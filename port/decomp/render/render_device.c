// port/decomp/render/render_device.c: Ghidra decompiles for the render subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:39 UTC: tools/decomp.sh '--into' 'render/render_device' 'Aska::RenderDeviceGL::RenderDeviceGL\(' 'Aska::RenderDeviceGL::BindVertexFormat' 'Aska::RenderDeviceGL::BindTexture' 'Aska::RenderDeviceGL::ActiveTexture' 'Aska::RenderDeviceGL::RemoveTexture' 'Aska::RenderDeviceGL::SetTexture' 'Aska::RenderDeviceGL::BindVertexBuffer' 'Aska::RenderDeviceGL::SetScissorRect' 'Aska::RenderDeviceGL::Set(Pixel|Vertex)ShaderConstant' 'Aska::RenderDeviceGL::EnableStencil' 'Aska::RenderDeviceGL::SetDepthBias' 'Aska::RenderDeviceGL::EnableZTest' 'Aska::RenderDeviceGL::EnableZWrite' 'Aska::RenderDeviceGL::SetCullMode' 'Aska::RenderDeviceGL::EnableAlphaBlend' 'Aska::RenderDeviceGL::SetVertexShader\(' 'Aska::RenderDeviceGL::SetPixelShader\(' 'Aska::RenderDeviceData::DrawIndexedPrimitive' 'Aska::RenderDeviceData::UpdateShaderProgram' 'Aska::RenderDeviceData::GetTextureStateCaches' 'Aska::RenderDeviceData::UpdateVertexAttribute' 'Aska::RenderDeviceData::UpdateRenderState' 'Aska::RenderDeviceData::LastMinuteDrawCommands_Textures' 'Aska::RenderDeviceData::GetThreadOglState1' 'Aska::RenderDeviceData::GetBoundTextureID' 'Aska::RenderDeviceData::UpdateTextureFilters' 'Aska::RenderDeviceData::BindFrameBuffer' 'Aska::RenderDeviceData::RenderDeviceData\(' 'Aska::RenderDeviceGL::GetGLVersion'

// ==== Aska::RenderDeviceGL::BindTexture(unsigned int, unsigned int)
// vaddr 0x2174804 | ghidra 0x2274804 | size 256 | symbol _ZN4Aska14RenderDeviceGL11BindTextureEjj | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x022748e8: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x022748ec) */

void _ZN4Aska14RenderDeviceGL11BindTextureEjj(long param_1,int param_2,int param_3)

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
        goto code_r0x02274868;
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
    if (iVar3 == 0) goto code_r0x02274868;
  }
  else {
code_r0x02274868:
    lVar4 = pthread_getspecific(*(undefined4 *)(lVar6 + 8));
    if (lVar4 != 0) goto joined_r0x022748a8;
  }
  lVar4 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar6);
joined_r0x022748a8:
  if (lVar4 != 0) {
    if (param_2 == 0x806f) {
      lVar6 = lVar4 + 0x88;
    }
    else if (param_2 == 0x8513) {
      lVar6 = lVar4 + 0x48;
    }
    else {
      lVar6 = lVar4 + 8;
    }
    if (*(int *)(lVar6 + (ulong)*(byte *)(lVar4 + 200) * 4) == param_3) {
      return;
    }
  }
  (*(code *)PTR_glBindTexture_02cb45f8)(param_2,param_3);
  return;
}

// ==== Aska::RenderDeviceGL::GetGLVersion() const
// vaddr 0x2175964 | ghidra 0x2275964 | size 20 | symbol _ZNK4Aska14RenderDeviceGL12GetGLVersionEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska14RenderDeviceGL12GetGLVersionEv(long param_1)

{
  return *(undefined4 *)(*(long *)(param_1 + 0xeaa80) + 0x230);
}

// ==== Aska::RenderDeviceGL::RenderDeviceGL()
// vaddr 0x2176244 | ghidra 0x2276244 | size 192 | symbol _ZN4Aska14RenderDeviceGLC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGLC2Ev(long param_1)

{
  undefined1 *puVar1;
  long lVar2;
  
  Aska::RenderManagerBase::RenderManagerBase()();
  lVar2 = 0x80;
  puVar1 = (undefined1 *)(param_1 + 0xeaaf3);
  do {
    *(undefined2 *)(puVar1 + -0x2e) = 0;
    *(undefined2 *)(puVar1 + -2) = 0;
    puVar1[-0x2c] = 0;
    *puVar1 = 0;
    lVar2 = lVar2 + -2;
    puVar1 = puVar1 + 0x58;
  } while (lVar2 != 0);
  memset(param_1 + 0xeaa9c,0,0x1604);
  lVar2 = operator new(unsigned long, std::nothrow_t const&)(0xc6b0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar2 != 0) {
    Aska::RenderDeviceData::RenderDeviceData()(lVar2);
  }
  *(long *)(param_1 + 0xeaa80) = lVar2;
  *(undefined4 *)(param_1 + 0xeaa98) = 0x100;
  *(undefined8 *)(param_1 + 0xeaa90) = 0x3f8000003f800000;
  *(undefined4 *)(param_1 + 0xec0a0) = 0;
  *(undefined4 *)(param_1 + 0xec0a8) = 0;
  return;
}

// ==== Aska::RenderDeviceData::RenderDeviceData()
// vaddr 0x2176558 | ghidra 0x2276558 | size 1068 | symbol _ZN4Aska16RenderDeviceDataC2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16RenderDeviceDataC2Ev(long param_1)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined1 *puVar7;
  ulong uVar8;
  undefined1 *puVar9;
  ulong uVar11;
  ulong uVar12;
  ulong uVar13;
  undefined1 *puVar10;
  
  *(undefined2 *)(param_1 + 0x160) = 0x101;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x148) = 0;
  *(undefined8 *)(param_1 + 0x140) = 0;
  *(undefined8 *)(param_1 + 0x158) = 0;
  *(undefined8 *)(param_1 + 0x150) = 0;
  *(undefined8 *)(param_1 + 0x1b0) = 0;
  *(undefined8 *)(param_1 + 0x1a8) = 0;
  puVar5 = PTR__ZTVN4Aska9TPoolFastINS_15_RenderDeviceGL17TextureStateCacheELb0EEE_02cb7890;
  *(undefined8 *)(param_1 + 0x1a0) = 0;
  *(undefined8 *)(param_1 + 0x198) = 0;
  puVar6 = 
  PTR__ZTVN4Aska8THashMapIjPNS_15_RenderDeviceGL17TextureStateCacheENS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjS3_EEEEEE_02cc2970
  ;
  puVar1 = PTR__ZTVN4Aska9TBitArrayImLb0EEE_02cbeda0 + 0x10;
  *(undefined4 *)(param_1 + 0x1c8) = 0;
  *(undefined **)(param_1 + 0x1c0) = puVar1;
  *(undefined **)(param_1 + 0x1b8) = puVar5 + 0x10;
  *(undefined1 *)(param_1 + 0x1e0) = 0;
  *(undefined1 *)(param_1 + 0x1f9) = 0;
  *(undefined8 *)(param_1 + 0x1e8) = 0;
  *(undefined8 *)(param_1 + 0x1f0) = 0;
  *(undefined8 *)(param_1 + 0x1d0) = 0;
  *(undefined8 *)(param_1 + 0x1d8) = 0;
  *(undefined **)(param_1 + 0x200) = puVar6 + 0x10;
  *(undefined8 *)(param_1 + 0x20c) = 0x3f400000;
  *(undefined4 *)(param_1 + 0x214) = 0;
  puVar7 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0x6000,8);
  uVar8 = (ulong)(puVar7 != (undefined1 *)0x0);
  *(undefined1 **)(param_1 + 0x220) = puVar7;
  *(ulong *)(param_1 + 0x228) = uVar8 * 0x400;
  if (puVar7 != (undefined1 *)0x0) {
    uVar12 = (uVar8 * 0x6000 - 0x18) / 0x18 + 1;
    puVar10 = puVar7;
    if ((1 < uVar12) && (uVar11 = uVar12 & 0x1ffffffffffffffe, uVar11 != 0)) {
      uVar13 = uVar11;
      do {
        *puVar10 = 0;
        puVar10[0x18] = 0;
        uVar13 = uVar13 - 2;
        puVar10 = puVar10 + 0x30;
      } while (uVar13 != 0);
      puVar10 = puVar7 + uVar11 * 0x18;
      if (uVar12 == uVar11) goto code_r0x02276684;
    }
    do {
      puVar9 = puVar10 + 0x18;
      *puVar10 = 0;
      puVar10 = puVar9;
    } while (puVar7 + uVar8 * 0x6000 != puVar9);
  }
code_r0x02276684:
  *(undefined8 *)(param_1 + 0x230) = 0;
  *(undefined1 *)(param_1 + 0x238) = 1;
  Aska::Event::Event()(param_1 + 0x240);
  *(undefined4 *)(param_1 + 0x2a8) = 0;
  *(undefined8 *)(param_1 + 0x2b0) = 0;
  *(undefined **)(param_1 + 0x82b8) =
       PTR__ZTVN4Aska13TDynamicArrayINS_5TPairIPNS_11GpuResourceEjEENS_10TAllocatorIS4_EEEE_02cc2e20
       + 0x10;
  *(undefined8 *)(param_1 + 0x82d0) = 0;
  *(undefined8 *)(param_1 + 0x82c8) = 0;
  puVar1 = PTR__ZTVN4Aska13TDynamicArrayIPNS_14ShaderKeyValueENS_10TAllocatorIS2_EEEE_02cc0378;
  *(undefined8 *)(param_1 + 0x82c0) = 0;
  *(undefined **)(param_1 + 0x82e0) = puVar1 + 0x10;
  *(undefined8 *)(param_1 + 0x82f8) = 0;
  *(undefined8 *)(param_1 + 0x82f0) = 0;
  puVar1 = PTR__ZTVN4Aska13TDynamicArrayIPNS_18ShaderProgramValueENS_10TAllocatorIS2_EEEE_02cba350;
  *(undefined8 *)(param_1 + 0x82e8) = 0;
  *(undefined **)(param_1 + 0x8308) = puVar1 + 0x10;
  *(undefined8 *)(param_1 + 0x8320) = 0;
  *(undefined8 *)(param_1 + 0x8318) = 0;
  puVar1 = 
  PTR__ZTVN4Aska8THashSetIPNS_14ShaderKeyValueENS_16THasher_StateKeyIS2_EENS_17TEqualTo_StateKeyIS2_EENS_10TAllocatorIS2_EEEE_02cba260
  ;
  *(undefined8 *)(param_1 + 0x8310) = 0;
  *(undefined **)(param_1 + 0x8330) = puVar1 + 0x10;
  *(undefined8 *)(param_1 + 0x833c) = 0x3f400000;
  *(undefined4 *)(param_1 + 0x8344) = 0;
  puVar7 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0x110,8);
  *(undefined1 **)(param_1 + 0x8350) = puVar7;
  lVar2 = 0x11;
  if (puVar7 == (undefined1 *)0x0) {
    lVar2 = 0;
  }
  *(long *)(param_1 + 0x8358) = lVar2;
  if (puVar7 != (undefined1 *)0x0) {
    uVar8 = (lVar2 * 0x10 - 0x10U >> 4) + 1;
    puVar10 = puVar7;
    if ((1 < uVar8) && (uVar12 = uVar8 & 0x1ffffffffffffffe, uVar12 != 0)) {
      puVar10 = puVar7 + 0x10;
      uVar11 = uVar12;
      do {
        puVar10[-0x10] = 0;
        *puVar10 = 0;
        uVar11 = uVar11 - 2;
        puVar10 = puVar10 + 0x20;
      } while (uVar11 != 0);
      puVar10 = puVar7 + uVar12 * 0x10;
      if (uVar8 == uVar12) goto code_r0x022767dc;
    }
    do {
      puVar9 = puVar10 + 0x10;
      *puVar10 = 0;
      puVar10 = puVar9;
    } while (puVar7 + lVar2 * 0x10 != puVar9);
  }
code_r0x022767dc:
  *(undefined4 *)(param_1 + 0x8378) = 0;
  *(undefined8 *)(param_1 + 0x8370) = 0;
  puVar1 = PTR__ZTVN4Aska13TDynamicArrayIhNS_10TAllocatorIhEEEE_02cc3768;
  *(undefined8 *)(param_1 + 0x8368) = 0;
  *(undefined **)(param_1 + 0x8380) = puVar1 + 0x10;
  *(undefined8 *)(param_1 + 0x8398) = 0;
  *(undefined8 *)(param_1 + 0x8390) = 0;
  puVar1 = 
  PTR__ZTVN4Aska8THashSetIPNS_18ShaderProgramValueENS_16THasher_StateKeyIS2_EENS_17TEqualTo_StateKeyIS2_EENS_10TAllocatorIS2_EEEE_02cc0ab0
  ;
  *(undefined8 *)(param_1 + 0x8388) = 0;
  *(undefined **)(param_1 + 0x83a8) = puVar1 + 0x10;
  *(undefined8 *)(param_1 + 0x83b4) = 0x3f400000;
  *(undefined4 *)(param_1 + 0x83bc) = 0;
  puVar7 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0x110,8);
  *(undefined1 **)(param_1 + 0x83c8) = puVar7;
  lVar2 = 0x11;
  if (puVar7 == (undefined1 *)0x0) {
    lVar2 = 0;
  }
  *(long *)(param_1 + 0x83d0) = lVar2;
  if (puVar7 != (undefined1 *)0x0) {
    uVar8 = (lVar2 * 0x10 - 0x10U >> 4) + 1;
    puVar10 = puVar7;
    if ((1 < uVar8) && (uVar12 = uVar8 & 0x1ffffffffffffffe, uVar12 != 0)) {
      puVar10 = puVar7 + 0x10;
      uVar11 = uVar12;
      do {
        puVar10[-0x10] = 0;
        *puVar10 = 0;
        uVar11 = uVar11 - 2;
        puVar10 = puVar10 + 0x20;
      } while (uVar11 != 0);
      puVar10 = puVar7 + uVar12 * 0x10;
      if (uVar8 == uVar12) goto code_r0x011c68b0;
    }
    do {
      puVar9 = puVar10 + 0x10;
      *puVar10 = 0;
      puVar10 = puVar9;
    } while (puVar7 + lVar2 * 0x10 != puVar9);
  }
code_r0x011c68b0:
  *(undefined4 *)(param_1 + 0x83f0) = 0;
  *(undefined8 *)(param_1 + 0x83e8) = 0;
  *(undefined8 *)(param_1 + 0x83e0) = 0;
  *(undefined4 *)(param_1 + 0x8410) = 0;
  *(undefined8 *)(param_1 + 0x8408) = 0;
  *(undefined8 *)(param_1 + 0x8400) = 0;
  *(undefined8 *)(param_1 + 0x83f8) = 0;
  *(undefined8 *)(param_1 + 0x170) = 0;
  *(undefined8 *)(param_1 + 0x168) = 0;
  memset(param_1 + 0x30,0,0x110);
  memset(param_1 + 0x8418,0,0x44);
  *(undefined8 *)(param_1 + 0xc6a8) = 0;
  *(undefined8 *)(param_1 + 0xc6a0) = 0;
  uVar4 = _UNK_029cd0d8;
  uVar3 = _UNK_029cd0d0;
  *(undefined4 *)PTR__ZN4Aska15s_GL_HALF_FLOATE_02cbe908 = 0x140b;
  *(undefined4 *)(param_1 + 0x230) = 2;
  *(undefined4 *)(param_1 + 400) = 0;
  *(undefined8 *)(param_1 + 0x188) = uVar4;
  *(undefined8 *)(param_1 + 0x180) = uVar3;
  memset(param_1 + 0x2b8,0,0x8000);
  (*(code *)PTR__ZN4Aska5Event6CreateEbb_02c9b448)(param_1 + 0x240,0,0);
  return;
}

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

