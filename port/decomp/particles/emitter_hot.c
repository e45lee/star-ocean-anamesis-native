// port/decomp/particles/emitter_hot.c: Ghidra decompiles for the particles subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileAt.java, tools/resolve_decomp.py
// run      2026-10-08 13:24 UTC: tools/decomp_at.sh '--into' 'particles/emitter_hot' '0x24cde9c' '0x24ce704' '0x24ce49c' '0x24c9ecc' '0x24c5b18'

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

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::Emit(int, Aska::IParticleEmitter::EmitContext*, Aska::IParticleEmitter::MatrixContext const*)
// vaddr 0x23c9ecc | ghidra 0x24c9ecc | size 8380 | symbol _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEE4EmitEiPNS_16IParticleEmitter11EmitContextEPKNSF_13MatrixContextE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEE4EmitEiPNS_16IParticleEmitter11EmitContextEPKNSF_13MatrixContextE
               (long param_1,int param_2,long *param_3,long *param_4)

{
  undefined8 *puVar1;
  undefined2 *puVar2;
  undefined4 uVar3;
  byte bVar4;
  ushort uVar5;
  uint uVar6;
  undefined1 uVar7;
  undefined4 uVar8;
  long lVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  long lVar14;
  ulong uVar15;
  undefined4 *puVar16;
  undefined8 *puVar17;
  long lVar18;
  uint uVar19;
  long lVar20;
  float *pfVar21;
  int iVar22;
  float fVar23;
  float fVar24;
  undefined8 uVar25;
  ulong uVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float unaff_s9;
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
  float fVar42;
  float fVar43;
  float fVar44;
  float fStack_254;
  float fStack_250;
  float fStack_24c;
  float fStack_23c;
  float fStack_238;
  float fStack_234;
  float fStack_230;
  float fStack_22c;
  float fStack_228;
  float fStack_224;
  float fStack_220;
  float fStack_21c;
  float fStack_218;
  undefined8 uStack_210;
  long lStack_208;
  float fStack_1f0;
  float fStack_1ec;
  float fStack_1e8;
  undefined8 uStack_1e0;
  undefined8 uStack_1d8;
  float fStack_1d0;
  float fStack_1cc;
  float fStack_1c8;
  float fStack_1c4;
  byte bStack_12c;
  float fStack_120;
  float fStack_11c;
  float fStack_118;
  float fStack_114;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined1 auStack_f0 [16];
  undefined8 uStack_e0;
  ulong uStack_d8;
  undefined8 uStack_d0;
  ulong uStack_c8;
  undefined8 uStack_c0;
  ulong uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  
  lVar18 = *(long *)(param_1 + 0x1b8);
  if (lVar18 == 0) {
    return;
  }
  if (*(long *)(param_1 + 0x1c0) == 0) {
    return;
  }
  puVar17 = (undefined8 *)*param_4;
  lVar20 = param_4[3];
  uStack_e0 = *puVar17;
  uStack_d0 = puVar17[2];
  uStack_c0 = puVar17[4];
  uStack_a8 = puVar17[7];
  uStack_b0 = puVar17[6];
  uStack_d8 = puVar17[1] & 0xffffffff;
  uStack_c8 = puVar17[3] & 0xffffffff;
  uStack_b8 = puVar17[5] & 0xffffffff;
  bVar4 = *(byte *)(param_1 + 0x2d9);
  uVar25 = uStack_b0;
  if (((bVar4 >> 3 & 1) != 0) && (*(char *)(param_1 + 0x300) != '\0')) {
    uVar25 = *(undefined8 *)(param_1 + 0x2e0);
    *(undefined1 *)(param_1 + 0x300) = 0;
    *(undefined8 *)(param_1 + 0x2f8) = *(undefined8 *)(param_1 + 0x2e8);
    *(undefined8 *)(param_1 + 0x2f0) = uVar25;
  }
  if (0 < param_2) {
    fStack_254 = SUB84(&fStack_1f0,0);
    iVar22 = 0;
    fVar31 = (float)param_2;
    fVar24 = 0.0;
    fStack_23c = (float)uVar25;
    fStack_250 = fStack_254;
    fStack_24c = fStack_254;
    fStack_238 = fStack_23c;
    fStack_234 = fStack_23c;
    fStack_230 = fStack_254;
    fStack_22c = fStack_254;
    fStack_228 = fStack_254;
    fStack_224 = fStack_254;
code_r0x024cbf20:
    iVar12 = *(int *)(lVar18 + 0x1d0);
    if (iVar12 < 1) {
      return;
    }
    uVar19 = *(uint *)(lVar18 + 0x1f0);
    iVar13 = 0;
    do {
      if ((*(uint *)(*(long *)(lVar18 + 0x1e0) + (long)((int)uVar19 >> 5) * 4) &
          1 << (ulong)(uVar19 & 0x1f)) == 0) {
        uVar26 = memset(*(long *)(lVar18 + 0x1b8) +
                                 (ulong)(*(int *)(lVar18 + 0x1c8) * uVar19),0);
        uVar10 = (int)*(uint *)(lVar18 + 0x1f0) >> 5;
        uVar15 = -(ulong)(uVar10 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar10 << 2;
        *(uint *)(*(long *)(lVar18 + 0x1e0) + uVar15) =
             *(uint *)(*(long *)(lVar18 + 0x1e0) + uVar15) |
             1 << (ulong)(*(uint *)(lVar18 + 0x1f0) & 0x1f);
        iVar12 = *(int *)(lVar18 + 0x1d0);
        uVar10 = 0;
        if (*(int *)(lVar18 + 0x1f0) + 1 < iVar12) {
          uVar10 = *(int *)(lVar18 + 0x1f0) + 1;
        }
        *(uint *)(lVar18 + 0x1f0) = uVar10;
        fVar39 = _UNK_027f7cb4;
        fVar44 = _UNK_027f7cb0;
        fVar35 = _UNK_027f7cac;
        fVar42 = _UNK_027f7ca8;
        fVar43 = _UNK_027f7ca4;
        fVar36 = _UNK_027ebe0c;
        fVar30 = _UNK_027ebe04;
        fVar32 = _UNK_027ebe00;
        fVar34 = _UNK_027ebdfc;
        fVar33 = _UNK_027ebdf8;
        fVar27 = _UNK_027ebdf4;
        fVar23 = _UNK_027e3fd0;
        if (uVar19 != 0xffffffff) goto code_r0x024ca074;
      }
      else {
        uVar10 = 0;
        if ((int)(uVar19 + 1) < iVar12) {
          uVar10 = uVar19 + 1;
        }
        *(uint *)(lVar18 + 0x1f0) = uVar10;
      }
      uVar19 = uVar10;
      iVar13 = iVar13 + 1;
      if (iVar12 <= iVar13) {
        return;
      }
    } while( true );
  }
code_r0x024cbf34:
  if ((bVar4 >> 3 & 1) != 0) {
    uVar8 = *(undefined4 *)((long)puVar17 + 0x1c);
    uVar3 = *(undefined4 *)((long)puVar17 + 0x2c);
    *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)((long)puVar17 + 0xc);
    *(undefined4 *)(param_1 + 0x2f4) = uVar8;
    *(undefined4 *)(param_1 + 0x2f8) = uVar3;
    *(undefined4 *)(param_1 + 0x2fc) = 0x3f800000;
  }
  return;
code_r0x024ca074:
  lVar14 = *(long *)(*(long *)(param_1 + 0x1b8) + 0x1b8);
  if (0xf < *(byte *)(param_1 + 0x2cc)) goto code_r0x024cb14c;
  fVar29 = *(float *)(param_1 + 0x28c);
  switch(*(byte *)(param_1 + 0x2cc)) {
  case 0:
    uStack_f8 = *(long *)(PTR__ZN4Aska6Vector10zeroVectorE_02cc0768 + 8);
    uVar26 = *(ulong *)PTR__ZN4Aska6Vector10zeroVectorE_02cc0768;
    uStack_100 = uVar26;
    break;
  case 1:
    uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
    fVar23 = (float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0;
    *(uint *)(param_1 + 0x198) = uVar10;
    if (fVar29 == 0.0) {
      uVar10 = uVar10 * 0x19660d + 0x3c6ef35f;
      uVar11 = uVar10 * 0x19660d + 0x3c6ef35f;
      fVar33 = (float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0;
      *(uint *)(param_1 + 0x198) = uVar11;
      fVar27 = (float)(uVar11 & 0x7fffff | 0x3f800000) + -1.0;
    }
    else {
      fVar23 = (float)expf(-(fVar29 * fVar23 * fVar23));
      uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
      fVar23 = 1.0 - fVar23;
      fVar27 = (float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0;
      *(uint *)(param_1 + 0x198) = uVar10;
      fVar33 = (float)expf(-(fVar29 * fVar27 * fVar27));
      uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
      fVar33 = 1.0 - fVar33;
      fVar27 = (float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0;
      *(uint *)(param_1 + 0x198) = uVar10;
      fVar27 = (float)expf(-(fVar29 * fVar27 * fVar27));
      fVar27 = 1.0 - fVar27;
    }
    uVar10 = *(int *)PTR__ZN4Aska26g_uiLowPrecisionRandomSeedE_02cbb068 * 0x19660d + 0x3c6ef35f;
    uVar11 = uVar10 * 0x19660d + 0x3c6ef35f;
    uVar6 = uVar11 * 0x19660d + 0x3c6ef35f;
    *(uint *)PTR__ZN4Aska26g_uiLowPrecisionRandomSeedE_02cbb068 = uVar6;
    if ((uVar10 & 0x8000) != 0) {
      fVar23 = -fVar23;
    }
    fVar23 = *(float *)(param_1 + 0x220) * fVar23;
    uVar26 = (ulong)(uint)fVar23;
    if ((uVar11 & 0x8000) != 0) {
      fVar33 = -fVar33;
    }
    uStack_100 = CONCAT44(*(float *)(param_1 + 0x224) * fVar33,fVar23);
    if ((uVar6 & 0x8000) != 0) {
      fVar27 = -fVar27;
    }
    uStack_f8 = CONCAT44(uStack_f8._4_4_,*(float *)(param_1 + 0x228) * fVar27);
    break;
  default:
    uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
    fVar38 = (float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0;
    *(uint *)(param_1 + 0x198) = uVar10;
    if (fVar29 != 0.0) {
      fVar38 = (float)expf(-(fVar29 * fVar38 * fVar38));
      uVar10 = *(uint *)(param_1 + 0x198);
      fVar38 = 1.0 - fVar38;
    }
    fVar39 = _UNK_027f7cb4;
    fVar44 = _UNK_027f7cb0;
    fVar35 = _UNK_027f7cac;
    fVar42 = _UNK_027f7ca8;
    fVar43 = _UNK_027f7ca4;
    fVar36 = _UNK_027ebe0c;
    fVar30 = _UNK_027ebe04;
    fVar32 = _UNK_027ebe00;
    fVar34 = _UNK_027ebdfc;
    fVar33 = _UNK_027ebdf8;
    fVar27 = _UNK_027ebdf4;
    fVar23 = _UNK_027e3fd0;
    uVar10 = uVar10 * 0x19660d + 0x3c6ef35f;
    fVar29 = (float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0;
    fVar28 = (fVar29 + fVar29) * _UNK_027e3fd0;
    iVar12 = (int)(fVar28 * _UNK_027ebdf4);
    fVar37 = *(float *)(param_1 + 0x328) + fVar38 * (_UNK_0295c574 - *(float *)(param_1 + 0x328));
    fVar28 = fVar28 - (float)iVar12 * _UNK_027e3fd0;
    fVar38 = fVar28 * fVar28;
    fVar29 = (float)(iVar12 << 0x1f | 0x3f800000);
    fVar40 = fVar29 * _UNK_027ebe0c +
             fVar38 * fVar29 *
             (fVar38 * (fVar38 * (fVar38 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
             _UNK_027ebe04);
    fVar29 = fVar28 * fVar29 *
             (fVar38 * (fVar38 * (fVar38 * (fVar38 * _UNK_027f7ca4 + _UNK_027f7ca8) + _UNK_027f7cac)
                       + _UNK_027f7cb0) + _UNK_027f7cb4);
    fVar28 = *(float *)(param_1 + 0x224);
    uVar10 = uVar10 * 0x19660d + 0x3c6ef35f;
    fVar38 = fVar37 * *(float *)(param_1 + 0x220);
    *(uint *)(param_1 + 0x198) = uVar10;
    goto code_r0x024ca350;
  case 3:
  case 6:
    uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
    uVar11 = uVar10 * 0x19660d + 0x3c6ef35f;
    fVar38 = (float)(uVar11 & 0x7fffff | 0x3f800000) + -1.0;
    fVar37 = fVar29 * ((float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0) + 1.0 + fVar29 * -0.5;
    fVar38 = (fVar38 + fVar38) * _UNK_027e3fd0;
    iVar12 = (int)(fVar38 * _UNK_027ebdf4);
    fVar38 = fVar38 - (float)iVar12 * _UNK_027e3fd0;
    fVar28 = fVar38 * fVar38;
    fVar29 = (float)(iVar12 << 0x1f | 0x3f800000);
    fVar40 = fVar29 * _UNK_027ebe0c +
             fVar28 * fVar29 *
             (fVar28 * (fVar28 * (fVar28 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
             _UNK_027ebe04);
    fVar29 = fVar38 * fVar29 *
             (fVar28 * (fVar28 * (fVar28 * (fVar28 * _UNK_027f7ca4 + _UNK_027f7ca8) + _UNK_027f7cac)
                       + _UNK_027f7cb0) + _UNK_027f7cb4);
    fVar28 = *(float *)(param_1 + 0x224);
    uVar10 = uVar11 * 0x19660d + 0x3c6ef35f;
    *(uint *)(param_1 + 0x198) = uVar10;
    fVar38 = *(float *)(param_1 + 0x220) * fVar37;
code_r0x024ca350:
    fVar38 = fVar38 * fVar29;
    uVar26 = (ulong)(uint)fVar38;
    if (fVar28 == 0.0) {
      uStack_100 = (ulong)(uint)fVar38;
      fVar23 = fVar40 * fVar37 * *(float *)(param_1 + 0x228);
    }
    else {
      fVar29 = ((float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0) * fVar23;
      iVar12 = (int)(fVar29 * fVar27);
      fVar29 = fVar29 - (float)iVar12 * fVar23;
      fVar41 = fVar29 * fVar29;
      fVar27 = (float)(iVar12 << 0x1f | 0x3f800000);
      fVar23 = fVar27 * fVar36 +
               fVar41 * fVar27 * (fVar41 * (fVar41 * (fVar41 * fVar33 + fVar34) + fVar32) + fVar30);
      fVar38 = fVar23 * fVar38;
      uVar26 = (ulong)(uint)fVar38;
      uStack_100 = CONCAT44(fVar29 * fVar27 *
                            (fVar41 * (fVar41 * (fVar41 * (fVar41 * fVar43 + fVar42) + fVar35) +
                                      fVar44) + fVar39) * fVar37 * fVar28,fVar38);
      fVar23 = fVar23 * fVar40 * fVar37 * *(float *)(param_1 + 0x228);
    }
    goto code_r0x024cb148;
  case 4:
    uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
    uVar11 = uVar10 * 0x19660d + 0x3c6ef35f;
    fVar33 = *(float *)(param_1 + 0x224) * ((float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0);
    uVar10 = uVar11 * 0x19660d + 0x3c6ef35f;
    fVar23 = (float)(uVar11 & 0x7fffff | 0x3f800000) + -1.0;
    fVar27 = (fVar23 + fVar23) * _UNK_027e3fd0;
    fVar23 = (float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0;
    *(uint *)(param_1 + 0x198) = uVar10;
    if (fVar29 != 0.0) {
      fVar23 = (float)expf(-(fVar29 * fVar23 * fVar23));
      fVar23 = 1.0 - fVar23;
    }
    fVar34 = (float)tanf(fVar23 * *(float *)(param_1 + 0x220) * 0.5);
    iVar12 = (int)(fVar27 * _UNK_027ebdf4);
    fVar27 = fVar27 + (float)iVar12 * _UNK_027edb30;
    fVar32 = fVar27 * fVar27;
    fVar23 = (float)(iVar12 << 0x1f | 0x3f800000);
    fVar34 = fVar33 * fVar34;
    fVar27 = fVar27 * fVar23 *
             (fVar32 * (fVar32 * (fVar32 * (fVar32 * _UNK_027f7ca4 + _UNK_027f7ca8) + _UNK_027f7cac)
                       + _UNK_027f7cb0) + _UNK_027f7cb4) * fVar34;
    uVar26 = (ulong)(uint)fVar27;
    uStack_100 = CONCAT44(fVar33,fVar27);
    uStack_f8 = CONCAT44(uStack_f8._4_4_,
                         (fVar23 * _UNK_027ebe0c +
                         fVar32 * fVar23 *
                         (fVar32 * (fVar32 * (fVar32 * _UNK_027ebdf8 + _UNK_027ebdfc) +
                                   _UNK_027ebe00) + _UNK_027ebe04)) * fVar34);
    break;
  case 7:
  case 9:
    uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
    fVar23 = (float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0;
    *(uint *)(param_1 + 0x198) = uVar10;
    if (fVar29 != 0.0) {
      fVar23 = (float)expf(-(fVar29 * fVar23 * fVar23));
      uVar10 = *(uint *)(param_1 + 0x198);
      fVar23 = 1.0 - fVar23;
    }
    uVar11 = uVar10 * 0x19660d + 0x3c6ef35f;
    fVar34 = *(float *)(param_1 + 0x328) + fVar23 * (_UNK_0295c574 - *(float *)(param_1 + 0x328));
    fVar23 = (float)(uVar11 & 0x7fffff | 0x3f800000) + -1.0;
    fVar33 = (fVar23 + fVar23) * _UNK_027e3fd0;
    iVar12 = (int)(fVar33 * _UNK_027ebdf4);
    fVar33 = fVar33 - (float)iVar12 * _UNK_027e3fd0;
    fVar32 = fVar33 * fVar33;
    fVar27 = (float)(iVar12 << 0x1f | 0x3f800000);
    fVar30 = *(float *)(param_1 + 0x224);
    fVar23 = fVar27 * _UNK_027ebe0c +
             fVar32 * fVar27 *
             (fVar32 * (fVar32 * (fVar32 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
             _UNK_027ebe04);
    fVar27 = fVar34 * *(float *)(param_1 + 0x220) *
             fVar33 * fVar27 *
             (fVar32 * (fVar32 * (fVar32 * (fVar32 * _UNK_027f7ca4 + _UNK_027f7ca8) + _UNK_027f7cac)
                       + _UNK_027f7cb0) + _UNK_027f7cb4);
    goto code_r0x024ca6a4;
  case 8:
  case 10:
    uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
    uVar11 = uVar10 * 0x19660d + 0x3c6ef35f;
    fVar34 = fVar29 * ((float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0) + 1.0 + fVar29 * -0.5;
    fVar23 = (float)(uVar11 & 0x7fffff | 0x3f800000) + -1.0;
    fVar33 = (fVar23 + fVar23) * _UNK_027e3fd0;
    iVar12 = (int)(fVar33 * _UNK_027ebdf4);
    fVar33 = fVar33 - (float)iVar12 * _UNK_027e3fd0;
    fVar32 = fVar33 * fVar33;
    fVar27 = (float)(iVar12 << 0x1f | 0x3f800000);
    fVar30 = *(float *)(param_1 + 0x224);
    fVar23 = fVar27 * _UNK_027ebe0c +
             fVar32 * fVar27 *
             (fVar32 * (fVar32 * (fVar32 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
             _UNK_027ebe04);
    fVar27 = *(float *)(param_1 + 0x220) * fVar34 *
             fVar33 * fVar27 *
             (fVar32 * (fVar32 * (fVar32 * (fVar32 * _UNK_027f7ca4 + _UNK_027f7ca8) + _UNK_027f7cac)
                       + _UNK_027f7cb0) + _UNK_027f7cb4);
code_r0x024ca6a4:
    uVar26 = (ulong)(uint)fVar27;
    *(uint *)(param_1 + 0x198) = uVar11;
    if (fVar30 == 0.0) {
      fVar30 = 0.0;
    }
    else {
      uVar10 = uVar11 * 0x19660d + 0x3c6ef35f;
      fVar33 = fVar30 * ((float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0);
      fVar30 = (fVar33 + fVar33) - fVar30;
      *(uint *)(param_1 + 0x198) = uVar10;
    }
    uStack_100 = CONCAT44(fVar30,fVar27);
    fVar23 = fVar23 * fVar34 * *(float *)(param_1 + 0x228);
    goto code_r0x024cb148;
  case 0xb:
    if (*(long *)(param_1 + 0x1c8) != 0) {
      puVar17 = (undefined8 *)param_4[4];
      if ((*(int *)(*(long *)(param_1 + 0x1c8) + 0x378) < 0) &&
         (lVar9 = Aska::MeshGeneratorManager::FindMeshGenerator(Aska::AofObject const*)(*(undefined8 *)
                                   PTR__ZN4Aska6Global23m_pMeshGeneratorManagerE_02cc2bc0),
         lVar9 != 0)) {
        uVar26 = Aska::Random(unsigned int)(*(undefined4 *)(lVar9 + 0x30));
        puVar1 = (undefined8 *)
                 (*(long *)(lVar9 + (ulong)*(byte *)(lVar9 + 0x98) * 8 + 0x58) +
                 (uVar26 & 0xffffffff) * 0x40);
        uVar25 = *puVar1;
        puVar17[1] = puVar1[1];
        *puVar17 = uVar25;
        uVar25 = puVar1[2];
        puVar17[3] = puVar1[3];
        puVar17[2] = uVar25;
        lVar9 = _UNK_027dbb38;
        uVar26 = _UNK_027dbb30;
        uVar25 = puVar1[4];
        puVar17[5] = puVar1[5];
        puVar17[4] = uVar25;
        puVar17[7] = lVar9;
        puVar17[6] = uVar26;
      }
      uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
      fVar23 = (float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0;
      *(uint *)(param_1 + 0x198) = uVar10;
      if (fVar29 != 0.0) {
        fVar23 = (float)expf(-(fVar29 * fVar23 * fVar23));
        fVar23 = 1.0 - fVar23;
      }
      uStack_210 = 0;
      lStack_208 = 0;
      uStack_110 = 0;
      uStack_108 = 0;
      Aska::AofObject::GetRandomVertexPosAndNormal(Aska::Vector*, Aska::Vector*) const(*(undefined8 *)(param_1 + 0x1c8),&uStack_210,&uStack_110);
      fVar38 = _UNK_027f7cb4;
      fVar29 = _UNK_027f7cb0;
      fVar39 = _UNK_027f7cac;
      fVar44 = _UNK_027f7ca8;
      fVar35 = _UNK_027f7ca4;
      fVar42 = _UNK_027ebe0c;
      fVar43 = _UNK_027ebe04;
      fVar36 = _UNK_027ebe00;
      fVar30 = _UNK_027ebdfc;
      fVar32 = _UNK_027ebdf8;
      fVar34 = _UNK_027ebdf4;
      fVar33 = _UNK_027e3fd0;
      uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
      fVar27 = (float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0;
      fVar28 = (fVar27 + fVar27) * _UNK_027e3fd0;
      iVar12 = (int)(fVar28 * _UNK_027ebdf4);
      fVar28 = fVar28 - (float)iVar12 * _UNK_027e3fd0;
      fVar37 = fVar28 * fVar28;
      fVar27 = (float)(iVar12 << 0x1f | 0x3f800000);
      fVar40 = fVar37 * (fVar37 * (fVar37 * (fVar37 * _UNK_027f7ca4 + _UNK_027f7ca8) + _UNK_027f7cac
                                  ) + _UNK_027f7cb0) + _UNK_027f7cb4;
      uVar10 = uVar10 * 0x19660d + 0x3c6ef35f;
      fVar37 = fVar27 * _UNK_027ebe0c +
               fVar37 * fVar27 *
               (fVar37 * (fVar37 * (fVar37 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
               _UNK_027ebe04);
      *(uint *)(param_1 + 0x198) = uVar10;
      fVar27 = fVar23 * *(float *)(param_1 + 0x220) * fVar28 * fVar27 * fVar40;
      if (*(float *)(param_1 + 0x224) == 0.0) {
        fVar33 = *(float *)(param_1 + 0x1e8);
        fVar27 = fVar27 + (float)uStack_210 + (float)uStack_110 * fVar33;
        uStack_100 = CONCAT44(uStack_210._4_4_ + uStack_110._4_4_ * fVar33,fVar27);
        fVar23 = fVar23 * *(float *)(param_1 + 0x228);
      }
      else {
        fVar28 = ((float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0) * fVar33;
        iVar12 = (int)(fVar28 * fVar34);
        fVar28 = fVar28 - (float)iVar12 * fVar33;
        fVar40 = fVar28 * fVar28;
        fVar34 = (float)(iVar12 << 0x1f | 0x3f800000);
        fVar33 = *(float *)(param_1 + 0x1e8);
        fVar32 = fVar34 * fVar42 +
                 fVar40 * fVar34 *
                 (fVar40 * (fVar40 * (fVar40 * fVar32 + fVar30) + fVar36) + fVar43);
        fVar27 = fVar32 * fVar27 + (float)uStack_210 + (float)uStack_110 * fVar33;
        uStack_100 = CONCAT44(uStack_210._4_4_ +
                              fVar28 * fVar34 *
                              (fVar40 * (fVar40 * (fVar40 * (fVar40 * fVar35 + fVar44) + fVar39) +
                                        fVar29) + fVar38) * fVar23 * *(float *)(param_1 + 0x224) +
                              uStack_110._4_4_ * fVar33,fVar27);
        fVar23 = fVar37 * fVar23 * *(float *)(param_1 + 0x228);
        fVar37 = fVar32;
      }
      uVar26 = (ulong)(uint)fVar27;
      uStack_f8 = CONCAT44(uStack_f8._4_4_,
                           fVar37 * fVar23 + (float)lStack_208 + (float)uStack_108 * fVar33);
    }
    break;
  case 0xc:
    if (*(long *)(param_1 + 0x1c8) != 0) {
      puVar17 = (undefined8 *)param_4[4];
      lStack_208 = _UNK_027dbb38;
      uStack_210 = _UNK_027dbb30;
      uVar8 = Aska::AofObject::GetVertexPosition(int, Aska::Vector*) const(*(long *)(param_1 + 0x1c8),*(undefined4 *)(param_1 + 0x298),
                              &uStack_210);
      *(undefined4 *)(param_1 + 0x298) = uVar8;
      uStack_f8 = lStack_208;
      uStack_100 = uStack_210;
      uVar26 = uStack_210;
    }
    break;
  case 0xd:
    uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
    fVar23 = (float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0;
    *(uint *)(param_1 + 0x198) = uVar10;
    if (fVar29 != 0.0) {
      fVar23 = (float)expf(-(fVar29 * fVar23 * fVar23));
      uVar10 = *(uint *)(param_1 + 0x198);
      fVar23 = 1.0 - fVar23;
    }
    fVar30 = _UNK_027f7ca8;
    fVar32 = _UNK_027f7ca4;
    fVar34 = _UNK_027ebdf4;
    fVar33 = _UNK_027e3fd0;
    uVar10 = uVar10 * 0x19660d + 0x3c6ef35f;
    uVar11 = uVar10 * 0x19660d + 0x3c6ef35f;
    fVar27 = (float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0;
    fVar36 = (fVar27 + fVar27) * _UNK_027e3fd0;
    fVar27 = (float)(uVar11 & 0x7fffff | 0x3f800000) + -1.0;
    fVar43 = fVar36 * _UNK_027ebdf4;
    fVar42 = _UNK_0295c574 - *(float *)(param_1 + 0x328);
    *(uint *)(param_1 + 0x198) = uVar11;
    iVar13 = (int)fVar43;
    fVar43 = (fVar27 + fVar27) * fVar33;
    fVar27 = (float)(iVar13 << 0x1f | 0x3f800000);
    fVar42 = *(float *)(param_1 + 0x328) + fVar23 * fVar42;
    iVar12 = (int)(fVar43 * fVar34);
    fVar36 = fVar36 - (float)iVar13 * fVar33;
    fVar35 = fVar36 * fVar36;
    fVar43 = fVar43 - (float)iVar12 * fVar33;
    fVar44 = fVar43 * fVar43;
    fVar33 = (float)(iVar12 << 0x1f | 0x3f800000);
    fVar23 = fVar33 * _UNK_027ebe0c +
             fVar44 * fVar33 *
             (fVar44 * (fVar44 * (fVar44 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
             _UNK_027ebe04);
    fVar34 = fVar42 * *(float *)(param_1 + 0x220) *
             fVar36 * fVar27 *
             (fVar35 * (fVar35 * (fVar35 * (fVar35 * fVar32 + fVar30) + _UNK_027f7cac) +
                       _UNK_027f7cb0) + _UNK_027f7cb4) * fVar23;
    uVar26 = (ulong)(uint)fVar34;
    uStack_100 = CONCAT44(fVar42 * *(float *)(param_1 + 0x224) *
                          fVar43 * fVar33 *
                          (fVar44 * (fVar44 * (fVar44 * (fVar44 * fVar32 + fVar30) + _UNK_027f7cac)
                                    + _UNK_027f7cb0) + _UNK_027f7cb4),fVar34);
    fVar23 = fVar42 * *(float *)(param_1 + 0x228) *
             (fVar27 * _UNK_027ebe0c +
             fVar35 * fVar27 *
             (fVar35 * (fVar35 * (fVar35 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
             _UNK_027ebe04)) * fVar23;
    goto code_r0x024cb148;
  case 0xe:
    uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
    uVar11 = uVar10 * 0x19660d + 0x3c6ef35f;
    uVar6 = uVar11 * 0x19660d + 0x3c6ef35f;
    fVar33 = (float)(uVar11 & 0x7fffff | 0x3f800000) + -1.0;
    fVar32 = (fVar33 + fVar33) * _UNK_027e3fd0;
    fVar33 = (float)(uVar6 & 0x7fffff | 0x3f800000) + -1.0;
    fVar34 = fVar32 * _UNK_027ebdf4;
    fVar30 = fVar29 * ((float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0) + 1.0 + fVar29 * -0.5;
    *(uint *)(param_1 + 0x198) = uVar6;
    iVar13 = (int)fVar34;
    fVar34 = (fVar33 + fVar33) * fVar23;
    fVar33 = (float)(iVar13 << 0x1f | 0x3f800000);
    iVar12 = (int)(fVar34 * fVar27);
    fVar32 = fVar32 - (float)iVar13 * fVar23;
    fVar34 = fVar34 - (float)iVar12 * fVar23;
    fVar36 = fVar32 * fVar32;
    fVar42 = fVar34 * fVar34;
    fVar27 = (float)(iVar12 << 0x1f | 0x3f800000);
    fVar23 = fVar27 * _UNK_027ebe0c +
             fVar42 * fVar27 *
             (fVar42 * (fVar42 * (fVar42 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
             _UNK_027ebe04);
    fVar32 = *(float *)(param_1 + 0x220) * fVar30 *
             fVar32 * fVar33 *
             (fVar36 * (fVar36 * (fVar36 * (fVar36 * fVar43 + _UNK_027f7ca8) + _UNK_027f7cac) +
                       _UNK_027f7cb0) + _UNK_027f7cb4) * fVar23;
    uVar26 = (ulong)(uint)fVar32;
    uStack_100 = CONCAT44(*(float *)(param_1 + 0x224) * fVar30 *
                          fVar34 * fVar27 *
                          (fVar42 * (fVar42 * (fVar42 * (fVar42 * fVar43 + _UNK_027f7ca8) +
                                              _UNK_027f7cac) + _UNK_027f7cb0) + _UNK_027f7cb4),
                          fVar32);
    fVar23 = *(float *)(param_1 + 0x228) * fVar30 *
             (fVar33 * _UNK_027ebe0c +
             fVar36 * fVar33 *
             (fVar36 * (fVar36 * (fVar36 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
             _UNK_027ebe04)) * fVar23;
    goto code_r0x024cb148;
  case 0xf:
    uVar10 = *(uint *)(param_1 + 0x2ac);
    uVar11 = 0;
    if (uVar10 != 0) {
      uVar11 = uVar19 / uVar10;
    }
    fVar27 = (_UNK_027edb34 / (float)uVar10) * (float)((uVar19 - uVar11 * uVar10) + 1);
    iVar12 = (int)(fVar27 * _UNK_027ebdf4);
    fVar27 = fVar27 + (float)iVar12 * _UNK_027edb30;
    fVar33 = fVar27 * fVar27;
    fVar23 = (float)(iVar12 << 0x1f | 0x3f800000);
    fVar27 = *(float *)(param_1 + 0x2b0) *
             fVar27 * fVar23 *
             (fVar33 * (fVar33 * (fVar33 * (fVar33 * _UNK_027f7ca4 + _UNK_027f7ca8) + _UNK_027f7cac)
                       + _UNK_027f7cb0) + _UNK_027f7cb4);
    uVar26 = (ulong)(uint)fVar27;
    uStack_f8 = (ulong)*(uint *)(PTR__ZN4Aska6Vector10zeroVectorE_02cc0768 + 0xc) << 0x20;
    fVar23 = *(float *)(param_1 + 0x2b0) *
             (fVar23 * _UNK_027ebe0c +
             fVar33 * fVar23 *
             (fVar33 * (fVar33 * (fVar33 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
             _UNK_027ebe04));
    uStack_100 = CONCAT44(*(undefined4 *)(PTR__ZN4Aska6Vector10zeroVectorE_02cc0768 + 4),fVar27);
code_r0x024cb148:
    uStack_f8 = CONCAT44(uStack_f8._4_4_,fVar23);
  }
code_r0x024cb14c:
  switch(*(undefined1 *)(param_1 + 0x2cd)) {
  case 0:
    fStack_224 = *(float *)(param_1 + 0x230);
    fStack_234 = *(float *)(param_1 + 0x234);
    fStack_23c = *(float *)(param_1 + 0x238);
    fStack_238 = *(float *)(param_1 + 0x23c);
    bVar4 = *(byte *)((long)param_3 + 0xe4);
    fStack_230 = fStack_238;
    fStack_22c = fStack_23c;
    fStack_228 = fStack_234;
    uVar26 = uStack_100;
    unaff_s9 = fStack_224;
    goto joined_r0x024cb38c;
  case 1:
    uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
    uVar11 = uVar10 * 0x19660d + 0x3c6ef35f;
    fStack_224 = (*(float *)(param_1 + 0x230) +
                 *(float *)(param_1 + 0x240) * ((float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0)) -
                 *(float *)(param_1 + 0x240) * 0.5;
    uVar10 = uVar11 * 0x19660d + 0x3c6ef35f;
    fStack_234 = (*(float *)(param_1 + 0x234) +
                 *(float *)(param_1 + 0x244) * ((float)(uVar11 & 0x7fffff | 0x3f800000) + -1.0)) -
                 *(float *)(param_1 + 0x244) * 0.5;
    uVar11 = uVar10 * 0x19660d + 0x3c6ef35f;
    fStack_23c = (*(float *)(param_1 + 0x238) +
                 *(float *)(param_1 + 0x248) * ((float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0)) -
                 *(float *)(param_1 + 0x248) * 0.5;
    fStack_238 = (*(float *)(param_1 + 0x23c) +
                 *(float *)(param_1 + 0x24c) * ((float)(uVar11 & 0x7fffff | 0x3f800000) + -1.0)) -
                 *(float *)(param_1 + 0x24c) * 0.5;
    *(uint *)(param_1 + 0x198) = uVar11;
    fStack_230 = fStack_238;
    fStack_22c = fStack_23c;
    fStack_228 = fStack_234;
    unaff_s9 = fStack_224;
    break;
  case 2:
    fVar27 = (float)uVar26 * (float)uVar26 + uStack_100._4_4_ * uStack_100._4_4_ +
             (float)uStack_f8 * (float)uStack_f8;
    fVar23 = SQRT(fVar27);
    if (NAN(fVar23)) {
      fVar23 = (float)sqrtf(fVar27);
    }
    fVar23 = fVar23 / *(float *)(param_1 + 0x1f8);
    fStack_224 = *(float *)(param_1 + 0x230) + fVar23 * *(float *)(param_1 + 0x240);
    fStack_234 = *(float *)(param_1 + 0x234) + fVar23 * *(float *)(param_1 + 0x244);
    fStack_23c = *(float *)(param_1 + 0x238) + fVar23 * *(float *)(param_1 + 0x248);
    fStack_238 = *(float *)(param_1 + 0x23c) + fVar23 * *(float *)(param_1 + 0x24c);
    fStack_230 = fStack_238;
    fStack_22c = fStack_23c;
    fStack_228 = fStack_234;
    unaff_s9 = fStack_224;
    break;
  case 3:
    uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
    fVar23 = (float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0;
    fStack_224 = (*(float *)(param_1 + 0x230) + *(float *)(param_1 + 0x240) * fVar23) -
                 *(float *)(param_1 + 0x240) * 0.5;
    fStack_234 = (*(float *)(param_1 + 0x234) + *(float *)(param_1 + 0x244) * fVar23) -
                 *(float *)(param_1 + 0x244) * 0.5;
    fStack_23c = (*(float *)(param_1 + 0x238) + fVar23 * *(float *)(param_1 + 0x248)) -
                 *(float *)(param_1 + 0x248) * 0.5;
    fStack_238 = (*(float *)(param_1 + 0x23c) + fVar23 * *(float *)(param_1 + 0x24c)) -
                 *(float *)(param_1 + 0x24c) * 0.5;
    *(uint *)(param_1 + 0x198) = uVar10;
    fStack_230 = fStack_238;
    fStack_22c = fStack_23c;
    fStack_228 = fStack_234;
    unaff_s9 = fStack_224;
  }
  bVar4 = *(byte *)((long)param_3 + 0xe4);
  uVar26 = uStack_100;
joined_r0x024cb38c:
  if ((bVar4 >> 3 & 1) != 0) {
    fStack_224 = unaff_s9 * *(float *)(param_3 + 8);
    fStack_234 = fStack_234 * *(float *)((long)param_3 + 0x44);
    fStack_23c = fStack_23c * *(float *)(param_3 + 9);
    fStack_238 = fStack_238 * *(float *)((long)param_3 + 0x4c);
    fStack_230 = fStack_238;
    fStack_22c = fStack_23c;
    fStack_228 = fStack_234;
    unaff_s9 = fStack_224;
  }
  uStack_100 = uVar26;
  if ((*(byte *)(param_1 + 0x214) & 0x18) == 0) goto code_r0x024cb484;
  uStack_100._0_4_ = (float)uVar26;
  uStack_100._4_4_ = (float)(uVar26 >> 0x20);
  if (*(char *)(param_1 + 0x212) == '\x01') {
    fVar27 = *(float *)(param_1 + 500) * *(float *)(param_1 + 500);
    fVar23 = (float)uStack_100 * (float)uStack_100 + uStack_100._4_4_ * uStack_100._4_4_ +
             (float)uStack_f8 * (float)uStack_f8 + fVar27;
code_r0x024cb45c:
    fVar33 = fVar27 / fVar23;
    uVar26 = uStack_100;
  }
  else {
    fVar33 = 0.0;
    if (*(char *)(param_1 + 0x212) == '\0') {
      fVar27 = (float)uStack_100 * (float)uStack_100 + uStack_100._4_4_ * uStack_100._4_4_ +
               (float)uStack_f8 * (float)uStack_f8;
      fVar23 = SQRT(fVar27);
      if (NAN(fVar23)) {
        fVar23 = (float)sqrtf(fVar27);
      }
      fVar27 = *(float *)(param_1 + 500);
      fVar33 = 1.0;
      fVar23 = fVar23 + fVar27;
      uVar26 = uStack_100;
      if (fVar23 != 0.0) goto code_r0x024cb45c;
    }
  }
  uStack_100 = uVar26;
  uVar5 = *(ushort *)(param_1 + 0x214);
  if ((uVar5 >> 5 & 1) != 0) {
    fVar23 = uStack_100._4_4_;
    fVar34 = (float)uStack_f8 * (float)uStack_f8 +
             (float)uStack_100 * (float)uStack_100 + uStack_100._4_4_ * uStack_100._4_4_;
    fVar27 = SQRT(fVar34);
    if (NAN(fVar27)) {
      fVar27 = (float)sqrtf(fVar34);
    }
    if (_UNK_027e519c <= fVar27) {
      fVar23 = (1.0 / fVar27) * fVar23;
    }
    if (fVar23 <= 0.0) {
      fVar23 = 0.0;
    }
    uVar5 = *(ushort *)(param_1 + 0x214);
    fVar27 = *(float *)(param_1 + 0x1f0) * (fVar23 * fVar23 - *(float *)(param_1 + 0x1ec));
    fVar34 = (float)NEON_fminnm(fVar27,0x3f800000);
    fVar23 = 0.0;
    if (0.0 <= fVar27) {
      fVar23 = fVar34;
    }
    fVar33 = fVar33 * fVar23;
  }
  if ((uVar5 >> 3 & 1) != 0) {
    fStack_224 = fVar33 * fStack_224;
    fStack_234 = fVar33 * fStack_228;
    fStack_23c = fVar33 * fStack_22c;
    fStack_22c = fStack_23c;
    fStack_228 = fStack_234;
    unaff_s9 = fStack_224;
  }
  if ((uVar5 >> 4 & 1) != 0) {
    fStack_238 = fVar33 * fStack_230;
    fStack_230 = fStack_238;
  }
code_r0x024cb484:
  if (*(char *)(param_1 + 0x20e) == '\x01') {
    if (*(char *)(param_1 + 0x2d0) == '\x01') {
      uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
      fStack_254 = *(float *)(param_1 + 0x2b4) +
                   *(float *)(param_1 + 0x2b8) * ((float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0) +
                   *(float *)(param_1 + 0x2b8) * -0.5;
      *(uint *)(param_1 + 0x198) = uVar10;
    }
    else if (*(char *)(param_1 + 0x2d0) == '\0') {
      fStack_254 = *(float *)(param_1 + 0x2b4);
    }
    if (*(char *)(param_1 + 0x2d1) == '\x01') {
      uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
      fStack_250 = *(float *)(param_1 + 700) +
                   *(float *)(param_1 + 0x2c0) * ((float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0) +
                   *(float *)(param_1 + 0x2c0) * -0.5;
      *(uint *)(param_1 + 0x198) = uVar10;
    }
    else if (*(char *)(param_1 + 0x2d1) == '\0') {
      fStack_250 = *(float *)(param_1 + 700);
    }
    if (*(char *)(param_1 + 0x2d2) == '\x01') {
      uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
      fStack_24c = *(float *)(param_1 + 0x2c4) +
                   *(float *)(param_1 + 0x2c8) * ((float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0) +
                   *(float *)(param_1 + 0x2c8) * -0.5;
      *(uint *)(param_1 + 0x198) = uVar10;
    }
    else if (*(char *)(param_1 + 0x2d2) == '\0') {
      fStack_24c = *(float *)(param_1 + 0x2c4);
    }
  }
  uStack_f8 = CONCAT44(0x3f800000,(float)uStack_f8);
  if ((*(byte *)((long)param_3 + 0xe4) & 1) == 0) {
    Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const(&uStack_100,&uStack_110,puVar17);
  }
  else {
    Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const(&uStack_100,&uStack_110,&uStack_e0);
    uStack_110 = CONCAT44(*(float *)((long)param_3 + 0x34) + uStack_110._4_4_,
                          *(float *)(param_3 + 6) + (float)uStack_110);
    uStack_108 = CONCAT44(uStack_108._4_4_,*(float *)(param_3 + 7) + (float)uStack_108);
  }
  if ((*(byte *)(param_1 + 0x2ce) & 1) != 0) {
    fVar23 = *(float *)(param_3 + 0x1c);
    fVar27 = *(float *)(param_1 + 0x290);
    uStack_110 = CONCAT44(uStack_110._4_4_ + fVar23 * *(float *)(param_1 + 0x274) * fVar27,
                          (float)uStack_110 + fVar23 * *(float *)(param_1 + 0x270) * fVar27);
    uStack_108 = CONCAT44(uStack_108._4_4_,
                          (float)uStack_108 + fVar23 * *(float *)(param_1 + 0x278) * fVar27);
  }
  if ((*(byte *)(param_1 + 0x2ce) >> 2 & 1) != 0) {
    fVar23 = (float)iVar22;
    uStack_110 = CONCAT44(uStack_110._4_4_ + (*(float *)(param_1 + 0x264) * fVar23) / fVar31,
                          (float)uStack_110 + (*(float *)(param_1 + 0x260) * fVar23) / fVar31);
    uStack_108 = CONCAT44(uStack_108._4_4_,
                          (float)uStack_108 + (*(float *)(param_1 + 0x268) * fVar23) / fVar31);
  }
  pfVar21 = (float *)(lVar14 + (long)(int)uVar19 * 0xd0);
  fVar23 = fVar24;
  if ((iVar22 != 0) && ((*(byte *)(param_1 + 0x2d9) >> 3 & 1) != 0)) {
    fVar34 = (float)uStack_110 - *(float *)(param_1 + 0x2f0);
    fVar32 = uStack_110._4_4_ - *(float *)(param_1 + 0x2f4);
    fVar33 = (float)uStack_108 - *(float *)(param_1 + 0x2f8);
    fVar30 = fVar34 * fVar34 + fVar32 * fVar32 + fVar33 * fVar33;
    fVar27 = SQRT(fVar30);
    if (NAN(fVar27)) {
      fVar27 = (float)sqrtf(fVar30);
    }
    if ((*(float *)(param_1 + 0x2dc) <= fVar27) && (fVar23 = 0.0, fVar24 < fVar27)) {
      fVar23 = SQRT(fVar30);
      if (NAN(fVar23)) {
        fVar23 = (float)sqrtf(fVar30);
      }
      if (_UNK_027e519c <= fVar23) {
        fVar23 = 1.0 / fVar23;
        fVar34 = fVar34 * fVar23;
        fVar32 = fVar32 * fVar23;
        fVar33 = fVar33 * fVar23;
      }
      fVar24 = fVar24 + *(float *)(param_1 + 0x2dc);
      fVar34 = fVar34 * fVar24;
      fVar32 = fVar32 * fVar24;
      fVar33 = fVar33 * fVar24;
      fVar23 = SQRT(fVar33 * fVar33 + fVar34 * fVar34 + fVar32 * fVar32);
      uStack_110 = CONCAT44(*(float *)(param_1 + 0x2f4) + fVar32,
                            *(float *)(param_1 + 0x2f0) + fVar34);
      uStack_108 = CONCAT44(*(undefined4 *)(param_1 + 0x2fc),fVar33 + *(float *)(param_1 + 0x2f8));
      if (NAN(fVar23)) {
        fVar23 = (float)sqrtf();
      }
    }
  }
  fVar24 = fVar23;
  Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const(&uStack_110,&fStack_120,lVar20);
  bStack_12c = 0;
  fStack_1ec = 0.0;
  fStack_1f0 = 0.0;
  fStack_1e8 = 0.0;
  if (((*(byte *)(param_1 + 0x214) >> 1 & 1) != 0) && (*(long *)(param_1 + 0x1d0) != 0)) {
    bStack_12c = *(byte *)(param_1 + 0x20c);
    if ((bStack_12c & 1) != 0) {
      uStack_1d8 = uStack_108;
      uStack_1e0 = uStack_110;
    }
    if ((bStack_12c >> 3 & 1) != 0) {
      fStack_1d0 = fStack_224;
      fStack_1cc = fStack_228;
      fStack_1c8 = fStack_22c;
      fStack_1c4 = fStack_230;
    }
  }
  *pfVar21 = fStack_120;
  pfVar21[1] = fStack_11c;
  pfVar21[2] = fStack_118;
  pfVar21[5] = fStack_250;
  pfVar21[6] = fStack_24c;
  pfVar21[8] = fStack_224;
  pfVar21[9] = fStack_228;
  pfVar21[10] = fStack_22c;
  pfVar21[3] = fStack_114;
  pfVar21[0xb] = fStack_230;
  pfVar21[4] = fStack_254;
  *param_3 = (long)puVar17;
  param_3[1] = lVar20;
  param_3[2] = (long)auStack_f0;
  param_3[0x1b] = uStack_f8;
  param_3[0x1a] = uStack_100;
  pfVar21[3] = 0.0;
  pfVar21[7] = *(float *)(lVar18 + 0xa0c);
  fVar23 = *(float *)(lVar18 + 0xa10);
  uVar10 = *(int *)(param_1 + 0x198) * 0x19660d + 0x3c6ef35f;
  *(uint *)(param_1 + 0x198) = uVar10;
  pfVar21[7] = pfVar21[7] + fVar23 * ((float)(uVar10 & 0x7fffff | 0x3f800000) + -1.0);
  if (*(char *)(lVar18 + 0xa08) != '\0') {
    uVar7 = Aska::Random(unsigned int)();
    *(undefined1 *)(pfVar21 + 0xc) = uVar7;
  }
  lVar14 = *(long *)(lVar18 + 0xa00);
  if (lVar14 != 0) {
    pfVar21[8] = *(float *)(lVar14 + 0x10) + pfVar21[8];
    pfVar21[9] = *(float *)(lVar14 + 0x14) + pfVar21[9];
    pfVar21[10] = *(float *)(lVar14 + 0x18) + pfVar21[10];
    pfVar21[0xb] = *(float *)(lVar14 + 0x1c) + pfVar21[0xb];
  }
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::EmitMotion(Aska::ParticleElement<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >*, Aska::IParticleEmitter::EmitContext const*, Aska::IParticleEmitter::EmitContext*, StBoolean<true>)(param_1,pfVar21,param_3,&uStack_210);
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::EmitColorAnimation(Aska::ParticleElement<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >*, Aska::Vector const*, StBoolean<true>)(param_1,pfVar21,&uStack_100);
  Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::EmitTexture(Aska::ParticleElement<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >*, StBoolean<true>)(param_1,pfVar21);
  if (bStack_12c != 0) {
    (**(code **)(**(long **)(param_1 + 0x1d0) + 0x180))
              (*(long **)(param_1 + 0x1d0),*(undefined1 *)(param_1 + 0x20d),&uStack_210);
  }
  lVar14 = (long)(int)uVar19 * 0xd0;
  if (*(char *)(param_1 + 0x2cf) == '\0') {
    if (*(long *)(lVar18 + 0x120) != 0) {
      *(undefined4 *)(*(long *)(lVar18 + 0x1b8) + lVar14 + 0xcc) = *(undefined4 *)(lVar18 + 0x130);
    }
    Aska::ParticleObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >, Aska::DefaultFunctorList>::SetupParticleTails(int, Aska::Vector const*)(lVar18,uVar19,0);
    if (((1 < *(int *)(lVar18 + 0x1d4)) && (*(long *)(lVar18 + 0x148) != 0)) &&
       (*(long *)(lVar18 + 0x158) != 0)) {
      uVar10 = *(int *)(lVar18 + 0x1d4) - 1;
      uVar26 = (ulong)uVar10;
      lVar14 = *(long *)(lVar18 + 0x1b8) + lVar14;
      puVar2 = (undefined2 *)(*(long *)(lVar18 + 0x158) + (ulong)*(uint *)(lVar14 + 0x6c) * 0x10);
      puVar16 = (undefined4 *)
                (*(long *)(lVar18 + 0x1c0) + (long)(int)(uVar10 * uVar19) * 0x70 + 0x50);
      do {
        uVar26 = uVar26 - 1;
        puVar16[-4] = *(undefined4 *)(lVar14 + 0x40);
        puVar16[-3] = *(undefined4 *)(lVar14 + 0x44);
        puVar16[-2] = *(undefined4 *)(lVar14 + 0x48);
        puVar16[-1] = *(undefined4 *)(lVar14 + 0x4c);
        *puVar16 = CONCAT22(*puVar2,puVar2[1]);
        puVar16 = puVar16 + 0x1c;
      } while (uVar26 != 0);
    }
  }
  else if (*(char *)(param_1 + 0x2cf) == '\x01') {
    fStack_1f0 = fStack_1f0 * _UNK_029671ec;
    fStack_1ec = fStack_1ec * _UNK_029671ec;
    fStack_1e8 = fStack_1e8 * _UNK_029671ec;
    fVar23 = *(float *)(PTR__ZN4Aska6Vector10zeroVectorE_02cc0768 + 4);
    fVar27 = *(float *)(PTR__ZN4Aska6Vector10zeroVectorE_02cc0768 + 8);
    fVar33 = *(float *)(param_1 + 0x29c);
    *pfVar21 = fStack_1f0 * fVar33 + *(float *)PTR__ZN4Aska6Vector10zeroVectorE_02cc0768 + *pfVar21;
    pfVar21[1] = fStack_1ec * fVar33 + fVar23 + pfVar21[1];
    pfVar21[2] = fStack_1e8 * fVar33 + fVar27 + pfVar21[2];
    if (*(long *)(lVar18 + 0x120) != 0) {
      *(undefined4 *)(*(long *)(lVar18 + 0x1b8) + lVar14 + 0xcc) = *(undefined4 *)(lVar18 + 0x130);
    }
    Aska::ParticleObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >, Aska::DefaultFunctorList>::SetupParticleTails(int, Aska::Vector const*, StBoolean<false>)(lVar18,uVar19,&fStack_1f0);
    if (((1 < *(int *)(lVar18 + 0x1d4)) && (*(long *)(lVar18 + 0x148) != 0)) &&
       (*(long *)(lVar18 + 0x158) != 0)) {
      uVar10 = *(int *)(lVar18 + 0x1d4) - 1;
      uVar26 = (ulong)uVar10;
      lVar14 = *(long *)(lVar18 + 0x1b8) + lVar14;
      puVar2 = (undefined2 *)(*(long *)(lVar18 + 0x158) + (ulong)*(uint *)(lVar14 + 0x6c) * 0x10);
      puVar16 = (undefined4 *)
                (*(long *)(lVar18 + 0x1c0) + (long)(int)(uVar10 * uVar19) * 0x70 + 0x50);
      do {
        uVar26 = uVar26 - 1;
        puVar16[-4] = *(undefined4 *)(lVar14 + 0x40);
        puVar16[-3] = *(undefined4 *)(lVar14 + 0x44);
        puVar16[-2] = *(undefined4 *)(lVar14 + 0x48);
        puVar16[-1] = *(undefined4 *)(lVar14 + 0x4c);
        *puVar16 = CONCAT22(*puVar2,puVar2[1]);
        puVar16 = puVar16 + 0x1c;
      } while (uVar26 != 0);
    }
  }
  else {
    Aska::Vector::ApplyMatrixNoTransport(Aska::Vector*, Aska::Matrix const*) const(&uStack_110,&fStack_220,param_4[1]);
    fVar27 = fStack_220 * fStack_220 + fStack_21c * fStack_21c + fStack_218 * fStack_218;
    fVar23 = SQRT(fVar27);
    if (NAN(fVar23)) {
      fVar23 = (float)sqrtf(fVar27);
    }
    if (_UNK_027e519c <= fVar23) {
      fVar23 = 1.0 / fVar23;
      fStack_220 = fVar23 * fStack_220;
      fStack_21c = fVar23 * fStack_21c;
      fStack_218 = fVar23 * fStack_218;
    }
    fVar23 = *(float *)(param_1 + 0x29c);
    fStack_220 = fVar23 * fStack_220;
    fStack_21c = fVar23 * fStack_21c;
    fStack_218 = fVar23 * fStack_218;
    Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const(&fStack_220,&fStack_220,lVar20);
    if (*(long *)(lVar18 + 0x120) != 0) {
      *(undefined4 *)(*(long *)(lVar18 + 0x1b8) + lVar14 + 0xcc) = *(undefined4 *)(lVar18 + 0x130);
    }
    Aska::ParticleObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >, Aska::DefaultFunctorList>::SetupParticleTails(int, Aska::Vector const*)(lVar18,uVar19,&fStack_220);
    if (((1 < *(int *)(lVar18 + 0x1d4)) && (*(long *)(lVar18 + 0x148) != 0)) &&
       (*(long *)(lVar18 + 0x158) != 0)) {
      uVar10 = *(int *)(lVar18 + 0x1d4) - 1;
      uVar26 = (ulong)uVar10;
      lVar14 = *(long *)(lVar18 + 0x1b8) + lVar14;
      puVar2 = (undefined2 *)(*(long *)(lVar18 + 0x158) + (ulong)*(uint *)(lVar14 + 0x6c) * 0x10);
      puVar16 = (undefined4 *)
                (*(long *)(lVar18 + 0x1c0) + (long)(int)(uVar10 * uVar19) * 0x70 + 0x50);
      do {
        uVar26 = uVar26 - 1;
        puVar16[-4] = *(undefined4 *)(lVar14 + 0x40);
        puVar16[-3] = *(undefined4 *)(lVar14 + 0x44);
        puVar16[-2] = *(undefined4 *)(lVar14 + 0x48);
        puVar16[-1] = *(undefined4 *)(lVar14 + 0x4c);
        *puVar16 = CONCAT22(*puVar2,puVar2[1]);
        puVar16 = puVar16 + 0x1c;
      } while (uVar26 != 0);
    }
  }
  iVar22 = iVar22 + 1;
  if (param_2 <= iVar22) goto code_r0x024cbf30;
  goto code_r0x024cbf20;
code_r0x024cbf30:
  bVar4 = *(byte *)(param_1 + 0x2d9);
  goto code_r0x024cbf34;
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

// ==== Aska::ParticleRenderableObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >::RenderProcedure(float, Aska::IParticleEmitter::MatrixContext*, bool)
// vaddr 0x23ce49c | ghidra 0x24ce49c | size 616 | symbol _ZN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEE15RenderProcedureEfPNS_16IParticleEmitter13MatrixContextEb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEE15RenderProcedureEfPNS_16IParticleEmitter13MatrixContextEb
               (undefined8 param_1,long *param_2,undefined8 param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  ulong uVar4;
  uint *puVar5;
  undefined8 *puVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  long lVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  int iVar20;
  int iVar22;
  undefined8 uVar21;
  int iVar23;
  int iVar25;
  undefined8 uVar24;
  uint uVar26;
  uint uVar28;
  int iVar29;
  undefined8 uVar27;
  uint uVar30;
  uint uVar33;
  ulong uVar31;
  int iVar34;
  undefined8 uVar32;
  uint uVar35;
  uint uVar38;
  ulong uVar36;
  int iVar39;
  undefined8 uVar37;
  uint uVar40;
  uint uVar43;
  ulong uVar41;
  int iVar44;
  undefined8 uVar42;
  undefined1 auStack_1010 [128];
  undefined1 auStack_f90 [3840];
  undefined1 auStack_90 [80];
  undefined4 uStack_34;
  
  if (param_2[0x1e9] == 0) {
    return;
  }
  Aska::ParticleRenderableBase::PerfCounterStart()(param_2);
  lVar3 = (**(code **)(*param_2 + 0x98))(param_2);
  lVar9 = param_2[0x1e9];
  param_2[0x24] = lVar3;
  lVar3 = *(long *)(lVar9 + 0x1e0);
  uVar1 = *(uint *)(lVar3 + -4);
  if (uVar1 == 0) {
    iVar2 = 0;
    goto code_r0x024ce5f8;
  }
  if (uVar1 < 8) {
    lVar8 = 0;
code_r0x024ce5b0:
    iVar2 = 0;
  }
  else {
    lVar8 = (ulong)uVar1 - (ulong)(uVar1 & 7);
    if (lVar8 == 0) goto code_r0x024ce5b0;
    puVar6 = (undefined8 *)(lVar3 + 0x10);
    iVar2 = 0;
    iVar10 = 0;
    iVar11 = 0;
    iVar12 = 0;
    iVar20 = 0;
    iVar22 = 0;
    iVar23 = 0;
    iVar25 = 0;
    lVar7 = lVar8;
    do {
      uVar19 = puVar6[-1];
      uVar18 = puVar6[-2];
      uVar24 = puVar6[1];
      uVar21 = *puVar6;
      lVar7 = lVar7 + -8;
      puVar6 = puVar6 + 4;
      uVar28 = (uint)((ulong)uVar18 >> 0x20);
      uVar33 = (uint)((ulong)uVar19 >> 0x20);
      uVar38 = (uint)((ulong)uVar21 >> 0x20);
      uVar43 = (uint)((ulong)uVar24 >> 0x20);
      uVar26 = (uint)uVar18 -
               (CONCAT13((byte)((ulong)uVar18 >> 0x18) >> 1,
                         CONCAT12((char)((ushort)((ulong)uVar18 >> 0x10) >> 1),
                                  CONCAT11((char)((uint3)((ulong)uVar18 >> 8) >> 1),
                                           (char)((uint)uVar18 >> 1)))) & 0x55555555);
      uVar28 = uVar28 - (CONCAT13((byte)((ulong)uVar18 >> 0x39),
                                  CONCAT12((char)(ushort)((ulong)uVar18 >> 0x31),
                                           CONCAT11((char)(uint3)((ulong)uVar18 >> 0x29),
                                                    (char)(uVar28 >> 1)))) & 0x55555555);
      uVar30 = (uint)uVar19 -
               (CONCAT13((byte)((ulong)uVar19 >> 0x18) >> 1,
                         CONCAT12((char)((ushort)((ulong)uVar19 >> 0x10) >> 1),
                                  CONCAT11((char)((uint3)((ulong)uVar19 >> 8) >> 1),
                                           (char)((uint)uVar19 >> 1)))) & 0x55555555);
      uVar33 = uVar33 - (CONCAT13((byte)((ulong)uVar19 >> 0x39),
                                  CONCAT12((char)(ushort)((ulong)uVar19 >> 0x31),
                                           CONCAT11((char)(uint3)((ulong)uVar19 >> 0x29),
                                                    (char)(uVar33 >> 1)))) & 0x55555555);
      uVar35 = (uint)uVar21 -
               (CONCAT13((byte)((ulong)uVar21 >> 0x18) >> 1,
                         CONCAT12((char)((ushort)((ulong)uVar21 >> 0x10) >> 1),
                                  CONCAT11((char)((uint3)((ulong)uVar21 >> 8) >> 1),
                                           (char)((uint)uVar21 >> 1)))) & 0x55555555);
      uVar38 = uVar38 - (CONCAT13((byte)((ulong)uVar21 >> 0x39),
                                  CONCAT12((char)(ushort)((ulong)uVar21 >> 0x31),
                                           CONCAT11((char)(uint3)((ulong)uVar21 >> 0x29),
                                                    (char)(uVar38 >> 1)))) & 0x55555555);
      uVar40 = (uint)uVar24 -
               (CONCAT13((byte)((ulong)uVar24 >> 0x18) >> 1,
                         CONCAT12((char)((ushort)((ulong)uVar24 >> 0x10) >> 1),
                                  CONCAT11((char)((uint3)((ulong)uVar24 >> 8) >> 1),
                                           (char)((uint)uVar24 >> 1)))) & 0x55555555);
      uVar43 = uVar43 - (CONCAT13((byte)((ulong)uVar24 >> 0x39),
                                  CONCAT12((char)(ushort)((ulong)uVar24 >> 0x31),
                                           CONCAT11((char)(uint3)((ulong)uVar24 >> 0x29),
                                                    (char)(uVar43 >> 1)))) & 0x55555555);
      uVar4 = CONCAT17((byte)(uVar28 >> 0x1a),
                       CONCAT16((char)((uint3)(uVar28 >> 10) >> 8),
                                CONCAT15((char)((uVar28 >> 2) >> 8),
                                         CONCAT14((char)(uVar28 >> 2),
                                                  CONCAT13((byte)(uVar26 >> 0x1a),
                                                           (int3)(uVar26 >> 2)))))) &
              0x3333333333333333;
      uVar31 = CONCAT17((byte)(uVar33 >> 0x1a),
                        CONCAT16((char)((uint3)(uVar33 >> 10) >> 8),
                                 CONCAT15((char)((uVar33 >> 2) >> 8),
                                          CONCAT14((char)(uVar33 >> 2),
                                                   CONCAT13((byte)(uVar30 >> 0x1a),
                                                            (int3)(uVar30 >> 2)))))) &
               0x3333333333333333;
      uVar36 = CONCAT17((byte)(uVar38 >> 0x1a),
                        CONCAT16((char)((uint3)(uVar38 >> 10) >> 8),
                                 CONCAT15((char)((uVar38 >> 2) >> 8),
                                          CONCAT14((char)(uVar38 >> 2),
                                                   CONCAT13((byte)(uVar35 >> 0x1a),
                                                            (int3)(uVar35 >> 2)))))) &
               0x3333333333333333;
      uVar41 = CONCAT17((byte)(uVar43 >> 0x1a),
                        CONCAT16((char)((uint3)(uVar43 >> 10) >> 8),
                                 CONCAT15((char)((uVar43 >> 2) >> 8),
                                          CONCAT14((char)(uVar43 >> 2),
                                                   CONCAT13((byte)(uVar40 >> 0x1a),
                                                            (int3)(uVar40 >> 2)))))) &
               0x3333333333333333;
      uVar26 = (int)uVar4 + (uVar26 & 0x33333333);
      uVar28 = (int)(uVar4 >> 0x20) + (uVar28 & 0x33333333);
      uVar30 = (int)uVar31 + (uVar30 & 0x33333333);
      uVar33 = (int)(uVar31 >> 0x20) + (uVar33 & 0x33333333);
      uVar35 = (int)uVar36 + (uVar35 & 0x33333333);
      uVar38 = (int)(uVar36 >> 0x20) + (uVar38 & 0x33333333);
      uVar40 = (int)uVar41 + (uVar40 & 0x33333333);
      uVar43 = (int)(uVar41 >> 0x20) + (uVar43 & 0x33333333);
      uVar26 = uVar26 + (uVar26 >> 4);
      iVar29 = uVar28 + (uVar28 >> 4);
      uVar30 = uVar30 + (uVar30 >> 4);
      iVar34 = uVar33 + (uVar33 >> 4);
      iVar39 = uVar38 + (uVar38 >> 4);
      iVar44 = uVar43 + (uVar43 >> 4);
      uVar4 = CONCAT17((char)((uint)iVar39 >> 0x18),
                       CONCAT16((char)((uint)iVar39 >> 0x10),
                                CONCAT15((char)((uint)iVar39 >> 8),
                                         CONCAT14((char)iVar39,uVar35 + (uVar35 >> 4))))) &
              0xf0f0f0f0f0f0f0f;
      uVar31 = CONCAT17((char)((uint)iVar44 >> 0x18),
                        CONCAT16((char)((uint)iVar44 >> 0x10),
                                 CONCAT15((char)((uint)iVar44 >> 8),
                                          CONCAT14((char)iVar44,uVar40 + (uVar40 >> 4))))) &
               0xf0f0f0f0f0f0f0f;
      iVar2 = iVar2 + ((uVar26 & 0xf0f0f0f) * 0x1010101 >> 0x18);
      iVar10 = iVar10 + (((uint)(CONCAT17((char)((uint)iVar29 >> 0x18),
                                          CONCAT16((char)((uint)iVar29 >> 0x10),
                                                   CONCAT15((char)((uint)iVar29 >> 8),
                                                            CONCAT14((char)iVar29,uVar26)))) >> 0x20
                                ) & 0xf0f0f0f) * 0x1010101 >> 0x18);
      iVar11 = iVar11 + ((uVar30 & 0xf0f0f0f) * 0x1010101 >> 0x18);
      iVar12 = iVar12 + (((uint)(CONCAT17((char)((uint)iVar34 >> 0x18),
                                          CONCAT16((char)((uint)iVar34 >> 0x10),
                                                   CONCAT15((char)((uint)iVar34 >> 8),
                                                            CONCAT14((char)iVar34,uVar30)))) >> 0x20
                                ) & 0xf0f0f0f) * 0x1010101 >> 0x18);
      iVar20 = iVar20 + ((uint)((int)uVar4 * 0x1010101) >> 0x18);
      iVar22 = iVar22 + ((uint)((int)(uVar4 >> 0x20) * 0x1010101) >> 0x18);
      iVar23 = iVar23 + ((uint)((int)uVar31 * 0x1010101) >> 0x18);
      iVar25 = iVar25 + ((uint)((int)(uVar31 >> 0x20) * 0x1010101) >> 0x18);
    } while (lVar7 != 0);
    iVar2 = iVar20 + iVar2 + iVar22 + iVar10 + iVar23 + iVar11 + iVar25 + iVar12;
    if ((uVar1 & 7) == 0) goto code_r0x024ce5f8;
  }
  lVar7 = (ulong)uVar1 - lVar8;
  puVar5 = (uint *)(lVar3 + lVar8 * 4);
  do {
    lVar7 = lVar7 + -1;
    uVar1 = *puVar5 - (*puVar5 >> 1 & 0x55555555);
    uVar1 = (uVar1 >> 2 & 0x33333333) + (uVar1 & 0x33333333);
    iVar2 = iVar2 + ((uVar1 + (uVar1 >> 4) & 0xf0f0f0f) * 0x1010101 >> 0x18);
    puVar5 = puVar5 + 1;
  } while (lVar7 != 0);
code_r0x024ce5f8:
  iVar10 = 0;
  if (*(long *)(lVar9 + 0x148) != 0) {
    iVar10 = *(int *)(*(long *)(lVar9 + 0x148) + 0x18);
  }
  if (iVar10 == 0) {
    iVar10 = 1;
  }
  uVar4 = Aska::ParticleRenderableBase::Begin(int, int, int)(param_2,iVar2,*(undefined4 *)(lVar9 + 0x1d4),iVar10);
  if ((uVar4 & 1) != 0) {
    Aska::ParticleRenderableBase::CreateDrawContext(Aska::ParticleRenderableBase::DrawContext*)(param_2,param_2 + (ulong)*(uint *)(param_2 + 0x1eb) * 0x1c + 0x14a);
    Aska::ParticleRenderableBase::SetupLod()(param_2);
    puVar6 = (undefined8 *)param_2[0x24];
    lVar8 = param_2[0x27];
    lVar3 = param_2[0x26];
    lVar13 = param_2[0x29];
    lVar7 = param_2[0x28];
    lVar15 = param_2[0x2b];
    lVar14 = param_2[0x2a];
    lVar17 = param_2[0x2d];
    lVar16 = param_2[0x2c];
    uVar19 = puVar6[1];
    uVar18 = *puVar6;
    uVar24 = puVar6[3];
    uVar21 = puVar6[2];
    uVar32 = puVar6[5];
    uVar27 = puVar6[4];
    uVar42 = puVar6[7];
    uVar37 = puVar6[6];
    *(undefined4 *)(lVar9 + 0x1dc) = 0;
    *(undefined4 *)(lVar9 + 0x1e8) = 0;
    *(long *)(lVar9 + 0x58) = lVar8;
    *(long *)(lVar9 + 0x50) = lVar3;
    *(long *)(lVar9 + 0x68) = lVar13;
    *(long *)(lVar9 + 0x60) = lVar7;
    *(undefined8 *)(lVar9 + 0x18) = uVar19;
    *(undefined8 *)(lVar9 + 0x10) = uVar18;
    *(undefined8 *)(lVar9 + 0x28) = uVar24;
    *(undefined8 *)(lVar9 + 0x20) = uVar21;
    *(undefined8 *)(lVar9 + 0x38) = uVar32;
    *(undefined8 *)(lVar9 + 0x30) = uVar27;
    *(undefined8 *)(lVar9 + 0x48) = uVar42;
    *(undefined8 *)(lVar9 + 0x40) = uVar37;
    *(long *)(lVar9 + 0x78) = lVar15;
    *(long *)(lVar9 + 0x70) = lVar14;
    *(long *)(lVar9 + 0x88) = lVar17;
    *(long *)(lVar9 + 0x80) = lVar16;
    Aska::ParticleRenderableBase::CreateFillContext(Aska::ParticleFillContext*, unsigned int)(param_2,auStack_90,iVar2);
    uStack_34 = 0;
    while (iVar2 = Aska::IParticleObject::GatherActive(float, int, int*, int*)(param_1,lVar9,0x20,auStack_1010,&uStack_34), iVar2 != 0) {
      uVar4 = Aska::ParticleObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >, Aska::DefaultFunctorList>::Procedure(float, int*, int, Aska::ParticleContext*)(param_1,lVar9,auStack_1010,uStack_34,auStack_f90);
      if ((uVar4 & 1) != 0) {
        Aska::ParticleRenderableBase::Fill(Aska::ParticleFillContext const*, Aska::ParticleContext const*, int)(param_2,auStack_90,auStack_f90,iVar2);
      }
    }
    Aska::ParticleRenderableBase::End(bool)(param_2,param_4 & 1);
  }
  Aska::ParticleRenderableBase::PerfCounterEnd()(param_2);
  return;
}

// ==== Aska::ParticleObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >, Aska::DefaultFunctorList>::Procedure(float, int*, int, Aska::ParticleContext*)
// vaddr 0x23ce704 | ghidra 0x24ce704 | size 2520 | symbol _ZN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEE9ProcedureEfPiiPNS_15ParticleContextE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEE9ProcedureEfPiiPNS_15ParticleContextE
               (undefined8 param_1,long param_2,int *param_3,uint param_4,long param_5)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  bool bVar7;
  ulong uVar8;
  int *piVar9;
  uint uVar10;
  float *pfVar11;
  int iVar12;
  float *pfVar13;
  float *pfVar14;
  float *pfVar15;
  long lVar16;
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
  
  iVar12 = *(int *)(param_2 + 0x1d4);
  fVar1 = *(float *)(param_2 + 0x90);
  fVar2 = *(float *)(param_2 + 0x94);
  fVar6 = *(float *)(param_2 + 0x98);
  lVar16 = *(long *)(param_2 + 0x1b8);
  fVar24 = 1.0;
  if ((*(byte *)(param_2 + 0x1f6) & 8) != 0) {
    fVar24 = 0.0;
  }
  fVar23 = (float)param_1;
  if (iVar12 < 2) {
    iVar12 = (int)param_4 >> 2;
    if (iVar12 < 1) {
      uVar10 = 0;
    }
    else {
      uVar10 = iVar12 << 2;
      piVar9 = param_3 + 2;
      pfVar11 = (float *)(param_5 + 0xa0);
      do {
        iVar3 = *piVar9;
        iVar12 = iVar12 + -1;
        pfVar13 = (float *)(lVar16 + (long)piVar9[1] * 0xd0);
        fVar19 = pfVar13[0x30];
        fVar20 = pfVar13[0x31];
        fVar18 = pfVar13[0x32];
        fVar17 = pfVar13[0x33];
        bVar7 = pfVar13[0x2b] == 0.0;
        fVar21 = fVar19 + pfVar13[0x28] * fVar23;
        fVar22 = fVar20 + pfVar13[0x29] * fVar23;
        fVar26 = fVar18 + pfVar13[0x2a] * fVar23;
        fVar25 = fVar19;
        if (bVar7 || 0.0 <= fVar19 * fVar21) {
          fVar25 = fVar21;
        }
        fVar27 = pfVar13[0x2c];
        fVar28 = pfVar13[0x2d];
        fVar29 = pfVar13[0x2e];
        fVar21 = fVar20;
        if (bVar7 || 0.0 <= fVar20 * fVar22) {
          fVar21 = fVar22;
        }
        fVar32 = pfVar13[3];
        fVar22 = *pfVar13 + fVar24 * (fVar19 * fVar23 + fVar1);
        fVar30 = pfVar13[1] + fVar24 * (fVar20 * fVar23 + fVar2);
        fVar31 = pfVar13[2] + fVar24 * (fVar18 * fVar23 + fVar6);
        iVar4 = piVar9[-2];
        iVar5 = piVar9[-1];
        pfVar11[0x14] = fVar22;
        pfVar11[0x15] = fVar30;
        pfVar11[0x16] = fVar31;
        pfVar13[2] = fVar31;
        pfVar13[3] = fVar32 + fVar23;
        pfVar13[0x2e] = fVar18 * fVar23 + fVar29;
        fVar29 = pfVar13[0x20];
        fVar31 = pfVar13[0x21];
        fVar32 = pfVar13[0x22];
        fVar34 = pfVar13[0x23];
        fVar33 = pfVar13[0x24];
        fVar35 = pfVar13[0x25];
        fVar36 = pfVar13[0x26];
        fVar37 = pfVar13[0x27];
        *pfVar13 = fVar22;
        pfVar13[1] = fVar30;
        pfVar13[0x2c] = fVar19 * fVar23 + fVar27;
        pfVar13[0x2d] = fVar20 * fVar23 + fVar28;
        pfVar13[0x30] = fVar25;
        pfVar13[0x31] = fVar21;
        fVar25 = pfVar13[8] + fVar29 * fVar23;
        fVar19 = pfVar13[9] + fVar31 * fVar23;
        fVar20 = pfVar13[10] + fVar32 * fVar23;
        fVar21 = pfVar13[0xb] + fVar34 * fVar23;
        if (bVar7 || 0.0 <= fVar18 * fVar26) {
          fVar18 = fVar26;
        }
        pfVar15 = (float *)(lVar16 + (long)iVar3 * 0xd0);
        pfVar13[0x32] = fVar18;
        pfVar13[0x33] = fVar17 - fVar23;
        pfVar11[0x18] = fVar25;
        pfVar11[0x19] = fVar19;
        pfVar11[0x1a] = fVar20;
        pfVar11[0x1b] = fVar21;
        pfVar13[8] = fVar25;
        pfVar13[9] = fVar19;
        pfVar13[10] = fVar20;
        pfVar13[0xb] = fVar21;
        pfVar13[0x20] = fVar29 + fVar33 * fVar23;
        pfVar13[0x21] = fVar31 + fVar35 * fVar23;
        pfVar13[0x22] = fVar32 + fVar36 * fVar23;
        pfVar13[0x23] = fVar34 + fVar37 * fVar23;
        fVar22 = pfVar15[0x30];
        fVar25 = pfVar15[0x31];
        fVar26 = pfVar15[0x32];
        fVar27 = pfVar15[0x33];
        fVar30 = pfVar15[0x2a];
        fVar34 = pfVar15[0x2e];
        fVar31 = pfVar15[0x2c];
        fVar32 = pfVar15[0x2d];
        fVar21 = pfVar15[3];
        fVar28 = fVar22 + pfVar15[0x28] * fVar23;
        bVar7 = pfVar15[0x2b] == 0.0;
        pfVar13 = (float *)(lVar16 + (long)iVar4 * 0xd0);
        fVar29 = fVar25 + pfVar15[0x29] * fVar23;
        fVar17 = *pfVar15 + fVar24 * (fVar22 * fVar23 + fVar1);
        fVar19 = pfVar15[1] + fVar24 * (fVar25 * fVar23 + fVar2);
        fVar20 = pfVar15[2] + fVar24 * (fVar26 * fVar23 + fVar6);
        *pfVar11 = fVar17;
        pfVar11[1] = fVar19;
        pfVar11[2] = fVar20;
        fVar18 = fVar22;
        if (bVar7 || 0.0 <= fVar22 * fVar28) {
          fVar18 = fVar28;
        }
        fVar28 = fVar26 + fVar30 * fVar23;
        pfVar15[0x2c] = fVar22 * fVar23 + fVar31;
        pfVar15[0x2d] = fVar25 * fVar23 + fVar32;
        pfVar15[0x2e] = fVar26 * fVar23 + fVar34;
        fVar22 = pfVar15[0x20];
        fVar30 = pfVar15[0x21];
        fVar31 = pfVar15[0x22];
        fVar32 = pfVar15[0x23];
        fVar34 = pfVar15[0x24];
        fVar33 = pfVar15[0x25];
        fVar35 = pfVar15[0x26];
        fVar36 = pfVar15[0x27];
        *pfVar15 = fVar17;
        pfVar15[1] = fVar19;
        pfVar15[2] = fVar20;
        pfVar15[3] = fVar21 + fVar23;
        if (bVar7 || 0.0 <= fVar25 * fVar29) {
          fVar25 = fVar29;
        }
        pfVar15[0x30] = fVar18;
        pfVar15[0x31] = fVar25;
        fVar18 = pfVar15[8] + fVar22 * fVar23;
        fVar25 = pfVar15[9] + fVar30 * fVar23;
        fVar17 = pfVar15[10] + fVar31 * fVar23;
        fVar19 = pfVar15[0xb] + fVar32 * fVar23;
        if (bVar7 || 0.0 <= fVar26 * fVar28) {
          fVar26 = fVar28;
        }
        pfVar14 = (float *)(lVar16 + (long)iVar5 * 0xd0);
        pfVar15[0x32] = fVar26;
        pfVar15[0x33] = fVar27 - fVar23;
        pfVar11[4] = fVar18;
        pfVar11[5] = fVar25;
        pfVar11[6] = fVar17;
        pfVar11[7] = fVar19;
        pfVar15[8] = fVar18;
        pfVar15[9] = fVar25;
        pfVar15[10] = fVar17;
        pfVar15[0xb] = fVar19;
        pfVar15[0x20] = fVar22 + fVar34 * fVar23;
        pfVar15[0x21] = fVar30 + fVar33 * fVar23;
        pfVar15[0x22] = fVar31 + fVar35 * fVar23;
        pfVar15[0x23] = fVar32 + fVar36 * fVar23;
        fVar22 = pfVar14[0x30];
        fVar25 = pfVar14[0x31];
        fVar26 = pfVar14[0x32];
        fVar27 = pfVar14[0x33];
        fVar30 = pfVar14[0x2a];
        fVar34 = pfVar14[0x2e];
        fVar31 = pfVar14[0x2c];
        fVar32 = pfVar14[0x2d];
        fVar21 = pfVar14[3];
        fVar28 = fVar22 + pfVar14[0x28] * fVar23;
        bVar7 = pfVar14[0x2b] == 0.0;
        fVar29 = fVar25 + pfVar14[0x29] * fVar23;
        fVar17 = *pfVar14 + fVar24 * (fVar22 * fVar23 + fVar1);
        fVar19 = pfVar14[1] + fVar24 * (fVar25 * fVar23 + fVar2);
        fVar20 = pfVar14[2] + fVar24 * (fVar26 * fVar23 + fVar6);
        pfVar11[-0x14] = fVar17;
        pfVar11[-0x13] = fVar19;
        pfVar11[-0x12] = fVar20;
        fVar18 = fVar22;
        if (bVar7 || 0.0 <= fVar22 * fVar28) {
          fVar18 = fVar28;
        }
        fVar28 = fVar26 + fVar30 * fVar23;
        pfVar14[0x2c] = fVar22 * fVar23 + fVar31;
        pfVar14[0x2d] = fVar25 * fVar23 + fVar32;
        pfVar14[0x2e] = fVar26 * fVar23 + fVar34;
        fVar22 = pfVar14[0x20];
        fVar30 = pfVar14[0x21];
        fVar31 = pfVar14[0x22];
        fVar32 = pfVar14[0x23];
        fVar34 = pfVar14[0x24];
        fVar33 = pfVar14[0x25];
        fVar35 = pfVar14[0x26];
        fVar36 = pfVar14[0x27];
        *pfVar14 = fVar17;
        pfVar14[1] = fVar19;
        pfVar14[2] = fVar20;
        pfVar14[3] = fVar21 + fVar23;
        if (bVar7 || 0.0 <= fVar25 * fVar29) {
          fVar25 = fVar29;
        }
        pfVar14[0x30] = fVar18;
        pfVar14[0x31] = fVar25;
        fVar18 = pfVar14[8] + fVar22 * fVar23;
        fVar25 = pfVar14[9] + fVar30 * fVar23;
        fVar17 = pfVar14[10] + fVar31 * fVar23;
        fVar19 = pfVar14[0xb] + fVar32 * fVar23;
        if (bVar7 || 0.0 <= fVar26 * fVar28) {
          fVar26 = fVar28;
        }
        pfVar14[0x32] = fVar26;
        pfVar14[0x33] = fVar27 - fVar23;
        pfVar11[-0x10] = fVar18;
        pfVar11[-0xf] = fVar25;
        pfVar11[-0xe] = fVar17;
        pfVar11[-0xd] = fVar19;
        pfVar14[8] = fVar18;
        pfVar14[9] = fVar25;
        pfVar14[10] = fVar17;
        pfVar14[0xb] = fVar19;
        pfVar14[0x20] = fVar22 + fVar34 * fVar23;
        pfVar14[0x21] = fVar30 + fVar33 * fVar23;
        pfVar14[0x22] = fVar31 + fVar35 * fVar23;
        pfVar14[0x23] = fVar32 + fVar36 * fVar23;
        fVar22 = pfVar13[0x30];
        fVar25 = pfVar13[0x31];
        fVar26 = pfVar13[0x32];
        fVar27 = pfVar13[0x33];
        fVar30 = pfVar13[0x2a];
        fVar34 = pfVar13[0x2e];
        fVar31 = pfVar13[0x2c];
        fVar32 = pfVar13[0x2d];
        fVar21 = pfVar13[3];
        fVar28 = fVar22 + pfVar13[0x28] * fVar23;
        bVar7 = pfVar13[0x2b] == 0.0;
        fVar29 = fVar25 + pfVar13[0x29] * fVar23;
        fVar17 = *pfVar13 + fVar24 * (fVar22 * fVar23 + fVar1);
        fVar19 = pfVar13[1] + fVar24 * (fVar25 * fVar23 + fVar2);
        fVar20 = pfVar13[2] + fVar24 * (fVar26 * fVar23 + fVar6);
        pfVar11[-0x28] = fVar17;
        pfVar11[-0x27] = fVar19;
        pfVar11[-0x26] = fVar20;
        fVar18 = fVar22;
        if (bVar7 || 0.0 <= fVar22 * fVar28) {
          fVar18 = fVar28;
        }
        fVar28 = fVar26 + fVar30 * fVar23;
        pfVar13[0x2c] = fVar22 * fVar23 + fVar31;
        pfVar13[0x2d] = fVar25 * fVar23 + fVar32;
        pfVar13[0x2e] = fVar26 * fVar23 + fVar34;
        fVar22 = pfVar13[0x20];
        fVar30 = pfVar13[0x21];
        fVar31 = pfVar13[0x22];
        fVar32 = pfVar13[0x23];
        *pfVar13 = fVar17;
        pfVar13[1] = fVar19;
        pfVar13[2] = fVar20;
        pfVar13[3] = fVar21 + fVar23;
        fVar19 = pfVar13[0x24];
        fVar20 = pfVar13[0x25];
        fVar17 = pfVar13[0x26];
        fVar21 = pfVar13[0x27];
        if (bVar7 || 0.0 <= fVar25 * fVar29) {
          fVar25 = fVar29;
        }
        pfVar13[0x30] = fVar18;
        pfVar13[0x31] = fVar25;
        fVar18 = pfVar13[8] + fVar22 * fVar23;
        fVar25 = pfVar13[9] + fVar30 * fVar23;
        fVar29 = pfVar13[10] + fVar31 * fVar23;
        fVar34 = pfVar13[0xb] + fVar32 * fVar23;
        if (bVar7 || 0.0 <= fVar26 * fVar28) {
          fVar26 = fVar28;
        }
        piVar9 = piVar9 + 4;
        pfVar13[0x32] = fVar26;
        pfVar13[0x33] = fVar27 - fVar23;
        pfVar11[-0x24] = fVar18;
        pfVar11[-0x23] = fVar25;
        pfVar11[-0x22] = fVar29;
        pfVar11[-0x21] = fVar34;
        pfVar11 = pfVar11 + 0x50;
        pfVar13[8] = fVar18;
        pfVar13[9] = fVar25;
        pfVar13[10] = fVar29;
        pfVar13[0xb] = fVar34;
        pfVar13[0x20] = fVar22 + fVar19 * fVar23;
        pfVar13[0x21] = fVar30 + fVar20 * fVar23;
        pfVar13[0x22] = fVar31 + fVar17 * fVar23;
        pfVar13[0x23] = fVar32 + fVar21 * fVar23;
      } while (iVar12 != 0);
    }
    if ((param_4 & 3) != 0) {
      iVar12 = (uVar10 | param_4 & 3) - uVar10;
      pfVar11 = (float *)(param_5 + (long)(int)uVar10 * 0x50 + 0x10);
      piVar9 = param_3 + (int)uVar10;
      do {
        iVar12 = iVar12 + -1;
        pfVar13 = (float *)(lVar16 + (long)*piVar9 * 0xd0);
        fVar22 = pfVar13[0x30];
        fVar25 = pfVar13[0x31];
        fVar26 = pfVar13[0x32];
        fVar27 = pfVar13[0x33];
        fVar30 = pfVar13[0x2a];
        fVar34 = pfVar13[0x2e];
        fVar31 = pfVar13[0x2c];
        fVar32 = pfVar13[0x2d];
        fVar21 = pfVar13[3];
        fVar28 = fVar22 + pfVar13[0x28] * fVar23;
        bVar7 = pfVar13[0x2b] == 0.0;
        fVar29 = fVar25 + pfVar13[0x29] * fVar23;
        fVar17 = *pfVar13 + fVar24 * (fVar22 * fVar23 + fVar1);
        fVar19 = pfVar13[1] + fVar24 * (fVar25 * fVar23 + fVar2);
        fVar20 = pfVar13[2] + fVar24 * (fVar26 * fVar23 + fVar6);
        pfVar11[-4] = fVar17;
        pfVar11[-3] = fVar19;
        pfVar11[-2] = fVar20;
        fVar18 = fVar22;
        if (bVar7 || 0.0 <= fVar22 * fVar28) {
          fVar18 = fVar28;
        }
        fVar28 = fVar26 + fVar30 * fVar23;
        pfVar13[0x2c] = fVar22 * fVar23 + fVar31;
        pfVar13[0x2d] = fVar25 * fVar23 + fVar32;
        pfVar13[0x2e] = fVar26 * fVar23 + fVar34;
        fVar22 = pfVar13[0x20];
        fVar30 = pfVar13[0x21];
        fVar31 = pfVar13[0x22];
        fVar32 = pfVar13[0x23];
        *pfVar13 = fVar17;
        pfVar13[1] = fVar19;
        pfVar13[2] = fVar20;
        pfVar13[3] = fVar21 + fVar23;
        fVar19 = pfVar13[0x24];
        fVar20 = pfVar13[0x25];
        fVar17 = pfVar13[0x26];
        fVar21 = pfVar13[0x27];
        if (bVar7 || 0.0 <= fVar25 * fVar29) {
          fVar25 = fVar29;
        }
        pfVar13[0x30] = fVar18;
        pfVar13[0x31] = fVar25;
        fVar18 = pfVar13[8] + fVar22 * fVar23;
        fVar25 = pfVar13[9] + fVar30 * fVar23;
        fVar29 = pfVar13[10] + fVar31 * fVar23;
        fVar34 = pfVar13[0xb] + fVar32 * fVar23;
        if (bVar7 || 0.0 <= fVar26 * fVar28) {
          fVar26 = fVar28;
        }
        pfVar13[0x32] = fVar26;
        pfVar13[0x33] = fVar27 - fVar23;
        *pfVar11 = fVar18;
        pfVar11[1] = fVar25;
        pfVar11[2] = fVar29;
        pfVar11[3] = fVar34;
        pfVar11 = pfVar11 + 0x14;
        pfVar13[8] = fVar18;
        pfVar13[9] = fVar25;
        pfVar13[10] = fVar29;
        pfVar13[0xb] = fVar34;
        pfVar13[0x20] = fVar22 + fVar19 * fVar23;
        pfVar13[0x21] = fVar30 + fVar20 * fVar23;
        pfVar13[0x22] = fVar31 + fVar17 * fVar23;
        pfVar13[0x23] = fVar32 + fVar21 * fVar23;
        piVar9 = piVar9 + 1;
      } while (iVar12 != 0);
    }
  }
  else {
    Aska::IParticleObject::TailProcedure(int const*, int, Aska::ParticleContext*)(param_2,param_3,param_4,param_5);
    if (0 < (int)param_4) {
      uVar8 = (ulong)param_4;
      pfVar11 = (float *)(param_5 + 0x10);
      piVar9 = param_3;
      do {
        uVar8 = uVar8 - 1;
        pfVar13 = (float *)(lVar16 + (long)*piVar9 * 0xd0);
        fVar22 = pfVar13[0x30];
        fVar25 = pfVar13[0x31];
        fVar26 = pfVar13[0x32];
        fVar27 = pfVar13[0x33];
        fVar30 = pfVar13[0x2a];
        fVar34 = pfVar13[0x2e];
        fVar31 = pfVar13[0x2c];
        fVar32 = pfVar13[0x2d];
        fVar21 = pfVar13[3];
        fVar28 = fVar22 + pfVar13[0x28] * fVar23;
        bVar7 = pfVar13[0x2b] == 0.0;
        fVar29 = fVar25 + pfVar13[0x29] * fVar23;
        fVar17 = *pfVar13 + fVar24 * (fVar22 * fVar23 + fVar1);
        fVar19 = pfVar13[1] + fVar24 * (fVar25 * fVar23 + fVar2);
        fVar20 = pfVar13[2] + fVar24 * (fVar26 * fVar23 + fVar6);
        pfVar11[-4] = fVar17;
        pfVar11[-3] = fVar19;
        pfVar11[-2] = fVar20;
        fVar18 = fVar22;
        if (bVar7 || 0.0 <= fVar22 * fVar28) {
          fVar18 = fVar28;
        }
        fVar28 = fVar26 + fVar30 * fVar23;
        pfVar13[0x2c] = fVar22 * fVar23 + fVar31;
        pfVar13[0x2d] = fVar25 * fVar23 + fVar32;
        pfVar13[0x2e] = fVar26 * fVar23 + fVar34;
        fVar22 = pfVar13[0x20];
        fVar30 = pfVar13[0x21];
        fVar31 = pfVar13[0x22];
        fVar32 = pfVar13[0x23];
        *pfVar13 = fVar17;
        pfVar13[1] = fVar19;
        pfVar13[2] = fVar20;
        pfVar13[3] = fVar21 + fVar23;
        fVar19 = pfVar13[0x24];
        fVar20 = pfVar13[0x25];
        fVar17 = pfVar13[0x26];
        fVar21 = pfVar13[0x27];
        if (bVar7 || 0.0 <= fVar25 * fVar29) {
          fVar25 = fVar29;
        }
        pfVar13[0x30] = fVar18;
        pfVar13[0x31] = fVar25;
        fVar18 = pfVar13[8] + fVar22 * fVar23;
        fVar25 = pfVar13[9] + fVar30 * fVar23;
        fVar29 = pfVar13[10] + fVar31 * fVar23;
        fVar34 = pfVar13[0xb] + fVar32 * fVar23;
        if (bVar7 || 0.0 <= fVar26 * fVar28) {
          fVar26 = fVar28;
        }
        pfVar13[0x32] = fVar26;
        pfVar13[0x33] = fVar27 - fVar23;
        *pfVar11 = fVar18;
        pfVar11[1] = fVar25;
        pfVar11[2] = fVar29;
        pfVar11[3] = fVar34;
        pfVar11 = pfVar11 + (long)iVar12 * 0x14;
        pfVar13[8] = fVar18;
        pfVar13[9] = fVar25;
        pfVar13[10] = fVar29;
        pfVar13[0xb] = fVar34;
        pfVar13[0x20] = fVar22 + fVar19 * fVar23;
        pfVar13[0x21] = fVar30 + fVar20 * fVar23;
        pfVar13[0x22] = fVar31 + fVar17 * fVar23;
        pfVar13[0x23] = fVar32 + fVar21 * fVar23;
        piVar9 = piVar9 + 1;
      } while (uVar8 != 0);
    }
    Aska::IParticleObject::ExtendProcedure(Aska::ParticleContext*, int)(param_2,param_5,param_4);
  }
  *(undefined1 *)(param_2 + 0xa09) = 0;
  Aska::ParticleObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >, Aska::DefaultFunctorList>::TextureProcedure(float, int const*, int, Aska::ParticleContext*, StBoolean<true>)(param_1,param_2,param_3,param_4,param_5);
  Aska::ParticleObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >, Aska::DefaultFunctorList>::LifeProcedure(int const*, int, StBoolean<true>)(param_2,param_3,param_4);
  Aska::ParticleObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >, Aska::DefaultFunctorList>::EmitLinkProcedure(int const*, int, StBoolean<true>)(param_2,param_3,param_4);
  Aska::IParticleObject::LightingProcedure(float, int const*, int, Aska::ParticleContext*)(param_1,param_2,param_3,param_4,param_5);
  bVar7 = *(char *)(param_2 + 0xa09) == '\0';
  if (bVar7) {
    Aska::ParticleObject<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >, Aska::DefaultFunctorList>::AnimationProcedure(int const*, int, StBoolean<true>)(param_2,param_3,param_4);
  }
  return bVar7;
}
