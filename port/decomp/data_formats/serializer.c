// port/decomp/data_formats/serializer.c: Ghidra decompiles for the data_formats subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:12 UTC: tools/decomp.sh '--into' 'data_formats/serializer' '_AsonSerializer::' 'SerializerImpl::'
// run      2026-10-04 05:22 UTC: tools/decomp.sh '--into' 'data_formats/serializer' 'AsonSerializer_Prepare::'

// ==== AsonSerializer_Prepare::Serialize_Key(char const*)
// vaddr 0x14a9964 | ghidra 0x15a9964 | size 4 | symbol _ZN22AsonSerializer_Prepare13Serialize_KeyEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare13Serialize_KeyEPKc(void)

{
  return;
}

// ==== AsonSerializer_Prepare::Serialize_Value(bool&)
// vaddr 0x14a9968 | ghidra 0x15a9968 | size 28 | symbol _ZN22AsonSerializer_Prepare15Serialize_ValueERb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare15Serialize_ValueERb(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_Value(unsigned char&)
// vaddr 0x14a9984 | ghidra 0x15a9984 | size 28 | symbol _ZN22AsonSerializer_Prepare15Serialize_ValueERh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare15Serialize_ValueERh(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_Value(signed char&)
// vaddr 0x14a99a0 | ghidra 0x15a99a0 | size 28 | symbol _ZN22AsonSerializer_Prepare15Serialize_ValueERa | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare15Serialize_ValueERa(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_Value(unsigned short&)
// vaddr 0x14a99bc | ghidra 0x15a99bc | size 28 | symbol _ZN22AsonSerializer_Prepare15Serialize_ValueERt | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare15Serialize_ValueERt(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_Value(short&)
// vaddr 0x14a99d8 | ghidra 0x15a99d8 | size 28 | symbol _ZN22AsonSerializer_Prepare15Serialize_ValueERs | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare15Serialize_ValueERs(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_Value(unsigned int&)
// vaddr 0x14a99f4 | ghidra 0x15a99f4 | size 28 | symbol _ZN22AsonSerializer_Prepare15Serialize_ValueERj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare15Serialize_ValueERj(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_Value(int&)
// vaddr 0x14a9a10 | ghidra 0x15a9a10 | size 28 | symbol _ZN22AsonSerializer_Prepare15Serialize_ValueERi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare15Serialize_ValueERi(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_Value(unsigned long&)
// vaddr 0x14a9a2c | ghidra 0x15a9a2c | size 28 | symbol _ZN22AsonSerializer_Prepare15Serialize_ValueERm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare15Serialize_ValueERm(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_Value(long&)
// vaddr 0x14a9a48 | ghidra 0x15a9a48 | size 28 | symbol _ZN22AsonSerializer_Prepare15Serialize_ValueERl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare15Serialize_ValueERl(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_Value(float&)
// vaddr 0x14a9a64 | ghidra 0x15a9a64 | size 28 | symbol _ZN22AsonSerializer_Prepare15Serialize_ValueERf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare15Serialize_ValueERf(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_Value(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >&)
// vaddr 0x14a9a80 | ghidra 0x15a9a80 | size 28 | symbol _ZN22AsonSerializer_Prepare15Serialize_ValueERNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare15Serialize_ValueERNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE
               (long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_StartObject()
// vaddr 0x14a9a9c | ghidra 0x15a9a9c | size 4 | symbol _ZN22AsonSerializer_Prepare21Serialize_StartObjectEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare21Serialize_StartObjectEv(void)

{
  (*(code *)PTR__ZN22AsonSerializer_Prepare9IncrementEv_02ca34b8)();
  return;
}

// ==== AsonSerializer_Prepare::Serialize_EndObject()
// vaddr 0x14a9aa0 | ghidra 0x15a9aa0 | size 60 | symbol _ZN22AsonSerializer_Prepare19Serialize_EndObjectEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare19Serialize_EndObjectEv(long param_1)

{
  int iVar1;
  long lVar2;
  
  iVar1 = *(int *)(param_1 + 0x84);
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + -1;
  *(int *)(param_1 + 0x84) = iVar1 + -1;
  iVar1 = *(int *)(*(long *)(param_1 + 0x78) + (long)iVar1 * 4);
  *(int *)(param_1 + 8) = iVar1;
  lVar2 = (long)iVar1 * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar2) = *(int *)(*(long *)(param_1 + 0x18) + lVar2) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_StartArray(char const*, unsigned int)
// vaddr 0x14a9adc | ghidra 0x15a9adc | size 4 | symbol _ZN22AsonSerializer_Prepare20Serialize_StartArrayEPKcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare20Serialize_StartArrayEPKcj(void)

{
  (*(code *)PTR__ZN22AsonSerializer_Prepare9IncrementEv_02ca34b8)();
  return;
}

// ==== AsonSerializer_Prepare::Serialize_ArrayValue(bool&)
// vaddr 0x14a9ae0 | ghidra 0x15a9ae0 | size 28 | symbol _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERb(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_ArrayValue(unsigned char&)
// vaddr 0x14a9afc | ghidra 0x15a9afc | size 28 | symbol _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERh(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_ArrayValue(signed char&)
// vaddr 0x14a9b18 | ghidra 0x15a9b18 | size 28 | symbol _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERa | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERa(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_ArrayValue(unsigned short&)
// vaddr 0x14a9b34 | ghidra 0x15a9b34 | size 28 | symbol _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERt | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERt(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_ArrayValue(short&)
// vaddr 0x14a9b50 | ghidra 0x15a9b50 | size 28 | symbol _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERs | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERs(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_ArrayValue(unsigned int&)
// vaddr 0x14a9b6c | ghidra 0x15a9b6c | size 28 | symbol _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERj(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_ArrayValue(int&)
// vaddr 0x14a9b88 | ghidra 0x15a9b88 | size 28 | symbol _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERi(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_ArrayValue(unsigned long&)
// vaddr 0x14a9ba4 | ghidra 0x15a9ba4 | size 28 | symbol _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERm(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_ArrayValue(long&)
// vaddr 0x14a9bc0 | ghidra 0x15a9bc0 | size 28 | symbol _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERl(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_ArrayValue(float&)
// vaddr 0x14a9bdc | ghidra 0x15a9bdc | size 28 | symbol _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERf(long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_ArrayValue(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >&)
// vaddr 0x14a9bf8 | ghidra 0x15a9bf8 | size 28 | symbol _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare20Serialize_ArrayValueERNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE
               (long param_1)

{
  long lVar1;
  
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar1) = *(int *)(*(long *)(param_1 + 0x18) + lVar1) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_StartArrayObject(unsigned int)
// vaddr 0x14a9c14 | ghidra 0x15a9c14 | size 4 | symbol _ZN22AsonSerializer_Prepare26Serialize_StartArrayObjectEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare26Serialize_StartArrayObjectEj(void)

{
  return;
}

// ==== AsonSerializer_Prepare::Serialize_EndArrayObject(unsigned int)
// vaddr 0x14a9c18 | ghidra 0x15a9c18 | size 4 | symbol _ZN22AsonSerializer_Prepare24Serialize_EndArrayObjectEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare24Serialize_EndArrayObjectEj(void)

{
  return;
}

// ==== AsonSerializer_Prepare::Serialize_EndArray(char const*, unsigned int)
// vaddr 0x14a9c1c | ghidra 0x15a9c1c | size 60 | symbol _ZN22AsonSerializer_Prepare18Serialize_EndArrayEPKcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare18Serialize_EndArrayEPKcj(long param_1)

{
  int iVar1;
  long lVar2;
  
  iVar1 = *(int *)(param_1 + 0x84);
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + -1;
  *(int *)(param_1 + 0x84) = iVar1 + -1;
  iVar1 = *(int *)(*(long *)(param_1 + 0x78) + (long)iVar1 * 4);
  *(int *)(param_1 + 8) = iVar1;
  lVar2 = (long)iVar1 * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar2) = *(int *)(*(long *)(param_1 + 0x18) + lVar2) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Serialize_StartMap(char const*, unsigned int)
// vaddr 0x14a9c58 | ghidra 0x15a9c58 | size 4 | symbol _ZN22AsonSerializer_Prepare18Serialize_StartMapEPKcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare18Serialize_StartMapEPKcj(void)

{
  (*(code *)PTR__ZN22AsonSerializer_Prepare9IncrementEv_02ca34b8)();
  return;
}

// ==== AsonSerializer_Prepare::Serialize_StartMapObject(char const*, unsigned int)
// vaddr 0x14a9c5c | ghidra 0x15a9c5c | size 4 | symbol _ZN22AsonSerializer_Prepare24Serialize_StartMapObjectEPKcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare24Serialize_StartMapObjectEPKcj(void)

{
  return;
}

// ==== AsonSerializer_Prepare::Serialize_EndMapObject(char const*, unsigned int)
// vaddr 0x14a9c60 | ghidra 0x15a9c60 | size 4 | symbol _ZN22AsonSerializer_Prepare22Serialize_EndMapObjectEPKcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare22Serialize_EndMapObjectEPKcj(void)

{
  return;
}

// ==== AsonSerializer_Prepare::Serialize_EndMap(char const*, unsigned int)
// vaddr 0x14a9c64 | ghidra 0x15a9c64 | size 60 | symbol _ZN22AsonSerializer_Prepare16Serialize_EndMapEPKcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare16Serialize_EndMapEPKcj(long param_1)

{
  int iVar1;
  long lVar2;
  
  iVar1 = *(int *)(param_1 + 0x84);
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + -1;
  *(int *)(param_1 + 0x84) = iVar1 + -1;
  iVar1 = *(int *)(*(long *)(param_1 + 0x78) + (long)iVar1 * 4);
  *(int *)(param_1 + 8) = iVar1;
  lVar2 = (long)iVar1 * 4;
  *(int *)(*(long *)(param_1 + 0x18) + lVar2) = *(int *)(*(long *)(param_1 + 0x18) + lVar2) + 1;
  return;
}

// ==== AsonSerializer_Prepare::Increment()
// vaddr 0x14a9d3c | ghidra 0x15a9d3c | size 424 | symbol _ZN22AsonSerializer_Prepare9IncrementEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN22AsonSerializer_Prepare9IncrementEv(long param_1)

{
  int iVar1;
  undefined8 *puVar2;
  int iVar3;
  undefined1 auVar4 [16];
  ulong uVar5;
  long lVar6;
  long *plVar7;
  int iVar8;
  long lVar9;
  undefined4 uStack_44;
  
  uStack_44 = *(undefined4 *)(param_1 + 8);
  puVar2 = (undefined8 *)(param_1 + 0x48);
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
  iVar3 = *(int *)(param_1 + 0x80);
  iVar8 = *(int *)(param_1 + 0x84);
  iVar1 = iVar8 + 1;
  if (iVar3 <= iVar1) {
    plVar7 = (long *)(param_1 + 0x78);
    lVar6 = *plVar7;
    lVar9 = param_1 + 0x50;
    if (iVar3 < 1) {
      if (lVar6 != lVar9) {
        if (lVar6 != 0) {
          operator delete[](void*)(lVar6);
          iVar8 = *(int *)(param_1 + 0x84);
        }
        *plVar7 = lVar9;
      }
      *(undefined4 *)(param_1 + 0x80) = 10;
      if (9 < iVar8) {
        *(undefined4 *)(param_1 + 0x84) = 9;
      }
    }
    else {
      if (lVar6 != lVar9) goto code_r0x015a9dc4;
      uVar5 = (long)iVar3 << 4;
      auVar4._8_8_ = 0;
      auVar4._0_8_ = uVar5;
      lVar9 = (long)iVar3 << 6;
      if (SUB168(auVar4 * ZEXT816(4),8) != 0) {
        lVar9 = -1;
      }
      lVar9 = operator new[](unsigned long, std::nothrow_t const&)(lVar9,PTR__ZSt7nothrow_02cb9a80);
      *plVar7 = lVar9;
      if (lVar9 == 0) {
        *plVar7 = lVar6;
        goto code_r0x015a9dc4;
      }
      *(int *)(param_1 + 0x80) = (int)uVar5;
      if (-1 < iVar8) {
        lVar6 = (long)iVar8 * 4;
        uVar5 = (*(code *)**(undefined8 **)(param_1 + 0x48))
                          (puVar2,(long)(param_1 + 0x48) + lVar6 + 8,lVar9 + lVar6);
        if ((uVar5 & 1) != 0) {
          lVar9 = (long)iVar8 + 1;
          do {
            lVar6 = lVar6 + -4;
            lVar9 = lVar9 + -1;
            if (lVar9 < 1) goto code_r0x015a9d80;
            uVar5 = (*(code *)**(undefined8 **)(param_1 + 0x48))
                              (puVar2,param_1 + lVar6 + 0x50,*(long *)(param_1 + 0x78) + lVar6);
          } while ((uVar5 & 1) != 0);
        }
        goto code_r0x015a9dc4;
      }
    }
  }
code_r0x015a9d80:
  uVar5 = (**(code **)*puVar2)(puVar2,&uStack_44,*(long *)(param_1 + 0x78) + (long)iVar1 * 4);
  if ((uVar5 & 1) != 0) {
    *(int *)(param_1 + 0x84) = iVar1;
  }
code_r0x015a9dc4:
  lVar6 = *(long *)(param_1 + 0x28);
  *(int *)(param_1 + 8) = (int)lVar6;
  if (-1 < lVar6) {
    Aska::TArray<unsigned int, false>::Resize(long, bool)(param_1 + 0x10,lVar6 + 1,0);
    *(undefined4 *)(*(long *)(param_1 + 0x18) + lVar6 * 4) = 0;
  }
  return;
}


// FAILED to create function at 02ac6c98 AsonSerializer_Prepare::vtable
// FAILED to create function at 02ac6dc0 AsonSerializer_Prepare::typeinfo

// ==== SerializerImpl::_Serializer_Impl<KeyValuePair<SerializableArray<CPlayerCharacterCheatInfo_C2S> > >::Accept(_Serializer<SerializerImpl>&, KeyValuePair<SerializableArray<CPlayerCharacterCheatInfo_C2S> >&, unsigned int)
// vaddr 0x14ab1e8 | ghidra 0x15ab1e8 | size 340 | symbol _ZN14SerializerImpl16_Serializer_ImplI12KeyValuePairI17SerializableArrayI29CPlayerCharacterCheatInfo_C2SEEE6AcceptER11_SerializerIS_ERS5_j | lib libSOA-3.7.0.so | 2026-10-04
void _ZN14SerializerImpl16_Serializer_ImplI12KeyValuePairI17SerializableArrayI29CPlayerCharacterCheatInfo_C2SEEE6AcceptER11_SerializerIS_ERS5_j
               (long *param_1,undefined8 *param_2)

{
  long lVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  undefined8 uStack_68;
  undefined4 uStack_54;
  
  lVar1 = param_2[1];
  uVar2 = *(ulong *)(lVar1 + 0x18);
  (**(code **)(*param_1 + 0x70))(param_1,*param_2,uVar2 & 0xffffffff);
  if ((int)uVar2 != 0) {
    lVar4 = 0;
    uVar3 = 0;
    do {
      (**(code **)(*param_1 + 0xd0))(param_1,uVar3 & 0xffffffff);
      lVar5 = *(long *)(lVar1 + 8);
      (**(code **)(*param_1 + 0x60))(param_1);
      lVar5 = lVar5 + lVar4;
      uStack_54 = *(undefined4 *)(lVar5 + 0x38);
      (**(code **)*param_1)(param_1,&UNK_028ea11e/*"player_id"*/);
      (**(code **)(*param_1 + 0x30))(param_1,&uStack_54);
      uStack_68 = *(undefined8 *)(lVar5 + 0x68);
      (**(code **)*param_1)(param_1,&UNK_0282de66/*"character_id"*/);
      (**(code **)(*param_1 + 0x40))(param_1,&uStack_68);
      (**(code **)(*param_1 + 0x68))(param_1);
      (**(code **)(*param_1 + 0xd8))(param_1,uVar3 & 0xffffffff);
      uVar3 = uVar3 + 1;
      lVar4 = lVar4 + 0x70;
    } while ((uVar2 & 0xffffffff) != uVar3);
  }
  (**(code **)(*param_1 + 0xe0))(param_1,*param_2,uVar2 & 0xffffffff);
  return;
}

// ==== SerializerImpl::_Serializer_Impl<KeyValuePair<SerializableArray<CEnemyInfo> > >::Accept(_Serializer<SerializerImpl>&, KeyValuePair<SerializableArray<CEnemyInfo> >&, unsigned int)
// vaddr 0x14ab33c | ghidra 0x15ab33c | size 332 | symbol _ZN14SerializerImpl16_Serializer_ImplI12KeyValuePairI17SerializableArrayI10CEnemyInfoEEE6AcceptER11_SerializerIS_ERS5_j | lib libSOA-3.7.0.so | 2026-10-04
void _ZN14SerializerImpl16_Serializer_ImplI12KeyValuePairI17SerializableArrayI10CEnemyInfoEEE6AcceptER11_SerializerIS_ERS5_j
               (long *param_1,undefined8 *param_2)

{
  long lVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  undefined4 uStack_58;
  undefined4 uStack_54;
  
  lVar1 = param_2[1];
  uVar2 = *(ulong *)(lVar1 + 0x18);
  (**(code **)(*param_1 + 0x70))(param_1,*param_2,uVar2 & 0xffffffff);
  if ((int)uVar2 != 0) {
    lVar4 = 0;
    uVar3 = 0;
    do {
      (**(code **)(*param_1 + 0xd0))(param_1,uVar3 & 0xffffffff);
      lVar5 = *(long *)(lVar1 + 8);
      (**(code **)(*param_1 + 0x60))(param_1);
      lVar5 = lVar5 + lVar4;
      uStack_54 = *(undefined4 *)(lVar5 + 0x38);
      (**(code **)*param_1)(param_1,&UNK_027ffe64/*"id"*/);
      (**(code **)(*param_1 + 0x30))(param_1,&uStack_54);
      uStack_58 = *(undefined4 *)(lVar5 + 0x68);
      (**(code **)*param_1)(param_1,&UNK_0282e1a6/*"num"*/);
      (**(code **)(*param_1 + 0x30))(param_1,&uStack_58);
      (**(code **)(*param_1 + 0x68))(param_1);
      (**(code **)(*param_1 + 0xd8))(param_1,uVar3 & 0xffffffff);
      uVar3 = uVar3 + 1;
      lVar4 = lVar4 + 0x70;
    } while ((uVar2 & 0xffffffff) != uVar3);
  }
  (**(code **)(*param_1 + 0xe0))(param_1,*param_2,uVar2 & 0xffffffff);
  return;
}

// ==== SerializerImpl::_Serializer_Impl<KeyValuePair<SerializableArray<CBattleEvaluationInfo> > >::Accept(_Serializer<SerializerImpl>&, KeyValuePair<SerializableArray<CBattleEvaluationInfo> >&, unsigned int)
// vaddr 0x14ab488 | ghidra 0x15ab488 | size 340 | symbol _ZN14SerializerImpl16_Serializer_ImplI12KeyValuePairI17SerializableArrayI21CBattleEvaluationInfoEEE6AcceptER11_SerializerIS_ERS5_j | lib libSOA-3.7.0.so | 2026-10-04
void _ZN14SerializerImpl16_Serializer_ImplI12KeyValuePairI17SerializableArrayI21CBattleEvaluationInfoEEE6AcceptER11_SerializerIS_ERS5_j
               (long *param_1,undefined8 *param_2)

{
  long lVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  undefined8 uStack_68;
  undefined4 uStack_54;
  
  lVar1 = param_2[1];
  uVar2 = *(ulong *)(lVar1 + 0x18);
  (**(code **)(*param_1 + 0x70))(param_1,*param_2,uVar2 & 0xffffffff);
  if ((int)uVar2 != 0) {
    lVar4 = 0;
    uVar3 = 0;
    do {
      (**(code **)(*param_1 + 0xd0))(param_1,uVar3 & 0xffffffff);
      lVar5 = *(long *)(lVar1 + 8);
      (**(code **)(*param_1 + 0x60))(param_1);
      lVar5 = lVar5 + lVar4;
      uStack_54 = *(undefined4 *)(lVar5 + 0x38);
      (**(code **)*param_1)(param_1,&UNK_027e95d6/*"evaluation_type"*/);
      (**(code **)(*param_1 + 0x30))(param_1,&uStack_54);
      uStack_68 = *(undefined8 *)(lVar5 + 0x68);
      (**(code **)*param_1)(param_1,&UNK_02887d51/*"score"*/);
      (**(code **)(*param_1 + 0x40))(param_1,&uStack_68);
      (**(code **)(*param_1 + 0x68))(param_1);
      (**(code **)(*param_1 + 0xd8))(param_1,uVar3 & 0xffffffff);
      uVar3 = uVar3 + 1;
      lVar4 = lVar4 + 0x70;
    } while ((uVar2 & 0xffffffff) != uVar3);
  }
  (**(code **)(*param_1 + 0xe0))(param_1,*param_2,uVar2 & 0xffffffff);
  return;
}

// ==== _AsonSerializer::Serialize_Key(char const*)
// vaddr 0x14ab5dc | ghidra 0x15ab5dc | size 68 | symbol _ZN15_AsonSerializer13Serialize_KeyEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer13Serialize_KeyEPKc(long param_1,undefined8 param_2)

{
  long lVar1;
  uint uVar2;
  undefined1 auStack_8 [8];
  
  uVar2 = *(uint *)(*(long *)(param_1 + 0x50) + (long)*(int *)(param_1 + 8) * 4);
  if ((uVar2 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) &&
     (lVar1 = **(long **)(param_1 + 0x208) + (ulong)uVar2 * 0x40, lVar1 != 0)) {
    Aska::ASON::AValue::SetString(char const*, Aska::ASON*)(auStack_8,lVar1,param_2,*(undefined8 *)(param_1 + 0xc0));
  }
  return;
}

// ==== _AsonSerializer::Serialize_Value(bool&)
// vaddr 0x14ab620 | ghidra 0x15ab620 | size 76 | symbol _ZN15_AsonSerializer15Serialize_ValueERb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer15Serialize_ValueERb(long param_1,undefined1 *param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  
  iVar1 = *(int *)(param_1 + 8);
  lVar3 = *(long *)(param_1 + 0x50);
  uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  if (uVar2 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    lVar3 = **(long **)(param_1 + 0x208) + (ulong)uVar2 * 0x40;
    *(undefined4 *)(lVar3 + 0x20) = 1;
    *(undefined1 *)(lVar3 + 0x28) = *param_2;
    iVar1 = *(int *)(param_1 + 8);
    lVar3 = *(long *)(param_1 + 0x50);
    uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  }
  *(uint *)(lVar3 + (long)iVar1 * 4) = uVar2 + 1;
  return;
}

