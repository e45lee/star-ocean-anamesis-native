// port/decomp/params/base.c: Ghidra decompiles for the params subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:12 UTC: tools/decomp.sh '--into' 'params/base' 'CParameterElementBase::' 'CParameterBase::' 'IParameterProperty::'

// ==== IParameterProperty::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x11575e0 | ghidra 0x12575e0 | size 8 | symbol _ZN18IParameterProperty11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN18IParameterProperty11DeserializeEPKN4Aska4ASON6AValue4AMapE(void)

{
  return 1;
}

// ==== IParameterProperty::PrintC() const
// vaddr 0x11575e8 | ghidra 0x12575e8 | size 4 | symbol _ZNK18IParameterProperty6PrintCEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK18IParameterProperty6PrintCEv(void)

{
  return;
}

// ==== CParameterElementBase::CParameterElementBase()
// vaddr 0x16e8288 | ghidra 0x17e8288 | size 20 | symbol _ZN21CParameterElementBaseC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN21CParameterElementBaseC2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTV21CParameterElementBase_02cbbc00 + 0x10);
  param_1[1] = 0;
  return;
}

// ==== CParameterElementBase::Initialize()
// vaddr 0x16e829c | ghidra 0x17e829c | size 4 | symbol _ZN21CParameterElementBase10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN21CParameterElementBase10InitializeEv(void)

{
  return;
}

// ==== CParameterElementBase::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x16e82a0 | ghidra 0x17e82a0 | size 244 | symbol _ZN21CParameterElementBase11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN21CParameterElementBase11DeserializeEPKN4Aska4ASON6AValue4AMapE(long param_1,long *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  long *plVar5;
  undefined1 auStack_40 [16];
  
  if (param_2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e3b2/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterBase.cpp"*/,0x1e,&UNK_027dc58a/*"apParser is null."*/);
    uVar3 = uRam0000000000000008;
  }
  else {
    uVar3 = *(uint *)(param_2 + 1);
  }
  if (uVar3 != 0) {
    uVar4 = 0;
    do {
      if ((*(int *)(*param_2 + (ulong)uVar4 * 0x40) == 5) &&
         (*(long *)(*param_2 + (ulong)uVar4 * 0x40 + 0x10) != 0)) {
        Framework::CHash32::CHash32(char const*)(auStack_40);
        for (plVar5 = *(long **)(param_1 + 8); plVar5 != (long *)0x0; plVar5 = (long *)plVar5[1]) {
          iVar1 = (**(code **)(*plVar5 + 0x10))(plVar5);
          iVar2 = Framework::CHash32::operator unsigned int() const(auStack_40);
          if (iVar1 == iVar2) {
            (**(code **)(*plVar5 + 0x18))(plVar5,param_2);
            break;
          }
        }
        Framework::CHash32::~CHash32()(auStack_40);
        uVar3 = *(uint *)(param_2 + 1);
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < uVar3);
  }
  return 1;
}

// ==== CParameterElementBase::PrintC() const
// vaddr 0x16e8394 | ghidra 0x17e8394 | size 44 | symbol _ZNK21CParameterElementBase6PrintCEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK21CParameterElementBase6PrintCEv(long param_1)

{
  long *plVar1;
  
  for (plVar1 = *(long **)(param_1 + 8); plVar1 != (long *)0x0; plVar1 = (long *)plVar1[1]) {
    (**(code **)(*plVar1 + 0x20))(plVar1);
  }
  return;
}

// ==== CParameterElementBase::AddProperty(IParameterProperty*)
// vaddr 0x16e83c0 | ghidra 0x17e83c0 | size 44 | symbol _ZN21CParameterElementBase11AddPropertyEP18IParameterProperty | lib libSOA-3.7.0.so | 2026-10-04
void _ZN21CParameterElementBase11AddPropertyEP18IParameterProperty(long param_1,long param_2)

