// port/decomp/params/convert.c: Ghidra decompiles for the params subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileAt.java, tools/resolve_decomp.py
// run      2026-10-04 07:42 UTC: tools/decomp_at.sh '--into' 'params/convert' '0x17f727c' '0x17f61c4' '0x17f6584' '0x17f6954' '0x17f6d14'

// ==== int StringToNumber<int>(char*)
// vaddr 0x16f61c4 | ghidra 0x17f61c4 | size 436 | symbol _Z14StringToNumberIiET_Pc | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _Z14StringToNumberIiET_Pc(long param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined4 uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uStack_178;
  ulong uStack_170;
  ulong uStack_168;
  undefined *puStack_160;
  undefined8 uStack_158;
  undefined *puStack_150;
  undefined1 auStack_148 [8];
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  ulong uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined4 uStack_f0;
  undefined *apuStack_e8 [17];
  undefined8 uStack_60;
  undefined4 uStack_58;
  
  if (param_1 == 0) {
    return 0;
  }
  uStack_170 = 0;
  uStack_168 = 0;
  uStack_178 = 0;
  uVar6 = strlen(param_1);
  if (uVar6 < 0x17) {
    uVar7 = (ulong)&uStack_178 | 1;
    uStack_178 = CONCAT71(uStack_178._1_7_,(char)(uVar6 << 1));
    if (uVar6 == 0) goto code_r0x017f6250;
  }
  else {
    uVar8 = uVar6 + 0x10 & 0xfffffffffffffff0;
    uVar7 = operator new(unsigned long)(uVar8);
    uStack_178 = uVar8 | 1;
    uStack_170 = uVar6;
    uStack_168 = uVar7;
  }
  memcpy(uVar7,param_1,uVar6);
code_r0x017f6250:
  *(undefined1 *)(uVar7 + uVar6) = 0;
  apuStack_e8[0] =
       PTR__ZTCNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE0_NS_13basic_istreamIcS2_EE_02cba808
       + 0x40;
  puStack_160 = PTR__ZTCNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE0_NS_13basic_istreamIcS2_EE_02cba808
                + 0x18;
  uStack_158 = 0;
  std::__ndk1::ios_base::init(void*)(apuStack_e8,&puStack_150);
  puVar4 = PTR__ZTVNSt6__ndk115basic_streambufIcNS_11char_traitsIcEEEE_02cbbe18;
  uStack_60 = 0;
  uStack_58 = 0xffffffff;
  puVar1 = PTR__ZTVNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc2490
           + 0x18;
  puVar2 = PTR__ZTVNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc2490
           + 0x40;
  puStack_150 = PTR__ZTVNSt6__ndk115basic_streambufIcNS_11char_traitsIcEEEE_02cbbe18 + 0x10;
  puStack_160 = puVar1;
  apuStack_e8[0] = puVar2;
  std::__ndk1::locale::locale()(auStack_148);
  puVar3 = PTR__ZTVNSt6__ndk115basic_stringbufIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc3ba8 +
           0x10;
  uStack_128 = 0;
  uStack_130 = 0;
  uStack_118 = 0;
  uStack_120 = 0;
  uStack_138 = 0;
  uStack_140 = 0;
  uStack_108 = 0;
  uStack_110 = 0;
  uStack_f8 = 0;
  uStack_100 = 0;
  uStack_f0 = 8;
  puStack_150 = puVar3;
  std::__ndk1::basic_stringbuf<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >::str(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&)(&puStack_150,&uStack_178);
  if ((uStack_178 & 1) != 0) {
    operator delete(void*)(uStack_168);
  }
  uStack_178 = uStack_178 & 0xffffffff00000000;
  std::__ndk1::basic_istream<char, std::__ndk1::char_traits<char> >::operator>>(int&)(&puStack_160,&uStack_178);
  uVar5 = (undefined4)uStack_178;
  puStack_160 = puVar1;
  apuStack_e8[0] = puVar2;
  if ((uStack_110 & 1) != 0) {
    puStack_150 = puVar3;
    operator delete(void*)(uStack_100);
  }
  puStack_150 = puVar4 + 0x10;
  std::__ndk1::locale::~locale()(auStack_148);
  std::__ndk1::ios_base::~ios_base()(apuStack_e8);
  return uVar5;
}

