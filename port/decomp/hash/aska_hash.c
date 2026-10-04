// port/decomp/hash/aska_hash.c: Ghidra decompiles for the hash subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:07 UTC: tools/decomp.sh '--into' 'hash/aska_hash' 'Aska::Hash::'

// ==== Aska::Hash::HMAC_SHA1(char*, unsigned long, char const*, unsigned long, char*, unsigned long, char*, unsigned long, bool)
// vaddr 0x1f85f3c | ghidra 0x2085f3c | size 668 | symbol _ZN4Aska4Hash9HMAC_SHA1EPcmPKcmS1_mS1_mb | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska4Hash9HMAC_SHA1EPcmPKcmS1_mS1_mb
                (undefined8 param_1,ulong param_2,undefined8 param_3,long param_4,undefined8 param_5
                ,ulong param_6,ulong *param_7,ulong param_8,byte param_9)

{
  long lVar1;
  long lVar2;
  ulong uStack_100;
  ulong uStack_f8;
  ulong uStack_f0;
  ulong uStack_e8;
  ulong uStack_e0;
  ulong uStack_d8;
  ulong uStack_d0;
  ulong uStack_c8;
  ulong uStack_b0;
  ulong uStack_a8;
  ulong uStack_a0;
  ulong uStack_98;
  ulong uStack_90;
  ulong uStack_88;
  ulong uStack_80;
  ulong uStack_78;
  
  if ((0x13 < param_6) || ((param_9 & 1) != 0)) {
    memset(&uStack_b0,0,0x41);
    memset(&uStack_100,0,0x41);
    if (0x40 < param_2) {
      param_2 = Aska::Hash::SHA1(char const*, unsigned long, char*, unsigned long, char*, unsigned long)(param_1,param_2,param_5,param_6,param_7,param_8);
      if (param_2 == 0) {
        return 0;
      }
      memcpy(param_1,param_5,param_2);
    }
    lVar1 = 0;
    if (param_2 < 0x41) {
      lVar1 = 0x41 - param_2;
    }
    memset((long)&uStack_b0 + param_2,0,lVar1);
    memcpy(&uStack_b0,param_1,param_2);
    memset((long)&uStack_100 + param_2,0,lVar1);
    memcpy(&uStack_100,param_1,param_2);
    uStack_b0 = uStack_b0 ^ 0x3636363636363636;
    uStack_a8 = uStack_a8 ^ 0x3636363636363636;
    uStack_100 = uStack_100 ^ 0x5c5c5c5c5c5c5c5c;
    uStack_f8 = uStack_f8 ^ 0x5c5c5c5c5c5c5c5c;
    uStack_a0 = uStack_a0 ^ 0x3636363636363636;
    uStack_98 = uStack_98 ^ 0x3636363636363636;
    uStack_f0 = uStack_f0 ^ 0x5c5c5c5c5c5c5c5c;
    uStack_e8 = uStack_e8 ^ 0x5c5c5c5c5c5c5c5c;
    uStack_90 = uStack_90 ^ 0x3636363636363636;
    uStack_88 = uStack_88 ^ 0x3636363636363636;
    uStack_e0 = uStack_e0 ^ 0x5c5c5c5c5c5c5c5c;
    uStack_d8 = uStack_d8 ^ 0x5c5c5c5c5c5c5c5c;
    uStack_80 = uStack_80 ^ 0x3636363636363636;
    uStack_78 = uStack_78 ^ 0x3636363636363636;
    uStack_c8 = uStack_c8 ^ 0x5c5c5c5c5c5c5c5c;
    uStack_d0 = uStack_d0 ^ 0x5c5c5c5c5c5c5c5c;
    if (param_8 < param_4 + 0x41U) {
      return 0;
    }
    param_7[7] = uStack_78;
    param_7[6] = uStack_80;
    lVar1 = (long)param_7 + param_4 + 0x41U;
    param_7[5] = uStack_88;
    param_7[4] = uStack_90;
    param_7[3] = uStack_98;
    param_7[2] = uStack_a0;
    param_7[1] = uStack_a8;
    *param_7 = uStack_b0;
    memcpy(param_7 + 8,param_3,param_4 + 1);
    lVar2 = Aska::Hash::SHA1(char const*, unsigned long, char*, unsigned long, char*, unsigned long)(param_7,param_4 + 0x40,lVar1,0x14,lVar1 + 0x14,
                            (param_8 - param_4) + -0x55);
    if (lVar2 != 0) {
      memmove(param_7 + 8,lVar1,lVar2 + 1);
      if (lVar2 + 0x41U <= param_8) {
        lVar1 = (long)param_7 + lVar2 + 0x41U;
        param_7[7] = uStack_c8;
        param_7[6] = uStack_d0;
        param_7[5] = uStack_d8;
        param_7[4] = uStack_e0;
        param_7[3] = uStack_e8;
        param_7[2] = uStack_f0;
        param_7[1] = uStack_f8;
        *param_7 = uStack_100;
        lVar2 = Aska::Hash::SHA1(char const*, unsigned long, char*, unsigned long, char*, unsigned long)(param_7,lVar2 + 0x40,lVar1,0x14,lVar1 + 0x14,
                                (param_8 - lVar2) + -0x55);
        if (lVar2 != 0) {
          if (0x13 < param_6) {
            param_6 = 0x14;
          }
          memcpy(param_5,lVar1,param_6);
          return param_6;
        }
      }
    }
  }
  return 0;
}

// ==== Aska::Hash::SHA1(char const*, unsigned long, char*, unsigned long, char*, unsigned long)
// vaddr 0x1f861d8 | ghidra 0x20861d8 | size 2124 | symbol _ZN4Aska4Hash4SHA1EPKcmPcmS3_m | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska4Hash4SHA1EPKcmPcmS3_m
          (undefined8 param_1,ulong param_2,uint *param_3,ulong param_4,long param_5,ulong param_6)

