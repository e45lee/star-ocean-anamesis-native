// port/decomp/dynamics/forces.c: Ghidra decompiles for the dynamics subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 14:43 UTC: tools/decomp.sh '--into' 'dynamics/forces' ' Aska::(DynamicsForceEmitter\w*|Dynamics\w*Wind|DynamicsGravitation|DynamicsAirFriction|DynamicsAcceleration)(::_\w+)?::[~\w<>]+\('

// ==== Aska::DynamicsForceEmitterManager::_UpdateTask::~_UpdateTask()
// vaddr 0x209f448 | ghidra 0x219f448 | size 24 | symbol _ZN4Aska27DynamicsForceEmitterManager11_UpdateTaskD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27DynamicsForceEmitterManager11_UpdateTaskD0Ev(undefined8 param_1)

{
  Aska::Task::~Task()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsForceEmitterManager::_UpdateTask::Run(int)
// vaddr 0x209f460 | ghidra 0x219f460 | size 40 | symbol _ZN4Aska27DynamicsForceEmitterManager11_UpdateTask3RunEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27DynamicsForceEmitterManager11_UpdateTask3RunEi(long param_1)

{
  if (*(long *)(param_1 + 0x28) != 0) {
    Aska::DynamicsForceEmitterManager::MakeDynamicsList()();
    (*(code *)PTR__ZN4Aska27DynamicsForceEmitterManager15UpdateWorldWindEv_02caa880)
              (*(undefined8 *)(param_1 + 0x28));
    return;
  }
  return;
}

// ==== Aska::DynamicsForceEmitterManager::~DynamicsForceEmitterManager()
// vaddr 0x209f488 | ghidra 0x219f488 | size 88 | symbol _ZN4Aska27DynamicsForceEmitterManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27DynamicsForceEmitterManagerD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska27DynamicsForceEmitterManagerE_02cbf088 + 0x10);
  if (param_1[9] != 0) {
    operator delete[](void*)();
    param_1[9] = 0;
  }
  if ((long *)param_1[8] != (long *)0x0) {
    (**(code **)(*(long *)param_1[8] + 0x50))();
  }
  param_1[1] = (long)(PTR__ZTVN4Aska5TListINS_21AnimatableLinkElementEEE_02cc13d8 + 0x10);
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1 + 2);
  return;
}

// ==== Aska::DynamicsForceEmitterManager::~DynamicsForceEmitterManager()
// vaddr 0x209f4e0 | ghidra 0x219f4e0 | size 96 | symbol _ZN4Aska27DynamicsForceEmitterManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27DynamicsForceEmitterManagerD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska27DynamicsForceEmitterManagerE_02cbf088 + 0x10);
  if (param_1[9] != 0) {
    operator delete[](void*)();
    param_1[9] = 0;
  }
  if ((long *)param_1[8] != (long *)0x0) {
    (**(code **)(*(long *)param_1[8] + 0x50))();
  }
  param_1[1] = (long)(PTR__ZTVN4Aska5TListINS_21AnimatableLinkElementEEE_02cc13d8 + 0x10);
  Aska::IAnimatable::~IAnimatable()(param_1 + 2);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsForceEmitter::DynamicsForceEmitter()
// vaddr 0x20e5da0 | ghidra 0x21e5da0 | size 312 | symbol _ZN4Aska20DynamicsForceEmitterC2Ev | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska20DynamicsForceEmitterC2Ev(long *param_1)

{
  byte bVar1;
  byte bVar2;
  long lVar3;
  long lVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined4 uVar7;
  code *pcVar8;
  long *plVar9;
  long *plVar10;
  long *plVar11;
  
  pcVar8 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
  *param_1 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined2 *)((long)param_1 + 0x24) = 0;
  *(undefined1 *)((long)param_1 + 0x26) = 0;
  uVar7 = (*pcVar8)();
  *(undefined4 *)(param_1 + 4) = uVar7;
  puVar5 = PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8;
  *param_1 = (long)(PTR__ZTVN4Aska18HierarchicalObjectE_02cb6bb0 + 0x10);
  plVar9 = param_1 + 6;
  *plVar9 = (long)(puVar5 + 0x10);
  *(undefined4 *)(param_1 + 0x14) = 0x3f800000;
  *(undefined4 *)((long)param_1 + 0xac) = 0x3f800000;
  lVar4 = _UNK_027dbb38;
  lVar3 = _UNK_027dbb30;
  bVar1 = *(byte *)(param_1 + 0x25);
  bVar2 = *(byte *)((long)param_1 + 0x129);
  *(byte *)((long)param_1 + 0x129) = bVar2 & 0xfc;
  *(undefined8 *)((long)param_1 + 0xa4) = 0x3f8000003f800000;
  param_1[0x11] = lVar4;
  param_1[0x10] = lVar3;
  param_1[0x13] = lVar4;
  param_1[0x12] = lVar3;
  *(byte *)(param_1 + 0x25) = bVar1 & 0xde | 1;
  plVar10 = param_1 + 0x18;
  do {
    plVar11 = (long *)((long)plVar10 + 0x7fU & 0xffffffffffffff81);
    Hint_Prefetch(plVar10,0,2,0);
    plVar10 = plVar11;
  } while (plVar11 < param_1 + 0x1a);
  param_1[0x20] = (long)plVar9;
  param_1[0x21] = (long)plVar9;
  param_1[0x1b] = lVar4;
  param_1[0x1a] = lVar3;
  param_1[0x1d] = lVar4;
  param_1[0x1c] = lVar3;
  param_1[0x17] = lVar4;
  param_1[0x16] = lVar3;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined8 *)((long)param_1 + 0xc4) = 0;
  param_1[0x1e] = 0;
  param_1[0x1f] = 0;
  param_1[0x22] = 0;
  param_1[0x23] = 0;
  param_1[5] = 0;
  *(byte *)((long)param_1 + 0x129) = bVar2 & 0xf8;
  *(undefined4 *)((long)param_1 + 0xcc) = 0x3f800000;
  param_1[0x23] = (long)param_1;
  param_1[0x24] = (long)(param_1 + 8);
  param_1[0x30] = 0;
  param_1[0x31] = 0;
  *(undefined4 *)(param_1 + 0x32) = 0;
  *(undefined1 *)((long)param_1 + 0x197) = 0;
  puVar6 = PTR__ZN4Aska20DynamicsForceEmitter25m_uiDefaultForceEmitterIDE_02cc49c0;
  puVar5 = PTR__ZTVN4Aska20DynamicsForceEmitterE_02cc1580;
  *(undefined2 *)((long)param_1 + 0x194) = 1;
  *(byte *)(param_1 + 0x25) = bVar1 & 200 | 1;
  *param_1 = (long)(puVar5 + 0x10);
  uVar7 = *(undefined4 *)puVar6;
  *(undefined1 *)((long)param_1 + 0x19c) = 0;
  *(undefined4 *)(param_1 + 0x33) = uVar7;
  return;
}

// ==== Aska::DynamicsForceEmitter::Get(unsigned long, void*) const
// vaddr 0x2339244 | ghidra 0x2439244 | size 4 | symbol _ZNK4Aska20DynamicsForceEmitter3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK4Aska20DynamicsForceEmitter3GetEmPv(void)

{
  (*(code *)PTR__ZNK4Aska18HierarchicalObject3GetEmPv_02caf7c8)();
  return;
}

// ==== Aska::DynamicsForceEmitter::Set(unsigned long, void const*)
// vaddr 0x2339248 | ghidra 0x2439248 | size 4 | symbol _ZN4Aska20DynamicsForceEmitter3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20DynamicsForceEmitter3SetEmPKv(void)

{
  (*(code *)PTR__ZN4Aska18HierarchicalObject3SetEmPKv_02c94c28)();
  return;
}

// ==== Aska::DynamicsWorldWind::_WorldWind::Run(int)
// vaddr 0x233924c | ghidra 0x243924c | size 228 | symbol _ZN4Aska17DynamicsWorldWind10_WorldWind3RunEi | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska17DynamicsWorldWind10_WorldWind3RunEi(long param_1)

{
  long *plVar1;
  undefined8 uVar2;
  long lVar3;
  float fVar4;
  float fVar5;
  
  plVar1 = *(long **)(param_1 + 0x38);
  if (plVar1 != (long *)0x0) {
    if ((*(byte *)(plVar1 + 0x25) & 1) != 0) {
      (**(code **)(*plVar1 + 0xa8))();
      plVar1 = *(long **)(param_1 + 0x38);
    }
    uVar2 = (**(code **)(*plVar1 + 0x98))();
    Aska::Vector::ApplyMatrixNoTransport(Aska::Vector*, Aska::Matrix const*) const(PTR__ZN4Aska17DynamicsPrimitive8m_vUnitYE_02cbf898,plVar1 + 0x34,uVar2);
    lVar3 = *(long *)(param_1 + 0x38);
    fVar5 = *(float *)(lVar3 + 0x1a0) * *(float *)(lVar3 + 0x1a0) +
            *(float *)(lVar3 + 0x1a4) * *(float *)(lVar3 + 0x1a4) +
            *(float *)(lVar3 + 0x1a8) * *(float *)(lVar3 + 0x1a8);
    fVar4 = SQRT(fVar5);
    if (NAN(fVar4)) {
      fVar4 = (float)sqrtf(fVar5);
    }
    if (_UNK_027e519c <= fVar4) {
      fVar4 = 1.0 / fVar4;
      *(float *)(lVar3 + 0x1a0) = fVar4 * *(float *)(lVar3 + 0x1a0);
      *(float *)(lVar3 + 0x1a4) = fVar4 * *(float *)(lVar3 + 0x1a4);
      *(float *)(lVar3 + 0x1a8) = fVar4 * *(float *)(lVar3 + 0x1a8);
    }
    if (*(char *)(*(long *)(param_1 + 0x38) + 0x19c) == '\0') {
      *(undefined1 *)(*(long *)(param_1 + 0x38) + 0x19c) = 1;
    }
  }
  return;
}

// ==== Aska::DynamicsWorldWind::CreateParticleObject()
// vaddr 0x2339330 | ghidra 0x2439330 | size 52 | symbol _ZN4Aska17DynamicsWorldWind20CreateParticleObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17DynamicsWorldWind20CreateParticleObjectEv(long param_1)

{
  long *plVar1;
  
  plVar1 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80);
  if (plVar1 != (long *)0x0) {
    *plVar1 = (long)(PTR__ZTVN4Aska25ParticleDynamicsWorldWindE_02cbb420 + 0x10);
    plVar1[1] = param_1;
  }
  return;
}

// ==== Aska::DynamicsWorldWind::Clone(Aska::IAnimatable const*)
// vaddr 0x2339364 | ghidra 0x2439364 | size 8 | symbol _ZN4Aska17DynamicsWorldWind5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska17DynamicsWorldWind5CloneEPKNS_11IAnimatableE(void)

{
  return 0;
}

