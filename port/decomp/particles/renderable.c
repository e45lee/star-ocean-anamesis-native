// port/decomp/particles/renderable.c: Ghidra decompiles for the particles subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 13:23 UTC: tools/decomp.sh '--into' 'particles/renderable' 'Aska::ParticleRenderableBase::' 'Aska::ParticleDrawContext::'

// ==== Aska::ParticleRenderableBase::GetBoundingBox(bool)
// vaddr 0x219d31c | ghidra 0x229d31c | size 24 | symbol _ZN4Aska22ParticleRenderableBase14GetBoundingBoxEb | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska22ParticleRenderableBase14GetBoundingBoxEb(long param_1)

{
  return param_1 + (ulong)(*(uint *)(param_1 + 0xf58) ^ 1) * 0xe0 + 0xa60;
}

// ==== Aska::ParticleRenderableBase::SetSystemColorRate(Aska::Vector const*)
// vaddr 0x219d334 | ghidra 0x229d334 | size 92 | symbol _ZN4Aska22ParticleRenderableBase18SetSystemColorRateEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase18SetSystemColorRateEPKNS_6VectorE(long param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  *(float *)(param_1 + 0xfd0) = *param_2;
  *(float *)(param_1 + 0xfd4) = param_2[1];
  *(float *)(param_1 + 0xfd8) = param_2[2];
  *(float *)(param_1 + 0xfdc) = param_2[3];
  fVar1 = param_2[1];
  fVar2 = param_2[2];
  fVar3 = param_2[3];
  *(float *)(param_1 + 0x270) = *param_2 * *(float *)(param_1 + 0xfc0);
  *(float *)(param_1 + 0x274) = fVar1 * *(float *)(param_1 + 0xfc4);
  *(float *)(param_1 + 0x278) = fVar2 * *(float *)(param_1 + 0xfc8);
  *(float *)(param_1 + 0x27c) = fVar3 * *(float *)(param_1 + 0xfcc);
  return;
}

// ==== Aska::ParticleRenderableBase::SystemColorRate() const
// vaddr 0x219d390 | ghidra 0x229d390 | size 8 | symbol _ZNK4Aska22ParticleRenderableBase15SystemColorRateEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK4Aska22ParticleRenderableBase15SystemColorRateEv(long param_1)

{
  return param_1 + 0xfd0;
}

// ==== Aska::ParticleRenderableBase::SetColorRate(Aska::Vector const*)
// vaddr 0x219d398 | ghidra 0x229d398 | size 92 | symbol _ZN4Aska22ParticleRenderableBase12SetColorRateEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase12SetColorRateEPKNS_6VectorE(long param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  *(float *)(param_1 + 0xfc0) = *param_2;
  *(float *)(param_1 + 0xfc4) = param_2[1];
  *(float *)(param_1 + 0xfc8) = param_2[2];
  *(float *)(param_1 + 0xfcc) = param_2[3];
  fVar1 = param_2[1];
  fVar2 = param_2[2];
  fVar3 = param_2[3];
  *(float *)(param_1 + 0x270) = *param_2 * *(float *)(param_1 + 0xfd0);
  *(float *)(param_1 + 0x274) = fVar1 * *(float *)(param_1 + 0xfd4);
  *(float *)(param_1 + 0x278) = fVar2 * *(float *)(param_1 + 0xfd8);
  *(float *)(param_1 + 0x27c) = fVar3 * *(float *)(param_1 + 0xfdc);
  return;
}

// ==== Aska::ParticleRenderableBase::ColorRate() const
// vaddr 0x219d3f4 | ghidra 0x229d3f4 | size 8 | symbol _ZNK4Aska22ParticleRenderableBase9ColorRateEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK4Aska22ParticleRenderableBase9ColorRateEv(long param_1)

{
  return param_1 + 0xfc0;
}

// ==== Aska::ParticleRenderableBase::ComputeBoundingSphere(bool)
// vaddr 0x219d3fc | ghidra 0x229d3fc | size 40 | symbol _ZN4Aska22ParticleRenderableBase21ComputeBoundingSphereEb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase21ComputeBoundingSphereEb(long param_1)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  
  lVar1 = param_1 + (ulong)(*(uint *)(param_1 + 0xf58) ^ 1) * 0xe0;
  uVar3 = *(undefined8 *)(lVar1 + 0xa58);
  uVar2 = *(undefined8 *)(lVar1 + 0xa50);
  *(byte *)(param_1 + 0x128) = *(byte *)(param_1 + 0x128) | 0x10;
  *(undefined8 *)(param_1 + 0x2d8) = uVar3;
  *(undefined8 *)(param_1 + 0x2d0) = uVar2;
  return;
}

// ==== Aska::ParticleRenderableBase::ParticleRenderableBase()
// vaddr 0x21a497c | ghidra 0x22a497c | size 856 | symbol _ZN4Aska22ParticleRenderableBaseC2Ev | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska22ParticleRenderableBaseC1Ev(long *param_1)

