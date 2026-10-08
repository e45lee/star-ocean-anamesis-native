// port/decomp/particles/manager.c: Ghidra decompiles for the particles subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 13:19 UTC: tools/decomp.sh '--into' 'particles/manager' 'Aska::ParticleManager::'

// ==== Aska::ParticleManager::ParticleManager()
// vaddr 0x2197504 | ghidra 0x2297504 | size 212 | symbol _ZN4Aska15ParticleManagerC2Ev | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleManagerC1Ev(long *param_1)

{
  long lVar1;
  long lVar2;
  undefined *puVar3;
  
  Aska::TaskManager::TaskManager()();
  puVar3 = PTR__ZTVN4Aska15ParticleManagerE_02cbfd08;
  *(undefined4 *)(param_1 + 0x1ff) = 0;
  *param_1 = (long)(puVar3 + 0x10);
  param_1[5] = (long)(puVar3 + 200);
  param_1[0x1fe] = (long)(puVar3 + 0x170);
  Aska::CriticalSection::CriticalSection()((long)param_1 + 0xffc);
  Aska::Event::Event()(param_1 + 0x206);
  *(undefined4 *)(param_1 + 0x213) = 0;
  puVar3 = PTR__ZTVN4Aska15ParticleManager21ParticleDeleteHandlerE_02cbf960;
  lVar2 = _UNK_0285f1f8;
  lVar1 = _UNK_0285f1f0;
  param_1[0x214] = (long)(PTR__ZTVN4Aska18ParticleMakeMatrixE_02cc3068 + 0x10);
  param_1[0x217] = (long)(puVar3 + 0x10);
  param_1[0x216] = lVar2;
  param_1[0x215] = lVar1;
  Aska::Event::Create(bool, bool)(param_1 + 0x206,1,1);
  param_1[0x219] = 0;
  param_1[0x21b] = 0;
  puVar3 = PTR__ZN4Aska15ParticleManager25m_nTaskLevelForMakeMatrixE_02cc2a90;
  param_1[0x218] = (long)(param_1 + 0x21c);
  param_1[0x21a] = (long)(param_1 + 0xa1c);
  *(undefined1 *)(param_1 + 0x121c) = 0;
  *(undefined4 *)puVar3 = 0x10;
  return;
}

// ==== Aska::ParticleManager::~ParticleManager()
// vaddr 0x21975d8 | ghidra 0x22975d8 | size 128 | symbol _ZN4Aska15ParticleManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManagerD2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  long *plVar4;
  
  puVar3 = PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108;
  puVar1 = PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 200;
  puVar2 = PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 0x170;
  *param_1 = (long)(PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 0x10);
  param_1[5] = (long)puVar1;
  param_1[0x1fe] = (long)puVar2;
  plVar4 = (long *)param_1[0x205];
  if (*(long **)puVar3 == plVar4) {
    *(undefined8 *)puVar3 = 0;
  }
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 8))();
    param_1[0x205] = 0;
  }
  Aska::Event::Exit()(param_1 + 0x206);
  Aska::CriticalSection::~CriticalSection()((long)param_1 + 0xffc);
  (*(code *)PTR__ZN4Aska11TaskManagerD2Ev_02ca45c0)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::ParticleManager::~ParticleManager()
// vaddr 0x2197658 | ghidra 0x2297658 | size 140 | symbol _ZThn40_N4Aska15ParticleManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn40_N4Aska15ParticleManagerD1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  long *plVar4;
  
  puVar3 = PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108;
  puVar1 = PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 200;
  puVar2 = PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 0x170;
  param_1[-5] = (long)(PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 0x10);
  *param_1 = (long)puVar1;
  param_1[0x1f9] = (long)puVar2;
  plVar4 = (long *)param_1[0x200];
  if (*(long **)puVar3 == plVar4) {
    *(undefined8 *)puVar3 = 0;
  }
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 8))();
    param_1[0x200] = 0;
  }
  Aska::Event::Exit()(param_1 + 0x201);
  Aska::CriticalSection::~CriticalSection()((long)param_1 + 0xfd4);
  (*(code *)PTR__ZN4Aska11TaskManagerD2Ev_02ca45c0)(param_1 + -5);
  return;
}

// ==== non-virtual thunk to Aska::ParticleManager::~ParticleManager()
// vaddr 0x21976e4 | ghidra 0x22976e4 | size 140 | symbol _ZThn4080_N4Aska15ParticleManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn4080_N4Aska15ParticleManagerD1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  long *plVar4;
  
  puVar3 = PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108;
  puVar1 = PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 200;
  puVar2 = PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 0x170;
  param_1[-0x1fe] = (long)(PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 0x10);
  param_1[-0x1f9] = (long)puVar1;
  *param_1 = (long)puVar2;
  plVar4 = (long *)param_1[7];
  if (*(long **)puVar3 == plVar4) {
    *(undefined8 *)puVar3 = 0;
  }
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 8))();
    param_1[7] = 0;
  }
  Aska::Event::Exit()(param_1 + 8);
  Aska::CriticalSection::~CriticalSection()((long)param_1 + 0xc);
  (*(code *)PTR__ZN4Aska11TaskManagerD2Ev_02ca45c0)(param_1 + -0x1fe);
  return;
}

// ==== Aska::ParticleManager::~ParticleManager()
// vaddr 0x2197770 | ghidra 0x2297770 | size 136 | symbol _ZN4Aska15ParticleManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManagerD0Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  long *plVar4;
  
  puVar3 = PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108;
  puVar1 = PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 200;
  puVar2 = PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 0x170;
  *param_1 = (long)(PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 0x10);
  param_1[5] = (long)puVar1;
  param_1[0x1fe] = (long)puVar2;
  plVar4 = (long *)param_1[0x205];
  if (*(long **)puVar3 == plVar4) {
    *(undefined8 *)puVar3 = 0;
  }
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 8))();
    param_1[0x205] = 0;
  }
  Aska::Event::Exit()(param_1 + 0x206);
  Aska::CriticalSection::~CriticalSection()((long)param_1 + 0xffc);
  Aska::TaskManager::~TaskManager()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::ParticleManager::~ParticleManager()
// vaddr 0x21977f8 | ghidra 0x22977f8 | size 148 | symbol _ZThn40_N4Aska15ParticleManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn40_N4Aska15ParticleManagerD0Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  long *plVar4;
  long *plVar5;
  
  puVar3 = PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108;
  puVar1 = PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 200;
  puVar2 = PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 0x170;
  plVar5 = param_1 + -5;
  *plVar5 = (long)(PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 0x10);
  *param_1 = (long)puVar1;
  param_1[0x1f9] = (long)puVar2;
  plVar4 = (long *)param_1[0x200];
  if (*(long **)puVar3 == plVar4) {
    *(undefined8 *)puVar3 = 0;
  }
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 8))();
    param_1[0x200] = 0;
  }
  Aska::Event::Exit()(param_1 + 0x201);
  Aska::CriticalSection::~CriticalSection()((long)param_1 + 0xfd4);
  Aska::TaskManager::~TaskManager()(plVar5);
  (*(code *)PTR__ZdlPv_02ca4758)(plVar5);
  return;
}

// ==== non-virtual thunk to Aska::ParticleManager::~ParticleManager()
// vaddr 0x219788c | ghidra 0x229788c | size 148 | symbol _ZThn4080_N4Aska15ParticleManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn4080_N4Aska15ParticleManagerD0Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  long *plVar4;
  long *plVar5;
  
  puVar3 = PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108;
  plVar5 = param_1 + -0x1fe;
  puVar1 = PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 200;
  puVar2 = PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 0x170;
  *plVar5 = (long)(PTR__ZTVN4Aska15ParticleManagerE_02cbfd08 + 0x10);
  param_1[-0x1f9] = (long)puVar1;
  *param_1 = (long)puVar2;
  plVar4 = (long *)param_1[7];
  if (*(long **)puVar3 == plVar4) {
    *(undefined8 *)puVar3 = 0;
  }
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 8))();
    param_1[7] = 0;
  }
  Aska::Event::Exit()(param_1 + 8);
  Aska::CriticalSection::~CriticalSection()((long)param_1 + 0xc);
  Aska::TaskManager::~TaskManager()(plVar5);
  (*(code *)PTR__ZdlPv_02ca4758)(plVar5);
  return;
}

// ==== Aska::ParticleManager::Init()
// vaddr 0x2197920 | ghidra 0x2297920 | size 120 | symbol _ZN4Aska15ParticleManager4InitEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager4InitEv(long param_1)

{
  long *plVar1;
  
  plVar1 = (long *)operator new(unsigned long, unsigned long, bool)(0x14570,0x10,1);
  if (plVar1 == (long *)0x0) {
    *(undefined8 *)(param_1 + 0x1028) = 0;
  }
  else {
    Aska::ParticleRenderManager::ParticleRenderManager()(plVar1);
    *(long **)(param_1 + 0x1028) = plVar1;
    (**(code **)(*plVar1 + 0x18))(plVar1);
  }
  *(undefined8 *)PTR__ZN4Aska6Global24m_pParticleRenderManagerE_02cc0108 =
       *(undefined8 *)(param_1 + 0x1028);
  return;
}

