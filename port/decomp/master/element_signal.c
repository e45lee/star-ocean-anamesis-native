// port/decomp/master/element_signal.c: Ghidra decompiles for the master subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 13:05 UTC: tools/decomp.sh '--into' 'master/element_signal' 'CMasterParameterSignalElement::'

// ==== CMasterParameterSignalElement::GetSignalParameter(Parameter::SignalParameter&) const
// vaddr 0x11ac904 | ghidra 0x12ac904 | size 684 | symbol _ZNK29CMasterParameterSignalElement18GetSignalParameterERN9Parameter15SignalParameterE | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK29CMasterParameterSignalElement18GetSignalParameterERN9Parameter15SignalParameterE
               (long param_1,undefined4 *param_2)

{
  byte *pbVar1;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  *param_2 = *(undefined4 *)(param_1 + 0xd8);
  param_2[1] = (float)*(int *)(param_1 + 0x108);
  param_2[2] = *(undefined4 *)(param_1 + 0x138);
  param_2[3] = (float)*(int *)(param_1 + 0x168);
  param_2[4] = *(undefined4 *)(param_1 + 0x198);
  param_2[5] = (float)*(int *)(param_1 + 0x1c8);
  param_2[6] = *(undefined4 *)(param_1 + 0x1f8);
  param_2[7] = (float)*(int *)(param_1 + 0x228);
  param_2[8] = *(undefined4 *)(param_1 + 600);
  param_2[9] = (float)*(int *)(param_1 + 0x288);
  param_2[10] = *(undefined4 *)(param_1 + 0x2b8);
  param_2[0xb] = (float)*(int *)(param_1 + 0x2e8);
  param_2[0xc] = *(undefined4 *)(param_1 + 0x318);
  param_2[0xd] = (float)*(int *)(param_1 + 0x348);
  param_2[0xe] = *(undefined4 *)(param_1 + 0x378);
  param_2[0xf] = (float)*(int *)(param_1 + 0x3a8);
  param_2[0x10] = *(undefined4 *)(param_1 + 0x3d8);
  param_2[0x11] = (float)*(int *)(param_1 + 0x408);
  param_2[0x12] = *(undefined4 *)(param_1 + 0x438);
  param_2[0x13] = (float)*(int *)(param_1 + 0x468);
  param_2[0x14] = *(undefined4 *)(param_1 + 0x498);
  param_2[0x15] = (float)*(int *)(param_1 + 0x4c8);
  param_2[0x16] = *(undefined4 *)(param_1 + 0x4f8);
  param_2[0x17] = (float)*(int *)(param_1 + 0x528);
  param_2[0x18] = *(undefined4 *)(param_1 + 0x558);
  param_2[0x19] = (float)*(int *)(param_1 + 0x588);
  param_2[0x1a] = *(undefined4 *)(param_1 + 0x5b8);
  param_2[0x1b] = (float)*(int *)(param_1 + 0x5e8);
  param_2[0x1c] = *(undefined4 *)(param_1 + 0x618);
  param_2[0x1d] = (float)*(int *)(param_1 + 0x648);
  param_2[0x1e] = *(undefined4 *)(param_1 + 0x678);
  param_2[0x1f] = (float)*(int *)(param_1 + 0x6a8);
  param_2[0x20] = *(undefined4 *)(param_1 + 0x6d8);
  uStack_30 = 0;
  uStack_28 = 0;
  uStack_38 = 0;
  void CParameterPropertyBase<105u>::CryptString<string >(string&, string const&)(&uStack_38,param_1 + 0x708);
  pbVar1 = (byte *)(param_2 + 0x22);
  if ((*pbVar1 & 1) == 0) {
    pbVar1[0] = 0;
    pbVar1[1] = 0;
  }
  else {
    **(undefined1 **)(param_2 + 0x26) = 0;
    *(undefined8 *)(param_2 + 0x24) = 0;
  }
  string::reserve(unsigned long)(pbVar1,0);
  *(undefined8 *)(param_2 + 0x26) = uStack_28;
  *(undefined8 *)(param_2 + 0x24) = uStack_30;
  *(undefined8 *)pbVar1 = uStack_38;
  uStack_30 = 0;
  uStack_28 = 0;
  uStack_38 = 0;
  void CParameterPropertyBase<106u>::CryptString<string >(string&, string const&)(&uStack_38,param_1 + 0x748);
  pbVar1 = (byte *)(param_2 + 0x28);
  if ((*pbVar1 & 1) == 0) {
    pbVar1[0] = 0;
    pbVar1[1] = 0;
  }
  else {
    **(undefined1 **)(param_2 + 0x2c) = 0;
    *(undefined8 *)(param_2 + 0x2a) = 0;
  }
  string::reserve(unsigned long)(pbVar1,0);
  *(undefined8 *)(param_2 + 0x2c) = uStack_28;
  *(undefined8 *)(param_2 + 0x2a) = uStack_30;
  *(undefined8 *)pbVar1 = uStack_38;
  uStack_30 = 0;
  uStack_28 = 0;
  uStack_38 = 0;
  void CParameterPropertyBase<107u>::CryptString<string >(string&, string const&)(&uStack_38,param_1 + 0x788);
  pbVar1 = (byte *)(param_2 + 0x2e);
  if ((*pbVar1 & 1) == 0) {
    pbVar1[0] = 0;
    pbVar1[1] = 0;
  }
  else {
    **(undefined1 **)(param_2 + 0x32) = 0;
    *(undefined8 *)(param_2 + 0x30) = 0;
  }
  string::reserve(unsigned long)(pbVar1,0);
  *(undefined8 *)(param_2 + 0x32) = uStack_28;
  *(undefined8 *)(param_2 + 0x30) = uStack_30;
  *(undefined8 *)pbVar1 = uStack_38;
  uStack_30 = 0;
  uStack_28 = 0;
  uStack_38 = 0;
  void CParameterPropertyBase<108u>::CryptString<string >(string&, string const&)(&uStack_38,param_1 + 0x7c8);
  pbVar1 = (byte *)(param_2 + 0x34);
  if ((*pbVar1 & 1) == 0) {
    pbVar1[0] = 0;
    pbVar1[1] = 0;
  }
  else {
    **(undefined1 **)(param_2 + 0x38) = 0;
    *(undefined8 *)(param_2 + 0x36) = 0;
  }
  string::reserve(unsigned long)(pbVar1,0);
  *(undefined8 *)(param_2 + 0x38) = uStack_28;
  *(undefined8 *)(param_2 + 0x36) = uStack_30;
  *(undefined8 *)pbVar1 = uStack_38;
  return;
}

