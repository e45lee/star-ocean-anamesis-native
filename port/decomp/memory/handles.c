// port/decomp/memory/handles.c: Ghidra decompiles for the memory subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:04 UTC: tools/decomp.sh '--into' 'memory/handles' 'Aska::MemoryHandleManager::' 'Framework::CHandleManager' 'Aska::MemoryPool'

// ==== Framework::CHandleManager_Base::MountAdditionalInformation(unsigned int, unsigned int)
// vaddr 0x1e845b4 | ghidra 0x1f845b4 | size 12 | symbol _ZN9Framework19CHandleManager_Base26MountAdditionalInformationEjj | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN9Framework19CHandleManager_Base26MountAdditionalInformationEjj(ulong param_1,long param_2)

{
  return param_1 & 0xffffffff | param_2 << 0x20;
}

// ==== Framework::CHandleManager_Base::UnmountAdditionalInformation(unsigned long)
// vaddr 0x1e845c0 | ghidra 0x1f845c0 | size 8 | symbol _ZN9Framework19CHandleManager_Base28UnmountAdditionalInformationEm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN9Framework19CHandleManager_Base28UnmountAdditionalInformationEm(ulong param_1)

{
  return param_1 >> 0x20;
}

// ==== Framework::CHandleManager_Base::UnmountHandleValue(unsigned long)
// vaddr 0x1e845c8 | ghidra 0x1f845c8 | size 4 | symbol _ZN9Framework19CHandleManager_Base18UnmountHandleValueEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework19CHandleManager_Base18UnmountHandleValueEm(void)

{
  return;
}

// ==== Framework::CHandleManager_Base::MountAdditionalInformationBySelf(unsigned int) const
// vaddr 0x1e845cc | ghidra 0x1f845cc | size 72 | symbol _ZNK9Framework19CHandleManager_Base32MountAdditionalInformationBySelfEj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK9Framework19CHandleManager_Base32MountAdditionalInformationBySelfEj
          (long param_1,undefined4 param_2)

{
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0x33,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  return CONCAT44(*(undefined4 *)(param_1 + 8),param_2);
}

// ==== Framework::CHandleManager_Base::CHandleManager_Base()
// vaddr 0x1e84614 | ghidra 0x1f84614 | size 24 | symbol _ZN9Framework19CHandleManager_BaseC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework19CHandleManager_BaseC2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework19CHandleManager_BaseE_02cb7f48;
  param_1[2] = 0;
  param_1[3] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  return;
}

// ==== Framework::CHandleManager_Base::~CHandleManager_Base()
// vaddr 0x1e8462c | ghidra 0x1f8462c | size 128 | symbol _ZN9Framework19CHandleManager_BaseD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework19CHandleManager_BaseD1Ev(long *param_1)

{
  ulong uVar1;
  
  *param_1 = (long)(PTR__ZTVN9Framework19CHandleManager_BaseE_02cb7f48 + 0x10);
  if ((long *)param_1[3] != (long *)0x0) {
    uVar1 = (**(code **)(*(long *)param_1[3] + 0x10))();
    if ((uVar1 & 1) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0x96,&UNK_02963da3/*"Mutex locked."*/);
    }
    if ((long *)param_1[3] != (long *)0x0) {
      (**(code **)(*(long *)param_1[3] + 8))();
    }
    param_1[3] = 0;
  }
  if ((long *)param_1[2] != (long *)0x0) {
    (**(code **)(*(long *)param_1[2] + 8))();
    param_1[2] = 0;
  }
  return;
}

// ==== Framework::CHandleManager_Base::Release()
// vaddr 0x1e846ac | ghidra 0x1f846ac | size 112 | symbol _ZN9Framework19CHandleManager_Base7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework19CHandleManager_Base7ReleaseEv(long param_1)

{
  ulong uVar1;
  
  if (*(long **)(param_1 + 0x18) != (long *)0x0) {
    uVar1 = (**(code **)(**(long **)(param_1 + 0x18) + 0x10))();
    if ((uVar1 & 1) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0x96,&UNK_02963da3/*"Mutex locked."*/);
    }
    if (*(long **)(param_1 + 0x18) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x18) + 8))();
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
  }
  if (*(long **)(param_1 + 0x10) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x10) + 8))();
    *(undefined8 *)(param_1 + 0x10) = 0;
  }
  return;
}

// ==== Framework::CHandleManager_Base::~CHandleManager_Base()
// vaddr 0x1e8471c | ghidra 0x1f8471c | size 128 | symbol _ZN9Framework19CHandleManager_BaseD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework19CHandleManager_BaseD0Ev(long *param_1)

{
  ulong uVar1;
  
  *param_1 = (long)(PTR__ZTVN9Framework19CHandleManager_BaseE_02cb7f48 + 0x10);
  if ((long *)param_1[3] != (long *)0x0) {
    uVar1 = (**(code **)(*(long *)param_1[3] + 0x10))();
    if ((uVar1 & 1) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0x96,&UNK_02963da3/*"Mutex locked."*/);
    }
    if ((long *)param_1[3] != (long *)0x0) {
      (**(code **)(*(long *)param_1[3] + 8))();
    }
    param_1[3] = 0;
  }
  if ((long *)param_1[2] != (long *)0x0) {
    (**(code **)(*(long *)param_1[2] + 8))();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CHandleManager_Base::Initialize(unsigned int, unsigned int, unsigned int)
// vaddr 0x1e8479c | ghidra 0x1f8479c | size 452 | symbol _ZN9Framework19CHandleManager_Base10InitializeEjjj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework19CHandleManager_Base10InitializeEjjj
               (long param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  ulong uVar2;
  int iVar3;
  uint uVar4;
  undefined *puVar5;
  long *plVar6;
  undefined1 *puVar7;
  ulong uVar8;
  undefined1 *puVar9;
  ulong uVar11;
  ulong uVar12;
  undefined1 *puVar10;
  
  if (*(long *)(param_1 + 0x10) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0x56,&UNK_027ee2b4/*"m_pElements isn't null.(%08x)"*/);
  }
  if (*(long *)(param_1 + 0x18) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0x57,&UNK_02963d3d/*"m_pMutex isn't null.(%08x)"*/);
  }
  puVar5 = PTR__ZN9Framework19CHandleManager_Base21gInstanceUniqueNumberE_02cc02b0;
  iVar3 = *(int *)PTR__ZN9Framework19CHandleManager_Base21gInstanceUniqueNumberE_02cc02b0;
  iVar1 = iVar3 + 1;
  *(int *)PTR__ZN9Framework19CHandleManager_Base21gInstanceUniqueNumberE_02cc02b0 = iVar1;
  *(int *)(param_1 + 8) = iVar3;
  if (iVar1 == 0) {
    *(undefined4 *)puVar5 = 1;
  }
  uVar2 = 2;
  do {
    uVar8 = uVar2;
    uVar4 = (int)uVar8 << 1;
    uVar2 = (ulong)uVar4;
  } while (uVar4 < param_2);
  plVar6 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
  puVar5 = 
  PTR__ZTVN4Aska8THashMapIjmNS_7THasherIjEENS_8TEqualToIjEENS_10TAllocatorINS_5TPairIKjmEEEEEE_02cbcdd8
  ;
  if (plVar6 != (long *)0x0) {
    *(undefined8 *)((long)plVar6 + 0xc) = 0x3f400000;
    *(undefined4 *)((long)plVar6 + 0x14) = 0;
    *plVar6 = (long)(puVar5 + 0x10);
    puVar7 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(uVar8 * 0x18,8);
    if (puVar7 == (undefined1 *)0x0) {
      uVar8 = 0;
    }
    plVar6[4] = (long)puVar7;
    plVar6[5] = uVar8;
    if (uVar8 != 0) {
      uVar2 = (uVar8 * 0x18 - 0x18) / 0x18 + 1;
      puVar10 = puVar7;
      if ((1 < uVar2) && (uVar11 = uVar2 & 0x1ffffffffffffffe, uVar11 != 0)) {
        uVar12 = uVar11;
        do {
          *puVar10 = 0;
          puVar10[0x18] = 0;
          uVar12 = uVar12 - 2;
          puVar10 = puVar10 + 0x30;
        } while (uVar12 != 0);
        puVar10 = puVar7 + uVar11 * 0x18;
        if (uVar2 == uVar11) goto code_r0x01f84908;
      }
      do {
        puVar9 = puVar10 + 0x18;
        *puVar10 = 0;
        puVar10 = puVar9;
      } while (puVar7 + uVar8 * 0x18 != puVar9);
    }
  }
code_r0x01f84908:
  *(long **)(param_1 + 0x10) = plVar6;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x20) = 1;
  *(uint *)(param_1 + 0x24) = param_2;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_3 != 0) {
    if (param_4 < param_3) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0x73,&UNK_02963d58/*"The argument 'aEnd' should be grater than or equal to the 'aStart'.(%d/%d)"*/,param_3,param_4);
    }
    *(uint *)(param_1 + 0x2c) = param_3;
    *(uint *)(param_1 + 0x30) = param_4;
  }
  return;
}

// ==== Framework::CHandleManager_Base::tReserve::Reset()
// vaddr 0x1e84960 | ghidra 0x1f84960 | size 8 | symbol _ZN9Framework19CHandleManager_Base8tReserve5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework19CHandleManager_Base8tReserve5ResetEv(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== Framework::CHandleManager_Base::IsInitialized() const
// vaddr 0x1e84968 | ghidra 0x1f84968 | size 16 | symbol _ZNK9Framework19CHandleManager_Base13IsInitializedEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework19CHandleManager_Base13IsInitializedEv(long param_1)

{
  return *(long *)(param_1 + 0x10) != 0;
}

// ==== Framework::CHandleManager_Base::EnableMutex()
// vaddr 0x1e84978 | ghidra 0x1f84978 | size 124 | symbol _ZN9Framework19CHandleManager_Base11EnableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework19CHandleManager_Base11EnableMutexEv(long param_1)

{
  long lVar1;
  
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0x83,&UNK_027ee29f/*"m_pElements is null."*/);
    lVar1 = *(long *)(param_1 + 0x18);
  }
  else {
    lVar1 = *(long *)(param_1 + 0x18);
  }
  if (lVar1 != 0) {
    return;
  }
  lVar1 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar1 != 0) {
    Framework::CMutex::CMutex()(lVar1);
  }
  *(long *)(param_1 + 0x18) = lVar1;
  (*(code *)PTR__ZN9Framework6CMutex10InitializeEv_02ca3bf0)(lVar1);
  return;
}

// ==== Framework::CHandleManager_Base::DisableMutex()
// vaddr 0x1e849f4 | ghidra 0x1f849f4 | size 120 | symbol _ZN9Framework19CHandleManager_Base12DisableMutexEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework19CHandleManager_Base12DisableMutexEv(long param_1)

{
  ulong uVar1;
  
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0x8e,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  if (*(long **)(param_1 + 0x18) != (long *)0x0) {
    uVar1 = (**(code **)(**(long **)(param_1 + 0x18) + 0x10))();
    if ((uVar1 & 1) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0x96,&UNK_02963da3/*"Mutex locked."*/);
    }
    if (*(long **)(param_1 + 0x18) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x18) + 8))();
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
  }
  return;
}

// ==== Framework::CHandleManager_Base::DisableMutex_Execute()
// vaddr 0x1e84a6c | ghidra 0x1f84a6c | size 88 | symbol _ZN9Framework19CHandleManager_Base20DisableMutex_ExecuteEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework19CHandleManager_Base20DisableMutex_ExecuteEv(long param_1)

{
  ulong uVar1;
  
  if (*(long **)(param_1 + 0x18) != (long *)0x0) {
    uVar1 = (**(code **)(**(long **)(param_1 + 0x18) + 0x10))();
    if ((uVar1 & 1) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0x96,&UNK_02963da3/*"Mutex locked."*/);
    }
    if (*(long **)(param_1 + 0x18) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x18) + 8))();
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
  }
  return;
}

// ==== Framework::CHandleManager_Base::rElementContainer()
// vaddr 0x1e84ac4 | ghidra 0x1f84ac4 | size 60 | symbol _ZN9Framework19CHandleManager_Base17rElementContainerEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework19CHandleManager_Base17rElementContainerEv(long param_1)

{
  if (*(long *)(param_1 + 0x10) != 0) {
    return *(long *)(param_1 + 0x10);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0xa5,&UNK_027ee29f/*"m_pElements is null."*/);
  return *(long *)(param_1 + 0x10);
}

// ==== Framework::CHandleManager_Base::tReserve::IsEnable() const
// vaddr 0x1e84b00 | ghidra 0x1f84b00 | size 16 | symbol _ZNK9Framework19CHandleManager_Base8tReserve8IsEnableEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework19CHandleManager_Base8tReserve8IsEnableEv(int *param_1)

{
  return *param_1 != 0;
}

// ==== Framework::CHandleManager_Base::Register(unsigned long)
// vaddr 0x1e84b10 | ghidra 0x1f84b10 | size 248 | symbol _ZN9Framework19CHandleManager_Base8RegisterEm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN9Framework19CHandleManager_Base8RegisterEm(long param_1,undefined8 param_2)

{
  ulong uVar1;
  undefined8 *puVar2;
  long lVar3;
  undefined8 uVar4;
  uint uStack_24;
  
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0xc2,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  lVar3 = *(long *)(param_1 + 0x18);
  if (lVar3 != 0) {
    uVar1 = Framework::CMutex::IsInitialized() const(lVar3);
    if ((uVar1 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar3);
    }
    Framework::CMutex::Lock()(lVar3);
  }
  if (*(uint *)(param_1 + 0x28) < *(uint *)(param_1 + 0x24)) {
    uStack_24 = *(uint *)(param_1 + 0x20);
    if ((*(int *)(param_1 + 0x2c) - 1U < uStack_24) && (uStack_24 <= *(uint *)(param_1 + 0x30))) {
      uStack_24 = *(uint *)(param_1 + 0x30) + 1;
      *(uint *)(param_1 + 0x20) = uStack_24;
    }
    *(uint *)(param_1 + 0x20) = uStack_24 + 1;
    if (uStack_24 + 1 == 0) {
      *(undefined4 *)(param_1 + 0x20) = 1;
    }
    puVar2 = (undefined8 *)Aska::THashMap<unsigned int, unsigned long, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned long> > >::operator[](unsigned int const&)(*(undefined8 *)(param_1 + 0x10),&uStack_24);
    *puVar2 = param_2;
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
    uVar4 = CONCAT44(*(undefined4 *)(param_1 + 8),uStack_24);
  }
  else {
    uVar4 = 0;
  }
  if (lVar3 != 0) {
    Framework::CMutex::Unlock()(lVar3);
  }
  return uVar4;
}

// ==== Framework::CHandleManager_Base::RegisterToReserve(unsigned long, unsigned int)
// vaddr 0x1e84d48 | ghidra 0x1f84d48 | size 348 | symbol _ZN9Framework19CHandleManager_Base17RegisterToReserveEmj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN9Framework19CHandleManager_Base17RegisterToReserveEmj
          (long param_1,undefined8 param_2,uint param_3)

{
  ulong uVar1;
  char cVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  undefined8 *puVar6;
  ulong uVar7;
  ulong uVar8;
  long lVar9;
  long lVar10;
  undefined8 uVar11;
  uint uStack_24;
  
  uStack_24 = param_3;
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0xf3,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  lVar10 = *(long *)(param_1 + 0x18);
  if (lVar10 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar10);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar10);
    }
    Framework::CMutex::Lock()(lVar10);
  }
  if (((*(int *)(param_1 + 0x2c) - 1U < param_3) && (param_3 <= *(uint *)(param_1 + 0x30))) &&
     (*(uint *)(param_1 + 0x28) < *(uint *)(param_1 + 0x24))) {
    lVar5 = *(long *)(param_1 + 0x10);
    uVar4 = *(ulong *)(lVar5 + 0x28);
    if (uVar4 != 0) {
      uVar7 = ~(ulong)param_3 + (ulong)param_3 * 0x200000;
      uVar7 = (uVar7 ^ uVar7 >> 0x18) * 0x109;
      uVar8 = (uVar7 ^ uVar7 >> 0xe) * 0x15;
      uVar7 = 0;
      do {
        uVar1 = (uVar8 ^ uVar8 >> 0x1c) * 0x80000001 + uVar7;
        uVar3 = 0;
        if (uVar4 != 0) {
          uVar3 = uVar1 / uVar4;
        }
        lVar9 = uVar1 - uVar3 * uVar4;
        cVar2 = *(char *)(*(long *)(lVar5 + 0x20) + lVar9 * 0x18);
        if (cVar2 == '\x01') {
          if (*(uint *)(*(long *)(lVar5 + 0x20) + lVar9 * 0x18 + 8) == param_3)
          goto code_r0x01f84e80;
        }
        else if (cVar2 == '\0') break;
        uVar7 = uVar7 + 1;
      } while (uVar7 < uVar4);
    }
    puVar6 = (undefined8 *)Aska::THashMap<unsigned int, unsigned long, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned long> > >::operator[](unsigned int const&)(lVar5,&uStack_24);
    *puVar6 = param_2;
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
    uVar11 = CONCAT44(*(undefined4 *)(param_1 + 8),uStack_24);
  }
  else {
code_r0x01f84e80:
    uVar11 = 0;
  }
  if (lVar10 != 0) {
    Framework::CMutex::Unlock()(lVar10);
  }
  return uVar11;
}

// ==== Framework::CHandleManager_Base::IsRegisteredPointer(unsigned long) const
// vaddr 0x1e84ea4 | ghidra 0x1f84ea4 | size 256 | symbol _ZNK9Framework19CHandleManager_Base19IsRegisteredPointerEm | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework19CHandleManager_Base19IsRegisteredPointerEm(long param_1,long param_2)

{
  char *pcVar1;
  ulong uVar2;
  long lVar3;
  char *pcVar4;
  long lVar5;
  long lVar6;
  undefined4 uVar7;
  
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0x12a,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  lVar6 = *(long *)(param_1 + 0x18);
  if (lVar6 != 0) {
    uVar2 = Framework::CMutex::IsInitialized() const(lVar6);
    if ((uVar2 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar6);
    }
    Framework::CMutex::Lock()(lVar6);
  }
  lVar3 = *(long *)(param_1 + 0x10);
  if (*(int *)(lVar3 + 0x10) != 0) {
    pcVar1 = *(char **)(lVar3 + 0x20);
    lVar3 = *(long *)(lVar3 + 0x28);
    pcVar4 = pcVar1;
    if (lVar3 == 0) {
code_r0x01f84f38:
      while (pcVar4 != pcVar1 + lVar3 * 0x18) {
        if (*(long *)(pcVar4 + 0x10) == param_2) {
          uVar7 = 1;
          goto joined_r0x01f84f9c;
        }
        do {
          if (pcVar1 + lVar3 * 0x18 == pcVar4) goto code_r0x01f84f7c;
          pcVar4 = pcVar4 + 0x18;
        } while (*pcVar4 != '\x01');
      }
    }
    else {
      lVar5 = lVar3 * 0x18;
      do {
        if (*pcVar4 == '\x01') goto code_r0x01f84f38;
        lVar5 = lVar5 + -0x18;
        pcVar4 = pcVar4 + 0x18;
      } while (lVar5 != 0);
    }
  }
code_r0x01f84f7c:
  uVar7 = 0;
joined_r0x01f84f9c:
  if (lVar6 != 0) {
    Framework::CMutex::Unlock()(lVar6);
  }
  return uVar7;
}

// ==== Framework::CHandleManager_Base::IsRegisteredReserveHandle(unsigned int) const
// vaddr 0x1e84fa4 | ghidra 0x1f84fa4 | size 208 | symbol _ZNK9Framework19CHandleManager_Base25IsRegisteredReserveHandleEj | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework19CHandleManager_Base25IsRegisteredReserveHandleEj(long param_1,uint param_2)

{
  ulong uVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  char *pcVar5;
  ulong uVar6;
  ulong uVar7;
  char *pcVar8;
  long lVar9;
  
  if (param_2 <= *(int *)(param_1 + 0x2c) - 1U) {
    return false;
  }
  if (*(uint *)(param_1 + 0x30) < param_2) {
    return false;
  }
  lVar2 = *(long *)(*(long *)(param_1 + 0x10) + 0x20);
  uVar3 = *(ulong *)(*(long *)(param_1 + 0x10) + 0x28);
  if (uVar3 != 0) {
    uVar6 = ~(ulong)param_2 + (ulong)param_2 * 0x200000;
    uVar6 = (uVar6 ^ uVar6 >> 0x18) * 0x109;
    uVar7 = (uVar6 ^ uVar6 >> 0xe) * 0x15;
    uVar6 = 0;
    do {
      uVar1 = (uVar7 ^ uVar7 >> 0x1c) * 0x80000001 + uVar6;
      uVar4 = 0;
      if (uVar3 != 0) {
        uVar4 = uVar1 / uVar3;
      }
      lVar9 = uVar1 - uVar4 * uVar3;
      pcVar8 = (char *)(lVar2 + lVar9 * 0x18);
      if (*pcVar8 == '\x01') {
        if (*(uint *)(lVar2 + lVar9 * 0x18 + 8) == param_2) {
          pcVar5 = (char *)(lVar2 + uVar3 * 0x18);
          goto code_r0x01f8505c;
        }
      }
      else if (*pcVar8 == '\0') break;
      uVar6 = uVar6 + 1;
    } while (uVar6 < uVar3);
  }
  pcVar5 = (char *)(lVar2 + uVar3 * 0x18);
  pcVar8 = pcVar5;
code_r0x01f8505c:
  return pcVar8 != pcVar5;
}

// ==== Framework::CHandleManager_Base::IsIssuedHandle(unsigned long) const
// vaddr 0x1e85074 | ghidra 0x1f85074 | size 20 | symbol _ZNK9Framework19CHandleManager_Base14IsIssuedHandleEm | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework19CHandleManager_Base14IsIssuedHandleEm(long param_1,undefined8 param_2)

{
  return *(int *)(param_1 + 8) == (int)((ulong)param_2 >> 0x20);
}

// ==== Framework::CHandleManager_Base::Unregister(unsigned long)
// vaddr 0x1e85088 | ghidra 0x1f85088 | size 392 | symbol _ZN9Framework19CHandleManager_Base10UnregisterEm | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN9Framework19CHandleManager_Base10UnregisterEm(long param_1,ulong param_2)

{
  char cVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  long lVar9;
  char *pcVar10;
  long lVar11;
  undefined4 uVar12;
  
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0x162,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  lVar11 = *(long *)(param_1 + 0x18);
  if (lVar11 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar11);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar11);
    }
    Framework::CMutex::Lock()(lVar11);
  }
  if (*(int *)(param_1 + 8) == (int)(param_2 >> 0x20)) {
    lVar5 = *(long *)(param_1 + 0x10);
    uVar4 = *(ulong *)(lVar5 + 0x28);
    if (uVar4 != 0) {
      uVar7 = (param_2 & 0xffffffff) * 0x200000 + ((param_2 | 0xffffffff00000000) ^ 0xffffffff);
      uVar7 = (uVar7 ^ uVar7 >> 0x18) * 0x109;
      lVar6 = *(long *)(lVar5 + 0x20);
      uVar8 = (uVar7 ^ uVar7 >> 0xe) * 0x15;
      uVar7 = 0;
      lVar3 = (uVar8 ^ uVar8 >> 0x1c) * 0x80000001;
      do {
        uVar8 = lVar3 + uVar7;
        uVar2 = 0;
        if (uVar4 != 0) {
          uVar2 = uVar8 / uVar4;
        }
        lVar9 = uVar8 - uVar2 * uVar4;
        cVar1 = *(char *)(lVar6 + lVar9 * 0x18);
        if (cVar1 == '\x01') {
          if (*(int *)(lVar6 + lVar9 * 0x18 + 8) == (int)param_2) {
            uVar7 = 0;
            goto code_r0x01f8519c;
          }
        }
        else if (cVar1 == '\0') break;
        uVar7 = uVar7 + 1;
      } while (uVar7 < uVar4);
    }
  }
  uVar12 = 0;
  goto joined_r0x01f85208;
code_r0x01f8519c:
  do {
    uVar8 = lVar3 + uVar7;
    uVar2 = 0;
    if (uVar4 != 0) {
      uVar2 = uVar8 / uVar4;
    }
    lVar9 = uVar8 - uVar2 * uVar4;
    pcVar10 = (char *)(lVar6 + lVar9 * 0x18);
    cVar1 = *pcVar10;
    if (cVar1 == '\x01') {
      if (*(int *)(lVar6 + lVar9 * 0x18 + 8) == (int)param_2) {
        *(int *)(lVar5 + 0x10) = *(int *)(lVar5 + 0x10) + -1;
        *(int *)(lVar5 + 0x14) = *(int *)(lVar5 + 0x14) + 1;
        *pcVar10 = '\x02';
        break;
      }
    }
    else if (cVar1 == '\0') break;
    uVar7 = uVar7 + 1;
  } while (uVar7 < uVar4);
  *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + -1;
  uVar12 = 1;
joined_r0x01f85208:
  if (lVar11 != 0) {
    Framework::CMutex::Unlock()(lVar11);
  }
  return uVar12;
}

// ==== Framework::CHandleManager_Base::Refer(unsigned long) const
// vaddr 0x1e85210 | ghidra 0x1f85210 | size 300 | symbol _ZNK9Framework19CHandleManager_Base5ReferEm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework19CHandleManager_Base5ReferEm(long param_1,ulong param_2)

{
  ulong uVar1;
  char cVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  undefined8 *puVar6;
  ulong uVar7;
  ulong uVar8;
  long lVar9;
  long lVar10;
  undefined8 uVar11;
  int iStack_24;
  
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0x185,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  lVar10 = *(long *)(param_1 + 0x18);
  if (lVar10 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar10);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar10);
    }
    Framework::CMutex::Lock()(lVar10);
  }
  if (*(int *)(param_1 + 8) == (int)(param_2 >> 0x20)) {
    iStack_24 = (int)param_2;
    lVar5 = *(long *)(param_1 + 0x10);
    uVar4 = *(ulong *)(lVar5 + 0x28);
    if (uVar4 != 0) {
      uVar7 = (param_2 & 0xffffffff) * 0x200000 + ((param_2 | 0xffffffff00000000) ^ 0xffffffff);
      uVar7 = (uVar7 ^ uVar7 >> 0x18) * 0x109;
      uVar8 = (uVar7 ^ uVar7 >> 0xe) * 0x15;
      uVar7 = 0;
      do {
        uVar1 = (uVar8 ^ uVar8 >> 0x1c) * 0x80000001 + uVar7;
        uVar3 = 0;
        if (uVar4 != 0) {
          uVar3 = uVar1 / uVar4;
        }
        lVar9 = uVar1 - uVar3 * uVar4;
        cVar2 = *(char *)(*(long *)(lVar5 + 0x20) + lVar9 * 0x18);
        if (cVar2 == '\x01') {
          if (*(int *)(*(long *)(lVar5 + 0x20) + lVar9 * 0x18 + 8) == iStack_24) {
            puVar6 = (undefined8 *)Aska::THashMap<unsigned int, unsigned long, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned long> > >::operator[](unsigned int const&)(lVar5,&iStack_24);
            uVar11 = *puVar6;
            if (lVar10 == 0) {
              return uVar11;
            }
            goto code_r0x01f8530c;
          }
        }
        else if (cVar2 == '\0') break;
        uVar7 = uVar7 + 1;
      } while (uVar7 < uVar4);
    }
  }
  uVar11 = 0;
  if (lVar10 != 0) {
code_r0x01f8530c:
    Framework::CMutex::Unlock()(lVar10);
  }
  return uVar11;
}

