// port/decomp/memory/mapped.c: Ghidra decompiles for the memory subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileAt.java, tools/resolve_decomp.py
// run      2026-10-04 06:13 UTC: tools/decomp_at.sh '--into' 'memory/mapped' '0x2029c54' '0x2029d64' '0x202a83c' '0x202af08' '0x202b184' '0x202a02c' '0x202a3ec' '0x202a55c' '0x202a6cc' '0x202a1ac' '0x202a1e0' '0x202a364' '0x202a3ac' '0x202b5c0' '0x202b614' '0x202b3bc' '0x202b1ac' '0x202c8c4' '0x202cfc4' '0x2031078' '0x2031024' '0x202d530' '0x202c890' '0x202d3e8' '0x202eecc'

// ==== Aska::Global::InstantiateMappedMemoryManager()
// vaddr 0x1f29c54 | ghidra 0x2029c54 | size 272 | symbol _ZN4Aska6Global30InstantiateMappedMemoryManagerEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Global30InstantiateMappedMemoryManagerEv(void)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  long lVar10;
  undefined1 auStack_58 [8];
  
  puVar1 = PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368;
  if (*(long *)PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368 == 0) {
    Aska::AppProjectDependentProxy::AppProjectDependentProxy()(auStack_58);
    uVar2 = Aska::AppProjectDependentProxy::GetMappedMemoryManagerRegisterTable() const(auStack_58);
    uVar3 = Aska::AppProjectDependentProxy::GetMappedMemoryManagerRegisterPool() const(auStack_58);
    uVar4 = Aska::AppProjectDependentProxy::GetMappedMemoryManagerMappingTable() const(auStack_58);
    uVar5 = Aska::AppProjectDependentProxy::GetMappedMemoryManagerMappingPool() const(auStack_58);
    uVar6 = Aska::AppProjectDependentProxy::GetMappedMemoryManagerHandlerTable() const(auStack_58);
    uVar7 = Aska::AppProjectDependentProxy::GetMappedMemoryManagerHandlerPool() const(auStack_58);
    uVar8 = Aska::AppProjectDependentProxy::GetMappedMemoryManagerReturnTable() const(auStack_58);
    uVar9 = Aska::AppProjectDependentProxy::GetMappedMemoryManagerReturnPool() const(auStack_58);
    lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x468,PTR__ZSt7nothrow_02cb9a80);
    if (lVar10 != 0) {
      Aska::MappedMemoryManager::MappedMemoryManager(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int)(lVar10,uVar2,uVar3,uVar4,uVar5,uVar6,uVar7,uVar8,uVar9);
    }
    *(long *)puVar1 = lVar10;
    Aska::AppProjectDependentProxy::~AppProjectDependentProxy()(auStack_58);
    if (lVar10 != 0) {
      return 1;
    }
  }
  return 0;
}

// ==== Aska::Global::DeleteMappedMemoryManager()
// vaddr 0x1f29d64 | ghidra 0x2029d64 | size 44 | symbol _ZN4Aska6Global25DeleteMappedMemoryManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Global25DeleteMappedMemoryManagerEv(void)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368;
  if (*(long **)PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368 != (long *)0x0) {
    (**(code **)(**(long **)PTR__ZN4Aska6Global22m_pMappedMemoryManagerE_02cc0368 + 0x18))();
    *(undefined8 *)puVar1 = 0;
  }
  return;
}

// ==== Aska::MappedMemoryManager::PointerManager::PointerManager(unsigned int, unsigned int)
// vaddr 0x1f2a02c | ghidra 0x202a02c | size 236 | symbol _ZN4Aska19MappedMemoryManager14PointerManagerC2Ejj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MappedMemoryManager14PointerManagerC1Ejj
               (long *param_1,uint param_2,undefined4 param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  long *plVar3;
  
  *(undefined4 *)(param_1 + 1) = 0;
  puVar2 = PTR__ZTVN4Aska11TPoolLegacyINS_19MappedMemoryPointerELb0EEE_02cbb0f0;
  *(undefined4 *)(param_1 + 3) = 0;
  puVar1 = PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10;
  *(undefined1 *)(param_1 + 6) = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  *param_1 = (long)(puVar2 + 0x10);
  param_1[2] = (long)puVar1;
  param_1[8] = 0;
  Aska::TPoolLegacy<Aska::MappedMemoryPointer, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1,param_3,0,0,0);
  *param_1 = (long)(PTR__ZTVN4Aska11TBinaryTreeINS_19MappedMemoryPointerEEE_02cc4a20 + 0x10);
  if (param_2 < 2) {
    param_2 = 1;
    plVar3 = param_1 + 0xd;
  }
  else {
    plVar3 = (long *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 << 3,PTR__ZSt7nothrow_02cb9a80);
    if (plVar3 == (long *)0x0) {
      param_2 = 1;
      plVar3 = param_1 + 0xd;
    }
  }
  memset(plVar3,0,(ulong)param_2 << 3);
  *(uint *)(param_1 + 0xb) = param_2;
  param_1[10] = (long)plVar3;
  param_1[0xc] = (long)plVar3;
  *(undefined4 *)((long)param_1 + 0x8c) = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  *(undefined1 *)(param_1 + 0x11) = 0;
  param_1[0xe] = 0;
  *param_1 = (long)(PTR__ZTVN4Aska19MappedMemoryManager14PointerManagerE_02cbb410 + 0x10);
  return;
}

// ==== Aska::MappedMemoryManager::PointerManager::Register(void const*)
// vaddr 0x1f2a1ac | ghidra 0x202a1ac | size 52 | symbol _ZN4Aska19MappedMemoryManager14PointerManager8RegisterEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MappedMemoryManager14PointerManager8RegisterEPKv(long *param_1,undefined8 param_2)

{
  undefined4 uVar1;
  
  uVar1 = (**(code **)(*param_1 + 0x60))();
  (*(code *)PTR__ZN4Aska15TCategorizeHashINS_19MappedMemoryPointerEE6RegistEPKvj_02cad2d8)
            (param_1,param_2,uVar1);
  return;
}

// ==== Aska::MappedMemoryManager::PointerManager::Register(void const*, unsigned int)
// vaddr 0x1f2a1e0 | ghidra 0x202a1e0 | size 4 | symbol _ZN4Aska19MappedMemoryManager14PointerManager8RegisterEPKvj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MappedMemoryManager14PointerManager8RegisterEPKvj(void)

{
  (*(code *)PTR__ZN4Aska15TCategorizeHashINS_19MappedMemoryPointerEE6RegistEPKvj_02cad2d8)();
  return;
}

// ==== Aska::MappedMemoryManager::PointerManager::IsRegistered(void const*)
// vaddr 0x1f2a364 | ghidra 0x202a364 | size 72 | symbol _ZN4Aska19MappedMemoryManager14PointerManager12IsRegisteredEPKv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska19MappedMemoryManager14PointerManager12IsRegisteredEPKv
               (long *param_1,undefined8 param_2)

{
  undefined4 uVar1;
  long lVar2;
  
  uVar1 = (**(code **)(*param_1 + 0x60))();
  lVar2 = (**(code **)(*param_1 + 0x80))(param_1,param_2,uVar1);
  return lVar2 != 0;
}

// ==== Aska::MappedMemoryManager::PointerManager::IsRegistered(void const*, unsigned int)
// vaddr 0x1f2a3ac | ghidra 0x202a3ac | size 32 | symbol _ZN4Aska19MappedMemoryManager14PointerManager12IsRegisteredEPKvj | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska19MappedMemoryManager14PointerManager12IsRegisteredEPKvj(long *param_1)

{
  long lVar1;
  
  lVar1 = (**(code **)(*param_1 + 0x80))();
  return lVar1 != 0;
}

// ==== Aska::MappedMemoryManager::RelationManager::RelationManager(unsigned int, unsigned int)
// vaddr 0x1f2a3ec | ghidra 0x202a3ec | size 236 | symbol _ZN4Aska19MappedMemoryManager15RelationManagerC2Ejj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MappedMemoryManager15RelationManagerC1Ejj
               (long *param_1,uint param_2,undefined4 param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  long *plVar3;
  
  *(undefined4 *)(param_1 + 1) = 0;
  puVar2 = PTR__ZTVN4Aska11TPoolLegacyINS_20MappedMemoryRelationELb0EEE_02cc03e0;
  *(undefined4 *)(param_1 + 3) = 0;
  puVar1 = PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10;
  *(undefined1 *)(param_1 + 6) = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  *param_1 = (long)(puVar2 + 0x10);
  param_1[2] = (long)puVar1;
  param_1[8] = 0;
  Aska::TPoolLegacy<Aska::MappedMemoryRelation, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1,param_3,0,0,0);
  *param_1 = (long)(PTR__ZTVN4Aska11TBinaryTreeINS_20MappedMemoryRelationEEE_02cb76a0 + 0x10);
  if (param_2 < 2) {
    param_2 = 1;
    plVar3 = param_1 + 0xd;
  }
  else {
    plVar3 = (long *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 << 3,PTR__ZSt7nothrow_02cb9a80);
    if (plVar3 == (long *)0x0) {
      param_2 = 1;
      plVar3 = param_1 + 0xd;
    }
  }
  memset(plVar3,0,(ulong)param_2 << 3);
  *(uint *)(param_1 + 0xb) = param_2;
  param_1[10] = (long)plVar3;
  param_1[0xc] = (long)plVar3;
  *(undefined4 *)((long)param_1 + 0x8c) = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  *(undefined1 *)(param_1 + 0x11) = 0;
  param_1[0xe] = 0;
  *param_1 = (long)(PTR__ZTVN4Aska19MappedMemoryManager15RelationManagerE_02cbc5a8 + 0x10);
  return;
}

// ==== Aska::MappedMemoryManager::LocationManager::LocationManager(unsigned int, unsigned int)
// vaddr 0x1f2a55c | ghidra 0x202a55c | size 236 | symbol _ZN4Aska19MappedMemoryManager15LocationManagerC2Ejj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MappedMemoryManager15LocationManagerC1Ejj
               (long *param_1,uint param_2,undefined4 param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  long *plVar3;
  
  *(undefined4 *)(param_1 + 1) = 0;
  puVar2 = PTR__ZTVN4Aska11TPoolLegacyINS_20MappedMemoryLocationELb0EEE_02cc0260;
  *(undefined4 *)(param_1 + 3) = 0;
  puVar1 = PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10;
  *(undefined1 *)(param_1 + 6) = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  *param_1 = (long)(puVar2 + 0x10);
  param_1[2] = (long)puVar1;
  param_1[8] = 0;
  Aska::TPoolLegacy<Aska::MappedMemoryLocation, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1,param_3,0,0,0);
  *param_1 = (long)(PTR__ZTVN4Aska11TBinaryTreeINS_20MappedMemoryLocationEEE_02cbab58 + 0x10);
  if (param_2 < 2) {
    param_2 = 1;
    plVar3 = param_1 + 0xd;
  }
  else {
    plVar3 = (long *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 << 3,PTR__ZSt7nothrow_02cb9a80);
    if (plVar3 == (long *)0x0) {
      param_2 = 1;
      plVar3 = param_1 + 0xd;
    }
  }
  memset(plVar3,0,(ulong)param_2 << 3);
  *(uint *)(param_1 + 0xb) = param_2;
  param_1[10] = (long)plVar3;
  param_1[0xc] = (long)plVar3;
  *(undefined4 *)((long)param_1 + 0x8c) = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  *(undefined1 *)(param_1 + 0x11) = 0;
  param_1[0xe] = 0;
  *param_1 = (long)(PTR__ZTVN4Aska19MappedMemoryManager15LocationManagerE_02cc3b98 + 0x10);
  return;
}