// ==== _AsonSerializer::Serialize_Value(unsigned char&)
// vaddr 0x14ab66c | ghidra 0x15ab66c | size 76 | symbol _ZN15_AsonSerializer15Serialize_ValueERh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer15Serialize_ValueERh(long param_1,byte *param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  
  iVar1 = *(int *)(param_1 + 8);
  lVar3 = *(long *)(param_1 + 0x50);
  uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  if (uVar2 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    lVar3 = **(long **)(param_1 + 0x208) + (ulong)uVar2 * 0x40;
    *(undefined4 *)(lVar3 + 0x20) = 2;
    *(ulong *)(lVar3 + 0x28) = (ulong)*param_2;
    iVar1 = *(int *)(param_1 + 8);
    lVar3 = *(long *)(param_1 + 0x50);
    uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  }
  *(uint *)(lVar3 + (long)iVar1 * 4) = uVar2 + 1;
  return;
}

// ==== _AsonSerializer::Serialize_Value(signed char&)
// vaddr 0x14ab6b8 | ghidra 0x15ab6b8 | size 76 | symbol _ZN15_AsonSerializer15Serialize_ValueERa | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer15Serialize_ValueERa(long param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  
  iVar1 = *(int *)(param_1 + 8);
  lVar3 = *(long *)(param_1 + 0x50);
  uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  if (uVar2 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    lVar3 = **(long **)(param_1 + 0x208) + (ulong)uVar2 * 0x40;
    *(undefined4 *)(lVar3 + 0x20) = 3;
    *(long *)(lVar3 + 0x28) = (long)*param_2;
    iVar1 = *(int *)(param_1 + 8);
    lVar3 = *(long *)(param_1 + 0x50);
    uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  }
  *(uint *)(lVar3 + (long)iVar1 * 4) = uVar2 + 1;
  return;
}