{
  long *plVar1;
  undefined *puVar2;
  long lVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  char cVar7;
  bool bVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  ulong uVar15;
  undefined4 uVar16;
  long lVar17;
  uint uVar18;
  long lVar19;
  long lVar20;
  long lVar22;
  undefined1 auVar21 [16];
  long lVar23;
  long *plStack_40;
  undefined8 uStack_38;
  
  Aska::RenderableObject::RenderableObject()();
  *(undefined4 *)(param_1 + 0x62) = 0;
  plVar1 = param_1 + 100;
  puVar2 = PTR__ZTVN4Aska16TBarrierSlimBaseINS_12TBarrierSlimILb1EEEEE_02cbf998 + 0x10;
  param_1[0x61] = (long)(PTR__ZTVN4Aska15ITextureHandlerE_02cc0f80 + 0x10);
  param_1[99] = (long)puVar2;
  do {
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar8) {
      *(undefined4 *)plVar1 = 0;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
  Aska::Event::Event()(param_1 + 0x65);
  param_1[99] = (long)(PTR__ZTVN4Aska12TBarrierSlimILb1EEE_02cba3c0 + 0x10);
  *(undefined4 *)(param_1 + 0x72) = 0;
  do {
    if ((int)*plVar1 != 0) {
      ClearExclusiveLocal();
      uVar18 = 0;
      do {
        uVar18 = uVar18 + 1;
        if ((uVar18 & 0x1ff) == 0) {
          Aska::Thread::SleepU(unsigned int)(0);
        }
        while ((int)*plVar1 == 0) {
          cVar7 = '\x01';
          bVar8 = (bool)ExclusiveMonitorPass(plVar1,0x10);
          if (bVar8) {
            *(undefined4 *)plVar1 = 1;
            cVar7 = ExclusiveMonitorsStatus();
          }
          if (cVar7 == '\0') goto code_r0x022a4a38;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar8) {
      *(undefined4 *)plVar1 = 1;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
code_r0x022a4a38:
  *(undefined4 *)((long)param_1 + 0x324) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined1 *)((long)param_1 + 0x39c) = 0;
  do {
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(param_1 + 0x73,0x10);
    if (bVar8) {
      *(undefined4 *)(param_1 + 0x73) = 0;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
  uStack_38 = 0;
  lVar17 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
  lVar3 = lVar17 + 0xb0;
  plStack_40 = param_1 + 0x61;
  Aska::CriticalSection::Enter() const(lVar3);
  Aska::TextureManager::RegisterTextureEx(Aska::TextureMemory::tagKey const*, bool, int, int)(lVar17,&plStack_40,1,0,0);
  Aska::CriticalSection::Leave() const(lVar3);
  puVar2 = PTR__ZTVN4Aska22ParticleRenderableBaseE_02cbfe58;
  *(undefined4 *)(param_1 + 0x115) = 0xffffffff;
  auVar21 = _UNK_027dbb30;
  lVar12 = _UNK_027dbb28;
  lVar11 = _UNK_027dbb20;
  lVar10 = _UNK_027dbb18;
  lVar9 = _UNK_027dbb10;
  lVar17 = _UNK_027dbb08;
  lVar3 = _UNK_027dbb00;
  param_1[0x114] = 1;
  *(undefined1 *)(param_1 + 0x117) = 0;
  *param_1 = (long)(puVar2 + 0x10);
  param_1[0x61] = (long)(puVar2 + 0x2f0);
  param_1[0x1e9] = 0;
  param_1[0x1e8] = 0;
  *(undefined4 *)(param_1 + 0x1eb) = 0;
  param_1[0x4c] = -1;
  param_1[0x1ee] = 0;
  *(undefined4 *)(param_1 + 0x1ef) = 0;
  param_1[0x1ed] = 0;
  param_1[0x1ec] = 0;
  param_1[0xf5] = lVar17;
  param_1[0xf4] = lVar3;
  param_1[0xf7] = lVar10;
  param_1[0xf6] = lVar9;
  param_1[0xf9] = lVar12;
  param_1[0xf8] = lVar11;
  lVar22 = auVar21._8_8_;
  param_1[0xfb] = lVar22;
  lVar19 = auVar21._0_8_;
  param_1[0xfa] = lVar19;
  param_1[0xfd] = lVar17;
  param_1[0xfc] = lVar3;
  param_1[0xff] = lVar10;
  param_1[0xfe] = lVar9;
  param_1[0x101] = lVar12;
  param_1[0x100] = lVar11;
  param_1[0x103] = lVar22;
  param_1[0x102] = lVar19;
  param_1[0x105] = lVar17;
  param_1[0x104] = lVar3;
  param_1[0x107] = lVar10;
  param_1[0x106] = lVar9;
  param_1[0x109] = lVar12;
  param_1[0x108] = lVar11;
  param_1[0x10b] = lVar22;
  param_1[0x10a] = lVar19;
  param_1[0x10d] = 0;
  param_1[0x10c] = 0;
  puVar2 = PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  if ((*(byte *)(param_1 + 0x5e) & 1) == 0) {
    uVar16 = 6;
  }
  else {
    uVar16 = 6;
    uVar15 = Aska::ObjectManager::IsReducedBufferLayer(int)(*(undefined8 *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688,6);
    if (((uVar15 & 1) == 0) &&
       (uVar15 = Aska::ObjectManager::IsNeedZLayer(int)(*(undefined8 *)puVar2,6), (uVar15 & 1) == 0)) {
      uVar16 = 8;
    }
  }
  Aska::RenderableObject::SetRenderLayerID(unsigned char)(param_1,uVar16);
  memset(param_1 + 0x156,0,0x160);
  puVar2 = PTR__ZN4Aska6Vector10zeroVectorE_02cc0768;
  lVar14 = _UNK_029c6988;
  lVar13 = _UNK_029c6980;
  auVar21 = NEON_fmov(0x3f800000,4);
  uVar5 = *(undefined4 *)PTR__ZN4Aska6Vector10zeroVectorE_02cc0768;
  *(undefined4 *)(param_1 + 0x14a) = uVar5;
  uVar16 = *(undefined4 *)(puVar2 + 4);
  uVar4 = *(undefined4 *)(puVar2 + 8);
  *(undefined4 *)((long)param_1 + 0xa54) = uVar16;
  *(undefined4 *)(param_1 + 0x14b) = uVar4;
  uVar6 = *(undefined4 *)(puVar2 + 0xc);
  *(undefined4 *)(param_1 + 0x166) = uVar5;
  *(undefined4 *)((long)param_1 + 0xb34) = uVar16;
  *(undefined4 *)(param_1 + 0x167) = uVar4;
  lVar23 = auVar21._8_8_;
  lVar20 = auVar21._0_8_;
  *(undefined4 *)((long)param_1 + 0xa5c) = uVar6;
  *(undefined4 *)((long)param_1 + 0xb3c) = uVar6;
  param_1[0x14d] = lVar22;
  param_1[0x14c] = lVar19;
  *(undefined4 *)(param_1 + 0x150) = 0x3f800000;
  *(undefined8 *)((long)param_1 + 0xa8c) = 0;
  *(undefined8 *)((long)param_1 + 0xa84) = 0;
  *(undefined4 *)((long)param_1 + 0xa94) = 0x3f800000;
  param_1[0x154] = 0;
  param_1[0x153] = 0;
  param_1[0x155] = 0x3f800000;
  param_1[0x14f] = lVar23;
  param_1[0x14e] = lVar20;
  param_1[0x169] = lVar22;
  param_1[0x168] = lVar19;
  param_1[0x16b] = lVar23;
  param_1[0x16a] = lVar20;
  *(undefined4 *)(param_1 + 0x16c) = 0x3f800000;
  *(undefined8 *)((long)param_1 + 0xb6c) = 0;
  *(undefined8 *)((long)param_1 + 0xb64) = 0;
  *(undefined4 *)((long)param_1 + 0xb74) = 0x3f800000;
  param_1[0x170] = 0;
  param_1[0x16f] = 0;
  param_1[0x171] = 0x3f800000;
  param_1[0x116] = 0xffffffff;
  param_1[0x10f] = 0;
  param_1[0x10e] = 0;
  param_1[0x111] = lVar14;
  param_1[0x110] = lVar13;
  param_1[0x113] = 0;
  param_1[0x112] = 0;
  param_1[0x149] = 0;
  param_1[0x148] = 0;
  *(byte *)((long)param_1 + 0xf5c) = *(byte *)((long)param_1 + 0xf5c) & 0x86 | 1;
  memset(param_1 + 0x138,0,0x80);
  param_1[0x1ea] = 0;
  memset(param_1 + 0x74,0,0x400);
  param_1[0x1f9] = lVar23;
  param_1[0x1f8] = lVar20;
  param_1[0x1fb] = lVar23;
  param_1[0x1fa] = lVar20;
  param_1[0x1f1] = lVar17;
  param_1[0x1f0] = lVar3;
  param_1[499] = lVar10;
  param_1[0x1f2] = lVar9;
  param_1[0x1f5] = lVar12;
  param_1[500] = lVar11;
  param_1[0x1f7] = lVar22;
  param_1[0x1f6] = lVar19;
  return;
}

// ==== Aska::ParticleRenderableBase::~ParticleRenderableBase()
// vaddr 0x21a4cd4 | ghidra 0x22a4cd4 | size 420 | symbol _ZN4Aska22ParticleRenderableBaseD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBaseD1Ev(long *param_1)

{
  undefined *puVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  long lVar5;
  
  lVar5 = param_1[0x1e9];
  puVar1 = PTR__ZTVN4Aska22ParticleRenderableBaseE_02cbfe58 + 0x2f0;
  *param_1 = (long)(PTR__ZTVN4Aska22ParticleRenderableBaseE_02cbfe58 + 0x10);
  param_1[0x61] = (long)puVar1;
  if (lVar5 != 0) {
    if ((int)param_1[0x115] != -1) {
      (**(code **)(**(long **)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108 + 0x40))();
      lVar5 = param_1[0x1e9];
      *(undefined4 *)(param_1 + 0x115) = 0xffffffff;
    }
    Aska::IParticleObject::Release()(lVar5);
    param_1[0x1e9] = 0;
  }
  if (param_1[0x149] != 0) {
    piVar2 = (int *)(param_1[0x149] + 0x4c);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar4) {
        *piVar2 = *piVar2 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    param_1[0x149] = 0;
  }
  if (param_1[0x148] != 0) {
    piVar2 = (int *)(*(long *)(param_1[0x148] + 0x10) + 0x4c);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar4) {
        *piVar2 = *piVar2 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    param_1[0x148] = 0;
  }
  if ((int)param_1[0x115] != -1) {
    (**(code **)(**(long **)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108 + 0x40))();
    *(undefined4 *)(param_1 + 0x115) = 0xffffffff;
  }
  lVar5 = 0;
  do {
    *(undefined8 *)((long)param_1 + lVar5 + 0x3a0) = 0;
    if (*(long *)((long)param_1 + lVar5 + 0x3a8) != 0) {
      operator delete(void*)();
      *(undefined8 *)((long)param_1 + lVar5 + 0x3a8) = 0;
    }
    if (*(long *)((long)param_1 + lVar5 + 0x3b0) != 0) {
      operator delete(void*)();
      *(undefined8 *)((long)param_1 + lVar5 + 0x3b0) = 0;
    }
    if (*(long *)((long)param_1 + lVar5 + 0x3b8) != 0) {
      operator delete(void*)();
      *(undefined8 *)((long)param_1 + lVar5 + 0x3b8) = 0;
    }
    lVar5 = lVar5 + 0x20;
  } while (lVar5 != 0x400);
  if (param_1[0x1ed] != 0) {
    (**(code **)(**(long **)PTR__ZN4Aska6Global23m_pMeshGeneratorManagerE_02cc2bc0 + 0x28))();
    if ((long *)param_1[0x1ed] != (long *)0x0) {
      (**(code **)(*(long *)param_1[0x1ed] + 8))();
      param_1[0x1ed] = 0;
    }
  }
  param_1[0x61] = (long)(PTR__ZTVN4Aska15ITextureHandlerE_02cc0f80 + 0x10);
  Aska::ITextureHandler::DetachTexture()(param_1 + 0x61);
  Aska::TBarrierSlim<true>::~TBarrierSlim()(param_1 + 99);
  param_1[0x61] = (long)(PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10);
  (*(code *)PTR__ZN4Aska16RenderableObjectD2Ev_02cad338)(param_1);
  return;
}

// ==== Aska::ParticleRenderableBase::DetachObject()
// vaddr 0x21a4e78 | ghidra 0x22a4e78 | size 80 | symbol _ZN4Aska22ParticleRenderableBase12DetachObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase12DetachObjectEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0xf48);
  if (lVar1 != 0) {
    if (*(int *)(param_1 + 0x8a8) != -1) {
      (**(code **)(**(long **)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108 + 0x40))();
      lVar1 = *(long *)(param_1 + 0xf48);
      *(undefined4 *)(param_1 + 0x8a8) = 0xffffffff;
    }
    Aska::IParticleObject::Release()(lVar1);
    *(undefined8 *)(param_1 + 0xf48) = 0;
  }
  return;
}

// ==== Aska::ParticleRenderableBase::ReleaseBuffers()
// vaddr 0x21a4ec8 | ghidra 0x22a4ec8 | size 60 | symbol _ZN4Aska22ParticleRenderableBase14ReleaseBuffersEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase14ReleaseBuffersEv(long param_1)

{
  if (*(int *)(param_1 + 0x8a8) != -1) {
    (**(code **)(**(long **)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108 + 0x40))();
    *(undefined4 *)(param_1 + 0x8a8) = 0xffffffff;
  }
  return;
}

// ==== non-virtual thunk to Aska::ParticleRenderableBase::~ParticleRenderableBase()
// vaddr 0x21a4f04 | ghidra 0x22a4f04 | size 8 | symbol _ZThn776_N4Aska22ParticleRenderableBaseD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn776_N4Aska22ParticleRenderableBaseD1Ev(long param_1)

{
  (*(code *)PTR__ZN4Aska22ParticleRenderableBaseD1Ev_02c958f8)(param_1 + -0x308);
  return;
}

// ==== Aska::ParticleRenderableBase::~ParticleRenderableBase()
// vaddr 0x21a4f0c | ghidra 0x22a4f0c | size 64 | symbol _ZN4Aska22ParticleRenderableBaseD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBaseD0Ev(long param_1)

{
  Aska::ParticleRenderableBase::~ParticleRenderableBase()();
  if (param_1 == 0) {
    return;
  }
  if (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPv_02cb5c60)
              (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838,param_1);
    return;
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::ParticleRenderableBase::operator delete(void*)
// vaddr 0x21a4f4c | ghidra 0x22a4f4c | size 44 | symbol _ZN4Aska22ParticleRenderableBasedlEPv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBasedlEPv(long param_1)

{
  if (param_1 == 0) {
    return;
  }
  if (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPv_02cb5c60)
              (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838,param_1);
    return;
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::ParticleRenderableBase::~ParticleRenderableBase()
// vaddr 0x21a4f78 | ghidra 0x22a4f78 | size 56 | symbol _ZThn776_N4Aska22ParticleRenderableBaseD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn776_N4Aska22ParticleRenderableBaseD0Ev(long param_1)

{
  param_1 = param_1 + -0x308;
  Aska::ParticleRenderableBase::~ParticleRenderableBase()(param_1);
  if (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPv_02cb5c60)
              (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838,param_1);
    return;
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::ParticleRenderableBase::ReleaseImmediately()
// vaddr 0x21a4fb0 | ghidra 0x22a4fb0 | size 24 | symbol _ZN4Aska22ParticleRenderableBase18ReleaseImmediatelyEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase18ReleaseImmediatelyEv(long param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x8a0);
  iVar2 = iVar1 + -1;
  *(int *)(param_1 + 0x8a0) = iVar2;
  if (iVar2 == 0 || iVar1 < 1) {
    (*(code *)PTR__ZN4Aska4Task21DeleteThisImmediatelyEv_02caf760)();
    return;
  }
  return;
}

// ==== Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)
// vaddr 0x21a4fc8 | ghidra 0x22a4fc8 | size 240 | symbol _ZN4Aska22ParticleRenderableBase12AttachObjectEPNS_15IParticleObjectE | lib libSOA-3.7.0.so | 2026-10-08
ulong _ZN4Aska22ParticleRenderableBase12AttachObjectEPNS_15IParticleObjectE
                (long param_1,long param_2)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0xf48);
  if (lVar3 != 0) {
    if (*(int *)(param_1 + 0x8a8) != -1) {
      (**(code **)(**(long **)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108 + 0x40))();
      lVar3 = *(long *)(param_1 + 0xf48);
      *(undefined4 *)(param_1 + 0x8a8) = 0xffffffff;
    }
    Aska::IParticleObject::Release()(lVar3);
    *(undefined8 *)(param_1 + 0xf48) = 0;
  }
  *(long *)(param_1 + 0xf48) = param_2;
  Aska::IParticleObject::AddRef()(param_2);
  if (*(char *)(param_1 + 0x8b8) == '\a') {
    lVar3 = operator new(unsigned long, std::nothrow_t const&)(0x230,PTR__ZSt7nothrow_02cb9a80);
    if (lVar3 != 0) {
      Aska::MeshGenerator::MeshGenerator()(lVar3);
      *(long *)(param_1 + 0xf68) = lVar3;
      uVar2 = (*(code *)PTR__ZN4Aska13MeshGenerator4InitEjb_02cb0a20)
                        (lVar3,*(undefined4 *)(*(long *)(param_1 + 0xf48) + 0x1d0),0);
      return uVar2;
    }
    *(undefined8 *)(param_1 + 0xf68) = 0;
    uVar2 = 0;
  }
  else {
    iVar1 = (**(code **)(**(long **)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108 + 0x10))
                      (*(long **)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108,
                       *(char *)(param_1 + 0x8b8),
                       *(int *)(param_2 + 0x1d0) * *(int *)(param_2 + 0x1d4),
                       *(undefined1 *)(param_2 + 0x1ae));
    *(int *)(param_1 + 0x8a8) = iVar1;
    uVar2 = (ulong)(iVar1 != -1);
  }
  return uVar2;
}

// ==== Aska::ParticleRenderableBase::InitBuffers(unsigned char, int, int, int)
// vaddr 0x21a50b8 | ghidra 0x22a50b8 | size 152 | symbol _ZN4Aska22ParticleRenderableBase11InitBuffersEhiii | lib libSOA-3.7.0.so | 2026-10-08
ulong _ZN4Aska22ParticleRenderableBase11InitBuffersEhiii
                (long param_1,undefined8 param_2,int param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  
  if (((uint)param_2 & 0xff) == 7) {
    lVar3 = operator new(unsigned long, std::nothrow_t const&)(0x230,PTR__ZSt7nothrow_02cb9a80);
    if (lVar3 != 0) {
      Aska::MeshGenerator::MeshGenerator()(lVar3);
      *(long *)(param_1 + 0xf68) = lVar3;
      uVar2 = (*(code *)PTR__ZN4Aska13MeshGenerator4InitEjb_02cb0a20)
                        (lVar3,*(undefined4 *)(*(long *)(param_1 + 0xf48) + 0x1d0),0);
      return uVar2;
    }
    *(undefined8 *)(param_1 + 0xf68) = 0;
    uVar2 = 0;
  }
  else {
    iVar1 = (**(code **)(**(long **)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108 + 0x10))
                      (*(long **)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108,param_2,
                       param_4 * param_3,param_5);
    *(int *)(param_1 + 0x8a8) = iVar1;
    uVar2 = (ulong)(iVar1 != -1);
  }
  return uVar2;
}

// ==== Aska::ParticleRenderableBase::AttachMeshObject(Aska::AofObject*)
// vaddr 0x21a5150 | ghidra 0x22a5150 | size 172 | symbol _ZN4Aska22ParticleRenderableBase16AttachMeshObjectEPNS_9AofObjectE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska22ParticleRenderableBase16AttachMeshObjectEPNS_9AofObjectE(long param_1,long *param_2)

{
  long lVar1;
  
  if (*(long **)(param_1 + 0xf60) != param_2) {
    Aska::MeshGenerator::AttachSourceObject(Aska::AofObject*, bool)(*(undefined8 *)(param_1 + 0xf68),param_2,1);
    (**(code **)(**(long **)PTR__ZN4Aska6Global23m_pMeshGeneratorManagerE_02cc2bc0 + 0x10))
              (*(long **)PTR__ZN4Aska6Global23m_pMeshGeneratorManagerE_02cc2bc0,
               *(undefined8 *)(param_1 + 0xf68));
    *(long **)(param_1 + 0xf60) = param_2;
    lVar1 = *(long *)(param_1 + 0xf68);
    *(undefined4 *)(param_2 + 0xd1) = 0;
    param_2[0xd0] = lVar1;
    *(undefined2 *)((long)param_2 + 0x37c) = *(undefined2 *)((long)param_2 + 0x37c);
    *(uint *)(param_2 + 0x6f) = *(uint *)(param_2 + 0x6f) & 0x7fffffff | (uint)(lVar1 != 0) << 0x1f;
    *(uint *)(param_2 + 0x33) = *(uint *)(param_2 + 0x33) | 2;
    (**(code **)(*param_2 + 200))(0,0,0,param_2);
  }
  return 1;
}

// ==== Aska::ParticleRenderableBase::DetachMeshObject()
// vaddr 0x21a51fc | ghidra 0x22a51fc | size 96 | symbol _ZN4Aska22ParticleRenderableBase16DetachMeshObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase16DetachMeshObjectEv(long param_1)

{
  long lVar1;
  
  if (*(long *)(param_1 + 0xf60) != 0) {
    Aska::MeshGenerator::DetachSourceObject()(*(undefined8 *)(param_1 + 0xf68));
    (**(code **)(**(long **)PTR__ZN4Aska6Global23m_pMeshGeneratorManagerE_02cc2bc0 + 0x28))
              (*(long **)PTR__ZN4Aska6Global23m_pMeshGeneratorManagerE_02cc2bc0,
               *(undefined8 *)(param_1 + 0xf68));
    lVar1 = *(long *)(param_1 + 0xf60);
    *(undefined8 *)(lVar1 + 0x680) = 0;
    *(undefined4 *)(lVar1 + 0x688) = 0;
    *(undefined2 *)(lVar1 + 0x37c) = *(undefined2 *)(lVar1 + 0x37c);
    *(uint *)(lVar1 + 0x378) = *(uint *)(lVar1 + 0x378) & 0x7fffffff;
    *(undefined8 *)(param_1 + 0xf60) = 0;
  }
  return;
}

// ==== Aska::ParticleRenderableBase::CreateFillContext(Aska::ParticleFillContext*, unsigned int)
// vaddr 0x21a525c | ghidra 0x22a525c | size 284 | symbol _ZN4Aska22ParticleRenderableBase17CreateFillContextEPNS_19ParticleFillContextEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase17CreateFillContextEPNS_19ParticleFillContextEj
               (long param_1,undefined8 *param_2,undefined4 param_3)

{
  byte bVar1;
  undefined4 uVar2;
  uint uVar3;
  long lVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  
  *param_2 = *(undefined8 *)(*(long *)(param_1 + 0xf48) + 0x160);
  *(undefined4 *)(param_2 + 1) = *(undefined4 *)(*(long *)(param_1 + 0xf48) + 0x168);
  *(ushort *)(param_2 + 3) = (ushort)*(byte *)(param_1 + 0x8b8);
  *(short *)((long)param_2 + 0x1a) = (short)*(undefined4 *)(*(long *)(param_1 + 0xf48) + 0x1d4);
  *(undefined4 *)((long)param_2 + 0x14) = *(undefined4 *)(*(long *)(param_1 + 0xf48) + 0xe0);
  *(byte *)((long)param_2 + 0x44) = (byte)(*(ushort *)(*(long *)(param_1 + 0xf48) + 500) >> 6) & 1;
  lVar4 = *(long *)(*(long *)(param_1 + 0xf48) + 0x140);
  if ((lVar4 == 0) || (*(long *)(lVar4 + 0x10) == 0)) {
    uVar5 = 0;
    uVar6 = 0x3f80;
    *(undefined4 *)((long)param_2 + 0xc) = 0x3f800000;
  }
  else {
    uVar2 = NEON_ucvtf((uint)*(ushort *)(*(long *)(param_1 + 0xf48) + 0x10c));
    *(undefined4 *)((long)param_2 + 0xc) = uVar2;
    uVar2 = NEON_ucvtf((uint)*(ushort *)(*(long *)(param_1 + 0xf48) + 0x10e));
    uVar5 = (undefined2)uVar2;
    uVar6 = (undefined2)((uint)uVar2 >> 0x10);
  }
  *(uint *)(param_2 + 2) = CONCAT22(uVar6,uVar5);
  *(undefined4 *)((long)param_2 + 0x24) = param_3;
  fVar7 = *(float *)(param_1 + 0x84);
  fVar8 = *(float *)(param_1 + 0x874);
  fVar9 = *(float *)(param_1 + 0x88);
  fVar10 = *(float *)(param_1 + 0x878);
  uVar2 = *(undefined4 *)(param_1 + 0x8c);
  *(float *)(param_2 + 6) = *(float *)(param_1 + 0x80) - *(float *)(param_1 + 0x870);
  *(float *)((long)param_2 + 0x34) = fVar7 - fVar8;
  *(float *)(param_2 + 7) = fVar9 - fVar10;
  *(undefined4 *)((long)param_2 + 0x3c) = uVar2;
  lVar4 = *(long *)(*(long *)(param_1 + 0xf48) + 0x148);
  uVar3 = 0;
  if (lVar4 != 0) {
    uVar3 = *(uint *)(lVar4 + 0x18);
  }
  if (uVar3 < 2) {
    uVar3 = 1;
  }
  *(uint *)(param_2 + 8) = uVar3;
  bVar1 = *(byte *)(*(long *)(param_1 + 0xf40) + 0x2d9);
  *(byte *)((long)param_2 + 0x45) = bVar1 >> 4 & 1;
  if ((bVar1 >> 4 & 1) == 0) {
    *(undefined4 *)((long)param_2 + 0x1c) = 0x3f800000;
    *(undefined4 *)(param_2 + 4) = 0x3f800000;
    return;
  }
  *(undefined4 *)((long)param_2 + 0x1c) = *(undefined4 *)(*(long *)(param_1 + 0xf40) + 0x310);
  *(undefined4 *)(param_2 + 4) = *(undefined4 *)(*(long *)(param_1 + 0xf40) + 0x314);
  return;
}

// ==== Aska::ParticleRenderableBase::CreateDrawContext(Aska::ParticleRenderableBase::DrawContext*)
// vaddr 0x21a5378 | ghidra 0x22a5378 | size 596 | symbol _ZN4Aska22ParticleRenderableBase17CreateDrawContextEPNS0_11DrawContextE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase17CreateDrawContextEPNS0_11DrawContextE
               (long param_1,long param_2)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  long lVar6;
  
  *(undefined4 *)(param_2 + 0xa0) = *(undefined4 *)(*(long *)(param_1 + 0xf48) + 0xe0);
  *(undefined4 *)(param_2 + 0xa4) = *(undefined4 *)(*(long *)(param_1 + 0xf48) + 0xec);
  *(undefined4 *)(param_2 + 0xa8) = *(undefined4 *)(*(long *)(param_1 + 0xf48) + 0xf0);
  *(undefined4 *)(param_2 + 0xac) = *(undefined4 *)(*(long *)(param_1 + 0xf48) + 0xf4);
  *(undefined4 *)(param_2 + 0xb0) = *(undefined4 *)(*(long *)(param_1 + 0xf48) + 0x104);
  lVar6 = *(long *)(*(long *)(param_1 + 0xf48) + 0x148);
  uVar5 = 0;
  if (lVar6 != 0) {
    uVar5 = (undefined1)*(undefined4 *)(lVar6 + 0x18);
  }
  *(undefined1 *)(param_2 + 0xd4) = uVar5;
  uVar1 = *(ushort *)(param_2 + 0xd9);
  *(undefined1 *)(param_2 + 0xd5) = *(undefined1 *)(*(long *)(param_1 + 0xf48) + 0x1b0);
  *(undefined1 *)(param_2 + 0xd6) = *(undefined1 *)(*(long *)(param_1 + 0xf48) + 0x1b2);
  *(undefined1 *)(param_2 + 0xd7) = *(undefined1 *)(*(long *)(param_1 + 0xf48) + 0x1b1);
  uVar3 = (*(ushort *)(*(long *)(param_1 + 0xf48) + 500) >> 1 & 1) << 1;
  *(ushort *)(param_2 + 0xd9) = uVar1 & 0xfffc | uVar1 & 1 | uVar3;
  uVar2 = *(ushort *)(*(long *)(param_1 + 0xf48) + 500) >> 2 & 1;
  *(ushort *)(param_2 + 0xd9) = uVar1 & 0xfffc | uVar3 | uVar2;
  uVar3 = uVar3 | uVar2 | (*(ushort *)(*(long *)(param_1 + 0xf48) + 500) >> 3 & 1) << 2;
  *(ushort *)(param_2 + 0xd9) = uVar1 & 0xfff8 | uVar3;
  uVar3 = uVar3 | (*(ushort *)(*(long *)(param_1 + 0xf48) + 500) >> 4 & 1) << 3;
  *(ushort *)(param_2 + 0xd9) = uVar1 & 0xfff0 | uVar3;
  uVar3 = uVar3 | (*(ushort *)(*(long *)(param_1 + 0xf48) + 500) >> 6 & 1) << 4;
  *(ushort *)(param_2 + 0xd9) = uVar1 & 0xffe0 | uVar3;
  *(ushort *)(param_2 + 0xd9) =
       *(ushort *)(*(long *)(param_1 + 0xf48) + 500) >> 1 & 0x40 | uVar1 & 0xffa0 | uVar3;
  lVar6 = *(long *)(param_1 + 0xf48);
  *(undefined4 *)(param_2 + 0x60) = *(undefined4 *)(lVar6 + 0xa0);
  *(undefined4 *)(param_2 + 100) = *(undefined4 *)(lVar6 + 0xa4);
  *(undefined4 *)(param_2 + 0x68) = *(undefined4 *)(lVar6 + 0xa8);
  *(undefined4 *)(param_2 + 0x6c) = *(undefined4 *)(lVar6 + 0xac);
  lVar6 = *(long *)(param_1 + 0xf48);
  *(undefined4 *)(param_2 + 0x70) = *(undefined4 *)(lVar6 + 0xb0);
  *(undefined4 *)(param_2 + 0x74) = *(undefined4 *)(lVar6 + 0xb4);
  *(undefined4 *)(param_2 + 0x78) = *(undefined4 *)(lVar6 + 0xb8);
  *(undefined4 *)(param_2 + 0x7c) = *(undefined4 *)(lVar6 + 0xbc);
  lVar6 = *(long *)(param_1 + 0xf48);
  *(undefined4 *)(param_2 + 0x80) = *(undefined4 *)(lVar6 + 0xc0);
  *(undefined4 *)(param_2 + 0x84) = *(undefined4 *)(lVar6 + 0xc4);
  *(undefined4 *)(param_2 + 0x88) = *(undefined4 *)(lVar6 + 200);
  *(undefined4 *)(param_2 + 0x8c) = *(undefined4 *)(lVar6 + 0xcc);
  lVar6 = *(long *)(param_1 + 0xf48);
  *(undefined4 *)(param_2 + 0x90) = *(undefined4 *)(lVar6 + 0xd0);
  *(undefined4 *)(param_2 + 0x94) = *(undefined4 *)(lVar6 + 0xd4);
  *(undefined4 *)(param_2 + 0x98) = *(undefined4 *)(lVar6 + 0xd8);
  *(undefined4 *)(param_2 + 0x9c) = *(undefined4 *)(lVar6 + 0xdc);
  uVar4 = Aska::IParticleObject::GetAnimBlendModes() const(*(undefined8 *)(param_1 + 0xf48));
  *(undefined4 *)(param_2 + 0xb4) = uVar4;
  uVar2 = *(ushort *)(param_2 + 0xd9);
  uVar3 = uVar2 & 0x1f | (*(ushort *)(*(long *)(param_1 + 0xf48) + 500) >> 10 & 1) << 5;
  *(ushort *)(param_2 + 0xd9) = uVar2 & 0xffc0 | uVar3;
  uVar3 = uVar2 & 0x40 | uVar3 | (*(ushort *)(*(long *)(param_1 + 0xf48) + 500) >> 0xe & 1) << 7;
  *(ushort *)(param_2 + 0xd9) = uVar2 & 0xff00 | uVar3;
  *(ushort *)(param_2 + 0xd9) =
       *(ushort *)(*(long *)(param_1 + 0xf48) + 500) >> 6 & 0x200 | uVar2 & 0xfd00 | uVar3;
  *(undefined4 *)(param_2 + 0xb8) = *(undefined4 *)(*(long *)(param_1 + 0xf48) + 0x17c);
  *(undefined4 *)(param_2 + 0xbc) = *(undefined4 *)(*(long *)(param_1 + 0xf48) + 0x180);
  *(undefined4 *)(param_2 + 0xc0) = *(undefined4 *)(*(long *)(param_1 + 0xf48) + 0x184);
  *(undefined4 *)(param_2 + 0xc4) = *(undefined4 *)(*(long *)(param_1 + 0xf48) + 0x188);
  *(undefined4 *)(param_2 + 200) = *(undefined4 *)(*(long *)(param_1 + 0xf48) + 0x18c);
  *(undefined4 *)(param_2 + 0xd0) = *(undefined4 *)(param_1 + 0x1c8);
  return;
}

// ==== Aska::ParticleRenderableBase::SetupLod()
// vaddr 0x21a55cc | ghidra 0x22a55cc | size 216 | symbol _ZN4Aska22ParticleRenderableBase8SetupLodEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase8SetupLodEv(long param_1)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  if ((*(ushort *)(*(long *)(param_1 + 0xf48) + 500) >> 5 & 1) == 0) {
    return;
  }
  fVar5 = *(float *)(*(long *)(param_1 + 0xf48) + 0x108);
  fVar2 = *(float *)(param_1 + 0x870) - *(float *)(param_1 + 0x80);
  fVar3 = *(float *)(param_1 + 0x874) - *(float *)(param_1 + 0x84);
  fVar4 = *(float *)(param_1 + 0x878) - *(float *)(param_1 + 0x88);
  fVar3 = fVar2 * fVar2 + fVar3 * fVar3 + fVar4 * fVar4;
  fVar2 = SQRT(fVar3);
  if (NAN(fVar2)) {
    fVar2 = (float)sqrtf(fVar3);
  }
  if (0.0 < fVar5) {
    fVar2 = fVar2 / fVar5;
    if (8.0 <= fVar2) {
      uVar1 = 7;
      goto code_r0x022a5690;
    }
    if (4.0 <= fVar2) {
      uVar1 = 3;
      goto code_r0x022a5690;
    }
    if (2.0 <= fVar2) {
      uVar1 = 1;
      goto code_r0x022a5690;
    }
  }
  uVar1 = 0;
code_r0x022a5690:
  *(undefined4 *)(*(long *)(param_1 + 0xf48) + 0x1ec) = uVar1;
  return;
}

// ==== Aska::ParticleRenderableBase::SetRenderLayerID(unsigned char)
// vaddr 0x21a56a4 | ghidra 0x22a56a4 | size 104 | symbol _ZN4Aska22ParticleRenderableBase16SetRenderLayerIDEh | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase16SetRenderLayerIDEh(long param_1,uint param_2)

{
  undefined *puVar1;
  ulong uVar2;
  
  puVar1 = PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  if ((*(byte *)(param_1 + 0x2f0) & 1) != 0) {
    uVar2 = Aska::ObjectManager::IsReducedBufferLayer(int)(*(undefined8 *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688,
                            param_2 & 0xff);
    if (((uVar2 & 1) == 0) &&
       (uVar2 = Aska::ObjectManager::IsNeedZLayer(int)(*(undefined8 *)puVar1,param_2 & 0xff), (uVar2 & 1) == 0)) {
      param_2 = 8;
    }
  }
  (*(code *)PTR__ZN4Aska16RenderableObject16SetRenderLayerIDEh_02ca2050)(param_1,param_2);
  return;
}

// ==== Aska::ParticleRenderableBase::GetClassID(int) const
// vaddr 0x21a570c | ghidra 0x22a570c | size 68 | symbol _ZNK4Aska22ParticleRenderableBase10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska22ParticleRenderableBase10GetClassIDEi(undefined8 param_1,uint param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 < 3) {
    return *(undefined8 *)(&UNK_029d1290 + (long)(int)param_2 * 8);
  }
  uVar2 = 0xf000f001;
  if (param_2 != 4) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf000f001f002;
  if (param_2 != 3) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::ParticleRenderableBase::PerfCounterStart()
// vaddr 0x21a5750 | ghidra 0x22a5750 | size 4 | symbol _ZN4Aska22ParticleRenderableBase16PerfCounterStartEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase16PerfCounterStartEv(void)

{
  return;
}

// ==== Aska::ParticleRenderableBase::PerfCounterEnd()
// vaddr 0x21a5754 | ghidra 0x22a5754 | size 4 | symbol _ZN4Aska22ParticleRenderableBase14PerfCounterEndEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase14PerfCounterEndEv(void)

{
  return;
}

// ==== Aska::ParticleRenderableBase::SetRenderLayer(unsigned int, bool)
// vaddr 0x21a5758 | ghidra 0x22a5758 | size 212 | symbol _ZN4Aska22ParticleRenderableBase14SetRenderLayerEjb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase14SetRenderLayerEjb(long *param_1,uint param_2,ulong param_3)

{
  undefined4 uVar1;
  uint uVar2;
  undefined4 uStack_24;
  
  uStack_24 = 0;
  uVar2 = param_2;
  if (*(byte *)(param_1 + 0x117) - 3 < 2) {
    if (((param_3 & 1) != 0) && (uVar2 = 0x2001, param_2 != 4)) {
      uVar2 = 10;
    }
  }
  else if (*(byte *)(param_1 + 0x117) == 5) {
    uVar2 = 4;
  }
  if (0x1c < uVar2 && 2 < uVar2 - 0x2000) {
    uVar2 = 0x2000;
  }
  Aska::RenderLayerChooser::GetDefaultLogicalId(unsigned int, unsigned int, unsigned int*)(param_2,uVar2,&uStack_24);
  uVar1 = (**(code **)**(undefined8 **)PTR__ZN4Aska6Global22m_pIRenderLayerChooserE_02cc3bd0)
                    (*(undefined8 **)PTR__ZN4Aska6Global22m_pIRenderLayerChooserE_02cc3bd0,param_2,
                     uVar2,&uStack_24);
  *(char *)(param_1 + 0x5e) = (char)uStack_24;
  (**(code **)(*param_1 + 0x160))(param_1,uVar1);
  return;
}

// ==== Aska::ParticleRenderableBase::GetVBufSize() const
// vaddr 0x21a582c | ghidra 0x22a582c | size 36 | symbol _ZNK4Aska22ParticleRenderableBase11GetVBufSizeEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska22ParticleRenderableBase11GetVBufSizeEv(long param_1)

{
  undefined8 uVar1;
  
  if (*(int *)(param_1 + 0x8a8) != -1) {
    uVar1 = (*(code *)PTR__ZN4Aska22IParticleRenderManager24GetBufferMemoryFootprintEi_02cabd38)
                      (*(undefined8 *)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108);
    return uVar1;
  }
  return 0;
}

// ==== Aska::ParticleRenderableBase::Begin(int, int, int)
// vaddr 0x21a5850 | ghidra 0x22a5850 | size 180 | symbol _ZN4Aska22ParticleRenderableBase5BeginEiii | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska22ParticleRenderableBase5BeginEiii
               (long param_1,int param_2,int param_3,undefined4 param_4)

{
  bool bVar1;
  long lVar2;
  undefined8 uVar3;
  
  *(undefined8 *)(param_1 + 0xf28) = 0x7f7fffff7f7fffff;
  *(undefined8 *)(param_1 + 0xf20) = 0x7f7fffff7f7fffff;
  *(int *)(param_1 + 0x8ac) = param_3;
  *(undefined8 *)(param_1 + 0xf38) = 0xff7fffffff7fffff;
  *(undefined8 *)(param_1 + 0xf30) = 0xff7fffffff7fffff;
  if (*(char *)(param_1 + 0x8b8) == '\a') {
    bVar1 = false;
    if (*(long *)(param_1 + 0xf68) != 0) {
      if (*(char *)(*(long *)(param_1 + 0xf68) + 0x9c) != '\0') {
        return false;
      }
      uVar3 = Aska::MeshGenerator::LockInstances()();
      *(undefined8 *)(param_1 + 0xf70) = uVar3;
      *(undefined4 *)(param_1 + 0xf78) = 0;
      return true;
    }
  }
  else {
    if (*(int *)(param_1 + 0x8a8) == -1) {
      return false;
    }
    lVar2 = (**(code **)(**(long **)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108 + 0x28))
                      (*(long **)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108,
                       *(int *)(param_1 + 0x8a8),*(char *)(param_1 + 0x8b8),param_3 * param_2,
                       param_4);
    bVar1 = lVar2 != 0;
  }
  return bVar1;
}

// ==== Aska::ParticleRenderableBase::Fill(Aska::ParticleFillContext const*, Aska::ParticleContext const*, int)
// vaddr 0x21a5904 | ghidra 0x22a5904 | size 88 | symbol _ZN4Aska22ParticleRenderableBase4FillEPKNS_19ParticleFillContextEPKNS_15ParticleContextEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase4FillEPKNS_19ParticleFillContextEPKNS_15ParticleContextEi
               (long param_1,long param_2,undefined8 param_3,undefined4 param_4)

{
  if (*(short *)(param_2 + 0x18) == 7) {
    (*(code *)
      PTR__ZN4Aska22ParticleRenderableBase8FillMeshEPKNS_19ParticleFillContextEPKNS_15ParticleContextEi_02c93b88
    )(param_1,param_2,param_3,param_4);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x022a5958. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108 + 0x48))
            (*(long **)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108,
             *(undefined4 *)(param_1 + 0x8a8),param_2,param_3,param_4,param_1 + 0xf20,
             param_1 + 0xf30);
  return;
}

// ==== Aska::ParticleRenderableBase::FillMesh(Aska::ParticleFillContext const*, Aska::ParticleContext const*, int)
// vaddr 0x21a595c | ghidra 0x22a595c | size 1612 | symbol _ZN4Aska22ParticleRenderableBase8FillMeshEPKNS_19ParticleFillContextEPKNS_15ParticleContextEi | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska22ParticleRenderableBase8FillMeshEPKNS_19ParticleFillContextEPKNS_15ParticleContextEi
               (long param_1,undefined8 param_2,float *param_3,uint param_4)

{
  uint uVar1;
  float *pfVar2;
  uint uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  float fVar12;
  float fVar13;
  bool bVar14;
  uint uVar15;
  int iVar16;
  long lVar17;
  undefined8 *puVar18;
  undefined8 *puVar19;
  long lVar20;
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
  float fStack_1c0;
  float fStack_1bc;
  float fStack_1b8;
  float fStack_1b4;
  float fStack_1b0;
  float fStack_1ac;
  float fStack_1a8;
  float fStack_1a4;
  float fStack_1a0;
  float fStack_19c;
  float fStack_198;
  float fStack_194;
  undefined8 uStack_190;
  undefined8 uStack_188;
  float fStack_180;
  float fStack_17c;
  float fStack_178;
  float fStack_174;
  float fStack_170;
  float fStack_16c;
  float fStack_168;
  float fStack_164;
  float fStack_160;
  float fStack_15c;
  float fStack_158;
  float fStack_154;
  undefined8 uStack_150;
  undefined8 uStack_148;
  float fStack_140;
  float fStack_13c;
  float fStack_138;
  float fStack_134;
  float fStack_130;
  float fStack_12c;
  float fStack_128;
  float fStack_124;
  float fStack_120;
  float fStack_11c;
  float fStack_118;
  float fStack_114;
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
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  float fStack_b4;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  
  fVar13 = _UNK_02970cbc;
  fVar12 = _UNK_02964918;
  fVar27 = _UNK_02964914;
  fVar26 = _UNK_027ebdf4;
  fVar24 = _UNK_027e3fd0;
  uVar11 = _UNK_027dbb38;
  uVar10 = _UNK_027dbb30;
  uVar9 = _UNK_027dbb28;
  uVar8 = _UNK_027dbb20;
  uVar7 = _UNK_027dbb18;
  uVar6 = _UNK_027dbb10;
  uVar5 = _UNK_027dbb08;
  uVar4 = _UNK_027dbb00;
  lVar17 = *(long *)(param_1 + 0xf68);
  fStack_b0 = *(float *)(param_1 + 0xf20);
  iVar16 = *(int *)(param_1 + 0xf78);
  puVar18 = *(undefined8 **)(param_1 + 0xf70);
  fStack_ac = *(float *)(param_1 + 0xf24);
  uVar3 = *(int *)(lVar17 + 0x30) - iVar16;
  fStack_a8 = *(float *)(param_1 + 0xf28);
  uVar1 = param_4;
  if (uVar3 <= param_4) {
    uVar1 = uVar3;
  }
  fStack_a4 = *(float *)(param_1 + 0xf2c);
  fStack_c0 = *(float *)(param_1 + 0xf30);
  fStack_bc = *(float *)(param_1 + 0xf34);
  fStack_b8 = *(float *)(param_1 + 0xf38);
  fStack_b4 = *(float *)(param_1 + 0xf3c);
  if (0 < (int)uVar1) {
    uVar3 = (iVar16 + -1) - *(int *)(lVar17 + 0x30);
    if (uVar3 <= ~param_4) {
      uVar3 = ~param_4;
    }
    lVar20 = 1;
    puVar19 = puVar18;
    while( true ) {
      fVar28 = *param_3;
      pfVar2 = &fStack_b0;
      if (fVar28 <= fStack_b0) {
        pfVar2 = param_3;
      }
      fStack_b0 = *pfVar2;
      fVar25 = param_3[1];
      pfVar2 = &fStack_b0;
      if (fVar25 <= fStack_ac) {
        pfVar2 = param_3;
      }
      fStack_ac = pfVar2[1];
      fVar23 = param_3[2];
      pfVar2 = &fStack_b0;
      if (fVar23 <= fStack_a8) {
        pfVar2 = param_3;
      }
      fStack_a8 = pfVar2[2];
      pfVar2 = &fStack_b0;
      if (param_3[3] <= fStack_a4) {
        pfVar2 = param_3;
      }
      fStack_134 = fVar28 + 0.0;
      fStack_a4 = pfVar2[3];
      pfVar2 = &fStack_c0;
      if (fStack_c0 <= fVar28) {
        pfVar2 = param_3;
      }
      fStack_140 = fVar28 * 0.0 + 1.0;
      fStack_c0 = *pfVar2;
      pfVar2 = &fStack_c0;
      if (fStack_bc <= fVar25) {
        pfVar2 = param_3;
      }
      fStack_13c = fVar28 * 0.0 + 0.0;
      fStack_124 = fVar25 + 0.0;
      fStack_bc = pfVar2[1];
      pfVar2 = &fStack_c0;
      if (fStack_b8 <= fVar23) {
        pfVar2 = param_3;
      }
      fStack_130 = fVar25 * 0.0 + 0.0;
      fStack_b8 = pfVar2[2];
      pfVar2 = &fStack_c0;
      if (fStack_b4 <= param_3[3]) {
        pfVar2 = param_3;
      }
      fStack_b4 = pfVar2[3];
      uStack_f8 = uVar5;
      uStack_100 = uVar4;
      fStack_12c = fVar25 * 0.0 + 1.0;
      fStack_114 = fVar23 + 0.0;
      fStack_120 = fVar23 * 0.0 + 0.0;
      uStack_e8 = uVar7;
      uStack_f0 = uVar6;
      fStack_118 = fVar23 * 0.0 + 1.0;
      uStack_d8 = uVar9;
      uStack_e0 = uVar8;
      uStack_c8 = uVar11;
      uStack_d0 = uVar10;
      uStack_108 = uVar11;
      uStack_110 = uVar10;
      fStack_138 = fStack_13c;
      fStack_128 = fStack_130;
      fStack_11c = fStack_120;
      Aska::Matrix::Mul(Aska::Matrix const*)(&uStack_100,&fStack_140);
      if ((*(byte *)(*(long *)(param_1 + 0xf48) + 0x1f6) & 2) != 0) {
        Aska::Matrix::Mul(Aska::Matrix const*)(&uStack_100,param_1 + 0xf80);
      }
      if ((*(byte *)(param_1 + 0x8ba) >> 3 & 1) != 0) {
        uStack_148 = uVar11;
        uStack_150 = uVar10;
        fStack_180 = param_3[10];
        fStack_16c = param_3[0xb];
        fStack_158 = param_3[0xc];
        uStack_188 = uVar11;
        uStack_190 = uVar10;
        fStack_17c = fStack_180 * 0.0;
        fStack_170 = fStack_16c * 0.0;
        fStack_160 = fStack_158 * 0.0;
        uVar15 = (uint)(param_3[8] * fVar26);
        fVar28 = param_3[8] - (float)(int)uVar15 * fVar24;
        bVar14 = (uVar15 & 1) != 0;
        fVar25 = fVar28 * fVar28;
        if (bVar14) {
          fVar28 = -fVar28;
        }
        fVar29 = fVar25 * (fVar25 * (fVar25 * (fVar25 * (fVar25 * (fVar25 * (fVar27 - fVar25 * 
                                                  fVar13) + fVar12) + _UNK_0296491c) + _UNK_02964920
                                              ) + _UNK_02964924) + -0.5);
        fVar23 = -1.0 - fVar29;
        if (!bVar14) {
          fVar23 = fVar29 + 1.0;
        }
        fVar28 = fVar28 * (fVar25 * (fVar25 * (fVar25 * (fVar25 * (fVar25 * (fVar25 * (_UNK_0296492c
                                                                                      - fVar25 * 
                                                  _UNK_02970cc0) + _UNK_02964930) + _UNK_02964934) +
                                                  _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) +
                          1.0);
        fVar29 = fVar28 * 0.0;
        fVar30 = fVar23 * 0.0;
        fStack_1c0 = fVar23 - fVar29;
        fStack_1bc = fVar30 - fVar28;
        fStack_1b8 = fVar30 - fVar29;
        uVar15 = (uint)(param_3[9] * fVar26);
        fVar31 = param_3[9] - (float)(int)uVar15 * fVar24;
        bVar14 = (uVar15 & 1) != 0;
        fVar25 = fVar31;
        if (bVar14) {
          fVar25 = -fVar31;
        }
        fVar31 = fVar31 * fVar31;
        fStack_1a0 = (float)uVar8;
        fStack_19c = (float)((ulong)uVar8 >> 0x20);
        fStack_198 = (float)uVar9;
        fStack_194 = (float)((ulong)uVar9 >> 0x20);
        fVar21 = fVar31 * (fVar31 * (fVar31 * (fVar31 * (fVar31 * (fVar31 * (fVar27 - fVar31 * 
                                                  fVar13) + fVar12) + _UNK_0296491c) + _UNK_02964920
                                              ) + _UNK_02964924) + -0.5);
        fVar22 = -1.0 - fVar21;
        if (!bVar14) {
          fVar22 = fVar21 + 1.0;
        }
        fVar25 = fVar25 * (fVar31 * (fVar31 * (fVar31 * (fVar31 * (fVar31 * (fVar31 * (_UNK_0296492c
                                                                                      - fVar31 * 
                                                  _UNK_02970cc0) + _UNK_02964930) + _UNK_02964934) +
                                                  _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) +
                          1.0);
        fStack_1a4 = (fVar29 + fVar30) * fVar22;
        fVar31 = (fVar29 + fVar30) * fVar25;
        fStack_1b0 = (fVar28 + fVar30) * fVar22 - fStack_1a0 * fVar25;
        fStack_1ac = (fVar29 + fVar23) * fVar22 - fStack_19c * fVar25;
        fStack_1a8 = fStack_1a4 - fStack_198 * fVar25;
        fStack_1a4 = fStack_1a4 - fStack_194 * fVar25;
        _fStack_1a0 = CONCAT44((fVar29 + fVar23) * fVar25 + fStack_19c * fVar22,
                               (fVar28 + fVar30) * fVar25 + fStack_1a0 * fVar22);
        _fStack_198 = CONCAT44(fVar31 + fStack_194 * fVar22,fVar31 + fStack_198 * fVar22);
        fStack_1b4 = fStack_1b8;
        fStack_178 = fStack_17c;
        fStack_174 = fStack_17c;
        fStack_168 = fStack_170;
        fStack_164 = fStack_170;
        fStack_15c = fStack_160;
        fStack_154 = fStack_160;
        Aska::Matrix::Mul(Aska::Matrix const*)(&uStack_100,&fStack_1c0);
        Aska::Matrix::Mul(Aska::Matrix const*)(&uStack_100,&fStack_180);
      }
      puVar19[1] = uStack_f8;
      *puVar19 = uStack_100;
      puVar19[3] = uStack_e8;
      puVar19[2] = uStack_f0;
      puVar19[5] = uStack_d8;
      puVar19[4] = uStack_e0;
      *(float *)(puVar19 + 6) = param_3[4];
      *(float *)((long)puVar19 + 0x34) = param_3[5];
      *(float *)(puVar19 + 7) = param_3[6];
      *(float *)((long)puVar19 + 0x3c) = param_3[7];
      if ((int)uVar1 <= lVar20) break;
      param_3 = param_3 + 0x14;
      lVar20 = lVar20 + 1;
      puVar19 = puVar19 + 8;
    }
    iVar16 = *(int *)(param_1 + 0xf78);
    puVar18 = puVar18 + ((ulong)(-uVar3 - 2) + 1) * 8;
  }
  fVar24 = *(float *)(lVar17 + 0xb0);
  fVar27 = *(float *)(lVar17 + 0xb4);
  fVar26 = *(float *)(lVar17 + 0xb8);
  *(float *)(param_1 + 0xf2c) = fStack_a4;
  *(float *)(param_1 + 0xf20) = fStack_b0 - fVar24;
  *(float *)(param_1 + 0xf24) = fStack_ac - fVar27;
  *(float *)(param_1 + 0xf28) = fStack_a8 - fVar26;
  fVar24 = *(float *)(lVar17 + 0xb0);
  fVar26 = *(float *)(lVar17 + 0xb4);
  fVar27 = *(float *)(lVar17 + 0xb8);
  *(float *)(param_1 + 0xf3c) = fStack_b4;
  *(undefined8 **)(param_1 + 0xf70) = puVar18;
  *(float *)(param_1 + 0xf30) = fStack_c0 + fVar24;
  *(float *)(param_1 + 0xf34) = fStack_bc + fVar26;
  *(float *)(param_1 + 0xf38) = fStack_b8 + fVar27;
  *(uint *)(param_1 + 0xf78) = iVar16 + uVar1;
  return;
}

// ==== Aska::ParticleRenderableBase::End(bool)
// vaddr 0x21a5fa8 | ghidra 0x22a5fa8 | size 856 | symbol _ZN4Aska22ParticleRenderableBase3EndEb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase3EndEb(long param_1,uint param_2)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int iVar3;
  long lVar4;
  float *pfVar5;
  long lVar6;
  long *plVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  
  if (*(char *)(param_1 + 0x8b8) == '\a') {
    Aska::MeshGenerator::UnlockInstances(unsigned int)(*(undefined8 *)(param_1 + 0xf68),*(undefined4 *)(param_1 + 0xf78));
    fVar8 = *(float *)(param_1 + 0xf30);
    fVar9 = *(float *)(param_1 + 0xf20);
    fVar10 = *(float *)(param_1 + 0xf34);
    fVar11 = *(float *)(param_1 + 0xf24);
    fVar13 = *(float *)(param_1 + 0xf38);
    fVar15 = *(float *)(param_1 + 0xf28);
    lVar6 = param_1 + 0xa50;
    lVar4 = lVar6 + (ulong)*(uint *)(param_1 + 0xf58) * 0xe0;
    fVar12 = (fVar8 + fVar9) * 0.5;
    fVar14 = (fVar10 + fVar11) * 0.5;
    fVar16 = (fVar13 + fVar15) * 0.5;
    *(undefined4 *)(lVar4 + 0x1c) = 0x3f800000;
    *(float *)(lVar4 + 0x10) = fVar12;
    *(float *)(lVar4 + 0x14) = fVar14;
    *(float *)(lVar4 + 0x18) = fVar16;
    fVar8 = (fVar8 - fVar9) * 0.5;
    fVar9 = (fVar10 - fVar11) * 0.5;
    fVar10 = (fVar13 - fVar15) * 0.5;
    lVar4 = lVar6 + (ulong)*(uint *)(param_1 + 0xf58) * 0xe0;
    *(float *)(lVar4 + 0x20) = fVar8;
    *(float *)(lVar4 + 0x24) = fVar9;
    *(float *)(lVar4 + 0x28) = fVar10;
    *(undefined4 *)(lVar4 + 0x2c) = 0x3f800000;
    pfVar5 = (float *)(lVar6 + (ulong)*(uint *)(param_1 + 0xf58) * 0xe0);
    *pfVar5 = fVar12;
    pfVar5[1] = fVar14;
    pfVar5[2] = fVar16;
    pfVar5[3] = 1.0;
    Aska::Vector::ApplyMatrix(Aska::Matrix const*)(lVar6 + (ulong)*(uint *)(param_1 + 0xf58) * 0xe0,
                    *(undefined8 *)(param_1 + 0x120));
    fVar9 = fVar8 * fVar8 + fVar9 * fVar9 + fVar10 * fVar10;
    fVar8 = SQRT(fVar9);
    if (NAN(fVar8)) {
      fVar8 = (float)sqrtf(fVar9);
    }
    *(float *)(param_1 + (ulong)*(uint *)(param_1 + 0xf58) * 0xe0 + 0xa5c) = fVar8;
    *(byte *)(param_1 + 0xf5c) = *(byte *)(param_1 + 0xf5c) | 0x40;
    goto code_r0x022a62bc;
  }
  plVar7 = *(long **)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108;
  uVar2 = (**(code **)(*plVar7 + 0x20))(plVar7,*(undefined4 *)(param_1 + 0x8a8),param_2 & 1);
  uVar1 = Aska::IParticleRenderManager::FlipBuffer(int)(plVar7,*(undefined4 *)(param_1 + 0x8a8));
  *(undefined1 *)(param_1 + 0xa50 + (ulong)*(uint *)(param_1 + 0xf58) * 0xe0 + 0xd8) = uVar1;
  lVar6 = param_1 + 0xa50 + (ulong)*(uint *)(param_1 + 0xf58) * 0xe0;
  *(ushort *)(lVar6 + 0xd9) = *(ushort *)(lVar6 + 0xd9) | 0x100;
  if (*(byte *)(param_1 + 0x8b8) - 3 < 4) {
    fVar8 = (float)Aska::IParticleObject::GetAnimationSize() const(*(undefined8 *)(param_1 + 0xf48));
code_r0x022a617c:
    fVar9 = *(float *)(param_1 + 0xf20) - fVar8;
    fVar11 = *(float *)(param_1 + 0xf24) - fVar8;
    fVar13 = *(float *)(param_1 + 0xf28) - fVar8;
    fVar10 = fVar8 + *(float *)(param_1 + 0xf30);
    fVar12 = fVar8 + *(float *)(param_1 + 0xf34);
    fVar8 = fVar8 + *(float *)(param_1 + 0xf38);
    *(float *)(param_1 + 0xf20) = fVar9;
    *(float *)(param_1 + 0xf24) = fVar11;
    *(float *)(param_1 + 0xf28) = fVar13;
    *(float *)(param_1 + 0xf30) = fVar10;
    *(float *)(param_1 + 0xf34) = fVar12;
    *(float *)(param_1 + 0xf38) = fVar8;
  }
  else {
    if (*(byte *)(param_1 + 0x8b8) - 1 < 2) {
      fVar9 = *(float *)(*(long *)(param_1 + 0xf48) + 0xe8);
      fVar8 = *(float *)(param_1 + (ulong)*(uint *)(param_1 + 0xf58) * 0xe0 + 0xaf0);
      if (fVar8 < fVar9) {
        fVar8 = fVar9;
      }
      goto code_r0x022a617c;
    }
    fVar10 = *(float *)(param_1 + 0xf30);
    fVar9 = *(float *)(param_1 + 0xf20);
    fVar12 = *(float *)(param_1 + 0xf34);
    fVar11 = *(float *)(param_1 + 0xf24);
    fVar8 = *(float *)(param_1 + 0xf38);
    fVar13 = *(float *)(param_1 + 0xf28);
  }
  lVar6 = param_1 + 0xa50;
  fVar14 = (fVar10 + fVar9) * 0.5;
  fVar15 = (fVar12 + fVar11) * 0.5;
  fVar16 = (fVar8 + fVar13) * 0.5;
  lVar4 = lVar6 + (ulong)*(uint *)(param_1 + 0xf58) * 0xe0;
  *(float *)(lVar4 + 0x10) = fVar14;
  *(float *)(lVar4 + 0x14) = fVar15;
  *(float *)(lVar4 + 0x18) = fVar16;
  *(undefined4 *)(lVar4 + 0x1c) = 0x3f800000;
  fVar9 = (fVar10 - fVar9) * 0.5;
  fVar10 = (fVar12 - fVar11) * 0.5;
  fVar8 = (fVar8 - fVar13) * 0.5;
  lVar4 = lVar6 + (ulong)*(uint *)(param_1 + 0xf58) * 0xe0;
  *(float *)(lVar4 + 0x20) = fVar9;
  *(float *)(lVar4 + 0x24) = fVar10;
  *(float *)(lVar4 + 0x28) = fVar8;
  *(undefined4 *)(lVar4 + 0x2c) = 0x3f800000;
  pfVar5 = (float *)(lVar6 + (ulong)*(uint *)(param_1 + 0xf58) * 0xe0);
  *pfVar5 = fVar14;
  pfVar5[1] = fVar15;
  pfVar5[2] = fVar16;
  pfVar5[3] = 1.0;
  Aska::Vector::ApplyMatrix(Aska::Matrix const*)(lVar6 + (ulong)*(uint *)(param_1 + 0xf58) * 0xe0,*(undefined8 *)(param_1 + 0x120))
  ;
  fVar9 = fVar9 * fVar9 + fVar10 * fVar10 + fVar8 * fVar8;
  fVar8 = SQRT(fVar9);
  if (NAN(fVar8)) {
    fVar8 = (float)sqrtf(fVar9);
  }
  *(float *)(param_1 + (ulong)*(uint *)(param_1 + 0xf58) * 0xe0 + 0xa5c) = fVar8;
  *(byte *)(param_1 + 0xf5c) = *(byte *)(param_1 + 0xf5c) | 0x40;
  if ((param_2 & 1) == 0) {
    iVar3 = *(int *)(param_1 + 0x8b0) + 1;
  }
  else {
    iVar3 = 0;
  }
  *(int *)(param_1 + 0x8b0) = iVar3;
  *(undefined4 *)(param_1 + 0x8b4) = uVar2;
code_r0x022a62bc:
  DataMemoryBarrier(2,3);
  *(uint *)(param_1 + 0xf58) = *(uint *)(param_1 + 0xf58) ^ 1;
  return;
}

// ==== Aska::ParticleRenderableBase::NotifyTexture()
// vaddr 0x21a6300 | ghidra 0x22a6300 | size 320 | symbol _ZN4Aska22ParticleRenderableBase13NotifyTextureEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase13NotifyTextureEv(long param_1)

{
  long *plVar1;
  undefined4 uVar2;
  ulong uVar3;
  code *pcVar4;
  ulong uStack_28;
  
  plVar1 = (long *)(*(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0 + 0x2a8);
  if (*(long *)(param_1 + 0x9d0) != 0) {
    uStack_28 = *(ulong *)(param_1 + 0x9c0) & 0xffffffffffffff80;
    pcVar4 = *(code **)(*plVar1 + 0x78);
    uVar2 = (**(code **)(*plVar1 + 0x60))(plVar1,&uStack_28);
    uVar3 = (*pcVar4)(plVar1,&uStack_28,uVar2);
    if ((uVar3 & 1) != 0) {
      *(undefined8 *)(param_1 + 0x9d0) = 0;
    }
  }
  if (*(long *)(param_1 + 0x9f0) != 0) {
    uStack_28 = *(ulong *)(param_1 + 0x9e0) & 0xffffffffffffff80;
    pcVar4 = *(code **)(*plVar1 + 0x78);
    uVar2 = (**(code **)(*plVar1 + 0x60))(plVar1,&uStack_28);
    uVar3 = (*pcVar4)(plVar1,&uStack_28,uVar2);
    if ((uVar3 & 1) != 0) {
      *(undefined8 *)(param_1 + 0x9f0) = 0;
    }
  }
  if (*(long *)(param_1 + 0xa10) != 0) {
    uStack_28 = *(ulong *)(param_1 + 0xa00) & 0xffffffffffffff80;
    pcVar4 = *(code **)(*plVar1 + 0x78);
    uVar2 = (**(code **)(*plVar1 + 0x60))(plVar1,&uStack_28);
    uVar3 = (*pcVar4)(plVar1,&uStack_28,uVar2);
    if ((uVar3 & 1) != 0) {
      *(undefined8 *)(param_1 + 0xa10) = 0;
    }
  }
  if (*(long *)(param_1 + 0xa30) != 0) {
    uStack_28 = *(ulong *)(param_1 + 0xa20) & 0xffffffffffffff80;
    pcVar4 = *(code **)(*plVar1 + 0x78);
    uVar2 = (**(code **)(*plVar1 + 0x60))(plVar1,&uStack_28);
    uVar3 = (*pcVar4)(plVar1,&uStack_28,uVar2);
    if ((uVar3 & 1) != 0) {
      *(undefined8 *)(param_1 + 0xa30) = 0;
    }
  }
  return;
}

// ==== non-virtual thunk to Aska::ParticleRenderableBase::NotifyTexture()
// vaddr 0x21a6440 | ghidra 0x22a6440 | size 8 | symbol _ZThn776_N4Aska22ParticleRenderableBase13NotifyTextureEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn776_N4Aska22ParticleRenderableBase13NotifyTextureEv(long param_1)

{
  (*(code *)PTR__ZN4Aska22ParticleRenderableBase13NotifyTextureEv_02c9a258)(param_1 + -0x308);
  return;
}

// ==== Aska::ParticleRenderableBase::ReleaseShaderCache()
// vaddr 0x21a6448 | ghidra 0x22a6448 | size 124 | symbol _ZN4Aska22ParticleRenderableBase18ReleaseShaderCacheEv | lib libSOA-3.7.0.so | 2026-10-08
int _ZN4Aska22ParticleRenderableBase18ReleaseShaderCacheEv(long param_1)

{
  int iVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  
  lVar3 = *(long *)PTR__ZN4Aska6Global20m_pShaderLinkManagerE_02cb93f8;
  if (*(long *)(param_1 + 0xa48) == 0) {
    iVar1 = 0;
    lVar4 = *(long *)(param_1 + 0xa40);
  }
  else {
    iVar1 = Aska::AHSLCacheManagerV2::L1::ReleaseAndDeleteShaderCache(Aska::ShaderCache*)(lVar3 + 0x38);
    *(undefined8 *)(param_1 + 0xa48) = 0;
    lVar4 = *(long *)(param_1 + 0xa40);
  }
  if (lVar4 != 0) {
    iVar2 = Aska::AHSLCacheManagerV2::L1::ReleaseAndDeleteShaderCache(Aska::ShaderCache*)(lVar3 + 0x38,*(undefined8 *)(lVar4 + 0x10));
    iVar1 = iVar2 + iVar1;
    *(undefined8 *)(param_1 + 0xa40) = 0;
  }
  *(byte *)(param_1 + 0xf5c) = *(byte *)(param_1 + 0xf5c) | 1;
  return iVar1;
}

// ==== Aska::ParticleRenderableBase::PreliminarilyPrepare(Aska::LightManager*)
// vaddr 0x21a64c4 | ghidra 0x22a64c4 | size 480 | symbol _ZN4Aska22ParticleRenderableBase20PreliminarilyPrepareEPNS_12LightManagerE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska22ParticleRenderableBase20PreliminarilyPrepareEPNS_12LightManagerE(long param_1)

{
  long lVar1;
  float fVar2;
  long lVar3;
  byte bVar4;
  long lVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined1 auVar10 [16];
  
  *(byte *)(param_1 + 0xf5c) = *(byte *)(param_1 + 0xf5c) & 0xf9;
  DataMemoryBarrier(2,3);
  if (*(int *)(param_1 + 0x1ac) == 0) {
    return 0;
  }
  DataMemoryBarrier(2,3);
  fVar6 = (float)*(undefined8 *)(param_1 + 0x270);
  fVar7 = (float)((ulong)*(undefined8 *)(param_1 + 0x270) >> 0x20);
  fVar8 = (float)*(undefined8 *)(param_1 + 0x278);
  fVar9 = (float)((ulong)*(undefined8 *)(param_1 + 0x278) >> 0x20);
  *(undefined4 *)(param_1 + 0x1c0) = *(undefined4 *)(param_1 + 0x1ac);
  if ((*(float *)(param_1 + 0x88c) == fVar9 &&
       (*(float *)(param_1 + 0x888) == fVar8 &&
       (*(float *)(param_1 + 0x880) == fVar6 && *(float *)(param_1 + 0x884) == fVar7))) &&
     (fVar2 = *(float *)(param_1 + 0x280),
     (((float)((ulong)*(undefined8 *)(param_1 + 0x890) >> 0x20) == *(float *)(param_1 + 0x284) &&
      (float)*(undefined8 *)(param_1 + 0x890) == fVar2) &&
     (float)*(undefined8 *)(param_1 + 0x898) == *(float *)(param_1 + 0x288)) &&
     (float)((ulong)*(undefined8 *)(param_1 + 0x898) >> 0x20) == *(float *)(param_1 + 0x28c)))
  goto code_r0x022a65e4;
  auVar10 = NEON_fmov(0xbf800000,4);
  if (0.0001 < ABS(fVar9 + auVar10._12_4_) ||
      (0.0001 < ABS(fVar8 + auVar10._8_4_) ||
      (0.0001 < ABS(fVar6 + auVar10._0_4_) || 0.0001 < ABS(fVar7 + auVar10._4_4_)))) {
    fVar2 = *(float *)(param_1 + 0x280);
code_r0x022a65d4:
    bVar4 = *(byte *)(param_1 + 0xf5c) | 8;
  }
  else {
    fVar2 = *(float *)(param_1 + 0x280);
    if (((0.0001 < ABS(*(float *)(param_1 + 0x284)) || 0.0001 < ABS(fVar2)) ||
        0.0001 < ABS(*(float *)(param_1 + 0x288))) || 0.0001 < ABS(*(float *)(param_1 + 0x28c)))
    goto code_r0x022a65d4;
    bVar4 = *(byte *)(param_1 + 0xf5c) & 0xf7;
  }
  *(byte *)(param_1 + 0xf5c) = bVar4 | 1;
code_r0x022a65e4:
  *(float *)(param_1 + 0x880) = fVar6;
  *(float *)(param_1 + 0x890) = fVar2;
  lVar1 = *(long *)(param_1 + 0xf48);
  *(undefined4 *)(param_1 + 0x884) = *(undefined4 *)(param_1 + 0x274);
  *(undefined4 *)(param_1 + 0x888) = *(undefined4 *)(param_1 + 0x278);
  *(undefined4 *)(param_1 + 0x88c) = *(undefined4 *)(param_1 + 0x27c);
  *(undefined4 *)(param_1 + 0x894) = *(undefined4 *)(param_1 + 0x284);
  *(undefined4 *)(param_1 + 0x898) = *(undefined4 *)(param_1 + 0x288);
  *(undefined4 *)(param_1 + 0x89c) = *(undefined4 *)(param_1 + 0x28c);
  if (lVar1 != 0) {
    lVar3 = *(long *)(lVar1 + 0x140);
    if (lVar3 == 0) {
      lVar5 = 0;
    }
    else {
      lVar5 = *(long *)(lVar3 + 0x10);
    }
    if (*(long *)(param_1 + 0x9c0) != lVar5) {
      *(long *)(param_1 + 0x9c0) = lVar5;
      *(undefined8 *)(param_1 + 0x9d0) = 0;
      lVar3 = *(long *)(lVar1 + 0x140);
    }
    lVar5 = 0;
    if (lVar3 != 0) {
      lVar5 = *(long *)(lVar3 + 0x18);
    }
    if (*(long *)(param_1 + 0x9e0) != lVar5) {
      *(long *)(param_1 + 0x9e0) = lVar5;
      *(undefined8 *)(param_1 + 0x9f0) = 0;
    }
    if (*(long *)(param_1 + 0xa00) != *(long *)(lVar1 + 0x110)) {
      *(long *)(param_1 + 0xa00) = *(long *)(lVar1 + 0x110);
      *(undefined8 *)(param_1 + 0xa10) = 0;
    }
    if (*(long *)(param_1 + 0xa20) != 0) {
      *(undefined8 *)(param_1 + 0xa20) = 0;
      *(undefined8 *)(param_1 + 0xa30) = 0;
    }
  }
  *(undefined1 *)(param_1 + 0x8b9) = *(undefined1 *)(param_1 + 0x1b7);
  return 1;
}

// ==== Aska::ParticleRenderableBase::PrepareForRendering(Aska::RENDERINFO const*)
// vaddr 0x21a66a4 | ghidra 0x22a66a4 | size 4368 | symbol _ZN4Aska22ParticleRenderableBase19PrepareForRenderingEPKNS_10RENDERINFOE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN4Aska22ParticleRenderableBase19PrepareForRenderingEPKNS_10RENDERINFOE
               (long param_1,short *param_2)

{
  long lVar1;
  ushort *puVar2;
  int *piVar3;
  float *pfVar4;
  uint uVar5;
  long lVar6;
  uint uVar7;
  char cVar8;
  byte bVar9;
  ushort uVar10;
  char cVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined7 uVar15;
  undefined *puVar16;
  ulong uVar17;
  ulong uVar18;
  bool bVar19;
  int iVar20;
  undefined8 uVar21;
  long lVar22;
  byte bVar23;
  long lVar24;
  ushort uVar25;
  undefined2 uVar26;
  ulong *puVar27;
  undefined8 *puVar28;
  long lVar29;
  float *pfVar30;
  undefined8 *puVar31;
  long lVar32;
  long lVar33;
  ulong uVar34;
  ulong uVar35;
  long lVar36;
  float fVar37;
  float fVar38;
  ulong uVar39;
  ulong uVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  float fVar47;
  undefined8 uStack_4c0;
  undefined8 uStack_4b8;
  undefined8 uStack_4b0;
  ulong uStack_4a8;
  undefined8 uStack_4a0;
  undefined8 uStack_498;
  undefined8 uStack_490;
  undefined8 uStack_488;
  undefined8 uStack_480;
  undefined8 uStack_478;
  undefined8 uStack_470;
  undefined8 uStack_468;
  undefined8 uStack_460;
  undefined8 uStack_458;
  float afStack_400 [6];
  float fStack_3e8;
  float fStack_3e4;
  float fStack_3d0;
  float fStack_3cc;
  float fStack_3c8;
  float fStack_3c4;
  float fStack_3b0;
  float fStack_3ac;
  float fStack_3a8;
  float fStack_3a4;
  float fStack_390;
  float fStack_38c;
  float fStack_388;
  float fStack_384;
  float fStack_360;
  float fStack_35c;
  float fStack_358;
  float fStack_354;
  float fStack_310;
  float fStack_30c;
  float fStack_308;
  float fStack_304;
  float fStack_2c0;
  float fStack_2bc;
  float fStack_2b8;
  float fStack_2b4;
  float fStack_270;
  float fStack_26c;
  float fStack_268;
  float fStack_264;
  undefined1 auStack_240 [16];
  float fStack_230;
  float fStack_22c;
  float fStack_228;
  float fStack_224;
  long lStack_190;
  byte bStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  ulong uStack_170;
  ulong uStack_168;
  ulong uStack_160;
  ulong uStack_158;
  ulong uStack_150;
  ulong uStack_148;
  long lStack_138;
  ulong uStack_130;
  ulong uStack_128;
  ulong uStack_120;
  ulong uStack_118;
  undefined8 uStack_110;
  ulong uStack_108;
  ulong uStack_100;
  ulong uStack_f8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  
  uVar34 = _UNK_027dbb38;
  uVar35 = _UNK_027dbb30;
  if (*(int *)(param_1 + 0xf78) != 0) {
    lVar24 = *(long *)(param_2 + 8);
    uVar12 = *(undefined8 *)(lVar24 + 0x138);
    uVar21 = *(undefined8 *)(lVar24 + 0x130);
    uVar14 = *(undefined8 *)(lVar24 + 0x148);
    uVar13 = *(undefined8 *)(lVar24 + 0x140);
    uVar40 = *(ulong *)(lVar24 + 0x158);
    uVar39 = *(ulong *)(lVar24 + 0x150);
    *(ulong *)(param_1 + 0xf88) = uVar39 & 0xffffffff;
    *(ulong *)(param_1 + 0xf80) = CONCAT44((int)uVar13,(int)uVar21);
    *(ulong *)(param_1 + 0xf98) = uVar39 >> 0x20;
    *(ulong *)(param_1 + 0xf90) =
         CONCAT44((int)((ulong)uVar13 >> 0x20),(int)((ulong)uVar21 >> 0x20));
    *(ulong *)(param_1 + 0xfa8) = uVar40 & 0xffffffff;
    *(ulong *)(param_1 + 4000) = CONCAT44((int)uVar14,(int)uVar12);
    *(ulong *)(param_1 + 0xfb8) = uVar34;
    *(ulong *)(param_1 + 0xfb0) = uVar35;
  }
  if (*(int *)(param_1 + 0x8b0) < 1) {
code_r0x022a7008:
    bVar19 = false;
  }
  else {
    lVar24 = *(long *)(param_2 + 4);
    lVar6 = *(long *)(param_2 + 8);
    puVar28 = *(undefined8 **)(param_1 + 0x120);
    DataMemoryBarrier(2,3);
    uVar7 = *(uint *)(param_1 + 0x1b0);
    cVar8 = *(char *)(lVar6 + 0xeb1);
    if (cVar8 == '\x01') {
code_r0x022a678c:
      lVar36 = 1;
    }
    else {
      if (cVar8 == -1) {
        cVar11 = *PTR__ZN4Aska6Camera15m_cActiveTileNoE_02cbb2c8;
      }
      else {
        cVar11 = *PTR__ZN4Aska6Camera15m_cActiveTileNoE_02cbb2c8;
        if (cVar8 <= cVar11) goto code_r0x022a678c;
      }
      lVar36 = (long)cVar11 + 2;
    }
    lVar36 = lVar6 + lVar36 * 0x40;
    puVar31 = (undefined8 *)(lVar36 + 0x9e0);
    if ((uVar7 >> 0x11 & 1) != 0) {
      uStack_488 = _UNK_027dbb08;
      uStack_490 = _UNK_027dbb00;
      uStack_478 = _UNK_027dbb18;
      uStack_480 = _UNK_027dbb10;
      fVar46 = 0.0;
      uStack_468 = _UNK_027dbb28;
      uStack_470 = _UNK_027dbb20;
      uStack_458 = _UNK_027dbb38;
      uStack_460 = _UNK_027dbb30;
      uStack_b8 = *(undefined8 *)(lVar36 + 0x9e8);
      uStack_c0 = *puVar31;
      uStack_a8 = *(undefined8 *)(lVar36 + 0x9f8);
      uStack_b0 = *(undefined8 *)(lVar36 + 0x9f0);
      uStack_98 = *(undefined8 *)(lVar36 + 0xa08);
      uStack_a0 = *(undefined8 *)(lVar36 + 0xa00);
      uStack_88 = *(undefined8 *)(lVar36 + 0xa18);
      uStack_90 = *(undefined8 *)(lVar36 + 0xa10);
      if ((uVar7 >> 0x10 & 1) != 0) {
        fVar46 = *(float *)(param_1 + 0x1c4);
      }
      fVar47 = *(float *)(param_1 + 0x1c8);
      fVar37 = (float)Aska::RenderableObject::GetShallowestZ(int) const(param_1,(long)*param_2);
      fVar38 = (float)Aska::RenderableObject::GetDeepestZ(int) const(param_1,(long)*param_2);
      fVar46 = fVar46 + fVar37 + ((fVar46 + fVar38) - (fVar46 + fVar37)) * 0.5;
      uStack_488 = uStack_488 & 0xffffffff;
      uStack_478 = uStack_478 & 0xffffffff;
      uStack_468 = CONCAT44((*(float *)(lVar6 + 0x988) +
                            *(float *)(lVar6 + 0x98c) / (fVar46 - fVar47)) -
                            (*(float *)(lVar6 + 0x988) + *(float *)(lVar6 + 0x98c) / fVar46),
                            (float)uStack_468);
      puVar31 = &uStack_c0;
      Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_c0,&uStack_490);
    }
    uVar21 = *puVar31;
    *(undefined8 *)(lVar24 + 0x68) = puVar31[1];
    *(undefined8 *)(lVar24 + 0x60) = uVar21;
    uVar21 = puVar31[2];
    *(undefined8 *)(lVar24 + 0x78) = puVar31[3];
    *(undefined8 *)(lVar24 + 0x70) = uVar21;
    uVar21 = puVar31[4];
    *(undefined8 *)(lVar24 + 0x88) = puVar31[5];
    *(undefined8 *)(lVar24 + 0x80) = uVar21;
    uVar21 = puVar31[6];
    *(undefined8 *)(lVar24 + 0x98) = puVar31[7];
    *(undefined8 *)(lVar24 + 0x90) = uVar21;
    Aska::Matrix::Mul(Aska::Matrix const*)((undefined8 *)(lVar24 + 0x60),puVar28);
    uVar21 = *puVar28;
    *(undefined8 *)(lVar24 + 0xe8) = puVar28[1];
    *(undefined8 *)(lVar24 + 0xe0) = uVar21;
    uVar21 = puVar28[2];
    *(undefined8 *)(lVar24 + 0xf8) = puVar28[3];
    *(undefined8 *)(lVar24 + 0xf0) = uVar21;
    uVar21 = puVar28[4];
    *(undefined8 *)(lVar24 + 0x108) = puVar28[5];
    *(undefined8 *)(lVar24 + 0x100) = uVar21;
    uVar21 = *(undefined8 *)(lVar6 + 0x130);
    *(undefined8 *)(lVar24 + 0x178) = *(undefined8 *)(lVar6 + 0x138);
    *(undefined8 *)(lVar24 + 0x170) = uVar21;
    uVar21 = *(undefined8 *)(lVar6 + 0x140);
    *(undefined8 *)(lVar24 + 0x188) = *(undefined8 *)(lVar6 + 0x148);
    *(undefined8 *)(lVar24 + 0x180) = uVar21;
    uVar21 = *(undefined8 *)(lVar6 + 0x150);
    *(undefined8 *)(lVar24 + 0x198) = *(undefined8 *)(lVar6 + 0x158);
    *(undefined8 *)(lVar24 + 400) = uVar21;
    uVar21 = *puVar31;
    *(undefined8 *)(lVar24 + 0xa8) = puVar31[1];
    *(undefined8 *)(lVar24 + 0xa0) = uVar21;
    uVar21 = puVar31[2];
    *(undefined8 *)(lVar24 + 0xb8) = puVar31[3];
    *(undefined8 *)(lVar24 + 0xb0) = uVar21;
    uVar21 = puVar31[4];
    *(undefined8 *)(lVar24 + 200) = puVar31[5];
    *(undefined8 *)(lVar24 + 0xc0) = uVar21;
    uVar21 = puVar31[6];
    *(undefined8 *)(lVar24 + 0xd8) = puVar31[7];
    *(undefined8 *)(lVar24 + 0xd0) = uVar21;
    *(undefined4 *)(lVar24 + 0x110) = *(undefined4 *)(lVar6 + 0xc60);
    *(undefined4 *)(lVar24 + 0x114) = *(undefined4 *)(lVar6 + 0xc64);
    *(undefined4 *)(lVar24 + 0x118) = *(undefined4 *)(lVar6 + 0xc68);
    *(undefined4 *)(lVar24 + 0x11c) = *(undefined4 *)(lVar6 + 0xc6c);
    *(undefined4 *)(param_1 + 0x870) = *(undefined4 *)(lVar6 + 0xc60);
    *(undefined4 *)(param_1 + 0x874) = *(undefined4 *)(lVar6 + 0xc64);
    *(undefined4 *)(param_1 + 0x878) = *(undefined4 *)(lVar6 + 0xc68);
    *(undefined4 *)(param_1 + 0x87c) = *(undefined4 *)(lVar6 + 0xc6c);
    if ((*(byte *)(param_1 + 0xf5c) >> 3 & 1) != 0) {
      *(undefined4 *)(lVar24 + 0x120) = *(undefined4 *)(param_1 + 0x880);
      *(undefined4 *)(lVar24 + 0x124) = *(undefined4 *)(param_1 + 0x884);
      *(undefined4 *)(lVar24 + 0x128) = *(undefined4 *)(param_1 + 0x888);
      *(undefined4 *)(lVar24 + 300) = *(undefined4 *)(param_1 + 0x88c);
      *(undefined4 *)(lVar24 + 0x130) = *(undefined4 *)(param_1 + 0x890);
      *(undefined4 *)(lVar24 + 0x134) = *(undefined4 *)(param_1 + 0x894);
      *(undefined4 *)(lVar24 + 0x138) = *(undefined4 *)(param_1 + 0x898);
      *(undefined4 *)(lVar24 + 0x13c) = *(undefined4 *)(param_1 + 0x89c);
    }
    if ((*(char *)(*(long *)(param_2 + 8) + 0xeb2) == '\0') ||
       ((*(byte *)(param_1 + 0x19b) & 1) == 0)) {
      uVar21 = Aska::Camera::GetFogConst()(lVar6);
      bVar23 = 0;
      *(undefined8 *)(lVar24 + 0x150) = uVar21;
    }
    else {
      *(uint *)(lVar24 + 0x58) = *(uint *)(lVar24 + 0x58) | 1;
      uVar21 = Aska::Camera::GetFogConst()(lVar6);
      *(undefined8 *)(lVar24 + 0x150) = uVar21;
      bVar23 = *(byte *)(*(long *)(param_2 + 8) + 0xeb2);
    }
    bVar9 = *(byte *)(param_1 + 0xf5c);
    if ((bVar9 >> 4 & 3) != bVar23) {
      *(byte *)(param_1 + 0xf5c) = bVar9 & 0xc0 | bVar9 & 0xe | (bVar23 & 3) << 4 | 1;
    }
    uVar5 = *(uint *)(param_1 + 0xf58) ^ 1;
    uVar35 = (ulong)uVar5;
    *(byte *)(lVar24 + 10) = *(byte *)(lVar24 + 10) & 0xfc | (byte)uVar5 & 3;
    lVar36 = param_1 + (ulong)uVar5 * 0xe0;
    if ((*(byte *)(lVar36 + 0xb29) >> 1 & 1) == 0) {
      lVar29 = 0;
      bVar19 = false;
    }
    else {
      lVar29 = Aska::FrameTextureModifier::GetTexture(unsigned long, int, int, int)(0x737a407a00000000,(long)*param_2,(long)(char)param_2[1],
                               *(undefined1 *)(param_1 + 0x1b7));
      if (lVar29 == 0) {
        lVar29 = Aska::ObjectManager::GetNoTexture() const(*(undefined8 *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688);
      }
      bVar19 = true;
    }
    if (*(char *)(param_1 + 0x8b8) == '\x05') {
      lVar22 = Aska::FrameTextureModifier::GetTexture(unsigned long, int, int, int)(0x7274406300000000,(long)*param_2,(long)(char)param_2[1],
                               *(undefined1 *)(param_1 + 0x1b7));
      if (lVar22 == 0) {
        lVar22 = Aska::ObjectManager::GetNoTexture() const(*(undefined8 *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688);
      }
      bVar19 = true;
    }
    else {
      lVar22 = 0;
    }
    uVar5 = *(uint *)(lVar24 + 0x58) | 4;
    if ((uVar7 & 0x100) == 0) {
      uVar5 = *(uint *)(lVar24 + 0x58) & 0xfffffffb;
    }
    *(uint *)(lVar24 + 0x58) = uVar5;
    *(byte *)(lVar24 + 0xb) = *(byte *)(lVar24 + 0xb) & 0xfc | *(byte *)((long)param_2 + 3) >> 3 & 3
    ;
    lVar24 = Aska::RenderContext::AllocBatch(int)(lVar24,1);
    memset((undefined8 *)(lVar24 + 0x20),0,0x98);
    lVar32 = *(long *)(param_1 + 0x9c0);
    if (lVar32 == 0) {
code_r0x022a6b68:
      uVar21 = 0;
    }
    else {
      lVar33 = *(long *)(param_1 + 0x9d0);
      if (lVar33 == 0) {
        lVar33 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
        lVar1 = lVar33 + 0xb0;
        Aska::CriticalSection::Enter() const(lVar1);
        lVar33 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar33,lVar32,1);
        Aska::CriticalSection::Leave() const(lVar1);
        *(long *)(param_1 + 0x9d0) = lVar33;
        if (lVar33 == 0) goto code_r0x022a6b68;
      }
      uVar21 = **(undefined8 **)(lVar33 + 0x60);
    }
    *(undefined8 *)(lVar24 + 0x20) = uVar21;
    lVar32 = *(long *)(param_1 + 0x9e0);
    if (lVar32 == 0) {
code_r0x022a6bc8:
      uVar21 = 0;
    }
    else {
      lVar33 = *(long *)(param_1 + 0x9f0);
      if (lVar33 == 0) {
        lVar33 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
        lVar1 = lVar33 + 0xb0;
        Aska::CriticalSection::Enter() const(lVar1);
        lVar33 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar33,lVar32,1);
        Aska::CriticalSection::Leave() const(lVar1);
        *(long *)(param_1 + 0x9f0) = lVar33;
        if (lVar33 == 0) goto code_r0x022a6bc8;
      }
      uVar21 = **(undefined8 **)(lVar33 + 0x60);
    }
    *(undefined8 *)(lVar24 + 0x28) = uVar21;
    lVar32 = *(long *)(param_1 + 0xa00);
    if (lVar32 == 0) {
code_r0x022a6c28:
      uVar21 = 0;
    }
    else {
      lVar33 = *(long *)(param_1 + 0xa10);
      if (lVar33 == 0) {
        lVar33 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
        lVar1 = lVar33 + 0xb0;
        Aska::CriticalSection::Enter() const(lVar1);
        lVar33 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar33,lVar32,1);
        Aska::CriticalSection::Leave() const(lVar1);
        *(long *)(param_1 + 0xa10) = lVar33;
        if (lVar33 == 0) goto code_r0x022a6c28;
      }
      uVar21 = **(undefined8 **)(lVar33 + 0x60);
    }
    *(undefined8 *)(lVar24 + 0x30) = uVar21;
    lVar32 = *(long *)(param_1 + 0xa20);
    if (lVar32 == 0) {
code_r0x022a6c88:
      uVar21 = 0;
    }
    else {
      lVar33 = *(long *)(param_1 + 0xa30);
      if (lVar33 == 0) {
        lVar33 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
        lVar1 = lVar33 + 0xb0;
        Aska::CriticalSection::Enter() const(lVar1);
        lVar33 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar33,lVar32,1);
        Aska::CriticalSection::Leave() const(lVar1);
        *(long *)(param_1 + 0xa30) = lVar33;
        if (lVar33 == 0) goto code_r0x022a6c88;
      }
      uVar21 = **(undefined8 **)(lVar33 + 0x60);
    }
    *(undefined8 *)(lVar24 + 0x38) = uVar21;
    if (bVar19) {
      if (lVar29 == 0) {
        *(undefined8 *)(lVar24 + 0x40) = 0;
        if (lVar22 != 0) goto code_r0x022a6cac;
code_r0x022a6cc4:
        uVar21 = 0;
      }
      else {
        *(undefined8 *)(lVar24 + 0x40) = **(undefined8 **)(lVar29 + 0x60);
        if (lVar22 == 0) goto code_r0x022a6cc4;
code_r0x022a6cac:
        uVar21 = **(undefined8 **)(lVar22 + 0x60);
      }
      *(undefined8 *)(lVar24 + 0x48) = uVar21;
    }
    bVar23 = *(byte *)(param_1 + 0xf5c);
    puVar2 = (ushort *)(lVar36 + 0xb29);
    if ((bVar23 & 3) == 1) {
      if (*(long *)(param_1 + 0xa40) != 0) {
        piVar3 = (int *)(*(long *)(*(long *)(param_1 + 0xa40) + 0x10) + 0x4c);
        do {
          cVar8 = '\x01';
          bVar19 = (bool)ExclusiveMonitorPass(piVar3,0x10);
          if (bVar19) {
            *piVar3 = *piVar3 + -1;
            cVar8 = ExclusiveMonitorsStatus();
          }
        } while (cVar8 != '\0');
        *(undefined8 *)(param_1 + 0xa40) = 0;
      }
      if (*(long *)(param_1 + 0xa48) != 0) {
        piVar3 = (int *)(*(long *)(param_1 + 0xa48) + 0x4c);
        do {
          cVar8 = '\x01';
          bVar19 = (bool)ExclusiveMonitorPass(piVar3,0x10);
          if (bVar19) {
            *piVar3 = *piVar3 + -1;
            cVar8 = ExclusiveMonitorsStatus();
          }
        } while (cVar8 != '\0');
        *(undefined8 *)(param_1 + 0xa48) = 0;
      }
      uStack_130 = uStack_130 & 0xffffffffffffff00;
      uStack_120 = 0;
      uStack_128 = 0;
      uVar7 = ((*(byte *)(param_1 + 0xf5c) & 8) >> 3) << 0xc | 0x80;
      uStack_488 = 0;
      uStack_470._0_4_ = (float)CONCAT22(0x80,(undefined2)uStack_470);
      uStack_490 = uStack_490 & 0xffffffffffffff00;
      uStack_480 = param_1 + 0x8bbU;
      Aska::ShaderKeyUtil::Open(Aska::AHSLShaderTarget::E, int, int, Aska::AHSLShaderKind::E, int, int)(&uStack_490,0,0,uVar7,2,0,0);
      uStack_110._0_4_ = CONCAT22(0x80,(undefined2)uStack_110);
      uStack_130 = uStack_130 & 0xfffffffffffffffd;
      uStack_120 = param_1 + 0x93bU;
      Aska::ShaderKeyUtil::Open(Aska::AHSLShaderTarget::E, int, int, Aska::AHSLShaderKind::E, int, int)(&uStack_130,1,0,uVar7,2,0,0);
      uStack_178 = (ulong)uStack_178._4_4_ << 0x20;
      uStack_180 = (ulong)*(byte *)(param_1 + 0x8b8);
      uVar10 = *puVar2;
      if ((uVar10 >> 4 & 1) != 0) {
        uStack_180._0_3_ = CONCAT21(0x801,*(byte *)(param_1 + 0x8b8));
        uStack_180 = (ulong)(uint3)uStack_180;
      }
      if ((uVar10 >> 6 & 1) == 0) {
        uVar25 = 0;
      }
      else {
        uVar25 = 8;
        uStack_180._0_6_ = CONCAT24(8,(float)uStack_180);
        uStack_180 = (ulong)(uint6)uStack_180;
      }
      if ((uVar10 >> 1 & 1) != 0) {
        uStack_180._0_6_ = CONCAT24(uVar25,(float)uStack_180) | 0x200000000;
        uStack_180 = (ulong)(uint6)uStack_180;
        uVar25 = uVar25 | 2;
      }
      if ((uVar10 >> 9 & 1) != 0) {
        uStack_180._0_6_ = CONCAT24(uVar25,(float)uStack_180) | 0x4000000000;
        uStack_180 = (ulong)(uint6)uStack_180;
      }
      lVar29 = param_1 + uVar35 * 0xe0;
      uVar15 = CONCAT16(*(undefined1 *)(lVar29 + 0xb25),(uint6)uStack_180);
      uStack_180._0_4_ = (float)CONCAT13(*(undefined1 *)(lVar29 + 0xb26),(uint3)uStack_180);
      uStack_180 = (ulong)CONCAT34((int3)((uint7)uVar15 >> 0x20),(float)uStack_180);
      if ((uVar10 >> 2 & 1) == 0) {
        uVar26 = 4;
      }
      else {
        uStack_178 = CONCAT62(uStack_178._2_6_,1);
        uVar26 = 5;
      }
      if ((uVar10 >> 3 & 1) != 0) {
        uVar34 = uStack_178 >> 0x18;
        uStack_178._3_5_ = (undefined5)uVar34;
        uStack_178._0_3_ = CONCAT12(*(undefined1 *)(param_1 + uVar35 * 0xe0 + 0xb27),uVar26);
      }
      Aska::ParticleShaderKeyUtil::AddShaderIDs(Aska::ParticleShaderFlags const*, Aska::ShaderKeyUtil*, Aska::ShaderKeyUtil*)(&uStack_180,&uStack_490,&uStack_130);
      if ((*(byte *)(param_1 + 0xf5c) & 0x30) != 0) {
        Aska::ShaderKeyUtil::AddShaderID(int, int)(&uStack_490,0x89,0);
        Aska::ShaderKeyUtil::AddSemanticsID(int)(&uStack_490,0);
        Aska::ShaderKeyUtil::EndShaderID()(&uStack_490);
        Aska::ShaderKeyUtil::AddShaderID(int, int)(&uStack_130,0x89,0);
        Aska::ShaderKeyUtil::AddSemanticsID(int)(&uStack_130,0);
        Aska::ShaderKeyUtil::EndShaderID()(&uStack_130);
        if ((*(byte *)(param_1 + 0xf5c) & 0x30) == 0x20) {
          Aska::ShaderKeyUtil::AddShaderID(int, int)(&uStack_130,0x12a,0);
          Aska::ShaderKeyUtil::EndShaderID()(&uStack_130);
        }
      }
      iVar20 = Aska::ShaderKeyUtil::Close()(&uStack_490);
      if ((iVar20 == 0) || (iVar20 = Aska::ShaderKeyUtil::Close()(&uStack_130), iVar20 == 0)) {
code_r0x022a6ff0:
        bVar19 = true;
        if ((uStack_130 & 1) == 0) goto code_r0x022a6ffc;
code_r0x022a6fc0:
        if (uStack_120 == 0) goto code_r0x022a6ffc;
        operator delete[](void*)();
        uStack_120 = 0;
        if ((uStack_490 & 1) != 0) goto code_r0x022a6fd8;
code_r0x022a7004:
        if (bVar19) goto code_r0x022a7008;
      }
      else {
        uStack_4c0 = 0;
        lStack_138 = 0;
        iVar20 = Aska::AofAhslManager::SearchParticleShaders(unsigned char const*, unsigned char const*, Aska::ShaderCache**, Aska::ShaderCache**)(*(long *)PTR__ZN4Aska6Global20m_pShaderLinkManagerE_02cb93f8 + 8,
                                 param_1 + 0x8bbU,param_1 + 0x93bU,&uStack_4c0,&lStack_138);
        puVar16 = PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108;
        *(byte *)(param_1 + 0xf5c) = *(byte *)(param_1 + 0xf5c) & 0xfe | iVar20 != 0;
        lVar22 = (**(code **)(**(long **)puVar16 + 0x50))(*(long **)puVar16,uStack_4c0);
        *(long *)(param_1 + 0xa40) = lVar22;
        *(long *)(param_1 + 0xa48) = lStack_138;
        lVar29 = lStack_138;
        if (lVar22 != 0) {
          piVar3 = (int *)(*(long *)(lVar22 + 0x10) + 0x4c);
          do {
            cVar8 = '\x01';
            bVar19 = (bool)ExclusiveMonitorPass(piVar3,0x10);
            if (bVar19) {
              *piVar3 = *piVar3 + 1;
              cVar8 = ExclusiveMonitorsStatus();
            }
          } while (cVar8 != '\0');
          lVar29 = *(long *)(param_1 + 0xa48);
        }
        if (lVar29 != 0) {
          piVar3 = (int *)(lVar29 + 0x4c);
          do {
            cVar8 = '\x01';
            bVar19 = (bool)ExclusiveMonitorPass(piVar3,0x10);
            if (bVar19) {
              *piVar3 = *piVar3 + 1;
              cVar8 = ExclusiveMonitorsStatus();
            }
          } while (cVar8 != '\0');
        }
        if (*(long *)(param_1 + 0xa40) == 0) goto code_r0x022a6ff0;
        bVar19 = false;
        *(byte *)(param_1 + 0xf5c) = *(byte *)(param_1 + 0xf5c) | 2;
        if ((uStack_130 & 1) != 0) goto code_r0x022a6fc0;
code_r0x022a6ffc:
        if ((uStack_490 & 1) == 0) goto code_r0x022a7004;
code_r0x022a6fd8:
        if (uStack_480 == 0) goto code_r0x022a7004;
        operator delete[](void*)();
        uStack_480 = 0;
        if (bVar19) goto code_r0x022a7008;
      }
      bVar23 = *(byte *)(param_1 + 0xf5c);
    }
    if ((bVar23 >> 2 & 1) == 0) {
      uStack_128 = _UNK_027dbb08;
      uStack_130 = _UNK_027dbb00;
      uStack_118 = _UNK_027dbb18;
      uStack_120 = _UNK_027dbb10;
      uStack_178 = _UNK_027dbb08;
      uStack_180 = _UNK_027dbb00;
      uStack_168 = _UNK_027dbb18;
      uStack_170 = _UNK_027dbb10;
      uStack_108 = _UNK_027dbb28;
      uStack_110 = _UNK_027dbb20;
      uStack_f8 = _UNK_027dbb38;
      uStack_100 = _UNK_027dbb30;
      uStack_158 = _UNK_027dbb28;
      uStack_160 = _UNK_027dbb20;
      uStack_148 = _UNK_027dbb38;
      uStack_150 = _UNK_027dbb30;
      if ((*(byte *)puVar2 >> 1 & 1) != 0) {
        uStack_128 = *(ulong *)(lVar6 + 0x968);
        uStack_130 = *(ulong *)(lVar6 + 0x960);
        uStack_118 = *(ulong *)(lVar6 + 0x978);
        uStack_120 = *(ulong *)(lVar6 + 0x970);
        uStack_108 = *(ulong *)(lVar6 + 0x988);
        uStack_110 = *(ulong *)(lVar6 + 0x980);
        uStack_f8 = *(ulong *)(lVar6 + 0x998);
        uStack_100 = *(ulong *)(lVar6 + 0x990);
        Aska::Matrix::Invert()(&uStack_130);
      }
      lVar29 = param_1 + uVar35 * 0xe0;
      cVar8 = *(char *)(lVar29 + 0xb25);
      if (cVar8 != '\0') {
        uStack_178 = *(ulong *)(lVar6 + 0x138);
        uStack_180 = *(ulong *)(lVar6 + 0x130);
        uStack_168 = *(ulong *)(lVar6 + 0x148);
        uStack_170 = *(ulong *)(lVar6 + 0x140);
        uStack_158 = *(ulong *)(lVar6 + 0x158);
        uStack_160 = *(ulong *)(lVar6 + 0x150);
        uStack_148 = *(ulong *)(lVar6 + 0x168);
        uStack_150 = *(ulong *)(lVar6 + 0x160);
        uVar21 = *(undefined8 *)(param_2 + 0xc);
        Aska::LightManager::MakeLightContext(Aska::RenderableObject*, Aska::LightManager::LightContextSimple*)(uVar21,param_1,&uStack_490);
        fVar46 = _UNK_027e519c;
        lVar22 = param_1 + uVar35 * 0xe0;
        fVar45 = *(float *)(lVar22 + 0xad0);
        fVar44 = *(float *)(lVar22 + 0xad4);
        fVar43 = *(float *)(lVar22 + 0xad8);
        fVar42 = *(float *)(lVar22 + 0xadc);
        fVar41 = *(float *)(lVar22 + 0xac0);
        fVar47 = *(float *)(lVar22 + 0xac4);
        fVar38 = *(float *)(lVar22 + 0xac8);
        fVar37 = *(float *)(lVar22 + 0xacc);
        afStack_400[4] = fVar45 * afStack_400[4];
        afStack_400[5] = fVar44 * afStack_400[5];
        fStack_3e8 = fVar43 * fStack_3e8;
        fStack_3e4 = fVar42 * fStack_3e4;
        fStack_360 = fVar45 * fStack_360;
        fStack_35c = fVar44 * fStack_35c;
        fStack_358 = fVar43 * fStack_358;
        fStack_354 = fVar42 * fStack_354;
        uStack_490 = CONCAT44(fVar47 * uStack_490._4_4_,fVar41 * (float)uStack_490);
        uStack_488 = CONCAT44(fVar37 * uStack_488._4_4_,fVar38 * (float)uStack_488);
        fStack_3d0 = fVar45 * fStack_3d0;
        fStack_3cc = fVar44 * fStack_3cc;
        fStack_3c8 = fVar43 * fStack_3c8;
        fStack_3c4 = fVar42 * fStack_3c4;
        fStack_310 = fVar45 * fStack_310;
        fStack_30c = fVar44 * fStack_30c;
        fStack_308 = fVar43 * fStack_308;
        fStack_304 = fVar42 * fStack_304;
        uStack_480 = CONCAT44(fVar47 * uStack_480._4_4_,fVar41 * (float)uStack_480);
        uStack_478 = CONCAT44(fVar37 * uStack_478._4_4_,fVar38 * (float)uStack_478);
        fStack_3b0 = fVar45 * fStack_3b0;
        fStack_3ac = fVar44 * fStack_3ac;
        fStack_3a8 = fVar43 * fStack_3a8;
        fStack_3a4 = fVar42 * fStack_3a4;
        fStack_2c0 = fVar45 * fStack_2c0;
        fStack_2bc = fVar44 * fStack_2bc;
        fStack_2b8 = fVar43 * fStack_2b8;
        fStack_2b4 = fVar42 * fStack_2b4;
        uStack_470 = CONCAT44(fVar47 * uStack_470._4_4_,fVar41 * (float)uStack_470);
        uStack_468 = CONCAT44(fVar37 * uStack_468._4_4_,fVar38 * (float)uStack_468);
        fStack_390 = fVar45 * fStack_390;
        fStack_38c = fVar44 * fStack_38c;
        fStack_388 = fVar43 * fStack_388;
        fStack_384 = fVar42 * fStack_384;
        fStack_270 = fVar45 * fStack_270;
        fStack_26c = fVar44 * fStack_26c;
        fStack_268 = fVar43 * fStack_268;
        fStack_264 = fVar42 * fStack_264;
        uStack_460 = CONCAT44(fVar47 * uStack_460._4_4_,fVar41 * (float)uStack_460);
        uStack_458 = CONCAT44(fVar37 * uStack_458._4_4_,fVar38 * (float)uStack_458);
        fStack_230 = *(float *)(lVar22 + 0xae0) * fStack_230;
        fStack_22c = *(float *)(lVar22 + 0xae4) * fStack_22c;
        fStack_228 = *(float *)(lVar22 + 0xae8) * fStack_228;
        pfVar4 = (float *)0x0;
        if (cVar8 != '\x01') {
          pfVar4 = (float *)&uStack_180;
        }
        fStack_224 = *(float *)(lVar22 + 0xaec) * fStack_224;
        if (cVar8 != '\x01') {
          uVar34 = (ulong)bStack_188;
          if (uVar34 != 0) {
            pfVar30 = afStack_400;
            do {
              Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(pfVar30,pfVar4);
              fVar38 = *pfVar30 * *pfVar30 + pfVar30[1] * pfVar30[1] + pfVar30[2] * pfVar30[2];
              fVar37 = SQRT(fVar38);
              if (NAN(fVar37)) {
                fVar37 = (float)sqrtf(fVar38);
              }
              if (fVar37 < fVar46) {
                fVar38 = pfVar30[2];
              }
              else {
                fVar37 = 1.0 / fVar37;
                fVar38 = fVar37 * pfVar30[2];
                *pfVar30 = fVar37 * *pfVar30;
                pfVar30[1] = fVar37 * pfVar30[1];
                pfVar30[2] = fVar38;
              }
              uVar34 = uVar34 - 1;
              pfVar30[2] = -fVar38;
              pfVar30 = pfVar30 + 8;
            } while (uVar34 != 0);
          }
          if ((lStack_190 != 0) && (*(char *)(lStack_190 + 0x2a1) != '\0')) {
            Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(auStack_240,pfVar4);
          }
          fVar38 = *pfVar4;
          fVar37 = pfVar4[1];
          fVar46 = pfVar4[2];
          fVar47 = pfVar4[4];
          fVar41 = pfVar4[5];
          fVar42 = pfVar4[6];
          fVar44 = pfVar4[9];
          fVar45 = pfVar4[10];
          uStack_4b8 = uStack_488;
          uVar39 = uStack_4b8;
          uStack_4c0 = uStack_490;
          uVar34 = uStack_4c0;
          uStack_4a8 = uStack_478;
          uVar17 = uStack_4a8;
          uStack_4b0 = uStack_480;
          uVar40 = uStack_4b0;
          uStack_498 = uStack_468;
          uVar12 = uStack_498;
          uStack_4a0 = uStack_470;
          uVar18 = uStack_4a0;
          uStack_4c0._0_4_ = (float)uStack_490;
          uStack_4c0._4_4_ = (float)(uStack_490 >> 0x20);
          uStack_4b8._0_4_ = (float)uStack_488;
          uStack_4b0._0_4_ = (float)uStack_480;
          uStack_4b0._4_4_ = (float)(uStack_480 >> 0x20);
          uStack_4a8._0_4_ = (float)uStack_478;
          uStack_4a0._0_4_ = (float)uStack_470;
          uStack_4a0._4_4_ = (float)(uStack_470 >> 0x20);
          uStack_498._0_4_ = (float)uStack_468;
          fVar43 = -pfVar4[8];
          uStack_4b8._4_4_ = (undefined4)(uStack_488 >> 0x20);
          uStack_490 = CONCAT44(fVar47 * uStack_4c0._4_4_ + fVar41 * uStack_4b0._4_4_ +
                                fVar42 * uStack_4a0._4_4_,
                                fVar47 * (float)uStack_4c0 + fVar41 * (float)uStack_4b0 +
                                fVar42 * (float)uStack_4a0);
          uStack_488 = CONCAT44(uStack_4b8._4_4_,
                                fVar47 * (float)uStack_4b8 + fVar41 * (float)uStack_4a8 +
                                fVar42 * (float)uStack_498);
          uStack_480 = CONCAT44((uStack_4c0._4_4_ * fVar43 - fVar44 * uStack_4b0._4_4_) -
                                fVar45 * uStack_4a0._4_4_,
                                ((float)uStack_4c0 * fVar43 - fVar44 * (float)uStack_4b0) -
                                fVar45 * (float)uStack_4a0);
          uStack_478 = CONCAT44(uStack_4b8._4_4_,
                                ((float)uStack_4b8 * fVar43 - fVar44 * (float)uStack_4a8) -
                                fVar45 * (float)uStack_498);
          uStack_470 = CONCAT44(fVar38 * uStack_4c0._4_4_ + fVar37 * uStack_4b0._4_4_ +
                                fVar46 * uStack_4a0._4_4_,
                                fVar38 * (float)uStack_4c0 + fVar37 * (float)uStack_4b0 +
                                fVar46 * (float)uStack_4a0);
          uStack_468 = CONCAT44(uStack_4b8._4_4_,
                                fVar38 * (float)uStack_4b8 + fVar37 * (float)uStack_4a8 +
                                fVar46 * (float)uStack_498);
          uStack_4c0 = uVar34;
          uStack_4b8 = uVar39;
          uStack_4b0 = uVar40;
          uStack_4a8 = uVar17;
          uStack_4a0 = uVar18;
          uStack_498 = uVar12;
        }
        if (*(char *)(lVar29 + 0xb25) != '\x01') {
          Aska::LightManager::CalcSH(Aska::LightManager::LightContextSimple*, Aska::Matrix const*)(uVar21,&uStack_490,0);
        }
      }
      if (*(byte *)(param_1 + 0x8b8) - 3 < 4) {
        lVar29 = *(long *)(param_1 + 0x9c0);
        if (lVar29 == 0) {
          lVar22 = 0;
        }
        else {
          lVar22 = *(long *)(param_1 + 0x9d0);
          if (lVar22 == 0) {
            lVar22 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
            lVar32 = lVar22 + 0xb0;
            Aska::CriticalSection::Enter() const(lVar32);
            lVar22 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar22,lVar29,1);
            Aska::CriticalSection::Leave() const(lVar32);
            *(long *)(param_1 + 0x9d0) = lVar22;
          }
        }
        bVar19 = lVar22 != 0;
      }
      else {
        bVar19 = true;
      }
      lVar29 = *(long *)(param_1 + 0x3a0);
      if (lVar6 == lVar29) {
        lVar22 = 0;
        lVar29 = param_1;
      }
      else {
        lVar32 = 0;
        lVar22 = 0;
        do {
          if (lVar29 == 0) {
            lVar32 = param_1 + lVar32;
            *(long *)(lVar32 + 0x3a0) = lVar6;
            puVar16 = PTR__ZSt7nothrow_02cb9a80;
            puVar27 = (ulong *)operator new(unsigned long, std::nothrow_t const&)(0x40,PTR__ZSt7nothrow_02cb9a80);
            *(ulong **)(lVar32 + 0x3a8) = puVar27;
            uVar21 = operator new(unsigned long, std::nothrow_t const&)(0x40,puVar16);
            *(undefined8 *)(lVar32 + 0x3b0) = uVar21;
            uVar21 = operator new(unsigned long, std::nothrow_t const&)(0x310,puVar16);
            *(undefined8 *)(lVar32 + 0x3b8) = uVar21;
            puVar27[1] = uStack_128;
            *puVar27 = uStack_130;
            puVar27[3] = uStack_118;
            puVar27[2] = uStack_120;
            puVar27[5] = uStack_108;
            puVar27[4] = uStack_110;
            puVar27[7] = uStack_f8;
            puVar27[6] = uStack_100;
            puVar27 = *(ulong **)(lVar32 + 0x3b0);
            puVar27[1] = uStack_178;
            *puVar27 = uStack_180;
            puVar27[3] = uStack_168;
            puVar27[2] = uStack_170;
            puVar27[5] = uStack_158;
            puVar27[4] = uStack_160;
            puVar27[7] = uStack_148;
            puVar27[6] = uStack_150;
            uVar21 = *(undefined8 *)(lVar32 + 0x3b8);
            goto code_r0x022a7788;
          }
          if (lVar32 == 0x3e0) goto code_r0x022a7008;
          lVar29 = *(long *)(param_1 + lVar32 + 0x3c0);
          lVar22 = lVar22 + 1;
          lVar32 = lVar32 + 0x20;
        } while (lVar6 != lVar29);
        lVar29 = param_1 + lVar32;
      }
      *(long *)(lVar29 + 0x3a0) = lVar6;
      lVar32 = param_1 + lVar22 * 0x20;
      puVar27 = *(ulong **)(lVar32 + 0x3a8);
      puVar27[1] = uStack_128;
      *puVar27 = uStack_130;
      puVar27[3] = uStack_118;
      puVar27[2] = uStack_120;
      puVar27[5] = uStack_108;
      puVar27[4] = uStack_110;
      puVar27[7] = uStack_f8;
      puVar27[6] = uStack_100;
      puVar27 = *(ulong **)(lVar32 + 0x3b0);
      puVar27[1] = uStack_178;
      *puVar27 = uStack_180;
      puVar27[3] = uStack_168;
      puVar27[2] = uStack_170;
      puVar27[5] = uStack_158;
      puVar27[4] = uStack_160;
      puVar27[7] = uStack_148;
      puVar27[6] = uStack_150;
      uVar21 = *(undefined8 *)(lVar32 + 0x3b8);
code_r0x022a7788:
      Aska::LightManager::LightContextSimple::operator=(Aska::LightManager::LightContextSimple const&)(uVar21,&uStack_490);
      *(undefined8 *)(lVar24 + 0x118) = *(undefined8 *)(lVar32 + 0x3a8);
      *(undefined8 *)(lVar24 + 0x120) = *(undefined8 *)(lVar32 + 0x3b0);
      *(undefined8 *)(lVar24 + 0x128) = *(undefined8 *)(lVar32 + 0x3b8);
      bVar23 = *(byte *)(lVar36 + 0xb2a);
    }
    else {
      bVar19 = true;
      bVar23 = *(byte *)(lVar36 + 0xb2a);
    }
    if ((bVar23 & 1) != 0) {
      Aska::ParticleRenderManager::FlipSync(int, int)(*(undefined8 *)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108,
                      *(undefined4 *)(param_1 + 0x8a8),
                      *(undefined1 *)(param_1 + uVar35 * 0xe0 + 0xb28));
      *puVar2 = *puVar2 & 0xfeff;
    }
  }
  return bVar19;
}

// ==== Aska::ParticleRenderableBase::Render(Aska::RenderContext*, int)
// vaddr 0x21a7be8 | ghidra 0x22a7be8 | size 552 | symbol _ZN4Aska22ParticleRenderableBase6RenderEPNS_13RenderContextEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBase6RenderEPNS_13RenderContextEi(long param_1,long param_2)

{
  int iVar1;
  ushort uVar2;
  long lVar3;
  undefined8 *puVar4;
  long lVar5;
  int iVar6;
  undefined8 uVar7;
  ulong uVar8;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  undefined8 uStack_168;
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
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  long lStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined4 uStack_80;
  uint uStack_7c;
  undefined4 uStack_78;
  uint uStack_74;
  undefined4 uStack_70;
  undefined8 uStack_68;
  undefined1 uStack_60;
  undefined1 uStack_5f;
  undefined1 uStack_5e;
  undefined1 uStack_5d;
  undefined8 uStack_5c;
  undefined8 uStack_54;
  undefined4 uStack_4c;
  byte bStack_48;
  
  if (0 < *(int *)(param_1 + 0x8b0)) {
    uVar7 = *(undefined8 *)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108;
    lVar3 = Aska::RenderContext::GetBatchArray(int)(param_2,0);
    Aska::ParticleDrawContext::ParticleDrawContext()(&uStack_190);
    puVar4 = *(undefined8 **)(lVar3 + 0x118);
    uStack_188 = puVar4[1];
    uStack_190 = *puVar4;
    uVar8 = (ulong)*(byte *)(param_2 + 10) & 3;
    lVar5 = param_1 + uVar8 * 0xe0;
    uStack_178 = puVar4[3];
    uStack_180 = puVar4[2];
    uStack_168 = puVar4[5];
    uStack_170 = puVar4[4];
    uStack_158 = puVar4[7];
    uStack_160 = puVar4[6];
    puVar4 = *(undefined8 **)(lVar3 + 0x120);
    uStack_148 = puVar4[1];
    uStack_150 = *puVar4;
    uStack_138 = puVar4[3];
    uStack_140 = puVar4[2];
    uStack_128 = puVar4[5];
    uStack_130 = puVar4[4];
    uStack_118 = puVar4[7];
    uStack_120 = puVar4[6];
    uStack_68 = *(undefined8 *)(lVar3 + 0x128);
    uStack_108 = *(undefined8 *)(param_1 + 0x868);
    uStack_110 = *(undefined8 *)(param_1 + 0x860);
    uStack_80 = *(undefined4 *)(param_1 + 0x8a8);
    uStack_7c = (uint)*(byte *)(param_1 + 0x8b8);
    uStack_78 = *(undefined4 *)(param_1 + 0x8ac);
    uStack_70 = *(undefined4 *)(lVar5 + 0xb04);
    uStack_74 = (uint)*(byte *)(lVar5 + 0xb24);
    uStack_d8 = *(undefined8 *)(lVar5 + 0xaf8);
    uStack_e0 = *(undefined8 *)(lVar5 + 0xaf0);
    uStack_d0 = *(undefined4 *)(lVar5 + 0xb00);
    uStack_cc = *(undefined4 *)(lVar5 + 0xb20);
    uStack_c0 = *(undefined8 *)(param_1 + 0xa48);
    uStack_c8 = *(undefined8 *)(param_1 + 0xa40);
    uStack_b0 = *(undefined8 *)(lVar3 + 0x20);
    uStack_a8 = *(undefined8 *)(lVar3 + 0x28);
    uStack_a0 = *(undefined8 *)(lVar3 + 0x30);
    uStack_98 = *(undefined8 *)(lVar3 + 0x38);
    uStack_f8 = *(undefined8 *)(lVar5 + 0xab8);
    uStack_100 = *(undefined8 *)(lVar5 + 0xab0);
    uStack_5f = *(undefined1 *)(lVar5 + 0xb25);
    uStack_60 = *(undefined1 *)(lVar5 + 0xb28);
    uStack_5e = *(undefined1 *)(lVar5 + 0xb26);
    uVar2 = *(ushort *)(lVar5 + 0xb29);
    uStack_90 = *(undefined8 *)(lVar3 + 0x40);
    uStack_88 = *(undefined8 *)(lVar3 + 0x48);
    uStack_5d = *(undefined1 *)(param_1 + 0x8b9);
    uStack_54 = *(undefined8 *)(lVar5 + 0xb10);
    uStack_5c = *(undefined8 *)(lVar5 + 0xb08);
    uStack_4c = *(undefined4 *)(lVar5 + 0xb18);
    bStack_48 = (byte)(uVar2 >> 1) & 0x40 | (byte)(uVar2 >> 2) & 0x80 |
                (byte)uVar2 & 0x1f | (*(byte *)(param_1 + 0xf5c) >> 3 & 1) << 5;
    lStack_b8 = param_2;
    Aska::IParticleRenderManager::Draw(Aska::ParticleDrawContext*)(uVar7,&uStack_190);
    iVar1 = *(int *)(*(long *)PTR__ZN4Aska6Global18m_pParticleManagerE_02cbd300 + 0x10a8);
    iVar6 = 1;
    if (iVar1 != -1) {
      iVar6 = iVar1 + 1;
    }
    *(int *)(*(long *)PTR__ZN4Aska6Global18m_pParticleManagerE_02cbd300 + 0x10a8) = iVar6;
    *(int *)(param_1 + uVar8 * 4 + 0xf50) = iVar1;
    Aska::ParticleDrawContext::~ParticleDrawContext()(&uStack_190);
  }
  return;
}

// ==== Aska::ParticleRenderableBase::IsBufferReady() const
// vaddr 0x21a7e10 | ghidra 0x22a7e10 | size 84 | symbol _ZNK4Aska22ParticleRenderableBase13IsBufferReadyEv | lib libSOA-3.7.0.so | 2026-10-08
byte _ZNK4Aska22ParticleRenderableBase13IsBufferReadyEv(long param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  uVar1 = *(uint *)(param_1 + (ulong)*(uint *)(param_1 + 0xf58) * 4 + 0xf50);
  if (uVar1 != 0) {
    uVar2 = *(uint *)(*(long *)PTR__ZN4Aska6Global18m_pParticleManagerE_02cbd300 + 0x10a8);
    uVar3 = *(uint *)(*(long *)PTR__ZN4Aska6Global18m_pParticleManagerE_02cbd300 + 0x10ac);
    bVar4 = uVar2 < uVar3;
    if (uVar2 < uVar1) {
      bVar4 = uVar3 < uVar2;
    }
    return uVar1 <= uVar3 & (bVar4 ^ 1U);
  }
  return 1;
}

// ==== Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)
// vaddr 0x21a7e64 | ghidra 0x22a7e64 | size 56 | symbol _ZN4Aska22ParticleRenderableBasenwEmmb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBasenwEmmb(undefined8 param_1,undefined8 param_2)

{
  if (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager13AlignedMallocEml_02cae360)
              (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838,param_1,param_2);
    return;
  }
  (*(code *)PTR__Znwmmb_02c9f858)(param_1,param_2,1);
  return;
}

// ==== Aska::ParticleRenderableBase::operator new[](unsigned long, unsigned long, bool)
// vaddr 0x21a7e9c | ghidra 0x22a7e9c | size 56 | symbol _ZN4Aska22ParticleRenderableBasenaEmmb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBasenaEmmb(undefined8 param_1,undefined8 param_2)

{
  if (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager13AlignedMallocEml_02cae360)
              (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838,param_1,param_2);
    return;
  }
  (*(code *)PTR__Znwmmb_02c9f858)(param_1,param_2,1);
  return;
}

