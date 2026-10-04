// port/decomp/render/state_cache.c: Ghidra decompiles for the render subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 14:58 UTC: tools/decomp.sh '--into' 'render/state_cache' 'StateCacheThreadSafe::' 'RenderDeviceData::LastMinuteDrawCommands_Blending' 'RenderDeviceData::LastMinuteDrawCommands_Depth'

// ==== Aska::StateCacheThreadSafe::ThreadDestruct()
// vaddr 0x21812c4 | ghidra 0x22812c4 | size 284 | symbol _ZN4Aska20StateCacheThreadSafe14ThreadDestructEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x02281350: Changing call to branch */

void _ZN4Aska20StateCacheThreadSafe14ThreadDestructEv(undefined8 *param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  long lVar4;
  int *piVar5;
  undefined8 *puVar6;
  undefined4 *puVar7;
  long lVar8;
  
  piVar5 = (int *)(param_1 + 2);
  puVar6 = param_1 + 1;
  if (*piVar5 == 0) {
    do {
      if (*piVar5 != 0) {
        ClearExclusiveLocal();
        goto code_r0x02281314;
      }
      cVar1 = '\x01';
      bVar2 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar2) {
        *piVar5 = 1;
        cVar1 = ExclusiveMonitorsStatus();
      }
    } while (cVar1 != '\0');
    iVar3 = pthread_key_create(puVar6,
                            PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv_02cbd3a8);
    if (iVar3 == 0) goto code_r0x02281314;
    lVar8 = 0;
  }
  else {
code_r0x02281314:
    lVar8 = pthread_getspecific(*(undefined4 *)puVar6);
  }
  Aska::ArrayThreadSafe::Remove(Aska::ASKA_OGL_STATESET0*)(*param_1,lVar8);
  lVar4 = pthread_getspecific(*(undefined4 *)(param_1 + 1));
  if (lVar8 == lVar4) {
    pthread_setspecific(*(undefined4 *)puVar6,0);
  }
  if (lVar8 != 0) goto code_r0x011d8ed0;
  piVar5 = (int *)((long)param_1 + 0x14);
  puVar7 = (undefined4 *)((long)param_1 + 0xc);
  if (*piVar5 == 0) {
    do {
      if (*piVar5 != 0) {
        ClearExclusiveLocal();
        goto code_r0x02281394;
      }
      cVar1 = '\x01';
      bVar2 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar2) {
        *piVar5 = 1;
        cVar1 = ExclusiveMonitorsStatus();
      }
    } while (cVar1 != '\0');
    iVar3 = pthread_key_create(puVar7,
                            PTR__ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct1EPv_02cbe1b0);
    if (iVar3 == 0) goto code_r0x02281394;
    lVar8 = 0;
  }
  else {
code_r0x02281394:
    lVar8 = pthread_getspecific(*puVar7);
  }
  lVar4 = pthread_getspecific(*puVar7);
  if (lVar8 == lVar4) {
    pthread_setspecific(*puVar7,0);
  }
  if (lVar8 == 0) {
    return;
  }
code_r0x011d8ed0:
  (*(code *)PTR__ZdlPv_02ca4758)(lVar8);
  return;
}

