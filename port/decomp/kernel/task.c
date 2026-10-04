// port/decomp/kernel/task.c: Ghidra decompiles for the kernel subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:15 UTC: tools/decomp.sh '--into' 'kernel/task' 'Aska::TaskManager::' 'Aska::Task::' 'Aska::TaskThread' 'Aska::AnimatableLinkElement::'

// ==== Aska::Task::GetClassID(int) const
// vaddr 0x120232c | ghidra 0x130232c | size 44 | symbol _ZNK4Aska4Task10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska4Task10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar2 = 0xf000f001;
  if (param_2 != 1) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf000f001f002;
  if (param_2 != 0) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::AnimatableLinkElement::Get(unsigned long, void*) const
// vaddr 0x1202358 | ghidra 0x1302358 | size 8 | symbol _ZNK4Aska21AnimatableLinkElement3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska21AnimatableLinkElement3GetEmPv(void)

{
  return 0;
}

// ==== Aska::AnimatableLinkElement::Set(unsigned long, void const*)
// vaddr 0x1202360 | ghidra 0x1302360 | size 8 | symbol _ZN4Aska21AnimatableLinkElement3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska21AnimatableLinkElement3SetEmPKv(void)

{
  return 0;
}

// ==== Aska::Task::MessageHandler(unsigned int, int, void*, void*)
// vaddr 0x1202370 | ghidra 0x1302370 | size 8 | symbol _ZN4Aska4Task14MessageHandlerEjiPvS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4Task14MessageHandlerEjiPvS1_(void)

{
  return 0;
}

// ==== Aska::Task::IsMulti() const
// vaddr 0x1202378 | ghidra 0x1302378 | size 8 | symbol _ZNK4Aska4Task7IsMultiEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska4Task7IsMultiEv(void)

{
  return 0;
}

// ==== Aska::Task::OnDeleteFromTaskManager()
// vaddr 0x1202380 | ghidra 0x1302380 | size 4 | symbol _ZN4Aska4Task23OnDeleteFromTaskManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task23OnDeleteFromTaskManagerEv(void)

{
  return;
}

// ==== Aska::Task::OnAddToTaskManager()
// vaddr 0x1202384 | ghidra 0x1302384 | size 4 | symbol _ZN4Aska4Task18OnAddToTaskManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task18OnAddToTaskManagerEv(void)

{
  return;
}

// ==== Aska::Task::OnAddTopToTaskManager()
// vaddr 0x1202388 | ghidra 0x1302388 | size 4 | symbol _ZN4Aska4Task21OnAddTopToTaskManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task21OnAddTopToTaskManagerEv(void)

{
  return;
}

// ==== Aska::Task::OnInsertToTaskManager()
// vaddr 0x120238c | ghidra 0x130238c | size 4 | symbol _ZN4Aska4Task21OnInsertToTaskManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task21OnInsertToTaskManagerEv(void)

{
  return;
}

// ==== Aska::Task::GetDefaultLevel() const
// vaddr 0x134e514 | ghidra 0x144e514 | size 8 | symbol _ZNK4Aska4Task15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska4Task15GetDefaultLevelEv(void)

{
  return 0x40;
}

// ==== Aska::AnimatableLinkElement::~AnimatableLinkElement()
// vaddr 0x1f70430 | ghidra 0x2070430 | size 24 | symbol _ZN4Aska21AnimatableLinkElementD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska21AnimatableLinkElementD0Ev(undefined8 param_1)

{
  Aska::IAnimatable::~IAnimatable()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::AnimatableLinkElement::GetClassID(int) const
// vaddr 0x1f70448 | ghidra 0x2070448 | size 24 | symbol _ZNK4Aska21AnimatableLinkElement10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska21AnimatableLinkElement10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0xf000f001;
  if (param_2 != 0) {
    uVar1 = 0xf000;
  }
  return uVar1;
}

// ==== Aska::AnimatableLinkElement::CreateClone(Aska::IAnimatable const*)
// vaddr 0x1f70460 | ghidra 0x2070460 | size 8 | symbol _ZN4Aska21AnimatableLinkElement11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska21AnimatableLinkElement11CreateCloneEPKNS_11IAnimatableE(void)

{
  return 0;
}

// ==== Aska::Task::~Task()
// vaddr 0x1f7f564 | ghidra 0x207f564 | size 60 | symbol _ZN4Aska4TaskD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4TaskD1Ev(long *param_1)

{
  long *plVar1;
  
  plVar1 = (long *)param_1[3];
  *param_1 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0x40))(plVar1,param_1);
  }
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1);
  return;
}

// ==== Aska::Task::~Task()
// vaddr 0x1f7f5a0 | ghidra 0x207f5a0 | size 68 | symbol _ZN4Aska4TaskD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4TaskD0Ev(long *param_1)

{
  long *plVar1;
  
  plVar1 = (long *)param_1[3];
  *param_1 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
  if (plVar1 != (long *)0x0) {
    (**(code **)(*plVar1 + 0x40))(plVar1,param_1);
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::Task::Remove()
// vaddr 0x1f7f5e4 | ghidra 0x207f5e4 | size 32 | symbol _ZN4Aska4Task6RemoveEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task6RemoveEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x18);
  if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0207f5fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x40))(plVar1,param_1);
    return;
  }
  return;
}

// ==== Aska::Task::DeleteThis(Aska::DeleteManager*)
// vaddr 0x1f7f604 | ghidra 0x207f604 | size 48 | symbol _ZN4Aska4Task10DeleteThisEPNS_13DeleteManagerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task10DeleteThisEPNS_13DeleteManagerE(undefined8 param_1,undefined *param_2)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0;
  if (param_2 != (undefined *)0x0) {
    puVar1 = param_2;
  }
  (*(code *)PTR__ZN4Aska13DeleteManager7AddMainEPvhhPNS_14IDeleteHandlerE_02c9d0d8)
            (puVar1,param_1,3,0,0);
  return;
}

// ==== Aska::Task::DeleteThisNextFrame(Aska::DeleteManager*)
// vaddr 0x1f7f634 | ghidra 0x207f634 | size 52 | symbol _ZN4Aska4Task19DeleteThisNextFrameEPNS_13DeleteManagerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task19DeleteThisNextFrameEPNS_13DeleteManagerE(undefined8 param_1,undefined *param_2)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0;
  if (param_2 != (undefined *)0x0) {
    puVar1 = param_2;
  }
  (*(code *)PTR__ZN4Aska13DeleteManager7AddMainEPvhhPNS_14IDeleteHandlerE_02c9d0d8)
            (puVar1,param_1,3,1,0);
  return;
}

// ==== Aska::Task::DeleteThisAfterTwoFrames(Aska::DeleteManager*)
// vaddr 0x1f7f668 | ghidra 0x207f668 | size 52 | symbol _ZN4Aska4Task24DeleteThisAfterTwoFramesEPNS_13DeleteManagerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task24DeleteThisAfterTwoFramesEPNS_13DeleteManagerE
               (undefined8 param_1,undefined *param_2)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0;
  if (param_2 != (undefined *)0x0) {
    puVar1 = param_2;
  }
  (*(code *)PTR__ZN4Aska13DeleteManager7AddMainEPvhhPNS_14IDeleteHandlerE_02c9d0d8)
            (puVar1,param_1,3,2,0);
  return;
}

// ==== Aska::Task::DeleteThisImmediately()
// vaddr 0x1f7f69c | ghidra 0x207f69c | size 20 | symbol _ZN4Aska4Task21DeleteThisImmediatelyEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task21DeleteThisImmediatelyEv(long *param_1)

{
  if (param_1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0207f6a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 8))();
    return;
  }
  return;
}

// ==== Aska::Task::Clone(Aska::IAnimatable const*)
// vaddr 0x1f7f6b0 | ghidra 0x207f6b0 | size 76 | symbol _ZN4Aska4Task5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4Task5CloneEPKNS_11IAnimatableE(long param_1,long param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  
  uVar1 = Aska::IAnimatable::Clone(Aska::IAnimatable const*)();
  if (((uVar1 & 1) == 0) || (param_2 == 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_2 + 0x20);
    *(undefined1 *)(param_1 + 0x26) = *(undefined1 *)(param_2 + 0x26);
    *(undefined2 *)(param_1 + 0x24) = *(undefined2 *)(param_2 + 0x24);
  }
  return uVar2;
}

// ==== Aska::Task::CreateClone(Aska::IAnimatable const*)
// vaddr 0x1f7f6fc | ghidra 0x207f6fc | size 156 | symbol _ZN4Aska4Task11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska4Task11CreateCloneEPKNS_11IAnimatableE(undefined8 param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  ulong uVar3;
  
  plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
  if (plVar2 != (long *)0x0) {
    puVar1 = PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10;
    plVar2[2] = 0;
    plVar2[3] = 0;
    *(undefined2 *)((long)plVar2 + 0x24) = 0;
    *(undefined1 *)((long)plVar2 + 0x26) = 0;
    *plVar2 = (long)puVar1;
    plVar2[1] = 0;
    *(undefined4 *)(plVar2 + 4) = 0x40;
    uVar3 = Aska::IAnimatable::Clone(Aska::IAnimatable const*)(plVar2,param_2);
    if (((uVar3 & 1) == 0) || (param_2 == 0)) {
      (**(code **)(*plVar2 + 8))(plVar2);
      plVar2 = (long *)0x0;
    }
    else {
      *(undefined4 *)(plVar2 + 4) = *(undefined4 *)(param_2 + 0x20);
      *(undefined1 *)((long)plVar2 + 0x26) = *(undefined1 *)(param_2 + 0x26);
      *(undefined2 *)((long)plVar2 + 0x24) = *(undefined2 *)(param_2 + 0x24);
    }
  }
  return plVar2;
}

// ==== Aska::Task::ChangeLevel(unsigned int)
// vaddr 0x1f7f798 | ghidra 0x207f798 | size 56 | symbol _ZN4Aska4Task11ChangeLevelEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task11ChangeLevelEj(long param_1,int param_2)

{
  if (param_2 != 0) {
    if (*(long *)(param_1 + 0x18) != 0) {
      Aska::TaskManager::ChangeLevel(Aska::Task*, unsigned int)(*(long *)(param_1 + 0x18),param_1,param_2);
    }
    *(int *)(param_1 + 0x20) = param_2;
  }
  return;
}

// ==== Aska::Task::ForceDelete()
// vaddr 0x1f7f7d0 | ghidra 0x207f7d0 | size 16 | symbol _ZN4Aska4Task11ForceDeleteEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task11ForceDeleteEv(long *param_1)

