// port/decomp/params/parser.c: Ghidra decompiles for the params subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:12 UTC: tools/decomp.sh '--into' 'params/parser' 'CParameterParser::'

// ==== CParameterParser::GetValueString(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f5bf0 | ghidra 0x17f5bf0 | size 280 | symbol _ZN16CParameterParser14GetValueStringEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1  [16]
_ZN16CParameterParser14GetValueStringEPKN4Aska4ASON6AValue4AMapEPKc(long param_1,undefined8 param_2)

{
  int *piVar1;
  undefined *puVar2;
  ulong uVar3;
  undefined8 uVar4;
  undefined1 auVar5 [16];
  byte bStack_38;
  undefined7 uStack_37;
  undefined1 uStack_30;
  undefined2 uStack_2f;
  undefined1 uStack_2d;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x12,&UNK_0285e8ae/*"apObject is null."*/);
  }
  piVar1 = (int *)Aska::ASON::AValue::AMap::Get_(char const*)(param_1,param_2);
  if (piVar1 == (int *)0x0) {
    uStack_2c = 0;
    uStack_28 = 0;
    bStack_38 = 0x14;
    uStack_37 = (undefined7)_UNK_0285e8c0;
    uStack_30 = (undefined1)((ulong)_UNK_0285e8c0 >> 0x38);
    uStack_2f = 0x2064;
    uStack_2d = 0;
    uVar3 = strlen(param_2);
    if (uVar3 < 0xc || uVar3 - 0xc == 0) {
      if (uVar3 != 0) {
        memcpy(&uStack_2d,param_2,uVar3);
        *(undefined1 *)(((ulong)&bStack_38 | 1) + uVar3 + 10) = 0;
      }
    }
    else {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_38,0x16,uVar3 - 0xc,10,10,0,uVar3,param_2);
      if ((bStack_38 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
      }
    }
  }
  else if ((*piVar1 != 0) && (puVar2 = *(undefined **)(piVar1 + 4), puVar2 != (undefined *)0x0)) {
    uVar4 = 1;
    goto code_r0x017f5cf8;
  }
  uVar4 = 0;
  puVar2 = &UNK_029d2011;
code_r0x017f5cf8:
  auVar5._8_8_ = uVar4;
  auVar5._0_8_ = puVar2;
  return auVar5;
}

// ==== CParameterParser::GetValueString(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f5d08 | ghidra 0x17f5d08 | size 108 | symbol _ZN16CParameterParser14GetValueStringEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
undefined1  [16]
_ZN16CParameterParser14GetValueStringEPKN4Aska4ASON6AValue4AMapEj(long param_1,undefined4 param_2)

{
  int *piVar1;
  undefined *puVar2;
  undefined8 uVar3;
  undefined1 auVar4 [16];
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x37,&UNK_0285e8ae/*"apObject is null."*/);
  }
  piVar1 = (int *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_1,param_2);
  if (((piVar1 == (int *)0x0) || (*piVar1 == 0)) ||
     (puVar2 = *(undefined **)(piVar1 + 4), puVar2 == (undefined *)0x0)) {
    uVar3 = 0;
    puVar2 = &UNK_029d2011;
  }
  else {
    uVar3 = 1;
  }
  auVar4._8_8_ = uVar3;
  auVar4._0_8_ = puVar2;
  return auVar4;
}

// ==== CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f5d74 | ghidra 0x17f5d74 | size 204 | symbol _ZN16CParameterParser14GetParserValueEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN16CParameterParser14GetParserValueEPKN4Aska4ASON6AValue4AMapEj(long *param_1,int param_2)