// ==== Aska::DynamicsForceEmitter::Clone(Aska::IAnimatable const*)
// vaddr 0x233936c | ghidra 0x243936c | size 8 | symbol _ZN4Aska20DynamicsForceEmitter5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska20DynamicsForceEmitter5CloneEPKNS_11IAnimatableE(void)

{
  return 0;
}

// ==== Aska::DynamicsWorldWind::CreateClone(Aska::IAnimatable const*)
// vaddr 0x2339374 | ghidra 0x2439374 | size 280 | symbol _ZN4Aska17DynamicsWorldWind11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska17DynamicsWorldWind11CreateCloneEPKNS_11IAnimatableE(void)

{
  long *plVar1;
  long lVar2;
  undefined *puVar3;
  undefined *puVar4;
  long *plVar5;
  long lVar6;
  
  plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x200,PTR__ZSt7nothrow_02cb9a80);
  if (plVar5 != (long *)0x0) {
    Aska::DynamicsForceEmitter::DynamicsForceEmitter()(plVar5);
    plVar5[0x3a] = 0;
    plVar5[0x3b] = 0;
    *(undefined1 *)((long)plVar5 + 0x1f6) = 0;
    plVar5[0x3c] = 0;
    plVar5[0x3d] = 0;
    *(undefined4 *)(plVar5 + 0x3e) = 0x100;
    puVar3 = PTR__ZTVN4Aska17DynamicsWorldWind10_WorldWindE_02cc2e08;
    *(undefined1 *)((long)plVar5 + 500) = 1;
    plVar5[0x3f] = (long)plVar5;
    puVar4 = PTR__ZTVN4Aska17DynamicsWorldWindE_02cc3998;
    lVar6 = _UNK_027dbb38;
    lVar2 = _UNK_027dbb30;
    plVar5[0x38] = (long)(puVar3 + 0x10);
    plVar5[0x39] = 0;
    plVar5[0x35] = lVar6;
    plVar5[0x34] = lVar2;
    *plVar5 = (long)(puVar4 + 0x10);
    Aska::DynamicsHandler::~DynamicsHandler()(plVar5 + 0x38);
    plVar1 = plVar5 + 6;
    *plVar5 = (long)(PTR__ZTVN4Aska18HierarchicalObjectE_02cb6bb0 + 0x10);
    Aska::HierarchicalObjectContainer::DetachFromParent()(plVar1);
    if ((*(byte *)(plVar5 + 0x25) & 1) == 0) {
      Aska::HierarchicalObjectContainer::UpdateHierarchically()(plVar1);
    }
    if ((code *)plVar5[5] != (code *)0x0) {
      (*(code *)plVar5[5])(plVar5);
    }
    if (plVar5[0x30] != 0) {
      operator delete(void*)();
      plVar5[0x30] = 0;
    }
    plVar5[6] = (long)(PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8 + 0x10);
    lVar2 = plVar5[0x22];
    while (lVar2 != 0) {
      lVar6 = *(long *)(lVar2 + 8);
      *(undefined8 *)(lVar2 + 8) = 0;
      *(undefined8 *)(lVar2 + 0x10) = 0;
      lVar2 = lVar6;
    }
    Aska::IAnimatable::~IAnimatable()(plVar1);
    Aska::Task::~Task()(plVar5);
    operator delete(void*)(plVar5);
  }
  return 0;
}

// ==== Aska::DynamicsWorldWind::Get(unsigned long, void*) const
// vaddr 0x233948c | ghidra 0x243948c | size 96 | symbol _ZNK4Aska17DynamicsWorldWind3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska17DynamicsWorldWind3GetEmPv(long param_1,ulong param_2,undefined4 *param_3)

{
  uint uVar1;
  ulong uVar2;
  undefined4 uVar3;
  
  uVar2 = Aska::HierarchicalObject::Get(unsigned long, void*) const();
  if ((uVar2 & 1) == 0) {
    if ((param_2 & 0xffff00000000) != 0) {
      return 0;
    }
    uVar1 = (uint)param_2 & 0xffff;
    if (uVar1 == 0x11) {
      uVar3 = *(undefined4 *)(param_1 + 0x1b4);
    }
    else {
      if (uVar1 != 0x10) {
        return 0;
      }
      uVar3 = *(undefined4 *)(param_1 + 0x1b0);
    }
    *param_3 = uVar3;
  }
  return 1;
}

// ==== Aska::DynamicsWorldWind::Set(unsigned long, void const*)
// vaddr 0x23394ec | ghidra 0x24394ec | size 104 | symbol _ZN4Aska17DynamicsWorldWind3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska17DynamicsWorldWind3SetEmPKv(long param_1,ulong param_2,undefined4 *param_3)

{
  uint uVar1;
  ulong uVar2;
  
  uVar2 = Aska::HierarchicalObject::Set(unsigned long, void const*)();
  if ((uVar2 & 1) == 0) {
    if ((param_2 & 0xffff00000000) != 0) {
      return 0;
    }
    uVar1 = (uint)param_2 & 0xffff;
    if (uVar1 == 0x11) {
      *(undefined4 *)(param_1 + 0x1b4) = *param_3;
    }
    else {
      if (uVar1 != 0x10) {
        return 0;
      }
      *(undefined4 *)(param_1 + 0x1b0) = *param_3;
    }
  }
  return 1;
}

// ==== Aska::DynamicsOmniWind::_OmniWind::Run(int)
// vaddr 0x2339554 | ghidra 0x2439554 | size 108 | symbol _ZN4Aska16DynamicsOmniWind9_OmniWind3RunEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16DynamicsOmniWind9_OmniWind3RunEi(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x38);
  if (plVar1 != (long *)0x0) {
    if ((*(byte *)(plVar1 + 0x25) & 1) != 0) {
      (**(code **)(*plVar1 + 0xa8))();
      plVar1 = *(long **)(param_1 + 0x38);
    }
    *(undefined4 *)(plVar1 + 0x34) = *(undefined4 *)((long)plVar1 + 0x4c);
    *(undefined4 *)((long)plVar1 + 0x1a4) = *(undefined4 *)((long)plVar1 + 0x5c);
    *(undefined4 *)(plVar1 + 0x35) = *(undefined4 *)((long)plVar1 + 0x6c);
    *(undefined4 *)((long)plVar1 + 0x1ac) = 0x3f800000;
    if (*(char *)(*(long *)(param_1 + 0x38) + 0x19c) == '\0') {
      *(undefined1 *)(*(long *)(param_1 + 0x38) + 0x19c) = 1;
      return;
    }
  }
  return;
}

// ==== Aska::DynamicsOmniWind::CreateParticleObject()
// vaddr 0x23395c0 | ghidra 0x24395c0 | size 52 | symbol _ZN4Aska16DynamicsOmniWind20CreateParticleObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16DynamicsOmniWind20CreateParticleObjectEv(long param_1)

{
  long *plVar1;
  
  plVar1 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80);
  if (plVar1 != (long *)0x0) {
    *plVar1 = (long)(PTR__ZTVN4Aska24ParticleDynamicsOmniWindE_02cc3ee8 + 0x10);
    plVar1[1] = param_1;
  }
  return;
}

// ==== Aska::DynamicsOmniWind::Clone(Aska::IAnimatable const*)
// vaddr 0x23395f4 | ghidra 0x24395f4 | size 8 | symbol _ZN4Aska16DynamicsOmniWind5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska16DynamicsOmniWind5CloneEPKNS_11IAnimatableE(void)

{
  return 0;
}

// ==== Aska::DynamicsOmniWind::CreateClone(Aska::IAnimatable const*)
// vaddr 0x23395fc | ghidra 0x24395fc | size 280 | symbol _ZN4Aska16DynamicsOmniWind11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska16DynamicsOmniWind11CreateCloneEPKNS_11IAnimatableE(void)

{
  long *plVar1;
  long lVar2;
  undefined *puVar3;
  undefined *puVar4;
  long *plVar5;
  long lVar6;
  
  plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x200,PTR__ZSt7nothrow_02cb9a80);
  if (plVar5 != (long *)0x0) {
    Aska::DynamicsForceEmitter::DynamicsForceEmitter()(plVar5);
    plVar5[0x3a] = 0;
    plVar5[0x3b] = 0;
    *(undefined1 *)((long)plVar5 + 0x1f6) = 0;
    plVar5[0x3c] = 0;
    plVar5[0x3d] = 0;
    *(undefined4 *)(plVar5 + 0x3e) = 0x100;
    puVar4 = PTR__ZTVN4Aska16DynamicsOmniWind9_OmniWindE_02cc2f20;
    *(undefined1 *)((long)plVar5 + 500) = 1;
    plVar5[0x3f] = (long)plVar5;
    puVar3 = PTR__ZTVN4Aska16DynamicsOmniWindE_02cc1a60;
    lVar6 = _UNK_027dbb38;
    lVar2 = _UNK_027dbb30;
    plVar5[0x38] = (long)(puVar4 + 0x10);
    plVar5[0x39] = 0;
    plVar5[0x35] = lVar6;
    plVar5[0x34] = lVar2;
    *plVar5 = (long)(puVar3 + 0x10);
    Aska::DynamicsHandler::~DynamicsHandler()(plVar5 + 0x38);
    plVar1 = plVar5 + 6;
    *plVar5 = (long)(PTR__ZTVN4Aska18HierarchicalObjectE_02cb6bb0 + 0x10);
    Aska::HierarchicalObjectContainer::DetachFromParent()(plVar1);
    if ((*(byte *)(plVar5 + 0x25) & 1) == 0) {
      Aska::HierarchicalObjectContainer::UpdateHierarchically()(plVar1);
    }
    if ((code *)plVar5[5] != (code *)0x0) {
      (*(code *)plVar5[5])(plVar5);
    }
    if (plVar5[0x30] != 0) {
      operator delete(void*)();
      plVar5[0x30] = 0;
    }
    plVar5[6] = (long)(PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8 + 0x10);
    lVar2 = plVar5[0x22];
    while (lVar2 != 0) {
      lVar6 = *(long *)(lVar2 + 8);
      *(undefined8 *)(lVar2 + 8) = 0;
      *(undefined8 *)(lVar2 + 0x10) = 0;
      lVar2 = lVar6;
    }
    Aska::IAnimatable::~IAnimatable()(plVar1);
    Aska::Task::~Task()(plVar5);
    operator delete(void*)(plVar5);
  }
  return 0;
}

// ==== Aska::DynamicsOmniWind::Get(unsigned long, void*) const
// vaddr 0x2339714 | ghidra 0x2439714 | size 112 | symbol _ZNK4Aska16DynamicsOmniWind3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska16DynamicsOmniWind3GetEmPv(long param_1,ulong param_2,undefined4 *param_3)