{
  param_1[3] = 0;
                    /* WARNING: Could not recover jumptable at 0x0207f7dc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x50))();
  return;
}

// ==== Aska::Task::Run(int)
// vaddr 0x1f7f7e0 | ghidra 0x207f7e0 | size 4 | symbol _ZN4Aska4Task3RunEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Task3RunEi(void)

{
  return;
}

// ==== Aska::TaskManager::TaskManager()
// vaddr 0x1f7f7e4 | ghidra 0x207f7e4 | size 496 | symbol _ZN4Aska11TaskManagerC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManagerC2Ev(long *param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  code *pcVar3;
  long *plVar4;
  
  *(undefined4 *)(param_1 + 4) = 0;
  puVar1 = PTR__ZTVN4Aska14AnimatableListE_02cb9290 + 0x10;
  param_1[1] = (long)(PTR__ZTVN4Aska21AnimatableLinkElementE_02cc02b8 + 0x10);
  *param_1 = (long)puVar1;
  puVar1 = PTR__ZTVN4Aska4TaskE_02cbe020;
  param_1[2] = (long)(param_1 + 1);
  param_1[3] = (long)(param_1 + 1);
  param_1[7] = 0;
  param_1[6] = 0;
  pcVar3 = *(code **)(puVar1 + 0x68);
  plVar4 = param_1 + 5;
  *plVar4 = (long)(puVar1 + 0x10);
  param_1[8] = 0;
  *(undefined2 *)((long)param_1 + 0x4c) = 0;
  *(undefined1 *)((long)param_1 + 0x4e) = 0;
  uVar2 = (*pcVar3)(plVar4);
  *(undefined4 *)(param_1 + 9) = uVar2;
  puVar1 = PTR__ZTVN4Aska11TaskManagerE_02cb7910;
  *param_1 = (long)(PTR__ZTVN4Aska11TaskManagerE_02cb7910 + 0x10);
  *plVar4 = (long)(puVar1 + 0xa0);
  param_1[0x1f] = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  param_1[0x1b] = 0;
  param_1[0x1a] = 0;
  param_1[0x1d] = 0;
  param_1[0x1c] = 0;
  *(undefined1 *)(param_1 + 0x24) = 0xf;
  *(undefined2 *)((long)param_1 + 0x122) = 0;
  param_1[0x25] = 0;
  Aska::Event::Event()(param_1 + 0x26);
  Aska::Event::Event()(param_1 + 0x33);
  Aska::Event::Event()(param_1 + 0x40);
  Aska::Event::Event()(param_1 + 0x4d);
  Aska::Event::Event()(param_1 + 0x5a);
  Aska::Event::Event()(param_1 + 0x67);
  Aska::Event::Event()(param_1 + 0x74);
  Aska::Event::Event()(param_1 + 0x81);
  Aska::Event::Event()(param_1 + 0x8e);
  Aska::Event::Event()(param_1 + 0x9b);
  Aska::Event::Event()(param_1 + 0xa8);
  Aska::Event::Event()(param_1 + 0xb5);
  Aska::Event::Event()(param_1 + 0xc2);
  Aska::Event::Event()(param_1 + 0xcf);
  Aska::Event::Event()(param_1 + 0xdc);
  Aska::Event::Event()(param_1 + 0xe9);
  Aska::Event::Event()(param_1 + 0xf6);
  Aska::Event::Event()(param_1 + 0x103);
  Aska::Event::Event()(param_1 + 0x110);
  Aska::Event::Event()(param_1 + 0x11d);
  Aska::Event::Event()(param_1 + 0x12a);
  Aska::Event::Event()(param_1 + 0x137);
  Aska::Event::Event()(param_1 + 0x144);
  Aska::Event::Event()(param_1 + 0x151);
  Aska::Event::Event()(param_1 + 0x15e);
  Aska::Event::Event()(param_1 + 0x16b);
  Aska::Event::Event()(param_1 + 0x178);
  Aska::Event::Event()(param_1 + 0x185);
  Aska::Event::Event()(param_1 + 0x192);
  Aska::Event::Event()(param_1 + 0x19f);
  Aska::Event::Event()(param_1 + 0x1ac);
  Aska::Event::Event()(param_1 + 0x1b9);
  Aska::CriticalSection::CriticalSection()(param_1 + 0x1e7);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x1ec);
  memset(param_1 + 10,0,0x80);
  memset(param_1 + 0x1c6,0,0x108);
  param_1[0x22] = (long)param_1;
  param_1[0x23] = (long)param_1;
  param_1[0x21] = (long)param_1;
  return;
}

// ==== Aska::TaskManager::~TaskManager()
// vaddr 0x1f7f9d4 | ghidra 0x207f9d4 | size 540 | symbol _ZN4Aska11TaskManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManagerD2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  long lVar3;
  
  lVar3 = 0;
  puVar1 = PTR__ZTVN4Aska11TaskManagerE_02cb7910 + 0xa0;
  plVar2 = param_1 + 0x26;
  *param_1 = (long)(PTR__ZTVN4Aska11TaskManagerE_02cb7910 + 0x10);
  param_1[5] = (long)puVar1;
  do {
    if ((*(uint *)(param_1 + 0x1c6) & 1 << (ulong)((uint)lVar3 & 0x1f)) != 0) {
      Aska::Event::Exit()(plVar2);
    }
    lVar3 = lVar3 + 1;
    plVar2 = plVar2 + 0xd;
  } while (lVar3 != 0x20);
  *(undefined4 *)(param_1 + 0x1c6) = 0;
  if (((long *)param_1[0x21] == param_1) && ((long *)param_1[0x1c] != (long *)0x0)) {
    (**(code **)(*(long *)param_1[0x1c] + 8))();
    lVar3 = param_1[0x21];
    param_1[0x1c] = 0;
    do {
      *(undefined8 *)(lVar3 + 0xe0) = 0;
      lVar3 = *(long *)(lVar3 + 0x118);
    } while (param_1[0x21] != lVar3);
  }
  Aska::TaskManager::ForceDelete()(param_1);
  (**(code **)(*param_1 + 0x50))(param_1);
  (**(code **)(*param_1 + 0x60))(param_1);
  if (param_1[0x25] != 0) {
    operator delete[](void*)();
    param_1[0x25] = 0;
  }
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 0x1ec);
  Aska::CriticalSection::~CriticalSection()(param_1 + 0x1e7);
  Aska::Event::Exit()(param_1 + 0x1b9);
  Aska::Event::Exit()(param_1 + 0x1ac);
  Aska::Event::Exit()(param_1 + 0x19f);
  Aska::Event::Exit()(param_1 + 0x192);
  Aska::Event::Exit()(param_1 + 0x185);
  Aska::Event::Exit()(param_1 + 0x178);
  Aska::Event::Exit()(param_1 + 0x16b);
  Aska::Event::Exit()(param_1 + 0x15e);
  Aska::Event::Exit()(param_1 + 0x151);
  Aska::Event::Exit()(param_1 + 0x144);
  Aska::Event::Exit()(param_1 + 0x137);
  Aska::Event::Exit()(param_1 + 0x12a);
  Aska::Event::Exit()(param_1 + 0x11d);
  Aska::Event::Exit()(param_1 + 0x110);
  Aska::Event::Exit()(param_1 + 0x103);
  Aska::Event::Exit()(param_1 + 0xf6);
  Aska::Event::Exit()(param_1 + 0xe9);
  Aska::Event::Exit()(param_1 + 0xdc);
  Aska::Event::Exit()(param_1 + 0xcf);
  Aska::Event::Exit()(param_1 + 0xc2);
  Aska::Event::Exit()(param_1 + 0xb5);
  Aska::Event::Exit()(param_1 + 0xa8);
  Aska::Event::Exit()(param_1 + 0x9b);
  Aska::Event::Exit()(param_1 + 0x8e);
  Aska::Event::Exit()(param_1 + 0x81);
  Aska::Event::Exit()(param_1 + 0x74);
  Aska::Event::Exit()(param_1 + 0x67);
  Aska::Event::Exit()(param_1 + 0x5a);
  Aska::Event::Exit()(param_1 + 0x4d);
  Aska::Event::Exit()(param_1 + 0x40);
  Aska::Event::Exit()(param_1 + 0x33);
  Aska::Event::Exit()(param_1 + 0x26);
  Aska::Task::~Task()(param_1 + 5);
  *param_1 = (long)(PTR__ZTVN4Aska5TListINS_21AnimatableLinkElementEEE_02cc13d8 + 0x10);
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1 + 1);
  return;
}

// ==== Aska::TaskManager::DeleteMessageQueue()
// vaddr 0x1f7fbf0 | ghidra 0x207fbf0 | size 76 | symbol _ZN4Aska11TaskManager18DeleteMessageQueueEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager18DeleteMessageQueueEv(long param_1)

{
  long lVar1;
  
  if ((*(long *)(param_1 + 0x108) == param_1) && (*(long **)(param_1 + 0xe0) != (long *)0x0)) {
    (**(code **)(**(long **)(param_1 + 0xe0) + 8))();
    lVar1 = *(long *)(param_1 + 0x108);
    *(undefined8 *)(param_1 + 0xe0) = 0;
    do {
      *(undefined8 *)(lVar1 + 0xe0) = 0;
      lVar1 = *(long *)(lVar1 + 0x118);
    } while (*(long *)(param_1 + 0x108) != lVar1);
  }
  return;
}

// ==== Aska::TaskManager::ForceDelete()
// vaddr 0x1f7fc3c | ghidra 0x207fc3c | size 680 | symbol _ZN4Aska11TaskManager11ForceDeleteEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager11ForceDeleteEv(long param_1)

{
  int *piVar1;
  long lVar2;
  int *piVar3;
  long lVar4;
  char cVar5;
  bool bVar6;
  ulong uVar7;
  int iVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  
  lVar10 = *(long *)(param_1 + 0x108);
code_r0x0207fc5c:
  lVar10 = *(long *)(lVar10 + 0x110);
  if (0 < *(int *)(lVar10 + 0x20)) {
    piVar1 = (int *)(lVar10 + 0xf98);
    iVar8 = 0;
code_r0x0207fc74:
    do {
      if (*piVar1 == -1) goto code_r0x0207fc80;
      ClearExclusiveLocal();
      bVar6 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
    } while (bVar6);
    piVar3 = (int *)(lVar10 + 0xf9c);
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
      if (bVar6) {
        *piVar3 = *piVar3 + 1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    do {
      if (*piVar1 != -1) {
        ClearExclusiveLocal();
        do {
          uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0xfd8);
          if ((uVar7 & 1) == 0) {
            do {
              cVar5 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
              if (bVar6) {
                *piVar3 = *piVar3 + -1;
                cVar5 = ExclusiveMonitorsStatus();
              }
            } while (cVar5 != '\0');
            Aska::Thread::Sleep(unsigned int)(1);
          }
          else {
            Aska::Semaphore::Wait() const(lVar10 + 0xfd8);
          }
          do {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
            if (bVar6) {
              *piVar3 = *piVar3 + 1;
              cVar5 = ExclusiveMonitorsStatus();
            }
          } while (cVar5 != '\0');
          while (*piVar1 == -1) {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar6) {
              *piVar1 = 0;
              cVar5 = ExclusiveMonitorsStatus();
            }
            if (cVar5 == '\0') goto code_r0x0207fd2c;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar6) {
        *piVar1 = 0;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
code_r0x0207fd2c:
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
      if (bVar6) {
        *piVar3 = *piVar3 + -1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
code_r0x0207fd3c:
    DataMemoryBarrier(2,3);
    lVar2 = lVar10 + 8;
    piVar3 = (int *)(lVar10 + 0xf9c);
    if (lVar2 == *(long *)(lVar10 + 0x10)) goto code_r0x0207fe6c;
    lVar4 = lVar10 + 0xfd8;
    lVar9 = *(long *)(lVar10 + 0x10);
code_r0x0207fd58:
    lVar11 = *(long *)(lVar9 + 8);
    DataMemoryBarrier(2,3);
    *piVar1 = -1;
    DataMemoryBarrier(2,3);
    if (0x14 < *piVar3) {
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
        if (bVar6) {
          *piVar3 = *piVar3 + -1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
      uVar7 = Aska::Semaphore::IsReady() const(lVar4);
      if ((uVar7 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar4);
      }
    }
    Aska::Task::Remove()(lVar9);
    iVar8 = 0;
    do {
      while (*piVar1 != -1) {
        ClearExclusiveLocal();
        bVar6 = 0x1fe < iVar8;
        iVar8 = iVar8 + 1;
        if (bVar6) goto code_r0x0207fdcc;
      }
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar6) {
        *piVar1 = 0;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    goto code_r0x0207fe5c;
  }
  goto code_r0x0207feb0;
code_r0x0207fc80:
  cVar5 = '\x01';
  bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
  if (bVar6) {
    *piVar1 = 0;
    cVar5 = ExclusiveMonitorsStatus();
  }
  if (cVar5 == '\0') goto code_r0x0207fd3c;
  goto code_r0x0207fc74;
code_r0x0207fdcc:
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
    if (bVar6) {
      *piVar3 = *piVar3 + 1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  do {
    if (*piVar1 != -1) {
      do {
        ClearExclusiveLocal();
        uVar7 = Aska::Semaphore::IsReady() const(lVar4);
        if ((uVar7 & 1) == 0) {
          do {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
            if (bVar6) {
              *piVar3 = *piVar3 + -1;
              cVar5 = ExclusiveMonitorsStatus();
            }
          } while (cVar5 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(lVar4);
        }
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
          if (bVar6) {
            *piVar3 = *piVar3 + 1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        while (*piVar1 == -1) {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar6) {
            *piVar1 = 0;
            cVar5 = ExclusiveMonitorsStatus();
          }
          if (cVar5 == '\0') goto code_r0x0207fe4c;
        }
      } while( true );
    }
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar6) {
      *piVar1 = 0;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
code_r0x0207fe4c:
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
    if (bVar6) {
      *piVar3 = *piVar3 + -1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
code_r0x0207fe5c:
  DataMemoryBarrier(2,3);
  lVar9 = lVar11;
  if (lVar2 == lVar11) goto code_r0x0207fe6c;
  goto code_r0x0207fd58;
code_r0x0207fe6c:
  *(long *)(lVar10 + 0x10) = lVar2;
  *(long *)(lVar10 + 0x18) = lVar2;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar10 + 0xf98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(lVar10 + 0xf9c)) {
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
      if (bVar6) {
        *piVar3 = *piVar3 + -1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    uVar7 = Aska::Semaphore::IsReady() const(lVar10 + 0xfd8);
    if ((uVar7 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar10 + 0xfd8);
    }
  }
code_r0x0207feb0:
  if (lVar10 == *(long *)(param_1 + 0x108)) {
    memset(param_1 + 0x50,0,0x84);
    return;
  }
  goto code_r0x0207fc5c;
}

// ==== non-virtual thunk to Aska::TaskManager::~TaskManager()
// vaddr 0x1f7fee4 | ghidra 0x207fee4 | size 8 | symbol _ZThn40_N4Aska11TaskManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn40_N4Aska11TaskManagerD1Ev(long param_1)

{
  (*(code *)PTR__ZN4Aska11TaskManagerD2Ev_02ca45c0)(param_1 + -0x28);
  return;
}

// ==== Aska::TaskManager::~TaskManager()
// vaddr 0x1f7feec | ghidra 0x207feec | size 24 | symbol _ZN4Aska11TaskManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManagerD0Ev(undefined8 param_1)

{
  Aska::TaskManager::~TaskManager()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::TaskManager::~TaskManager()
// vaddr 0x1f7ff04 | ghidra 0x207ff04 | size 28 | symbol _ZThn40_N4Aska11TaskManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn40_N4Aska11TaskManagerD0Ev(long param_1)

{
  Aska::TaskManager::~TaskManager()(param_1 + -0x28);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1 + -0x28);
  return;
}

// ==== Aska::TaskManager::Add(Aska::Task*)
// vaddr 0x1f7ff20 | ghidra 0x207ff20 | size 8 | symbol _ZN4Aska11TaskManager3AddEPNS_4TaskE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager3AddEPNS_4TaskE(undefined8 param_1,undefined8 param_2)

{
  (*(code *)PTR__ZN4Aska11TaskManager3AddEPNS_4TaskEj_02cb0488)(param_1,param_2,0);
  return;
}

// ==== Aska::TaskManager::Add(Aska::Task*, unsigned int)
// vaddr 0x1f7ff28 | ghidra 0x207ff28 | size 476 | symbol _ZN4Aska11TaskManager3AddEPNS_4TaskEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager3AddEPNS_4TaskEj(long param_1,long *param_2,uint param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  int *piVar6;
  long lVar7;
  
  if (param_2 == (long *)0x0) {
    return;
  }
  piVar6 = (int *)(param_1 + 0xf98);
  iVar5 = 0;
  do {
    while (*piVar6 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x0208002c;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0xf9c);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if (*piVar6 != -1) {
      ClearExclusiveLocal();
      do {
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xfd8);
        if ((uVar4 & 1) == 0) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar3) {
              *piVar1 = *piVar1 + -1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0xfd8);
        }
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while (*piVar6 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x0208001c;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
    if (bVar3) {
      *piVar6 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0208001c:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x0208002c:
  DataMemoryBarrier(2,3);
  param_2[3] = param_1;
  if (param_3 == 0) {
    param_3 = (**(code **)(*param_2 + 0x58))(param_2);
  }
  piVar6 = (int *)(param_1 + 0x50);
  *(uint *)(param_2 + 4) = param_3;
  do {
    if ((param_3 & 1) != 0) {
      *piVar6 = *piVar6 + 1;
      *(int *)(param_1 + 0xd0) = *(int *)(param_1 + 0xd0) + 1;
    }
    param_3 = param_3 >> 1;
    piVar6 = piVar6 + 1;
  } while (param_3 != 0);
  lVar7 = *(long *)(param_1 + 0x10);
  param_2[1] = lVar7;
  param_2[2] = param_1 + 8;
  *(long **)(param_1 + 0x10) = param_2;
  *(long **)(lVar7 + 0x10) = param_2;
  *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xf98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0xf9c)) {
    piVar6 = (int *)(param_1 + 0xf9c);
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = *piVar6 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xfd8);
    if ((uVar4 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xfd8);
    }
  }
                    /* WARNING: Could not recover jumptable at 0x02080100. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_2 + 0x80))(param_2);
  return;
}

// ==== Aska::TaskManager::IncrementTaskLevelCount(unsigned int)
// vaddr 0x1f80104 | ghidra 0x2080104 | size 48 | symbol _ZN4Aska11TaskManager23IncrementTaskLevelCountEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager23IncrementTaskLevelCountEj(long param_1,uint param_2)

{
  int *piVar1;
  
  piVar1 = (int *)(param_1 + 0x50);
  do {
    if ((param_2 & 1) != 0) {
      *piVar1 = *piVar1 + 1;
      *(int *)(param_1 + 0xd0) = *(int *)(param_1 + 0xd0) + 1;
    }
    param_2 = param_2 >> 1;
    piVar1 = piVar1 + 1;
  } while (param_2 != 0);
  return;
}

// ==== Aska::TaskManager::AddTop(Aska::Task*)
// vaddr 0x1f80134 | ghidra 0x2080134 | size 8 | symbol _ZN4Aska11TaskManager6AddTopEPNS_4TaskE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager6AddTopEPNS_4TaskE(undefined8 param_1,undefined8 param_2)

{
  (*(code *)PTR__ZN4Aska11TaskManager6AddTopEPNS_4TaskEj_02ca9500)(param_1,param_2,0);
  return;
}

// ==== Aska::TaskManager::AddTop(Aska::Task*, unsigned int)
// vaddr 0x1f8013c | ghidra 0x208013c | size 476 | symbol _ZN4Aska11TaskManager6AddTopEPNS_4TaskEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager6AddTopEPNS_4TaskEj(long param_1,long *param_2,uint param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  int *piVar6;
  long lVar7;
  
  if (param_2 == (long *)0x0) {
    return;
  }
  piVar6 = (int *)(param_1 + 0xf98);
  iVar5 = 0;
  do {
    while (*piVar6 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x02080240;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0xf9c);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if (*piVar6 != -1) {
      ClearExclusiveLocal();
      do {
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xfd8);
        if ((uVar4 & 1) == 0) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar3) {
              *piVar1 = *piVar1 + -1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0xfd8);
        }
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while (*piVar6 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x02080230;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
    if (bVar3) {
      *piVar6 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02080230:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02080240:
  DataMemoryBarrier(2,3);
  param_2[3] = param_1;
  if (param_3 == 0) {
    param_3 = (**(code **)(*param_2 + 0x58))(param_2);
  }
  piVar6 = (int *)(param_1 + 0x50);
  *(uint *)(param_2 + 4) = param_3;
  do {
    if ((param_3 & 1) != 0) {
      *piVar6 = *piVar6 + 1;
      *(int *)(param_1 + 0xd0) = *(int *)(param_1 + 0xd0) + 1;
    }
    param_3 = param_3 >> 1;
    piVar6 = piVar6 + 1;
  } while (param_3 != 0);
  lVar7 = *(long *)(param_1 + 0x18);
  param_2[1] = param_1 + 8;
  param_2[2] = lVar7;
  *(long **)(lVar7 + 8) = param_2;
  *(long **)(param_1 + 0x18) = param_2;
  *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xf98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0xf9c)) {
    piVar6 = (int *)(param_1 + 0xf9c);
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = *piVar6 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xfd8);
    if ((uVar4 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xfd8);
    }
  }
                    /* WARNING: Could not recover jumptable at 0x02080314. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_2 + 0x88))(param_2);
  return;
}

// ==== Aska::TaskManager::Insert(Aska::Task*, Aska::Task*)
// vaddr 0x1f80318 | ghidra 0x2080318 | size 8 | symbol _ZN4Aska11TaskManager6InsertEPNS_4TaskES2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager6InsertEPNS_4TaskES2_(void)

{
  (*(code *)PTR__ZN4Aska11TaskManager6InsertEPNS_4TaskES2_j_02ca28b8)();
  return;
}

// ==== Aska::TaskManager::Insert(Aska::Task*, Aska::Task*, unsigned int)
// vaddr 0x1f80320 | ghidra 0x2080320 | size 580 | symbol _ZN4Aska11TaskManager6InsertEPNS_4TaskES2_j | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x02080540: Changing call to branch */

void _ZN4Aska11TaskManager6InsertEPNS_4TaskES2_j
               (long param_1,long param_2,long *param_3,uint param_4)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  int *piVar6;
  long lVar7;
  
  if ((param_2 == 0) || (param_3 == (long *)0x0)) {
    return;
  }
  piVar6 = (int *)(param_1 + 0xf98);
  iVar5 = 0;
  do {
    while (*piVar6 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x02080418;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0xf9c);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if (*piVar6 != -1) {
      ClearExclusiveLocal();
      do {
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xfd8);
        if ((uVar4 & 1) == 0) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar3) {
              *piVar1 = *piVar1 + -1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0xfd8);
        }
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while (*piVar6 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar3) {
            *piVar6 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x02080408;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
    if (bVar3) {
      *piVar6 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02080408:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02080418:
  DataMemoryBarrier(2,3);
  if (*(long *)(param_2 + 0x18) != param_1) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0xf98) = 0xffffffff;
    DataMemoryBarrier(2,3);
    if (*(int *)(param_1 + 0xf9c) < 0x15) {
      return;
    }
    piVar6 = (int *)(param_1 + 0xf9c);
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = *piVar6 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xfd8);
    if ((uVar4 & 1) == 0) {
      return;
    }
code_r0x011bd9c0:
    (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xfd8);
    return;
  }
  param_3[3] = param_1;
  if (param_4 == 0) {
    param_4 = (**(code **)(*param_3 + 0x58))(param_3);
  }
  piVar6 = (int *)(param_1 + 0x50);
  *(uint *)(param_3 + 4) = param_4;
  do {
    if ((param_4 & 1) != 0) {
      *piVar6 = *piVar6 + 1;
      *(int *)(param_1 + 0xd0) = *(int *)(param_1 + 0xd0) + 1;
    }
    param_4 = param_4 >> 1;
    piVar6 = piVar6 + 1;
  } while (param_4 != 0);
  lVar7 = *(long *)(param_2 + 0x10);
  param_3[1] = param_2;
  param_3[2] = lVar7;
  *(long **)(lVar7 + 8) = param_3;
  *(long **)(param_2 + 0x10) = param_3;
  *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xf98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0xf9c)) {
    piVar6 = (int *)(param_1 + 0xf9c);
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = *piVar6 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xfd8);
    if ((uVar4 & 1) != 0) goto code_r0x011bd9c0;
  }
                    /* WARNING: Could not recover jumptable at 0x02080560. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_3 + 0x90))(param_3);
  return;
}

// ==== Aska::TaskManager::ChangeLevel(Aska::Task*, unsigned int)
// vaddr 0x1f80564 | ghidra 0x2080564 | size 444 | symbol _ZN4Aska11TaskManager11ChangeLevelEPNS_4TaskEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager11ChangeLevelEPNS_4TaskEj(long param_1,long param_2,uint param_3)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  
  piVar7 = (int *)(param_1 + 0xf98);
  iVar5 = 0;
  do {
    while (*piVar7 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x02080650;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0xf9c);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if (*piVar7 != -1) {
      ClearExclusiveLocal();
      do {
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xfd8);
        if ((uVar4 & 1) == 0) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar3) {
              *piVar1 = *piVar1 + -1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0xfd8);
        }
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while (*piVar7 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
          if (bVar3) {
            *piVar7 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x02080640;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
    if (bVar3) {
      *piVar7 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02080640:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02080650:
  DataMemoryBarrier(2,3);
  uVar6 = *(uint *)(param_2 + 0x20);
  if (uVar6 != 0) {
    piVar7 = (int *)(param_1 + 0x50);
    do {
      if ((uVar6 & 1) != 0) {
        *piVar7 = *piVar7 + -1;
        *(int *)(param_1 + 0xd0) = *(int *)(param_1 + 0xd0) + -1;
      }
      uVar6 = uVar6 >> 1;
      piVar7 = piVar7 + 1;
    } while (uVar6 != 0);
  }
  piVar7 = (int *)(param_1 + 0x50);
  do {
    if ((param_3 & 1) != 0) {
      *piVar7 = *piVar7 + 1;
      *(int *)(param_1 + 0xd0) = *(int *)(param_1 + 0xd0) + 1;
    }
    param_3 = param_3 >> 1;
    piVar7 = piVar7 + 1;
  } while (param_3 != 0);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xf98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0xf9c)) {
    piVar7 = (int *)(param_1 + 0xf9c);
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar3) {
        *piVar7 = *piVar7 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xfd8);
    if ((uVar4 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xfd8);
      return;
    }
  }
  return;
}

// ==== Aska::TaskManager::DecrementTaskLevelCount(unsigned int)
// vaddr 0x1f80720 | ghidra 0x2080720 | size 52 | symbol _ZN4Aska11TaskManager23DecrementTaskLevelCountEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager23DecrementTaskLevelCountEj(long param_1,uint param_2)

{
  int *piVar1;
  
  if (param_2 != 0) {
    piVar1 = (int *)(param_1 + 0x50);
    do {
      if ((param_2 & 1) != 0) {
        *piVar1 = *piVar1 + -1;
        *(int *)(param_1 + 0xd0) = *(int *)(param_1 + 0xd0) + -1;
      }
      param_2 = param_2 >> 1;
      piVar1 = piVar1 + 1;
    } while (param_2 != 0);
  }
  return;
}

// ==== Aska::TaskManager::PreAllocateTaskList(int)
// vaddr 0x1f80754 | ghidra 0x2080754 | size 108 | symbol _ZN4Aska11TaskManager19PreAllocateTaskListEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager19PreAllocateTaskListEi(long *param_1,int param_2)

{
  uint uVar1;
  undefined1 auVar2 [16];
  long lVar3;
  ulong uVar4;
  
  (**(code **)(*param_1 + 0x50))();
  if (0 < param_2) {
    uVar1 = param_2 + 0x21;
    auVar2._8_8_ = 0;
    auVar2._0_8_ = (long)(int)uVar1;
    uVar4 = -(ulong)(uVar1 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar1 << 3;
    if (SUB168(auVar2 * ZEXT816(8),8) != 0) {
      uVar4 = 0xffffffffffffffff;
    }
    lVar3 = operator new[](unsigned long, std::nothrow_t const&)(uVar4,PTR__ZSt7nothrow_02cb9a80);
    param_1[0x1d] = lVar3;
    if (lVar3 != 0) {
      param_1[0x1f] = lVar3 + (long)param_2 * 8;
      *(int *)(param_1 + 0x20) = param_2;
    }
  }
  return;
}

// ==== Aska::TaskManager::DeletePreAllocateTaskList()
// vaddr 0x1f807c0 | ghidra 0x20807c0 | size 52 | symbol _ZN4Aska11TaskManager25DeletePreAllocateTaskListEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager25DeletePreAllocateTaskListEv(long param_1)

{
  if (0 < *(int *)(param_1 + 0x100)) {
    if (*(long *)(param_1 + 0xe8) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0xe8) = 0;
    }
    *(undefined8 *)(param_1 + 0xf8) = 0;
  }
  *(undefined4 *)(param_1 + 0x100) = 0;
  return;
}

// ==== Aska::TaskManager::MergeManager(Aska::TaskManager*)
// vaddr 0x1f807f4 | ghidra 0x20807f4 | size 416 | symbol _ZN4Aska11TaskManager12MergeManagerEPS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager12MergeManagerEPS0_(long param_1,long param_2)

{
  long *plVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  long lVar7;
  long lVar8;
  undefined8 uVar9;
  
  lVar3 = *(long *)(*(long *)(param_1 + 0x108) + 0xe0);
  if (lVar3 != 0) {
    Aska::Semaphore::Wait() const(lVar3 + 0x70);
  }
  lVar7 = *(long *)(param_2 + 0x108);
  lVar8 = *(long *)(lVar7 + 0xe0);
  lVar3 = param_2;
  if (lVar8 != 0) {
    lVar3 = *(long *)(*(long *)(param_1 + 0x108) + 0xe0);
    if (lVar3 == 0) {
      *(long *)(*(long *)(param_1 + 0x108) + 0xe0) = lVar8;
      *(undefined8 *)(lVar7 + 0xe0) = 0;
      lVar3 = param_2;
    }
    else {
      Aska::CriticalSection::Enter() const(lVar3 + 0x44);
      Aska::CriticalSection::Enter() const(lVar8 + 0x44);
      uVar4 = 0;
      if (*(int *)(lVar8 + 0x2c) + 1U < *(uint *)(lVar8 + 0x30)) {
        uVar4 = *(int *)(lVar8 + 0x2c) + 1;
      }
      if (uVar4 != *(uint *)(lVar8 + 0x28)) {
        do {
          *(uint *)(lVar8 + 0x2c) = uVar4;
          lVar3 = *(long *)(*(long *)(param_1 + 0x108) + 0xe0);
          puVar5 = (undefined8 *)(*(long *)(lVar8 + 0x38) + (ulong)uVar4 * 0x30);
          uVar4 = *(uint *)(lVar3 + 0x28);
          if (*(uint *)(lVar3 + 0x2c) == uVar4) {
            puVar6 = (undefined8 *)0x0;
          }
          else {
            puVar6 = (undefined8 *)(*(long *)(lVar3 + 0x38) + (ulong)uVar4 * 0x30);
            iVar2 = 0;
            if (uVar4 + 1 < *(uint *)(lVar3 + 0x30)) {
              iVar2 = uVar4 + 1;
            }
            *(int *)(lVar3 + 0x28) = iVar2;
          }
          uVar9 = puVar5[4];
          puVar6[5] = puVar5[5];
          puVar6[4] = uVar9;
          uVar9 = puVar5[2];
          puVar6[3] = puVar5[3];
          puVar6[2] = uVar9;
          uVar9 = *puVar5;
          puVar6[1] = puVar5[1];
          *puVar6 = uVar9;
          uVar4 = 0;
          if (*(int *)(lVar8 + 0x2c) + 1U < *(uint *)(lVar8 + 0x30)) {
            uVar4 = *(int *)(lVar8 + 0x2c) + 1;
          }
        } while (uVar4 != *(uint *)(lVar8 + 0x28));
      }
      Aska::CriticalSection::Leave() const(lVar8 + 0x44);
      if (*(long **)(lVar7 + 0xe0) != (long *)0x0) {
        (**(code **)(**(long **)(lVar7 + 0xe0) + 8))();
        *(undefined8 *)(lVar7 + 0xe0) = 0;
      }
      Aska::CriticalSection::Leave() const(*(long *)(*(long *)(param_1 + 0x108) + 0xe0) + 0x44);
      lVar3 = param_2;
    }
  }
  do {
    *(undefined8 *)(lVar3 + 0x108) = *(undefined8 *)(param_1 + 0x108);
    *(undefined8 *)(lVar3 + 0xe0) = *(undefined8 *)(*(long *)(param_1 + 0x108) + 0xe0);
    plVar1 = (long *)(lVar3 + 0x118);
    lVar3 = *plVar1;
  } while (*plVar1 != param_2);
  lVar3 = *(long *)(*(long *)(param_1 + 0x108) + 0x110);
  *(long *)(lVar3 + 0x118) = param_2;
  *(long *)(param_2 + 0x110) = lVar3;
  *(undefined8 *)(param_2 + 0x118) = *(undefined8 *)(param_1 + 0x108);
  *(long *)(*(long *)(param_1 + 0x108) + 0x110) = param_2;
  lVar3 = *(long *)(*(long *)(param_1 + 0x108) + 0xe0);
  if (lVar3 == 0) {
    return;
  }
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(lVar3 + 0x70);
  return;
}

// ==== Aska::TaskManager::ReleaseMergedManager()
// vaddr 0x1f80994 | ghidra 0x2080994 | size 104 | symbol _ZN4Aska11TaskManager20ReleaseMergedManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager20ReleaseMergedManagerEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x108);
  if (*(long *)(lVar1 + 0xe0) != 0) {
    Aska::Semaphore::Wait() const(*(long *)(lVar1 + 0xe0) + 0x70);
  }
  if (lVar1 != param_1) {
    *(undefined8 *)(param_1 + 0xe0) = 0;
    *(undefined8 *)(*(long *)(param_1 + 0x118) + 0x110) = *(undefined8 *)(param_1 + 0x110);
    *(undefined8 *)(*(long *)(param_1 + 0x110) + 0x118) = *(undefined8 *)(param_1 + 0x118);
    *(long *)(param_1 + 0x110) = param_1;
    *(long *)(param_1 + 0x118) = param_1;
    *(long *)(param_1 + 0x108) = param_1;
    if (*(long *)(lVar1 + 0xe0) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(*(long *)(lVar1 + 0xe0) + 0x70);
      return;
    }
  }
  return;
}

// ==== Aska::TaskManager::GetTotalTaskNumber() const
// vaddr 0x1f809fc | ghidra 0x20809fc | size 348 | symbol _ZNK4Aska11TaskManager18GetTotalTaskNumberEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK4Aska11TaskManager18GetTotalTaskNumberEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  
  piVar1 = (int *)(param_1 + 0xf98);
  iVar6 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02080adc;
    }
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0xf9c);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      do {
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xfd8);
        if ((uVar5 & 1) == 0) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar4) {
              *piVar2 = *piVar2 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0xfd8);
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + 1;
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
          if (cVar3 == '\0') goto code_r0x02080acc;
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
code_r0x02080acc:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02080adc:
  DataMemoryBarrier(2,3);
  iVar6 = 0;
  lVar7 = param_1;
  do {
    piVar1 = (int *)(lVar7 + 0xd0);
    lVar7 = *(long *)(lVar7 + 0x118);
    iVar6 = *piVar1 + iVar6;
  } while (lVar7 != param_1);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xf98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0xf9c)) {
    piVar1 = (int *)(param_1 + 0xf9c);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0xfd8);
    if ((uVar5 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xfd8);
    }
  }
  return iVar6;
}

// ==== Aska::TaskManager::AllocateBroadcast()
// vaddr 0x1f80b58 | ghidra 0x2080b58 | size 76 | symbol _ZN4Aska11TaskManager17AllocateBroadcastEv | lib libSOA-3.7.0.so | 2026-10-04
byte _ZN4Aska11TaskManager17AllocateBroadcastEv(long param_1)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = *(byte *)(param_1 + 0x120);
  if ((bVar1 >> 4 & 1) == 0) {
    bVar2 = 0x10;
  }
  else if ((bVar1 >> 5 & 1) == 0) {
    bVar2 = 0x20;
  }
  else if ((bVar1 >> 6 & 1) == 0) {
    bVar2 = 0x40;
  }
  else {
    if ((char)bVar1 < '\0') {
      return 0;
    }
    bVar2 = 0x80;
  }
  *(byte *)(param_1 + 0x120) = bVar2 | bVar1;
  return bVar2;
}

// ==== Aska::TaskManager::AllocateBroadcast(int)
// vaddr 0x1f80ba4 | ghidra 0x2080ba4 | size 124 | symbol _ZN4Aska11TaskManager17AllocateBroadcastEi | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska11TaskManager17AllocateBroadcastEi(long param_1,int param_2)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  
  bVar2 = *(byte *)(param_1 + 0x120);
  uVar4 = (uint)bVar2;
  if ((bVar2 >> 4 & 1) == 0) {
    uVar4 = uVar4 | 0x10;
    uVar3 = 0x10;
    *(char *)(param_1 + 0x120) = (char)uVar4;
    if (param_2 < 2) {
      return 0x10;
    }
    param_2 = param_2 + -1;
    bVar2 = bVar2 & 0x20;
  }
  else {
    uVar3 = 0;
    bVar2 = bVar2 >> 5 & 1;
  }
  if (bVar2 == 0) {
    uVar3 = uVar3 | 0x20;
    *(char *)(param_1 + 0x120) = (char)(uVar4 | 0x20);
    if (param_2 < 2) {
      return uVar3;
    }
    param_2 = param_2 + -1;
    uVar1 = uVar4 & 0x40;
    uVar4 = uVar4 | 0x20;
  }
  else {
    uVar1 = uVar4 >> 6 & 1;
  }
  if (uVar1 == 0) {
    uVar3 = uVar3 | 0x40;
    uVar4 = uVar4 | 0x40;
    *(char *)(param_1 + 0x120) = (char)uVar4;
    if (param_2 < 2) {
      return uVar3;
    }
  }
  if (uVar4 >> 7 == 0) {
    uVar3 = uVar3 | 0xffffff80;
    *(byte *)(param_1 + 0x120) = (byte)uVar4 | 0x80;
  }
  return uVar3;
}

// ==== Aska::TaskManager::ReleaseBroadcast(unsigned char)
// vaddr 0x1f80c20 | ghidra 0x2080c20 | size 16 | symbol _ZN4Aska11TaskManager16ReleaseBroadcastEh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager16ReleaseBroadcastEh(long param_1,byte param_2)

{
  *(byte *)(param_1 + 0x120) = *(byte *)(param_1 + 0x120) & (param_2 ^ 0xff);
  return;
}

// ==== Aska::TaskManager::Broadcast(unsigned char)
// vaddr 0x1f80c30 | ghidra 0x2080c30 | size 136 | symbol _ZN4Aska11TaskManager9BroadcastEh | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska11TaskManager9BroadcastEh(long param_1,byte param_2)

{
  ulong uVar1;
  long lVar2;
  long *plVar3;
  long lVar4;
  
  if ((*(byte *)(param_1 + 0x120) & param_2) != 0) {
    uVar1 = (ulong)*(uint *)(param_1 + 0xdc);
    lVar2 = param_1;
    if (0 < (int)*(uint *)(param_1 + 0xdc)) {
      plVar3 = *(long **)(param_1 + 0xe8);
      do {
        lVar4 = *plVar3;
        if (lVar4 != 0) {
          *(byte *)(lVar4 + 0x26) = *(byte *)(lVar4 + 0x26) | param_2;
        }
        uVar1 = uVar1 - 1;
        plVar3 = plVar3 + 1;
      } while (uVar1 != 0);
    }
    do {
      for (lVar4 = *(long *)(lVar2 + 0x18); lVar2 + 8 != lVar4; lVar4 = *(long *)(lVar4 + 0x10)) {
        *(byte *)(lVar4 + 0x26) = *(byte *)(lVar4 + 0x26) | param_2;
      }
      plVar3 = (long *)(lVar2 + 0x118);
      lVar2 = *plVar3;
    } while (*plVar3 != param_1);
    return 1;
  }
  return 0;
}

// ==== Aska::TaskManager::SetupMessageQueue(Aska::MessageQueue*)
// vaddr 0x1f80cb8 | ghidra 0x2080cb8 | size 120 | symbol _ZN4Aska11TaskManager17SetupMessageQueueEPNS_12MessageQueueE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager17SetupMessageQueueEPNS_12MessageQueueE(long param_1,long param_2)

{
  long lVar1;
  
  if (*(long *)(param_1 + 0x108) == param_1) {
    if (*(long **)(param_1 + 0xe0) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0xe0) + 8))();
      lVar1 = *(long *)(param_1 + 0x108);
      *(undefined8 *)(param_1 + 0xe0) = 0;
      do {
        *(undefined8 *)(lVar1 + 0xe0) = 0;
        lVar1 = *(long *)(lVar1 + 0x118);
      } while (*(long *)(param_1 + 0x108) != lVar1);
    }
    *(long *)(param_2 + 0x18) = param_1;
    lVar1 = *(long *)(param_1 + 0x108);
    *(long *)(param_1 + 0xe0) = param_2;
    do {
      *(long *)(lVar1 + 0xe0) = param_2;
      lVar1 = *(long *)(lVar1 + 0x118);
    } while (*(long *)(param_1 + 0x108) != lVar1);
  }
  return;
}

// ==== Aska::TaskManager::PostMessage(unsigned short, void*, void*)
// vaddr 0x1f80d30 | ghidra 0x2080d30 | size 32 | symbol _ZN4Aska11TaskManager11PostMessageEtPvS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager11PostMessageEtPvS1_(long param_1)

{
  if (*(long **)(param_1 + 0xe0) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02080d48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + 0xe0) + 0x18))();
    return;
  }
  return;
}

// ==== Aska::TaskManager::PostMessageToTask(unsigned short, Aska::Task*, void*, void*)
// vaddr 0x1f80d50 | ghidra 0x2080d50 | size 28 | symbol _ZN4Aska11TaskManager17PostMessageToTaskEtPNS_4TaskEPvS3_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager17PostMessageToTaskEtPNS_4TaskEPvS3_(long param_1)

{
  if (*(long **)(param_1 + 0xe0) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02080d64. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + 0xe0) + 0x20))();
    return;
  }
  return;
}

// ==== Aska::TaskManager::PostMessage(unsigned short, void*, void*, Aska::MessageBlockCondition*, unsigned int*)
// vaddr 0x1f80d6c | ghidra 0x2080d6c | size 24 | symbol _ZN4Aska11TaskManager11PostMessageEtPvS1_PNS_21MessageBlockConditionEPj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager11PostMessageEtPvS1_PNS_21MessageBlockConditionEPj(long param_1)

{
  if (*(long **)(param_1 + 0xe0) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02080d7c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + 0xe0) + 0x18))();
    return;
  }
  return;
}

// ==== Aska::TaskManager::PostMessageToTask(unsigned short, Aska::Task*, void*, void*, unsigned int*)
// vaddr 0x1f80d84 | ghidra 0x2080d84 | size 24 | symbol _ZN4Aska11TaskManager17PostMessageToTaskEtPNS_4TaskEPvS3_Pj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager17PostMessageToTaskEtPNS_4TaskEPvS3_Pj(long param_1)

{
  if (*(long **)(param_1 + 0xe0) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02080d94. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + 0xe0) + 0x20))();
    return;
  }
  return;
}

// ==== Aska::TaskManager::SendMessage(unsigned short, void*, void*)
// vaddr 0x1f80d9c | ghidra 0x2080d9c | size 28 | symbol _ZN4Aska11TaskManager11SendMessageEtPvS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager11SendMessageEtPvS1_(long param_1)

{
  if (*(long **)(param_1 + 0xe0) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02080db0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + 0xe0) + 0x28))();
    return;
  }
  return;
}

// ==== Aska::TaskManager::SendMessage(unsigned short, void*, void*, Aska::MessageBlockCondition*)
// vaddr 0x1f80db8 | ghidra 0x2080db8 | size 24 | symbol _ZN4Aska11TaskManager11SendMessageEtPvS1_PNS_21MessageBlockConditionE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager11SendMessageEtPvS1_PNS_21MessageBlockConditionE(long param_1)

{
  if (*(long **)(param_1 + 0xe0) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02080dc8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + 0xe0) + 0x28))();
    return;
  }
  return;
}

// ==== Aska::TaskManager::SendMessageToTask(unsigned short, Aska::Task*, void*, void*)
// vaddr 0x1f80dd0 | ghidra 0x2080dd0 | size 24 | symbol _ZN4Aska11TaskManager17SendMessageToTaskEtPNS_4TaskEPvS3_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager17SendMessageToTaskEtPNS_4TaskEPvS3_(long param_1)

{
  if (*(long **)(param_1 + 0xe0) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02080de0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + 0xe0) + 0x30))();
    return;
  }
  return;
}

// ==== Aska::TaskManager::GetMessage(Aska::MessageBlock*)
// vaddr 0x1f80de8 | ghidra 0x2080de8 | size 36 | symbol _ZN4Aska11TaskManager10GetMessageEPNS_12MessageBlockE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska11TaskManager10GetMessageEPNS_12MessageBlockE(long param_1,long param_2)

{
  long *plVar1;
  undefined8 uVar2;
  
  if ((param_2 != 0) &&
     (plVar1 = *(long **)(*(long *)(param_1 + 0x108) + 0xe0), plVar1 != (long *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x02080e00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(*plVar1 + 0x48))();
    return uVar2;
  }
  return 0;
}

// ==== Aska::TaskManager::PeekMessage()
// vaddr 0x1f80e0c | ghidra 0x2080e0c | size 28 | symbol _ZN4Aska11TaskManager11PeekMessageEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager11PeekMessageEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(*(long *)(param_1 + 0x108) + 0xe0);
  if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02080e20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x50))();
    return;
  }
  return;
}

// ==== Aska::TaskManager::DispatchMessage(Aska::MessageBlock*)
// vaddr 0x1f80e28 | ghidra 0x2080e28 | size 28 | symbol _ZN4Aska11TaskManager15DispatchMessageEPNS_12MessageBlockE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager15DispatchMessageEPNS_12MessageBlockE(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(*(long *)(param_1 + 0x108) + 0xe0);
  if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02080e3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x58))();
    return;
  }
  return;
}

// ==== Aska::TaskManager::CreateEndNotifyList(int)
// vaddr 0x1f80e44 | ghidra 0x2080e44 | size 168 | symbol _ZN4Aska11TaskManager19CreateEndNotifyListEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska11TaskManager19CreateEndNotifyListEi(long param_1,int param_2)

{
  uint uVar1;
  undefined1 auVar2 [16];
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  
  if (param_2 < 1) {
    uVar3 = 0;
  }
  else {
    uVar1 = param_2 + 1;
    if (*(long *)(param_1 + 0x128) != 0) {
      operator delete[](void*)();
    }
    auVar2._8_8_ = 0;
    auVar2._0_8_ = (long)(int)uVar1;
    lVar5 = ((long)(int)uVar1 + (long)(int)uVar1 * 2) * 8;
    if (SUB168(auVar2 * ZEXT816(0x18),8) != 0) {
      lVar5 = -1;
    }
    lVar5 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 0x128) = lVar5;
    uVar3 = 0;
    if (lVar5 != 0) {
      *(short *)(param_1 + 0x122) = (short)uVar1;
      *(undefined1 *)(lVar5 + 0x11) = 0;
      *(undefined1 *)(*(long *)(param_1 + 0x128) + 0x12) = 0;
      lVar4 = (ulong)uVar1 - 1;
      *(undefined1 *)(*(long *)(param_1 + 0x128) + 0x10) = 1;
      lVar5 = 0x28;
      do {
        lVar4 = lVar4 + -1;
        *(undefined1 *)(*(long *)(param_1 + 0x128) + lVar5) = 0;
        lVar5 = lVar5 + 0x18;
      } while (lVar4 != 0);
      uVar3 = 1;
    }
  }
  return uVar3;
}

// ==== Aska::TaskManager::AddEndNotify(Aska::INotify*, unsigned long)
// vaddr 0x1f80eec | ghidra 0x2080eec | size 204 | symbol _ZN4Aska11TaskManager12AddEndNotifyEPNS_7INotifyEm | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TaskManager12AddEndNotifyEPNS_7INotifyEm
          (long param_1,undefined8 param_2,undefined8 param_3)

{
  ushort uVar1;
  long lVar2;
  undefined8 uVar3;
  uint uVar4;
  long lVar5;
  char *pcVar6;
  
  lVar2 = *(long *)(param_1 + 0x128);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar1 = *(ushort *)(param_1 + 0x122);
    if ((ulong)uVar1 < 2) {
      uVar4 = 1;
      if (uVar1 == 1) {
        return 0;
      }
    }
    else {
      pcVar6 = (char *)(lVar2 + 0x28);
      lVar5 = 1;
      do {
        if (*pcVar6 == '\0') break;
        lVar5 = lVar5 + 1;
        pcVar6 = pcVar6 + 0x18;
      } while (lVar5 < (long)(ulong)uVar1);
      uVar4 = (uint)lVar5;
      if (uVar4 == uVar1) {
        return 0;
      }
    }
    *(undefined8 *)(lVar2 + (long)(int)uVar4 * 0x18) = param_2;
    *(undefined8 *)(*(long *)(param_1 + 0x128) + (long)(int)uVar4 * 0x18 + 8) = param_3;
    uVar3 = 1;
    *(undefined1 *)(*(long *)(param_1 + 0x128) + (long)(int)uVar4 * 0x18 + 0x10) = 1;
    *(undefined1 *)(*(long *)(param_1 + 0x128) + (long)(int)uVar4 * 0x18 + 0x12) =
         *(undefined1 *)(*(long *)(param_1 + 0x128) + 0x12);
    *(undefined1 *)(*(long *)(param_1 + 0x128) + (long)(int)uVar4 * 0x18 + 0x11) = 0;
    *(char *)(*(long *)(param_1 + 0x128) +
              (ulong)*(byte *)(*(long *)(param_1 + 0x128) + 0x12) * 0x18 + 0x11) = (char)uVar4;
    *(char *)(*(long *)(param_1 + 0x128) + 0x12) = (char)uVar4;
  }
  return uVar3;
}

// ==== Aska::TaskManager::RemoveEndNotify(Aska::INotify*, unsigned long)
// vaddr 0x1f80fb8 | ghidra 0x2080fb8 | size 144 | symbol _ZN4Aska11TaskManager15RemoveEndNotifyEPNS_7INotifyEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager15RemoveEndNotifyEPNS_7INotifyEm(long param_1,long param_2,long param_3)

{
  byte bVar1;
  long lVar2;
  long *plVar3;
  ulong uVar4;
  long lVar5;
  
  lVar2 = *(long *)(param_1 + 0x128);
  if ((lVar2 != 0) && (uVar4 = (ulong)*(byte *)(lVar2 + 0x11), uVar4 != 0)) {
    while( true ) {
      plVar3 = (long *)(lVar2 + uVar4 * 0x18);
      bVar1 = *(byte *)((long)plVar3 + 0x11);
      if ((*plVar3 == param_2) && (*(long *)(lVar2 + uVar4 * 0x18 + 8) == param_3)) {
        lVar5 = uVar4 * 0x18;
        *(byte *)(lVar2 + (ulong)*(byte *)(lVar2 + lVar5 + 0x12) * 0x18 + 0x11) = bVar1;
        lVar2 = *(long *)(param_1 + 0x128) + lVar5;
        *(undefined1 *)(*(long *)(param_1 + 0x128) + (ulong)*(byte *)(lVar2 + 0x11) * 0x18 + 0x12) =
             *(undefined1 *)(lVar2 + 0x12);
        *(undefined1 *)(*(long *)(param_1 + 0x128) + lVar5 + 0x10) = 0;
      }
      if (bVar1 == 0) break;
      lVar2 = *(long *)(param_1 + 0x128);
      uVar4 = (ulong)bVar1;
    }
  }
  return;
}

// ==== Aska::TaskManager::AddThreadBarrier(int)
// vaddr 0x1f81048 | ghidra 0x2081048 | size 192 | symbol _ZN4Aska11TaskManager16AddThreadBarrierEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager16AddThreadBarrierEi(long param_1,uint param_2)

{
  int *piVar1;
  long lVar2;
  uint uVar3;
  ulong uVar4;
  int iVar5;
  long lVar6;
  
  Aska::CriticalSection::Enter() const(param_1 + 0xf38);
  uVar3 = 1 << (ulong)(param_2 & 0x1f);
  lVar6 = (long)(int)param_2;
  if (((*(uint *)(param_1 + 0xe30) & uVar3) == 0) &&
     (uVar4 = Aska::Event::Create(bool, bool)(param_1 + lVar6 * 0x68 + 0x130,1,0), (uVar4 & 1) != 0)) {
    *(uint *)(param_1 + 0xe30) = *(uint *)(param_1 + 0xe30) | uVar3;
  }
  lVar2 = param_1 + lVar6 * 4;
  iVar5 = *(int *)(lVar2 + 0xe38);
  piVar1 = (int *)(lVar2 + 0xe38);
  if (iVar5 == 0) {
    if ((*(uint *)(param_1 + 0xe34) & uVar3) == 0) {
      Aska::Event::Reset() const(param_1 + lVar6 * 0x68 + 0x130);
      *(uint *)(param_1 + 0xe34) = *(uint *)(param_1 + 0xe34) | uVar3;
      iVar5 = *piVar1;
    }
    else {
      iVar5 = 0;
    }
  }
  *piVar1 = iVar5 + 1;
  (*(code *)PTR__ZNK4Aska15CriticalSection5LeaveEv_02ca8d00)(param_1 + 0xf38);
  return;
}

// ==== Aska::TaskManager::DeleteThreadBarrier(int)
// vaddr 0x1f81108 | ghidra 0x2081108 | size 88 | symbol _ZN4Aska11TaskManager19DeleteThreadBarrierEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager19DeleteThreadBarrierEi(long param_1,uint param_2)

{
  long lVar1;
  int iVar2;
  
  Aska::CriticalSection::Enter() const(param_1 + 0xf38);
  if ((*(uint *)(param_1 + 0xe30) & 1 << (ulong)(param_2 & 0x1f)) != 0) {
    lVar1 = param_1 + (long)(int)param_2 * 4;
    iVar2 = *(int *)(lVar1 + 0xe38);
    if (0 < iVar2) {
      *(int *)(lVar1 + 0xe38) = iVar2 + -1;
    }
  }
  (*(code *)PTR__ZNK4Aska15CriticalSection5LeaveEv_02ca8d00)(param_1 + 0xf38);
  return;
}

// ==== Aska::TaskManager::IncrementThreadBarrierCount(int)
// vaddr 0x1f81160 | ghidra 0x2081160 | size 176 | symbol _ZN4Aska11TaskManager27IncrementThreadBarrierCountEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager27IncrementThreadBarrierCountEi(long param_1,uint param_2)

{
  long lVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 1 << (ulong)(param_2 & 0x1f);
  if ((*(uint *)(param_1 + 0xe30) & uVar3) != 0) {
    lVar1 = param_1 + (long)(int)param_2 * 4;
    iVar2 = *(int *)(lVar1 + 0xe38);
    Aska::CriticalSection::Enter() const(param_1 + 0xf38);
    if (*(int *)(lVar1 + 0xeb8) < iVar2) {
      iVar2 = *(int *)(lVar1 + 0xeb8) + 1;
    }
    *(int *)(lVar1 + 0xeb8) = iVar2;
    if ((0 < iVar2) && ((*(uint *)(param_1 + 0xe34) & uVar3) == 0)) {
      Aska::Event::Reset() const(param_1 + (long)(int)param_2 * 0x68 + 0x130);
      *(uint *)(param_1 + 0xe34) = *(uint *)(param_1 + 0xe34) | uVar3;
    }
    (*(code *)PTR__ZNK4Aska15CriticalSection5LeaveEv_02ca8d00)(param_1 + 0xf38);
    return;
  }
  return;
}

// ==== Aska::TaskManager::DecrementThreadBarrierCount(int)
// vaddr 0x1f81210 | ghidra 0x2081210 | size 124 | symbol _ZN4Aska11TaskManager27DecrementThreadBarrierCountEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager27DecrementThreadBarrierCountEi(long param_1,uint param_2)

{
  long lVar1;
  uint uVar2;
  int iVar3;
  
  Aska::CriticalSection::Enter() const(param_1 + 0xf38);
  lVar1 = param_1 + (long)(int)param_2 * 4;
  iVar3 = *(int *)(lVar1 + 0xeb8) + -1;
  *(int *)(lVar1 + 0xeb8) = iVar3;
  if (iVar3 == 0) {
    uVar2 = 1 << (ulong)(param_2 & 0x1f);
    if ((*(uint *)(param_1 + 0xe34) & uVar2) != 0) {
      Aska::Event::Set() const(param_1 + (long)(int)param_2 * 0x68 + 0x130);
      *(uint *)(param_1 + 0xe34) = *(uint *)(param_1 + 0xe34) & (uVar2 ^ 0xffffffff);
    }
  }
  (*(code *)PTR__ZNK4Aska15CriticalSection5LeaveEv_02ca8d00)(param_1 + 0xf38);
  return;
}

// ==== Aska::TaskManager::IsCalled(Aska::Task*)
// vaddr 0x1f8128c | ghidra 0x208128c | size 124 | symbol _ZN4Aska11TaskManager8IsCalledEPNS_4TaskE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska11TaskManager8IsCalledEPNS_4TaskE(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  if (*(long *)(param_1 + 0xe8) == 0) {
    lVar1 = *(long *)(param_1 + 0x108);
    if (lVar1 == param_1) {
      return 1;
    }
    lVar2 = (long)*(int *)(lVar1 + 0xd8);
    do {
      lVar2 = lVar2 + 1;
      if (*(int *)(lVar1 + 0xdc) <= lVar2) {
        return 1;
      }
    } while (*(long *)(*(long *)(lVar1 + 0xe8) + lVar2 * 8) != param_2);
  }
  else {
    lVar1 = (long)*(int *)(param_1 + 0xd8);
    do {
      lVar1 = lVar1 + 1;
      if (*(int *)(param_1 + 0xdc) <= lVar1) {
        return 1;
      }
    } while (*(long *)(*(long *)(param_1 + 0xe8) + lVar1 * 8) != param_2);
  }
  return 0;
}

// ==== Aska::TaskManager::OwnersKickTask()
// vaddr 0x1f81308 | ghidra 0x2081308 | size 648 | symbol _ZN4Aska11TaskManager14OwnersKickTaskEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager14OwnersKickTaskEv(long *param_1)

{
  long *plVar1;
  uint *puVar2;
  uint uVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  long *plVar7;
  undefined8 *puVar8;
  int iVar9;
  long lVar10;
  int iVar11;
  long lVar12;
  ulong uVar13;
  long lVar14;
  long *plVar15;
  ulong uVar16;
  
  if (*(long **)PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620 == param_1) {
    Aska::PerformanceCounter::Mark(int)(*(undefined8 *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8,0);
  }
  lVar10 = 0;
  plVar1 = param_1 + 0x1e7;
  lVar12 = 0xeb8;
  lVar14 = 0x130;
  do {
    uVar5 = 1 << (ulong)((uint)lVar10 & 0x1f);
    if ((*(uint *)(param_1 + 0x1c6) & uVar5) != 0) {
      puVar2 = (uint *)((long)param_1 + lVar12);
      uVar3 = puVar2[-0x20];
      Aska::CriticalSection::Enter() const(plVar1);
      uVar3 = (*puVar2 & (int)*puVar2 >> 0x1f) + uVar3;
      *puVar2 = uVar3;
      if ((0 < (int)uVar3) && ((*(uint *)((long)param_1 + 0xe34) & uVar5) == 0)) {
        Aska::Event::Reset() const((long)param_1 + lVar14);
        *(uint *)((long)param_1 + 0xe34) = *(uint *)((long)param_1 + 0xe34) | uVar5;
      }
      Aska::CriticalSection::Leave() const(plVar1);
    }
    lVar10 = lVar10 + 1;
    lVar12 = lVar12 + 4;
    lVar14 = lVar14 + 0x68;
  } while (lVar10 != 0x20);
  iVar6 = Aska::TaskManager::GetTotalTaskNumber() const(param_1);
  *(int *)((long)param_1 + 0xdc) = iVar6;
  if (iVar6 != 0) {
    if ((int)param_1[0x20] < iVar6) {
      (**(code **)(*param_1 + 0x48))(param_1,iVar6);
    }
    if (param_1[0x1d] != 0) {
      Aska::TaskManager::MakeTaskList()(param_1);
      plVar15 = (long *)param_1[0x1d];
      iVar9 = 0;
      uVar13 = 0;
      *(undefined8 *)((long)param_1 + 0xd4) = 0;
      while( true ) {
        iVar11 = (int)uVar13;
        if (plVar15 == *(long **)(param_1[0x1f] + (long)iVar11 * 8)) {
          lVar10 = (long)iVar11 * 0x68 + 0x198;
          uVar16 = (long)iVar11;
          do {
            uVar5 = (int)uVar16 + 1;
            uVar13 = uVar16 + 1;
            *(uint *)((long)param_1 + 0xd4) = uVar5;
            if ((*(uint *)(param_1 + 0x1c6) & 1 << (ulong)(uVar5 & 0x1f)) != 0) {
              Aska::CriticalSection::Enter() const(plVar1);
              iVar9 = *(int *)((long)param_1 + uVar16 * 4 + 0xebc);
              Aska::CriticalSection::Leave() const(plVar1);
              if (0 < iVar9) {
                Aska::Event::Wait(unsigned int) const((long)param_1 + lVar10,0);
              }
            }
            lVar10 = lVar10 + 0x68;
            lVar12 = uVar16 * 8;
            uVar16 = uVar13;
          } while (plVar15 == *(long **)(param_1[0x1f] + lVar12 + 8));
          iVar9 = (int)param_1[0x1b];
        }
        if (iVar6 <= iVar9) break;
        plVar7 = (long *)*plVar15;
        if ((plVar7 != (long *)0x0) && ((*(byte *)((long)plVar7 + 0x24) >> 1 & 1) == 0)) {
          (**(code **)(*plVar7 + 0x68))(plVar7,uVar13 & 0xffffffff);
          iVar9 = (int)param_1[0x1b];
        }
        iVar9 = iVar9 + 1;
        *(int *)(param_1 + 0x1b) = iVar9;
        plVar15 = plVar15 + 1;
      }
      lVar10 = param_1[0x25];
      if ((lVar10 != 0) && (bVar4 = *(byte *)(lVar10 + 0x11), bVar4 != 0)) {
        while( true ) {
          uVar13 = (ulong)bVar4;
          puVar8 = *(undefined8 **)(lVar10 + uVar13 * 0x18);
          if (puVar8 != (undefined8 *)0x0) {
            (**(code **)*puVar8)(puVar8,*(undefined8 *)(lVar10 + uVar13 * 0x18 + 8));
          }
          bVar4 = *(byte *)(lVar10 + uVar13 * 0x18 + 0x11);
          if (bVar4 == 0) break;
          lVar10 = param_1[0x25];
        }
      }
      if (((int)param_1[0x20] == 0) && (param_1[0x1d] != 0)) {
        (*(code *)PTR__ZdaPv_02cb5db8)();
        return;
      }
    }
  }
  return;
}

// ==== Aska::TaskManager::MakeTaskList()
// vaddr 0x1f81590 | ghidra 0x2081590 | size 2116 | symbol _ZN4Aska11TaskManager12MakeTaskListEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager12MakeTaskListEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  char cVar8;
  bool bVar9;
  undefined8 uVar10;
  ulong uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int *piVar16;
  long lVar17;
  int iVar18;
  long lVar19;
  long lVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  uint uVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int aiStack_e0 [4];
  int iStack_d0;
  int iStack_cc;
  int iStack_c8;
  int iStack_c4;
  int iStack_c0;
  int iStack_bc;
  int iStack_b8;
  int iStack_b4;
  int iStack_b0;
  int iStack_ac;
  int iStack_a8;
  int iStack_a4;
  int iStack_a0;
  int iStack_9c;
  int iStack_98;
  int iStack_94;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  lVar19 = *(long *)(param_1 + 0x108);
  piVar16 = (int *)(lVar19 + 0xf98);
  iVar12 = 0;
code_r0x020815bc:
  do {
    if (*piVar16 != -1) {
      ClearExclusiveLocal();
      bVar9 = iVar12 < 0x1ff;
      iVar12 = iVar12 + 1;
      if (bVar9) goto code_r0x020815bc;
      piVar3 = (int *)(lVar19 + 0xf9c);
      do {
        cVar8 = '\x01';
        bVar9 = (bool)ExclusiveMonitorPass(piVar3,0x10);
        if (bVar9) {
          *piVar3 = *piVar3 + 1;
          cVar8 = ExclusiveMonitorsStatus();
        }
      } while (cVar8 != '\0');
      do {
        if (*piVar16 != -1) {
          ClearExclusiveLocal();
          do {
            uVar11 = Aska::Semaphore::IsReady() const(lVar19 + 0xfd8);
            if ((uVar11 & 1) == 0) {
              do {
                cVar8 = '\x01';
                bVar9 = (bool)ExclusiveMonitorPass(piVar3,0x10);
                if (bVar9) {
                  *piVar3 = *piVar3 + -1;
                  cVar8 = ExclusiveMonitorsStatus();
                }
              } while (cVar8 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
            else {
              Aska::Semaphore::Wait() const(lVar19 + 0xfd8);
            }
            do {
              cVar8 = '\x01';
              bVar9 = (bool)ExclusiveMonitorPass(piVar3,0x10);
              if (bVar9) {
                *piVar3 = *piVar3 + 1;
                cVar8 = ExclusiveMonitorsStatus();
              }
            } while (cVar8 != '\0');
            while (*piVar16 == -1) {
              cVar8 = '\x01';
              bVar9 = (bool)ExclusiveMonitorPass(piVar16,0x10);
              if (bVar9) {
                *piVar16 = 0;
                cVar8 = ExclusiveMonitorsStatus();
              }
              if (cVar8 == '\0') goto code_r0x02081674;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar8 = '\x01';
        bVar9 = (bool)ExclusiveMonitorPass(piVar16,0x10);
        if (bVar9) {
          *piVar16 = 0;
          cVar8 = ExclusiveMonitorsStatus();
        }
      } while (cVar8 != '\0');
code_r0x02081674:
      do {
        cVar8 = '\x01';
        bVar9 = (bool)ExclusiveMonitorPass(piVar3,0x10);
        if (bVar9) {
          *piVar3 = *piVar3 + -1;
          cVar8 = ExclusiveMonitorsStatus();
        }
      } while (cVar8 != '\0');
code_r0x02081684:
      DataMemoryBarrier(2,3);
      lVar19 = *(long *)(lVar19 + 0x118);
      do {
        if (lVar19 == *(long *)(param_1 + 0x108)) {
          memset(aiStack_e0,0,0x80);
          iVar21 = 0;
          iStack_a4 = 0;
          iStack_a8 = 0;
          iStack_ac = 0;
          iStack_b0 = 0;
          iStack_b4 = 0;
          iStack_b8 = 0;
          iStack_bc = 0;
          iStack_c0 = 0;
          iStack_c4 = 0;
          iStack_c8 = 0;
          iStack_cc = 0;
          iStack_d0 = 0;
          aiStack_e0[3] = 0;
          iVar12 = 0;
          aiStack_e0[1] = 0;
          lVar20 = lVar19;
          iVar15 = iStack_a0;
          iVar14 = iStack_9c;
          iVar13 = iStack_98;
          iVar18 = iStack_94;
          do {
            iVar29 = (int)uStack_90 + (int)*(undefined8 *)(lVar20 + 0xa0);
            iVar30 = (int)((ulong)uStack_90 >> 0x20) +
                     (int)((ulong)*(undefined8 *)(lVar20 + 0xa0) >> 0x20);
            iVar31 = (int)uStack_88 + (int)*(undefined8 *)(lVar20 + 0xa8);
            iVar32 = (int)((ulong)uStack_88 >> 0x20) +
                     (int)((ulong)*(undefined8 *)(lVar20 + 0xa8) >> 0x20);
            iVar25 = (int)uStack_80 + (int)*(undefined8 *)(lVar20 + 0xb0);
            iVar26 = (int)((ulong)uStack_80 >> 0x20) +
                     (int)((ulong)*(undefined8 *)(lVar20 + 0xb0) >> 0x20);
            uStack_80 = CONCAT44(iVar26,iVar25);
            iVar27 = (int)uStack_78 + (int)*(undefined8 *)(lVar20 + 0xb8);
            iVar28 = (int)((ulong)uStack_78 >> 0x20) +
                     (int)((ulong)*(undefined8 *)(lVar20 + 0xb8) >> 0x20);
            uStack_78 = CONCAT44(iVar28,iVar27);
            aiStack_e0[1] = aiStack_e0[1] + *(int *)(lVar20 + 0x50);
            iVar12 = iVar12 + *(int *)(lVar20 + 0x54);
            aiStack_e0[3] = aiStack_e0[3] + *(int *)(lVar20 + 0x58);
            iStack_d0 = iStack_d0 + *(int *)(lVar20 + 0x5c);
            piVar16 = (int *)(lVar20 + 0x80);
            piVar4 = (int *)(lVar20 + 0x84);
            iStack_cc = iStack_cc + *(int *)(lVar20 + 0x60);
            iStack_c8 = iStack_c8 + *(int *)(lVar20 + 100);
            piVar3 = (int *)(lVar20 + 0x88);
            piVar5 = (int *)(lVar20 + 0x8c);
            iStack_c4 = iStack_c4 + *(int *)(lVar20 + 0x68);
            iStack_c0 = iStack_c0 + *(int *)(lVar20 + 0x6c);
            piVar1 = (int *)(lVar20 + 0x90);
            piVar6 = (int *)(lVar20 + 0x94);
            iStack_bc = iStack_bc + *(int *)(lVar20 + 0x70);
            iStack_b8 = iStack_b8 + *(int *)(lVar20 + 0x74);
            piVar2 = (int *)(lVar20 + 0x98);
            piVar7 = (int *)(lVar20 + 0x9c);
            uStack_88 = CONCAT44(iVar32,iVar31);
            uStack_90 = CONCAT44(iVar30,iVar29);
            iStack_b4 = iStack_b4 + *(int *)(lVar20 + 0x78);
            iStack_b0 = iStack_b0 + *(int *)(lVar20 + 0x7c);
            iVar22 = (int)uStack_70 + (int)*(undefined8 *)(lVar20 + 0xc0);
            iVar23 = (int)((ulong)uStack_70 >> 0x20) +
                     (int)((ulong)*(undefined8 *)(lVar20 + 0xc0) >> 0x20);
            uStack_70 = CONCAT44(iVar23,iVar22);
            uVar24 = (int)uStack_68 + (int)*(undefined8 *)(lVar20 + 200);
            uStack_68 = (ulong)uVar24;
            lVar20 = *(long *)(lVar20 + 0x118);
            iVar18 = iVar18 + *piVar7;
            iStack_ac = iStack_ac + *piVar16;
            iStack_a8 = iStack_a8 + *piVar4;
            iStack_a4 = iStack_a4 + *piVar3;
            iVar21 = iVar21 + *piVar5;
            iVar15 = iVar15 + *piVar1;
            iVar14 = iVar14 + *piVar6;
            iVar13 = iVar13 + *piVar2;
          } while (lVar20 != lVar19);
          aiStack_e0[0] = 0;
          aiStack_e0[2] = iVar12 + aiStack_e0[1];
          aiStack_e0[3] = aiStack_e0[3] + iVar12 + aiStack_e0[1];
          iStack_d0 = iStack_d0 + aiStack_e0[3];
          iStack_cc = iStack_cc + iStack_d0;
          iStack_c8 = iStack_c8 + iStack_cc;
          iStack_c4 = iStack_c4 + iStack_c8;
          iStack_c0 = iStack_c0 + iStack_c4;
          iStack_bc = iStack_bc + iStack_c0;
          iStack_b8 = iStack_b8 + iStack_bc;
          iStack_b4 = iStack_b4 + iStack_b8;
          iStack_b0 = iStack_b0 + iStack_b4;
          iStack_ac = iStack_ac + iStack_b0;
          iStack_a8 = iStack_a8 + iStack_ac;
          iStack_a4 = iStack_a4 + iStack_a8;
          iStack_a0 = iVar21 + iStack_a4;
          iStack_9c = iVar15 + iStack_a0;
          iStack_98 = iVar14 + iStack_9c;
          iStack_94 = iVar13 + iStack_98;
          iVar18 = iVar18 + iStack_94;
          iVar29 = iVar29 + iVar18;
          uStack_90 = CONCAT44(iVar29,iVar18);
          iVar30 = iVar30 + iVar29;
          iVar31 = iVar31 + iVar30;
          uStack_88 = CONCAT44(iVar31,iVar30);
          iVar32 = iVar32 + iVar31;
          iVar25 = iVar25 + iVar32;
          uStack_80 = CONCAT44(iVar25,iVar32);
          iVar26 = iVar26 + iVar25;
          iVar27 = iVar27 + iVar26;
          uStack_78 = CONCAT44(iVar27,iVar26);
          iVar28 = iVar28 + iVar27;
          iVar22 = iVar22 + iVar28;
          uStack_70 = CONCAT44(iVar22,iVar28);
          iVar23 = iVar23 + iVar22;
          uStack_68 = CONCAT44(uVar24 + iVar23,iVar23);
          lVar19 = *(long *)(param_1 + 0x108);
          do {
            uVar10 = uStack_68;
            for (lVar20 = *(long *)(lVar19 + 0x18); uStack_68 = uVar10, lVar19 + 8 != lVar20;
                lVar20 = *(long *)(lVar20 + 0x10)) {
              uVar24 = *(uint *)(lVar20 + 0x20);
              piVar16 = aiStack_e0;
              do {
                if ((uVar24 & 1) != 0) {
                  iVar12 = *piVar16;
                  lVar17 = *(long *)(param_1 + 0xe8);
                  *piVar16 = iVar12 + 1;
                  *(long *)(lVar17 + (long)iVar12 * 8) = lVar20;
                }
                uVar24 = uVar24 >> 1;
                piVar16 = piVar16 + 1;
              } while (uVar24 != 0);
              uVar10 = uStack_68;
            }
            lVar19 = *(long *)(lVar19 + 0x118);
          } while (lVar19 != *(long *)(param_1 + 0x108));
          **(long **)(param_1 + 0xf8) = *(long *)(param_1 + 0xe8) + (long)aiStack_e0[0] * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 8) =
               *(long *)(param_1 + 0xe8) + (long)aiStack_e0[1] * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x10) =
               *(long *)(param_1 + 0xe8) + (long)aiStack_e0[2] * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x18) =
               *(long *)(param_1 + 0xe8) + (long)aiStack_e0[3] * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x20) =
               *(long *)(param_1 + 0xe8) + (long)iStack_d0 * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x28) =
               *(long *)(param_1 + 0xe8) + (long)iStack_cc * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x30) =
               *(long *)(param_1 + 0xe8) + (long)iStack_c8 * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x38) =
               *(long *)(param_1 + 0xe8) + (long)iStack_c4 * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x40) =
               *(long *)(param_1 + 0xe8) + (long)iStack_c0 * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x48) =
               *(long *)(param_1 + 0xe8) + (long)iStack_bc * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x50) =
               *(long *)(param_1 + 0xe8) + (long)iStack_b8 * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x58) =
               *(long *)(param_1 + 0xe8) + (long)iStack_b4 * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x60) =
               *(long *)(param_1 + 0xe8) + (long)iStack_b0 * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x68) =
               *(long *)(param_1 + 0xe8) + (long)iStack_ac * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x70) =
               *(long *)(param_1 + 0xe8) + (long)iStack_a8 * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x78) =
               *(long *)(param_1 + 0xe8) + (long)iStack_a4 * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x80) =
               *(long *)(param_1 + 0xe8) + (long)iStack_a0 * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x88) =
               *(long *)(param_1 + 0xe8) + (long)iStack_9c * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x90) =
               *(long *)(param_1 + 0xe8) + (long)iStack_98 * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0x98) =
               *(long *)(param_1 + 0xe8) + (long)iStack_94 * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0xa0) =
               *(long *)(param_1 + 0xe8) + (long)(int)uStack_90 * 8;
          uStack_90._4_4_ = (int)((ulong)uStack_90 >> 0x20);
          *(long *)(*(long *)(param_1 + 0xf8) + 0xa8) =
               *(long *)(param_1 + 0xe8) + (long)uStack_90._4_4_ * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0xb0) =
               *(long *)(param_1 + 0xe8) + (long)(int)uStack_88 * 8;
          uStack_88._4_4_ = (int)((ulong)uStack_88 >> 0x20);
          *(long *)(*(long *)(param_1 + 0xf8) + 0xb8) =
               *(long *)(param_1 + 0xe8) + (long)uStack_88._4_4_ * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0xc0) =
               *(long *)(param_1 + 0xe8) + (long)(int)uStack_80 * 8;
          uStack_80._4_4_ = (int)((ulong)uStack_80 >> 0x20);
          *(long *)(*(long *)(param_1 + 0xf8) + 200) =
               *(long *)(param_1 + 0xe8) + (long)uStack_80._4_4_ * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0xd0) =
               *(long *)(param_1 + 0xe8) + (long)(int)uStack_78 * 8;
          uStack_78._4_4_ = (int)((ulong)uStack_78 >> 0x20);
          *(long *)(*(long *)(param_1 + 0xf8) + 0xd8) =
               *(long *)(param_1 + 0xe8) + (long)uStack_78._4_4_ * 8;
          *(long *)(*(long *)(param_1 + 0xf8) + 0xe0) =
               *(long *)(param_1 + 0xe8) + (long)(int)uStack_70 * 8;
          uStack_70._4_4_ = (int)((ulong)uStack_70 >> 0x20);
          *(long *)(*(long *)(param_1 + 0xf8) + 0xe8) =
               *(long *)(param_1 + 0xe8) + (long)uStack_70._4_4_ * 8;
          uStack_68._0_4_ = (int)uVar10;
          *(long *)(*(long *)(param_1 + 0xf8) + 0xf0) =
               *(long *)(param_1 + 0xe8) + (long)(int)uStack_68 * 8;
          uStack_68._4_4_ = (int)((ulong)uVar10 >> 0x20);
          *(long *)(*(long *)(param_1 + 0xf8) + 0xf8) =
               *(long *)(param_1 + 0xe8) + (long)uStack_68._4_4_ * 8;
          *(undefined8 *)(*(long *)(param_1 + 0xf8) + 0x100) = 0;
          lVar20 = *(long *)(param_1 + 0x108);
          lVar19 = *(long *)(lVar20 + 0x118);
          if (lVar19 != lVar20) {
            do {
              DataMemoryBarrier(2,3);
              *(undefined4 *)(lVar19 + 0xf98) = 0xffffffff;
              DataMemoryBarrier(2,3);
              piVar16 = (int *)(lVar19 + 0xf9c);
              if (0x14 < *(int *)(lVar19 + 0xf9c)) {
                do {
                  cVar8 = '\x01';
                  bVar9 = (bool)ExclusiveMonitorPass(piVar16,0x10);
                  if (bVar9) {
                    *piVar16 = *piVar16 + -1;
                    cVar8 = ExclusiveMonitorsStatus();
                  }
                } while (cVar8 != '\0');
                uVar11 = Aska::Semaphore::IsReady() const(lVar19 + 0xfd8);
                if ((uVar11 & 1) != 0) {
                  Aska::Semaphore::Signal() const(lVar19 + 0xfd8);
                }
              }
              lVar20 = *(long *)(lVar19 + 0x118);
              lVar19 = lVar20;
            } while (lVar20 != *(long *)(param_1 + 0x108));
          }
          DataMemoryBarrier(2,3);
          *(undefined4 *)(lVar20 + 0xf98) = 0xffffffff;
          DataMemoryBarrier(2,3);
          if (0x14 < *(int *)(lVar20 + 0xf9c)) {
            piVar16 = (int *)(lVar20 + 0xf9c);
            do {
              cVar8 = '\x01';
              bVar9 = (bool)ExclusiveMonitorPass(piVar16,0x10);
              if (bVar9) {
                *piVar16 = *piVar16 + -1;
                cVar8 = ExclusiveMonitorsStatus();
              }
            } while (cVar8 != '\0');
            uVar11 = Aska::Semaphore::IsReady() const(lVar20 + 0xfd8);
            if ((uVar11 & 1) != 0) {
              Aska::Semaphore::Signal() const(lVar20 + 0xfd8);
            }
          }
          return;
        }
        piVar16 = (int *)(lVar19 + 0xf98);
        iVar12 = 0;
code_r0x020816ac:
        if (*piVar16 == -1) {
          cVar8 = '\x01';
          bVar9 = (bool)ExclusiveMonitorPass(piVar16,0x10);
          if (bVar9) {
            *piVar16 = 0;
            cVar8 = ExclusiveMonitorsStatus();
          }
          if (cVar8 == '\0') goto code_r0x02081690;
          goto code_r0x020816ac;
        }
        ClearExclusiveLocal();
        bVar9 = iVar12 < 0x1ff;
        iVar12 = iVar12 + 1;
        if (bVar9) goto code_r0x020816ac;
        piVar3 = (int *)(lVar19 + 0xf9c);
        do {
          cVar8 = '\x01';
          bVar9 = (bool)ExclusiveMonitorPass(piVar3,0x10);
          if (bVar9) {
            *piVar3 = *piVar3 + 1;
            cVar8 = ExclusiveMonitorsStatus();
          }
        } while (cVar8 != '\0');
        do {
          if (*piVar16 != -1) {
            ClearExclusiveLocal();
            do {
              uVar11 = Aska::Semaphore::IsReady() const(lVar19 + 0xfd8);
              if ((uVar11 & 1) == 0) {
                do {
                  cVar8 = '\x01';
                  bVar9 = (bool)ExclusiveMonitorPass(piVar3,0x10);
                  if (bVar9) {
                    *piVar3 = *piVar3 + -1;
                    cVar8 = ExclusiveMonitorsStatus();
                  }
                } while (cVar8 != '\0');
                Aska::Thread::Sleep(unsigned int)(1);
              }
              else {
                Aska::Semaphore::Wait() const(lVar19 + 0xfd8);
              }
              do {
                cVar8 = '\x01';
                bVar9 = (bool)ExclusiveMonitorPass(piVar3,0x10);
                if (bVar9) {
                  *piVar3 = *piVar3 + 1;
                  cVar8 = ExclusiveMonitorsStatus();
                }
              } while (cVar8 != '\0');
              while (*piVar16 == -1) {
                cVar8 = '\x01';
                bVar9 = (bool)ExclusiveMonitorPass(piVar16,0x10);
                if (bVar9) {
                  *piVar16 = 0;
                  cVar8 = ExclusiveMonitorsStatus();
                }
                if (cVar8 == '\0') goto code_r0x02081764;
              }
              ClearExclusiveLocal();
            } while( true );
          }
          cVar8 = '\x01';
          bVar9 = (bool)ExclusiveMonitorPass(piVar16,0x10);
          if (bVar9) {
            *piVar16 = 0;
            cVar8 = ExclusiveMonitorsStatus();
          }
        } while (cVar8 != '\0');
code_r0x02081764:
        do {
          cVar8 = '\x01';
          bVar9 = (bool)ExclusiveMonitorPass(piVar3,0x10);
          if (bVar9) {
            *piVar3 = *piVar3 + -1;
            cVar8 = ExclusiveMonitorsStatus();
          }
        } while (cVar8 != '\0');
code_r0x02081690:
        DataMemoryBarrier(2,3);
        lVar19 = *(long *)(lVar19 + 0x118);
      } while( true );
    }
    cVar8 = '\x01';
    bVar9 = (bool)ExclusiveMonitorPass(piVar16,0x10);
    if (bVar9) {
      *piVar16 = 0;
      cVar8 = ExclusiveMonitorsStatus();
    }
    if (cVar8 == '\0') goto code_r0x02081684;
  } while( true );
}

// ==== Aska::TaskManager::Delete(Aska::Task*)
// vaddr 0x1f81dd4 | ghidra 0x2081dd4 | size 984 | symbol _ZN4Aska11TaskManager6DeleteEPNS_4TaskE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0208218c: Changing call to branch */