// ==== Framework::CHandleManager_Base::Replace(unsigned long, unsigned long)
// vaddr 0x1e8533c | ghidra 0x1f8533c | size 308 | symbol _ZN9Framework19CHandleManager_Base7ReplaceEmm | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN9Framework19CHandleManager_Base7ReplaceEmm(long param_1,ulong param_2,undefined8 param_3)

{
  ulong uVar1;
  char cVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  undefined8 *puVar6;
  ulong uVar7;
  ulong uVar8;
  long lVar9;
  long lVar10;
  undefined4 uVar11;
  int iStack_24;
  
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963ce4/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\HandleManager.cpp"*/,0x1a5,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  lVar10 = *(long *)(param_1 + 0x18);
  if (lVar10 != 0) {
    uVar4 = Framework::CMutex::IsInitialized() const(lVar10);
    if ((uVar4 & 1) == 0) {
      Framework::CMutex::Initialize()(lVar10);
    }
    Framework::CMutex::Lock()(lVar10);
  }
  if (*(int *)(param_1 + 8) == (int)(param_2 >> 0x20)) {
    iStack_24 = (int)param_2;
    lVar5 = *(long *)(param_1 + 0x10);
    uVar4 = *(ulong *)(lVar5 + 0x28);
    if (uVar4 != 0) {
      uVar7 = (param_2 & 0xffffffff) * 0x200000 + ((param_2 | 0xffffffff00000000) ^ 0xffffffff);
      uVar7 = (uVar7 ^ uVar7 >> 0x18) * 0x109;
      uVar8 = (uVar7 ^ uVar7 >> 0xe) * 0x15;
      uVar7 = 0;
      do {
        uVar1 = (uVar8 ^ uVar8 >> 0x1c) * 0x80000001 + uVar7;
        uVar3 = 0;
        if (uVar4 != 0) {
          uVar3 = uVar1 / uVar4;
        }
        lVar9 = uVar1 - uVar3 * uVar4;
        cVar2 = *(char *)(*(long *)(lVar5 + 0x20) + lVar9 * 0x18);
        if (cVar2 == '\x01') {
          if (*(int *)(*(long *)(lVar5 + 0x20) + lVar9 * 0x18 + 8) == iStack_24) {
            puVar6 = (undefined8 *)Aska::THashMap<unsigned int, unsigned long, Aska::THasher<unsigned int>, Aska::TEqualTo<unsigned int>, Aska::TAllocator<Aska::TPair<unsigned int const, unsigned long> > >::operator[](unsigned int const&)(lVar5,&iStack_24);
            *puVar6 = param_3;
            uVar11 = 1;
            if (lVar10 == 0) {
              return 1;
            }
            goto code_r0x01f8543c;
          }
        }
        else if (cVar2 == '\0') break;
        uVar7 = uVar7 + 1;
      } while (uVar7 < uVar4);
    }
  }
  uVar11 = 0;
  if (lVar10 != 0) {
code_r0x01f8543c:
    Framework::CMutex::Unlock()(lVar10);
  }
  return uVar11;
}

// ==== Framework::CHandleManager_Base::MakeHandleFromReserve(unsigned int) const
// vaddr 0x1e85470 | ghidra 0x1f85470 | size 16 | symbol _ZNK9Framework19CHandleManager_Base21MakeHandleFromReserveEj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK9Framework19CHandleManager_Base21MakeHandleFromReserveEj(long param_1,undefined4 param_2)

{
  return CONCAT44(*(undefined4 *)(param_1 + 8),param_2);
}

// ==== Framework::CHandleManager_Base::RegressionTest()
// vaddr 0x1e85480 | ghidra 0x1f85480 | size 4 | symbol _ZN9Framework19CHandleManager_Base14RegressionTestEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework19CHandleManager_Base14RegressionTestEv(void)

{
  return;
}

// ==== Aska::MemoryHandleManager::GetBlock(unsigned int) const
// vaddr 0x1f40608 | ghidra 0x2040608 | size 376 | symbol _ZNK4Aska19MemoryHandleManager8GetBlockEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska19MemoryHandleManager8GetBlockEj(long param_1,uint param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long *plVar7;
  long lVar8;
  
  piVar1 = (int *)(param_1 + 0x338);
  iVar6 = 0;
code_r0x02040624:
  if (*piVar1 == -1) {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x020406ec;
    goto code_r0x02040624;
  }
  ClearExclusiveLocal();
  bVar4 = iVar6 < 0x1ff;
  iVar6 = iVar6 + 1;
  if (bVar4) goto code_r0x02040624;
  piVar2 = (int *)(param_1 + 0x33c);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x378);
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
          Aska::Semaphore::Wait() const(param_1 + 0x378);
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
          if (cVar3 == '\0') goto code_r0x020406dc;
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
code_r0x020406dc:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x020406ec:
  DataMemoryBarrier(2,3);
  plVar7 = *(long **)(param_1 + 0x1f8);
  do {
    if (plVar7 == (long *)0x0) {
      lVar8 = 0;
code_r0x02040724:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x338) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_1 + 0x33c)) {
        piVar1 = (int *)(param_1 + 0x33c);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x378);
        if ((uVar5 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x378);
        }
      }
      return lVar8;
    }
    iVar6 = (param_2 & 0xffffff) - *(int *)((long)plVar7 + 0x14);
    if (iVar6 < (int)plVar7[2]) {
      lVar8 = *plVar7 + (long)iVar6 * 0x48;
      goto code_r0x02040724;
    }
    plVar7 = (long *)plVar7[1];
  } while( true );
}

// ==== Aska::MemoryHandleManager::FreeEx(void*)
// vaddr 0x1f40780 | ghidra 0x2040780 | size 564 | symbol _ZN4Aska19MemoryHandleManager6FreeExEPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska19MemoryHandleManager6FreeExEPv(long param_1,ulong param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  undefined8 uVar5;
  int iVar6;
  ulong uVar7;
  long lVar8;
  
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar6 = 0;
code_r0x0204079c:
  if (*piVar1 == -1) {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x02040864;
    goto code_r0x0204079c;
  }
  ClearExclusiveLocal();
  bVar4 = iVar6 < 0x1ff;
  iVar6 = iVar6 + 1;
  if (bVar4) goto code_r0x0204079c;
  piVar2 = (int *)(param_1 + 0x2ac);
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
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar7 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x2e8);
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
          if (cVar3 == '\0') goto code_r0x02040854;
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
code_r0x02040854:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02040864:
  uVar7 = param_2 >> 0x18 & 0xff;
  DataMemoryBarrier(2,3);
  lVar8 = *(long *)(param_1 + (ulong)((((((((int)uVar7 + (int)(uVar7 / 0x3b) * -0x3b) * 8 +
                                          ((uint)(param_2 >> 0x10) & 0xff)) % 0x3b) * 8 +
                                        ((uint)(param_2 >> 8) & 0xff)) % 0x3b) * 8 +
                                      ((uint)param_2 & 0xff)) % 0x3b) * 8 + 0x10);
  do {
    if (lVar8 == 0) {
code_r0x02040958:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_1 + 0x2ac)) {
        piVar1 = (int *)(param_1 + 0x2ac);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar7 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x2e8);
        }
      }
      return 0;
    }
    if (*(ulong *)(lVar8 + 8) == param_2) {
      if (*(int *)(lVar8 + 0x34) != 0) {
        uVar5 = Aska::MemoryHandleManager::GetBlock(unsigned int) const(param_1);
        Aska::MemoryHandleManager::LocalFree(Aska::_MemoryHandleBlock*)(param_1,uVar5);
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
        DataMemoryBarrier(2,3);
        if (0x14 < *(int *)(param_1 + 0x2ac)) {
          piVar1 = (int *)(param_1 + 0x2ac);
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
          if ((uVar7 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0x2e8);
          }
        }
        return 1;
      }
      goto code_r0x02040958;
    }
    lVar8 = *(long *)(lVar8 + 0x40);
  } while( true );
}

// ==== Aska::MemoryHandleManager::CalcSrbkSize(unsigned long)
// vaddr 0x1f409b4 | ghidra 0x20409b4 | size 24 | symbol _ZN4Aska19MemoryHandleManager12CalcSrbkSizeEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19MemoryHandleManager12CalcSrbkSizeEm(long param_1)

{
  return (param_1 + 0xff7fU >> 0x10) * 0x30;
}

// ==== Aska::MemoryHandleManager::CalcBlocksSize(int)
// vaddr 0x1f409cc | ghidra 0x20409cc | size 16 | symbol _ZN4Aska19MemoryHandleManager14CalcBlocksSizeEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19MemoryHandleManager14CalcBlocksSizeEi(int param_1)

{
  return (long)param_1 * 0x48 + 0x18;
}

// ==== Aska::MemoryHandleManager::CalcSrbkAndBlocksSize(unsigned long, int)
// vaddr 0x1f409dc | ghidra 0x20409dc | size 36 | symbol _ZN4Aska19MemoryHandleManager21CalcSrbkAndBlocksSizeEmi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19MemoryHandleManager21CalcSrbkAndBlocksSizeEmi(long param_1,int param_2)

{
  return (param_1 + 0xfeffU >> 0x10) * 0x30 + (long)param_2 * 0x48 + 0x18;
}

// ==== Aska::MemoryHandleManager::CalcFullHeapSize(unsigned long)
// vaddr 0x1f40a00 | ghidra 0x2040a00 | size 40 | symbol _ZN4Aska19MemoryHandleManager16CalcFullHeapSizeEm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska19MemoryHandleManager16CalcFullHeapSizeEm(long param_1)

{
  return (param_1 * 10 + 0x500U) / 9;
}

// ==== Aska::MemoryHandleManager::CalcFullHeapSizeForOneBlock(unsigned long, long, bool)
// vaddr 0x1f40a28 | ghidra 0x2040a28 | size 52 | symbol _ZN4Aska19MemoryHandleManager27CalcFullHeapSizeForOneBlockEmlb | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska19MemoryHandleManager27CalcFullHeapSizeForOneBlockEmlb(long param_1,ulong param_2)

{
  ulong uVar1;
  
  uVar1 = 0;
  if (param_2 != 0) {
    uVar1 = (param_2 + 0x7f) / param_2;
  }
  return ((param_2 + param_1 + uVar1) * 10) / 9;
}

// ==== Aska::MemoryHandleManager::MemoryHandleManager()
// vaddr 0x1f40a5c | ghidra 0x2040a5c | size 116 | symbol _ZN4Aska19MemoryHandleManagerC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManagerC2Ev(long *param_1)

{
  *(undefined1 *)(param_1 + 1) = 0;
  *param_1 = (long)(PTR__ZTVN4Aska19MemoryHandleManagerE_02cbf0d8 + 0x10);
  memset(param_1 + 2,0,0x1d8);
  *(undefined2 *)(param_1 + 0x46) = 0;
  param_1[0x3f] = 0;
  param_1[0x4d] = 0;
  param_1[0x43] = 0;
  param_1[0x42] = 0;
  param_1[0x45] = 0;
  param_1[0x44] = 0;
  param_1[0x41] = 0;
  param_1[0x40] = 0;
  param_1[0x4c] = 0;
  param_1[0x4b] = 0;
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x4e);
  Aska::FastCriticalSection::FastCriticalSection()(param_1 + 0x60);
  param_1[0x47] = (long)param_1;
  param_1[0x48] = (long)param_1;
  param_1[0x49] = (long)param_1;
  param_1[0x4a] = 0;
  return;
}

// ==== Aska::MemoryHandleManager::~MemoryHandleManager()
// vaddr 0x1f40ad0 | ghidra 0x2040ad0 | size 228 | symbol _ZN4Aska19MemoryHandleManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x02040ba0: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02040ba4) */

void _ZN4Aska19MemoryHandleManagerD1Ev(long *param_1)

{
  long *plVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska19MemoryHandleManagerE_02cbf0d8 + 0x10);
  plVar1 = (long *)param_1[0x48];
  do {
    plVar2 = (long *)plVar1[0x48];
    if ((plVar1 != (long *)0x0) && ((long *)plVar1[0x4a] == param_1)) {
      (**(code **)(*plVar1 + 0xd0))();
    }
    plVar1 = plVar2;
  } while (plVar2 != param_1);
  if (param_1 == (long *)0x0) goto code_r0x011d43e0;
  if ((long *)param_1[0x47] == param_1) {
    plVar2 = (long *)param_1[0x48];
    plVar1 = plVar2;
    do {
      if ((long *)plVar1[0x4a] != param_1) goto code_r0x02040b50;
      plVar1 = (long *)plVar1[0x48];
    } while (plVar1 != param_1);
    goto code_r0x011d43e0;
  }
code_r0x02040b70:
  param_1[0x47] = (long)param_1;
  *(long *)(param_1[0x48] + 0x248) = param_1[0x49];
  *(long *)(param_1[0x49] + 0x240) = param_1[0x48];
  param_1[0x48] = (long)param_1;
  param_1[0x49] = (long)param_1;
code_r0x011d43e0:
  Aska::MemoryHandleManager::DeleteHeap()(param_1);
  (*(code *)PTR__ZN4Aska19FastCriticalSectionD2Ev_02ca21e0)(param_1 + 0x60);
  return;
code_r0x02040b50:
  do {
    plVar2[0x47] = (long)plVar1;
    if ((long *)plVar2[0x4a] == param_1) {
      plVar2[0x4a] = (long)plVar1;
    }
    plVar2 = (long *)plVar2[0x48];
  } while (plVar2 != param_1);
  goto code_r0x02040b70;
}

// ==== Aska::MemoryHandleManager::Remove(Aska::MemoryHandleManager*)
// vaddr 0x1f40bb4 | ghidra 0x2040bb4 | size 160 | symbol _ZN4Aska19MemoryHandleManager6RemoveEPS0_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska19MemoryHandleManager6RemoveEPS0_(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  if (param_2 == 0) {
    return 0;
  }
  if (*(long *)(param_2 + 0x238) != *(long *)(param_1 + 0x238)) {
    return 0;
  }
  if (*(long *)(param_2 + 0x238) == param_2) {
    lVar1 = *(long *)(param_2 + 0x240);
    lVar2 = lVar1;
    while (*(long *)(lVar2 + 0x250) == param_2) {
      lVar2 = *(long *)(lVar2 + 0x240);
      if (lVar2 == param_2) {
        return 0;
      }
    }
    do {
      *(long *)(lVar1 + 0x238) = lVar2;
      if (*(long *)(lVar1 + 0x250) == param_2) {
        *(long *)(lVar1 + 0x250) = lVar2;
      }
      lVar1 = *(long *)(lVar1 + 0x240);
    } while (lVar1 != param_2);
  }
  *(long *)(param_2 + 0x238) = param_2;
  *(undefined8 *)(*(long *)(param_2 + 0x240) + 0x248) = *(undefined8 *)(param_2 + 0x248);
  *(undefined8 *)(*(long *)(param_2 + 0x248) + 0x240) = *(undefined8 *)(param_2 + 0x240);
  *(long *)(param_2 + 0x240) = param_2;
  *(long *)(param_2 + 0x248) = param_2;
  return 1;
}

// ==== Aska::MemoryHandleManager::DeleteHeap()
// vaddr 0x1f40c54 | ghidra 0x2040c54 | size 492 | symbol _ZN4Aska19MemoryHandleManager10DeleteHeapEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager10DeleteHeapEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  
  if ((*(long *)(param_1 + 0x1f8) != 0) || (*(long *)(param_1 + 0x218) != 0)) {
    Aska::MemoryHandleManager::DeregisterThis()(param_1);
    if (*(char *)(param_1 + 0x230) != '\0') {
      piVar1 = (int *)(param_1 + 0x338);
      iVar6 = 0;
code_r0x02040c8c:
      do {
        if (*piVar1 == -1) goto code_r0x02040c98;
        ClearExclusiveLocal();
        bVar4 = iVar6 < 0x1ff;
        iVar6 = iVar6 + 1;
      } while (bVar4);
      piVar2 = (int *)(param_1 + 0x33c);
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
            uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x378);
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
              Aska::Semaphore::Wait() const(param_1 + 0x378);
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
              if (cVar3 == '\0') goto code_r0x02040d44;
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
code_r0x02040d44:
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar4) {
          *piVar2 = *piVar2 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x02040d54:
      DataMemoryBarrier(2,3);
      if ((*(long *)(param_1 + 0x1f8) != 0) &&
         (lVar7 = *(long *)(*(long *)(param_1 + 0x1f8) + 8), lVar7 != 0)) {
        lVar8 = *(long *)(lVar7 + 8);
        if (*(long *)(param_1 + 0x210) == 0) {
          for (; lVar8 != 0; lVar8 = *(long *)(lVar8 + 8)) {
            operator delete(void*)(lVar7);
            lVar7 = lVar8;
          }
        }
        else if (lVar8 != 0) {
          Aska::MemoryManager::LocalFree(void*)(*(long *)(param_1 + 0x210),lVar7);
          for (lVar7 = *(long *)(lVar8 + 8); lVar7 != 0; lVar7 = *(long *)(lVar7 + 8)) {
            Aska::MemoryManager::LocalFree(void*)(*(undefined8 *)(param_1 + 0x210),lVar8);
            lVar8 = lVar7;
          }
        }
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x338) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_1 + 0x33c)) {
        piVar1 = (int *)(param_1 + 0x33c);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x378);
        if ((uVar5 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x378);
        }
      }
    }
    if (*(char *)(param_1 + 0x231) != '\0') {
      operator delete[](void*)(*(long *)(param_1 + 0x218) + -0x80);
      *(undefined8 *)(param_1 + 0x218) = 0;
      *(undefined1 *)(param_1 + 0x231) = 0;
    }
    *(undefined8 *)(param_1 + 0x1f8) = 0;
    *(undefined8 *)(param_1 + 0x218) = 0;
  }
  return;
code_r0x02040c98:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
  if (bVar4) {
    *piVar1 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02040d54;
  goto code_r0x02040c8c;
}

// ==== Aska::MemoryHandleManager::~MemoryHandleManager()
// vaddr 0x1f40e40 | ghidra 0x2040e40 | size 24 | symbol _ZN4Aska19MemoryHandleManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManagerD0Ev(undefined8 param_1)