// ==== Aska::RenderDeviceData::BindFrameBuffer(Aska::GpuResource*)
// vaddr 0x217a4cc | ghidra 0x227a4cc | size 296 | symbol _ZN4Aska16RenderDeviceData15BindFrameBufferEPNS_11GpuResourceE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderDeviceData15BindFrameBufferEPNS_11GpuResourceE(long param_1,long param_2)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  ulong uVar4;
  long lVar5;
  int *piVar6;
  int iVar7;
  long lVar8;
  
  if (param_2 == 0) {
code_r0x0227a510:
    uVar4 = 0;
  }
  else if ((*(int *)(param_2 + 0x68) != 0) || (uVar4 = *(ulong *)(param_2 + 0x48), uVar4 == 0)) {
    uVar4 = (**(code **)**(undefined8 **)(param_2 + 0x40))(*(undefined8 **)(param_2 + 0x40),param_2)
    ;
    if ((uVar4 & 1) == 0) goto code_r0x0227a510;
    uVar4 = *(ulong *)(param_2 + 0x48);
    *(undefined4 *)(param_2 + 0x68) = 0;
  }
  lVar8 = *(long *)(param_1 + 0x2b0);
  piVar6 = (int *)(lVar8 + 0x10);
  iVar7 = (int)uVar4;
  if (*piVar6 == 0) {
    do {
      if (*piVar6 != 0) {
        ClearExclusiveLocal();
        goto code_r0x0227a564;
      }
      cVar1 = '\x01';
      bVar2 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar2) {
        *piVar6 = 1;
        cVar1 = ExclusiveMonitorsStatus();
      }
    } while (cVar1 != '\0');
    iVar3 = pthread_key_create((undefined4 *)(lVar8 + 8),
                            PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8);
    if (iVar3 == 0) goto code_r0x0227a564;
  }
  else {
code_r0x0227a564:
    lVar5 = pthread_getspecific(*(undefined4 *)(lVar8 + 8));
    if (lVar5 != 0) goto joined_r0x0227a5b4;
  }
  lVar5 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar8);
joined_r0x0227a5b4:
  if (lVar5 == 0) {
    glBindFramebuffer(0x8d40,uVar4 & 0xffffffff);
  }
  else if (*(int *)(lVar5 + 0xd4) != iVar7) {
    glBindFramebuffer(0x8d40,uVar4 & 0xffffffff);
    *(int *)(lVar5 + 0xd4) = iVar7;
    memset(lVar5 + 0xdc,0xff,0x90);
  }
  if (*(int *)(param_1 + 0x2c) != iVar7) {
    memset(param_1 + 0x30,0,0x110);
    *(int *)(param_1 + 0x2c) = iVar7;
  }
  return;
}

// ==== Aska::RenderDeviceGL::ActiveTexture(unsigned int)
// vaddr 0x217ad24 | ghidra 0x227ad24 | size 224 | symbol _ZN4Aska14RenderDeviceGL13ActiveTextureEj | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0227adc4: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0227adc8) */

void _ZN4Aska14RenderDeviceGL13ActiveTextureEj(long param_1,uint param_2)

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
        goto code_r0x0227ad88;
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
    if (iVar3 == 0) goto code_r0x0227ad88;
  }
  else {
code_r0x0227ad88:
    lVar4 = pthread_getspecific(*(undefined4 *)(lVar6 + 8));
    if (lVar4 != 0) goto joined_r0x0227ade8;
  }
  lVar4 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar6);
joined_r0x0227ade8:
  if (lVar4 != 0) {
    if ((*(uint *)(param_1 + 0xeaa88) <= param_2) ||
       ((uint)*(byte *)(lVar4 + 200) == (param_2 & 0xff))) {
      return;
    }
  }
  (*(code *)PTR_glActiveTexture_02ca3148)(param_2 + 0x84c0);
  return;
}

// ==== Aska::RenderDeviceGL::BindVertexFormat(Aska::VertexBuffer*)
// vaddr 0x217b138 | ghidra 0x227b138 | size 128 | symbol _ZN4Aska14RenderDeviceGL16BindVertexFormatEPNS_12VertexBufferE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL16BindVertexFormatEPNS_12VertexBufferE
               (undefined8 param_1,undefined4 *param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_2 + 2);
  if (lVar3 != 0) {
    if (((*(int *)(lVar3 + 0x68) != 0) || (*(long *)(lVar3 + 0x48) == 0)) &&
       (uVar1 = (**(code **)**(undefined8 **)(lVar3 + 0x40))(*(undefined8 **)(lVar3 + 0x40),lVar3),
       (uVar1 & 1) != 0)) {
      *(undefined4 *)(lVar3 + 0x68) = 0;
    }
    if (*(long *)(*(long *)(param_2 + 2) + 0x48) != 0) {
      uVar2 = 0;
      goto code_r0x011c8ef0;
    }
  }
  uVar2 = Aska::VertexBuffer::GetData(int) const(param_2,1);
code_r0x011c8ef0:
  (*(code *)PTR__ZN4Aska14RenderDeviceGL16BindVertexFormatEiiPv_02c9c768)
            (param_1,*param_2,*(undefined1 *)(param_2 + 0x19),uVar2);
  return;
}

// ==== Aska::RenderDeviceGL::BindVertexFormat(int, int, void*)
// vaddr 0x217b1b8 | ghidra 0x227b1b8 | size 912 | symbol _ZN4Aska14RenderDeviceGL16BindVertexFormatEiiPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL16BindVertexFormatEiiPv
               (long param_1,int param_2,undefined4 param_3,long param_4)

{
  long *plVar1;
  byte *pbVar2;
  uint uVar3;
  byte bVar4;
  undefined1 uVar5;
  char cVar6;
  bool bVar7;
  undefined *puVar8;
  int iVar9;
  long lVar10;
  uint uVar11;
  long lVar12;
  int *piVar13;
  uint uVar14;
  long lVar15;
  ulong uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined8 uVar19;
  long lVar20;
  
  puVar8 = PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8;
  plVar1 = (long *)(param_1 + 0xeaa80);
  lVar12 = *plVar1;
  lVar20 = (long)param_2;
  lVar15 = *(long *)(lVar12 + 0x8418);
  if (*(int *)(lVar12 + 0x2a8) != 0) {
    uVar16 = 0;
    do {
      lVar12 = *(long *)(lVar12 + 0x2b0);
      piVar13 = (int *)(lVar12 + 0x10);
      if (*piVar13 == 0) {
        do {
          if (*piVar13 != 0) {
            ClearExclusiveLocal();
            goto code_r0x0227b254;
          }
          cVar6 = '\x01';
          bVar7 = (bool)ExclusiveMonitorPass(piVar13,0x10);
          if (bVar7) {
            *piVar13 = 1;
            cVar6 = ExclusiveMonitorsStatus();
          }
        } while (cVar6 != '\0');
        iVar9 = pthread_key_create((undefined4 *)(lVar12 + 8),puVar8);
        if (iVar9 == 0) goto code_r0x0227b254;
code_r0x0227b270:
        lVar10 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar12);
        if (lVar10 != 0) goto code_r0x0227b264;
code_r0x0227b27c:
        glDisableVertexAttribArray(uVar16 & 0xffffffff);
      }
      else {
code_r0x0227b254:
        lVar10 = pthread_getspecific(*(undefined4 *)(lVar12 + 8));
        if (lVar10 == 0) goto code_r0x0227b270;
        if (lVar10 == 0) goto code_r0x0227b27c;
code_r0x0227b264:
        *(undefined1 *)(lVar10 + uVar16 + 0x38c) = 0;
      }
      lVar12 = *plVar1;
      uVar16 = uVar16 + 1;
    } while (uVar16 < *(uint *)(lVar12 + 0x2a8));
  }
  pbVar2 = (byte *)(param_1 + lVar20 * 0x2c + 0xeaac4);
  bVar4 = *pbVar2;
  uVar11 = (uint)bVar4;
  if (bVar4 != 0) {
    uVar14 = 0;
    do {
      lVar12 = param_1 + lVar20 * 0x2c + (ulong)uVar14 * 4;
      uVar3 = *(uint *)(lVar15 + (ulong)*(byte *)(lVar12 + 0xeaa9e) * 0x20 +
                        (ulong)*(byte *)(lVar12 + 0xeaa9f) * 4 + 0x48);
      if ((int)uVar3 < 0) goto code_r0x0227b51c;
      uVar5 = *(undefined1 *)(param_1 + lVar20 * 0x2c + (ulong)uVar14 * 4 + 0xeaa9d);
      uVar17 = 0;
      uVar18 = 1;
      uVar19 = 0x1406;
      switch(uVar5) {
      case 1:
        break;
      case 2:
        uVar17 = 0;
        uVar18 = 2;
        uVar19 = 0x1406;
        break;
      case 3:
        uVar17 = 0;
        uVar18 = 3;
        uVar19 = 0x1406;
        break;
      case 4:
        uVar17 = 0;
        uVar18 = 4;
        uVar19 = 0x1406;
        break;
      default:
        if (*(int *)(*(long *)(*(long *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0 + 0xeaa80) + 0x230) !=
            0) {
          uVar17 = 0;
          uVar18 = 4;
          uVar19 = 0x140b;
          switch(uVar5) {
          case 5:
            uVar17 = 0;
            uVar18 = 2;
            uVar19 = 0x140b;
            break;
          case 6:
            break;
          default:
            goto code_r0x0227b51c;
          case 0x17:
            uVar17 = 0;
            uVar18 = 4;
            uVar19 = 0x8368;
            break;
          case 0x18:
            uVar17 = 0;
            uVar18 = 4;
            uVar19 = 0x8d9f;
          }
          break;
        }
        goto code_r0x0227b51c;
      case 8:
        uVar17 = 0;
        goto code_r0x0227b418;
      case 9:
        uVar17 = 1;
        uVar18 = 2;
        uVar19 = 0x1402;
        break;
      case 10:
        uVar17 = 1;
code_r0x0227b418:
        uVar18 = 4;
        uVar19 = 0x1402;
        break;
      case 0xb:
        uVar17 = 0;
        goto code_r0x0227b438;
      case 0xc:
        uVar17 = 0;
        goto code_r0x0227b448;
      case 0xd:
        uVar17 = 1;
code_r0x0227b438:
        uVar18 = 2;
        uVar19 = 0x1403;
        break;
      case 0xe:
        uVar17 = 1;
code_r0x0227b448:
        uVar18 = 4;
        uVar19 = 0x1403;
        break;
      case 0xf:
        uVar17 = 0;
        goto code_r0x0227b458;
      case 0x10:
      case 0x1d:
        uVar17 = 1;
code_r0x0227b458:
        uVar18 = 4;
        uVar19 = 0x1401;
      }
      lVar12 = *(long *)(*plVar1 + 0x2b0);
      piVar13 = (int *)(lVar12 + 0x10);
      if (*piVar13 == 0) {
        do {
          if (*piVar13 != 0) {
            ClearExclusiveLocal();
            goto code_r0x0227b4a8;
          }
          cVar6 = '\x01';
          bVar7 = (bool)ExclusiveMonitorPass(piVar13,0x10);
          if (bVar7) {
            *piVar13 = 1;
            cVar6 = ExclusiveMonitorsStatus();
          }
        } while (cVar6 != '\0');
        iVar9 = pthread_key_create((undefined4 *)(lVar12 + 8),
                                PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8
                               );
        if (iVar9 == 0) goto code_r0x0227b4a8;
code_r0x0227b4c4:
        lVar10 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar12);
        if (lVar10 != 0) goto code_r0x0227b4b8;
code_r0x0227b4d0:
        glEnableVertexAttribArray(uVar3);
      }
      else {
code_r0x0227b4a8:
        lVar10 = pthread_getspecific(*(undefined4 *)(lVar12 + 8));
        if (lVar10 == 0) goto code_r0x0227b4c4;
        if (lVar10 == 0) goto code_r0x0227b4d0;
code_r0x0227b4b8:
        *(undefined1 *)(lVar10 + (ulong)uVar3 + 0x38c) = 1;
      }
      glVertexAttribPointer((ulong)uVar3,uVar18,uVar19,uVar17,param_3,
                      param_4 + (ulong)*(byte *)(param_1 + lVar20 * 0x2c + (ulong)uVar14 * 4 +
                                                0xeaa9c));
      uVar11 = (uint)*pbVar2;
code_r0x0227b51c:
      uVar14 = uVar14 + 1;
    } while (uVar14 < uVar11);
  }
  return;
}

// ==== Aska::RenderDeviceGL::SetTexture(unsigned int, Aska::GpuResource* const*)
// vaddr 0x217b548 | ghidra 0x227b548 | size 592 | symbol _ZN4Aska14RenderDeviceGL10SetTextureEjPKPNS_11GpuResourceE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL10SetTextureEjPKPNS_11GpuResourceE
               (long param_1,uint param_2,long *param_3)

{
  uint *puVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  ulong uVar5;
  long lVar6;
  undefined4 uVar7;
  int *piVar8;
  uint uVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  
  if (*(uint *)(param_1 + 0xeaa88) <= param_2) {
    return;
  }
  if (param_3 == (long *)0x0) {
    lVar10 = *(long *)(*(long *)(param_1 + 0xeaa80) + 0x2b0);
    piVar8 = (int *)(lVar10 + 0x10);
    if (*piVar8 == 0) {
      do {
        if (*piVar8 != 0) {
          ClearExclusiveLocal();
          goto code_r0x0227b69c;
        }
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar3) {
          *piVar8 = 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      iVar4 = pthread_key_create((undefined4 *)(lVar10 + 8),
                              PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8
                             );
      if (iVar4 == 0) goto code_r0x0227b69c;
    }
    else {
code_r0x0227b69c:
      lVar11 = pthread_getspecific(*(undefined4 *)(lVar10 + 8));
      if (lVar11 != 0) goto code_r0x0227b6b0;
    }
    lVar11 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar10);
code_r0x0227b6b0:
    if (lVar11 == 0) {
      return;
    }
    lVar11 = lVar11 + (ulong)param_2 * 4;
    *(undefined4 *)(lVar11 + 8) = 0;
    *(undefined4 *)(lVar11 + 0x48) = 0;
    *(undefined4 *)(lVar11 + 0x88) = 0;
    return;
  }
  lVar10 = *param_3;
  if (((*(int *)(lVar10 + 0x68) != 0) || (*(long *)(lVar10 + 0x48) == 0)) &&
     (uVar5 = (**(code **)**(undefined8 **)(lVar10 + 0x40))(*(undefined8 **)(lVar10 + 0x40),lVar10),
     (uVar5 & 1) != 0)) {
    *(undefined4 *)(lVar10 + 0x68) = 0;
  }
  lVar10 = *param_3;
  lVar11 = *(long *)(param_1 + 0xeaa80);
  if ((lVar10 != 0) && ((*(int *)(lVar10 + 0x68) != 0 || (*(long *)(lVar10 + 0x48) == 0)))) {
    uVar5 = (**(code **)**(undefined8 **)(lVar10 + 0x40))(*(undefined8 **)(lVar10 + 0x40),lVar10);
    if ((uVar5 & 1) == 0) {
      return;
    }
    *(undefined4 *)(lVar10 + 0x68) = 0;
  }
  uVar9 = (uint)*(undefined8 *)(lVar10 + 0x48);
  if (0x3ff < uVar9) {
    return;
  }
  lVar12 = (long)(int)uVar9;
  lVar10 = *(long *)(*(long *)(param_1 + 0xeaa80) + 0x2b0);
  piVar8 = (int *)(lVar10 + 0x10);
  if (*piVar8 == 0) {
    do {
      if (*piVar8 != 0) {
        ClearExclusiveLocal();
        goto code_r0x0227b6cc;
      }
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar3) {
        *piVar8 = 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    iVar4 = pthread_key_create((undefined4 *)(lVar10 + 8),
                            PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8);
    if (iVar4 == 0) goto code_r0x0227b6cc;
code_r0x0227b6dc:
    lVar6 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar10);
  }
  else {
code_r0x0227b6cc:
    lVar6 = pthread_getspecific(*(undefined4 *)(lVar10 + 8));
    if (lVar6 == 0) goto code_r0x0227b6dc;
  }
  puVar1 = (uint *)(lVar11 + lVar12 * 0x20 + 0x2b8);
  if (lVar6 != 0) {
    uVar9 = *puVar1;
    if ((uVar9 >> 2 & 1) == 0) {
      if ((uVar9 >> 4 & 1) == 0) {
        lVar10 = lVar6 + 8;
      }
      else {
        lVar10 = lVar6 + 0x88;
      }
    }
    else {
      lVar10 = lVar6 + 0x48;
    }
    if (*(int *)(lVar10 + (ulong)param_2 * 4) == *(int *)(lVar11 + lVar12 * 0x20 + 0x2c4))
    goto code_r0x0227b768;
  }
  Aska::RenderDeviceGL::ActiveTexture(unsigned int)(param_1,param_2);
  uVar9 = *puVar1;
  if ((uVar9 >> 2 & 1) == 0) {
    uVar7 = 0xde1;
    if ((uVar9 & 0x10) != 0) {
      uVar7 = 0x806f;
    }
  }
  else {
    uVar7 = 0x8513;
  }
  Aska::RenderDeviceGL::BindTexture(unsigned int, unsigned int)(param_1,uVar7,*(undefined4 *)(lVar11 + lVar12 * 0x20 + 0x2c4));
  if (lVar6 == 0) {
    return;
  }
code_r0x0227b768:
  *(byte *)(lVar6 + (ulong)param_2 * 0x18 + 0x180) = *(byte *)(lVar11 + lVar12 * 0x20 + 0x2d0) & 1;
  return;
}