// ==== unsigned int StringToNumber<unsigned int>(char*)
// vaddr 0x16f6584 | ghidra 0x17f6584 | size 436 | symbol _Z14StringToNumberIjET_Pc | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _Z14StringToNumberIjET_Pc(long param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined4 uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uStack_178;
  ulong uStack_170;
  ulong uStack_168;
  undefined *puStack_160;
  undefined8 uStack_158;
  undefined *puStack_150;
  undefined1 auStack_148 [8];
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  ulong uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined4 uStack_f0;
  undefined *apuStack_e8 [17];
  undefined8 uStack_60;
  undefined4 uStack_58;
  
  if (param_1 == 0) {
    return 0;
  }
  uStack_170 = 0;
  uStack_168 = 0;
  uStack_178 = 0;
  uVar6 = strlen(param_1);
  if (uVar6 < 0x17) {
    uVar7 = (ulong)&uStack_178 | 1;
    uStack_178 = CONCAT71(uStack_178._1_7_,(char)(uVar6 << 1));
    if (uVar6 == 0) goto code_r0x017f6610;
  }
  else {
    uVar8 = uVar6 + 0x10 & 0xfffffffffffffff0;
    uVar7 = operator new(unsigned long)(uVar8);
    uStack_178 = uVar8 | 1;
    uStack_170 = uVar6;
    uStack_168 = uVar7;
  }
  memcpy(uVar7,param_1,uVar6);
code_r0x017f6610:
  *(undefined1 *)(uVar7 + uVar6) = 0;
  apuStack_e8[0] =
       PTR__ZTCNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE0_NS_13basic_istreamIcS2_EE_02cba808
       + 0x40;
  puStack_160 = PTR__ZTCNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE0_NS_13basic_istreamIcS2_EE_02cba808
                + 0x18;
  uStack_158 = 0;
  std::__ndk1::ios_base::init(void*)(apuStack_e8,&puStack_150);
  puVar4 = PTR__ZTVNSt6__ndk115basic_streambufIcNS_11char_traitsIcEEEE_02cbbe18;
  uStack_60 = 0;
  uStack_58 = 0xffffffff;
  puVar1 = PTR__ZTVNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc2490
           + 0x18;
  puVar2 = PTR__ZTVNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc2490
           + 0x40;
  puStack_150 = PTR__ZTVNSt6__ndk115basic_streambufIcNS_11char_traitsIcEEEE_02cbbe18 + 0x10;
  puStack_160 = puVar1;
  apuStack_e8[0] = puVar2;
  std::__ndk1::locale::locale()(auStack_148);
  puVar3 = PTR__ZTVNSt6__ndk115basic_stringbufIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc3ba8 +
           0x10;
  uStack_128 = 0;
  uStack_130 = 0;
  uStack_118 = 0;
  uStack_120 = 0;
  uStack_138 = 0;
  uStack_140 = 0;
  uStack_108 = 0;
  uStack_110 = 0;
  uStack_f8 = 0;
  uStack_100 = 0;
  uStack_f0 = 8;
  puStack_150 = puVar3;
  std::__ndk1::basic_stringbuf<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >::str(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&)(&puStack_150,&uStack_178);
  if ((uStack_178 & 1) != 0) {
    operator delete(void*)(uStack_168);
  }
  uStack_178 = uStack_178 & 0xffffffff00000000;
  std::__ndk1::basic_istream<char, std::__ndk1::char_traits<char> >::operator>>(unsigned int&)(&puStack_160,&uStack_178);
  uVar5 = (undefined4)uStack_178;
  puStack_160 = puVar1;
  apuStack_e8[0] = puVar2;
  if ((uStack_110 & 1) != 0) {
    puStack_150 = puVar3;
    operator delete(void*)(uStack_100);
  }
  puStack_150 = puVar4 + 0x10;
  std::__ndk1::locale::~locale()(auStack_148);
  std::__ndk1::ios_base::~ios_base()(apuStack_e8);
  return uVar5;
}

