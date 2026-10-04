// port/decomp/containers/object_container.c: Ghidra decompiles for the containers subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:20 UTC: tools/decomp.sh '--into' 'containers/object_container' 'TObjectContainer<Framework::CSound::CElement>::' 'TObjectContainer<Collision::CollisionShapeGroup>::' 'TObjectContainer<BehaviorQueue\*>::'

// ==== Framework::TObjectContainer<Collision::CollisionShapeGroup>::Initialize(unsigned long)
// vaddr 0x11e223c | ghidra 0x12e223c | size 188 | symbol _ZN9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEE10InitializeEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEE10InitializeEm
               (long param_1,ulong param_2)

{
  undefined1 auVar1 [16];
  long lVar2;
  long lVar3;
  long lVar4;
  
  if (*(long *)(param_1 + 0x10) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ee245/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TObjectContainer.h"*/,0x25,&UNK_027ee2b4/*"m_pElements isn't null.(%08x)"*/);
  }
  auVar1._8_8_ = 0;
  auVar1._0_8_ = param_2;
  *(ulong *)(param_1 + 8) = param_2;
  lVar2 = param_2 * 0x90 + 0x10;
  if (SUB168(auVar1 * ZEXT816(0x90),8) != 0 || 0xffffffffffffffef < param_2 * 0x90) {
    lVar2 = -1;
  }
  lVar2 = operator new[](unsigned long, std::nothrow_t const&)(lVar2,PTR__ZSt7nothrow_02cb9a80);
  if (lVar2 == 0) {
    lVar3 = 0;
  }
  else {
    lVar3 = lVar2 + 0x10;
    *(ulong *)(lVar2 + 8) = param_2;
    if (param_2 != 0) {
      lVar4 = param_2 * 0x90;
      lVar2 = lVar3;
      do {
        Collision::CollisionShapeGroup::CollisionShapeGroup()(lVar2);
        lVar4 = lVar4 + -0x90;
        lVar2 = lVar2 + 0x90;
      } while (lVar4 != 0);
    }
  }
  *(long *)(param_1 + 0x10) = lVar3;
  return;
}

// ==== Framework::TObjectContainer<Collision::CollisionShapeGroup>::Reset()
// vaddr 0x11e22f8 | ghidra 0x12e22f8 | size 4 | symbol _ZN9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEE5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEE5ResetEv(void)

{
  return;
}

// ==== Framework::TObjectContainer<Collision::CollisionShapeGroup>::NumElements() const
// vaddr 0x11e22fc | ghidra 0x12e22fc | size 52 | symbol _ZNK9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEE11NumElementsEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEE11NumElementsEv(long param_1)

{
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ee245/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TObjectContainer.h"*/,0x3e,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  return *(undefined8 *)(param_1 + 8);
}

