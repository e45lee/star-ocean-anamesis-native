// port/decomp/particles/simulate.c: Ghidra decompiles for the particles subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileAt.java, tools/resolve_decomp.py
// run      2026-10-08 15:39 UTC: tools/decomp_at.sh '--into' 'particles/simulate' '0x229c46c' '0x22a07fc' '0x2472854' '0x2479360' '0x247ffb4' '0x248618c' '0x248d058' '0x2494134' '0x249b358' '0x24a1b10' '0x24a8cf4' '0x24b0cac' '0x24b7db0' '0x24be44c' '0x24c5b18' '0x24cde9c' '0x24d61b0' '0x24dd994' '0x24e59f4' '0x24edc54' '0x24f5e48' '0x24fd540' '0x2504a10' '0x250b3e4' '0x2511efc' '0x2517fb4' '0x251f694' '0x2526d58' '0x252e560' '0x2535300' '0x253cdbc' '0x2544994' '0x254d6a4' '0x25549cc' '0x255c700' '0x25642d0' '0x256bfd8' '0x2573330' '0x257ace8' '0x25823a4' '0x2589ba4' '0x2590944' '0x2598708' '0x25a10a4' '0x25a99c0' '0x25b17b0' '0x25bb118' '0x25c40a8' '0x25ccfc0' '0x25d53e4' '0x25df05c' '0x25e7fdc' '0x25f0ee4' '0x25f92c0' '0x2601b6c' '0x260c500' '0x2614e14' '0x261cc34' '0x26244d8' '0x262c290' '0x2633fd8' '0x263b1f0' '0x2642c94' '0x264a914' '0x2652520' '0x2659608' '0x2662b5c' '0x266bf48' '0x267575c' '0x267ef20' '0x2686db8' '0x268cfd8' '0x2693124' '0x2698ea0'

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> >::Simulate(float)
// vaddr 0x219c46c | ghidra 0x229c46c | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures9LifeLimitENS_6StNULLEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures9LifeLimitENS_6StNULLEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x0229c504:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x0229c50c:
    do {
      if (*piVar8 == -1) goto code_r0x0229c518;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0229c5d0;
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
code_r0x0229c5d0:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0229c5e0:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0229c5e8;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x0229c504;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0229c5e8:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0229c728;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0229c728:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x0229c518:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0229c5e0;
  goto code_r0x0229c50c;
}

