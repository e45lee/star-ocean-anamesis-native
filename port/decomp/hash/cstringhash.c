// port/decomp/hash/cstringhash.c: Ghidra decompiles for the hash subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:07 UTC: tools/decomp.sh '--into' 'hash/cstringhash' 'Framework::CStringHash::'

// ==== Framework::CStringHash::CStringHash()
// vaddr 0x1e9b63c | ghidra 0x1f9b63c | size 20 | symbol _ZN9Framework11CStringHashC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CStringHashC1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework11CStringHashE_02cc1820 + 0x10);
  param_1[1] = 0;
  return;
}

// ==== Framework::CStringHash::~CStringHash()
// vaddr 0x1e9b650 | ghidra 0x1f9b650 | size 56 | symbol _ZN9Framework11CStringHashD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CStringHashD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework11CStringHashE_02cc1820 + 0x10);
  if ((long *)param_1[1] != (long *)0x0) {
    (**(code **)(*(long *)param_1[1] + 8))();
    param_1[1] = 0;
  }
  return;
}

// ==== Framework::CStringHash::Release()
// vaddr 0x1e9b688 | ghidra 0x1f9b688 | size 40 | symbol _ZN9Framework11CStringHash7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CStringHash7ReleaseEv(long param_1)

{
  if (*(long **)(param_1 + 8) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 8) + 8))();
    *(undefined8 *)(param_1 + 8) = 0;
  }
  return;
}

// ==== Framework::CStringHash::~CStringHash()
// vaddr 0x1e9b6b0 | ghidra 0x1f9b6b0 | size 56 | symbol _ZN9Framework11CStringHashD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CStringHashD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework11CStringHashE_02cc1820 + 0x10);
  if ((long *)param_1[1] != (long *)0x0) {
    (**(code **)(*(long *)param_1[1] + 8))();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CStringHash::IsInitialized() const
// vaddr 0x1e9b6e8 | ghidra 0x1f9b6e8 | size 16 | symbol _ZNK9Framework11CStringHash13IsInitializedEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework11CStringHash13IsInitializedEv(long param_1)

{
  return *(long *)(param_1 + 8) != 0;
}

// ==== Framework::CStringHash::Initialize(unsigned int, unsigned int)
// vaddr 0x1e9b6f8 | ghidra 0x1f9b6f8 | size 312 | symbol _ZN9Framework11CStringHash10InitializeEjj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CStringHash10InitializeEjj(long param_1,undefined4 param_2,uint param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  long *plVar3;
  long *plVar4;
  
  if (*(long *)(param_1 + 8) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x29,&UNK_029661c2/*"m_pSubstance isn't null.(%08x)"*/);
  }
  plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x98,PTR__ZSt7nothrow_02cb9a80);
  if (plVar3 != (long *)0x0) {
    *(undefined4 *)(plVar3 + 1) = 0;
    puVar2 = PTR__ZTVN4Aska11TPoolLegacyIN9Framework11CStringHash8tElementELb0EEE_02cbd4e0;
    *(undefined4 *)(plVar3 + 3) = 0;
    puVar1 = PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10;
    *(undefined1 *)(plVar3 + 6) = 0;
    plVar3[4] = 0;
    plVar3[5] = 0;
    *plVar3 = (long)(puVar2 + 0x10);
    plVar3[2] = (long)puVar1;
    plVar3[8] = 0;
    Aska::TPoolLegacy<Framework::CStringHash::tElement, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(plVar3,param_2,0,0,0);
    *plVar3 = (long)(PTR__ZTVN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEEE_02cbb0a0 +
                    0x10);
    if (param_3 < 2) {
      param_3 = 1;
      plVar4 = plVar3 + 0xd;
    }
    else {
      plVar4 = (long *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_3 << 3,PTR__ZSt7nothrow_02cb9a80);
      if (plVar4 == (long *)0x0) {
        param_3 = 1;
        plVar4 = plVar3 + 0xd;
      }
    }
    memset(plVar4,0,(ulong)param_3 << 3);
    *(uint *)(plVar3 + 0xb) = param_3;
    plVar3[10] = (long)plVar4;
    plVar3[0xc] = (long)plVar4;
    *(undefined4 *)((long)plVar3 + 0x8c) = 0;
    plVar3[0xf] = 0;
    plVar3[0x10] = 0;
    *(undefined1 *)(plVar3 + 0x11) = 0;
    plVar3[0xe] = 0;
    *plVar3 = (long)(PTR__ZTVN9Framework11CStringHash10CSubstanceE_02cc1b70 + 0x10);
  }
  *(long **)(param_1 + 8) = plVar3;
  return;
}

// ==== Framework::CStringHash::rSubstance()
// vaddr 0x1e9b830 | ghidra 0x1f9b830 | size 60 | symbol _ZN9Framework11CStringHash10rSubstanceEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework11CStringHash10rSubstanceEv(long param_1)

{
  if (*(long *)(param_1 + 8) != 0) {
    return *(long *)(param_1 + 8);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x35,&UNK_027e7586/*"m_pSubstance is null."*/);
  return *(long *)(param_1 + 8);
}

// ==== Framework::CStringHash::Register(char const*, unsigned int)
// vaddr 0x1e9b86c | ghidra 0x1f9b86c | size 76 | symbol _ZN9Framework11CStringHash8RegisterEPKcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CStringHash8RegisterEPKcj(long param_1,undefined8 param_2,undefined4 param_3)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x3b,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar1 = *(long *)(param_1 + 8);
  }
  (*(code *)PTR__ZN9Framework11CStringHash10CSubstance8RegisterEPKcj_02c8fdf0)
            (lVar1,param_2,param_3);
  return;
}

// ==== Framework::CStringHash::CSubstance::Register(char const*, unsigned int)
// vaddr 0x1e9b8b8 | ghidra 0x1f9b8b8 | size 416 | symbol _ZN9Framework11CStringHash10CSubstance8RegisterEPKcj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN9Framework11CStringHash10CSubstance8RegisterEPKcj(long *param_1,long param_2,undefined4 param_3)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  long lVar4;
  long *plVar5;
  ulong uVar6;
  code *pcVar7;
  ulong uVar8;
  ulong *puVar9;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0xb2,&UNK_02966202/*"apString is null."*/);
  }
  pcVar7 = *(code **)(*param_1 + 0x80);
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1,param_2);
  lVar4 = (*pcVar7)(param_1,param_2,uVar1);
  if (lVar4 != 0) {
    return 0;
  }
  uVar2 = (**(code **)(*param_1 + 0x60))(param_1,param_2);
  uVar8 = (ulong)uVar2;
  if (*(uint *)(param_1 + 0xb) <= uVar2) {
    uVar8 = 0;
  }
  puVar9 = (ulong *)(param_1[10] + uVar8 * 8);
  param_1[0xc] = (long)puVar9;
  plVar5 = (long *)*puVar9;
  while (plVar5 != (long *)0x0) {
    while (iVar3 = (**(code **)(*plVar5 + 0x20))(plVar5,param_2), iVar3 < 0) {
      puVar9 = (ulong *)(*puVar9 + 0x18);
      plVar5 = (long *)*puVar9;
      if (plVar5 == (long *)0x0) goto code_r0x01f9b99c;
    }
    if (iVar3 == 0) goto code_r0x01f9b9b8;
    puVar9 = (ulong *)(*puVar9 + 0x20);
    plVar5 = (long *)*puVar9;
  }
code_r0x01f9b99c:
  uVar8 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *puVar9 = uVar8;
  if (uVar8 != 0) {
code_r0x01f9b9b8:
    if ((puVar9 != (ulong *)0x0) && (uVar8 = *puVar9, uVar8 != 0)) goto code_r0x01f9b9e0;
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0xbd,&UNK_02966214/*"Register failed."*/);
  uVar8 = 0;
