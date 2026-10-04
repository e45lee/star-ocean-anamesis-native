// port/decomp/render/render_thread.c: Ghidra decompiles for the render subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:28 UTC: tools/decomp.sh '--into' 'render/render_thread' 'Aska::RenderThread::' 'Aska::RenderContextServer::'

// ==== Aska::RenderContextServer::RenderContextServer(int, int, int, int)
// vaddr 0x21b9258 | ghidra 0x22b9258 | size 312 | symbol _ZN4Aska19RenderContextServerC2Eiiii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19RenderContextServerC1Eiiii
               (long *param_1,undefined8 param_2,undefined4 param_3,uint param_4,int param_5)

{
  undefined *puVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  long lVar4;
  ulong uVar5;
  long *plVar6;
  
  puVar1 = PTR__ZTVN4Aska19RenderContextServerE_02cbe468 + 0x10;
  param_1[3] = 0;
  *param_1 = (long)puVar1;
  param_1[1] = 0;
  param_1[5] = 0;
  Aska::RenderContextServer::ReallocRenderContext(int)();
  Aska::RenderContextServer::ReallocBatch(int)(param_1,param_3);
  if (param_4 != 0) {
    auVar2._8_8_ = 0;
    auVar2._0_8_ = (long)(int)param_4;
    uVar5 = -(ulong)(param_4 >> 0x1f) & 0xfffffffc00000000 | (ulong)param_4 << 2;
    if (SUB168(auVar2 * ZEXT816(4),8) != 0) {
      uVar5 = 0xffffffffffffffff;
    }
    lVar4 = operator new[](unsigned long, unsigned long, bool)(uVar5,0x10,1);
    if (lVar4 != 0) {
      if (param_1[5] != 0) {
        operator delete[](void*)();
        param_1[5] = 0;
      }
      *(uint *)(param_1 + 6) = param_4;
      param_1[5] = lVar4;
      *(undefined4 *)((long)param_1 + 0x14) = 0;
      *(undefined4 *)((long)param_1 + 0x24) = 0;
      *(undefined4 *)((long)param_1 + 0x34) = 0;
      *(undefined4 *)(param_1 + 9) = 0;
      *(byte *)(param_1 + 10) = *(byte *)(param_1 + 10) ^ 1;
    }
  }
  plVar6 = param_1 + 7;
  *plVar6 = 0;
  *(undefined1 *)(param_1 + 10) = 0;
  *(undefined4 *)(param_1 + 9) = 0;
  param_1[8] = 0;
  if (param_5 != 0) {
    lVar4 = (long)(param_5 << 1) * 0x550;
    auVar3._8_8_ = 0;
    auVar3._0_8_ = (long)(param_5 << 1);
    if (SUB168(auVar3 * ZEXT816(0x550),8) != 0) {
      lVar4 = -1;
    }
    lVar4 = operator new[](unsigned long, unsigned long, bool)(lVar4,0x10,1);
    if (lVar4 != 0) {
      if (*plVar6 != 0) {
        operator delete[](void*)();
        *plVar6 = 0;
      }
      *(undefined4 *)(param_1 + 9) = 0;
      *(int *)((long)param_1 + 0x4c) = param_5;
      *(undefined4 *)((long)param_1 + 0x14) = 0;
      param_1[7] = lVar4;
      param_1[8] = lVar4 + (long)param_5 * 0x550;
      *(undefined4 *)((long)param_1 + 0x24) = 0;
      *(undefined4 *)((long)param_1 + 0x34) = 0;
      *(byte *)(param_1 + 10) = *(byte *)(param_1 + 10) ^ 1;
    }
  }
  return;
}

// ==== Aska::RenderContextServer::ReallocRenderContext(int)
// vaddr 0x21b9390 | ghidra 0x22b9390 | size 236 | symbol _ZN4Aska19RenderContextServer20ReallocRenderContextEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19RenderContextServer20ReallocRenderContextEi(long param_1,int param_2)

{
  undefined1 auVar1 [16];
  long lVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  
  uVar3 = (ulong)param_2;
  auVar1._8_8_ = 0;
  auVar1._0_8_ = uVar3;
  lVar2 = (long)param_2 * 0x230 + 0x10;
  if (SUB168(auVar1 * ZEXT816(0x230),8) != 0 || 0xffffffffffffffef < (ulong)((long)param_2 * 0x230))
  {
    lVar2 = -1;
  }
  lVar2 = operator new[](unsigned long, unsigned long, bool)(lVar2,0x10,1);
  if (lVar2 != 0) {
    *(ulong *)(lVar2 + 8) = uVar3;
    if (param_2 != 0) {
      lVar4 = uVar3 * 0x230;
      lVar5 = lVar2 + 0x10;
      do {
        Aska::RenderContext::RenderContext()(lVar5);
        lVar4 = lVar4 + -0x230;
        lVar5 = lVar5 + 0x230;
      } while (lVar4 != 0);
    }
    lVar5 = *(long *)(param_1 + 8);
    if (lVar5 != 0) {
      if (*(long *)(lVar5 + -8) != 0) {
        lVar4 = *(long *)(lVar5 + -8) * 0x230;
        do {
          Aska::RenderContext::~RenderContext()(lVar5 + lVar4 + -0x230);
          lVar4 = lVar4 + -0x230;
        } while (lVar4 != 0);
      }
      operator delete[](void*)(lVar5 + -0x10);
    }
    *(long *)(param_1 + 8) = lVar2 + 0x10;
    *(int *)(param_1 + 0x10) = param_2;
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(undefined4 *)(param_1 + 0x24) = 0;
    *(undefined4 *)(param_1 + 0x34) = 0;
    *(undefined4 *)(param_1 + 0x48) = 0;
    *(byte *)(param_1 + 0x50) = *(byte *)(param_1 + 0x50) ^ 1;
  }
  return;
}

// ==== Aska::RenderContextServer::ReallocBatch(int)
// vaddr 0x21b947c | ghidra 0x22b947c | size 244 | symbol _ZN4Aska19RenderContextServer12ReallocBatchEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19RenderContextServer12ReallocBatchEi(long param_1,int param_2)

{
  undefined1 auVar1 [16];
  long lVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  
  uVar3 = (ulong)param_2;
  auVar1._8_8_ = 0;
  auVar1._0_8_ = uVar3;
  lVar2 = (long)param_2 * 0x130 + 0x10;
  if (SUB168(auVar1 * ZEXT816(0x130),8) != 0 || 0xffffffffffffffef < (ulong)((long)param_2 * 0x130))
  {
    lVar2 = -1;
  }
  lVar2 = operator new[](unsigned long, unsigned long, bool)(lVar2,0x10,1);
  if (lVar2 != 0) {
    *(ulong *)(lVar2 + 8) = uVar3;
    if (param_2 != 0) {
      lVar4 = uVar3 * 0x130;
      lVar5 = lVar2 + 0x10;
      do {
        Aska::RenderContextBatch::RenderContextBatch()(lVar5);
        lVar4 = lVar4 + -0x130;
        lVar5 = lVar5 + 0x130;
      } while (lVar4 != 0);
    }
    lVar5 = *(long *)(param_1 + 0x18);
    if (lVar5 != 0) {
      if (*(long *)(lVar5 + -8) != 0) {
        lVar4 = *(long *)(lVar5 + -8) * 0x130;
        do {
          Aska::RenderContextBatch::~RenderContextBatch()(lVar5 + lVar4 + -0x130);
          lVar4 = lVar4 + -0x130;
        } while (lVar4 != 0);
      }
      operator delete[](void*)(lVar5 + -0x10);
      *(undefined8 *)(param_1 + 0x18) = 0;
    }
    *(int *)(param_1 + 0x20) = param_2;
    *(long *)(param_1 + 0x18) = lVar2 + 0x10;
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(undefined4 *)(param_1 + 0x24) = 0;
    *(undefined4 *)(param_1 + 0x34) = 0;
    *(undefined4 *)(param_1 + 0x48) = 0;
    *(byte *)(param_1 + 0x50) = *(byte *)(param_1 + 0x50) ^ 1;
  }
  return;
}

// ==== Aska::RenderContextServer::ReallocBatchLite(int)
// vaddr 0x21b9570 | ghidra 0x22b9570 | size 128 | symbol _ZN4Aska19RenderContextServer16ReallocBatchLiteEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19RenderContextServer16ReallocBatchLiteEi(long param_1,uint param_2)

{
  undefined1 auVar1 [16];
  long lVar2;
  ulong uVar3;
  
  if (param_2 != 0) {
    auVar1._8_8_ = 0;
    auVar1._0_8_ = (long)(int)param_2;
    uVar3 = -(ulong)(param_2 >> 0x1f) & 0xfffffffc00000000 | (ulong)param_2 << 2;
    if (SUB168(auVar1 * ZEXT816(4),8) != 0) {
      uVar3 = 0xffffffffffffffff;
    }
    lVar2 = operator new[](unsigned long, unsigned long, bool)(uVar3,0x10,1);
    if (lVar2 != 0) {
      if (*(long *)(param_1 + 0x28) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 0x28) = 0;
      }
      *(uint *)(param_1 + 0x30) = param_2;
      *(long *)(param_1 + 0x28) = lVar2;
      *(undefined4 *)(param_1 + 0x14) = 0;
      *(undefined4 *)(param_1 + 0x24) = 0;
      *(undefined4 *)(param_1 + 0x34) = 0;
      *(undefined4 *)(param_1 + 0x48) = 0;
      *(byte *)(param_1 + 0x50) = *(byte *)(param_1 + 0x50) ^ 1;
    }
  }
  return;
}

// ==== Aska::RenderContextServer::ReallocLightContext(int)
// vaddr 0x21b95f0 | ghidra 0x22b95f0 | size 136 | symbol _ZN4Aska19RenderContextServer19ReallocLightContextEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19RenderContextServer19ReallocLightContextEi(long param_1,int param_2)

{
  undefined1 auVar1 [16];
  long lVar2;
  
  if (param_2 != 0) {
    lVar2 = (long)(param_2 << 1) * 0x550;
    auVar1._8_8_ = 0;
    auVar1._0_8_ = (long)(param_2 << 1);
    if (SUB168(auVar1 * ZEXT816(0x550),8) != 0) {
      lVar2 = -1;
    }
    lVar2 = operator new[](unsigned long, unsigned long, bool)(lVar2,0x10,1);
    if (lVar2 != 0) {
      if (*(long *)(param_1 + 0x38) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 0x38) = 0;
      }
      *(undefined4 *)(param_1 + 0x48) = 0;
      *(int *)(param_1 + 0x4c) = param_2;
      *(undefined4 *)(param_1 + 0x14) = 0;
      *(long *)(param_1 + 0x38) = lVar2;
      *(long *)(param_1 + 0x40) = lVar2 + (long)param_2 * 0x550;
      *(undefined4 *)(param_1 + 0x24) = 0;
      *(undefined4 *)(param_1 + 0x34) = 0;
      *(byte *)(param_1 + 0x50) = *(byte *)(param_1 + 0x50) ^ 1;
    }
  }
  return;
}

// ==== Aska::RenderContextServer::~RenderContextServer()
// vaddr 0x21b9678 | ghidra 0x22b9678 | size 188 | symbol _ZN4Aska19RenderContextServerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19RenderContextServerD2Ev(long *param_1)

{
  long lVar1;
  long lVar2;
  
  lVar1 = param_1[1];
  *param_1 = (long)(PTR__ZTVN4Aska19RenderContextServerE_02cbe468 + 0x10);
  if (lVar1 != 0) {
    if (*(long *)(lVar1 + -8) != 0) {
      lVar2 = *(long *)(lVar1 + -8) * 0x230;
      do {
        Aska::RenderContext::~RenderContext()(lVar1 + lVar2 + -0x230);
        lVar2 = lVar2 + -0x230;
      } while (lVar2 != 0);
    }
    operator delete[](void*)(lVar1 + -0x10);
  }
  lVar1 = param_1[3];
  if (lVar1 != 0) {
    if (*(long *)(lVar1 + -8) != 0) {
      lVar2 = *(long *)(lVar1 + -8) * 0x130;
      do {
        Aska::RenderContextBatch::~RenderContextBatch()(lVar1 + lVar2 + -0x130);
        lVar2 = lVar2 + -0x130;
      } while (lVar2 != 0);
    }
    operator delete[](void*)(lVar1 + -0x10);
  }
  if (param_1[5] != 0) {
    operator delete[](void*)();
  }
  if (param_1[7] != 0) {
    operator delete[](void*)();
    param_1[7] = 0;
  }
  return;
}

// ==== Aska::RenderContextServer::~RenderContextServer()
// vaddr 0x21b9734 | ghidra 0x22b9734 | size 24 | symbol _ZN4Aska19RenderContextServerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19RenderContextServerD0Ev(undefined8 param_1)