// ==== Aska::ParticleRenderableBase::operator delete[](void*)
// vaddr 0x21a7ed4 | ghidra 0x22a7ed4 | size 44 | symbol _ZN4Aska22ParticleRenderableBasedaEPv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22ParticleRenderableBasedaEPv(long param_1)

{
  if (param_1 == 0) {
    return;
  }
  if (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPv_02cb5c60)
              (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838,param_1);
    return;
  }
  (*(code *)PTR__ZdaPv_02cb5db8)(param_1);
  return;
}

// ==== Aska::ParticleDrawContext::ParticleDrawContext()
// vaddr 0x259a854 | ghidra 0x269a854 | size 20 | symbol _ZN4Aska19ParticleDrawContextC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19ParticleDrawContextC2Ev(long param_1)

{
  *(byte *)(param_1 + 0x148) = *(byte *)(param_1 + 0x148) & 0x75;
  return;
}

// ==== Aska::ParticleDrawContext::~ParticleDrawContext()
// vaddr 0x259a868 | ghidra 0x269a868 | size 4 | symbol _ZN4Aska19ParticleDrawContextD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19ParticleDrawContextD1Ev(void)

{
  return;
}

// ==== Aska::ParticleDrawContext::SetShaderConstant_Vertex()
// vaddr 0x259a86c | ghidra 0x269a86c | size 1448 | symbol _ZN4Aska19ParticleDrawContext24SetShaderConstant_VertexEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska19ParticleDrawContext24SetShaderConstant_VertexEv(long param_1)

