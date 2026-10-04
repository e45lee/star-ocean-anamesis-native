// port/decomp/render/render_context.c: Ghidra decompiles for the render subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:34 UTC: tools/decomp.sh '--into' 'render/render_context' 'Aska::RenderContext::' 'Aska::RenderContextBase::' 'Aska::RenderContextBatch::' 'Aska::RenderContextBatchBase::' 'Aska::RenderState::' 'Aska::RenderStateManager::'

// ==== Aska::RenderContextBatch::RenderContextBatch()
// vaddr 0x2173c58 | ghidra 0x2273c58 | size 56 | symbol _ZN4Aska18RenderContextBatchC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18RenderContextBatchC2Ev(long param_1)

{
  memset(param_1 + 0x20,0,0x80);
  *(undefined2 *)(param_1 + 0x112) = 0;
  *(undefined1 *)(param_1 + 0x114) = 0;
  *(undefined8 *)(param_1 + 0xc0) = 0;
  *(undefined8 *)(param_1 + 200) = 0;
  *(undefined8 *)(param_1 + 0xb8) = 0;
  *(undefined8 *)(param_1 + 0xe0) = 0;
  *(undefined8 *)(param_1 + 0xe8) = 0;
  *(undefined8 *)(param_1 + 0x100) = 0;
  *(undefined8 *)(param_1 + 0x108) = 0;
  return;
}

// ==== Aska::RenderContextBatch::~RenderContextBatch()
// vaddr 0x2173c90 | ghidra 0x2273c90 | size 4 | symbol _ZN4Aska18RenderContextBatchD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18RenderContextBatchD1Ev(void)

{
  return;
}

// ==== Aska::RenderContextBatch::ApplyState()
// vaddr 0x2173c94 | ghidra 0x2273c94 | size 52 | symbol _ZN4Aska18RenderContextBatch10ApplyStateEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x02273ca8: Changing call to branch */

void _ZN4Aska18RenderContextBatch10ApplyStateEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 200);
  if ((lVar1 == 0) && (lVar1 = *(long *)(param_1 + 0xc0), lVar1 == 0)) {
    return;
  }
  (*(code *)PTR__ZN4Aska11RenderState5ApplyEPNS_14RenderDeviceGLE_02c94138)(lVar1,0);
  return;
}

// ==== Aska::RenderContextBatch::ApplyTextures()
// vaddr 0x2173cc8 | ghidra 0x2273cc8 | size 208 | symbol _ZN4Aska18RenderContextBatch13ApplyTexturesEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18RenderContextBatch13ApplyTexturesEv(long param_1)