{
  Aska::RenderContextServer::~RenderContextServer()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RenderContextServer::ResetServer()
// vaddr 0x21b974c | ghidra 0x22b974c | size 32 | symbol _ZN4Aska19RenderContextServer11ResetServerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19RenderContextServer11ResetServerEv(long param_1)

{
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(byte *)(param_1 + 0x50) = *(byte *)(param_1 + 0x50) ^ 1;
  return;
}

// ==== Aska::RenderContextServer::GetRenderContext(int)
// vaddr 0x21b976c | ghidra 0x22b976c | size 60 | symbol _ZN4Aska19RenderContextServer16GetRenderContextEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19RenderContextServer16GetRenderContextEi(long param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x14);
  param_2 = iVar1 + param_2;
  if (param_2 < *(int *)(param_1 + 0x10)) {
    *(int *)(param_1 + 0x14) = param_2;
    return *(long *)(param_1 + 8) + (long)iVar1 * 0x230;
  }
  return 0;
}

// ==== Aska::RenderContextServer::GetRenderBatch(int)
// vaddr 0x21b97a8 | ghidra 0x22b97a8 | size 56 | symbol _ZN4Aska19RenderContextServer14GetRenderBatchEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19RenderContextServer14GetRenderBatchEi(long param_1,int param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  
  puVar1 = (uint *)(param_1 + 0x24);
  do {
    uVar3 = *puVar1;
    uVar2 = uVar3 + param_2;
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(puVar1,0x10);
    if (bVar5) {
      *puVar1 = uVar2;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  if (uVar2 < *(uint *)(param_1 + 0x20)) {
    return *(long *)(param_1 + 0x18) + (ulong)uVar3 * 0x130;
  }
  return 0;
}

// ==== Aska::RenderContextServer::GetRenderBatchLite(int)
// vaddr 0x21b97e0 | ghidra 0x22b97e0 | size 52 | symbol _ZN4Aska19RenderContextServer18GetRenderBatchLiteEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19RenderContextServer18GetRenderBatchLiteEi(long param_1,int param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  
  puVar1 = (uint *)(param_1 + 0x34);
  do {
    uVar3 = *puVar1;
    uVar2 = uVar3 + param_2;
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(puVar1,0x10);
    if (bVar5) {
      *puVar1 = uVar2;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  if (uVar2 < *(uint *)(param_1 + 0x30)) {
    return *(long *)(param_1 + 0x28) + (ulong)uVar3 * 4;
  }
  return 0;
}

// ==== Aska::RenderContextServer::GetLightContext(int)
// vaddr 0x21b9814 | ghidra 0x22b9814 | size 68 | symbol _ZN4Aska19RenderContextServer15GetLightContextEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19RenderContextServer15GetLightContextEi(long param_1,int param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  
  puVar1 = (uint *)(param_1 + 0x48);
  do {
    uVar3 = *puVar1;
    uVar2 = uVar3 + param_2;
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(puVar1,0x10);
    if (bVar5) {
      *puVar1 = uVar2;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  if (uVar2 < *(uint *)(param_1 + 0x4c)) {
    return *(long *)(param_1 + (ulong)*(byte *)(param_1 + 0x50) * 8 + 0x38) + (ulong)uVar3 * 0x550;
  }
  return 0;
}

// ==== Aska::RenderThread::RenderThread()
// vaddr 0x21c1344 | ghidra 0x22c1344 | size 1100 | symbol _ZN4Aska12RenderThreadC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThreadC1Ev(long *param_1)

{
  uint uVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  ulong uVar6;
  undefined4 uVar7;
  long lVar8;
  long alStack_50 [2];
  
  Aska::Thread::Thread()();
  *param_1 = (long)(PTR__ZTVN4Aska12RenderThreadE_02cc4f70 + 0x10);
  Aska::Event::Event()(param_1 + 3);
  Aska::Event::Event()(param_1 + 0x10);
  Aska::CriticalSection::CriticalSection()(param_1 + 0x1d);
  Aska::Event::Event()(param_1 + 0x22);
  param_1[0x33] = (long)(PTR__ZTVN4Aska6TQueueINS_14RENDER_REQUESTELi8192EEE_02cb80d0 + 0x10);
  *(undefined4 *)(param_1 + 0x34) = 1;
  *(undefined4 *)((long)param_1 + 0x1a4) = 0;
  *(undefined1 *)((long)param_1 + 0x501d1) = 0;
  *(undefined2 *)((long)param_1 + 0x501d3) = 1;
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0xa03e);
  *(undefined1 *)(param_1 + 0xa03a) = 0;
  *(undefined1 *)((long)param_1 + 0x501d2) = 0;
  *(undefined1 *)((long)param_1 + 0x501d5) = 0;
  plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x2040,PTR__ZSt7nothrow_02cb9a80);
  if (plVar2 != (long *)0x0) {
    Aska::Thread::Thread()(plVar2);
    *plVar2 = (long)(PTR__ZTVN4Aska26RenderFinishCallbackThreadE_02cb76f0 + 0x10);
    Aska::Semaphore::Semaphore()(plVar2 + 3);
    *(undefined1 *)((long)plVar2 + 0x3d) = 0;
    Aska::Semaphore::Create(int, int)(plVar2 + 3,0,0x10000);
    Aska::Thread::Create(bool, int, int, bool)(plVar2,0,0xa0,0x3000,1);
    *(undefined4 *)(plVar2 + 6) = 0;
    *(undefined4 *)((long)plVar2 + 0x34) = 0;
    *(undefined4 *)(plVar2 + 7) = 0;
    *(undefined1 *)((long)plVar2 + 0x3c) = 0;
    memset(plVar2 + 8,0,0x2000);
  }
  param_1[0xa03b] = (long)plVar2;
  plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x3088,PTR__ZSt7nothrow_02cb9a80);
  if (plVar2 != (long *)0x0) {
    Aska::Thread::Thread()(plVar2);
    *plVar2 = (long)(PTR__ZTVN4Aska26RenderThreadCallBackThreadE_02cb6b80 + 0x10);
    *(undefined2 *)(plVar2 + 0x603) = 0;
    *(undefined2 *)((long)plVar2 + 0x301a) = 0;
    *(undefined2 *)((long)plVar2 + 0x301c) = 0;
    Aska::Event::Event()(plVar2 + 0x604);
    *(undefined1 *)((long)plVar2 + 0x301e) = 0;
    Aska::Event::Create(bool, bool)(plVar2 + 0x604,0,0);
    Aska::Thread::Create(bool, int, int, bool)(plVar2,0,0xff,0x4000,1);
  }
  param_1[0xa03c] = (long)plVar2;
  Aska::Event::Create(bool, bool)(param_1 + 3,0,0);
  Aska::Event::Create(bool, bool)(param_1 + 0x10,0,0);
  param_1[0x2f] = 0;
  Aska::Event::Create(bool, bool)(param_1 + 0x22,0,0);
  *(undefined1 *)((long)param_1 + 0x192) = 0;
  plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xd8,PTR__ZSt7nothrow_02cb9a80);
  uVar7 = 0x980013;
  if (plVar2 != (long *)0x0) {
    Aska::NotifierThread::NotifierThread(int)(plVar2,8);
    *plVar2 = (long)(PTR__ZTVN4Aska7GPUSyncE_02cc05c8 + 0x10);
    Aska::Semaphore::Semaphore()(plVar2 + 0x18);
    *(undefined1 *)(plVar2 + 0x17) = 0;
    Aska::Semaphore::Create(int, int)(plVar2 + 0x18,1,1);
  }
  *(long **)PTR__ZN4Aska12RenderThread10m_pGPUSyncE_02cbe328 = plVar2;
  Aska::NotifierThread::Init()(plVar2);
  lVar8 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
  lVar4 = lVar8 + 0xb0;
  Aska::CriticalSection::Enter() const(lVar4);
  Aska::TextureManager::AllocTextureEx(unsigned long, int, int, int, int, int, void*, int, Aska::AFF::AifImage const**, bool)(alStack_50,lVar8,0x7274406400000000,1,1,
                  "lPoint_Normal_Step_U24ELb1ELb1ELj3EEEED0Ev",0,1,0,1,0,1);
  Aska::CriticalSection::Leave() const(lVar4);
  if (alStack_50[0] == 0) {
    Aska::CriticalSection::Enter() const(lVar4);
    uVar7 = 0x980093;
    Aska::TextureManager::AllocTextureEx(unsigned long, int, int, int, int, int, void*, int, Aska::AFF::AifImage const**, bool)(alStack_50,lVar8,0x7274406400000000,1,1,"l_Linear_U24ELb1ELb0ELj0EEEED0Ev",0,1,0
                    ,1,0,1);
    Aska::CriticalSection::Leave() const(lVar4);
  }
  Aska::CriticalSection::Enter() const(lVar4);
  lVar3 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar8,0x7274406400000000,1);
  Aska::CriticalSection::Leave() const(lVar4);
  param_1[0xa03d] = lVar3;
  lVar4 = Aska::Texture::GetBody() const(lVar3);
  uVar5 = Aska::IPixelFormatGL::GetNativeFormat(Aska::APXFORMAT)(uVar7);
  uVar6 = Aska::PixelFormatBase::CalcNativeMipLvOffset(unsigned long, int, int, int, int, int, int, int, int)(uVar5,0x20,1,1,1,0,0,0,0xffffffff);
  uVar1 = Aska::TextureManager::CalcTextureBodySize(int, int, Aska::APXFORMAT, int, int, int)(lVar8,*(undefined2 *)(param_1[0xa03d] + 0x18),
                          *(undefined2 *)(param_1[0xa03d] + 0x1a),uVar7,0,1,1);
  if (3 < uVar1) {
    memset(lVar4 + (uVar6 & 0xffffffff),0,uVar1 & 0xfffffffc);
  }
  Aska::TextureManager::MarkTextureForUpdate(unsigned long)(lVar8,0x7274406400000000);
  *(undefined2 *)(param_1 + 0x32) = 0;
  param_1[0xa051] = 0;
  param_1[0xa050] = 0;
  Aska::Thread::Create(bool, int, int, bool)(param_1,0,0xa0,0x40000,1);
  return;
}

// ==== Aska::RenderThread::~RenderThread()
// vaddr 0x21c1790 | ghidra 0x22c1790 | size 244 | symbol _ZN4Aska12RenderThreadD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThreadD2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska12RenderThreadE_02cc4f70 + 0x10);
  Aska::Thread::WaitEnd()();
  plVar2 = (long *)param_1[0xa03b];
  if (plVar2 != (long *)0x0) {
    (**(code **)(*plVar2 + 8))();
    param_1[0xa03b] = 0;
  }
  plVar2 = (long *)param_1[0xa03c];
  if (plVar2 != (long *)0x0) {
    (**(code **)(*plVar2 + 8))();
    param_1[0xa03c] = 0;
  }
  puVar1 = PTR__ZN4Aska12RenderThread10m_pGPUSyncE_02cbe328;
  if (*(long **)PTR__ZN4Aska12RenderThread10m_pGPUSyncE_02cbe328 != (long *)0x0) {
    (**(code **)(**(long **)PTR__ZN4Aska12RenderThread10m_pGPUSyncE_02cbe328 + 8))();
    *(undefined8 *)puVar1 = 0;
  }
  Aska::Event::Exit()(param_1 + 3);
  Aska::Event::Exit()(param_1 + 0x10);
  Aska::Event::Exit()(param_1 + 0x22);
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0xa03e);
  Aska::Event::Exit()(param_1 + 0x22);
  Aska::CriticalSection::~CriticalSection()(param_1 + 0x1d);
  Aska::Event::Exit()(param_1 + 0x10);
  Aska::Event::Exit()(param_1 + 3);
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)(param_1);
  return;
}

// ==== Aska::RenderThread::~RenderThread()
// vaddr 0x21c1888 | ghidra 0x22c1888 | size 24 | symbol _ZN4Aska12RenderThreadD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThreadD0Ev(undefined8 param_1)