// ==== Aska::RenderDeviceGL::RemoveTexture(unsigned int)
// vaddr 0x217b798 | ghidra 0x227b798 | size 164 | symbol _ZN4Aska14RenderDeviceGL13RemoveTextureEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL13RemoveTextureEj(long param_1,uint param_2)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  long lVar4;
  int *piVar5;
  long lVar6;
  
  if (*(uint *)(param_1 + 0xeaa88) <= param_2) {
    return;
  }
  lVar6 = *(long *)(*(long *)(param_1 + 0xeaa80) + 0x2b0);
  piVar5 = (int *)(lVar6 + 0x10);
  if (*piVar5 == 0) {
    do {
      if (*piVar5 != 0) {
        ClearExclusiveLocal();
        goto code_r0x0227b808;
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
    if (iVar3 == 0) goto code_r0x0227b808;
  }
  else {
code_r0x0227b808:
    lVar4 = pthread_getspecific(*(undefined4 *)(lVar6 + 8));
    if (lVar4 != 0) goto code_r0x0227b81c;
  }
  lVar4 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar6);
code_r0x0227b81c:
  if (lVar4 != 0) {
    lVar4 = lVar4 + (ulong)param_2 * 4;
    *(undefined4 *)(lVar4 + 8) = 0;
    *(undefined4 *)(lVar4 + 0x48) = 0;
    *(undefined4 *)(lVar4 + 0x88) = 0;
  }
  return;
}

// ==== Aska::RenderDeviceGL::SetScissorRect(RECT const*, bool)
// vaddr 0x217cd0c | ghidra 0x227cd0c | size 564 | symbol _ZN4Aska14RenderDeviceGL14SetScissorRectEPK4RECTb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0227ceb0: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0227ceb4) */

void _ZN4Aska14RenderDeviceGL14SetScissorRectEPK4RECTb(long param_1,int *param_2,uint param_3)

{
  long *plVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  ushort uVar7;
  char cVar8;
  bool bVar9;
  float fVar10;
  uint uVar11;
  int iVar12;
  long lVar13;
  int *piVar14;
  long lVar15;
  float fVar16;
  float fVar17;
  
  iVar2 = param_2[2];
  iVar4 = param_2[3];
  iVar3 = *param_2;
  iVar5 = param_2[1];
  lVar15 = *(long *)PTR__ZN4Aska6Global22m_pRenderTargetManagerE_02cbfa00;
  uVar11 = Aska::RenderTargetManagerGL::GetRtHeight(Aska::RenderTarget*)(lVar15,*(undefined8 *)(lVar15 + 0x20));
  fVar17 = 1.0;
  fVar16 = 1.0;
  if (*(long *)(lVar15 + 0x20) == 0) {
    fVar16 = fVar17;
    if (*PTR__ZN4Aska6Global23m_bIsExecuteFrontScaledE_02cc0788 == '\0') {
      fVar17 = (float)NEON_ucvtf((uint)uRam0000000002dd0760);
      uVar7 = *(ushort *)(*(long *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198 + 0x1a);
      uVar11 = (uint)uVar7;
      fVar16 = (float)NEON_ucvtf((uint)uRam0000000002dd0764);
      fVar10 = (float)NEON_ucvtf((uint)*(ushort *)
                                        (*(long *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198 +
                                        0x18));
      fVar17 = fVar17 / fVar10;
      fVar16 = fVar16 / (float)uVar7;
    }
  }
  else {
    fVar17 = 1.0;
  }
  plVar1 = (long *)(param_1 + 0xeaa80);
  iVar6 = param_2[3];
  lVar15 = *(long *)(*plVar1 + 0x2b0);
  piVar14 = (int *)(lVar15 + 0x10);
  if (*piVar14 == 0) {
    do {
      if (*piVar14 != 0) {
        ClearExclusiveLocal();
        goto code_r0x0227ce14;
      }
      cVar8 = '\x01';
      bVar9 = (bool)ExclusiveMonitorPass(piVar14,0x10);
      if (bVar9) {
        *piVar14 = 1;
        cVar8 = ExclusiveMonitorsStatus();
      }
    } while (cVar8 != '\0');
    iVar12 = pthread_key_create((undefined4 *)(lVar15 + 8),
                             PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8)
    ;
    if (iVar12 == 0) goto code_r0x0227ce14;
  }
  else {
code_r0x0227ce14:
    lVar13 = pthread_getspecific(*(undefined4 *)(lVar15 + 8));
    if (lVar13 != 0) goto code_r0x0227ce30;
  }
  lVar13 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar15);
code_r0x0227ce30:
  if (lVar13 == 0) {
    Aska::RenderDeviceData::EnableScissorTest(bool)(*plVar1,1);
  }
  else {
    if ((((iVar3 == *(int *)(lVar13 + 0x3cc)) && (uVar11 - iVar6 == *(int *)(lVar13 + 0x3d0))) &&
        (iVar2 - iVar3 == *(int *)(lVar13 + 0x3d4))) &&
       ((iVar4 - iVar5 == *(int *)(lVar13 + 0x3d8) && ((param_3 & 1) == 0)))) {
      return;
    }
    Aska::RenderDeviceData::EnableScissorTest(bool)(*plVar1,1);
  }
  (*(code *)PTR_glScissor_02c9f218)
            ((int)(fVar17 * (float)iVar3),(int)(fVar16 * (float)(int)(uVar11 - iVar6)),
             (int)(fVar17 * (float)(iVar2 - iVar3)),(int)(fVar16 * (float)(iVar4 - iVar5)));
  return;
}

// ==== Aska::RenderDeviceData::DrawIndexedPrimitive(Aska::RenderDeviceGL*, Aska::PrimType::Type, Aska::IndexBuffer&, unsigned long, int)
// vaddr 0x217d0f8 | ghidra 0x227d0f8 | size 704 | symbol _ZN4Aska16RenderDeviceData20DrawIndexedPrimitiveEPNS_14RenderDeviceGLENS_8PrimType4TypeERNS_11IndexBufferEmi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0227d20c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0227d368: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0227d220: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0227d210) */
/* WARNING: Removing unreachable block (ram,0x0227d36c) */

void _ZN4Aska16RenderDeviceData20DrawIndexedPrimitiveEPNS_14RenderDeviceGLENS_8PrimType4TypeERNS_11IndexBufferEmi
               (long param_1,undefined8 param_2,ulong param_3,long *param_4,long param_5,
               undefined4 param_6)

{
  undefined4 uVar1;
  char cVar2;
  undefined *puVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  ulong uVar7;
  int *piVar8;
  undefined4 uVar9;
  long lVar10;
  long lVar11;
  
  if (*(char *)(param_1 + 0x160) == '\0') {
    return;
  }
  uVar7 = Aska::RenderDeviceData::UpdateRenderState(Aska::RenderDeviceGL*)(param_1);
  puVar3 = PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  if ((uVar7 & 1) == 0) {
    return;
  }
  lVar10 = *param_4;
  lVar11 = *(long *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  iVar6 = 0;
  if (lVar10 != 0) {
    if (((*(int *)(lVar10 + 0x68) != 0) || (*(long *)(lVar10 + 0x48) == 0)) &&
       (uVar7 = (**(code **)**(undefined8 **)(lVar10 + 0x40))
                          (*(undefined8 **)(lVar10 + 0x40),lVar10), (uVar7 & 1) != 0)) {
      *(undefined4 *)(lVar10 + 0x68) = 0;
    }
    iVar6 = *(int *)(*param_4 + 0x48);
  }
  lVar10 = *(long *)(*(long *)(lVar11 + 0xeaa80) + 0x2b0);
  piVar8 = (int *)(lVar10 + 0x10);
  if (*piVar8 == 0) {
    do {
      if (*piVar8 != 0) {
        ClearExclusiveLocal();
        goto code_r0x0227d1d0;
      }
      cVar2 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar4) {
        *piVar8 = 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    iVar5 = pthread_key_create((undefined4 *)(lVar10 + 8),
                            PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8);
    if (iVar5 == 0) goto code_r0x0227d1d0;
code_r0x0227d1e0:
    lVar11 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar10);
  }
  else {
code_r0x0227d1d0:
    lVar11 = pthread_getspecific(*(undefined4 *)(lVar10 + 8));
    if (lVar11 == 0) goto code_r0x0227d1e0;
  }
  if ((lVar11 == 0) || (*(int *)(lVar11 + 0xd0) != iVar6)) goto code_r0x011db5a0;
  lVar10 = *param_4;
  uVar1 = *(undefined4 *)(&UNK_029ce77c + (param_3 & 0xffffffff) * 4);
  if (lVar10 == 0) {
code_r0x0227d274:
    lVar10 = Aska::IndexBuffer::GetData(int) const(param_4,1);
  }
  else {
    if (((*(int *)(lVar10 + 0x68) != 0) || (*(long *)(lVar10 + 0x48) == 0)) &&
       (uVar7 = (**(code **)**(undefined8 **)(lVar10 + 0x40))
                          (*(undefined8 **)(lVar10 + 0x40),lVar10), (uVar7 & 1) != 0)) {
      *(undefined4 *)(lVar10 + 0x68) = 0;
    }
    if (*(long *)(*param_4 + 0x48) == 0) goto code_r0x0227d274;
    lVar10 = 0;
  }
  uVar7 = Aska::IndexBuffer::Is32BitBuffer() const(param_4);
  bVar4 = (uVar7 & 1) != 0;
  lVar11 = 1;
  if (bVar4) {
    lVar11 = 2;
  }
  uVar9 = 0x1405;
  if (!bVar4) {
    uVar9 = 0x1403;
  }
  if (((*(int *)(param_1 + 0x144) == 0) && (*(long *)(param_1 + 0x148) == 0)) ||
     (*(uint *)(param_1 + 0x15c) < 2)) {
    glDrawElements(uVar1,param_6,uVar9,lVar10 + (param_5 << lVar11));
  }
  else {
    (*pcRam0000000002dd0818)(uVar1,param_6);
  }
  lVar10 = *(long *)(*(long *)(*(long *)puVar3 + 0xeaa80) + 0x2b0);
  piVar8 = (int *)(lVar10 + 0x10);
  if (*piVar8 == 0) {
    do {
      if (*piVar8 != 0) {
        ClearExclusiveLocal();
        goto code_r0x0227d344;
      }
      cVar2 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar4) {
        *piVar8 = 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    iVar6 = pthread_key_create((undefined4 *)(lVar10 + 8),
                            PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8);
    if (iVar6 == 0) goto code_r0x0227d344;
code_r0x0227d388:
    lVar11 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar10);
  }
  else {
code_r0x0227d344:
    lVar11 = pthread_getspecific(*(undefined4 *)(lVar10 + 8));
    if (lVar11 == 0) goto code_r0x0227d388;
  }
  if (lVar11 == 0) {
    iVar6 = 0;
  }
  else {
    if (*(int *)(lVar11 + 0xd0) == 0) {
      return;
    }
    iVar6 = 0;
  }
code_r0x011db5a0:
  (*(code *)PTR_glBindBuffer_02ca5ac0)(0x8893,iVar6);
  return;
}

// ==== Aska::RenderDeviceGL::BindVertexBuffer(unsigned long, void*)
// vaddr 0x217d3c0 | ghidra 0x227d3c0 | size 188 | symbol _ZN4Aska14RenderDeviceGL16BindVertexBufferEmPv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0227d444: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0227d448) */

void _ZN4Aska14RenderDeviceGL16BindVertexBufferEmPv(long param_1,int param_2)

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
        goto code_r0x0227d41c;
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
    if (iVar3 == 0) goto code_r0x0227d41c;
  }
  else {
code_r0x0227d41c:
    lVar4 = pthread_getspecific(*(undefined4 *)(lVar6 + 8));
    if (lVar4 != 0) goto joined_r0x0227d464;
  }
  lVar4 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar6);
joined_r0x0227d464:
  if (lVar4 != 0) {
    if (*(int *)(lVar4 + 0xcc) == param_2) {
      return;
    }
  }
  (*(code *)PTR_glBindBuffer_02ca5ac0)(0x8892,param_2);
  return;
}

// ==== Aska::RenderDeviceGL::EnableAlphaBlend(bool)
// vaddr 0x217dcc0 | ghidra 0x227dcc0 | size 180 | symbol _ZN4Aska14RenderDeviceGL16EnableAlphaBlendEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL16EnableAlphaBlendEb(long param_1,ushort param_2)

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
        goto code_r0x0227dd1c;
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
    if (iVar3 == 0) goto code_r0x0227dd1c;
  }
  else {
code_r0x0227dd1c:
    lVar4 = pthread_getspecific(*(undefined4 *)(lVar6 + 8));
    if (lVar4 != 0) goto joined_r0x0227dd50;
  }
  lVar4 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar6);
joined_r0x0227dd50:
  if (lVar4 != 0) {
    *(ushort *)(lVar4 + 0x300) =
         *(ushort *)(lVar4 + 0x300) & 0xfff0 | *(ushort *)(lVar4 + 0x300) & 7 | (param_2 & 1) << 3;
    return;
  }
  if ((param_2 & 1) != 0) {
    (*(code *)PTR_glEnable_02c9ddf8)();
    return;
  }
  (*(code *)PTR_glDisable_02cac210)(0xbe2);
  return;
}

// ==== Aska::RenderDeviceGL::SetTextureSamplingFilter(unsigned int, Aska::TexSamp::Filter)
// vaddr 0x217dfc0 | ghidra 0x227dfc0 | size 160 | symbol _ZN4Aska14RenderDeviceGL24SetTextureSamplingFilterEjNS_7TexSamp6FilterE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL24SetTextureSamplingFilterEjNS_7TexSamp6FilterE
               (long param_1,uint param_2,undefined4 param_3)

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
        goto code_r0x0227e024;
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
    if (iVar3 == 0) goto code_r0x0227e024;
  }
  else {
code_r0x0227e024:
    lVar4 = pthread_getspecific(*(undefined4 *)(lVar6 + 8));
    if (lVar4 != 0) goto code_r0x0227e038;
  }
  lVar4 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar6);
code_r0x0227e038:
  if ((param_2 < 0x10) && (lVar4 != 0)) {
    *(undefined4 *)(lVar4 + (ulong)param_2 * 0x18 + 0x178) = param_3;
  }
  return;
}