{
  long lVar1;
  long *plVar2;
  uint uVar3;
  ulong uVar4;
  
  lVar1 = *(long *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  if (*(int *)(lVar1 + 0xeaa88) != 0) {
    uVar3 = *(int *)(lVar1 + 0xeaa88) - 1;
    plVar2 = (long *)(param_1 + (ulong)uVar3 * 8 + 0x20);
    do {
      if (*plVar2 == 0) {
        Aska::RenderDeviceGL::RemoveTexture(unsigned int)(lVar1,uVar3);
      }
      else {
        Aska::RenderDeviceGL::SetTexture(unsigned int, Aska::GpuResource* const*)(lVar1,uVar3,plVar2);
      }
      uVar3 = uVar3 - 1;
      plVar2 = plVar2 + -1;
    } while (uVar3 != 0xffffffff);
  }
  uVar3 = *(uint *)(lVar1 + 0xeaa8c);
  if (2 < uVar3) {
    uVar3 = 3;
  }
  if (uVar3 != 0) {
    uVar4 = 0;
    plVar2 = (long *)(param_1 + 0xa0);
    do {
      if (*plVar2 != 0) {
        Aska::RenderDeviceGL::SetTexture(unsigned int, Aska::GpuResource* const*)(lVar1,uVar4 & 0xffffffff,plVar2);
      }
      uVar4 = uVar4 + 1;
      plVar2 = plVar2 + 1;
    } while (uVar4 < uVar3);
  }
  return;
}

// ==== Aska::RenderContextBatch::GetTexturesTextureStage(int)
// vaddr 0x2173d98 | ghidra 0x2273d98 | size 84 | symbol _ZN4Aska18RenderContextBatch23GetTexturesTextureStageEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska18RenderContextBatch23GetTexturesTextureStageEi(long param_1,int param_2)

{
  long lVar1;
  int iVar2;
  
  if (*(uint *)(*(long *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0 + 0xeaa88) != 0) {
    lVar1 = 0;
    iVar2 = 0;
    do {
      if (*(long *)(param_1 + 0x20 + lVar1 * 8) != 0) {
        if (iVar2 == param_2) {
          return lVar1;
        }
        iVar2 = iVar2 + 1;
      }
      lVar1 = lVar1 + 1;
    } while ((uint)lVar1 < *(uint *)(*(long *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0 + 0xeaa88));
  }
  return 0;
}

// ==== Aska::RenderContextBatch::PrepairMatricies()
// vaddr 0x2173dec | ghidra 0x2273dec | size 4 | symbol _ZN4Aska18RenderContextBatch16PrepairMatriciesEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18RenderContextBatch16PrepairMatriciesEv(void)

{
  return;
}

// ==== Aska::RenderContextBatch::ApplyShaderConstants(unsigned long, Aska::ShaderNodeHandler*)
// vaddr 0x2173df0 | ghidra 0x2273df0 | size 80 | symbol _ZN4Aska18RenderContextBatch20ApplyShaderConstantsEmPNS_17ShaderNodeHandlerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18RenderContextBatch20ApplyShaderConstantsEmPNS_17ShaderNodeHandlerE
               (long param_1,undefined8 param_2,undefined8 param_3)

{
  Aska::RenderContextBatchBase::Apply(unsigned long, Aska::RenderDeviceGL*, Aska::ShaderNodeHandler*)(param_1,param_2,*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,param_3);
  if (*(long *)(param_1 + 0x108) != 0) {
    (*(code *)
      PTR__ZN4Aska21ShaderConstantHandler17SetShaderConstantEmPNS_17ShaderNodeHandlerE_02c9aae0)
              (*(long *)(param_1 + 0x108),param_2,param_3);
    return;
  }
  return;
}

// ==== Aska::RenderContext::RenderContext()
// vaddr 0x2173e40 | ghidra 0x2273e40 | size 200 | symbol _ZN4Aska13RenderContextC2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13RenderContextC1Ev(undefined8 *param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined1 auVar9 [16];
  
  uVar8 = _UNK_027dbb38;
  uVar7 = _UNK_027dbb30;
  uVar6 = _UNK_027dbb28;
  uVar5 = _UNK_027dbb20;
  uVar4 = _UNK_027dbb18;
  uVar3 = _UNK_027dbb10;
  uVar2 = _UNK_027dbb08;
  uVar1 = _UNK_027dbb00;
  *(byte *)((long)param_1 + 10) = *(byte *)((long)param_1 + 10) & 0x8c;
  *param_1 = 0;
  *(undefined2 *)(param_1 + 1) = 0;
  *(undefined4 *)(param_1 + 0xb) = 0;
  *(undefined8 *)((long)param_1 + 0x35) = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[3] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[8] = 0;
  *(undefined8 *)((long)param_1 + 0xec) = 0;
  *(undefined8 *)((long)param_1 + 0xe4) = 0;
  param_1[0x1f] = 0;
  param_1[0x20] = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0x3f800000;
  *(undefined4 *)((long)param_1 + 0xf4) = 0x3f800000;
  param_1[0xd] = uVar2;
  param_1[0xc] = uVar1;
  param_1[0xf] = uVar4;
  param_1[0xe] = uVar3;
  param_1[0x11] = uVar6;
  param_1[0x10] = uVar5;
  param_1[0x13] = uVar8;
  param_1[0x12] = uVar7;
  param_1[0x15] = uVar2;
  param_1[0x14] = uVar1;
  param_1[0x17] = uVar4;
  param_1[0x16] = uVar3;
  param_1[0x19] = uVar6;
  param_1[0x18] = uVar5;
  param_1[0x1b] = uVar8;
  param_1[0x1a] = uVar7;
  param_1[0x22] = uVar2;
  param_1[0x21] = uVar1;
  param_1[0x23] = 0x3f80000000000000;
  *(undefined4 *)(param_1 + 0x2e) = 0x3f800000;
  *(undefined8 *)((long)param_1 + 0x17c) = 0;
  *(undefined8 *)((long)param_1 + 0x174) = 0;
  auVar9 = NEON_fmov(0x3f800000,4);
  *(undefined4 *)((long)param_1 + 0x184) = 0x3f800000;
  param_1[0x31] = 0;
  param_1[0x32] = 0;
  *(undefined4 *)(param_1 + 0x33) = 0x3f800000;
  *(undefined8 *)((long)param_1 + 0x19c) = 0;
  *(undefined8 *)((long)param_1 + 0x1a4) = 0;
  *(undefined4 *)((long)param_1 + 0x1ac) = 0x3f800000;
  param_1[0x25] = auVar9._8_8_;
  param_1[0x24] = auVar9._0_8_;
  param_1[0x27] = uVar8;
  param_1[0x26] = uVar7;
  return;
}

// ==== Aska::RenderContext::~RenderContext()
// vaddr 0x2173f08 | ghidra 0x2273f08 | size 12 | symbol _ZN4Aska13RenderContextD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13RenderContextD2Ev(undefined8 *param_1)

{
  *param_1 = 0;
  *(undefined2 *)(param_1 + 1) = 0;
  return;
}

// ==== Aska::RenderContext::AllocBatch(int)
// vaddr 0x2173f14 | ghidra 0x2273f14 | size 4 | symbol _ZN4Aska13RenderContext10AllocBatchEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13RenderContext10AllocBatchEi(void)

{
  (*(code *)PTR__ZN4Aska17RenderContextBase10AllocBatchEi_02ca0548)();
  return;
}

// ==== Aska::RenderContext::GetBatchArray(int)
// vaddr 0x2173f18 | ghidra 0x2273f18 | size 16 | symbol _ZN4Aska13RenderContext13GetBatchArrayEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska13RenderContext13GetBatchArrayEi(long *param_1,int param_2)

{
  return *param_1 + (long)param_2 * 0x130;
}

// ==== Aska::RenderContext::OnPaint()
// vaddr 0x2173f28 | ghidra 0x2273f28 | size 1136 | symbol _ZN4Aska13RenderContext7OnPaintEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x02273f50: Changing call to branch */
/* WARNING: Possible PIC construction at 0x02274058: Changing call to branch */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13RenderContext7OnPaintEv(long *param_1)

{
  long lVar1;
  long lVar2;
  ushort uVar3;
  undefined *puVar4;
  int iVar5;
  long lVar6;
  long lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  long lVar10;
  uint uVar11;
  long lVar12;
  long lVar13;
  ulong uVar14;
  long *plVar15;
  long lVar16;
  long lVar17;
  float fVar18;
  
  lVar13 = _UNK_027dbb38;
  lVar1 = _UNK_027dbb30;
  lVar7 = _UNK_027dbb28;
  lVar12 = _UNK_027dbb20;
  lVar10 = _UNK_027dbb18;
  lVar17 = _UNK_027dbb10;
  lVar16 = _UNK_027dbb00;
  lVar6 = param_1[9];
  if (lVar6 == 0) {
    if ((*(byte *)((long)param_1 + 10) >> 2 & 1) == 0) {
      lVar6 = *(long *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198;
      param_1[0xd] = _UNK_027dbb08;
      param_1[0xc] = lVar16;
      param_1[0xf] = lVar10;
      param_1[0xe] = lVar17;
      param_1[0x11] = lVar7;
      param_1[0x10] = lVar12;
      param_1[0x13] = lVar13;
      param_1[0x12] = lVar1;
      fVar18 = (float)NEON_ucvtf((uint)*(ushort *)(lVar6 + 0x28));
      *(float *)(param_1 + 0xc) = 2.0 / fVar18;
      uVar3 = *(ushort *)(lVar6 + 0x2a);
      param_1[0x12] = 0x3f800000bf800000;
      *(undefined4 *)(param_1 + 0x11) = 0x3f800000;
      *(float *)((long)param_1 + 0x74) = -2.0 / (float)uVar3;
      *(undefined4 *)((long)param_1 + 0x9c) = 0x3f800000;
    }
    plVar15 = (long *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
    iVar5 = Aska::RenderDeviceGL::GetGLVersion() const(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
    if (((iVar5 != 0) && ((*(byte *)((long)param_1 + 10) >> 2 & 1) != 0)) &&
       (*(char *)((long)param_1 + 0x3c) != '\0')) {
      Aska::RenderDeviceGL::BindInstanceVertexBuffer(Aska::GpuResource*)(*plVar15,param_1[8]);
      Aska::RenderDeviceGL::SetInstanceCount(unsigned int)(*plVar15,(int)param_1[7]);
      if ((*(byte *)((long)param_1 + 0x3c) >> 1 & 1) == 0) {
        uVar8 = 7;
      }
      else {
        uVar8 = 0xf;
      }
      Aska::RenderDeviceGL::SetInstanceVertexFormat(int, int)(*plVar15,uVar8,0x40);
    }
    if ((short)param_1[1] != 0) {
      lVar16 = 0;
      do {
        lVar17 = *param_1;
        lVar12 = lVar17 + lVar16 * 0x130;
        lVar6 = *(long *)(lVar12 + 200);
        lVar10 = *(long *)(lVar12 + 0xb8);
        if (lVar6 != 0) goto code_r0x011b8290;
        lVar7 = *(long *)(lVar17 + lVar16 * 0x130 + 0xc0);
        if (lVar7 != 0) {
          Aska::RenderState::Apply(Aska::RenderDeviceGL*)(lVar7,0);
        }
        lVar7 = *plVar15;
        iVar5 = *(int *)(lVar7 + 0xeaa88);
        if (iVar5 != 0) {
          lVar1 = lVar17 + lVar16 * 0x130 + (ulong)(iVar5 - 1) * 8 + 0x20;
          lVar6 = 0;
          lVar13 = lVar1;
          do {
            lVar2 = (ulong)(iVar5 - 1) + lVar6;
            if (*(long *)(lVar1 + lVar6 * 8) == 0) {
              Aska::RenderDeviceGL::RemoveTexture(unsigned int)(lVar7,lVar2);
            }
            else {
              Aska::RenderDeviceGL::SetTexture(unsigned int, Aska::GpuResource* const*)(lVar7,lVar2,lVar13);
            }
            lVar6 = lVar6 + -1;
            lVar13 = lVar13 + -8;
          } while (-iVar5 != (int)lVar6);
        }
        uVar11 = *(uint *)(lVar7 + 0xeaa8c);
        if (2 < uVar11) {
          uVar11 = 3;
        }
        if (uVar11 != 0) {
          uVar14 = 0;
          plVar15 = (long *)(lVar17 + lVar16 * 0x130 + 0xa0);
          do {
            if (*plVar15 != 0) {
              Aska::RenderDeviceGL::SetTexture(unsigned int, Aska::GpuResource* const*)(lVar7,uVar14 & 0xffffffff,plVar15);
            }
            uVar14 = uVar14 + 1;
            plVar15 = plVar15 + 1;
          } while (uVar14 < uVar11);
        }
        plVar15 = (long *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
        puVar4 = PTR__ZN4Aska6Global20m_pShaderLinkManagerE_02cb93f8;
        if ((*(byte *)((long)param_1 + 10) >> 2 & 1) == 0) {
          lVar17 = lVar17 + lVar16 * 0x130;
          Aska::ShaderLinkManager::SetPresetShader(int, int)(*(undefined8 *)PTR__ZN4Aska6Global20m_pShaderLinkManagerE_02cb93f8,
                          *(undefined4 *)(lVar17 + 0xe0),*(undefined4 *)(lVar17 + 0xe8));
          Aska::ShaderLinkManager::SetPresetShaderConstants()(*(undefined8 *)puVar4);
code_r0x02274214:
          lVar17 = *(long *)(lVar10 + 0x10);
          uVar8 = *plVar15;
          lVar12 = *(long *)(lVar17 + 8);
          if (lVar12 == 0) {
            uVar9 = 0;
          }
          else {
            if (((*(int *)(lVar12 + 0x68) != 0) || (*(long *)(lVar12 + 0x48) == 0)) &&
               (uVar14 = (**(code **)**(undefined8 **)(lVar12 + 0x40))
                                   (*(undefined8 **)(lVar12 + 0x40),lVar12), (uVar14 & 1) != 0)) {
              *(undefined4 *)(lVar12 + 0x68) = 0;
            }
            uVar9 = *(undefined8 *)(*(long *)(lVar17 + 8) + 0x48);
          }
          Aska::RenderDeviceGL::BindVertexBuffer(unsigned long, void*)(uVar8,uVar9,0);
          Aska::RenderDeviceGL::BindVertexFormat(Aska::VertexBuffer*)(*plVar15,lVar17);
          Aska::RenderablePrimitive::Kick(unsigned int)(lVar10,0);
        }
        else {
          lVar17 = lVar17 + lVar16 * 0x130;
          Aska::ShaderLinkManager::SetBindedRenderingShader(void*, void*, void*)(*(undefined8 *)PTR__ZN4Aska6Global20m_pShaderLinkManagerE_02cb93f8,
                          *(undefined8 *)(lVar17 + 0xe0),*(undefined8 *)(lVar17 + 0xe8),0);
          Aska::RenderContextBase::SetShaderConstant_Vertex(unsigned long, Aska::ShaderNodeHandler*)(param_1,0,0);
          Aska::RenderContextBase::SetShaderConstant_Pixel(unsigned long, Aska::ShaderNodeHandler*)(param_1,0,0);
          uVar8 = *(undefined8 *)
                   (*(long *)(param_1[4] + 8) + (ulong)*(byte *)(lVar17 + 0x114) * 0x1b8 + 0x20);
          Aska::RenderContextBatchBase::Apply(unsigned long, Aska::RenderDeviceGL*, Aska::ShaderNodeHandler*)(lVar12,0,*plVar15,uVar8);
          if (*(long *)(lVar17 + 0x108) != 0) {
            Aska::ShaderConstantHandler::SetShaderConstant(unsigned long, Aska::ShaderNodeHandler*)(*(long *)(lVar17 + 0x108),0,uVar8);
          }
          if (*(char *)((long)param_1 + 0x3c) == '\0') goto code_r0x02274214;
          lVar17 = *(long *)(lVar10 + 0x10);
          uVar8 = *plVar15;
          lVar12 = *(long *)(lVar17 + 8);
          if (lVar12 == 0) {
            uVar9 = 0;
          }
          else {
            if (((*(int *)(lVar12 + 0x68) != 0) || (*(long *)(lVar12 + 0x48) == 0)) &&
               (uVar14 = (**(code **)**(undefined8 **)(lVar12 + 0x40))
                                   (*(undefined8 **)(lVar12 + 0x40),lVar12), (uVar14 & 1) != 0)) {
              *(undefined4 *)(lVar12 + 0x68) = 0;
            }
            uVar9 = *(undefined8 *)(*(long *)(lVar17 + 8) + 0x48);
          }
          Aska::RenderDeviceGL::BindVertexBuffer(unsigned long, void*)(uVar8,uVar9,0);
          Aska::RenderDeviceGL::BindVertexFormat(Aska::VertexBuffer*)(*plVar15,lVar17);
          if ((int)param_1[7] != 0) {
            uVar11 = 0;
            do {
              Aska::RenderContextBase::SetShaderConstant_Vertex_ForInstancing(unsigned int)(param_1,uVar11);
              Aska::RenderablePrimitive::Kick(unsigned int)(lVar10,0);
              uVar11 = uVar11 + 1;
            } while (uVar11 < *(uint *)(param_1 + 7));
          }
        }
        Aska::RenderDeviceGL::SetVertexShader(Aska::VertexShader*)(*plVar15,0);
        Aska::RenderDeviceGL::SetPixelShader(Aska::PixelShader*)(*plVar15,0);
        Aska::RenderDeviceGL::BindVertexBuffer(unsigned long, void*)(*plVar15,0,0);
        lVar16 = lVar16 + 1;
      } while (lVar16 < (long)(ulong)*(ushort *)(param_1 + 1));
    }
    iVar5 = Aska::RenderDeviceGL::GetGLVersion() const(*plVar15);
    if (((iVar5 != 0) && ((*(byte *)((long)param_1 + 10) >> 2 & 1) != 0)) &&
       (*(char *)((long)param_1 + 0x3c) != '\0')) {
      Aska::RenderDeviceGL::BindInstanceVertexBuffer(Aska::GpuResource*)(*plVar15,0);
    }
    if (param_1[10] == 0) {
      return;
    }
    lVar6 = param_1[9];
  }
code_r0x011b8290:
  (*(code *)PTR__ZN4Aska11RenderState5ApplyEPNS_14RenderDeviceGLE_02c94138)(lVar6,0);
  return;
}

// ==== Aska::RenderContext::PrepairMatricies()
// vaddr 0x2174398 | ghidra 0x2274398 | size 128 | symbol _ZN4Aska13RenderContext16PrepairMatriciesEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13RenderContext16PrepairMatriciesEv(long param_1)

{
  ushort uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  long lVar9;
  float fVar10;
  
  uVar8 = _UNK_027dbb38;
  uVar7 = _UNK_027dbb30;
  uVar6 = _UNK_027dbb28;
  uVar5 = _UNK_027dbb20;
  uVar4 = _UNK_027dbb18;
  uVar3 = _UNK_027dbb10;
  uVar2 = _UNK_027dbb00;
  if ((*(byte *)(param_1 + 10) >> 2 & 1) == 0) {
    lVar9 = *(long *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198;
    *(undefined8 *)(param_1 + 0x68) = _UNK_027dbb08;
    *(undefined8 *)(param_1 + 0x60) = uVar2;
    *(undefined8 *)(param_1 + 0x78) = uVar4;
    *(undefined8 *)(param_1 + 0x70) = uVar3;
    *(undefined8 *)(param_1 + 0x88) = uVar6;
    *(undefined8 *)(param_1 + 0x80) = uVar5;
    *(undefined8 *)(param_1 + 0x98) = uVar8;
    *(undefined8 *)(param_1 + 0x90) = uVar7;
    fVar10 = (float)NEON_ucvtf((uint)*(ushort *)(lVar9 + 0x28));
    *(float *)(param_1 + 0x60) = 2.0 / fVar10;
    uVar1 = *(ushort *)(lVar9 + 0x2a);
    *(undefined8 *)(param_1 + 0x90) = 0x3f800000bf800000;
    *(undefined4 *)(param_1 + 0x88) = 0x3f800000;
    *(float *)(param_1 + 0x74) = -2.0 / (float)uVar1;
    *(undefined4 *)(param_1 + 0x9c) = 0x3f800000;
  }
  return;
}

// ==== Aska::RenderContext::Static::SetShaderConstantLightMaskGroup(Aska::RenderDeviceGL*, Aska::LightManager::LightContext*)
// vaddr 0x2174418 | ghidra 0x2274418 | size 224 | symbol _ZN4Aska13RenderContext6Static31SetShaderConstantLightMaskGroupEPNS_14RenderDeviceGLEPNS_12LightManager12LightContextE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x02274434: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0227445c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022744a4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022744cc: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02274438) */
/* WARNING: Removing unreachable block (ram,0x02274460) */
/* WARNING: Removing unreachable block (ram,0x022744ec) */
/* WARNING: Removing unreachable block (ram,0x02274480) */
/* WARNING: Removing unreachable block (ram,0x02274494) */
/* WARNING: Removing unreachable block (ram,0x022744a8) */
/* WARNING: Removing unreachable block (ram,0x022744bc) */
/* WARNING: Removing unreachable block (ram,0x022744d0) */
/* WARNING: Recovered jumptable eliminated as dead code */

void _ZN4Aska13RenderContext6Static31SetShaderConstantLightMaskGroupEPNS_14RenderDeviceGLEPNS_12LightManager12LightContextE
               (undefined8 param_1,long param_2)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL22SetPixelShaderConstantEiPKvi_02c965b0)
            (param_1,0x16,param_2 + 0xa0,1);
  return;
}

// ==== Aska::RenderState::RenderState()
// vaddr 0x2189e9c | ghidra 0x2289e9c | size 12 | symbol _ZN4Aska11RenderStateC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderStateC2Ev(undefined8 *param_1)

{
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  return;
}

// ==== Aska::RenderState::~RenderState()
// vaddr 0x2189ea8 | ghidra 0x2289ea8 | size 72 | symbol _ZN4Aska11RenderStateD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderStateD1Ev(long *param_1)

{
  if (*param_1 != 0) {
    Aska::RenderStatePool::Free(void*, int)(*(undefined8 *)PTR__ZN4Aska6Global18m_pRenderStatePoolE_02cbf5f0,*param_1,
                    (int)param_1[2]);
    *param_1 = 0;
  }
  *(undefined4 *)(param_1 + 2) = 0;
  return;
}

// ==== Aska::RenderState::Alloc(int)
// vaddr 0x2189ef0 | ghidra 0x2289ef0 | size 68 | symbol _ZN4Aska11RenderState5AllocEi | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska11RenderState5AllocEi(long *param_1,undefined4 param_2)

{
  long lVar1;
  
  lVar1 = Aska::RenderStatePool::Alloc(int)(*(undefined8 *)PTR__ZN4Aska6Global18m_pRenderStatePoolE_02cbf5f0);
  *param_1 = lVar1;
  if (lVar1 != 0) {
    param_1[1] = lVar1;
    *(undefined4 *)(param_1 + 2) = param_2;
    *(undefined4 *)((long)param_1 + 0x14) = 0;
  }
  return lVar1 != 0;
}

// ==== Aska::RenderState::Reset()
// vaddr 0x2189f34 | ghidra 0x2289f34 | size 16 | symbol _ZN4Aska11RenderState5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState5ResetEv(undefined8 *param_1)

{
  *(undefined4 *)((long)param_1 + 0x14) = 0;
  param_1[1] = *param_1;
  return;
}

// ==== Aska::RenderState::Release()
// vaddr 0x2189f44 | ghidra 0x2289f44 | size 68 | symbol _ZN4Aska11RenderState7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState7ReleaseEv(long *param_1)

{
  if (*param_1 != 0) {
    Aska::RenderStatePool::Free(void*, int)(*(undefined8 *)PTR__ZN4Aska6Global18m_pRenderStatePoolE_02cbf5f0,*param_1,
                    (int)param_1[2]);
    *param_1 = 0;
  }
  *(undefined4 *)(param_1 + 2) = 0;
  (*(code *)PTR__ZN4Aska18RenderStateManager6ReturnEPNS_11RenderStateE_02cafde8)
            (*(undefined8 *)PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10,param_1);
  return;
}

// ==== Aska::RenderState::SetFillMode(int)
// vaddr 0x2189f88 | ghidra 0x2289f88 | size 4 | symbol _ZN4Aska11RenderState11SetFillModeEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState11SetFillModeEi(void)

{
  return;
}

// ==== Aska::RenderState::SetCullMode(int)
// vaddr 0x2189f8c | ghidra 0x2289f8c | size 40 | symbol _ZN4Aska11RenderState11SetCullModeEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState11SetCullModeEi(long param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_1 + 8);
  *(undefined1 **)(param_1 + 8) = puVar1 + 2;
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
  *puVar1 = 0xdf;
  puVar1[1] = param_2;
  return;
}

// ==== Aska::RenderState::EnableZTest(bool)
// vaddr 0x2189fb4 | ghidra 0x2289fb4 | size 44 | symbol _ZN4Aska11RenderState11EnableZTestEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState11EnableZTestEb(long param_1,byte param_2)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_1 + 8);
  *(undefined1 **)(param_1 + 8) = puVar1 + 2;
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
  *puVar1 = 0xdb;
  puVar1[1] = param_2 & 1;
  return;
}

// ==== Aska::RenderState::EnableZWrite(bool)
// vaddr 0x2189fe0 | ghidra 0x2289fe0 | size 44 | symbol _ZN4Aska11RenderState12EnableZWriteEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState12EnableZWriteEb(long param_1,byte param_2)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_1 + 8);
  *(undefined1 **)(param_1 + 8) = puVar1 + 2;
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
  *puVar1 = 0xdc;
  puVar1[1] = param_2 & 1;
  return;
}

// ==== Aska::RenderState::SetZTestFunction(int)
// vaddr 0x218a00c | ghidra 0x228a00c | size 40 | symbol _ZN4Aska11RenderState16SetZTestFunctionEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState16SetZTestFunctionEi(long param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_1 + 8);
  *(undefined1 **)(param_1 + 8) = puVar1 + 2;
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
  *puVar1 = 0xdd;
  puVar1[1] = param_2;
  return;
}

// ==== Aska::RenderState::SetDepthBias(float, float)
// vaddr 0x218a034 | ghidra 0x228a034 | size 80 | symbol _ZN4Aska11RenderState12SetDepthBiasEff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState12SetDepthBiasEff(undefined4 param_1,undefined4 param_2,long param_3)

{
  undefined1 *puVar1;
  
  if (*(uint *)(param_3 + 0x14) < *(uint *)(param_3 + 0x10)) {
    puVar1 = *(undefined1 **)(param_3 + 8);
    *(uint *)(param_3 + 0x14) = *(uint *)(param_3 + 0x14) + 1;
    *(undefined1 **)(param_3 + 8) = puVar1 + 9;
  }
  else {
    puVar1 = (undefined1 *)0x0;
  }
  *puVar1 = 0xde;
  *(undefined4 *)(puVar1 + 1) = param_1;
  *(undefined4 *)(puVar1 + 5) = param_2;
  return;
}

// ==== Aska::RenderState::EnableAlphaBlend(bool)
// vaddr 0x218a084 | ghidra 0x228a084 | size 44 | symbol _ZN4Aska11RenderState16EnableAlphaBlendEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState16EnableAlphaBlendEb(long param_1,byte param_2)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_1 + 8);
  *(undefined1 **)(param_1 + 8) = puVar1 + 2;
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
  *puVar1 = 200;
  puVar1[1] = param_2 & 1;
  return;
}

