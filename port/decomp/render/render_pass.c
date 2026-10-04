// port/decomp/render/render_pass.c: Ghidra decompiles for the render subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:46 UTC: tools/decomp.sh '--into' 'render/render_pass' 'Aska::RenderPass::' 'Aska::RenderPassManager::'

// ==== Aska::RenderPass::Create(int)
// vaddr 0x21bb3ac | ghidra 0x22bb3ac | size 536 | symbol _ZN4Aska10RenderPass6CreateEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10RenderPass6CreateEi(long param_1,int param_2)

{
  undefined *puVar1;
  long lVar2;
  undefined1 *puVar3;
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  
  lVar5 = *(long *)(param_1 + 8);
  if (lVar5 == 0) {
    uVar4 = 0;
  }
  else {
    if (param_2 == 0) {
      if (*(char *)(param_1 + 0x26) != '\0') {
        *(undefined1 *)(lVar5 + 0x132) = 0;
        *(undefined2 *)(lVar5 + 0x130) = 0;
        *(undefined8 *)(lVar5 + 0x128) = 0;
        memset(lVar5 + 0x138,0,0x50);
        puVar1 = PTR__ZTVN4Aska18ShaderNodeModifierE_02cc1658;
        *(undefined1 *)(lVar5 + 0x188) = 0;
        *(undefined **)(lVar5 + 0x120) = puVar1 + 0x10;
        *(long *)(*(long *)(param_1 + 8) + 0x20) = lVar5 + 0x120;
        if (1 < *(byte *)(param_1 + 0x26)) {
          lVar5 = 1;
          lVar6 = 0x340;
          do {
            puVar3 = (undefined1 *)(*(long *)(param_1 + 8) + lVar6);
            puVar3[-0x56] = 0;
            *(undefined2 *)(puVar3 + -0x58) = 0;
            *(undefined8 *)(puVar3 + -0x60) = 0;
            memset(puVar3 + -0x50,0,0x50);
            *(undefined **)(puVar3 + -0x68) = puVar1 + 0x10;
            *puVar3 = 0;
            lVar5 = lVar5 + 1;
            *(undefined1 **)(*(long *)(param_1 + 8) + lVar6 + -0x168) = puVar3 + -0x68;
            lVar6 = lVar6 + 0x1b8;
          } while (lVar5 < (long)(ulong)*(byte *)(param_1 + 0x26));
        }
      }
    }
    else if (param_2 == 1) {
      if (*(char *)(param_1 + 0x26) != '\0') {
        Aska::DirectShaderNode::DirectShaderNode()(lVar5 + 0x120);
        *(long *)(*(long *)(param_1 + 8) + 0x20) = lVar5 + 0x120;
        if (1 < *(byte *)(param_1 + 0x26)) {
          lVar5 = 1;
          lVar6 = 0x1d8;
          do {
            lVar2 = *(long *)(param_1 + 8) + lVar6 + 0x100;
            Aska::DirectShaderNode::DirectShaderNode()(lVar2);
            lVar5 = lVar5 + 1;
            *(long *)(*(long *)(param_1 + 8) + lVar6) = lVar2;
            lVar6 = lVar6 + 0x1b8;
          } while (lVar5 < (long)(ulong)*(byte *)(param_1 + 0x26));
        }
      }
    }
    else if ((param_2 == 2) && (*(char *)(param_1 + 0x26) != '\0')) {
      *(undefined1 *)(lVar5 + 0x132) = 0;
      *(undefined2 *)(lVar5 + 0x130) = 0;
      *(undefined8 *)(lVar5 + 0x128) = 0;
      memset(lVar5 + 0x138,0,0x51);
      puVar1 = PTR__ZTVN4Aska24ShaderNodeSystemModifierE_02cb8bb8 + 0x10;
      *(undefined **)(lVar5 + 0x120) = puVar1;
      *(long *)(*(long *)(param_1 + 8) + 0x20) = lVar5 + 0x120;
      if (1 < *(byte *)(param_1 + 0x26)) {
        lVar5 = 1;
        lVar6 = 0x2f0;
        do {
          lVar2 = *(long *)(param_1 + 8) + lVar6;
          *(undefined1 *)(lVar2 + -6) = 0;
          *(undefined2 *)(lVar2 + -8) = 0;
          *(undefined8 *)(lVar2 + -0x10) = 0;
          memset(lVar2,0,0x51);
          *(long *)(lVar2 + -0x18) = (long)puVar1;
          lVar5 = lVar5 + 1;
          *(long **)(*(long *)(param_1 + 8) + lVar6 + -0x118) = (long *)(lVar2 + -0x18);
          lVar6 = lVar6 + 0x1b8;
        } while (lVar5 < (long)(ulong)*(byte *)(param_1 + 0x26));
      }
    }
    uVar4 = 1;
    *(char *)(param_1 + 0x2c) = (char)param_2;
    *(ushort *)(param_1 + 0x2f) = *(ushort *)(param_1 + 0x2f) | 4;
  }
  return uVar4;
}

// ==== Aska::RenderPass::Clone(Aska::RenderPass const*, Aska::RenderPass const*, bool)
// vaddr 0x21bb5c4 | ghidra 0x22bb5c4 | size 576 | symbol _ZN4Aska10RenderPass5CloneEPKS0_S2_b | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10RenderPass5CloneEPKS0_S2_b(long param_1,long param_2,long param_3,ushort param_4)

{
  ushort uVar1;
  long lVar2;
  ulong uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  
  uVar3 = Aska::RenderPass::Create(int)(param_1,*(undefined1 *)(param_2 + 0x2c));
  if ((uVar3 & 1) == 0) {
code_r0x022bb780:
    uVar4 = 0;
  }
  else {
    if (*(char *)(param_1 + 0x26) != '\0') {
      lVar8 = 0;
      if (param_3 == 0) {
        lVar9 = 0;
        do {
          Aska::ShaderConstantManager::Clone(Aska::ShaderConstantManager const*)(*(long *)(param_1 + 8) + lVar8,*(long *)(param_2 + 8) + lVar8);
          lVar7 = *(long *)(*(long *)(param_1 + 8) + lVar8 + 0x20);
          lVar10 = *(long *)(*(long *)(param_2 + 8) + lVar8 + 0x20);
          if ((param_4 & 1) == 0) {
            uVar3 = Aska::ShaderNodeModifier::Create(int, void*)(lVar7,*(undefined2 *)(lVar10 + 0x80),0);
            if ((uVar3 & 1) == 0) goto code_r0x022bb780;
            Aska::ShaderNodeModifier::Clone(Aska::ShaderNodeChunk const*)(lVar7,*(undefined8 *)(lVar10 + 8));
          }
          else {
            uVar4 = *(undefined8 *)(lVar10 + 8);
            *(undefined1 *)(lVar7 + 0x10) = 0;
            *(undefined8 *)(lVar7 + 8) = uVar4;
          }
          lVar9 = lVar9 + 1;
          lVar7 = *(long *)(param_2 + 8) + lVar8;
          lVar10 = *(long *)(param_1 + 8) + lVar8;
          lVar8 = lVar8 + 0x1b8;
          *(undefined8 *)(lVar10 + 0x28) = *(undefined8 *)(lVar7 + 0x28);
        } while (lVar9 < (long)(ulong)*(byte *)(param_1 + 0x26));
      }
      else {
        lVar9 = 0x20;
        do {
          lVar7 = *(long *)(param_3 + 8) + lVar9;
          lVar2 = lVar7 + -0x20;
          lVar10 = *(long *)(param_1 + 8) + lVar9;
          *(long *)(lVar10 + -0x18) = lVar2;
          if (lVar2 != 0) {
            *(undefined8 *)(lVar10 + -0x10) = *(undefined8 *)(lVar7 + -0x10);
          }
          lVar7 = *(long *)(*(long *)(param_1 + 8) + lVar9);
          lVar10 = *(long *)(*(long *)(param_2 + 8) + lVar9);
          if ((param_4 & 1) == 0) {
            uVar3 = Aska::ShaderNodeModifier::Create(int, void*)(lVar7,*(undefined2 *)(lVar10 + 0x80),0);
            if ((uVar3 & 1) == 0) goto code_r0x022bb780;
            Aska::ShaderNodeModifier::Clone(Aska::ShaderNodeChunk const*)(lVar7,*(undefined8 *)(lVar10 + 8));
          }
          else {
            uVar4 = *(undefined8 *)(lVar10 + 8);
            *(undefined1 *)(lVar7 + 0x10) = 0;
            *(undefined8 *)(lVar7 + 8) = uVar4;
          }
          lVar8 = lVar8 + 1;
          lVar7 = *(long *)(param_2 + 8) + lVar9;
          lVar10 = *(long *)(param_1 + 8) + lVar9;
          lVar9 = lVar9 + 0x1b8;
          *(undefined8 *)(lVar10 + 8) = *(undefined8 *)(lVar7 + 8);
        } while (lVar8 < (long)(ulong)*(byte *)(param_1 + 0x26));
      }
    }
    uVar1 = *(ushort *)(param_1 + 0x2f);
    *(ushort *)(param_1 + 0x2f) = uVar1 & 0xfff0 | uVar1 & 7 | (param_4 & 1) << 3;
    if (*(long *)(param_1 + 0x38) != 0) {
      plVar5 = (long *)(*(long *)(param_1 + 0x38) + 0x40);
      lVar8 = *plVar5;
      lVar9 = lVar8;
      if (lVar8 == param_1) {
        plVar6 = (long *)(param_1 + 0x48);
code_r0x022bb794:
        *plVar5 = *plVar6;
      }
      else {
        while (lVar7 = lVar9, lVar7 != 0) {
          plVar6 = (long *)(lVar7 + 0x48);
          if (lVar7 == param_1) {
            plVar5 = (long *)(lVar8 + 0x48);
            goto code_r0x022bb794;
          }
          lVar8 = lVar7;
          lVar9 = *plVar6;
        }
      }
      *(undefined8 *)(param_1 + 0x48) = 0;
      *(undefined8 *)(param_1 + 0x38) = 0;
    }
    if (param_3 == 0) {
      param_3 = *(long *)(param_2 + 0x38);
    }
    lVar8 = *(long *)(param_3 + 0x40);
    if (lVar8 != 0) {
      *(long *)(param_1 + 0x48) = lVar8;
    }
    *(long *)(param_3 + 0x40) = param_1;
    uVar4 = 1;
    *(long *)(param_1 + 0x38) = param_3;
    uVar1 = *(ushort *)(param_2 + 0x2f);
    *(undefined1 *)(param_1 + 0x31) = *(undefined1 *)(param_1 + 0x31);
    *(ushort *)(param_1 + 0x2f) = *(ushort *)(param_1 + 0x2f) & 0xf7ff | uVar1 & 0x800;
  }
  return uVar4;
}

// ==== Aska::RenderPass::Init(int, void*)
// vaddr 0x21bb804 | ghidra 0x22bb804 | size 284 | symbol _ZN4Aska10RenderPass4InitEiPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10RenderPass4InitEiPv(long param_1,int param_2)