{
  Aska::MemoryHandleManager::~MemoryHandleManager()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::MemoryHandleManager::InitHeap(unsigned char*, long, unsigned char*, long)
// vaddr 0x1f40e58 | ghidra 0x2040e58 | size 188 | symbol _ZN4Aska19MemoryHandleManager8InitHeapEPhlS1_l | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska19MemoryHandleManager8InitHeapEPhlS1_l
          (long param_1,long param_2,long param_3,long param_4,long param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  uint uVar4;
  
  Aska::MemoryHandleManager::DeleteHeap()();
  if (param_4 == 0) {
    uVar3 = 0;
  }
  else {
    *(long *)(param_1 + 0x218) = param_2 + 0x80;
    *(long *)(param_1 + 0x220) = param_3 + -0x80;
    lVar1 = param_3 + 0x1ff7e;
    if (-1 < param_3 + 0xff7f) {
      lVar1 = param_3 + 0xff7f;
    }
    uVar4 = (uint)((ulong)lVar1 >> 0x10);
    *(uint *)(param_1 + 0x1f0) = uVar4;
    lVar1 = (lVar1 >> 0x10 & 0xffffffffU) + (ulong)uVar4 * 2;
    *(long *)(param_1 + 0x1e8) = param_4;
    Aska::MemoryHandleManager::AddUnusedMemoryBlockChunk(Aska::MemoryHandleManager::_UnusedMemoryBlockChunk*, unsigned long)(param_1,param_4 + lVar1 * 0x10,param_5 + -0x18 + lVar1 * -0x10);
    uVar2 = Aska::MemoryHandleManager::InitSrbk()(param_1);
    if ((uVar2 & 1) == 0) {
      uVar3 = 0;
      *(undefined8 *)(param_1 + 0x218) = 0;
    }
    else {
      Aska::MemoryHandleManager::RegisterThis()(param_1);
      uVar3 = 1;
    }
  }
  return uVar3;
}

// ==== Aska::MemoryHandleManager::CalcNumberOfSrbks(long)
// vaddr 0x1f40f14 | ghidra 0x2040f14 | size 32 | symbol _ZN4Aska19MemoryHandleManager17CalcNumberOfSrbksEl | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19MemoryHandleManager17CalcNumberOfSrbksEl(undefined8 param_1,long param_2)

{
  long lVar1;
  
  lVar1 = param_2 + 0x1fffe;
  if (-1 < param_2 + 0xffff) {
    lVar1 = param_2 + 0xffff;
  }
  return lVar1 >> 0x10;
}

// ==== Aska::MemoryHandleManager::AddUnusedMemoryBlockChunk(Aska::MemoryHandleManager::_UnusedMemoryBlockChunk*, unsigned long)
// vaddr 0x1f40f34 | ghidra 0x2040f34 | size 664 | symbol _ZN4Aska19MemoryHandleManager25AddUnusedMemoryBlockChunkEPNS0_23_UnusedMemoryBlockChunkEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager25AddUnusedMemoryBlockChunkEPNS0_23_UnusedMemoryBlockChunkEm
               (long param_1,long *param_2,ulong param_3)

{
  int *piVar1;
  int *piVar2;
  ulong uVar3;
  int iVar4;
  char cVar5;
  bool bVar6;
  int iVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  ulong uVar11;
  long lVar12;
  
  piVar1 = (int *)(param_1 + 0x338);
  iVar7 = 0;
code_r0x02040f58:
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar6 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
      if (bVar6) goto code_r0x02040f58;
      piVar2 = (int *)(param_1 + 0x33c);
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar6) {
          *piVar2 = *piVar2 + 1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
      do {
        if (*piVar1 != -1) {
          ClearExclusiveLocal();
          do {
            uVar11 = Aska::Semaphore::IsReady() const(param_1 + 0x378);
            if ((uVar11 & 1) == 0) {
              do {
                cVar5 = '\x01';
                bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
                if (bVar6) {
                  *piVar2 = *piVar2 + -1;
                  cVar5 = ExclusiveMonitorsStatus();
                }
              } while (cVar5 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
            else {
              Aska::Semaphore::Wait() const(param_1 + 0x378);
            }
            do {
              cVar5 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar6) {
                *piVar2 = *piVar2 + 1;
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
              if (cVar5 == '\0') goto code_r0x02041010;
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
code_r0x02041010:
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar6) {
          *piVar2 = *piVar2 + -1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
code_r0x02041020:
      DataMemoryBarrier(2,3);
      *param_2 = (long)(param_2 + 3);
      *(int *)(param_2 + 2) = (int)(param_3 / 0x48);
      if (*(long *)(param_1 + 0x1f8) == 0) {
        *(undefined4 *)((long)param_2 + 0x14) = 0;
        *(long **)(param_1 + 0x1f8) = param_2;
        *(long *)(param_1 + 0x208) = *param_2;
      }
      else {
        lVar8 = *(long *)(param_1 + 0x200);
        *(long **)(lVar8 + 8) = param_2;
        *(int *)((long)param_2 + 0x14) = *(int *)(lVar8 + 0x10) + *(int *)(lVar8 + 0x14);
      }
      param_2[1] = 0;
      *(long **)(param_1 + 0x200) = param_2;
      iVar4 = (int)param_2[2];
      lVar8 = *param_2;
      lVar12 = *(long *)(param_1 + 0x208);
      uVar11 = lVar8 + (long)(iVar4 + -1) * 0x48;
      memset(lVar8,0,(long)iVar4 * 0x48);
      iVar7 = *(int *)((long)param_2 + 0x14);
      if (lVar12 == lVar8) {
        *(long *)(lVar12 + 0x10) = lVar12;
        *(long *)(lVar12 + 0x18) = lVar12;
        *(int *)(lVar12 + 0x34) = iVar7;
        iVar7 = iVar7 + 1;
        lVar9 = lVar12 + 0x48;
        lVar10 = lVar12;
        if (iVar4 < 2) {
          lVar9 = lVar12;
        }
      }
      else {
        lVar9 = lVar8;
        lVar10 = *(long *)(lVar12 + 0x18);
      }
      *(long *)(lVar10 + 0x10) = lVar9;
      *(long *)(lVar9 + 0x18) = lVar10;
      *(long *)(lVar8 + (long)(iVar4 + -1) * 0x48 + 0x10) = lVar12;
      *(ulong *)(lVar12 + 0x18) = uVar11;
      if (1 < iVar4) {
        uVar3 = lVar9 + 0x48;
        *(int *)(lVar9 + 0x34) = iVar7;
        *(ulong *)(lVar9 + 0x10) = uVar3;
        *(long *)(lVar9 + 0x60) = lVar9;
        while (iVar7 = iVar7 + 1, uVar3 < uVar11) {
          uVar3 = lVar9 + 0x90;
          *(int *)(lVar9 + 0x7c) = iVar7;
          *(ulong *)(lVar9 + 0x58) = uVar3;
          *(long *)(lVar9 + 0xa8) = lVar9 + 0x48;
          lVar9 = lVar9 + 0x48;
        }
        *(int *)(lVar9 + 0x7c) = iVar7;
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x338) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_1 + 0x33c)) {
        piVar1 = (int *)(param_1 + 0x33c);
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar6) {
            *piVar1 = *piVar1 + -1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        uVar11 = Aska::Semaphore::IsReady() const(param_1 + 0x378);
        if ((uVar11 & 1) != 0) {
          (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x378);
          return;
        }
      }
      return;
    }
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar6) {
      *piVar1 = 0;
      cVar5 = ExclusiveMonitorsStatus();
    }
    if (cVar5 == '\0') goto code_r0x02041020;
  } while( true );
}

// ==== Aska::MemoryHandleManager::InitSrbk()
// vaddr 0x1f411cc | ghidra 0x20411cc | size 580 | symbol _ZN4Aska19MemoryHandleManager8InitSrbkEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska19MemoryHandleManager8InitSrbkEv(long param_1)

{
  bool bVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  undefined8 *puVar6;
  undefined1 *puVar7;
  undefined8 *puVar8;
  
  puVar7 = *(undefined1 **)(param_1 + 0x1e8);
  *puVar7 = 1;
  *(undefined8 *)(puVar7 + 4) = 0;
  puVar6 = *(undefined8 **)(param_1 + 0x208);
  puVar2 = (undefined8 *)puVar6[2];
  if (puVar6 == puVar2) {
    if (*(char *)(param_1 + 0x230) != '\0') {
      lVar4 = ((long)*(int *)(*(long *)(param_1 + 0x200) + 0x10) +
              (long)*(int *)(*(long *)(param_1 + 0x200) + 0x14)) * 0x48;
      if (*(long *)(param_1 + 0x210) == 0) {
        lVar5 = operator new[](unsigned long, std::nothrow_t const&)(lVar4 + 0x18,PTR__ZSt7nothrow_02cb9a80);
      }
      else {
        lVar5 = Aska::MemoryManager::Malloc(unsigned long)();
      }
      if (lVar5 != 0) {
        Aska::MemoryHandleManager::AddUnusedMemoryBlockChunk(Aska::MemoryHandleManager::_UnusedMemoryBlockChunk*, unsigned long)(param_1,lVar5,lVar4);
        puVar2 = (undefined8 *)puVar6[2];
        goto code_r0x020411fc;
      }
    }
    puVar6 = (undefined8 *)0x0;
  }
  else {
code_r0x020411fc:
    lVar4 = puVar6[3];
    puVar2[3] = lVar4;
    *(undefined8 **)(lVar4 + 0x10) = puVar2;
    *(undefined8 **)(param_1 + 0x208) = puVar2;
    *(undefined1 *)((long)puVar6 + 0x31) = 0;
  }
  puVar8 = *(undefined8 **)(param_1 + 0x208);
  puVar2 = (undefined8 *)puVar8[2];
  if (puVar8 == puVar2) {
    if (*(char *)(param_1 + 0x230) != '\0') {
      lVar4 = ((long)*(int *)(*(long *)(param_1 + 0x200) + 0x10) +
              (long)*(int *)(*(long *)(param_1 + 0x200) + 0x14)) * 0x48;
      if (*(long *)(param_1 + 0x210) == 0) {
        lVar5 = operator new[](unsigned long, std::nothrow_t const&)(lVar4 + 0x18,PTR__ZSt7nothrow_02cb9a80);
      }
      else {
        lVar5 = Aska::MemoryManager::Malloc(unsigned long)();
      }
      if (lVar5 != 0) {
        Aska::MemoryHandleManager::AddUnusedMemoryBlockChunk(Aska::MemoryHandleManager::_UnusedMemoryBlockChunk*, unsigned long)(param_1,lVar5,lVar4);
        puVar2 = (undefined8 *)puVar8[2];
        goto code_r0x02041290;
      }
    }
    if (puVar6 == (undefined8 *)0x0) {
      return 0;
    }
    puVar8 = (undefined8 *)0x0;
    bVar1 = true;
  }
  else {
code_r0x02041290:
    lVar4 = puVar8[3];
    bVar1 = puVar8 == (undefined8 *)0x0;
    puVar2[3] = lVar4;
    *(undefined8 **)(lVar4 + 0x10) = puVar2;
    *(undefined8 **)(param_1 + 0x208) = puVar2;
    *(undefined1 *)((long)puVar8 + 0x31) = 0;
    if ((puVar6 != (undefined8 *)0x0) && (puVar8 != (undefined8 *)0x0)) {
      lVar5 = *(long *)(param_1 + 0x1e8);
      lVar4 = *(long *)(param_1 + 0x218);
      uVar3 = *(undefined8 *)(param_1 + 0x220);
      *(undefined2 *)(puVar6 + 6) = 0x100;
      *puVar6 = 0;
      puVar6[1] = lVar4 + ((ulong)((long)puVar7 - lVar5) >> 4) * -0x5555555555550000;
      *(undefined8 **)(puVar7 + 0x28) = puVar6;
      puVar6[4] = puVar8;
      puVar6[5] = puVar8;
      puVar6[2] = puVar8;
      puVar6[3] = puVar8;
      *puVar8 = uVar3;
      *(undefined2 *)(puVar8 + 6) = 0;
      puVar8[4] = puVar6;
      puVar8[5] = puVar6;
      puVar8[2] = puVar6;
      puVar8[3] = puVar6;
      puVar8[1] = puVar6[1];
      *(undefined8 *)(puVar7 + 0x10) = 0;
      uVar3 = *(undefined8 *)(param_1 + 0x220);
      *(undefined8 *)(puVar7 + 0x18) = uVar3;
      *(undefined8 *)(puVar7 + 0x20) = uVar3;
      if (1 < (int)*(uint *)(param_1 + 0x1f0)) {
        lVar5 = (ulong)*(uint *)(param_1 + 0x1f0) - 1;
        lVar4 = 0x30;
        do {
          lVar5 = lVar5 + -1;
          *(undefined1 *)(*(long *)(param_1 + 0x1e8) + lVar4) = 0;
          lVar4 = lVar4 + 0x30;
        } while (lVar5 != 0);
      }
      return 1;
    }
    if (puVar6 == (undefined8 *)0x0) goto code_r0x020413e4;
  }
  lVar4 = *(long *)(param_1 + 0x208);
  lVar5 = *(long *)(lVar4 + 0x18);
  *(undefined8 **)(lVar4 + 0x18) = puVar6;
  puVar6[2] = lVar4;
  *(undefined8 **)(lVar5 + 0x10) = puVar6;
  puVar6[3] = lVar5;
  if (bVar1) {
    return 0;
  }
code_r0x020413e4:
  lVar4 = *(long *)(param_1 + 0x208);
  lVar5 = *(long *)(lVar4 + 0x18);
  *(undefined8 **)(lVar4 + 0x18) = puVar8;
  puVar8[2] = lVar4;
  *(undefined8 **)(lVar5 + 0x10) = puVar8;
  puVar8[3] = lVar5;
  return 0;
}

// ==== Aska::MemoryHandleManager::RegisterThis()
// vaddr 0x1f41410 | ghidra 0x2041410 | size 468 | symbol _ZN4Aska19MemoryHandleManager12RegisterThisEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager12RegisterThisEv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  long lVar4;
  ulong uVar5;
  int iVar6;
  int *piVar7;
  long lVar8;
  long lVar9;
  
  lVar9 = *(long *)PTR__ZN4Aska19MemoryHandleManager12m_pCriGlobalE_02cbad50;
  if (lVar9 != 0) {
    piVar7 = (int *)(lVar9 + 0x38);
    iVar6 = 0;
code_r0x02041438:
    do {
      if (*piVar7 == -1) goto code_r0x02041444;
      ClearExclusiveLocal();
      bVar3 = iVar6 < 0x1ff;
      iVar6 = iVar6 + 1;
    } while (bVar3);
    piVar1 = (int *)(lVar9 + 0x3c);
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
          uVar5 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
          if ((uVar5 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar9 + 0x78);
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
            if (cVar2 == '\0') goto code_r0x020414f0;
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
code_r0x020414f0:
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
code_r0x02041500:
    DataMemoryBarrier(2,3);
  }
  if (*(long *)PTR__ZN4Aska19MemoryHandleManager15m_pGlobalMasterE_02cbe208 == 0) {
    *(long *)PTR__ZN4Aska19MemoryHandleManager15m_pGlobalMasterE_02cbe208 = param_1;
  }
  else {
    lVar4 = *(long *)PTR__ZN4Aska19MemoryHandleManager15m_pGlobalMasterE_02cbe208;
    do {
      while ((lVar8 = lVar4, *(ulong *)(param_1 + 0x218) < *(ulong *)(lVar8 + 0x218) ||
             (*(long *)(lVar8 + 0x220) + *(ulong *)(lVar8 + 0x218) <
              *(long *)(param_1 + 0x220) + *(ulong *)(param_1 + 0x218)))) {
        lVar4 = *(long *)(lVar8 + 0x268);
        if (*(long *)(lVar8 + 0x268) == 0) {
          *(long *)(lVar8 + 0x268) = param_1;
          *(undefined8 *)(param_1 + 0x260) = *(undefined8 *)(lVar8 + 0x260);
          goto joined_r0x0204155c;
        }
      }
      lVar4 = *(long *)(lVar8 + 600);
    } while (*(long *)(lVar8 + 600) != 0);
    *(long *)(lVar8 + 600) = param_1;
    *(long *)(param_1 + 0x260) = lVar8;
  }
joined_r0x0204155c:
  if (lVar9 != 0) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar7 = (int *)(lVar9 + 0x3c);
    if (0x14 < *piVar7) {
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
        if (bVar3) {
          *piVar7 = *piVar7 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      uVar5 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
      if ((uVar5 & 1) != 0) {
        (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(lVar9 + 0x78);
        return;
      }
    }
  }
  return;
code_r0x02041444:
  cVar2 = '\x01';
  bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
  if (bVar3) {
    *piVar7 = 0;
    cVar2 = ExclusiveMonitorsStatus();
  }
  if (cVar2 == '\0') goto code_r0x02041500;
  goto code_r0x02041438;
}

// ==== Aska::MemoryHandleManager::InitHeap(unsigned char*, long, unsigned char*, long, unsigned char*, long)
// vaddr 0x1f415e4 | ghidra 0x20415e4 | size 204 | symbol _ZN4Aska19MemoryHandleManager8InitHeapEPhlS1_lS1_l | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska19MemoryHandleManager8InitHeapEPhlS1_lS1_l
          (long param_1,long param_2,long param_3,long param_4,ulong param_5,long param_6,
          long param_7)

{
  long lVar1;
  undefined8 uVar2;
  ulong uVar3;
  
  Aska::MemoryHandleManager::DeleteHeap()();
  uVar2 = 0;
  if ((param_4 != 0) && (param_6 != 0)) {
    *(long *)(param_1 + 0x220) = param_3 + -0x80;
    *(long *)(param_1 + 0x218) = param_2 + 0x80;
    lVar1 = param_3 + 0x1ff7e;
    if (-1 < param_3 + 0xff7f) {
      lVar1 = param_3 + 0xff7f;
    }
    *(long *)(param_1 + 0x1e8) = param_4;
    *(int *)(param_1 + 0x1f0) = (int)((ulong)lVar1 >> 0x10);
    Aska::MemoryHandleManager::AddUnusedMemoryBlockChunk(Aska::MemoryHandleManager::_UnusedMemoryBlockChunk*, unsigned long)(param_1,param_6,param_7 + -0x18);
    uVar3 = (ulong)*(uint *)(param_1 + 0x1f0) * 0x30;
    if ((uVar3 < param_5 || uVar3 - param_5 == 0) &&
       (uVar3 = Aska::MemoryHandleManager::InitSrbk()(param_1), (uVar3 & 1) != 0)) {
      Aska::MemoryHandleManager::RegisterThis()(param_1);
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

// ==== Aska::MemoryHandleManager::InitHeap(unsigned char*, long)
// vaddr 0x1f416b0 | ghidra 0x20416b0 | size 220 | symbol _ZN4Aska19MemoryHandleManager8InitHeapEPhl | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska19MemoryHandleManager8InitHeapEPhl(long param_1,long param_2,long param_3)

{
  long lVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  uint uVar5;
  ulong uVar6;
  
  lVar3 = 0xc0;
  if (0x77f < param_3) {
    lVar3 = param_3 / 10;
  }
  uVar6 = param_3 - lVar3 & 0xfffffffffffffff0;
  lVar2 = param_2 + uVar6;
  Aska::MemoryHandleManager::DeleteHeap()();
  if (lVar2 == 0) {
    uVar4 = 0;
  }
  else {
    *(long *)(param_1 + 0x218) = param_2 + 0x80;
    *(ulong *)(param_1 + 0x220) = uVar6 - 0x80;
    lVar1 = uVar6 + 0x1ff7e;
    if (-1 < (long)(uVar6 + 0xff7f)) {
      lVar1 = uVar6 + 0xff7f;
    }
    uVar5 = (uint)((ulong)lVar1 >> 0x10);
    *(uint *)(param_1 + 0x1f0) = uVar5;
    lVar1 = (lVar1 >> 0x10 & 0xffffffffU) + (ulong)uVar5 * 2;
    *(long *)(param_1 + 0x1e8) = lVar2;
    Aska::MemoryHandleManager::AddUnusedMemoryBlockChunk(Aska::MemoryHandleManager::_UnusedMemoryBlockChunk*, unsigned long)(param_1,lVar2 + lVar1 * 0x10,lVar3 + -0x18 + lVar1 * -0x10);
    uVar6 = Aska::MemoryHandleManager::InitSrbk()(param_1);
    if ((uVar6 & 1) == 0) {
      uVar4 = 0;
      *(undefined8 *)(param_1 + 0x218) = 0;
    }
    else {
      Aska::MemoryHandleManager::RegisterThis()(param_1);
      uVar4 = 1;
    }
  }
  return uVar4;
}

// ==== Aska::MemoryHandleManager::InitHeap(long)
// vaddr 0x1f4178c | ghidra 0x204178c | size 260 | symbol _ZN4Aska19MemoryHandleManager8InitHeapEl | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska19MemoryHandleManager8InitHeapEl(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  long lVar3;
  uint uVar4;
  ulong uVar5;
  
  if (*(long *)(param_1 + 0x218) == 0) {
    lVar3 = operator new[](unsigned long, std::nothrow_t const&)(param_2,PTR__ZSt7nothrow_02cb9a80);
    if (lVar3 == 0) {
      return 0;
    }
    lVar2 = 0xc0;
    if (0x77f < param_2) {
      lVar2 = param_2 / 10;
    }
    uVar5 = param_2 - lVar2 & 0xfffffffffffffff0;
    Aska::MemoryHandleManager::DeleteHeap()(param_1);
    *(long *)(param_1 + 0x218) = lVar3 + 0x80;
    *(ulong *)(param_1 + 0x220) = uVar5 - 0x80;
    lVar1 = uVar5 + 0x1ff7e;
    if (-1 < (long)(uVar5 + 0xff7f)) {
      lVar1 = uVar5 + 0xff7f;
    }
    uVar4 = (uint)((ulong)lVar1 >> 0x10);
    *(uint *)(param_1 + 0x1f0) = uVar4;
    lVar1 = (lVar1 >> 0x10 & 0xffffffffU) + (ulong)uVar4 * 2;
    *(ulong *)(param_1 + 0x1e8) = lVar3 + uVar5;
    Aska::MemoryHandleManager::AddUnusedMemoryBlockChunk(Aska::MemoryHandleManager::_UnusedMemoryBlockChunk*, unsigned long)(param_1,lVar3 + uVar5 + lVar1 * 0x10,lVar2 + -0x18 + lVar1 * -0x10);
    uVar5 = Aska::MemoryHandleManager::InitSrbk()(param_1);
    if ((uVar5 & 1) != 0) {
      Aska::MemoryHandleManager::RegisterThis()(param_1);
      *(undefined1 *)(param_1 + 0x231) = 1;
      return 1;
    }
    *(undefined8 *)(param_1 + 0x218) = 0;
    operator delete[](void*)(lVar3);
  }
  return 0;
}

// ==== Aska::MemoryHandleManager::DeregisterThis()
// vaddr 0x1f41890 | ghidra 0x2041890 | size 608 | symbol _ZN4Aska19MemoryHandleManager14DeregisterThisEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager14DeregisterThisEv(long param_1)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  int *piVar7;
  ulong uVar8;
  ulong uVar9;
  long lVar10;
  long lVar11;
  
  lVar11 = *(long *)PTR__ZN4Aska19MemoryHandleManager12m_pCriGlobalE_02cbad50;
  if (lVar11 != 0) {
    piVar7 = (int *)(lVar11 + 0x38);
    iVar4 = 0;
code_r0x020418b8:
    do {
      if (*piVar7 == -1) goto code_r0x020418c4;
      ClearExclusiveLocal();
      bVar3 = iVar4 < 0x1ff;
      iVar4 = iVar4 + 1;
    } while (bVar3);
    piVar1 = (int *)(lVar11 + 0x3c);
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
          uVar9 = Aska::Semaphore::IsReady() const(lVar11 + 0x78);
          if ((uVar9 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar11 + 0x78);
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
            if (cVar2 == '\0') goto code_r0x02041970;
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
code_r0x02041970:
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar3) {
        *piVar1 = *piVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
code_r0x02041980:
    DataMemoryBarrier(2,3);
  }
  lVar5 = *(long *)PTR__ZN4Aska19MemoryHandleManager15m_pGlobalMasterE_02cbe208;
  if (lVar5 != 0) {
    if (lVar5 == param_1) {
      *(undefined8 *)PTR__ZN4Aska19MemoryHandleManager15m_pGlobalMasterE_02cbe208 = 0;
    }
    else {
      uVar9 = *(ulong *)(lVar5 + 0x218);
      if (uVar9 == 0) {
        do {
          lVar6 = lVar5;
          lVar5 = *(long *)(lVar6 + 600);
          if (lVar5 == 0) {
            lVar5 = *(long *)(lVar6 + 0x268);
            lVar10 = lVar6;
            while (lVar5 == 0) {
              lVar10 = *(long *)(lVar10 + 0x260);
              if (lVar10 == 0) goto joined_r0x02041abc;
              lVar5 = *(long *)(lVar10 + 0x268);
            }
          }
        } while (lVar5 != param_1);
        lVar5 = *(long *)(param_1 + 0x260);
        if (lVar5 == 0) {
          *(undefined8 *)PTR__ZN4Aska19MemoryHandleManager15m_pGlobalMasterE_02cbe208 =
               *(undefined8 *)(param_1 + 0x268);
          goto joined_r0x02041abc;
        }
        if (*(long *)(lVar5 + 600) != param_1) {
          if (lVar6 != 0) {
            *(undefined8 *)(lVar6 + 0x268) = *(undefined8 *)(param_1 + 0x268);
          }
          goto joined_r0x02041abc;
        }
      }
      else {
        uVar8 = *(ulong *)(param_1 + 0x218);
        if (uVar8 < uVar9) goto code_r0x020419e8;
        while( true ) {
          if (*(long *)(lVar5 + 0x220) + uVar9 < *(long *)(param_1 + 0x220) + uVar8)
          goto code_r0x020419e8;
          lVar6 = *(long *)(lVar5 + 600);
          if (*(long *)(lVar5 + 600) == param_1) break;
          while( true ) {
            lVar5 = lVar6;
            if (lVar5 == 0) goto joined_r0x02041abc;
            uVar9 = *(ulong *)(lVar5 + 0x218);
            if (uVar9 <= uVar8) break;
code_r0x020419e8:
            lVar6 = *(long *)(lVar5 + 0x268);
            if (*(long *)(lVar5 + 0x268) == param_1) {
              *(undefined8 *)(lVar5 + 0x268) = *(undefined8 *)(param_1 + 0x268);
              goto joined_r0x02041abc;
            }
          }
        }
      }
      *(undefined8 *)(lVar5 + 600) = *(undefined8 *)(param_1 + 0x268);
    }
  }
joined_r0x02041abc:
  if (lVar11 != 0) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar11 + 0x38) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar7 = (int *)(lVar11 + 0x3c);
    if (0x14 < *piVar7) {
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
        if (bVar3) {
          *piVar7 = *piVar7 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      uVar9 = Aska::Semaphore::IsReady() const(lVar11 + 0x78);
      if ((uVar9 & 1) != 0) {
        (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(lVar11 + 0x78);
        return;
      }
    }
  }
  return;
code_r0x020418c4:
  cVar2 = '\x01';
  bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
  if (bVar3) {
    *piVar7 = 0;
    cVar2 = ExclusiveMonitorsStatus();
  }
  if (cVar2 == '\0') goto code_r0x02041980;
  goto code_r0x020418b8;
}

// ==== Aska::MemoryHandleManager::IsAllocated(unsigned int, unsigned long*) const
// vaddr 0x1f41af0 | ghidra 0x2041af0 | size 384 | symbol _ZNK4Aska19MemoryHandleManager11IsAllocatedEjPm | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZNK4Aska19MemoryHandleManager11IsAllocatedEjPm(long param_1,undefined4 param_2,undefined8 *param_3)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  undefined8 *puVar5;
  ulong uVar6;
  int iVar7;
  undefined4 uVar8;
  
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02041bdc;
    }
    ClearExclusiveLocal();
    bVar4 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0x2ac);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar6 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x2e8);
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
          if (cVar3 == '\0') goto code_r0x02041bcc;
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
code_r0x02041bcc:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02041bdc:
  DataMemoryBarrier(2,3);
  puVar5 = (undefined8 *)Aska::MemoryHandleManager::GetBlock(unsigned int) const(param_1,param_2);
  if ((puVar5 == (undefined8 *)0x0) || (*(char *)((long)puVar5 + 0x31) == '\0')) {
    uVar8 = 0;
  }
  else {
    if (param_3 != (undefined8 *)0x0) {
      *param_3 = *puVar5;
    }
    uVar8 = 1;
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x2ac)) {
    piVar1 = (int *)(param_1 + 0x2ac);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x2e8);
    }
  }
  return uVar8;
}

// ==== Aska::MemoryHandleManager::IsAllocated(void const*, unsigned long*)
// vaddr 0x1f41c70 | ghidra 0x2041c70 | size 184 | symbol _ZN4Aska19MemoryHandleManager11IsAllocatedEPKvPm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska19MemoryHandleManager11IsAllocatedEPKvPm(ulong param_1)

{
  long lVar1;
  ulong uVar2;
  
  lVar1 = Aska::MemoryHandleManager::GetAllocatedManager(void const*, unsigned long*)(param_1,0);
  if (lVar1 != 0) {
    uVar2 = param_1 >> 0x18 & 0xff;
    for (lVar1 = *(long *)(lVar1 + (ulong)((((((((int)uVar2 + (int)(uVar2 / 0x3b) * -0x3b) * 8 +
                                               ((uint)(param_1 >> 0x10) & 0xff)) % 0x3b) * 8 +
                                             ((uint)(param_1 >> 8) & 0xff)) % 0x3b) * 8 +
                                           ((uint)param_1 & 0xff)) % 0x3b) * 8 + 0x10); lVar1 != 0;
        lVar1 = *(long *)(lVar1 + 0x40)) {
      if (*(ulong *)(lVar1 + 8) == param_1) {
        if (*(int *)(lVar1 + 0x34) == 0) {
          return 0;
        }
        return 1;
      }
    }
  }
  return 0;
}

// ==== Aska::MemoryHandleManager::GetAllocatedManager(void const*, unsigned long*)
// vaddr 0x1f41d28 | ghidra 0x2041d28 | size 660 | symbol _ZN4Aska19MemoryHandleManager19GetAllocatedManagerEPKvPm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19MemoryHandleManager19GetAllocatedManagerEPKvPm(ulong param_1,undefined8 *param_2)