{
  uint uVar1;
  ulong uVar2;
  undefined4 uVar3;
  
  uVar2 = Aska::HierarchicalObject::Get(unsigned long, void*) const();
  if ((uVar2 & 1) == 0) {
    if ((param_2 & 0xffff00000000) != 0) {
      return 0;
    }
    uVar1 = (uint)param_2 & 0xffff;
    if (uVar1 == 0x14) {
      uVar3 = *(undefined4 *)(param_1 + 0x1b8);
    }
    else if (uVar1 == 0x13) {
      uVar3 = *(undefined4 *)(param_1 + 0x1b4);
    }
    else {
      if (uVar1 != 0x12) {
        return 0;
      }
      uVar3 = *(undefined4 *)(param_1 + 0x1b0);
    }
    *param_3 = uVar3;
  }
  return 1;
}

// ==== Aska::DynamicsOmniWind::Set(unsigned long, void const*)
// vaddr 0x2339784 | ghidra 0x2439784 | size 124 | symbol _ZN4Aska16DynamicsOmniWind3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska16DynamicsOmniWind3SetEmPKv(long param_1,ulong param_2,undefined4 *param_3)

{
  uint uVar1;
  ulong uVar2;
  
  uVar2 = Aska::HierarchicalObject::Set(unsigned long, void const*)();
  if ((uVar2 & 1) == 0) {
    if ((param_2 & 0xffff00000000) != 0) {
      return 0;
    }
    uVar1 = (uint)param_2 & 0xffff;
    if (uVar1 == 0x14) {
      *(undefined4 *)(param_1 + 0x1b8) = *param_3;
    }
    else if (uVar1 == 0x13) {
      *(undefined4 *)(param_1 + 0x1b4) = *param_3;
    }
    else {
      if (uVar1 != 0x12) {
        return 0;
      }
      *(undefined4 *)(param_1 + 0x1b0) = *param_3;
    }
  }
  return 1;
}

// ==== Aska::DynamicsCircleWind::_CircleWind::Run(int)
// vaddr 0x2339800 | ghidra 0x2439800 | size 364 | symbol _ZN4Aska18DynamicsCircleWind11_CircleWind3RunEi | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska18DynamicsCircleWind11_CircleWind3RunEi(long param_1)

{
  long lVar1;
  undefined8 uVar2;
  byte bVar3;
  long lVar4;
  long *plVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  plVar5 = *(long **)(param_1 + 0x38);
  if (plVar5 != (long *)0x0) {
    if ((*(byte *)(plVar5 + 0x25) & 1) != 0) {
      (**(code **)(*plVar5 + 0xa8))(plVar5);
      plVar5 = *(long **)(param_1 + 0x38);
    }
    lVar1 = _UNK_027dbb38;
    lVar4 = _UNK_027dbb30;
    bVar3 = *(byte *)(plVar5 + 0x25);
    if ((bVar3 >> 2 & 1) == 0) {
      if ((*(byte *)((long)plVar5 + 0x129) & 3) == 0) {
        fVar6 = *(float *)((long)plVar5 + 0x4c);
        fVar7 = *(float *)((long)plVar5 + 0x5c);
        fVar8 = *(float *)((long)plVar5 + 0x6c);
        plVar5[0x27] = CONCAT44((int)plVar5[0xe],*(float *)(plVar5 + 0xc));
        plVar5[0x26] = CONCAT44(*(float *)(plVar5 + 10),*(float *)(plVar5 + 8));
        plVar5[0x29] = CONCAT44(*(undefined4 *)((long)plVar5 + 0x74),*(float *)((long)plVar5 + 100))
        ;
        plVar5[0x28] = CONCAT44(*(float *)((long)plVar5 + 0x54),*(float *)((long)plVar5 + 0x44));
        *(float *)((long)plVar5 + 0x13c) =
             -(*(float *)(plVar5 + 8) * fVar6 + *(float *)(plVar5 + 10) * fVar7 +
              *(float *)(plVar5 + 0xc) * fVar8);
        *(float *)((long)plVar5 + 0x14c) =
             -(fVar6 * *(float *)((long)plVar5 + 0x44) + fVar7 * *(float *)((long)plVar5 + 0x54) +
              fVar8 * *(float *)((long)plVar5 + 100));
        plVar5[0x2b] = CONCAT44((int)plVar5[0xf],*(float *)(plVar5 + 0xd));
        plVar5[0x2a] = CONCAT44(*(float *)(plVar5 + 0xb),*(float *)(plVar5 + 9));
        plVar5[0x2d] = lVar1;
        plVar5[0x2c] = lVar4;
        *(float *)((long)plVar5 + 0x15c) =
             -(fVar6 * *(float *)(plVar5 + 9) + fVar7 * *(float *)(plVar5 + 0xb) +
              fVar8 * *(float *)(plVar5 + 0xd));
      }
      else {
        Aska::Matrix::InvertLowError(Aska::Matrix*) const(plVar5 + 8,plVar5 + 0x26);
        bVar3 = *(byte *)(plVar5 + 0x25);
      }
      *(byte *)(plVar5 + 0x25) = bVar3 | 4;
      plVar5 = *(long **)(param_1 + 0x38);
    }
    uVar2 = (**(code **)(*plVar5 + 0x98))(plVar5);
    Aska::Vector::ApplyMatrixNoTransport(Aska::Vector*, Aska::Matrix const*) const(PTR__ZN4Aska17DynamicsPrimitive8m_vUnitYE_02cbf898,plVar5 + 0x3c,uVar2);
    lVar4 = *(long *)(param_1 + 0x38);
    *(undefined8 *)(lVar4 + 0x1a8) = *(undefined8 *)(lVar4 + 0x138);
    *(undefined8 *)(lVar4 + 0x1a0) = *(undefined8 *)(lVar4 + 0x130);
    *(undefined8 *)(lVar4 + 0x1b8) = *(undefined8 *)(lVar4 + 0x148);
    *(undefined8 *)(lVar4 + 0x1b0) = *(undefined8 *)(lVar4 + 0x140);
    *(undefined8 *)(lVar4 + 0x1c8) = *(undefined8 *)(lVar4 + 0x158);
    *(undefined8 *)(lVar4 + 0x1c0) = *(undefined8 *)(lVar4 + 0x150);
    *(undefined8 *)(lVar4 + 0x1d8) = *(undefined8 *)(lVar4 + 0x168);
    *(undefined8 *)(lVar4 + 0x1d0) = *(undefined8 *)(lVar4 + 0x160);
    if (*(char *)(*(long *)(param_1 + 0x38) + 0x19c) == '\0') {
      *(undefined1 *)(*(long *)(param_1 + 0x38) + 0x19c) = 1;
    }
  }
  return;
}

// ==== Aska::DynamicsCircleWind::CreateParticleObject()
// vaddr 0x233996c | ghidra 0x243996c | size 52 | symbol _ZN4Aska18DynamicsCircleWind20CreateParticleObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska18DynamicsCircleWind20CreateParticleObjectEv(long param_1)

{
  long *plVar1;
  
  plVar1 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x60,PTR__ZSt7nothrow_02cb9a80);
  if (plVar1 != (long *)0x0) {
    *plVar1 = (long)(PTR__ZTVN4Aska26ParticleDynamicsCircleWindE_02cc0ab8 + 0x10);
    plVar1[1] = param_1;
  }
  return;
}

// ==== Aska::DynamicsCircleWind::Clone(Aska::IAnimatable const*)
// vaddr 0x23399a0 | ghidra 0x24399a0 | size 8 | symbol _ZN4Aska18DynamicsCircleWind5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska18DynamicsCircleWind5CloneEPKNS_11IAnimatableE(void)

{
  return 0;
}

// ==== Aska::DynamicsCircleWind::CreateClone(Aska::IAnimatable const*)
// vaddr 0x23399a8 | ghidra 0x24399a8 | size 292 | symbol _ZN4Aska18DynamicsCircleWind11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska18DynamicsCircleWind11CreateCloneEPKNS_11IAnimatableE(void)

{
  long *plVar1;
  long lVar2;
  undefined *puVar3;
  long *plVar4;
  long lVar5;
  
  plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x240,PTR__ZSt7nothrow_02cb9a80);
  if (plVar4 != (long *)0x0) {
    Aska::DynamicsForceEmitter::DynamicsForceEmitter()(plVar4);
    plVar4[0x43] = 0;
    plVar4[0x42] = 0;
    plVar4[0x41] = 0;
    *(undefined4 *)(plVar4 + 0x46) = 0x100;
    *(undefined1 *)((long)plVar4 + 0x234) = 1;
    plVar4[0x45] = 0;
    plVar4[0x44] = 0;
    lVar5 = _UNK_027dbb38;
    lVar2 = _UNK_027dbb30;
    plVar4[0x40] = (long)(PTR__ZTVN4Aska18DynamicsCircleWind11_CircleWindE_02cbc418 + 0x10);
    puVar3 = PTR__ZTVN4Aska18DynamicsCircleWindE_02cc1cb8;
    *(undefined1 *)((long)plVar4 + 0x236) = 0;
    plVar4[0x47] = (long)plVar4;
    plVar4[0x3d] = lVar5;
    plVar4[0x3c] = lVar2;
    *plVar4 = (long)(puVar3 + 0x10);
    Aska::DynamicsHandler::~DynamicsHandler()(plVar4 + 0x40);
    plVar1 = plVar4 + 6;
    *plVar4 = (long)(PTR__ZTVN4Aska18HierarchicalObjectE_02cb6bb0 + 0x10);
    Aska::HierarchicalObjectContainer::DetachFromParent()(plVar1);
    if ((*(byte *)(plVar4 + 0x25) & 1) == 0) {
      Aska::HierarchicalObjectContainer::UpdateHierarchically()(plVar1);
    }
    if ((code *)plVar4[5] != (code *)0x0) {
      (*(code *)plVar4[5])(plVar4);
    }
    if (plVar4[0x30] != 0) {
      operator delete(void*)();
      plVar4[0x30] = 0;
    }
    plVar4[6] = (long)(PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8 + 0x10);
    lVar2 = plVar4[0x22];
    while (lVar2 != 0) {
      lVar5 = *(long *)(lVar2 + 8);
      *(undefined8 *)(lVar2 + 8) = 0;
      *(undefined8 *)(lVar2 + 0x10) = 0;
      lVar2 = lVar5;
    }
    Aska::IAnimatable::~IAnimatable()(plVar1);
    Aska::Task::~Task()(plVar4);
    operator delete(void*)(plVar4);
  }
  return 0;
}

// ==== Aska::DynamicsCircleWind::Get(unsigned long, void*) const
// vaddr 0x2339acc | ghidra 0x2439acc | size 128 | symbol _ZNK4Aska18DynamicsCircleWind3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska18DynamicsCircleWind3GetEmPv(long param_1,ulong param_2,undefined4 *param_3)