// ==== Aska::RenderDeviceGL::SetTextureSamplingMipmapFilter(unsigned int, Aska::TexSamp::MipFilter)
// vaddr 0x217e060 | ghidra 0x227e060 | size 160 | symbol _ZN4Aska14RenderDeviceGL30SetTextureSamplingMipmapFilterEjNS_7TexSamp9MipFilterE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL30SetTextureSamplingMipmapFilterEjNS_7TexSamp9MipFilterE
               (long param_1,uint param_2,undefined4 param_3)

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
        goto code_r0x0227e0c4;
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
    if (iVar3 == 0) goto code_r0x0227e0c4;
  }
  else {
code_r0x0227e0c4:
    lVar4 = pthread_getspecific(*(undefined4 *)(lVar6 + 8));
    if (lVar4 != 0) goto code_r0x0227e0d8;
  }
  lVar4 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar6);
code_r0x0227e0d8:
  if ((param_2 < 0x10) && (lVar4 != 0)) {
    *(undefined4 *)(lVar4 + (ulong)param_2 * 0x18 + 0x17c) = param_3;
  }
  return;
}

// ==== Aska::RenderDeviceGL::SetTextureSamplingWrapMode(unsigned int, Aska::TexWrap::Mode, Aska::TexWrap::Mode, Aska::TexWrap::Mode)
// vaddr 0x217e100 | ghidra 0x227e100 | size 196 | symbol _ZN4Aska14RenderDeviceGL26SetTextureSamplingWrapModeEjNS_7TexWrap4ModeES2_S2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL26SetTextureSamplingWrapModeEjNS_7TexWrap4ModeES2_S2_
               (long param_1,uint param_2,int param_3,int param_4)

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
        goto code_r0x0227e168;
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
    if (iVar3 == 0) goto code_r0x0227e168;
  }
  else {
code_r0x0227e168:
    lVar4 = pthread_getspecific(*(undefined4 *)(lVar6 + 8));
    if (lVar4 != 0) goto code_r0x0227e17c;
  }
  lVar4 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar6);
code_r0x0227e17c:
  if ((param_2 < 0x10) && (lVar4 != 0)) {
    if (param_3 != 10) {
      *(int *)(lVar4 + (ulong)param_2 * 0x18 + 0x16c) = param_3;
    }
    if (param_4 != 10) {
      *(int *)(lVar4 + (ulong)param_2 * 0x18 + 0x170) = param_4;
    }
  }
  return;
}

// ==== Aska::RenderDeviceGL::SetTextureSamplingMaxAnisotropic(unsigned int, unsigned int)
// vaddr 0x217e1c4 | ghidra 0x227e1c4 | size 196 | symbol _ZN4Aska14RenderDeviceGL32SetTextureSamplingMaxAnisotropicEjj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL32SetTextureSamplingMaxAnisotropicEjj
               (long param_1,uint param_2,uint param_3)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  long lVar4;
  int *piVar5;
  long lVar6;
  
  if (*(char *)(*(long *)(param_1 + 0xeaa80) + 6) == '\0') {
    return;
  }
  lVar6 = *(long *)(*(long *)(param_1 + 0xeaa80) + 0x2b0);
  piVar5 = (int *)(lVar6 + 0x10);
  if (*piVar5 == 0) {
    do {
      if (*piVar5 != 0) {
        ClearExclusiveLocal();
        goto code_r0x0227e230;
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
    if (iVar3 == 0) goto code_r0x0227e230;
  }
  else {
code_r0x0227e230:
    lVar4 = pthread_getspecific(*(undefined4 *)(lVar6 + 8));
    if (lVar4 != 0) goto code_r0x0227e244;
  }
  lVar4 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar6);
code_r0x0227e244:
  if ((param_2 < 0x10) && (lVar4 != 0)) {
    *(uint *)(lVar4 + (ulong)param_2 * 0x18 + 0x174) = param_3;
    return;
  }
  (*(code *)PTR_glTexParameterf_02c9dc88)((float)param_3,0xde1,0x84fe);
  return;
}

// ==== Aska::RenderDeviceGL::EnableZTest(bool)
// vaddr 0x217e288 | ghidra 0x227e288 | size 180 | symbol _ZN4Aska14RenderDeviceGL11EnableZTestEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL11EnableZTestEb(long param_1,ushort param_2)

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
        goto code_r0x0227e2e4;
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
    if (iVar3 == 0) goto code_r0x0227e2e4;
  }
  else {
code_r0x0227e2e4:
    lVar4 = pthread_getspecific(*(undefined4 *)(lVar6 + 8));
    if (lVar4 != 0) goto joined_r0x0227e318;
  }
  lVar4 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar6);
joined_r0x0227e318:
  if (lVar4 != 0) {
    *(ushort *)(lVar4 + 0x300) =
         *(ushort *)(lVar4 + 0x300) & 0xfffc | *(ushort *)(lVar4 + 0x300) & 1 | (param_2 & 1) << 1;
    return;
  }
  if ((param_2 & 1) != 0) {
    (*(code *)PTR_glEnable_02c9ddf8)();
    return;
  }
  (*(code *)PTR_glDisable_02cac210)(0xb71);
  return;
}

// ==== Aska::RenderDeviceGL::SetDepthBias(float, float)
// vaddr 0x217e3e4 | ghidra 0x227e3e4 | size 176 | symbol _ZN4Aska14RenderDeviceGL12SetDepthBiasEff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL12SetDepthBiasEff(undefined8 param_1,undefined8 param_2,long param_3)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  long lVar4;
  int *piVar5;
  long lVar6;
  
  lVar6 = *(long *)(*(long *)(param_3 + 0xeaa80) + 0x2b0);
  piVar5 = (int *)(lVar6 + 0x10);
  if (*piVar5 == 0) {
    do {
      if (*piVar5 != 0) {
        ClearExclusiveLocal();
        goto code_r0x0227e448;
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
    if (iVar3 == 0) goto code_r0x0227e448;
  }
  else {
code_r0x0227e448:
    lVar4 = pthread_getspecific(*(undefined4 *)(lVar6 + 8));
    if (lVar4 != 0) goto joined_r0x0227e478;
  }
  lVar4 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar6);
joined_r0x0227e478:
  if (lVar4 == 0) {
    (*(code *)PTR_glPolygonOffset_02c9da10)(param_2,param_1);
    return;
  }
  *(int *)(lVar4 + 0x37c) = (int)param_2;
  *(int *)(lVar4 + 0x380) = (int)param_1;
  return;
}

// ==== Aska::RenderDeviceGL::EnableStencil(Aska::StencilMode::Mode)
// vaddr 0x217e494 | ghidra 0x227e494 | size 184 | symbol _ZN4Aska14RenderDeviceGL13EnableStencilENS_11StencilMode4ModeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL13EnableStencilENS_11StencilMode4ModeE(long param_1,int param_2)

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
        goto code_r0x0227e4f0;
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
    if (iVar3 == 0) goto code_r0x0227e4f0;
  }
  else {
code_r0x0227e4f0:
    lVar4 = pthread_getspecific(*(undefined4 *)(lVar6 + 8));
    if (lVar4 != 0) goto joined_r0x0227e528;
  }
  lVar4 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar6);
joined_r0x0227e528:
  if (lVar4 != 0) {
    *(ushort *)(lVar4 + 0x300) =
         *(ushort *)(lVar4 + 0x300) & 0xfff8 |
         *(ushort *)(lVar4 + 0x300) & 3 | (ushort)(param_2 != 0) << 2;
    return;
  }
  if (param_2 != 0) {
    (*(code *)PTR_glEnable_02c9ddf8)();
    return;
  }
  (*(code *)PTR_glDisable_02cac210)(0xb90);
  return;
}

// ==== Aska::RenderDeviceGL::SetCullMode(Aska::Cull::Mode)
// vaddr 0x217e794 | ghidra 0x227e794 | size 16 | symbol _ZN4Aska14RenderDeviceGL11SetCullModeENS_4Cull4ModeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL11SetCullModeENS_4Cull4ModeE(long param_1)

{
  (*(code *)PTR__ZN4Aska16RenderDeviceData11SetCullModeENS_4Cull4ModeE_02cb0520)
            (*(undefined8 *)(param_1 + 0xeaa80));
  return;
}

// ==== Aska::RenderDeviceGL::SetVertexShader(Aska::VertexShader*)
// vaddr 0x217ea54 | ghidra 0x227ea54 | size 24 | symbol _ZN4Aska14RenderDeviceGL15SetVertexShaderEPNS_12VertexShaderE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL15SetVertexShaderEPNS_12VertexShaderE(long param_1,undefined8 param_2)

{
  *(undefined8 *)(*(long *)(param_1 + 0xeaa80) + 0x8418) = param_2;
  return;
}

// ==== Aska::RenderDeviceGL::SetPixelShader(Aska::PixelShader*)
// vaddr 0x217ea6c | ghidra 0x227ea6c | size 24 | symbol _ZN4Aska14RenderDeviceGL14SetPixelShaderEPNS_11PixelShaderE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL14SetPixelShaderEPNS_11PixelShaderE(long param_1,undefined8 param_2)

{
  *(undefined8 *)(*(long *)(param_1 + 0xeaa80) + 0x8420) = param_2;
  return;
}

// ==== Aska::RenderDeviceGL::SetVertexShaderConstant(int, void const*, int)
// vaddr 0x217ea84 | ghidra 0x227ea84 | size 156 | symbol _ZN4Aska14RenderDeviceGL23SetVertexShaderConstantEiPKvi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL23SetVertexShaderConstantEiPKvi
               (long param_1,uint param_2,undefined8 param_3,int param_4)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  
  lVar2 = *(long *)(param_1 + 0xeaa80);
  lVar3 = *(long *)(lVar2 + 0x8418);
  if ((lVar3 != 0) && (param_2 < *(uint *)(lVar3 + 0x28))) {
    uVar1 = *(uint *)(*(long *)(lVar3 + 0x20) + (long)(int)param_2 * 4);
    if (uVar1 < *(uint *)(lVar3 + 0x10)) {
      Aska::RenderDeviceData::UpdateShaderProgram()(lVar2);
      (*(code *)
        PTR__ZN4Aska16RenderDeviceData17_SetUniformDirectEPNS_6ShaderEPKNS_7UniformEiPKvi_02ca5708)
                (lVar2,lVar3,*(long *)(lVar3 + 0x18) + (long)(int)uVar1 * 0x10,
                 *(undefined4 *)(*(long *)(*(long *)(lVar2 + 0x8440) + 0x28) + (long)(int)uVar1 * 4)
                 ,param_3,param_4 << 4);
      return;
    }
  }
  return;
}

// ==== Aska::RenderDeviceGL::SetPixelShaderConstant(int, void const*, int)
// vaddr 0x217eb20 | ghidra 0x227eb20 | size 156 | symbol _ZN4Aska14RenderDeviceGL22SetPixelShaderConstantEiPKvi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL22SetPixelShaderConstantEiPKvi
               (long param_1,uint param_2,undefined8 param_3,int param_4)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  
  lVar2 = *(long *)(param_1 + 0xeaa80);
  lVar3 = *(long *)(lVar2 + 0x8420);
  if ((lVar3 != 0) && (param_2 < *(uint *)(lVar3 + 0x28))) {
    uVar1 = *(uint *)(*(long *)(lVar3 + 0x20) + (long)(int)param_2 * 4);
    if (uVar1 < *(uint *)(lVar3 + 0x10)) {
      Aska::RenderDeviceData::UpdateShaderProgram()(lVar2);
      (*(code *)
        PTR__ZN4Aska16RenderDeviceData17_SetUniformDirectEPNS_6ShaderEPKNS_7UniformEiPKvi_02ca5708)
                (lVar2,lVar3,*(long *)(lVar3 + 0x18) + (long)(int)uVar1 * 0x10,
                 *(undefined4 *)(*(long *)(*(long *)(lVar2 + 0x8440) + 0x30) + (long)(int)uVar1 * 4)
                 ,param_3,param_4 << 4);
      return;
    }
  }
  return;
}

// ==== Aska::RenderDeviceGL::SetVertexShaderConstant(Aska::UniformValueBuffer2*)
// vaddr 0x217ebbc | ghidra 0x227ebbc | size 184 | symbol _ZN4Aska14RenderDeviceGL23SetVertexShaderConstantEPNS_19UniformValueBuffer2E | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL23SetVertexShaderConstantEPNS_19UniformValueBuffer2E
               (long param_1,int *param_2)

{
  short *psVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  int iVar5;
  
  lVar3 = *(long *)(param_1 + 0xeaa80);
  lVar4 = *(long *)(lVar3 + 0x8418);
  if ((lVar4 != 0) && (Aska::RenderDeviceData::UpdateShaderProgram()(lVar3), *param_2 != 0)) {
    lVar2 = *(long *)(param_2 + 2);
    iVar5 = 0;
    do {
      psVar1 = (short *)(lVar2 + iVar5);
      Aska::RenderDeviceData::_SetUniformDirect(Aska::Shader*, Aska::Uniform const*, int, void const*, int)(lVar3,lVar4,*(long *)(lVar4 + 0x18) + (long)*psVar1 * 0x10,
                      *(undefined4 *)
                       (*(long *)(*(long *)(lVar3 + 0x8440) + 0x28) + (long)*psVar1 * 4),psVar1 + 2,
                      (long)psVar1[1]);
      lVar2 = *(long *)(param_2 + 2);
      iVar5 = iVar5 + *(short *)(lVar2 + iVar5 + 2) + 4;
    } while (*param_2 != iVar5);
  }
  return;
}

// ==== Aska::RenderDeviceGL::SetPixelShaderConstant(Aska::UniformValueBuffer2*)
// vaddr 0x217ec74 | ghidra 0x227ec74 | size 184 | symbol _ZN4Aska14RenderDeviceGL22SetPixelShaderConstantEPNS_19UniformValueBuffer2E | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14RenderDeviceGL22SetPixelShaderConstantEPNS_19UniformValueBuffer2E
               (long param_1,int *param_2)

{
  short *psVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  int iVar5;
  
  lVar3 = *(long *)(param_1 + 0xeaa80);
  lVar4 = *(long *)(lVar3 + 0x8420);
  if ((lVar4 != 0) && (Aska::RenderDeviceData::UpdateShaderProgram()(lVar3), *param_2 != 0)) {
    lVar2 = *(long *)(param_2 + 2);
    iVar5 = 0;
    do {
      psVar1 = (short *)(lVar2 + iVar5);
      Aska::RenderDeviceData::_SetUniformDirect(Aska::Shader*, Aska::Uniform const*, int, void const*, int)(lVar3,lVar4,*(long *)(lVar4 + 0x18) + (long)*psVar1 * 0x10,
                      *(undefined4 *)
                       (*(long *)(*(long *)(lVar3 + 0x8440) + 0x30) + (long)*psVar1 * 4),psVar1 + 2,
                      (long)psVar1[1]);
      lVar2 = *(long *)(param_2 + 2);
      iVar5 = iVar5 + *(short *)(lVar2 + iVar5 + 2) + 4;
    } while (*param_2 != iVar5);
  }
  return;
}

// ==== Aska::RenderDeviceData::GetBoundTextureID(unsigned int)
// vaddr 0x2182ed8 | ghidra 0x2282ed8 | size 292 | symbol _ZN4Aska16RenderDeviceData17GetBoundTextureIDEj | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska16RenderDeviceData17GetBoundTextureIDEj(long param_1,int param_2)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  long lVar4;
  int *piVar5;
  undefined4 *puVar6;
  long lVar7;
  undefined4 uStack_24;
  
  lVar7 = *(long *)(param_1 + 0x2b0);
  piVar5 = (int *)(lVar7 + 0x10);
  if (*piVar5 == 0) {
    do {
      if (*piVar5 != 0) {
        ClearExclusiveLocal();
        goto code_r0x02282f2c;
      }
      cVar1 = '\x01';
      bVar2 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar2) {
        *piVar5 = 1;
        cVar1 = ExclusiveMonitorsStatus();
      }
    } while (cVar1 != '\0');
    iVar3 = pthread_key_create((undefined4 *)(lVar7 + 8),
                            PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8);
    if (iVar3 == 0) goto code_r0x02282f2c;
  }
  else {
code_r0x02282f2c:
    lVar4 = pthread_getspecific(*(undefined4 *)(lVar7 + 8));
    if (lVar4 != 0) goto joined_r0x02282f7c;
  }
  lVar4 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar7);