{
  ulong uVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  ulong uVar5;
  undefined1 auStack_30 [16];
  int iStack_14;
  
  iStack_14 = param_2;
  if (param_1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e8e7/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/Parameter/ParameterParser.h"*/,0x2c,&UNK_027dc58a/*"apParser is null."*/);
  }
  if ((param_2 != 0) && (uVar2 = *(uint *)(param_1 + 1), uVar2 != 0)) {
    uVar4 = 0;
    do {
      uVar5 = (ulong)uVar4;
      if (*(int *)(*param_1 + uVar5 * 0x40) == 5) {
        Framework::CHash32::CHash32(char const*)(auStack_30,*(undefined8 *)(*param_1 + uVar5 * 0x40 + 0x10));
        uVar1 = Framework::CHash32::operator==(unsigned int const&) const(auStack_30,&iStack_14);
        if ((uVar1 & 1) != 0) {
          lVar3 = *param_1;
          Framework::CHash32::~CHash32()(auStack_30);
          return lVar3 + uVar5 * 0x40 + 0x20;
        }
        Framework::CHash32::~CHash32()(auStack_30);
        uVar2 = *(uint *)(param_1 + 1);
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < uVar2);
  }
  return 0;
}

// ==== CParameterParser::GetValueFloat(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f5e40 | ghidra 0x17f5e40 | size 368 | symbol _ZN16CParameterParser13GetValueFloatEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong _ZN16CParameterParser13GetValueFloatEPKN4Aska4ASON6AValue4AMapEPKc
                (long param_1,undefined8 param_2)

{
  undefined4 *puVar1;
  ulong uVar2;
  undefined8 uVar3;
  float fVar4;
  double dVar5;
  byte bStack_38;
  undefined7 uStack_37;
  undefined1 uStack_30;
  undefined2 uStack_2f;
  undefined1 uStack_2d;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x7d,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar1 = (undefined4 *)Aska::ASON::AValue::AMap::Get_(char const*)(param_1,param_2);
  if (puVar1 == (undefined4 *)0x0) {
    uStack_2f = 0x2064;
    uVar3 = _UNK_0285e8c0;
    goto code_r0x017f5f0c;
  }
  switch(*puVar1) {
  case 2:
    fVar4 = (float)*(ulong *)(puVar1 + 2);
    goto code_r0x017f5eec;
  case 3:
    fVar4 = (float)*(long *)(puVar1 + 2);
    goto code_r0x017f5eec;
  case 4:
    dVar5 = *(double *)(puVar1 + 2);
    break;
  case 5:
    if (*(long *)(puVar1 + 4) == 0) goto code_r0x017f5ef8;
    dVar5 = (double)atof();
    break;
  default:
code_r0x017f5ef8:
    uStack_2f = 0x2068;
    uVar3 = _UNK_0285e8cb;
code_r0x017f5f0c:
    uStack_2c = 0;
    uStack_28 = 0;
    bStack_38 = 0x14;
    uStack_37 = (undefined7)uVar3;
    uStack_30 = (undefined1)((ulong)uVar3 >> 0x38);
    uStack_2d = 0;
    uVar2 = strlen(param_2);
    if (uVar2 < 0xc || uVar2 - 0xc == 0) {
      if (uVar2 != 0) {
        memcpy(&uStack_2d,param_2,uVar2);
        *(undefined1 *)(((ulong)&bStack_38 | 1) + uVar2 + 10) = 0;
      }
    }
    else {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_38,0x16,uVar2 - 0xc,10,10,0,uVar2,param_2);
      if ((bStack_38 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
      }
    }
    return 0;
  }
  fVar4 = (float)dVar5;
code_r0x017f5eec:
  return (ulong)(uint)fVar4 | 0x100000000;
}

// ==== CParameterParser::GetValueFloat(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f5fb0 | ghidra 0x17f5fb0 | size 172 | symbol _ZN16CParameterParser13GetValueFloatEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN16CParameterParser13GetValueFloatEPKN4Aska4ASON6AValue4AMapEj
                (long param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  float fVar2;
  double dVar3;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0xa5,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar1 = (undefined4 *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_1,param_2);
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  switch(*puVar1) {
  case 2:
    fVar2 = (float)*(ulong *)(puVar1 + 2);
    goto code_r0x017f6048;
  case 3:
    fVar2 = (float)*(long *)(puVar1 + 2);
    goto code_r0x017f6048;
  case 4:
    dVar3 = *(double *)(puVar1 + 2);
    break;
  case 5:
    if (*(long *)(puVar1 + 4) == 0) {
      return 0;
    }
    dVar3 = (double)atof();
    break;
  default:
    return 0;
  }
  fVar2 = (float)dVar3;
code_r0x017f6048:
  return (ulong)(uint)fVar2 | 0x100000000;
}

// ==== CParameterParser::GetValueInt(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f605c | ghidra 0x17f605c | size 360 | symbol _ZN16CParameterParser11GetValueIntEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong _ZN16CParameterParser11GetValueIntEPKN4Aska4ASON6AValue4AMapEPKc
                (long param_1,undefined8 param_2)

{
  undefined4 *puVar1;
  ulong uVar2;
  undefined8 uVar3;
  byte bStack_38;
  undefined7 uStack_37;
  undefined1 uStack_30;
  undefined2 uStack_2f;
  undefined1 uStack_2d;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0xbe,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar1 = (undefined4 *)Aska::ASON::AValue::AMap::Get_(char const*)(param_1,param_2);
  if (puVar1 == (undefined4 *)0x0) {
    uStack_2f = 0x2064;
    uVar3 = _UNK_0285e8c0;
code_r0x017f6120:
    uStack_2c = 0;
    uStack_28 = 0;
    bStack_38 = 0x14;
    uStack_37 = (undefined7)uVar3;
    uStack_30 = (undefined1)((ulong)uVar3 >> 0x38);
    uStack_2d = 0;
    uVar2 = strlen(param_2);
    if (uVar2 < 0xc || uVar2 - 0xc == 0) {
      if (uVar2 != 0) {
        memcpy(&uStack_2d,param_2,uVar2);
        *(undefined1 *)(((ulong)&bStack_38 | 1) + uVar2 + 10) = 0;
      }
    }
    else {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_38,0x16,uVar2 - 0xc,10,10,0,uVar2,param_2);
      if ((bStack_38 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
      }
    }
    uVar2 = 0;
  }
  else {
    switch(*puVar1) {
    case 2:
    case 3:
      uVar2 = (ulong)(uint)puVar1[2] | 0x100000000;
      break;
    case 4:
      uVar2 = (ulong)(uint)(int)*(double *)(puVar1 + 2) | 0x100000000;
      break;
    case 5:
      if (*(long *)(puVar1 + 4) != 0) {
        uVar2 = int StringToNumber<int>(char*)();
        return uVar2 & 0xffffffff | 0x100000000;
      }
    default:
      uStack_2f = 0x2068;
      uVar3 = _UNK_0285e8cb;
      goto code_r0x017f6120;
    }
  }
  return uVar2;
}

// ==== CParameterParser::GetValueInt(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f6378 | ghidra 0x17f6378 | size 156 | symbol _ZN16CParameterParser11GetValueIntEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN16CParameterParser11GetValueIntEPKN4Aska4ASON6AValue4AMapEj
                (long param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  ulong uVar2;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0xe5,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar1 = (undefined4 *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_1,param_2);
  uVar2 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    switch(*puVar1) {
    case 2:
    case 3:
      uVar2 = (ulong)(uint)puVar1[2];
      break;
    case 4:
      uVar2 = (ulong)(uint)(int)*(double *)(puVar1 + 2);
      break;
    case 5:
      if (*(long *)(puVar1 + 4) == 0) {
        return 0;
      }
      uVar2 = int StringToNumber<int>(char*)();
      uVar2 = uVar2 & 0xffffffff;
      break;
    default:
      return 0;
    }
    uVar2 = uVar2 | 0x100000000;
  }
  return uVar2;
}

