// port/decomp/params/property.c: Ghidra decompiles for the params subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileAt.java, tools/resolve_decomp.py
// run      2026-10-04 06:13 UTC: tools/decomp_at.sh '--into' 'params/property' '0x12597b4' '0x12597fc' '0x125981c' '0x1281bcc' '0x1259824' '0x1259870' '0x1298180' '0x12981cc' '0x1379370' '0x13793c0' '0x14592f8' '0x1382530' '0x1382598' '0x12b5c98' '0x12b5d1c' '0x12b5d20' '0x16a0480'

// ==== CParameterPropertyBase<96u>::CompareName(char const*) const
// vaddr 0x11597b4 | ghidra 0x12597b4 | size 72 | symbol _ZNK22CParameterPropertyBaseILj96EE11CompareNameEPKc | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK22CParameterPropertyBaseILj96EE11CompareNameEPKc(long param_1,long param_2)

{
  uint uVar1;
  undefined1 auStack_20 [16];
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    Framework::CHash32::CHash32(char const*)(auStack_20);
    uVar1 = Framework::CHash32::operator==(Framework::CHash32 const&) const(param_1 + 0x18,auStack_20);
    Framework::CHash32::~CHash32()(auStack_20);
  }
  return uVar1 & 1;
}

// ==== CParameterPropertyBase<96u>::CompareName(unsigned int) const
// vaddr 0x11597fc | ghidra 0x12597fc | size 32 | symbol _ZNK22CParameterPropertyBaseILj96EE11CompareNameEj | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK22CParameterPropertyBaseILj96EE11CompareNameEj(long param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uStack_4;
  
  uStack_4 = param_2;
  uVar1 = Framework::CHash32::operator==(unsigned int const&) const(param_1 + 0x18,&uStack_4);
  return uVar1 & 1;
}

// ==== CParameterPropertyBase<96u>::NameHash() const
// vaddr 0x115981c | ghidra 0x125981c | size 8 | symbol _ZNK22CParameterPropertyBaseILj96EE8NameHashEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK22CParameterPropertyBaseILj96EE8NameHashEv(long param_1)

{
  (*(code *)PTR__ZNK9Framework7CHash32cvjEv_02c97a40)(param_1 + 0x18);
  return;
}

// ==== CParameterPropertyValue<unsigned int, 96u, CPropertyConverter>::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x1159824 | ghidra 0x1259824 | size 76 | symbol _ZN23CParameterPropertyValueIjLj96E18CPropertyConverterE11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN23CParameterPropertyValueIjLj96E18CPropertyConverterE11DeserializeEPKN4Aska4ASON6AValue4AMapE
               (long *param_1,undefined8 param_2)

{
  undefined4 uVar1;
  ulong uVar2;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  uVar2 = std::__ndk1::pair<unsigned int, bool> CParameterParser::GetValue<unsigned int>(Aska::ASON::AValue::AMap const*, unsigned int)(param_2,uVar1);
  if ((uVar2 >> 0x20 & 0xff) != 0) {
    *(int *)(param_1 + 5) = (int)uVar2;
  }
  return (uVar2 >> 0x20 & 0xff) != 0;
}

// ==== CParameterPropertyValue<unsigned int, 96u, CPropertyConverter>::PrintC() const
// vaddr 0x1159870 | ghidra 0x1259870 | size 4 | symbol _ZNK23CParameterPropertyValueIjLj96E18CPropertyConverterE6PrintCEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK23CParameterPropertyValueIjLj96E18CPropertyConverterE6PrintCEv(void)

{
  return;
}