{
  int *piVar1;
  long lVar2;
  int iVar3;
  undefined1 *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined8 uVar9;
  uint uVar10;
  uint uVar11;
  ulong uVar12;
  uint uVar13;
  ulong uVar14;
  uint uVar15;
  long lVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  ulong uVar22;
  uint auStack_1a0 [80];
  
  if ((param_4 < 0x14) ||
     (uVar22 = param_2 + 0x41 & 0xffffffffffffffc0, param_6 < (uVar22 | 0x3c) + 4)) {
    uVar9 = 0;
  }
  else {
    lVar16 = (uVar22 - param_2) + -8;
    uVar17 = 0x10325476;
    uVar20 = 0x67452301;
    uVar19 = 0x98badcfe;
    uVar18 = 0xc3d2e1f0;
    uVar21 = 0xefcdab89;
    if (lVar16 < 1) {
      uVar22 = uVar22 + 0x40;
      lVar16 = (-8 - param_2) + uVar22;
    }
    memcpy(param_5,param_1,param_2);
    memset((undefined1 *)(param_5 + param_2),0,lVar16);
    puVar4 = (undefined1 *)(param_5 + lVar16 + param_2);
    *(undefined1 *)(param_5 + param_2) = 0x80;
    uVar5 = (uint)(param_2 >> 0x20);
    *puVar4 = (char)(uVar5 >> 0x15);
    puVar4[1] = (char)(uVar5 >> 0xd);
    puVar4[2] = (char)(uVar5 >> 5);
    puVar4[3] = (char)(param_2 >> 0x1d);
    puVar4[4] = (char)(param_2 >> 0x15);
    puVar4[5] = (char)(param_2 >> 0xd);
    puVar4[6] = (char)(param_2 >> 5);
    puVar4[7] = (char)(param_2 << 3);
    if (uVar22 != 0) {
      uVar12 = 0;
      do {
        lVar16 = 0;
        do {
          uVar14 = (ulong)(uint)((int)uVar12 + (int)lVar16);
          *(uint *)((long)auStack_1a0 + lVar16) =
               (uint)*(byte *)(param_5 + uVar14) << 0x18 |
               (uint)*(byte *)(param_5 + (uVar14 | 1)) << 0x10 |
               (uint)*(byte *)(param_5 + (uVar14 | 2)) << 8 |
               (uint)*(byte *)(param_5 + (uVar14 | 3));
          lVar16 = lVar16 + 4;
        } while (lVar16 != 0x40);
        lVar16 = 0;
        do {
          lVar2 = lVar16 + 4;
          uVar5 = *(uint *)((long)auStack_1a0 + lVar16 + 0x20) ^
                  *(uint *)((long)auStack_1a0 + lVar16 + 0x34) ^
                  *(uint *)((long)auStack_1a0 + lVar16 + 8) ^ *(uint *)((long)auStack_1a0 + lVar16);
          *(uint *)((long)auStack_1a0 + lVar16 + 0x40) = uVar5 >> 0x1f | uVar5 << 1;
          lVar16 = lVar2;
        } while (lVar2 != 0x100);
        lVar16 = 0;
        uVar11 = uVar19;
        uVar5 = uVar20;
        uVar13 = uVar21;
        uVar6 = uVar17;
        uVar8 = uVar18;
        do {
          uVar10 = uVar6;
          uVar7 = uVar5;
          uVar6 = uVar11;
          piVar1 = (int *)((long)auStack_1a0 + lVar16);
          uVar11 = uVar13 >> 2 | uVar13 << 0x1e;
          lVar16 = lVar16 + 4;
          uVar5 = uVar8 + (uVar13 & uVar6 | uVar10 & (uVar13 ^ 0xffffffff)) +
                  (uVar7 >> 0x1b | uVar7 << 5) + *piVar1 + 0x5a827999;
          uVar13 = uVar7;
          uVar8 = uVar10;
        } while (lVar16 != 0x50);
        uVar8 = uVar7 >> 2 | uVar7 << 0x1e;
        uVar15 = uVar5 >> 2 | uVar5 * 0x40000000;
        lVar16 = 0;
        uVar13 = uVar10 + (uVar11 ^ uVar6 ^ uVar7) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x14] + 0x6ed9eba1;
        uVar5 = uVar6 + (uVar8 ^ uVar11 ^ uVar5) + (uVar13 >> 0x1b | uVar13 * 0x20) +
                auStack_1a0[0x15] + 0x6ed9eba1;
        uVar6 = uVar13 >> 2 | uVar13 * 0x40000000;
        uVar7 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar11 = uVar11 + (uVar15 ^ uVar8 ^ uVar13) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x16] + 0x6ed9eba1;
        uVar5 = uVar8 + (uVar6 ^ uVar15 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x17] + 0x6ed9eba1;
        uVar13 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar8 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar11 = uVar15 + (uVar7 ^ uVar6 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x18] + 0x6ed9eba1;
        uVar5 = uVar6 + (uVar13 ^ uVar7 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x19] + 0x6ed9eba1;
        uVar6 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar10 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar11 = uVar7 + (uVar8 ^ uVar13 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x1a] + 0x6ed9eba1;
        uVar5 = uVar13 + (uVar6 ^ uVar8 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x1b] + 0x6ed9eba1;
        uVar13 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar7 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar11 = uVar8 + (uVar10 ^ uVar6 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x1c] + 0x6ed9eba1;
        uVar5 = uVar6 + (uVar13 ^ uVar10 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x1d] + 0x6ed9eba1;
        uVar6 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar8 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar11 = uVar10 + (uVar7 ^ uVar13 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x1e] + 0x6ed9eba1;
        uVar5 = uVar13 + (uVar6 ^ uVar7 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x1f] + 0x6ed9eba1;
        uVar13 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar10 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar11 = uVar7 + (uVar8 ^ uVar6 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x20] + 0x6ed9eba1;
        uVar5 = uVar6 + (uVar13 ^ uVar8 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x21] + 0x6ed9eba1;
        uVar6 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar7 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar11 = uVar8 + (uVar10 ^ uVar13 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x22] + 0x6ed9eba1;
        uVar8 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar5 = uVar13 + (uVar6 ^ uVar10 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x23] + 0x6ed9eba1;
        uVar13 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar11 = uVar10 + (uVar7 ^ uVar6 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x24] + 0x6ed9eba1;
        uVar5 = uVar6 + (uVar8 ^ uVar7 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x25] + 0x6ed9eba1;
        uVar6 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar11 = uVar7 + (uVar13 ^ uVar8 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x26] + 0x6ed9eba1;
        uVar7 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar5 = uVar8 + (uVar6 ^ uVar13 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x27] + 0x6ed9eba1;
        do {
          uVar8 = uVar5;
          uVar10 = uVar7;
          uVar15 = uVar6;
          lVar2 = lVar16 + 0xa0;
          uVar7 = uVar11 >> 2 | uVar11 << 0x1e;
          lVar16 = lVar16 + 4;
          iVar3 = uVar13 + (uVar11 & (uVar10 | uVar15) | uVar10 & uVar15) +
                  (uVar8 >> 0x1b | uVar8 << 5) + *(int *)((long)auStack_1a0 + lVar2);
          uVar5 = iVar3 + 0x8f1bbcdc;
          uVar13 = uVar15;
          uVar6 = uVar10;
          uVar11 = uVar8;
        } while (lVar16 != 0x50);
        uVar6 = uVar8 >> 2 | uVar8 << 0x1e;
        uVar11 = uVar15 + (uVar7 ^ uVar10 ^ uVar8) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x3c] + 0xca62c1d6;
        uVar13 = uVar5 >> 2 | iVar3 * 0x40000000;
        uVar5 = uVar10 + (uVar6 ^ uVar7 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x3d] + 0xca62c1d6;
        uVar8 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar11 = uVar7 + (uVar13 ^ uVar6 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x3e] + 0xca62c1d6;
        uVar7 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar5 = uVar6 + (uVar8 ^ uVar13 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x3f] + 0xca62c1d6;
        uVar6 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar11 = uVar13 + (uVar7 ^ uVar8 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x40] + 0xca62c1d6;
        uVar13 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar5 = uVar8 + (uVar6 ^ uVar7 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x41] + 0xca62c1d6;
        uVar8 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar11 = uVar7 + (uVar13 ^ uVar6 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x42] + 0xca62c1d6;
        uVar7 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar5 = uVar6 + (uVar8 ^ uVar13 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x43] + 0xca62c1d6;
        uVar6 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar11 = uVar13 + (uVar7 ^ uVar8 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x44] + 0xca62c1d6;
        uVar13 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar5 = uVar8 + (uVar6 ^ uVar7 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x45] + 0xca62c1d6;
        uVar8 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar11 = uVar7 + (uVar13 ^ uVar6 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x46] + 0xca62c1d6;
        uVar7 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar5 = uVar6 + (uVar8 ^ uVar13 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x47] + 0xca62c1d6;
        uVar6 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar11 = uVar13 + (uVar7 ^ uVar8 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x48] + 0xca62c1d6;
        uVar13 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar5 = uVar8 + (uVar6 ^ uVar7 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x49] + 0xca62c1d6;
        uVar8 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar11 = uVar7 + (uVar13 ^ uVar6 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x4a] + 0xca62c1d6;
        uVar7 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar5 = uVar6 + (uVar8 ^ uVar13 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x4b] + 0xca62c1d6;
        uVar6 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar11 = uVar13 + (uVar7 ^ uVar8 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x4c] + 0xca62c1d6;
        uVar13 = uVar5 >> 2 | uVar5 * 0x40000000;
        uVar10 = uVar11 >> 2 | uVar11 * 0x40000000;
        uVar5 = uVar8 + (uVar6 ^ uVar7 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                auStack_1a0[0x4d] + 0xca62c1d6;
        uVar17 = uVar10 + uVar17;
        uVar19 = (uVar5 >> 2 | uVar5 * 0x40000000) + uVar19;
        uVar11 = uVar7 + (uVar13 ^ uVar6 ^ uVar11) + (uVar5 >> 0x1b | uVar5 * 0x20) +
                 auStack_1a0[0x4e] + 0xca62c1d6;
        uVar12 = (ulong)((int)uVar12 + 0x40);
        uVar21 = uVar11 + uVar21;
        uVar20 = uVar6 + (uVar10 ^ uVar13 ^ uVar5) + (uVar11 >> 0x1b | uVar11 * 0x20) +
                 auStack_1a0[0x4f] + uVar20 + 0xca62c1d6;
        uVar18 = uVar13 + uVar18;
      } while (uVar12 < uVar22);
    }
    uVar20 = (uVar20 & 0xff00ff00) >> 8 | (uVar20 & 0xff00ff) << 8;
    uVar21 = (uVar21 & 0xff00ff00) >> 8 | (uVar21 & 0xff00ff) << 8;
    uVar19 = (uVar19 & 0xff00ff00) >> 8 | (uVar19 & 0xff00ff) << 8;
    uVar17 = (uVar17 & 0xff00ff00) >> 8 | (uVar17 & 0xff00ff) << 8;
    uVar18 = (uVar18 & 0xff00ff00) >> 8 | (uVar18 & 0xff00ff) << 8;
    uVar9 = 0x14;
    *param_3 = uVar20 >> 0x10 | uVar20 << 0x10;
    param_3[1] = uVar21 >> 0x10 | uVar21 << 0x10;
    param_3[2] = uVar19 >> 0x10 | uVar19 << 0x10;
    param_3[3] = uVar17 >> 0x10 | uVar17 << 0x10;
    param_3[4] = uVar18 >> 0x10 | uVar18 << 0x10;
  }
  return uVar9;
}

// ==== Aska::Hash::HMAC_MD5(char*, unsigned long, char const*, unsigned long, char*, unsigned long, char*, unsigned long, bool)
// vaddr 0x1f86a24 | ghidra 0x2086a24 | size 668 | symbol _ZN4Aska4Hash8HMAC_MD5EPcmPKcmS1_mS1_mb | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska4Hash8HMAC_MD5EPcmPKcmS1_mS1_mb
                (undefined8 param_1,ulong param_2,undefined8 param_3,long param_4,undefined8 param_5
                ,ulong param_6,ulong *param_7,ulong param_8,byte param_9)

{
  long lVar1;
  long lVar2;
  ulong uStack_100;
  ulong uStack_f8;
  ulong uStack_f0;
  ulong uStack_e8;
  ulong uStack_e0;
  ulong uStack_d8;
  ulong uStack_d0;
  ulong uStack_c8;
  ulong uStack_b0;
  ulong uStack_a8;
  ulong uStack_a0;
  ulong uStack_98;
  ulong uStack_90;
  ulong uStack_88;
  ulong uStack_80;
  ulong uStack_78;
  
  if ((0xf < param_6) || ((param_9 & 1) != 0)) {
    memset(&uStack_b0,0,0x41);
    memset(&uStack_100,0,0x41);
    if (0x40 < param_2) {
      param_2 = Aska::Hash::MD5(char const*, unsigned long, char*, unsigned long, char*, unsigned long)(param_1,param_2,param_5,param_6,param_7,param_8);
      if (param_2 == 0) {
        return 0;
      }
      memcpy(param_1,param_5,param_2);
    }
    lVar1 = 0;
    if (param_2 < 0x41) {
      lVar1 = 0x41 - param_2;
    }
    memset((long)&uStack_b0 + param_2,0,lVar1);
    memcpy(&uStack_b0,param_1,param_2);
    memset((long)&uStack_100 + param_2,0,lVar1);
    memcpy(&uStack_100,param_1,param_2);
    uStack_b0 = uStack_b0 ^ 0x3636363636363636;
    uStack_a8 = uStack_a8 ^ 0x3636363636363636;
    uStack_100 = uStack_100 ^ 0x5c5c5c5c5c5c5c5c;
    uStack_f8 = uStack_f8 ^ 0x5c5c5c5c5c5c5c5c;
    uStack_a0 = uStack_a0 ^ 0x3636363636363636;
    uStack_98 = uStack_98 ^ 0x3636363636363636;
    uStack_f0 = uStack_f0 ^ 0x5c5c5c5c5c5c5c5c;
    uStack_e8 = uStack_e8 ^ 0x5c5c5c5c5c5c5c5c;
    uStack_90 = uStack_90 ^ 0x3636363636363636;
    uStack_88 = uStack_88 ^ 0x3636363636363636;
    uStack_e0 = uStack_e0 ^ 0x5c5c5c5c5c5c5c5c;
    uStack_d8 = uStack_d8 ^ 0x5c5c5c5c5c5c5c5c;
    uStack_80 = uStack_80 ^ 0x3636363636363636;
    uStack_78 = uStack_78 ^ 0x3636363636363636;
    uStack_c8 = uStack_c8 ^ 0x5c5c5c5c5c5c5c5c;
    uStack_d0 = uStack_d0 ^ 0x5c5c5c5c5c5c5c5c;
    if (param_8 < param_4 + 0x41U) {
      return 0;
    }
    param_7[7] = uStack_78;
    param_7[6] = uStack_80;
    lVar1 = (long)param_7 + param_4 + 0x41U;
    param_7[5] = uStack_88;
    param_7[4] = uStack_90;
    param_7[3] = uStack_98;
    param_7[2] = uStack_a0;
    param_7[1] = uStack_a8;
    *param_7 = uStack_b0;
    memcpy(param_7 + 8,param_3,param_4 + 1);
    lVar2 = Aska::Hash::MD5(char const*, unsigned long, char*, unsigned long, char*, unsigned long)(param_7,param_4 + 0x40,lVar1,0x10,lVar1 + 0x10,
                            (param_8 - param_4) + -0x51);
    if (lVar2 != 0) {
      memmove(param_7 + 8,lVar1,lVar2 + 1);
      if (lVar2 + 0x41U <= param_8) {
        lVar1 = (long)param_7 + lVar2 + 0x41U;
        param_7[7] = uStack_c8;
        param_7[6] = uStack_d0;
        param_7[5] = uStack_d8;
        param_7[4] = uStack_e0;
        param_7[3] = uStack_e8;
        param_7[2] = uStack_f0;
        param_7[1] = uStack_f8;
        *param_7 = uStack_100;
        lVar2 = Aska::Hash::MD5(char const*, unsigned long, char*, unsigned long, char*, unsigned long)(param_7,lVar2 + 0x40,lVar1,0x10,lVar1 + 0x14,
                                (param_8 - lVar2) + -0x51);
        if (lVar2 != 0) {
          if (0xf < param_6) {
            param_6 = 0x10;
          }
          memcpy(param_5,lVar1,param_6);
          return param_6;
        }
      }
    }
  }
  return 0;
}