{
  long lVar1;
  byte bVar2;
  undefined1 auVar3 [16];
  undefined8 uVar4;
  ulong *puVar5;
  long lVar6;
  ulong uVar7;
  undefined1 *puVar8;
  
  if (*(long *)(param_1 + 8) == 0) {
    uVar7 = (ulong)param_2;
    auVar3._8_8_ = 0;
    auVar3._0_8_ = uVar7;
    lVar6 = (long)param_2 * 0x1b8 + 8;
    if (SUB168(auVar3 * ZEXT816(0x1b8),8) != 0 ||
        0xfffffffffffffff7 < (ulong)((long)param_2 * 0x1b8)) {
      lVar6 = -1;
    }
    puVar5 = (ulong *)operator new[](unsigned long, unsigned long, bool)(lVar6,0x10,1);
    if (puVar5 == (ulong *)0x0) {
      *(undefined8 *)(param_1 + 8) = 0;
      uVar4 = 0;
    }
    else {
      *puVar5 = uVar7;
      if (param_2 != 0) {
        lVar6 = 0;
        do {
          puVar8 = (undefined1 *)((long)puVar5 + lVar6 + 0x25);
          *puVar8 = 1;
          bVar2 = *(byte *)((long)puVar5 + lVar6 + 0x60);
          *(undefined4 *)((long)puVar5 + lVar6 + 0x20) = 0;
          *(undefined8 *)((long)puVar5 + lVar6 + 0x10) = 0;
          *(undefined8 *)((long)puVar5 + lVar6 + 8) = 0;
          *(undefined1 **)((long)puVar5 + lVar6 + 0x18) = puVar8;
          *(undefined8 *)((long)puVar5 + lVar6 + 0x50) = 0;
          *(undefined8 *)((long)puVar5 + lVar6 + 0x48) = 0;
          *(undefined8 *)((long)puVar5 + lVar6 + 0x40) = 0;
          *(undefined8 *)((long)puVar5 + lVar6 + 0x38) = 0;
          *(undefined8 *)((long)puVar5 + lVar6 + 0x58) = 0;
          *(undefined8 *)((long)puVar5 + lVar6 + 0x30) = 0;
          *(undefined8 *)((long)puVar5 + lVar6 + 0x28) = 0;
          *(undefined2 *)((long)puVar5 + lVar6 + 0x61) = 0;
          *(byte *)((long)puVar5 + lVar6 + 0x24) = *(byte *)((long)puVar5 + lVar6 + 0x24) & 0xfc | 2
          ;
          memset((long)puVar5 + lVar6 + 100,0,0x84);
          lVar1 = lVar6 + 0x1b8;
          *(byte *)((long)puVar5 + lVar6 + 0x60) = bVar2 & 0xf8;
          lVar6 = lVar1;
        } while (uVar7 * 0x1b8 - lVar1 != 0);
      }
      uVar4 = 1;
      *(ulong **)(param_1 + 8) = puVar5 + 1;
      *(char *)(param_1 + 0x26) = (char)param_2;
      *(undefined1 *)(param_1 + 0x29) = 0;
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}

// ==== Aska::RenderPass::RenderPass()
// vaddr 0x21bb920 | ghidra 0x22bb920 | size 132 | symbol _ZN4Aska10RenderPassC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10RenderPassC1Ev(long *param_1)

{
  uint uVar1;
  undefined *puVar2;
  
  puVar2 = PTR__ZTVN4Aska10RenderPassE_02cbbab0;
  param_1[4] = 0;
  *param_1 = (long)(puVar2 + 0x10);
  param_1[1] = 0;
  *(undefined2 *)((long)param_1 + 0x2a) = 0;
  *(undefined1 *)((long)param_1 + 0x2d) = 0;
  uVar1 = *(uint3 *)((long)param_1 + 0x2f) & 0xf0b008 | 0x20013;
  *(short *)((long)param_1 + 0x2f) = (short)uVar1;
  *(char *)((long)param_1 + 0x31) = (char)(uVar1 >> 0x10);
  memset(param_1 + 7,0,0x188);
  *(undefined2 *)(param_1 + 0x31) = 0xfefe;
  param_1[0x30] = -0x101010101010102;
  param_1[0x33] = 0;
  return;
}

// ==== Aska::RenderPass::~RenderPass()
// vaddr 0x21bb9a4 | ghidra 0x22bb9a4 | size 544 | symbol _ZN4Aska10RenderPassD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10RenderPassD2Ev(long *param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  undefined8 *puVar4;
  long lVar5;
  long *plVar6;
  long lVar7;
  long *plVar8;
  long *plVar9;
  long *plVar10;
  long *plVar11;
  long *plVar12;
  long lVar13;
  
  *param_1 = (long)(PTR__ZTVN4Aska10RenderPassE_02cbbab0 + 0x10);
  if (*(char *)((long)param_1 + 0x26) != '\0') {
    lVar13 = 0;
    do {
      lVar5 = param_1[1];
      lVar7 = *(long *)(lVar5 + lVar13 * 0x1b8 + 0x38);
      if (lVar7 != 0) {
        piVar1 = (int *)(lVar7 + 0x4c);
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        *(undefined8 *)(param_1[1] + lVar13 * 0x1b8 + 0x38) = 0;
        lVar5 = param_1[1];
      }
      lVar7 = *(long *)(lVar5 + lVar13 * 0x1b8 + 0x40);
      if (lVar7 != 0) {
        piVar1 = (int *)(lVar7 + 0x4c);
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        *(undefined8 *)(param_1[1] + lVar13 * 0x1b8 + 0x40) = 0;
        lVar5 = param_1[1];
      }
      puVar4 = *(undefined8 **)(lVar5 + lVar13 * 0x1b8 + 0x20);
      if (puVar4 != (undefined8 *)0x0) {
        (**(code **)*puVar4)();
        *(undefined8 *)(param_1[1] + lVar13 * 0x1b8 + 0x20) = 0;
        lVar5 = param_1[1];
      }
      if (*(long *)(lVar5 + lVar13 * 0x1b8 + 0x48) != 0) {
        Aska::RenderState::Release()();
        *(undefined8 *)(param_1[1] + lVar13 * 0x1b8 + 0x48) = 0;
      }
      lVar13 = lVar13 + 1;
    } while (lVar13 < (long)(ulong)*(byte *)((long)param_1 + 0x26));
  }
  plVar6 = param_1 + 7;
  if (*plVar6 == 0) goto code_r0x022bbb0c;
  plVar8 = (long *)(*plVar6 + 0x40);
  plVar10 = (long *)*plVar8;
  plVar12 = plVar10;
  plVar9 = param_1;
  if (plVar10 == param_1) {
    plVar12 = param_1 + 9;
code_r0x022bbaf8:
    *plVar8 = *plVar12;
  }
  else {
    for (; plVar8 = plVar12, plVar8 != (long *)0x0; plVar12 = (long *)*plVar12) {
      plVar12 = plVar8 + 9;
      if (plVar8 == param_1) {
        plVar8 = plVar10 + 9;
        goto code_r0x022bbaf8;
      }
      plVar10 = plVar8;
    }
  }
  do {
    do {
      while( true ) {
        plVar9[9] = 0;
        *plVar6 = 0;
code_r0x022bbb0c:
        plVar9 = (long *)param_1[8];
        if (plVar9 == (long *)0x0) {
          lVar13 = param_1[1];
          if (lVar13 != 0) {
            lVar5 = *(long *)(lVar13 + -8);
            if (lVar5 != 0) {
              lVar5 = lVar5 * 0x1b8;
              do {
                Aska::ShaderConstantManager::~ShaderConstantManager()(lVar13 + lVar5 + -0x1b8);
                lVar5 = lVar5 + -0x1b8;
              } while (lVar5 != 0);
            }
            operator delete[](void*)((long *)(lVar13 + -8));
            param_1[1] = 0;
          }
          if (param_1[0x33] != 0) {
            operator delete[](void*)();
            param_1[0x33] = 0;
          }
          return;
        }
        plVar6 = plVar9 + 7;
        plVar8 = (long *)(*plVar6 + 0x40);
        plVar10 = (long *)*plVar8;
        if (plVar10 != plVar9) break;
        plVar12 = plVar9 + 9;
code_r0x022bbbb8:
        *plVar8 = *plVar12;
      }
      plVar8 = plVar10;
    } while (plVar10 == (long *)0x0);
    do {
      plVar11 = plVar8;
      plVar12 = plVar11 + 9;
      if (plVar11 == plVar9) {
        plVar8 = plVar10 + 9;
        goto code_r0x022bbbb8;
      }
      plVar8 = (long *)*plVar12;
      plVar10 = plVar11;
    } while ((long *)*plVar12 != (long *)0x0);
  } while( true );
}

// ==== Aska::RenderPass::~RenderPass()
// vaddr 0x21bbbc4 | ghidra 0x22bbbc4 | size 24 | symbol _ZN4Aska10RenderPassD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10RenderPassD0Ev(undefined8 param_1)

{
  Aska::RenderPass::~RenderPass()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RenderPass::SetNoneModifyingShader()
// vaddr 0x21bbbdc | ghidra 0x22bbbdc | size 300 | symbol _ZN4Aska10RenderPass22SetNoneModifyingShaderEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10RenderPass22SetNoneModifyingShaderEv(long param_1)

{
  long *plVar1;
  bool bVar2;
  uint uVar3;
  long lVar4;
  long lVar5;
  undefined8 uVar6;
  long lVar7;
  
  if (*(char *)(param_1 + 0x27) == -1) {
    *(ushort *)(param_1 + 0x2f) = *(ushort *)(param_1 + 0x2f) & 0xffef;
    return 0;
  }
  *(undefined1 *)(param_1 + 0x27) = 0xff;
  *(undefined1 *)(param_1 + 0x25) = 0;
  uVar3 = *(uint3 *)(param_1 + 0x2f) | 0x10;
  *(short *)(param_1 + 0x2f) = (short)uVar3;
  if (*(char *)(param_1 + 0x26) != '\0') {
    lVar4 = 0;
    lVar5 = 0x20;
    do {
      lVar4 = lVar4 + 1;
      lVar7 = *(long *)(*(long *)(param_1 + 8) + lVar5);
      plVar1 = (long *)(*(long *)(*(long *)(param_1 + 0x38) + 8) + lVar5);
      lVar5 = lVar5 + 0x1b8;
      uVar6 = *(undefined8 *)(*plVar1 + 8);
      *(undefined1 *)(lVar7 + 0x10) = 0;
      *(undefined8 *)(lVar7 + 8) = uVar6;
    } while (lVar4 < (long)(ulong)*(byte *)(param_1 + 0x26));
    uVar3 = (uint)*(uint3 *)(param_1 + 0x2f);
  }
  *(undefined2 *)(param_1 + 0x180) = 0xfefe;
  *(char *)(param_1 + 0x31) = (char)(uVar3 >> 0x10);
  *(ushort *)(param_1 + 0x2f) = (ushort)uVar3 & 0xff9e | 1;
  if (*(long *)(param_1 + 0x40) == 0) {
    return 1;
  }
  bVar2 = false;
  lVar4 = *(long *)(param_1 + 0x40);
code_r0x022bbcb4:
  do {
    lVar5 = lVar4;
    if (!bVar2) {
      bVar2 = false;
      *(ushort *)(lVar5 + 0x2f) = *(ushort *)(lVar5 + 0x2f) | 1;
      lVar4 = *(long *)(lVar5 + 0x40);
      if (*(long *)(lVar5 + 0x40) != 0) goto code_r0x022bbcb4;
    }
    bVar2 = false;
    lVar4 = *(long *)(lVar5 + 0x48);
    if (*(long *)(lVar5 + 0x48) == 0) {
      bVar2 = true;
      lVar4 = *(long *)(lVar5 + 0x38);
      if (*(long *)(lVar5 + 0x38) == param_1) {
        return 1;
      }
    }
  } while( true );
}

// ==== Aska::RenderPass::BeginModifyingShader()
// vaddr 0x21bbd08 | ghidra 0x22bbd08 | size 32 | symbol _ZN4Aska10RenderPass20BeginModifyingShaderEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10RenderPass20BeginModifyingShaderEv(long param_1)

{
  *(ushort *)(param_1 + 0x2f) = *(ushort *)(param_1 + 0x2f) & 0xffef;
  *(undefined2 *)(param_1 + 0x27) = 0;
  return 1;
}

// ==== Aska::RenderPass::EndModifyingShader(Aska::MaterialList*)
// vaddr 0x21bbd28 | ghidra 0x22bbd28 | size 644 | symbol _ZN4Aska10RenderPass18EndModifyingShaderEPNS_12MaterialListE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10RenderPass18EndModifyingShaderEPNS_12MaterialListE(long param_1,long param_2)

{
  long lVar1;
  char cVar2;
  byte bVar3;
  bool bVar4;
  undefined8 uVar5;
  long *plVar6;
  uint uVar7;
  ulong uVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long lStack_78;
  long lStack_70;
  char cStack_68;
  undefined1 uStack_67;
  char cStack_66;
  undefined1 uStack_65;
  undefined2 uStack_64;
  undefined1 uStack_62;
  
  uVar7 = (uint)*(uint3 *)(param_1 + 0x2f);
  if (*(char *)(param_1 + 0x28) != *(char *)(param_1 + 0x25)) {
    uVar7 = uVar7 | 0x10;
    *(char *)(param_1 + 0x31) = (char)(*(uint3 *)(param_1 + 0x2f) >> 0x10);
    *(short *)(param_1 + 0x2f) = (short)uVar7;
    *(char *)(param_1 + 0x25) = *(char *)(param_1 + 0x28);
  }
  if ((uVar7 >> 4 & 1) == 0) {
    uVar5 = 0;
  }
  else {
    if (*(char *)(param_1 + 0x26) != '\0') {
      lVar10 = 0;
      lVar1 = param_1 + 0x158;
      do {
        lVar9 = *(long *)(*(long *)(param_1 + 8) + lVar10 * 0x1b8 + 0x20);
        Aska::ShaderNodeModifier::Clone(Aska::ShaderNodeChunk const*)(lVar9,*(undefined8 *)
                               (*(long *)(*(long *)(*(long *)(param_1 + 0x38) + 8) + lVar10 * 0x1b8
                                         + 0x20) + 8));
        uStack_65 = (undefined1)lVar10;
        uStack_64 = 0x1012;
        uStack_62 = 0;
        lStack_70 = 0;
        if (*(long *)(param_2 + 0x18) != 0) {
          lStack_70 = *(long *)(param_2 + 0x18) + lVar10 * 0x2a0 + 0x10;
        }
        uVar8 = (ulong)*(byte *)(param_1 + 0x27);
        lStack_78 = lVar9;
        if (*(byte *)(param_1 + 0x27) != 0) {
          lVar11 = 0;
          bVar3 = 0;
          cVar2 = *(char *)(lStack_70 + 0x1b) + *(char *)(lStack_70 + 0x247);
          do {
            uStack_67 = (undefined1)lVar11;
            cStack_68 = cVar2 + *(char *)(lVar1 + lVar11 + 0x32);
            cStack_66 = *(char *)(lVar1 + lVar11 + 0x37) + -1;
            plVar6 = *(long **)(lVar1 + lVar11 * 8);
            if (*(char *)((long)plVar6 + 0xd) == '\0') {
              (**(code **)(*plVar6 + 0x28))(plVar6,&lStack_78);
              uVar8 = (ulong)*(byte *)(param_1 + 0x27);
            }
            else {
              bVar3 = 1;
            }
            lVar11 = lVar11 + 1;
          } while (lVar11 < (long)uVar8);
          if (((int)uVar8 != 0) && (!(bool)(bVar3 ^ 1))) {
            lVar11 = 0;
            do {
              plVar6 = *(long **)(lVar1 + lVar11 * 8);
              if (*(char *)((long)plVar6 + 0xd) != '\0') {
                uStack_67 = (undefined1)lVar11;
                cStack_68 = cVar2 + *(char *)(lVar1 + lVar11 + 0x32);
                cStack_66 = *(char *)(lVar1 + lVar11 + 0x37) + -1;
                (**(code **)(*plVar6 + 0x28))(plVar6,&lStack_78);
                uVar8 = (ulong)*(byte *)(param_1 + 0x27);
              }
              lVar11 = lVar11 + 1;
            } while (lVar11 < (long)uVar8);
          }
        }
        if ((0x1b < (byte)uStack_64) || (0x15 < uStack_64._1_1_)) {
          Aska::ShaderNodeModifier::Clone(Aska::ShaderNodeChunk const*)(lVar9,*(undefined8 *)
                                 (*(long *)(*(long *)(*(long *)(param_1 + 0x38) + 8) +
                                            lVar10 * 0x1b8 + 0x20) + 8));
        }
        *(undefined1 *)(lVar9 + 0x10) = 0;
        lVar10 = lVar10 + 1;
      } while (lVar10 < (long)(ulong)*(byte *)(param_1 + 0x26));
      uVar7 = (uint)*(uint3 *)(param_1 + 0x2f);
    }
    *(char *)(param_1 + 0x31) = (char)(uVar7 >> 0x10);
    *(ushort *)(param_1 + 0x2f) = (ushort)uVar7 & 0xff9e | 1;
    if (*(long *)(param_1 + 0x40) != 0) {
      bVar4 = false;
      lVar1 = *(long *)(param_1 + 0x40);
code_r0x022bbf48:
      do {
        do {
          lVar10 = lVar1;
          if (!bVar4) {
            bVar4 = false;
            *(ushort *)(lVar10 + 0x2f) = *(ushort *)(lVar10 + 0x2f) | 1;
            lVar1 = *(long *)(lVar10 + 0x40);
            if (*(long *)(lVar10 + 0x40) != 0) goto code_r0x022bbf48;
          }
          bVar4 = false;
          lVar1 = *(long *)(lVar10 + 0x48);
        } while (*(long *)(lVar10 + 0x48) != 0);
        bVar4 = true;
        lVar1 = *(long *)(lVar10 + 0x38);
      } while (*(long *)(lVar10 + 0x38) != param_1);
    }
    uVar5 = 1;
  }
  return uVar5;
}

// ==== Aska::RenderPass::AddShaderAdapter(Aska::BaseShaderAdapter*, int)
// vaddr 0x21bbfac | ghidra 0x22bbfac | size 700 | symbol _ZN4Aska10RenderPass16AddShaderAdapterEPNS_17BaseShaderAdapterEi | lib libSOA-3.7.0.so | 2026-10-04
ushort _ZN4Aska10RenderPass16AddShaderAdapterEPNS_17BaseShaderAdapterEi
                 (long param_1,long *param_2,uint param_3)

{
  long lVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  ushort uVar5;
  bool bVar6;
  uint uVar7;
  long *plVar8;
  ulong uVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  ulong uVar13;
  long lVar14;
  ushort uVar15;
  long lVar16;
  long lVar17;
  
  bVar2 = *(byte *)(param_1 + 0x27);
  uVar13 = (ulong)bVar2;
  if (bVar2 != 5) {
    bVar3 = *(byte *)((long)param_2 + 0xc);
    bVar4 = *(byte *)(param_1 + 0x28);
    uVar7 = (uint)bVar4 + (uint)bVar3;
    if (uVar7 < 9) {
      lVar14 = param_1 + uVar13;
      if (bVar3 == 0) {
        bVar4 = 0xff;
      }
      *(byte *)(lVar14 + 0x18a) = bVar4;
      *(char *)(param_1 + 0x28) = (char)uVar7;
      lVar1 = param_1 + uVar13 * 8;
      if (*(long **)(lVar1 + 0x158) == param_2) {
        uVar15 = 0;
      }
      else {
        if (bVar2 < 4) {
          lVar11 = uVar13 + 0x2c;
          do {
            if (*(long *)(param_1 + lVar11 * 8) == 0) break;
            lVar12 = lVar11 + -0x2c;
            *(undefined8 *)(param_1 + lVar11 * 8) = 0;
            lVar11 = lVar11 + 1;
          } while (lVar12 < 3);
        }
        uVar15 = 1;
        *(long **)(lVar1 + 0x158) = param_2;
      }
      if (*(byte *)(lVar14 + 399) != param_3) {
        uVar15 = 1;
        *(char *)(lVar14 + 399) = (char)param_3;
      }
      uVar7 = (**(code **)*param_2)(param_2);
      lVar1 = param_1 + uVar13 * 2;
      if (uVar7 != *(ushort *)(lVar1 + 0x180)) {
        uVar15 = 1;
        *(short *)(lVar1 + 0x180) = (short)uVar7;
      }
      if (bVar3 != 0) {
        uVar7 = 0;
        do {
          lVar1 = param_1 + ((long)*(char *)(lVar14 + 0x18a) + (long)(int)uVar7) * 0x20;
          plVar8 = (long *)(**(code **)(*param_2 + 0x20))(param_2,uVar7);
          lVar10 = *(long *)(lVar1 + 0x60);
          lVar11 = *plVar8;
          lVar12 = plVar8[1];
          if (lVar11 == 0) {
            lVar16 = 0;
          }
          else {
            lVar16 = plVar8[2];
            if (lVar16 == 0) {
              lVar16 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
              lVar17 = lVar16 + 0xb0;
              Aska::CriticalSection::Enter() const(lVar17);
              lVar16 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar16,lVar11,1);
              Aska::CriticalSection::Leave() const(lVar17);
              plVar8[2] = lVar16;
            }
          }
          lVar17 = plVar8[2];
          lVar11 = *(long *)(lVar1 + 0x68);
          uVar7 = uVar7 + 1;
          *(long *)(lVar1 + 0x70) = plVar8[3];
          *(long *)(lVar1 + 0x68) = lVar17;
          lVar17 = *plVar8;
          uVar15 = uVar15 | lVar10 != lVar12 | (ushort)(lVar16 != lVar11);
          *(long *)(lVar1 + 0x60) = plVar8[1];
          *(long *)(lVar1 + 0x58) = lVar17;
        } while (bVar3 != uVar7);
      }
      uVar5 = *(ushort *)(param_1 + 0x2f);
      *(ushort *)(param_1 + 0x2f) = uVar5 & 0xffe0 | uVar5 & 0xf | (uVar15 | uVar5 >> 4 & 1) << 4;
      if (*(char *)(param_1 + 0x26) != '\0') {
        lVar14 = 0;
        do {
          uVar9 = (**(code **)(*param_2 + 0x18))
                            (param_2,*(long *)(param_1 + 8) + lVar14 * 0x1b8,uVar13);
          if ((uVar9 & 1) != 0) {
            *(ushort *)(param_1 + 0x2f) = *(ushort *)(param_1 + 0x2f) | 1;
            if (*(long *)(param_1 + 0x40) != 0) {
              bVar6 = false;
              lVar1 = *(long *)(param_1 + 0x40);
code_r0x022bc1e8:
              do {
                do {
                  lVar11 = lVar1;
                  if (!bVar6) {
                    bVar6 = false;
                    *(ushort *)(lVar11 + 0x2f) = *(ushort *)(lVar11 + 0x2f) | 1;
                    lVar1 = *(long *)(lVar11 + 0x40);
                    if (*(long *)(lVar11 + 0x40) != 0) goto code_r0x022bc1e8;
                  }
                  bVar6 = false;
                  lVar1 = *(long *)(lVar11 + 0x48);
                } while (*(long *)(lVar11 + 0x48) != 0);
                bVar6 = true;
                lVar1 = *(long *)(lVar11 + 0x38);
              } while (*(long *)(lVar11 + 0x38) != param_1);
            }
          }
          lVar14 = lVar14 + 1;
        } while (lVar14 < (long)(ulong)*(byte *)(param_1 + 0x26));
      }
      *(char *)(param_1 + 0x27) = *(char *)(param_1 + 0x27) + '\x01';
      return uVar15;
    }
  }
  return 0;
}

// ==== Aska::RenderPass::InvalidateShaders()
// vaddr 0x21bc268 | ghidra 0x22bc268 | size 100 | symbol _ZN4Aska10RenderPass17InvalidateShadersEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10RenderPass17InvalidateShadersEv(long param_1)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  
  if (((*(long *)(*(long *)(param_1 + 8) + 0x20) != 0) && (*(char *)(param_1 + 0x26) != '\0')) &&
     (*(undefined1 *)(*(long *)(*(long *)(param_1 + 8) + 0x20) + 0x10) = 0,
     1 < *(byte *)(param_1 + 0x26))) {
    lVar2 = 1;
    lVar3 = 0x1d8;
    do {
      lVar2 = lVar2 + 1;
      plVar1 = (long *)(*(long *)(param_1 + 8) + lVar3);
      lVar3 = lVar3 + 0x1b8;
      *(undefined1 *)(*plVar1 + 0x10) = 0;
    } while (lVar2 < (long)(ulong)*(byte *)(param_1 + 0x26));
  }
  *(ushort *)(param_1 + 0x2f) = *(ushort *)(param_1 + 0x2f) & 0xffdf;
  return;
}

// ==== Aska::RenderPass::InvalidateShaderCaches()
// vaddr 0x21bc2cc | ghidra 0x22bc2cc | size 204 | symbol _ZN4Aska10RenderPass22InvalidateShaderCachesEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska10RenderPass22InvalidateShaderCachesEv(long param_1)

{
  int iVar1;
  long lVar2;
  long lVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  
  lVar2 = *(long *)(param_1 + 8);
  if ((*(long *)(lVar2 + 0x20) == 0) || (*(char *)(param_1 + 0x26) == '\0')) {
    iVar4 = 0;
  }
  else {
    lVar5 = 0;
    iVar4 = 0;
    lVar6 = 1;
    lVar3 = *(long *)PTR__ZN4Aska6Global20m_pShaderLinkManagerE_02cb93f8;
    while( true ) {
      lVar2 = lVar2 + lVar5;
      *(undefined1 *)(*(long *)(lVar2 + 0x20) + 0x10) = 0;
      if (*(long *)(lVar2 + 0x38) != 0) {
        iVar1 = Aska::AHSLCacheManagerV2::L1::ReleaseAndDeleteShaderCache(Aska::ShaderCache*)(lVar3 + 0x38);
        iVar4 = iVar1 + iVar4;
        *(undefined8 *)(lVar2 + 0x38) = 0;
      }
      if (*(long *)(lVar2 + 0x40) != 0) {
        iVar1 = Aska::AHSLCacheManagerV2::L1::ReleaseAndDeleteShaderCache(Aska::ShaderCache*)(lVar3 + 0x38);
        iVar4 = iVar1 + iVar4;
        *(undefined8 *)(lVar2 + 0x40) = 0;
      }
      if ((long)(ulong)*(byte *)(param_1 + 0x26) <= lVar6) break;
      lVar2 = *(long *)(param_1 + 8);
      lVar5 = lVar5 + 0x1b8;
      lVar6 = lVar6 + 1;
    }
  }
  *(ushort *)(param_1 + 0x2f) = *(ushort *)(param_1 + 0x2f) & 0xffdf;
  return iVar4;
}

// ==== Aska::RenderPass::ReadyShaderKey(int, int, Aska::MaterialList*, bool)
// vaddr 0x21bc398 | ghidra 0x22bc398 | size 496 | symbol _ZN4Aska10RenderPass14ReadyShaderKeyEiiPNS_12MaterialListEb | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska10RenderPass14ReadyShaderKeyEiiPNS_12MaterialListEb
          (long param_1,undefined4 param_2,undefined4 param_3,long param_4,ulong param_5)

{
  long lVar1;
  long lVar2;
  char *pcVar3;
  uint uVar4;
  undefined *puVar5;
  uint uVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  undefined6 uStack_70;
  undefined2 uStack_6a;
  undefined6 uStack_68;
  undefined1 uStack_62;
  
  puVar5 = PTR__ZN4Aska10RenderPass20m_ucSpecialAtCDitherE_02cb8898;
  uVar7 = (ulong)*(byte *)(param_1 + 0x26);
  if (*(byte *)(param_1 + 0x26) != 0) {
    lVar9 = 0;
    lVar10 = 0;
    lVar11 = 0x10;
    if ((param_5 & 1) == 0) {
      do {
        lVar8 = *(long *)(*(long *)(param_1 + 8) + lVar9 + 0x20);
        if (*(char *)(lVar8 + 0x10) == '\0') {
          uVar4 = *(uint *)(param_1 + 0x20);
          lVar2 = 0;
          if (*(long *)(param_4 + 0x18) != 0) {
            lVar2 = *(long *)(param_4 + 0x18) + lVar11;
          }
          if (*puVar5 == -1) {
            pcVar3 = (char *)(lVar2 + 0x232);
            if ((*(byte *)(param_1 + 0x31) & 8) != 0) {
              pcVar3 = (char *)(param_1 + 0x1c0);
            }
            if (*pcVar3 != '\0') {
              uVar4 = uVar4 | 0x20000;
            }
          }
          uStack_68 = 0;
          uStack_70 = 0;
          uStack_6a = 0;
          uStack_62 = *(undefined1 *)(lVar2 + 0x1e);
          lVar2 = *(long *)(param_1 + 8) + lVar9;
          uVar6 = (uint)*(byte *)(*(long *)(lVar2 + 0x28) + 0x2c);
          Aska::ShaderNodeHandler::MakeShaderKey(int, int, unsigned int, int, Aska::ShaderConstantManager*, Aska::ShaderContext*)(lVar8,param_2,param_3,uVar4,(uVar6 & 2) << 0xe | (uVar6 & 1) << 0xb,lVar2,
                          &uStack_70);
          if (*(char *)(lVar8 + 0x10) == '\0') {
            return 0;
          }
          uVar7 = (ulong)*(byte *)(param_1 + 0x26);
        }
        lVar10 = lVar10 + 1;
        lVar9 = lVar9 + 0x1b8;
        lVar11 = lVar11 + 0x2a0;
      } while (lVar10 < (long)uVar7);
    }
    else {
      do {
        lVar8 = *(long *)(*(long *)(param_1 + 8) + lVar9 + 0x20);
        if (*(char *)(lVar8 + 0x10) == '\0') {
          uVar4 = *(uint *)(param_1 + 0x20);
          lVar2 = 0;
          if (*(long *)(param_4 + 0x18) != 0) {
            lVar2 = *(long *)(param_4 + 0x18) + lVar11;
          }
          if (*puVar5 == -1) {
            pcVar3 = (char *)(lVar2 + 0x232);
            if ((*(byte *)(param_1 + 0x31) & 8) != 0) {
              pcVar3 = (char *)(param_1 + 0x1c0);
            }
            if (*pcVar3 != '\0') {
              uVar4 = uVar4 | 0x20000;
            }
          }
          lVar1 = *(long *)(param_1 + 8) + lVar9;
          uVar6 = (uint)*(byte *)(*(long *)(lVar1 + 0x28) + 0x2c);
          Aska::ShaderNodeHandler::MakeShaderKey(int, int, unsigned int, int, Aska::ShaderConstantManager*, Aska::ShaderContext*)(lVar8,param_2,param_3,uVar4,(uVar6 & 2) << 0xe | (uVar6 & 1) << 0xb,lVar1,
                          lVar2 + 0x10);
          if (*(char *)(lVar8 + 0x10) == '\0') {
            return 0;
          }
          uVar7 = (ulong)*(byte *)(param_1 + 0x26);
        }
        lVar10 = lVar10 + 1;
        lVar9 = lVar9 + 0x1b8;
        lVar11 = lVar11 + 0x2a0;
      } while (lVar10 < (long)uVar7);
    }
  }
  return 1;
}

// ==== Aska::RenderPass::GetShaderKeyFlags(Aska::RenderPassBatch const*)
// vaddr 0x21bc588 | ghidra 0x22bc588 | size 28 | symbol _ZN4Aska10RenderPass17GetShaderKeyFlagsEPKNS_15RenderPassBatchE | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska10RenderPass17GetShaderKeyFlagsEPKNS_15RenderPassBatchE(long param_1)

{
  uint uVar1;
  
  uVar1 = (uint)*(byte *)(*(long *)(param_1 + 0x28) + 0x2c);
  return (uVar1 & 2) << 0xe | (uVar1 & 1) << 0xb;
}