{
  bool bVar1;
  long *plVar2;
  long lVar3;
  
  plVar2 = (long *)(param_1 + 8);
  lVar3 = *plVar2;
  if (*plVar2 != 0) {
    while( true ) {
      plVar2 = (long *)(lVar3 + 8);
      if (*plVar2 == 0) break;
      bVar1 = lVar3 == param_2;
      lVar3 = *plVar2;
      if (bVar1) {
        return;
      }
    }
  }
  *plVar2 = param_2;
  return;
}

// ==== CParameterBase::CParameterBase()
// vaddr 0x16e83ec | ghidra 0x17e83ec | size 20 | symbol _ZN14CParameterBaseC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN14CParameterBaseC2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTV14CParameterBase_02cbb9e8 + 0x10);
  return;
}

// ==== CParameterBase::Initialize()
// vaddr 0x16e8400 | ghidra 0x17e8400 | size 4 | symbol _ZN14CParameterBase10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN14CParameterBase10InitializeEv(void)

{
  return;
}

// ==== CParameterBase::Find(Aska::ASON::AValue::AMap const*)
// vaddr 0x16e8404 | ghidra 0x17e8404 | size 92 | symbol _ZN14CParameterBase4FindEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN14CParameterBase4FindEPKN4Aska4ASON6AValue4AMapE(long *param_1,long param_2)

{
  undefined8 uVar1;
  long lVar2;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e3b2/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterBase.cpp"*/,100,&UNK_027dc58a/*"apParser is null."*/);
  }
  uVar1 = (**(code **)(*param_1 + 0x18))(param_1);
  lVar2 = Aska::ASON::AValue::AMap::Get_(char const*)(param_2,uVar1);
  return lVar2 != 0;
}

// ==== CParameterBase::pGetRoot(Aska::ASON::AValue::AMap const*) const
// vaddr 0x16e8460 | ghidra 0x17e8460 | size 80 | symbol _ZNK14CParameterBase8pGetRootEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK14CParameterBase8pGetRootEPKN4Aska4ASON6AValue4AMapE(long *param_1,long param_2)

{
  undefined8 uVar1;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e3b2/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterBase.cpp"*/,0x70,&UNK_027dc58a/*"apParser is null."*/);
  }
  uVar1 = (**(code **)(*param_1 + 0x18))(param_1);
  (*(code *)PTR__ZN4Aska4ASON6AValue4AMap4Get_EPKc_02c9ff08)(param_2,uVar1);
  return;
}

// ==== CParameterBase::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x16e84b0 | ghidra 0x17e84b0 | size 8 | symbol _ZN14CParameterBase11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN14CParameterBase11DeserializeEPKN4Aska4ASON6AValue4AMapE(void)

{
  return 1;
}

// ==== CParameterBase::~CParameterBase()
// vaddr 0x16e84b8 | ghidra 0x17e84b8 | size 4 | symbol _ZN14CParameterBaseD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN14CParameterBaseD2Ev(void)

{
  return;
}

// ==== CParameterBase::~CParameterBase()
// vaddr 0x16e84bc | ghidra 0x17e84bc | size 4 | symbol _ZN14CParameterBaseD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN14CParameterBaseD0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x17e84c0);
  (*pcVar1)();
}

// ==== CParameterBase::ReleaseParameter(char const*)
// vaddr 0x16e84c0 | ghidra 0x17e84c0 | size 8 | symbol _ZN14CParameterBase16ReleaseParameterEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN14CParameterBase16ReleaseParameterEPKc(void)

{
  return 1;
}


// FAILED to create function at 02a97040 IParameterProperty::typeinfo
// FAILED to create function at 02a970c0 IParameterProperty::vtable
// FAILED to create function at 02b0b778 CParameterElementBase::vtable
// FAILED to create function at 02b0b798 CParameterBase::vtable
// FAILED to create function at 02b0b7e0 CParameterBase::typeinfo
// FAILED to create function at 02b0b7f0 CParameterElementBase::typeinfo