// ==== Aska::Hash::MD5(char const*, unsigned long, char*, unsigned long, char*, unsigned long)
// vaddr 0x1f86cc0 | ghidra 0x2086cc0 | size 2752 | symbol _ZN4Aska4Hash3MD5EPKcmPcmS3_m | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska4Hash3MD5EPKcmPcmS3_m
          (undefined8 param_1,long param_2,int *param_3,ulong param_4,undefined8 *param_5,
          ulong param_6)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  ulong uVar9;
  int iStack_a0;
  int iStack_9c;
  int iStack_98;
  int iStack_94;
  int iStack_90;
  int iStack_8c;
  int iStack_88;
  int iStack_84;
  int iStack_80;
  int iStack_7c;
  int iStack_78;
  int iStack_74;
  int iStack_70;
  int iStack_6c;
  int iStack_68;
  int iStack_64;
  
  if (0xf < param_4) {
    uVar9 = param_2 + 0x48U & 0xffffffffffffffc0;
    if (uVar9 <= param_6) {
      memcpy(param_5,param_1,param_2);
      *(undefined1 *)((long)param_5 + param_2) = 0x80;
      if (param_2 + 1 < (long)(uVar9 - 8)) {
        memset((long)param_5 + param_2 + 1,0,(uVar9 - 9) - param_2);
      }
      uVar5 = 0xefcdab89;
      uVar6 = 0x98badcfe;
      iVar7 = 0x67452301;
      uVar8 = 0x10325476;
      *(long *)((long)param_5 + (uVar9 - 8)) = param_2 << 3;
      for (uVar9 = param_2 + 0x48U >> 6; uVar9 != 0; uVar9 = uVar9 - 1) {
        iStack_a0 = (int)*param_5;
        iStack_9c = (int)((ulong)*param_5 >> 0x20);
        uVar1 = iVar7 + (uVar5 & uVar6 | uVar8 & (uVar5 ^ 0xffffffff)) + iStack_a0 + 0xd76aa478;
        uVar1 = (uVar1 >> 0x19 | uVar1 * 0x80) + uVar5;
        iStack_98 = (int)param_5[1];
        iStack_94 = (int)((ulong)param_5[1] >> 0x20);
        uVar2 = uVar8 + iStack_9c + (uVar1 & uVar5 | uVar6 & (uVar1 ^ 0xffffffff)) + 0xe8c7b756;
        uVar2 = (uVar2 >> 0x14 | uVar2 * 0x1000) + uVar1;
        iStack_90 = (int)param_5[2];
        iStack_8c = (int)((ulong)param_5[2] >> 0x20);
        uVar3 = uVar6 + iStack_98 + (uVar2 & uVar1 | uVar5 & (uVar2 ^ 0xffffffff)) + 0x242070db;
        uVar3 = (uVar3 >> 0xf | uVar3 * 0x20000) + uVar2;
        uVar4 = uVar5 + iStack_94 + (uVar3 & uVar2 | uVar1 & (uVar3 ^ 0xffffffff)) + 0xc1bdceee;
        uVar4 = (uVar4 >> 10 | uVar4 * 0x400000) + uVar3;
        iStack_88 = (int)param_5[3];
        iStack_84 = (int)((ulong)param_5[3] >> 0x20);
        uVar1 = iStack_90 + uVar1 + (uVar4 & uVar3 | uVar2 & (uVar4 ^ 0xffffffff)) + 0xf57c0faf;
        uVar1 = (uVar1 >> 0x19 | uVar1 * 0x80) + uVar4;
        uVar2 = iStack_8c + uVar2 + (uVar1 & uVar4 | uVar3 & (uVar1 ^ 0xffffffff)) + 0x4787c62a;
        uVar2 = (uVar2 >> 0x14 | uVar2 * 0x1000) + uVar1;
        iStack_80 = (int)param_5[4];
        iStack_7c = (int)((ulong)param_5[4] >> 0x20);
        uVar3 = iStack_88 + uVar3 + (uVar2 & uVar1 | uVar4 & (uVar2 ^ 0xffffffff)) + 0xa8304613;
        uVar3 = (uVar3 >> 0xf | uVar3 * 0x20000) + uVar2;
        uVar4 = iStack_84 + uVar4 + (uVar3 & uVar2 | uVar1 & (uVar3 ^ 0xffffffff)) + 0xfd469501;
        uVar4 = (uVar4 >> 10 | uVar4 * 0x400000) + uVar3;
        iStack_78 = (int)param_5[5];
        iStack_74 = (int)((ulong)param_5[5] >> 0x20);
        uVar1 = iStack_80 + uVar1 + (uVar4 & uVar3 | uVar2 & (uVar4 ^ 0xffffffff)) + 0x698098d8;
        uVar1 = (uVar1 >> 0x19 | uVar1 * 0x80) + uVar4;
        uVar2 = iStack_7c + uVar2 + (uVar1 & uVar4 | uVar3 & (uVar1 ^ 0xffffffff)) + 0x8b44f7af;
        uVar2 = (uVar2 >> 0x14 | uVar2 * 0x1000) + uVar1;
        iStack_70 = (int)param_5[6];
        iStack_6c = (int)((ulong)param_5[6] >> 0x20);
        uVar3 = (iStack_78 + uVar3 + (uVar2 & uVar1 | uVar4 & (uVar2 ^ 0xffffffff))) - 0xa44f;
        uVar3 = (uVar3 >> 0xf | uVar3 * 0x20000) + uVar2;
        uVar4 = iStack_74 + uVar4 + (uVar3 & uVar2 | uVar1 & (uVar3 ^ 0xffffffff)) + 0x895cd7be;
        uVar4 = (uVar4 >> 10 | uVar4 * 0x400000) + uVar3;
        iStack_68 = (int)param_5[7];
        iStack_64 = (int)((ulong)param_5[7] >> 0x20);
        uVar1 = iStack_70 + uVar1 + (uVar4 & uVar3 | uVar2 & (uVar4 ^ 0xffffffff)) + 0x6b901122;
        uVar1 = (uVar1 >> 0x19 | uVar1 * 0x80) + uVar4;
        uVar2 = iStack_6c + uVar2 + (uVar1 & uVar4 | uVar3 & (uVar1 ^ 0xffffffff)) + 0xfd987193;
        uVar2 = (uVar2 >> 0x14 | uVar2 * 0x1000) + uVar1;
        uVar3 = iStack_68 + uVar3 + (uVar2 & uVar1 | uVar4 & (uVar2 ^ 0xffffffff)) + 0xa679438e;
        uVar3 = (uVar3 >> 0xf | uVar3 * 0x20000) + uVar2;
        uVar4 = iStack_64 + uVar4 + (uVar3 & uVar2 | uVar1 & (uVar3 ^ 0xffffffff)) + 0x49b40821;
        uVar4 = (uVar4 >> 10 | uVar4 * 0x400000) + uVar3;
        uVar1 = iStack_9c + uVar1 + (uVar4 & uVar2 | uVar3 & (uVar2 ^ 0xffffffff)) + 0xf61e2562;
        uVar1 = (uVar1 >> 0x1b | uVar1 * 0x20) + uVar4;
        uVar2 = iStack_88 + uVar2 + (uVar1 & uVar3 | uVar4 & (uVar3 ^ 0xffffffff)) + 0xc040b340;
        uVar2 = (uVar2 >> 0x17 | uVar2 * 0x200) + uVar1;
        uVar3 = iStack_74 + uVar3 + (uVar2 & uVar4 | uVar1 & (uVar4 ^ 0xffffffff)) + 0x265e5a51;
        uVar3 = (uVar3 >> 0x12 | uVar3 * 0x4000) + uVar2;
        uVar4 = iStack_a0 + uVar4 + (uVar3 & uVar1 | uVar2 & (uVar1 ^ 0xffffffff)) + 0xe9b6c7aa;
        uVar4 = (uVar4 >> 0xc | uVar4 * 0x100000) + uVar3;
        uVar1 = iStack_8c + uVar1 + (uVar4 & uVar2 | uVar3 & (uVar2 ^ 0xffffffff)) + 0xd62f105d;
        uVar1 = (uVar1 >> 0x1b | uVar1 * 0x20) + uVar4;
        uVar2 = iStack_78 + uVar2 + (uVar1 & uVar3 | uVar4 & (uVar3 ^ 0xffffffff)) + 0x2441453;
        uVar2 = (uVar2 >> 0x17 | uVar2 * 0x200) + uVar1;
        uVar3 = iStack_64 + uVar3 + (uVar2 & uVar4 | uVar1 & (uVar4 ^ 0xffffffff)) + 0xd8a1e681;
        uVar3 = (uVar3 >> 0x12 | uVar3 * 0x4000) + uVar2;
        uVar4 = iStack_90 + uVar4 + (uVar3 & uVar1 | uVar2 & (uVar1 ^ 0xffffffff)) + 0xe7d3fbc8;
        uVar4 = (uVar4 >> 0xc | uVar4 * 0x100000) + uVar3;
        uVar1 = iStack_7c + uVar1 + (uVar4 & uVar2 | uVar3 & (uVar2 ^ 0xffffffff)) + 0x21e1cde6;
        uVar1 = (uVar1 >> 0x1b | uVar1 * 0x20) + uVar4;
        uVar2 = iStack_68 + uVar2 + (uVar1 & uVar3 | uVar4 & (uVar3 ^ 0xffffffff)) + 0xc33707d6;
        uVar2 = (uVar2 >> 0x17 | uVar2 * 0x200) + uVar1;
        uVar3 = iStack_94 + uVar3 + (uVar2 & uVar4 | uVar1 & (uVar4 ^ 0xffffffff)) + 0xf4d50d87;
        uVar3 = (uVar3 >> 0x12 | uVar3 * 0x4000) + uVar2;
        uVar4 = iStack_80 + uVar4 + (uVar3 & uVar1 | uVar2 & (uVar1 ^ 0xffffffff)) + 0x455a14ed;
        uVar4 = (uVar4 >> 0xc | uVar4 * 0x100000) + uVar3;
        uVar1 = iStack_6c + uVar1 + (uVar4 & uVar2 | uVar3 & (uVar2 ^ 0xffffffff)) + 0xa9e3e905;
        uVar1 = (uVar1 >> 0x1b | uVar1 * 0x20) + uVar4;
        uVar2 = iStack_98 + uVar2 + (uVar1 & uVar3 | uVar4 & (uVar3 ^ 0xffffffff)) + 0xfcefa3f8;
        uVar2 = (uVar2 >> 0x17 | uVar2 * 0x200) + uVar1;
        uVar3 = iStack_84 + uVar3 + (uVar2 & uVar4 | uVar1 & (uVar4 ^ 0xffffffff)) + 0x676f02d9;
        uVar3 = (uVar3 >> 0x12 | uVar3 * 0x4000) + uVar2;
        uVar4 = iStack_70 + uVar4 + (uVar3 & uVar1 | uVar2 & (uVar1 ^ 0xffffffff)) + 0x8d2a4c8a;
        uVar4 = (uVar4 >> 0xc | uVar4 * 0x100000) + uVar3;
        uVar1 = (iStack_8c + uVar1 + (uVar3 ^ uVar2 ^ uVar4)) - 0x5c6be;
        uVar1 = (uVar1 >> 0x1c | uVar1 * 0x10) + uVar4;
        uVar2 = iStack_80 + uVar2 + (uVar4 ^ uVar3 ^ uVar1) + 0x8771f681;
        uVar2 = (uVar2 >> 0x15 | uVar2 * 0x800) + uVar1;
        uVar3 = iStack_74 + uVar3 + (uVar1 ^ uVar4 ^ uVar2) + 0x6d9d6122;
        uVar3 = (uVar3 >> 0x10 | uVar3 * 0x10000) + uVar2;
        uVar4 = iStack_68 + uVar4 + (uVar2 ^ uVar1 ^ uVar3) + 0xfde5380c;
        uVar4 = (uVar4 >> 9 | uVar4 * 0x800000) + uVar3;
        uVar1 = iStack_9c + uVar1 + (uVar3 ^ uVar2 ^ uVar4) + 0xa4beea44;
        uVar1 = (uVar1 >> 0x1c | uVar1 * 0x10) + uVar4;
        uVar2 = iStack_90 + uVar2 + (uVar4 ^ uVar3 ^ uVar1) + 0x4bdecfa9;
        uVar2 = (uVar2 >> 0x15 | uVar2 * 0x800) + uVar1;
        uVar3 = iStack_84 + uVar3 + (uVar1 ^ uVar4 ^ uVar2) + 0xf6bb4b60;
        uVar3 = (uVar3 >> 0x10 | uVar3 * 0x10000) + uVar2;
        uVar4 = iStack_78 + uVar4 + (uVar2 ^ uVar1 ^ uVar3) + 0xbebfbc70;
        uVar4 = (uVar4 >> 9 | uVar4 * 0x800000) + uVar3;
        uVar1 = iStack_6c + uVar1 + (uVar3 ^ uVar2 ^ uVar4) + 0x289b7ec6;
        uVar1 = (uVar1 >> 0x1c | uVar1 * 0x10) + uVar4;
        uVar2 = iStack_a0 + uVar2 + (uVar4 ^ uVar3 ^ uVar1) + 0xeaa127fa;
        uVar2 = (uVar2 >> 0x15 | uVar2 * 0x800) + uVar1;
        uVar3 = iStack_94 + uVar3 + (uVar1 ^ uVar4 ^ uVar2) + 0xd4ef3085;
        uVar3 = (uVar3 >> 0x10 | uVar3 * 0x10000) + uVar2;
        uVar4 = iStack_88 + uVar4 + (uVar2 ^ uVar1 ^ uVar3) + 0x4881d05;
        uVar4 = (uVar4 >> 9 | uVar4 * 0x800000) + uVar3;
        uVar1 = iStack_7c + uVar1 + (uVar3 ^ uVar2 ^ uVar4) + 0xd9d4d039;
        uVar1 = (uVar1 >> 0x1c | uVar1 * 0x10) + uVar4;
        uVar2 = iStack_70 + uVar2 + (uVar4 ^ uVar3 ^ uVar1) + 0xe6db99e5;
        uVar2 = (uVar2 >> 0x15 | uVar2 * 0x800) + uVar1;
        uVar3 = iStack_64 + uVar3 + (uVar1 ^ uVar4 ^ uVar2) + 0x1fa27cf8;
        uVar3 = (uVar3 >> 0x10 | uVar3 * 0x10000) + uVar2;
        uVar4 = iStack_98 + uVar4 + (uVar2 ^ uVar1 ^ uVar3) + 0xc4ac5665;
        uVar4 = (uVar4 >> 9 | uVar4 * 0x800000) + uVar3;
        uVar1 = iStack_a0 + uVar1 + ((uVar4 | uVar2 ^ 0xffffffff) ^ uVar3) + 0xf4292244;
        uVar1 = (uVar1 >> 0x1a | uVar1 * 0x40) + uVar4;
        uVar2 = iStack_84 + uVar2 + ((uVar1 | uVar3 ^ 0xffffffff) ^ uVar4) + 0x432aff97;
        uVar2 = (uVar2 >> 0x16 | uVar2 * 0x400) + uVar1;
        uVar3 = iStack_68 + uVar3 + ((uVar2 | uVar4 ^ 0xffffffff) ^ uVar1) + 0xab9423a7;
        uVar3 = (uVar3 >> 0x11 | uVar3 * 0x8000) + uVar2;
        uVar4 = iStack_8c + uVar4 + ((uVar3 | uVar1 ^ 0xffffffff) ^ uVar2) + 0xfc93a039;
        uVar4 = (uVar4 >> 0xb | uVar4 * 0x200000) + uVar3;
        uVar1 = iStack_70 + uVar1 + ((uVar4 | uVar2 ^ 0xffffffff) ^ uVar3) + 0x655b59c3;
        uVar1 = (uVar1 >> 0x1a | uVar1 * 0x40) + uVar4;
        uVar2 = iStack_94 + uVar2 + ((uVar1 | uVar3 ^ 0xffffffff) ^ uVar4) + 0x8f0ccc92;
        uVar2 = (uVar2 >> 0x16 | uVar2 * 0x400) + uVar1;
        uVar3 = (iStack_78 + uVar3 + ((uVar2 | uVar4 ^ 0xffffffff) ^ uVar1)) - 0x100b83;
        uVar3 = (uVar3 >> 0x11 | uVar3 * 0x8000) + uVar2;
        uVar4 = iStack_9c + uVar4 + ((uVar3 | uVar1 ^ 0xffffffff) ^ uVar2) + 0x85845dd1;
        uVar4 = (uVar4 >> 0xb | uVar4 * 0x200000) + uVar3;
        uVar1 = iStack_80 + uVar1 + ((uVar4 | uVar2 ^ 0xffffffff) ^ uVar3) + 0x6fa87e4f;
        uVar1 = (uVar1 >> 0x1a | uVar1 * 0x40) + uVar4;
        uVar2 = iStack_64 + uVar2 + ((uVar1 | uVar3 ^ 0xffffffff) ^ uVar4) + 0xfe2ce6e0;
        uVar2 = (uVar2 >> 0x16 | uVar2 * 0x400) + uVar1;
        uVar3 = iStack_88 + uVar3 + ((uVar2 | uVar4 ^ 0xffffffff) ^ uVar1) + 0xa3014314;
        uVar3 = (uVar3 >> 0x11 | uVar3 * 0x8000) + uVar2;
        uVar4 = iStack_6c + uVar4 + ((uVar3 | uVar1 ^ 0xffffffff) ^ uVar2) + 0x4e0811a1;
        uVar4 = (uVar4 >> 0xb | uVar4 * 0x200000) + uVar3;
        uVar1 = iStack_90 + uVar1 + ((uVar4 | uVar2 ^ 0xffffffff) ^ uVar3) + 0xf7537e82;
        uVar1 = (uVar1 >> 0x1a | uVar1 * 0x40) + uVar4;
        uVar2 = iStack_74 + uVar2 + ((uVar1 | uVar3 ^ 0xffffffff) ^ uVar4) + 0xbd3af235;
        uVar2 = (uVar2 >> 0x16 | uVar2 * 0x400) + uVar1;
        uVar3 = iStack_98 + uVar3 + ((uVar2 | uVar4 ^ 0xffffffff) ^ uVar1) + 0x2ad7d2bb;
        uVar3 = (uVar3 >> 0x11 | uVar3 * 0x8000) + uVar2;
        iVar7 = uVar1 + iVar7;
        uVar1 = iStack_7c + uVar4 + ((uVar3 | uVar1 ^ 0xffffffff) ^ uVar2) + 0xeb86d391;
        uVar6 = uVar3 + uVar6;
        uVar8 = uVar2 + uVar8;
        uVar5 = uVar3 + uVar5 + (uVar1 >> 0xb | uVar1 * 0x200000);
        param_5 = param_5 + 8;
      }
      *param_3 = iVar7;
      param_3[1] = uVar5;
      param_3[2] = uVar6;
      param_3[3] = uVar8;
      return 0x10;
    }
  }
  return 0;
}