{
  ulong uVar1;
  undefined4 uVar2;
  
  uVar1 = Aska::HierarchicalObject::Get(unsigned long, void*) const();
  if ((uVar1 & 1) == 0) {
    if ((param_2 & 0xffff00000000) != 0) {
code_r0x02439b40:
      return 0;
    }
    switch((uint)param_2 & 0xffff) {
    case 0x15:
      uVar2 = *(undefined4 *)(param_1 + 0x1f0);
      break;
    case 0x16:
      uVar2 = *(undefined4 *)(param_1 + 500);
      break;
    case 0x17:
      uVar2 = *(undefined4 *)(param_1 + 0x1f8);
      break;
    case 0x18:
      uVar2 = *(undefined4 *)(param_1 + 0x1fc);
      break;
    default:
      goto code_r0x02439b40;
    }
    *param_3 = uVar2;
  }
  return 1;
}

// ==== Aska::DynamicsCircleWind::Set(unsigned long, void const*)
// vaddr 0x2339b4c | ghidra 0x2439b4c | size 144 | symbol _ZN4Aska18DynamicsCircleWind3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska18DynamicsCircleWind3SetEmPKv(long param_1,ulong param_2,undefined4 *param_3)

{
  ulong uVar1;
  undefined8 uVar2;
  
  uVar1 = Aska::HierarchicalObject::Set(unsigned long, void const*)();
  if ((uVar1 & 1) != 0) goto code_r0x02439b68;
  if ((param_2 & 0xffff00000000) == 0) {
    switch((uint)param_2 & 0xffff) {
    case 0x15:
      *(undefined4 *)(param_1 + 0x1f0) = *param_3;
      break;
    case 0x16:
      *(undefined4 *)(param_1 + 500) = *param_3;
      break;
    case 0x17:
      *(undefined4 *)(param_1 + 0x1f8) = *param_3;
      break;
    case 0x18:
      *(undefined4 *)(param_1 + 0x1fc) = *param_3;
      break;
    default:
      goto code_r0x02439b78;
    }
code_r0x02439b68:
    uVar2 = 1;
  }
  else {
code_r0x02439b78:
    uVar2 = 0;
  }
  return uVar2;
}

// ==== Aska::DynamicsAcceleration::_Acceleration::Run(int)
// vaddr 0x2339bdc | ghidra 0x2439bdc | size 112 | symbol _ZN4Aska20DynamicsAcceleration13_Acceleration3RunEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20DynamicsAcceleration13_Acceleration3RunEi(long param_1)

{
  long *plVar1;
  undefined8 uVar2;
  
  plVar1 = *(long **)(param_1 + 0x38);
  if (plVar1 != (long *)0x0) {
    if ((*(byte *)(plVar1 + 0x25) & 1) != 0) {
      (**(code **)(*plVar1 + 0xa8))();
      plVar1 = *(long **)(param_1 + 0x38);
    }
    uVar2 = (**(code **)(*plVar1 + 0x98))();
    Aska::Vector::ApplyMatrixNoTransport(Aska::Vector*, Aska::Matrix const*) const(plVar1 + 0x34,plVar1 + 0x36,uVar2);
    if (*(char *)(*(long *)(param_1 + 0x38) + 0x19c) == '\0') {
      *(undefined1 *)(*(long *)(param_1 + 0x38) + 0x19c) = 1;
    }
  }
  return;
}

// ==== Aska::DynamicsAcceleration::CreateParticleObject()
// vaddr 0x2339c4c | ghidra 0x2439c4c | size 52 | symbol _ZN4Aska20DynamicsAcceleration20CreateParticleObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20DynamicsAcceleration20CreateParticleObjectEv(long param_1)

{
  long *plVar1;
  
  plVar1 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80);
  if (plVar1 != (long *)0x0) {
    *plVar1 = (long)(PTR__ZTVN4Aska28ParticleDynamicsAccelerationE_02cb8710 + 0x10);
    plVar1[1] = param_1;
  }
  return;
}

// ==== Aska::DynamicsAcceleration::Clone(Aska::IAnimatable const*)
// vaddr 0x2339c80 | ghidra 0x2439c80 | size 8 | symbol _ZN4Aska20DynamicsAcceleration5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska20DynamicsAcceleration5CloneEPKNS_11IAnimatableE(void)

{
  return 0;
}

// ==== Aska::DynamicsAcceleration::CreateClone(Aska::IAnimatable const*)
// vaddr 0x2339c88 | ghidra 0x2439c88 | size 268 | symbol _ZN4Aska20DynamicsAcceleration11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska20DynamicsAcceleration11CreateCloneEPKNS_11IAnimatableE(void)

{
  long *plVar1;
  long lVar2;
  undefined *puVar3;
  undefined *puVar4;
  long *plVar5;
  long lVar6;
  
  plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x200,PTR__ZSt7nothrow_02cb9a80);
  if (plVar5 != (long *)0x0) {
    Aska::DynamicsForceEmitter::DynamicsForceEmitter()(plVar5);
    plVar5[0x3a] = 0;
    plVar5[0x3b] = 0;
    *(undefined1 *)((long)plVar5 + 0x1f6) = 0;
    plVar5[0x3c] = 0;
    plVar5[0x3d] = 0;
    *(undefined4 *)(plVar5 + 0x3e) = 0x100;
    puVar3 = PTR__ZTVN4Aska20DynamicsAcceleration13_AccelerationE_02cbf360;
    plVar5[0x3f] = (long)plVar5;
    *(undefined1 *)((long)plVar5 + 500) = 1;
    puVar4 = PTR__ZTVN4Aska20DynamicsAccelerationE_02cc2838;
    plVar5[0x38] = (long)(puVar3 + 0x10);
    plVar5[0x39] = 0;
    *plVar5 = (long)(puVar4 + 0x10);
    Aska::DynamicsHandler::~DynamicsHandler()(plVar5 + 0x38);
    plVar1 = plVar5 + 6;
    *plVar5 = (long)(PTR__ZTVN4Aska18HierarchicalObjectE_02cb6bb0 + 0x10);
    Aska::HierarchicalObjectContainer::DetachFromParent()(plVar1);
    if ((*(byte *)(plVar5 + 0x25) & 1) == 0) {
      Aska::HierarchicalObjectContainer::UpdateHierarchically()(plVar1);
    }
    if ((code *)plVar5[5] != (code *)0x0) {
      (*(code *)plVar5[5])(plVar5);
    }
    if (plVar5[0x30] != 0) {
      operator delete(void*)();
      plVar5[0x30] = 0;
    }
    plVar5[6] = (long)(PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8 + 0x10);
    lVar2 = plVar5[0x22];
    while (lVar2 != 0) {
      lVar6 = *(long *)(lVar2 + 8);
      *(undefined8 *)(lVar2 + 8) = 0;
      *(undefined8 *)(lVar2 + 0x10) = 0;
      lVar2 = lVar6;
    }
    Aska::IAnimatable::~IAnimatable()(plVar1);
    Aska::Task::~Task()(plVar5);
    operator delete(void*)(plVar5);
  }
  return 0;
}

// ==== Aska::DynamicsAcceleration::Get(unsigned long, void*) const
// vaddr 0x2339d94 | ghidra 0x2439d94 | size 96 | symbol _ZNK4Aska20DynamicsAcceleration3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska20DynamicsAcceleration3GetEmPv(long param_1,ulong param_2,undefined4 *param_3)

{
  ulong uVar1;
  
  uVar1 = Aska::HierarchicalObject::Get(unsigned long, void*) const();
  if ((uVar1 & 1) == 0) {
    if ((param_2 & 0xffff0000ffff) != 0x19) {
      return 0;
    }
    *param_3 = *(undefined4 *)(param_1 + 0x1a0);
    param_3[1] = *(undefined4 *)(param_1 + 0x1a4);
    param_3[2] = *(undefined4 *)(param_1 + 0x1a8);
    param_3[3] = *(undefined4 *)(param_1 + 0x1ac);
  }
  return 1;
}

// ==== Aska::DynamicsAcceleration::Set(unsigned long, void const*)
// vaddr 0x2339df4 | ghidra 0x2439df4 | size 96 | symbol _ZN4Aska20DynamicsAcceleration3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska20DynamicsAcceleration3SetEmPKv(long param_1,ulong param_2,undefined4 *param_3)

{
  ulong uVar1;
  
  uVar1 = Aska::HierarchicalObject::Set(unsigned long, void const*)();
  if ((uVar1 & 1) == 0) {
    if ((param_2 & 0xffff0000ffff) != 0x19) {
      return 0;
    }
    *(undefined4 *)(param_1 + 0x1a0) = *param_3;
    *(undefined4 *)(param_1 + 0x1a4) = param_3[1];
    *(undefined4 *)(param_1 + 0x1a8) = param_3[2];
    *(undefined4 *)(param_1 + 0x1ac) = param_3[3];
  }
  return 1;
}

// ==== Aska::DynamicsAirFriction::_AirFriction::Run(int)
// vaddr 0x2339e54 | ghidra 0x2439e54 | size 72 | symbol _ZN4Aska19DynamicsAirFriction12_AirFriction3RunEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsAirFriction12_AirFriction3RunEi(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x38);
  if (plVar1 != (long *)0x0) {
    if ((*(byte *)(plVar1 + 0x25) & 1) != 0) {
      (**(code **)(*plVar1 + 0xa8))();
      plVar1 = *(long **)(param_1 + 0x38);
    }
    if (*(char *)((long)plVar1 + 0x19c) == '\0') {
      *(undefined1 *)((long)plVar1 + 0x19c) = 1;
      return;
    }
  }
  return;
}

// ==== Aska::DynamicsAirFriction::CreateParticleObject()
// vaddr 0x2339e9c | ghidra 0x2439e9c | size 52 | symbol _ZN4Aska19DynamicsAirFriction20CreateParticleObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsAirFriction20CreateParticleObjectEv(long param_1)

{
  long *plVar1;
  
  plVar1 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x10,PTR__ZSt7nothrow_02cb9a80);
  if (plVar1 != (long *)0x0) {
    *plVar1 = (long)(PTR__ZTVN4Aska27ParticleDynamicsAirFrictionE_02cbe860 + 0x10);
    plVar1[1] = param_1;
  }
  return;
}

// ==== Aska::DynamicsAirFriction::Clone(Aska::IAnimatable const*)
// vaddr 0x2339ed0 | ghidra 0x2439ed0 | size 8 | symbol _ZN4Aska19DynamicsAirFriction5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska19DynamicsAirFriction5CloneEPKNS_11IAnimatableE(void)

{
  return 0;
}

// ==== Aska::DynamicsAirFriction::CreateClone(Aska::IAnimatable const*)
// vaddr 0x2339ed8 | ghidra 0x2439ed8 | size 268 | symbol _ZN4Aska19DynamicsAirFriction11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska19DynamicsAirFriction11CreateCloneEPKNS_11IAnimatableE(void)