// ==== Aska::MappedMemoryManager::IdentifierManager::IdentifierManager(unsigned int, unsigned int)
// vaddr 0x1f2a6cc | ghidra 0x202a6cc | size 236 | symbol _ZN4Aska19MappedMemoryManager17IdentifierManagerC2Ejj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MappedMemoryManager17IdentifierManagerC1Ejj
               (long *param_1,uint param_2,undefined4 param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  long *plVar3;
  
  *(undefined4 *)(param_1 + 1) = 0;
  puVar2 = PTR__ZTVN4Aska11TPoolLegacyINS_22MappedMemoryIdentifierELb0EEE_02cb7218;
  *(undefined4 *)(param_1 + 3) = 0;
  puVar1 = PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10;
  *(undefined1 *)(param_1 + 6) = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  *param_1 = (long)(puVar2 + 0x10);
  param_1[2] = (long)puVar1;
  param_1[8] = 0;
  Aska::TPoolLegacy<Aska::MappedMemoryIdentifier, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1,param_3,0,0,0);
  *param_1 = (long)(PTR__ZTVN4Aska11TBinaryTreeINS_22MappedMemoryIdentifierEEE_02cb8b78 + 0x10);
  if (param_2 < 2) {
    param_2 = 1;
    plVar3 = param_1 + 0xd;
  }
  else {
    plVar3 = (long *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 << 3,PTR__ZSt7nothrow_02cb9a80);
    if (plVar3 == (long *)0x0) {
      param_2 = 1;
      plVar3 = param_1 + 0xd;
    }
  }
  memset(plVar3,0,(ulong)param_2 << 3);
  *(uint *)(param_1 + 0xb) = param_2;
  param_1[10] = (long)plVar3;
  param_1[0xc] = (long)plVar3;
  *(undefined4 *)((long)param_1 + 0x8c) = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  *(undefined1 *)(param_1 + 0x11) = 0;
  param_1[0xe] = 0;
  *param_1 = (long)(PTR__ZTVN4Aska19MappedMemoryManager17IdentifierManagerE_02cc08c8 + 0x10);
  return;
}

// ==== Aska::MappedMemoryManager::MappedMemoryManager(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int)
// vaddr 0x1f2a83c | ghidra 0x202a83c | size 1740 | symbol _ZN4Aska19MappedMemoryManagerC1Ejjjjjjjj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MappedMemoryManagerC2Ejjjjjjjj
               (long *param_1,uint param_2,undefined4 param_3,uint param_4,undefined4 param_5,
               uint param_6,undefined4 param_7,uint param_8,int param_9)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  long *plVar5;
  uint uVar6;
  long *plVar7;
  
  *param_1 = (long)(PTR__ZTVN4Aska19MappedMemoryManagerE_02cbc698 + 0x10);
  Aska::CriticalSection::CriticalSection()(param_1 + 1);
  puVar2 = PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038;
  plVar5 = param_1 + 7;
  *plVar5 = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_19MappedMemoryPointerELb0EEE_02cbb0f0 + 0x10);
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 10) = 0;
  param_1[9] = (long)(puVar2 + 0x10);
  *(undefined1 *)(param_1 + 0xd) = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xf] = 0;
  Aska::TPoolLegacy<Aska::MappedMemoryPointer, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(plVar5,param_3,0,0,0);
  *plVar5 = (long)(PTR__ZTVN4Aska11TBinaryTreeINS_19MappedMemoryPointerEEE_02cc4a20 + 0x10);
  if (param_2 < 2) {
    plVar5 = param_1 + 0x14;
    uVar6 = 1;
  }
  else {
    plVar5 = (long *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 << 3,PTR__ZSt7nothrow_02cb9a80);
    uVar6 = param_2;
    if (plVar5 == (long *)0x0) {
      plVar5 = param_1 + 0x14;
      uVar6 = 1;
    }
  }
  memset(plVar5,0,(ulong)uVar6 << 3);
  plVar7 = param_1 + 0x1b;
  *plVar7 = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_20MappedMemoryRelationELb0EEE_02cc03e0 + 0x10);
  puVar1 = PTR__ZTVN4Aska19MappedMemoryManager14PointerManagerE_02cbb410 + 0x10;
  *(uint *)(param_1 + 0x12) = uVar6;
  param_1[0x11] = (long)plVar5;
  param_1[0x13] = (long)plVar5;
  *(undefined4 *)((long)param_1 + 0xc4) = 0;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  *(undefined1 *)(param_1 + 0x18) = 0;
  param_1[0x15] = 0;
  param_1[7] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x1e) = 0;
  param_1[0x1d] = (long)(puVar2 + 0x10);
  *(undefined1 *)(param_1 + 0x21) = 0;
  param_1[0x1f] = 0;
  param_1[0x20] = 0;
  param_1[0x23] = 0;
  Aska::TPoolLegacy<Aska::MappedMemoryRelation, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(plVar7,param_3,0,0,0);
  *plVar7 = (long)(PTR__ZTVN4Aska11TBinaryTreeINS_20MappedMemoryRelationEEE_02cb76a0 + 0x10);
  if (param_2 < 2) {
    param_2 = 1;
    plVar5 = param_1 + 0x28;
  }
  else {
    plVar5 = (long *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 << 3,PTR__ZSt7nothrow_02cb9a80);
    if (plVar5 == (long *)0x0) {
      param_2 = 1;
      plVar5 = param_1 + 0x28;
    }
  }
  puVar4 = PTR__ZTVN4Aska11TBinaryTreeINS_19MappedMemoryPointerEEE_02cc4a20;
  puVar3 = PTR__ZTVN4Aska11TPoolLegacyINS_19MappedMemoryPointerELb0EEE_02cbb0f0;
  memset(plVar5,0,(ulong)param_2 << 3);
  *(uint *)(param_1 + 0x26) = param_2;
  param_1[0x25] = (long)plVar5;
  param_1[0x27] = (long)plVar5;
  *(undefined4 *)((long)param_1 + 0x164) = 0;
  param_1[0x2a] = 0;
  param_1[0x2b] = 0;
  *(undefined1 *)(param_1 + 0x2c) = 0;
  param_1[0x29] = 0;
  puVar1 = PTR__ZTVN4Aska19MappedMemoryManager15RelationManagerE_02cbc5a8;
  param_1[0x2f] = (long)(puVar2 + 0x10);
  *(undefined4 *)(param_1 + 0x2e) = 0;
  param_1[0x1b] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTVN4Aska11TPoolLegacyINS_20MappedMemoryLocationELb0EEE_02cc0260 + 0x10;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined1 *)(param_1 + 0x33) = 0;
  param_1[0x31] = 0;
  param_1[0x32] = 0;
  param_1[0x2d] = (long)puVar1;
  param_1[0x35] = 0;
  Aska::TPoolLegacy<Aska::MappedMemoryLocation, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1 + 0x2d,param_5,0,0,0);
  param_1[0x2d] = (long)(PTR__ZTVN4Aska11TBinaryTreeINS_20MappedMemoryLocationEEE_02cbab58 + 0x10);
  if (param_4 < 2) {
    param_4 = 1;
    plVar5 = param_1 + 0x3a;
  }
  else {
    plVar5 = (long *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_4 << 3,PTR__ZSt7nothrow_02cb9a80);
    if (plVar5 == (long *)0x0) {
      param_4 = 1;
      plVar5 = param_1 + 0x3a;
    }
  }
  memset(plVar5,0,(ulong)param_4 << 3);
  *(uint *)(param_1 + 0x38) = param_4;
  param_1[0x37] = (long)plVar5;
  param_1[0x39] = (long)plVar5;
  *(undefined4 *)((long)param_1 + 500) = 0;
  param_1[0x3c] = 0;
  param_1[0x3d] = 0;
  *(undefined1 *)(param_1 + 0x3e) = 0;
  param_1[0x3b] = 0;
  puVar1 = PTR__ZTVN4Aska19MappedMemoryManager15LocationManagerE_02cc3b98;
  param_1[0x41] = (long)(puVar3 + 0x10);
  *(undefined4 *)(param_1 + 0x42) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined1 *)(param_1 + 0x47) = 0;
  param_1[0x46] = 0;
  param_1[0x45] = 0;
  param_1[0x43] = (long)(puVar2 + 0x10);
  param_1[0x2d] = (long)(puVar1 + 0x10);
  param_1[0x49] = 0;
  Aska::TPoolLegacy<Aska::MappedMemoryPointer, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1 + 0x41,param_7,0,0,0);
  param_1[0x41] = (long)(puVar4 + 0x10);
  if (param_6 < 2) {
    plVar5 = param_1 + 0x4e;
    uVar6 = 1;
  }
  else {
    plVar5 = (long *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_6 << 3,PTR__ZSt7nothrow_02cb9a80);
    uVar6 = param_6;
    if (plVar5 == (long *)0x0) {
      plVar5 = param_1 + 0x4e;
      uVar6 = 1;
    }
  }
  puVar3 = PTR__ZTVN4Aska19MappedMemoryManager14PointerManagerE_02cbb410;
  memset(plVar5,0,(ulong)uVar6 << 3);
  *(uint *)(param_1 + 0x4c) = uVar6;
  param_1[0x4b] = (long)plVar5;
  param_1[0x4d] = (long)plVar5;
  *(undefined4 *)((long)param_1 + 0x294) = 0;
  param_1[0x51] = 0;
  *(undefined1 *)(param_1 + 0x52) = 0;
  param_1[0x50] = 0;
  param_1[0x4f] = 0;
  *(undefined4 *)(param_1 + 0x56) = 0;
  puVar1 = PTR__ZTVN4Aska11TPoolLegacyINS_22MappedMemoryIdentifierELb0EEE_02cb7218;
  param_1[0x41] = (long)(puVar3 + 0x10);
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(undefined1 *)(param_1 + 0x5b) = 0;
  param_1[0x5a] = 0;
  param_1[0x59] = 0;
  param_1[0x57] = (long)(puVar2 + 0x10);
  param_1[0x55] = (long)(puVar1 + 0x10);
  param_1[0x5d] = 0;
  Aska::TPoolLegacy<Aska::MappedMemoryIdentifier, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1 + 0x55,param_7,0,0,0);
  param_1[0x55] = (long)(PTR__ZTVN4Aska11TBinaryTreeINS_22MappedMemoryIdentifierEEE_02cb8b78 + 0x10)
  ;
  if (param_6 < 2) {
    param_6 = 1;
    plVar5 = param_1 + 0x62;
  }
  else {
    plVar5 = (long *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_6 << 3,PTR__ZSt7nothrow_02cb9a80);
    if (plVar5 == (long *)0x0) {
      param_6 = 1;
      plVar5 = param_1 + 0x62;
    }
  }
  memset(plVar5,0,(ulong)param_6 << 3);
  *(uint *)(param_1 + 0x60) = param_6;
  param_1[0x5f] = (long)plVar5;
  param_1[0x61] = (long)plVar5;
  *(undefined4 *)((long)param_1 + 0x334) = 0;
  param_1[0x65] = 0;
  *(undefined1 *)(param_1 + 0x66) = 0;
  param_1[100] = 0;
  param_1[99] = 0;
  puVar1 = PTR__ZTVN4Aska19MappedMemoryManager17IdentifierManagerE_02cc08c8;
  param_1[0x6b] = (long)(puVar2 + 0x10);
  *(undefined4 *)(param_1 + 0x6a) = 0;
  param_1[0x55] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTVN4Aska11TPoolLegacyINS_8AUIDNodeELb0EEE_02cbc620 + 0x10;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined1 *)(param_1 + 0x6f) = 0;
  param_1[0x6e] = 0;
  param_1[0x6d] = 0;
  param_1[0x69] = (long)puVar1;
  param_1[0x71] = 0;
  Aska::TPoolLegacy<Aska::AUIDNode, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1 + 0x69,param_9,0,0,0);
  param_1[0x69] = (long)(PTR__ZTVN4Aska11TBinaryTreeINS_8AUIDNodeEEE_02cc2ca8 + 0x10);
  if (param_8 < 2) {
    plVar5 = param_1 + 0x76;
    uVar6 = 1;
  }
  else {
    plVar5 = (long *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_8 << 3,PTR__ZSt7nothrow_02cb9a80);
    uVar6 = param_8;
    if (plVar5 == (long *)0x0) {
      plVar5 = param_1 + 0x76;
      uVar6 = 1;
    }
  }
  memset(plVar5,0,(ulong)uVar6 << 3);
  *(uint *)(param_1 + 0x74) = uVar6;
  param_1[0x73] = (long)plVar5;
  param_1[0x75] = (long)plVar5;
  *(undefined4 *)((long)param_1 + 0x3d4) = 0;
  param_1[0x79] = 0;
  *(undefined1 *)(param_1 + 0x7a) = 0;
  param_1[0x78] = 0;
  param_1[0x77] = 0;
  puVar1 = PTR__ZTVN4Aska8AUIDHashE_02cc0bc8;
  param_1[0x7d] = (long)(puVar2 + 0x10);
  *(undefined4 *)(param_1 + 0x7c) = 0;
  param_1[0x69] = (long)(puVar1 + 0x10);
  puVar1 = PTR__ZTVN4Aska11TPoolLegacyINS_11AddressNodeELb0EEE_02cb9ff8 + 0x10;
  *(undefined4 *)(param_1 + 0x7e) = 0;
  *(undefined1 *)(param_1 + 0x81) = 0;
  param_1[0x80] = 0;
  param_1[0x7f] = 0;
  param_1[0x7b] = (long)puVar1;
  param_1[0x83] = 0;
  Aska::TPoolLegacy<Aska::AddressNode, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1 + 0x7b,param_9 << 2,0,0,0);
  param_1[0x7b] = (long)(PTR__ZTVN4Aska11TBinaryTreeINS_11AddressNodeEEE_02cb9e00 + 0x10);
  if (param_8 < 2) {
    param_8 = 1;
    plVar5 = param_1 + 0x88;
  }
  else {
    plVar5 = (long *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_8 << 3,PTR__ZSt7nothrow_02cb9a80);
    if (plVar5 == (long *)0x0) {
      param_8 = 1;
      plVar5 = param_1 + 0x88;
    }
  }
  memset(plVar5,0,(ulong)param_8 << 3);
  *(uint *)(param_1 + 0x86) = param_8;
  param_1[0x85] = (long)plVar5;
  param_1[0x87] = (long)plVar5;
  *(undefined4 *)((long)param_1 + 0x464) = 0;
  param_1[0x8b] = 0;
  *(undefined1 *)(param_1 + 0x8c) = 0;
  param_1[0x8a] = 0;
  param_1[0x89] = 0;
  param_1[0x7b] = (long)(PTR__ZTVN4Aska15TAddressManagerINS_11AddressNodeEEE_02cbd398 + 0x10);
  plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x50,PTR__ZSt7nothrow_02cb9a80);
  if (plVar5 == (long *)0x0) {
    param_1[6] = 0;
  }
  else {
    *(undefined4 *)(plVar5 + 1) = 0;
    puVar1 = PTR__ZTVN4Aska11TPoolLegacyINS_8AUIDElemELb0EEE_02cb6b40 + 0x10;
    *(undefined4 *)(plVar5 + 3) = 0;
    *(undefined1 *)(plVar5 + 6) = 0;
    plVar5[4] = 0;
    plVar5[5] = 0;
    plVar5[2] = (long)(puVar2 + 0x10);
    *plVar5 = (long)puVar1;
    plVar5[8] = 0;
    Aska::TPoolLegacy<Aska::AUIDElem, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(plVar5,param_5,0,0,0);
    param_1[6] = (long)plVar5;
    *(int *)(plVar5 + 1) = (int)plVar5[1] + 1;
  }
  return;
}