// ==== Aska::Hash::MD5(Aska::IStream*, unsigned long, char*, unsigned long)
// vaddr 0x1f87780 | ghidra 0x2087780 | size 2872 | symbol _ZN4Aska4Hash3MD5EPNS_7IStreamEmPcm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Hash3MD5EPNS_7IStreamEmPcm
               (long *param_1,long *param_2,long param_3,int *param_4,ulong param_5)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ulong uVar5;
  long lVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  ulong uVar12;
  long lVar13;
  undefined1 auStack_130 [64];
  int iStack_f0;
  int iStack_ec;
  int iStack_e8;
  int iStack_e4;
  int iStack_e0;
  int iStack_dc;
  int iStack_d8;
  int iStack_d4;
  int iStack_d0;
  int iStack_cc;
  int iStack_c8;
  int iStack_c4;
  int iStack_c0;
  int iStack_bc;
  int iStack_b8;
  int iStack_b4;
  long lStack_b0;
  undefined1 auStack_a8 [72];
  
  if (param_5 < 0x10) {
    *param_1 = -0x3bf;
  }
  else {
    memset(auStack_a8,0,0x48);
    uVar8 = 0x10325476;
    iVar10 = 0x67452301;
    uVar9 = 0x98badcfe;
    uVar11 = 0xefcdab89;
    if (param_3 == 0) {
      param_3 = (**(code **)(*param_2 + 0x60))(param_2);
    }
    uVar12 = param_3 + 0x48U >> 6;
    auStack_a8[0] = 0x80;
    *(long *)((long)&lStack_b0 + ((param_3 + 0x48U & 0xffffffffffffffc0) - param_3)) = param_3 << 3;
    if (uVar12 != 0) {
      iVar7 = 0;
      lVar13 = 0;
      do {
        uVar5 = (**(code **)(*param_2 + 0x28))(param_2,auStack_130,1,0x40);
        if (uVar5 != 0x40) {
          lVar6 = (**(code **)(*param_2 + 0x50))(param_2);
          *param_1 = lVar6;
          if (lVar6 != -0x3c1) {
            return;
          }
          if (uVar5 < 0x40) {
            memcpy(auStack_130 + uVar5,auStack_a8 + iVar7,0x40 - uVar5);
            iVar7 = (iVar7 + 0x40) - (int)uVar5;
          }
        }
        iStack_f0 = (int)auStack_130._0_8_;
        iStack_ec = SUB84(auStack_130._0_8_,4);
        uVar1 = iVar10 + (uVar11 & uVar9 | uVar8 & (uVar11 ^ 0xffffffff)) + iStack_f0 + 0xd76aa478;
        uVar1 = (uVar1 >> 0x19 | uVar1 * 0x80) + uVar11;
        iStack_e8 = (int)auStack_130._8_8_;
        iStack_e4 = SUB84(auStack_130._8_8_,4);
        uVar2 = uVar8 + iStack_ec + (uVar1 & uVar11 | uVar9 & (uVar1 ^ 0xffffffff)) + 0xe8c7b756;
        uVar2 = (uVar2 >> 0x14 | uVar2 * 0x1000) + uVar1;
        iStack_e0 = (int)auStack_130._16_8_;
        iStack_dc = SUB84(auStack_130._16_8_,4);
        uVar3 = uVar9 + iStack_e8 + (uVar2 & uVar1 | uVar11 & (uVar2 ^ 0xffffffff)) + 0x242070db;
        uVar3 = (uVar3 >> 0xf | uVar3 * 0x20000) + uVar2;
        uVar4 = uVar11 + iStack_e4 + (uVar3 & uVar2 | uVar1 & (uVar3 ^ 0xffffffff)) + 0xc1bdceee;
        uVar4 = (uVar4 >> 10 | uVar4 * 0x400000) + uVar3;
        iStack_d8 = (int)auStack_130._24_8_;
        iStack_d4 = SUB84(auStack_130._24_8_,4);
        uVar1 = iStack_e0 + uVar1 + (uVar4 & uVar3 | uVar2 & (uVar4 ^ 0xffffffff)) + 0xf57c0faf;
        uVar1 = (uVar1 >> 0x19 | uVar1 * 0x80) + uVar4;
        uVar2 = iStack_dc + uVar2 + (uVar1 & uVar4 | uVar3 & (uVar1 ^ 0xffffffff)) + 0x4787c62a;
        uVar2 = (uVar2 >> 0x14 | uVar2 * 0x1000) + uVar1;
        iStack_d0 = (int)auStack_130._32_8_;
        iStack_cc = SUB84(auStack_130._32_8_,4);
        uVar3 = iStack_d8 + uVar3 + (uVar2 & uVar1 | uVar4 & (uVar2 ^ 0xffffffff)) + 0xa8304613;
        uVar3 = (uVar3 >> 0xf | uVar3 * 0x20000) + uVar2;
        uVar4 = iStack_d4 + uVar4 + (uVar3 & uVar2 | uVar1 & (uVar3 ^ 0xffffffff)) + 0xfd469501;
        uVar4 = (uVar4 >> 10 | uVar4 * 0x400000) + uVar3;
        iStack_c8 = (int)auStack_130._40_8_;
        iStack_c4 = SUB84(auStack_130._40_8_,4);
        uVar1 = iStack_d0 + uVar1 + (uVar4 & uVar3 | uVar2 & (uVar4 ^ 0xffffffff)) + 0x698098d8;
        uVar1 = (uVar1 >> 0x19 | uVar1 * 0x80) + uVar4;
        uVar2 = iStack_cc + uVar2 + (uVar1 & uVar4 | uVar3 & (uVar1 ^ 0xffffffff)) + 0x8b44f7af;
        uVar2 = (uVar2 >> 0x14 | uVar2 * 0x1000) + uVar1;
        iStack_c0 = (int)auStack_130._48_8_;
        iStack_bc = SUB84(auStack_130._48_8_,4);
        uVar3 = (iStack_c8 + uVar3 + (uVar2 & uVar1 | uVar4 & (uVar2 ^ 0xffffffff))) - 0xa44f;
        uVar3 = (uVar3 >> 0xf | uVar3 * 0x20000) + uVar2;
        uVar4 = iStack_c4 + uVar4 + (uVar3 & uVar2 | uVar1 & (uVar3 ^ 0xffffffff)) + 0x895cd7be;
        uVar4 = (uVar4 >> 10 | uVar4 * 0x400000) + uVar3;
        iStack_b8 = (int)auStack_130._56_8_;
        iStack_b4 = SUB84(auStack_130._56_8_,4);
        uVar1 = iStack_c0 + uVar1 + (uVar4 & uVar3 | uVar2 & (uVar4 ^ 0xffffffff)) + 0x6b901122;
        uVar1 = (uVar1 >> 0x19 | uVar1 * 0x80) + uVar4;
        uVar2 = iStack_bc + uVar2 + (uVar1 & uVar4 | uVar3 & (uVar1 ^ 0xffffffff)) + 0xfd987193;
        uVar2 = (uVar2 >> 0x14 | uVar2 * 0x1000) + uVar1;
        uVar3 = iStack_b8 + uVar3 + (uVar2 & uVar1 | uVar4 & (uVar2 ^ 0xffffffff)) + 0xa679438e;
        uVar3 = (uVar3 >> 0xf | uVar3 * 0x20000) + uVar2;
        uVar4 = iStack_b4 + uVar4 + (uVar3 & uVar2 | uVar1 & (uVar3 ^ 0xffffffff)) + 0x49b40821;
        uVar4 = (uVar4 >> 10 | uVar4 * 0x400000) + uVar3;
        uVar1 = iStack_ec + uVar1 + (uVar4 & uVar2 | uVar3 & (uVar2 ^ 0xffffffff)) + 0xf61e2562;
        uVar1 = (uVar1 >> 0x1b | uVar1 * 0x20) + uVar4;
        uVar2 = iStack_d8 + uVar2 + (uVar1 & uVar3 | uVar4 & (uVar3 ^ 0xffffffff)) + 0xc040b340;
        uVar2 = (uVar2 >> 0x17 | uVar2 * 0x200) + uVar1;
        uVar3 = iStack_c4 + uVar3 + (uVar2 & uVar4 | uVar1 & (uVar4 ^ 0xffffffff)) + 0x265e5a51;
        uVar3 = (uVar3 >> 0x12 | uVar3 * 0x4000) + uVar2;
        uVar4 = iStack_f0 + uVar4 + (uVar3 & uVar1 | uVar2 & (uVar1 ^ 0xffffffff)) + 0xe9b6c7aa;
        uVar4 = (uVar4 >> 0xc | uVar4 * 0x100000) + uVar3;
        uVar1 = iStack_dc + uVar1 + (uVar4 & uVar2 | uVar3 & (uVar2 ^ 0xffffffff)) + 0xd62f105d;
        uVar1 = (uVar1 >> 0x1b | uVar1 * 0x20) + uVar4;
        uVar2 = iStack_c8 + uVar2 + (uVar1 & uVar3 | uVar4 & (uVar3 ^ 0xffffffff)) + 0x2441453;
        uVar2 = (uVar2 >> 0x17 | uVar2 * 0x200) + uVar1;
        uVar3 = iStack_b4 + uVar3 + (uVar2 & uVar4 | uVar1 & (uVar4 ^ 0xffffffff)) + 0xd8a1e681;
        uVar3 = (uVar3 >> 0x12 | uVar3 * 0x4000) + uVar2;
        uVar4 = iStack_e0 + uVar4 + (uVar3 & uVar1 | uVar2 & (uVar1 ^ 0xffffffff)) + 0xe7d3fbc8;
        uVar4 = (uVar4 >> 0xc | uVar4 * 0x100000) + uVar3;
        uVar1 = iStack_cc + uVar1 + (uVar4 & uVar2 | uVar3 & (uVar2 ^ 0xffffffff)) + 0x21e1cde6;
        uVar1 = (uVar1 >> 0x1b | uVar1 * 0x20) + uVar4;
        uVar2 = iStack_b8 + uVar2 + (uVar1 & uVar3 | uVar4 & (uVar3 ^ 0xffffffff)) + 0xc33707d6;
        uVar2 = (uVar2 >> 0x17 | uVar2 * 0x200) + uVar1;
        uVar3 = iStack_e4 + uVar3 + (uVar2 & uVar4 | uVar1 & (uVar4 ^ 0xffffffff)) + 0xf4d50d87;
        uVar3 = (uVar3 >> 0x12 | uVar3 * 0x4000) + uVar2;
        uVar4 = iStack_d0 + uVar4 + (uVar3 & uVar1 | uVar2 & (uVar1 ^ 0xffffffff)) + 0x455a14ed;
        uVar4 = (uVar4 >> 0xc | uVar4 * 0x100000) + uVar3;
        uVar1 = iStack_bc + uVar1 + (uVar4 & uVar2 | uVar3 & (uVar2 ^ 0xffffffff)) + 0xa9e3e905;
        uVar1 = (uVar1 >> 0x1b | uVar1 * 0x20) + uVar4;
        uVar2 = iStack_e8 + uVar2 + (uVar1 & uVar3 | uVar4 & (uVar3 ^ 0xffffffff)) + 0xfcefa3f8;
        uVar2 = (uVar2 >> 0x17 | uVar2 * 0x200) + uVar1;
        uVar3 = iStack_d4 + uVar3 + (uVar2 & uVar4 | uVar1 & (uVar4 ^ 0xffffffff)) + 0x676f02d9;
        uVar3 = (uVar3 >> 0x12 | uVar3 * 0x4000) + uVar2;
        uVar4 = iStack_c0 + uVar4 + (uVar3 & uVar1 | uVar2 & (uVar1 ^ 0xffffffff)) + 0x8d2a4c8a;
        uVar4 = (uVar4 >> 0xc | uVar4 * 0x100000) + uVar3;
        uVar1 = (iStack_dc + uVar1 + (uVar3 ^ uVar2 ^ uVar4)) - 0x5c6be;
        uVar1 = (uVar1 >> 0x1c | uVar1 * 0x10) + uVar4;
        uVar2 = iStack_d0 + uVar2 + (uVar4 ^ uVar3 ^ uVar1) + 0x8771f681;
        uVar2 = (uVar2 >> 0x15 | uVar2 * 0x800) + uVar1;
        uVar3 = iStack_c4 + uVar3 + (uVar1 ^ uVar4 ^ uVar2) + 0x6d9d6122;
        uVar3 = (uVar3 >> 0x10 | uVar3 * 0x10000) + uVar2;
        uVar4 = iStack_b8 + uVar4 + (uVar2 ^ uVar1 ^ uVar3) + 0xfde5380c;
        uVar4 = (uVar4 >> 9 | uVar4 * 0x800000) + uVar3;
        uVar1 = iStack_ec + uVar1 + (uVar3 ^ uVar2 ^ uVar4) + 0xa4beea44;
        uVar1 = (uVar1 >> 0x1c | uVar1 * 0x10) + uVar4;
        uVar2 = iStack_e0 + uVar2 + (uVar4 ^ uVar3 ^ uVar1) + 0x4bdecfa9;
        uVar2 = (uVar2 >> 0x15 | uVar2 * 0x800) + uVar1;
        uVar3 = iStack_d4 + uVar3 + (uVar1 ^ uVar4 ^ uVar2) + 0xf6bb4b60;
        uVar3 = (uVar3 >> 0x10 | uVar3 * 0x10000) + uVar2;
        uVar4 = iStack_c8 + uVar4 + (uVar2 ^ uVar1 ^ uVar3) + 0xbebfbc70;
        uVar4 = (uVar4 >> 9 | uVar4 * 0x800000) + uVar3;
        uVar1 = iStack_bc + uVar1 + (uVar3 ^ uVar2 ^ uVar4) + 0x289b7ec6;
        uVar1 = (uVar1 >> 0x1c | uVar1 * 0x10) + uVar4;
        uVar2 = iStack_f0 + uVar2 + (uVar4 ^ uVar3 ^ uVar1) + 0xeaa127fa;
        uVar2 = (uVar2 >> 0x15 | uVar2 * 0x800) + uVar1;
        uVar3 = iStack_e4 + uVar3 + (uVar1 ^ uVar4 ^ uVar2) + 0xd4ef3085;
        uVar3 = (uVar3 >> 0x10 | uVar3 * 0x10000) + uVar2;
        uVar4 = iStack_d8 + uVar4 + (uVar2 ^ uVar1 ^ uVar3) + 0x4881d05;
        uVar4 = (uVar4 >> 9 | uVar4 * 0x800000) + uVar3;
        uVar1 = iStack_cc + uVar1 + (uVar3 ^ uVar2 ^ uVar4) + 0xd9d4d039;
        uVar1 = (uVar1 >> 0x1c | uVar1 * 0x10) + uVar4;
        uVar2 = iStack_c0 + uVar2 + (uVar4 ^ uVar3 ^ uVar1) + 0xe6db99e5;
        uVar2 = (uVar2 >> 0x15 | uVar2 * 0x800) + uVar1;
        uVar3 = iStack_b4 + uVar3 + (uVar1 ^ uVar4 ^ uVar2) + 0x1fa27cf8;
        uVar3 = (uVar3 >> 0x10 | uVar3 * 0x10000) + uVar2;
        uVar4 = iStack_e8 + uVar4 + (uVar2 ^ uVar1 ^ uVar3) + 0xc4ac5665;
        uVar4 = (uVar4 >> 9 | uVar4 * 0x800000) + uVar3;
        uVar1 = iStack_f0 + uVar1 + ((uVar4 | uVar2 ^ 0xffffffff) ^ uVar3) + 0xf4292244;
        uVar1 = (uVar1 >> 0x1a | uVar1 * 0x40) + uVar4;
        uVar2 = iStack_d4 + uVar2 + ((uVar1 | uVar3 ^ 0xffffffff) ^ uVar4) + 0x432aff97;
        uVar2 = (uVar2 >> 0x16 | uVar2 * 0x400) + uVar1;
        uVar3 = iStack_b8 + uVar3 + ((uVar2 | uVar4 ^ 0xffffffff) ^ uVar1) + 0xab9423a7;
        uVar3 = (uVar3 >> 0x11 | uVar3 * 0x8000) + uVar2;
        uVar4 = iStack_dc + uVar4 + ((uVar3 | uVar1 ^ 0xffffffff) ^ uVar2) + 0xfc93a039;
        uVar4 = (uVar4 >> 0xb | uVar4 * 0x200000) + uVar3;
        uVar1 = iStack_c0 + uVar1 + ((uVar4 | uVar2 ^ 0xffffffff) ^ uVar3) + 0x655b59c3;
        uVar1 = (uVar1 >> 0x1a | uVar1 * 0x40) + uVar4;
        uVar2 = iStack_e4 + uVar2 + ((uVar1 | uVar3 ^ 0xffffffff) ^ uVar4) + 0x8f0ccc92;
        uVar2 = (uVar2 >> 0x16 | uVar2 * 0x400) + uVar1;
        uVar3 = (iStack_c8 + uVar3 + ((uVar2 | uVar4 ^ 0xffffffff) ^ uVar1)) - 0x100b83;
        uVar3 = (uVar3 >> 0x11 | uVar3 * 0x8000) + uVar2;
        uVar4 = iStack_ec + uVar4 + ((uVar3 | uVar1 ^ 0xffffffff) ^ uVar2) + 0x85845dd1;
        uVar4 = (uVar4 >> 0xb | uVar4 * 0x200000) + uVar3;
        uVar1 = iStack_d0 + uVar1 + ((uVar4 | uVar2 ^ 0xffffffff) ^ uVar3) + 0x6fa87e4f;
        uVar1 = (uVar1 >> 0x1a | uVar1 * 0x40) + uVar4;
        uVar2 = iStack_b4 + uVar2 + ((uVar1 | uVar3 ^ 0xffffffff) ^ uVar4) + 0xfe2ce6e0;
        uVar2 = (uVar2 >> 0x16 | uVar2 * 0x400) + uVar1;
        uVar3 = iStack_d8 + uVar3 + ((uVar2 | uVar4 ^ 0xffffffff) ^ uVar1) + 0xa3014314;
        uVar3 = (uVar3 >> 0x11 | uVar3 * 0x8000) + uVar2;
        uVar4 = iStack_bc + uVar4 + ((uVar3 | uVar1 ^ 0xffffffff) ^ uVar2) + 0x4e0811a1;
        uVar4 = (uVar4 >> 0xb | uVar4 * 0x200000) + uVar3;
        uVar1 = iStack_e0 + uVar1 + ((uVar4 | uVar2 ^ 0xffffffff) ^ uVar3) + 0xf7537e82;
        uVar1 = (uVar1 >> 0x1a | uVar1 * 0x40) + uVar4;
        uVar2 = iStack_c4 + uVar2 + ((uVar1 | uVar3 ^ 0xffffffff) ^ uVar4) + 0xbd3af235;
        uVar2 = (uVar2 >> 0x16 | uVar2 * 0x400) + uVar1;
        uVar3 = iStack_e8 + uVar3 + ((uVar2 | uVar4 ^ 0xffffffff) ^ uVar1) + 0x2ad7d2bb;
        uVar3 = (uVar3 >> 0x11 | uVar3 * 0x8000) + uVar2;
        iVar10 = uVar1 + iVar10;
        uVar9 = uVar3 + uVar9;
        uVar1 = iStack_cc + uVar4 + ((uVar3 | uVar1 ^ 0xffffffff) ^ uVar2) + 0xeb86d391;
        lVar13 = lVar13 + 1;
        uVar11 = uVar3 + uVar11 + (uVar1 >> 0xb | uVar1 * 0x200000);
        uVar8 = uVar2 + uVar8;
      } while (lVar13 < (long)uVar12);
    }
    *param_4 = iVar10;
    param_4[1] = uVar11;
    param_4[2] = uVar9;
    param_4[3] = uVar8;
    *param_1 = 0;
  }
  return;
}