{
  long *plVar1;
  long lVar2;
  undefined *puVar3;
  undefined *puVar4;
  long *plVar5;
  long lVar6;
  
  plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x1f0,PTR__ZSt7nothrow_02cb9a80);
  if (plVar5 != (long *)0x0) {
    Aska::DynamicsForceEmitter::DynamicsForceEmitter()(plVar5);
    plVar5[0x36] = 0;
    plVar5[0x37] = 0;
    *(undefined1 *)((long)plVar5 + 0x1d6) = 0;
    plVar5[0x38] = 0;
    plVar5[0x39] = 0;
    *(undefined4 *)(plVar5 + 0x3a) = 0x100;
    puVar3 = PTR__ZTVN4Aska19DynamicsAirFriction12_AirFrictionE_02cbb570;
    plVar5[0x3b] = (long)plVar5;
    *(undefined1 *)((long)plVar5 + 0x1d4) = 1;
    puVar4 = PTR__ZTVN4Aska19DynamicsAirFrictionE_02cc09a8;
    plVar5[0x34] = (long)(puVar3 + 0x10);
    plVar5[0x35] = 0;
    *plVar5 = (long)(puVar4 + 0x10);
    Aska::DynamicsHandler::~DynamicsHandler()(plVar5 + 0x34);
    plVar1 = plVar5 + 6;
    *plVar5 = (long)(PTR__ZTVN4Aska18HierarchicalObjectE_02cb6bb0 + 0x10);
    Aska::HierarchicalObjectContainer::DetachFromParent()(plVar1);
    if ((*(byte *)(plVar5 + 0x25) & 1) == 0) {
      Aska::HierarchicalObjectContainer::UpdateHierarchically()(plVar1);
    }
    if ((code *)plVar5[5] != (code *)0x0) {
      (*(code *)plVar5[5])(plVar5);
    }
    if (plVar5[0x30] != 0) {
      operator delete(void*)();
      plVar5[0x30] = 0;
    }
    plVar5[6] = (long)(PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8 + 0x10);
    lVar2 = plVar5[0x22];
    while (lVar2 != 0) {
      lVar6 = *(long *)(lVar2 + 8);
      *(undefined8 *)(lVar2 + 8) = 0;
      *(undefined8 *)(lVar2 + 0x10) = 0;
      lVar2 = lVar6;
    }
    Aska::IAnimatable::~IAnimatable()(plVar1);
    Aska::Task::~Task()(plVar5);
    operator delete(void*)(plVar5);
  }
  return 0;
}

// ==== Aska::DynamicsAirFriction::Get(unsigned long, void*) const
// vaddr 0x2339fe4 | ghidra 0x2439fe4 | size 96 | symbol _ZNK4Aska19DynamicsAirFriction3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska19DynamicsAirFriction3GetEmPv(long param_1,ulong param_2,undefined4 *param_3)

{
  uint uVar1;
  ulong uVar2;
  undefined4 uVar3;
  
  uVar2 = Aska::HierarchicalObject::Get(unsigned long, void*) const();
  if ((uVar2 & 1) == 0) {
    if ((param_2 & 0xffff00000000) != 0) {
      return 0;
    }
    uVar1 = (uint)param_2 & 0xffff;
    if (uVar1 == 0x1b) {
      uVar3 = *(undefined4 *)(param_1 + 0x1e4);
    }
    else {
      if (uVar1 != 0x1a) {
        return 0;
      }
      uVar3 = *(undefined4 *)(param_1 + 0x1e0);
    }
    *param_3 = uVar3;
  }
  return 1;
}

// ==== Aska::DynamicsAirFriction::Set(unsigned long, void const*)
// vaddr 0x233a044 | ghidra 0x243a044 | size 104 | symbol _ZN4Aska19DynamicsAirFriction3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska19DynamicsAirFriction3SetEmPKv(long param_1,ulong param_2,undefined4 *param_3)

{
  uint uVar1;
  ulong uVar2;
  
  uVar2 = Aska::HierarchicalObject::Set(unsigned long, void const*)();
  if ((uVar2 & 1) == 0) {
    if ((param_2 & 0xffff00000000) != 0) {
      return 0;
    }
    uVar1 = (uint)param_2 & 0xffff;
    if (uVar1 == 0x1b) {
      *(undefined4 *)(param_1 + 0x1e4) = *param_3;
    }
    else {
      if (uVar1 != 0x1a) {
        return 0;
      }
      *(undefined4 *)(param_1 + 0x1e0) = *param_3;
    }
  }
  return 1;
}

// ==== Aska::DynamicsGravitation::_Gravitation::Run(int)
// vaddr 0x233a0ac | ghidra 0x243a0ac | size 108 | symbol _ZN4Aska19DynamicsGravitation12_Gravitation3RunEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsGravitation12_Gravitation3RunEi(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x38);
  if (plVar1 != (long *)0x0) {
    if ((*(byte *)(plVar1 + 0x25) & 1) != 0) {
      (**(code **)(*plVar1 + 0xa8))();
      plVar1 = *(long **)(param_1 + 0x38);
    }
    *(undefined4 *)(plVar1 + 0x3c) = *(undefined4 *)((long)plVar1 + 0x4c);
    *(undefined4 *)((long)plVar1 + 0x1e4) = *(undefined4 *)((long)plVar1 + 0x5c);
    *(undefined4 *)(plVar1 + 0x3d) = *(undefined4 *)((long)plVar1 + 0x6c);
    *(undefined4 *)((long)plVar1 + 0x1ec) = 0x3f800000;
    if (*(char *)(*(long *)(param_1 + 0x38) + 0x19c) == '\0') {
      *(undefined1 *)(*(long *)(param_1 + 0x38) + 0x19c) = 1;
      return;
    }
  }
  return;
}

// ==== Aska::DynamicsGravitation::CreateParticleObject()
// vaddr 0x233a118 | ghidra 0x243a118 | size 52 | symbol _ZN4Aska19DynamicsGravitation20CreateParticleObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsGravitation20CreateParticleObjectEv(long param_1)

{
  long *plVar1;
  
  plVar1 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80);
  if (plVar1 != (long *)0x0) {
    *plVar1 = (long)(PTR__ZTVN4Aska27ParticleDynamicsGravitationE_02cc3bb8 + 0x10);
    plVar1[1] = param_1;
  }
  return;
}

// ==== Aska::DynamicsGravitation::Clone(Aska::IAnimatable const*)
// vaddr 0x233a14c | ghidra 0x243a14c | size 8 | symbol _ZN4Aska19DynamicsGravitation5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska19DynamicsGravitation5CloneEPKNS_11IAnimatableE(void)

{
  return 0;
}

// ==== Aska::DynamicsGravitation::CreateClone(Aska::IAnimatable const*)
// vaddr 0x233a154 | ghidra 0x243a154 | size 268 | symbol _ZN4Aska19DynamicsGravitation11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska19DynamicsGravitation11CreateCloneEPKNS_11IAnimatableE(void)

{
  long *plVar1;
  long lVar2;
  undefined *puVar3;
  undefined *puVar4;
  long *plVar5;
  long lVar6;
  
  plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x200,PTR__ZSt7nothrow_02cb9a80);
  if (plVar5 != (long *)0x0) {
    Aska::DynamicsForceEmitter::DynamicsForceEmitter()(plVar5);
    plVar5[0x36] = 0;
    plVar5[0x37] = 0;
    *(undefined1 *)((long)plVar5 + 0x1d6) = 0;
    plVar5[0x38] = 0;
    plVar5[0x39] = 0;
    *(undefined4 *)(plVar5 + 0x3a) = 0x100;
    puVar4 = PTR__ZTVN4Aska19DynamicsGravitation12_GravitationE_02cc4c40;
    plVar5[0x3b] = (long)plVar5;
    *(undefined1 *)((long)plVar5 + 0x1d4) = 1;
    puVar3 = PTR__ZTVN4Aska19DynamicsGravitationE_02cb9640;
    plVar5[0x34] = (long)(puVar4 + 0x10);
    plVar5[0x35] = 0;
    *plVar5 = (long)(puVar3 + 0x10);
    Aska::DynamicsHandler::~DynamicsHandler()(plVar5 + 0x34);
    plVar1 = plVar5 + 6;
    *plVar5 = (long)(PTR__ZTVN4Aska18HierarchicalObjectE_02cb6bb0 + 0x10);
    Aska::HierarchicalObjectContainer::DetachFromParent()(plVar1);
    if ((*(byte *)(plVar5 + 0x25) & 1) == 0) {
      Aska::HierarchicalObjectContainer::UpdateHierarchically()(plVar1);
    }
    if ((code *)plVar5[5] != (code *)0x0) {
      (*(code *)plVar5[5])(plVar5);
    }
    if (plVar5[0x30] != 0) {
      operator delete(void*)();
      plVar5[0x30] = 0;
    }
    plVar5[6] = (long)(PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8 + 0x10);
    lVar2 = plVar5[0x22];
    while (lVar2 != 0) {
      lVar6 = *(long *)(lVar2 + 8);
      *(undefined8 *)(lVar2 + 8) = 0;
      *(undefined8 *)(lVar2 + 0x10) = 0;
      lVar2 = lVar6;
    }
    Aska::IAnimatable::~IAnimatable()(plVar1);
    Aska::Task::~Task()(plVar5);
    operator delete(void*)(plVar5);
  }
  return 0;
}

// ==== Aska::DynamicsGravitation::Get(unsigned long, void*) const
// vaddr 0x233a260 | ghidra 0x243a260 | size 84 | symbol _ZNK4Aska19DynamicsGravitation3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZNK4Aska19DynamicsGravitation3GetEmPv(long param_1,ulong param_2,float *param_3)

{
  ulong uVar1;
  
  uVar1 = Aska::HierarchicalObject::Get(unsigned long, void*) const();
  if ((uVar1 & 1) == 0) {
    if ((param_2 & 0xffff0000ffff) != 0x1c) {
      return 0;
    }
    *param_3 = *(float *)(param_1 + 0x1f0) / _UNK_029c7444;
  }
  return 1;
}

// ==== Aska::DynamicsGravitation::Set(unsigned long, void const*)
// vaddr 0x233a2b4 | ghidra 0x243a2b4 | size 84 | symbol _ZN4Aska19DynamicsGravitation3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska19DynamicsGravitation3SetEmPKv(long param_1,ulong param_2,float *param_3)

{
  ulong uVar1;
  
  uVar1 = Aska::HierarchicalObject::Set(unsigned long, void const*)();
  if ((uVar1 & 1) == 0) {
    if ((param_2 & 0xffff0000ffff) != 0x1c) {
      return 0;
    }
    *(float *)(param_1 + 0x1f0) = *param_3 * _UNK_029c7444;
  }
  return 1;
}

// ==== Aska::DynamicsForceEmitter::~DynamicsForceEmitter()
// vaddr 0x233a308 | ghidra 0x243a308 | size 24 | symbol _ZN4Aska20DynamicsForceEmitterD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20DynamicsForceEmitterD0Ev(undefined8 param_1)