code_r0x01f9b9e0:
  uVar6 = param_1[8];
  if ((((uVar6 == 0) || (uVar8 < uVar6)) ||
      (uVar6 + (ulong)*(uint *)((long)param_1 + 0x2c) * 0x40 <= uVar8)) ||
     ((*(uint *)(param_1[4] + (uVar8 - uVar6 >> 0xb & 0x7ffffff) * 4) &
      1 << (ulong)((uint)(uVar8 - uVar6) >> 6 & 0x1f)) == 0)) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0xbf,&UNK_029661e1/*"Pool memory full."*/);
  }
  *(long *)(uVar8 + 0x30) = param_2;
  *(undefined4 *)(uVar8 + 0x38) = param_3;
  *(uint *)(uVar8 + 0x3c) = uVar2;
  return 1;
}

// ==== Framework::CStringHash::IsRegistered(char const*) const
// vaddr 0x1e9ba58 | ghidra 0x1f9ba58 | size 128 | symbol _ZNK9Framework11CStringHash12IsRegisteredEPKc | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework11CStringHash12IsRegisteredEPKc(long param_1,long param_2)

{
  long lVar1;
  long *plVar2;
  
  plVar2 = *(long **)(param_1 + 8);
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x41,&UNK_027e7586/*"m_pSubstance is null."*/);
    plVar2 = *(long **)(param_1 + 8);
  }
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0xcc,&UNK_02966202/*"apString is null."*/);
  }
  lVar1 = (**(code **)(*plVar2 + 0x58))(plVar2,param_2);
  return lVar1 != 0;
}

// ==== Framework::CStringHash::CSubstance::IsRegistered(char const*) const
// vaddr 0x1e9bad8 | ghidra 0x1f9bad8 | size 84 | symbol _ZNK9Framework11CStringHash10CSubstance12IsRegisteredEPKc | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework11CStringHash10CSubstance12IsRegisteredEPKc(long *param_1,long param_2)

{
  long lVar1;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0xcc,&UNK_02966202/*"apString is null."*/);
  }
  lVar1 = (**(code **)(*param_1 + 0x58))(param_1,param_2);
  return lVar1 != 0;
}

// ==== Framework::CStringHash::Remove(char const*)
// vaddr 0x1e9bb2c | ghidra 0x1f9bb2c | size 152 | symbol _ZN9Framework11CStringHash6RemoveEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CStringHash6RemoveEPKc(long param_1,long param_2)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  long *plVar2;
  
  plVar2 = *(long **)(param_1 + 8);
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x47,&UNK_027e7586/*"m_pSubstance is null."*/);
    plVar2 = *(long **)(param_1 + 8);
  }
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0xd3,&UNK_02966202/*"apString is null."*/);
  }
  UNRECOVERED_JUMPTABLE = *(code **)(*plVar2 + 0x70);
  uVar1 = (**(code **)(*plVar2 + 0x60))(plVar2,param_2);
                    /* WARNING: Could not recover jumptable at 0x01f9bb84. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(plVar2,param_2,uVar1);
  return;
}

// ==== Framework::CStringHash::CSubstance::Remove(char const*)
// vaddr 0x1e9bbc4 | ghidra 0x1f9bbc4 | size 100 | symbol _ZN9Framework11CStringHash10CSubstance6RemoveEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CStringHash10CSubstance6RemoveEPKc(long *param_1,long param_2)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0xd3,&UNK_02966202/*"apString is null."*/);
  }
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x70);
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1,param_2);
                    /* WARNING: Could not recover jumptable at 0x01f9bc24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,uVar1);
  return;
}

// ==== Framework::CStringHash::Value(char const*) const
// vaddr 0x1e9bc28 | ghidra 0x1f9bc28 | size 256 | symbol _ZNK9Framework11CStringHash5ValueEPKc | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZNK9Framework11CStringHash5ValueEPKc(long param_1,long param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  ulong *puVar7;
  undefined1 auVar8 [16];
  
  plVar6 = *(long **)(param_1 + 8);
  if (plVar6 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x4d,&UNK_027e7586/*"m_pSubstance is null."*/);
    plVar6 = *(long **)(param_1 + 8);
  }
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0xd9,&UNK_02966202/*"apString is null."*/);
  }
  uVar1 = (**(code **)(*plVar6 + 0x60))(plVar6,param_2);
  uVar5 = (ulong)uVar1;
  if (*(uint *)(plVar6 + 0xb) <= uVar1) {
    uVar5 = 0;
  }
  plVar6 = (long *)(plVar6[10] + uVar5 * 8);
  plVar3 = (long *)*plVar6;
  while (plVar3 != (long *)0x0) {
    while (iVar2 = (**(code **)(*plVar3 + 0x20))(plVar3,param_2), -1 < iVar2) {
      if (iVar2 == 0) {
        if (*plVar6 != 0) {
          return (ulong)*(uint *)(*plVar6 + 0x38);
        }
        goto code_r0x01f9bd10;
      }
      plVar6 = (long *)(*plVar6 + 0x20);
      plVar3 = (long *)*plVar6;
      if (plVar3 == (long *)0x0) goto code_r0x01f9bd10;
    }
    plVar6 = (long *)(*plVar6 + 0x18);
    plVar3 = (long *)*plVar6;
  }
code_r0x01f9bd10:
  auVar8 = Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x4f,&UNK_0285eab8/*"pElement is null."*/);
  lVar4 = auVar8._8_8_;
  plVar6 = auVar8._0_8_;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0xd9,&UNK_02966202/*"apString is null."*/);
  }
  uVar1 = (**(code **)(*plVar6 + 0x60))(plVar6,lVar4);
  uVar5 = (ulong)uVar1;
  if (*(uint *)(plVar6 + 0xb) <= uVar1) {
    uVar5 = 0;
  }
  puVar7 = (ulong *)(plVar6[10] + uVar5 * 8);
  plVar6 = (long *)*puVar7;
  while( true ) {
    if (plVar6 == (long *)0x0) {
      return 0;
    }
    while (iVar2 = (**(code **)(*plVar6 + 0x20))(plVar6,lVar4), iVar2 < 0) {
      puVar7 = (ulong *)(*puVar7 + 0x18);
      plVar6 = (long *)*puVar7;
      if (plVar6 == (long *)0x0) {
        return 0;
      }
    }
    if (iVar2 == 0) break;
    puVar7 = (ulong *)(*puVar7 + 0x20);
    plVar6 = (long *)*puVar7;
  }
  return *puVar7;
}

// ==== Framework::CStringHash::CSubstance::pSearch(char const*)
// vaddr 0x1e9bd28 | ghidra 0x1f9bd28 | size 180 | symbol _ZN9Framework11CStringHash10CSubstance7pSearchEPKc | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework11CStringHash10CSubstance7pSearchEPKc(long *param_1,long param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0xd9,&UNK_02966202/*"apString is null."*/);
  }
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1,param_2);
  uVar4 = (ulong)uVar1;
  if (*(uint *)(param_1 + 0xb) <= uVar1) {
    uVar4 = 0;
  }
  plVar5 = (long *)(param_1[10] + uVar4 * 8);
  plVar3 = (long *)*plVar5;
  do {
    if (plVar3 == (long *)0x0) {
      return 0;
    }
    while (iVar2 = (**(code **)(*plVar3 + 0x20))(plVar3,param_2), -1 < iVar2) {
      if (iVar2 == 0) {
        return *plVar5;
      }
      plVar5 = (long *)(*plVar5 + 0x20);
      plVar3 = (long *)*plVar5;
      if (plVar3 == (long *)0x0) {
        return 0;
      }
    }
    plVar5 = (long *)(*plVar5 + 0x18);
    plVar3 = (long *)*plVar5;
  } while( true );
}