{
  Aska::RenderThread::~RenderThread()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RenderThread::GetStatus() const
// vaddr 0x21c18a0 | ghidra 0x22c18a0 | size 372 | symbol _ZNK4Aska12RenderThread9GetStatusEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK4Aska12RenderThread9GetStatusEv(long param_1)

{
  int *piVar1;
  undefined1 uVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  int *piVar7;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar6 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar6;
      iVar6 = iVar6 + 1;
      if (bVar4) {
        piVar7 = (int *)(param_1 + 0x5022c);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
          if (bVar4) {
            *piVar7 = *piVar7 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        do {
          if (*piVar1 != -1) {
            ClearExclusiveLocal();
            do {
              uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
              if ((uVar5 & 1) == 0) {
                do {
                  cVar3 = '\x01';
                  bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
                  if (bVar4) {
                    *piVar7 = *piVar7 + -1;
                    cVar3 = ExclusiveMonitorsStatus();
                  }
                } while (cVar3 != '\0');
                Aska::Thread::Sleep(unsigned int)(1);
              }
              else {
                Aska::Semaphore::Wait() const(param_1 + 0x50268);
              }
              do {
                cVar3 = '\x01';
                bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
                if (bVar4) {
                  *piVar7 = *piVar7 + 1;
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
                if (cVar3 == '\0') goto code_r0x022c19fc;
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
code_r0x022c19fc:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
          if (bVar4) {
            *piVar7 = *piVar7 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x022c192c:
        piVar7 = (int *)(param_1 + 0x5022c);
        uVar2 = *(undefined1 *)(param_1 + 0x192);
        DataMemoryBarrier(2,3);
        *piVar1 = -1;
        DataMemoryBarrier(2,3);
        if (0x14 < *piVar7) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
            if (bVar4) {
              *piVar7 = *piVar7 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
          if ((uVar5 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0x50268);
          }
        }
        return uVar2;
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
  goto code_r0x022c192c;
}

// ==== Aska::RenderThread::DeviceReset()
// vaddr 0x21c1a14 | ghidra 0x22c1a14 | size 120 | symbol _ZN4Aska12RenderThread11DeviceResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread11DeviceResetEv(long param_1)

{
  char *pcVar1;
  
  pcVar1 = (char *)(param_1 + 0x501d3);
  if (*pcVar1 != '\0') {
    Aska::RenderDeviceGL::SetCurrentContext_RenderThread()(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
  }
  Aska::FrameBuffer::ResetBuffers()(*(undefined8 *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198);
  *(undefined1 *)(param_1 + 0x501d1) = 0;
  if (*pcVar1 != '\0') {
    Aska::VSync::Initialize()(*(undefined8 *)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460);
    *pcVar1 = '\0';
  }
  (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(param_1 + 0x80);
  return;
}

// ==== Aska::RenderThread::WaitForInit()
// vaddr 0x21c1a8c | ghidra 0x22c1a8c | size 4 | symbol _ZN4Aska12RenderThread11WaitForInitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread11WaitForInitEv(void)

{
  return;
}

// ==== Aska::RenderThread::Handler_Init()
// vaddr 0x21c1a90 | ghidra 0x22c1a90 | size 20 | symbol _ZN4Aska12RenderThread12Handler_InitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread12Handler_InitEv(long param_1)

{
  *(undefined1 *)(param_1 + 0x501d0) = 1;
  return;
}

// ==== Aska::RenderThread::Handler()
// vaddr 0x21c1aa4 | ghidra 0x22c1aa4 | size 764 | symbol _ZN4Aska12RenderThread7HandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread7HandlerEv(long param_1)

{
  long lVar1;
  int *piVar2;
  int *piVar3;
  long lVar4;
  bool bVar5;
  undefined *puVar6;
  undefined *puVar7;
  char cVar8;
  ulong uVar9;
  int iVar10;
  long lVar11;
  undefined1 auStack_68 [4];
  undefined4 uStack_64;
  
  puVar6 = PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  *(undefined1 *)(param_1 + 0x501d0) = 1;
  puVar7 = PTR__ZN4Aska6Global22m_pRenderTargetManagerE_02cbfa00;
  piVar2 = (int *)(param_1 + 0x50228);
  piVar3 = (int *)(param_1 + 0x5022c);
  lVar4 = param_1 + 0x50268;
  uStack_64 = 0;
  auStack_68[0] = 1;
code_r0x022c1b4c:
  while( true ) {
    cVar8 = Aska::RenderThread::GetStatus() const(param_1);
    if (cVar8 != '\x02') break;
    Aska::RenderThread::Render(int&, bool&)(param_1,&uStack_64,auStack_68);
  }
  if (cVar8 != '\x01') goto code_r0x022c1b68;
  goto code_r0x022c1c24;
code_r0x022c1b68:
  if (cVar8 != '\0') goto code_r0x022c1b4c;
  while( true ) {
    if (*(long *)(param_1 + 0x178) != 0) {
      (**(code **)(param_1 + 0x178))
                (*(undefined8 *)(param_1 + 0x180),*(undefined8 *)(param_1 + 0x188));
      *(undefined8 *)(param_1 + 0x178) = 0;
      Aska::Event::Set() const(param_1 + 0x110);
    }
    if (*(char *)(param_1 + 0x501d4) != '\0') {
      if (*(long *)(param_1 + 0x501e8) != 0) {
        lVar11 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
        lVar1 = lVar11 + 0xb0;
        Aska::CriticalSection::Enter() const(lVar1);
        Aska::TextureManager::DeleteTextureImmediatelyEx(unsigned long)(lVar11,0x7274406400000000);
        Aska::CriticalSection::Leave() const(lVar1);
        *(long *)(param_1 + 0x501e8) = 0;
      }
      Aska::VSync::Exit()(*(undefined8 *)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460);
      Aska::RenderManagerBase::DecideDeleteGpuResources()(*(undefined8 *)puVar6);
      uVar9 = Aska::RenderDeviceGL::BeginRender()(*(undefined8 *)puVar6);
      if ((uVar9 & 1) != 0) {
        Aska::RenderDeviceGL::EndRender()(*(undefined8 *)puVar6);
      }
      Aska::RenderTargetManagerGL::ReleaseID(unsigned int)(*(undefined8 *)puVar7,0xc1);
      Aska::RenderDeviceGL::SetCurrentContext_None()(*(undefined8 *)puVar6);
      Aska::Thread::Exit()();
    }
    if (*(char *)(param_1 + 0x501d2) == '\0') break;
    *(char *)(param_1 + 0x501d2) = '\0';
  }
code_r0x022c1c24:
  iVar10 = 0;
  do {
    while (*piVar2 != -1) {
      ClearExclusiveLocal();
      bVar5 = 0x1fe < iVar10;
      iVar10 = iVar10 + 1;
      if (bVar5) goto code_r0x022c1c50;
    }
    cVar8 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = 0;
      cVar8 = ExclusiveMonitorsStatus();
    }
  } while (cVar8 != '\0');
code_r0x022c1cf4:
  DataMemoryBarrier(2,3);
  if (*(short *)(param_1 + 400) == 0) {
    DataMemoryBarrier(2,3);
    *piVar2 = -1;
    DataMemoryBarrier(2,3);
    if (0x14 < *piVar3) {
      do {
        cVar8 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar3,0x10);
        if (bVar5) {
          *piVar3 = *piVar3 + -1;
          cVar8 = ExclusiveMonitorsStatus();
        }
      } while (cVar8 != '\0');
      uVar9 = Aska::Semaphore::IsReady() const(lVar4);
      if ((uVar9 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar4);
      }
    }
    Aska::Event::Wait(unsigned int) const(param_1 + 0x18,0);
  }
  else {
    *(undefined1 *)(param_1 + 0x192) = 2;
    DataMemoryBarrier(2,3);
    *piVar2 = -1;
    DataMemoryBarrier(2,3);
    if (0x14 < *piVar3) {
      do {
        cVar8 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar3,0x10);
        if (bVar5) {
          *piVar3 = *piVar3 + -1;
          cVar8 = ExclusiveMonitorsStatus();
        }
      } while (cVar8 != '\0');
      uVar9 = Aska::Semaphore::IsReady() const(lVar4);
      if ((uVar9 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar4);
        uStack_64 = 0;
        goto code_r0x022c1b4c;
      }
    }
  }
  uStack_64 = 0;
  goto code_r0x022c1b4c;
code_r0x022c1c50:
  do {
    cVar8 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar3,0x10);
    if (bVar5) {
      *piVar3 = *piVar3 + 1;
      cVar8 = ExclusiveMonitorsStatus();
    }
  } while (cVar8 != '\0');
  do {
    if (*piVar2 != -1) {
      do {
        ClearExclusiveLocal();
        uVar9 = Aska::Semaphore::IsReady() const(lVar4);
        if ((uVar9 & 1) == 0) {
          do {
            cVar8 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar3,0x10);
            if (bVar5) {
              *piVar3 = *piVar3 + -1;
              cVar8 = ExclusiveMonitorsStatus();
            }
          } while (cVar8 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(lVar4);
        }
        do {
          cVar8 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar3,0x10);
          if (bVar5) {
            *piVar3 = *piVar3 + 1;
            cVar8 = ExclusiveMonitorsStatus();
          }
        } while (cVar8 != '\0');
        while (*piVar2 == -1) {
          cVar8 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = 0;
            cVar8 = ExclusiveMonitorsStatus();
          }
          if (cVar8 == '\0') goto code_r0x022c1ce4;
        }
      } while( true );
    }
    cVar8 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = 0;
      cVar8 = ExclusiveMonitorsStatus();
    }
  } while (cVar8 != '\0');
code_r0x022c1ce4:
  do {
    cVar8 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar3,0x10);
    if (bVar5) {
      *piVar3 = *piVar3 + -1;
      cVar8 = ExclusiveMonitorsStatus();
    }
  } while (cVar8 != '\0');
  goto code_r0x022c1cf4;
}

// ==== Aska::RenderThread::BlockCallFunc()
// vaddr 0x21c1da0 | ghidra 0x22c1da0 | size 52 | symbol _ZN4Aska12RenderThread13BlockCallFuncEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread13BlockCallFuncEv(long param_1)

{
  if (*(long *)(param_1 + 0x178) != 0) {
    (**(code **)(param_1 + 0x178))
              (*(undefined8 *)(param_1 + 0x180),*(undefined8 *)(param_1 + 0x188));
    *(undefined8 *)(param_1 + 0x178) = 0;
    (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(param_1 + 0x110);
    return;
  }
  return;
}

// ==== Aska::RenderThread::Render(int&, bool&)
// vaddr 0x21c1dd4 | ghidra 0x22c1dd4 | size 1976 | symbol _ZN4Aska12RenderThread6RenderERiRb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x022c2404: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022c23c8: Changing call to branch */
/* WARNING: Possible PIC construction at 0x022c1fe4: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x022c23cc) */
/* WARNING: Removing unreachable block (ram,0x022c2408) */
/* WARNING: Removing unreachable block (ram,0x022c2410) */
/* WARNING: Removing unreachable block (ram,0x022c2424) */
/* WARNING: Removing unreachable block (ram,0x022c2428) */
/* WARNING: Removing unreachable block (ram,0x022c2440) */
/* WARNING: Removing unreachable block (ram,0x022c2450) */
/* WARNING: Removing unreachable block (ram,0x022c2458) */
/* WARNING: Removing unreachable block (ram,0x022c2460) */
/* WARNING: Removing unreachable block (ram,0x022c2478) */
/* WARNING: Removing unreachable block (ram,0x022c2494) */
/* WARNING: Removing unreachable block (ram,0x022c249c) */
/* WARNING: Removing unreachable block (ram,0x022c24a4) */
/* WARNING: Removing unreachable block (ram,0x022c2488) */
/* WARNING: Removing unreachable block (ram,0x022c24ac) */
/* WARNING: Removing unreachable block (ram,0x022c24b4) */
/* WARNING: Removing unreachable block (ram,0x022c24bc) */
/* WARNING: Removing unreachable block (ram,0x022c24c8) */
/* WARNING: Removing unreachable block (ram,0x022c246c) */
/* WARNING: Removing unreachable block (ram,0x022c2474) */
/* WARNING: Removing unreachable block (ram,0x022c24d0) */
/* WARNING: Removing unreachable block (ram,0x022c24d8) */
/* WARNING: Removing unreachable block (ram,0x022c2434) */
/* WARNING: Removing unreachable block (ram,0x022c243c) */
/* WARNING: Removing unreachable block (ram,0x022c24e0) */
/* WARNING: Removing unreachable block (ram,0x022c2524) */
/* WARNING: Removing unreachable block (ram,0x022c252c) */
/* WARNING: Removing unreachable block (ram,0x022c2534) */
/* WARNING: Removing unreachable block (ram,0x022c2540) */
/* WARNING: Removing unreachable block (ram,0x022c1fe8) */

void _ZN4Aska12RenderThread6RenderERiRb(long param_1,int *param_2,byte *param_3)

{
  float *pfVar1;
  long *plVar2;
  char *pcVar3;
  char *pcVar4;
  int *piVar5;
  int *piVar6;
  float fVar7;
  float fVar8;
  undefined4 uVar9;
  char cVar10;
  bool bVar11;
  long *plVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  long *plVar15;
  undefined *puVar16;
  byte bVar17;
  ulong uVar18;
  int iVar19;
  undefined8 uVar20;
  long lVar21;
  long lVar22;
  long lVar23;
  
  uVar18 = Aska::LifeCycleManager::SurfaceControl()();
  if ((uVar18 & 1) != 0) {
    return;
  }
  uVar20 = *(undefined8 *)PTR__ZN4Aska6Global22m_pRenderTargetManagerE_02cbfa00;
  plVar2 = (long *)(param_1 + 0x501d8);
  lVar21 = param_1 + 0x50268;
  pcVar3 = (char *)(param_1 + 0x501d3);
  pcVar4 = (char *)(param_1 + 0x501d1);
  piVar5 = (int *)(param_1 + 0x50228);
  piVar6 = (int *)(param_1 + 0x5022c);
code_r0x022c1ef0:
  do {
    if (*(long *)(param_1 + 0x178) != 0) {
      (**(code **)(param_1 + 0x178))
                (*(undefined8 *)(param_1 + 0x180),*(undefined8 *)(param_1 + 0x188));
      *(undefined8 *)(param_1 + 0x178) = 0;
      Aska::Event::Set() const(param_1 + 0x110);
    }
    DataMemoryBarrier(2,3);
    iVar19 = 0;
    if (*(int *)(param_1 + 0x1a4) + 1 < 0x2001) {
      iVar19 = *(int *)(param_1 + 0x1a4) + 1;
    }
    lVar22 = param_1 + (long)iVar19 * 0x28;
    if (iVar19 == *(int *)(param_1 + 0x1a0)) {
      return;
    }
    cVar10 = *(char *)(lVar22 + 0x1a8);
    pfVar1 = (float *)(lVar22 + 0x1b0);
    fVar7 = *pfVar1;
    plVar15 = *(long **)pfVar1;
    uVar14 = *(undefined8 *)pfVar1;
    plVar12 = *(long **)pfVar1;
    pfVar1 = (float *)(lVar22 + 0x1b8);
    fVar8 = *pfVar1;
    uVar9 = *(undefined4 *)(lVar22 + 0x1bc);
    lVar23 = *(long *)pfVar1;
    uVar13 = *(undefined8 *)pfVar1;
    uVar18 = *(ulong *)(lVar22 + 0x1c0);
    iVar19 = 0;
    if (*(int *)(param_1 + 0x1a4) + 1 < 0x2001) {
      iVar19 = *(int *)(param_1 + 0x1a4) + 1;
    }
    *(int *)(param_1 + 0x1a4) = iVar19;
    if (*param_3 != 0) goto code_r0x022c1f70;
    if (cVar10 == '\x01') goto code_r0x022c2008;
    if (cVar10 == '\n') goto code_r0x022c203c;
  } while (cVar10 != '\x06');
  goto code_r0x022c23e0;
code_r0x022c1f70:
  switch(cVar10) {
  case '\0':
    (**(code **)(*plVar12 + 0x288))(plVar12,uVar13,uVar18 & 0xffffffff);
    if ((*(byte *)((long)plVar12 + 0x19a) >> 3 & 1) != 0) {
      plVar15 = plVar12 + 0x35;
      do {
        iVar19 = (int)*plVar15 + -1;
        cVar10 = '\x01';
        bVar11 = (bool)ExclusiveMonitorPass(plVar15,0x10);
        if (bVar11) {
          *(int *)plVar15 = iVar19;
          cVar10 = ExclusiveMonitorsStatus();
        }
      } while (cVar10 != '\0');
      if (iVar19 == 0) {
        lVar21 = *plVar2;
        iVar19 = *(int *)(lVar21 + 0x34);
        *(int *)(lVar21 + 0x34) = iVar19 + 1;
        *(long **)(lVar21 + (long)iVar19 * 8 + 0x40) = plVar12;
        DataMemoryBarrier(2,3);
        lVar21 = *plVar2 + 0x18;
        goto code_r0x011bd9c0;
      }
    }
    break;
  case '\x01':
code_r0x022c2008:
    bVar17 = Aska::RenderDeviceGL::BeginRender()(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
    *param_3 = bVar17 & 1;
    if ((bVar17 & 1) != 0) {
      *(undefined1 *)(*(long *)PTR__ZN4Aska12RenderThread10m_pGPUSyncE_02cbe328 + 0xb8) = 1;
    }
    goto code_r0x022c1ef0;
  case '\x02':
    Aska::RenderTargetManagerGL::ChangeTarget(unsigned int, int)(uVar20,fVar7,0);
    if (*(int *)(lVar23 + 0x10) == 0) goto code_r0x022c1ef0;
    Aska::RenderTargetManagerGL::ClearCurrentTarget(unsigned int, int, float, int)(*(undefined4 *)(lVar23 + 0x18),uVar20,*(undefined4 *)(lVar23 + 0x14),
                    *(int *)(lVar23 + 0x10),*(undefined4 *)(lVar23 + 0x1c));
    break;
  case '\x03':
    Aska::RenderTargetManagerGL::Resolve(int, bool, int)(uVar20,fVar8,0,uVar18 & 0xffffffff);
    goto code_r0x022c1ef0;
  case '\x04':
    lVar22 = (**(code **)(*plVar15 + 0x290))(plVar15,fVar8,uVar18 & 0xffffffff);
    if (lVar22 != 0) {
      Aska::RenderTargetManagerGL::TemporaryResolve(Aska::Texture*, bool, int, int, int, int, int)(uVar20,lVar22,0,1,0,0,0,0);
    }
  default:
    goto code_r0x022c1ef0;
  case '\x06':
    goto code_r0x022c23d0;
  case '\a':
    lVar23 = *(long *)(param_1 + 0x501e0);
    *(undefined8 *)(lVar23 + (ulong)*(ushort *)(lVar23 + 0x301c) * 8 + 0x18) = uVar14;
    lVar22 = lVar23 + (ulong)*(ushort *)(lVar23 + 0x301c) * 8;
    *(float *)(lVar22 + 0x1018) = fVar8;
    *(undefined4 *)(lVar22 + 0x101c) = uVar9;
    *(ulong *)(lVar23 + (ulong)*(ushort *)(lVar23 + 0x301c) * 8 + 0x2018) = uVar18;
    *(ushort *)(lVar23 + 0x301c) = *(short *)(lVar23 + 0x301c) + 1U & 0x1ff;
    lVar22 = *(long *)(param_1 + 0x501e0);
    *(ushort *)(lVar22 + 0x301a) = *(short *)(lVar22 + 0x301a) + 1U & 0x1ff;
    Aska::Event::Set() const(lVar22 + 0x3020);
    goto code_r0x022c1ef0;
  case '\n':
code_r0x022c203c:
    if (*pcVar4 != '\0') {
      if (*pcVar3 != '\0') {
        Aska::RenderDeviceGL::SetCurrentContext_RenderThread()(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
      }
      Aska::FrameBuffer::ResetBuffers()(*(undefined8 *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198);
      *pcVar4 = '\0';
      if (*pcVar3 != '\0') {
        Aska::VSync::Initialize()(*(undefined8 *)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460);
        *pcVar3 = '\0';
      }
      Aska::Event::Set() const(param_1 + 0x80);
    }
    Aska::FrameBuffer::Swap()(*(undefined8 *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198);
    lVar22 = *plVar2;
    while (*(int *)(lVar22 + 0x30) < *(int *)(lVar22 + 0x34)) {
      Aska::Thread::Switch()();
    }
    *(undefined4 *)(lVar22 + 0x30) = 0;
    *(undefined4 *)(lVar22 + 0x34) = 0;
    *(undefined4 *)(lVar22 + 0x38) = 0;
    iVar19 = 0;
    do {
      while (*piVar5 == -1) {
        cVar10 = '\x01';
        bVar11 = (bool)ExclusiveMonitorPass(piVar5,0x10);
        if (bVar11) {
          *piVar5 = 0;
          cVar10 = ExclusiveMonitorsStatus();
        }
        if (cVar10 == '\0') goto code_r0x022c2384;
      }
      ClearExclusiveLocal();
      bVar11 = iVar19 < 0x1ff;
      iVar19 = iVar19 + 1;
    } while (bVar11);
    do {
      cVar10 = '\x01';
      bVar11 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar11) {
        *piVar6 = *piVar6 + 1;
        cVar10 = ExclusiveMonitorsStatus();
      }
    } while (cVar10 != '\0');
    do {
      if (*piVar5 != -1) {
        do {
          ClearExclusiveLocal();
          uVar18 = Aska::Semaphore::IsReady() const(lVar21);
          if ((uVar18 & 1) == 0) {
            do {
              cVar10 = '\x01';
              bVar11 = (bool)ExclusiveMonitorPass(piVar6,0x10);
              if (bVar11) {
                *piVar6 = *piVar6 + -1;
                cVar10 = ExclusiveMonitorsStatus();
              }
            } while (cVar10 != '\0');
            Aska::Thread::Sleep(unsigned int)(1);
          }
          else {
            Aska::Semaphore::Wait() const(lVar21);
          }
          do {
            cVar10 = '\x01';
            bVar11 = (bool)ExclusiveMonitorPass(piVar6,0x10);
            if (bVar11) {
              *piVar6 = *piVar6 + 1;
              cVar10 = ExclusiveMonitorsStatus();
            }
          } while (cVar10 != '\0');
          while (*piVar5 == -1) {
            cVar10 = '\x01';
            bVar11 = (bool)ExclusiveMonitorPass(piVar5,0x10);
            if (bVar11) {
              *piVar5 = 0;
              cVar10 = ExclusiveMonitorsStatus();
            }
            if (cVar10 == '\0') goto code_r0x022c2374;
          }
        } while( true );
      }
      cVar10 = '\x01';
      bVar11 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar11) {
        *piVar5 = 0;
        cVar10 = ExclusiveMonitorsStatus();
      }
    } while (cVar10 != '\0');
code_r0x022c2374:
    do {
      cVar10 = '\x01';
      bVar11 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar11) {
        *piVar6 = *piVar6 + -1;
        cVar10 = ExclusiveMonitorsStatus();
      }
    } while (cVar10 != '\0');
code_r0x022c2384:
    DataMemoryBarrier(2,3);
    *(undefined1 *)(param_1 + 0x192) = 0;
    DataMemoryBarrier(2,3);
    *piVar5 = -1;
    DataMemoryBarrier(2,3);
    if (0x14 < *piVar6) {
      do {
        cVar10 = '\x01';
        bVar11 = (bool)ExclusiveMonitorPass(piVar6,0x10);
        if (bVar11) {
          *piVar6 = *piVar6 + -1;
          cVar10 = ExclusiveMonitorsStatus();
        }
      } while (cVar10 != '\0');
      uVar18 = Aska::Semaphore::IsReady() const(lVar21);
      if ((uVar18 & 1) != 0) goto code_r0x011bd9c0;
    }
    puVar16 = PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8;
    Aska::PerformanceCounter::Mark(int)(*(undefined8 *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8,1);
    Aska::PerformanceCounter::Mark(int)(*(undefined8 *)puVar16,2);
    goto code_r0x022c1ef0;
  case '\x10':
    *(float *)(param_1 + 0x50290) = fVar7;
    *(float *)(param_1 + 0x50294) = fVar8;
    puVar16 = PTR__ZN4Aska20GlobalShaderConstant15m_vHDRTransformE_02cb9e40;
    *(float *)(PTR__ZN4Aska20GlobalShaderConstant15m_vHDRTransformE_02cb9e40 + 4) = fVar7;
    *(undefined8 *)(puVar16 + 8) = 0x3f80000000000000;
    *(float *)puVar16 = 1.0 / fVar7;
    *(float *)(puVar16 + 0x10) = 1.0 / fVar7;
    *(float *)(puVar16 + 0x14) = fVar7 * fVar8;
    *(undefined8 *)(puVar16 + 0x18) = 0x3f80000000000000;
    goto code_r0x022c1ef0;
  case '\x11':
    *(bool *)(param_1 + 0x501d5) = fVar7 != 0.0;
    Aska::RenderState::Static::EnableColorWrite(Aska::RenderDeviceGL*, bool)(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,fVar7 == 0.0);
    goto code_r0x022c1ef0;
  case '\x13':
    if (*pcVar4 != '\0') {
      if (*pcVar3 != '\0') {
        Aska::RenderDeviceGL::SetCurrentContext_RenderThread()(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
      }
      Aska::FrameBuffer::ResetBuffers()(*(undefined8 *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198);
      *pcVar4 = '\0';
      if (*pcVar3 != '\0') {
        Aska::VSync::Initialize()(*(undefined8 *)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460);
        *pcVar3 = '\0';
      }
      Aska::Event::Set() const(param_1 + 0x80);
      Aska::FrameBuffer::Swap()(*(undefined8 *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198);
    }
    goto code_r0x022c1ef0;
  }
  *param_2 = *param_2 + 1;
  goto code_r0x022c1ef0;
code_r0x022c23d0:
  Aska::RenderDeviceGL::EndRender()(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0);
code_r0x022c23e0:
  Aska::RenderDeviceGL::FlushPendingCommands(Aska::RenderDeviceGL::Blocking)(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,0);
  lVar21 = *(long *)PTR__ZN4Aska12RenderThread10m_pGPUSyncE_02cbe328 + 0x58;
code_r0x011bd9c0:
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(lVar21);
  return;
}

// ==== Aska::RenderThread::InsertCallBack(Aska::RenderThread::CALLBACK_ID, unsigned long)
// vaddr 0x21c25a4 | ghidra 0x22c25a4 | size 136 | symbol _ZN4Aska12RenderThread14InsertCallBackENS0_11CALLBACK_IDEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread14InsertCallBackENS0_11CALLBACK_IDEm(int param_1,long param_2)

{
  long lVar1;
  
  if (param_1 == 2) {
    lVar1 = *(long *)(param_2 + 0x501e0);
    *(ushort *)(lVar1 + 0x301a) = *(short *)(lVar1 + 0x301a) + 1U & 0x1ff;
    (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(lVar1 + 0x3020);
    return;
  }
  if (param_1 == 1) {
    lVar1 = *(long *)(param_2 + 0x501d8) + 0x18;
  }
  else {
    if (param_1 != 0) {
      return;
    }
    Aska::RenderDeviceGL::FlushPendingCommands(Aska::RenderDeviceGL::Blocking)(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,0);
    lVar1 = *(long *)PTR__ZN4Aska12RenderThread10m_pGPUSyncE_02cbe328 + 0x58;
  }
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(lVar1);
  return;
}

// ==== Aska::RenderThread::SetExposureScale(float, float)
// vaddr 0x21c262c | ghidra 0x22c262c | size 68 | symbol _ZN4Aska12RenderThread16SetExposureScaleEff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread16SetExposureScaleEff(float param_1,float param_2,long param_3)

{
  undefined *puVar1;
  
  *(float *)(param_3 + 0x50290) = param_1;
  *(float *)(param_3 + 0x50294) = param_2;
  puVar1 = PTR__ZN4Aska20GlobalShaderConstant15m_vHDRTransformE_02cb9e40;
  *(undefined8 *)(PTR__ZN4Aska20GlobalShaderConstant15m_vHDRTransformE_02cb9e40 + 8) =
       0x3f80000000000000;
  *(float *)puVar1 = 1.0 / param_1;
  *(float *)(puVar1 + 4) = param_1;
  *(float *)(puVar1 + 0x10) = 1.0 / param_1;
  *(float *)(puVar1 + 0x14) = param_1 * param_2;
  *(undefined8 *)(puVar1 + 0x18) = 0x3f80000000000000;
  return;
}

// ==== Aska::RenderThread::EnableFastZ(bool)
// vaddr 0x21c2670 | ghidra 0x22c2670 | size 40 | symbol _ZN4Aska12RenderThread11EnableFastZEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread11EnableFastZEb(long param_1,byte param_2)

{
  *(byte *)(param_1 + 0x501d5) = param_2 & 1;
  (*(code *)PTR__ZN4Aska11RenderState6Static16EnableColorWriteEPNS_14RenderDeviceGLEb_02cb0e38)
            (*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,~param_2 & 1);
  return;
}

// ==== Aska::RenderThread::DirectInsertCallBack(void (*)(unsigned long, unsigned long), unsigned long, unsigned long)
// vaddr 0x21c2698 | ghidra 0x22c2698 | size 104 | symbol _ZN4Aska12RenderThread20DirectInsertCallBackEPFvmmEmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread20DirectInsertCallBackEPFvmmEmm
               (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x501e0);
  *(undefined8 *)(lVar1 + (ulong)*(ushort *)(lVar1 + 0x301c) * 8 + 0x18) = param_2;
  *(undefined8 *)(lVar1 + (ulong)*(ushort *)(lVar1 + 0x301c) * 8 + 0x1018) = param_3;
  *(undefined8 *)(lVar1 + (ulong)*(ushort *)(lVar1 + 0x301c) * 8 + 0x2018) = param_4;
  *(ushort *)(lVar1 + 0x301c) = *(short *)(lVar1 + 0x301c) + 1U & 0x1ff;
  lVar1 = *(long *)(param_1 + 0x501e0);
  *(ushort *)(lVar1 + 0x301a) = *(short *)(lVar1 + 0x301a) + 1U & 0x1ff;
  (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(lVar1 + 0x3020);
  return;
}

// ==== Aska::RenderThread::CheckBoot()
// vaddr 0x21c2734 | ghidra 0x22c2734 | size 36 | symbol _ZN4Aska12RenderThread9CheckBootEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread9CheckBootEv(long param_1)

{
  if (*(char *)(param_1 + 0x192) == '\x02') {
    return;
  }
  *(undefined1 *)(param_1 + 0x192) = 2;
  (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(param_1 + 0x18);
  return;
}

// ==== Aska::RenderThread::AddCreateRenderTarget(unsigned int, Aska::MULTIPASS_ENVIRONMENT*)
// vaddr 0x21c2758 | ghidra 0x22c2758 | size 8 | symbol _ZN4Aska12RenderThread21AddCreateRenderTargetEjPNS_21MULTIPASS_ENVIRONMENTE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska12RenderThread21AddCreateRenderTargetEjPNS_21MULTIPASS_ENVIRONMENTE(void)

{
  return 0;
}

// ==== Aska::RenderThread::AddChangeRenderTarget(unsigned int, Aska::MULTIPASS_ENVIRONMENT*)
// vaddr 0x21c2760 | ghidra 0x22c2760 | size 520 | symbol _ZN4Aska12RenderThread21AddChangeRenderTargetEjPNS_21MULTIPASS_ENVIRONMENTE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska12RenderThread21AddChangeRenderTargetEjPNS_21MULTIPASS_ENVIRONMENTE
          (long param_1,uint param_2,undefined8 param_3)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  undefined4 uVar9;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined4 uStack_38;
  undefined2 uStack_34;
  undefined1 uStack_32;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x022c2868;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x5022c);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
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
          Aska::Semaphore::Wait() const(param_1 + 0x50268);
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
          if (cVar4 == '\0') goto code_r0x022c2858;
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
code_r0x022c2858:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x022c2868:
  DataMemoryBarrier(2,3);
  uVar3 = *(uint *)(param_1 + 0x1a0);
  if (*(uint *)(param_1 + 0x1a4) == uVar3) {
    uVar9 = 0;
  }
  else {
    lVar8 = param_1 + (ulong)uVar3 * 0x28;
    *(undefined1 *)(lVar8 + 0x1a8) = 2;
    *(undefined4 *)(lVar8 + 0x1a9) = uStack_38;
    *(undefined1 *)(lVar8 + 0x1af) = uStack_32;
    *(undefined2 *)(lVar8 + 0x1ad) = uStack_34;
    *(ulong *)(lVar8 + 0x1b0) = (ulong)param_2;
    *(undefined8 *)(lVar8 + 0x1b8) = param_3;
    iVar7 = 0;
    if (uVar3 + 1 < 0x2001) {
      iVar7 = uVar3 + 1;
    }
    *(undefined8 *)(lVar8 + 0x1c8) = uStack_48;
    *(undefined8 *)(lVar8 + 0x1c0) = uStack_50;
    DataMemoryBarrier(2,3);
    *(int *)(param_1 + 0x1a0) = iVar7;
    if (*(char *)(param_1 + 0x192) != '\x02') {
      *(undefined1 *)(param_1 + 0x192) = 2;
      Aska::Event::Set() const(param_1 + 0x18);
    }
    uVar9 = 1;
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x5022c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x50268);
    }
  }
  return uVar9;
}

// ==== Aska::RenderThread::AddReloadZCull()
// vaddr 0x21c2968 | ghidra 0x22c2968 | size 492 | symbol _ZN4Aska12RenderThread14AddReloadZCullEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska12RenderThread14AddReloadZCullEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  undefined4 uVar9;
  undefined4 uStack_28;
  undefined2 uStack_24;
  undefined1 uStack_22;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x022c2a60;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x5022c);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
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
          Aska::Semaphore::Wait() const(param_1 + 0x50268);
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
          if (cVar4 == '\0') goto code_r0x022c2a50;
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
code_r0x022c2a50:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x022c2a60:
  DataMemoryBarrier(2,3);
  uVar3 = *(uint *)(param_1 + 0x1a0);
  if (*(uint *)(param_1 + 0x1a4) == uVar3) {
    uVar9 = 0;
  }
  else {
    lVar8 = param_1 + (ulong)uVar3 * 0x28;
    *(undefined1 *)(lVar8 + 0x1a8) = 0xb;
    *(undefined1 *)(lVar8 + 0x1af) = uStack_22;
    iVar7 = 0;
    if (uVar3 + 1 < 0x2001) {
      iVar7 = uVar3 + 1;
    }
    *(undefined2 *)(lVar8 + 0x1ad) = uStack_24;
    *(undefined4 *)(lVar8 + 0x1a9) = uStack_28;
    *(undefined8 *)(lVar8 + 0x1b8) = 0;
    *(undefined8 *)(lVar8 + 0x1c0) = 0;
    *(undefined8 *)(lVar8 + 0x1b0) = 0;
    DataMemoryBarrier(2,3);
    *(int *)(param_1 + 0x1a0) = iVar7;
    if (*(char *)(param_1 + 0x192) != '\x02') {
      *(undefined1 *)(param_1 + 0x192) = 2;
      Aska::Event::Set() const(param_1 + 0x18);
    }
    uVar9 = 1;
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x5022c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x50268);
    }
  }
  return uVar9;
}

// ==== Aska::RenderThread::AddEnableGnmOcclusionQuery(bool)
// vaddr 0x21c2b54 | ghidra 0x22c2b54 | size 508 | symbol _ZN4Aska12RenderThread26AddEnableGnmOcclusionQueryEb | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska12RenderThread26AddEnableGnmOcclusionQueryEb(long param_1,uint param_2)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  undefined4 uVar9;
  undefined4 uStack_38;
  undefined2 uStack_34;
  undefined1 uStack_32;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x022c2c54;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x5022c);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
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
          Aska::Semaphore::Wait() const(param_1 + 0x50268);
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
          if (cVar4 == '\0') goto code_r0x022c2c44;
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
code_r0x022c2c44:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x022c2c54:
  DataMemoryBarrier(2,3);
  uVar3 = *(uint *)(param_1 + 0x1a0);
  if (*(uint *)(param_1 + 0x1a4) == uVar3) {
    uVar9 = 0;
  }
  else {
    lVar8 = param_1 + (ulong)uVar3 * 0x28;
    *(undefined1 *)(lVar8 + 0x1a8) = 0x14;
    *(undefined1 *)(lVar8 + 0x1af) = uStack_32;
    iVar7 = 0;
    if (uVar3 + 1 < 0x2001) {
      iVar7 = uVar3 + 1;
    }
    *(undefined2 *)(lVar8 + 0x1ad) = uStack_34;
    *(undefined4 *)(lVar8 + 0x1a9) = uStack_38;
    *(undefined8 *)(lVar8 + 0x1b8) = 0;
    *(undefined8 *)(lVar8 + 0x1c0) = 0;
    *(ulong *)(lVar8 + 0x1b0) = (ulong)(param_2 & 1);
    DataMemoryBarrier(2,3);
    *(int *)(param_1 + 0x1a0) = iVar7;
    if (*(char *)(param_1 + 0x192) != '\x02') {
      *(undefined1 *)(param_1 + 0x192) = 2;
      Aska::Event::Set() const(param_1 + 0x18);
    }
    uVar9 = 1;
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x5022c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x50268);
    }
  }
  return uVar9;
}