// ==== Aska::RenderState::SetAlphaBlendFunction(Aska::AlphaBlend::Operation, Aska::SeparateAlphaBlendMode::E)
// vaddr 0x218a0b0 | ghidra 0x228a0b0 | size 76 | symbol _ZN4Aska11RenderState21SetAlphaBlendFunctionENS_10AlphaBlend9OperationENS_22SeparateAlphaBlendMode1EE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState21SetAlphaBlendFunctionENS_10AlphaBlend9OperationENS_22SeparateAlphaBlendMode1EE
               (long param_1,uint param_2,uint param_3)

{
  undefined1 *puVar1;
  
  if ((param_2 < 0x11) && (param_3 < 3)) {
    if (*(uint *)(param_1 + 0x14) < *(uint *)(param_1 + 0x10)) {
      puVar1 = *(undefined1 **)(param_1 + 8);
      *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) + 1;
      *(undefined1 **)(param_1 + 8) = puVar1 + 3;
    }
    else {
      puVar1 = (undefined1 *)0x0;
    }
    puVar1[1] = (char)param_2;
    *puVar1 = 0xc9;
    puVar1[2] = (char)param_3;
  }
  return;
}

// ==== Aska::RenderState::EnableAlphaTest(bool)
// vaddr 0x218a0fc | ghidra 0x228a0fc | size 4 | symbol _ZN4Aska11RenderState15EnableAlphaTestEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState15EnableAlphaTestEb(void)

{
  return;
}

// ==== Aska::RenderState::SetAlphaTestFunction(int, int)
// vaddr 0x218a100 | ghidra 0x228a100 | size 4 | symbol _ZN4Aska11RenderState20SetAlphaTestFunctionEii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState20SetAlphaTestFunctionEii(void)

{
  return;
}

// ==== Aska::RenderState::SetAlphaToCoverage(int)
// vaddr 0x218a104 | ghidra 0x228a104 | size 40 | symbol _ZN4Aska11RenderState18SetAlphaToCoverageEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState18SetAlphaToCoverageEi(long param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_1 + 8);
  *(undefined1 **)(param_1 + 8) = puVar1 + 2;
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
  *puVar1 = 0xce;
  puVar1[1] = param_2;
  return;
}

// ==== Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)
// vaddr 0x218a12c | ghidra 0x228a12c | size 40 | symbol _ZN4Aska11RenderState13EnableStencilENS_11StencilMode4ModeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState13EnableStencilENS_11StencilMode4ModeE(long param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_1 + 8);
  *(undefined1 **)(param_1 + 8) = puVar1 + 2;
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
  *puVar1 = 0xe2;
  puVar1[1] = param_2;
  return;
}

// ==== Aska::RenderState::SetStencilOp(int, int, int, int, int, short)
// vaddr 0x218a154 | ghidra 0x228a154 | size 60 | symbol _ZN4Aska11RenderState12SetStencilOpEiiiiis | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState12SetStencilOpEiiiiis
               (long param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
               undefined1 param_5,undefined1 param_6,undefined1 param_7)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_1 + 8);
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
  *(undefined1 **)(param_1 + 8) = puVar1 + 7;
  *puVar1 = 0xe3;
  puVar1[1] = param_2;
  puVar1[2] = param_3;
  puVar1[3] = param_4;
  puVar1[4] = param_5;
  puVar1[5] = param_6;
  puVar1[6] = param_7;
  return;
}

// ==== Aska::RenderState::SetStencilOpCCW(int, int, int, int, int, short)
// vaddr 0x218a190 | ghidra 0x228a190 | size 60 | symbol _ZN4Aska11RenderState15SetStencilOpCCWEiiiiis | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState15SetStencilOpCCWEiiiiis
               (long param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
               undefined1 param_5,undefined1 param_6,undefined1 param_7)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_1 + 8);
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
  *(undefined1 **)(param_1 + 8) = puVar1 + 7;
  *puVar1 = 0xe4;
  puVar1[1] = param_2;
  puVar1[2] = param_3;
  puVar1[3] = param_4;
  puVar1[4] = param_5;
  puVar1[5] = param_6;
  puVar1[6] = param_7;
  return;
}