// ==== Framework::CStringHash::ValueSafe(char const*, unsigned int&) const
// vaddr 0x1e9bddc | ghidra 0x1f9bddc | size 260 | symbol _ZNK9Framework11CStringHash9ValueSafeEPKcRj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK9Framework11CStringHash9ValueSafeEPKcRj(long param_1,long param_2,undefined4 *param_3)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  plVar5 = *(long **)(param_1 + 8);
  if (plVar5 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x58,&UNK_027e7586/*"m_pSubstance is null."*/);
    plVar5 = *(long **)(param_1 + 8);
  }
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0xd9,&UNK_02966202/*"apString is null."*/);
  }
  uVar1 = (**(code **)(*plVar5 + 0x60))(plVar5,param_2);
  uVar4 = (ulong)uVar1;
  if (*(uint *)(plVar5 + 0xb) <= uVar1) {
    uVar4 = 0;
  }
  plVar5 = (long *)(plVar5[10] + uVar4 * 8);
  plVar3 = (long *)*plVar5;
  do {
    if (plVar3 == (long *)0x0) {
      return 0;
    }
    while (iVar2 = (**(code **)(*plVar3 + 0x20))(plVar3,param_2), -1 < iVar2) {
      if (iVar2 == 0) {
        if (*plVar5 != 0) {
          *param_3 = *(undefined4 *)(*plVar5 + 0x38);
          return 1;
        }
        return 0;
      }
      plVar5 = (long *)(*plVar5 + 0x20);
      plVar3 = (long *)*plVar5;
      if (plVar3 == (long *)0x0) {
        return 0;
      }
    }
    plVar5 = (long *)(*plVar5 + 0x18);
    plVar3 = (long *)*plVar5;
  } while( true );
}

// ==== Framework::CStringHash::GetRegistCount() const
// vaddr 0x1e9bee0 | ghidra 0x1f9bee0 | size 12 | symbol _ZNK9Framework11CStringHash14GetRegistCountEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework11CStringHash14GetRegistCountEv(long param_1)

{
  return *(undefined4 *)(*(long *)(param_1 + 8) + 0x8c);
}

// ==== Framework::CStringHash::SetDebugTag(char const*)
// vaddr 0x1e9beec | ghidra 0x1f9beec | size 36 | symbol _ZN9Framework11CStringHash11SetDebugTagEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CStringHash11SetDebugTagEPKc(long param_1)

{
  if (*(long *)(param_1 + 8) != 0) {
    return;
  }
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x6e,&UNK_027e7586/*"m_pSubstance is null."*/);
  return;
}

// ==== Framework::CStringHash::SetDebugTag(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1e9bf10 | ghidra 0x1f9bf10 | size 36 | symbol _ZN9Framework11CStringHash11SetDebugTagERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CStringHash11SetDebugTagERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE
               (long param_1)

{
  if (*(long *)(param_1 + 8) != 0) {
    return;
  }
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x75,&UNK_027e7586/*"m_pSubstance is null."*/);
  return;
}

// ==== Framework::CStringHash::GetDebugTag() const
// vaddr 0x1e9bf34 | ghidra 0x1f9bf34 | size 56 | symbol _ZNK9Framework11CStringHash11GetDebugTagEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework11CStringHash11GetDebugTagEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x7c,&UNK_027e7586/*"m_pSubstance is null."*/);
    lVar1 = *(long *)(param_1 + 8);
  }
  return lVar1 + 0x90;
}

// ==== Framework::CStringHash::CSubstance::CSubstance(unsigned int, unsigned int)
// vaddr 0x1e9bf6c | ghidra 0x1f9bf6c | size 236 | symbol _ZN9Framework11CStringHash10CSubstanceC1Ejj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CStringHash10CSubstanceC2Ejj(long *param_1,uint param_2,undefined4 param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  long *plVar3;
  
  *(undefined4 *)(param_1 + 1) = 0;
  puVar2 = PTR__ZTVN4Aska11TPoolLegacyIN9Framework11CStringHash8tElementELb0EEE_02cbd4e0;
  *(undefined4 *)(param_1 + 3) = 0;
  puVar1 = PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10;
  *(undefined1 *)(param_1 + 6) = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  *param_1 = (long)(puVar2 + 0x10);
  param_1[2] = (long)puVar1;
  param_1[8] = 0;
  Aska::TPoolLegacy<Framework::CStringHash::tElement, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)(param_1,param_3,0,0,0);
  *param_1 = (long)(PTR__ZTVN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEEE_02cbb0a0 + 0x10
                   );
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
  *param_1 = (long)(PTR__ZTVN9Framework11CStringHash10CSubstanceE_02cc1b70 + 0x10);
  return;
}

// ==== Framework::CStringHash::CSubstance::AllocNode(void const*)
// vaddr 0x1e9c058 | ghidra 0x1f9c058 | size 128 | symbol _ZN9Framework11CStringHash10CSubstance9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN9Framework11CStringHash10CSubstance9AllocNodeEPKv(long param_1)

{
  ulong uVar1;
  ulong uVar2;
  
  uVar1 = Aska::TBinaryTree<Framework::CStringHash::tElement>::AllocNode(void const*)();
  uVar2 = *(ulong *)(param_1 + 0x40);
  if ((((uVar2 != 0) && (uVar2 <= uVar1)) &&
      (uVar1 < uVar2 + (ulong)*(uint *)(param_1 + 0x2c) * 0x40)) &&
     ((*(uint *)(*(long *)(param_1 + 0x20) + (uVar1 - uVar2 >> 0xb & 0x7ffffff) * 4) &
      1 << (ulong)((uint)(uVar1 - uVar2) >> 6 & 0x1f)) != 0)) {
    return uVar1;
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x90,&UNK_029661e1/*"Pool memory full."*/);
  return uVar1;
}

// ==== Aska::TBinaryTree<Framework::CStringHash::tElement>::AllocNode(void const*)
// vaddr 0x1e9c0d8 | ghidra 0x1f9c0d8 | size 360 | symbol _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE9AllocNodeEPKv
                 (long param_1,undefined8 param_2)

{
  undefined *puVar1;
  ulong uVar2;
  uint uVar3;
  uint uVar4;
  long *plVar5;
  long lVar6;
  uint uVar7;
  long lVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar6 = *(long *)(param_1 + 0x20);
    uVar4 = *(uint *)(param_1 + 0x38);
    do {
      uVar7 = uVar4;
      if (*(uint *)(param_1 + 0x2c) <= uVar7) {
        uVar7 = 0;
      }
      uVar3 = 1 << (ulong)(uVar7 & 0x1f);
      uVar4 = uVar7 + 1;
    } while ((uVar3 & *(uint *)(lVar6 + (ulong)(uVar7 >> 5) * 4)) != 0);
    uVar2 = *(long *)(param_1 + 0x40) + (ulong)uVar7 * 0x40;
    uVar10 = uVar2;
    do {
      uVar11 = uVar10 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar10,0,2,0);
      uVar10 = uVar11;
    } while (uVar11 < uVar2 + 0x40);
    lVar9 = (ulong)(uVar7 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar7 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    lVar8 = (ulong)uVar7 * 0x40;
    *(uint *)(lVar6 + lVar9) = *(uint *)(lVar6 + lVar9) | uVar3;
    plVar5 = (long *)(*(long *)(param_1 + 0x40) + lVar8);
    puVar1 = PTR__ZTVN9Framework11CStringHash8tElementE_02cc09a0 + 0x10;
    plVar5[4] = 0;
    plVar5[3] = 0;
    plVar5[2] = 0;
    plVar5[1] = 0;
    *plVar5 = (long)puVar1;
    plVar5 = (long *)(*(long *)(param_1 + 0x40) + lVar8);
    if (plVar5 == (long *)0x0) goto code_r0x01f9c19c;
  }
  else {
code_r0x01f9c19c:
    plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x40,PTR__ZSt7nothrow_02cb9a80);
    puVar1 = PTR__ZTVN9Framework11CStringHash8tElementE_02cc09a0;
    if (plVar5 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar5[4] = 0;
    plVar5[3] = 0;
    plVar5[2] = 0;
    plVar5[1] = 0;
    *plVar5 = (long)(puVar1 + 0x10);
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar5;
    lVar6 = *(long *)(param_1 + 0x78);
    if (lVar6 == 0) {
      lVar8 = 0;
      goto code_r0x01f9c1f4;
    }
  }
  else {
    lVar6 = *(long *)(param_1 + 0x78);
    lVar8 = 0;
    if (lVar6 == 0) goto code_r0x01f9c1f4;
  }
  *(long **)(lVar6 + 0x10) = plVar5;
  lVar8 = *(long *)(param_1 + 0x78);