{
  int *piVar1;
  char cVar2;
  bool bVar3;
  undefined *puVar4;
  undefined8 *puVar5;
  undefined4 uVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  ulong uVar10;
  int iVar11;
  int *piVar12;
  
  puVar4 = PTR__ZN4Aska19MemoryHandleManager12m_pCriGlobalE_02cbad50;
  lVar7 = *(long *)PTR__ZN4Aska19MemoryHandleManager12m_pCriGlobalE_02cbad50;
  if (lVar7 == 0) {
    return 0;
  }
  piVar12 = (int *)(lVar7 + 0x38);
  iVar11 = 0;
code_r0x02041d58:
  if (*piVar12 == -1) {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar12,0x10);
    if (bVar3) {
      *piVar12 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
    if (cVar2 == '\0') goto code_r0x02041e28;
    goto code_r0x02041d58;
  }
  ClearExclusiveLocal();
  bVar3 = iVar11 < 0x1ff;
  iVar11 = iVar11 + 1;
  if (bVar3) goto code_r0x02041d58;
  piVar1 = (int *)(lVar7 + 0x3c);
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + 1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  do {
    if (*piVar12 != -1) {
      ClearExclusiveLocal();
      do {
        uVar10 = Aska::Semaphore::IsReady() const(lVar7 + 0x78);
        if ((uVar10 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(lVar7 + 0x78);
        }
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar3) {
            *piVar1 = *piVar1 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        while (*piVar12 == -1) {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar12,0x10);
          if (bVar3) {
            *piVar12 = 0;
            cVar2 = ExclusiveMonitorsStatus();
          }
          if (cVar2 == '\0') goto code_r0x02041e18;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar12,0x10);
    if (bVar3) {
      *piVar12 = 0;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02041e18:
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar3) {
      *piVar1 = *piVar1 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
code_r0x02041e28:
  DataMemoryBarrier(2,3);
  if (*(long *)PTR__ZN4Aska19MemoryHandleManager15m_pGlobalMasterE_02cbe208 == 0) {
    lVar7 = 0;
  }
  else {
    lVar7 = 0;
    lVar9 = *(long *)PTR__ZN4Aska19MemoryHandleManager15m_pGlobalMasterE_02cbe208;
    do {
      while( true ) {
        while (lVar8 = lVar9, param_1 < *(ulong *)(lVar8 + 0x218)) {
          lVar9 = *(long *)(lVar8 + 0x268);
          while (lVar9 == 0) {
            if ((*(long *)(lVar8 + 0x260) == 0) ||
               (lVar9 = *(long *)(*(long *)(lVar8 + 0x260) + 0x268), lVar9 == 0))
            goto code_r0x02041eac;
          }
        }
        if (param_1 < *(long *)(lVar8 + 0x220) + *(ulong *)(lVar8 + 0x218)) break;
        lVar9 = *(long *)(lVar8 + 0x268);
        while (lVar9 == 0) {
          if ((*(long *)(lVar8 + 0x260) == 0) ||
             (lVar9 = *(long *)(*(long *)(lVar8 + 0x260) + 0x268), lVar9 == 0))
          goto code_r0x02041eac;
        }
      }
      lVar7 = lVar8;
      lVar9 = *(long *)(lVar8 + 600);
    } while (*(long *)(lVar8 + 600) != 0);
code_r0x02041eac:
    if ((param_2 != (undefined8 *)0x0) && (lVar7 != 0)) {
      uVar10 = param_1 >> 0x18 & 0xff;
      for (lVar9 = *(long *)(lVar7 + (ulong)((((((((int)uVar10 + (int)(uVar10 / 0x3b) * -0x3b) * 8 +
                                                 ((uint)(param_1 >> 0x10) & 0xff)) % 0x3b) * 8 +
                                               ((uint)(param_1 >> 8) & 0xff)) % 0x3b) * 8 +
                                             ((uint)param_1 & 0xff)) % 0x3b) * 8 + 0x10); lVar9 != 0
          ; lVar9 = *(long *)(lVar9 + 0x40)) {
        if (*(ulong *)(lVar9 + 8) == param_1) {
          uVar6 = *(undefined4 *)(lVar9 + 0x34);
          goto code_r0x02041f48;
        }
      }
      uVar6 = 0;
code_r0x02041f48:
      puVar5 = (undefined8 *)Aska::MemoryHandleManager::GetBlock(unsigned int) const(lVar7,uVar6);
      *param_2 = *puVar5;
    }
  }
  lVar9 = *(long *)puVar4;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar9 + 0x38) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar12 = (int *)(lVar9 + 0x3c);
  if (*piVar12 < 0x15) {
    return lVar7;
  }
  do {
    cVar2 = '\x01';
    bVar3 = (bool)ExclusiveMonitorPass(piVar12,0x10);
    if (bVar3) {
      *piVar12 = *piVar12 + -1;
      cVar2 = ExclusiveMonitorsStatus();
    }
  } while (cVar2 != '\0');
  uVar10 = Aska::Semaphore::IsReady() const(lVar9 + 0x78);
  if ((uVar10 & 1) == 0) {
    return lVar7;
  }
  Aska::Semaphore::Signal() const(lVar9 + 0x78);
  return lVar7;
}

// ==== Aska::MemoryHandleManager::StaticFree(void const*)
// vaddr 0x1f41fbc | ghidra 0x2041fbc | size 40 | symbol _ZN4Aska19MemoryHandleManager10StaticFreeEPKv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska19MemoryHandleManager10StaticFreeEPKv(undefined8 param_1)

{
  long lVar1;
  
  lVar1 = Aska::MemoryHandleManager::GetAllocatedManager(void const*, unsigned long*)(param_1,0);
  if (lVar1 != 0) {
    Aska::MemoryHandleManager::Free(void const*)(lVar1,param_1);
  }
  return lVar1 != 0;
}

// ==== Aska::MemoryHandleManager::Free(void const*)
// vaddr 0x1f41fe4 | ghidra 0x2041fe4 | size 492 | symbol _ZN4Aska19MemoryHandleManager4FreeEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager4FreeEPKv(long param_1,ulong param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  undefined8 uVar5;
  int iVar6;
  ulong uVar7;
  long lVar8;
  
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar6 = 0;
code_r0x02042000:
  if (*piVar1 == -1) {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x020420c8;
    goto code_r0x02042000;
  }
  ClearExclusiveLocal();
  bVar4 = iVar6 < 0x1ff;
  iVar6 = iVar6 + 1;
  if (bVar4) goto code_r0x02042000;
  piVar2 = (int *)(param_1 + 0x2ac);
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
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar7 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x2e8);
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
          if (cVar3 == '\0') goto code_r0x020420b8;
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
code_r0x020420b8:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x020420c8:
  uVar7 = param_2 >> 0x18 & 0xff;
  DataMemoryBarrier(2,3);
  lVar8 = *(long *)(param_1 + (ulong)((((((((int)uVar7 + (int)(uVar7 / 0x3b) * -0x3b) * 8 +
                                          ((uint)(param_2 >> 0x10) & 0xff)) % 0x3b) * 8 +
                                        ((uint)(param_2 >> 8) & 0xff)) % 0x3b) * 8 +
                                      ((uint)param_2 & 0xff)) % 0x3b) * 8 + 0x10);
  do {
    if (lVar8 == 0) {
code_r0x0204216c:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_1 + 0x2ac)) {
        piVar1 = (int *)(param_1 + 0x2ac);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar7 & 1) != 0) {
          (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x2e8);
          return;
        }
      }
      return;
    }
    if (*(ulong *)(lVar8 + 8) == param_2) {
      if (*(int *)(lVar8 + 0x34) != 0) {
        uVar5 = Aska::MemoryHandleManager::GetBlock(unsigned int) const(param_1);
        Aska::MemoryHandleManager::LocalFree(Aska::_MemoryHandleBlock*)(param_1,uVar5);
      }
      goto code_r0x0204216c;
    }
    lVar8 = *(long *)(lVar8 + 0x40);
  } while( true );
}

// ==== Aska::MemoryHandleManager::Malloc(unsigned long)
// vaddr 0x1f421d0 | ghidra 0x20421d0 | size 600 | symbol _ZN4Aska19MemoryHandleManager6MallocEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19MemoryHandleManager6MallocEm(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  undefined8 *puVar8;
  int iVar9;
  long unaff_x21;
  long lStack_90;
  long lStack_88;
  undefined8 uStack_80;
  int *piStack_78;
  long lStack_70;
  int iStack_64;
  
  if (param_2 == 0) {
    return 0;
  }
  if (*(char *)(param_1 + 8) == '\x01') {
    lVar5 = (*(code *)PTR__ZN4Aska19MemoryHandleManager10MallocHighEm_02caefb0)(param_1,param_2);
    return lVar5;
  }
  iStack_64 = 0;
  lVar5 = param_1;
code_r0x020422c8:
  piVar1 = (int *)(lVar5 + 0x2a8);
  iVar9 = 0;
code_r0x020422d0:
  do {
    if (*piVar1 == -1) goto code_r0x020422dc;
    ClearExclusiveLocal();
    bVar4 = iVar9 < 0x1ff;
    iVar9 = iVar9 + 1;
  } while (bVar4);
  piVar2 = (int *)(lVar5 + 0x2ac);
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
        uVar7 = Aska::Semaphore::IsReady() const(lVar5 + 0x2e8);
        if ((uVar7 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(lVar5 + 0x2e8);
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
          if (cVar3 == '\0') goto code_r0x020422b0;
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
code_r0x020422b0:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x0204232c;
code_r0x020422dc:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
  if (bVar4) {
    *piVar1 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02042324;
  goto code_r0x020422d0;
code_r0x02042324:
  DataMemoryBarrier(2,3);
code_r0x0204232c:
  lVar6 = Aska::_MemoryHandleBlock* Aska::_MemoryHandleLocalFunctions::LocalMalloc<false>(Aska::MemoryHandleManager*, Aska::_MemoryHandleBlock*, unsigned long)(lVar5,0,param_2 + 0xfU & 0xfffffffffffffff0);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar5 + 0x2a8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(lVar5 + 0x2ac);
  if (0x14 < *piVar1) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar7 = Aska::Semaphore::IsReady() const(lVar5 + 0x2e8);
    if ((uVar7 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar5 + 0x2e8);
    }
  }
  if (lVar6 == 0) {
    iVar9 = 3;
    if (*(long *)(lVar5 + 0x240) != param_1) {
      iVar9 = 0;
    }
    lVar5 = *(long *)(lVar5 + 0x240);
    if (iVar9 == 0) goto code_r0x020422c8;
  }
  else {
    unaff_x21 = *(long *)(lVar6 + 8);
    iVar9 = 1;
  }
  if (iVar9 != 3) {
    return unaff_x21;
  }
  if (0 < iStack_64) {
    return 0;
  }
  puVar8 = *(undefined8 **)(param_1 + 0x228);
  if (puVar8 == (undefined8 *)0x0) {
    return 0;
  }
  iStack_64 = iStack_64 + 1;
  uStack_80 = 4;
  lStack_70 = 0;
  lStack_90 = param_1;
  lStack_88 = param_2;
  piStack_78 = &iStack_64;
  (**(code **)*puVar8)(puVar8,&lStack_90);
  lVar5 = param_1;
  if (lStack_70 != 0) {
    return lStack_70;
  }
  goto code_r0x020422c8;
}

// ==== Aska::MemoryHandleManager::MallocHigh(unsigned long)
// vaddr 0x1f42428 | ghidra 0x2042428 | size 548 | symbol _ZN4Aska19MemoryHandleManager10MallocHighEm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19MemoryHandleManager10MallocHighEm(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  long lVar5;
  ulong uVar6;
  undefined8 *puVar7;
  int iVar8;
  long unaff_x21;
  long lVar9;
  long lStack_90;
  long lStack_88;
  undefined8 uStack_80;
  int *piStack_78;
  long lStack_70;
  int iStack_64;
  
  if (param_2 == 0) {
    return 0;
  }
  iStack_64 = 0;
  lVar9 = param_1;
code_r0x020424ec:
  piVar1 = (int *)(lVar9 + 0x2a8);
  iVar8 = 0;
code_r0x020424f4:
  do {
    if (*piVar1 == -1) goto code_r0x02042500;
    ClearExclusiveLocal();
    bVar4 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar4);
  piVar2 = (int *)(lVar9 + 0x2ac);
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
        uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x2e8);
        if ((uVar6 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(lVar9 + 0x2e8);
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
          if (cVar3 == '\0') goto code_r0x020424d4;
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
code_r0x020424d4:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x02042550;
code_r0x02042500:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
  if (bVar4) {
    *piVar1 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02042548;
  goto code_r0x020424f4;
code_r0x02042548:
  DataMemoryBarrier(2,3);
code_r0x02042550:
  lVar5 = Aska::_MemoryHandleBlock* Aska::_MemoryHandleLocalFunctions::LocalMallocHigh<false>(Aska::MemoryHandleManager*, Aska::_MemoryHandleBlock*, unsigned long)(lVar9,0,param_2 + 0xfU & 0xfffffffffffffff0);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar9 + 0x2a8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(lVar9 + 0x2ac);
  if (0x14 < *piVar1) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x2e8);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar9 + 0x2e8);
    }
  }
  if (lVar5 == 0) {
    iVar8 = 3;
    if (*(long *)(lVar9 + 0x240) != param_1) {
      iVar8 = 0;
    }
    lVar9 = *(long *)(lVar9 + 0x240);
    if (iVar8 == 0) goto code_r0x020424ec;
  }
  else {
    unaff_x21 = *(long *)(lVar5 + 8);
    iVar8 = 1;
  }
  if (iVar8 != 3) {
    return unaff_x21;
  }
  if (0 < iStack_64) {
    return 0;
  }
  puVar7 = *(undefined8 **)(param_1 + 0x228);
  if (puVar7 == (undefined8 *)0x0) {
    return 0;
  }
  iStack_64 = iStack_64 + 1;
  uStack_80 = 4;
  lStack_70 = 0;
  lStack_90 = param_1;
  lStack_88 = param_2;
  piStack_78 = &iStack_64;
  (**(code **)*puVar7)(puVar7,&lStack_90);
  lVar9 = param_1;
  if (lStack_70 != 0) {
    return lStack_70;
  }
  goto code_r0x020424ec;
}

// ==== Aska::MemoryHandleManager::AlignedMalloc(unsigned long, long)
// vaddr 0x1f4310c | ghidra 0x204310c | size 608 | symbol _ZN4Aska19MemoryHandleManager13AlignedMallocEml | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19MemoryHandleManager13AlignedMallocEml(long param_1,long param_2,long param_3)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  undefined8 *puVar8;
  int iVar9;
  long unaff_x21;
  ulong uVar10;
  long lStack_90;
  long lStack_88;
  ulong uStack_80;
  int *piStack_78;
  long lStack_70;
  int iStack_64;
  
  if (param_2 == 0) {
    return 0;
  }
  if (*(char *)(param_1 + 8) == '\x01') {
    lVar5 = (*(code *)PTR__ZN4Aska19MemoryHandleManager17AlignedMallocHighEml_02ca2d90)
                      (param_1,param_2);
    return lVar5;
  }
  uVar10 = param_3 + 3U & 0xfffffffffffffffc;
  iStack_64 = 0;
  lVar5 = param_1;
code_r0x02043208:
  piVar1 = (int *)(lVar5 + 0x2a8);
  iVar9 = 0;
code_r0x02043210:
  do {
    if (*piVar1 == -1) goto code_r0x0204321c;
    ClearExclusiveLocal();
    bVar4 = iVar9 < 0x1ff;
    iVar9 = iVar9 + 1;
  } while (bVar4);
  piVar2 = (int *)(lVar5 + 0x2ac);
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
        uVar7 = Aska::Semaphore::IsReady() const(lVar5 + 0x2e8);
        if ((uVar7 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(lVar5 + 0x2e8);
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
          if (cVar3 == '\0') goto code_r0x020431f0;
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
code_r0x020431f0:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x0204326c;
code_r0x0204321c:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
  if (bVar4) {
    *piVar1 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02043264;
  goto code_r0x02043210;
code_r0x02043264:
  DataMemoryBarrier(2,3);
code_r0x0204326c:
  lVar6 = Aska::_MemoryHandleBlock* Aska::_MemoryHandleLocalFunctions::LocalAlignedMalloc<false>(Aska::MemoryHandleManager*, Aska::_MemoryHandleBlock*, unsigned long, long)(lVar5,0,param_2 + 0xfU & 0xfffffffffffffff0,uVar10);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar5 + 0x2a8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(lVar5 + 0x2ac);
  if (0x14 < *piVar1) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar7 = Aska::Semaphore::IsReady() const(lVar5 + 0x2e8);
    if ((uVar7 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar5 + 0x2e8);
    }
  }
  if (lVar6 == 0) {
    iVar9 = 3;
    if (*(long *)(lVar5 + 0x240) != param_1) {
      iVar9 = 0;
    }
    lVar5 = *(long *)(lVar5 + 0x240);
    if (iVar9 == 0) goto code_r0x02043208;
  }
  else {
    unaff_x21 = *(long *)(lVar6 + 8);
    iVar9 = 1;
  }
  if (iVar9 != 3) {
    return unaff_x21;
  }
  if (0 < iStack_64) {
    return 0;
  }
  puVar8 = *(undefined8 **)(param_1 + 0x228);
  if (puVar8 == (undefined8 *)0x0) {
    return 0;
  }
  iStack_64 = iStack_64 + 1;
  piStack_78 = &iStack_64;
  lStack_70 = 0;
  lStack_90 = param_1;
  lStack_88 = param_2;
  uStack_80 = uVar10;
  (**(code **)*puVar8)(puVar8,&lStack_90);
  lVar5 = param_1;
  if (lStack_70 != 0) {
    return lStack_70;
  }
  goto code_r0x02043208;
}

// ==== Aska::MemoryHandleManager::AlignedMallocHigh(unsigned long, long)
// vaddr 0x1f4336c | ghidra 0x204336c | size 556 | symbol _ZN4Aska19MemoryHandleManager17AlignedMallocHighEml | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19MemoryHandleManager17AlignedMallocHighEml(long param_1,long param_2,long param_3)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  long lVar5;
  ulong uVar6;
  undefined8 *puVar7;
  int iVar8;
  long unaff_x21;
  ulong uVar9;
  long lVar10;
  long lStack_90;
  long lStack_88;
  ulong uStack_80;
  int *piStack_78;
  long lStack_70;
  int iStack_64;
  
  if (param_2 == 0) {
    return 0;
  }
  uVar9 = param_3 + 3U & 0xfffffffffffffffc;
  iStack_64 = 0;
  lVar10 = param_1;
code_r0x02043434:
  piVar1 = (int *)(lVar10 + 0x2a8);
  iVar8 = 0;
code_r0x0204343c:
  do {
    if (*piVar1 == -1) goto code_r0x02043448;
    ClearExclusiveLocal();
    bVar4 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar4);
  piVar2 = (int *)(lVar10 + 0x2ac);
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
        uVar6 = Aska::Semaphore::IsReady() const(lVar10 + 0x2e8);
        if ((uVar6 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(lVar10 + 0x2e8);
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
          if (cVar3 == '\0') goto code_r0x0204341c;
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
code_r0x0204341c:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x02043498;
code_r0x02043448:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
  if (bVar4) {
    *piVar1 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x02043490;
  goto code_r0x0204343c;
code_r0x02043490:
  DataMemoryBarrier(2,3);
code_r0x02043498:
  lVar5 = Aska::_MemoryHandleBlock* Aska::_MemoryHandleLocalFunctions::LocalAlignedMallocHigh<false>(Aska::MemoryHandleManager*, Aska::_MemoryHandleBlock*, unsigned long, long)(lVar10,0,param_2 + 0xfU & 0xfffffffffffffff0,uVar9);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar10 + 0x2a8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(lVar10 + 0x2ac);
  if (0x14 < *piVar1) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(lVar10 + 0x2e8);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar10 + 0x2e8);
    }
  }
  if (lVar5 == 0) {
    iVar8 = 3;
    if (*(long *)(lVar10 + 0x240) != param_1) {
      iVar8 = 0;
    }
    lVar10 = *(long *)(lVar10 + 0x240);
    if (iVar8 == 0) goto code_r0x02043434;
  }
  else {
    unaff_x21 = *(long *)(lVar5 + 8);
    iVar8 = 1;
  }
  if (iVar8 != 3) {
    return unaff_x21;
  }
  if (0 < iStack_64) {
    return 0;
  }
  puVar7 = *(undefined8 **)(param_1 + 0x228);
  if (puVar7 == (undefined8 *)0x0) {
    return 0;
  }
  iStack_64 = iStack_64 + 1;
  piStack_78 = &iStack_64;
  lStack_70 = 0;
  lStack_90 = param_1;
  lStack_88 = param_2;
  uStack_80 = uVar9;
  (**(code **)*puVar7)(puVar7,&lStack_90);
  lVar10 = param_1;
  if (lStack_70 != 0) {
    return lStack_70;
  }
  goto code_r0x02043434;
}

// ==== Aska::MemoryHandleManager::Realloc(unsigned long, void*, long)
// vaddr 0x1f44480 | ghidra 0x2044480 | size 3088 | symbol _ZN4Aska19MemoryHandleManager7ReallocEmPvl | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x02045010: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02045014) */
/* WARNING: Removing unreachable block (ram,0x0204501c) */
/* WARNING: Removing unreachable block (ram,0x02045024) */
/* WARNING: Removing unreachable block (ram,0x02045040) */
/* WARNING: Removing unreachable block (ram,0x02045074) */
/* WARNING: Removing unreachable block (ram,0x02045058) */
/* WARNING: Removing unreachable block (ram,0x02045068) */

ulong _ZN4Aska19MemoryHandleManager7ReallocEmPvl
                (long param_1,long param_2,ulong param_3,ulong param_4)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  char cVar6;
  ulong *puVar7;
  long lVar8;
  int iVar9;
  ulong uVar10;
  long lVar11;
  ulong uVar12;
  long *plVar13;
  undefined8 *puVar14;
  long *plVar15;
  ulong uVar16;
  ulong *puVar17;
  long lVar18;
  long lVar19;
  undefined1 *puVar20;
  long lVar21;
  undefined1 *puVar22;
  undefined4 uVar23;
  undefined8 *puVar24;
  ulong uVar25;
  ulong uVar26;
  long *plVar27;
  long *plVar28;
  ulong uVar29;
  ulong *puVar30;
  
  if (param_3 == 0) {
code_r0x011de570:
    uVar10 = (*(code *)PTR__ZN4Aska19MemoryHandleManager13AlignedMallocEml_02ca72a8)
                       (param_1,param_2,param_4);
    return uVar10;
  }
  uVar10 = param_3 >> 0x18 & 0xff;
  lVar11 = *(long *)(param_1 + (ulong)((((((((int)uVar10 + (int)(uVar10 / 0x3b) * -0x3b) * 8 +
                                           ((uint)(param_3 >> 0x10) & 0xff)) % 0x3b) * 8 +
                                         ((uint)(param_3 >> 8) & 0xff)) % 0x3b) * 8 +
                                       ((uint)param_3 & 0xff)) % 0x3b) * 8 + 0x10);
  while( true ) {
    if (lVar11 == 0) {
      return 0;
    }
    if (*(ulong *)(lVar11 + 8) == param_3) break;
    lVar11 = *(long *)(lVar11 + 0x40);
  }
  if (*(int *)(lVar11 + 0x34) == 0) {
    return 0;
  }
  puVar7 = (ulong *)Aska::MemoryHandleManager::GetBlock(unsigned int) const(param_1);
  if (param_2 == 0) {
    Aska::MemoryHandleManager::LocalFree(Aska::_MemoryHandleBlock*)(param_1,puVar7);
    return 0;
  }
  uVar10 = *puVar7;
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar9 = 0;
code_r0x02044584:
  if (*piVar1 == -1) {
    cVar6 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = 0;
      cVar6 = ExclusiveMonitorsStatus();
    }
    if (cVar6 == '\0') goto code_r0x02044680;
    goto code_r0x02044584;
  }
  ClearExclusiveLocal();
  bVar5 = iVar9 < 0x1ff;
  iVar9 = iVar9 + 1;
  if (bVar5) goto code_r0x02044584;
  piVar2 = (int *)(param_1 + 0x2ac);
  do {
    cVar6 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + 1;
      cVar6 = ExclusiveMonitorsStatus();
    }
  } while (cVar6 != '\0');
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      do {
        uVar25 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar25 & 1) == 0) {
          do {
            cVar6 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar5) {
              *piVar2 = *piVar2 + -1;
              cVar6 = ExclusiveMonitorsStatus();
            }
          } while (cVar6 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x2e8);
        }
        do {
          cVar6 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = *piVar2 + 1;
            cVar6 = ExclusiveMonitorsStatus();
          }
        } while (cVar6 != '\0');
        while (*piVar1 == -1) {
          cVar6 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = 0;
            cVar6 = ExclusiveMonitorsStatus();
          }
          if (cVar6 == '\0') goto code_r0x02044670;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar6 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = 0;
      cVar6 = ExclusiveMonitorsStatus();
    }
  } while (cVar6 != '\0');
code_r0x02044670:
  do {
    cVar6 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar6 = ExclusiveMonitorsStatus();
    }
  } while (cVar6 != '\0');