// ==== Aska::RenderState::SetTextureSamplingFilter(int, Aska::TexSamp::Filter)
// vaddr 0x218a1cc | ghidra 0x228a1cc | size 60 | symbol _ZN4Aska11RenderState24SetTextureSamplingFilterEiNS_7TexSamp6FilterE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState24SetTextureSamplingFilterEiNS_7TexSamp6FilterE
               (long param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  if (*(uint *)(param_1 + 0x14) < *(uint *)(param_1 + 0x10)) {
    puVar1 = *(undefined1 **)(param_1 + 8);
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) + 1;
    *(undefined1 **)(param_1 + 8) = puVar1 + 3;
  }
  else {
    puVar1 = (undefined1 *)0x0;
  }
  puVar1[1] = param_2;
  *puVar1 = 0xcf;
  puVar1[2] = param_3;
  return;
}

// ==== Aska::RenderState::SetTextureSamplingMipmapFilter(int, Aska::TexSamp::MipFilter)
// vaddr 0x218a208 | ghidra 0x228a208 | size 60 | symbol _ZN4Aska11RenderState30SetTextureSamplingMipmapFilterEiNS_7TexSamp9MipFilterE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState30SetTextureSamplingMipmapFilterEiNS_7TexSamp9MipFilterE
               (long param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  if (*(uint *)(param_1 + 0x14) < *(uint *)(param_1 + 0x10)) {
    puVar1 = *(undefined1 **)(param_1 + 8);
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) + 1;
    *(undefined1 **)(param_1 + 8) = puVar1 + 3;
  }
  else {
    puVar1 = (undefined1 *)0x0;
  }
  puVar1[1] = param_2;
  *puVar1 = 0xd0;
  puVar1[2] = param_3;
  return;
}

// ==== Aska::RenderState::SetTextureSamplingWrapMode(int, Aska::TexWrap::Mode)
// vaddr 0x218a244 | ghidra 0x228a244 | size 60 | symbol _ZN4Aska11RenderState26SetTextureSamplingWrapModeEiNS_7TexWrap4ModeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState26SetTextureSamplingWrapModeEiNS_7TexWrap4ModeE
               (long param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  if (*(uint *)(param_1 + 0x14) < *(uint *)(param_1 + 0x10)) {
    puVar1 = *(undefined1 **)(param_1 + 8);
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) + 1;
    *(undefined1 **)(param_1 + 8) = puVar1 + 3;
  }
  else {
    puVar1 = (undefined1 *)0x0;
  }
  puVar1[1] = param_2;
  *puVar1 = 0xd1;
  puVar1[2] = param_3;
  return;
}

// ==== Aska::RenderState::SetTextureSamplingWrapModeU(int, Aska::TexWrap::Mode)
// vaddr 0x218a280 | ghidra 0x228a280 | size 60 | symbol _ZN4Aska11RenderState27SetTextureSamplingWrapModeUEiNS_7TexWrap4ModeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState27SetTextureSamplingWrapModeUEiNS_7TexWrap4ModeE
               (long param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  if (*(uint *)(param_1 + 0x14) < *(uint *)(param_1 + 0x10)) {
    puVar1 = *(undefined1 **)(param_1 + 8);
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) + 1;
    *(undefined1 **)(param_1 + 8) = puVar1 + 3;
  }
  else {
    puVar1 = (undefined1 *)0x0;
  }
  puVar1[1] = param_2;
  *puVar1 = 0xd2;
  puVar1[2] = param_3;
  return;
}

// ==== Aska::RenderState::SetTextureSamplingWrapModeV(int, Aska::TexWrap::Mode)
// vaddr 0x218a2bc | ghidra 0x228a2bc | size 60 | symbol _ZN4Aska11RenderState27SetTextureSamplingWrapModeVEiNS_7TexWrap4ModeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState27SetTextureSamplingWrapModeVEiNS_7TexWrap4ModeE
               (long param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  if (*(uint *)(param_1 + 0x14) < *(uint *)(param_1 + 0x10)) {
    puVar1 = *(undefined1 **)(param_1 + 8);
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) + 1;
    *(undefined1 **)(param_1 + 8) = puVar1 + 3;
  }
  else {
    puVar1 = (undefined1 *)0x0;
  }
  puVar1[1] = param_2;
  *puVar1 = 0xd3;
  puVar1[2] = param_3;
  return;
}

// ==== Aska::RenderState::SetTextureSamplingMipmapLODBias(int, int)
// vaddr 0x218a2f8 | ghidra 0x228a2f8 | size 4 | symbol _ZN4Aska11RenderState31SetTextureSamplingMipmapLODBiasEii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState31SetTextureSamplingMipmapLODBiasEii(void)

{
  return;
}

// ==== Aska::RenderState::SetTextureSamplingTrilinearClamp(int, unsigned int)
// vaddr 0x218a2fc | ghidra 0x228a2fc | size 4 | symbol _ZN4Aska11RenderState32SetTextureSamplingTrilinearClampEij | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState32SetTextureSamplingTrilinearClampEij(void)

{
  return;
}

// ==== Aska::RenderState::SetTextureSamplingMaxAnisotropic(int, unsigned int)
// vaddr 0x218a300 | ghidra 0x228a300 | size 60 | symbol _ZN4Aska11RenderState32SetTextureSamplingMaxAnisotropicEij | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState32SetTextureSamplingMaxAnisotropicEij
               (long param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  if (*(uint *)(param_1 + 0x14) < *(uint *)(param_1 + 0x10)) {
    puVar1 = *(undefined1 **)(param_1 + 8);
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) + 1;
    *(undefined1 **)(param_1 + 8) = puVar1 + 3;
  }
  else {
    puVar1 = (undefined1 *)0x0;
  }
  puVar1[1] = param_2;
  *puVar1 = 0xd9;
  puVar1[2] = param_3;
  return;
}

// ==== Aska::RenderState::SetTextureSamplingAnisotropicBias(int, int)
// vaddr 0x218a33c | ghidra 0x228a33c | size 4 | symbol _ZN4Aska11RenderState33SetTextureSamplingAnisotropicBiasEii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState33SetTextureSamplingAnisotropicBiasEii(void)

{
  return;
}

// ==== Aska::RenderState::Apply(Aska::RenderDeviceGL*)
// vaddr 0x218a340 | ghidra 0x228a340 | size 620 | symbol _ZN4Aska11RenderState5ApplyEPNS_14RenderDeviceGLE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState5ApplyEPNS_14RenderDeviceGLE(undefined8 *param_1,long param_2)

{
  long lVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  uint uVar7;
  undefined1 *puVar8;
  undefined1 *puVar9;
  
  lVar1 = *(long *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  if (param_2 != 0) {
    lVar1 = param_2;
  }
  if (((undefined1 *)*param_1 != (undefined1 *)0x0) && (*(int *)((long)param_1 + 0x14) != 0)) {
    uVar7 = 0;
    puVar9 = (undefined1 *)*param_1;
    do {
      puVar8 = puVar9 + 1;
      switch(*puVar9) {
      case 200:
        puVar8 = puVar9 + 2;
        Aska::RenderDeviceGL::EnableAlphaBlend(bool)(lVar1,puVar9[1] != '\0');
        break;
      case 0xc9:
        puVar8 = puVar9 + 3;
        Aska::RenderDeviceGL::SetAlphaBlendFunction(Aska::AlphaBlend::Operation, Aska::SeparateAlphaBlendMode::E)(lVar1,puVar9[1],puVar9[2]);
        break;
      case 0xcb:
      case 0xce:
      case 0xe0:
        puVar8 = puVar9 + 2;
        break;
      case 0xcc:
        puVar8 = puVar9 + 3;
        break;
      case 0xcf:
        puVar8 = puVar9 + 3;
        Aska::RenderDeviceGL::SetTextureSamplingFilter(unsigned int, Aska::TexSamp::Filter)(lVar1,puVar9[1],puVar9[2]);
        break;
      case 0xd0:
        puVar8 = puVar9 + 3;
        Aska::RenderDeviceGL::SetTextureSamplingMipmapFilter(unsigned int, Aska::TexSamp::MipFilter)(lVar1,puVar9[1],puVar9[2]);
        break;
      case 0xd1:
        puVar8 = puVar9 + 3;
        Aska::RenderDeviceGL::SetTextureSamplingWrapMode(unsigned int, Aska::TexWrap::Mode, Aska::TexWrap::Mode, Aska::TexWrap::Mode)(lVar1,puVar9[1],puVar9[2],puVar9[2],10);
        break;
      case 0xd2:
        uVar4 = puVar9[1];
        uVar2 = puVar9[2];
        uVar3 = 10;
        goto code_r0x0228a45c;
      case 0xd3:
        uVar4 = puVar9[1];
        uVar3 = puVar9[2];
        uVar2 = 10;
code_r0x0228a45c:
        puVar8 = puVar9 + 3;
        Aska::RenderDeviceGL::SetTextureSamplingWrapMode(unsigned int, Aska::TexWrap::Mode, Aska::TexWrap::Mode, Aska::TexWrap::Mode)(lVar1,uVar4,uVar2,uVar3,10);
        break;
      case 0xd9:
        puVar8 = puVar9 + 3;
        Aska::RenderDeviceGL::SetTextureSamplingMaxAnisotropic(unsigned int, unsigned int)(lVar1,puVar9[1],puVar9[2]);
        break;
      case 0xdb:
        puVar8 = puVar9 + 2;
        Aska::RenderDeviceGL::EnableZTest(bool)(lVar1,puVar9[1] != '\0');
        break;
      case 0xdc:
        puVar8 = puVar9 + 2;
        Aska::RenderDeviceGL::EnableZWrite(bool)(lVar1,puVar9[1] != '\0');
        break;
      case 0xdd:
        puVar8 = puVar9 + 2;
        Aska::RenderDeviceGL::SetZTestFunction(Aska::ZTest::Func)(lVar1,puVar9[1]);
        break;
      case 0xde:
        puVar8 = puVar9 + 9;
        Aska::RenderDeviceGL::SetDepthBias(float, float)(*(undefined4 *)(puVar9 + 1),*(undefined4 *)(puVar9 + 5),lVar1);
        break;
      case 0xdf:
        puVar8 = puVar9 + 2;
        Aska::RenderDeviceGL::SetCullMode(Aska::Cull::Mode)(lVar1,puVar9[1]);
        break;
      case 0xe2:
        puVar8 = puVar9 + 2;
        Aska::RenderDeviceGL::EnableStencil(Aska::StencilMode::Mode)(lVar1,puVar9[1]);
        break;
      case 0xe3:
        uVar2 = puVar9[1];
        uVar3 = puVar9[2];
        uVar4 = puVar9[3];
        uVar5 = puVar9[4];
        uVar6 = puVar9[5];
        if (puVar9[6] == '\0') goto code_r0x0228a57c;
code_r0x0228a550:
        puVar8 = puVar9 + 7;
        Aska::RenderDeviceGL::SetStencilOpCCW(Aska::StencilTest::Func, Aska::StencilOp::Operation, Aska::StencilOp::Operation, Aska::StencilOp::Operation, int)(lVar1);
        break;
      case 0xe4:
        uVar2 = puVar9[1];
        uVar3 = puVar9[2];
        uVar4 = puVar9[3];
        uVar5 = puVar9[4];
        uVar6 = puVar9[5];
        if (puVar9[6] == '\0') goto code_r0x0228a550;
code_r0x0228a57c:
        puVar8 = puVar9 + 7;
        Aska::RenderDeviceGL::SetStencilOp(Aska::StencilTest::Func, Aska::StencilOp::Operation, Aska::StencilOp::Operation, Aska::StencilOp::Operation, int)(lVar1,uVar2,uVar3,uVar4,uVar5,uVar6);
      }
      uVar7 = uVar7 + 1;
      puVar9 = puVar8;
    } while (uVar7 < *(uint *)((long)param_1 + 0x14));
  }
  return;
}

// ==== Aska::RenderState::Static::SetFillMode(Aska::RenderDeviceGL*, Aska::Fill::Mode)
// vaddr 0x218a5ac | ghidra 0x228a5ac | size 4 | symbol _ZN4Aska11RenderState6Static11SetFillModeEPNS_14RenderDeviceGLENS_4Fill4ModeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static11SetFillModeEPNS_14RenderDeviceGLENS_4Fill4ModeE(void)

{
  return;
}

// ==== Aska::RenderState::Static::SetCullMode(Aska::RenderDeviceGL*, Aska::Cull::Mode)
// vaddr 0x218a5b0 | ghidra 0x228a5b0 | size 4 | symbol _ZN4Aska11RenderState6Static11SetCullModeEPNS_14RenderDeviceGLENS_4Cull4ModeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static11SetCullModeEPNS_14RenderDeviceGLENS_4Cull4ModeE(void)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL11SetCullModeENS_4Cull4ModeE_02ca5ae0)();
  return;
}