void _ZN4Aska11TaskManager6DeleteEPNS_4TaskE(long param_1,long *param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  int iVar5;
  uint uVar6;
  long lVar7;
  undefined8 *puVar8;
  int *piVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  
  if (param_2 == (long *)0x0) {
    return;
  }
  piVar9 = (int *)(param_1 + 0xf98);
  iVar5 = 0;
  do {
    while (*piVar9 == -1) {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
      if (bVar3) {
        *piVar9 = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
      if (cVar2 == '\0') goto code_r0x02081ebc;
    }
    ClearExclusiveLocal();
    bVar3 = iVar5 < 0x1ff;
    iVar5 = iVar5 + 1;
  } while (bVar3);
  piVar1 = (int *)(param_1 + 0xf9c);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if (*piVar9 != -1) {
      ClearExclusiveLocal();
      do {
        uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xfd8);
        if ((uVar4 & 1) == 0) {
          do {
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar3) {
              *piVar1 = *piVar1 + -1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0xfd8);
        }
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while (*piVar9 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
          if (bVar3) {
            *piVar9 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x02081eac;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar3) {
      *piVar9 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02081eac:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02081ebc:
  DataMemoryBarrier(2,3);
  if (param_2[3] != param_1) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0xf98) = 0xffffffff;
    DataMemoryBarrier(2,3);
    if (*(int *)(param_1 + 0xf9c) < 0x15) {
      return;
    }
    piVar9 = (int *)(param_1 + 0xf9c);
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
      if (bVar3) {
        *piVar9 = *piVar9 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xfd8);
    if ((uVar4 & 1) == 0) {
      return;
    }
    goto code_r0x011bd9c0;
  }
  uVar6 = *(uint *)(param_2 + 4);
  if (uVar6 != 0) {
    piVar9 = (int *)(param_1 + 0x50);
    do {
      if ((uVar6 & 1) != 0) {
        *piVar9 = *piVar9 + -1;
        *(int *)(param_1 + 0xd0) = *(int *)(param_1 + 0xd0) + -1;
      }
      uVar6 = uVar6 >> 1;
      piVar9 = piVar9 + 1;
    } while (uVar6 != 0);
  }
  lVar7 = *(long *)(param_1 + 0xe8);
  if (lVar7 == 0) {
    lVar7 = *(long *)(param_1 + 0x108);
    if (lVar7 != param_1) {
      iVar5 = *(int *)(lVar7 + 0xdc);
      lVar11 = (long)*(int *)(lVar7 + 0xd8) + 1;
      if ((int)lVar11 < iVar5) {
        lVar10 = *(long *)(lVar7 + 0xe8);
        uVar6 = (iVar5 + -2) - *(int *)(lVar7 + 0xd8);
        uVar4 = (ulong)uVar6 + 1;
        lVar7 = lVar11;
        if (3 < uVar4) {
          uVar6 = uVar6 + 1 & 3;
          lVar12 = uVar4 - uVar6;
          if (lVar12 != 0) {
            lVar7 = lVar12 + lVar11;
            puVar8 = (undefined8 *)(lVar10 + lVar11 * 8 + 0x10);
            do {
              if ((long *)puVar8[-2] == param_2) {
                puVar8[-2] = 0;
              }
              if ((long *)puVar8[-1] == param_2) {
                puVar8[-1] = 0;
              }
              if ((long *)*puVar8 == param_2) {
                *puVar8 = 0;
              }
              if ((long *)puVar8[1] == param_2) {
                puVar8[1] = 0;
              }
              lVar12 = lVar12 + -4;
              puVar8 = puVar8 + 4;
            } while (lVar12 != 0);
            if (uVar6 == 0) goto code_r0x02082108;
          }
        }
        puVar8 = (undefined8 *)(lVar10 + lVar7 * 8);
        iVar5 = iVar5 - (int)lVar7;
        do {
          if ((long *)*puVar8 == param_2) {
            *puVar8 = 0;
          }
          iVar5 = iVar5 + -1;
          puVar8 = puVar8 + 1;
        } while (iVar5 != 0);
      }
    }
  }
  else {
    iVar5 = *(int *)(param_1 + 0xdc);
    lVar11 = (long)*(int *)(param_1 + 0xd8) + 1;
    if ((int)lVar11 < iVar5) {
      uVar6 = (iVar5 + -2) - *(int *)(param_1 + 0xd8);
      uVar4 = (ulong)uVar6 + 1;
      lVar10 = lVar11;
      if (3 < uVar4) {
        uVar6 = uVar6 + 1 & 3;
        lVar12 = uVar4 - uVar6;
        if (lVar12 != 0) {
          lVar10 = lVar12 + lVar11;
          puVar8 = (undefined8 *)(lVar7 + lVar11 * 8 + 0x10);
          do {
            if ((long *)puVar8[-2] == param_2) {
              puVar8[-2] = 0;
            }
            if ((long *)puVar8[-1] == param_2) {
              puVar8[-1] = 0;
            }
            if ((long *)*puVar8 == param_2) {
              *puVar8 = 0;
            }
            if ((long *)puVar8[1] == param_2) {
              puVar8[1] = 0;
            }
            lVar12 = lVar12 + -4;
            puVar8 = puVar8 + 4;
          } while (lVar12 != 0);
          if (uVar6 == 0) goto code_r0x02082108;
        }
      }
      puVar8 = (undefined8 *)(lVar7 + lVar10 * 8);
      iVar5 = iVar5 - (int)lVar10;
      do {
        if ((long *)*puVar8 == param_2) {
          *puVar8 = 0;
        }
        iVar5 = iVar5 + -1;
        puVar8 = puVar8 + 1;
      } while (iVar5 != 0);
    }
  }
code_r0x02082108:
  if ((long *)(param_1 + 8) != param_2) {
    lVar7 = param_2[1];
    lVar11 = param_2[2];
    if (lVar7 != 0) {
      *(long *)(lVar7 + 0x10) = lVar11;
    }
    if (lVar11 != 0) {
      *(long *)(lVar11 + 8) = lVar7;
    }
    if (0 < *(int *)(param_1 + 0x20)) {
      *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + -1;
    }
    param_2[1] = 0;
    param_2[2] = 0;
  }
  param_2[3] = 0;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xf98) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0xf9c)) {
    piVar9 = (int *)(param_1 + 0xf9c);
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar9,0x10);
      if (bVar3) {
        *piVar9 = *piVar9 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    uVar4 = Aska::Semaphore::IsReady() const(param_1 + 0xfd8);
    if ((uVar4 & 1) != 0) {
code_r0x011bd9c0:
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0xfd8);
      return;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x020821a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_2 + 0x78))(param_2);
  return;
}

