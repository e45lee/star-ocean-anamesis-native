// port/decomp/hash/chash32.c: Ghidra decompiles for the hash subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:06 UTC: tools/decomp.sh '--into' 'hash/chash32' 'Framework::CHash32::'

// ==== Framework::CHash32::CHash32()
// vaddr 0x1e859f8 | ghidra 0x1f859f8 | size 24 | symbol _ZN9Framework7CHash32C2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CHash32C1Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework7CHash32E_02cba528;
  *(undefined4 *)(param_1 + 1) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  return;
}

// ==== Framework::CHash32::CHash32(char const*)
// vaddr 0x1e85a10 | ghidra 0x1f85a10 | size 112 | symbol _ZN9Framework7CHash32C2EPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CHash32C1EPKc(long *param_1,byte *param_2)

{
  uint uVar1;
  ulong uVar2;
  ulong uVar3;
  
  *param_1 = (long)(PTR__ZTVN9Framework7CHash32E_02cba528 + 0x10);
  if (param_2 == (byte *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar2 = strlen(param_2);
    uVar1 = 0;
    uVar3 = uVar2;
    for (; uVar2 != 0; uVar2 = uVar2 - 1) {
      uVar1 = *(uint *)(&UNK_02963e48 + (ulong)((uint)uVar3 & 0xff ^ (uint)*param_2) * 4) ^
              (uint)uVar3 >> 8;
      uVar3 = (ulong)uVar1;
      param_2 = param_2 + 1;
    }
  }
  *(uint *)(param_1 + 1) = uVar1;
  return;
}

// ==== Framework::CHash32::CHash32(char const*, unsigned long)
// vaddr 0x1e85a80 | ghidra 0x1f85a80 | size 76 | symbol _ZN9Framework7CHash32C1EPKcm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CHash32C2EPKcm(long *param_1,byte *param_2,long param_3)

{
  uint uVar1;
  
  uVar1 = 0;
  *param_1 = (long)(PTR__ZTVN9Framework7CHash32E_02cba528 + 0x10);
  if ((param_2 != (byte *)0x0) && (param_3 != 0)) {
    uVar1 = (uint)param_3;
    do {
      param_3 = param_3 + -1;
      uVar1 = *(uint *)(&UNK_02963e48 + (ulong)(uVar1 & 0xff ^ (uint)*param_2) * 4) ^ uVar1 >> 8;
      param_2 = param_2 + 1;
    } while (param_3 != 0);
  }
  *(uint *)(param_1 + 1) = uVar1;
  return;
}

// ==== Framework::CHash32::CHash32(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1e85acc | ghidra 0x1f85acc | size 112 | symbol _ZN9Framework7CHash32C1ERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CHash32C2ERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE
               (long *param_1,byte *param_2)

{
  uint uVar1;
  byte bVar2;
  ulong uVar3;
  byte *pbVar4;
  ulong uVar5;
  
  *param_1 = (long)(PTR__ZTVN9Framework7CHash32E_02cba528 + 0x10);
  bVar2 = *param_2;
  uVar3 = (ulong)(bVar2 >> 1);
  if ((bVar2 & 1) != 0) {
    uVar3 = *(ulong *)(param_2 + 8);
  }
  if (uVar3 != 0) {
    pbVar4 = *(byte **)(param_2 + 0x10);
    if ((bVar2 & 1) == 0) {
      pbVar4 = param_2 + 1;
    }
    uVar5 = uVar3 & 0xffffffff;
    do {
      uVar3 = uVar3 - 1;
      uVar1 = *(uint *)(&UNK_02963e48 + (ulong)((uint)uVar5 & 0xff ^ (uint)*pbVar4) * 4) ^
              (uint)uVar5 >> 8;
      uVar5 = (ulong)uVar1;
      pbVar4 = pbVar4 + 1;
    } while (uVar3 != 0);
    *(uint *)(param_1 + 1) = uVar1;
    return;
  }
  *(undefined4 *)(param_1 + 1) = 0;
  return;
}

// ==== Framework::CHash32::CHash32(unsigned int)
// vaddr 0x1e85b3c | ghidra 0x1f85b3c | size 132 | symbol _ZN9Framework7CHash32C1Ej | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CHash32C2Ej(long *param_1,undefined4 param_2)

{
  uint uVar1;
  byte *pbVar2;
  ulong uVar3;
  ulong uVar4;
  byte abStack_20 [16];
  
  *param_1 = (long)(PTR__ZTVN9Framework7CHash32E_02cba528 + 0x10);
  abStack_20[0] = 0;
  abStack_20[1] = 0;
  abStack_20[2] = 0;
  abStack_20[3] = 0;
  abStack_20[4] = 0;
  abStack_20[5] = 0;
  abStack_20[6] = 0;
  abStack_20[7] = 0;
  abStack_20[8] = 0;
  abStack_20[9] = 0;
  abStack_20[10] = 0;
  abStack_20[0xb] = 0;
  abStack_20[0xc] = 0;
  abStack_20[0xd] = 0;
  abStack_20[0xe] = 0;
  abStack_20[0xf] = 0;
  snprintf(abStack_20,0x10,&UNK_027e6d32/*"%u"*/,param_2);
  uVar3 = strlen(abStack_20);
  uVar1 = 0;
  uVar4 = uVar3;
  pbVar2 = abStack_20;
  for (; uVar3 != 0; uVar3 = uVar3 - 1) {
    uVar1 = *(uint *)(&UNK_02963e48 + (ulong)((uint)uVar4 & 0xff ^ (uint)*pbVar2) * 4) ^
            (uint)uVar4 >> 8;
    uVar4 = (ulong)uVar1;
    pbVar2 = pbVar2 + 1;
  }
  *(uint *)(param_1 + 1) = uVar1;
  return;
}

// ==== Framework::CHash32::CHash32(int)
// vaddr 0x1e85bc0 | ghidra 0x1f85bc0 | size 132 | symbol _ZN9Framework7CHash32C2Ei | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CHash32C1Ei(long *param_1,undefined4 param_2)

{
  uint uVar1;
  byte *pbVar2;
  ulong uVar3;
  ulong uVar4;
  byte abStack_20 [16];
  
  *param_1 = (long)(PTR__ZTVN9Framework7CHash32E_02cba528 + 0x10);
  abStack_20[0] = 0;
  abStack_20[1] = 0;
  abStack_20[2] = 0;
  abStack_20[3] = 0;
  abStack_20[4] = 0;
  abStack_20[5] = 0;
  abStack_20[6] = 0;
  abStack_20[7] = 0;
  abStack_20[8] = 0;
  abStack_20[9] = 0;
  abStack_20[10] = 0;
  abStack_20[0xb] = 0;
  abStack_20[0xc] = 0;
  abStack_20[0xd] = 0;
  abStack_20[0xe] = 0;
  abStack_20[0xf] = 0;
  snprintf(abStack_20,0x10,&UNK_027e6d32/*"%u"*/,param_2);
  uVar3 = strlen(abStack_20);
  uVar1 = 0;
  uVar4 = uVar3;
  pbVar2 = abStack_20;
  for (; uVar3 != 0; uVar3 = uVar3 - 1) {
    uVar1 = *(uint *)(&UNK_02963e48 + (ulong)((uint)uVar4 & 0xff ^ (uint)*pbVar2) * 4) ^
            (uint)uVar4 >> 8;
    uVar4 = (ulong)uVar1;
    pbVar2 = pbVar2 + 1;
  }
  *(uint *)(param_1 + 1) = uVar1;
  return;
}

// ==== Framework::CHash32::~CHash32()
// vaddr 0x1e85c44 | ghidra 0x1f85c44 | size 4 | symbol _ZN9Framework7CHash32D2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CHash32D1Ev(void)

{
  return;
}

// ==== Framework::CHash32::~CHash32()
// vaddr 0x1e85c48 | ghidra 0x1f85c48 | size 4 | symbol _ZN9Framework7CHash32D0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CHash32D0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Framework::CHash32::Get() const
// vaddr 0x1e85c4c | ghidra 0x1f85c4c | size 8 | symbol _ZNK9Framework7CHash323GetEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework7CHash323GetEv(long param_1)

{
  return *(undefined4 *)(param_1 + 8);
}

// ==== Framework::CHash32::operator unsigned int() const
// vaddr 0x1e85c54 | ghidra 0x1f85c54 | size 8 | symbol _ZNK9Framework7CHash32cvjEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework7CHash32cvjEv(long param_1)

{
  return *(undefined4 *)(param_1 + 8);
}

// ==== Framework::CHash32::operator==(Framework::CHash32 const&) const
// vaddr 0x1e85c5c | ghidra 0x1f85c5c | size 20 | symbol _ZNK9Framework7CHash32eqERKS0_ | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework7CHash32eqERKS0_(long param_1,long param_2)

{
  return *(int *)(param_1 + 8) == *(int *)(param_2 + 8);
}

// ==== Framework::CHash32::operator==(unsigned int const&) const
// vaddr 0x1e85c70 | ghidra 0x1f85c70 | size 20 | symbol _ZNK9Framework7CHash32eqERKj | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework7CHash32eqERKj(long param_1,int *param_2)

{
  return *(int *)(param_1 + 8) == *param_2;
}

// ==== Framework::CHash32::operator!=(Framework::CHash32 const&) const
// vaddr 0x1e85c84 | ghidra 0x1f85c84 | size 20 | symbol _ZNK9Framework7CHash32neERKS0_ | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework7CHash32neERKS0_(long param_1,long param_2)

{
  return *(int *)(param_1 + 8) != *(int *)(param_2 + 8);
}

// ==== Framework::CHash32::operator!=(unsigned int const&) const
// vaddr 0x1e85c98 | ghidra 0x1f85c98 | size 20 | symbol _ZNK9Framework7CHash32neERKj | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework7CHash32neERKj(long param_1,int *param_2)

{
  return *(int *)(param_1 + 8) != *param_2;
}

// ==== Framework::CHash32::operator<(Framework::CHash32 const&) const
// vaddr 0x1e85cac | ghidra 0x1f85cac | size 20 | symbol _ZNK9Framework7CHash32ltERKS0_ | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework7CHash32ltERKS0_(long param_1,long param_2)

{
  return *(uint *)(param_1 + 8) < *(uint *)(param_2 + 8);
}

// ==== Framework::CHash32::operator>(Framework::CHash32 const&) const
// vaddr 0x1e85cc0 | ghidra 0x1f85cc0 | size 20 | symbol _ZNK9Framework7CHash32gtERKS0_ | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework7CHash32gtERKS0_(long param_1,long param_2)

{
  return *(uint *)(param_2 + 8) < *(uint *)(param_1 + 8);
}

// ==== Framework::CHash32::operator<(char const*) const
// vaddr 0x1e85cd4 | ghidra 0x1f85cd4 | size 88 | symbol _ZNK9Framework7CHash32ltEPKc | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework7CHash32ltEPKc(long param_1,byte *param_2)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  ulong uVar4;
  
  uVar2 = *(uint *)(param_1 + 8);
  uVar3 = strlen(param_2);
  uVar1 = 0;
  uVar4 = uVar3;
  for (; uVar3 != 0; uVar3 = uVar3 - 1) {
    uVar1 = *(uint *)(&UNK_02963e48 + (ulong)((uint)uVar4 & 0xff ^ (uint)*param_2) * 4) ^
            (uint)uVar4 >> 8;
    uVar4 = (ulong)uVar1;
    param_2 = param_2 + 1;
  }
  return uVar2 < uVar1;
}

