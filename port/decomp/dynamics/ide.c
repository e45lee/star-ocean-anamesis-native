// port/decomp/dynamics/ide.c: Ghidra decompiles for the dynamics subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 14:42 UTC: tools/decomp.sh '--into' 'dynamics/ide' ' Aska::(IDE\w*|IntegratedDynamics\w*)(<[^(]*>)?::[~\w<>]+\('

// ==== Aska::IntegratedDynamicsEnvironment::Run(int)
// vaddr 0x20a9814 | ghidra 0x21a9814 | size 176 | symbol _ZN4Aska29IntegratedDynamicsEnvironment3RunEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska29IntegratedDynamicsEnvironment3RunEi(long param_1)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  
  if (*(long **)(param_1 + 0x88) != (long *)0x0) {
    if (*(long *)(param_1 + 0x70) != 0) {
      lVar2 = *(long *)(*(long *)(param_1 + 0x70) + 0x10);
      (**(code **)(**(long **)(param_1 + 0x88) + 0x80))();
      while (lVar2 != 0) {
        lVar3 = *(long *)(lVar2 + 0x10);
        (**(code **)(**(long **)(param_1 + 0x88) + 0x80))(*(long **)(param_1 + 0x88),lVar2);
        lVar2 = lVar3;
      }
    }
    Aska::IDEPrimitiveListHandler::Clear()(param_1 + 0x68);
    if ((((*(char *)(param_1 + 0x94) != '\0') && (*(long *)(param_1 + 0x30) != 0)) &&
        (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))(), (uVar1 & 1) != 0)) &&
       (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x18))
                          (*(long **)(param_1 + 0x88),param_1 + 0x28), (uVar1 & 1) != 0)) {
      *(undefined1 *)(param_1 + 0x94) = 0;
    }
  }
  return;
}

// ==== Aska::IntegratedDynamicsEnvironment::IsAvailable()
// vaddr 0x20a98c4 | ghidra 0x21a98c4 | size 16 | symbol _ZN4Aska29IntegratedDynamicsEnvironment11IsAvailableEv | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska29IntegratedDynamicsEnvironment11IsAvailableEv(long param_1)

{
  return *(long *)(param_1 + 0x88) != 0;
}

// ==== Aska::IntegratedDynamicsEnvironment::FrameUpdate()
// vaddr 0x20a98d4 | ghidra 0x21a98d4 | size 80 | symbol _ZN4Aska29IntegratedDynamicsEnvironment11FrameUpdateEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska29IntegratedDynamicsEnvironment11FrameUpdateEv(long param_1)

{
  ulong uVar1;
  
  if ((((*(char *)(param_1 + 0x94) != '\0') && (*(long *)(param_1 + 0x30) != 0)) &&
      (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))(), (uVar1 & 1) != 0)) &&
     (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x18))
                        (*(long **)(param_1 + 0x88),param_1 + 0x28), (uVar1 & 1) != 0)) {
    *(undefined1 *)(param_1 + 0x94) = 0;
  }
  return;
}

// ==== Aska::IntegratedDynamicsEnvironment::Add(Aska::AABB_MinMax*)
// vaddr 0x20a9924 | ghidra 0x21a9924 | size 108 | symbol _ZN4Aska29IntegratedDynamicsEnvironment3AddEPNS_11AABB_MinMaxE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska29IntegratedDynamicsEnvironment3AddEPNS_11AABB_MinMaxE(long param_1,long param_2)

{
  undefined8 uVar1;
  long lVar2;
  long *plVar3;
  
  uVar1 = 0;
  if (((param_2 != 0) && (plVar3 = *(long **)(param_1 + 0x88), plVar3 != (long *)0x0)) &&
     (lVar2 = (**(code **)(*plVar3 + 0x30))(plVar3), uVar1 = 0, lVar2 != 0)) {
    Aska::IDEPrimitiveListHandler::Add(Aska::IDEPrimitiveBase*)(param_1 + 0x48,lVar2);
    *(undefined1 *)(param_1 + 0x94) = 1;
    (**(code **)(**(long **)(param_1 + 0x88) + 0x108))(*(long **)(param_1 + 0x88),0);
    uVar1 = *(undefined8 *)(lVar2 + 0x18);
  }
  return uVar1;
}

// ==== Aska::IntegratedDynamicsEnvironment::Add(Aska::Vector*)
// vaddr 0x20a9990 | ghidra 0x21a9990 | size 108 | symbol _ZN4Aska29IntegratedDynamicsEnvironment3AddEPNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska29IntegratedDynamicsEnvironment3AddEPNS_6VectorE(long param_1,long param_2)

{
  undefined8 uVar1;
  long lVar2;
  long *plVar3;
  
  uVar1 = 0;
  if (((param_2 != 0) && (plVar3 = *(long **)(param_1 + 0x88), plVar3 != (long *)0x0)) &&
     (lVar2 = (**(code **)(*plVar3 + 0x38))(plVar3), uVar1 = 0, lVar2 != 0)) {
    Aska::IDEPrimitiveListHandler::Add(Aska::IDEPrimitiveBase*)(param_1 + 0x48,lVar2);
    *(undefined1 *)(param_1 + 0x94) = 1;
    (**(code **)(**(long **)(param_1 + 0x88) + 0x108))(*(long **)(param_1 + 0x88),0);
    uVar1 = *(undefined8 *)(lVar2 + 0x18);
  }
  return uVar1;
}

// ==== Aska::IntegratedDynamicsEnvironment::Add(Aska::HeightObject*)
// vaddr 0x20a99fc | ghidra 0x21a99fc | size 108 | symbol _ZN4Aska29IntegratedDynamicsEnvironment3AddEPNS_12HeightObjectE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment3AddEPNS_12HeightObjectE(long param_1,long param_2)

{
  undefined8 uVar1;
  long lVar2;
  long *plVar3;
  
  uVar1 = 0;
  if (((param_2 != 0) && (plVar3 = *(long **)(param_1 + 0x88), plVar3 != (long *)0x0)) &&
     (lVar2 = (**(code **)(*plVar3 + 0x40))(plVar3), uVar1 = 0, lVar2 != 0)) {
    Aska::IDEPrimitiveListHandler::Add(Aska::IDEPrimitiveBase*)(param_1 + 0x48,lVar2);
    *(undefined1 *)(param_1 + 0x94) = 1;
    (**(code **)(**(long **)(param_1 + 0x88) + 0x108))(*(long **)(param_1 + 0x88),0);
    uVar1 = *(undefined8 *)(lVar2 + 0x18);
  }
  return uVar1;
}

// ==== Aska::IntegratedDynamicsEnvironment::Add(Aska::CollisionHandler*, void*)
// vaddr 0x20a9a68 | ghidra 0x21a9a68 | size 108 | symbol _ZN4Aska29IntegratedDynamicsEnvironment3AddEPNS_16CollisionHandlerEPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment3AddEPNS_16CollisionHandlerEPv(long param_1,long param_2)

{
  undefined8 uVar1;
  long lVar2;
  long *plVar3;
  
  uVar1 = 0;
  if (((param_2 != 0) && (plVar3 = *(long **)(param_1 + 0x88), plVar3 != (long *)0x0)) &&
     (lVar2 = (**(code **)(*plVar3 + 0x48))(plVar3), uVar1 = 0, lVar2 != 0)) {
    Aska::IDEPrimitiveListHandler::Add(Aska::IDEPrimitiveBase*)(param_1 + 0x48,lVar2);
    *(undefined1 *)(param_1 + 0x94) = 1;
    (**(code **)(**(long **)(param_1 + 0x88) + 0x108))(*(long **)(param_1 + 0x88),0);
    uVar1 = *(undefined8 *)(lVar2 + 0x18);
  }
  return uVar1;
}

// ==== Aska::IntegratedDynamicsEnvironment::Add(Aska::Light*)
// vaddr 0x20a9ad4 | ghidra 0x21a9ad4 | size 108 | symbol _ZN4Aska29IntegratedDynamicsEnvironment3AddEPNS_5LightE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska29IntegratedDynamicsEnvironment3AddEPNS_5LightE(long param_1,long param_2)

{
  undefined8 uVar1;
  long lVar2;
  long *plVar3;
  
  uVar1 = 0;
  if (((param_2 != 0) && (plVar3 = *(long **)(param_1 + 0x88), plVar3 != (long *)0x0)) &&
     (lVar2 = (**(code **)(*plVar3 + 0x50))(plVar3), uVar1 = 0, lVar2 != 0)) {
    Aska::IDEPrimitiveListHandler::Add(Aska::IDEPrimitiveBase*)(param_1 + 0x48,lVar2);
    *(undefined1 *)(param_1 + 0x94) = 1;
    (**(code **)(**(long **)(param_1 + 0x88) + 0x108))(*(long **)(param_1 + 0x88),0);
    uVar1 = *(undefined8 *)(lVar2 + 0x18);
  }
  return uVar1;
}

// ==== Aska::IntegratedDynamicsEnvironment::Set(unsigned long, Aska::AABB_MinMax*)
// vaddr 0x20a9b40 | ghidra 0x21a9b40 | size 48 | symbol _ZN4Aska29IntegratedDynamicsEnvironment3SetEmPNS_11AABB_MinMaxE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment3SetEmPNS_11AABB_MinMaxE
          (long param_1,long param_2,long param_3)