// ==== Aska::TaskThreadManager::Exit()
// vaddr 0x1f82568 | ghidra 0x2082568 | size 40 | symbol _ZN4Aska17TaskThreadManager4ExitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17TaskThreadManager4ExitEv(long param_1)

{
  if (*(long **)(param_1 + 0x18) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x18) + 8))();
    *(undefined8 *)(param_1 + 0x18) = 0;
  }
  return;
}

// ==== Aska::TDynamicQueue<Aska::TaskThreadManager*, true>::~TDynamicQueue()
// vaddr 0x1f82590 | ghidra 0x2082590 | size 56 | symbol _ZN4Aska13TDynamicQueueIPNS_17TaskThreadManagerELb1EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13TDynamicQueueIPNS_17TaskThreadManagerELb1EED2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueIPNS_17TaskThreadManagerELb1EEE_02cb83b8;
  *(undefined4 *)(param_1 + 2) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 1;
  if (param_1[3] != 0) {
    operator delete[](void*)();
    param_1[3] = 0;
  }
  return;
}

// ==== Aska::TaskThreadManager::RequestEndThread() const
// vaddr 0x1f83720 | ghidra 0x2083720 | size 28 | symbol _ZNK4Aska17TaskThreadManager16RequestEndThreadEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska17TaskThreadManager16RequestEndThreadEv(long param_1)