// ==== CParameterParser::GetValueUInt(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f6414 | ghidra 0x17f6414 | size 368 | symbol _ZN16CParameterParser12GetValueUIntEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong _ZN16CParameterParser12GetValueUIntEPKN4Aska4ASON6AValue4AMapEPKc
                (long param_1,undefined8 param_2)

{
  undefined4 *puVar1;
  ulong uVar2;
  undefined8 uVar3;
  ulong uVar4;
  byte bStack_38;
  undefined7 uStack_37;
  undefined1 uStack_30;
  undefined2 uStack_2f;
  undefined1 uStack_2d;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0xfe,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar1 = (undefined4 *)Aska::ASON::AValue::AMap::Get_(char const*)(param_1,param_2);
  if (puVar1 != (undefined4 *)0x0) {
    switch(*puVar1) {
    case 2:
    case 3:
      uVar2 = (ulong)(uint)puVar1[2];
      uVar4 = 0x100000000;
      break;
    case 4:
      uVar4 = 0x100000000;
      uVar2 = (ulong)(uint)(int)*(double *)(puVar1 + 2);
      break;
    case 5:
      if (*(long *)(puVar1 + 4) != 0) {
        uVar2 = unsigned int StringToNumber<unsigned int>(char*)();
        uVar4 = 0x100000000;
        break;
      }
    default:
      uStack_2f = 0x2068;
      uVar3 = _UNK_0285e8cb;
code_r0x017f64d4:
      uStack_2c = 0;
      uStack_28 = 0;
      bStack_38 = 0x14;
      uStack_37 = (undefined7)uVar3;
      uStack_30 = (undefined1)((ulong)uVar3 >> 0x38);
      uStack_2d = 0;
      uVar2 = strlen(param_2);
      if (uVar2 < 0xc || uVar2 - 0xc == 0) {
        if (uVar2 != 0) {
          memcpy(&uStack_2d,param_2,uVar2);
          *(undefined1 *)(((ulong)&bStack_38 | 1) + uVar2 + 10) = 0;
        }
      }
      else {
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_38,0x16,uVar2 - 0xc,10,10,0,uVar2,param_2);
        if ((bStack_38 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
        }
      }
      uVar2 = 0;
      uVar4 = 0;
    }
    return uVar4 | uVar2 & 0xffffffff;
  }
  uStack_2f = 0x2064;
  uVar3 = _UNK_0285e8c0;
  goto code_r0x017f64d4;
}

// ==== CParameterParser::GetValueUInt(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f6738 | ghidra 0x17f6738 | size 180 | symbol _ZN16CParameterParser12GetValueUIntEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN16CParameterParser12GetValueUIntEPKN4Aska4ASON6AValue4AMapEj
                (long param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  ulong uVar2;
  ulong uVar3;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x125,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar1 = (undefined4 *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_1,param_2);
  if (puVar1 == (undefined4 *)0x0) {
code_r0x017f67d4:
    uVar2 = 0;
    uVar3 = 0;
  }
  else {
    switch(*puVar1) {
    case 1:
      uVar2 = (ulong)*(byte *)(puVar1 + 2);
      break;
    case 2:
    case 3:
      uVar2 = (ulong)(uint)puVar1[2];
      break;
    case 4:
      uVar2 = (ulong)(uint)(int)*(double *)(puVar1 + 2);
      break;
    case 5:
      if (*(long *)(puVar1 + 4) == 0) goto code_r0x017f67d4;
      uVar2 = unsigned int StringToNumber<unsigned int>(char*)();
      break;
    default:
      uVar2 = 0;
      uVar3 = 0;
      goto code_r0x017f67d8;
    }
    uVar3 = 0x100000000;
  }
code_r0x017f67d8:
  return uVar3 | uVar2 & 0xffffffff;
}

// ==== CParameterParser::GetValueLong(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f67ec | ghidra 0x17f67ec | size 360 | symbol _ZN16CParameterParser12GetValueLongEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long _ZN16CParameterParser12GetValueLongEPKN4Aska4ASON6AValue4AMapEPKc
               (long param_1,undefined8 param_2)

{
  undefined4 *puVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  byte bStack_38;
  undefined7 uStack_37;
  undefined1 uStack_30;
  undefined2 uStack_2f;
  undefined1 uStack_2d;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x140,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar1 = (undefined4 *)Aska::ASON::AValue::AMap::Get_(char const*)(param_1,param_2);
  if (puVar1 == (undefined4 *)0x0) {
    uStack_2f = 0x2064;
    uVar4 = _UNK_0285e8c0;
code_r0x017f68ac:
    uStack_2c = 0;
    uStack_28 = 0;
    bStack_38 = 0x14;
    uStack_37 = (undefined7)uVar4;
    uStack_30 = (undefined1)((ulong)uVar4 >> 0x38);
    uStack_2d = 0;
    uVar2 = strlen(param_2);
    if (uVar2 < 0xc || uVar2 - 0xc == 0) {
      if (uVar2 != 0) {
        memcpy(&uStack_2d,param_2,uVar2);
        *(undefined1 *)(((ulong)&bStack_38 | 1) + uVar2 + 10) = 0;
      }
    }
    else {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_38,0x16,uVar2 - 0xc,10,10,0,uVar2,param_2);
      if ((bStack_38 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
      }
    }
    lVar3 = 0;
  }
  else {
    switch(*puVar1) {
    case 2:
    case 3:
      lVar3 = *(long *)(puVar1 + 2);
      break;
    case 4:
      lVar3 = (long)*(double *)(puVar1 + 2);
      break;
    case 5:
      if (*(long *)(puVar1 + 4) != 0) {
        lVar3 = long StringToNumber<long>(char*)();
        return lVar3;
      }
    default:
      uStack_2f = 0x2068;
      uVar4 = _UNK_0285e8cb;
      goto code_r0x017f68ac;
    }
  }
  return lVar3;
}