{
  Aska::HierarchicalObject::~HierarchicalObject()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsForceEmitter::GetClassID(int) const
// vaddr 0x233a320 | ghidra 0x243a320 | size 88 | symbol _ZNK4Aska20DynamicsForceEmitter10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska20DynamicsForceEmitter10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf111f140;
  }
  if (param_2 == 1) {
    return 0xf000f002f111;
  }
  uVar2 = 0xf000f001;
  if (param_2 != 3) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf000f001f002;
  if (param_2 != 2) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::DynamicsForceEmitter::CreateClone(Aska::IAnimatable const*)
// vaddr 0x233a378 | ghidra 0x243a378 | size 8 | symbol _ZN4Aska20DynamicsForceEmitter11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska20DynamicsForceEmitter11CreateCloneEPKNS_11IAnimatableE(void)

{
  return 0;
}

// ==== Aska::DynamicsForceEmitter::GetDynamicsHandler()
// vaddr 0x233a380 | ghidra 0x243a380 | size 8 | symbol _ZN4Aska20DynamicsForceEmitter18GetDynamicsHandlerEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska20DynamicsForceEmitter18GetDynamicsHandlerEv(void)

{
  return 0;
}

// ==== Aska::DynamicsForceEmitter::EmitForce(float, Aska::Vector const*, Aska::Vector*, float)
// vaddr 0x233a388 | ghidra 0x243a388 | size 4 | symbol _ZN4Aska20DynamicsForceEmitter9EmitForceEfPKNS_6VectorEPS1_f | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20DynamicsForceEmitter9EmitForceEfPKNS_6VectorEPS1_f(void)

{
  return;
}

// ==== Aska::DynamicsForceEmitter::SetDispatchHandle(int, unsigned long)
// vaddr 0x233a38c | ghidra 0x243a38c | size 48 | symbol _ZN4Aska20DynamicsForceEmitter17SetDispatchHandleEim | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20DynamicsForceEmitter17SetDispatchHandleEim
               (long *param_1,undefined4 param_2,undefined8 param_3)

{
  undefined8 uVar1;
  
  uVar1 = (**(code **)(*param_1 + 0x160))();
  (*(code *)PTR__ZN4Aska15DynamicsHandler17SetDispatchHandleEim_02cb2448)(uVar1,param_2,param_3);
  return;
}

// ==== Aska::DynamicsForceEmitter::GetDispatchHandle(int)
// vaddr 0x233a3bc | ghidra 0x243a3bc | size 36 | symbol _ZN4Aska20DynamicsForceEmitter17GetDispatchHandleEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska20DynamicsForceEmitter17GetDispatchHandleEi(long *param_1,int param_2)

{
  long lVar1;
  
  lVar1 = (**(code **)(*param_1 + 0x160))();
  return *(undefined8 *)(lVar1 + (long)param_2 * 8 + 0x20);
}

// ==== Aska::DynamicsForceEmitter::CreateParticleObject()
// vaddr 0x233a3e0 | ghidra 0x243a3e0 | size 8 | symbol _ZN4Aska20DynamicsForceEmitter20CreateParticleObjectEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska20DynamicsForceEmitter20CreateParticleObjectEv(void)

{
  return 0;
}

// ==== Aska::DynamicsWorldWind::_WorldWind::~_WorldWind()
// vaddr 0x233a3e8 | ghidra 0x243a3e8 | size 24 | symbol _ZN4Aska17DynamicsWorldWind10_WorldWindD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17DynamicsWorldWind10_WorldWindD0Ev(undefined8 param_1)

{
  Aska::DynamicsHandler::~DynamicsHandler()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsWorldWind::~DynamicsWorldWind()
// vaddr 0x233a400 | ghidra 0x243a400 | size 44 | symbol _ZN4Aska17DynamicsWorldWindD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17DynamicsWorldWindD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska17DynamicsWorldWindE_02cc3998 + 0x10);
  Aska::DynamicsHandler::~DynamicsHandler()(param_1 + 0x38);
  (*(code *)PTR__ZN4Aska18HierarchicalObjectD2Ev_02ca75e8)(param_1);
  return;
}

// ==== Aska::DynamicsWorldWind::~DynamicsWorldWind()
// vaddr 0x233a42c | ghidra 0x243a42c | size 52 | symbol _ZN4Aska17DynamicsWorldWindD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17DynamicsWorldWindD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska17DynamicsWorldWindE_02cc3998 + 0x10);
  Aska::DynamicsHandler::~DynamicsHandler()(param_1 + 0x38);
  Aska::HierarchicalObject::~HierarchicalObject()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsWorldWind::GetClassID(int) const
// vaddr 0x233a460 | ghidra 0x243a460 | size 68 | symbol _ZNK4Aska17DynamicsWorldWind10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska17DynamicsWorldWind10GetClassIDEi(undefined8 param_1,uint param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 < 3) {
    return *(undefined8 *)(&UNK_029e34c0 + (long)(int)param_2 * 8);
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

// ==== Aska::DynamicsWorldWind::GetDynamicsHandler()
// vaddr 0x233a4a4 | ghidra 0x243a4a4 | size 8 | symbol _ZN4Aska17DynamicsWorldWind18GetDynamicsHandlerEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska17DynamicsWorldWind18GetDynamicsHandlerEv(long param_1)

{
  return param_1 + 0x1c0;
}

// ==== Aska::DynamicsWorldWind::EmitForce(float, Aska::Vector const*, Aska::Vector*, float)
// vaddr 0x233a4ac | ghidra 0x243a4ac | size 72 | symbol _ZN4Aska17DynamicsWorldWind9EmitForceEfPKNS_6VectorEPS1_f | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska17DynamicsWorldWind9EmitForceEfPKNS_6VectorEPS1_f
               (float param_1,float param_2,long param_3,undefined8 param_4,float *param_5)

{
  float fVar1;
  
  fVar1 = param_1 * _UNK_027ebde0 *
          (*(float *)(param_3 + 0x1b0) + *(float *)(param_3 + 0x1b4) * param_2);
  *param_5 = *(float *)(param_3 + 0x1a0) * fVar1;
  param_5[1] = *(float *)(param_3 + 0x1a4) * fVar1;
  param_5[2] = fVar1 * *(float *)(param_3 + 0x1a8);
  return;
}

// ==== Aska::DynamicsOmniWind::_OmniWind::~_OmniWind()
// vaddr 0x233a4f4 | ghidra 0x243a4f4 | size 24 | symbol _ZN4Aska16DynamicsOmniWind9_OmniWindD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16DynamicsOmniWind9_OmniWindD0Ev(undefined8 param_1)

{
  Aska::DynamicsHandler::~DynamicsHandler()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsOmniWind::~DynamicsOmniWind()
// vaddr 0x233a50c | ghidra 0x243a50c | size 44 | symbol _ZN4Aska16DynamicsOmniWindD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16DynamicsOmniWindD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska16DynamicsOmniWindE_02cc1a60 + 0x10);
  Aska::DynamicsHandler::~DynamicsHandler()(param_1 + 0x38);
  (*(code *)PTR__ZN4Aska18HierarchicalObjectD2Ev_02ca75e8)(param_1);
  return;
}

// ==== Aska::DynamicsOmniWind::~DynamicsOmniWind()
// vaddr 0x233a538 | ghidra 0x243a538 | size 52 | symbol _ZN4Aska16DynamicsOmniWindD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16DynamicsOmniWindD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska16DynamicsOmniWindE_02cc1a60 + 0x10);
  Aska::DynamicsHandler::~DynamicsHandler()(param_1 + 0x38);
  Aska::HierarchicalObject::~HierarchicalObject()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsOmniWind::GetClassID(int) const
// vaddr 0x233a56c | ghidra 0x243a56c | size 68 | symbol _ZNK4Aska16DynamicsOmniWind10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska16DynamicsOmniWind10GetClassIDEi(undefined8 param_1,uint param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 < 3) {
    return *(undefined8 *)(&UNK_029e34e0 + (long)(int)param_2 * 8);
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

// ==== Aska::DynamicsOmniWind::GetDynamicsHandler()
// vaddr 0x233a5b0 | ghidra 0x243a5b0 | size 8 | symbol _ZN4Aska16DynamicsOmniWind18GetDynamicsHandlerEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska16DynamicsOmniWind18GetDynamicsHandlerEv(long param_1)

{
  return param_1 + 0x1c0;
}

// ==== Aska::DynamicsOmniWind::EmitForce(float, Aska::Vector const*, Aska::Vector*, float)
// vaddr 0x233a5b8 | ghidra 0x243a5b8 | size 332 | symbol _ZN4Aska16DynamicsOmniWind9EmitForceEfPKNS_6VectorEPS1_f | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16DynamicsOmniWind9EmitForceEfPKNS_6VectorEPS1_f
               (float param_1,float param_2,long param_3,float *param_4,float *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  fVar1 = *(float *)(param_3 + 0x1b8);
  fVar3 = *param_4 - *(float *)(param_3 + 0x1a0);
  fVar4 = param_4[2] - *(float *)(param_3 + 0x1a8);
  fVar2 = -fVar4;
  if (0.0 <= fVar1) {
    fVar2 = fVar3;
  }
  fVar6 = param_4[1] - *(float *)(param_3 + 0x1a4);
  fVar7 = -fVar1;
  if (0.0 <= fVar1) {
    fVar7 = fVar1;
    fVar3 = fVar4;
  }
  fVar1 = param_4[3];
  fVar5 = fVar3 * fVar3 + fVar6 * fVar6 + fVar2 * fVar2;
  fVar4 = SQRT(fVar5);
  if (NAN(fVar4)) {
    fVar4 = (float)sqrtf(fVar5);
  }
  if (_UNK_027e519c <= fVar4) {
    fVar4 = 1.0 / fVar4;
    fVar2 = fVar4 * fVar2;
    fVar3 = fVar4 * fVar3;
    fVar6 = fVar6 * fVar4;
  }
  param_1 = param_1 * _UNK_027ebde0;
  fVar4 = ((fVar7 * fVar7) / (fVar7 * fVar7 + fVar5)) *
          (*(float *)(param_3 + 0x1b0) + *(float *)(param_3 + 0x1b4) * param_2);
  *param_5 = param_1 * fVar4 * fVar2;
  param_5[1] = param_1 * fVar6 * fVar4;
  param_5[2] = param_1 * fVar4 * fVar3;
  param_5[3] = fVar1;
  return;
}

// ==== Aska::DynamicsOmniWind::GetDefaultTaskLevel() const
// vaddr 0x233a704 | ghidra 0x243a704 | size 8 | symbol _ZNK4Aska16DynamicsOmniWind19GetDefaultTaskLevelEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska16DynamicsOmniWind19GetDefaultTaskLevelEv(void)

{
  return 0x100;
}

// ==== Aska::DynamicsCircleWind::_CircleWind::~_CircleWind()
// vaddr 0x233a70c | ghidra 0x243a70c | size 24 | symbol _ZN4Aska18DynamicsCircleWind11_CircleWindD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska18DynamicsCircleWind11_CircleWindD0Ev(undefined8 param_1)