// ==== Aska::Hash::RSA_SHA1(Aska::Cryption::BigNumber const&, Aska::Cryption::BigNumber const&, char const*, unsigned long, char*, unsigned long, char*, unsigned long)
// vaddr 0x1f882b8 | ghidra 0x20882b8 | size 112 | symbol _ZN4Aska4Hash8RSA_SHA1ERKNS_8Cryption9BigNumberES4_PKcmPcmS7_m | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Hash8RSA_SHA1ERKNS_8Cryption9BigNumberES4_PKcmPcmS7_m
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               long param_5,long param_6,undefined8 param_7,undefined8 param_8)

{
  long lVar1;
  undefined1 auStack_28 [8];
  
  lVar1 = Aska::Hash::SHA1(char const*, unsigned long, char*, unsigned long, char*, unsigned long)(param_3,param_4,param_5,0x14,param_7,param_8);
  if (lVar1 != 0) {
    Aska::Cryption::RSA::DoCalc(char const*, unsigned long, char*, unsigned long, Aska::Cryption::BigNumber const&, Aska::Cryption::BigNumber const&)(auStack_28,param_5,0x14,param_5 + 0x14,param_6 + -0x14,param_2,param_1);
  }
  return;
}

// ==== Aska::Hash::CRC(unsigned char const*, unsigned long, unsigned short*)
// vaddr 0x1f88328 | ghidra 0x2088328 | size 88 | symbol _ZN4Aska4Hash3CRCEPKhmPt | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4Hash3CRCEPKhmPt(long param_1,ulong param_2,ushort *param_3)

