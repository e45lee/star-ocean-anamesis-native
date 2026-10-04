// port/decomp/render/render_device_setters.c: Ghidra decompiles for the render subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 15:05 UTC: tools/decomp.sh '--into' 'render/render_device_setters' 'RenderDeviceGL::SetAlphaBlendFunction' 'RenderDeviceGL::SetZTestFunction' 'RenderDeviceData::SetCullMode' 'RenderDeviceGL::SetStencilOp' 'RenderDeviceGL::EnableZWrite'
// run      2026-10-04 15:06 UTC: tools/decomp.sh '--into' 'render/render_device_setters' 'RenderDeviceData::SetAlphaBlendFunction'

// ==== Aska::RenderDeviceGL::EnableZWrite(bool)
// vaddr 0x217a15c | ghidra 0x227a15c | size 188 | symbol _ZN4Aska14RenderDeviceGL12EnableZWriteEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL12EnableZWriteEb(long param_1,byte param_2)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  long lVar4;
  int *piVar5;
  long lVar6;
  
  lVar6 = *(long *)(*(long *)(param_1 + 0xeaa80) + 0x2b0);
  piVar5 = (int *)(lVar6 + 0x10);
  if (*piVar5 == 0) {
    do {
      if (*piVar5 != 0) {
        ClearExclusiveLocal();
        goto code_r0x0227a1c0;
      }
      cVar1 = '\x01';
      bVar2 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar2) {
        *piVar5 = 1;
        cVar1 = ExclusiveMonitorsStatus();
      }
    } while (cVar1 != '\0');
    iVar3 = pthread_key_create((undefined4 *)(lVar6 + 8),
                            PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8);
    if (iVar3 == 0) goto code_r0x0227a1c0;
  }
  else {
code_r0x0227a1c0:
    lVar4 = pthread_getspecific(*(undefined4 *)(lVar6 + 8));
    if (lVar4 != 0) goto joined_r0x0227a1cc;
  }
  lVar4 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar6);
joined_r0x0227a1cc:
  if (lVar4 != 0) {
    if ((param_2 & 1) == *(byte *)(lVar4 + 0x2ec)) {
      return;
    }
    *(byte *)(lVar4 + 0x2ec) = param_2 & 1;
  }
  (*(code *)PTR_glDepthMask_02c9b898)(param_2 & 1);
  return;
}

// ==== Aska::RenderDeviceGL::SetAlphaBlendFunction(Aska::AlphaBlend::Operation, Aska::SeparateAlphaBlendMode::E)
// vaddr 0x217dd74 | ghidra 0x227dd74 | size 16 | symbol _ZN4Aska14RenderDeviceGL21SetAlphaBlendFunctionENS_10AlphaBlend9OperationENS_22SeparateAlphaBlendMode1EE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL21SetAlphaBlendFunctionENS_10AlphaBlend9OperationENS_22SeparateAlphaBlendMode1EE
               (long param_1)

{
  (*(code *)
    PTR__ZN4Aska16RenderDeviceData21SetAlphaBlendFunctionENS_10AlphaBlend9OperationENS_22SeparateAlphaBlendMode1EE_02ca7660
  )(*(undefined8 *)(param_1 + 0xeaa80));
  return;
}

// ==== Aska::RenderDeviceData::SetAlphaBlendFunction(Aska::AlphaBlend::Operation, Aska::SeparateAlphaBlendMode::E)
// vaddr 0x217dd84 | ghidra 0x227dd84 | size 288 | symbol _ZN4Aska16RenderDeviceData21SetAlphaBlendFunctionENS_10AlphaBlend9OperationENS_22SeparateAlphaBlendMode1EE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderDeviceData21SetAlphaBlendFunctionENS_10AlphaBlend9OperationENS_22SeparateAlphaBlendMode1EE
               (long param_1,ulong param_2,int param_3)

