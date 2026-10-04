// port/decomp/containers/pool.c: Ghidra decompiles for the containers subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileAt.java, tools/resolve_decomp.py
// run      2026-10-04 05:12 UTC: tools/decomp_at.sh '--into' 'containers/pool' '202d9d0' '2035dc0' '2035fb4' '20361a8' '203639c' '2036588' '203677c' '20367ac' '2036844' '20368c8' '2036abc' '2051ba4' '2052df8' '2074df8' '2076210' '2076358' '20764a0' '20765e4' '2076728' '2076870' '20769b8' '2076b00' '2076c48' '2076d88' '21a0bc4' '21a0d6c' '21bd7f8' '21df790' '21df914' '21dfa78' '21dfab4' '21e07d8' '21e1500' '21e1d9c' '21e7700' '21f9b64' '21fae5c' '21fc960' '21fe55c' '2236880' '224c4f0' '224c774' '2269534' '2273570' '227370c' '22738a8' '2273a80' '2281878' '2281af0' '22c0440' '22c0730' '22c8080' '22c8218' '22df6ac' '22e070c' '22e1a64' '22e63d0' '22e6a2c' '22e6d2c' '22e6fec' '230261c' '2302764' '23028ac' '230b2f4' '2326d80' '2328084' '232abac' '232ff14' '2335e64' '24571dc' '2457514' '269e42c'

// ==== Aska::TAddressManager<Aska::AddressNode>::Register(void const*)
// vaddr 0x1f2d9d0 | ghidra 0x202d9d0 | size 184 | symbol _ZN4Aska15TAddressManagerINS_11AddressNodeEE8RegisterEPKv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska15TAddressManagerINS_11AddressNodeEE8RegisterEPKv(long *param_1,undefined8 param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  ulong uVar6;
  long *plVar7;
  
  uVar1 = (**(code **)(*param_1 + 0x60))();
  uVar6 = (ulong)uVar1;
  if (*(uint *)(param_1 + 0xb) <= uVar1) {
    uVar6 = 0;
  }
  plVar7 = (long *)(param_1[10] + uVar6 * 8);
  param_1[0xc] = (long)plVar7;
  plVar3 = (long *)*plVar7;
  while (plVar3 != (long *)0x0) {
    while (iVar2 = (**(code **)(*plVar3 + 0x20))(plVar3,param_2), iVar2 < 0) {
      plVar7 = (long *)(*plVar7 + 0x18);
      plVar3 = (long *)*plVar7;
      if (plVar3 == (long *)0x0) goto code_r0x0202da50;
    }
    if (iVar2 == 0) goto code_r0x0202da6c;
    plVar7 = (long *)(*plVar7 + 0x20);
    plVar3 = (long *)*plVar7;
  }
code_r0x0202da50:
  lVar4 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar7 = lVar4;
  lVar5 = 0;
  if (lVar4 != 0) {
code_r0x0202da6c:
    if (plVar7 == (long *)0x0) {
      lVar5 = 0;
    }
    else {
      lVar5 = *plVar7;
    }
  }
  return lVar5;
}

// ==== Aska::TPoolLegacy<Aska::AUIDNode, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f35dc0 | ghidra 0x2035dc0 | size 500 | symbol _ZN4Aska11TPoolLegacyINS_8AUIDNodeELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_8AUIDNodeELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x38,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x02035f78;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x02035f18;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x02035f78:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x02035f18:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x38);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::MappedMemoryPointer, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f35fb4 | ghidra 0x2035fb4 | size 500 | symbol _ZN4Aska11TPoolLegacyINS_19MappedMemoryPointerELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_19MappedMemoryPointerELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x50,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x0203616c;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x0203610c;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x0203616c:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x0203610c:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x50);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::MappedMemoryRelation, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f361a8 | ghidra 0x20361a8 | size 500 | symbol _ZN4Aska11TPoolLegacyINS_20MappedMemoryRelationELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_20MappedMemoryRelationELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x648,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x02036360;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x02036300;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x02036360:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x02036300:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x648);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::MappedMemoryLocation, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f3639c | ghidra 0x203639c | size 492 | symbol _ZN4Aska11TPoolLegacyINS_20MappedMemoryLocationELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_20MappedMemoryLocationELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 << 7,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x0203654c;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x020364f0;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x0203654c:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x020364f0:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 << 7);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::MappedMemoryIdentifier, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f36588 | ghidra 0x2036588 | size 500 | symbol _ZN4Aska11TPoolLegacyINS_22MappedMemoryIdentifierELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_22MappedMemoryIdentifierELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x50,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x02036740;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x020366e0;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x02036740:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x020366e0:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x50);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TAddressManager<Aska::AddressNode>::~TAddressManager()
// vaddr 0x1f3677c | ghidra 0x203677c | size 48 | symbol _ZN4Aska15TAddressManagerINS_11AddressNodeEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TAddressManagerINS_11AddressNodeEED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska5THashINS_11AddressNodeEEE_02cc0728 + 0x10);
  Aska::TBinaryTree<Aska::AddressNode>::FreeTable()();
  Aska::TBinaryTree<Aska::AddressNode>::~TBinaryTree()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TAddressManager<Aska::AddressNode>::IsRegistered(void const*)
// vaddr 0x1f367ac | ghidra 0x20367ac | size 152 | symbol _ZN4Aska15TAddressManagerINS_11AddressNodeEE12IsRegisteredEPKv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska15TAddressManagerINS_11AddressNodeEE12IsRegisteredEPKv
               (long *param_1,undefined8 param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  uVar1 = (**(code **)(*param_1 + 0x60))();
  uVar4 = (ulong)uVar1;
  if (*(uint *)(param_1 + 0xb) <= uVar1) {
    uVar4 = 0;
  }
  plVar5 = (long *)(param_1[10] + uVar4 * 8);
  plVar3 = (long *)*plVar5;
  do {
    if (plVar3 == (long *)0x0) {
      return false;
    }
    while (iVar2 = (**(code **)(*plVar3 + 0x20))(plVar3,param_2), -1 < iVar2) {
      if (iVar2 == 0) {
        return *plVar5 != 0;
      }
      plVar5 = (long *)(*plVar5 + 0x20);
      plVar3 = (long *)*plVar5;
      if (plVar3 == (long *)0x0) {
        return false;
      }
    }
    plVar5 = (long *)(*plVar5 + 0x18);
    plVar3 = (long *)*plVar5;
  } while( true );
}

// ==== Aska::TAddressManager<Aska::AddressNode>::CalcHashValue(void const*) const
// vaddr 0x1f36844 | ghidra 0x2036844 | size 132 | symbol _ZNK4Aska15TAddressManagerINS_11AddressNodeEE13CalcHashValueEPKv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK4Aska15TAddressManagerINS_11AddressNodeEE13CalcHashValueEPKv(long param_1,byte *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = *(uint *)(param_1 + 0x58);
  uVar2 = 0;
  if (uVar1 != 0) {
    uVar2 = *param_2 / uVar1;
  }
  uVar2 = (uint)param_2[1] + ((uint)*param_2 - uVar2 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[2] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[3] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[4] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[5] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[6] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[7] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  return uVar2 - uVar3 * uVar1;
}

// ==== Aska::TPoolLegacy<Aska::AddressNode, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f368c8 | ghidra 0x20368c8 | size 500 | symbol _ZN4Aska11TPoolLegacyINS_11AddressNodeELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_11AddressNodeELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x30,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x02036a80;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x02036a20;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x02036a80:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x02036a20:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x30);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::AUIDElem, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f36abc | ghidra 0x2036abc | size 500 | symbol _ZN4Aska11TPoolLegacyINS_8AUIDElemELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_8AUIDElemELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x28,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x02036c74;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x02036c14;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x02036c74:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x02036c14:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x28);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::ClassNameSet, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f51ba4 | ghidra 0x2051ba4 | size 492 | symbol _ZN4Aska11TPoolLegacyINS_12ClassNameSetELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_12ClassNameSetELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 << 6,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x02051d54;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x02051cf8;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x02051d54:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x02051cf8:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 << 6);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::ParamNameSet, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f52df8 | ghidra 0x2052df8 | size 492 | symbol _ZN4Aska11TPoolLegacyINS_12ParamNameSetELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_12ParamNameSetELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 << 6,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x02052fa8;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x02052f4c;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x02052fa8:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x02052f4c:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 << 6);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolAtomicDynamic<Aska::DiscReadStream::ReadAsyncNotify>::~TPoolAtomicDynamic()
// vaddr 0x1f74df8 | ghidra 0x2074df8 | size 200 | symbol _ZN4Aska18TPoolAtomicDynamicINS_14DiscReadStream15ReadAsyncNotifyEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18TPoolAtomicDynamicINS_14DiscReadStream15ReadAsyncNotifyEED2Ev(long *param_1)

{
  long lVar1;
  long lVar2;
  
  *param_1 = (long)(
                   PTR__ZTVN4Aska18TPoolAtomicDynamicINS_14DiscReadStream15ReadAsyncNotifyEEE_02cc1350
                   + 0x10);
  if ((*(char *)((long)param_1 + 0x21) == '\0') || ((char)param_1[4] == '\0'))
  goto code_r0x02074ea0;
  if (param_1[2] != 0) {
    operator delete[](void*)();
    param_1[2] = 0;
  }
  if ((long *)param_1[1] == (long *)0x0) goto code_r0x02074ea0;
  if (*(int *)((long)param_1 + 0x24) < 1) {
code_r0x02074e98:
    operator delete[](void*)();
  }
  else {
    (**(code **)(*(long *)param_1[1] + 8))();
    if (1 < *(int *)((long)param_1 + 0x24)) {
      lVar1 = 1;
      lVar2 = 0x50;
      do {
        (**(code **)(*(long *)(param_1[1] + lVar2) + 8))();
        lVar1 = lVar1 + 1;
        lVar2 = lVar2 + 0x50;
      } while (lVar1 < *(int *)((long)param_1 + 0x24));
    }
    if (param_1[1] != 0) goto code_r0x02074e98;
  }
  param_1[1] = 0;
code_r0x02074ea0:
  *(undefined4 *)((long)param_1 + 0x24) = 0;
  *(undefined4 *)((long)param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 3) = 0;
  *(undefined2 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 3) = 0;
  return;
}

// ==== Aska::TPoolLegacy<Aska::SEControlObject, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f76210 | ghidra 0x2076210 | size 328 | symbol _ZN4Aska11TPoolLegacyINS_15SEControlObjectELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_15SEControlObjectELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)(param_1 + 0x20);
  if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar5 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