code_r0x01f9c1f4:
  plVar5[1] = lVar8;
  plVar5[2] = 0;
  *(long **)(param_1 + 0x78) = plVar5;
  (**(code **)(*plVar5 + 0x28))(plVar5,param_2);
  (**(code **)(*plVar5 + 0x10))(plVar5);
  return plVar5;
}

// ==== Framework::CStringHash::CSubstance::CalcHashValue(void const*) const
// vaddr 0x1e9c240 | ghidra 0x1f9c240 | size 108 | symbol _ZNK9Framework11CStringHash10CSubstance13CalcHashValueEPKv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK9Framework11CStringHash10CSubstance13CalcHashValueEPKv(long param_1,long param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined1 auStack_30 [16];
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x96,&UNK_029661f3/*"apKey is null."*/);
  }
  Framework::CHash32::CHash32(char const*)(auStack_30,param_2);
  uVar3 = Framework::CHash32::Get() const(auStack_30);
  Framework::CHash32::~CHash32()(auStack_30);
  uVar1 = *(uint *)(param_1 + 0x58);
  uVar2 = 0;
  if (uVar1 != 0) {
    uVar2 = uVar3 / uVar1;
  }
  return uVar3 - uVar2 * uVar1;
}

// ==== Aska::THash<Framework::CStringHash::tElement>::Search(void const*)
// vaddr 0x1e9c2ac | ghidra 0x1f9c2ac | size 68 | symbol _ZN4Aska5THashIN9Framework11CStringHash8tElementEE6SearchEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashIN9Framework11CStringHash8tElementEE6SearchEPKv(long *param_1,undefined8 param_2)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x80);
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1);
                    /* WARNING: Could not recover jumptable at 0x01f9c2ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,uVar1);
  return;
}

// ==== Aska::THash<Framework::CStringHash::tElement>::Regist(void const*, unsigned int)
// vaddr 0x1e9c2f0 | ghidra 0x1f9c2f0 | size 168 | symbol _ZN4Aska5THashIN9Framework11CStringHash8tElementEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5THashIN9Framework11CStringHash8tElementEE6RegistEPKvj
               (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  
  uVar5 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar5 = 0;
  }
  plVar6 = (long *)(param_1[10] + uVar5 * 8);
  param_1[0xc] = (long)plVar6;
  plVar2 = (long *)*plVar6;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x01f9c37c;
      plVar6 = (long *)(*plVar6 + 0x20);
      plVar2 = (long *)*plVar6;
      if (plVar2 == (long *)0x0) goto code_r0x01f9c360;
    }
    plVar6 = (long *)(*plVar6 + 0x18);
    plVar2 = (long *)*plVar6;
  }
code_r0x01f9c360:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar6 = lVar3;
  lVar4 = 0;
  if (lVar3 != 0) {
code_r0x01f9c37c:
    if (plVar6 == (long *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar6;
    }
  }
  return lVar4;
}

// ==== Aska::THash<Framework::CStringHash::tElement>::Remove(void const*)
// vaddr 0x1e9c398 | ghidra 0x1f9c398 | size 68 | symbol _ZN4Aska5THashIN9Framework11CStringHash8tElementEE6RemoveEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashIN9Framework11CStringHash8tElementEE6RemoveEPKv(long *param_1,undefined8 param_2)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x70);
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1);
                    /* WARNING: Could not recover jumptable at 0x01f9c3d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,uVar1);
  return;
}

// ==== Aska::THash<Framework::CStringHash::tElement>::Search(void const*, unsigned int)
// vaddr 0x1e9c3dc | ghidra 0x1f9c3dc | size 124 | symbol _ZN4Aska5THashIN9Framework11CStringHash8tElementEE6SearchEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5THashIN9Framework11CStringHash8tElementEE6SearchEPKvj
               (long param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0x58) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(*(long *)(param_1 + 0x50) + uVar3 * 8);
  plVar2 = (long *)*plVar4;
  do {
    if (plVar2 == (long *)0x0) {
      return 0;
    }
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return *plVar4;
      }
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) {
        return 0;
      }
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  } while( true );
}

// ==== Framework::CStringHash::CSubstance::pSearch(char const*) const
// vaddr 0x1e9c458 | ghidra 0x1f9c458 | size 96 | symbol _ZNK9Framework11CStringHash10CSubstance7pSearchEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework11CStringHash10CSubstance7pSearchEPKc(long *param_1,long param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0xe0,&UNK_02966202/*"apString is null."*/);
  }
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1,param_2);
                    /* WARNING: Could not recover jumptable at 0x01f9c4b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x80))(param_1,param_2,uVar1);
  return;
}

// ==== Framework::CStringHash::gRegressionTest()
// vaddr 0x1e9c4b8 | ghidra 0x1f9c4b8 | size 480 | symbol _ZN9Framework11CStringHash15gRegressionTestEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CStringHash15gRegressionTestEv(void)

{
  undefined *puVar1;
  long *plVar2;
  undefined4 uVar3;
  code *pcVar4;
  undefined *puStack_40;
  long *plStack_38;
  
  puVar1 = PTR__ZTVN9Framework11CStringHashE_02cc1820;
  puStack_40 = PTR__ZTVN9Framework11CStringHashE_02cc1820 + 0x10;
  plStack_38 = (long *)0x0;
  Framework::CStringHash::Initialize(unsigned int, unsigned int)(&puStack_40,5,0x11);
  plVar2 = plStack_38;
  if (plStack_38 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x3b,&UNK_027e7586/*"m_pSubstance is null."*/);
    Framework::CStringHash::CSubstance::Register(char const*, unsigned int)(0,&UNK_02966225/*"Test1"*/,0x7b);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x3b,&UNK_027e7586/*"m_pSubstance is null."*/);
    Framework::CStringHash::CSubstance::Register(char const*, unsigned int)(0,&UNK_0296622b/*"Test2"*/,0x1c8);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x3b,&UNK_027e7586/*"m_pSubstance is null."*/);
    Framework::CStringHash::CSubstance::Register(char const*, unsigned int)(0,&UNK_02966231/*"IFProj"*/,0x315);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x3b,&UNK_027e7586/*"m_pSubstance is null."*/);
    Framework::CStringHash::CSubstance::Register(char const*, unsigned int)(0,&UNK_02966238/*"SADASDA"*/,0x1e240);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x3b,&UNK_027e7586/*"m_pSubstance is null."*/);
    Framework::CStringHash::CSubstance::Register(char const*, unsigned int)(0,&UNK_02966240/*"Test3longlonglonglong_123456789123456789123456789"*/,0x28e);
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296616c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\StringHash.cpp"*/,0x47,&UNK_027e7586/*"m_pSubstance is null."*/);
  }
  else {
    Framework::CStringHash::CSubstance::Register(char const*, unsigned int)(plStack_38,&UNK_02966225/*"Test1"*/,0x7b);
    Framework::CStringHash::CSubstance::Register(char const*, unsigned int)(plVar2,&UNK_0296622b/*"Test2"*/,0x1c8);
    Framework::CStringHash::CSubstance::Register(char const*, unsigned int)(plVar2,&UNK_02966231/*"IFProj"*/,0x315);
    Framework::CStringHash::CSubstance::Register(char const*, unsigned int)(plVar2,&UNK_02966238/*"SADASDA"*/,0x1e240);
    Framework::CStringHash::CSubstance::Register(char const*, unsigned int)(plVar2,&UNK_02966240/*"Test3longlonglonglong_123456789123456789123456789"*/,0x28e);
  }
  pcVar4 = *(code **)(*plVar2 + 0x70);
  uVar3 = (**(code **)(*plVar2 + 0x60))(plVar2,&UNK_02966225/*"Test1"*/);
  (*pcVar4)(plVar2,&UNK_02966225/*"Test1"*/,uVar3);
  puStack_40 = puVar1 + 0x10;
  if (plVar2 != (long *)0x0) {
    (**(code **)(*plVar2 + 8))(plVar2);
  }
  return;
}