// ==== CMasterParameterSignalElement::CMasterParameterSignalElement()
// vaddr 0x1285ddc | ghidra 0x1385ddc | size 1972 | symbol _ZN29CMasterParameterSignalElementC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN29CMasterParameterSignalElementC2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  CParameterElementBase::CParameterElementBase()();
  puVar2 = PTR__ZTV29CMasterParameterSignalElement_02cc2a30;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj69EE_02cb76b8;
  *(undefined1 *)(param_1 + 4) = 0;
  *param_1 = (long)(puVar2 + 0x10);
  param_1[2] = (long)(puVar1 + 0x10);
  param_1[3] = 0;
  Framework::CHash32::CHash32()(param_1 + 5);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj69EE_02cc27b0
  ;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[0xb] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj70EE_02cc3ce0;
  *(undefined1 *)(param_1 + 0xc) = 0;
  param_1[2] = (long)(puVar1 + 0x10);
  param_1[9] = 0;
  param_1[10] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xd);
  puVar2 = PTR__ZTV23CParameterPropertyValueIjLj70E18CPropertyConverterE_02cc4af8;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj71EE_02cc16f0;
  *(undefined1 *)(param_1 + 0x12) = 0;
  param_1[10] = (long)(puVar2 + 0x10);
  param_1[0x10] = (long)(puVar1 + 0x10);
  param_1[0x11] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x13);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj72EE_02cc49d0;
  puVar1 = PTR__ZTV23CParameterPropertyValueIjLj71E18CPropertyConverterE_02cc27b8;
  *(undefined1 *)(param_1 + 0x18) = 0;
  param_1[0x10] = (long)(puVar1 + 0x10);
  param_1[0x16] = (long)(puVar2 + 0x10);
  param_1[0x17] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x19);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj73EE_02cc1520;
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj72E18CPropertyConverterE_02cb7a88;
  *(undefined1 *)(param_1 + 0x1e) = 0;
  param_1[0x16] = (long)(puVar1 + 0x10);
  param_1[0x1c] = (long)(puVar2 + 0x10);
  param_1[0x1d] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x1f);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj74EE_02cc1bd0;
  puVar1 = PTR__ZTV23CParameterPropertyValueIiLj73E18CPropertyConverterE_02cbb1c0;
  *(undefined1 *)(param_1 + 0x24) = 0;
  param_1[0x1c] = (long)(puVar1 + 0x10);
  param_1[0x22] = (long)(puVar2 + 0x10);
  param_1[0x23] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x25);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj75EE_02cbea40;
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj74E18CPropertyConverterE_02cb84f0;
  *(undefined1 *)(param_1 + 0x2a) = 0;
  param_1[0x22] = (long)(puVar1 + 0x10);
  param_1[0x28] = (long)(puVar2 + 0x10);
  param_1[0x29] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x2b);
  puVar2 = PTR__ZTV23CParameterPropertyValueIiLj75E18CPropertyConverterE_02cc2110;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj76EE_02cc1a08;
  *(undefined1 *)(param_1 + 0x30) = 0;
  param_1[0x28] = (long)(puVar2 + 0x10);
  param_1[0x2e] = (long)(puVar1 + 0x10);
  param_1[0x2f] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x31);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj76E18CPropertyConverterE_02cc2c98;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj77EE_02cbf550;
  *(undefined1 *)(param_1 + 0x36) = 0;
  param_1[0x2e] = (long)(puVar2 + 0x10);
  param_1[0x34] = (long)(puVar1 + 0x10);
  param_1[0x35] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x37);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj78EE_02cc2748;
  puVar1 = PTR__ZTV23CParameterPropertyValueIiLj77E18CPropertyConverterE_02cbc220;
  *(undefined1 *)(param_1 + 0x3c) = 0;
  param_1[0x34] = (long)(puVar1 + 0x10);
  param_1[0x3a] = (long)(puVar2 + 0x10);
  param_1[0x3b] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x3d);
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj78E18CPropertyConverterE_02cb6c10;
  param_1[0x41] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj79EE_02cb7300;
  *(undefined1 *)(param_1 + 0x42) = 0;
  param_1[0x3a] = (long)(puVar1 + 0x10);
  param_1[0x40] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x43);
  puVar2 = PTR__ZTV23CParameterPropertyValueIiLj79E18CPropertyConverterE_02cbc0e0;
  param_1[0x47] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj80EE_02cb6c00;
  *(undefined1 *)(param_1 + 0x48) = 0;
  param_1[0x40] = (long)(puVar2 + 0x10);
  param_1[0x46] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x49);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj80E18CPropertyConverterE_02cc1428;
  param_1[0x4d] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj81EE_02cc0f08;
  *(undefined1 *)(param_1 + 0x4e) = 0;
  param_1[0x46] = (long)(puVar2 + 0x10);
  param_1[0x4c] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x4f);
  puVar1 = PTR__ZTV23CParameterPropertyValueIiLj81E18CPropertyConverterE_02cbefa0;
  param_1[0x53] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj82EE_02cc4fc8;
  *(undefined1 *)(param_1 + 0x54) = 0;
  param_1[0x4c] = (long)(puVar1 + 0x10);
  param_1[0x52] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x55);
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj82E18CPropertyConverterE_02cb8f70;
  param_1[0x59] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj83EE_02cbe348;
  *(undefined1 *)(param_1 + 0x5a) = 0;
  param_1[0x52] = (long)(puVar1 + 0x10);
  param_1[0x58] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x5b);
  puVar1 = PTR__ZTV23CParameterPropertyValueIiLj83E18CPropertyConverterE_02cc0748;
  param_1[0x5f] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj84EE_02cc2208;
  *(undefined1 *)(param_1 + 0x60) = 0;
  param_1[0x58] = (long)(puVar1 + 0x10);
  param_1[0x5e] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x61);
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj84E18CPropertyConverterE_02cbdad8;
  param_1[0x65] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj85EE_02cbe188;
  *(undefined1 *)(param_1 + 0x66) = 0;
  param_1[0x5e] = (long)(puVar1 + 0x10);
  param_1[100] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x67);
  puVar1 = PTR__ZTV23CParameterPropertyValueIiLj85E18CPropertyConverterE_02cc0b90;
  param_1[0x6b] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj86EE_02cc2fd8;
  *(undefined1 *)(param_1 + 0x6c) = 0;
  param_1[100] = (long)(puVar1 + 0x10);
  param_1[0x6a] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x6d);
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj86E18CPropertyConverterE_02cb7aa0;
  param_1[0x71] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj87EE_02cbee28;
  *(undefined1 *)(param_1 + 0x72) = 0;
  param_1[0x6a] = (long)(puVar1 + 0x10);
  param_1[0x70] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x73);
  puVar2 = PTR__ZTV23CParameterPropertyValueIiLj87E18CPropertyConverterE_02cbee50;
  param_1[0x77] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj88EE_02cbab60;
  *(undefined1 *)(param_1 + 0x78) = 0;
  param_1[0x70] = (long)(puVar2 + 0x10);
  param_1[0x76] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x79);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj88E18CPropertyConverterE_02cbee10;
  param_1[0x7d] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj89EE_02cba390;
  *(undefined1 *)(param_1 + 0x7e) = 0;
  param_1[0x76] = (long)(puVar2 + 0x10);
  param_1[0x7c] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x7f);
  puVar2 = PTR__ZTV23CParameterPropertyValueIiLj89E18CPropertyConverterE_02cbee78;
  param_1[0x83] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj90EE_02cb98a8;
  *(undefined1 *)(param_1 + 0x84) = 0;
  param_1[0x7c] = (long)(puVar2 + 0x10);
  param_1[0x82] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x85);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj90E18CPropertyConverterE_02cc3530;
  param_1[0x89] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj91EE_02cbc970;
  *(undefined1 *)(param_1 + 0x8a) = 0;
  param_1[0x82] = (long)(puVar2 + 0x10);
  param_1[0x88] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x8b);
  puVar2 = PTR__ZTV23CParameterPropertyValueIiLj91E18CPropertyConverterE_02cbf540;
  param_1[0x8f] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj92EE_02cba3e8;
  *(undefined1 *)(param_1 + 0x90) = 0;
  param_1[0x88] = (long)(puVar2 + 0x10);
  param_1[0x8e] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x91);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj92E18CPropertyConverterE_02cc45d8;
  param_1[0x95] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj93EE_02cbd5e8;
  *(undefined1 *)(param_1 + 0x96) = 0;
  param_1[0x8e] = (long)(puVar2 + 0x10);
  param_1[0x94] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x97);
  puVar1 = PTR__ZTV23CParameterPropertyValueIiLj93E18CPropertyConverterE_02cb78d0;
  param_1[0x9b] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj94EE_02cba2b0;
  *(undefined1 *)(param_1 + 0x9c) = 0;
  param_1[0x94] = (long)(puVar1 + 0x10);
  param_1[0x9a] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x9d);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj94E18CPropertyConverterE_02cbb1d8;
  param_1[0xa1] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj95EE_02cba878;
  *(undefined1 *)(param_1 + 0xa2) = 0;
  param_1[0x9a] = (long)(puVar2 + 0x10);
  param_1[0xa0] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xa3);
  puVar2 = PTR__ZTV23CParameterPropertyValueIiLj95E18CPropertyConverterE_02cc2b58;
  param_1[0xa7] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj96EE_02cb75b0;
  *(undefined1 *)(param_1 + 0xa8) = 0;
  param_1[0xa0] = (long)(puVar2 + 0x10);
  param_1[0xa6] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xa9);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj96E18CPropertyConverterE_02cbe058;
  param_1[0xad] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj97EE_02cba650;
  *(undefined1 *)(param_1 + 0xae) = 0;
  param_1[0xa6] = (long)(puVar2 + 0x10);
  param_1[0xac] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xaf);
  puVar2 = PTR__ZTV23CParameterPropertyValueIiLj97E18CPropertyConverterE_02cbe7f0;
  param_1[0xb3] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj98EE_02cb81c0;
  *(undefined1 *)(param_1 + 0xb4) = 0;
  param_1[0xac] = (long)(puVar2 + 0x10);
  param_1[0xb2] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xb5);
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj98E18CPropertyConverterE_02cb8a58;
  param_1[0xb9] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj99EE_02cbb310;
  *(undefined1 *)(param_1 + 0xba) = 0;
  param_1[0xb2] = (long)(puVar1 + 0x10);
  param_1[0xb8] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xbb);
  puVar2 = PTR__ZTV23CParameterPropertyValueIiLj99E18CPropertyConverterE_02cc3f10;
  param_1[0xbf] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj100EE_02cc23f0;
  *(undefined1 *)(param_1 + 0xc0) = 0;
  param_1[0xb8] = (long)(puVar2 + 0x10);
  param_1[0xbe] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xc1);
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj100E18CPropertyConverterE_02cbcdf0;
  param_1[0xc5] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj101EE_02cbe0f0;
  *(undefined1 *)(param_1 + 0xc6) = 0;
  param_1[0xbe] = (long)(puVar1 + 0x10);
  param_1[0xc4] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 199);
  puVar2 = PTR__ZTV23CParameterPropertyValueIiLj101E18CPropertyConverterE_02cbfd00;
  param_1[0xcb] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj102EE_02cb7580;
  *(undefined1 *)(param_1 + 0xcc) = 0;
  param_1[0xc4] = (long)(puVar2 + 0x10);
  param_1[0xca] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xcd);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj102E18CPropertyConverterE_02cc1200;
  param_1[0xd1] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj103EE_02cb80d8;
  *(undefined1 *)(param_1 + 0xd2) = 0;
  param_1[0xca] = (long)(puVar2 + 0x10);
  param_1[0xd0] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xd3);
  puVar2 = PTR__ZTV23CParameterPropertyValueIiLj103E18CPropertyConverterE_02cc2118;
  param_1[0xd7] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj104EE_02cbc2d0;
  *(undefined1 *)(param_1 + 0xd8) = 0;
  param_1[0xd0] = (long)(puVar2 + 0x10);
  param_1[0xd6] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xd9);
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj104E18CPropertyConverterE_02cbf828;
  param_1[0xdd] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj105EE_02cc2cd0;
  *(undefined1 *)(param_1 + 0xde) = 0;
  param_1[0xd6] = (long)(puVar1 + 0x10);
  param_1[0xdc] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xdf);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj105EE_02cbc338
  ;
  param_1[0xe3] = 0;
  param_1[0xe2] = 0;
  param_1[0xe1] = 0;
  param_1[0xe5] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj106EE_02cc4338;
  *(undefined1 *)(param_1 + 0xe6) = 0;
  param_1[0xdc] = (long)(puVar1 + 0x10);
  param_1[0xe4] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xe7);
  puVar2 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj106EE_02cc3f00
  ;
  param_1[0xeb] = 0;
  param_1[0xea] = 0;
  param_1[0xe9] = 0;
  param_1[0xed] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj107EE_02cb8570;
  *(undefined1 *)(param_1 + 0xee) = 0;
  param_1[0xe4] = (long)(puVar2 + 0x10);
  param_1[0xec] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xef);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj107EE_02cbf0c0
  ;
  param_1[0xf3] = 0;
  param_1[0xf2] = 0;
  param_1[0xf1] = 0;
  param_1[0xf5] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj108EE_02cc2bd8;
  *(undefined1 *)(param_1 + 0xf6) = 0;
  param_1[0xec] = (long)(puVar1 + 0x10);
  param_1[0xf4] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xf7);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj108EE_02cb94e8
  ;
  param_1[0xfb] = 0;
  param_1[0xfa] = 0;
  param_1[0xf9] = 0;
  param_1[0xf4] = (long)(puVar1 + 0x10);
  return;
}

// ==== CMasterParameterSignalElement::Initialize()
// vaddr 0x1286590 | ghidra 0x1386590 | size 3928 | symbol _ZN29CMasterParameterSignalElement10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN29CMasterParameterSignalElement10InitializeEv(long param_1)