code_r0x02044680:
  DataMemoryBarrier(2,3);
  uVar26 = param_2 + 0xfU & 0xfffffffffffffff0;
  uVar25 = uVar10 - uVar26;
  if (uVar26 <= uVar10 && uVar25 != 0) {
    uVar16 = puVar7[1];
    uVar10 = 0;
    if (param_4 != 0) {
      uVar10 = uVar16 / param_4;
    }
    if (uVar16 != uVar10 * param_4) goto code_r0x020448bc;
    uVar16 = uVar16 - *(long *)(param_1 + 0x218) >> 0x10;
    plVar28 = (long *)(*(long *)(param_1 + 0x1e8) + uVar16 * 0x30 + 0x28);
    uVar10 = uVar16;
    do {
      plVar15 = plVar28;
      uVar29 = uVar10;
      if ((char)plVar15[-5] != '\0') break;
      bVar5 = 0 < (long)uVar10;
      plVar28 = plVar15 + -6;
      uVar29 = uVar16;
      uVar10 = uVar10 - 1;
    } while (bVar5);
    puVar30 = *(ulong **)(param_1 + 0x208);
    uVar10 = *(ulong *)(*(long *)(param_1 + 0x1e8) + uVar29 * 0x30 + 0x28);
    puVar17 = (ulong *)puVar30[2];
    if (puVar30 == puVar17) {
      if (*(char *)(param_1 + 0x230) != '\0') {
        lVar11 = ((long)*(int *)(*(long *)(param_1 + 0x200) + 0x10) +
                 (long)*(int *)(*(long *)(param_1 + 0x200) + 0x14)) * 0x48;
        if (*(long *)(param_1 + 0x210) == 0) {
          lVar19 = operator new[](unsigned long, std::nothrow_t const&)(lVar11 + 0x18,PTR__ZSt7nothrow_02cb9a80);
        }
        else {
          lVar19 = Aska::MemoryManager::Malloc(unsigned long)();
        }
        if (lVar19 != 0) {
          Aska::MemoryHandleManager::AddUnusedMemoryBlockChunk(Aska::MemoryHandleManager::_UnusedMemoryBlockChunk*, unsigned long)(param_1,lVar19,lVar11);
          puVar17 = (ulong *)puVar30[2];
          goto code_r0x02044704;
        }
      }
    }
    else {
code_r0x02044704:
      uVar16 = puVar30[3];
      puVar17[3] = uVar16;
      *(ulong **)(uVar16 + 0x10) = puVar17;
      *(ulong **)(param_1 + 0x208) = puVar17;
      *(undefined1 *)((long)puVar30 + 0x31) = 0;
      if (puVar30 != (ulong *)0x0) {
        uVar12 = puVar7[1];
        plVar28 = plVar15 + -5;
        *puVar30 = uVar25;
        puVar30[1] = uVar12 + uVar26;
        uVar16 = uVar10;
        do {
          uVar16 = *(ulong *)(uVar16 + 0x20);
          if (uVar16 == uVar10) break;
        } while (*(ulong *)(uVar16 + 8) < uVar12 + uVar26);
        uVar10 = *(ulong *)(uVar16 + 0x28);
        puVar30[4] = uVar16;
        puVar30[5] = uVar10;
        *(ulong **)(uVar10 + 0x20) = puVar30;
        *(ulong **)(puVar30[4] + 0x28) = puVar30;
        uVar10 = puVar7[2];
        puVar30[2] = uVar10;
        puVar30[3] = (ulong)puVar7;
        *(ulong **)(uVar10 + 0x18) = puVar30;
        *(ulong **)(puVar30[3] + 0x10) = puVar30;
        *puVar7 = uVar26;
        plVar13 = (long *)puVar30[2];
        if (*(char *)((long)plVar13 + 0x31) == '\0') {
          *puVar30 = *puVar30 + *plVar13;
          puVar30[2] = plVar13[2];
          puVar30[4] = plVar13[4];
          *(ulong **)(plVar13[2] + 0x18) = puVar30;
          *(ulong **)(plVar13[4] + 0x28) = puVar30;
          if (plVar13 != (long *)0x0) {
            lVar11 = *(long *)(param_1 + 0x208);
            lVar19 = *(long *)(lVar11 + 0x18);
            *(long **)(lVar11 + 0x18) = plVar13;
            plVar13[2] = lVar11;
            *(long **)(lVar19 + 0x10) = plVar13;
            plVar13[3] = lVar19;
          }
        }
        *(undefined1 *)((long)puVar30 + 0x31) = 0;
        lVar11 = plVar15[-3];
        lVar19 = plVar15[-2];
        plVar15[-3] = lVar11 - uVar25;
        plVar15[-2] = lVar19 + uVar25;
        if (lVar11 - uVar25 == 0) {
          lVar11 = *(long *)(param_1 + 0x1e8);
          if ((long)plVar15 - lVar11 != 0x28) {
            uVar3 = *(uint *)(plVar15 + -4);
            if (*(long *)(lVar11 + (ulong)uVar3 * 0x30 + 0x10) == 0) {
              lVar18 = (ulong)uVar3 * 0x30;
              *(undefined1 *)(plVar15 + -5) = 0;
              plVar28 = (long *)(lVar11 + lVar18);
              lVar11 = plVar28[3] + lVar19 + uVar25;
              plVar28[3] = lVar11;
              **(long **)(*(long *)(*(long *)(param_1 + 0x1e8) + lVar18 + 0x28) + 0x20) = lVar11;
              *(undefined4 *)((long)plVar28 + 4) = *(undefined4 *)((long)plVar15 + -0x24);
              *(uint *)(*(long *)(param_1 + 0x1e8) + (ulong)*(uint *)((long)plVar15 + -0x24) * 0x30
                       + 8) = uVar3;
              lVar11 = *plVar15;
              lVar19 = *(long *)(lVar11 + 0x10);
              if (lVar19 != 0) {
                lVar18 = *(long *)(param_1 + 0x208);
                lVar8 = *(long *)(lVar18 + 0x18);
                *(long *)(lVar18 + 0x18) = lVar19;
                *(long *)(lVar19 + 0x10) = lVar18;
                *(long *)(lVar8 + 0x10) = lVar19;
                *(long *)(lVar19 + 0x18) = lVar8;
              }
              if (lVar11 != 0) {
                lVar19 = *(long *)(param_1 + 0x208);
                lVar18 = *(long *)(lVar19 + 0x18);
                *(long *)(lVar19 + 0x18) = lVar11;
                *(long *)(lVar11 + 0x10) = lVar19;
                *(long *)(lVar18 + 0x10) = lVar11;
                *(long *)(lVar11 + 0x18) = lVar18;
              }
            }
          }
          uVar3 = *(uint *)((long)plVar28 + 4);
          if ((uVar3 != 0) &&
             (*(long *)(*(long *)(param_1 + 0x1e8) + (ulong)uVar3 * 0x30 + 0x10) == 0)) {
            puVar20 = (undefined1 *)(*(long *)(param_1 + 0x1e8) + (ulong)uVar3 * 0x30);
            *puVar20 = 0;
            *(undefined4 *)((long)plVar28 + 4) = *(undefined4 *)(puVar20 + 4);
            *(undefined4 *)(*(long *)(param_1 + 0x1e8) + (ulong)*(uint *)(puVar20 + 4) * 0x30 + 8) =
                 *(undefined4 *)(puVar20 + 8);
            plVar28[3] = *(long *)(puVar20 + 0x18) + plVar28[3] + 0x48;
            lVar19 = *(long *)(puVar20 + 0x28);
            lVar18 = *(long *)(lVar19 + 0x10);
            lVar11 = *(long *)(*(long *)(param_1 + 0x1e8) + (ulong)*(uint *)(puVar20 + 8) * 0x30 +
                              0x28);
            if (lVar18 != 0) {
              lVar8 = *(long *)(param_1 + 0x208);
              lVar21 = *(long *)(lVar8 + 0x18);
              *(long *)(lVar8 + 0x18) = lVar18;
              *(long *)(lVar18 + 0x10) = lVar8;
              *(long *)(lVar21 + 0x10) = lVar18;
              *(long *)(lVar18 + 0x18) = lVar21;
            }
            if (lVar19 != 0) {
              lVar18 = *(long *)(param_1 + 0x208);
              lVar8 = *(long *)(lVar18 + 0x18);
              *(long *)(lVar18 + 0x18) = lVar19;
              *(long *)(lVar19 + 0x10) = lVar18;
              *(long *)(lVar8 + 0x10) = lVar19;
              *(long *)(lVar19 + 0x18) = lVar8;
            }
            **(long **)(lVar11 + 0x20) = plVar28[3];
          }
code_r0x02044f64:
          puVar17 = (ulong *)plVar28[5];
          puVar30 = (ulong *)puVar17[4];
          if (puVar30 == puVar17) {
            uVar10 = 0;
          }
          else {
            uVar25 = 0;
            do {
              uVar10 = *puVar30;
              puVar30 = (ulong *)puVar30[4];
              if (uVar10 <= uVar25) {
                uVar10 = uVar25;
              }
              uVar25 = uVar10;
            } while (puVar30 != puVar17);
          }
          plVar28[4] = uVar10;
          goto code_r0x02044fa4;
        }
        uVar10 = puVar30[1];
        if (uVar10 <= *(ulong *)(puVar30[2] + 8)) goto code_r0x02044f64;
        uVar25 = (uVar10 - *(long *)(param_1 + 0x218)) + 0xffff;
        uVar26 = uVar25 >> 0x10;
        if ((long)uVar26 <= (long)uVar29) goto code_r0x02044f64;
        lVar11 = *(long *)(param_1 + 0x218) + (uVar25 & 0xffffffffffff0000);
        uVar10 = lVar11 - uVar10;
        lVar19 = *puVar30 - uVar10;
        if (*puVar30 < uVar10 || lVar19 == 0) goto code_r0x02044f64;
        puVar24 = *(undefined8 **)(param_1 + 0x208);
        puVar14 = (undefined8 *)puVar24[2];
        if (puVar24 == puVar14) {
          if (*(char *)(param_1 + 0x230) == '\0') {
            puVar24 = (undefined8 *)0x0;
          }
          else {
            lVar18 = ((long)*(int *)(*(long *)(param_1 + 0x200) + 0x10) +
                     (long)*(int *)(*(long *)(param_1 + 0x200) + 0x14)) * 0x48;
            if (*(long *)(param_1 + 0x210) == 0) {
              lVar8 = operator new[](unsigned long, std::nothrow_t const&)(lVar18 + 0x18,PTR__ZSt7nothrow_02cb9a80);
            }
            else {
              lVar8 = Aska::MemoryManager::Malloc(unsigned long)();
            }
            if (lVar8 != 0) {
              Aska::MemoryHandleManager::AddUnusedMemoryBlockChunk(Aska::MemoryHandleManager::_UnusedMemoryBlockChunk*, unsigned long)(param_1,lVar8,lVar18);
              puVar14 = (undefined8 *)puVar24[2];
              goto code_r0x02044838;
            }
            puVar24 = (undefined8 *)0x0;
          }
        }
        else {
code_r0x02044838:
          lVar18 = puVar24[3];
          puVar14[3] = lVar18;
          *(undefined8 **)(lVar18 + 0x10) = puVar14;
          *(undefined8 **)(param_1 + 0x208) = puVar14;
          *(undefined1 *)((long)puVar24 + 0x31) = 0;
        }
        plVar27 = *(long **)(param_1 + 0x208);
        plVar13 = (long *)plVar27[2];
        if (plVar27 != plVar13) {
code_r0x0204485c:
          lVar18 = plVar27[3];
          cVar6 = plVar27 == (long *)0x0;
          plVar13[3] = lVar18;
          *(long **)(lVar18 + 0x10) = plVar13;
          *(long **)(param_1 + 0x208) = plVar13;
          *(undefined1 *)((long)plVar27 + 0x31) = 0;
          if ((puVar24 == (undefined8 *)0x0) || (plVar27 == (long *)0x0)) {
            if (puVar24 != (undefined8 *)0x0) goto code_r0x02044e70;
            goto code_r0x02044e94;
          }
          if (uVar10 == 0) {
            uVar10 = puVar30[3];
            *(ulong *)(uVar10 + 0x10) = puVar30[2];
            *(ulong *)(puVar30[2] + 0x18) = uVar10;
            *(ulong *)(puVar30[5] + 0x20) = puVar30[4];
            *(ulong *)(puVar30[4] + 0x28) = puVar30[5];
          }
          else {
            *puVar30 = uVar10;
          }
          lVar18 = *(long *)(param_1 + 0x1e8);
          *(undefined2 *)(puVar24 + 6) = 0x100;
          puVar20 = (undefined1 *)(lVar18 + uVar26 * 0x30);
          *puVar24 = 0;
          puVar24[1] = lVar11;
          puVar17 = (ulong *)(puVar20 + 0x28);
          *puVar17 = (ulong)puVar24;
          puVar24[4] = plVar27;
          puVar24[5] = plVar27;
          puVar24[2] = plVar27;
          puVar24[3] = plVar27;
          *plVar27 = lVar19;
          *(undefined2 *)(plVar27 + 6) = 0;
          plVar27[4] = (long)puVar24;
          plVar27[5] = (long)puVar24;
          plVar27[2] = (long)puVar24;
          plVar27[3] = (long)puVar24;
          plVar27[1] = puVar24[1];
          plVar15[-2] = plVar15[-2] - lVar19;
          *(undefined4 *)(puVar20 + 4) = *(undefined4 *)((long)plVar15 + -0x24);
          uVar23 = (undefined4)(uVar25 >> 0x10);
          *(undefined4 *)
           (*(long *)(param_1 + 0x1e8) + (ulong)*(uint *)((long)plVar15 + -0x24) * 0x30 + 8) =
               uVar23;
          *(undefined4 *)((long)plVar15 + -0x24) = uVar23;
          uVar10 = (ulong)*(uint *)(puVar20 + 4);
          *(int *)(puVar20 + 8) = (int)uVar29;
          *puVar20 = 1;
          *(undefined8 *)(puVar20 + 0x10) = 0;
          if (*(uint *)(puVar20 + 4) == 0) {
            lVar11 = *(long *)(param_1 + 0x220) - (uVar25 & 0xffffffffffff0000);
code_r0x02044dbc:
            *(long *)(lVar18 + uVar26 * 0x30 + 0x18) = lVar11;
          }
          else {
            if (*(long *)(*(long *)(param_1 + 0x1e8) + uVar10 * 0x30 + 0x10) != 0) {
              lVar11 = (uVar10 - uVar26) * 0x10000;
              goto code_r0x02044dbc;
            }
            puVar22 = (undefined1 *)(*(long *)(param_1 + 0x1e8) + uVar10 * 0x30);
            *(undefined4 *)(puVar20 + 4) = *(undefined4 *)(puVar22 + 4);
            *(undefined4 *)(*(long *)(param_1 + 0x1e8) + (ulong)*(uint *)(puVar22 + 4) * 0x30 + 8) =
                 uVar23;
            *puVar22 = 0;
            lVar19 = *(long *)(puVar22 + 0x18) + (uVar10 - uVar26) * 0x10000;
            *(long *)(lVar18 + uVar26 * 0x30 + 0x18) = lVar19;
            *(undefined2 *)(puVar24 + 6) = 0x100;
            *puVar24 = 0;
            puVar24[1] = lVar11;
            *puVar17 = (ulong)puVar24;
            puVar24[4] = plVar27;
            puVar24[5] = plVar27;
            puVar24[2] = plVar27;
            puVar24[3] = plVar27;
            *plVar27 = lVar19;
            *(undefined2 *)(plVar27 + 6) = 0;
            plVar27[4] = (long)puVar24;
            plVar27[5] = (long)puVar24;
            plVar27[2] = (long)puVar24;
            plVar27[3] = (long)puVar24;
            plVar27[1] = puVar24[1];
          }
          puVar17 = (ulong *)*puVar17;
          puVar30 = (ulong *)puVar17[4];
          if (puVar30 == puVar17) {
            uVar10 = 0;
          }
          else {
            uVar25 = 0;
            do {
              uVar10 = *puVar30;
              puVar30 = (ulong *)puVar30[4];
              if (uVar10 <= uVar25) {
                uVar10 = uVar25;
              }
              uVar25 = uVar10;
            } while (puVar30 != puVar17);
          }
          *(ulong *)(lVar18 + uVar26 * 0x30 + 0x20) = uVar10;
          goto code_r0x02044f64;
        }
        if (*(char *)(param_1 + 0x230) != '\0') {
          lVar18 = ((long)*(int *)(*(long *)(param_1 + 0x200) + 0x10) +
                   (long)*(int *)(*(long *)(param_1 + 0x200) + 0x14)) * 0x48;
          if (*(long *)(param_1 + 0x210) == 0) {
            lVar8 = operator new[](unsigned long, std::nothrow_t const&)(lVar18 + 0x18,PTR__ZSt7nothrow_02cb9a80);
          }
          else {
            lVar8 = Aska::MemoryManager::Malloc(unsigned long)();
          }
          if (lVar8 != 0) {
            Aska::MemoryHandleManager::AddUnusedMemoryBlockChunk(Aska::MemoryHandleManager::_UnusedMemoryBlockChunk*, unsigned long)(param_1,lVar8,lVar18);
            plVar13 = (long *)plVar27[2];
            goto code_r0x0204485c;
          }
        }
        cVar6 = true;
        if (puVar24 == (undefined8 *)0x0) {
          uVar25 = 0;
          goto code_r0x02044fac;
        }
        plVar27 = (long *)0x0;
code_r0x02044e70:
        lVar11 = *(long *)(param_1 + 0x208);
        lVar19 = *(long *)(lVar11 + 0x18);
        *(undefined8 **)(lVar11 + 0x18) = puVar24;
        puVar24[2] = lVar11;
        *(undefined8 **)(lVar19 + 0x10) = puVar24;
        puVar24[3] = lVar19;
        if ((bool)cVar6 == false) {
code_r0x02044e94:
          lVar11 = *(long *)(param_1 + 0x208);
          lVar19 = *(long *)(lVar11 + 0x18);
          *(long **)(lVar11 + 0x18) = plVar27;
          plVar27[2] = lVar11;
          *(long **)(lVar19 + 0x10) = plVar27;
          plVar27[3] = lVar19;
        }
        uVar25 = 0;
        goto code_r0x02044fa8;
      }
    }
    cVar6 = '\0';
  }
  else if (uVar26 <= uVar10) {
code_r0x02044fa4:
    uVar25 = puVar7[1];
code_r0x02044fa8:
    cVar6 = '\x01';
  }
  else {
    plVar28 = (long *)puVar7[2];
    if (*(char *)((long)plVar28 + 0x31) == '\0') {
      uVar16 = 0;
      if (param_4 != 0) {
        uVar16 = puVar7[1] / param_4;
      }
      if (puVar7[1] == uVar16 * param_4) {
        uVar16 = *plVar28 + uVar10;
        if (uVar26 <= uVar16) {
          uVar29 = plVar28[2];
          if (uVar16 - uVar26 != 0) {
            plVar13 = *(long **)(param_1 + 0x208);
            uVar25 = plVar28[4];
            plVar15 = (long *)plVar13[2];
            if (plVar13 == plVar15) {
              if (*(char *)(param_1 + 0x230) != '\0') {
                lVar11 = ((long)*(int *)(*(long *)(param_1 + 0x200) + 0x10) +
                         (long)*(int *)(*(long *)(param_1 + 0x200) + 0x14)) * 0x48;
                if (*(long *)(param_1 + 0x210) == 0) {
                  lVar19 = operator new[](unsigned long, std::nothrow_t const&)(lVar11 + 0x18,PTR__ZSt7nothrow_02cb9a80);
                }
                else {
                  lVar19 = Aska::MemoryManager::Malloc(unsigned long)();
                }
                if (lVar19 != 0) {
                  Aska::MemoryHandleManager::AddUnusedMemoryBlockChunk(Aska::MemoryHandleManager::_UnusedMemoryBlockChunk*, unsigned long)(param_1,lVar19,lVar11);
                  plVar15 = (long *)plVar13[2];
                  goto code_r0x02044aa4;
                }
              }
            }
            else {
code_r0x02044aa4:
              lVar11 = plVar13[3];
              plVar15[3] = lVar11;
              *(long **)(lVar11 + 0x10) = plVar15;
              *(long **)(param_1 + 0x208) = plVar15;
              *(undefined1 *)((long)plVar13 + 0x31) = 0;
              if (plVar13 != (long *)0x0) {
                uVar12 = puVar7[1];
                lVar11 = plVar28[5];
                *(undefined1 *)((long)plVar13 + 0x31) = 0;
                plVar13[2] = uVar29;
                plVar13[3] = (long)puVar7;
                plVar13[4] = uVar25;
                plVar13[5] = lVar11;
                *plVar13 = uVar16 - uVar26;
                plVar13[1] = uVar12 + uVar26;
                *(long **)(lVar11 + 0x20) = plVar13;
                *(long **)(plVar13[4] + 0x28) = plVar13;
                *puVar7 = uVar26;
                puVar7[2] = (ulong)plVar13;
                *(long **)(uVar29 + 0x18) = plVar13;
                uVar16 = uVar26;
                goto code_r0x02044b40;
              }
            }
            cVar6 = '\a';
            goto code_r0x02044fac;
          }
          *puVar7 = uVar16;
          puVar7[2] = uVar29;
          *(ulong **)(uVar29 + 0x18) = puVar7;
          *(long *)(plVar28[5] + 0x20) = plVar28[4];
          *(long *)(plVar28[4] + 0x28) = plVar28[5];
code_r0x02044b40:
          uVar25 = puVar7[1] - *(long *)(param_1 + 0x218) >> 0x10;
          lVar11 = uVar25 + 1;
          plVar28 = (long *)(*(long *)(param_1 + 0x1e8) + uVar25 * 0x30 + 0x18);
          do {
            plVar15 = plVar28;
            if ((char)plVar15[-3] != '\0') break;
            lVar11 = lVar11 + -1;
            plVar28 = plVar15 + -6;
          } while (0 < lVar11);
          puVar17 = (ulong *)plVar15[2];
          plVar15[-1] = plVar15[-1] + (uVar16 - uVar10);
          *plVar15 = *plVar15 - (uVar16 - uVar10);
          puVar30 = (ulong *)puVar17[4];
          if (puVar30 == puVar17) {
            uVar10 = 0;
          }
          else {
            uVar25 = 0;
            do {
              uVar10 = *puVar30;
              puVar30 = (ulong *)puVar30[4];
              if (uVar10 <= uVar25) {
                uVar10 = uVar25;
              }
              uVar25 = uVar10;
            } while (puVar30 != puVar17);
          }
          plVar15[1] = uVar10;
          goto code_r0x02044fa4;
        }
      }
    }
code_r0x020448bc:
    cVar6 = '\0';
  }
code_r0x02044fac:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x2ac)) {
    piVar1 = (int *)(param_1 + 0x2ac);
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar10 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
    if ((uVar10 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x2e8);
    }
  }
  if ((cVar6 != '\a') && (cVar6 != '\0')) {
    return uVar25;
  }
  goto code_r0x011de570;
}

// ==== Aska::MemoryHandleManager::LocalFreeBlock(Aska::_MemoryHandleBlock*)
// vaddr 0x1f45090 | ghidra 0x2045090 | size 4 | symbol _ZN4Aska19MemoryHandleManager14LocalFreeBlockEPNS_18_MemoryHandleBlockE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager14LocalFreeBlockEPNS_18_MemoryHandleBlockE(void)

{
  (*(code *)PTR__ZN4Aska19MemoryHandleManager9LocalFreeEPNS_18_MemoryHandleBlockE_02cb3f68)();
  return;
}

// ==== Aska::MemoryHandleManager::IsCreated() const
// vaddr 0x1f45094 | ghidra 0x2045094 | size 356 | symbol _ZNK4Aska19MemoryHandleManager9IsCreatedEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska19MemoryHandleManager9IsCreatedEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  int iVar6;
  long lVar7;
  undefined4 uVar8;
  
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar6 = 0;
code_r0x020450ac:
  if (*piVar1 == -1) {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x02045174;
    goto code_r0x020450ac;
  }
  ClearExclusiveLocal();
  bVar4 = iVar6 < 0x1ff;
  iVar6 = iVar6 + 1;
  if (bVar4) goto code_r0x020450ac;
  piVar2 = (int *)(param_1 + 0x2ac);
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
        uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
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
          Aska::Semaphore::Wait() const(param_1 + 0x2e8);
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
          if (cVar3 == '\0') goto code_r0x02045164;
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
code_r0x02045164:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02045174:
  DataMemoryBarrier(2,3);
  lVar7 = param_1;
  do {
    if (*(long *)(lVar7 + 0x218) != 0) {
      uVar8 = 1;
      goto code_r0x0204519c;
    }
    lVar7 = *(long *)(lVar7 + 0x240);
  } while (lVar7 != param_1);
  uVar8 = 0;
code_r0x0204519c:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x2ac)) {
    piVar1 = (int *)(param_1 + 0x2ac);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar5 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
    if ((uVar5 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x2e8);
    }
  }
  return uVar8;
}

// ==== Aska::MemoryHandleManager::CalcFreeSize(long*, long*) const
// vaddr 0x1f451f8 | ghidra 0x20451f8 | size 508 | symbol _ZNK4Aska19MemoryHandleManager12CalcFreeSizeEPlS1_ | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZNK4Aska19MemoryHandleManager12CalcFreeSizeEPlS1_(long param_1,long *param_2,long *param_3)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  ulong uVar6;
  int iVar7;
  ulong uVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  
  uVar5 = Aska::MemoryHandleManager::IsCreated() const();
  if ((uVar5 & 1) == 0) {
    *param_2 = 0;
    *param_3 = 0;
    return 0;
  }
  lVar10 = 0;
  lVar11 = 0;
  uVar5 = 0;
  lVar12 = param_1;
code_r0x020452c8:
  piVar1 = (int *)(lVar12 + 0x2a8);
  iVar7 = 0;
code_r0x020452d0:
  do {
    if (*piVar1 == -1) goto code_r0x020452dc;
    ClearExclusiveLocal();
    bVar4 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar4);
  piVar2 = (int *)(lVar12 + 0x2ac);
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
        uVar6 = Aska::Semaphore::IsReady() const(lVar12 + 0x2e8);
        if ((uVar6 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(lVar12 + 0x2e8);
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
          if (cVar3 == '\0') goto code_r0x020452a8;
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
code_r0x020452a8:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x02045330;
code_r0x020452dc:
  cVar3 = '\x01';
  bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
  if (bVar4) {
    *piVar1 = 0;
    cVar3 = ExclusiveMonitorsStatus();
  }
  if (cVar3 == '\0') goto code_r0x0204532c;
  goto code_r0x020452d0;
code_r0x0204532c:
  DataMemoryBarrier(2,3);
code_r0x02045330:
  uVar8 = 0;
  uVar6 = uVar5;
  do {
    lVar9 = *(long *)(lVar12 + 0x1e8) + uVar8 * 0x30;
    uVar8 = (ulong)*(uint *)(lVar9 + 4);
    uVar5 = *(ulong *)(lVar9 + 0x20);
    if ((long)*(ulong *)(lVar9 + 0x20) <= (long)uVar6) {
      uVar5 = uVar6;
    }
    lVar11 = *(long *)(lVar9 + 0x18) + lVar11;
    uVar6 = uVar5;
  } while (*(uint *)(lVar9 + 4) != 0);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(lVar12 + 0x2a8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  lVar10 = *(long *)(lVar12 + 0x220) + lVar10;
  if (0x14 < *(int *)(lVar12 + 0x2ac)) {
    piVar1 = (int *)(lVar12 + 0x2ac);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(lVar12 + 0x2e8);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar12 + 0x2e8);
    }
  }
  lVar12 = *(long *)(lVar12 + 0x240);
  if (lVar12 == param_1) {
    if (param_2 != (long *)0x0) {
      *param_2 = lVar10;
    }
    if (param_3 != (long *)0x0) {
      *param_3 = lVar10 - lVar11;
    }
    return uVar5 & ((long)uVar5 >> 0x3f ^ 0xffffffffffffffffU);
  }
  goto code_r0x020452c8;
}

// ==== Aska::MemoryHandleManager::CountFreeBlocks()
// vaddr 0x1f453f4 | ghidra 0x20453f4 | size 424 | symbol _ZN4Aska19MemoryHandleManager15CountFreeBlocksEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska19MemoryHandleManager15CountFreeBlocksEv(long param_1)