// ==== Aska::RenderState::Static::EnableZTest(Aska::RenderDeviceGL*, bool)
// vaddr 0x218a5b4 | ghidra 0x228a5b4 | size 8 | symbol _ZN4Aska11RenderState6Static11EnableZTestEPNS_14RenderDeviceGLEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static11EnableZTestEPNS_14RenderDeviceGLEb
               (undefined8 param_1,uint param_2)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL11EnableZTestEb_02ca4b40)(param_1,param_2 & 1);
  return;
}

// ==== Aska::RenderState::Static::EnableZWrite(Aska::RenderDeviceGL*, bool)
// vaddr 0x218a5bc | ghidra 0x228a5bc | size 8 | symbol _ZN4Aska11RenderState6Static12EnableZWriteEPNS_14RenderDeviceGLEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static12EnableZWriteEPNS_14RenderDeviceGLEb
               (undefined8 param_1,uint param_2)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL12EnableZWriteEb_02c9a160)(param_1,param_2 & 1);
  return;
}

// ==== Aska::RenderState::Static::SetZTestFunction(Aska::RenderDeviceGL*, int)
// vaddr 0x218a5c4 | ghidra 0x228a5c4 | size 4 | symbol _ZN4Aska11RenderState6Static16SetZTestFunctionEPNS_14RenderDeviceGLEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static16SetZTestFunctionEPNS_14RenderDeviceGLEi(void)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL16SetZTestFunctionENS_5ZTest4FuncE_02c9a710)();
  return;
}

// ==== Aska::RenderState::Static::SetDepthBias(Aska::RenderDeviceGL*, float, float)
// vaddr 0x218a5c8 | ghidra 0x228a5c8 | size 4 | symbol _ZN4Aska11RenderState6Static12SetDepthBiasEPNS_14RenderDeviceGLEff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static12SetDepthBiasEPNS_14RenderDeviceGLEff(void)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL12SetDepthBiasEff_02caab20)();
  return;
}

// ==== Aska::RenderState::Static::EnableAlphaBlend(Aska::RenderDeviceGL*, bool)
// vaddr 0x218a5cc | ghidra 0x228a5cc | size 8 | symbol _ZN4Aska11RenderState6Static16EnableAlphaBlendEPNS_14RenderDeviceGLEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static16EnableAlphaBlendEPNS_14RenderDeviceGLEb
               (undefined8 param_1,uint param_2)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL16EnableAlphaBlendEb_02ca9030)(param_1,param_2 & 1);
  return;
}

// ==== Aska::RenderState::Static::SetAlphaBlendFunction(Aska::RenderDeviceGL*, Aska::AlphaBlend::Operation, Aska::SeparateAlphaBlendMode::E)
// vaddr 0x218a5d4 | ghidra 0x228a5d4 | size 4 | symbol _ZN4Aska11RenderState6Static21SetAlphaBlendFunctionEPNS_14RenderDeviceGLENS_10AlphaBlend9OperationENS_22SeparateAlphaBlendMode1EE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static21SetAlphaBlendFunctionEPNS_14RenderDeviceGLENS_10AlphaBlend9OperationENS_22SeparateAlphaBlendMode1EE
               (void)

{
  (*(code *)
    PTR__ZN4Aska14RenderDeviceGL21SetAlphaBlendFunctionENS_10AlphaBlend9OperationENS_22SeparateAlphaBlendMode1EE_02c973e8
  )();
  return;
}

// ==== Aska::RenderState::Static::EnableAlphaTest(Aska::RenderDeviceGL*, bool)
// vaddr 0x218a5d8 | ghidra 0x228a5d8 | size 4 | symbol _ZN4Aska11RenderState6Static15EnableAlphaTestEPNS_14RenderDeviceGLEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static15EnableAlphaTestEPNS_14RenderDeviceGLEb(void)

{
  return;
}

// ==== Aska::RenderState::Static::SetAlphaTestFunction(Aska::RenderDeviceGL*, Aska::AlphaTest::Func, int)
// vaddr 0x218a5dc | ghidra 0x228a5dc | size 4 | symbol _ZN4Aska11RenderState6Static20SetAlphaTestFunctionEPNS_14RenderDeviceGLENS_9AlphaTest4FuncEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static20SetAlphaTestFunctionEPNS_14RenderDeviceGLENS_9AlphaTest4FuncEi
               (void)

{
  return;
}

// ==== Aska::RenderState::Static::SetAlphaToCoverage(Aska::RenderDeviceGL*, Aska::AlphaToCoverage::AtoC)
// vaddr 0x218a5e0 | ghidra 0x228a5e0 | size 4 | symbol _ZN4Aska11RenderState6Static18SetAlphaToCoverageEPNS_14RenderDeviceGLENS_15AlphaToCoverage4AtoCE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static18SetAlphaToCoverageEPNS_14RenderDeviceGLENS_15AlphaToCoverage4AtoCE
               (void)

{
  return;
}

// ==== Aska::RenderState::Static::EnableStencil(Aska::RenderDeviceGL*, Aska::StencilMode::Mode)
// vaddr 0x218a5e4 | ghidra 0x228a5e4 | size 4 | symbol _ZN4Aska11RenderState6Static13EnableStencilEPNS_14RenderDeviceGLENS_11StencilMode4ModeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static13EnableStencilEPNS_14RenderDeviceGLENS_11StencilMode4ModeE(void)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL13EnableStencilENS_11StencilMode4ModeE_02ca5180)();
  return;
}

// ==== Aska::RenderState::Static::SetStencilOp(Aska::RenderDeviceGL*, Aska::StencilTest::Func, Aska::StencilOp::Operation, Aska::StencilOp::Operation, Aska::StencilOp::Operation, int)
// vaddr 0x218a5e8 | ghidra 0x228a5e8 | size 4 | symbol _ZN4Aska11RenderState6Static12SetStencilOpEPNS_14RenderDeviceGLENS_11StencilTest4FuncENS_9StencilOp9OperationES7_S7_i | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static12SetStencilOpEPNS_14RenderDeviceGLENS_11StencilTest4FuncENS_9StencilOp9OperationES7_S7_i
               (void)

{
  (*(code *)
    PTR__ZN4Aska14RenderDeviceGL12SetStencilOpENS_11StencilTest4FuncENS_9StencilOp9OperationES4_S4_i_02cb0c30
  )();
  return;
}

// ==== Aska::RenderState::Static::SetStencilOpCCW(Aska::RenderDeviceGL*, Aska::StencilTest::Func, Aska::StencilOp::Operation, Aska::StencilOp::Operation, Aska::StencilOp::Operation, int)
// vaddr 0x218a5ec | ghidra 0x228a5ec | size 4 | symbol _ZN4Aska11RenderState6Static15SetStencilOpCCWEPNS_14RenderDeviceGLENS_11StencilTest4FuncENS_9StencilOp9OperationES7_S7_i | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static15SetStencilOpCCWEPNS_14RenderDeviceGLENS_11StencilTest4FuncENS_9StencilOp9OperationES7_S7_i
               (void)

{
  (*(code *)
    PTR__ZN4Aska14RenderDeviceGL15SetStencilOpCCWENS_11StencilTest4FuncENS_9StencilOp9OperationES4_S4_i_02cad658
  )();
  return;
}

// ==== Aska::RenderState::Static::SetTextureSamplingFilter(Aska::RenderDeviceGL*, int, Aska::TexSamp::Filter)
// vaddr 0x218a5f0 | ghidra 0x228a5f0 | size 4 | symbol _ZN4Aska11RenderState6Static24SetTextureSamplingFilterEPNS_14RenderDeviceGLEiNS_7TexSamp6FilterE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static24SetTextureSamplingFilterEPNS_14RenderDeviceGLEiNS_7TexSamp6FilterE
               (void)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL24SetTextureSamplingFilterEjNS_7TexSamp6FilterE_02c9aa08)();
  return;
}

// ==== Aska::RenderState::Static::SetTextureSamplingMipmapFilter(Aska::RenderDeviceGL*, int, Aska::TexSamp::MipFilter)
// vaddr 0x218a5f4 | ghidra 0x228a5f4 | size 4 | symbol _ZN4Aska11RenderState6Static30SetTextureSamplingMipmapFilterEPNS_14RenderDeviceGLEiNS_7TexSamp9MipFilterE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static30SetTextureSamplingMipmapFilterEPNS_14RenderDeviceGLEiNS_7TexSamp9MipFilterE
               (void)

{
  (*(code *)
    PTR__ZN4Aska14RenderDeviceGL30SetTextureSamplingMipmapFilterEjNS_7TexSamp9MipFilterE_02ca4af8)()
  ;
  return;
}

// ==== Aska::RenderState::Static::SetTextureSamplingWrapMode(Aska::RenderDeviceGL*, int, Aska::TexWrap::Mode, Aska::TexWrap::Mode, Aska::TexWrap::Mode)
// vaddr 0x218a5f8 | ghidra 0x228a5f8 | size 4 | symbol _ZN4Aska11RenderState6Static26SetTextureSamplingWrapModeEPNS_14RenderDeviceGLEiNS_7TexWrap4ModeES5_S5_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static26SetTextureSamplingWrapModeEPNS_14RenderDeviceGLEiNS_7TexWrap4ModeES5_S5_
               (void)

{
  (*(code *)
    PTR__ZN4Aska14RenderDeviceGL26SetTextureSamplingWrapModeEjNS_7TexWrap4ModeES2_S2__02c9b550)();
  return;
}

// ==== Aska::RenderState::Static::SetTextureSamplingMaxAnisotropic(Aska::RenderDeviceGL*, int, unsigned int)
// vaddr 0x218a5fc | ghidra 0x228a5fc | size 4 | symbol _ZN4Aska11RenderState6Static32SetTextureSamplingMaxAnisotropicEPNS_14RenderDeviceGLEij | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static32SetTextureSamplingMaxAnisotropicEPNS_14RenderDeviceGLEij(void)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL32SetTextureSamplingMaxAnisotropicEjj_02c9f488)();
  return;
}