// ==== Aska::MappedMemoryManager::~MappedMemoryManager()
// vaddr 0x1f2af08 | ghidra 0x202af08 | size 428 | symbol _ZN4Aska19MappedMemoryManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MappedMemoryManagerD2Ev(long *param_1)

{
  long *plVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  long *plVar5;
  
  plVar1 = param_1 + 1;
  *param_1 = (long)(PTR__ZTVN4Aska19MappedMemoryManagerE_02cbc698 + 0x10);
  Aska::CriticalSection::Enter() const(plVar1);
  plVar5 = (long *)param_1[6];
  if ((plVar5 != (long *)0x0) &&
     (iVar4 = (int)plVar5[1] + -1, *(int *)(plVar5 + 1) = iVar4, iVar4 == 0)) {
    (**(code **)(*plVar5 + 8))();
  }
  Aska::CriticalSection::Leave() const(plVar1);
  param_1[0x7b] = (long)(PTR__ZTVN4Aska5THashINS_11AddressNodeEEE_02cc0728 + 0x10);
  Aska::TBinaryTree<Aska::AddressNode>::FreeTable()(param_1 + 0x7b);
  Aska::TBinaryTree<Aska::AddressNode>::~TBinaryTree()(param_1 + 0x7b);
  param_1[0x69] = (long)(PTR__ZTVN4Aska5THashINS_8AUIDNodeEEE_02cc0720 + 0x10);
  Aska::TBinaryTree<Aska::AUIDNode>::FreeTable()(param_1 + 0x69);
  Aska::TBinaryTree<Aska::AUIDNode>::~TBinaryTree()(param_1 + 0x69);
  plVar5 = param_1 + 0x55;
  param_1[0x55] =
       (long)(PTR__ZTVN4Aska15TCategorizeHashINS_22MappedMemoryIdentifierEEE_02cb7a30 + 0x10);
  Aska::TBinaryTree<Aska::MappedMemoryIdentifier>::FreeTable()(plVar5);
  param_1[0x55] = (long)(PTR__ZTVN4Aska5THashINS_22MappedMemoryIdentifierEEE_02cc3950 + 0x10);
  Aska::TBinaryTree<Aska::MappedMemoryIdentifier>::FreeTable()(plVar5);
  Aska::TBinaryTree<Aska::MappedMemoryIdentifier>::~TBinaryTree()(plVar5);
  plVar5 = param_1 + 0x41;
  puVar2 = PTR__ZTVN4Aska15TCategorizeHashINS_19MappedMemoryPointerEEE_02cbb818 + 0x10;
  param_1[0x41] = (long)puVar2;
  Aska::TBinaryTree<Aska::MappedMemoryPointer>::FreeTable()(plVar5);
  puVar3 = PTR__ZTVN4Aska5THashINS_19MappedMemoryPointerEEE_02cc30a0 + 0x10;
  param_1[0x41] = (long)puVar3;
  Aska::TBinaryTree<Aska::MappedMemoryPointer>::FreeTable()(plVar5);
  Aska::TBinaryTree<Aska::MappedMemoryPointer>::~TBinaryTree()(plVar5);
  plVar5 = param_1 + 0x2d;
  param_1[0x2d] =
       (long)(PTR__ZTVN4Aska15TCategorizeHashINS_20MappedMemoryLocationEEE_02cba5b8 + 0x10);
  Aska::TBinaryTree<Aska::MappedMemoryLocation>::FreeTable()(plVar5);
  param_1[0x2d] = (long)(PTR__ZTVN4Aska5THashINS_20MappedMemoryLocationEEE_02cba720 + 0x10);
  Aska::TBinaryTree<Aska::MappedMemoryLocation>::FreeTable()(plVar5);
  Aska::TBinaryTree<Aska::MappedMemoryLocation>::~TBinaryTree()(plVar5);
  plVar5 = param_1 + 0x1b;
  *plVar5 = (long)(PTR__ZTVN4Aska5THashINS_20MappedMemoryRelationEEE_02cb9b00 + 0x10);
  Aska::TBinaryTree<Aska::MappedMemoryRelation>::FreeTable()(plVar5);
  Aska::TBinaryTree<Aska::MappedMemoryRelation>::~TBinaryTree()(plVar5);
  param_1 = param_1 + 7;
  *param_1 = (long)puVar2;
  Aska::TBinaryTree<Aska::MappedMemoryPointer>::FreeTable()(param_1);
  *param_1 = (long)puVar3;
  Aska::TBinaryTree<Aska::MappedMemoryPointer>::FreeTable()(param_1);
  Aska::TBinaryTree<Aska::MappedMemoryPointer>::~TBinaryTree()(param_1);
  (*(code *)PTR__ZN4Aska15CriticalSectionD2Ev_02c9a1f8)(plVar1);
  return;
}

// ==== Aska::MappedMemoryManager::~MappedMemoryManager()
// vaddr 0x1f2b184 | ghidra 0x202b184 | size 24 | symbol _ZN4Aska19MappedMemoryManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MappedMemoryManagerD0Ev(undefined8 param_1)