joined_r0x02282f7c:
  if (lVar4 == 0) {
    if (param_2 == 0x8513) {
      param_2 = 0x8514;
    }
    else if (param_2 == 0x806f) {
      param_2 = 0x806a;
    }
    else if (param_2 == 0xde1) {
      param_2 = 0x8069;
    }
    uStack_24 = 0;
    glGetIntegerv(param_2,&uStack_24);
  }
  else {
    if (param_2 - 0x8513U < 2) {
      puVar6 = (undefined4 *)(lVar4 + (ulong)*(byte *)(lVar4 + 200) * 4 + 0x48);
    }
    else if ((param_2 == 0x806a) || (param_2 == 0x806f)) {
      puVar6 = (undefined4 *)(lVar4 + (ulong)*(byte *)(lVar4 + 200) * 4 + 0x88);
    }
    else {
      puVar6 = (undefined4 *)(lVar4 + (ulong)*(byte *)(lVar4 + 200) * 4 + 8);
    }
    uStack_24 = *puVar6;
  }
  return uStack_24;
}

// ==== Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)
// vaddr 0x2183b98 | ghidra 0x2283b98 | size 704 | symbol _ZN4Aska16RenderDeviceData21GetTextureStateCachesEj | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska16RenderDeviceData21GetTextureStateCachesEj(long param_1,uint param_2)

{
  ulong *puVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  uint uVar5;
  long lVar6;
  undefined8 uVar7;
  ulong uVar8;
  char *pcVar9;
  ulong uVar10;
  long lVar11;
  long lVar12;
  ulong uVar13;
  char *pcVar14;
  long lVar15;
  ulong uVar16;
  undefined8 *puVar17;
  
  uVar8 = ~(ulong)param_2 + (ulong)param_2 * 0x200000;
  uVar10 = (uVar8 ^ uVar8 >> 0x18) * 0x109;
  uVar8 = *(ulong *)(param_1 + 0x228);
  uVar10 = (uVar10 ^ uVar10 >> 0xe) * 0x15;
  lVar6 = (uVar10 ^ uVar10 >> 0x1c) * 0x80000001;
  if (uVar8 == 0) {
code_r0x02283c84:
    uVar2 = *(uint *)(param_1 + 0x1dc);
    if (*(uint *)(param_1 + 500) < uVar2) {
      uVar3 = *(uint *)(param_1 + 0x1f0);
      uVar8 = (ulong)uVar3;
      *(uint *)(param_1 + 500) = *(uint *)(param_1 + 500) + 1;
      puVar1 = (ulong *)(*(long *)(param_1 + 0x1d0) + (ulong)(uVar3 >> 6) * 8);
      uVar10 = *puVar1;
      uVar13 = 1L << (uVar8 & 0x3f);
      uVar16 = uVar13 & uVar10;
      while (uVar16 != 0) {
        uVar3 = (int)uVar8 + 1;
        uVar5 = 0;
        if (uVar2 != 0) {
          uVar5 = uVar3 / uVar2;
        }
        uVar3 = uVar3 - uVar5 * uVar2;
        uVar8 = (ulong)uVar3;
        puVar1 = (ulong *)(*(long *)(param_1 + 0x1d0) + (ulong)(uVar3 >> 6) * 8);
        uVar10 = *puVar1;
        uVar13 = 1L << (uVar3 & 0x3f);
        uVar16 = uVar13 & uVar10;
      }
      *puVar1 = uVar13 | uVar10;
      lVar12 = *(long *)(param_1 + 0x1e8);
      uVar5 = 0;
      if (uVar2 != 0) {
        uVar5 = (uVar3 + 1) / uVar2;
      }
      puVar17 = (undefined8 *)(lVar12 + (ulong)uVar3 * 0x14);
      *(uint *)(param_1 + 0x1f0) = (uVar3 + 1) - uVar5 * uVar2;
      uVar7 = _UNK_029cd0f0;
      if (puVar17 != (undefined8 *)0x0) {
        puVar17[1] = _UNK_029cd0f8;
        *puVar17 = uVar7;
        *(undefined4 *)(lVar12 + (ulong)uVar3 * 0x14 + 0x10) = 1;
        uVar10 = *(ulong *)(param_1 + 0x228);
        uVar8 = (ulong)((float)((ulong)*(uint *)(param_1 + 0x210) +
                                (ulong)*(uint *)(param_1 + 0x214) + 1) / *(float *)(param_1 + 0x20c)
                       );
        if (uVar10 < uVar8) {
          Aska::THashMap<unsigned int, Aska::_RenderDeviceGL::TextureStateCache*, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, Aska::_RenderDeviceGL::TextureStateCache*> > >::Rehash_(unsigned long)(param_1 + 0x200,uVar8 << 1 | 1);
          uVar10 = *(ulong *)(param_1 + 0x228);
        }
        if (uVar10 != 0) {
          uVar8 = 0;
          pcVar9 = (char *)0x0;
          do {
            uVar13 = 0;
            if (uVar10 != 0) {
              uVar13 = (lVar6 + uVar8) / uVar10;
            }
            lVar12 = (lVar6 + uVar8) - uVar13 * uVar10;
            pcVar14 = (char *)(*(long *)(param_1 + 0x220) + lVar12 * 0x18);
            cVar4 = *pcVar14;
            if (cVar4 == '\x01') {
              if (*(uint *)(*(long *)(param_1 + 0x220) + lVar12 * 0x18 + 8) == param_2)
              goto code_r0x02283e44;
            }
            else if (cVar4 == '\0') {
              if (pcVar9 != (char *)0x0) {
                pcVar14 = pcVar9;
              }
              break;
            }
            uVar8 = uVar8 + 1;
            if (cVar4 != '\x02' || pcVar9 != (char *)0x0) {
              pcVar14 = pcVar9;
            }
            pcVar9 = pcVar14;
          } while (uVar8 < uVar10);
          if (pcVar14 != (char *)0x0) {
            *(uint *)(pcVar14 + 8) = param_2;
            *(undefined8 **)(pcVar14 + 0x10) = puVar17;
            if (*pcVar14 == '\0') {
code_r0x02283e00:
              *(int *)(param_1 + 0x210) = *(int *)(param_1 + 0x210) + 1;
            }
            else if (*pcVar14 == '\x02') {
              *(int *)(param_1 + 0x214) = *(int *)(param_1 + 0x214) + -1;
              goto code_r0x02283e00;
            }
            *pcVar14 = '\x01';
            lVar11 = *(long *)(param_1 + 0x220);
            uVar8 = *(ulong *)(param_1 + 0x228);
            goto joined_r0x02283e1c;
          }
        }
      }
    }
code_r0x02283e44:
    uVar7 = 0;
  }
  else {
    lVar11 = *(long *)(param_1 + 0x220);
    lVar12 = 0;
    uVar10 = 0;
    do {
      uVar13 = 0;
      if (uVar8 != 0) {
        uVar13 = (lVar6 + uVar10) / uVar8;
      }
      lVar15 = (lVar6 + uVar10) - uVar13 * uVar8;
      cVar4 = *(char *)(lVar11 + lVar15 * 0x18);
      if (cVar4 == '\x01') {
        if (*(uint *)(lVar11 + lVar15 * 0x18 + 8) == param_2) {
          lVar12 = lVar12 + 1;
        }
      }
      else if (cVar4 == '\0') break;
      uVar10 = uVar10 + 1;
    } while (uVar10 < uVar8);
    if (lVar12 == 0) goto code_r0x02283c84;
joined_r0x02283e1c:
    uVar10 = uVar8;
    if (uVar8 != 0) {
      uVar13 = 0;
      do {
        uVar10 = 0;
        if (uVar8 != 0) {
          uVar10 = (lVar6 + uVar13) / uVar8;
        }
        uVar10 = (lVar6 + uVar13) - uVar10 * uVar8;
        cVar4 = *(char *)(lVar11 + uVar10 * 0x18);
        if (cVar4 == '\x01') {
          if (*(uint *)(lVar11 + uVar10 * 0x18 + 8) == param_2) break;
        }
        else {
          uVar10 = uVar8;
          if (cVar4 == '\0') break;
        }
        uVar13 = uVar13 + 1;
        uVar10 = uVar8;
      } while (uVar13 < uVar8);
    }
    uVar7 = *(undefined8 *)(lVar11 + uVar10 * 0x18 + 0x10);
  }
  return uVar7;
}

// ==== Aska::RenderDeviceData::GetThreadOglState1()
// vaddr 0x2185de4 | ghidra 0x2285de4 | size 168 | symbol _ZN4Aska16RenderDeviceData18GetThreadOglState1Ev | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska16RenderDeviceData18GetThreadOglState1Ev(long param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  long *plVar4;
  int *piVar5;
  long lVar6;
  
  lVar6 = *(long *)(param_1 + 0x2b0);
  piVar5 = (int *)(lVar6 + 0x14);
  if (*piVar5 == 0) {
    do {
      if (*piVar5 != 0) {
        ClearExclusiveLocal();
        goto code_r0x02285e30;
      }
      cVar1 = '\x01';
      bVar2 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar2) {
        *piVar5 = 1;
        cVar1 = ExclusiveMonitorsStatus();
      }
    } while (cVar1 != '\0');
    iVar3 = pthread_key_create((undefined4 *)(lVar6 + 0xc),
                            PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct1EPv_02cbe1b0);
    if (iVar3 != 0) goto code_r0x02285e40;
  }
code_r0x02285e30:
  plVar4 = (long *)pthread_getspecific(*(undefined4 *)(lVar6 + 0xc));
  if (plVar4 != (long *)0x0) {
    return plVar4;
  }
code_r0x02285e40:
  plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x10,PTR__ZSt7nothrow_02cb9a80);
  if (plVar4 != (long *)0x0) {
    *plVar4 = lVar6;
    plVar4[1] = -1;
    iVar3 = pthread_setspecific(*(undefined4 *)(lVar6 + 0xc),plVar4);
    if (iVar3 != 0) {
      operator delete(void*)(plVar4);
      plVar4 = (long *)0x0;
    }
  }
  return plVar4;
}

// ==== Aska::RenderDeviceData::UpdateShaderProgram()
// vaddr 0x21871a0 | ghidra 0x22871a0 | size 948 | symbol _ZN4Aska16RenderDeviceData19UpdateShaderProgramEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x02287258: Changing call to branch */
/* WARNING: Possible PIC construction at 0x02287510: Changing call to branch */
/* WARNING: Possible PIC construction at 0x02287540: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0228725c) */
/* WARNING: Removing unreachable block (ram,0x02287514) */

void _ZN4Aska16RenderDeviceData19UpdateShaderProgramEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  char cVar3;
  ulong uVar4;
  int iVar5;
  long *plVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  long lVar10;
  ulong uVar11;
  long lVar12;
  undefined8 uVar13;
  undefined8 uStack_68;
  long *plStack_60;
  long lStack_48;
  
  plVar1 = (long *)(param_1 + 0x8428);
  lVar7 = *(long *)(*(long *)(param_1 + 0x8418) + 0x30);
  plVar2 = (long *)(param_1 + 0x8420);
  if (*(long *)(param_1 + 0x8420) == 0) {
    plVar2 = plVar1;
  }
  lVar9 = *plVar2;
  *(long *)(param_1 + 0x83e0) = lVar7;
  lVar9 = *(long *)(lVar9 + 0x30);
  *(long *)(param_1 + 0x83e8) = lVar9;
  plVar2 = (long *)(param_1 + 0x8440);
  lVar10 = *plVar2;
  if (((lVar10 == 0) || (*(long *)(lVar10 + 8) != lVar7)) || (*(long *)(lVar10 + 0x10) != lVar9)) {
    uStack_68 = 0;
    lStack_48 = 0;
    Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)((long *)(param_1 + 0x83e0),0x10,&lStack_48,&uStack_68);
    lVar7 = lStack_48;
    *(long *)(param_1 + 0x83d8) = lStack_48;
    uVar8 = *(ulong *)(param_1 + 0x83d0);
    if (uVar8 != 0) {
      lVar9 = *(long *)(param_1 + 0x83c8);
      uVar11 = 0;
      do {
        uVar4 = 0;
        if (uVar8 != 0) {
          uVar4 = (lStack_48 + uVar11) / uVar8;
        }
        lVar10 = (lStack_48 + uVar11) - uVar4 * uVar8;
        cVar3 = *(char *)(lVar9 + lVar10 * 0x10);
        if (cVar3 == '\x01') {
          lVar12 = *(long *)(lVar9 + lVar10 * 0x10 + 8);
          if ((*(long *)(lVar12 + 8) == *(long *)(param_1 + 0x83e0)) &&
             (*(long *)(lVar12 + 0x10) == *(long *)(param_1 + 0x83e8))) {
            lVar7 = *(long *)(lVar9 + lVar10 * 0x10 + 8);
            *plVar2 = lVar7;
            if (*(int *)(lVar7 + 0x18) == 0) {
              uVar13 = *(undefined8 *)(*(long *)(lVar7 + 8) + 8);
              uVar8 = Aska::Shader::GetIsCreated() const(uVar13);
              if ((uVar8 & 1) == 0) {
                Aska::RenderDeviceData::CreateShader(unsigned int, Aska::Shader*)(param_1,0x8b31,uVar13);
              }
              if (*(long *)(lVar7 + 0x10) != 0) {
                plVar1 = (long *)(*(long *)(lVar7 + 0x10) + 8);
              }
              lVar9 = *plVar1;
              uVar8 = Aska::Shader::GetIsCreated() const(lVar9);
              if ((uVar8 & 1) == 0) {
                Aska::RenderDeviceData::CreateShader(unsigned int, Aska::Shader*)(param_1,0x8b30,lVar9);
              }
              uVar8 = Aska::RenderDeviceData::CompileShaderProgram(Aska::ShaderProgramValue*)(param_1,lVar7);
              if ((uVar8 & 1) != 0) {
                Aska::RenderDeviceData::SetShaderProgramUniform(Aska::ShaderProgramValue*)(param_1,lVar7);
              }
              if (*(char *)(param_1 + 0x1b) != '\0') {
                Aska::RenderDeviceData::WriteShaderProgramCache(char const*, Aska::AHSLFileCacheHeader&, bool (Aska::RenderDeviceData::*)(unsigned char*&, unsigned int&))(param_1,param_1 + 0xc5a0,param_1 + 0xa580,
                                PTR__ZN4Aska16RenderDeviceData28WriteShaderLinkedBinaryCacheERPhRj_02cb8b10
                                ,0);
              }
            }
            iVar5 = *(int *)(*plVar2 + 0x18);
            lVar7 = Aska::RenderDeviceData::GetThreadOglState1()(param_1);
            if ((lVar7 != 0) && (*(int *)(lVar7 + 8) = iVar5, *(int *)(lVar7 + 0xc) == iVar5)) {
              Aska::RenderDeviceData::SetShaderProgramUniform(Aska::ShaderProgramValue*)(param_1,*plVar2);
              return;
            }
            goto code_r0x011b9610;
          }
        }
        else if (cVar3 == '\0') break;
        uVar11 = uVar11 + 1;
      } while (uVar11 < uVar8);
    }
    plVar6 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x40,PTR__ZSt7nothrow_02cb9a80);
    if (plVar6 != (long *)0x0) {
      *(undefined4 *)(plVar6 + 3) = 0;
      plVar6[1] = 0;
      plVar6[2] = 0;
      *(undefined4 *)(plVar6 + 7) = 0;
      plVar6[5] = 0;
      plVar6[6] = 0;
      plVar6[4] = 0;
    }
    *plVar2 = (long)plVar6;
    lVar10 = *(long *)(param_1 + 0x83e8);
    lVar9 = *(long *)(param_1 + 0x83e0);
    *plVar6 = lVar7;
    plVar6[2] = lVar10;
    plVar6[1] = lVar9;
    uVar13 = *(undefined8 *)(lVar9 + 8);
    uVar8 = Aska::Shader::GetIsCreated() const(uVar13);
    if ((uVar8 & 1) == 0) {
      Aska::RenderDeviceData::CreateShader(unsigned int, Aska::Shader*)(param_1,0x8b31,uVar13);
    }
    if (plVar6[2] != 0) {
      plVar1 = (long *)(plVar6[2] + 8);
    }
    lVar7 = *plVar1;
    uVar8 = Aska::Shader::GetIsCreated() const(lVar7);
    if ((uVar8 & 1) == 0) {
      Aska::RenderDeviceData::CreateShader(unsigned int, Aska::Shader*)(param_1,0x8b30,lVar7);
    }
    uVar8 = Aska::RenderDeviceData::CompileShaderProgram(Aska::ShaderProgramValue*)(param_1,plVar6);
    if ((uVar8 & 1) != 0) {
      Aska::RenderDeviceData::SetShaderProgramUniform(Aska::ShaderProgramValue*)(param_1,plVar6);
    }
    uStack_68 = 1;
    plStack_60 = plVar2;
    Aska::TArrayIterator<Aska::TDynamicArray<Aska::ShaderProgramValue*, Aska::TAllocator<Aska::ShaderProgramValue*> > > Aska::TDynamicArray<Aska::ShaderProgramValue*, Aska::TAllocator<Aska::ShaderProgramValue*> >::Insert_<Aska::Memory::TUninitializedFillN<Aska::ShaderProgramValue*> >(Aska::ShaderProgramValue* const*, unsigned long, Aska::Memory::TUninitializedFillN<Aska::ShaderProgramValue*> const&)(param_1 + 0x8308,*(undefined8 *)(param_1 + 0x8318),1,&uStack_68);
    Aska::THashSet<Aska::ShaderProgramValue*, Aska::THasher_StateKey<Aska::ShaderProgramValue*>, Aska::TEqualTo_StateKey<Aska::ShaderProgramValue*>, Aska::TAllocator<Aska::ShaderProgramValue*> >::Insert(Aska::ShaderProgramValue* const&)(&uStack_68,param_1 + 0x83a8,plVar2);
    if (*(char *)(param_1 + 0x1b) != '\0') {
      Aska::RenderDeviceData::WriteShaderProgramCache(char const*, Aska::AHSLFileCacheHeader&, bool (Aska::RenderDeviceData::*)(unsigned char*&, unsigned int&))(param_1,param_1 + 0xc5a0,param_1 + 0xa580,
                      PTR__ZN4Aska16RenderDeviceData28WriteShaderLinkedBinaryCacheERPhRj_02cb8b10,0)
      ;
    }
  }
  else {
    iVar5 = *(int *)(lVar10 + 0x18);
    lVar7 = Aska::RenderDeviceData::GetThreadOglState1()(param_1);
    if ((lVar7 == 0) || (*(int *)(lVar7 + 8) = iVar5, *(int *)(lVar7 + 0xc) != iVar5)) {
code_r0x011b9610:
      (*(code *)PTR_glUseProgram_02c94af8)(iVar5);
      return;
    }
  }
  return;
}

