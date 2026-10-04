// port/decomp/lib_crypto/encrypt_aes.c: Ghidra decompiles for the lib_crypto subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:14 UTC: tools/decomp.sh '--into' 'lib_crypto/encrypt_aes' 'Encrypt::CEncryptAES128::'

// ==== Encrypt::CEncryptAES128::CEncryptAES128()
// vaddr 0x25a5c58 | ghidra 0x26a5c58 | size 4 | symbol _ZN7Encrypt14CEncryptAES128C1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN7Encrypt14CEncryptAES128C2Ev(void)

{
  return;
}

// ==== Encrypt::CEncryptAES128::CEncryptAES128(unsigned char const*, unsigned char const*)
// vaddr 0x25a5c5c | ghidra 0x26a5c5c | size 4 | symbol _ZN7Encrypt14CEncryptAES128C1EPKhS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN7Encrypt14CEncryptAES128C2EPKhS2_(void)

{
  (*(code *)PTR__ZN7Encrypt14CEncryptAES12810InitializeEPKhS2__02c93520)();
  return;
}

// ==== Encrypt::CEncryptAES128::Initialize(unsigned char const*, unsigned char const*)
// vaddr 0x25a5c60 | ghidra 0x26a5c60 | size 224 | symbol _ZN7Encrypt14CEncryptAES12810InitializeEPKhS2_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN7Encrypt14CEncryptAES12810InitializeEPKhS2_(undefined8 *param_1,long param_2,undefined *param_3)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  undefined8 uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  undefined1 uStack_28;
  undefined1 uStack_27;
  undefined1 uStack_24;
  undefined1 uStack_23;
  
  if (param_3 == (undefined *)0x0) {
    param_3 = &UNK_02a31c30/*"09375711857134629684891855841614"*/;
  }
  if ((param_2 == 0) || (iVar4 = strlen(param_2), iVar4 != 0x20)) {
    uVar5 = 0xffffff9b;
  }
  else {
    *param_1 = 0;
    param_1[1] = 0;
    uVar8 = 0;
    do {
      uStack_24 = *(undefined1 *)(param_2 + uVar8);
      uStack_23 = 0;
      bVar3 = atoi(&uStack_24);
      uVar6 = uVar8 >> 1 & 0x7fffffff;
      bVar2 = bVar3 << 4;
      if ((uVar8 & 1) != 0) {
        bVar2 = bVar3;
      }
      *(byte *)((long)param_1 + uVar6) = bVar2 | *(byte *)((long)param_1 + uVar6);
      bVar1 = (long)uVar8 < 0x1f;
      uVar8 = uVar8 + 1;
    } while (bVar1);
    uVar8 = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    do {
      uStack_28 = param_3[uVar8];
      uStack_27 = 0;
      bVar3 = atoi(&uStack_28);
      uVar7 = uVar8 >> 1 & 0x7fffffff;
      uVar6 = uVar8 & 1;
      uVar8 = uVar8 + 1;
      bVar2 = bVar3 << 4;
      if (uVar6 != 0) {
        bVar2 = bVar3;
      }
      *(byte *)((long)param_1 + uVar7 + 0x10) = bVar2 | *(byte *)((long)param_1 + uVar7 + 0x10);
    } while (uVar8 != 0x20);
    uVar5 = 0;
  }
  return uVar5;
}

// ==== Encrypt::CEncryptAES128::Encrypt(void const*, unsigned int, void*, unsigned int)
// vaddr 0x25a5d40 | ghidra 0x26a5d40 | size 212 | symbol _ZN7Encrypt14CEncryptAES1287EncryptEPKvjPvj | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN7Encrypt14CEncryptAES1287EncryptEPKvjPvj
               (long param_1,undefined8 param_2,uint param_3,undefined8 param_4)

{
  uint uVar1;
  long lVar2;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined1 auStack_138 [248];
  
  AES_set_encrypt_key(param_1,0x80,auStack_138);
  uStack_148 = *(undefined8 *)(param_1 + 0x18);
  uStack_150 = *(undefined8 *)(param_1 + 0x10);
  uVar1 = param_3 + 0xf & 0xfffffff0;
  if (uVar1 == param_3) {
    AES_cbc_encrypt(param_2,param_4,uVar1,auStack_138,&uStack_150,1);
  }
  else {
    lVar2 = operator new[](unsigned long)(uVar1);
    memcpy(lVar2,param_2,(ulong)param_3);
    memset(lVar2 + (ulong)param_3,0,uVar1 - param_3);
    AES_cbc_encrypt(lVar2,param_4,uVar1,auStack_138,&uStack_150,1);
    operator delete[](void*)(lVar2);
  }
  return uVar1;
}

// ==== Encrypt::CEncryptAES128::Decrypt(void const*, unsigned int, void*, unsigned int)
// vaddr 0x25a5e14 | ghidra 0x26a5e14 | size 116 | symbol _ZN7Encrypt14CEncryptAES1287DecryptEPKvjPvj | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN7Encrypt14CEncryptAES1287DecryptEPKvjPvj
          (long param_1,undefined8 param_2,undefined4 param_3,undefined8 param_4)

{
  undefined4 uVar1;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined1 auStack_138 [248];
  
  uVar1 = AES_set_decrypt_key(param_1,0x80,auStack_138);
  uStack_148 = *(undefined8 *)(param_1 + 0x18);
  uStack_150 = *(undefined8 *)(param_1 + 0x10);
  AES_cbc_encrypt(param_2,param_4,param_3,auStack_138,&uStack_150,0);
  return uVar1;
}

// ==== Encrypt::CEncryptAES128::CalcEncryptBufferSize(unsigned int)
// vaddr 0x25a5e88 | ghidra 0x26a5e88 | size 12 | symbol _ZN7Encrypt14CEncryptAES12821CalcEncryptBufferSizeEj | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN7Encrypt14CEncryptAES12821CalcEncryptBufferSizeEj(int param_1)

{
  return param_1 + 0xfU & 0xfffffff0;
}