// ==== Framework::TObjectContainer<Collision::CollisionShapeGroup>::rElement(unsigned long)
// vaddr 0x11e2330 | ghidra 0x12e2330 | size 144 | symbol _ZN9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEE8rElementEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEE8rElementEm
               (long *param_1,ulong param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if (param_1[2] == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ee245/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TObjectContainer.h"*/,0x44,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
  if (uVar1 <= param_2) {
    uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ee245/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TObjectContainer.h"*/,0x45,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,uVar2);
  }
  return param_1[2] + param_2 * 0x90;
}

// ==== Framework::TObjectContainer<Collision::CollisionShapeGroup>::crElement(unsigned long) const
// vaddr 0x11e23c0 | ghidra 0x12e23c0 | size 144 | symbol _ZNK9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEE9crElementEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEE9crElementEm
               (long *param_1,ulong param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if (param_1[2] == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ee245/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TObjectContainer.h"*/,0x4b,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
  if (uVar1 <= param_2) {
    uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ee245/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TObjectContainer.h"*/,0x4c,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,uVar2);
  }
  return param_1[2] + param_2 * 0x90;
}

// ==== Framework::TObjectContainer<Collision::CollisionShapeGroup>::~TObjectContainer()
// vaddr 0x11e2450 | ghidra 0x12e2450 | size 280 | symbol _ZN9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEED2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  long *plVar4;
  long *plVar5;
  long *plVar6;
  long *plVar7;
  
  plVar4 = (long *)param_1[2];
  *param_1 = (long)(
                   PTR__ZTVN9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEEE_02cbefe0
                   + 0x10);
  if (plVar4 != (long *)0x0) {
    if (plVar4[-1] != 0) {
      puVar1 = PTR__ZTVN9Collision19CollisionShapeGroupE_02cb8078 + 0x10;
      plVar6 = plVar4 + plVar4[-1] * 0x12;
      do {
        plVar5 = plVar6 + -0x12;
        *plVar5 = (long)puVar1;
        plVar3 = (long *)plVar6[-0x11];
        plVar2 = (long *)plVar6[-0x10];
        plVar7 = plVar3;
        if (plVar3 != plVar2) {
          do {
            if ((long *)*plVar3 != (long *)0x0) {
              (**(code **)(*(long *)*plVar3 + 8))();
              *plVar3 = 0;
            }
            plVar3 = plVar3 + 1;
          } while (plVar2 != plVar3);
          plVar3 = (long *)plVar6[-0x11];
          plVar2 = (long *)plVar6[-0x10];
          plVar7 = plVar3;
          if (plVar2 != plVar3) {
            plVar7 = (long *)((long)plVar2 +
                             (~((long)plVar2 + (-8 - (long)plVar3)) & 0xfffffffffffffff8U));
            plVar6[-0x10] = (long)plVar7;
          }
        }
        *(undefined2 *)(plVar6 + -0xd) = 0;
        plVar6[-0xe] = 0;
        if (plVar3 != (long *)0x0) {
          if (plVar7 != plVar3) {
            plVar6[-0x10] =
                 (long)plVar7 + (~((long)plVar7 + (-8 - (long)plVar3)) & 0xfffffffffffffff8U);
          }
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
        }
        plVar6 = plVar5;
      } while (plVar5 != plVar4);
    }
    operator delete[](void*)(plVar4 + -2);
    param_1[2] = 0;
  }
  return;
}

// ==== Framework::TObjectContainer<Collision::CollisionShapeGroup>::~TObjectContainer()
// vaddr 0x11e2568 | ghidra 0x12e2568 | size 24 | symbol _ZN9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEED0Ev(undefined8 param_1)

{
  Framework::TObjectContainer<Collision::CollisionShapeGroup>::~TObjectContainer()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::TObjectContainer<BehaviorQueue*>::Initialize(unsigned long)
// vaddr 0x123dd94 | ghidra 0x133dd94 | size 100 | symbol _ZN9Framework16TObjectContainerIP13BehaviorQueueE10InitializeEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16TObjectContainerIP13BehaviorQueueE10InitializeEm(long param_1,ulong param_2)

{
  undefined1 auVar1 [16];
  undefined8 uVar2;
  long lVar3;
  
  if (*(long *)(param_1 + 0x10) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ee245/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TObjectContainer.h"*/,0x25,&UNK_027ee2b4/*"m_pElements isn't null.(%08x)"*/);
  }
  *(ulong *)(param_1 + 8) = param_2;
  auVar1._8_8_ = 0;
  auVar1._0_8_ = param_2;
  lVar3 = param_2 << 3;
  if (SUB168(auVar1 * ZEXT816(8),8) != 0) {
    lVar3 = -1;
  }
  uVar2 = operator new[](unsigned long, std::nothrow_t const&)(lVar3,PTR__ZSt7nothrow_02cb9a80);
  *(undefined8 *)(param_1 + 0x10) = uVar2;
  return;
}

// ==== Framework::TObjectContainer<BehaviorQueue*>::Reset()
// vaddr 0x123ed24 | ghidra 0x133ed24 | size 4 | symbol _ZN9Framework16TObjectContainerIP13BehaviorQueueE5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16TObjectContainerIP13BehaviorQueueE5ResetEv(void)

{
  return;
}

// ==== Framework::TObjectContainer<BehaviorQueue*>::NumElements() const
// vaddr 0x123ed28 | ghidra 0x133ed28 | size 52 | symbol _ZNK9Framework16TObjectContainerIP13BehaviorQueueE11NumElementsEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework16TObjectContainerIP13BehaviorQueueE11NumElementsEv(long param_1)

{
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ee245/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TObjectContainer.h"*/,0x3e,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  return *(undefined8 *)(param_1 + 8);
}

// ==== Framework::TObjectContainer<BehaviorQueue*>::rElement(unsigned long)
// vaddr 0x123ed5c | ghidra 0x133ed5c | size 140 | symbol _ZN9Framework16TObjectContainerIP13BehaviorQueueE8rElementEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework16TObjectContainerIP13BehaviorQueueE8rElementEm(long *param_1,ulong param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if (param_1[2] == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ee245/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TObjectContainer.h"*/,0x44,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
  if (uVar1 <= param_2) {
    uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ee245/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TObjectContainer.h"*/,0x45,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,uVar2);
  }
  return param_1[2] + param_2 * 8;
}

// ==== Framework::TObjectContainer<BehaviorQueue*>::crElement(unsigned long) const
// vaddr 0x123ede8 | ghidra 0x133ede8 | size 140 | symbol _ZNK9Framework16TObjectContainerIP13BehaviorQueueE9crElementEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework16TObjectContainerIP13BehaviorQueueE9crElementEm(long *param_1,ulong param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if (param_1[2] == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ee245/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TObjectContainer.h"*/,0x4b,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
  if (uVar1 <= param_2) {
    uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ee245/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TObjectContainer.h"*/,0x4c,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,uVar2);
  }
  return param_1[2] + param_2 * 8;
}