// ==== Aska::RenderDeviceData::UpdateRenderState(Aska::RenderDeviceGL*)
// vaddr 0x2187ee4 | ghidra 0x2287ee4 | size 628 | symbol _ZN4Aska16RenderDeviceData17UpdateRenderStateEPNS_14RenderDeviceGLE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska16RenderDeviceData17UpdateRenderStateEPNS_14RenderDeviceGLE(long param_1,undefined8 param_2)

{
  byte bVar1;
  ushort uVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  ushort uVar6;
  int iVar7;
  long lVar8;
  uint uVar9;
  int *piVar10;
  long lVar11;
  
  Aska::RenderDeviceData::UpdateShaderProgram()();
  lVar11 = *(long *)(param_1 + 0x2b0);
  piVar10 = (int *)(lVar11 + 0x10);
  if (*piVar10 == 0) {
    do {
      if (*piVar10 != 0) {
        ClearExclusiveLocal();
        goto code_r0x02287f40;
      }
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
      if (bVar4) {
        *piVar10 = 1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    iVar7 = pthread_key_create((undefined4 *)(lVar11 + 8),
                            PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8);
    if (iVar7 == 0) goto code_r0x02287f40;
  }
  else {
code_r0x02287f40:
    lVar8 = pthread_getspecific(*(undefined4 *)(lVar11 + 8));
    if (lVar8 != 0) goto code_r0x02287f5c;
  }
  lVar8 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar11);
code_r0x02287f5c:
  if (lVar8 != 0) {
    Aska::RenderDeviceData::UpdateVertexAttribute(Aska::ASKA_OGL_STATESET0*)(param_1,lVar8);
    uVar2 = *(ushort *)(lVar8 + 0x300);
    uVar9 = (uint)uVar2;
    uVar6 = uVar2 >> 4 & 1;
    if (uVar6 != (uVar2 >> 0xb & 1)) {
      if (uVar6 == 0) {
        glDisable(0x809e);
      }
      else {
        glEnable(0x809e);
      }
      uVar2 = *(ushort *)(lVar8 + 0x300);
      uVar9 = uVar2 & 0xfffff000 | uVar2 & 0x7ff | (uVar2 >> 4 & 1) << 0xb;
      *(short *)(lVar8 + 0x300) = (short)uVar9;
    }
    uVar5 = uVar9 >> 5 & 1;
    if (uVar5 != (uVar9 >> 0xc & 1)) {
      if (uVar5 == 0) {
        glDisable(0xbd0);
      }
      else {
        glEnable(0xbd0);
      }
      uVar2 = *(ushort *)(lVar8 + 0x300);
      uVar9 = uVar2 & 0xffffe000 | uVar2 & 0xfff | (uVar2 >> 5 & 1) << 0xc;
      *(short *)(lVar8 + 0x300) = (short)uVar9;
    }
    if ((((*(int *)(lVar8 + 0x35c) != *(int *)(lVar8 + 0x334)) ||
         (*(int *)(lVar8 + 0x360) != *(int *)(lVar8 + 0x338))) ||
        (*(int *)(lVar8 + 0x364) != *(int *)(lVar8 + 0x33c))) ||
       (*(int *)(lVar8 + 0x368) != *(int *)(lVar8 + 0x340))) {
      glViewport(*(int *)(lVar8 + 0x35c),*(int *)(lVar8 + 0x360),*(undefined4 *)(lVar8 + 0x364)
                      ,*(undefined4 *)(lVar8 + 0x368));
      *(undefined8 *)(lVar8 + 0x33c) = *(undefined8 *)(lVar8 + 0x364);
      *(undefined8 *)(lVar8 + 0x334) = *(undefined8 *)(lVar8 + 0x35c);
      uVar9 = (uint)*(ushort *)(lVar8 + 0x300);
    }
    if ((uVar9 & 1) != (uVar9 >> 7 & 1)) {
      if ((uVar9 & 1) == 0) {
        glDisable(0xb44);
      }
      else {
        glEnable(0xb44);
      }
      uVar2 = *(ushort *)(lVar8 + 0x300);
      *(ushort *)(lVar8 + 0x300) = uVar2 & 0xff00 | uVar2 & 0x7f | (uVar2 & 1) << 7;
    }
    if (*(int *)(lVar8 + 0x30c) != *(int *)(lVar8 + 0x310)) {
      glFrontFace();
      *(undefined4 *)(lVar8 + 0x310) = *(undefined4 *)(lVar8 + 0x30c);
    }
    if (*(int *)(lVar8 + 0x314) != *(int *)(lVar8 + 0x318)) {
      glCullFace();
      *(undefined4 *)(lVar8 + 0x318) = *(undefined4 *)(lVar8 + 0x314);
    }
    Aska::RenderDeviceData::LastMinuteDrawCommands_Blending(Aska::ASKA_OGL_STATESET0*)(param_1,lVar8);
    Aska::RenderDeviceData::LastMinuteDrawCommands_Depth(Aska::ASKA_OGL_STATESET0*)(param_1,lVar8);
    uVar2 = *(ushort *)(lVar8 + 0x300) >> 2 & 1;
    if (uVar2 != (*(ushort *)(lVar8 + 0x300) >> 9 & 1)) {
      if (uVar2 == 0) {
        glDisable(0xb90);
      }
      else {
        glEnable(0xb90);
      }
      uVar2 = *(ushort *)(lVar8 + 0x300);
      *(ushort *)(lVar8 + 0x300) = uVar2 & 0xfc00 | uVar2 & 0x1ff | (uVar2 >> 2 & 1) << 9;
    }
    bVar1 = *(byte *)(lVar8 + 0x304);
    if (((*(byte *)(lVar8 + 0x308) ^ bVar1) & 0xf) != 0) {
      glColorMask(bVar1 & 1,bVar1 >> 1 & 1,bVar1 >> 2 & 1,bVar1 >> 3 & 1);
      *(undefined4 *)(lVar8 + 0x308) = *(undefined4 *)(lVar8 + 0x304);
    }
  }
  Aska::RenderDeviceData::LastMinuteDrawCommands_Textures(Aska::ASKA_OGL_STATESET0*, Aska::RenderDeviceGL*)(param_1,lVar8,param_2);
  return 1;
}

// ==== Aska::RenderDeviceData::UpdateVertexAttribute(Aska::ASKA_OGL_STATESET0*)
// vaddr 0x2188158 | ghidra 0x2288158 | size 1220 | symbol _ZN4Aska16RenderDeviceData21UpdateVertexAttributeEPNS_18ASKA_OGL_STATESET0E | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderDeviceData21UpdateVertexAttributeEPNS_18ASKA_OGL_STATESET0E
               (long param_1,long param_2)

{
  uint uVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  long lVar6;
  int *piVar7;
  ulong uVar8;
  uint uVar9;
  long lVar10;
  uint uVar11;
  
  uVar9 = *(uint *)(param_1 + 0x154);
  if (uVar9 != 0) {
    if (0 < (int)uVar9) {
      uVar8 = 0;
      do {
        if ((uVar9 & 1) != 0) {
          (*pcRam0000000002dd0808)(uVar8 & 0xffffffff,0);
          glDisableVertexAttribArray(uVar8 & 0xffffffff);
          *(undefined1 *)(param_2 + 0x3ac + uVar8) = 0;
        }
        uVar9 = uVar9 >> 1;
        uVar8 = uVar8 + 1;
      } while (uVar9 != 0);
    }
    *(undefined4 *)(param_1 + 0x154) = 0;
  }
  if (*(int *)(param_1 + 0x230) == 0) goto code_r0x02288538;
  iVar5 = *(int *)(param_1 + 0x144);
  if (iVar5 == 0) {
    if (*(long *)(param_1 + 0x148) == 0) goto code_r0x02288538;
    lVar10 = *(long *)(param_1 + 0x2b0);
    piVar7 = (int *)(lVar10 + 0x10);
    if (*piVar7 == 0) {
      do {
        if (*piVar7 != 0) {
          ClearExclusiveLocal();
          goto code_r0x0228841c;
        }
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
        if (bVar3) {
          *piVar7 = 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      iVar5 = pthread_key_create((undefined4 *)(lVar10 + 8),
                              PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8
                             );
      if (iVar5 == 0) goto code_r0x0228841c;
code_r0x0228842c:
      lVar6 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar10);
    }
    else {
code_r0x0228841c:
      lVar6 = pthread_getspecific(*(undefined4 *)(lVar10 + 8));
      if (lVar6 == 0) goto code_r0x0228842c;
    }
    if (lVar6 == 0) {
      glBindBuffer(0x8892,0);
    }
    else if (*(int *)(lVar6 + 0xcc) != 0) {
      glBindBuffer(0x8892,0);
      *(undefined4 *)(lVar6 + 0xcc) = 0;
    }
    uVar9 = *(uint *)(param_1 + 0x150);
    if (0 < (int)uVar9) {
      lVar10 = 0;
      uVar11 = 0;
      do {
        if ((uVar9 & 1) != 0) {
          lVar6 = 0x20;
          if (*(int *)(param_1 + 0x230) == 1) {
            uVar1 = uVar11 + 1;
          }
          else {
            lVar6 = 0x100;
            uVar1 = uVar11;
          }
          uVar1 = *(uint *)(*(long *)(*(long *)(param_1 + 0x8440) + 0x20) +
                           (long)*(int *)(*(long *)(param_1 + 0x8418) + lVar6 + (ulong)uVar1 * 4 +
                                         0x48) * 4);
          if (-1 < (int)uVar1) {
            *(uint *)(param_1 + 0x154) = *(uint *)(param_1 + 0x154) | 1 << (ulong)(uVar1 & 0x1f);
            (*pcRam0000000002dd0808)(uVar1,1);
            glEnableVertexAttribArray(uVar1);
            glVertexAttribPointer(uVar1,4,0x1406,0,*(undefined4 *)(param_1 + 0x158),
                            *(long *)(param_1 + 0x148) + lVar10);
            lVar10 = lVar10 + 0x10;
            *(undefined1 *)(param_2 + (int)uVar1 + 0x38c) = 1;
            *(undefined1 *)(param_2 + (int)uVar1 + 0x3ac) = 1;
          }
        }
        uVar9 = uVar9 >> 1;
        uVar11 = uVar11 + 1;
      } while (uVar9 != 0);
    }
    goto code_r0x02288538;
  }
  lVar10 = *(long *)(param_1 + 0x2b0);
  piVar7 = (int *)(lVar10 + 0x10);
  if (*piVar7 == 0) {
    do {
      if (*piVar7 != 0) {
        ClearExclusiveLocal();
        goto code_r0x02288264;
      }
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    iVar4 = pthread_key_create((undefined4 *)(lVar10 + 8),
                            PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8);
    if (iVar4 == 0) goto code_r0x02288264;
code_r0x02288298:
    lVar6 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar10);
    if (lVar6 == 0) goto code_r0x022882a8;
code_r0x02288278:
    if (*(int *)(lVar6 + 0xcc) != iVar5) {
      glBindBuffer(0x8892,iVar5);
      *(int *)(lVar6 + 0xcc) = iVar5;
    }
  }
  else {
code_r0x02288264:
    lVar6 = pthread_getspecific(*(undefined4 *)(lVar10 + 8));
    if (lVar6 == 0) goto code_r0x02288298;
    if (lVar6 != 0) goto code_r0x02288278;
code_r0x022882a8:
    glBindBuffer(0x8892,iVar5);
  }
  uVar9 = *(uint *)(param_1 + 0x150);
  if (0 < (int)uVar9) {
    lVar10 = 0;
    uVar11 = 0;
    do {
      if ((uVar9 & 1) != 0) {
        lVar6 = 0x20;
        if (*(int *)(param_1 + 0x230) == 1) {
          uVar1 = uVar11 + 1;
        }
        else {
          lVar6 = 0x100;
          uVar1 = uVar11;
        }
        uVar1 = *(uint *)(*(long *)(*(long *)(param_1 + 0x8440) + 0x20) +
                         (long)*(int *)(*(long *)(param_1 + 0x8418) + lVar6 + (ulong)uVar1 * 4 +
                                       0x48) * 4);
        if (-1 < (int)uVar1) {
          *(uint *)(param_1 + 0x154) = *(uint *)(param_1 + 0x154) | 1 << (ulong)(uVar1 & 0x1f);
          (*pcRam0000000002dd0808)(uVar1,1);
          glEnableVertexAttribArray(uVar1);
          glVertexAttribPointer(uVar1,4,0x1406,0,*(undefined4 *)(param_1 + 0x158),lVar10);
          lVar10 = lVar10 + 0x10;
          *(undefined1 *)(param_2 + (int)uVar1 + 0x38c) = 1;
          *(undefined1 *)(param_2 + (int)uVar1 + 0x3ac) = 1;
        }
      }
      uVar9 = uVar9 >> 1;
      uVar11 = uVar11 + 1;
    } while (uVar9 != 0);
  }
  lVar10 = *(long *)(param_1 + 0x2b0);
  piVar7 = (int *)(lVar10 + 0x10);
  if (*piVar7 == 0) {
    do {
      if (*piVar7 != 0) {
        ClearExclusiveLocal();
        goto code_r0x022883c8;
      }
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    iVar5 = pthread_key_create((undefined4 *)(lVar10 + 8),
                            PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8);
    if (iVar5 == 0) goto code_r0x022883c8;
code_r0x022883f8:
    lVar6 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar10);
  }
  else {
code_r0x022883c8:
    lVar6 = pthread_getspecific(*(undefined4 *)(lVar10 + 8));
    if (lVar6 == 0) goto code_r0x022883f8;
  }
  if (lVar6 == 0) {
    glBindBuffer(0x8892,0);
  }
  else if (*(int *)(lVar6 + 0xcc) != 0) {
    glBindBuffer(0x8892,0);
    *(undefined4 *)(lVar6 + 0xcc) = 0;
  }
code_r0x02288538:
  uVar9 = *(uint *)(*(long *)(param_1 + 0x8418) + 0x168);
  if ((int)uVar9 < 1) {
    uVar9 = 0;
  }
  else {
    uVar8 = 0;
    do {
      lVar10 = param_2 + uVar8;
      iVar5 = *(int *)(*(long *)(*(long *)(param_1 + 0x8440) + 0x20) + uVar8 * 4);
      *(bool *)(lVar10 + 0x38c) = iVar5 != -1;
      if ((iVar5 != -1) != (bool)*(char *)(lVar10 + 0x3ac)) {
        if (iVar5 == -1) {
          glDisableVertexAttribArray(uVar8 & 0xffffffff);
        }
        else {
          glEnableVertexAttribArray();
        }
        *(undefined1 *)(lVar10 + 0x3ac) = *(undefined1 *)(lVar10 + 0x38c);
      }
      uVar8 = uVar8 + 1;
    } while (uVar9 != uVar8);
  }
  uVar11 = *(uint *)(param_1 + 0x2a8);
  if (0x1f < uVar11) {
    uVar11 = 0x20;
  }
  if ((int)uVar9 < (int)uVar11) {
    uVar8 = (ulong)(int)uVar9;
    do {
      lVar10 = param_2 + uVar8;
      *(undefined1 *)(lVar10 + 0x38c) = 0;
      if (*(char *)(lVar10 + 0x3ac) != '\0') {
        glDisableVertexAttribArray(uVar8 & 0xffffffff);
        *(undefined1 *)(lVar10 + 0x3ac) = *(undefined1 *)(lVar10 + 0x38c);
      }
      uVar8 = uVar8 + 1;
    } while ((long)uVar8 < (long)(ulong)uVar11);
  }
  return;
}

// ==== Aska::RenderDeviceData::LastMinuteDrawCommands_Textures(Aska::ASKA_OGL_STATESET0*, Aska::RenderDeviceGL*)
// vaddr 0x218887c | ghidra 0x228887c | size 2544 | symbol _ZN4Aska16RenderDeviceData31LastMinuteDrawCommands_TexturesEPNS_18ASKA_OGL_STATESET0EPNS_14RenderDeviceGLE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderDeviceData31LastMinuteDrawCommands_TexturesEPNS_18ASKA_OGL_STATESET0EPNS_14RenderDeviceGLE
               (long param_1,long param_2,long param_3)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  undefined *puVar6;
  int iVar7;
  long lVar8;
  ulong uVar9;
  long lVar10;
  int *piVar11;
  long lVar12;
  undefined4 uStack_64;
  
  puVar6 = PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8;
  iVar7 = *(int *)(param_3 + 0xeaa88);
  uVar9 = (ulong)(iVar7 - 1);
  if (param_2 == 0) {
    while (iVar7 != 0) {
      Aska::RenderDeviceGL::ActiveTexture(unsigned int)(param_3,uVar9);
      lVar12 = *(long *)(param_1 + 0x2b0);
      piVar11 = (int *)(lVar12 + 0x10);
      if (*piVar11 == 0) {
        do {
          if (*piVar11 != 0) {
            ClearExclusiveLocal();
            goto code_r0x02288e54;
          }
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar5) {
            *piVar11 = 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        iVar7 = pthread_key_create((undefined4 *)(lVar12 + 8),puVar6);
        if (iVar7 == 0) goto code_r0x02288e54;
code_r0x02288e74:
        lVar10 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar12);
        if (lVar10 == 0) goto code_r0x02288e80;
code_r0x02288e64:
        uVar1 = *(undefined4 *)(lVar10 + (ulong)*(byte *)(lVar10 + 200) * 4 + 8);
      }
      else {
code_r0x02288e54:
        lVar10 = pthread_getspecific(*(undefined4 *)(lVar12 + 8));
        if (lVar10 == 0) goto code_r0x02288e74;
        if (lVar10 != 0) goto code_r0x02288e64;
code_r0x02288e80:
        uStack_64 = 0;
        glGetIntegerv(0x8069,&uStack_64);
        uVar1 = uStack_64;
      }
      lVar12 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      if (*(int *)(lVar12 + 8) != 0x812f) {
        glTexParameteri(0xde1,0x2802,0x812f);
        *(undefined4 *)(lVar12 + 8) = 0x812f;
      }
      lVar12 = *(long *)(param_1 + 0x2b0);
      piVar11 = (int *)(lVar12 + 0x10);
      if (*piVar11 == 0) {
        do {
          if (*piVar11 != 0) {
            ClearExclusiveLocal();
            goto code_r0x02288efc;
          }
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar5) {
            *piVar11 = 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        iVar7 = pthread_key_create((undefined4 *)(lVar12 + 8),puVar6);
        if (iVar7 == 0) goto code_r0x02288efc;
code_r0x02288f1c:
        lVar10 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar12);
        if (lVar10 == 0) goto code_r0x02288f28;
code_r0x02288f0c:
        uVar1 = *(undefined4 *)(lVar10 + (ulong)*(byte *)(lVar10 + 200) * 4 + 8);
      }
      else {
code_r0x02288efc:
        lVar10 = pthread_getspecific(*(undefined4 *)(lVar12 + 8));
        if (lVar10 == 0) goto code_r0x02288f1c;
        if (lVar10 != 0) goto code_r0x02288f0c;
code_r0x02288f28:
        uStack_64 = 0;
        glGetIntegerv(0x8069,&uStack_64);
        uVar1 = uStack_64;
      }
      lVar12 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      if (*(int *)(lVar12 + 0xc) != 0x812f) {
        glTexParameteri(0xde1,0x2803,0x812f);
        *(undefined4 *)(lVar12 + 0xc) = 0x812f;
      }
      Aska::RenderDeviceData::UpdateTextureFilters(Aska::ASKA_OGL_STATESET0*, int, unsigned int)(param_1,0,0xde1,uVar9);
      lVar12 = *(long *)(param_1 + 0x2b0);
      piVar11 = (int *)(lVar12 + 0x10);
      if (*piVar11 == 0) {
        do {
          if (*piVar11 != 0) {
            ClearExclusiveLocal();
            goto code_r0x02288fb8;
          }
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar5) {
            *piVar11 = 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        iVar7 = pthread_key_create((undefined4 *)(lVar12 + 8),puVar6);
        if (iVar7 == 0) goto code_r0x02288fb8;
code_r0x02288fd8:
        lVar10 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar12);
        if (lVar10 == 0) goto code_r0x02288fe4;
code_r0x02288fc8:
        uVar1 = *(undefined4 *)(lVar10 + (ulong)*(byte *)(lVar10 + 200) * 4 + 0x48);
      }
      else {
code_r0x02288fb8:
        lVar10 = pthread_getspecific(*(undefined4 *)(lVar12 + 8));
        if (lVar10 == 0) goto code_r0x02288fd8;
        if (lVar10 != 0) goto code_r0x02288fc8;
code_r0x02288fe4:
        uStack_64 = 0;
        glGetIntegerv(0x8514,&uStack_64);
        uVar1 = uStack_64;
      }
      lVar12 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      if (*(int *)(lVar12 + 8) != 0x812f) {
        glTexParameteri(0x8513,0x2802,0x812f);
        *(undefined4 *)(lVar12 + 8) = 0x812f;
      }
      lVar12 = *(long *)(param_1 + 0x2b0);
      piVar11 = (int *)(lVar12 + 0x10);
      if (*piVar11 == 0) {
        do {
          if (*piVar11 != 0) {
            ClearExclusiveLocal();
            goto code_r0x02289060;
          }
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar5) {
            *piVar11 = 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        iVar7 = pthread_key_create((undefined4 *)(lVar12 + 8),puVar6);
        if (iVar7 == 0) goto code_r0x02289060;
code_r0x02289080:
        lVar10 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar12);
        if (lVar10 == 0) goto code_r0x0228908c;
code_r0x02289070:
        uVar1 = *(undefined4 *)(lVar10 + (ulong)*(byte *)(lVar10 + 200) * 4 + 0x48);
      }
      else {
code_r0x02289060:
        lVar10 = pthread_getspecific(*(undefined4 *)(lVar12 + 8));
        if (lVar10 == 0) goto code_r0x02289080;
        if (lVar10 != 0) goto code_r0x02289070;
code_r0x0228908c:
        uStack_64 = 0;
        glGetIntegerv(0x8514,&uStack_64);
        uVar1 = uStack_64;
      }
      lVar12 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      if (*(int *)(lVar12 + 0xc) != 0x812f) {
        glTexParameteri(0x8513,0x2803,0x812f);
        *(undefined4 *)(lVar12 + 0xc) = 0x812f;
      }
      Aska::RenderDeviceData::UpdateTextureFilters(Aska::ASKA_OGL_STATESET0*, int, unsigned int)(param_1,0,0x8513,uVar9);
      lVar12 = *(long *)(param_1 + 0x2b0);
      piVar11 = (int *)(lVar12 + 0x10);
      if (*piVar11 == 0) {
        do {
          if (*piVar11 != 0) {
            ClearExclusiveLocal();
            goto code_r0x0228911c;
          }
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar5) {
            *piVar11 = 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        iVar7 = pthread_key_create((undefined4 *)(lVar12 + 8),puVar6);
        if (iVar7 == 0) goto code_r0x0228911c;
code_r0x0228913c:
        lVar10 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar12);
        if (lVar10 == 0) goto code_r0x02289148;
code_r0x0228912c:
        uVar1 = *(undefined4 *)(lVar10 + (ulong)*(byte *)(lVar10 + 200) * 4 + 0x88);
      }
      else {
code_r0x0228911c:
        lVar10 = pthread_getspecific(*(undefined4 *)(lVar12 + 8));
        if (lVar10 == 0) goto code_r0x0228913c;
        if (lVar10 != 0) goto code_r0x0228912c;
code_r0x02289148:
        uStack_64 = 0;
        glGetIntegerv(0x806a,&uStack_64);
        uVar1 = uStack_64;
      }
      lVar12 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      if (*(int *)(lVar12 + 8) != 0x812f) {
        glTexParameteri(0x806f,0x2802,0x812f);
        *(undefined4 *)(lVar12 + 8) = 0x812f;
      }
      lVar12 = *(long *)(param_1 + 0x2b0);
      piVar11 = (int *)(lVar12 + 0x10);
      if (*piVar11 == 0) {
        do {
          if (*piVar11 != 0) {
            ClearExclusiveLocal();
            goto code_r0x022891c4;
          }
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar5) {
            *piVar11 = 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        iVar7 = pthread_key_create((undefined4 *)(lVar12 + 8),puVar6);
        if (iVar7 == 0) goto code_r0x022891c4;
code_r0x022891e4:
        lVar10 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar12);
        if (lVar10 == 0) goto code_r0x022891f0;
code_r0x022891d4:
        uVar1 = *(undefined4 *)(lVar10 + (ulong)*(byte *)(lVar10 + 200) * 4 + 0x88);
      }
      else {
code_r0x022891c4:
        lVar10 = pthread_getspecific(*(undefined4 *)(lVar12 + 8));
        if (lVar10 == 0) goto code_r0x022891e4;
        if (lVar10 != 0) goto code_r0x022891d4;
code_r0x022891f0:
        uStack_64 = 0;
        glGetIntegerv(0x806a,&uStack_64);
        uVar1 = uStack_64;
      }
      lVar12 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      if (*(int *)(lVar12 + 0xc) != 0x812f) {
        glTexParameteri(0x806f,0x2803,0x812f);
        *(undefined4 *)(lVar12 + 0xc) = 0x812f;
      }
      Aska::RenderDeviceData::UpdateTextureFilters(Aska::ASKA_OGL_STATESET0*, int, unsigned int)(param_1,0,0x806f,uVar9);
      iVar7 = (int)uVar9;
      uVar9 = (ulong)(iVar7 - 1);
    }
  }
  else if (iVar7 != 0) {
    do {
      lVar12 = param_2 + uVar9 * 4;
      if (*(int *)(lVar12 + 8) != 0) {
        Aska::RenderDeviceGL::ActiveTexture(unsigned int)(param_3,uVar9 & 0xffffffff);
        Aska::RenderDeviceData::UpdateTextureFilters(Aska::ASKA_OGL_STATESET0*, int, unsigned int)(param_1,param_2,0xde1,uVar9 & 0xffffffff);
        lVar10 = param_2 + uVar9 * 0x18;
        uVar2 = *(uint *)(lVar10 + 0x16c);
        uVar3 = *(uint *)(lVar10 + 0x170);
        if (uVar2 < 5) {
          lVar10 = *(long *)(param_1 + 0x2b0);
          piVar11 = (int *)(lVar10 + 0x10);
          if (*piVar11 == 0) {
            do {
              if (*piVar11 != 0) {
                ClearExclusiveLocal();
                goto code_r0x02288954;
              }
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
              if (bVar5) {
                *piVar11 = 1;
                cVar4 = ExclusiveMonitorsStatus();
              }
            } while (cVar4 != '\0');
            iVar7 = pthread_key_create((undefined4 *)(lVar10 + 8),
                                    PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8
                                   );
            if (iVar7 == 0) goto code_r0x02288954;
code_r0x02288978:
            lVar8 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar10);
            iVar7 = *(int *)(&UNK_029cef80 + (long)(int)uVar2 * 4);
            if (lVar8 == 0) goto code_r0x02288988;
code_r0x02288968:
            uVar1 = *(undefined4 *)(lVar8 + (ulong)*(byte *)(lVar8 + 200) * 4 + 8);
          }
          else {
code_r0x02288954:
            lVar8 = pthread_getspecific(*(undefined4 *)(lVar10 + 8));
            if (lVar8 == 0) goto code_r0x02288978;
            iVar7 = *(int *)(&UNK_029cef80 + (long)(int)uVar2 * 4);
            if (lVar8 != 0) goto code_r0x02288968;
code_r0x02288988:
            uStack_64 = 0;
            glGetIntegerv(0x8069,&uStack_64);
            uVar1 = uStack_64;
          }
          lVar10 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
          if (*(int *)(lVar10 + 8) != iVar7) {
            glTexParameteri(0xde1,0x2802,iVar7);
            *(int *)(lVar10 + 8) = iVar7;
          }
        }
        if (uVar3 < 5) {
          lVar10 = *(long *)(param_1 + 0x2b0);
          piVar11 = (int *)(lVar10 + 0x10);
          if (*piVar11 == 0) {
            do {
              if (*piVar11 != 0) {
                ClearExclusiveLocal();
                goto code_r0x02288a10;
              }
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
              if (bVar5) {
                *piVar11 = 1;
                cVar4 = ExclusiveMonitorsStatus();
              }
            } while (cVar4 != '\0');
            iVar7 = pthread_key_create((undefined4 *)(lVar10 + 8),
                                    PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8
                                   );
            if (iVar7 == 0) goto code_r0x02288a10;
code_r0x02288a34:
            lVar8 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar10);
            iVar7 = *(int *)(&UNK_029cef80 + (long)(int)uVar3 * 4);
            if (lVar8 == 0) goto code_r0x02288a44;
code_r0x02288a24:
            uVar1 = *(undefined4 *)(lVar8 + (ulong)*(byte *)(lVar8 + 200) * 4 + 8);
          }
          else {
code_r0x02288a10:
            lVar8 = pthread_getspecific(*(undefined4 *)(lVar10 + 8));
            if (lVar8 == 0) goto code_r0x02288a34;
            iVar7 = *(int *)(&UNK_029cef80 + (long)(int)uVar3 * 4);
            if (lVar8 != 0) goto code_r0x02288a24;
code_r0x02288a44:
            uStack_64 = 0;
            glGetIntegerv(0x8069,&uStack_64);
            uVar1 = uStack_64;
          }
          lVar10 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
          if (*(int *)(lVar10 + 0xc) != iVar7) {
            glTexParameteri(0xde1,0x2803,iVar7);
            *(int *)(lVar10 + 0xc) = iVar7;
          }
        }
      }
      if (*(int *)(lVar12 + 0x48) != 0) {
        Aska::RenderDeviceGL::ActiveTexture(unsigned int)(param_3,uVar9 & 0xffffffff);
        Aska::RenderDeviceData::UpdateTextureFilters(Aska::ASKA_OGL_STATESET0*, int, unsigned int)(param_1,param_2,0x8513,uVar9 & 0xffffffff);
        lVar12 = param_2 + uVar9 * 0x18;
        uVar2 = *(uint *)(lVar12 + 0x16c);
        uVar3 = *(uint *)(lVar12 + 0x170);
        if (uVar2 < 5) {
          lVar12 = *(long *)(param_1 + 0x2b0);
          piVar11 = (int *)(lVar12 + 0x10);
          if (*piVar11 == 0) {
            do {
              if (*piVar11 != 0) {
                ClearExclusiveLocal();
                goto code_r0x02288b04;
              }
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
              if (bVar5) {
                *piVar11 = 1;
                cVar4 = ExclusiveMonitorsStatus();
              }
            } while (cVar4 != '\0');
            iVar7 = pthread_key_create((undefined4 *)(lVar12 + 8),
                                    PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8
                                   );
            if (iVar7 == 0) goto code_r0x02288b04;
code_r0x02288b28:
            lVar10 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar12);
            iVar7 = *(int *)(&UNK_029cef80 + (long)(int)uVar2 * 4);
            if (lVar10 == 0) goto code_r0x02288b38;
code_r0x02288b18:
            uVar1 = *(undefined4 *)(lVar10 + (ulong)*(byte *)(lVar10 + 200) * 4 + 0x48);
          }
          else {
code_r0x02288b04:
            lVar10 = pthread_getspecific(*(undefined4 *)(lVar12 + 8));
            if (lVar10 == 0) goto code_r0x02288b28;
            iVar7 = *(int *)(&UNK_029cef80 + (long)(int)uVar2 * 4);
            if (lVar10 != 0) goto code_r0x02288b18;
code_r0x02288b38:
            uStack_64 = 0;
            glGetIntegerv(0x8514,&uStack_64);
            uVar1 = uStack_64;
          }
          lVar12 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
          if (*(int *)(lVar12 + 8) != iVar7) {
            glTexParameteri(0x8513,0x2802,iVar7);
            *(int *)(lVar12 + 8) = iVar7;
          }
        }
        if (uVar3 < 5) {
          lVar12 = *(long *)(param_1 + 0x2b0);
          piVar11 = (int *)(lVar12 + 0x10);
          if (*piVar11 == 0) {
            do {
              if (*piVar11 != 0) {
                ClearExclusiveLocal();
                goto code_r0x02288bc0;
              }
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
              if (bVar5) {
                *piVar11 = 1;
                cVar4 = ExclusiveMonitorsStatus();
              }
            } while (cVar4 != '\0');
            iVar7 = pthread_key_create((undefined4 *)(lVar12 + 8),
                                    PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8
                                   );
            if (iVar7 == 0) goto code_r0x02288bc0;
code_r0x02288be4:
            lVar10 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar12);
            iVar7 = *(int *)(&UNK_029cef80 + (long)(int)uVar3 * 4);
            if (lVar10 == 0) goto code_r0x02288bf4;
code_r0x02288bd4:
            uVar1 = *(undefined4 *)(lVar10 + (ulong)*(byte *)(lVar10 + 200) * 4 + 0x48);
          }
          else {
code_r0x02288bc0:
            lVar10 = pthread_getspecific(*(undefined4 *)(lVar12 + 8));
            if (lVar10 == 0) goto code_r0x02288be4;
            iVar7 = *(int *)(&UNK_029cef80 + (long)(int)uVar3 * 4);
            if (lVar10 != 0) goto code_r0x02288bd4;
code_r0x02288bf4:
            uStack_64 = 0;
            glGetIntegerv(0x8514,&uStack_64);
            uVar1 = uStack_64;
          }
          lVar12 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
          if (*(int *)(lVar12 + 0xc) != iVar7) {
            glTexParameteri(0x8513,0x2803,iVar7);
            *(int *)(lVar12 + 0xc) = iVar7;
          }
        }
      }
      if (*(int *)(param_2 + uVar9 * 4 + 0x88) != 0) {
        Aska::RenderDeviceGL::ActiveTexture(unsigned int)(param_3,uVar9 & 0xffffffff);
        Aska::RenderDeviceData::UpdateTextureFilters(Aska::ASKA_OGL_STATESET0*, int, unsigned int)(param_1,param_2,0x806f,uVar9 & 0xffffffff);
        lVar12 = param_2 + uVar9 * 0x18;
        uVar2 = *(uint *)(lVar12 + 0x16c);
        uVar3 = *(uint *)(lVar12 + 0x170);
        if (uVar2 < 5) {
          lVar12 = *(long *)(param_1 + 0x2b0);
          piVar11 = (int *)(lVar12 + 0x10);
          if (*piVar11 == 0) {
            do {
              if (*piVar11 != 0) {
                ClearExclusiveLocal();
                goto code_r0x02288cb8;
              }
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
              if (bVar5) {
                *piVar11 = 1;
                cVar4 = ExclusiveMonitorsStatus();
              }
            } while (cVar4 != '\0');
            iVar7 = pthread_key_create((undefined4 *)(lVar12 + 8),
                                    PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8
                                   );
            if (iVar7 == 0) goto code_r0x02288cb8;
code_r0x02288cdc:
            lVar10 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar12);
            iVar7 = *(int *)(&UNK_029cef80 + (long)(int)uVar2 * 4);
            if (lVar10 == 0) goto code_r0x02288cec;
code_r0x02288ccc:
            uVar1 = *(undefined4 *)(lVar10 + (ulong)*(byte *)(lVar10 + 200) * 4 + 0x88);
          }
          else {
code_r0x02288cb8:
            lVar10 = pthread_getspecific(*(undefined4 *)(lVar12 + 8));
            if (lVar10 == 0) goto code_r0x02288cdc;
            iVar7 = *(int *)(&UNK_029cef80 + (long)(int)uVar2 * 4);
            if (lVar10 != 0) goto code_r0x02288ccc;
code_r0x02288cec:
            uStack_64 = 0;
            glGetIntegerv(0x806a,&uStack_64);
            uVar1 = uStack_64;
          }
          lVar12 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
          if (*(int *)(lVar12 + 8) != iVar7) {
            glTexParameteri(0x806f,0x2802,iVar7);
            *(int *)(lVar12 + 8) = iVar7;
          }
        }
        if (uVar3 < 5) {
          lVar12 = *(long *)(param_1 + 0x2b0);
          piVar11 = (int *)(lVar12 + 0x10);
          if (*piVar11 == 0) {
            do {
              if (*piVar11 != 0) {
                ClearExclusiveLocal();
                goto code_r0x02288d74;
              }
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar11,0x10);
              if (bVar5) {
                *piVar11 = 1;
                cVar4 = ExclusiveMonitorsStatus();
              }
            } while (cVar4 != '\0');
            iVar7 = pthread_key_create((undefined4 *)(lVar12 + 8),
                                    PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8
                                   );
            if (iVar7 == 0) goto code_r0x02288d74;
code_r0x02288d98:
            lVar10 = Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()(lVar12);
            iVar7 = *(int *)(&UNK_029cef80 + (long)(int)uVar3 * 4);
            if (lVar10 == 0) goto code_r0x02288da8;
code_r0x02288d88:
            uVar1 = *(undefined4 *)(lVar10 + (ulong)*(byte *)(lVar10 + 200) * 4 + 0x88);
          }
          else {
code_r0x02288d74:
            lVar10 = pthread_getspecific(*(undefined4 *)(lVar12 + 8));
            if (lVar10 == 0) goto code_r0x02288d98;
            iVar7 = *(int *)(&UNK_029cef80 + (long)(int)uVar3 * 4);
            if (lVar10 != 0) goto code_r0x02288d88;
code_r0x02288da8:
            uStack_64 = 0;
            glGetIntegerv(0x806a,&uStack_64);
            uVar1 = uStack_64;
          }
          lVar12 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
          if (*(int *)(lVar12 + 0xc) != iVar7) {
            glTexParameteri(0x806f,0x2803,iVar7);
            *(int *)(lVar12 + 0xc) = iVar7;
          }
        }
      }
      bVar5 = uVar9 != 0;
      uVar9 = uVar9 - 1;
    } while (bVar5);
  }
  return;
}