// ==== Aska::RenderState::ReadyDefaultRenderState(Aska::RenderDeviceGL*)
// vaddr 0x218a600 | ghidra 0x228a600 | size 132 | symbol _ZN4Aska11RenderState23ReadyDefaultRenderStateEPNS_14RenderDeviceGLE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState23ReadyDefaultRenderStateEPNS_14RenderDeviceGLE(undefined8 param_1)

{
  Aska::RenderDeviceGL::EnableAlphaBlend(bool)(param_1,0);
  Aska::RenderDeviceGL::EnableZTest(bool)(param_1,1);
  Aska::RenderDeviceGL::SetZTestFunction(Aska::ZTest::Func)(param_1,3);
  Aska::RenderDeviceGL::EnableZWrite(bool)(param_1,1);
  Aska::RenderDeviceGL::SetDepthBias(float, float)(0,0,param_1);
  Aska::RenderDeviceGL::SetCullMode(Aska::Cull::Mode)(param_1,1);
  Aska::RenderDeviceGL::EnableStencil(Aska::StencilMode::Mode)(param_1,0);
  Aska::RenderDeviceGL::ResetTextureFiltersAll()(param_1);
  Aska::RenderDeviceGL::BindVertexBuffer(unsigned long, void*)(param_1,0,0);
  (*(code *)PTR__ZN4Aska14RenderDeviceGL15BindIndexBufferEm_02caa198)(param_1,0);
  return;
}

// ==== Aska::RenderState::RestoreDefaultRenderState(Aska::RenderDeviceGL*)
// vaddr 0x218a684 | ghidra 0x228a684 | size 4 | symbol _ZN4Aska11RenderState25RestoreDefaultRenderStateEPNS_14RenderDeviceGLE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState25RestoreDefaultRenderStateEPNS_14RenderDeviceGLE(void)

{
  return;
}

// ==== Aska::RenderState::CheckDefaultRenderState(Aska::RenderDeviceGL*, char const*)
// vaddr 0x218a688 | ghidra 0x228a688 | size 4 | symbol _ZN4Aska11RenderState23CheckDefaultRenderStateEPNS_14RenderDeviceGLEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState23CheckDefaultRenderStateEPNS_14RenderDeviceGLEPKc(void)

{
  return;
}

// ==== Aska::RenderState::Static::SetTextureSamplingWrapMode(Aska::RenderDeviceGL*, int, Aska::TexWrap::Mode)
// vaddr 0x218a68c | ghidra 0x228a68c | size 12 | symbol _ZN4Aska11RenderState6Static26SetTextureSamplingWrapModeEPNS_14RenderDeviceGLEiNS_7TexWrap4ModeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static26SetTextureSamplingWrapModeEPNS_14RenderDeviceGLEiNS_7TexWrap4ModeE
               (void)

{
  (*(code *)
    PTR__ZN4Aska14RenderDeviceGL26SetTextureSamplingWrapModeEjNS_7TexWrap4ModeES2_S2__02c9b550)();
  return;
}

// ==== Aska::RenderState::Static::SetTextureSamplingAnisotropicBias(Aska::RenderDeviceGL*, int, int)
// vaddr 0x218a698 | ghidra 0x228a698 | size 4 | symbol _ZN4Aska11RenderState6Static33SetTextureSamplingAnisotropicBiasEPNS_14RenderDeviceGLEii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static33SetTextureSamplingAnisotropicBiasEPNS_14RenderDeviceGLEii(void)

{
  return;
}

// ==== Aska::RenderState::Static::EnableColorWrite(Aska::RenderDeviceGL*, bool)
// vaddr 0x218a69c | ghidra 0x228a69c | size 20 | symbol _ZN4Aska11RenderState6Static16EnableColorWriteEPNS_14RenderDeviceGLEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static16EnableColorWriteEPNS_14RenderDeviceGLEb
               (undefined8 param_1,uint param_2)

{
  param_2 = param_2 & 1;
  (*(code *)PTR__ZN4Aska14RenderDeviceGL16EnableColorWriteEbbbb_02c97268)
            (param_1,param_2,param_2,param_2,param_2);
  return;
}

// ==== Aska::RenderState::Static::EnableColorWrite(Aska::RenderDeviceGL*, bool, bool, bool, bool)
// vaddr 0x218a6b0 | ghidra 0x228a6b0 | size 20 | symbol _ZN4Aska11RenderState6Static16EnableColorWriteEPNS_14RenderDeviceGLEbbbb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static16EnableColorWriteEPNS_14RenderDeviceGLEbbbb
               (undefined8 param_1,uint param_2,uint param_3,uint param_4,uint param_5)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL16EnableColorWriteEbbbb_02c97268)
            (param_1,param_2 & 1,param_3 & 1,param_4 & 1,param_5 & 1);
  return;
}

// ==== Aska::RenderState::Static::EnableDither(Aska::RenderDeviceGL*, bool)
// vaddr 0x218a6c4 | ghidra 0x228a6c4 | size 8 | symbol _ZN4Aska11RenderState6Static12EnableDitherEPNS_14RenderDeviceGLEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11RenderState6Static12EnableDitherEPNS_14RenderDeviceGLEb
               (undefined8 param_1,uint param_2)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL12EnableDitherEb_02caf048)(param_1,param_2 & 1);
  return;
}

// ==== Aska::RenderStateManager::RenderStateManager()
// vaddr 0x218a7a8 | ghidra 0x228a7a8 | size 16 | symbol _ZN4Aska18RenderStateManagerC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18RenderStateManagerC1Ev(undefined8 *param_1)

{
  *param_1 = 0;
  *(undefined8 *)((long)param_1 + 0x16) = 0;
  param_1[2] = 0;
  return;
}

// ==== Aska::RenderStateManager::~RenderStateManager()
// vaddr 0x218a7b8 | ghidra 0x228a7b8 | size 108 | symbol _ZN4Aska18RenderStateManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18RenderStateManagerD2Ev(long *param_1)

{
  long lVar1;
  long lVar2;
  
  lVar2 = param_1[2];
  if (lVar2 != 0) {
    lVar1 = *(long *)(lVar2 + -8);
    if (lVar1 != 0) {
      lVar1 = lVar1 * 0x18;
      do {
        Aska::RenderState::~RenderState()(lVar2 + lVar1 + -0x18);
        lVar1 = lVar1 + -0x18;
      } while (lVar1 != 0);
    }
    operator delete[](void*)((long *)(lVar2 + -8));
    param_1[2] = 0;
  }
  if (*param_1 != 0) {
    operator delete[](void*)();
    *param_1 = 0;
  }
  return;
}

// ==== Aska::RenderStateManager::Init(int)
// vaddr 0x218a824 | ghidra 0x228a824 | size 296 | symbol _ZN4Aska18RenderStateManager4InitEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18RenderStateManager4InitEi(long *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined1 auVar3 [16];
  ulong *puVar4;
  undefined8 *puVar5;
  ulong uVar6;
  ulong *puVar7;
  ulong uVar8;
  long lVar9;
  
  uVar8 = (ulong)param_2;
  auVar3._8_8_ = 0;
  auVar3._0_8_ = uVar8;
  uVar6 = (uVar8 + (long)param_2 * 2) * 8;
  lVar9 = uVar6 + 8;
  if (SUB168(auVar3 * ZEXT816(0x18),8) != 0 || 0xfffffffffffffff7 < uVar6) {
    lVar9 = -1;
  }
  puVar4 = (ulong *)operator new[](unsigned long, std::nothrow_t const&)(lVar9,PTR__ZSt7nothrow_02cb9a80);
  puVar7 = puVar4;
  if (puVar4 != (ulong *)0x0) {
    puVar7 = puVar4 + 1;
    *puVar4 = uVar8;
    if (param_2 != 0) {
      lVar9 = uVar8 * 0x18;
      puVar4 = puVar7;
      do {
        Aska::RenderState::RenderState()(puVar4);
        lVar9 = lVar9 + -0x18;
        puVar4 = puVar4 + 3;
      } while (lVar9 != 0);
    }
  }
  param_1[2] = (long)puVar7;
  if (*param_1 != 0) {
    operator delete[](void*)();
    *param_1 = 0;
  }
  iVar2 = param_2 + 0x7e;
  if (-1 < param_2 + 0x3f) {
    iVar2 = param_2 + 0x3f;
  }
  uVar1 = iVar2 >> 6;
  *(short *)((long)param_1 + 10) = (short)param_2;
  *(short *)(param_1 + 1) = (short)uVar1;
  puVar5 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)((uVar1 & 0xffff) << 3,PTR__ZSt7nothrow_02cb9a80);
  *param_1 = (long)puVar5;
  if (((uVar1 & 0xffff) != 0) && (*puVar5 = 0, 1 < *(ushort *)(param_1 + 1))) {
    lVar9 = 1;
    do {
      *(undefined8 *)(*param_1 + lVar9 * 8) = 0;
      lVar9 = lVar9 + 1;
    } while (lVar9 < (long)(ulong)*(ushort *)(param_1 + 1));
  }
  *(short *)(param_1 + 3) = (short)param_2;
  *(undefined4 *)((long)param_1 + 0x1a) = 0;
  (*(code *)PTR__ZN4Aska16BackBufferScaler4InitEv_02ca2a60)
            (*(undefined8 *)(*(long *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0 + 0xec0b0));
  return;
}

// ==== Aska::RenderStateManager::Get(int)
// vaddr 0x218a94c | ghidra 0x228a94c | size 244 | symbol _ZN4Aska18RenderStateManager3GetEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska18RenderStateManager3GetEi(long *param_1)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  ulong uVar7;
  long lVar8;
  ulong uVar6;
  
  uVar1 = *(ushort *)(param_1 + 3);
  if (*(ushort *)((long)param_1 + 0x1c) != uVar1) {
    uVar2 = *(ushort *)((long)param_1 + 0x1a);
    uVar6 = (ulong)uVar2;
    uVar5 = (uint)uVar2;
    uVar7 = 1L << (uVar6 & 0x3f) & *(ulong *)(*param_1 + (ulong)(uVar2 >> 6) * 8);
    while (uVar7 != 0) {
      uVar5 = (int)uVar6 + 1U & 0xffff;
      uVar4 = 0;
      if (uVar1 != 0) {
        uVar4 = uVar5 / uVar1;
      }
      uVar5 = uVar5 - uVar4 * uVar1;
      uVar6 = (ulong)uVar5;
      *(short *)((long)param_1 + 0x1a) = (short)uVar5;
      uVar7 = *(ulong *)(*param_1 + (ulong)(uVar5 >> 6) * 8) & 1L << (uVar5 & 0x3f);
    }
    lVar8 = param_1[2] + (ulong)(uVar5 & 0xffff) * 0x18;
    uVar6 = Aska::RenderState::Alloc(int)(lVar8);
    if ((uVar6 & 1) != 0) {
      uVar6 = (ulong)(*(ushort *)((long)param_1 + 0x1a) >> 3) & 0x1ff8;
      *(ulong *)(*param_1 + uVar6) =
           1L << (*(ushort *)((long)param_1 + 0x1a) & 0x3f) | *(ulong *)(*param_1 + uVar6);
      uVar2 = *(ushort *)(param_1 + 3);
      uVar1 = *(short *)((long)param_1 + 0x1a) + 1;
      *(short *)((long)param_1 + 0x1c) = *(short *)((long)param_1 + 0x1c) + 1;
      uVar3 = 0;
      if (uVar2 != 0) {
        uVar3 = uVar1 / uVar2;
      }
      *(ushort *)((long)param_1 + 0x1a) = uVar1 - uVar3 * uVar2;
      return lVar8;
    }
  }
  return 0;
}