{
  char *pcVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  int iVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  int iVar11;
  long lVar12;
  
  iVar11 = 0;
  lVar12 = param_1;
  do {
    piVar2 = (int *)(lVar12 + 0x2a8);
    iVar7 = 0;
code_r0x02045424:
    if (*piVar2 == -1) {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar6) {
        *piVar2 = 0;
        cVar5 = ExclusiveMonitorsStatus();
      }
      if (cVar5 == '\0') goto code_r0x020454ec;
      goto code_r0x02045424;
    }
    ClearExclusiveLocal();
    bVar6 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
    if (bVar6) goto code_r0x02045424;
    piVar3 = (int *)(lVar12 + 0x2ac);
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
      if (bVar6) {
        *piVar3 = *piVar3 + 1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    do {
      if (*piVar2 != -1) {
        ClearExclusiveLocal();
        do {
          uVar8 = Aska::Semaphore::IsReady() const(lVar12 + 0x2e8);
          if ((uVar8 & 1) == 0) {
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
            Aska::Semaphore::Wait() const(lVar12 + 0x2e8);
          }
          do {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
            if (bVar6) {
              *piVar3 = *piVar3 + 1;
              cVar5 = ExclusiveMonitorsStatus();
            }
          } while (cVar5 != '\0');
          while (*piVar2 == -1) {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar6) {
              *piVar2 = 0;
              cVar5 = ExclusiveMonitorsStatus();
            }
            if (cVar5 == '\0') goto code_r0x020454dc;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar6) {
        *piVar2 = 0;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
code_r0x020454dc:
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar3,0x10);
      if (bVar6) {
        *piVar3 = *piVar3 + -1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
code_r0x020454ec:
    DataMemoryBarrier(2,3);
    uVar8 = 0;
    do {
      uVar9 = *(ulong *)(*(long *)(lVar12 + 0x1e8) + uVar8 * 0x30 + 0x28);
      uVar10 = *(ulong *)(uVar9 + 0x20);
      while (uVar9 < uVar10) {
        pcVar1 = (char *)(uVar10 + 0x31);
        uVar10 = *(ulong *)(uVar10 + 0x20);
        if (*pcVar1 == '\0') {
          iVar11 = iVar11 + 1;
        }
      }
      uVar4 = *(uint *)(*(long *)(lVar12 + 0x1e8) + uVar8 * 0x30 + 4);
      uVar8 = (ulong)uVar4;
    } while (uVar4 != 0);
    DataMemoryBarrier(2,3);
    *(undefined4 *)(lVar12 + 0x2a8) = 0xffffffff;
    DataMemoryBarrier(2,3);
    if (0x14 < *(int *)(lVar12 + 0x2ac)) {
      piVar2 = (int *)(lVar12 + 0x2ac);
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar6) {
          *piVar2 = *piVar2 + -1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
      uVar8 = Aska::Semaphore::IsReady() const(lVar12 + 0x2e8);
      if ((uVar8 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar12 + 0x2e8);
      }
    }
    lVar12 = *(long *)(lVar12 + 0x240);
    if (lVar12 == param_1) {
      return iVar11;
    }
  } while( true );
}

// ==== Aska::MemoryHandleManager::IsEmpty(bool) const
// vaddr 0x1f4559c | ghidra 0x204559c | size 816 | symbol _ZNK4Aska19MemoryHandleManager7IsEmptyEb | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska19MemoryHandleManager7IsEmptyEb(long param_1,uint param_2)

{
  long *plVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  long lVar9;
  
  uVar6 = Aska::MemoryHandleManager::IsCreated() const();
  if ((uVar6 & 1) == 0) {
    return 1;
  }
  lVar9 = param_1;
  if ((param_2 & 1) == 0) {
    do {
      piVar8 = (int *)(lVar9 + 0x2a8);
      iVar7 = 0;
code_r0x02045630:
      if (*piVar8 == -1) {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar5) {
          *piVar8 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
        if (cVar4 == '\0') goto code_r0x020456f8;
        goto code_r0x02045630;
      }
      ClearExclusiveLocal();
      bVar5 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
      if (bVar5) goto code_r0x02045630;
      piVar2 = (int *)(lVar9 + 0x2ac);
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + 1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      do {
        if (*piVar8 != -1) {
          ClearExclusiveLocal();
          do {
            uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x2e8);
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
              Aska::Semaphore::Wait() const(lVar9 + 0x2e8);
            }
            do {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar5) {
                *piVar2 = *piVar2 + 1;
                cVar4 = ExclusiveMonitorsStatus();
              }
            } while (cVar4 != '\0');
            while (*piVar8 == -1) {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
              if (bVar5) {
                *piVar8 = 0;
                cVar4 = ExclusiveMonitorsStatus();
              }
              if (cVar4 == '\0') goto code_r0x020456e8;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar5) {
          *piVar8 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x020456e8:
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x020456f8:
      DataMemoryBarrier(2,3);
      uVar6 = 0;
      do {
        if (*(long *)(*(long *)(lVar9 + 0x1e8) + uVar6 * 0x30 + 0x10) != 0) goto code_r0x02045864;
        uVar3 = *(uint *)(*(long *)(lVar9 + 0x1e8) + uVar6 * 0x30 + 4);
        uVar6 = (ulong)uVar3;
      } while (uVar3 != 0);
      DataMemoryBarrier(2,3);
      *(undefined4 *)(lVar9 + 0x2a8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(lVar9 + 0x2ac)) {
        piVar8 = (int *)(lVar9 + 0x2ac);
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar5) {
            *piVar8 = *piVar8 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x2e8);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(lVar9 + 0x2e8);
        }
      }
      plVar1 = (long *)(lVar9 + 0x240);
      lVar9 = *plVar1;
      if (*plVar1 == param_1) {
        return 1;
      }
    } while( true );
  }
  piVar8 = (int *)(param_1 + 0x2a8);
  iVar7 = 0;
  do {
    while (*piVar8 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar5) {
        *piVar8 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x020457e8;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x2ac);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  do {
    if (*piVar8 != -1) {
      ClearExclusiveLocal();
      do {
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
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
          Aska::Semaphore::Wait() const(param_1 + 0x2e8);
        }
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar5) {
            *piVar2 = *piVar2 + 1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        while (*piVar8 == -1) {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
          if (bVar5) {
            *piVar8 = 0;
            cVar4 = ExclusiveMonitorsStatus();
          }
          if (cVar4 == '\0') goto code_r0x020457d8;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
    if (bVar5) {
      *piVar8 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x020457d8:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x020457e8:
  DataMemoryBarrier(2,3);
  uVar6 = 0;
  while (*(long *)(*(long *)(param_1 + 0x1e8) + uVar6 * 0x30 + 0x10) == 0) {
    uVar3 = *(uint *)(*(long *)(param_1 + 0x1e8) + uVar6 * 0x30 + 4);
    uVar6 = (ulong)uVar3;
    if (uVar3 == 0) {
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (*(int *)(param_1 + 0x2ac) < 0x15) {
        return 1;
      }
      piVar8 = (int *)(param_1 + 0x2ac);
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar5) {
          *piVar8 = *piVar8 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
      if ((uVar6 & 1) == 0) {
        return 1;
      }
      Aska::Semaphore::Signal() const(param_1 + 0x2e8);
      return 1;
    }
  }
code_r0x02045864:
  DataMemoryBarrier(2,3);
  *piVar8 = -1;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(lVar9 + 0x2ac)) {
    piVar8 = (int *)(lVar9 + 0x2ac);
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar5) {
        *piVar8 = *piVar8 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x2e8);
    if ((uVar6 & 1) != 0) {
      Aska::Semaphore::Signal() const(lVar9 + 0x2e8);
    }
  }
  return 0;
}

// ==== Aska::MemoryHandleManager::CalcFreeSize(bool)
// vaddr 0x1f458cc | ghidra 0x20458cc | size 756 | symbol _ZN4Aska19MemoryHandleManager12CalcFreeSizeEb | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19MemoryHandleManager12CalcFreeSizeEb(long param_1,uint param_2)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  
  uVar6 = Aska::MemoryHandleManager::IsCreated() const();
  if ((uVar6 & 1) == 0) {
    return 0;
  }
  if ((param_2 & 1) == 0) {
    lVar10 = 0;
    lVar9 = param_1;
    do {
      piVar1 = (int *)(lVar9 + 0x2a8);
      iVar7 = 0;
code_r0x02045968:
      if (*piVar1 == -1) {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
        if (cVar4 == '\0') goto code_r0x02045a30;
        goto code_r0x02045968;
      }
      ClearExclusiveLocal();
      bVar5 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
      if (bVar5) goto code_r0x02045968;
      piVar2 = (int *)(lVar9 + 0x2ac);
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
            uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x2e8);
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
              Aska::Semaphore::Wait() const(lVar9 + 0x2e8);
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
              if (cVar4 == '\0') goto code_r0x02045a20;
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
code_r0x02045a20:
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x02045a30:
      DataMemoryBarrier(2,3);
      uVar6 = 0;
      Hint_Prefetch(*(undefined8 *)(lVar9 + 0x240),0,2,0);
      do {
        lVar8 = *(long *)(lVar9 + 0x1e8) + uVar6 * 0x30;
        uVar3 = *(uint *)(lVar8 + 4);
        uVar6 = (ulong)uVar3;
        lVar10 = *(long *)(lVar8 + 0x18) + lVar10;
      } while (uVar3 != 0);
      DataMemoryBarrier(2,3);
      *(undefined4 *)(lVar9 + 0x2a8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(lVar9 + 0x2ac)) {
        piVar1 = (int *)(lVar9 + 0x2ac);
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(lVar9 + 0x2e8);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(lVar9 + 0x2e8);
        }
      }
      lVar9 = *(long *)(lVar9 + 0x240);
      if (lVar9 == param_1) {
        return lVar10;
      }
    } while( true );
  }
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar7 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x02045b24;
    }
    ClearExclusiveLocal();
    bVar5 = iVar7 < 0x1ff;
    iVar7 = iVar7 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x2ac);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
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
          Aska::Semaphore::Wait() const(param_1 + 0x2e8);
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
          if (cVar4 == '\0') goto code_r0x02045b14;
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
code_r0x02045b14:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x02045b24:
  DataMemoryBarrier(2,3);
  lVar10 = 0;
  uVar6 = 0;
  Hint_Prefetch(*(undefined8 *)(param_1 + 0x240),0,2,0);
  do {
    lVar9 = *(long *)(param_1 + 0x1e8) + uVar6 * 0x30;
    uVar3 = *(uint *)(lVar9 + 4);
    uVar6 = (ulong)uVar3;
    lVar10 = *(long *)(lVar9 + 0x18) + lVar10;
  } while (uVar3 != 0);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (*(int *)(param_1 + 0x2ac) < 0x15) {
    return lVar10;
  }
  piVar1 = (int *)(param_1 + 0x2ac);
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
  if ((uVar6 & 1) == 0) {
    return lVar10;
  }
  Aska::Semaphore::Signal() const(param_1 + 0x2e8);
  return lVar10;
}

// ==== Aska::MemoryHandleManager::PrintMemoryChain()
// vaddr 0x1f45bc0 | ghidra 0x2045bc0 | size 4 | symbol _ZN4Aska19MemoryHandleManager16PrintMemoryChainEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager16PrintMemoryChainEv(void)

{
  return;
}

// ==== Aska::MemoryHandleManager::PrintMemoryChain(char const*)
// vaddr 0x1f45bc4 | ghidra 0x2045bc4 | size 4 | symbol _ZN4Aska19MemoryHandleManager16PrintMemoryChainEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager16PrintMemoryChainEPKc(void)

{
  return;
}

// ==== Aska::MemoryHandleManager::SearchNextBlock(Aska::MemoryHandleManager::_Srbk**, Aska::_MemoryHandleBlock**, bool)
// vaddr 0x1f45bc8 | ghidra 0x2045bc8 | size 588 | symbol _ZN4Aska19MemoryHandleManager15SearchNextBlockEPPNS0_5_SrbkEPPNS_18_MemoryHandleBlockEb | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska19MemoryHandleManager15SearchNextBlockEPPNS0_5_SrbkEPPNS_18_MemoryHandleBlockEb
               (long param_1,long *param_2,long *param_3,uint param_4)

{
  int *piVar1;
  int *piVar2;
  long lVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  bool bVar7;
  ulong uVar8;
  int iVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  uint uVar14;
  long lVar15;
  long lVar16;
  
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar9 = 0;
  do {
    while (*piVar1 == -1) {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar6) {
        *piVar1 = 0;
        cVar5 = ExclusiveMonitorsStatus();
      }
      if (cVar5 == '\0') goto code_r0x02045cb8;
    }
    ClearExclusiveLocal();
    bVar6 = iVar9 < 0x1ff;
    iVar9 = iVar9 + 1;
  } while (bVar6);
  piVar2 = (int *)(param_1 + 0x2ac);
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar6) {
      *piVar2 = *piVar2 + 1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      do {
        uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar8 & 1) == 0) {
          do {
            cVar5 = '\x01';
            bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar6) {
              *piVar2 = *piVar2 + -1;
              cVar5 = ExclusiveMonitorsStatus();
            }
          } while (cVar5 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x2e8);
        }
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar6) {
            *piVar2 = *piVar2 + 1;
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
          if (cVar5 == '\0') goto code_r0x02045ca8;
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
code_r0x02045ca8:
  do {
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar6) {
      *piVar2 = *piVar2 + -1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
code_r0x02045cb8:
  DataMemoryBarrier(2,3);
  lVar11 = *param_2;
  lVar12 = *(long *)(param_1 + 0x1e8);
  lVar10 = *param_3;
  lVar3 = lVar12;
  if (lVar11 != 0) {
    lVar3 = lVar11;
  }
  uVar4 = *(uint *)(lVar3 + 4);
  uVar14 = *(uint *)(lVar12 + (ulong)uVar4 * 0x30 + 8);
  lVar13 = 0;
  if (lVar11 != 0) {
    lVar13 = lVar10;
  }
  if ((param_4 & 1) == 0) {
    do {
      lVar16 = *(long *)(lVar12 + (ulong)uVar14 * 0x30 + 0x28);
      if (lVar13 == 0) {
        lVar13 = *(long *)(lVar16 + 0x10);
      }
      if (lVar13 != lVar16) {
code_r0x02045d98:
        *param_2 = lVar3;
        *param_3 = lVar13;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
        DataMemoryBarrier(2,3);
        bVar6 = lVar10 != lVar13 || lVar11 != lVar3;
        if (*(int *)(param_1 + 0x2ac) < 0x15) {
          return bVar6;
        }
        piVar1 = (int *)(param_1 + 0x2ac);
        do {
          cVar5 = '\x01';
          bVar7 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar7) {
            *piVar1 = *piVar1 + -1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar8 & 1) == 0) {
          return bVar6;
        }
        Aska::Semaphore::Signal() const(param_1 + 0x2e8);
        return bVar6;
      }
      lVar13 = 0;
      uVar14 = uVar4;
    } while (uVar4 != 0);
  }
  else {
    do {
      lVar15 = *(long *)(lVar12 + (ulong)uVar14 * 0x30 + 0x28);
      lVar16 = lVar15;
      if (lVar13 != 0) goto code_r0x02045d00;
      while( true ) {
        lVar13 = *(long *)(lVar16 + 0x10);
code_r0x02045d00:
        if (lVar13 == lVar15) break;
        lVar16 = lVar13;
        if (*(char *)(lVar13 + 0x31) == '\0') goto code_r0x02045d98;
      }
      lVar13 = 0;
      uVar14 = uVar4;
    } while (uVar4 != 0);
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x2ac)) {
    piVar1 = (int *)(param_1 + 0x2ac);
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar6) {
        *piVar1 = *piVar1 + -1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
    if ((uVar8 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x2e8);
    }
  }
  return false;
}

// ==== Aska::MemoryHandleManager::Add(Aska::MemoryHandleManager*)
// vaddr 0x1f45e14 | ghidra 0x2045e14 | size 92 | symbol _ZN4Aska19MemoryHandleManager3AddEPS0_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska19MemoryHandleManager3AddEPS0_(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  if (param_2 != 0) {
    lVar1 = *(long *)(param_2 + 0x238);
    lVar2 = param_2;
    do {
      *(undefined8 *)(lVar2 + 0x238) = *(undefined8 *)(param_1 + 0x238);
      lVar2 = *(long *)(lVar2 + 0x240);
    } while (lVar2 != param_2);
    *(undefined8 *)(*(long *)(lVar1 + 0x248) + 0x240) = *(undefined8 *)(param_1 + 0x238);
    *(undefined8 *)(lVar1 + 0x248) = *(undefined8 *)(*(long *)(param_1 + 0x238) + 0x248);
    *(long *)(*(long *)(*(long *)(param_1 + 0x238) + 0x248) + 0x240) = lVar1;
    *(long *)(*(long *)(param_1 + 0x238) + 0x248) = lVar1;
    return 1;
  }
  return 0;
}

// ==== Aska::MemoryHandleManager::LocalFree(Aska::_MemoryHandleBlock*)
// vaddr 0x1f45e70 | ghidra 0x2045e70 | size 1332 | symbol _ZN4Aska19MemoryHandleManager9LocalFreeEPNS_18_MemoryHandleBlockE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager9LocalFreeEPNS_18_MemoryHandleBlockE(long param_1,long *param_2)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  ulong *puVar8;
  undefined1 *puVar9;
  ulong uVar10;
  long *plVar11;
  ulong uVar12;
  long lVar13;
  long *plVar14;
  ulong *puVar15;
  ulong uVar16;
  long *plVar17;
  long *plVar18;
  long lVar19;
  long *plVar20;
  long lVar21;
  
  if (*(char *)((long)param_2 + 0x31) == '\0') {
    return;
  }
  lVar21 = *param_2;
  if (param_2[7] != 0) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
    DataMemoryBarrier(2,3);
    piVar1 = (int *)(param_1 + 0x2ac);
    if (0x14 < *(int *)(param_1 + 0x2ac)) {
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = *piVar1 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x2e8);
      }
    }
    piVar2 = (int *)(param_1 + 0x2a8);
    (**(code **)(*(long *)param_2[7] + 8))((long *)param_2[7],param_2[1]);
    iVar7 = 0;
    do {
      while (*piVar2 == -1) {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = 0;
          cVar4 = ExclusiveMonitorsStatus();
        }
        if (cVar4 == '\0') goto code_r0x02045fd0;
      }
      ClearExclusiveLocal();
      bVar5 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
    } while (bVar5);
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + 1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    do {
      if (*piVar2 != -1) {
        ClearExclusiveLocal();
        do {
          uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
          if ((uVar6 & 1) == 0) {
            do {
              cVar4 = '\x01';
              bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar5) {
                *piVar1 = *piVar1 + -1;
                cVar4 = ExclusiveMonitorsStatus();
              }
            } while (cVar4 != '\0');
            Aska::Thread::Sleep(unsigned int)(1);
          }
          else {
            Aska::Semaphore::Wait() const(param_1 + 0x2e8);
          }
          do {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar5) {
              *piVar1 = *piVar1 + 1;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          while (*piVar2 == -1) {
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar5) {
              *piVar2 = 0;
              cVar4 = ExclusiveMonitorsStatus();
            }
            if (cVar4 == '\0') goto code_r0x02045fc0;
          }
          ClearExclusiveLocal();
        } while( true );
      }
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
      if (bVar5) {
        *piVar2 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
code_r0x02045fc0:
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
code_r0x02045fd0:
    DataMemoryBarrier(2,3);
    param_2[7] = 0;
    if (*(char *)((long)param_2 + 0x31) == '\0') {
      return;
    }
  }
  uVar10 = param_2[1];
  uVar16 = uVar10 - *(long *)(param_1 + 0x218) >> 0x10;
  uVar6 = uVar16;
  plVar11 = (long *)(*(long *)(param_1 + 0x1e8) + uVar16 * 0x30 + 0x28);
  do {
    plVar20 = plVar11;
    uVar12 = uVar6;
    if ((char)plVar20[-5] != '\0') break;
    bVar5 = 0 < (long)uVar6;
    uVar12 = uVar16;
    uVar6 = uVar6 - 1;
    plVar11 = plVar20 + -6;
  } while (bVar5);
  uVar6 = uVar10 >> 0x18 & 0xff;
  plVar11 = (long *)(param_1 + (ulong)((((((((int)uVar6 + (int)(uVar6 / 0x3b) * -0x3b) * 8 +
                                           ((uint)(uVar10 >> 0x10) & 0xff)) % 0x3b) * 8 +
                                         ((uint)(uVar10 >> 8) & 0xff)) % 0x3b) * 8 +
                                       ((uint)uVar10 & 0xff)) % 0x3b) * 8 + 0x10);
  plVar17 = (long *)*plVar11;
  if (plVar17 != (long *)0x0) {
    plVar14 = (long *)0x0;
    do {
      plVar18 = plVar17;
      if (plVar18 == param_2) {
        if (plVar14 != (long *)0x0) {
          plVar11 = plVar14 + 8;
        }
        *plVar11 = param_2[8];
        param_2[8] = 0;
        break;
      }
      plVar17 = (long *)plVar18[8];
      plVar14 = plVar18;
    } while ((long *)plVar18[8] != (long *)0x0);
  }
  plVar17 = (long *)param_2[3];
  plVar11 = plVar20 + -5;
  if (*(char *)((long)plVar17 + 0x31) == '\0') {
    plVar17[2] = param_2[2];
    *(long **)(param_2[2] + 0x18) = plVar17;
    *plVar17 = *plVar17 + lVar21;
    *(undefined1 *)((long)param_2 + 0x31) = 0;
    lVar19 = *(long *)(param_1 + 0x208);
    lVar13 = *(long *)(lVar19 + 0x18);
    *(long **)(lVar19 + 0x18) = param_2;
    param_2[2] = lVar19;
    *(long **)(lVar13 + 0x10) = param_2;
    param_2[3] = lVar13;
  }
  else {
    lVar19 = param_2[2];
    if (*(char *)(lVar19 + 0x31) == '\0') {
      param_2[4] = lVar19;
      lVar13 = *(long *)(lVar19 + 0x28);
    }
    else {
      lVar13 = *(long *)(*(long *)(param_1 + 0x1e8) + uVar12 * 0x30 + 0x28);
      lVar19 = lVar13;
      do {
        lVar19 = *(long *)(lVar19 + 0x20);
        if (lVar19 == lVar13) break;
      } while (*(ulong *)(lVar19 + 8) < (ulong)param_2[1]);
      lVar13 = *(long *)(lVar19 + 0x28);
      param_2[4] = lVar19;
    }
    param_2[5] = lVar13;
    *(long **)(lVar19 + 0x28) = param_2;
    *(long **)(param_2[5] + 0x20) = param_2;
    plVar17 = param_2;
  }
  plVar14 = (long *)plVar17[2];
  if (*(char *)((long)plVar14 + 0x31) == '\0') {
    *plVar17 = *plVar17 + *plVar14;
    plVar17[2] = plVar14[2];
    plVar17[4] = plVar14[4];
    *(long **)(plVar17[5] + 0x20) = plVar17;
    *(long **)(plVar14[4] + 0x28) = plVar17;
    *(long **)(plVar14[2] + 0x18) = plVar17;
    if (plVar14 != (long *)0x0) {
      lVar19 = *(long *)(param_1 + 0x208);
      lVar13 = *(long *)(lVar19 + 0x18);
      *(long **)(lVar19 + 0x18) = plVar14;
      plVar14[2] = lVar19;
      *(long **)(lVar13 + 0x10) = plVar14;
      plVar14[3] = lVar13;
    }
  }
  *(undefined1 *)((long)plVar17 + 0x31) = 0;
  lVar19 = plVar20[-3];
  lVar13 = plVar20[-2];
  plVar20[-3] = lVar19 - lVar21;
  plVar20[-2] = lVar13 + lVar21;
  if (lVar19 - lVar21 == 0) {
    lVar19 = *(long *)(param_1 + 0x1e8);
    if ((long)plVar20 - lVar19 != 0x28) {
      uVar3 = *(uint *)(plVar20 + -4);
      plVar17 = (long *)(lVar19 + (ulong)uVar3 * 0x30);
      if (plVar17[2] == 0) {
        *(undefined1 *)(plVar20 + -5) = 0;
        lVar19 = lVar19 + (ulong)uVar3 * 0x30;
        lVar21 = *(long *)(lVar19 + 0x18) + lVar13 + lVar21;
        *(long *)(lVar19 + 0x18) = lVar21;
        **(long **)(*(long *)(lVar19 + 0x28) + 0x20) = lVar21;
        *(undefined4 *)(lVar19 + 4) = *(undefined4 *)((long)plVar20 + -0x24);
        *(uint *)(*(long *)(param_1 + 0x1e8) + (ulong)*(uint *)((long)plVar20 + -0x24) * 0x30 + 8) =
             uVar3;
        lVar21 = *plVar20;
        lVar19 = *(long *)(lVar21 + 0x10);
        if (lVar19 != 0) {
          lVar21 = *(long *)(param_1 + 0x208);
          lVar13 = *(long *)(lVar21 + 0x18);
          *(long *)(lVar21 + 0x18) = lVar19;
          *(long *)(lVar19 + 0x10) = lVar21;
          *(long *)(lVar13 + 0x10) = lVar19;
          *(long *)(lVar19 + 0x18) = lVar13;
          lVar21 = *plVar20;
        }
        plVar11 = plVar17;
        if (lVar21 != 0) {
          lVar19 = *(long *)(param_1 + 0x208);
          lVar13 = *(long *)(lVar19 + 0x18);
          *(long *)(lVar19 + 0x18) = lVar21;
          *(long *)(lVar21 + 0x10) = lVar19;
          *(long *)(lVar13 + 0x10) = lVar21;
          *(long *)(lVar21 + 0x18) = lVar13;
        }
      }
    }
    uVar3 = *(uint *)((long)plVar11 + 4);
    if ((uVar3 != 0) && (*(long *)(*(long *)(param_1 + 0x1e8) + (ulong)uVar3 * 0x30 + 0x10) == 0)) {
      puVar9 = (undefined1 *)(*(long *)(param_1 + 0x1e8) + (ulong)uVar3 * 0x30);
      *puVar9 = 0;
      *(undefined4 *)((long)plVar11 + 4) = *(undefined4 *)(puVar9 + 4);
      *(undefined4 *)(*(long *)(param_1 + 0x1e8) + (ulong)*(uint *)(puVar9 + 4) * 0x30 + 8) =
           *(undefined4 *)(puVar9 + 8);
      lVar21 = *(long *)(puVar9 + 0x18);
      lVar19 = plVar11[3];
      plVar11[3] = lVar19 + lVar21;
      **(long **)(*(long *)(*(long *)(param_1 + 0x1e8) + (ulong)*(uint *)(puVar9 + 8) * 0x30 + 0x28)
                 + 0x20) = lVar19 + lVar21;
      lVar21 = *(long *)(puVar9 + 0x28);
      lVar19 = *(long *)(lVar21 + 0x10);
      if (lVar19 != 0) {
        lVar21 = *(long *)(param_1 + 0x208);
        lVar13 = *(long *)(lVar21 + 0x18);
        *(long *)(lVar21 + 0x18) = lVar19;
        *(long *)(lVar19 + 0x10) = lVar21;
        *(long *)(lVar13 + 0x10) = lVar19;
        *(long *)(lVar19 + 0x18) = lVar13;
        lVar21 = *(long *)(puVar9 + 0x28);
      }
      if (lVar21 != 0) {
        lVar19 = *(long *)(param_1 + 0x208);
        lVar13 = *(long *)(lVar19 + 0x18);
        *(long *)(lVar19 + 0x18) = lVar21;
        *(long *)(lVar21 + 0x10) = lVar19;
        *(long *)(lVar13 + 0x10) = lVar21;
        *(long *)(lVar21 + 0x18) = lVar13;
      }
    }
  }
  puVar8 = (ulong *)plVar11[5];
  puVar15 = (ulong *)puVar8[4];
  if (puVar15 == puVar8) {
    uVar6 = 0;
  }
  else {
    uVar10 = 0;
    do {
      uVar6 = *puVar15;
      puVar15 = (ulong *)puVar15[4];
      if (uVar6 <= uVar10) {
        uVar6 = uVar10;
      }
      uVar10 = uVar6;
    } while (puVar15 != puVar8);
  }
  plVar11[4] = uVar6;
  return;
}

// ==== Aska::MemoryHandleManager::Move(unsigned int)
// vaddr 0x1f463a4 | ghidra 0x20463a4 | size 368 | symbol _ZN4Aska19MemoryHandleManager4MoveEj | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska19MemoryHandleManager4MoveEj(long param_1,undefined4 param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar8 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02046488;
    }
    ClearExclusiveLocal();
    bVar4 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0x2ac);
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
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar7 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x2e8);
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
          if (cVar3 == '\0') goto code_r0x02046478;
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
code_r0x02046478:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02046488:
  DataMemoryBarrier(2,3);
  lVar6 = Aska::MemoryHandleManager::GetBlock(unsigned int) const(param_1,param_2);
  if (lVar6 == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = Aska::MemoryHandleManager::LocalMove(Aska::_MemoryHandleBlock&)(param_1,lVar6);
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x2ac)) {
    piVar1 = (int *)(param_1 + 0x2ac);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
    if ((uVar7 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x2e8);
    }
  }
  return uVar5 & 1;
}

// ==== Aska::MemoryHandleManager::LocalMove(Aska::_MemoryHandleBlock&)
// vaddr 0x1f46514 | ghidra 0x2046514 | size 860 | symbol _ZN4Aska19MemoryHandleManager9LocalMoveERNS_18_MemoryHandleBlockE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska19MemoryHandleManager9LocalMoveERNS_18_MemoryHandleBlockE(long param_1,undefined8 *param_2)