// ==== Aska::ParticleManager::GetClassID(int) const
// vaddr 0x2197998 | ghidra 0x2297998 | size 60 | symbol _ZNK4Aska15ParticleManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska15ParticleManager10GetClassIDEi(undefined8 param_1,int param_2)

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
  return 0xf01b;
}

// ==== non-virtual thunk to Aska::ParticleManager::GetClassID(int) const
// vaddr 0x21979d4 | ghidra 0x22979d4 | size 60 | symbol _ZThn40_NK4Aska15ParticleManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZThn40_NK4Aska15ParticleManager10GetClassIDEi(undefined8 param_1,int param_2)

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
  return 0xf01b;
}

// ==== Aska::ParticleManager::GetDefaultLevel() const
// vaddr 0x2197a10 | ghidra 0x2297a10 | size 12 | symbol _ZNK4Aska15ParticleManager15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska15ParticleManager15GetDefaultLevelEv(void)

{
  return 0x10004000;
}

// ==== non-virtual thunk to Aska::ParticleManager::GetDefaultLevel() const
// vaddr 0x2197a1c | ghidra 0x2297a1c | size 12 | symbol _ZThn40_NK4Aska15ParticleManager15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZThn40_NK4Aska15ParticleManager15GetDefaultLevelEv(void)

{
  return 0x10004000;
}

// ==== Aska::ParticleManager::PreAllocateBuffers()
// vaddr 0x2197a28 | ghidra 0x2297a28 | size 16 | symbol _ZN4Aska15ParticleManager18PreAllocateBuffersEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager18PreAllocateBuffersEv(long param_1)