{
  ulong uVar1;
  ushort uVar2;
  ulong uVar3;
  uint uVar4;
  ulong uVar5;
  
  uVar2 = 0;
  if ((param_2 != 0) && (param_1 != 0)) {
    uVar4 = 0xffff;
    uVar1 = 1;
    uVar5 = 0;
    do {
      uVar3 = uVar1;
      uVar4 = uVar4 >> 8 ^
              (uint)*(ushort *)
                     (&UNK_02972808 + (ulong)(uVar4 & 0xff ^ (uint)*(byte *)(param_1 + uVar5)) * 2);
      uVar1 = (ulong)((int)uVar3 + 1);
      uVar5 = uVar3;
    } while (uVar3 < param_2);
    uVar2 = ~(ushort)uVar4;
  }
  *param_3 = uVar2;
  return 2;
}

// ==== Aska::Hash::CRC(Aska::IStream*, unsigned long, unsigned short*, void*, unsigned long)
// vaddr 0x1f88380 | ghidra 0x2088380 | size 236 | symbol _ZN4Aska4Hash3CRCEPNS_7IStreamEmPtPvm | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska4Hash3CRCEPNS_7IStreamEmPtPvm
          (long *param_1,undefined8 param_2,ushort *param_3,long param_4,long param_5)

{
  short sVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  ushort auStack_34 [2];
  
  if ((param_1 == (long *)0x0) ||
     (uVar2 = (**(code **)(*param_1 + 0x10))(param_1), (uVar2 & 1) == 0)) {
    return 0;
  }
  if ((param_4 == 0) || (param_5 == 0)) {
    param_5 = 0x1000;
    lVar4 = operator new[](unsigned long, std::nothrow_t const&)(0x1000,PTR__ZSt7nothrow_02cb9a80);
    param_4 = lVar4;
    if (lVar4 != 0) goto code_r0x020883f4;
  }
  else {
    lVar4 = 0;
code_r0x020883f4:
    auStack_34[0] = 0xffff;
    sVar1 = TSharedCRC<unsigned short>::Calc(Aska::IStream*, unsigned long, unsigned short*, unsigned short const*, unsigned char*, unsigned long)(param_1,param_2,auStack_34,&UNK_02972808,param_4,param_5);
    if (sVar1 == 2) {
      auStack_34[0] = ~auStack_34[0];
      *param_3 = auStack_34[0];
      uVar3 = 2;
      goto joined_r0x02088448;
    }
  }
  uVar3 = 0;
joined_r0x02088448:
  if (lVar4 != 0) {
    operator delete[](void*)(lVar4);
  }
  return uVar3;
}

// ==== Aska::Hash::CRC(Aska::IStream*, unsigned long, unsigned int*, void*, unsigned long)
// vaddr 0x1f88770 | ghidra 0x2088770 | size 232 | symbol _ZN4Aska4Hash3CRCEPNS_7IStreamEmPjPvm | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska4Hash3CRCEPNS_7IStreamEmPjPvm
          (long *param_1,undefined8 param_2,uint *param_3,long param_4,long param_5)