// ==== Framework::CHash32::operator>(char const*) const
// vaddr 0x1e85d2c | ghidra 0x1f85d2c | size 88 | symbol _ZNK9Framework7CHash32gtEPKc | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework7CHash32gtEPKc(long param_1,byte *param_2)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  ulong uVar4;
  
  uVar2 = *(uint *)(param_1 + 8);
  uVar3 = strlen(param_2);
  uVar1 = 0;
  uVar4 = uVar3;
  for (; uVar3 != 0; uVar3 = uVar3 - 1) {
    uVar1 = *(uint *)(&UNK_02963e48 + (ulong)((uint)uVar4 & 0xff ^ (uint)*param_2) * 4) ^
            (uint)uVar4 >> 8;
    uVar4 = (ulong)uVar1;
    param_2 = param_2 + 1;
  }
  return uVar1 < uVar2;
}

// ==== Framework::CHash32::operator<(unsigned int const&) const
// vaddr 0x1e85d84 | ghidra 0x1f85d84 | size 20 | symbol _ZNK9Framework7CHash32ltERKj | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework7CHash32ltERKj(long param_1,uint *param_2)

{
  return *param_2 < *(uint *)(param_1 + 8);
}

// ==== Framework::CHash32::operator>(unsigned int const&) const
// vaddr 0x1e85d98 | ghidra 0x1f85d98 | size 20 | symbol _ZNK9Framework7CHash32gtERKj | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework7CHash32gtERKj(long param_1,uint *param_2)