{
  Aska::DynamicsHandler::~DynamicsHandler()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsCircleWind::~DynamicsCircleWind()
// vaddr 0x233a724 | ghidra 0x243a724 | size 44 | symbol _ZN4Aska18DynamicsCircleWindD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska18DynamicsCircleWindD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska18DynamicsCircleWindE_02cc1cb8 + 0x10);
  Aska::DynamicsHandler::~DynamicsHandler()(param_1 + 0x40);
  (*(code *)PTR__ZN4Aska18HierarchicalObjectD2Ev_02ca75e8)(param_1);
  return;
}

// ==== Aska::DynamicsCircleWind::~DynamicsCircleWind()
// vaddr 0x233a750 | ghidra 0x243a750 | size 52 | symbol _ZN4Aska18DynamicsCircleWindD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska18DynamicsCircleWindD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska18DynamicsCircleWindE_02cc1cb8 + 0x10);
  Aska::DynamicsHandler::~DynamicsHandler()(param_1 + 0x40);
  Aska::HierarchicalObject::~HierarchicalObject()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsCircleWind::GetClassID(int) const
// vaddr 0x233a784 | ghidra 0x243a784 | size 68 | symbol _ZNK4Aska18DynamicsCircleWind10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska18DynamicsCircleWind10GetClassIDEi(undefined8 param_1,uint param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 < 3) {
    return *(undefined8 *)(&UNK_029e3500 + (long)(int)param_2 * 8);
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

// ==== Aska::DynamicsCircleWind::GetDynamicsHandler()
// vaddr 0x233a7c8 | ghidra 0x243a7c8 | size 8 | symbol _ZN4Aska18DynamicsCircleWind18GetDynamicsHandlerEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska18DynamicsCircleWind18GetDynamicsHandlerEv(long param_1)

{
  return param_1 + 0x200;
}

// ==== Aska::DynamicsCircleWind::EmitForce(float, Aska::Vector const*, Aska::Vector*, float)
// vaddr 0x233a7d0 | ghidra 0x243a7d0 | size 244 | symbol _ZN4Aska18DynamicsCircleWind9EmitForceEfPKNS_6VectorEPS1_f | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska18DynamicsCircleWind9EmitForceEfPKNS_6VectorEPS1_f
               (float param_1,float param_2,long param_3,undefined8 param_4,float *param_5)

{
  float fVar1;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  
  Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const(param_4,&fStack_40,param_3 + 0x1a0);
  fVar1 = 0.0;
  if (fStack_40 * fStack_40 + 0.0 + fStack_38 * fStack_38 <=
      *(float *)(param_3 + 0x1f8) * *(float *)(param_3 + 0x1f8)) {
    fVar1 = *(float *)(param_3 + 0x1fc) * *(float *)(param_3 + 0x1fc);
    fVar1 = (fVar1 / (fVar1 + fStack_38 * fStack_38 + fStack_40 * fStack_40 + fStack_3c * fStack_3c)
            ) * (*(float *)(param_3 + 0x1f0) + *(float *)(param_3 + 500) * param_2);
    param_1 = param_1 * _UNK_027ebde0;
    *param_5 = param_1 * *(float *)(param_3 + 0x1e0) * fVar1;
    param_5[1] = param_1 * *(float *)(param_3 + 0x1e4) * fVar1;
    fVar1 = param_1 * fVar1 * *(float *)(param_3 + 0x1e8);
  }
  else {
    param_5[0] = 0.0;
    param_5[1] = 0.0;
    param_5[3] = 1.0;
  }
  param_5[2] = fVar1;
  return;
}

// ==== Aska::DynamicsAcceleration::_Acceleration::~_Acceleration()
// vaddr 0x233a8c4 | ghidra 0x243a8c4 | size 24 | symbol _ZN4Aska20DynamicsAcceleration13_AccelerationD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20DynamicsAcceleration13_AccelerationD0Ev(undefined8 param_1)

{
  Aska::DynamicsHandler::~DynamicsHandler()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsAcceleration::~DynamicsAcceleration()
// vaddr 0x233a8dc | ghidra 0x243a8dc | size 44 | symbol _ZN4Aska20DynamicsAccelerationD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20DynamicsAccelerationD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska20DynamicsAccelerationE_02cc2838 + 0x10);
  Aska::DynamicsHandler::~DynamicsHandler()(param_1 + 0x38);
  (*(code *)PTR__ZN4Aska18HierarchicalObjectD2Ev_02ca75e8)(param_1);
  return;
}

// ==== Aska::DynamicsAcceleration::~DynamicsAcceleration()
// vaddr 0x233a908 | ghidra 0x243a908 | size 52 | symbol _ZN4Aska20DynamicsAccelerationD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20DynamicsAccelerationD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska20DynamicsAccelerationE_02cc2838 + 0x10);
  Aska::DynamicsHandler::~DynamicsHandler()(param_1 + 0x38);
  Aska::HierarchicalObject::~HierarchicalObject()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsAcceleration::GetClassID(int) const
// vaddr 0x233a93c | ghidra 0x243a93c | size 68 | symbol _ZNK4Aska20DynamicsAcceleration10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska20DynamicsAcceleration10GetClassIDEi(undefined8 param_1,uint param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 < 3) {
    return *(undefined8 *)(&UNK_029e3520 + (long)(int)param_2 * 8);
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

// ==== Aska::DynamicsAcceleration::GetDynamicsHandler()
// vaddr 0x233a980 | ghidra 0x243a980 | size 8 | symbol _ZN4Aska20DynamicsAcceleration18GetDynamicsHandlerEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska20DynamicsAcceleration18GetDynamicsHandlerEv(long param_1)

{
  return param_1 + 0x1c0;
}

// ==== Aska::DynamicsAcceleration::EmitForce(float, Aska::Vector const*, Aska::Vector*, float)
// vaddr 0x233a988 | ghidra 0x243a988 | size 4 | symbol _ZN4Aska20DynamicsAcceleration9EmitForceEfPKNS_6VectorEPS1_f | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20DynamicsAcceleration9EmitForceEfPKNS_6VectorEPS1_f(void)

{
  return;
}

// ==== Aska::DynamicsAirFriction::_AirFriction::~_AirFriction()
// vaddr 0x233a98c | ghidra 0x243a98c | size 24 | symbol _ZN4Aska19DynamicsAirFriction12_AirFrictionD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsAirFriction12_AirFrictionD0Ev(undefined8 param_1)

{
  Aska::DynamicsHandler::~DynamicsHandler()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsAirFriction::~DynamicsAirFriction()
// vaddr 0x233a9a4 | ghidra 0x243a9a4 | size 44 | symbol _ZN4Aska19DynamicsAirFrictionD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsAirFrictionD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska19DynamicsAirFrictionE_02cc09a8 + 0x10);
  Aska::DynamicsHandler::~DynamicsHandler()(param_1 + 0x34);
  (*(code *)PTR__ZN4Aska18HierarchicalObjectD2Ev_02ca75e8)(param_1);
  return;
}

// ==== Aska::DynamicsAirFriction::~DynamicsAirFriction()
// vaddr 0x233a9d0 | ghidra 0x243a9d0 | size 52 | symbol _ZN4Aska19DynamicsAirFrictionD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsAirFrictionD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska19DynamicsAirFrictionE_02cc09a8 + 0x10);
  Aska::DynamicsHandler::~DynamicsHandler()(param_1 + 0x34);
  Aska::HierarchicalObject::~HierarchicalObject()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsAirFriction::GetClassID(int) const
// vaddr 0x233aa04 | ghidra 0x243aa04 | size 68 | symbol _ZNK4Aska19DynamicsAirFriction10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska19DynamicsAirFriction10GetClassIDEi(undefined8 param_1,uint param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 < 3) {
    return *(undefined8 *)(&UNK_029e3540 + (long)(int)param_2 * 8);
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

// ==== Aska::DynamicsAirFriction::GetDynamicsHandler()
// vaddr 0x233aa48 | ghidra 0x243aa48 | size 8 | symbol _ZN4Aska19DynamicsAirFriction18GetDynamicsHandlerEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska19DynamicsAirFriction18GetDynamicsHandlerEv(long param_1)

{
  return param_1 + 0x1a0;
}

// ==== Aska::DynamicsAirFriction::EmitForce(float, Aska::Vector const*, Aska::Vector*, float)
// vaddr 0x233aa50 | ghidra 0x243aa50 | size 4 | symbol _ZN4Aska19DynamicsAirFriction9EmitForceEfPKNS_6VectorEPS1_f | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsAirFriction9EmitForceEfPKNS_6VectorEPS1_f(void)

{
  return;
}

// ==== Aska::DynamicsGravitation::_Gravitation::~_Gravitation()
// vaddr 0x233aa54 | ghidra 0x243aa54 | size 24 | symbol _ZN4Aska19DynamicsGravitation12_GravitationD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsGravitation12_GravitationD0Ev(undefined8 param_1)

{
  Aska::DynamicsHandler::~DynamicsHandler()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsGravitation::~DynamicsGravitation()
// vaddr 0x233aa6c | ghidra 0x243aa6c | size 44 | symbol _ZN4Aska19DynamicsGravitationD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsGravitationD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska19DynamicsGravitationE_02cb9640 + 0x10);
  Aska::DynamicsHandler::~DynamicsHandler()(param_1 + 0x34);
  (*(code *)PTR__ZN4Aska18HierarchicalObjectD2Ev_02ca75e8)(param_1);
  return;
}

// ==== Aska::DynamicsGravitation::~DynamicsGravitation()
// vaddr 0x233aa98 | ghidra 0x243aa98 | size 52 | symbol _ZN4Aska19DynamicsGravitationD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsGravitationD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska19DynamicsGravitationE_02cb9640 + 0x10);
  Aska::DynamicsHandler::~DynamicsHandler()(param_1 + 0x34);
  Aska::HierarchicalObject::~HierarchicalObject()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsGravitation::GetClassID(int) const
// vaddr 0x233aacc | ghidra 0x243aacc | size 68 | symbol _ZNK4Aska19DynamicsGravitation10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska19DynamicsGravitation10GetClassIDEi(undefined8 param_1,uint param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 < 3) {
    return *(undefined8 *)(&UNK_029e3560 + (long)(int)param_2 * 8);
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

// ==== Aska::DynamicsGravitation::GetDynamicsHandler()
// vaddr 0x233ab10 | ghidra 0x243ab10 | size 8 | symbol _ZN4Aska19DynamicsGravitation18GetDynamicsHandlerEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska19DynamicsGravitation18GetDynamicsHandlerEv(long param_1)

{
  return param_1 + 0x1a0;
}