// ==== Aska::RenderStateManager::Return(Aska::RenderState*)
// vaddr 0x218aa40 | ghidra 0x228aa40 | size 92 | symbol _ZN4Aska18RenderStateManager6ReturnEPNS_11RenderStateE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18RenderStateManager6ReturnEPNS_11RenderStateE(long *param_1,long param_2)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  
  uVar2 = (int)((ulong)(param_2 - param_1[2]) >> 3) * -0x55555555;
  uVar1 = uVar2 + 0x3f;
  if (-1 < (int)uVar2) {
    uVar1 = uVar2;
  }
  uVar3 = -(ulong)((uint)((int)uVar1 >> 6) >> 0x1f) & 0xfffffff800000000 |
          (ulong)(uint)((int)uVar1 >> 6) << 3;
  *(ulong *)(*param_1 + uVar3) =
       *(ulong *)(*param_1 + uVar3) & (1L << ((ulong)uVar2 & 0x3f) ^ 0xffffffffffffffffU);
  *(short *)((long)param_1 + 0x1c) = *(short *)((long)param_1 + 0x1c) + -1;
  return;
}

// ==== Aska::RenderStateManager::GetAvailableBufferCount() const
// vaddr 0x218aa9c | ghidra 0x228aa9c | size 8 | symbol _ZNK4Aska18RenderStateManager23GetAvailableBufferCountEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska18RenderStateManager23GetAvailableBufferCountEv(void)

{
  return 0;
}

// ==== Aska::RenderStateManager::GetAllocatedBufferCount() const
// vaddr 0x218aaa4 | ghidra 0x228aaa4 | size 8 | symbol _ZNK4Aska18RenderStateManager23GetAllocatedBufferCountEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska18RenderStateManager23GetAllocatedBufferCountEv(void)

{
  return 0;
}

// ==== Aska::RenderContextBase::AllocBatch(int)
// vaddr 0x21b8c68 | ghidra 0x22b8c68 | size 76 | symbol _ZN4Aska17RenderContextBase10AllocBatchEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17RenderContextBase10AllocBatchEi(undefined8 *param_1,undefined2 param_2)

{
  undefined8 uVar1;
  
  uVar1 = Aska::RenderContextServer::GetRenderBatch(int)(*(undefined8 *)
                           (*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x1000));
  *param_1 = uVar1;
  *(undefined2 *)(param_1 + 1) = param_2;
  *(byte *)((long)param_1 + 10) = *(byte *)((long)param_1 + 10) & 0x9f;
  return;
}

// ==== Aska::RenderContextBase::SetShaderConstant_Vertex(unsigned long, Aska::ShaderNodeHandler*)
// vaddr 0x21b8cb4 | ghidra 0x22b8cb4 | size 496 | symbol _ZN4Aska17RenderContextBase24SetShaderConstant_VertexEmPNS_17ShaderNodeHandlerE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x022b8cf4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022b8d2c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022b8d54: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022b8d90: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022b8e94: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022b8e50: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022b8e18: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x022b8e54) */
/* WARNING: Removing unreachable block (ram,0x022b8e5c) */
/* WARNING: Removing unreachable block (ram,0x022b8e98) */
/* WARNING: Removing unreachable block (ram,0x022b8ea0) */
/* WARNING: Removing unreachable block (ram,0x022b8d94) */
/* WARNING: Removing unreachable block (ram,0x022b8da8) */
/* WARNING: Removing unreachable block (ram,0x022b8dbc) */
/* WARNING: Removing unreachable block (ram,0x022b8dc4) */
/* WARNING: Removing unreachable block (ram,0x022b8d58) */
/* WARNING: Removing unreachable block (ram,0x022b8d60) */
/* WARNING: Removing unreachable block (ram,0x022b8de0) */
/* WARNING: Removing unreachable block (ram,0x022b8d68) */
/* WARNING: Removing unreachable block (ram,0x022b8d6c) */
/* WARNING: Removing unreachable block (ram,0x022b8d80) */
/* WARNING: Removing unreachable block (ram,0x022b8d30) */
/* WARNING: Removing unreachable block (ram,0x022b8e1c) */

void _ZN4Aska17RenderContextBase24SetShaderConstant_VertexEmPNS_17ShaderNodeHandlerE(long param_1)

{
  undefined8 uVar1;
  undefined *puVar2;
  undefined8 uVar3;
  uint uVar4;
  ulong uVar5;
  undefined8 uVar6;
  
  uVar5 = *(ulong *)(param_1 + 0x140);
  uVar6 = *(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  uVar4 = (uint)uVar5;
  if ((uVar4 >> 0x10 & 1) != 0) {
    Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar6,0xc,param_1 + 0x210,2);
    uVar5 = *(ulong *)(param_1 + 0x140);
    uVar4 = (uint)uVar5;
  }
  if ((uVar5 & 1) == 0) {
    if ((uVar4 >> 1 & 1) != 0) {
      Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar6,1,param_1 + 0xe0,3);
      uVar4 = (uint)*(undefined8 *)(param_1 + 0x140);
    }
    if ((uVar4 >> 9 & 1) == 0) {
      if ((uVar4 >> 2 & 1) == 0) {
        Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar6,0xe,param_1 + 0x110,1);
        uVar4 = (uint)*(undefined8 *)(param_1 + 0x140);
        if ((uVar4 >> 6 & 1) != 0) {
          Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)(uVar6,6,PTR__ZN4Aska20GlobalShaderConstant16m_vScreenUVConstE_02cb9a90,1);
          uVar4 = (uint)*(undefined8 *)(param_1 + 0x140);
        }
        if ((uVar4 >> 0xf & 1) == 0) {
          if ((uVar4 >> 0xe & 1) == 0) {
            uVar1 = 0xb;
            uVar3 = 3;
            puVar2 = *(undefined **)(param_1 + 0x150);
          }
          else {
            uVar1 = 0xf;
            uVar3 = 4;
            puVar2 = (undefined *)(param_1 + 0x1c0);
          }
        }
        else {
          uVar1 = 0xd;
          uVar3 = 1;
          puVar2 = PTR__ZN4Aska20GlobalShaderConstant18m_vActualFrameSizeE_02cc4d80;
        }
      }
      else {
        uVar1 = 9;
        uVar3 = 3;
        puVar2 = (undefined *)(param_1 + 0x170);
      }
    }
    else {
      puVar2 = (undefined *)(param_1 + 0xa0);
      uVar1 = 10;
      uVar3 = 4;
    }
  }
  else {
    puVar2 = (undefined *)(param_1 + 0x60);
    uVar3 = 4;
    uVar1 = 0;
  }
  (*(code *)PTR__ZN4Aska14RenderDeviceGL23SetVertexShaderConstantEiPKvi_02c92a28)
            (uVar6,uVar1,puVar2,uVar3);
  return;
}

// ==== Aska::RenderContextBase::SetShaderConstant_Pixel(unsigned long, Aska::ShaderNodeHandler*)
// vaddr 0x21b8ea4 | ghidra 0x22b8ea4 | size 484 | symbol _ZN4Aska17RenderContextBase23SetShaderConstant_PixelEmPNS_17ShaderNodeHandlerE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x022b8ed4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022b8efc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022b8f34: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022b8fa8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022b904c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022b9010: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x022b9050) */
/* WARNING: Removing unreachable block (ram,0x022b8fac) */
/* WARNING: Removing unreachable block (ram,0x022b8f38) */
/* WARNING: Removing unreachable block (ram,0x022b8fe4) */
/* WARNING: Removing unreachable block (ram,0x022b8f40) */
/* WARNING: Removing unreachable block (ram,0x022b9000) */
/* WARNING: Removing unreachable block (ram,0x022b8f44) */
/* WARNING: Removing unreachable block (ram,0x022b8f00) */
/* WARNING: Removing unreachable block (ram,0x022b8ed8) */
/* WARNING: Removing unreachable block (ram,0x022b9014) */
/* WARNING: Removing unreachable block (ram,0x022b8f48) */
/* WARNING: Removing unreachable block (ram,0x022b901c) */
/* WARNING: Removing unreachable block (ram,0x022b8f4c) */
/* WARNING: Removing unreachable block (ram,0x022b9058) */
/* WARNING: Removing unreachable block (ram,0x022b8f50) */
/* WARNING: Removing unreachable block (ram,0x022b8f58) */
/* WARNING: Removing unreachable block (ram,0x022b8f60) */
/* WARNING: Removing unreachable block (ram,0x022b8f64) */
/* WARNING: Removing unreachable block (ram,0x022b8f78) */
/* WARNING: Removing unreachable block (ram,0x022b8fb8) */
/* WARNING: Removing unreachable block (ram,0x022b9074) */
/* WARNING: Removing unreachable block (ram,0x022b8fc0) */
/* WARNING: Removing unreachable block (ram,0x022b8f8c) */
/* WARNING: Removing unreachable block (ram,0x022b8f98) */
/* WARNING: Removing unreachable block (ram,0x022b9038) */

void _ZN4Aska17RenderContextBase23SetShaderConstant_PixelEmPNS_17ShaderNodeHandlerE(long param_1)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL22SetPixelShaderConstantEiPKvi_02c965b0)
            (*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,0x14,param_1 + 0x120,1);
  return;
}

// ==== Aska::RenderContextBase::SetShaderConstant_Vertex_ForInstancing(unsigned int)
// vaddr 0x21b9088 | ghidra 0x22b9088 | size 116 | symbol _ZN4Aska17RenderContextBase38SetShaderConstant_Vertex_ForInstancingEj | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x022b90c8: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x022b90cc) */
/* WARNING: Removing unreachable block (ram,0x022b90e0) */
/* WARNING: Removing unreachable block (ram,0x022b90d4) */

void _ZN4Aska17RenderContextBase38SetShaderConstant_Vertex_ForInstancingEj
               (long param_1,uint param_2)

{
  if (*(long *)(param_1 + 0x30) != 0) {
    param_2 = *(uint *)(*(long *)(param_1 + 0x30) + (ulong)param_2 * 4);
  }
  (*(code *)PTR__ZN4Aska14RenderDeviceGL23SetVertexShaderConstantEiPKvi_02c92a28)
            (*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,0x11,
             *(long *)(param_1 + 0x28) + (ulong)param_2 * 0x40,3);
  return;
}