{
  long lVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined8 *puVar5;
  long lVar6;
  undefined8 *puVar7;
  long *plVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  undefined8 uVar11;
  undefined1 auStack_78 [72];
  
  uVar11 = *param_2;
  if ((ulong)*(byte *)((long)param_2 + 0x32) == 0) {
    puVar5 = (undefined8 *)Aska::_MemoryHandleBlock* Aska::_MemoryHandleLocalFunctions::LocalMalloc<true>(Aska::MemoryHandleManager*, Aska::_MemoryHandleBlock*, unsigned long)(param_1,param_2,uVar11);
  }
  else {
    puVar5 = (undefined8 *)
             Aska::_MemoryHandleBlock* Aska::_MemoryHandleLocalFunctions::LocalAlignedMalloc<true>(Aska::MemoryHandleManager*, Aska::_MemoryHandleBlock*, unsigned long, long)(param_1,param_2,uVar11,
                             0x80000000L >> ((ulong)*(byte *)((long)param_2 + 0x32) & 0x3f));
  }
  if (puVar5 == (undefined8 *)0x0) {
    uVar11 = 0;
  }
  else {
    memcpy(puVar5[1],param_2[1],uVar11);
    uVar2 = *(uint *)(puVar5 + 1);
    plVar8 = (long *)(param_1 + (ulong)((((((((uVar2 >> 0x18) % 0x3b) * 8 + (uVar2 >> 0x10 & 0xff))
                                           % 0x3b) * 8 + (uVar2 >> 8 & 0xff)) % 0x3b) * 8 +
                                        (uVar2 & 0xff)) % 0x3b) * 8 + 0x10);
    puVar10 = (undefined8 *)*plVar8;
    if (puVar10 != (undefined8 *)0x0) {
      puVar9 = (undefined8 *)0x0;
      do {
        puVar7 = puVar10;
        if (puVar7 == puVar5) {
          if (puVar9 != (undefined8 *)0x0) {
            plVar8 = puVar9 + 8;
          }
          *plVar8 = puVar5[8];
          puVar5[8] = 0;
          break;
        }
        puVar10 = (undefined8 *)puVar7[8];
        puVar9 = puVar7;
      } while ((undefined8 *)puVar7[8] != (undefined8 *)0x0);
    }
    uVar2 = *(uint *)(param_2 + 1);
    plVar8 = (long *)(param_1 + (ulong)((((((((uVar2 >> 0x18) % 0x3b) * 8 + (uVar2 >> 0x10 & 0xff))
                                           % 0x3b) * 8 + (uVar2 >> 8 & 0xff)) % 0x3b) * 8 +
                                        (uVar2 & 0xff)) % 0x3b) * 8 + 0x10);
    puVar10 = (undefined8 *)*plVar8;
    if (puVar10 != (undefined8 *)0x0) {
      puVar9 = (undefined8 *)0x0;
      do {
        puVar7 = puVar10;
        if (puVar7 == param_2) {
          if (puVar9 != (undefined8 *)0x0) {
            plVar8 = puVar9 + 8;
          }
          *plVar8 = param_2[8];
          param_2[8] = 0;
          break;
        }
        puVar10 = (undefined8 *)puVar7[8];
        puVar9 = puVar7;
      } while ((undefined8 *)puVar7[8] != (undefined8 *)0x0);
    }
    memcpy(auStack_78,puVar5,0x48);
    uVar3 = *(undefined4 *)((long)puVar5 + 0x34);
    uVar4 = *(undefined4 *)((long)param_2 + 0x34);
    memcpy(puVar5,param_2,0x48);
    memcpy(param_2,auStack_78,0x48);
    *(undefined4 *)((long)puVar5 + 0x34) = uVar3;
    *(undefined4 *)((long)param_2 + 0x34) = uVar4;
    puVar10 = (undefined8 *)puVar5[3];
    if ((undefined8 *)puVar5[3] == puVar5) {
      puVar5[3] = param_2;
      puVar10 = param_2;
    }
    puVar10[2] = puVar5;
    puVar10 = (undefined8 *)puVar5[2];
    if ((undefined8 *)puVar5[2] == puVar5) {
      puVar5[2] = param_2;
      puVar10 = param_2;
    }
    puVar10[3] = puVar5;
    puVar10 = (undefined8 *)param_2[3];
    if ((undefined8 *)param_2[3] == param_2) {
      param_2[3] = puVar5;
      puVar10 = puVar5;
    }
    puVar10[2] = param_2;
    puVar10 = (undefined8 *)param_2[2];
    if ((undefined8 *)param_2[2] == param_2) {
      param_2[2] = puVar5;
      puVar10 = puVar5;
    }
    puVar10[3] = param_2;
    uVar2 = *(uint *)(puVar5 + 1);
    lVar1 = param_1 + 0x10;
    lVar6 = (ulong)((((((((uVar2 >> 0x18) % 0x3b) * 8 + (uVar2 >> 0x10 & 0xff)) % 0x3b) * 8 +
                      (uVar2 >> 8 & 0xff)) % 0x3b) * 8 + (uVar2 & 0xff)) % 0x3b) * 8;
    puVar5[8] = *(undefined8 *)(lVar1 + lVar6);
    *(undefined8 **)(lVar1 + lVar6) = puVar5;
    uVar2 = *(uint *)(param_2 + 1);
    lVar6 = (ulong)((((((((uVar2 >> 0x18) % 0x3b) * 8 + (uVar2 >> 0x10 & 0xff)) % 0x3b) * 8 +
                      (uVar2 >> 8 & 0xff)) % 0x3b) * 8 + (uVar2 & 0xff)) % 0x3b) * 8;
    param_2[8] = *(undefined8 *)(lVar1 + lVar6);
    *(undefined8 **)(lVar1 + lVar6) = param_2;
    Aska::MemoryHandleManager::LocalFree(Aska::_MemoryHandleBlock*)(param_1,puVar5);
    uVar11 = 1;
  }
  return uVar11;
}

// ==== Aska::MemoryHandleManager::MoveToHigh(unsigned int)
// vaddr 0x1f46870 | ghidra 0x2046870 | size 368 | symbol _ZN4Aska19MemoryHandleManager10MoveToHighEj | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska19MemoryHandleManager10MoveToHighEj(long param_1,undefined4 param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar8 = 0;
  do {
    while (*piVar1 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02046954;
    }
    ClearExclusiveLocal();
    bVar4 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar4);
  piVar2 = (int *)(param_1 + 0x2ac);
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
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar7 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x2e8);
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
          if (cVar3 == '\0') goto code_r0x02046944;
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
code_r0x02046944:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02046954:
  DataMemoryBarrier(2,3);
  lVar6 = Aska::MemoryHandleManager::GetBlock(unsigned int) const(param_1,param_2);
  if (lVar6 == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = Aska::MemoryHandleManager::LocalMoveToHigh(Aska::_MemoryHandleBlock&)(param_1,lVar6);
  }
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x2ac)) {
    piVar1 = (int *)(param_1 + 0x2ac);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
    if ((uVar7 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x2e8);
    }
  }
  return uVar5 & 1;
}

// ==== Aska::MemoryHandleManager::LocalMoveToHigh(Aska::_MemoryHandleBlock&)
// vaddr 0x1f469e0 | ghidra 0x20469e0 | size 860 | symbol _ZN4Aska19MemoryHandleManager15LocalMoveToHighERNS_18_MemoryHandleBlockE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska19MemoryHandleManager15LocalMoveToHighERNS_18_MemoryHandleBlockE
          (long param_1,undefined8 *param_2)

{
  long lVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined8 *puVar5;
  long lVar6;
  undefined8 *puVar7;
  long *plVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  undefined8 uVar11;
  undefined1 auStack_78 [72];
  
  uVar11 = *param_2;
  if ((ulong)*(byte *)((long)param_2 + 0x32) == 0) {
    puVar5 = (undefined8 *)Aska::_MemoryHandleBlock* Aska::_MemoryHandleLocalFunctions::LocalMallocHigh<true>(Aska::MemoryHandleManager*, Aska::_MemoryHandleBlock*, unsigned long)(param_1,param_2,uVar11);
  }
  else {
    puVar5 = (undefined8 *)
             Aska::_MemoryHandleBlock* Aska::_MemoryHandleLocalFunctions::LocalAlignedMallocHigh<true>(Aska::MemoryHandleManager*, Aska::_MemoryHandleBlock*, unsigned long, long)(param_1,param_2,uVar11,
                             0x80000000L >> ((ulong)*(byte *)((long)param_2 + 0x32) & 0x3f));
  }
  if (puVar5 == (undefined8 *)0x0) {
    uVar11 = 0;
  }
  else {
    memcpy(puVar5[1],param_2[1],uVar11);
    uVar2 = *(uint *)(puVar5 + 1);
    plVar8 = (long *)(param_1 + (ulong)((((((((uVar2 >> 0x18) % 0x3b) * 8 + (uVar2 >> 0x10 & 0xff))
                                           % 0x3b) * 8 + (uVar2 >> 8 & 0xff)) % 0x3b) * 8 +
                                        (uVar2 & 0xff)) % 0x3b) * 8 + 0x10);
    puVar10 = (undefined8 *)*plVar8;
    if (puVar10 != (undefined8 *)0x0) {
      puVar9 = (undefined8 *)0x0;
      do {
        puVar7 = puVar10;
        if (puVar7 == puVar5) {
          if (puVar9 != (undefined8 *)0x0) {
            plVar8 = puVar9 + 8;
          }
          *plVar8 = puVar5[8];
          puVar5[8] = 0;
          break;
        }
        puVar10 = (undefined8 *)puVar7[8];
        puVar9 = puVar7;
      } while ((undefined8 *)puVar7[8] != (undefined8 *)0x0);
    }
    uVar2 = *(uint *)(param_2 + 1);
    plVar8 = (long *)(param_1 + (ulong)((((((((uVar2 >> 0x18) % 0x3b) * 8 + (uVar2 >> 0x10 & 0xff))
                                           % 0x3b) * 8 + (uVar2 >> 8 & 0xff)) % 0x3b) * 8 +
                                        (uVar2 & 0xff)) % 0x3b) * 8 + 0x10);
    puVar10 = (undefined8 *)*plVar8;
    if (puVar10 != (undefined8 *)0x0) {
      puVar9 = (undefined8 *)0x0;
      do {
        puVar7 = puVar10;
        if (puVar7 == param_2) {
          if (puVar9 != (undefined8 *)0x0) {
            plVar8 = puVar9 + 8;
          }
          *plVar8 = param_2[8];
          param_2[8] = 0;
          break;
        }
        puVar10 = (undefined8 *)puVar7[8];
        puVar9 = puVar7;
      } while ((undefined8 *)puVar7[8] != (undefined8 *)0x0);
    }
    memcpy(auStack_78,puVar5,0x48);
    uVar3 = *(undefined4 *)((long)puVar5 + 0x34);
    uVar4 = *(undefined4 *)((long)param_2 + 0x34);
    memcpy(puVar5,param_2,0x48);
    memcpy(param_2,auStack_78,0x48);
    *(undefined4 *)((long)puVar5 + 0x34) = uVar3;
    *(undefined4 *)((long)param_2 + 0x34) = uVar4;
    puVar10 = (undefined8 *)puVar5[3];
    if ((undefined8 *)puVar5[3] == puVar5) {
      puVar5[3] = param_2;
      puVar10 = param_2;
    }
    puVar10[2] = puVar5;
    puVar10 = (undefined8 *)puVar5[2];
    if ((undefined8 *)puVar5[2] == puVar5) {
      puVar5[2] = param_2;
      puVar10 = param_2;
    }
    puVar10[3] = puVar5;
    puVar10 = (undefined8 *)param_2[3];
    if ((undefined8 *)param_2[3] == param_2) {
      param_2[3] = puVar5;
      puVar10 = puVar5;
    }
    puVar10[2] = param_2;
    puVar10 = (undefined8 *)param_2[2];
    if ((undefined8 *)param_2[2] == param_2) {
      param_2[2] = puVar5;
      puVar10 = puVar5;
    }
    puVar10[3] = param_2;
    uVar2 = *(uint *)(puVar5 + 1);
    lVar1 = param_1 + 0x10;
    lVar6 = (ulong)((((((((uVar2 >> 0x18) % 0x3b) * 8 + (uVar2 >> 0x10 & 0xff)) % 0x3b) * 8 +
                      (uVar2 >> 8 & 0xff)) % 0x3b) * 8 + (uVar2 & 0xff)) % 0x3b) * 8;
    puVar5[8] = *(undefined8 *)(lVar1 + lVar6);
    *(undefined8 **)(lVar1 + lVar6) = puVar5;
    uVar2 = *(uint *)(param_2 + 1);
    lVar6 = (ulong)((((((((uVar2 >> 0x18) % 0x3b) * 8 + (uVar2 >> 0x10 & 0xff)) % 0x3b) * 8 +
                      (uVar2 >> 8 & 0xff)) % 0x3b) * 8 + (uVar2 & 0xff)) % 0x3b) * 8;
    param_2[8] = *(undefined8 *)(lVar1 + lVar6);
    *(undefined8 **)(lVar1 + lVar6) = param_2;
    Aska::MemoryHandleManager::LocalFree(Aska::_MemoryHandleBlock*)(param_1,puVar5);
    uVar11 = 1;
  }
  return uVar11;
}

// ==== Aska::MemoryHandleManager::Compaction(unsigned long)
// vaddr 0x1f46d3c | ghidra 0x2046d3c | size 692 | symbol _ZN4Aska19MemoryHandleManager10CompactionEm | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska19MemoryHandleManager10CompactionEm(long param_1,ulong param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  int iVar8;
  ulong *puVar9;
  long lVar10;
  char *pcVar11;
  ulong *puVar12;
  
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar7 = 0;
code_r0x02046d64:
  do {
    if (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar5 = iVar7 < 0x1ff;
      iVar7 = iVar7 + 1;
      if (bVar5) goto code_r0x02046d64;
      piVar2 = (int *)(param_1 + 0x2ac);
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
            uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
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
              Aska::Semaphore::Wait() const(param_1 + 0x2e8);
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
              if (cVar4 == '\0') goto code_r0x02046e1c;
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
code_r0x02046e1c:
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar5) {
          *piVar2 = *piVar2 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
code_r0x02046e2c:
      DataMemoryBarrier(2,3);
      lVar10 = *(long *)(param_1 + 0x1e8);
      iVar7 = 0;
      iVar3 = *(int *)(lVar10 + 8);
      iVar8 = iVar3;
      do {
        pcVar11 = (char *)(lVar10 + (long)iVar8 * 0x30);
        do {
          puVar12 = *(ulong **)(pcVar11 + 0x28);
          puVar9 = (ulong *)puVar12[3];
          if (puVar9 == puVar12) {
code_r0x02046f00:
            bVar5 = false;
          }
          else {
            if (0 < iVar7) {
              do {
                if (*(char *)((long)puVar9 + 0x31) != '\0') {
                  if (param_2 < *puVar9) goto code_r0x02046f88;
                  if ((char)puVar9[6] == '\0') {
                    uVar6 = Aska::MemoryHandleManager::LocalMove(Aska::_MemoryHandleBlock&)(param_1,puVar9);
                  }
                  else {
                    uVar6 = Aska::MemoryHandleManager::LocalMoveToHigh(Aska::_MemoryHandleBlock&)(param_1,puVar9);
                  }
                  if ((uVar6 & 1) != 0) goto code_r0x02046f5c;
                  if (param_2 == 0) goto code_r0x02046f88;
                }
                puVar9 = (ulong *)puVar9[3];
              } while (puVar9 != puVar12);
              goto code_r0x02046f00;
            }
            if (param_2 != 0) {
              do {
                if (*(char *)((long)puVar9 + 0x31) != '\0') {
                  if ((char)puVar9[6] == '\0') {
                    uVar6 = Aska::MemoryHandleManager::LocalMove(Aska::_MemoryHandleBlock&)(param_1,puVar9);
                  }
                  else {
                    uVar6 = Aska::MemoryHandleManager::LocalMoveToHigh(Aska::_MemoryHandleBlock&)(param_1,puVar9);
                  }
                  if ((uVar6 & 1) != 0) goto code_r0x02046f5c;
                }
                puVar9 = (ulong *)puVar9[3];
              } while (puVar9 != puVar12);
              goto code_r0x02046f00;
            }
            while (*(char *)((long)puVar9 + 0x31) == '\0') {
              puVar9 = (ulong *)puVar9[3];
              if (puVar9 == puVar12) goto code_r0x02046f88;
            }
            if ((char)puVar9[6] == '\0') {
              uVar6 = Aska::MemoryHandleManager::LocalMove(Aska::_MemoryHandleBlock&)(param_1,puVar9);
            }
            else {
              uVar6 = Aska::MemoryHandleManager::LocalMoveToHigh(Aska::_MemoryHandleBlock&)(param_1,puVar9);
            }
            if ((uVar6 & 1) == 0) goto code_r0x02046f88;
code_r0x02046f5c:
            iVar7 = iVar7 + 1;
            bVar5 = param_2 < *puVar9;
            param_2 = param_2 - *puVar9;
            if (bVar5) goto code_r0x02046f88;
            bVar5 = true;
          }
          if (param_2 == 0) goto code_r0x02046f88;
        } while ((bVar5) && (*pcVar11 != '\0'));
        iVar8 = *(int *)(lVar10 + (long)iVar8 * 0x30 + 8);
      } while (iVar8 != iVar3);
code_r0x02046f88:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_1 + 0x2ac)) {
        piVar1 = (int *)(param_1 + 0x2ac);
        do {
          cVar4 = '\x01';
          bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar5) {
            *piVar1 = *piVar1 + -1;
            cVar4 = ExclusiveMonitorsStatus();
          }
        } while (cVar4 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x2e8);
        }
      }
      return iVar7;
    }
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x02046e2c;
  } while( true );
}

// ==== Aska::MemoryHandleManager::Compaction()
// vaddr 0x1f46ff0 | ghidra 0x2046ff0 | size 488 | symbol _ZN4Aska19MemoryHandleManager10CompactionEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska19MemoryHandleManager10CompactionEv(long param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  char cVar4;
  bool bVar5;
  ulong uVar6;
  int iVar7;
  int iVar8;
  long lVar9;
  long lVar10;
  char *pcVar11;
  long lVar12;
  
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar7 = 0;
code_r0x02047014:
  if (*piVar1 == -1) {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = 0;
      cVar4 = ExclusiveMonitorsStatus();
    }
    if (cVar4 == '\0') goto code_r0x020470dc;
    goto code_r0x02047014;
  }
  ClearExclusiveLocal();
  bVar5 = iVar7 < 0x1ff;
  iVar7 = iVar7 + 1;
  if (bVar5) goto code_r0x02047014;
  piVar2 = (int *)(param_1 + 0x2ac);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
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
          Aska::Semaphore::Wait() const(param_1 + 0x2e8);
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
          if (cVar4 == '\0') goto code_r0x020470cc;
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
code_r0x020470cc:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x020470dc:
  DataMemoryBarrier(2,3);
  lVar10 = *(long *)(param_1 + 0x1e8);
  iVar7 = 0;
  iVar3 = *(int *)(lVar10 + 8);
  iVar8 = iVar3;
code_r0x020470f4:
  pcVar11 = (char *)(lVar10 + (long)iVar8 * 0x30);
code_r0x02047100:
  lVar12 = *(long *)(pcVar11 + 0x28);
  lVar9 = *(long *)(lVar12 + 0x18);
  if (lVar9 != lVar12) {
    do {
      if (*(char *)(lVar9 + 0x31) != '\0') {
        if (*(char *)(lVar9 + 0x30) == '\0') {
          uVar6 = Aska::MemoryHandleManager::LocalMove(Aska::_MemoryHandleBlock&)(param_1,lVar9);
        }
        else {
          uVar6 = Aska::MemoryHandleManager::LocalMoveToHigh(Aska::_MemoryHandleBlock&)(param_1,lVar9);
        }
        if ((uVar6 & 1) != 0) goto code_r0x02047154;
      }
      lVar9 = *(long *)(lVar9 + 0x18);
      if (lVar9 == lVar12) break;
    } while( true );
  }
  goto code_r0x02047160;
code_r0x02047154:
  iVar7 = iVar7 + 1;
  if (*pcVar11 == '\0') goto code_r0x02047160;
  goto code_r0x02047100;
code_r0x02047160:
  iVar8 = *(int *)(lVar10 + (long)iVar8 * 0x30 + 8);
  if (iVar8 == iVar3) {
    DataMemoryBarrier(2,3);
    *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
    DataMemoryBarrier(2,3);
    if (0x14 < *(int *)(param_1 + 0x2ac)) {
      piVar1 = (int *)(param_1 + 0x2ac);
      do {
        cVar4 = '\x01';
        bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar5) {
          *piVar1 = *piVar1 + -1;
          cVar4 = ExclusiveMonitorsStatus();
        }
      } while (cVar4 != '\0');
      uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
      if ((uVar6 & 1) != 0) {
        Aska::Semaphore::Signal() const(param_1 + 0x2e8);
      }
    }
    return iVar7;
  }
  goto code_r0x020470f4;
}

// ==== Aska::MemoryHandleManager::IsPhysical() const
// vaddr 0x1f471d8 | ghidra 0x20471d8 | size 8 | symbol _ZNK4Aska19MemoryHandleManager10IsPhysicalEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska19MemoryHandleManager10IsPhysicalEv(void)

{
  return 0;
}

// ==== Aska::MemoryHandleManager::VirtualMalloc(unsigned long)
// vaddr 0x1f471e0 | ghidra 0x20471e0 | size 4 | symbol _ZN4Aska19MemoryHandleManager13VirtualMallocEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager13VirtualMallocEm(void)

{
  (*(code *)PTR__ZN4Aska19MemoryHandleManager6MallocEm_02c8f4d8)();
  return;
}

// ==== Aska::MemoryHandleManager::VirtualMallocHigh(unsigned long)
// vaddr 0x1f471e4 | ghidra 0x20471e4 | size 4 | symbol _ZN4Aska19MemoryHandleManager17VirtualMallocHighEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager17VirtualMallocHighEm(void)

{
  (*(code *)PTR__ZN4Aska19MemoryHandleManager10MallocHighEm_02caefb0)();
  return;
}

// ==== Aska::MemoryHandleManager::VirtualAlignedMalloc(unsigned long, long)
// vaddr 0x1f471e8 | ghidra 0x20471e8 | size 4 | symbol _ZN4Aska19MemoryHandleManager20VirtualAlignedMallocEml | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager20VirtualAlignedMallocEml(void)

{
  (*(code *)PTR__ZN4Aska19MemoryHandleManager13AlignedMallocEml_02ca72a8)();
  return;
}

// ==== Aska::MemoryHandleManager::VirtualAlignedMallocHigh(unsigned long, long)
// vaddr 0x1f471ec | ghidra 0x20471ec | size 4 | symbol _ZN4Aska19MemoryHandleManager24VirtualAlignedMallocHighEml | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager24VirtualAlignedMallocHighEml(void)

{
  (*(code *)PTR__ZN4Aska19MemoryHandleManager17AlignedMallocHighEml_02ca2d90)();
  return;
}

// ==== Aska::MemoryHandleManager::VirtualRealloc(unsigned long, void*, long)
// vaddr 0x1f471f0 | ghidra 0x20471f0 | size 4 | symbol _ZN4Aska19MemoryHandleManager14VirtualReallocEmPvl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager14VirtualReallocEmPvl(void)

{
  (*(code *)PTR__ZN4Aska19MemoryHandleManager7ReallocEmPvl_02c960f0)();
  return;
}

// ==== Aska::MemoryHandleManager::VirtualSplit(void*, void*)
// vaddr 0x1f471f4 | ghidra 0x20471f4 | size 872 | symbol _ZN4Aska19MemoryHandleManager12VirtualSplitEPvS1_ | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska19MemoryHandleManager12VirtualSplitEPvS1_(long param_1,ulong param_2,ulong param_3)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  ulong *puVar6;
  long lVar7;
  int iVar8;
  ulong uVar9;
  long lVar10;
  ulong *puVar11;
  ulong uVar12;
  ulong *puVar13;
  ulong uVar14;
  
  uVar9 = param_2 >> 0x18 & 0xff;
  lVar10 = *(long *)(param_1 + (ulong)((((((((int)uVar9 + (int)(uVar9 / 0x3b) * -0x3b) * 8 +
                                           ((uint)(param_2 >> 0x10) & 0xff)) % 0x3b) * 8 +
                                         ((uint)(param_2 >> 8) & 0xff)) % 0x3b) * 8 +
                                       ((uint)param_2 & 0xff)) % 0x3b) * 8 + 0x10);
  while( true ) {
    if (lVar10 == 0) {
      return 0;
    }
    if (*(ulong *)(lVar10 + 8) == param_2) break;
    lVar10 = *(long *)(lVar10 + 0x40);
  }
  if (*(int *)(lVar10 + 0x34) == 0) {
    return 0;
  }
  puVar6 = (ulong *)Aska::MemoryHandleManager::GetBlock(unsigned int) const(param_1);
  if (puVar6 == (ulong *)0x0) {
    return 0;
  }
  uVar9 = *puVar6 + (param_2 - param_3);
  if (uVar9 != (uVar9 + 0xf & 0xfffffffffffffff0)) {
    return 0;
  }
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar8 = 0;
  do {
    while (*piVar1 == -1) {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = 0;
        cVar4 = ExclusiveMonitorsStatus();
      }
      if (cVar4 == '\0') goto code_r0x0204739c;
    }
    ClearExclusiveLocal();
    bVar5 = iVar8 < 0x1ff;
    iVar8 = iVar8 + 1;
  } while (bVar5);
  piVar2 = (int *)(param_1 + 0x2ac);
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
        uVar12 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar12 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x2e8);
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
          if (cVar4 == '\0') goto code_r0x0204738c;
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
code_r0x0204738c:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar5) {
      *piVar2 = *piVar2 + -1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
code_r0x0204739c:
  DataMemoryBarrier(2,3);
  puVar13 = *(ulong **)(param_1 + 0x208);
  puVar11 = (ulong *)puVar13[2];
  if (puVar13 == puVar11) {
    if (*(char *)(param_1 + 0x230) == '\0') {
      return 0;
    }
    lVar10 = ((long)*(int *)(*(long *)(param_1 + 0x200) + 0x10) +
             (long)*(int *)(*(long *)(param_1 + 0x200) + 0x14)) * 0x48;
    if (*(long *)(param_1 + 0x210) == 0) {
      lVar7 = operator new[](unsigned long, std::nothrow_t const&)(lVar10 + 0x18,PTR__ZSt7nothrow_02cb9a80);
    }
    else {
      lVar7 = Aska::MemoryManager::Malloc(unsigned long)();
    }
    if (lVar7 == 0) {
      return 0;
    }
    Aska::MemoryHandleManager::AddUnusedMemoryBlockChunk(Aska::MemoryHandleManager::_UnusedMemoryBlockChunk*, unsigned long)(param_1,lVar7,lVar10);
    puVar11 = (ulong *)puVar13[2];
  }
  uVar12 = puVar13[3];
  puVar11[3] = uVar12;
  *(ulong **)(uVar12 + 0x10) = puVar11;
  *(ulong **)(param_1 + 0x208) = puVar11;
  *(undefined1 *)((long)puVar13 + 0x31) = 0;
  if (puVar13 == (ulong *)0x0) {
    return 0;
  }
  uVar12 = *puVar6;
  puVar13[1] = puVar6[1];
  *puVar13 = uVar12;
  uVar12 = puVar6[6];
  puVar13[7] = puVar6[7];
  puVar13[6] = uVar12;
  uVar12 = puVar6[4];
  puVar13[5] = puVar6[5];
  puVar13[4] = uVar12;
  uVar14 = puVar6[3];
  uVar12 = puVar6[2];
  puVar13[1] = param_3;
  *(undefined4 *)((long)puVar13 + 0x34) = *(undefined4 *)((long)puVar13 + 0x34);
  puVar13[8] = 0;
  puVar13[3] = uVar14;
  puVar13[2] = uVar12;
  *puVar6 = -(param_2 - param_3);
  *puVar13 = uVar9;
  uVar12 = puVar6[2];
  puVar13[2] = uVar12;
  puVar13[3] = (ulong)puVar6;
  *(ulong **)(uVar12 + 0x18) = puVar13;
  puVar6[2] = (ulong)puVar13;
  uVar3 = (uint)puVar13[1];
  lVar10 = param_1 + (ulong)((((((((uVar3 >> 0x18) % 0x3b) * 8 + (uVar3 >> 0x10 & 0xff)) % 0x3b) * 8
                               + (uVar3 >> 8 & 0xff)) % 0x3b) * 8 + (uVar3 & 0xff)) % 0x3b) * 8;
  puVar13[8] = *(ulong *)(lVar10 + 0x10);
  *(ulong **)(lVar10 + 0x10) = puVar13;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  if (0x14 < *(int *)(param_1 + 0x2ac)) {
    piVar1 = (int *)(param_1 + 0x2ac);
    do {
      cVar4 = '\x01';
      bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar5) {
        *piVar1 = *piVar1 + -1;
        cVar4 = ExclusiveMonitorsStatus();
      }
    } while (cVar4 != '\0');
    uVar12 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
    if ((uVar12 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x2e8);
      return uVar9;
    }
    return uVar9;
  }
  return uVar9;
}