// ==== Aska::ParticleEmitter<Aska::StNULL>::Simulate(float)
// vaddr 0x21a07fc | ghidra 0x22a07fc | size 944 | symbol _ZN4Aska15ParticleEmitterINS_6StNULLEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_6StNULLEE8SimulateEf(float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x022a0894:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x022a089c:
    do {
      if (*piVar8 == -1) goto code_r0x022a08a8;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x022a0960;
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
code_r0x022a0960:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x022a0970:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x022a0978;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x022a0894;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x022a0978:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::StNULL>::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x022a0ab8;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x022a0ab8:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::StNULL>::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::StNULL>::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x022a08a8:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x022a0970;
  goto code_r0x022a089c;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >::Simulate(float)
// vaddr 0x2372854 | ghidra 0x2472854 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x024728ec:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x024728f4:
    do {
      if (*piVar8 == -1) goto code_r0x02472900;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x024729b8;
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
code_r0x024729b8:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x024729c8:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x024729d0;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x024728ec;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x024729d0:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02472b10;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02472b10:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x02472900:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x024729c8;
  goto code_r0x024728f4;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > >::Simulate(float)
// vaddr 0x2379360 | ghidra 0x2479360 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x024793f8:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x02479400:
    do {
      if (*piVar8 == -1) goto code_r0x0247940c;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x024794c4;
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
code_r0x024794c4:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x024794d4:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x024794dc;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x024793f8;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x024794dc:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0247961c;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0247961c:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x0247940c:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x024794d4;
  goto code_r0x02479400;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > >::Simulate(float)
// vaddr 0x237ffb4 | ghidra 0x247ffb4 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_4LineENS_6StNULLEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_4LineENS_6StNULLEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x0248004c:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x02480054:
    do {
      if (*piVar8 == -1) goto code_r0x02480060;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02480118;
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
code_r0x02480118:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02480128:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02480130;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x0248004c;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02480130:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02480270;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02480270:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x02480060:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02480128;
  goto code_r0x02480054;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::StNULL> > >::Simulate(float)
// vaddr 0x238618c | ghidra 0x248618c | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS_6StNULLEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS_6StNULLEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x02486224:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x0248622c:
    do {
      if (*piVar8 == -1) goto code_r0x02486238;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x024862f0;
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
code_r0x024862f0:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02486300:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02486308;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x02486224;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02486308:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::StNULL> > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02486448;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02486448:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::StNULL> > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::StNULL> > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x02486238:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02486300;
  goto code_r0x0248622c;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x238d058 | ghidra 0x248d058 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x0248d0f0:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x0248d0f8:
    do {
      if (*piVar8 == -1) goto code_r0x0248d104;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0248d1bc;
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
code_r0x0248d1bc:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0248d1cc:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0248d1d4;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x0248d0f0;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0248d1d4:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0248d314;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0248d314:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x0248d104:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0248d1cc;
  goto code_r0x0248d0f8;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >::Simulate(float)
// vaddr 0x2394134 | ghidra 0x2494134 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x024941cc:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x024941d4:
    do {
      if (*piVar8 == -1) goto code_r0x024941e0;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02494298;
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
code_r0x02494298:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x024942a8:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x024942b0;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x024941cc;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x024942b0:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x024943f0;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x024943f0:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x024941e0:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x024942a8;
  goto code_r0x024941d4;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >::Simulate(float)
// vaddr 0x239b358 | ghidra 0x249b358 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x0249b3f0:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x0249b3f8:
    do {
      if (*piVar8 == -1) goto code_r0x0249b404;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0249b4bc;
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
code_r0x0249b4bc:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0249b4cc:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0249b4d4;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x0249b3f0;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0249b4d4:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0249b614;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0249b614:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x0249b404:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0249b4cc;
  goto code_r0x0249b3f8;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > >::Simulate(float)
// vaddr 0x23a1b10 | ghidra 0x24a1b10 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x024a1ba8:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x024a1bb0:
    do {
      if (*piVar8 == -1) goto code_r0x024a1bbc;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x024a1c74;
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
code_r0x024a1c74:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x024a1c84:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x024a1c8c;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x024a1ba8;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x024a1c8c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x024a1dcc;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x024a1dcc:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x024a1bbc:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x024a1c84;
  goto code_r0x024a1bb0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Simulate(float)
// vaddr 0x23a8cf4 | ghidra 0x24a8cf4 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x024a8d8c:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x024a8d94:
    do {
      if (*piVar8 == -1) goto code_r0x024a8da0;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x024a8e58;
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
code_r0x024a8e58:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x024a8e68:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x024a8e70;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x024a8d8c;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x024a8e70:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x024a8fb0;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x024a8fb0:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x024a8da0:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x024a8e68;
  goto code_r0x024a8d94;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Simulate(float)
// vaddr 0x23b0cac | ghidra 0x24b0cac | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x024b0d44:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x024b0d4c:
    do {
      if (*piVar8 == -1) goto code_r0x024b0d58;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x024b0e10;
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
code_r0x024b0e10:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x024b0e20:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x024b0e28;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x024b0d44;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x024b0e28:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x024b0f68;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x024b0f68:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x024b0d58:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x024b0e20;
  goto code_r0x024b0d4c;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Simulate(float)
// vaddr 0x23b7db0 | ghidra 0x24b7db0 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x024b7e48:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x024b7e50:
    do {
      if (*piVar8 == -1) goto code_r0x024b7e5c;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x024b7f14;
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
code_r0x024b7f14:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x024b7f24:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x024b7f2c;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x024b7e48;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x024b7f2c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x024b806c;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x024b806c:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x024b7e5c:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x024b7f24;
  goto code_r0x024b7e50;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x23be44c | ghidra 0x24be44c | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x024be4e4:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x024be4ec:
    do {
      if (*piVar8 == -1) goto code_r0x024be4f8;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x024be5b0;
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
code_r0x024be5b0:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x024be5c0:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x024be5c8;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x024be4e4;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x024be5c8:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x024be708;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x024be708:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x024be4f8:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x024be5c0;
  goto code_r0x024be4ec;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::Simulate(float)
// vaddr 0x23c5b18 | ghidra 0x24c5b18 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x024c5bb0:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x024c5bb8:
    do {
      if (*piVar9 == -1) goto code_r0x024c5bc4;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x024c5c7c;
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
code_r0x024c5c7c:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x024c5c8c:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x024c5c94;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x024c5bb0;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x024c5c94:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x024c5dd4;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x024c5dd4:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x024c5bc4:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x024c5c8c;
  goto code_r0x024c5bb8;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x23cde9c | ghidra 0x24cde9c | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x024cdf34:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x024cdf3c:
    do {
      if (*piVar9 == -1) goto code_r0x024cdf48;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x024ce000;
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
code_r0x024ce000:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x024ce010:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x024ce018;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x024cdf34;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x024ce018:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x024ce158;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x024ce158:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x024cdf48:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x024ce010;
  goto code_r0x024cdf3c;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x23d61b0 | ghidra 0x24d61b0 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x024d6248:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x024d6250:
    do {
      if (*piVar9 == -1) goto code_r0x024d625c;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x024d6314;
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
code_r0x024d6314:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x024d6324:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x024d632c;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x024d6248;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x024d632c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x024d646c;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x024d646c:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x024d625c:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x024d6324;
  goto code_r0x024d6250;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > > >::Simulate(float)
// vaddr 0x23dd994 | ghidra 0x24dd994 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS_6StNULLEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS_6StNULLEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x024dda2c:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x024dda34:
    do {
      if (*piVar9 == -1) goto code_r0x024dda40;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x024ddaf8;
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
code_r0x024ddaf8:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x024ddb08:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x024ddb10;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x024dda2c;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x024ddb10:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x024ddc50;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x024ddc50:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x024dda40:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x024ddb08;
  goto code_r0x024dda34;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::Simulate(float)
// vaddr 0x23e59f4 | ghidra 0x24e59f4 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x024e5a8c:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x024e5a94:
    do {
      if (*piVar9 == -1) goto code_r0x024e5aa0;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x024e5b58;
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
code_r0x024e5b58:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x024e5b68:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x024e5b70;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x024e5a8c;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x024e5b70:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x024e5cb0;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x024e5cb0:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x024e5aa0:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x024e5b68;
  goto code_r0x024e5a94;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Simulate(float)
// vaddr 0x23edc54 | ghidra 0x24edc54 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x024edcec:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x024edcf4:
    do {
      if (*piVar9 == -1) goto code_r0x024edd00;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x024eddb8;
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
code_r0x024eddb8:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x024eddc8:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x024eddd0;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x024edcec;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x024eddd0:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x024edf10;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x024edf10:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x024edd00:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x024eddc8;
  goto code_r0x024edcf4;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Simulate(float)
// vaddr 0x23f5e48 | ghidra 0x24f5e48 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x024f5ee0:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x024f5ee8:
    do {
      if (*piVar9 == -1) goto code_r0x024f5ef4;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x024f5fac;
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
code_r0x024f5fac:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x024f5fbc:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x024f5fc4;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x024f5ee0;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x024f5fc4:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x024f6104;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x024f6104:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x024f5ef4:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x024f5fbc;
  goto code_r0x024f5ee8;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Simulate(float)
// vaddr 0x23fd540 | ghidra 0x24fd540 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x024fd5d8:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x024fd5e0:
    do {
      if (*piVar9 == -1) goto code_r0x024fd5ec;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x024fd6a4;
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
code_r0x024fd6a4:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x024fd6b4:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x024fd6bc;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x024fd5d8;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x024fd6bc:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x024fd7fc;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x024fd7fc:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x024fd5ec:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x024fd6b4;
  goto code_r0x024fd5e0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Simulate(float)
// vaddr 0x2404a10 | ghidra 0x2504a10 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x02504aa8:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x02504ab0:
    do {
      if (*piVar8 == -1) goto code_r0x02504abc;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02504b74;
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
code_r0x02504b74:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02504b84:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02504b8c;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x02504aa8;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02504b8c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02504ccc;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02504ccc:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x02504abc:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02504b84;
  goto code_r0x02504ab0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x240b3e4 | ghidra 0x250b3e4 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x0250b47c:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x0250b484:
    do {
      if (*piVar8 == -1) goto code_r0x0250b490;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0250b548;
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
code_r0x0250b548:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0250b558:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0250b560;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x0250b47c;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0250b560:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0250b6a0;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0250b6a0:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x0250b490:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0250b558;
  goto code_r0x0250b484;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x2411efc | ghidra 0x2511efc | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x02511f94:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x02511f9c:
    do {
      if (*piVar8 == -1) goto code_r0x02511fa8;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02512060;
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
code_r0x02512060:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02512070:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02512078;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x02511f94;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02512078:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x025121b8;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x025121b8:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x02511fa8:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02512070;
  goto code_r0x02511f9c;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > >::Simulate(float)
// vaddr 0x2417fb4 | ghidra 0x2517fb4 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x0251804c:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x02518054:
    do {
      if (*piVar8 == -1) goto code_r0x02518060;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02518118;
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
code_r0x02518118:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02518128:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02518130;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x0251804c;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02518130:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02518270;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02518270:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x02518060:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02518128;
  goto code_r0x02518054;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x241f694 | ghidra 0x251f694 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x0251f72c:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x0251f734:
    do {
      if (*piVar8 == -1) goto code_r0x0251f740;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0251f7f8;
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
code_r0x0251f7f8:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0251f808:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0251f810;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x0251f72c;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0251f810:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0251f950;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0251f950:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x0251f740:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0251f808;
  goto code_r0x0251f734;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >::Simulate(float)
// vaddr 0x2426d58 | ghidra 0x2526d58 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x02526df0:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x02526df8:
    do {
      if (*piVar8 == -1) goto code_r0x02526e04;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02526ebc;
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
code_r0x02526ebc:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02526ecc:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02526ed4;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x02526df0;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02526ed4:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02527014;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02527014:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x02526e04:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02526ecc;
  goto code_r0x02526df8;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >::Simulate(float)
// vaddr 0x242e560 | ghidra 0x252e560 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_4LineENS_6StNULLEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_4LineENS_6StNULLEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x0252e5f8:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x0252e600:
    do {
      if (*piVar8 == -1) goto code_r0x0252e60c;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0252e6c4;
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
code_r0x0252e6c4:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0252e6d4:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0252e6dc;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x0252e5f8;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0252e6dc:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0252e81c;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0252e81c:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x0252e60c:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0252e6d4;
  goto code_r0x0252e600;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::StNULL> > > >::Simulate(float)
// vaddr 0x2435300 | ghidra 0x2535300 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS_6StNULLEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS_6StNULLEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x02535398:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x025353a0:
    do {
      if (*piVar8 == -1) goto code_r0x025353ac;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02535464;
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
code_r0x02535464:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02535474:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0253547c;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x02535398;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0253547c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::StNULL> > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x025355bc;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x025355bc:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::StNULL> > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::StNULL> > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x025353ac:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02535474;
  goto code_r0x025353a0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::Simulate(float)
// vaddr 0x243cdbc | ghidra 0x253cdbc | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x0253ce54:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x0253ce5c:
    do {
      if (*piVar8 == -1) goto code_r0x0253ce68;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0253cf20;
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
code_r0x0253cf20:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0253cf30:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0253cf38;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x0253ce54;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0253cf38:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0253d078;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0253d078:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x0253ce68:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0253cf30;
  goto code_r0x0253ce5c;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x2444994 | ghidra 0x2544994 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x02544a2c:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x02544a34:
    do {
      if (*piVar8 == -1) goto code_r0x02544a40;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02544af8;
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
code_r0x02544af8:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02544b08:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02544b10;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x02544a2c;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02544b10:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02544c50;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02544c50:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x02544a40:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02544b08;
  goto code_r0x02544a34;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x244d6a4 | ghidra 0x254d6a4 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x0254d73c:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x0254d744:
    do {
      if (*piVar8 == -1) goto code_r0x0254d750;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0254d808;
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
code_r0x0254d808:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0254d818:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0254d820;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x0254d73c;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0254d820:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0254d960;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0254d960:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x0254d750:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0254d818;
  goto code_r0x0254d744;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > > >::Simulate(float)
// vaddr 0x24549cc | ghidra 0x25549cc | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x02554a64:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x02554a6c:
    do {
      if (*piVar8 == -1) goto code_r0x02554a78;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02554b30;
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
code_r0x02554b30:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02554b40:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02554b48;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x02554a64;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02554b48:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02554c88;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02554c88:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x02554a78:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02554b40;
  goto code_r0x02554a6c;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::Simulate(float)
// vaddr 0x245c700 | ghidra 0x255c700 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x0255c798:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x0255c7a0:
    do {
      if (*piVar8 == -1) goto code_r0x0255c7ac;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0255c864;
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
code_r0x0255c864:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0255c874:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0255c87c;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x0255c798;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0255c87c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0255c9bc;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0255c9bc:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x0255c7ac:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0255c874;
  goto code_r0x0255c7a0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Simulate(float)
// vaddr 0x24642d0 | ghidra 0x25642d0 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x02564368:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x02564370:
    do {
      if (*piVar8 == -1) goto code_r0x0256437c;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02564434;
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
code_r0x02564434:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02564444:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0256444c;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x02564368;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0256444c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0256458c;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0256458c:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x0256437c:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02564444;
  goto code_r0x02564370;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Simulate(float)
// vaddr 0x246bfd8 | ghidra 0x256bfd8 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x0256c070:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x0256c078:
    do {
      if (*piVar8 == -1) goto code_r0x0256c084;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0256c13c;
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
code_r0x0256c13c:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0256c14c:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0256c154;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x0256c070;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0256c154:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0256c294;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0256c294:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x0256c084:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0256c14c;
  goto code_r0x0256c078;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Simulate(float)
// vaddr 0x2473330 | ghidra 0x2573330 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x025733c8:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x025733d0:
    do {
      if (*piVar8 == -1) goto code_r0x025733dc;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02573494;
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
code_r0x02573494:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x025734a4:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x025734ac;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x025733c8;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x025734ac:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x025735ec;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x025735ec:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x025733dc:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x025734a4;
  goto code_r0x025733d0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Simulate(float)
// vaddr 0x247ace8 | ghidra 0x257ace8 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x0257ad80:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x0257ad88:
    do {
      if (*piVar8 == -1) goto code_r0x0257ad94;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0257ae4c;
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
code_r0x0257ae4c:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0257ae5c:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0257ae64;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x0257ad80;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0257ae64:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0257afa4;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0257afa4:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x0257ad94:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0257ae5c;
  goto code_r0x0257ad88;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Simulate(float)
// vaddr 0x24823a4 | ghidra 0x25823a4 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x0258243c:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x02582444:
    do {
      if (*piVar8 == -1) goto code_r0x02582450;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02582508;
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
code_r0x02582508:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02582518:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02582520;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x0258243c;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02582520:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02582660;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02582660:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x02582450:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02582518;
  goto code_r0x02582444;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Simulate(float)
// vaddr 0x2489ba4 | ghidra 0x2589ba4 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x02589c3c:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x02589c44:
    do {
      if (*piVar8 == -1) goto code_r0x02589c50;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02589d08;
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
code_r0x02589d08:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02589d18:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02589d20;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x02589c3c;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02589d20:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02589e60;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02589e60:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x02589c50:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02589d18;
  goto code_r0x02589c44;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x2490944 | ghidra 0x2590944 | size 944 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  long lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar10 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar10 + 0x8b4) = 0;
  lVar9 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar9 != 0) {
code_r0x025909dc:
    piVar8 = (int *)(lVar9 + 0x38);
    iVar7 = 0;
code_r0x025909e4:
    do {
      if (*piVar8 == -1) goto code_r0x025909f0;
      ClearExclusiveLocal();
      bVar4 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02590aa8;
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
code_r0x02590aa8:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02590ab8:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02590ac0;
  }
  lVar9 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar9 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar9);
    *(long *)(param_2 + 0x1e0) = lVar9;
    goto code_r0x025909dc;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02590ac0:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar11 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar11 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar12 = *(float *)(param_2 + 0x280);
    fVar13 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar11 = param_1 * fVar12 *
             (*(float *)(param_2 + 0x284) * fVar11 + fVar13 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar11 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02590c00;
    }
    fVar11 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar12 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar13 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar12 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    if ((fVar11 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02590c00:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar11 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar11) {
    *(float *)(param_2 + 0x288) = fVar11 - (float)(int)fVar11;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar11,&uStack_190,alStack_88);
  }
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar10 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar10 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar10,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar8 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar8) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar4) {
          *piVar8 = *piVar8 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar9 + 0x78);
      }
    }
  }
  return;
code_r0x025909f0:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
  if (bVar4) {
    *piVar8 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02590ab8;
  goto code_r0x025909e4;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::Simulate(float)
// vaddr 0x2498708 | ghidra 0x2598708 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x025987a0:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x025987a8:
    do {
      if (*piVar9 == -1) goto code_r0x025987b4;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0259886c;
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
code_r0x0259886c:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0259887c:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02598884;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x025987a0;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02598884:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x025989c4;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x025989c4:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x025987b4:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0259887c;
  goto code_r0x025987a8;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x24a10a4 | ghidra 0x25a10a4 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x025a113c:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x025a1144:
    do {
      if (*piVar9 == -1) goto code_r0x025a1150;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x025a1208;
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
code_r0x025a1208:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x025a1218:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x025a1220;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x025a113c;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x025a1220:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x025a1360;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x025a1360:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x025a1150:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x025a1218;
  goto code_r0x025a1144;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x24a99c0 | ghidra 0x25a99c0 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x025a9a58:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x025a9a60:
    do {
      if (*piVar9 == -1) goto code_r0x025a9a6c;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x025a9b24;
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
code_r0x025a9b24:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x025a9b34:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x025a9b3c;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x025a9a58;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x025a9b3c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x025a9c7c;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x025a9c7c:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x025a9a6c:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x025a9b34;
  goto code_r0x025a9a60;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > > >::Simulate(float)
// vaddr 0x24b17b0 | ghidra 0x25b17b0 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS_6StNULLEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS_6StNULLEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x025b1848:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x025b1850:
    do {
      if (*piVar9 == -1) goto code_r0x025b185c;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x025b1914;
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
code_r0x025b1914:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x025b1924:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x025b192c;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x025b1848;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x025b192c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x025b1a6c;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x025b1a6c:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x025b185c:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x025b1924;
  goto code_r0x025b1850;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > > >::Simulate(float)
// vaddr 0x24bb118 | ghidra 0x25bb118 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x025bb1b0:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x025bb1b8:
    do {
      if (*piVar9 == -1) goto code_r0x025bb1c4;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x025bb27c;
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
code_r0x025bb27c:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x025bb28c:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x025bb294;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x025bb1b0;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x025bb294:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x025bb3d4;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x025bb3d4:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3ea)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3e0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ee);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x025bb1c4:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x025bb28c;
  goto code_r0x025bb1b8;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > > >::Simulate(float)
// vaddr 0x24c40a8 | ghidra 0x25c40a8 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x025c4140:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x025c4148:
    do {
      if (*piVar9 == -1) goto code_r0x025c4154;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x025c420c;
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
code_r0x025c420c:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x025c421c:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x025c4224;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x025c4140;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x025c4224:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x025c4364;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x025c4364:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3ea)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3e0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ee);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x025c4154:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x025c421c;
  goto code_r0x025c4148;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::Simulate(float)
// vaddr 0x24ccfc0 | ghidra 0x25ccfc0 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x025cd058:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x025cd060:
    do {
      if (*piVar9 == -1) goto code_r0x025cd06c;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x025cd124;
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
code_r0x025cd124:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x025cd134:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x025cd13c;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x025cd058;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x025cd13c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x025cd27c;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x025cd27c:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3ea)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3e0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ee);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x025cd06c:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x025cd134;
  goto code_r0x025cd060;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x24d53e4 | ghidra 0x25d53e4 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x025d547c:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x025d5484:
    do {
      if (*piVar9 == -1) goto code_r0x025d5490;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x025d5548;
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
code_r0x025d5548:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x025d5558:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x025d5560;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x025d547c;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x025d5560:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x025d56a0;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x025d56a0:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3ea)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3e0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ee);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x025d5490:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x025d5558;
  goto code_r0x025d5484;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > >::Simulate(float)
// vaddr 0x24df05c | ghidra 0x25df05c | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x025df0f4:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x025df0fc:
    do {
      if (*piVar9 == -1) goto code_r0x025df108;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x025df1c0;
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
code_r0x025df1c0:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x025df1d0:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x025df1d8;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x025df0f4;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x025df1d8:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x025df318;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x025df318:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3ea)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3e0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ee);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x025df108:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x025df1d0;
  goto code_r0x025df0fc;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::Simulate(float)
// vaddr 0x24e7fdc | ghidra 0x25e7fdc | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x025e8074:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x025e807c:
    do {
      if (*piVar9 == -1) goto code_r0x025e8088;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x025e8140;
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
code_r0x025e8140:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x025e8150:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x025e8158;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x025e8074;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x025e8158:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x025e8298;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x025e8298:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3ea)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3e0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ee);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x025e8088:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x025e8150;
  goto code_r0x025e807c;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::Simulate(float)
// vaddr 0x24f0ee4 | ghidra 0x25f0ee4 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x025f0f7c:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x025f0f84:
    do {
      if (*piVar9 == -1) goto code_r0x025f0f90;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x025f1048;
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
code_r0x025f1048:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x025f1058:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x025f1060;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x025f0f7c;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x025f1060:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x025f11a0;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x025f11a0:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3ea)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3e0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ee);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x025f0f90:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x025f1058;
  goto code_r0x025f0f84;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Simulate(float)
// vaddr 0x24f92c0 | ghidra 0x25f92c0 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x025f9358:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x025f9360:
    do {
      if (*piVar9 == -1) goto code_r0x025f936c;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x025f9424;
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
code_r0x025f9424:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x025f9434:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x025f943c;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x025f9358;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x025f943c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x025f957c;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x025f957c:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3ea)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3e0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ee);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x025f936c:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x025f9434;
  goto code_r0x025f9360;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::Simulate(float)
// vaddr 0x2501b6c | ghidra 0x2601b6c | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x02601c04:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x02601c0c:
    do {
      if (*piVar9 == -1) goto code_r0x02601c18;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02601cd0;
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
code_r0x02601cd0:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02601ce0:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02601ce8;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x02601c04;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02601ce8:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02601e28;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02601e28:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x02601c18:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02601ce0;
  goto code_r0x02601c0c;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Simulate(float)
// vaddr 0x250c500 | ghidra 0x260c500 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x0260c598:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x0260c5a0:
    do {
      if (*piVar9 == -1) goto code_r0x0260c5ac;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0260c664;
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
code_r0x0260c664:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0260c674:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0260c67c;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x0260c598;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0260c67c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0260c7bc;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0260c7bc:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x0260c5ac:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0260c674;
  goto code_r0x0260c5a0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Simulate(float)
// vaddr 0x2514e14 | ghidra 0x2614e14 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x02614eac:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x02614eb4:
    do {
      if (*piVar9 == -1) goto code_r0x02614ec0;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02614f78;
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
code_r0x02614f78:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02614f88:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02614f90;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x02614eac;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02614f90:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x026150d0;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x026150d0:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x02614ec0:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02614f88;
  goto code_r0x02614eb4;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Simulate(float)
// vaddr 0x251cc34 | ghidra 0x261cc34 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x0261cccc:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x0261ccd4:
    do {
      if (*piVar9 == -1) goto code_r0x0261cce0;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0261cd98;
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
code_r0x0261cd98:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0261cda8:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0261cdb0;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x0261cccc;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0261cdb0:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0261cef0;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0261cef0:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x0261cce0:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0261cda8;
  goto code_r0x0261ccd4;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x25244d8 | ghidra 0x26244d8 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x02624570:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x02624578:
    do {
      if (*piVar9 == -1) goto code_r0x02624584;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0262463c;
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
code_r0x0262463c:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0262464c:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02624654;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x02624570;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02624654:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02624794;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02624794:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x02624584:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0262464c;
  goto code_r0x02624578;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >::Simulate(float)
// vaddr 0x252c290 | ghidra 0x262c290 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x0262c328:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x0262c330:
    do {
      if (*piVar9 == -1) goto code_r0x0262c33c;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0262c3f4;
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
code_r0x0262c3f4:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0262c404:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0262c40c;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x0262c328;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0262c40c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0262c54c;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0262c54c:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x0262c33c:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0262c404;
  goto code_r0x0262c330;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >::Simulate(float)
// vaddr 0x2533fd8 | ghidra 0x2633fd8 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x02634070:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x02634078:
    do {
      if (*piVar9 == -1) goto code_r0x02634084;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0263413c;
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
code_r0x0263413c:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0263414c:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02634154;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x02634070;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02634154:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02634294;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02634294:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x02634084:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0263414c;
  goto code_r0x02634078;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > >::Simulate(float)
// vaddr 0x253b1f0 | ghidra 0x263b1f0 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS_6StNULLEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS_6StNULLEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x0263b288:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x0263b290:
    do {
      if (*piVar9 == -1) goto code_r0x0263b29c;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0263b354;
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
code_r0x0263b354:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0263b364:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0263b36c;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x0263b288;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0263b36c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0263b4ac;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0263b4ac:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x0263b29c:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0263b364;
  goto code_r0x0263b290;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Simulate(float)
// vaddr 0x2542c94 | ghidra 0x2642c94 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x02642d2c:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x02642d34:
    do {
      if (*piVar9 == -1) goto code_r0x02642d40;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02642df8;
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
code_r0x02642df8:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02642e08:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02642e10;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x02642d2c;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02642e10:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02642f50;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02642f50:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x02642d40:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02642e08;
  goto code_r0x02642d34;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Simulate(float)
// vaddr 0x254a914 | ghidra 0x264a914 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x0264a9ac:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x0264a9b4:
    do {
      if (*piVar9 == -1) goto code_r0x0264a9c0;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0264aa78;
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
code_r0x0264aa78:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0264aa88:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0264aa90;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x0264a9ac;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0264aa90:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0264abd0;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0264abd0:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x0264a9c0:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0264aa88;
  goto code_r0x0264a9b4;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Simulate(float)
// vaddr 0x2552520 | ghidra 0x2652520 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x026525b8:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x026525c0:
    do {
      if (*piVar9 == -1) goto code_r0x026525cc;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02652684;
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
code_r0x02652684:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02652694:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0265269c;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x026525b8;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0265269c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x026527dc;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x026527dc:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x026525cc:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02652694;
  goto code_r0x026525c0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x2559608 | ghidra 0x2659608 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x026596a0:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x026596a8:
    do {
      if (*piVar9 == -1) goto code_r0x026596b4;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0265976c;
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
code_r0x0265976c:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0265977c:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02659784;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x026596a0;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02659784:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x026598c4;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x026598c4:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3aa)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3a0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ae);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x026596b4:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0265977c;
  goto code_r0x026596a8;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > > > >::Simulate(float)
// vaddr 0x2562b5c | ghidra 0x2662b5c | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x02662bf4:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x02662bfc:
    do {
      if (*piVar9 == -1) goto code_r0x02662c08;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02662cc0;
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
code_r0x02662cc0:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02662cd0:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02662cd8;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x02662bf4;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02662cd8:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02662e18;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02662e18:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3ea)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3e0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ee);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x02662c08:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02662cd0;
  goto code_r0x02662bfc;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > > > >::Simulate(float)
// vaddr 0x256bf48 | ghidra 0x266bf48 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x0266bfe0:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x0266bfe8:
    do {
      if (*piVar9 == -1) goto code_r0x0266bff4;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0266c0ac;
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
code_r0x0266c0ac:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0266c0bc:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0266c0c4;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x0266bfe0;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0266c0c4:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0266c204;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0266c204:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3ea)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3e0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ee);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x0266bff4:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0266c0bc;
  goto code_r0x0266bfe8;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > > >::Simulate(float)
// vaddr 0x257575c | ghidra 0x267575c | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x026757f4:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x026757fc:
    do {
      if (*piVar9 == -1) goto code_r0x02675808;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x026758c0;
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
code_r0x026758c0:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x026758d0:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x026758d8;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x026757f4;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x026758d8:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02675a18;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02675a18:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3ea)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3e0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ee);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x02675808:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x026758d0;
  goto code_r0x026757fc;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > >::Simulate(float)
// vaddr 0x257ef20 | ghidra 0x267ef20 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x0267efb8:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x0267efc0:
    do {
      if (*piVar9 == -1) goto code_r0x0267efcc;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0267f084;
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
code_r0x0267f084:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0267f094:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0267f09c;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x0267efb8;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0267f09c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0267f1dc;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0267f1dc:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3ea)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3e0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ee);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x0267efcc:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0267f094;
  goto code_r0x0267efc0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::Simulate(float)
// vaddr 0x2586db8 | ghidra 0x2686db8 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x02686e50:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x02686e58:
    do {
      if (*piVar9 == -1) goto code_r0x02686e64;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02686f1c;
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
code_r0x02686f1c:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02686f2c:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x02686f34;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x02686e50;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x02686f34:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x02687074;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x02687074:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3ea)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3e0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ee);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x02686e64:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02686f2c;
  goto code_r0x02686e58;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x258cfd8 | ghidra 0x268cfd8 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x0268d070:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x0268d078:
    do {
      if (*piVar9 == -1) goto code_r0x0268d084;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x0268d13c;
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
code_r0x0268d13c:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x0268d14c:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0268d154;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x0268d070;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0268d154:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0268d294;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0268d294:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3ea)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3e0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ee);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x0268d084:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0268d14c;
  goto code_r0x0268d078;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::Simulate(float)
// vaddr 0x2593124 | ghidra 0x2693124 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x026931bc:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x026931c4:
    do {
      if (*piVar9 == -1) goto code_r0x026931d0;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02693288;
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
code_r0x02693288:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02693298:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x026932a0;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x026931bc;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x026932a0:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x026933e0;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x026933e0:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3ea)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3e0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ee);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x026931d0:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02693298;
  goto code_r0x026931c4;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::StNULL> > > > >::Simulate(float)
// vaddr 0x2598ea0 | ghidra 0x2698ea0 | size 1020 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS_6StNULLEEEEEEEEEE8SimulateEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS_6StNULLEEEEEEEEEE8SimulateEf
               (float param_1,long param_2)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_b0;
  undefined1 uStack_ac;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  long alStack_88 [5];
  
  if (*(long *)(param_2 + 0x1b8) == 0) {
    return;
  }
  if (*(long *)(param_2 + 0x1c0) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x215) & 1) != 0) {
    return;
  }
  if ((*(byte *)(param_2 + 0x210) - 1 < 2) && (*(long *)(param_2 + 0x1d8) == 0)) {
    return;
  }
  Aska::IParticleEmitter::PerfCounterStart()(param_2);
  lVar11 = *(long *)(param_2 + 0x1c0);
  *(undefined4 *)(lVar11 + 0x8b4) = 0;
  lVar10 = *(long *)(param_2 + 0x1e0);
  param_1 = *(float *)(param_2 + 800) * param_1;
  if (lVar10 != 0) {
code_r0x02698f38:
    piVar9 = (int *)(lVar10 + 0x38);
    iVar8 = 0;
code_r0x02698f40:
    do {
      if (*piVar9 == -1) goto code_r0x02698f4c;
      ClearExclusiveLocal();
      bVar4 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar4);
    piVar1 = (int *)(lVar10 + 0x3c);
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
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
          if ((uVar7 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar10 + 0x78);
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
            if (cVar3 == '\0') goto code_r0x02699004;
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
code_r0x02699004:
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
code_r0x02699014:
    DataMemoryBarrier(2,3);
    bVar4 = false;
    goto code_r0x0269901c;
  }
  lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x90,PTR__ZSt7nothrow_02cb9a80);
  if (lVar10 != 0) {
    Aska::FastCriticalSection::FastCriticalSection()(lVar10);
    *(long *)(param_2 + 0x1e0) = lVar10;
    goto code_r0x02698f38;
  }
  *(undefined8 *)(param_2 + 0x1e0) = 0;
  bVar4 = true;
code_r0x0269901c:
  Aska::IParticleEmitter::FillMatrixContext(Aska::IParticleEmitter::MatrixContext*)(param_2,alStack_88);
  fStack_a0 = *(float *)(alStack_88[0] + 0xc);
  fStack_9c = *(float *)(alStack_88[0] + 0x1c);
  fStack_98 = *(float *)(alStack_88[0] + 0x2c);
  uStack_94 = 0x3f800000;
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::StNULL> > > > >::EmitterAffectToParticle(Aska::Vector*, Aska::IParticleEmitter::MatrixContext*, float)(param_1,param_2,&fStack_a0,alStack_88);
  fVar12 = _UNK_027e6ae4;
  if (_UNK_027e5198 <= *(float *)(param_2 + 0x284)) {
    fVar12 = param_1 * *(float *)(param_2 + 0x280);
  }
  else {
    fVar13 = *(float *)(param_2 + 0x280);
    fVar14 = (_UNK_027e5198 - *(float *)(param_2 + 0x284)) * _UNK_027e6ae4;
    uVar5 = Aska::Random(unsigned int)(10000);
    fVar12 = param_1 * fVar13 *
             (*(float *)(param_2 + 0x284) * fVar12 + fVar14 * (float)uVar5 * _UNK_027edb40);
  }
  *(float *)(param_2 + 0x288) = fVar12 + *(float *)(param_2 + 0x288);
  if ((*(byte *)(param_2 + 0x2d9) >> 3 & 1) != 0) {
    if (*(char *)(param_2 + 0x324) != '\0') {
      *(undefined1 *)(param_2 + 0x324) = 0;
      *(ulong *)(param_2 + 0x2e8) = CONCAT44(uStack_94,fStack_98);
      *(ulong *)(param_2 + 0x2e0) = CONCAT44(fStack_9c,fStack_a0);
      bVar2 = *(byte *)(param_2 + 0x2d9);
      goto joined_r0x0269915c;
    }
    fVar12 = *(float *)(param_2 + 0x2e0) - fStack_a0;
    fVar13 = (float)*(undefined8 *)(param_2 + 0x2e4) - fStack_9c;
    fVar14 = (float)((ulong)*(undefined8 *)(param_2 + 0x2e4) >> 0x20) - fStack_98;
    fVar13 = fVar12 * fVar12 + fVar13 * fVar13 + fVar14 * fVar14;
    fVar12 = SQRT(fVar13);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar13);
    }
    if ((fVar12 < _UNK_027e6a14) || (*(float *)(param_2 + 0x284) == 0.0)) {
      *(undefined1 *)(param_2 + 0x300) = 1;
    }
  }
  bVar2 = *(byte *)(param_2 + 0x2d9);
joined_r0x0269915c:
  if ((bVar2 >> 4 & 1) != 0) {
    Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const(alStack_88[0],0,0,&uStack_190);
    *(undefined8 *)(param_2 + 0x318) = uStack_188;
    *(undefined8 *)(param_2 + 0x310) = uStack_190;
  }
  fVar12 = *(float *)(param_2 + 0x288);
  if (1.0 <= fVar12) {
    *(float *)(param_2 + 0x288) = fVar12 - (float)(int)fVar12;
    uStack_ac = 0;
    fStack_b0 = param_1;
    Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::StNULL> > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)(param_2,(int)fVar12,&uStack_190,alStack_88);
  }
  lVar6 = *(long *)(param_2 + 0x1b8);
  if (*(uint *)(lVar6 + 0x16c) != (uint)*(byte *)(param_2 + 0x3ea)) {
    Aska::IParticleObject::SetAnimation(int)();
    lVar6 = *(long *)(param_2 + 0x1b8);
  }
  *(undefined4 *)(lVar6 + 0x178) = *(undefined4 *)(param_2 + 0x3e0);
  lVar6 = *(long *)(param_2 + 0x1b8);
  bVar2 = *(byte *)(param_2 + 0x3ee);
  *(undefined2 *)(lVar6 + 500) = *(undefined2 *)(lVar6 + 500);
  *(byte *)(lVar6 + 0x1f6) = *(byte *)(lVar6 + 0x1f6) & 0xfe | bVar2 >> 2 & 1;
  Aska::IParticleEmitter::PerfCounterEnd()(param_2);
  *(ulong *)(lVar11 + 0x868) = CONCAT44(uStack_94,fStack_98);
  *(ulong *)(lVar11 + 0x860) = CONCAT44(fStack_9c,fStack_a0);
  Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::StNULL> > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)(param_1,lVar11,alStack_88,
                  *(float *)(param_2 + 0x200) < *(float *)(param_2 + 0x1fc));
  if (!bVar4) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar10 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar9 = (int *)(lVar10 + 0x3c);
    if (0x14 < *piVar9) {
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar4) {
          *piVar9 = *piVar9 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0x78);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar10 + 0x78);
      }
    }
  }
  return;
code_r0x02698f4c:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar9,0x10);
  if (bVar4) {
    *piVar9 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02699014;
  goto code_r0x02698f40;
}