{
  Aska::MappedMemoryManager::~MappedMemoryManager()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::MappedMemoryManager::RemoveHandlerEx(Aska::IMappingHandler const*)
// vaddr 0x1f2b1ac | ghidra 0x202b1ac | size 460 | symbol _ZN4Aska19MappedMemoryManager15RemoveHandlerExEPKNS_15IMappingHandlerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MappedMemoryManager15RemoveHandlerExEPKNS_15IMappingHandlerE
               (long param_1,undefined8 param_2)

{
  long *plVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  long *plVar5;
  long lVar6;
  undefined8 *puVar7;
  long *plVar8;
  ulong uVar9;
  long *plVar10;
  code *pcVar11;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  uStack_40 = 0;
  uStack_38 = 0;
  plVar1 = (long *)(param_1 + 0x208);
  uStack_48 = param_2;
  uVar2 = (**(code **)(*(long *)(param_1 + 0x208) + 0x60))(plVar1,&uStack_48);
  uVar9 = (ulong)uVar2;
  if (*(uint *)(param_1 + 0x260) <= uVar2) {
    uVar9 = 0;
  }
  plVar10 = (long *)(*(long *)(param_1 + 600) + uVar9 * 8);
  plVar5 = (long *)*plVar10;
  while (plVar5 != (long *)0x0) {
    while (iVar4 = (**(code **)(*plVar5 + 0x20))(plVar5,&uStack_48), iVar4 < 0) {
      plVar10 = (long *)(*plVar10 + 0x18);
      plVar5 = (long *)*plVar10;
      if (plVar5 == (long *)0x0) goto code_r0x0202b2b4;
    }
    if (iVar4 == 0) {
      plVar10 = (long *)*plVar10;
      if (plVar10 != (long *)0x0) {
        plVar5 = (long *)(param_1 + 0x2a8);
        do {
          lVar6 = (**(code **)(*plVar10 + 0x30))(plVar10);
          puVar7 = (undefined8 *)(**(code **)(*plVar10 + 0x30))(plVar10);
          uStack_58 = *(undefined8 *)(lVar6 + 0x10);
          uStack_60 = *(undefined8 *)(lVar6 + 8);
          uStack_50 = *puVar7;
          pcVar11 = *(code **)(*plVar5 + 0x70);
          uVar3 = (**(code **)(*plVar5 + 0x60))(plVar5,&uStack_60);
          (*pcVar11)(plVar5,&uStack_60,uVar3);
          plVar10 = (long *)plVar10[9];
        } while (plVar10 != (long *)0x0);
      }
      break;
    }
    plVar10 = (long *)(*plVar10 + 0x20);
    plVar5 = (long *)*plVar10;
  }
code_r0x0202b2b4:
  uVar2 = (**(code **)(*(long *)(param_1 + 0x208) + 0x60))(plVar1,&uStack_48);
  uVar9 = (ulong)uVar2;
  if (*(uint *)(param_1 + 0x260) <= uVar2) {
    uVar9 = 0;
  }
  plVar10 = (long *)(*(long *)(param_1 + 600) + uVar9 * 8);
  *(long **)(param_1 + 0x268) = plVar10;
  plVar5 = (long *)*plVar10;
  if (plVar5 == (long *)0x0) {
    plVar8 = (long *)0x0;
  }
  else {
    do {
      while (iVar4 = (**(code **)(*plVar5 + 0x20))(plVar5,&uStack_48), -1 < iVar4) {
        if (iVar4 == 0) goto code_r0x0202b330;
        plVar10 = (long *)(*plVar10 + 0x20);
        plVar5 = (long *)*plVar10;
        plVar8 = (long *)0x0;
        if (plVar5 == (long *)0x0) goto code_r0x0202b334;
      }
      plVar10 = (long *)(*plVar10 + 0x18);
      plVar5 = (long *)*plVar10;
    } while (plVar5 != (long *)0x0);
    plVar8 = (long *)0x0;
  }
code_r0x0202b334:
  while ((plVar8 != (long *)0x0 &&
         (iVar4 = (**(code **)(*plVar8 + 0x20))(plVar8,&uStack_48), iVar4 == 0))) {
    (**(code **)(*plVar1 + 0x40))(plVar1,plVar10);
code_r0x0202b330:
    plVar8 = (long *)*plVar10;
  }
  return;
}

// ==== Aska::MappedMemoryManager::ShouldBeMappedEx(Aska::AFF::AskaFile const*)
// vaddr 0x1f2b3bc | ghidra 0x202b3bc | size 404 | symbol _ZN4Aska19MappedMemoryManager16ShouldBeMappedExEPKNS_3AFF8AskaFileE | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska19MappedMemoryManager16ShouldBeMappedExEPKNS_3AFF8AskaFileE(long param_1,int *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  long *plVar4;
  long *plVar5;
  byte abStack_28 [4];
  byte abStack_24 [4];
  
  if (param_2 != (int *)0x0) {
    iVar2 = Aska::AffUtil::GetTotalIndex()();
    iVar3 = Aska::AffUtil::GetMagicIndex(unsigned int, int*)(*param_2,abStack_28);
    if (iVar3 < iVar2) {
      while (param_2[2] == 0) {
        uVar1 = param_2[3];
        if ((uVar1 < (uint)param_2[1]) && (uVar1 != 0)) {
          return false;
        }
        if ((abStack_28[0] & 1) == 0) {
          return false;
        }
        if (*param_2 == 0x414d4620) {
          iVar3 = Aska::AffUtil::GetTotalIndex()();
          iVar2 = *param_2;
          while( true ) {
            iVar2 = Aska::AffUtil::GetMagicIndex(unsigned int, int*)(iVar2,abStack_24);
            if (iVar3 <= iVar2) {
              return false;
            }
            if (param_2[2] != 0) {
              return false;
            }
            uVar1 = param_2[3];
            if ((uVar1 < (uint)param_2[1]) && (uVar1 != 0)) {
              return false;
            }
            if ((abStack_24[0] & 1) == 0) {
              return false;
            }
            if (*param_2 == 0x414d4620) break;
            if (uVar1 == 0) {
              return false;
            }
            param_2 = (int *)((long)param_2 + (ulong)uVar1);
            iVar2 = *param_2;
          }
          if (param_2[4] != 0x68656164) {
            return false;
          }
          if (param_2[8] != 0x10000) {
            return false;
          }
          plVar5 = *(long **)(param_1 + 0x138);
          plVar4 = (long *)*plVar5;
          if (plVar4 == (long *)0x0) {
            return true;
          }
          do {
            iVar2 = (**(code **)(*plVar4 + 0x20))(plVar4,param_2 + 0xc);
            if (iVar2 < 0) {
              plVar5 = (long *)(*plVar5 + 0x18);
            }
            else {
              if (iVar2 == 0) {
                return *plVar5 == 0;
              }
              plVar5 = (long *)(*plVar5 + 0x20);
            }
            plVar4 = (long *)*plVar5;
          } while (plVar4 != (long *)0x0);
          return true;
        }
        if (uVar1 == 0) {
          return false;
        }
        param_2 = (int *)((long)param_2 + (ulong)uVar1);
        iVar3 = Aska::AffUtil::GetMagicIndex(unsigned int, int*)(*param_2,abStack_28);
        if (iVar2 <= iVar3) {
          return false;
        }
      }
    }
  }
  return false;
}

// ==== Aska::MappedMemoryManager::RegisterMappingEx(void*, Aska::AFF::AskaFile*, void const**)
// vaddr 0x1f2b5c0 | ghidra 0x202b5c0 | size 84 | symbol _ZN4Aska19MappedMemoryManager17RegisterMappingExEPvPNS_3AFF8AskaFileEPPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska19MappedMemoryManager17RegisterMappingExEPvPNS_3AFF8AskaFileEPPKv
          (undefined8 param_1,undefined8 param_2)

{
  ulong uVar1;
  
  uVar1 = Aska::MappedMemoryManager::AttachMappingEx(void*, Aska::AFF::AskaFile*, void const**)();
  if ((uVar1 & 1) != 0) {
    uVar1 = Aska::IMemoryManager::RegisterNotify(void*, Aska::IMemoryNotify*)(param_2,param_1);
    if ((uVar1 & 1) != 0) {
      return 1;
    }
    Aska::MappedMemoryManager::DetachMappingEx(void*, Aska::AUID const*, bool)(param_1,param_2,0,0);
  }
  return 0;
}

// ==== Aska::MappedMemoryManager::AttachMappingEx(void*, Aska::AFF::AskaFile*, void const**)
// vaddr 0x1f2b614 | ghidra 0x202b614 | size 2868 | symbol _ZN4Aska19MappedMemoryManager15AttachMappingExEPvPNS_3AFF8AskaFileEPPKv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

undefined8
_ZN4Aska19MappedMemoryManager15AttachMappingExEPvPNS_3AFF8AskaFileEPPKv
          (long param_1,int *param_2,int *param_3,long param_4)