{
  byte bStack_58;
  undefined2 uStack_57;
  undefined1 uStack_55;
  undefined1 uStack_54;
  undefined2 uStack_53;
  undefined1 uStack_51;
  undefined1 uStack_50;
  undefined4 uStack_4f;
  undefined3 uStack_4b;
  undefined8 uStack_48;
  
  uStack_48 = 0;
  uStack_4b = 0;
  bStack_58 = 0x10;
  uStack_57 = 0x6469;
  uStack_55 = 0x5f;
  uStack_54 = 0x6c;
  uStack_53 = 0x6261;
  uStack_51 = 0x65;
  uStack_50 = 0x6c;
  uStack_4f = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x28,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x20) = 1;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x10);
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  uStack_54 = 0;
  uStack_53 = 0;
  uStack_51 = 0;
  bStack_58 = 4;
  uStack_57 = 0x6469;
  uStack_55 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x68,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x60) = 1;
  *(undefined4 *)(param_1 + 0x78) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x50);
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0x10;
  uStack_57 = 0x7267;
  uStack_55 = 0x6f;
  uStack_54 = 0x75;
  uStack_53 = 0x5f70;
  uStack_51 = 0x69;
  uStack_50 = 100;
  uStack_4f = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x98,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x90) = 1;
  *(undefined4 *)(param_1 + 0xa8) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x80);
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0x16;
  uStack_57 = (undefined2)_UNK_027f83fb;
  uStack_55 = (undefined1)((ulong)_UNK_027f83fb >> 0x10);
  uStack_54 = (undefined1)((ulong)_UNK_027f83fb >> 0x18);
  uStack_53 = (undefined2)((ulong)_UNK_027f83fb >> 0x20);
  uStack_51 = (undefined1)((ulong)_UNK_027f83fb >> 0x30);
  uStack_50 = (undefined1)((ulong)_UNK_027f83fb >> 0x38);
  uStack_4f = 0x656d61;
  Framework::CHash32::operator=(char const*)(param_1 + 200,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0xc0) = 1;
  *(undefined4 *)(param_1 + 0xd8) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0xb0);
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xc;
  uStack_53 = 0x3165;
  uStack_57 = 0x7266;
  uStack_55 = 0x61;
  uStack_54 = 0x6d;
  uStack_51 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xf8,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0xf0) = 1;
  *(undefined4 *)(param_1 + 0x108) = 0xffffffff;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0xe0);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x31;
  uStack_53 = 0x6c61;
  uStack_57 = 0x6973;
  uStack_55 = 0x67;
  uStack_54 = 0x6e;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x128,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x120) = 1;
  *(undefined4 *)(param_1 + 0x138) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x110);
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xc;
  uStack_53 = 0x3265;
  uStack_57 = 0x7266;
  uStack_55 = 0x61;
  uStack_54 = 0x6d;
  uStack_51 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x158,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x150) = 1;
  *(undefined4 *)(param_1 + 0x168) = 0xffffffff;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x140);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x32;
  uStack_53 = 0x6c61;
  uStack_57 = 0x6973;
  uStack_55 = 0x67;
  uStack_54 = 0x6e;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x188,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x180) = 1;
  *(undefined4 *)(param_1 + 0x198) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x170);
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xc;
  uStack_53 = 0x3365;
  uStack_57 = 0x7266;
  uStack_55 = 0x61;
  uStack_54 = 0x6d;
  uStack_51 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x1b8,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x1b0) = 1;
  *(undefined4 *)(param_1 + 0x1c8) = 0xffffffff;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x1a0);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x33;
  uStack_53 = 0x6c61;
  uStack_57 = 0x6973;
  uStack_55 = 0x67;
  uStack_54 = 0x6e;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x1e8,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x1e0) = 1;
  *(undefined4 *)(param_1 + 0x1f8) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x1d0);
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xc;
  uStack_53 = 0x3465;
  uStack_57 = 0x7266;
  uStack_55 = 0x61;
  uStack_54 = 0x6d;
  uStack_51 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x218,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x210) = 1;
  *(undefined4 *)(param_1 + 0x228) = 0xffffffff;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x200);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x34;
  uStack_53 = 0x6c61;
  uStack_57 = 0x6973;
  uStack_55 = 0x67;
  uStack_54 = 0x6e;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x248,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x240) = 1;
  *(undefined4 *)(param_1 + 600) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x230);
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xc;
  uStack_53 = 0x3565;
  uStack_57 = 0x7266;
  uStack_55 = 0x61;
  uStack_54 = 0x6d;
  uStack_51 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x278,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x270) = 1;
  *(undefined4 *)(param_1 + 0x288) = 0xffffffff;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x260);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x35;
  uStack_53 = 0x6c61;
  uStack_57 = 0x6973;
  uStack_55 = 0x67;
  uStack_54 = 0x6e;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x2a8,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x2a0) = 1;
  *(undefined4 *)(param_1 + 0x2b8) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x290);
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xc;
  uStack_53 = 0x3665;
  uStack_57 = 0x7266;
  uStack_55 = 0x61;
  uStack_54 = 0x6d;
  uStack_51 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x2d8,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x2d0) = 1;
  *(undefined4 *)(param_1 + 0x2e8) = 0xffffffff;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x2c0);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x36;
  uStack_53 = 0x6c61;
  uStack_57 = 0x6973;
  uStack_55 = 0x67;
  uStack_54 = 0x6e;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x308,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x300) = 1;
  *(undefined4 *)(param_1 + 0x318) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x2f0);
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xc;
  uStack_53 = 0x3765;
  uStack_57 = 0x7266;
  uStack_55 = 0x61;
  uStack_54 = 0x6d;
  uStack_51 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x338,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x330) = 1;
  *(undefined4 *)(param_1 + 0x348) = 0xffffffff;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 800);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x37;
  uStack_53 = 0x6c61;
  uStack_57 = 0x6973;
  uStack_55 = 0x67;
  uStack_54 = 0x6e;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x368,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x360) = 1;
  *(undefined4 *)(param_1 + 0x378) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x350);
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xc;
  uStack_53 = 0x3865;
  uStack_57 = 0x7266;
  uStack_55 = 0x61;
  uStack_54 = 0x6d;
  uStack_51 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x398,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x390) = 1;
  *(undefined4 *)(param_1 + 0x3a8) = 0xffffffff;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x380);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x38;
  uStack_53 = 0x6c61;
  uStack_57 = 0x6973;
  uStack_55 = 0x67;
  uStack_54 = 0x6e;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x3c8,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x3c0) = 1;
  *(undefined4 *)(param_1 + 0x3d8) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x3b0);
  uStack_50 = 0;
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xc;
  uStack_53 = 0x3965;
  uStack_57 = 0x7266;
  uStack_55 = 0x61;
  uStack_54 = 0x6d;
  uStack_51 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x3f8,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x3f0) = 1;
  *(undefined4 *)(param_1 + 0x408) = 0xffffffff;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x3e0);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x39;
  uStack_53 = 0x6c61;
  uStack_57 = 0x6973;
  uStack_55 = 0x67;
  uStack_54 = 0x6e;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x428,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x420) = 1;
  *(undefined4 *)(param_1 + 0x438) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x410);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x30;
  uStack_53 = 0x3165;
  uStack_57 = 0x7266;
  uStack_55 = 0x61;
  uStack_54 = 0x6d;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x458,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x450) = 1;
  *(undefined4 *)(param_1 + 0x468) = 0xffffffff;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x440);
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0x10;
  uStack_57 = 0x6973;
  uStack_55 = 0x67;
  uStack_54 = 0x6e;
  uStack_53 = 0x6c61;
  uStack_51 = 0x31;
  uStack_50 = 0x30;
  uStack_4f = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x488,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x480) = 1;
  *(undefined4 *)(param_1 + 0x498) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x470);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x31;
  uStack_53 = 0x3165;
  uStack_57 = 0x7266;
  uStack_55 = 0x61;
  uStack_54 = 0x6d;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x4b8,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x4b0) = 1;
  *(undefined4 *)(param_1 + 0x4c8) = 0xffffffff;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x4a0);
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0x10;
  uStack_57 = 0x6973;
  uStack_55 = 0x67;
  uStack_54 = 0x6e;
  uStack_53 = 0x6c61;
  uStack_51 = 0x31;
  uStack_50 = 0x31;
  uStack_4f = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x4e8,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x4e0) = 1;
  *(undefined4 *)(param_1 + 0x4f8) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x4d0);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x32;
  uStack_53 = 0x3165;
  uStack_57 = 0x7266;
  uStack_55 = 0x61;
  uStack_54 = 0x6d;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x518,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x510) = 1;
  *(undefined4 *)(param_1 + 0x528) = 0xffffffff;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x500);
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0x10;
  uStack_57 = 0x6973;
  uStack_55 = 0x67;
  uStack_54 = 0x6e;
  uStack_53 = 0x6c61;
  uStack_51 = 0x31;
  uStack_50 = 0x32;
  uStack_4f = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x548,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x540) = 1;
  *(undefined4 *)(param_1 + 0x558) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x530);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x33;
  uStack_53 = 0x3165;
  uStack_57 = 0x7266;
  uStack_55 = 0x61;
  uStack_54 = 0x6d;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x578,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x570) = 1;
  *(undefined4 *)(param_1 + 0x588) = 0xffffffff;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x560);
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0x10;
  uStack_57 = 0x6973;
  uStack_55 = 0x67;
  uStack_54 = 0x6e;
  uStack_53 = 0x6c61;
  uStack_51 = 0x31;
  uStack_50 = 0x33;
  uStack_4f = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x5a8,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x5a0) = 1;
  *(undefined4 *)(param_1 + 0x5b8) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x590);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x34;
  uStack_53 = 0x3165;
  uStack_57 = 0x7266;
  uStack_55 = 0x61;
  uStack_54 = 0x6d;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x5d8,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x5d0) = 1;
  *(undefined4 *)(param_1 + 0x5e8) = 0xffffffff;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x5c0);
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0x10;
  uStack_57 = 0x6973;
  uStack_55 = 0x67;
  uStack_54 = 0x6e;
  uStack_53 = 0x6c61;
  uStack_51 = 0x31;
  uStack_50 = 0x34;
  uStack_4f = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x608,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x600) = 1;
  *(undefined4 *)(param_1 + 0x618) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x5f0);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x35;
  uStack_53 = 0x3165;
  uStack_57 = 0x7266;
  uStack_55 = 0x61;
  uStack_54 = 0x6d;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x638,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x630) = 1;
  *(undefined4 *)(param_1 + 0x648) = 0xffffffff;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x620);
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0x10;
  uStack_57 = 0x6973;
  uStack_55 = 0x67;
  uStack_54 = 0x6e;
  uStack_53 = 0x6c61;
  uStack_51 = 0x31;
  uStack_50 = 0x35;
  uStack_4f = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x668,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x660) = 1;
  *(undefined4 *)(param_1 + 0x678) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x650);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x36;
  uStack_53 = 0x3165;
  uStack_57 = 0x7266;
  uStack_55 = 0x61;
  uStack_54 = 0x6d;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x698,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x690) = 1;
  *(undefined4 *)(param_1 + 0x6a8) = 0xffffffff;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x680);
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0x10;
  uStack_57 = 0x6973;
  uStack_55 = 0x67;
  uStack_54 = 0x6e;
  uStack_53 = 0x6c61;
  uStack_51 = 0x31;
  uStack_50 = 0x36;
  uStack_4f = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x6c8,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x6c0) = 1;
  *(undefined4 *)(param_1 + 0x6d8) = 0;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x6b0);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x31;
  uStack_53 = 0x6e6f;
  uStack_57 = 0x6f63;
  uStack_55 = 0x6d;
  uStack_54 = 0x6d;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x6f8,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x6f0) = 1;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x6e0);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x32;
  uStack_53 = 0x6e6f;
  uStack_57 = 0x6f63;
  uStack_55 = 0x6d;
  uStack_54 = 0x6d;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x738,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x730) = 1;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x720);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x33;
  uStack_53 = 0x6e6f;
  uStack_57 = 0x6f63;
  uStack_55 = 0x6d;
  uStack_54 = 0x6d;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x778,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x770) = 1;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x760);
  uStack_4f = 0;
  uStack_4b = 0;
  uStack_48 = 0;
  bStack_58 = 0xe;
  uStack_51 = 0x34;
  uStack_53 = 0x6e6f;
  uStack_57 = 0x6f63;
  uStack_55 = 0x6d;
  uStack_54 = 0x6d;
  uStack_50 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x7b8,(ulong)&bStack_58 | 1);
  *(undefined1 *)(param_1 + 0x7b0) = 1;
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x7a0);
  return;
}