{
  undefined4 uVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  long lVar5;
  int *piVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  long lVar9;
  
  param_2 = param_2 & 0xffffffff;
  if (param_3 == 2) {
    uVar8 = 1;
    uVar7 = 1;
  }
  else if (param_3 == 1) {
    uVar7 = *(undefined4 *)(&UNK_029cee68 + param_2 * 0x10);
    uVar8 = 0;
  }
  else {
    uVar7 = 0;
    uVar8 = 1;
  }
  lVar9 = *(long *)(param_1 + 0x2b0);
  piVar6 = (int *)(lVar9 + 0x10);
  if (*piVar6 == 0) {
    do {
      if (*piVar6 != 0) {
        ClearExclusiveLocal();
        goto code_r0x0227de14;
      }
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    iVar4 = pthread_key_create((undefined4 *)(lVar9 + 8),
                            PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8);
    if (iVar4 == 0) goto code_r0x0227de14;
  }
  else {
code_r0x0227de14:
    lVar5 = pthread_getspecific(*(undefined4 *)(lVar9 + 8));
    if (lVar5 != 0) goto code_r0x0227de28;
  }
  lVar5 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar9);
code_r0x0227de28:
  if (lVar5 == 0) {
    glBlendFuncSeparate(*(undefined4 *)(&UNK_029cee60 + param_2 * 0x10),
                    *(undefined4 *)(&UNK_029cee64 + param_2 * 0x10),uVar8,uVar7);
    (*(code *)PTR_glBlendEquationSeparate_02ca2e48)
              (*(undefined4 *)(&UNK_029cee6c + param_2 * 0x10),0x8006);
    return;
  }
  *(undefined4 *)(lVar5 + 0x344) = *(undefined4 *)(&UNK_029cee60 + param_2 * 0x10);
  *(undefined4 *)(lVar5 + 0x350) = uVar8;
  uVar8 = *(undefined4 *)(&UNK_029cee64 + param_2 * 0x10);
  uVar1 = *(undefined4 *)(&UNK_029cee6c + param_2 * 0x10);
  *(undefined4 *)(lVar5 + 0x354) = uVar7;
  *(undefined4 *)(lVar5 + 0x348) = uVar8;
  *(undefined4 *)(lVar5 + 0x34c) = uVar1;
  *(undefined4 *)(lVar5 + 0x358) = 0x8006;
  return;
}

// ==== Aska::RenderDeviceGL::SetZTestFunction(Aska::ZTest::Func)
// vaddr 0x217e33c | ghidra 0x227e33c | size 168 | symbol _ZN4Aska14RenderDeviceGL16SetZTestFunctionENS_5ZTest4FuncE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL16SetZTestFunctionENS_5ZTest4FuncE(long param_1,uint param_2)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  long lVar4;
  int *piVar5;
  long lVar6;
  
  if (7 < param_2) {
    return;
  }
  lVar6 = *(long *)(*(long *)(param_1 + 0xeaa80) + 0x2b0);
  piVar5 = (int *)(lVar6 + 0x10);
  if (*piVar5 == 0) {
    do {
      if (*piVar5 != 0) {
        ClearExclusiveLocal();
        goto code_r0x0227e3a0;
      }
      cVar1 = '\x01';
      bVar2 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar2) {
        *piVar5 = 1;
        cVar1 = ExclusiveMonitorsStatus();
      }
    } while (cVar1 != '\0');
    iVar3 = pthread_key_create((undefined4 *)(lVar6 + 8),
                            PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8);
    if (iVar3 == 0) goto code_r0x0227e3a0;
  }
  else {
code_r0x0227e3a0:
    lVar4 = pthread_getspecific(*(undefined4 *)(lVar6 + 8));
    if (lVar4 != 0) goto code_r0x0227e3b4;
  }
  lVar4 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar6);
code_r0x0227e3b4:
  if (lVar4 != 0) {
    *(undefined4 *)(lVar4 + 0x36c) = *(undefined4 *)(&UNK_029ce73c + (ulong)param_2 * 4);
    return;
  }
  (*(code *)PTR_glDepthFunc_02c94c00)(*(undefined4 *)(&UNK_029ce73c + (ulong)param_2 * 4));
  return;
}

// ==== Aska::RenderDeviceGL::SetStencilOp(Aska::StencilTest::Func, Aska::StencilOp::Operation, Aska::StencilOp::Operation, Aska::StencilOp::Operation, int)
// vaddr 0x217e54c | ghidra 0x227e54c | size 172 | symbol _ZN4Aska14RenderDeviceGL12SetStencilOpENS_11StencilTest4FuncENS_9StencilOp9OperationES4_S4_i | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL12SetStencilOpENS_11StencilTest4FuncENS_9StencilOp9OperationES4_S4_i
               (undefined8 param_1,uint param_2,uint param_3,uint param_4,uint param_5,
               undefined4 param_6)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (param_2 < 8) {
    uVar1 = *(undefined4 *)(&UNK_029ce73c + (ulong)param_2 * 4);
  }
  else {
    uVar1 = 0x207;
  }
  if (param_3 < 8) {
    uVar2 = *(undefined4 *)(&UNK_029ce75c + (ulong)param_3 * 4);
  }
  else {
    uVar2 = 0x1e00;
  }
  if (param_4 < 8) {
    uVar3 = *(undefined4 *)(&UNK_029ce75c + (ulong)param_4 * 4);
  }
  else {
    uVar3 = 0x1e00;
  }
  if (param_5 < 8) {
    uVar4 = *(undefined4 *)(&UNK_029ce75c + (ulong)param_5 * 4);
  }
  else {
    uVar4 = 0x1e00;
  }
  glStencilFuncSeparate(0x404,uVar1,param_6,0xffff);
  (*(code *)PTR_glStencilOpSeparate_02ca83e0)(0x404,uVar2,uVar3,uVar4);
  return;
}