// ==== long StringToNumber<long>(char*)
// vaddr 0x16f6954 | ghidra 0x17f6954 | size 436 | symbol _Z14StringToNumberIlET_Pc | lib libSOA-3.7.0.so | 2026-10-04
ulong _Z14StringToNumberIlET_Pc(long param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uStack_178;
  ulong uStack_170;
  ulong uStack_168;
  undefined *puStack_160;
  undefined8 uStack_158;
  undefined *puStack_150;
  undefined1 auStack_148 [8];
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  ulong uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined4 uStack_f0;
  undefined *apuStack_e8 [17];
  undefined8 uStack_60;
  undefined4 uStack_58;
  
  if (param_1 == 0) {
    return 0;
  }
  uStack_170 = 0;
  uStack_168 = 0;
  uStack_178 = 0;
  uVar5 = strlen(param_1);
  if (uVar5 < 0x17) {
    uVar6 = (ulong)&uStack_178 | 1;
    uStack_178 = CONCAT71(uStack_178._1_7_,(char)(uVar5 << 1));
    if (uVar5 == 0) goto code_r0x017f69e0;
  }
  else {
    uVar7 = uVar5 + 0x10 & 0xfffffffffffffff0;
    uVar6 = operator new(unsigned long)(uVar7);
    uStack_178 = uVar7 | 1;
    uStack_170 = uVar5;
    uStack_168 = uVar6;
  }
  memcpy(uVar6,param_1,uVar5);
code_r0x017f69e0:
  *(undefined1 *)(uVar6 + uVar5) = 0;
  apuStack_e8[0] =
       PTR__ZTCNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE0_NS_13basic_istreamIcS2_EE_02cba808
       + 0x40;
  puStack_160 = PTR__ZTCNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE0_NS_13basic_istreamIcS2_EE_02cba808
                + 0x18;
  uStack_158 = 0;
  std::__ndk1::ios_base::init(void*)(apuStack_e8,&puStack_150);
  puVar4 = PTR__ZTVNSt6__ndk115basic_streambufIcNS_11char_traitsIcEEEE_02cbbe18;
  uStack_60 = 0;
  uStack_58 = 0xffffffff;
  puVar1 = PTR__ZTVNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc2490
           + 0x18;
  puVar2 = PTR__ZTVNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc2490
           + 0x40;
  puStack_150 = PTR__ZTVNSt6__ndk115basic_streambufIcNS_11char_traitsIcEEEE_02cbbe18 + 0x10;
  puStack_160 = puVar1;
  apuStack_e8[0] = puVar2;
  std::__ndk1::locale::locale()(auStack_148);
  puVar3 = PTR__ZTVNSt6__ndk115basic_stringbufIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc3ba8 +
           0x10;
  uStack_128 = 0;
  uStack_130 = 0;
  uStack_118 = 0;
  uStack_120 = 0;
  uStack_138 = 0;
  uStack_140 = 0;
  uStack_108 = 0;
  uStack_110 = 0;
  uStack_f8 = 0;
  uStack_100 = 0;
  uStack_f0 = 8;
  puStack_150 = puVar3;
  std::__ndk1::basic_stringbuf<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >::str(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&)(&puStack_150,&uStack_178);
  if ((uStack_178 & 1) != 0) {
    operator delete(void*)(uStack_168);
  }
  uStack_178 = 0;
  std::__ndk1::basic_istream<char, std::__ndk1::char_traits<char> >::operator>>(long&)(&puStack_160,&uStack_178);
  uVar5 = uStack_178;
  puStack_160 = puVar1;
  apuStack_e8[0] = puVar2;
  if ((uStack_110 & 1) != 0) {
    puStack_150 = puVar3;
    operator delete(void*)(uStack_100);
  }
  puStack_150 = puVar4 + 0x10;
  std::__ndk1::locale::~locale()(auStack_148);
  std::__ndk1::ios_base::~ios_base()(apuStack_e8);
  return uVar5;
}