{
  undefined8 uVar1;
  long *plVar2;
  
  if (((param_3 != 0) && (param_2 != 0)) &&
     (plVar2 = *(long **)(param_1 + 0x88), plVar2 != (long *)0x0)) {
    *(undefined1 *)(param_1 + 0x94) = 1;
                    /* WARNING: Could not recover jumptable at 0x021a9b64. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*plVar2 + 0x58))(plVar2);
    return uVar1;
  }
  return 0;
}

// ==== Aska::IntegratedDynamicsEnvironment::Set(unsigned long, Aska::Vector*)
// vaddr 0x20a9b70 | ghidra 0x21a9b70 | size 48 | symbol _ZN4Aska29IntegratedDynamicsEnvironment3SetEmPNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment3SetEmPNS_6VectorE(long param_1,long param_2,long param_3)

{
  undefined8 uVar1;
  long *plVar2;
  
  if (((param_3 != 0) && (param_2 != 0)) &&
     (plVar2 = *(long **)(param_1 + 0x88), plVar2 != (long *)0x0)) {
    *(undefined1 *)(param_1 + 0x94) = 1;
                    /* WARNING: Could not recover jumptable at 0x021a9b94. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*plVar2 + 0x60))(plVar2);
    return uVar1;
  }
  return 0;
}

// ==== Aska::IntegratedDynamicsEnvironment::Set(unsigned long, Aska::HeightObject*)
// vaddr 0x20a9ba0 | ghidra 0x21a9ba0 | size 48 | symbol _ZN4Aska29IntegratedDynamicsEnvironment3SetEmPNS_12HeightObjectE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment3SetEmPNS_12HeightObjectE
          (long param_1,long param_2,long param_3)

{
  undefined8 uVar1;
  long *plVar2;
  
  if (((param_3 != 0) && (param_2 != 0)) &&
     (plVar2 = *(long **)(param_1 + 0x88), plVar2 != (long *)0x0)) {
    *(undefined1 *)(param_1 + 0x94) = 1;
                    /* WARNING: Could not recover jumptable at 0x021a9bc4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*plVar2 + 0x68))(plVar2);
    return uVar1;
  }
  return 0;
}

// ==== Aska::IntegratedDynamicsEnvironment::Set(unsigned long, Aska::CollisionHandler*)
// vaddr 0x20a9bd0 | ghidra 0x21a9bd0 | size 48 | symbol _ZN4Aska29IntegratedDynamicsEnvironment3SetEmPNS_16CollisionHandlerE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment3SetEmPNS_16CollisionHandlerE
          (long param_1,long param_2,long param_3)

{
  undefined8 uVar1;
  long *plVar2;
  
  if (((param_3 != 0) && (param_2 != 0)) &&
     (plVar2 = *(long **)(param_1 + 0x88), plVar2 != (long *)0x0)) {
    *(undefined1 *)(param_1 + 0x94) = 1;
                    /* WARNING: Could not recover jumptable at 0x021a9bf4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*plVar2 + 0x70))(plVar2);
    return uVar1;
  }
  return 0;
}

// ==== Aska::IntegratedDynamicsEnvironment::GetType(unsigned long)
// vaddr 0x20a9c00 | ghidra 0x21a9c00 | size 20 | symbol _ZN4Aska29IntegratedDynamicsEnvironment7GetTypeEm | lib libSOA-3.7.0.so | 2026-10-08
ulong _ZN4Aska29IntegratedDynamicsEnvironment7GetTypeEm(undefined8 param_1,long param_2)

{
  if (param_2 != 0) {
    return (ulong)*(byte *)(param_2 + 0x20);
  }
  return 0xffffffff;
}

// ==== Aska::IntegratedDynamicsEnvironment::SetDirty(unsigned long)
// vaddr 0x20a9c14 | ghidra 0x21a9c14 | size 20 | symbol _ZN4Aska29IntegratedDynamicsEnvironment8SetDirtyEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska29IntegratedDynamicsEnvironment8SetDirtyEm(long param_1,long param_2)

{
  if (param_2 != 0) {
    *(undefined1 *)(param_2 + 0x21) = 1;
    *(undefined1 *)(param_1 + 0x94) = 1;
  }
  return;
}

// ==== Aska::IntegratedDynamicsEnvironment::Delete(unsigned long)
// vaddr 0x20a9c28 | ghidra 0x21a9c28 | size 108 | symbol _ZN4Aska29IntegratedDynamicsEnvironment6DeleteEm | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska29IntegratedDynamicsEnvironment6DeleteEm(long param_1,long param_2)

{
  ulong uVar1;
  long lVar2;
  undefined8 uVar3;
  
  if ((param_2 == 0) || (*(long *)(param_1 + 0x88) == 0)) {
    uVar3 = 0;
  }
  else {
    lVar2 = param_1 + 0x48;
    uVar1 = Aska::IDEPrimitiveListHandler::Exists(Aska::IDEPrimitiveBase*)(lVar2,param_2);
    if ((uVar1 & 1) == 0) {
      lVar2 = param_1 + 0x28;
    }
    Aska::IDEPrimitiveListHandler::Remove(Aska::IDEPrimitiveBase*)(lVar2,param_2);
    Aska::IDEPrimitiveListHandler::Add(Aska::IDEPrimitiveBase*)(param_1 + 0x68,param_2);
    uVar3 = 1;
    *(undefined1 *)(param_1 + 0x94) = 1;
  }
  return uVar3;
}

// ==== Aska::IntegratedDynamicsEnvironment::DeleteAll()
// vaddr 0x20a9c94 | ghidra 0x21a9c94 | size 228 | symbol _ZN4Aska29IntegratedDynamicsEnvironment9DeleteAllEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska29IntegratedDynamicsEnvironment9DeleteAllEv(long param_1)

{
  undefined8 uVar1;
  long lVar2;
  long lVar3;
  
  uVar1 = 0;
  if (*(long **)(param_1 + 0x88) != (long *)0x0) {
    if (*(long *)(param_1 + 0x70) != 0) {
      lVar2 = *(long *)(*(long *)(param_1 + 0x70) + 0x10);
      (**(code **)(**(long **)(param_1 + 0x88) + 0x80))();
      while (lVar2 != 0) {
        lVar3 = *(long *)(lVar2 + 0x10);
        (**(code **)(**(long **)(param_1 + 0x88) + 0x80))(*(long **)(param_1 + 0x88),lVar2);
        lVar2 = lVar3;
      }
    }
    Aska::IDEPrimitiveListHandler::Clear()(param_1 + 0x68);
    lVar2 = *(long *)(param_1 + 0x50);
    while (lVar2 != 0) {
      lVar2 = *(long *)(lVar2 + 0x10);
      (**(code **)(**(long **)(param_1 + 0x88) + 0x80))();
    }
    Aska::IDEPrimitiveListHandler::Clear()(param_1 + 0x48);
    lVar2 = *(long *)(param_1 + 0x30);
    while (lVar2 != 0) {
      lVar2 = *(long *)(lVar2 + 0x10);
      (**(code **)(**(long **)(param_1 + 0x88) + 0x80))();
    }
    Aska::IDEPrimitiveListHandler::Clear()(param_1 + 0x28);
    (**(code **)(**(long **)(param_1 + 0x88) + 0x88))();
    uVar1 = 1;
  }
  return uVar1;
}

// ==== Aska::IntegratedDynamicsEnvironment::IsBelongToSpacePartition(unsigned long)
// vaddr 0x20a9d78 | ghidra 0x21a9d78 | size 28 | symbol _ZN4Aska29IntegratedDynamicsEnvironment24IsBelongToSpacePartitionEm | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment24IsBelongToSpacePartitionEm(long param_1,long param_2)

{
  undefined8 uVar1;
  
  if ((param_2 != 0) && (*(long *)(param_1 + 0x88) != 0)) {
    uVar1 = (*(code *)PTR__ZN4Aska23IDEPrimitiveListHandler6ExistsEPNS_16IDEPrimitiveBaseE_02ca0da8)
                      (param_1 + 0x28);
    return uVar1;
  }
  return 0;
}

// ==== Aska::IntegratedDynamicsEnvironment::SetMemoryManager(Aska::MemoryManager*)
// vaddr 0x20a9d94 | ghidra 0x21a9d94 | size 16 | symbol _ZN4Aska29IntegratedDynamicsEnvironment16SetMemoryManagerEPNS_13MemoryManagerE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska29IntegratedDynamicsEnvironment16SetMemoryManagerEPNS_13MemoryManagerE
               (long param_1,undefined8 param_2)

{
  if (*(long *)(param_1 + 0x88) != 0) {
    *(undefined8 *)(*(long *)(param_1 + 0x88) + 8) = param_2;
  }
  return;
}

// ==== Aska::IntegratedDynamicsEnvironment::Build()
// vaddr 0x20a9da4 | ghidra 0x21a9da4 | size 168 | symbol _ZN4Aska29IntegratedDynamicsEnvironment5BuildEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska29IntegratedDynamicsEnvironment5BuildEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  
  if (*(long *)(param_1 + 0x50) != 0) {
    lVar2 = *(long *)(param_1 + 0x50);
    do {
      lVar3 = *(long *)(lVar2 + 0x10);
      Aska::IDEPrimitiveListHandler::Remove(Aska::IDEPrimitiveBase*)(param_1 + 0x48,lVar2);
      Aska::IDEPrimitiveListHandler::Add(Aska::IDEPrimitiveBase*)(param_1 + 0x28,lVar2);
      lVar2 = lVar3;
    } while (lVar3 != 0);
  }
  if ((((*(char *)(param_1 + 0x94) != '\0') && (*(long *)(param_1 + 0x30) != 0)) &&
      (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))(), (uVar1 & 1) != 0)) &&
     (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x18))
                        (*(long **)(param_1 + 0x88),param_1 + 0x28), (uVar1 & 1) != 0)) {
    *(undefined1 *)(param_1 + 0x94) = 0;
  }
                    /* WARNING: Could not recover jumptable at 0x021a9e48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(param_1 + 0x88) + 0x20))(*(long **)(param_1 + 0x88),param_1 + 0x28);
  return;
}

// ==== Aska::IntegratedDynamicsEnvironment::Modify()
// vaddr 0x20a9e4c | ghidra 0x21a9e4c | size 336 | symbol _ZN4Aska29IntegratedDynamicsEnvironment6ModifyEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska29IntegratedDynamicsEnvironment6ModifyEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))();
  if ((uVar1 & 1) != 0) {
    if (((*(char *)(param_1 + 0x94) != '\0') && (*(long *)(param_1 + 0x30) != 0)) &&
       ((uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))(), (uVar1 & 1) != 0 &&
        (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x18))
                           (*(long **)(param_1 + 0x88),param_1 + 0x28), (uVar1 & 1) != 0)))) {
      *(undefined1 *)(param_1 + 0x94) = 0;
    }
    (**(code **)(**(long **)(param_1 + 0x88) + 0x28))(*(long **)(param_1 + 0x88),param_1 + 0x48);
    if (*(long *)(param_1 + 0x50) != 0) {
      lVar2 = *(long *)(param_1 + 0x50);
      do {
        lVar3 = *(long *)(lVar2 + 0x10);
        Aska::IDEPrimitiveListHandler::Remove(Aska::IDEPrimitiveBase*)(param_1 + 0x48,lVar2);
        Aska::IDEPrimitiveListHandler::Add(Aska::IDEPrimitiveBase*)(param_1 + 0x28,lVar2);
        lVar2 = lVar3;
      } while (lVar3 != 0);
    }
    return;
  }
  lVar2 = param_1 + 0x28;
  if (*(long *)(param_1 + 0x50) != 0) {
    lVar3 = *(long *)(param_1 + 0x50);
    do {
      lVar4 = *(long *)(lVar3 + 0x10);
      Aska::IDEPrimitiveListHandler::Remove(Aska::IDEPrimitiveBase*)(param_1 + 0x48,lVar3);
      Aska::IDEPrimitiveListHandler::Add(Aska::IDEPrimitiveBase*)(lVar2,lVar3);
      lVar3 = lVar4;
    } while (lVar4 != 0);
  }
  if ((((*(char *)(param_1 + 0x94) != '\0') && (*(long *)(param_1 + 0x30) != 0)) &&
      (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))(), (uVar1 & 1) != 0)) &&
     (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x18))(*(long **)(param_1 + 0x88),lVar2),
     (uVar1 & 1) != 0)) {
    *(undefined1 *)(param_1 + 0x94) = 0;
  }
                    /* WARNING: Could not recover jumptable at 0x021a9f98. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(param_1 + 0x88) + 0x20))(*(long **)(param_1 + 0x88),lVar2);
  return;
}

// ==== Aska::IntegratedDynamicsEnvironment::Intersect(Aska::Ray const*, unsigned short)
// vaddr 0x20a9f9c | ghidra 0x21a9f9c | size 92 | symbol _ZN4Aska29IntegratedDynamicsEnvironment9IntersectEPKNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment9IntersectEPKNS_3RayEt
          (long param_1,undefined8 param_2,undefined4 param_3)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if ((*(long **)(param_1 + 0x88) != (long *)0x0) &&
     (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))(), (uVar1 & 1) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x021a9fe4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(**(long **)(param_1 + 0x88) + 0x90))
                      (*(long **)(param_1 + 0x88),param_2,param_3);
    return uVar2;
  }
  return 0;
}

// ==== Aska::IntegratedDynamicsEnvironment::Intersect(Aska::Segment const*, unsigned short)
// vaddr 0x20a9ff8 | ghidra 0x21a9ff8 | size 92 | symbol _ZN4Aska29IntegratedDynamicsEnvironment9IntersectEPKNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment9IntersectEPKNS_7SegmentEt
          (long param_1,undefined8 param_2,undefined4 param_3)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if ((*(long **)(param_1 + 0x88) != (long *)0x0) &&
     (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))(), (uVar1 & 1) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x021aa040. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(**(long **)(param_1 + 0x88) + 0x98))
                      (*(long **)(param_1 + 0x88),param_2,param_3);
    return uVar2;
  }
  return 0;
}

// ==== Aska::IntegratedDynamicsEnvironment::FindIntersectNearestPoint(Aska::Vector*, Aska::Ray const*, unsigned short)
// vaddr 0x20aa054 | ghidra 0x21aa054 | size 112 | symbol _ZN4Aska29IntegratedDynamicsEnvironment25FindIntersectNearestPointEPNS_6VectorEPKNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment25FindIntersectNearestPointEPNS_6VectorEPKNS_3RayEt
          (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if ((*(long **)(param_1 + 0x88) != (long *)0x0) &&
     (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))(), (uVar1 & 1) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x021aa0ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(**(long **)(param_1 + 0x88) + 0xa0))
                      (*(long **)(param_1 + 0x88),param_2,param_3,param_4);
    return uVar2;
  }
  return 0;
}

// ==== Aska::IntegratedDynamicsEnvironment::FindIntersectNearestPoint(Aska::Vector*, Aska::Segment const*, unsigned short)
// vaddr 0x20aa0c4 | ghidra 0x21aa0c4 | size 112 | symbol _ZN4Aska29IntegratedDynamicsEnvironment25FindIntersectNearestPointEPNS_6VectorEPKNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment25FindIntersectNearestPointEPNS_6VectorEPKNS_7SegmentEt
          (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if ((*(long **)(param_1 + 0x88) != (long *)0x0) &&
     (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))(), (uVar1 & 1) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x021aa11c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(**(long **)(param_1 + 0x88) + 0xa8))
                      (*(long **)(param_1 + 0x88),param_2,param_3,param_4);
    return uVar2;
  }
  return 0;
}

// ==== Aska::IntegratedDynamicsEnvironment::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Ray const*, unsigned short)
// vaddr 0x20aa134 | ghidra 0x21aa134 | size 112 | symbol _ZN4Aska29IntegratedDynamicsEnvironment26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPKNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPKNS_3RayEt
          (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if ((*(long **)(param_1 + 0x88) != (long *)0x0) &&
     (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))(), (uVar1 & 1) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x021aa18c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(**(long **)(param_1 + 0x88) + 0xb0))
                      (*(long **)(param_1 + 0x88),param_2,param_3,param_4);
    return uVar2;
  }
  return 0;
}

// ==== Aska::IntegratedDynamicsEnvironment::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Segment const*, unsigned short)
// vaddr 0x20aa1a4 | ghidra 0x21aa1a4 | size 112 | symbol _ZN4Aska29IntegratedDynamicsEnvironment26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPKNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPKNS_7SegmentEt
          (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if ((*(long **)(param_1 + 0x88) != (long *)0x0) &&
     (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))(), (uVar1 & 1) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x021aa1fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(**(long **)(param_1 + 0x88) + 0xb8))
                      (*(long **)(param_1 + 0x88),param_2,param_3,param_4);
    return uVar2;
  }
  return 0;
}

// ==== Aska::IntegratedDynamicsEnvironment::GetHeight(Aska::IDE_ResultOfHeight*, Aska::Vector*, unsigned int, unsigned short)
// vaddr 0x20aa214 | ghidra 0x21aa214 | size 116 | symbol _ZN4Aska29IntegratedDynamicsEnvironment9GetHeightEPNS_18IDE_ResultOfHeightEPNS_6VectorEjt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment9GetHeightEPNS_18IDE_ResultOfHeightEPNS_6VectorEjt
          (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,undefined4 param_5)

{
  ulong uVar1;
  undefined8 uVar2;
  
  uVar2 = 0;
  if (*(long **)(param_1 + 0x88) != (long *)0x0) {
    uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))();
    if ((uVar1 & 1) == 0) {
      uVar2 = 0;
    }
    else {
      (**(code **)(**(long **)(param_1 + 0x88) + 0xc0))
                (*(long **)(param_1 + 0x88),param_2,param_3,param_4,param_5);
      uVar2 = 1;
    }
  }
  return uVar2;
}

// ==== Aska::IntegratedDynamicsEnvironment::FindIntersectNearestObjectArray(Aska::IDE_ResultOfNearestObject*, Aska::Ray*, unsigned int, unsigned short)
// vaddr 0x20aa288 | ghidra 0x21aa288 | size 116 | symbol _ZN4Aska29IntegratedDynamicsEnvironment31FindIntersectNearestObjectArrayEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEjt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment31FindIntersectNearestObjectArrayEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEjt
          (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,undefined4 param_5)

{
  ulong uVar1;
  undefined8 uVar2;
  
  uVar2 = 0;
  if (*(long **)(param_1 + 0x88) != (long *)0x0) {
    uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))();
    if ((uVar1 & 1) == 0) {
      uVar2 = 0;
    }
    else {
      (**(code **)(**(long **)(param_1 + 0x88) + 200))
                (*(long **)(param_1 + 0x88),param_2,param_3,param_4,param_5);
      uVar2 = 1;
    }
  }
  return uVar2;
}

// ==== Aska::IntegratedDynamicsEnvironment::FindIntersectNearestObjectArray(Aska::IDE_ResultOfNearestObject*, Aska::Segment*, unsigned int, unsigned short)
// vaddr 0x20aa2fc | ghidra 0x21aa2fc | size 116 | symbol _ZN4Aska29IntegratedDynamicsEnvironment31FindIntersectNearestObjectArrayEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEjt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment31FindIntersectNearestObjectArrayEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEjt
          (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,undefined4 param_5)

{
  ulong uVar1;
  undefined8 uVar2;
  
  uVar2 = 0;
  if (*(long **)(param_1 + 0x88) != (long *)0x0) {
    uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))();
    if ((uVar1 & 1) == 0) {
      uVar2 = 0;
    }
    else {
      (**(code **)(**(long **)(param_1 + 0x88) + 0xd0))
                (*(long **)(param_1 + 0x88),param_2,param_3,param_4,param_5);
      uVar2 = 1;
    }
  }
  return uVar2;
}

// ==== Aska::IntegratedDynamicsEnvironment::FindIntersectObjects(Aska::INotify*, Aska::Vector const*, unsigned short)
// vaddr 0x20aa370 | ghidra 0x21aa370 | size 108 | symbol _ZN4Aska29IntegratedDynamicsEnvironment20FindIntersectObjectsEPNS_7INotifyEPKNS_6VectorEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska29IntegratedDynamicsEnvironment20FindIntersectObjectsEPNS_7INotifyEPKNS_6VectorEt
               (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  ulong uVar1;
  
  if ((*(long **)(param_1 + 0x88) != (long *)0x0) &&
     (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))(), (uVar1 & 1) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x021aa3c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + 0x88) + 0xd8))
              (*(long **)(param_1 + 0x88),param_2,param_3,param_4);
    return;
  }
  return;
}

// ==== Aska::IntegratedDynamicsEnvironment::FindIntersectObjects(Aska::INotify*, Aska::Box const*, unsigned short)
// vaddr 0x20aa3dc | ghidra 0x21aa3dc | size 108 | symbol _ZN4Aska29IntegratedDynamicsEnvironment20FindIntersectObjectsEPNS_7INotifyEPKNS_3BoxEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska29IntegratedDynamicsEnvironment20FindIntersectObjectsEPNS_7INotifyEPKNS_3BoxEt
               (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  ulong uVar1;
  
  if ((*(long **)(param_1 + 0x88) != (long *)0x0) &&
     (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))(), (uVar1 & 1) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x021aa434. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + 0x88) + 0xe0))
              (*(long **)(param_1 + 0x88),param_2,param_3,param_4);
    return;
  }
  return;
}

// ==== Aska::IntegratedDynamicsEnvironment::PostFindIntersectObjects(Aska::IDE_ResultOfFindObjects*, int, unsigned int*, unsigned int*, Aska::INotify*, Aska::Box const*, unsigned int, unsigned short)
// vaddr 0x20aa448 | ghidra 0x21aa448 | size 172 | symbol _ZN4Aska29IntegratedDynamicsEnvironment24PostFindIntersectObjectsEPNS_23IDE_ResultOfFindObjectsEiPjS3_PNS_7INotifyEPKNS_3BoxEjt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska29IntegratedDynamicsEnvironment24PostFindIntersectObjectsEPNS_23IDE_ResultOfFindObjectsEiPjS3_PNS_7INotifyEPKNS_3BoxEjt
               (long param_1,undefined8 param_2,undefined4 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined4 param_8)

{
  ulong uVar1;
  
  if (*(long **)(param_1 + 0x88) != (long *)0x0) {
    uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))();
    if ((uVar1 & 1) != 0) {
                    /* WARNING: Could not recover jumptable at 0x021aa4d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(**(long **)(param_1 + 0x88) + 0xe8))
                (*(long **)(param_1 + 0x88),param_2,param_3,param_4,param_5,param_6,param_7,param_8)
      ;
      return;
    }
  }
  return;
}

// ==== Aska::IntegratedDynamicsEnvironment::PostFindIntersectObjects_Wait()
// vaddr 0x20aa4f4 | ghidra 0x21aa4f4 | size 16 | symbol _ZN4Aska29IntegratedDynamicsEnvironment29PostFindIntersectObjects_WaitEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska29IntegratedDynamicsEnvironment29PostFindIntersectObjects_WaitEv(long param_1)

{
                    /* WARNING: Could not recover jumptable at 0x021aa500. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(param_1 + 0x88) + 0xf0))();
  return;
}

// ==== Aska::IntegratedDynamicsEnvironment::FindIntersectPrimitives(Aska::IDEIntersectNotify*)
// vaddr 0x20aa504 | ghidra 0x21aa504 | size 100 | symbol _ZN4Aska29IntegratedDynamicsEnvironment23FindIntersectPrimitivesEPNS_18IDEIntersectNotifyE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska29IntegratedDynamicsEnvironment23FindIntersectPrimitivesEPNS_18IDEIntersectNotifyE
               (long param_1,undefined8 param_2)

{
  ulong uVar1;
  
  if (((*(long **)(param_1 + 0x88) != (long *)0x0) &&
      (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x78))(), (uVar1 & 1) != 0)) &&
     (uVar1 = (**(code **)(**(long **)(param_1 + 0x88) + 0x100))(), (uVar1 & 1) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x021aa558. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + 0x88) + 0xf8))(*(long **)(param_1 + 0x88),param_2);
    return;
  }
  return;
}

// ==== Aska::IntegratedDynamicsEnvironment::Attach(Aska::IDEPrimitiveBase*, int, Aska::IDEPrimitiveBase*, int)
// vaddr 0x20aa568 | ghidra 0x21aa568 | size 188 | symbol _ZN4Aska29IntegratedDynamicsEnvironment6AttachEPNS_16IDEPrimitiveBaseEiS2_i | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska29IntegratedDynamicsEnvironment6AttachEPNS_16IDEPrimitiveBaseEiS2_i
          (long param_1,undefined8 param_2,undefined4 param_3,ulong param_4,int param_5)

{
  undefined8 uVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  
  if ((param_4 != 0) && (lVar2 = *(long *)(param_1 + 0x88), lVar2 != 0)) {
    *(undefined1 *)(param_1 + 0x94) = 1;
    if ((0 < param_5) && (uVar4 = param_4 + (long)param_5 * 0x130, param_4 < uVar4)) {
      uVar3 = param_4;
      do {
        Aska::IDEPrimitiveListHandler::Add(Aska::IDEPrimitiveBase*)(param_1 + 0x28,uVar3);
        uVar3 = uVar3 + 0x130;
      } while (uVar3 < uVar4);
      lVar2 = *(long *)(param_1 + 0x88);
    }
    uVar1 = (*(code *)
              PTR__ZN4Aska20IDESpacePartitionBVH6AttachEPNS_16IDEPrimitiveBaseEiS2_i_02cb09c8)
                      (lVar2,param_2,param_3,param_4,param_5);
    return uVar1;
  }
  return 0;
}

// ==== Aska::IntegratedDynamicsEnvironment::IntegratedDynamicsEnvironment(Aska::_EnumIDESpacePartitionType)
// vaddr 0x20aa624 | ghidra 0x21aa624 | size 176 | symbol _ZN4Aska29IntegratedDynamicsEnvironmentC2ENS_26_EnumIDESpacePartitionTypeE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska29IntegratedDynamicsEnvironmentC1ENS_26_EnumIDESpacePartitionTypeE
               (long *param_1,int param_2)

{
  undefined4 uVar1;
  long lVar2;
  int iVar3;
  code *pcVar4;
  
  pcVar4 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
  *param_1 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined2 *)((long)param_1 + 0x24) = 0;
  *(undefined1 *)((long)param_1 + 0x26) = 0;
  uVar1 = (*pcVar4)();
  *(undefined4 *)(param_1 + 4) = uVar1;
  *param_1 = (long)(PTR__ZTVN4Aska29IntegratedDynamicsEnvironmentE_02cbe110 + 0x10);
  Aska::IDEPrimitiveListHandler::IDEPrimitiveListHandler()(param_1 + 5);
  Aska::IDEPrimitiveListHandler::IDEPrimitiveListHandler()(param_1 + 9);
  Aska::IDEPrimitiveListHandler::IDEPrimitiveListHandler()(param_1 + 0xd);
  if (param_2 == 0) {
    lVar2 = operator new(unsigned long, std::nothrow_t const&)(0x40,PTR__ZSt7nothrow_02cb9a80);
    if (lVar2 != 0) {
      Aska::IDESpacePartitionBVH::IDESpacePartitionBVH()(lVar2);
    }
    param_1[0x11] = lVar2;
    iVar3 = -(uint)(lVar2 == 0);
  }
  else {
    iVar3 = -1;
    param_1[0x11] = 0;
  }
  *(int *)(param_1 + 0x12) = iVar3;
  *(undefined1 *)((long)param_1 + 0x94) = 0;
  return;
}

// ==== Aska::IntegratedDynamicsEnvironment::~IntegratedDynamicsEnvironment()
// vaddr 0x20aa6d4 | ghidra 0x21aa6d4 | size 96 | symbol _ZN4Aska29IntegratedDynamicsEnvironmentD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska29IntegratedDynamicsEnvironmentD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska29IntegratedDynamicsEnvironmentE_02cbe110 + 0x10);
  Aska::IntegratedDynamicsEnvironment::DeleteAll()();
  if ((long *)param_1[0x11] != (long *)0x0) {
    (**(code **)(*(long *)param_1[0x11] + 8))();
    param_1[0x11] = 0;
    *(undefined4 *)(param_1 + 0x12) = 0xffffffff;
  }
  Aska::IDEPrimitiveListHandler::~IDEPrimitiveListHandler()(param_1 + 0xd);
  Aska::IDEPrimitiveListHandler::~IDEPrimitiveListHandler()(param_1 + 9);
  Aska::IDEPrimitiveListHandler::~IDEPrimitiveListHandler()(param_1 + 5);
  (*(code *)PTR__ZN4Aska4TaskD1Ev_02c92d10)(param_1);
  return;
}

// ==== Aska::IntegratedDynamicsEnvironment::~IntegratedDynamicsEnvironment()
// vaddr 0x20aa734 | ghidra 0x21aa734 | size 104 | symbol _ZN4Aska29IntegratedDynamicsEnvironmentD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska29IntegratedDynamicsEnvironmentD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska29IntegratedDynamicsEnvironmentE_02cbe110 + 0x10);
  Aska::IntegratedDynamicsEnvironment::DeleteAll()();
  if ((long *)param_1[0x11] != (long *)0x0) {
    (**(code **)(*(long *)param_1[0x11] + 8))();
    param_1[0x11] = 0;
    *(undefined4 *)(param_1 + 0x12) = 0xffffffff;
  }
  Aska::IDEPrimitiveListHandler::~IDEPrimitiveListHandler()(param_1 + 0xd);
  Aska::IDEPrimitiveListHandler::~IDEPrimitiveListHandler()(param_1 + 9);
  Aska::IDEPrimitiveListHandler::~IDEPrimitiveListHandler()(param_1 + 5);
  Aska::Task::~Task()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::IntegratedDynamicsEnvironment::Get(unsigned long, void*) const
// vaddr 0x20aa79c | ghidra 0x21aa79c | size 40 | symbol _ZNK4Aska29IntegratedDynamicsEnvironment3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska29IntegratedDynamicsEnvironment3GetEmPv(undefined8 param_1,undefined8 param_2)

{
  if (((short)((ulong)param_2 >> 0x20) == 0) && ((ushort)((short)param_2 - 5U) < 2)) {
    return 1;
  }
  return 0;
}

// ==== Aska::IntegratedDynamicsEnvironment::Set(unsigned long, void const*)
// vaddr 0x20aa7c4 | ghidra 0x21aa7c4 | size 40 | symbol _ZN4Aska29IntegratedDynamicsEnvironment3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska29IntegratedDynamicsEnvironment3SetEmPKv(undefined8 param_1,undefined8 param_2)

{
  if (((short)((ulong)param_2 >> 0x20) == 0) && ((ushort)((short)param_2 - 5U) < 2)) {
    return 1;
  }
  return 0;
}

// ==== Aska::IntegratedDynamicsEnvironment::GetClassID(int) const
// vaddr 0x20aa7ec | ghidra 0x21aa7ec | size 64 | symbol _ZNK4Aska29IntegratedDynamicsEnvironment10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska29IntegratedDynamicsEnvironment10GetClassIDEi(undefined8 param_1,int param_2)

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
  return 0xf002f053;
}

// ==== Aska::IDEPrimitiveBase::CheckToDispatch(Aska::Ray*, unsigned short)
// vaddr 0x20e6314 | ghidra 0x21e6314 | size 8 | symbol _ZN4Aska16IDEPrimitiveBase15CheckToDispatchEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska16IDEPrimitiveBase15CheckToDispatchEPNS_3RayEt(void)

{
  return 1;
}

// ==== Aska::IDEPrimitiveBase::CheckToDispatch(Aska::Segment*, unsigned short)
// vaddr 0x20e631c | ghidra 0x21e631c | size 8 | symbol _ZN4Aska16IDEPrimitiveBase15CheckToDispatchEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska16IDEPrimitiveBase15CheckToDispatchEPNS_7SegmentEt(void)

{
  return 1;
}

// ==== Aska::IDEPrimitiveBase::CheckToDispatch(Aska::Vector const*, unsigned short)
// vaddr 0x20e6324 | ghidra 0x21e6324 | size 8 | symbol _ZN4Aska16IDEPrimitiveBase15CheckToDispatchEPKNS_6VectorEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska16IDEPrimitiveBase15CheckToDispatchEPKNS_6VectorEt(void)

{
  return 1;
}

// ==== Aska::IDEPrimitiveBase::CheckToDispatch(Aska::Box const*, unsigned short)
// vaddr 0x20e632c | ghidra 0x21e632c | size 8 | symbol _ZN4Aska16IDEPrimitiveBase15CheckToDispatchEPKNS_3BoxEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska16IDEPrimitiveBase15CheckToDispatchEPKNS_3BoxEt(void)

{
  return 1;
}

// ==== Aska::IDEPrimitiveBase::Update()
// vaddr 0x20e6334 | ghidra 0x21e6334 | size 4 | symbol _ZN4Aska16IDEPrimitiveBase6UpdateEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16IDEPrimitiveBase6UpdateEv(void)

{
  return;
}

// ==== Aska::IDEPrimitiveBase::Intersect(Aska::Ray*, unsigned short)
// vaddr 0x20e6338 | ghidra 0x21e6338 | size 8 | symbol _ZN4Aska16IDEPrimitiveBase9IntersectEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska16IDEPrimitiveBase9IntersectEPNS_3RayEt(void)

{
  return 0;
}

// ==== Aska::IDEPrimitiveBase::Intersect(Aska::Segment*, unsigned short)
// vaddr 0x20e6340 | ghidra 0x21e6340 | size 8 | symbol _ZN4Aska16IDEPrimitiveBase9IntersectEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska16IDEPrimitiveBase9IntersectEPNS_7SegmentEt(void)

{
  return 0;
}

// ==== Aska::IDEPrimitiveBase::FindIntersectNearestPoint(Aska::Vector*, Aska::Ray*, unsigned short)
// vaddr 0x20e6348 | ghidra 0x21e6348 | size 8 | symbol _ZN4Aska16IDEPrimitiveBase25FindIntersectNearestPointEPNS_6VectorEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska16IDEPrimitiveBase25FindIntersectNearestPointEPNS_6VectorEPNS_3RayEt(void)

{
  return 0;
}

// ==== Aska::IDEPrimitiveBase::FindIntersectNearestPoint(Aska::Vector*, Aska::Segment*, unsigned short)
// vaddr 0x20e6350 | ghidra 0x21e6350 | size 8 | symbol _ZN4Aska16IDEPrimitiveBase25FindIntersectNearestPointEPNS_6VectorEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska16IDEPrimitiveBase25FindIntersectNearestPointEPNS_6VectorEPNS_7SegmentEt(void)

{
  return 0;
}

// ==== Aska::IDEPrimitiveBase::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Ray*, unsigned short)
// vaddr 0x20e6358 | ghidra 0x21e6358 | size 8 | symbol _ZN4Aska16IDEPrimitiveBase26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska16IDEPrimitiveBase26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEt
          (void)

{
  return 0;
}

// ==== Aska::IDEPrimitiveBase::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Segment*, unsigned short)
// vaddr 0x20e6360 | ghidra 0x21e6360 | size 8 | symbol _ZN4Aska16IDEPrimitiveBase26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska16IDEPrimitiveBase26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEt
          (void)

{
  return 0;
}

// ==== Aska::IDEPrimitiveBase::FindIntersectObjects(Aska::INotify*, Aska::Vector const*, unsigned short)
// vaddr 0x20e6368 | ghidra 0x21e6368 | size 4 | symbol _ZN4Aska16IDEPrimitiveBase20FindIntersectObjectsEPNS_7INotifyEPKNS_6VectorEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16IDEPrimitiveBase20FindIntersectObjectsEPNS_7INotifyEPKNS_6VectorEt(void)

{
  return;
}

// ==== Aska::IDEPrimitiveBase::FindIntersectObjects(Aska::INotify*, Aska::Box const*, unsigned short)
// vaddr 0x20e636c | ghidra 0x21e636c | size 4 | symbol _ZN4Aska16IDEPrimitiveBase20FindIntersectObjectsEPNS_7INotifyEPKNS_3BoxEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16IDEPrimitiveBase20FindIntersectObjectsEPNS_7INotifyEPKNS_3BoxEt(void)

{
  return;
}

// ==== Aska::IDEPrimitiveBase::~IDEPrimitiveBase()
// vaddr 0x20e8260 | ghidra 0x21e8260 | size 4 | symbol _ZN4Aska16IDEPrimitiveBaseD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16IDEPrimitiveBaseD2Ev(void)

{
  return;
}

// ==== Aska::IDEPrimitiveListHandler::IDEPrimitiveListHandler()
// vaddr 0x23455ac | ghidra 0x24455ac | size 28 | symbol _ZN4Aska23IDEPrimitiveListHandlerC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23IDEPrimitiveListHandlerC2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska23IDEPrimitiveListHandlerE_02cc0660;
  *(undefined4 *)(param_1 + 3) = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  return;
}

// ==== Aska::IDEPrimitiveListHandler::~IDEPrimitiveListHandler()
// vaddr 0x23455c8 | ghidra 0x24455c8 | size 4 | symbol _ZN4Aska23IDEPrimitiveListHandlerD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23IDEPrimitiveListHandlerD1Ev(void)

{
  return;
}

// ==== Aska::IDEPrimitiveListHandler::~IDEPrimitiveListHandler()
// vaddr 0x23455cc | ghidra 0x24455cc | size 4 | symbol _ZN4Aska23IDEPrimitiveListHandlerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23IDEPrimitiveListHandlerD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IDEPrimitiveListHandler::Attach(Aska::IDEPrimitiveBase*, Aska::IDEPrimitiveBase*, unsigned int)
// vaddr 0x23455d0 | ghidra 0x24455d0 | size 12 | symbol _ZN4Aska23IDEPrimitiveListHandler6AttachEPNS_16IDEPrimitiveBaseES2_j | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23IDEPrimitiveListHandler6AttachEPNS_16IDEPrimitiveBaseES2_j
               (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  *(undefined8 *)(param_1 + 8) = param_2;
  *(undefined8 *)(param_1 + 0x10) = param_3;
  *(undefined4 *)(param_1 + 0x18) = param_4;
  return;
}

// ==== Aska::IDEPrimitiveListHandler::Add(Aska::IDEPrimitiveBase*)
// vaddr 0x23455dc | ghidra 0x24455dc | size 56 | symbol _ZN4Aska23IDEPrimitiveListHandler3AddEPNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23IDEPrimitiveListHandler3AddEPNS_16IDEPrimitiveBaseE(long param_1,long param_2)

{
  if (*(long *)(param_1 + 8) == 0) {
    *(undefined8 *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = 0;
    *(long *)(param_1 + 8) = param_2;
  }
  else {
    *(long *)(*(long *)(param_1 + 0x10) + 0x10) = param_2;
    *(undefined8 *)(param_2 + 8) = *(undefined8 *)(param_1 + 0x10);
    *(undefined8 *)(param_2 + 0x10) = 0;
  }
  *(long *)(param_1 + 0x10) = param_2;
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 1;
  return;
}

// ==== Aska::IDEPrimitiveListHandler::Remove(Aska::IDEPrimitiveBase*)
// vaddr 0x2345614 | ghidra 0x2445614 | size 72 | symbol _ZN4Aska23IDEPrimitiveListHandler6RemoveEPNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23IDEPrimitiveListHandler6RemoveEPNS_16IDEPrimitiveBaseE(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  lVar1 = *(long *)(param_2 + 8);
  lVar2 = *(long *)(param_2 + 0x10);
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + -1;
  if (lVar1 == 0) {
    if (lVar2 != 0) {
      *(undefined8 *)(lVar2 + 8) = 0;
      *(long *)(param_1 + 8) = lVar2;
      return;
    }
    *(undefined8 *)(param_1 + 8) = 0;
    *(undefined8 *)(param_1 + 0x10) = 0;
    return;
  }
  if (lVar2 != 0) {
    *(long *)(lVar1 + 0x10) = lVar2;
    *(long *)(lVar2 + 8) = lVar1;
    return;
  }
  *(undefined8 *)(lVar1 + 0x10) = 0;
  *(long *)(param_1 + 0x10) = lVar1;
  return;
}

// ==== Aska::IDEPrimitiveListHandler::Exists(Aska::IDEPrimitiveBase*)
// vaddr 0x234565c | ghidra 0x244565c | size 48 | symbol _ZN4Aska23IDEPrimitiveListHandler6ExistsEPNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska23IDEPrimitiveListHandler6ExistsEPNS_16IDEPrimitiveBaseE(long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  if (lVar1 == 0) {
    return 0;
  }
  do {
    if (lVar1 == param_2) {
      return 1;
    }
    lVar1 = *(long *)(lVar1 + 0x10);
  } while (lVar1 != 0);
  return 0;
}

// ==== Aska::IDEPrimitiveListHandler::Clear()
// vaddr 0x234568c | ghidra 0x244568c | size 12 | symbol _ZN4Aska23IDEPrimitiveListHandler5ClearEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23IDEPrimitiveListHandler5ClearEv(long param_1)

{
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  return;
}

// ==== Aska::IDEPrimitiveListHandler::GetNode(unsigned int)
// vaddr 0x2345698 | ghidra 0x2445698 | size 32 | symbol _ZN4Aska23IDEPrimitiveListHandler7GetNodeEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23IDEPrimitiveListHandler7GetNodeEj(long param_1,uint param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  if (lVar1 != 0) {
    param_2 = ~param_2;
    do {
      param_2 = param_2 + 1;
      if (param_2 == 0) {
        return;
      }
      lVar1 = *(long *)(lVar1 + 0x10);
    } while (lVar1 != 0);
  }
  return;
}

// ==== Aska::IDEPrimitiveListHandler::Swap(Aska::IDEPrimitiveBase*, Aska::IDEPrimitiveBase*)
// vaddr 0x23456b8 | ghidra 0x24456b8 | size 112 | symbol _ZN4Aska23IDEPrimitiveListHandler4SwapEPNS_16IDEPrimitiveBaseES2_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska23IDEPrimitiveListHandler4SwapEPNS_16IDEPrimitiveBaseES2_
          (long param_1,long param_2,long param_3)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  
  if (*(long *)(param_2 + 0x10) != param_3) {
    return 0;
  }
  if (*(long *)(param_3 + 8) != param_2) {
    return 0;
  }
  lVar2 = *(long *)(param_2 + 8);
  lVar3 = *(long *)(param_3 + 0x10);
  plVar1 = (long *)(param_1 + 8);
  if (lVar2 != 0) {
    plVar1 = (long *)(lVar2 + 0x10);
  }
  *plVar1 = param_3;
  plVar1 = (long *)(param_1 + 0x10);
  if (lVar3 != 0) {
    plVar1 = (long *)(lVar3 + 8);
  }
  *plVar1 = param_2;
  *(long *)(param_3 + 8) = lVar2;
  *(long *)(param_2 + 0x10) = lVar3;
  *(long *)(param_3 + 0x10) = param_2;
  *(long *)(param_2 + 8) = param_3;
  return 1;
}

// ==== Aska::IDESpacePartitionBVH::IDESpacePartitionBVH()
// vaddr 0x2345728 | ghidra 0x2445728 | size 48 | symbol _ZN4Aska20IDESpacePartitionBVHC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVHC1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska20IDESpacePartitionBVHE_02cc0c90 + 0x10);
  param_1[1] = 0;
  Aska::IDEPrimitiveListHandler::IDEPrimitiveListHandler()(param_1 + 2);
  param_1[6] = 0;
  *(undefined2 *)(param_1 + 7) = 0;
  return;
}

// ==== Aska::IDESpacePartitionBVH::~IDESpacePartitionBVH()
// vaddr 0x2345758 | ghidra 0x2445758 | size 156 | symbol _ZN4Aska20IDESpacePartitionBVHD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVHD1Ev(long *param_1)

{
  long *plVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska20IDESpacePartitionBVHE_02cc0c90 + 0x10);
  plVar2 = (long *)param_1[3];
  while (plVar1 = plVar2, plVar1 != (long *)0x0) {
    plVar2 = (long *)plVar1[2];
    if ((*(byte *)((long)plVar1 + 0x23) & 1) != 0) {
      if (param_1[1] == 0) {
        (*(code *)((undefined8 *)*plVar1)[1])(plVar1);
      }
      else {
        (**(code **)*plVar1)(plVar1);
        Aska::MemoryManager::LocalFree(void*)(param_1[1],plVar1);
      }
    }
  }
  Aska::IDEPrimitiveListHandler::Clear()(param_1 + 2);
  param_1[6] = 0;
  *(undefined1 *)(param_1 + 7) = 0;
  (*(code *)PTR__ZN4Aska23IDEPrimitiveListHandlerD1Ev_02ca7840)(param_1 + 2);
  return;
}

// ==== Aska::IDESpacePartitionBVH::~IDESpacePartitionBVH()
// vaddr 0x23457f4 | ghidra 0x24457f4 | size 164 | symbol _ZN4Aska20IDESpacePartitionBVHD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVHD0Ev(long *param_1)

{
  long *plVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska20IDESpacePartitionBVHE_02cc0c90 + 0x10);
  plVar2 = (long *)param_1[3];
  while (plVar1 = plVar2, plVar1 != (long *)0x0) {
    plVar2 = (long *)plVar1[2];
    if ((*(byte *)((long)plVar1 + 0x23) & 1) != 0) {
      if (param_1[1] == 0) {
        (*(code *)((undefined8 *)*plVar1)[1])(plVar1);
      }
      else {
        (**(code **)*plVar1)(plVar1);
        Aska::MemoryManager::LocalFree(void*)(param_1[1],plVar1);
      }
    }
  }
  Aska::IDEPrimitiveListHandler::Clear()(param_1 + 2);
  param_1[6] = 0;
  *(undefined1 *)(param_1 + 7) = 0;
  Aska::IDEPrimitiveListHandler::~IDEPrimitiveListHandler()(param_1 + 2);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::IDESpacePartitionBVH::Update(Aska::IDEPrimitiveListHandler*)
// vaddr 0x2345898 | ghidra 0x2445898 | size 124 | symbol _ZN4Aska20IDESpacePartitionBVH6UpdateEPNS_23IDEPrimitiveListHandlerE | lib libSOA-3.7.0.so | 2026-10-08
undefined4
_ZN4Aska20IDESpacePartitionBVH6UpdateEPNS_23IDEPrimitiveListHandlerE(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  undefined4 uVar3;
  
  if (*(long *)(param_2 + 0x10) == 0) {
    uVar3 = 1;
  }
  else {
    uVar3 = 1;
    lVar1 = *(long *)(param_2 + 0x10);
    do {
      while ((lVar2 = *(long *)(lVar1 + 8), *(long *)(lVar1 + 0x60) == 0 &&
             (*(long *)(param_1 + 0x30) != lVar1))) {
        uVar3 = 0;
        lVar1 = lVar2;
        if (lVar2 == 0) {
          return 0;
        }
      }
      if (*(char *)(lVar1 + 0x21) != '\0') {
        Aska::IDESpacePartitionBVH::UpdateBoundHierarchy(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)(param_1);
      }
      lVar1 = lVar2;
    } while (lVar2 != 0);
  }
  return uVar3;
}

// ==== Aska::IDESpacePartitionBVH::IsBelongToHierarchy(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)
// vaddr 0x2345914 | ghidra 0x2445914 | size 32 | symbol _ZN4Aska20IDESpacePartitionBVH19IsBelongToHierarchyEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska20IDESpacePartitionBVH19IsBelongToHierarchyEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE
               (long param_1,long param_2)

{
  if (*(long *)(param_2 + 0x60) != 0) {
    return true;
  }
  return *(long *)(param_1 + 0x30) == param_2;
}

// ==== Aska::IDESpacePartitionBVH::UpdateBoundHierarchy(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)
// vaddr 0x2345934 | ghidra 0x2445934 | size 664 | symbol _ZN4Aska20IDESpacePartitionBVH20UpdateBoundHierarchyEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH20UpdateBoundHierarchyEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE
               (undefined8 param_1,long *param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  long lVar3;
  float fVar4;
  float fVar5;
  undefined *apuStack_d0 [3];
  undefined1 *puStack_b8;
  undefined2 uStack_af;
  undefined1 uStack_ad;
  undefined8 uStack_a0;
  float fStack_98;
  undefined4 uStack_94;
  undefined8 uStack_90;
  float fStack_88;
  undefined4 uStack_84;
  float fStack_80;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined1 uStack_58;
  undefined1 uStack_57;
  
  puVar1 = PTR__ZTVN4Aska18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE_02cbfec0 + 0x10;
  while( true ) {
    while (*(char *)((long)param_2 + 0x21) != '\0') {
      uVar2 = (**(code **)(*param_2 + 0x30))(param_2);
      param_1 = Aska::IDESpacePartitionBVH::SetBound(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)(uVar2,param_2);
      lVar3 = param_2[0xe];
      if (lVar3 != 0) {
        do {
          param_1 = Aska::IDESpacePartitionBVH_BoundingAABB::Resize(Aska::IDESpacePartitionBVH_BoundingAABB*)(param_2 + 6,lVar3 + 0x30);
          lVar3 = *(long *)(lVar3 + 0x68);
        } while (lVar3 != 0);
      }
      *(undefined1 *)((long)param_2 + 0x21) = 0;
      param_2 = (long *)param_2[0xc];
      if (param_2 == (long *)0x0) {
        return;
      }
    }
    *(undefined8 *)((ulong)apuStack_d0 | 8) = 0;
    ((undefined8 *)((ulong)apuStack_d0 | 8))[1] = 0;
    uStack_af = 1;
    uStack_ad = 1;
    uStack_58 = 0;
    uStack_68 = 0;
    uStack_60 = 0;
    uStack_70 = 0;
    uStack_57 = 1;
    uStack_a0 = 0;
    fStack_98 = 0.0;
    uStack_90 = 0;
    fStack_88 = 0.0;
    fStack_80 = -1.0;
    apuStack_d0[0] = puVar1;
    puStack_b8 = (undefined1 *)apuStack_d0;
    if (*(char *)((long)param_2 + 0x79) != '\0') {
      puStack_b8 = (undefined1 *)apuStack_d0;
      param_1 = Aska::IDESpacePartitionBVH::SetBound(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*, Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)(param_1,apuStack_d0,param_2);
    }
    lVar3 = param_2[0xe];
    if (lVar3 == 0) {
      fVar4 = (float)uStack_a0;
    }
    else {
      do {
        if (fStack_80 < 0.0) {
          fVar4 = *(float *)(lVar3 + 0x30);
          uStack_a0 = *(undefined8 *)(lVar3 + 0x30);
          fStack_98 = *(float *)(lVar3 + 0x38);
          uStack_94 = *(undefined4 *)(lVar3 + 0x3c);
          uStack_90 = *(undefined8 *)(lVar3 + 0x40);
          fStack_88 = *(float *)(lVar3 + 0x48);
          uStack_84 = *(undefined4 *)(lVar3 + 0x4c);
          fStack_80 = fStack_88 - fStack_98;
          fVar5 = (*(float *)(lVar3 + 0x40) - fVar4) *
                  (*(float *)(lVar3 + 0x44) - *(float *)(lVar3 + 0x34));
        }
        else {
          fVar4 = (float)uStack_a0;
          if (*(float *)(lVar3 + 0x30) <= (float)uStack_a0) {
            fVar4 = *(float *)(lVar3 + 0x30);
          }
          if (*(float *)(lVar3 + 0x34) <= uStack_a0._4_4_) {
            uStack_a0._4_4_ = *(float *)(lVar3 + 0x34);
          }
          if (*(float *)(lVar3 + 0x38) <= fStack_98) {
            fStack_98 = *(float *)(lVar3 + 0x38);
          }
          if ((float)uStack_90 <= *(float *)(lVar3 + 0x40)) {
            uStack_90._0_4_ = *(float *)(lVar3 + 0x40);
          }
          if (uStack_90._4_4_ <= *(float *)(lVar3 + 0x44)) {
            uStack_90._4_4_ = *(float *)(lVar3 + 0x44);
          }
          if (fStack_88 <= *(float *)(lVar3 + 0x48)) {
            fStack_88 = *(float *)(lVar3 + 0x48);
          }
          uStack_a0 = CONCAT44(uStack_a0._4_4_,fVar4);
          fStack_80 = fStack_88 - fStack_98;
          fVar5 = ((float)uStack_90 - fVar4) * (uStack_90._4_4_ - uStack_a0._4_4_);
        }
        fStack_80 = fStack_80 * fVar5;
        lVar3 = *(long *)(lVar3 + 0x68);
      } while (lVar3 != 0);
    }
    if ((((*(float *)(param_2 + 6) == fVar4) &&
         (*(float *)((long)param_2 + 0x34) == uStack_a0._4_4_)) &&
        (*(float *)(param_2 + 7) == fStack_98)) &&
       (((*(float *)(param_2 + 8) == (float)uStack_90 &&
         (*(float *)((long)param_2 + 0x44) == uStack_90._4_4_)) &&
        (*(float *)(param_2 + 9) == fStack_88)))) break;
    *(float *)(param_2 + 6) = fVar4;
    *(float *)((long)param_2 + 0x34) = uStack_a0._4_4_;
    *(float *)(param_2 + 7) = fStack_98;
    *(undefined4 *)((long)param_2 + 0x3c) = uStack_94;
    *(float *)(param_2 + 8) = (float)uStack_90;
    *(float *)((long)param_2 + 0x44) = uStack_90._4_4_;
    *(float *)(param_2 + 9) = fStack_88;
    *(undefined4 *)((long)param_2 + 0x4c) = uStack_84;
    *(float *)(param_2 + 10) = fStack_80;
    param_2 = (long *)param_2[0xc];
    if (param_2 == (long *)0x0) {
      return;
    }
  }
  return;
}

// ==== Aska::IDESpacePartitionBVH::Build(Aska::IDEPrimitiveListHandler*)
// vaddr 0x2345bcc | ghidra 0x2445bcc | size 56 | symbol _ZN4Aska20IDESpacePartitionBVH5BuildEPNS_23IDEPrimitiveListHandlerE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH5BuildEPNS_23IDEPrimitiveListHandlerE(long *param_1,long param_2)

{
  if (*(int *)(param_2 + 0x18) != 0) {
    Aska::IDESpacePartitionBVH::CreateHierarchy(Aska::IDEPrimitiveListHandler*)(param_1);
                    /* WARNING: Could not recover jumptable at 0x02445bf8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 0x108))(param_1,1);
    return;
  }
  return;
}

// ==== Aska::IDESpacePartitionBVH::CreateHierarchy(Aska::IDEPrimitiveListHandler*)
// vaddr 0x2345c04 | ghidra 0x2445c04 | size 1024 | symbol _ZN4Aska20IDESpacePartitionBVH15CreateHierarchyEPNS_23IDEPrimitiveListHandlerE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH15CreateHierarchyEPNS_23IDEPrimitiveListHandlerE
               (long param_1,long param_2)

{
  undefined *puVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  bool bVar6;
  long *plVar7;
  long lVar8;
  long lVar9;
  long *plVar10;
  long lVar11;
  long *plVar12;
  
  lVar3 = param_1;
  if (*(char *)(param_1 + 0x38) != '\0') {
    plVar12 = *(long **)(param_1 + 0x18);
joined_r0x02445c2c:
    plVar10 = plVar12;
    if (plVar12 != (long *)0x0) {
      do {
        plVar12 = (long *)plVar10[2];
        if ((*(byte *)((long)plVar10 + 0x23) & 1) != 0) {
          if (*(long *)(param_1 + 8) == 0) goto code_r0x02445c6c;
          (**(code **)*plVar10)(plVar10);
          Aska::MemoryManager::LocalFree(void*)(*(undefined8 *)(param_1 + 8),plVar10);
        }
        plVar10 = plVar12;
        if (plVar12 == (long *)0x0) break;
      } while( true );
    }
    lVar3 = Aska::IDEPrimitiveListHandler::Clear()(param_1 + 0x10);
    *(undefined8 *)(param_1 + 0x30) = 0;
    *(undefined1 *)(param_1 + 0x38) = 0;
  }
  plVar12 = *(long **)(param_2 + 8);
  do {
    if (*(char *)((long)plVar12 + 0x21) != '\0') {
      lVar3 = (**(code **)(*plVar12 + 0x30))(plVar12);
      *(undefined1 *)((long)plVar12 + 0x21) = 0;
    }
    *(undefined1 *)(plVar12 + 0xf) = 0;
    plVar12[0xd] = 0;
    plVar12[0xe] = 0;
    plVar12[0xc] = 0;
    *(undefined1 *)((long)plVar12 + 0x79) = 1;
    plVar12[6] = 0;
    *(undefined4 *)(plVar12 + 7) = 0;
    plVar12[8] = 0;
    *(undefined4 *)(plVar12 + 9) = 0;
    *(undefined4 *)(plVar12 + 10) = 0xbf800000;
    lVar3 = Aska::IDESpacePartitionBVH::SetBound(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)(lVar3,plVar12);
    plVar12 = (long *)plVar12[2];
  } while (plVar12 != (long *)0x0);
  if (*(long *)(*(long *)(param_2 + 8) + 0x10) == 0) {
    *(long *)(param_1 + 0x30) = *(long *)(param_2 + 8);
  }
  else {
    if (*(long *)(param_1 + 8) == 0) {
      plVar12 = (long *)operator new(unsigned long, unsigned long, bool)(0x80,0x10,1);
      if (plVar12 == (long *)0x0) {
        *(undefined8 *)(param_1 + 0x30) = 0;
        return;
      }
      plVar12[1] = 0;
      plVar12[2] = 0;
      *(undefined2 *)((long)plVar12 + 0x21) = 1;
      plVar12[3] = (long)plVar12;
      *(undefined1 *)((long)plVar12 + 0x23) = 1;
      plVar12[0xe] = 0;
      *(undefined1 *)(plVar12 + 0xf) = 0;
    }
    else {
      plVar12 = (long *)Aska::MemoryManager::AlignedMalloc(unsigned long, long)(*(long *)(param_1 + 8),0x80,0x10);
      plVar12[1] = 0;
      plVar12[2] = 0;
      plVar12[3] = (long)plVar12;
      plVar12[0xe] = 0;
      *(undefined1 *)(plVar12 + 0xf) = 0;
      *(undefined2 *)((long)plVar12 + 0x21) = 1;
      *(undefined1 *)((long)plVar12 + 0x23) = 1;
    }
    plVar12[0xc] = 0;
    plVar12[0xd] = 0;
    puVar1 = 
    PTR__ZTVN4Aska12IDEPrimitiveILNS_26_EnumIDESpacePartitionTypeE0ELNS_21_EnumIDEPrimitiveTypeE0EEE_02cbf7e8
    ;
    *(undefined1 *)((long)plVar12 + 0x79) = 1;
    plVar12[6] = 0;
    *(undefined4 *)(plVar12 + 7) = 0;
    plVar12[8] = 0;
    *(undefined4 *)(plVar12 + 9) = 0;
    *(undefined4 *)(plVar12 + 10) = 0xbf800000;
    *(undefined1 *)(plVar12 + 4) = 0;
    *plVar12 = (long)(puVar1 + 0x10);
    *(long **)(param_1 + 0x30) = plVar12;
    if (plVar12 == (long *)0x0) {
      return;
    }
    *(undefined1 *)((long)plVar12 + 0x79) = 0;
    Aska::IDEPrimitiveListHandler::Add(Aska::IDEPrimitiveBase*)(param_1 + 0x10,plVar12);
    for (lVar3 = *(long *)(param_2 + 8); lVar3 != 0; lVar3 = *(long *)(lVar3 + 0x10)) {
      Aska::IDESpacePartitionBVH_BoundingAABB::Resize(Aska::IDESpacePartitionBVH_BoundingAABB*)(plVar12 + 6,lVar3 + 0x30);
    }
    lVar3 = 0;
    do {
      lVar11 = *(long *)(param_2 + 8);
      bVar6 = false;
      lVar9 = lVar11;
      lVar2 = lVar11;
      while (lVar8 = lVar2, lVar5 = lVar9, lVar4 = lVar11, lVar5 != 0) {
        lVar9 = *(long *)(lVar5 + 0x10);
        do {
          lVar11 = lVar9;
          if (lVar3 == lVar11) goto code_r0x02445e54;
          lVar9 = 0;
        } while (lVar11 == 0);
        lVar9 = lVar11;
        lVar2 = lVar11;
        if (*(float *)(lVar8 + 0x50) < *(float *)(lVar11 + 0x50)) {
          Aska::IDEPrimitiveListHandler::Swap(Aska::IDEPrimitiveBase*, Aska::IDEPrimitiveBase*)(param_2,lVar5);
          bVar6 = true;
          lVar11 = lVar4;
          lVar9 = lVar5;
          lVar2 = lVar8;
        }
      }
code_r0x02445e54:
      lVar3 = lVar4;
    } while (bVar6);
    lVar3 = plVar12[0xc];
    if (lVar3 != 0) {
      plVar10 = *(long **)(lVar3 + 0x70);
      if (*(long **)(lVar3 + 0x70) == plVar12) {
        *(long *)(lVar3 + 0x70) = plVar12[0xd];
      }
      else {
        do {
          plVar7 = plVar10;
          if (plVar7 == (long *)0x0) goto code_r0x02445eac;
          plVar10 = (long *)plVar7[0xd];
        } while ((long *)plVar7[0xd] != plVar12);
        plVar7[0xd] = plVar12[0xd];
      }
code_r0x02445eac:
      plVar12[0xd] = 0;
      *(char *)(plVar12[0xc] + 0x78) = *(char *)(plVar12[0xc] + 0x78) + -1;
      plVar12[0xc] = 0;
    }
    for (lVar3 = *(long *)(param_2 + 8); lVar3 != 0; lVar3 = *(long *)(lVar3 + 0x10)) {
      while (*(long *)(lVar3 + 0x60) != 0) {
        lVar3 = *(long *)(lVar3 + 0x10);
        if (lVar3 == 0) goto code_r0x02445fdc;
      }
      lVar11 = plVar12[0xe];
      if (lVar11 == 0) {
        plVar12[0xe] = lVar3;
      }
      else {
        do {
          plVar10 = (long *)(lVar11 + 0x68);
          lVar11 = *plVar10;
        } while (lVar11 != 0);
        *plVar10 = lVar3;
      }
      *(long **)(lVar3 + 0x60) = plVar12;
      *(char *)(plVar12 + 0xf) = (char)plVar12[0xf] + '\x01';
      for (lVar11 = *(long *)(lVar3 + 0x10); lVar11 != 0; lVar11 = *(long *)(lVar11 + 0x10)) {
        if (((((*(long *)(lVar11 + 0x60) == 0) && (0.0 <= *(float *)(lVar3 + 0x50))) &&
             (*(float *)(lVar3 + 0x30) <= *(float *)(lVar11 + 0x30))) &&
            ((*(float *)(lVar3 + 0x34) <= *(float *)(lVar11 + 0x34) &&
             (*(float *)(lVar3 + 0x38) <= *(float *)(lVar11 + 0x38))))) &&
           ((*(float *)(lVar11 + 0x40) <= *(float *)(lVar3 + 0x40) &&
            ((*(float *)(lVar11 + 0x44) <= *(float *)(lVar3 + 0x44) &&
             (*(float *)(lVar11 + 0x48) <= *(float *)(lVar3 + 0x48))))))) {
          lVar9 = *(long *)(lVar3 + 0x70);
          if (lVar9 == 0) {
            *(long *)(lVar3 + 0x70) = lVar11;
          }
          else {
            do {
              plVar10 = (long *)(lVar9 + 0x68);
              lVar9 = *plVar10;
            } while (lVar9 != 0);
            *plVar10 = lVar11;
          }
          *(long *)(lVar11 + 0x60) = lVar3;
          *(char *)(lVar3 + 0x78) = *(char *)(lVar3 + 0x78) + '\x01';
        }
      }
      Aska::IDESpacePartitionBVH::DivideGroup(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)(param_1);
    }
code_r0x02445fdc:
    Aska::IDESpacePartitionBVH::DivideBranch(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)(param_1,plVar12);
  }
  *(undefined1 *)(param_1 + 0x38) = 1;
  return;
code_r0x02445c6c:
  (*(code *)((undefined8 *)*plVar10)[1])(plVar10);
  goto joined_r0x02445c2c;
}

// ==== Aska::IDESpacePartitionBVH::Modify(Aska::IDEPrimitiveListHandler*)
// vaddr 0x2346004 | ghidra 0x2446004 | size 16 | symbol _ZN4Aska20IDESpacePartitionBVH6ModifyEPNS_23IDEPrimitiveListHandlerE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH6ModifyEPNS_23IDEPrimitiveListHandlerE
               (undefined8 param_1,long param_2)

{
  if (*(int *)(param_2 + 0x18) != 0) {
    (*(code *)
      PTR__ZN4Aska20IDESpacePartitionBVH15ModifyHierarchyEPNS_23IDEPrimitiveListHandlerE_02cb0200)()
    ;
    return;
  }
  return;
}

// ==== Aska::IDESpacePartitionBVH::ModifyHierarchy(Aska::IDEPrimitiveListHandler*)
// vaddr 0x2346014 | ghidra 0x2446014 | size 580 | symbol _ZN4Aska20IDESpacePartitionBVH15ModifyHierarchyEPNS_23IDEPrimitiveListHandlerE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH15ModifyHierarchyEPNS_23IDEPrimitiveListHandlerE
               (long param_1,long param_2)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  long *plVar4;
  long lVar5;
  
  lVar1 = param_1;
  for (plVar4 = *(long **)(param_2 + 8); plVar4 != (long *)0x0; plVar4 = (long *)plVar4[2]) {
    if (*(char *)((long)plVar4 + 0x21) != '\0') {
      lVar1 = (**(code **)(*plVar4 + 0x30))(plVar4);
      *(undefined1 *)((long)plVar4 + 0x21) = 0;
    }
    *(undefined1 *)(plVar4 + 0xf) = 0;
    plVar4[0xd] = 0;
    plVar4[0xe] = 0;
    plVar4[0xc] = 0;
    *(undefined1 *)((long)plVar4 + 0x79) = 1;
    plVar4[6] = 0;
    *(undefined4 *)(plVar4 + 7) = 0;
    plVar4[8] = 0;
    *(undefined4 *)(plVar4 + 9) = 0;
    *(undefined4 *)(plVar4 + 10) = 0xbf800000;
    lVar1 = Aska::IDESpacePartitionBVH::SetBound(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)(lVar1,plVar4);
  }
  lVar1 = *(long *)(param_2 + 0x10);
joined_r0x0244608c:
  do {
    if (lVar1 == 0) {
      return;
    }
    lVar5 = *(long *)(param_1 + 0x30);
    if (((((*(float *)(lVar5 + 0x50) < 0.0) || (*(float *)(lVar1 + 0x30) < *(float *)(lVar5 + 0x30))
          ) || (*(float *)(lVar1 + 0x34) < *(float *)(lVar5 + 0x34))) ||
        ((*(float *)(lVar1 + 0x38) < *(float *)(lVar5 + 0x38) ||
         (*(float *)(lVar5 + 0x40) < *(float *)(lVar1 + 0x40))))) ||
       ((*(float *)(lVar5 + 0x44) < *(float *)(lVar1 + 0x44) ||
        (lVar3 = lVar5, *(float *)(lVar5 + 0x48) < *(float *)(lVar1 + 0x48))))) {
      if ((((0.0 <= *(float *)(lVar1 + 0x50)) &&
           (*(float *)(lVar1 + 0x30) <= *(float *)(lVar5 + 0x30))) &&
          ((*(float *)(lVar1 + 0x34) <= *(float *)(lVar5 + 0x34) &&
           ((*(float *)(lVar1 + 0x38) <= *(float *)(lVar5 + 0x38) &&
            (*(float *)(lVar5 + 0x40) <= *(float *)(lVar1 + 0x40))))))) &&
         ((*(float *)(lVar5 + 0x44) <= *(float *)(lVar1 + 0x44) &&
          (*(float *)(lVar5 + 0x48) <= *(float *)(lVar1 + 0x48))))) {
        lVar3 = *(long *)(lVar1 + 0x70);
        if (lVar3 == 0) {
          *(long *)(lVar1 + 0x70) = lVar5;
        }
        else {
          do {
            plVar4 = (long *)(lVar3 + 0x68);
            lVar3 = *plVar4;
          } while (lVar3 != 0);
          *plVar4 = lVar5;
        }
        *(long *)(lVar5 + 0x60) = lVar1;
        *(char *)(lVar1 + 0x78) = *(char *)(lVar1 + 0x78) + '\x01';
        *(long *)(param_1 + 0x30) = lVar1;
        lVar1 = *(long *)(lVar1 + 8);
        goto joined_r0x0244608c;
      }
code_r0x02446230:
      Aska::IDESpacePartitionBVH::ModifyChildren(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*, Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)(param_1,lVar5,lVar1);
    }
    else {
      while (lVar5 = lVar3, lVar3 = *(long *)(lVar5 + 0x70), lVar3 != 0) {
        while ((((*(float *)(lVar3 + 0x50) < 0.0 ||
                 (*(float *)(lVar1 + 0x30) < *(float *)(lVar3 + 0x30))) ||
                ((*(float *)(lVar1 + 0x34) < *(float *)(lVar3 + 0x34) ||
                 (((*(float *)(lVar1 + 0x38) < *(float *)(lVar3 + 0x38) ||
                   (*(float *)(lVar3 + 0x40) < *(float *)(lVar1 + 0x40))) ||
                  (*(float *)(lVar3 + 0x44) < *(float *)(lVar1 + 0x44))))))) ||
               (*(float *)(lVar3 + 0x48) < *(float *)(lVar1 + 0x48)))) {
          lVar3 = *(long *)(lVar3 + 0x68);
          if (lVar3 == 0) goto code_r0x0244621c;
        }
      }
code_r0x0244621c:
      uVar2 = Aska::IDESpacePartitionBVH::ModifyParent(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*, Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)(param_1,lVar5,lVar1);
      if ((uVar2 & 1) == 0) goto code_r0x02446230;
    }
    lVar1 = *(long *)(lVar1 + 8);
  } while( true );
}

// ==== Aska::IDESpacePartitionBVH::InstanciatePrimitive(Aska::AABB_MinMax*)
// vaddr 0x2346258 | ghidra 0x2446258 | size 136 | symbol _ZN4Aska20IDESpacePartitionBVH20InstanciatePrimitiveEPNS_11AABB_MinMaxE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH20InstanciatePrimitiveEPNS_11AABB_MinMaxE
               (undefined8 param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  long lVar7;
  
  lVar7 = Aska::IDEPrimitiveAABB<(Aska::_EnumIDESpacePartitionType)0>* Aska::IDESpacePartition::Alloc<Aska::IDEPrimitiveAABB<(Aska::_EnumIDESpacePartitionType)0>, Aska::AABB_MinMax>(Aska::AABB_MinMax*)();
  if (lVar7 != 0) {
    fVar1 = *param_2;
    *(float *)(lVar7 + 0x30) = fVar1;
    fVar2 = param_2[1];
    *(float *)(lVar7 + 0x34) = fVar2;
    fVar3 = param_2[2];
    *(float *)(lVar7 + 0x38) = fVar3;
    *(float *)(lVar7 + 0x3c) = param_2[3];
    fVar4 = param_2[4];
    *(float *)(lVar7 + 0x40) = fVar4;
    fVar5 = param_2[5];
    *(float *)(lVar7 + 0x44) = fVar5;
    fVar6 = param_2[6];
    *(float *)(lVar7 + 0x48) = fVar6;
    *(float *)(lVar7 + 0x4c) = param_2[7];
    *(float *)(lVar7 + 0x50) = (fVar4 - fVar1) * (fVar5 - fVar2) * (fVar6 - fVar3);
  }
  return;
}

// ==== Aska::IDESpacePartitionBVH::InstanciatePrimitive(Aska::Vector*)
// vaddr 0x2346448 | ghidra 0x2446448 | size 124 | symbol _ZN4Aska20IDESpacePartitionBVH20InstanciatePrimitiveEPNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska20IDESpacePartitionBVH20InstanciatePrimitiveEPNS_6VectorE
               (undefined8 param_1,float *param_2)

{
  float fVar1;
  long lVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  lVar2 = Aska::IDEPrimitiveSphere<(Aska::_EnumIDESpacePartitionType)0>* Aska::IDESpacePartition::Alloc<Aska::IDEPrimitiveSphere<(Aska::_EnumIDESpacePartitionType)0>, Aska::Vector>(Aska::Vector*)();
  if (lVar2 != 0) {
    fVar1 = param_2[3];
    fVar3 = fVar1 * _UNK_029e3674;
    fVar6 = *param_2 - fVar3;
    fVar7 = param_2[1] - fVar3;
    fVar4 = *param_2 + fVar3;
    fVar5 = param_2[1] + fVar3;
    fVar8 = param_2[2] - fVar3;
    fVar3 = param_2[2] + fVar3;
    *(float *)(lVar2 + 0x40) = fVar4;
    *(float *)(lVar2 + 0x44) = fVar5;
    *(float *)(lVar2 + 0x48) = fVar3;
    *(float *)(lVar2 + 0x3c) = fVar1;
    *(float *)(lVar2 + 0x4c) = fVar1;
    *(float *)(lVar2 + 0x30) = fVar6;
    *(float *)(lVar2 + 0x34) = fVar7;
    *(float *)(lVar2 + 0x38) = fVar8;
    *(float *)(lVar2 + 0x50) = (fVar3 - fVar8) * (fVar4 - fVar6) * (fVar5 - fVar7);
  }
  return;
}

// ==== Aska::IDESpacePartitionBVH::InstanciatePrimitive(Aska::HeightObject*)
// vaddr 0x23465f4 | ghidra 0x24465f4 | size 160 | symbol _ZN4Aska20IDESpacePartitionBVH20InstanciatePrimitiveEPNS_12HeightObjectE | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska20IDESpacePartitionBVH20InstanciatePrimitiveEPNS_12HeightObjectE
               (undefined8 param_1,long param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  long lVar7;
  
  lVar7 = Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>* Aska::IDESpacePartition::Alloc<Aska::IDEPrimitiveHeightObject<(Aska::_EnumIDESpacePartitionType)0>, Aska::HeightObject>(Aska::HeightObject*)();
  if (lVar7 != 0) {
    Aska::HeightObject::UpdateMinMax()(param_2);
    fVar1 = *(float *)(param_2 + 0x1c0);
    *(float *)(lVar7 + 0x30) = fVar1;
    fVar2 = *(float *)(param_2 + 0x1c4);
    *(float *)(lVar7 + 0x34) = fVar2;
    fVar3 = *(float *)(param_2 + 0x1c8);
    *(float *)(lVar7 + 0x38) = fVar3;
    *(undefined4 *)(lVar7 + 0x3c) = *(undefined4 *)(param_2 + 0x1cc);
    fVar4 = *(float *)(param_2 + 0x1d0);
    *(float *)(lVar7 + 0x40) = fVar4;
    fVar5 = *(float *)(param_2 + 0x1d4);
    *(float *)(lVar7 + 0x44) = fVar5;
    fVar6 = *(float *)(param_2 + 0x1d8);
    *(float *)(lVar7 + 0x48) = fVar6;
    *(undefined4 *)(lVar7 + 0x4c) = *(undefined4 *)(param_2 + 0x1dc);
    *(float *)(lVar7 + 0x50) = (fVar4 - fVar1) * (fVar5 - fVar2) * (fVar6 - fVar3);
  }
  return lVar7;
}

// ==== Aska::IDESpacePartitionBVH::InstanciatePrimitive(Aska::CollisionHandler*, void*)
// vaddr 0x23467b8 | ghidra 0x24467b8 | size 60 | symbol _ZN4Aska20IDESpacePartitionBVH20InstanciatePrimitiveEPNS_16CollisionHandlerEPv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska20IDESpacePartitionBVH20InstanciatePrimitiveEPNS_16CollisionHandlerEPv
               (undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  
  lVar1 = Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>* Aska::IDESpacePartition::Alloc<Aska::IDEPrimitiveCollisionHandler<(Aska::_EnumIDESpacePartitionType)0>, Aska::CollisionHandler>(Aska::CollisionHandler*)();
  if (lVar1 != 0) {
    *(undefined8 *)(lVar1 + 0xa0) = param_3;
    Aska::IDESpacePartitionBVH_BoundingAABB::Set(Aska::CollisionHandler*)(lVar1 + 0x30,param_2);
  }
  return lVar1;
}

// ==== Aska::IDESpacePartitionBVH::InstanciatePrimitive(Aska::Light*)
// vaddr 0x2346884 | ghidra 0x2446884 | size 784 | symbol _ZN4Aska20IDESpacePartitionBVH20InstanciatePrimitiveEPNS_5LightE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska20IDESpacePartitionBVH20InstanciatePrimitiveEPNS_5LightE(long param_1,long param_2)

{
  undefined *puVar1;
  long lVar2;
  long *plVar3;
  undefined8 uVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  if (((((*(ushort *)(param_2 + 0x2a5) & 1) == 0) || (*(float *)(param_2 + 0x2b8) < _UNK_027daba4))
      || (lVar2 = Aska::Light::GetIBLTextureID(int) const(param_2,0), lVar2 == 0)) ||
     ((*(ushort *)(param_2 + 0x2a5) >> 0xd & 1) != 0)) {
    return (long *)0x0;
  }
  if (*(long *)(param_1 + 8) == 0) {
    plVar3 = (long *)operator new(unsigned long, unsigned long, bool)(0x130,0x10,1);
    if (plVar3 == (long *)0x0) {
      return (long *)0x0;
    }
    *(undefined2 *)((long)plVar3 + 0x21) = 1;
    plVar3[2] = 0;
    plVar3[3] = (long)plVar3;
    *(undefined1 *)((long)plVar3 + 0x23) = 1;
    *(undefined1 *)(plVar3 + 0xf) = 0;
    plVar3[0xd] = 0;
    plVar3[0xe] = 0;
    plVar3[0xc] = 0;
    *(undefined1 *)((long)plVar3 + 0x79) = 1;
    plVar3[6] = 0;
    *(undefined4 *)(plVar3 + 7) = 0;
    plVar3[8] = 0;
    *(undefined4 *)(plVar3 + 9) = 0;
    *(undefined4 *)(plVar3 + 10) = 0xbf800000;
    puVar1 = PTR__ZTVN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EEE_02cbeab8;
    *(undefined1 *)(plVar3 + 4) = 5;
    *plVar3 = (long)(puVar1 + 0x10);
    plVar3[1] = 0;
  }
  else {
    plVar3 = (long *)Aska::MemoryManager::AlignedMalloc(unsigned long, long)(*(long *)(param_1 + 8),0x130,0x10);
    if (plVar3 != (long *)0x0) {
      plVar3[2] = 0;
      plVar3[3] = (long)plVar3;
      *(undefined1 *)(plVar3 + 0xf) = 0;
      plVar3[0xd] = 0;
      plVar3[0xe] = 0;
      plVar3[0xc] = 0;
      plVar3[6] = 0;
      *(undefined4 *)(plVar3 + 7) = 0;
      plVar3[8] = 0;
      *(undefined4 *)(plVar3 + 9) = 0;
      *(undefined2 *)((long)plVar3 + 0x21) = 1;
      *(undefined1 *)((long)plVar3 + 0x23) = 1;
      *(undefined1 *)((long)plVar3 + 0x79) = 1;
      *(undefined4 *)(plVar3 + 10) = 0xbf800000;
      puVar1 = PTR__ZTVN4Aska15IDEPrimitiveOBBILNS_26_EnumIDESpacePartitionTypeE0EEE_02cbeab8;
      *(undefined1 *)(plVar3 + 4) = 5;
      *plVar3 = (long)(puVar1 + 0x10);
      plVar3[1] = 0;
      goto code_r0x024469d4;
    }
  }
  if (plVar3 == (long *)0x0) {
    return (long *)0x0;
  }
code_r0x024469d4:
  *(undefined8 *)((long)plVar3 + 0xfc) = 0;
  *(undefined8 *)((long)plVar3 + 0xf4) = 0;
  plVar3[0x23] = 0x3f800000;
  plVar3[0x24] = param_2;
  *(undefined4 *)(plVar3 + 0x1c) = 0x3f800000;
  *(undefined8 *)((long)plVar3 + 0xe4) = 0x3f8000003f800000;
  *(undefined4 *)(plVar3 + 0x1e) = 0x3f800000;
  *(undefined4 *)((long)plVar3 + 0x104) = 0x3f800000;
  plVar3[0x21] = 0;
  plVar3[0x22] = 0;
  if (*(long **)(param_2 + 0x408) != (long *)0x0) {
    uVar4 = (**(code **)(**(long **)(param_2 + 0x408) + 0x98))();
    Aska::Vector::ApplyMatrix(Aska::Matrix const*)(plVar3 + 0x1a,uVar4);
    Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(plVar3 + 0x1e,uVar4);
    Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(plVar3 + 0x20,uVar4);
    Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(plVar3 + 0x22,uVar4);
    fVar6 = *(float *)(plVar3 + 0x1e) * *(float *)(plVar3 + 0x1e) +
            *(float *)((long)plVar3 + 0xf4) * *(float *)((long)plVar3 + 0xf4) +
            *(float *)(plVar3 + 0x1f) * *(float *)(plVar3 + 0x1f);
    fVar5 = SQRT(fVar6);
    if (NAN(fVar5)) {
      fVar5 = (float)sqrtf(fVar6);
    }
    fVar6 = 1.0 / fVar5;
    *(float *)(plVar3 + 0x1c) = fVar5 * *(float *)(plVar3 + 0x1c);
    *(float *)(plVar3 + 0x1e) = fVar6 * *(float *)(plVar3 + 0x1e);
    *(float *)((long)plVar3 + 0xf4) = fVar6 * *(float *)((long)plVar3 + 0xf4);
    fVar7 = *(float *)(plVar3 + 0x20) * *(float *)(plVar3 + 0x20) +
            *(float *)((long)plVar3 + 0x104) * *(float *)((long)plVar3 + 0x104) +
            *(float *)(plVar3 + 0x21) * *(float *)(plVar3 + 0x21);
    fVar5 = SQRT(fVar7);
    *(float *)(plVar3 + 0x1f) = fVar6 * *(float *)(plVar3 + 0x1f);
    if (NAN(fVar5)) {
      fVar5 = (float)sqrtf(fVar7);
    }
    fVar6 = 1.0 / fVar5;
    *(float *)((long)plVar3 + 0xe4) = fVar5 * *(float *)((long)plVar3 + 0xe4);
    *(float *)(plVar3 + 0x20) = fVar6 * *(float *)(plVar3 + 0x20);
    fVar7 = *(float *)(plVar3 + 0x22) * *(float *)(plVar3 + 0x22) +
            *(float *)((long)plVar3 + 0x114) * *(float *)((long)plVar3 + 0x114) +
            *(float *)(plVar3 + 0x23) * *(float *)(plVar3 + 0x23);
    fVar5 = SQRT(fVar7);
    *(float *)((long)plVar3 + 0x104) = fVar6 * *(float *)((long)plVar3 + 0x104);
    *(float *)(plVar3 + 0x21) = fVar6 * *(float *)(plVar3 + 0x21);
    if (NAN(fVar5)) {
      fVar5 = (float)sqrtf(fVar7);
    }
    fVar6 = 1.0 / fVar5;
    *(float *)(plVar3 + 0x1d) = fVar5 * *(float *)(plVar3 + 0x1d);
    *(undefined4 *)((long)plVar3 + 0xfc) = 0;
    *(undefined4 *)((long)plVar3 + 0x10c) = 0;
    *(float *)(plVar3 + 0x22) = fVar6 * *(float *)(plVar3 + 0x22);
    *(float *)((long)plVar3 + 0x114) = fVar6 * *(float *)((long)plVar3 + 0x114);
    *(float *)(plVar3 + 0x23) = fVar6 * *(float *)(plVar3 + 0x23);
    *(undefined4 *)((long)plVar3 + 0x11c) = 0;
  }
  lVar2 = _UNK_027dbb30;
  plVar3[0x1b] = _UNK_027dbb38;
  plVar3[0x1a] = lVar2;
  return plVar3;
}

// ==== Aska::IDESpacePartitionBVH::Set(Aska::IDEPrimitiveBase*, Aska::AABB_MinMax*)
// vaddr 0x2346b94 | ghidra 0x2446b94 | size 96 | symbol _ZN4Aska20IDESpacePartitionBVH3SetEPNS_16IDEPrimitiveBaseEPNS_11AABB_MinMaxE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska20IDESpacePartitionBVH3SetEPNS_16IDEPrimitiveBaseEPNS_11AABB_MinMaxE
          (undefined8 param_1,long param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  if (*(char *)(param_2 + 0x20) == '\x01') {
    *(undefined4 *)(param_2 + 0x80) = *param_3;
    *(undefined4 *)(param_2 + 0x84) = param_3[1];
    *(undefined4 *)(param_2 + 0x88) = param_3[2];
    *(undefined4 *)(param_2 + 0x8c) = param_3[3];
    *(undefined4 *)(param_2 + 0x90) = param_3[4];
    *(undefined4 *)(param_2 + 0x94) = param_3[5];
    *(undefined4 *)(param_2 + 0x98) = param_3[6];
    uVar1 = param_3[7];
    *(undefined1 *)(param_2 + 0x21) = 1;
    *(undefined4 *)(param_2 + 0x9c) = uVar1;
    return 1;
  }
  return 0;
}

// ==== Aska::IDESpacePartitionBVH::Set(Aska::IDEPrimitiveBase*, Aska::Vector*)
// vaddr 0x2346bf4 | ghidra 0x2446bf4 | size 64 | symbol _ZN4Aska20IDESpacePartitionBVH3SetEPNS_16IDEPrimitiveBaseEPNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska20IDESpacePartitionBVH3SetEPNS_16IDEPrimitiveBaseEPNS_6VectorE
          (undefined8 param_1,long param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  if (*(char *)(param_2 + 0x20) == '\x02') {
    *(undefined4 *)(param_2 + 0x80) = *param_3;
    *(undefined4 *)(param_2 + 0x84) = param_3[1];
    *(undefined4 *)(param_2 + 0x88) = param_3[2];
    uVar1 = param_3[3];
    *(undefined1 *)(param_2 + 0x21) = 1;
    *(undefined4 *)(param_2 + 0x8c) = uVar1;
    return 1;
  }
  return 0;
}

// ==== Aska::IDESpacePartitionBVH::Set(Aska::IDEPrimitiveBase*, Aska::HeightObject*)
// vaddr 0x2346c34 | ghidra 0x2446c34 | size 92 | symbol _ZN4Aska20IDESpacePartitionBVH3SetEPNS_16IDEPrimitiveBaseEPNS_12HeightObjectE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska20IDESpacePartitionBVH3SetEPNS_16IDEPrimitiveBaseEPNS_12HeightObjectE
          (undefined8 param_1,long param_2,long *param_3)

{
  byte bVar1;
  ulong uVar2;
  
  if (*(char *)(param_2 + 0x20) == '\x03') {
    *(long **)(param_2 + 0x80) = param_3;
    uVar2 = (**(code **)(*param_3 + 0x1a0))(param_3);
    bVar1 = 0x80;
    if ((uVar2 & 1) == 0) {
      bVar1 = 0;
    }
    *(byte *)(param_2 + 0x23) = *(byte *)(param_2 + 0x23) | bVar1;
    *(undefined1 *)(param_2 + 0x21) = 1;
    return 1;
  }
  return 0;
}

// ==== Aska::IDESpacePartitionBVH::Set(Aska::IDEPrimitiveBase*, Aska::CollisionHandler*)
// vaddr 0x2346c90 | ghidra 0x2446c90 | size 36 | symbol _ZN4Aska20IDESpacePartitionBVH3SetEPNS_16IDEPrimitiveBaseEPNS_16CollisionHandlerE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska20IDESpacePartitionBVH3SetEPNS_16IDEPrimitiveBaseEPNS_16CollisionHandlerE
          (undefined8 param_1,long param_2,undefined8 param_3)

{
  if (*(char *)(param_2 + 0x20) == '\x04') {
    *(undefined8 *)(param_2 + 0x80) = param_3;
    *(undefined1 *)(param_2 + 0x21) = 1;
    return 1;
  }
  return 0;
}

// ==== Aska::IDESpacePartitionBVH::Set(Aska::IDEPrimitiveBase*, Aska::Box*, Aska::HierarchicalObject*)
// vaddr 0x2346cb4 | ghidra 0x2446cb4 | size 172 | symbol _ZN4Aska20IDESpacePartitionBVH3SetEPNS_16IDEPrimitiveBaseEPNS_3BoxEPNS_18HierarchicalObjectE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska20IDESpacePartitionBVH3SetEPNS_16IDEPrimitiveBaseEPNS_3BoxEPNS_18HierarchicalObjectE
          (undefined8 param_1,long param_2,undefined4 *param_3,undefined8 param_4)

{
  undefined4 uVar1;
  
  if (*(char *)(param_2 + 0x20) == '\x05') {
    *(undefined4 *)(param_2 + 0x80) = *param_3;
    *(undefined4 *)(param_2 + 0x84) = param_3[1];
    *(undefined4 *)(param_2 + 0x88) = param_3[2];
    *(undefined4 *)(param_2 + 0x8c) = param_3[3];
    *(undefined4 *)(param_2 + 0x90) = param_3[4];
    *(undefined4 *)(param_2 + 0x94) = param_3[5];
    *(undefined4 *)(param_2 + 0x98) = param_3[6];
    *(undefined4 *)(param_2 + 0x9c) = param_3[7];
    *(undefined4 *)(param_2 + 0xa0) = param_3[8];
    *(undefined4 *)(param_2 + 0xa4) = param_3[9];
    *(undefined4 *)(param_2 + 0xa8) = param_3[10];
    *(undefined4 *)(param_2 + 0xac) = 0;
    *(undefined4 *)(param_2 + 0xb0) = param_3[0xc];
    *(undefined4 *)(param_2 + 0xb4) = param_3[0xd];
    *(undefined4 *)(param_2 + 0xb8) = param_3[0xe];
    *(undefined4 *)(param_2 + 0xbc) = 0;
    *(undefined4 *)(param_2 + 0xc0) = param_3[0x10];
    *(undefined4 *)(param_2 + 0xc4) = param_3[0x11];
    uVar1 = param_3[0x12];
    *(undefined8 *)(param_2 + 0x120) = param_4;
    *(undefined1 *)(param_2 + 0x21) = 1;
    *(undefined4 *)(param_2 + 200) = uVar1;
    *(undefined4 *)(param_2 + 0xcc) = 0;
    return 1;
  }
  return 0;
}

// ==== Aska::IDESpacePartitionBVH::Delete(Aska::IDEPrimitiveBase*)
// vaddr 0x2346d60 | ghidra 0x2446d60 | size 720 | symbol _ZN4Aska20IDESpacePartitionBVH6DeleteEPNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x02446ee0: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02446ee4) */
/* WARNING: Removing unreachable block (ram,0x02446eec) */

void _ZN4Aska20IDESpacePartitionBVH6DeleteEPNS_16IDEPrimitiveBaseE(long param_1,long *param_2)

{
  long lVar1;
  byte bVar2;
  char cVar3;
  long lVar4;
  undefined8 uVar5;
  long *plVar6;
  long lVar7;
  long lVar8;
  long *plVar9;
  long *plVar10;
  
  if ((param_2[0xc] != 0) || (*(long **)(param_1 + 0x30) == param_2)) {
    bVar2 = *(byte *)(param_2 + 0xf);
    lVar1 = param_1 + 0x10;
    while (*(long **)(param_1 + 0x30) != param_2) {
      plVar10 = (long *)param_2[0xc];
      if (4 < ((uint)*(byte *)(plVar10 + 0xf) + (uint)bVar2) - 1) goto code_r0x02446f30;
      plVar9 = (long *)plVar10[0xe];
      if ((long *)plVar10[0xe] == param_2) {
        plVar10[0xe] = param_2[0xd];
      }
      else {
        do {
          plVar6 = plVar9;
          if (plVar6 == (long *)0x0) goto code_r0x02446ddc;
          plVar9 = (long *)plVar6[0xd];
        } while ((long *)plVar6[0xd] != param_2);
        plVar6[0xd] = param_2[0xd];
      }
code_r0x02446ddc:
      param_2[0xd] = 0;
      *(char *)(param_2[0xc] + 0x78) = *(char *)(param_2[0xc] + 0x78) + -1;
      param_2[0xc] = 0;
      if ((char)param_2[0xf] != '\0') {
        for (lVar7 = param_2[0xe]; lVar7 != 0; lVar7 = *(long *)(lVar7 + 0x68)) {
          lVar8 = *(long *)(lVar7 + 0x60);
          if (lVar8 != 0) {
            lVar4 = *(long *)(lVar8 + 0x70);
            if (*(long *)(lVar8 + 0x70) == lVar7) {
              *(undefined8 *)(lVar8 + 0x70) = *(undefined8 *)(lVar7 + 0x68);
            }
            else {
              do {
                lVar8 = lVar4;
                if (lVar8 == 0) goto code_r0x02446e40;
                lVar4 = *(long *)(lVar8 + 0x68);
              } while (*(long *)(lVar8 + 0x68) != lVar7);
              *(undefined8 *)(lVar8 + 0x68) = *(undefined8 *)(lVar7 + 0x68);
            }
code_r0x02446e40:
            *(undefined8 *)(lVar7 + 0x68) = 0;
            *(char *)(*(long *)(lVar7 + 0x60) + 0x78) =
                 *(char *)(*(long *)(lVar7 + 0x60) + 0x78) + -1;
            *(undefined8 *)(lVar7 + 0x60) = 0;
          }
          lVar8 = plVar10[0xe];
          if (lVar8 == 0) {
            plVar10[0xe] = lVar7;
          }
          else {
            do {
              plVar9 = (long *)(lVar8 + 0x68);
              lVar8 = *plVar9;
            } while (lVar8 != 0);
            *plVar9 = lVar7;
          }
          *(long **)(lVar7 + 0x60) = plVar10;
          *(char *)(plVar10 + 0xf) = (char)plVar10[0xf] + '\x01';
        }
      }
      if (*(char *)((long)param_2 + 0x79) == '\0') {
        Aska::IDEPrimitiveListHandler::Remove(Aska::IDEPrimitiveBase*)(lVar1,param_2);
        if ((*(byte *)((long)param_2 + 0x23) & 1) != 0) goto code_r0x02446ec0;
code_r0x02446ea0:
        cVar3 = *(char *)((long)plVar10 + 0x79);
      }
      else {
        if ((*(byte *)((long)param_2 + 0x23) & 1) == 0) goto code_r0x02446ea0;
code_r0x02446ec0:
        if (*(long *)(param_1 + 8) != 0) {
          (**(code **)*param_2)(param_2);
          uVar5 = *(undefined8 *)(param_1 + 8);
          goto code_r0x011fb8e0;
        }
        (*(code *)((undefined8 *)*param_2)[1])(param_2);
        cVar3 = *(char *)((long)plVar10 + 0x79);
      }
      if (cVar3 != '\0') {
        return;
      }
      bVar2 = 0;
      param_2 = plVar10;
      if ((char)plVar10[0xf] != '\0') {
        return;
      }
    }
    if (1 < bVar2) {
code_r0x02446f30:
      if (*(char *)((long)param_2 + 0x79) == '\0') {
        return;
      }
      *(undefined1 *)((long)param_2 + 0x79) = 0;
      (*(code *)PTR__ZN4Aska23IDEPrimitiveListHandler3AddEPNS_16IDEPrimitiveBaseE_02caba80)
                (lVar1,param_2);
      return;
    }
    lVar7 = param_2[0xe];
    if ((lVar7 != 0) && (lVar8 = *(long *)(lVar7 + 0x60), lVar8 != 0)) {
      lVar4 = *(long *)(lVar8 + 0x70);
      if (*(long *)(lVar8 + 0x70) == lVar7) {
        *(undefined8 *)(lVar8 + 0x70) = *(undefined8 *)(lVar7 + 0x68);
      }
      else {
        do {
          lVar8 = lVar4;
          if (lVar8 == 0) goto code_r0x02446f98;
          lVar4 = *(long *)(lVar8 + 0x68);
        } while (*(long *)(lVar8 + 0x68) != lVar7);
        *(undefined8 *)(lVar8 + 0x68) = *(undefined8 *)(lVar7 + 0x68);
      }
code_r0x02446f98:
      *(undefined8 *)(lVar7 + 0x68) = 0;
      *(char *)(*(long *)(lVar7 + 0x60) + 0x78) = *(char *)(*(long *)(lVar7 + 0x60) + 0x78) + -1;
      *(undefined8 *)(lVar7 + 0x60) = 0;
    }
    *(long *)(param_1 + 0x30) = lVar7;
    if (*(char *)((long)param_2 + 0x79) == '\0') {
      Aska::IDEPrimitiveListHandler::Remove(Aska::IDEPrimitiveBase*)(lVar1,param_2);
      bVar2 = *(byte *)((long)param_2 + 0x23);
      goto joined_r0x02446fe4;
    }
  }
  bVar2 = *(byte *)((long)param_2 + 0x23);
joined_r0x02446fe4:
  if ((bVar2 & 1) == 0) {
    return;
  }
  if (*(long *)(param_1 + 8) == 0) {
                    /* WARNING: Could not recover jumptable at 0x0244702c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)((undefined8 *)*param_2)[1])(param_2);
    return;
  }
  (**(code **)*param_2)(param_2);
  uVar5 = *(undefined8 *)(param_1 + 8);
code_r0x011fb8e0:
  (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPv_02cb5c60)(uVar5,param_2);
  return;
}

// ==== Aska::IDESpacePartitionBVH::DeleteAll()
// vaddr 0x2347030 | ghidra 0x2447030 | size 136 | symbol _ZN4Aska20IDESpacePartitionBVH9DeleteAllEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH9DeleteAllEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  
  plVar2 = *(long **)(param_1 + 0x18);
  while (plVar1 = plVar2, plVar1 != (long *)0x0) {
    plVar2 = (long *)plVar1[2];
    if ((*(byte *)((long)plVar1 + 0x23) & 1) != 0) {
      if (*(long *)(param_1 + 8) == 0) {
        (*(code *)((undefined8 *)*plVar1)[1])(plVar1);
      }
      else {
        (**(code **)*plVar1)(plVar1);
        Aska::MemoryManager::LocalFree(void*)(*(undefined8 *)(param_1 + 8),plVar1);
      }
    }
  }
  Aska::IDEPrimitiveListHandler::Clear()(param_1 + 0x10);
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined1 *)(param_1 + 0x38) = 0;
  return;
}

// ==== Aska::IDESpacePartitionBVH::DeleteAllBranch()
// vaddr 0x23470b8 | ghidra 0x24470b8 | size 136 | symbol _ZN4Aska20IDESpacePartitionBVH15DeleteAllBranchEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH15DeleteAllBranchEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  
  plVar2 = *(long **)(param_1 + 0x18);
  while (plVar1 = plVar2, plVar1 != (long *)0x0) {
    plVar2 = (long *)plVar1[2];
    if ((*(byte *)((long)plVar1 + 0x23) & 1) != 0) {
      if (*(long *)(param_1 + 8) == 0) {
        (*(code *)((undefined8 *)*plVar1)[1])(plVar1);
      }
      else {
        (**(code **)*plVar1)(plVar1);
        Aska::MemoryManager::LocalFree(void*)(*(undefined8 *)(param_1 + 8),plVar1);
      }
    }
  }
  Aska::IDEPrimitiveListHandler::Clear()(param_1 + 0x10);
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined1 *)(param_1 + 0x38) = 0;
  return;
}

// ==== Aska::IDESpacePartitionBVH::Intersect(Aska::Ray const*, unsigned short)
// vaddr 0x2347140 | ghidra 0x2447140 | size 104 | symbol _ZN4Aska20IDESpacePartitionBVH9IntersectEPKNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska20IDESpacePartitionBVH9IntersectEPKNS_3RayEt
               (long param_1,undefined8 *param_2,undefined2 param_3)

{
  undefined2 auStack_50 [8];
  undefined8 uStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined8 uStack_30;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined8 uStack_20;
  
  uStack_40 = *param_2;
  uStack_38 = *(undefined4 *)(param_2 + 1);
  uStack_34 = 0x3f800000;
  uStack_30 = param_2[2];
  uStack_28 = *(undefined4 *)(param_2 + 3);
  uStack_20 = 0;
  uStack_24 = 0x3f800000;
  auStack_50[0] = param_3;
  void Aska::IDESpacePartitionBVH::CollisionDetection<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)0>, true>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)0>*, Aska::IDEPrimitiveBase*)(auStack_50,*(undefined8 *)(param_1 + 0x30));
  Aska::IDE_SyncNotifyOfEvent::Wait(int*)((long)&uStack_20 + 4);
  return (int)uStack_20 != 0;
}

// ==== Aska::IDESpacePartitionBVH::Intersect(Aska::Segment const*, unsigned short)
// vaddr 0x23471a8 | ghidra 0x24471a8 | size 104 | symbol _ZN4Aska20IDESpacePartitionBVH9IntersectEPKNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska20IDESpacePartitionBVH9IntersectEPKNS_7SegmentEt
               (long param_1,undefined8 *param_2,undefined2 param_3)

{
  undefined2 auStack_50 [8];
  undefined8 uStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined8 uStack_30;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined8 uStack_20;
  
  uStack_40 = *param_2;
  uStack_38 = *(undefined4 *)(param_2 + 1);
  uStack_34 = 0x3f800000;
  uStack_30 = param_2[2];
  uStack_28 = *(undefined4 *)(param_2 + 3);
  uStack_20 = 0;
  uStack_24 = 0x3f800000;
  auStack_50[0] = param_3;
  void Aska::IDESpacePartitionBVH::CollisionDetection<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)0>, true>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)0>*, Aska::IDEPrimitiveBase*)(auStack_50,*(undefined8 *)(param_1 + 0x30));
  Aska::IDE_SyncNotifyOfEvent::Wait(int*)((long)&uStack_20 + 4);
  return (int)uStack_20 != 0;
}

// ==== Aska::IDESpacePartitionBVH::FindIntersectNearestPoint(Aska::Vector*, Aska::Ray const*, unsigned short)
// vaddr 0x2347210 | ghidra 0x2447210 | size 152 | symbol _ZN4Aska20IDESpacePartitionBVH25FindIntersectNearestPointEPNS_6VectorEPKNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN4Aska20IDESpacePartitionBVH25FindIntersectNearestPointEPNS_6VectorEPKNS_3RayEt
               (long param_1,undefined8 *param_2,undefined8 *param_3,undefined2 param_4)

{
  undefined2 auStack_70 [8];
  undefined8 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined8 uStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  char cStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  
  uStack_60 = *param_3;
  uStack_58 = *(undefined4 *)(param_3 + 1);
  uStack_54 = 0x3f800000;
  uStack_50 = param_3[2];
  uStack_48 = *(undefined4 *)(param_3 + 3);
  uStack_3c = (undefined4)_UNK_027dbb08;
  uStack_38 = (undefined4)((ulong)_UNK_027dbb08 >> 0x20);
  uStack_44 = (undefined4)_UNK_027dbb00;
  uStack_40 = (undefined4)((ulong)_UNK_027dbb00 >> 0x20);
  uStack_34 = 0x7f7fffff;
  cStack_30 = '\0';
  uStack_2c = 0;
  uStack_28 = 0;
  auStack_70[0] = param_4;
  void Aska::IDESpacePartitionBVH::CollisionDetection<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)1>, true>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)1>*, Aska::IDEPrimitiveBase*)(auStack_70,*(undefined8 *)(param_1 + 0x30));
  Aska::IDE_SyncNotifyOfEvent::Wait(int*)(&uStack_2c);
  if (cStack_30 != '\0') {
    param_2[1] = CONCAT44(uStack_34,uStack_38);
    *param_2 = CONCAT44(uStack_3c,uStack_40);
  }
  return cStack_30 != '\0';
}

// ==== Aska::IDESpacePartitionBVH::FindIntersectNearestPoint(Aska::Vector*, Aska::Segment const*, unsigned short)
// vaddr 0x23472a8 | ghidra 0x24472a8 | size 152 | symbol _ZN4Aska20IDESpacePartitionBVH25FindIntersectNearestPointEPNS_6VectorEPKNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN4Aska20IDESpacePartitionBVH25FindIntersectNearestPointEPNS_6VectorEPKNS_7SegmentEt
               (long param_1,undefined8 *param_2,undefined8 *param_3,undefined2 param_4)

{
  undefined2 auStack_70 [8];
  undefined8 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined8 uStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  char cStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  
  uStack_60 = *param_3;
  uStack_58 = *(undefined4 *)(param_3 + 1);
  uStack_54 = 0x3f800000;
  uStack_50 = param_3[2];
  uStack_48 = *(undefined4 *)(param_3 + 3);
  uStack_3c = (undefined4)_UNK_027dbb08;
  uStack_38 = (undefined4)((ulong)_UNK_027dbb08 >> 0x20);
  uStack_44 = (undefined4)_UNK_027dbb00;
  uStack_40 = (undefined4)((ulong)_UNK_027dbb00 >> 0x20);
  uStack_34 = 0x7f7fffff;
  cStack_30 = '\0';
  uStack_2c = 0;
  uStack_28 = 0;
  auStack_70[0] = param_4;
  void Aska::IDESpacePartitionBVH::CollisionDetection<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)1>, true>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)1>*, Aska::IDEPrimitiveBase*)(auStack_70,*(undefined8 *)(param_1 + 0x30));
  Aska::IDE_SyncNotifyOfEvent::Wait(int*)(&uStack_2c);
  if (cStack_30 != '\0') {
    param_2[1] = CONCAT44(uStack_34,uStack_38);
    *param_2 = CONCAT44(uStack_3c,uStack_40);
  }
  return cStack_30 != '\0';
}

// ==== Aska::IDESpacePartitionBVH::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Ray const*, unsigned short)
// vaddr 0x2347340 | ghidra 0x2447340 | size 216 | symbol _ZN4Aska20IDESpacePartitionBVH26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPKNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN4Aska20IDESpacePartitionBVH26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPKNS_3RayEt
               (long param_1,undefined8 *param_2,undefined8 *param_3,undefined2 param_4)

{
  undefined2 auStack_e0 [8];
  undefined8 uStack_d0;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined8 uStack_c0;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  long lStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 auStack_30 [2];
  
  uStack_d0 = *param_3;
  uStack_c8 = *(undefined4 *)(param_3 + 1);
  uStack_c4 = 0x3f800000;
  uStack_c0 = param_3[2];
  uStack_b8 = *(undefined4 *)(param_3 + 3);
  uStack_ac = (undefined4)_UNK_027dbb08;
  uStack_a8 = (undefined4)((ulong)_UNK_027dbb08 >> 0x20);
  uStack_b4 = (undefined4)_UNK_027dbb00;
  uStack_b0 = (undefined4)((ulong)_UNK_027dbb00 >> 0x20);
  uStack_a4 = 0x7f7fffff;
  lStack_a0 = 0;
  auStack_30[0] = 0;
  auStack_e0[0] = param_4;
  void Aska::IDESpacePartitionBVH::CollisionDetection<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)2>, true>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)0, (Aska::_Enum_IDECollisionDetectionOutputType)2>*, Aska::IDEPrimitiveBase*)(auStack_e0,*(undefined8 *)(param_1 + 0x30));
  Aska::IDE_SyncNotifyOfEvent::Wait(int*)(auStack_30);
  if (lStack_a0 == 0) {
    param_2[2] = 0;
  }
  else {
    param_2[1] = CONCAT44(uStack_a4,uStack_a8);
    *param_2 = CONCAT44(uStack_ac,uStack_b0);
    param_2[3] = uStack_98;
    param_2[2] = lStack_a0;
    param_2[5] = uStack_88;
    param_2[4] = uStack_90;
    param_2[7] = uStack_78;
    param_2[6] = uStack_80;
    param_2[9] = uStack_68;
    param_2[8] = uStack_70;
    param_2[0xb] = uStack_58;
    param_2[10] = uStack_60;
    param_2[0xd] = uStack_48;
    param_2[0xc] = uStack_50;
    param_2[0xf] = uStack_38;
    param_2[0xe] = uStack_40;
  }
  return lStack_a0 != 0;
}

// ==== Aska::IDESpacePartitionBVH::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Segment const*, unsigned short)
// vaddr 0x2347418 | ghidra 0x2447418 | size 216 | symbol _ZN4Aska20IDESpacePartitionBVH26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPKNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN4Aska20IDESpacePartitionBVH26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPKNS_7SegmentEt
               (long param_1,undefined8 *param_2,undefined8 *param_3,undefined2 param_4)

{
  undefined2 auStack_e0 [8];
  undefined8 uStack_d0;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined8 uStack_c0;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  long lStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 auStack_30 [2];
  
  uStack_d0 = *param_3;
  uStack_c8 = *(undefined4 *)(param_3 + 1);
  uStack_c4 = 0x3f800000;
  uStack_c0 = param_3[2];
  uStack_b8 = *(undefined4 *)(param_3 + 3);
  uStack_ac = (undefined4)_UNK_027dbb08;
  uStack_a8 = (undefined4)((ulong)_UNK_027dbb08 >> 0x20);
  uStack_b4 = (undefined4)_UNK_027dbb00;
  uStack_b0 = (undefined4)((ulong)_UNK_027dbb00 >> 0x20);
  uStack_a4 = 0x7f7fffff;
  lStack_a0 = 0;
  auStack_30[0] = 0;
  auStack_e0[0] = param_4;
  void Aska::IDESpacePartitionBVH::CollisionDetection<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)2>, true>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)1, (Aska::_Enum_IDECollisionDetectionOutputType)2>*, Aska::IDEPrimitiveBase*)(auStack_e0,*(undefined8 *)(param_1 + 0x30));
  Aska::IDE_SyncNotifyOfEvent::Wait(int*)(auStack_30);
  if (lStack_a0 == 0) {
    param_2[2] = 0;
  }
  else {
    param_2[1] = CONCAT44(uStack_a4,uStack_a8);
    *param_2 = CONCAT44(uStack_ac,uStack_b0);
    param_2[3] = uStack_98;
    param_2[2] = lStack_a0;
    param_2[5] = uStack_88;
    param_2[4] = uStack_90;
    param_2[7] = uStack_78;
    param_2[6] = uStack_80;
    param_2[9] = uStack_68;
    param_2[8] = uStack_70;
    param_2[0xb] = uStack_58;
    param_2[10] = uStack_60;
    param_2[0xd] = uStack_48;
    param_2[0xc] = uStack_50;
    param_2[0xf] = uStack_38;
    param_2[0xe] = uStack_40;
  }
  return lStack_a0 != 0;
}

// ==== Aska::IDESpacePartitionBVH::GetHeight(Aska::IDE_ResultOfHeight*, Aska::Vector*, unsigned int, unsigned short)
// vaddr 0x23474f0 | ghidra 0x24474f0 | size 288 | symbol _ZN4Aska20IDESpacePartitionBVH9GetHeightEPNS_18IDE_ResultOfHeightEPNS_6VectorEjt | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska20IDESpacePartitionBVH9GetHeightEPNS_18IDE_ResultOfHeightEPNS_6VectorEjt
               (long param_1,undefined4 *param_2,long param_3,uint param_4,undefined2 param_5)

{
  ulong uVar1;
  long lVar2;
  float *pfVar3;
  long lVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined2 auStack_80 [2];
  undefined8 uStack_7c;
  undefined8 uStack_74;
  long lStack_68;
  uint uStack_60;
  undefined4 uStack_40;
  undefined8 uStack_3c;
  undefined4 uStack_34;
  undefined4 *puStack_30;
  uint uStack_28;
  undefined8 uStack_24;
  undefined8 uStack_18;
  
  uStack_74 = _UNK_029e3688;
  uStack_7c = _UNK_029e3680;
  if (param_4 != 0) {
    uVar1 = (ulong)param_4;
    pfVar3 = (float *)(param_3 + 8);
    fVar6 = _UNK_027ebde8;
    fVar5 = _UNK_02884248;
    fVar8 = _UNK_02884248;
    fVar9 = _UNK_027ebde8;
    do {
      fVar10 = pfVar3[-2];
      fVar11 = *pfVar3;
      uVar1 = uVar1 - 1;
      fVar7 = fVar10;
      if (fVar9 <= fVar10) {
        fVar7 = fVar9;
      }
      fVar9 = fVar7;
      fVar7 = fVar11;
      if (fVar6 <= fVar11) {
        fVar7 = fVar6;
      }
      if (fVar10 <= fVar8) {
        fVar10 = fVar8;
      }
      fVar8 = fVar10;
      if (fVar11 <= fVar5) {
        fVar11 = fVar5;
      }
      fVar5 = fVar11;
      pfVar3 = pfVar3 + 4;
      fVar6 = fVar7;
    } while (uVar1 != 0);
    uStack_7c = CONCAT44(fVar8,fVar9);
    uStack_74 = CONCAT44(fVar5,fVar7);
  }
  uStack_40 = 0;
  uStack_3c = 0xbf800000;
  uStack_34 = 0x3f800000;
  if (param_4 != 0) {
    *param_2 = 0xff7fffff;
    *(undefined1 *)(param_2 + 1) = 1;
    if (param_4 != 1) {
      param_2[2] = 0xff7fffff;
      *(undefined1 *)(param_2 + 3) = 1;
      if (param_4 != 2) {
        lVar4 = (ulong)param_4 - 2;
        lVar2 = 0;
        do {
          lVar4 = lVar4 + -1;
          *(undefined4 *)((long)param_2 + lVar2 + 0x10) = 0xff7fffff;
          *(undefined1 *)((long)param_2 + lVar2 + 0x14) = 1;
          lVar2 = lVar2 + 8;
        } while (lVar4 != 0);
      }
    }
  }
  uStack_24 = 0;
  uStack_18 = 0;
  auStack_80[0] = param_5;
  lStack_68 = param_3;
  uStack_60 = param_4;
  puStack_30 = param_2;
  uStack_28 = param_4;
  void Aska::IDESpacePartitionBVH::CollisionDetectionForArray<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)2, (Aska::_Enum_IDECollisionDetectionOutputType)3>, false>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)2, (Aska::_Enum_IDECollisionDetectionOutputType)3>*, Aska::IDEPrimitiveBase*)(auStack_80,*(undefined8 *)(param_1 + 0x30));
  return;
}

// ==== Aska::IDESpacePartitionBVH::FindIntersectNearestObjectArray(Aska::IDE_ResultOfNearestObject*, Aska::Ray*, unsigned int, unsigned short)
// vaddr 0x2347a78 | ghidra 0x2447a78 | size 168 | symbol _ZN4Aska20IDESpacePartitionBVH31FindIntersectNearestObjectArrayEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEjt | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska20IDESpacePartitionBVH31FindIntersectNearestObjectArrayEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEjt
               (long param_1,undefined8 *param_2,undefined8 param_3,uint param_4,undefined2 param_5)

{
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  long lVar4;
  undefined2 auStack_48 [4];
  undefined8 uStack_40;
  uint uStack_38;
  undefined8 *puStack_30;
  uint uStack_28;
  undefined8 uStack_24;
  undefined8 uStack_18;
  
  uVar2 = _UNK_029e36a8;
  uVar1 = _UNK_029e36a0;
  if (param_4 != 0) {
    param_2[2] = 0;
    param_2[1] = uVar2;
    *param_2 = uVar1;
    if (param_4 != 1) {
      param_2[0x12] = 0;
      param_2[0x11] = uVar2;
      param_2[0x10] = uVar1;
      if (param_4 != 2) {
        param_2[0x22] = 0;
        param_2[0x21] = uVar2;
        param_2[0x20] = uVar1;
        if (param_4 != 3) {
          lVar3 = (ulong)param_4 - 3;
          lVar4 = 0x180;
          do {
            lVar3 = lVar3 + -1;
            *(undefined8 *)((long)param_2 + lVar4 + 0x10) = 0;
            ((undefined8 *)((long)param_2 + lVar4))[1] = uVar2;
            *(undefined8 *)((long)param_2 + lVar4) = uVar1;
            lVar4 = lVar4 + 0x80;
          } while (lVar3 != 0);
        }
      }
    }
  }
  uStack_24 = 0;
  uStack_18 = 0;
  auStack_48[0] = param_5;
  uStack_40 = param_3;
  uStack_38 = param_4;
  puStack_30 = param_2;
  uStack_28 = param_4;
  void Aska::IDESpacePartitionBVH::CollisionDetectionForArray<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)3, (Aska::_Enum_IDECollisionDetectionOutputType)4>, false>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)3, (Aska::_Enum_IDECollisionDetectionOutputType)4>*, Aska::IDEPrimitiveBase*)(auStack_48,*(undefined8 *)(param_1 + 0x30));
  return;
}

// ==== Aska::IDESpacePartitionBVH::FindIntersectNearestObjectArray(Aska::IDE_ResultOfNearestObject*, Aska::Segment*, unsigned int, unsigned short)
// vaddr 0x2347b20 | ghidra 0x2447b20 | size 168 | symbol _ZN4Aska20IDESpacePartitionBVH31FindIntersectNearestObjectArrayEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEjt | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska20IDESpacePartitionBVH31FindIntersectNearestObjectArrayEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEjt
               (long param_1,undefined8 *param_2,undefined8 param_3,uint param_4,undefined2 param_5)

{
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  long lVar4;
  undefined2 auStack_48 [4];
  undefined8 uStack_40;
  uint uStack_38;
  undefined8 *puStack_30;
  uint uStack_28;
  undefined8 uStack_24;
  undefined8 uStack_18;
  
  uVar2 = _UNK_029e36a8;
  uVar1 = _UNK_029e36a0;
  if (param_4 != 0) {
    param_2[2] = 0;
    param_2[1] = uVar2;
    *param_2 = uVar1;
    if (param_4 != 1) {
      param_2[0x12] = 0;
      param_2[0x11] = uVar2;
      param_2[0x10] = uVar1;
      if (param_4 != 2) {
        param_2[0x22] = 0;
        param_2[0x21] = uVar2;
        param_2[0x20] = uVar1;
        if (param_4 != 3) {
          lVar3 = (ulong)param_4 - 3;
          lVar4 = 0x180;
          do {
            lVar3 = lVar3 + -1;
            *(undefined8 *)((long)param_2 + lVar4 + 0x10) = 0;
            ((undefined8 *)((long)param_2 + lVar4))[1] = uVar2;
            *(undefined8 *)((long)param_2 + lVar4) = uVar1;
            lVar4 = lVar4 + 0x80;
          } while (lVar3 != 0);
        }
      }
    }
  }
  uStack_24 = 0;
  uStack_18 = 0;
  auStack_48[0] = param_5;
  uStack_40 = param_3;
  uStack_38 = param_4;
  puStack_30 = param_2;
  uStack_28 = param_4;
  void Aska::IDESpacePartitionBVH::CollisionDetectionForArray<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)4, (Aska::_Enum_IDECollisionDetectionOutputType)4>, false>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)4, (Aska::_Enum_IDECollisionDetectionOutputType)4>*, Aska::IDEPrimitiveBase*)(auStack_48,*(undefined8 *)(param_1 + 0x30));
  return;
}

// ==== Aska::IDESpacePartitionBVH::SetBound(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)
// vaddr 0x2347bc8 | ghidra 0x2447bc8 | size 584 | symbol _ZN4Aska20IDESpacePartitionBVH8SetBoundEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska20IDESpacePartitionBVH8SetBoundEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE
               (undefined8 param_1,long param_2)

{
  long lVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  switch(*(undefined1 *)(param_2 + 0x20)) {
  case 1:
    *(float *)(param_2 + 0x38) = *(float *)(param_2 + 0x88);
    *(undefined4 *)(param_2 + 0x3c) = *(undefined4 *)(param_2 + 0x8c);
    *(float *)(param_2 + 0x30) = *(float *)(param_2 + 0x80);
    *(float *)(param_2 + 0x34) = *(float *)(param_2 + 0x84);
    *(float *)(param_2 + 0x40) = *(float *)(param_2 + 0x90);
    *(float *)(param_2 + 0x44) = *(float *)(param_2 + 0x94);
    *(float *)(param_2 + 0x48) = *(float *)(param_2 + 0x98);
    *(undefined4 *)(param_2 + 0x4c) = *(undefined4 *)(param_2 + 0x9c);
    *(float *)(param_2 + 0x50) =
         (*(float *)(param_2 + 0x90) - *(float *)(param_2 + 0x80)) *
         (*(float *)(param_2 + 0x94) - *(float *)(param_2 + 0x84)) *
         (*(float *)(param_2 + 0x98) - *(float *)(param_2 + 0x88));
    return;
  case 2:
    fVar2 = *(float *)(param_2 + 0x8c);
    fVar5 = fVar2 * _UNK_029e3674;
    fVar8 = *(float *)(param_2 + 0x80) - fVar5;
    fVar6 = *(float *)(param_2 + 0x84) - fVar5;
    fVar3 = *(float *)(param_2 + 0x80) + fVar5;
    fVar4 = *(float *)(param_2 + 0x84) + fVar5;
    fVar7 = *(float *)(param_2 + 0x88) - fVar5;
    fVar5 = *(float *)(param_2 + 0x88) + fVar5;
    *(float *)(param_2 + 0x40) = fVar3;
    *(float *)(param_2 + 0x44) = fVar4;
    *(float *)(param_2 + 0x48) = fVar5;
    *(float *)(param_2 + 0x3c) = fVar2;
    *(float *)(param_2 + 0x4c) = fVar2;
    *(float *)(param_2 + 0x30) = fVar8;
    *(float *)(param_2 + 0x34) = fVar6;
    *(float *)(param_2 + 0x38) = fVar7;
    *(float *)(param_2 + 0x50) = (fVar5 - fVar7) * (fVar3 - fVar8) * (fVar4 - fVar6);
    return;
  case 3:
    lVar1 = *(long *)(param_2 + 0x80);
    fVar2 = *(float *)(lVar1 + 0x1c0);
    *(float *)(param_2 + 0x30) = fVar2;
    fVar3 = *(float *)(lVar1 + 0x1c4);
    *(float *)(param_2 + 0x34) = fVar3;
    fVar4 = *(float *)(lVar1 + 0x1c8);
    *(float *)(param_2 + 0x38) = fVar4;
    *(undefined4 *)(param_2 + 0x3c) = *(undefined4 *)(lVar1 + 0x1cc);
    fVar5 = *(float *)(lVar1 + 0x1d0);
    *(float *)(param_2 + 0x40) = fVar5;
    fVar8 = *(float *)(lVar1 + 0x1d4);
    *(float *)(param_2 + 0x44) = fVar8;
    fVar6 = *(float *)(lVar1 + 0x1d8);
    *(float *)(param_2 + 0x48) = fVar6;
    *(undefined4 *)(param_2 + 0x4c) = *(undefined4 *)(lVar1 + 0x1dc);
    *(float *)(param_2 + 0x50) = (fVar5 - fVar2) * (fVar8 - fVar3) * (fVar6 - fVar4);
    return;
  case 4:
    (*(code *)PTR__ZN4Aska33IDESpacePartitionBVH_BoundingAABB3SetEPNS_16CollisionHandlerE_02c9cfd8)
              (param_2 + 0x30,*(undefined8 *)(param_2 + 0x80));
    return;
  case 5:
    fVar4 = *(float *)(param_2 + 0x90);
    fVar5 = *(float *)(param_2 + 0x94);
    fVar8 = *(float *)(param_2 + 0x98);
    fVar2 = ABS(fVar4 * *(float *)(param_2 + 0xa0)) + ABS(fVar5 * *(float *)(param_2 + 0xb0)) +
            ABS(fVar8 * *(float *)(param_2 + 0xc0));
    fVar3 = ABS(fVar4 * *(float *)(param_2 + 0xa4)) + ABS(fVar5 * *(float *)(param_2 + 0xb4)) +
            ABS(fVar8 * *(float *)(param_2 + 0xc4));
    fVar4 = ABS(fVar4 * *(float *)(param_2 + 0xa8)) + ABS(fVar5 * *(float *)(param_2 + 0xb8)) +
            ABS(fVar8 * *(float *)(param_2 + 200));
    *(undefined4 *)(param_2 + 0x3c) = *(undefined4 *)(param_2 + 0x8c);
    *(float *)(param_2 + 0x30) = *(float *)(param_2 + 0x80) - fVar2;
    *(float *)(param_2 + 0x34) = *(float *)(param_2 + 0x84) - fVar3;
    *(float *)(param_2 + 0x38) = *(float *)(param_2 + 0x88) - fVar4;
    *(float *)(param_2 + 0x40) = *(float *)(param_2 + 0x80) + fVar2;
    *(float *)(param_2 + 0x44) = *(float *)(param_2 + 0x84) + fVar3;
    *(float *)(param_2 + 0x48) = *(float *)(param_2 + 0x88) + fVar4;
    *(undefined4 *)(param_2 + 0x4c) = 0x3f800000;
    return;
  default:
    *(undefined4 *)(param_2 + 0x30) = 0;
    *(undefined8 *)(param_2 + 0x34) = 0;
    *(undefined4 *)(param_2 + 0x40) = 0;
    *(undefined8 *)(param_2 + 0x44) = 0;
    *(undefined4 *)(param_2 + 0x50) = 0xbf800000;
    return;
  }
}

// ==== Aska::IDESpacePartitionBVH::SetBound(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*, Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)
// vaddr 0x2347e10 | ghidra 0x2447e10 | size 600 | symbol _ZN4Aska20IDESpacePartitionBVH8SetBoundEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska20IDESpacePartitionBVH8SetBoundEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4_
               (undefined8 param_1,long param_2,long param_3)

{
  undefined4 uVar1;
  long lVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  
  switch(*(undefined1 *)(param_3 + 0x20)) {
  case 1:
    fVar3 = *(float *)(param_3 + 0x80);
    *(float *)(param_2 + 0x30) = fVar3;
    fVar4 = *(float *)(param_3 + 0x84);
    *(float *)(param_2 + 0x34) = fVar4;
    fVar5 = *(float *)(param_3 + 0x88);
    *(float *)(param_2 + 0x38) = fVar5;
    *(undefined4 *)(param_2 + 0x3c) = *(undefined4 *)(param_3 + 0x8c);
    fVar6 = *(float *)(param_3 + 0x90);
    *(float *)(param_2 + 0x40) = fVar6;
    fVar7 = *(float *)(param_3 + 0x94);
    *(float *)(param_2 + 0x44) = fVar7;
    fVar8 = *(float *)(param_3 + 0x98);
    fVar3 = (fVar6 - fVar3) * (fVar7 - fVar4);
    *(float *)(param_2 + 0x48) = fVar8;
    uVar1 = *(undefined4 *)(param_3 + 0x9c);
    break;
  case 2:
    fVar3 = *(float *)(param_3 + 0x8c);
    fVar4 = fVar3 * _UNK_029e3674;
    fVar7 = *(float *)(param_3 + 0x80) - fVar4;
    fVar8 = *(float *)(param_3 + 0x84) - fVar4;
    fVar5 = *(float *)(param_3 + 0x80) + fVar4;
    fVar6 = *(float *)(param_3 + 0x84) + fVar4;
    fVar9 = *(float *)(param_3 + 0x88) - fVar4;
    fVar4 = *(float *)(param_3 + 0x88) + fVar4;
    *(float *)(param_2 + 0x40) = fVar5;
    *(float *)(param_2 + 0x44) = fVar6;
    *(float *)(param_2 + 0x48) = fVar4;
    *(float *)(param_2 + 0x3c) = fVar3;
    *(float *)(param_2 + 0x4c) = fVar3;
    *(float *)(param_2 + 0x30) = fVar7;
    *(float *)(param_2 + 0x34) = fVar8;
    *(float *)(param_2 + 0x38) = fVar9;
    *(float *)(param_2 + 0x50) = (fVar4 - fVar9) * (fVar5 - fVar7) * (fVar6 - fVar8);
    return;
  case 3:
    lVar2 = *(long *)(param_3 + 0x80);
    fVar3 = *(float *)(lVar2 + 0x1c0);
    *(float *)(param_2 + 0x30) = fVar3;
    fVar4 = *(float *)(lVar2 + 0x1c4);
    *(float *)(param_2 + 0x34) = fVar4;
    fVar5 = *(float *)(lVar2 + 0x1c8);
    *(float *)(param_2 + 0x38) = fVar5;
    *(undefined4 *)(param_2 + 0x3c) = *(undefined4 *)(lVar2 + 0x1cc);
    fVar6 = *(float *)(lVar2 + 0x1d0);
    *(float *)(param_2 + 0x40) = fVar6;
    fVar7 = *(float *)(lVar2 + 0x1d4);
    *(float *)(param_2 + 0x44) = fVar7;
    fVar8 = *(float *)(lVar2 + 0x1d8);
    fVar3 = (fVar6 - fVar3) * (fVar7 - fVar4);
    *(float *)(param_2 + 0x48) = fVar8;
    uVar1 = *(undefined4 *)(lVar2 + 0x1dc);
    break;
  case 4:
    (*(code *)PTR__ZN4Aska33IDESpacePartitionBVH_BoundingAABB3SetEPNS_16CollisionHandlerE_02c9cfd8)
              (param_2 + 0x30,*(undefined8 *)(param_3 + 0x80));
    return;
  case 5:
    fVar5 = *(float *)(param_3 + 0x90);
    fVar6 = *(float *)(param_3 + 0x94);
    fVar9 = *(float *)(param_3 + 0x98);
    fVar7 = *(float *)(param_3 + 0x80);
    fVar10 = *(float *)(param_3 + 0x84);
    fVar8 = *(float *)(param_3 + 0x88);
    fVar3 = ABS(fVar5 * *(float *)(param_3 + 0xa0)) + ABS(fVar6 * *(float *)(param_3 + 0xb0)) +
            ABS(fVar9 * *(float *)(param_3 + 0xc0));
    fVar4 = ABS(fVar5 * *(float *)(param_3 + 0xa4)) + ABS(fVar6 * *(float *)(param_3 + 0xb4)) +
            ABS(fVar9 * *(float *)(param_3 + 0xc4));
    fVar5 = ABS(fVar5 * *(float *)(param_3 + 0xa8)) + ABS(fVar6 * *(float *)(param_3 + 0xb8)) +
            ABS(fVar9 * *(float *)(param_3 + 200));
    *(undefined4 *)(param_2 + 0x3c) = *(undefined4 *)(param_3 + 0x8c);
    *(float *)(param_2 + 0x30) = fVar7 - fVar3;
    *(float *)(param_2 + 0x34) = fVar10 - fVar4;
    *(float *)(param_2 + 0x38) = fVar8 - fVar5;
    *(float *)(param_2 + 0x40) = fVar7 + fVar3;
    *(float *)(param_2 + 0x44) = fVar10 + fVar4;
    *(float *)(param_2 + 0x48) = fVar8 + fVar5;
    *(undefined4 *)(param_2 + 0x4c) = 0x3f800000;
    return;
  default:
    *(undefined4 *)(param_2 + 0x30) = 0;
    *(undefined8 *)(param_2 + 0x34) = 0;
    *(undefined4 *)(param_2 + 0x40) = 0;
    *(undefined8 *)(param_2 + 0x44) = 0;
    *(undefined4 *)(param_2 + 0x50) = 0xbf800000;
    return;
  }
  *(undefined4 *)(param_2 + 0x4c) = uVar1;
  *(float *)(param_2 + 0x50) = fVar3 * (fVar8 - fVar5);
  return;
}

// ==== Aska::IDESpacePartitionBVH::Revert(Aska::IDEPrimitiveListHandler*)
// vaddr 0x2348068 | ghidra 0x2448068 | size 116 | symbol _ZN4Aska20IDESpacePartitionBVH6RevertEPNS_23IDEPrimitiveListHandlerE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH6RevertEPNS_23IDEPrimitiveListHandlerE
               (undefined8 param_1,long param_2)

{
  long *plVar1;
  
  for (plVar1 = *(long **)(param_2 + 8); plVar1 != (long *)0x0; plVar1 = (long *)plVar1[2]) {
    if (*(char *)((long)plVar1 + 0x21) != '\0') {
      param_1 = (**(code **)(*plVar1 + 0x30))(plVar1);
      *(undefined1 *)((long)plVar1 + 0x21) = 0;
    }
    *(undefined1 *)(plVar1 + 0xf) = 0;
    plVar1[0xd] = 0;
    plVar1[0xe] = 0;
    plVar1[0xc] = 0;
    *(undefined1 *)((long)plVar1 + 0x79) = 1;
    plVar1[6] = 0;
    *(undefined4 *)(plVar1 + 7) = 0;
    plVar1[8] = 0;
    *(undefined4 *)(plVar1 + 9) = 0;
    *(undefined4 *)(plVar1 + 10) = 0xbf800000;
    param_1 = Aska::IDESpacePartitionBVH::SetBound(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)(param_1,plVar1);
  }
  return;
}

// ==== Aska::IDESpacePartitionBVH::DivideGroup(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)
// vaddr 0x23480dc | ghidra 0x24480dc | size 316 | symbol _ZN4Aska20IDESpacePartitionBVH11DivideGroupEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH11DivideGroupEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE
               (undefined8 param_1,long param_2)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  long lVar5;
  long lVar6;
  
  if (4 < *(byte *)(param_2 + 0x78)) {
    for (lVar6 = *(long *)(param_2 + 0x70); lVar6 != 0; lVar6 = *(long *)(lVar6 + 0x68)) {
      lVar3 = *(long *)(lVar6 + 0x68);
      while (lVar1 = lVar3, lVar1 != 0) {
        lVar3 = *(long *)(lVar1 + 0x68);
        if ((((0.0 <= *(float *)(lVar6 + 0x50)) &&
             (*(float *)(lVar6 + 0x30) <= *(float *)(lVar1 + 0x30))) &&
            (*(float *)(lVar6 + 0x34) <= *(float *)(lVar1 + 0x34))) &&
           (((*(float *)(lVar6 + 0x38) <= *(float *)(lVar1 + 0x38) &&
             (*(float *)(lVar1 + 0x40) <= *(float *)(lVar6 + 0x40))) &&
            ((*(float *)(lVar1 + 0x44) <= *(float *)(lVar6 + 0x44) &&
             (*(float *)(lVar1 + 0x48) <= *(float *)(lVar6 + 0x48))))))) {
          lVar5 = *(long *)(lVar1 + 0x60);
          if (lVar5 != 0) {
            lVar2 = *(long *)(lVar5 + 0x70);
            if (*(long *)(lVar5 + 0x70) == lVar1) {
              *(long *)(lVar5 + 0x70) = lVar3;
            }
            else {
              do {
                lVar5 = lVar2;
                if (lVar5 == 0) goto code_r0x024481ac;
                lVar2 = *(long *)(lVar5 + 0x68);
              } while (*(long *)(lVar5 + 0x68) != lVar1);
              *(long *)(lVar5 + 0x68) = lVar3;
            }
code_r0x024481ac:
            *(undefined8 *)(lVar1 + 0x68) = 0;
            *(char *)(*(long *)(lVar1 + 0x60) + 0x78) =
                 *(char *)(*(long *)(lVar1 + 0x60) + 0x78) + -1;
            *(undefined8 *)(lVar1 + 0x60) = 0;
          }
          lVar5 = *(long *)(lVar6 + 0x70);
          if (lVar5 == 0) {
            *(long *)(lVar6 + 0x70) = lVar1;
          }
          else {
            do {
              plVar4 = (long *)(lVar5 + 0x68);
              lVar5 = *plVar4;
            } while (lVar5 != 0);
            *plVar4 = lVar1;
          }
          *(long *)(lVar1 + 0x60) = lVar6;
          *(char *)(lVar6 + 0x78) = *(char *)(lVar6 + 0x78) + '\x01';
        }
      }
      _ZN4Aska20IDESpacePartitionBVH11DivideGroupEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE
                (param_1,lVar6);
    }
  }
  return;
}

// ==== Aska::IDESpacePartitionBVH::DivideBranch(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)
// vaddr 0x2348218 | ghidra 0x2448218 | size 1720 | symbol _ZN4Aska20IDESpacePartitionBVH12DivideBranchEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska20IDESpacePartitionBVH12DivideBranchEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE
               (long param_1,long param_2)

{
  float *pfVar1;
  float *pfVar2;
  long *plVar3;
  undefined *puVar4;
  byte bVar5;
  uint uVar6;
  long *plVar7;
  long *plVar8;
  char cVar9;
  long *plVar10;
  long *plVar11;
  long *plVar12;
  long *plVar13;
  long lVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  undefined *puStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined **ppuStack_c8;
  undefined2 uStack_bf;
  undefined1 uStack_bd;
  undefined4 uStack_b0;
  undefined8 uStack_ac;
  undefined4 uStack_a0;
  undefined8 uStack_9c;
  undefined4 uStack_90;
  undefined8 uStack_80;
  undefined8 uStack_78;
  long *plStack_70;
  byte bStack_68;
  undefined1 uStack_67;
  
  bVar5 = *(byte *)(param_2 + 0x78);
  if (bVar5 < 5) {
    for (lVar14 = *(long *)(param_2 + 0x70); lVar14 != 0; lVar14 = *(long *)(lVar14 + 0x68)) {
      _ZN4Aska20IDESpacePartitionBVH12DivideBranchEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE
                (param_1,lVar14);
    }
  }
  else {
    uVar16 = bVar5 + 3;
    uVar6 = uVar16 >> 2;
    uVar17 = 0;
    if (uVar6 != 0) {
      uVar17 = ((bVar5 + uVar6) - 1) / uVar6;
    }
    uVar15 = uVar17;
    if (0xf < uVar16 || uVar17 <= uVar6) {
      uVar15 = uVar6;
      uVar6 = uVar17;
    }
    plVar7 = *(long **)(param_2 + 0x70);
    fVar18 = _UNK_02884248;
    if (plVar7 == (long *)0x0) {
      fVar19 = -3.4028235e+38;
      fVar20 = -3.4028235e+38;
    }
    else {
      fVar19 = -3.4028235e+38;
      fVar20 = -3.4028235e+38;
      plVar10 = plVar7;
      do {
        plVar11 = plVar10 + 8;
        plVar8 = plVar10 + 6;
        pfVar1 = (float *)(plVar10 + 9);
        pfVar2 = (float *)(plVar10 + 7);
        plVar10 = (long *)plVar10[0xd];
        fVar22 = ((float)*plVar11 - (float)*plVar8) * 0.5;
        fVar23 = ((float)((ulong)*plVar11 >> 0x20) - (float)((ulong)*plVar8 >> 0x20)) * 0.5;
        fVar21 = (*pfVar1 - *pfVar2) * 0.5;
        fVar19 = (float)((uint)fVar22 ^ ((uint)fVar22 ^ (uint)fVar19) & -(uint)(fVar22 < fVar19));
        fVar20 = (float)((uint)fVar23 ^ ((uint)fVar23 ^ (uint)fVar20) & -(uint)(fVar23 < fVar20));
        if (fVar18 <= fVar21) {
          fVar18 = fVar21;
        }
      } while (plVar10 != (long *)0x0);
    }
    ppuStack_c8 = &puStack_e0;
    fVar19 = fVar19 / (((float)*(undefined8 *)(param_2 + 0x40) -
                       (float)*(undefined8 *)(param_2 + 0x30)) * 0.5);
    fVar20 = fVar20 / (((float)((ulong)*(undefined8 *)(param_2 + 0x40) >> 0x20) -
                       (float)((ulong)*(undefined8 *)(param_2 + 0x30) >> 0x20)) * 0.5);
    uStack_d8 = 0;
    uStack_d0 = 0;
    uStack_bf = 1;
    fVar18 = fVar18 / ((*(float *)(param_2 + 0x48) - *(float *)(param_2 + 0x38)) * 0.5);
    uStack_bd = 1;
    cVar9 = '\x02';
    if (fVar18 < fVar20) {
      cVar9 = '\x01';
    }
    bStack_68 = 0;
    if (fVar19 <= fVar20) {
      cVar9 = fVar18 < fVar19;
    }
    puStack_e0 = PTR__ZTVN4Aska18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE_02cbfec0 +
                 0x10;
    uStack_78 = 0;
    plStack_70 = (long *)0x0;
    uStack_80 = 0;
    uStack_b0 = 0;
    uStack_ac = 0;
    uStack_a0 = 0;
    uStack_9c = 0;
    uStack_90 = 0xbf800000;
    if (cVar9 == '\x02') {
      if (plVar7 != (long *)0x0) {
        do {
          lVar14 = plVar7[0xc];
          plVar10 = (long *)plVar7[0xd];
          if (lVar14 != 0) {
            plVar11 = *(long **)(lVar14 + 0x70);
            if (*(long **)(lVar14 + 0x70) == plVar7) {
              *(long **)(lVar14 + 0x70) = plVar10;
            }
            else {
              do {
                plVar8 = plVar11;
                if (plVar8 == (long *)0x0) goto code_r0x024484e8;
                plVar11 = (long *)plVar8[0xd];
              } while ((long *)plVar8[0xd] != plVar7);
              plVar8[0xd] = (long)plVar10;
            }
code_r0x024484e8:
            plVar7[0xd] = 0;
            *(char *)(plVar7[0xc] + 0x78) = *(char *)(plVar7[0xc] + 0x78) + -1;
            plVar7[0xc] = 0;
          }
          plVar11 = plVar7;
          if (plStack_70 != (long *)0x0) {
            plVar8 = (long *)0x0;
            plVar13 = plStack_70;
            do {
              if ((*(float *)((long)plVar7 + 0x44) + *(float *)((long)plVar7 + 0x34)) * 0.5 <
                  (*(float *)((long)plVar13 + 0x44) + *(float *)((long)plVar13 + 0x34)) * 0.5) {
                if (plVar8 == (long *)0x0) {
                  plVar7[0xd] = (long)plStack_70;
                }
                else {
                  plVar7[0xd] = plVar8[0xd];
                  plVar8[0xd] = (long)plVar7;
                  plVar11 = plStack_70;
                }
                goto code_r0x02448584;
              }
              plVar3 = plVar13 + 0xd;
              plVar12 = plStack_70;
              plVar8 = plVar13;
              plVar13 = (long *)*plVar3;
            } while ((long *)*plVar3 != (long *)0x0);
            do {
              plVar11 = plVar12 + 0xd;
              plVar12 = (long *)*plVar11;
            } while (plVar12 != (long *)0x0);
            *plVar11 = (long)plVar7;
            plVar11 = plStack_70;
          }
code_r0x02448584:
          plStack_70 = plVar11;
          plVar7[0xc] = (long)&puStack_e0;
          bStack_68 = bStack_68 + 1;
          plVar7 = plVar10;
        } while (plVar10 != (long *)0x0);
      }
    }
    else if (cVar9 == '\x01') {
      if (plVar7 != (long *)0x0) {
        do {
          lVar14 = plVar7[0xc];
          plVar10 = (long *)plVar7[0xd];
          if (lVar14 != 0) {
            plVar11 = *(long **)(lVar14 + 0x70);
            if (*(long **)(lVar14 + 0x70) == plVar7) {
              *(long **)(lVar14 + 0x70) = plVar10;
            }
            else {
              do {
                plVar8 = plVar11;
                if (plVar8 == (long *)0x0) goto code_r0x024485dc;
                plVar11 = (long *)plVar8[0xd];
              } while ((long *)plVar8[0xd] != plVar7);
              plVar8[0xd] = (long)plVar10;
            }
code_r0x024485dc:
            plVar7[0xd] = 0;
            *(char *)(plVar7[0xc] + 0x78) = *(char *)(plVar7[0xc] + 0x78) + -1;
            plVar7[0xc] = 0;
          }
          plVar11 = plVar7;
          if (plStack_70 != (long *)0x0) {
            plVar8 = (long *)0x0;
            plVar13 = plStack_70;
            do {
              if ((*(float *)(plVar7 + 9) + *(float *)(plVar7 + 7)) * 0.5 <
                  (*(float *)(plVar13 + 9) + *(float *)(plVar13 + 7)) * 0.5) {
                if (plVar8 == (long *)0x0) {
                  plVar7[0xd] = (long)plStack_70;
                }
                else {
                  plVar7[0xd] = plVar8[0xd];
                  plVar8[0xd] = (long)plVar7;
                  plVar11 = plStack_70;
                }
                goto code_r0x02448678;
              }
              plVar3 = plVar13 + 0xd;
              plVar12 = plStack_70;
              plVar8 = plVar13;
              plVar13 = (long *)*plVar3;
            } while ((long *)*plVar3 != (long *)0x0);
            do {
              plVar11 = plVar12 + 0xd;
              plVar12 = (long *)*plVar11;
            } while (plVar12 != (long *)0x0);
            *plVar11 = (long)plVar7;
            plVar11 = plStack_70;
          }
code_r0x02448678:
          plStack_70 = plVar11;
          plVar7[0xc] = (long)&puStack_e0;
          bStack_68 = bStack_68 + 1;
          plVar7 = plVar10;
        } while (plVar10 != (long *)0x0);
      }
    }
    else if ((cVar9 == '\0') && (plVar7 != (long *)0x0)) {
      do {
        lVar14 = plVar7[0xc];
        plVar10 = (long *)plVar7[0xd];
        if (lVar14 != 0) {
          plVar11 = *(long **)(lVar14 + 0x70);
          if (*(long **)(lVar14 + 0x70) == plVar7) {
            *(long **)(lVar14 + 0x70) = plVar10;
          }
          else {
            do {
              plVar8 = plVar11;
              if (plVar8 == (long *)0x0) goto code_r0x024483f4;
              plVar11 = (long *)plVar8[0xd];
            } while ((long *)plVar8[0xd] != plVar7);
            plVar8[0xd] = (long)plVar10;
          }
code_r0x024483f4:
          plVar7[0xd] = 0;
          *(char *)(plVar7[0xc] + 0x78) = *(char *)(plVar7[0xc] + 0x78) + -1;
          plVar7[0xc] = 0;
        }
        plVar11 = plVar7;
        if (plStack_70 != (long *)0x0) {
          plVar8 = (long *)0x0;
          plVar13 = plStack_70;
          do {
            if ((*(float *)(plVar7 + 8) + *(float *)(plVar7 + 6)) * 0.5 <
                (*(float *)(plVar13 + 8) + *(float *)(plVar13 + 6)) * 0.5) {
              if (plVar8 == (long *)0x0) {
                plVar7[0xd] = (long)plStack_70;
              }
              else {
                plVar7[0xd] = plVar8[0xd];
                plVar8[0xd] = (long)plVar7;
                plVar11 = plStack_70;
              }
              goto code_r0x02448490;
            }
            plVar3 = plVar13 + 0xd;
            plVar12 = plStack_70;
            plVar8 = plVar13;
            plVar13 = (long *)*plVar3;
          } while ((long *)*plVar3 != (long *)0x0);
          do {
            plVar11 = plVar12 + 0xd;
            plVar12 = (long *)*plVar11;
          } while (plVar12 != (long *)0x0);
          *plVar11 = (long)plVar7;
          plVar11 = plStack_70;
        }
code_r0x02448490:
        plStack_70 = plVar11;
        plVar7[0xc] = (long)&puStack_e0;
        bStack_68 = bStack_68 + 1;
        plVar7 = plVar10;
      } while (plVar10 != (long *)0x0);
    }
    uStack_67 = 1;
    if (uVar6 != 0) {
      uVar16 = 0;
      puVar4 = PTR__ZTVN4Aska12IDEPrimitiveILNS_26_EnumIDESpacePartitionTypeE0ELNS_21_EnumIDEPrimitiveTypeE0EEE_02cbf7e8
               + 0x10;
      do {
        if (*(long *)(param_1 + 8) == 0) {
          plVar7 = (long *)operator new(unsigned long, unsigned long, bool)(0x80,0x10,1);
          if (plVar7 != (long *)0x0) goto code_r0x024486e4;
code_r0x02448744:
          lVar14 = plStack_70[0xc];
          if (lVar14 != 0) {
            plVar7 = *(long **)(lVar14 + 0x70);
            if (*(long **)(lVar14 + 0x70) == plStack_70) {
              *(long *)(lVar14 + 0x70) = plStack_70[0xd];
            }
            else {
              do {
                plVar10 = plVar7;
                if (plVar10 == (long *)0x0) goto code_r0x02448784;
                plVar7 = (long *)plVar10[0xd];
              } while ((long *)plVar10[0xd] != plStack_70);
              plVar10[0xd] = plStack_70[0xd];
            }
code_r0x02448784:
            plStack_70[0xd] = 0;
            *(char *)(plStack_70[0xc] + 0x78) = *(char *)(plStack_70[0xc] + 0x78) + -1;
            plStack_70[0xc] = 0;
          }
          uVar17 = uVar6 - uVar16;
          uVar15 = 0;
          if (uVar17 != 0) {
            uVar15 = ((uVar17 + bStack_68) - 1) / uVar17;
          }
          lVar14 = *(long *)(param_2 + 0x70);
          plVar7 = plStack_70;
          if (lVar14 == 0) goto code_r0x024487bc;
code_r0x024487c8:
          do {
            plVar10 = (long *)(lVar14 + 0x68);
            lVar14 = *plVar10;
          } while (lVar14 != 0);
          *plVar10 = (long)plVar7;
        }
        else {
          plVar7 = (long *)Aska::MemoryManager::AlignedMalloc(unsigned long, long)(*(long *)(param_1 + 8),0x80,0x10);
code_r0x024486e4:
          plVar7[1] = 0;
          plVar7[2] = 0;
          *(undefined2 *)((long)plVar7 + 0x21) = 1;
          plVar7[3] = (long)plVar7;
          *(undefined1 *)((long)plVar7 + 0x23) = 1;
          plVar7[0xd] = 0;
          plVar7[0xe] = 0;
          *(undefined1 *)(plVar7 + 0xf) = 0;
          plVar7[0xc] = 0;
          *(undefined1 *)((long)plVar7 + 0x79) = 1;
          plVar7[6] = 0;
          *(undefined4 *)(plVar7 + 7) = 0;
          plVar7[8] = 0;
          *(undefined4 *)(plVar7 + 9) = 0;
          *(undefined4 *)(plVar7 + 10) = 0xbf800000;
          *plVar7 = (long)puVar4;
          *(undefined1 *)(plVar7 + 4) = 0;
          if (plVar7 == (long *)0x0) goto code_r0x02448744;
          Aska::IDEPrimitiveListHandler::Add(Aska::IDEPrimitiveBase*)(param_1 + 0x10,plVar7);
          *(undefined1 *)((long)plVar7 + 0x79) = 0;
          lVar14 = *(long *)(param_2 + 0x70);
          if (lVar14 != 0) goto code_r0x024487c8;
code_r0x024487bc:
          *(long **)(param_2 + 0x70) = plVar7;
        }
        plVar7[0xc] = param_2;
        *(char *)(param_2 + 0x78) = *(char *)(param_2 + 0x78) + '\x01';
        if ((plStack_70 != (long *)0x0) && (uVar15 != 0)) {
          uVar17 = 0;
          plVar10 = plStack_70;
          do {
            lVar14 = plVar10[0xc];
            plVar11 = (long *)plVar10[0xd];
            if (lVar14 != 0) {
              plVar8 = *(long **)(lVar14 + 0x70);
              if (*(long **)(lVar14 + 0x70) == plVar10) {
                *(long **)(lVar14 + 0x70) = plVar11;
              }
              else {
                do {
                  plVar13 = plVar8;
                  if (plVar13 == (long *)0x0) goto code_r0x0244882c;
                  plVar8 = (long *)plVar13[0xd];
                } while ((long *)plVar13[0xd] != plVar10);
                plVar13[0xd] = (long)plVar11;
              }
code_r0x0244882c:
              plVar10[0xd] = 0;
              *(char *)(plVar10[0xc] + 0x78) = *(char *)(plVar10[0xc] + 0x78) + -1;
              plVar10[0xc] = 0;
            }
            Aska::IDESpacePartitionBVH_BoundingAABB::Resize(Aska::IDESpacePartitionBVH_BoundingAABB*)(plVar7 + 6,plVar10 + 6);
            lVar14 = plVar7[0xe];
            if (lVar14 == 0) {
              plVar7[0xe] = (long)plVar10;
            }
            else {
              do {
                plVar8 = (long *)(lVar14 + 0x68);
                lVar14 = *plVar8;
              } while (lVar14 != 0);
              *plVar8 = (long)plVar10;
            }
            plVar10[0xc] = (long)plVar7;
            *(char *)(plVar7 + 0xf) = (char)plVar7[0xf] + '\x01';
          } while ((plVar11 != (long *)0x0) &&
                  (uVar17 = uVar17 + 1, plVar10 = plVar11, uVar17 < uVar15));
        }
        _ZN4Aska20IDESpacePartitionBVH12DivideBranchEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE
                  (param_1,plVar7);
        uVar16 = uVar16 + 1;
      } while (uVar16 != uVar6);
    }
  }
  return;
}

// ==== Aska::IDESpacePartitionBVH::FixUpGroup(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)
// vaddr 0x23488d0 | ghidra 0x24488d0 | size 4 | symbol _ZN4Aska20IDESpacePartitionBVH10FixUpGroupEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH10FixUpGroupEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE
               (void)

{
  return;
}

// ==== Aska::IDESpacePartitionBVH::DevideAxis(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)
// vaddr 0x23488d4 | ghidra 0x24488d4 | size 180 | symbol _ZN4Aska20IDESpacePartitionBVH10DevideAxisEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1
_ZN4Aska20IDESpacePartitionBVH10DevideAxisEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE
          (undefined8 param_1,long param_2)

{
  float *pfVar1;
  float *pfVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined1 uVar5;
  long lVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  
  lVar6 = *(long *)(param_2 + 0x70);
  fVar7 = _UNK_02884248;
  if (lVar6 == 0) {
    fVar8 = -3.4028235e+38;
    fVar9 = -3.4028235e+38;
  }
  else {
    fVar8 = -3.4028235e+38;
    fVar9 = -3.4028235e+38;
    do {
      puVar3 = (undefined8 *)(lVar6 + 0x40);
      puVar4 = (undefined8 *)(lVar6 + 0x30);
      pfVar1 = (float *)(lVar6 + 0x48);
      pfVar2 = (float *)(lVar6 + 0x38);
      lVar6 = *(long *)(lVar6 + 0x68);
      fVar11 = ((float)*puVar3 - (float)*puVar4) * 0.5;
      fVar12 = ((float)((ulong)*puVar3 >> 0x20) - (float)((ulong)*puVar4 >> 0x20)) * 0.5;
      fVar10 = (*pfVar1 - *pfVar2) * 0.5;
      fVar8 = (float)((uint)fVar11 ^ ((uint)fVar11 ^ (uint)fVar8) & -(uint)(fVar11 < fVar8));
      fVar9 = (float)((uint)fVar12 ^ ((uint)fVar12 ^ (uint)fVar9) & -(uint)(fVar12 < fVar9));
      if (fVar7 <= fVar10) {
        fVar7 = fVar10;
      }
    } while (lVar6 != 0);
  }
  fVar8 = fVar8 / (((float)*(undefined8 *)(param_2 + 0x40) - (float)*(undefined8 *)(param_2 + 0x30))
                  * 0.5);
  fVar9 = fVar9 / (((float)((ulong)*(undefined8 *)(param_2 + 0x40) >> 0x20) -
                   (float)((ulong)*(undefined8 *)(param_2 + 0x30) >> 0x20)) * 0.5);
  fVar7 = fVar7 / ((*(float *)(param_2 + 0x48) - *(float *)(param_2 + 0x38)) * 0.5);
  uVar5 = 2;
  if (fVar7 < fVar9) {
    uVar5 = 1;
  }
  if (fVar8 <= fVar9) {
    uVar5 = fVar7 < fVar8;
  }
  return uVar5;
}

// ==== Aska::IDESpacePartitionBVH::ForceAddChild(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*, Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)
// vaddr 0x2348988 | ghidra 0x2448988 | size 504 | symbol _ZN4Aska20IDESpacePartitionBVH13ForceAddChildEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH13ForceAddChildEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4_
               (undefined8 param_1,long param_2,long param_3)

{
  long lVar1;
  byte bVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  byte *pbVar8;
  long lVar9;
  
  lVar6 = *(long *)(param_3 + 0x70);
  if (lVar6 != 0) {
    lVar4 = *(long *)(lVar6 + 0x60);
    if (lVar4 != 0) {
      lVar7 = *(long *)(lVar4 + 0x70);
      if (*(long *)(lVar4 + 0x70) == lVar6) {
        *(undefined8 *)(lVar4 + 0x70) = *(undefined8 *)(lVar6 + 0x68);
      }
      else {
        do {
          lVar4 = lVar7;
          if (lVar4 == 0) goto code_r0x024489d8;
          lVar7 = *(long *)(lVar4 + 0x68);
        } while (*(long *)(lVar4 + 0x68) != lVar6);
        *(undefined8 *)(lVar4 + 0x68) = *(undefined8 *)(lVar6 + 0x68);
      }
code_r0x024489d8:
      *(undefined8 *)(lVar6 + 0x68) = 0;
      *(char *)(*(long *)(lVar6 + 0x60) + 0x78) = *(char *)(*(long *)(lVar6 + 0x60) + 0x78) + -1;
      *(undefined8 *)(lVar6 + 0x60) = 0;
    }
    lVar4 = *(long *)(param_2 + 0x70);
    if (lVar4 == 0) {
      *(long *)(param_2 + 0x70) = lVar6;
    }
    else {
      do {
        plVar3 = (long *)(lVar4 + 0x68);
        lVar4 = *plVar3;
      } while (lVar4 != 0);
      *plVar3 = lVar6;
    }
    *(long *)(lVar6 + 0x60) = param_2;
    *(char *)(param_2 + 0x78) = *(char *)(param_2 + 0x78) + '\x01';
    lVar4 = *(long *)(param_3 + 0x70);
    while (lVar4 != 0) {
      lVar7 = *(long *)(lVar4 + 0x60);
      lVar1 = *(long *)(lVar4 + 0x68);
      if (lVar7 != 0) {
        lVar9 = *(long *)(lVar7 + 0x70);
        if (*(long *)(lVar7 + 0x70) == lVar4) {
          *(long *)(lVar7 + 0x70) = lVar1;
        }
        else {
          do {
            lVar7 = lVar9;
            if (lVar7 == 0) goto code_r0x02448a5c;
            lVar9 = *(long *)(lVar7 + 0x68);
          } while (*(long *)(lVar7 + 0x68) != lVar4);
          *(long *)(lVar7 + 0x68) = lVar1;
        }
code_r0x02448a5c:
        *(undefined8 *)(lVar4 + 0x68) = 0;
        *(char *)(*(long *)(lVar4 + 0x60) + 0x78) = *(char *)(*(long *)(lVar4 + 0x60) + 0x78) + -1;
        *(undefined8 *)(lVar4 + 0x60) = 0;
      }
      pbVar8 = (byte *)(lVar6 + 0x78);
      bVar2 = *pbVar8;
      while (lVar7 = lVar6, lVar9 = lVar4, 3 < bVar2) {
        lVar7 = *(long *)(lVar6 + 0x68);
        if (lVar7 == 0) {
          lVar7 = *(long *)(lVar6 + 0x70);
        }
        pbVar8 = (byte *)(lVar7 + 0x78);
        lVar6 = lVar7;
        bVar2 = *pbVar8;
      }
      while ((((lVar5 = lVar7, *(float *)(lVar5 + 0x50) < 0.0 ||
               (*(float *)(lVar9 + 0x30) < *(float *)(lVar5 + 0x30))) ||
              (*(float *)(lVar9 + 0x34) < *(float *)(lVar5 + 0x34))) ||
             (((*(float *)(lVar9 + 0x38) < *(float *)(lVar5 + 0x38) ||
               (*(float *)(lVar5 + 0x40) < *(float *)(lVar9 + 0x40))) ||
              ((*(float *)(lVar5 + 0x44) < *(float *)(lVar9 + 0x44) ||
               (*(float *)(lVar5 + 0x48) < *(float *)(lVar9 + 0x48)))))))) {
        Aska::IDESpacePartitionBVH_BoundingAABB::Resize(Aska::IDESpacePartitionBVH_BoundingAABB*)(lVar5 + 0x30);
        lVar9 = lVar5;
        lVar7 = *(long *)(lVar5 + 0x60);
      }
      lVar7 = *(long *)(lVar6 + 0x70);
      if (lVar7 == 0) {
        *(long *)(lVar6 + 0x70) = lVar4;
      }
      else {
        do {
          plVar3 = (long *)(lVar7 + 0x68);
          lVar7 = *plVar3;
        } while (lVar7 != 0);
        *plVar3 = lVar4;
      }
      *(long *)(lVar4 + 0x60) = lVar6;
      *pbVar8 = *pbVar8 + 1;
      lVar4 = lVar1;
    }
  }
  return;
}

// ==== Aska::IDESpacePartitionBVH::ModifyHierarchyRecursiv(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*, Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)
// vaddr 0x2348b80 | ghidra 0x2448b80 | size 228 | symbol _ZN4Aska20IDESpacePartitionBVH23ModifyHierarchyRecursivEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH23ModifyHierarchyRecursivEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4_
               (undefined8 param_1,long param_2,long param_3)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  
  lVar1 = *(long *)(param_2 + 0x70);
  while (lVar3 = lVar1, lVar3 != 0) {
    while ((((*(float *)(lVar3 + 0x50) < 0.0 ||
             (*(float *)(param_3 + 0x30) < *(float *)(lVar3 + 0x30))) ||
            (*(float *)(param_3 + 0x34) < *(float *)(lVar3 + 0x34))) ||
           (((*(float *)(param_3 + 0x38) < *(float *)(lVar3 + 0x38) ||
             (*(float *)(lVar3 + 0x40) < *(float *)(param_3 + 0x40))) ||
            ((*(float *)(lVar3 + 0x44) < *(float *)(param_3 + 0x44) ||
             (*(float *)(lVar3 + 0x48) < *(float *)(param_3 + 0x48)))))))) {
      lVar3 = *(long *)(lVar3 + 0x68);
      if (lVar3 == 0) goto code_r0x02448c2c;
    }
    param_2 = lVar3;
    lVar1 = *(long *)(lVar3 + 0x70);
  }
code_r0x02448c2c:
  uVar2 = Aska::IDESpacePartitionBVH::ModifyParent(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*, Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)(param_1,param_2,param_3);
  if ((uVar2 & 1) == 0) {
    (*(code *)
      PTR__ZN4Aska20IDESpacePartitionBVH14ModifyChildrenEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4__02cab058
    )(param_1,param_2,param_3);
    return;
  }
  return;
}

// ==== Aska::IDESpacePartitionBVH::ModifyParent(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*, Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)
// vaddr 0x2348c64 | ghidra 0x2448c64 | size 648 | symbol _ZN4Aska20IDESpacePartitionBVH12ModifyParentEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska20IDESpacePartitionBVH12ModifyParentEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4_
          (long param_1,long param_2,long param_3)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  long *plVar4;
  uint uVar5;
  long lVar6;
  float fVar7;
  long alStack_20 [4];
  
  if (param_2 == 0) {
    if (*(float *)(param_3 + 0x50) < 0.0) {
      return 0;
    }
    lVar2 = *(long *)(param_1 + 0x30);
    if (*(float *)(lVar2 + 0x30) < *(float *)(param_3 + 0x30)) {
      return 0;
    }
    if (*(float *)(lVar2 + 0x34) < *(float *)(param_3 + 0x34)) {
      return 0;
    }
    if (*(float *)(lVar2 + 0x38) < *(float *)(param_3 + 0x38)) {
      return 0;
    }
    if (*(float *)(param_3 + 0x40) < *(float *)(lVar2 + 0x40)) {
      return 0;
    }
    if (*(float *)(param_3 + 0x44) < *(float *)(lVar2 + 0x44)) {
      return 0;
    }
    if (*(float *)(param_3 + 0x48) < *(float *)(lVar2 + 0x48)) {
      return 0;
    }
    lVar6 = *(long *)(param_3 + 0x70);
    if (lVar6 == 0) {
      *(long *)(param_3 + 0x70) = lVar2;
    }
    else {
      do {
        plVar4 = (long *)(lVar6 + 0x68);
        lVar6 = *plVar4;
      } while (lVar6 != 0);
      *plVar4 = lVar2;
    }
    *(long *)(lVar2 + 0x60) = param_3;
    *(char *)(param_3 + 0x78) = *(char *)(param_3 + 0x78) + '\x01';
    *(long *)(param_1 + 0x30) = param_3;
    return 1;
  }
  lVar2 = *(long *)(param_2 + 0x70);
  if (lVar2 == 0) {
    return 0;
  }
  if (*(float *)(param_3 + 0x50) < 0.0) {
    do {
      lVar2 = *(long *)(lVar2 + 0x68);
    } while (lVar2 != 0);
    return 0;
  }
  fVar7 = *(float *)(param_3 + 0x30);
  uVar5 = 0;
  do {
    if ((((fVar7 <= *(float *)(lVar2 + 0x30)) &&
         (*(float *)(param_3 + 0x34) <= *(float *)(lVar2 + 0x34))) &&
        (*(float *)(param_3 + 0x38) <= *(float *)(lVar2 + 0x38))) &&
       (((*(float *)(lVar2 + 0x40) <= *(float *)(param_3 + 0x40) &&
         (*(float *)(lVar2 + 0x44) <= *(float *)(param_3 + 0x44))) &&
        (*(float *)(lVar2 + 0x48) <= *(float *)(param_3 + 0x48))))) {
      alStack_20[uVar5] = lVar2;
      uVar5 = uVar5 + 1;
    }
    lVar2 = *(long *)(lVar2 + 0x68);
  } while (lVar2 != 0);
  if (uVar5 == 0) {
    return 0;
  }
  uVar3 = 0;
  do {
    lVar2 = alStack_20[uVar3];
    lVar6 = *(long *)(lVar2 + 0x60);
    if (lVar6 != 0) {
      lVar1 = *(long *)(lVar6 + 0x70);
      if (*(long *)(lVar6 + 0x70) == lVar2) {
        *(undefined8 *)(lVar6 + 0x70) = *(undefined8 *)(lVar2 + 0x68);
      }
      else {
        do {
          lVar6 = lVar1;
          if (lVar6 == 0) goto code_r0x02448d4c;
          lVar1 = *(long *)(lVar6 + 0x68);
        } while (*(long *)(lVar6 + 0x68) != lVar2);
        *(undefined8 *)(lVar6 + 0x68) = *(undefined8 *)(lVar2 + 0x68);
      }
code_r0x02448d4c:
      *(undefined8 *)(lVar2 + 0x68) = 0;
      *(char *)(*(long *)(lVar2 + 0x60) + 0x78) = *(char *)(*(long *)(lVar2 + 0x60) + 0x78) + -1;
      *(undefined8 *)(lVar2 + 0x60) = 0;
    }
    lVar6 = *(long *)(param_3 + 0x70);
    if (lVar6 == 0) {
      *(long *)(param_3 + 0x70) = lVar2;
    }
    else {
      do {
        plVar4 = (long *)(lVar6 + 0x68);
        lVar6 = *plVar4;
      } while (lVar6 != 0);
      *plVar4 = lVar2;
    }
    *(long *)(lVar2 + 0x60) = param_3;
    uVar3 = uVar3 + 1;
    *(char *)(param_3 + 0x78) = *(char *)(param_3 + 0x78) + '\x01';
    if (uVar3 == uVar5) {
      lVar2 = *(long *)(param_2 + 0x70);
      if (lVar2 == 0) {
        *(long *)(param_2 + 0x70) = param_3;
      }
      else {
        do {
          plVar4 = (long *)(lVar2 + 0x68);
          lVar2 = *plVar4;
        } while (lVar2 != 0);
        *plVar4 = param_3;
      }
      *(long *)(param_3 + 0x60) = param_2;
      *(char *)(param_2 + 0x78) = *(char *)(param_2 + 0x78) + '\x01';
      return 1;
    }
  } while( true );
}

// ==== Aska::IDESpacePartitionBVH::ModifyChildren(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*, Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)
// vaddr 0x2348eec | ghidra 0x2448eec | size 468 | symbol _ZN4Aska20IDESpacePartitionBVH14ModifyChildrenEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska20IDESpacePartitionBVH14ModifyChildrenEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4_
               (undefined8 param_1,long param_2,long param_3)

{
  byte bVar1;
  float fVar2;
  byte *pbVar3;
  long *plVar4;
  long lVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  
  fVar2 = _UNK_027ebde8;
  pbVar3 = (byte *)(param_2 + 0x78);
  bVar1 = *pbVar3;
  while (3 < bVar1) {
    lVar5 = *(long *)(param_2 + 0x70);
    if (lVar5 == 0) {
      param_2 = 0;
    }
    else {
      fVar6 = *(float *)(param_3 + 0x40);
      fVar9 = *(float *)(param_3 + 0x30);
      fVar13 = (float)*(undefined8 *)(param_3 + 0x44);
      fVar17 = (float)*(undefined8 *)(param_3 + 0x34);
      fVar15 = (float)((ulong)*(undefined8 *)(param_3 + 0x44) >> 0x20);
      fVar19 = (float)((ulong)*(undefined8 *)(param_3 + 0x34) >> 0x20);
      param_2 = 0;
      fVar21 = fVar2;
      do {
        fVar7 = *(float *)(lVar5 + 0x40);
        fVar10 = *(float *)(lVar5 + 0x30);
        fVar14 = (float)*(undefined8 *)(lVar5 + 0x44);
        fVar18 = (float)*(undefined8 *)(lVar5 + 0x34);
        fVar16 = (float)((ulong)*(undefined8 *)(lVar5 + 0x44) >> 0x20);
        fVar20 = (float)((ulong)*(undefined8 *)(lVar5 + 0x34) >> 0x20);
        fVar8 = (fVar6 + fVar9) * 0.5 - (fVar7 + fVar10) * 0.5;
        fVar11 = (fVar13 + fVar17) * 0.5 - (fVar14 + fVar18) * 0.5;
        fVar12 = (fVar15 + fVar19) * 0.5 - (fVar16 + fVar20) * 0.5;
        fVar11 = fVar8 * fVar8 + fVar11 * fVar11 + fVar12 * fVar12;
        fVar8 = SQRT(fVar11);
        if (NAN(fVar8)) {
          fVar8 = (float)sqrtf(fVar11);
        }
        fVar10 = fVar8 - ((fVar6 - fVar9) * 0.5 + (fVar7 - fVar10) * 0.5);
        fVar7 = fVar8 - ((fVar13 - fVar17) * 0.5 + (fVar14 - fVar18) * 0.5);
        fVar8 = fVar8 - ((fVar15 - fVar19) * 0.5 + (fVar16 - fVar20) * 0.5);
        if (fVar10 <= fVar7) {
          fVar7 = fVar10;
        }
        if (fVar7 <= fVar8) {
          fVar8 = fVar7;
        }
        if (fVar8 <= fVar21) {
          param_2 = lVar5;
        }
        lVar5 = *(long *)(lVar5 + 0x70);
        if (fVar8 <= fVar21) {
          fVar21 = fVar8;
        }
      } while (lVar5 != 0);
    }
    pbVar3 = (byte *)(param_2 + 0x78);
    bVar1 = *pbVar3;
  }
  lVar5 = *(long *)(param_2 + 0x70);
  if (lVar5 == 0) {
    *(long *)(param_2 + 0x70) = param_3;
  }
  else {
    do {
      plVar4 = (long *)(lVar5 + 0x68);
      lVar5 = *plVar4;
    } while (lVar5 != 0);
    *plVar4 = param_3;
  }
  *(long *)(param_3 + 0x60) = param_2;
  *pbVar3 = *pbVar3 + 1;
  *(undefined1 *)(param_2 + 0x21) = 1;
  (*(code *)
    PTR__ZN4Aska20IDESpacePartitionBVH20UpdateBoundHierarchyEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEE_02cac7c0
  )(param_1,param_2);
  return;
}

// ==== Aska::IDESpacePartitionBVH::FindIntersectPrimitives(Aska::IDEIntersectNotify*)
// vaddr 0x23490c0 | ghidra 0x24490c0 | size 32 | symbol _ZN4Aska20IDESpacePartitionBVH23FindIntersectPrimitivesEPNS_18IDEIntersectNotifyE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH23FindIntersectPrimitivesEPNS_18IDEIntersectNotifyE
               (long param_1,undefined8 param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(*(long *)(param_1 + 0x30) + 0x70);
  if (lVar1 != 0) {
    (*(code *)
      PTR__ZN4Aska20IDESpacePartitionBVH29FindIntersectPrimitives_Main0EPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEEPNS_18IDEIntersectNotifyE_02c9a280
    )(param_1,lVar1,param_2);
    return;
  }
  return;
}

// ==== Aska::IDESpacePartitionBVH::FindIntersectPrimitives_Main0(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*, Aska::IDEIntersectNotify*)
// vaddr 0x23490e0 | ghidra 0x24490e0 | size 140 | symbol _ZN4Aska20IDESpacePartitionBVH29FindIntersectPrimitives_Main0EPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEEPNS_18IDEIntersectNotifyE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH29FindIntersectPrimitives_Main0EPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEEPNS_18IDEIntersectNotifyE
               (undefined8 param_1,long param_2,undefined8 param_3)

{
  long lVar1;
  long lVar2;
  
  while (param_2 != 0) {
    lVar2 = *(long *)(param_2 + 0x68);
    lVar1 = lVar2;
    if (lVar2 == 0) {
      param_2 = *(long *)(param_2 + 0x70);
    }
    else {
      do {
        Aska::IDESpacePartitionBVH::FindIntersectPrimitives_Main1(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*, Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*, Aska::IDEIntersectNotify*, bool)(param_1,param_2,lVar1,param_3,1);
        lVar1 = *(long *)(lVar1 + 0x68);
      } while (lVar1 != 0);
      _ZN4Aska20IDESpacePartitionBVH29FindIntersectPrimitives_Main0EPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEEPNS_18IDEIntersectNotifyE
                (param_1,*(undefined8 *)(param_2 + 0x70),param_3);
      param_2 = lVar2;
    }
  }
  return;
}

// ==== Aska::IDESpacePartitionBVH::FindIntersectPrimitives_Main1(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*, Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*, Aska::IDEIntersectNotify*, bool)
// vaddr 0x234916c | ghidra 0x244916c | size 212 | symbol _ZN4Aska20IDESpacePartitionBVH29FindIntersectPrimitives_Main1EPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4_PNS_18IDEIntersectNotifyEb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH29FindIntersectPrimitives_Main1EPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4_PNS_18IDEIntersectNotifyEb
               (undefined8 param_1,long param_2,long param_3,undefined8 *param_4,ulong param_5)

{
  ulong uVar1;
  long lVar2;
  
  uVar1 = Aska::Collision::Intersect(Aska::AABB_MinMax const*, Aska::AABB_MinMax const*)(param_2 + 0x30,param_3 + 0x30);
  if ((uVar1 & 1) != 0) {
    if (((*(char *)(param_2 + 0x79) != '\0') && (*(char *)(param_3 + 0x79) != '\0')) &&
       (uVar1 = Aska::IDESpacePartitionBVH::IntersectPrimitives(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*, Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)(uVar1,param_2,param_3), (uVar1 & 1) != 0)) {
      param_4[1] = param_2;
      param_4[2] = param_3;
      (**(code **)*param_4)(param_4,0);
    }
    for (lVar2 = *(long *)(param_2 + 0x70); lVar2 != 0; lVar2 = *(long *)(lVar2 + 0x68)) {
      _ZN4Aska20IDESpacePartitionBVH29FindIntersectPrimitives_Main1EPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4_PNS_18IDEIntersectNotifyEb
                (param_1,lVar2,param_3,param_4,0);
    }
    if ((param_5 & 1) != 0) {
      for (lVar2 = *(long *)(param_3 + 0x70); lVar2 != 0; lVar2 = *(long *)(lVar2 + 0x68)) {
        _ZN4Aska20IDESpacePartitionBVH29FindIntersectPrimitives_Main1EPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4_PNS_18IDEIntersectNotifyEb
                  (param_1,param_2,lVar2,param_4,1);
      }
    }
  }
  return;
}

// ==== Aska::IDESpacePartitionBVH::IntersectPrimitives(Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*, Aska::SpacePartitionData<(Aska::_EnumIDESpacePartitionType)0>*)
// vaddr 0x2349240 | ghidra 0x2449240 | size 884 | symbol _ZN4Aska20IDESpacePartitionBVH19IntersectPrimitivesEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x02449484: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02449488) */

ulong _ZN4Aska20IDESpacePartitionBVH19IntersectPrimitivesEPNS_18SpacePartitionDataILNS_26_EnumIDESpacePartitionTypeE0EEES4_
                (undefined8 param_1,long param_2,long param_3)

{
  bool bVar1;
  bool bVar2;
  uint uVar3;
  ulong uVar4;
  long lVar5;
  float *pfVar6;
  float *pfVar7;
  undefined8 uVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  undefined4 uStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined8 uStack_4c;
  undefined8 uStack_44;
  undefined4 uStack_3c;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  pfVar6 = &fStack_70;
  uVar3 = 0;
  switch(*(undefined1 *)(param_2 + 0x20)) {
  case 1:
    uVar3 = 0;
    if (4 < *(byte *)(param_3 + 0x20) - 1) goto code_r0x024494e8;
    lVar5 = param_2 + 0x80;
    switch((uint)*(byte *)(param_3 + 0x20)) {
    case 1:
      uVar4 = (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_11AABB_MinMaxES3__02cb0af8)
                        (lVar5,param_3 + 0x80);
      return uVar4;
    case 2:
      fVar9 = (float)Aska::AABB_MinMax::CalcDistance(Aska::Vector const*) const(lVar5,param_3 + 0x80);
      fVar10 = *(float *)(param_3 + 0x8c);
code_r0x024493f8:
      bVar2 = fVar10 <= fVar9;
      bVar1 = fVar9 == fVar10;
      break;
    case 3:
      goto code_r0x024494e8;
    case 4:
      fStack_70 = *(float *)(param_2 + 0x90) + *(float *)(param_2 + 0x80);
      fStack_6c = *(float *)(param_2 + 0x94) + *(float *)(param_2 + 0x84);
      fStack_68 = *(float *)(param_2 + 0x98) + *(float *)(param_2 + 0x88);
      fStack_60 = *(float *)(param_2 + 0x90) - *(float *)(param_2 + 0x80);
      fStack_5c = *(float *)(param_2 + 0x94) - *(float *)(param_2 + 0x84);
      fStack_58 = *(float *)(param_2 + 0x98) - *(float *)(param_2 + 0x88);
      uStack_54 = *(undefined4 *)(param_2 + 0x9c);
      uVar8 = *(undefined8 *)(param_3 + 0x80);
      goto code_r0x02449484;
    case 5:
      pfVar6 = (float *)(param_3 + 0x80);
code_r0x02449494:
      uVar4 = (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_11AABB_MinMaxEPKNS_3BoxE_02ca67c8)
                        (lVar5,pfVar6);
      return uVar4;
    }
    break;
  case 2:
    uVar3 = 0;
    if (4 < *(byte *)(param_3 + 0x20) - 1) goto code_r0x024494e8;
    pfVar7 = (float *)(param_2 + 0x80);
    switch((uint)*(byte *)(param_3 + 0x20)) {
    case 1:
      fVar9 = (float)Aska::AABB_MinMax::CalcDistance(Aska::Vector const*) const(param_3 + 0x80,pfVar7);
      fVar10 = *(float *)(param_2 + 0x8c);
      goto code_r0x024493f8;
    case 2:
      fVar9 = *(float *)(param_2 + 0x8c) + *(float *)(param_3 + 0x8c);
      fVar10 = *pfVar7 - *(float *)(param_3 + 0x80);
      fVar11 = (float)*(undefined8 *)(param_2 + 0x84) - (float)*(undefined8 *)(param_3 + 0x84);
      fVar12 = (float)((ulong)*(undefined8 *)(param_2 + 0x84) >> 0x20) -
               (float)((ulong)*(undefined8 *)(param_3 + 0x84) >> 0x20);
      fVar10 = fVar10 * fVar10 + fVar11 * fVar11 + fVar12 * fVar12;
      fVar9 = fVar9 * fVar9;
      bVar1 = false;
      bVar2 = true;
      if (!NAN(fVar10) && !NAN(fVar9)) {
        bVar1 = fVar10 == fVar9;
        bVar2 = fVar9 <= fVar10;
      }
      break;
    case 3:
      goto code_r0x024494e8;
    case 4:
      uVar8 = *(undefined8 *)(param_3 + 0x80);
code_r0x02449524:
      uVar4 = (*(code *)
                PTR__ZN4Aska9Collision9IntersectEPKNS_16CollisionHandlerEtPKNS_6VectorE_02ca3200)
                        (uVar8,0xffff,pfVar7);
      return uVar4;
    case 5:
      pfVar6 = (float *)(param_3 + 0x80);
code_r0x02449570:
      uVar4 = (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_3BoxEPKNS_6VectorE_02ca76b8)
                        (pfVar6,pfVar7);
      return uVar4;
    }
    break;
  default:
    goto code_r0x024494e8;
  case 4:
    uVar3 = 0;
    if (4 < *(byte *)(param_3 + 0x20) - 1) goto code_r0x024494e8;
    uVar8 = *(undefined8 *)(param_2 + 0x80);
    switch((uint)*(byte *)(param_3 + 0x20)) {
    case 1:
      fStack_70 = *(float *)(param_3 + 0x90) + *(float *)(param_3 + 0x80);
      fStack_6c = *(float *)(param_3 + 0x94) + *(float *)(param_3 + 0x84);
      fStack_68 = *(float *)(param_3 + 0x98) + *(float *)(param_3 + 0x88);
      fStack_60 = *(float *)(param_3 + 0x90) - *(float *)(param_3 + 0x80);
      fStack_5c = *(float *)(param_3 + 0x94) - *(float *)(param_3 + 0x84);
      fStack_58 = *(float *)(param_3 + 0x98) - *(float *)(param_3 + 0x88);
      uStack_54 = *(undefined4 *)(param_3 + 0x9c);
      break;
    case 2:
      pfVar7 = (float *)(param_3 + 0x80);
      goto code_r0x02449524;
    case 3:
      goto code_r0x024494e8;
    case 4:
      uVar4 = (*(code *)
                PTR__ZN4Aska9Collision9IntersectEPKNS_16CollisionHandlerEtS3_tPKNS_6MatrixE_02ca8548
              )(uVar8,0xffff,*(undefined8 *)(param_3 + 0x80),0xffff,0);
      return uVar4;
    case 5:
      pfVar6 = (float *)(param_3 + 0x80);
      goto code_r0x011fcc00;
    }
code_r0x02449484:
    fStack_58 = fStack_58 * 0.5;
    fStack_5c = fStack_5c * 0.5;
    fStack_60 = fStack_60 * 0.5;
    fStack_68 = fStack_68 * 0.5;
    fStack_6c = fStack_6c * 0.5;
    fStack_70 = fStack_70 * 0.5;
    uStack_28 = 0x3f800000;
    uStack_30 = 0;
    uStack_38 = 0;
    uStack_3c = 0x3f800000;
    uStack_44 = 0;
    uStack_4c = 0;
    uStack_50 = 0x3f800000;
    uStack_64 = 0x3f800000;
code_r0x011fcc00:
    uVar4 = (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_16CollisionHandlerEtPKNS_3BoxE_02cb65f0)
                      (uVar8,0xffff,pfVar6);
    return uVar4;
  case 5:
    uVar3 = 0;
    if (*(byte *)(param_3 + 0x20) - 1 < 5) {
      pfVar6 = (float *)(param_2 + 0x80);
      switch((uint)*(byte *)(param_3 + 0x20)) {
      case 1:
        lVar5 = param_3 + 0x80;
        goto code_r0x02449494;
      case 2:
        pfVar7 = (float *)(param_3 + 0x80);
        goto code_r0x02449570;
      case 4:
        uVar8 = *(undefined8 *)(param_3 + 0x80);
        goto code_r0x011fcc00;
      case 5:
        uVar4 = (*(code *)PTR__ZN4Aska9Collision9IntersectEPKNS_3BoxES3__02c92188)
                          (pfVar6,param_3 + 0x80);
        return uVar4;
      }
    }
    goto code_r0x024494e8;
  }
  uVar3 = (uint)(!bVar2 || bVar1);
code_r0x024494e8:
  return (ulong)uVar3;
}

// ==== Aska::IDESpacePartitionBVH::FindIntersectObjects(Aska::INotify*, Aska::Vector const*, unsigned short)
// vaddr 0x23495b4 | ghidra 0x24495b4 | size 84 | symbol _ZN4Aska20IDESpacePartitionBVH20FindIntersectObjectsEPNS_7INotifyEPKNS_6VectorEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH20FindIntersectObjectsEPNS_7INotifyEPKNS_6VectorEt
               (long param_1,undefined8 param_2,undefined8 *param_3,undefined2 param_4)

{
  undefined2 auStack_80 [8];
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined4 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined4 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  uStack_68 = param_3[1];
  uStack_70 = *param_3;
  uStack_20 = 0;
  uStack_40 = 0;
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_60 = 0;
  uStack_58 = 0;
  uStack_28 = 0;
  uStack_38 = 0;
  uStack_30 = 0;
  auStack_80[0] = param_4;
  uStack_18 = param_2;
  void Aska::IDESpacePartitionBVH::CollisionDetection<Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)5, (Aska::_Enum_IDECollisionDetectionOutputType)5>, true>(Aska::IDE_CollisionDetectionParam<(Aska::_Enum_IDECollisionDetectionInputType)5, (Aska::_Enum_IDECollisionDetectionOutputType)5>*, Aska::IDEPrimitiveBase*)(auStack_80,*(undefined8 *)(param_1 + 0x30));
  Aska::IDE_SyncNotifyOfEvent::Wait(int*)(&uStack_58);
  return;
}

// ==== Aska::IDESpacePartitionBVH::PostFindIntersectObjects(Aska::IDE_ResultOfFindObjects*, int, unsigned int*, unsigned int*, Aska::INotify*, Aska::Box const*, unsigned int, unsigned short)
// vaddr 0x2349608 | ghidra 0x2449608 | size 288 | symbol _ZN4Aska20IDESpacePartitionBVH24PostFindIntersectObjectsEPNS_23IDE_ResultOfFindObjectsEiPjS3_PNS_7INotifyEPKNS_3BoxEjt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH24PostFindIntersectObjectsEPNS_23IDE_ResultOfFindObjectsEiPjS3_PNS_7INotifyEPKNS_3BoxEjt
               (long param_1)

{
  ulong uVar1;
  undefined8 in_x5;
  undefined8 in_x6;
  int iVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  long *plVar6;
  undefined2 in_stack_00000000;
  undefined8 uStack_270;
  undefined8 uStack_268;
  undefined8 uStack_260;
  undefined4 uStack_258;
  undefined8 uStack_250;
  undefined8 uStack_248;
  undefined4 uStack_240;
  long alStack_238 [61];
  
  alStack_238[0] = 0;
  uStack_258 = 0;
  uStack_268 = 0;
  uStack_260 = 0;
  uStack_270 = 0;
  uStack_240 = 0;
  uStack_250 = 0;
  uStack_248 = 0;
  iVar2 = 0;
  plVar3 = *(long **)(param_1 + 0x30);
code_r0x02449664:
  do {
    lVar4 = (long)iVar2;
    if ((char)plVar3[0xf] == '\0') {
      plVar6 = (long *)0x0;
    }
    else {
      plVar6 = (long *)plVar3[0xe];
    }
    alStack_238[lVar4 + 1] = (long)plVar6;
    uVar1 = Aska::Collision::Intersect(Aska::AABB_MinMax const*, Aska::Box const*)(plVar3 + 6,in_x6);
    if ((uVar1 & 1) != 0) {
      if (*(char *)((long)plVar3 + 0x79) != '\0') {
        (**(code **)(*plVar3 + 0x70))(plVar3,in_x5,in_x6,in_stack_00000000);
      }
      if ((iVar2 < 0x3b) && (plVar6 != (long *)0x0)) {
        alStack_238[lVar4 + 1] = plVar6[0xd];
        iVar2 = iVar2 + 1;
        plVar3 = plVar6;
        goto code_r0x02449664;
      }
    }
    iVar2 = iVar2 + 1;
    do {
      lVar5 = lVar4;
      if (lVar5 < 1) {
        Aska::IDE_SyncNotifyOfEvent::Wait(int*)(&uStack_270);
        return;
      }
      iVar2 = iVar2 + -1;
      lVar4 = lVar5 + -1;
    } while ((0x3b < lVar5) || (plVar3 = (long *)alStack_238[lVar5], plVar3 == (long *)0x0));
    alStack_238[lVar5] = plVar3[0xd];
  } while( true );
}

// ==== Aska::IDESpacePartitionBVH::PostFindIntersectObjects_Wait()
// vaddr 0x2349728 | ghidra 0x2449728 | size 4 | symbol _ZN4Aska20IDESpacePartitionBVH29PostFindIntersectObjects_WaitEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH29PostFindIntersectObjects_WaitEv(void)

{
  return;
}

// ==== Aska::IDESpacePartitionBVH::FindIntersectObjects(Aska::INotify*, Aska::Box const*, unsigned short)
// vaddr 0x234972c | ghidra 0x244972c | size 288 | symbol _ZN4Aska20IDESpacePartitionBVH20FindIntersectObjectsEPNS_7INotifyEPKNS_3BoxEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH20FindIntersectObjectsEPNS_7INotifyEPKNS_3BoxEt
               (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  ulong uVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  long *plVar6;
  undefined8 uStack_270;
  undefined8 uStack_268;
  undefined8 uStack_260;
  undefined4 uStack_258;
  undefined8 uStack_250;
  undefined8 uStack_248;
  undefined4 uStack_240;
  long alStack_238 [61];
  
  alStack_238[0] = 0;
  uStack_258 = 0;
  uStack_268 = 0;
  uStack_260 = 0;
  uStack_270 = 0;
  uStack_240 = 0;
  uStack_250 = 0;
  uStack_248 = 0;
  iVar2 = 0;
  plVar3 = *(long **)(param_1 + 0x30);
code_r0x02449788:
  do {
    lVar4 = (long)iVar2;
    if ((char)plVar3[0xf] == '\0') {
      plVar6 = (long *)0x0;
    }
    else {
      plVar6 = (long *)plVar3[0xe];
    }
    alStack_238[lVar4 + 1] = (long)plVar6;
    uVar1 = Aska::Collision::Intersect(Aska::AABB_MinMax const*, Aska::Box const*)(plVar3 + 6,param_3);
    if ((uVar1 & 1) != 0) {
      if (*(char *)((long)plVar3 + 0x79) != '\0') {
        (**(code **)(*plVar3 + 0x70))(plVar3,param_2,param_3,param_4);
      }
      if ((iVar2 < 0x3b) && (plVar6 != (long *)0x0)) {
        alStack_238[lVar4 + 1] = plVar6[0xd];
        iVar2 = iVar2 + 1;
        plVar3 = plVar6;
        goto code_r0x02449788;
      }
    }
    iVar2 = iVar2 + 1;
    do {
      lVar5 = lVar4;
      if (lVar5 < 1) {
        Aska::IDE_SyncNotifyOfEvent::Wait(int*)(&uStack_270);
        return;
      }
      iVar2 = iVar2 + -1;
      lVar4 = lVar5 + -1;
    } while ((0x3b < lVar5) || (plVar3 = (long *)alStack_238[lVar5], plVar3 == (long *)0x0));
    alStack_238[lVar5] = plVar3[0xd];
  } while( true );
}

// ==== Aska::IDESpacePartitionBVH::Attach(Aska::IDEPrimitiveBase*, int, Aska::IDEPrimitiveBase*, int)
// vaddr 0x234984c | ghidra 0x244984c | size 72 | symbol _ZN4Aska20IDESpacePartitionBVH6AttachEPNS_16IDEPrimitiveBaseEiS2_i | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska20IDESpacePartitionBVH6AttachEPNS_16IDEPrimitiveBaseEiS2_i
          (long param_1,long param_2,int param_3,long param_4,int param_5)

{
  if (param_3 < 1) {
    if (param_5 != 1) {
      return 0;
    }
  }
  else {
    *(long *)(param_1 + 0x18) = param_2;
    *(long *)(param_1 + 0x20) = param_2 + (long)(param_3 + -1) * 0x80;
    param_4 = param_2;
  }
  *(long *)(param_1 + 0x30) = param_4;
  *(int *)(param_1 + 0x28) = param_3;
  *(undefined1 *)(param_1 + 0x38) = 1;
  return 1;
}

// ==== Aska::IDESpacePartitionBVH::GetType()
// vaddr 0x2349894 | ghidra 0x2449894 | size 8 | symbol _ZN4Aska20IDESpacePartitionBVH7GetTypeEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska20IDESpacePartitionBVH7GetTypeEv(void)

{
  return 0;
}

// ==== Aska::IDESpacePartitionBVH::IsAvailable()
// vaddr 0x234989c | ghidra 0x244989c | size 16 | symbol _ZN4Aska20IDESpacePartitionBVH11IsAvailableEv | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska20IDESpacePartitionBVH11IsAvailableEv(long param_1)

{
  return *(long *)(param_1 + 0x30) != 0;
}

// ==== Aska::IDESpacePartitionBVH::IsClean() const
// vaddr 0x23498ac | ghidra 0x24498ac | size 8 | symbol _ZNK4Aska20IDESpacePartitionBVH7IsCleanEv | lib libSOA-3.7.0.so | 2026-10-08
undefined1 _ZNK4Aska20IDESpacePartitionBVH7IsCleanEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x39);
}

// ==== Aska::IDESpacePartitionBVH::SetClean(bool)
// vaddr 0x23498b4 | ghidra 0x24498b4 | size 12 | symbol _ZN4Aska20IDESpacePartitionBVH8SetCleanEb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska20IDESpacePartitionBVH8SetCleanEb(long param_1,byte param_2)

{
  *(byte *)(param_1 + 0x39) = param_2 & 1;
  return;
}

// ==== Aska::IDESpacePartitionBVH_BoundingAABB::Set(Aska::CollisionHandler*)
// vaddr 0x23498c0 | ghidra 0x24498c0 | size 296 | symbol _ZN4Aska33IDESpacePartitionBVH_BoundingAABB3SetEPNS_16CollisionHandlerE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska33IDESpacePartitionBVH_BoundingAABB3SetEPNS_16CollisionHandlerE
               (float *param_1,long param_2)

{
  float fVar1;
  long lVar2;
  float *pfVar3;
  float fVar4;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  
  Aska::CollisionHandler::MakeMatrix()(param_2);
  if ((*(char *)(param_2 + 0x55) == '\0') ||
     (((*(short *)(*(long *)(param_2 + 0x10) + 2) == 0 ||
       (pfVar3 = *(float **)(param_2 + 0x18), pfVar3 == (float *)0x0)) &&
      ((*(short *)(*(long *)(param_2 + 0x10) + 4) == 0 ||
       (pfVar3 = *(float **)(param_2 + 0x20), pfVar3 == (float *)0x0)))))) {
    param_1[0] = 0.0;
    param_1[1] = 0.0;
    param_1[2] = 0.0;
    param_1[4] = 0.0;
    param_1[5] = 0.0;
    param_1[6] = 0.0;
    param_1[8] = -1.0;
  }
  else {
    if (*(char *)(pfVar3 + 0xc) == '\0') {
      lVar2 = Aska::CollisionHandler::GetObjectLinkedWithBranch(Aska::AcfSphereTreeBranch*) const(param_2,pfVar3);
    }
    else {
      lVar2 = Aska::CollisionHandler::GetObjectLinkedWithLeaf(Aska::AcfSphereTreeLeaf*) const(param_2,pfVar3);
    }
    fStack_30 = *pfVar3;
    fStack_2c = pfVar3[1];
    fStack_28 = pfVar3[2];
    fVar1 = pfVar3[3];
    uStack_24 = 0x3f800000;
    Aska::Vector::ApplyMatrix(Aska::Matrix const*)(&fStack_30,lVar2 + 0x10);
    fVar4 = fVar1 * _UNK_029e3674;
    param_1[4] = fVar4 + fStack_30;
    param_1[5] = fVar4 + fStack_2c;
    param_1[6] = fVar4 + fStack_28;
    param_1[3] = fVar1;
    param_1[7] = fVar1;
    *param_1 = fStack_30 - fVar4;
    param_1[1] = fStack_2c - fVar4;
    param_1[2] = fStack_28 - fVar4;
    param_1[8] = ((fVar4 + fStack_30) - (fStack_30 - fVar4)) *
                 ((fVar4 + fStack_2c) - (fStack_2c - fVar4)) *
                 ((fVar4 + fStack_28) - (fStack_28 - fVar4));
  }
  return;
}

// ==== Aska::IDESpacePartitionBVH_BoundingAABB::Resize(Aska::IDESpacePartitionBVH_BoundingAABB*)
// vaddr 0x23499e8 | ghidra 0x24499e8 | size 248 | symbol _ZN4Aska33IDESpacePartitionBVH_BoundingAABB6ResizeEPS0_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska33IDESpacePartitionBVH_BoundingAABB6ResizeEPS0_(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  if (param_1[8] < 0.0) {
    fVar3 = *param_2;
    *param_1 = fVar3;
    fVar2 = param_2[1];
    param_1[1] = fVar2;
    fVar5 = param_2[2];
    param_1[2] = fVar5;
    param_1[3] = param_2[3];
    fVar4 = param_2[4];
    param_1[4] = fVar4;
    fVar6 = param_2[5];
    param_1[5] = fVar6;
    fVar1 = param_2[6];
    fVar3 = (fVar4 - fVar3) * (fVar6 - fVar2);
    param_1[6] = fVar1;
    fVar1 = fVar1 - fVar5;
    param_1[7] = param_2[7];
  }
  else {
    fVar3 = *param_1;
    if (*param_2 <= *param_1) {
      fVar3 = *param_2;
    }
    fVar2 = param_1[1];
    if (param_2[1] <= param_1[1]) {
      fVar2 = param_2[1];
    }
    fVar5 = param_1[2];
    if (param_2[2] <= param_1[2]) {
      fVar5 = param_2[2];
    }
    fVar4 = param_1[4];
    if (param_1[4] <= param_2[4]) {
      fVar4 = param_2[4];
    }
    fVar6 = param_1[5];
    if (param_1[5] <= param_2[5]) {
      fVar6 = param_2[5];
    }
    fVar7 = param_2[6];
    *param_1 = fVar3;
    param_1[1] = fVar2;
    fVar1 = param_1[6];
    if (param_1[6] <= fVar7) {
      fVar1 = fVar7;
    }
    param_1[6] = fVar1;
    fVar1 = fVar1 - fVar5;
    fVar3 = (fVar4 - fVar3) * (fVar6 - fVar2);
    param_1[2] = fVar5;
    param_1[4] = fVar4;
    param_1[5] = fVar6;
  }
  param_1[8] = fVar1 * fVar3;
  return;
}