// ==== Aska::THash<Framework::CStringHash::tElement>::~THash()
// vaddr 0x1e9c6a0 | ghidra 0x1f9c6a0 | size 40 | symbol _ZN4Aska5THashIN9Framework11CStringHash8tElementEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashIN9Framework11CStringHash8tElementEED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska5THashIN9Framework11CStringHash8tElementEEE_02cb75d8 + 0x10);
  Aska::TBinaryTree<Framework::CStringHash::tElement>::FreeTable()();
  (*(code *)PTR__ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEED2Ev_02cac828)(param_1);
  return;
}

// ==== Framework::CStringHash::CSubstance::~CSubstance()
// vaddr 0x1e9c6c8 | ghidra 0x1f9c6c8 | size 48 | symbol _ZN9Framework11CStringHash10CSubstanceD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CStringHash10CSubstanceD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska5THashIN9Framework11CStringHash8tElementEEE_02cb75d8 + 0x10);
  Aska::TBinaryTree<Framework::CStringHash::tElement>::FreeTable()();
  Aska::TBinaryTree<Framework::CStringHash::tElement>::~TBinaryTree()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TBinaryTree<Framework::CStringHash::tElement>::FreeNode(Framework::CStringHash::tElement**)
// vaddr 0x1e9c6f8 | ghidra 0x1f9c6f8 | size 376 | symbol _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE8FreeNodeEPPS3_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE8FreeNodeEPPS3_
               (long *param_1,ulong *param_2)

{
  long *plVar1;
  ulong uVar2;
  long *plVar3;
  long lVar4;
  
  uVar2 = *param_2;
  if (uVar2 != 0) {
    if (param_1[0xe] == uVar2) {
      param_1[0xe] = *(long *)(uVar2 + 0x10);
      uVar2 = *param_2;
    }
    if (param_1[0xf] == uVar2) {
      param_1[0xf] = *(long *)(uVar2 + 8);
      uVar2 = *param_2;
    }
    if (param_1[0x10] == uVar2) {
      param_1[0x10] = *(long *)(uVar2 + 8);
      uVar2 = *param_2;
    }
    lVar4 = *(long *)(uVar2 + 0x10);
    if (*(long *)(uVar2 + 8) != 0) {
      *(long *)(*(long *)(uVar2 + 8) + 0x10) = lVar4;
    }
    if (lVar4 != 0) {
      *(undefined8 *)(lVar4 + 8) = *(undefined8 *)(*param_2 + 8);
    }
    *(undefined8 *)(*param_2 + 0x10) = 0;
    *(undefined8 *)(*param_2 + 8) = 0;
    plVar1 = (long *)*param_2;
    if (plVar1[4] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar1 = (long *)*param_2;
    }
    if (plVar1[3] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar1 = (long *)*param_2;
    }
    (**(code **)(*plVar1 + 0x18))();
    *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
    plVar3 = (long *)param_1[8];
    plVar1 = (long *)*param_2;
    if (((plVar3 == (long *)0x0) || (plVar1 < plVar3)) ||
       (plVar3 + (ulong)*(uint *)((long)param_1 + 0x2c) * 8 <= plVar1)) {
      if (plVar1 != (long *)0x0) {
        (**(code **)(*plVar1 + 8))();
      }
    }
    else {
      uVar2 = (long)plVar1 - (long)plVar3;
      (**(code **)plVar3[(uVar2 >> 6 & 0xffffffff) * 8])();
      lVar4 = (uVar2 >> 0xb & 0x7ffffff) * 4;
      *(uint *)(param_1[4] + lVar4) =
           *(uint *)(param_1[4] + lVar4) & (1 << (uVar2 >> 6 & 0x1f) ^ 0xffffffffU);
      *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
    }
    *param_2 = 0;
  }
  return;
}

// ==== Aska::THash<Framework::CStringHash::tElement>::RegistEx(void const*)
// vaddr 0x1e9c870 | ghidra 0x1f9c870 | size 176 | symbol _ZN4Aska5THashIN9Framework11CStringHash8tElementEE8RegistExEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska5THashIN9Framework11CStringHash8tElementEE8RegistExEPKv
                 (long *param_1,undefined8 param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  
  uVar1 = (**(code **)(*param_1 + 0x60))();
  uVar5 = (ulong)uVar1;
  if (*(uint *)(param_1 + 0xb) <= uVar1) {
    uVar5 = 0;
  }
  plVar6 = (long *)(param_1[10] + uVar5 * 8);
  param_1[0xc] = (long)plVar6;
  plVar3 = (long *)*plVar6;
  while (plVar3 != (long *)0x0) {
    while (iVar2 = (**(code **)(*plVar3 + 0x20))(plVar3,param_2), iVar2 < 0) {
      plVar6 = (long *)(*plVar6 + 0x18);
      plVar3 = (long *)*plVar6;
      if (plVar3 == (long *)0x0) goto code_r0x01f9c8f0;
    }
    if (iVar2 == 0) {
      return plVar6;
    }
    plVar6 = (long *)(*plVar6 + 0x20);
    plVar3 = (long *)*plVar6;
  }
code_r0x01f9c8f0:
  lVar4 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar6 = lVar4;
  if (lVar4 == 0) {
    plVar6 = (long *)0x0;
  }
  return plVar6;
}