// ==== Aska::RenderPass::ReadyShader()
// vaddr 0x21bc5a4 | ghidra 0x22bc5a4 | size 592 | symbol _ZN4Aska10RenderPass11ReadyShaderEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10RenderPass11ReadyShaderEv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  long *plVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long *plVar12;
  long *plVar13;
  ulong *puVar14;
  long lVar15;
  long lVar16;
  
  lVar9 = *(long *)PTR__ZN4Aska6Global20m_pShaderLinkManagerE_02cb93f8;
  puVar14 = (ulong *)(param_1 + 0x10);
  *puVar14 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  if (*(char *)(param_1 + 0x26) != '\0') {
    lVar15 = 0;
    do {
      lVar16 = *(long *)(param_1 + 8);
      lVar11 = lVar16 + lVar15 * 0x1b8;
      plVar12 = (long *)(lVar11 + 0x38);
      lVar10 = *(long *)(lVar11 + 0x20);
      plVar13 = (long *)(lVar11 + 0x40);
      if (*plVar12 != 0) {
        piVar1 = (int *)(*plVar12 + 0x4c);
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        *plVar12 = 0;
      }
      if (*plVar13 != 0) {
        piVar1 = (int *)(*plVar13 + 0x4c);
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        *plVar13 = 0;
      }
      if ((*(byte *)(lVar16 + lVar15 * 0x1b8 + 0x58) >> 2 & 1) == 0) {
        if (*(char *)(lVar10 + 0x11) == '\0') {
          uVar6 = 0;
          if ((*(byte *)(lVar10 + 0x10) >> 1 & 1) == 0) goto code_r0x022bc668;
code_r0x022bc684:
          plVar8 = plVar13;
          if (*(char *)(lVar10 + 0x12) == '\0') {
            uVar7 = 0;
          }
          else {
            uVar7 = *(undefined8 *)(lVar10 + 0x20);
          }
        }
        else {
          uVar6 = *(undefined8 *)(lVar10 + 0x18);
          if ((*(byte *)(lVar10 + 0x10) >> 1 & 1) != 0) goto code_r0x022bc684;
code_r0x022bc668:
          uVar7 = 0;
          plVar8 = (long *)0x0;
        }
        iVar4 = Aska::AofAhslManager::SearchShaders(unsigned char const*, unsigned char const*, Aska::ShaderCache**, Aska::ShaderCache**)(lVar9 + 8,uVar6,uVar7,plVar12,plVar8);
        if ((ulong *)*plVar12 == (ulong *)0x0) {
          return 0;
        }
        *puVar14 = *puVar14 | *(ulong *)*plVar12;
        if ((ulong *)*plVar13 != (ulong *)0x0) {
          *(ulong *)(param_1 + 0x18) = *(ulong *)(param_1 + 0x18) | *(ulong *)*plVar13;
          piVar1 = (int *)(*plVar13 + 0x4c);
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar3) {
              *piVar1 = *piVar1 + 1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
        }
        if (*plVar12 != 0) {
          piVar1 = (int *)(*plVar12 + 0x4c);
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar3) {
              *piVar1 = *piVar1 + 1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
        }
        plVar13 = (long *)(lVar16 + lVar15 * 0x1b8 + 0x28);
        if (*plVar13 == 0) {
          if (iVar4 != 0) {
            return 0;
          }
        }
        else {
          if ((*(ushort *)(param_1 + 0x2f) >> 0xb & 1) == 0) {
            uVar6 = Aska::PrimitiveBuffer::GetVertexAsmBit() const();
            uVar5 = Aska::PrimitiveBuffer::GetVertexStride() const(*plVar13);
          }
          else {
            uVar6 = Aska::PrimitiveBuffer::GetVertexAsmBitSource() const();
            uVar5 = Aska::PrimitiveBuffer::GetVertexStrideSource() const(*plVar13);
          }
          lVar10 = Aska::AHSLCacheManagerV2::SearchBindedVS(Aska::ShaderCache*, unsigned long, int)(lVar9 + 8,*plVar12,uVar6,uVar5);
          *(long *)(lVar16 + lVar15 * 0x1b8 + 0x30) = lVar10;
          if (iVar4 != 0) {
            return 0;
          }
          if (lVar10 == 0) {
            return 0;
          }
        }
        lVar10 = *(long *)(param_1 + 8) + lVar15 * 0x1b8;
        *(byte *)(lVar10 + 0x1c) = *(byte *)(lVar10 + 0x1c) | 2;
      }
      lVar15 = lVar15 + 1;
    } while (lVar15 < (long)(ulong)*(byte *)(param_1 + 0x26));
  }
  *(ushort *)(param_1 + 0x2f) = *(ushort *)(param_1 + 0x2f) | 0x22;
  return 1;
}

// ==== Aska::RenderPass::UpdatePacket()
// vaddr 0x21bc7f4 | ghidra 0x22bc7f4 | size 268 | symbol _ZN4Aska10RenderPass12UpdatePacketEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska10RenderPass12UpdatePacketEv(long param_1)

{
  long lVar1;
  ushort uVar2;
  uint3 uVar3;
  uint uVar4;
  ulong uVar5;
  uint uVar6;
  long lVar7;
  long lVar8;
  undefined4 uVar9;
  long lVar10;
  long lVar11;
  
  if (*(char *)(param_1 + 0x26) == '\0') {
    uVar9 = 0;
    uVar6 = 0;
  }
  else {
    lVar7 = 0;
    lVar8 = 0;
    uVar6 = 0;
    uVar9 = 0;
    do {
      lVar11 = *(long *)(param_1 + 8);
      lVar1 = lVar11 + lVar7;
      uVar5 = Aska::ShaderConstantManager::IsShaderConstantManagerDirty() const(lVar1);
      if (((uVar5 & 1) != 0) || ((*(byte *)(lVar1 + 0x1c) >> 1 & 1) != 0)) {
        lVar10 = *(long *)(lVar1 + 0x20);
        if (*(long *)(lVar1 + 0x38) != 0) {
          uVar4 = Aska::ShaderConstantManager::UpdatePacket(Aska::UniformValueBuffer2*, Aska::ShaderCache*)(lVar1,lVar10 + 0x28);
          uVar6 = uVar6 | uVar4 ^ 1;
        }
        lVar11 = lVar11 + lVar7;
        if (*(long *)(lVar11 + 0x40) != 0) {
          uVar4 = Aska::ShaderConstantManager::UpdatePacket(Aska::UniformValueBuffer2*, Aska::ShaderCache*)(lVar1,lVar10 + 0x38);
          uVar6 = uVar6 | uVar4 ^ 1;
        }
        uVar9 = 1;
        *(byte *)(lVar11 + 0x1c) = *(byte *)(lVar11 + 0x1c) & 0xfc;
      }
      lVar8 = lVar8 + 1;
      lVar7 = lVar7 + 0x1b8;
    } while (lVar8 < (long)(ulong)*(byte *)(param_1 + 0x26));
  }
  uVar3 = *(uint3 *)(param_1 + 0x2f);
  uVar4 = (uint)uVar3 & ((uVar3 & 0x20) >> 4 ^ 0xffdffe);
  uVar2 = (ushort)uVar4;
  *(ushort *)(param_1 + 0x2f) =
       uVar2 & 0xc000 | uVar2 & 0x1fff | (ushort)(((uVar6 | uVar3 >> 0xd) & 1) << 0xd);
  *(char *)(param_1 + 0x31) = (char)(uVar4 >> 0x10);
  return uVar9;
}

// ==== Aska::RenderPass::PrepareRenderState(Aska::MaterialList*, bool)
// vaddr 0x21bc954 | ghidra 0x22bc954 | size 1712 | symbol _ZN4Aska10RenderPass18PrepareRenderStateEPNS_12MaterialListEb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska10RenderPass18PrepareRenderStateEPNS_12MaterialListEb
          (long param_1,long param_2,uint param_3)

{
  ushort uVar1;
  long lVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  ushort uVar6;
  bool bVar7;
  long lVar8;
  long lVar9;
  undefined8 uVar10;
  int iVar11;
  undefined8 uVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  ulong uVar17;
  uint uVar18;
  long lVar19;
  long lVar20;
  long *plVar21;
  uint uVar22;
  ulong uVar23;
  ulong uVar24;
  long *plVar25;
  long lVar26;
  long lVar27;
  long lVar28;
  long lVar29;
  uint uStack_2ec;
  int iStack_2e8;
  uint uStack_2e4;
  undefined1 auStack_2e0 [8];
  long alStack_2d8 [63];
  long alStack_e0 [16];
  
  uVar12 = *(undefined8 *)PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10;
  memset(auStack_2e0,0xff,0x200);
  memset(alStack_e0,0,0x80);
  lVar9 = _UNK_02866318;
  lVar8 = _UNK_02866310;
  bVar3 = *(byte *)(param_1 + 0x26);
  if ((ulong)bVar3 != 0) {
    bVar4 = *(byte *)(param_1 + 0x25);
    uVar24 = (ulong)bVar4;
    uStack_2ec = 0xff;
    iStack_2e8 = 0xffffff;
    lVar26 = 0;
    lVar13 = uVar24 - (uVar24 & 3);
    uStack_2e4 = (uint)lVar13;
    do {
      lVar14 = *(long *)(param_2 + 0x18);
      if (lVar14 == 0) {
        lVar20 = 0;
      }
      else {
        lVar20 = *(long *)(lVar14 + lVar26 * 0x2a0);
      }
      lVar2 = 0;
      if (lVar14 != 0) {
        lVar2 = lVar14 + lVar26 * 0x2a0 + 0x10;
      }
      if (((*(byte *)(lVar2 + 0x246) >> 5 & 1) != 0) &&
         (lVar14 = *(long *)(param_1 + 8), (*(byte *)(lVar14 + lVar26 * 0x1b8 + 0x58) >> 2 & 1) == 0
         )) {
        uVar23 = (ulong)*(byte *)(lVar2 + 0x1b) + (ulong)*(byte *)(lVar2 + 0x247);
        uVar22 = (uint)uVar23;
        if (uVar22 != 0) {
          if (uVar22 < 4) {
            lVar15 = 0;
          }
          else {
            lVar15 = uVar23 - (uVar22 & 3);
            lVar19 = lVar15;
            plVar21 = alStack_e0 + 2;
            lVar16 = lVar8;
            lVar27 = lVar9;
            if (lVar15 != 0) {
              do {
                lVar29 = lVar2 + lVar16 * 0x20;
                lVar28 = lVar2 + lVar27 * 0x20;
                lVar19 = lVar19 + -4;
                plVar21[-1] = lVar28 + 0x20;
                plVar21[-2] = lVar29 + 0x20;
                plVar21[1] = lVar28 + 0x60;
                *plVar21 = lVar29 + 0x60;
                plVar21 = plVar21 + 4;
                lVar16 = lVar16 + 4;
                lVar27 = lVar27 + 4;
              } while (lVar19 != 0);
              if ((uVar23 & 3) == 0) goto code_r0x022bcb30;
            }
          }
          lVar19 = lVar2 + lVar15 * 0x20;
          lVar16 = uVar23 - lVar15;
          plVar21 = alStack_e0 + lVar15;
          do {
            lVar19 = lVar19 + 0x20;
            *plVar21 = lVar19;
            lVar16 = lVar16 + -1;
            plVar21 = plVar21 + 1;
          } while (lVar16 != 0);
        }
code_r0x022bcb30:
        uVar18 = (uint)bVar4;
        if (uVar18 != 0) {
          if (0x10 < uVar22 + uVar18) {
            return 0;
          }
          lVar19 = 0;
          if ((uVar18 < 4) || (lVar13 == 0)) {
code_r0x022bcb94:
            lVar16 = param_1 + 0x58 + lVar19 * 0x20;
            lVar27 = uVar24 - lVar19;
            plVar21 = alStack_e0 + lVar19 + uVar23;
            do {
              *plVar21 = lVar16;
              lVar27 = lVar27 + -1;
              lVar16 = lVar16 + 0x20;
              plVar21 = plVar21 + 1;
            } while (lVar27 != 0);
          }
          else {
            plVar21 = alStack_e0 + 2 + uVar23;
            lVar19 = lVar13;
            lVar16 = lVar8;
            lVar27 = lVar9;
            do {
              lVar15 = param_1 + lVar16 * 0x20;
              lVar29 = param_1 + lVar27 * 0x20;
              lVar16 = lVar16 + 4;
              lVar27 = lVar27 + 4;
              lVar19 = lVar19 + -4;
              plVar21[-1] = lVar29 + 0x58;
              plVar21[-2] = lVar15 + 0x58;
              plVar21[1] = lVar29 + 0x98;
              *plVar21 = lVar15 + 0x98;
              plVar21 = plVar21 + 4;
            } while (lVar19 != 0);
            lVar19 = lVar13;
            if ((bVar4 & 3) != 0) goto code_r0x022bcb94;
          }
          uVar23 = (ulong)(uVar22 + uVar18);
        }
        uVar17 = (ulong)*(byte *)(lVar20 + 0x15);
        if ((param_3 & 1) != 0) {
          uVar17 = (ulong)*(uint *)(&UNK_029d2000 + uVar17 * 4);
        }
        uVar22 = (uint)uVar17 & 7;
        if ((*(byte *)(lVar20 + 0x13) & 1) == 0) {
          uStack_2e4 = uVar22 | uStack_2e4 & 0xffffffe0;
        }
        else {
          uVar18 = 0x10;
          if (*(char *)(lVar20 + 0x70) == '\0') {
            uVar18 = 8;
          }
          uStack_2e4 = uVar18 | uVar22 | uStack_2e4 & 0xffffffe0;
        }
        plVar21 = (long *)(lVar14 + lVar26 * 0x1b8 + 0x48);
        lVar14 = *plVar21;
        if (lVar14 == 0) {
          lVar14 = Aska::RenderStateManager::Get(int)(uVar12,0x84);
          *plVar21 = lVar14;
          if (lVar14 == 0) {
            return 0;
          }
        }
        Aska::RenderState::Reset()(lVar14);
        if ((int)uVar23 == 0) {
          bVar7 = false;
        }
        else {
          uVar17 = 0;
          bVar7 = false;
          plVar25 = alStack_2d8;
          do {
            lVar19 = alStack_e0[uVar17];
            lVar16 = *plVar25;
            if (lVar16 != *(long *)(lVar19 + 8)) {
              bVar5 = *(byte *)(lVar19 + 0xf);
              if (*(byte *)((long)plVar25 + 7) != bVar5) {
                if ((char)bVar5 < '\0') {
                  Aska::RenderState::SetTextureSamplingWrapModeU(int, Aska::TexWrap::Mode)(lVar14,uVar17 & 0xffffffff,bVar5 & 0xf);
                  Aska::RenderState::SetTextureSamplingWrapModeV(int, Aska::TexWrap::Mode)(lVar14,uVar17 & 0xffffffff,bVar5 >> 4 & 7);
                }
                else {
                  Aska::RenderState::SetTextureSamplingWrapMode(int, Aska::TexWrap::Mode)(lVar14,uVar17 & 0xffffffff);
                }
              }
              if (*(char *)((long)plVar25 + 6) != *(char *)(lVar19 + 0xe)) {
                Aska::RenderState::SetTextureSamplingMipmapFilter(int, Aska::TexSamp::MipFilter)(lVar14,uVar17 & 0xffffffff,*(char *)(lVar19 + 0xe) < '\0');
                Aska::RenderState::SetTextureSamplingFilter(int, Aska::TexSamp::Filter)(lVar14,uVar17 & 0xffffffff,*(byte *)(lVar19 + 0xe) & 7);
              }
              uVar6 = *(ushort *)((long)plVar25 + 4);
              iVar11 = (int)*(short *)(lVar19 + 0xc) >> 6;
              if ((int)((uint)uVar6 << 0x10) >> 0x16 != iVar11) {
                if ((*(int *)PTR__ZN4Aska10RenderPass22m_iSpecialLODBiasShiftE_02cbfc78 != 0) &&
                   ((*(byte *)(lVar19 + 10) & 1) == 0)) {
                  iVar11 = iVar11 + *(int *)
                                     PTR__ZN4Aska10RenderPass22m_iSpecialLODBiasShiftE_02cbfc78 *
                                    0x20;
                  if (iVar11 < -0x1ff) {
                    iVar11 = -0x200;
                  }
                  if (0x1ff < iVar11) {
                    iVar11 = 0x200;
                  }
                }
                Aska::RenderState::SetTextureSamplingMipmapLODBias(int, int)(lVar14,uVar17 & 0xffffffff,iVar11);
              }
              uVar1 = *(ushort *)(lVar19 + 0xc) & 0x3f;
              if ((uVar6 & 0x3f) != uVar1) {
                Aska::RenderState::SetTextureSamplingTrilinearClamp(int, unsigned int)(lVar14,uVar17 & 0xffffffff,uVar1);
              }
              if (*(char *)((long)plVar25 + 1) != *(char *)(lVar19 + 9)) {
                Aska::RenderState::SetTextureSamplingMaxAnisotropic(int, unsigned int)(lVar14,uVar17 & 0xffffffff);
              }
              if ((uint)*(byte *)(lVar19 + 8) != ((uint)lVar16 & 0xff)) {
                Aska::RenderState::SetTextureSamplingAnisotropicBias(int, int)(lVar14,uVar17 & 0xffffffff,(int)(char)*(byte *)(lVar19 + 8));
              }
              bVar7 = true;
              *plVar25 = *(long *)(lVar19 + 8);
            }
            uVar17 = uVar17 + 1;
            plVar25 = plVar25 + 4;
          } while (uVar23 != uVar17);
        }
        uVar22 = uStack_2e4 >> 3 & 3;
        if ((uVar22 != 0) || ((uStack_2ec & 0xff | iStack_2e8 << 8) != (uStack_2e4 & 0xff))) {
          if (uVar22 == 2) {
            Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar14,2);
            Aska::RenderState::SetStencilOp(int, int, int, int, int, short)(lVar14,*(undefined1 *)(lVar20 + 0x74),*(undefined1 *)(lVar20 + 0x72),
                            *(undefined1 *)(lVar20 + 0x73),*(undefined1 *)(lVar20 + 0x71),
                            *(undefined1 *)(lVar20 + 0x75),0);
            Aska::RenderState::SetStencilOpCCW(int, int, int, int, int, short)(lVar14,*(undefined1 *)(lVar20 + 0x7b),*(undefined1 *)(lVar20 + 0x79),
                            *(undefined1 *)(lVar20 + 0x7a),*(undefined1 *)(lVar20 + 0x78),0,0);
          }
          else {
            if (uVar22 == 1) {
              bVar7 = true;
              Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar14,1);
              Aska::RenderState::SetStencilOp(int, int, int, int, int, short)(lVar14,*(undefined1 *)(lVar20 + 0x74),*(undefined1 *)(lVar20 + 0x72),
                              *(undefined1 *)(lVar20 + 0x73),*(undefined1 *)(lVar20 + 0x71),
                              *(undefined1 *)(lVar20 + 0x75),0);
              goto code_r0x022bceb4;
            }
            if (uVar22 == 0) {
              Aska::RenderState::EnableStencil(Aska::StencilMode::Mode)(lVar14,0);
            }
          }
          bVar7 = true;
        }
code_r0x022bceb4:
        if ((uStack_2ec & 0xff | iStack_2e8 << 8) == (uStack_2e4 & 0xff)) {
          if ((!bVar7) && (*plVar21 != 0)) {
            Aska::RenderState::Release()();
            *plVar21 = 0;
          }
code_r0x022bcf50:
          uVar6 = *(ushort *)(lVar2 + 0x245);
        }
        else {
          if (((uStack_2e4 ^ uStack_2ec) & 7) == 0) {
code_r0x022bcf44:
            iStack_2e8 = 0;
            uStack_2ec = uStack_2e4;
            goto code_r0x022bcf50;
          }
          uVar22 = uStack_2e4 & 7;
          if (uVar22 == 2) {
            Aska::RenderState::SetCullMode(int)(lVar14,2);
            goto code_r0x022bcf44;
          }
          if (uVar22 == 1) {
            uVar10 = 0;
code_r0x022bcf6c:
            Aska::RenderState::SetCullMode(int)(lVar14,uVar10);
          }
          else if (uVar22 == 0) {
            uVar10 = 1;
            goto code_r0x022bcf6c;
          }
          iStack_2e8 = 0;
          uVar6 = *(ushort *)(lVar2 + 0x245);
          uStack_2ec = uStack_2e4;
        }
        if (((uVar6 >> 5 & 1) != 0) || (*(short *)(lVar2 + 0x238) != 0 || (uVar6 & 8) != 0)) {
          uStack_2ec = 0xff;
          memset(auStack_2e0,0xff,0x200);
          iStack_2e8 = 0xffffff;
        }
      }
      lVar26 = lVar26 + 1;
    } while (lVar26 < (long)(ulong)bVar3);
  }
  *(ushort *)(param_1 + 0x2f) = *(ushort *)(param_1 + 0x2f) | 0x40;
  return 1;
}

// ==== Aska::RenderPass::PrepareShadowCastState(Aska::AofHandler*, unsigned char)
// vaddr 0x21bd004 | ghidra 0x22bd004 | size 1152 | symbol _ZN4Aska10RenderPass22PrepareShadowCastStateEPNS_10AofHandlerEh | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska10RenderPass22PrepareShadowCastStateEPNS_10AofHandlerEh
          (long param_1,long param_2,uint param_3)