// ==== Aska::RenderContextBatchBase::Apply(unsigned long, Aska::RenderDeviceGL*, Aska::ShaderNodeHandler*)
// vaddr 0x21b90fc | ghidra 0x22b90fc | size 348 | symbol _ZN4Aska22RenderContextBatchBase5ApplyEmPNS_14RenderDeviceGLEPNS_17ShaderNodeHandlerE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x022b912c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022b9170: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022b91d4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022b9208: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x022b9174) */
/* WARNING: Removing unreachable block (ram,0x022b917c) */
/* WARNING: Removing unreachable block (ram,0x022b9184) */
/* WARNING: Removing unreachable block (ram,0x022b9188) */
/* WARNING: Removing unreachable block (ram,0x022b919c) */
/* WARNING: Removing unreachable block (ram,0x022b91b0) */
/* WARNING: Removing unreachable block (ram,0x022b91b8) */
/* WARNING: Removing unreachable block (ram,0x022b91c0) */
/* WARNING: Removing unreachable block (ram,0x022b91d8) */
/* WARNING: Removing unreachable block (ram,0x022b91ec) */
/* WARNING: Removing unreachable block (ram,0x022b91c4) */
/* WARNING: Removing unreachable block (ram,0x022b9130) */
/* WARNING: Removing unreachable block (ram,0x022b914c) */
/* WARNING: Removing unreachable block (ram,0x022b9154) */
/* WARNING: Removing unreachable block (ram,0x022b9160) */
/* WARNING: Removing unreachable block (ram,0x022b920c) */
/* WARNING: Removing unreachable block (ram,0x022b91f8) */
/* WARNING: Removing unreachable block (ram,0x022b9218) */
/* WARNING: Removing unreachable block (ram,0x022b9234) */
/* WARNING: Removing unreachable block (ram,0x022b9220) */

void _ZN4Aska22RenderContextBatchBase5ApplyEmPNS_14RenderDeviceGLEPNS_17ShaderNodeHandlerE
               (undefined8 param_1)

{
  (*(code *)PTR__ZN4Aska14RenderDeviceGL22SetPixelShaderConstantEiPKvi_02c965b0)
            (*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,0x14,param_1,1);
  return;
}

// ==== Aska::TPoolFast<Aska::RenderState::StatePack, false>::SecurePool(unsigned int, Aska::RenderState::StatePack*)
// vaddr 0x21c0440 | ghidra 0x22c0440 | size 404 | symbol _ZN4Aska9TPoolFastINS_11RenderState9StatePackELb0EE10SecurePoolEjPS2_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9TPoolFastINS_11RenderState9StatePackELb0EE10SecurePoolEjPS2_
          (long param_1,uint param_2,long param_3)

{
  bool bVar1;
  char cVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  long *plVar6;
  
  if (*(char *)(param_1 + 0x41) == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (*(long *)(param_1 + 0x30) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    *(undefined1 *)(param_1 + 0x41) = 0;
  }
  plVar6 = (long *)(param_1 + 0x18);
  if ((*plVar6 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *plVar6 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  if (param_2 == 0) {
    return 1;
  }
  if (param_3 == 0) {
    param_3 = operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 + (ulong)param_2 * 8,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 0x30) = param_3;
    if (param_3 == 0) {
      cVar2 = *(char *)(param_1 + 0x41);
      goto joined_r0x022c0598;
    }
    *(undefined1 *)(param_1 + 0x41) = 1;
  }
  else {
    *(long *)(param_1 + 0x30) = param_3;
  }
  uVar4 = (ulong)param_2 + 0x3f >> 6;
  *(int *)(param_1 + 0x20) = (int)uVar4;
  *(uint *)(param_1 + 0x24) = param_2;
  lVar5 = uVar4 << 3;
  lVar3 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
  *(long *)(param_1 + 0x18) = lVar3;
  *(undefined1 *)(param_1 + 0x28) = 1;
  if (lVar3 != 0) {
    memset(lVar3,0,lVar5);
    *(undefined8 *)(param_1 + 0x38) = 0;
    memset(lVar3,0,lVar5);
    return 1;
  }
  *(undefined1 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  cVar2 = *(char *)(param_1 + 0x41);
joined_r0x022c0598:
  if (cVar2 == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (param_3 == 0) {
      lVar3 = 0;
      *(undefined1 *)(param_1 + 0x41) = 0;
      bVar1 = false;
    }
    else {
      operator delete[](void*)(param_3);
      lVar3 = *(long *)(param_1 + 0x18);
      *(undefined8 *)(param_1 + 0x30) = 0;
      *(undefined1 *)(param_1 + 0x41) = 0;
      bVar1 = lVar3 != 0;
    }
    if ((bVar1) && (*(char *)(param_1 + 0x28) != '\0')) {
      operator delete[](void*)(lVar3);
      *(undefined1 *)(param_1 + 0x28) = 0;
    }
  }
  *plVar6 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  return 0;
}

// ==== Aska::TPoolFast<Aska::RenderState::StatePack, false>::Scoop(int)
// vaddr 0x21c0730 | ghidra 0x22c0730 | size 516 | symbol _ZN4Aska9TPoolFastINS_11RenderState9StatePackELb0EE5ScoopEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska9TPoolFastINS_11RenderState9StatePackELb0EE5ScoopEi(long param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  ulong *puVar9;
  int iVar10;
  ulong uVar11;
  uint uVar12;
  long lVar13;
  int iVar14;
  long lVar15;
  
  uVar4 = *(uint *)(param_1 + 0x24);
  if ((uint)(*(int *)(param_1 + 0x3c) + param_2) <= uVar4) {
    uVar5 = *(uint *)(param_1 + 0x38);
    iVar6 = param_2 + -1;
    iVar14 = (uVar4 + iVar6) - uVar5;
    if ((int)(uVar5 + param_2) <= (int)uVar4) {
      iVar14 = iVar6;
    }
    uVar12 = 0;
    if ((int)(uVar5 + param_2) <= (int)uVar4) {
      uVar12 = uVar5;
    }
    if (iVar14 < (int)uVar4) {
      if (param_2 == 0) {
code_r0x022c08fc:
        uVar5 = 0;
        if (uVar4 != 0) {
          uVar5 = (uVar12 + param_2) / uVar4;
        }
        *(uint *)(param_1 + 0x38) = (uVar12 + param_2) - uVar5 * uVar4;
        *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + param_2;
        return *(long *)(param_1 + 0x30) + (long)(int)uVar12 + (long)(int)uVar12 * 8;
      }
      lVar13 = *(long *)(param_1 + 0x18);
      do {
        uVar5 = uVar12 + 0x3f;
        if (-1 < (int)uVar12) {
          uVar5 = uVar12;
        }
        uVar7 = (int)uVar12 % 0x40;
        puVar9 = (ulong *)(lVar13 + (long)((int)uVar5 >> 6) * 8);
        iVar10 = param_2;
        uVar1 = uVar7;
        while( true ) {
          uVar11 = 0xffffffffffffffff >> ((ulong)(0x40 - iVar10) & 0x3f);
          if (0x3f < iVar10) {
            uVar11 = 0xffffffffffffffff;
          }
          iVar2 = 0;
          if (iVar10 < 0x40) {
            iVar2 = iVar10;
          }
          if ((uVar11 << ((ulong)uVar1 & 0x3f) & *puVar9) != 0) break;
          iVar3 = 0x40 - uVar1;
          if (iVar2 <= (int)(0x40 - uVar1)) {
            iVar3 = iVar2;
          }
          iVar10 = iVar10 - iVar3;
          puVar9 = puVar9 + 1;
          uVar1 = 0;
          if (iVar10 == 0) {
            uVar11 = 0xffffffffffffffff >> ((ulong)(0x40 - param_2) & 0x3f);
            lVar15 = ((long)((ulong)uVar5 << 0x20) >> 0x26) * 8;
            if (0x3f < param_2) {
              uVar11 = 0xffffffffffffffff;
            }
            iVar14 = 0;
            if (param_2 < 0x40) {
              iVar14 = param_2;
            }
            iVar6 = 0x40 - uVar7;
            if (iVar14 <= (int)(0x40 - uVar7)) {
              iVar6 = iVar14;
            }
            *(ulong *)(lVar13 + lVar15) =
                 *(ulong *)(lVar13 + lVar15) | uVar11 << ((ulong)uVar7 & 0x3f);
            for (iVar6 = param_2 - iVar6; iVar6 != 0; iVar6 = iVar6 - iVar14) {
              lVar15 = lVar15 + 8;
              uVar11 = 0xffffffffffffffff >> ((ulong)(0x40 - iVar6) & 0x3f);
              iVar14 = iVar6;
              if (0x3f < iVar6) {
                uVar11 = 0xffffffffffffffff;
                iVar14 = 0x40;
              }
              if (0x3f < iVar14) {
                iVar14 = 0x40;
              }
              *(ulong *)(*(long *)(param_1 + 0x18) + lVar15) =
                   uVar11 | *(ulong *)(*(long *)(param_1 + 0x18) + lVar15);
            }
            goto code_r0x022c08fc;
          }
        }
        iVar10 = 0;
        do {
          uVar5 = uVar12 + iVar6 + iVar10;
          iVar10 = iVar10 + -1;
        } while ((1L << (uVar5 & 0x3f) & *(ulong *)(lVar13 + (ulong)(uVar5 >> 6) * 8)) == 0);
        iVar2 = (param_2 << 1 | 1U) + uVar12;
        iVar3 = param_2 + 1 + uVar12;
        iVar8 = (((uVar4 - 1) - param_2) - uVar12) - iVar10;
        uVar12 = 0;
        if (iVar2 + iVar10 <= (int)uVar4) {
          iVar8 = 0;
          uVar12 = iVar3 + iVar10;
        }
        iVar14 = iVar8 + param_2 + 1 + iVar14 + iVar10;
        if ((int)uVar4 <= iVar14) {
          return 0;
        }
      } while( true );
    }
  }
  return 0;
}

// ==== Aska::TPoolFast<Aska::RenderState::StatePack, false>::~TPoolFast()
// vaddr 0x21c0dc0 | ghidra 0x22c0dc0 | size 124 | symbol _ZN4Aska9TPoolFastINS_11RenderState9StatePackELb0EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9TPoolFastINS_11RenderState9StatePackELb0EED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska9TPoolFastINS_11RenderState9StatePackELb0EEE_02cbdb00 + 0x10);
  if (*(char *)((long)param_1 + 0x41) == '\0') {
    param_1[6] = 0;
  }
  else {
    if (param_1[6] != 0) {
      operator delete[](void*)();
      param_1[6] = 0;
    }
    *(undefined1 *)((long)param_1 + 0x41) = 0;
  }
  if ((param_1[3] != 0) && ((char)param_1[5] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 5) = 0;
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[1] = (long)(PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10);
  return;
}

// ==== Aska::TPoolFast<Aska::RenderState::StatePack, false>::~TPoolFast()
// vaddr 0x21c0e3c | ghidra 0x22c0e3c | size 100 | symbol _ZN4Aska9TPoolFastINS_11RenderState9StatePackELb0EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9TPoolFastINS_11RenderState9StatePackELb0EED0Ev(long *param_1)

{
  long lVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska9TPoolFastINS_11RenderState9StatePackELb0EEE_02cbdb00 + 0x10);
  if (*(char *)((long)param_1 + 0x41) == '\0') {
    param_1[6] = 0;
    lVar1 = param_1[3];
  }
  else {
    if (param_1[6] != 0) {
      operator delete[](void*)();
      param_1[6] = 0;
    }
    *(undefined1 *)((long)param_1 + 0x41) = 0;
    lVar1 = param_1[3];
  }
  if ((lVar1 != 0) && ((char)param_1[5] != '\0')) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}


// FAILED to create function at 029d2120 typeinfo name for Aska::TPoolFast<Aska::RenderState::StatePack, false>
// FAILED to create function at 02c54328 Aska::TPoolFast<Aska::RenderState::StatePack,false>::vtable
// FAILED to create function at 02c54348 Aska::TPoolFast<Aska::RenderState::StatePack,false>::typeinfo