{
  *(byte *)(*(long *)(param_1 + 0x18) + 0x90) = *(byte *)(*(long *)(param_1 + 0x18) + 0x90) | 1;
  (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(*(long *)(param_1 + 0x18) + 0x28);
  return;
}

// ==== Aska::TaskThreadManager::Register(Aska::Task*, int)
// vaddr 0x1f8373c | ghidra 0x208373c | size 60 | symbol _ZN4Aska17TaskThreadManager8RegisterEPNS_4TaskEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17TaskThreadManager8RegisterEPNS_4TaskEi(long param_1,undefined8 param_2,uint param_3)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x18);
  *(undefined8 *)(lVar1 + 0x20) = param_2;
  Aska::Event::Set() const(lVar1 + 0x28);
  if (*(ushort *)(param_1 + 8) != param_3) {
    *(short *)(param_1 + 8) = (short)param_3;
  }
  return;
}

// ==== Aska::TaskThreadManager::Instantiate(Aska::MultiTaskManager*)
// vaddr 0x1f83778 | ghidra 0x2083778 | size 216 | symbol _ZN4Aska17TaskThreadManager11InstantiateEPNS_16MultiTaskManagerE | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska17TaskThreadManager11InstantiateEPNS_16MultiTaskManagerE(long param_1)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  
  plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80);
  puVar1 = PTR__ZTVN4Aska17TaskThreadManagerE_02cc23a0;
  if (plVar2 != (long *)0x0) {
    *(undefined2 *)(plVar2 + 1) = 0;
    plVar2[2] = param_1;
    *plVar2 = (long)(puVar1 + 0x10);
    plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x98,PTR__ZSt7nothrow_02cb9a80);
    if (plVar3 == (long *)0x0) {
      operator delete(void*)(plVar2);
      plVar2 = (long *)0x0;
    }
    else {
      Aska::Thread::Thread()(plVar3);
      puVar1 = PTR__ZTVN4Aska10TaskThreadE_02cbfa20;
      plVar3[4] = 0;
      *plVar3 = (long)(puVar1 + 0x10);
      Aska::Event::Event()(plVar3 + 5);
      *(undefined1 *)(plVar3 + 0x12) = 0;
      plVar3[3] = (long)plVar2;
      plVar3[4] = 0;
      *(undefined1 *)(plVar3 + 0x12) = 0;
      uVar4 = Aska::Event::Create(bool, bool)(plVar3 + 5,1,0);
      if ((uVar4 & 1) != 0) {
        Aska::Thread::Create(bool, int, int, bool)(plVar3,0,0x80,0x3000,1);
      }
      plVar2[3] = (long)plVar3;
    }
  }
  return plVar2;
}