{
  long lVar1;
  undefined *puVar2;
  undefined *puVar3;
  int *piVar4;
  ushort uVar5;
  ushort uVar6;
  uint *puVar7;
  byte bVar8;
  short sVar9;
  short sVar10;
  uint uVar11;
  bool bVar12;
  bool bVar13;
  int iVar14;
  int iVar15;
  undefined4 uVar16;
  long *plVar17;
  long lVar18;
  long *plVar19;
  long lVar20;
  long lVar21;
  ulong *puVar22;
  uint uVar23;
  uint uVar24;
  undefined8 uVar25;
  ulong uVar26;
  int *piVar27;
  undefined8 uVar28;
  undefined8 uVar29;
  int *piVar30;
  undefined8 uVar31;
  ulong uVar32;
  int *piVar33;
  long *plVar34;
  code *pcVar35;
  int *piVar36;
  ulong uVar37;
  long *plVar38;
  int *piVar39;
  long *plVar40;
  long lVar41;
  long lStack_450;
  long lStack_438;
  long lStack_420;
  long lStack_418;
  undefined8 uStack_410;
  undefined8 uStack_408;
  char acStack_3f4 [4];
  ulong auStack_3f0 [111];
  int *piStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  if (param_3 == (int *)0x0) {
    return 1;
  }
  iVar14 = Aska::AffUtil::GetTotalIndex()();
  iVar15 = Aska::AffUtil::GetMagicIndex(unsigned int, int*)(*param_3,auStack_3f0);
  if (iVar14 <= iVar15) {
    return 1;
  }
  while( true ) {
    if (param_3[2] != 0) {
      return 1;
    }
    uVar24 = param_3[3];
    if ((uVar24 < (uint)param_3[1]) && (uVar24 != 0)) {
      return 1;
    }
    if ((auStack_3f0[0] & 1) == 0) {
      return 1;
    }
    if (*param_3 == 0x414d4620) break;
    if (uVar24 == 0) {
      return 1;
    }
    param_3 = (int *)((long)param_3 + (ulong)uVar24);
    iVar15 = Aska::AffUtil::GetMagicIndex(unsigned int, int*)(*param_3,auStack_3f0);
    if (iVar14 <= iVar15) {
      return 1;
    }
  }
  iVar14 = Aska::AffUtil::GetTotalIndex()();
  iVar15 = Aska::AffUtil::GetMagicIndex(unsigned int, int*)(*param_3,auStack_3f0);
  piVar4 = param_3;
  while( true ) {
    if (iVar14 <= iVar15) {
      return 0;
    }
    if (piVar4[2] != 0) {
      return 0;
    }
    uVar24 = piVar4[3];
    if ((uVar24 < (uint)piVar4[1]) && (uVar24 != 0)) {
      return 0;
    }
    if ((auStack_3f0[0] & 1) == 0) {
      return 0;
    }
    if (*piVar4 == 0x414d4620) break;
    if (uVar24 == 0) {
      return 0;
    }
    piVar4 = (int *)((long)piVar4 + (ulong)uVar24);
    iVar15 = Aska::AffUtil::GetMagicIndex(unsigned int, int*)(*piVar4,auStack_3f0);
  }
  piVar33 = piVar4 + 4;
  if ((((*piVar33 != 0x68656164) || (piVar4[8] != 0x10000)) || (piVar4[10] - 1U < 0x3f)) ||
     (((piVar36 = piVar4 + 0xc, *piVar36 == 0 && (piVar4[0xd] == 0)) &&
      ((piVar4[0xe] == 0 && (piVar4[0xf] == 0)))))) {
    return 0;
  }
  plVar17 = (long *)Aska::IMemoryManager::GetAllocatedManager(void*, unsigned long*)(param_2,auStack_3f0);
  if (plVar17 == (long *)0x0) {
    bVar12 = false;
  }
  else {
    if ((param_3 < param_2) ||
       ((long)param_2 + auStack_3f0[0] < (long)param_3 + (ulong)(uint)param_3[1])) {
      bVar12 = false;
    }
    else {
      bVar12 = true;
    }
    (**(code **)(*plVar17 + 0x50))(plVar17);
  }
  uStack_68 = *(undefined8 *)(piVar4 + 0xe);
  uStack_70 = *(undefined8 *)piVar36;
  plVar40 = (long *)(param_1 + 0x38);
  piStack_78 = param_2;
  uVar16 = (**(code **)(*plVar40 + 0x60))(plVar40,&piStack_78);
  lVar18 = (**(code **)(*plVar40 + 0x80))(plVar40,&piStack_78,uVar16);
  if (lVar18 != 0) {
    return 1;
  }
  uVar16 = (**(code **)(*plVar40 + 0x60))(plVar40,&piStack_78);
  plVar19 = (long *)Aska::TCategorizeHash<Aska::MappedMemoryPointer>::Regist(void const*, unsigned int)(plVar40,&piStack_78,uVar16);
  if (plVar19 == (long *)0x0) {
    return 0;
  }
  plVar38 = (long *)(param_1 + 0xd8);
  lVar18 = (**(code **)(*plVar38 + 0x28))(plVar38,piVar36);
  if (lVar18 == 0) {
    pcVar35 = *(code **)(*plVar40 + 0x70);
    uVar16 = (**(code **)(*plVar40 + 0x60))(plVar40,&piStack_78);
    (*pcVar35)(plVar40,&piStack_78,uVar16);
    return 0;
  }
  plVar34 = *(long **)(param_1 + 0x30);
  plVar40 = *(long **)(lVar18 + 0x40);
  if (plVar40 != plVar34) {
    if (plVar40 != (long *)0x0) {
      iVar14 = (int)plVar40[1] + -1;
      *(int *)(plVar40 + 1) = iVar14;
      if (iVar14 == 0) {
        (**(code **)(*plVar40 + 8))();
      }
      *(undefined8 *)(lVar18 + 0x40) = 0;
    }
    if (plVar34 != (long *)0x0) {
      *(int *)(plVar34 + 1) = (int)plVar34[1] + 1;
      *(long **)(lVar18 + 0x40) = plVar34;
    }
  }
  do {
    plVar40 = plVar19;
    plVar19 = (long *)plVar40[8];
  } while ((long *)plVar40[8] != (long *)0x0);
  for (; plVar40 != (long *)0x0; plVar40 = (long *)plVar40[9]) {
    lVar20 = (**(code **)(*plVar40 + 0x30))(plVar40);
    pcVar35 = *(code **)(*plVar38 + 0x80);
    uVar16 = (**(code **)(*plVar38 + 0x60))(plVar38,lVar20 + 8);
    lVar20 = (*pcVar35)(plVar38,lVar20 + 8,uVar16);
    *(uint *)(lVar20 + 0x38) =
         *(uint *)(lVar20 + 0x38) & 0x80000000 | *(uint *)(lVar20 + 0x38) + 1 & 0x7fffffff;
  }
  if ((*(uint *)(lVar18 + 0x38) & 0x7fffffff) == 1) {
    *(int *)(lVar18 + 0x3c) = piVar4[9];
    uVar24 = piVar4[7];
    if (uVar24 != 0) {
      memset(auStack_3f0 + 0x4a,0,0x128);
      auStack_3f0[1] = 0;
      auStack_3f0[2] = 0;
      auStack_3f0[0] = 0;
      auStack_3f0[3] = 0;
      auStack_3f0[4] = 0;
      auStack_3f0[5] = 0;
      auStack_3f0[6] = 0;
      auStack_3f0[7] = 0;
      auStack_3f0[8] = 0;
      auStack_3f0[9] = 0;
      auStack_3f0[10] = 0;
      auStack_3f0[0xb] = 0;
      auStack_3f0[0xc] = 0;
      auStack_3f0[0xd] = 0;
      auStack_3f0[0xe] = 0;
      auStack_3f0[0xf] = 0;
      auStack_3f0[0x10] = 0;
      auStack_3f0[0x11] = 0;
      auStack_3f0[0x12] = 0;
      auStack_3f0[0x13] = 0;
      auStack_3f0[0x14] = 0;
      auStack_3f0[0x15] = 0;
      auStack_3f0[0x16] = 0;
      auStack_3f0[0x17] = 0;
      auStack_3f0[0x18] = 0;
      auStack_3f0[0x19] = 0;
      auStack_3f0[0x1a] = 0;
      auStack_3f0[0x1b] = 0;
      auStack_3f0[0x1c] = 0;
      auStack_3f0[0x1d] = 0;
      auStack_3f0[0x1e] = 0;
      auStack_3f0[0x1f] = 0;
      auStack_3f0[0x20] = 0;
      auStack_3f0[0x21] = 0;
      auStack_3f0[0x22] = 0;
      auStack_3f0[0x23] = 0;
      auStack_3f0[0x24] = 0;
      auStack_3f0[0x25] = 0;
      auStack_3f0[0x26] = 0;
      auStack_3f0[0x27] = 0;
      auStack_3f0[0x28] = 0;
      auStack_3f0[0x29] = 0;
      auStack_3f0[0x2a] = 0;
      auStack_3f0[0x2b] = 0;
      auStack_3f0[0x2c] = 0;
      auStack_3f0[0x2d] = 0;
      auStack_3f0[0x2e] = 0;
      auStack_3f0[0x2f] = 0;
      auStack_3f0[0x30] = 0;
      auStack_3f0[0x31] = 0;
      auStack_3f0[0x32] = 0;
      auStack_3f0[0x33] = 0;
      auStack_3f0[0x34] = 0;
      auStack_3f0[0x35] = 0;
      auStack_3f0[0x36] = 0;
      auStack_3f0[0x37] = 0;
      auStack_3f0[0x38] = 0;
      auStack_3f0[0x39] = 0;
      auStack_3f0[0x3a] = 0;
      auStack_3f0[0x3b] = 0;
      auStack_3f0[0x3c] = 0;
      auStack_3f0[0x3d] = 0;
      auStack_3f0[0x3e] = 0;
      auStack_3f0[0x3f] = 0;
      auStack_3f0[0x40] = 0;
      auStack_3f0[0x41] = 0;
      auStack_3f0[0x42] = 0;
      auStack_3f0[0x43] = 0;
      auStack_3f0[0x44] = 0;
      auStack_3f0[0x45] = 0;
      auStack_3f0[0x46] = 0;
      auStack_3f0[0x47] = 0;
      auStack_3f0[0x48] = 0;
      auStack_3f0[0x49] = 0;
      piVar39 = (int *)((long)piVar33 + (ulong)uVar24);
      lVar20 = PrepareForMappedAddressIterator(Aska::AFF::AskaChunk*, Aska::MappedAddressIterator*, unsigned int)(piVar33,auStack_3f0,0x25);
      iVar14 = *piVar39;
      if (iVar14 == 0x62756666) {
        lStack_450 = 0;
        do {
          Hint_Prefetch((long)piVar39 + (ulong)(uint)piVar39[3],0,2,0);
          sVar9 = (short)piVar39[0xb];
          uVar26 = (ulong)((int)sVar9 + 0x12) & 0xffff;
          auStack_3f0[uVar26 + 0x4a] = (ulong)piVar39;
          sVar10 = (short)piVar39[0xb];
          if (sVar10 < 1) {
            lStack_438 = (long)piVar39 + *(long *)(piVar39 + 6);
            if (bVar12) {
              lVar21 = lStack_438;
              if (lStack_450 != 0) {
                lVar21 = lStack_450;
              }
            }
            else {
              uVar23 = (uint)sVar10;
              uVar24 = -uVar23;
              if (-1 < (int)uVar23) {
                uVar24 = uVar23;
              }
              puVar7 = (uint *)(piVar39 + 8);
              if (uVar24 != 0) {
                puVar7 = (uint *)(piVar39 + 9);
              }
              uVar23 = *puVar7;
              uVar37 = *(ulong *)(piVar39 + 4);
              plVar40 = (long *)Aska::Global::GetAvailableMemoryManager()();
              bVar13 = false;
              if ((uVar24 < 0x13) &&
                 (((uVar24 = 1 << (ulong)(uVar24 & 0x1f), (uVar24 & 0x10410) != 0 ||
                   ((uVar24 & 0x20820) != 0)) || ((uVar24 & 0x41040) != 0)))) {
                bVar13 = true;
              }
              if (((uint)(uVar23 == 0xffffffff) == -uVar23) &&
                 (lVar20 = uVar37 - ((uVar37 / 0xffffffff << 0x20) - uVar37 / 0xffffffff),
                 lVar20 != 0)) {
                uVar37 = (uVar37 + 0xffffffff) - lVar20;
              }
              if (uVar23 < 2) {
                if (bVar13) {
                  pcVar35 = (code *)((undefined8 *)*plVar40)[1];
                }
                else {
                  pcVar35 = *(code **)*plVar40;
                }
                lVar41 = (*pcVar35)(plVar40,uVar37);
              }
              else {
                if (bVar13) {
                  pcVar35 = *(code **)(*plVar40 + 0x18);
                }
                else {
                  pcVar35 = *(code **)(*plVar40 + 0x10);
                }
                lVar41 = (*pcVar35)(plVar40,uVar37,uVar23);
              }
              if (lVar41 == 0) {
                acStack_3f4[0] = '\0';
                lVar20 = 0;
                goto code_r0x0202bc8c;
              }
              lVar20 = memcpy(lVar41,lStack_438,uVar37);
              acStack_3f4[0] = '\x01';
              lVar21 = lStack_450;
              lStack_438 = lVar41;
            }
            lStack_450 = lVar21;
            puVar22 = auStack_3f0 + uVar26 * 2;
            lVar41 = lStack_438;
            if (lStack_438 == 0) {
code_r0x0202bce8:
              lStack_438 = 0;
              lVar41 = (long)piVar39 + *(long *)(piVar39 + 6);
            }
            lStack_420 = CONCAT62(lStack_420._2_6_,(short)piVar39[0xb]);
            lVar20 = Aska::MappedMemoryManager::TranslateMappedBufferEx(Aska::MappedTarget, void const*, unsigned long, unsigned int, unsigned int, Aska::MappedAddressIterator*, unsigned long, bool*)(lVar20,&lStack_420,lVar41,*(undefined8 *)(piVar39 + 4),
                                     piVar39[9],piVar39[8],puVar22,*(undefined8 *)(piVar39 + 0xc),
                                     acStack_3f4);
            lVar41 = lVar20;
            if (acStack_3f4[0] == '\0') goto code_r0x0202c12c;
          }
          else {
            uVar24 = -(int)sVar9;
            if (-1 < sVar9) {
              uVar24 = (int)sVar9;
            }
            uVar37 = (ulong)uVar24;
            lVar41 = *(long *)(param_4 + uVar37 * 8);
            if (lVar41 == 0) {
              if (*(long *)(piVar4 + 0x12) != 0) {
code_r0x0202bc8c:
                puVar22 = auStack_3f0 + uVar26 * 2;
                goto code_r0x0202bce8;
              }
              goto code_r0x0202c12c;
            }
            if ((int)sVar10 - 7U < 0xc) {
              lStack_420 = CONCAT62(lStack_420._2_6_,sVar10);
              lVar21 = Aska::MappedMemoryManager::TranslateMappedBufferEx(Aska::MappedTarget, void const*, unsigned long, unsigned int, unsigned int, Aska::MappedAddressIterator*, unsigned long, bool*)(lVar20,&lStack_420,lVar41,*(undefined8 *)(piVar39 + 4),
                                       piVar39[9],piVar39[8],auStack_3f0 + uVar26 * 2,
                                       *(undefined8 *)(piVar39 + 0xc),acStack_3f4);
              plVar40 = (long *)Aska::IMemoryManager::GetAllocatedManager(void*, unsigned long*)(lVar41,0);
              lVar20 = 0;
              if (plVar40 != (long *)0x0) {
                lVar20 = (**(code **)(*plVar40 + 0x40))(plVar40,lVar41);
              }
              *(undefined8 *)(param_4 + uVar37 * 8) = 0;
              if (acStack_3f4[0] == '\0') goto code_r0x0202c12c;
              lStack_438 = 0;
              lVar41 = lVar21;
            }
            else {
              *(undefined8 *)(param_4 + uVar37 * 8) = 0;
              lStack_438 = 0;
            }
          }
          sVar9 = (short)piVar39[0xb];
          uVar25 = *(undefined8 *)(piVar39 + 4);
          iVar14 = -(int)sVar9;
          if (-1 < sVar9) {
            iVar14 = (int)sVar9;
          }
          piVar27 = piVar39 + 0xc;
          if (0xb < iVar14 - 7U) {
            piVar27 = piVar39 + 4;
          }
          iVar14 = piVar39[8];
          iVar15 = piVar39[9];
          uVar29 = *(undefined8 *)piVar27;
          lVar21 = lVar18 + (ulong)(ushort)(sVar9 + 0x12U) * 8;
          lVar1 = lVar18 + (ulong)(ushort)(sVar9 + 0x12U) * 4;
          *(long *)(lVar21 + 0x48) = lStack_438;
          *(long *)(lVar21 + 0x170) = lVar41;
          *(undefined8 *)(lVar21 + 0x298) = uVar25;
          *(undefined8 *)(lVar21 + 0x3c0) = uVar29;
          *(int *)(lVar1 + 0x4e8) = iVar15;
          *(int *)(lVar1 + 0x57c) = iVar14;
          if (piVar39[3] == 0) {
            iVar14 = *piVar39;
            break;
          }
          piVar39 = (int *)((long)piVar39 + (ulong)(uint)piVar39[3]);
          iVar14 = *piVar39;
        } while (iVar14 == 0x62756666);
      }
      else {
        lStack_450 = 0;
      }
      if (iVar14 == 0x61646472) {
        plVar40 = (long *)(param_1 + 0x168);
        puVar2 = PTR__ZTVN4Aska8AUIDElemE_02cb7e98 + 0x10;
        do {
          uVar24 = piVar39[3];
          Hint_Prefetch((long)piVar39 + (ulong)uVar24,0,2,0);
          sVar9 = (short)piVar39[0xf];
          if (auStack_3f0[((ulong)((int)sVar9 + 0x12) & 0xffff) + 0x4a] == 0) {
code_r0x0202c12c:
            Aska::MappedMemoryManager::DetachMappingEx(void*, Aska::AUID const*, bool)(param_1,param_2,0,0);
            return 0;
          }
          if (*(char *)((long)piVar39 + 0x3e) != '\v') {
            Aska::AmfUtil::GetTargetTypeFromAmfUsage(unsigned char)();
            goto code_r0x0202c12c;
          }
          bVar8 = *(byte *)((long)piVar39 + 0x3f);
          if ((bVar8 & 5) == 0) {
            lStack_418 = *(long *)(piVar39 + 6);
            lStack_420 = *(long *)(piVar39 + 4);
            uStack_408 = *(undefined8 *)(piVar4 + 0xe);
            uStack_410 = *(undefined8 *)piVar36;
            pcVar35 = *(code **)(*plVar40 + 0x80);
            uVar16 = (**(code **)(*plVar40 + 0x60))(plVar40,&lStack_420);
            lVar20 = (*pcVar35)(plVar40,&lStack_420,uVar16);
            if (lVar20 != 0) goto code_r0x0202c12c;
            lVar20 = *(long *)(lVar18 + 0x40);
            if (lVar20 == 0) {
code_r0x0202bfe8:
              plVar19 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
              if (plVar19 == (long *)0x0) goto code_r0x0202c12c;
              plVar19[2] = 0;
              *plVar19 = (long)puVar2;
              plVar19[1] = 0;
            }
            else {
              if (*(uint *)(lVar20 + 0x2c) <= *(uint *)(lVar20 + 0x3c)) goto code_r0x0202bfe8;
              lVar41 = *(long *)(lVar20 + 0x20);
              uVar24 = *(uint *)(lVar20 + 0x38);
              do {
                uVar23 = uVar24;
                if (*(uint *)(lVar20 + 0x2c) <= uVar23) {
                  uVar23 = 0;
                }
                uVar11 = 1 << (ulong)(uVar23 & 0x1f);
                uVar24 = uVar23 + 1;
              } while ((uVar11 & *(uint *)(lVar41 + (ulong)(uVar23 >> 5) * 4)) != 0);
              uVar37 = *(long *)(lVar20 + 0x40) + (ulong)uVar23 * 0x28;
              uVar26 = uVar37;
              do {
                uVar32 = uVar26 + 0x7f & 0xffffffffffffff81;
                Hint_Prefetch(uVar26,0,2,0);
                uVar26 = uVar32;
              } while (uVar32 < uVar37 + 0x28);
              lVar21 = (ulong)(uVar23 >> 5) * 4;
              *(uint *)(lVar20 + 0x38) = uVar23 + 1;
              *(uint *)(lVar20 + 0x3c) = *(uint *)(lVar20 + 0x3c) + 1;
              *(uint *)(lVar41 + lVar21) = *(uint *)(lVar41 + lVar21) | uVar11;
              plVar19 = (long *)(*(long *)(lVar20 + 0x40) + (ulong)uVar23 * 0x28);
              puVar3 = PTR__ZTVN4Aska8AUIDElemE_02cb7e98 + 0x10;
              plVar19[1] = 0;
              plVar19[2] = 0;
              *plVar19 = (long)puVar3;
              plVar19 = (long *)(*(long *)(lVar20 + 0x40) + (ulong)uVar23 * 0x28);
              if (plVar19 == (long *)0x0) goto code_r0x0202bfe8;
            }
            plVar19[4] = lStack_418;
            plVar19[3] = lStack_420;
            lVar20 = *(long *)(lVar18 + 0x620);
            plVar19[1] = lVar20;
            plVar19[2] = lVar18 + 0x618;
            *(long **)(lVar18 + 0x620) = plVar19;
            *(long **)(lVar20 + 0x10) = plVar19;
            *(int *)(lVar18 + 0x640) = *(int *)(lVar18 + 0x640) + 1;
            uVar16 = (**(code **)(*plVar40 + 0x60))(plVar40,&lStack_420);
            lVar20 = Aska::TCategorizeHash<Aska::MappedMemoryLocation>::Regist(void const*, unsigned int)(plVar40,&lStack_420,uVar16);
            if (lVar20 == 0) goto code_r0x0202c12c;
            if (sVar9 < 1) {
              uVar25 = *(undefined8 *)(piVar39 + 10);
              sVar10 = (short)piVar39[0xf];
              iVar14 = -(int)sVar10;
              if (-1 < sVar10) {
                iVar14 = (int)sVar10;
              }
              bVar13 = 0xb < iVar14 - 7U;
              piVar27 = piVar39 + 0x14;
              if (bVar13) {
                piVar27 = piVar39 + 10;
              }
              uVar29 = *(undefined8 *)(piVar39 + 8);
              piVar30 = piVar39 + 0x12;
              if (bVar13) {
                piVar30 = piVar39 + 8;
              }
            }
            else {
              sVar10 = (short)piVar39[0xf];
              iVar14 = -(int)sVar10;
              if (-1 < sVar10) {
                iVar14 = (int)sVar10;
              }
              uVar25 = 0;
              uVar29 = 0;
              piVar27 = piVar39 + 0x14;
              piVar30 = piVar39 + 0x12;
              if (0xb < iVar14 - 7U) {
                piVar27 = piVar39 + 10;
                piVar30 = piVar39 + 8;
              }
            }
            uVar28 = *(undefined8 *)piVar27;
            uVar31 = *(undefined8 *)piVar30;
            bVar13 = (bVar8 & 0x18) == 0x10;
            *(undefined8 *)(lVar20 + 0x60) = uVar25;
            *(undefined8 *)(lVar20 + 0x68) = uVar28;
            uVar5 = *(ushort *)(lVar20 + 0x5a) | 1;
            if (bVar13) {
              uVar5 = *(ushort *)(lVar20 + 0x5a) & 0xfffe;
            }
            uVar6 = uVar5 | 2;
            if (bVar13) {
              uVar6 = uVar5 & 0xfffd;
            }
            *(short *)(lVar20 + 0x58) = sVar9;
            *(ushort *)(lVar20 + 0x5a) = uVar6;
            *(undefined8 *)(lVar20 + 0x70) = uVar29;
            *(undefined8 *)(lVar20 + 0x78) = uVar31;
            uVar24 = piVar39[3];
          }
        } while ((uVar24 != 0) &&
                (piVar39 = (int *)((long)piVar39 + (ulong)uVar24), *piVar39 == 0x61646472));
      }
      goto code_r0x0202bda4;
    }
  }
  lStack_450 = 0;
code_r0x0202bda4:
  if (!(bool)(plVar17 != (long *)0x0 & bVar12)) {
    return 1;
  }
  if (*(long *)(piVar4 + 0x12) != 0) {
    lVar18 = *(long *)(piVar4 + 0x12) + (long)piVar33;
    (**(code **)(*plVar17 + 0x20))(plVar17,lVar18 - (long)param_2,param_2,1);
    param_3[1] = (int)lVar18 - (int)param_3;
    if (*(long *)(piVar4 + 0x10) != 0) {
      *(undefined4 *)((long)piVar33 + *(long *)(piVar4 + 0x10) + 0xc) = 0;
    }
    piVar4[0x12] = 0;
    piVar4[0x13] = 0;
  }
  if (lStack_450 == 0) {
    return 1;
  }
  (**(code **)(*plVar17 + 0x28))(plVar17,param_2,lStack_450);
  param_3[1] = (-0x40 - (int)param_3) + (int)lStack_450;
  return 1;
}