// ==== Aska::RenderThread::AddExposureScale(float, float)
// vaddr 0x21c2d50 | ghidra 0x22c2d50 | size 516 | symbol _ZN4Aska12RenderThread16AddExposureScaleEff | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska12RenderThread16AddExposureScaleEff(undefined4 param_1,undefined4 param_2,long param_3)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  undefined4 uVar9;
  undefined4 uStack_40;
  undefined2 uStack_3c;
  undefined1 uStack_3a;
  undefined4 uStack_34;
  undefined4 uStack_24;
  
  piVar1 = (int *)(param_3 + 0x50228);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x022c2e54;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_3 + 0x5022c);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_3 + 0x50268);
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
          Aska::Semaphore::Wait() const(param_3 + 0x50268);
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
          if (cVar4 == '\0') goto code_r0x022c2e44;
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
code_r0x022c2e44:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x022c2e54:
  DataMemoryBarrier(2,3);
  uVar3 = *(uint *)(param_3 + 0x1a0);
  if (*(uint *)(param_3 + 0x1a4) == uVar3) {
    uVar9 = 0;
  }
  else {
    lVar8 = param_3 + (ulong)uVar3 * 0x28;
    *(undefined1 *)(lVar8 + 0x1a8) = 0x10;
    *(undefined1 *)(lVar8 + 0x1af) = uStack_3a;
    iVar7 = 0;
    if (uVar3 + 1 < 0x2001) {
      iVar7 = uVar3 + 1;
    }
    *(undefined2 *)(lVar8 + 0x1ad) = uStack_3c;
    *(undefined4 *)(lVar8 + 0x1a9) = uStack_40;
    *(ulong *)(lVar8 + 0x1b0) = CONCAT44(uStack_24,param_1);
    *(ulong *)(lVar8 + 0x1b8) = CONCAT44(uStack_34,param_2);
    *(undefined8 *)(lVar8 + 0x1c0) = 0;
    DataMemoryBarrier(2,3);
    *(int *)(param_3 + 0x1a0) = iVar7;
    if (*(char *)(param_3 + 0x192) != '\x02') {
      *(undefined1 *)(param_3 + 0x192) = 2;
      Aska::Event::Set() const(param_3 + 0x18);
    }
    uVar9 = 1;
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_3 + 0x5022c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_3 + 0x50268);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_3 + 0x50268);
    }
  }
  return uVar9;
}