{
  int iVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  uint uStack_34;
  
  if ((param_1 == (long *)0x0) ||
     (uVar2 = (**(code **)(*param_1 + 0x10))(param_1), (uVar2 & 1) == 0)) {
    return 0;
  }
  if ((param_4 == 0) || (param_5 == 0)) {
    param_5 = 0x1000;
    lVar4 = operator new[](unsigned long, std::nothrow_t const&)(0x1000,PTR__ZSt7nothrow_02cb9a80);
    param_4 = lVar4;
    if (lVar4 != 0) goto code_r0x020887e4;
  }
  else {
    lVar4 = 0;
code_r0x020887e4:
    uStack_34 = 0xffffffff;
    iVar1 = TSharedCRC<unsigned int>::Calc(Aska::IStream*, unsigned long, unsigned int*, unsigned int const*, unsigned char*, unsigned long)(param_1,param_2,&uStack_34,&UNK_02972a08,param_4,param_5);
    if (iVar1 == 4) {
      uStack_34 = ~uStack_34;
      *param_3 = uStack_34;
      uVar3 = 4;
      goto joined_r0x02088834;
    }
  }
  uVar3 = 0;
joined_r0x02088834:
  if (lVar4 != 0) {
    operator delete[](void*)(lVar4);
  }
  return uVar3;
}

// ==== Aska::Hash::CRC(unsigned char const*, unsigned long, unsigned int*)
// vaddr 0x1f88b50 | ghidra 0x2088b50 | size 84 | symbol _ZN4Aska4Hash3CRCEPKhmPj | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska4Hash3CRCEPKhmPj(long param_1,ulong param_2,uint *param_3)

{
  ulong uVar1;
  uint uVar2;
  ulong uVar3;
  ulong uVar4;
  
  uVar2 = 0;
  if ((param_2 != 0) && (param_1 != 0)) {
    uVar2 = 0xffffffff;
    uVar1 = 1;
    uVar4 = 0;
    do {
      uVar3 = uVar1;
      uVar2 = *(uint *)(&UNK_02972a08 + (ulong)(uVar2 & 0xff ^ (uint)*(byte *)(param_1 + uVar4)) * 4
                       ) ^ uVar2 >> 8;
      uVar1 = (ulong)((int)uVar3 + 1);
      uVar4 = uVar3;
    } while (uVar3 < param_2);
    uVar2 = ~uVar2;
  }
  *param_3 = uVar2;
  return 4;
}

// ==== Aska::Hash::_SHA1_DEFAULT(Aska::IStream*, unsigned long, char*, unsigned long)
// vaddr 0x1f88ba4 | ghidra 0x2088ba4 | size 3116 | symbol _ZN4Aska4Hash13_SHA1_DEFAULTEPNS_7IStreamEmPcm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Hash13_SHA1_DEFAULTEPNS_7IStreamEmPcm
               (long *param_1,long *param_2,ulong param_3,uint *param_4,ulong param_5)