// ==== Aska::MemoryHandleManager::VirtualMove(void*, long, bool)
// vaddr 0x1f4755c | ghidra 0x204755c | size 368 | symbol _ZN4Aska19MemoryHandleManager11VirtualMoveEPvlb | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19MemoryHandleManager11VirtualMoveEPvlb
               (long *param_1,undefined8 param_2,long param_3,uint param_4)

{
  long *plVar1;
  long lVar2;
  undefined8 *puVar3;
  ulong uVar4;
  ulong uStack_38;
  
  plVar1 = (long *)(**(code **)(*param_1 + 0xa0))(param_1,param_2,&uStack_38);
  if (plVar1 != (long *)0x0) {
    if (param_3 < 2) {
      if ((param_4 & 1) == 0) {
        lVar2 = Aska::MemoryHandleManager::Malloc(unsigned long)(param_1,uStack_38);
      }
      else {
        lVar2 = Aska::MemoryHandleManager::MallocHigh(unsigned long)(param_1);
      }
    }
    else if ((param_4 & 1) == 0) {
      lVar2 = Aska::MemoryHandleManager::AlignedMalloc(unsigned long, long)(param_1,uStack_38,param_3);
    }
    else {
      lVar2 = Aska::MemoryHandleManager::AlignedMallocHigh(unsigned long, long)(param_1,uStack_38,param_3);
    }
    if (lVar2 == 0) {
      return 0;
    }
    memcpy(lVar2,param_2,uStack_38);
    puVar3 = (undefined8 *)(**(code **)(*plVar1 + 0xc0))(plVar1,param_2);
    if ((puVar3 == (undefined8 *)0x0) ||
       (uVar4 = (**(code **)*puVar3)(puVar3,param_2,lVar2), (uVar4 & 1) != 0)) {
      Aska::IMemoryManager::Free(void const*)(param_2);
      return lVar2;
    }
    Aska::MemoryHandleManager::Free(void const*)(param_1,lVar2);
  }
  return 0;
}

// ==== Aska::MemoryHandleManager::VirtualFree(void*)
// vaddr 0x1f476cc | ghidra 0x20476cc | size 536 | symbol _ZN4Aska19MemoryHandleManager11VirtualFreeEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager11VirtualFreeEPv(long param_1,ulong param_2)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  long lVar5;
  undefined8 uVar6;
  int iVar7;
  ulong uVar8;
  long lVar9;
  int *piVar10;
  
  lVar5 = Aska::MemoryHandleManager::GetAllocatedManager(void const*, unsigned long*)(param_2,0);
  if (lVar5 == 0) {
    return;
  }
  uVar8 = param_2 >> 0x18 & 0xff;
  lVar9 = *(long *)(lVar5 + (ulong)((((((((int)uVar8 + (int)(uVar8 / 0x3b) * -0x3b) * 8 +
                                        ((uint)(param_2 >> 0x10) & 0xff)) % 0x3b) * 8 +
                                      ((uint)(param_2 >> 8) & 0xff)) % 0x3b) * 8 +
                                    ((uint)param_2 & 0xff)) % 0x3b) * 8 + 0x10);
  while( true ) {
    if (lVar9 == 0) {
      return;
    }
    if (*(ulong *)(lVar9 + 8) == param_2) break;
    lVar9 = *(long *)(lVar9 + 0x40);
  }
  iVar2 = *(int *)(lVar9 + 0x34);
  if (iVar2 == 0) {
    return;
  }
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar7 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar7;
      iVar7 = iVar7 + 1;
      if (bVar4) {
        piVar10 = (int *)(param_1 + 0x2ac);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
          if (bVar4) {
            *piVar10 = *piVar10 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        do {
          if (*piVar1 != -1) {
            ClearExclusiveLocal();
            do {
              uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
              if ((uVar8 & 1) == 0) {
                do {
                  cVar3 = '\x01';
                  bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
                  if (bVar4) {
                    *piVar10 = *piVar10 + -1;
                    cVar3 = ExclusiveMonitorsStatus();
                  }
                } while (cVar3 != '\0');
                Aska::Thread::Sleep(unsigned int)(1);
              }
              else {
                Aska::Semaphore::Wait() const(param_1 + 0x2e8);
              }
              do {
                cVar3 = '\x01';
                bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
                if (bVar4) {
                  *piVar10 = *piVar10 + 1;
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
                if (cVar3 == '\0') goto code_r0x020478cc;
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
code_r0x020478cc:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
          if (bVar4) {
            *piVar10 = *piVar10 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
        goto code_r0x020477e8;
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
code_r0x020477e8:
  piVar10 = (int *)(param_1 + 0x2ac);
  uVar6 = Aska::MemoryHandleManager::GetBlock(unsigned int) const(lVar5,iVar2);
  Aska::MemoryHandleManager::LocalFree(Aska::_MemoryHandleBlock*)(lVar5,uVar6);
  DataMemoryBarrier(2,3);
  *piVar1 = -1;
  DataMemoryBarrier(2,3);
  if (0x14 < *piVar10) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar10,0x10);
      if (bVar4) {
        *piVar10 = *piVar10 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar8 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
    if ((uVar8 & 1) != 0) {
      (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x2e8);
      return;
    }
  }
  return;
}

// ==== Aska::MemoryHandleManager::VirtualGetAllocatedManager(void const*, unsigned long*)
// vaddr 0x1f478e4 | ghidra 0x20478e4 | size 212 | symbol _ZN4Aska19MemoryHandleManager26VirtualGetAllocatedManagerEPKvPm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19MemoryHandleManager26VirtualGetAllocatedManagerEPKvPm
               (undefined8 param_1,ulong param_2,undefined8 *param_3)

{
  long lVar1;
  undefined8 *puVar2;
  ulong uVar3;
  long lVar4;
  
  lVar1 = Aska::MemoryHandleManager::GetAllocatedManager(void const*, unsigned long*)(param_2,0);
  if ((param_3 != (undefined8 *)0x0) && (lVar1 != 0)) {
    uVar3 = param_2 >> 0x18 & 0xff;
    for (lVar4 = *(long *)(lVar1 + (ulong)((((((((int)uVar3 + (int)(uVar3 / 0x3b) * -0x3b) * 8 +
                                               ((uint)(param_2 >> 0x10) & 0xff)) % 0x3b) * 8 +
                                             ((uint)(param_2 >> 8) & 0xff)) % 0x3b) * 8 +
                                           ((uint)param_2 & 0xff)) % 0x3b) * 8 + 0x10); lVar4 != 0;
        lVar4 = *(long *)(lVar4 + 0x40)) {
      if (*(ulong *)(lVar4 + 8) == param_2) {
        if (*(int *)(lVar4 + 0x34) == 0) {
          return lVar1;
        }
        puVar2 = (undefined8 *)Aska::MemoryHandleManager::GetBlock(unsigned int) const(lVar1);
        *param_3 = *puVar2;
        return lVar1;
      }
    }
  }
  return lVar1;
}

// ==== Aska::MemoryHandleManager::VirtualRegisterNotify(void*, Aska::IMemoryNotify*)
// vaddr 0x1f479b8 | ghidra 0x20479b8 | size 516 | symbol _ZN4Aska19MemoryHandleManager21VirtualRegisterNotifyEPvPNS_13IMemoryNotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska19MemoryHandleManager21VirtualRegisterNotifyEPvPNS_13IMemoryNotifyE
          (long param_1,ulong param_2,long param_3)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  ulong uVar6;
  long lVar7;
  undefined4 uVar8;
  
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar5 = 0;
code_r0x020479dc:
  if (*piVar1 == -1) {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x02047aa4;
    goto code_r0x020479dc;
  }
  ClearExclusiveLocal();
  bVar4 = iVar5 < 0x1ff;
  iVar5 = iVar5 + 1;
  if (bVar4) goto code_r0x020479dc;
  piVar2 = (int *)(param_1 + 0x2ac);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar6 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x2e8);
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
          if (cVar3 == '\0') goto code_r0x02047a94;
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
code_r0x02047a94:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02047aa4:
  uVar6 = param_2 >> 0x18 & 0xff;
  DataMemoryBarrier(2,3);
  lVar7 = *(long *)(param_1 + (ulong)((((((((int)uVar6 + (int)(uVar6 / 0x3b) * -0x3b) * 8 +
                                          ((uint)(param_2 >> 0x10) & 0xff)) % 0x3b) * 8 +
                                        ((uint)(param_2 >> 8) & 0xff)) % 0x3b) * 8 +
                                      ((uint)param_2 & 0xff)) % 0x3b) * 8 + 0x10);
  do {
    if (lVar7 == 0) {
      uVar8 = 0;
code_r0x02047b34:
      lVar7 = Aska::MemoryHandleManager::GetBlock(unsigned int) const(param_1,uVar8);
      if ((*(long *)(lVar7 + 0x38) == 0) || (*(long *)(lVar7 + 0x38) == param_3)) {
        *(long *)(lVar7 + 0x38) = param_3;
        uVar8 = 1;
      }
      else {
        uVar8 = 0;
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_1 + 0x2ac)) {
        piVar1 = (int *)(param_1 + 0x2ac);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x2e8);
        }
      }
      return uVar8;
    }
    if (*(ulong *)(lVar7 + 8) == param_2) {
      uVar8 = *(undefined4 *)(lVar7 + 0x34);
      goto code_r0x02047b34;
    }
    lVar7 = *(long *)(lVar7 + 0x40);
  } while( true );
}

// ==== Aska::MemoryHandleManager::VirtualRemoveNotify(void*, Aska::IMemoryNotify*)
// vaddr 0x1f47bbc | ghidra 0x2047bbc | size 516 | symbol _ZN4Aska19MemoryHandleManager19VirtualRemoveNotifyEPvPNS_13IMemoryNotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska19MemoryHandleManager19VirtualRemoveNotifyEPvPNS_13IMemoryNotifyE
          (long param_1,ulong param_2,long param_3)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  ulong uVar6;
  long lVar7;
  undefined4 uVar8;
  
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar5 = 0;
code_r0x02047be0:
  if (*piVar1 == -1) {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x02047ca8;
    goto code_r0x02047be0;
  }
  ClearExclusiveLocal();
  bVar4 = iVar5 < 0x1ff;
  iVar5 = iVar5 + 1;
  if (bVar4) goto code_r0x02047be0;
  piVar2 = (int *)(param_1 + 0x2ac);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar6 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x2e8);
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
          if (cVar3 == '\0') goto code_r0x02047c98;
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
code_r0x02047c98:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02047ca8:
  uVar6 = param_2 >> 0x18 & 0xff;
  DataMemoryBarrier(2,3);
  lVar7 = *(long *)(param_1 + (ulong)((((((((int)uVar6 + (int)(uVar6 / 0x3b) * -0x3b) * 8 +
                                          ((uint)(param_2 >> 0x10) & 0xff)) % 0x3b) * 8 +
                                        ((uint)(param_2 >> 8) & 0xff)) % 0x3b) * 8 +
                                      ((uint)param_2 & 0xff)) % 0x3b) * 8 + 0x10);
  do {
    if (lVar7 == 0) {
      uVar8 = 0;
code_r0x02047d38:
      lVar7 = Aska::MemoryHandleManager::GetBlock(unsigned int) const(param_1,uVar8);
      if ((param_3 == 0) || (*(long *)(lVar7 + 0x38) == param_3)) {
        uVar8 = 1;
        *(undefined8 *)(lVar7 + 0x38) = 0;
      }
      else {
        uVar8 = 0;
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_1 + 0x2ac)) {
        piVar1 = (int *)(param_1 + 0x2ac);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x2e8);
        }
      }
      return uVar8;
    }
    if (*(ulong *)(lVar7 + 8) == param_2) {
      uVar8 = *(undefined4 *)(lVar7 + 0x34);
      goto code_r0x02047d38;
    }
    lVar7 = *(long *)(lVar7 + 0x40);
  } while( true );
}

// ==== Aska::MemoryHandleManager::VirtualIsRegisteredNotify(void*, Aska::IMemoryNotify*)
// vaddr 0x1f47dc0 | ghidra 0x2047dc0 | size 516 | symbol _ZN4Aska19MemoryHandleManager25VirtualIsRegisteredNotifyEPvPNS_13IMemoryNotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska19MemoryHandleManager25VirtualIsRegisteredNotifyEPvPNS_13IMemoryNotifyE
          (long param_1,ulong param_2,long param_3)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  ulong uVar6;
  long lVar7;
  undefined4 uVar8;
  
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar5 = 0;
code_r0x02047de4:
  if (*piVar1 == -1) {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x02047eac;
    goto code_r0x02047de4;
  }
  ClearExclusiveLocal();
  bVar4 = iVar5 < 0x1ff;
  iVar5 = iVar5 + 1;
  if (bVar4) goto code_r0x02047de4;
  piVar2 = (int *)(param_1 + 0x2ac);
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
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar6 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x2e8);
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
          if (cVar3 == '\0') goto code_r0x02047e9c;
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
code_r0x02047e9c:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02047eac:
  uVar6 = param_2 >> 0x18 & 0xff;
  DataMemoryBarrier(2,3);
  lVar7 = *(long *)(param_1 + (ulong)((((((((int)uVar6 + (int)(uVar6 / 0x3b) * -0x3b) * 8 +
                                          ((uint)(param_2 >> 0x10) & 0xff)) % 0x3b) * 8 +
                                        ((uint)(param_2 >> 8) & 0xff)) % 0x3b) * 8 +
                                      ((uint)param_2 & 0xff)) % 0x3b) * 8 + 0x10);
  do {
    if (lVar7 == 0) {
      uVar8 = 0;
code_r0x02047f3c:
      lVar7 = Aska::MemoryHandleManager::GetBlock(unsigned int) const(param_1,uVar8);
      if (param_3 == 0) {
        if (*(long *)(lVar7 + 0x38) != 0) goto code_r0x02047f60;
      }
      else if (*(long *)(lVar7 + 0x38) == param_3) {
code_r0x02047f60:
        uVar8 = 1;
        goto code_r0x02047f64;
      }
      uVar8 = 0;
code_r0x02047f64:
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_1 + 0x2ac)) {
        piVar1 = (int *)(param_1 + 0x2ac);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar6 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x2e8);
        }
      }
      return uVar8;
    }
    if (*(ulong *)(lVar7 + 8) == param_2) {
      uVar8 = *(undefined4 *)(lVar7 + 0x34);
      goto code_r0x02047f3c;
    }
    lVar7 = *(long *)(lVar7 + 0x40);
  } while( true );
}

// ==== Aska::MemoryHandleManager::VirtualGetRegisteredNotify(void*)
// vaddr 0x1f47fc4 | ghidra 0x2047fc4 | size 476 | symbol _ZN4Aska19MemoryHandleManager26VirtualGetRegisteredNotifyEPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska19MemoryHandleManager26VirtualGetRegisteredNotifyEPv(long param_1,ulong param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  undefined4 uVar5;
  int iVar6;
  ulong uVar7;
  long lVar8;
  undefined8 uVar9;
  
  piVar1 = (int *)(param_1 + 0x2a8);
  iVar6 = 0;
code_r0x02047fe0:
  if (*piVar1 == -1) {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x020480a8;
    goto code_r0x02047fe0;
  }
  ClearExclusiveLocal();
  bVar4 = iVar6 < 0x1ff;
  iVar6 = iVar6 + 1;
  if (bVar4) goto code_r0x02047fe0;
  piVar2 = (int *)(param_1 + 0x2ac);
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
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar7 & 1) == 0) {
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
          Aska::Semaphore::Wait() const(param_1 + 0x2e8);
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
          if (cVar3 == '\0') goto code_r0x02048098;
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
code_r0x02048098:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar4) {
      *piVar2 = *piVar2 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x020480a8:
  uVar7 = param_2 >> 0x18 & 0xff;
  DataMemoryBarrier(2,3);
  lVar8 = *(long *)(param_1 + (ulong)((((((((int)uVar7 + (int)(uVar7 / 0x3b) * -0x3b) * 8 +
                                          ((uint)(param_2 >> 0x10) & 0xff)) % 0x3b) * 8 +
                                        ((uint)(param_2 >> 8) & 0xff)) % 0x3b) * 8 +
                                      ((uint)param_2 & 0xff)) % 0x3b) * 8 + 0x10);
  do {
    if (lVar8 == 0) {
      uVar5 = 0;
code_r0x02048138:
      lVar8 = Aska::MemoryHandleManager::GetBlock(unsigned int) const(param_1,uVar5);
      uVar9 = *(undefined8 *)(lVar8 + 0x38);
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x2a8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      if (0x14 < *(int *)(param_1 + 0x2ac)) {
        piVar1 = (int *)(param_1 + 0x2ac);
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar7 = Aska::Semaphore::IsReady() const(param_1 + 0x2e8);
        if ((uVar7 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0x2e8);
        }
      }
      return uVar9;
    }
    if (*(ulong *)(lVar8 + 8) == param_2) {
      uVar5 = *(undefined4 *)(lVar8 + 0x34);
      goto code_r0x02048138;
    }
    lVar8 = *(long *)(lVar8 + 0x40);
  } while( true );
}

// ==== Aska::MemoryHandleManager::CreateDebugMemoryMap(int, int, bool)
// vaddr 0x1f481a0 | ghidra 0x20481a0 | size 4 | symbol _ZN4Aska19MemoryHandleManager20CreateDebugMemoryMapEiib | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager20CreateDebugMemoryMapEiib(void)

{
  return;
}

// ==== Aska::MemoryHandleManager::UpdateDebugMemoryMap()
// vaddr 0x1f481a4 | ghidra 0x20481a4 | size 4 | symbol _ZN4Aska19MemoryHandleManager20UpdateDebugMemoryMapEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager20UpdateDebugMemoryMapEv(void)

{
  return;
}

// ==== Aska::MemoryHandleManager::GetDebugMemoryMap(Aska::Text*, float, float, unsigned int, float, float)
// vaddr 0x1f481a8 | ghidra 0x20481a8 | size 4 | symbol _ZN4Aska19MemoryHandleManager17GetDebugMemoryMapEPNS_4TextEffjff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager17GetDebugMemoryMapEPNS_4TextEffjff(void)

{
  return;
}

// ==== Aska::MemoryHandleManager::SetSwapDebugMemoryMap(bool)
// vaddr 0x1f481ac | ghidra 0x20481ac | size 4 | symbol _ZN4Aska19MemoryHandleManager21SetSwapDebugMemoryMapEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager21SetSwapDebugMemoryMapEb(void)

{
  return;
}

// ==== Aska::MemoryHandleManager::GetUnusedMemoryBlockTotal() const
// vaddr 0x1f481b0 | ghidra 0x20481b0 | size 40 | symbol _ZNK4Aska19MemoryHandleManager25GetUnusedMemoryBlockTotalEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK4Aska19MemoryHandleManager25GetUnusedMemoryBlockTotalEv(long param_1)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0x1f8);
  if (lVar3 != 0) {
    iVar2 = 0;
    do {
      piVar1 = (int *)(lVar3 + 0x10);
      lVar3 = *(long *)(lVar3 + 8);
      iVar2 = *piVar1 + iVar2;
    } while (lVar3 != 0);
    return iVar2;
  }
  return 0;
}

// ==== Aska::MemoryHandleManager::VirtualMoveHigh(void*, long)
// vaddr 0x1f481d8 | ghidra 0x20481d8 | size 16 | symbol _ZN4Aska19MemoryHandleManager15VirtualMoveHighEPvl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager15VirtualMoveHighEPvl(long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x020481e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x30))();
  return;
}

// ==== Aska::MemoryHandleManager::VirtualGetHeapAddress() const
// vaddr 0x1f481e8 | ghidra 0x20481e8 | size 8 | symbol _ZNK4Aska19MemoryHandleManager21VirtualGetHeapAddressEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska19MemoryHandleManager21VirtualGetHeapAddressEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x218);
}

// ==== Aska::MemoryHandleManager::VirtualIsPhysical() const
// vaddr 0x1f481f0 | ghidra 0x20481f0 | size 8 | symbol _ZNK4Aska19MemoryHandleManager17VirtualIsPhysicalEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska19MemoryHandleManager17VirtualIsPhysicalEv(void)

{
  return 0;
}

// ==== Aska::MemoryHandleManager::VirtualIsMemoryHandleManager()
// vaddr 0x1f481f8 | ghidra 0x20481f8 | size 8 | symbol _ZN4Aska19MemoryHandleManager28VirtualIsMemoryHandleManagerEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska19MemoryHandleManager28VirtualIsMemoryHandleManagerEv(void)

{
  return 1;
}

// ==== Aska::MemoryHandleManager::VirtualCalcFreeSize(long*, long*) const
// vaddr 0x1f48200 | ghidra 0x2048200 | size 4 | symbol _ZNK4Aska19MemoryHandleManager19VirtualCalcFreeSizeEPlS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska19MemoryHandleManager19VirtualCalcFreeSizeEPlS1_(void)

{
  (*(code *)PTR__ZNK4Aska19MemoryHandleManager12CalcFreeSizeEPlS1__02cab0f0)();
  return;
}

// ==== Aska::MemoryHandleManager::VirtualIsEmpty(bool) const
// vaddr 0x1f48204 | ghidra 0x2048204 | size 8 | symbol _ZNK4Aska19MemoryHandleManager14VirtualIsEmptyEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska19MemoryHandleManager14VirtualIsEmptyEb(undefined8 param_1,uint param_2)

{
  (*(code *)PTR__ZNK4Aska19MemoryHandleManager7IsEmptyEb_02c9e4a8)(param_1,param_2 & 1);
  return;
}

// ==== Aska::MemoryHandleManager::VirtualGetFastCriticalSection()
// vaddr 0x1f4820c | ghidra 0x204820c | size 8 | symbol _ZN4Aska19MemoryHandleManager29VirtualGetFastCriticalSectionEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska19MemoryHandleManager29VirtualGetFastCriticalSectionEv(long param_1)

{
  return param_1 + 0x270;
}

// ==== Aska::MemoryHandleManager::VirtualGetSrbk(int) const
// vaddr 0x1f48214 | ghidra 0x2048214 | size 16 | symbol _ZNK4Aska19MemoryHandleManager14VirtualGetSrbkEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska19MemoryHandleManager14VirtualGetSrbkEi(long param_1,int param_2)

{
  return *(long *)(param_1 + 0x1e8) + (long)param_2 * 0x30;
}

// ==== Aska::MemoryHandleManager::VirtualGetTopSrbkAddress() const
// vaddr 0x1f48224 | ghidra 0x2048224 | size 8 | symbol _ZNK4Aska19MemoryHandleManager24VirtualGetTopSrbkAddressEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska19MemoryHandleManager24VirtualGetTopSrbkAddressEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x1e8);
}

// ==== Aska::MemoryHandleManager::VirtualPrintMemoryChain()
// vaddr 0x1f48234 | ghidra 0x2048234 | size 4 | symbol _ZN4Aska19MemoryHandleManager23VirtualPrintMemoryChainEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MemoryHandleManager23VirtualPrintMemoryChainEv(void)

{
  return;
}

// ==== Aska::MemoryHandleManager::VirtualGetHeapSize() const
// vaddr 0x1f48238 | ghidra 0x2048238 | size 8 | symbol _ZNK4Aska19MemoryHandleManager18VirtualGetHeapSizeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska19MemoryHandleManager18VirtualGetHeapSizeEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x220);
}


// FAILED to create function at 02963cd8 Framework::CHandleManager_Base::iInvalidHandle
// FAILED to create function at 02963ce0 Framework::CHandleManager_Base::iInvalidHandleValue
// FAILED to create function at 02963db8 Framework::CHandleManager_Base::iDirtyPointer
// FAILED to create function at 02963dc0 typeinfo name for Framework::CHandleManager_Base
// FAILED to create function at 02ba8f08 Framework::CHandleManager_Base::vtable
// FAILED to create function at 02ba8f28 Framework::CHandleManager_Base::typeinfo
// FAILED to create function at 02bb1d88 Aska::MemoryHandleManager::vtable
// FAILED to create function at 02bb1e80 Aska::MemoryHandleManager::typeinfo
// FAILED to create function at 02cc70a8 Framework::CHandleManager_Base::gInstanceUniqueNumber
// FAILED to create function at 02dcc5f0 Aska::MemoryHandleManager::m_pGlobalMaster
// FAILED to create function at 02dcc5f8 Aska::MemoryHandleManager::m_pCriGlobal
// FAILED to create function at 02dcc600 Aska::MemoryHandleManager::m_criGlobal