// ==== Aska::RenderThread::AddEnableFastZ(bool)
// vaddr 0x21c2f54 | ghidra 0x22c2f54 | size 508 | symbol _ZN4Aska12RenderThread14AddEnableFastZEb | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska12RenderThread14AddEnableFastZEb(long param_1,uint param_2)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  undefined4 uVar9;
  undefined4 uStack_38;
  undefined2 uStack_34;
  undefined1 uStack_32;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x022c3054;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x5022c);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
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
          Aska::Semaphore::Wait() const(param_1 + 0x50268);
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
          if (cVar4 == '\0') goto code_r0x022c3044;
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
code_r0x022c3044:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x022c3054:
  DataMemoryBarrier(2,3);
  uVar3 = *(uint *)(param_1 + 0x1a0);
  if (*(uint *)(param_1 + 0x1a4) == uVar3) {
    uVar9 = 0;
  }
  else {
    lVar8 = param_1 + (ulong)uVar3 * 0x28;
    *(undefined1 *)(lVar8 + 0x1a8) = 0x11;
    *(undefined1 *)(lVar8 + 0x1af) = uStack_32;
    iVar7 = 0;
    if (uVar3 + 1 < 0x2001) {
      iVar7 = uVar3 + 1;
    }
    *(undefined2 *)(lVar8 + 0x1ad) = uStack_34;
    *(undefined4 *)(lVar8 + 0x1a9) = uStack_38;
    *(undefined8 *)(lVar8 + 0x1b8) = 0;
    *(undefined8 *)(lVar8 + 0x1c0) = 0;
    *(ulong *)(lVar8 + 0x1b0) = (ulong)(param_2 & 1);
    DataMemoryBarrier(2,3);
    *(int *)(param_1 + 0x1a0) = iVar7;
    if (*(char *)(param_1 + 0x192) != '\x02') {
      *(undefined1 *)(param_1 + 0x192) = 2;
      Aska::Event::Set() const(param_1 + 0x18);
    }
    uVar9 = 1;
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x5022c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x50268);
    }
  }
  return uVar9;
}