// ==== Aska::IDE_SyncNotifyOfEvent::PostSync(int*, Aska::Event*)
// vaddr 0x25a3130 | ghidra 0x26a3130 | size 132 | symbol _ZN4Aska21IDE_SyncNotifyOfEvent8PostSyncEPiPNS_5EventE | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN4Aska21IDE_SyncNotifyOfEvent8PostSyncEPiPNS_5EventE(int *param_1,undefined8 param_2)

{
  undefined *puVar1;
  ulong uVar2;
  undefined8 uVar3;
  
  puVar1 = PTR__ZN4Aska21IDE_SyncNotifyOfEvent10m_InstanceE_02cc0178;
  uVar3 = *(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
  do {
    uVar2 = Aska::SimpleMessageDispatcher::PostSyncMessageEnd(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar3,0x12,param_1,puVar1,param_2,0,0,1);
    if ((uVar2 & 1) != 0) {
      return 1;
    }
    Aska::Thread::Sleep(unsigned int)(1);
    DataMemoryBarrier(2,3);
  } while (0 < *param_1);
  return 0;
}

// ==== Aska::IDE_SyncNotifyOfEvent::Wait(int*)
// vaddr 0x25a31b4 | ghidra 0x26a31b4 | size 224 | symbol _ZN4Aska21IDE_SyncNotifyOfEvent4WaitEPi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21IDE_SyncNotifyOfEvent4WaitEPi(int *param_1)

{
  int iVar1;
  undefined *puVar2;
  ulong uVar3;
  undefined8 uVar4;
  undefined1 auStack_88 [104];
  
  DataMemoryBarrier(2,3);
  if (0 < *param_1) {
    Aska::Event::Event()(auStack_88);
    uVar3 = Aska::Event::Create(bool, bool)(auStack_88,1,0);
    puVar2 = PTR__ZN4Aska21IDE_SyncNotifyOfEvent10m_InstanceE_02cc0178;
    if ((uVar3 & 1) != 0) {
      uVar4 = *(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
      do {
        uVar3 = Aska::SimpleMessageDispatcher::PostSyncMessageEnd(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(uVar4,0x12,param_1,puVar2,auStack_88,0,0,1);
        if ((uVar3 & 1) != 0) {
          Aska::Event::Wait(unsigned int) const(auStack_88,0);
          goto code_r0x026a327c;
        }
        Aska::Thread::Sleep(unsigned int)(1);
        DataMemoryBarrier(2,3);
      } while (0 < *param_1);
    }
    DataMemoryBarrier(2,3);
    iVar1 = *param_1;
    while (0 < iVar1) {
      Aska::Thread::SleepU(unsigned int)(100);
      DataMemoryBarrier(2,3);
      iVar1 = *param_1;
    }
code_r0x026a327c:
    Aska::Event::Exit()(auStack_88);
  }
  return;
}

// ==== Aska::IDE_SyncNotifyOfEvent::Handler(unsigned long)
// vaddr 0x25a3294 | ghidra 0x26a3294 | size 8 | symbol _ZN4Aska21IDE_SyncNotifyOfEvent7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21IDE_SyncNotifyOfEvent7HandlerEm(undefined8 param_1,long param_2)

{
  (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(*(undefined8 *)(param_2 + 0x30));
  return;
}

// ==== Aska::IDE_SyncNotifyOfEvent::~IDE_SyncNotifyOfEvent()
// vaddr 0x25a329c | ghidra 0x26a329c | size 4 | symbol _ZN4Aska21IDE_SyncNotifyOfEventD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21IDE_SyncNotifyOfEventD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::IDESpacePartition::GetHeight(Aska::IDE_ResultOfHeight*, Aska::Vector*, unsigned int, unsigned short)
// vaddr 0x25a38a0 | ghidra 0x26a38a0 | size 100 | symbol _ZN4Aska17IDESpacePartition9GetHeightEPNS_18IDE_ResultOfHeightEPNS_6VectorEjt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17IDESpacePartition9GetHeightEPNS_18IDE_ResultOfHeightEPNS_6VectorEjt
               (undefined8 param_1,long param_2,undefined8 param_3,uint param_4)

{
  long lVar1;
  long lVar2;
  undefined1 *puVar3;
  
  if (param_4 != 0) {
    if (param_4 == 1) {
      lVar2 = 0;
    }
    else {
      lVar2 = (ulong)param_4 - (ulong)(param_4 & 1);
      if (lVar2 != 0) {
        puVar3 = (undefined1 *)(param_2 + 0xc);
        lVar1 = lVar2;
        do {
          puVar3[-8] = 1;
          *puVar3 = 1;
          lVar1 = lVar1 + -2;
          puVar3 = puVar3 + 0x10;
        } while (lVar1 != 0);
        if ((param_4 & 1) == 0) {
          return;
        }
      }
    }
    lVar1 = (ulong)param_4 - lVar2;
    puVar3 = (undefined1 *)(param_2 + lVar2 * 8 + 4);
    do {
      lVar1 = lVar1 + -1;
      *puVar3 = 1;
      puVar3 = puVar3 + 8;
    } while (lVar1 != 0);
  }
  return;
}

// ==== Aska::IDESpacePartition::FindIntersectNearestObjectArray(Aska::IDE_ResultOfNearestObject*, Aska::Ray*, unsigned int, unsigned short)
// vaddr 0x25a3904 | ghidra 0x26a3904 | size 96 | symbol _ZN4Aska17IDESpacePartition31FindIntersectNearestObjectArrayEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEjt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17IDESpacePartition31FindIntersectNearestObjectArrayEPNS_25IDE_ResultOfNearestObjectEPNS_3RayEjt
               (undefined8 param_1,long param_2,undefined8 param_3,uint param_4)

{
  long lVar1;
  long lVar2;
  undefined8 *puVar3;
  
  if (param_4 != 0) {
    if (param_4 == 1) {
      lVar2 = 0;
    }
    else {
      lVar2 = (ulong)param_4 - (ulong)(param_4 & 1);
      if (lVar2 != 0) {
        puVar3 = (undefined8 *)(param_2 + 0x90);
        lVar1 = lVar2;
        do {
          puVar3[-0x10] = 0;
          *puVar3 = 0;
          lVar1 = lVar1 + -2;
          puVar3 = puVar3 + 0x20;
        } while (lVar1 != 0);
        if ((param_4 & 1) == 0) {
          return;
        }
      }
    }
    lVar1 = (ulong)param_4 - lVar2;
    puVar3 = (undefined8 *)(param_2 + lVar2 * 0x80 + 0x10);
    do {
      lVar1 = lVar1 + -1;
      *puVar3 = 0;
      puVar3 = puVar3 + 0x10;
    } while (lVar1 != 0);
  }
  return;
}

// ==== Aska::IDESpacePartition::FindIntersectNearestObjectArray(Aska::IDE_ResultOfNearestObject*, Aska::Segment*, unsigned int, unsigned short)
// vaddr 0x25a3964 | ghidra 0x26a3964 | size 96 | symbol _ZN4Aska17IDESpacePartition31FindIntersectNearestObjectArrayEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEjt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17IDESpacePartition31FindIntersectNearestObjectArrayEPNS_25IDE_ResultOfNearestObjectEPNS_7SegmentEjt
               (undefined8 param_1,long param_2,undefined8 param_3,uint param_4)

{
  long lVar1;
  long lVar2;
  undefined8 *puVar3;
  
  if (param_4 != 0) {
    if (param_4 == 1) {
      lVar2 = 0;
    }
    else {
      lVar2 = (ulong)param_4 - (ulong)(param_4 & 1);
      if (lVar2 != 0) {
        puVar3 = (undefined8 *)(param_2 + 0x90);
        lVar1 = lVar2;
        do {
          puVar3[-0x10] = 0;
          *puVar3 = 0;
          lVar1 = lVar1 + -2;
          puVar3 = puVar3 + 0x20;
        } while (lVar1 != 0);
        if ((param_4 & 1) == 0) {
          return;
        }
      }
    }
    lVar1 = (ulong)param_4 - lVar2;
    puVar3 = (undefined8 *)(param_2 + lVar2 * 0x80 + 0x10);
    do {
      lVar1 = lVar1 + -1;
      *puVar3 = 0;
      puVar3 = puVar3 + 0x10;
    } while (lVar1 != 0);
  }
  return;
}

// ==== Aska::IDESpacePartition::~IDESpacePartition()
// vaddr 0x25a39c4 | ghidra 0x26a39c4 | size 4 | symbol _ZN4Aska17IDESpacePartitionD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17IDESpacePartitionD2Ev(void)

{
  return;
}

// ==== Aska::IDESpacePartition::~IDESpacePartition()
// vaddr 0x25a39c8 | ghidra 0x26a39c8 | size 4 | symbol _ZN4Aska17IDESpacePartitionD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17IDESpacePartitionD0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x26a39cc);
  (*pcVar1)();
}

// ==== Aska::IDESpacePartition::IsAvailable()
// vaddr 0x25a39cc | ghidra 0x26a39cc | size 8 | symbol _ZN4Aska17IDESpacePartition11IsAvailableEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska17IDESpacePartition11IsAvailableEv(void)

{
  return 0;
}

// ==== Aska::IDESpacePartition::Delete(Aska::IDEPrimitiveBase*)
// vaddr 0x25a39d4 | ghidra 0x26a39d4 | size 100 | symbol _ZN4Aska17IDESpacePartition6DeleteEPNS_16IDEPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17IDESpacePartition6DeleteEPNS_16IDEPrimitiveBaseE(long param_1,long *param_2)

{
  if ((*(byte *)((long)param_2 + 0x23) & 1) == 0) {
    return;
  }
  if (*(long *)(param_1 + 8) != 0) {
    (**(code **)*param_2)(param_2);
    (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPv_02cb5c60)
              (*(undefined8 *)(param_1 + 8),param_2);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x026a3a34. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)((undefined8 *)*param_2)[1])(param_2);
  return;
}

// ==== Aska::IDESpacePartition::DeleteAll()
// vaddr 0x25a3a38 | ghidra 0x26a3a38 | size 4 | symbol _ZN4Aska17IDESpacePartition9DeleteAllEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17IDESpacePartition9DeleteAllEv(void)

{
  return;
}

// ==== Aska::IDESpacePartition::Intersect(Aska::Ray const*, unsigned short)
// vaddr 0x25a3a3c | ghidra 0x26a3a3c | size 8 | symbol _ZN4Aska17IDESpacePartition9IntersectEPKNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska17IDESpacePartition9IntersectEPKNS_3RayEt(void)

{
  return 0;
}

// ==== Aska::IDESpacePartition::Intersect(Aska::Segment const*, unsigned short)
// vaddr 0x25a3a44 | ghidra 0x26a3a44 | size 8 | symbol _ZN4Aska17IDESpacePartition9IntersectEPKNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska17IDESpacePartition9IntersectEPKNS_7SegmentEt(void)

{
  return 0;
}

// ==== Aska::IDESpacePartition::FindIntersectNearestPoint(Aska::Vector*, Aska::Ray const*, unsigned short)
// vaddr 0x25a3a4c | ghidra 0x26a3a4c | size 8 | symbol _ZN4Aska17IDESpacePartition25FindIntersectNearestPointEPNS_6VectorEPKNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska17IDESpacePartition25FindIntersectNearestPointEPNS_6VectorEPKNS_3RayEt(void)

{
  return 0;
}

// ==== Aska::IDESpacePartition::FindIntersectNearestPoint(Aska::Vector*, Aska::Segment const*, unsigned short)
// vaddr 0x25a3a54 | ghidra 0x26a3a54 | size 8 | symbol _ZN4Aska17IDESpacePartition25FindIntersectNearestPointEPNS_6VectorEPKNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska17IDESpacePartition25FindIntersectNearestPointEPNS_6VectorEPKNS_7SegmentEt(void)

{
  return 0;
}

// ==== Aska::IDESpacePartition::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Ray const*, unsigned short)
// vaddr 0x25a3a5c | ghidra 0x26a3a5c | size 8 | symbol _ZN4Aska17IDESpacePartition26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPKNS_3RayEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska17IDESpacePartition26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPKNS_3RayEt
          (void)

{
  return 0;
}

// ==== Aska::IDESpacePartition::FindIntersectNearestObject(Aska::IDE_ResultOfNearestObject*, Aska::Segment const*, unsigned short)
// vaddr 0x25a3a64 | ghidra 0x26a3a64 | size 8 | symbol _ZN4Aska17IDESpacePartition26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPKNS_7SegmentEt | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska17IDESpacePartition26FindIntersectNearestObjectEPNS_25IDE_ResultOfNearestObjectEPKNS_7SegmentEt
          (void)

{
  return 0;
}

// ==== Aska::IDESpacePartition::FindIntersectObjects(Aska::INotify*, Aska::Vector const*, unsigned short)
// vaddr 0x25a3a6c | ghidra 0x26a3a6c | size 4 | symbol _ZN4Aska17IDESpacePartition20FindIntersectObjectsEPNS_7INotifyEPKNS_6VectorEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17IDESpacePartition20FindIntersectObjectsEPNS_7INotifyEPKNS_6VectorEt(void)

{
  return;
}

// ==== Aska::IDESpacePartition::FindIntersectObjects(Aska::INotify*, Aska::Box const*, unsigned short)
// vaddr 0x25a3a70 | ghidra 0x26a3a70 | size 4 | symbol _ZN4Aska17IDESpacePartition20FindIntersectObjectsEPNS_7INotifyEPKNS_3BoxEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17IDESpacePartition20FindIntersectObjectsEPNS_7INotifyEPKNS_3BoxEt(void)

{
  return;
}

// ==== Aska::IDESpacePartition::PostFindIntersectObjects(Aska::IDE_ResultOfFindObjects*, int, unsigned int*, unsigned int*, Aska::INotify*, Aska::Box const*, unsigned int, unsigned short)
// vaddr 0x25a3a74 | ghidra 0x26a3a74 | size 4 | symbol _ZN4Aska17IDESpacePartition24PostFindIntersectObjectsEPNS_23IDE_ResultOfFindObjectsEiPjS3_PNS_7INotifyEPKNS_3BoxEjt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17IDESpacePartition24PostFindIntersectObjectsEPNS_23IDE_ResultOfFindObjectsEiPjS3_PNS_7INotifyEPKNS_3BoxEjt
               (void)

{
  return;
}

// ==== Aska::IDESpacePartition::PostFindIntersectObjects_Wait()
// vaddr 0x25a3a78 | ghidra 0x26a3a78 | size 4 | symbol _ZN4Aska17IDESpacePartition29PostFindIntersectObjects_WaitEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17IDESpacePartition29PostFindIntersectObjects_WaitEv(void)

{
  return;
}

// ==== Aska::IDESpacePartition::FindIntersectPrimitives(Aska::IDEIntersectNotify*)
// vaddr 0x25a3a7c | ghidra 0x26a3a7c | size 4 | symbol _ZN4Aska17IDESpacePartition23FindIntersectPrimitivesEPNS_18IDEIntersectNotifyE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17IDESpacePartition23FindIntersectPrimitivesEPNS_18IDEIntersectNotifyE(void)

{
  return;
}

// ==== Aska::IDESpacePartition::IsClean() const
// vaddr 0x25a3a80 | ghidra 0x26a3a80 | size 8 | symbol _ZNK4Aska17IDESpacePartition7IsCleanEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska17IDESpacePartition7IsCleanEv(void)

{
  return 0;
}

// ==== Aska::IDESpacePartition::SetClean(bool)
// vaddr 0x25a3a88 | ghidra 0x26a3a88 | size 4 | symbol _ZN4Aska17IDESpacePartition8SetCleanEb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17IDESpacePartition8SetCleanEb(void)

{
  return;
}