// ==== CMasterParameterSignalElement::~CMasterParameterSignalElement()
// vaddr 0x12874e8 | ghidra 0x13874e8 | size 1148 | symbol _ZN29CMasterParameterSignalElementD2Ev | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x01387534: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0138756c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x013875a4: Changing call to branch */
/* WARNING: Possible PIC construction at 0x013875dc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0138760c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0138763c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0138766c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0138769c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x013876cc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x013876fc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0138772c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0138775c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0138778c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x013877bc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x013877ec: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0138781c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0138784c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0138787c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x013878ac: Changing call to branch */
/* WARNING: Possible PIC construction at 0x013878dc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0138790c: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x013878e0) */
/* WARNING: Removing unreachable block (ram,0x013878b0) */
/* WARNING: Removing unreachable block (ram,0x01387880) */
/* WARNING: Removing unreachable block (ram,0x01387850) */
/* WARNING: Removing unreachable block (ram,0x01387820) */
/* WARNING: Removing unreachable block (ram,0x013877f0) */
/* WARNING: Removing unreachable block (ram,0x013877c0) */
/* WARNING: Removing unreachable block (ram,0x01387790) */
/* WARNING: Removing unreachable block (ram,0x01387760) */
/* WARNING: Removing unreachable block (ram,0x01387730) */
/* WARNING: Removing unreachable block (ram,0x01387700) */
/* WARNING: Removing unreachable block (ram,0x013876d0) */
/* WARNING: Removing unreachable block (ram,0x013876a0) */
/* WARNING: Removing unreachable block (ram,0x01387670) */
/* WARNING: Removing unreachable block (ram,0x01387640) */
/* WARNING: Removing unreachable block (ram,0x01387610) */
/* WARNING: Removing unreachable block (ram,0x013875e0) */
/* WARNING: Removing unreachable block (ram,0x013875a8) */
/* WARNING: Removing unreachable block (ram,0x013875c0) */
/* WARNING: Removing unreachable block (ram,0x013875c8) */
/* WARNING: Removing unreachable block (ram,0x01387570) */
/* WARNING: Removing unreachable block (ram,0x01387588) */
/* WARNING: Removing unreachable block (ram,0x01387590) */
/* WARNING: Removing unreachable block (ram,0x01387538) */
/* WARNING: Removing unreachable block (ram,0x01387550) */
/* WARNING: Removing unreachable block (ram,0x01387558) */
/* WARNING: Removing unreachable block (ram,0x01387910) */
/* WARNING: Removing unreachable block (ram,0x01387940) */
/* WARNING: Removing unreachable block (ram,0x01387948) */

void _ZN29CMasterParameterSignalElementD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTV29CMasterParameterSignalElement_02cc2a30 + 0x10);
  param_1[0xf4] =
       (long)(
             PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj108EE_02cb94e8
             + 0x10);
  if ((*(byte *)(param_1 + 0xf9) & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0xfb]);
  }
  param_1[0xf4] = (long)(PTR__ZTV22CParameterPropertyBaseILj108EE_02cc2bd8 + 0x10);
  (*(code *)PTR__ZN9Framework7CHash32D1Ev_02cb3740)(param_1 + 0xf7);
  return;
}

// ==== CMasterParameterSignalElement::~CMasterParameterSignalElement()
// vaddr 0x1287964 | ghidra 0x1387964 | size 24 | symbol _ZN29CMasterParameterSignalElementD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN29CMasterParameterSignalElementD0Ev(undefined8 param_1)