// ==== _AsonSerializer::Serialize_Value(unsigned short&)
// vaddr 0x14ab704 | ghidra 0x15ab704 | size 76 | symbol _ZN15_AsonSerializer15Serialize_ValueERt | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer15Serialize_ValueERt(long param_1,ushort *param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  
  iVar1 = *(int *)(param_1 + 8);
  lVar3 = *(long *)(param_1 + 0x50);
  uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  if (uVar2 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    lVar3 = **(long **)(param_1 + 0x208) + (ulong)uVar2 * 0x40;
    *(undefined4 *)(lVar3 + 0x20) = 2;
    *(ulong *)(lVar3 + 0x28) = (ulong)*param_2;
    iVar1 = *(int *)(param_1 + 8);
    lVar3 = *(long *)(param_1 + 0x50);
    uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  }
  *(uint *)(lVar3 + (long)iVar1 * 4) = uVar2 + 1;
  return;
}

// ==== _AsonSerializer::Serialize_Value(short&)
// vaddr 0x14ab750 | ghidra 0x15ab750 | size 76 | symbol _ZN15_AsonSerializer15Serialize_ValueERs | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer15Serialize_ValueERs(long param_1,short *param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  
  iVar1 = *(int *)(param_1 + 8);
  lVar3 = *(long *)(param_1 + 0x50);
  uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  if (uVar2 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    lVar3 = **(long **)(param_1 + 0x208) + (ulong)uVar2 * 0x40;
    *(undefined4 *)(lVar3 + 0x20) = 3;
    *(long *)(lVar3 + 0x28) = (long)*param_2;
    iVar1 = *(int *)(param_1 + 8);
    lVar3 = *(long *)(param_1 + 0x50);
    uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  }
  *(uint *)(lVar3 + (long)iVar1 * 4) = uVar2 + 1;
  return;
}