// ==== Aska::RenderThread::AddFinishRenderTarget(unsigned int, int, int)
// vaddr 0x21c3150 | ghidra 0x22c3150 | size 532 | symbol _ZN4Aska12RenderThread21AddFinishRenderTargetEjii | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska12RenderThread21AddFinishRenderTargetEjii(long param_1,uint param_2,int param_3,int param_4)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  undefined4 uVar9;
  undefined4 uStack_48;
  undefined2 uStack_44;
  undefined1 uStack_42;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x022c325c;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x5022c);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
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
          Aska::Semaphore::Wait() const(param_1 + 0x50268);
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
          if (cVar4 == '\0') goto code_r0x022c324c;
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
code_r0x022c324c:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x022c325c:
  DataMemoryBarrier(2,3);
  uVar3 = *(uint *)(param_1 + 0x1a0);
  if (*(uint *)(param_1 + 0x1a4) == uVar3) {
    uVar9 = 0;
  }
  else {
    lVar8 = param_1 + (ulong)uVar3 * 0x28;
    *(undefined1 *)(lVar8 + 0x1a8) = 3;
    *(undefined1 *)(lVar8 + 0x1af) = uStack_42;
    *(undefined2 *)(lVar8 + 0x1ad) = uStack_44;
    iVar7 = 0;
    if (uVar3 + 1 < 0x2001) {
      iVar7 = uVar3 + 1;
    }
    *(undefined4 *)(lVar8 + 0x1a9) = uStack_48;
    *(ulong *)(lVar8 + 0x1b0) = (ulong)param_2;
    *(long *)(lVar8 + 0x1b8) = (long)param_3;
    *(long *)(lVar8 + 0x1c0) = (long)param_4;
    DataMemoryBarrier(2,3);
    *(int *)(param_1 + 0x1a0) = iVar7;
    if (*(char *)(param_1 + 0x192) != '\x02') {
      *(undefined1 *)(param_1 + 0x192) = 2;
      Aska::Event::Set() const(param_1 + 0x18);
    }
    uVar9 = 1;
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x5022c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x50268);
    }
  }
  return uVar9;
}

// ==== Aska::RenderThread::AddTemporaryResolve(Aska::RenderableObject*, int, int)
// vaddr 0x21c3364 | ghidra 0x22c3364 | size 528 | symbol _ZN4Aska12RenderThread19AddTemporaryResolveEPNS_16RenderableObjectEii | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska12RenderThread19AddTemporaryResolveEPNS_16RenderableObjectEii
          (long param_1,undefined8 param_2,int param_3,int param_4)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  undefined4 uVar9;
  undefined4 uStack_48;
  undefined2 uStack_44;
  undefined1 uStack_42;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x022c3470;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x5022c);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
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
          Aska::Semaphore::Wait() const(param_1 + 0x50268);
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
          if (cVar4 == '\0') goto code_r0x022c3460;
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
code_r0x022c3460:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x022c3470:
  DataMemoryBarrier(2,3);
  uVar3 = *(uint *)(param_1 + 0x1a0);
  if (*(uint *)(param_1 + 0x1a4) == uVar3) {
    uVar9 = 0;
  }
  else {
    lVar8 = param_1 + (ulong)uVar3 * 0x28;
    *(undefined1 *)(lVar8 + 0x1a8) = 4;
    *(undefined1 *)(lVar8 + 0x1af) = uStack_42;
    *(undefined2 *)(lVar8 + 0x1ad) = uStack_44;
    iVar7 = 0;
    if (uVar3 + 1 < 0x2001) {
      iVar7 = uVar3 + 1;
    }
    *(undefined4 *)(lVar8 + 0x1a9) = uStack_48;
    *(undefined8 *)(lVar8 + 0x1b0) = param_2;
    *(long *)(lVar8 + 0x1b8) = (long)param_3;
    *(long *)(lVar8 + 0x1c0) = (long)param_4;
    DataMemoryBarrier(2,3);
    *(int *)(param_1 + 0x1a0) = iVar7;
    if (*(char *)(param_1 + 0x192) != '\x02') {
      *(undefined1 *)(param_1 + 0x192) = 2;
      Aska::Event::Set() const(param_1 + 0x18);
    }
    uVar9 = 1;
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x5022c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x50268);
    }
  }
  return uVar9;
}

// ==== Aska::RenderThread::AddRenderQueue(Aska::RenderableObject*, Aska::RenderContext*, int)
// vaddr 0x21c3574 | ghidra 0x22c3574 | size 128 | symbol _ZN4Aska12RenderThread14AddRenderQueueEPNS_16RenderableObjectEPNS_13RenderContextEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska12RenderThread14AddRenderQueueEPNS_16RenderableObjectEPNS_13RenderContextEi
          (long param_1,long param_2,undefined8 param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  long lVar5;
  
  piVar1 = (int *)(param_2 + 0x1a8);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  lVar5 = param_1 + (long)*(int *)(param_1 + 0x1a0) * 0x28;
  if (*(int *)(param_1 + 0x1a4) == *(int *)(param_1 + 0x1a0)) {
    return 0;
  }
  *(undefined1 *)(lVar5 + 0x1a8) = 0;
  *(long *)(lVar5 + 0x1b0) = param_2;
  *(undefined8 *)(lVar5 + 0x1b8) = param_3;
  *(long *)(lVar5 + 0x1c0) = (long)param_4;
  DataMemoryBarrier(2,3);
  if (*(int *)(param_1 + 0x1a4) != *(int *)(param_1 + 0x1a0)) {
    iVar2 = 0;
    if (*(int *)(param_1 + 0x1a0) < 0x2000) {
      iVar2 = *(int *)(param_1 + 0x1a0) + 1;
    }
    *(int *)(param_1 + 0x1a0) = iVar2;
  }
  DataMemoryBarrier(2,3);
  return 1;
}

// ==== Aska::RenderThread::AddBeginRender()
// vaddr 0x21c35f4 | ghidra 0x22c35f4 | size 492 | symbol _ZN4Aska12RenderThread14AddBeginRenderEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska12RenderThread14AddBeginRenderEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  undefined4 uVar9;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined7 uStack_40;
  undefined1 uStack_39;
  undefined7 uStack_38;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x022c36f0;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x5022c);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
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
          Aska::Semaphore::Wait() const(param_1 + 0x50268);
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
          if (cVar4 == '\0') goto code_r0x022c36e0;
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
code_r0x022c36e0:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x022c36f0:
  DataMemoryBarrier(2,3);
  uVar3 = *(uint *)(param_1 + 0x1a0);
  if (*(uint *)(param_1 + 0x1a4) == uVar3) {
    uVar9 = 0;
  }
  else {
    uVar9 = 1;
    lVar8 = param_1 + (ulong)uVar3 * 0x28;
    *(undefined1 *)(lVar8 + 0x1a8) = 1;
    *(ulong *)(lVar8 + 0x1c8) = CONCAT71(uStack_38,uStack_39);
    *(ulong *)(lVar8 + 0x1c1) = CONCAT17(uStack_39,uStack_40);
    *(undefined8 *)(lVar8 + 0x1b9) = uStack_48;
    iVar7 = 0;
    if (uVar3 + 1 < 0x2001) {
      iVar7 = uVar3 + 1;
    }
    *(undefined8 *)(lVar8 + 0x1b1) = uStack_50;
    *(undefined8 *)(lVar8 + 0x1a9) = uStack_58;
    DataMemoryBarrier(2,3);
    *(int *)(param_1 + 0x1a0) = iVar7;
    if (*(char *)(param_1 + 0x192) != '\x02') {
      *(undefined1 *)(param_1 + 0x192) = 2;
      Aska::Event::Set() const(param_1 + 0x18);
      uVar9 = 1;
    }
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x5022c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x50268);
    }
  }
  return uVar9;
}

// ==== Aska::RenderThread::AddEndRender(Aska::INotify*)
// vaddr 0x21c37e0 | ghidra 0x22c37e0 | size 532 | symbol _ZN4Aska12RenderThread12AddEndRenderEPNS_7INotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska12RenderThread12AddEndRenderEPNS_7INotifyE(long param_1,undefined8 param_2)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  undefined4 uVar9;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined4 uStack_38;
  undefined2 uStack_34;
  undefined1 uStack_32;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x022c38e0;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x5022c);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
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
          Aska::Semaphore::Wait() const(param_1 + 0x50268);
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
          if (cVar4 == '\0') goto code_r0x022c38d0;
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
code_r0x022c38d0:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x022c38e0:
  DataMemoryBarrier(2,3);
  uVar3 = *(uint *)(param_1 + 0x1a0);
  if (*(uint *)(param_1 + 0x1a4) == uVar3) {
    uVar9 = 0;
  }
  else {
    lVar8 = param_1 + (ulong)uVar3 * 0x28;
    *(undefined1 *)(lVar8 + 0x1a8) = 6;
    *(undefined4 *)(lVar8 + 0x1a9) = uStack_38;
    *(undefined1 *)(lVar8 + 0x1af) = uStack_32;
    *(undefined2 *)(lVar8 + 0x1ad) = uStack_34;
    *(undefined8 *)(lVar8 + 0x1b0) = param_2;
    iVar7 = 0;
    if (uVar3 + 1 < 0x2001) {
      iVar7 = uVar3 + 1;
    }
    *(undefined8 *)(lVar8 + 0x1c8) = uStack_40;
    *(undefined8 *)(lVar8 + 0x1c0) = uStack_48;
    *(undefined8 *)(lVar8 + 0x1b8) = uStack_50;
    DataMemoryBarrier(2,3);
    *(int *)(param_1 + 0x1a0) = iVar7;
    if (*(char *)(param_1 + 0x192) != '\x02') {
      *(undefined1 *)(param_1 + 0x192) = 2;
      Aska::Event::Set() const(param_1 + 0x18);
    }
    uVar9 = 1;
  }
  *(short *)(param_1 + 400) = *(short *)(param_1 + 400) + 1;
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x5022c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x50268);
    }
  }
  return uVar9;
}