{
  CMasterParameterSignalElement::~CMasterParameterSignalElement()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CMasterParameterSignalElement::CMasterParameterSignalElement(CMasterParameterSignalElement const&)
// vaddr 0x1287f4c | ghidra 0x1387f4c | size 3952 | symbol _ZN29CMasterParameterSignalElementC2ERKS_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN29CMasterParameterSignalElementC2ERKS_(long *param_1,long param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  long lVar8;
  undefined8 uVar9;
  ulong uVar10;
  long *plVar11;
  ulong uVar12;
  
  puVar6 = PTR__ZTV29CMasterParameterSignalElement_02cc2a30;
  puVar7 = PTR__ZTV18IParameterProperty_02cbe818;
  *param_1 = (long)(PTR__ZTV21CParameterElementBase_02cbbc00 + 0x10);
  lVar8 = *(long *)(param_2 + 8);
  *param_1 = (long)(puVar6 + 0x10);
  param_1[1] = lVar8;
  param_1[2] = (long)(puVar7 + 0x10);
  lVar8 = *(long *)(param_2 + 0x18);
  param_1[2] = (long)(PTR__ZTV22CParameterPropertyBaseILj69EE_02cb76b8 + 0x10);
  param_1[3] = lVar8;
  puVar6 = PTR__ZTVN9Framework7CHash32E_02cba528;
  *(undefined1 *)(param_1 + 4) = *(undefined1 *)(param_2 + 0x20);
  param_1[5] = (long)(puVar6 + 0x10);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj69EE_02cc27b0
  ;
  uVar3 = *(undefined4 *)(param_2 + 0x30);
  plVar11 = param_1 + 7;
  *plVar11 = 0;
  *(undefined4 *)(param_1 + 6) = uVar3;
  param_1[2] = (long)(puVar1 + 0x10);
  param_1[8] = 0;
  param_1[9] = 0;
  if ((*(byte *)(param_2 + 0x38) & 1) == 0) {
    param_1[9] = *(long *)(param_2 + 0x48);
    lVar8 = *(long *)(param_2 + 0x38);
    param_1[8] = *(long *)(param_2 + 0x40);
    *plVar11 = lVar8;
  }
  else {
    uVar10 = *(ulong *)(param_2 + 0x40);
    uVar9 = *(undefined8 *)(param_2 + 0x48);
    if (uVar10 < 0x17) {
      lVar8 = (long)param_1 + 0x39;
      *(char *)plVar11 = (char)(uVar10 << 1);
      if (uVar10 != 0) goto code_r0x0138808c;
    }
    else {
      uVar12 = uVar10 + 0x10 & 0xfffffffffffffff0;
      if (uVar12 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar12,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (lVar8 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      param_1[8] = uVar10;
      param_1[9] = lVar8;
      param_1[7] = uVar12 | 1;
code_r0x0138808c:
      memcpy(lVar8,uVar9,uVar10);
    }
    *(undefined1 *)(lVar8 + uVar10) = 0;
  }
  puVar1 = puVar7 + 0x10;
  param_1[10] = (long)puVar1;
  lVar8 = *(long *)(param_2 + 0x58);
  param_1[10] = (long)(PTR__ZTV22CParameterPropertyBaseILj70EE_02cc3ce0 + 0x10);
  param_1[0xb] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0x60);
  puVar2 = puVar6 + 0x10;
  param_1[0xd] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xc) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIjLj70E18CPropertyConverterE_02cc4af8;
  *(undefined4 *)(param_1 + 0xe) = *(undefined4 *)(param_2 + 0x70);
  param_1[10] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x78);
  param_1[0x10] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xf) = uVar3;
  lVar8 = *(long *)(param_2 + 0x88);
  param_1[0x10] = (long)(PTR__ZTV22CParameterPropertyBaseILj71EE_02cc16f0 + 0x10);
  param_1[0x11] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0x90);
  param_1[0x13] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x12) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIjLj71E18CPropertyConverterE_02cc27b8;
  *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_2 + 0xa0);
  param_1[0x10] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0xa8);
  param_1[0x16] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x15) = uVar3;
  lVar8 = *(long *)(param_2 + 0xb8);
  param_1[0x16] = (long)(PTR__ZTV22CParameterPropertyBaseILj72EE_02cc49d0 + 0x10);
  param_1[0x17] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0xc0);
  param_1[0x19] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x18) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj72E18CPropertyConverterE_02cb7a88;
  *(undefined4 *)(param_1 + 0x1a) = *(undefined4 *)(param_2 + 0xd0);
  param_1[0x16] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0xd8);
  param_1[0x1c] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x1b) = uVar3;
  lVar8 = *(long *)(param_2 + 0xe8);
  param_1[0x1c] = (long)(PTR__ZTV22CParameterPropertyBaseILj73EE_02cc1520 + 0x10);
  param_1[0x1d] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0xf0);
  param_1[0x1f] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x1e) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIiLj73E18CPropertyConverterE_02cbb1c0;
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_2 + 0x100);
  param_1[0x1c] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x108);
  param_1[0x22] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x21) = uVar3;
  lVar8 = *(long *)(param_2 + 0x118);
  param_1[0x22] = (long)(PTR__ZTV22CParameterPropertyBaseILj74EE_02cc1bd0 + 0x10);
  param_1[0x23] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0x120);
  param_1[0x25] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x24) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj74E18CPropertyConverterE_02cb84f0;
  *(undefined4 *)(param_1 + 0x26) = *(undefined4 *)(param_2 + 0x130);
  param_1[0x22] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x138);
  param_1[0x28] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x27) = uVar3;
  lVar8 = *(long *)(param_2 + 0x148);
  param_1[0x28] = (long)(PTR__ZTV22CParameterPropertyBaseILj75EE_02cbea40 + 0x10);
  param_1[0x29] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0x150);
  param_1[0x2b] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x2a) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIiLj75E18CPropertyConverterE_02cc2110;
  *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_2 + 0x160);
  param_1[0x28] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x168);
  param_1[0x2e] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x2d) = uVar3;
  lVar8 = *(long *)(param_2 + 0x178);
  param_1[0x2e] = (long)(PTR__ZTV22CParameterPropertyBaseILj76EE_02cc1a08 + 0x10);
  param_1[0x2f] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0x180);
  param_1[0x31] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x30) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj76E18CPropertyConverterE_02cc2c98;
  *(undefined4 *)(param_1 + 0x32) = *(undefined4 *)(param_2 + 400);
  param_1[0x2e] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x198);
  param_1[0x34] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x33) = uVar3;
  lVar8 = *(long *)(param_2 + 0x1a8);
  param_1[0x34] = (long)(PTR__ZTV22CParameterPropertyBaseILj77EE_02cbf550 + 0x10);
  param_1[0x35] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0x1b0);
  param_1[0x37] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x36) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIiLj77E18CPropertyConverterE_02cbc220;
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_2 + 0x1c0);
  param_1[0x34] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x1c8);
  param_1[0x3a] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x39) = uVar3;
  lVar8 = *(long *)(param_2 + 0x1d8);
  param_1[0x3a] = (long)(PTR__ZTV22CParameterPropertyBaseILj78EE_02cc2748 + 0x10);
  param_1[0x3b] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0x1e0);
  param_1[0x3d] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x3c) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj78E18CPropertyConverterE_02cb6c10;
  *(undefined4 *)(param_1 + 0x3e) = *(undefined4 *)(param_2 + 0x1f0);
  param_1[0x3a] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x1f8);
  param_1[0x40] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x3f) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj79EE_02cb7300;
  param_1[0x41] = *(long *)(param_2 + 0x208);
  param_1[0x40] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x210);
  param_1[0x43] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x42) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIiLj79E18CPropertyConverterE_02cbc0e0;
  *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_2 + 0x220);
  param_1[0x40] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x228);
  param_1[0x46] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x45) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj80EE_02cb6c00;
  param_1[0x47] = *(long *)(param_2 + 0x238);
  param_1[0x46] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x240);
  param_1[0x49] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x48) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj80E18CPropertyConverterE_02cc1428;
  *(undefined4 *)(param_1 + 0x4a) = *(undefined4 *)(param_2 + 0x250);
  param_1[0x46] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 600);
  param_1[0x4c] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x4b) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj81EE_02cc0f08;
  param_1[0x4d] = *(long *)(param_2 + 0x268);
  param_1[0x4c] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x270);
  param_1[0x4f] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x4e) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIiLj81E18CPropertyConverterE_02cbefa0;
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_2 + 0x280);
  param_1[0x4c] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x288);
  param_1[0x52] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x51) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj82EE_02cc4fc8;
  param_1[0x53] = *(long *)(param_2 + 0x298);
  param_1[0x52] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x2a0);
  param_1[0x55] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x54) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj82E18CPropertyConverterE_02cb8f70;
  *(undefined4 *)(param_1 + 0x56) = *(undefined4 *)(param_2 + 0x2b0);
  param_1[0x52] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x2b8);
  param_1[0x58] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x57) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj83EE_02cbe348;
  param_1[0x59] = *(long *)(param_2 + 0x2c8);
  param_1[0x58] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x2d0);
  param_1[0x5b] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x5a) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIiLj83E18CPropertyConverterE_02cc0748;
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_2 + 0x2e0);
  param_1[0x58] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x2e8);
  param_1[0x5e] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x5d) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj84EE_02cc2208;
  param_1[0x5f] = *(long *)(param_2 + 0x2f8);
  param_1[0x5e] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x300);
  param_1[0x61] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x60) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj84E18CPropertyConverterE_02cbdad8;
  *(undefined4 *)(param_1 + 0x62) = *(undefined4 *)(param_2 + 0x310);
  param_1[0x5e] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x318);
  param_1[100] = (long)puVar1;
  *(undefined4 *)(param_1 + 99) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj85EE_02cbe188;
  param_1[0x65] = *(long *)(param_2 + 0x328);
  param_1[100] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x330);
  param_1[0x67] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x66) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIiLj85E18CPropertyConverterE_02cc0b90;
  *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_2 + 0x340);
  param_1[100] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x348);
  param_1[0x6a] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x69) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj86EE_02cc2fd8;
  param_1[0x6b] = *(long *)(param_2 + 0x358);
  param_1[0x6a] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x360);
  param_1[0x6d] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x6c) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj86E18CPropertyConverterE_02cb7aa0;
  *(undefined4 *)(param_1 + 0x6e) = *(undefined4 *)(param_2 + 0x370);
  param_1[0x6a] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x378);
  param_1[0x70] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x6f) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj87EE_02cbee28;
  param_1[0x71] = *(long *)(param_2 + 0x388);
  param_1[0x70] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x390);
  param_1[0x73] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x72) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIiLj87E18CPropertyConverterE_02cbee50;
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_2 + 0x3a0);
  param_1[0x70] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x3a8);
  param_1[0x76] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x75) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj88EE_02cbab60;
  param_1[0x77] = *(long *)(param_2 + 0x3b8);
  param_1[0x76] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x3c0);
  param_1[0x79] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x78) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj88E18CPropertyConverterE_02cbee10;
  *(undefined4 *)(param_1 + 0x7a) = *(undefined4 *)(param_2 + 0x3d0);
  param_1[0x76] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x3d8);
  param_1[0x7c] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x7b) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj89EE_02cba390;
  param_1[0x7d] = *(long *)(param_2 + 1000);
  param_1[0x7c] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x3f0);
  param_1[0x7f] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x7e) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIiLj89E18CPropertyConverterE_02cbee78;
  *(undefined4 *)(param_1 + 0x80) = *(undefined4 *)(param_2 + 0x400);
  param_1[0x7c] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x408);
  param_1[0x82] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x81) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj90EE_02cb98a8;
  param_1[0x83] = *(long *)(param_2 + 0x418);
  param_1[0x82] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x420);
  param_1[0x85] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x84) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj90E18CPropertyConverterE_02cc3530;
  *(undefined4 *)(param_1 + 0x86) = *(undefined4 *)(param_2 + 0x430);
  param_1[0x82] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x438);
  param_1[0x88] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x87) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj91EE_02cbc970;
  param_1[0x89] = *(long *)(param_2 + 0x448);
  param_1[0x88] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x450);
  param_1[0x8b] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x8a) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIiLj91E18CPropertyConverterE_02cbf540;
  *(undefined4 *)(param_1 + 0x8c) = *(undefined4 *)(param_2 + 0x460);
  param_1[0x88] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x468);
  param_1[0x8e] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x8d) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj92EE_02cba3e8;
  param_1[0x8f] = *(long *)(param_2 + 0x478);
  param_1[0x8e] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x480);
  param_1[0x91] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x90) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj92E18CPropertyConverterE_02cc45d8;
  *(undefined4 *)(param_1 + 0x92) = *(undefined4 *)(param_2 + 0x490);
  param_1[0x8e] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x498);
  param_1[0x94] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x93) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj93EE_02cbd5e8;
  param_1[0x95] = *(long *)(param_2 + 0x4a8);
  param_1[0x94] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x4b0);
  param_1[0x97] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x96) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIiLj93E18CPropertyConverterE_02cb78d0;
  *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(param_2 + 0x4c0);
  param_1[0x94] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x4c8);
  param_1[0x9a] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x99) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj94EE_02cba2b0;
  param_1[0x9b] = *(long *)(param_2 + 0x4d8);
  param_1[0x9a] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x4e0);
  param_1[0x9d] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x9c) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj94E18CPropertyConverterE_02cbb1d8;
  *(undefined4 *)(param_1 + 0x9e) = *(undefined4 *)(param_2 + 0x4f0);
  param_1[0x9a] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x4f8);
  param_1[0xa0] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x9f) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj95EE_02cba878;
  param_1[0xa1] = *(long *)(param_2 + 0x508);
  param_1[0xa0] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x510);
  param_1[0xa3] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xa2) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIiLj95E18CPropertyConverterE_02cc2b58;
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_2 + 0x520);
  param_1[0xa0] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x528);
  param_1[0xa6] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xa5) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj96EE_02cb75b0;
  param_1[0xa7] = *(long *)(param_2 + 0x538);
  param_1[0xa6] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x540);
  param_1[0xa9] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xa8) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj96E18CPropertyConverterE_02cbe058;
  *(undefined4 *)(param_1 + 0xaa) = *(undefined4 *)(param_2 + 0x550);
  param_1[0xa6] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x558);
  param_1[0xac] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xab) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj97EE_02cba650;
  param_1[0xad] = *(long *)(param_2 + 0x568);
  param_1[0xac] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x570);
  param_1[0xaf] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xae) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIiLj97E18CPropertyConverterE_02cbe7f0;
  *(undefined4 *)(param_1 + 0xb0) = *(undefined4 *)(param_2 + 0x580);
  param_1[0xac] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x588);
  param_1[0xb2] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xb1) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj98EE_02cb81c0;
  param_1[0xb3] = *(long *)(param_2 + 0x598);
  param_1[0xb2] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x5a0);
  param_1[0xb5] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xb4) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj98E18CPropertyConverterE_02cb8a58;
  *(undefined4 *)(param_1 + 0xb6) = *(undefined4 *)(param_2 + 0x5b0);
  param_1[0xb2] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x5b8);
  param_1[0xb8] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xb7) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj99EE_02cbb310;
  param_1[0xb9] = *(long *)(param_2 + 0x5c8);
  param_1[0xb8] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x5d0);
  param_1[0xbb] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xba) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIiLj99E18CPropertyConverterE_02cc3f10;
  *(undefined4 *)(param_1 + 0xbc) = *(undefined4 *)(param_2 + 0x5e0);
  param_1[0xb8] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x5e8);
  param_1[0xbe] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xbd) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj100EE_02cc23f0;
  param_1[0xbf] = *(long *)(param_2 + 0x5f8);
  param_1[0xbe] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x600);
  param_1[0xc1] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xc0) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj100E18CPropertyConverterE_02cbcdf0;
  *(undefined4 *)(param_1 + 0xc2) = *(undefined4 *)(param_2 + 0x610);
  param_1[0xbe] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x618);
  param_1[0xc4] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xc3) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj101EE_02cbe0f0;
  param_1[0xc5] = *(long *)(param_2 + 0x628);
  param_1[0xc4] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x630);
  param_1[199] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xc6) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIiLj101E18CPropertyConverterE_02cbfd00;
  *(undefined4 *)(param_1 + 200) = *(undefined4 *)(param_2 + 0x640);
  param_1[0xc4] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x648);
  param_1[0xca] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xc9) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj102EE_02cb7580;
  param_1[0xcb] = *(long *)(param_2 + 0x658);
  param_1[0xca] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x660);
  param_1[0xcd] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xcc) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj102E18CPropertyConverterE_02cc1200;
  *(undefined4 *)(param_1 + 0xce) = *(undefined4 *)(param_2 + 0x670);
  param_1[0xca] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x678);
  param_1[0xd0] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xcf) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj103EE_02cb80d8;
  param_1[0xd1] = *(long *)(param_2 + 0x688);
  param_1[0xd0] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x690);
  param_1[0xd3] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xd2) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIiLj103E18CPropertyConverterE_02cc2118;
  *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(param_2 + 0x6a0);
  param_1[0xd0] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x6a8);
  param_1[0xd6] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xd5) = uVar3;
  puVar5 = PTR__ZTV22CParameterPropertyBaseILj104EE_02cbc2d0;
  param_1[0xd7] = *(long *)(param_2 + 0x6b8);
  param_1[0xd6] = (long)(puVar5 + 0x10);
  uVar4 = *(undefined1 *)(param_2 + 0x6c0);
  param_1[0xd9] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xd8) = uVar4;
  puVar5 = PTR__ZTV23CParameterPropertyValueIfLj104E18CPropertyConverterE_02cbf828;
  *(undefined4 *)(param_1 + 0xda) = *(undefined4 *)(param_2 + 0x6d0);
  param_1[0xd6] = (long)(puVar5 + 0x10);
  uVar3 = *(undefined4 *)(param_2 + 0x6d8);
  param_1[0xdc] = (long)puVar1;
  *(undefined4 *)(param_1 + 0xdb) = uVar3;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj105EE_02cc2cd0;
  param_1[0xdd] = *(long *)(param_2 + 0x6e8);
  param_1[0xdc] = (long)(puVar1 + 0x10);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj105EE_02cbc338
  ;
  uVar4 = *(undefined1 *)(param_2 + 0x6f0);
  param_1[0xdf] = (long)puVar2;
  *(undefined1 *)(param_1 + 0xde) = uVar4;
  uVar3 = *(undefined4 *)(param_2 + 0x700);
  param_1[0xdc] = (long)(puVar1 + 0x10);
  param_1[0xe3] = 0;
  param_1[0xe2] = 0;
  *(undefined4 *)(param_1 + 0xe0) = uVar3;
  param_1[0xe1] = 0;
  if ((*(byte *)(param_2 + 0x708) & 1) == 0) {
    param_1[0xe3] = *(long *)(param_2 + 0x718);
    lVar8 = *(long *)(param_2 + 0x708);
    param_1[0xe2] = *(long *)(param_2 + 0x710);
    param_1[0xe1] = lVar8;
  }
  else {
    uVar10 = *(ulong *)(param_2 + 0x710);
    uVar9 = *(undefined8 *)(param_2 + 0x718);
    if (uVar10 < 0x17) {
      lVar8 = (long)param_1 + 0x709;
      *(char *)(param_1 + 0xe1) = (char)(uVar10 << 1);
      if (uVar10 != 0) goto code_r0x01388b54;
    }
    else {
      uVar12 = uVar10 + 0x10 & 0xfffffffffffffff0;
      if (uVar12 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar12,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (lVar8 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      param_1[0xe3] = lVar8;
      param_1[0xe1] = uVar12 | 1;
      param_1[0xe2] = uVar10;
code_r0x01388b54:
      memcpy(lVar8,uVar9,uVar10);
    }
    *(undefined1 *)(lVar8 + uVar10) = 0;
  }
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj106EE_02cc4338;
  param_1[0xe4] = (long)(puVar7 + 0x10);
  lVar8 = *(long *)(param_2 + 0x728);
  param_1[0xe4] = (long)(puVar1 + 0x10);
  param_1[0xe5] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0x730);
  param_1[0xe7] = (long)(puVar6 + 0x10);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj106EE_02cc3f00
  ;
  *(undefined1 *)(param_1 + 0xe6) = uVar4;
  uVar3 = *(undefined4 *)(param_2 + 0x740);
  param_1[0xeb] = 0;
  param_1[0xe4] = (long)(puVar1 + 0x10);
  param_1[0xea] = 0;
  *(undefined4 *)(param_1 + 0xe8) = uVar3;
  param_1[0xe9] = 0;
  if ((*(byte *)(param_2 + 0x748) & 1) == 0) {
    param_1[0xeb] = *(long *)(param_2 + 0x758);
    lVar8 = *(long *)(param_2 + 0x748);
    param_1[0xea] = *(long *)(param_2 + 0x750);
    param_1[0xe9] = lVar8;
  }
  else {
    uVar10 = *(ulong *)(param_2 + 0x750);
    uVar9 = *(undefined8 *)(param_2 + 0x758);
    if (uVar10 < 0x17) {
      lVar8 = (long)param_1 + 0x749;
      *(char *)(param_1 + 0xe9) = (char)(uVar10 << 1);
      if (uVar10 != 0) goto code_r0x01388c68;
    }
    else {
      uVar12 = uVar10 + 0x10 & 0xfffffffffffffff0;
      if (uVar12 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar12,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (lVar8 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      param_1[0xeb] = lVar8;
      param_1[0xe9] = uVar12 | 1;
      param_1[0xea] = uVar10;
code_r0x01388c68:
      memcpy(lVar8,uVar9,uVar10);
    }
    *(undefined1 *)(lVar8 + uVar10) = 0;
  }
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj107EE_02cb8570;
  param_1[0xec] = (long)(puVar7 + 0x10);
  lVar8 = *(long *)(param_2 + 0x768);
  param_1[0xec] = (long)(puVar1 + 0x10);
  param_1[0xed] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0x770);
  param_1[0xef] = (long)(puVar6 + 0x10);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj107EE_02cbf0c0
  ;
  *(undefined1 *)(param_1 + 0xee) = uVar4;
  uVar3 = *(undefined4 *)(param_2 + 0x780);
  param_1[0xf3] = 0;
  param_1[0xec] = (long)(puVar1 + 0x10);
  param_1[0xf2] = 0;
  *(undefined4 *)(param_1 + 0xf0) = uVar3;
  param_1[0xf1] = 0;
  if ((*(byte *)(param_2 + 0x788) & 1) == 0) {
    param_1[0xf3] = *(long *)(param_2 + 0x798);
    lVar8 = *(long *)(param_2 + 0x788);
    param_1[0xf2] = *(long *)(param_2 + 0x790);
    param_1[0xf1] = lVar8;
  }
  else {
    uVar10 = *(ulong *)(param_2 + 0x790);
    uVar9 = *(undefined8 *)(param_2 + 0x798);
    if (uVar10 < 0x17) {
      lVar8 = (long)param_1 + 0x789;
      *(char *)(param_1 + 0xf1) = (char)(uVar10 << 1);
      if (uVar10 != 0) goto code_r0x01388d7c;
    }
    else {
      uVar12 = uVar10 + 0x10 & 0xfffffffffffffff0;
      if (uVar12 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar12,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (lVar8 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      param_1[0xf3] = lVar8;
      param_1[0xf1] = uVar12 | 1;
      param_1[0xf2] = uVar10;
code_r0x01388d7c:
      memcpy(lVar8,uVar9,uVar10);
    }
    *(undefined1 *)(lVar8 + uVar10) = 0;
  }
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj108EE_02cc2bd8;
  param_1[0xf4] = (long)(puVar7 + 0x10);
  lVar8 = *(long *)(param_2 + 0x7a8);
  param_1[0xf4] = (long)(puVar1 + 0x10);
  param_1[0xf5] = lVar8;
  uVar4 = *(undefined1 *)(param_2 + 0x7b0);
  param_1[0xf7] = (long)(puVar6 + 0x10);
  puVar6 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj108EE_02cb94e8
  ;
  *(undefined1 *)(param_1 + 0xf6) = uVar4;
  uVar3 = *(undefined4 *)(param_2 + 0x7c0);
  param_1[0xfb] = 0;
  param_1[0xf4] = (long)(puVar6 + 0x10);
  param_1[0xfa] = 0;
  *(undefined4 *)(param_1 + 0xf8) = uVar3;
  param_1[0xf9] = 0;
  if ((*(byte *)(param_2 + 0x7c8) & 1) == 0) {
    param_1[0xfb] = *(long *)(param_2 + 0x7d8);
    lVar8 = *(long *)(param_2 + 0x7c8);
    param_1[0xfa] = *(long *)(param_2 + 2000);
    param_1[0xf9] = lVar8;
    return;
  }
  uVar10 = *(ulong *)(param_2 + 2000);
  uVar9 = *(undefined8 *)(param_2 + 0x7d8);
  if (uVar10 < 0x17) {
    lVar8 = (long)param_1 + 0x7c9;
    *(char *)(param_1 + 0xf9) = (char)(uVar10 << 1);
    if (uVar10 == 0) goto code_r0x01388ea0;
  }
  else {
    uVar12 = uVar10 + 0x10 & 0xfffffffffffffff0;
    if (uVar12 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar12,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (lVar8 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[0xfb] = lVar8;
    param_1[0xf9] = uVar12 | 1;
    param_1[0xfa] = uVar10;
  }
  memcpy(lVar8,uVar9,uVar10);
code_r0x01388ea0:
  *(undefined1 *)(lVar8 + uVar10) = 0;
  return;
}

// ==== CMasterParameterSignalElement::operator=(CMasterParameterSignalElement const&)
// vaddr 0x1329ea4 | ghidra 0x1429ea4 | size 2264 | symbol _ZN29CMasterParameterSignalElementaSERKS_ | lib libSOA-3.7.0.so | 2026-10-08
long _ZN29CMasterParameterSignalElementaSERKS_(long param_1,long param_2)

{
  ulong *puVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  ulong uVar5;
  long lVar6;
  
  *(undefined8 *)(param_1 + 8) = *(undefined8 *)(param_2 + 8);
  *(undefined8 *)(param_1 + 0x18) = *(undefined8 *)(param_2 + 0x18);
  *(undefined1 *)(param_1 + 0x20) = *(undefined1 *)(param_2 + 0x20);
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_2 + 0x30);
  if (param_1 != param_2) {
    puVar1 = (ulong *)(param_1 + 0x38);
    uVar5 = *(ulong *)(param_2 + 0x40);
    lVar4 = *(long *)(param_2 + 0x48);
    uVar3 = (ulong)*(byte *)puVar1;
    if ((*(byte *)(param_2 + 0x38) & 1) == 0) {
      lVar4 = param_2 + 0x39;
      uVar5 = (ulong)(*(byte *)(param_2 + 0x38) >> 1);
    }
    if ((*(byte *)puVar1 & 1) == 0) {
      uVar2 = 0x16;
      lVar6 = uVar5 - 0x16;
      if (0x15 < uVar5 && lVar6 != 0) {
code_r0x01429f38:
        if ((uVar3 & 1) == 0) {
          uVar3 = (ulong)(((uint)uVar3 & 0xfe) >> 1);
        }
        else {
          uVar3 = *(ulong *)(param_1 + 0x40);
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar2,lVar6,uVar3,0,uVar3,uVar5);
        goto code_r0x01429f98;
      }
    }
    else {
      uVar3 = *puVar1;
      uVar2 = (uVar3 & 0xfffffffffffffffe) - 1;
      lVar6 = uVar5 - uVar2;
      if (uVar2 <= uVar5 && lVar6 != 0) goto code_r0x01429f38;
    }
    if ((uVar3 & 1) == 0) {
      lVar6 = param_1 + 0x39;
    }
    else {
      lVar6 = *(long *)(param_1 + 0x48);
    }
    if (uVar5 != 0) {
      memmove(lVar6,lVar4,uVar5);
    }
    *(undefined1 *)(lVar6 + uVar5) = 0;
    if ((*(byte *)puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar5 << 1);
    }
    else {
      *(ulong *)(param_1 + 0x40) = uVar5;
    }
  }
code_r0x01429f98:
  *(undefined8 *)(param_1 + 0x58) = *(undefined8 *)(param_2 + 0x58);
  *(undefined1 *)(param_1 + 0x60) = *(undefined1 *)(param_2 + 0x60);
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_2 + 0x70);
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_2 + 0x78);
  *(undefined8 *)(param_1 + 0x88) = *(undefined8 *)(param_2 + 0x88);
  *(undefined1 *)(param_1 + 0x90) = *(undefined1 *)(param_2 + 0x90);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_2 + 0xa0);
  *(undefined4 *)(param_1 + 0xa8) = *(undefined4 *)(param_2 + 0xa8);
  *(undefined8 *)(param_1 + 0xb8) = *(undefined8 *)(param_2 + 0xb8);
  *(undefined1 *)(param_1 + 0xc0) = *(undefined1 *)(param_2 + 0xc0);
  *(undefined4 *)(param_1 + 0xd0) = *(undefined4 *)(param_2 + 0xd0);
  *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(param_2 + 0xd8);
  *(undefined8 *)(param_1 + 0xe8) = *(undefined8 *)(param_2 + 0xe8);
  *(undefined1 *)(param_1 + 0xf0) = *(undefined1 *)(param_2 + 0xf0);
  *(undefined4 *)(param_1 + 0x100) = *(undefined4 *)(param_2 + 0x100);
  *(undefined4 *)(param_1 + 0x108) = *(undefined4 *)(param_2 + 0x108);
  *(undefined8 *)(param_1 + 0x118) = *(undefined8 *)(param_2 + 0x118);
  *(undefined1 *)(param_1 + 0x120) = *(undefined1 *)(param_2 + 0x120);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_2 + 0x130);
  *(undefined4 *)(param_1 + 0x138) = *(undefined4 *)(param_2 + 0x138);
  *(undefined8 *)(param_1 + 0x148) = *(undefined8 *)(param_2 + 0x148);
  *(undefined1 *)(param_1 + 0x150) = *(undefined1 *)(param_2 + 0x150);
  *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_2 + 0x160);
  *(undefined4 *)(param_1 + 0x168) = *(undefined4 *)(param_2 + 0x168);
  *(undefined8 *)(param_1 + 0x178) = *(undefined8 *)(param_2 + 0x178);
  *(undefined1 *)(param_1 + 0x180) = *(undefined1 *)(param_2 + 0x180);
  *(undefined4 *)(param_1 + 400) = *(undefined4 *)(param_2 + 400);
  *(undefined4 *)(param_1 + 0x198) = *(undefined4 *)(param_2 + 0x198);
  *(undefined8 *)(param_1 + 0x1a8) = *(undefined8 *)(param_2 + 0x1a8);
  *(undefined1 *)(param_1 + 0x1b0) = *(undefined1 *)(param_2 + 0x1b0);
  *(undefined4 *)(param_1 + 0x1c0) = *(undefined4 *)(param_2 + 0x1c0);
  *(undefined4 *)(param_1 + 0x1c8) = *(undefined4 *)(param_2 + 0x1c8);
  *(undefined8 *)(param_1 + 0x1d8) = *(undefined8 *)(param_2 + 0x1d8);
  *(undefined1 *)(param_1 + 0x1e0) = *(undefined1 *)(param_2 + 0x1e0);
  *(undefined4 *)(param_1 + 0x1f0) = *(undefined4 *)(param_2 + 0x1f0);
  *(undefined4 *)(param_1 + 0x1f8) = *(undefined4 *)(param_2 + 0x1f8);
  *(undefined8 *)(param_1 + 0x208) = *(undefined8 *)(param_2 + 0x208);
  *(undefined1 *)(param_1 + 0x210) = *(undefined1 *)(param_2 + 0x210);
  *(undefined4 *)(param_1 + 0x220) = *(undefined4 *)(param_2 + 0x220);
  *(undefined4 *)(param_1 + 0x228) = *(undefined4 *)(param_2 + 0x228);
  *(undefined8 *)(param_1 + 0x238) = *(undefined8 *)(param_2 + 0x238);
  *(undefined1 *)(param_1 + 0x240) = *(undefined1 *)(param_2 + 0x240);
  *(undefined4 *)(param_1 + 0x250) = *(undefined4 *)(param_2 + 0x250);
  *(undefined4 *)(param_1 + 600) = *(undefined4 *)(param_2 + 600);
  *(undefined8 *)(param_1 + 0x268) = *(undefined8 *)(param_2 + 0x268);
  *(undefined1 *)(param_1 + 0x270) = *(undefined1 *)(param_2 + 0x270);
  *(undefined4 *)(param_1 + 0x280) = *(undefined4 *)(param_2 + 0x280);
  *(undefined4 *)(param_1 + 0x288) = *(undefined4 *)(param_2 + 0x288);
  *(undefined8 *)(param_1 + 0x298) = *(undefined8 *)(param_2 + 0x298);
  *(undefined1 *)(param_1 + 0x2a0) = *(undefined1 *)(param_2 + 0x2a0);
  *(undefined4 *)(param_1 + 0x2b0) = *(undefined4 *)(param_2 + 0x2b0);
  *(undefined4 *)(param_1 + 0x2b8) = *(undefined4 *)(param_2 + 0x2b8);
  *(undefined8 *)(param_1 + 0x2c8) = *(undefined8 *)(param_2 + 0x2c8);
  *(undefined1 *)(param_1 + 0x2d0) = *(undefined1 *)(param_2 + 0x2d0);
  *(undefined4 *)(param_1 + 0x2e0) = *(undefined4 *)(param_2 + 0x2e0);
  *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_2 + 0x2e8);
  *(undefined8 *)(param_1 + 0x2f8) = *(undefined8 *)(param_2 + 0x2f8);
  *(undefined1 *)(param_1 + 0x300) = *(undefined1 *)(param_2 + 0x300);
  *(undefined4 *)(param_1 + 0x310) = *(undefined4 *)(param_2 + 0x310);
  *(undefined4 *)(param_1 + 0x318) = *(undefined4 *)(param_2 + 0x318);
  *(undefined8 *)(param_1 + 0x328) = *(undefined8 *)(param_2 + 0x328);
  *(undefined1 *)(param_1 + 0x330) = *(undefined1 *)(param_2 + 0x330);
  *(undefined4 *)(param_1 + 0x340) = *(undefined4 *)(param_2 + 0x340);
  *(undefined4 *)(param_1 + 0x348) = *(undefined4 *)(param_2 + 0x348);
  *(undefined8 *)(param_1 + 0x358) = *(undefined8 *)(param_2 + 0x358);
  *(undefined1 *)(param_1 + 0x360) = *(undefined1 *)(param_2 + 0x360);
  *(undefined4 *)(param_1 + 0x370) = *(undefined4 *)(param_2 + 0x370);
  *(undefined4 *)(param_1 + 0x378) = *(undefined4 *)(param_2 + 0x378);
  *(undefined8 *)(param_1 + 0x388) = *(undefined8 *)(param_2 + 0x388);
  *(undefined1 *)(param_1 + 0x390) = *(undefined1 *)(param_2 + 0x390);
  *(undefined4 *)(param_1 + 0x3a0) = *(undefined4 *)(param_2 + 0x3a0);
  *(undefined4 *)(param_1 + 0x3a8) = *(undefined4 *)(param_2 + 0x3a8);
  *(undefined8 *)(param_1 + 0x3b8) = *(undefined8 *)(param_2 + 0x3b8);
  *(undefined1 *)(param_1 + 0x3c0) = *(undefined1 *)(param_2 + 0x3c0);
  *(undefined4 *)(param_1 + 0x3d0) = *(undefined4 *)(param_2 + 0x3d0);
  *(undefined4 *)(param_1 + 0x3d8) = *(undefined4 *)(param_2 + 0x3d8);
  *(undefined8 *)(param_1 + 1000) = *(undefined8 *)(param_2 + 1000);
  *(undefined1 *)(param_1 + 0x3f0) = *(undefined1 *)(param_2 + 0x3f0);
  *(undefined4 *)(param_1 + 0x400) = *(undefined4 *)(param_2 + 0x400);
  *(undefined4 *)(param_1 + 0x408) = *(undefined4 *)(param_2 + 0x408);
  *(undefined8 *)(param_1 + 0x418) = *(undefined8 *)(param_2 + 0x418);
  *(undefined1 *)(param_1 + 0x420) = *(undefined1 *)(param_2 + 0x420);
  *(undefined4 *)(param_1 + 0x430) = *(undefined4 *)(param_2 + 0x430);
  *(undefined4 *)(param_1 + 0x438) = *(undefined4 *)(param_2 + 0x438);
  *(undefined8 *)(param_1 + 0x448) = *(undefined8 *)(param_2 + 0x448);
  *(undefined1 *)(param_1 + 0x450) = *(undefined1 *)(param_2 + 0x450);
  *(undefined4 *)(param_1 + 0x460) = *(undefined4 *)(param_2 + 0x460);
  *(undefined4 *)(param_1 + 0x468) = *(undefined4 *)(param_2 + 0x468);
  *(undefined8 *)(param_1 + 0x478) = *(undefined8 *)(param_2 + 0x478);
  *(undefined1 *)(param_1 + 0x480) = *(undefined1 *)(param_2 + 0x480);
  *(undefined4 *)(param_1 + 0x490) = *(undefined4 *)(param_2 + 0x490);
  *(undefined4 *)(param_1 + 0x498) = *(undefined4 *)(param_2 + 0x498);
  *(undefined8 *)(param_1 + 0x4a8) = *(undefined8 *)(param_2 + 0x4a8);
  *(undefined1 *)(param_1 + 0x4b0) = *(undefined1 *)(param_2 + 0x4b0);
  *(undefined4 *)(param_1 + 0x4c0) = *(undefined4 *)(param_2 + 0x4c0);
  *(undefined4 *)(param_1 + 0x4c8) = *(undefined4 *)(param_2 + 0x4c8);
  *(undefined8 *)(param_1 + 0x4d8) = *(undefined8 *)(param_2 + 0x4d8);
  *(undefined1 *)(param_1 + 0x4e0) = *(undefined1 *)(param_2 + 0x4e0);
  *(undefined4 *)(param_1 + 0x4f0) = *(undefined4 *)(param_2 + 0x4f0);
  *(undefined4 *)(param_1 + 0x4f8) = *(undefined4 *)(param_2 + 0x4f8);
  *(undefined8 *)(param_1 + 0x508) = *(undefined8 *)(param_2 + 0x508);
  *(undefined1 *)(param_1 + 0x510) = *(undefined1 *)(param_2 + 0x510);
  *(undefined4 *)(param_1 + 0x520) = *(undefined4 *)(param_2 + 0x520);
  *(undefined4 *)(param_1 + 0x528) = *(undefined4 *)(param_2 + 0x528);
  *(undefined8 *)(param_1 + 0x538) = *(undefined8 *)(param_2 + 0x538);
  *(undefined1 *)(param_1 + 0x540) = *(undefined1 *)(param_2 + 0x540);
  *(undefined4 *)(param_1 + 0x550) = *(undefined4 *)(param_2 + 0x550);
  *(undefined4 *)(param_1 + 0x558) = *(undefined4 *)(param_2 + 0x558);
  *(undefined8 *)(param_1 + 0x568) = *(undefined8 *)(param_2 + 0x568);
  *(undefined1 *)(param_1 + 0x570) = *(undefined1 *)(param_2 + 0x570);
  *(undefined4 *)(param_1 + 0x580) = *(undefined4 *)(param_2 + 0x580);
  *(undefined4 *)(param_1 + 0x588) = *(undefined4 *)(param_2 + 0x588);
  *(undefined8 *)(param_1 + 0x598) = *(undefined8 *)(param_2 + 0x598);
  *(undefined1 *)(param_1 + 0x5a0) = *(undefined1 *)(param_2 + 0x5a0);
  *(undefined4 *)(param_1 + 0x5b0) = *(undefined4 *)(param_2 + 0x5b0);
  *(undefined4 *)(param_1 + 0x5b8) = *(undefined4 *)(param_2 + 0x5b8);
  *(undefined8 *)(param_1 + 0x5c8) = *(undefined8 *)(param_2 + 0x5c8);
  *(undefined1 *)(param_1 + 0x5d0) = *(undefined1 *)(param_2 + 0x5d0);
  *(undefined4 *)(param_1 + 0x5e0) = *(undefined4 *)(param_2 + 0x5e0);
  *(undefined4 *)(param_1 + 0x5e8) = *(undefined4 *)(param_2 + 0x5e8);
  *(undefined8 *)(param_1 + 0x5f8) = *(undefined8 *)(param_2 + 0x5f8);
  *(undefined1 *)(param_1 + 0x600) = *(undefined1 *)(param_2 + 0x600);
  *(undefined4 *)(param_1 + 0x610) = *(undefined4 *)(param_2 + 0x610);
  *(undefined4 *)(param_1 + 0x618) = *(undefined4 *)(param_2 + 0x618);
  *(undefined8 *)(param_1 + 0x628) = *(undefined8 *)(param_2 + 0x628);
  *(undefined1 *)(param_1 + 0x630) = *(undefined1 *)(param_2 + 0x630);
  *(undefined4 *)(param_1 + 0x640) = *(undefined4 *)(param_2 + 0x640);
  *(undefined4 *)(param_1 + 0x648) = *(undefined4 *)(param_2 + 0x648);
  *(undefined8 *)(param_1 + 0x658) = *(undefined8 *)(param_2 + 0x658);
  *(undefined1 *)(param_1 + 0x660) = *(undefined1 *)(param_2 + 0x660);
  *(undefined4 *)(param_1 + 0x670) = *(undefined4 *)(param_2 + 0x670);
  *(undefined4 *)(param_1 + 0x678) = *(undefined4 *)(param_2 + 0x678);
  *(undefined8 *)(param_1 + 0x688) = *(undefined8 *)(param_2 + 0x688);
  *(undefined1 *)(param_1 + 0x690) = *(undefined1 *)(param_2 + 0x690);
  *(undefined4 *)(param_1 + 0x6a0) = *(undefined4 *)(param_2 + 0x6a0);
  *(undefined4 *)(param_1 + 0x6a8) = *(undefined4 *)(param_2 + 0x6a8);
  *(undefined8 *)(param_1 + 0x6b8) = *(undefined8 *)(param_2 + 0x6b8);
  *(undefined1 *)(param_1 + 0x6c0) = *(undefined1 *)(param_2 + 0x6c0);
  *(undefined4 *)(param_1 + 0x6d0) = *(undefined4 *)(param_2 + 0x6d0);
  *(undefined4 *)(param_1 + 0x6d8) = *(undefined4 *)(param_2 + 0x6d8);
  *(undefined8 *)(param_1 + 0x6e8) = *(undefined8 *)(param_2 + 0x6e8);
  *(undefined1 *)(param_1 + 0x6f0) = *(undefined1 *)(param_2 + 0x6f0);
  *(undefined4 *)(param_1 + 0x700) = *(undefined4 *)(param_2 + 0x700);
  if (param_1 != param_2) {
    puVar1 = (ulong *)(param_1 + 0x708);
    lVar4 = *(long *)(param_2 + 0x718);
    uVar5 = *(ulong *)(param_2 + 0x710);
    uVar3 = (ulong)*(byte *)puVar1;
    if ((*(byte *)(param_2 + 0x708) & 1) == 0) {
      lVar4 = param_2 + 0x709;
      uVar5 = (ulong)(*(byte *)(param_2 + 0x708) >> 1);
    }
    if ((*(byte *)puVar1 & 1) == 0) {
      uVar2 = 0x16;
      lVar6 = uVar5 - 0x16;
      if (0x15 < uVar5 && lVar6 != 0) {
code_r0x0142a474:
        if ((uVar3 & 1) == 0) {
          uVar3 = (ulong)(((uint)uVar3 & 0xfe) >> 1);
        }
        else {
          uVar3 = *(ulong *)(param_1 + 0x710);
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar2,lVar6,uVar3,0,uVar3,uVar5);
        goto code_r0x0142a4d4;
      }
    }
    else {
      uVar3 = *puVar1;
      uVar2 = (uVar3 & 0xfffffffffffffffe) - 1;
      lVar6 = uVar5 - uVar2;
      if (uVar2 <= uVar5 && lVar6 != 0) goto code_r0x0142a474;
    }
    if ((uVar3 & 1) == 0) {
      lVar6 = param_1 + 0x709;
    }
    else {
      lVar6 = *(long *)(param_1 + 0x718);
    }
    if (uVar5 != 0) {
      memmove(lVar6,lVar4,uVar5);
    }
    *(undefined1 *)(lVar6 + uVar5) = 0;
    if ((*(byte *)puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar5 << 1);
    }
    else {
      *(ulong *)(param_1 + 0x710) = uVar5;
    }
  }