// ==== _AsonSerializer::Serialize_Value(unsigned int&)
// vaddr 0x14ab79c | ghidra 0x15ab79c | size 76 | symbol _ZN15_AsonSerializer15Serialize_ValueERj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer15Serialize_ValueERj(long param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  
  iVar1 = *(int *)(param_1 + 8);
  lVar3 = *(long *)(param_1 + 0x50);
  uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  if (uVar2 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    lVar3 = **(long **)(param_1 + 0x208) + (ulong)uVar2 * 0x40;
    *(undefined4 *)(lVar3 + 0x20) = 2;
    *(ulong *)(lVar3 + 0x28) = (ulong)*param_2;
    iVar1 = *(int *)(param_1 + 8);
    lVar3 = *(long *)(param_1 + 0x50);
    uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  }
  *(uint *)(lVar3 + (long)iVar1 * 4) = uVar2 + 1;
  return;
}

// ==== _AsonSerializer::Serialize_Value(int&)
// vaddr 0x14ab7e8 | ghidra 0x15ab7e8 | size 76 | symbol _ZN15_AsonSerializer15Serialize_ValueERi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer15Serialize_ValueERi(long param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  
  iVar1 = *(int *)(param_1 + 8);
  lVar3 = *(long *)(param_1 + 0x50);
  uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  if (uVar2 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    lVar3 = **(long **)(param_1 + 0x208) + (ulong)uVar2 * 0x40;
    *(undefined4 *)(lVar3 + 0x20) = 3;
    *(long *)(lVar3 + 0x28) = (long)*param_2;
    iVar1 = *(int *)(param_1 + 8);
    lVar3 = *(long *)(param_1 + 0x50);
    uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  }
  *(uint *)(lVar3 + (long)iVar1 * 4) = uVar2 + 1;
  return;
}

// ==== _AsonSerializer::Serialize_Value(unsigned long&)
// vaddr 0x14ab834 | ghidra 0x15ab834 | size 76 | symbol _ZN15_AsonSerializer15Serialize_ValueERm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer15Serialize_ValueERm(long param_1,undefined8 *param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  
  iVar1 = *(int *)(param_1 + 8);
  lVar3 = *(long *)(param_1 + 0x50);
  uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  if (uVar2 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    lVar3 = **(long **)(param_1 + 0x208) + (ulong)uVar2 * 0x40;
    *(undefined4 *)(lVar3 + 0x20) = 2;
    *(undefined8 *)(lVar3 + 0x28) = *param_2;
    iVar1 = *(int *)(param_1 + 8);
    lVar3 = *(long *)(param_1 + 0x50);
    uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  }
  *(uint *)(lVar3 + (long)iVar1 * 4) = uVar2 + 1;
  return;
}

// ==== _AsonSerializer::Serialize_Value(long&)
// vaddr 0x14ab880 | ghidra 0x15ab880 | size 76 | symbol _ZN15_AsonSerializer15Serialize_ValueERl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer15Serialize_ValueERl(long param_1,undefined8 *param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  
  iVar1 = *(int *)(param_1 + 8);
  lVar3 = *(long *)(param_1 + 0x50);
  uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  if (uVar2 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    lVar3 = **(long **)(param_1 + 0x208) + (ulong)uVar2 * 0x40;
    *(undefined4 *)(lVar3 + 0x20) = 3;
    *(undefined8 *)(lVar3 + 0x28) = *param_2;
    iVar1 = *(int *)(param_1 + 8);
    lVar3 = *(long *)(param_1 + 0x50);
    uVar2 = *(uint *)(lVar3 + (long)iVar1 * 4);
  }
  *(uint *)(lVar3 + (long)iVar1 * 4) = uVar2 + 1;
  return;
}

// ==== _AsonSerializer::Serialize_Value(float&)
// vaddr 0x14ab8cc | ghidra 0x15ab8cc | size 80 | symbol _ZN15_AsonSerializer15Serialize_ValueERf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer15Serialize_ValueERf(long param_1,float *param_2)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  float fVar4;
  
  iVar2 = *(int *)(param_1 + 8);
  lVar3 = *(long *)(param_1 + 0x50);
  uVar1 = *(uint *)(lVar3 + (long)iVar2 * 4);
  if (uVar1 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    fVar4 = *param_2;
    lVar3 = **(long **)(param_1 + 0x208) + (ulong)uVar1 * 0x40;
    *(undefined4 *)(lVar3 + 0x20) = 4;
    *(double *)(lVar3 + 0x28) = (double)fVar4;
    iVar2 = *(int *)(param_1 + 8);
    lVar3 = *(long *)(param_1 + 0x50);
    uVar1 = *(uint *)(lVar3 + (long)iVar2 * 4);
  }
  *(uint *)(lVar3 + (long)iVar2 * 4) = uVar1 + 1;
  return;
}

// ==== _AsonSerializer::Serialize_Value(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >&)
// vaddr 0x14ab91c | ghidra 0x15ab91c | size 112 | symbol _ZN15_AsonSerializer15Serialize_ValueERNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer15Serialize_ValueERNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE
               (long param_1,byte *param_2)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  byte *pbVar4;
  undefined1 auStack_18 [8];
  
  iVar2 = *(int *)(param_1 + 8);
  lVar3 = *(long *)(param_1 + 0x50);
  uVar1 = *(uint *)(lVar3 + (long)iVar2 * 4);
  if (uVar1 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    pbVar4 = *(byte **)(param_2 + 0x10);
    if ((*param_2 & 1) == 0) {
      pbVar4 = param_2 + 1;
    }
    Aska::ASON::AValue::SetString(char const*, Aska::ASON*)(auStack_18,**(long **)(param_1 + 0x208) + (ulong)uVar1 * 0x40 + 0x20,pbVar4,
                    *(undefined8 *)(param_1 + 0xc0));
    iVar2 = *(int *)(param_1 + 8);
    lVar3 = *(long *)(param_1 + 0x50);
    uVar1 = *(uint *)(lVar3 + (long)iVar2 * 4);
  }
  *(uint *)(lVar3 + (long)iVar2 * 4) = uVar1 + 1;
  return;
}

// ==== _AsonSerializer::Serialize_StartObject()
// vaddr 0x14ab98c | ghidra 0x15ab98c | size 748 | symbol _ZN15_AsonSerializer21Serialize_StartObjectEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer21Serialize_StartObjectEv(long param_1)