// ==== unsigned long StringToNumber<unsigned long>(char*)
// vaddr 0x16f6d14 | ghidra 0x17f6d14 | size 436 | symbol _Z14StringToNumberImET_Pc | lib libSOA-3.7.0.so | 2026-10-04
ulong _Z14StringToNumberImET_Pc(long param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uStack_178;
  ulong uStack_170;
  ulong uStack_168;
  undefined *puStack_160;
  undefined8 uStack_158;
  undefined *puStack_150;
  undefined1 auStack_148 [8];
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  ulong uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined4 uStack_f0;
  undefined *apuStack_e8 [17];
  undefined8 uStack_60;
  undefined4 uStack_58;
  
  if (param_1 == 0) {
    return 0;
  }
  uStack_170 = 0;
  uStack_168 = 0;
  uStack_178 = 0;
  uVar5 = strlen(param_1);
  if (uVar5 < 0x17) {
    uVar6 = (ulong)&uStack_178 | 1;
    uStack_178 = CONCAT71(uStack_178._1_7_,(char)(uVar5 << 1));
    if (uVar5 == 0) goto code_r0x017f6da0;
  }
  else {
    uVar7 = uVar5 + 0x10 & 0xfffffffffffffff0;
    uVar6 = operator new(unsigned long)(uVar7);
    uStack_178 = uVar7 | 1;
    uStack_170 = uVar5;
    uStack_168 = uVar6;
  }
  memcpy(uVar6,param_1,uVar5);
code_r0x017f6da0:
  *(undefined1 *)(uVar6 + uVar5) = 0;
  apuStack_e8[0] =
       PTR__ZTCNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE0_NS_13basic_istreamIcS2_EE_02cba808
       + 0x40;
  puStack_160 = PTR__ZTCNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE0_NS_13basic_istreamIcS2_EE_02cba808
                + 0x18;
  uStack_158 = 0;
  std::__ndk1::ios_base::init(void*)(apuStack_e8,&puStack_150);
  puVar4 = PTR__ZTVNSt6__ndk115basic_streambufIcNS_11char_traitsIcEEEE_02cbbe18;
  uStack_60 = 0;
  uStack_58 = 0xffffffff;
  puVar1 = PTR__ZTVNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc2490
           + 0x18;
  puVar2 = PTR__ZTVNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc2490
           + 0x40;
  puStack_150 = PTR__ZTVNSt6__ndk115basic_streambufIcNS_11char_traitsIcEEEE_02cbbe18 + 0x10;
  puStack_160 = puVar1;
  apuStack_e8[0] = puVar2;
  std::__ndk1::locale::locale()(auStack_148);
  puVar3 = PTR__ZTVNSt6__ndk115basic_stringbufIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc3ba8 +
           0x10;
  uStack_128 = 0;
  uStack_130 = 0;
  uStack_118 = 0;
  uStack_120 = 0;
  uStack_138 = 0;
  uStack_140 = 0;
  uStack_108 = 0;
  uStack_110 = 0;
  uStack_f8 = 0;
  uStack_100 = 0;
  uStack_f0 = 8;
  puStack_150 = puVar3;
  std::__ndk1::basic_stringbuf<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >::str(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&)(&puStack_150,&uStack_178);
  if ((uStack_178 & 1) != 0) {
    operator delete(void*)(uStack_168);
  }
  uStack_178 = 0;
  std::__ndk1::basic_istream<char, std::__ndk1::char_traits<char> >::operator>>(unsigned long&)(&puStack_160,&uStack_178);
  uVar5 = uStack_178;
  puStack_160 = puVar1;
  apuStack_e8[0] = puVar2;
  if ((uStack_110 & 1) != 0) {
    puStack_150 = puVar3;
    operator delete(void*)(uStack_100);
  }
  puStack_150 = puVar4 + 0x10;
  std::__ndk1::locale::~locale()(auStack_148);
  std::__ndk1::ios_base::~ios_base()(apuStack_e8);
  return uVar5;
}

// ==== unsigned char StringToNumber<unsigned char>(char*)
// vaddr 0x16f727c | ghidra 0x17f727c | size 548 | symbol _Z14StringToNumberIhET_Pc | lib libSOA-3.7.0.so | 2026-10-04
uint _Z14StringToNumberIhET_Pc(long param_1)