// ==== void CParameterPropertyBase<96u>::CryptString<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1181bcc | ghidra 0x1281bcc | size 288 | symbol _ZN22CParameterPropertyBaseILj96EE11CryptStringINSt6__ndk112basic_stringIcNS2_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS6_22CSTLStringAllocatorInfEEEEEEEvRT_RKSB_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22CParameterPropertyBaseILj96EE11CryptStringINSt6__ndk112basic_stringIcNS2_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS6_22CSTLStringAllocatorInfEEEEEEEvRT_RKSB_
               (ulong *param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  bool bVar3;
  ulong uVar4;
  byte bVar5;
  byte *pbVar6;
  ulong uVar7;
  
  if ((*param_1 & 1) == 0) {
    *(undefined2 *)param_1 = 0;
  }
  else {
    *(undefined1 *)param_1[2] = 0;
    param_1[1] = 0;
  }
  bVar3 = (*param_2 & 1) != 0;
  uVar7 = (ulong)(*param_2 >> 1);
  if (bVar3) {
    uVar7 = *(ulong *)(param_2 + 8);
  }
  if (uVar7 != 0) {
    pbVar6 = param_2 + 1;
    if (bVar3) {
      pbVar6 = *(byte **)(param_2 + 0x10);
    }
    do {
      bVar1 = *pbVar6;
      bVar5 = (byte)*param_1;
      if ((bVar5 & 1) == 0) {
        uVar7 = (ulong)(bVar5 >> 1);
        uVar4 = 0x16;
        if (uVar7 == 0x16) goto code_r0x01281c60;
      }
      else {
        uVar7 = param_1[1];
        uVar4 = (*param_1 & 0xfffffffffffffffe) - 1;
        if (uVar7 == uVar4) {
code_r0x01281c60:
          string::__grow_by(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)(param_1,uVar4,1,uVar4,uVar4,0,0);
          bVar5 = (byte)*param_1;
        }
      }
      if ((bVar5 & 1) == 0) {
        *(char *)param_1 = (char)uVar7 * '\x02' + '\x02';
        uVar4 = (long)param_1 + 1;
      }
      else {
        param_1[1] = uVar7 + 1;
        uVar4 = param_1[2];
      }
      *(byte *)(uVar4 + uVar7) = bVar1 ^ 0x60;
      ((byte *)(uVar4 + uVar7))[1] = 0;
      pbVar6 = pbVar6 + 1;
      uVar7 = (ulong)(*param_2 >> 1);
      pbVar2 = param_2 + 1;
      if ((*param_2 & 1) != 0) {
        uVar7 = *(ulong *)(param_2 + 8);
        pbVar2 = *(byte **)(param_2 + 0x10);
      }
    } while (pbVar6 != pbVar2 + uVar7);
  }
  return;
}

// ==== CParameterPropertyValue<float, 96u, CPropertyConverter>::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x1198180 | ghidra 0x1298180 | size 76 | symbol _ZN23CParameterPropertyValueIfLj96E18CPropertyConverterE11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN23CParameterPropertyValueIfLj96E18CPropertyConverterE11DeserializeEPKN4Aska4ASON6AValue4AMapE
               (long *param_1,undefined8 param_2)

{
  undefined4 uVar1;
  ulong uVar2;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  uVar2 = std::__ndk1::pair<float, bool> CParameterParser::GetValue<float>(Aska::ASON::AValue::AMap const*, unsigned int)(param_2,uVar1);
  if ((uVar2 >> 0x20 & 0xff) != 0) {
    *(int *)(param_1 + 5) = (int)uVar2;
  }
  return (uVar2 >> 0x20 & 0xff) != 0;
}

// ==== CParameterPropertyValue<float, 96u, CPropertyConverter>::PrintC() const
// vaddr 0x11981cc | ghidra 0x12981cc | size 4 | symbol _ZNK23CParameterPropertyValueIfLj96E18CPropertyConverterE6PrintCEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK23CParameterPropertyValueIfLj96E18CPropertyConverterE6PrintCEv(void)

{
  return;
}

// ==== CParameterPropertyString<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, 100u>::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x11b5c98 | ghidra 0x12b5c98 | size 132 | symbol _ZN24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj100EE11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj100EE11DeserializeEPKN4Aska4ASON6AValue4AMapE
               (long *param_1,undefined8 param_2)