// ==== Aska::TaskThread::Register(Aska::Task*)
// vaddr 0x1f83850 | ghidra 0x2083850 | size 16 | symbol _ZN4Aska10TaskThread8RegisterEPNS_4TaskE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TaskThread8RegisterEPNS_4TaskE(long param_1,undefined8 param_2)

{
  *(undefined8 *)(param_1 + 0x20) = param_2;
  (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(param_1 + 0x28);
  return;
}

// ==== Aska::TaskThread::Handler()
// vaddr 0x1f83860 | ghidra 0x2083860 | size 272 | symbol _ZN4Aska10TaskThread7HandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TaskThread7HandlerEv(long param_1)

{
  long lVar1;
  int iVar2;
  long lVar3;
  
  lVar3 = *(long *)(*(long *)(param_1 + 0x18) + 0x10);
  Aska::Event::Wait(unsigned int) const(param_1 + 0x28,0);
  lVar1 = lVar3 + 0x13f8;
  do {
    Aska::Semaphore::Wait() const(lVar1);
    if ((*(byte *)(param_1 + 0x90) >> 2 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar1);
      Aska::Semaphore::Wait() const(lVar1);
      *(byte *)(param_1 + 0x90) = *(byte *)(param_1 + 0x90) | 8;
      Aska::Semaphore::Signal() const(lVar1);
      (*(code *)PTR__ZN4Aska6Thread4ExitEv_02c97d18)();
      return;
    }
    if ((*(long *)(param_1 + 0x20) == 0) && ((*(byte *)(param_1 + 0x90) & 1) != 0)) {
code_r0x0208392c:
      *(byte *)(param_1 + 0x90) = *(byte *)(param_1 + 0x90) | 2;
    }
    else {
      Aska::Semaphore::Signal() const(lVar1);
      (**(code **)(**(long **)(param_1 + 0x20) + 0x68))
                (*(long **)(param_1 + 0x20),*(undefined2 *)(*(long *)(param_1 + 0x18) + 8));
      Aska::Semaphore::Wait() const(lVar1);
      *(undefined8 *)(param_1 + 0x20) = 0;
      if (*(uint *)(lVar3 + 0x1424) != *(uint *)(lVar3 + 0x1420)) {
        *(undefined8 *)(*(long *)(lVar3 + 0x1430) + (ulong)*(uint *)(lVar3 + 0x1420) * 8) =
             *(undefined8 *)(param_1 + 0x18);
        iVar2 = 0;
        if (*(int *)(lVar3 + 0x1420) + 1U < *(uint *)(lVar3 + 0x1428)) {
          iVar2 = *(int *)(lVar3 + 0x1420) + 1;
        }
        *(int *)(lVar3 + 0x1420) = iVar2;
      }
      if ((*(byte *)(param_1 + 0x90) & 1) != 0) goto code_r0x0208392c;
    }
    Aska::Semaphore::Signal() const(lVar1);
    Aska::Event::Wait(unsigned int) const(param_1 + 0x28,0);
  } while( true );
}

// ==== Aska::TaskThread::Init()
// vaddr 0x1f83970 | ghidra 0x2083970 | size 88 | symbol _ZN4Aska10TaskThread4InitEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska10TaskThread4InitEv(long param_1)

{
  bool bVar1;
  ulong uVar2;
  
  *(undefined1 *)(param_1 + 0x90) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  uVar2 = Aska::Event::Create(bool, bool)(param_1 + 0x28,1,0);
  bVar1 = (uVar2 & 1) != 0;
  if (bVar1) {
    Aska::Thread::Create(bool, int, int, bool)(param_1,0,0x80,0x3000,1);
  }
  return bVar1;
}

// ==== Aska::TaskThread::Exit()
// vaddr 0x1f839c8 | ghidra 0x20839c8 | size 40 | symbol _ZN4Aska10TaskThread4ExitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TaskThread4ExitEv(long param_1)

{
  *(byte *)(param_1 + 0x90) = *(byte *)(param_1 + 0x90) | 4;
  Aska::Event::Set() const(param_1 + 0x28);
  (*(code *)PTR__ZN4Aska6Thread7WaitEndEv_02c98108)(param_1);
  return;
}

// ==== Aska::TaskThread::Instantiate(Aska::TaskThreadManager*)
// vaddr 0x1f839f0 | ghidra 0x20839f0 | size 148 | symbol _ZN4Aska10TaskThread11InstantiateEPNS_17TaskThreadManagerE | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska10TaskThread11InstantiateEPNS_17TaskThreadManagerE(long param_1)

{
  undefined *puVar1;
  long *plVar2;
  ulong uVar3;
  
  plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x98,PTR__ZSt7nothrow_02cb9a80);
  if (plVar2 != (long *)0x0) {
    Aska::Thread::Thread()(plVar2);
    puVar1 = PTR__ZTVN4Aska10TaskThreadE_02cbfa20;
    plVar2[4] = 0;
    *plVar2 = (long)(puVar1 + 0x10);
    Aska::Event::Event()(plVar2 + 5);
    *(undefined1 *)(plVar2 + 0x12) = 0;
    plVar2[3] = param_1;
    plVar2[4] = 0;
    *(undefined1 *)(plVar2 + 0x12) = 0;
    uVar3 = Aska::Event::Create(bool, bool)(plVar2 + 5,1,0);
    if ((uVar3 & 1) != 0) {
      Aska::Thread::Create(bool, int, int, bool)(plVar2,0,0x80,0x3000,1);
    }
  }
  return plVar2;
}