// ==== Aska::RenderDeviceData::UpdateTextureFilters(Aska::ASKA_OGL_STATESET0*, int, unsigned int)
// vaddr 0x218926c | ghidra 0x228926c | size 996 | symbol _ZN4Aska16RenderDeviceData20UpdateTextureFiltersEPNS_18ASKA_OGL_STATESET0Eij | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderDeviceData20UpdateTextureFiltersEPNS_18ASKA_OGL_STATESET0Eij
               (long param_1,long param_2,undefined4 param_3,uint param_4)

{
  undefined4 uVar1;
  int *piVar2;
  long lVar3;
  undefined8 uVar4;
  int iVar5;
  ulong uVar6;
  
  iVar5 = *(int *)(param_2 + (ulong)param_4 * 0x18 + 0x178);
  uVar6 = (ulong)param_4;
  if (iVar5 == 2) {
    if (*(char *)(param_2 + uVar6 * 0x18 + 0x180) == '\0') {
      uVar1 = Aska::RenderDeviceData::GetBoundTextureID(unsigned int)(param_1,param_3);
      piVar2 = (int *)Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      if (*piVar2 != 0x2601) {
        *piVar2 = 0x2601;
        glTexParameteri(param_3,0x2801,0x2601);
      }
      uVar1 = Aska::RenderDeviceData::GetBoundTextureID(unsigned int)(param_1,param_3);
      lVar3 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      iVar5 = *(int *)(lVar3 + 4);
    }
    else {
      iVar5 = 0x2703;
      if (*(int *)(param_2 + uVar6 * 0x18 + 0x17c) != 1) {
        iVar5 = 0x2701;
      }
      uVar1 = Aska::RenderDeviceData::GetBoundTextureID(unsigned int)(param_1,param_3);
      piVar2 = (int *)Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      if (*piVar2 != iVar5) {
        *piVar2 = iVar5;
        glTexParameteri(param_3,0x2801,iVar5);
      }
      uVar1 = Aska::RenderDeviceData::GetBoundTextureID(unsigned int)(param_1,param_3);
      lVar3 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      iVar5 = *(int *)(lVar3 + 4);
    }
    if (iVar5 != 0x2601) {
      *(undefined4 *)(lVar3 + 4) = 0x2601;
      glTexParameteri(param_3,0x2800,0x2601);
    }
    if (*(char *)(param_1 + 6) == '\0') {
      return;
    }
    uVar1 = Aska::RenderDeviceData::GetBoundTextureID(unsigned int)(param_1,param_3);
    lVar3 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
    if (*(int *)(lVar3 + 0x10) == 2) {
      return;
    }
    glTexParameterf(0x40000000,param_3,0x84fe);
    uVar1 = 2;
    goto code_r0x02289640;
  }
  if (iVar5 == 1) {
    if (*(char *)(param_2 + uVar6 * 0x18 + 0x180) == '\0') {
      uVar1 = Aska::RenderDeviceData::GetBoundTextureID(unsigned int)(param_1,param_3);
      piVar2 = (int *)Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      if (*piVar2 != 0x2601) {
        *piVar2 = 0x2601;
        glTexParameteri(param_3,0x2801,0x2601);
      }
      uVar1 = Aska::RenderDeviceData::GetBoundTextureID(unsigned int)(param_1,param_3);
      lVar3 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      iVar5 = *(int *)(lVar3 + 4);
    }
    else {
      iVar5 = 0x2703;
      if (*(int *)(param_2 + uVar6 * 0x18 + 0x17c) != 1) {
        iVar5 = 0x2701;
      }
      uVar1 = Aska::RenderDeviceData::GetBoundTextureID(unsigned int)(param_1,param_3);
      piVar2 = (int *)Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      if (*piVar2 != iVar5) {
        *piVar2 = iVar5;
        glTexParameteri(param_3,0x2801,iVar5);
      }
      uVar1 = Aska::RenderDeviceData::GetBoundTextureID(unsigned int)(param_1,param_3);
      lVar3 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      iVar5 = *(int *)(lVar3 + 4);
    }
    if (iVar5 != 0x2601) {
      *(undefined4 *)(lVar3 + 4) = 0x2601;
      uVar4 = 0x2601;
      goto code_r0x022895f4;
    }
  }
  else {
    if (iVar5 != 0) {
      return;
    }
    if (*(char *)(param_2 + uVar6 * 0x18 + 0x180) == '\0') {
      uVar1 = Aska::RenderDeviceData::GetBoundTextureID(unsigned int)(param_1,param_3);
      piVar2 = (int *)Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      if (*piVar2 != 0x2600) {
        *piVar2 = 0x2600;
        glTexParameteri(param_3,0x2801,0x2600);
      }
      uVar1 = Aska::RenderDeviceData::GetBoundTextureID(unsigned int)(param_1,param_3);
      lVar3 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      iVar5 = *(int *)(lVar3 + 4);
    }
    else {
      iVar5 = 0x2702;
      if (*(int *)(param_2 + uVar6 * 0x18 + 0x17c) != 1) {
        iVar5 = 0x2700;
      }
      uVar1 = Aska::RenderDeviceData::GetBoundTextureID(unsigned int)(param_1,param_3);
      piVar2 = (int *)Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      if (*piVar2 != iVar5) {
        *piVar2 = iVar5;
        glTexParameteri(param_3,0x2801,iVar5);
      }
      uVar1 = Aska::RenderDeviceData::GetBoundTextureID(unsigned int)(param_1,param_3);
      lVar3 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
      iVar5 = *(int *)(lVar3 + 4);
    }
    if (iVar5 != 0x2600) {
      uVar4 = 0x2600;
      *(undefined4 *)(lVar3 + 4) = 0x2600;
code_r0x022895f4:
      glTexParameteri(param_3,0x2800,uVar4);
    }
  }
  if (*(char *)(param_1 + 6) == '\0') {
    return;
  }
  uVar1 = Aska::RenderDeviceData::GetBoundTextureID(unsigned int)(param_1,param_3);
  lVar3 = Aska::RenderDeviceData::GetTextureStateCaches(unsigned int)(param_1,uVar1);
  if (*(int *)(lVar3 + 0x10) == 1) {
    return;
  }
  glTexParameterf(0x3f800000,param_3,0x84fe);
  uVar1 = 1;
code_r0x02289640:
  *(undefined4 *)(lVar3 + 0x10) = uVar1;
  return;
}