{
  bool bVar1;
  undefined4 uVar2;
  byte abStack_40 [16];
  undefined8 uStack_30;
  char cStack_28;
  
  uVar2 = (**(code **)(*param_1 + 0x10))();
  std::__ndk1::pair<string, bool> CParameterParser::GetValue<string >(Aska::ASON::AValue::AMap const*, unsigned int)(abStack_40,param_2,uVar2);
  if (cStack_28 == '\0') {
    bVar1 = false;
  }
  else {
    void CParameterPropertyBase<100u>::CryptString<string >(string&, string const&)(param_1 + 5,abStack_40);
    bVar1 = cStack_28 != '\0';
  }
  if ((abStack_40[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_30);
  }
  return bVar1;
}

// ==== CParameterPropertyString<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, 100u>::PrintC() const
// vaddr 0x11b5d1c | ghidra 0x12b5d1c | size 4 | symbol _ZNK24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj100EE6PrintCEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj100EE6PrintCEv
               (void)

{
  return;
}

// ==== void CParameterPropertyBase<100u>::CryptString<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x11b5d20 | ghidra 0x12b5d20 | size 292 | symbol _ZN22CParameterPropertyBaseILj100EE11CryptStringINSt6__ndk112basic_stringIcNS2_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS6_22CSTLStringAllocatorInfEEEEEEEvRT_RKSB_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22CParameterPropertyBaseILj100EE11CryptStringINSt6__ndk112basic_stringIcNS2_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS6_22CSTLStringAllocatorInfEEEEEEEvRT_RKSB_
               (ulong *param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  bool bVar4;
  ulong uVar5;
  byte *pbVar6;
  ulong uVar7;
  
  if ((*param_1 & 1) == 0) {
    *(undefined2 *)param_1 = 0;
  }
  else {
    *(undefined1 *)param_1[2] = 0;
    param_1[1] = 0;
  }
  bVar4 = (*param_2 & 1) != 0;
  uVar7 = (ulong)(*param_2 >> 1);
  if (bVar4) {
    uVar7 = *(ulong *)(param_2 + 8);
  }
  if (uVar7 != 0) {
    pbVar6 = param_2 + 1;
    if (bVar4) {
      pbVar6 = *(byte **)(param_2 + 0x10);
    }
    do {
      bVar2 = (byte)*param_1;
      bVar1 = *pbVar6;
      if ((bVar2 & 1) == 0) {
        uVar7 = (ulong)(bVar2 >> 1);
        uVar5 = 0x16;
      }
      else {
        uVar7 = param_1[1];
        uVar5 = (*param_1 & 0xfffffffffffffffe) - 1;
      }
      if (uVar7 == uVar5) {
        string::__grow_by(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)(param_1,uVar5,1,uVar5,uVar5,0,0);
        bVar2 = (byte)*param_1;
      }
      if ((bVar2 & 1) == 0) {
        *(char *)param_1 = (char)uVar7 * '\x02' + '\x02';
        uVar5 = (long)param_1 + 1;
      }
      else {
        param_1[1] = uVar7 + 1;
        uVar5 = param_1[2];
      }
      *(byte *)(uVar5 + uVar7) = bVar1 ^ 100;
      ((byte *)(uVar5 + uVar7))[1] = 0;
      pbVar6 = pbVar6 + 1;
      uVar7 = (ulong)(*param_2 >> 1);
      pbVar3 = param_2 + 1;
      if ((*param_2 & 1) != 0) {
        uVar7 = *(ulong *)(param_2 + 8);
        pbVar3 = *(byte **)(param_2 + 0x10);
      }
    } while (pbVar6 != pbVar3 + uVar7);
  }
  return;
}

// ==== CParameterPropertyValue<bool, 96u, CPropertyConverter>::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x1279370 | ghidra 0x1379370 | size 80 | symbol _ZN23CParameterPropertyValueIbLj96E18CPropertyConverterE11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN23CParameterPropertyValueIbLj96E18CPropertyConverterE11DeserializeEPKN4Aska4ASON6AValue4AMapE
               (long *param_1,undefined8 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  
  uVar2 = (**(code **)(*param_1 + 0x10))();
  uVar3 = std::__ndk1::pair<bool, bool> CParameterParser::GetValue<bool>(Aska::ASON::AValue::AMap const*, unsigned int)(param_2,uVar2);
  uVar1 = uVar3 >> 8 & 0xff;
  if (uVar1 != 0) {
    *(bool *)(param_1 + 5) = (uVar3 & 0xff) != 0;
  }
  return uVar1 != 0;
}

// ==== CParameterPropertyValue<bool, 96u, CPropertyConverter>::PrintC() const
// vaddr 0x12793c0 | ghidra 0x13793c0 | size 4 | symbol _ZNK23CParameterPropertyValueIbLj96E18CPropertyConverterE6PrintCEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK23CParameterPropertyValueIbLj96E18CPropertyConverterE6PrintCEv(void)

{
  return;
}

// ==== CParameterPropertyValue<float, 118u, CPropertyConverterRadian>::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x1282530 | ghidra 0x1382530 | size 104 | symbol _ZN23CParameterPropertyValueIfLj118E24CPropertyConverterRadianE11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN23CParameterPropertyValueIfLj118E24CPropertyConverterRadianE11DeserializeEPKN4Aska4ASON6AValue4AMapE
               (long *param_1,undefined8 param_2)

{
  undefined4 uVar1;
  ulong uVar2;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  uVar2 = std::__ndk1::pair<float, bool> CParameterParser::GetValue<float>(Aska::ASON::AValue::AMap const*, unsigned int)(param_2,uVar1);
  if ((uVar2 >> 0x20 & 0xff) != 0) {
    *(float *)(param_1 + 5) = ((float)uVar2 * _UNK_027e3fd0) / _UNK_027e3fd4;
  }
  return (uVar2 >> 0x20 & 0xff) != 0;
}

// ==== CParameterPropertyValue<float, 118u, CPropertyConverterRadian>::PrintC() const
// vaddr 0x1282598 | ghidra 0x1382598 | size 4 | symbol _ZNK23CParameterPropertyValueIfLj118E24CPropertyConverterRadianE6PrintCEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK23CParameterPropertyValueIfLj118E24CPropertyConverterRadianE6PrintCEv(void)

{
  return;
}

// ==== void CParameterPropertyBase<31u>::CryptString<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x13592f8 | ghidra 0x14592f8 | size 288 | symbol _ZN22CParameterPropertyBaseILj31EE11CryptStringINSt6__ndk112basic_stringIcNS2_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS6_22CSTLStringAllocatorInfEEEEEEEvRT_RKSB_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22CParameterPropertyBaseILj31EE11CryptStringINSt6__ndk112basic_stringIcNS2_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS6_22CSTLStringAllocatorInfEEEEEEEvRT_RKSB_
               (ulong *param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  bool bVar3;
  ulong uVar4;
  byte bVar5;
  byte *pbVar6;
  ulong uVar7;
  
  if ((*param_1 & 1) == 0) {
    *(undefined2 *)param_1 = 0;
  }
  else {
    *(undefined1 *)param_1[2] = 0;
    param_1[1] = 0;
  }
  bVar3 = (*param_2 & 1) != 0;
  uVar7 = (ulong)(*param_2 >> 1);
  if (bVar3) {
    uVar7 = *(ulong *)(param_2 + 8);
  }
  if (uVar7 != 0) {
    pbVar6 = param_2 + 1;
    if (bVar3) {
      pbVar6 = *(byte **)(param_2 + 0x10);
    }
    do {
      bVar1 = *pbVar6;
      bVar5 = (byte)*param_1;
      if ((bVar5 & 1) == 0) {
        uVar7 = (ulong)(bVar5 >> 1);
        uVar4 = 0x16;
        if (uVar7 == 0x16) goto code_r0x0145938c;
      }
      else {
        uVar7 = param_1[1];
        uVar4 = (*param_1 & 0xfffffffffffffffe) - 1;
        if (uVar7 == uVar4) {
code_r0x0145938c:
          string::__grow_by(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)(param_1,uVar4,1,uVar4,uVar4,0,0);
          bVar5 = (byte)*param_1;
        }
      }
      if ((bVar5 & 1) == 0) {
        *(char *)param_1 = (char)uVar7 * '\x02' + '\x02';
        uVar4 = (long)param_1 + 1;
      }
      else {
        param_1[1] = uVar7 + 1;
        uVar4 = param_1[2];
      }
      *(byte *)(uVar4 + uVar7) = bVar1 ^ 0x1f;
      ((byte *)(uVar4 + uVar7))[1] = 0;
      pbVar6 = pbVar6 + 1;
      uVar7 = (ulong)(*param_2 >> 1);
      pbVar2 = param_2 + 1;
      if ((*param_2 & 1) != 0) {
        uVar7 = *(ulong *)(param_2 + 8);
        pbVar2 = *(byte **)(param_2 + 0x10);
      }
    } while (pbVar6 != pbVar2 + uVar7);
  }
  return;
}

// ==== CParameterPropertyValue<unsigned char, 186u, CPropertyConverter>::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x15a0480 | ghidra 0x16a0480 | size 72 | symbol _ZN23CParameterPropertyValueIhLj186E18CPropertyConverterE11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN23CParameterPropertyValueIhLj186E18CPropertyConverterE11DeserializeEPKN4Aska4ASON6AValue4AMapE
               (long *param_1,undefined8 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  
  uVar2 = (**(code **)(*param_1 + 0x10))();
  uVar3 = std::__ndk1::pair<unsigned char, bool> CParameterParser::GetValue<unsigned char>(Aska::ASON::AValue::AMap const*, unsigned int)(param_2,uVar2);
  uVar1 = uVar3 >> 8 & 0xff;
  if (uVar1 != 0) {
    *(char *)(param_1 + 5) = (char)uVar3;
  }
  return uVar1 != 0;
}