code_r0x0142a4d4:
  *(undefined8 *)(param_1 + 0x728) = *(undefined8 *)(param_2 + 0x728);
  *(undefined1 *)(param_1 + 0x730) = *(undefined1 *)(param_2 + 0x730);
  *(undefined4 *)(param_1 + 0x740) = *(undefined4 *)(param_2 + 0x740);
  if (param_1 != param_2) {
    puVar1 = (ulong *)(param_1 + 0x748);
    lVar4 = *(long *)(param_2 + 0x758);
    uVar5 = *(ulong *)(param_2 + 0x750);
    uVar3 = (ulong)*(byte *)puVar1;
    if ((*(byte *)(param_2 + 0x748) & 1) == 0) {
      lVar4 = param_2 + 0x749;
      uVar5 = (ulong)(*(byte *)(param_2 + 0x748) >> 1);
    }
    if ((*(byte *)puVar1 & 1) == 0) {
      uVar2 = 0x16;
      lVar6 = uVar5 - 0x16;
      if (0x15 < uVar5 && lVar6 != 0) {
code_r0x0142a550:
        if ((uVar3 & 1) == 0) {
          uVar3 = (ulong)(((uint)uVar3 & 0xfe) >> 1);
        }
        else {
          uVar3 = *(ulong *)(param_1 + 0x750);
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar2,lVar6,uVar3,0,uVar3,uVar5);
        goto code_r0x0142a5b0;
      }
    }
    else {
      uVar3 = *puVar1;
      uVar2 = (uVar3 & 0xfffffffffffffffe) - 1;
      lVar6 = uVar5 - uVar2;
      if (uVar2 <= uVar5 && lVar6 != 0) goto code_r0x0142a550;
    }
    if ((uVar3 & 1) == 0) {
      lVar6 = param_1 + 0x749;
    }
    else {
      lVar6 = *(long *)(param_1 + 0x758);
    }
    if (uVar5 != 0) {
      memmove(lVar6,lVar4,uVar5);
    }
    *(undefined1 *)(lVar6 + uVar5) = 0;
    if ((*(byte *)puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar5 << 1);
    }
    else {
      *(ulong *)(param_1 + 0x750) = uVar5;
    }
  }