{
  int iVar1;
  undefined8 *puVar2;
  long *plVar3;
  int iVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  ulong uVar7;
  long lVar8;
  long lVar9;
  int iVar10;
  long lVar11;
  undefined1 auStack_48 [8];
  
  _AsonSerializer::Increment()();
  iVar10 = *(int *)(param_1 + 0x134);
  iVar4 = *(int *)(param_1 + 0x130);
  puVar2 = (undefined8 *)(param_1 + 0xd0);
  iVar1 = iVar10 + 1;
  if (iVar1 < iVar4) {
code_r0x015ab9c4:
    uVar7 = (**(code **)*puVar2)(puVar2,param_1 + 200,*(long *)(param_1 + 0x128) + (long)iVar1 * 8);
    if ((uVar7 & 1) != 0) {
      *(int *)(param_1 + 0x134) = iVar1;
    }
  }
  else {
    lVar9 = *(long *)(param_1 + 0x128);
    plVar3 = (long *)(param_1 + 0x128);
    lVar8 = param_1 + 0xd8;
    if (iVar4 < 1) {
      if (lVar9 != lVar8) {
        if (lVar9 != 0) {
          operator delete[](void*)(lVar9);
          iVar10 = *(int *)(param_1 + 0x134);
        }
        *plVar3 = lVar8;
      }
      *(undefined4 *)(param_1 + 0x130) = 10;
      if (9 < iVar10) {
        *(undefined4 *)(param_1 + 0x134) = 9;
      }
      goto code_r0x015ab9c4;
    }
    if (lVar9 == lVar8) {
      uVar7 = (long)iVar4 << 4;
      auVar5._8_8_ = 0;
      auVar5._0_8_ = uVar7;
      lVar8 = (long)iVar4 << 7;
      if (SUB168(auVar5 * ZEXT816(8),8) != 0) {
        lVar8 = -1;
      }
      lVar8 = operator new[](unsigned long, std::nothrow_t const&)(lVar8,PTR__ZSt7nothrow_02cb9a80);
      *plVar3 = lVar8;
      if (lVar8 == 0) {
        *plVar3 = lVar9;
      }
      else {
        *(int *)(param_1 + 0x130) = (int)uVar7;
        if (iVar10 < 0) goto code_r0x015ab9c4;
        lVar9 = (long)iVar10;
        lVar11 = lVar9 * 8;
        uVar7 = (*(code *)**(undefined8 **)(param_1 + 0xd0))
                          (puVar2,(undefined8 *)(param_1 + 0xd0) + lVar9 + 1,lVar8 + lVar11);
        if ((uVar7 & 1) != 0) {
          lVar9 = lVar9 + 1;
          do {
            lVar11 = lVar11 + -8;
            lVar9 = lVar9 + -1;
            if (lVar9 < 1) goto code_r0x015ab9c4;
            uVar7 = (*(code *)**(undefined8 **)(param_1 + 0xd0))
                              (puVar2,param_1 + lVar11 + 0xd8,*(long *)(param_1 + 0x128) + lVar11);
          } while ((uVar7 & 1) != 0);
        }
      }
    }
  }
  iVar10 = *(int *)(param_1 + 0x19c);
  iVar4 = *(int *)(param_1 + 0x198);
  puVar2 = (undefined8 *)(param_1 + 0x138);
  iVar1 = iVar10 + 1;
  if (iVar4 <= iVar1) {
    lVar9 = *(long *)(param_1 + 400);
    plVar3 = (long *)(param_1 + 400);
    lVar8 = param_1 + 0x140;
    if (iVar4 < 1) {
      if (lVar9 != lVar8) {
        if (lVar9 != 0) {
          operator delete[](void*)(lVar9);
          iVar10 = *(int *)(param_1 + 0x19c);
        }
        *plVar3 = lVar8;
      }
      *(undefined4 *)(param_1 + 0x198) = 10;
      if (9 < iVar10) {
        *(undefined4 *)(param_1 + 0x19c) = 9;
      }
    }
    else {
      if (lVar9 != lVar8) goto code_r0x015aba68;
      uVar7 = (long)iVar4 << 4;
      auVar6._8_8_ = 0;
      auVar6._0_8_ = uVar7;
      lVar8 = (long)iVar4 << 7;
      if (SUB168(auVar6 * ZEXT816(8),8) != 0) {
        lVar8 = -1;
      }
      lVar8 = operator new[](unsigned long, std::nothrow_t const&)(lVar8,PTR__ZSt7nothrow_02cb9a80);
      *plVar3 = lVar8;
      if (lVar8 == 0) {
        *plVar3 = lVar9;
        goto code_r0x015aba68;
      }
      *(int *)(param_1 + 0x198) = (int)uVar7;
      if (-1 < iVar10) {
        lVar9 = (long)iVar10 * 8;
        uVar7 = (*(code *)**(undefined8 **)(param_1 + 0x138))
                          (puVar2,param_1 + lVar9 + 0x140,lVar8 + lVar9);
        if ((uVar7 & 1) != 0) {
          lVar8 = (long)iVar10 + 1;
          do {
            lVar9 = lVar9 + -8;
            lVar8 = lVar8 + -1;
            if (lVar8 < 1) goto code_r0x015aba24;
            uVar7 = (*(code *)**(undefined8 **)(param_1 + 0x138))
                              (puVar2,param_1 + lVar9 + 0x140,*(long *)(param_1 + 400) + lVar9);
          } while ((uVar7 & 1) != 0);
        }
        goto code_r0x015aba68;
      }
    }
  }
code_r0x015aba24:
  uVar7 = (**(code **)*puVar2)(puVar2,param_1 + 0x208,*(long *)(param_1 + 400) + (long)iVar1 * 8);
  if ((uVar7 & 1) != 0) {
    *(int *)(param_1 + 0x19c) = iVar1;
  }
code_r0x015aba68:
  Aska::ASON::MakeAValue_Map(Aska::ASON::AValue*, unsigned int)(auStack_48,*(undefined8 *)(param_1 + 0xc0),*(undefined8 *)(param_1 + 200),
                  *(int *)(*(long *)(param_1 + 0x18) + (long)*(int *)(param_1 + 8) * 4) -
                  (uint)((long)*(int *)(param_1 + 8) == 0));
  *(long *)(param_1 + 0x208) = *(long *)(param_1 + 200) + 8;
  return;
}

// ==== _AsonSerializer::Serialize_EndObject()
// vaddr 0x14abc78 | ghidra 0x15abc78 | size 96 | symbol _ZN15_AsonSerializer19Serialize_EndObjectEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer19Serialize_EndObjectEv(long param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  undefined8 uVar5;
  
  iVar1 = *(int *)(param_1 + 0xbc);
  iVar2 = *(int *)(param_1 + 0x134);
  *(int *)(param_1 + 0xbc) = iVar1 + -1;
  iVar3 = *(int *)(*(long *)(param_1 + 0xb0) + (long)iVar1 * 4);
  iVar1 = *(int *)(param_1 + 0x19c);
  *(int *)(param_1 + 0x134) = iVar2 + -1;
  *(int *)(param_1 + 8) = iVar3;
  uVar5 = *(undefined8 *)(*(long *)(param_1 + 0x128) + (long)iVar2 * 8);
  *(int *)(param_1 + 0x19c) = iVar1 + -1;
  *(undefined8 *)(param_1 + 200) = uVar5;
  lVar4 = (long)iVar3 * 4;
  *(undefined8 *)(param_1 + 0x208) = *(undefined8 *)(*(long *)(param_1 + 400) + (long)iVar1 * 8);
  *(int *)(*(long *)(param_1 + 0x50) + lVar4) = *(int *)(*(long *)(param_1 + 0x50) + lVar4) + 1;
  return;
}

// ==== _AsonSerializer::Serialize_StartArray(char const*, unsigned int)
// vaddr 0x14abcd8 | ghidra 0x15abcd8 | size 536 | symbol _ZN15_AsonSerializer20Serialize_StartArrayEPKcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer20Serialize_StartArrayEPKcj(long param_1,undefined8 param_2)

{
  int iVar1;
  undefined8 *puVar2;
  long *plVar3;
  uint uVar4;
  int iVar5;
  undefined1 auVar6 [16];
  ulong uVar7;
  long lVar8;
  long lVar9;
  int iVar10;
  undefined1 auStack_50 [8];
  undefined1 auStack_48 [8];
  
  uVar4 = *(uint *)(*(long *)(param_1 + 0x50) + (long)*(int *)(param_1 + 8) * 4);
  if (uVar4 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    lVar8 = **(long **)(param_1 + 0x208) + (ulong)uVar4 * 0x40;
  }
  else {
    lVar8 = 0;
  }
  Aska::ASON::AValue::SetString(char const*, Aska::ASON*)(auStack_48,lVar8,param_2,*(undefined8 *)(param_1 + 0xc0));
  uVar4 = *(uint *)(*(long *)(param_1 + 0x50) + (long)*(int *)(param_1 + 8) * 4);
  if (uVar4 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    lVar8 = **(long **)(param_1 + 0x208) + (ulong)uVar4 * 0x40 + 0x20;
  }
  else {
    lVar8 = 0;
  }
  *(long *)(param_1 + 200) = lVar8;
  _AsonSerializer::Increment()(param_1);
  iVar10 = *(int *)(param_1 + 0x204);
  iVar5 = *(int *)(param_1 + 0x200);
  puVar2 = (undefined8 *)(param_1 + 0x1a0);
  iVar1 = iVar10 + 1;
  if (iVar5 <= iVar1) {
    lVar9 = *(long *)(param_1 + 0x1f8);
    plVar3 = (long *)(param_1 + 0x1f8);
    lVar8 = param_1 + 0x1a8;
    if (iVar5 < 1) {
      if (lVar9 != lVar8) {
        if (lVar9 != 0) {
          operator delete[](void*)(lVar9);
          iVar10 = *(int *)(param_1 + 0x204);
        }
        *plVar3 = lVar8;
      }
      *(undefined4 *)(param_1 + 0x200) = 10;
      if (9 < iVar10) {
        *(undefined4 *)(param_1 + 0x204) = 9;
      }
    }
    else {
      if (lVar9 != lVar8) goto code_r0x015abdc4;
      uVar7 = (long)iVar5 << 4;
      auVar6._8_8_ = 0;
      auVar6._0_8_ = uVar7;
      lVar8 = (long)iVar5 << 7;
      if (SUB168(auVar6 * ZEXT816(8),8) != 0) {
        lVar8 = -1;
      }
      lVar8 = operator new[](unsigned long, std::nothrow_t const&)(lVar8,PTR__ZSt7nothrow_02cb9a80);
      *plVar3 = lVar8;
      if (lVar8 == 0) {
        *plVar3 = lVar9;
        goto code_r0x015abdc4;
      }
      *(int *)(param_1 + 0x200) = (int)uVar7;
      if (-1 < iVar10) {
        lVar9 = (long)iVar10 * 8;
        uVar7 = (*(code *)**(undefined8 **)(param_1 + 0x1a0))
                          (puVar2,param_1 + lVar9 + 0x1a8,lVar8 + lVar9);
        if ((uVar7 & 1) != 0) {
          lVar8 = (long)iVar10 + 1;
          do {
            lVar9 = lVar9 + -8;
            lVar8 = lVar8 + -1;
            if (lVar8 < 1) goto code_r0x015abd80;
            uVar7 = (*(code *)**(undefined8 **)(param_1 + 0x1a0))
                              (puVar2,param_1 + lVar9 + 0x1a8,*(long *)(param_1 + 0x1f8) + lVar9);
          } while ((uVar7 & 1) != 0);
        }
        goto code_r0x015abdc4;
      }
    }
  }
code_r0x015abd80:
  uVar7 = (**(code **)*puVar2)(puVar2,param_1 + 0x210,*(long *)(param_1 + 0x1f8) + (long)iVar1 * 8);
  if ((uVar7 & 1) != 0) {
    *(int *)(param_1 + 0x204) = iVar1;
  }
code_r0x015abdc4:
  Aska::ASON::MakeAValue_Array(Aska::ASON::AValue*, unsigned int)(auStack_50,*(undefined8 *)(param_1 + 0xc0),*(undefined8 *)(param_1 + 200),
                  *(int *)(*(long *)(param_1 + 0x18) + (long)*(int *)(param_1 + 8) * 4) -
                  (uint)((long)*(int *)(param_1 + 8) == 0));
  *(long *)(param_1 + 0x210) = *(long *)(param_1 + 200) + 8;
  return;
}