code_r0x020762fc:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x340,0x10,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x020762b4;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x020762b4:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x340);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x020762fc;
      }
      lVar4 = *(long *)(param_1 + 0x40);
    }
    if (lVar4 != 0) {
      if (*(char *)(param_1 + 0x48) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    *(char *)(param_1 + 0x48) = '\0';
    if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar3 = 0;
    *plVar5 = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return uVar3;
}

// ==== Aska::TPoolLegacy<Aska::BGMControlObject, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f76358 | ghidra 0x2076358 | size 328 | symbol _ZN4Aska11TPoolLegacyINS_16BGMControlObjectELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_16BGMControlObjectELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)(param_1 + 0x20);
  if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar5 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
code_r0x02076444:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x230,8,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x020763fc;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x020763fc:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x230);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x02076444;
      }
      lVar4 = *(long *)(param_1 + 0x40);
    }
    if (lVar4 != 0) {
      if (*(char *)(param_1 + 0x48) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    *(char *)(param_1 + 0x48) = '\0';
    if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar3 = 0;
    *plVar5 = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return uVar3;
}

// ==== Aska::TPoolLegacy<Aska::SoundHandle, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f764a0 | ghidra 0x20764a0 | size 324 | symbol _ZN4Aska11TPoolLegacyINS_11SoundHandleELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_11SoundHandleELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)(param_1 + 0x20);
  if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar5 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
code_r0x02076588:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 << 5,8,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x02076540;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x02076540:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 << 5);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x02076588;
      }
      lVar4 = *(long *)(param_1 + 0x40);
    }
    if (lVar4 != 0) {
      if (*(char *)(param_1 + 0x48) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    *(char *)(param_1 + 0x48) = '\0';
    if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar3 = 0;
    *plVar5 = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return uVar3;
}

// ==== Aska::TPoolLegacy<Aska::AudioMessageNote, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f765e4 | ghidra 0x20765e4 | size 324 | symbol _ZN4Aska11TPoolLegacyINS_16AudioMessageNoteELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_16AudioMessageNoteELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)(param_1 + 0x20);
  if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar5 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
code_r0x020766cc:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 << 6,8,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x02076684;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x02076684:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 << 6);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x020766cc;
      }
      lVar4 = *(long *)(param_1 + 0x40);
    }
    if (lVar4 != 0) {
      if (*(char *)(param_1 + 0x48) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    *(char *)(param_1 + 0x48) = '\0';
    if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar3 = 0;
    *plVar5 = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return uVar3;
}

// ==== Aska::TPoolLegacy<Aska::SLVoice, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f76728 | ghidra 0x2076728 | size 328 | symbol _ZN4Aska11TPoolLegacyINS_7SLVoiceELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_7SLVoiceELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)(param_1 + 0x20);
  if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar5 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
code_r0x02076814:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x648,8,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x020767cc;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x020767cc:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x648);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x02076814;
      }
      lVar4 = *(long *)(param_1 + 0x40);
    }
    if (lVar4 != 0) {
      if (*(char *)(param_1 + 0x48) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    *(char *)(param_1 + 0x48) = '\0';
    if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar3 = 0;
    *plVar5 = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return uVar3;
}

// ==== Aska::TPoolLegacy<Aska::SoundCommand, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f76870 | ghidra 0x2076870 | size 328 | symbol _ZN4Aska11TPoolLegacyINS_12SoundCommandELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_12SoundCommandELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)(param_1 + 0x20);
  if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar5 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
code_r0x0207695c:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0xa8,8,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x02076914;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x02076914:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0xa8);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x0207695c;
      }
      lVar4 = *(long *)(param_1 + 0x40);
    }
    if (lVar4 != 0) {
      if (*(char *)(param_1 + 0x48) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    *(char *)(param_1 + 0x48) = '\0';
    if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar3 = 0;
    *plVar5 = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return uVar3;
}

// ==== Aska::TPoolLegacy<Aska::SoundPass, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f769b8 | ghidra 0x20769b8 | size 328 | symbol _ZN4Aska11TPoolLegacyINS_9SoundPassELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_9SoundPassELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)(param_1 + 0x20);
  if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar5 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
code_r0x02076aa4:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0xe8,8,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x02076a5c;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x02076a5c:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0xe8);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x02076aa4;
      }
      lVar4 = *(long *)(param_1 + 0x40);
    }
    if (lVar4 != 0) {
      if (*(char *)(param_1 + 0x48) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    *(char *)(param_1 + 0x48) = '\0';
    if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar3 = 0;
    *plVar5 = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return uVar3;
}

// ==== Aska::TPoolLegacy<Aska::AudioInterface, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f76b00 | ghidra 0x2076b00 | size 328 | symbol _ZN4Aska11TPoolLegacyINS_14AudioInterfaceELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_14AudioInterfaceELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)(param_1 + 0x20);
  if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar5 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
code_r0x02076bec:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x28,8,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x02076ba4;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x02076ba4:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x28);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x02076bec;
      }
      lVar4 = *(long *)(param_1 + 0x40);
    }
    if (lVar4 != 0) {
      if (*(char *)(param_1 + 0x48) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    *(char *)(param_1 + 0x48) = '\0';
    if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar3 = 0;
    *plVar5 = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return uVar3;
}

// ==== Aska::TPoolLegacy<Aska::SoundServer::AskaAdpcmDecodeBuffer, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f76c48 | ghidra 0x2076c48 | size 320 | symbol _ZN4Aska11TPoolLegacyINS_11SoundServer21AskaAdpcmDecodeBufferELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_11SoundServer21AskaAdpcmDecodeBufferELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)(param_1 + 0x20);
  if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar5 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
code_r0x02076d30:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x6000,1,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x02076ce8;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x02076ce8:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x6000);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x02076d30;
      }
      lVar4 = *(long *)(param_1 + 0x40);
    }
    if (lVar4 != 0) {
      if (*(char *)(param_1 + 0x48) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    *(char *)(param_1 + 0x48) = '\0';
    if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar3 = 0;
    *plVar5 = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return uVar3;
}

// ==== Aska::TPoolLegacy<Aska::SoundServer::FilePathBuffer, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1f76d88 | ghidra 0x2076d88 | size 320 | symbol _ZN4Aska11TPoolLegacyINS_11SoundServer14FilePathBufferELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_11SoundServer14FilePathBufferELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)(param_1 + 0x20);
  if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar5 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
code_r0x02076e70:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x104,1,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x02076e28;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x02076e28:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x104);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x02076e70;
      }
      lVar4 = *(long *)(param_1 + 0x40);
    }
    if (lVar4 != 0) {
      if (*(char *)(param_1 + 0x48) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    *(char *)(param_1 + 0x48) = '\0';
    if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar3 = 0;
    *plVar5 = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return uVar3;
}

// ==== Aska::TPoolFast<Aska::DynamicsPrimitiveElement, true>::SecurePool(unsigned int, Aska::DynamicsPrimitiveElement*)
// vaddr 0x20a0bc4 | ghidra 0x21a0bc4 | size 412 | symbol _ZN4Aska9TPoolFastINS_24DynamicsPrimitiveElementELb1EE10SecurePoolEjPS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9TPoolFastINS_24DynamicsPrimitiveElementELb1EE10SecurePoolEjPS1_
          (long param_1,uint param_2,long param_3)

{
  uint uVar1;
  undefined *puVar2;
  ulong *puVar3;
  long lVar4;
  undefined8 uVar5;
  long lVar6;
  uint uVar7;
  ulong uVar8;
  uint *puVar9;
  
  Aska::TPoolFast<Aska::DynamicsPrimitiveElement, true>::ReleasePool()();
  if (param_2 == 0) {
    return 1;
  }
  if (param_3 == 0) {
    uVar8 = (ulong)param_2;
    puVar3 = (ulong *)operator new[](unsigned long, std::nothrow_t const&)(uVar8 << 6 | 8,PTR__ZSt7nothrow_02cb9a80);
    puVar2 = PTR__ZTVN4Aska24DynamicsPrimitiveElementE_02cbbef0;
    if (puVar3 != (ulong *)0x0) {
      *puVar3 = uVar8;
      lVar4 = 0;
      do {
        lVar6 = lVar4 + 0x40;
        *(undefined8 *)((long)puVar3 + lVar4 + 0x18) = 0;
        *(undefined8 *)((long)puVar3 + lVar4 + 0x20) = 0;
        *(undefined **)((long)puVar3 + lVar4 + 8) = puVar2 + 0x10;
        *(undefined8 *)((long)puVar3 + lVar4 + 0x10) = 0;
        *(undefined4 *)((long)puVar3 + lVar4 + 0x38) = 0x100;
        *(undefined1 *)((long)puVar3 + lVar4 + 0x3e) = 0;
        *(undefined8 *)((long)puVar3 + lVar4 + 0x28) = 0;
        *(undefined8 *)((long)puVar3 + lVar4 + 0x30) = 0;
        *(undefined1 *)((long)puVar3 + lVar4 + 0x3c) = 1;
        *(undefined8 *)((long)puVar3 + lVar4 + 0x40) = 0;
        lVar4 = lVar6;
      } while (uVar8 * 0x40 - lVar6 != 0);
      *(ulong **)(param_1 + 0x30) = puVar3 + 1;
      *(undefined1 *)(param_1 + 0xd0) = 1;
      goto code_r0x021a0c6c;
    }
    *(undefined8 *)(param_1 + 0x30) = 0;
code_r0x021a0d44:
    Aska::TPoolFast<Aska::DynamicsPrimitiveElement, true>::ReleasePool()(param_1);
    uVar5 = 0;
  }
  else {
    *(long *)(param_1 + 0x30) = param_3;
code_r0x021a0c6c:
    uVar8 = (ulong)param_2 + 0x3f >> 6;
    uVar7 = (uint)uVar8;
    if ((*(char *)(param_1 + 0x28) == '\0') || (uVar1 = *(uint *)(param_1 + 0x20), uVar1 < uVar7)) {
      if ((*(long *)(param_1 + 0x18) != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
        operator delete[](void*)();
        *(undefined1 *)(param_1 + 0x28) = 0;
      }
      puVar9 = (uint *)(param_1 + 0x20);
      *puVar9 = uVar7;
      *(uint *)(param_1 + 0x24) = param_2;
      lVar6 = uVar8 << 3;
      lVar4 = operator new[](unsigned long, std::nothrow_t const&)(lVar6,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x18) = lVar4;
      *(undefined1 *)(param_1 + 0x28) = 1;
      if (lVar4 == 0) {
        *(undefined1 *)(param_1 + 0x28) = 0;
        puVar9[0] = 0;
        puVar9[1] = 0;
        goto code_r0x021a0d44;
      }
      if (uVar7 == 0) goto code_r0x021a0d28;
      memset(lVar4,0,lVar6);
      *(undefined8 *)(param_1 + 0x38) = 0;
    }
    else {
      *(uint *)(param_1 + 0x24) = param_2;
      if (uVar1 == 0) {
code_r0x021a0d28:
        *(undefined8 *)(param_1 + 0x38) = 0;
        return 1;
      }
      memset(*(undefined8 *)(param_1 + 0x18),0,uVar1 << 3);
      uVar7 = *(uint *)(param_1 + 0x20);
      *(undefined8 *)(param_1 + 0x38) = 0;
      if (uVar7 == 0) {
        return 1;
      }
    }
    memset(*(undefined8 *)(param_1 + 0x18),0,uVar7 << 3);
    uVar5 = 1;
  }
  return uVar5;
}

// ==== Aska::TPoolFast<Aska::DynamicsPrimitiveElement, true>::ReleasePool()
// vaddr 0x20a0d6c | ghidra 0x21a0d6c | size 204 | symbol _ZN4Aska9TPoolFastINS_24DynamicsPrimitiveElementELb1EE11ReleasePoolEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9TPoolFastINS_24DynamicsPrimitiveElementELb1EE11ReleasePoolEv(long param_1)

{
  undefined *puVar1;
  long lVar2;
  int iVar3;
  long *plVar4;
  long lVar5;
  long lVar6;
  
  if (*(char *)(param_1 + 0xd0) == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    lVar6 = *(long *)(param_1 + 0x30);
    if (lVar6 != 0) {
      lVar5 = *(long *)(lVar6 + -8);
      if (lVar5 != 0) {
        lVar5 = lVar5 << 6;
        puVar1 = PTR__ZTVN4Aska24DynamicsPrimitiveElementE_02cbbef0 + 0x10;
        do {
          lVar2 = lVar6 + lVar5;
          plVar4 = *(long **)(lVar2 + -8);
          *(undefined **)(lVar2 + -0x40) = puVar1;
          if (plVar4 != (long *)0x0) {
            iVar3 = (int)plVar4[5] + -1;
            *(int *)(plVar4 + 5) = iVar3;
            if (iVar3 == 0) {
              (**(code **)(*plVar4 + 8))();
            }
            *(undefined8 *)(lVar2 + -8) = 0;
          }
          Aska::DynamicsHandler::~DynamicsHandler()(lVar2 + -0x40);
          lVar5 = lVar5 + -0x40;
        } while (lVar5 != 0);
      }
      operator delete[](void*)((long *)(lVar6 + -8));
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    *(undefined1 *)(param_1 + 0xd0) = 0;
  }
  if ((*(long *)(param_1 + 0x18) != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *(long *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  return;
}

// ==== Aska::TPoolFast<Aska::Vector, false>::Scoop(int)
// vaddr 0x20bd7f8 | ghidra 0x21bd7f8 | size 508 | symbol _ZN4Aska9TPoolFastINS_6VectorELb0EE5ScoopEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska9TPoolFastINS_6VectorELb0EE5ScoopEi(long param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  ulong *puVar9;
  int iVar10;
  ulong uVar11;
  uint uVar12;
  long lVar13;
  int iVar14;
  long lVar15;
  
  uVar4 = *(uint *)(param_1 + 0x24);
  if ((uint)(*(int *)(param_1 + 0x3c) + param_2) <= uVar4) {
    uVar5 = *(uint *)(param_1 + 0x38);
    iVar6 = param_2 + -1;
    iVar14 = (uVar4 + iVar6) - uVar5;
    if ((int)(uVar5 + param_2) <= (int)uVar4) {
      iVar14 = iVar6;
    }
    uVar12 = 0;
    if ((int)(uVar5 + param_2) <= (int)uVar4) {
      uVar12 = uVar5;
    }
    if (iVar14 < (int)uVar4) {
      if (param_2 == 0) {
code_r0x021bd9c4:
        uVar5 = 0;
        if (uVar4 != 0) {
          uVar5 = (uVar12 + param_2) / uVar4;
        }
        *(uint *)(param_1 + 0x38) = (uVar12 + param_2) - uVar5 * uVar4;
        *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + param_2;
        return *(long *)(param_1 + 0x30) + (long)(int)uVar12 * 0x10;
      }
      lVar13 = *(long *)(param_1 + 0x18);
      do {
        uVar5 = uVar12 + 0x3f;
        if (-1 < (int)uVar12) {
          uVar5 = uVar12;
        }
        uVar7 = (int)uVar12 % 0x40;
        puVar9 = (ulong *)(lVar13 + (long)((int)uVar5 >> 6) * 8);
        iVar10 = param_2;
        uVar1 = uVar7;
        while( true ) {
          uVar11 = 0xffffffffffffffff >> ((ulong)(0x40 - iVar10) & 0x3f);
          if (0x3f < iVar10) {
            uVar11 = 0xffffffffffffffff;
          }
          iVar2 = 0;
          if (iVar10 < 0x40) {
            iVar2 = iVar10;
          }
          if ((uVar11 << ((ulong)uVar1 & 0x3f) & *puVar9) != 0) break;
          iVar3 = 0x40 - uVar1;
          if (iVar2 <= (int)(0x40 - uVar1)) {
            iVar3 = iVar2;
          }
          iVar10 = iVar10 - iVar3;
          puVar9 = puVar9 + 1;
          uVar1 = 0;
          if (iVar10 == 0) {
            uVar11 = 0xffffffffffffffff >> ((ulong)(0x40 - param_2) & 0x3f);
            lVar15 = ((long)((ulong)uVar5 << 0x20) >> 0x26) * 8;
            if (0x3f < param_2) {
              uVar11 = 0xffffffffffffffff;
            }
            iVar14 = 0;
            if (param_2 < 0x40) {
              iVar14 = param_2;
            }
            iVar6 = 0x40 - uVar7;
            if (iVar14 <= (int)(0x40 - uVar7)) {
              iVar6 = iVar14;
            }
            *(ulong *)(lVar13 + lVar15) =
                 *(ulong *)(lVar13 + lVar15) | uVar11 << ((ulong)uVar7 & 0x3f);
            for (iVar6 = param_2 - iVar6; iVar6 != 0; iVar6 = iVar6 - iVar14) {
              lVar15 = lVar15 + 8;
              uVar11 = 0xffffffffffffffff >> ((ulong)(0x40 - iVar6) & 0x3f);
              iVar14 = iVar6;
              if (0x3f < iVar6) {
                uVar11 = 0xffffffffffffffff;
                iVar14 = 0x40;
              }
              if (0x3f < iVar14) {
                iVar14 = 0x40;
              }
              *(ulong *)(*(long *)(param_1 + 0x18) + lVar15) =
                   uVar11 | *(ulong *)(*(long *)(param_1 + 0x18) + lVar15);
            }
            goto code_r0x021bd9c4;
          }
        }
        iVar10 = 0;
        do {
          uVar5 = uVar12 + iVar6 + iVar10;
          iVar10 = iVar10 + -1;
        } while ((1L << (uVar5 & 0x3f) & *(ulong *)(lVar13 + (ulong)(uVar5 >> 6) * 8)) == 0);
        iVar2 = (param_2 << 1 | 1U) + uVar12;
        iVar3 = param_2 + 1 + uVar12;
        iVar8 = (((uVar4 - 1) - param_2) - uVar12) - iVar10;
        uVar12 = 0;
        if (iVar2 + iVar10 <= (int)uVar4) {
          iVar8 = 0;
          uVar12 = iVar3 + iVar10;
        }
        iVar14 = iVar8 + param_2 + 1 + iVar14 + iVar10;
        if ((int)uVar4 <= iVar14) {
          return 0;
        }
      } while( true );
    }
  }
  return 0;
}

// ==== Aska::TPoolHandler<Aska::TAddressSet<Aska::AsfHandler> >::CreateNode()
// vaddr 0x20df790 | ghidra 0x21df790 | size 232 | symbol _ZN4Aska12TPoolHandlerINS_11TAddressSetINS_10AsfHandlerEEEE10CreateNodeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12TPoolHandlerINS_11TAddressSetINS_10AsfHandlerEEEE10CreateNodeEv(long param_1)

{
  ulong uVar1;
  uint uVar2;
  undefined *puVar3;
  uint uVar4;
  long *plVar5;
  long lVar6;
  long lVar7;
  uint uVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  
  lVar6 = *(long *)(param_1 + 8);
  if (lVar6 != 0) {
    if (*(uint *)(lVar6 + 0x3c) < *(uint *)(lVar6 + 0x2c)) {
      lVar7 = *(long *)(lVar6 + 0x20);
      uVar4 = *(uint *)(lVar6 + 0x38);
      do {
        uVar8 = uVar4;
        if (*(uint *)(lVar6 + 0x2c) <= uVar8) {
          uVar8 = 0;
        }
        uVar2 = 1 << (ulong)(uVar8 & 0x1f);
        uVar4 = uVar8 + 1;
      } while ((uVar2 & *(uint *)(lVar7 + (ulong)(uVar8 >> 5) * 4)) != 0);
      uVar1 = *(long *)(lVar6 + 0x40) + (ulong)uVar8 * 0x20;
      uVar10 = uVar1;
      do {
        uVar11 = uVar10 + 0x7f & 0xffffffffffffff81;
        Hint_Prefetch(uVar10,0,2,0);
        uVar10 = uVar11;
      } while (uVar11 < uVar1 + 0x20);
      lVar9 = (ulong)(uVar8 >> 5) * 4;
      *(uint *)(lVar6 + 0x38) = uVar8 + 1;
      *(uint *)(lVar6 + 0x3c) = *(uint *)(lVar6 + 0x3c) + 1;
      *(uint *)(lVar7 + lVar9) = *(uint *)(lVar7 + lVar9) | uVar2;
      lVar7 = (ulong)uVar8 * 0x20;
      plVar5 = (long *)(*(long *)(lVar6 + 0x40) + lVar7);
      *plVar5 = (long)(PTR__ZTVN4Aska11TAddressSetINS_10AsfHandlerEEE_02cb7948 + 0x10);
      plVar5[1] = 0;
      plVar5[2] = 0;
      plVar5[3] = 0;
      if (*(long *)(lVar6 + 0x40) + lVar7 != 0) {
        return;
      }
    }
  }
  plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80);
  puVar3 = PTR__ZTVN4Aska11TAddressSetINS_10AsfHandlerEEE_02cb7948;
  if (plVar5 != (long *)0x0) {
    plVar5[2] = 0;
    plVar5[3] = 0;
    *plVar5 = (long)(puVar3 + 0x10);
    plVar5[1] = 0;
  }
  return;
}

// ==== Aska::TPoolHandler<Aska::TAddressSet<Aska::AsfHandler> >::DeleteNode(Aska::TAddressSet<Aska::AsfHandler>**)
// vaddr 0x20df914 | ghidra 0x21df914 | size 164 | symbol _ZN4Aska12TPoolHandlerINS_11TAddressSetINS_10AsfHandlerEEEE10DeleteNodeEPPS3_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12TPoolHandlerINS_11TAddressSetINS_10AsfHandlerEEEE10DeleteNodeEPPS3_
               (long param_1,ulong *param_2)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  
  lVar4 = *(long *)(param_1 + 8);
  plVar1 = (long *)*param_2;
  if ((((lVar4 == 0) || (plVar2 = *(long **)(lVar4 + 0x40), plVar2 == (long *)0x0)) ||
      (plVar1 < plVar2)) || (plVar2 + (ulong)*(uint *)(lVar4 + 0x2c) * 4 <= plVar1)) {
    if (plVar1 == (long *)0x0) {
      return;
    }
    (**(code **)(*plVar1 + 8))();
  }
  else {
    uVar5 = (long)plVar1 - (long)plVar2;
    (**(code **)plVar2[(uVar5 >> 5 & 0xffffffff) * 4])();
    lVar3 = (uVar5 >> 10 & 0x7ffffff) * 4;
    *(uint *)(*(long *)(lVar4 + 0x20) + lVar3) =
         *(uint *)(*(long *)(lVar4 + 0x20) + lVar3) & (1 << (uVar5 >> 5 & 0x1f) ^ 0xffffffffU);
    *(int *)(lVar4 + 0x3c) = *(int *)(lVar4 + 0x3c) + -1;
  }
  *param_2 = 0;
  return;
}

// ==== Aska::TPoolHandler<Aska::TAddressSet<Aska::AsfHandler> >::AttachPool(Aska::TPoolLegacy<Aska::TAddressSet<Aska::AsfHandler>, false>*)
// vaddr 0x20dfa78 | ghidra 0x21dfa78 | size 60 | symbol _ZN4Aska12TPoolHandlerINS_11TAddressSetINS_10AsfHandlerEEEE10AttachPoolEPNS_11TPoolLegacyIS3_Lb0EEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12TPoolHandlerINS_11TAddressSetINS_10AsfHandlerEEEE10AttachPoolEPNS_11TPoolLegacyIS3_Lb0EEE
               (long *param_1,long param_2)

{
  (**(code **)(*param_1 + 0x38))();
  if (param_2 != 0) {
    *(int *)(param_2 + 8) = *(int *)(param_2 + 8) + 1;
    param_1[1] = param_2;
  }
  return;
}

// ==== Aska::TPoolHandler<Aska::TAddressSet<Aska::AsfHandler> >::DetachPool()
// vaddr 0x20dfab4 | ghidra 0x21dfab4 | size 56 | symbol _ZN4Aska12TPoolHandlerINS_11TAddressSetINS_10AsfHandlerEEEE10DetachPoolEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12TPoolHandlerINS_11TAddressSetINS_10AsfHandlerEEEE10DetachPoolEv(long param_1)

{
  int iVar1;
  long *plVar2;
  
  plVar2 = *(long **)(param_1 + 8);
  if (plVar2 != (long *)0x0) {
    iVar1 = (int)plVar2[1] + -1;
    *(int *)(plVar2 + 1) = iVar1;
    if (iVar1 == 0) {
      (**(code **)(*plVar2 + 8))();
    }
    *(undefined8 *)(param_1 + 8) = 0;
  }
  return;
}

// ==== Aska::TPoolLegacy<Aska::AsfNode, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x20e07d8 | ghidra 0x21e07d8 | size 500 | symbol _ZN4Aska11TPoolLegacyINS_7AsfNodeELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_7AsfNodeELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x50,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x021e0990;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x021e0930;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x021e0990:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x021e0930:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x50);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TAddressManager<Aska::AsfHandler::IAnimatableSet>::CalcHashValue(void const*) const
// vaddr 0x20e1500 | ghidra 0x21e1500 | size 132 | symbol _ZNK4Aska15TAddressManagerINS_10AsfHandler14IAnimatableSetEE13CalcHashValueEPKv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK4Aska15TAddressManagerINS_10AsfHandler14IAnimatableSetEE13CalcHashValueEPKv
              (long param_1,byte *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = *(uint *)(param_1 + 0x58);
  uVar2 = 0;
  if (uVar1 != 0) {
    uVar2 = *param_2 / uVar1;
  }
  uVar2 = (uint)param_2[1] + ((uint)*param_2 - uVar2 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[2] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[3] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[4] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[5] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[6] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[7] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  return uVar2 - uVar3 * uVar1;
}

// ==== Aska::TPoolLegacy<Aska::AsfHandler::IAnimatableSet, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x20e1d9c | ghidra 0x21e1d9c | size 492 | symbol _ZN4Aska11TPoolLegacyINS_10AsfHandler14IAnimatableSetELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_10AsfHandler14IAnimatableSetELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 << 6,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x021e1f4c;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x021e1ef0;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x021e1f4c:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x021e1ef0:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 << 6);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::TAddressSet<Aska::AsfHandler>, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x20e7700 | ghidra 0x21e7700 | size 492 | symbol _ZN4Aska11TPoolLegacyINS_11TAddressSetINS_10AsfHandlerEEELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_11TAddressSetINS_10AsfHandlerEEELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 << 5,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x021e78b0;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x021e7854;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x021e78b0:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x021e7854:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 << 5);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::DecodeTextureQueue::TextureMemoryEx, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x20f9b64 | ghidra 0x21f9b64 | size 500 | symbol _ZN4Aska11TPoolLegacyINS_18DecodeTextureQueue15TextureMemoryExELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_18DecodeTextureQueue15TextureMemoryExELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x50,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x021f9d1c;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x021f9cbc;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x021f9d1c:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x021f9cbc:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x50);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::DecodeTextureQueue::DecodeTextureIdIterator, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x20fae5c | ghidra 0x21fae5c | size 492 | symbol _ZN4Aska11TPoolLegacyINS_18DecodeTextureQueue23DecodeTextureIdIteratorELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_18DecodeTextureQueue23DecodeTextureIdIteratorELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 << 6,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x021fb00c;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x021fafb0;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x021fb00c:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x021fafb0:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 << 6);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::DecodeTextureQueue::TextureDecoderIterator, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x20fc960 | ghidra 0x21fc960 | size 500 | symbol _ZN4Aska11TPoolLegacyINS_18DecodeTextureQueue22TextureDecoderIteratorELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_18DecodeTextureQueue22TextureDecoderIteratorELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x58,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x021fcb18;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x021fcab8;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x021fcb18:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x021fcab8:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x58);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::DecodeTextureQueue::TextureMemoryIterator, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x20fe55c | ghidra 0x21fe55c | size 500 | symbol _ZN4Aska11TPoolLegacyINS_18DecodeTextureQueue21TextureMemoryIteratorELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_18DecodeTextureQueue21TextureMemoryIteratorELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x58,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x021fe714;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x021fe6b4;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x021fe714:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x021fe6b4:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x58);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::LIBLManager::_AarLoaderElem, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x2136880 | ghidra 0x2236880 | size 328 | symbol _ZN4Aska11TPoolLegacyINS_11LIBLManager14_AarLoaderElemELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_11LIBLManager14_AarLoaderElemELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)(param_1 + 0x20);
  if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar5 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
code_r0x0223696c:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x268,8,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x02236924;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x02236924:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x268);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x0223696c;
      }
      lVar4 = *(long *)(param_1 + 0x40);
    }
    if (lVar4 != 0) {
      if (*(char *)(param_1 + 0x48) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    *(char *)(param_1 + 0x48) = '\0';
    if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar3 = 0;
    *plVar5 = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return uVar3;
}

// ==== Aska::TPoolFast<Aska::IndexBuffer, true>::SecurePool(unsigned int, Aska::IndexBuffer*)
// vaddr 0x214c4f0 | ghidra 0x224c4f0 | size 644 | symbol _ZN4Aska9TPoolFastINS_11IndexBufferELb1EE10SecurePoolEjPS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9TPoolFastINS_11IndexBufferELb1EE10SecurePoolEjPS1_(long param_1,uint param_2,long param_3)

{
  uint uVar1;
  ulong *puVar2;
  undefined8 uVar3;
  long lVar4;
  uint uVar5;
  ulong *puVar6;
  ulong uVar7;
  uint *puVar8;
  long lVar9;
  long *plVar10;
  
  if (*(char *)(param_1 + 0xd0) == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    lVar9 = *(long *)(param_1 + 0x30);
    if (lVar9 != 0) {
      lVar4 = *(long *)(lVar9 + -8);
      if (lVar4 != 0) {
        lVar4 = lVar4 * 0x58;
        do {
          Aska::IndexBuffer::Release()(lVar9 + lVar4 + -0x58);
          lVar4 = lVar4 + -0x58;
        } while (lVar4 != 0);
      }
      operator delete[](void*)((long *)(lVar9 + -8));
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    *(undefined1 *)(param_1 + 0xd0) = 0;
  }
  plVar10 = (long *)(param_1 + 0x18);
  if ((*plVar10 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *plVar10 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  if (param_2 == 0) {
    return 1;
  }
  if (param_3 == 0) {
    puVar2 = (ulong *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 * 0x58 + 8,PTR__ZSt7nothrow_02cb9a80);
    if (puVar2 != (ulong *)0x0) {
      puVar6 = puVar2 + 1;
      *puVar2 = (ulong)param_2;
      puVar2 = puVar6;
      do {
        memset(puVar2,0,0x41);
        *(undefined4 *)(puVar2 + 10) = 0;
        puVar2[9] = 0;
        puVar2 = puVar2 + 0xb;
      } while (puVar2 != puVar6 + (ulong)param_2 * 0xb);
      *(ulong **)(param_1 + 0x30) = puVar6;
      *(undefined1 *)(param_1 + 0xd0) = 1;
      goto code_r0x0224c5f4;
    }
    *(undefined8 *)(param_1 + 0x30) = 0;
    if (*(char *)(param_1 + 0xd0) != '\0') goto code_r0x0224c6cc;
code_r0x0224c728:
    *(undefined8 *)(param_1 + 0x30) = 0;
code_r0x0224c748:
    uVar3 = 0;
    *plVar10 = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  else {
    *(long *)(param_1 + 0x30) = param_3;
code_r0x0224c5f4:
    uVar7 = (ulong)param_2 + 0x3f >> 6;
    uVar5 = (uint)uVar7;
    if ((*(char *)(param_1 + 0x28) == '\0') || (uVar1 = *(uint *)(param_1 + 0x20), uVar1 < uVar5)) {
      if ((*plVar10 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
        operator delete[](void*)();
        *(undefined1 *)(param_1 + 0x28) = 0;
      }
      puVar8 = (uint *)(param_1 + 0x20);
      *puVar8 = uVar5;
      *(uint *)(param_1 + 0x24) = param_2;
      lVar4 = uVar7 << 3;
      lVar9 = operator new[](unsigned long, std::nothrow_t const&)(lVar4,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x18) = lVar9;
      *(undefined1 *)(param_1 + 0x28) = 1;
      if (lVar9 == 0) {
        *(undefined1 *)(param_1 + 0x28) = 0;
        puVar8[0] = 0;
        puVar8[1] = 0;
        if (*(char *)(param_1 + 0xd0) == '\0') goto code_r0x0224c728;
code_r0x0224c6cc:
        lVar9 = *(long *)(param_1 + 0x30);
        if (lVar9 == 0) {
          *(undefined1 *)(param_1 + 0xd0) = 0;
        }
        else {
          lVar4 = *(long *)(lVar9 + -8);
          if (lVar4 != 0) {
            lVar4 = lVar4 * 0x58;
            do {
              Aska::IndexBuffer::Release()(lVar9 + lVar4 + -0x58);
              lVar4 = lVar4 + -0x58;
            } while (lVar4 != 0);
          }
          operator delete[](void*)((long *)(lVar9 + -8));
          *(undefined8 *)(param_1 + 0x30) = 0;
          *(undefined1 *)(param_1 + 0xd0) = 0;
          if ((*(long *)(param_1 + 0x18) != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
            operator delete[](void*)(*(long *)(param_1 + 0x18));
            *(undefined1 *)(param_1 + 0x28) = 0;
          }
        }
        goto code_r0x0224c748;
      }
      if (uVar5 == 0) goto code_r0x0224c6b0;
      memset(lVar9,0,lVar4);
      *(undefined8 *)(param_1 + 0x38) = 0;
    }
    else {
      *(uint *)(param_1 + 0x24) = param_2;
      if (uVar1 == 0) {
code_r0x0224c6b0:
        *(undefined8 *)(param_1 + 0x38) = 0;
        return 1;
      }
      memset(*(undefined8 *)(param_1 + 0x18),0,uVar1 << 3);
      uVar5 = *(uint *)(param_1 + 0x20);
      *(undefined8 *)(param_1 + 0x38) = 0;
      if (uVar5 == 0) {
        return 1;
      }
    }
    memset(*plVar10,0,uVar5 << 3);
    uVar3 = 1;
  }
  return uVar3;
}

// ==== Aska::TPoolFast<Aska::VertexBuffer, true>::SecurePool(unsigned int, Aska::VertexBuffer*)
// vaddr 0x214c774 | ghidra 0x224c774 | size 664 | symbol _ZN4Aska9TPoolFastINS_12VertexBufferELb1EE10SecurePoolEjPS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9TPoolFastINS_12VertexBufferELb1EE10SecurePoolEjPS1_(long param_1,uint param_2,long param_3)

{
  uint uVar1;
  ulong *puVar2;
  undefined8 uVar3;
  long lVar4;
  uint uVar5;
  ulong *puVar6;
  ulong uVar7;
  long *plVar8;
  long lVar9;
  uint *puVar10;
  
  if (*(char *)(param_1 + 0xd0) == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    lVar9 = *(long *)(param_1 + 0x30);
    if (lVar9 != 0) {
      lVar4 = *(long *)(lVar9 + -8);
      if (lVar4 != 0) {
        lVar4 = lVar4 * 0x68;
        do {
          Aska::VertexBuffer::~VertexBuffer()(lVar9 + lVar4 + -0x68);
          lVar4 = lVar4 + -0x68;
        } while (lVar4 != 0);
      }
      operator delete[](void*)((long *)(lVar9 + -8));
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    *(undefined1 *)(param_1 + 0xd0) = 0;
  }
  plVar8 = (long *)(param_1 + 0x18);
  if ((*plVar8 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *plVar8 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  if (param_2 == 0) {
    return 1;
  }
  if (param_3 == 0) {
    puVar2 = (ulong *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 * 0x68 + 8,PTR__ZSt7nothrow_02cb9a80);
    if (puVar2 != (ulong *)0x0) {
      puVar6 = puVar2 + 1;
      *puVar2 = (ulong)param_2;
      puVar2 = puVar6;
      do {
        *(undefined4 *)puVar2 = 0xffffffff;
        memset(puVar2 + 1,0,0x41);
        *(undefined8 *)((long)puVar2 + 0x5d) = 0;
        puVar2[10] = 0;
        puVar2[0xb] = 0;
        puVar2 = puVar2 + 0xd;
      } while (puVar2 != puVar6 + (ulong)param_2 * 0xd);
      *(ulong **)(param_1 + 0x30) = puVar6;
      *(undefined1 *)(param_1 + 0xd0) = 1;
      goto code_r0x0224c888;
    }
    *(undefined8 *)(param_1 + 0x30) = 0;
    if (*(char *)(param_1 + 0xd0) != '\0') goto code_r0x0224c960;
code_r0x0224c9bc:
    *(undefined8 *)(param_1 + 0x30) = 0;
code_r0x0224c9dc:
    uVar3 = 0;
    *plVar8 = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  else {
    *(long *)(param_1 + 0x30) = param_3;
code_r0x0224c888:
    uVar7 = (ulong)param_2 + 0x3f >> 6;
    uVar5 = (uint)uVar7;
    if ((*(char *)(param_1 + 0x28) == '\0') || (uVar1 = *(uint *)(param_1 + 0x20), uVar1 < uVar5)) {
      if ((*plVar8 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
        operator delete[](void*)();
        *(undefined1 *)(param_1 + 0x28) = 0;
      }
      puVar10 = (uint *)(param_1 + 0x20);
      *puVar10 = uVar5;
      *(uint *)(param_1 + 0x24) = param_2;
      lVar4 = uVar7 << 3;
      lVar9 = operator new[](unsigned long, std::nothrow_t const&)(lVar4,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x18) = lVar9;
      *(undefined1 *)(param_1 + 0x28) = 1;
      if (lVar9 == 0) {
        *(undefined1 *)(param_1 + 0x28) = 0;
        puVar10[0] = 0;
        puVar10[1] = 0;
        if (*(char *)(param_1 + 0xd0) == '\0') goto code_r0x0224c9bc;
code_r0x0224c960:
        lVar9 = *(long *)(param_1 + 0x30);
        if (lVar9 == 0) {
          *(undefined1 *)(param_1 + 0xd0) = 0;
        }
        else {
          lVar4 = *(long *)(lVar9 + -8);
          if (lVar4 != 0) {
            lVar4 = lVar4 * 0x68;
            do {
              Aska::VertexBuffer::~VertexBuffer()(lVar9 + lVar4 + -0x68);
              lVar4 = lVar4 + -0x68;
            } while (lVar4 != 0);
          }
          operator delete[](void*)((long *)(lVar9 + -8));
          *(undefined8 *)(param_1 + 0x30) = 0;
          *(undefined1 *)(param_1 + 0xd0) = 0;
          if ((*(long *)(param_1 + 0x18) != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
            operator delete[](void*)(*(long *)(param_1 + 0x18));
            *(undefined1 *)(param_1 + 0x28) = 0;
          }
        }
        goto code_r0x0224c9dc;
      }
      if (uVar5 == 0) goto code_r0x0224c944;
      memset(lVar9,0,lVar4);
      *(undefined8 *)(param_1 + 0x38) = 0;
    }
    else {
      *(uint *)(param_1 + 0x24) = param_2;
      if (uVar1 == 0) {
code_r0x0224c944:
        *(undefined8 *)(param_1 + 0x38) = 0;
        return 1;
      }
      memset(*(undefined8 *)(param_1 + 0x18),0,uVar1 << 3);
      uVar5 = *(uint *)(param_1 + 0x20);
      *(undefined8 *)(param_1 + 0x38) = 0;
      if (uVar5 == 0) {
        return 1;
      }
    }
    memset(*plVar8,0,uVar5 << 3);
    uVar3 = 1;
  }
  return uVar3;
}

// ==== Aska::TPoolFast<unsigned char [90], true>::SecurePool(unsigned int, unsigned char (*) [90])
// vaddr 0x2169534 | ghidra 0x2269534 | size 408 | symbol _ZN4Aska9TPoolFastIA90_hLb1EE10SecurePoolEjPS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska9TPoolFastIA90_hLb1EE10SecurePoolEjPS1_(long param_1,uint param_2,long param_3)

{
  bool bVar1;
  char cVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  long *plVar6;
  
  if (*(char *)(param_1 + 0xd0) == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (*(long *)(param_1 + 0x30) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    *(undefined1 *)(param_1 + 0xd0) = 0;
  }
  plVar6 = (long *)(param_1 + 0x18);
  if ((*plVar6 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *plVar6 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  if (param_2 == 0) {
    return 1;
  }
  if (param_3 == 0) {
    param_3 = operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 * 0x5a,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 0x30) = param_3;
    if (param_3 == 0) {
      cVar2 = *(char *)(param_1 + 0xd0);
      goto joined_r0x02269690;
    }
    *(undefined1 *)(param_1 + 0xd0) = 1;
  }
  else {
    *(long *)(param_1 + 0x30) = param_3;
  }
  uVar4 = (ulong)param_2 + 0x3f >> 6;
  *(int *)(param_1 + 0x20) = (int)uVar4;
  *(uint *)(param_1 + 0x24) = param_2;
  lVar5 = uVar4 << 3;
  lVar3 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
  *(long *)(param_1 + 0x18) = lVar3;
  *(undefined1 *)(param_1 + 0x28) = 1;
  if (lVar3 != 0) {
    memset(lVar3,0,lVar5);
    *(undefined8 *)(param_1 + 0x38) = 0;
    memset(lVar3,0,lVar5);
    return 1;
  }
  *(undefined1 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  cVar2 = *(char *)(param_1 + 0xd0);
joined_r0x02269690:
  if (cVar2 == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (param_3 == 0) {
      lVar3 = 0;
      *(undefined1 *)(param_1 + 0xd0) = 0;
      bVar1 = false;
    }
    else {
      operator delete[](void*)(param_3);
      lVar3 = *(long *)(param_1 + 0x18);
      *(undefined8 *)(param_1 + 0x30) = 0;
      *(undefined1 *)(param_1 + 0xd0) = 0;
      bVar1 = lVar3 != 0;
    }
    if ((bVar1) && (*(char *)(param_1 + 0x28) != '\0')) {
      operator delete[](void*)(lVar3);
      *(undefined1 *)(param_1 + 0x28) = 0;
    }
  }
  *plVar6 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  return 0;
}

// ==== Aska::TPoolFast<Aska::IndexBuffer, true>::Sink(Aska::IndexBuffer*)
// vaddr 0x2173570 | ghidra 0x2273570 | size 412 | symbol _ZN4Aska9TPoolFastINS_11IndexBufferELb1EE4SinkEPS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska9TPoolFastINS_11IndexBufferELb1EE4SinkEPS1_(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  ulong uVar6;
  long lVar7;
  
  piVar1 = (int *)(param_1 + 0x78);
  iVar5 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar5;
      iVar5 = iVar5 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_1 + 0x7c);
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
              uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xb8);
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
                Aska::Semaphore::Wait() const(param_1 + 0xb8);
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
                if (cVar3 == '\0') goto code_r0x022736f4;
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
code_r0x022736f4:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x022735e8:
        uVar6 = (param_2 - *(long *)(param_1 + 0x30) >> 3) * 0x2e8ba2e8ba2e8ba3;
        lVar7 = (uVar6 >> 6 & 0x3ffffff) * 8;
        *(ulong *)(*(long *)(param_1 + 0x18) + lVar7) =
             *(ulong *)(*(long *)(param_1 + 0x18) + lVar7) &
             (1L << (uVar6 & 0x3f) ^ 0xffffffffffffffffU);
        *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + -1;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x78) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_1 + 0x7c);
        if (0x14 < *piVar1) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xb8);
          if ((uVar6 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0xb8);
          }
        }
        return 1;
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
  goto code_r0x022735e8;
}

// ==== Aska::TPoolFast<Aska::VertexBuffer, true>::Sink(Aska::VertexBuffer*)
// vaddr 0x217370c | ghidra 0x227370c | size 412 | symbol _ZN4Aska9TPoolFastINS_12VertexBufferELb1EE4SinkEPS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska9TPoolFastINS_12VertexBufferELb1EE4SinkEPS1_(long param_1,long param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  ulong uVar6;
  long lVar7;
  
  piVar1 = (int *)(param_1 + 0x78);
  iVar5 = 0;
  do {
    while (*piVar1 != -1) {
      ClearExclusiveLocal();
      bVar4 = 0x1fe < iVar5;
      iVar5 = iVar5 + 1;
      if (bVar4) {
        piVar2 = (int *)(param_1 + 0x7c);
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
              uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xb8);
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
                Aska::Semaphore::Wait() const(param_1 + 0xb8);
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
                if (cVar3 == '\0') goto code_r0x02273890;
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
code_r0x02273890:
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar4) {
            *piVar2 = *piVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        DataMemoryBarrier(2,3);
code_r0x02273784:
        uVar6 = (param_2 - *(long *)(param_1 + 0x30) >> 3) * 0x4ec4ec4ec4ec4ec5;
        lVar7 = (uVar6 >> 6 & 0x3ffffff) * 8;
        *(ulong *)(*(long *)(param_1 + 0x18) + lVar7) =
             *(ulong *)(*(long *)(param_1 + 0x18) + lVar7) &
             (1L << (uVar6 & 0x3f) ^ 0xffffffffffffffffU);
        *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + -1;
        DataMemoryBarrier(2,3);
        *(undefined4 *)(param_1 + 0x78) = 0xffffffff;
        DataMemoryBarrier(2,3);
        piVar1 = (int *)(param_1 + 0x7c);
        if (0x14 < *piVar1) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          uVar6 = Aska::Semaphore::IsReady() const(param_1 + 0xb8);
          if ((uVar6 & 1) != 0) {
            Aska::Semaphore::Signal() const(param_1 + 0xb8);
          }
        }
        return 1;
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
  goto code_r0x02273784;
}

// ==== Aska::TPoolFast<Aska::VertexBuffer, true>::Scoop()
// vaddr 0x21738a8 | ghidra 0x22738a8 | size 472 | symbol _ZN4Aska9TPoolFastINS_12VertexBufferELb1EE5ScoopEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska9TPoolFastINS_12VertexBufferELb1EE5ScoopEv(long param_1)

{
  ulong *puVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  ulong uVar13;
  long lVar14;
  
  piVar9 = (int *)(param_1 + 0x78);
  iVar8 = 0;
code_r0x022738c0:
  do {
    if (*piVar9 != -1) {
      ClearExclusiveLocal();
      bVar6 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
      if (bVar6) goto code_r0x022738c0;
      piVar2 = (int *)(param_1 + 0x7c);
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar6) {
          *piVar2 = *piVar2 + 1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
      do {
        if (*piVar9 != -1) {
          ClearExclusiveLocal();
          do {
            uVar10 = Aska::Semaphore::IsReady() const(param_1 + 0xb8);
            if ((uVar10 & 1) == 0) {
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
              Aska::Semaphore::Wait() const(param_1 + 0xb8);
            }
            do {
              cVar5 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar6) {
                *piVar2 = *piVar2 + 1;
                cVar5 = ExclusiveMonitorsStatus();
              }
            } while (cVar5 != '\0');
            while (*piVar9 == -1) {
              cVar5 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(piVar9,0x10);
              if (bVar6) {
                *piVar9 = 0;
                cVar5 = ExclusiveMonitorsStatus();
              }
              if (cVar5 == '\0') goto code_r0x02273978;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar6) {
          *piVar9 = 0;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
code_r0x02273978:
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar6) {
          *piVar2 = *piVar2 + -1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
code_r0x02273988:
      DataMemoryBarrier(2,3);
      uVar3 = *(uint *)(param_1 + 0x24);
      if (*(uint *)(param_1 + 0x3c) < uVar3) {
        uVar4 = *(uint *)(param_1 + 0x38);
        uVar10 = (ulong)uVar4;
        *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
        puVar1 = (ulong *)(*(long *)(param_1 + 0x18) + (ulong)(uVar4 >> 6) * 8);
        uVar11 = *puVar1;
        uVar12 = 1L << (uVar10 & 0x3f);
        uVar13 = uVar12 & uVar11;
        while (uVar13 != 0) {
          uVar4 = (int)uVar10 + 1;
          uVar7 = 0;
          if (uVar3 != 0) {
            uVar7 = uVar4 / uVar3;
          }
          uVar4 = uVar4 - uVar7 * uVar3;
          uVar10 = (ulong)uVar4;
          puVar1 = (ulong *)(*(long *)(param_1 + 0x18) + (ulong)(uVar4 >> 6) * 8);
          uVar11 = *puVar1;
          uVar12 = 1L << (uVar4 & 0x3f);
          uVar13 = uVar12 & uVar11;
        }
        *puVar1 = uVar12 | uVar11;
        uVar7 = 0;
        if (uVar3 != 0) {
          uVar7 = (uVar4 + 1) / uVar3;
        }
        *(uint *)(param_1 + 0x38) = (uVar4 + 1) - uVar7 * uVar3;
        lVar14 = *(long *)(param_1 + 0x30) + (ulong)uVar4 * 0x68;
      }
      else {
        lVar14 = 0;
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x78) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar9 = (int *)(param_1 + 0x7c);
      if (0x14 < *piVar9) {
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar9,0x10);
          if (bVar6) {
            *piVar9 = *piVar9 + -1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        uVar10 = Aska::Semaphore::IsReady() const(param_1 + 0xb8);
        if ((uVar10 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0xb8);
        }
      }
      return lVar14;
    }
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar6) {
      *piVar9 = 0;
      cVar5 = ExclusiveMonitorsStatus();
    }
    if (cVar5 == '\0') goto code_r0x02273988;
  } while( true );
}

// ==== Aska::TPoolFast<Aska::IndexBuffer, true>::Scoop()
// vaddr 0x2173a80 | ghidra 0x2273a80 | size 472 | symbol _ZN4Aska9TPoolFastINS_11IndexBufferELb1EE5ScoopEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska9TPoolFastINS_11IndexBufferELb1EE5ScoopEv(long param_1)

{
  ulong *puVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  ulong uVar13;
  long lVar14;
  
  piVar9 = (int *)(param_1 + 0x78);
  iVar8 = 0;
code_r0x02273a98:
  do {
    if (*piVar9 != -1) {
      ClearExclusiveLocal();
      bVar6 = iVar8 < 0x1ff;
      iVar8 = iVar8 + 1;
      if (bVar6) goto code_r0x02273a98;
      piVar2 = (int *)(param_1 + 0x7c);
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar6) {
          *piVar2 = *piVar2 + 1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
      do {
        if (*piVar9 != -1) {
          ClearExclusiveLocal();
          do {
            uVar10 = Aska::Semaphore::IsReady() const(param_1 + 0xb8);
            if ((uVar10 & 1) == 0) {
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
              Aska::Semaphore::Wait() const(param_1 + 0xb8);
            }
            do {
              cVar5 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
              if (bVar6) {
                *piVar2 = *piVar2 + 1;
                cVar5 = ExclusiveMonitorsStatus();
              }
            } while (cVar5 != '\0');
            while (*piVar9 == -1) {
              cVar5 = '\x01';
              bVar6 = (bool)ExclusiveMonitorPass(piVar9,0x10);
              if (bVar6) {
                *piVar9 = 0;
                cVar5 = ExclusiveMonitorsStatus();
              }
              if (cVar5 == '\0') goto code_r0x02273b50;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar9,0x10);
        if (bVar6) {
          *piVar9 = 0;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
code_r0x02273b50:
      do {
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar2,0x10);
        if (bVar6) {
          *piVar2 = *piVar2 + -1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
code_r0x02273b60:
      DataMemoryBarrier(2,3);
      uVar3 = *(uint *)(param_1 + 0x24);
      if (*(uint *)(param_1 + 0x3c) < uVar3) {
        uVar4 = *(uint *)(param_1 + 0x38);
        uVar10 = (ulong)uVar4;
        *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
        puVar1 = (ulong *)(*(long *)(param_1 + 0x18) + (ulong)(uVar4 >> 6) * 8);
        uVar11 = *puVar1;
        uVar12 = 1L << (uVar10 & 0x3f);
        uVar13 = uVar12 & uVar11;
        while (uVar13 != 0) {
          uVar4 = (int)uVar10 + 1;
          uVar7 = 0;
          if (uVar3 != 0) {
            uVar7 = uVar4 / uVar3;
          }
          uVar4 = uVar4 - uVar7 * uVar3;
          uVar10 = (ulong)uVar4;
          puVar1 = (ulong *)(*(long *)(param_1 + 0x18) + (ulong)(uVar4 >> 6) * 8);
          uVar11 = *puVar1;
          uVar12 = 1L << (uVar4 & 0x3f);
          uVar13 = uVar12 & uVar11;
        }
        *puVar1 = uVar12 | uVar11;
        uVar7 = 0;
        if (uVar3 != 0) {
          uVar7 = (uVar4 + 1) / uVar3;
        }
        *(uint *)(param_1 + 0x38) = (uVar4 + 1) - uVar7 * uVar3;
        lVar14 = *(long *)(param_1 + 0x30) + (ulong)uVar4 * 0x58;
      }
      else {
        lVar14 = 0;
      }
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_1 + 0x78) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar9 = (int *)(param_1 + 0x7c);
      if (0x14 < *piVar9) {
        do {
          cVar5 = '\x01';
          bVar6 = (bool)ExclusiveMonitorPass(piVar9,0x10);
          if (bVar6) {
            *piVar9 = *piVar9 + -1;
            cVar5 = ExclusiveMonitorsStatus();
          }
        } while (cVar5 != '\0');
        uVar10 = Aska::Semaphore::IsReady() const(param_1 + 0xb8);
        if ((uVar10 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_1 + 0xb8);
        }
      }
      return lVar14;
    }
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar9,0x10);
    if (bVar6) {
      *piVar9 = 0;
      cVar5 = ExclusiveMonitorsStatus();
    }
    if (cVar5 == '\0') goto code_r0x02273b60;
  } while( true );
}

// ==== Aska::TPoolFast<Aska::RenderManagerBase::TempSurface, false>::SecurePool(unsigned int, Aska::RenderManagerBase::TempSurface*)
// vaddr 0x2181878 | ghidra 0x2281878 | size 408 | symbol _ZN4Aska9TPoolFastINS_17RenderManagerBase11TempSurfaceELb0EE10SecurePoolEjPS2_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9TPoolFastINS_17RenderManagerBase11TempSurfaceELb0EE10SecurePoolEjPS2_
          (long param_1,uint param_2,long param_3)

{
  bool bVar1;
  char cVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  long *plVar6;
  
  if (*(char *)(param_1 + 0x41) == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (*(long *)(param_1 + 0x30) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    *(undefined1 *)(param_1 + 0x41) = 0;
  }
  plVar6 = (long *)(param_1 + 0x18);
  if ((*plVar6 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *plVar6 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  if (param_2 == 0) {
    return 1;
  }
  if (param_3 == 0) {
    param_3 = operator new[](unsigned long, std::nothrow_t const&)(((ulong)param_2 + (ulong)param_2 * 4) * 8,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 0x30) = param_3;
    if (param_3 == 0) {
      cVar2 = *(char *)(param_1 + 0x41);
      goto joined_r0x022819d4;
    }
    *(undefined1 *)(param_1 + 0x41) = 1;
  }
  else {
    *(long *)(param_1 + 0x30) = param_3;
  }
  uVar4 = (ulong)param_2 + 0x3f >> 6;
  *(int *)(param_1 + 0x20) = (int)uVar4;
  *(uint *)(param_1 + 0x24) = param_2;
  lVar5 = uVar4 << 3;
  lVar3 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
  *(long *)(param_1 + 0x18) = lVar3;
  *(undefined1 *)(param_1 + 0x28) = 1;
  if (lVar3 != 0) {
    memset(lVar3,0,lVar5);
    *(undefined8 *)(param_1 + 0x38) = 0;
    memset(lVar3,0,lVar5);
    return 1;
  }
  *(undefined1 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  cVar2 = *(char *)(param_1 + 0x41);
joined_r0x022819d4:
  if (cVar2 == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (param_3 == 0) {
      lVar3 = 0;
      *(undefined1 *)(param_1 + 0x41) = 0;
      bVar1 = false;
    }
    else {
      operator delete[](void*)(param_3);
      lVar3 = *(long *)(param_1 + 0x18);
      *(undefined8 *)(param_1 + 0x30) = 0;
      *(undefined1 *)(param_1 + 0x41) = 0;
      bVar1 = lVar3 != 0;
    }
    if ((bVar1) && (*(char *)(param_1 + 0x28) != '\0')) {
      operator delete[](void*)(lVar3);
      *(undefined1 *)(param_1 + 0x28) = 0;
    }
  }
  *plVar6 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  return 0;
}

// ==== Aska::TPoolFast<Aska::_RenderDeviceGL::TextureStateCache, false>::SecurePool(unsigned int, Aska::_RenderDeviceGL::TextureStateCache*)
// vaddr 0x2181af0 | ghidra 0x2281af0 | size 640 | symbol _ZN4Aska9TPoolFastINS_15_RenderDeviceGL17TextureStateCacheELb0EE10SecurePoolEjPS2_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska9TPoolFastINS_15_RenderDeviceGL17TextureStateCacheELb0EE10SecurePoolEjPS2_
          (long param_1,uint param_2,long param_3)

{
  uint uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  long lVar6;
  undefined8 uVar7;
  undefined8 *puVar8;
  ulong uVar9;
  ulong uVar10;
  long lVar11;
  uint uVar12;
  ulong uVar13;
  long *plVar14;
  uint *puVar15;
  
  if (*(char *)(param_1 + 0x41) == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (*(long *)(param_1 + 0x30) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    *(undefined1 *)(param_1 + 0x41) = 0;
  }
  plVar14 = (long *)(param_1 + 0x18);
  if ((*plVar14 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *plVar14 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  if (param_2 == 0) {
    return 1;
  }
  if (param_3 == 0) {
    puVar5 = (undefined8 *)
             operator new[](unsigned long, std::nothrow_t const&)(((ulong)param_2 + (ulong)param_2 * 4) * 4,PTR__ZSt7nothrow_02cb9a80);
    uVar4 = _UNK_029cd108;
    uVar3 = _UNK_029cd100;
    uVar2 = _UNK_029cd0f8;
    uVar7 = _UNK_029cd0f0;
    if (puVar5 != (undefined8 *)0x0) {
      lVar6 = (ulong)param_2 * 0x14;
      uVar13 = (lVar6 - 0x14U) / 0x14 + 1;
      puVar8 = puVar5;
      if ((uVar13 < 2) || (uVar9 = uVar13 & 0x1ffffffffffffffe, uVar9 == 0)) {
code_r0x02281c18:
        uVar2 = _UNK_029cd0f8;
        uVar7 = _UNK_029cd0f0;
        do {
          puVar8[1] = uVar2;
          *puVar8 = uVar7;
          *(undefined4 *)(puVar8 + 2) = 1;
          puVar8 = (undefined8 *)((long)puVar8 + 0x14);
        } while (puVar8 != (undefined8 *)((long)puVar5 + lVar6));
      }
      else {
        puVar8 = puVar5 + 4;
        uVar10 = uVar9;
        do {
          *puVar8 = 0x100002901;
          puVar8[-3] = uVar2;
          puVar8[-4] = uVar7;
          puVar8[-1] = uVar4;
          puVar8[-2] = uVar3;
          uVar10 = uVar10 - 2;
          puVar8 = puVar8 + 5;
        } while (uVar10 != 0);
        puVar8 = (undefined8 *)((long)puVar5 + uVar9 * 0x14);
        if (uVar13 != uVar9) goto code_r0x02281c18;
      }
      *(undefined8 **)(param_1 + 0x30) = puVar5;
      *(undefined1 *)(param_1 + 0x41) = 1;
      goto code_r0x02281c48;
    }
    *(undefined8 *)(param_1 + 0x30) = 0;
    if (*(char *)(param_1 + 0x41) != '\0') goto code_r0x02281d20;
code_r0x02281c04:
    *(undefined8 *)(param_1 + 0x30) = 0;
code_r0x02281d58:
    uVar7 = 0;
    *plVar14 = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  else {
    *(long *)(param_1 + 0x30) = param_3;
code_r0x02281c48:
    uVar13 = (ulong)param_2 + 0x3f >> 6;
    uVar12 = (uint)uVar13;
    if ((*(char *)(param_1 + 0x28) == '\0') || (uVar1 = *(uint *)(param_1 + 0x20), uVar1 < uVar12))
    {
      if ((*plVar14 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
        operator delete[](void*)();
        *(undefined1 *)(param_1 + 0x28) = 0;
      }
      puVar15 = (uint *)(param_1 + 0x20);
      *puVar15 = uVar12;
      *(uint *)(param_1 + 0x24) = param_2;
      lVar11 = uVar13 << 3;
      lVar6 = operator new[](unsigned long, std::nothrow_t const&)(lVar11,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x18) = lVar6;
      *(undefined1 *)(param_1 + 0x28) = 1;
      if (lVar6 == 0) {
        *(undefined1 *)(param_1 + 0x28) = 0;
        puVar15[0] = 0;
        puVar15[1] = 0;
        if (*(char *)(param_1 + 0x41) == '\0') goto code_r0x02281c04;
code_r0x02281d20:
        lVar6 = 0;
        if (*(long *)(param_1 + 0x30) != 0) {
          operator delete[](void*)(*(long *)(param_1 + 0x30));
          lVar6 = *(long *)(param_1 + 0x18);
          *(undefined8 *)(param_1 + 0x30) = 0;
        }
        *(undefined1 *)(param_1 + 0x41) = 0;
        if ((lVar6 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
          operator delete[](void*)(lVar6);
          *(undefined1 *)(param_1 + 0x28) = 0;
        }
        goto code_r0x02281d58;
      }
      if (uVar12 == 0) goto code_r0x02281d04;
      memset(lVar6,0,lVar11);
      *(undefined8 *)(param_1 + 0x38) = 0;
    }
    else {
      *(uint *)(param_1 + 0x24) = param_2;
      if (uVar1 == 0) {
code_r0x02281d04:
        *(undefined8 *)(param_1 + 0x38) = 0;
        return 1;
      }
      memset(*(undefined8 *)(param_1 + 0x18),0,uVar1 << 3);
      uVar12 = *(uint *)(param_1 + 0x20);
      *(undefined8 *)(param_1 + 0x38) = 0;
      if (uVar12 == 0) {
        return 1;
      }
    }
    memset(*plVar14,0,uVar12 << 3);
    uVar7 = 1;
  }
  return uVar7;
}

// ==== Aska::TPoolFast<Aska::RenderState::StatePack, false>::SecurePool(unsigned int, Aska::RenderState::StatePack*)
// vaddr 0x21c0440 | ghidra 0x22c0440 | size 404 | symbol _ZN4Aska9TPoolFastINS_11RenderState9StatePackELb0EE10SecurePoolEjPS2_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9TPoolFastINS_11RenderState9StatePackELb0EE10SecurePoolEjPS2_
          (long param_1,uint param_2,long param_3)

{
  bool bVar1;
  char cVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  long *plVar6;
  
  if (*(char *)(param_1 + 0x41) == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (*(long *)(param_1 + 0x30) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    *(undefined1 *)(param_1 + 0x41) = 0;
  }
  plVar6 = (long *)(param_1 + 0x18);
  if ((*plVar6 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *plVar6 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  if (param_2 == 0) {
    return 1;
  }
  if (param_3 == 0) {
    param_3 = operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 + (ulong)param_2 * 8,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 0x30) = param_3;
    if (param_3 == 0) {
      cVar2 = *(char *)(param_1 + 0x41);
      goto joined_r0x022c0598;
    }
    *(undefined1 *)(param_1 + 0x41) = 1;
  }
  else {
    *(long *)(param_1 + 0x30) = param_3;
  }
  uVar4 = (ulong)param_2 + 0x3f >> 6;
  *(int *)(param_1 + 0x20) = (int)uVar4;
  *(uint *)(param_1 + 0x24) = param_2;
  lVar5 = uVar4 << 3;
  lVar3 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
  *(long *)(param_1 + 0x18) = lVar3;
  *(undefined1 *)(param_1 + 0x28) = 1;
  if (lVar3 != 0) {
    memset(lVar3,0,lVar5);
    *(undefined8 *)(param_1 + 0x38) = 0;
    memset(lVar3,0,lVar5);
    return 1;
  }
  *(undefined1 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  cVar2 = *(char *)(param_1 + 0x41);
joined_r0x022c0598:
  if (cVar2 == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (param_3 == 0) {
      lVar3 = 0;
      *(undefined1 *)(param_1 + 0x41) = 0;
      bVar1 = false;
    }
    else {
      operator delete[](void*)(param_3);
      lVar3 = *(long *)(param_1 + 0x18);
      *(undefined8 *)(param_1 + 0x30) = 0;
      *(undefined1 *)(param_1 + 0x41) = 0;
      bVar1 = lVar3 != 0;
    }
    if ((bVar1) && (*(char *)(param_1 + 0x28) != '\0')) {
      operator delete[](void*)(lVar3);
      *(undefined1 *)(param_1 + 0x28) = 0;
    }
  }
  *plVar6 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  return 0;
}

// ==== Aska::TPoolFast<Aska::RenderState::StatePack, false>::Scoop(int)
// vaddr 0x21c0730 | ghidra 0x22c0730 | size 516 | symbol _ZN4Aska9TPoolFastINS_11RenderState9StatePackELb0EE5ScoopEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska9TPoolFastINS_11RenderState9StatePackELb0EE5ScoopEi(long param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  ulong *puVar9;
  int iVar10;
  ulong uVar11;
  uint uVar12;
  long lVar13;
  int iVar14;
  long lVar15;
  
  uVar4 = *(uint *)(param_1 + 0x24);
  if ((uint)(*(int *)(param_1 + 0x3c) + param_2) <= uVar4) {
    uVar5 = *(uint *)(param_1 + 0x38);
    iVar6 = param_2 + -1;
    iVar14 = (uVar4 + iVar6) - uVar5;
    if ((int)(uVar5 + param_2) <= (int)uVar4) {
      iVar14 = iVar6;
    }
    uVar12 = 0;
    if ((int)(uVar5 + param_2) <= (int)uVar4) {
      uVar12 = uVar5;
    }
    if (iVar14 < (int)uVar4) {
      if (param_2 == 0) {
code_r0x022c08fc:
        uVar5 = 0;
        if (uVar4 != 0) {
          uVar5 = (uVar12 + param_2) / uVar4;
        }
        *(uint *)(param_1 + 0x38) = (uVar12 + param_2) - uVar5 * uVar4;
        *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + param_2;
        return *(long *)(param_1 + 0x30) + (long)(int)uVar12 + (long)(int)uVar12 * 8;
      }
      lVar13 = *(long *)(param_1 + 0x18);
      do {
        uVar5 = uVar12 + 0x3f;
        if (-1 < (int)uVar12) {
          uVar5 = uVar12;
        }
        uVar7 = (int)uVar12 % 0x40;
        puVar9 = (ulong *)(lVar13 + (long)((int)uVar5 >> 6) * 8);
        iVar10 = param_2;
        uVar1 = uVar7;
        while( true ) {
          uVar11 = 0xffffffffffffffff >> ((ulong)(0x40 - iVar10) & 0x3f);
          if (0x3f < iVar10) {
            uVar11 = 0xffffffffffffffff;
          }
          iVar2 = 0;
          if (iVar10 < 0x40) {
            iVar2 = iVar10;
          }
          if ((uVar11 << ((ulong)uVar1 & 0x3f) & *puVar9) != 0) break;
          iVar3 = 0x40 - uVar1;
          if (iVar2 <= (int)(0x40 - uVar1)) {
            iVar3 = iVar2;
          }
          iVar10 = iVar10 - iVar3;
          puVar9 = puVar9 + 1;
          uVar1 = 0;
          if (iVar10 == 0) {
            uVar11 = 0xffffffffffffffff >> ((ulong)(0x40 - param_2) & 0x3f);
            lVar15 = ((long)((ulong)uVar5 << 0x20) >> 0x26) * 8;
            if (0x3f < param_2) {
              uVar11 = 0xffffffffffffffff;
            }
            iVar14 = 0;
            if (param_2 < 0x40) {
              iVar14 = param_2;
            }
            iVar6 = 0x40 - uVar7;
            if (iVar14 <= (int)(0x40 - uVar7)) {
              iVar6 = iVar14;
            }
            *(ulong *)(lVar13 + lVar15) =
                 *(ulong *)(lVar13 + lVar15) | uVar11 << ((ulong)uVar7 & 0x3f);
            for (iVar6 = param_2 - iVar6; iVar6 != 0; iVar6 = iVar6 - iVar14) {
              lVar15 = lVar15 + 8;
              uVar11 = 0xffffffffffffffff >> ((ulong)(0x40 - iVar6) & 0x3f);
              iVar14 = iVar6;
              if (0x3f < iVar6) {
                uVar11 = 0xffffffffffffffff;
                iVar14 = 0x40;
              }
              if (0x3f < iVar14) {
                iVar14 = 0x40;
              }
              *(ulong *)(*(long *)(param_1 + 0x18) + lVar15) =
                   uVar11 | *(ulong *)(*(long *)(param_1 + 0x18) + lVar15);
            }
            goto code_r0x022c08fc;
          }
        }
        iVar10 = 0;
        do {
          uVar5 = uVar12 + iVar6 + iVar10;
          iVar10 = iVar10 + -1;
        } while ((1L << (uVar5 & 0x3f) & *(ulong *)(lVar13 + (ulong)(uVar5 >> 6) * 8)) == 0);
        iVar2 = (param_2 << 1 | 1U) + uVar12;
        iVar3 = param_2 + 1 + uVar12;
        iVar8 = (((uVar4 - 1) - param_2) - uVar12) - iVar10;
        uVar12 = 0;
        if (iVar2 + iVar10 <= (int)uVar4) {
          iVar8 = 0;
          uVar12 = iVar3 + iVar10;
        }
        iVar14 = iVar8 + param_2 + 1 + iVar14 + iVar10;
        if ((int)uVar4 <= iVar14) {
          return 0;
        }
      } while( true );
    }
  }
  return 0;
}

// ==== Aska::TPoolFast<Aska::Vector, false>::SecurePool(unsigned int, Aska::Vector*)
// vaddr 0x21c8080 | ghidra 0x22c8080 | size 408 | symbol _ZN4Aska9TPoolFastINS_6VectorELb0EE10SecurePoolEjPS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9TPoolFastINS_6VectorELb0EE10SecurePoolEjPS1_(long param_1,uint param_2,long param_3)

{
  bool bVar1;
  char cVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  long *plVar6;
  
  if (*(char *)(param_1 + 0x41) == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (*(long *)(param_1 + 0x30) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    *(undefined1 *)(param_1 + 0x41) = 0;
  }
  plVar6 = (long *)(param_1 + 0x18);
  if ((*plVar6 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *plVar6 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  if (param_2 == 0) {
    return 1;
  }
  if (param_3 == 0) {
    param_3 = operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 << 4,PTR__ZSt7nothrow_02cb9a80);
    if (param_3 == 0) {
      *(undefined8 *)(param_1 + 0x30) = 0;
      cVar2 = *(char *)(param_1 + 0x41);
      goto joined_r0x022c81dc;
    }
    *(long *)(param_1 + 0x30) = param_3;
    *(undefined1 *)(param_1 + 0x41) = 1;
  }
  else {
    *(long *)(param_1 + 0x30) = param_3;
  }
  uVar4 = (ulong)param_2 + 0x3f >> 6;
  *(int *)(param_1 + 0x20) = (int)uVar4;
  *(uint *)(param_1 + 0x24) = param_2;
  lVar5 = uVar4 << 3;
  lVar3 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
  *(long *)(param_1 + 0x18) = lVar3;
  *(undefined1 *)(param_1 + 0x28) = 1;
  if (lVar3 != 0) {
    memset(lVar3,0,lVar5);
    *(undefined8 *)(param_1 + 0x38) = 0;
    memset(lVar3,0,lVar5);
    return 1;
  }
  *(undefined1 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  cVar2 = *(char *)(param_1 + 0x41);
joined_r0x022c81dc:
  if (cVar2 == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (param_3 == 0) {
      lVar3 = 0;
      *(undefined1 *)(param_1 + 0x41) = 0;
      bVar1 = false;
    }
    else {
      operator delete[](void*)(param_3);
      lVar3 = *(long *)(param_1 + 0x18);
      *(undefined8 *)(param_1 + 0x30) = 0;
      *(undefined1 *)(param_1 + 0x41) = 0;
      bVar1 = lVar3 != 0;
    }
    if ((bVar1) && (*(char *)(param_1 + 0x28) != '\0')) {
      operator delete[](void*)(lVar3);
      *(undefined1 *)(param_1 + 0x28) = 0;
    }
  }
  *plVar6 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  return 0;
}

// ==== Aska::TPoolFast<Aska::ConstInfo, false>::SecurePool(unsigned int, Aska::ConstInfo*)
// vaddr 0x21c8218 | ghidra 0x22c8218 | size 408 | symbol _ZN4Aska9TPoolFastINS_9ConstInfoELb0EE10SecurePoolEjPS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9TPoolFastINS_9ConstInfoELb0EE10SecurePoolEjPS1_(long param_1,uint param_2,long param_3)

{
  bool bVar1;
  char cVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  long *plVar6;
  
  if (*(char *)(param_1 + 0x41) == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (*(long *)(param_1 + 0x30) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    *(undefined1 *)(param_1 + 0x41) = 0;
  }
  plVar6 = (long *)(param_1 + 0x18);
  if ((*plVar6 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *plVar6 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  if (param_2 == 0) {
    return 1;
  }
  if (param_3 == 0) {
    param_3 = operator new[](unsigned long, std::nothrow_t const&)(((ulong)param_2 + (ulong)param_2 * 2) * 8,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 0x30) = param_3;
    if (param_3 == 0) {
      cVar2 = *(char *)(param_1 + 0x41);
      goto joined_r0x022c8374;
    }
    *(undefined1 *)(param_1 + 0x41) = 1;
  }
  else {
    *(long *)(param_1 + 0x30) = param_3;
  }
  uVar4 = (ulong)param_2 + 0x3f >> 6;
  *(int *)(param_1 + 0x20) = (int)uVar4;
  *(uint *)(param_1 + 0x24) = param_2;
  lVar5 = uVar4 << 3;
  lVar3 = operator new[](unsigned long, std::nothrow_t const&)(lVar5,PTR__ZSt7nothrow_02cb9a80);
  *(long *)(param_1 + 0x18) = lVar3;
  *(undefined1 *)(param_1 + 0x28) = 1;
  if (lVar3 != 0) {
    memset(lVar3,0,lVar5);
    *(undefined8 *)(param_1 + 0x38) = 0;
    memset(lVar3,0,lVar5);
    return 1;
  }
  *(undefined1 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  cVar2 = *(char *)(param_1 + 0x41);
joined_r0x022c8374:
  if (cVar2 == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (param_3 == 0) {
      lVar3 = 0;
      *(undefined1 *)(param_1 + 0x41) = 0;
      bVar1 = false;
    }
    else {
      operator delete[](void*)(param_3);
      lVar3 = *(long *)(param_1 + 0x18);
      *(undefined8 *)(param_1 + 0x30) = 0;
      *(undefined1 *)(param_1 + 0x41) = 0;
      bVar1 = lVar3 != 0;
    }
    if ((bVar1) && (*(char *)(param_1 + 0x28) != '\0')) {
      operator delete[](void*)(lVar3);
      *(undefined1 *)(param_1 + 0x28) = 0;
    }
  }
  *plVar6 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  return 0;
}

// ==== Aska::TPoolLegacy<Aska::AliasID, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x21df6ac | ghidra 0x22df6ac | size 500 | symbol _ZN4Aska11TPoolLegacyINS_7AliasIDELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_7AliasIDELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x38,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x022df864;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x022df804;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x022df864:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x022df804:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x38);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::TextureIDs, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x21e070c | ghidra 0x22e070c | size 500 | symbol _ZN4Aska11TPoolLegacyINS_10TextureIDsELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_10TextureIDsELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x48,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x022e08c4;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x022e0864;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x022e08c4:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x022e0864:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x48);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::RelatedTextureIDSet, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x21e1a64 | ghidra 0x22e1a64 | size 500 | symbol _ZN4Aska11TPoolLegacyINS_19RelatedTextureIDSetELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_19RelatedTextureIDSetELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x38,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x022e1c1c;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x022e1bbc;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x022e1c1c:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x022e1bbc:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x38);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::TextureNode, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x21e63d0 | ghidra 0x22e63d0 | size 500 | symbol _ZN4Aska11TPoolLegacyINS_11TextureNodeELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_11TextureNodeELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x108,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x022e6588;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x022e6528;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x022e6588:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x022e6528:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x108);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::TextureMemory, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x21e6a2c | ghidra 0x22e6a2c | size 500 | symbol _ZN4Aska11TPoolLegacyINS_13TextureMemoryELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_13TextureMemoryELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x48,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x022e6be4;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x022e6b84;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x022e6be4:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x022e6b84:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x48);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::TextureDeletionID, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x21e6d2c | ghidra 0x22e6d2c | size 500 | symbol _ZN4Aska11TPoolLegacyINS_17TextureDeletionIDELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_17TextureDeletionIDELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x38,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x022e6ee4;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x022e6e84;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x022e6ee4:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x022e6e84:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x38);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::TextureID, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x21e6fec | ghidra 0x22e6fec | size 500 | symbol _ZN4Aska11TPoolLegacyINS_9TextureIDELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_9TextureIDELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x30,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x022e71a4;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x022e7144;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x022e71a4:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x022e7144:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x30);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::Yayoi::NetworkEvent::ConnectJob, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x220261c | ghidra 0x230261c | size 328 | symbol _ZN4Aska11TPoolLegacyINS_5Yayoi12NetworkEvent10ConnectJobELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_5Yayoi12NetworkEvent10ConnectJobELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)(param_1 + 0x20);
  if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar5 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
code_r0x02302708:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0xa0,8,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x023026c0;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x023026c0:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0xa0);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x02302708;
      }
      lVar4 = *(long *)(param_1 + 0x40);
    }
    if (lVar4 != 0) {
      if (*(char *)(param_1 + 0x48) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    *(char *)(param_1 + 0x48) = '\0';
    if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar3 = 0;
    *plVar5 = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return uVar3;
}

// ==== Aska::TPoolLegacy<Aska::Yayoi::NetworkEvent::AcceptJob, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x2202764 | ghidra 0x2302764 | size 328 | symbol _ZN4Aska11TPoolLegacyINS_5Yayoi12NetworkEvent9AcceptJobELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_5Yayoi12NetworkEvent9AcceptJobELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)(param_1 + 0x20);
  if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar5 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
code_r0x02302850:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x18,8,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x02302808;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x02302808:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x18);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x02302850;
      }
      lVar4 = *(long *)(param_1 + 0x40);
    }
    if (lVar4 != 0) {
      if (*(char *)(param_1 + 0x48) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    *(char *)(param_1 + 0x48) = '\0';
    if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar3 = 0;
    *plVar5 = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return uVar3;
}

// ==== Aska::TPoolLegacy<Aska::Yayoi::NetworkEvent::PollJob, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x22028ac | ghidra 0x23028ac | size 328 | symbol _ZN4Aska11TPoolLegacyINS_5Yayoi12NetworkEvent7PollJobELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_5Yayoi12NetworkEvent7PollJobELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,undefined8 param_5)

{
  long lVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)(param_1 + 0x20);
  if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar5 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
code_r0x02302998:
    uVar3 = 1;
  }
  else {
    if (param_4 == 0) {
      lVar1 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x28,8,1);
      *(undefined1 *)(param_1 + 0x48) = 1;
      *(long *)(param_1 + 0x40) = lVar1;
      lVar4 = 0;
      if (lVar1 != 0) goto code_r0x02302950;
    }
    else {
      *(undefined1 *)(param_1 + 0x48) = 0;
      *(long *)(param_1 + 0x40) = param_4;
code_r0x02302950:
      uVar2 = Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)(param_1 + 0x10,param_2,param_5);
      if ((uVar2 & 1) != 0) {
        if ((param_3 & 1) != 0) {
          memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x28);
        }
        *(undefined8 *)(param_1 + 0x38) = 0;
        if (*(int *)(param_1 + 0x28) != 0) {
          memset(*plVar5,0,*(int *)(param_1 + 0x28) << 2);
        }
        goto code_r0x02302998;
      }
      lVar4 = *(long *)(param_1 + 0x40);
    }
    if (lVar4 != 0) {
      if (*(char *)(param_1 + 0x48) != '\0') {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    *(char *)(param_1 + 0x48) = '\0';
    if ((*plVar5 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar3 = 0;
    *plVar5 = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return uVar3;
}

// ==== Aska::TPoolLegacy<Aska::Yayoi::RawdatPair, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x220b2f4 | ghidra 0x230b2f4 | size 500 | symbol _ZN4Aska11TPoolLegacyINS_5Yayoi10RawdatPairELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_5Yayoi10RawdatPairELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x60,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x0230b4ac;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x0230b44c;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x0230b4ac:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x0230b44c:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x60);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolAtomicDynamic<Aska::DiscReadStream::ReadAsyncNotify>::SecurePool(int)
// vaddr 0x2226d80 | ghidra 0x2326d80 | size 568 | symbol _ZN4Aska18TPoolAtomicDynamicINS_14DiscReadStream15ReadAsyncNotifyEE10SecurePoolEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska18TPoolAtomicDynamicINS_14DiscReadStream15ReadAsyncNotifyEE10SecurePoolEi
          (long param_1,int param_2)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  undefined1 auVar4 [16];
  undefined4 *puVar5;
  long *plVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  long *plVar10;
  long lVar11;
  long lVar12;
  
  if ((param_2 == 0) || (*(char *)(param_1 + 0x20) != '\0')) {
    return 0;
  }
  *(undefined2 *)(param_1 + 0x20) = 0x101;
  iVar3 = param_2 + 0x1f;
  if (-1 < param_2) {
    iVar3 = param_2;
  }
  *(int *)(param_1 + 0x24) = param_2;
  uVar1 = (iVar3 >> 5) + 1;
  auVar4._8_8_ = 0;
  auVar4._0_8_ = (long)(int)uVar1;
  uVar7 = -(ulong)(uVar1 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar1 << 2;
  if (SUB168(auVar4 * ZEXT816(4),8) != 0) {
    uVar7 = 0xffffffffffffffff;
  }
  puVar5 = (undefined4 *)operator new[](unsigned long, std::nothrow_t const&)(uVar7,PTR__ZSt7nothrow_02cb9a80);
  *(undefined4 **)(param_1 + 0x10) = puVar5;
  if (puVar5 != (undefined4 *)0x0) {
    uVar7 = (ulong)param_2;
    plVar6 = (long *)operator new[](unsigned long, std::nothrow_t const&)((uVar7 + (long)param_2 * 4) * 0x10,PTR__ZSt7nothrow_02cb9a80);
    *(long **)(param_1 + 8) = plVar6;
    if (plVar6 != (long *)0x0) {
      if (0 < param_2) {
        if (param_2 == 1) {
          uVar8 = 0;
        }
        else {
          uVar8 = uVar7 & 0xfffffffffffffffe;
          if (uVar8 != 0) {
            puVar2 = PTR__ZTVN4Aska14DiscReadStream15ReadAsyncNotifyE_02cc2498 + 0x10;
            uVar9 = uVar8;
            plVar10 = plVar6;
            do {
              *plVar10 = (long)puVar2;
              plVar10[10] = (long)puVar2;
              uVar9 = uVar9 - 2;
              plVar10 = plVar10 + 0x14;
            } while (uVar9 != 0);
            if (uVar8 == uVar7) goto code_r0x02326f90;
          }
        }
        puVar2 = PTR__ZTVN4Aska14DiscReadStream15ReadAsyncNotifyE_02cc2498 + 0x10;
        plVar6 = plVar6 + uVar8 * 10;
        do {
          uVar8 = uVar8 + 1;
          *plVar6 = (long)puVar2;
          plVar6 = plVar6 + 10;
        } while ((long)uVar8 < (long)uVar7);
      }
code_r0x02326f90:
      if (uVar1 != 0) {
        uVar7 = ~((long)(int)uVar1 - 1U);
        do {
          uVar7 = uVar7 + 1;
          *puVar5 = 0;
          puVar5 = puVar5 + 1;
        } while (uVar7 != 0);
      }
      return 1;
    }
    operator delete[](void*)(puVar5);
    *(undefined8 *)(param_1 + 0x10) = 0;
    if (*(long **)(param_1 + 8) == (long *)0x0) goto code_r0x02326f18;
    if (0 < *(int *)(param_1 + 0x24)) {
      (**(code **)(**(long **)(param_1 + 8) + 8))();
      if (1 < *(int *)(param_1 + 0x24)) {
        lVar11 = 1;
        lVar12 = 0x50;
        do {
          (**(code **)(*(long *)(*(long *)(param_1 + 8) + lVar12) + 8))();
          lVar11 = lVar11 + 1;
          lVar12 = lVar12 + 0x50;
        } while (lVar11 < *(int *)(param_1 + 0x24));
      }
      goto code_r0x02326f08;
    }
    goto code_r0x02326f10;
  }
  if (*(long **)(param_1 + 8) == (long *)0x0) goto code_r0x02326f18;
  if (*(int *)(param_1 + 0x24) < 1) {
code_r0x02326f10:
    operator delete[](void*)();
  }
  else {
    (**(code **)(**(long **)(param_1 + 8) + 8))();
    if (1 < *(int *)(param_1 + 0x24)) {
      lVar11 = 1;
      lVar12 = 0x50;
      do {
        (**(code **)(*(long *)(*(long *)(param_1 + 8) + lVar12) + 8))();
        lVar11 = lVar11 + 1;
        lVar12 = lVar12 + 0x50;
      } while (lVar11 < *(int *)(param_1 + 0x24));
    }
code_r0x02326f08:
    if (*(long *)(param_1 + 8) != 0) goto code_r0x02326f10;
  }
  *(undefined8 *)(param_1 + 8) = 0;
code_r0x02326f18:
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined2 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  return 0;
}

// ==== Aska::TPoolFast<Aska::Event, false>::SecurePool(unsigned int, Aska::Event*)
// vaddr 0x2228084 | ghidra 0x2328084 | size 628 | symbol _ZN4Aska9TPoolFastINS_5EventELb0EE10SecurePoolEjPS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9TPoolFastINS_5EventELb0EE10SecurePoolEjPS1_(long param_1,uint param_2,long param_3)

{
  uint uVar1;
  ulong *puVar2;
  undefined8 uVar3;
  long lVar4;
  uint uVar5;
  ulong uVar6;
  ulong *puVar7;
  uint *puVar8;
  long lVar9;
  long *plVar10;
  
  if (*(char *)(param_1 + 0x41) == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    lVar9 = *(long *)(param_1 + 0x30);
    if (lVar9 != 0) {
      lVar4 = *(long *)(lVar9 + -8);
      if (lVar4 != 0) {
        lVar4 = lVar4 * 0x68;
        do {
          Aska::Event::Exit()(lVar9 + lVar4 + -0x68);
          lVar4 = lVar4 + -0x68;
        } while (lVar4 != 0);
      }
      operator delete[](void*)((long *)(lVar9 + -8));
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    *(undefined1 *)(param_1 + 0x41) = 0;
  }
  plVar10 = (long *)(param_1 + 0x18);
  if ((*plVar10 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *plVar10 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  if (param_2 == 0) {
    return 1;
  }
  if (param_3 == 0) {
    puVar2 = (ulong *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 * 0x68 + 8,PTR__ZSt7nothrow_02cb9a80);
    if (puVar2 != (ulong *)0x0) {
      *puVar2 = (ulong)param_2;
      lVar9 = (ulong)param_2 * 0x68;
      puVar7 = puVar2 + 1;
      do {
        Aska::Event::Event()(puVar7);
        lVar9 = lVar9 + -0x68;
        puVar7 = puVar7 + 0xd;
      } while (lVar9 != 0);
      *(ulong **)(param_1 + 0x30) = puVar2 + 1;
      *(undefined1 *)(param_1 + 0x41) = 1;
      goto code_r0x02328178;
    }
    *(undefined8 *)(param_1 + 0x30) = 0;
    if (*(char *)(param_1 + 0x41) != '\0') goto code_r0x02328250;
code_r0x023282ac:
    *(undefined8 *)(param_1 + 0x30) = 0;
code_r0x023282cc:
    uVar3 = 0;
    *plVar10 = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  else {
    *(long *)(param_1 + 0x30) = param_3;
code_r0x02328178:
    uVar6 = (ulong)param_2 + 0x3f >> 6;
    uVar5 = (uint)uVar6;
    if ((*(char *)(param_1 + 0x28) == '\0') || (uVar1 = *(uint *)(param_1 + 0x20), uVar1 < uVar5)) {
      if ((*plVar10 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
        operator delete[](void*)();
        *(undefined1 *)(param_1 + 0x28) = 0;
      }
      puVar8 = (uint *)(param_1 + 0x20);
      *puVar8 = uVar5;
      *(uint *)(param_1 + 0x24) = param_2;
      lVar4 = uVar6 << 3;
      lVar9 = operator new[](unsigned long, std::nothrow_t const&)(lVar4,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x18) = lVar9;
      *(undefined1 *)(param_1 + 0x28) = 1;
      if (lVar9 == 0) {
        *(undefined1 *)(param_1 + 0x28) = 0;
        puVar8[0] = 0;
        puVar8[1] = 0;
        if (*(char *)(param_1 + 0x41) == '\0') goto code_r0x023282ac;
code_r0x02328250:
        lVar9 = *(long *)(param_1 + 0x30);
        if (lVar9 == 0) {
          *(undefined1 *)(param_1 + 0x41) = 0;
        }
        else {
          lVar4 = *(long *)(lVar9 + -8);
          if (lVar4 != 0) {
            lVar4 = lVar4 * 0x68;
            do {
              Aska::Event::Exit()(lVar9 + lVar4 + -0x68);
              lVar4 = lVar4 + -0x68;
            } while (lVar4 != 0);
          }
          operator delete[](void*)((long *)(lVar9 + -8));
          *(undefined8 *)(param_1 + 0x30) = 0;
          *(undefined1 *)(param_1 + 0x41) = 0;
          if ((*(long *)(param_1 + 0x18) != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
            operator delete[](void*)(*(long *)(param_1 + 0x18));
            *(undefined1 *)(param_1 + 0x28) = 0;
          }
        }
        goto code_r0x023282cc;
      }
      if (uVar5 == 0) goto code_r0x02328234;
      memset(lVar9,0,lVar4);
      *(undefined8 *)(param_1 + 0x38) = 0;
    }
    else {
      *(uint *)(param_1 + 0x24) = param_2;
      if (uVar1 == 0) {
code_r0x02328234:
        *(undefined8 *)(param_1 + 0x38) = 0;
        return 1;
      }
      memset(*(undefined8 *)(param_1 + 0x18),0,uVar1 << 3);
      uVar5 = *(uint *)(param_1 + 0x20);
      *(undefined8 *)(param_1 + 0x38) = 0;
      if (uVar5 == 0) {
        return 1;
      }
    }
    memset(*plVar10,0,uVar5 << 3);
    uVar3 = 1;
  }
  return uVar3;
}

// ==== Aska::TPoolLegacy<Aska::HostMachineSet, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x222abac | ghidra 0x232abac | size 500 | symbol _ZN4Aska11TPoolLegacyINS_14HostMachineSetELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_14HostMachineSetELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0x60,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x0232ad64;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x0232ad04;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x0232ad64:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x0232ad04:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0x60);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolLegacy<Aska::MappedAddressSet, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x222ff14 | ghidra 0x232ff14 | size 500 | symbol _ZN4Aska11TPoolLegacyINS_16MappedAddressSetELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyINS_16MappedAddressSetELb0EE10SecurePoolEjbPKvPKj
          (long param_1,uint param_2,ulong param_3,long param_4,long param_5)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  ulong uVar5;
  uint *puVar6;
  
  plVar4 = (long *)(param_1 + 0x20);
  if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x30) = 0;
  }
  *plVar4 = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(long *)(param_1 + 0x40) != 0) {
    if (*(char *)(param_1 + 0x48) != '\0') {
      operator delete[](void*)();
    }
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (param_2 == 0) {
    return 1;
  }
  if (param_4 == 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(param_2 * 0xb0,8,1);
    *(undefined1 *)(param_1 + 0x48) = 1;
    *(long *)(param_1 + 0x40) = lVar2;
    lVar3 = 0;
    if (lVar2 == 0) goto code_r0x023300cc;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x0233006c;
    param_5 = *plVar4;
    uVar5 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    puVar6 = (uint *)(param_1 + 0x28);
    *puVar6 = (uint)uVar5;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(uint *)(param_1 + 0x2c) = param_2;
    if (param_5 == 0) {
      param_5 = operator new[](unsigned long, std::nothrow_t const&)(uVar5 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 1;
      if (param_5 == 0) {
        *(undefined1 *)(param_1 + 0x30) = 0;
        puVar6[0] = 0;
        puVar6[1] = 0;
        lVar3 = *(long *)(param_1 + 0x40);
code_r0x023300cc:
        if (lVar3 != 0) {
          if (*(char *)(param_1 + 0x48) != '\0') {
            operator delete[](void*)();
          }
          *(undefined8 *)(param_1 + 0x40) = 0;
        }
        *(char *)(param_1 + 0x48) = '\0';
        if ((*plVar4 != 0) && (*(char *)(param_1 + 0x30) != '\0')) {
          operator delete[](void*)();
          *(undefined1 *)(param_1 + 0x30) = 0;
        }
        *plVar4 = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x20) = param_5;
      *(undefined1 *)(param_1 + 0x30) = 0;
    }
    uVar5 = uVar5 << 2;
  }
  memset(param_5,0,uVar5);
code_r0x0233006c:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 * 0xb0);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Aska::TPoolFast<Aska::NotifierThread::NotifyElement, false>::SecurePool(unsigned int, Aska::NotifierThread::NotifyElement*)
// vaddr 0x2235e64 | ghidra 0x2335e64 | size 536 | symbol _ZN4Aska9TPoolFastINS_14NotifierThread13NotifyElementELb0EE10SecurePoolEjPS2_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9TPoolFastINS_14NotifierThread13NotifyElementELb0EE10SecurePoolEjPS2_
          (long param_1,uint param_2,long param_3)

{
  bool bVar1;
  uint uVar2;
  ulong *puVar3;
  undefined *puVar4;
  ulong *puVar5;
  long lVar6;
  undefined8 uVar7;
  long lVar8;
  uint uVar9;
  ulong uVar10;
  long *plVar11;
  uint *puVar12;
  
  if (*(char *)(param_1 + 0x41) == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (*(long *)(param_1 + 0x30) != 0) {
      operator delete[](void*)(*(long *)(param_1 + 0x30) + -8);
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    *(undefined1 *)(param_1 + 0x41) = 0;
  }
  plVar11 = (long *)(param_1 + 0x18);
  if ((*plVar11 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *plVar11 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  if (param_2 == 0) {
    return 1;
  }
  if (param_3 == 0) {
    puVar5 = (ulong *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 * 0x28 + 8,PTR__ZSt7nothrow_02cb9a80);
    puVar4 = PTR__ZTVN4Aska14NotifierThread13NotifyElementE_02cb7108;
    if (puVar5 != (ulong *)0x0) {
      *puVar5 = (ulong)param_2;
      lVar6 = (ulong)param_2 * 0x28;
      puVar3 = puVar5;
      do {
        puVar3[1] = (ulong)(puVar4 + 0x10);
        puVar3[2] = 0;
        puVar3[3] = 0;
        puVar3[4] = 0;
        *(undefined4 *)(puVar3 + 5) = 0;
        lVar6 = lVar6 + -0x28;
        puVar3 = puVar3 + 5;
      } while (lVar6 != 0);
      *(ulong **)(param_1 + 0x30) = puVar5 + 1;
      *(undefined1 *)(param_1 + 0x41) = 1;
      goto code_r0x02335f38;
    }
    *(undefined8 *)(param_1 + 0x30) = 0;
    if (*(char *)(param_1 + 0x41) != '\0') goto code_r0x02336010;
code_r0x02336058:
    lVar6 = 0;
    *(undefined8 *)(param_1 + 0x30) = 0;
    bVar1 = false;
joined_r0x02336060:
    if ((bVar1) && (*(char *)(param_1 + 0x28) != '\0')) {
      operator delete[](void*)(lVar6);
      *(undefined1 *)(param_1 + 0x28) = 0;
    }
    uVar7 = 0;
    *plVar11 = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  else {
    *(long *)(param_1 + 0x30) = param_3;
code_r0x02335f38:
    uVar10 = (ulong)param_2 + 0x3f >> 6;
    uVar9 = (uint)uVar10;
    if ((*(char *)(param_1 + 0x28) == '\0') || (uVar2 = *(uint *)(param_1 + 0x20), uVar2 < uVar9)) {
      if ((*plVar11 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
        operator delete[](void*)();
        *(undefined1 *)(param_1 + 0x28) = 0;
      }
      puVar12 = (uint *)(param_1 + 0x20);
      *puVar12 = uVar9;
      *(uint *)(param_1 + 0x24) = param_2;
      lVar8 = uVar10 << 3;
      lVar6 = operator new[](unsigned long, std::nothrow_t const&)(lVar8,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x18) = lVar6;
      *(undefined1 *)(param_1 + 0x28) = 1;
      if (lVar6 == 0) {
        *(undefined1 *)(param_1 + 0x28) = 0;
        puVar12[0] = 0;
        puVar12[1] = 0;
        if (*(char *)(param_1 + 0x41) == '\0') goto code_r0x02336058;
code_r0x02336010:
        lVar6 = 0;
        if (*(long *)(param_1 + 0x30) != 0) {
          operator delete[](void*)(*(long *)(param_1 + 0x30) + -8);
          lVar6 = *(long *)(param_1 + 0x18);
          *(undefined8 *)(param_1 + 0x30) = 0;
        }
        *(undefined1 *)(param_1 + 0x41) = 0;
        bVar1 = lVar6 != 0;
        goto joined_r0x02336060;
      }
      if (uVar9 == 0) goto code_r0x02335ff4;
      memset(lVar6,0,lVar8);
      *(undefined8 *)(param_1 + 0x38) = 0;
    }
    else {
      *(uint *)(param_1 + 0x24) = param_2;
      if (uVar2 == 0) {
code_r0x02335ff4:
        *(undefined8 *)(param_1 + 0x38) = 0;
        return 1;
      }
      memset(*(undefined8 *)(param_1 + 0x18),0,uVar2 << 3);
      uVar9 = *(uint *)(param_1 + 0x20);
      *(undefined8 *)(param_1 + 0x38) = 0;
      if (uVar9 == 0) {
        return 1;
      }
    }
    memset(*plVar11,0,uVar9 << 3);
    uVar7 = 1;
  }
  return uVar7;
}

// ==== Aska::TPoolFast<unsigned char [90], true>::Scoop(int)
// vaddr 0x23571dc | ghidra 0x24571dc | size 824 | symbol _ZN4Aska9TPoolFastIA90_hLb1EE5ScoopEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska9TPoolFastIA90_hLb1EE5ScoopEi(long param_1,int param_2)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  char cVar7;
  bool bVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  ulong *puVar13;
  ulong uVar14;
  int iVar15;
  int *piVar16;
  uint uVar17;
  long lVar18;
  long lVar19;
  
  piVar16 = (int *)(param_1 + 0x78);
  iVar15 = 0;
  do {
    while (*piVar16 == -1) {
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(piVar16,0x10);
      if (bVar8) {
        *piVar16 = 0;
        cVar7 = ExclusiveMonitorsStatus();
      }
      if (cVar7 == '\0') goto code_r0x024572c0;
    }
    ClearExclusiveLocal();
    bVar8 = iVar15 < 0x1ff;
    iVar15 = iVar15 + 1;
  } while (bVar8);
  piVar2 = (int *)(param_1 + 0x7c);
  do {
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar8) {
      *piVar2 = *piVar2 + 1;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
  do {
    if (*piVar16 != -1) {
      ClearExclusiveLocal();
      do {
        uVar14 = Aska::Semaphore::IsReady() const(param_1 + 0xb8);
        if ((uVar14 & 1) == 0) {
          do {
            cVar7 = '\x01';
            bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
            if (bVar8) {
              *piVar2 = *piVar2 + -1;
              cVar7 = ExclusiveMonitorsStatus();
            }
          } while (cVar7 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0xb8);
        }
        do {
          cVar7 = '\x01';
          bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
          if (bVar8) {
            *piVar2 = *piVar2 + 1;
            cVar7 = ExclusiveMonitorsStatus();
          }
        } while (cVar7 != '\0');
        while (*piVar16 == -1) {
          cVar7 = '\x01';
          bVar8 = (bool)ExclusiveMonitorPass(piVar16,0x10);
          if (bVar8) {
            *piVar16 = 0;
            cVar7 = ExclusiveMonitorsStatus();
          }
          if (cVar7 == '\0') goto code_r0x024572b0;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(piVar16,0x10);
    if (bVar8) {
      *piVar16 = 0;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
code_r0x024572b0:
  do {
    cVar7 = '\x01';
    bVar8 = (bool)ExclusiveMonitorPass(piVar2,0x10);
    if (bVar8) {
      *piVar2 = *piVar2 + -1;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
code_r0x024572c0:
  DataMemoryBarrier(2,3);
  uVar5 = *(uint *)(param_1 + 0x24);
  if ((uint)(*(int *)(param_1 + 0x3c) + param_2) <= uVar5) {
    uVar6 = *(uint *)(param_1 + 0x38);
    iVar9 = param_2 + -1;
    iVar15 = (uVar5 + iVar9) - uVar6;
    if ((int)(uVar6 + param_2) <= (int)uVar5) {
      iVar15 = iVar9;
    }
    uVar17 = 0;
    if ((int)(uVar6 + param_2) <= (int)uVar5) {
      uVar17 = uVar6;
    }
    if (iVar15 < (int)uVar5) {
      if (param_2 == 0) {
code_r0x0245748c:
        uVar6 = 0;
        if (uVar5 != 0) {
          uVar6 = (uVar17 + param_2) / uVar5;
        }
        *(uint *)(param_1 + 0x38) = (uVar17 + param_2) - uVar6 * uVar5;
        *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + param_2;
        lVar19 = *(long *)(param_1 + 0x30) + (long)(int)uVar17 * 0x5a;
      }
      else {
        lVar18 = *(long *)(param_1 + 0x18);
        do {
          uVar6 = uVar17 + 0x3f;
          if (-1 < (int)uVar17) {
            uVar6 = uVar17;
          }
          uVar10 = (int)uVar17 % 0x40;
          puVar13 = (ulong *)(lVar18 + (long)((int)uVar6 >> 6) * 8);
          uVar1 = uVar10;
          iVar12 = param_2;
          while( true ) {
            uVar14 = 0xffffffffffffffff >> ((ulong)(0x40 - iVar12) & 0x3f);
            if (0x3f < iVar12) {
              uVar14 = 0xffffffffffffffff;
            }
            iVar3 = 0;
            if (iVar12 < 0x40) {
              iVar3 = iVar12;
            }
            if ((uVar14 << ((ulong)uVar1 & 0x3f) & *puVar13) != 0) break;
            iVar4 = 0x40 - uVar1;
            if (iVar3 <= (int)(0x40 - uVar1)) {
              iVar4 = iVar3;
            }
            iVar12 = iVar12 - iVar4;
            puVar13 = puVar13 + 1;
            uVar1 = 0;
            if (iVar12 == 0) {
              uVar14 = 0xffffffffffffffff >> ((ulong)(0x40 - param_2) & 0x3f);
              lVar19 = ((long)((ulong)uVar6 << 0x20) >> 0x26) * 8;
              if (0x3f < param_2) {
                uVar14 = 0xffffffffffffffff;
              }
              iVar15 = 0;
              if (param_2 < 0x40) {
                iVar15 = param_2;
              }
              iVar9 = 0x40 - uVar10;
              if (iVar15 <= (int)(0x40 - uVar10)) {
                iVar9 = iVar15;
              }
              *(ulong *)(lVar18 + lVar19) =
                   *(ulong *)(lVar18 + lVar19) | uVar14 << ((ulong)uVar10 & 0x3f);
              for (iVar9 = param_2 - iVar9; iVar9 != 0; iVar9 = iVar9 - iVar15) {
                lVar19 = lVar19 + 8;
                uVar14 = 0xffffffffffffffff >> ((ulong)(0x40 - iVar9) & 0x3f);
                iVar15 = iVar9;
                if (0x3f < iVar9) {
                  uVar14 = 0xffffffffffffffff;
                  iVar15 = 0x40;
                }
                if (0x3f < iVar15) {
                  iVar15 = 0x40;
                }
                *(ulong *)(*(long *)(param_1 + 0x18) + lVar19) =
                     uVar14 | *(ulong *)(*(long *)(param_1 + 0x18) + lVar19);
              }
              goto code_r0x0245748c;
            }
          }
          iVar12 = 0;
          do {
            uVar6 = uVar17 + iVar9 + iVar12;
            iVar12 = iVar12 + -1;
          } while ((1L << (uVar6 & 0x3f) & *(ulong *)(lVar18 + (ulong)(uVar6 >> 6) * 8)) == 0);
          iVar3 = (param_2 << 1 | 1U) + uVar17;
          iVar4 = param_2 + 1 + uVar17;
          iVar11 = (((uVar5 - 1) - param_2) - uVar17) - iVar12;
          uVar17 = 0;
          if (iVar3 + iVar12 <= (int)uVar5) {
            iVar11 = 0;
            uVar17 = iVar4 + iVar12;
          }
          iVar15 = iVar11 + param_2 + 1 + iVar15 + iVar12;
          lVar19 = 0;
        } while (iVar15 < (int)uVar5);
      }
      goto code_r0x024574b8;
    }
  }
  lVar19 = 0;
code_r0x024574b8:
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x78) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar16 = (int *)(param_1 + 0x7c);
  if (0x14 < *piVar16) {
    do {
      cVar7 = '\x01';
      bVar8 = (bool)ExclusiveMonitorPass(piVar16,0x10);
      if (bVar8) {
        *piVar16 = *piVar16 + -1;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
    uVar14 = Aska::Semaphore::IsReady() const(param_1 + 0xb8);
    if ((uVar14 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xb8);
    }
  }
  return lVar19;
}

// ==== Aska::TPoolFast<unsigned char [90], true>::Sink(unsigned char (*) [90], int)
// vaddr 0x2357514 | ghidra 0x2457514 | size 536 | symbol _ZN4Aska9TPoolFastIA90_hLb1EE4SinkEPS1_i | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska9TPoolFastIA90_hLb1EE4SinkEPS1_i(long param_1,long param_2,int param_3)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  
  piVar7 = (int *)(param_1 + 0x78);
  iVar6 = 0;
  do {
    while (*piVar7 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar4) {
        *piVar7 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x02457600;
    }
    ClearExclusiveLocal();
    bVar4 = iVar6 < 0x1ff;
    iVar6 = iVar6 + 1;
  } while (bVar4);
  piVar1 = (int *)(param_1 + 0x7c);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar7 != -1) {
      ClearExclusiveLocal();
      do {
        uVar10 = Aska::Semaphore::IsReady() const(param_1 + 0xb8);
        if ((uVar10 & 1) == 0) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0xb8);
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (*piVar7 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
          if (bVar4) {
            *piVar7 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x024575f0;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
    if (bVar4) {
      *piVar7 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x024575f0:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x02457600:
  DataMemoryBarrier(2,3);
  iVar8 = (int)((ulong)(param_2 - *(long *)(param_1 + 0x30)) >> 1) * -0x5b05b05b;
  iVar6 = iVar8 + 0x3f;
  if (-1 < iVar8) {
    iVar6 = iVar8;
  }
  if (param_3 != 0) {
    uVar2 = iVar6 >> 6;
    uVar11 = -(ulong)(uVar2 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar2 << 3;
    uVar10 = 0xffffffffffffffff >> ((ulong)(0x40 - param_3) & 0x3f);
    uVar5 = iVar8 + uVar2 * -0x40;
    if (0x3f < param_3) {
      uVar10 = 0xffffffffffffffff;
    }
    iVar6 = 0;
    if (param_3 < 0x40) {
      iVar6 = param_3;
    }
    iVar8 = 0x40 - uVar5;
    if (iVar6 <= iVar8) {
      iVar8 = iVar6;
    }
    iVar8 = param_3 - iVar8;
    *(ulong *)(*(long *)(param_1 + 0x18) + uVar11) =
         *(ulong *)(*(long *)(param_1 + 0x18) + uVar11) &
         (uVar10 << ((ulong)uVar5 & 0x3f) ^ 0xffffffffffffffff);
    if (iVar8 != 0) {
      lVar9 = (long)(int)uVar2 * 8;
      do {
        lVar9 = lVar9 + 8;
        iVar6 = 0x40;
        if (iVar8 < 0x40) {
          iVar6 = iVar8;
        }
        uVar10 = 0;
        if (iVar8 < 0x40) {
          uVar10 = ~(0xffffffffffffffffU >> ((ulong)(0x40 - iVar8) & 0x3f));
        }
        if (0x3f < iVar6) {
          iVar6 = 0x40;
        }
        iVar8 = iVar8 - iVar6;
        *(ulong *)(*(long *)(param_1 + 0x18) + lVar9) =
             uVar10 & *(ulong *)(*(long *)(param_1 + 0x18) + lVar9);
      } while (iVar8 != 0);
    }
  }
  *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) - param_3;
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0x78) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar7 = (int *)(param_1 + 0x7c);
  if (0x14 < *piVar7) {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar4) {
        *piVar7 = *piVar7 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    uVar10 = Aska::Semaphore::IsReady() const(param_1 + 0xb8);
    if ((uVar10 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0xb8);
    }
  }
  return 1;
}

// ==== Aska::TPoolAtomic<Aska::Yayoi::NativeHttpClient, 32>::TPoolAtomic()
// vaddr 0x259e42c | ghidra 0x269e42c | size 332 | symbol _ZN4Aska11TPoolAtomicINS_5Yayoi16NativeHttpClientELi32EEC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TPoolAtomicINS_5Yayoi16NativeHttpClientELi32EEC2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska11TPoolAtomicINS_5Yayoi16NativeHttpClientELi32EEE_02cb93c8 + 0x10)
  ;
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 2);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 9);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x10);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x17);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x1e);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x25);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x2c);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x33);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x3a);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x41);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x48);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x4f);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x56);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x5d);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 100);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x6b);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x72);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x79);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x80);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x87);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x8e);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x95);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0x9c);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0xa3);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0xaa);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0xb1);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0xb8);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0xbf);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0xc6);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0xcd);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0xd4);
  Aska::Yayoi::NativeHttpClient::NativeHttpClient()(param_1 + 0xdb);
  *(undefined4 *)(param_1 + 0xe2) = 0;
  *(undefined4 *)((long)param_1 + 0x714) = 0;
  *(undefined4 *)(param_1 + 1) = 0;
  *(undefined4 *)((long)param_1 + 0xc) = 0;
  *(undefined1 *)(param_1 + 0xe3) = 1;
  return;
}