// ==== CParameterParser::GetValueLong(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f6b08 | ghidra 0x17f6b08 | size 164 | symbol _ZN16CParameterParser12GetValueLongEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN16CParameterParser12GetValueLongEPKN4Aska4ASON6AValue4AMapEj
               (long param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  long lVar2;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x167,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar1 = (undefined4 *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_1,param_2);
  if (puVar1 == (undefined4 *)0x0) {
code_r0x017f6b9c:
    lVar2 = 0;
  }
  else {
    switch(*puVar1) {
    case 2:
    case 3:
      lVar2 = *(long *)(puVar1 + 2);
      break;
    case 4:
      lVar2 = (long)*(double *)(puVar1 + 2);
      break;
    case 5:
      if (*(long *)(puVar1 + 4) != 0) {
        lVar2 = long StringToNumber<long>(char*)();
        return lVar2;
      }
      goto code_r0x017f6b9c;
    default:
      lVar2 = 0;
    }
  }
  return lVar2;
}

// ==== CParameterParser::GetValueULong(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f6bac | ghidra 0x17f6bac | size 360 | symbol _ZN16CParameterParser13GetValueULongEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long _ZN16CParameterParser13GetValueULongEPKN4Aska4ASON6AValue4AMapEPKc
               (long param_1,undefined8 param_2)

{
  undefined4 *puVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  byte bStack_38;
  undefined7 uStack_37;
  undefined1 uStack_30;
  undefined2 uStack_2f;
  undefined1 uStack_2d;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x180,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar1 = (undefined4 *)Aska::ASON::AValue::AMap::Get_(char const*)(param_1,param_2);
  if (puVar1 == (undefined4 *)0x0) {
    uStack_2f = 0x2064;
    uVar4 = _UNK_0285e8c0;
code_r0x017f6c6c:
    uStack_2c = 0;
    uStack_28 = 0;
    bStack_38 = 0x14;
    uStack_37 = (undefined7)uVar4;
    uStack_30 = (undefined1)((ulong)uVar4 >> 0x38);
    uStack_2d = 0;
    uVar2 = strlen(param_2);
    if (uVar2 < 0xc || uVar2 - 0xc == 0) {
      if (uVar2 != 0) {
        memcpy(&uStack_2d,param_2,uVar2);
        *(undefined1 *)(((ulong)&bStack_38 | 1) + uVar2 + 10) = 0;
      }
    }
    else {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_38,0x16,uVar2 - 0xc,10,10,0,uVar2,param_2);
      if ((bStack_38 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
      }
    }
    lVar3 = 0;
  }
  else {
    switch(*puVar1) {
    case 2:
    case 3:
      lVar3 = *(long *)(puVar1 + 2);
      break;
    case 4:
      lVar3 = (long)*(double *)(puVar1 + 2);
      break;
    case 5:
      if (*(long *)(puVar1 + 4) != 0) {
        lVar3 = unsigned long StringToNumber<unsigned long>(char*)();
        return lVar3;
      }
    default:
      uStack_2f = 0x2068;
      uVar4 = _UNK_0285e8cb;
      goto code_r0x017f6c6c;
    }
  }
  return lVar3;
}

// ==== CParameterParser::GetValueULong(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f6ec8 | ghidra 0x17f6ec8 | size 164 | symbol _ZN16CParameterParser13GetValueULongEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN16CParameterParser13GetValueULongEPKN4Aska4ASON6AValue4AMapEj
               (long param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  long lVar2;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x1a7,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar1 = (undefined4 *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_1,param_2);
  if (puVar1 == (undefined4 *)0x0) {
code_r0x017f6f5c:
    lVar2 = 0;
  }
  else {
    switch(*puVar1) {
    case 2:
    case 3:
      lVar2 = *(long *)(puVar1 + 2);
      break;
    case 4:
      lVar2 = (long)*(double *)(puVar1 + 2);
      break;
    case 5:
      if (*(long *)(puVar1 + 4) != 0) {
        lVar2 = unsigned long StringToNumber<unsigned long>(char*)();
        return lVar2;
      }
      goto code_r0x017f6f5c;
    default:
      lVar2 = 0;
    }
  }
  return lVar2;
}

// ==== CParameterParser::GetValueBool(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f6f6c | ghidra 0x17f6f6c | size 240 | symbol _ZN16CParameterParser12GetValueBoolEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN16CParameterParser12GetValueBoolEPKN4Aska4ASON6AValue4AMapEPKc
          (undefined8 param_1,undefined8 param_2)