// ==== Aska::DynamicsGravitation::EmitForce(float, Aska::Vector const*, Aska::Vector*, float)
// vaddr 0x233ab18 | ghidra 0x243ab18 | size 4 | symbol _ZN4Aska19DynamicsGravitation9EmitForceEfPKNS_6VectorEPS1_f | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsGravitation9EmitForceEfPKNS_6VectorEPS1_f(void)

{
  return;
}

// ==== Aska::DynamicsForceEmitterManager::Add(Aska::DynamicsForceEmitter*)
// vaddr 0x233ab1c | ghidra 0x243ab1c | size 132 | symbol _ZN4Aska27DynamicsForceEmitterManager3AddEPNS_20DynamicsForceEmitterE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27DynamicsForceEmitterManager3AddEPNS_20DynamicsForceEmitterE
               (long param_1,long *param_2)

{
  char cVar1;
  long *plVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0x18);
  param_2[1] = lVar3;
  param_2[2] = param_1 + 0x10;
  *(long **)(param_1 + 0x18) = param_2;
  *(long **)(lVar3 + 0x10) = param_2;
  *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
  plVar2 = (long *)(**(code **)(*param_2 + 0x160))(param_2);
  cVar1 = (**(code **)(*plVar2 + 0x10))();
  if (cVar1 != '\x02') {
    Aska::DynamicsManager::Add(Aska::DynamicsHandler*, unsigned int)(*(undefined8 *)PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38,plVar2,0);
  }
  *(undefined1 *)(param_1 + 0x61) = 1;
  return;
}

// ==== Aska::DynamicsForceEmitterManager::AddTop(Aska::DynamicsForceEmitter*)
// vaddr 0x233aba0 | ghidra 0x243aba0 | size 132 | symbol _ZN4Aska27DynamicsForceEmitterManager6AddTopEPNS_20DynamicsForceEmitterE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27DynamicsForceEmitterManager6AddTopEPNS_20DynamicsForceEmitterE
               (long param_1,long *param_2)

{
  char cVar1;
  long *plVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0x20);
  param_2[1] = param_1 + 0x10;
  param_2[2] = lVar3;
  *(long **)(lVar3 + 8) = param_2;
  *(long **)(param_1 + 0x20) = param_2;
  *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
  plVar2 = (long *)(**(code **)(*param_2 + 0x160))(param_2);
  cVar1 = (**(code **)(*plVar2 + 0x10))();
  if (cVar1 != '\x02') {
    Aska::DynamicsManager::AddTop(Aska::DynamicsHandler*, unsigned int)(*(undefined8 *)PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38,plVar2,0);
  }
  *(undefined1 *)(param_1 + 0x61) = 1;
  return;
}

// ==== Aska::DynamicsForceEmitterManager::Insert(Aska::DynamicsForceEmitter*, Aska::DynamicsForceEmitter*)
// vaddr 0x233ac24 | ghidra 0x243ac24 | size 156 | symbol _ZN4Aska27DynamicsForceEmitterManager6InsertEPNS_20DynamicsForceEmitterES2_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27DynamicsForceEmitterManager6InsertEPNS_20DynamicsForceEmitterES2_
               (long param_1,long *param_2,long *param_3)

{
  char cVar1;
  undefined8 uVar2;
  long *plVar3;
  long lVar4;
  
  lVar4 = param_2[2];
  param_3[1] = (long)param_2;
  param_3[2] = lVar4;
  *(long **)(lVar4 + 8) = param_3;
  param_2[2] = (long)param_3;
  *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
  uVar2 = (**(code **)(*param_2 + 0x160))(param_2);
  plVar3 = (long *)(**(code **)(*param_3 + 0x160))(param_3);
  cVar1 = (**(code **)(*plVar3 + 0x10))();
  if (cVar1 != '\x02') {
    Aska::DynamicsManager::Insert(Aska::DynamicsHandler*, Aska::DynamicsHandler*, unsigned int)(*(undefined8 *)PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38,uVar2,plVar3,0)
    ;
  }
  *(undefined1 *)(param_1 + 0x61) = 1;
  return;
}

// ==== Aska::DynamicsForceEmitterManager::Delete(Aska::DynamicsForceEmitter*)
// vaddr 0x233acc0 | ghidra 0x243acc0 | size 184 | symbol _ZN4Aska27DynamicsForceEmitterManager6DeleteEPNS_20DynamicsForceEmitterE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27DynamicsForceEmitterManager6DeleteEPNS_20DynamicsForceEmitterE
               (long param_1,long *param_2)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  long lVar4;
  long lVar5;
  
  if (0 < *(int *)(param_1 + 0x58)) {
    puVar3 = *(undefined8 **)(param_1 + 0x50);
    puVar1 = puVar3 + *(int *)(param_1 + 0x58);
    do {
      if ((long *)*puVar3 == param_2) {
        *puVar3 = 0;
        if (param_2 == (long *)0x0) goto code_r0x0243ad40;
        goto code_r0x0243ad04;
      }
      puVar3 = puVar3 + 1;
    } while (puVar3 < puVar1);
  }
  if (param_2 != (long *)0x0) {
code_r0x0243ad04:
    if ((long *)(param_1 + 0x10) != param_2) {
      lVar4 = param_2[1];
      lVar5 = param_2[2];
      if (lVar4 != 0) {
        *(long *)(lVar4 + 0x10) = lVar5;
      }
      if (lVar5 != 0) {
        *(long *)(lVar5 + 8) = lVar4;
      }
      if (0 < *(int *)(param_1 + 0x28)) {
        *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + -1;
      }
      param_2[1] = 0;
      param_2[2] = 0;
    }
  }
code_r0x0243ad40:
  uVar2 = (**(code **)(*param_2 + 0x160))(param_2);
  Aska::DynamicsManager::Delete(Aska::DynamicsHandler*)(*(undefined8 *)PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38,uVar2);
  *(undefined1 *)(param_1 + 0x61) = 1;
  return;
}

// ==== Aska::DynamicsForceEmitterManager::RemoveFromRuntimeList(Aska::DynamicsForceEmitter*)
// vaddr 0x233ad78 | ghidra 0x243ad78 | size 56 | symbol _ZN4Aska27DynamicsForceEmitterManager21RemoveFromRuntimeListEPNS_20DynamicsForceEmitterE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27DynamicsForceEmitterManager21RemoveFromRuntimeListEPNS_20DynamicsForceEmitterE
               (long param_1,long param_2)

{
  long *plVar1;
  long *plVar2;
  
  if (0 < *(int *)(param_1 + 0x58)) {
    plVar2 = *(long **)(param_1 + 0x50);
    plVar1 = plVar2 + *(int *)(param_1 + 0x58);
    do {
      if (*plVar2 == param_2) {
        *plVar2 = 0;
        return;
      }
      plVar2 = plVar2 + 1;
    } while (plVar2 < plVar1);
  }
  return;
}

// ==== Aska::DynamicsForceEmitterManager::PreAllocateList(Aska::DynamicsForceEmitter**, int)
// vaddr 0x233adb0 | ghidra 0x243adb0 | size 64 | symbol _ZN4Aska27DynamicsForceEmitterManager15PreAllocateListEPPNS_20DynamicsForceEmitterEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska27DynamicsForceEmitterManager15PreAllocateListEPPNS_20DynamicsForceEmitterEi
               (long param_1,undefined8 param_2,undefined4 param_3)

{
  if (*(long *)(param_1 + 0x48) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x48) = 0;
  }
  *(undefined8 *)(param_1 + 0x50) = param_2;
  *(undefined4 *)(param_1 + 0x5c) = param_3;
  *(undefined2 *)(param_1 + 0x60) = 0x101;
  return;
}

// ==== Aska::DynamicsForceEmitterManager::MakeDynamicsList()
// vaddr 0x233adf0 | ghidra 0x243adf0 | size 192 | symbol _ZN4Aska27DynamicsForceEmitterManager16MakeDynamicsListEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska27DynamicsForceEmitterManager16MakeDynamicsListEv(long param_1)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x61) != '\0') {
    iVar4 = *(int *)(param_1 + 0x28);
    if (*(char *)(param_1 + 0x60) == '\0') {
      if (*(long *)(param_1 + 0x48) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 0x48) = 0;
      }
      if (0 < iVar4) {
        lVar2 = operator new[](unsigned long, unsigned long, bool)(iVar4 << 3,4,1);
        *(long *)(param_1 + 0x48) = lVar2;
        *(long *)(param_1 + 0x50) = lVar2;
        if (lVar2 == 0) {
          *(undefined4 *)(param_1 + 0x58) = 0;
          return 0;
        }
      }
    }
    else if (*(int *)(param_1 + 0x5c) <= iVar4) {
      iVar4 = *(int *)(param_1 + 0x5c);
    }
    *(int *)(param_1 + 0x58) = iVar4;
    if ((0 < iVar4) && (*(long **)(param_1 + 0x50) != (long *)0x0)) {
      lVar2 = *(long *)(param_1 + 0x20);
      if (param_1 + 0x10 != lVar2) {
        lVar3 = (long)iVar4 * 8;
        plVar1 = *(long **)(param_1 + 0x50);
        do {
          lVar3 = lVar3 + -8;
          *plVar1 = lVar2;
          if (lVar3 == 0) break;
          lVar2 = *(long *)(lVar2 + 0x10);
          plVar1 = plVar1 + 1;
        } while (param_1 + 0x10 != lVar2);
      }
    }
    *(undefined1 *)(param_1 + 0x61) = 0;
  }
  return 1;
}

// ==== Aska::DynamicsForceEmitterManager::UpdateWorldWind()
// vaddr 0x233aeb0 | ghidra 0x243aeb0 | size 192 | symbol _ZN4Aska27DynamicsForceEmitterManager15UpdateWorldWindEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska27DynamicsForceEmitterManager15UpdateWorldWindEv(long param_1)

{
  undefined8 uVar1;
  undefined4 uVar2;
  ulong uVar3;
  long *plVar4;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  
  uVar1 = _UNK_027dbb30;
  *(undefined8 *)(param_1 + 0x38) = _UNK_027dbb38;
  *(undefined8 *)(param_1 + 0x30) = uVar1;
  uVar2 = _UNK_029671ec;
  if (0 < *(int *)(param_1 + 0x28)) {
    for (plVar4 = *(long **)(param_1 + 0x20); (long *)(param_1 + 0x10) != plVar4;
        plVar4 = (long *)plVar4[2]) {
      uVar3 = Aska::IAnimatable::IsThisIt(unsigned short) const(plVar4,0xf141);
      if ((uVar3 & 1) != 0) {
        (**(code **)(*plVar4 + 0x168))(uVar2,0,plVar4,0,&fStack_40);
        *(float *)(param_1 + 0x30) = fStack_40 + *(float *)(param_1 + 0x30);
        *(float *)(param_1 + 0x34) = fStack_3c + *(float *)(param_1 + 0x34);
        *(float *)(param_1 + 0x38) = fStack_38 + *(float *)(param_1 + 0x38);
      }
    }
  }
  return;
}