{
  int *piVar1;
  long lVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint3 uVar6;
  ulong uVar7;
  long lVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  ulong uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  ulong uVar21;
  ulong uVar22;
  int iStack_27c;
  undefined1 auStack_230 [64];
  undefined8 uStack_1f0;
  undefined8 uStack_1e8;
  undefined8 uStack_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  uint auStack_1b0 [66];
  undefined1 auStack_a8 [72];
  
  if (param_5 < 0x14) {
    *param_1 = -0x3bf;
  }
  else {
    memset(auStack_a8,0,0x48);
    if (param_3 == 0) {
      param_3 = (**(code **)(*param_2 + 0x60))(param_2);
    }
    uVar13 = param_3 + 0x41 & 0xffffffffffffffc0;
    lVar8 = (uVar13 - param_3) + -8;
    uVar16 = 0x10325476;
    uVar19 = 0x67452301;
    uVar17 = 0x98badcfe;
    uVar18 = 0xc3d2e1f0;
    uVar20 = 0xefcdab89;
    if (lVar8 < 1) {
      uVar13 = uVar13 + 0x40;
      lVar8 = (-8 - param_3) + uVar13;
    }
    auStack_a8[0] = 0x80;
    uVar4 = (uint)(param_3 >> 0x20);
    auStack_a8[lVar8 + 1] = (char)(uVar4 >> 0xd);
    auStack_a8[lVar8 + 2] = (char)(uVar4 >> 5);
    auStack_a8[lVar8 + 3] = (char)(param_3 >> 0x1d);
    auStack_a8[lVar8] = (char)(uVar4 >> 0x15);
    auStack_a8[lVar8 + 4] = (char)(param_3 >> 0x15);
    auStack_a8[lVar8 + 5] = (char)(param_3 >> 0xd);
    auStack_a8[lVar8 + 6] = (char)(param_3 >> 5);
    auStack_a8[lVar8 + 7] = (char)(param_3 << 3);
    if (uVar13 != 0) {
      uVar21 = 0;
      iStack_27c = 0;
      do {
        uVar7 = (**(code **)(*param_2 + 0x28))(param_2,auStack_230,1,0x40);
        if (uVar7 != 0x40) {
          lVar8 = (**(code **)(*param_2 + 0x50))(param_2);
          *param_1 = lVar8;
          if (lVar8 != -0x3c1) {
            return;
          }
          if (uVar7 < 0x40) {
            memcpy(auStack_230 + uVar7,auStack_a8 + iStack_27c,0x40 - uVar7);
            iStack_27c = (iStack_27c + 0x40) - (int)uVar7;
          }
        }
        uVar6 = CONCAT12(SUB81(auStack_230._0_8_,4),(short)auStack_230._0_8_) & 0xff00ff;
        uVar22 = CONCAT62((uint6)SUB81(auStack_230._24_8_,4) << 0x10,(short)auStack_230._24_8_) &
                 0xffffffff00ff;
        uVar7 = CONCAT62((uint6)SUB81(auStack_230._56_8_,4) << 0x10,(short)auStack_230._56_8_) &
                0xffffffff00ff;
        uStack_1e8 = CONCAT17(SUB81(auStack_230._8_8_,4),
                              CONCAT16(SUB81(auStack_230._8_8_,5),
                                       CONCAT15(SUB81(auStack_230._8_8_,6),
                                                CONCAT14(SUB81(auStack_230._8_8_,7),
                                                         CONCAT13((char)auStack_230._8_8_,
                                                                  CONCAT12(SUB81(auStack_230._8_8_,1
                                                                                ),CONCAT11(SUB81(
                                                  auStack_230._8_8_,2),SUB81(auStack_230._8_8_,3))))
                                                  ))));
        uStack_1f0 = CONCAT17((char)(uVar6 >> 0x10),
                              CONCAT16(SUB81(auStack_230._0_8_,5),
                                       CONCAT15(SUB81(auStack_230._0_8_,6),
                                                CONCAT14(SUB81(auStack_230._0_8_,7),
                                                         CONCAT13((char)uVar6,
                                                                  CONCAT12(SUB81(auStack_230._0_8_,1
                                                                                ),CONCAT11(SUB81(
                                                  auStack_230._0_8_,2),SUB81(auStack_230._0_8_,3))))
                                                  ))));
        uStack_1d8 = CONCAT17((char)(uVar22 >> 0x20),
                              CONCAT16(SUB81(auStack_230._24_8_,5),
                                       CONCAT15(SUB81(auStack_230._24_8_,6),
                                                CONCAT14(SUB81(auStack_230._24_8_,7),
                                                         CONCAT13((char)uVar22,
                                                                  CONCAT12(SUB81(auStack_230._24_8_,
                                                                                 1),CONCAT11(SUB81(
                                                  auStack_230._24_8_,2),SUB81(auStack_230._24_8_,3))
                                                  ))))));
        uStack_1e0 = CONCAT17(SUB81(auStack_230._16_8_,4),
                              CONCAT16(SUB81(auStack_230._16_8_,5),
                                       CONCAT15(SUB81(auStack_230._16_8_,6),
                                                CONCAT14(SUB81(auStack_230._16_8_,7),
                                                         CONCAT13((char)auStack_230._16_8_,
                                                                  CONCAT12(SUB81(auStack_230._16_8_,
                                                                                 1),CONCAT11(SUB81(
                                                  auStack_230._16_8_,2),SUB81(auStack_230._16_8_,3))
                                                  ))))));
        uStack_1c8 = CONCAT17(SUB81(auStack_230._40_8_,4),
                              CONCAT16(SUB81(auStack_230._40_8_,5),
                                       CONCAT15(SUB81(auStack_230._40_8_,6),
                                                CONCAT14(SUB81(auStack_230._40_8_,7),
                                                         CONCAT13((char)auStack_230._40_8_,
                                                                  CONCAT12(SUB81(auStack_230._40_8_,
                                                                                 1),CONCAT11(SUB81(
                                                  auStack_230._40_8_,2),SUB81(auStack_230._40_8_,3))
                                                  ))))));
        uStack_1d0 = CONCAT17(SUB81(auStack_230._32_8_,4),
                              CONCAT16(SUB81(auStack_230._32_8_,5),
                                       CONCAT15(SUB81(auStack_230._32_8_,6),
                                                CONCAT14(SUB81(auStack_230._32_8_,7),
                                                         CONCAT13((char)auStack_230._32_8_,
                                                                  CONCAT12(SUB81(auStack_230._32_8_,
                                                                                 1),CONCAT11(SUB81(
                                                  auStack_230._32_8_,2),SUB81(auStack_230._32_8_,3))
                                                  ))))));
        uStack_1b8 = CONCAT17((char)(uVar7 >> 0x20),
                              CONCAT16(SUB81(auStack_230._56_8_,5),
                                       CONCAT15(SUB81(auStack_230._56_8_,6),
                                                CONCAT14(SUB81(auStack_230._56_8_,7),
                                                         CONCAT13((char)uVar7,
                                                                  CONCAT12(SUB81(auStack_230._56_8_,
                                                                                 1),CONCAT11(SUB81(
                                                  auStack_230._56_8_,2),SUB81(auStack_230._56_8_,3))
                                                  ))))));
        uStack_1c0 = CONCAT17(SUB81(auStack_230._48_8_,4),
                              CONCAT16(SUB81(auStack_230._48_8_,5),
                                       CONCAT15(SUB81(auStack_230._48_8_,6),
                                                CONCAT14(SUB81(auStack_230._48_8_,7),
                                                         CONCAT13((char)auStack_230._48_8_,
                                                                  CONCAT12(SUB81(auStack_230._48_8_,
                                                                                 1),CONCAT11(SUB81(
                                                  auStack_230._48_8_,2),SUB81(auStack_230._48_8_,3))
                                                  ))))));
        lVar8 = 0;
        do {
          lVar2 = lVar8 + 4;
          uVar4 = *(uint *)((long)&uStack_1d0 + lVar8) ^ *(uint *)((long)&uStack_1c0 + lVar8 + 4) ^
                  *(uint *)((long)&uStack_1e8 + lVar8) ^ *(uint *)((long)&uStack_1f0 + lVar8);
          *(uint *)((long)auStack_1b0 + lVar8) = uVar4 >> 0x1f | uVar4 << 1;
          lVar8 = lVar2;
        } while (lVar2 != 0x100);
        lVar8 = 0;
        uVar14 = uVar20;
        uVar9 = uVar18;
        uVar5 = uVar16;
        uVar15 = uVar17;
        uVar4 = uVar19;
        do {
          uVar11 = uVar4;
          uVar10 = uVar15;
          uVar12 = uVar5;
          piVar1 = (int *)((long)&uStack_1f0 + lVar8);
          uVar15 = uVar14 >> 2 | uVar14 << 0x1e;
          lVar8 = lVar8 + 4;
          uVar4 = uVar9 + (uVar14 & uVar10 | uVar12 & (uVar14 ^ 0xffffffff)) +
                  (uVar11 >> 0x1b | uVar11 << 5) + *piVar1 + 0x5a827999;
          uVar14 = uVar11;
          uVar9 = uVar12;
          uVar5 = uVar10;
        } while (lVar8 != 0x50);
        uVar9 = uVar11 >> 2 | uVar11 << 0x1e;
        uVar5 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar14 = uVar12 + (uVar15 ^ uVar10 ^ uVar11) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[4] + 0x6ed9eba1;
        uVar4 = uVar10 + (uVar9 ^ uVar15 ^ uVar4) + (uVar14 >> 0x1b | uVar14 * 0x20) +
                auStack_1b0[5] + 0x6ed9eba1;
        uVar10 = uVar14 >> 2 | uVar14 * 0x40000000;
        uVar11 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar15 = uVar15 + (uVar5 ^ uVar9 ^ uVar14) + (uVar4 >> 0x1b | uVar4 * 0x20) + auStack_1b0[6]
                 + 0x6ed9eba1;
        uVar4 = uVar9 + (uVar10 ^ uVar5 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) + auStack_1b0[7]
                + 0x6ed9eba1;
        uVar14 = uVar15 >> 2 | uVar15 * 0x40000000;
        uVar15 = uVar5 + (uVar11 ^ uVar10 ^ uVar15) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[8] + 0x6ed9eba1;
        uVar9 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar4 = uVar10 + (uVar14 ^ uVar11 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                auStack_1b0[9] + 0x6ed9eba1;
        uVar5 = uVar15 >> 2 | uVar15 * 0x40000000;
        uVar15 = uVar11 + (uVar9 ^ uVar14 ^ uVar15) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[10] + 0x6ed9eba1;
        uVar10 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar4 = uVar14 + (uVar5 ^ uVar9 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                auStack_1b0[0xb] + 0x6ed9eba1;
        uVar14 = uVar15 >> 2 | uVar15 * 0x40000000;
        uVar15 = uVar9 + (uVar10 ^ uVar5 ^ uVar15) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[0xc] + 0x6ed9eba1;
        uVar9 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar4 = uVar5 + (uVar14 ^ uVar10 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                auStack_1b0[0xd] + 0x6ed9eba1;
        uVar5 = uVar15 >> 2 | uVar15 * 0x40000000;
        uVar15 = uVar10 + (uVar9 ^ uVar14 ^ uVar15) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[0xe] + 0x6ed9eba1;
        uVar10 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar4 = uVar14 + (uVar5 ^ uVar9 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                auStack_1b0[0xf] + 0x6ed9eba1;
        uVar14 = uVar15 >> 2 | uVar15 * 0x40000000;
        uVar15 = uVar9 + (uVar10 ^ uVar5 ^ uVar15) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[0x10] + 0x6ed9eba1;
        uVar9 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar4 = uVar5 + (uVar14 ^ uVar10 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                auStack_1b0[0x11] + 0x6ed9eba1;
        uVar5 = uVar15 >> 2 | uVar15 * 0x40000000;
        uVar15 = uVar10 + (uVar9 ^ uVar14 ^ uVar15) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[0x12] + 0x6ed9eba1;
        uVar10 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar4 = uVar14 + (uVar5 ^ uVar9 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                auStack_1b0[0x13] + 0x6ed9eba1;
        uVar14 = uVar15 >> 2 | uVar15 * 0x40000000;
        uVar15 = uVar9 + (uVar10 ^ uVar5 ^ uVar15) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[0x14] + 0x6ed9eba1;
        uVar9 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar4 = uVar5 + (uVar14 ^ uVar10 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                auStack_1b0[0x15] + 0x6ed9eba1;
        uVar5 = uVar15 >> 2 | uVar15 * 0x40000000;
        uVar15 = uVar10 + (uVar9 ^ uVar14 ^ uVar15) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[0x16] + 0x6ed9eba1;
        lVar8 = 0;
        uVar14 = uVar14 + (uVar5 ^ uVar9 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                 auStack_1b0[0x17] + 0x6ed9eba1;
        uVar4 = uVar4 >> 2 | uVar4 * 0x40000000;
        do {
          uVar12 = uVar4;
          uVar11 = uVar14;
          uVar10 = uVar5;
          lVar2 = lVar8 + 0x60;
          uVar4 = uVar15 >> 2 | uVar15 << 0x1e;
          lVar8 = lVar8 + 4;
          iVar3 = uVar9 + (uVar15 & (uVar12 | uVar10) | uVar12 & uVar10) +
                  (uVar11 >> 0x1b | uVar11 << 5) + *(int *)((long)auStack_1b0 + lVar2);
          uVar14 = iVar3 + 0x8f1bbcdc;
          uVar9 = uVar10;
          uVar5 = uVar12;
          uVar15 = uVar11;
        } while (lVar8 != 0x50);
        uVar9 = uVar11 >> 2 | uVar11 << 0x1e;
        uVar15 = uVar10 + (uVar4 ^ uVar12 ^ uVar11) + (uVar14 >> 0x1b | uVar14 * 0x20) +
                 auStack_1b0[0x2c] + 0xca62c1d6;
        uVar5 = uVar14 >> 2 | iVar3 * 0x40000000;
        uVar14 = uVar12 + (uVar9 ^ uVar4 ^ uVar14) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                 auStack_1b0[0x2d] + 0xca62c1d6;
        uVar10 = uVar15 >> 2 | uVar15 * 0x40000000;
        uVar4 = uVar4 + (uVar5 ^ uVar9 ^ uVar15) + (uVar14 >> 0x1b | uVar14 * 0x20) +
                auStack_1b0[0x2e] + 0xca62c1d6;
        uVar11 = uVar14 >> 2 | uVar14 * 0x40000000;
        uVar15 = uVar9 + (uVar10 ^ uVar5 ^ uVar14) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[0x2f] + 0xca62c1d6;
        uVar14 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar4 = uVar5 + (uVar11 ^ uVar10 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                auStack_1b0[0x30] + 0xca62c1d6;
        uVar9 = uVar15 >> 2 | uVar15 * 0x40000000;
        uVar15 = uVar10 + (uVar14 ^ uVar11 ^ uVar15) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[0x31] + 0xca62c1d6;
        uVar5 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar4 = uVar11 + (uVar9 ^ uVar14 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                auStack_1b0[0x32] + 0xca62c1d6;
        uVar10 = uVar15 >> 2 | uVar15 * 0x40000000;
        uVar15 = uVar14 + (uVar5 ^ uVar9 ^ uVar15) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[0x33] + 0xca62c1d6;
        uVar14 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar4 = uVar9 + (uVar10 ^ uVar5 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                auStack_1b0[0x34] + 0xca62c1d6;
        uVar9 = uVar15 >> 2 | uVar15 * 0x40000000;
        uVar15 = uVar5 + (uVar14 ^ uVar10 ^ uVar15) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[0x35] + 0xca62c1d6;
        uVar5 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar4 = uVar10 + (uVar9 ^ uVar14 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                auStack_1b0[0x36] + 0xca62c1d6;
        uVar10 = uVar15 >> 2 | uVar15 * 0x40000000;
        uVar15 = uVar14 + (uVar5 ^ uVar9 ^ uVar15) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[0x37] + 0xca62c1d6;
        uVar14 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar4 = uVar9 + (uVar10 ^ uVar5 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                auStack_1b0[0x38] + 0xca62c1d6;
        uVar9 = uVar15 >> 2 | uVar15 * 0x40000000;
        uVar15 = uVar5 + (uVar14 ^ uVar10 ^ uVar15) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[0x39] + 0xca62c1d6;
        uVar5 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar4 = uVar10 + (uVar9 ^ uVar14 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                auStack_1b0[0x3a] + 0xca62c1d6;
        uVar10 = uVar15 >> 2 | uVar15 * 0x40000000;
        uVar15 = uVar14 + (uVar5 ^ uVar9 ^ uVar15) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[0x3b] + 0xca62c1d6;
        uVar14 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar4 = uVar9 + (uVar10 ^ uVar5 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                auStack_1b0[0x3c] + 0xca62c1d6;
        uVar9 = uVar15 >> 2 | uVar15 * 0x40000000;
        uVar11 = uVar4 >> 2 | uVar4 * 0x40000000;
        uVar15 = uVar5 + (uVar14 ^ uVar10 ^ uVar15) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[0x3d] + 0xca62c1d6;
        uVar16 = uVar11 + uVar16;
        uVar17 = (uVar15 >> 2 | uVar15 * 0x40000000) + uVar17;
        uVar4 = uVar10 + (uVar9 ^ uVar14 ^ uVar4) + (uVar15 >> 0x1b | uVar15 * 0x20) +
                auStack_1b0[0x3e] + 0xca62c1d6;
        uVar21 = (ulong)((int)uVar21 + 0x40);
        uVar20 = uVar4 + uVar20;
        uVar19 = uVar14 + (uVar11 ^ uVar9 ^ uVar15) + (uVar4 >> 0x1b | uVar4 * 0x20) +
                 auStack_1b0[0x3f] + uVar19 + 0xca62c1d6;
        uVar18 = uVar9 + uVar18;
      } while (uVar21 < uVar13);
    }
    uVar19 = (uVar19 & 0xff00ff00) >> 8 | (uVar19 & 0xff00ff) << 8;
    uVar20 = (uVar20 & 0xff00ff00) >> 8 | (uVar20 & 0xff00ff) << 8;
    uVar17 = (uVar17 & 0xff00ff00) >> 8 | (uVar17 & 0xff00ff) << 8;
    uVar16 = (uVar16 & 0xff00ff00) >> 8 | (uVar16 & 0xff00ff) << 8;
    uVar18 = (uVar18 & 0xff00ff00) >> 8 | (uVar18 & 0xff00ff) << 8;
    *param_4 = uVar19 >> 0x10 | uVar19 << 0x10;
    param_4[1] = uVar20 >> 0x10 | uVar20 << 0x10;
    param_4[2] = uVar17 >> 0x10 | uVar17 << 0x10;
    param_4[3] = uVar16 >> 0x10 | uVar16 << 0x10;
    param_4[4] = uVar18 >> 0x10 | uVar18 << 0x10;
    *param_1 = 0;
  }
  return;
}

// ==== Aska::Hash::SHA1(Aska::IStream*, unsigned long, char*, unsigned long)
// vaddr 0x1f897d0 | ghidra 0x20897d0 | size 4 | symbol _ZN4Aska4Hash4SHA1EPNS_7IStreamEmPcm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4Hash4SHA1EPNS_7IStreamEmPcm(void)

{
  (*(code *)PTR__ZN4Aska4Hash13_SHA1_DEFAULTEPNS_7IStreamEmPcm_02ca90e0)();
  return;
}