{
                    /* WARNING: Could not recover jumptable at 0x02297a34. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(param_1 + 0x1028) + 0x58))();
  return;
}

// ==== Aska::ParticleManager::ReleaseBuffers()
// vaddr 0x2197a38 | ghidra 0x2297a38 | size 16 | symbol _ZN4Aska15ParticleManager14ReleaseBuffersEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager14ReleaseBuffersEv(long param_1)

{
                    /* WARNING: Could not recover jumptable at 0x02297a44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(param_1 + 0x1028) + 0x30))();
  return;
}

// ==== Aska::ParticleManager::Add(Aska::AnimatableLinkElement*)
// vaddr 0x2197a48 | ghidra 0x2297a48 | size 76 | symbol _ZN4Aska15ParticleManager3AddEPNS_21AnimatableLinkElementE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager3AddEPNS_21AnimatableLinkElementE(long param_1,long param_2)

{
  long lVar1;
  
  Aska::CriticalSection::Enter() const(param_1 + 0xffc);
  lVar1 = *(long *)(param_1 + 0x10);
  *(long *)(param_2 + 8) = lVar1;
  *(long *)(param_2 + 0x10) = param_1 + 8;
  *(long *)(param_1 + 0x10) = param_2;
  *(long *)(lVar1 + 0x10) = param_2;
  *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;
  (*(code *)PTR__ZNK4Aska15CriticalSection5LeaveEv_02ca8d00)(param_1 + 0xffc);
  return;
}

// ==== Aska::ParticleManager::Delete(Aska::AnimatableLinkElement*)
// vaddr 0x2197a94 | ghidra 0x2297a94 | size 104 | symbol _ZN4Aska15ParticleManager6DeleteEPNS_21AnimatableLinkElementE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager6DeleteEPNS_21AnimatableLinkElementE(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  Aska::CriticalSection::Enter() const(param_1 + 0xffc);
  if ((param_1 + 8 != param_2) && (param_2 != 0)) {
    lVar1 = *(long *)(param_2 + 8);
    lVar2 = *(long *)(param_2 + 0x10);
    if (lVar1 != 0) {
      *(long *)(lVar1 + 0x10) = lVar2;
    }
    if (lVar2 != 0) {
      *(long *)(lVar2 + 8) = lVar1;
    }
    if (0 < *(int *)(param_1 + 0x20)) {
      *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + -1;
    }
    *(long *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = 0;
  }
  (*(code *)PTR__ZNK4Aska15CriticalSection5LeaveEv_02ca8d00)(param_1 + 0xffc);
  return;
}

// ==== Aska::ParticleManager::Run(int)
// vaddr 0x2197afc | ghidra 0x2297afc | size 28 | symbol _ZN4Aska15ParticleManager3RunEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager3RunEi(undefined8 param_1,int param_2)

{
  if (param_2 == 0x1c) {
    (*(code *)PTR__ZN4Aska15ParticleManager17RunAfterRenderingEv_02ca7908)();
    return;
  }
  if (param_2 == 0xe) {
    (*(code *)PTR__ZN4Aska15ParticleManager6RunLowEv_02c8f5e8)();
    return;
  }
  return;
}

// ==== Aska::ParticleManager::RunLow()
// vaddr 0x2197b18 | ghidra 0x2297b18 | size 700 | symbol _ZN4Aska15ParticleManager6RunLowEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager6RunLowEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  int *piVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  long *plVar9;
  undefined8 uVar10;
  float fVar11;
  
  fVar11 = (float)(**(code **)**(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460)
                            (*(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460,0);
  *(float *)(param_1 + 0xff8) = fVar11 + *(float *)(param_1 + 0xff8);
  if (*(int *)(param_1 + 0x1098) < 1) {
    lVar7 = *(long *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
    Aska::CriticalSection::Enter() const(param_1 + 0xffc);
    plVar1 = (long *)(param_1 + 8);
    for (plVar9 = *(long **)(param_1 + 0x18); plVar1 != plVar9; plVar9 = (long *)plVar9[2]) {
      if ((*(byte *)((long)plVar9 + 0x214) & 1) != 0) {
        (**(code **)(*plVar9 + 0x168))(plVar9);
      }
    }
    *(undefined8 *)(param_1 + 0x10c8) = 0;
    *(undefined8 *)(param_1 + 0x10d8) = 0;
    if ((*(int *)(param_1 + 0x20) != 0) && (plVar9 = *(long **)(param_1 + 0x18), plVar1 != plVar9))
    {
      do {
        if (((*(byte *)((long)plVar9 + 0x214) & 1) != 0) &&
           (((uVar6 = Aska::IParticleEmitter::SkipThisFrame() const(plVar9), (uVar6 & 1) == 0 &&
             (*(char *)((long)plVar9 + 0x213) == '\0')) && ((char)plVar9[0x42] == '\0')))) {
          if (0x7ff < *(ulong *)(param_1 + 0x10c8)) break;
          *(long **)(*(long *)(param_1 + 0x10c0) + *(ulong *)(param_1 + 0x10c8) * 8) = plVar9;
          *(long *)(param_1 + 0x10c8) = *(long *)(param_1 + 0x10c8) + 1;
        }
        plVar9 = (long *)plVar9[2];
      } while (plVar1 != plVar9);
      plVar9 = *(long **)(param_1 + 0x18);
      if (plVar1 != plVar9) {
        piVar3 = (int *)(param_1 + 0x1098);
        do {
          if ((((*(byte *)((long)plVar9 + 0x214) & 1) != 0) &&
              (uVar6 = Aska::IParticleEmitter::SkipThisFrame() const(plVar9), (uVar6 & 1) == 0)) &&
             ((*(char *)((long)plVar9 + 0x213) == '\0' && (*(char *)((long)plVar9 + 0x20f) == '\0'))
             )) {
            if (0x7ff < *(ulong *)(param_1 + 0x10d8)) break;
            uVar6 = Aska::ParticleRenderableBase::IsBufferReady() const(plVar9[0x38]);
            if ((uVar6 & 1) == 0) {
              *(undefined1 *)((long)plVar9 + 0x213) = 1;
              *(undefined1 *)(param_1 + 0x90e0) = 1;
            }
            else {
              plVar2 = plVar9 + 0x34;
              do {
                if ((int)*plVar2 != 0) {
                  ClearExclusiveLocal();
                  goto code_r0x02297d0c;
                }
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(plVar2,0x10);
                if (bVar5) {
                  *(int *)plVar2 = 1;
                  cVar4 = ExclusiveMonitorsStatus();
                }
              } while (cVar4 != '\0');
              *(undefined1 *)((long)plVar9 + 0x19c) = 0;
              *(long **)(*(long *)(param_1 + 0x10d0) + *(long *)(param_1 + 0x10d8) * 8) = plVar9;
              *(long *)(param_1 + 0x10d8) = *(long *)(param_1 + 0x10d8) + 1;
              *(undefined1 *)((long)plVar9 + 0x213) = 0;
              do {
                cVar4 = '\x01';
                bVar5 = (bool)ExclusiveMonitorPass(piVar3,0x10);
                if (bVar5) {
                  *piVar3 = *piVar3 + 1;
                  cVar4 = ExclusiveMonitorsStatus();
                }
              } while (cVar4 != '\0');
            }
          }
code_r0x02297d0c:
          plVar9 = (long *)plVar9[2];
        } while (plVar1 != plVar9);
      }
    }
    Aska::CriticalSection::Leave() const(param_1 + 0xffc);
    lVar8 = *(long *)(param_1 + 0x10c8);
    if (lVar8 == 0) {
      if (*(long *)(param_1 + 0x10d8) != 0) {
        (*(code *)PTR__ZN4Aska15ParticleManager16DispatchEmittersEv_02ca7c90)(param_1);
        return;
      }
    }
    else {
      uVar10 = *(undefined8 *)(param_1 + 0x10c0);
      uVar6 = Aska::SimpleMessageDispatcher::PostMessage(Aska::Task*, int, unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(lVar7,param_1 + 0x28,0x10,0x299,param_1 + 0x10a0,uVar10,lVar8,0,0,0,0)
      ;
      if ((uVar6 & 1) == 0) {
        do {
          Aska::Event::Wait(unsigned int) const(lVar7 + 0x148,0);
          uVar6 = Aska::SimpleMessageDispatcher::PostMessage(Aska::Task*, int, unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(lVar7,param_1 + 0x28,0x10,0x299,param_1 + 0x10a0,uVar10,lVar8,0,0,
                                  0,0);
        } while ((uVar6 & 1) == 0);
      }
    }
  }
  return;
}

// ==== Aska::ParticleManager::RunAfterRendering()
// vaddr 0x2197dd4 | ghidra 0x2297dd4 | size 380 | symbol _ZN4Aska15ParticleManager17RunAfterRenderingEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager17RunAfterRenderingEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  undefined4 uVar3;
  char cVar4;
  bool bVar5;
  undefined *puVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  undefined4 uStack_54;
  
  *(undefined4 *)(param_1 + 0x10b0 + (ulong)*(uint *)(param_1 + 0x10b4) * 4) =
       *(undefined4 *)(param_1 + 0x10a8);
  uVar3 = *(undefined4 *)(param_1 + 0x10b0);
  *(undefined8 *)(param_1 + 0x10b0) = 0;
  *(undefined4 *)(param_1 + 0x10ac) = uVar3;
  Aska::CriticalSection::Enter() const(param_1 + 0xffc);
  puVar6 = PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
  if (*(char *)(param_1 + 0x90e0) != '\0') {
    lVar8 = *(long *)(param_1 + 0x18);
    if (param_1 + 8 != lVar8) {
      piVar2 = (int *)(param_1 + 0x1098);
code_r0x02297e58:
      if (*(char *)(lVar8 + 0x213) != '\0') {
        *(undefined1 *)(lVar8 + 0x213) = 0;
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = *piVar2 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        lVar9 = *(long *)puVar6;
        piVar1 = (int *)(lVar8 + 0x1a0);
code_r0x02297e7c:
        if (*piVar1 == 0) goto code_r0x02297e84;
        ClearExclusiveLocal();
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = *piVar2 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
      }
      goto code_r0x02297f18;
    }
code_r0x02297f24:
    *(char *)(param_1 + 0x90e0) = '\0';
  }
  Aska::CriticalSection::Leave() const(param_1 + 0xffc);
  return;
code_r0x02297e84:
  cVar4 = '\x01';
  bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
  if (bVar5) {
    *piVar1 = 1;
    cVar4 = ExclusiveMonitorsStatus();
  }
  if (cVar4 == '\0') goto code_r0x02297e8c;
  goto code_r0x02297e7c;
code_r0x02297e8c:
  *(undefined1 *)(lVar8 + 0x19c) = 0;
  uVar7 = Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(lVar9,0x29a,param_1 + 0xff0,lVar8,0,*(undefined8 *)(lVar8 + 0x1a8),0,
                          &uStack_54,0);
  if ((uVar7 & 1) == 0) {
    do {
      Aska::Event::Wait(unsigned int) const(lVar9 + 0x148,0);
      uVar7 = Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(lVar9,0x29a,param_1 + 0xff0,lVar8,0,*(undefined8 *)(lVar8 + 0x1a8),0,
                              &uStack_54,0);
    } while ((uVar7 & 1) == 0);
  }
  *(undefined4 *)(lVar8 + 0x1b0) = uStack_54;
code_r0x02297f18:
  lVar8 = *(long *)(lVar8 + 0x10);
  if (param_1 + 8 == lVar8) goto code_r0x02297f24;
  goto code_r0x02297e58;
}

// ==== non-virtual thunk to Aska::ParticleManager::Run(int)
// vaddr 0x2197f50 | ghidra 0x2297f50 | size 32 | symbol _ZThn40_N4Aska15ParticleManager3RunEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn40_N4Aska15ParticleManager3RunEi(long param_1,int param_2)

{
  if (param_2 == 0x1c) {
    (*(code *)PTR__ZN4Aska15ParticleManager17RunAfterRenderingEv_02ca7908)(param_1 + -0x28);
    return;
  }
  if (param_2 == 0xe) {
    (*(code *)PTR__ZN4Aska15ParticleManager6RunLowEv_02c8f5e8)();
    return;
  }
  return;
}

// ==== Aska::ParticleManager::DispatchEmitters()
// vaddr 0x2197f70 | ghidra 0x2297f70 | size 384 | symbol _ZN4Aska15ParticleManager16DispatchEmittersEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska15ParticleManager16DispatchEmittersEv(long param_1)

{
  int iVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  int iVar8;
  
  uVar5 = *(ulong *)(param_1 + 0x10d8);
  if (uVar5 != 0) {
    lVar4 = *(long *)(param_1 + 0x10d0);
    lVar3 = *(long *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
    iVar1 = *(int *)(lVar3 + 0x1b8);
    if (1 < iVar1) {
      lVar7 = 0;
      uVar6 = 0;
      if ((long)iVar1 != 0) {
        uVar6 = uVar5 / (ulong)(long)iVar1;
      }
      iVar2 = iVar1 + -1;
      iVar8 = 0;
      do {
        if (uVar6 == 0) {
          do {
            if (iVar1 <= iVar8) {
              return 1;
            }
            iVar8 = iVar8 + 1;
          } while (iVar2 != iVar8);
        }
        else {
          do {
            if (iVar1 <= iVar8) {
              return 1;
            }
            while (uVar5 = Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(lVar3,iVar8 + 0x29a,param_1 + 0xff0,lVar4,uVar6,0,0,0,0),
                  (uVar5 & 1) == 0) {
              Aska::Event::Wait(unsigned int) const(lVar3 + 0x148,0);
            }
            iVar8 = iVar8 + 1;
            lVar4 = lVar4 + uVar6 * 8;
            lVar7 = lVar7 + uVar6;
          } while (iVar8 != iVar2);
          uVar5 = *(ulong *)(param_1 + 0x10d8);
        }
        uVar6 = uVar5 - lVar7;
        iVar8 = iVar2;
      } while( true );
    }
    uVar6 = Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(lVar3,0x29a,param_1 + 0xff0,lVar4,uVar5,0,0,0,0);
    if ((uVar6 & 1) == 0) {
      do {
        Aska::Event::Wait(unsigned int) const(lVar3 + 0x148,0);
        uVar6 = Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(lVar3,0x29a,param_1 + 0xff0,lVar4,uVar5,0,0,0,0);
      } while ((uVar6 & 1) == 0);
    }
  }
  return 1;
}

// ==== Aska::ParticleManager::DispatchEmitter(Aska::IParticleEmitter*, bool)
// vaddr 0x21980f0 | ghidra 0x22980f0 | size 252 | symbol _ZN4Aska15ParticleManager15DispatchEmitterEPNS_16IParticleEmitterEb | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska15ParticleManager15DispatchEmitterEPNS_16IParticleEmitterEb
          (long param_1,long param_2,ulong param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  long lVar5;
  undefined4 uStack_34;
  
  piVar1 = (int *)(param_2 + 0x1a0);
  lVar5 = *(long *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
  do {
    if (*piVar1 != 0) goto code_r0x022981d0;
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  *(undefined1 *)(param_2 + 0x19c) = 0;
  uVar4 = Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(lVar5,0x29a,param_1 + 0xff0,param_2,0,*(undefined8 *)(param_2 + 0x1a8),0,
                          &uStack_34,0);
  if ((uVar4 & 1) == 0) {
    if ((param_3 & 1) == 0) {
      *(undefined1 *)(param_2 + 0x19c) = 1;
      while (*piVar1 == 1) {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar3) {
          *piVar1 = 0;
          cVar2 = ExclusiveMonitorsStatus();
        }
        if (cVar2 == '\0') {
          return 0;
        }
      }
code_r0x022981d0:
      ClearExclusiveLocal();
      return 0;
    }
    do {
      Aska::Event::Wait(unsigned int) const(lVar5 + 0x148,0);
      uVar4 = Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(lVar5,0x29a,param_1 + 0xff0,param_2,0,*(undefined8 *)(param_2 + 0x1a8)
                              ,0,&uStack_34,0);
    } while ((uVar4 & 1) == 0);
  }
  *(undefined4 *)(param_2 + 0x1b0) = uStack_34;
  return 1;
}

// ==== Aska::ParticleManager::Kick(Aska::IParticleEmitter*)
// vaddr 0x21981ec | ghidra 0x22981ec | size 424 | symbol _ZN4Aska15ParticleManager4KickEPNS_16IParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager4KickEPNS_16IParticleEmitterE(long param_1,long *param_2)

{
  long *plVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  undefined *puVar5;
  undefined *puVar6;
  ulong uVar7;
  long lVar8;
  ulong in_stack_ffffffffffffff90;
  undefined4 uStack_54;
  
  (**(code **)(*param_2 + 0x168))(param_2);
  puVar5 = PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
  piVar2 = (int *)(param_1 + 0x1098);
  lVar8 = *(long *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
    puVar6 = PTR__ZN4Aska15ParticleManager25m_nTaskLevelForMakeMatrixE_02cc2a90;
  } while (cVar3 != '\0');
  if ((char)param_2[0x42] == '\0') {
    in_stack_ffffffffffffff90 = 0;
    uVar7 = Aska::SimpleMessageDispatcher::PostMessage(Aska::Task*, int, unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(lVar8,param_1 + 0x28,
                            *(undefined4 *)
                             PTR__ZN4Aska15ParticleManager25m_nTaskLevelForMakeMatrixE_02cc2a90,
                            0x299,param_1 + 0x10a0,param_2,0,param_2[0x35],0,0,0);
    if ((uVar7 & 1) == 0) {
      do {
        Aska::Event::Wait(unsigned int) const(lVar8 + 0x148,0);
        in_stack_ffffffffffffff90 = 0;
        uVar7 = Aska::SimpleMessageDispatcher::PostMessage(Aska::Task*, int, unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(lVar8,param_1 + 0x28,*(undefined4 *)puVar6,0x299,param_1 + 0x10a0,
                                param_2,0,param_2[0x35],0,0,0);
      } while ((uVar7 & 1) == 0);
    }
  }
  lVar8 = *(long *)puVar5;
  plVar1 = param_2 + 0x34;
  do {
    if ((int)*plVar1 != 0) {
      ClearExclusiveLocal();
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar4) {
          *piVar2 = *piVar2 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      return;
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar4) {
      *(int *)plVar1 = 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  *(undefined1 *)((long)param_2 + 0x19c) = 0;
  in_stack_ffffffffffffff90 = in_stack_ffffffffffffff90 & 0xffffffffffffff00;
  uVar7 = Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(lVar8,0x29a,param_1 + 0xff0,param_2,0,param_2[0x35],0,&uStack_54,
                          in_stack_ffffffffffffff90);
  if ((uVar7 & 1) == 0) {
    do {
      Aska::Event::Wait(unsigned int) const(lVar8 + 0x148,0);
      in_stack_ffffffffffffff90 = in_stack_ffffffffffffff90 & 0xffffffffffffff00;
      uVar7 = Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(lVar8,0x29a,param_1 + 0xff0,param_2,0,param_2[0x35],0,&uStack_54,
                              in_stack_ffffffffffffff90);
    } while ((uVar7 & 1) == 0);
  }
  *(undefined4 *)(param_2 + 0x36) = uStack_54;
  return;
}

// ==== Aska::ParticleManager::Tick(Aska::IParticleEmitter*, float)
// vaddr 0x2198394 | ghidra 0x2298394 | size 52 | symbol _ZN4Aska15ParticleManager4TickEPNS_16IParticleEmitterEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager4TickEPNS_16IParticleEmitterEf(undefined8 param_1,long *param_2)

{
  long *plVar1;
  char cVar2;
  bool bVar3;
  
  plVar1 = param_2 + 0x34;
  do {
    if ((int)*plVar1 != 0) {
      ClearExclusiveLocal();
      return;
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(plVar1,0x10);
    if (bVar3) {
      *(int *)plVar1 = 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  *(undefined1 *)((long)param_2 + 0x19c) = 0;
                    /* WARNING: Could not recover jumptable at 0x022983bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_2 + 0x198))(param_2);
  return;
}

// ==== Aska::ParticleManager::Handler(unsigned long)
// vaddr 0x21983c8 | ghidra 0x22983c8 | size 328 | symbol _ZN4Aska15ParticleManager7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15ParticleManager7HandlerEm(long param_1,long param_2)

{
  long *plVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  long *plVar5;
  ulong uVar6;
  ulong uVar7;
  long lVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  
  fVar10 = _UNK_027f7c94;
  uVar6 = *(ulong *)(param_2 + 0x38);
  if (uVar6 == 0) {
    plVar5 = *(long **)(param_2 + 0x30);
    *(undefined4 *)(plVar5 + 0x36) = 0xffffffff;
    fVar10 = *(float *)(param_1 + 0xff8);
    fVar9 = *(float *)(plVar5 + 0x41);
    *(float *)(plVar5 + 0x41) = fVar10;
    fVar10 = fVar10 - fVar9;
    if (_UNK_027f7c94 < fVar10) {
      fVar10 = _UNK_027f7c94;
    }
    (**(code **)(*plVar5 + 0x198))(fVar10,plVar5);
    *(undefined1 *)((long)plVar5 + 0x19c) = 1;
    plVar5 = plVar5 + 0x34;
    do {
      if ((int)*plVar5 != 1) {
        ClearExclusiveLocal();
        break;
      }
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(plVar5,0x10);
      if (bVar4) {
        *(int *)plVar5 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    piVar2 = (int *)(param_1 + 0x1098);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar4) {
        *piVar2 = *piVar2 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
  else {
    lVar8 = *(long *)(param_2 + 0x30);
    uVar7 = 0;
    piVar2 = (int *)(param_1 + 0x1098);
    do {
      plVar5 = *(long **)(lVar8 + uVar7 * 8);
      *(undefined4 *)(plVar5 + 0x36) = 0xffffffff;
      fVar9 = *(float *)(param_1 + 0xff8);
      fVar11 = *(float *)(plVar5 + 0x41);
      *(float *)(plVar5 + 0x41) = fVar9;
      fVar9 = fVar9 - fVar11;
      if (fVar10 < fVar9) {
        fVar9 = fVar10;
      }
      (**(code **)(*plVar5 + 0x198))(fVar9,plVar5);
      plVar1 = plVar5 + 0x34;
      *(undefined1 *)((long)plVar5 + 0x19c) = 1;
      do {
        if ((int)*plVar1 != 1) {
          ClearExclusiveLocal();
          break;
        }
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(plVar1,0x10);
        if (bVar4) {
          *(int *)plVar1 = 0;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar4) {
          *piVar2 = *piVar2 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = uVar7 + 1;
    } while (uVar7 < uVar6);
  }
  return;
}

// ==== non-virtual thunk to Aska::ParticleManager::Handler(unsigned long)
// vaddr 0x2198510 | ghidra 0x2298510 | size 320 | symbol _ZThn4080_N4Aska15ParticleManager7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZThn4080_N4Aska15ParticleManager7HandlerEm(long param_1,long param_2)

{
  int *piVar1;
  long *plVar2;
  char cVar3;
  bool bVar4;
  long *plVar5;
  ulong uVar6;
  ulong uVar7;
  long lVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  
  fVar10 = _UNK_027f7c94;
  uVar6 = *(ulong *)(param_2 + 0x38);
  if (uVar6 == 0) {
    plVar5 = *(long **)(param_2 + 0x30);
    *(undefined4 *)(plVar5 + 0x36) = 0xffffffff;
    fVar10 = *(float *)(param_1 + 8);
    fVar9 = *(float *)(plVar5 + 0x41);
    *(float *)(plVar5 + 0x41) = fVar10;
    fVar10 = fVar10 - fVar9;
    if (_UNK_027f7c94 < fVar10) {
      fVar10 = _UNK_027f7c94;
    }
    (**(code **)(*plVar5 + 0x198))(fVar10,plVar5);
    *(undefined1 *)((long)plVar5 + 0x19c) = 1;
    plVar5 = plVar5 + 0x34;
    do {
      if ((int)*plVar5 != 1) {
        ClearExclusiveLocal();
        break;
      }
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(plVar5,0x10);
      if (bVar4) {
        *(int *)plVar5 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    piVar1 = (int *)(param_1 + 0xa8);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
  else {
    lVar8 = *(long *)(param_2 + 0x30);
    uVar7 = 0;
    piVar1 = (int *)(param_1 + 0xa8);
    do {
      plVar5 = *(long **)(lVar8 + uVar7 * 8);
      *(undefined4 *)(plVar5 + 0x36) = 0xffffffff;
      fVar9 = *(float *)(param_1 + 8);
      fVar11 = *(float *)(plVar5 + 0x41);
      *(float *)(plVar5 + 0x41) = fVar9;
      fVar9 = fVar9 - fVar11;
      if (fVar10 < fVar9) {
        fVar9 = fVar10;
      }
      (**(code **)(*plVar5 + 0x198))(fVar9,plVar5);
      plVar2 = plVar5 + 0x34;
      *(undefined1 *)((long)plVar5 + 0x19c) = 1;
      do {
        if ((int)*plVar2 != 1) {
          ClearExclusiveLocal();
          break;
        }
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(plVar2,0x10);
        if (bVar4) {
          *(int *)plVar2 = 0;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar4) {
          *piVar1 = *piVar1 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      uVar7 = uVar7 + 1;
    } while (uVar7 < uVar6);
  }
  return;
}

// ==== Aska::ParticleManager::DeleteEmitter(Aska::IParticleEmitter*)
// vaddr 0x21986a4 | ghidra 0x22986a4 | size 144 | symbol _ZN4Aska15ParticleManager13DeleteEmitterEPNS_16IParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager13DeleteEmitterEPNS_16IParticleEmitterE(long param_1,long param_2)

{
  undefined *puVar1;
  ulong uVar2;
  ushort uVar3;
  
  Aska::CriticalSection::Enter() const(param_1 + 0xffc);
  Aska::Task::Remove()(param_2);
  Aska::CriticalSection::Leave() const(param_1 + 0xffc);
  uVar2 = Aska::IParticleEmitter::DetachRenderableForRender()(param_2);
  puVar1 = PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0;
  if ((uVar2 & 1) == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = *(ushort *)(*(long *)(param_2 + 0x1c0) + 0x1b5) >> 3 & 1;
  }
  *(undefined1 *)(param_2 + 0x213) = 0;
  (*(code *)PTR__ZN4Aska13DeleteManager7AddMainEPvhhPNS_14IDeleteHandlerE_02c9d0d8)
            (puVar1,param_2,0,uVar3,param_1 + 0x10b8);
  return;
}

// ==== Aska::ParticleManager::Get(unsigned long, void*) const
// vaddr 0x2198734 | ghidra 0x2298734 | size 32 | symbol _ZNK4Aska15ParticleManager3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska15ParticleManager3GetEmPv(undefined8 param_1,ulong param_2,undefined1 *param_3)

{
  if ((param_2 & 0xffff0000ffff) == 9) {
    *param_3 = 1;
    return 1;
  }
  return 0;
}

// ==== non-virtual thunk to Aska::ParticleManager::Get(unsigned long, void*) const
// vaddr 0x2198754 | ghidra 0x2298754 | size 32 | symbol _ZThn40_NK4Aska15ParticleManager3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZThn40_NK4Aska15ParticleManager3GetEmPv(undefined8 param_1,ulong param_2,undefined1 *param_3)

{
  if ((param_2 & 0xffff0000ffff) == 9) {
    *param_3 = 1;
    return 1;
  }
  return 0;
}

// ==== Aska::ParticleManager::Set(unsigned long, void const*)
// vaddr 0x2198774 | ghidra 0x2298774 | size 8 | symbol _ZN4Aska15ParticleManager3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska15ParticleManager3SetEmPKv(void)

{
  return 0;
}

// ==== non-virtual thunk to Aska::ParticleManager::Set(unsigned long, void const*)
// vaddr 0x219877c | ghidra 0x229877c | size 8 | symbol _ZThn40_N4Aska15ParticleManager3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZThn40_N4Aska15ParticleManager3SetEmPKv(void)

{
  return 0;
}

// ==== Aska::ParticleManager::CreateParticle(Aska::AFF::AsfParticleEmitter const*, unsigned int)
// vaddr 0x2198784 | ghidra 0x2298784 | size 528 | symbol _ZN4Aska15ParticleManager14CreateParticleEPKNS_3AFF18AsfParticleEmitterEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager14CreateParticleEPKNS_3AFF18AsfParticleEmitterEj
               (undefined8 param_1,long param_2,uint param_3)

{
  long lVar1;
  
  if ((param_3 >> 5 & 1) != 0) {
    if ((param_3 >> 4 & 1) == 0) {
      (*(code *)PTR__Z19CreateParticle_PROGPKN4Aska3AFF18AsfParticleEmitterEj_02ca0820)
                (param_2,param_3 & 0x20);
      return;
    }
    (*(code *)PTR__Z20CreateParticle_PROGDPKN4Aska3AFF18AsfParticleEmitterEj_02ca4ee0)();
    return;
  }
  if ((param_3 >> 6 & 1) == 0) {
    if ((param_3 >> 4 & 1) == 0) {
      lVar1 = CreateParticle_MC(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
      if (lVar1 != 0xffffffff) {
        return;
      }
      lVar1 = CreateParticle_MRC(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
      if (lVar1 != 0xffffffff) {
        return;
      }
      lVar1 = CreateParticle_MCT(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
      if (lVar1 != 0xffffffff) {
        return;
      }
      lVar1 = CreateParticle_MR(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
      if (lVar1 != 0xffffffff) {
        return;
      }
      lVar1 = CreateParticle_MRT(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
      if (lVar1 != 0xffffffff) {
        return;
      }
      lVar1 = CreateParticle_MRTC(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
      if (lVar1 != 0xffffffff) {
        return;
      }
      lVar1 = CreateParticle_MT(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
      if (lVar1 != 0xffffffff) {
        return;
      }
      lVar1 = CreateParticle_M(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
    }
    else {
      lVar1 = CreateParticle_MCD(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
      if (lVar1 != 0xffffffff) {
        return;
      }
      lVar1 = CreateParticle_MRCD(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
      if (lVar1 != 0xffffffff) {
        return;
      }
      lVar1 = CreateParticle_MCTD(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
      if (lVar1 != 0xffffffff) {
        return;
      }
      lVar1 = CreateParticle_MRD(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
      if (lVar1 != 0xffffffff) {
        return;
      }
      lVar1 = CreateParticle_MRTD(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
      if (lVar1 != 0xffffffff) {
        return;
      }
      lVar1 = CreateParticle_MRTCD(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
      if (lVar1 != 0xffffffff) {
        return;
      }
      lVar1 = CreateParticle_MTD(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
      if (lVar1 != 0xffffffff) {
        return;
      }
      lVar1 = CreateParticle_MD(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
    }
  }
  else {
    lVar1 = CreateParticle_VTC(Aska::AFF::AsfParticleEmitter const*, unsigned int)(param_2,param_3);
  }
  if (lVar1 == 0xffffffff) {
    if (*(char *)(param_2 + 0x1d7) == '\0') {
      lVar1 = Aska::ParticleEmitter<Aska::StNULL>* Aska::ParticleManager::CreateParticle<Aska::StNULL>(Aska::AFF::AsfParticleEmitter const*)(param_1,param_2);
    }
    else {
      lVar1 = Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> >(Aska::AFF::AsfParticleEmitter const*)(param_1,param_2);
    }
    if (lVar1 != 0) {
      *(ushort *)(lVar1 + 0x214) = *(ushort *)(lVar1 + 0x214) | 0x100;
    }
  }
  return;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2198994 | ghidra 0x2298994 | size 412 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures9LifeLimitENS_6StNULLEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures9LifeLimitENS_6StNULLEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x330,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures9LifeLimitENS_6StNULLEEEEE_02cc3040
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,2,0x40,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures9LifeLimitENS_6StNULLEEENS_18DefaultFunctorListEEE_02cba908
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures9LifeLimitENS_6StNULLEEEEE_02cc3380
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures9LifeLimitENS_6StNULLEEEEE_02cc3380
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::StNULL>* Aska::ParticleManager::CreateParticle<Aska::StNULL>(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2198b30 | ghidra 0x2298b30 | size 400 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_6StNULLEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_6StNULLEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x330,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    *plVar2 = (long)(PTR__ZTVN4Aska15ParticleEmitterINS_6StNULLEEE_02cb6e18 + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0,0x40,0xa10);
      *plVar3 = (long)(PTR__ZTVN4Aska14ParticleObjectINS_6StNULLENS_18DefaultFunctorListEEE_02cc4808
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_6StNULLEEE_02cbb0c8 + 0x2f0;
        *plVar5 = (long)(PTR__ZTVN4Aska24ParticleRenderableObjectINS_6StNULLEEE_02cbb0c8 + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleManager::Malloc(unsigned long)
// vaddr 0x2198cc0 | ghidra 0x2298cc0 | size 52 | symbol _ZN4Aska15ParticleManager6MallocEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager6MallocEm(undefined8 param_1)

{
  if (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager13AlignedMallocEml_02cae360)
              (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838,param_1,0x10);
    return;
  }
  (*(code *)PTR__Znammb_02c9d8d8)(param_1,0x10,1);
  return;
}

// ==== Aska::ParticleManager::Free(void*)
// vaddr 0x2198cf4 | ghidra 0x2298cf4 | size 44 | symbol _ZN4Aska15ParticleManager4FreeEPv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager4FreeEPv(long param_1)

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

// ==== Aska::ParticleManager::ParticleDeleteHandler::DeleteCallback(int, void*)
// vaddr 0x2198e80 | ghidra 0x2298e80 | size 16 | symbol _ZN4Aska15ParticleManager21ParticleDeleteHandler14DeleteCallbackEiPv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager21ParticleDeleteHandler14DeleteCallbackEiPv
               (undefined8 param_1,undefined8 param_2,long *param_3)

{
                    /* WARNING: Could not recover jumptable at 0x02298e8c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_3 + 0x50))(param_3);
  return;
}

// ==== Aska::ParticleManager::ParticleDeleteHandler::CancelCallback(int, void*)
// vaddr 0x2198e90 | ghidra 0x2298e90 | size 4 | symbol _ZN4Aska15ParticleManager21ParticleDeleteHandler14CancelCallbackEiPv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager21ParticleDeleteHandler14CancelCallbackEiPv(void)

{
  return;
}

// ==== Aska::ParticleManager::ParticleDeleteHandler::~ParticleDeleteHandler()
// vaddr 0x2198e94 | ghidra 0x2298e94 | size 4 | symbol _ZN4Aska15ParticleManager21ParticleDeleteHandlerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15ParticleManager21ParticleDeleteHandlerD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x236d444 | ghidra 0x246d444 | size 452 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x380,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x66);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEE_02cbed78
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0xc3,0x70,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEENS_18DefaultFunctorListEEE_02cbcf30
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEE_02cc1f48
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEE_02cc1f48
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x236d608 | ghidra 0x246d608 | size 420 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x380,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x66);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEE_02cc42c0
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0xc2,0x70,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS_6StNULLEEEEEEENS_18DefaultFunctorListEEE_02cbd1e8
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEE_02cb6d88
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEE_02cb6d88
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x236d7ac | ghidra 0x246d7ac | size 440 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_4LineENS_6StNULLEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_4LineENS_6StNULLEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x380,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x66);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_4LineENS_6StNULLEEEEEEEEE_02cbca78
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0xc1,0x70,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_4LineENS_6StNULLEEEEEEENS_18DefaultFunctorListEEE_02cb83a0
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_4LineENS_6StNULLEEEEEEEEE_02cbd998
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_4LineENS_6StNULLEEEEEEEEE_02cbd998
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::StNULL> > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::StNULL> > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x236d964 | ghidra 0x246d964 | size 408 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS_6StNULLEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS_6StNULLEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x380,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x66);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS_6StNULLEEEEEEE_02cc3270
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0xc0,0x70,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS_6StNULLEEEEENS_18DefaultFunctorListEEE_02cbb538
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS_6StNULLEEEEEEE_02cbc3a8
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS_6StNULLEEEEEEE_02cbc3a8
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23878c8 | ghidra 0x24878c8 | size 460 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x3c0,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x6e);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cc3818
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0xd3,0x90,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc2418
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cc3970
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cc3970
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2387a94 | ghidra 0x2487a94 | size 428 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x3c0,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x6e);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEE_02cbc440
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0xd2,0x90,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEENS_18DefaultFunctorListEEE_02cbf468
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEE_02cb9558
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEE_02cb9558
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2387c40 | ghidra 0x2487c40 | size 448 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x3c0,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x6e);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEE_02cb7228
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0xd1,0x90,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEENS_18DefaultFunctorListEEE_02cbe6d8
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEE_02cb88f8
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEE_02cb88f8
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2387e00 | ghidra 0x2487e00 | size 416 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS_6StNULLEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS_6StNULLEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x3c0,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x6e);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEEE_02cbad58
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0xd0,0x90,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEENS_18DefaultFunctorListEEE_02cb7bd0
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEEE_02cc4ae8
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEEE_02cc4ae8
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23a34bc | ghidra 0x24a34bc | size 476 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x3c0,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x6e);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cc3cf0
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x2d7,0x90,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cbbcb8
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cbeff0
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cbeff0
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23a3698 | ghidra 0x24a3698 | size 444 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x3c0,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x6e);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cc4ce8
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x2d6,0x90,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cbea50
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cc0228
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cc0228
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23a3854 | ghidra 0x24a3854 | size 464 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x3c0,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x6e);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cc3c20
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x2d5,0x90,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cb8250
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cbb108
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cbb108
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23a3a24 | ghidra 0x24a3a24 | size 432 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x3c0,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x6e);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEE_02cc0888
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x2d4,0x90,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc2ec8
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEE_02cba2a0
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEE_02cba2a0
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23bfca0 | ghidra 0x24bfca0 | size 468 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x440,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x76);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x7e);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEE_02cbd7c0
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x1d3,0xd0,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cbfd68
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEE_02cb7aa8
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEE_02cb7aa8
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23bfe74 | ghidra 0x24bfe74 | size 436 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_7TextureENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_7TextureENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x440,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x76);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x7e);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEE_02cc0750
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x1d2,0xd0,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc0a80
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEE_02cc2b10
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEE_02cc2b10
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23c0028 | ghidra 0x24c0028 | size 456 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_7TextureENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_7TextureENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x440,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x76);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x7e);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cbd608
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x1d1,0xd0,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc2060
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cb6d38
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cb6d38
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23c01f0 | ghidra 0x24c01f0 | size 424 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_7TextureENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_7TextureENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x440,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x76);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x7e);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS_6StNULLEEEEEEEEEEE_02cbb280
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x1d0,0xd0,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS_6StNULLEEEEEEEEENS_18DefaultFunctorListEEE_02cbe018
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS_6StNULLEEEEEEEEEEE_02cbd378
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS_6StNULLEEEEEEEEEEE_02cbd378
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23dfb34 | ghidra 0x24dfb34 | size 484 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x440,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x76);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x7e);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cc22e0
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x3d7,0xd0,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cb9d50
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cc0028
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cc0028
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23dfd18 | ghidra 0x24dfd18 | size 452 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x440,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x76);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x7e);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cb8f68
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x3d6,0xd0,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc24f0
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cc15f8
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cc15f8
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23dfedc | ghidra 0x24dfedc | size 472 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_7TextureENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_7TextureENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x440,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x76);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x7e);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cc1900
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x3d5,0xd0,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cb76d8
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cbf750
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cbf750
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23e00b4 | ghidra 0x24e00b4 | size 440 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_7TextureENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_14ColorAnimationENS2_INS3_7TextureENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x440,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x76);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x7e);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cc4910
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x3d4,0xd0,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cbce40
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cbbd10
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_14ColorAnimationENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cbbd10
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23ff588 | ghidra 0x24ff588 | size 468 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x380,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x66);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cc1650
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x2c7,0x70,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cb7540
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cbbff0
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cbbff0
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23ff75c | ghidra 0x24ff75c | size 436 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x380,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x66);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEE_02cc42d8
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x2c6,0x70,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc34a0
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEE_02cb9398
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEE_02cb9398
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23ff910 | ghidra 0x24ff910 | size 456 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x380,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x66);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEE_02cb6ff0
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x2c5,0x70,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc3b30
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEE_02cb6c68
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEE_02cb6c68
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x23ffad8 | ghidra 0x24ffad8 | size 424 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x380,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x66);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEE_02cb7630
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x2c4,0x70,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEENS_18DefaultFunctorListEEE_02cbee38
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEE_02cb6f08
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEE_02cb6f08
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x241957c | ghidra 0x251957c | size 460 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x450,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x80);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cb8e68
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0xe3,0xe0,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc4c28
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cc4860
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cc4860
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2419748 | ghidra 0x2519748 | size 428 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x450,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x80);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEE_02cc3c90
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0xe2,0xe0,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEENS_18DefaultFunctorListEEE_02cc17f0
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEE_02cb8040
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEE_02cb8040
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x24198f4 | ghidra 0x25198f4 | size 448 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x450,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x80);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEE_02cc25c8
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0xe1,0xe0,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_4LineENS_6StNULLEEEEEEEEENS_18DefaultFunctorListEEE_02cbf3f0
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEE_02cb73f0
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEE_02cb73f0
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::StNULL> > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::StNULL> > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2419ab4 | ghidra 0x2519ab4 | size 416 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS_6StNULLEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS_6StNULLEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x450,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x80);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS_6StNULLEEEEEEEEE_02cbfe48
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0xe0,0xe0,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS_6StNULLEEEEEEENS_18DefaultFunctorListEEE_02cc3190
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS_6StNULLEEEEEEEEE_02cc1980
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS_6StNULLEEEEEEEEE_02cc1980
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2436908 | ghidra 0x2536908 | size 468 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x490,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x6e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x88);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEE_02cc2c00
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0xf3,0x100,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc4520
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEE_02cbaf20
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEE_02cbaf20
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2436adc | ghidra 0x2536adc | size 436 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x490,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x6e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x88);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEE_02cbd7c8
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0xf2,0x100,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cbe5d8
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEE_02cbdf50
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEE_02cbdf50
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2436c90 | ghidra 0x2536c90 | size 456 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_14ColorAnimationENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_14ColorAnimationENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x490,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x6e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x88);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cbd4e8
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0xf1,0x100,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cb7b68
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cbf9b0
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cbf9b0
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2436e58 | ghidra 0x2536e58 | size 424 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_14ColorAnimationENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_14ColorAnimationENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x490,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x6e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x88);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEEEEE_02cc0f10
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0xf0,0x100,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEEENS_18DefaultFunctorListEEE_02cbee58
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEEEEE_02cc37a0
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEEEEE_02cc37a0
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2456204 | ghidra 0x2556204 | size 484 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x490,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x6e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x88);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cbdca0
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x2f7,0x100,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc0668
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cb7080
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cb7080
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x24563e8 | ghidra 0x25563e8 | size 452 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x490,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x6e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x88);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cc3fe8
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x2f6,0x100,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc2730
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cb6ba0
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cb6ba0
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x24565ac | ghidra 0x25565ac | size 472 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_14ColorAnimationENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_14ColorAnimationENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x490,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x6e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x88);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cbf770
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x2f5,0x100,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cba170
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cc4b50
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cc4b50
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2456784 | ghidra 0x2556784 | size 440 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_14ColorAnimationENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_14ColorAnimationENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x490,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x6e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x88);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cbf6e0
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x2f4,0x100,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc3f80
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cc09e8
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cc09e8
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2474b28 | ghidra 0x2574b28 | size 476 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x450,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x80);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cb8468
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x2e7,0xe0,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cb9c90
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cb9168
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cb9168
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2474d04 | ghidra 0x2574d04 | size 444 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x450,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x80);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cc4c20
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x2e6,0xe0,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cbc968
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cbdc70
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cbdc70
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2474ec0 | ghidra 0x2574ec0 | size 464 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x450,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x80);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cbb5f8
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x2e5,0xe0,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc2978
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cb9e30
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cb9e30
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2475090 | ghidra 0x2575090 | size 432 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x450,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x80);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEE_02cba6b8
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x2e4,0xe0,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc0708
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEE_02cc1210
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEE_02cc1210
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2491f0c | ghidra 0x2591f0c | size 468 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x4d0,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x76);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x90);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEE_02cc0bf0
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x1e3,0x120,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cb9968
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEE_02cbeac0
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEE_02cbeac0
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x24920e0 | ghidra 0x25920e0 | size 436 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x4d0,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x76);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x90);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEE_02cbfd80
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x1e2,0x120,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cb7d78
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEE_02cb73a8
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEE_02cb73a8
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2492294 | ghidra 0x2592294 | size 456 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x4d0,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x76);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x90);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cb86c8
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x1e1,0x120,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cb97c8
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cbcf98
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cbcf98
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x249245c | ghidra 0x259245c | size 424 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x4d0,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x76);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x90);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS_6StNULLEEEEEEEEEEE_02cbcee0
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x1e0,0x120,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS_6StNULLEEEEEEEEENS_18DefaultFunctorListEEE_02cbd480
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS_6StNULLEEEEEEEEEEE_02cbbf50
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS_6StNULLEEEEEEEEEEE_02cbbf50
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x24b35c8 | ghidra 0x25b35c8 | size 476 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x510,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x6e);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x7e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x98);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEEEE_02cbafa8
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,499,0x140,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cb6cd0
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEEEE_02cc3338
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEEEE_02cc3338
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x24b37a4 | ghidra 0x25b37a4 | size 444 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x510,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x6e);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x7e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x98);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEEEE_02cc1ab8
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x1f2,0x140,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cb8380
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEEEE_02cc2468
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEEEE_02cc2468
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x24b3960 | ghidra 0x25b3960 | size 464 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x510,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x6e);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x7e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x98);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEE_02cbae10
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x1f1,0x140,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cbbd08
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEE_02cbfff0
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEE_02cbfff0
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x24b3b30 | ghidra 0x25b3b30 | size 432 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x510,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x6e);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x7e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x98);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEEEEEEE_02cbf3f8
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x1f0,0x140,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cb94f8
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEEEEEEE_02cbc008
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS_6StNULLEEEEEEEEEEEEE_02cbc008
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x24d7494 | ghidra 0x25d7494 | size 492 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x510,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x6e);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x7e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x98);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEE_02cc3590
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x3f7,0x140,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cb7390
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEE_02cc4118
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEE_02cc4118
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x24d7680 | ghidra 0x25d7680 | size 460 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x510,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x6e);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x7e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x98);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cbde90
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x3f6,0x140,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cba410
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cba1f0
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cba1f0
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x24d784c | ghidra 0x25d784c | size 480 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x510,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x6e);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x7e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x98);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cb87b0
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x3f5,0x140,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc0ec8
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cbcb48
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cbcb48
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x24d7a2c | ghidra 0x25d7a2c | size 448 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x510,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x6e);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x7e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x98);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cc4b20
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x3f4,0x140,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc1390
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cc0240
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cc0240
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x24fb328 | ghidra 0x25fb328 | size 484 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x4d0,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x76);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x90);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cb8498
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,999,0x120,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cbdfc8
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cc2af8
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cc2af8
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x24fb50c | ghidra 0x25fb50c | size 452 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x4d0,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x76);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x90);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cbd5f8
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x3e6,0x120,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc0738
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cb7468
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cb7468
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x24fb6d0 | ghidra 0x25fb6d0 | size 472 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x4d0,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x76);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x90);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cbea20
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x3e5,0x120,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cbfc80
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cbd780
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cbd780
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x24fb8a8 | ghidra 0x25fb8a8 | size 440 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x4d0,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x76);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x90);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cc2470
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x3e4,0x120,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cbb3e0
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cb7b20
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cb7b20
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x251ea0c | ghidra 0x261ea0c | size 460 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x400,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x76);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cc17f8
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x1c3,0xb0,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc34f8
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cbd698
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cbd698
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x251ebd8 | ghidra 0x261ebd8 | size 428 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_7TextureENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_7TextureENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x400,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x76);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEE_02cb99f0
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x1c2,0xb0,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEENS_18DefaultFunctorListEEE_02cc4508
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEE_02cb8da8
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEE_02cb8da8
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x251ed84 | ghidra 0x261ed84 | size 448 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_7TextureENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_7TextureENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x400,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x76);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEEE_02cbb4a8
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x1c1,0xb0,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEENS_18DefaultFunctorListEEE_02cbb688
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEEE_02cbb5d0
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_4LineENS_6StNULLEEEEEEEEEEE_02cbb5d0
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::StNULL> > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x251ef44 | ghidra 0x261ef44 | size 416 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_7TextureENS_6StNULLEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_7TextureENS_6StNULLEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x400,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x76);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS_6StNULLEEEEEEEEE_02cbf070
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x1c0,0xb0,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS_6StNULLEEEEEEENS_18DefaultFunctorListEEE_02cc4a18
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS_6StNULLEEEEEEEEE_02cbd380
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS_6StNULLEEEEEEEEE_02cbd380
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x253d120 | ghidra 0x263d120 | size 476 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x400,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x76);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cc4840
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x3c7,0xb0,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cbb368
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cc2398
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEE_02cc2398
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x253d2fc | ghidra 0x263d2fc | size 444 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_7TextureENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x400,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x76);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cc0800
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x3c6,0xb0,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cba0f8
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cb6dc8
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cb6dc8
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x253d4b8 | ghidra 0x263d4b8 | size 464 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_7TextureENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_7TextureENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x400,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x76);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cb92a0
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x3c5,0xb0,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cbc628
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cbba88
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEE_02cbba88
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x253d688 | ghidra 0x263d688 | size 432 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_7TextureENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures5SpeedENS2_INS3_6MotionENS2_INS3_7TextureENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x400,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x76);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEE_02cbeb48
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x3c4,0xb0,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cb9da0
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEE_02cb9788
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures5SpeedENS1_INS2_6MotionENS1_INS2_7TextureENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEE_02cb9788
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x255b37c | ghidra 0x265b37c | size 476 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS2_INS3_5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS2_INS3_5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x510,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x6e);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x7e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x98);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cc18b0
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x1fb,400,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc4768
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar7 & 1) != 0) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cc21c0
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEEEEEE_02cc21c0
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x255b558 | ghidra 0x265b558 | size 444 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS2_INS3_5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS2_INS3_5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x510,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x6e);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x7e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x98);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEEEEEE_02cbc2f8
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x1fa,400,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc1058
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if ((uVar4 & 1) != 0) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEEEEEE_02cc2df0
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEEEEEE_02cc2df0
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x256ef24 | ghidra 0x266ef24 | size 492 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS2_INS3_5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS2_INS3_5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_4LineENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x510,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x6e);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar5 + 0x7e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar5 + 0x98);
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEEEE_02cb81a0
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x3ff,400,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cbfbc0
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEEEE_02cbbdd8
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_4LineENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEEEE_02cbbdd8
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::Programmable, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Motion, Aska::FeatureList<Aska::ParticleFeatures::Rotation, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Dynamics, Aska::FeatureList<Aska::ParticleDynamicsFeatures::Dynamics, Aska::StNULL> > > > > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x256f110 | ghidra 0x266f110 | size 460 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS2_INS3_5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS2_INS3_5SpeedENS2_INS3_6MotionENS2_INS3_8RotationENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_9LifeLimitENS2_INS3_8DynamicsENS2_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x510,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x6e);
    Aska::ParticleEmitterRotationUnit::ParticleEmitterRotationUnit()(plVar2 + 0x7e);
    Aska::ParticleEmitterMotionUnit::ParticleEmitterMotionUnit()(plVar2 + 0x98);
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEE_02cc32c8
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x3fe,400,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cb8160
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEE_02cbfa10
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures12ProgrammableENS1_INS2_5SpeedENS1_INS2_6MotionENS1_INS2_8RotationENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_9LifeLimitENS1_INS2_8DynamicsENS1_INS_24ParticleDynamicsFeatures8DynamicsENS_6StNULLEEEEEEEEEEEEEEEEEEEEE_02cbfa10
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x25822ac | ghidra 0x26822ac | size 480 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_5SpeedENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_5SpeedENS2_INS3_9LifeLimitENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x400,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x6e);
    plVar5[0x7e] = 0;
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEE_02cc1e70
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa40,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x393,0x100,0xa40);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEENS_18DefaultFunctorListEEE_02cbff08
      ;
      *(undefined1 *)((long)plVar6 + 0xa34) = 0;
      *(undefined8 *)((long)plVar6 + 0xa2c) = 0;
      *plVar6 = (long)(puVar1 + 0x10);
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachCurveMotion(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEE_02cc0a28
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_9LifeLimitENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEEEE_02cc0a28
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::LifeLimit, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x258248c | ghidra 0x268248c | size 448 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_5SpeedENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_5SpeedENS2_INS3_9LifeLimitENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x400,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x6e);
    plVar2[0x7e] = 0;
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEE_02cb89f0
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa20,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x392,0x100,0xa20);
      puVar1 = 
      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cc0e90
      ;
      *(undefined8 *)((long)plVar3 + 0xa0c) = 0;
      *(undefined1 *)((long)plVar3 + 0xa14) = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachCurveMotion(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEE_02cb6cb8
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_9LifeLimitENS_6StNULLEEEEEEEEEEEEE_02cb6cb8
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::FeatureList<Aska::ParticleFeatures::Line, Aska::StNULL> > > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x258264c | ghidra 0x268264c | size 468 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_5SpeedENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_5SpeedENS2_INS3_4LineENS_6StNULLEEEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long *plVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  
  plVar5 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x400,0x10,1);
  if (plVar5 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar5);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar5 + 0x66);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar5 + 0x6e);
    plVar5[0x7e] = 0;
    *plVar5 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cb85e0
                    + 0x10);
    plVar6 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa30,0x10,1);
    if (plVar6 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar6,0x391,0x100,0xa30);
      uVar4 = _UNK_029e82e8;
      uVar3 = _UNK_029e82e0;
      uVar2 = _UNK_029e82d0;
      puVar1 = PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_4LineENS_6StNULLEEEEEEEEEEENS_18DefaultFunctorListEEE_02cbb8f0
               + 0x10;
      *(undefined8 *)((long)plVar6 + 0xa14) = _UNK_029e82d8;
      *(undefined8 *)((long)plVar6 + 0xa0c) = uVar2;
      *(undefined8 *)((long)plVar6 + 0xa24) = uVar4;
      *(undefined8 *)((long)plVar6 + 0xa1c) = uVar3;
      *plVar6 = (long)puVar1;
      uVar7 = Aska::IParticleObject::Alloc(int, int)(plVar6,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar7 & 1) != 0) && (uVar7 = Aska::IParticleObject::AttachCurveMotion(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar6,param_2), (uVar7 & 1) != 0)) {
        plVar8 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cbd730
                 + 0x2f0;
        *plVar8 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS1_INS2_4LineENS_6StNULLEEEEEEEEEEEEE_02cbd730
                        + 0x10);
        plVar8[0x61] = (long)puVar1;
        if (plVar8 != (long *)0x0) {
          (**(code **)(*plVar5 + 0x160))(plVar5,param_2);
          (**(code **)(*plVar6 + 0x10))(plVar6,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar5,plVar6);
          *(undefined1 *)(plVar8 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar8 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar7 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar8,plVar6);
          if ((uVar7 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar5,param_2,plVar8);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar5);
            return plVar5;
          }
          Aska::IParticleEmitter::DetachObject()(plVar5);
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    (**(code **)(*plVar5 + 0x38))(plVar5,0);
  }
  return (long *)0x0;
}

// ==== Aska::ParticleEmitter<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::StNULL> > > > >* Aska::ParticleManager::CreateParticle<Aska::FeatureList<Aska::ParticleFeatures::CurveMotion, Aska::FeatureList<Aska::ParticleFeatures::Texture, Aska::FeatureList<Aska::ParticleFeatures::ColorAnimation, Aska::FeatureList<Aska::ParticleFeatures::Speed, Aska::StNULL> > > > >(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x2582820 | ghidra 0x2682820 | size 436 | symbol _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_5SpeedENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska15ParticleManager14CreateParticleINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS2_INS3_7TextureENS2_INS3_14ColorAnimationENS2_INS3_5SpeedENS_6StNULLEEEEEEEEEEEPNS_15ParticleEmitterIT_EEPKNS_3AFF18AsfParticleEmitterE
                 (undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar2 = (long *)Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(0x400,0x10,1);
  if (plVar2 != (long *)0x0) {
    Aska::IParticleEmitter::IParticleEmitter()(plVar2);
    Aska::ParticleEmitterColorAnimationUnit::ParticleEmitterColorAnimationUnit()(plVar2 + 0x66);
    Aska::ParticleEmitterTextureUnit::ParticleEmitterTextureUnit()(plVar2 + 0x6e);
    plVar2[0x7e] = 0;
    *plVar2 = (long)(
                    PTR__ZTVN4Aska15ParticleEmitterINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS_6StNULLEEEEEEEEEEE_02cb7438
                    + 0x10);
    plVar3 = (long *)Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(0xa10,0x10,1);
    if (plVar3 != (long *)0x0) {
      Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)(plVar3,0x390,0x100,0xa10);
      *plVar3 = (long)(
                      PTR__ZTVN4Aska14ParticleObjectINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS_6StNULLEEEEEEEEENS_18DefaultFunctorListEEE_02cc29b8
                      + 0x10);
      uVar4 = Aska::IParticleObject::Alloc(int, int)(plVar3,*(undefined2 *)(param_2 + 0x1c0),
                              *(undefined1 *)(param_2 + 0x1d0));
      if (((uVar4 & 1) != 0) && (uVar4 = Aska::IParticleObject::AttachCurveMotion(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)(plVar3,param_2), (uVar4 & 1) != 0)) {
        plVar5 = (long *)Aska::ParticleRenderableBase::operator new(unsigned long, unsigned long, bool)(0xfe0,0x10,1);
        Aska::ParticleRenderableBase::ParticleRenderableBase()();
        puVar1 = PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS_6StNULLEEEEEEEEEEE_02cb8ac0
                 + 0x2f0;
        *plVar5 = (long)(
                        PTR__ZTVN4Aska24ParticleRenderableObjectINS_11FeatureListINS_16ParticleFeatures11CurveMotionENS1_INS2_7TextureENS1_INS2_14ColorAnimationENS1_INS2_5SpeedENS_6StNULLEEEEEEEEEEE_02cb8ac0
                        + 0x10);
        plVar5[0x61] = (long)puVar1;
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar2 + 0x160))(plVar2,param_2);
          (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
          Aska::IParticleEmitter::AttachObject(Aska::IParticleObject*)(plVar2,plVar3);
          *(undefined1 *)(plVar5 + 0x117) = *(undefined1 *)(param_2 + 0x1d1);
          *(undefined1 *)((long)plVar5 + 0x8ba) = *(undefined1 *)(param_2 + 0x1d2);
          uVar4 = Aska::ParticleRenderableBase::AttachObject(Aska::IParticleObject*)(plVar5,plVar3);
          if ((uVar4 & 1) != 0) {
            Aska::IParticleEmitter::AttachRenderable(Aska::AFF::AsfParticleEmitter const*, Aska::ParticleRenderableBase*)(plVar2,param_2,plVar5);
            Aska::TaskManager::Add(Aska::Task*)(param_1,plVar2);
            return plVar2;
          }
          Aska::IParticleEmitter::DetachObject()(plVar2);
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
  }
  return (long *)0x0;
}


// FAILED to create function at 029d0df0 typeinfo name for Aska::ParticleManager::ParticleDeleteHandler
// FAILED to create function at 02c514c8 Aska::ParticleManager::vtable
// FAILED to create function at 02c516a0 Aska::ParticleManager::typeinfo
// FAILED to create function at 02c516d8 Aska::ParticleManager::ParticleDeleteHandler::vtable
// FAILED to create function at 02c51710 Aska::ParticleManager::ParticleDeleteHandler::typeinfo
// FAILED to create function at 02dd0928 Aska::ParticleManager::m_nTaskLevelForMakeMatrix
// FAILED to create function at 02dd0938 Aska::ParticleManager::gpMemHeap
// FAILED to create function at 02dd0940 Aska::ParticleManager::gpMemPhys