// ==== Framework::TObjectContainer<BehaviorQueue*>::~TObjectContainer()
// vaddr 0x123ee74 | ghidra 0x133ee74 | size 48 | symbol _ZN9Framework16TObjectContainerIP13BehaviorQueueED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16TObjectContainerIP13BehaviorQueueED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework16TObjectContainerIP13BehaviorQueueEE_02cc2678 + 0x10);
  if (param_1[2] != 0) {
    operator delete[](void*)();
    param_1[2] = 0;
  }
  return;
}

// ==== Framework::TObjectContainer<BehaviorQueue*>::~TObjectContainer()
// vaddr 0x123eea4 | ghidra 0x133eea4 | size 48 | symbol _ZN9Framework16TObjectContainerIP13BehaviorQueueED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16TObjectContainerIP13BehaviorQueueED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework16TObjectContainerIP13BehaviorQueueEE_02cc2678 + 0x10);
  if (param_1[2] != 0) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::TObjectContainer<Framework::CSound::CElement>::~TObjectContainer()
// vaddr 0x1e9aacc | ghidra 0x1f9aacc | size 176 | symbol _ZN9Framework16TObjectContainerINS_6CSound8CElementEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16TObjectContainerINS_6CSound8CElementEED2Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  
  lVar5 = param_1[2];
  *param_1 = (long)(PTR__ZTVN9Framework16TObjectContainerINS_6CSound8CElementEEE_02cc3758 + 0x10);
  if (lVar5 != 0) {
    lVar4 = *(long *)(lVar5 + -8);
    if (lVar4 != 0) {
      lVar4 = lVar4 * 0x70;
      puVar1 = PTR__ZTVN9Framework6CSound8CElementE_02cc3c98 + 0x10;
      do {
        lVar2 = lVar5 + lVar4;
        *(undefined **)(lVar2 + -0x70) = puVar1;
        if (*(long **)(lVar2 + -0x60) != (long *)0x0) {
          (**(code **)(**(long **)(lVar2 + -0x60) + 0x38))();
          *(undefined8 *)(lVar2 + -0x60) = 0;
        }
        plVar3 = *(long **)(lVar2 + -0x50);
        if (plVar3 != (long *)0x0) {
          (**(code **)(*plVar3 + 0x38))(plVar3,0);
          *(undefined8 *)(lVar2 + -0x50) = 0;
        }
        lVar4 = lVar4 + -0x70;
      } while (lVar4 != 0);
    }
    operator delete[](void*)((long *)(lVar5 + -8));
    param_1[2] = 0;
  }
  return;
}