// ==== Aska::MappedMemoryManager::LocationManager::Register(void const*)
// vaddr 0x1f2c890 | ghidra 0x202c890 | size 52 | symbol _ZN4Aska19MappedMemoryManager15LocationManager8RegisterEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MappedMemoryManager15LocationManager8RegisterEPKv(long *param_1,undefined8 param_2)

{
  undefined4 uVar1;
  
  uVar1 = (**(code **)(*param_1 + 0x60))();
  (*(code *)PTR__ZN4Aska15TCategorizeHashINS_20MappedMemoryLocationEE6RegistEPKvj_02c90c60)
            (param_1,param_2,uVar1);
  return;
}

// ==== Aska::MappedMemoryManager::DetachMappingEx(void*, Aska::AUID const*, bool)
// vaddr 0x1f2c8c4 | ghidra 0x202c8c4 | size 1032 | symbol _ZN4Aska19MappedMemoryManager15DetachMappingExEPvPKNS_4AUIDEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MappedMemoryManager15DetachMappingExEPvPKNS_4AUIDEb
               (long param_1,undefined8 param_2,undefined8 *param_3)

{
  long lVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  long lVar6;
  long lVar7;
  long *plVar8;
  ulong uVar9;
  long *plVar10;
  long *plVar11;
  long *plVar12;
  code *pcVar13;
  long *plVar14;
  long lVar15;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  uStack_78 = param_2;
  if (param_3 == (undefined8 *)0x0) {
    uStack_70 = 0;
    uStack_68 = 0;
    uVar4 = (**(code **)(*(long *)(param_1 + 0x38) + 0x60))((long *)(param_1 + 0x38),&uStack_78);
    uVar9 = (ulong)uVar4;
    if (*(uint *)(param_1 + 0x90) <= uVar4) {
      uVar9 = 0;
    }
    plVar14 = (long *)(*(long *)(param_1 + 0x88) + uVar9 * 8);
    plVar10 = (long *)*plVar14;
    if (plVar10 == (long *)0x0) goto code_r0x0202cbfc;
    do {
      while (iVar5 = (**(code **)(*plVar10 + 0x20))(plVar10,&uStack_78), iVar5 < 0) {
        plVar14 = (long *)(*plVar14 + 0x18);
        plVar10 = (long *)*plVar14;
        if (plVar10 == (long *)0x0) goto code_r0x0202cbcc;
      }
      if (iVar5 == 0) {
        plVar14 = (long *)*plVar14;
        goto joined_r0x0202cbc8;
      }
      plVar14 = (long *)(*plVar14 + 0x20);
      plVar10 = (long *)*plVar14;
    } while (plVar10 != (long *)0x0);
  }
  else {
    uStack_68 = param_3[1];
    uStack_70 = *param_3;
    plVar14 = (long *)(param_1 + 0x38);
    pcVar13 = *(code **)(*plVar14 + 0x80);
    uVar3 = (**(code **)(*plVar14 + 0x60))(plVar14,&uStack_78);
    plVar14 = (long *)(*pcVar13)(plVar14,&uStack_78,uVar3);
joined_r0x0202cbc8:
    if (plVar14 != (long *)0x0) {
      plVar10 = (long *)(param_1 + 0xd8);
      plVar11 = (long *)(param_1 + 0x348);
      plVar12 = (long *)(param_1 + 0x168);
      do {
        lVar6 = (**(code **)(*plVar14 + 0x30))(plVar14);
        lVar1 = lVar6 + 8;
        pcVar13 = *(code **)(*plVar10 + 0x80);
        uVar3 = (**(code **)(*plVar10 + 0x60))(plVar10,lVar1);
        lVar7 = (*pcVar13)(plVar10,lVar1,uVar3);
        if ((lVar7 != 0) &&
           (uVar4 = *(uint *)(lVar7 + 0x38) + 0x7fffffff,
           *(uint *)(lVar7 + 0x38) = *(uint *)(lVar7 + 0x38) & 0x80000000 | uVar4 & 0x7fffffff,
           (uVar4 & 0x7fffffff) == 0)) {
          pcVar13 = *(code **)(*plVar11 + 0x68);
          uVar3 = (**(code **)(*plVar11 + 0x60))(plVar11,lVar1);
          (*pcVar13)(plVar11,lVar1,uVar3);
          lVar15 = *(long *)(lVar7 + 0x628);
          if (lVar7 + 0x618 != *(long *)(lVar7 + 0x628)) {
            while (lVar15 != 0) {
              uStack_98 = *(undefined8 *)(lVar15 + 0x20);
              uStack_a0 = *(undefined8 *)(lVar15 + 0x18);
              uStack_90 = *(undefined4 *)(lVar6 + 8);
              uStack_8c = *(undefined4 *)(lVar6 + 0xc);
              uStack_88 = *(undefined4 *)(lVar6 + 0x10);
              uStack_84 = *(undefined4 *)(lVar6 + 0x14);
              pcVar13 = *(code **)(*plVar12 + 0x70);
              uVar3 = (**(code **)(*plVar12 + 0x60))(plVar12,&uStack_a0);
              (*pcVar13)(plVar12,&uStack_a0,uVar3);
              plVar8 = (long *)(lVar15 + 0x10);
              lVar15 = 0;
              if (lVar7 + 0x618 != *plVar8) {
                lVar15 = *plVar8;
              }
            }
          }
          uVar4 = 0x12;
          iVar5 = 0xffee;
          do {
            lVar6 = lVar7 + (ulong)(ushort)((short)iVar5 + 0x12) * 8;
            lVar15 = *(long *)(lVar6 + 0x48);
            lVar6 = *(long *)(lVar6 + 0x170);
            uVar2 = iVar5 - 0x10000;
            if ((short)iVar5 < 0) {
              uVar2 = uVar4;
            }
            if ((lVar15 != 0) && (plVar8 = (long *)Aska::IMemoryManager::GetAllocatedManager(void*, unsigned long*)(lVar15,0), plVar8 != (long *)0x0)
               ) {
              (**(code **)(*plVar8 + 0x40))(plVar8,lVar15);
            }
            if (((((uVar2 != 0) && (lVar6 != 0)) && (uVar2 < 0x11)) &&
                ((1 << (ulong)(uVar2 & 0x1f) & 0x12492U) != 0)) &&
               (((lVar15 = Aska::MemoryHandleManager::GetAllocatedManager(void const*, unsigned long*)(lVar6,0), lVar15 == 0 ||
                 (uVar9 = Aska::MemoryHandleManager::FreeEx(void*)(lVar15,lVar6), (uVar9 & 1) == 0)) &&
                (lVar15 = Aska::MemoryManager::GetAllocatedManager(void const*)(lVar6), lVar15 != 0)))) {
              Aska::MemoryManager::LocalFree(void*)(lVar15,lVar6);
            }
            uVar4 = uVar4 - 1;
            iVar5 = iVar5 + 1;
          } while (uVar4 != 0xffffffed);
          pcVar13 = *(code **)(*plVar10 + 0x70);
          uVar3 = (**(code **)(*plVar10 + 0x60))(plVar10,lVar1);
          (*pcVar13)(plVar10,lVar1,uVar3);
        }
        if (param_3 != (undefined8 *)0x0) goto code_r0x0202cbd0;
        plVar14 = (long *)plVar14[9];
      } while (plVar14 != (long *)0x0);
      goto code_r0x0202cbfc;
    }
  }
code_r0x0202cbcc:
  if (param_3 != (undefined8 *)0x0) {
code_r0x0202cbd0:
    plVar14 = (long *)(param_1 + 0x38);
    pcVar13 = *(code **)(*plVar14 + 0x70);
    uVar3 = (**(code **)(*plVar14 + 0x60))(plVar14,&uStack_78);
    (*pcVar13)(plVar14,&uStack_78,uVar3);
    return;
  }
code_r0x0202cbfc:
  plVar14 = (long *)(param_1 + 0x38);
  uVar4 = (**(code **)(*plVar14 + 0x60))(plVar14,&uStack_78);
  uVar9 = (ulong)uVar4;
  if (*(uint *)(param_1 + 0x90) <= uVar4) {
    uVar9 = 0;
  }
  plVar10 = (long *)(*(long *)(param_1 + 0x88) + uVar9 * 8);
  *(long **)(param_1 + 0x98) = plVar10;
  plVar11 = (long *)*plVar10;
  if (plVar11 == (long *)0x0) {
    plVar12 = (long *)0x0;
  }
  else {
    do {
      while (iVar5 = (**(code **)(*plVar11 + 0x20))(plVar11,&uStack_78), iVar5 < 0) {
        plVar10 = (long *)(*plVar10 + 0x18);
        plVar11 = (long *)*plVar10;
        if (plVar11 == (long *)0x0) {
          plVar12 = (long *)0x0;
          goto code_r0x0202cc9c;
        }
      }
      if (iVar5 == 0) goto code_r0x0202cc98;
      plVar10 = (long *)(*plVar10 + 0x20);
      plVar11 = (long *)*plVar10;
      plVar12 = (long *)0x0;
    } while (plVar11 != (long *)0x0);
  }
code_r0x0202cc9c:
  while ((plVar12 != (long *)0x0 &&
         (iVar5 = (**(code **)(*plVar12 + 0x20))(plVar12,&uStack_78), iVar5 == 0))) {
    (**(code **)(*plVar14 + 0x40))(plVar14,plVar10);
code_r0x0202cc98:
    plVar12 = (long *)*plVar10;
  }
  return;
}