// ==== _AsonSerializer::Serialize_ArrayValue(bool&)
// vaddr 0x14abef0 | ghidra 0x15abef0 | size 48 | symbol _ZN15_AsonSerializer20Serialize_ArrayValueERb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer20Serialize_ArrayValueERb(long param_1,undefined1 *param_2)

{
  undefined4 *puVar1;
  long lVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 200);
  *puVar1 = 1;
  *(undefined1 *)(puVar1 + 2) = *param_2;
  lVar2 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x50) + lVar2) = *(int *)(*(long *)(param_1 + 0x50) + lVar2) + 1;
  return;
}

// ==== _AsonSerializer::Serialize_ArrayValue(unsigned char&)
// vaddr 0x14abf20 | ghidra 0x15abf20 | size 48 | symbol _ZN15_AsonSerializer20Serialize_ArrayValueERh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer20Serialize_ArrayValueERh(long param_1,byte *param_2)

{
  undefined4 *puVar1;
  long lVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 200);
  *puVar1 = 2;
  *(ulong *)(puVar1 + 2) = (ulong)*param_2;
  lVar2 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x50) + lVar2) = *(int *)(*(long *)(param_1 + 0x50) + lVar2) + 1;
  return;
}

// ==== _AsonSerializer::Serialize_ArrayValue(signed char&)
// vaddr 0x14abf50 | ghidra 0x15abf50 | size 48 | symbol _ZN15_AsonSerializer20Serialize_ArrayValueERa | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer20Serialize_ArrayValueERa(long param_1,char *param_2)

{
  undefined4 *puVar1;
  long lVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 200);
  *puVar1 = 3;
  *(long *)(puVar1 + 2) = (long)*param_2;
  lVar2 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x50) + lVar2) = *(int *)(*(long *)(param_1 + 0x50) + lVar2) + 1;
  return;
}

// ==== _AsonSerializer::Serialize_ArrayValue(unsigned short&)
// vaddr 0x14abf80 | ghidra 0x15abf80 | size 48 | symbol _ZN15_AsonSerializer20Serialize_ArrayValueERt | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer20Serialize_ArrayValueERt(long param_1,ushort *param_2)

{
  undefined4 *puVar1;
  long lVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 200);
  *puVar1 = 2;
  *(ulong *)(puVar1 + 2) = (ulong)*param_2;
  lVar2 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x50) + lVar2) = *(int *)(*(long *)(param_1 + 0x50) + lVar2) + 1;
  return;
}

// ==== _AsonSerializer::Serialize_ArrayValue(short&)
// vaddr 0x14abfb0 | ghidra 0x15abfb0 | size 48 | symbol _ZN15_AsonSerializer20Serialize_ArrayValueERs | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer20Serialize_ArrayValueERs(long param_1,short *param_2)

{
  undefined4 *puVar1;
  long lVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 200);
  *puVar1 = 3;
  *(long *)(puVar1 + 2) = (long)*param_2;
  lVar2 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x50) + lVar2) = *(int *)(*(long *)(param_1 + 0x50) + lVar2) + 1;
  return;
}

// ==== _AsonSerializer::Serialize_ArrayValue(unsigned int&)
// vaddr 0x14abfe0 | ghidra 0x15abfe0 | size 48 | symbol _ZN15_AsonSerializer20Serialize_ArrayValueERj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer20Serialize_ArrayValueERj(long param_1,uint *param_2)

{
  undefined4 *puVar1;
  long lVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 200);
  *puVar1 = 2;
  *(ulong *)(puVar1 + 2) = (ulong)*param_2;
  lVar2 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x50) + lVar2) = *(int *)(*(long *)(param_1 + 0x50) + lVar2) + 1;
  return;
}

// ==== _AsonSerializer::Serialize_ArrayValue(int&)
// vaddr 0x14ac010 | ghidra 0x15ac010 | size 48 | symbol _ZN15_AsonSerializer20Serialize_ArrayValueERi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer20Serialize_ArrayValueERi(long param_1,int *param_2)

{
  undefined4 *puVar1;
  long lVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 200);
  *puVar1 = 3;
  *(long *)(puVar1 + 2) = (long)*param_2;
  lVar2 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x50) + lVar2) = *(int *)(*(long *)(param_1 + 0x50) + lVar2) + 1;
  return;
}

// ==== _AsonSerializer::Serialize_ArrayValue(unsigned long&)
// vaddr 0x14ac040 | ghidra 0x15ac040 | size 48 | symbol _ZN15_AsonSerializer20Serialize_ArrayValueERm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer20Serialize_ArrayValueERm(long param_1,undefined8 *param_2)

{
  undefined4 *puVar1;
  long lVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 200);
  *puVar1 = 2;
  *(undefined8 *)(puVar1 + 2) = *param_2;
  lVar2 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x50) + lVar2) = *(int *)(*(long *)(param_1 + 0x50) + lVar2) + 1;
  return;
}

// ==== _AsonSerializer::Serialize_ArrayValue(long&)
// vaddr 0x14ac070 | ghidra 0x15ac070 | size 48 | symbol _ZN15_AsonSerializer20Serialize_ArrayValueERl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer20Serialize_ArrayValueERl(long param_1,undefined8 *param_2)

{
  undefined4 *puVar1;
  long lVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 200);
  *puVar1 = 3;
  *(undefined8 *)(puVar1 + 2) = *param_2;
  lVar2 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x50) + lVar2) = *(int *)(*(long *)(param_1 + 0x50) + lVar2) + 1;
  return;
}

// ==== _AsonSerializer::Serialize_ArrayValue(float&)
// vaddr 0x14ac0a0 | ghidra 0x15ac0a0 | size 52 | symbol _ZN15_AsonSerializer20Serialize_ArrayValueERf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer20Serialize_ArrayValueERf(long param_1,float *param_2)

{
  undefined4 *puVar1;
  long lVar2;
  float fVar3;
  
  fVar3 = *param_2;
  puVar1 = *(undefined4 **)(param_1 + 200);
  *puVar1 = 4;
  *(double *)(puVar1 + 2) = (double)fVar3;
  lVar2 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x50) + lVar2) = *(int *)(*(long *)(param_1 + 0x50) + lVar2) + 1;
  return;
}

// ==== _AsonSerializer::Serialize_ArrayValue(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >&)
// vaddr 0x14ac0d4 | ghidra 0x15ac0d4 | size 76 | symbol _ZN15_AsonSerializer20Serialize_ArrayValueERNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer20Serialize_ArrayValueERNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE
               (long param_1,byte *param_2)