// ==== Framework::TObjectContainer<Framework::CSound::CElement>::~TObjectContainer()
// vaddr 0x1e9ab7c | ghidra 0x1f9ab7c | size 176 | symbol _ZN9Framework16TObjectContainerINS_6CSound8CElementEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16TObjectContainerINS_6CSound8CElementEED0Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  
  lVar5 = param_1[2];
  *param_1 = (long)(PTR__ZTVN9Framework16TObjectContainerINS_6CSound8CElementEEE_02cc3758 + 0x10);
  if (lVar5 != 0) {
    lVar4 = *(long *)(lVar5 + -8);
    if (lVar4 != 0) {
      lVar4 = lVar4 * 0x70;
      puVar1 = PTR__ZTVN9Framework6CSound8CElementE_02cc3c98 + 0x10;
      do {
        lVar2 = lVar5 + lVar4;
        *(undefined **)(lVar2 + -0x70) = puVar1;
        if (*(long **)(lVar2 + -0x60) != (long *)0x0) {
          (**(code **)(**(long **)(lVar2 + -0x60) + 0x38))();
          *(undefined8 *)(lVar2 + -0x60) = 0;
        }
        plVar3 = *(long **)(lVar2 + -0x50);
        if (plVar3 != (long *)0x0) {
          (**(code **)(*plVar3 + 0x38))(plVar3,0);
          *(undefined8 *)(lVar2 + -0x50) = 0;
        }
        lVar4 = lVar4 + -0x70;
      } while (lVar4 != 0);
    }
    operator delete[](void*)((long *)(lVar5 + -8));
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::TObjectContainer<Framework::CSound::CElement>::Initialize(unsigned long)
// vaddr 0x1e9ac2c | ghidra 0x1f9ac2c | size 180 | symbol _ZN9Framework16TObjectContainerINS_6CSound8CElementEE10InitializeEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16TObjectContainerINS_6CSound8CElementEE10InitializeEm(long param_1,ulong param_2)

{
  long lVar1;
  undefined *puVar2;
  undefined1 auVar3 [16];
  ulong *puVar4;
  ulong *puVar5;
  
  if (*(long *)(param_1 + 0x10) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x25,&UNK_027ee2b4/*"m_pElements isn't null.(%08x)"*/);
  }
  auVar3._8_8_ = 0;
  auVar3._0_8_ = param_2;
  *(ulong *)(param_1 + 8) = param_2;
  lVar1 = param_2 * 0x70 + 8;
  if (SUB168(auVar3 * ZEXT816(0x70),8) != 0 || 0xfffffffffffffff7 < param_2 * 0x70) {
    lVar1 = -1;
  }
  puVar4 = (ulong *)operator new[](unsigned long, std::nothrow_t const&)(lVar1,PTR__ZSt7nothrow_02cb9a80);
  puVar5 = puVar4;
  if (puVar4 != (ulong *)0x0) {
    puVar5 = puVar4 + 1;
    *puVar4 = param_2;
    if (param_2 != 0) {
      puVar2 = PTR__ZTVN9Framework6CSound8CElementE_02cc3c98 + 0x10;
      puVar4 = puVar5;
      do {
        *puVar4 = (ulong)puVar2;
        puVar4[2] = 0;
        puVar4[4] = 0;
        puVar4 = puVar4 + 0xe;
      } while (puVar4 != puVar5 + param_2 * 0xe);
    }
  }
  *(ulong **)(param_1 + 0x10) = puVar5;
  return;
}

// ==== Framework::TObjectContainer<Framework::CSound::CElement>::Reset()
// vaddr 0x1e9ace0 | ghidra 0x1f9ace0 | size 4 | symbol _ZN9Framework16TObjectContainerINS_6CSound8CElementEE5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16TObjectContainerINS_6CSound8CElementEE5ResetEv(void)

{
  return;
}

// ==== Framework::TObjectContainer<Framework::CSound::CElement>::NumElements() const
// vaddr 0x1e9ace4 | ghidra 0x1f9ace4 | size 52 | symbol _ZNK9Framework16TObjectContainerINS_6CSound8CElementEE11NumElementsEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework16TObjectContainerINS_6CSound8CElementEE11NumElementsEv(long param_1)

{
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x3e,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  return *(undefined8 *)(param_1 + 8);
}

// ==== Framework::TObjectContainer<Framework::CSound::CElement>::rElement(unsigned long)
// vaddr 0x1e9ad18 | ghidra 0x1f9ad18 | size 144 | symbol _ZN9Framework16TObjectContainerINS_6CSound8CElementEE8rElementEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework16TObjectContainerINS_6CSound8CElementEE8rElementEm(long *param_1,ulong param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if (param_1[2] == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x44,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
  if (uVar1 <= param_2) {
    uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x45,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,uVar2);
  }
  return param_1[2] + param_2 * 0x70;
}

// ==== Framework::TObjectContainer<Framework::CSound::CElement>::crElement(unsigned long) const
// vaddr 0x1e9ada8 | ghidra 0x1f9ada8 | size 144 | symbol _ZNK9Framework16TObjectContainerINS_6CSound8CElementEE9crElementEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework16TObjectContainerINS_6CSound8CElementEE9crElementEm(long *param_1,ulong param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if (param_1[2] == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x4b,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  uVar1 = (**(code **)(*param_1 + 0x20))(param_1);
  if (uVar1 <= param_2) {
    uVar2 = (**(code **)(*param_1 + 0x20))(param_1);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02965e66/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TObjectContainer.h"*/,0x4c,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,uVar2);
  }
  return param_1[2] + param_2 * 0x70;
}


// FAILED to create function at 02aa6568 Framework::TObjectContainer<Collision::CollisionShapeGroup>::typeinfo
// FAILED to create function at 02aa65c8 Framework::TObjectContainer<Collision::CollisionShapeGroup>::vtable
// FAILED to create function at 02aafc48 Framework::TObjectContainer<BehaviorQueue*>::typeinfo
// FAILED to create function at 02aafca8 Framework::TObjectContainer<BehaviorQueue*>::vtable
// FAILED to create function at 02bab088 Framework::TObjectContainer<Framework::CSound::CElement>::vtable
// FAILED to create function at 02bab0d0 Framework::TObjectContainer<Framework::CSound::CElement>::typeinfo