{
  float *pfVar1;
  uint uVar2;
  float fVar3;
  uint uVar4;
  char cVar5;
  undefined4 uVar6;
  float fVar7;
  undefined8 uVar8;
  undefined8 *puVar9;
  long lVar10;
  long lVar11;
  uint *puVar12;
  uint *puVar13;
  undefined8 uVar14;
  long lVar15;
  float *pfVar16;
  long lVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fStack_190;
  float fStack_18c;
  float fStack_188;
  undefined4 uStack_184;
  undefined4 uStack_150;
  undefined8 uStack_14c;
  undefined4 uStack_144;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  ulong uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  ulong uStack_a8;
  undefined8 uStack_a0;
  ulong uStack_98;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined8 uStack_80;
  undefined8 uStack_78;
  
  uVar6 = *(undefined4 *)(param_1 + 0xb4);
  uStack_80 = CONCAT44(uVar6,uVar6);
  uStack_78 = CONCAT44(uVar6,uVar6);
  uVar14 = *(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,0xc,&uStack_80,1);
  Aska::RenderState::Static::SetZTestFunction(Aska::RenderDeviceGL*, int)(uVar14,2);
  Aska::RenderState::Static::SetCullMode(Aska::RenderDeviceGL*, Aska::Cull::Mode)(uVar14,0);
  Aska::RenderState::Static::EnableZWrite(Aska::RenderDeviceGL*, bool)(uVar14,*(byte *)(param_1 + 0x148) & 1);
  Aska::RenderState::Static::EnableAlphaBlend(Aska::RenderDeviceGL*, bool)(uVar14,1);
  lVar10 = *(long *)(param_1 + 0xd8);
  uStack_c0 = (undefined4)*(undefined8 *)(lVar10 + 0x170);
  uStack_84 = (undefined4)((ulong)_UNK_027dbb38 >> 0x20);
  uStack_a0 = CONCAT44((int)*(undefined8 *)(lVar10 + 0x188),(int)*(undefined8 *)(lVar10 + 0x178));
  uStack_8c = (undefined4)((ulong)*(undefined8 *)(lVar10 + 0x188) >> 0x20);
  uStack_bc = (undefined4)*(undefined8 *)(lVar10 + 0x180);
  uStack_b8 = (undefined4)*(ulong *)(lVar10 + 400);
  uStack_88 = (undefined4)(*(ulong *)(lVar10 + 0x198) >> 0x20);
  _uStack_b0 = CONCAT44((int)((ulong)*(undefined8 *)(lVar10 + 0x180) >> 0x20),
                        (int)((ulong)*(undefined8 *)(lVar10 + 0x170) >> 0x20));
  uStack_b4 = 0;
  uStack_90 = (undefined4)((ulong)*(undefined8 *)(lVar10 + 0x178) >> 0x20);
  uStack_a8 = *(ulong *)(lVar10 + 400) >> 0x20;
  uStack_98 = *(ulong *)(lVar10 + 0x198) & 0xffffffff;
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,0x1c,lVar10 + 0x170,4);
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,0x1d,&uStack_c0,3);
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,0x1e,*(long *)(param_1 + 0xd8) + 0x110,1);
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,0x27,param_1 + 0x40,4);
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,0,*(long *)(param_1 + 0xd8) + 0x60,4);
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,3,*(long *)(param_1 + 0xd8) + 0xa0,4);
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,1,*(long *)(param_1 + 0xd8) + 0xe0,3);
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,2,param_1 + 0x80,1);
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,4,lVar10 + 0x170,1);
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,5,lVar10 + 0x180,1);
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,6,lVar10 + 400,1);
  if (*(char *)(param_1 + 0x131) == '\0') goto code_r0x0269ad74;
  if (*(char *)(param_1 + 0x131) == '\x01') {
    lVar10 = *(long *)(param_1 + 0x128);
    uStack_f8 = *(undefined8 *)(lVar10 + 0x98);
    uStack_100 = *(undefined8 *)(lVar10 + 0x90);
    uStack_138 = *(undefined8 *)(lVar10 + 0xa8);
    uStack_140 = *(undefined8 *)(lVar10 + 0xa0);
    uStack_e8 = *(undefined8 *)(lVar10 + 0xb8);
    uStack_f0 = *(undefined8 *)(lVar10 + 0xb0);
    uStack_128 = *(undefined8 *)(lVar10 + 200);
    uStack_130 = *(undefined8 *)(lVar10 + 0xc0);
    uStack_d8 = *(undefined8 *)(lVar10 + 0xd8);
    uStack_e0 = *(undefined8 *)(lVar10 + 0xd0);
    lVar10 = *(long *)(param_1 + 0x128);
    uStack_118 = *(undefined8 *)(lVar10 + 0xe8);
    uStack_120 = *(undefined8 *)(lVar10 + 0xe0);
    uStack_c8 = *(undefined8 *)(lVar10 + 0xf8);
    uStack_d0 = *(undefined8 *)(lVar10 + 0xf0);
    uStack_108 = *(undefined8 *)(lVar10 + 0x108);
    uStack_110 = *(undefined8 *)(lVar10 + 0x100);
    Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,0xe,&uStack_100,4);
    uVar8 = 0xf;
    puVar9 = &uStack_140;
  }
  else {
    uVar8 = 0xd;
    puVar9 = (undefined8 *)(*(long *)(param_1 + 0x128) + 0x270);
  }
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,uVar8,puVar9,4);
  lVar10 = *(long *)(param_1 + 0x128);
  uStack_f8 = *(undefined8 *)(lVar10 + 0x118);
  uStack_100 = *(undefined8 *)(lVar10 + 0x110);
  uStack_138 = *(undefined8 *)(lVar10 + 0x138);
  uStack_140 = *(undefined8 *)(lVar10 + 0x130);
  uStack_e8 = *(undefined8 *)(lVar10 + 0x168);
  uStack_f0 = *(undefined8 *)(lVar10 + 0x160);
  uStack_128 = *(undefined8 *)(lVar10 + 0x188);
  uStack_130 = *(undefined8 *)(lVar10 + 0x180);
  uStack_d8 = *(undefined8 *)(lVar10 + 0x1b8);
  uStack_e0 = *(undefined8 *)(lVar10 + 0x1b0);
  lVar10 = *(long *)(param_1 + 0x128);
  uStack_118 = *(undefined8 *)(lVar10 + 0x1d8);
  uStack_120 = *(undefined8 *)(lVar10 + 0x1d0);
  uStack_c8 = *(undefined8 *)(lVar10 + 0x208);
  uStack_d0 = *(undefined8 *)(lVar10 + 0x200);
  uStack_108 = *(undefined8 *)(lVar10 + 0x228);
  uStack_110 = *(undefined8 *)(lVar10 + 0x220);
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,0x10,&uStack_100,4);
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,0x11,&uStack_140,4);
  uStack_150 = *(undefined4 *)(param_1 + 0xc0);
  uStack_14c = 0;
  uStack_144 = 0;
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,0x22,&uStack_150,1);
  if ((*(byte *)(param_1 + 0x148) >> 2 & 1) != 0) {
    uStack_184 = *(undefined4 *)(param_1 + 0x9c);
    lVar10 = *(long *)(param_1 + 0x128);
    fStack_190 = *(float *)(lVar10 + 0x260) * *(float *)(param_1 + 0x90);
    fStack_18c = *(float *)(lVar10 + 0x264) * *(float *)(param_1 + 0x94);
    fStack_188 = *(float *)(lVar10 + 0x268) * *(float *)(param_1 + 0x98);
    Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,0x20,lVar10 + 0x250,1);
    Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,0x21,&fStack_190,1);
  }
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,0x26,*(long *)(param_1 + 0x128),4);
  if ((*(byte *)(param_1 + 0x148) >> 3 & 1) == 0) goto code_r0x0269ad74;
  lVar10 = *(long *)(param_1 + 0x128);
  fVar21 = *(float *)(param_1 + 0x80);
  fVar22 = *(float *)(param_1 + 0x84);
  fVar23 = *(float *)(param_1 + 0x88);
  if (*(char *)(lVar10 + 0x308) == '\0') {
    lVar11 = 0;
    cVar5 = *(char *)(lVar10 + 0x309);
    fVar7 = _UNK_027e519c;
joined_r0x0269ac78:
    _UNK_027e519c = fVar7;
    if (cVar5 != '\0') {
      lVar15 = 0;
      pfVar16 = (float *)((long)&fStack_190 + ((lVar11 << 0x20) >> 0x1c) | 8);
      lVar17 = 0x110;
      do {
        pfVar1 = (float *)(lVar10 + lVar17);
        fVar18 = *pfVar1;
        pfVar16[-2] = fVar18;
        fVar19 = pfVar1[1];
        fVar18 = fVar18 - fVar21;
        pfVar16[-1] = fVar19;
        fVar20 = pfVar1[2];
        fVar19 = fVar19 - fVar22;
        *pfVar16 = fVar20;
        fVar20 = fVar20 - fVar23;
        fVar3 = pfVar1[3];
        pfVar16[-2] = fVar18;
        pfVar16[-1] = fVar19;
        fVar19 = fVar20 * fVar20 + fVar19 * fVar19 + fVar18 * fVar18;
        fVar18 = SQRT(fVar19);
        pfVar16[1] = fVar3;
        *pfVar16 = fVar20;
        if (NAN(fVar18)) {
          fVar18 = (float)sqrtf(fVar19);
        }
        if (fVar7 <= fVar18) {
          fVar18 = 1.0 / fVar18;
          pfVar16[-2] = fVar18 * pfVar16[-2];
          pfVar16[-1] = fVar18 * pfVar16[-1];
          *pfVar16 = fVar18 * *pfVar16;
        }
        if (2 < (int)lVar11 + lVar15) break;
        lVar10 = *(long *)(param_1 + 0x128);
        lVar15 = lVar15 + 1;
        lVar17 = lVar17 + 0x50;
        pfVar16 = pfVar16 + 4;
      } while (lVar15 < (long)(ulong)*(byte *)(lVar10 + 0x309));
    }
  }
  else {
    lVar11 = 0;
    puVar12 = (uint *)(lVar10 + 0x98);
    puVar13 = (uint *)((ulong)&fStack_190 | 8);
    do {
      uVar2 = puVar12[-1];
      uVar4 = *puVar12;
      lVar11 = lVar11 + 1;
      puVar13[-2] = puVar12[-2] ^ 0x80000000;
      puVar13[-1] = uVar2 ^ 0x80000000;
      *puVar13 = uVar4 ^ 0x80000000;
      puVar13[1] = 0x3f800000;
      puVar12 = puVar12 + 8;
      puVar13 = puVar13 + 4;
    } while (lVar11 < (long)(ulong)*(byte *)(lVar10 + 0x308));
    if ((int)lVar11 < 4) {
      cVar5 = *(char *)(lVar10 + 0x309);
      fVar7 = _UNK_027e519c;
      goto joined_r0x0269ac78;
    }
  }
  Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,0x19,&fStack_190,4);