{
  return *(uint *)(param_1 + 8) < *param_2;
}

// ==== Framework::CHash32::operator=(char const*)
// vaddr 0x1e85dac | ghidra 0x1f85dac | size 116 | symbol _ZN9Framework7CHash32aSEPKc | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework7CHash32aSEPKc(long param_1,byte *param_2)

{
  uint uVar1;
  ulong uVar2;
  ulong uVar3;
  
  if (param_2 == (byte *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964248/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Hash32.cpp"*/,0xda,&UNK_0296429a/*"apSrc is null."*/);
  }
  uVar2 = strlen(param_2);
  uVar1 = 0;
  uVar3 = uVar2;
  for (; uVar2 != 0; uVar2 = uVar2 - 1) {
    uVar1 = *(uint *)(&UNK_02963e48 + (ulong)((uint)uVar3 & 0xff ^ (uint)*param_2) * 4) ^
            (uint)uVar3 >> 8;
    uVar3 = (ulong)uVar1;
    param_2 = param_2 + 1;
  }
  *(uint *)(param_1 + 8) = uVar1;
  return param_1;
}

// ==== Framework::CHash32::operator=(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1e85e20 | ghidra 0x1f85e20 | size 76 | symbol _ZN9Framework7CHash32aSERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CHash32aSERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE
               (long param_1,byte *param_2)

{
  uint uVar1;
  byte *pbVar2;
  ulong uVar3;
  ulong uVar4;
  
  uVar4 = *(ulong *)(param_2 + 8);
  pbVar2 = *(byte **)(param_2 + 0x10);
  if ((*param_2 & 1) == 0) {
    pbVar2 = param_2 + 1;
    uVar4 = (ulong)(*param_2 >> 1);
  }
  uVar1 = 0;
  uVar3 = uVar4;
  for (; uVar4 != 0; uVar4 = uVar4 - 1) {
    uVar1 = *(uint *)(&UNK_02963e48 + (ulong)((uint)uVar3 & 0xff ^ (uint)*pbVar2) * 4) ^
            (uint)uVar3 >> 8;
    uVar3 = (ulong)uVar1;
    pbVar2 = pbVar2 + 1;
  }
  *(uint *)(param_1 + 8) = uVar1;
  return;
}


// FAILED to create function at 02ba8f68 Framework::CHash32::vtable
// FAILED to create function at 02ba8f88 Framework::CHash32::typeinfo