{
  ulong uVar1;
  byte bStack_38;
  undefined7 uStack_37;
  undefined1 uStack_30;
  undefined2 uStack_2f;
  undefined1 uStack_2d;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  
  uVar1 = CParameterParser::GetValueUInt(Aska::ASON::AValue::AMap const*, char const*)();
  if ((uVar1 >> 0x20 & 1) != 0) {
    if ((int)uVar1 == 0) {
      return 0x100;
    }
    if ((int)uVar1 == 1) {
      return 0x101;
    }
    uStack_2c = 0;
    uStack_28 = 0;
    bStack_38 = 0x14;
    uStack_37 = (undefined7)_UNK_0285e8cb;
    uStack_30 = (undefined1)((ulong)_UNK_0285e8cb >> 0x38);
    uStack_2f = 0x2068;
    uStack_2d = 0;
    uVar1 = strlen(param_2);
    if (uVar1 < 0xc || uVar1 - 0xc == 0) {
      if (uVar1 != 0) {
        memcpy(&uStack_2d,param_2,uVar1);
        *(undefined1 *)(((ulong)&bStack_38 | 1) + uVar1 + 10) = 0;
      }
    }
    else {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_38,0x16,uVar1 - 0xc,10,10,0,uVar1,param_2);
      if ((bStack_38 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
      }
    }
  }
  return 0;
}

// ==== CParameterParser::GetValueBool(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f705c | ghidra 0x17f705c | size 180 | symbol _ZN16CParameterParser12GetValueBoolEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN16CParameterParser12GetValueBoolEPKN4Aska4ASON6AValue4AMapEj(long param_1,undefined4 param_2)

{
  undefined8 uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined8 uVar4;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x125,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar3 = (undefined4 *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_1,param_2);
  uVar4 = 0;
  if (puVar3 != (undefined4 *)0x0) {
    switch(*puVar3) {
    case 1:
      uVar2 = (uint)*(byte *)(puVar3 + 2);
      break;
    case 2:
    case 3:
      uVar2 = puVar3[2];
      break;
    case 4:
      uVar2 = (uint)*(double *)(puVar3 + 2);
      break;
    case 5:
      if (*(long *)(puVar3 + 4) == 0) {
        return 0;
      }
      uVar2 = unsigned int StringToNumber<unsigned int>(char*)();
      break;
    default:
      return 0;
    }
    uVar1 = 0x101;
    if (uVar2 != 1) {
      uVar1 = 0;
    }
    uVar4 = 0x100;
    if (uVar2 != 0) {
      uVar4 = uVar1;
    }
  }
  return uVar4;
}

// ==== CParameterParser::GetValueUTiny(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f7110 | ghidra 0x17f7110 | size 364 | symbol _ZN16CParameterParser13GetValueUTinyEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint _ZN16CParameterParser13GetValueUTinyEPKN4Aska4ASON6AValue4AMapEPKc
               (long param_1,undefined8 param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  ulong uVar3;
  undefined8 uVar4;
  byte bStack_38;
  undefined7 uStack_37;
  undefined1 uStack_30;
  undefined2 uStack_2f;
  undefined1 uStack_2d;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x1e8,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar2 = (undefined4 *)Aska::ASON::AValue::AMap::Get_(char const*)(param_1,param_2);
  if (puVar2 != (undefined4 *)0x0) {
    switch(*puVar2) {
    case 2:
    case 3:
      uVar1 = *(byte *)(puVar2 + 2) | 0x100;
      break;
    case 4:
      uVar1 = (int)*(double *)(puVar2 + 2) | 0x100;
      break;
    case 5:
      if (*(long *)(puVar2 + 4) != 0) {
        uVar1 = unsigned char StringToNumber<unsigned char>(char*)();
        uVar1 = uVar1 & 0xff | 0x100;
        break;
      }
    default:
      uStack_2f = 0x2068;
      uVar4 = _UNK_0285e8cb;
code_r0x017f71d4:
      uStack_2c = 0;
      uStack_28 = 0;
      bStack_38 = 0x14;
      uStack_37 = (undefined7)uVar4;
      uStack_30 = (undefined1)((ulong)uVar4 >> 0x38);
      uStack_2d = 0;
      uVar3 = strlen(param_2);
      if (uVar3 < 0xc || uVar3 - 0xc == 0) {
        if (uVar3 != 0) {
          memcpy(&uStack_2d,param_2,uVar3);
          *(undefined1 *)(((ulong)&bStack_38 | 1) + uVar3 + 10) = 0;
        }
      }
      else {
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_38,0x16,uVar3 - 0xc,10,10,0,uVar3,param_2);
        if ((bStack_38 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
        }
      }
      uVar1 = 0;
    }
    return uVar1 & 0xffff;
  }
  uStack_2f = 0x2064;
  uVar4 = _UNK_0285e8c0;
  goto code_r0x017f71d4;
}

// ==== CParameterParser::GetValueUTiny(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f74a0 | ghidra 0x17f74a0 | size 160 | symbol _ZN16CParameterParser13GetValueUTinyEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN16CParameterParser13GetValueUTinyEPKN4Aska4ASON6AValue4AMapEj
               (long param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x20f,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar2 = (undefined4 *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_1,param_2);
  if (puVar2 == (undefined4 *)0x0) {
code_r0x017f752c:
    uVar1 = 0;
  }
  else {
    switch(*puVar2) {
    case 2:
    case 3:
      uVar1 = (uint)*(byte *)(puVar2 + 2);
      break;
    case 4:
      uVar1 = (uint)*(double *)(puVar2 + 2);
      break;
    case 5:
      if (*(long *)(puVar2 + 4) == 0) goto code_r0x017f752c;
      uVar1 = unsigned char StringToNumber<unsigned char>(char*)();
      uVar1 = uVar1 & 0xff;
      break;
    default:
      goto code_r0x017f752c;
    }
    uVar1 = uVar1 | 0x100;
  }
  return uVar1 & 0xffff;
}

// ==== CParameterParser::GetValue(Aska::ASON::AValue const*)
// vaddr 0x16f7540 | ghidra 0x17f7540 | size 108 | symbol _ZN16CParameterParser8GetValueEPKN4Aska4ASON6AValueE | lib libSOA-3.7.0.so | 2026-10-04
undefined1  [16] _ZN16CParameterParser8GetValueEPKN4Aska4ASON6AValueE(int *param_1)