code_r0x0269ad74:
  if (*(char *)(param_1 + 0x148) < '\0') {
    uStack_140 = *(undefined8 *)(param_1 + 0x140);
    uStack_100 = *(undefined8 *)(param_1 + 0x134);
    uStack_f8 = (ulong)(uint)*(float *)(param_1 + 0x13c);
    uStack_138 = CONCAT44(-(*(float *)(param_1 + 0x140) - *(float *)(param_1 + 0x144)) /
                          (*(float *)(param_1 + 0x13c) - *(float *)(param_1 + 0x138)),
                          _UNK_027f7284 /
                          (*(float *)(param_1 + 0x138) - *(float *)(param_1 + 0x134)));
    Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,10,&uStack_100,1);
    Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar14,0xb,&uStack_140,1);
  }
  return;
}

// ==== Aska::ParticleDrawContext::SetShaderConstant_Pixel()
// vaddr 0x259ae14 | ghidra 0x269ae14 | size 428 | symbol _ZN4Aska19ParticleDrawContext23SetShaderConstant_PixelEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19ParticleDrawContext23SetShaderConstant_PixelEv(long param_1)

{
  float *pfVar1;
  long lVar2;
  undefined8 uVar3;
  undefined1 auVar4 [16];
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  
  pfVar1 = &fStack_30;
  uVar3 = *(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  if ((*(char *)(param_1 + 0x131) != '\0') && ((*(byte *)(param_1 + 0x148) >> 3 & 1) != 0)) {
    uStack_24 = *(undefined4 *)(param_1 + 0x9c);
    lVar2 = *(long *)(param_1 + 0x128);
    fStack_30 = *(float *)(lVar2 + 0x260) * *(float *)(param_1 + 0x90);
    fStack_2c = *(float *)(lVar2 + 0x264) * *(float *)(param_1 + 0x94);
    fStack_28 = *(float *)(lVar2 + 0x268) * *(float *)(param_1 + 0x98);
    Aska::RenderDeviceGL::SetPixelShaderConstant(int, void const*, int)(uVar3,0x18,&fStack_30,1);
  }
  if ((*(byte *)(param_1 + 0x148) >> 1 & 1) == 0) {
    lVar2 = 0;
  }
  else {
    fStack_30 = *(float *)(param_1 + 0xbc);
    uStack_24 = *(undefined4 *)(param_1 + 0xc4);
    fStack_2c = 0.0;
    fStack_28 = 0.0;
    Aska::RenderDeviceGL::SetPixelShaderConstant(int, void const*, int)(uVar3,0x12,param_1,4);
    Aska::RenderDeviceGL::SetPixelShaderConstant(int, void const*, int)(uVar3,0x13,&fStack_30,1);
    lVar2 = param_1 + 0x100;
  }
  Aska::RenderDeviceGL::SetTexture(unsigned int, Aska::GpuResource* const*)(uVar3,2,lVar2);
  if (((*(byte *)(param_1 + 0x148) >> 1 & 1) == 0) && (*(int *)(param_1 + 0x114) != 5)) {
    auVar4 = NEON_fmov(0x3f800000,4);
    fStack_28 = auVar4._8_4_;
    uStack_24 = auVar4._12_4_;
    fStack_30 = auVar4._0_4_;
    fStack_2c = auVar4._4_4_;
  }
  else {
    pfVar1 = (float *)(*(long *)PTR__ZN4Aska6Global22m_pRenderTargetManagerE_02cbfa00 + 0xa0);
  }
  Aska::RenderDeviceGL::SetPixelShaderConstant(int, void const*, int)(uVar3,0x1b,pfVar1,1);
  if ((*(byte *)(param_1 + 0x148) >> 5 & 1) != 0) {
    Aska::RenderDeviceGL::SetPixelShaderConstant(int, void const*, int)(uVar3,0x15,*(long *)(param_1 + 0xd8) + 0x120,1);
    Aska::RenderDeviceGL::SetPixelShaderConstant(int, void const*, int)(uVar3,0x16,*(long *)(param_1 + 0xd8) + 0x130,1);
  }
  Aska::RenderDeviceGL::SetPixelShaderConstant(int, void const*, int)(uVar3,0x17,*(undefined8 *)(*(long *)(param_1 + 0xd8) + 0x150),3);
  Aska::RenderDeviceGL::SetPixelShaderConstant(int, void const*, int)(uVar3,0x1a,
                  PTR__ZN4Aska20GlobalShaderConstant15m_vHDRTransformE_02cb9e40 +
                  (ulong)(*(uint *)(*(long *)(param_1 + 0xd8) + 0x58) >> 2 & 1) * 0x10,1);
  return;
}


// FAILED to create function at 02c523b0 Aska::ParticleRenderableBase::vtable
// FAILED to create function at 02c526c0 Aska::ParticleRenderableBase::typeinfo