{
  long lVar1;
  byte *pbVar2;
  undefined1 auStack_18 [8];
  
  pbVar2 = *(byte **)(param_2 + 0x10);
  if ((*param_2 & 1) == 0) {
    pbVar2 = param_2 + 1;
  }
  Aska::ASON::AValue::SetString(char const*, Aska::ASON*)(auStack_18,*(undefined8 *)(param_1 + 200),pbVar2,*(undefined8 *)(param_1 + 0xc0));
  lVar1 = (long)*(int *)(param_1 + 8) * 4;
  *(int *)(*(long *)(param_1 + 0x50) + lVar1) = *(int *)(*(long *)(param_1 + 0x50) + lVar1) + 1;
  return;
}

// ==== _AsonSerializer::Serialize_StartArrayObject(unsigned int)
// vaddr 0x14ac120 | ghidra 0x15ac120 | size 48 | symbol _ZN15_AsonSerializer26Serialize_StartArrayObjectEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer26Serialize_StartArrayObjectEj(long param_1,uint param_2)

{
  if (param_2 < *(uint *)(*(long **)(param_1 + 0x210) + 1)) {
    *(ulong *)(param_1 + 200) = **(long **)(param_1 + 0x210) + (ulong)param_2 * 0x20;
    return;
  }
  *(undefined8 *)(param_1 + 200) = 0;
  return;
}

// ==== _AsonSerializer::Serialize_EndArrayObject(unsigned int)
// vaddr 0x14ac150 | ghidra 0x15ac150 | size 4 | symbol _ZN15_AsonSerializer24Serialize_EndArrayObjectEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer24Serialize_EndArrayObjectEj(void)

{
  return;
}

// ==== _AsonSerializer::Serialize_EndArray(char const*, unsigned int)
// vaddr 0x14ac154 | ghidra 0x15ac154 | size 72 | symbol _ZN15_AsonSerializer18Serialize_EndArrayEPKcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer18Serialize_EndArrayEPKcj(long param_1)

{
  int iVar1;
  long lVar2;
  
  iVar1 = *(int *)(param_1 + 0xbc);
  *(int *)(param_1 + 0xbc) = iVar1 + -1;
  iVar1 = *(int *)(*(long *)(param_1 + 0xb0) + (long)iVar1 * 4);
  *(int *)(param_1 + 8) = iVar1;
  lVar2 = (long)iVar1 * 4;
  *(int *)(*(long *)(param_1 + 0x50) + lVar2) = *(int *)(*(long *)(param_1 + 0x50) + lVar2) + 1;
  iVar1 = *(int *)(param_1 + 0x204);
  *(int *)(param_1 + 0x204) = iVar1 + -1;
  *(undefined8 *)(param_1 + 0x210) = *(undefined8 *)(*(long *)(param_1 + 0x1f8) + (long)iVar1 * 8);
  return;
}

// ==== _AsonSerializer::Serialize_StartMap(char const*, unsigned int)
// vaddr 0x14ac19c | ghidra 0x15ac19c | size 540 | symbol _ZN15_AsonSerializer18Serialize_StartMapEPKcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer18Serialize_StartMapEPKcj(long param_1,undefined8 param_2)

{
  int iVar1;
  undefined8 *puVar2;
  long *plVar3;
  uint uVar4;
  int iVar5;
  undefined1 auVar6 [16];
  ulong uVar7;
  long lVar8;
  long lVar9;
  int iVar10;
  undefined1 auStack_50 [8];
  undefined1 auStack_48 [8];
  
  uVar4 = *(uint *)(*(long *)(param_1 + 0x50) + (long)*(int *)(param_1 + 8) * 4);
  if (uVar4 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    lVar8 = **(long **)(param_1 + 0x208) + (ulong)uVar4 * 0x40;
  }
  else {
    lVar8 = 0;
  }
  Aska::ASON::AValue::SetString(char const*, Aska::ASON*)(auStack_48,lVar8,param_2,*(undefined8 *)(param_1 + 0xc0));
  uVar4 = *(uint *)(*(long *)(param_1 + 0x50) + (long)*(int *)(param_1 + 8) * 4);
  if (uVar4 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    lVar8 = **(long **)(param_1 + 0x208) + (ulong)uVar4 * 0x40 + 0x20;
  }
  else {
    lVar8 = 0;
  }
  *(long *)(param_1 + 200) = lVar8;
  _AsonSerializer::Increment()(param_1);
  iVar10 = *(int *)(param_1 + 0x19c);
  iVar5 = *(int *)(param_1 + 0x198);
  puVar2 = (undefined8 *)(param_1 + 0x138);
  iVar1 = iVar10 + 1;
  if (iVar5 <= iVar1) {
    lVar9 = *(long *)(param_1 + 400);
    plVar3 = (long *)(param_1 + 400);
    lVar8 = param_1 + 0x140;
    if (iVar5 < 1) {
      if (lVar9 != lVar8) {
        if (lVar9 != 0) {
          operator delete[](void*)(lVar9);
          iVar10 = *(int *)(param_1 + 0x19c);
        }
        *plVar3 = lVar8;
      }
      *(undefined4 *)(param_1 + 0x198) = 10;
      if (9 < iVar10) {
        *(undefined4 *)(param_1 + 0x19c) = 9;
      }
    }
    else {
      if (lVar9 != lVar8) goto code_r0x015ac288;
      uVar7 = (long)iVar5 << 4;
      auVar6._8_8_ = 0;
      auVar6._0_8_ = uVar7;
      lVar8 = (long)iVar5 << 7;
      if (SUB168(auVar6 * ZEXT816(8),8) != 0) {
        lVar8 = -1;
      }
      lVar8 = operator new[](unsigned long, std::nothrow_t const&)(lVar8,PTR__ZSt7nothrow_02cb9a80);
      *plVar3 = lVar8;
      if (lVar8 == 0) {
        *plVar3 = lVar9;
        goto code_r0x015ac288;
      }
      *(int *)(param_1 + 0x198) = (int)uVar7;
      if (-1 < iVar10) {
        lVar9 = (long)iVar10 * 8;
        uVar7 = (*(code *)**(undefined8 **)(param_1 + 0x138))
                          (puVar2,param_1 + lVar9 + 0x140,lVar8 + lVar9);
        if ((uVar7 & 1) != 0) {
          lVar8 = (long)iVar10 + 1;
          do {
            lVar9 = lVar9 + -8;
            lVar8 = lVar8 + -1;
            if (lVar8 < 1) goto code_r0x015ac244;
            uVar7 = (*(code *)**(undefined8 **)(param_1 + 0x138))
                              (puVar2,param_1 + lVar9 + 0x140,*(long *)(param_1 + 400) + lVar9);
          } while ((uVar7 & 1) != 0);
        }
        goto code_r0x015ac288;
      }
    }
  }
code_r0x015ac244:
  uVar7 = (**(code **)*puVar2)(puVar2,param_1 + 0x208,*(long *)(param_1 + 400) + (long)iVar1 * 8);
  if ((uVar7 & 1) != 0) {
    *(int *)(param_1 + 0x19c) = iVar1;
  }
code_r0x015ac288:
  iVar1 = *(int *)(*(long *)(param_1 + 0x18) + (long)*(int *)(param_1 + 8) * 4) -
          (uint)((long)*(int *)(param_1 + 8) == 0);
  if (iVar1 == 0) {
    iVar1 = 1;
  }
  Aska::ASON::MakeAValue_Map(Aska::ASON::AValue*, unsigned int)(auStack_50,*(undefined8 *)(param_1 + 0xc0),*(undefined8 *)(param_1 + 200),iVar1);
  *(long *)(param_1 + 0x208) = *(long *)(param_1 + 200) + 8;
  return;
}

// ==== _AsonSerializer::Serialize_StartMapObject(char const*, unsigned int)
// vaddr 0x14ac3b8 | ghidra 0x15ac3b8 | size 120 | symbol _ZN15_AsonSerializer24Serialize_StartMapObjectEPKcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer24Serialize_StartMapObjectEPKcj
               (long param_1,undefined8 param_2,uint param_3)

{
  long lVar1;
  undefined1 auStack_18 [8];
  
  if (param_3 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    lVar1 = **(long **)(param_1 + 0x208) + (ulong)param_3 * 0x40;
  }
  else {
    lVar1 = 0;
  }
  Aska::ASON::AValue::SetString(char const*, Aska::ASON*)(auStack_18,lVar1,param_2,*(undefined8 *)(param_1 + 0xc0));
  if (param_3 < *(uint *)(*(long **)(param_1 + 0x208) + 1)) {
    lVar1 = **(long **)(param_1 + 0x208) + (ulong)param_3 * 0x40 + 0x20;
  }
  else {
    lVar1 = 0;
  }
  *(long *)(param_1 + 200) = lVar1;
  return;
}