// ==== Aska::StateCacheThreadSafe::Static::ThreadDestruct0(void*)
// vaddr 0x21816f8 | ghidra 0x22816f8 | size 72 | symbol _ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct0EPv(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar2 = (undefined8 *)*param_1;
  Aska::ArrayThreadSafe::Remove(Aska::ASKA_OGL_STATESET0*)(*puVar2,param_1);
  puVar1 = (undefined8 *)pthread_getspecific(*(undefined4 *)(puVar2 + 1));
  if (puVar1 == param_1) {
    pthread_setspecific(*(undefined4 *)(puVar2 + 1),0);
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::StateCacheThreadSafe::Static::ThreadDestruct1(void*)
// vaddr 0x2181740 | ghidra 0x2281740 | size 60 | symbol _ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct1EPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20StateCacheThreadSafe6Static15ThreadDestruct1EPv(long *param_1)

{
  long *plVar1;
  long lVar2;
  
  lVar2 = *param_1;
  plVar1 = (long *)pthread_getspecific(*(undefined4 *)(lVar2 + 0xc));
  if (plVar1 == param_1) {
    pthread_setspecific(*(undefined4 *)(lVar2 + 0xc),0);
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::StateCacheThreadSafe::AllocateAndStoreStateSet0()
// vaddr 0x2185e8c | ghidra 0x2285e8c | size 272 | symbol _ZN4Aska20StateCacheThreadSafe25AllocateAndStoreStateSet0Ev | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska20StateCacheThreadSafe25AllocateAndStoreStateSet0Ev(undefined8 *param_1)

{
  int iVar1;
  long lVar2;
  
  lVar2 = operator new(unsigned long, std::nothrow_t const&)(0x3e0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar2 != 0) {
    *(undefined1 *)(lVar2 + 0x180) = 0;
    *(undefined1 *)(lVar2 + 0x198) = 0;
    *(undefined1 *)(lVar2 + 0x1b0) = 0;
    *(undefined1 *)(lVar2 + 0x1c8) = 0;
    *(undefined1 *)(lVar2 + 0x1e0) = 0;
    *(undefined1 *)(lVar2 + 0x1f8) = 0;
    *(undefined1 *)(lVar2 + 0x210) = 0;
    *(undefined1 *)(lVar2 + 0x228) = 0;
    *(undefined1 *)(lVar2 + 0x240) = 0;
    *(undefined4 *)(lVar2 + 0x23c) = 0;
    *(undefined1 *)(lVar2 + 600) = 0;
    *(undefined4 *)(lVar2 + 0x254) = 0;
    *(undefined1 *)(lVar2 + 0x270) = 0;
    *(undefined4 *)(lVar2 + 0x26c) = 0;
    *(undefined1 *)(lVar2 + 0x288) = 0;
    *(undefined4 *)(lVar2 + 0x284) = 0;
    *(undefined1 *)(lVar2 + 0x2a0) = 0;
    *(undefined4 *)(lVar2 + 0x29c) = 0;
    *(undefined1 *)(lVar2 + 0x2b8) = 0;
    *(undefined4 *)(lVar2 + 0x2b4) = 0;
    *(undefined1 *)(lVar2 + 0x2d0) = 0;
    *(undefined4 *)(lVar2 + 0x2cc) = 0;
    *(undefined1 *)(lVar2 + 0x2e8) = 0;
    *(undefined8 *)(lVar2 + 0x178) = 1;
    *(undefined8 *)(lVar2 + 400) = 1;
    *(undefined8 *)(lVar2 + 0x1a8) = 1;
    *(undefined8 *)(lVar2 + 0x1c0) = 1;
    *(undefined8 *)(lVar2 + 0x1d8) = 1;
    *(undefined8 *)(lVar2 + 0x1f0) = 1;
    *(undefined8 *)(lVar2 + 0x208) = 1;
    *(undefined8 *)(lVar2 + 0x220) = 1;
    *(undefined4 *)(lVar2 + 0x238) = 1;
    *(undefined4 *)(lVar2 + 0x250) = 1;
    *(undefined4 *)(lVar2 + 0x268) = 1;
    *(undefined4 *)(lVar2 + 0x280) = 1;
    *(undefined4 *)(lVar2 + 0x298) = 1;
    *(undefined4 *)(lVar2 + 0x2b0) = 1;
    *(undefined4 *)(lVar2 + 0x2c8) = 1;
    *(undefined4 *)(lVar2 + 0x2e0) = 1;
    *(undefined4 *)(lVar2 + 0x2e4) = 0;
    Aska::StateCacheThreadSafe::SetDefaults(Aska::ASKA_OGL_STATESET0*)(param_1,lVar2);
    iVar1 = pthread_setspecific(*(undefined4 *)(param_1 + 1),lVar2);
    if (iVar1 == 0) {
      Aska::ArrayThreadSafe::Add(Aska::ASKA_OGL_STATESET0*)(*param_1,lVar2);
    }
    else {
      operator delete(void*)(lVar2);
      lVar2 = 0;
    }
  }
  return lVar2;
}

// ==== Aska::StateCacheThreadSafe::SetDefaults(Aska::ASKA_OGL_STATESET0*)
// vaddr 0x2185f9c | ghidra 0x2285f9c | size 668 | symbol _ZN4Aska20StateCacheThreadSafe11SetDefaultsEPNS_18ASKA_OGL_STATESET0E | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska20StateCacheThreadSafe11SetDefaultsEPNS_18ASKA_OGL_STATESET0E
               (undefined8 param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  char cVar4;
  undefined4 uStack_24;
  
  memset(param_2,0xff,0x3e0);
  *(undefined2 *)(param_2 + 0x60) = 0xff7e;
  glDisable(0xb44);
  *(ushort *)(param_2 + 0x60) = *(ushort *)(param_2 + 0x60) & 0xfefd;
  glDisable(0xb71);
  *(ushort *)(param_2 + 0x60) = *(ushort *)(param_2 + 0x60) & 0xfdfb;
  glDisable(0xb90);
  *(ushort *)(param_2 + 0x60) = *(ushort *)(param_2 + 0x60) & 0xfbf7;
  glDisable(0xbe2);
  *(ushort *)(param_2 + 0x60) = *(ushort *)(param_2 + 0x60) & 0xf7ef;
  glDisable(0x809e);
  *(ushort *)(param_2 + 0x60) = *(ushort *)(param_2 + 0x60) | 0x1020;
  glEnable(0xbd0);
  *(ushort *)(param_2 + 0x60) = *(ushort *)(param_2 + 0x60) & 0xffbf;
  glDisable(0xc11);
  *(undefined8 *)((long)param_2 + 0x3d4) = 0xffffffffffffffff;
  *(undefined8 *)((long)param_2 + 0x3cc) = 0xffffffffffffffff;
  *(byte *)((long)param_2 + 0x304) = *(byte *)((long)param_2 + 0x304) | 0xf;
  *(undefined4 *)(param_2 + 0x61) = *(undefined4 *)((long)param_2 + 0x304);
  glColorMask(1,1,1,1);
  glGetFloatv(0x8038,(long)param_2 + 0x37c);
  glGetFloatv(0x8038,(long)param_2 + 900);
  glGetFloatv(0x2a00,param_2 + 0x70);
  glGetFloatv(0x2a00,param_2 + 0x71);
  glGetFloatv(0xb73,(long)param_2 + 0x374);
  glGetFloatv(0xc22,param_2 + 0x5e);
  glGetIntegerv(0xb91,param_2 + 0x6f);
  uVar2 = _UNK_029cd118;
  uVar1 = _UNK_029cd110;
  *(undefined4 *)(param_2 + 0x66) = 0x8006;
  *(undefined8 *)((long)param_2 + 0x324) = uVar2;
  *(undefined8 *)((long)param_2 + 0x31c) = uVar1;
  *(undefined4 *)((long)param_2 + 0x32c) = 0;
  *(undefined8 *)((long)param_2 + 0x354) = *(undefined8 *)((long)param_2 + 0x32c);
  *(undefined8 *)((long)param_2 + 0x34c) = *(undefined8 *)((long)param_2 + 0x324);
  *(undefined8 *)((long)param_2 + 0x344) = *(undefined8 *)((long)param_2 + 0x31c);
  *(undefined1 *)(param_2 + 0x30) = 0;
  param_2[0x2f] = 1;
  *(undefined1 *)(param_2 + 0x33) = 0;
  param_2[0x32] = 1;
  *(undefined1 *)(param_2 + 0x36) = 0;
  param_2[0x35] = 1;
  *(undefined1 *)(param_2 + 0x39) = 0;
  param_2[0x38] = 1;
  *(undefined1 *)(param_2 + 0x3c) = 0;
  param_2[0x3b] = 1;
  *(undefined1 *)(param_2 + 0x3f) = 0;
  param_2[0x3e] = 1;
  *(undefined1 *)(param_2 + 0x42) = 0;
  param_2[0x41] = 1;
  *(undefined1 *)(param_2 + 0x45) = 0;
  param_2[0x44] = 1;
  *(undefined1 *)(param_2 + 0x48) = 0;
  param_2[0x47] = 1;
  *(undefined1 *)(param_2 + 0x4b) = 0;
  param_2[0x4a] = 1;
  *(undefined1 *)(param_2 + 0x4e) = 0;
  param_2[0x4d] = 1;
  *(undefined1 *)(param_2 + 0x51) = 0;
  param_2[0x50] = 1;
  *(undefined1 *)(param_2 + 0x54) = 0;
  param_2[0x53] = 1;
  *(undefined1 *)(param_2 + 0x57) = 0;
  param_2[0x56] = 1;
  *(undefined1 *)(param_2 + 0x5a) = 0;
  param_2[0x59] = 1;
  *(undefined1 *)(param_2 + 0x5d) = 0;
  param_2[0x5c] = 1;
  memset((long)param_2 + 0xd4,0xff,0xb8);
  memset(param_2 + 1,0,0xc0);
  uStack_24 = 0xff;
  lVar3 = eglGetCurrentContext();
  if (lVar3 == 0) {
    cVar4 = '\0';
  }
  else {
    glGetIntegerv(0x84e0,&uStack_24);
    cVar4 = (char)uStack_24 + '@';
  }
  *(char *)(param_2 + 0x19) = cVar4;
  *(undefined8 *)((long)param_2 + 0x3c4) = 0;
  *(undefined8 *)((long)param_2 + 0x3bc) = 0;
  *(undefined8 *)((long)param_2 + 0x3b4) = 0;
  *(undefined8 *)((long)param_2 + 0x3ac) = 0;
  *(undefined8 *)((long)param_2 + 0x3a4) = 0;
  *(undefined8 *)((long)param_2 + 0x39c) = 0;
  *(undefined8 *)((long)param_2 + 0x394) = 0;
  *(undefined8 *)((long)param_2 + 0x38c) = 0;
  *param_2 = param_1;
  return;
}

// ==== Aska::RenderDeviceData::LastMinuteDrawCommands_Blending(Aska::ASKA_OGL_STATESET0*)
// vaddr 0x218861c | ghidra 0x228861c | size 388 | symbol _ZN4Aska16RenderDeviceData31LastMinuteDrawCommands_BlendingEPNS_18ASKA_OGL_STATESET0E | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RenderDeviceData31LastMinuteDrawCommands_BlendingEPNS_18ASKA_OGL_STATESET0E
               (undefined8 param_1,long param_2)

{
  ushort uVar1;
  bool bVar2;
  long lVar3;
  
  uVar1 = *(ushort *)(param_2 + 0x300) >> 3 & 1;
  if (uVar1 != (*(ushort *)(param_2 + 0x300) >> 10 & 1)) {
    if (uVar1 == 0) {
      glDisable(0xbe2);
    }
    else {
      glEnable(0xbe2);
    }
    uVar1 = *(ushort *)(param_2 + 0x300);
    *(ushort *)(param_2 + 0x300) = uVar1 & 0xf800 | uVar1 & 0x3ff | (uVar1 >> 3 & 1) << 10;
  }
  lVar3 = *(long *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  if ((*(int *)(lVar3 + 0xec0a0) == 3) && (299 < *(uint *)(lVar3 + 0xec0a4))) {
    if (*(int *)(lVar3 + 0xec0b8) < 4) {
      bVar2 = true;
    }
    else {
      bVar2 = *(int *)(lVar3 + 0xec0b8) == 4 && *(int *)(lVar3 + 0xec0bc) < 3;
    }
  }
  else {
    bVar2 = false;
  }
  if ((((*(int *)(param_2 + 0x344) != *(int *)(param_2 + 0x31c)) ||
       (*(int *)(param_2 + 0x348) != *(int *)(param_2 + 800))) ||
      (*(int *)(param_2 + 0x350) != *(int *)(param_2 + 0x328))) ||
     (*(int *)(param_2 + 0x354) != *(int *)(param_2 + 0x32c))) {
    if (bVar2) {
      glBlendFunc();
    }
    else {
      glBlendFuncSeparate(*(int *)(param_2 + 0x344),*(int *)(param_2 + 0x348),
                      *(undefined4 *)(param_2 + 0x350),*(undefined4 *)(param_2 + 0x354));
    }
    *(undefined4 *)(param_2 + 0x31c) = *(undefined4 *)(param_2 + 0x344);
    *(undefined4 *)(param_2 + 800) = *(undefined4 *)(param_2 + 0x348);
    *(undefined4 *)(param_2 + 0x328) = *(undefined4 *)(param_2 + 0x350);
    *(undefined4 *)(param_2 + 0x32c) = *(undefined4 *)(param_2 + 0x354);
  }
  if ((*(int *)(param_2 + 0x34c) != *(int *)(param_2 + 0x324)) ||
     (*(int *)(param_2 + 0x358) != *(int *)(param_2 + 0x330))) {
    if (bVar2) {
      glBlendEquation();
    }
    else {
      glBlendEquationSeparate(*(int *)(param_2 + 0x34c),*(undefined4 *)(param_2 + 0x358));
    }
    *(undefined4 *)(param_2 + 0x324) = *(undefined4 *)(param_2 + 0x34c);
    *(undefined4 *)(param_2 + 0x330) = *(undefined4 *)(param_2 + 0x358);
  }
  return;
}

// ==== Aska::RenderDeviceData::LastMinuteDrawCommands_Depth(Aska::ASKA_OGL_STATESET0*)
// vaddr 0x21887a0 | ghidra 0x22887a0 | size 220 | symbol _ZN4Aska16RenderDeviceData28LastMinuteDrawCommands_DepthEPNS_18ASKA_OGL_STATESET0E | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x022887c4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022887d0: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x022887c8) */
/* WARNING: Removing unreachable block (ram,0x022887d4) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16RenderDeviceData28LastMinuteDrawCommands_DepthEPNS_18ASKA_OGL_STATESET0E
               (undefined8 param_1,long param_2)

{
  ushort uVar1;
  float fVar2;
  undefined8 uVar3;
  
  uVar1 = *(ushort *)(param_2 + 0x300) >> 1 & 1;
  if (uVar1 == (*(ushort *)(param_2 + 0x300) >> 8 & 1)) {
    if (*(int *)(param_2 + 0x36c) != *(int *)(param_2 + 0x370)) {
      glDepthFunc();
      *(undefined4 *)(param_2 + 0x370) = *(undefined4 *)(param_2 + 0x36c);
    }
    if ((*(float *)(param_2 + 0x37c) == *(float *)(param_2 + 900)) &&
       (*(float *)(param_2 + 0x380) == *(float *)(param_2 + 0x388))) {
      return;
    }
    glPolygonOffset();
    fVar2 = _UNK_027fac84;
    *(float *)(param_2 + 900) = *(float *)(param_2 + 0x37c);
    *(float *)(param_2 + 0x388) = *(float *)(param_2 + 0x380);
    if ((ABS(*(float *)(param_2 + 0x37c)) <= fVar2) && (ABS(*(float *)(param_2 + 0x380)) <= fVar2))
    {
      uVar3 = 0x8037;
      goto code_r0x011e8440;
    }
    uVar3 = 0x8037;
  }
  else {
    if (uVar1 == 0) {
      uVar3 = 0xb71;
code_r0x011e8440:
      (*(code *)PTR_glDisable_02cac210)(uVar3);
      return;
    }
    uVar3 = 0xb71;
  }
  (*(code *)PTR_glEnable_02c9ddf8)(uVar3);
  return;
}