// ==== Aska::TaskThread::~TaskThread()
// vaddr 0x1f83a84 | ghidra 0x2083a84 | size 84 | symbol _ZN4Aska10TaskThreadD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TaskThreadD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska10TaskThreadE_02cbfa20 + 0x10);
  *(byte *)(param_1 + 0x12) = *(byte *)(param_1 + 0x12) | 4;
  Aska::Event::Set() const(param_1 + 5);
  Aska::Thread::WaitEnd()(param_1);
  Aska::Event::Exit()(param_1 + 5);
  (*(code *)PTR__ZN4Aska6ThreadD1Ev_02c9be08)(param_1);
  return;
}

// ==== Aska::TaskThread::~TaskThread()
// vaddr 0x1f83ad8 | ghidra 0x2083ad8 | size 92 | symbol _ZN4Aska10TaskThreadD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10TaskThreadD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska10TaskThreadE_02cbfa20 + 0x10);
  *(byte *)(param_1 + 0x12) = *(byte *)(param_1 + 0x12) | 4;
  Aska::Event::Set() const(param_1 + 5);
  Aska::Thread::WaitEnd()(param_1);
  Aska::Event::Exit()(param_1 + 5);
  Aska::Thread::~Thread()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TaskManager::GetClassID(int) const
// vaddr 0x1f83b34 | ghidra 0x2083b34 | size 64 | symbol _ZNK4Aska11TaskManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska11TaskManager10GetClassIDEi(undefined8 param_1,int param_2)

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
  return 0xf002f003;
}