// ==== Aska::MappedMemoryManager::QueryMappingEx(Aska::IMappingHandler const*, Aska::AUID const*, unsigned long*, Aska::MappedTarget*)
// vaddr 0x1f2cfc4 | ghidra 0x202cfc4 | size 108 | symbol _ZN4Aska19MappedMemoryManager14QueryMappingExEPKNS_15IMappingHandlerEPKNS_4AUIDEPmPNS_12MappedTargetE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Removing unreachable block (ram,0x0202d004) */
/* WARNING: Removing unreachable block (ram,0x0202d008) */

undefined8
_ZN4Aska19MappedMemoryManager14QueryMappingExEPKNS_15IMappingHandlerEPKNS_4AUIDEPmPNS_12MappedTargetE
          (void)

{
  ulong uVar1;
  undefined8 *in_x3;
  undefined8 uStack_28;
  
  uVar1 = Aska::MappedMemoryManager::QueryResourcesEx(Aska::IMappingHandler const*, Aska::AUID const*, void**, void**, unsigned long*, unsigned long*, Aska::MappedTarget*)();
  if (((uVar1 & 1) != 0) && (in_x3 != (undefined8 *)0x0)) {
    *in_x3 = uStack_28;
  }
  return 0;
}

// ==== Aska::MappedMemoryManager::IdentifierManager::Register(void const*)
// vaddr 0x1f2d3e8 | ghidra 0x202d3e8 | size 52 | symbol _ZN4Aska19MappedMemoryManager17IdentifierManager8RegisterEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MappedMemoryManager17IdentifierManager8RegisterEPKv(long *param_1,undefined8 param_2)

{
  undefined4 uVar1;
  
  uVar1 = (**(code **)(*param_1 + 0x60))();
  (*(code *)PTR__ZN4Aska15TCategorizeHashINS_22MappedMemoryIdentifierEE6RegistEPKvj_02ca9c90)
            (param_1,param_2,uVar1);
  return;
}

// ==== Aska::MappedMemoryManager::FlushMappingEx()
// vaddr 0x1f2d530 | ghidra 0x202d530 | size 1184 | symbol _ZN4Aska19MappedMemoryManager14FlushMappingExEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MappedMemoryManager14FlushMappingExEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  ulong uVar3;
  undefined8 uVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  long *plVar8;
  long *plVar9;
  undefined8 *puVar10;
  long *plVar11;
  long lVar12;
  long *plVar13;
  char cVar14;
  ulong uVar15;
  code *pcVar16;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  
  if (*(int *)(param_1 + 0x3d4) == 0) {
    return;
  }
  cVar14 = '\0';
  plVar8 = (long *)0x0;
  plVar13 = (long *)(param_1 + 0x2a8);
  plVar1 = (long *)(param_1 + 0x3d8);
  plVar2 = (long *)(param_1 + 0x208);
  *(undefined8 *)(param_1 + 0x3c8) = 0;
  *(undefined1 *)(param_1 + 0x3d0) = 0;