// ==== Aska::RenderThread::AddCallBack(void (*)(unsigned long, unsigned long), unsigned long, unsigned long)
// vaddr 0x21c39f4 | ghidra 0x22c39f4 | size 520 | symbol _ZN4Aska12RenderThread11AddCallBackEPFvmmEmm | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska12RenderThread11AddCallBackEPFvmmEmm
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  undefined4 uVar9;
  undefined4 uStack_48;
  undefined2 uStack_44;
  undefined1 uStack_42;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x022c3b00;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x5022c);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
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
          Aska::Semaphore::Wait() const(param_1 + 0x50268);
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
          if (cVar4 == '\0') goto code_r0x022c3af0;
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
code_r0x022c3af0:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x022c3b00:
  DataMemoryBarrier(2,3);
  uVar3 = *(uint *)(param_1 + 0x1a0);
  if (*(uint *)(param_1 + 0x1a4) == uVar3) {
    uVar9 = 0;
  }
  else {
    lVar8 = param_1 + (ulong)uVar3 * 0x28;
    *(undefined1 *)(lVar8 + 0x1a8) = 7;
    *(undefined1 *)(lVar8 + 0x1af) = uStack_42;
    iVar7 = 0;
    if (uVar3 + 1 < 0x2001) {
      iVar7 = uVar3 + 1;
    }
    *(undefined2 *)(lVar8 + 0x1ad) = uStack_44;
    *(undefined4 *)(lVar8 + 0x1a9) = uStack_48;
    *(undefined8 *)(lVar8 + 0x1b0) = param_2;
    *(undefined8 *)(lVar8 + 0x1b8) = param_3;
    *(undefined8 *)(lVar8 + 0x1c0) = param_4;
    DataMemoryBarrier(2,3);
    *(int *)(param_1 + 0x1a0) = iVar7;
    if (*(char *)(param_1 + 0x192) != '\x02') {
      *(undefined1 *)(param_1 + 0x192) = 2;
      Aska::Event::Set() const(param_1 + 0x18);
    }
    uVar9 = 1;
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x5022c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x50268);
    }
  }
  return uVar9;
}

// ==== Aska::RenderThread::ReqCustomCommandBlock(void (*)(unsigned long, unsigned long), unsigned long, unsigned long)
// vaddr 0x21c3bfc | ghidra 0x22c3bfc | size 108 | symbol _ZN4Aska12RenderThread21ReqCustomCommandBlockEPFvmmEmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread21ReqCustomCommandBlockEPFvmmEmm
               (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  Aska::CriticalSection::Enter() const(param_1 + 0xe8);
  Aska::Event::Reset() const(param_1 + 0x110);
  *(undefined8 *)(param_1 + 0x180) = param_3;
  *(undefined8 *)(param_1 + 0x188) = param_4;
  *(undefined8 *)(param_1 + 0x178) = param_2;
  Aska::Event::Set() const(param_1 + 0x18);
  Aska::Event::Wait(unsigned int) const(param_1 + 0x110,0);
  (*(code *)PTR__ZNK4Aska15CriticalSection5LeaveEv_02ca8d00)(param_1 + 0xe8);
  return;
}

// ==== Aska::RenderThread::ReqDownloadResourceBlock(Aska::GpuResource*)
// vaddr 0x21c3c98 | ghidra 0x22c3c98 | size 116 | symbol _ZN4Aska12RenderThread24ReqDownloadResourceBlockEPNS_11GpuResourceE | lib libSOA-3.7.0.so | 2026-10-04
undefined1
_ZN4Aska12RenderThread24ReqDownloadResourceBlockEPNS_11GpuResourceE(long param_1,undefined8 param_2)

{
  undefined *puVar1;
  undefined1 auStack_24 [4];
  
  auStack_24[0] = 0;
  Aska::CriticalSection::Enter() const(param_1 + 0xe8);
  Aska::Event::Reset() const(param_1 + 0x110);
  puVar1 = PTR__Z16DownloadResourcemm_02cc4c60;
  *(undefined8 *)(param_1 + 0x180) = param_2;
  *(undefined1 **)(param_1 + 0x188) = auStack_24;
  *(undefined **)(param_1 + 0x178) = puVar1;
  Aska::Event::Set() const(param_1 + 0x18);
  Aska::Event::Wait(unsigned int) const(param_1 + 0x110,0);
  Aska::CriticalSection::Leave() const(param_1 + 0xe8);
  return auStack_24[0];
}

// ==== Aska::RenderThread::AddDataTransfer(void*, void*, unsigned int)
// vaddr 0x21c3d0c | ghidra 0x22c3d0c | size 524 | symbol _ZN4Aska12RenderThread15AddDataTransferEPvS1_j | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska12RenderThread15AddDataTransferEPvS1_j
          (long param_1,undefined8 param_2,undefined8 param_3,uint param_4)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  undefined4 uVar9;
  undefined4 uStack_48;
  undefined2 uStack_44;
  undefined1 uStack_42;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x022c3e18;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x5022c);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
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
          Aska::Semaphore::Wait() const(param_1 + 0x50268);
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
          if (cVar4 == '\0') goto code_r0x022c3e08;
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
code_r0x022c3e08:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x022c3e18:
  DataMemoryBarrier(2,3);
  uVar3 = *(uint *)(param_1 + 0x1a0);
  if (*(uint *)(param_1 + 0x1a4) == uVar3) {
    uVar9 = 0;
  }
  else {
    lVar8 = param_1 + (ulong)uVar3 * 0x28;
    *(undefined1 *)(lVar8 + 0x1a8) = 0xc;
    *(undefined1 *)(lVar8 + 0x1af) = uStack_42;
    iVar7 = 0;
    if (uVar3 + 1 < 0x2001) {
      iVar7 = uVar3 + 1;
    }
    *(undefined2 *)(lVar8 + 0x1ad) = uStack_44;
    *(undefined4 *)(lVar8 + 0x1a9) = uStack_48;
    *(undefined8 *)(lVar8 + 0x1b0) = param_2;
    *(undefined8 *)(lVar8 + 0x1b8) = param_3;
    *(ulong *)(lVar8 + 0x1c0) = (ulong)param_4;
    DataMemoryBarrier(2,3);
    *(int *)(param_1 + 0x1a0) = iVar7;
    if (*(char *)(param_1 + 0x192) != '\x02') {
      *(undefined1 *)(param_1 + 0x192) = 2;
      Aska::Event::Set() const(param_1 + 0x18);
    }
    uVar9 = 1;
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x5022c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x50268);
    }
  }
  return uVar9;
}

// ==== Aska::RenderThread::ExecutePendingTileRegionOperationByAddress(void*)
// vaddr 0x21c3f18 | ghidra 0x22c3f18 | size 520 | symbol _ZN4Aska12RenderThread42ExecutePendingTileRegionOperationByAddressEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread42ExecutePendingTileRegionOperationByAddressEPv
               (long param_1,undefined8 param_2)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined4 uStack_38;
  undefined2 uStack_34;
  undefined1 uStack_32;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x022c4018;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x5022c);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
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
          Aska::Semaphore::Wait() const(param_1 + 0x50268);
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
          if (cVar4 == '\0') goto code_r0x022c4008;
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
code_r0x022c4008:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x022c4018:
  DataMemoryBarrier(2,3);
  uVar3 = *(uint *)(param_1 + 0x1a0);
  if (*(uint *)(param_1 + 0x1a4) != uVar3) {
    lVar8 = param_1 + (ulong)uVar3 * 0x28;
    *(undefined1 *)(lVar8 + 0x1a8) = 0xe;
    *(undefined4 *)(lVar8 + 0x1a9) = uStack_38;
    *(undefined1 *)(lVar8 + 0x1af) = uStack_32;
    *(undefined2 *)(lVar8 + 0x1ad) = uStack_34;
    *(undefined8 *)(lVar8 + 0x1b0) = param_2;
    iVar7 = 0;
    if (uVar3 + 1 < 0x2001) {
      iVar7 = uVar3 + 1;
    }
    *(undefined8 *)(lVar8 + 0x1c8) = uStack_40;
    *(undefined8 *)(lVar8 + 0x1c0) = uStack_48;
    *(undefined8 *)(lVar8 + 0x1b8) = uStack_50;
    DataMemoryBarrier(2,3);
    *(int *)(param_1 + 0x1a0) = iVar7;
    if (*(char *)(param_1 + 0x192) != '\x02') {
      *(undefined1 *)(param_1 + 0x192) = 2;
      Aska::Event::Set() const(param_1 + 0x18);
    }
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x5022c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
    if ((uVar6 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x50268);
      return;
    }
  }
  return;
}

// ==== Aska::RenderThread::AddOcclusionQueryBegin(unsigned int*)
// vaddr 0x21c4120 | ghidra 0x22c4120 | size 520 | symbol _ZN4Aska12RenderThread22AddOcclusionQueryBeginEPj | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska12RenderThread22AddOcclusionQueryBeginEPj(long param_1,undefined8 param_2)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  undefined4 uVar9;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined4 uStack_38;
  undefined2 uStack_34;
  undefined1 uStack_32;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x022c4220;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x5022c);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
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
          Aska::Semaphore::Wait() const(param_1 + 0x50268);
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
          if (cVar4 == '\0') goto code_r0x022c4210;
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
code_r0x022c4210:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x022c4220:
  DataMemoryBarrier(2,3);
  uVar3 = *(uint *)(param_1 + 0x1a0);
  if (*(uint *)(param_1 + 0x1a4) == uVar3) {
    uVar9 = 0;
  }
  else {
    lVar8 = param_1 + (ulong)uVar3 * 0x28;
    *(undefined1 *)(lVar8 + 0x1a8) = 8;
    *(undefined4 *)(lVar8 + 0x1a9) = uStack_38;
    *(undefined1 *)(lVar8 + 0x1af) = uStack_32;
    *(undefined2 *)(lVar8 + 0x1ad) = uStack_34;
    *(undefined8 *)(lVar8 + 0x1b0) = param_2;
    iVar7 = 0;
    if (uVar3 + 1 < 0x2001) {
      iVar7 = uVar3 + 1;
    }
    *(undefined8 *)(lVar8 + 0x1c8) = uStack_40;
    *(undefined8 *)(lVar8 + 0x1c0) = uStack_48;
    *(undefined8 *)(lVar8 + 0x1b8) = uStack_50;
    DataMemoryBarrier(2,3);
    *(int *)(param_1 + 0x1a0) = iVar7;
    if (*(char *)(param_1 + 0x192) != '\x02') {
      *(undefined1 *)(param_1 + 0x192) = 2;
      Aska::Event::Set() const(param_1 + 0x18);
    }
    uVar9 = 1;
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x5022c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x50268);
    }
  }
  return uVar9;
}

// ==== Aska::RenderThread::AddOcclusionQueryEnd()
// vaddr 0x21c4328 | ghidra 0x22c4328 | size 492 | symbol _ZN4Aska12RenderThread20AddOcclusionQueryEndEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska12RenderThread20AddOcclusionQueryEndEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  undefined4 uVar9;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined7 uStack_40;
  undefined1 uStack_39;
  undefined7 uStack_38;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x022c4424;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x5022c);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
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
          Aska::Semaphore::Wait() const(param_1 + 0x50268);
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
          if (cVar4 == '\0') goto code_r0x022c4414;
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
code_r0x022c4414:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x022c4424:
  DataMemoryBarrier(2,3);
  uVar3 = *(uint *)(param_1 + 0x1a0);
  if (*(uint *)(param_1 + 0x1a4) == uVar3) {
    uVar9 = 0;
  }
  else {
    lVar8 = param_1 + (ulong)uVar3 * 0x28;
    *(undefined1 *)(lVar8 + 0x1a8) = 9;
    *(ulong *)(lVar8 + 0x1c8) = CONCAT71(uStack_38,uStack_39);
    *(ulong *)(lVar8 + 0x1c1) = CONCAT17(uStack_39,uStack_40);
    *(undefined8 *)(lVar8 + 0x1b9) = uStack_48;
    iVar7 = 0;
    if (uVar3 + 1 < 0x2001) {
      iVar7 = uVar3 + 1;
    }
    *(undefined8 *)(lVar8 + 0x1b1) = uStack_50;
    *(undefined8 *)(lVar8 + 0x1a9) = uStack_58;
    DataMemoryBarrier(2,3);
    *(int *)(param_1 + 0x1a0) = iVar7;
    if (*(char *)(param_1 + 0x192) != '\x02') {
      *(undefined1 *)(param_1 + 0x192) = 2;
      Aska::Event::Set() const(param_1 + 0x18);
    }
    uVar9 = 1;
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x5022c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x50268);
    }
  }
  return uVar9;
}