// ==== _AsonSerializer::Serialize_EndMapObject(char const*, unsigned int)
// vaddr 0x14ac430 | ghidra 0x15ac430 | size 4 | symbol _ZN15_AsonSerializer22Serialize_EndMapObjectEPKcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer22Serialize_EndMapObjectEPKcj(void)

{
  return;
}

// ==== _AsonSerializer::Serialize_EndMap(char const*, unsigned int)
// vaddr 0x14ac434 | ghidra 0x15ac434 | size 72 | symbol _ZN15_AsonSerializer16Serialize_EndMapEPKcj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer16Serialize_EndMapEPKcj(long param_1)

{
  int iVar1;
  long lVar2;
  
  iVar1 = *(int *)(param_1 + 0xbc);
  *(int *)(param_1 + 0xbc) = iVar1 + -1;
  iVar1 = *(int *)(*(long *)(param_1 + 0xb0) + (long)iVar1 * 4);
  *(int *)(param_1 + 8) = iVar1;
  lVar2 = (long)iVar1 * 4;
  *(int *)(*(long *)(param_1 + 0x50) + lVar2) = *(int *)(*(long *)(param_1 + 0x50) + lVar2) + 1;
  iVar1 = *(int *)(param_1 + 0x19c);
  *(int *)(param_1 + 0x19c) = iVar1 + -1;
  *(undefined8 *)(param_1 + 0x208) = *(undefined8 *)(*(long *)(param_1 + 400) + (long)iVar1 * 8);
  return;
}

// ==== _AsonSerializer::Increment()
// vaddr 0x14ac650 | ghidra 0x15ac650 | size 416 | symbol _ZN15_AsonSerializer9IncrementEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN15_AsonSerializer9IncrementEv(long param_1)

{
  int iVar1;
  undefined8 *puVar2;
  int iVar3;
  undefined1 auVar4 [16];
  ulong uVar5;
  long lVar6;
  long *plVar7;
  int iVar8;
  long lVar9;
  undefined4 uStack_44;
  
  uStack_44 = *(undefined4 *)(param_1 + 8);
  puVar2 = (undefined8 *)(param_1 + 0x80);
  iVar3 = *(int *)(param_1 + 0xb8);
  iVar8 = *(int *)(param_1 + 0xbc);
  iVar1 = iVar8 + 1;
  if (iVar3 <= iVar1) {
    plVar7 = (long *)(param_1 + 0xb0);
    lVar6 = *plVar7;
    lVar9 = param_1 + 0x88;
    if (iVar3 < 1) {
      if (lVar6 != lVar9) {
        if (lVar6 != 0) {
          operator delete[](void*)(lVar6);
          iVar8 = *(int *)(param_1 + 0xbc);
        }
        *plVar7 = lVar9;
      }
      *(undefined4 *)(param_1 + 0xb8) = 10;
      if (9 < iVar8) {
        *(undefined4 *)(param_1 + 0xbc) = 9;
      }
    }
    else {
      if (lVar6 != lVar9) goto code_r0x015ac6d0;
      uVar5 = (long)iVar3 << 4;
      auVar4._8_8_ = 0;
      auVar4._0_8_ = uVar5;
      lVar9 = (long)iVar3 << 6;
      if (SUB168(auVar4 * ZEXT816(4),8) != 0) {
        lVar9 = -1;
      }
      lVar9 = operator new[](unsigned long, std::nothrow_t const&)(lVar9,PTR__ZSt7nothrow_02cb9a80);
      *plVar7 = lVar9;
      if (lVar9 == 0) {
        *plVar7 = lVar6;
        goto code_r0x015ac6d0;
      }
      *(int *)(param_1 + 0xb8) = (int)uVar5;
      if (-1 < iVar8) {
        lVar6 = (long)iVar8 * 4;
        uVar5 = (*(code *)**(undefined8 **)(param_1 + 0x80))
                          (puVar2,(long)(param_1 + 0x80) + lVar6 + 8,lVar9 + lVar6);
        if ((uVar5 & 1) != 0) {
          lVar9 = (long)iVar8 + 1;
          do {
            lVar6 = lVar6 + -4;
            lVar9 = lVar9 + -1;
            if (lVar9 < 1) goto code_r0x015ac68c;
            uVar5 = (*(code *)**(undefined8 **)(param_1 + 0x80))
                              (puVar2,param_1 + lVar6 + 0x88,*(long *)(param_1 + 0xb0) + lVar6);
          } while ((uVar5 & 1) != 0);
        }
        goto code_r0x015ac6d0;
      }
    }
  }
code_r0x015ac68c:
  uVar5 = (**(code **)*puVar2)(puVar2,&uStack_44,*(long *)(param_1 + 0xb0) + (long)iVar1 * 4);
  if ((uVar5 & 1) != 0) {
    *(int *)(param_1 + 0xbc) = iVar1;
  }
code_r0x015ac6d0:
  lVar6 = *(long *)(param_1 + 0x60);
  *(int *)(param_1 + 8) = (int)lVar6;
  if (-1 < lVar6) {
    Aska::TArray<unsigned int, false>::Resize(long, bool)(param_1 + 0x48,lVar6 + 1,0);
    *(undefined4 *)(*(long *)(param_1 + 0x50) + lVar6 * 4) = 0;
  }
  return;
}

// ==== SerializerImpl::_Serializer_Impl<KeyValuePair<SerializableMap<CAssetInfo> > >::Accept(_Serializer<SerializerImpl>&, KeyValuePair<SerializableMap<CAssetInfo> >&, unsigned int)
// vaddr 0x17f5e10 | ghidra 0x18f5e10 | size 328 | symbol _ZN14SerializerImpl16_Serializer_ImplI12KeyValuePairI15SerializableMapI10CAssetInfoEEE6AcceptER11_SerializerIS_ERS5_j | lib libSOA-3.7.0.so | 2026-10-04
void _ZN14SerializerImpl16_Serializer_ImplI12KeyValuePairI15SerializableMapI10CAssetInfoEEE6AcceptER11_SerializerIS_ERS5_j
               (long *param_1,long param_2,undefined4 param_3)

{
  long lVar1;
  char *pcVar2;
  long lVar3;
  int iVar4;
  long lVar5;
  char *pcVar6;
  char *pcVar7;
  
  lVar5 = *(long *)(param_2 + 8);
  if (*(int *)(lVar5 + 0x10) != 0) {
    pcVar7 = *(char **)(lVar5 + 0x20);
    lVar1 = *(long *)(lVar5 + 0x28);
    pcVar6 = pcVar7;
    if (lVar1 == 0) {
code_r0x018f5e6c:
      pcVar7 = pcVar7 + lVar1 * 0xc0;
      if (pcVar6 != pcVar7) {
        iVar4 = 0;
        do {
          if ((pcVar6[8] & 1U) == 0) {
            pcVar2 = pcVar6 + 9;
          }
          else {
            pcVar2 = *(char **)(pcVar6 + 0x18);
          }
          (**(code **)(*param_1 + 0xf0))(param_1,pcVar2,iVar4);
          (**(code **)(*param_1 + 0x60))(param_1);
          void CAssetInfo::Accept<_Serializer<SerializerImpl> >(_Serializer<SerializerImpl>&, unsigned int)(pcVar6 + 0x20,param_1,param_3);
          (**(code **)(*param_1 + 0x68))(param_1);
          if ((pcVar6[8] & 1U) == 0) {
            pcVar2 = pcVar6 + 9;
          }
          else {
            pcVar2 = *(char **)(pcVar6 + 0x18);
          }
          (**(code **)(*param_1 + 0xf8))(param_1,pcVar2,iVar4);
          iVar4 = iVar4 + 1;
          pcVar2 = pcVar6;
          do {
            pcVar6 = pcVar7;
            if (pcVar7 == pcVar2) break;
            pcVar6 = pcVar2 + 0xc0;
            pcVar2 = pcVar6;
          } while (*pcVar6 != '\x01');
        } while (pcVar6 != (char *)(*(long *)(lVar5 + 0x20) + *(long *)(lVar5 + 0x28) * 0xc0));
      }
    }
    else {
      lVar3 = lVar1 * 0xc0;
      do {
        if (*pcVar6 == '\x01') goto code_r0x018f5e6c;
        lVar3 = lVar3 + -0xc0;
        pcVar6 = pcVar6 + 0xc0;
      } while (lVar3 != 0);
    }
  }
  return;
}


// FAILED to create function at 02ac6e10 _AsonSerializer::vtable
// FAILED to create function at 02ac6f30 _AsonSerializer::typeinfo