{
  ulong uVar1;
  undefined *puVar2;
  long lVar3;
  byte bVar4;
  byte bVar5;
  undefined1 uVar6;
  ushort uVar7;
  float fVar8;
  long lVar9;
  long lVar10;
  int iVar11;
  undefined8 uVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  long *plVar16;
  long lVar17;
  ulong uVar18;
  uint uVar19;
  ulong *puVar20;
  long lVar21;
  ulong uVar22;
  float *pfVar23;
  long lVar24;
  long lVar25;
  long lVar26;
  undefined1 auStack_2f0 [8];
  ulong auStack_2e8 [63];
  long alStack_f0 [16];
  
  uVar12 = *(undefined8 *)PTR__ZN4Aska6Global21m_pRenderStateManagerE_02cc0c10;
  puVar2 = &UNK_029d200f;
  if ((param_3 & 1) == 0) {
    puVar2 = &UNK_029d200c;
  }
  memset(auStack_2f0,0xff,0x200);
  lVar10 = _UNK_02866318;
  lVar9 = _UNK_02866310;
  fVar8 = _UNK_027f5450;
  if (*(char *)(param_1 + 0x26) != '\0') {
    lVar21 = 0;
    pfVar23 = (float *)PTR__ZN4Aska13ShadowManager25m_fMasterShadowBiasOffsetE_02cbefc0;
    do {
      lVar3 = 0;
      if (*(long *)(param_2 + 0x100) != 0) {
        lVar3 = *(long *)(param_2 + 0x100) + lVar21 * 0x2a0 + 0x10;
      }
      if ((*(byte *)(*(long *)(param_1 + 8) + lVar21 * 0x1b8 + 0x58) >> 2 & 1) == 0) {
        bVar4 = *(byte *)(lVar3 + 0x233);
        uVar7 = *(ushort *)(lVar3 + 0x245);
        plVar16 = (long *)(*(long *)(param_1 + 8) + lVar21 * 0x1b8 + 0x48);
        lVar17 = *plVar16;
        if (lVar17 == 0) {
          iVar11 = 0x90;
          if ((uVar7 & 2) == 0) {
            iVar11 = ((param_3 & 2) >> 1) + 3;
          }
          lVar17 = Aska::RenderStateManager::Get(int)(uVar12,iVar11);
          *plVar16 = lVar17;
          if (lVar17 == 0) {
            return 0;
          }
          Aska::RenderState::Reset()(lVar17);
          if ((uVar7 >> 1 & 1) == 0) goto code_r0x022bd1cc;
code_r0x022bd1a4:
          uVar1 = (ulong)*(byte *)(lVar3 + 0x1b) + (ulong)*(byte *)(lVar3 + 0x247);
          uVar19 = (uint)uVar1;
          if (uVar19 != 0) {
            if (uVar19 < 4) {
              lVar13 = 0;
code_r0x022bd230:
              lVar15 = lVar3 + lVar13 * 0x20;
              lVar14 = uVar1 - lVar13;
              plVar16 = alStack_f0 + lVar13;
              do {
                lVar15 = lVar15 + 0x20;
                *plVar16 = lVar15;
                lVar14 = lVar14 + -1;
                plVar16 = plVar16 + 1;
              } while (lVar14 != 0);
            }
            else {
              lVar13 = uVar1 - (uVar19 & 3);
              lVar15 = lVar13;
              plVar16 = alStack_f0 + 2;
              lVar14 = lVar9;
              lVar24 = lVar10;
              if (lVar13 == 0) goto code_r0x022bd230;
              do {
                lVar25 = lVar3 + lVar14 * 0x20;
                lVar26 = lVar3 + lVar24 * 0x20;
                lVar15 = lVar15 + -4;
                plVar16[-1] = lVar26 + 0x20;
                plVar16[-2] = lVar25 + 0x20;
                plVar16[1] = lVar26 + 0x60;
                *plVar16 = lVar25 + 0x60;
                plVar16 = plVar16 + 4;
                lVar14 = lVar14 + 4;
                lVar24 = lVar24 + 4;
              } while (lVar15 != 0);
              if ((uVar1 & 3) != 0) goto code_r0x022bd230;
            }
            if (uVar19 != 0) {
              uVar18 = 0;
              puVar20 = auStack_2e8;
              do {
                lVar15 = alStack_f0[uVar18];
                uVar22 = *puVar20;
                if (uVar22 != *(ulong *)(lVar15 + 8)) {
                  bVar5 = *(byte *)(lVar15 + 0xf);
                  if (*(byte *)((long)puVar20 + 7) != bVar5) {
                    if ((char)bVar5 < '\0') {
                      Aska::RenderState::SetTextureSamplingWrapModeU(int, Aska::TexWrap::Mode)(lVar17,uVar18 & 0xffffffff,bVar5 & 0xf);
                      Aska::RenderState::SetTextureSamplingWrapModeV(int, Aska::TexWrap::Mode)(lVar17,uVar18 & 0xffffffff,*(byte *)(lVar15 + 0xf) >> 4 & 7);
                    }
                    else {
                      Aska::RenderState::SetTextureSamplingWrapMode(int, Aska::TexWrap::Mode)(lVar17,uVar18 & 0xffffffff);
                    }
                  }
                  if (*(char *)((long)puVar20 + 6) != *(char *)(lVar15 + 0xe)) {
                    Aska::RenderState::SetTextureSamplingMipmapFilter(int, Aska::TexSamp::MipFilter)(lVar17,uVar18 & 0xffffffff,0);
                    Aska::RenderState::SetTextureSamplingFilter(int, Aska::TexSamp::Filter)(lVar17,uVar18 & 0xffffffff,*(byte *)(lVar15 + 0xe) & 7);
                  }
                  uVar7 = *(ushort *)((long)puVar20 + 4);
                  iVar11 = (int)*(short *)(lVar15 + 0xc) >> 6;
                  if ((int)((uint)uVar7 << 0x10) >> 0x16 != iVar11) {
                    if ((*(int *)PTR__ZN4Aska10RenderPass22m_iSpecialLODBiasShiftE_02cbfc78 != 0) &&
                       ((*(byte *)(lVar15 + 10) & 1) == 0)) {
                      iVar11 = iVar11 + *(int *)
                                         PTR__ZN4Aska10RenderPass22m_iSpecialLODBiasShiftE_02cbfc78
                                        * 0x20;
                      if (iVar11 < -0x1ff) {
                        iVar11 = -0x200;
                      }
                      if (0x1ff < iVar11) {
                        iVar11 = 0x200;
                      }
                    }
                    Aska::RenderState::SetTextureSamplingMipmapLODBias(int, int)(lVar17,uVar18 & 0xffffffff,iVar11);
                  }
                  if ((uVar7 & 0x3f) != 0) {
                    Aska::RenderState::SetTextureSamplingTrilinearClamp(int, unsigned int)(lVar17,uVar18 & 0xffffffff,0);
                  }
                  if (*(char *)((long)puVar20 + 1) != '\x01') {
                    Aska::RenderState::SetTextureSamplingMaxAnisotropic(int, unsigned int)(lVar17,uVar18 & 0xffffffff,1);
                  }
                  if ((uVar22 & 0xff) != 0) {
                    Aska::RenderState::SetTextureSamplingAnisotropicBias(int, int)(lVar17,uVar18 & 0xffffffff,0);
                  }
                  *puVar20 = *(ulong *)(lVar15 + 8);
                }
                uVar18 = uVar18 + 1;
                puVar20 = puVar20 + 4;
              } while (uVar1 != uVar18);
            }
          }
          Aska::RenderState::SetAlphaTestFunction(int, int)(lVar17,2,*(undefined1 *)(lVar3 + 0x231));
          pfVar23 = (float *)PTR__ZN4Aska13ShadowManager25m_fMasterShadowBiasOffsetE_02cbefc0;
        }
        else {
          if ((uVar7 >> 1 & 1) != 0) {
            if (*(int *)(lVar17 + 0x10) != 0x90) {
              Aska::RenderState::Release()(lVar17);
              lVar17 = Aska::RenderStateManager::Get(int)(uVar12,0x90);
              *plVar16 = lVar17;
              if (lVar17 == 0) {
                return 0;
              }
            }
            Aska::RenderState::Reset()(lVar17);
            goto code_r0x022bd1a4;
          }
          Aska::RenderState::Reset()(lVar17);
code_r0x022bd1cc:
          if ((param_3 & 2) != 0) {
            Aska::RenderState::EnableAlphaBlend(bool)(lVar17,0);
          }
        }
        uVar6 = puVar2[bVar4];
        Aska::RenderState::SetDepthBias(float, float)((*(float *)(param_2 + 0xbc) + *pfVar23) * fVar8,
                        -(*(float *)(param_2 + 0xc0) *
                         *(float *)PTR__ZN4Aska13ShadowManager24m_fMasterShadowBiasScaleE_02cbc450),
                        lVar17);
        Aska::RenderState::SetCullMode(int)(lVar17,uVar6);
        uVar7 = *(ushort *)(lVar3 + 0x245);
        if (((uVar7 >> 5 & 1) != 0) || (*(short *)(lVar3 + 0x238) != 0 || (uVar7 & 8) != 0)) {
          memset(auStack_2f0,0xff,0x200);
        }
      }
      lVar21 = lVar21 + 1;
    } while (lVar21 < (long)(ulong)*(byte *)(param_1 + 0x26));
  }
  *(ushort *)(param_1 + 0x2f) = *(ushort *)(param_1 + 0x2f) | 0x40;
  return 1;
}

// ==== Aska::RenderPass::PrepareMultiDrawState(Aska::AofHandler*)
// vaddr 0x21bd484 | ghidra 0x22bd484 | size 24 | symbol _ZN4Aska10RenderPass21PrepareMultiDrawStateEPNS_10AofHandlerE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10RenderPass21PrepareMultiDrawStateEPNS_10AofHandlerE(long param_1)

{
  *(ushort *)(param_1 + 0x2f) = *(ushort *)(param_1 + 0x2f) | 0x40;
  return 1;
}

// ==== Aska::RenderPass::SetObjectState(Aska::AofObjectRenderState*)
// vaddr 0x21bd49c | ghidra 0x22bd49c | size 152 | symbol _ZN4Aska10RenderPass14SetObjectStateEPNS_20AofObjectRenderStateE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10RenderPass14SetObjectStateEPNS_20AofObjectRenderStateE(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  long lVar3;
  
  if (*(undefined8 **)(param_2 + 0x10) == (undefined8 *)0x0) {
    if (*(char *)(param_1 + 0x26) != '\0') {
      lVar2 = 0;
      lVar3 = 0x50;
      do {
        lVar2 = lVar2 + 1;
        *(undefined8 *)(*(long *)(param_1 + 8) + lVar3) = 0;
        lVar3 = lVar3 + 0x1b8;
      } while (lVar2 < (long)(ulong)*(byte *)(param_1 + 0x26));
    }
  }
  else if ((*(char *)(param_1 + 0x26) != '\0') &&
          (*(undefined8 *)(*(long *)(param_1 + 8) + 0x50) =
                *(undefined8 *)**(undefined8 **)(param_2 + 0x10), 1 < *(byte *)(param_1 + 0x26))) {
    lVar2 = 1;
    lVar3 = 0x208;
    do {
      lVar1 = lVar2 * 8;
      lVar2 = lVar2 + 1;
      *(undefined8 *)(*(long *)(param_1 + 8) + lVar3) =
           *(undefined8 *)(**(long **)(param_2 + 0x10) + lVar1);
      lVar3 = lVar3 + 0x1b8;
    } while (lVar2 < (long)(ulong)*(byte *)(param_1 + 0x26));
  }
  *(ushort *)(param_1 + 0x2f) = *(ushort *)(param_1 + 0x2f) | 0x80;
  return;
}

// ==== Aska::RenderPass::UpdateTexture(Aska::MaterialList*, Aska::TextureModifierManager*, Aska::RENDERINFO const*, int, bool)
// vaddr 0x21bd534 | ghidra 0x22bd534 | size 1428 | symbol _ZN4Aska10RenderPass13UpdateTextureEPNS_12MaterialListEPNS_22TextureModifierManagerEPKNS_10RENDERINFOEib | lib libSOA-3.7.0.so | 2026-10-04
byte _ZN4Aska10RenderPass13UpdateTextureEPNS_12MaterialListEPNS_22TextureModifierManagerEPKNS_10RENDERINFOEib
               (long param_1,long param_2,long param_3,undefined8 param_4,undefined4 param_5)

{
  uint uVar1;
  long lVar2;
  byte bVar3;
  byte bVar4;
  bool bVar5;
  long lVar6;
  long lVar7;
  undefined1 *puVar8;
  int *piVar9;
  uint3 *puVar10;
  long lVar11;
  long lVar12;
  ulong uVar13;
  long lVar14;
  uint *puVar15;
  long lVar16;
  byte bVar17;
  long lVar18;
  long *plVar19;
  long *plVar20;
  
  *(ushort *)(param_1 + 0x2f) = *(ushort *)(param_1 + 0x2f) & 0xbfff;
  if (*(char *)(param_1 + 0x26) == '\0') {
    bVar17 = 0;
  }
  else {
    lVar18 = 0;
    bVar17 = 0;
    do {
      lVar12 = *(long *)(param_1 + 8);
      lVar14 = lVar12 + lVar18 * 0x1b8;
      lVar2 = 0;
      if (*(long *)(param_2 + 0x18) != 0) {
        lVar2 = *(long *)(param_2 + 0x18) + lVar18 * 0x2a0 + 0x10;
      }
      bVar3 = *(byte *)(lVar2 + 0x1b);
      bVar4 = *(byte *)(lVar2 + 0x247);
      puVar15 = (uint *)(lVar14 + 0x5c);
      *puVar15 = 0;
      lVar16 = (ulong)bVar3 + (ulong)bVar4;
      puVar8 = (undefined1 *)(lVar14 + 0x59);
      *puVar8 = (char)lVar16;
      if (*(int *)(param_3 + 0x20) < 1) {
        if ((int)lVar16 != 0) {
          lVar14 = 0;
          do {
            lVar6 = lVar2 + lVar14 * 0x20;
            plVar19 = (long *)(lVar6 + 0x20);
            lVar7 = *plVar19;
            if (lVar7 == 0) {
              lVar6 = 0;
            }
            else {
              plVar20 = (long *)(lVar6 + 0x30);
              lVar6 = *plVar20;
              if (lVar6 == 0) {
                lVar6 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
                lVar11 = lVar6 + 0xb0;
                Aska::CriticalSection::Enter() const(lVar11);
                lVar6 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar6,lVar7,1);
                Aska::CriticalSection::Leave() const(lVar11);
                *plVar20 = lVar6;
                lVar7 = *plVar19;
              }
            }
            if (0 < *(int *)PTR__ZN4Aska10RenderPass26m_numFrameTextureRegistersE_02cc3af8) {
              lVar11 = 0;
              plVar19 = (long *)PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8;
              do {
                if (*plVar19 == lVar7) goto code_r0x022bd898;
                lVar11 = lVar11 + 1;
                plVar19 = plVar19 + 3;
              } while (lVar11 < *(int *)
                                 PTR__ZN4Aska10RenderPass26m_numFrameTextureRegistersE_02cc3af8);
            }
            if ((lVar7 == 0x737a407a00000000) || (lVar7 == 0x7274406300000000)) {
code_r0x022bd898:
              bVar5 = false;
              *puVar15 = *puVar15 | 1 << (ulong)((uint)lVar14 & 0x1f);
            }
            else {
              if (lVar6 == 0) {
                lVar6 = Aska::ObjectManager::GetNoTexture() const(*(undefined8 *)
                                         PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688);
              }
              plVar19 = (long *)(lVar12 + lVar18 * 0x1b8 + lVar14 * 8 + 0x60);
              bVar5 = *plVar19 != lVar6;
              if (bVar5) {
                *plVar19 = lVar6;
              }
              piVar9 = (int *)(lVar12 + lVar18 * 0x1b8 + lVar14 * 4 + 0xe0);
              if (*piVar9 != *(int *)(lVar6 + 0x7c)) {
                bVar5 = true;
                *piVar9 = *(int *)(lVar6 + 0x7c);
              }
            }
            lVar14 = lVar14 + 1;
            bVar17 = bVar17 | bVar5;
          } while (lVar14 != lVar16);
        }
      }
      else if ((int)lVar16 != 0) {
        lVar14 = 0;
        do {
          plVar19 = (long *)(lVar2 + lVar14 * 0x20 + 0x20);
          lVar6 = Aska::TextureModifierManager::GetTexture(unsigned long, Aska::RENDERINFO const*, int)(param_3,*plVar19,param_4,param_5);
          if (lVar6 == 0) {
            lVar7 = *plVar19;
            if (lVar7 != 0) {
              plVar20 = (long *)(lVar2 + lVar14 * 0x20 + 0x30);
              lVar6 = *plVar20;
              if (lVar6 == 0) {
                lVar6 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
                lVar11 = lVar6 + 0xb0;
                Aska::CriticalSection::Enter() const(lVar11);
                lVar6 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar6,lVar7,1);
                Aska::CriticalSection::Leave() const(lVar11);
                *plVar20 = lVar6;
              }
              goto code_r0x022bd6d8;
            }
            lVar7 = 0;
            lVar6 = 0;
          }
          else {
code_r0x022bd6d8:
            lVar7 = *plVar19;
          }
          if (0 < *(int *)PTR__ZN4Aska10RenderPass26m_numFrameTextureRegistersE_02cc3af8) {
            lVar11 = 0;
            plVar19 = (long *)PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8;
            do {
              if (*plVar19 == lVar7) goto code_r0x022bd738;
              lVar11 = lVar11 + 1;
              plVar19 = plVar19 + 3;
            } while (lVar11 < *(int *)PTR__ZN4Aska10RenderPass26m_numFrameTextureRegistersE_02cc3af8
                    );
          }
          if ((lVar7 == 0x737a407a00000000) || (lVar7 == 0x7274406300000000)) {
code_r0x022bd738:
            bVar5 = false;
            *puVar15 = *puVar15 | 1 << (ulong)((uint)lVar14 & 0x1f);
          }
          else {
            if (lVar6 == 0) {
              lVar6 = Aska::ObjectManager::GetNoTexture() const(*(undefined8 *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688
                                     );
            }
            plVar19 = (long *)(lVar12 + lVar18 * 0x1b8 + lVar14 * 8 + 0x60);
            bVar5 = *plVar19 != lVar6;
            if (bVar5) {
              *plVar19 = lVar6;
            }
            piVar9 = (int *)(lVar12 + lVar18 * 0x1b8 + lVar14 * 4 + 0xe0);
            if (*piVar9 != *(int *)(lVar6 + 0x7c)) {
              bVar5 = true;
              *piVar9 = *(int *)(lVar6 + 0x7c);
            }
          }
          lVar14 = lVar14 + 1;
          bVar17 = bVar17 | bVar5;
        } while (lVar14 != lVar16);
      }
      bVar3 = *(byte *)(param_1 + 0x25);
      if (bVar3 != 0) {
        lVar2 = (ulong)*(byte *)(lVar2 + 0x1b) + (ulong)*(byte *)(lVar2 + 0x247);
        uVar1 = (int)lVar2 + (uint)bVar3;
        if (uVar1 < 0x11) {
          uVar13 = 0;
          do {
            lVar14 = param_1 + uVar13 * 0x20;
            plVar19 = (long *)(lVar14 + 0x58);
            lVar16 = *plVar19;
            if (lVar16 == 0) {
              lVar14 = 0;
            }
            else {
              plVar20 = (long *)(lVar14 + 0x68);
              lVar14 = *plVar20;
              if (lVar14 == 0) {
                lVar14 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
                lVar6 = lVar14 + 0xb0;
                Aska::CriticalSection::Enter() const(lVar6);
                lVar14 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar14,lVar16,1);
                Aska::CriticalSection::Leave() const(lVar6);
                *plVar20 = lVar14;
                lVar16 = *plVar19;
              }
            }
            lVar6 = uVar13 + lVar2;
            if (0 < *(int *)PTR__ZN4Aska10RenderPass26m_numFrameTextureRegistersE_02cc3af8) {
              lVar7 = 0;
              plVar19 = (long *)PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8;
              do {
                if (*plVar19 == lVar16) goto code_r0x022bda20;
                lVar7 = lVar7 + 1;
                plVar19 = plVar19 + 3;
              } while (lVar7 < *(int *)
                                PTR__ZN4Aska10RenderPass26m_numFrameTextureRegistersE_02cc3af8);
            }
            if ((lVar16 == 0x737a407a00000000) || (lVar16 == 0x7274406300000000)) {
code_r0x022bda20:
              bVar5 = false;
              *puVar15 = *puVar15 | 1 << (ulong)((uint)lVar6 & 0x1f);
            }
            else {
              if (lVar14 == 0) {
                lVar14 = Aska::ObjectManager::GetNoTexture() const(*(undefined8 *)
                                          PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688);
              }
              plVar19 = (long *)(lVar12 + lVar18 * 0x1b8 + lVar6 * 8 + 0x60);
              bVar5 = *plVar19 != lVar14;
              if (bVar5) {
                *plVar19 = lVar14;
              }
              piVar9 = (int *)(lVar12 + lVar18 * 0x1b8 + lVar6 * 4 + 0xe0);
              if (*piVar9 != *(int *)(lVar14 + 0x7c)) {
                bVar5 = true;
                *piVar9 = *(int *)(lVar14 + 0x7c);
              }
            }
            uVar13 = uVar13 + 1;
            bVar17 = bVar17 | bVar5;
          } while (uVar13 != bVar3);
          *puVar8 = (char)uVar1;
        }
      }
      uVar1 = *puVar15;
      puVar10 = (uint3 *)(param_1 + 0x2f);
      lVar18 = lVar18 + 1;
      *(undefined1 *)(param_1 + 0x31) = *(undefined1 *)(param_1 + 0x31);
      *(ushort *)puVar10 =
           (ushort)*puVar10 & 0x8000 |
           *(ushort *)puVar10 & 0x3fff | (ushort)((*puVar10 >> 0xe & 1 | (uint)(uVar1 != 0)) << 0xe)
      ;
    } while (lVar18 < (long)(ulong)*(byte *)(param_1 + 0x26));
  }
  return bVar17;
}

// ==== Aska::RenderPass::UpdateMaterial(Aska::MaterialList*)
// vaddr 0x21bdac8 | ghidra 0x22bdac8 | size 156 | symbol _ZN4Aska10RenderPass14UpdateMaterialEPNS_12MaterialListE | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska10RenderPass14UpdateMaterialEPNS_12MaterialListE(long param_1,long param_2)

