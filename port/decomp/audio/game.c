// port/decomp/audio/game.c: Ghidra decompiles for the audio subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 13:05 UTC: tools/decomp.sh '--into' 'audio/game' ' CSound[A-Za-z0-9]*::' 'CParameterSound[A-Za-z0-9]*::' 'C[A-Za-z0-9]*VoiceManager::'

// ==== CParameterSoundElement::operator=(CParameterSoundElement const&)
// vaddr 0x1358050 | ghidra 0x1458050 | size 832 | symbol _ZN22CParameterSoundElementaSERKS_ | lib libSOA-3.7.0.so | 2026-10-08
long _ZN22CParameterSoundElementaSERKS_(long param_1,long param_2)

{
  ulong *puVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  
  *(undefined8 *)(param_1 + 8) = *(undefined8 *)(param_2 + 8);
  *(undefined8 *)(param_1 + 0x18) = *(undefined8 *)(param_2 + 0x18);
  *(undefined1 *)(param_1 + 0x20) = *(undefined1 *)(param_2 + 0x20);
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_2 + 0x30);
  if (param_1 != param_2) {
    puVar1 = (ulong *)(param_1 + 0x38);
    uVar2 = *(ulong *)(param_2 + 0x40);
    lVar3 = *(long *)(param_2 + 0x48);
    uVar5 = (ulong)*(byte *)puVar1;
    if ((*(byte *)(param_2 + 0x38) & 1) == 0) {
      lVar3 = param_2 + 0x39;
      uVar2 = (ulong)(*(byte *)(param_2 + 0x38) >> 1);
    }
    if ((*(byte *)puVar1 & 1) == 0) {
      uVar4 = 0x16;
      lVar6 = uVar2 - 0x16;
      if (0x15 < uVar2 && lVar6 != 0) {
code_r0x014580e4:
        if ((uVar5 & 1) == 0) {
          uVar5 = (ulong)(((uint)uVar5 & 0xfe) >> 1);
        }
        else {
          uVar5 = *(ulong *)(param_1 + 0x40);
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar4,lVar6,uVar5,0,uVar5,uVar2);
        goto code_r0x01458144;
      }
    }
    else {
      uVar5 = *puVar1;
      uVar4 = (uVar5 & 0xfffffffffffffffe) - 1;
      lVar6 = uVar2 - uVar4;
      if (uVar4 <= uVar2 && lVar6 != 0) goto code_r0x014580e4;
    }
    if ((uVar5 & 1) == 0) {
      lVar6 = param_1 + 0x39;
    }
    else {
      lVar6 = *(long *)(param_1 + 0x48);
    }
    if (uVar2 != 0) {
      memmove(lVar6,lVar3,uVar2);
    }
    *(undefined1 *)(lVar6 + uVar2) = 0;
    if ((*(byte *)puVar1 & 1) == 0) {
      *(byte *)puVar1 = (byte)(uVar2 << 1);
    }
    else {
      *(ulong *)(param_1 + 0x40) = uVar2;
    }
  }
code_r0x01458144:
  *(undefined8 *)(param_1 + 0x58) = *(undefined8 *)(param_2 + 0x58);
  *(undefined1 *)(param_1 + 0x60) = *(undefined1 *)(param_2 + 0x60);
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_2 + 0x70);
  if (param_1 == param_2) goto code_r0x0145821c;
  puVar1 = (ulong *)(param_1 + 0x78);
  uVar2 = *(ulong *)(param_2 + 0x80);
  lVar3 = *(long *)(param_2 + 0x88);
  uVar5 = (ulong)*(byte *)puVar1;
  if ((*(byte *)(param_2 + 0x78) & 1) == 0) {
    lVar3 = param_2 + 0x79;
    uVar2 = (ulong)(*(byte *)(param_2 + 0x78) >> 1);
  }
  if ((*(byte *)puVar1 & 1) == 0) {
    uVar4 = 0x16;
    lVar6 = uVar2 - 0x16;
    if (0x15 < uVar2 && lVar6 != 0) {
code_r0x014581bc:
      if ((uVar5 & 1) == 0) {
        uVar5 = (ulong)(((uint)uVar5 & 0xfe) >> 1);
      }
      else {
        uVar5 = *(ulong *)(param_1 + 0x80);
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar1,uVar4,lVar6,uVar5,0,uVar5,uVar2);
      goto code_r0x0145821c;
    }
  }
  else {
    uVar5 = *puVar1;
    uVar4 = (uVar5 & 0xfffffffffffffffe) - 1;
    lVar6 = uVar2 - uVar4;
    if (uVar4 <= uVar2 && lVar6 != 0) goto code_r0x014581bc;
  }
  if ((uVar5 & 1) == 0) {
    lVar6 = param_1 + 0x79;
  }
  else {
    lVar6 = *(long *)(param_1 + 0x88);
  }
  if (uVar2 != 0) {
    memmove(lVar6,lVar3,uVar2);
  }
  *(undefined1 *)(lVar6 + uVar2) = 0;
  if ((*(byte *)puVar1 & 1) == 0) {
    *(byte *)puVar1 = (byte)(uVar2 << 1);
  }
  else {
    *(ulong *)(param_1 + 0x80) = uVar2;
  }
code_r0x0145821c:
  *(undefined8 *)(param_1 + 0x98) = *(undefined8 *)(param_2 + 0x98);
  *(undefined1 *)(param_1 + 0xa0) = *(undefined1 *)(param_2 + 0xa0);
  *(undefined4 *)(param_1 + 0xb0) = *(undefined4 *)(param_2 + 0xb0);
  *(undefined4 *)(param_1 + 0xb8) = *(undefined4 *)(param_2 + 0xb8);
  *(undefined8 *)(param_1 + 200) = *(undefined8 *)(param_2 + 200);
  *(undefined1 *)(param_1 + 0xd0) = *(undefined1 *)(param_2 + 0xd0);
  *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(param_2 + 0xe0);
  *(undefined4 *)(param_1 + 0xe8) = *(undefined4 *)(param_2 + 0xe8);
  *(undefined8 *)(param_1 + 0xf8) = *(undefined8 *)(param_2 + 0xf8);
  *(undefined1 *)(param_1 + 0x100) = *(undefined1 *)(param_2 + 0x100);
  *(undefined4 *)(param_1 + 0x110) = *(undefined4 *)(param_2 + 0x110);
  *(undefined4 *)(param_1 + 0x118) = *(undefined4 *)(param_2 + 0x118);
  *(undefined8 *)(param_1 + 0x128) = *(undefined8 *)(param_2 + 0x128);
  *(undefined1 *)(param_1 + 0x130) = *(undefined1 *)(param_2 + 0x130);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_2 + 0x140);
  *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_2 + 0x148);
  *(undefined8 *)(param_1 + 0x158) = *(undefined8 *)(param_2 + 0x158);
  *(undefined1 *)(param_1 + 0x160) = *(undefined1 *)(param_2 + 0x160);
  *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(param_2 + 0x170);
  *(undefined4 *)(param_1 + 0x178) = *(undefined4 *)(param_2 + 0x178);
  *(undefined8 *)(param_1 + 0x188) = *(undefined8 *)(param_2 + 0x188);
  *(undefined1 *)(param_1 + 400) = *(undefined1 *)(param_2 + 400);
  *(undefined4 *)(param_1 + 0x1a0) = *(undefined4 *)(param_2 + 0x1a0);
  *(undefined4 *)(param_1 + 0x1a8) = *(undefined4 *)(param_2 + 0x1a8);
  *(undefined8 *)(param_1 + 0x1b8) = *(undefined8 *)(param_2 + 0x1b8);
  *(undefined1 *)(param_1 + 0x1c0) = *(undefined1 *)(param_2 + 0x1c0);
  *(undefined4 *)(param_1 + 0x1d0) = *(undefined4 *)(param_2 + 0x1d0);
  *(undefined4 *)(param_1 + 0x1d8) = *(undefined4 *)(param_2 + 0x1d8);
  *(undefined8 *)(param_1 + 0x1e8) = *(undefined8 *)(param_2 + 0x1e8);
  *(undefined1 *)(param_1 + 0x1f0) = *(undefined1 *)(param_2 + 0x1f0);
  *(undefined4 *)(param_1 + 0x200) = *(undefined4 *)(param_2 + 0x200);
  *(undefined4 *)(param_1 + 0x208) = *(undefined4 *)(param_2 + 0x208);
  *(undefined8 *)(param_1 + 0x218) = *(undefined8 *)(param_2 + 0x218);
  *(undefined1 *)(param_1 + 0x220) = *(undefined1 *)(param_2 + 0x220);
  *(undefined4 *)(param_1 + 0x230) = *(undefined4 *)(param_2 + 0x230);
  *(undefined4 *)(param_1 + 0x238) = *(undefined4 *)(param_2 + 0x238);
  *(undefined8 *)(param_1 + 0x248) = *(undefined8 *)(param_2 + 0x248);
  *(undefined1 *)(param_1 + 0x250) = *(undefined1 *)(param_2 + 0x250);
  *(undefined4 *)(param_1 + 0x260) = *(undefined4 *)(param_2 + 0x260);
  *(undefined4 *)(param_1 + 0x268) = *(undefined4 *)(param_2 + 0x268);
  *(undefined8 *)(param_1 + 0x278) = *(undefined8 *)(param_2 + 0x278);
  *(undefined1 *)(param_1 + 0x280) = *(undefined1 *)(param_2 + 0x280);
  *(undefined4 *)(param_1 + 0x290) = *(undefined4 *)(param_2 + 0x290);
  *(undefined4 *)(param_1 + 0x298) = *(undefined4 *)(param_2 + 0x298);
  return param_1;
}

// ==== CParameterSoundElement::CParameterSoundElement()
// vaddr 0x16f8624 | ghidra 0x17f8624 | size 636 | symbol _ZN22CParameterSoundElementC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CParameterSoundElementC2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  CParameterElementBase::CParameterElementBase()();
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj31EE_02cc17e0;
  puVar1 = PTR__ZTV22CParameterSoundElement_02cbbcf8;
  *(undefined1 *)(param_1 + 4) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[2] = (long)(puVar2 + 0x10);
  param_1[3] = 0;
  Framework::CHash32::CHash32()(param_1 + 5);
  puVar1 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj31EE_02cba990
  ;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[0xb] = 0;
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj32EE_02cc0fa8;
  *(undefined1 *)(param_1 + 0xc) = 0;
  param_1[2] = (long)(puVar1 + 0x10);
  param_1[9] = 0;
  param_1[10] = (long)(puVar2 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0xd);
  puVar2 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj32EE_02cc31e8
  ;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[0x13] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj33EE_02cb96b8;
  *(undefined1 *)(param_1 + 0x14) = 0;
  param_1[10] = (long)(puVar2 + 0x10);
  param_1[0x11] = 0;
  param_1[0x12] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x15);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj34EE_02cc0de8;
  puVar1 = PTR__ZTV23CParameterPropertyValueIiLj33E18CPropertyConverterE_02cbba60;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  param_1[0x12] = (long)(puVar1 + 0x10);
  param_1[0x18] = (long)(puVar2 + 0x10);
  param_1[0x19] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x1b);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj35EE_02cc13f0;
  puVar1 = PTR__ZTV23CParameterPropertyValueIiLj34E18CPropertyConverterE_02cbf5d0;
  *(undefined1 *)(param_1 + 0x20) = 0;
  param_1[0x18] = (long)(puVar1 + 0x10);
  param_1[0x1e] = (long)(puVar2 + 0x10);
  param_1[0x1f] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x21);
  puVar2 = PTR__ZTV23CParameterPropertyValueIiLj35E18CPropertyConverterE_02cbd140;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj36EE_02cb6f78;
  *(undefined1 *)(param_1 + 0x26) = 0;
  param_1[0x1e] = (long)(puVar2 + 0x10);
  param_1[0x24] = (long)(puVar1 + 0x10);
  param_1[0x25] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x27);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj37EE_02cbda08;
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj36E18CPropertyConverterE_02cbb9c8;
  *(undefined1 *)(param_1 + 0x2c) = 0;
  param_1[0x24] = (long)(puVar1 + 0x10);
  param_1[0x2a] = (long)(puVar2 + 0x10);
  param_1[0x2b] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x2d);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj38EE_02cc0aa0;
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj37E18CPropertyConverterE_02cbd708;
  *(undefined1 *)(param_1 + 0x32) = 0;
  param_1[0x2a] = (long)(puVar1 + 0x10);
  param_1[0x30] = (long)(puVar2 + 0x10);
  param_1[0x31] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x33);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj39EE_02cc3d00;
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj38E18CPropertyConverterE_02cb9be8;
  *(undefined1 *)(param_1 + 0x38) = 0;
  param_1[0x30] = (long)(puVar1 + 0x10);
  param_1[0x36] = (long)(puVar2 + 0x10);
  param_1[0x37] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x39);
  puVar2 = PTR__ZTV22CParameterPropertyBaseILj46EE_02cc4ed0;
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj39E18CPropertyConverterE_02cbf368;
  *(undefined1 *)(param_1 + 0x3e) = 0;
  param_1[0x36] = (long)(puVar1 + 0x10);
  param_1[0x3c] = (long)(puVar2 + 0x10);
  param_1[0x3d] = 0;
  Framework::CHash32::CHash32()(param_1 + 0x3f);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj46E18CPropertyConverterE_02cc11f8;
  param_1[0x43] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj47EE_02cba780;
  *(undefined1 *)(param_1 + 0x44) = 0;
  param_1[0x3c] = (long)(puVar2 + 0x10);
  param_1[0x42] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x45);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj47E18CPropertyConverterE_02cc3370;
  param_1[0x49] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj52EE_02cba830;
  *(undefined1 *)(param_1 + 0x4a) = 0;
  param_1[0x42] = (long)(puVar2 + 0x10);
  param_1[0x48] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x4b);
  puVar2 = PTR__ZTV23CParameterPropertyValueIfLj52E18CPropertyConverterE_02cbb648;
  param_1[0x4f] = 0;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj53EE_02cb75b8;
  *(undefined1 *)(param_1 + 0x50) = 0;
  param_1[0x48] = (long)(puVar2 + 0x10);
  param_1[0x4e] = (long)(puVar1 + 0x10);
  Framework::CHash32::CHash32()(param_1 + 0x51);
  param_1[0x4e] =
       (long)(PTR__ZTV23CParameterPropertyValueIfLj53E18CPropertyConverterE_02cb8a30 + 0x10);
  return;
}

// ==== CParameterSoundElement::~CParameterSoundElement()
// vaddr 0x16f88a0 | ghidra 0x17f88a0 | size 404 | symbol _ZN22CParameterSoundElementD1Ev | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x017f88cc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x017f88fc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x017f892c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x017f895c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x017f898c: Changing call to branch */
/* WARNING: Possible PIC construction at 0x017f89bc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x017f89f4: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x017f89c0) */
/* WARNING: Removing unreachable block (ram,0x017f89d8) */
/* WARNING: Removing unreachable block (ram,0x017f89e0) */
/* WARNING: Removing unreachable block (ram,0x017f8990) */
/* WARNING: Removing unreachable block (ram,0x017f8960) */
/* WARNING: Removing unreachable block (ram,0x017f8930) */
/* WARNING: Removing unreachable block (ram,0x017f8900) */
/* WARNING: Removing unreachable block (ram,0x017f88d0) */
/* WARNING: Removing unreachable block (ram,0x017f89f8) */
/* WARNING: Removing unreachable block (ram,0x017f8a10) */
/* WARNING: Removing unreachable block (ram,0x017f8a18) */

void _ZN22CParameterSoundElementD2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj53EE_02cb75b8 + 0x10;
  *param_1 = (long)(PTR__ZTV22CParameterSoundElement_02cbbcf8 + 0x10);
  param_1[0x4e] = (long)puVar1;
  (*(code *)PTR__ZN9Framework7CHash32D1Ev_02cb3740)(param_1 + 0x51);
  return;
}

// ==== CParameterSoundElement::~CParameterSoundElement()
// vaddr 0x16f8a34 | ghidra 0x17f8a34 | size 24 | symbol _ZN22CParameterSoundElementD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CParameterSoundElementD0Ev(undefined8 param_1)

{
  CParameterSoundElement::~CParameterSoundElement()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CParameterSoundElement::Initialize()
// vaddr 0x16f8a4c | ghidra 0x17f8a4c | size 1256 | symbol _ZN22CParameterSoundElement10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN22CParameterSoundElement10InitializeEv(long param_1)

{
  byte bStack_48;
  undefined2 uStack_47;
  undefined1 uStack_45;
  undefined1 uStack_44;
  undefined1 uStack_43;
  undefined1 uStack_42;
  undefined1 uStack_41;
  undefined1 uStack_40;
  undefined1 uStack_3f;
  undefined1 uStack_3e;
  undefined1 uStack_3d;
  undefined1 uStack_3c;
  undefined1 uStack_3b;
  undefined2 uStack_3a;
  undefined8 uStack_38;
  
  uStack_40 = 0;
  uStack_3f = 0;
  uStack_3e = 0;
  uStack_3d = 0;
  uStack_3c = 0;
  uStack_3b = 0;
  uStack_3a = 0;
  uStack_38 = 0;
  uStack_42 = 0;
  uStack_41 = 0;
  bStack_48 = 8;
  uStack_47 = 0x614e;
  uStack_45 = 0x6d;
  uStack_44 = 0x65;
  uStack_43 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x28,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0x20) = 1;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x10);
  uStack_3b = 0;
  uStack_3a = 0;
  uStack_38 = 0;
  bStack_48 = 0x16;
  uStack_47 = (undefined2)_UNK_0285e9e3;
  uStack_45 = (undefined1)((ulong)_UNK_0285e9e3 >> 0x10);
  uStack_44 = (undefined1)((ulong)_UNK_0285e9e3 >> 0x18);
  uStack_43 = (undefined1)((ulong)_UNK_0285e9e3 >> 0x20);
  uStack_42 = (undefined1)((ulong)_UNK_0285e9e3 >> 0x28);
  uStack_41 = (undefined1)((ulong)_UNK_0285e9e3 >> 0x30);
  uStack_40 = (undefined1)((ulong)_UNK_0285e9e3 >> 0x38);
  uStack_3f = 0x61;
  uStack_3e = 0x6d;
  uStack_3d = 0x65;
  uStack_3c = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x68,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0x60) = 1;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x50);
  uStack_40 = 0;
  uStack_3f = 0;
  uStack_3e = 0;
  uStack_3d = 0;
  uStack_3c = 0;
  uStack_3b = 0;
  uStack_3a = 0;
  uStack_38 = 0;
  uStack_41 = 0;
  bStack_48 = 10;
  uStack_43 = 100;
  uStack_47 = 0x7543;
  uStack_45 = 0x65;
  uStack_44 = 0x49;
  uStack_42 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xa8,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0xa0) = 1;
  *(undefined4 *)(param_1 + 0xb8) = 0xffffffff;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x90);
  bStack_48 = 0x1e;
  uStack_47 = (undefined2)_UNK_0285e9f5;
  uStack_45 = (undefined1)((uint7)_UNK_0285e9f5 >> 0x10);
  uStack_44 = (undefined1)((uint7)_UNK_0285e9f5 >> 0x18);
  uStack_43 = (undefined1)((uint7)_UNK_0285e9f5 >> 0x20);
  uStack_42 = (undefined1)((uint7)_UNK_0285e9f5 >> 0x28);
  uStack_41 = (undefined1)((uint7)_UNK_0285e9f5 >> 0x30);
  uStack_40 = UNK_0285e9fc;
  uStack_3f = (undefined1)_UNK_0285e9fd;
  uStack_3e = (undefined1)((uint7)_UNK_0285e9fd >> 8);
  uStack_3d = (undefined1)((uint7)_UNK_0285e9fd >> 0x10);
  uStack_3c = (undefined1)((uint7)_UNK_0285e9fd >> 0x18);
  uStack_3b = (undefined1)((uint7)_UNK_0285e9fd >> 0x20);
  uStack_3a = (undefined2)((uint7)_UNK_0285e9fd >> 0x28);
  uStack_38 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0xd8,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0xd0) = 1;
  *(undefined4 *)(param_1 + 0xe8) = 1;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0xc0);
  uStack_3c = 0;
  uStack_3b = 0;
  uStack_3a = 0;
  uStack_38 = 0;
  bStack_48 = 0x14;
  uStack_47 = (undefined2)_UNK_0285ea05;
  uStack_45 = (undefined1)((ulong)_UNK_0285ea05 >> 0x10);
  uStack_44 = (undefined1)((ulong)_UNK_0285ea05 >> 0x18);
  uStack_43 = (undefined1)((ulong)_UNK_0285ea05 >> 0x20);
  uStack_42 = (undefined1)((ulong)_UNK_0285ea05 >> 0x28);
  uStack_41 = (undefined1)((ulong)_UNK_0285ea05 >> 0x30);
  uStack_40 = (undefined1)((ulong)_UNK_0285ea05 >> 0x38);
  uStack_3f = 0x74;
  uStack_3e = 0x79;
  uStack_3d = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x108,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0x100) = 1;
  *(undefined4 *)(param_1 + 0x118) = 0xffffffff;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0xf0);
  uStack_3e = 0;
  uStack_3d = 0;
  uStack_3c = 0;
  uStack_3b = 0;
  uStack_3a = 0;
  uStack_38 = 0;
  bStack_48 = 0x10;
  uStack_47 = 0x6146;
  uStack_45 = 100;
  uStack_44 = 0x65;
  uStack_43 = 0x54;
  uStack_42 = 0x69;
  uStack_41 = 0x6d;
  uStack_40 = 0x65;
  uStack_3f = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x138,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0x130) = 1;
  *(undefined4 *)(param_1 + 0x148) = 0;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x120);
  uStack_40 = 0;
  uStack_3f = 0;
  uStack_3e = 0;
  uStack_3d = 0;
  uStack_3c = 0;
  uStack_3b = 0;
  uStack_3a = 0;
  uStack_38 = 0;
  bStack_48 = 0xc;
  uStack_43 = 0x6d;
  uStack_42 = 0x65;
  uStack_47 = 0x6f56;
  uStack_45 = 0x6c;
  uStack_44 = 0x75;
  uStack_41 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x168,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0x160) = 1;
  *(undefined4 *)(param_1 + 0x178) = 0x3f800000;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x150);
  uStack_40 = 0;
  uStack_3f = 0;
  uStack_3e = 0;
  uStack_3d = 0;
  uStack_3c = 0;
  uStack_3b = 0;
  uStack_3a = 0;
  uStack_38 = 0;
  uStack_41 = 0;
  bStack_48 = 10;
  uStack_43 = 0x68;
  uStack_47 = 0x6950;
  uStack_45 = 0x74;
  uStack_44 = 99;
  uStack_42 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x198,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 400) = 1;
  *(undefined4 *)(param_1 + 0x1a8) = 0;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x180);
  uStack_40 = 0;
  uStack_3f = 0;
  uStack_3e = 0;
  uStack_3d = 0;
  uStack_3c = 0;
  uStack_3b = 0;
  uStack_3a = 0;
  uStack_38 = 0;
  uStack_43 = 0;
  uStack_42 = 0;
  uStack_41 = 0;
  bStack_48 = 6;
  uStack_45 = 0x6e;
  uStack_47 = 0x6150;
  uStack_44 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x1c8,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0x1c0) = 1;
  *(undefined4 *)(param_1 + 0x1d8) = 0;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x1b0);
  uStack_3a = 0;
  uStack_38 = 0;
  bStack_48 = 0x18;
  uStack_47 = (undefined2)_UNK_0285ea1a;
  uStack_45 = (undefined1)((ulong)_UNK_0285ea1a >> 0x10);
  uStack_44 = (undefined1)((ulong)_UNK_0285ea1a >> 0x18);
  uStack_43 = (undefined1)((ulong)_UNK_0285ea1a >> 0x20);
  uStack_42 = (undefined1)((ulong)_UNK_0285ea1a >> 0x28);
  uStack_41 = (undefined1)((ulong)_UNK_0285ea1a >> 0x30);
  uStack_40 = (undefined1)((ulong)_UNK_0285ea1a >> 0x38);
  uStack_3f = 0x74;
  uStack_3e = 99;
  uStack_3d = 0x68;
  uStack_3c = 0x4c;
  uStack_3b = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x1f8,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0x1f0) = 1;
  *(undefined4 *)(param_1 + 0x208) = 0;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x1e0);
  uStack_3a = 0;
  uStack_38 = 0;
  bStack_48 = 0x18;
  uStack_47 = (undefined2)_UNK_0285ea27;
  uStack_45 = (undefined1)((ulong)_UNK_0285ea27 >> 0x10);
  uStack_44 = (undefined1)((ulong)_UNK_0285ea27 >> 0x18);
  uStack_43 = (undefined1)((ulong)_UNK_0285ea27 >> 0x20);
  uStack_42 = (undefined1)((ulong)_UNK_0285ea27 >> 0x28);
  uStack_41 = (undefined1)((ulong)_UNK_0285ea27 >> 0x30);
  uStack_40 = (undefined1)((ulong)_UNK_0285ea27 >> 0x38);
  uStack_3f = 0x74;
  uStack_3e = 99;
  uStack_3d = 0x68;
  uStack_3c = 0x48;
  uStack_3b = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x228,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0x220) = 1;
  *(undefined4 *)(param_1 + 0x238) = 0;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x210);
  uStack_40 = 0;
  uStack_3f = 0;
  uStack_3e = 0;
  uStack_3d = 0;
  uStack_3c = 0;
  uStack_3b = 0;
  uStack_3a = 0;
  uStack_38 = 0;
  bStack_48 = 0xc;
  uStack_43 = 0x65;
  uStack_42 = 0x4c;
  uStack_47 = 0x6152;
  uStack_45 = 0x6e;
  uStack_44 = 0x67;
  uStack_41 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 600,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0x250) = 1;
  *(undefined4 *)(param_1 + 0x268) = 0;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x240);
  uStack_40 = 0;
  uStack_3f = 0;
  uStack_3e = 0;
  uStack_3d = 0;
  uStack_3c = 0;
  uStack_3b = 0;
  uStack_3a = 0;
  uStack_38 = 0;
  bStack_48 = 0xc;
  uStack_43 = 0x65;
  uStack_42 = 0x48;
  uStack_47 = 0x6152;
  uStack_45 = 0x6e;
  uStack_44 = 0x67;
  uStack_41 = 0;
  Framework::CHash32::operator=(char const*)(param_1 + 0x288,(ulong)&bStack_48 | 1);
  *(undefined1 *)(param_1 + 0x280) = 1;
  *(undefined4 *)(param_1 + 0x298) = 0;
  if ((bStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  CParameterElementBase::AddProperty(IParameterProperty*)(param_1,param_1 + 0x270);
  return;
}

// ==== CParameterSound::CParameterSound()
// vaddr 0x16f8f34 | ghidra 0x17f8f34 | size 68 | symbol _ZN15CParameterSoundC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CParameterSoundC2Ev(long *param_1)

{
  undefined *puVar1;
  
  CParameterBase::CParameterBase()();
  puVar1 = PTR__ZTV15CParameterSound_02cbd2c8;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[8] = 0;
  *(undefined4 *)(param_1 + 5) = 0x3f800000;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[7] = 0;
  param_1[6] = (long)(param_1 + 7);
  return;
}

// ==== CParameterSound::~CParameterSound()
// vaddr 0x16f8f78 | ghidra 0x17f8f78 | size 132 | symbol _ZN15CParameterSoundD2Ev | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x017f8fc4: Changing call to branch */

void _ZN15CParameterSoundD1Ev(long *param_1)

{
  long *plVar1;
  long lVar2;
  
  *param_1 = (long)(PTR__ZTV15CParameterSound_02cbd2c8 + 0x10);
  CParameterSound::Release()();
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CParameterSoundElement*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CParameterSoundElement*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CParameterSoundElement*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CParameterSoundElement*>, void*>*)(param_1 + 6,param_1[7]);
  plVar1 = (long *)param_1[3];
  do {
    if (plVar1 == (long *)0x0) {
      lVar2 = param_1[1];
      param_1[1] = 0;
      if (lVar2 == 0) {
        return;
      }
code_r0x011d23a0:
      (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)(lVar2);
      return;
    }
    lVar2 = *plVar1;
    CParameterSoundElement::~CParameterSoundElement()(plVar1 + 5);
    if ((*(byte *)(plVar1 + 2) & 1) != 0) {
      lVar2 = plVar1[4];
      goto code_r0x011d23a0;
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
    plVar1 = (long *)lVar2;
  } while( true );
}

// ==== CParameterSound::Release()
// vaddr 0x16f8ffc | ghidra 0x17f8ffc | size 148 | symbol _ZN15CParameterSound7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CParameterSound7ReleaseEv(long param_1)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CParameterSoundElement*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CParameterSoundElement*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CParameterSoundElement*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CParameterSoundElement*>, void*>*)(param_1 + 0x30,*(undefined8 *)(param_1 + 0x38));
  *(undefined8 **)(param_1 + 0x30) = (undefined8 *)(param_1 + 0x38);
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  if (*(long *)(param_1 + 0x20) != 0) {
    plVar1 = (long *)*(long *)(param_1 + 0x18);
    while (plVar1 != (long *)0x0) {
      lVar3 = *plVar1;
      CParameterSoundElement::~CParameterSoundElement()(plVar1 + 5);
      if ((*(byte *)(plVar1 + 2) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1[4]);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
      plVar1 = (long *)lVar3;
    }
    lVar3 = *(long *)(param_1 + 0x10);
    *(undefined8 *)(param_1 + 0x18) = 0;
    if (lVar3 != 0) {
      lVar2 = 0;
      do {
        *(undefined8 *)(*(long *)(param_1 + 8) + lVar2 * 8) = 0;
        lVar2 = lVar2 + 1;
      } while (lVar3 != lVar2);
    }
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  return;
}

// ==== CParameterSound::~CParameterSound()
// vaddr 0x16f9090 | ghidra 0x17f9090 | size 24 | symbol _ZN15CParameterSoundD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CParameterSoundD0Ev(undefined8 param_1)

{
  CParameterSound::~CParameterSound()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CParameterSound::pParseName() const
// vaddr 0x16f90a8 | ghidra 0x17f90a8 | size 12 | symbol _ZNK15CParameterSound10pParseNameEv | lib libSOA-3.7.0.so | 2026-10-08
undefined * _ZNK15CParameterSound10pParseNameEv(void)

{
  return &UNK_0285ea42/*"Sound"*/;
}

// ==== CParameterSound::Deserialize(Aska::ASON::AValue::AMap const*)
// vaddr 0x16f90b4 | ghidra 0x17f90b4 | size 100 | symbol _ZN15CParameterSound11DeserializeEPKN4Aska4ASON6AValue4AMapE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN15CParameterSound11DeserializeEPKN4Aska4ASON6AValue4AMapE(long *param_1,long param_2)

{
  long lVar1;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285ea48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterSound.cpp"*/,0x4d,&UNK_027dc58a/*"apParser is null."*/);
  }
  lVar1 = (**(code **)(*param_1 + 0x30))(param_1,param_2);
  if (lVar1 != 0) {
    CParameterSound::DeserializeParameter(Framework::CSTLUnorderedMap<string, CParameterSoundElement, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > >&, Aska::ASON::AValue::AArray const*)(param_1,param_1 + 1,lVar1 + 8);
  }
  return lVar1 != 0;
}

// ==== CParameterSound::DeserializeParameter(Framework::CSTLUnorderedMap<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >, CParameterSoundElement, std::__ndk1::hash<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >, std::__ndk1::equal_to<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > > >&, Aska::ASON::AValue::AArray const*)
// vaddr 0x16f9118 | ghidra 0x17f9118 | size 612 | symbol _ZN15CParameterSound20DeserializeParameterERN9Framework16CSTLUnorderedMapINSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEE22CParameterSoundElementNS2_4hashIS9_EENS2_8equal_toIS9_EEEEPKN4Aska4ASON6AValue6AArrayE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN15CParameterSound20DeserializeParameterERN9Framework16CSTLUnorderedMapINSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEE22CParameterSoundElementNS2_4hashIS9_EENS2_8equal_toIS9_EEEEPKN4Aska4ASON6AValue6AArrayE
          (undefined8 param_1,undefined8 param_2,long *param_3)

{
  uint uVar1;
  long lVar2;
  int iVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  long *plVar8;
  ulong uVar9;
  undefined1 auVar10 [16];
  ulong uStack_328;
  ulong uStack_320;
  ulong uStack_318;
  undefined1 auStack_88 [16];
  long alStack_78 [2];
  char cStack_68;
  
  if (param_3 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285ea48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterSound.cpp"*/,0x8c,&UNK_02845e17/*"apArray is null."*/);
    iVar3 = iRam0000000000000008;
  }
  else {
    iVar3 = (int)param_3[1];
  }
  if (iVar3 != 0) {
    uVar7 = 0;
    do {
      lVar2 = *param_3 + uVar7 * 0x20;
      if (lVar2 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285ea48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterSound.cpp"*/,0x90,&UNK_0285e8d7/*"pValue is null."*/);
      }
      lVar2 = lVar2 + 8;
      auVar10 = std::__ndk1::pair<char*, bool> CParameterParser::GetValue<char*>(Aska::ASON::AValue::AMap const*, char const*)(lVar2,&UNK_029d84d4/*"Name"*/);
      auStack_88 = auVar10;
      if ((auVar10._8_8_ & 0xff) != 0) {
        uStack_320 = 0;
        uStack_318 = 0;
        uStack_328 = 0;
        uVar4 = strlen(auVar10._0_8_);
        if (uVar4 < 0x17) {
          uStack_328 = CONCAT71(uStack_328._1_7_,(char)(uVar4 << 1));
          uVar5 = (ulong)&uStack_328 | 1;
          if (uVar4 != 0) goto code_r0x017f9264;
        }
        else {
          uVar9 = uVar4 + 0x10 & 0xfffffffffffffff0;
          if (uVar9 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          uVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (uVar5 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uStack_328 = uVar9 | 1;
          uStack_320 = uVar4;
          uStack_318 = uVar5;
code_r0x017f9264:
          memcpy(uVar5,auVar10._0_8_,uVar4);
        }
        *(undefined1 *)(uVar5 + uVar4) = 0;
        lVar6 = std::__ndk1::__hash_iterator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CParameterSoundElement>, void*>*> std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, CParameterSoundElement>, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, CParameterSoundElement>, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, CParameterSoundElement>, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, CParameterSoundElement>, Framework::CSTLUnorderedMapAllocatorInf> >::find<string >(string const&)(param_2,&uStack_328);
        if ((uStack_328 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_318);
        }
        if (lVar6 == 0) {
          CParameterSoundElement::CParameterSoundElement()(&uStack_328);
          std::__ndk1::unique_ptr<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CParameterSoundElement>, void*>, std::__ndk1::__hash_node_destructor<Framework::CSTLAllocator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CParameterSoundElement>, void*>, Framework::CSTLUnorderedMapAllocatorInf> > > std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, CParameterSoundElement>, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, CParameterSoundElement>, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, CParameterSoundElement>, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, CParameterSoundElement>, Framework::CSTLUnorderedMapAllocatorInf> >::__construct_node<char*&, CParameterSoundElement>(char*&, CParameterSoundElement&&)(alStack_78,param_2,auStack_88,&uStack_328);
          auVar10 = std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, CParameterSoundElement>, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, CParameterSoundElement>, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, CParameterSoundElement>, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, CParameterSoundElement>, Framework::CSTLUnorderedMapAllocatorInf> >::__node_insert_unique(std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CParameterSoundElement>, void*>*)(param_2,alStack_78[0]);
          lVar6 = alStack_78[0];
          if ((auVar10._8_8_ & 1) == 0) {
            alStack_78[0] = 0;
            if (lVar6 != 0) {
              if (cStack_68 != '\0') {
                CParameterSoundElement::~CParameterSoundElement()(lVar6 + 0x28);
                if ((*(byte *)(lVar6 + 0x10) & 1) != 0) {
                  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar6 + 0x20));
                }
              }
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar6);
            }
          }
          else {
            alStack_78[0] = 0;
          }
          CParameterSoundElement::~CParameterSoundElement()(&uStack_328);
          plVar8 = (long *)(auVar10._0_8_ + 0x28);
          (**(code **)*plVar8)(plVar8);
        }
        else {
          plVar8 = (long *)(lVar6 + 0x28);
        }
        (**(code **)(*plVar8 + 8))(plVar8,lVar2);
        CParameterSound::AddQueSheet(CParameterSoundElement*)(param_1,plVar8);
      }
      uVar1 = (int)uVar7 + 1;
      uVar7 = (ulong)uVar1;
    } while (uVar1 < *(uint *)(param_3 + 1));
  }
  return 1;
}

// ==== CParameterSound::pParameter(char const*) const
// vaddr 0x16f937c | ghidra 0x17f937c | size 288 | symbol _ZNK15CParameterSound10pParameterEPKc | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK15CParameterSound10pParameterEPKc(long param_1,long param_2)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uStack_48;
  ulong uStack_40;
  ulong uStack_38;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285ea48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterSound.cpp"*/,0x5f,&UNK_0285e592/*"apId is null."*/);
  }
  uStack_40 = 0;
  uStack_38 = 0;
  uStack_48 = 0;
  uVar2 = strlen(param_2);
  if (uVar2 < 0x17) {
    uVar5 = (ulong)&uStack_48 | 1;
    uStack_48 = CONCAT71(uStack_48._1_7_,(char)(uVar2 << 1));
    if (uVar2 == 0) goto code_r0x017f9458;
  }
  else {
    uVar4 = uVar2 + 0x10 & 0xfffffffffffffff0;
    if (uVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar4,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_48 = uVar4 | 1;
    uStack_40 = uVar2;
    uStack_38 = uVar5;
  }
  memcpy(uVar5,param_2,uVar2);
code_r0x017f9458:
  *(undefined1 *)(uVar5 + uVar2) = 0;
  lVar3 = std::__ndk1::__hash_const_iterator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CParameterSoundElement>, void*>*> std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, CParameterSoundElement>, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, CParameterSoundElement>, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, CParameterSoundElement>, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, CParameterSoundElement>, Framework::CSTLUnorderedMapAllocatorInf> >::find<string >(string const&) const(param_1 + 8,&uStack_48);
  if ((uStack_48 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  lVar1 = 0;
  if (lVar3 != 0) {
    lVar1 = lVar3 + 0x28;
  }
  return lVar1;
}

// ==== CParameterSound::pParameter(char const*, unsigned int) const
// vaddr 0x16f949c | ghidra 0x17f949c | size 240 | symbol _ZNK15CParameterSound10pParameterEPKcj | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK15CParameterSound10pParameterEPKcj(long param_1,long param_2,undefined4 param_3)

{
  long *plVar1;
  long *plVar2;
  uint uVar3;
  long *plVar4;
  long *plVar5;
  long *plVar6;
  long lVar7;
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [256];
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285ea48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterSound.cpp"*/,0x6e,&UNK_0285ea95/*"apPackageName is null."*/);
  }
  snprintf(auStack_130,0xff,&UNK_0285eaac/*"%sCueID:%d"*/,param_2,param_3);
  Framework::CHash32::CHash32(char const*)(auStack_140,auStack_130);
  uVar3 = Framework::CHash32::Get() const(auStack_140);
  plVar6 = (long *)(param_1 + 0x38);
  plVar2 = (long *)*plVar6;
  plVar4 = plVar6;
  if ((long *)*plVar6 != (long *)0x0) {
    do {
      while (plVar5 = plVar2, uVar3 <= *(uint *)(plVar5 + 4)) {
        plVar2 = (long *)*plVar5;
        plVar4 = plVar5;
        if ((long *)*plVar5 == (long *)0x0) goto code_r0x017f9540;
      }
      plVar1 = plVar5 + 1;
      plVar5 = plVar4;
      plVar2 = (long *)*plVar1;
    } while ((long *)*plVar1 != (long *)0x0);
code_r0x017f9540:
    if (plVar5 != plVar6) {
      lVar7 = 0;
      if ((*(uint *)(plVar5 + 4) <= uVar3) && (plVar5 != plVar6)) {
        lVar7 = plVar5[5];
      }
      goto code_r0x017f956c;
    }
  }
  lVar7 = 0;
code_r0x017f956c:
  Framework::CHash32::~CHash32()(auStack_140);
  return lVar7;
}

// ==== CParameterSound::rParameter() const
// vaddr 0x16f958c | ghidra 0x17f958c | size 8 | symbol _ZNK15CParameterSound10rParameterEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK15CParameterSound10rParameterEv(long param_1)

{
  return param_1 + 8;
}

// ==== CParameterSound::AddQueSheet(CParameterSoundElement*)
// vaddr 0x16f9594 | ghidra 0x17f9594 | size 268 | symbol _ZN15CParameterSound11AddQueSheetEP22CParameterSoundElement | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CParameterSound11AddQueSheetEP22CParameterSoundElement(long param_1,long param_2)

{
  ulong uVar1;
  undefined4 uStack_15c;
  ulong auStack_158 [3];
  undefined4 auStack_140 [64];
  undefined1 auStack_40 [16];
  long lStack_28;
  
  lStack_28 = param_2;
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0285ea48/*"C:\BAS_Submission\Client\Project\..\Source\Game\Parameter\ParameterSound.cpp"*/,0xb0,&UNK_0285eab7/*"apElement is null."*/);
  }
  if (*(int *)(param_2 + 0xb8) != -1) {
    Framework::CHash32::CHash32()(auStack_40);
    auStack_140[0] = Framework::CHash32::operator unsigned int() const(auStack_40);
    uVar1 = Framework::CHash32::operator==(unsigned int const&) const(param_2 + 0x68,auStack_140);
    Framework::CHash32::~CHash32()(auStack_40);
    if ((uVar1 & 1) == 0) {
      auStack_158[1] = 0;
      auStack_158[2] = 0;
      auStack_158[0] = 0;
      void CParameterPropertyBase<32u>::CryptString<string >(string&, string const&)(auStack_158,param_2 + 0x78);
      uVar1 = (ulong)auStack_158 | 1;
      if ((auStack_158[0] & 1) != 0) {
        uVar1 = auStack_158[2];
      }
      snprintf(auStack_140,0xff,&UNK_0285eaac/*"%sCueID:%d"*/,uVar1,*(undefined4 *)(param_2 + 0xb8));
      if ((auStack_158[0] & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_158[2]);
      }
      Framework::CHash32::CHash32(char const*)(auStack_158,auStack_140);
      uStack_15c = Framework::CHash32::Get() const(auStack_158);
      std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<unsigned int, CParameterSoundElement*>, std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, CParameterSoundElement*>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, CParameterSoundElement*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, CParameterSoundElement*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, CParameterSoundElement*>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<unsigned int, unsigned int, CParameterSoundElement*&>(unsigned int const&, unsigned int&&, CParameterSoundElement*&)(param_1 + 0x30,&uStack_15c,&uStack_15c,&lStack_28);
      Framework::CHash32::~CHash32()(auStack_158);
    }
  }
  return;
}

// ==== CParameterSoundElement::CParameterSoundElement(CParameterSoundElement const&)
// vaddr 0x16f9fd0 | ghidra 0x17f9fd0 | size 1392 | symbol _ZN22CParameterSoundElementC2ERKS_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN22CParameterSoundElementC2ERKS_(long *param_1,long param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  ulong uVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  undefined1 uVar6;
  undefined *puVar7;
  long lVar8;
  long *plVar9;
  ulong uVar10;
  
  puVar1 = PTR__ZTV18IParameterProperty_02cbe818;
  puVar2 = PTR__ZTV22CParameterSoundElement_02cbbcf8;
  *param_1 = (long)(PTR__ZTV21CParameterElementBase_02cbbc00 + 0x10);
  lVar8 = *(long *)(param_2 + 8);
  *param_1 = (long)(puVar2 + 0x10);
  param_1[1] = lVar8;
  param_1[2] = (long)(puVar1 + 0x10);
  lVar8 = *(long *)(param_2 + 0x18);
  param_1[2] = (long)(PTR__ZTV22CParameterPropertyBaseILj31EE_02cc17e0 + 0x10);
  param_1[3] = lVar8;
  puVar2 = PTR__ZTVN9Framework7CHash32E_02cba528;
  *(undefined1 *)(param_1 + 4) = *(undefined1 *)(param_2 + 0x20);
  param_1[5] = (long)(puVar2 + 0x10);
  puVar7 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj31EE_02cba990
  ;
  uVar5 = *(undefined4 *)(param_2 + 0x30);
  plVar9 = param_1 + 7;
  *plVar9 = 0;
  *(undefined4 *)(param_1 + 6) = uVar5;
  param_1[2] = (long)(puVar7 + 0x10);
  param_1[8] = 0;
  param_1[9] = 0;
  if ((*(byte *)(param_2 + 0x38) & 1) == 0) {
    param_1[9] = *(long *)(param_2 + 0x48);
    lVar8 = *(long *)(param_2 + 0x38);
    param_1[8] = *(long *)(param_2 + 0x40);
    *plVar9 = lVar8;
  }
  else {
    uVar3 = *(ulong *)(param_2 + 0x40);
    uVar4 = *(undefined8 *)(param_2 + 0x48);
    if (uVar3 < 0x17) {
      lVar8 = (long)param_1 + 0x39;
      *(char *)plVar9 = (char)(uVar3 << 1);
      if (uVar3 != 0) goto code_r0x017fa110;
    }
    else {
      uVar10 = uVar3 + 0x10 & 0xfffffffffffffff0;
      if (uVar10 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar10,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (lVar8 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      param_1[8] = uVar3;
      param_1[9] = lVar8;
      param_1[7] = uVar10 | 1;
code_r0x017fa110:
      memcpy(lVar8,uVar4,uVar3);
    }
    *(undefined1 *)(lVar8 + uVar3) = 0;
  }
  param_1[10] = (long)(puVar1 + 0x10);
  lVar8 = *(long *)(param_2 + 0x58);
  param_1[10] = (long)(PTR__ZTV22CParameterPropertyBaseILj32EE_02cc0fa8 + 0x10);
  param_1[0xb] = lVar8;
  uVar6 = *(undefined1 *)(param_2 + 0x60);
  param_1[0xd] = (long)(puVar2 + 0x10);
  *(undefined1 *)(param_1 + 0xc) = uVar6;
  puVar7 = 
  PTR__ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEELj32EE_02cc31e8
  ;
  uVar5 = *(undefined4 *)(param_2 + 0x70);
  plVar9 = param_1 + 0xf;
  *plVar9 = 0;
  *(undefined4 *)(param_1 + 0xe) = uVar5;
  param_1[10] = (long)(puVar7 + 0x10);
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  if ((*(byte *)(param_2 + 0x78) & 1) == 0) {
    param_1[0x11] = *(long *)(param_2 + 0x88);
    lVar8 = *(long *)(param_2 + 0x78);
    param_1[0x10] = *(long *)(param_2 + 0x80);
    *plVar9 = lVar8;
    goto code_r0x017fa228;
  }
  uVar3 = *(ulong *)(param_2 + 0x80);
  uVar4 = *(undefined8 *)(param_2 + 0x88);
  if (uVar3 < 0x17) {
    lVar8 = (long)param_1 + 0x79;
    *(char *)plVar9 = (char)(uVar3 << 1);
    if (uVar3 != 0) goto code_r0x017fa214;
  }
  else {
    uVar10 = uVar3 + 0x10 & 0xfffffffffffffff0;
    if (uVar10 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar10,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (lVar8 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[0x10] = uVar3;
    param_1[0x11] = lVar8;
    param_1[0xf] = uVar10 | 1;
code_r0x017fa214:
    memcpy(lVar8,uVar4,uVar3);
  }
  *(undefined1 *)(lVar8 + uVar3) = 0;
code_r0x017fa228:
  puVar1 = puVar1 + 0x10;
  param_1[0x12] = (long)puVar1;
  lVar8 = *(long *)(param_2 + 0x98);
  param_1[0x12] = (long)(PTR__ZTV22CParameterPropertyBaseILj33EE_02cb96b8 + 0x10);
  param_1[0x13] = lVar8;
  uVar6 = *(undefined1 *)(param_2 + 0xa0);
  puVar2 = puVar2 + 0x10;
  param_1[0x15] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x14) = uVar6;
  puVar7 = PTR__ZTV23CParameterPropertyValueIiLj33E18CPropertyConverterE_02cbba60;
  *(undefined4 *)(param_1 + 0x16) = *(undefined4 *)(param_2 + 0xb0);
  param_1[0x12] = (long)(puVar7 + 0x10);
  uVar5 = *(undefined4 *)(param_2 + 0xb8);
  param_1[0x18] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x17) = uVar5;
  lVar8 = *(long *)(param_2 + 200);
  param_1[0x18] = (long)(PTR__ZTV22CParameterPropertyBaseILj34EE_02cc0de8 + 0x10);
  param_1[0x19] = lVar8;
  uVar6 = *(undefined1 *)(param_2 + 0xd0);
  param_1[0x1b] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x1a) = uVar6;
  puVar7 = PTR__ZTV23CParameterPropertyValueIiLj34E18CPropertyConverterE_02cbf5d0;
  *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_2 + 0xe0);
  param_1[0x18] = (long)(puVar7 + 0x10);
  uVar5 = *(undefined4 *)(param_2 + 0xe8);
  param_1[0x1e] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x1d) = uVar5;
  lVar8 = *(long *)(param_2 + 0xf8);
  param_1[0x1e] = (long)(PTR__ZTV22CParameterPropertyBaseILj35EE_02cc13f0 + 0x10);
  param_1[0x1f] = lVar8;
  uVar6 = *(undefined1 *)(param_2 + 0x100);
  param_1[0x21] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x20) = uVar6;
  puVar7 = PTR__ZTV23CParameterPropertyValueIiLj35E18CPropertyConverterE_02cbd140;
  *(undefined4 *)(param_1 + 0x22) = *(undefined4 *)(param_2 + 0x110);
  param_1[0x1e] = (long)(puVar7 + 0x10);
  uVar5 = *(undefined4 *)(param_2 + 0x118);
  param_1[0x24] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x23) = uVar5;
  lVar8 = *(long *)(param_2 + 0x128);
  param_1[0x24] = (long)(PTR__ZTV22CParameterPropertyBaseILj36EE_02cb6f78 + 0x10);
  param_1[0x25] = lVar8;
  uVar6 = *(undefined1 *)(param_2 + 0x130);
  param_1[0x27] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x26) = uVar6;
  puVar7 = PTR__ZTV23CParameterPropertyValueIfLj36E18CPropertyConverterE_02cbb9c8;
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_2 + 0x140);
  param_1[0x24] = (long)(puVar7 + 0x10);
  uVar5 = *(undefined4 *)(param_2 + 0x148);
  param_1[0x2a] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x29) = uVar5;
  lVar8 = *(long *)(param_2 + 0x158);
  param_1[0x2a] = (long)(PTR__ZTV22CParameterPropertyBaseILj37EE_02cbda08 + 0x10);
  param_1[0x2b] = lVar8;
  uVar6 = *(undefined1 *)(param_2 + 0x160);
  param_1[0x2d] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x2c) = uVar6;
  puVar7 = PTR__ZTV23CParameterPropertyValueIfLj37E18CPropertyConverterE_02cbd708;
  *(undefined4 *)(param_1 + 0x2e) = *(undefined4 *)(param_2 + 0x170);
  param_1[0x2a] = (long)(puVar7 + 0x10);
  uVar5 = *(undefined4 *)(param_2 + 0x178);
  param_1[0x30] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x2f) = uVar5;
  lVar8 = *(long *)(param_2 + 0x188);
  param_1[0x30] = (long)(PTR__ZTV22CParameterPropertyBaseILj38EE_02cc0aa0 + 0x10);
  param_1[0x31] = lVar8;
  uVar6 = *(undefined1 *)(param_2 + 400);
  param_1[0x33] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x32) = uVar6;
  puVar7 = PTR__ZTV23CParameterPropertyValueIfLj38E18CPropertyConverterE_02cb9be8;
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_2 + 0x1a0);
  param_1[0x30] = (long)(puVar7 + 0x10);
  uVar5 = *(undefined4 *)(param_2 + 0x1a8);
  param_1[0x36] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x35) = uVar5;
  lVar8 = *(long *)(param_2 + 0x1b8);
  param_1[0x36] = (long)(PTR__ZTV22CParameterPropertyBaseILj39EE_02cc3d00 + 0x10);
  param_1[0x37] = lVar8;
  uVar6 = *(undefined1 *)(param_2 + 0x1c0);
  param_1[0x39] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x38) = uVar6;
  puVar7 = PTR__ZTV23CParameterPropertyValueIfLj39E18CPropertyConverterE_02cbf368;
  *(undefined4 *)(param_1 + 0x3a) = *(undefined4 *)(param_2 + 0x1d0);
  param_1[0x36] = (long)(puVar7 + 0x10);
  uVar5 = *(undefined4 *)(param_2 + 0x1d8);
  param_1[0x3c] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x3b) = uVar5;
  lVar8 = *(long *)(param_2 + 0x1e8);
  param_1[0x3c] = (long)(PTR__ZTV22CParameterPropertyBaseILj46EE_02cc4ed0 + 0x10);
  param_1[0x3d] = lVar8;
  uVar6 = *(undefined1 *)(param_2 + 0x1f0);
  param_1[0x3f] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x3e) = uVar6;
  puVar7 = PTR__ZTV23CParameterPropertyValueIfLj46E18CPropertyConverterE_02cc11f8;
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_2 + 0x200);
  param_1[0x3c] = (long)(puVar7 + 0x10);
  uVar5 = *(undefined4 *)(param_2 + 0x208);
  param_1[0x42] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x41) = uVar5;
  puVar7 = PTR__ZTV22CParameterPropertyBaseILj47EE_02cba780;
  param_1[0x43] = *(long *)(param_2 + 0x218);
  param_1[0x42] = (long)(puVar7 + 0x10);
  uVar6 = *(undefined1 *)(param_2 + 0x220);
  param_1[0x45] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x44) = uVar6;
  puVar7 = PTR__ZTV23CParameterPropertyValueIfLj47E18CPropertyConverterE_02cc3370;
  *(undefined4 *)(param_1 + 0x46) = *(undefined4 *)(param_2 + 0x230);
  param_1[0x42] = (long)(puVar7 + 0x10);
  uVar5 = *(undefined4 *)(param_2 + 0x238);
  param_1[0x48] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x47) = uVar5;
  puVar7 = PTR__ZTV22CParameterPropertyBaseILj52EE_02cba830;
  param_1[0x49] = *(long *)(param_2 + 0x248);
  param_1[0x48] = (long)(puVar7 + 0x10);
  uVar6 = *(undefined1 *)(param_2 + 0x250);
  param_1[0x4b] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x4a) = uVar6;
  puVar7 = PTR__ZTV23CParameterPropertyValueIfLj52E18CPropertyConverterE_02cbb648;
  *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_2 + 0x260);
  param_1[0x48] = (long)(puVar7 + 0x10);
  uVar5 = *(undefined4 *)(param_2 + 0x268);
  param_1[0x4e] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x4d) = uVar5;
  puVar1 = PTR__ZTV22CParameterPropertyBaseILj53EE_02cb75b8;
  param_1[0x4f] = *(long *)(param_2 + 0x278);
  param_1[0x4e] = (long)(puVar1 + 0x10);
  uVar6 = *(undefined1 *)(param_2 + 0x280);
  param_1[0x51] = (long)puVar2;
  *(undefined1 *)(param_1 + 0x50) = uVar6;
  puVar1 = PTR__ZTV23CParameterPropertyValueIfLj53E18CPropertyConverterE_02cb8a30;
  *(undefined4 *)(param_1 + 0x52) = *(undefined4 *)(param_2 + 0x290);
  param_1[0x4e] = (long)(puVar1 + 0x10);
  *(undefined4 *)(param_1 + 0x53) = *(undefined4 *)(param_2 + 0x298);
  return;
}

// ==== CSoundManager::tGameVolume::tGameVolume()
// vaddr 0x17fc2a0 | ghidra 0x18fc2a0 | size 20 | symbol _ZN13CSoundManager11tGameVolumeC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager11tGameVolumeC1Ev(undefined8 *param_1)

{
  *param_1 = 0x3f8000003f800000;
  *(undefined4 *)(param_1 + 1) = 0x3f800000;
  return;
}

// ==== CSoundManager::tSoundImage::tSoundImage()
// vaddr 0x17fc2b4 | ghidra 0x18fc2b4 | size 16 | symbol _ZN13CSoundManager11tSoundImageC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager11tSoundImageC2Ev(undefined8 *param_1)

{
  *(undefined1 *)(param_1 + 3) = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  return;
}

// ==== CSoundManager::tSoundImage::tSoundImage(Framework::FileStream::tImage::tValidateEntry const&, bool)
// vaddr 0x17fc2c4 | ghidra 0x18fc2c4 | size 28 | symbol _ZN13CSoundManager11tSoundImageC2ERKN9Framework10FileStream6tImage14tValidateEntryEb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager11tSoundImageC1ERKN9Framework10FileStream6tImage14tValidateEntryEb
               (undefined8 *param_1,undefined8 *param_2,byte param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  param_1[2] = param_2[2];
  uVar2 = param_2[1];
  uVar1 = *param_2;
  *(byte *)(param_1 + 3) = param_3 & 1;
  param_1[1] = uVar2;
  *param_1 = uVar1;
  return;
}

// ==== CSoundManager::tSoundImage::IsVoice() const
// vaddr 0x17fc2e0 | ghidra 0x18fc2e0 | size 8 | symbol _ZNK13CSoundManager11tSoundImage7IsVoiceEv | lib libSOA-3.7.0.so | 2026-10-08
undefined1 _ZNK13CSoundManager11tSoundImage7IsVoiceEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x18);
}

// ==== CSoundManager::tSoundImage::VolumeBGM(float, CSoundManager::tGameVolume const&) const
// vaddr 0x17fc2e8 | ghidra 0x18fc2e8 | size 12 | symbol _ZNK13CSoundManager11tSoundImage9VolumeBGMEfRKNS_11tGameVolumeE | lib libSOA-3.7.0.so | 2026-10-08
float _ZNK13CSoundManager11tSoundImage9VolumeBGMEfRKNS_11tGameVolumeE
                (float param_1,undefined8 param_2,float *param_3)

{
  return *param_3 * param_1;
}

// ==== CSoundManager::tSoundImage::VolumeSE(float, CSoundManager::tGameVolume const&) const
// vaddr 0x17fc2f4 | ghidra 0x18fc2f4 | size 32 | symbol _ZNK13CSoundManager11tSoundImage8VolumeSEEfRKNS_11tGameVolumeE | lib libSOA-3.7.0.so | 2026-10-08
float _ZNK13CSoundManager11tSoundImage8VolumeSEEfRKNS_11tGameVolumeE
                (float param_1,long param_2,long param_3)

{
  float *pfVar1;
  
  pfVar1 = (float *)(param_3 + 4);
  if (*(char *)(param_2 + 0x18) == '\0') {
    pfVar1 = (float *)(param_3 + 8);
  }
  return *pfVar1 * param_1;
}

// ==== CSoundManager::tPlaySetting::tPlaySetting()
// vaddr 0x17fc314 | ghidra 0x18fc314 | size 28 | symbol _ZN13CSoundManager12tPlaySettingC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager12tPlaySettingC2Ev(long param_1)

{
  Framework::CSound::tArguments::tArguments()();
  *(undefined8 *)(param_1 + 0x70) = 1;
  return;
}

// ==== CSoundManager::CSoundManager()
// vaddr 0x17fc330 | ghidra 0x18fc330 | size 208 | symbol _ZN13CSoundManagerC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManagerC1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  long lVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
  if (*(long *)PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x15,&UNK_027daee5/*"m_pInstance isn't null.(%08x)"*/);
  }
  *(long **)puVar1 = param_1;
  puVar1 = PTR__ZTV13CSoundManager_02cbd820 + 0x10;
  *(undefined4 *)(param_1 + 1) = 0x3f800000;
  *(undefined8 *)((long)param_1 + 0xc) = 0x3f8000003f800000;
  *param_1 = (long)puVar1;
  Framework::CSoundManager::CSoundManager()(param_1 + 3);
  *(undefined4 *)(param_1 + 0x18) = 0x3f800000;
  puVar2 = PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  param_1[0x22] = (long)(param_1 + 0x22);
  param_1[0x23] = (long)(param_1 + 0x22);
  param_1[0x20] = 0x3f8000003f800000;
  param_1[0x28] = 0;
  *(undefined4 *)(param_1 + 0x29) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x2a) = 0x20;
  puVar1 = PTR__ZTVN13CSoundManager16CInterruptNotifyE_02cc1240;
  *(undefined4 *)(param_1 + 0x2d) = 0;
  param_1[0x15] = 0;
  param_1[0x14] = 0;
  param_1[0x17] = 0;
  param_1[0x16] = 0;
  lVar3 = *(long *)puVar2;
  param_1[0x1d] = 0;
  param_1[0x1c] = 0;
  param_1[0x1f] = 0;
  param_1[0x1e] = 0;
  param_1[0x1b] = 0;
  param_1[0x1a] = 0;
  param_1[0x25] = 0;
  param_1[0x24] = 0;
  param_1[0x27] = 0;
  param_1[0x26] = 0;
  *(undefined2 *)(param_1 + 0x1a) = 0;
  *(undefined2 *)(param_1 + 0x1d) = 0;
  param_1[0x2b] = (long)(puVar1 + 0x10);
  param_1[0x2c] = (long)param_1;
  param_1[0x19] = lVar3;
  *(undefined4 *)(param_1 + 0x21) = 0x3f800000;
  return;
}

// ==== CSoundManager::~CSoundManager()
// vaddr 0x17fc400 | ghidra 0x18fc400 | size 472 | symbol _ZN13CSoundManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManagerD2Ev(long *param_1)

{
  long lVar1;
  undefined *puVar2;
  int iVar3;
  long *plVar4;
  long *plVar5;
  long lVar6;
  long *plVar7;
  
  plVar4 = param_1 + 3;
  *param_1 = (long)(PTR__ZTV13CSoundManager_02cbd820 + 0x10);
  Framework::CSoundManager::EnableIgnorePlayRequest(bool)(plVar4,1);
  Framework::CSoundManager::StopAll()(plVar4);
  iVar3 = Framework::CSoundManager::NumPlaying() const(plVar4);
  if (iVar3 == 0) {
    Framework::CSoundManager::Release()(plVar4);
    plVar5 = (long *)param_1[0x27];
  }
  else {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0x5c,&UNK_02868699);
    plVar5 = (long *)param_1[0x27];
  }
  while (plVar5 != (long *)0x0) {
    lVar6 = *plVar5;
    if (plVar5[7] != 0) {
      lVar1 = plVar5[5];
      plVar7 = (long *)plVar5[6];
      *(undefined8 *)(*plVar7 + 8) = *(undefined8 *)(lVar1 + 8);
      **(long **)(lVar1 + 8) = *plVar7;
      plVar5[7] = 0;
      while (plVar7 != plVar5 + 5) {
        plVar7 = (long *)plVar7[1];
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
      }
    }
    if ((*(byte *)(plVar5 + 2) & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar5[4]);
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar5);
    plVar5 = (long *)lVar6;
  }
  lVar6 = param_1[0x25];
  param_1[0x25] = 0;
  if (lVar6 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  if (param_1[0x24] != 0) {
    lVar6 = param_1[0x22];
    plVar5 = (long *)param_1[0x23];
    *(undefined8 *)(*plVar5 + 8) = *(undefined8 *)(lVar6 + 8);
    **(long **)(lVar6 + 8) = *plVar5;
    param_1[0x24] = 0;
    while (plVar5 != param_1 + 0x22) {
      plVar7 = (long *)plVar5[1];
      if ((*(byte *)(plVar5 + 2) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar5[4]);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar5);
      plVar5 = plVar7;
    }
  }
  if ((*(byte *)(param_1 + 0x1d) & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0x1f]);
  }
  if ((*(byte *)(param_1 + 0x1a) & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(param_1[0x1c]);
  }
  std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, Framework::CSTLUnorderedMapAllocatorInf> >::__deallocate(std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, void*>*)(param_1 + 0x14,param_1[0x16]);
  lVar6 = param_1[0x14];
  param_1[0x14] = 0;
  if (lVar6 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  Framework::CSoundManager::~CSoundManager()(plVar4);
  puVar2 = PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
  if (*(long *)PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x1d,&UNK_027daf21/*"m_pInstance is null."*/);
  }
  *(undefined8 *)puVar2 = 0;
  return;
}

// ==== CSoundManager::Release()
// vaddr 0x17fc5d8 | ghidra 0x18fc5d8 | size 72 | symbol _ZN13CSoundManager7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN13CSoundManager7ReleaseEv(long param_1)

{
  int iVar1;
  
  param_1 = param_1 + 0x18;
  Framework::CSoundManager::EnableIgnorePlayRequest(bool)(param_1,1);
  Framework::CSoundManager::StopAll()(param_1);
  iVar1 = Framework::CSoundManager::NumPlaying() const(param_1);
  if (iVar1 != 0) {
    return 0;
  }
  Framework::CSoundManager::Release()(param_1);
  return 1;
}

// ==== CSoundManager::~CSoundManager()
// vaddr 0x17fc620 | ghidra 0x18fc620 | size 24 | symbol _ZN13CSoundManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManagerD0Ev(undefined8 param_1)

{
  CSoundManager::~CSoundManager()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CSoundManager::Initialize()
// vaddr 0x17fc638 | ghidra 0x18fc638 | size 52 | symbol _ZN13CSoundManager10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager10InitializeEv(long param_1)

{
  Framework::CSoundManager::Initialize(unsigned int)(param_1 + 0x18,0x200);
  *(long *)(*(long *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50 + 0x10e0) = param_1 + 0x158;
  (*(code *)PTR__ZN13CSoundManager16CInterruptNotify7HandlerEm_02c9b040)(param_1 + 0x158,1);
  return;
}

// ==== CSoundManager::CInterruptNotify::Handler(unsigned long)
// vaddr 0x17fc66c | ghidra 0x18fc66c | size 392 | symbol _ZN13CSoundManager16CInterruptNotify7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager16CInterruptNotify7HandlerEm(long param_1,int param_2)

{
  undefined4 uVar1;
  ulong uVar2;
  long lVar3;
  code *pcVar4;
  undefined *puStack_50;
  float fStack_48;
  undefined4 uStack_44;
  long *plStack_30;
  
  if (param_2 != 1) {
    return;
  }
  uVar2 = Aska::SoundManager::IsOtherAudioPlaying() const(*(undefined8 *)PTR__ZN4Aska6Global15m_pSoundManagerE_02cc3a50);
  if ((uVar2 & 1) == 0) {
    if (*(float *)(param_1 + 0x10) <= 0.0) {
      return;
    }
    *(float *)(*(long *)(param_1 + 8) + 0x108) = *(float *)(param_1 + 0x10);
    lVar3 = *(long *)(param_1 + 8);
    if (*(long *)(lVar3 + 200) != *(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340) {
      puStack_50 = &UNK_02b11268;
      fStack_48 = *(float *)(lVar3 + 0x104) * *(float *)(lVar3 + 0x100) * *(float *)(lVar3 + 0x108)
                  * *(float *)(lVar3 + 8);
      uStack_44 = 0x44fa0000;
      plStack_30 = (long *)&puStack_50;
      Framework::CSoundManager::Element(unsigned long, std::__ndk1::function<void (Framework::CSound::CElement&)>)(lVar3 + 0x18,*(long *)(lVar3 + 200),&puStack_50);
      if (&puStack_50 == (undefined **)plStack_30) {
        pcVar4 = *(code **)(*plStack_30 + 0x20);
      }
      else {
        if (plStack_30 == (long *)0x0) goto code_r0x018fc7e0;
        pcVar4 = *(code **)(*plStack_30 + 0x28);
      }
      (*pcVar4)();
    }
code_r0x018fc7e0:
    *(undefined4 *)(param_1 + 0x10) = 0;
    return;
  }
  uVar1 = *(undefined4 *)(*(long *)(param_1 + 8) + 0x108);
  *(undefined4 *)(*(long *)(param_1 + 8) + 0x108) = 0;
  lVar3 = *(long *)(param_1 + 8);
  if (*(long *)(lVar3 + 200) != *(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340) {
    puStack_50 = &UNK_02b11268;
    fStack_48 = *(float *)(lVar3 + 0x104) * *(float *)(lVar3 + 0x100) * *(float *)(lVar3 + 0x108) *
                *(float *)(lVar3 + 8);
    uStack_44 = 0x44fa0000;
    plStack_30 = (long *)&puStack_50;
    Framework::CSoundManager::Element(unsigned long, std::__ndk1::function<void (Framework::CSound::CElement&)>)(lVar3 + 0x18,*(long *)(lVar3 + 200),&puStack_50);
    if (&puStack_50 == (undefined **)plStack_30) {
      pcVar4 = *(code **)(*plStack_30 + 0x20);
    }
    else {
      if (plStack_30 == (long *)0x0) goto code_r0x018fc7cc;
      pcVar4 = *(code **)(*plStack_30 + 0x28);
    }
    (*pcVar4)();
  }
code_r0x018fc7cc:
  *(undefined4 *)(param_1 + 0x10) = uVar1;
  return;
}

// ==== CSoundManager::StopAll()
// vaddr 0x17fc7f4 | ghidra 0x18fc7f4 | size 464 | symbol _ZN13CSoundManager7StopAllEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager7StopAllEv(long param_1)

{
  byte bVar1;
  long *plVar2;
  bool bVar3;
  byte *pbVar4;
  long lVar5;
  undefined1 *puVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  ulong *puVar10;
  long lVar11;
  long *plVar12;
  
  Framework::CSoundManager::StopAll()(param_1 + 0x18);
  if (*(long *)(param_1 + 0x140) != 0) {
    plVar2 = (long *)*(long *)(param_1 + 0x138);
    while (plVar2 != (long *)0x0) {
      lVar11 = *plVar2;
      if (plVar2[7] != 0) {
        lVar5 = plVar2[5];
        plVar12 = (long *)plVar2[6];
        *(undefined8 *)(*plVar12 + 8) = *(undefined8 *)(lVar5 + 8);
        **(long **)(lVar5 + 8) = *plVar12;
        plVar2[7] = 0;
        while (plVar12 != plVar2 + 5) {
          plVar12 = (long *)plVar12[1];
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
        }
      }
      if ((*(byte *)(plVar2 + 2) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar2[4]);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar2);
      plVar2 = (long *)lVar11;
    }
    lVar11 = *(long *)(param_1 + 0x130);
    *(undefined8 *)(param_1 + 0x138) = 0;
    if (lVar11 != 0) {
      lVar5 = 0;
      do {
        *(undefined8 *)(*(long *)(param_1 + 0x128) + lVar5 * 8) = 0;
        lVar5 = lVar5 + 1;
      } while (lVar11 != lVar5);
    }
    *(undefined8 *)(param_1 + 0x140) = 0;
  }
  pbVar4 = (byte *)(param_1 + 0xe8);
  bVar1 = *pbVar4;
  if ((bVar1 & 1) != 0) {
    bVar1 = *pbVar4;
  }
  if ((bVar1 & 1) == 0) {
    puVar6 = (undefined1 *)(param_1 + 0xe9);
  }
  else {
    puVar6 = *(undefined1 **)(param_1 + 0xf8);
  }
  *puVar6 = 0;
  uVar8 = (ulong)*pbVar4;
  if ((*pbVar4 & 1) == 0) {
    uVar9 = *(ulong *)(param_1 + 0xf0);
    uVar8 = 0;
    *(undefined1 *)(param_1 + 0xe8) = 0;
  }
  else {
    uVar9 = 0;
    *(undefined8 *)(param_1 + 0xf0) = 0;
  }
  puVar10 = (ulong *)(param_1 + 0xd0);
  uVar7 = (ulong)*(byte *)puVar10;
  bVar3 = (uVar8 & 1) != 0;
  uVar8 = uVar8 >> 1;
  if (bVar3) {
    uVar8 = uVar9;
  }
  lVar11 = *(long *)(param_1 + 0xf8);
  if (!bVar3) {
    lVar11 = param_1 + 0xe9;
  }
  if ((*(byte *)puVar10 & 1) == 0) {
    uVar9 = 0x16;
    lVar5 = uVar8 - 0x16;
    if (0x15 < uVar8 && lVar5 != 0) {
code_r0x018fc944:
      if ((uVar7 & 1) == 0) {
        uVar7 = (ulong)(((uint)uVar7 & 0xfe) >> 1);
      }
      else {
        uVar7 = *(ulong *)(param_1 + 0xd8);
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar10,uVar9,lVar5,uVar7,0,uVar7,uVar8);
      goto code_r0x018fc9a4;
    }
  }
  else {
    uVar7 = *puVar10;
    uVar9 = (uVar7 & 0xfffffffffffffffe) - 1;
    lVar5 = uVar8 - uVar9;
    if (uVar9 <= uVar8 && lVar5 != 0) goto code_r0x018fc944;
  }
  if ((uVar7 & 1) == 0) {
    lVar5 = param_1 + 0xd1;
  }
  else {
    lVar5 = *(long *)(param_1 + 0xe0);
  }
  if (uVar8 != 0) {
    memmove(lVar5,lVar11,uVar8);
  }
  *(undefined1 *)(lVar5 + uVar8) = 0;
  if ((*(byte *)puVar10 & 1) == 0) {
    *(byte *)puVar10 = (byte)(uVar8 << 1);
  }
  else {
    *(ulong *)(param_1 + 0xd8) = uVar8;
  }
code_r0x018fc9a4:
  *(undefined8 *)(param_1 + 200) = *(undefined8 *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340
  ;
  return;
}

// ==== CSoundManager::StopSE(std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)
// vaddr 0x17fc9c4 | ghidra 0x18fc9c4 | size 204 | symbol _ZN13CSoundManager6StopSEENSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager6StopSEENSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE(long param_1)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  
  Framework::CSoundManager::StopSE(float)(param_1 + 0x18);
  if (*(long *)(param_1 + 0x140) != 0) {
    plVar1 = (long *)*(long *)(param_1 + 0x138);
    while (plVar1 != (long *)0x0) {
      lVar3 = *plVar1;
      if (plVar1[7] != 0) {
        lVar2 = plVar1[5];
        plVar4 = (long *)plVar1[6];
        *(undefined8 *)(*plVar4 + 8) = *(undefined8 *)(lVar2 + 8);
        **(long **)(lVar2 + 8) = *plVar4;
        plVar1[7] = 0;
        while (plVar4 != plVar1 + 5) {
          plVar4 = (long *)plVar4[1];
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
        }
      }
      if ((*(byte *)(plVar1 + 2) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1[4]);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
      plVar1 = (long *)lVar3;
    }
    lVar3 = *(long *)(param_1 + 0x130);
    *(undefined8 *)(param_1 + 0x138) = 0;
    if (lVar3 != 0) {
      lVar2 = 0;
      do {
        *(undefined8 *)(*(long *)(param_1 + 0x128) + lVar2 * 8) = 0;
        lVar2 = lVar2 + 1;
      } while (lVar3 != lVar2);
    }
    *(undefined8 *)(param_1 + 0x140) = 0;
  }
  return;
}

// ==== CSoundManager::StopSE3D(std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)
// vaddr 0x17fca90 | ghidra 0x18fca90 | size 168 | symbol _ZN13CSoundManager8StopSE3DENSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager8StopSE3DENSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE
               (undefined8 param_1,long param_2)

{
  bool bVar1;
  long *plVar2;
  long lVar3;
  undefined8 uVar4;
  ulong uVar5;
  ulong uVar6;
  
  plVar2 = (long *)Framework::CSoundManager::rElementContainer() const(param_2 + 0x18);
  lVar3 = (**(code **)(*plVar2 + 0x20))();
  if (lVar3 != 0) {
    uVar5 = 0;
    uVar6 = 1;
    do {
      uVar4 = (**(code **)(*plVar2 + 0x30))(plVar2,uVar5);
      uVar5 = Framework::CSound::CElement::Is3D() const();
      if ((uVar5 & 1) != 0) {
        uVar4 = Framework::CSound::CElement::Handle() const(uVar4);
        Framework::CSoundManager::Stop(unsigned long, float)(param_1,param_2 + 0x18,uVar4);
      }
      uVar5 = (**(code **)(*plVar2 + 0x20))(plVar2);
      bVar1 = uVar6 < uVar5;
      uVar5 = uVar6;
      uVar6 = (ulong)((int)uVar6 + 1);
    } while (bVar1);
  }
  return;
}

// ==== CSoundManager::NumPlaying() const
// vaddr 0x17fcb38 | ghidra 0x18fcb38 | size 8 | symbol _ZNK13CSoundManager10NumPlayingEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK13CSoundManager10NumPlayingEv(long param_1)

{
  (*(code *)PTR__ZNK9Framework13CSoundManager10NumPlayingEv_02c9d1d0)(param_1 + 0x18);
  return;
}

// ==== CSoundManager::GetPlaySetting(char const*)
// vaddr 0x17fcb40 | ghidra 0x18fcb40 | size 152 | symbol _ZN13CSoundManager14GetPlaySettingEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager14GetPlaySettingEPKc(undefined8 param_1,long param_2)

{
  long lVar1;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xa5,&UNK_028686b2/*"apName is null."*/);
  }
  lVar1 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xa8,&UNK_027fd285/*"pParameterManager is null."*/);
  }
  lVar1 = CParameterManager::pParameterSound() const(lVar1);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xab,&UNK_027fd2a0/*"pParameterSound is null."*/);
  }
  CParameterSound::pParameter(char const*) const(lVar1,param_2);
  (*(code *)PTR__ZN13CSoundManager20GetPlaySettingDetailEPK22CParameterSoundElement_02c921c8)
            (param_1);
  return;
}

// ==== CSoundManager::GetPlaySettingDetail(CParameterSoundElement const*)
// vaddr 0x17fcbd8 | ghidra 0x18fcbd8 | size 408 | symbol _ZN13CSoundManager20GetPlaySettingDetailEPK22CParameterSoundElement | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN13CSoundManager20GetPlaySettingDetailEPK22CParameterSoundElement(long param_1,long param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined *puStack_78;
  undefined4 uStack_70;
  float fStack_68;
  undefined *puStack_60;
  undefined8 uStack_58;
  undefined1 uStack_50;
  undefined *puStack_48;
  undefined4 uStack_40;
  float fStack_38;
  
  Framework::CSound::tArguments::tArguments()(param_1);
  *(undefined8 *)(param_1 + 0x70) = 1;
  if (param_2 != 0) {
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_2 + 0xe8);
    *(short *)(param_1 + 0x1c) = (short)*(undefined4 *)(param_2 + 0x118);
    *(int *)(param_1 + 8) = (int)*(float *)(param_2 + 0x148);
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_2 + 0x178);
    *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_2 + 0x1a8);
    if (*(float *)(param_2 + 0x1d8) != 0.0) {
      *(float *)(param_1 + 0x18) = *(float *)(param_2 + 0x1d8);
      *(undefined1 *)(param_1 + 0x31) = 1;
    }
    fVar3 = *(float *)(param_2 + 0x208);
    if ((fVar3 != 0.0) || (*(float *)(param_2 + 0x238) != 0.0)) {
      fVar4 = *(float *)(param_2 + 0x238) - fVar3;
      if (_UNK_027ebe10 <= fVar4) {
        fVar1 = (float)Aska::RandomFloat()();
        fVar2 = -fVar4;
        if (0.0 <= fVar4) {
          fVar2 = fVar4;
        }
        fVar3 = fVar3 + fVar2 * fVar1;
      }
      *(float *)(param_1 + 0x14) = fVar3;
    }
    uStack_58 = *(undefined8 *)(param_2 + 0x248);
    uStack_50 = *(undefined1 *)(param_2 + 0x250);
    puStack_78 = PTR__ZTVN9Framework7CHash32E_02cba528 + 0x10;
    uStack_40 = *(undefined4 *)(param_2 + 0x260);
    puStack_60 = PTR__ZTV23CParameterPropertyValueIfLj52E18CPropertyConverterE_02cbb648 + 0x10;
    fStack_38 = *(float *)(param_2 + 0x268);
    uStack_70 = *(undefined4 *)(param_2 + 0x290);
    fStack_68 = *(float *)(param_2 + 0x298);
    if (fStack_38 != 0.0) {
      *(float *)(param_1 + 0x60) = fStack_38;
    }
    if (fStack_68 != 0.0) {
      *(float *)(param_1 + 100) = fStack_68;
    }
    puStack_48 = puStack_78;
    Framework::CHash32::~CHash32()(&puStack_78);
    puStack_60 = PTR__ZTV22CParameterPropertyBaseILj52EE_02cba830 + 0x10;
    Framework::CHash32::~CHash32()(&puStack_48);
  }
  return;
}

// ==== CSoundManager::IsExistSoundFile(char const*)
// vaddr 0x17fcd70 | ghidra 0x18fcd70 | size 128 | symbol _ZN13CSoundManager16IsExistSoundFileEPKc | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN13CSoundManager16IsExistSoundFileEPKc(long param_1)

{
  bool bVar1;
  long lVar2;
  
  bVar1 = false;
  if (param_1 != 0) {
    lVar2 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xb8,&UNK_027fd285/*"pParameterManager is null."*/);
    }
    lVar2 = CParameterManager::pParameterSound() const(lVar2);
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xbb,&UNK_027fd2a0/*"pParameterSound is null."*/);
    }
    lVar2 = CParameterSound::pParameter(char const*) const(lVar2,param_1);
    bVar1 = lVar2 != 0;
  }
  return bVar1;
}

// ==== CSoundManager::IsExistPlaySetting(char const*, unsigned int)
// vaddr 0x17fcdf0 | ghidra 0x18fcdf0 | size 160 | symbol _ZN13CSoundManager18IsExistPlaySettingEPKcj | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN13CSoundManager18IsExistPlaySettingEPKcj(long param_1,undefined4 param_2)

{
  long lVar1;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,199,&UNK_0285ea95/*"apPackageName is null."*/);
  }
  lVar1 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xca,&UNK_027fd285/*"pParameterManager is null."*/);
  }
  lVar1 = CParameterManager::pParameterSound() const(lVar1);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xcd,&UNK_027fd2a0/*"pParameterSound is null."*/);
  }
  lVar1 = CParameterSound::pParameter(char const*, unsigned int) const(lVar1,param_1,param_2);
  return lVar1 != 0;
}

// ==== CSoundManager::GetPlaySetting(char const*, unsigned int)
// vaddr 0x17fce90 | ghidra 0x18fce90 | size 168 | symbol _ZN13CSoundManager14GetPlaySettingEPKcj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager14GetPlaySettingEPKcj(undefined8 param_1,long param_2,undefined4 param_3)

{
  long lVar1;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xd8,&UNK_0285ea95/*"apPackageName is null."*/);
  }
  lVar1 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xdb,&UNK_027fd285/*"pParameterManager is null."*/);
  }
  lVar1 = CParameterManager::pParameterSound() const(lVar1);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xde,&UNK_027fd2a0/*"pParameterSound is null."*/);
  }
  CParameterSound::pParameter(char const*, unsigned int) const(lVar1,param_2,param_3);
  (*(code *)PTR__ZN13CSoundManager20GetPlaySettingDetailEPK22CParameterSoundElement_02c921c8)
            (param_1);
  return;
}

// ==== CSoundManager::GetPlayElement(char const*)
// vaddr 0x17fcf38 | ghidra 0x18fcf38 | size 140 | symbol _ZN13CSoundManager14GetPlayElementEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager14GetPlayElementEPKc(long param_1)

{
  long lVar1;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xe8,&UNK_028686b2/*"apName is null."*/);
  }
  lVar1 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xeb,&UNK_027fd285/*"pParameterManager is null."*/);
  }
  lVar1 = CParameterManager::pParameterSound() const(lVar1);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xee,&UNK_027fd2a0/*"pParameterSound is null."*/);
  }
  (*(code *)PTR__ZNK15CParameterSound10pParameterEPKc_02caf258)(lVar1,param_1);
  return;
}

// ==== CSoundManager::PlaySe(char const*)
// vaddr 0x17fcfc4 | ghidra 0x18fcfc4 | size 336 | symbol _ZN13CSoundManager6PlaySeEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager6PlaySeEPKc(long param_1,long param_2)

{
  long *plVar1;
  ulong uVar2;
  long lVar3;
  long *plVar4;
  undefined1 auStack_b0 [128];
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0x147,&UNK_028686b2/*"apName is null."*/);
  }
  plVar4 = *(long **)(param_1 + 0x118);
  while (plVar1 = plVar4, (long *)(param_1 + 0x110) != plVar1) {
    if ((*(byte *)(plVar1 + 2) & 1) == 0) {
      lVar3 = (long)plVar1 + 0x11;
    }
    else {
      lVar3 = plVar1[4];
    }
    uVar2 = CSoundManager::ResourceMapping(char const*)(param_1,lVar3);
    plVar4 = (long *)plVar1[1];
    if ((uVar2 & 1) != 0) {
      *(long **)(*plVar1 + 8) = plVar4;
      *(long *)plVar1[1] = *plVar1;
      *(long *)(param_1 + 0x120) = *(long *)(param_1 + 0x120) + -1;
      if ((*(byte *)(plVar1 + 2) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1[4]);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
    }
  }
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xa5,&UNK_028686b2/*"apName is null."*/);
  }
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xa8,&UNK_027fd285/*"pParameterManager is null."*/);
  }
  lVar3 = CParameterManager::pParameterSound() const(lVar3);
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xab,&UNK_027fd2a0/*"pParameterSound is null."*/);
  }
  CParameterSound::pParameter(char const*) const(lVar3,param_2);
  CSoundManager::GetPlaySettingDetail(CParameterSoundElement const*)(auStack_b0);
  CSoundManager::PlaySe(char const*, CSoundManager::tPlaySetting const&)(param_1,param_2,auStack_b0);
  return;
}

// ==== CSoundManager::UpdateMapping()
// vaddr 0x17fd114 | ghidra 0x18fd114 | size 152 | symbol _ZN13CSoundManager13UpdateMappingEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager13UpdateMappingEv(long param_1)

{
  long *plVar1;
  ulong uVar2;
  long lVar3;
  long *plVar4;
  
  plVar4 = *(long **)(param_1 + 0x118);
  while (plVar1 = plVar4, (long *)(param_1 + 0x110) != plVar1) {
    if ((*(byte *)(plVar1 + 2) & 1) == 0) {
      lVar3 = (long)plVar1 + 0x11;
    }
    else {
      lVar3 = plVar1[4];
    }
    uVar2 = CSoundManager::ResourceMapping(char const*)(param_1,lVar3);
    plVar4 = (long *)plVar1[1];
    if ((uVar2 & 1) != 0) {
      *(long **)(*plVar1 + 8) = plVar4;
      *(long *)plVar1[1] = *plVar1;
      *(long *)(param_1 + 0x120) = *(long *)(param_1 + 0x120) + -1;
      if ((*(byte *)(plVar1 + 2) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1[4]);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
    }
  }
  return;
}

// ==== CSoundManager::PlaySe(char const*, CSoundManager::tPlaySetting const&)
// vaddr 0x17fd1ac | ghidra 0x18fd1ac | size 2776 | symbol _ZN13CSoundManager6PlaySeEPKcRKNS_12tPlaySettingE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

long _ZN13CSoundManager6PlaySeEPKcRKNS_12tPlaySettingE
               (long param_1,long param_2,undefined8 *param_3)

{
  long *******ppppppplVar1;
  float *pfVar2;
  uint uVar3;
  char cVar4;
  byte bVar5;
  ulong uVar6;
  ulong uVar7;
  int iVar8;
  ulong uVar9;
  long *plVar10;
  ulong uVar11;
  long *plVar12;
  long *******ppppppplVar13;
  long lVar14;
  undefined8 *puVar15;
  ulong uVar16;
  long *plVar17;
  long lVar18;
  undefined8 uVar19;
  ulong uVar20;
  long *plVar21;
  ulong unaff_x27;
  float fVar22;
  long *plStack_110;
  ulong uStack_108;
  undefined8 uStack_100;
  long lStack_f8;
  undefined8 uStack_f0;
  long *plStack_e8;
  undefined8 uStack_e0;
  undefined1 uStack_d8;
  undefined1 uStack_d0;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a0;
  long *******ppppppplStack_90;
  long *******ppppppplStack_88;
  ulong uStack_80;
  ulong uStack_78;
  ulong uStack_70;
  ulong uStack_68;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0x153,&UNK_028686b2/*"apName is null."*/);
  }
  plVar17 = *(long **)(param_1 + 0x118);
  while (plVar10 = plVar17, (long *)(param_1 + 0x110) != plVar10) {
    if ((*(byte *)(plVar10 + 2) & 1) == 0) {
      lVar18 = (long)plVar10 + 0x11;
    }
    else {
      lVar18 = plVar10[4];
    }
    uVar9 = CSoundManager::ResourceMapping(char const*)(param_1,lVar18);
    plVar17 = (long *)plVar10[1];
    if ((uVar9 & 1) != 0) {
      *(long **)(*plVar10 + 8) = plVar17;
      *(long *)plVar10[1] = *plVar10;
      *(long *)(param_1 + 0x120) = *(long *)(param_1 + 0x120) + -1;
      if ((*(byte *)(plVar10 + 2) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar10[4]);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar10);
    }
  }
  uStack_70 = 0;
  uStack_68 = 0;
  uStack_78 = 0;
  uVar9 = strlen(param_2);
  if (uVar9 < 0x17) {
    uVar20 = (ulong)&uStack_78 | 1;
    uStack_78 = CONCAT71(uStack_78._1_7_,(char)(uVar9 << 1));
    if (uVar9 != 0) goto code_r0x018fd300;
  }
  else {
    uVar11 = uVar9 + 0x10 & 0xfffffffffffffff0;
    if (uVar11 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar20 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar20 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_78 = uVar11 | 1;
    uStack_70 = uVar9;
    uStack_68 = uVar20;
code_r0x018fd300:
    memcpy(uVar20,param_2,uVar9);
  }
  plVar17 = (long *)(param_1 + 0x128);
  *(undefined1 *)(uVar20 + uVar9) = 0;
  plVar10 = (long *)std::__ndk1::__hash_iterator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> > >, void*>*> std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> > >, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> > >, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> > >, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> > >, Framework::CSTLUnorderedMapAllocatorInf> >::find<string >(string const&)(plVar17,&uStack_78);
  if (plVar10 == (long *)0x0) {
    ppppppplStack_90 = (long *******)&ppppppplStack_90;
    uVar9 = uStack_78 >> 1 & 0x7f;
    uVar11 = (ulong)&uStack_78 | 1;
    if ((uStack_78 & 1) != 0) {
      uVar9 = uStack_70;
      uVar11 = uStack_68;
    }
    uStack_80 = 0;
    ppppppplStack_88 = ppppppplStack_90;
    uVar9 = std::__ndk1::__murmur2_or_cityhash<unsigned long, 64ul>::operator()(void const*, unsigned long)(&plStack_110,uVar11,uVar9);
    uVar11 = *(ulong *)(param_1 + 0x130);
    if (uVar11 != 0) {
      uVar20 = uVar11 - 1;
      if ((uVar20 & uVar11) == 0) {
        unaff_x27 = uVar20 & uVar9;
      }
      else {
        uVar6 = 0;
        if (uVar11 != 0) {
          uVar6 = uVar9 / uVar11;
        }
        unaff_x27 = uVar9 - uVar6 * uVar11;
      }
      puVar15 = *(undefined8 **)(*plVar17 + unaff_x27 * 8);
      if ((puVar15 != (undefined8 *)0x0) && (plVar10 = (long *)*puVar15, plVar10 != (long *)0x0)) {
        uVar6 = (ulong)&uStack_78 | 1;
        uVar7 = uStack_78 >> 1 & 0x7f;
        if ((uStack_78 & 1) != 0) {
          uVar6 = uStack_68;
          uVar7 = uStack_70;
        }
        if ((uVar20 & uVar11) == 0) {
          if (uVar7 == 0) {
            do {
              if ((plVar10[1] & uVar20) != unaff_x27) break;
              uVar6 = (ulong)(*(byte *)(plVar10 + 2) >> 1);
              if ((*(byte *)(plVar10 + 2) & 1) != 0) {
                uVar6 = plVar10[3];
              }
              if (uVar6 == 0) goto joined_r0x018fdb30;
              plVar10 = (long *)*plVar10;
            } while (plVar10 != (long *)0x0);
          }
          else {
            do {
              if ((plVar10[1] & uVar20) != unaff_x27) break;
              bVar5 = *(byte *)(plVar10 + 2);
              uVar16 = (ulong)(bVar5 >> 1);
              if ((bVar5 & 1) != 0) {
                uVar16 = plVar10[3];
              }
              if (uVar16 == uVar7) {
                if ((bVar5 & 1) == 0) {
                  uVar16 = 0;
                  while (*(char *)((long)plVar10 + uVar16 + 0x11) == *(char *)(uVar6 + uVar16)) {
                    uVar16 = uVar16 + 1;
                    if (bVar5 >> 1 == uVar16) goto joined_r0x018fdb30;
                  }
                }
                else {
                  iVar8 = memcmp(plVar10[4],uVar6,uVar7);
                  if (iVar8 == 0) goto joined_r0x018fdb30;
                }
              }
              plVar10 = (long *)*plVar10;
            } while (plVar10 != (long *)0x0);
          }
        }
        else if (uVar7 == 0) {
          do {
            uVar20 = 0;
            if (uVar11 != 0) {
              uVar20 = (ulong)plVar10[1] / uVar11;
            }
            if (plVar10[1] - uVar20 * uVar11 != unaff_x27) break;
            uVar20 = (ulong)(*(byte *)(plVar10 + 2) >> 1);
            if ((*(byte *)(plVar10 + 2) & 1) != 0) {
              uVar20 = plVar10[3];
            }
            if (uVar20 == 0) goto joined_r0x018fdb30;
            plVar10 = (long *)*plVar10;
          } while (plVar10 != (long *)0x0);
        }
        else {
          do {
            uVar20 = 0;
            if (uVar11 != 0) {
              uVar20 = (ulong)plVar10[1] / uVar11;
            }
            if (plVar10[1] - uVar20 * uVar11 != unaff_x27) break;
            bVar5 = *(byte *)(plVar10 + 2);
            uVar20 = (ulong)(bVar5 >> 1);
            if ((bVar5 & 1) != 0) {
              uVar20 = plVar10[3];
            }
            if (uVar20 == uVar7) {
              if ((bVar5 & 1) == 0) {
                uVar20 = 0;
                while (*(char *)((long)plVar10 + uVar20 + 0x11) == *(char *)(uVar6 + uVar20)) {
                  uVar20 = uVar20 + 1;
                  if (bVar5 >> 1 == uVar20) goto joined_r0x018fdb30;
                }
              }
              else {
                iVar8 = memcmp(plVar10[4],uVar6,uVar7);
                if (iVar8 == 0) goto joined_r0x018fdb30;
              }
            }
            plVar10 = (long *)*plVar10;
          } while (plVar10 != (long *)0x0);
        }
      }
    }
    std::__ndk1::unique_ptr<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> > >, void*>, std::__ndk1::__hash_node_destructor<Framework::CSTLAllocator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> > >, void*>, Framework::CSTLUnorderedMapAllocatorInf> > > std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> > >, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> > >, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> > >, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> > >, Framework::CSTLUnorderedMapAllocatorInf> >::__construct_node_hash<string&, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> > >(unsigned long, string&, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> >&&)(&plStack_110,plVar17,uVar9,&uStack_78,&ppppppplStack_90);
    fVar22 = (float)(*(long *)(param_1 + 0x140) + 1);
    if ((uVar11 == 0) || (*(float *)(param_1 + 0x148) * (float)uVar11 < fVar22)) {
      if (uVar11 < 3) {
        uVar20 = 1;
      }
      else {
        uVar20 = (ulong)((uVar11 - 1 & uVar11) != 0);
      }
      uVar20 = uVar20 | uVar11 << 1;
      uVar11 = (ulong)(fVar22 / *(float *)(param_1 + 0x148));
      if (uVar11 <= uVar20) {
        uVar11 = uVar20;
      }
      std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> > >, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> > >, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> > >, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, Framework::CSTLList<std::__ndk1::pair<unsigned long, int> > >, Framework::CSTLUnorderedMapAllocatorInf> >::rehash(unsigned long)(plVar17,uVar11);
      uVar11 = *(ulong *)(param_1 + 0x130);
      if ((uVar11 - 1 & uVar11) == 0) {
        unaff_x27 = uVar11 - 1 & uVar9;
      }
      else {
        uVar20 = 0;
        if (uVar11 != 0) {
          uVar20 = uVar9 / uVar11;
        }
        unaff_x27 = uVar9 - uVar20 * uVar11;
      }
    }
    plVar10 = plStack_110;
    plVar12 = *(long **)(*plVar17 + unaff_x27 * 8);
    if (plVar12 == (long *)0x0) {
      *plStack_110 = *(long *)(param_1 + 0x138);
      *(long **)(param_1 + 0x138) = plStack_110;
      *(long *)(*(long *)(param_1 + 0x128) + unaff_x27 * 8) = param_1 + 0x138;
      if (*plStack_110 != 0) {
        uVar9 = *(ulong *)(*plStack_110 + 8);
        if ((uVar11 - 1 & uVar11) == 0) {
          uVar9 = uVar9 & uVar11 - 1;
        }
        else {
          uVar20 = 0;
          if (uVar11 != 0) {
            uVar20 = uVar9 / uVar11;
          }
          uVar9 = uVar9 - uVar20 * uVar11;
        }
        *(long **)(*plVar17 + uVar9 * 8) = plStack_110;
      }
    }
    else {
      *plStack_110 = *plVar12;
      *plVar12 = (long)plStack_110;
    }
    *(long *)(param_1 + 0x140) = *(long *)(param_1 + 0x140) + 1;
    plStack_110 = (long *)0x0;
joined_r0x018fdb30:
    if (uStack_80 != 0) {
      (*ppppppplStack_88)[1] = (long *****)ppppppplStack_90[1];
      *ppppppplStack_90[1] = (long *****)*ppppppplStack_88;
      uStack_80 = 0;
      ppppppplVar13 = ppppppplStack_88;
      while ((long ********)ppppppplVar13 != &ppppppplStack_90) {
        ppppppplVar13 = (long *******)ppppppplVar13[1];
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
      }
    }
  }
  plVar17 = plVar10 + 5;
  if (plVar17 == (long *)plVar10[6]) {
    uVar9 = 0;
  }
  else {
    uVar9 = 0;
    plVar12 = (long *)plVar10[6];
    do {
      while (uVar11 = Framework::CSoundManager::IsPlaying(unsigned long) const(param_1 + 0x18,plVar12[2]), (uVar11 & 1) != 0) {
        plVar12 = (long *)plVar12[1];
        uVar9 = uVar9 + 1;
        if (plVar17 == plVar12) goto code_r0x018fd3fc;
      }
      plVar21 = (long *)plVar12[1];
      *(long **)(*plVar12 + 8) = plVar21;
      *(long *)plVar12[1] = *plVar12;
      plVar10[7] = plVar10[7] + -1;
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar12);
      plVar12 = plVar21;
    } while (plVar17 != plVar21);
  }
code_r0x018fd3fc:
  if ((*(int *)(param_3 + 0xe) != 0) && ((ulong)(long)*(int *)(param_3 + 0xe) <= uVar9)) {
    if (*(int *)((long)param_3 + 0x74) < *(int *)(plVar10[6] + 0x18)) {
      lVar18 = *(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
      goto joined_r0x018fd8c4;
    }
    if (*(long *)(param_1 + 200) == *(long *)(plVar10[6] + 0x10)) {
      CSoundManager::StopBgm(std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)(0,param_1);
    }
    else {
      Framework::CSoundManager::Stop(unsigned long, float)(0,param_1 + 0x18);
    }
    plVar12 = (long *)plVar10[6];
    *(long *)(*plVar12 + 8) = plVar12[1];
    *(long *)plVar12[1] = *plVar12;
    plVar10[7] = plVar10[7] + -1;
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  ppppppplStack_88 = (long *******)0x0;
  uStack_80 = 0;
  ppppppplStack_90 = (long *******)0x0;
  ppppppplVar13 = (long *******)strlen(param_2);
  if (ppppppplVar13 < (long *******)0x17) {
    uVar11 = (ulong)&ppppppplStack_90 | 1;
    ppppppplStack_90 =
         (long *******)CONCAT71(ppppppplStack_90._1_7_,(char)((long)ppppppplVar13 << 1));
    if (ppppppplVar13 != (long *******)0x0) goto code_r0x018fd524;
  }
  else {
    uVar9 = (ulong)(ppppppplVar13 + 2) & 0xfffffffffffffff0;
    if (uVar9 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar11 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar11 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    ppppppplStack_90 = (long *******)(uVar9 | 1);
    ppppppplStack_88 = ppppppplVar13;
    uStack_80 = uVar11;
code_r0x018fd524:
    memcpy(uVar11,param_2,ppppppplVar13);
  }
  *(undefined1 *)(uVar11 + (long)ppppppplVar13) = 0;
  if (((ulong)ppppppplStack_90 & 1) == 0) {
    lVar18 = 0x16;
    ppppppplVar13 = (long *******)((ulong)ppppppplStack_90 & 0xff);
  }
  else {
    lVar18 = ((ulong)ppppppplStack_90 & 0xfffffffffffffffe) - 1;
    ppppppplVar13 = ppppppplStack_90;
  }
  ppppppplVar1 = (long *******)(ulong)(((uint)ppppppplVar13 & 0xfe) >> 1);
  if (((ulong)ppppppplVar13 & 1) != 0) {
    ppppppplVar1 = ppppppplStack_88;
  }
  if ((ulong)(lVar18 - (long)ppppppplVar1) < 4) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&ppppppplStack_90,lVar18,(4 - lVar18) + (long)ppppppplVar1,ppppppplVar1,
                    ppppppplVar1,0,4,&UNK_028686c2/*".aac"*/);
    plVar12 = *(long **)(param_1 + 0xb0);
  }
  else {
    uVar9 = (ulong)&ppppppplStack_90 | 1;
    if (((ulong)ppppppplVar13 & 1) != 0) {
      uVar9 = uStack_80;
    }
    *(undefined4 *)(uVar9 + (long)ppppppplVar1) = 0x6361612e;
    ppppppplVar1 = (long *******)((long)ppppppplVar1 + 4);
    ppppppplVar13 = ppppppplVar1;
    if (((ulong)ppppppplStack_90 & 1) == 0) {
      ppppppplStack_90 = (long *******)CONCAT71(ppppppplStack_90._1_7_,(char)ppppppplVar1 * '\x02');
      ppppppplVar13 = ppppppplStack_88;
    }
    ppppppplStack_88 = ppppppplVar13;
    *(undefined1 *)(uVar9 + (long)ppppppplVar1) = 0;
    plVar12 = *(long **)(param_1 + 0xb0);
  }
  if (plVar12 == (long *)0x0) {
code_r0x018fd8a4:
    lVar18 = *(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
  }
  else {
code_r0x018fd608:
    uStack_108 = 0;
    uStack_100 = 0;
    plStack_110 = (long *)0x0;
    if ((plVar12[2] & 1U) == 0) {
      uStack_100 = plVar12[4];
      uStack_108 = plVar12[3];
      plStack_110 = (long *)plVar12[2];
    }
    else {
      uVar9 = plVar12[3];
      lVar18 = plVar12[4];
      if (uVar9 < 0x17) {
        plStack_110 = (long *)((uVar9 & 0x7f) << 1);
        uVar20 = (ulong)&plStack_110 | 1;
        if (uVar9 != 0) goto code_r0x018fd6b0;
      }
      else {
        uVar11 = uVar9 + 0x10 & 0xfffffffffffffff0;
        if (uVar11 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar20 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (uVar20 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        plStack_110 = (long *)(uVar11 | 1);
        uStack_108 = uVar9;
        uStack_100 = uVar20;
code_r0x018fd6b0:
        memcpy(uVar20,lVar18,uVar9);
      }
      *(undefined1 *)(uVar20 + uVar9) = 0;
    }
    std::__ndk1::unordered_map<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string >, Framework::CSTLAllocator<std::__ndk1::pair<string const, CSoundManager::tSoundImage>, Framework::CSTLUnorderedMapAllocatorInf> >::unordered_map(std::__ndk1::unordered_map<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string >, Framework::CSTLAllocator<std::__ndk1::pair<string const, CSoundManager::tSoundImage>, Framework::CSTLUnorderedMapAllocatorInf> > const&)(&lStack_f8,plVar12 + 5);
    lVar14 = std::__ndk1::__hash_const_iterator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, void*>*> std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, Framework::CSTLUnorderedMapAllocatorInf> >::find<string >(string const&) const(&lStack_f8,&ppppppplStack_90);
    lVar18 = lStack_f8;
    plVar21 = plStack_e8;
    if (lVar14 == 0) goto joined_r0x018fd6e4;
    uVar19 = *(undefined8 *)(lVar14 + 0x30);
    iVar8 = *(int *)(lVar14 + 0x38);
    cVar4 = *(char *)(lVar14 + 0x40);
    plVar12 = plStack_e8;
    while (plVar12 != (long *)0x0) {
      plVar21 = (long *)*plVar12;
      lStack_f8 = lVar18;
      if ((*(byte *)(plVar12 + 2) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar12[4]);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar12);
      lVar18 = lStack_f8;
      plVar12 = plVar21;
    }
    lStack_f8 = 0;
    if (lVar18 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
    if (((ulong)plStack_110 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_100);
    }
    if (iVar8 == 0) goto code_r0x018fd8a4;
    pfVar2 = (float *)(param_1 + 0xc);
    if (cVar4 == '\0') {
      pfVar2 = (float *)(param_1 + 0x10);
    }
    plStack_e8 = (long *)param_3[5];
    uStack_f0 = param_3[4];
    lStack_f8 = param_3[3];
    uStack_108 = param_3[1];
    plStack_110 = (long *)*param_3;
    uStack_d8 = *(undefined1 *)(param_3 + 7);
    uStack_e0 = CONCAT44(*(undefined4 *)((long)param_3 + 0x34),(int)param_3[6]);
    uStack_d0 = *(undefined1 *)(param_3 + 8);
    uStack_b8 = param_3[0xb];
    uStack_c0 = param_3[10];
    uStack_b0 = param_3[0xc];
    uStack_100._0_4_ = (float)param_3[2];
    uStack_a0 = param_3[0xe];
    uStack_100 = CONCAT44((int)((ulong)param_3[2] >> 0x20),(float)uStack_100 * *pfVar2);
    lVar18 = Framework::CSoundManager::PlayMemorySE(void const*, unsigned long, Framework::CSound::tArguments const&, char const*)(param_1 + 0x18,uVar19,iVar8,&plStack_110,param_2);
    if (*(int *)(param_3 + 0xe) != 0) {
      plVar12 = (long *)plVar10[6];
      uVar3 = *(uint *)((long)param_3 + 0x74);
      do {
        if (plVar17 == plVar12) {
          plVar12 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x20,&UNK_027e7774/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_List.h"*/,0x20);
          if (plVar12 == (long *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          plVar12[1] = (long)plVar17;
          plVar12[2] = lVar18;
          plVar12[3] = (ulong)uVar3;
          lVar14 = *plVar17;
          *plVar12 = lVar14;
          *(long **)(lVar14 + 8) = plVar12;
          *plVar17 = (long)plVar12;
code_r0x018fdb8c:
          plVar10[7] = plVar10[7] + 1;
          break;
        }
        if ((int)plVar12[3] < (int)uVar3) {
          plVar17 = (long *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x20,&UNK_027e7774/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_List.h"*/,0x20);
          if (plVar17 == (long *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          *plVar17 = 0;
          plVar17[2] = lVar18;
          plVar17[3] = (ulong)uVar3;
          *(long **)(*plVar12 + 8) = plVar17;
          *plVar17 = *plVar12;
          *plVar12 = (long)plVar17;
          plVar17[1] = (long)plVar12;
          goto code_r0x018fdb8c;
        }
        plVar12 = (long *)plVar12[1];
      } while( true );
    }
  }
  if (((ulong)ppppppplStack_90 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_80);
  }
joined_r0x018fd8c4:
  if ((uStack_78 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
  }
  return lVar18;
joined_r0x018fd6e4:
  while (plVar21 != (long *)0x0) {
    lVar14 = *plVar21;
    lStack_f8 = lVar18;
    if ((*(byte *)(plVar21 + 2) & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar21[4]);
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar21);
    lVar18 = lStack_f8;
    plVar21 = (long *)lVar14;
  }
  lStack_f8 = 0;
  if (lVar18 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  if (((ulong)plStack_110 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_100);
  }
  plVar12 = (long *)*plVar12;
  if (plVar12 == (long *)0x0) goto code_r0x018fd8a4;
  goto code_r0x018fd608;
}

// ==== CSoundManager::IsPlaying(unsigned long) const
// vaddr 0x17fdc84 | ghidra 0x18fdc84 | size 8 | symbol _ZNK13CSoundManager9IsPlayingEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZNK13CSoundManager9IsPlayingEm(long param_1)

{
  (*(code *)PTR__ZNK9Framework13CSoundManager9IsPlayingEm_02ca8870)(param_1 + 0x18);
  return;
}

// ==== CSoundManager::Stop(unsigned long, std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)
// vaddr 0x17fdc8c | ghidra 0x18fdc8c | size 24 | symbol _ZN13CSoundManager4StopEmNSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager4StopEmNSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE
               (long param_1,long param_2)

{
  if (*(long *)(param_1 + 200) == param_2) {
    (*(code *)
      PTR__ZN13CSoundManager7StopBgmENSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE_02c9f780
    )();
    return;
  }
  (*(code *)PTR__ZN9Framework13CSoundManager4StopEmf_02cab2a0)(param_1 + 0x18);
  return;
}

// ==== CSoundManager::PlaySe(char const*, unsigned int)
// vaddr 0x17fdca4 | ghidra 0x18fdca4 | size 412 | symbol _ZN13CSoundManager6PlaySeEPKcj | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN13CSoundManager6PlaySeEPKcj(long param_1,long param_2,undefined4 param_3)

{
  long *plVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  undefined1 auStack_e0 [136];
  ulong auStack_58 [3];
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0x242,&UNK_0285ea95/*"apPackageName is null."*/);
  }
  plVar5 = *(long **)(param_1 + 0x118);
  while (plVar1 = plVar5, (long *)(param_1 + 0x110) != plVar1) {
    if ((*(byte *)(plVar1 + 2) & 1) == 0) {
      lVar4 = (long)plVar1 + 0x11;
    }
    else {
      lVar4 = plVar1[4];
    }
    uVar2 = CSoundManager::ResourceMapping(char const*)(param_1,lVar4);
    plVar5 = (long *)plVar1[1];
    if ((uVar2 & 1) != 0) {
      *(long **)(*plVar1 + 8) = plVar5;
      *(long *)plVar1[1] = *plVar1;
      *(long *)(param_1 + 0x120) = *(long *)(param_1 + 0x120) + -1;
      if ((*(byte *)(plVar1 + 2) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1[4]);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
    }
  }
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0x247,&UNK_027fd285/*"pParameterManager is null."*/);
  }
  lVar4 = CParameterManager::pParameterSound() const(lVar4);
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0x24a,&UNK_027fd2a0/*"pParameterSound is null."*/);
  }
  lVar4 = CParameterSound::pParameter(char const*, unsigned int) const(lVar4,param_2,param_3);
  if (lVar4 == 0) {
    uVar3 = 0;
  }
  else {
    auStack_58[1] = 0;
    auStack_58[2] = 0;
    auStack_58[0] = 0;
    void CParameterPropertyBase<31u>::CryptString<string >(string&, string const&)(auStack_58,lVar4 + 0x38);
    uVar2 = (ulong)auStack_58 | 1;
    if ((auStack_58[0] & 1) != 0) {
      uVar2 = auStack_58[2];
    }
    CSoundManager::GetPlaySettingDetail(CParameterSoundElement const*)(auStack_e0,lVar4);
    uVar3 = CSoundManager::PlaySe(char const*, CSoundManager::tPlaySetting const&)(param_1,uVar2,auStack_e0);
    if ((auStack_58[0] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_58[2]);
    }
  }
  return uVar3;
}

// ==== CSoundManager::PlaySe(char const*, unsigned int, CSoundManager::tPlaySetting const&)
// vaddr 0x17fde40 | ghidra 0x18fde40 | size 396 | symbol _ZN13CSoundManager6PlaySeEPKcjRKNS_12tPlaySettingE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN13CSoundManager6PlaySeEPKcjRKNS_12tPlaySettingE
          (long param_1,long param_2,undefined4 param_3,undefined8 param_4)

{
  long *plVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  ulong auStack_58 [3];
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0x25b,&UNK_0285ea95/*"apPackageName is null."*/);
  }
  plVar5 = *(long **)(param_1 + 0x118);
  while (plVar1 = plVar5, (long *)(param_1 + 0x110) != plVar1) {
    if ((*(byte *)(plVar1 + 2) & 1) == 0) {
      lVar4 = (long)plVar1 + 0x11;
    }
    else {
      lVar4 = plVar1[4];
    }
    uVar2 = CSoundManager::ResourceMapping(char const*)(param_1,lVar4);
    plVar5 = (long *)plVar1[1];
    if ((uVar2 & 1) != 0) {
      *(long **)(*plVar1 + 8) = plVar5;
      *(long *)plVar1[1] = *plVar1;
      *(long *)(param_1 + 0x120) = *(long *)(param_1 + 0x120) + -1;
      if ((*(byte *)(plVar1 + 2) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1[4]);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
    }
  }
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0x260,&UNK_027fd285/*"pParameterManager is null."*/);
  }
  lVar4 = CParameterManager::pParameterSound() const(lVar4);
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0x263,&UNK_027fd2a0/*"pParameterSound is null."*/);
  }
  lVar4 = CParameterSound::pParameter(char const*, unsigned int) const(lVar4,param_2,param_3);
  if (lVar4 == 0) {
    uVar3 = 0;
  }
  else {
    auStack_58[1] = 0;
    auStack_58[2] = 0;
    auStack_58[0] = 0;
    void CParameterPropertyBase<31u>::CryptString<string >(string&, string const&)(auStack_58,lVar4 + 0x38);
    uVar2 = (ulong)auStack_58 | 1;
    if ((auStack_58[0] & 1) != 0) {
      uVar2 = auStack_58[2];
    }
    uVar3 = CSoundManager::PlaySe(char const*, CSoundManager::tPlaySetting const&)(param_1,uVar2,param_4);
    if ((auStack_58[0] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_58[2]);
    }
  }
  return uVar3;
}

// ==== CSoundManager::PlayBgm(char const*, float, std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >, std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >, int)
// vaddr 0x17fdfcc | ghidra 0x18fdfcc | size 1932 | symbol _ZN13CSoundManager7PlayBgmEPKcfNSt6__ndk16chrono8durationIfNS2_5ratioILl1ELl1000EEEEES7_i | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN13CSoundManager7PlayBgmEPKcfNSt6__ndk16chrono8durationIfNS2_5ratioILl1ELl1000EEEEES7_i
          (float param_1,undefined4 param_2,undefined8 param_3,long param_4,long param_5,
          undefined4 param_6)

{
  byte bVar1;
  uint uVar2;
  undefined *puVar3;
  undefined1 uVar4;
  int iVar5;
  ulong uVar6;
  ulong uVar7;
  undefined4 *puVar8;
  undefined8 uVar9;
  long lVar10;
  undefined1 *puVar11;
  long lVar12;
  ulong *puVar13;
  ulong *puVar14;
  ulong uVar15;
  undefined4 *puVar16;
  undefined8 uStack_440;
  undefined8 uStack_438;
  undefined8 uStack_430;
  undefined8 uStack_428;
  undefined8 uStack_420;
  undefined8 uStack_418;
  ushort uStack_410;
  undefined4 uStack_40c;
  undefined1 uStack_408;
  undefined1 uStack_400;
  undefined8 uStack_3f0;
  undefined8 uStack_3e8;
  undefined8 uStack_3e0;
  undefined8 uStack_3d0;
  undefined1 auStack_3c0 [328];
  undefined4 uStack_278;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined2 uStack_f0;
  undefined4 uStack_ec;
  undefined1 uStack_e8;
  undefined1 uStack_e0;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b0;
  undefined8 uStack_98;
  ulong uStack_90;
  undefined4 *puStack_88;
  
  uVar6 = strlen(param_5);
  puVar13 = (ulong *)(param_4 + 0xd0);
  bVar1 = *(byte *)puVar13;
  uVar7 = (ulong)(bVar1 >> 1);
  if ((bVar1 & 1) != 0) {
    uVar7 = *(ulong *)(param_4 + 0xd8);
  }
  if (uVar6 == uVar7) {
    if (uVar6 == 0) {
code_r0x018fe118:
      return *(undefined8 *)(param_4 + 200);
    }
    lVar12 = *(long *)(param_4 + 0xe0);
    if ((bVar1 & 1) == 0) {
      lVar12 = param_4 + 0xd1;
    }
    iVar5 = memcmp(lVar12,param_5,uVar6);
    if (iVar5 == 0) goto code_r0x018fe118;
  }
  puVar3 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  lVar12 = *(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  if (lVar12 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar12 = *(long *)puVar3;
  }
  puStack_88 = (undefined4 *)0x0;
  uStack_90 = 0;
  puVar16 = (undefined4 *)((ulong)&uStack_98 | 1);
  uStack_98 = 0x2f646e756f530c;
  uVar7 = strlen(param_5);
  if (uVar7 < 0x11) {
    if (uVar7 != 0) {
      memcpy((ulong)&uStack_98 | 7,param_5,uVar7);
      uStack_98 = CONCAT71(uStack_98._1_7_,((char)uVar7 + '\x06') * '\x02');
      puVar11 = (undefined1 *)((long)&uStack_98 + uVar7 + 7);
      goto code_r0x018fe1ac;
    }
    uVar7 = 0xc;
code_r0x018fe1cc:
    lVar10 = 0x16;
  }
  else {
    uVar6 = uVar7 + 6;
    uVar15 = uVar6;
    if (uVar6 < 0x2d) {
      uVar15 = 0x2c;
    }
    if (uVar15 < 0x17) {
      uVar15 = 0x17;
    }
    else {
      uVar15 = uVar15 + 0x10 & 0xfffffffffffffff0;
      if (uVar15 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
    }
    puVar8 = (undefined4 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar15,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (puVar8 == (undefined4 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    *(undefined2 *)(puVar8 + 1) = *(undefined2 *)(puVar16 + 1);
    *puVar8 = *puVar16;
    memcpy((long)puVar8 + 6,param_5,uVar7);
    uStack_98 = uVar15 | 1;
    puVar11 = (undefined1 *)((long)puVar8 + uVar6);
    uStack_90 = uVar6;
    puStack_88 = puVar8;
code_r0x018fe1ac:
    *puVar11 = 0;
    uVar7 = uStack_98 & 0xff;
    if ((uStack_98 & 1) == 0) goto code_r0x018fe1cc;
    lVar10 = (uStack_98 & 0xfffffffffffffffe) - 1;
    uVar7 = uStack_98;
  }
  uVar6 = (ulong)(((uint)uVar7 & 0xfe) >> 1);
  if ((uVar7 & 1) != 0) {
    uVar6 = uStack_90;
  }
  if (lVar10 - uVar6 < 4) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_98,lVar10,(4 - lVar10) + uVar6,uVar6,uVar6,0,4,&UNK_028686c2/*".aac"*/);
  }
  else {
    puVar8 = puVar16;
    if ((uVar7 & 1) != 0) {
      puVar8 = puStack_88;
    }
    *(undefined4 *)((long)puVar8 + uVar6) = 0x6361612e;
    uVar6 = uVar6 + 4;
    uVar7 = uVar6;
    if ((uStack_98 & 1) == 0) {
      uStack_98 = CONCAT71(uStack_98._1_7_,(char)uVar6 * '\x02');
      uVar7 = uStack_90;
    }
    uStack_90 = uVar7;
    *(undefined1 *)((long)puVar8 + uVar6) = 0;
  }
  puVar8 = puVar16;
  if ((uStack_98 & 1) != 0) {
    puVar8 = puStack_88;
  }
  uVar7 = Framework::CFileLoader::gIsFileExist(char const*, char const*)(puVar8,0);
  if ((uVar7 & 1) == 0) {
    puVar8 = puVar16;
    if ((uStack_98 & 1) != 0) {
      puVar8 = puStack_88;
    }
    uVar7 = CGameResourceManager::IsFileExistDownloadFolder(char const*) const(lVar12,puVar8);
    if ((uVar7 & 1) == 0) {
      uVar9 = *(undefined8 *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
      goto joined_r0x018fe30c;
    }
    if ((*(byte *)(lVar12 + 0x58) & 1) == 0) {
      lVar12 = lVar12 + 0x59;
    }
    else {
      lVar12 = *(long *)(lVar12 + 0x68);
    }
    uVar7 = strlen(lVar12);
    puVar14 = (ulong *)(param_4 + 0xe8);
    uVar6 = (ulong)*(byte *)puVar14;
    if ((*(byte *)puVar14 & 1) == 0) {
      uVar15 = 0x16;
      lVar10 = uVar7 - 0x16;
      if (0x15 < uVar7 && lVar10 != 0) {
code_r0x018fe3d8:
        if ((uVar6 & 1) == 0) {
          uVar6 = (ulong)(((uint)uVar6 & 0xfe) >> 1);
        }
        else {
          uVar6 = *(ulong *)(param_4 + 0xf0);
        }
        goto code_r0x018fe414;
      }
    }
    else {
      uVar6 = *puVar14;
      uVar15 = (uVar6 & 0xfffffffffffffffe) - 1;
      lVar10 = uVar7 - uVar15;
      if (uVar15 <= uVar7 && lVar10 != 0) goto code_r0x018fe3d8;
    }
    if ((uVar6 & 1) == 0) {
      lVar10 = param_4 + 0xe9;
    }
    else {
      lVar10 = *(long *)(param_4 + 0xf8);
    }
    if (uVar7 != 0) {
      memmove(lVar10,lVar12,uVar7);
    }
    *(undefined1 *)(lVar10 + uVar7) = 0;
    uVar6 = (ulong)*(byte *)puVar14;
    if ((*(byte *)puVar14 & 1) == 0) {
      uVar2 = (int)uVar7 << 1;
      uVar6 = (ulong)uVar2;
      *(byte *)puVar14 = (byte)uVar2;
    }
    else {
      *(ulong *)(param_4 + 0xf0) = uVar7;
    }
  }
  else {
    lVar12 = Framework::CFileLoader::pDefaultDirectLoadFolder()();
    uVar7 = strlen();
    puVar14 = (ulong *)(param_4 + 0xe8);
    uVar6 = (ulong)*(byte *)puVar14;
    if ((*(byte *)puVar14 & 1) == 0) {
      uVar15 = 0x16;
      lVar10 = uVar7 - 0x16;
      if (0x15 < uVar7 && lVar10 != 0) {
code_r0x018fe2ec:
        if ((uVar6 & 1) == 0) {
          uVar6 = (ulong)(((uint)uVar6 & 0xfe) >> 1);
        }
        else {
          uVar6 = *(ulong *)(param_4 + 0xf0);
        }
code_r0x018fe414:
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)((byte *)(param_4 + 0xe8),uVar15,lVar10,uVar6,0,uVar6,uVar7,lVar12);
        uVar6 = (ulong)*(byte *)(param_4 + 0xe8);
        goto code_r0x018fe41c;
      }
    }
    else {
      uVar6 = *puVar14;
      uVar15 = (uVar6 & 0xfffffffffffffffe) - 1;
      lVar10 = uVar7 - uVar15;
      if (uVar15 <= uVar7 && lVar10 != 0) goto code_r0x018fe2ec;
    }
    if ((uVar6 & 1) == 0) {
      lVar10 = param_4 + 0xe9;
    }
    else {
      lVar10 = *(long *)(param_4 + 0xf8);
    }
    if (uVar7 != 0) {
      memmove(lVar10,lVar12,uVar7);
    }
    *(undefined1 *)(lVar10 + uVar7) = 0;
    uVar6 = (ulong)*(byte *)puVar14;
    if ((*(byte *)puVar14 & 1) == 0) {
      uVar2 = (int)uVar7 << 1;
      uVar6 = (ulong)uVar2;
      *(byte *)puVar14 = (byte)uVar2;
    }
    else {
      *(ulong *)(param_4 + 0xf0) = uVar7;
    }
  }
code_r0x018fe41c:
  puVar14 = (ulong *)(param_4 + 0xe8);
  uVar7 = uStack_98 >> 1 & 0x7f;
  if ((uStack_98 & 1) != 0) {
    uVar7 = uStack_90;
    puVar16 = puStack_88;
  }
  if ((uVar6 & 1) == 0) {
    lVar12 = 0x16;
    if ((uVar6 & 1) != 0) goto code_r0x018fe444;
code_r0x018fe45c:
    uVar15 = (ulong)(((uint)uVar6 & 0xfe) >> 1);
  }
  else {
    uVar6 = *puVar14;
    lVar12 = (uVar6 & 0xfffffffffffffffe) - 1;
    if ((uVar6 & 1) == 0) goto code_r0x018fe45c;
code_r0x018fe444:
    uVar15 = *(ulong *)(param_4 + 0xf0);
  }
  if (lVar12 - uVar15 < uVar7) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar14,lVar12,(uVar7 - lVar12) + uVar15,uVar15,uVar15,0,uVar7);
  }
  else if (uVar7 != 0) {
    if ((uVar6 & 1) == 0) {
      lVar12 = param_4 + 0xe9;
    }
    else {
      lVar12 = *(long *)(param_4 + 0xf8);
    }
    memcpy(lVar12 + uVar15,puVar16,uVar7);
    lVar10 = uVar15 + uVar7;
    if ((*(byte *)puVar14 & 1) == 0) {
      *(char *)puVar14 = (char)lVar10 * '\x02';
      *(undefined1 *)(lVar12 + lVar10) = 0;
    }
    else {
      *(long *)(param_4 + 0xf0) = lVar10;
      *(undefined1 *)(lVar12 + lVar10) = 0;
    }
  }
  uVar7 = strlen(param_5);
  uVar6 = (ulong)*(byte *)puVar13;
  if ((*(byte *)puVar13 & 1) == 0) {
    uVar15 = 0x16;
    lVar12 = uVar7 - 0x16;
    if (uVar7 < 0x16 || lVar12 == 0) goto code_r0x018fe4fc;
code_r0x018fe520:
    if ((uVar6 & 1) == 0) {
      uVar6 = (ulong)(((uint)uVar6 & 0xfe) >> 1);
    }
    else {
      uVar6 = *(ulong *)(param_4 + 0xd8);
    }
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar13,uVar15,lVar12,uVar6,0,uVar6,uVar7,param_5);
  }
  else {
    uVar6 = *puVar13;
    uVar15 = (uVar6 & 0xfffffffffffffffe) - 1;
    lVar12 = uVar7 - uVar15;
    if (uVar15 <= uVar7 && lVar12 != 0) goto code_r0x018fe520;
code_r0x018fe4fc:
    if ((uVar6 & 1) == 0) {
      lVar12 = param_4 + 0xd1;
    }
    else {
      lVar12 = *(long *)(param_4 + 0xe0);
    }
    if (uVar7 != 0) {
      memmove(lVar12,param_5,uVar7);
    }
    *(undefined1 *)(lVar12 + uVar7) = 0;
    if ((*(byte *)puVar13 & 1) == 0) {
      *(byte *)puVar13 = (byte)(uVar7 << 1);
    }
    else {
      *(ulong *)(param_4 + 0xd8) = uVar7;
    }
  }
  if (*(long *)(param_4 + 200) != *(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340) {
    Framework::CSoundManager::Stop(unsigned long, float)(param_3,param_4 + 0x18);
  }
  Framework::CSound::tArguments::tArguments()(&uStack_120);
  uStack_b0 = 1;
  if (param_5 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xe8,&UNK_028686b2/*"apName is null."*/);
  }
  lVar12 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar12 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xeb,&UNK_027fd285/*"pParameterManager is null."*/);
  }
  lVar12 = CParameterManager::pParameterSound() const(lVar12);
  if (lVar12 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0xee,&UNK_027fd2a0/*"pParameterSound is null."*/);
  }
  lVar12 = CParameterSound::pParameter(char const*) const(lVar12,param_5);
  if (lVar12 != 0) {
    CParameterSoundElement::CParameterSoundElement(CParameterSoundElement const&)(auStack_3c0,lVar12);
    uStack_278 = param_2;
    CSoundManager::GetPlaySettingDetail(CParameterSoundElement const*)(&uStack_440,auStack_3c0);
    uStack_f0 = uStack_410;
    uStack_108 = uStack_428;
    uStack_110 = uStack_430;
    uStack_f8 = uStack_418;
    uStack_100 = uStack_420;
    uStack_ec = uStack_40c;
    uStack_118 = uStack_438;
    uStack_120 = uStack_440;
    uStack_e8 = uStack_408;
    uStack_e0 = uStack_400;
    uStack_c8 = uStack_3e8;
    uStack_d0 = uStack_3f0;
    uStack_c0 = uStack_3e0;
    uStack_b0 = uStack_3d0;
    CParameterSoundElement::~CParameterSoundElement()(auStack_3c0);
  }
  *(float *)(param_4 + 0x104) = param_1;
  *(float *)(param_4 + 0x100) = (float)uStack_110;
  uStack_110 = CONCAT44(uStack_110._4_4_,
                        (float)uStack_110 * param_1 * *(float *)(param_4 + 0x108) *
                        *(float *)(param_4 + 8));
  uStack_100 = CONCAT44(param_6,(undefined4)uStack_100);
  if ((*(byte *)(param_4 + 0xe8) & 1) == 0) {
    lVar12 = param_4 + 0xe9;
  }
  else {
    lVar12 = *(long *)(param_4 + 0xf8);
  }
  uVar4 = Framework::CFileLoader::IsAssetManagerPath(char const*)(lVar12);
  uStack_f0 = CONCAT11(uStack_f0._1_1_,uVar4) & 0xff01;
  if ((*(byte *)(param_4 + 0xe8) & 1) == 0) {
    lVar12 = param_4 + 0xe9;
  }
  else {
    lVar12 = *(long *)(param_4 + 0xf8);
  }
  uVar9 = Framework::CSoundManager::PlayBGM(char const*, Framework::CSound::tArguments const&)(param_4 + 0x18,lVar12,&uStack_120);
  *(undefined8 *)(param_4 + 200) = uVar9;
joined_r0x018fe30c:
  if ((uStack_98 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_88);
  }
  return uVar9;
}

// ==== CSoundManager::IsPlayingBGM(char const*) const
// vaddr 0x17fe758 | ghidra 0x18fe758 | size 140 | symbol _ZNK13CSoundManager12IsPlayingBGMEPKc | lib libSOA-3.7.0.so | 2026-10-08
bool _ZNK13CSoundManager12IsPlayingBGMEPKc(long param_1,undefined8 param_2)

{
  byte bVar1;
  int iVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  
  uVar3 = Framework::CSoundManager::IsPlaying(unsigned long) const(param_1 + 0x18,*(undefined8 *)(param_1 + 200));
  if ((uVar3 & 1) == 0) {
    return false;
  }
  uVar4 = strlen(param_2);
  bVar1 = *(byte *)(param_1 + 0xd0);
  uVar3 = (ulong)(bVar1 >> 1);
  if ((bVar1 & 1) != 0) {
    uVar3 = *(ulong *)(param_1 + 0xd8);
  }
  if (uVar4 != uVar3) {
    return false;
  }
  if (uVar4 != 0) {
    lVar5 = *(long *)(param_1 + 0xe0);
    if ((bVar1 & 1) == 0) {
      lVar5 = param_1 + 0xd1;
    }
    iVar2 = memcmp(lVar5,param_2,uVar4);
    if (iVar2 != 0) goto code_r0x018fe7c8;
  }
  iVar2 = 0;
code_r0x018fe7c8:
  return iVar2 == 0;
}

// ==== CSoundManager::GetBgmFileName() const
// vaddr 0x17fe7e4 | ghidra 0x18fe7e4 | size 8 | symbol _ZNK13CSoundManager14GetBgmFileNameEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK13CSoundManager14GetBgmFileNameEv(long param_1)

{
  return param_1 + 0xd0;
}

// ==== CSoundManager::UpdateVolumeBGM(float)
// vaddr 0x17fe7ec | ghidra 0x18fe7ec | size 168 | symbol _ZN13CSoundManager15UpdateVolumeBGMEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager15UpdateVolumeBGMEf(float param_1,long param_2)

{
  long lVar1;
  code *pcVar2;
  undefined *puStack_40;
  float fStack_38;
  undefined4 uStack_34;
  long *plStack_20;
  
  if (*(float *)(param_2 + 8) != param_1) {
    lVar1 = *(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340;
    *(float *)(param_2 + 8) = param_1;
    if (*(long *)(param_2 + 200) != lVar1) {
      plStack_20 = (long *)&puStack_40;
      fStack_38 = *(float *)(param_2 + 0x104) * *(float *)(param_2 + 0x100) *
                  *(float *)(param_2 + 0x108) * param_1;
      puStack_40 = &UNK_02b11268;
      uStack_34 = 0;
      Framework::CSoundManager::Element(unsigned long, std::__ndk1::function<void (Framework::CSound::CElement&)>)(param_2 + 0x18,*(long *)(param_2 + 200),&puStack_40);
      if (&puStack_40 == (undefined **)plStack_20) {
        pcVar2 = *(code **)(*plStack_20 + 0x20);
      }
      else {
        if (plStack_20 == (long *)0x0) {
          return;
        }
        pcVar2 = *(code **)(*plStack_20 + 0x28);
      }
      (*pcVar2)();
    }
  }
  return;
}

// ==== CSoundManager::BgmVolume(float, std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)
// vaddr 0x17fe894 | ghidra 0x18fe894 | size 152 | symbol _ZN13CSoundManager9BgmVolumeEfNSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager9BgmVolumeEfNSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE
               (float param_1,undefined4 param_2,long param_3)

{
  code *pcVar1;
  undefined *puStack_40;
  float fStack_38;
  undefined4 uStack_34;
  long *plStack_20;
  
  if (*(long *)(param_3 + 200) != *(long *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340) {
    plStack_20 = (long *)&puStack_40;
    *(float *)(param_3 + 0x104) = param_1;
    fStack_38 = *(float *)(param_3 + 0x100) * param_1 * *(float *)(param_3 + 0x108) *
                *(float *)(param_3 + 8);
    puStack_40 = &UNK_02b11268;
    uStack_34 = param_2;
    Framework::CSoundManager::Element(unsigned long, std::__ndk1::function<void (Framework::CSound::CElement&)>)(param_3 + 0x18,*(long *)(param_3 + 200),&puStack_40);
    if (&puStack_40 == (undefined **)plStack_20) {
      pcVar1 = *(code **)(*plStack_20 + 0x20);
    }
    else {
      if (plStack_20 == (long *)0x0) {
        return;
      }
      pcVar1 = *(code **)(*plStack_20 + 0x28);
    }
    (*pcVar1)();
  }
  return;
}

// ==== CSoundManager::UpdateVolumeSE(float)
// vaddr 0x17fe92c | ghidra 0x18fe92c | size 8 | symbol _ZN13CSoundManager14UpdateVolumeSEEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager14UpdateVolumeSEEf(undefined4 param_1,long param_2)

{
  *(undefined4 *)(param_2 + 0x10) = param_1;
  return;
}

// ==== CSoundManager::UpdateVolumeVoice(float)
// vaddr 0x17fe934 | ghidra 0x18fe934 | size 8 | symbol _ZN13CSoundManager17UpdateVolumeVoiceEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager17UpdateVolumeVoiceEf(undefined4 param_1,long param_2)

{
  *(undefined4 *)(param_2 + 0xc) = param_1;
  return;
}

// ==== CSoundManager::StopBgm(std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)
// vaddr 0x17fe93c | ghidra 0x18fe93c | size 304 | symbol _ZN13CSoundManager7StopBgmENSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager7StopBgmENSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE(long param_1)

{
  byte bVar1;
  bool bVar2;
  byte *pbVar3;
  undefined1 *puVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  long lVar8;
  ulong *puVar9;
  long lVar10;
  
  Framework::CSoundManager::Stop(unsigned long, float)(param_1 + 0x18,*(undefined8 *)(param_1 + 200));
  pbVar3 = (byte *)(param_1 + 0xe8);
  bVar1 = *pbVar3;
  if ((bVar1 & 1) != 0) {
    bVar1 = *pbVar3;
  }
  if ((bVar1 & 1) == 0) {
    puVar4 = (undefined1 *)(param_1 + 0xe9);
  }
  else {
    puVar4 = *(undefined1 **)(param_1 + 0xf8);
  }
  *puVar4 = 0;
  uVar6 = (ulong)*pbVar3;
  if ((*pbVar3 & 1) == 0) {
    uVar7 = *(ulong *)(param_1 + 0xf0);
    uVar6 = 0;
    *(undefined1 *)(param_1 + 0xe8) = 0;
  }
  else {
    uVar7 = 0;
    *(undefined8 *)(param_1 + 0xf0) = 0;
  }
  puVar9 = (ulong *)(param_1 + 0xd0);
  uVar5 = (ulong)*(byte *)puVar9;
  bVar2 = (uVar6 & 1) != 0;
  uVar6 = uVar6 >> 1;
  if (bVar2) {
    uVar6 = uVar7;
  }
  lVar8 = *(long *)(param_1 + 0xf8);
  if (!bVar2) {
    lVar8 = param_1 + 0xe9;
  }
  if ((*(byte *)puVar9 & 1) == 0) {
    uVar7 = 0x16;
    lVar10 = uVar6 - 0x16;
    if (0x15 < uVar6 && lVar10 != 0) {
code_r0x018fe9ec:
      if ((uVar5 & 1) == 0) {
        uVar5 = (ulong)(((uint)uVar5 & 0xfe) >> 1);
      }
      else {
        uVar5 = *(ulong *)(param_1 + 0xd8);
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar9,uVar7,lVar10,uVar5,0,uVar5,uVar6);
      goto code_r0x018fea4c;
    }
  }
  else {
    uVar5 = *puVar9;
    uVar7 = (uVar5 & 0xfffffffffffffffe) - 1;
    lVar10 = uVar6 - uVar7;
    if (uVar7 <= uVar6 && lVar10 != 0) goto code_r0x018fe9ec;
  }
  if ((uVar5 & 1) == 0) {
    lVar10 = param_1 + 0xd1;
  }
  else {
    lVar10 = *(long *)(param_1 + 0xe0);
  }
  if (uVar6 != 0) {
    memmove(lVar10,lVar8,uVar6);
  }
  *(undefined1 *)(lVar10 + uVar6) = 0;
  if ((*(byte *)puVar9 & 1) == 0) {
    *(byte *)puVar9 = (byte)(uVar6 << 1);
  }
  else {
    *(ulong *)(param_1 + 0xd8) = uVar6;
  }
code_r0x018fea4c:
  *(undefined8 *)(param_1 + 200) = *(undefined8 *)PTR__ZN9Framework6CSound14iInvalidHandleE_02cc4340
  ;
  return;
}

// ==== CSoundManager::Pause(unsigned long, std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)
// vaddr 0x17fea6c | ghidra 0x18fea6c | size 8 | symbol _ZN13CSoundManager5PauseEmNSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager5PauseEmNSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE(long param_1)

{
  (*(code *)PTR__ZN9Framework13CSoundManager5PauseEmf_02c98ec0)(param_1 + 0x18);
  return;
}

// ==== CSoundManager::Resume(unsigned long, std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)
// vaddr 0x17fea74 | ghidra 0x18fea74 | size 8 | symbol _ZN13CSoundManager6ResumeEmNSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager6ResumeEmNSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE(long param_1)

{
  (*(code *)PTR__ZN9Framework13CSoundManager6ResumeEmf_02c9ab70)(param_1 + 0x18);
  return;
}

// ==== CSoundManager::PauseAll(std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)
// vaddr 0x17fea7c | ghidra 0x18fea7c | size 8 | symbol _ZN13CSoundManager8PauseAllENSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager8PauseAllENSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE
               (long param_1)

{
  (*(code *)PTR__ZN9Framework13CSoundManager8PauseAllEf_02c8e5b8)(param_1 + 0x18);
  return;
}

// ==== CSoundManager::ResumeAll(std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)
// vaddr 0x17fea84 | ghidra 0x18fea84 | size 8 | symbol _ZN13CSoundManager9ResumeAllENSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager9ResumeAllENSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE
               (long param_1)

{
  (*(code *)PTR__ZN9Framework13CSoundManager9ResumeAllEf_02c8fad0)(param_1 + 0x18);
  return;
}

// ==== CSoundManager::Watchdog(unsigned long)
// vaddr 0x17fea8c | ghidra 0x18fea8c | size 8 | symbol _ZN13CSoundManager8WatchdogEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager8WatchdogEm(long param_1)

{
  (*(code *)PTR__ZN9Framework13CSoundManager8WatchdogEm_02ca6ad0)(param_1 + 0x18);
  return;
}

// ==== CSoundManager::Volume(unsigned long, float, std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)
// vaddr 0x17fea94 | ghidra 0x18fea94 | size 100 | symbol _ZN13CSoundManager6VolumeEmfNSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager6VolumeEmfNSt6__ndk16chrono8durationIfNS0_5ratioILl1ELl1000EEEEE
               (undefined4 param_1,undefined4 param_2,long param_3,undefined8 param_4)

{
  code *pcVar1;
  undefined *puStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  long *plStack_20;
  
  plStack_20 = (long *)&puStack_40;
  puStack_40 = &UNK_02b11268;
  uStack_38 = param_1;
  uStack_34 = param_2;
  Framework::CSoundManager::Element(unsigned long, std::__ndk1::function<void (Framework::CSound::CElement&)>)(param_3 + 0x18,param_4,&puStack_40);
  if (&puStack_40 == (undefined **)plStack_20) {
    pcVar1 = *(code **)(*plStack_20 + 0x20);
  }
  else {
    if (plStack_20 == (long *)0x0) {
      return;
    }
    pcVar1 = *(code **)(*plStack_20 + 0x28);
  }
  (*pcVar1)();
  return;
}

// ==== CSoundManager::IsResourceExist(char const*, unsigned int)
// vaddr 0x17feaf8 | ghidra 0x18feaf8 | size 1076 | symbol _ZN13CSoundManager15IsResourceExistEPKcj | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN13CSoundManager15IsResourceExistEPKcj(long param_1,long param_2,undefined4 param_3)

{
  int iVar1;
  long *plVar2;
  bool bVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  long *plVar10;
  ulong uStack_c0;
  ulong uStack_b8;
  ulong uStack_b0;
  long alStack_a8 [2];
  long *plStack_98;
  ulong uStack_78;
  ulong uStack_70;
  ulong uStack_68;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0x333,&UNK_0285ea95/*"apPackageName is null."*/);
  }
  lVar8 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar8 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0x336,&UNK_027fd285/*"pParameterManager is null."*/);
  }
  lVar8 = CParameterManager::pParameterSound() const(lVar8);
  if (lVar8 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0x339,&UNK_027fd2a0/*"pParameterSound is null."*/);
  }
  lVar8 = CParameterSound::pParameter(char const*, unsigned int) const(lVar8,param_2,param_3);
  if (lVar8 == 0) {
    return false;
  }
  uStack_b8 = 0;
  uStack_b0 = 0;
  uStack_c0 = 0;
  void CParameterPropertyBase<31u>::CryptString<string >(string&, string const&)(&uStack_c0,lVar8 + 0x38);
  uStack_70 = 0;
  uStack_68 = 0;
  uVar7 = (ulong)&uStack_c0 | 1;
  if ((uStack_c0 & 1) != 0) {
    uVar7 = uStack_b0;
  }
  uStack_78 = 0;
  uVar4 = strlen(uVar7);
  if (uVar4 < 0x17) {
    uVar9 = (ulong)&uStack_78 | 1;
    uStack_78 = CONCAT71(uStack_78._1_7_,(char)(uVar4 << 1));
    if (uVar4 == 0) goto code_r0x018fec7c;
  }
  else {
    uVar5 = uVar4 + 0x10 & 0xfffffffffffffff0;
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar9 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar9 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_78 = uVar5 | 1;
    uStack_70 = uVar4;
    uStack_68 = uVar9;
  }
  memcpy(uVar9,uVar7,uVar4);
code_r0x018fec7c:
  *(undefined1 *)(uVar9 + uVar4) = 0;
  if ((uStack_c0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_b0);
  }
  if ((uStack_78 & 1) == 0) {
    lVar8 = 0x16;
    uVar7 = uStack_78 & 0xff;
  }
  else {
    lVar8 = (uStack_78 & 0xfffffffffffffffe) - 1;
    uVar7 = uStack_78;
  }
  uVar4 = (ulong)(((uint)uVar7 & 0xfe) >> 1);
  if ((uVar7 & 1) != 0) {
    uVar4 = uStack_70;
  }
  if (lVar8 - uVar4 < 4) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_78,lVar8,(4 - lVar8) + uVar4,uVar4,uVar4,0,4,&UNK_028686c2/*".aac"*/);
    plVar10 = *(long **)(param_1 + 0xb0);
  }
  else {
    uVar5 = (ulong)&uStack_78 | 1;
    if ((uVar7 & 1) != 0) {
      uVar5 = uStack_68;
    }
    *(undefined4 *)(uVar5 + uVar4) = 0x6361612e;
    uVar4 = uVar4 + 4;
    uVar7 = uVar4;
    if ((uStack_78 & 1) == 0) {
      uStack_78 = CONCAT71(uStack_78._1_7_,(char)uVar4 * '\x02');
      uVar7 = uStack_70;
    }
    uStack_70 = uVar7;
    *(undefined1 *)(uVar5 + uVar4) = 0;
    plVar10 = *(long **)(param_1 + 0xb0);
  }
  if (plVar10 == (long *)0x0) {
code_r0x018fee90:
    bVar3 = false;
    if ((uStack_78 & 1) != 0) {
code_r0x018fee9c:
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
    }
    return bVar3;
  }
code_r0x018fed74:
  uStack_b8 = 0;
  uStack_b0 = 0;
  uStack_c0 = 0;
  if ((plVar10[2] & 1U) == 0) {
    uStack_b0 = plVar10[4];
    uStack_b8 = plVar10[3];
    uStack_c0 = plVar10[2];
  }
  else {
    uVar7 = plVar10[3];
    lVar8 = plVar10[4];
    if (uVar7 < 0x17) {
      uStack_c0 = (uVar7 & 0x7f) << 1;
      uVar5 = (ulong)&uStack_c0 | 1;
      if (uVar7 != 0) goto code_r0x018fee0c;
    }
    else {
      uVar4 = uVar7 + 0x10 & 0xfffffffffffffff0;
      if (uVar4 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar4,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar5 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      uStack_c0 = uVar4 | 1;
      uStack_b8 = uVar7;
      uStack_b0 = uVar5;
code_r0x018fee0c:
      memcpy(uVar5,lVar8,uVar7);
    }
    *(undefined1 *)(uVar5 + uVar7) = 0;
  }
  std::__ndk1::unordered_map<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string >, Framework::CSTLAllocator<std::__ndk1::pair<string const, CSoundManager::tSoundImage>, Framework::CSTLUnorderedMapAllocatorInf> >::unordered_map(std::__ndk1::unordered_map<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string >, Framework::CSTLAllocator<std::__ndk1::pair<string const, CSoundManager::tSoundImage>, Framework::CSTLUnorderedMapAllocatorInf> > const&)(alStack_a8,plVar10 + 5);
  lVar6 = std::__ndk1::__hash_const_iterator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, void*>*> std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, Framework::CSTLUnorderedMapAllocatorInf> >::find<string >(string const&) const(alStack_a8,&uStack_78);
  plVar2 = plStack_98;
  lVar8 = alStack_a8[0];
  if (lVar6 == 0) goto joined_r0x018fee64;
  iVar1 = *(int *)(lVar6 + 0x38);
  plVar10 = plStack_98;
  while (plVar10 != (long *)0x0) {
    lVar6 = *plVar10;
    alStack_a8[0] = lVar8;
    if ((*(byte *)(plVar10 + 2) & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar10[4]);
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar10);
    lVar8 = alStack_a8[0];
    plVar10 = (long *)lVar6;
  }
  alStack_a8[0] = 0;
  if (lVar8 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  if ((uStack_c0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_b0);
  }
  bVar3 = iVar1 != 0;
  if ((uStack_78 & 1) == 0) {
    return bVar3;
  }
  goto code_r0x018fee9c;
joined_r0x018fee64:
  while (plVar2 != (long *)0x0) {
    lVar6 = *plVar2;
    alStack_a8[0] = lVar8;
    if ((*(byte *)(plVar2 + 2) & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar2[4]);
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar2);
    plVar2 = (long *)lVar6;
    lVar8 = alStack_a8[0];
  }
  alStack_a8[0] = 0;
  if (lVar8 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  if ((uStack_c0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_b0);
  }
  plVar10 = (long *)*plVar10;
  if (plVar10 == (long *)0x0) goto code_r0x018fee90;
  goto code_r0x018fed74;
}

// ==== CSoundManager::IsResourceExist(char const*)
// vaddr 0x17fef2c | ghidra 0x18fef2c | size 148 | symbol _ZN13CSoundManager15IsResourceExistEPKc | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN13CSoundManager15IsResourceExistEPKc(undefined8 param_1,undefined8 param_2)

{
  ulong uVar1;
  undefined *puVar2;
  uint uVar3;
  long lVar4;
  byte abStack_38 [16];
  ulong uStack_28;
  
  puVar2 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar2;
  }
  CSoundManager::MakeSoundResourcePath(char const*)(abStack_38,param_2);
  uVar1 = (ulong)abStack_38 | 1;
  if ((abStack_38[0] & 1) != 0) {
    uVar1 = uStack_28;
  }
  uVar3 = CGameResourceManager::IsFileExist(char const*, bool) const(lVar4,uVar1,1);
  if ((abStack_38[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
  }
  return uVar3 & 1;
}

// ==== CSoundManager::MakeSoundResourcePath(char const*)
// vaddr 0x17fefc0 | ghidra 0x18fefc0 | size 408 | symbol _ZN13CSoundManager21MakeSoundResourcePathEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager21MakeSoundResourcePathEPKc(ulong *param_1,undefined8 param_2)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  ulong uVar5;
  ulong uStack_68;
  ulong uStack_60;
  ulong uStack_58;
  ulong uStack_50;
  ulong uStack_48;
  ulong uStack_40;
  
  uStack_60 = 0;
  uStack_58 = 0;
  uStack_68 = 0x2f646e756f530c;
  uVar3 = strlen();
  if (uVar3 < 0x10 || uVar3 - 0x10 == 0) {
    if (uVar3 != 0) {
      memcpy((ulong)&uStack_68 | 7,param_2,uVar3);
      uStack_68 = CONCAT71(uStack_68._1_7_,(char)(uVar3 + 6) * '\x02');
      *(undefined1 *)(((ulong)&uStack_68 | 1) + uVar3 + 6) = 0;
    }
  }
  else {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_68,0x16,uVar3 - 0x10,6,6,0,uVar3,param_2);
  }
  uStack_40 = uStack_58;
  uStack_48 = uStack_60;
  uVar3 = uStack_68;
  uStack_60 = 0;
  uStack_58 = 0;
  uStack_68 = 0;
  uStack_50 = uVar3;
  if ((uVar3 & 1) == 0) {
    lVar4 = 0x16;
    uVar5 = uVar3 & 0xff;
  }
  else {
    lVar4 = (uVar3 & 0xfffffffffffffffe) - 1;
    uVar5 = uVar3;
  }
  uVar1 = (ulong)(((uint)uVar5 & 0xfe) >> 1);
  if ((uVar5 & 1) != 0) {
    uVar1 = uStack_48;
  }
  if (lVar4 - uVar1 < 4) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_50,lVar4,(4 - lVar4) + uVar1,uVar1,uVar1,0,4,&UNK_028681fa/*".spk"*/);
  }
  else {
    uVar2 = (ulong)&uStack_50 | 1;
    if ((uVar5 & 1) != 0) {
      uVar2 = uStack_40;
    }
    *(undefined4 *)(uVar2 + uVar1) = 0x6b70732e;
    uVar1 = uVar1 + 4;
    uVar5 = uVar1;
    if ((uVar3 & 1) == 0) {
      uStack_50 = CONCAT71((int7)(uVar3 >> 8),(char)uVar1 * '\x02');
      uVar5 = uStack_48;
    }
    uStack_48 = uVar5;
    *(undefined1 *)(uVar2 + uVar1) = 0;
  }
  uVar1 = uStack_40;
  uVar5 = uStack_48;
  uVar3 = uStack_50;
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_40 = 0;
  param_1[2] = uVar1;
  param_1[1] = uVar5;
  *param_1 = uVar3;
  if ((uStack_68 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_58);
  }
  return;
}

// ==== CSoundManager::IsBgmExist(char const*)
// vaddr 0x17ff158 | ghidra 0x18ff158 | size 148 | symbol _ZN13CSoundManager10IsBgmExistEPKc | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN13CSoundManager10IsBgmExistEPKc(undefined8 param_1,undefined8 param_2)

{
  ulong uVar1;
  undefined *puVar2;
  uint uVar3;
  long lVar4;
  byte abStack_38 [16];
  ulong uStack_28;
  
  puVar2 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar2;
  }
  CSoundManager::MakeBgmResourcePath(char const*)(abStack_38,param_2);
  uVar1 = (ulong)abStack_38 | 1;
  if ((abStack_38[0] & 1) != 0) {
    uVar1 = uStack_28;
  }
  uVar3 = CGameResourceManager::IsFileExist(char const*, bool) const(lVar4,uVar1,1);
  if ((abStack_38[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
  }
  return uVar3 & 1;
}

// ==== CSoundManager::MakeBgmResourcePath(char const*)
// vaddr 0x17ff1ec | ghidra 0x18ff1ec | size 408 | symbol _ZN13CSoundManager19MakeBgmResourcePathEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager19MakeBgmResourcePathEPKc(ulong *param_1,undefined8 param_2)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  ulong uVar5;
  ulong uStack_68;
  ulong uStack_60;
  ulong uStack_58;
  ulong uStack_50;
  ulong uStack_48;
  ulong uStack_40;
  
  uStack_60 = 0;
  uStack_58 = 0;
  uStack_68 = 0x2f646e756f530c;
  uVar3 = strlen();
  if (uVar3 < 0x10 || uVar3 - 0x10 == 0) {
    if (uVar3 != 0) {
      memcpy((ulong)&uStack_68 | 7,param_2,uVar3);
      uStack_68 = CONCAT71(uStack_68._1_7_,(char)(uVar3 + 6) * '\x02');
      *(undefined1 *)(((ulong)&uStack_68 | 1) + uVar3 + 6) = 0;
    }
  }
  else {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_68,0x16,uVar3 - 0x10,6,6,0,uVar3,param_2);
  }
  uStack_40 = uStack_58;
  uStack_48 = uStack_60;
  uVar3 = uStack_68;
  uStack_60 = 0;
  uStack_58 = 0;
  uStack_68 = 0;
  uStack_50 = uVar3;
  if ((uVar3 & 1) == 0) {
    lVar4 = 0x16;
    uVar5 = uVar3 & 0xff;
  }
  else {
    lVar4 = (uVar3 & 0xfffffffffffffffe) - 1;
    uVar5 = uVar3;
  }
  uVar1 = (ulong)(((uint)uVar5 & 0xfe) >> 1);
  if ((uVar5 & 1) != 0) {
    uVar1 = uStack_48;
  }
  if (lVar4 - uVar1 < 4) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_50,lVar4,(4 - lVar4) + uVar1,uVar1,uVar1,0,4,&UNK_028686c2/*".aac"*/);
  }
  else {
    uVar2 = (ulong)&uStack_50 | 1;
    if ((uVar5 & 1) != 0) {
      uVar2 = uStack_40;
    }
    *(undefined4 *)(uVar2 + uVar1) = 0x6361612e;
    uVar1 = uVar1 + 4;
    uVar5 = uVar1;
    if ((uVar3 & 1) == 0) {
      uStack_50 = CONCAT71((int7)(uVar3 >> 8),(char)uVar1 * '\x02');
      uVar5 = uStack_48;
    }
    uStack_48 = uVar5;
    *(undefined1 *)(uVar2 + uVar1) = 0;
  }
  uVar1 = uStack_40;
  uVar5 = uStack_48;
  uVar3 = uStack_50;
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_40 = 0;
  param_1[2] = uVar1;
  param_1[1] = uVar5;
  *param_1 = uVar3;
  if ((uStack_68 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_58);
  }
  return;
}

// ==== CSoundManager::AddResource(char const*, bool)
// vaddr 0x17ff384 | ghidra 0x18ff384 | size 420 | symbol _ZN13CSoundManager11AddResourceEPKcb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager11AddResourceEPKcb(long param_1,undefined8 param_2,uint param_3)

{
  long *plVar1;
  undefined *puVar2;
  ulong uVar3;
  long lVar4;
  long *plVar5;
  byte abStack_58 [16];
  ulong uStack_48;
  undefined8 uStack_38;
  
  puVar2 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  uStack_38 = param_2;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar2;
  }
  CSoundManager::MakeSoundResourcePath(char const*)(abStack_58,param_2);
  uVar3 = (ulong)abStack_58 | 1;
  if ((abStack_58[0] & 1) != 0) {
    uVar3 = uStack_48;
  }
  uVar3 = CGameResourceManager::IsFileExist(char const*, bool) const(lVar4,uVar3,1);
  if ((abStack_58[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  if ((uVar3 & 1) != 0) {
    lVar4 = *(long *)puVar2;
    if (lVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar4 = *(long *)puVar2;
    }
    CSoundManager::MakeSoundResourcePath(char const*)(abStack_58,uStack_38);
    uVar3 = (ulong)abStack_58 | 1;
    if ((abStack_58[0] & 1) != 0) {
      uVar3 = uStack_48;
    }
    CGameResourceManager::AddDirectFile(unsigned int, char const*, unsigned int, bool, CGameResourceManager::iPriorityMode)(lVar4,0xc,uVar3,0,param_3 & 1,0);
    void std::__ndk1::list<string, Framework::CSTLAllocator<string, Framework::CSTLListAllocatorInf> >::emplace_back<char const*&>(char const*&)((long *)(param_1 + 0x110),&uStack_38);
    plVar5 = *(long **)(param_1 + 0x118);
    while (plVar1 = plVar5, (long *)(param_1 + 0x110) != plVar1) {
      if ((*(byte *)(plVar1 + 2) & 1) == 0) {
        lVar4 = (long)plVar1 + 0x11;
      }
      else {
        lVar4 = plVar1[4];
      }
      uVar3 = CSoundManager::ResourceMapping(char const*)(param_1,lVar4);
      plVar5 = (long *)plVar1[1];
      if ((uVar3 & 1) != 0) {
        *(long **)(*plVar1 + 8) = plVar5;
        *(long *)plVar1[1] = *plVar1;
        *(long *)(param_1 + 0x120) = *(long *)(param_1 + 0x120) + -1;
        if ((*(byte *)(plVar1 + 2) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1[4]);
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar1);
      }
    }
    if ((abStack_58[0] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
    }
  }
  return;
}

// ==== CSoundManager::GetResourceFileList(char const*, Framework::CSTLVector<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >*)
// vaddr 0x17ff654 | ghidra 0x18ff654 | size 500 | symbol _ZN13CSoundManager19GetResourceFileListEPKcPN9Framework10CSTLVectorINSt6__ndk112basic_stringIcNS4_11char_traitsIcEENS2_13CSTLAllocatorIcNS2_22CSTLStringAllocatorInfEEEEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager19GetResourceFileListEPKcPN9Framework10CSTLVectorINSt6__ndk112basic_stringIcNS4_11char_traitsIcEENS2_13CSTLAllocatorIcNS2_22CSTLStringAllocatorInfEEEEEEE
               (undefined8 param_1,undefined8 param_2,long param_3)

{
  ulong *puVar1;
  undefined *puVar2;
  ulong uVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  byte bStack_58;
  undefined7 uStack_57;
  ulong uStack_50;
  ulong uStack_48;
  
  puVar2 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar2;
  }
  CSoundManager::MakeSoundResourcePath(char const*)(&bStack_58,param_2);
  uVar3 = (ulong)&bStack_58 | 1;
  if ((bStack_58 & 1) != 0) {
    uVar3 = uStack_48;
  }
  uVar3 = CGameResourceManager::IsFileExist(char const*, bool) const(lVar4,uVar3,1);
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  if ((uVar3 & 1) == 0) {
    return;
  }
  if (*(long *)puVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
  }
  CSoundManager::MakeSoundResourcePath(char const*)(&bStack_58,param_2);
  if (param_3 == 0) goto joined_r0x018ff770;
  puVar1 = *(ulong **)(param_3 + 8);
  if (puVar1 == *(ulong **)(param_3 + 0x10)) {
    void std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<string const&>(string const&)(param_3,&bStack_58);
    goto joined_r0x018ff770;
  }
  if (puVar1 == (ulong *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  uVar3 = uStack_48;
  puVar1[1] = 0;
  puVar1[2] = 0;
  *puVar1 = 0;
  if ((bStack_58 & 1) == 0) {
    puVar1[2] = uStack_48;
    puVar1[1] = uStack_50;
    *puVar1 = CONCAT71(uStack_57,bStack_58);
  }
  else {
    if (uStack_50 < 0x17) {
      uVar6 = (long)puVar1 + 1;
      *(char *)puVar1 = (char)(uStack_50 << 1);
      if (uStack_50 != 0) goto code_r0x018ff81c;
    }
    else {
      uVar5 = uStack_50 + 0x10 & 0xfffffffffffffff0;
      if (uVar5 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar6 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      puVar1[1] = uStack_50;
      puVar1[2] = uVar6;
      *puVar1 = uVar5 | 1;
code_r0x018ff81c:
      memcpy(uVar6,uVar3,uStack_50);
    }
    *(undefined1 *)(uVar6 + uStack_50) = 0;
  }
  *(long *)(param_3 + 8) = *(long *)(param_3 + 8) + 0x18;
joined_r0x018ff770:
  if ((bStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  return;
}

// ==== CSoundManager::RemoveResource(char const*)
// vaddr 0x17ff848 | ghidra 0x18ff848 | size 580 | symbol _ZN13CSoundManager14RemoveResourceEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager14RemoveResourceEPKc(long param_1,undefined8 param_2)

{
  undefined *puVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uStack_60;
  ulong uStack_58;
  ulong uStack_50;
  byte abStack_48 [16];
  ulong uStack_38;
  
  puVar1 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  CSoundManager::MakeSoundResourcePath(char const*)(abStack_48,param_2);
  uVar2 = (ulong)abStack_48 | 1;
  if ((abStack_48[0] & 1) != 0) {
    uVar2 = uStack_38;
  }
  uVar2 = CGameResourceManager::RemoveDirectFile(char const*)(lVar3,uVar2);
  if ((uVar2 & 1) == 0) goto code_r0x018ffa68;
  uStack_58 = 0;
  uStack_50 = 0;
  uStack_60 = 0;
  uVar2 = strlen(param_2);
  if (uVar2 < 0x17) {
    uVar5 = (ulong)&uStack_60 | 1;
    uStack_60 = CONCAT71(uStack_60._1_7_,(char)(uVar2 << 1));
    if (uVar2 != 0) goto code_r0x018ff954;
  }
  else {
    uVar4 = uVar2 + 0x10 & 0xfffffffffffffff0;
    if (uVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar4,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_60 = uVar4 | 1;
    uStack_58 = uVar2;
    uStack_50 = uVar5;
code_r0x018ff954:
    memcpy(uVar5,param_2,uVar2);
  }
  *(undefined1 *)(uVar5 + uVar2) = 0;
  lVar3 = std::__ndk1::__hash_iterator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, void*>*> std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, Framework::CSTLUnorderedMapAllocatorInf> >::find<string >(string const&)(param_1 + 0xa0,&uStack_60);
  if (lVar3 != 0) {
    std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, Framework::CSTLUnorderedMapAllocatorInf> >::erase(std::__ndk1::__hash_const_iterator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, void*>*>)(param_1 + 0xa0,lVar3);
  }
  if ((uStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_50);
  }
  uStack_58 = 0;
  uStack_50 = 0;
  uStack_60 = 0;
  uVar2 = strlen(param_2);
  if (uVar2 < 0x17) {
    uVar5 = (ulong)&uStack_60 | 1;
    uStack_60 = CONCAT71(uStack_60._1_7_,(char)(uVar2 << 1));
    if (uVar2 != 0) goto code_r0x018ffa38;
  }
  else {
    uVar4 = uVar2 + 0x10 & 0xfffffffffffffff0;
    if (uVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar4,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_60 = uVar4 | 1;
    uStack_58 = uVar2;
    uStack_50 = uVar5;
code_r0x018ffa38:
    memcpy(uVar5,param_2,uVar2);
  }
  *(undefined1 *)(uVar5 + uVar2) = 0;
  std::__ndk1::list<string, Framework::CSTLAllocator<string, Framework::CSTLListAllocatorInf> >::remove(string const&)(param_1 + 0x110,&uStack_60);
  if ((uStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_50);
  }
code_r0x018ffa68:
  if ((abStack_48[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  return;
}

// ==== CSoundManager::ResourceMapping(char const*)
// vaddr 0x17ffd1c | ghidra 0x18ffd1c | size 804 | symbol _ZN13CSoundManager15ResourceMappingEPKc | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN13CSoundManager15ResourceMappingEPKc(long param_1,undefined8 param_2)

{
  long lVar1;
  undefined *puVar2;
  ulong uVar3;
  long lVar4;
  long *plVar5;
  int *piVar6;
  ulong extraout_x1;
  uint uVar7;
  undefined4 uVar8;
  long lVar9;
  uint uVar10;
  long lVar11;
  undefined1 auVar12 [16];
  long lStack_d0;
  long lStack_c8;
  int iStack_c0;
  int iStack_bc;
  long lStack_b0;
  long lStack_a8;
  long lStack_a0;
  undefined8 uStack_98;
  undefined4 uStack_90;
  byte abStack_80 [16];
  ulong uStack_70;
  long alStack_68 [2];
  char cStack_58;
  undefined8 uStack_48;
  
  puVar2 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  lVar9 = *(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  uStack_48 = param_2;
  if (lVar9 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar9 = *(long *)puVar2;
  }
  CSoundManager::MakeSoundResourcePath(char const*)(abStack_80,param_2);
  uVar3 = (ulong)abStack_80 | 1;
  if ((abStack_80[0] & 1) != 0) {
    uVar3 = uStack_70;
  }
  uVar3 = CGameResourceManager::IsReadyDirectFile(char const*) const(lVar9,uVar3);
  if ((uVar3 & 1) == 0) {
    uVar8 = 0;
  }
  else {
    lVar4 = strstr(uStack_48,&UNK_028686c7/*"Voice"*/);
    uStack_90 = 0x3f800000;
    lStack_a8 = 0;
    lStack_b0 = 0;
    uStack_98 = 0;
    lStack_a0 = 0;
    std::__ndk1::unique_ptr<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, void*>, std::__ndk1::__hash_node_destructor<Framework::CSTLAllocator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, void*>, Framework::CSTLUnorderedMapAllocatorInf> > > std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, Framework::CSTLUnorderedMapAllocatorInf> >::__construct_node<char const*&, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >(char const*&, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > >&&)(alStack_68,param_1 + 0xa0,&uStack_48,&lStack_b0);
    auVar12 = std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, Framework::CSTLUnorderedMapAllocatorInf> >::__node_insert_unique(std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, Framework::CSTLUnorderedMap<string, CSoundManager::tSoundImage, std::__ndk1::hash<string >, std::__ndk1::equal_to<string > > >, void*>*)(param_1 + 0xa0,alStack_68[0]);
    lVar1 = alStack_68[0];
    if (((auVar12._8_8_ & 1) == 0) && (alStack_68[0] = 0, lVar1 != 0)) {
      if (cStack_58 != '\0') {
        plVar5 = (long *)*(long *)(lVar1 + 0x38);
        while (plVar5 != (long *)0x0) {
          lVar11 = *plVar5;
          if ((*(byte *)(plVar5 + 2) & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar5[4]);
          }
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar5);
          plVar5 = (long *)lVar11;
        }
        lVar11 = *(long *)(lVar1 + 0x28);
        *(undefined8 *)(lVar1 + 0x28) = 0;
        if (lVar11 != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
        }
        if ((*(byte *)(lVar1 + 0x10) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar1 + 0x20));
        }
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar1);
      lVar1 = lStack_b0;
      plVar5 = (long *)lStack_a0;
    }
    else {
      alStack_68[0] = 0;
      lVar1 = lStack_b0;
      plVar5 = (long *)lStack_a0;
    }
    while (plVar5 != (long *)0x0) {
      lVar11 = *plVar5;
      lStack_b0 = lVar1;
      if ((*(byte *)(plVar5 + 2) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar5[4]);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar5);
      lVar1 = lStack_b0;
      plVar5 = (long *)lVar11;
    }
    lStack_b0 = 0;
    if (lVar1 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
    CGameResourceManager::Lock()(lVar9);
    uVar3 = (ulong)abStack_80 | 1;
    if ((abStack_80[0] & 1) != 0) {
      uVar3 = uStack_70;
    }
    plVar5 = (long *)CGameResourceManager::crResourceElementDirectFile(char const*) const(lVar9,uVar3);
    piVar6 = (int *)(**(code **)(*plVar5 + 0x50))();
    if ((*piVar6 != 0x46534900) || (0x20130304 < (uint)piVar6[1])) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0x3af,&UNK_028686cd/*"pFileStreamImage->IsValid() is null."*/);
    }
    uVar7 = piVar6[2];
    if (uVar7 != 0) {
      lVar1 = auVar12._0_8_ + 0x28;
      uVar10 = 0;
      do {
        if (uVar7 <= uVar10) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02866e51/*"C:\BAS_Submission\Client\Project\../Library/Framework/Tools\MakeFileStream/FileStream_Image.h"*/,0xf1,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar10);
        }
        lStack_d0 = (long)piVar6 + (*(ulong *)(piVar6 + (ulong)uVar10 * 4 + 4) & 0xffffffff);
        lStack_c8 = (long)piVar6 + (*(ulong *)(piVar6 + (ulong)uVar10 * 4 + 4) >> 0x20);
        iStack_c0 = (int)*(long *)(piVar6 + (ulong)uVar10 * 4 + 6);
        iStack_bc = piVar6[(ulong)uVar10 * 4 + 7];
        lStack_a0 = *(long *)(piVar6 + (ulong)uVar10 * 4 + 6);
        uStack_98 = CONCAT71(uStack_98._1_7_,lVar4 != 0);
        lStack_b0 = lStack_d0;
        lStack_a8 = lStack_c8;
        std::__ndk1::unique_ptr<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, void*>, std::__ndk1::__hash_node_destructor<Framework::CSTLAllocator<std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, void*>, Framework::CSTLUnorderedMapAllocatorInf> > > std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, Framework::CSTLUnorderedMapAllocatorInf> >::__construct_node<char const*&, CSoundManager::tSoundImage>(char const*&, CSoundManager::tSoundImage&&)(alStack_68,lVar1,&lStack_d0,&lStack_b0);
        std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, std::__ndk1::__unordered_map_hasher<string, std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, std::__ndk1::hash<string >, true>, std::__ndk1::__unordered_map_equal<string, std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, std::__ndk1::equal_to<string >, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, Framework::CSTLUnorderedMapAllocatorInf> >::__node_insert_unique(std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<string, CSoundManager::tSoundImage>, void*>*)(lVar1,alStack_68[0]);
        lVar11 = alStack_68[0];
        if ((extraout_x1 & 1) == 0) {
          alStack_68[0] = 0;
          if (lVar11 != 0) {
            if ((cStack_58 != '\0') && ((*(byte *)(lVar11 + 0x10) & 1) != 0)) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar11 + 0x20));
            }
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar11);
          }
        }
        else {
          alStack_68[0] = 0;
        }
        uVar7 = piVar6[2];
        uVar10 = uVar10 + 1;
      } while (uVar10 < uVar7);
    }
    CGameResourceManager::Unlock()(lVar9);
    uVar8 = 1;
  }
  if ((abStack_80[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_70);
  }
  return uVar8;
}

// ==== CSoundManager::IsReady(char const*)
// vaddr 0x1800040 | ghidra 0x1900040 | size 144 | symbol _ZN13CSoundManager7IsReadyEPKc | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN13CSoundManager7IsReadyEPKc(undefined8 param_1,undefined8 param_2)

{
  ulong uVar1;
  undefined *puVar2;
  uint uVar3;
  long lVar4;
  byte abStack_38 [16];
  ulong uStack_28;
  
  puVar2 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar2;
  }
  CSoundManager::MakeSoundResourcePath(char const*)(abStack_38,param_2);
  uVar1 = (ulong)abStack_38 | 1;
  if ((abStack_38[0] & 1) != 0) {
    uVar1 = uStack_28;
  }
  uVar3 = CGameResourceManager::IsReadyDirectFile(char const*) const(lVar4,uVar1);
  if ((abStack_38[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
  }
  return uVar3 & 1;
}

// ==== CSoundManager::SetMaxPlaySoundObject(unsigned int)
// vaddr 0x18000d0 | ghidra 0x19000d0 | size 8 | symbol _ZN13CSoundManager21SetMaxPlaySoundObjectEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager21SetMaxPlaySoundObjectEj(long param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x150) = param_2;
  return;
}

// ==== CSoundManager::GetMaxPlaySoundObject() const
// vaddr 0x18000d8 | ghidra 0x19000d8 | size 8 | symbol _ZNK13CSoundManager21GetMaxPlaySoundObjectEv | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZNK13CSoundManager21GetMaxPlaySoundObjectEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x150);
}

// ==== CSoundManager::rSoundResourceMap() const
// vaddr 0x18000e0 | ghidra 0x19000e0 | size 8 | symbol _ZNK13CSoundManager17rSoundResourceMapEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK13CSoundManager17rSoundResourceMapEv(long param_1)

{
  return param_1 + 0xa0;
}

// ==== CSoundManager::pSoundFileName(char const*, unsigned int) const
// vaddr 0x18000e8 | ghidra 0x19000e8 | size 352 | symbol _ZNK13CSoundManager14pSoundFileNameEPKcj | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK13CSoundManager14pSoundFileNameEPKcj(undefined8 param_1,long param_2,uint param_3)

{
  undefined *puVar1;
  ulong uVar2;
  long *plVar3;
  int *piVar4;
  long lVar5;
  long lVar6;
  byte abStack_48 [16];
  ulong uStack_38;
  
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0x3f4,&UNK_0285ea95/*"apPackageName is null."*/);
  }
  puVar1 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  lVar6 = *(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  if (lVar6 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar6 = *(long *)puVar1;
  }
  CSoundManager::MakeSoundResourcePath(char const*)(abStack_48,param_2);
  uVar2 = (ulong)abStack_48 | 1;
  if ((abStack_48[0] & 1) != 0) {
    uVar2 = uStack_38;
  }
  uVar2 = CGameResourceManager::IsReadyDirectFile(char const*) const(lVar6,uVar2);
  if ((uVar2 & 1) == 0) {
    lVar5 = 0;
  }
  else {
    CGameResourceManager::Lock()(lVar6);
    uVar2 = (ulong)abStack_48 | 1;
    if ((abStack_48[0] & 1) != 0) {
      uVar2 = uStack_38;
    }
    plVar3 = (long *)CGameResourceManager::crResourceElementDirectFile(char const*) const(lVar6,uVar2);
    piVar4 = (int *)(**(code **)(*plVar3 + 0x50))();
    if ((*piVar4 != 0x46534900) || (0x20130304 < (uint)piVar4[1])) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02868658/*"C:\BAS_Submission\Client\Project\..\Source\Game\SoundManager.cpp"*/,0x3fe,&UNK_028686cd/*"pFileStreamImage->IsValid() is null."*/);
    }
    if (param_3 < (uint)piVar4[2]) {
      lVar5 = (ulong)(uint)piVar4[(ulong)param_3 * 4 + 4] + (long)piVar4;
    }
    else {
      lVar5 = 0;
    }
    CGameResourceManager::Unlock()(lVar6);
  }
  if ((abStack_48[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  return lVar5;
}

// ==== CSoundManager::IsLoading() const
// vaddr 0x1800248 | ghidra 0x1900248 | size 212 | symbol _ZNK13CSoundManager9IsLoadingEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK13CSoundManager9IsLoadingEv(long param_1)

{
  undefined *puVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  byte abStack_48 [16];
  ulong uStack_38;
  
  puVar1 = PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonI20CGameResourceManagerE11m_pInstanceE_02cc2018;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar1;
  }
  lVar5 = *(long *)(param_1 + 0x118);
  if (param_1 + 0x110 != lVar5) {
    do {
      if ((*(byte *)(lVar5 + 0x10) & 1) == 0) {
        lVar2 = lVar5 + 0x11;
      }
      else {
        lVar2 = *(long *)(lVar5 + 0x20);
      }
      CSoundManager::MakeSoundResourcePath(char const*)(abStack_48,lVar2);
      uVar3 = (ulong)abStack_48 | 1;
      if ((abStack_48[0] & 1) != 0) {
        uVar3 = uStack_38;
      }
      uVar3 = CGameResourceManager::IsReadyDirectFile(char const*) const(lVar4,uVar3);
      if ((abStack_48[0] & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
      }
      if ((uVar3 & 1) == 0) {
        return 1;
      }
      lVar5 = *(long *)(lVar5 + 8);
    } while (param_1 + 0x110 != lVar5);
  }
  return 0;
}

// ==== CSoundManager::CInterruptNotify::~CInterruptNotify()
// vaddr 0x180031c | ghidra 0x190031c | size 4 | symbol _ZN13CSoundManager16CInterruptNotifyD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN13CSoundManager16CInterruptNotifyD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== CMenuVoiceManager::CMenuVoiceManager()
// vaddr 0x1aa8f8c | ghidra 0x1ba8f8c | size 40 | symbol _ZN17CMenuVoiceManagerC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManagerC1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTV17CMenuVoiceManager_02cc40b8 + 0x10);
  memset(param_1 + 1,0,0x78);
  return;
}

// ==== CMenuVoiceManager::~CMenuVoiceManager()
// vaddr 0x1aa8fb4 | ghidra 0x1ba8fb4 | size 540 | symbol _ZN17CMenuVoiceManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManagerD1Ev(long *param_1)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  long lVar4;
  code *pcVar5;
  long lVar6;
  long lVar7;
  long alStack_60 [4];
  long *plStack_40;
  
  *param_1 = (long)(PTR__ZTV17CMenuVoiceManager_02cc40b8 + 0x10);
  puVar1 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  uVar3 = CUIManager::rVoicePlayPriorityManager()(lVar2);
  plStack_40 = (long *)0x0;
  CVoicePlayPriority::SetFuncStopMenuVoice(std::__ndk1::function<void ()>)(uVar3,alStack_60);
  if (alStack_60 == plStack_40) {
    pcVar5 = *(code **)(*plStack_40 + 0x20);
  }
  else {
    if (plStack_40 == (long *)0x0) goto code_r0x01ba9040;
    pcVar5 = *(code **)(*plStack_40 + 0x28);
  }
  (*pcVar5)();
code_r0x01ba9040:
  lVar2 = param_1[0xd];
  if (lVar2 != 0) {
    lVar6 = param_1[0xe];
    if (lVar6 != lVar2) {
      do {
        param_1[0xe] = lVar6 + -0x20;
        lVar4 = lVar6 + -0x20;
        if ((*(byte *)(lVar6 + -0x18) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar6 + -8));
          lVar4 = param_1[0xe];
        }
        lVar6 = lVar4;
      } while (lVar6 != lVar2);
      lVar2 = param_1[0xd];
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar2);
  }
  lVar2 = param_1[10];
  if (lVar2 != 0) {
    lVar6 = param_1[0xb];
    if (lVar6 != lVar2) {
      do {
        param_1[0xb] = lVar6 + -0x18;
        lVar4 = lVar6 + -0x18;
        if ((*(byte *)(lVar6 + -0x18) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar6 + -8));
          lVar4 = param_1[0xb];
        }
        lVar6 = lVar4;
      } while (lVar6 != lVar2);
      lVar2 = param_1[10];
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar2);
  }
  lVar2 = param_1[7];
  if (lVar2 != 0) {
    lVar6 = param_1[8];
    if (lVar6 != lVar2) {
      do {
        param_1[8] = lVar6 + -0x18;
        lVar4 = lVar6 + -0x18;
        if ((*(byte *)(lVar6 + -0x18) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar6 + -8));
          lVar4 = param_1[8];
        }
        lVar6 = lVar4;
      } while (lVar6 != lVar2);
      lVar2 = param_1[7];
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar2);
  }
  lVar2 = param_1[4];
  if (lVar2 != 0) {
    lVar6 = param_1[5];
    if (lVar6 != lVar2) {
      do {
        param_1[5] = lVar6 + -0x38;
        lVar4 = *(long *)(lVar6 + -0x20);
        if (lVar4 != 0) {
          lVar7 = *(long *)(lVar6 + -0x18);
          if (lVar7 != lVar4) {
            *(ulong *)(lVar6 + -0x18) = lVar7 + (~((lVar7 + -0x10) - lVar4) & 0xfffffffffffffff0U);
          }
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
        }
        if ((*(byte *)(lVar6 + -0x38) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar6 + -0x28));
        }
        lVar6 = param_1[5];
      } while (lVar6 != lVar2);
      lVar2 = param_1[4];
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar2);
  }
  lVar2 = param_1[1];
  if (lVar2 != 0) {
    lVar6 = param_1[2];
    if (lVar6 != lVar2) {
      param_1[2] = lVar6 + (~((lVar6 + -8) - lVar2) & 0xfffffffffffffff8U);
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  return;
}

// ==== CMenuVoiceManager::~CMenuVoiceManager()
// vaddr 0x1aa91d0 | ghidra 0x1ba91d0 | size 24 | symbol _ZN17CMenuVoiceManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManagerD0Ev(undefined8 param_1)

{
  CMenuVoiceManager::~CMenuVoiceManager()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CMenuVoiceManager::Initialize()
// vaddr 0x1aa91e8 | ghidra 0x1ba91e8 | size 156 | symbol _ZN17CMenuVoiceManager10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManager10InitializeEv(undefined8 param_1)

{
  undefined *puVar1;
  undefined8 uVar2;
  long lVar3;
  code *pcVar4;
  undefined *puStack_50;
  undefined8 uStack_48;
  long *plStack_30;
  
  puVar1 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  uVar2 = CUIManager::rVoicePlayPriorityManager()(lVar3);
  puStack_50 = &UNK_02b533b8;
  uStack_48 = param_1;
  plStack_30 = (long *)&puStack_50;
  CVoicePlayPriority::SetFuncStopMenuVoice(std::__ndk1::function<void ()>)(uVar2,&puStack_50);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar4 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) {
      return;
    }
    pcVar4 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar4)();
  return;
}

// ==== CMenuVoiceManager::Progress()
// vaddr 0x1aa9284 | ghidra 0x1ba9284 | size 340 | symbol _ZN17CMenuVoiceManager8ProgressEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManager8ProgressEv(long param_1)

{
  long *plVar1;
  int iVar2;
  code *pcVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  long lVar6;
  undefined *puStack_60;
  long lStack_58;
  long *plStack_40;
  
  CSoundManager::UpdateMapping()(*(undefined8 *)
                   PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358);
  if (*(long *)(param_1 + 0x50) != *(long *)(param_1 + 0x58)) {
    puStack_60 = &UNK_02b53438;
    lStack_58 = param_1;
    plStack_40 = (long *)&puStack_60;
    if ((*(long *)(param_1 + 8) == *(long *)(param_1 + 0x10)) ||
       (std::__ndk1::__tree_node_base<void*>*& std::__ndk1::__tree<std::__ndk1::__value_type<string, unsigned int>, std::__ndk1::__map_value_compare<string, std::__ndk1::__value_type<string, unsigned int>, std::__ndk1::less<string >, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<string, unsigned int>, Framework::CSTLMapAllocatorInf> >::__find_equal<string >(std::__ndk1::__tree_node_base<void*>*&, string const&)+0x1a0(param_1), &puStack_60 == (undefined **)plStack_40)) {
      pcVar3 = *(code **)(*plStack_40 + 0x20);
    }
    else {
      if (plStack_40 == (long *)0x0) goto code_r0x01ba932c;
      pcVar3 = *(code **)(*plStack_40 + 0x28);
    }
    (*pcVar3)();
  }
code_r0x01ba932c:
  puVar5 = *(undefined4 **)(param_1 + 8);
  plVar1 = (long *)(param_1 + 0x10);
  if (puVar5 != (undefined4 *)*plVar1) {
    do {
      while (iVar2 = CMenuVoiceManager::PlaySE(unsigned int, bool)(param_1,*puVar5,*(undefined1 *)(puVar5 + 1)), iVar2 != 0) {
        puVar4 = (undefined4 *)*plVar1;
        lVar6 = (long)puVar4 - (long)(puVar5 + 2) >> 3;
        if (lVar6 != 0) {
          memmove(puVar5);
          puVar4 = (undefined4 *)*plVar1;
        }
        if (puVar4 != puVar5 + lVar6 * 2) {
          puVar4 = (undefined4 *)
                   ((long)puVar4 +
                   (~((long)puVar4 + (-8 - (long)(puVar5 + lVar6 * 2))) & 0xfffffffffffffff8U));
          *plVar1 = (long)puVar4;
        }
        if (puVar4 == puVar5) goto code_r0x01ba93ac;
      }
      puVar5 = puVar5 + 2;
    } while ((undefined4 *)*plVar1 != puVar5);
  }
code_r0x01ba93ac:
  CMenuVoiceManager::ProgressPlayingList()(param_1);
  CMenuVoiceManager::ProgressRemovePackList()(param_1);
  CMenuVoiceManager::ProgressStopRequestList()(param_1);
  return;
}

// ==== CMenuVoiceManager::RemovePlayWaitElement()
// vaddr 0x1aa93d8 | ghidra 0x1ba93d8 | size 148 | symbol _ZN17CMenuVoiceManager21RemovePlayWaitElementEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN17CMenuVoiceManager21RemovePlayWaitElementEv(long param_1)

{
  code *pcVar1;
  undefined *puStack_50;
  long lStack_48;
  long *plStack_30;
  long *plStack_18;
  
  if (*(long *)(param_1 + 0x50) != *(long *)(param_1 + 0x58)) {
    puStack_50 = &UNK_02b53438;
    lStack_48 = param_1;
    plStack_30 = (long *)&puStack_50;
    if ((*(long *)(param_1 + 8) == *(long *)(param_1 + 0x10)) ||
       (plStack_18 = (long *)(param_1 + 8), (*_UNK_02b53468)(&puStack_50,&plStack_18),
       &puStack_50 == (undefined **)plStack_30)) {
      pcVar1 = *(code **)(*plStack_30 + 0x20);
    }
    else {
      if (plStack_30 == (long *)0x0) {
        return;
      }
      pcVar1 = *(code **)(*plStack_30 + 0x28);
    }
    (*pcVar1)();
  }
  return;
}

// ==== CMenuVoiceManager::ProgressReserveList()
// vaddr 0x1aa946c | ghidra 0x1ba946c | size 152 | symbol _ZN17CMenuVoiceManager19ProgressReserveListEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManager19ProgressReserveListEv(long param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  long lVar4;
  
  puVar3 = *(undefined4 **)(param_1 + 8);
  if (puVar3 != *(undefined4 **)(param_1 + 0x10)) {
    do {
      while (iVar1 = CMenuVoiceManager::PlaySE(unsigned int, bool)(param_1,*puVar3,*(undefined1 *)(puVar3 + 1)), iVar1 == 0) {
        puVar3 = puVar3 + 2;
        if (*(undefined4 **)(param_1 + 0x10) == puVar3) {
          return;
        }
      }
      puVar2 = *(undefined4 **)(param_1 + 0x10);
      lVar4 = (long)puVar2 - (long)(puVar3 + 2) >> 3;
      if (lVar4 != 0) {
        memmove(puVar3);
        puVar2 = *(undefined4 **)(param_1 + 0x10);
      }
      if (puVar2 != puVar3 + lVar4 * 2) {
        puVar2 = (undefined4 *)
                 ((long)puVar2 +
                 (~((long)puVar2 + (-8 - (long)(puVar3 + lVar4 * 2))) & 0xfffffffffffffff8U));
        *(undefined4 **)(param_1 + 0x10) = puVar2;
      }
    } while (puVar2 != puVar3);
  }
  return;
}

// ==== CMenuVoiceManager::ProgressPlayingList()
// vaddr 0x1aa9504 | ghidra 0x1ba9504 | size 444 | symbol _ZN17CMenuVoiceManager19ProgressPlayingListEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManager19ProgressPlayingListEv(long param_1)

{
  undefined *puVar1;
  ulong uVar2;
  long lVar3;
  undefined8 *puVar4;
  byte *pbVar5;
  long lVar6;
  undefined8 *puVar7;
  byte *pbVar8;
  undefined8 uVar9;
  byte *pbVar10;
  byte *pbVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  
  puVar1 = PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
  pbVar11 = *(byte **)(param_1 + 0x20);
  if (pbVar11 == *(byte **)(param_1 + 0x28)) {
    return;
  }
  do {
    puVar7 = *(undefined8 **)(pbVar11 + 0x18);
    puVar4 = *(undefined8 **)(pbVar11 + 0x20);
    if (puVar7 != puVar4) {
      uVar9 = *(undefined8 *)puVar1;
      do {
        while (uVar2 = CSoundManager::IsPlaying(unsigned long) const(uVar9,*puVar7), (uVar2 & 1) == 0) {
          puVar4 = *(undefined8 **)(pbVar11 + 0x20);
          lVar3 = (long)puVar4 - (long)(puVar7 + 2) >> 4;
          if (lVar3 != 0) {
            memmove(puVar7);
            puVar4 = *(undefined8 **)(pbVar11 + 0x20);
          }
          if (puVar4 != puVar7 + lVar3 * 2) {
            puVar4 = (undefined8 *)
                     ((long)puVar4 +
                     (~((long)puVar4 + (-0x10 - (long)(puVar7 + lVar3 * 2))) & 0xfffffffffffffff0U))
            ;
            *(undefined8 **)(pbVar11 + 0x20) = puVar4;
          }
          if (puVar7 == puVar4) goto code_r0x01ba95ac;
        }
        puVar4 = *(undefined8 **)(pbVar11 + 0x20);
        puVar7 = puVar7 + 2;
      } while (puVar7 != puVar4);
code_r0x01ba95ac:
      puVar7 = *(undefined8 **)(pbVar11 + 0x18);
    }
    if (puVar4 == puVar7) {
      pbVar5 = *(byte **)(param_1 + 0x28);
      pbVar8 = pbVar11 + 0x38;
      pbVar10 = pbVar11;
      if (pbVar8 == pbVar5) goto code_r0x01ba9650;
      pbVar8 = pbVar11;
      do {
        if ((*pbVar8 & 1) == 0) {
          pbVar8[0] = 0;
          pbVar8[1] = 0;
        }
        else {
          **(undefined1 **)(pbVar8 + 0x10) = 0;
          pbVar8[8] = 0;
          pbVar8[9] = 0;
          pbVar8[10] = 0;
          pbVar8[0xb] = 0;
          pbVar8[0xc] = 0;
          pbVar8[0xd] = 0;
          pbVar8[0xe] = 0;
          pbVar8[0xf] = 0;
        }
        string::reserve(unsigned long)(pbVar8,0);
        uVar13 = *(undefined8 *)(pbVar8 + 0x40);
        uVar12 = *(undefined8 *)(pbVar8 + 0x38);
        uVar9 = *(undefined8 *)(pbVar8 + 0x48);
        pbVar10 = pbVar8 + 0x38;
        pbVar8[0x40] = 0;
        pbVar8[0x41] = 0;
        pbVar8[0x42] = 0;
        pbVar8[0x43] = 0;
        pbVar8[0x44] = 0;
        pbVar8[0x45] = 0;
        pbVar8[0x46] = 0;
        pbVar8[0x47] = 0;
        pbVar8[0x48] = 0;
        pbVar8[0x49] = 0;
        pbVar8[0x4a] = 0;
        pbVar8[0x4b] = 0;
        pbVar8[0x4c] = 0;
        pbVar8[0x4d] = 0;
        pbVar8[0x4e] = 0;
        pbVar8[0x4f] = 0;
        pbVar8[0x38] = 0;
        pbVar8[0x39] = 0;
        pbVar8[0x3a] = 0;
        pbVar8[0x3b] = 0;
        pbVar8[0x3c] = 0;
        pbVar8[0x3d] = 0;
        pbVar8[0x3e] = 0;
        pbVar8[0x3f] = 0;
        *(undefined8 *)(pbVar8 + 0x10) = uVar9;
        *(undefined8 *)(pbVar8 + 8) = uVar13;
        *(undefined8 *)pbVar8 = uVar12;
        std::__ndk1::enable_if<__is_forward_iterator<CMenuVoiceManager::PlayingData::PlayUnit*>::value&&is_constructible<CMenuVoiceManager::PlayingData::PlayUnit, std::__ndk1::iterator_traits<CMenuVoiceManager::PlayingData::PlayUnit*>::reference>::value, void>::type std::__ndk1::vector<CMenuVoiceManager::PlayingData::PlayUnit, Framework::CSTLAllocator<CMenuVoiceManager::PlayingData::PlayUnit, Framework::CSTLVectorAllocatorInf> >::assign<CMenuVoiceManager::PlayingData::PlayUnit*>(CMenuVoiceManager::PlayingData::PlayUnit*, CMenuVoiceManager::PlayingData::PlayUnit*)(pbVar8 + 0x18,*(undefined8 *)(pbVar8 + 0x50),*(undefined8 *)(pbVar8 + 0x58))
        ;
        *(undefined4 *)(pbVar8 + 0x30) = *(undefined4 *)(pbVar8 + 0x68);
        pbVar8 = pbVar10;
      } while (pbVar5 + -0x38 != pbVar10);
      while (pbVar8 = *(byte **)(param_1 + 0x28), pbVar8 != pbVar10) {
code_r0x01ba9650:
        *(byte **)(param_1 + 0x28) = pbVar8 + -0x38;
        lVar3 = *(long *)(pbVar8 + -0x20);
        if (lVar3 != 0) {
          lVar6 = *(long *)(pbVar8 + -0x18);
          if (lVar6 != lVar3) {
            *(ulong *)(pbVar8 + -0x18) = lVar6 + (~((lVar6 + -0x10) - lVar3) & 0xfffffffffffffff0U);
          }
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
        }
        if ((pbVar8[-0x38] & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(pbVar8 + -0x28));
        }
      }
      if (pbVar10 == pbVar11) {
        return;
      }
    }
    else {
      pbVar11 = pbVar11 + 0x38;
      if (*(byte **)(param_1 + 0x28) == pbVar11) {
        return;
      }
    }
  } while( true );
}

// ==== CMenuVoiceManager::ProgressRemovePackList()
// vaddr 0x1aa96c0 | ghidra 0x1ba96c0 | size 568 | symbol _ZN17CMenuVoiceManager22ProgressRemovePackListEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManager22ProgressRemovePackListEv(long param_1)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  byte bVar4;
  byte bVar5;
  bool bVar6;
  int iVar7;
  byte *pbVar8;
  long lVar9;
  undefined8 uVar10;
  byte *pbVar11;
  byte *pbVar12;
  undefined8 uVar13;
  long lVar14;
  byte *pbVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  byte abStack_88 [8];
  ulong uStack_80;
  byte *pbStack_78;
  long lStack_70;
  long lStack_68;
  
  pbVar15 = *(byte **)(param_1 + 0x38);
  if (pbVar15 != *(byte **)(param_1 + 0x40)) {
    uVar13 = *(undefined8 *)PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
    do {
      while( true ) {
        lVar14 = *(long *)(param_1 + 0x20);
        lVar3 = *(long *)(param_1 + 0x28);
        if (lVar14 != lVar3) break;
code_r0x01ba9848:
        if ((*pbVar15 & 1) == 0) {
          pbVar11 = pbVar15 + 1;
        }
        else {
          pbVar11 = *(byte **)(pbVar15 + 0x10);
        }
        CSoundManager::RemoveResource(char const*)(uVar13,pbVar11);
        pbVar12 = *(byte **)(param_1 + 0x40);
        pbVar11 = pbVar15 + 0x18;
        pbVar8 = pbVar15;
        if (pbVar11 == pbVar12) {
code_r0x01ba9718:
          do {
            *(byte **)(param_1 + 0x40) = pbVar11 + -0x18;
            pbVar12 = pbVar11 + -0x18;
            if ((pbVar11[-0x18] & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(pbVar11 + -8));
              pbVar12 = *(byte **)(param_1 + 0x40);
            }
            pbVar11 = pbVar12;
          } while (pbVar11 != pbVar8);
        }
        else {
          pbVar11 = pbVar15;
          do {
            if ((*pbVar11 & 1) == 0) {
              pbVar11[0] = 0;
              pbVar11[1] = 0;
            }
            else {
              **(undefined1 **)(pbVar11 + 0x10) = 0;
              pbVar11[8] = 0;
              pbVar11[9] = 0;
              pbVar11[10] = 0;
              pbVar11[0xb] = 0;
              pbVar11[0xc] = 0;
              pbVar11[0xd] = 0;
              pbVar11[0xe] = 0;
              pbVar11[0xf] = 0;
            }
            string::reserve(unsigned long)(pbVar11,0);
            uVar10 = *(undefined8 *)(pbVar11 + 0x28);
            uVar17 = *(undefined8 *)(pbVar11 + 0x20);
            uVar16 = *(undefined8 *)(pbVar11 + 0x18);
            pbVar8 = pbVar11 + 0x18;
            pbVar11[0x20] = 0;
            pbVar11[0x21] = 0;
            pbVar11[0x22] = 0;
            pbVar11[0x23] = 0;
            pbVar11[0x24] = 0;
            pbVar11[0x25] = 0;
            pbVar11[0x26] = 0;
            pbVar11[0x27] = 0;
            pbVar11[0x28] = 0;
            pbVar11[0x29] = 0;
            pbVar11[0x2a] = 0;
            pbVar11[0x2b] = 0;
            pbVar11[0x2c] = 0;
            pbVar11[0x2d] = 0;
            pbVar11[0x2e] = 0;
            pbVar11[0x2f] = 0;
            *(undefined8 *)(pbVar11 + 0x10) = uVar10;
            pbVar11[0x18] = 0;
            pbVar11[0x19] = 0;
            pbVar11[0x1a] = 0;
            pbVar11[0x1b] = 0;
            pbVar11[0x1c] = 0;
            pbVar11[0x1d] = 0;
            pbVar11[0x1e] = 0;
            pbVar11[0x1f] = 0;
            *(undefined8 *)(pbVar11 + 8) = uVar17;
            *(undefined8 *)pbVar11 = uVar16;
            pbVar11 = pbVar8;
          } while (pbVar12 + -0x18 != pbVar8);
          pbVar11 = *(byte **)(param_1 + 0x40);
          if (pbVar11 != pbVar8) goto code_r0x01ba9718;
        }
        if (pbVar8 == pbVar15) {
          return;
        }
      }
      bVar6 = true;
      do {
        CMenuVoiceManager::PlayingData::PlayingData(CMenuVoiceManager::PlayingData const&)(abStack_88,lVar14);
        bVar5 = abStack_88[0];
        bVar4 = *pbVar15;
        uVar1 = (ulong)(abStack_88[0] >> 1);
        if ((abStack_88[0] & 1) != 0) {
          uVar1 = uStack_80;
        }
        uVar2 = (ulong)(bVar4 >> 1);
        if ((bVar4 & 1) != 0) {
          uVar2 = *(ulong *)(pbVar15 + 8);
        }
        if (uVar1 == uVar2) {
          pbVar11 = (byte *)((ulong)abStack_88 | 1);
          if ((abStack_88[0] & 1) != 0) {
            pbVar11 = pbStack_78;
          }
          pbVar8 = pbVar15 + 1;
          if ((bVar4 & 1) != 0) {
            pbVar8 = *(byte **)(pbVar15 + 0x10);
          }
          if ((abStack_88[0] & 1) == 0) {
            if (uVar1 != 0) {
              lVar9 = -(ulong)(abStack_88[0] >> 1);
              pbVar11 = (byte *)((ulong)abStack_88 | 1);
              do {
                if (*pbVar11 != *pbVar8) goto code_r0x01ba97f0;
                pbVar11 = pbVar11 + 1;
                lVar9 = lVar9 + 1;
                pbVar8 = pbVar8 + 1;
              } while (lVar9 != 0);
            }
          }
          else if ((uVar1 != 0) && (iVar7 = memcmp(pbVar11), iVar7 != 0))
          goto code_r0x01ba97f0;
          bVar6 = false;
        }
code_r0x01ba97f0:
        if (lStack_70 != 0) {
          if (lStack_68 != lStack_70) {
            lStack_68 = lStack_68 + (~((lStack_68 + -0x10) - lStack_70) & 0xfffffffffffffff0U);
          }
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
          bVar5 = abStack_88[0];
        }
        if ((bVar5 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pbStack_78);
        }
        lVar14 = lVar14 + 0x38;
      } while ((lVar14 != lVar3) && (bVar6));
      if (bVar6) goto code_r0x01ba9848;
      pbVar15 = pbVar15 + 0x18;
    } while (*(byte **)(param_1 + 0x40) != pbVar15);
  }
  return;
}

// ==== CMenuVoiceManager::ProgressStopRequestList()
// vaddr 0x1aa98f8 | ghidra 0x1ba98f8 | size 600 | symbol _ZN17CMenuVoiceManager23ProgressStopRequestListEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN17CMenuVoiceManager23ProgressStopRequestListEv(long param_1)

{
  ulong uVar1;
  byte *pbVar2;
  ulong uVar3;
  ulong *puVar4;
  ulong uVar5;
  byte *pbVar6;
  undefined8 *puVar7;
  byte bVar8;
  ulong *puVar9;
  byte *pbVar10;
  ulong uVar11;
  undefined4 uVar12;
  int iVar13;
  byte *pbVar14;
  ulong uVar15;
  byte *pbVar16;
  undefined8 uVar17;
  undefined8 *puVar18;
  byte *pbVar19;
  ulong *puVar20;
  ulong uStack_90;
  ulong uStack_88;
  byte *pbStack_80;
  
  uVar12 = _UNK_02863804;
  puVar20 = *(ulong **)(param_1 + 0x50);
  puVar4 = *(ulong **)(param_1 + 0x58);
  if (puVar20 != puVar4) {
    if (*(long *)(param_1 + 0x20) != *(long *)(param_1 + 0x28)) {
      uVar17 = *(undefined8 *)PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
      pbVar19 = (byte *)((ulong)&uStack_90 | 1);
      do {
        uStack_88 = 0;
        pbStack_80 = (byte *)0x0;
        uStack_90 = 0;
        if ((*puVar20 & 1) == 0) {
          pbStack_80 = (byte *)puVar20[2];
          uStack_88 = puVar20[1];
          uStack_90 = *puVar20;
        }
        else {
          uVar3 = puVar20[1];
          uVar5 = puVar20[2];
          if (uVar3 < 0x17) {
            uStack_90 = (uVar3 & 0x7f) << 1;
            pbVar14 = pbVar19;
            if (uVar3 != 0) goto code_r0x01ba99fc;
          }
          else {
            uVar15 = uVar3 + 0x10 & 0xfffffffffffffff0;
            if (uVar15 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
            }
            pbVar14 = (byte *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar15,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
            if (pbVar14 == (byte *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
            }
            uStack_90 = uVar15 | 1;
            uStack_88 = uVar3;
            pbStack_80 = pbVar14;
code_r0x01ba99fc:
            memcpy(pbVar14,uVar5,uVar3);
          }
          pbVar14[uVar3] = 0;
        }
        uVar3 = uStack_90;
        pbVar14 = *(byte **)(param_1 + 0x20);
        pbVar6 = *(byte **)(param_1 + 0x28);
        if (pbVar14 != pbVar6) {
          uVar15 = uStack_90 >> 1 & 0x7f;
          uVar5 = uVar15;
          if ((uStack_90 & 1) != 0) {
            uVar5 = uStack_88;
          }
          do {
            bVar8 = *pbVar14;
            uVar1 = (ulong)(bVar8 >> 1);
            if ((bVar8 & 1) != 0) {
              uVar1 = *(ulong *)(pbVar14 + 8);
            }
            if (uVar5 == uVar1) {
              pbVar16 = *(byte **)(pbVar14 + 0x10);
              pbVar2 = pbVar19;
              if ((uVar3 & 1) != 0) {
                pbVar2 = pbStack_80;
              }
              if ((bVar8 & 1) == 0) {
                pbVar16 = pbVar14 + 1;
              }
              pbVar10 = pbVar19;
              uVar1 = -uVar15;
              uVar11 = uVar5;
              if ((uVar3 & 1) == 0) {
                while (uVar11 != 0) {
                  if (*pbVar10 != *pbVar16) goto code_r0x01ba9ad0;
                  pbVar16 = pbVar16 + 1;
                  uVar1 = uVar1 + 1;
                  pbVar10 = pbVar10 + 1;
                  uVar11 = uVar1;
                }
              }
              else if ((uVar5 != 0) && (iVar13 = memcmp(pbVar2,pbVar16,uVar5), iVar13 != 0)
                      ) goto code_r0x01ba9ad0;
              puVar7 = *(undefined8 **)(pbVar14 + 0x20);
              for (puVar18 = *(undefined8 **)(pbVar14 + 0x18); puVar18 != puVar7;
                  puVar18 = puVar18 + 2) {
                CSoundManager::Stop(unsigned long, std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)(uVar12,uVar17,*puVar18);
              }
            }
code_r0x01ba9ad0:
            pbVar14 = pbVar14 + 0x38;
          } while (pbVar14 != pbVar6);
        }
        if ((uVar3 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pbStack_80);
        }
        puVar20 = puVar20 + 3;
      } while (puVar20 != puVar4);
      puVar20 = *(ulong **)(param_1 + 0x50);
      puVar4 = *(ulong **)(param_1 + 0x58);
    }
    while (puVar9 = puVar4, puVar9 != puVar20) {
      *(ulong **)(param_1 + 0x58) = puVar9 + -3;
      puVar4 = puVar9 + -3;
      if ((puVar9[-3] & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar9[-1]);
        puVar4 = *(ulong **)(param_1 + 0x58);
      }
    }
  }
  return;
}

// ==== CMenuVoiceManager::PlayVoiceFromMenuID(unsigned int, unsigned int, bool, int)
// vaddr 0x1aa9b50 | ghidra 0x1ba9b50 | size 716 | symbol _ZN17CMenuVoiceManager19PlayVoiceFromMenuIDEjjbi | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN17CMenuVoiceManager19PlayVoiceFromMenuIDEjjbi
               (long param_1,undefined4 param_2,undefined4 param_3,byte param_4)

{
  undefined8 *puVar1;
  int *piVar2;
  long lVar3;
  undefined8 *puVar4;
  int iVar5;
  int *piVar6;
  bool bVar7;
  float fVar8;
  undefined *puVar9;
  undefined8 uVar10;
  ulong uVar11;
  ulong uVar12;
  long lVar13;
  long lVar14;
  int iVar15;
  int iVar16;
  undefined4 uStack_90;
  uint uStack_8c;
  long lStack_88;
  long lStack_80;
  undefined8 uStack_78;
  
  puVar9 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  lVar13 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lVar13 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar13 = *(long *)puVar9;
  }
  uVar10 = CUIManager::rVoicePlayPriorityManager()(lVar13);
  uVar11 = CVoicePlayPriority::StopOtherCategoryVoice(unsigned int)(uVar10,0);
  if ((uVar11 & 1) != 0) {
    lStack_80 = 0;
    uStack_78 = 0;
    lStack_88 = 0;
    CMenuVoiceManager::GetPlaySEList(unsigned int, Framework::CSTLVector<unsigned int>&, unsigned int)(param_1,param_2,&lStack_88,param_3);
    lVar13 = lStack_88;
    if (lStack_88 != lStack_80) {
      uVar11 = Aska::Random(int, int)(0,(ulong)(lStack_80 - lStack_88) >> 2);
      uVar11 = uVar11 & 0xffffffff;
      if ((param_4 & 1) != 0) {
        piVar2 = *(int **)(param_1 + 0x10);
        lVar14 = lStack_80 - lStack_88;
        piVar6 = *(int **)(param_1 + 8);
        lVar13 = lStack_88;
        while (bVar7 = (ulong)(lVar14 >> 2) <= uVar11, piVar6 != piVar2) {
          if (bVar7) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar11);
            lVar13 = lStack_88;
          }
          if (*(int *)(lVar13 + uVar11 * 4) == *piVar6) goto code_r0x01ba9dcc;
          lVar14 = lStack_80 - lVar13;
          piVar6 = piVar6 + 2;
        }
        if (bVar7) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar11);
          lVar13 = lStack_88;
        }
        fVar8 = _UNK_027ebdd8;
        lVar14 = *(long *)(param_1 + 0x20);
        lVar3 = *(long *)(param_1 + 0x28);
        if (lVar14 != lVar3) {
          iVar5 = *(int *)(lVar13 + uVar11 * 4);
          iVar15 = -1;
          uVar10 = *(undefined8 *)
                    PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
          do {
            puVar4 = *(undefined8 **)(lVar14 + 0x20);
            for (puVar1 = *(undefined8 **)(lVar14 + 0x18); puVar1 != puVar4; puVar1 = puVar1 + 2) {
              iVar16 = iVar15;
              if ((*(int *)(puVar1 + 1) == iVar5) &&
                 (uVar12 = CSoundManager::IsPlaying(unsigned long) const(uVar10,*puVar1), (uVar12 & 1) != 0)) {
                iVar16 = 0x14;
                if (-1 < iVar15) {
                  iVar16 = iVar15;
                }
                CSoundManager::Stop(unsigned long, std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)(((float)iVar16 * fVar8) / 3.0,uVar10,*puVar1);
              }
              iVar15 = iVar16;
            }
            lVar14 = lVar14 + 0x38;
          } while (lVar14 != lVar3);
        }
      }
      if ((ulong)(lStack_80 - lStack_88 >> 2) <= uVar11) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar11);
      }
      uStack_90 = *(undefined4 *)(lStack_88 + uVar11 * 4);
      uStack_8c = CONCAT31(uStack_8c._1_3_,param_4) & 0xffffff01;
      puVar1 = *(undefined8 **)(param_1 + 0x10);
      if (puVar1 < *(undefined8 **)(param_1 + 0x18)) {
        if (puVar1 == (undefined8 *)0x0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
        }
        *puVar1 = CONCAT44(uStack_8c,uStack_90);
        *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + 8;
        lVar13 = lStack_88;
      }
      else {
        void std::__ndk1::vector<CMenuVoiceManager::ReserveData, Framework::CSTLAllocator<CMenuVoiceManager::ReserveData, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<CMenuVoiceManager::ReserveData&>(CMenuVoiceManager::ReserveData&)(param_1 + 8,&uStack_90);
        lVar13 = lStack_88;
      }
    }
code_r0x01ba9dcc:
    if (lVar13 != 0) {
      if (lStack_80 != lVar13) {
        lStack_80 = lStack_80 + (~((lStack_80 + -4) - lVar13) & 0xfffffffffffffffcU);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
  }
  return;
}

// ==== CMenuVoiceManager::GetPlaySEList(unsigned int, Framework::CSTLVector<unsigned int>&, unsigned int)
// vaddr 0x1aa9e1c | ghidra 0x1ba9e1c | size 1308 | symbol _ZN17CMenuVoiceManager13GetPlaySEListEjRN9Framework10CSTLVectorIjEEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManager13GetPlaySEListEjRN9Framework10CSTLVectorIjEEj
               (undefined8 param_1,undefined4 param_2,long param_3,int param_4)

{
  ulong *puVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  undefined *puVar5;
  ulong uVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  uint uVar11;
  undefined8 *puVar12;
  undefined8 *puVar13;
  long lVar14;
  undefined8 *puVar15;
  undefined8 uVar16;
  undefined8 *puVar17;
  undefined8 *puVar18;
  long *plVar19;
  long lVar20;
  long lVar21;
  long lStack_1b0;
  undefined8 uStack_1a8;
  long *plStack_1a0;
  undefined8 uStack_198;
  undefined4 uStack_190;
  undefined *puStack_188;
  undefined8 uStack_180;
  ulong *puStack_178;
  undefined8 uStack_170;
  undefined4 uStack_168;
  undefined1 uStack_164;
  ulong uStack_160;
  ulong uStack_158;
  ulong uStack_150;
  
  puVar5 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar8 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar8 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar8 = *(long *)puVar5;
  }
  uStack_1a8 = 0;
  lStack_1b0 = 0;
  uStack_198 = 0;
  plStack_1a0 = (long *)0x0;
  uStack_190 = 0x3f800000;
  uVar16 = *(undefined8 *)(*(long *)(lVar8 + 0x5f8) + 0x430);
  snprintf(&uStack_160,0x100,&UNK_027e6d32/*"%u"*/,param_2);
  puStack_188 = &UNK_028472c9/*"menu_voice_type"*/;
  uStack_180 = 0xf;
  puStack_178 = &uStack_160;
  uStack_170 = strlen(&uStack_160);
  uStack_168 = 0;
  uStack_164 = 0;
  CMasterParameterBaseSqlite_Simple<CMasterParameterMenuCommonVoiceElement>::ParameterByQuery(char const*, Framework::CSTLUnorderedMap<unsigned int, CMasterParameterMenuCommonVoiceElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >&, Aska::Yayoi::QueryParam*, unsigned int) const(uVar16,&UNK_028d2484/*"SELECT * FROM master_menu_common_voice WHERE menu_voice_type=?"*/,&lStack_1b0,&puStack_188,1);
  if (plStack_1a0 == (long *)0x0) {
    puVar12 = (undefined8 *)0x0;
    puVar17 = (undefined8 *)0x0;
  }
  else {
    puVar15 = (undefined8 *)0x0;
    uVar9 = (ulong)&uStack_160 | 1;
    puVar13 = (undefined8 *)0x0;
    puVar18 = (undefined8 *)0x0;
    plVar19 = plStack_1a0;
    do {
      uStack_158 = 0;
      uStack_150 = 0;
      uStack_160 = 0;
      void CParameterPropertyBase<54u>::CryptString<string >(string&, string const&)(&uStack_160,plVar19 + 0x38);
      uStack_180 = 0;
      puStack_178 = (ulong *)0x0;
      puStack_188 = (undefined *)0x0;
      void CParameterPropertyBase<55u>::CryptString<string >(string&, string const&)(&puStack_188,plVar19 + 0x40);
      uVar6 = CUIUtility::IsWithinDayEnableEmpty(string const&, string const&)(&uStack_160,&puStack_188);
      if (((ulong)puStack_188 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_178);
      }
      if ((uStack_160 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_150);
      }
      puVar12 = puVar13;
      puVar17 = puVar18;
      if ((uVar6 & 1) != 0) {
        iVar3 = (int)plVar19[0x1e];
        if ((iVar3 - 5U < 2) || (iVar3 == 2)) {
          uVar6 = CUIUtility::IsMenuVoiceCoroEnable()();
joined_r0x01ba9fe0:
          if ((uVar6 & 1) == 0) goto code_r0x01baa238;
        }
        else if (iVar3 == 1) {
          uVar6 = CUIUtility::IsMenuVoiceEveleashEnable()();
          goto joined_r0x01ba9fe0;
        }
        uVar6 = CUIUtility::IsMenuVoiceOtherEnable()();
        if ((uVar6 & 1) != 0) {
          lVar8 = plVar19[0x1e];
          uStack_180 = 0;
          puStack_178 = (ulong *)0x0;
          puStack_188 = (undefined *)0x0;
          void CParameterPropertyBase<51u>::CryptString<string >(string&, string const&)(&puStack_188,plVar19 + 0x2a);
          uStack_158 = 0;
          uStack_150 = 0;
          uStack_160 = 0;
          puVar1 = (ulong *)((ulong)&puStack_188 | 1);
          if (((ulong)puStack_188 & 1) != 0) {
            puVar1 = puStack_178;
          }
          uVar6 = strlen(puVar1);
          if (uVar6 < 0x17) {
            uStack_160 = CONCAT71(uStack_160._1_7_,(char)(uVar6 << 1));
            uVar7 = uVar9;
            if (uVar6 != 0) goto code_r0x01baa0c0;
          }
          else {
            uVar10 = uVar6 + 0x10 & 0xfffffffffffffff0;
            if (uVar10 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
            }
            uVar7 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar10,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
            if (uVar7 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
            }
            uStack_160 = uVar10 | 1;
            uStack_158 = uVar6;
            uStack_150 = uVar7;
code_r0x01baa0c0:
            memcpy(uVar7,puVar1,uVar6);
          }
          *(undefined1 *)(uVar7 + uVar6) = 0;
          uVar6 = CMenuVoiceManager::IsChangeSoundPackage(unsigned int, string const&, unsigned int)(param_1,(int)lVar8,&uStack_160,(int)plVar19[0x32]);
          if ((uVar6 & 1) == 0) {
            if ((uStack_160 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_150);
            }
            if (((ulong)puStack_188 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_178);
            }
          }
          else {
            lVar8 = plVar19[0x1e];
            if ((uStack_160 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_150);
            }
            if (((ulong)puStack_188 & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_178);
            }
            if ((int)lVar8 != param_4) goto code_r0x01baa238;
          }
          lVar8 = plVar19[10];
          lVar14 = plVar19[0x18];
          if (puVar18 < puVar15) {
            if (puVar18 == (undefined8 *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
            }
            *puVar18 = CONCAT44((int)lVar14,(int)lVar8);
            puVar17 = puVar18 + 1;
          }
          else {
            lVar21 = (long)puVar18 - (long)puVar13 >> 3;
            if ((ulong)((long)puVar15 - (long)puVar13 >> 3) < 0xfffffffffffffff) {
              uVar10 = (long)puVar15 - (long)puVar13 >> 2;
              uVar6 = lVar21 + 1U;
              if (lVar21 + 1U <= uVar10) {
                uVar6 = uVar10;
              }
              if (uVar6 != 0) goto code_r0x01baa1bc;
              lVar20 = 0;
              puVar12 = (undefined8 *)(lVar21 << 3);
            }
            else {
              uVar6 = 0x1fffffffffffffff;
code_r0x01baa1bc:
              lVar20 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6 << 3,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
              if (lVar20 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
                puVar12 = (undefined8 *)(lVar21 * 8);
              }
              else {
                puVar12 = (undefined8 *)(lVar20 + lVar21 * 8);
              }
            }
            if (puVar12 == (undefined8 *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
            }
            puVar15 = (undefined8 *)(lVar20 + uVar6 * 8);
            puVar17 = puVar12 + 1;
            *puVar12 = CONCAT44((int)lVar14,(int)lVar8);
            while (puVar18 != puVar13) {
              puVar18 = puVar18 + -1;
              puVar12[-1] = *puVar18;
              puVar12 = puVar12 + -1;
            }
            if (puVar13 != (undefined8 *)0x0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar13);
            }
          }
        }
      }
code_r0x01baa238:
      plVar19 = (long *)*plVar19;
      puVar13 = puVar12;
      puVar18 = puVar17;
    } while (plVar19 != (long *)0x0);
  }
  void std::__ndk1::vector<CMenuVoiceManager::PlayingData, Framework::CSTLAllocator<CMenuVoiceManager::PlayingData, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<CMenuVoiceManager::PlayingData const&>(CMenuVoiceManager::PlayingData const&)+0x1c0(puVar12,puVar17);
  if (puVar12 != puVar17) {
    puVar15 = puVar12;
    uVar11 = 0;
    do {
      uVar4 = *(uint *)((long)puVar15 + 4);
      if (uVar4 < uVar11) break;
      puVar2 = *(undefined4 **)(param_3 + 8);
      if (puVar2 < *(undefined4 **)(param_3 + 0x10)) {
        if (puVar2 == (undefined4 *)0x0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
        }
        *puVar2 = *(undefined4 *)puVar15;
        *(long *)(param_3 + 8) = *(long *)(param_3 + 8) + 4;
      }
      else {
        void std::__ndk1::vector<unsigned int, Framework::CSTLAllocator<unsigned int, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<unsigned int&>(unsigned int&)(param_3,puVar15);
      }
      puVar15 = puVar15 + 1;
      uVar11 = uVar4;
    } while (puVar15 != puVar17);
  }
  lVar8 = lStack_1b0;
  plVar19 = plStack_1a0;
  if (puVar12 != (undefined8 *)0x0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar12);
    lVar8 = lStack_1b0;
    plVar19 = plStack_1a0;
  }
  while (plVar19 != (long *)0x0) {
    lVar14 = *plVar19;
    lStack_1b0 = lVar8;
    CMasterParameterMenuCommonVoiceElement::~CMasterParameterMenuCommonVoiceElement()(plVar19 + 3);
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar19);
    lVar8 = lStack_1b0;
    plVar19 = (long *)lVar14;
  }
  lStack_1b0 = 0;
  if (lVar8 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  return;
}

// ==== CMenuVoiceManager::StopPlayingVoice(unsigned int, int)
// vaddr 0x1aaa338 | ghidra 0x1baa338 | size 196 | symbol _ZN17CMenuVoiceManager16StopPlayingVoiceEji | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN17CMenuVoiceManager16StopPlayingVoiceEji(long param_1,int param_2,int param_3)

{
  undefined8 *puVar1;
  long lVar2;
  undefined8 *puVar3;
  float fVar4;
  ulong uVar5;
  int iVar6;
  undefined8 uVar7;
  long lVar8;
  
  fVar4 = _UNK_027ebdd8;
  lVar8 = *(long *)(param_1 + 0x20);
  lVar2 = *(long *)(param_1 + 0x28);
  if (lVar8 != lVar2) {
    uVar7 = *(undefined8 *)PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
    do {
      puVar3 = *(undefined8 **)(lVar8 + 0x20);
      for (puVar1 = *(undefined8 **)(lVar8 + 0x18); puVar1 != puVar3; puVar1 = puVar1 + 2) {
        iVar6 = param_3;
        if ((*(int *)(puVar1 + 1) == param_2) &&
           (uVar5 = CSoundManager::IsPlaying(unsigned long) const(uVar7,*puVar1), (uVar5 & 1) != 0)) {
          iVar6 = 0x14;
          if (-1 < param_3) {
            iVar6 = param_3;
          }
          CSoundManager::Stop(unsigned long, std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)(((float)iVar6 * fVar4) / 3.0,uVar7,*puVar1);
        }
        param_3 = iVar6;
      }
      lVar8 = lVar8 + 0x38;
    } while (lVar8 != lVar2);
  }
  return;
}

// ==== CMenuVoiceManager::PlayVoiceFromID(char const*, bool, int)
// vaddr 0x1aaa3fc | ghidra 0x1baa3fc | size 80 | symbol _ZN17CMenuVoiceManager15PlayVoiceFromIDEPKcbi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManager15PlayVoiceFromIDEPKcbi
               (undefined8 param_1,undefined8 param_2,uint param_3)

{
  undefined4 uVar1;
  undefined1 auStack_30 [16];
  
  Framework::CHash32::CHash32(char const*)(auStack_30);
  uVar1 = Framework::CHash32::operator unsigned int() const(auStack_30);
  Framework::CHash32::~CHash32()(auStack_30);
  CMenuVoiceManager::PlayVoiceFromMasterID(unsigned int, bool, int)(param_1,uVar1,param_3 & 1);
  return;
}

// ==== CMenuVoiceManager::PlayVoiceFromMasterID(unsigned int, bool, int)
// vaddr 0x1aaa44c | ghidra 0x1baa44c | size 832 | symbol _ZN17CMenuVoiceManager21PlayVoiceFromMasterIDEjbi | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN17CMenuVoiceManager21PlayVoiceFromMasterIDEjbi(long param_1,int param_2,byte param_3)

{
  undefined8 *puVar1;
  ulong *puVar2;
  long lVar3;
  undefined8 *puVar4;
  undefined4 uVar5;
  int *piVar6;
  float fVar7;
  undefined *puVar8;
  bool bVar9;
  undefined8 uVar10;
  ulong uVar11;
  long lVar12;
  int iVar13;
  int iVar14;
  long lStack_1a8;
  long lStack_1a0;
  undefined *puStack_198;
  undefined8 uStack_190;
  undefined8 *puStack_188;
  undefined8 uStack_180;
  undefined4 uStack_178;
  undefined1 uStack_174;
  undefined8 uStack_170;
  undefined8 uStack_168;
  ulong uStack_160;
  
  puVar8 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  lVar12 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lVar12 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar12 = *(long *)puVar8;
  }
  uVar10 = CUIManager::rVoicePlayPriorityManager()(lVar12);
  uVar11 = CVoicePlayPriority::StopOtherCategoryVoice(unsigned int)(uVar10,0);
  fVar7 = _UNK_027ebdd8;
  if ((uVar11 & 1) == 0) {
    return;
  }
  if ((param_3 & 1) != 0) {
    piVar6 = *(int **)(param_1 + 8);
    while (piVar6 != *(int **)(param_1 + 0x10)) {
      iVar13 = *piVar6;
      piVar6 = piVar6 + 2;
      if (iVar13 == param_2) {
        return;
      }
    }
    lVar12 = *(long *)(param_1 + 0x20);
    lVar3 = *(long *)(param_1 + 0x28);
    if (lVar12 != lVar3) {
      iVar13 = -1;
      uVar10 = *(undefined8 *)PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
      do {
        puVar4 = *(undefined8 **)(lVar12 + 0x20);
        for (puVar1 = *(undefined8 **)(lVar12 + 0x18); puVar1 != puVar4; puVar1 = puVar1 + 2) {
          iVar14 = iVar13;
          if ((*(int *)(puVar1 + 1) == param_2) &&
             (uVar11 = CSoundManager::IsPlaying(unsigned long) const(uVar10,*puVar1), (uVar11 & 1) != 0)) {
            iVar14 = 0x14;
            if (-1 < iVar13) {
              iVar14 = iVar13;
            }
            CSoundManager::Stop(unsigned long, std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)(((float)iVar14 * fVar7) / 3.0,uVar10,*puVar1);
          }
          iVar13 = iVar14;
        }
        lVar12 = lVar12 + 0x38;
      } while (lVar12 != lVar3);
    }
  }
  puVar8 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar12 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar12 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar12 = *(long *)puVar8;
  }
  uVar10 = *(undefined8 *)(*(long *)(lVar12 + 0x5f8) + 0x430);
  snprintf(&uStack_170,0x100,&UNK_027e6d32/*"%u"*/,param_2);
  puStack_198 = &UNK_027ffe64/*"id"*/;
  uStack_190 = 2;
  puStack_188 = &uStack_170;
  uStack_180 = strlen(&uStack_170);
  uStack_178 = 0;
  uStack_174 = 0;
  CMasterParameterBaseSqlite_Simple<CMasterParameterMenuCommonVoiceElement>::ParameterByQuery(char const*, Aska::Yayoi::QueryParam*, unsigned int) const(&lStack_1a8,uVar10,&UNK_028d2452/*"SELECT * FROM master_menu_common_voice WHERE id=?"*/,&puStack_198,1);
  if (lStack_1a8 == 0) goto joined_r0x01baa760;
  iVar13 = *(int *)(lStack_1a8 + 0xd8);
  if ((iVar13 - 5U < 2) || (iVar13 == 2)) {
    uVar11 = CUIUtility::IsMenuVoiceCoroEnable()();
joined_r0x01baa634:
    if ((uVar11 & 1) == 0) goto joined_r0x01baa760;
  }
  else if (iVar13 == 1) {
    uVar11 = CUIUtility::IsMenuVoiceEveleashEnable()();
    goto joined_r0x01baa634;
  }
  uVar11 = CUIUtility::IsMenuVoiceOtherEnable()();
  if ((uVar11 & 1) == 0) goto joined_r0x01baa760;
  uStack_170 = 0;
  uStack_168 = 0;
  uStack_160 = 0;
  void CParameterPropertyBase<51u>::CryptString<string >(string&, string const&)(&uStack_170,lStack_1a8 + 0x138);
  if ((uStack_170 & 1) == 0) {
    uVar11 = (ulong)&uStack_170 | 1;
code_r0x01baa67c:
    lVar12 = *(long *)puVar8;
    uVar5 = *(undefined4 *)(lStack_1a8 + 0x178);
    if (lVar12 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028d240a/*"C:\BAS_Submission\Client\Project\..\Source\Game\UI\MenuVoiceManager.cpp"*/,0x3c1,&UNK_027fd285/*"pParameterManager is null."*/);
    }
    lVar12 = CParameterManager::pParameterSound() const(lVar12);
    if (lVar12 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028d240a/*"C:\BAS_Submission\Client\Project\..\Source\Game\UI\MenuVoiceManager.cpp"*/,0x3c4,&UNK_027fd2a0/*"pParameterSound is null."*/);
    }
    lVar12 = CParameterSound::pParameter(char const*, unsigned int) const(lVar12,uVar11,uVar5);
    bVar9 = lVar12 != 0;
  }
  else {
    bVar9 = false;
    uVar11 = uStack_160;
    if (uStack_160 != 0) goto code_r0x01baa67c;
  }
  if (((byte)uStack_170 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_160);
  }
  if (bVar9) {
    uStack_170 = CONCAT44(CONCAT31(uStack_170._5_3_,param_3),*(undefined4 *)(lStack_1a8 + 0x38)) &
                 0xffffff01ffffffff;
    puVar2 = *(ulong **)(param_1 + 0x10);
    if (puVar2 < *(ulong **)(param_1 + 0x18)) {
      if (puVar2 == (ulong *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar2 = uStack_170;
      *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + 8;
    }
    else {
      void std::__ndk1::vector<CMenuVoiceManager::ReserveData, Framework::CSTLAllocator<CMenuVoiceManager::ReserveData, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<CMenuVoiceManager::ReserveData&>(CMenuVoiceManager::ReserveData&)(param_1 + 8,&uStack_170);
    }
  }
joined_r0x01baa760:
  if (lStack_1a0 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return;
}

// ==== CMenuVoiceManager::IsSystemSettingMenuVoiceEnable(unsigned int)
// vaddr 0x1aaa78c | ghidra 0x1baa78c | size 68 | symbol _ZN17CMenuVoiceManager30IsSystemSettingMenuVoiceEnableEj | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN17CMenuVoiceManager30IsSystemSettingMenuVoiceEnableEj(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  ulong uVar2;
  
  if ((param_2 - 5U < 2) || (param_2 == 2)) {
    uVar2 = CUIUtility::IsMenuVoiceCoroEnable()();
  }
  else {
    if (param_2 != 1) goto code_r0x011d2370;
    uVar2 = CUIUtility::IsMenuVoiceEveleashEnable()();
  }
  if ((uVar2 & 1) == 0) {
    return 0;
  }
code_r0x011d2370:
  uVar1 = (*(code *)PTR__ZN10CUIUtility22IsMenuVoiceOtherEnableEv_02ca11a8)();
  return uVar1;
}

// ==== CMenuVoiceManager::IsExistResourcePackage(char const*, unsigned int)
// vaddr 0x1aaa7d0 | ghidra 0x1baa7d0 | size 144 | symbol _ZN17CMenuVoiceManager22IsExistResourcePackageEPKcj | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN17CMenuVoiceManager22IsExistResourcePackageEPKcj
               (undefined8 param_1,long param_2,undefined4 param_3)

{
  bool bVar1;
  long lVar2;
  
  if (param_2 == 0) {
    bVar1 = false;
  }
  else {
    lVar2 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028d240a/*"C:\BAS_Submission\Client\Project\..\Source\Game\UI\MenuVoiceManager.cpp"*/,0x3c1,&UNK_027fd285/*"pParameterManager is null."*/);
    }
    lVar2 = CParameterManager::pParameterSound() const(lVar2);
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028d240a/*"C:\BAS_Submission\Client\Project\..\Source\Game\UI\MenuVoiceManager.cpp"*/,0x3c4,&UNK_027fd2a0/*"pParameterSound is null."*/);
    }
    lVar2 = CParameterSound::pParameter(char const*, unsigned int) const(lVar2,param_2,param_3);
    bVar1 = lVar2 != 0;
  }
  return bVar1;
}

// ==== CMenuVoiceManager::AddResourcePackFromMenuID(unsigned int, unsigned int)
// vaddr 0x1aaa860 | ghidra 0x1baa860 | size 1004 | symbol _ZN17CMenuVoiceManager25AddResourcePackFromMenuIDEjj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManager25AddResourcePackFromMenuIDEjj
               (long param_1,undefined8 param_2,undefined4 param_3)

{
  undefined8 *puVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  ulong uVar5;
  byte *pbVar6;
  byte *pbVar7;
  undefined8 uVar8;
  byte *pbVar9;
  long lVar10;
  byte *pbVar11;
  ulong uVar12;
  byte *pbVar13;
  ulong *puVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined8 uStack_98;
  ulong uStack_90;
  undefined8 uStack_88;
  byte *pbStack_80;
  byte *pbStack_78;
  byte *pbStack_70;
  undefined8 uStack_68;
  
  pbStack_70 = (byte *)0x0;
  uStack_68 = 0;
  pbStack_78 = (byte *)0x0;
  CMenuVoiceManager::MakeResourceList(unsigned int, Framework::CSTLVector<string >&, unsigned int)(param_1,param_2,&pbStack_78,param_3);
  pbVar9 = pbStack_80;
  pbVar7 = pbStack_78;
  pbVar13 = pbStack_78;
  if (pbStack_78 != pbStack_70) {
    pbVar9 = pbStack_78;
    do {
      pbVar7 = *(byte **)(param_1 + 0x38);
      pbVar13 = *(byte **)(param_1 + 0x40);
      pbStack_80 = pbVar9;
      if (pbVar13 == pbVar7) {
code_r0x01baa964:
        if ((*pbVar9 & 1) == 0) {
          pbVar7 = pbVar9 + 1;
        }
        else {
          pbVar7 = *(byte **)(pbVar9 + 0x10);
        }
        CSoundManager::AddResource(char const*, bool)(*(undefined8 *)
                         PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358,
                        pbVar7,0);
        uStack_90 = 0;
        uStack_88 = 0;
        uStack_98 = 0;
        if ((*pbVar9 & 1) == 0) {
          pbVar9 = pbVar9 + 1;
        }
        else {
          pbVar9 = *(byte **)(pbVar9 + 0x10);
        }
        uStack_a0 = (int)param_2;
        uStack_9c = param_3;
        uVar5 = strlen(pbVar9);
        if (uVar5 < 0x16 || uVar5 - 0x16 == 0) {
          if (uVar5 != 0) {
            memmove((long)&uStack_98 + 1,pbVar9,uVar5);
          }
          *(undefined1 *)((long)&uStack_98 + uVar5 + 1) = 0;
          uStack_98 = CONCAT71(uStack_98._1_7_,(char)(uVar5 << 1));
        }
        else {
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_98,0x16,uVar5 - 0x16,0,0,0,uVar5,pbVar9);
        }
        puVar1 = *(undefined8 **)(param_1 + 0x70);
        if (puVar1 < *(undefined8 **)(param_1 + 0x78)) {
          if (puVar1 == (undefined8 *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          uVar8 = uStack_88;
          uVar5 = uStack_90;
          *puVar1 = CONCAT44(uStack_9c,uStack_a0);
          puVar14 = puVar1 + 1;
          *puVar14 = 0;
          puVar1[2] = 0;
          puVar1[3] = 0;
          if ((uStack_98 & 1) == 0) {
            puVar1[3] = uStack_88;
            puVar1[2] = uStack_90;
            *puVar14 = uStack_98;
          }
          else {
            if (uStack_90 < 0x17) {
              lVar10 = (long)puVar1 + 9;
              *(char *)puVar14 = (char)(uStack_90 << 1);
              if (uStack_90 != 0) goto code_r0x01baab94;
            }
            else {
              uVar12 = uStack_90 + 0x10 & 0xfffffffffffffff0;
              if (uVar12 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
              }
              lVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar12,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
              if (lVar10 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
              }
              puVar1[2] = uVar5;
              puVar1[3] = lVar10;
              puVar1[1] = uVar12 | 1;
code_r0x01baab94:
              memcpy(lVar10,uVar8,uVar5);
            }
            *(undefined1 *)(lVar10 + uVar5) = 0;
          }
          *(long *)(param_1 + 0x70) = *(long *)(param_1 + 0x70) + 0x20;
        }
        else {
          void std::__ndk1::vector<CMenuVoiceManager::ResourceData, Framework::CSTLAllocator<CMenuVoiceManager::ResourceData, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<CMenuVoiceManager::ResourceData&>(CMenuVoiceManager::ResourceData&)(param_1 + 0x68,&uStack_a0);
        }
        if ((uStack_98 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_88);
        }
      }
      else {
        bVar2 = *pbVar9;
        uVar5 = (ulong)(bVar2 >> 1);
        if ((bVar2 & 1) != 0) {
          uVar5 = *(ulong *)(pbVar9 + 8);
        }
code_r0x01baa8e4:
        bVar3 = *pbVar7;
        uVar12 = (ulong)(bVar3 >> 1);
        if ((bVar3 & 1) != 0) {
          uVar12 = *(ulong *)(pbVar7 + 8);
        }
        if (uVar12 != uVar5) goto code_r0x01baa958;
        pbVar11 = *(byte **)(pbVar7 + 0x10);
        if ((bVar3 & 1) == 0) {
          pbVar11 = pbVar7 + 1;
        }
        pbVar6 = pbVar9 + 1;
        if ((bVar2 & 1) != 0) {
          pbVar6 = *(byte **)(pbVar9 + 0x10);
        }
        if ((bVar3 & 1) == 0) {
          if (uVar12 != 0) {
            lVar10 = -(ulong)(bVar3 >> 1);
            pbVar11 = pbVar7;
            while (pbVar11 = pbVar11 + 1, *pbVar11 == *pbVar6) {
              lVar10 = lVar10 + 1;
              pbVar6 = pbVar6 + 1;
              if (lVar10 == 0) goto code_r0x01baa980;
            }
            goto code_r0x01baa958;
          }
        }
        else if ((uVar12 != 0) && (iVar4 = memcmp(pbVar11), iVar4 != 0))
        goto code_r0x01baa958;
code_r0x01baa980:
        if (pbVar7 + 0x18 != pbVar13) {
          pbVar9 = pbVar7;
          do {
            if ((*pbVar9 & 1) == 0) {
              pbVar9[0] = 0;
              pbVar9[1] = 0;
            }
            else {
              **(undefined1 **)(pbVar9 + 0x10) = 0;
              pbVar9[8] = 0;
              pbVar9[9] = 0;
              pbVar9[10] = 0;
              pbVar9[0xb] = 0;
              pbVar9[0xc] = 0;
              pbVar9[0xd] = 0;
              pbVar9[0xe] = 0;
              pbVar9[0xf] = 0;
            }
            string::reserve(unsigned long)(pbVar9,0);
            uVar8 = *(undefined8 *)(pbVar9 + 0x28);
            uVar16 = *(undefined8 *)(pbVar9 + 0x20);
            uVar15 = *(undefined8 *)(pbVar9 + 0x18);
            pbVar7 = pbVar9 + 0x18;
            pbVar9[0x20] = 0;
            pbVar9[0x21] = 0;
            pbVar9[0x22] = 0;
            pbVar9[0x23] = 0;
            pbVar9[0x24] = 0;
            pbVar9[0x25] = 0;
            pbVar9[0x26] = 0;
            pbVar9[0x27] = 0;
            pbVar9[0x28] = 0;
            pbVar9[0x29] = 0;
            pbVar9[0x2a] = 0;
            pbVar9[0x2b] = 0;
            pbVar9[0x2c] = 0;
            pbVar9[0x2d] = 0;
            pbVar9[0x2e] = 0;
            pbVar9[0x2f] = 0;
            *(undefined8 *)(pbVar9 + 0x10) = uVar8;
            pbVar9[0x18] = 0;
            pbVar9[0x19] = 0;
            pbVar9[0x1a] = 0;
            pbVar9[0x1b] = 0;
            pbVar9[0x1c] = 0;
            pbVar9[0x1d] = 0;
            pbVar9[0x1e] = 0;
            pbVar9[0x1f] = 0;
            *(undefined8 *)(pbVar9 + 8) = uVar16;
            *(undefined8 *)pbVar9 = uVar15;
            pbVar9 = pbVar7;
          } while (pbVar13 + -0x18 != pbVar7);
          pbVar13 = *(byte **)(param_1 + 0x40);
          if (*(byte **)(param_1 + 0x40) == pbVar7) goto code_r0x01baabc4;
        }
        do {
          pbVar9 = pbVar13 + -0x18;
          *(byte **)(param_1 + 0x40) = pbVar9;
          if ((pbVar13[-0x18] & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(pbVar13 + -8));
            pbVar9 = *(byte **)(param_1 + 0x40);
          }
          pbVar13 = pbVar9;
        } while (pbVar9 != pbVar7);
      }
code_r0x01baabc4:
      pbVar9 = pbStack_80 + 0x18;
      pbVar7 = pbVar9;
      pbVar13 = pbStack_78;
    } while (pbVar9 != pbStack_70);
  }
  pbStack_80 = pbVar9;
  pbStack_78 = pbVar13;
  if (pbVar13 != (byte *)0x0) {
    while (pbVar9 = pbVar7, pbVar9 != pbVar13) {
      pbStack_70 = pbVar9 + -0x18;
      pbVar7 = pbStack_70;
      if ((pbVar9[-0x18] & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(pbVar9 + -8));
        pbVar7 = pbStack_70;
      }
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pbStack_78);
  }
  return;
code_r0x01baa958:
  pbVar7 = pbVar7 + 0x18;
  if (pbVar13 == pbVar7) goto code_r0x01baa964;
  goto code_r0x01baa8e4;
}

// ==== CMenuVoiceManager::MakeResourceList(unsigned int, Framework::CSTLVector<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >&, unsigned int)
// vaddr 0x1aaac4c | ghidra 0x1baac4c | size 1308 | symbol _ZN17CMenuVoiceManager16MakeResourceListEjRN9Framework10CSTLVectorINSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEEEEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManager16MakeResourceListEjRN9Framework10CSTLVectorINSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEEEEj
               (undefined8 param_1,undefined8 param_2,long *param_3)

{
  ulong uVar1;
  ulong *puVar2;
  undefined8 uVar3;
  long lVar4;
  undefined *puVar5;
  undefined8 *puVar6;
  bool bVar7;
  undefined8 *puVar8;
  undefined4 *puVar9;
  ulong uVar10;
  undefined1 *puVar11;
  long lVar12;
  long lVar13;
  ulong uVar14;
  long *plVar15;
  undefined8 *puVar16;
  ulong uVar17;
  ulong uStack_2e8;
  ulong uStack_2e0;
  ulong uStack_2d8;
  ulong uStack_2d0;
  undefined4 uStack_2c8;
  undefined1 auStack_1a0 [208];
  long lStack_d0;
  undefined8 uStack_c8;
  long *plStack_c0;
  undefined8 uStack_b8;
  undefined4 uStack_b0;
  undefined8 *puStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  long lStack_90;
  long lStack_88;
  undefined8 uStack_80;
  ulong uStack_78;
  ulong uStack_70;
  undefined1 *puStack_68;
  
  uStack_80 = 0;
  lStack_88 = 0;
  lStack_90 = 0;
  CMenuVoiceManager::GetPlaySEList(unsigned int, Framework::CSTLVector<unsigned int>&, unsigned int)(param_1,param_2,&lStack_90);
  puVar5 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  uStack_98 = 0;
  uStack_a0 = 0;
  lVar12 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  uStack_c8 = 0;
  lStack_d0 = 0;
  uStack_b8 = 0;
  plStack_c0 = (long *)0x0;
  uStack_b0 = 0x3f800000;
  puStack_a8 = &uStack_a0;
  if (lVar12 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar12 = *(long *)puVar5;
  }
  CMasterParameterMenuCommonVoice::ParameterByIDList(Framework::CSTLVector<unsigned int>&, Framework::CSTLUnorderedMap<unsigned int, CMasterParameterMenuCommonVoiceElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >&) const(*(undefined8 *)(*(long *)(lVar12 + 0x5f8) + 0x430),&lStack_90,&lStack_d0);
  if (plStack_c0 != (long *)0x0) {
    plVar15 = plStack_c0;
    do {
      uStack_2e0 = CONCAT44(uStack_2e0._4_4_,(int)plVar15[2]);
      CMasterParameterMenuCommonVoiceElement::CMasterParameterMenuCommonVoiceElement(CMasterParameterMenuCommonVoiceElement const&)(&uStack_2d8,plVar15 + 3);
      puStack_68 = (undefined1 *)0x0;
      uStack_70 = 0;
      uStack_78 = 0;
      void CParameterPropertyBase<51u>::CryptString<string >(string&, string const&)(&uStack_78,auStack_1a0);
      puVar8 = (undefined8 *)std::__ndk1::__tree_iterator<std::__ndk1::__value_type<string, unsigned int>, std::__ndk1::__tree_node<std::__ndk1::__value_type<string, unsigned int>, void*>*, long> std::__ndk1::__tree<std::__ndk1::__value_type<string, unsigned int>, std::__ndk1::__map_value_compare<string, std::__ndk1::__value_type<string, unsigned int>, std::__ndk1::less<string >, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<string, unsigned int>, Framework::CSTLMapAllocatorInf> >::find<string >(string const&)(&puStack_a8,&uStack_78);
      if ((uStack_78 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_68);
      }
      if (puVar8 == &uStack_a0) {
        puStack_68 = (undefined1 *)0x0;
        uStack_70 = 0;
        uStack_78 = 0;
        void CParameterPropertyBase<51u>::CryptString<string >(string&, string const&)(&uStack_78,auStack_1a0);
        puVar9 = (undefined4 *)std::__ndk1::map<string, unsigned int, std::__ndk1::less<string >, Framework::CSTLAllocator<std::__ndk1::pair<string const, unsigned int>, Framework::CSTLMapAllocatorInf> >::operator[](string&&)(&puStack_a8,&uStack_78);
        *puVar9 = 0;
        if ((uStack_78 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_68);
        }
      }
      CMasterParameterMenuCommonVoiceElement::~CMasterParameterMenuCommonVoiceElement()(&uStack_2d8);
      plVar15 = (long *)*plVar15;
    } while (plVar15 != (long *)0x0);
  }
  lVar12 = *param_3;
  lVar13 = param_3[1];
  puVar8 = puStack_a8;
  while (lVar4 = lVar13, puStack_a8 = puVar8, lVar4 != lVar12) {
    param_3[1] = lVar4 + -0x18;
    lVar13 = lVar4 + -0x18;
    if ((*(byte *)(lVar4 + -0x18) & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar4 + -8));
      lVar13 = param_3[1];
      puVar8 = puStack_a8;
    }
  }
  lVar12 = lStack_d0;
  plVar15 = plStack_c0;
  if (puVar8 != &uStack_a0) {
    uVar14 = (ulong)&uStack_2e0 | 1;
    do {
      uStack_2d8 = 0;
      uStack_2d0 = 0;
      uStack_2e0 = 0;
      if ((puVar8[4] & 1) == 0) {
        uStack_2d0 = puVar8[6];
        uStack_2d8 = puVar8[5];
        uStack_2e0 = puVar8[4];
      }
      else {
        uVar1 = puVar8[5];
        uVar3 = puVar8[6];
        if (uVar1 < 0x17) {
          uStack_2e0 = (uVar1 & 0x7f) << 1;
          uVar17 = uVar14;
          if (uVar1 != 0) goto code_r0x01baae9c;
        }
        else {
          uVar10 = uVar1 + 0x10 & 0xfffffffffffffff0;
          if (uVar10 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          uVar17 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar10,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (uVar17 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uStack_2e0 = uVar10 | 1;
          uStack_2d8 = uVar1;
          uStack_2d0 = uVar17;
code_r0x01baae9c:
          memcpy(uVar17,uVar3,uVar1);
        }
        *(undefined1 *)(uVar17 + uVar1) = 0;
      }
      uStack_2c8 = *(undefined4 *)(puVar8 + 7);
      uVar1 = uVar14;
      if ((uStack_2e0 & 1) != 0) {
        uVar1 = uStack_2d0;
      }
      puVar2 = (ulong *)param_3[1];
      uStack_2e8 = uVar1;
      if (puVar2 < (ulong *)param_3[2]) {
        puStack_68 = (undefined1 *)0x0;
        uStack_70 = 0;
        uStack_78 = 0;
        uVar10 = strlen(uVar1);
        if (uVar10 < 0x17) {
          uStack_78 = CONCAT71(uStack_78._1_7_,(char)(uVar10 << 1));
          puVar11 = (undefined1 *)((ulong)&uStack_78 | 1);
          if (uVar10 != 0) goto code_r0x01baafb0;
          *(undefined1 *)((ulong)&uStack_78 | 1) = 0;
        }
        else {
          uVar17 = uVar10 + 0x10 & 0xfffffffffffffff0;
          if (uVar17 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          puVar11 = (undefined1 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar17,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (puVar11 == (undefined1 *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uStack_78 = uVar17 | 1;
          uStack_70 = uVar10;
          puStack_68 = puVar11;
code_r0x01baafb0:
          memcpy(puVar11,uVar1,uVar10);
          puVar11[uVar10] = 0;
        }
        if (puVar2 == (ulong *)0x0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
        }
        puVar11 = puStack_68;
        uVar1 = uStack_70;
        puVar2[1] = 0;
        puVar2[2] = 0;
        *puVar2 = 0;
        if ((uStack_78 & 1) == 0) {
          puVar2[2] = (ulong)puStack_68;
          puVar2[1] = uStack_70;
          *puVar2 = uStack_78;
        }
        else {
          if (uStack_70 < 0x17) {
            uVar17 = (long)puVar2 + 1;
            *(char *)puVar2 = (char)(uStack_70 << 1);
            if (uStack_70 != 0) goto code_r0x01bab060;
          }
          else {
            uVar10 = uStack_70 + 0x10 & 0xfffffffffffffff0;
            if (uVar10 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
            }
            uVar17 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar10,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
            if (uVar17 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
            }
            puVar2[1] = uVar1;
            puVar2[2] = uVar17;
            *puVar2 = uVar10 | 1;
code_r0x01bab060:
            memcpy(uVar17,puVar11,uVar1);
          }
          *(undefined1 *)(uVar17 + uVar1) = 0;
        }
        if ((uStack_78 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_68);
        }
        param_3[1] = param_3[1] + 0x18;
      }
      else {
        void std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<char const*>(char const*&&)(param_3,&uStack_2e8);
      }
      if ((uStack_2e0 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_2d0);
      }
      puVar6 = (undefined8 *)puVar8[1];
      puVar16 = puVar8;
      if ((undefined8 *)puVar8[1] == (undefined8 *)0x0) {
        do {
          puVar8 = (undefined8 *)puVar16[2];
          bVar7 = (undefined8 *)*puVar8 != puVar16;
          puVar16 = puVar8;
        } while (bVar7);
      }
      else {
        do {
          puVar8 = puVar6;
          puVar6 = (undefined8 *)*puVar8;
        } while ((undefined8 *)*puVar8 != (undefined8 *)0x0);
      }
      lVar12 = lStack_d0;
      plVar15 = plStack_c0;
    } while (puVar8 != &uStack_a0);
  }
  while (plVar15 != (long *)0x0) {
    lVar13 = *plVar15;
    lStack_d0 = lVar12;
    CMasterParameterMenuCommonVoiceElement::~CMasterParameterMenuCommonVoiceElement()(plVar15 + 3);
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar15);
    lVar12 = lStack_d0;
    plVar15 = (long *)lVar13;
  }
  lStack_d0 = 0;
  if (lVar12 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  std::__ndk1::__tree<std::__ndk1::__value_type<string, unsigned int>, std::__ndk1::__map_value_compare<string, std::__ndk1::__value_type<string, unsigned int>, std::__ndk1::less<string >, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<string, unsigned int>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<string, unsigned int>, void*>*)(&puStack_a8,uStack_a0);
  if (lStack_90 != 0) {
    if (lStack_88 != lStack_90) {
      lStack_88 = lStack_88 + (~((lStack_88 + -4) - lStack_90) & 0xfffffffffffffffcU);
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  return;
}

// ==== CMenuVoiceManager::PlaySE(unsigned int, bool)
// vaddr 0x1aab168 | ghidra 0x1bab168 | size 1640 | symbol _ZN17CMenuVoiceManager6PlaySEEjb | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN17CMenuVoiceManager6PlaySEEjb(long param_1,int param_2,ulong param_3)

{
  ulong uVar1;
  undefined *puVar2;
  long *plVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  undefined **ppuVar10;
  long lVar11;
  undefined8 uVar12;
  long lVar13;
  undefined4 uVar14;
  undefined8 uVar15;
  undefined **ppuVar16;
  long lStack_1a8;
  int iStack_1a0;
  undefined4 uStack_19c;
  long lStack_198;
  long lStack_190;
  undefined *puStack_188;
  ulong uStack_180;
  undefined **ppuStack_178;
  undefined8 uStack_170;
  undefined4 uStack_168;
  undefined1 uStack_164;
  undefined *puStack_160;
  ulong uStack_158;
  undefined **ppuStack_150;
  long *plStack_148;
  long *plStack_140;
  long *plStack_138;
  undefined4 uStack_130;
  
  puVar2 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  uVar12 = *(undefined8 *)PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
  lVar8 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar8 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar8 = *(long *)puVar2;
  }
  uVar15 = *(undefined8 *)(*(long *)(lVar8 + 0x5f8) + 0x430);
  snprintf(&puStack_160,0x100,&UNK_027e6d32/*"%u"*/,param_2);
  puStack_188 = &UNK_027ffe64/*"id"*/;
  uStack_180 = 2;
  ppuStack_178 = &puStack_160;
  uStack_170 = strlen(&puStack_160);
  uStack_168 = 0;
  uStack_164 = 0;
  uVar14 = 1;
  CMasterParameterBaseSqlite_Simple<CMasterParameterMenuCommonVoiceElement>::ParameterByQuery(char const*, Aska::Yayoi::QueryParam*, unsigned int) const(&lStack_198,uVar15,&UNK_028d2452/*"SELECT * FROM master_menu_common_voice WHERE id=?"*/,&puStack_188,1);
  puVar2 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lStack_198 == 0) goto joined_r0x01bab404;
  lVar8 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lVar8 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar8 = *(long *)puVar2;
  }
  uVar15 = CUIManager::rUIVoiceManager()(lVar8);
  puStack_188 = (undefined *)0x0;
  uStack_180 = 0;
  ppuStack_178 = (undefined **)0x0;
  void CParameterPropertyBase<51u>::CryptString<string >(string&, string const&)(&puStack_188,lStack_198 + 0x138);
  uStack_158 = 0;
  ppuStack_150 = (undefined **)0x0;
  ppuVar10 = (undefined **)((ulong)&puStack_188 | 1);
  if (((ulong)puStack_188 & 1) != 0) {
    ppuVar10 = ppuStack_178;
  }
  puStack_160 = (undefined *)0x0;
  uVar7 = strlen(ppuVar10);
  if (uVar7 < 0x17) {
    ppuVar16 = (undefined **)((ulong)&puStack_160 | 1);
    puStack_160 = (undefined *)CONCAT71(puStack_160._1_7_,(char)(uVar7 << 1));
    if (uVar7 != 0) goto code_r0x01bab338;
  }
  else {
    uVar9 = uVar7 + 0x10 & 0xfffffffffffffff0;
    if (uVar9 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    ppuVar16 = (undefined **)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (ppuVar16 == (undefined **)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    puStack_160 = (undefined *)(uVar9 | 1);
    uStack_158 = uVar7;
    ppuStack_150 = ppuVar16;
code_r0x01bab338:
    memcpy(ppuVar16,ppuVar10,uVar7);
  }
  *(char *)((long)ppuVar16 + uVar7) = '\0';
  uVar7 = CUIVoiceManager::IsReadyResourcePack(string const&)(uVar15,&puStack_160);
  if (((ulong)puStack_160 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(ppuStack_150);
  }
  if (((ulong)puStack_188 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(ppuStack_178);
  }
  if ((uVar7 & 1) == 0) {
    uVar14 = 0;
    goto joined_r0x01bab404;
  }
  if ((param_3 & 1) != 0) {
    lVar8 = *(long *)(param_1 + 0x20);
    if (*(long *)(param_1 + 0x28) != lVar8) {
      do {
        if (*(long *)(lVar8 + 0x18) == *(long *)(lVar8 + 0x20)) {
          bVar5 = false;
        }
        else {
          bVar5 = false;
          lVar13 = *(long *)(lVar8 + 0x18);
          do {
            lVar11 = lVar13 + 0x10;
            bVar4 = *(int *)(lVar13 + 8) == param_2;
            bVar5 = (bool)(bVar5 | bVar4);
            if (bVar4) break;
            lVar13 = lVar11;
          } while (*(long *)(lVar8 + 0x20) != lVar11);
        }
      } while ((!bVar5) && (lVar8 = lVar8 + 0x38, lVar8 != *(long *)(param_1 + 0x28)));
      if (bVar5) {
        uVar14 = 0;
        goto joined_r0x01bab404;
      }
    }
  }
  puStack_160 = (undefined *)0x0;
  uStack_158 = 0;
  ppuStack_150 = (undefined **)0x0;
  void CParameterPropertyBase<51u>::CryptString<string >(string&, string const&)(&puStack_160,lStack_198 + 0x138);
  ppuVar10 = (undefined **)((ulong)&puStack_160 | 1);
  if (((ulong)puStack_160 & 1) != 0) {
    ppuVar10 = ppuStack_150;
  }
  lVar8 = CSoundManager::PlaySe(char const*, unsigned int)(uVar12,ppuVar10,*(undefined4 *)(lStack_198 + 0x178));
  if (((ulong)puStack_160 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(ppuStack_150);
  }
  if (lVar8 == 0) {
    uVar14 = 1;
    goto joined_r0x01bab404;
  }
  lVar13 = *(long *)(param_1 + 0x20);
  lVar11 = *(long *)(param_1 + 0x28);
  lStack_1a8 = lVar8;
  iStack_1a0 = param_2;
  if (lVar13 == lVar11) {
code_r0x01bab654:
    plStack_148 = (long *)0x0;
    ppuStack_150 = (undefined **)0x0;
    plStack_138 = (long *)0x0;
    plStack_140 = (long *)0x0;
    uStack_158 = 0;
    puStack_160 = (undefined *)0x0;
    puStack_188 = (undefined *)0x0;
    uStack_180 = 0;
    ppuStack_178 = (undefined **)0x0;
    void CParameterPropertyBase<51u>::CryptString<string >(string&, string const&)(&puStack_188,lStack_198 + 0x138);
    puStack_160 = (undefined *)((ulong)puStack_160 & 0xffffffffffff0000);
    string::reserve(unsigned long)(&puStack_160,0);
    ppuStack_150 = ppuStack_178;
    uStack_158 = uStack_180;
    puStack_160 = puStack_188;
    if (plStack_140 != plStack_148) {
      plStack_140 = (long *)((long)plStack_140 +
                            (~((long)plStack_140 + (-0x10 - (long)plStack_148)) &
                            0xfffffffffffffff0U));
    }
    plVar3 = plStack_140;
    if (plStack_140 < plStack_138) {
      if (plStack_140 == (long *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      plVar3[1] = CONCAT44(uStack_19c,iStack_1a0);
      *plVar3 = lStack_1a8;
      plStack_140 = plStack_140 + 2;
    }
    else {
      void std::__ndk1::vector<CMenuVoiceManager::PlayingData::PlayUnit, Framework::CSTLAllocator<CMenuVoiceManager::PlayingData::PlayUnit, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<CMenuVoiceManager::PlayingData::PlayUnit&>(CMenuVoiceManager::PlayingData::PlayUnit&)(&plStack_148,&lStack_1a8);
    }
    uStack_130 = *(undefined4 *)(lStack_198 + 0x108);
    lVar8 = *(long *)(param_1 + 0x28);
    if (lVar8 == *(long *)(param_1 + 0x30)) {
      void std::__ndk1::vector<CMenuVoiceManager::PlayingData, Framework::CSTLAllocator<CMenuVoiceManager::PlayingData, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<CMenuVoiceManager::PlayingData const&>(CMenuVoiceManager::PlayingData const&)((long *)(param_1 + 0x20),&puStack_160);
    }
    else {
      if (lVar8 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      CMenuVoiceManager::PlayingData::PlayingData(CMenuVoiceManager::PlayingData const&)(lVar8,&puStack_160);
      *(long *)(param_1 + 0x28) = *(long *)(param_1 + 0x28) + 0x38;
    }
    if (plStack_148 != (long *)0x0) {
      if (plStack_140 != plStack_148) {
        plStack_140 = (long *)((long)plStack_140 +
                              (~((long)plStack_140 + (-0x10 - (long)plStack_148)) &
                              0xfffffffffffffff0U));
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
    if (((ulong)puStack_160 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(ppuStack_150);
    }
  }
  else {
    do {
      CMenuVoiceManager::PlayingData::PlayingData(CMenuVoiceManager::PlayingData const&)(&puStack_160,lVar13);
      puStack_188 = (undefined *)0x0;
      uStack_180 = 0;
      ppuStack_178 = (undefined **)0x0;
      void CParameterPropertyBase<51u>::CryptString<string >(string&, string const&)(&puStack_188,lStack_198 + 0x138);
      puVar2 = puStack_188;
      uVar9 = (ulong)puStack_160 >> 1 & 0x7f;
      uVar7 = uVar9;
      if (((ulong)puStack_160 & 1) != 0) {
        uVar7 = uStack_158;
      }
      uVar1 = (ulong)puStack_188 >> 1 & 0x7f;
      if (((ulong)puStack_188 & 1) != 0) {
        uVar1 = uStack_180;
      }
      if (uVar7 == uVar1) {
        ppuVar10 = (undefined **)((ulong)&puStack_160 | 1);
        if (((ulong)puStack_160 & 1) != 0) {
          ppuVar10 = ppuStack_150;
        }
        ppuVar16 = (undefined **)((ulong)&puStack_188 | 1);
        if (((ulong)puStack_188 & 1) != 0) {
          ppuVar16 = ppuStack_178;
        }
        if (((ulong)puStack_160 & 1) == 0) {
          if (uVar7 != 0) {
            lVar8 = -uVar9;
            ppuVar10 = (undefined **)((ulong)&puStack_160 | 1);
            do {
              if (*(char *)ppuVar10 != *(char *)ppuVar16) goto code_r0x01bab568;
              ppuVar10 = (undefined **)((long)ppuVar10 + 1);
              lVar8 = lVar8 + 1;
              ppuVar16 = (undefined **)((long)ppuVar16 + 1);
            } while (lVar8 != 0);
          }
        }
        else if (uVar7 != 0) {
          iVar6 = memcmp(ppuVar10);
          bVar5 = iVar6 == 0;
          goto joined_r0x01bab56c;
        }
        bVar5 = true;
      }
      else {
code_r0x01bab568:
        bVar5 = false;
      }
joined_r0x01bab56c:
      if (((ulong)puVar2 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(ppuStack_178);
      }
      plVar3 = plStack_140;
      if (bVar5) {
        if (plStack_140 < plStack_138) {
          if (plStack_140 == (long *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          plVar3[1] = CONCAT44(uStack_19c,iStack_1a0);
          *plVar3 = lStack_1a8;
          plStack_140 = plStack_140 + 2;
        }
        else {
          void std::__ndk1::vector<CMenuVoiceManager::PlayingData::PlayUnit, Framework::CSTLAllocator<CMenuVoiceManager::PlayingData::PlayUnit, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<CMenuVoiceManager::PlayingData::PlayUnit&>(CMenuVoiceManager::PlayingData::PlayUnit&)(&plStack_148,&lStack_1a8);
        }
        bVar5 = true;
      }
      else {
        bVar5 = false;
      }
      if (plStack_148 != (long *)0x0) {
        if (plStack_140 != plStack_148) {
          plStack_140 = (long *)((long)plStack_140 +
                                (~((long)plStack_140 + (-0x10 - (long)plStack_148)) &
                                0xfffffffffffffff0U));
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
      }
      if (((ulong)puStack_160 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(ppuStack_150);
      }
      lVar13 = lVar13 + 0x38;
    } while (!(bool)(bVar5 | lVar13 == lVar11));
    if (!bVar5) goto code_r0x01bab654;
  }
  uVar14 = 2;
joined_r0x01bab404:
  if (lStack_190 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return uVar14;
}

// ==== CMenuVoiceManager::PlayingData::PlayingData(CMenuVoiceManager::PlayingData const&)
// vaddr 0x1aab7d0 | ghidra 0x1bab7d0 | size 400 | symbol _ZN17CMenuVoiceManager11PlayingDataC2ERKS0_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManager11PlayingDataC2ERKS0_(ulong *param_1,ulong *param_2)

{
  ulong uVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  undefined8 *puVar7;
  ulong uVar8;
  undefined8 uVar9;
  
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  if ((*param_2 & 1) == 0) {
    param_1[2] = param_2[2];
    uVar8 = *param_2;
    param_1[1] = param_2[1];
    *param_1 = uVar8;
    goto code_r0x01bab8a4;
  }
  uVar8 = param_2[1];
  uVar1 = param_2[2];
  if (uVar8 < 0x17) {
    uVar5 = (long)param_1 + 1;
    *(char *)param_1 = (char)(uVar8 << 1);
    if (uVar8 != 0) goto code_r0x01bab890;
  }
  else {
    uVar6 = uVar8 + 0x10 & 0xfffffffffffffff0;
    if (uVar6 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uVar8;
    param_1[2] = uVar5;
    *param_1 = uVar6 | 1;
code_r0x01bab890:
    memcpy(uVar5,uVar1,uVar8);
  }
  *(undefined1 *)(uVar5 + uVar8) = 0;
code_r0x01bab8a4:
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[3] = 0;
  lVar4 = (long)(param_2[4] - param_2[3]) >> 4;
  if (lVar4 != 0) {
    puVar3 = (undefined8 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(param_2[4] - param_2[3],&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
    if (puVar3 == (undefined8 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[3] = (ulong)puVar3;
    param_1[4] = (ulong)puVar3;
    param_1[5] = (ulong)(puVar3 + lVar4 * 2);
    puVar2 = (undefined8 *)param_2[4];
    for (puVar7 = (undefined8 *)param_2[3]; puVar7 != puVar2; puVar7 = puVar7 + 2) {
      if (puVar3 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      uVar9 = *puVar7;
      puVar3[1] = puVar7[1];
      *puVar3 = uVar9;
      puVar3 = (undefined8 *)(param_1[4] + 0x10);
      param_1[4] = (ulong)puVar3;
    }
  }
  *(int *)(param_1 + 6) = (int)param_2[6];
  return;
}

// ==== CMenuVoiceManager::IsChangeSoundPackage(unsigned int, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, unsigned int)
// vaddr 0x1aab960 | ghidra 0x1bab960 | size 776 | symbol _ZN17CMenuVoiceManager20IsChangeSoundPackageEjRKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEEj | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN17CMenuVoiceManager20IsChangeSoundPackageEjRKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEEj
          (undefined8 param_1,int param_2,byte *param_3,undefined4 param_4)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  byte bVar5;
  undefined7 uVar6;
  bool bVar7;
  int iVar8;
  ulong uVar9;
  undefined1 *puVar10;
  byte *pbVar11;
  long lVar12;
  byte bStack_88;
  undefined7 uStack_87;
  char cStack_80;
  undefined7 uStack_7f;
  ulong uStack_78;
  undefined7 uStack_70;
  char cStack_69;
  undefined7 uStack_68;
  byte bStack_60;
  undefined1 uStack_5f;
  undefined6 uStack_5e;
  char cStack_58;
  undefined7 uStack_57;
  undefined1 *puStack_50;
  byte abStack_48 [8];
  ulong uStack_40;
  ulong uStack_38;
  
  iVar8 = CMenuVoiceManager::GetMascotToCharaType()();
  if (iVar8 == param_2) {
code_r0x01bab988:
    if ((*param_3 & 1) == 0) {
      pbVar11 = param_3 + 1;
code_r0x01bab9b8:
      lVar12 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
      if (lVar12 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028d240a/*"C:\BAS_Submission\Client\Project\..\Source\Game\UI\MenuVoiceManager.cpp"*/,0x3c1,&UNK_027fd285/*"pParameterManager is null."*/);
      }
      lVar12 = CParameterManager::pParameterSound() const(lVar12);
      if (lVar12 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028d240a/*"C:\BAS_Submission\Client\Project\..\Source\Game\UI\MenuVoiceManager.cpp"*/,0x3c4,&UNK_027fd2a0/*"pParameterSound is null."*/);
      }
      lVar12 = CParameterSound::pParameter(char const*, unsigned int) const(lVar12,pbVar11,param_4);
      if (lVar12 != 0) {
        return 0;
      }
    }
    else {
      pbVar11 = *(byte **)(param_3 + 0x10);
      if (pbVar11 != (byte *)0x0) goto code_r0x01bab9b8;
    }
    if (param_2 != 2) {
      return 1;
    }
  }
  else {
    if (param_2 - 5U < 2) {
      return 1;
    }
    if (param_2 != 2) goto code_r0x01bab988;
  }
  CUIUtility::GetMascot()(abStack_48);
  cStack_58 = 0;
  uStack_57 = 0;
  puStack_50 = (undefined1 *)0x0;
  bStack_60 = 0;
  uStack_5f = 0;
  uStack_5e = 0;
  string std::__ndk1::operator+<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >(string const&, char const*)(&bStack_88,param_3,&UNK_029e43f2/*"_"*/);
  uVar9 = (ulong)bStack_88;
  uVar1 = (ulong)(abStack_48[0] >> 1);
  uVar4 = (ulong)abStack_48 | 1;
  if ((abStack_48[0] & 1) != 0) {
    uVar1 = uStack_40;
    uVar4 = uStack_38;
  }
  if ((bStack_88 & 1) == 0) {
    lVar12 = 0x16;
  }
  else {
    uVar9 = CONCAT71(uStack_87,bStack_88);
    lVar12 = (uVar9 & 0xfffffffffffffffe) - 1;
  }
  uVar2 = (ulong)(((uint)uVar9 & 0xfe) >> 1);
  if ((uVar9 & 1) != 0) {
    uVar2 = CONCAT71(uStack_7f,cStack_80);
  }
  if (lVar12 - uVar2 < uVar1) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_88,lVar12,(uVar1 - lVar12) + uVar2,uVar2,uVar2,0,uVar1);
  }
  else if (uVar1 != 0) {
    uVar3 = (ulong)&bStack_88 | 1;
    if ((uVar9 & 1) != 0) {
      uVar3 = uStack_78;
    }
    memcpy(uVar3 + uVar2,uVar4,uVar1);
    lVar12 = uVar2 + uVar1;
    if ((bStack_88 & 1) == 0) {
      bStack_88 = (char)lVar12 * '\x02';
    }
    else {
      uStack_7f = (undefined7)((ulong)lVar12 >> 8);
      cStack_80 = (char)lVar12;
    }
    *(undefined1 *)(uVar3 + lVar12) = 0;
  }
  uVar1 = uStack_78;
  uStack_68 = uStack_7f;
  cStack_69 = cStack_80;
  uStack_70 = uStack_87;
  bVar5 = bStack_88;
  bStack_88 = 0;
  uStack_87 = 0;
  cStack_80 = 0;
  uStack_7f = 0;
  uStack_78 = 0;
  if ((bStack_60 & 1) == 0) {
    bStack_60 = 0;
    uStack_5f = 0;
  }
  else {
    *puStack_50 = 0;
    cStack_58 = 0;
    uStack_57 = 0;
  }
  string::reserve(unsigned long)(&bStack_60,0);
  uVar6 = uStack_70;
  bStack_60 = bVar5;
  uStack_70 = 0;
  uStack_57 = uStack_68;
  uStack_5f = (undefined1)uVar6;
  uStack_5e = (undefined6)((uint7)uVar6 >> 8);
  cStack_58 = cStack_69;
  puStack_50 = (undefined1 *)uVar1;
  cStack_69 = 0;
  uStack_68 = 0;
  if ((bStack_88 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_78);
  }
  if ((bStack_60 & 1) == 0) {
    puVar10 = (undefined1 *)((ulong)&bStack_60 | 1);
  }
  else {
    puVar10 = puStack_50;
    if (puStack_50 == (undefined1 *)0x0) {
      bVar7 = false;
      goto joined_r0x01babc60;
    }
  }
  lVar12 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar12 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028d240a/*"C:\BAS_Submission\Client\Project\..\Source\Game\UI\MenuVoiceManager.cpp"*/,0x3c1,&UNK_027fd285/*"pParameterManager is null."*/);
  }
  lVar12 = CParameterManager::pParameterSound() const(lVar12);
  if (lVar12 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028d240a/*"C:\BAS_Submission\Client\Project\..\Source\Game\UI\MenuVoiceManager.cpp"*/,0x3c4,&UNK_027fd2a0/*"pParameterSound is null."*/);
  }
  lVar12 = CParameterSound::pParameter(char const*, unsigned int) const(lVar12,puVar10,param_4);
  bVar7 = lVar12 != 0;
joined_r0x01babc60:
  if ((bStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_50);
  }
  if ((abStack_48[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  if (bVar7) {
    return 1;
  }
  return 0;
}

// ==== CMenuVoiceManager::StopAll(bool, float)
// vaddr 0x1aac20c | ghidra 0x1bac20c | size 260 | symbol _ZN17CMenuVoiceManager7StopAllEbf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN17CMenuVoiceManager7StopAllEbf(float param_1,long param_2,ulong param_3)

{
  undefined8 *puVar1;
  long lVar2;
  undefined8 *puVar3;
  ulong uVar4;
  undefined8 uVar5;
  long lVar6;
  
  lVar6 = *(long *)(param_2 + 0x10);
  uVar5 = *(undefined8 *)PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
  if (lVar6 != *(long *)(param_2 + 8)) {
    *(ulong *)(param_2 + 0x10) =
         lVar6 + (~((lVar6 + -8) - *(long *)(param_2 + 8)) & 0xfffffffffffffff8U);
  }
  lVar6 = *(long *)(param_2 + 0x20);
  lVar2 = *(long *)(param_2 + 0x28);
  if (lVar6 != lVar2) {
    if ((param_3 & 1) == 0) {
      do {
        puVar3 = *(undefined8 **)(lVar6 + 0x20);
        for (puVar1 = *(undefined8 **)(lVar6 + 0x18); puVar1 != puVar3; puVar1 = puVar1 + 2) {
          uVar4 = CSoundManager::IsPlaying(unsigned long) const(uVar5,*puVar1);
          if ((uVar4 & 1) != 0) {
            CSoundManager::Stop(unsigned long, std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)(0,uVar5,*puVar1);
          }
        }
        lVar6 = lVar6 + 0x38;
      } while (lVar6 != lVar2);
    }
    else {
      param_1 = param_1 * _UNK_027ebdd8;
      do {
        puVar3 = *(undefined8 **)(lVar6 + 0x20);
        for (puVar1 = *(undefined8 **)(lVar6 + 0x18); puVar1 != puVar3; puVar1 = puVar1 + 2) {
          uVar4 = CSoundManager::IsPlaying(unsigned long) const(uVar5,*puVar1);
          if ((uVar4 & 1) != 0) {
            CSoundManager::Stop(unsigned long, std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)(param_1 / 3.0,uVar5,*puVar1);
          }
        }
        lVar6 = lVar6 + 0x38;
      } while (lVar6 != lVar2);
    }
  }
  return;
}

// ==== CMenuVoiceManager::RequestStop(unsigned int, unsigned int)
// vaddr 0x1aac310 | ghidra 0x1bac310 | size 872 | symbol _ZN17CMenuVoiceManager11RequestStopEjj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManager11RequestStopEjj(long param_1,int param_2,int param_3)

{
  long lVar1;
  ulong *puVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  ulong uVar5;
  long lVar6;
  undefined1 *puVar7;
  int iVar8;
  ulong uVar9;
  ulong uVar10;
  undefined8 *puVar11;
  long lStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  ulong uStack_88;
  long lStack_80;
  ulong uStack_78;
  ulong uStack_70;
  undefined1 *puStack_68;
  
  puVar11 = *(undefined8 **)(param_1 + 0x68);
  puVar3 = *(undefined8 **)(param_1 + 0x70);
  if (puVar11 != puVar3) {
    lVar1 = (long)&uStack_90 + 1;
    do {
      uStack_98 = *puVar11;
      uStack_88 = 0;
      lStack_80 = 0;
      uStack_90 = 0;
      if ((puVar11[1] & 1) == 0) {
        lStack_80 = puVar11[3];
        uStack_88 = puVar11[2];
        uStack_90 = puVar11[1];
        iVar8 = (int)((ulong)uStack_98 >> 0x20);
      }
      else {
        uVar5 = puVar11[2];
        uVar4 = puVar11[3];
        if (uVar5 < 0x17) {
          uStack_90 = (uVar5 & 0x7f) << 1;
          lVar6 = lVar1;
          if (uVar5 != 0) goto code_r0x01bac4c0;
        }
        else {
          uVar9 = uVar5 + 0x10 & 0xfffffffffffffff0;
          if (uVar9 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          lVar6 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (lVar6 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uStack_90 = uVar9 | 1;
          uStack_88 = uVar5;
          lStack_80 = lVar6;
code_r0x01bac4c0:
          memcpy(lVar6,uVar4,uVar5);
        }
        *(undefined1 *)(lVar6 + uVar5) = 0;
        iVar8 = uStack_98._4_4_;
      }
      if (((int)uStack_98 == param_2) && (iVar8 == param_3)) {
        lVar6 = lVar1;
        if ((uStack_90 & 1) != 0) {
          lVar6 = lStack_80;
        }
        puVar2 = *(ulong **)(param_1 + 0x58);
        lStack_a0 = lVar6;
        if (puVar2 < *(ulong **)(param_1 + 0x60)) {
          uStack_70 = 0;
          puStack_68 = (undefined1 *)0x0;
          uStack_78 = 0;
          uVar5 = strlen(lVar6);
          if (uVar5 < 0x17) {
            uStack_78 = CONCAT71(uStack_78._1_7_,(char)(uVar5 << 1));
            puVar7 = (undefined1 *)((ulong)&uStack_78 | 1);
            if (uVar5 != 0) goto code_r0x01bac54c;
            *(undefined1 *)((ulong)&uStack_78 | 1) = 0;
          }
          else {
            uVar9 = uVar5 + 0x10 & 0xfffffffffffffff0;
            if (uVar9 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
            }
            puVar7 = (undefined1 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
            if (puVar7 == (undefined1 *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
            }
            uStack_78 = uVar9 | 1;
            uStack_70 = uVar5;
            puStack_68 = puVar7;
code_r0x01bac54c:
            memcpy(puVar7,lVar6,uVar5);
            puVar7[uVar5] = 0;
          }
          if (puVar2 == (ulong *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          puVar7 = puStack_68;
          uVar5 = uStack_70;
          puVar2[1] = 0;
          puVar2[2] = 0;
          *puVar2 = 0;
          if ((uStack_78 & 1) == 0) {
            puVar2[2] = (ulong)puStack_68;
            puVar2[1] = uStack_70;
            *puVar2 = uStack_78;
          }
          else {
            if (uStack_70 < 0x17) {
              uVar10 = (long)puVar2 + 1;
              *(char *)puVar2 = (char)(uStack_70 << 1);
              if (uStack_70 != 0) goto code_r0x01bac608;
            }
            else {
              uVar9 = uStack_70 + 0x10 & 0xfffffffffffffff0;
              if (uVar9 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
              }
              uVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
              if (uVar10 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
              }
              puVar2[1] = uVar5;
              puVar2[2] = uVar10;
              *puVar2 = uVar9 | 1;
code_r0x01bac608:
              memcpy(uVar10,puVar7,uVar5);
            }
            *(undefined1 *)(uVar10 + uVar5) = 0;
          }
          if ((uStack_78 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_68);
          }
          *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 0x18;
        }
        else {
          void std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<char const*>(char const*&&)(param_1 + 0x50,&lStack_a0);
        }
      }
      if ((uStack_90 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lStack_80);
      }
      puVar11 = puVar11 + 4;
    } while (puVar3 != puVar11);
  }
  return;
}

// ==== CMenuVoiceManager::RequestStop(char const*)
// vaddr 0x1aac678 | ghidra 0x1bac678 | size 776 | symbol _ZN17CMenuVoiceManager11RequestStopEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManager11RequestStopEPKc(long param_1)

{
  ulong *puVar1;
  ulong *puVar2;
  undefined *puVar3;
  undefined4 uVar4;
  ulong uVar5;
  long lVar6;
  undefined8 uVar7;
  ulong uVar8;
  undefined1 *puVar9;
  ulong uVar10;
  ulong *puStack_190;
  long lStack_188;
  long lStack_180;
  undefined1 auStack_178 [16];
  undefined *puStack_168;
  undefined8 uStack_160;
  ulong *puStack_158;
  undefined8 uStack_150;
  undefined4 uStack_148;
  undefined1 uStack_144;
  ulong uStack_140;
  ulong uStack_138;
  undefined1 *puStack_130;
  
  Framework::CHash32::CHash32(char const*)(auStack_178);
  uVar4 = Framework::CHash32::operator unsigned int() const(auStack_178);
  Framework::CHash32::~CHash32()(auStack_178);
  puVar3 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar6 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar6 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar6 = *(long *)puVar3;
  }
  uVar7 = *(undefined8 *)(*(long *)(lVar6 + 0x5f8) + 0x430);
  snprintf(&uStack_140,0x100,&UNK_027e6d32/*"%u"*/,uVar4);
  puStack_168 = &UNK_027ffe64/*"id"*/;
  uStack_160 = 2;
  puStack_158 = &uStack_140;
  uStack_150 = strlen(&uStack_140);
  uStack_148 = 0;
  uStack_144 = 0;
  CMasterParameterBaseSqlite_Simple<CMasterParameterMenuCommonVoiceElement>::ParameterByQuery(char const*, Aska::Yayoi::QueryParam*, unsigned int) const(&lStack_188,uVar7,&UNK_028d2452/*"SELECT * FROM master_menu_common_voice WHERE id=?"*/,&puStack_168,1);
  if (lStack_188 == 0) goto code_r0x01bac95c;
  uStack_160 = 0;
  puStack_158 = (ulong *)0x0;
  puStack_168 = (undefined *)0x0;
  void CParameterPropertyBase<51u>::CryptString<string >(string&, string const&)(&puStack_168,lStack_188 + 0x138);
  puVar1 = (ulong *)((ulong)&puStack_168 | 1);
  if (((ulong)puStack_168 & 1) != 0) {
    puVar1 = puStack_158;
  }
  puVar2 = *(ulong **)(param_1 + 0x58);
  puStack_190 = puVar1;
  if (puVar2 < *(ulong **)(param_1 + 0x60)) {
    uStack_138 = 0;
    puStack_130 = (undefined1 *)0x0;
    uStack_140 = 0;
    uVar5 = strlen(puVar1);
    if (uVar5 < 0x17) {
      puVar9 = (undefined1 *)((ulong)&uStack_140 | 1);
      uStack_140 = CONCAT71(uStack_140._1_7_,(char)(uVar5 << 1));
      if (uVar5 != 0) goto code_r0x01bac860;
      *puVar9 = 0;
    }
    else {
      uVar8 = uVar5 + 0x10 & 0xfffffffffffffff0;
      if (uVar8 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      puVar9 = (undefined1 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar8,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (puVar9 == (undefined1 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      uStack_140 = uVar8 | 1;
      uStack_138 = uVar5;
      puStack_130 = puVar9;
code_r0x01bac860:
      memcpy(puVar9,puVar1,uVar5);
      puVar9[uVar5] = 0;
    }
    if (puVar2 == (ulong *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
    }
    puVar9 = puStack_130;
    uVar5 = uStack_138;
    puVar2[1] = 0;
    puVar2[2] = 0;
    *puVar2 = 0;
    if ((uStack_140 & 1) == 0) {
      puVar2[2] = (ulong)puStack_130;
      puVar2[1] = uStack_138;
      *puVar2 = uStack_140;
    }
    else {
      if (uStack_138 < 0x17) {
        uVar10 = (long)puVar2 + 1;
        *(char *)puVar2 = (char)(uStack_138 << 1);
        if (uStack_138 != 0) goto code_r0x01bac91c;
      }
      else {
        uVar8 = uStack_138 + 0x10 & 0xfffffffffffffff0;
        if (uVar8 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar8,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (uVar10 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        puVar2[1] = uVar5;
        puVar2[2] = uVar10;
        *puVar2 = uVar8 | 1;
code_r0x01bac91c:
        memcpy(uVar10,puVar9,uVar5);
      }
      *(undefined1 *)(uVar10 + uVar5) = 0;
    }
    if ((uStack_140 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_130);
    }
    *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 0x18;
  }
  else {
    void std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<char const*>(char const*&&)(param_1 + 0x50,&puStack_190);
  }
  if (((ulong)puStack_168 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_158);
  }
code_r0x01bac95c:
  if (lStack_180 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return;
}

// ==== CMenuVoiceManager::StopPlayPack(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, float)
// vaddr 0x1aac980 | ghidra 0x1bac980 | size 1128 | symbol _ZN17CMenuVoiceManager12StopPlayPackERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN17CMenuVoiceManager12StopPlayPackERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEEf
               (float param_1,long param_2,byte *param_3)

{
  ulong uVar1;
  ulong uVar2;
  byte *pbVar3;
  ulong *puVar4;
  byte bVar5;
  byte bVar6;
  ulong *puVar7;
  bool bVar8;
  undefined *puVar9;
  undefined4 *puVar10;
  bool bVar11;
  int iVar12;
  long lVar13;
  long lVar14;
  ulong uVar15;
  byte *pbVar16;
  byte *pbVar17;
  undefined8 uVar18;
  byte *pbVar19;
  ulong *puVar20;
  undefined8 *puVar21;
  long *plVar22;
  long lVar23;
  ulong uStack_2d0;
  ulong uStack_2c8;
  byte *pbStack_2c0;
  ulong uStack_2b8;
  undefined1 auStack_2b0 [312];
  undefined1 auStack_178 [200];
  long lStack_b0;
  undefined8 uStack_a8;
  long *plStack_a0;
  undefined8 uStack_98;
  undefined4 uStack_90;
  undefined4 *puStack_88;
  undefined4 *puStack_80;
  undefined4 *puStack_78;
  
  puVar9 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  uVar15 = (ulong)(*param_3 >> 1);
  if ((*param_3 & 1) != 0) {
    uVar15 = *(ulong *)(param_3 + 8);
  }
  if (uVar15 != 0) {
    if (*(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    }
    puStack_78 = (undefined4 *)0x0;
    puStack_80 = (undefined4 *)0x0;
    puStack_88 = (undefined4 *)0x0;
    puVar20 = *(ulong **)(param_2 + 8);
    puVar4 = *(ulong **)(param_2 + 0x10);
    while (puVar7 = puVar20, puVar20 != puVar4) {
      while( true ) {
        puVar10 = puStack_80;
        puVar20 = puVar7 + 1;
        uVar15 = *puVar7;
        uStack_2b8 = uVar15;
        if (puStack_78 <= puStack_80) break;
        if (puStack_80 == (undefined4 *)0x0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          uVar15 = uStack_2b8 & 0xffffffff;
        }
        *puVar10 = (int)uVar15;
        puStack_80 = puStack_80 + 1;
        puVar7 = puVar20;
        if (puVar4 == puVar20) goto code_r0x01baca88;
      }
      void std::__ndk1::vector<unsigned int, Framework::CSTLAllocator<unsigned int, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<unsigned int&>(unsigned int&)(&puStack_88,&uStack_2b8);
    }
code_r0x01baca88:
    lVar13 = *(long *)puVar9;
    uStack_a8 = 0;
    lStack_b0 = 0;
    uStack_98 = 0;
    plStack_a0 = (long *)0x0;
    uStack_90 = 0x3f800000;
    if (lVar13 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar13 = *(long *)puVar9;
    }
    CMasterParameterMenuCommonVoice::ParameterByIDList(Framework::CSTLVector<unsigned int>&, Framework::CSTLUnorderedMap<unsigned int, CMasterParameterMenuCommonVoiceElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >&) const(*(undefined8 *)(*(long *)(lVar13 + 0x5f8) + 0x430),&puStack_88,&lStack_b0);
    lVar13 = *(long *)(param_2 + 8);
    lVar14 = *(long *)(param_2 + 0x10);
    if (lVar14 != lVar13) {
      do {
        while (plStack_a0 == (long *)0x0) {
code_r0x01bacc4c:
          lVar13 = lVar13 + 8;
          if (lVar14 == lVar13) goto code_r0x01bacc58;
        }
        bVar8 = false;
        plVar22 = plStack_a0;
        do {
          uStack_2b8 = CONCAT44(uStack_2b8._4_4_,(int)plVar22[2]);
          CMasterParameterMenuCommonVoiceElement::CMasterParameterMenuCommonVoiceElement(CMasterParameterMenuCommonVoiceElement const&)(auStack_2b0,plVar22 + 3);
          uStack_2c8 = 0;
          pbStack_2c0 = (byte *)0x0;
          uStack_2d0 = 0;
          void CParameterPropertyBase<51u>::CryptString<string >(string&, string const&)(&uStack_2d0,auStack_178);
          uVar2 = uStack_2d0;
          bVar5 = *param_3;
          uVar15 = (ulong)(bVar5 >> 1);
          if ((bVar5 & 1) != 0) {
            uVar15 = *(ulong *)(param_3 + 8);
          }
          uVar1 = uStack_2d0 >> 1 & 0x7f;
          if ((uStack_2d0 & 1) != 0) {
            uVar1 = uStack_2c8;
          }
          if (uVar15 == uVar1) {
            pbVar16 = param_3 + 1;
            if ((bVar5 & 1) != 0) {
              pbVar16 = *(byte **)(param_3 + 0x10);
            }
            pbVar19 = (byte *)((ulong)&uStack_2d0 | 1);
            if ((uStack_2d0 & 1) != 0) {
              pbVar19 = pbStack_2c0;
            }
            if ((bVar5 & 1) == 0) {
              if (uVar15 != 0) {
                lVar14 = -(ulong)(bVar5 >> 1);
                pbVar16 = param_3 + 1;
                do {
                  if (*pbVar16 != *pbVar19) goto code_r0x01bacbd0;
                  pbVar16 = pbVar16 + 1;
                  lVar14 = lVar14 + 1;
                  pbVar19 = pbVar19 + 1;
                } while (lVar14 != 0);
              }
            }
            else if (uVar15 != 0) {
              iVar12 = memcmp(pbVar16);
              bVar11 = iVar12 == 0;
              goto joined_r0x01bacbd4;
            }
            bVar11 = true;
          }
          else {
code_r0x01bacbd0:
            bVar11 = false;
          }
joined_r0x01bacbd4:
          if ((uVar2 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pbStack_2c0);
          }
          bVar8 = (bool)(bVar8 | bVar11);
          CMasterParameterMenuCommonVoiceElement::~CMasterParameterMenuCommonVoiceElement()(auStack_2b0);
          plVar22 = (long *)*plVar22;
        } while (plVar22 != (long *)0x0);
        if (!bVar8) {
          lVar14 = *(long *)(param_2 + 0x10);
          goto code_r0x01bacc4c;
        }
        lVar14 = *(long *)(param_2 + 0x10);
        lVar23 = lVar14 - (lVar13 + 8) >> 3;
        if (lVar23 != 0) {
          memmove(lVar13);
          lVar14 = *(long *)(param_2 + 0x10);
        }
        lVar23 = lVar13 + lVar23 * 8;
        if (lVar14 != lVar23) {
          lVar14 = lVar14 + (~((lVar14 + -8) - lVar23) & 0xfffffffffffffff8U);
          *(long *)(param_2 + 0x10) = lVar14;
        }
      } while (lVar14 != lVar13);
    }
code_r0x01bacc58:
    pbVar16 = *(byte **)(param_2 + 0x20);
    pbVar19 = *(byte **)(param_2 + 0x28);
    lVar13 = lStack_b0;
    plVar22 = plStack_a0;
    if ((pbVar19 != pbVar16) && (pbVar19 != pbVar16)) {
      param_1 = param_1 * _UNK_027ebdd8;
      uVar18 = *(undefined8 *)PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
      do {
        bVar5 = *pbVar16;
        bVar6 = *param_3;
        uVar15 = (ulong)(bVar5 >> 1);
        if ((bVar5 & 1) != 0) {
          uVar15 = *(ulong *)(pbVar16 + 8);
        }
        uVar2 = (ulong)(bVar6 >> 1);
        if ((bVar6 & 1) != 0) {
          uVar2 = *(ulong *)(param_3 + 8);
        }
        if (uVar15 == uVar2) {
          pbVar17 = *(byte **)(pbVar16 + 0x10);
          if ((bVar5 & 1) == 0) {
            pbVar17 = pbVar16 + 1;
          }
          pbVar3 = param_3 + 1;
          if ((bVar6 & 1) != 0) {
            pbVar3 = *(byte **)(param_3 + 0x10);
          }
          if ((bVar5 & 1) == 0) {
            if (uVar15 != 0) {
              uVar15 = 0;
              do {
                if (pbVar16[uVar15 + 1] != pbVar3[uVar15]) goto code_r0x01bacd54;
                uVar15 = uVar15 + 1;
              } while (bVar5 >> 1 != uVar15);
            }
          }
          else if ((uVar15 != 0) && (iVar12 = memcmp(pbVar17), iVar12 != 0))
          goto code_r0x01bacd54;
          puVar21 = *(undefined8 **)(pbVar16 + 0x18);
          if (*(undefined8 **)(pbVar16 + 0x20) != puVar21) {
            do {
              uVar15 = CSoundManager::IsPlaying(unsigned long) const(uVar18,*puVar21);
              if ((uVar15 & 1) != 0) {
                CSoundManager::Stop(unsigned long, std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)(param_1 / 3.0,uVar18,*puVar21);
              }
              puVar21 = puVar21 + 2;
            } while (puVar21 != *(undefined8 **)(pbVar16 + 0x20));
            pbVar19 = *(byte **)(param_2 + 0x28);
          }
        }
code_r0x01bacd54:
        pbVar16 = pbVar16 + 0x38;
        lVar13 = lStack_b0;
        plVar22 = plStack_a0;
      } while (pbVar16 != pbVar19);
    }
    while (plVar22 != (long *)0x0) {
      lVar14 = *plVar22;
      lStack_b0 = lVar13;
      CMasterParameterMenuCommonVoiceElement::~CMasterParameterMenuCommonVoiceElement()(plVar22 + 3);
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar22);
      lVar13 = lStack_b0;
      plVar22 = (long *)lVar14;
    }
    lStack_b0 = 0;
    if (lVar13 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
    if (puStack_88 != (undefined4 *)0x0) {
      if (puStack_80 != puStack_88) {
        puStack_80 = (undefined4 *)
                     ((long)puStack_80 +
                     (~((long)puStack_80 + (-4 - (long)puStack_88)) & 0xfffffffffffffffcU));
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
  }
  return;
}

// ==== CMenuVoiceManager::RemoveResourcePack(unsigned int, unsigned int)
// vaddr 0x1aacde8 | ghidra 0x1bacde8 | size 1036 | symbol _ZN17CMenuVoiceManager18RemoveResourcePackEjj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManager18RemoveResourcePackEjj(long param_1,int param_2,int param_3)

{
  ulong *puVar1;
  ulong uVar2;
  int *piVar3;
  int *piVar4;
  byte *pbVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  int *piVar10;
  int *piVar11;
  long lVar12;
  ulong uStack_88;
  ulong uStack_80;
  ulong uStack_78;
  
  piVar11 = *(int **)(param_1 + 0x68);
  piVar10 = *(int **)(param_1 + 0x70);
  if (piVar11 != piVar10) {
    uVar7 = (ulong)&uStack_88 | 1;
    do {
      while ((*piVar11 == param_2 && (piVar11[1] == param_3))) {
        pbVar5 = (byte *)(piVar11 + 2);
        if ((*pbVar5 & 1) == 0) {
          lVar12 = (long)piVar11 + 9;
        }
        else {
          lVar12 = *(long *)(piVar11 + 6);
        }
        uStack_80 = 0;
        uStack_78 = 0;
        uStack_88 = 0;
        uVar2 = strlen(lVar12);
        if (uVar2 < 0x17) {
          uStack_88 = CONCAT71(uStack_88._1_7_,(char)(uVar2 << 1));
          uVar8 = uVar7;
          if (uVar2 != 0) goto code_r0x01bacf40;
        }
        else {
          uVar9 = uVar2 + 0x10 & 0xfffffffffffffff0;
          if (uVar9 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          uVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (uVar8 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uStack_88 = uVar9 | 1;
          uStack_80 = uVar2;
          uStack_78 = uVar8;
code_r0x01bacf40:
          memcpy(uVar8,lVar12,uVar2);
        }
        *(undefined1 *)(uVar8 + uVar2) = 0;
        CMenuVoiceManager::StopPlayPack(string const&, float)(0x41200000,param_1,&uStack_88);
        if ((uStack_88 & 1) == 0) {
          if ((*pbVar5 & 1) != 0) goto code_r0x01bacf8c;
code_r0x01bacf74:
          lVar12 = (long)piVar11 + 9;
        }
        else {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_78);
          if ((*pbVar5 & 1) == 0) goto code_r0x01bacf74;
code_r0x01bacf8c:
          lVar12 = *(long *)(piVar11 + 6);
        }
        uStack_80 = 0;
        uStack_78 = 0;
        uStack_88 = 0;
        uVar2 = strlen(lVar12);
        if (uVar2 < 0x17) {
          uStack_88 = CONCAT71(uStack_88._1_7_,(char)(uVar2 << 1));
          uVar8 = uVar7;
          if (uVar2 != 0) goto code_r0x01bad020;
        }
        else {
          uVar9 = uVar2 + 0x10 & 0xfffffffffffffff0;
          if (uVar9 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          uVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (uVar8 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uStack_88 = uVar9 | 1;
          uStack_80 = uVar2;
          uStack_78 = uVar8;
code_r0x01bad020:
          memcpy(uVar8,lVar12,uVar2);
        }
        *(undefined1 *)(uVar8 + uVar2) = 0;
        puVar1 = *(ulong **)(param_1 + 0x40);
        if (puVar1 < *(ulong **)(param_1 + 0x48)) {
          if (puVar1 == (ulong *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          uVar9 = uStack_78;
          uVar2 = uStack_80;
          puVar1[1] = 0;
          puVar1[2] = 0;
          *puVar1 = 0;
          if ((uStack_88 & 1) == 0) {
            puVar1[2] = uStack_78;
            puVar1[1] = uStack_80;
            *puVar1 = uStack_88;
          }
          else {
            if (uStack_80 < 0x17) {
              uVar6 = (long)puVar1 + 1;
              *(char *)puVar1 = (char)(uStack_80 << 1);
              if (uStack_80 != 0) goto code_r0x01bad11c;
            }
            else {
              uVar8 = uStack_80 + 0x10 & 0xfffffffffffffff0;
              if (uVar8 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
              }
              uVar6 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar8,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
              if (uVar6 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
              }
              puVar1[1] = uVar2;
              puVar1[2] = uVar6;
              *puVar1 = uVar8 | 1;
code_r0x01bad11c:
              memcpy(uVar6,uVar9,uVar2);
            }
            *(undefined1 *)(uVar6 + uVar2) = 0;
          }
          *(long *)(param_1 + 0x40) = *(long *)(param_1 + 0x40) + 0x18;
        }
        else {
          void std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<string >(string&&)(param_1 + 0x38,&uStack_88);
        }
        if ((uStack_88 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_78);
        }
        piVar4 = *(int **)(param_1 + 0x70);
        piVar3 = piVar11 + 8;
        piVar10 = piVar11;
        if (piVar3 == piVar4) {
code_r0x01bace44:
          do {
            *(int **)(param_1 + 0x70) = piVar3 + -8;
            piVar4 = piVar3 + -8;
            if ((*(byte *)(piVar3 + -6) & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(piVar3 + -2));
              piVar4 = *(int **)(param_1 + 0x70);
            }
            piVar3 = piVar4;
          } while (piVar3 != piVar10);
        }
        else {
          do {
            *(undefined8 *)piVar10 = *(undefined8 *)(piVar10 + 8);
            pbVar5 = (byte *)(piVar10 + 2);
            if ((*pbVar5 & 1) == 0) {
              *(undefined2 *)(piVar10 + 2) = 0;
            }
            else {
              **(undefined1 **)(piVar10 + 6) = 0;
              piVar10[4] = 0;
              piVar10[5] = 0;
            }
            string::reserve(unsigned long)(pbVar5,0);
            *(undefined8 *)(piVar10 + 6) = *(undefined8 *)(piVar10 + 0xe);
            *(undefined8 *)(piVar10 + 4) = *(undefined8 *)(piVar10 + 0xc);
            *(undefined8 *)pbVar5 = *(undefined8 *)(piVar10 + 10);
            piVar10[0xc] = 0;
            piVar10[0xd] = 0;
            piVar10[0xe] = 0;
            piVar10[0xf] = 0;
            piVar10[10] = 0;
            piVar10[0xb] = 0;
            piVar10 = piVar10 + 8;
          } while (piVar4 + -8 != piVar10);
          piVar3 = *(int **)(param_1 + 0x70);
          if (piVar3 != piVar10) goto code_r0x01bace44;
        }
        if (piVar10 == piVar11) {
          return;
        }
      }
      piVar11 = piVar11 + 8;
    } while (piVar10 != piVar11);
  }
  return;
}

// ==== CMenuVoiceManager::RemoveResourcePack(char const*)
// vaddr 0x1aad1f4 | ghidra 0x1bad1f4 | size 1460 | symbol _ZN17CMenuVoiceManager18RemoveResourcePackEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManager18RemoveResourcePackEPKc(long param_1)

{
  ulong *puVar1;
  byte bVar2;
  undefined *puVar3;
  bool bVar4;
  undefined4 uVar5;
  int iVar6;
  ulong uVar7;
  long lVar8;
  char *pcVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  byte *pbVar12;
  undefined8 uVar13;
  undefined8 *puVar14;
  ulong uVar15;
  char *pcVar16;
  ulong uVar17;
  undefined8 *puVar18;
  long lStack_188;
  long lStack_180;
  undefined1 auStack_178 [16];
  undefined *puStack_168;
  undefined8 uStack_160;
  ulong *puStack_158;
  undefined8 uStack_150;
  undefined4 uStack_148;
  undefined1 uStack_144;
  ulong uStack_140;
  ulong uStack_138;
  char *pcStack_130;
  
  Framework::CHash32::CHash32(char const*)(auStack_178);
  uVar5 = Framework::CHash32::operator unsigned int() const(auStack_178);
  Framework::CHash32::~CHash32()(auStack_178);
  puVar3 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar8 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar8 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar8 = *(long *)puVar3;
  }
  uVar13 = *(undefined8 *)(*(long *)(lVar8 + 0x5f8) + 0x430);
  snprintf(&uStack_140,0x100,&UNK_027e6d32/*"%u"*/,uVar5);
  puStack_168 = &UNK_027ffe64/*"id"*/;
  uStack_160 = 2;
  puStack_158 = &uStack_140;
  uStack_150 = strlen(&uStack_140);
  uStack_148 = 0;
  uStack_144 = 0;
  CMasterParameterBaseSqlite_Simple<CMasterParameterMenuCommonVoiceElement>::ParameterByQuery(char const*, Aska::Yayoi::QueryParam*, unsigned int) const(&lStack_188,uVar13,&UNK_028d2452/*"SELECT * FROM master_menu_common_voice WHERE id=?"*/,&puStack_168,1);
  if (lStack_188 == 0) goto code_r0x01bad784;
  uStack_160 = 0;
  puStack_158 = (ulong *)0x0;
  puStack_168 = (undefined *)0x0;
  void CParameterPropertyBase<51u>::CryptString<string >(string&, string const&)(&puStack_168,lStack_188 + 0x138);
  uStack_138 = 0;
  pcStack_130 = (char *)0x0;
  puVar1 = (ulong *)((ulong)&puStack_168 | 1);
  if (((ulong)puStack_168 & 1) != 0) {
    puVar1 = puStack_158;
  }
  uStack_140 = 0;
  uVar7 = strlen(puVar1);
  if (uVar7 < 0x17) {
    uVar15 = (ulong)&uStack_140 | 1;
    uStack_140 = CONCAT71(uStack_140._1_7_,(char)(uVar7 << 1));
    if (uVar7 != 0) goto code_r0x01bad388;
  }
  else {
    uVar17 = uVar7 + 0x10 & 0xfffffffffffffff0;
    if (uVar17 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar15 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar17,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar15 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_140 = uVar17 | 1;
    uStack_138 = uVar7;
    pcStack_130 = (char *)uVar15;
code_r0x01bad388:
    memcpy(uVar15,puVar1,uVar7);
  }
  *(undefined1 *)(uVar15 + uVar7) = 0;
  CMenuVoiceManager::StopPlayPack(string const&, float)(0x40000000,param_1,&uStack_140);
  if ((uStack_140 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pcStack_130);
  }
  if (((ulong)puStack_168 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_158);
  }
  puStack_168 = (undefined *)0x0;
  uStack_160 = 0;
  puStack_158 = (ulong *)0x0;
  void CParameterPropertyBase<51u>::CryptString<string >(string&, string const&)(&puStack_168,lStack_188 + 0x138);
  uStack_138 = 0;
  pcStack_130 = (char *)0x0;
  puVar1 = (ulong *)((ulong)&puStack_168 | 1);
  if (((ulong)puStack_168 & 1) != 0) {
    puVar1 = puStack_158;
  }
  uStack_140 = 0;
  uVar7 = strlen(puVar1);
  if (uVar7 < 0x17) {
    pcVar16 = (char *)((ulong)&uStack_140 | 1);
    uStack_140 = CONCAT71(uStack_140._1_7_,(char)(uVar7 << 1));
    if (uVar7 != 0) goto code_r0x01bad494;
  }
  else {
    uVar17 = uVar7 + 0x10 & 0xfffffffffffffff0;
    if (uVar17 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    pcVar16 = (char *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar17,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (pcVar16 == (char *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_140 = uVar17 | 1;
    uStack_138 = uVar7;
    pcStack_130 = pcVar16;
code_r0x01bad494:
    memcpy(pcVar16,puVar1,uVar7);
  }
  pcVar16[uVar7] = '\0';
  puVar1 = *(ulong **)(param_1 + 0x40);
  if (puVar1 < *(ulong **)(param_1 + 0x48)) {
    if (puVar1 == (ulong *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
    }
    pcVar16 = pcStack_130;
    uVar7 = uStack_138;
    puVar1[1] = 0;
    puVar1[2] = 0;
    *puVar1 = 0;
    if ((uStack_140 & 1) == 0) {
      puVar1[2] = (ulong)pcStack_130;
      puVar1[1] = uStack_138;
      *puVar1 = uStack_140;
    }
    else {
      if (uStack_138 < 0x17) {
        uVar15 = (long)puVar1 + 1;
        *(char *)puVar1 = (char)(uStack_138 << 1);
        if (uStack_138 != 0) goto code_r0x01bad594;
      }
      else {
        uVar17 = uStack_138 + 0x10 & 0xfffffffffffffff0;
        if (uVar17 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar15 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar17,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (uVar15 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        puVar1[1] = uVar7;
        puVar1[2] = uVar15;
        *puVar1 = uVar17 | 1;
code_r0x01bad594:
        memcpy(uVar15,pcVar16,uVar7);
      }
      *(undefined1 *)(uVar15 + uVar7) = 0;
    }
    *(long *)(param_1 + 0x40) = *(long *)(param_1 + 0x40) + 0x18;
  }
  else {
    void std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<string >(string&&)(param_1 + 0x38,&uStack_140);
  }
  if ((uStack_140 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pcStack_130);
  }
  if (((ulong)puStack_168 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_158);
  }
  puVar14 = *(undefined8 **)(param_1 + 0x68);
  if (*(undefined8 **)(param_1 + 0x70) != puVar14) {
code_r0x01bad654:
    do {
      uStack_140 = 0;
      uStack_138 = 0;
      pcStack_130 = (char *)0x0;
      void CParameterPropertyBase<51u>::CryptString<string >(string&, string const&)(&uStack_140,lStack_188 + 0x138);
      uVar17 = uStack_140;
      bVar2 = *(byte *)(puVar14 + 1);
      uVar7 = (ulong)(bVar2 >> 1);
      if ((bVar2 & 1) != 0) {
        uVar7 = puVar14[2];
      }
      uVar15 = uStack_140 >> 1 & 0x7f;
      if ((uStack_140 & 1) != 0) {
        uVar15 = uStack_138;
      }
      if (uVar7 == uVar15) {
        lVar8 = puVar14[3];
        if ((bVar2 & 1) == 0) {
          lVar8 = (long)puVar14 + 9;
        }
        pcVar16 = (char *)((ulong)&uStack_140 | 1);
        if ((uStack_140 & 1) != 0) {
          pcVar16 = pcStack_130;
        }
        if ((bVar2 & 1) == 0) {
          if (uVar7 != 0) {
            pcVar9 = (char *)((long)puVar14 + 9);
            lVar8 = -(ulong)(bVar2 >> 1);
            do {
              if (*pcVar9 != *pcVar16) goto code_r0x01bad6ec;
              pcVar9 = pcVar9 + 1;
              lVar8 = lVar8 + 1;
              pcVar16 = pcVar16 + 1;
            } while (lVar8 != 0);
          }
        }
        else if (uVar7 != 0) {
          iVar6 = memcmp(lVar8);
          bVar4 = iVar6 == 0;
          goto joined_r0x01bad6f0;
        }
        bVar4 = true;
      }
      else {
code_r0x01bad6ec:
        bVar4 = false;
      }
joined_r0x01bad6f0:
      if ((uVar17 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pcStack_130);
      }
      if (bVar4) {
        puVar11 = *(undefined8 **)(param_1 + 0x70);
        puVar10 = puVar14 + 4;
        puVar18 = puVar14;
        if (puVar10 == puVar11) {
code_r0x01bad628:
          do {
            *(undefined8 **)(param_1 + 0x70) = puVar10 + -4;
            puVar11 = puVar10 + -4;
            if ((*(byte *)(puVar10 + -3) & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar10[-1]);
              puVar11 = *(undefined8 **)(param_1 + 0x70);
            }
            puVar10 = puVar11;
          } while (puVar10 != puVar18);
        }
        else {
          do {
            *puVar18 = puVar18[4];
            pbVar12 = (byte *)(puVar18 + 1);
            if ((*pbVar12 & 1) == 0) {
              *(undefined2 *)(puVar18 + 1) = 0;
            }
            else {
              *(undefined1 *)puVar18[3] = 0;
              puVar18[2] = 0;
            }
            string::reserve(unsigned long)(pbVar12,0);
            puVar18[3] = puVar18[7];
            puVar18[2] = puVar18[6];
            *(undefined8 *)pbVar12 = puVar18[5];
            puVar18[6] = 0;
            puVar18[7] = 0;
            puVar18[5] = 0;
            puVar18 = puVar18 + 4;
          } while (puVar11 + -4 != puVar18);
          puVar10 = *(undefined8 **)(param_1 + 0x70);
          if (puVar10 != puVar18) goto code_r0x01bad628;
        }
        if (puVar18 == puVar14) break;
        goto code_r0x01bad654;
      }
      puVar14 = puVar14 + 4;
    } while (*(undefined8 **)(param_1 + 0x70) != puVar14);
  }
code_r0x01bad784:
  if (lStack_180 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return;
}

// ==== CMenuVoiceManager::IsReadyResource(unsigned int, unsigned int)
// vaddr 0x1aad7a8 | ghidra 0x1bad7a8 | size 440 | symbol _ZN17CMenuVoiceManager15IsReadyResourceEjj | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN17CMenuVoiceManager15IsReadyResourceEjj(long param_1,int param_2,int param_3)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  ulong uVar4;
  ulong uVar5;
  int *piVar6;
  int *piVar7;
  ulong uVar8;
  ulong uStack_80;
  ulong uStack_78;
  ulong uStack_70;
  int *piStack_68;
  
  puVar1 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  piVar7 = *(int **)(param_1 + 0x68);
  piVar6 = *(int **)(param_1 + 0x70);
  if (piVar7 != piVar6) {
    do {
      piStack_68 = piVar7;
      if ((*piVar7 == param_2) && (piVar7[1] == param_3)) {
        lVar2 = *(long *)puVar1;
        if (lVar2 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar2 = *(long *)puVar1;
        }
        uVar3 = CUIManager::rUIVoiceManager()(lVar2);
        if ((*(byte *)(piVar7 + 2) & 1) == 0) {
          lVar2 = (long)piVar7 + 9;
        }
        else {
          lVar2 = *(long *)(piVar7 + 6);
        }
        uStack_78 = 0;
        uStack_70 = 0;
        uStack_80 = 0;
        uVar4 = strlen(lVar2);
        if (uVar4 < 0x17) {
          uStack_80 = CONCAT71(uStack_80._1_7_,(char)(uVar4 << 1));
          uVar5 = (ulong)&uStack_80 | 1;
          if (uVar4 != 0) goto code_r0x01bad8e4;
        }
        else {
          uVar8 = uVar4 + 0x10 & 0xfffffffffffffff0;
          if (uVar8 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          uVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar8,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (uVar5 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uStack_80 = uVar8 | 1;
          uStack_78 = uVar4;
          uStack_70 = uVar5;
code_r0x01bad8e4:
          memcpy(uVar5,lVar2,uVar4);
        }
        *(undefined1 *)(uVar5 + uVar4) = 0;
        uVar4 = CUIVoiceManager::IsReadyResourcePack(string const&)(uVar3,&uStack_80);
        if ((uStack_80 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_70);
        }
        if ((uVar4 & 1) == 0) {
          return 0;
        }
        piVar6 = *(int **)(param_1 + 0x70);
      }
      piVar7 = piStack_68 + 8;
    } while (piVar7 != piVar6);
  }
  return 1;
}

// ==== CMenuVoiceManager::IsReadyResource(char const*)
// vaddr 0x1aad960 | ghidra 0x1bad960 | size 568 | symbol _ZN17CMenuVoiceManager15IsReadyResourceEPKc | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN17CMenuVoiceManager15IsReadyResourceEPKc(void)

{
  ulong *puVar1;
  undefined *puVar2;
  undefined4 uVar3;
  uint uVar4;
  ulong uVar5;
  long lVar6;
  undefined8 uVar7;
  ulong uVar8;
  ulong uVar9;
  long lStack_188;
  long lStack_180;
  undefined1 auStack_178 [16];
  undefined *puStack_168;
  undefined8 uStack_160;
  ulong *puStack_158;
  undefined8 uStack_150;
  undefined4 uStack_148;
  undefined1 uStack_144;
  ulong uStack_140;
  ulong uStack_138;
  ulong uStack_130;
  
  Framework::CHash32::CHash32(char const*)(auStack_178);
  uVar3 = Framework::CHash32::operator unsigned int() const(auStack_178);
  Framework::CHash32::~CHash32()(auStack_178);
  puVar2 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar6 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar6 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar6 = *(long *)puVar2;
  }
  uVar7 = *(undefined8 *)(*(long *)(lVar6 + 0x5f8) + 0x430);
  snprintf(&uStack_140,0x100,&UNK_027e6d32/*"%u"*/,uVar3);
  puStack_168 = &UNK_027ffe64/*"id"*/;
  uStack_160 = 2;
  puStack_158 = &uStack_140;
  uStack_150 = strlen(&uStack_140);
  uStack_148 = 0;
  uStack_144 = 0;
  uVar4 = 1;
  CMasterParameterBaseSqlite_Simple<CMasterParameterMenuCommonVoiceElement>::ParameterByQuery(char const*, Aska::Yayoi::QueryParam*, unsigned int) const(&lStack_188,uVar7,&UNK_028d2452/*"SELECT * FROM master_menu_common_voice WHERE id=?"*/,&puStack_168,1);
  puVar2 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lStack_188 == 0) goto code_r0x01badb70;
  lVar6 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lVar6 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar6 = *(long *)puVar2;
  }
  uVar7 = CUIManager::rUIVoiceManager()(lVar6);
  puStack_168 = (undefined *)0x0;
  uStack_160 = 0;
  puStack_158 = (ulong *)0x0;
  void CParameterPropertyBase<51u>::CryptString<string >(string&, string const&)(&puStack_168,lStack_188 + 0x138);
  uStack_138 = 0;
  uStack_130 = 0;
  puVar1 = (ulong *)((ulong)&puStack_168 | 1);
  if (((ulong)puStack_168 & 1) != 0) {
    puVar1 = puStack_158;
  }
  uStack_140 = 0;
  uVar5 = strlen(puVar1);
  if (uVar5 < 0x17) {
    uVar8 = (ulong)&uStack_140 | 1;
    uStack_140 = CONCAT71(uStack_140._1_7_,(char)(uVar5 << 1));
    if (uVar5 != 0) goto code_r0x01badb2c;
  }
  else {
    uVar9 = uVar5 + 0x10 & 0xfffffffffffffff0;
    if (uVar9 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar8 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_140 = uVar9 | 1;
    uStack_138 = uVar5;
    uStack_130 = uVar8;
code_r0x01badb2c:
    memcpy(uVar8,puVar1,uVar5);
  }
  *(undefined1 *)(uVar8 + uVar5) = 0;
  uVar4 = CUIVoiceManager::IsReadyResourcePack(string const&)(uVar7,&uStack_140);
  if ((uStack_140 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_130);
  }
  if (((ulong)puStack_168 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_158);
  }
code_r0x01badb70:
  if (lStack_180 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return uVar4 & 1;
}

// ==== CMenuVoiceManager::IsExistRemoveResource()
// vaddr 0x1aadb98 | ghidra 0x1badb98 | size 16 | symbol _ZN17CMenuVoiceManager21IsExistRemoveResourceEv | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN17CMenuVoiceManager21IsExistRemoveResourceEv(long param_1)

{
  return *(long *)(param_1 + 0x38) != *(long *)(param_1 + 0x40);
}

// ==== CMenuVoiceManager::GetPlayIDListBySoundPackage(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, Framework::CSTLVector<unsigned int>&)
// vaddr 0x1aadba8 | ghidra 0x1badba8 | size 388 | symbol _ZN17CMenuVoiceManager27GetPlayIDListBySoundPackageERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEERNS4_10CSTLVectorIjEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManager27GetPlayIDListBySoundPackageERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEERNS4_10CSTLVectorIjEE
               (undefined8 param_1,byte *param_2,long param_3)

{
  undefined4 *puVar1;
  long *plVar2;
  undefined *puVar3;
  long lVar4;
  byte *pbVar5;
  long lVar6;
  long *plVar7;
  undefined8 uVar8;
  long lStack_190;
  undefined8 uStack_188;
  long *plStack_180;
  undefined8 uStack_178;
  undefined4 uStack_170;
  undefined *puStack_168;
  undefined8 uStack_160;
  undefined4 *puStack_158;
  undefined8 uStack_150;
  undefined4 uStack_148;
  undefined1 uStack_144;
  undefined4 auStack_140 [64];
  
  puVar3 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar3;
  }
  uStack_188 = 0;
  lStack_190 = 0;
  uStack_178 = 0;
  plStack_180 = (long *)0x0;
  uStack_170 = 0x3f800000;
  pbVar5 = *(byte **)(param_2 + 0x10);
  uVar8 = *(undefined8 *)(*(long *)(lVar4 + 0x5f8) + 0x430);
  if ((*param_2 & 1) == 0) {
    pbVar5 = param_2 + 1;
  }
  snprintf(auStack_140,0x100,&UNK_027f6a37/*"%s"*/,pbVar5);
  puStack_168 = &UNK_027dc134/*"voice_sound_package"*/;
  uStack_160 = 0x13;
  puStack_158 = auStack_140;
  uStack_150 = strlen(auStack_140);
  uStack_148 = 0;
  uStack_144 = 0;
  CMasterParameterBaseSqlite_Simple<CMasterParameterMenuCommonVoiceElement>::ParameterByQuery(char const*, Framework::CSTLUnorderedMap<unsigned int, CMasterParameterMenuCommonVoiceElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >&, Aska::Yayoi::QueryParam*, unsigned int) const(uVar8,&UNK_028d24f7/*"SELECT * FROM master_menu_common_voice WHERE voice_sound_package=?"*/,&lStack_190,&puStack_168,1);
  for (plVar7 = plStack_180; lVar4 = lStack_190, plVar2 = plStack_180, plVar7 != (long *)0x0;
      plVar7 = (long *)*plVar7) {
    auStack_140[0] = (undefined4)plVar7[10];
    puVar1 = *(undefined4 **)(param_3 + 8);
    if (puVar1 < *(undefined4 **)(param_3 + 0x10)) {
      if (puVar1 == (undefined4 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      *puVar1 = auStack_140[0];
      *(long *)(param_3 + 8) = *(long *)(param_3 + 8) + 4;
    }
    else {
      void std::__ndk1::vector<unsigned int, Framework::CSTLAllocator<unsigned int, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<unsigned int>(unsigned int&&)(param_3,auStack_140);
    }
  }
  while (plVar2 != (long *)0x0) {
    lVar6 = *plVar2;
    lStack_190 = lVar4;
    CMasterParameterMenuCommonVoiceElement::~CMasterParameterMenuCommonVoiceElement()(plVar2 + 3);
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(plVar2);
    lVar4 = lStack_190;
    plVar2 = (long *)lVar6;
  }
  lStack_190 = 0;
  if (lVar4 != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  return;
}

// ==== CMenuVoiceManager::IsMascot(unsigned int)
// vaddr 0x1aadd2c | ghidra 0x1badd2c | size 40 | symbol _ZN17CMenuVoiceManager8IsMascotEj | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN17CMenuVoiceManager8IsMascotEj(undefined8 param_1,int param_2)

{
  if (param_2 - 2U < 5) {
    return 0x19U >> (ulong)(param_2 - 2U & 0x1f) & 1;
  }
  return 0;
}

// ==== CMenuVoiceManager::IsPlaying(char const*) const
// vaddr 0x1aadd54 | ghidra 0x1badd54 | size 336 | symbol _ZNK17CMenuVoiceManager9IsPlayingEPKc | lib libSOA-3.7.0.so | 2026-10-08
byte _ZNK17CMenuVoiceManager9IsPlayingEPKc(long param_1)

{
  undefined8 *puVar1;
  long lVar2;
  long lVar3;
  int *piVar4;
  byte bVar5;
  int iVar6;
  undefined8 uVar7;
  int iVar8;
  byte abStack_88 [16];
  undefined8 uStack_78;
  undefined8 *puStack_70;
  undefined8 *puStack_68;
  undefined1 auStack_50 [16];
  
  uVar7 = *(undefined8 *)PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
  Framework::CHash32::CHash32(char const*)(auStack_50);
  iVar6 = Framework::CHash32::operator unsigned int() const(auStack_50);
  Framework::CHash32::~CHash32()(auStack_50);
  piVar4 = *(int **)(param_1 + 8);
  while (piVar4 != *(int **)(param_1 + 0x10)) {
    iVar8 = *piVar4;
    piVar4 = piVar4 + 2;
    if (iVar8 == iVar6) {
      return 1;
    }
  }
  lVar3 = *(long *)(param_1 + 0x28);
  bVar5 = 1;
  for (lVar2 = *(long *)(param_1 + 0x20); lVar2 != lVar3; lVar2 = lVar2 + 0x38) {
    CMenuVoiceManager::PlayingData::PlayingData(CMenuVoiceManager::PlayingData const&)(abStack_88,lVar2);
    for (puVar1 = puStack_70; puVar1 != puStack_68; puVar1 = puVar1 + 2) {
      if (*(int *)(puVar1 + 1) == iVar6) {
        bVar5 = CSoundManager::IsPlaying(unsigned long) const(uVar7,*puVar1);
        iVar8 = 1;
        goto joined_r0x01bade4c;
      }
    }
    iVar8 = 6;
joined_r0x01bade4c:
    if (puStack_70 != (undefined8 *)0x0) {
      if (puStack_68 != puStack_70) {
        puStack_68 = (undefined8 *)
                     ((long)puStack_68 +
                     (~((long)puStack_68 + (-0x10 - (long)puStack_70)) & 0xfffffffffffffff0U));
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
    if ((abStack_88[0] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_78);
    }
    if (iVar8 != 6) goto code_r0x01bade78;
  }
  iVar8 = 4;
code_r0x01bade78:
  return bVar5 & iVar8 != 4;
}

// ==== CMenuVoiceManager::GetMascotToCharaType()
// vaddr 0x1aadea4 | ghidra 0x1badea4 | size 304 | symbol _ZN17CMenuVoiceManager20GetMascotToCharaTypeEv | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN17CMenuVoiceManager20GetMascotToCharaTypeEv(void)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  byte abStack_48 [8];
  ulong uStack_40;
  ulong uStack_38;
  
  CUIUtility::GetMascot()(abStack_48);
  uVar1 = (ulong)(abStack_48[0] >> 1);
  if ((abStack_48[0] & 1) != 0) {
    uVar1 = uStack_40;
  }
  uVar2 = 6;
  if (uVar1 < 7) {
    uVar2 = uVar1;
  }
  if (uVar2 == 0) {
code_r0x01badf08:
    if ((5 < uVar1) && (uVar1 < 7)) {
      uVar6 = 2;
      goto joined_r0x01badfb0;
    }
    if (uVar2 != 0) goto code_r0x01badf28;
code_r0x01badf50:
    if ((5 < uVar1) && (uVar1 < 7)) {
      uVar6 = 5;
      goto joined_r0x01badfb0;
    }
    if (uVar2 != 0) goto code_r0x01badf70;
code_r0x01badf98:
    uVar5 = (uint)(6 < uVar1);
    if (uVar1 < 6) {
      uVar5 = 0xffffffff;
    }
  }
  else {
    uVar3 = (ulong)abStack_48 | 1;
    if ((abStack_48[0] & 1) != 0) {
      uVar3 = uStack_38;
    }
    iVar4 = memcmp(uVar3,&UNK_028b06f4/*"cp0003"*/,uVar2);
    if (iVar4 == 0) goto code_r0x01badf08;
code_r0x01badf28:
    uVar3 = (ulong)abStack_48 | 1;
    if ((abStack_48[0] & 1) != 0) {
      uVar3 = uStack_38;
    }
    iVar4 = memcmp(uVar3,&UNK_028d23fc/*"cp0012"*/,uVar2);
    if (iVar4 == 0) goto code_r0x01badf50;
code_r0x01badf70:
    uVar3 = (ulong)abStack_48 | 1;
    if ((abStack_48[0] & 1) != 0) {
      uVar3 = uStack_38;
    }
    uVar5 = memcmp(uVar3,&UNK_028d2403/*"cc0040"*/,uVar2);
    if (uVar5 == 0) goto code_r0x01badf98;
  }
  uVar6 = 6;
  if (uVar5 != 0) {
    uVar6 = 0;
  }
joined_r0x01badfb0:
  if ((abStack_48[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_38);
  }
  return uVar6;
}

// ==== CMenuVoiceManager::GetUseCharaType(unsigned int)
// vaddr 0x1aadfd4 | ghidra 0x1badfd4 | size 64 | symbol _ZN17CMenuVoiceManager15GetUseCharaTypeEj | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN17CMenuVoiceManager15GetUseCharaTypeEj(undefined8 param_1,uint param_2)

{
  uint uVar1;
  
  if (((param_2 < 7) && ((1 << (ulong)(param_2 & 0x1f) & 100U) != 0)) &&
     (uVar1 = CMenuVoiceManager::GetMascotToCharaType()(), uVar1 != param_2 && uVar1 != 0)) {
    param_2 = uVar1;
  }
  return param_2;
}

// ==== CMenuVoiceManager::ChangeMascotVoiceID(unsigned int, char const*)
// vaddr 0x1aae014 | ghidra 0x1bae014 | size 508 | symbol _ZN17CMenuVoiceManager19ChangeMascotVoiceIDEjPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CMenuVoiceManager19ChangeMascotVoiceIDEjPKc
               (ulong *param_1,undefined8 param_2,int param_3,undefined8 param_4)

{
  byte bVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  byte *pbVar6;
  ulong uVar7;
  byte abStack_70 [8];
  ulong uStack_68;
  ulong uStack_60;
  byte abStack_58 [16];
  undefined8 uStack_48;
  
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  uVar2 = strlen(param_4);
  if (uVar2 < 0x17) {
    pbVar6 = (byte *)((long)param_1 + 1);
    *(byte *)param_1 = (byte)(uVar2 << 1);
    if (uVar2 != 0) goto code_r0x01bae0c8;
  }
  else {
    uVar7 = uVar2 + 0x10 & 0xfffffffffffffff0;
    if (uVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    pbVar6 = (byte *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar7,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (pbVar6 == (byte *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uVar2;
    param_1[2] = (ulong)pbVar6;
    *param_1 = uVar7 | 1;
code_r0x01bae0c8:
    memcpy(pbVar6,param_4,uVar2);
  }
  pbVar6[uVar2] = 0;
  if (param_3 != 2) {
    return;
  }
  CUIUtility::GetMascot()(abStack_58);
  string std::__ndk1::operator+<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >(char const*, string const&)(abStack_70,&UNK_029e43f2/*"_"*/,abStack_58);
  bVar1 = (byte)*param_1;
  uVar4 = (ulong)bVar1;
  uVar2 = (ulong)(abStack_70[0] >> 1);
  uVar7 = (ulong)abStack_70 | 1;
  if ((abStack_70[0] & 1) != 0) {
    uVar2 = uStack_68;
    uVar7 = uStack_60;
  }
  if ((bVar1 & 1) == 0) {
    lVar3 = 0x16;
    if ((bVar1 & 1) == 0) {
code_r0x01bae148:
      uVar5 = (ulong)(((uint)uVar4 & 0xfe) >> 1);
      goto code_r0x01bae150;
    }
  }
  else {
    uVar4 = *param_1;
    lVar3 = (uVar4 & 0xfffffffffffffffe) - 1;
    if ((uVar4 & 1) == 0) goto code_r0x01bae148;
  }
  uVar5 = param_1[1];
code_r0x01bae150:
  if (lVar3 - uVar5 < uVar2) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(param_1,lVar3,(uVar2 - lVar3) + uVar5,uVar5,uVar5,0,uVar2);
  }
  else if (uVar2 != 0) {
    if ((uVar4 & 1) == 0) {
      pbVar6 = (byte *)((long)param_1 + 1);
    }
    else {
      pbVar6 = (byte *)param_1[2];
    }
    memcpy(pbVar6 + uVar5,uVar7,uVar2);
    uVar5 = uVar5 + uVar2;
    if ((*param_1 & 1) == 0) {
      *(char *)param_1 = (char)uVar5 * '\x02';
      pbVar6[uVar5] = 0;
    }
    else {
      param_1[1] = uVar5;
      pbVar6[uVar5] = 0;
    }
  }
  if ((abStack_70[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_60);
  }
  if ((abStack_58[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
  return;
}

// ==== void std::__ndk1::vector<CMenuVoiceManager::ReserveData, Framework::CSTLAllocator<CMenuVoiceManager::ReserveData, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<CMenuVoiceManager::ReserveData&>(CMenuVoiceManager::ReserveData&)
// vaddr 0x1aaf974 | ghidra 0x1baf974 | size 288 | symbol _ZNSt6__ndk16vectorIN17CMenuVoiceManager11ReserveDataEN9Framework13CSTLAllocatorIS2_NS3_22CSTLVectorAllocatorInfEEEE24__emplace_back_slow_pathIJRS2_EEEvDpOT_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk16vectorIN17CMenuVoiceManager11ReserveDataEN9Framework13CSTLAllocatorIS2_NS3_22CSTLVectorAllocatorInfEEEE24__emplace_back_slow_pathIJRS2_EEEvDpOT_
               (long *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  long lVar2;
  ulong uVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  ulong uVar6;
  long lVar7;
  undefined8 *puVar8;
  
  lVar2 = param_1[2] - *param_1;
  lVar7 = param_1[1] - *param_1 >> 3;
  if ((ulong)(lVar2 >> 3) < 0xfffffffffffffff) {
    uVar3 = lVar2 >> 2;
    uVar6 = lVar7 + 1U;
    if (lVar7 + 1U <= uVar3) {
      uVar6 = uVar3;
    }
    if (uVar6 == 0) {
      lVar2 = 0;
      puVar8 = (undefined8 *)(lVar7 << 3);
      goto joined_r0x01bafa8c;
    }
  }
  else {
    uVar6 = 0x1fffffffffffffff;
  }
  lVar2 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6 << 3,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    puVar8 = (undefined8 *)(lVar7 * 8);
  }
  else {
    puVar8 = (undefined8 *)(lVar2 + lVar7 * 8);
  }
joined_r0x01bafa8c:
  if (puVar8 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  puVar4 = puVar8 + 1;
  *puVar8 = *param_2;
  puVar1 = (undefined8 *)*param_1;
  puVar5 = (undefined8 *)param_1[1];
  if (puVar5 != puVar1) {
    do {
      puVar5 = puVar5 + -1;
      puVar8[-1] = *puVar5;
      puVar8 = puVar8 + -1;
    } while (puVar1 != puVar5);
    puVar1 = (undefined8 *)*param_1;
  }
  *param_1 = (long)puVar8;
  param_1[1] = (long)puVar4;
  param_1[2] = lVar2 + uVar6 * 8;
  if (puVar1 != (undefined8 *)0x0) {
    (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)();
    return;
  }
  return;
}

// ==== void std::__ndk1::vector<CMenuVoiceManager::ResourceData, Framework::CSTLAllocator<CMenuVoiceManager::ResourceData, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<CMenuVoiceManager::ResourceData&>(CMenuVoiceManager::ResourceData&)
// vaddr 0x1aafa94 | ghidra 0x1bafa94 | size 532 | symbol _ZNSt6__ndk16vectorIN17CMenuVoiceManager12ResourceDataEN9Framework13CSTLAllocatorIS2_NS3_22CSTLVectorAllocatorInfEEEE24__emplace_back_slow_pathIJRS2_EEEvDpOT_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk16vectorIN17CMenuVoiceManager12ResourceDataEN9Framework13CSTLAllocatorIS2_NS3_22CSTLVectorAllocatorInfEEEE24__emplace_back_slow_pathIJRS2_EEEvDpOT_
               (long *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  ulong *puVar8;
  long lVar9;
  long lStack_78;
  undefined8 *puStack_70;
  undefined8 *puStack_68;
  long lStack_60;
  long *plStack_58;
  
  plStack_58 = param_1 + 2;
  lVar4 = *plStack_58 - *param_1;
  lVar7 = param_1[1] - *param_1 >> 5;
  if ((ulong)(lVar4 >> 5) < 0x3ffffffffffffff) {
    uVar5 = lVar4 >> 4;
    uVar6 = lVar7 + 1U;
    if (lVar7 + 1U <= uVar5) {
      uVar6 = uVar5;
    }
    if (uVar6 != 0) goto code_r0x01bafb04;
    lVar4 = 0;
  }
  else {
    uVar6 = 0x7ffffffffffffff;
code_r0x01bafb04:
    lStack_60 = 0;
    lVar4 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6 << 5,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
    if (lVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
  }
  puVar1 = (undefined8 *)(lVar4 + lVar7 * 0x20);
  lStack_60 = lVar4 + uVar6 * 0x20;
  lStack_78 = lVar4;
  puStack_70 = puVar1;
  puStack_68 = puVar1;
  if (puVar1 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  *puVar1 = *param_2;
  puVar8 = puVar1 + 1;
  *puVar8 = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  if ((param_2[1] & 1) == 0) {
    puVar1[3] = param_2[3];
    uVar6 = param_2[1];
    puVar1[2] = param_2[2];
    *puVar8 = uVar6;
    goto code_r0x01bafc34;
  }
  uVar6 = param_2[2];
  uVar2 = param_2[3];
  if (uVar6 < 0x17) {
    lVar9 = (long)puVar1 + 9;
    *(char *)puVar8 = (char)(uVar6 << 1);
    if (uVar6 != 0) goto code_r0x01bafc20;
  }
  else {
    uVar5 = uVar6 + 0x10 & 0xfffffffffffffff0;
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    lVar9 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (lVar9 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    lVar4 = lVar4 + lVar7 * 0x20;
    *(ulong *)(lVar4 + 0x10) = uVar6;
    *(long *)(lVar4 + 0x18) = lVar9;
    *puVar8 = uVar5 | 1;
code_r0x01bafc20:
    memcpy(lVar9,uVar2,uVar6);
  }
  *(undefined1 *)(lVar9 + uVar6) = 0;
code_r0x01bafc34:
  puStack_68 = puStack_68 + 4;
  std::__ndk1::vector<CMenuVoiceManager::ResourceData, Framework::CSTLAllocator<CMenuVoiceManager::ResourceData, Framework::CSTLVectorAllocatorInf> >::__swap_out_circular_buffer(std::__ndk1::__split_buffer<CMenuVoiceManager::ResourceData, Framework::CSTLAllocator<CMenuVoiceManager::ResourceData, Framework::CSTLVectorAllocatorInf>&>&)(param_1,&lStack_78);
  puVar1 = puStack_70;
  while (puVar3 = puStack_68, puVar3 != puVar1) {
    puStack_68 = puVar3 + -4;
    if ((*(byte *)(puVar3 + -3) & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar3[-1]);
    }
  }
  if (lStack_78 != 0) {
    puStack_68 = puVar3;
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  return;
}

// ==== std::__ndk1::vector<CMenuVoiceManager::ResourceData, Framework::CSTLAllocator<CMenuVoiceManager::ResourceData, Framework::CSTLVectorAllocatorInf> >::__swap_out_circular_buffer(std::__ndk1::__split_buffer<CMenuVoiceManager::ResourceData, Framework::CSTLAllocator<CMenuVoiceManager::ResourceData, Framework::CSTLVectorAllocatorInf>&>&)
// vaddr 0x1aafca8 | ghidra 0x1bafca8 | size 368 | symbol _ZNSt6__ndk16vectorIN17CMenuVoiceManager12ResourceDataEN9Framework13CSTLAllocatorIS2_NS3_22CSTLVectorAllocatorInfEEEE26__swap_out_circular_bufferERNS_14__split_bufferIS2_RS6_EE | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk16vectorIN17CMenuVoiceManager12ResourceDataEN9Framework13CSTLAllocatorIS2_NS3_22CSTLVectorAllocatorInfEEEE26__swap_out_circular_bufferERNS_14__split_bufferIS2_RS6_EE
               (long *param_1,undefined8 *param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  long lVar5;
  undefined8 *puVar6;
  long lVar7;
  ulong uVar8;
  undefined8 *puVar9;
  undefined8 *puVar4;
  
  puVar9 = (undefined8 *)*param_1;
  if ((undefined8 *)param_1[1] == puVar9) {
    lVar5 = param_2[1];
  }
  else {
    lVar5 = param_2[1];
    puVar3 = (undefined8 *)param_1[1];
    do {
      puVar4 = puVar3 + -4;
      uVar2 = *puVar4;
      puVar6 = (undefined8 *)(lVar5 + -0x18);
      *puVar6 = 0;
      *(undefined8 *)(lVar5 + -0x10) = 0;
      *(undefined8 *)(lVar5 + -8) = 0;
      *(undefined8 *)(lVar5 + -0x20) = uVar2;
      if ((*(byte *)(puVar3 + -3) & 1) == 0) {
        *(undefined8 *)(lVar5 + -8) = puVar3[-1];
        uVar2 = puVar3[-3];
        *(undefined8 *)(lVar5 + -0x10) = puVar3[-2];
        *puVar6 = uVar2;
      }
      else {
        uVar1 = puVar3[-2];
        uVar2 = puVar3[-1];
        if (uVar1 < 0x17) {
          lVar7 = lVar5 + -0x17;
          *(char *)puVar6 = (char)(uVar1 << 1);
          if (uVar1 != 0) goto code_r0x01bafd94;
        }
        else {
          uVar8 = uVar1 + 0x10 & 0xfffffffffffffff0;
          if (uVar8 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          lVar7 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar8,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (lVar7 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          *(ulong *)(lVar5 + -0x10) = uVar1;
          *(long *)(lVar5 + -8) = lVar7;
          *(ulong *)(lVar5 + -0x18) = uVar8 | 1;
code_r0x01bafd94:
          memcpy(lVar7,uVar2,uVar1);
        }
        *(undefined1 *)(lVar7 + uVar1) = 0;
      }
      lVar5 = param_2[1] + -0x20;
      param_2[1] = lVar5;
      puVar3 = puVar4;
    } while (puVar9 != puVar4);
    puVar9 = (undefined8 *)*param_1;
  }
  *param_1 = lVar5;
  param_2[1] = puVar9;
  lVar5 = param_1[1];
  param_1[1] = param_2[2];
  param_2[2] = lVar5;
  lVar5 = param_1[2];
  param_1[2] = param_2[3];
  param_2[3] = lVar5;
  *param_2 = param_2[1];
  return;
}

// ==== void std::__ndk1::vector<CMenuVoiceManager::PlayingData::PlayUnit, Framework::CSTLAllocator<CMenuVoiceManager::PlayingData::PlayUnit, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<CMenuVoiceManager::PlayingData::PlayUnit&>(CMenuVoiceManager::PlayingData::PlayUnit&)
// vaddr 0x1aafe18 | ghidra 0x1bafe18 | size 292 | symbol _ZNSt6__ndk16vectorIN17CMenuVoiceManager11PlayingData8PlayUnitEN9Framework13CSTLAllocatorIS3_NS4_22CSTLVectorAllocatorInfEEEE24__emplace_back_slow_pathIJRS3_EEEvDpOT_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk16vectorIN17CMenuVoiceManager11PlayingData8PlayUnitEN9Framework13CSTLAllocatorIS3_NS4_22CSTLVectorAllocatorInfEEEE24__emplace_back_slow_pathIJRS3_EEEvDpOT_
               (long *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  undefined8 *puVar8;
  undefined8 uVar9;
  
  lVar3 = param_1[2] - *param_1;
  lVar7 = param_1[1] - *param_1 >> 4;
  if ((ulong)(lVar3 >> 4) < 0x7ffffffffffffff) {
    uVar4 = lVar3 >> 3;
    uVar6 = lVar7 + 1U;
    if (lVar7 + 1U <= uVar4) {
      uVar6 = uVar4;
    }
    if (uVar6 == 0) {
      lVar3 = 0;
      puVar8 = (undefined8 *)(lVar7 << 4);
      goto joined_r0x01baff34;
    }
  }
  else {
    uVar6 = 0xfffffffffffffff;
  }
  lVar3 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6 << 4,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    puVar8 = (undefined8 *)(lVar7 * 0x10);
  }
  else {
    puVar8 = (undefined8 *)(lVar3 + lVar7 * 0x10);
  }
joined_r0x01baff34:
  if (puVar8 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  uVar9 = *param_2;
  puVar1 = puVar8 + 2;
  puVar8[1] = param_2[1];
  *puVar8 = uVar9;
  lVar7 = *param_1;
  lVar5 = param_1[1];
  if (lVar5 != lVar7) {
    do {
      puVar2 = (undefined8 *)(lVar5 + -8);
      uVar9 = *(undefined8 *)(lVar5 + -0x10);
      lVar5 = lVar5 + -0x10;
      puVar8[-1] = *puVar2;
      puVar8[-2] = uVar9;
      puVar8 = puVar8 + -2;
    } while (lVar7 != lVar5);
    lVar7 = *param_1;
  }
  *param_1 = (long)puVar8;
  param_1[1] = (long)puVar1;
  param_1[2] = lVar3 + uVar6 * 0x10;
  if (lVar7 != 0) {
    (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)();
    return;
  }
  return;
}

// ==== void std::__ndk1::vector<CMenuVoiceManager::PlayingData, Framework::CSTLAllocator<CMenuVoiceManager::PlayingData, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<CMenuVoiceManager::PlayingData const&>(CMenuVoiceManager::PlayingData const&)
// vaddr 0x1aaff3c | ghidra 0x1baff3c | size 448 | symbol _ZNSt6__ndk16vectorIN17CMenuVoiceManager11PlayingDataEN9Framework13CSTLAllocatorIS2_NS3_22CSTLVectorAllocatorInfEEEE21__push_back_slow_pathIRKS2_EEvOT_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x01bb00a8: Changing call to branch */

void _ZNSt6__ndk16vectorIN17CMenuVoiceManager11PlayingDataEN9Framework13CSTLAllocatorIS2_NS3_22CSTLVectorAllocatorInfEEEE21__push_back_slow_pathIRKS2_EEvOT_
               (long *param_1,undefined8 param_2)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  
  lVar1 = param_1[2] - *param_1 >> 3;
  lVar4 = param_1[1] - *param_1 >> 3;
  if ((ulong)(lVar1 * 0x6db6db6db6db6db7) < 0x249249249249249) {
    uVar8 = lVar4 * 0x6db6db6db6db6db7 + 1;
    uVar2 = lVar1 * -0x2492492492492492;
    if (uVar8 <= uVar2) {
      uVar8 = uVar2;
    }
    if (uVar8 == 0) {
      lVar1 = 0;
      goto code_r0x01bb0000;
    }
  }
  else {
    uVar8 = 0x492492492492492;
  }
  lVar1 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar8 * 0x38,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
code_r0x01bb0000:
  lVar4 = lVar1 + lVar4 * 8;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  CMenuVoiceManager::PlayingData::PlayingData(CMenuVoiceManager::PlayingData const&)(lVar4,param_2);
  lVar6 = *param_1;
  lVar5 = param_1[1];
  lVar3 = lVar4 + 0x38;
  lVar7 = lVar6;
  if (lVar5 != lVar6) {
    do {
      lVar5 = lVar5 + -0x38;
      CMenuVoiceManager::PlayingData::PlayingData(CMenuVoiceManager::PlayingData const&)(lVar4 + -0x38,lVar5);
      lVar4 = lVar4 + -0x38;
    } while (lVar6 != lVar5);
    lVar6 = *param_1;
    lVar7 = param_1[1];
  }
  *param_1 = lVar4;
  param_1[1] = lVar3;
  param_1[2] = lVar1 + uVar8 * 0x38;
  do {
    lVar1 = lVar7;
    if (lVar1 == lVar6) {
      lVar4 = lVar6;
      if (lVar6 == 0) {
        return;
      }
code_r0x011d23a0:
      (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)(lVar4);
      return;
    }
    lVar4 = *(long *)(lVar1 + -0x20);
    if (lVar4 != 0) {
      lVar3 = *(long *)(lVar1 + -0x18);
      if (lVar3 != lVar4) {
        *(ulong *)(lVar1 + -0x18) = lVar3 + (~((lVar3 + -0x10) - lVar4) & 0xfffffffffffffff0U);
      }
      goto code_r0x011d23a0;
    }
    lVar7 = lVar1 + -0x38;
    if ((*(byte *)(lVar1 + -0x38) & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar1 + -0x28));
    }
  } while( true );
}

// ==== std::__ndk1::enable_if<__is_forward_iterator<CMenuVoiceManager::PlayingData::PlayUnit*>::value&&is_constructible<CMenuVoiceManager::PlayingData::PlayUnit, std::__ndk1::iterator_traits<CMenuVoiceManager::PlayingData::PlayUnit*>::reference>::value, void>::type std::__ndk1::vector<CMenuVoiceManager::PlayingData::PlayUnit, Framework::CSTLAllocator<CMenuVoiceManager::PlayingData::PlayUnit, Framework::CSTLVectorAllocatorInf> >::assign<CMenuVoiceManager::PlayingData::PlayUnit*>(CMenuVoiceManager::PlayingData::PlayUnit*, CMenuVoiceManager::PlayingData::PlayUnit*)
// vaddr 0x1ab1144 | ghidra 0x1bb1144 | size 528 | symbol _ZNSt6__ndk16vectorIN17CMenuVoiceManager11PlayingData8PlayUnitEN9Framework13CSTLAllocatorIS3_NS4_22CSTLVectorAllocatorInfEEEE6assignIPS3_EENS_9enable_ifIXaasr21__is_forward_iteratorIT_EE5valuesr16is_constructibleIS3_NS_15iterator_traitsISC_E9referenceEEE5valueEvE4typeESC_SC_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk16vectorIN17CMenuVoiceManager11PlayingData8PlayUnitEN9Framework13CSTLAllocatorIS3_NS4_22CSTLVectorAllocatorInfEEEE6assignIPS3_EENS_9enable_ifIXaasr21__is_forward_iteratorIT_EE5valuesr16is_constructibleIS3_NS_15iterator_traitsISC_E9referenceEEE5valueEvE4typeESC_SC_
               (long *param_1,undefined8 *param_2,undefined8 *param_3)

{
  undefined8 *puVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  ulong uVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  undefined8 uVar9;
  
  lVar2 = param_1[2];
  lVar5 = *param_1;
  uVar6 = (long)param_3 - (long)param_2 >> 4;
  if ((ulong)(lVar2 - lVar5 >> 4) < uVar6) {
    if (lVar5 != 0) {
      lVar2 = param_1[1];
      if (lVar2 != lVar5) {
        param_1[1] = lVar2 + (~((lVar2 + -0x10) - lVar5) & 0xfffffffffffffff0U);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar5);
      lVar2 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
      *param_1 = 0;
    }
    if ((ulong)(lVar2 >> 4) < 0x7ffffffffffffff) {
      uVar3 = lVar2 >> 3;
      if ((uVar6 <= uVar3) && (uVar6 = uVar3, uVar3 == 0)) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
    }
    else {
      uVar6 = 0xfffffffffffffff;
    }
    puVar1 = (undefined8 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6 << 4,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
    if (puVar1 == (undefined8 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    *param_1 = (long)puVar1;
    param_1[1] = (long)puVar1;
    param_1[2] = (long)(puVar1 + uVar6 * 2);
    for (; param_2 != param_3; param_2 = param_2 + 2) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      uVar9 = *param_2;
      puVar1[1] = param_2[1];
      *puVar1 = uVar9;
      puVar1 = (undefined8 *)(param_1[1] + 0x10);
      param_1[1] = (long)puVar1;
    }
  }
  else {
    uVar3 = param_1[1] - lVar5 >> 4;
    puVar1 = (undefined8 *)((long)param_2 + (param_1[1] - lVar5));
    puVar7 = puVar1;
    if (uVar6 <= uVar3) {
      puVar7 = param_3;
    }
    lVar2 = (long)puVar7 - (long)param_2 >> 4;
    if (lVar2 != 0) {
      memmove(lVar5,param_2);
    }
    if (uVar3 < uVar6) {
      if (puVar7 != param_3) {
        puVar7 = (undefined8 *)param_1[1];
        do {
          if (puVar7 == (undefined8 *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          puVar8 = puVar1 + 2;
          uVar9 = *puVar1;
          puVar7[1] = puVar1[1];
          *puVar7 = uVar9;
          puVar7 = (undefined8 *)(param_1[1] + 0x10);
          param_1[1] = (long)puVar7;
          puVar1 = puVar8;
        } while (param_3 != puVar8);
      }
    }
    else {
      lVar4 = param_1[1];
      lVar5 = lVar5 + lVar2 * 0x10;
      if (lVar4 != lVar5) {
        param_1[1] = lVar4 + (~((lVar4 + -0x10) - lVar5) & 0xfffffffffffffff0U);
      }
    }
  }
  return;
}

// ==== CUIVoiceManager::CUIVoiceManager()
// vaddr 0x1e13224 | ghidra 0x1f13224 | size 40 | symbol _ZN15CUIVoiceManagerC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManagerC1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTV15CUIVoiceManager_02cb84b0 + 0x10);
  memset(param_1 + 1,0,0x48);
  return;
}

// ==== CUIVoiceManager::~CUIVoiceManager()
// vaddr 0x1e1324c | ghidra 0x1f1324c | size 320 | symbol _ZN15CUIVoiceManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x01f13294: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f132fc: Changing call to branch */
/* WARNING: Possible PIC construction at 0x01f13324: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x01f13298) */

void _ZN15CUIVoiceManagerD1Ev(long *param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  lVar3 = param_1[7];
  *param_1 = (long)(PTR__ZTV15CUIVoiceManager_02cb84b0 + 0x10);
  if (lVar3 != 0) {
    lVar4 = param_1[8];
    if (param_1[8] != lVar3) {
      do {
        lVar2 = lVar4 + -0x18;
        param_1[8] = lVar2;
        if ((*(byte *)(lVar4 + -0x18) & 1) != 0) {
          lVar3 = *(long *)(lVar4 + -8);
          goto code_r0x011d23a0;
        }
        lVar4 = lVar2;
      } while (lVar2 != lVar3);
      lVar3 = param_1[7];
    }
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar3);
  }
  lVar3 = param_1[4];
  if (lVar3 == 0) {
    lVar3 = param_1[1];
    if (lVar3 == 0) {
      return;
    }
    lVar4 = param_1[2];
    if (lVar4 != lVar3) {
      do {
        param_1[2] = lVar4 + -0x20;
        lVar2 = lVar4 + -0x20;
        if ((*(byte *)(lVar4 + -0x20) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar4 + -0x10));
          lVar2 = param_1[2];
        }
        lVar4 = lVar2;
      } while (lVar4 != lVar3);
      lVar3 = param_1[1];
    }
  }
  else {
    lVar4 = param_1[5];
    if (lVar4 != lVar3) {
      do {
        param_1[5] = lVar4 + -0x30;
        lVar2 = *(long *)(lVar4 + -0x18);
        if (lVar2 != 0) {
          lVar1 = *(long *)(lVar4 + -0x10);
          lVar3 = lVar2;
          if (lVar1 != lVar2) {
            *(ulong *)(lVar4 + -0x10) = lVar1 + (~((lVar1 + -0x10) - lVar2) & 0xfffffffffffffff0U);
          }
          goto code_r0x011d23a0;
        }
        if ((*(byte *)(lVar4 + -0x30) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar4 + -0x20));
        }
        lVar4 = param_1[5];
      } while (lVar4 != lVar3);
      lVar3 = param_1[4];
    }
  }
code_r0x011d23a0:
  (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)(lVar3);
  return;
}

// ==== CUIVoiceManager::~CUIVoiceManager()
// vaddr 0x1e1338c | ghidra 0x1f1338c | size 24 | symbol _ZN15CUIVoiceManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManagerD0Ev(undefined8 param_1)

{
  CUIVoiceManager::~CUIVoiceManager()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CUIVoiceManager::Initialize()
// vaddr 0x1e133a4 | ghidra 0x1f133a4 | size 4 | symbol _ZN15CUIVoiceManager10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager10InitializeEv(void)

{
  return;
}

// ==== CUIVoiceManager::Progress()
// vaddr 0x1e133a8 | ghidra 0x1f133a8 | size 2080 | symbol _ZN15CUIVoiceManager8ProgressEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager8ProgressEv(long param_1)

{
  byte *pbVar1;
  byte bVar2;
  byte bVar3;
  undefined *puVar4;
  int iVar5;
  ulong uVar6;
  long lVar7;
  undefined8 uVar8;
  byte *pbVar9;
  long lVar10;
  byte *pbVar11;
  ulong uVar12;
  byte *pbVar13;
  undefined8 uVar14;
  undefined8 *puVar15;
  long lVar16;
  byte *pbVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 *puStack_88;
  undefined8 *puStack_80;
  undefined8 *puStack_78;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  long lStack_68;
  
  puVar4 = PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
  CSoundManager::UpdateMapping()(*(undefined8 *)
                   PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358);
  pbVar17 = *(byte **)(param_1 + 8);
  if (*(byte **)(param_1 + 0x10) != pbVar17) {
    uVar14 = *(undefined8 *)puVar4;
    do {
      while( true ) {
        bVar2 = *pbVar17;
        uVar6 = (ulong)(bVar2 >> 1);
        if ((bVar2 & 1) != 0) {
          uVar6 = *(ulong *)(pbVar17 + 8);
        }
        if (uVar6 != 0) break;
code_r0x01f134d0:
        if ((*pbVar17 & 1) == 0) {
          pbVar11 = pbVar17 + 1;
        }
        else {
          pbVar11 = *(byte **)(pbVar17 + 0x10);
        }
        lVar7 = CSoundManager::PlaySe(char const*, unsigned int)(uVar14,pbVar11,*(undefined4 *)(pbVar17 + 0x18));
        pbVar11 = pbVar17;
        if (lVar7 == 0) {
          pbVar13 = *(byte **)(param_1 + 0x10);
          pbVar9 = pbVar17 + 0x20;
          if (pbVar9 != pbVar13) {
            pbVar9 = pbVar17;
            do {
              if ((*pbVar9 & 1) == 0) {
                pbVar9[0] = 0;
                pbVar9[1] = 0;
              }
              else {
                **(undefined1 **)(pbVar9 + 0x10) = 0;
                pbVar9[8] = 0;
                pbVar9[9] = 0;
                pbVar9[10] = 0;
                pbVar9[0xb] = 0;
                pbVar9[0xc] = 0;
                pbVar9[0xd] = 0;
                pbVar9[0xe] = 0;
                pbVar9[0xf] = 0;
              }
              string::reserve(unsigned long)(pbVar9,0);
              uVar8 = *(undefined8 *)(pbVar9 + 0x30);
              uVar19 = *(undefined8 *)(pbVar9 + 0x28);
              uVar18 = *(undefined8 *)(pbVar9 + 0x20);
              pbVar11 = pbVar9 + 0x20;
              pbVar9[0x28] = 0;
              pbVar9[0x29] = 0;
              pbVar9[0x2a] = 0;
              pbVar9[0x2b] = 0;
              pbVar9[0x2c] = 0;
              pbVar9[0x2d] = 0;
              pbVar9[0x2e] = 0;
              pbVar9[0x2f] = 0;
              pbVar9[0x30] = 0;
              pbVar9[0x31] = 0;
              pbVar9[0x32] = 0;
              pbVar9[0x33] = 0;
              pbVar9[0x34] = 0;
              pbVar9[0x35] = 0;
              pbVar9[0x36] = 0;
              pbVar9[0x37] = 0;
              pbVar9[0x20] = 0;
              pbVar9[0x21] = 0;
              pbVar9[0x22] = 0;
              pbVar9[0x23] = 0;
              pbVar9[0x24] = 0;
              pbVar9[0x25] = 0;
              pbVar9[0x26] = 0;
              pbVar9[0x27] = 0;
              *(undefined8 *)(pbVar9 + 0x10) = uVar8;
              *(undefined8 *)(pbVar9 + 8) = uVar19;
              *(undefined8 *)pbVar9 = uVar18;
              *(undefined4 *)(pbVar9 + 0x18) = *(undefined4 *)(pbVar9 + 0x38);
              pbVar9 = pbVar11;
            } while (pbVar13 + -0x20 != pbVar11);
            pbVar9 = *(byte **)(param_1 + 0x10);
            if (pbVar9 == pbVar11) goto code_r0x01f13878;
          }
          do {
            *(byte **)(param_1 + 0x10) = pbVar9 + -0x20;
            pbVar13 = pbVar9 + -0x20;
            if ((pbVar9[-0x20] & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(pbVar9 + -0x10));
              pbVar13 = *(byte **)(param_1 + 0x10);
            }
            pbVar9 = pbVar13;
          } while (pbVar9 != pbVar11);
        }
        else {
          uStack_70 = *(undefined4 *)(pbVar17 + 0x18);
          pbVar9 = *(byte **)(param_1 + 0x20);
          lStack_68 = lVar7;
          if (pbVar9 != *(byte **)(param_1 + 0x28)) {
            bVar2 = *pbVar17;
            uVar6 = (ulong)(bVar2 >> 1);
            if ((bVar2 & 1) != 0) {
              uVar6 = *(ulong *)(pbVar17 + 8);
            }
            do {
              bVar3 = *pbVar9;
              uVar12 = (ulong)(bVar3 >> 1);
              if ((bVar3 & 1) != 0) {
                uVar12 = *(ulong *)(pbVar9 + 8);
              }
              if (uVar12 == uVar6) {
                pbVar13 = *(byte **)(pbVar9 + 0x10);
                if ((bVar3 & 1) == 0) {
                  pbVar13 = pbVar9 + 1;
                }
                pbVar1 = pbVar17 + 1;
                if ((bVar2 & 1) != 0) {
                  pbVar1 = *(byte **)(pbVar17 + 0x10);
                }
                if ((bVar3 & 1) == 0) {
                  if (uVar12 == 0) {
code_r0x01f1367c:
                    puVar15 = *(undefined8 **)(pbVar9 + 0x20);
                    if (puVar15 == *(undefined8 **)(pbVar9 + 0x28)) {
                      void std::__ndk1::vector<CUIVoiceManager::UpVoicePlayingData::PlayUnit, Framework::CSTLAllocator<CUIVoiceManager::UpVoicePlayingData::PlayUnit, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<CUIVoiceManager::UpVoicePlayingData::PlayUnit const&>(CUIVoiceManager::UpVoicePlayingData::PlayUnit const&)(pbVar9 + 0x18,&uStack_70);
                    }
                    else {
                      if (puVar15 == (undefined8 *)0x0) {
                        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
                      }
                      puVar15[1] = lStack_68;
                      *puVar15 = CONCAT44(uStack_6c,uStack_70);
                      *(long *)(pbVar9 + 0x20) = *(long *)(pbVar9 + 0x20) + 0x10;
                    }
                    goto code_r0x01f137fc;
                  }
                  uVar12 = 0;
                  while (pbVar9[uVar12 + 1] == pbVar1[uVar12]) {
                    uVar12 = uVar12 + 1;
                    if (bVar3 >> 1 == uVar12) goto code_r0x01f1367c;
                  }
                }
                else if ((uVar12 == 0) || (iVar5 = memcmp(pbVar13), iVar5 == 0))
                goto code_r0x01f1367c;
              }
              pbVar9 = pbVar9 + 0x30;
            } while (pbVar9 != *(byte **)(param_1 + 0x28));
          }
          puStack_88 = (undefined8 *)0x0;
          uStack_90 = 0;
          puStack_78 = (undefined8 *)0x0;
          puStack_80 = (undefined8 *)0x0;
          uStack_98 = 0;
          uStack_a0 = 0;
          if ((byte *)&uStack_a0 != pbVar17) {
            pbVar9 = pbVar17 + 1;
            uVar6 = (ulong)(*pbVar17 >> 1);
            if ((*pbVar17 & 1) != 0) {
              pbVar9 = *(byte **)(pbVar17 + 0x10);
              uVar6 = *(ulong *)(pbVar17 + 8);
            }
            if (uVar6 < 0x16 || uVar6 - 0x16 == 0) {
              if (uVar6 != 0) {
                memmove((ulong)&uStack_a0 | 1,pbVar9,uVar6);
              }
              *(undefined1 *)((long)&uStack_a0 + uVar6 + 1) = 0;
              uStack_a0 = CONCAT71(uStack_a0._1_7_,(char)(uVar6 << 1));
            }
            else {
              string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_a0,0x16,uVar6 - 0x16,0,0,0,uVar6);
            }
          }
          puVar15 = puStack_88;
          if (puStack_80 != puStack_88) {
            puVar15 = (undefined8 *)
                      ((long)puStack_80 +
                      (~((long)puStack_80 + (-0x10 - (long)puStack_88)) & 0xfffffffffffffff0U));
            puStack_80 = puVar15;
          }
          if (puVar15 == puStack_78) {
            void std::__ndk1::vector<CUIVoiceManager::UpVoicePlayingData::PlayUnit, Framework::CSTLAllocator<CUIVoiceManager::UpVoicePlayingData::PlayUnit, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<CUIVoiceManager::UpVoicePlayingData::PlayUnit const&>(CUIVoiceManager::UpVoicePlayingData::PlayUnit const&)(&puStack_88,&uStack_70);
          }
          else {
            if (puVar15 == (undefined8 *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
            }
            puVar15[1] = lStack_68;
            *puVar15 = CONCAT44(uStack_6c,uStack_70);
            puStack_80 = puStack_80 + 2;
          }
          lVar7 = *(long *)(param_1 + 0x28);
          if (lVar7 == *(long *)(param_1 + 0x30)) {
            void std::__ndk1::vector<CUIVoiceManager::UpVoicePlayingData, Framework::CSTLAllocator<CUIVoiceManager::UpVoicePlayingData, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<CUIVoiceManager::UpVoicePlayingData const&>(CUIVoiceManager::UpVoicePlayingData const&)(param_1 + 0x20,&uStack_a0);
          }
          else {
            if (lVar7 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
            }
            CUIVoiceManager::UpVoicePlayingData::UpVoicePlayingData(CUIVoiceManager::UpVoicePlayingData const&)(lVar7,&uStack_a0);
            *(long *)(param_1 + 0x28) = *(long *)(param_1 + 0x28) + 0x30;
          }
          if (puStack_88 != (undefined8 *)0x0) {
            if (puStack_80 != puStack_88) {
              puStack_80 = (undefined8 *)
                           ((long)puStack_80 +
                           (~((long)puStack_80 + (-0x10 - (long)puStack_88)) & 0xfffffffffffffff0U))
              ;
            }
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
          }
          if ((uStack_a0 & 1) != 0) {
            Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_90);
          }
code_r0x01f137fc:
          pbVar13 = *(byte **)(param_1 + 0x10);
          pbVar9 = pbVar17 + 0x20;
          if (pbVar9 != pbVar13) {
            pbVar9 = pbVar17;
            do {
              if ((*pbVar9 & 1) == 0) {
                pbVar9[0] = 0;
                pbVar9[1] = 0;
              }
              else {
                **(undefined1 **)(pbVar9 + 0x10) = 0;
                pbVar9[8] = 0;
                pbVar9[9] = 0;
                pbVar9[10] = 0;
                pbVar9[0xb] = 0;
                pbVar9[0xc] = 0;
                pbVar9[0xd] = 0;
                pbVar9[0xe] = 0;
                pbVar9[0xf] = 0;
              }
              string::reserve(unsigned long)(pbVar9,0);
              uVar8 = *(undefined8 *)(pbVar9 + 0x30);
              uVar19 = *(undefined8 *)(pbVar9 + 0x28);
              uVar18 = *(undefined8 *)(pbVar9 + 0x20);
              pbVar11 = pbVar9 + 0x20;
              pbVar9[0x28] = 0;
              pbVar9[0x29] = 0;
              pbVar9[0x2a] = 0;
              pbVar9[0x2b] = 0;
              pbVar9[0x2c] = 0;
              pbVar9[0x2d] = 0;
              pbVar9[0x2e] = 0;
              pbVar9[0x2f] = 0;
              pbVar9[0x30] = 0;
              pbVar9[0x31] = 0;
              pbVar9[0x32] = 0;
              pbVar9[0x33] = 0;
              pbVar9[0x34] = 0;
              pbVar9[0x35] = 0;
              pbVar9[0x36] = 0;
              pbVar9[0x37] = 0;
              pbVar9[0x20] = 0;
              pbVar9[0x21] = 0;
              pbVar9[0x22] = 0;
              pbVar9[0x23] = 0;
              pbVar9[0x24] = 0;
              pbVar9[0x25] = 0;
              pbVar9[0x26] = 0;
              pbVar9[0x27] = 0;
              *(undefined8 *)(pbVar9 + 0x10) = uVar8;
              *(undefined8 *)(pbVar9 + 8) = uVar19;
              *(undefined8 *)pbVar9 = uVar18;
              *(undefined4 *)(pbVar9 + 0x18) = *(undefined4 *)(pbVar9 + 0x38);
              pbVar9 = pbVar11;
            } while (pbVar13 + -0x20 != pbVar11);
            pbVar9 = *(byte **)(param_1 + 0x10);
            if (pbVar9 == pbVar11) goto code_r0x01f13878;
          }
          do {
            *(byte **)(param_1 + 0x10) = pbVar9 + -0x20;
            pbVar13 = pbVar9 + -0x20;
            if ((pbVar9[-0x20] & 1) != 0) {
              Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(pbVar9 + -0x10));
              pbVar13 = *(byte **)(param_1 + 0x10);
            }
            pbVar9 = pbVar13;
          } while (pbVar9 != pbVar11);
        }
code_r0x01f13878:
        if (pbVar11 == pbVar17) goto code_r0x01f13880;
      }
      pbVar11 = *(byte **)(pbVar17 + 0x10);
      if ((bVar2 & 1) == 0) {
        pbVar11 = pbVar17 + 1;
      }
      uVar6 = CSoundManager::IsResourceExist(char const*)(*(undefined8 *)puVar4,pbVar11);
      if ((uVar6 & 1) == 0) goto code_r0x01f134d0;
      pbVar11 = pbVar17 + 1;
      if ((*pbVar17 & 1) != 0) {
        pbVar11 = *(byte **)(pbVar17 + 0x10);
      }
      uVar6 = CSoundManager::IsReady(char const*)(*(undefined8 *)puVar4,pbVar11);
      if ((uVar6 & 1) != 0) goto code_r0x01f134d0;
      pbVar17 = pbVar17 + 0x20;
    } while (*(byte **)(param_1 + 0x10) != pbVar17);
  }
code_r0x01f13880:
  pbVar11 = *(byte **)(param_1 + 0x20);
  pbVar17 = *(byte **)(param_1 + 0x28);
  if ((pbVar17 != pbVar11) && (pbVar17 != pbVar11)) {
    uVar14 = *(undefined8 *)puVar4;
code_r0x01f13898:
    do {
      lVar7 = *(long *)(pbVar11 + 0x18);
      lVar10 = *(long *)(pbVar11 + 0x20);
      if (lVar7 != lVar10) {
        do {
          while (uVar6 = CSoundManager::IsPlaying(unsigned long) const(uVar14,*(undefined8 *)(lVar7 + 8)), (uVar6 & 1) == 0) {
            lVar10 = *(long *)(pbVar11 + 0x20);
            lVar16 = lVar10 - (lVar7 + 0x10) >> 4;
            if (lVar16 != 0) {
              memmove(lVar7);
              lVar10 = *(long *)(pbVar11 + 0x20);
            }
            lVar16 = lVar7 + lVar16 * 0x10;
            if (lVar10 != lVar16) {
              lVar10 = lVar10 + (~((lVar10 + -0x10) - lVar16) & 0xfffffffffffffff0U);
              *(long *)(pbVar11 + 0x20) = lVar10;
            }
            if (lVar7 == lVar10) goto code_r0x01f13914;
          }
          lVar10 = *(long *)(pbVar11 + 0x20);
          lVar7 = lVar7 + 0x10;
        } while (lVar7 != lVar10);
code_r0x01f13914:
        lVar7 = *(long *)(pbVar11 + 0x18);
      }
      if (lVar10 != lVar7) {
        pbVar17 = *(byte **)(param_1 + 0x28);
        pbVar11 = pbVar11 + 0x30;
        if (pbVar17 == pbVar11) break;
        goto code_r0x01f13898;
      }
      pbVar13 = *(byte **)(param_1 + 0x28);
      pbVar9 = pbVar11 + 0x30;
      pbVar17 = pbVar11;
      if (pbVar9 == pbVar13) goto code_r0x01f139b0;
      pbVar9 = pbVar11;
      do {
        if ((*pbVar9 & 1) == 0) {
          pbVar9[0] = 0;
          pbVar9[1] = 0;
        }
        else {
          **(undefined1 **)(pbVar9 + 0x10) = 0;
          pbVar9[8] = 0;
          pbVar9[9] = 0;
          pbVar9[10] = 0;
          pbVar9[0xb] = 0;
          pbVar9[0xc] = 0;
          pbVar9[0xd] = 0;
          pbVar9[0xe] = 0;
          pbVar9[0xf] = 0;
        }
        string::reserve(unsigned long)(pbVar9,0);
        uVar19 = *(undefined8 *)(pbVar9 + 0x38);
        uVar18 = *(undefined8 *)(pbVar9 + 0x30);
        uVar8 = *(undefined8 *)(pbVar9 + 0x40);
        pbVar17 = pbVar9 + 0x30;
        pbVar9[0x38] = 0;
        pbVar9[0x39] = 0;
        pbVar9[0x3a] = 0;
        pbVar9[0x3b] = 0;
        pbVar9[0x3c] = 0;
        pbVar9[0x3d] = 0;
        pbVar9[0x3e] = 0;
        pbVar9[0x3f] = 0;
        pbVar9[0x40] = 0;
        pbVar9[0x41] = 0;
        pbVar9[0x42] = 0;
        pbVar9[0x43] = 0;
        pbVar9[0x44] = 0;
        pbVar9[0x45] = 0;
        pbVar9[0x46] = 0;
        pbVar9[0x47] = 0;
        pbVar9[0x30] = 0;
        pbVar9[0x31] = 0;
        pbVar9[0x32] = 0;
        pbVar9[0x33] = 0;
        pbVar9[0x34] = 0;
        pbVar9[0x35] = 0;
        pbVar9[0x36] = 0;
        pbVar9[0x37] = 0;
        *(undefined8 *)(pbVar9 + 0x10) = uVar8;
        *(undefined8 *)(pbVar9 + 8) = uVar19;
        *(undefined8 *)pbVar9 = uVar18;
        std::__ndk1::enable_if<__is_forward_iterator<CUIVoiceManager::UpVoicePlayingData::PlayUnit*>::value&&is_constructible<CUIVoiceManager::UpVoicePlayingData::PlayUnit, std::__ndk1::iterator_traits<CUIVoiceManager::UpVoicePlayingData::PlayUnit*>::reference>::value, void>::type std::__ndk1::vector<CUIVoiceManager::UpVoicePlayingData::PlayUnit, Framework::CSTLAllocator<CUIVoiceManager::UpVoicePlayingData::PlayUnit, Framework::CSTLVectorAllocatorInf> >::assign<CUIVoiceManager::UpVoicePlayingData::PlayUnit*>(CUIVoiceManager::UpVoicePlayingData::PlayUnit*, CUIVoiceManager::UpVoicePlayingData::PlayUnit*)(pbVar9 + 0x18,*(undefined8 *)(pbVar9 + 0x48),*(undefined8 *)(pbVar9 + 0x50))
        ;
        pbVar9 = pbVar17;
      } while (pbVar13 + -0x30 != pbVar17);
      while (pbVar9 = *(byte **)(param_1 + 0x28), pbVar9 != pbVar17) {
code_r0x01f139b0:
        *(byte **)(param_1 + 0x28) = pbVar9 + -0x30;
        lVar7 = *(long *)(pbVar9 + -0x18);
        if (lVar7 != 0) {
          lVar10 = *(long *)(pbVar9 + -0x10);
          if (lVar10 != lVar7) {
            *(ulong *)(pbVar9 + -0x10) =
                 lVar10 + (~((lVar10 + -0x10) - lVar7) & 0xfffffffffffffff0U);
          }
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
        }
        if ((pbVar9[-0x30] & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(pbVar9 + -0x20));
        }
      }
    } while (pbVar17 != pbVar11);
  }
  pbVar11 = *(byte **)(param_1 + 0x38);
  pbVar9 = *(byte **)(param_1 + 0x40);
  if (pbVar9 == pbVar11) {
    return;
  }
  uVar14 = *(undefined8 *)puVar4;
  do {
    pbVar13 = *(byte **)(param_1 + 0x20);
    if (pbVar13 != pbVar17) {
      bVar2 = *pbVar11;
      uVar6 = (ulong)(bVar2 >> 1);
      if ((bVar2 & 1) != 0) {
        uVar6 = *(ulong *)(pbVar11 + 8);
      }
      do {
        bVar3 = *pbVar13;
        uVar12 = (ulong)(bVar3 >> 1);
        if ((bVar3 & 1) != 0) {
          uVar12 = *(ulong *)(pbVar13 + 8);
        }
        if (uVar12 == uVar6) {
          if ((bVar3 & 1) == 0) {
            if (uVar12 != 0) {
              uVar12 = 0;
              pbVar1 = pbVar11 + 1;
              if ((bVar2 & 1) != 0) {
                pbVar1 = *(byte **)(pbVar11 + 0x10);
              }
              while (pbVar13[uVar12 + 1] == pbVar1[uVar12]) {
                uVar12 = uVar12 + 1;
                if (bVar3 >> 1 == uVar12) goto code_r0x01f13ae0;
              }
              goto code_r0x01f13ac4;
            }
          }
          else if (uVar12 != 0) {
            pbVar1 = pbVar11 + 1;
            if ((bVar2 & 1) != 0) {
              pbVar1 = *(byte **)(pbVar11 + 0x10);
            }
            iVar5 = memcmp(*(undefined8 *)(pbVar13 + 0x10),pbVar1,uVar6);
            if (iVar5 != 0) goto code_r0x01f13ac4;
          }
code_r0x01f13ae0:
          pbVar11 = pbVar11 + 0x18;
          if (pbVar9 == pbVar11) {
            return;
          }
          goto code_r0x01f13a24;
        }
code_r0x01f13ac4:
        pbVar13 = pbVar13 + 0x30;
      } while (pbVar13 != pbVar17);
    }
    if ((*pbVar11 & 1) == 0) {
      pbVar17 = pbVar11 + 1;
    }
    else {
      pbVar17 = *(byte **)(pbVar11 + 0x10);
    }
    CSoundManager::RemoveResource(char const*)(uVar14,pbVar17);
    pbVar13 = *(byte **)(param_1 + 0x40);
    pbVar17 = pbVar11 + 0x18;
    pbVar9 = pbVar11;
    if (pbVar17 == pbVar13) {
code_r0x01f13b7c:
      do {
        *(byte **)(param_1 + 0x40) = pbVar17 + -0x18;
        pbVar13 = pbVar17 + -0x18;
        if ((pbVar17[-0x18] & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(pbVar17 + -8));
          pbVar13 = *(byte **)(param_1 + 0x40);
        }
        pbVar17 = pbVar13;
      } while (pbVar17 != pbVar9);
    }
    else {
      pbVar17 = pbVar11;
      do {
        if ((*pbVar17 & 1) == 0) {
          pbVar17[0] = 0;
          pbVar17[1] = 0;
        }
        else {
          **(undefined1 **)(pbVar17 + 0x10) = 0;
          pbVar17[8] = 0;
          pbVar17[9] = 0;
          pbVar17[10] = 0;
          pbVar17[0xb] = 0;
          pbVar17[0xc] = 0;
          pbVar17[0xd] = 0;
          pbVar17[0xe] = 0;
          pbVar17[0xf] = 0;
        }
        string::reserve(unsigned long)(pbVar17,0);
        uVar8 = *(undefined8 *)(pbVar17 + 0x28);
        uVar19 = *(undefined8 *)(pbVar17 + 0x20);
        uVar18 = *(undefined8 *)(pbVar17 + 0x18);
        pbVar9 = pbVar17 + 0x18;
        pbVar17[0x20] = 0;
        pbVar17[0x21] = 0;
        pbVar17[0x22] = 0;
        pbVar17[0x23] = 0;
        pbVar17[0x24] = 0;
        pbVar17[0x25] = 0;
        pbVar17[0x26] = 0;
        pbVar17[0x27] = 0;
        pbVar17[0x28] = 0;
        pbVar17[0x29] = 0;
        pbVar17[0x2a] = 0;
        pbVar17[0x2b] = 0;
        pbVar17[0x2c] = 0;
        pbVar17[0x2d] = 0;
        pbVar17[0x2e] = 0;
        pbVar17[0x2f] = 0;
        *(undefined8 *)(pbVar17 + 0x10) = uVar8;
        pbVar17[0x18] = 0;
        pbVar17[0x19] = 0;
        pbVar17[0x1a] = 0;
        pbVar17[0x1b] = 0;
        pbVar17[0x1c] = 0;
        pbVar17[0x1d] = 0;
        pbVar17[0x1e] = 0;
        pbVar17[0x1f] = 0;
        *(undefined8 *)(pbVar17 + 8) = uVar19;
        *(undefined8 *)pbVar17 = uVar18;
        pbVar17 = pbVar9;
      } while (pbVar13 + -0x18 != pbVar9);
      pbVar17 = *(byte **)(param_1 + 0x40);
      if (pbVar17 != pbVar9) goto code_r0x01f13b7c;
    }
    if (pbVar9 == pbVar11) {
      return;
    }
code_r0x01f13a24:
    pbVar17 = *(byte **)(param_1 + 0x28);
  } while( true );
}

// ==== CUIVoiceManager::IsReadyResourcePack(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1e13bc8 | ghidra 0x1f13bc8 | size 120 | symbol _ZN15CUIVoiceManager19IsReadyResourcePackERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN15CUIVoiceManager19IsReadyResourcePackERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE
          (undefined8 param_1,byte *param_2)

{
  byte bVar1;
  undefined *puVar2;
  undefined8 uVar3;
  ulong uVar4;
  byte *pbVar5;
  
  puVar2 = PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
  bVar1 = *param_2;
  uVar4 = (ulong)(bVar1 >> 1);
  if ((bVar1 & 1) != 0) {
    uVar4 = *(ulong *)(param_2 + 8);
  }
  if (uVar4 != 0) {
    pbVar5 = *(byte **)(param_2 + 0x10);
    if ((bVar1 & 1) == 0) {
      pbVar5 = param_2 + 1;
    }
    uVar4 = CSoundManager::IsResourceExist(char const*)(*(undefined8 *)
                             PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358,
                            pbVar5);
    if ((uVar4 & 1) != 0) {
      pbVar5 = param_2 + 1;
      if ((*param_2 & 1) != 0) {
        pbVar5 = *(byte **)(param_2 + 0x10);
      }
      uVar3 = (*(code *)PTR__ZN13CSoundManager7IsReadyEPKc_02c95838)(*(undefined8 *)puVar2,pbVar5);
      return uVar3;
    }
  }
  return 1;
}

// ==== CUIVoiceManager::PlayVoiceFromMenuID(CUIVoiceManager::MenuID, CUIVoiceManager::MenuVoiceCharacterType, bool, int)
// vaddr 0x1e13c40 | ghidra 0x1f13c40 | size 136 | symbol _ZN15CUIVoiceManager19PlayVoiceFromMenuIDENS_6MenuIDENS_22MenuVoiceCharacterTypeEbi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager19PlayVoiceFromMenuIDENS_6MenuIDENS_22MenuVoiceCharacterTypeEbi
               (undefined8 param_1,int param_2,undefined4 param_3,uint param_4,undefined4 param_5)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (0x11 < param_2 - 1U) {
    return;
  }
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  uVar3 = CUIManager::rMenuVoiceManager()(lVar2);
  (*(code *)PTR__ZN17CMenuVoiceManager19PlayVoiceFromMenuIDEjjbi_02cb3840)
            (uVar3,param_2,param_3,param_4 & 1,param_5);
  return;
}

// ==== CUIVoiceManager::PlayVoice(char const*, bool, int)
// vaddr 0x1e13cc8 | ghidra 0x1f13cc8 | size 120 | symbol _ZN15CUIVoiceManager9PlayVoiceEPKcbi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager9PlayVoiceEPKcbi
               (undefined8 param_1,long param_2,uint param_3,undefined4 param_4)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (param_2 != 0) {
    lVar2 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar2 = *(long *)puVar1;
    }
    uVar3 = CUIManager::rMenuVoiceManager()(lVar2);
    (*(code *)PTR__ZN17CMenuVoiceManager15PlayVoiceFromIDEPKcbi_02ca10f0)
              (uVar3,param_2,param_3 & 1,param_4);
    return;
  }
  return;
}

// ==== CUIVoiceManager::PlayVoiceFromMasterID(unsigned int, bool, int)
// vaddr 0x1e13d40 | ghidra 0x1f13d40 | size 120 | symbol _ZN15CUIVoiceManager21PlayVoiceFromMasterIDEjbi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager21PlayVoiceFromMasterIDEjbi
               (undefined8 param_1,int param_2,uint param_3,undefined4 param_4)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (param_2 != 0) {
    lVar2 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar2 = *(long *)puVar1;
    }
    uVar3 = CUIManager::rMenuVoiceManager()(lVar2);
    (*(code *)PTR__ZN17CMenuVoiceManager21PlayVoiceFromMasterIDEjbi_02c8f990)
              (uVar3,param_2,param_3 & 1,param_4);
    return;
  }
  return;
}

// ==== CUIVoiceManager::CreateRandomQueID(unsigned int, unsigned int)
// vaddr 0x1e13db8 | ghidra 0x1f13db8 | size 80 | symbol _ZN15CUIVoiceManager17CreateRandomQueIDEjj | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN15CUIVoiceManager17CreateRandomQueIDEjj(undefined8 param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = Aska::Random(int, int)(param_2,param_3 + 1);
  if (param_3 < uVar1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029588d8/*"C:\BAS_Submission\Client\Project\..\Source\Game\UI\UIVoiceManager.cpp"*/,0x107,&UNK_0295891e/*"over range"*/);
  }
  return uVar1;
}

// ==== CUIVoiceManager::IsSystemSettingMenuVoiceEnable(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1e13e08 | ghidra 0x1f13e08 | size 544 | symbol _ZN15CUIVoiceManager30IsSystemSettingMenuVoiceEnableERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN15CUIVoiceManager30IsSystemSettingMenuVoiceEnableERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE
               (undefined8 param_1,byte *param_2)

{
  ulong uVar1;
  char *pcVar2;
  byte *pbVar3;
  bool bVar4;
  ulong uVar5;
  bool bVar6;
  int iVar7;
  ulong uVar8;
  char *pcVar9;
  long lVar10;
  char *pcVar11;
  byte abStack_50 [8];
  ulong uStack_48;
  char *pcStack_40;
  ulong uStack_38;
  ulong uStack_30;
  char *pcStack_28;
  
  uStack_30 = 0;
  pcStack_28 = (char *)0x0;
  uStack_38 = 0;
  uVar8 = *(ulong *)(param_2 + 8);
  pbVar3 = *(byte **)(param_2 + 0x10);
  if ((*param_2 & 1) == 0) {
    pbVar3 = param_2 + 1;
    uVar8 = (ulong)(*param_2 >> 1);
  }
  if (5 < uVar8) {
    uVar8 = 6;
  }
  if (uVar8 < 0x17) {
    pcVar11 = (char *)((ulong)&uStack_38 | 1);
    uStack_38 = (uVar8 & 0x7f) << 1;
    if (uVar8 != 0) goto code_r0x01f13ea0;
  }
  else {
    pcVar11 = (char *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x10,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (pcVar11 == (char *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_38 = 0x11;
    uStack_30 = uVar8;
    pcStack_28 = pcVar11;
code_r0x01f13ea0:
    memcpy(pcVar11,pbVar3,uVar8);
  }
  uVar5 = uStack_38;
  pcVar11[uVar8] = '\0';
  uVar8 = uStack_38 >> 1 & 0x7f;
  if ((uStack_38 & 1) != 0) {
    uVar8 = uStack_30;
  }
  if (uVar8 == 6) {
    pcVar11 = (char *)((ulong)&uStack_38 | 1);
    if ((uStack_38 & 1) != 0) {
      pcVar11 = pcStack_28;
    }
    iVar7 = memcmp(pcVar11,&UNK_0294e17d/*"cp0002"*/,6);
    if (iVar7 == 0) {
      uVar8 = CUIUtility::IsMenuVoiceEveleashEnable()();
      goto code_r0x01f14020;
    }
    pcVar11 = (char *)((ulong)&uStack_38 | 1);
    if ((uVar5 & 1) != 0) {
      pcVar11 = pcStack_28;
    }
    iVar7 = memcmp(pcVar11,&UNK_028b06f4/*"cp0003"*/,6);
    if (iVar7 != 0) goto code_r0x01f13f18;
code_r0x01f13f9c:
    uVar8 = CUIUtility::IsMenuVoiceCoroEnable()();
  }
  else {
code_r0x01f13f18:
    CUIUtility::GetMascot()(abStack_50);
    uVar1 = (ulong)(abStack_50[0] >> 1);
    if ((abStack_50[0] & 1) != 0) {
      uVar1 = uStack_48;
    }
    if (uVar1 == uVar8) {
      pcVar11 = (char *)((ulong)abStack_50 | 1);
      pcVar2 = pcVar11;
      if ((abStack_50[0] & 1) != 0) {
        pcVar2 = pcStack_40;
      }
      pcVar9 = (char *)((ulong)&uStack_38 | 1);
      if ((uVar5 & 1) != 0) {
        pcVar9 = pcStack_28;
      }
      if ((abStack_50[0] & 1) == 0) {
        if (uVar8 == 0) goto code_r0x01f13f9c;
        lVar10 = -(ulong)(abStack_50[0] >> 1);
        do {
          if (*pcVar11 != *pcVar9) goto code_r0x01f13fb0;
          pcVar11 = pcVar11 + 1;
          lVar10 = lVar10 + 1;
          pcVar9 = pcVar9 + 1;
        } while (lVar10 != 0);
        bVar6 = true;
        bVar4 = bVar6;
        if ((abStack_50[0] & 1) == 0) goto code_r0x01f13f98;
      }
      else {
        if (uVar8 == 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pcStack_40);
          uVar8 = CUIUtility::IsMenuVoiceCoroEnable()();
          goto code_r0x01f14020;
        }
        iVar7 = memcmp(pcVar2,pcVar9,uVar8);
        bVar6 = iVar7 == 0;
      }
code_r0x01f13fdc:
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pcStack_40);
      if (bVar6) goto code_r0x01f13f9c;
    }
    else {
code_r0x01f13fb0:
      bVar4 = false;
      bVar6 = false;
      if ((abStack_50[0] & 1) != 0) goto code_r0x01f13fdc;
code_r0x01f13f98:
      if (bVar4) goto code_r0x01f13f9c;
    }
    uVar8 = CUIUtility::IsMenuVoiceOtherEnable()();
  }
code_r0x01f14020:
  if ((uVar5 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pcStack_28);
  }
  return (uVar8 & 1) != 0;
}

// ==== CUIVoiceManager::IsPlaying(char const*)
// vaddr 0x1e14028 | ghidra 0x1f14028 | size 76 | symbol _ZN15CUIVoiceManager9IsPlayingEPKc | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager9IsPlayingEPKc(undefined8 param_1,undefined8 param_2)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  uVar3 = CUIManager::rMenuVoiceManager()(lVar2);
  (*(code *)PTR__ZNK17CMenuVoiceManager9IsPlayingEPKc_02ca30c8)(uVar3,param_2);
  return;
}

// ==== CUIVoiceManager::StopAll(bool, float)
// vaddr 0x1e14074 | ghidra 0x1f14074 | size 92 | symbol _ZN15CUIVoiceManager7StopAllEbf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager7StopAllEbf(undefined8 param_1,undefined8 param_2,uint param_3)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  uVar3 = CUIManager::rMenuVoiceManager()(lVar2);
  (*(code *)PTR__ZN17CMenuVoiceManager7StopAllEbf_02ca35c0)(param_1,uVar3,param_3 & 1);
  return;
}

// ==== CUIVoiceManager::GetMenuVoicePackName(unsigned int)
// vaddr 0x1e140d0 | ghidra 0x1f140d0 | size 1052 | symbol _ZN15CUIVoiceManager20GetMenuVoicePackNameEj | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Removing unreachable block (ram,0x01f14424) */
/* WARNING: Removing unreachable block (ram,0x01f1442c) */
/* WARNING: Type propagation algorithm not settling */

void _ZN15CUIVoiceManager20GetMenuVoicePackNameEj
               (ulong *param_1,undefined8 param_2,undefined4 param_3)

{
  ulong *puVar1;
  bool bVar2;
  undefined *puVar3;
  int iVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  undefined8 uVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uStack_1b8;
  undefined8 uStack_1b0;
  ulong uStack_1a8;
  ulong uStack_1a0;
  ulong uStack_198;
  ulong uStack_190;
  long lStack_188;
  long lStack_180;
  long lStack_178;
  long lStack_170;
  undefined *puStack_168;
  undefined8 uStack_160;
  ulong *puStack_158;
  undefined8 uStack_150;
  undefined4 uStack_148;
  undefined1 uStack_144;
  ulong uStack_140;
  ulong uStack_138;
  ulong uStack_130;
  
  CParameterUtility::FindPersonWithId(unsigned int)(&lStack_178,param_3);
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  if (lStack_178 == 0) goto code_r0x01f14490;
  iVar4 = CUIUtility::GetPersonVoiceSwitchID(unsigned int)(*(undefined4 *)(lStack_178 + 0x38));
  puVar3 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (iVar4 != 0) {
    lVar7 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar7 = *(long *)puVar3;
    }
    uVar8 = *(undefined8 *)(*(long *)(lVar7 + 0x5f8) + 0x418);
    snprintf(&uStack_140,0x100,&UNK_027e6d32/*"%u"*/,iVar4);
    puStack_168 = &UNK_027ffe64/*"id"*/;
    uStack_160 = 2;
    puStack_158 = &uStack_140;
    uStack_150 = strlen(&uStack_140);
    uStack_148 = 0;
    uStack_144 = 0;
    CMasterParameterBaseSqlite_Simple<CMasterParameterVoiceSwitchElement>::ParameterByQuery(char const*, Aska::Yayoi::QueryParam*, unsigned int) const(&lStack_188,uVar8,&UNK_027ffd77/*"SELECT * FROM master_voice_switch WHERE id=?"*/,&puStack_168,1);
    if (lStack_188 == 0) {
code_r0x01f1440c:
      bVar2 = false;
    }
    else {
      uStack_160 = 0;
      puStack_158 = (ulong *)0x0;
      puStack_168 = (undefined *)0x0;
      void CParameterPropertyBase<54u>::CryptString<string >(string&, string const&)(&puStack_168,lStack_188 + 0x328);
      uStack_138 = 0;
      uStack_130 = 0;
      puVar1 = (ulong *)((ulong)&puStack_168 | 1);
      if (((ulong)puStack_168 & 1) != 0) {
        puVar1 = puStack_158;
      }
      uStack_140 = 0;
      uVar5 = strlen(puVar1);
      if (uVar5 < 0x17) {
        uVar9 = (ulong)&uStack_140 | 1;
        uStack_140 = CONCAT71(uStack_140._1_7_,(char)(uVar5 << 1));
        if (uVar5 != 0) goto code_r0x01f14274;
      }
      else {
        uVar6 = uVar5 + 0x10 & 0xfffffffffffffff0;
        if (uVar6 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar9 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (uVar9 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        uStack_140 = uVar6 | 1;
        uStack_138 = uVar5;
        uStack_130 = uVar9;
code_r0x01f14274:
        memcpy(uVar9,puVar1,uVar5);
      }
      *(undefined1 *)(uVar9 + uVar5) = 0;
      uStack_1b8 = 0;
      uStack_1b0 = 0;
      uStack_1a8 = 0;
      void CParameterPropertyBase<55u>::CryptString<string >(string&, string const&)(&uStack_1b8,lStack_188 + 0x368);
      uStack_198 = 0;
      uStack_190 = 0;
      uVar5 = (ulong)&uStack_1b8 | 1;
      if ((uStack_1b8 & 1) != 0) {
        uVar5 = uStack_1a8;
      }
      uStack_1a0 = 0;
      uVar6 = strlen(uVar5);
      if (uVar6 < 0x17) {
        uVar10 = (ulong)&uStack_1a0 | 1;
        uStack_1a0 = CONCAT71(uStack_1a0._1_7_,(char)(uVar6 << 1));
        if (uVar6 != 0) goto code_r0x01f14350;
      }
      else {
        uVar9 = uVar6 + 0x10 & 0xfffffffffffffff0;
        if (uVar9 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (uVar10 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        uStack_1a0 = uVar9 | 1;
        uStack_198 = uVar6;
        uStack_190 = uVar10;
code_r0x01f14350:
        memcpy(uVar10,uVar5,uVar6);
      }
      *(undefined1 *)(uVar10 + uVar6) = 0;
      uVar5 = CUIUtility::IsWithinDayEnableEmpty(string const&, string const&)(&uStack_140,&uStack_1a0);
      if ((uStack_1a0 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_190);
      }
      if ((uStack_1b8 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1a8);
      }
      if ((uStack_140 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_130);
      }
      if (((ulong)puStack_168 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_158);
      }
      if ((uVar5 & 1) == 0) {
        CUIUtility::SetPersonVoiceSwitchID(unsigned int, unsigned int)(*(undefined4 *)(lStack_178 + 0x38),0);
        goto code_r0x01f1440c;
      }
      uStack_140 = 0;
      uStack_138 = 0;
      uStack_130 = 0;
      void CParameterPropertyBase<48u>::CryptString<string >(string&, string const&)(&uStack_140,lStack_188 + 0x1b8);
      if ((*param_1 & 1) == 0) {
        *(undefined2 *)param_1 = 0;
      }
      else {
        *(undefined1 *)param_1[2] = 0;
        param_1[1] = 0;
      }
      string::reserve(unsigned long)(param_1,0);
      bVar2 = true;
      param_1[2] = uStack_130;
      param_1[1] = uStack_138;
      *param_1 = uStack_140;
    }
    if (lStack_180 != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
    if (bVar2) goto code_r0x01f14490;
  }
  uStack_140 = 0;
  uStack_138 = 0;
  uStack_130 = 0;
  void CParameterPropertyBase<90u>::CryptString<string >(string&, string const&)(&uStack_140,lStack_178 + 0x338);
  if ((*param_1 & 1) == 0) {
    *(undefined2 *)param_1 = 0;
  }
  else {
    *(undefined1 *)param_1[2] = 0;
    param_1[1] = 0;
  }
  string::reserve(unsigned long)(param_1,0);
  param_1[2] = uStack_130;
  param_1[1] = uStack_138;
  *param_1 = uStack_140;
code_r0x01f14490:
  if (lStack_170 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return;
}

// ==== CUIVoiceManager::GetBattleVoicePackName(unsigned int)
// vaddr 0x1e144ec | ghidra 0x1f144ec | size 1052 | symbol _ZN15CUIVoiceManager22GetBattleVoicePackNameEj | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Removing unreachable block (ram,0x01f14840) */
/* WARNING: Removing unreachable block (ram,0x01f14848) */
/* WARNING: Type propagation algorithm not settling */

void _ZN15CUIVoiceManager22GetBattleVoicePackNameEj
               (ulong *param_1,undefined8 param_2,undefined4 param_3)

{
  ulong *puVar1;
  bool bVar2;
  undefined *puVar3;
  int iVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  undefined8 uVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uStack_1b8;
  undefined8 uStack_1b0;
  ulong uStack_1a8;
  ulong uStack_1a0;
  ulong uStack_198;
  ulong uStack_190;
  long lStack_188;
  long lStack_180;
  long lStack_178;
  long lStack_170;
  undefined *puStack_168;
  undefined8 uStack_160;
  ulong *puStack_158;
  undefined8 uStack_150;
  undefined4 uStack_148;
  undefined1 uStack_144;
  ulong uStack_140;
  ulong uStack_138;
  ulong uStack_130;
  
  CParameterUtility::FindPersonWithId(unsigned int)(&lStack_178,param_3);
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  if (lStack_178 == 0) goto code_r0x01f148ac;
  iVar4 = CUIUtility::GetPersonVoiceSwitchID(unsigned int)(*(undefined4 *)(lStack_178 + 0x38));
  puVar3 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (iVar4 != 0) {
    lVar7 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar7 = *(long *)puVar3;
    }
    uVar8 = *(undefined8 *)(*(long *)(lVar7 + 0x5f8) + 0x418);
    snprintf(&uStack_140,0x100,&UNK_027e6d32/*"%u"*/,iVar4);
    puStack_168 = &UNK_027ffe64/*"id"*/;
    uStack_160 = 2;
    puStack_158 = &uStack_140;
    uStack_150 = strlen(&uStack_140);
    uStack_148 = 0;
    uStack_144 = 0;
    CMasterParameterBaseSqlite_Simple<CMasterParameterVoiceSwitchElement>::ParameterByQuery(char const*, Aska::Yayoi::QueryParam*, unsigned int) const(&lStack_188,uVar8,&UNK_027ffd77/*"SELECT * FROM master_voice_switch WHERE id=?"*/,&puStack_168,1);
    if (lStack_188 == 0) {
code_r0x01f14828:
      bVar2 = false;
    }
    else {
      uStack_160 = 0;
      puStack_158 = (ulong *)0x0;
      puStack_168 = (undefined *)0x0;
      void CParameterPropertyBase<54u>::CryptString<string >(string&, string const&)(&puStack_168,lStack_188 + 0x328);
      uStack_138 = 0;
      uStack_130 = 0;
      puVar1 = (ulong *)((ulong)&puStack_168 | 1);
      if (((ulong)puStack_168 & 1) != 0) {
        puVar1 = puStack_158;
      }
      uStack_140 = 0;
      uVar5 = strlen(puVar1);
      if (uVar5 < 0x17) {
        uVar9 = (ulong)&uStack_140 | 1;
        uStack_140 = CONCAT71(uStack_140._1_7_,(char)(uVar5 << 1));
        if (uVar5 != 0) goto code_r0x01f14690;
      }
      else {
        uVar6 = uVar5 + 0x10 & 0xfffffffffffffff0;
        if (uVar6 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar9 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (uVar9 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        uStack_140 = uVar6 | 1;
        uStack_138 = uVar5;
        uStack_130 = uVar9;
code_r0x01f14690:
        memcpy(uVar9,puVar1,uVar5);
      }
      *(undefined1 *)(uVar9 + uVar5) = 0;
      uStack_1b8 = 0;
      uStack_1b0 = 0;
      uStack_1a8 = 0;
      void CParameterPropertyBase<55u>::CryptString<string >(string&, string const&)(&uStack_1b8,lStack_188 + 0x368);
      uStack_198 = 0;
      uStack_190 = 0;
      uVar5 = (ulong)&uStack_1b8 | 1;
      if ((uStack_1b8 & 1) != 0) {
        uVar5 = uStack_1a8;
      }
      uStack_1a0 = 0;
      uVar6 = strlen(uVar5);
      if (uVar6 < 0x17) {
        uVar10 = (ulong)&uStack_1a0 | 1;
        uStack_1a0 = CONCAT71(uStack_1a0._1_7_,(char)(uVar6 << 1));
        if (uVar6 != 0) goto code_r0x01f1476c;
      }
      else {
        uVar9 = uVar6 + 0x10 & 0xfffffffffffffff0;
        if (uVar9 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (uVar10 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        uStack_1a0 = uVar9 | 1;
        uStack_198 = uVar6;
        uStack_190 = uVar10;
code_r0x01f1476c:
        memcpy(uVar10,uVar5,uVar6);
      }
      *(undefined1 *)(uVar10 + uVar6) = 0;
      uVar5 = CUIUtility::IsWithinDayEnableEmpty(string const&, string const&)(&uStack_140,&uStack_1a0);
      if ((uStack_1a0 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_190);
      }
      if ((uStack_1b8 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1a8);
      }
      if ((uStack_140 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_130);
      }
      if (((ulong)puStack_168 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_158);
      }
      if ((uVar5 & 1) == 0) {
        CUIUtility::SetPersonVoiceSwitchID(unsigned int, unsigned int)(*(undefined4 *)(lStack_178 + 0x38),0);
        goto code_r0x01f14828;
      }
      uStack_140 = 0;
      uStack_138 = 0;
      uStack_130 = 0;
      void CParameterPropertyBase<46u>::CryptString<string >(string&, string const&)(&uStack_140,lStack_188 + 0x148);
      if ((*param_1 & 1) == 0) {
        *(undefined2 *)param_1 = 0;
      }
      else {
        *(undefined1 *)param_1[2] = 0;
        param_1[1] = 0;
      }
      string::reserve(unsigned long)(param_1,0);
      bVar2 = true;
      param_1[2] = uStack_130;
      param_1[1] = uStack_138;
      *param_1 = uStack_140;
    }
    if (lStack_180 != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
    if (bVar2) goto code_r0x01f148ac;
  }
  uStack_140 = 0;
  uStack_138 = 0;
  uStack_130 = 0;
  void CParameterPropertyBase<88u>::CryptString<string >(string&, string const&)(&uStack_140,lStack_178 + 0x2c8);
  if ((*param_1 & 1) == 0) {
    *(undefined2 *)param_1 = 0;
  }
  else {
    *(undefined1 *)param_1[2] = 0;
    param_1[1] = 0;
  }
  string::reserve(unsigned long)(param_1,0);
  param_1[2] = uStack_130;
  param_1[1] = uStack_138;
  *param_1 = uStack_140;
code_r0x01f148ac:
  if (lStack_170 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return;
}

// ==== CUIVoiceManager::GetHomeVoicePackName(unsigned int)
// vaddr 0x1e14908 | ghidra 0x1f14908 | size 1052 | symbol _ZN15CUIVoiceManager20GetHomeVoicePackNameEj | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Removing unreachable block (ram,0x01f14c5c) */
/* WARNING: Removing unreachable block (ram,0x01f14c64) */
/* WARNING: Type propagation algorithm not settling */

void _ZN15CUIVoiceManager20GetHomeVoicePackNameEj
               (ulong *param_1,undefined8 param_2,undefined4 param_3)

{
  ulong *puVar1;
  bool bVar2;
  undefined *puVar3;
  int iVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  undefined8 uVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uStack_1b8;
  undefined8 uStack_1b0;
  ulong uStack_1a8;
  ulong uStack_1a0;
  ulong uStack_198;
  ulong uStack_190;
  long lStack_188;
  long lStack_180;
  long lStack_178;
  long lStack_170;
  undefined *puStack_168;
  undefined8 uStack_160;
  ulong *puStack_158;
  undefined8 uStack_150;
  undefined4 uStack_148;
  undefined1 uStack_144;
  ulong uStack_140;
  ulong uStack_138;
  ulong uStack_130;
  
  CParameterUtility::FindPersonWithId(unsigned int)(&lStack_178,param_3);
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  if (lStack_178 == 0) goto code_r0x01f14cc8;
  iVar4 = CUIUtility::GetPersonVoiceSwitchID(unsigned int)(*(undefined4 *)(lStack_178 + 0x38));
  puVar3 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (iVar4 != 0) {
    lVar7 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar7 = *(long *)puVar3;
    }
    uVar8 = *(undefined8 *)(*(long *)(lVar7 + 0x5f8) + 0x418);
    snprintf(&uStack_140,0x100,&UNK_027e6d32/*"%u"*/,iVar4);
    puStack_168 = &UNK_027ffe64/*"id"*/;
    uStack_160 = 2;
    puStack_158 = &uStack_140;
    uStack_150 = strlen(&uStack_140);
    uStack_148 = 0;
    uStack_144 = 0;
    CMasterParameterBaseSqlite_Simple<CMasterParameterVoiceSwitchElement>::ParameterByQuery(char const*, Aska::Yayoi::QueryParam*, unsigned int) const(&lStack_188,uVar8,&UNK_027ffd77/*"SELECT * FROM master_voice_switch WHERE id=?"*/,&puStack_168,1);
    if (lStack_188 == 0) {
code_r0x01f14c44:
      bVar2 = false;
    }
    else {
      uStack_160 = 0;
      puStack_158 = (ulong *)0x0;
      puStack_168 = (undefined *)0x0;
      void CParameterPropertyBase<54u>::CryptString<string >(string&, string const&)(&puStack_168,lStack_188 + 0x328);
      uStack_138 = 0;
      uStack_130 = 0;
      puVar1 = (ulong *)((ulong)&puStack_168 | 1);
      if (((ulong)puStack_168 & 1) != 0) {
        puVar1 = puStack_158;
      }
      uStack_140 = 0;
      uVar5 = strlen(puVar1);
      if (uVar5 < 0x17) {
        uVar9 = (ulong)&uStack_140 | 1;
        uStack_140 = CONCAT71(uStack_140._1_7_,(char)(uVar5 << 1));
        if (uVar5 != 0) goto code_r0x01f14aac;
      }
      else {
        uVar6 = uVar5 + 0x10 & 0xfffffffffffffff0;
        if (uVar6 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar9 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (uVar9 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        uStack_140 = uVar6 | 1;
        uStack_138 = uVar5;
        uStack_130 = uVar9;
code_r0x01f14aac:
        memcpy(uVar9,puVar1,uVar5);
      }
      *(undefined1 *)(uVar9 + uVar5) = 0;
      uStack_1b8 = 0;
      uStack_1b0 = 0;
      uStack_1a8 = 0;
      void CParameterPropertyBase<55u>::CryptString<string >(string&, string const&)(&uStack_1b8,lStack_188 + 0x368);
      uStack_198 = 0;
      uStack_190 = 0;
      uVar5 = (ulong)&uStack_1b8 | 1;
      if ((uStack_1b8 & 1) != 0) {
        uVar5 = uStack_1a8;
      }
      uStack_1a0 = 0;
      uVar6 = strlen(uVar5);
      if (uVar6 < 0x17) {
        uVar10 = (ulong)&uStack_1a0 | 1;
        uStack_1a0 = CONCAT71(uStack_1a0._1_7_,(char)(uVar6 << 1));
        if (uVar6 != 0) goto code_r0x01f14b88;
      }
      else {
        uVar9 = uVar6 + 0x10 & 0xfffffffffffffff0;
        if (uVar9 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (uVar10 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        uStack_1a0 = uVar9 | 1;
        uStack_198 = uVar6;
        uStack_190 = uVar10;
code_r0x01f14b88:
        memcpy(uVar10,uVar5,uVar6);
      }
      *(undefined1 *)(uVar10 + uVar6) = 0;
      uVar5 = CUIUtility::IsWithinDayEnableEmpty(string const&, string const&)(&uStack_140,&uStack_1a0);
      if ((uStack_1a0 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_190);
      }
      if ((uStack_1b8 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1a8);
      }
      if ((uStack_140 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_130);
      }
      if (((ulong)puStack_168 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_158);
      }
      if ((uVar5 & 1) == 0) {
        CUIUtility::SetPersonVoiceSwitchID(unsigned int, unsigned int)(*(undefined4 *)(lStack_178 + 0x38),0);
        goto code_r0x01f14c44;
      }
      uStack_140 = 0;
      uStack_138 = 0;
      uStack_130 = 0;
      void CParameterPropertyBase<49u>::CryptString<string >(string&, string const&)(&uStack_140,lStack_188 + 0x1f8);
      if ((*param_1 & 1) == 0) {
        *(undefined2 *)param_1 = 0;
      }
      else {
        *(undefined1 *)param_1[2] = 0;
        param_1[1] = 0;
      }
      string::reserve(unsigned long)(param_1,0);
      bVar2 = true;
      param_1[2] = uStack_130;
      param_1[1] = uStack_138;
      *param_1 = uStack_140;
    }
    if (lStack_180 != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
    if (bVar2) goto code_r0x01f14cc8;
  }
  uStack_140 = 0;
  uStack_138 = 0;
  uStack_130 = 0;
  void CParameterPropertyBase<91u>::CryptString<string >(string&, string const&)(&uStack_140,lStack_178 + 0x378);
  if ((*param_1 & 1) == 0) {
    *(undefined2 *)param_1 = 0;
  }
  else {
    *(undefined1 *)param_1[2] = 0;
    param_1[1] = 0;
  }
  string::reserve(unsigned long)(param_1,0);
  param_1[2] = uStack_130;
  param_1[1] = uStack_138;
  *param_1 = uStack_140;
code_r0x01f14cc8:
  if (lStack_170 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return;
}

// ==== CUIVoiceManager::GetHomeVoicePackSubName(unsigned int)
// vaddr 0x1e14d24 | ghidra 0x1f14d24 | size 1052 | symbol _ZN15CUIVoiceManager23GetHomeVoicePackSubNameEj | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Removing unreachable block (ram,0x01f15078) */
/* WARNING: Removing unreachable block (ram,0x01f15080) */
/* WARNING: Type propagation algorithm not settling */

void _ZN15CUIVoiceManager23GetHomeVoicePackSubNameEj
               (ulong *param_1,undefined8 param_2,undefined4 param_3)

{
  ulong *puVar1;
  bool bVar2;
  undefined *puVar3;
  int iVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  undefined8 uVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uStack_1b8;
  undefined8 uStack_1b0;
  ulong uStack_1a8;
  ulong uStack_1a0;
  ulong uStack_198;
  ulong uStack_190;
  long lStack_188;
  long lStack_180;
  long lStack_178;
  long lStack_170;
  undefined *puStack_168;
  undefined8 uStack_160;
  ulong *puStack_158;
  undefined8 uStack_150;
  undefined4 uStack_148;
  undefined1 uStack_144;
  ulong uStack_140;
  ulong uStack_138;
  ulong uStack_130;
  
  CParameterUtility::FindPersonWithId(unsigned int)(&lStack_178,param_3);
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  if (lStack_178 == 0) goto code_r0x01f150e4;
  iVar4 = CUIUtility::GetPersonVoiceSwitchID(unsigned int)(*(undefined4 *)(lStack_178 + 0x38));
  puVar3 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (iVar4 != 0) {
    lVar7 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar7 = *(long *)puVar3;
    }
    uVar8 = *(undefined8 *)(*(long *)(lVar7 + 0x5f8) + 0x418);
    snprintf(&uStack_140,0x100,&UNK_027e6d32/*"%u"*/,iVar4);
    puStack_168 = &UNK_027ffe64/*"id"*/;
    uStack_160 = 2;
    puStack_158 = &uStack_140;
    uStack_150 = strlen(&uStack_140);
    uStack_148 = 0;
    uStack_144 = 0;
    CMasterParameterBaseSqlite_Simple<CMasterParameterVoiceSwitchElement>::ParameterByQuery(char const*, Aska::Yayoi::QueryParam*, unsigned int) const(&lStack_188,uVar8,&UNK_027ffd77/*"SELECT * FROM master_voice_switch WHERE id=?"*/,&puStack_168,1);
    if (lStack_188 == 0) {
code_r0x01f15060:
      bVar2 = false;
    }
    else {
      uStack_160 = 0;
      puStack_158 = (ulong *)0x0;
      puStack_168 = (undefined *)0x0;
      void CParameterPropertyBase<54u>::CryptString<string >(string&, string const&)(&puStack_168,lStack_188 + 0x328);
      uStack_138 = 0;
      uStack_130 = 0;
      puVar1 = (ulong *)((ulong)&puStack_168 | 1);
      if (((ulong)puStack_168 & 1) != 0) {
        puVar1 = puStack_158;
      }
      uStack_140 = 0;
      uVar5 = strlen(puVar1);
      if (uVar5 < 0x17) {
        uVar9 = (ulong)&uStack_140 | 1;
        uStack_140 = CONCAT71(uStack_140._1_7_,(char)(uVar5 << 1));
        if (uVar5 != 0) goto code_r0x01f14ec8;
      }
      else {
        uVar6 = uVar5 + 0x10 & 0xfffffffffffffff0;
        if (uVar6 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar9 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (uVar9 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        uStack_140 = uVar6 | 1;
        uStack_138 = uVar5;
        uStack_130 = uVar9;
code_r0x01f14ec8:
        memcpy(uVar9,puVar1,uVar5);
      }
      *(undefined1 *)(uVar9 + uVar5) = 0;
      uStack_1b8 = 0;
      uStack_1b0 = 0;
      uStack_1a8 = 0;
      void CParameterPropertyBase<55u>::CryptString<string >(string&, string const&)(&uStack_1b8,lStack_188 + 0x368);
      uStack_198 = 0;
      uStack_190 = 0;
      uVar5 = (ulong)&uStack_1b8 | 1;
      if ((uStack_1b8 & 1) != 0) {
        uVar5 = uStack_1a8;
      }
      uStack_1a0 = 0;
      uVar6 = strlen(uVar5);
      if (uVar6 < 0x17) {
        uVar10 = (ulong)&uStack_1a0 | 1;
        uStack_1a0 = CONCAT71(uStack_1a0._1_7_,(char)(uVar6 << 1));
        if (uVar6 != 0) goto code_r0x01f14fa4;
      }
      else {
        uVar9 = uVar6 + 0x10 & 0xfffffffffffffff0;
        if (uVar9 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar9,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (uVar10 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        uStack_1a0 = uVar9 | 1;
        uStack_198 = uVar6;
        uStack_190 = uVar10;
code_r0x01f14fa4:
        memcpy(uVar10,uVar5,uVar6);
      }
      *(undefined1 *)(uVar10 + uVar6) = 0;
      uVar5 = CUIUtility::IsWithinDayEnableEmpty(string const&, string const&)(&uStack_140,&uStack_1a0);
      if ((uStack_1a0 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_190);
      }
      if ((uStack_1b8 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_1a8);
      }
      if ((uStack_140 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_130);
      }
      if (((ulong)puStack_168 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_158);
      }
      if ((uVar5 & 1) == 0) {
        CUIUtility::SetPersonVoiceSwitchID(unsigned int, unsigned int)(*(undefined4 *)(lStack_178 + 0x38),0);
        goto code_r0x01f15060;
      }
      uStack_140 = 0;
      uStack_138 = 0;
      uStack_130 = 0;
      void CParameterPropertyBase<50u>::CryptString<string >(string&, string const&)(&uStack_140,lStack_188 + 0x238);
      if ((*param_1 & 1) == 0) {
        *(undefined2 *)param_1 = 0;
      }
      else {
        *(undefined1 *)param_1[2] = 0;
        param_1[1] = 0;
      }
      string::reserve(unsigned long)(param_1,0);
      bVar2 = true;
      param_1[2] = uStack_130;
      param_1[1] = uStack_138;
      *param_1 = uStack_140;
    }
    if (lStack_180 != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
    if (bVar2) goto code_r0x01f150e4;
  }
  uStack_140 = 0;
  uStack_138 = 0;
  uStack_130 = 0;
  void CParameterPropertyBase<92u>::CryptString<string >(string&, string const&)(&uStack_140,lStack_178 + 0x3b8);
  if ((*param_1 & 1) == 0) {
    *(undefined2 *)param_1 = 0;
  }
  else {
    *(undefined1 *)param_1[2] = 0;
    param_1[1] = 0;
  }
  string::reserve(unsigned long)(param_1,0);
  param_1[2] = uStack_130;
  param_1[1] = uStack_138;
  *param_1 = uStack_140;
code_r0x01f150e4:
  if (lStack_170 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return;
}

// ==== CUIVoiceManager::GetPackNameFromCategory(unsigned int, unsigned int)
// vaddr 0x1e15140 | ghidra 0x1f15140 | size 16 | symbol _ZN15CUIVoiceManager23GetPackNameFromCategoryEjj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager23GetPackNameFromCategoryEjj
               (undefined8 param_1,undefined8 param_2,int param_3)

{
  if (param_3 == 1) {
    (*(code *)PTR__ZN15CUIVoiceManager20GetMenuVoicePackNameEj_02cb1f70)();
    return;
  }
  (*(code *)PTR__ZN15CUIVoiceManager22GetBattleVoicePackNameEj_02cada58)();
  return;
}

// ==== CUIVoiceManager::GetGachaVoicePackName(unsigned int, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >&, unsigned int&)
// vaddr 0x1e15150 | ghidra 0x1f15150 | size 344 | symbol _ZN15CUIVoiceManager21GetGachaVoicePackNameEjRNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEERj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager21GetGachaVoicePackNameEjRNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEERj
               (undefined8 param_1,undefined4 param_2,byte *param_3,undefined4 *param_4)

{
  undefined8 uVar1;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  long lStack_50;
  long lStack_48;
  long lStack_40;
  long lStack_38;
  
  uVar1 = CParameterUtility::FindPersonWithId(unsigned int)(&lStack_40,param_2);
  if (lStack_40 == 0) goto joined_r0x01f1524c;
  uVar1 = CUIVoiceManager::GetMenuVoiceMasterID(unsigned int)(uVar1,*(undefined4 *)(lStack_40 + 0x38));
  if ((int)uVar1 == 0) {
    uStack_68 = 0;
    uStack_60 = 0;
    uStack_58 = 0;
    void CParameterPropertyBase<118u>::CryptString<string >(string&, string const&)(&uStack_68,lStack_40 + 0x968);
    if ((*param_3 & 1) == 0) {
      param_3[0] = 0;
      param_3[1] = 0;
    }
    else {
      **(undefined1 **)(param_3 + 0x10) = 0;
      param_3[8] = 0;
      param_3[9] = 0;
      param_3[10] = 0;
      param_3[0xb] = 0;
      param_3[0xc] = 0;
      param_3[0xd] = 0;
      param_3[0xe] = 0;
      param_3[0xf] = 0;
    }
    string::reserve(unsigned long)(param_3,0);
    *(undefined8 *)(param_3 + 0x10) = uStack_58;
    *(undefined8 *)(param_3 + 8) = uStack_60;
    *(undefined8 *)param_3 = uStack_68;
    *param_4 = *(undefined4 *)(lStack_40 + 0xa78);
    goto joined_r0x01f1524c;
  }
  uVar1 = CUIVoiceManager::GetMenuVoice(std::__ndk1::shared_ptr<CMasterParameterPersonElement> const&, CUIVoiceManager::MenuVoiceID, unsigned int)(&lStack_50,uVar1,&lStack_40,2,0);
  if (lStack_50 != 0) {
    if (*(int *)(lStack_50 + 0x128) == 1) {
      CUIVoiceManager::GetMenuVoicePackName(unsigned int)(&uStack_68,uVar1,param_2);
      if ((*param_3 & 1) == 0) goto code_r0x01f15214;
code_r0x01f151c8:
      **(undefined1 **)(param_3 + 0x10) = 0;
      param_3[8] = 0;
      param_3[9] = 0;
      param_3[10] = 0;
      param_3[0xb] = 0;
      param_3[0xc] = 0;
      param_3[0xd] = 0;
      param_3[0xe] = 0;
      param_3[0xf] = 0;
    }
    else {
      CUIVoiceManager::GetBattleVoicePackName(unsigned int)(&uStack_68,uVar1,param_2);
      if ((*param_3 & 1) != 0) goto code_r0x01f151c8;
code_r0x01f15214:
      param_3[0] = 0;
      param_3[1] = 0;
    }
    string::reserve(unsigned long)(param_3,0);
    *(undefined8 *)(param_3 + 0x10) = uStack_58;
    *(undefined8 *)(param_3 + 8) = uStack_60;
    *(undefined8 *)param_3 = uStack_68;
    *param_4 = *(undefined4 *)(lStack_50 + 0x158);
  }
  if (lStack_48 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
joined_r0x01f1524c:
  if (lStack_38 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return;
}

// ==== CUIVoiceManager::GetMenuVoiceMasterID(unsigned int)
// vaddr 0x1e152a8 | ghidra 0x1f152a8 | size 876 | symbol _ZN15CUIVoiceManager20GetMenuVoiceMasterIDEj | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

ulong _ZN15CUIVoiceManager20GetMenuVoiceMasterIDEj(undefined8 param_1,undefined4 param_2)

{
  ulong *puVar1;
  bool bVar2;
  undefined *puVar3;
  int iVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  undefined **ppuVar8;
  undefined8 uVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uStack_1a8;
  undefined8 uStack_1a0;
  ulong uStack_198;
  ulong uStack_190;
  ulong uStack_188;
  ulong uStack_180;
  long lStack_178;
  long lStack_170;
  long lStack_168;
  long lStack_160;
  undefined *puStack_158;
  undefined8 uStack_150;
  ulong *puStack_148;
  undefined8 uStack_140;
  undefined4 uStack_138;
  undefined1 uStack_134;
  ulong uStack_130;
  ulong uStack_128;
  ulong uStack_120;
  
  CParameterUtility::FindPersonWithId(unsigned int)(&lStack_168,param_2);
  if (lStack_168 == 0) {
    ppuVar8 = (undefined **)0x0;
    goto joined_r0x01f153e0;
  }
  iVar4 = CUIUtility::GetPersonVoiceSwitchID(unsigned int)(*(undefined4 *)(lStack_168 + 0x38));
  puVar3 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (iVar4 != 0) {
    lVar7 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar7 = *(long *)puVar3;
    }
    uVar9 = *(undefined8 *)(*(long *)(lVar7 + 0x5f8) + 0x418);
    snprintf(&uStack_130,0x100,&UNK_027e6d32/*"%u"*/,iVar4);
    puStack_158 = &UNK_027ffe64/*"id"*/;
    uStack_150 = 2;
    puStack_148 = &uStack_130;
    uStack_140 = strlen(&uStack_130);
    uStack_138 = 0;
    uStack_134 = 0;
    ppuVar8 = &puStack_158;
    CMasterParameterBaseSqlite_Simple<CMasterParameterVoiceSwitchElement>::ParameterByQuery(char const*, Aska::Yayoi::QueryParam*, unsigned int) const(&lStack_178,uVar9,&UNK_027ffd77/*"SELECT * FROM master_voice_switch WHERE id=?"*/,&puStack_158,1);
    if (lStack_178 == 0) {
code_r0x01f155d4:
      bVar2 = false;
    }
    else {
      uStack_150 = 0;
      puStack_148 = (ulong *)0x0;
      puStack_158 = (undefined *)0x0;
      void CParameterPropertyBase<54u>::CryptString<string >(string&, string const&)(&puStack_158,lStack_178 + 0x328);
      uStack_128 = 0;
      uStack_120 = 0;
      puVar1 = (ulong *)((ulong)ppuVar8 | 1);
      if (((ulong)puStack_158 & 1) != 0) {
        puVar1 = puStack_148;
      }
      uStack_130 = 0;
      uVar5 = strlen(puVar1);
      if (uVar5 < 0x17) {
        uVar10 = (ulong)&uStack_130 | 1;
        uStack_130 = CONCAT71(uStack_130._1_7_,(char)(uVar5 << 1));
        if (uVar5 != 0) goto code_r0x01f1544c;
      }
      else {
        uVar6 = uVar5 + 0x10 & 0xfffffffffffffff0;
        if (uVar6 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (uVar10 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        uStack_130 = uVar6 | 1;
        uStack_128 = uVar5;
        uStack_120 = uVar10;
code_r0x01f1544c:
        memcpy(uVar10,puVar1,uVar5);
      }
      *(undefined1 *)(uVar10 + uVar5) = 0;
      uStack_1a8 = 0;
      uStack_1a0 = 0;
      uStack_198 = 0;
      void CParameterPropertyBase<55u>::CryptString<string >(string&, string const&)(&uStack_1a8,lStack_178 + 0x368);
      uStack_188 = 0;
      uStack_180 = 0;
      uVar5 = (ulong)&uStack_1a8 | 1;
      if ((uStack_1a8 & 1) != 0) {
        uVar5 = uStack_198;
      }
      uStack_190 = 0;
      uVar6 = strlen(uVar5);
      if (uVar6 < 0x17) {
        uVar11 = (ulong)&uStack_190 | 1;
        uStack_190 = CONCAT71(uStack_190._1_7_,(char)(uVar6 << 1));
        if (uVar6 != 0) goto code_r0x01f15528;
      }
      else {
        uVar10 = uVar6 + 0x10 & 0xfffffffffffffff0;
        if (uVar10 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        uVar11 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar10,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (uVar11 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        uStack_190 = uVar10 | 1;
        uStack_188 = uVar6;
        uStack_180 = uVar11;
code_r0x01f15528:
        memcpy(uVar11,uVar5,uVar6);
      }
      *(undefined1 *)(uVar11 + uVar6) = 0;
      uVar5 = CUIUtility::IsWithinDayEnableEmpty(string const&, string const&)(&uStack_130,&uStack_190);
      ppuVar8 = (undefined **)(uVar5 & 0xffffffff);
      if ((uStack_190 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_180);
      }
      if ((uStack_1a8 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_198);
      }
      if ((uStack_130 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_120);
      }
      if (((ulong)puStack_158 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_148);
      }
      if ((uVar5 & 1) == 0) {
        CUIUtility::SetPersonVoiceSwitchID(unsigned int, unsigned int)(*(undefined4 *)(lStack_168 + 0x38),0);
        goto code_r0x01f155d4;
      }
      bVar2 = true;
      ppuVar8 = (undefined **)(ulong)*(uint *)(lStack_178 + 0x188);
    }
    if (lStack_170 != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
    if (bVar2) goto joined_r0x01f153e0;
  }
  ppuVar8 = (undefined **)(ulong)*(uint *)(lStack_168 + 0x308);
joined_r0x01f153e0:
  if (lStack_160 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return (ulong)ppuVar8 & 0xffffffff;
}

// ==== CUIVoiceManager::GetMenuVoice(std::__ndk1::shared_ptr<CMasterParameterPersonElement> const&, CUIVoiceManager::MenuVoiceID, unsigned int)
// vaddr 0x1e15614 | ghidra 0x1f15614 | size 1320 | symbol _ZN15CUIVoiceManager12GetMenuVoiceERKNSt6__ndk110shared_ptrI29CMasterParameterPersonElementEENS_11MenuVoiceIDEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager12GetMenuVoiceERKNSt6__ndk110shared_ptrI29CMasterParameterPersonElementEENS_11MenuVoiceIDEj
               (long *param_1,undefined8 param_2,long *param_3,uint param_4,uint param_5)

{
  uint uVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  int iVar4;
  long lVar5;
  ulong uVar6;
  undefined8 uVar7;
  long *plVar8;
  long lStack_2d8;
  undefined8 uStack_2d0;
  long *plStack_2c8;
  undefined8 uStack_2c0;
  undefined4 uStack_2b8;
  undefined *puStack_2b0;
  undefined8 uStack_2a8;
  undefined4 **ppuStack_2a0;
  undefined8 uStack_298;
  undefined4 uStack_290;
  undefined1 uStack_28c;
  undefined *puStack_288;
  undefined8 uStack_280;
  undefined1 *puStack_278;
  undefined8 uStack_270;
  undefined4 uStack_268;
  undefined1 uStack_264;
  undefined1 auStack_260 [256];
  undefined4 *puStack_160;
  undefined4 *puStack_158;
  undefined4 *puStack_150;
  
  if ((*param_3 != 0) &&
     (iVar4 = CUIVoiceManager::GetMenuVoiceMasterID(unsigned int)(param_2,*(undefined4 *)(*param_3 + 0x38)),
     puVar2 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0, iVar4 != 0)
     ) {
    lVar5 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (lVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar5 = *(long *)puVar2;
    }
    lVar5 = CParameterManager::pMasterParameterMenuVoice() const(lVar5);
    if (lVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029588d8/*"C:\BAS_Submission\Client\Project\..\Source\Game\UI\UIVoiceManager.cpp"*/,0x231,&UNK_02958929/*"pMenuVoice is null."*/);
    }
    uStack_2c0 = 0;
    plStack_2c8 = (long *)0x0;
    uStack_2d0 = 0;
    lStack_2d8 = 0;
    uStack_2b8 = 0x3f800000;
    snprintf(&puStack_160,0x100,&UNK_027e6d32/*"%u"*/,iVar4);
    snprintf(auStack_260,0x100,&UNK_027e6d32/*"%u"*/,param_4);
    puStack_2b0 = &UNK_02847bef/*"group_id"*/;
    uStack_2a8 = 8;
    ppuStack_2a0 = &puStack_160;
    uStack_298 = strlen(&puStack_160);
    uStack_290 = 0;
    uStack_28c = 0;
    puStack_288 = &UNK_028472c9/*"menu_voice_type"*/;
    uStack_280 = 0xf;
    puStack_278 = auStack_260;
    uStack_270 = strlen(auStack_260);
    uStack_268 = 0;
    uStack_264 = 0;
    CMasterParameterBaseSqlite_Simple<CMasterParameterMenuVoiceElement>::ParameterByQuery(char const*, Framework::CSTLUnorderedMap<unsigned int, CMasterParameterMenuVoiceElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int> >&, Aska::Yayoi::QueryParam*, unsigned int) const(lVar5,&UNK_02958943/*"SELECT * FROM master_menu_voice WHERE group_id=? AND menu_voice_type=?"*/,&lStack_2d8,&puStack_2b0,2);
    puStack_158 = (undefined4 *)0x0;
    puStack_150 = (undefined4 *)0x0;
    puStack_160 = (undefined4 *)0x0;
    if (plStack_2c8 != (long *)0x0) {
      plVar8 = plStack_2c8;
      if (param_4 == 1) {
        do {
          while (puVar3 = puStack_158, puStack_158 != puStack_150) {
            if (puStack_158 == (undefined4 *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
            }
            *puVar3 = (int)plVar8[2];
            puStack_158 = puStack_158 + 1;
            plVar8 = (long *)*plVar8;
            if (plVar8 == (long *)0x0) goto code_r0x01f15928;
          }
          void std::__ndk1::vector<unsigned int, Framework::CSTLAllocator<unsigned int, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<unsigned int const&>(unsigned int const&)(&puStack_160,plVar8 + 2);
          plVar8 = (long *)*plVar8;
        } while (plVar8 != (long *)0x0);
      }
      else if (param_4 == 2) {
        do {
          while (puVar3 = puStack_158, puStack_158 != puStack_150) {
            if (puStack_158 == (undefined4 *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
            }
            *puVar3 = (int)plVar8[2];
            puStack_158 = puStack_158 + 1;
            plVar8 = (long *)*plVar8;
            if (plVar8 == (long *)0x0) goto code_r0x01f15928;
          }
          void std::__ndk1::vector<unsigned int, Framework::CSTLAllocator<unsigned int, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<unsigned int const&>(unsigned int const&)(&puStack_160,plVar8 + 2);
          plVar8 = (long *)*plVar8;
        } while (plVar8 != (long *)0x0);
      }
      else {
        do {
          while (puVar3 = puStack_158, 7 < param_4) {
code_r0x01f15908:
            plVar8 = (long *)*plVar8;
joined_r0x01f158d8:
            if (plVar8 == (long *)0x0) goto code_r0x01f15928;
          }
          uVar1 = 1 << (ulong)(param_4 & 0x1f);
          if ((uVar1 & 0x96) == 0) {
            if ((uVar1 & 0x68) != 0) {
              if (((*(uint *)(plVar8 + 0x1c) == 0) || (*(uint *)(plVar8 + 0x1c) <= param_5)) &&
                 ((*(uint *)(plVar8 + 0x22) == 0 || (param_5 <= *(uint *)(plVar8 + 0x22)))))
              goto code_r0x01f1589c;
            }
            goto code_r0x01f15908;
          }
code_r0x01f1589c:
          if (puStack_158 != puStack_150) {
            if (puStack_158 == (undefined4 *)0x0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
            }
            *puVar3 = (int)plVar8[2];
            puStack_158 = puStack_158 + 1;
            plVar8 = (long *)*plVar8;
            goto joined_r0x01f158d8;
          }
          void std::__ndk1::vector<unsigned int, Framework::CSTLAllocator<unsigned int, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<unsigned int const&>(unsigned int const&)(&puStack_160,plVar8 + 2);
          plVar8 = (long *)*plVar8;
        } while (plVar8 != (long *)0x0);
      }
    }
code_r0x01f15928:
    if (puStack_160 != puStack_158) {
      uVar6 = Aska::Random(unsigned int)((ulong)((long)puStack_158 - (long)puStack_160) >> 2);
      uVar6 = uVar6 & 0xffffffff;
      uVar7 = Aska::Global::GetAvailableMemoryManager()();
      plVar8 = (long *)Aska::MemoryManager::Malloc(unsigned long)(uVar7,0x178);
      plVar8[2] = 0;
      *plVar8 = (long)(
                      PTR__ZTVNSt6__ndk120__shared_ptr_emplaceI32CMasterParameterMenuVoiceElement16BAS_STLAllocatorIS1_EEE_02cc0610
                      + 0x10);
      plVar8[1] = 0;
      CMasterParameterMenuVoiceElement::CMasterParameterMenuVoiceElement()(plVar8 + 3);
      *param_1 = (long)(plVar8 + 3);
      param_1[1] = (long)plVar8;
      if ((ulong)((long)puStack_158 - (long)puStack_160 >> 2) <= uVar6) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar6);
      }
      lVar5 = std::__ndk1::unordered_map<unsigned int, CMasterParameterMenuVoiceElement, std::__ndk1::hash<unsigned int>, std::__ndk1::equal_to<unsigned int>, Framework::CSTLAllocator<std::__ndk1::pair<unsigned int const, CMasterParameterMenuVoiceElement>, Framework::CSTLUnorderedMapAllocatorInf> >::operator[](unsigned int const&)(&lStack_2d8,puStack_160 + uVar6);
      plVar8[4] = *(long *)(lVar5 + 8);
      plVar8[6] = *(long *)(lVar5 + 0x18);
      *(undefined1 *)(plVar8 + 7) = *(undefined1 *)(lVar5 + 0x20);
      *(undefined4 *)(plVar8 + 9) = *(undefined4 *)(lVar5 + 0x30);
      *(undefined4 *)(plVar8 + 10) = *(undefined4 *)(lVar5 + 0x38);
      plVar8[0xc] = *(long *)(lVar5 + 0x48);
      *(undefined1 *)(plVar8 + 0xd) = *(undefined1 *)(lVar5 + 0x50);
      *(undefined4 *)(plVar8 + 0xf) = *(undefined4 *)(lVar5 + 0x60);
      *(undefined4 *)(plVar8 + 0x10) = *(undefined4 *)(lVar5 + 0x68);
      plVar8[0x12] = *(long *)(lVar5 + 0x78);
      *(undefined1 *)(plVar8 + 0x13) = *(undefined1 *)(lVar5 + 0x80);
      *(undefined4 *)(plVar8 + 0x15) = *(undefined4 *)(lVar5 + 0x90);
      *(undefined4 *)(plVar8 + 0x16) = *(undefined4 *)(lVar5 + 0x98);
      plVar8[0x18] = *(long *)(lVar5 + 0xa8);
      *(undefined1 *)(plVar8 + 0x19) = *(undefined1 *)(lVar5 + 0xb0);
      *(undefined4 *)(plVar8 + 0x1b) = *(undefined4 *)(lVar5 + 0xc0);
      *(undefined4 *)(plVar8 + 0x1c) = *(undefined4 *)(lVar5 + 200);
      plVar8[0x1e] = *(long *)(lVar5 + 0xd8);
      *(undefined1 *)(plVar8 + 0x1f) = *(undefined1 *)(lVar5 + 0xe0);
      *(undefined4 *)(plVar8 + 0x21) = *(undefined4 *)(lVar5 + 0xf0);
      *(undefined4 *)(plVar8 + 0x22) = *(undefined4 *)(lVar5 + 0xf8);
      plVar8[0x24] = *(long *)(lVar5 + 0x108);
      *(undefined1 *)(plVar8 + 0x25) = *(undefined1 *)(lVar5 + 0x110);
      *(undefined4 *)(plVar8 + 0x27) = *(undefined4 *)(lVar5 + 0x120);
      *(undefined4 *)(plVar8 + 0x28) = *(undefined4 *)(lVar5 + 0x128);
      plVar8[0x2a] = *(long *)(lVar5 + 0x138);
      *(undefined1 *)(plVar8 + 0x2b) = *(undefined1 *)(lVar5 + 0x140);
      *(undefined4 *)(plVar8 + 0x2d) = *(undefined4 *)(lVar5 + 0x150);
      *(undefined4 *)(plVar8 + 0x2e) = *(undefined4 *)(lVar5 + 0x158);
      if (puStack_160 != (undefined4 *)0x0) {
        if (puStack_158 != puStack_160) {
          puStack_158 = (undefined4 *)
                        ((long)puStack_158 +
                        (~((long)puStack_158 + (-4 - (long)puStack_160)) & 0xfffffffffffffffcU));
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
      }
      std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, CMasterParameterMenuVoiceElement>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CMasterParameterMenuVoiceElement>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CMasterParameterMenuVoiceElement>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, CMasterParameterMenuVoiceElement>, Framework::CSTLUnorderedMapAllocatorInf> >::__deallocate(std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<unsigned int, CMasterParameterMenuVoiceElement>, void*>*)(&lStack_2d8,plStack_2c8);
      lVar5 = lStack_2d8;
      lStack_2d8 = 0;
      if (lVar5 == 0) {
        return;
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
      return;
    }
    if (puStack_160 != (undefined4 *)0x0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
    std::__ndk1::__hash_table<std::__ndk1::__hash_value_type<unsigned int, CMasterParameterMenuVoiceElement>, std::__ndk1::__unordered_map_hasher<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CMasterParameterMenuVoiceElement>, std::__ndk1::hash<unsigned int>, true>, std::__ndk1::__unordered_map_equal<unsigned int, std::__ndk1::__hash_value_type<unsigned int, CMasterParameterMenuVoiceElement>, std::__ndk1::equal_to<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__hash_value_type<unsigned int, CMasterParameterMenuVoiceElement>, Framework::CSTLUnorderedMapAllocatorInf> >::__deallocate(std::__ndk1::__hash_node<std::__ndk1::__hash_value_type<unsigned int, CMasterParameterMenuVoiceElement>, void*>*)(&lStack_2d8,plStack_2c8);
    lVar5 = lStack_2d8;
    lStack_2d8 = 0;
    if (lVar5 != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
    }
  }
  *param_1 = 0;
  param_1[1] = 0;
  return;
}

// ==== CUIVoiceManager::PlayMenuVoice(CUIVoiceManager::MenuVoiceID, unsigned int, unsigned int)
// vaddr 0x1e15b3c | ghidra 0x1f15b3c | size 260 | symbol _ZN15CUIVoiceManager13PlayMenuVoiceENS_11MenuVoiceIDEjj | lib libSOA-3.7.0.so | 2026-10-08
undefined4
_ZN15CUIVoiceManager13PlayMenuVoiceENS_11MenuVoiceIDEjj
          (undefined8 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined8 uVar2;
  long lStack_50;
  long lStack_48;
  long lStack_40;
  long lStack_38;
  
  uVar2 = CParameterUtility::FindPersonWithId(unsigned int)(&lStack_40,param_3);
  if ((lStack_40 == 0) ||
     (uVar2 = CUIVoiceManager::GetMenuVoiceMasterID(unsigned int)(uVar2,*(undefined4 *)(lStack_40 + 0x38)), (int)uVar2 == 0)) {
    if (param_2 - 4U < 4) {
      CUIVoiceManager::PlayLimitOverVoice(unsigned int)(param_1,param_3);
    }
    else if (param_2 == 3) {
      CUIVoiceManager::PlayLevelUPVoiceStrength(unsigned int, unsigned int)(param_1,param_3,param_4);
    }
    else if (param_2 == 1) {
      uVar1 = CUIVoiceManager::PlayBattleVoice(unsigned int, unsigned int)(param_1,param_3,param_4);
      goto joined_r0x01f15c00;
    }
  }
  else {
    CUIVoiceManager::GetMenuVoice(std::__ndk1::shared_ptr<CMasterParameterPersonElement> const&, CUIVoiceManager::MenuVoiceID, unsigned int)(&lStack_50,uVar2,&lStack_40,param_2,param_4);
    if (lStack_50 != 0) {
      CUIVoiceManager::AddMenuVoice(unsigned int, unsigned int, unsigned int)(param_1,param_3,*(undefined4 *)(lStack_50 + 0x128),
                      *(undefined4 *)(lStack_50 + 0x158));
    }
    if (lStack_48 != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
  }
  uVar1 = 0;
joined_r0x01f15c00:
  if (lStack_38 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return uVar1;
}

// ==== CUIVoiceManager::AddMenuVoice(unsigned int, unsigned int, unsigned int)
// vaddr 0x1e15c40 | ghidra 0x1f15c40 | size 616 | symbol _ZN15CUIVoiceManager12AddMenuVoiceEjjj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager12AddMenuVoiceEjjj
               (long param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  ulong *puVar1;
  ulong uVar2;
  undefined1 *puVar3;
  undefined8 uVar4;
  ulong uVar5;
  ulong uVar6;
  byte bStack_78;
  undefined7 uStack_77;
  ulong uStack_70;
  ulong uStack_68;
  ulong uStack_60;
  ulong uStack_58;
  undefined1 *puStack_50;
  undefined4 uStack_48;
  
  uStack_58 = 0;
  puStack_50 = (undefined1 *)0x0;
  uStack_60 = 0;
  if (param_3 == 1) {
    CUIVoiceManager::GetMenuVoicePackName(unsigned int)();
    if ((uStack_60 & 1) != 0) goto code_r0x01f15c80;
code_r0x01f15c9c:
    uStack_60 = uStack_60 & 0xffffffffffff0000;
  }
  else {
    CUIVoiceManager::GetBattleVoicePackName(unsigned int)(&bStack_78);
    if ((uStack_60 & 1) == 0) goto code_r0x01f15c9c;
code_r0x01f15c80:
    *puStack_50 = 0;
    uStack_58 = 0;
  }
  uVar4 = string::reserve(unsigned long)(&uStack_60,0);
  uStack_60 = CONCAT71(uStack_77,bStack_78);
  puStack_50 = (undefined1 *)uStack_68;
  uStack_58 = uStack_70;
  uStack_48 = param_4;
  CUIVoiceManager::GetMenuVoicePackName(unsigned int)(&bStack_78,uVar4,param_2);
  uVar4 = CUIVoiceManager::StopPlayPack(string const&, float)(0x40000000,param_1,&bStack_78);
  if ((bStack_78 & 1) != 0) {
    uVar4 = Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
  }
  CUIVoiceManager::GetBattleVoicePackName(unsigned int)(&bStack_78,uVar4,param_2);
  uVar4 = CUIVoiceManager::StopPlayPack(string const&, float)(0x40000000,param_1,&bStack_78);
  if ((bStack_78 & 1) != 0) {
    uVar4 = Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
  }
  CUIVoiceManager::GetHomeVoicePackName(unsigned int)(&bStack_78,uVar4,param_2);
  uVar4 = CUIVoiceManager::StopPlayPack(string const&, float)(0x40000000,param_1,&bStack_78);
  if ((bStack_78 & 1) != 0) {
    uVar4 = Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
  }
  CUIVoiceManager::GetHomeVoicePackSubName(unsigned int)(&bStack_78,uVar4,param_2);
  CUIVoiceManager::StopPlayPack(string const&, float)(0x40000000,param_1,&bStack_78);
  if ((bStack_78 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
  }
  puVar1 = *(ulong **)(param_1 + 0x10);
  if (puVar1 == *(ulong **)(param_1 + 0x18)) {
    void std::__ndk1::vector<CUIVoiceManager::UpVoiceData, Framework::CSTLAllocator<CUIVoiceManager::UpVoiceData, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<CUIVoiceManager::UpVoiceData const&>(CUIVoiceManager::UpVoiceData const&)(param_1 + 8,&uStack_60);
    goto joined_r0x01f15dcc;
  }
  if (puVar1 == (ulong *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  puVar3 = puStack_50;
  uVar2 = uStack_58;
  puVar1[1] = 0;
  puVar1[2] = 0;
  *puVar1 = 0;
  if ((uStack_60 & 1) == 0) {
    puVar1[2] = (ulong)puStack_50;
    puVar1[1] = uStack_58;
    *puVar1 = uStack_60;
  }
  else {
    if (uStack_58 < 0x17) {
      uVar5 = (long)puVar1 + 1;
      *(char *)puVar1 = (char)(uStack_58 << 1);
      if (uStack_58 != 0) goto code_r0x01f15e58;
    }
    else {
      uVar6 = uStack_58 + 0x10 & 0xfffffffffffffff0;
      if (uVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar5 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      puVar1[1] = uVar2;
      puVar1[2] = uVar5;
      *puVar1 = uVar6 | 1;
code_r0x01f15e58:
      memcpy(uVar5,puVar3,uVar2);
    }
    *(undefined1 *)(uVar5 + uVar2) = 0;
  }
  *(undefined4 *)(puVar1 + 3) = uStack_48;
  *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + 0x20;
joined_r0x01f15dcc:
  if ((uStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_50);
  }
  return;
}

// ==== CUIVoiceManager::PlayBattleVoice(unsigned int, unsigned int)
// vaddr 0x1e15ea8 | ghidra 0x1f15ea8 | size 688 | symbol _ZN15CUIVoiceManager15PlayBattleVoiceEjj | lib libSOA-3.7.0.so | 2026-10-08
int _ZN15CUIVoiceManager15PlayBattleVoiceEjj(long param_1,undefined4 param_2,int param_3)

{
  ulong *puVar1;
  undefined *puVar2;
  ulong uVar3;
  ulong uVar4;
  int iVar5;
  undefined8 uVar6;
  ulong uVar7;
  long lVar8;
  undefined8 uVar9;
  ulong uVar10;
  ulong uVar11;
  int iVar12;
  ulong uStack_90;
  ulong uStack_88;
  ulong uStack_80;
  int iStack_78;
  byte bStack_68;
  undefined7 uStack_67;
  ulong uStack_60;
  ulong uStack_58;
  
  puVar2 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar8 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar8 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar8 = *(long *)puVar2;
  }
  uVar6 = CMasterParameterBaseSqlite_Simple<CMasterParameterPersonElement>::pParameterFromHash(unsigned int) const(&uStack_90,*(undefined8 *)(*(long *)(lVar8 + 0x5f8) + 400),param_2);
  uVar3 = uStack_88;
  if (uStack_88 != 0) {
    std::__ndk1::__shared_weak_count::__add_shared()(uStack_88);
    uVar6 = 0;
    if (uStack_88 != 0) {
      uVar6 = std::__ndk1::__shared_weak_count::__release_shared()();
    }
  }
  if (uStack_90 == 0) {
    iVar5 = -1;
  }
  else {
    uStack_88 = 0;
    uStack_80 = 0;
    uStack_90 = 0;
    uVar9 = *(undefined8 *)PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
    CUIVoiceManager::GetBattleVoicePackName(unsigned int)(&bStack_68,uVar6,param_2);
    uStack_90 = uStack_90 & 0xffffffffffff0000;
    string::reserve(unsigned long)(&uStack_90,0);
    uStack_90 = CONCAT71(uStack_67,bStack_68);
    iVar12 = 0;
    uStack_80 = uStack_58;
    uStack_88 = uStack_60;
    do {
      iVar5 = Aska::Random(unsigned int)(0x25);
      iVar5 = *(int *)(&UNK_0295898c + (long)iVar5 * 4);
      uVar7 = (ulong)&uStack_90 | 1;
      if ((uStack_90 & 1) != 0) {
        uVar7 = uStack_80;
      }
      uVar7 = CSoundManager::IsResourceExist(char const*, unsigned int)(uVar9,uVar7,iVar5);
      if ((iVar5 != param_3) && ((uVar7 & 1) != 0)) {
        iStack_78 = iVar5;
        CUIVoiceManager::GetBattleVoicePackName(unsigned int)(&bStack_68,uVar7,param_2);
        CUIVoiceManager::StopPlayPack(string const&, float)(0x40000000,param_1,&bStack_68);
        if ((bStack_68 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_58);
        }
        puVar1 = *(ulong **)(param_1 + 0x10);
        if (puVar1 == *(ulong **)(param_1 + 0x18)) {
          void std::__ndk1::vector<CUIVoiceManager::UpVoiceData, Framework::CSTLAllocator<CUIVoiceManager::UpVoiceData, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<CUIVoiceManager::UpVoiceData const&>(CUIVoiceManager::UpVoiceData const&)(param_1 + 8,&uStack_90);
        }
        else {
          if (puVar1 == (ulong *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          uVar4 = uStack_80;
          uVar7 = uStack_88;
          puVar1[1] = 0;
          puVar1[2] = 0;
          *puVar1 = 0;
          if ((uStack_90 & 1) == 0) {
            puVar1[2] = uStack_80;
            puVar1[1] = uStack_88;
            *puVar1 = uStack_90;
          }
          else {
            if (uStack_88 < 0x17) {
              uVar10 = (long)puVar1 + 1;
              *(char *)puVar1 = (char)(uStack_88 << 1);
              if (uStack_88 != 0) goto code_r0x01f160f4;
            }
            else {
              uVar11 = uStack_88 + 0x10 & 0xfffffffffffffff0;
              if (uVar11 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
              }
              uVar10 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
              if (uVar10 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
              }
              puVar1[1] = uVar7;
              puVar1[2] = uVar10;
              *puVar1 = uVar11 | 1;
code_r0x01f160f4:
              memcpy(uVar10,uVar4,uVar7);
            }
            *(undefined1 *)(uVar10 + uVar7) = 0;
          }
          *(int *)(puVar1 + 3) = iStack_78;
          *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + 0x20;
        }
        goto joined_r0x01f16120;
      }
      iVar12 = iVar12 + 1;
    } while (iVar12 < 0x24);
    iVar5 = -1;
joined_r0x01f16120:
    if ((uStack_90 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_80);
    }
  }
  if (uVar3 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()(uVar3);
  }
  return iVar5;
}

// ==== CUIVoiceManager::PlayLevelUPVoiceStrength(unsigned int, unsigned int)
// vaddr 0x1e16158 | ghidra 0x1f16158 | size 516 | symbol _ZN15CUIVoiceManager24PlayLevelUPVoiceStrengthEjj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager24PlayLevelUPVoiceStrengthEjj
               (undefined8 param_1,undefined4 param_2,uint param_3)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  int iVar4;
  int iVar5;
  short *psVar6;
  ulong uStack_80;
  ulong uStack_78;
  short *psStack_70;
  ulong uStack_68;
  ulong uStack_60;
  ulong uStack_58;
  long lStack_50;
  long lStack_48;
  
  CParameterUtility::FindPersonWithId(unsigned int)(&lStack_50,param_2);
  if (lStack_50 == 0) goto code_r0x01f16330;
  uStack_60 = 0;
  uStack_58 = 0;
  uStack_68 = 0;
  void CParameterPropertyBase<78u>::CryptString<string >(string&, string const&)(&uStack_68,lStack_50 + 0x68);
  uStack_78 = 0;
  psStack_70 = (short *)0x0;
  uVar2 = (ulong)&uStack_68 | 1;
  uVar1 = uStack_68 >> 1 & 0x7f;
  if ((uStack_68 & 1) != 0) {
    uVar2 = uStack_58;
    uVar1 = uStack_60;
  }
  if (1 < uVar1) {
    uVar1 = 2;
  }
  uStack_80 = 0;
  if (uVar1 < 0x17) {
    psVar6 = (short *)((ulong)&uStack_80 | 1);
    uStack_80 = (uVar1 & 0x7f) << 1;
    if (uVar1 != 0) goto code_r0x01f16234;
  }
  else {
    psVar6 = (short *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x10,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (psVar6 == (short *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_80 = 0x11;
    uStack_78 = uVar1;
    psStack_70 = psVar6;
code_r0x01f16234:
    memcpy(psVar6,uVar2,uVar1);
  }
  uVar3 = uStack_80;
  *(undefined1 *)((long)psVar6 + uVar1) = 0;
  uVar2 = uStack_80 >> 1 & 0x7f;
  if ((uStack_80 & 1) != 0) {
    uVar2 = uStack_78;
  }
  if (uVar2 == 2) {
    psVar6 = (short *)((ulong)&uStack_80 | 1);
    if ((uStack_80 & 1) != 0) {
      psVar6 = psStack_70;
    }
    if (*psVar6 != 0x7063) {
      psVar6 = (short *)((ulong)&uStack_80 | 1);
      if ((uStack_80 & 1) != 0) {
        psVar6 = psStack_70;
      }
      if (*psVar6 != 0x6363) {
        psVar6 = (short *)((ulong)&uStack_80 | 1);
        if ((uStack_80 & 1) != 0) {
          psVar6 = psStack_70;
        }
        if (*psVar6 != 0x6d63) goto code_r0x01f162c8;
      }
    }
    if (param_3 < 0x28) {
      if (param_3 < 0x1e) {
        if (0x13 < param_3) {
          iVar4 = 0x7d2;
          goto code_r0x01f16308;
        }
        iVar5 = 0x7d1;
      }
      else {
        iVar5 = 0x7d2;
      }
    }
    else {
      iVar5 = 0x7d3;
    }
    iVar4 = Aska::Random(unsigned int)(2);
    iVar4 = iVar4 + iVar5;
  }
  else {
code_r0x01f162c8:
    iVar4 = 0x7d1;
  }
code_r0x01f16308:
  CUIVoiceManager::AddPlayUpVoice(unsigned int, unsigned int)(param_1,param_2,iVar4);
  if ((uVar3 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(psStack_70);
  }
  if ((uStack_68 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_58);
  }
code_r0x01f16330:
  if (lStack_48 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return;
}

// ==== CUIVoiceManager::PlayLimitOverVoice(unsigned int)
// vaddr 0x1e1635c | ghidra 0x1f1635c | size 456 | symbol _ZN15CUIVoiceManager18PlayLimitOverVoiceEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager18PlayLimitOverVoiceEj(undefined8 param_1,undefined4 param_2)

{
  ulong uVar1;
  ulong uVar2;
  undefined4 uVar3;
  ulong uVar4;
  undefined4 uVar5;
  short *psVar6;
  ulong uStack_70;
  ulong uStack_68;
  short *psStack_60;
  ulong uStack_58;
  ulong uStack_50;
  ulong uStack_48;
  long lStack_40;
  long lStack_38;
  
  CParameterUtility::FindPersonWithId(unsigned int)(&lStack_40,param_2);
  if (lStack_40 == 0) goto code_r0x01f16504;
  uVar3 = *(undefined4 *)(lStack_40 + 0x38);
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_58 = 0;
  void CParameterPropertyBase<78u>::CryptString<string >(string&, string const&)(&uStack_58,lStack_40 + 0x68);
  uStack_68 = 0;
  psStack_60 = (short *)0x0;
  uVar2 = (ulong)&uStack_58 | 1;
  uVar1 = uStack_58 >> 1 & 0x7f;
  if ((uStack_58 & 1) != 0) {
    uVar2 = uStack_48;
    uVar1 = uStack_50;
  }
  if (1 < uVar1) {
    uVar1 = 2;
  }
  uStack_70 = 0;
  if (uVar1 < 0x17) {
    psVar6 = (short *)((ulong)&uStack_70 | 1);
    uStack_70 = (uVar1 & 0x7f) << 1;
    if (uVar1 != 0) goto code_r0x01f16430;
  }
  else {
    psVar6 = (short *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x10,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (psVar6 == (short *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_70 = 0x11;
    uStack_68 = uVar1;
    psStack_60 = psVar6;
code_r0x01f16430:
    memcpy(psVar6,uVar2,uVar1);
  }
  uVar4 = uStack_70;
  *(undefined1 *)((long)psVar6 + uVar1) = 0;
  uVar2 = uStack_70 >> 1 & 0x7f;
  if ((uStack_70 & 1) != 0) {
    uVar2 = uStack_68;
  }
  if (uVar2 == 2) {
    psVar6 = (short *)((ulong)&uStack_70 | 1);
    if ((uStack_70 & 1) != 0) {
      psVar6 = psStack_60;
    }
    if (*psVar6 == 0x7063) {
      uVar5 = 0x7d5;
    }
    else {
      uVar5 = 0x7d5;
      psVar6 = (short *)((ulong)&uStack_70 | 1);
      if ((uStack_70 & 1) != 0) {
        psVar6 = psStack_60;
      }
      if (*psVar6 != 0x6363) {
        psVar6 = (short *)((ulong)&uStack_70 | 1);
        if ((uStack_70 & 1) != 0) {
          psVar6 = psStack_60;
        }
        uVar5 = 0x7d5;
        if (*psVar6 != 0x6d63) {
          uVar5 = 0x7d1;
        }
      }
    }
  }
  else {
    uVar5 = 0x7d1;
  }
  CUIVoiceManager::AddPlayUpVoice(unsigned int, unsigned int)(param_1,uVar3,uVar5);
  if ((uVar4 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(psStack_60);
  }
  if ((uStack_58 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_48);
  }
code_r0x01f16504:
  if (lStack_38 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return;
}

// ==== CUIVoiceManager::GetLevelUpCueID(unsigned int)
// vaddr 0x1e1671c | ghidra 0x1f1671c | size 80 | symbol _ZN15CUIVoiceManager15GetLevelUpCueIDEj | lib libSOA-3.7.0.so | 2026-10-08
int _ZN15CUIVoiceManager15GetLevelUpCueIDEj(undefined8 param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2 < 0x28) {
    if (param_2 < 0x1e) {
      if (0x13 < param_2) {
        return 0x7d2;
      }
      iVar2 = 0x7d1;
    }
    else {
      iVar2 = 0x7d2;
    }
  }
  else {
    iVar2 = 0x7d3;
  }
  iVar1 = Aska::Random(unsigned int)(2);
  return iVar1 + iVar2;
}

// ==== CUIVoiceManager::AddPlayUpVoice(unsigned int, unsigned int)
// vaddr 0x1e1676c | ghidra 0x1f1676c | size 392 | symbol _ZN15CUIVoiceManager14AddPlayUpVoiceEjj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager14AddPlayUpVoiceEjj(long param_1,undefined8 param_2,undefined4 param_3)

{
  ulong *puVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uStack_78;
  ulong uStack_70;
  ulong uStack_68;
  ulong uStack_60;
  ulong uStack_58;
  ulong uStack_50;
  undefined4 uStack_48;
  
  uStack_58 = 0;
  uStack_50 = 0;
  uStack_60 = 0;
  CUIVoiceManager::GetMenuVoicePackName(unsigned int)(&uStack_78);
  uStack_60 = uStack_60 & 0xffffffffffff0000;
  string::reserve(unsigned long)(&uStack_60,0);
  uStack_50 = uStack_68;
  uStack_58 = uStack_70;
  uStack_60 = uStack_78;
  puVar1 = *(ulong **)(param_1 + 0x10);
  uStack_48 = param_3;
  if (puVar1 == *(ulong **)(param_1 + 0x18)) {
    void std::__ndk1::vector<CUIVoiceManager::UpVoiceData, Framework::CSTLAllocator<CUIVoiceManager::UpVoiceData, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<CUIVoiceManager::UpVoiceData const&>(CUIVoiceManager::UpVoiceData const&)(param_1 + 8,&uStack_60);
    goto joined_r0x01f16818;
  }
  if (puVar1 == (ulong *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  uVar3 = uStack_50;
  uVar2 = uStack_58;
  puVar1[1] = 0;
  puVar1[2] = 0;
  *puVar1 = 0;
  if ((uStack_60 & 1) == 0) {
    puVar1[2] = uStack_50;
    puVar1[1] = uStack_58;
    *puVar1 = uStack_60;
  }
  else {
    if (uStack_58 < 0x17) {
      uVar4 = (long)puVar1 + 1;
      *(char *)puVar1 = (char)(uStack_58 << 1);
      if (uStack_58 != 0) goto code_r0x01f168a4;
    }
    else {
      uVar5 = uStack_58 + 0x10 & 0xfffffffffffffff0;
      if (uVar5 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar4 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar5,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar4 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      puVar1[1] = uVar2;
      puVar1[2] = uVar4;
      *puVar1 = uVar5 | 1;
code_r0x01f168a4:
      memcpy(uVar4,uVar3,uVar2);
    }
    *(undefined1 *)(uVar4 + uVar2) = 0;
  }
  *(undefined4 *)(puVar1 + 3) = uStack_48;
  *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + 0x20;
joined_r0x01f16818:
  if ((uStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_50);
  }
  return;
}

// ==== CUIVoiceManager::StopPlayBattlePack(unsigned int)
// vaddr 0x1e168f4 | ghidra 0x1f168f4 | size 64 | symbol _ZN15CUIVoiceManager18StopPlayBattlePackEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager18StopPlayBattlePackEj(undefined8 param_1)

{
  byte abStack_28 [16];
  undefined8 uStack_18;
  
  CUIVoiceManager::GetBattleVoicePackName(unsigned int)(abStack_28);
  CUIVoiceManager::StopPlayPack(string const&, float)(0x40000000,param_1,abStack_28);
  if ((abStack_28[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_18);
  }
  return;
}

// ==== CUIVoiceManager::StopPlayPack(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, float)
// vaddr 0x1e16934 | ghidra 0x1f16934 | size 716 | symbol _ZN15CUIVoiceManager12StopPlayPackERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN15CUIVoiceManager12StopPlayPackERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEEf
               (float param_1,long param_2,byte *param_3)

{
  ulong uVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  byte *pbVar5;
  undefined8 uVar6;
  byte *pbVar7;
  ulong uVar8;
  byte *pbVar9;
  long lVar10;
  ulong uVar11;
  byte *pbVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  
  bVar2 = *param_3;
  uVar8 = *(ulong *)(param_3 + 8);
  uVar11 = (ulong)(bVar2 >> 1);
  if ((bVar2 & 1) != 0) {
    uVar11 = uVar8;
  }
  if (uVar11 != 0) {
    pbVar12 = *(byte **)(param_2 + 8);
    pbVar7 = *(byte **)(param_2 + 0x10);
    if (pbVar7 != pbVar12) {
      do {
        bVar3 = *pbVar12;
        uVar11 = (ulong)(bVar3 >> 1);
        if ((bVar3 & 1) != 0) {
          uVar11 = *(ulong *)(pbVar12 + 8);
        }
        uVar1 = (ulong)(bVar2 >> 1);
        if ((bVar2 & 1) != 0) {
          uVar1 = uVar8;
        }
        if (uVar11 == uVar1) {
          pbVar9 = *(byte **)(pbVar12 + 0x10);
          if ((bVar3 & 1) == 0) {
            pbVar9 = pbVar12 + 1;
          }
          pbVar5 = param_3 + 1;
          if ((bVar2 & 1) != 0) {
            pbVar5 = *(byte **)(param_3 + 0x10);
          }
          if ((bVar3 & 1) == 0) {
            if (uVar11 != 0) {
              lVar10 = -(ulong)(bVar3 >> 1);
              pbVar9 = pbVar12;
              do {
                pbVar9 = pbVar9 + 1;
                if (*pbVar9 != *pbVar5) goto code_r0x01f16a1c;
                lVar10 = lVar10 + 1;
                pbVar5 = pbVar5 + 1;
              } while (lVar10 != 0);
            }
          }
          else if ((uVar11 != 0) && (iVar4 = memcmp(pbVar9), iVar4 != 0))
          goto code_r0x01f16a1c;
          pbVar9 = pbVar12;
          if (pbVar12 + 0x20 == pbVar7) {
code_r0x01f16ab4:
            do {
              *(byte **)(param_2 + 0x10) = pbVar7 + -0x20;
              pbVar5 = pbVar7 + -0x20;
              if ((pbVar7[-0x20] & 1) != 0) {
                Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(pbVar7 + -0x10));
                pbVar5 = *(byte **)(param_2 + 0x10);
              }
              pbVar7 = pbVar5;
            } while (pbVar7 != pbVar9);
          }
          else {
            pbVar5 = pbVar12;
            do {
              if ((*pbVar5 & 1) == 0) {
                pbVar5[0] = 0;
                pbVar5[1] = 0;
              }
              else {
                **(undefined1 **)(pbVar5 + 0x10) = 0;
                pbVar5[8] = 0;
                pbVar5[9] = 0;
                pbVar5[10] = 0;
                pbVar5[0xb] = 0;
                pbVar5[0xc] = 0;
                pbVar5[0xd] = 0;
                pbVar5[0xe] = 0;
                pbVar5[0xf] = 0;
              }
              string::reserve(unsigned long)(pbVar5,0);
              uVar6 = *(undefined8 *)(pbVar5 + 0x30);
              uVar14 = *(undefined8 *)(pbVar5 + 0x28);
              uVar13 = *(undefined8 *)(pbVar5 + 0x20);
              pbVar9 = pbVar5 + 0x20;
              pbVar5[0x28] = 0;
              pbVar5[0x29] = 0;
              pbVar5[0x2a] = 0;
              pbVar5[0x2b] = 0;
              pbVar5[0x2c] = 0;
              pbVar5[0x2d] = 0;
              pbVar5[0x2e] = 0;
              pbVar5[0x2f] = 0;
              pbVar5[0x30] = 0;
              pbVar5[0x31] = 0;
              pbVar5[0x32] = 0;
              pbVar5[0x33] = 0;
              pbVar5[0x34] = 0;
              pbVar5[0x35] = 0;
              pbVar5[0x36] = 0;
              pbVar5[0x37] = 0;
              pbVar5[0x20] = 0;
              pbVar5[0x21] = 0;
              pbVar5[0x22] = 0;
              pbVar5[0x23] = 0;
              pbVar5[0x24] = 0;
              pbVar5[0x25] = 0;
              pbVar5[0x26] = 0;
              pbVar5[0x27] = 0;
              *(undefined8 *)(pbVar5 + 0x10) = uVar6;
              *(undefined8 *)(pbVar5 + 8) = uVar14;
              *(undefined8 *)pbVar5 = uVar13;
              *(undefined4 *)(pbVar5 + 0x18) = *(undefined4 *)(pbVar5 + 0x38);
              pbVar5 = pbVar9;
            } while (pbVar7 + -0x20 != pbVar9);
            pbVar7 = *(byte **)(param_2 + 0x10);
            if (pbVar7 != pbVar9) goto code_r0x01f16ab4;
          }
          pbVar7 = pbVar9;
          if (pbVar9 == pbVar12) break;
        }
        else {
code_r0x01f16a1c:
          pbVar12 = pbVar12 + 0x20;
          if (pbVar7 == pbVar12) break;
        }
        bVar2 = *param_3;
        uVar8 = *(ulong *)(param_3 + 8);
      } while( true );
    }
    pbVar12 = *(byte **)(param_2 + 0x20);
    pbVar7 = *(byte **)(param_2 + 0x28);
    if ((pbVar7 != pbVar12) && (pbVar7 != pbVar12)) {
      param_1 = param_1 * _UNK_027ebdd8;
      uVar6 = *(undefined8 *)PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
      do {
        bVar2 = *pbVar12;
        bVar3 = *param_3;
        uVar11 = (ulong)(bVar2 >> 1);
        if ((bVar2 & 1) != 0) {
          uVar11 = *(ulong *)(pbVar12 + 8);
        }
        uVar8 = (ulong)(bVar3 >> 1);
        if ((bVar3 & 1) != 0) {
          uVar8 = *(ulong *)(param_3 + 8);
        }
        if (uVar11 == uVar8) {
          pbVar9 = *(byte **)(pbVar12 + 0x10);
          if ((bVar2 & 1) == 0) {
            pbVar9 = pbVar12 + 1;
          }
          pbVar5 = param_3 + 1;
          if ((bVar3 & 1) != 0) {
            pbVar5 = *(byte **)(param_3 + 0x10);
          }
          if ((bVar2 & 1) == 0) {
            if (uVar11 != 0) {
              uVar11 = 0;
              do {
                if (pbVar12[uVar11 + 1] != pbVar5[uVar11]) goto code_r0x01f16bdc;
                uVar11 = uVar11 + 1;
              } while (bVar2 >> 1 != uVar11);
            }
          }
          else if ((uVar11 != 0) && (iVar4 = memcmp(pbVar9), iVar4 != 0))
          goto code_r0x01f16bdc;
          lVar10 = *(long *)(pbVar12 + 0x18);
          if (lVar10 != *(long *)(pbVar12 + 0x20)) {
            do {
              uVar11 = CSoundManager::IsPlaying(unsigned long) const(uVar6,*(undefined8 *)(lVar10 + 8));
              if ((uVar11 & 1) != 0) {
                CSoundManager::Stop(unsigned long, std::__ndk1::chrono::duration<float, std::__ndk1::ratio<1l, 1000l> >)(param_1 / 3.0,uVar6,*(undefined8 *)(lVar10 + 8));
              }
              lVar10 = lVar10 + 0x10;
            } while (lVar10 != *(long *)(pbVar12 + 0x20));
            pbVar7 = *(byte **)(param_2 + 0x28);
          }
        }
code_r0x01f16bdc:
        pbVar12 = pbVar12 + 0x30;
      } while (pbVar12 != pbVar7);
    }
  }
  return;
}

// ==== CUIVoiceManager::AddResourcePackMenu(unsigned int)
// vaddr 0x1e16c00 | ghidra 0x1f16c00 | size 60 | symbol _ZN15CUIVoiceManager19AddResourcePackMenuEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager19AddResourcePackMenuEj(undefined8 param_1)

{
  byte abStack_28 [16];
  undefined8 uStack_18;
  
  CUIVoiceManager::GetMenuVoicePackName(unsigned int)(abStack_28);
  CUIVoiceManager::AddResourcePack(string const&)(param_1,abStack_28);
  if ((abStack_28[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_18);
  }
  return;
}

// ==== CUIVoiceManager::AddResourcePack(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1e16c3c | ghidra 0x1f16c3c | size 412 | symbol _ZN15CUIVoiceManager15AddResourcePackERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager15AddResourcePackERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE
               (long param_1,byte *param_2)

{
  ulong uVar1;
  byte *pbVar2;
  ulong uVar3;
  byte bVar4;
  byte bVar5;
  int iVar6;
  byte *pbVar7;
  undefined8 uVar8;
  long lVar9;
  byte *pbVar10;
  byte *pbVar11;
  byte *pbVar12;
  byte *pbVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  
  bVar4 = *param_2;
  uVar1 = (ulong)(bVar4 >> 1);
  if ((bVar4 & 1) != 0) {
    uVar1 = *(ulong *)(param_2 + 8);
  }
  if (uVar1 == 0) {
    return;
  }
  pbVar11 = *(byte **)(param_1 + 0x38);
  pbVar12 = *(byte **)(param_1 + 0x40);
  pbVar13 = *(byte **)(param_2 + 0x10);
  if (pbVar12 != pbVar11) {
    pbVar2 = param_2 + 1;
    if ((bVar4 & 1) != 0) {
      pbVar2 = pbVar13;
    }
    do {
      bVar5 = *pbVar11;
      uVar3 = (ulong)(bVar5 >> 1);
      if ((bVar5 & 1) != 0) {
        uVar3 = *(ulong *)(pbVar11 + 8);
      }
      if (uVar3 == uVar1) {
        if ((bVar5 & 1) == 0) {
          lVar9 = -(ulong)(bVar5 >> 1);
          pbVar10 = pbVar2;
          pbVar7 = pbVar11;
          while (pbVar7 = pbVar7 + 1, *pbVar7 == *pbVar10) {
            lVar9 = lVar9 + 1;
            pbVar10 = pbVar10 + 1;
            if (lVar9 == 0) goto code_r0x01f16d28;
          }
        }
        else {
          iVar6 = memcmp(*(undefined8 *)(pbVar11 + 0x10),pbVar2,uVar1);
          if (iVar6 == 0) {
code_r0x01f16d28:
            if (pbVar11 + 0x18 != pbVar12) {
              pbVar13 = pbVar11;
              do {
                if ((*pbVar13 & 1) == 0) {
                  pbVar13[0] = 0;
                  pbVar13[1] = 0;
                }
                else {
                  **(undefined1 **)(pbVar13 + 0x10) = 0;
                  pbVar13[8] = 0;
                  pbVar13[9] = 0;
                  pbVar13[10] = 0;
                  pbVar13[0xb] = 0;
                  pbVar13[0xc] = 0;
                  pbVar13[0xd] = 0;
                  pbVar13[0xe] = 0;
                  pbVar13[0xf] = 0;
                }
                string::reserve(unsigned long)(pbVar13,0);
                uVar8 = *(undefined8 *)(pbVar13 + 0x28);
                uVar15 = *(undefined8 *)(pbVar13 + 0x20);
                uVar14 = *(undefined8 *)(pbVar13 + 0x18);
                pbVar11 = pbVar13 + 0x18;
                pbVar13[0x20] = 0;
                pbVar13[0x21] = 0;
                pbVar13[0x22] = 0;
                pbVar13[0x23] = 0;
                pbVar13[0x24] = 0;
                pbVar13[0x25] = 0;
                pbVar13[0x26] = 0;
                pbVar13[0x27] = 0;
                pbVar13[0x28] = 0;
                pbVar13[0x29] = 0;
                pbVar13[0x2a] = 0;
                pbVar13[0x2b] = 0;
                pbVar13[0x2c] = 0;
                pbVar13[0x2d] = 0;
                pbVar13[0x2e] = 0;
                pbVar13[0x2f] = 0;
                *(undefined8 *)(pbVar13 + 0x10) = uVar8;
                pbVar13[0x18] = 0;
                pbVar13[0x19] = 0;
                pbVar13[0x1a] = 0;
                pbVar13[0x1b] = 0;
                pbVar13[0x1c] = 0;
                pbVar13[0x1d] = 0;
                pbVar13[0x1e] = 0;
                pbVar13[0x1f] = 0;
                *(undefined8 *)(pbVar13 + 8) = uVar15;
                *(undefined8 *)pbVar13 = uVar14;
                pbVar13 = pbVar11;
              } while (pbVar12 + -0x18 != pbVar11);
              pbVar12 = *(byte **)(param_1 + 0x40);
              if (*(byte **)(param_1 + 0x40) == pbVar11) {
                return;
              }
            }
            do {
              pbVar13 = pbVar12 + -0x18;
              *(byte **)(param_1 + 0x40) = pbVar13;
              if ((pbVar12[-0x18] & 1) != 0) {
                Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(pbVar12 + -8));
                pbVar13 = *(byte **)(param_1 + 0x40);
              }
              pbVar12 = pbVar13;
            } while (pbVar13 != pbVar11);
            return;
          }
        }
      }
      pbVar11 = pbVar11 + 0x18;
    } while (pbVar12 != pbVar11);
  }
  pbVar11 = param_2 + 1;
  if ((bVar4 & 1) != 0) {
    pbVar11 = pbVar13;
  }
  (*(code *)PTR__ZN13CSoundManager11AddResourceEPKcb_02c91528)
            (*(undefined8 *)PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358,
             pbVar11,0);
  return;
}

// ==== CUIVoiceManager::AddResourcePackBattle(unsigned int)
// vaddr 0x1e16dd8 | ghidra 0x1f16dd8 | size 60 | symbol _ZN15CUIVoiceManager21AddResourcePackBattleEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager21AddResourcePackBattleEj(undefined8 param_1)

{
  byte abStack_28 [16];
  undefined8 uStack_18;
  
  CUIVoiceManager::GetBattleVoicePackName(unsigned int)(abStack_28);
  CUIVoiceManager::AddResourcePack(string const&)(param_1,abStack_28);
  if ((abStack_28[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_18);
  }
  return;
}

// ==== CUIVoiceManager::AddResourcePackHome(unsigned int)
// vaddr 0x1e16e14 | ghidra 0x1f16e14 | size 112 | symbol _ZN15CUIVoiceManager19AddResourcePackHomeEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager19AddResourcePackHomeEj(undefined8 param_1,undefined4 param_2)

{
  undefined8 uVar1;
  byte abStack_38 [16];
  undefined8 uStack_28;
  
  CUIVoiceManager::GetHomeVoicePackName(unsigned int)(abStack_38);
  uVar1 = CUIVoiceManager::AddResourcePack(string const&)(param_1,abStack_38);
  if ((abStack_38[0] & 1) != 0) {
    uVar1 = Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
  }
  CUIVoiceManager::GetHomeVoicePackSubName(unsigned int)(abStack_38,uVar1,param_2);
  CUIVoiceManager::AddResourcePack(string const&)(param_1,abStack_38);
  if ((abStack_38[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
  }
  return;
}

// ==== CUIVoiceManager::RemoveResourcePackMenu(unsigned int)
// vaddr 0x1e16e84 | ghidra 0x1f16e84 | size 60 | symbol _ZN15CUIVoiceManager22RemoveResourcePackMenuEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager22RemoveResourcePackMenuEj(undefined8 param_1)

{
  byte abStack_28 [16];
  undefined8 uStack_18;
  
  CUIVoiceManager::GetMenuVoicePackName(unsigned int)(abStack_28);
  CUIVoiceManager::RemoveResourcePack(string const&)(param_1,abStack_28);
  if ((abStack_28[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_18);
  }
  return;
}

// ==== CUIVoiceManager::RemoveResourcePack(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1e16ec0 | ghidra 0x1f16ec0 | size 356 | symbol _ZN15CUIVoiceManager18RemoveResourcePackERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager18RemoveResourcePackERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE
               (long param_1,ulong *param_2)

{
  ulong *puVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  
  uVar5 = (ulong)(byte)((byte)*param_2 >> 1);
  if (((byte)*param_2 & 1) != 0) {
    uVar5 = param_2[1];
  }
  if (uVar5 == 0) {
    return;
  }
  CUIVoiceManager::StopPlayPack(string const&, float)(0x41200000,param_1,param_2);
  puVar1 = *(ulong **)(param_1 + 0x40);
  if (puVar1 == *(ulong **)(param_1 + 0x48)) {
    (*(code *)
      PTR__ZNSt6__ndk16vectorINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEENS5_IS8_NS4_22CSTLVectorAllocatorInfEEEE21__push_back_slow_pathIRKS8_EEvOT__02c8e530
    )(param_1 + 0x38,param_2);
    return;
  }
  if (puVar1 == (ulong *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  puVar1[1] = 0;
  puVar1[2] = 0;
  *puVar1 = 0;
  if ((*param_2 & 1) == 0) {
    puVar1[2] = param_2[2];
    uVar5 = *param_2;
    puVar1[1] = param_2[1];
    *puVar1 = uVar5;
    goto code_r0x01f17004;
  }
  uVar5 = param_2[1];
  uVar2 = param_2[2];
  if (uVar5 < 0x17) {
    uVar4 = (long)puVar1 + 1;
    *(char *)puVar1 = (char)(uVar5 << 1);
    if (uVar5 != 0) goto code_r0x01f16ff0;
  }
  else {
    uVar3 = uVar5 + 0x10 & 0xfffffffffffffff0;
    if (uVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar4 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar3,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    puVar1[1] = uVar5;
    puVar1[2] = uVar4;
    *puVar1 = uVar3 | 1;
code_r0x01f16ff0:
    memcpy(uVar4,uVar2,uVar5);
  }
  *(undefined1 *)(uVar4 + uVar5) = 0;
code_r0x01f17004:
  *(long *)(param_1 + 0x40) = *(long *)(param_1 + 0x40) + 0x18;
  return;
}

// ==== CUIVoiceManager::RemoveResourcePackBattle(unsigned int)
// vaddr 0x1e17024 | ghidra 0x1f17024 | size 60 | symbol _ZN15CUIVoiceManager24RemoveResourcePackBattleEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager24RemoveResourcePackBattleEj(undefined8 param_1)

{
  byte abStack_28 [16];
  undefined8 uStack_18;
  
  CUIVoiceManager::GetBattleVoicePackName(unsigned int)(abStack_28);
  CUIVoiceManager::RemoveResourcePack(string const&)(param_1,abStack_28);
  if ((abStack_28[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_18);
  }
  return;
}

// ==== CUIVoiceManager::RemoveResourcePackHome(unsigned int)
// vaddr 0x1e17060 | ghidra 0x1f17060 | size 112 | symbol _ZN15CUIVoiceManager22RemoveResourcePackHomeEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager22RemoveResourcePackHomeEj(undefined8 param_1,undefined4 param_2)

{
  undefined8 uVar1;
  byte abStack_38 [16];
  undefined8 uStack_28;
  
  CUIVoiceManager::GetHomeVoicePackName(unsigned int)(abStack_38);
  uVar1 = CUIVoiceManager::RemoveResourcePack(string const&)(param_1,abStack_38);
  if ((abStack_38[0] & 1) != 0) {
    uVar1 = Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
  }
  CUIVoiceManager::GetHomeVoicePackSubName(unsigned int)(abStack_38,uVar1,param_2);
  CUIVoiceManager::RemoveResourcePack(string const&)(param_1,abStack_38);
  if ((abStack_38[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
  }
  return;
}

// ==== CUIVoiceManager::IsReadyResourcePackMenu(unsigned int)
// vaddr 0x1e170d0 | ghidra 0x1f170d0 | size 164 | symbol _ZN15CUIVoiceManager23IsReadyResourcePackMenuEj | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN15CUIVoiceManager23IsReadyResourcePackMenuEj(void)

{
  undefined *puVar1;
  uint uVar2;
  ulong uVar3;
  byte abStack_38 [8];
  ulong uStack_30;
  ulong uStack_28;
  
  CUIVoiceManager::GetMenuVoicePackName(unsigned int)(abStack_38);
  puVar1 = PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
  uVar3 = (ulong)(abStack_38[0] >> 1);
  if ((abStack_38[0] & 1) != 0) {
    uVar3 = uStack_30;
  }
  if (uVar3 != 0) {
    uVar3 = (ulong)abStack_38 | 1;
    if ((abStack_38[0] & 1) != 0) {
      uVar3 = uStack_28;
    }
    uVar3 = CSoundManager::IsResourceExist(char const*)(*(undefined8 *)
                             PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358,
                            uVar3);
    if ((uVar3 & 1) != 0) {
      uVar3 = (ulong)abStack_38 | 1;
      if ((abStack_38[0] & 1) != 0) {
        uVar3 = uStack_28;
      }
      uVar2 = CSoundManager::IsReady(char const*)(*(undefined8 *)puVar1,uVar3);
      goto joined_r0x01f17154;
    }
  }
  uVar2 = 1;
joined_r0x01f17154:
  if ((abStack_38[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
  }
  return uVar2 & 1;
}

// ==== CUIVoiceManager::IsReadyResourcePackBattle(unsigned int)
// vaddr 0x1e17174 | ghidra 0x1f17174 | size 164 | symbol _ZN15CUIVoiceManager25IsReadyResourcePackBattleEj | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN15CUIVoiceManager25IsReadyResourcePackBattleEj(void)

{
  undefined *puVar1;
  uint uVar2;
  ulong uVar3;
  byte abStack_38 [8];
  ulong uStack_30;
  ulong uStack_28;
  
  CUIVoiceManager::GetBattleVoicePackName(unsigned int)(abStack_38);
  puVar1 = PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
  uVar3 = (ulong)(abStack_38[0] >> 1);
  if ((abStack_38[0] & 1) != 0) {
    uVar3 = uStack_30;
  }
  if (uVar3 != 0) {
    uVar3 = (ulong)abStack_38 | 1;
    if ((abStack_38[0] & 1) != 0) {
      uVar3 = uStack_28;
    }
    uVar3 = CSoundManager::IsResourceExist(char const*)(*(undefined8 *)
                             PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358,
                            uVar3);
    if ((uVar3 & 1) != 0) {
      uVar3 = (ulong)abStack_38 | 1;
      if ((abStack_38[0] & 1) != 0) {
        uVar3 = uStack_28;
      }
      uVar2 = CSoundManager::IsReady(char const*)(*(undefined8 *)puVar1,uVar3);
      goto joined_r0x01f171f8;
    }
  }
  uVar2 = 1;
joined_r0x01f171f8:
  if ((abStack_38[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
  }
  return uVar2 & 1;
}

// ==== CUIVoiceManager::IsReadyResourcePackHome(unsigned int)
// vaddr 0x1e17218 | ghidra 0x1f17218 | size 304 | symbol _ZN15CUIVoiceManager23IsReadyResourcePackHomeEj | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN15CUIVoiceManager23IsReadyResourcePackHomeEj(undefined8 param_1,undefined4 param_2)

{
  undefined *puVar1;
  uint uVar2;
  ulong uVar3;
  ulong uVar4;
  byte abStack_50 [8];
  ulong uStack_48;
  ulong uStack_40;
  byte abStack_38 [8];
  ulong uStack_30;
  ulong uStack_28;
  
  uVar3 = CUIVoiceManager::GetHomeVoicePackName(unsigned int)(abStack_38);
  puVar1 = PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
  uVar4 = (ulong)(abStack_38[0] >> 1);
  if ((abStack_38[0] & 1) != 0) {
    uVar4 = uStack_30;
  }
  if (uVar4 != 0) {
    uVar4 = (ulong)abStack_38 | 1;
    if ((abStack_38[0] & 1) != 0) {
      uVar4 = uStack_28;
    }
    uVar3 = CSoundManager::IsResourceExist(char const*)(*(undefined8 *)
                             PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358,
                            uVar4);
    if ((uVar3 & 1) != 0) {
      uVar4 = (ulong)abStack_38 | 1;
      if ((abStack_38[0] & 1) != 0) {
        uVar4 = uStack_28;
      }
      uVar3 = CSoundManager::IsReady(char const*)(*(undefined8 *)puVar1,uVar4);
      if ((uVar3 & 1) == 0) {
        uVar2 = 0;
        goto joined_r0x01f17318;
      }
    }
  }
  CUIVoiceManager::GetHomeVoicePackSubName(unsigned int)(abStack_50,uVar3,param_2);
  puVar1 = PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
  uVar4 = (ulong)(abStack_50[0] >> 1);
  if ((abStack_50[0] & 1) != 0) {
    uVar4 = uStack_48;
  }
  if (uVar4 == 0) {
code_r0x01f17300:
    uVar2 = 1;
  }
  else {
    uVar4 = (ulong)abStack_50 | 1;
    if ((abStack_50[0] & 1) != 0) {
      uVar4 = uStack_40;
    }
    uVar4 = CSoundManager::IsResourceExist(char const*)(*(undefined8 *)
                             PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358,
                            uVar4);
    if ((uVar4 & 1) == 0) goto code_r0x01f17300;
    uVar4 = (ulong)abStack_50 | 1;
    if ((abStack_50[0] & 1) != 0) {
      uVar4 = uStack_40;
    }
    uVar2 = CSoundManager::IsReady(char const*)(*(undefined8 *)puVar1,uVar4);
  }
  if ((abStack_50[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_40);
  }
joined_r0x01f17318:
  if ((abStack_38[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_28);
  }
  return uVar2 & 1;
}

// ==== CUIVoiceManager::AddResource(CUIVoiceManager::MenuID, CUIVoiceManager::MenuVoiceCharacterType)
// vaddr 0x1e17348 | ghidra 0x1f17348 | size 108 | symbol _ZN15CUIVoiceManager11AddResourceENS_6MenuIDENS_22MenuVoiceCharacterTypeE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager11AddResourceENS_6MenuIDENS_22MenuVoiceCharacterTypeE
               (undefined8 param_1,int param_2,undefined4 param_3)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (0x11 < param_2 - 1U) {
    return;
  }
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  uVar3 = CUIManager::rMenuVoiceManager()(lVar2);
  (*(code *)PTR__ZN17CMenuVoiceManager25AddResourcePackFromMenuIDEjj_02cb1918)
            (uVar3,param_2,param_3);
  return;
}

// ==== CUIVoiceManager::RemoveResource(CUIVoiceManager::MenuID, CUIVoiceManager::MenuVoiceCharacterType)
// vaddr 0x1e173b4 | ghidra 0x1f173b4 | size 108 | symbol _ZN15CUIVoiceManager14RemoveResourceENS_6MenuIDENS_22MenuVoiceCharacterTypeE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager14RemoveResourceENS_6MenuIDENS_22MenuVoiceCharacterTypeE
               (undefined8 param_1,int param_2,undefined4 param_3)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (0x11 < param_2 - 1U) {
    return;
  }
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  uVar3 = CUIManager::rMenuVoiceManager()(lVar2);
  (*(code *)PTR__ZN17CMenuVoiceManager18RemoveResourcePackEjj_02c96d38)(uVar3,param_2,param_3);
  return;
}

// ==== CUIVoiceManager::RequestStop(CUIVoiceManager::MenuID, CUIVoiceManager::MenuVoiceCharacterType)
// vaddr 0x1e17420 | ghidra 0x1f17420 | size 108 | symbol _ZN15CUIVoiceManager11RequestStopENS_6MenuIDENS_22MenuVoiceCharacterTypeE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager11RequestStopENS_6MenuIDENS_22MenuVoiceCharacterTypeE
               (undefined8 param_1,int param_2,undefined4 param_3)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (0x11 < param_2 - 1U) {
    return;
  }
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  uVar3 = CUIManager::rMenuVoiceManager()(lVar2);
  (*(code *)PTR__ZN17CMenuVoiceManager11RequestStopEjj_02cb6540)(uVar3,param_2,param_3);
  return;
}

// ==== CUIVoiceManager::IsReadyResource(CUIVoiceManager::MenuID, CUIVoiceManager::MenuVoiceCharacterType)
// vaddr 0x1e1748c | ghidra 0x1f1748c | size 84 | symbol _ZN15CUIVoiceManager15IsReadyResourceENS_6MenuIDENS_22MenuVoiceCharacterTypeE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager15IsReadyResourceENS_6MenuIDENS_22MenuVoiceCharacterTypeE
               (undefined8 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  uVar3 = CUIManager::rMenuVoiceManager()(lVar2);
  (*(code *)PTR__ZN17CMenuVoiceManager15IsReadyResourceEjj_02c962d0)(uVar3,param_2,param_3);
  return;
}

// ==== CUIVoiceManager::IsExistRemoveResource()
// vaddr 0x1e174e0 | ghidra 0x1f174e0 | size 60 | symbol _ZN15CUIVoiceManager21IsExistRemoveResourceEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager21IsExistRemoveResourceEv(void)

{
  undefined *puVar1;
  long lVar2;
  
  puVar1 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  CUIManager::rMenuVoiceManager()(lVar2);
  (*(code *)PTR__ZN17CMenuVoiceManager21IsExistRemoveResourceEv_02ca9f98)();
  return;
}

// ==== CUIVoiceManager::GetEventMissionPackList(Framework::CSTLVector<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >&)
// vaddr 0x1e1751c | ghidra 0x1f1751c | size 1236 | symbol _ZN15CUIVoiceManager23GetEventMissionPackListERN9Framework10CSTLVectorINSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager23GetEventMissionPackListERN9Framework10CSTLVectorINSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEEEE
               (undefined8 param_1,byte **param_2)

{
  ulong uVar1;
  ulong uVar2;
  ulong *puVar3;
  ulong uVar4;
  byte *pbVar5;
  undefined *puVar6;
  int iVar7;
  byte *pbVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  byte *pbVar12;
  byte bVar13;
  byte *pbVar14;
  ulong uVar15;
  long lVar16;
  long lVar17;
  undefined8 uVar18;
  byte bStack_c8;
  undefined7 uStack_c7;
  ulong uStack_c0;
  ulong uStack_b8;
  ulong uStack_b0;
  ulong uStack_a8;
  ulong uStack_a0;
  byte abStack_90 [8];
  ulong uStack_88;
  ulong uStack_80;
  byte *pbStack_78;
  byte *pbStack_70;
  undefined8 uStack_68;
  
  pbStack_70 = (byte *)0x0;
  uStack_68 = 0;
  pbStack_78 = (byte *)0x0;
  CUIUtility::CollectMasterAreaVoicePackName(Framework::CSTLVector<string >&)(&pbStack_78);
  void std::__ndk1::__sort<std::__ndk1::__less<string, string >&, string*>(string*, string*, std::__ndk1::__less<string, string >&)(pbStack_78,pbStack_70,abStack_90);
  pbVar8 = (byte *)std::__ndk1::__wrap_iter<string*> std::__ndk1::unique<std::__ndk1::__wrap_iter<string*>, std::__ndk1::__equal_to<string, string > >(std::__ndk1::__wrap_iter<string*>, std::__ndk1::__wrap_iter<string*>, std::__ndk1::__equal_to<string, string >)(pbStack_78,pbStack_70);
  if (pbVar8 != pbStack_70) {
    pbVar12 = pbStack_70;
    pbVar14 = pbVar8;
    if (pbVar8 + ((long)pbStack_70 - (long)pbVar8) != pbStack_70) {
      lVar16 = ((long)pbStack_70 - (long)pbVar8 >> 3) * 8;
      lVar17 = lVar16 - (long)pbStack_70;
      do {
        if ((*pbVar8 & 1) == 0) {
          pbVar8[0] = 0;
          pbVar8[1] = 0;
        }
        else {
          **(undefined1 **)(pbVar8 + 0x10) = 0;
          pbVar8[8] = 0;
          pbVar8[9] = 0;
          pbVar8[10] = 0;
          pbVar8[0xb] = 0;
          pbVar8[0xc] = 0;
          pbVar8[0xd] = 0;
          pbVar8[0xe] = 0;
          pbVar8[0xf] = 0;
        }
        string::reserve(unsigned long)(pbVar8,0);
        pbVar12 = pbVar8 + lVar16;
        *(undefined8 *)(pbVar8 + 0x10) = *(undefined8 *)(pbVar12 + 0x10);
        uVar18 = *(undefined8 *)pbVar12;
        pbVar14 = pbVar8 + 0x18;
        *(undefined8 *)(pbVar8 + 8) = *(undefined8 *)(pbVar12 + 8);
        *(undefined8 *)pbVar8 = uVar18;
        pbVar12[8] = 0;
        pbVar12[9] = 0;
        pbVar12[10] = 0;
        pbVar12[0xb] = 0;
        pbVar12[0xc] = 0;
        pbVar12[0xd] = 0;
        pbVar12[0xe] = 0;
        pbVar12[0xf] = 0;
        pbVar12[0x10] = 0;
        pbVar12[0x11] = 0;
        pbVar12[0x12] = 0;
        pbVar12[0x13] = 0;
        pbVar12[0x14] = 0;
        pbVar12[0x15] = 0;
        pbVar12[0x16] = 0;
        pbVar12[0x17] = 0;
        pbVar12[0] = 0;
        pbVar12[1] = 0;
        pbVar12[2] = 0;
        pbVar12[3] = 0;
        pbVar12[4] = 0;
        pbVar12[5] = 0;
        pbVar12[6] = 0;
        pbVar12[7] = 0;
        pbVar8 = pbVar14;
        pbVar12 = pbStack_70;
      } while (pbVar14 + lVar17 != (byte *)0x0);
    }
    while (pbVar5 = pbStack_70, pbVar8 = pbVar12, pbStack_70 = pbVar5, pbVar5 != pbVar14) {
      pbStack_70 = pbVar5 + -0x18;
      pbVar12 = pbVar14;
      if ((pbVar5[-0x18] & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(pbVar5 + -8));
      }
    }
  }
  if (&pbStack_78 != param_2) {
    std::__ndk1::enable_if<__is_forward_iterator<string*>::value&&is_constructible<string, std::__ndk1::iterator_traits<string*>::reference>::value, void>::type std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::assign<string*>(string*, string*)(param_2,pbStack_78,pbVar8);
  }
  CUIUtility::GetMascot()(abStack_90);
  bVar13 = abStack_90[0];
  uVar15 = (ulong)(abStack_90[0] >> 1);
  if ((abStack_90[0] & 1) != 0) {
    uVar15 = uStack_88;
  }
  if (uVar15 == 6) {
    uVar15 = (ulong)abStack_90 | 1;
    if ((abStack_90[0] & 1) != 0) {
      uVar15 = uStack_80;
    }
    iVar7 = memcmp(uVar15,&UNK_028b06f4/*"cp0003"*/,6);
    if (iVar7 == 0) goto code_r0x01f1797c;
  }
  puVar6 = PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
  pbVar8 = *param_2;
  pbVar12 = param_2[1];
  lVar16 = (long)pbVar12 - (long)pbVar8;
  if (lVar16 != 0) {
    lVar17 = 0;
    uVar15 = 1;
    do {
      uVar10 = ((long)pbVar12 - (long)pbVar8 >> 3) * -0x5555555555555555;
      if (uVar10 < uVar15 - 1 || uVar10 - (uVar15 - 1) == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/);
        pbVar8 = *param_2;
      }
      string std::__ndk1::operator+<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >(string const&, char const*)(&bStack_c8,pbVar8 + lVar17,&UNK_029e43f2/*"_"*/);
      uVar11 = (ulong)bStack_c8;
      uVar10 = (ulong)(abStack_90[0] >> 1);
      uVar4 = (ulong)abStack_90 | 1;
      if ((abStack_90[0] & 1) != 0) {
        uVar10 = uStack_88;
        uVar4 = uStack_80;
      }
      if ((bStack_c8 & 1) == 0) {
        lVar9 = 0x16;
      }
      else {
        uVar11 = CONCAT71(uStack_c7,bStack_c8);
        lVar9 = (uVar11 & 0xfffffffffffffffe) - 1;
      }
      uVar1 = (ulong)(((uint)uVar11 & 0xfe) >> 1);
      if ((uVar11 & 1) != 0) {
        uVar1 = uStack_c0;
      }
      if (lVar9 - uVar1 < uVar10) {
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_c8,lVar9,(uVar10 - lVar9) + uVar1,uVar1,uVar1,0,uVar10);
      }
      else if (uVar10 != 0) {
        uVar2 = (ulong)&bStack_c8 | 1;
        if ((uVar11 & 1) != 0) {
          uVar2 = uStack_b8;
        }
        memcpy(uVar2 + uVar1,uVar4,uVar10);
        uVar1 = uVar1 + uVar10;
        uVar10 = uVar1;
        if ((bStack_c8 & 1) == 0) {
          bStack_c8 = (char)uVar1 * '\x02';
          uVar10 = uStack_c0;
        }
        uStack_c0 = uVar10;
        *(undefined1 *)(uVar2 + uVar1) = 0;
      }
      uStack_b0 = CONCAT71(uStack_c7,bStack_c8);
      uStack_a8 = uStack_c0;
      uStack_a0 = uStack_b8;
      uVar10 = (ulong)&uStack_b0 | 1;
      if ((bStack_c8 & 1) != 0) {
        uVar10 = uStack_b8;
      }
      uVar10 = CSoundManager::IsResourceExist(char const*)(*(undefined8 *)puVar6,uVar10);
      if ((uVar10 & 1) != 0) {
        puVar3 = (ulong *)param_2[1];
        if (puVar3 == (ulong *)param_2[2]) {
          void std::__ndk1::vector<string, Framework::CSTLAllocator<string, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<string const&>(string const&)(param_2,&uStack_b0);
        }
        else {
          if (puVar3 == (ulong *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          uVar4 = uStack_a0;
          uVar10 = uStack_a8;
          puVar3[1] = 0;
          puVar3[2] = 0;
          *puVar3 = 0;
          if ((uStack_b0 & 1) == 0) {
            puVar3[2] = uStack_a0;
            puVar3[1] = uStack_a8;
            *puVar3 = uStack_b0;
          }
          else {
            if (uStack_a8 < 0x17) {
              pbVar8 = (byte *)((long)puVar3 + 1);
              *(byte *)puVar3 = (byte)(uStack_a8 << 1);
              if (uStack_a8 != 0) goto code_r0x01f1792c;
            }
            else {
              uVar11 = uStack_a8 + 0x10 & 0xfffffffffffffff0;
              if (uVar11 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
              }
              pbVar8 = (byte *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
              if (pbVar8 == (byte *)0x0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
              }
              puVar3[1] = uVar10;
              puVar3[2] = (ulong)pbVar8;
              *puVar3 = uVar11 | 1;
code_r0x01f1792c:
              memcpy(pbVar8,uVar4,uVar10);
            }
            pbVar8[uVar10] = 0;
          }
          param_2[1] = param_2[1] + 0x18;
        }
      }
      if ((uStack_b0 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_a0);
      }
      bVar13 = abStack_90[0];
      if ((ulong)((lVar16 >> 3) * -0x5555555555555555) <= uVar15) break;
      pbVar8 = *param_2;
      pbVar12 = param_2[1];
      uVar15 = uVar15 + 1;
      lVar17 = lVar17 + 0x18;
    } while( true );
  }
code_r0x01f1797c:
  if ((bVar13 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_80);
  }
  pbVar8 = pbStack_78;
  if (pbStack_78 != (byte *)0x0) {
    while (pbVar12 = pbStack_70, pbVar12 != pbVar8) {
      pbStack_70 = pbVar12 + -0x18;
      if ((pbVar12[-0x18] & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(pbVar12 + -8));
      }
    }
    pbStack_70 = pbVar12;
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pbStack_78);
  }
  return;
}

// ==== CUIVoiceManager::AddEventMissionPackList(Framework::CSTLVector<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > > const&)
// vaddr 0x1e179f0 | ghidra 0x1f179f0 | size 120 | symbol _ZN15CUIVoiceManager23AddEventMissionPackListERKN9Framework10CSTLVectorINSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager23AddEventMissionPackListERKN9Framework10CSTLVectorINSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEEEE
               (undefined8 param_1,long *param_2)

{
  byte bVar1;
  byte *pbVar2;
  undefined8 uVar3;
  byte *pbVar4;
  
  pbVar4 = (byte *)*param_2;
  pbVar2 = (byte *)param_2[1];
  if (pbVar4 != pbVar2) {
    uVar3 = *(undefined8 *)PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
    do {
      bVar1 = *pbVar4;
      if ((bVar1 & 1) == 0) {
        if (bVar1 >> 1 != 0) {
code_r0x01f17a24:
          if ((bVar1 & 1) == 0) {
            pbVar2 = pbVar4 + 1;
          }
          else {
            pbVar2 = *(byte **)(pbVar4 + 0x10);
          }
          CSoundManager::AddResource(char const*, bool)(uVar3,pbVar2,0);
          pbVar2 = (byte *)param_2[1];
        }
      }
      else if (*(long *)(pbVar4 + 8) != 0) goto code_r0x01f17a24;
      pbVar4 = pbVar4 + 0x18;
    } while (pbVar4 != pbVar2);
  }
  return;
}

// ==== CUIVoiceManager::RemoveResourceEventMissionPackList(Framework::CSTLVector<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > > const&)
// vaddr 0x1e17a68 | ghidra 0x1f17a68 | size 96 | symbol _ZN15CUIVoiceManager34RemoveResourceEventMissionPackListERKN9Framework10CSTLVectorINSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager34RemoveResourceEventMissionPackListERKN9Framework10CSTLVectorINSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEEEE
               (undefined8 param_1,long *param_2)

{
  byte *pbVar1;
  byte *pbVar2;
  
  pbVar2 = (byte *)*param_2;
  pbVar1 = (byte *)param_2[1];
  if (pbVar2 != pbVar1) {
    do {
      if ((*pbVar2 & 1) == 0) {
        if (*pbVar2 >> 1 != 0) {
code_r0x01f17aa0:
          CUIVoiceManager::RemoveResourcePack(string const&)(param_1,pbVar2);
          pbVar1 = (byte *)param_2[1];
        }
      }
      else if (*(long *)(pbVar2 + 8) != 0) goto code_r0x01f17aa0;
      pbVar2 = pbVar2 + 0x18;
    } while (pbVar2 != pbVar1);
  }
  return;
}

// ==== CUIVoiceManager::IsReadyResourceEventMissionPackList(Framework::CSTLVector<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > > const&)
// vaddr 0x1e17ac8 | ghidra 0x1f17ac8 | size 176 | symbol _ZN15CUIVoiceManager35IsReadyResourceEventMissionPackListERKN9Framework10CSTLVectorINSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEEEE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN15CUIVoiceManager35IsReadyResourceEventMissionPackListERKN9Framework10CSTLVectorINSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEEEE
          (undefined8 param_1,long *param_2)

{
  byte bVar1;
  undefined *puVar2;
  ulong uVar3;
  byte *pbVar4;
  byte *pbVar5;
  
  puVar2 = PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358;
  pbVar5 = (byte *)*param_2;
  if (pbVar5 != (byte *)param_2[1]) {
    do {
      bVar1 = *pbVar5;
      if ((bVar1 & 1) == 0) {
        if (bVar1 >> 1 != 0) {
code_r0x01f17b04:
          uVar3 = (ulong)(bVar1 >> 1);
          if ((bVar1 & 1) != 0) {
            uVar3 = *(ulong *)(pbVar5 + 8);
          }
          if (uVar3 != 0) {
            pbVar4 = *(byte **)(pbVar5 + 0x10);
            if ((bVar1 & 1) == 0) {
              pbVar4 = pbVar5 + 1;
            }
            uVar3 = CSoundManager::IsResourceExist(char const*)(*(undefined8 *)puVar2,pbVar4);
            if ((uVar3 & 1) != 0) {
              pbVar4 = pbVar5 + 1;
              if ((*pbVar5 & 1) != 0) {
                pbVar4 = *(byte **)(pbVar5 + 0x10);
              }
              uVar3 = CSoundManager::IsReady(char const*)(*(undefined8 *)puVar2,pbVar4);
              if ((uVar3 & 1) == 0) {
                return 0;
              }
            }
          }
        }
      }
      else if (*(long *)(pbVar5 + 8) != 0) goto code_r0x01f17b04;
      pbVar5 = pbVar5 + 0x18;
    } while (pbVar5 != (byte *)param_2[1]);
  }
  return 1;
}

// ==== CUIVoiceManager::StopPlayPackEventMissionList(Framework::CSTLVector<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > > const&)
// vaddr 0x1e17b78 | ghidra 0x1f17b78 | size 84 | symbol _ZN15CUIVoiceManager28StopPlayPackEventMissionListERKN9Framework10CSTLVectorINSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEEEE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager28StopPlayPackEventMissionListERKN9Framework10CSTLVectorINSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS0_13CSTLAllocatorIcNS0_22CSTLStringAllocatorInfEEEEEEE
               (undefined8 param_1,long *param_2)

{
  long lVar1;
  
  lVar1 = *param_2;
  if (lVar1 != param_2[1]) {
    do {
      CUIVoiceManager::StopPlayPack(string const&, float)(0x41a00000,param_1,lVar1);
      lVar1 = lVar1 + 0x18;
    } while (lVar1 != param_2[1]);
  }
  return;
}

// ==== CUIVoiceManager::PlayEventMissionMenu(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, unsigned int, unsigned int)
// vaddr 0x1e17bcc | ghidra 0x1f17bcc | size 1492 | symbol _ZN15CUIVoiceManager20PlayEventMissionMenuERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEEjj | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

void _ZN15CUIVoiceManager20PlayEventMissionMenuERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEEjj
               (long param_1,byte *param_2,undefined4 param_3,uint param_4)

{
  ulong uVar1;
  ulong *puVar2;
  byte *pbVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  undefined8 uVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  ulong uVar13;
  byte bStack_a8;
  undefined7 uStack_a7;
  ulong uStack_a0;
  ulong uStack_98;
  ulong uStack_90;
  ulong uStack_88;
  ulong uStack_80;
  ulong uStack_78;
  ulong uStack_70;
  ulong uStack_68;
  undefined8 uStack_60;
  ulong uStack_58;
  ulong uStack_50;
  uint uStack_48;
  
  uVar10 = (ulong)(*param_2 >> 1);
  if ((*param_2 & 1) != 0) {
    uVar10 = *(ulong *)(param_2 + 8);
  }
  if (uVar10 == 0) {
    return;
  }
  uVar5 = Aska::Random(int, int)(param_3,param_4 + 1);
  if (param_4 < uVar5) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029588d8/*"C:\BAS_Submission\Client\Project\..\Source\Game\UI\UIVoiceManager.cpp"*/,0x107,&UNK_0295891e/*"over range"*/);
  }
  if (*(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0 == 0) {
    return;
  }
  lVar7 = CParameterManager::pParameterSound() const();
  if (lVar7 == 0) {
    return;
  }
  uStack_58 = 0;
  uStack_50 = 0;
  uStack_60 = 0;
  if ((byte *)&uStack_60 != param_2) {
    uVar10 = *(ulong *)(param_2 + 8);
    pbVar3 = *(byte **)(param_2 + 0x10);
    if ((*param_2 & 1) == 0) {
      pbVar3 = param_2 + 1;
      uVar10 = (ulong)(*param_2 >> 1);
    }
    if (uVar10 < 0x16 || uVar10 - 0x16 == 0) {
      if (uVar10 != 0) {
        memmove((ulong)&uStack_60 | 1,pbVar3,uVar10);
      }
      *(undefined1 *)((long)&uStack_60 + uVar10 + 1) = 0;
      uStack_60 = CONCAT71(uStack_60._1_7_,(char)(uVar10 << 1));
    }
    else {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_60,0x16,uVar10 - 0x16,0,0,0,uVar10);
    }
  }
  uStack_48 = uVar5;
  CUIUtility::GetMascot()(&uStack_78);
  uVar13 = uStack_78;
  uVar10 = uStack_78 >> 1 & 0x7f;
  if ((uStack_78 & 1) != 0) {
    uVar10 = uStack_70;
  }
  if (uVar10 == 6) {
    uVar10 = (ulong)&uStack_78 | 1;
    if ((uStack_78 & 1) != 0) {
      uVar10 = uStack_68;
    }
    iVar6 = memcmp(uVar10,&UNK_028b06f4/*"cp0003"*/,6);
    if (iVar6 != 0) goto code_r0x01f17d30;
    bVar4 = 0;
  }
  else {
code_r0x01f17d30:
    string std::__ndk1::operator+<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >(string const&, char const*)(&bStack_a8,param_2,&UNK_029e43f2/*"_"*/);
    uVar12 = (ulong)bStack_a8;
    uVar10 = uStack_78 >> 1 & 0x7f;
    uVar13 = (ulong)&uStack_78 | 1;
    if ((uStack_78 & 1) != 0) {
      uVar10 = uStack_70;
      uVar13 = uStack_68;
    }
    if ((bStack_a8 & 1) == 0) {
      lVar8 = 0x16;
    }
    else {
      uVar12 = CONCAT71(uStack_a7,bStack_a8);
      lVar8 = (uVar12 & 0xfffffffffffffffe) - 1;
    }
    uVar11 = (ulong)(((uint)uVar12 & 0xfe) >> 1);
    if ((uVar12 & 1) != 0) {
      uVar11 = uStack_a0;
    }
    if (lVar8 - uVar11 < uVar10) {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&bStack_a8,lVar8,(uVar10 - lVar8) + uVar11,uVar11,uVar11,0,uVar10);
    }
    else if (uVar10 != 0) {
      uVar1 = (ulong)&bStack_a8 | 1;
      if ((uVar12 & 1) != 0) {
        uVar1 = uStack_98;
      }
      memcpy(uVar1 + uVar11,uVar13,uVar10);
      uVar11 = uVar11 + uVar10;
      uVar10 = uVar11;
      if ((bStack_a8 & 1) == 0) {
        bStack_a8 = (char)uVar11 * '\x02';
        uVar10 = uStack_a0;
      }
      uStack_a0 = uVar10;
      *(undefined1 *)(uVar1 + uVar11) = 0;
    }
    uStack_90 = CONCAT71(uStack_a7,bStack_a8);
    uStack_88 = uStack_a0;
    uStack_80 = uStack_98;
    uVar10 = (ulong)&uStack_90 | 1;
    if ((bStack_a8 & 1) != 0) {
      uVar10 = uStack_98;
    }
    uVar10 = CSoundManager::IsResourceExist(char const*)(*(undefined8 *)
                              PTR__ZN9Framework10TSingletonI13CSoundManagerE11m_pInstanceE_02cb7358,
                             uVar10);
    if ((uVar10 & 1) == 0) {
      bVar4 = 0;
    }
    else {
      uVar10 = uStack_90 >> 1 & 0x7f;
      uVar13 = (ulong)&uStack_90 | 1;
      if ((uStack_90 & 1) != 0) {
        uVar10 = uStack_88;
        uVar13 = uStack_80;
      }
      if ((uStack_60 & 1) == 0) {
        uVar11 = 0x16;
        lVar8 = uVar10 - 0x16;
        uVar12 = uStack_60 & 0xff;
        if (0x15 < uVar10 && lVar8 != 0) goto code_r0x01f17ecc;
code_r0x01f17e68:
        uVar11 = (ulong)&uStack_60 | 1;
        if ((uVar12 & 1) != 0) {
          uVar11 = uStack_50;
        }
        if (uVar10 != 0) {
          memmove(uVar11,uVar13,uVar10);
        }
        *(undefined1 *)(uVar11 + uVar10) = 0;
        if ((uStack_60 & 1) == 0) {
          uStack_60 = CONCAT71(uStack_60._1_7_,(char)(uVar10 << 1));
          uVar10 = uStack_58;
        }
      }
      else {
        uVar11 = (uStack_60 & 0xfffffffffffffffe) - 1;
        lVar8 = uVar10 - uVar11;
        uVar12 = uStack_60;
        if (uVar10 < uVar11 || lVar8 == 0) goto code_r0x01f17e68;
code_r0x01f17ecc:
        uVar13 = (ulong)(((uint)uVar12 & 0xfe) >> 1);
        if ((uVar12 & 1) != 0) {
          uVar13 = uStack_58;
        }
        string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_60,uVar11,lVar8,uVar13,0,uVar13,uVar10);
        uVar10 = uStack_58;
      }
      uStack_58 = uVar10;
      bVar4 = 1;
    }
    uVar13 = uStack_78;
    if ((uStack_90 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_80);
      uVar13 = uStack_78;
    }
  }
  if ((uVar13 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
  }
  uVar13 = (ulong)&uStack_60 | 1;
  uVar10 = uVar13;
  if ((uStack_60 & 1) != 0) {
    uVar10 = uStack_50;
  }
  lVar8 = CParameterSound::pParameter(char const*, unsigned int) const(lVar7,uVar10,uVar5);
  if ((lVar8 == 0) && (!(bool)(bVar4 ^ 1))) {
    uVar10 = uStack_58;
    if ((byte *)&uStack_60 != param_2) {
      uVar10 = *(ulong *)(param_2 + 8);
      pbVar3 = *(byte **)(param_2 + 0x10);
      if ((*param_2 & 1) == 0) {
        pbVar3 = param_2 + 1;
        uVar10 = (ulong)(*param_2 >> 1);
      }
      if ((uStack_60 & 1) == 0) {
        uVar11 = 0x16;
        lVar8 = uVar10 - 0x16;
        uVar12 = uStack_60 & 0xff;
        if (0x15 < uVar10 && lVar8 != 0) {
code_r0x01f17fd4:
          uVar1 = (ulong)(((uint)uVar12 & 0xfe) >> 1);
          if ((uVar12 & 1) != 0) {
            uVar1 = uStack_58;
          }
          string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_60,uVar11,lVar8,uVar1,0,uVar1,uVar10);
          uVar10 = uStack_58;
          goto code_r0x01f18004;
        }
      }
      else {
        uVar11 = (uStack_60 & 0xfffffffffffffffe) - 1;
        lVar8 = uVar10 - uVar11;
        uVar12 = uStack_60;
        if (uVar11 <= uVar10 && lVar8 != 0) goto code_r0x01f17fd4;
      }
      uVar11 = uVar13;
      if ((uVar12 & 1) != 0) {
        uVar11 = uStack_50;
      }
      if (uVar10 != 0) {
        memmove(uVar11,pbVar3,uVar10);
      }
      *(undefined1 *)(uVar11 + uVar10) = 0;
      if ((uStack_60 & 1) == 0) {
        uStack_60 = CONCAT71(uStack_60._1_7_,(char)(uVar10 << 1));
        uVar10 = uStack_58;
      }
    }
code_r0x01f18004:
    uStack_58 = uVar10;
    if ((uStack_60 & 1) != 0) {
      uVar13 = uStack_50;
    }
    lVar8 = CParameterSound::pParameter(char const*, unsigned int) const(lVar7,uVar13,uVar5);
  }
  if (lVar8 != 0) {
    uStack_70 = 0;
    uStack_68 = 0;
    uStack_78 = 0;
    uVar9 = void CParameterPropertyBase<31u>::CryptString<string >(string&, string const&)(&uStack_78,lVar8 + 0x38);
    uVar10 = CUIVoiceManager::IsSystemSettingMenuVoiceEnable(string const&)(uVar9,&uStack_78);
    if ((uStack_78 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_68);
    }
    if ((uVar10 & 1) == 0) goto joined_r0x01f180e0;
  }
  puVar2 = *(ulong **)(param_1 + 0x10);
  if (puVar2 == *(ulong **)(param_1 + 0x18)) {
    void std::__ndk1::vector<CUIVoiceManager::UpVoiceData, Framework::CSTLAllocator<CUIVoiceManager::UpVoiceData, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<CUIVoiceManager::UpVoiceData const&>(CUIVoiceManager::UpVoiceData const&)(param_1 + 8,&uStack_60);
    goto joined_r0x01f180e0;
  }
  if (puVar2 == (ulong *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  uVar13 = uStack_50;
  uVar10 = uStack_58;
  puVar2[1] = 0;
  puVar2[2] = 0;
  *puVar2 = 0;
  if ((uStack_60 & 1) == 0) {
    puVar2[2] = uStack_50;
    puVar2[1] = uStack_58;
    *puVar2 = uStack_60;
  }
  else {
    if (uStack_58 < 0x17) {
      uVar11 = (long)puVar2 + 1;
      *(char *)puVar2 = (char)(uStack_58 << 1);
      if (uStack_58 != 0) goto code_r0x01f1816c;
    }
    else {
      uVar12 = uStack_58 + 0x10 & 0xfffffffffffffff0;
      if (uVar12 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar11 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar12,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar11 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      puVar2[1] = uVar10;
      puVar2[2] = uVar11;
      *puVar2 = uVar12 | 1;
code_r0x01f1816c:
      memcpy(uVar11,uVar13,uVar10);
    }
    *(undefined1 *)(uVar11 + uVar10) = 0;
  }
  *(uint *)(puVar2 + 3) = uStack_48;
  *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + 0x20;
joined_r0x01f180e0:
  if ((uStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_50);
  }
  return;
}

// ==== CUIVoiceManager::AddStampSE(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&, unsigned int)
// vaddr 0x1e181a0 | ghidra 0x1f181a0 | size 472 | symbol _ZN15CUIVoiceManager10AddStampSEERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager10AddStampSEERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEEj
               (long param_1,byte *param_2,undefined4 param_3)

{
  ulong uVar1;
  ulong *puVar2;
  byte *pbVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  undefined8 uStack_60;
  ulong uStack_58;
  ulong uStack_50;
  undefined4 uStack_48;
  
  uStack_58 = 0;
  uStack_50 = 0;
  uStack_60 = 0;
  if ((byte *)&uStack_60 != param_2) {
    uVar1 = *(ulong *)(param_2 + 8);
    pbVar3 = *(byte **)(param_2 + 0x10);
    if ((*param_2 & 1) == 0) {
      pbVar3 = param_2 + 1;
      uVar1 = (ulong)(*param_2 >> 1);
    }
    if (uVar1 < 0x16 || uVar1 - 0x16 == 0) {
      if (uVar1 != 0) {
        memmove((ulong)&uStack_60 | 1,pbVar3,uVar1);
      }
      *(undefined1 *)((long)&uStack_60 + uVar1 + 1) = 0;
      uStack_60 = CONCAT71(uStack_60._1_7_,(char)(uVar1 << 1));
    }
    else {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_60,0x16,uVar1 - 0x16,0,0,0,uVar1);
    }
  }
  puVar2 = *(ulong **)(param_1 + 0x10);
  uStack_48 = param_3;
  if (puVar2 == *(ulong **)(param_1 + 0x18)) {
    void std::__ndk1::vector<CUIVoiceManager::UpVoiceData, Framework::CSTLAllocator<CUIVoiceManager::UpVoiceData, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<CUIVoiceManager::UpVoiceData const&>(CUIVoiceManager::UpVoiceData const&)(param_1 + 8,&uStack_60);
    goto joined_r0x01f1829c;
  }
  if (puVar2 == (ulong *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  uVar4 = uStack_50;
  uVar1 = uStack_58;
  puVar2[1] = 0;
  puVar2[2] = 0;
  *puVar2 = 0;
  if ((uStack_60 & 1) == 0) {
    puVar2[2] = uStack_50;
    puVar2[1] = uStack_58;
    *puVar2 = uStack_60;
  }
  else {
    if (uStack_58 < 0x17) {
      uVar5 = (long)puVar2 + 1;
      *(char *)puVar2 = (char)(uStack_58 << 1);
      if (uStack_58 != 0) goto code_r0x01f18328;
    }
    else {
      uVar6 = uStack_58 + 0x10 & 0xfffffffffffffff0;
      if (uVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      uVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (uVar5 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      puVar2[1] = uVar1;
      puVar2[2] = uVar5;
      *puVar2 = uVar6 | 1;
code_r0x01f18328:
      memcpy(uVar5,uVar4,uVar1);
    }
    *(undefined1 *)(uVar5 + uVar1) = 0;
  }
  *(undefined4 *)(puVar2 + 3) = uStack_48;
  *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + 0x20;
joined_r0x01f1829c:
  if ((uStack_60 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_50);
  }
  return;
}

// ==== CUIVoiceManager::IsPlayingStampSE(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x1e18378 | ghidra 0x1f18378 | size 780 | symbol _ZN15CUIVoiceManager16IsPlayingStampSEERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN15CUIVoiceManager16IsPlayingStampSEERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE
          (long param_1,byte *param_2)

{
  ulong uVar1;
  ulong uVar2;
  ulong *puVar3;
  long lVar4;
  byte bVar5;
  bool bVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  ulong uVar10;
  long lVar11;
  ulong uVar12;
  long lVar13;
  byte *pbVar14;
  ulong *puVar15;
  ulong uStack_90;
  ulong uStack_88;
  byte *pbStack_80;
  undefined4 uStack_78;
  undefined4 uStack_74;
  long lStack_70;
  
  puVar15 = *(ulong **)(param_1 + 8);
  puVar3 = *(ulong **)(param_1 + 0x10);
  if (puVar15 != puVar3) {
    pbVar14 = (byte *)((ulong)&uStack_90 | 1);
    do {
      uStack_88 = 0;
      pbStack_80 = (byte *)0x0;
      uStack_90 = 0;
      if ((*puVar15 & 1) == 0) {
        pbStack_80 = (byte *)puVar15[2];
        uStack_88 = puVar15[1];
        uStack_90 = *puVar15;
      }
      else {
        uVar2 = puVar15[1];
        uVar12 = puVar15[2];
        if (uVar2 < 0x17) {
          uStack_90 = (uVar2 & 0x7f) << 1;
          pbVar8 = pbVar14;
          if (uVar2 != 0) goto code_r0x01f18460;
        }
        else {
          uVar10 = uVar2 + 0x10 & 0xfffffffffffffff0;
          if (uVar10 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          pbVar8 = (byte *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar10,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (pbVar8 == (byte *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uStack_90 = uVar10 | 1;
          uStack_88 = uVar2;
          pbStack_80 = pbVar8;
code_r0x01f18460:
          memcpy(pbVar8,uVar12,uVar2);
        }
        pbVar8[uVar2] = 0;
      }
      uStack_78 = (undefined4)puVar15[3];
      bVar5 = *param_2;
      uVar12 = uStack_90 >> 1 & 0x7f;
      uVar2 = uVar12;
      if ((uStack_90 & 1) != 0) {
        uVar2 = uStack_88;
      }
      uVar10 = (ulong)(bVar5 >> 1);
      if ((bVar5 & 1) != 0) {
        uVar10 = *(ulong *)(param_2 + 8);
      }
      if (uVar2 == uVar10) {
        pbVar8 = pbVar14;
        if ((uStack_90 & 1) != 0) {
          pbVar8 = pbStack_80;
        }
        pbVar9 = param_2 + 1;
        if ((bVar5 & 1) != 0) {
          pbVar9 = *(byte **)(param_2 + 0x10);
        }
        if ((uStack_90 & 1) == 0) {
          if (uVar2 == 0) {
            return 1;
          }
          lVar13 = -uVar12;
          pbVar8 = pbVar14;
          do {
            if (*pbVar8 != *pbVar9) goto code_r0x01f18500;
            pbVar8 = pbVar8 + 1;
            lVar13 = lVar13 + 1;
            pbVar9 = pbVar9 + 1;
          } while (lVar13 != 0);
          bVar6 = true;
          if ((uStack_90 & 1) == 0) goto code_r0x01f1852c;
        }
        else if ((uVar2 == 0) || (iVar7 = memcmp(pbVar8), iVar7 == 0)) {
          bVar6 = true;
        }
        else {
          bVar6 = false;
        }
code_r0x01f18524:
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pbStack_80);
      }
      else {
code_r0x01f18500:
        bVar6 = false;
        if ((uStack_90 & 1) != 0) goto code_r0x01f18524;
      }
code_r0x01f1852c:
      if (bVar6) {
        return 1;
      }
      puVar15 = puVar15 + 4;
    } while (puVar15 != puVar3);
  }
  lVar13 = *(long *)(param_1 + 0x20);
  lVar4 = *(long *)(param_1 + 0x28);
  if (lVar13 != lVar4) {
    do {
      CUIVoiceManager::UpVoicePlayingData::UpVoicePlayingData(CUIVoiceManager::UpVoicePlayingData const&)(&uStack_90,lVar13);
      uVar12 = uStack_90;
      bVar5 = *param_2;
      uVar10 = uStack_90 >> 1 & 0x7f;
      uVar2 = uVar10;
      if ((uStack_90 & 1) != 0) {
        uVar2 = uStack_88;
      }
      uVar1 = (ulong)(bVar5 >> 1);
      if ((bVar5 & 1) != 0) {
        uVar1 = *(ulong *)(param_2 + 8);
      }
      if (uVar2 == uVar1) {
        pbVar14 = (byte *)((ulong)&uStack_90 | 1);
        if ((uStack_90 & 1) != 0) {
          pbVar14 = pbStack_80;
        }
        pbVar8 = param_2 + 1;
        if ((bVar5 & 1) != 0) {
          pbVar8 = *(byte **)(param_2 + 0x10);
        }
        if ((uStack_90 & 1) == 0) {
          if (uVar2 != 0) {
            lVar11 = -uVar10;
            pbVar14 = (byte *)((ulong)&uStack_90 | 1);
            do {
              if (*pbVar14 != *pbVar8) goto code_r0x01f1863c;
              pbVar14 = pbVar14 + 1;
              lVar11 = lVar11 + 1;
              pbVar8 = pbVar8 + 1;
            } while (lVar11 != 0);
          }
        }
        else if ((uVar2 != 0) && (iVar7 = memcmp(pbVar14), iVar7 != 0))
        goto code_r0x01f1863c;
        bVar6 = true;
        lVar11 = CONCAT44(uStack_74,uStack_78);
      }
      else {
code_r0x01f1863c:
        bVar6 = false;
        lVar11 = CONCAT44(uStack_74,uStack_78);
      }
      if (lVar11 != 0) {
        if (lStack_70 != lVar11) {
          lStack_70 = lStack_70 + (~((lStack_70 + -0x10) - lVar11) & 0xfffffffffffffff0U);
        }
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
        uVar12 = uStack_90;
      }
      if ((uVar12 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(pbStack_80);
      }
      if (bVar6) {
        return 1;
      }
      lVar13 = lVar13 + 0x30;
    } while (lVar13 != lVar4);
  }
  return 0;
}

// ==== CUIVoiceManager::UpVoicePlayingData::UpVoicePlayingData(CUIVoiceManager::UpVoicePlayingData const&)
// vaddr 0x1e18684 | ghidra 0x1f18684 | size 392 | symbol _ZN15CUIVoiceManager18UpVoicePlayingDataC2ERKS0_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN15CUIVoiceManager18UpVoicePlayingDataC2ERKS0_(ulong *param_1,ulong *param_2)

{
  ulong uVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  long lVar4;
  ulong uVar5;
  undefined8 *puVar6;
  ulong uVar7;
  ulong uVar8;
  undefined8 uVar9;
  
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  if ((*param_2 & 1) == 0) {
    param_1[2] = param_2[2];
    uVar8 = *param_2;
    param_1[1] = param_2[1];
    *param_1 = uVar8;
    goto code_r0x01f18758;
  }
  uVar8 = param_2[1];
  uVar1 = param_2[2];
  if (uVar8 < 0x17) {
    uVar5 = (long)param_1 + 1;
    *(char *)param_1 = (char)(uVar8 << 1);
    if (uVar8 != 0) goto code_r0x01f18744;
  }
  else {
    uVar7 = uVar8 + 0x10 & 0xfffffffffffffff0;
    if (uVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar7,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[1] = uVar8;
    param_1[2] = uVar5;
    *param_1 = uVar7 | 1;
code_r0x01f18744:
    memcpy(uVar5,uVar1,uVar8);
  }
  *(undefined1 *)(uVar5 + uVar8) = 0;
code_r0x01f18758:
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[3] = 0;
  lVar4 = (long)(param_2[4] - param_2[3]) >> 4;
  if (lVar4 != 0) {
    puVar3 = (undefined8 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(param_2[4] - param_2[3],&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
    if (puVar3 == (undefined8 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    param_1[3] = (ulong)puVar3;
    param_1[4] = (ulong)puVar3;
    param_1[5] = (ulong)(puVar3 + lVar4 * 2);
    puVar2 = (undefined8 *)param_2[4];
    for (puVar6 = (undefined8 *)param_2[3]; puVar6 != puVar2; puVar6 = puVar6 + 2) {
      if (puVar3 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      uVar9 = *puVar6;
      puVar3[1] = puVar6[1];
      *puVar3 = uVar9;
      puVar3 = (undefined8 *)(param_1[4] + 0x10);
      param_1[4] = (ulong)puVar3;
    }
  }
  return;
}

// ==== CUIVoiceDataCache::Load(CUIVoiceManager::MenuID, CUIVoiceManager::MenuVoiceCharacterType)
// vaddr 0x1e18954 | ghidra 0x1f18954 | size 340 | symbol _ZN17CUIVoiceDataCache4LoadEN15CUIVoiceManager6MenuIDENS0_22MenuVoiceCharacterTypeE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN17CUIVoiceDataCache4LoadEN15CUIVoiceManager6MenuIDENS0_22MenuVoiceCharacterTypeE
               (int *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  long lVar4;
  undefined8 uVar5;
  
  puVar3 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if ((*param_1 != param_2) || (param_1[1] != param_3)) {
    if ((*param_1 != 0) && (param_1[1] != 0)) {
      lVar4 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
      if (lVar4 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar4 = *(long *)puVar3;
      }
      CUIManager::rUIVoiceManager()(lVar4);
      iVar1 = *param_1;
      if (iVar1 - 1U < 0x12) {
        lVar4 = *(long *)puVar3;
        iVar2 = param_1[1];
        if (lVar4 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar4 = *(long *)puVar3;
        }
        uVar5 = CUIManager::rMenuVoiceManager()(lVar4);
        CMenuVoiceManager::RemoveResourcePack(unsigned int, unsigned int)(uVar5,iVar1,iVar2);
      }
      param_1[0] = 0;
      param_1[1] = 0;
    }
    *param_1 = param_2;
    param_1[1] = param_3;
    puVar3 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
    lVar4 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
    if (lVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar4 = *(long *)puVar3;
    }
    CUIManager::rUIVoiceManager()(lVar4);
    if (param_2 - 1U < 0x12) {
      lVar4 = *(long *)puVar3;
      if (lVar4 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar4 = *(long *)puVar3;
      }
      uVar5 = CUIManager::rMenuVoiceManager()(lVar4);
      (*(code *)PTR__ZN17CMenuVoiceManager25AddResourcePackFromMenuIDEjj_02cb1918)
                (uVar5,param_2,param_3);
      return;
    }
  }
  return;
}

// ==== void std::__ndk1::vector<CUIVoiceManager::UpVoicePlayingData::PlayUnit, Framework::CSTLAllocator<CUIVoiceManager::UpVoicePlayingData::PlayUnit, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<CUIVoiceManager::UpVoicePlayingData::PlayUnit const&>(CUIVoiceManager::UpVoicePlayingData::PlayUnit const&)
// vaddr 0x1e19c24 | ghidra 0x1f19c24 | size 292 | symbol _ZNSt6__ndk16vectorIN15CUIVoiceManager18UpVoicePlayingData8PlayUnitEN9Framework13CSTLAllocatorIS3_NS4_22CSTLVectorAllocatorInfEEEE21__push_back_slow_pathIRKS3_EEvOT_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk16vectorIN15CUIVoiceManager18UpVoicePlayingData8PlayUnitEN9Framework13CSTLAllocatorIS3_NS4_22CSTLVectorAllocatorInfEEEE21__push_back_slow_pathIRKS3_EEvOT_
               (long *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  undefined8 *puVar8;
  undefined8 uVar9;
  
  lVar3 = param_1[2] - *param_1;
  lVar7 = param_1[1] - *param_1 >> 4;
  if ((ulong)(lVar3 >> 4) < 0x7ffffffffffffff) {
    uVar4 = lVar3 >> 3;
    uVar6 = lVar7 + 1U;
    if (lVar7 + 1U <= uVar4) {
      uVar6 = uVar4;
    }
    if (uVar6 == 0) {
      lVar3 = 0;
      puVar8 = (undefined8 *)(lVar7 << 4);
      goto joined_r0x01f19d40;
    }
  }
  else {
    uVar6 = 0xfffffffffffffff;
  }
  lVar3 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6 << 4,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    puVar8 = (undefined8 *)(lVar7 * 0x10);
  }
  else {
    puVar8 = (undefined8 *)(lVar3 + lVar7 * 0x10);
  }
joined_r0x01f19d40:
  if (puVar8 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  uVar9 = *param_2;
  puVar1 = puVar8 + 2;
  puVar8[1] = param_2[1];
  *puVar8 = uVar9;
  lVar7 = *param_1;
  lVar5 = param_1[1];
  if (lVar5 != lVar7) {
    do {
      puVar2 = (undefined8 *)(lVar5 + -8);
      uVar9 = *(undefined8 *)(lVar5 + -0x10);
      lVar5 = lVar5 + -0x10;
      puVar8[-1] = *puVar2;
      puVar8[-2] = uVar9;
      puVar8 = puVar8 + -2;
    } while (lVar7 != lVar5);
    lVar7 = *param_1;
  }
  *param_1 = (long)puVar8;
  param_1[1] = (long)puVar1;
  param_1[2] = lVar3 + uVar6 * 0x10;
  if (lVar7 != 0) {
    (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)();
    return;
  }
  return;
}

// ==== void std::__ndk1::vector<CUIVoiceManager::UpVoicePlayingData, Framework::CSTLAllocator<CUIVoiceManager::UpVoicePlayingData, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<CUIVoiceManager::UpVoicePlayingData const&>(CUIVoiceManager::UpVoicePlayingData const&)
// vaddr 0x1e19d48 | ghidra 0x1f19d48 | size 428 | symbol _ZNSt6__ndk16vectorIN15CUIVoiceManager18UpVoicePlayingDataEN9Framework13CSTLAllocatorIS2_NS3_22CSTLVectorAllocatorInfEEEE21__push_back_slow_pathIRKS2_EEvOT_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x01f19ea0: Changing call to branch */

void _ZNSt6__ndk16vectorIN15CUIVoiceManager18UpVoicePlayingDataEN9Framework13CSTLAllocatorIS2_NS3_22CSTLVectorAllocatorInfEEEE21__push_back_slow_pathIRKS2_EEvOT_
               (long *param_1,undefined8 param_2)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  
  lVar1 = param_1[2] - *param_1 >> 4;
  lVar4 = param_1[1] - *param_1 >> 4;
  if ((ulong)(lVar1 * -0x5555555555555555) < 0x2aaaaaaaaaaaaaa) {
    uVar8 = lVar4 * -0x5555555555555555 + 1;
    uVar2 = lVar1 * 0x5555555555555556;
    if (uVar8 <= uVar2) {
      uVar8 = uVar2;
    }
    if (uVar8 == 0) {
      lVar1 = 0;
      goto code_r0x01f19df8;
    }
  }
  else {
    uVar8 = 0x555555555555555;
  }
  lVar1 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar8 * 0x30,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
code_r0x01f19df8:
  lVar4 = lVar1 + lVar4 * 0x10;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  CUIVoiceManager::UpVoicePlayingData::UpVoicePlayingData(CUIVoiceManager::UpVoicePlayingData const&)(lVar4,param_2);
  lVar6 = *param_1;
  lVar5 = param_1[1];
  lVar3 = lVar4 + 0x30;
  lVar7 = lVar6;
  if (lVar5 != lVar6) {
    do {
      lVar5 = lVar5 + -0x30;
      CUIVoiceManager::UpVoicePlayingData::UpVoicePlayingData(CUIVoiceManager::UpVoicePlayingData const&)(lVar4 + -0x30,lVar5);
      lVar4 = lVar4 + -0x30;
    } while (lVar6 != lVar5);
    lVar6 = *param_1;
    lVar7 = param_1[1];
  }
  *param_1 = lVar4;
  param_1[1] = lVar3;
  param_1[2] = lVar1 + uVar8 * 0x30;
  do {
    lVar1 = lVar7;
    if (lVar1 == lVar6) {
      lVar4 = lVar6;
      if (lVar6 == 0) {
        return;
      }
code_r0x011d23a0:
      (*(code *)PTR__ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv_02ca11c0)(lVar4);
      return;
    }
    lVar4 = *(long *)(lVar1 + -0x18);
    if (lVar4 != 0) {
      lVar3 = *(long *)(lVar1 + -0x10);
      if (lVar3 != lVar4) {
        *(ulong *)(lVar1 + -0x10) = lVar3 + (~((lVar3 + -0x10) - lVar4) & 0xfffffffffffffff0U);
      }
      goto code_r0x011d23a0;
    }
    lVar7 = lVar1 + -0x30;
    if ((*(byte *)(lVar1 + -0x30) & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar1 + -0x20));
    }
  } while( true );
}

// ==== std::__ndk1::enable_if<__is_forward_iterator<CUIVoiceManager::UpVoicePlayingData::PlayUnit*>::value&&is_constructible<CUIVoiceManager::UpVoicePlayingData::PlayUnit, std::__ndk1::iterator_traits<CUIVoiceManager::UpVoicePlayingData::PlayUnit*>::reference>::value, void>::type std::__ndk1::vector<CUIVoiceManager::UpVoicePlayingData::PlayUnit, Framework::CSTLAllocator<CUIVoiceManager::UpVoicePlayingData::PlayUnit, Framework::CSTLVectorAllocatorInf> >::assign<CUIVoiceManager::UpVoicePlayingData::PlayUnit*>(CUIVoiceManager::UpVoicePlayingData::PlayUnit*, CUIVoiceManager::UpVoicePlayingData::PlayUnit*)
// vaddr 0x1e19ef4 | ghidra 0x1f19ef4 | size 528 | symbol _ZNSt6__ndk16vectorIN15CUIVoiceManager18UpVoicePlayingData8PlayUnitEN9Framework13CSTLAllocatorIS3_NS4_22CSTLVectorAllocatorInfEEEE6assignIPS3_EENS_9enable_ifIXaasr21__is_forward_iteratorIT_EE5valuesr16is_constructibleIS3_NS_15iterator_traitsISC_E9referenceEEE5valueEvE4typeESC_SC_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk16vectorIN15CUIVoiceManager18UpVoicePlayingData8PlayUnitEN9Framework13CSTLAllocatorIS3_NS4_22CSTLVectorAllocatorInfEEEE6assignIPS3_EENS_9enable_ifIXaasr21__is_forward_iteratorIT_EE5valuesr16is_constructibleIS3_NS_15iterator_traitsISC_E9referenceEEE5valueEvE4typeESC_SC_
               (long *param_1,undefined8 *param_2,undefined8 *param_3)

{
  undefined8 *puVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  ulong uVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  undefined8 uVar9;
  
  lVar2 = param_1[2];
  lVar5 = *param_1;
  uVar6 = (long)param_3 - (long)param_2 >> 4;
  if ((ulong)(lVar2 - lVar5 >> 4) < uVar6) {
    if (lVar5 != 0) {
      lVar2 = param_1[1];
      if (lVar2 != lVar5) {
        param_1[1] = lVar2 + (~((lVar2 + -0x10) - lVar5) & 0xfffffffffffffff0U);
      }
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lVar5);
      lVar2 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
      *param_1 = 0;
    }
    if ((ulong)(lVar2 >> 4) < 0x7ffffffffffffff) {
      uVar3 = lVar2 >> 3;
      if ((uVar6 <= uVar3) && (uVar6 = uVar3, uVar3 == 0)) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
    }
    else {
      uVar6 = 0xfffffffffffffff;
    }
    puVar1 = (undefined8 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6 << 4,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
    if (puVar1 == (undefined8 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    *param_1 = (long)puVar1;
    param_1[1] = (long)puVar1;
    param_1[2] = (long)(puVar1 + uVar6 * 2);
    for (; param_2 != param_3; param_2 = param_2 + 2) {
      if (puVar1 == (undefined8 *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
      }
      uVar9 = *param_2;
      puVar1[1] = param_2[1];
      *puVar1 = uVar9;
      puVar1 = (undefined8 *)(param_1[1] + 0x10);
      param_1[1] = (long)puVar1;
    }
  }
  else {
    uVar3 = param_1[1] - lVar5 >> 4;
    puVar1 = (undefined8 *)((long)param_2 + (param_1[1] - lVar5));
    puVar7 = puVar1;
    if (uVar6 <= uVar3) {
      puVar7 = param_3;
    }
    lVar2 = (long)puVar7 - (long)param_2 >> 4;
    if (lVar2 != 0) {
      memmove(lVar5,param_2);
    }
    if (uVar3 < uVar6) {
      if (puVar7 != param_3) {
        puVar7 = (undefined8 *)param_1[1];
        do {
          if (puVar7 == (undefined8 *)0x0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          puVar8 = puVar1 + 2;
          uVar9 = *puVar1;
          puVar7[1] = puVar1[1];
          *puVar7 = uVar9;
          puVar7 = (undefined8 *)(param_1[1] + 0x10);
          param_1[1] = (long)puVar7;
          puVar1 = puVar8;
        } while (param_3 != puVar8);
      }
    }
    else {
      lVar4 = param_1[1];
      lVar5 = lVar5 + lVar2 * 0x10;
      if (lVar4 != lVar5) {
        param_1[1] = lVar4 + (~((lVar4 + -0x10) - lVar5) & 0xfffffffffffffff0U);
      }
    }
  }
  return;
}

// ==== void std::__ndk1::vector<CUIVoiceManager::UpVoiceData, Framework::CSTLAllocator<CUIVoiceManager::UpVoiceData, Framework::CSTLVectorAllocatorInf> >::__push_back_slow_path<CUIVoiceManager::UpVoiceData const&>(CUIVoiceManager::UpVoiceData const&)
// vaddr 0x1e1a2f4 | ghidra 0x1f1a2f4 | size 532 | symbol _ZNSt6__ndk16vectorIN15CUIVoiceManager11UpVoiceDataEN9Framework13CSTLAllocatorIS2_NS3_22CSTLVectorAllocatorInfEEEE21__push_back_slow_pathIRKS2_EEvOT_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk16vectorIN15CUIVoiceManager11UpVoiceDataEN9Framework13CSTLAllocatorIS2_NS3_22CSTLVectorAllocatorInfEEEE21__push_back_slow_pathIRKS2_EEvOT_
               (long *param_1,ulong *param_2)

{
  ulong *puVar1;
  long lVar2;
  ulong *puVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  long lStack_78;
  ulong *puStack_70;
  ulong *puStack_68;
  long lStack_60;
  long *plStack_58;
  
  plStack_58 = param_1 + 2;
  lVar4 = *plStack_58 - *param_1;
  lVar8 = param_1[1] - *param_1 >> 5;
  if ((ulong)(lVar4 >> 5) < 0x3ffffffffffffff) {
    uVar5 = lVar4 >> 4;
    uVar6 = lVar8 + 1U;
    if (lVar8 + 1U <= uVar5) {
      uVar6 = uVar5;
    }
    if (uVar6 != 0) goto code_r0x01f1a364;
    lVar4 = 0;
  }
  else {
    uVar6 = 0x7ffffffffffffff;
code_r0x01f1a364:
    lStack_60 = 0;
    lVar4 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6 << 5,&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x20);
    if (lVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
  }
  puVar1 = (ulong *)(lVar4 + lVar8 * 0x20);
  lStack_60 = lVar4 + uVar6 * 0x20;
  lStack_78 = lVar4;
  puStack_70 = puVar1;
  puStack_68 = puVar1;
  if (puVar1 == (ulong *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
  }
  puVar1[1] = 0;
  puVar1[2] = 0;
  *puVar1 = 0;
  if ((*param_2 & 1) == 0) {
    puVar1[2] = param_2[2];
    uVar6 = *param_2;
    puVar1[1] = param_2[1];
    *puVar1 = uVar6;
    puStack_68 = puVar1;
    goto code_r0x01f1a48c;
  }
  uVar6 = param_2[1];
  uVar5 = param_2[2];
  if (uVar6 < 0x17) {
    lVar9 = (long)puVar1 + 1;
    *(char *)puVar1 = (char)(uVar6 << 1);
    if (uVar6 != 0) goto code_r0x01f1a474;
  }
  else {
    uVar7 = uVar6 + 0x10 & 0xfffffffffffffff0;
    if (uVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    lVar9 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar7,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (lVar9 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    lVar2 = lVar4 + lVar8 * 0x20;
    *(ulong *)(lVar2 + 8) = uVar6;
    *(long *)(lVar2 + 0x10) = lVar9;
    *puVar1 = uVar7 | 1;
code_r0x01f1a474:
    memcpy(lVar9,uVar5,uVar6);
  }
  *(undefined1 *)(lVar9 + uVar6) = 0;
code_r0x01f1a48c:
  puStack_68 = puStack_68 + 4;
  *(int *)(lVar4 + lVar8 * 0x20 + 0x18) = (int)param_2[3];
  std::__ndk1::vector<CUIVoiceManager::UpVoiceData, Framework::CSTLAllocator<CUIVoiceManager::UpVoiceData, Framework::CSTLVectorAllocatorInf> >::__swap_out_circular_buffer(std::__ndk1::__split_buffer<CUIVoiceManager::UpVoiceData, Framework::CSTLAllocator<CUIVoiceManager::UpVoiceData, Framework::CSTLVectorAllocatorInf>&>&)(param_1,&lStack_78);
  puVar1 = puStack_70;
  while (puVar3 = puStack_68, puVar3 != puVar1) {
    puStack_68 = puVar3 + -4;
    if ((puVar3[-4] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puVar3[-2]);
    }
  }
  if (lStack_78 != 0) {
    puStack_68 = puVar3;
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)();
  }
  return;
}

// ==== std::__ndk1::vector<CUIVoiceManager::UpVoiceData, Framework::CSTLAllocator<CUIVoiceManager::UpVoiceData, Framework::CSTLVectorAllocatorInf> >::__swap_out_circular_buffer(std::__ndk1::__split_buffer<CUIVoiceManager::UpVoiceData, Framework::CSTLAllocator<CUIVoiceManager::UpVoiceData, Framework::CSTLVectorAllocatorInf>&>&)
// vaddr 0x1e1a508 | ghidra 0x1f1a508 | size 376 | symbol _ZNSt6__ndk16vectorIN15CUIVoiceManager11UpVoiceDataEN9Framework13CSTLAllocatorIS2_NS3_22CSTLVectorAllocatorInfEEEE26__swap_out_circular_bufferERNS_14__split_bufferIS2_RS6_EE | lib libSOA-3.7.0.so | 2026-10-08
void _ZNSt6__ndk16vectorIN15CUIVoiceManager11UpVoiceDataEN9Framework13CSTLAllocatorIS2_NS3_22CSTLVectorAllocatorInfEEEE26__swap_out_circular_bufferERNS_14__split_bufferIS2_RS6_EE
               (long *param_1,undefined8 *param_2)

{
  ulong uVar1;
  long lVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  undefined8 uVar8;
  
  lVar2 = *param_1;
  if (param_1[1] == lVar2) {
    lVar7 = param_2[1];
  }
  else {
    lVar7 = param_2[1];
    puVar3 = (undefined8 *)(param_1[1] + -0x10);
    do {
      puVar4 = (undefined8 *)(lVar7 + -0x20);
      *puVar4 = 0;
      *(undefined8 *)(lVar7 + -0x18) = 0;
      *(undefined8 *)(lVar7 + -0x10) = 0;
      if ((*(byte *)(puVar3 + -2) & 1) == 0) {
        *(undefined8 *)(lVar7 + -0x10) = *puVar3;
        uVar8 = puVar3[-2];
        *(undefined8 *)(lVar7 + -0x18) = puVar3[-1];
        *puVar4 = uVar8;
      }
      else {
        uVar1 = puVar3[-1];
        uVar8 = *puVar3;
        if (uVar1 < 0x17) {
          lVar5 = lVar7 + -0x1f;
          *(char *)puVar4 = (char)(uVar1 << 1);
          if (uVar1 != 0) goto code_r0x01f1a5f0;
        }
        else {
          uVar6 = uVar1 + 0x10 & 0xfffffffffffffff0;
          if (uVar6 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          lVar5 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar6,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (lVar5 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          *(ulong *)(lVar7 + -0x18) = uVar1;
          *(long *)(lVar7 + -0x10) = lVar5;
          *(ulong *)(lVar7 + -0x20) = uVar6 | 1;
code_r0x01f1a5f0:
          memcpy(lVar5,uVar8,uVar1);
        }
        *(undefined1 *)(lVar5 + uVar1) = 0;
      }
      puVar4 = puVar3 + 1;
      puVar3 = puVar3 + -4;
      *(undefined4 *)(lVar7 + -8) = *(undefined4 *)puVar4;
      lVar7 = param_2[1] + -0x20;
      param_2[1] = lVar7;
    } while ((long)puVar3 - lVar2 != -0x10);
    lVar2 = *param_1;
  }
  *param_1 = lVar7;
  param_2[1] = lVar2;
  lVar2 = param_1[1];
  param_1[1] = param_2[2];
  param_2[2] = lVar2;
  lVar2 = param_1[2];
  param_1[2] = param_2[3];
  param_2[3] = lVar2;
  *param_2 = param_2[1];
  return;
}


// FAILED to create function at 02868700 typeinfo name for CSoundManager::CInterruptNotify
// FAILED to create function at 028d2760 typeinfo name for std::__ndk1::__function::__base<void (Framework::CSTLVector<CMenuVoiceManager::ReserveData>*)>
// FAILED to create function at 02b0bac8 CParameterSoundElement::vtable
// FAILED to create function at 02b0baf8 CParameterSound::vtable
// FAILED to create function at 02b0bb40 CParameterSoundElement::typeinfo
// FAILED to create function at 02b0bb60 CParameterSound::typeinfo
// FAILED to create function at 02b53328 CMenuVoiceManager::vtable
// FAILED to create function at 02b53348 CMenuVoiceManager::typeinfo
// FAILED to create function at 02b53480 std::__ndk1::__function::__base<void(Framework::CSTLVector<CMenuVoiceManager::ReserveData>*)>::typeinfo
// FAILED to create function at 02ba0c98 CUIVoiceManager::vtable
// FAILED to create function at 02ba0cb8 CUIVoiceManager::typeinfo