{
  int iVar1;
  ulong uVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  
  if (param_1 == (int *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x228,&UNK_0285e8d6/*"apValue is null."*/);
    return ZEXT816(0);
  }
  iVar1 = *param_1;
  if (iVar1 == 4) {
    uVar2 = *(ulong *)(param_1 + 2);
  }
  else {
    if (iVar1 == 3) {
      auVar5._0_8_ = (double)*(long *)(param_1 + 2);
      auVar5._8_8_ = 0;
      return auVar5;
    }
    uVar2 = 0;
    if (iVar1 == 2) {
      auVar3._0_8_ = NEON_ucvtf(*(undefined8 *)(param_1 + 2));
      auVar3._8_8_ = 0;
      return auVar3;
    }
  }
  auVar4._8_8_ = 0;
  auVar4._0_8_ = uVar2;
  return auVar4;
}

// ==== std::__ndk1::pair<float, bool> CParameterParser::GetValue<float>(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f75ac | ghidra 0x17f75ac | size 4 | symbol _ZN16CParameterParser8GetValueIfEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN16CParameterParser8GetValueIfEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc(void)

{
  (*(code *)PTR__ZN16CParameterParser13GetValueFloatEPKN4Aska4ASON6AValue4AMapEPKc_02c99ad8)();
  return;
}

// ==== std::__ndk1::pair<float, bool> CParameterParser::GetValue<float>(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f75b0 | ghidra 0x17f75b0 | size 172 | symbol _ZN16CParameterParser8GetValueIfEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN16CParameterParser8GetValueIfEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj
                (long param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  float fVar2;
  double dVar3;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0xa5,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar1 = (undefined4 *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_1,param_2);
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  switch(*puVar1) {
  case 2:
    fVar2 = (float)*(ulong *)(puVar1 + 2);
    goto code_r0x017f7648;
  case 3:
    fVar2 = (float)*(long *)(puVar1 + 2);
    goto code_r0x017f7648;
  case 4:
    dVar3 = *(double *)(puVar1 + 2);
    break;
  case 5:
    if (*(long *)(puVar1 + 4) == 0) {
      return 0;
    }
    dVar3 = (double)atof();
    break;
  default:
    return 0;
  }
  fVar2 = (float)dVar3;
code_r0x017f7648:
  return (ulong)(uint)fVar2 | 0x100000000;
}

// ==== std::__ndk1::pair<int, bool> CParameterParser::GetValue<int>(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f765c | ghidra 0x17f765c | size 4 | symbol _ZN16CParameterParser8GetValueIiEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN16CParameterParser8GetValueIiEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc(void)

{
  (*(code *)PTR__ZN16CParameterParser11GetValueIntEPKN4Aska4ASON6AValue4AMapEPKc_02c98720)();
  return;
}

// ==== std::__ndk1::pair<int, bool> CParameterParser::GetValue<int>(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f7660 | ghidra 0x17f7660 | size 156 | symbol _ZN16CParameterParser8GetValueIiEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN16CParameterParser8GetValueIiEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj
                (long param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  ulong uVar2;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0xe5,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar1 = (undefined4 *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_1,param_2);
  uVar2 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    switch(*puVar1) {
    case 2:
    case 3:
      uVar2 = (ulong)(uint)puVar1[2];
      break;
    case 4:
      uVar2 = (ulong)(uint)(int)*(double *)(puVar1 + 2);
      break;
    case 5:
      if (*(long *)(puVar1 + 4) == 0) {
        return 0;
      }
      uVar2 = int StringToNumber<int>(char*)();
      uVar2 = uVar2 & 0xffffffff;
      break;
    default:
      return 0;
    }
    uVar2 = uVar2 | 0x100000000;
  }
  return uVar2;
}

// ==== std::__ndk1::pair<unsigned int, bool> CParameterParser::GetValue<unsigned int>(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f76fc | ghidra 0x17f76fc | size 4 | symbol _ZN16CParameterParser8GetValueIjEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN16CParameterParser8GetValueIjEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc(void)

{
  (*(code *)PTR__ZN16CParameterParser12GetValueUIntEPKN4Aska4ASON6AValue4AMapEPKc_02ca4500)();
  return;
}

// ==== std::__ndk1::pair<unsigned int, bool> CParameterParser::GetValue<unsigned int>(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f7700 | ghidra 0x17f7700 | size 180 | symbol _ZN16CParameterParser8GetValueIjEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN16CParameterParser8GetValueIjEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj
                (long param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  ulong uVar2;
  ulong uVar3;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x125,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar1 = (undefined4 *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_1,param_2);
  if (puVar1 == (undefined4 *)0x0) {
code_r0x017f779c:
    uVar2 = 0;
    uVar3 = 0;
  }
  else {
    switch(*puVar1) {
    case 1:
      uVar2 = (ulong)*(byte *)(puVar1 + 2);
      break;
    case 2:
    case 3:
      uVar2 = (ulong)(uint)puVar1[2];
      break;
    case 4:
      uVar2 = (ulong)(uint)(int)*(double *)(puVar1 + 2);
      break;
    case 5:
      if (*(long *)(puVar1 + 4) == 0) goto code_r0x017f779c;
      uVar2 = unsigned int StringToNumber<unsigned int>(char*)();
      break;
    default:
      uVar2 = 0;
      uVar3 = 0;
      goto code_r0x017f77a0;
    }
    uVar3 = 0x100000000;
  }
code_r0x017f77a0:
  return uVar3 | uVar2 & 0xffffffff;
}