{
  long lVar1;
  byte bVar2;
  long lVar3;
  undefined4 uVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  
  uVar6 = (ulong)*(byte *)(param_1 + 0x26);
  if (*(byte *)(param_1 + 0x26) != 0) {
    lVar3 = 0;
    uVar4 = 0;
    lVar5 = 0x10;
    lVar7 = 0x58;
    do {
      lVar1 = 0;
      if (*(long *)(param_2 + 0x18) != 0) {
        lVar1 = *(long *)(param_2 + 0x18) + lVar5;
      }
      bVar2 = *(byte *)(*(long *)(param_1 + 8) + lVar7);
      if ((bool)(bVar2 >> 2 & 1) != ((*(ushort *)(lVar1 + 0x245) & 0x2000) == 0)) {
        *(byte *)(*(long *)(param_1 + 8) + lVar7) =
             (bVar2 & 0xfb | (byte)((*(ushort *)(lVar1 + 0x245) & 0x2000) >> 0xb)) ^ 4;
        uVar6 = (ulong)*(byte *)(param_1 + 0x26);
        uVar4 = 1;
      }
      lVar3 = lVar3 + 1;
      lVar5 = lVar5 + 0x2a0;
      lVar7 = lVar7 + 0x1b8;
    } while (lVar3 < (long)uVar6);
    return uVar4;
  }
  return 0;
}

// ==== Aska::RenderPass::ClearTexture()
// vaddr 0x21bdb64 | ghidra 0x22bdb64 | size 92 | symbol _ZN4Aska10RenderPass12ClearTextureEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska10RenderPass12ClearTextureEv(long param_1)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  undefined4 uVar5;
  
  uVar2 = (ulong)*(byte *)(param_1 + 0x26);
  if (*(byte *)(param_1 + 0x26) != 0) {
    lVar3 = 0;
    lVar4 = 0;
    uVar5 = 0;
    do {
      lVar1 = *(long *)(param_1 + 8) + lVar3;
      if (*(char *)(lVar1 + 0x59) != '\0') {
        *(undefined1 *)(lVar1 + 0x59) = 0;
        *(undefined4 *)(lVar1 + 0x5c) = 0;
        uVar2 = (ulong)*(byte *)(param_1 + 0x26);
        uVar5 = 1;
      }
      lVar4 = lVar4 + 1;
      lVar3 = lVar3 + 0x1b8;
    } while (lVar4 < (long)uVar2);
    return uVar5;
  }
  return 0;
}

// ==== Aska::RenderPass::UpdateTextureShadowPass(Aska::MaterialList*, Aska::TextureModifierManager*, Aska::RENDERINFO const*, int)
// vaddr 0x21bdbc0 | ghidra 0x22bdbc0 | size 1020 | symbol _ZN4Aska10RenderPass23UpdateTextureShadowPassEPNS_12MaterialListEPNS_22TextureModifierManagerEPKNS_10RENDERINFOEi | lib libSOA-3.7.0.so | 2026-10-04
byte _ZN4Aska10RenderPass23UpdateTextureShadowPassEPNS_12MaterialListEPNS_22TextureModifierManagerEPKNS_10RENDERINFOEi
               (long param_1,long param_2,long param_3,undefined8 param_4,undefined4 param_5)