// ==== Aska::RenderThread::WaitDeviceReset()
// vaddr 0x21c4514 | ghidra 0x22c4514 | size 32 | symbol _ZN4Aska12RenderThread15WaitDeviceResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread15WaitDeviceResetEv(long param_1)

{
  if (*(char *)(param_1 + 0x501d1) != '\0') {
    (*(code *)PTR__ZNK4Aska5Event4WaitEj_02c992c0)(param_1 + 0x80,0);
    return;
  }
  return;
}

// ==== Aska::RenderThread::ReqDeviceReset()
// vaddr 0x21c4534 | ghidra 0x22c4534 | size 408 | symbol _ZN4Aska12RenderThread14ReqDeviceResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread14ReqDeviceResetEv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  int *piVar6;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar5 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar3 = 0x1fe < iVar5;
      iVar5 = iVar5 + 1;
      if (bVar3) {
        piVar6 = (int *)(param_1 + 0x5022c);
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = *piVar6 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        do {
          if (*piVar1 != -1) {
            ClearExclusiveLocal();
            do {
              uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
              if ((uVar4 & 1) == 0) {
                do {
                  cVar2 = '\x01';
                  bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
                  if (bVar3) {
                    *piVar6 = *piVar6 + -1;
                    cVar2 = ExclusiveMonitorsStatus();
                  }
                } while (cVar2 != '\0');
                Aska::Thread::Sleep(unsigned int)(1);
              }
              else {
                Aska::Semaphore::Wait() const(param_1 + 0x50268);
              }
              do {
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
                if (bVar3) {
                  *piVar6 = *piVar6 + 1;
                  cVar2 = ExclusiveMonitorsStatus();
                }
              } while (cVar2 != '\0');
              while (*piVar1 == -1) {
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar3) {
                  *piVar1 = 0;
                  cVar2 = ExclusiveMonitorsStatus();
                }
                if (cVar2 == '\0') goto code_r0x022c46b4;
              }
              ClearExclusiveLocal();
            } while( true );
          }
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
code_r0x022c46b4:
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = *piVar6 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        DataMemoryBarrier(2,3);
code_r0x022c45c0:
        piVar6 = (int *)(param_1 + 0x5022c);
        *(undefined1 *)(param_1 + 0x501d1) = 1;
        Aska::Event::Set() const(param_1 + 0x18);
        Aska::Event::Reset() const(param_1 + 0x80);
        DataMemoryBarrier(2,3);
        *piVar1 = -1;
        DataMemoryBarrier(2,3);
        if (0x14 < *piVar6) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
            if (bVar3) {
              *piVar6 = *piVar6 + -1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
          if ((uVar4 & 1) != 0) {
            (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x50268);
            return;
          }
        }
        return;
      }
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x022c45c0;
}

// ==== Aska::RenderThread::ReqExit()
// vaddr 0x21c46cc | ghidra 0x22c46cc | size 400 | symbol _ZN4Aska12RenderThread7ReqExitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread7ReqExitEv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  int *piVar6;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar5 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar3 = 0x1fe < iVar5;
      iVar5 = iVar5 + 1;
      if (bVar3) {
        piVar6 = (int *)(param_1 + 0x5022c);
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = *piVar6 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        do {
          if (*piVar1 != -1) {
            ClearExclusiveLocal();
            do {
              uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
              if ((uVar4 & 1) == 0) {
                do {
                  cVar2 = '\x01';
                  bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
                  if (bVar3) {
                    *piVar6 = *piVar6 + -1;
                    cVar2 = ExclusiveMonitorsStatus();
                  }
                } while (cVar2 != '\0');
                Aska::Thread::Sleep(unsigned int)(1);
              }
              else {
                Aska::Semaphore::Wait() const(param_1 + 0x50268);
              }
              do {
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
                if (bVar3) {
                  *piVar6 = *piVar6 + 1;
                  cVar2 = ExclusiveMonitorsStatus();
                }
              } while (cVar2 != '\0');
              while (*piVar1 == -1) {
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar3) {
                  *piVar1 = 0;
                  cVar2 = ExclusiveMonitorsStatus();
                }
                if (cVar2 == '\0') goto code_r0x022c4844;
              }
              ClearExclusiveLocal();
            } while( true );
          }
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
code_r0x022c4844:
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = *piVar6 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        DataMemoryBarrier(2,3);
code_r0x022c4758:
        piVar6 = (int *)(param_1 + 0x5022c);
        *(undefined1 *)(param_1 + 0x501d4) = 1;
        Aska::Event::Set() const(param_1 + 0x18);
        DataMemoryBarrier(2,3);
        *piVar1 = -1;
        DataMemoryBarrier(2,3);
        if (0x14 < *piVar6) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
            if (bVar3) {
              *piVar6 = *piVar6 + -1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
          if ((uVar4 & 1) != 0) {
            (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x50268);
            return;
          }
        }
        return;
      }
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x022c4758;
}

// ==== Aska::RenderThread::ReqSwap()
// vaddr 0x21c485c | ghidra 0x22c485c | size 492 | symbol _ZN4Aska12RenderThread7ReqSwapEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread7ReqSwapEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined7 uStack_40;
  undefined1 uStack_39;
  undefined7 uStack_38;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x022c4958;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x5022c);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
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
          Aska::Semaphore::Wait() const(param_1 + 0x50268);
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
          if (cVar4 == '\0') goto code_r0x022c4948;
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
code_r0x022c4948:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x022c4958:
  DataMemoryBarrier(2,3);
  uVar3 = *(uint *)(param_1 + 0x1a0);
  if (*(uint *)(param_1 + 0x1a4) != uVar3) {
    lVar8 = param_1 + (ulong)uVar3 * 0x28;
    *(undefined1 *)(lVar8 + 0x1a8) = 10;
    *(ulong *)(lVar8 + 0x1c8) = CONCAT71(uStack_38,uStack_39);
    *(ulong *)(lVar8 + 0x1c1) = CONCAT17(uStack_39,uStack_40);
    *(undefined8 *)(lVar8 + 0x1b9) = uStack_48;
    iVar7 = 0;
    if (uVar3 + 1 < 0x2001) {
      iVar7 = uVar3 + 1;
    }
    *(undefined8 *)(lVar8 + 0x1b1) = uStack_50;
    *(undefined8 *)(lVar8 + 0x1a9) = uStack_58;
    DataMemoryBarrier(2,3);
    *(int *)(param_1 + 0x1a0) = iVar7;
    if (*(char *)(param_1 + 0x192) != '\x02') {
      *(undefined1 *)(param_1 + 0x192) = 2;
      Aska::Event::Set() const(param_1 + 0x18);
    }
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x5022c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
    if ((uVar6 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x50268);
      return;
    }
  }
  return;
}

// ==== Aska::RenderThread::ReqDeviceInit()
// vaddr 0x21c4a48 | ghidra 0x22c4a48 | size 516 | symbol _ZN4Aska12RenderThread13ReqDeviceInitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread13ReqDeviceInitEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined4 uStack_28;
  undefined2 uStack_24;
  undefined1 uStack_22;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x022c4b44;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x5022c);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
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
          Aska::Semaphore::Wait() const(param_1 + 0x50268);
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
          if (cVar4 == '\0') goto code_r0x022c4b34;
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
code_r0x022c4b34:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x022c4b44:
  DataMemoryBarrier(2,3);
  uVar3 = *(uint *)(param_1 + 0x1a0);
  if (*(uint *)(param_1 + 0x1a4) != uVar3) {
    lVar8 = param_1 + (ulong)uVar3 * 0x28;
    *(undefined1 *)(lVar8 + 0x1a8) = 0x13;
    *(undefined4 *)(lVar8 + 0x1a9) = uStack_28;
    *(undefined1 *)(lVar8 + 0x1af) = uStack_22;
    *(undefined2 *)(lVar8 + 0x1ad) = uStack_24;
    *(undefined8 *)(lVar8 + 0x1b0) = 0;
    iVar7 = 0;
    if (uVar3 + 1 < 0x2001) {
      iVar7 = uVar3 + 1;
    }
    *(undefined8 *)(lVar8 + 0x1c8) = uStack_38;
    *(undefined8 *)(lVar8 + 0x1c0) = uStack_40;
    *(undefined8 *)(lVar8 + 0x1b8) = uStack_48;
    DataMemoryBarrier(2,3);
    *(int *)(param_1 + 0x1a0) = iVar7;
    if (*(char *)(param_1 + 0x192) != '\x02') {
      *(undefined1 *)(param_1 + 0x192) = 2;
      Aska::Event::Set() const(param_1 + 0x18);
    }
  }
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0x5022c);
  if (0x14 < *piVar1) {
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
    if ((uVar6 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x50268);
      return;
    }
  }
  return;
}

// ==== Aska::RenderThread::ReqGpuWait()
// vaddr 0x21c4c4c | ghidra 0x22c4c4c | size 400 | symbol _ZN4Aska12RenderThread10ReqGpuWaitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread10ReqGpuWaitEv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  int *piVar6;
  
  piVar1 = (int *)(param_1 + 0x50228);
  iVar5 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar3 = 0x1fe < iVar5;
      iVar5 = iVar5 + 1;
      if (bVar3) {
        piVar6 = (int *)(param_1 + 0x5022c);
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = *piVar6 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        do {
          if (*piVar1 != -1) {
            ClearExclusiveLocal();
            do {
              uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
              if ((uVar4 & 1) == 0) {
                do {
                  cVar2 = '\x01';
                  bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
                  if (bVar3) {
                    *piVar6 = *piVar6 + -1;
                    cVar2 = ExclusiveMonitorsStatus();
                  }
                } while (cVar2 != '\0');
                Aska::Thread::Sleep(unsigned int)(1);
              }
              else {
                Aska::Semaphore::Wait() const(param_1 + 0x50268);
              }
              do {
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
                if (bVar3) {
                  *piVar6 = *piVar6 + 1;
                  cVar2 = ExclusiveMonitorsStatus();
                }
              } while (cVar2 != '\0');
              while (*piVar1 == -1) {
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar3) {
                  *piVar1 = 0;
                  cVar2 = ExclusiveMonitorsStatus();
                }
                if (cVar2 == '\0') goto code_r0x022c4dc4;
              }
              ClearExclusiveLocal();
            } while( true );
          }
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
code_r0x022c4dc4:
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = *piVar6 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        DataMemoryBarrier(2,3);
code_r0x022c4cd8:
        piVar6 = (int *)(param_1 + 0x5022c);
        *(undefined1 *)(param_1 + 0x501d2) = 1;
        Aska::Event::Set() const(param_1 + 0x18);
        DataMemoryBarrier(2,3);
        *piVar1 = -1;
        DataMemoryBarrier(2,3);
        if (0x14 < *piVar6) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
            if (bVar3) {
              *piVar6 = *piVar6 + -1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0x50268);
          if ((uVar4 & 1) != 0) {
            (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x50268);
            return;
          }
        }
        return;
      }
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x022c4cd8;
}

// ==== Aska::RenderThread::GPUIdleCallBack(unsigned long)
// vaddr 0x21c4ddc | ghidra 0x22c4ddc | size 20 | symbol _ZN4Aska12RenderThread15GPUIdleCallBackEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread15GPUIdleCallBackEm(void)

{
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)
            (*(long *)PTR__ZN4Aska12RenderThread10m_pGPUSyncE_02cbe328 + 0x58);
  return;
}

// ==== Aska::RenderThread::FinishRenderCallBack(unsigned long)
// vaddr 0x21c4df0 | ghidra 0x22c4df0 | size 20 | symbol _ZN4Aska12RenderThread20FinishRenderCallBackEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread20FinishRenderCallBackEm(long param_1)

{
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(*(long *)(param_1 + 0x501d8) + 0x18);
  return;
}

// ==== Aska::RenderThread::RenderThreadCallBack(unsigned long)
// vaddr 0x21c4e04 | ghidra 0x22c4e04 | size 44 | symbol _ZN4Aska12RenderThread20RenderThreadCallBackEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12RenderThread20RenderThreadCallBackEm(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x501e0);
  *(ushort *)(lVar1 + 0x301a) = *(short *)(lVar1 + 0x301a) + 1U & 0x1ff;
  (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(lVar1 + 0x3020);
  return;
}


// FAILED to create function at 02c54048 Aska::RenderContextServer::vtable
// FAILED to create function at 02c54068 Aska::RenderContextServer::typeinfo
// FAILED to create function at 02c543a8 Aska::RenderThread::vtable
// FAILED to create function at 02c54480 Aska::RenderThread::typeinfo
// FAILED to create function at 02e10d38 Aska::RenderThread::m_pGPUSync