// ==== std::__ndk1::pair<long, bool> CParameterParser::GetValue<long>(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f77b4 | ghidra 0x17f77b4 | size 4 | symbol _ZN16CParameterParser8GetValueIlEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN16CParameterParser8GetValueIlEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc(void)

{
  (*(code *)PTR__ZN16CParameterParser12GetValueLongEPKN4Aska4ASON6AValue4AMapEPKc_02caa968)();
  return;
}

// ==== std::__ndk1::pair<long, bool> CParameterParser::GetValue<long>(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f77b8 | ghidra 0x17f77b8 | size 164 | symbol _ZN16CParameterParser8GetValueIlEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN16CParameterParser8GetValueIlEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj
               (long param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  long lVar2;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x167,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar1 = (undefined4 *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_1,param_2);
  if (puVar1 == (undefined4 *)0x0) {
code_r0x017f784c:
    lVar2 = 0;
  }
  else {
    switch(*puVar1) {
    case 2:
    case 3:
      lVar2 = *(long *)(puVar1 + 2);
      break;
    case 4:
      lVar2 = (long)*(double *)(puVar1 + 2);
      break;
    case 5:
      if (*(long *)(puVar1 + 4) != 0) {
        lVar2 = long StringToNumber<long>(char*)();
        return lVar2;
      }
      goto code_r0x017f784c;
    default:
      lVar2 = 0;
    }
  }
  return lVar2;
}

// ==== std::__ndk1::pair<unsigned long, bool> CParameterParser::GetValue<unsigned long>(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f785c | ghidra 0x17f785c | size 4 | symbol _ZN16CParameterParser8GetValueImEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN16CParameterParser8GetValueImEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc(void)

{
  (*(code *)PTR__ZN16CParameterParser13GetValueULongEPKN4Aska4ASON6AValue4AMapEPKc_02caec60)();
  return;
}

// ==== std::__ndk1::pair<unsigned long, bool> CParameterParser::GetValue<unsigned long>(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f7860 | ghidra 0x17f7860 | size 164 | symbol _ZN16CParameterParser8GetValueImEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN16CParameterParser8GetValueImEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj
               (long param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  long lVar2;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x1a7,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar1 = (undefined4 *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_1,param_2);
  if (puVar1 == (undefined4 *)0x0) {
code_r0x017f78f4:
    lVar2 = 0;
  }
  else {
    switch(*puVar1) {
    case 2:
    case 3:
      lVar2 = *(long *)(puVar1 + 2);
      break;
    case 4:
      lVar2 = (long)*(double *)(puVar1 + 2);
      break;
    case 5:
      if (*(long *)(puVar1 + 4) != 0) {
        lVar2 = unsigned long StringToNumber<unsigned long>(char*)();
        return lVar2;
      }
      goto code_r0x017f78f4;
    default:
      lVar2 = 0;
    }
  }
  return lVar2;
}

// ==== std::__ndk1::pair<bool, bool> CParameterParser::GetValue<bool>(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f7904 | ghidra 0x17f7904 | size 20 | symbol _ZN16CParameterParser8GetValueIbEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined2
_ZN16CParameterParser8GetValueIbEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc(void)

{
  undefined2 uVar1;
  
  uVar1 = CParameterParser::GetValueBool(Aska::ASON::AValue::AMap const*, char const*)();
  return uVar1;
}

// ==== std::__ndk1::pair<bool, bool> CParameterParser::GetValue<bool>(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f7918 | ghidra 0x17f7918 | size 180 | symbol _ZN16CParameterParser8GetValueIbEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN16CParameterParser8GetValueIbEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj
          (long param_1,undefined4 param_2)

{
  undefined8 uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined8 uVar4;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x125,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar3 = (undefined4 *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_1,param_2);
  uVar4 = 0;
  if (puVar3 != (undefined4 *)0x0) {
    switch(*puVar3) {
    case 1:
      uVar2 = (uint)*(byte *)(puVar3 + 2);
      break;
    case 2:
    case 3:
      uVar2 = puVar3[2];
      break;
    case 4:
      uVar2 = (uint)*(double *)(puVar3 + 2);
      break;
    case 5:
      if (*(long *)(puVar3 + 4) == 0) {
        return 0;
      }
      uVar2 = unsigned int StringToNumber<unsigned int>(char*)();
      break;
    default:
      return 0;
    }
    uVar1 = 0x101;
    if (uVar2 != 1) {
      uVar1 = 0;
    }
    uVar4 = 0x100;
    if (uVar2 != 0) {
      uVar4 = uVar1;
    }
  }
  return uVar4;
}

// ==== std::__ndk1::pair<unsigned char, bool> CParameterParser::GetValue<unsigned char>(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f79cc | ghidra 0x17f79cc | size 20 | symbol _ZN16CParameterParser8GetValueIhEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
undefined2
_ZN16CParameterParser8GetValueIhEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc(void)

{
  undefined2 uVar1;
  
  uVar1 = CParameterParser::GetValueUTiny(Aska::ASON::AValue::AMap const*, char const*)();
  return uVar1;
}