// ==== Aska::THash<Framework::CStringHash::tElement>::Regist(void const*)
// vaddr 0x1e9c920 | ghidra 0x1f9c920 | size 64 | symbol _ZN4Aska5THashIN9Framework11CStringHash8tElementEE6RegistEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashIN9Framework11CStringHash8tElementEE6RegistEPKv(long *param_1,undefined8 param_2)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar1;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x68);
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1);
                    /* WARNING: Could not recover jumptable at 0x01f9c95c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,uVar1);
  return;
}

// ==== Aska::TBinaryTree<Framework::CStringHash::tElement>::Register(void const*)
// vaddr 0x1e9c960 | ghidra 0x1f9c960 | size 12 | symbol _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE8RegisterEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE8RegisterEPKv(long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x01f9c968. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x28))();
  return;
}

// ==== Aska::THash<Framework::CStringHash::tElement>::Remove(Framework::CStringHash::tElement**)
// vaddr 0x1e9c96c | ghidra 0x1f9c96c | size 140 | symbol _ZN4Aska5THashIN9Framework11CStringHash8tElementEE6RemoveEPPS3_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashIN9Framework11CStringHash8tElementEE6RemoveEPPS3_(long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  long lStack_8;
  
  lStack_8 = *param_2;
  if (lStack_8 != 0) {
    plVar2 = (long *)(lStack_8 + 0x20);
    plVar3 = (long *)(lStack_8 + 0x18);
    if (*plVar2 == 0) {
      *param_2 = *plVar3;
      plVar2 = plVar3;
    }
    else {
      plVar1 = plVar3;
      if (*plVar3 == 0) {
        *param_2 = *plVar2;
      }
      else {
        do {
          plVar5 = plVar1;
          lVar4 = *plVar5;
          plVar1 = (long *)(lVar4 + 0x20);
        } while (*(long *)(lVar4 + 0x20) != 0);
        *plVar5 = *(long *)(lVar4 + 0x18);
        *(long *)(lVar4 + 0x18) = *plVar3;
        *(long *)(lVar4 + 0x20) = *plVar2;
        *param_2 = lVar4;
        *plVar3 = 0;
      }
    }
    *plVar2 = 0;
    (**(code **)(*param_1 + 0x18))(param_1,&lStack_8);
  }
  return;
}

// ==== Aska::THash<Framework::CStringHash::tElement>::IsRegisted(void const*)
// vaddr 0x1e9c9f8 | ghidra 0x1f9c9f8 | size 68 | symbol _ZN4Aska5THashIN9Framework11CStringHash8tElementEE10IsRegistedEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashIN9Framework11CStringHash8tElementEE10IsRegistedEPKv
               (long *param_1,undefined8 param_2)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x78);
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1);
                    /* WARNING: Could not recover jumptable at 0x01f9ca38. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,uVar1);
  return;
}

// ==== Aska::TBinaryTree<Framework::CStringHash::tElement>::IsRegistered(void const*)
// vaddr 0x1e9ca3c | ghidra 0x1f9ca3c | size 112 | symbol _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE12IsRegisteredEPKv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE12IsRegisteredEPKv
               (long param_1,undefined8 param_2)

{
  int iVar1;
  long *plVar2;
  long *plVar3;
  
  plVar3 = *(long **)(param_1 + 0x60);
  plVar2 = (long *)*plVar3;
  do {
    if (plVar2 == (long *)0x0) {
      return false;
    }
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return *plVar3 != 0;
      }
      plVar3 = (long *)(*plVar3 + 0x20);
      plVar2 = (long *)*plVar3;
      if (plVar2 == (long *)0x0) {
        return false;
      }
    }
    plVar3 = (long *)(*plVar3 + 0x18);
    plVar2 = (long *)*plVar3;
  } while( true );
}

// ==== Framework::CStringHash::CSubstance::Regist(void const*, unsigned int)
// vaddr 0x1e9caac | ghidra 0x1f9caac | size 168 | symbol _ZN9Framework11CStringHash10CSubstance6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework11CStringHash10CSubstance6RegistEPKvj
               (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  
  uVar5 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar5 = 0;
  }
  plVar6 = (long *)(param_1[10] + uVar5 * 8);
  param_1[0xc] = (long)plVar6;
  plVar2 = (long *)*plVar6;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x01f9cb38;
      plVar6 = (long *)(*plVar6 + 0x20);
      plVar2 = (long *)*plVar6;
      if (plVar2 == (long *)0x0) goto code_r0x01f9cb1c;
    }
    plVar6 = (long *)(*plVar6 + 0x18);
    plVar2 = (long *)*plVar6;
  }
code_r0x01f9cb1c:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar6 = lVar3;
  lVar4 = 0;
  if (lVar3 != 0) {
code_r0x01f9cb38:
    if (plVar6 == (long *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar6;
    }
  }
  return lVar4;
}

// ==== Aska::THash<Framework::CStringHash::tElement>::Remove(void const*, unsigned int)
// vaddr 0x1e9cb54 | ghidra 0x1f9cb54 | size 140 | symbol _ZN4Aska5THashIN9Framework11CStringHash8tElementEE6RemoveEPKvj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashIN9Framework11CStringHash8tElementEE6RemoveEPKvj
               (long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar3 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x01f9cbc4;
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) goto code_r0x01f9cbc4;
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  }
code_r0x01f9cbc4:
                    /* WARNING: Could not recover jumptable at 0x01f9cbdc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x40))(param_1,plVar4);
  return;
}

// ==== Aska::THash<Framework::CStringHash::tElement>::IsRegisted(void const*, unsigned int)
// vaddr 0x1e9cbe0 | ghidra 0x1f9cbe0 | size 132 | symbol _ZN4Aska5THashIN9Framework11CStringHash8tElementEE10IsRegistedEPKvj | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska5THashIN9Framework11CStringHash8tElementEE10IsRegistedEPKvj
               (long param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0x58) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(*(long *)(param_1 + 0x50) + uVar3 * 8);
  plVar2 = (long *)*plVar4;
  do {
    if (plVar2 == (long *)0x0) {
      return false;
    }
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return *plVar4 != 0;
      }
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) {
        return false;
      }
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  } while( true );
}

// ==== Aska::TBinaryTree<Framework::CStringHash::tElement>::FreeTable()
// vaddr 0x1e9cc64 | ghidra 0x1f9cc64 | size 504 | symbol _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE9FreeTableEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE9FreeTableEv(long *param_1)

{
  int iVar1;
  long lVar2;
  long *plVar3;
  long *plVar4;
  ulong uVar5;
  long *plVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  long *plVar10;
  
  iVar8 = *(int *)((long)param_1 + 0x8c);
  iVar1 = (int)param_1[0xb];
  plVar4 = (long *)param_1[10];
  if (iVar8 == *(int *)((long)param_1 + 0x3c)) {
    iVar9 = iVar8 + -1;
    if (0 < iVar8) {
      lVar2 = 0;
      uVar7 = 0;
      if (*(uint *)((long)param_1 + 0x2c) != 0) goto code_r0x01f9ccc8;
      do {
        do {
          uVar7 = uVar7 + 1;
          lVar2 = lVar2 + 0x40;
        } while (*(uint *)((long)param_1 + 0x2c) <= uVar7);
code_r0x01f9ccc8:
      } while ((*(uint *)(param_1[4] + (ulong)(uVar7 >> 5) * 4) & 1 << (ulong)(uVar7 & 0x1f)) == 0);
      Hint_Prefetch((long *)(param_1[8] + lVar2),0,2,0);
      plVar6 = (long *)(param_1[8] + lVar2);
      do {
        if (iVar9 < 1) {
          plVar10 = (long *)0x0;
        }
        else {
          do {
            do {
              uVar7 = uVar7 + 1;
            } while (*(uint *)((long)param_1 + 0x2c) <= uVar7);
          } while ((*(uint *)(param_1[4] + (ulong)(uVar7 >> 5) * 4) & 1 << (ulong)(uVar7 & 0x1f)) ==
                   0);
          plVar10 = (long *)(param_1[8] + (ulong)uVar7 * 0x40);
          Hint_Prefetch(plVar10,0,2,0);
          iVar9 = iVar9 + -1;
        }
        (**(code **)(*plVar6 + 0x18))(plVar6);
        plVar3 = (long *)param_1[8];
        if (((plVar3 != (long *)0x0) && (plVar3 <= plVar6)) &&
           (plVar6 < plVar3 + (ulong)*(uint *)((long)param_1 + 0x2c) * 8)) {
          uVar5 = (long)plVar6 - (long)plVar3;
          (**(code **)plVar3[(uVar5 >> 6 & 0xffffffff) * 8])();
          lVar2 = (uVar5 >> 0xb & 0x7ffffff) * 4;
          *(uint *)(param_1[4] + lVar2) =
               *(uint *)(param_1[4] + lVar2) & (1 << (uVar5 >> 6 & 0x1f) ^ 0xffffffffU);
          *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
        }
        *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
        plVar6 = plVar10;
      } while (plVar10 != (long *)0x0);
    }
  }
  else if (iVar1 != 0) {
    plVar6 = plVar4 + (iVar1 - 1);
    iVar8 = iVar1;
    do {
      (**(code **)(*param_1 + 0x18))(param_1,plVar6);
      iVar8 = iVar8 + -1;
      plVar6 = plVar6 + -1;
    } while (iVar8 != 0);
  }
  param_1[0xc] = 0;
  *(undefined4 *)(param_1 + 0xb) = 0;
  param_1[10] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  *(undefined1 *)(param_1 + 0x11) = 0;
  param_1[0xe] = 0;
  if (((plVar4 != (long *)0x0) && (iVar1 != 0)) && (plVar4 != param_1 + 0xd)) {
    (*(code *)PTR__ZdaPv_02cb5db8)(plVar4);
    return;
  }
  return;
}

// ==== Aska::THash<Framework::CStringHash::tElement>::~THash()
// vaddr 0x1e9ce5c | ghidra 0x1f9ce5c | size 48 | symbol _ZN4Aska5THashIN9Framework11CStringHash8tElementEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashIN9Framework11CStringHash8tElementEED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska5THashIN9Framework11CStringHash8tElementEEE_02cb75d8 + 0x10);
  Aska::TBinaryTree<Framework::CStringHash::tElement>::FreeTable()();
  Aska::TBinaryTree<Framework::CStringHash::tElement>::~TBinaryTree()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::THash<Framework::CStringHash::tElement>::CalcHashValue(void const*) const
// vaddr 0x1e9ce8c | ghidra 0x1f9ce8c | size 84 | symbol _ZNK4Aska5THashIN9Framework11CStringHash8tElementEE13CalcHashValueEPKv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK4Aska5THashIN9Framework11CStringHash8tElementEE13CalcHashValueEPKv
              (long param_1,byte *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  
  uVar1 = *(uint *)(param_1 + 0x58);
  uVar2 = 0x811c9dc5;
  lVar4 = strlen(param_2);
  for (; lVar4 != 0; lVar4 = lVar4 + -1) {
    uVar2 = uVar2 * 0x1000193 ^ (uint)*param_2;
    param_2 = param_2 + 1;
  }
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  return uVar2 - uVar3 * uVar1;
}

// ==== Aska::TBinaryTree<Framework::CStringHash::tElement>::~TBinaryTree()
// vaddr 0x1e9cee0 | ghidra 0x1f9cee0 | size 240 | symbol _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEED2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEEE_02cbb0a0 + 0x10
                   );
  Aska::TBinaryTree<Framework::CStringHash::tElement>::FreeTable()();
  plVar2 = param_1 + 4;
  *param_1 = (long)(PTR__ZTVN4Aska11TPoolLegacyIN9Framework11CStringHash8tElementELb0EEE_02cbd4e0 +
                   0x10);
  if ((*plVar2 != 0) && ((char)param_1[6] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 6) = 0;
  }
  *plVar2 = 0;
  param_1[5] = 0;
  param_1[7] = 0;
  if (param_1[8] == 0) {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[9] == '\0') {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
    if ((param_1[4] != 0) && ((char)param_1[6] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 6) = 0;
    }
  }
  *plVar2 = 0;
  param_1[5] = 0;
  puVar1 = PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10;
  param_1[2] = (long)puVar1;
  *param_1 = (long)puVar1;
  return;
}

// ==== Aska::TBinaryTree<Framework::CStringHash::tElement>::~TBinaryTree()
// vaddr 0x1e9cfd0 | ghidra 0x1f9cfd0 | size 24 | symbol _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEED0Ev(undefined8 param_1)

{
  Aska::TBinaryTree<Framework::CStringHash::tElement>::~TBinaryTree()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TBinaryTree<Framework::CStringHash::tElement>::RegistEx(void const*)
// vaddr 0x1e9cfe8 | ghidra 0x1f9cfe8 | size 136 | symbol _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE8RegistExEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE8RegistExEPKv
                 (long *param_1,undefined8 param_2)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long *plVar4;
  
  plVar4 = (long *)param_1[0xc];
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return plVar4;
      }
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) goto code_r0x01f9d040;
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  }
code_r0x01f9d040:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar4 = lVar3;
  if (lVar3 == 0) {
    plVar4 = (long *)0x0;
  }
  return plVar4;
}

// ==== Aska::TBinaryTree<Framework::CStringHash::tElement>::Regist(void const*)
// vaddr 0x1e9d070 | ghidra 0x1f9d070 | size 144 | symbol _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE6RegistEPKv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE6RegistEPKv
               (long *param_1,undefined8 param_2)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)param_1[0xc];
  plVar2 = (long *)*plVar5;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x01f9d0e4;
      plVar5 = (long *)(*plVar5 + 0x20);
      plVar2 = (long *)*plVar5;
      if (plVar2 == (long *)0x0) goto code_r0x01f9d0c8;
    }
    plVar5 = (long *)(*plVar5 + 0x18);
    plVar2 = (long *)*plVar5;
  }
code_r0x01f9d0c8:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar5 = lVar3;
  lVar4 = 0;
  if (lVar3 != 0) {
code_r0x01f9d0e4:
    if (plVar5 == (long *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar5;
    }
  }
  return lVar4;
}

// ==== Aska::TBinaryTree<Framework::CStringHash::tElement>::Remove(void const*)
// vaddr 0x1e9d100 | ghidra 0x1f9d100 | size 116 | symbol _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE6RemoveEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE6RemoveEPKv
               (long *param_1,undefined8 param_2)

{
  int iVar1;
  long *plVar2;
  long *plVar3;
  
  plVar3 = (long *)param_1[0xc];
  plVar2 = (long *)*plVar3;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x01f9d158;
      plVar3 = (long *)(*plVar3 + 0x20);
      plVar2 = (long *)*plVar3;
      if (plVar2 == (long *)0x0) goto code_r0x01f9d158;
    }
    plVar3 = (long *)(*plVar3 + 0x18);
    plVar2 = (long *)*plVar3;
  }
code_r0x01f9d158:
                    /* WARNING: Could not recover jumptable at 0x01f9d170. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x40))(param_1,plVar3);
  return;
}

// ==== Aska::TBinaryTree<Framework::CStringHash::tElement>::Remove(Framework::CStringHash::tElement**)
// vaddr 0x1e9d174 | ghidra 0x1f9d174 | size 144 | symbol _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE6RemoveEPPS3_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE6RemoveEPPS3_
               (long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  undefined8 *puVar3;
  long lVar4;
  long lStack_8;
  
  lStack_8 = *param_2;
  if (lStack_8 != 0) {
    lVar4 = *(long *)(lStack_8 + 0x18);
    if (*(long *)(lStack_8 + 0x20) == 0) {
      *param_2 = lVar4;
      puVar3 = (undefined8 *)(lStack_8 + 0x18);
    }
    else {
      plVar1 = (long *)(lStack_8 + 0x18);
      if (lVar4 == 0) {
        *param_2 = *(long *)(lStack_8 + 0x20);
        puVar3 = (undefined8 *)(lStack_8 + 0x20);
      }
      else {
        do {
          plVar2 = plVar1;
          lVar4 = *plVar2;
          plVar1 = (long *)(lVar4 + 0x20);
        } while (*(long *)(lVar4 + 0x20) != 0);
        *plVar2 = *(long *)(lVar4 + 0x18);
        *(undefined8 *)(lVar4 + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
        puVar3 = (undefined8 *)(lStack_8 + 0x20);
        *(undefined8 *)(lVar4 + 0x20) = *puVar3;
        *param_2 = lVar4;
        *(undefined8 *)(lStack_8 + 0x18) = 0;
      }
    }
    *puVar3 = 0;
    (**(code **)(*param_1 + 0x18))(param_1,&lStack_8);
  }
  return;
}

// ==== Aska::TBinaryTree<Framework::CStringHash::tElement>::IsRegisted(void const*)
// vaddr 0x1e9d204 | ghidra 0x1f9d204 | size 112 | symbol _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE10IsRegistedEPKv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE10IsRegistedEPKv
               (long param_1,undefined8 param_2)

{
  int iVar1;
  long *plVar2;
  long *plVar3;
  
  plVar3 = *(long **)(param_1 + 0x60);
  plVar2 = (long *)*plVar3;
  do {
    if (plVar2 == (long *)0x0) {
      return false;
    }
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return *plVar3 != 0;
      }
      plVar3 = (long *)(*plVar3 + 0x20);
      plVar2 = (long *)*plVar3;
      if (plVar2 == (long *)0x0) {
        return false;
      }
    }
    plVar3 = (long *)(*plVar3 + 0x18);
    plVar2 = (long *)*plVar3;
  } while( true );
}

// ==== Aska::TBinaryTree<Framework::CStringHash::tElement>::Search(void const*)
// vaddr 0x1e9d274 | ghidra 0x1f9d274 | size 104 | symbol _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE6SearchEPKv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska11TBinaryTreeIN9Framework11CStringHash8tElementEE6SearchEPKv
               (long param_1,undefined8 param_2)

{
  int iVar1;
  long *plVar2;
  long *plVar3;
  
  plVar3 = *(long **)(param_1 + 0x60);
  plVar2 = (long *)*plVar3;
  do {
    if (plVar2 == (long *)0x0) {
      return 0;
    }
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return *plVar3;
      }
      plVar3 = (long *)(*plVar3 + 0x20);
      plVar2 = (long *)*plVar3;
      if (plVar2 == (long *)0x0) {
        return 0;
      }
    }
    plVar3 = (long *)(*plVar3 + 0x18);
    plVar2 = (long *)*plVar3;
  } while( true );
}

// ==== Aska::TPoolLegacy<Framework::CStringHash::tElement, false>::~TPoolLegacy()
// vaddr 0x1e9d2dc | ghidra 0x1f9d2dc | size 220 | symbol _ZN4Aska11TPoolLegacyIN9Framework11CStringHash8tElementELb0EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TPoolLegacyIN9Framework11CStringHash8tElementELb0EED2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska11TPoolLegacyIN9Framework11CStringHash8tElementELb0EEE_02cbd4e0 +
                   0x10);
  plVar2 = param_1 + 4;
  if ((*plVar2 != 0) && ((char)param_1[6] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 6) = 0;
  }
  *plVar2 = 0;
  param_1[5] = 0;
  param_1[7] = 0;
  if (param_1[8] == 0) {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[9] == '\0') {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
    if ((param_1[4] != 0) && ((char)param_1[6] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 6) = 0;
    }
  }
  *plVar2 = 0;
  param_1[5] = 0;
  puVar1 = PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10;
  param_1[2] = (long)puVar1;
  *param_1 = (long)puVar1;
  return;
}

// ==== Aska::TPoolLegacy<Framework::CStringHash::tElement, false>::~TPoolLegacy()
// vaddr 0x1e9d3b8 | ghidra 0x1f9d3b8 | size 220 | symbol _ZN4Aska11TPoolLegacyIN9Framework11CStringHash8tElementELb0EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TPoolLegacyIN9Framework11CStringHash8tElementELb0EED0Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska11TPoolLegacyIN9Framework11CStringHash8tElementELb0EEE_02cbd4e0 +
                   0x10);
  plVar1 = param_1 + 4;
  if ((*plVar1 != 0) && ((char)param_1[6] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 6) = 0;
  }
  *plVar1 = 0;
  param_1[5] = 0;
  param_1[7] = 0;
  if (param_1[8] == 0) {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[9] == '\0') {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
    if ((param_1[4] != 0) && ((char)param_1[6] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 6) = 0;
    }
  }
  *plVar1 = 0;
  param_1[5] = 0;
  param_1[2] = (long)(PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TPoolLegacy<Framework::CStringHash::tElement, false>::SecurePool(unsigned int, bool, void const*, unsigned int const*)
// vaddr 0x1e9d494 | ghidra 0x1f9d494 | size 492 | symbol _ZN4Aska11TPoolLegacyIN9Framework11CStringHash8tElementELb0EE10SecurePoolEjbPKvPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska11TPoolLegacyIN9Framework11CStringHash8tElementELb0EE10SecurePoolEjbPKvPKj
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
    if (lVar2 == 0) goto code_r0x01f9d644;
  }
  else {
    *(undefined1 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x40) = param_4;
  }
  uVar5 = (ulong)param_2 + 0x1f >> 5;
  if (((param_5 == 0) && (*(char *)(param_1 + 0x30) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x28), (uint)uVar5 <= uVar1)) {
    *(uint *)(param_1 + 0x2c) = param_2;
    if (uVar1 == 0) goto code_r0x01f9d5e8;
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
code_r0x01f9d644:
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
code_r0x01f9d5e8:
  if ((param_3 & 1) != 0) {
    memset(*(undefined8 *)(param_1 + 0x40),0,(ulong)param_2 << 6);
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    memset(*plVar4,0,*(int *)(param_1 + 0x28) << 2);
  }
  return 1;
}

// ==== Framework::CStringHash::tElement::~tElement()
// vaddr 0x1e9d680 | ghidra 0x1f9d680 | size 4 | symbol _ZN9Framework11CStringHash8tElementD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CStringHash8tElementD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Framework::CStringHash::tElement::Compare(void const*)
// vaddr 0x1e9d684 | ghidra 0x1f9d684 | size 36 | symbol _ZN9Framework11CStringHash8tElement7CompareEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CStringHash8tElement7CompareEPKv(long *param_1,undefined8 param_2)

{
  undefined8 uVar1;
  
  uVar1 = (**(code **)(*param_1 + 0x30))();
  (*(code *)PTR_strcmp_02c937a8)(param_2,uVar1);
  return;
}

// ==== Framework::CStringHash::tElement::SetKey(void const*)
// vaddr 0x1e9d6a8 | ghidra 0x1f9d6a8 | size 8 | symbol _ZN9Framework11CStringHash8tElement6SetKeyEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CStringHash8tElement6SetKeyEPKv(long param_1,undefined8 param_2)

{
  *(undefined8 *)(param_1 + 0x28) = param_2;
  return;
}

// ==== Framework::CStringHash::tElement::GetKey() const
// vaddr 0x1e9d6b0 | ghidra 0x1f9d6b0 | size 8 | symbol _ZNK9Framework11CStringHash8tElement6GetKeyEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework11CStringHash8tElement6GetKeyEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x28);
}


// FAILED to create function at 029662c0 typeinfo name for Framework::CStringHash::CSubstance
// FAILED to create function at 029662f0 typeinfo name for Aska::THash<Framework::CStringHash::tElement>
// FAILED to create function at 02966330 typeinfo name for Aska::TBinaryTree<Framework::CStringHash::tElement>
// FAILED to create function at 02966370 typeinfo name for Aska::TPoolLegacy<Framework::CStringHash::tElement, false>
// FAILED to create function at 029663b0 typeinfo name for Framework::CStringHash::tElement
// FAILED to create function at 02bab0e0 Framework::CStringHash::vtable
// FAILED to create function at 02bab100 Framework::CStringHash::CSubstance::vtable
// FAILED to create function at 02bab1a8 Framework::CStringHash::typeinfo
// FAILED to create function at 02bab1c0 Aska::TPoolLegacy<Framework::CStringHash::tElement,false>::typeinfo
// FAILED to create function at 02bab1e0 Aska::TBinaryTree<Framework::CStringHash::tElement>::typeinfo
// FAILED to create function at 02bab200 Aska::THash<Framework::CStringHash::tElement>::typeinfo
// FAILED to create function at 02bab220 Framework::CStringHash::CSubstance::typeinfo
// FAILED to create function at 02bab238 Aska::THash<Framework::CStringHash::tElement>::vtable
// FAILED to create function at 02bab2d0 Aska::TBinaryTree<Framework::CStringHash::tElement>::vtable
// FAILED to create function at 02bab340 Aska::TPoolLegacy<Framework::CStringHash::tElement,false>::vtable
// FAILED to create function at 02bab360 Framework::CStringHash::tElement::vtable
// FAILED to create function at 02bab3b0 Framework::CStringHash::tElement::typeinfo