code_r0x0202d678:
  if (plVar8 == (long *)0x0) {
    plVar8 = *(long **)(param_1 + 0x3b8);
    *(long **)(param_1 + 0x3c8) = plVar8;
    if (plVar8 == (long *)0x0) {
      *(undefined1 *)(param_1 + 0x3d0) = 1;
code_r0x0202d850:
      uVar6 = *(uint *)(param_1 + 0x3a0);
      if ((uVar6 != 0) &&
         ((**(code **)(*(long *)(param_1 + 0x348) + 0x18))
                    (param_1 + 0x348,*(undefined8 *)(param_1 + 0x398)), uVar6 != 1)) {
        uVar15 = 1;
        do {
          uVar3 = uVar15;
          if (*(uint *)(param_1 + 0x3a0) <= uVar15) {
            uVar3 = 0;
          }
          (**(code **)(*(long *)(param_1 + 0x348) + 0x18))
                    (param_1 + 0x348,*(long *)(param_1 + 0x398) + uVar3 * 8);
          uVar15 = uVar15 + 1;
        } while (uVar6 != uVar15);
      }
      cVar14 = '\0';
      plVar13 = (long *)0x0;
      *(undefined1 *)(param_1 + 0x3d0) = 0;
      *(undefined8 *)(param_1 + 0x3c0) = 0;
      *(undefined8 *)(param_1 + 0x3c8) = 0;
      *(undefined8 *)(param_1 + 0x3b8) = 0;
      *(undefined8 *)(param_1 + 0x458) = 0;
      *(undefined1 *)(param_1 + 0x460) = 0;
code_r0x0202d8d8:
      if (plVar13 == (long *)0x0) {
        plVar13 = *(long **)(param_1 + 0x448);
        *(long **)(param_1 + 0x458) = plVar13;
        if (plVar13 == (long *)0x0) {
          *(undefined1 *)(param_1 + 0x460) = 1;
code_r0x0202d950:
          uVar6 = *(uint *)(param_1 + 0x430);
          if ((uVar6 != 0) &&
             ((**(code **)(*(long *)(param_1 + 0x3d8) + 0x18))
                        (param_1 + 0x3d8,*(undefined8 *)(param_1 + 0x428)), uVar6 != 1)) {
            uVar15 = 1;
            do {
              uVar3 = uVar15;
              if (*(uint *)(param_1 + 0x430) <= uVar15) {
                uVar3 = 0;
              }
              (**(code **)(*(long *)(param_1 + 0x3d8) + 0x18))
                        (param_1 + 0x3d8,*(long *)(param_1 + 0x428) + uVar3 * 8);
              uVar15 = uVar15 + 1;
            } while (uVar6 != uVar15);
          }
          *(undefined1 *)(param_1 + 0x460) = 0;
          *(undefined8 *)(param_1 + 0x450) = 0;
          *(undefined8 *)(param_1 + 0x458) = 0;
          *(undefined8 *)(param_1 + 0x448) = 0;
          return;
        }
      }
      if (cVar14 == '\0') {
        puVar10 = (undefined8 *)(**(code **)(*plVar13 + 0x30))();
        (**(code **)(*(long *)*puVar10 + 0x10))();
        plVar13 = *(long **)(param_1 + 0x458);
        if (plVar13 != (long *)0x0) goto code_r0x0202d920;
        plVar13 = *(long **)(param_1 + 0x448);
        *(long **)(param_1 + 0x458) = plVar13;
        if (plVar13 != (long *)0x0) goto code_r0x0202d920;
        goto code_r0x0202d8d0;
      }
      goto code_r0x0202d950;
    }
  }
  if (cVar14 == '\0') {
    puVar10 = (undefined8 *)(**(code **)(*plVar8 + 0x30))();
    uStack_68 = puVar10[1];
    uStack_70 = *puVar10;
    uStack_60 = 0;
    uVar6 = (**(code **)(*(long *)(param_1 + 0x2a8) + 0x60))(plVar13,&uStack_70);
    uVar15 = (ulong)uVar6;
    if (*(uint *)(param_1 + 0x300) <= uVar6) {
      uVar15 = 0;
    }
    plVar8 = (long *)(*(long *)(param_1 + 0x2f8) + uVar15 * 8);
    plVar11 = (long *)*plVar8;
joined_r0x0202d6d8:
    if (plVar11 == (long *)0x0) goto code_r0x0202d584;
    iVar5 = (**(code **)(*plVar11 + 0x20))(plVar11,&uStack_70);
    if (iVar5 < 0) {
      plVar8 = (long *)(*plVar8 + 0x18);
      plVar11 = (long *)*plVar8;
      goto joined_r0x0202d6d8;
    }
    if (iVar5 != 0) {
      plVar8 = (long *)(*plVar8 + 0x20);
      plVar11 = (long *)*plVar8;
      goto joined_r0x0202d6d8;
    }
    for (plVar8 = (long *)*plVar8; plVar8 != (long *)0x0; plVar8 = (long *)plVar8[9]) {
      lVar12 = (**(code **)(*plVar8 + 0x30))(plVar8);
      uStack_78 = *(undefined8 *)(lVar12 + 0x10);
      uVar6 = (**(code **)(*(long *)(param_1 + 0x3d8) + 0x60))(plVar1,&uStack_78);
      uVar15 = (ulong)uVar6;
      if (*(uint *)(param_1 + 0x430) <= uVar6) {
        uVar15 = 0;
      }
      plVar11 = (long *)(*(long *)(param_1 + 0x428) + uVar15 * 8);
      *(long **)(param_1 + 0x438) = plVar11;
      plVar9 = (long *)*plVar11;
      while (plVar9 != (long *)0x0) {
        while (iVar5 = (**(code **)(*plVar9 + 0x20))(plVar9,&uStack_78), iVar5 < 0) {
          plVar11 = (long *)(*plVar11 + 0x18);
          plVar9 = (long *)*plVar11;
          if (plVar9 == (long *)0x0) goto code_r0x0202d7b8;
        }
        if (iVar5 == 0) goto code_r0x0202d7d0;
        plVar11 = (long *)(*plVar11 + 0x20);
        plVar9 = (long *)*plVar11;
      }
code_r0x0202d7b8:
      lVar12 = (**(code **)(*plVar1 + 0x10))(plVar1,&uStack_78);
      *plVar11 = lVar12;
code_r0x0202d7d0:
      uVar4 = uStack_78;
      puVar10 = (undefined8 *)(**(code **)(*plVar8 + 0x30))(plVar8);
      uStack_90 = uVar4;
      if (puVar10 == (undefined8 *)0x0) {
        uStack_88 = 0;
        uStack_80 = 0;
      }
      else {
        uStack_88 = *puVar10;
        uStack_80 = puVar10[1];
      }
      pcVar16 = *(code **)(*plVar2 + 0x70);
      uVar7 = (**(code **)(*plVar2 + 0x60))(plVar2,&uStack_90);
      (*pcVar16)(plVar2,&uStack_90,uVar7);
    }
code_r0x0202d584:
    uVar6 = (**(code **)(*(long *)(param_1 + 0x2a8) + 0x60))(plVar13,&uStack_70);
    uVar15 = (ulong)uVar6;
    if (*(uint *)(param_1 + 0x300) <= uVar6) {
      uVar15 = 0;
    }
    plVar8 = (long *)(*(long *)(param_1 + 0x2f8) + uVar15 * 8);
    *(long **)(param_1 + 0x308) = plVar8;
    plVar11 = (long *)*plVar8;
    if (plVar11 == (long *)0x0) {
      plVar9 = (long *)0x0;
    }
    else {
      do {
        while (iVar5 = (**(code **)(*plVar11 + 0x20))(plVar11,&uStack_70), -1 < iVar5) {
          if (iVar5 == 0) goto code_r0x0202d600;
          plVar8 = (long *)(*plVar8 + 0x20);
          plVar11 = (long *)*plVar8;
          plVar9 = (long *)0x0;
          if (plVar11 == (long *)0x0) goto code_r0x0202d604;
        }
        plVar8 = (long *)(*plVar8 + 0x18);
        plVar11 = (long *)*plVar8;
      } while (plVar11 != (long *)0x0);
      plVar9 = (long *)0x0;
    }
code_r0x0202d604:
    while ((plVar9 != (long *)0x0 &&
           (iVar5 = (**(code **)(*plVar9 + 0x20))(plVar9,&uStack_70), iVar5 == 0))) {
      (**(code **)(*plVar13 + 0x40))(plVar13,plVar8);
code_r0x0202d600:
      plVar9 = (long *)*plVar8;
    }
    plVar8 = *(long **)(param_1 + 0x3c8);
    if (plVar8 != (long *)0x0) goto code_r0x0202d630;
    plVar8 = *(long **)(param_1 + 0x3b8);
    *(long **)(param_1 + 0x3c8) = plVar8;
    if (plVar8 != (long *)0x0) goto code_r0x0202d630;
    goto code_r0x0202d670;
  }
  goto code_r0x0202d850;
code_r0x0202d630:
  cVar14 = *(char *)(param_1 + 0x3d0);
  if (cVar14 == '\0') {
    if (plVar8 != *(long **)(param_1 + 0x3c0)) {
      plVar8 = (long *)plVar8[2];
      cVar14 = '\0';
      *(long **)(param_1 + 0x3c8) = plVar8;
      if (plVar8 != (long *)0x0) goto code_r0x0202d678;
    }
code_r0x0202d670:
    cVar14 = '\x01';
    *(undefined1 *)(param_1 + 0x3d0) = 1;
  }
  goto code_r0x0202d678;
code_r0x0202d920:
  cVar14 = *(char *)(param_1 + 0x460);
  if (cVar14 == '\0') {
    if (plVar13 != *(long **)(param_1 + 0x450)) {
      plVar13 = (long *)plVar13[2];
      cVar14 = '\0';
      *(long **)(param_1 + 0x458) = plVar13;
      if (plVar13 != (long *)0x0) goto code_r0x0202d8d8;
    }
code_r0x0202d8d0:
    cVar14 = '\x01';
    *(undefined1 *)(param_1 + 0x460) = 1;
  }
  goto code_r0x0202d8d8;
}

// ==== Aska::MappedMemoryManager::PointerManager::~PointerManager()
// vaddr 0x1f2eecc | ghidra 0x202eecc | size 72 | symbol _ZN4Aska19MappedMemoryManager14PointerManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MappedMemoryManager14PointerManagerD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska15TCategorizeHashINS_19MappedMemoryPointerEEE_02cbb818 + 0x10);
  Aska::TBinaryTree<Aska::MappedMemoryPointer>::FreeTable()();
  *param_1 = (long)(PTR__ZTVN4Aska5THashINS_19MappedMemoryPointerEEE_02cc30a0 + 0x10);
  Aska::TBinaryTree<Aska::MappedMemoryPointer>::FreeTable()(param_1);
  Aska::TBinaryTree<Aska::MappedMemoryPointer>::~TBinaryTree()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::MappedMemoryManager::MoveHandler(void const*, void const*)
// vaddr 0x1f31024 | ghidra 0x2031024 | size 84 | symbol _ZN4Aska19MappedMemoryManager11MoveHandlerEPKvS2_ | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska19MappedMemoryManager11MoveHandlerEPKvS2_
               (long param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  
  Aska::CriticalSection::Enter() const(param_1 + 8);
  uVar1 = Aska::MappedMemoryManager::MoveMappingEx(void*, void*)(param_1,param_2,param_3);
  Aska::CriticalSection::Leave() const(param_1 + 8);
  return uVar1 & 1;
}

// ==== Aska::MappedMemoryManager::FreeHandler(void const*)
// vaddr 0x1f31078 | ghidra 0x2031078 | size 76 | symbol _ZN4Aska19MappedMemoryManager11FreeHandlerEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19MappedMemoryManager11FreeHandlerEPKv(long param_1,undefined8 param_2)

{
  Aska::CriticalSection::Enter() const(param_1 + 8);
  Aska::IMemoryManager::RemoveNotify(void*, Aska::IMemoryNotify*)(param_2,param_1);
  Aska::MappedMemoryManager::DetachMappingEx(void*, Aska::AUID const*, bool)(param_1,param_2,0,0);
  (*(code *)PTR__ZNK4Aska15CriticalSection5LeaveEv_02ca8d00)(param_1 + 8);
  return;
}