{
  long lVar1;
  long lVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  bool bVar6;
  long lVar7;
  ulong uVar8;
  uint uVar9;
  long lVar10;
  int *piVar11;
  uint3 *puVar12;
  long lVar13;
  uint *puVar14;
  long lVar15;
  ulong *puVar16;
  byte bVar17;
  long lVar18;
  long *plVar19;
  
  uVar5 = *(ushort *)(param_1 + 0x2f) & 0xffffbfff;
  uVar9 = uVar5 | (uint)*(byte *)(param_1 + 0x31) << 0x10;
  *(ushort *)(param_1 + 0x2f) = (ushort)uVar5;
  if (*(char *)(param_1 + 0x26) == '\0') {
    bVar17 = 0;
  }
  else {
    lVar18 = 0;
    bVar17 = 0;
    do {
      lVar15 = *(long *)(param_1 + 8);
      lVar13 = lVar15 + lVar18 * 0x1b8;
      lVar2 = 0;
      if (*(long *)(param_2 + 0x18) != 0) {
        lVar2 = *(long *)(param_2 + 0x18) + lVar18 * 0x2a0 + 0x10;
      }
      bVar3 = *(byte *)(lVar2 + 0x1b);
      bVar4 = *(byte *)(lVar2 + 0x247);
      puVar14 = (uint *)(lVar13 + 0x5c);
      *puVar14 = 0;
      lVar1 = (ulong)bVar3 + (ulong)bVar4;
      *(char *)(lVar13 + 0x59) = (char)lVar1;
      if (*(int *)(param_3 + 0x20) < 1) {
        if ((int)lVar1 != 0) {
          lVar13 = 0;
          do {
            uVar8 = *(ulong *)(lVar2 + lVar13 * 0x20 + 0x20);
            if ((uVar8 & 0xff0000000000) == 0x400000000000) {
              lVar7 = Aska::ObjectManager::GetNoTexture() const(*(undefined8 *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688
                                     );
            }
            else if (uVar8 == 0) {
              lVar7 = 0;
            }
            else {
              plVar19 = (long *)(lVar2 + lVar13 * 0x20 + 0x30);
              lVar7 = *plVar19;
              if (lVar7 == 0) {
                lVar7 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
                lVar10 = lVar7 + 0xb0;
                Aska::CriticalSection::Enter() const(lVar10);
                lVar7 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar7,uVar8,1);
                Aska::CriticalSection::Leave() const(lVar10);
                *plVar19 = lVar7;
              }
            }
            if (0 < *(int *)PTR__ZN4Aska10RenderPass26m_numFrameTextureRegistersE_02cc3af8) {
              lVar10 = 0;
              plVar19 = (long *)PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8;
              do {
                if (*plVar19 == 0) {
                  bVar6 = false;
                  *puVar14 = *puVar14 | 1 << (ulong)((uint)lVar13 & 0x1f);
                  goto code_r0x022bdf2c;
                }
                lVar10 = lVar10 + 1;
                plVar19 = plVar19 + 3;
              } while (lVar10 < *(int *)
                                 PTR__ZN4Aska10RenderPass26m_numFrameTextureRegistersE_02cc3af8);
            }
            if (lVar7 == 0) {
              lVar7 = Aska::ObjectManager::GetNoTexture() const(*(undefined8 *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688
                                     );
            }
            plVar19 = (long *)(lVar15 + lVar18 * 0x1b8 + lVar13 * 8 + 0x60);
            bVar6 = *plVar19 != lVar7;
            if (bVar6) {
              *plVar19 = lVar7;
            }
            piVar11 = (int *)(lVar15 + lVar18 * 0x1b8 + lVar13 * 4 + 0xe0);
            if (*piVar11 != *(int *)(lVar7 + 0x7c)) {
              bVar6 = true;
              *piVar11 = *(int *)(lVar7 + 0x7c);
            }
code_r0x022bdf2c:
            lVar13 = lVar13 + 1;
            bVar17 = bVar17 | bVar6;
          } while (lVar13 != lVar1);
        }
      }
      else if ((int)lVar1 != 0) {
        lVar13 = 0;
        do {
          puVar16 = (ulong *)(lVar2 + lVar13 * 0x20 + 0x20);
          uVar8 = *puVar16;
          if ((uVar8 & 0xff0000000000) == 0x400000000000) {
            lVar7 = Aska::ObjectManager::GetNoTexture() const(*(undefined8 *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688);
          }
          else {
            lVar7 = Aska::TextureModifierManager::GetTexture(unsigned long, Aska::RENDERINFO const*, int)(param_3,uVar8,param_4,param_5);
          }
          if (lVar7 == 0) {
            uVar8 = *puVar16;
            if (uVar8 == 0) {
              lVar7 = 0;
            }
            else {
              plVar19 = (long *)(lVar2 + lVar13 * 0x20 + 0x30);
              lVar7 = *plVar19;
              if (lVar7 == 0) {
                lVar7 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
                lVar10 = lVar7 + 0xb0;
                Aska::CriticalSection::Enter() const(lVar10);
                lVar7 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar7,uVar8,1);
                Aska::CriticalSection::Leave() const(lVar10);
                *plVar19 = lVar7;
              }
            }
          }
          if (0 < *(int *)PTR__ZN4Aska10RenderPass26m_numFrameTextureRegistersE_02cc3af8) {
            lVar10 = 0;
            plVar19 = (long *)PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8;
            do {
              if (*plVar19 == 0) {
                bVar6 = false;
                *puVar14 = *puVar14 | 1 << (ulong)((uint)lVar13 & 0x1f);
                goto code_r0x022bddd0;
              }
              lVar10 = lVar10 + 1;
              plVar19 = plVar19 + 3;
            } while (lVar10 < *(int *)PTR__ZN4Aska10RenderPass26m_numFrameTextureRegistersE_02cc3af8
                    );
          }
          if (lVar7 == 0) {
            lVar7 = Aska::ObjectManager::GetNoTexture() const(*(undefined8 *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688);
          }
          plVar19 = (long *)(lVar15 + lVar18 * 0x1b8 + lVar13 * 8 + 0x60);
          bVar6 = *plVar19 != lVar7;
          if (bVar6) {
            *plVar19 = lVar7;
          }
          piVar11 = (int *)(lVar15 + lVar18 * 0x1b8 + lVar13 * 4 + 0xe0);
          if (*piVar11 != *(int *)(lVar7 + 0x7c)) {
            bVar6 = true;
            *piVar11 = *(int *)(lVar7 + 0x7c);
          }
code_r0x022bddd0:
          lVar13 = lVar13 + 1;
          bVar17 = bVar17 | bVar6;
        } while (lVar13 != lVar1);
      }
      uVar9 = *puVar14;
      lVar18 = lVar18 + 1;
      puVar12 = (uint3 *)(param_1 + 0x2f);
      *(undefined1 *)(param_1 + 0x31) = *(undefined1 *)(param_1 + 0x31);
      uVar9 = *puVar12 & 0xffff8000 |
              *(ushort *)puVar12 & 0x3fff | (*puVar12 >> 0xe & 1 | (uint)(uVar9 != 0)) << 0xe;
      *(ushort *)puVar12 = (ushort)uVar9;
    } while (lVar18 < (long)(ulong)*(byte *)(param_1 + 0x26));
  }
  *(short *)(param_1 + 0x2f) = (short)uVar9;
  *(byte *)(param_1 + 0x31) = (byte)(uVar9 >> 0x10) | 4;
  return bVar17;
}

// ==== Aska::RenderPass::UpdateFrameTexturePointers(Aska::MaterialList*, Aska::RENDERINFO const*, int)
// vaddr 0x21bdfbc | ghidra 0x22bdfbc | size 452 | symbol _ZN4Aska10RenderPass26UpdateFrameTexturePointersEPNS_12MaterialListEPKNS_10RENDERINFOEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10RenderPass26UpdateFrameTexturePointersEPNS_12MaterialListEPKNS_10RENDERINFOEi
               (long param_1,long param_2,short *param_3)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  short sVar4;
  undefined4 uVar5;
  uint uVar6;
  short sVar7;
  ulong uVar8;
  long *plVar9;
  undefined8 *puVar10;
  long lVar11;
  uint uVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  
  uVar8 = (ulong)*(byte *)(param_1 + 0x26);
  if (*(byte *)(param_1 + 0x26) != 0) {
    sVar4 = *param_3;
    sVar7 = param_3[1];
    lVar14 = 0;
    do {
      lVar15 = *(long *)(param_1 + 8);
      uVar12 = *(uint *)(lVar15 + lVar14 * 0x1b8 + 0x5c);
      lVar3 = 0;
      if (*(long *)(param_2 + 0x18) != 0) {
        lVar3 = *(long *)(param_2 + 0x18) + lVar14 * 0x2a0 + 0x10;
      }
      if (uVar12 != 0) {
        uVar1 = (uint)*(byte *)(lVar3 + 0x1b) + (uint)*(byte *)(lVar3 + 0x247);
        do {
          uVar6 = 0x1f - (int)LZCOUNT(uVar12);
          uVar2 = uVar6 & 0xffff;
          if (uVar2 < uVar1) {
            plVar9 = (long *)(lVar3 + (ulong)uVar2 * 0x20 + 0x20);
          }
          else {
            plVar9 = (long *)(param_1 + (long)(int)(uVar2 - uVar1) * 0x20 + 0x58);
          }
          lVar13 = *plVar9;
          if (0 < *(int *)PTR__ZN4Aska10RenderPass26m_numFrameTextureRegistersE_02cc3af8) {
            lVar11 = 0;
            puVar10 = (undefined8 *)
                      (PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8 + 8);
            do {
              if (puVar10[-1] == lVar13) {
                lVar11 = (*(code *)*puVar10)(lVar13,*(undefined4 *)(puVar10 + 1),(int)sVar4,
                                             (int)(char)sVar7);
                if (lVar11 != 0) goto code_r0x022be124;
                break;
              }
              lVar11 = lVar11 + 1;
              puVar10 = puVar10 + 3;
            } while (lVar11 < *(int *)PTR__ZN4Aska10RenderPass26m_numFrameTextureRegistersE_02cc3af8
                    );
          }
          if (lVar13 == 0x7274406300000000) {
            uVar5 = 0x66744061;
code_r0x022be0fc:
            lVar11 = Aska::FrameTextureCoordinator::GetTexture(unsigned int, int, int)(PTR__ZN4Aska20FrameTextureEntities13m_coordinatorE_02cc44e0,
                                     uVar5,(int)sVar4,(int)(char)sVar7);
            if (lVar11 == 0) goto code_r0x022be114;
          }
          else {
            if (lVar13 == 0x737a407a00000000) {
              uVar5 = 0x737a4061;
              goto code_r0x022be0fc;
            }
code_r0x022be114:
            lVar11 = Aska::ObjectManager::GetNoTexture() const(*(undefined8 *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688)
            ;
          }
code_r0x022be124:
          lVar13 = lVar15 + lVar14 * 0x1b8;
          *(long *)(lVar13 + (ulong)uVar2 * 8 + 0x60) = lVar11;
          uVar12 = uVar12 & (1 << (ulong)(uVar6 & 0x1f) ^ 0xffffffffU);
          *(undefined4 *)(lVar13 + (ulong)uVar2 * 4 + 0xe0) = *(undefined4 *)(lVar11 + 0x7c);
        } while (uVar12 != 0);
        uVar8 = (ulong)*(byte *)(param_1 + 0x26);
      }
      lVar14 = lVar14 + 1;
    } while (lVar14 < (long)uVar8);
  }
  return;
}

// ==== Aska::RenderPass::TickShader()
// vaddr 0x21be180 | ghidra 0x22be180 | size 4 | symbol _ZN4Aska10RenderPass10TickShaderEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10RenderPass10TickShaderEv(void)

{
  return;
}

// ==== Aska::RenderPass::GetVertexPassNum() const
// vaddr 0x21be184 | ghidra 0x22be184 | size 164 | symbol _ZNK4Aska10RenderPass16GetVertexPassNumEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK4Aska10RenderPass16GetVertexPassNumEv(long param_1)

{
  byte *pbVar1;
  byte bVar2;
  ulong uVar3;
  long lVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  long lVar8;
  long lVar9;
  
  bVar2 = *(byte *)(param_1 + 0x26);
  uVar3 = (ulong)bVar2;
  if (uVar3 == 0) {
    return 0;
  }
  if (bVar2 == 1) {
    lVar4 = 0;
  }
  else {
    lVar4 = uVar3 - (uVar3 & 1);
    if (lVar4 != 0) {
      iVar6 = 0;
      iVar7 = 0;
      lVar8 = lVar4;
      lVar9 = *(long *)(param_1 + 8);
      do {
        pbVar5 = (byte *)(lVar9 + 0x58);
        pbVar1 = (byte *)(lVar9 + 0x210);
        lVar8 = lVar8 + -2;
        lVar9 = lVar9 + 0x370;
        iVar6 = iVar6 + (*pbVar5 >> 1 & 1);
        iVar7 = iVar7 + (*pbVar1 >> 1 & 1);
      } while (lVar8 != 0);
      iVar7 = iVar7 + iVar6;
      if ((bVar2 & 1) == 0) {
        return iVar7;
      }
      goto code_r0x022be1fc;
    }
  }
  iVar7 = 0;
code_r0x022be1fc:
  pbVar5 = (byte *)(*(long *)(param_1 + 8) + lVar4 * 0x1b8 + 0x58);
  do {
    bVar2 = *pbVar5;
    lVar4 = lVar4 + 1;
    pbVar5 = pbVar5 + 0x1b8;
    iVar7 = iVar7 + (bVar2 >> 1 & 1);
  } while (lVar4 < (long)uVar3);
  return iVar7;
}

// ==== Aska::RenderPass::RegisterFrameTexture(Aska::FrameTextureEntities*, Aska::Texture* (*)(unsigned long, unsigned int, unsigned int, unsigned int))
// vaddr 0x21be258 | ghidra 0x22be258 | size 848 | symbol _ZN4Aska10RenderPass20RegisterFrameTextureEPNS_20FrameTextureEntitiesEPFPNS_7TextureEmjjjE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10RenderPass20RegisterFrameTextureEPNS_20FrameTextureEntitiesEPFPNS_7TextureEmjjjE
               (long param_1,undefined *param_2)

{
  undefined4 uVar1;
  undefined *puVar2;
  bool bVar3;
  long lVar4;
  long *plVar5;
  long lVar6;
  long lVar7;
  
  puVar2 = PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8;
  lVar4 = *(long *)(param_1 + 0x458);
  uVar1 = *(undefined4 *)(param_1 + 0x1de8);
  lVar6 = 0;
  lVar7 = *(long *)PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8;
  bVar3 = lVar7 == 0;
  plVar5 = (long *)PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8;
  if ((lVar7 != lVar4) && (lVar7 != 0)) {
    plVar5 = (long *)(PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8 + 0x18);
    lVar7 = *plVar5;
    lVar6 = 1;
    bVar3 = lVar7 == 0;
    if ((lVar7 != lVar4) && (lVar7 != 0)) {
      plVar5 = (long *)(PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8 + 0x30);
      lVar7 = *plVar5;
      lVar6 = 2;
      bVar3 = lVar7 == 0;
      if ((lVar7 != lVar4) && (lVar7 != 0)) {
        plVar5 = (long *)(PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8 + 0x48);
        lVar7 = *plVar5;
        lVar6 = 3;
        bVar3 = lVar7 == 0;
        if ((lVar7 != lVar4) && (lVar7 != 0)) {
          plVar5 = (long *)(PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8 + 0x60);
          lVar7 = *plVar5;
          lVar6 = 4;
          bVar3 = lVar7 == 0;
          if ((lVar7 != lVar4) && (lVar7 != 0)) {
            plVar5 = (long *)(PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8 + 0x78);
            lVar7 = *plVar5;
            lVar6 = 5;
            bVar3 = lVar7 == 0;
            if ((lVar7 != lVar4) && (lVar7 != 0)) {
              plVar5 = (long *)(PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8 + 0x90);
              lVar7 = *plVar5;
              lVar6 = 6;
              bVar3 = lVar7 == 0;
              if ((lVar7 != lVar4) && (lVar7 != 0)) {
                plVar5 = (long *)(PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8 + 0xa8
                                 );
                lVar7 = *plVar5;
                lVar6 = 7;
                bVar3 = lVar7 == 0;
                if ((lVar7 != lVar4) && (lVar7 != 0)) {
                  plVar5 = (long *)(PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8 +
                                   0xc0);
                  lVar7 = *plVar5;
                  lVar6 = 8;
                  bVar3 = lVar7 == 0;
                  if ((lVar7 != lVar4) && (lVar7 != 0)) {
                    plVar5 = (long *)(PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8 +
                                     0xd8);
                    lVar7 = *plVar5;
                    lVar6 = 9;
                    bVar3 = lVar7 == 0;
                    if ((lVar7 != lVar4) && (lVar7 != 0)) {
                      plVar5 = (long *)(PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                       + 0xf0);
                      lVar7 = *plVar5;
                      lVar6 = 10;
                      bVar3 = lVar7 == 0;
                      if ((lVar7 != lVar4) && (lVar7 != 0)) {
                        lVar7 = *(long *)(
                                         PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                         + 0x108);
                        plVar5 = (long *)(
                                         PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                         + 0x108);
                        lVar6 = 0xb;
                        bVar3 = lVar7 == 0;
                        if ((lVar7 != lVar4) && (lVar7 != 0)) {
                          lVar7 = *(long *)(
                                           PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                           + 0x120);
                          plVar5 = (long *)(
                                           PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                           + 0x120);
                          lVar6 = 0xc;
                          bVar3 = lVar7 == 0;
                          if ((lVar7 != lVar4) && (lVar7 != 0)) {
                            lVar7 = *(long *)(
                                             PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                             + 0x138);
                            plVar5 = (long *)(
                                             PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                             + 0x138);
                            lVar6 = 0xd;
                            bVar3 = lVar7 == 0;
                            if ((lVar7 != lVar4) && (lVar7 != 0)) {
                              lVar7 = *(long *)(
                                               PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                               + 0x150);
                              plVar5 = (long *)(
                                               PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                               + 0x150);
                              lVar6 = 0xe;
                              bVar3 = lVar7 == 0;
                              if ((lVar7 != lVar4) && (lVar7 != 0)) {
                                lVar7 = *(long *)(
                                                 PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                 + 0x168);
                                plVar5 = (long *)(
                                                 PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                 + 0x168);
                                lVar6 = 0xf;
                                bVar3 = lVar7 == 0;
                                if ((lVar7 != lVar4) && (lVar7 != 0)) {
                                  lVar7 = *(long *)(
                                                  PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                  + 0x180);
                                  plVar5 = (long *)(
                                                  PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                  + 0x180);
                                  lVar6 = 0x10;
                                  bVar3 = lVar7 == 0;
                                  if ((lVar7 != lVar4) && (lVar7 != 0)) {
                                    lVar7 = *(long *)(
                                                  PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                  + 0x198);
                                    plVar5 = (long *)(
                                                  PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                  + 0x198);
                                    lVar6 = 0x11;
                                    bVar3 = lVar7 == 0;
                                    if ((lVar7 != lVar4) && (lVar7 != 0)) {
                                      lVar7 = *(long *)(
                                                  PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                  + 0x1b0);
                                      plVar5 = (long *)(
                                                  PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                  + 0x1b0);
                                      lVar6 = 0x12;
                                      bVar3 = lVar7 == 0;
                                      if ((lVar7 != lVar4) && (lVar7 != 0)) {
                                        lVar7 = *(long *)(
                                                  PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                  + 0x1c8);
                                        plVar5 = (long *)(
                                                  PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                  + 0x1c8);
                                        lVar6 = 0x13;
                                        bVar3 = lVar7 == 0;
                                        if ((lVar7 != lVar4) && (lVar7 != 0)) {
                                          lVar7 = *(long *)(
                                                  PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                  + 0x1e0);
                                          plVar5 = (long *)(
                                                  PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                  + 0x1e0);
                                          lVar6 = 0x14;
                                          bVar3 = lVar7 == 0;
                                          if ((lVar7 != lVar4) && (lVar7 != 0)) {
                                            lVar7 = *(long *)(
                                                  PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                  + 0x1f8);
                                            plVar5 = (long *)(
                                                  PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                  + 0x1f8);
                                            lVar6 = 0x15;
                                            bVar3 = lVar7 == 0;
                                            if ((lVar7 != lVar4) && (lVar7 != 0)) {
                                              lVar7 = *(long *)(
                                                  PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                  + 0x210);
                                              plVar5 = (long *)(
                                                  PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                  + 0x210);
                                              lVar6 = 0x16;
                                              bVar3 = lVar7 == 0;
                                              if ((lVar7 != lVar4) && (lVar7 != 0)) {
                                                lVar7 = *(long *)(
                                                  PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                  + 0x228);
                                                plVar5 = (long *)(
                                                  PTR__ZN4Aska10RenderPass23m_frameTextureRegistersE_02cc35d8
                                                  + 0x228);
                                                lVar6 = 0x17;
                                                bVar3 = lVar7 == 0;
                                                if ((lVar7 != lVar4) && (lVar7 != 0)) {
                                                  return;
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
        }
      }
    }
  }
  if (bVar3) {
    *(int *)PTR__ZN4Aska10RenderPass26m_numFrameTextureRegistersE_02cc3af8 =
         *(int *)PTR__ZN4Aska10RenderPass26m_numFrameTextureRegistersE_02cc3af8 + 1;
  }
  *plVar5 = lVar4;
  if (param_2 == (undefined *)0x0) {
    param_2 = PTR__Z27DefaultFrameTextureCallbackmjjj_02cc3788;
  }
  *(undefined **)(puVar2 + lVar6 * 0x18 + 8) = param_2;
  *(undefined4 *)(puVar2 + lVar6 * 0x18 + 0x10) = uVar1;
  return;
}

// ==== Aska::RenderPassManager::Init(int)
// vaddr 0x21be66c | ghidra 0x22be66c | size 372 | symbol _ZN4Aska17RenderPassManager4InitEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska17RenderPassManager4InitEi(long param_1,undefined8 param_2)

{
  long *plVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  
  *(char *)(param_1 + 0x7c) = (char)param_2;
  *(long *)(param_1 + 0x18) = param_1 + 0x1f8;
  uVar2 = Aska::RenderPass::Init(int, void*)(param_1 + 0x1f8,param_2,0);
  if ((uVar2 & 1) == 0) {
    return 0;
  }
  *(short *)(param_1 + 0x78) = *(short *)(param_1 + 0x78) + 1;
  if (*(ushort *)(param_1 + 0x28) < 4) {
    lVar4 = *(long *)(param_1 + 0x20);
    lVar3 = *(long *)(param_1 + 0x30);
    if (lVar4 == 0) {
      if (lVar3 == 0) {
        lVar3 = operator new[](unsigned long, std::nothrow_t const&)(0x80,PTR__ZSt7nothrow_02cb9a80);
      }
      else {
        lVar3 = Aska::MemoryManager::Malloc(unsigned long)(lVar3,0x80);
      }
      if (lVar3 != 0) {
        memcpy(lVar3,param_1 + 0x38,(ulong)*(ushort *)(param_1 + 0x2a) << 4);
      }
    }
    else if (lVar3 == 0) {
      lVar3 = operator new[](unsigned long, void*, unsigned long)(0x80,lVar4,4);
    }
    else {
      lVar3 = Aska::MemoryManager::Realloc(unsigned long, void*, long)(lVar3,0x80,lVar4,4);
    }
    if (lVar3 == 0) goto code_r0x022be754;
    *(long *)(param_1 + 0x20) = lVar3;
    *(undefined2 *)(param_1 + 0x28) = 8;
  }
  *(undefined2 *)(param_1 + 0x2a) = 4;
code_r0x022be754:
  plVar1 = (long *)(param_1 + 0x38);
  if (*(long **)(param_1 + 0x20) != (long *)0x0) {
    plVar1 = *(long **)(param_1 + 0x20);
  }
  *plVar1 = param_1 + 0x98;
  *(undefined1 *)(plVar1 + 1) = 0;
  plVar1 = (long *)(param_1 + 0x48);
  if (*(long *)(param_1 + 0x20) != 0) {
    plVar1 = (long *)(*(long *)(param_1 + 0x20) + 0x10);
  }
  *plVar1 = param_1 + 0xf0;
  *(undefined1 *)(plVar1 + 1) = 0;
  plVar1 = (long *)(param_1 + 0x58);
  if (*(long *)(param_1 + 0x20) != 0) {
    plVar1 = (long *)(*(long *)(param_1 + 0x20) + 0x20);
  }
  *plVar1 = param_1 + 0x148;
  *(undefined1 *)(plVar1 + 1) = 0;
  plVar1 = (long *)(param_1 + 0x68);
  if (*(long *)(param_1 + 0x20) != 0) {
    plVar1 = (long *)(*(long *)(param_1 + 0x20) + 0x30);
  }
  *plVar1 = param_1 + 0x1a0;
  *(undefined1 *)(plVar1 + 1) = 0;
  return 1;
}

// ==== Aska::RenderPassManager::SetPrimitive(int, Aska::RenderablePrimitive*)
// vaddr 0x21be7e0 | ghidra 0x22be7e0 | size 188 | symbol _ZN4Aska17RenderPassManager12SetPrimitiveEiPNS_19RenderablePrimitiveE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17RenderPassManager12SetPrimitiveEiPNS_19RenderablePrimitiveE
               (long param_1,int param_2,undefined8 param_3)

{
  long *plVar1;
  long *plVar2;
  ushort uVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  long *plVar7;
  
  *(undefined8 *)(*(long *)(*(long *)(param_1 + 0x18) + 8) + (long)param_2 * 0x1b8 + 0x28) = param_3
  ;
  if ((*(short *)(param_1 + 0x78) != 1) && (uVar3 = *(ushort *)(param_1 + 0x2a), (ulong)uVar3 != 0))
  {
    uVar4 = 0;
    do {
      lVar5 = *(long *)(param_1 + 0x20);
      plVar1 = (long *)(param_1 + 0x20) + uVar4 * 2 + 3;
      if (lVar5 != 0) {
        plVar1 = (long *)(lVar5 + uVar4 * 0x10);
      }
      plVar7 = (long *)*plVar1;
      uVar6 = (ulong)*(ushort *)((long)plVar7 + 10);
      if (uVar6 != 0) {
        lVar5 = 0;
        while( true ) {
          uVar6 = uVar6 - 1;
          plVar2 = (long *)((long)plVar7 + lVar5 + 0x18);
          if (*plVar7 != 0) {
            plVar2 = (long *)(*plVar7 + lVar5);
          }
          if (*plVar2 != 0) {
            *(undefined8 *)(*(long *)(*plVar2 + 8) + (long)param_2 * 0x1b8 + 0x28) = param_3;
          }
          if (uVar6 == 0) break;
          plVar7 = (long *)*plVar1;
          lVar5 = lVar5 + 8;
        }
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 != uVar3);
  }
  return;
}

// ==== Aska::RenderPassManager::~RenderPassManager()
// vaddr 0x21be89c | ghidra 0x22be89c | size 496 | symbol _ZN4Aska17RenderPassManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x022be95c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022be99c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022bea00: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022be9ec: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022be9d8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022be968: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x022be960) */
/* WARNING: Removing unreachable block (ram,0x022bea04) */
/* WARNING: Removing unreachable block (ram,0x022bea0c) */

void _ZN4Aska17RenderPassManagerD2Ev(long *param_1)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  long *plVar4;
  long lVar5;
  long *plVar6;
  ulong uVar7;
  
  *param_1 = (long)(PTR__ZTVN4Aska17RenderPassManagerE_02cbcfd8 + 0x10);
  if (*(short *)((long)param_1 + 0x2a) != 0) {
    lVar5 = 0;
    do {
      lVar3 = param_1[4];
      plVar4 = param_1 + 4 + lVar5 * 2 + 3;
      if (lVar3 != 0) {
        plVar4 = (long *)(lVar3 + lVar5 * 0x10);
      }
      plVar6 = (long *)*plVar4;
      uVar7 = (ulong)*(ushort *)((long)plVar6 + 10);
      if (uVar7 != 0) {
        lVar3 = 0;
        do {
          plVar1 = plVar6 + 3;
          if ((long *)*plVar6 != (long *)0x0) {
            plVar1 = (long *)*plVar6;
          }
          plVar2 = *(long **)((long)plVar1 + lVar3);
          if (plVar2 != (long *)0x0) {
            (**(code **)(*plVar2 + 8))();
            *(long *)((long)plVar1 + lVar3) = 0;
          }
          uVar7 = uVar7 - 1;
          lVar3 = lVar3 + 8;
        } while (uVar7 != 0);
      }
      if ((3 < lVar5) && (plVar4 = (long *)*plVar4, plVar4 != (long *)0x0)) {
        lVar3 = *plVar4;
        if (lVar3 != 0) {
          if (plVar4[2] != 0) goto code_r0x011fb8e0;
          goto code_r0x011fbb90;
        }
        operator delete(void*)(plVar4);
      }
      lVar5 = lVar5 + 1;
    } while (lVar5 < (long)(ulong)*(ushort *)((long)param_1 + 0x2a));
  }
  Aska::RenderPass::~RenderPass()(param_1 + 0x3f);
  if (param_1[0x34] == 0) {
    lVar3 = param_1[0x29];
    if (lVar3 == 0) goto code_r0x022be9dc;
code_r0x022be9a8:
    if (param_1[0x2b] == 0) goto code_r0x011fbb90;
    Aska::MemoryManager::LocalFree(void*)();
    lVar5 = param_1[0x1e];
    if (lVar5 == 0) goto code_r0x022be9f0;
code_r0x022be9e4:
    if (param_1[0x20] != 0) goto code_r0x011fb8e0;
    operator delete[](void*)(lVar5);
    lVar5 = param_1[0x13];
    if (lVar5 == 0) goto code_r0x022bea20;
code_r0x022be9f8:
    if (param_1[0x15] != 0) goto code_r0x011fb8e0;
    operator delete[](void*)(lVar5);
    lVar3 = param_1[4];
  }
  else {
    if (param_1[0x36] != 0) goto code_r0x011fb8e0;
    operator delete[](void*)(param_1[0x34]);
    lVar3 = param_1[0x29];
    if (lVar3 != 0) goto code_r0x022be9a8;
code_r0x022be9dc:
    lVar5 = param_1[0x1e];
    if (lVar5 != 0) goto code_r0x022be9e4;
code_r0x022be9f0:
    lVar5 = param_1[0x13];
    if (lVar5 != 0) goto code_r0x022be9f8;
code_r0x022bea20:
    lVar3 = param_1[4];
  }
  if (lVar3 == 0) {
    return;
  }
  if (param_1[6] == 0) {
code_r0x011fbb90:
    (*(code *)PTR__ZdaPv_02cb5db8)(lVar3);
    return;
  }
code_r0x011fb8e0:
  (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPv_02cb5c60)();
  return;
}

// ==== Aska::RenderPassManager::~RenderPassManager()
// vaddr 0x21bea8c | ghidra 0x22bea8c | size 24 | symbol _ZN4Aska17RenderPassManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17RenderPassManagerD0Ev(undefined8 param_1)

{
  Aska::RenderPassManager::~RenderPassManager()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RenderPassManager::GetPass(int, int)
// vaddr 0x21beaa4 | ghidra 0x22beaa4 | size 764 | symbol _ZN4Aska17RenderPassManager7GetPassEii | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska17RenderPassManager7GetPassEii(long param_1,uint param_2,uint param_3)

{
  long *plVar1;
  ushort uVar2;
  undefined8 *puVar3;
  long lVar4;
  long *plVar5;
  long lVar6;
  byte *pbVar7;
  long lVar8;
  long *plVar9;
  long lVar10;
  long lVar11;
  byte *pbVar12;
  ulong uVar13;
  
  uVar2 = *(ushort *)(param_1 + 0x2a);
  uVar13 = (ulong)uVar2;
  if (uVar2 != 0) {
    if (*(long *)(param_1 + 0x20) == 0) {
      lVar10 = 0;
      pbVar7 = (byte *)(param_1 + 0x40);
      do {
        if (*pbVar7 == 0) goto code_r0x022beba8;
        if (*pbVar7 == param_2) goto code_r0x022bebb4;
        lVar10 = lVar10 + 1;
        pbVar7 = pbVar7 + 0x10;
      } while (lVar10 < (long)uVar13);
    }
    else {
      lVar10 = 0;
      pbVar7 = (byte *)(*(long *)(param_1 + 0x20) + 8);
      do {
        if (*pbVar7 == 0) goto code_r0x022beba8;
        if (*pbVar7 == param_2) goto code_r0x022bebb4;
        lVar10 = lVar10 + 1;
        pbVar7 = pbVar7 + 0x10;
      } while (lVar10 < (long)uVar13);
    }
  }
  puVar3 = (undefined8 *)operator new(unsigned long, std::nothrow_t const&)(0x58,PTR__ZSt7nothrow_02cb9a80);
  if (puVar3 == (undefined8 *)0x0) {
    return (long *)0x0;
  }
  *puVar3 = 0;
  puVar3[2] = 0;
  puVar3[3] = 0;
  puVar3[4] = 0;
  puVar3[5] = 0;
  *(undefined4 *)(puVar3 + 1) = 0x40008;
  puVar3[6] = 0;
  if (uVar2 < *(ushort *)(param_1 + 0x2a)) {
code_r0x022bec30:
    lVar10 = *(long *)(param_1 + 0x20);
  }
  else {
    lVar10 = uVar13 + 1;
    if (uVar2 < *(ushort *)(param_1 + 0x28)) {
code_r0x022bec2c:
      *(short *)(param_1 + 0x2a) = (short)lVar10;
      goto code_r0x022bec30;
    }
    lVar8 = *(long *)(param_1 + 0x20);
    lVar4 = *(long *)(param_1 + 0x30);
    lVar6 = lVar10 * 0x20;
    if (lVar8 == 0) {
      if (lVar4 == 0) {
        lVar4 = operator new[](unsigned long, std::nothrow_t const&)(lVar6,PTR__ZSt7nothrow_02cb9a80);
      }
      else {
        lVar4 = Aska::MemoryManager::Malloc(unsigned long)();
      }
      if (lVar4 != 0) {
        memcpy(lVar4,param_1 + 0x38,(ulong)*(ushort *)(param_1 + 0x2a) << 4);
      }
    }
    else if (lVar4 == 0) {
      lVar4 = operator new[](unsigned long, void*, unsigned long)(lVar6,lVar8,4);
    }
    else {
      lVar4 = Aska::MemoryManager::Realloc(unsigned long, void*, long)(lVar4,lVar6,lVar8,4);
    }
    if (lVar4 != 0) {
      *(long *)(param_1 + 0x20) = lVar4;
      *(short *)(param_1 + 0x28) = (short)((int)lVar10 << 1);
      goto code_r0x022bec2c;
    }
    lVar10 = *(long *)(param_1 + 0x20);
    uVar13 = (ulong)*(ushort *)(param_1 + 0x2a) - 1;
  }
  pbVar12 = (byte *)(param_1 + uVar13 * 0x10 + 0x38);
  if (lVar10 != 0) {
    pbVar12 = (byte *)(lVar10 + uVar13 * 0x10);
  }
  *(undefined8 **)pbVar12 = puVar3;
  pbVar12[8] = (byte)param_2;
code_r0x022bec50:
  plVar5 = (long *)Aska::RenderPassMultipassArray::GetPass(int)(*(undefined8 *)pbVar12,(ulong)param_3);
  if ((plVar5 == (long *)0x0) &&
     (plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x1c8,PTR__ZSt7nothrow_02cb9a80), plVar5 != (long *)0x0)) {
    Aska::RenderPass::RenderPass()(plVar5);
    uVar13 = Aska::RenderPass::Init(int, void*)(plVar5,*(undefined1 *)(param_1 + 0x7c),0);
    if ((uVar13 & 1) == 0) {
      (**(code **)(*plVar5 + 8))(plVar5);
      plVar5 = (long *)0x0;
    }
    else {
      *(short *)(param_1 + 0x78) = *(short *)(param_1 + 0x78) + 1;
      lVar10 = *(long *)(param_1 + 0x18);
      if (*(char *)((long)plVar5 + 0x26) != '\0') {
        lVar6 = 0;
        lVar4 = 0;
        do {
          lVar11 = plVar5[1];
          lVar8 = *(long *)(lVar10 + 8) + lVar6;
          *(long *)(lVar11 + lVar6 + 8) = lVar8;
          if (lVar8 != 0) {
            *(undefined8 *)(lVar11 + lVar6 + 0x10) = *(undefined8 *)(lVar8 + 0x10);
          }
          lVar4 = lVar4 + 1;
          lVar8 = *(long *)(lVar10 + 8) + lVar6;
          lVar11 = plVar5[1] + lVar6;
          lVar6 = lVar6 + 0x1b8;
          *(undefined8 *)(lVar11 + 0x28) = *(undefined8 *)(lVar8 + 0x28);
        } while (lVar4 < (long)(ulong)*(byte *)((long)plVar5 + 0x26));
      }
      if (*(long *)(lVar10 + 0x40) != 0) {
        plVar5[9] = *(long *)(lVar10 + 0x40);
      }
      *(long **)(lVar10 + 0x40) = plVar5;
      plVar5[7] = lVar10;
      *(ushort *)((long)plVar5 + 0x2f) = *(ushort *)((long)plVar5 + 0x2f) & 0xfff7;
      plVar9 = *(long **)pbVar12;
      if ((int)param_3 < (int)(uint)*(ushort *)((long)plVar9 + 10)) {
        uVar13 = -(ulong)(param_3 >> 0x1f) & 0xfffffff800000000 | (ulong)param_3 << 3;
        plVar1 = (long *)((long)plVar9 + uVar13 + 0x18);
        if (*plVar9 != 0) {
          plVar1 = (long *)(*plVar9 + uVar13);
        }
        *plVar1 = (long)plVar5;
      }
    }
  }
  return plVar5;
code_r0x022beba8:
  pbVar12 = pbVar7 + -8;
  *pbVar7 = (byte)param_2;
  goto code_r0x022bec50;
code_r0x022bebb4:
  pbVar12 = pbVar7 + -8;
  goto code_r0x022bec50;
}

// ==== Aska::RenderPassManager::DeletePass(int, int)
// vaddr 0x21bef3c | ghidra 0x22bef3c | size 236 | symbol _ZN4Aska17RenderPassManager10DeletePassEii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17RenderPassManager10DeletePassEii(long param_1,uint param_2,uint param_3)

{
  undefined8 *puVar1;
  long *plVar2;
  ulong uVar3;
  byte *pbVar4;
  long lVar5;
  
  uVar3 = (ulong)*(ushort *)(param_1 + 0x2a);
  if (uVar3 != 0) {
    if (*(long *)(param_1 + 0x20) == 0) {
      lVar5 = 0;
      pbVar4 = (byte *)(param_1 + 0x40);
      do {
        if (*pbVar4 == 0) goto code_r0x022befb4;
        if (*pbVar4 == param_2) goto code_r0x022befc4;
        lVar5 = lVar5 + 1;
        pbVar4 = pbVar4 + 0x10;
      } while (lVar5 < (long)uVar3);
    }
    else {
      lVar5 = 0;
      pbVar4 = (byte *)(*(long *)(param_1 + 0x20) + 8);
      do {
        if (*pbVar4 == 0) {
code_r0x022befb4:
          *pbVar4 = (byte)param_2;
code_r0x022befc4:
          plVar2 = (long *)Aska::RenderPassMultipassArray::GetPass(int)(*(undefined8 *)(pbVar4 + -8),(ulong)param_3);
          if (plVar2 == (long *)0x0) {
            return;
          }
          *(short *)(param_1 + 0x78) = *(short *)(param_1 + 0x78) + -1;
          (**(code **)(*plVar2 + 8))();
          plVar2 = *(long **)(pbVar4 + -8);
          if ((int)(uint)*(ushort *)((long)plVar2 + 10) <= (int)param_3) {
            return;
          }
          uVar3 = -(ulong)(param_3 >> 0x1f) & 0xfffffff800000000 | (ulong)param_3 << 3;
          puVar1 = (undefined8 *)((long)plVar2 + uVar3 + 0x18);
          if (*plVar2 != 0) {
            puVar1 = (undefined8 *)(*plVar2 + uVar3);
          }
          *puVar1 = 0;
          return;
        }
        if (*pbVar4 == param_2) goto code_r0x022befc4;
        lVar5 = lVar5 + 1;
        pbVar4 = pbVar4 + 0x10;
      } while (lVar5 < (long)uVar3);
    }
  }
  return;
}

// ==== Aska::RenderPassManager::InvalidateAll()
// vaddr 0x21bf028 | ghidra 0x22bf028 | size 284 | symbol _ZN4Aska17RenderPassManager13InvalidateAllEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17RenderPassManager13InvalidateAllEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  ushort uVar3;
  uint uVar4;
  ushort *puVar5;
  long lVar6;
  long *plVar7;
  ulong uVar8;
  long lVar9;
  ulong uVar10;
  
  uVar3 = *(ushort *)(param_1 + 0x2a);
  puVar5 = (ushort *)(*(long *)(param_1 + 0x18) + 0x2f);
  *puVar5 = *puVar5 & 0xffbf;
  puVar5 = (ushort *)(*(long *)(param_1 + 0x18) + 0x2f);
  *puVar5 = *puVar5 & 0xff7f;
  lVar6 = *(long *)(param_1 + 0x18);
  *(undefined2 *)(lVar6 + 0x2f) = *(undefined2 *)(lVar6 + 0x2f);
  *(byte *)(lVar6 + 0x31) = *(byte *)(lVar6 + 0x31) & 0xfe;
  if ((ulong)uVar3 != 0) {
    uVar10 = 0;
    do {
      lVar6 = *(long *)(param_1 + 0x20);
      plVar1 = (long *)(param_1 + 0x20) + uVar10 * 2 + 3;
      if (lVar6 != 0) {
        plVar1 = (long *)(lVar6 + uVar10 * 0x10);
      }
      plVar7 = (long *)*plVar1;
      uVar8 = (ulong)*(ushort *)((long)plVar7 + 10);
      if (uVar8 != 0) {
        lVar6 = 0;
        while( true ) {
          uVar8 = uVar8 - 1;
          plVar2 = (long *)((long)plVar7 + lVar6 + 0x18);
          if (*plVar7 != 0) {
            plVar2 = (long *)(*plVar7 + lVar6);
          }
          lVar9 = *plVar2;
          if (lVar9 != 0) {
            Aska::RenderPass::InvalidateShaders()(lVar9);
            uVar4 = *(uint3 *)(lVar9 + 0x2f) & 0xfeff3f;
            *(short *)(lVar9 + 0x2f) = (short)uVar4;
            *(char *)(lVar9 + 0x31) = (char)(uVar4 >> 0x10);
          }
          if (uVar8 == 0) break;
          plVar7 = (long *)*plVar1;
          lVar6 = lVar6 + 8;
        }
      }
      uVar10 = uVar10 + 1;
    } while (uVar10 != uVar3);
  }
  return;
}

// ==== Aska::RenderPassManager::InvalidateShaders(bool)
// vaddr 0x21bf144 | ghidra 0x22bf144 | size 204 | symbol _ZN4Aska17RenderPassManager17InvalidateShadersEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17RenderPassManager17InvalidateShadersEb(long param_1,uint param_2)

{
  long *plVar1;
  long *plVar2;
  ushort uVar3;
  long *plVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  
  uVar3 = *(ushort *)(param_1 + 0x2a);
  if ((param_2 & 1) != 0) {
    Aska::RenderPass::InvalidateShaders()(*(undefined8 *)(param_1 + 0x18));
  }
  if (uVar3 != 0) {
    uVar8 = 0;
    do {
      lVar5 = *(long *)(param_1 + 0x20);
      plVar1 = (long *)(param_1 + 0x20) + uVar8 * 2 + 3;
      if (lVar5 != 0) {
        plVar1 = (long *)(lVar5 + uVar8 * 0x10);
      }
      plVar4 = (long *)*plVar1;
      uVar6 = (ulong)*(ushort *)((long)plVar4 + 10);
      if (uVar6 != 0) {
        lVar5 = 0;
        while( true ) {
          uVar6 = uVar6 - 1;
          plVar2 = (long *)((long)plVar4 + lVar5 + 0x18);
          if (*plVar4 != 0) {
            plVar2 = (long *)(*plVar4 + lVar5);
          }
          lVar7 = *plVar2;
          if (lVar7 != 0) {
            Aska::RenderPass::InvalidateShaders()(lVar7);
            *(undefined2 *)(lVar7 + 0x180) = 0xfefe;
          }
          if (uVar6 == 0) break;
          plVar4 = (long *)*plVar1;
          lVar5 = lVar5 + 8;
        }
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 != uVar3);
  }
  return;
}

// ==== Aska::RenderPassManager::InvalidateShaderCaches()
// vaddr 0x21bf210 | ghidra 0x22bf210 | size 200 | symbol _ZN4Aska17RenderPassManager22InvalidateShaderCachesEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska17RenderPassManager22InvalidateShaderCachesEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  ushort uVar3;
  int iVar4;
  long *plVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  ulong uVar9;
  
  uVar3 = *(ushort *)(param_1 + 0x2a);
  Aska::RenderPass::InvalidateShaderCaches()(*(undefined8 *)(param_1 + 0x18));
  if ((ulong)uVar3 == 0) {
    iVar8 = 0;
  }
  else {
    uVar9 = 0;
    iVar8 = 0;
    do {
      lVar6 = *(long *)(param_1 + 0x20);
      plVar1 = (long *)(param_1 + 0x20) + uVar9 * 2 + 3;
      if (lVar6 != 0) {
        plVar1 = (long *)(lVar6 + uVar9 * 0x10);
      }
      plVar5 = (long *)*plVar1;
      uVar7 = (ulong)*(ushort *)((long)plVar5 + 10);
      if (uVar7 != 0) {
        lVar6 = 0;
        while( true ) {
          uVar7 = uVar7 - 1;
          plVar2 = (long *)((long)plVar5 + lVar6 + 0x18);
          if (*plVar5 != 0) {
            plVar2 = (long *)(*plVar5 + lVar6);
          }
          if (*plVar2 != 0) {
            iVar4 = Aska::RenderPass::InvalidateShaderCaches()();
            iVar8 = iVar4 + iVar8;
          }
          if (uVar7 == 0) break;
          plVar5 = (long *)*plVar1;
          lVar6 = lVar6 + 8;
        }
      }
      uVar9 = uVar9 + 1;
    } while (uVar9 != uVar3);
  }
  return iVar8;
}

// ==== Aska::RenderPassManager::InvalidateRenderState()
// vaddr 0x21bf2d8 | ghidra 0x22bf2d8 | size 168 | symbol _ZN4Aska17RenderPassManager21InvalidateRenderStateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17RenderPassManager21InvalidateRenderStateEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  ushort uVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  long *plVar7;
  ushort *puVar8;
  
  lVar4 = *(long *)(param_1 + 0x18);
  uVar3 = *(ushort *)(param_1 + 0x2a);
  *(ushort *)(lVar4 + 0x2f) = *(ushort *)(lVar4 + 0x2f) & 0xffbf;
  *(undefined1 *)(lVar4 + 0x31) = *(undefined1 *)(lVar4 + 0x31);
  if ((ulong)uVar3 != 0) {
    uVar5 = 0;
    do {
      lVar4 = *(long *)(param_1 + 0x20);
      plVar1 = (long *)(param_1 + 0x20) + uVar5 * 2 + 3;
      if (lVar4 != 0) {
        plVar1 = (long *)(lVar4 + uVar5 * 0x10);
      }
      plVar7 = (long *)*plVar1;
      uVar6 = (ulong)*(ushort *)((long)plVar7 + 10);
      if (uVar6 != 0) {
        lVar4 = 0;
        while( true ) {
          uVar6 = uVar6 - 1;
          plVar2 = (long *)((long)plVar7 + lVar4 + 0x18);
          if (*plVar7 != 0) {
            plVar2 = (long *)(*plVar7 + lVar4);
          }
          if (*plVar2 != 0) {
            puVar8 = (ushort *)(*plVar2 + 0x2f);
            *puVar8 = *puVar8 & 0xffbf;
          }
          if (uVar6 == 0) break;
          plVar7 = (long *)*plVar1;
          lVar4 = lVar4 + 8;
        }
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 != uVar3);
  }
  return;
}

// ==== Aska::RenderPassManager::InvalidateObjectRenderState()
// vaddr 0x21bf380 | ghidra 0x22bf380 | size 168 | symbol _ZN4Aska17RenderPassManager27InvalidateObjectRenderStateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17RenderPassManager27InvalidateObjectRenderStateEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  ushort uVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  long *plVar7;
  ushort *puVar8;
  
  lVar4 = *(long *)(param_1 + 0x18);
  uVar3 = *(ushort *)(param_1 + 0x2a);
  *(ushort *)(lVar4 + 0x2f) = *(ushort *)(lVar4 + 0x2f) & 0xff7f;
  *(undefined1 *)(lVar4 + 0x31) = *(undefined1 *)(lVar4 + 0x31);
  if ((ulong)uVar3 != 0) {
    uVar5 = 0;
    do {
      lVar4 = *(long *)(param_1 + 0x20);
      plVar1 = (long *)(param_1 + 0x20) + uVar5 * 2 + 3;
      if (lVar4 != 0) {
        plVar1 = (long *)(lVar4 + uVar5 * 0x10);
      }
      plVar7 = (long *)*plVar1;
      uVar6 = (ulong)*(ushort *)((long)plVar7 + 10);
      if (uVar6 != 0) {
        lVar4 = 0;
        while( true ) {
          uVar6 = uVar6 - 1;
          plVar2 = (long *)((long)plVar7 + lVar4 + 0x18);
          if (*plVar7 != 0) {
            plVar2 = (long *)(*plVar7 + lVar4);
          }
          if (*plVar2 != 0) {
            puVar8 = (ushort *)(*plVar2 + 0x2f);
            *puVar8 = *puVar8 & 0xff7f;
          }
          if (uVar6 == 0) break;
          plVar7 = (long *)*plVar1;
          lVar4 = lVar4 + 8;
        }
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 != uVar3);
  }
  return;
}

// ==== Aska::RenderPassManager::InvalidateMaterial()
// vaddr 0x21bf428 | ghidra 0x22bf428 | size 184 | symbol _ZN4Aska17RenderPassManager18InvalidateMaterialEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17RenderPassManager18InvalidateMaterialEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  ushort uVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  long *plVar7;
  long lVar8;
  
  lVar4 = *(long *)(param_1 + 0x18);
  uVar3 = *(ushort *)(param_1 + 0x2a);
  *(undefined2 *)(lVar4 + 0x2f) = *(undefined2 *)(lVar4 + 0x2f);
  *(byte *)(lVar4 + 0x31) = *(byte *)(lVar4 + 0x31) & 0xfe;
  if ((ulong)uVar3 != 0) {
    uVar5 = 0;
    do {
      lVar4 = *(long *)(param_1 + 0x20);
      plVar1 = (long *)(param_1 + 0x20) + uVar5 * 2 + 3;
      if (lVar4 != 0) {
        plVar1 = (long *)(lVar4 + uVar5 * 0x10);
      }
      plVar7 = (long *)*plVar1;
      uVar6 = (ulong)*(ushort *)((long)plVar7 + 10);
      if (uVar6 != 0) {
        lVar4 = 0;
        while( true ) {
          uVar6 = uVar6 - 1;
          plVar2 = (long *)((long)plVar7 + lVar4 + 0x18);
          if (*plVar7 != 0) {
            plVar2 = (long *)(*plVar7 + lVar4);
          }
          lVar8 = *plVar2;
          if (lVar8 != 0) {
            *(undefined2 *)(lVar8 + 0x2f) = *(undefined2 *)(lVar8 + 0x2f);
            *(byte *)(lVar8 + 0x31) = *(byte *)(lVar8 + 0x31) & 0xfe;
          }
          if (uVar6 == 0) break;
          plVar7 = (long *)*plVar1;
          lVar4 = lVar4 + 8;
        }
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 != uVar3);
  }
  return;
}

// ==== Aska::RenderPassManager::InvalidateCommandBufferManager()
// vaddr 0x21bf4e0 | ghidra 0x22bf4e0 | size 4 | symbol _ZN4Aska17RenderPassManager30InvalidateCommandBufferManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17RenderPassManager30InvalidateCommandBufferManagerEv(void)

{
  return;
}

// ==== Aska::RenderPassManager::InvalidateDynamicShaderModifier()
// vaddr 0x21bf4e4 | ghidra 0x22bf4e4 | size 148 | symbol _ZN4Aska17RenderPassManager31InvalidateDynamicShaderModifierEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17RenderPassManager31InvalidateDynamicShaderModifierEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  ushort uVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  long *plVar7;
  long lVar8;
  
  uVar3 = *(ushort *)(param_1 + 0x2a);
  if ((ulong)uVar3 != 0) {
    uVar4 = 0;
    do {
      lVar5 = *(long *)(param_1 + 0x20);
      plVar1 = (long *)(param_1 + 0x20) + uVar4 * 2 + 3;
      if (lVar5 != 0) {
        plVar1 = (long *)(lVar5 + uVar4 * 0x10);
      }
      if ((char)plVar1[1] == '\x01') {
        plVar7 = (long *)*plVar1;
        uVar6 = (ulong)*(ushort *)((long)plVar7 + 10);
        if (uVar6 != 0) {
          lVar5 = 0;
          while( true ) {
            uVar6 = uVar6 - 1;
            plVar2 = (long *)((long)plVar7 + lVar5 + 0x18);
            if (*plVar7 != 0) {
              plVar2 = (long *)(*plVar7 + lVar5);
            }
            lVar8 = *plVar2;
            if (lVar8 != 0) {
              *(undefined8 *)(lVar8 + 0x50) = 0;
              *(undefined1 *)(lVar8 + 0x2a) = 0;
            }
            if (uVar6 == 0) break;
            plVar7 = (long *)*plVar1;
            lVar5 = lVar5 + 8;
          }
        }
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 != uVar3);
  }
  return;
}

// ==== Aska::RenderPassManager::InvalidateDynamicShaderModifierCache()
// vaddr 0x21bf578 | ghidra 0x22bf578 | size 148 | symbol _ZN4Aska17RenderPassManager36InvalidateDynamicShaderModifierCacheEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17RenderPassManager36InvalidateDynamicShaderModifierCacheEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  ushort uVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  long *plVar7;
  
  uVar3 = *(ushort *)(param_1 + 0x2a);
  if ((ulong)uVar3 != 0) {
    uVar4 = 0;
    do {
      lVar5 = *(long *)(param_1 + 0x20);
      plVar1 = (long *)(param_1 + 0x20) + uVar4 * 2 + 3;
      if (lVar5 != 0) {
        plVar1 = (long *)(lVar5 + uVar4 * 0x10);
      }
      if ((char)plVar1[1] == '\x01') {
        plVar7 = (long *)*plVar1;
        uVar6 = (ulong)*(ushort *)((long)plVar7 + 10);
        if (uVar6 != 0) {
          lVar5 = 0;
          while( true ) {
            uVar6 = uVar6 - 1;
            plVar2 = (long *)((long)plVar7 + lVar5 + 0x18);
            if (*plVar7 != 0) {
              plVar2 = (long *)(*plVar7 + lVar5);
            }
            if (*plVar2 != 0) {
              *(undefined2 *)(*plVar2 + 0x180) = 0xfefe;
            }
            if (uVar6 == 0) break;
            plVar7 = (long *)*plVar1;
            lVar5 = lVar5 + 8;
          }
        }
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 != uVar3);
  }
  return;
}

// ==== Aska::RenderPassManager::GetShadowCastPass(Aska::RenderPass*, Aska::MaterialList*, unsigned char, int)
// vaddr 0x21bf60c | ghidra 0x22bf60c | size 816 | symbol _ZN4Aska17RenderPassManager17GetShadowCastPassEPNS_10RenderPassEPNS_12MaterialListEhi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska17RenderPassManager17GetShadowCastPassEPNS_10RenderPassEPNS_12MaterialListEhi
               (long param_1,long param_2,long param_3,uint param_4)

{
  long lVar1;
  byte bVar2;
  ushort uVar3;
  bool bVar4;
  undefined4 uVar5;
  long lVar6;
  ulong uVar7;
  uint uVar8;
  undefined8 uVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  undefined8 uVar14;
  long lVar15;
  
  lVar6 = Aska::RenderPassManager::GetPass(int, int)(param_1,2,param_4 & 3);
  if (lVar6 != 0) {
    uVar3 = *(ushort *)(param_3 + 0x20);
    uVar8 = (uint)*(uint3 *)(lVar6 + 0x2f);
    if ((*(uint3 *)(lVar6 + 0x2f) & 4) == 0) {
      uVar7 = Aska::RenderPass::Create(int)(lVar6,0);
      if ((uVar7 & 1) == 0) {
        return 0;
      }
      uVar8 = (uint)*(ushort *)(lVar6 + 0x2f);
    }
    if ((uVar8 >> 5 & 1) == 0) {
      if ((uVar3 >> 7 & 1) == 0) {
        if (*(char *)(param_1 + 0x7c) != '\0') {
          lVar12 = 0;
          lVar13 = 0;
          lVar15 = 0x10;
          if (((param_4 & 0xff) >> 1 & 1) == 0) {
            do {
              lVar10 = *(long *)(*(long *)(lVar6 + 8) + lVar12 + 0x20);
              uVar9 = *(undefined8 *)(*(long *)(*(long *)(param_2 + 8) + lVar12 + 0x20) + 8);
              lVar1 = 0;
              if (*(long *)(param_3 + 0x18) != 0) {
                lVar1 = *(long *)(param_3 + 0x18) + lVar15;
              }
              *(undefined1 *)(lVar10 + 0x10) = 0;
              *(undefined8 *)(lVar10 + 8) = uVar9;
              uVar5 = Aska::RenderPass::GetShaderKeyFlags(Aska::RenderPassBatch const*)();
              Aska::ShaderNodeHandler::MakeZprepassShaderKey(int, Aska::ShaderContext*)(lVar10,uVar5,lVar1 + 0x10);
              if (*(char *)(lVar10 + 0x10) != '\x01') {
                return 0;
              }
              if (((*(ushort *)(lVar1 + 0x245) >> 5 & 1) == 0) && (*(short *)(lVar1 + 0x238) == 0))
              {
                bVar4 = (*(ushort *)(lVar1 + 0x245) & 0x2000) == 0;
              }
              else {
                bVar4 = true;
              }
              lVar13 = lVar13 + 1;
              lVar15 = lVar15 + 0x2a0;
              lVar1 = *(long *)(lVar6 + 8) + lVar12;
              bVar2 = *(byte *)(lVar1 + 0x58);
              lVar12 = lVar12 + 0x1b8;
              *(byte *)(lVar1 + 0x58) = bVar2 & 0xf8 | bVar2 & 3 | bVar4 << 2;
            } while (lVar13 < (long)(ulong)*(byte *)(param_1 + 0x7c));
          }
          else {
            do {
              lVar10 = *(long *)(*(long *)(lVar6 + 8) + lVar12 + 0x20);
              uVar9 = *(undefined8 *)(*(long *)(*(long *)(param_2 + 8) + lVar12 + 0x20) + 8);
              lVar1 = 0;
              if (*(long *)(param_3 + 0x18) != 0) {
                lVar1 = *(long *)(param_3 + 0x18) + lVar15;
              }
              *(undefined1 *)(lVar10 + 0x10) = 0;
              *(undefined8 *)(lVar10 + 8) = uVar9;
              uVar5 = Aska::RenderPass::GetShaderKeyFlags(Aska::RenderPassBatch const*)();
              Aska::ShaderNodeHandler::MakeColorShadowShaderKey(int, Aska::ShaderContext*)(lVar10,uVar5,lVar1 + 0x10);
              if (*(char *)(lVar10 + 0x10) != '\x03') {
                return 0;
              }
              if (((*(ushort *)(lVar1 + 0x245) >> 5 & 1) == 0) && (*(short *)(lVar1 + 0x238) == 0))
              {
                bVar4 = (*(ushort *)(lVar1 + 0x245) & 0x2000) == 0;
              }
              else {
                bVar4 = true;
              }
              lVar13 = lVar13 + 1;
              lVar15 = lVar15 + 0x2a0;
              lVar1 = *(long *)(lVar6 + 8) + lVar12;
              bVar2 = *(byte *)(lVar1 + 0x58);
              lVar12 = lVar12 + 0x1b8;
              *(byte *)(lVar1 + 0x58) = bVar2 & 0xf8 | bVar2 & 3 | bVar4 << 2;
            } while (lVar13 < (long)(ulong)*(byte *)(param_1 + 0x7c));
          }
        }
      }
      else if (*(char *)(param_1 + 0x7c) != '\0') {
        lVar12 = 0;
        lVar13 = 0;
        lVar15 = 0x10;
        do {
          lVar1 = 0;
          if (*(long *)(param_3 + 0x18) != 0) {
            lVar1 = *(long *)(param_3 + 0x18) + lVar15;
          }
          lVar10 = *(long *)(*(long *)(param_2 + 8) + lVar12 + 0x20);
          lVar11 = *(long *)(*(long *)(lVar6 + 8) + lVar12 + 0x20);
          if ((*(byte *)(lVar1 + 0x245) >> 1 & 1) == 0) {
            uVar9 = *(undefined8 *)(lVar10 + 8);
            *(undefined1 *)(lVar11 + 0x10) = 0;
            *(undefined8 *)(lVar11 + 8) = uVar9;
            uVar5 = Aska::RenderPass::GetShaderKeyFlags(Aska::RenderPassBatch const*)();
            Aska::ShaderNodeHandler::MakeZprepassShaderKey(int, Aska::ShaderContext*)(lVar11,uVar5,lVar1 + 0x10);
            if (*(char *)(lVar11 + 0x10) != '\x01') {
              return 0;
            }
          }
          else if (*(char *)(lVar11 + 0x10) == '\0') {
            if (*(char *)(lVar10 + 0x11) == '\0') {
              uVar9 = 0;
              if (*(char *)(lVar10 + 0x12) != '\0') goto code_r0x022bf894;
code_r0x022bf8a8:
              uVar14 = 0;
            }
            else {
              uVar9 = *(undefined8 *)(lVar10 + 0x18);
              if (*(char *)(lVar10 + 0x12) == '\0') goto code_r0x022bf8a8;
code_r0x022bf894:
              uVar14 = *(undefined8 *)(lVar10 + 0x20);
            }
            uVar5 = Aska::RenderPass::GetShaderKeyFlags(Aska::RenderPassBatch const*)();
            Aska::ShaderNodeHandler::MakePunchThroughDepthShaderKey(unsigned char*, unsigned char*, int)(lVar11,uVar9,uVar14,uVar5);
            if (*(char *)(lVar11 + 0x10) != '\x03') {
              return 0;
            }
          }
          if (((*(ushort *)(lVar1 + 0x245) >> 5 & 1) == 0) && (*(short *)(lVar1 + 0x238) == 0)) {
            bVar4 = (*(ushort *)(lVar1 + 0x245) & 0x2000) == 0;
          }
          else {
            bVar4 = true;
          }
          lVar13 = lVar13 + 1;
          lVar15 = lVar15 + 0x2a0;
          lVar1 = *(long *)(lVar6 + 8) + lVar12;
          bVar2 = *(byte *)(lVar1 + 0x58);
          lVar12 = lVar12 + 0x1b8;
          *(byte *)(lVar1 + 0x58) = bVar2 & 0xf8 | bVar2 & 3 | bVar4 << 2;
        } while (lVar13 < (long)(ulong)*(byte *)(param_1 + 0x7c));
      }
    }
  }
  return lVar6;
}

// ==== Aska::RenderPassManager::GetObjectMotionBlurPass(Aska::RenderPass*, Aska::MaterialList*, bool)
// vaddr 0x21bf93c | ghidra 0x22bf93c | size 400 | symbol _ZN4Aska17RenderPassManager23GetObjectMotionBlurPassEPNS_10RenderPassEPNS_12MaterialListEb | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska17RenderPassManager23GetObjectMotionBlurPassEPNS_10RenderPassEPNS_12MaterialListEb
               (long param_1,long param_2,long param_3,uint param_4)

{
  long lVar1;
  byte bVar2;
  bool bVar3;
  undefined4 uVar4;
  long lVar5;
  ulong uVar6;
  uint uVar7;
  long lVar8;
  long lVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  
  lVar5 = Aska::RenderPassManager::GetPass(int, int)(param_1,5,0);
  if (lVar5 != 0) {
    uVar7 = (uint)*(uint3 *)(lVar5 + 0x2f);
    if ((*(uint3 *)(lVar5 + 0x2f) & 4) == 0) {
      uVar6 = Aska::RenderPass::Create(int)(lVar5,0);
      if ((uVar6 & 1) == 0) {
        return 0;
      }
      uVar7 = *(ushort *)(lVar5 + 0x2f) | 0x100;
      *(ushort *)(lVar5 + 0x2f) = (ushort)uVar7;
    }
    if (((uVar7 >> 5 & 1) == 0) && (*(char *)(param_1 + 0x7c) != '\0')) {
      lVar12 = 0;
      lVar13 = 0;
      lVar14 = 0x10;
      do {
        lVar9 = *(long *)(*(long *)(lVar5 + 8) + lVar12 + 0x20);
        lVar1 = 0;
        if (*(long *)(param_3 + 0x18) != 0) {
          lVar1 = *(long *)(param_3 + 0x18) + lVar14;
        }
        if (*(char *)(lVar9 + 0x10) == '\0') {
          lVar8 = *(long *)(*(long *)(param_2 + 8) + lVar12 + 0x20);
          if (*(char *)(lVar8 + 0x11) == '\0') {
            uVar10 = 0;
            if (*(char *)(lVar8 + 0x12) != '\0') goto code_r0x022bfa18;
code_r0x022bfa2c:
            uVar11 = 0;
          }
          else {
            uVar10 = *(undefined8 *)(lVar8 + 0x18);
            if (*(char *)(lVar8 + 0x12) == '\0') goto code_r0x022bfa2c;
code_r0x022bfa18:
            uVar11 = *(undefined8 *)(lVar8 + 0x20);
          }
          uVar4 = Aska::RenderPass::GetShaderKeyFlags(Aska::RenderPassBatch const*)();
          Aska::ShaderNodeHandler::MakeObjectMotionBlurShaderKey(unsigned char*, unsigned char*, bool, int)(lVar9,uVar10,uVar11,param_4 & 1,uVar4);
          if (*(char *)(lVar9 + 0x10) != '\x03') {
            return 0;
          }
        }
        if (*(short *)(lVar1 + 0x238) == 0) {
          bVar3 = (*(byte *)(lVar1 + 0x246) & 0x20) == 0;
        }
        else {
          bVar3 = true;
        }
        lVar13 = lVar13 + 1;
        lVar14 = lVar14 + 0x2a0;
        lVar1 = *(long *)(lVar5 + 8) + lVar12;
        bVar2 = *(byte *)(lVar1 + 0x58);
        lVar12 = lVar12 + 0x1b8;
        *(byte *)(lVar1 + 0x58) = bVar2 & 0xf8 | bVar2 & 3 | bVar3 << 2;
      } while (lVar13 < (long)(ulong)*(byte *)(param_1 + 0x7c));
    }
  }
  return lVar5;
}

// ==== Aska::RenderPassManager::GetZprePass(Aska::RenderPass*, Aska::MaterialList*, int, Aska::RENDERINFO::Zprepass)
// vaddr 0x21bfacc | ghidra 0x22bfacc | size 968 | symbol _ZN4Aska17RenderPassManager11GetZprePassEPNS_10RenderPassEPNS_12MaterialListEiNS_10RENDERINFO8ZprepassE | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska17RenderPassManager11GetZprePassEPNS_10RenderPassEPNS_12MaterialListEiNS_10RENDERINFO8ZprepassE
               (long param_1,long param_2,long param_3,undefined4 param_4,uint param_5)

{
  long *plVar1;
  long lVar2;
  byte bVar3;
  ushort uVar4;
  bool bVar5;
  undefined4 uVar6;
  long lVar7;
  ulong uVar8;
  undefined8 uVar9;
  uint uVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  undefined8 uVar14;
  long lVar15;
  long lVar16;
  
  lVar7 = Aska::RenderPassManager::GetPass(int, int)(param_1,3,param_4);
  if (lVar7 != 0) {
    bVar3 = *(byte *)(param_3 + 0x21);
    uVar10 = (uint)*(uint3 *)(lVar7 + 0x2f);
    if ((*(uint3 *)(lVar7 + 0x2f) & 4) == 0) {
      uVar8 = Aska::RenderPass::Create(int)(lVar7,0);
      if ((uVar8 & 1) == 0) {
        return 0;
      }
      if (*(char *)(param_1 + 0x7c) != '\0') {
        lVar11 = 0;
        lVar13 = 0x20;
        do {
          lVar11 = lVar11 + 1;
          plVar1 = (long *)(*(long *)(param_2 + 8) + lVar13);
          lVar15 = *(long *)(*(long *)(lVar7 + 8) + lVar13);
          lVar13 = lVar13 + 0x1b8;
          uVar14 = *(undefined8 *)(*plVar1 + 8);
          *(undefined1 *)(lVar15 + 0x10) = 0;
          *(undefined8 *)(lVar15 + 8) = uVar14;
        } while (lVar11 < (long)(ulong)*(byte *)(param_1 + 0x7c));
      }
      uVar10 = *(uint3 *)(lVar7 + 0x2f) | 0x100;
      *(short *)(lVar7 + 0x2f) = (short)uVar10;
    }
    if ((uint)*(byte *)(lVar7 + 0x2e) != (param_5 & 0xff)) {
      *(char *)(lVar7 + 0x2e) = (char)param_5;
      Aska::RenderPass::InvalidateShaders()(lVar7);
      uVar10 = (uint)*(ushort *)(lVar7 + 0x2f);
    }
    if ((uVar10 >> 5 & 1) == 0) {
      if (param_5 == 0 && (bVar3 & 1) == 0) {
        if (*(char *)(param_1 + 0x7c) != '\0') {
          lVar15 = 0;
          lVar11 = 0;
          lVar13 = 0x10;
          do {
            lVar16 = *(long *)(*(long *)(lVar7 + 8) + lVar15 + 0x20);
            lVar2 = 0;
            if (*(long *)(param_3 + 0x18) != 0) {
              lVar2 = *(long *)(param_3 + 0x18) + lVar13;
            }
            if (*(char *)(lVar16 + 0x10) != '\x01') {
              uVar6 = Aska::RenderPass::GetShaderKeyFlags(Aska::RenderPassBatch const*)();
              Aska::ShaderNodeHandler::MakeZprepassShaderKey(int, Aska::ShaderContext*)(lVar16,uVar6,lVar2 + 0x10);
              if (*(char *)(lVar16 + 0x10) != '\x01') {
                return 0;
              }
            }
            if (((*(ushort *)(lVar2 + 0x245) >> 3 & 1) == 0) && (*(short *)(lVar2 + 0x238) == 0)) {
              bVar5 = (*(ushort *)(lVar2 + 0x245) & 0x2000) == 0;
            }
            else {
              bVar5 = true;
            }
            lVar11 = lVar11 + 1;
            lVar13 = lVar13 + 0x2a0;
            lVar2 = *(long *)(lVar7 + 8) + lVar15;
            bVar3 = *(byte *)(lVar2 + 0x58);
            lVar15 = lVar15 + 0x1b8;
            *(byte *)(lVar2 + 0x58) = bVar3 & 0xf8 | bVar3 & 3 | bVar5 << 2;
          } while (lVar11 < (long)(ulong)*(byte *)(param_1 + 0x7c));
        }
      }
      else if (*(char *)(param_1 + 0x7c) != '\0') {
        if (param_5 == 0) {
          lVar15 = 0;
          lVar11 = 0;
          lVar13 = 0x10;
          do {
            lVar2 = 0;
            if (*(long *)(param_3 + 0x18) != 0) {
              lVar2 = *(long *)(param_3 + 0x18) + lVar13;
            }
            lVar16 = *(long *)(*(long *)(param_2 + 8) + lVar15 + 0x20);
            lVar12 = *(long *)(*(long *)(lVar7 + 8) + lVar15 + 0x20);
            if ((*(byte *)(lVar2 + 0x245) >> 2 & 1) == 0) {
              uVar14 = *(undefined8 *)(lVar16 + 8);
              *(undefined1 *)(lVar12 + 0x10) = 0;
              *(undefined8 *)(lVar12 + 8) = uVar14;
              uVar6 = Aska::RenderPass::GetShaderKeyFlags(Aska::RenderPassBatch const*)();
              Aska::ShaderNodeHandler::MakeZprepassShaderKey(int, Aska::ShaderContext*)(lVar12,uVar6,lVar2 + 0x10);
              if (*(char *)(lVar12 + 0x10) != '\x01') {
                return 0;
              }
            }
            else if (*(char *)(lVar12 + 0x10) == '\0') {
              if (*(char *)(lVar16 + 0x11) == '\0') {
                uVar14 = 0;
                if (*(char *)(lVar16 + 0x12) != '\0') goto code_r0x022bfdf4;
code_r0x022bfe08:
                uVar9 = 0;
              }
              else {
                uVar14 = *(undefined8 *)(lVar16 + 0x18);
                if (*(char *)(lVar16 + 0x12) == '\0') goto code_r0x022bfe08;
code_r0x022bfdf4:
                uVar9 = *(undefined8 *)(lVar16 + 0x20);
              }
              Aska::ShaderNodeHandler::MakeSpecialZprepassShaderKey(unsigned char*, unsigned char*, bool, Aska::RENDERINFO::Zprepass)(lVar12,uVar14,uVar9,1,0);
              if (*(char *)(lVar12 + 0x10) != '\x03') {
                return 0;
              }
            }
            if (((*(ushort *)(lVar2 + 0x245) >> 3 & 1) == 0) && (*(short *)(lVar2 + 0x238) == 0)) {
              bVar5 = (*(ushort *)(lVar2 + 0x245) & 0x2000) == 0;
            }
            else {
              bVar5 = true;
            }
            lVar11 = lVar11 + 1;
            lVar13 = lVar13 + 0x2a0;
            lVar2 = *(long *)(lVar7 + 8) + lVar15;
            bVar3 = *(byte *)(lVar2 + 0x58);
            lVar15 = lVar15 + 0x1b8;
            *(byte *)(lVar2 + 0x58) = bVar3 & 0xf8 | bVar3 & 3 | bVar5 << 2;
          } while (lVar11 < (long)(ulong)*(byte *)(param_1 + 0x7c));
        }
        else {
          lVar15 = 0;
          lVar11 = 0;
          lVar13 = 0x10;
          do {
            lVar16 = *(long *)(*(long *)(lVar7 + 8) + lVar15 + 0x20);
            lVar2 = 0;
            if (*(long *)(param_3 + 0x18) != 0) {
              lVar2 = *(long *)(param_3 + 0x18) + lVar13;
            }
            if (*(char *)(lVar16 + 0x10) == '\0') {
              lVar12 = *(long *)(*(long *)(param_2 + 8) + lVar15 + 0x20);
              if (*(char *)(lVar12 + 0x11) == '\0') {
                uVar14 = 0;
                if (*(char *)(lVar12 + 0x12) != '\0') goto code_r0x022bfc30;
code_r0x022bfc44:
                uVar9 = 0;
              }
              else {
                uVar14 = *(undefined8 *)(lVar12 + 0x18);
                if (*(char *)(lVar12 + 0x12) == '\0') goto code_r0x022bfc44;
code_r0x022bfc30:
                uVar9 = *(undefined8 *)(lVar12 + 0x20);
              }
              Aska::ShaderNodeHandler::MakeSpecialZprepassShaderKey(unsigned char*, unsigned char*, bool, Aska::RENDERINFO::Zprepass)(lVar16,uVar14,uVar9,*(ushort *)(lVar2 + 0x245) >> 2 & 1,param_5);
              if (*(char *)(lVar16 + 0x10) != '\x03') {
                return 0;
              }
            }
            uVar4 = *(ushort *)(lVar2 + 0x245);
            if (((uVar4 >> 3 & 1) == 0) && (*(short *)(lVar2 + 0x238) == 0)) {
              bVar5 = (uVar4 & 0x2000) == 0;
            }
            else {
              bVar5 = true;
            }
            lVar11 = lVar11 + 1;
            lVar13 = lVar13 + 0x2a0;
            lVar2 = *(long *)(lVar7 + 8) + lVar15;
            bVar3 = *(byte *)(lVar2 + 0x58);
            lVar15 = lVar15 + 0x1b8;
            *(byte *)(lVar2 + 0x58) = bVar3 & 0xf8 | bVar3 & 3 | bVar5 << 2;
          } while (lVar11 < (long)(ulong)*(byte *)(param_1 + 0x7c));
        }
      }
    }
  }
  return lVar7;
}

// ==== Aska::RenderPassManager::GetVertexPass(Aska::RenderPass*)
// vaddr 0x21bfe94 | ghidra 0x22bfe94 | size 352 | symbol _ZN4Aska17RenderPassManager13GetVertexPassEPNS_10RenderPassE | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska17RenderPassManager13GetVertexPassEPNS_10RenderPassE(long param_1,long param_2)

{
  long *plVar1;
  undefined4 uVar2;
  long lVar3;
  ulong uVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  undefined8 uVar8;
  long lVar9;
  long lVar10;
  
  lVar3 = Aska::RenderPassManager::GetPass(int, int)(param_1,4,0);
  if (lVar3 != 0) {
    if ((*(ushort *)(lVar3 + 0x2f) >> 2 & 1) == 0) {
      uVar4 = Aska::RenderPass::Create(int)(lVar3,0);
      if ((uVar4 & 1) == 0) {
        return 0;
      }
      if (*(char *)(param_1 + 0x7c) != '\0') {
        lVar6 = 0;
        lVar7 = 0x20;
        do {
          lVar6 = lVar6 + 1;
          plVar1 = (long *)(*(long *)(param_2 + 8) + lVar7);
          lVar9 = *(long *)(*(long *)(lVar3 + 8) + lVar7);
          lVar7 = lVar7 + 0x1b8;
          uVar8 = *(undefined8 *)(*plVar1 + 8);
          *(undefined1 *)(lVar9 + 0x10) = 0;
          *(undefined8 *)(lVar9 + 8) = uVar8;
        } while (lVar6 < (long)(ulong)*(byte *)(param_1 + 0x7c));
      }
    }
    if (((*(ushort *)(lVar3 + 0x2f) >> 5 & 1) == 0) && (*(char *)(param_1 + 0x7c) != '\0')) {
      lVar7 = 0;
      lVar6 = 0;
      do {
        lVar9 = *(long *)(lVar3 + 8) + lVar7;
        lVar10 = *(long *)(lVar9 + 0x20);
        if (*(char *)(lVar10 + 0x10) != '\x03') {
          uVar8 = Aska::RenderPassBatch::GetAsmBitsSource() const(lVar9);
          uVar5 = Aska::RenderPassBatch::GetAsmBits() const(lVar9);
          uVar2 = Aska::RenderPass::GetShaderKeyFlags(Aska::RenderPassBatch const*)(lVar9);
          Aska::ShaderNodeHandler::MakeVertexPassShaderKey(unsigned long, unsigned long, int, Aska::ShaderConstantManager*)(lVar10,uVar8,uVar5,uVar2,lVar9);
          if (*(char *)(lVar10 + 0x10) != '\x03') {
            return 0;
          }
        }
        lVar6 = lVar6 + 1;
        lVar7 = lVar7 + 0x1b8;
        *(byte *)(lVar9 + 0x58) = *(byte *)(lVar9 + 0x58) | 2;
      } while (lVar6 < (long)(ulong)*(byte *)(param_1 + 0x7c));
    }
  }
  *(ushort *)(lVar3 + 0x2f) = *(ushort *)(lVar3 + 0x2f) | 0x800;
  return lVar3;
}

// ==== Aska::RenderPassManager::GetMultiDrawPass(Aska::RenderPass*, int)
// vaddr 0x21bfff4 | ghidra 0x22bfff4 | size 8 | symbol _ZN4Aska17RenderPassManager16GetMultiDrawPassEPNS_10RenderPassEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17RenderPassManager16GetMultiDrawPassEPNS_10RenderPassEi
               (undefined8 param_1,undefined8 param_2,undefined4 param_3)

{
  (*(code *)PTR__ZN4Aska17RenderPassManager34CreateShaderNodeMultiDrawModifiersEi_02ca22a8)
            (param_1,param_3);
  return;
}

// ==== Aska::RenderPassManager::CreateShaderNodeMultiDrawModifiers(int)
// vaddr 0x21bfffc | ghidra 0x22bfffc | size 188 | symbol _ZN4Aska17RenderPassManager34CreateShaderNodeMultiDrawModifiersEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska17RenderPassManager34CreateShaderNodeMultiDrawModifiersEi
               (long param_1,undefined4 param_2)

{
  byte bVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  
  lVar2 = Aska::RenderPassManager::GetPass(int, int)(param_1,6,param_2);
  if ((lVar2 != 0) && ((*(ushort *)(lVar2 + 0x2f) >> 2 & 1) == 0)) {
    bVar1 = *(byte *)(param_1 + 0x7c);
    uVar5 = (ulong)bVar1;
    lVar3 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 * 0x360,PTR__ZSt7nothrow_02cb9a80);
    if (lVar3 != 0) {
      uVar4 = Aska::RenderPass::Create(int)(lVar2,2);
      if ((uVar4 & 1) != 0) {
        *(long *)(lVar2 + 0x198) = lVar3;
        if (bVar1 == 0) {
          return lVar2;
        }
        lVar6 = 0x20;
        do {
          Aska::ShaderNodeModifier::Create(int, void*)(*(undefined8 *)(*(long *)(lVar2 + 8) + lVar6),0x360,lVar3);
          lVar3 = lVar3 + 0x360;
          uVar5 = uVar5 - 1;
          lVar6 = lVar6 + 0x1b8;
        } while (uVar5 != 0);
        return lVar2;
      }
      operator delete[](void*)(lVar3);
    }
    lVar2 = 0;
  }
  return lVar2;
}

// ==== Aska::RenderPassManager::CreateShaderNodeSystemModifiers(int)
// vaddr 0x21c00b8 | ghidra 0x22c00b8 | size 188 | symbol _ZN4Aska17RenderPassManager31CreateShaderNodeSystemModifiersEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska17RenderPassManager31CreateShaderNodeSystemModifiersEi(long param_1,undefined4 param_2)

{
  byte bVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  
  lVar2 = Aska::RenderPassManager::GetPass(int, int)(param_1,1,param_2);
  if ((lVar2 != 0) && ((*(ushort *)(lVar2 + 0x2f) >> 2 & 1) == 0)) {
    bVar1 = *(byte *)(param_1 + 0x7c);
    uVar5 = (ulong)bVar1;
    lVar3 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 * 0x360,PTR__ZSt7nothrow_02cb9a80);
    if (lVar3 != 0) {
      uVar4 = Aska::RenderPass::Create(int)(lVar2,2);
      if ((uVar4 & 1) != 0) {
        *(long *)(lVar2 + 0x198) = lVar3;
        if (bVar1 == 0) {
          return lVar2;
        }
        lVar6 = 0x20;
        do {
          Aska::ShaderNodeModifier::Create(int, void*)(*(undefined8 *)(*(long *)(lVar2 + 8) + lVar6),0x360,lVar3);
          lVar3 = lVar3 + 0x360;
          uVar5 = uVar5 - 1;
          lVar6 = lVar6 + 0x1b8;
        } while (uVar5 != 0);
        return lVar2;
      }
      operator delete[](void*)(lVar3);
    }
    lVar2 = 0;
  }
  return lVar2;
}


// FAILED to create function at 02c54118 Aska::RenderPass::vtable
// FAILED to create function at 02c54140 Aska::RenderPass::typeinfo
// FAILED to create function at 02c541d8 Aska::RenderPassManager::vtable
// FAILED to create function at 02c54200 Aska::RenderPassManager::typeinfo
// FAILED to create function at 02ce6ec0 Aska::RenderPass::m_ucSpecialAtCDither
// FAILED to create function at 02e10ac8 Aska::RenderPass::m_iSpecialLODBiasShift
// FAILED to create function at 02e10ad0 Aska::RenderPass::m_frameTextureRegisters
// FAILED to create function at 02e10d28 Aska::RenderPass::m_numFrameTextureRegisters