code_r0x0142a5b0:
  *(undefined8 *)(param_1 + 0x768) = *(undefined8 *)(param_2 + 0x768);
  *(undefined1 *)(param_1 + 0x770) = *(undefined1 *)(param_2 + 0x770);
  *(undefined4 *)(param_1 + 0x780) = *(undefined4 *)(param_2 + 0x780);
  if (param_1 != param_2) {
    puVar1 = (ulong *)(param_1 + 0x788);
    lVar4 = *(long *)(param_2 + 0x798);
    uVar5 = *(ulong *)(param_2 + 0x790);
    uVar3 = (ulong)*(byte *)puVar1;
    if ((*(byte *)(param_2 + 0x788) & 1) == 0) {
      lVar4 = param_2 + 0x789;
      uVar5 = (ulong)(*(byte *)(param_2 + 0x788) >> 1);
    }
    if ((*(byte *)puVar1 & 1) == 0) {
      uVar2 = 0x16;
      lVar6 = uVar5 - 0x16;
      if (0x15 < uVar5 && lVar6 != 0) {
code_r0x0142a62c:
        if ((uVar3 & 1) == 0) {
          uVar3 = (ulong)(((uint)uVar3 & 0xfe) >> 1);
        }
        else {
          uVar3 = *(ulong *)(param_1 + 0x790);
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar2,lVar6,uVar3,0,uVar3,uVar5);
        goto code_r0x0142a68c;
      }
    }
    else {
      uVar3 = *puVar1;
      uVar2 = (uVar3 & 0xfffffffffffffffe) - 1;
      lVar6 = uVar5 - uVar2;
      if (uVar2 <= uVar5 && lVar6 != 0) goto code_r0x0142a62c;
    }
    if ((uVar3 & 1) == 0) {
      lVar6 = param_1 + 0x789;
    }
    else {
      lVar6 = *(long *)(param_1 + 0x798);
    }
    if (uVar5 != 0) {
      memmove(lVar6,lVar4,uVar5);
    }
    *(undefined1 *)(lVar6 + uVar5) = 0;
    if ((*(byte *)puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar5 << 1);
    }
    else {
      *(ulong *)(param_1 + 0x790) = uVar5;
    }
  }