// ==== Aska::RenderDeviceGL::SetStencilOpCCW(Aska::StencilTest::Func, Aska::StencilOp::Operation, Aska::StencilOp::Operation, Aska::StencilOp::Operation, int)
// vaddr 0x217e5f8 | ghidra 0x227e5f8 | size 172 | symbol _ZN4Aska14RenderDeviceGL15SetStencilOpCCWENS_11StencilTest4FuncENS_9StencilOp9OperationES4_S4_i | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL15SetStencilOpCCWENS_11StencilTest4FuncENS_9StencilOp9OperationES4_S4_i
               (undefined8 param_1,uint param_2,uint param_3,uint param_4,uint param_5,
               undefined4 param_6)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (param_2 < 8) {
    uVar1 = *(undefined4 *)(&UNK_029ce73c + (ulong)param_2 * 4);
  }
  else {
    uVar1 = 0x207;
  }
  if (param_3 < 8) {
    uVar2 = *(undefined4 *)(&UNK_029ce75c + (ulong)param_3 * 4);
  }
  else {
    uVar2 = 0x1e00;
  }
  if (param_4 < 8) {
    uVar3 = *(undefined4 *)(&UNK_029ce75c + (ulong)param_4 * 4);
  }
  else {
    uVar3 = 0x1e00;
  }
  if (param_5 < 8) {
    uVar4 = *(undefined4 *)(&UNK_029ce75c + (ulong)param_5 * 4);
  }
  else {
    uVar4 = 0x1e00;
  }
  glStencilFuncSeparate(0x405,uVar1,param_6,0xffff);
  (*(code *)PTR_glStencilOpSeparate_02ca83e0)(0x405,uVar2,uVar3,uVar4);
  return;
}

// ==== Aska::RenderDeviceData::SetCullMode(Aska::Cull::Mode)
// vaddr 0x217e7a4 | ghidra 0x227e7a4 | size 292 | symbol _ZN4Aska16RenderDeviceData11SetCullModeENS_4Cull4ModeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderDeviceData11SetCullModeENS_4Cull4ModeE(long param_1,uint param_2)

{
  ushort uVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  long lVar5;
  undefined8 uVar6;
  int *piVar7;
  undefined4 uVar8;
  long lVar9;
  
  if (2 < param_2) {
    return;
  }
  lVar9 = *(long *)(param_1 + 0x2b0);
  piVar7 = (int *)(lVar9 + 0x10);
  if (*piVar7 == 0) {
    do {
      if (*piVar7 != 0) {
        ClearExclusiveLocal();
        goto code_r0x0227e7fc;
      }
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    iVar4 = pthread_key_create((undefined4 *)(lVar9 + 8),
                            PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8);
    if (iVar4 == 0) goto code_r0x0227e7fc;
  }
  else {
code_r0x0227e7fc:
    lVar5 = pthread_getspecific(*(undefined4 *)(lVar9 + 8));
    if (lVar5 != 0) goto code_r0x0227e810;
  }
  lVar5 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar9);
code_r0x0227e810:
  iVar4 = *(int *)(PTR__ZZN4Aska16RenderDeviceData11SetCullModeENS_4Cull4ModeEE8iNewMode_02cc1bb0 +
                  (ulong)param_2 * 4);
  if (lVar5 == 0) {
    if (iVar4 == 2) {
      glEnable(0xb44);
      uVar6 = 0x901;
    }
    else {
      if (iVar4 != 1) {
        if (iVar4 != 0) {
          return;
        }
        (*(code *)PTR_glDisable_02cac210)(0xb44);
        return;
      }
      glEnable(0xb44);
      uVar6 = 0x900;
    }
    glFrontFace(uVar6);
    (*(code *)PTR_glCullFace_02cb4f68)(0x405);
    return;
  }
  if (iVar4 == 2) {
    uVar1 = *(ushort *)(lVar5 + 0x300);
    uVar8 = 0x901;
  }
  else {
    if (iVar4 != 1) {
      if (iVar4 != 0) {
        return;
      }
      *(ushort *)(lVar5 + 0x300) = *(ushort *)(lVar5 + 0x300) & 0xfffe;
      return;
    }
    uVar1 = *(ushort *)(lVar5 + 0x300);
    uVar8 = 0x900;
  }
  *(undefined4 *)(lVar5 + 0x30c) = uVar8;
  *(ushort *)(lVar5 + 0x300) = uVar1 | 1;
  *(undefined4 *)(lVar5 + 0x314) = 0x405;
  return;
}


// FAILED to create function at 029cef70 Aska::RenderDeviceData::SetCullMode(Aska::Cull::Mode)::iNewMode