// ==== std::__ndk1::pair<unsigned char, bool> CParameterParser::GetValue<unsigned char>(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f79e0 | ghidra 0x17f79e0 | size 160 | symbol _ZN16CParameterParser8GetValueIhEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN16CParameterParser8GetValueIhEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj
               (long param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x20f,&UNK_0285e8ae/*"apObject is null."*/);
  }
  puVar2 = (undefined4 *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_1,param_2);
  if (puVar2 == (undefined4 *)0x0) {
code_r0x017f7a6c:
    uVar1 = 0;
  }
  else {
    switch(*puVar2) {
    case 2:
    case 3:
      uVar1 = (uint)*(byte *)(puVar2 + 2);
      break;
    case 4:
      uVar1 = (uint)*(double *)(puVar2 + 2);
      break;
    case 5:
      if (*(long *)(puVar2 + 4) == 0) goto code_r0x017f7a6c;
      uVar1 = unsigned char StringToNumber<unsigned char>(char*)();
      uVar1 = uVar1 & 0xff;
      break;
    default:
      goto code_r0x017f7a6c;
    }
    uVar1 = uVar1 | 0x100;
  }
  return uVar1 & 0xffff;
}

// ==== std::__ndk1::pair<char*, bool> CParameterParser::GetValue<char*>(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f7a80 | ghidra 0x17f7a80 | size 4 | symbol _ZN16CParameterParser8GetValueIPcEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN16CParameterParser8GetValueIPcEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc(void)

{
  (*(code *)PTR__ZN16CParameterParser14GetValueStringEPKN4Aska4ASON6AValue4AMapEPKc_02caa118)();
  return;
}

// ==== std::__ndk1::pair<char*, bool> CParameterParser::GetValue<char*>(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f7a84 | ghidra 0x17f7a84 | size 108 | symbol _ZN16CParameterParser8GetValueIPcEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
undefined1  [16]
_ZN16CParameterParser8GetValueIPcEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj
          (long param_1,undefined4 param_2)

{
  int *piVar1;
  undefined *puVar2;
  undefined8 uVar3;
  undefined1 auVar4 [16];
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x37,&UNK_0285e8ae/*"apObject is null."*/);
  }
  piVar1 = (int *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_1,param_2);
  if (((piVar1 == (int *)0x0) || (*piVar1 == 0)) ||
     (puVar2 = *(undefined **)(piVar1 + 4), puVar2 == (undefined *)0x0)) {
    uVar3 = 0;
    puVar2 = &UNK_029d2011;
  }
  else {
    uVar3 = 1;
  }
  auVar4._8_8_ = uVar3;
  auVar4._0_8_ = puVar2;
  return auVar4;
}

// ==== std::__ndk1::pair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, bool> CParameterParser::GetValue<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >(Aska::ASON::AValue::AMap const*, char const*)
// vaddr 0x16f7af0 | ghidra 0x17f7af0 | size 220 | symbol _ZN16CParameterParser8GetValueINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEEENS1_4pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN16CParameterParser8GetValueINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEEENS1_4pairIT_bEEPKN4Aska4ASON6AValue4AMapEPKc
               (ulong *param_1)

{
  undefined8 uVar1;
  ulong uVar2;
  undefined1 extraout_w1;
  ulong uVar3;
  ulong uVar4;
  
  uVar1 = CParameterParser::GetValueString(Aska::ASON::AValue::AMap const*, char const*)();
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  uVar2 = strlen();
  if (uVar2 < 0x17) {
    uVar3 = (long)param_1 + 1;
    *(char *)param_1 = (char)(uVar2 << 1);
    if (uVar2 == 0) goto code_r0x017f7bb0;
  }
  else {
    uVar4 = uVar2 + 0x10 & 0xfffffffffffffff0;
    if (uVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar3 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar4,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uVar2;
    param_1[2] = uVar3;
    *param_1 = uVar4 | 1;
  }
  memcpy(uVar3,uVar1,uVar2);
code_r0x017f7bb0:
  *(undefined1 *)(uVar3 + uVar2) = 0;
  *(undefined1 *)(param_1 + 3) = extraout_w1;
  return;
}

// ==== std::__ndk1::pair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, bool> CParameterParser::GetValue<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >(Aska::ASON::AValue::AMap const*, unsigned int)
// vaddr 0x16f7bcc | ghidra 0x17f7bcc | size 300 | symbol _ZN16CParameterParser8GetValueINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEEENS1_4pairIT_bEEPKN4Aska4ASON6AValue4AMapEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN16CParameterParser8GetValueINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEEENS1_4pairIT_bEEPKN4Aska4ASON6AValue4AMapEj
               (ulong *param_1,long param_2,undefined4 param_3)

{
  int *piVar1;
  ulong uVar2;
  undefined *puVar3;
  ulong uVar4;
  ulong uVar5;
  undefined1 uVar6;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285e860/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterParser.cpp"*/,0x37,&UNK_0285e8ae/*"apObject is null."*/);
  }
  piVar1 = (int *)CParameterParser::GetParserValue(Aska::ASON::AValue::AMap const*, unsigned int)(param_2,param_3);
  if (((piVar1 == (int *)0x0) || (*piVar1 == 0)) ||
     (puVar3 = *(undefined **)(piVar1 + 4), puVar3 == (undefined *)0x0)) {
    uVar6 = 0;
    puVar3 = &UNK_029d2011;
  }
  else {
    uVar6 = 1;
  }
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  uVar2 = strlen(puVar3);
  if (uVar2 < 0x17) {
    uVar4 = (long)param_1 + 1;
    *(char *)param_1 = (char)(uVar2 << 1);
    if (uVar2 == 0) goto code_r0x017f7cdc;
  }
  else {
    uVar5 = uVar2 + 0x10 & 0xfffffffffffffff0;
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar4 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uVar2;
    param_1[2] = uVar4;
    *param_1 = uVar5 | 1;
  }
  memcpy(uVar4,puVar3,uVar2);
code_r0x017f7cdc:
  *(undefined1 *)(uVar4 + uVar2) = 0;
  *(undefined1 *)(param_1 + 3) = uVar6;
  return;
}