{
  byte *pbVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  ulong uVar5;
  long *plVar6;
  uint uVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uStack_168;
  ulong uStack_160;
  ulong uStack_158;
  undefined *puStack_150;
  undefined8 uStack_148;
  undefined *puStack_140;
  undefined1 auStack_138 [8];
  uint auStack_130 [2];
  long alStack_128 [9];
  undefined4 uStack_e0;
  undefined *apuStack_d8 [17];
  undefined8 uStack_50;
  undefined4 uStack_48;
  
  if (param_1 == 0) {
    return 0;
  }
  uStack_160 = 0;
  uStack_158 = 0;
  uStack_168 = 0;
  uVar5 = strlen(param_1);
  if (uVar5 < 0x17) {
    uVar8 = (ulong)&uStack_168 | 1;
    uStack_168 = CONCAT71(uStack_168._1_7_,(char)(uVar5 << 1));
    if (uVar5 != 0) goto code_r0x017f72f4;
  }
  else {
    uVar9 = uVar5 + 0x10 & 0xfffffffffffffff0;
    uVar8 = operator new(unsigned long)(uVar9);
    uStack_168 = uVar9 | 1;
    uStack_160 = uVar5;
    uStack_158 = uVar8;
code_r0x017f72f4:
    memcpy(uVar8,param_1,uVar5);
  }
  *(undefined1 *)(uVar8 + uVar5) = 0;
  apuStack_d8[0] =
       PTR__ZTCNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE0_NS_13basic_istreamIcS2_EE_02cba808
       + 0x40;
  puStack_150 = PTR__ZTCNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE0_NS_13basic_istreamIcS2_EE_02cba808
                + 0x18;
  uStack_148 = 0;
  std::__ndk1::ios_base::init(void*)(apuStack_d8,&puStack_140);
  puVar3 = PTR__ZTVNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc2490
  ;
  puVar2 = PTR__ZTVNSt6__ndk115basic_streambufIcNS_11char_traitsIcEEEE_02cbbe18;
  uStack_50 = 0;
  uStack_48 = 0xffffffff;
  puStack_150 = PTR__ZTVNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc2490
                + 0x18;
  apuStack_d8[0] =
       PTR__ZTVNSt6__ndk119basic_istringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc2490 +
       0x40;
  puStack_140 = PTR__ZTVNSt6__ndk115basic_streambufIcNS_11char_traitsIcEEEE_02cbbe18 + 0x10;
  std::__ndk1::locale::locale()(auStack_138);
  puVar4 = PTR__ZTVNSt6__ndk115basic_stringbufIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc3ba8;
  puStack_140 = PTR__ZTVNSt6__ndk115basic_stringbufIcNS_11char_traitsIcEENS_9allocatorIcEEEE_02cc3ba8
                + 0x10;
  alStack_128[2] = 0;
  alStack_128[1] = 0;
  alStack_128[4] = 0;
  alStack_128[3] = 0;
  alStack_128[0] = 0;
  auStack_130[0] = 0;
  auStack_130[1] = 0;
  alStack_128[6] = 0;
  alStack_128[5] = 0;
  alStack_128[8] = 0;
  alStack_128[7] = 0;
  uStack_e0 = 8;
  std::__ndk1::basic_stringbuf<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >::str(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&)(&puStack_140,&uStack_168);
  if ((uStack_168 & 1) != 0) {
    operator delete(void*)(uStack_158);
  }
  std::__ndk1::basic_istream<char, std::__ndk1::char_traits<char> >::sentry::sentry(std::__ndk1::basic_istream<char, std::__ndk1::char_traits<char> >&, bool)(&uStack_168,&puStack_150,0);
  if ((char)uStack_168 != '\0') {
    plVar6 = *(long **)((long)alStack_128 + *(long *)(puStack_150 + -0x18));
    pbVar1 = (byte *)plVar6[3];
    if (pbVar1 != (byte *)plVar6[4]) {
      plVar6[3] = (long)(pbVar1 + 1);
      uVar7 = (uint)*pbVar1;
      goto code_r0x017f7444;
    }
    uVar7 = (**(code **)(*plVar6 + 0x50))();
    if (uVar7 != 0xffffffff) goto code_r0x017f7444;
    std::__ndk1::ios_base::clear(unsigned int)((long)&puStack_150 + *(long *)(puStack_150 + -0x18),
                    *(uint *)((long)auStack_130 + *(long *)(puStack_150 + -0x18)) | 6);
  }
  uVar7 = 0;
code_r0x017f7444:
  puStack_150 = puVar3 + 0x18;
  apuStack_d8[0] = puVar3 + 0x40;
  puStack_140 = puVar4 + 0x10;
  if ((alStack_128[5] & 1U) != 0) {
    operator delete(void*)(alStack_128[7]);
  }
  puStack_140 = puVar2 + 0x10;
  std::__ndk1::locale::~locale()(auStack_138);
  std::__ndk1::ios_base::~ios_base()(apuStack_d8);
  return uVar7;
}