// ==== Aska::TaskManager::GetThisType() const
// vaddr 0x1f83b74 | ghidra 0x2083b74 | size 8 | symbol _ZNK4Aska11TaskManager11GetThisTypeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska11TaskManager11GetThisTypeEv(void)

{
  return 0;
}

// ==== Aska::TaskManager::Delete(Aska::LinkElement*)
// vaddr 0x1f83b7c | ghidra 0x2083b7c | size 4 | symbol _ZN4Aska11TaskManager6DeleteEPNS_11LinkElementE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TaskManager6DeleteEPNS_11LinkElementE(void)

{
  return;
}

// ==== non-virtual thunk to Aska::TaskManager::GetClassID(int) const
// vaddr 0x1f83b80 | ghidra 0x2083b80 | size 64 | symbol _ZThn40_NK4Aska11TaskManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZThn40_NK4Aska11TaskManager10GetClassIDEi(undefined8 param_1,int param_2)

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
  return 0xf002f003;
}

// ==== Aska::TaskThreadManager::~TaskThreadManager()
// vaddr 0x1f83cc0 | ghidra 0x2083cc0 | size 4 | symbol _ZN4Aska17TaskThreadManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17TaskThreadManagerD2Ev(void)

{
  return;
}

// ==== Aska::TaskThreadManager::~TaskThreadManager()
// vaddr 0x1f83cc4 | ghidra 0x2083cc4 | size 4 | symbol _ZN4Aska17TaskThreadManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska17TaskThreadManagerD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::TDynamicQueue<Aska::TaskThreadManager*, true>::~TDynamicQueue()
// vaddr 0x1f83cc8 | ghidra 0x2083cc8 | size 56 | symbol _ZN4Aska13TDynamicQueueIPNS_17TaskThreadManagerELb1EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13TDynamicQueueIPNS_17TaskThreadManagerELb1EED0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska13TDynamicQueueIPNS_17TaskThreadManagerELb1EEE_02cb83b8;
  *(undefined4 *)(param_1 + 2) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 1;
  if (param_1[3] != 0) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}


// FAILED to create function at 029724f0 typeinfo name for Aska::TaskThread
// FAILED to create function at 029725b0 typeinfo name for Aska::TaskThreadManager
// FAILED to create function at 029725d0 typeinfo name for Aska::TDynamicQueue<Aska::TaskThreadManager*, true>
// FAILED to create function at 02bb3238 Aska::AnimatableLinkElement::vtable
// FAILED to create function at 02bb3280 Aska::AnimatableLinkElement::typeinfo
// FAILED to create function at 02bb4228 Aska::Task::vtable
// FAILED to create function at 02bb42d0 Aska::Task::typeinfo
// FAILED to create function at 02bb42e8 Aska::TaskManager::vtable
// FAILED to create function at 02bb4560 Aska::TaskThread::vtable
// FAILED to create function at 02bb4590 Aska::TaskThread::typeinfo
// FAILED to create function at 02bb45b0 Aska::TaskManager::typeinfo
// FAILED to create function at 02bb4678 Aska::TaskThreadManager::vtable
// FAILED to create function at 02bb4698 Aska::TaskThreadManager::typeinfo
// FAILED to create function at 02bb46a8 Aska::TDynamicQueue<Aska::TaskThreadManager*,true>::vtable
// FAILED to create function at 02bb46c8 Aska::TDynamicQueue<Aska::TaskThreadManager*,true>::typeinfo