code_r0x0142a68c:
  *(undefined8 *)(param_1 + 0x7a8) = *(undefined8 *)(param_2 + 0x7a8);
  *(undefined1 *)(param_1 + 0x7b0) = *(undefined1 *)(param_2 + 0x7b0);
  *(undefined4 *)(param_1 + 0x7c0) = *(undefined4 *)(param_2 + 0x7c0);
  if (param_1 == param_2) {
    return param_1;
  }
  puVar1 = (ulong *)(param_1 + 0x7c8);
  lVar4 = *(long *)(param_2 + 0x7d8);
  uVar5 = *(ulong *)(param_2 + 2000);
  uVar3 = (ulong)*(byte *)puVar1;
  if ((*(byte *)(param_2 + 0x7c8) & 1) == 0) {
    lVar4 = param_2 + 0x7c9;
    uVar5 = (ulong)(*(byte *)(param_2 + 0x7c8) >> 1);
  }
  if ((*(byte *)puVar1 & 1) == 0) {
    uVar2 = 0x16;
    lVar6 = uVar5 - 0x16;
    if (0x15 < uVar5 && lVar6 != 0) {
code_r0x0142a708:
      if ((uVar3 & 1) == 0) {
        uVar3 = (ulong)(((uint)uVar3 & 0xfe) >> 1);
      }
      else {
        uVar3 = *(ulong *)(param_1 + 2000);
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar2,lVar6,uVar3,0,uVar3,uVar5);
      return param_1;
    }
  }
  else {
    uVar3 = *puVar1;
    uVar2 = (uVar3 & 0xfffffffffffffffe) - 1;
    lVar6 = uVar5 - uVar2;
    if (uVar2 <= uVar5 && lVar6 != 0) goto code_r0x0142a708;
  }
  if ((uVar3 & 1) == 0) {
    lVar6 = param_1 + 0x7c9;
  }
  else {
    lVar6 = *(long *)(param_1 + 0x7d8);
  }
  if (uVar5 != 0) {
    memmove(lVar6,lVar4,uVar5);
  }
  *(undefined1 *)(lVar6 + uVar5) = 0;
  if ((*(byte *)puVar1 & 1) == 0) {
    *(byte *)puVar1 = (byte)(uVar5 << 1);
  }
  else {
    *(ulong *)(param_1 + 2000) = uVar5;
  }
  return param_1;
}


// FAILED to create function at 02ab1e48 CMasterParameterSignalElement::vtable
// FAILED to create function at 02ab1e80 CMasterParameterSignalElement::typeinfo
