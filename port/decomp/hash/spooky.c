// port/decomp/hash/spooky.c: Ghidra decompiles for the hash subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:07 UTC: tools/decomp.sh '--into' 'hash/spooky' 'Aska::detail::SpookyHashV2::'

// ==== Aska::detail::SpookyHashV2::Short(void const*, unsigned long, unsigned long*, unsigned long*)
// vaddr 0x1f8b154 | ghidra 0x208b154 | size 1108 | symbol _ZN4Aska6detail12SpookyHashV25ShortEPKvmPmS4_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6detail12SpookyHashV25ShortEPKvmPmS4_
               (uint *param_1,ulong param_2,ulong *param_3,ulong *param_4)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  long lStack_10;
  
  uVar5 = *param_3;
  uVar6 = *param_4;
  uVar9 = param_2 & 0x1f;
  if (param_2 < 0x10) {
    uVar7 = 0xdeadbeefdeadbeef;
    uVar10 = 0xdeadbeefdeadbeef;
  }
  else {
    puVar3 = (uint *)((long)param_1 + (param_2 & 0xffffffffffffffe0));
    if (param_1 < puVar3) {
      uVar10 = 0xdeadbeefdeadbeef;
      uVar7 = 0xdeadbeefdeadbeef;
      do {
        puVar1 = param_1 + 4;
        uVar10 = *(long *)(param_1 + 2) + uVar10;
        uVar7 = uVar10 + (*(long *)param_1 + uVar7 >> 0xe | *(long *)param_1 + uVar7 << 0x32);
        uVar5 = uVar7 ^ uVar5;
        uVar10 = (uVar10 >> 0xc | uVar10 << 0x34) + uVar5;
        uVar6 = uVar10 ^ uVar6;
        puVar2 = param_1 + 6;
        uVar5 = (uVar5 >> 0x22 | uVar5 << 0x1e) + uVar6;
        uVar7 = uVar5 ^ uVar7;
        uVar6 = (uVar6 >> 0x17 | uVar6 << 0x29) + uVar7;
        uVar10 = uVar6 ^ uVar10;
        uVar7 = (uVar7 >> 10 | uVar7 << 0x36) + uVar10;
        uVar5 = uVar7 ^ uVar5;
        uVar10 = (uVar10 >> 0x10 | uVar10 << 0x30) + uVar5;
        uVar6 = uVar10 ^ uVar6;
        uVar5 = (uVar5 >> 0x1a | uVar5 << 0x26) + uVar6;
        uVar7 = uVar5 ^ uVar7;
        uVar6 = (uVar6 >> 0x1b | uVar6 << 0x25) + uVar7;
        uVar10 = uVar6 ^ uVar10;
        uVar7 = (uVar7 >> 2 | uVar7 << 0x3e) + uVar10;
        uVar5 = uVar7 ^ uVar5;
        uVar10 = (uVar10 >> 0x1e | uVar10 << 0x22) + uVar5;
        uVar6 = uVar10 ^ uVar6;
        uVar5 = (uVar5 >> 0x3b | uVar5 << 5) + uVar6;
        uVar7 = uVar5 ^ uVar7;
        uVar6 = (uVar6 >> 0x1c | uVar6 << 0x24) + uVar7;
        param_1 = param_1 + 8;
        uVar10 = uVar6 ^ uVar10;
        uVar5 = uVar5 + *(long *)puVar1;
        uVar6 = *(long *)puVar2 + uVar6;
      } while (param_1 < puVar3);
    }
    else {
      uVar7 = 0xdeadbeefdeadbeef;
      uVar10 = 0xdeadbeefdeadbeef;
    }
    if (0xf < uVar9) {
      uVar9 = uVar9 - 0x10;
      lVar4 = *(long *)param_1;
      puVar3 = param_1 + 2;
      param_1 = param_1 + 4;
      uVar10 = *(long *)puVar3 + uVar10;
      uVar7 = uVar10 + (lVar4 + uVar7 >> 0xe | lVar4 + uVar7 << 0x32);
      uVar5 = uVar7 ^ uVar5;
      uVar10 = (uVar10 >> 0xc | uVar10 << 0x34) + uVar5;
      uVar6 = uVar10 ^ uVar6;
      uVar5 = (uVar5 >> 0x22 | uVar5 << 0x1e) + uVar6;
      uVar7 = uVar5 ^ uVar7;
      uVar6 = (uVar6 >> 0x17 | uVar6 << 0x29) + uVar7;
      uVar10 = uVar6 ^ uVar10;
      uVar7 = (uVar7 >> 10 | uVar7 << 0x36) + uVar10;
      uVar5 = uVar7 ^ uVar5;
      uVar10 = (uVar10 >> 0x10 | uVar10 << 0x30) + uVar5;
      uVar6 = uVar10 ^ uVar6;
      uVar5 = (uVar5 >> 0x1a | uVar5 << 0x26) + uVar6;
      uVar7 = uVar5 ^ uVar7;
      uVar6 = (uVar6 >> 0x1b | uVar6 << 0x25) + uVar7;
      uVar10 = uVar6 ^ uVar10;
      uVar7 = (uVar7 >> 2 | uVar7 << 0x3e) + uVar10;
      uVar5 = uVar7 ^ uVar5;
      uVar10 = (uVar10 >> 0x1e | uVar10 << 0x22) + uVar5;
      uVar6 = uVar10 ^ uVar6;
      uVar5 = (uVar5 >> 0x3b | uVar5 << 5) + uVar6;
      uVar7 = uVar5 ^ uVar7;
      uVar6 = (uVar6 >> 0x1c | uVar6 << 0x24) + uVar7;
      uVar10 = uVar6 ^ uVar10;
    }
  }
  uVar10 = uVar10 + (param_2 << 0x38);
  switch(uVar9) {
  case 0:
    uVar7 = uVar7 + 0xdeadbeefdeadbeef;
    uVar10 = uVar10 + 0xdeadbeefdeadbeef;
    break;
  case 3:
    uVar7 = uVar7 + (ulong)*(byte *)((long)param_1 + 2) * 0x10000;
  case 2:
    uVar7 = uVar7 + (ulong)*(byte *)((long)param_1 + 1) * 0x100;
  case 1:
    uVar7 = uVar7 + (byte)*param_1;
    break;
  case 7:
    uVar7 = uVar7 + ((ulong)*(byte *)((long)param_1 + 6) << 0x30);
  case 6:
    uVar7 = uVar7 + ((ulong)*(byte *)((long)param_1 + 5) << 0x28);
  case 5:
    uVar7 = uVar7 + ((ulong)(byte)param_1[1] << 0x20);
  case 4:
    uVar7 = uVar7 + *param_1;
    break;
  case 0xb:
    uVar10 = uVar10 + (ulong)*(byte *)((long)param_1 + 10) * 0x10000;
  case 10:
    uVar10 = uVar10 + (ulong)*(byte *)((long)param_1 + 9) * 0x100;
  case 9:
    uVar10 = uVar10 + (byte)param_1[2];
  case 8:
    lStack_10 = *(long *)param_1;
    goto code_r0x0208b50c;
  case 0xf:
    uVar10 = uVar10 + ((ulong)*(byte *)((long)param_1 + 0xe) << 0x30);
  case 0xe:
    uVar10 = uVar10 + ((ulong)*(byte *)((long)param_1 + 0xd) << 0x28);
  case 0xd:
    uVar10 = uVar10 + ((ulong)(byte)param_1[3] << 0x20);
  case 0xc:
    lStack_10 = *(long *)param_1;
    uVar10 = uVar10 + param_1[2];
code_r0x0208b50c:
    uVar7 = lStack_10 + uVar7;
  }
  uVar8 = uVar7 >> 0x31 | uVar7 << 0xf;
  uVar9 = (uVar10 ^ uVar7) + uVar8;
  uVar7 = uVar9 >> 0xc | uVar9 << 0x34;
  uVar5 = uVar7 + (uVar9 ^ uVar5);
  uVar9 = uVar5 >> 0x26 | uVar5 * 0x4000000;
  uVar5 = uVar9 + (uVar5 ^ uVar6);
  uVar10 = uVar5 >> 0xd | uVar5 << 0x33;
  uVar5 = uVar10 + (uVar5 ^ uVar8);
  uVar8 = uVar5 >> 0x24 | uVar5 * 0x10000000;
  uVar5 = uVar8 + (uVar5 ^ uVar7);
  uVar7 = uVar5 >> 0x37 | uVar5 * 0x200;
  uVar5 = uVar7 + (uVar5 ^ uVar9);
  uVar6 = uVar5 >> 0x11 | uVar5 << 0x2f;
  uVar5 = uVar6 + (uVar5 ^ uVar10);
  uVar9 = uVar5 >> 10 | uVar5 << 0x36;
  uVar5 = uVar9 + (uVar5 ^ uVar8);
  uVar5 = (uVar5 >> 0x20 | uVar5 << 0x20) + (uVar5 ^ uVar7);
  uVar5 = (uVar5 >> 0x27 | uVar5 * 0x2000000) + (uVar5 ^ uVar6);
  uVar6 = uVar5 >> 1 | uVar5 << 0x3f;
  *param_3 = uVar6;
  *param_4 = uVar6 + (uVar5 ^ uVar9);
  return;
}

// ==== Aska::detail::SpookyHashV2::Hash128(void const*, unsigned long, unsigned long*, unsigned long*)
// vaddr 0x1f8b5a8 | ghidra 0x208b5a8 | size 988 | symbol _ZN4Aska6detail12SpookyHashV27Hash128EPKvmPmS4_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6detail12SpookyHashV27Hash128EPKvmPmS4_
               (ulong param_1,ulong param_2,ulong *param_3,ulong *param_4)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  ulong uVar13;
  ulong uVar14;
  ulong uVar15;
  ulong uVar16;
  ulong uVar17;
  ulong uVar18;
  ulong uVar19;
  long lStack_120;
  long lStack_118;
  long lStack_110;
  long lStack_108;
  long lStack_100;
  long lStack_f8;
  long lStack_f0;
  long lStack_e8;
  long lStack_e0;
  long lStack_d8;
  long lStack_d0;
  undefined7 uStack_c8;
  long lStack_c0;
  ulong uStack_b8;
  ulong uStack_b0;
  long lStack_a8;
  ulong uStack_a0;
  ulong uStack_98;
  long lStack_90;
  ulong uStack_88;
  ulong uStack_80;
  long lStack_78;
  ulong uStack_70;
  ulong uStack_68;
  
  if (0xbf < param_2) {
    uStack_b0 = *param_3;
    lStack_a8 = -0x2152411021524111;
    lStack_90 = -0x2152411021524111;
    uStack_b8 = *param_4;
    uVar19 = param_1 + (param_2 / 0x60) * 0x60;
    lStack_c0 = -0x2152411021524111;
    lStack_78 = -0x2152411021524111;
    uStack_a0 = uStack_b8;
    uStack_98 = uStack_b0;
    uStack_88 = uStack_b8;
    uStack_80 = uStack_b0;
    uStack_70 = uStack_b8;
    uStack_68 = uStack_b0;
    if (param_1 < uVar19) {
      uVar7 = param_1;
      do {
        Aska::detail::SpookyHashV2::Mix(unsigned long const*, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&)(uVar7,&uStack_68,&uStack_70,&lStack_78,&uStack_80,&uStack_88,&lStack_90,
                        &uStack_98,&uStack_a0,&lStack_a8,&uStack_b0,&uStack_b8,&lStack_c0);
        uVar7 = uVar7 + 0x60;
      } while (uVar7 < uVar19);
    }
    uVar6 = uStack_68;
    uVar7 = uStack_70;
    lVar5 = lStack_78;
    uVar10 = uStack_80;
    uVar9 = uStack_88;
    lVar4 = lStack_90;
    uVar12 = uStack_98;
    uVar13 = uStack_a0;
    lVar3 = lStack_a8;
    uVar15 = uStack_b0;
    uVar17 = uStack_b8;
    lVar2 = lStack_c0;
    lVar1 = (param_1 - uVar19) + param_2;
    memcpy(&lStack_120,uVar19,lVar1);
    memset((long)&lStack_120 + lVar1,0,0x60 - lVar1);
    uVar7 = uVar7 + lStack_118;
    uVar19 = uVar7 + lVar2 + CONCAT17((char)lVar1,uStack_c8);
    uVar8 = lVar5 + lStack_110 ^ uVar19;
    uVar6 = uVar6 + lStack_120 + uVar8;
    uVar10 = uVar10 + lStack_108 ^ uVar6;
    uVar7 = (uVar7 >> 0x14 | uVar7 << 0x2c) + uVar10;
    uVar11 = uVar9 + lStack_100 ^ uVar7;
    uVar9 = (uVar8 >> 0x31 | uVar8 << 0xf) + uVar11;
    uVar8 = lVar4 + lStack_f8 ^ uVar9;
    uVar10 = (uVar10 >> 0x1e | uVar10 << 0x22) + uVar8;
    uVar14 = uVar12 + lStack_f0 ^ uVar10;
    uVar12 = (uVar11 >> 0x2b | uVar11 << 0x15) + uVar14;
    uVar11 = uVar13 + lStack_e8 ^ uVar12;
    uVar13 = (uVar8 >> 0x1a | uVar8 << 0x26) + uVar11;
    uVar16 = lVar3 + lStack_e0 ^ uVar13;
    uVar8 = (uVar14 >> 0x1f | uVar14 << 0x21) + uVar16;
    uVar14 = uVar15 + lStack_d8 ^ uVar8;
    uVar15 = (uVar11 >> 0x36 | uVar11 << 10) + uVar14;
    uVar18 = uVar17 + lStack_d0 ^ uVar15;
    uVar17 = (uVar16 >> 0x33 | uVar16 << 0xd) + uVar18;
    uVar19 = uVar19 ^ uVar17;
    uVar11 = (uVar14 >> 0x1a | uVar14 << 0x26) + uVar19;
    uVar6 = uVar6 ^ uVar11;
    uVar14 = (uVar18 >> 0xb | uVar18 << 0x35) + uVar6;
    uVar7 = uVar7 ^ uVar14;
    uVar19 = (uVar19 >> 0x16 | uVar19 << 0x2a) + uVar7;
    uVar9 = uVar9 ^ uVar19;
    uVar6 = (uVar6 >> 10 | uVar6 << 0x36) + uVar9;
    uVar10 = uVar10 ^ uVar6;
    uVar7 = (uVar7 >> 0x14 | uVar7 << 0x2c) + uVar10;
    uVar12 = uVar12 ^ uVar7;
    uVar9 = (uVar9 >> 0x31 | uVar9 << 0xf) + uVar12;
    uVar13 = uVar13 ^ uVar9;
    uVar10 = (uVar10 >> 0x1e | uVar10 << 0x22) + uVar13;
    uVar8 = uVar8 ^ uVar10;
    uVar12 = (uVar12 >> 0x2b | uVar12 << 0x15) + uVar8;
    uVar15 = uVar15 ^ uVar12;
    uVar13 = (uVar13 >> 0x1a | uVar13 << 0x26) + uVar15;
    uVar17 = uVar17 ^ uVar13;
    uVar8 = (uVar8 >> 0x1f | uVar8 << 0x21) + uVar17;
    uVar11 = uVar11 ^ uVar8;
    uVar15 = (uVar15 >> 0x36 | uVar15 << 10) + uVar11;
    uVar14 = uVar14 ^ uVar15;
    uVar17 = (uVar17 >> 0x33 | uVar17 << 0xd) + uVar14;
    uVar19 = uVar19 ^ uVar17;
    uVar11 = (uVar11 >> 0x1a | uVar11 << 0x26) + uVar19;
    uVar6 = uVar6 ^ uVar11;
    uVar14 = (uVar14 >> 0xb | uVar14 << 0x35) + uVar6;
    uVar7 = uVar7 ^ uVar14;
    uVar19 = (uVar19 >> 0x16 | uVar19 << 0x2a) + uVar7;
    uVar9 = uVar9 ^ uVar19;
    uVar6 = (uVar6 >> 10 | uVar6 << 0x36) + uVar9;
    uVar10 = uVar10 ^ uVar6;
    uVar7 = (uVar7 >> 0x14 | uVar7 << 0x2c) + uVar10;
    uVar12 = uVar12 ^ uVar7;
    uVar13 = uVar13 ^ (uVar9 >> 0x31 | uVar9 << 0xf) + uVar12;
    uVar8 = uVar8 ^ (uVar10 >> 0x1e | uVar10 << 0x22) + uVar13;
    uVar15 = uVar15 ^ (uVar12 >> 0x2b | uVar12 << 0x15) + uVar8;
    uVar17 = uVar17 ^ (uVar13 >> 0x1a | uVar13 << 0x26) + uVar15;
    uVar11 = uVar11 ^ (uVar8 >> 0x1f | uVar8 << 0x21) + uVar17;
    uVar14 = uVar14 ^ (uVar15 >> 0x36 | uVar15 << 10) + uVar11;
    uVar6 = uVar6 ^ (uVar11 >> 0x1a | uVar11 << 0x26) +
                    (uVar19 ^ (uVar17 >> 0x33 | uVar17 << 0xd) + uVar14);
    *param_3 = uVar6 >> 10 | uVar6 << 0x36;
    *param_4 = uVar7 ^ (uVar14 >> 0xb | uVar14 << 0x35) + uVar6;
    return;
  }
  (*(code *)PTR__ZN4Aska6detail12SpookyHashV25ShortEPKvmPmS4__02c99218)(param_1,param_2);
  return;
}

// ==== Aska::detail::SpookyHashV2::Mix(unsigned long const*, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&)
// vaddr 0x1f8b984 | ghidra 0x208b984 | size 1324 | symbol _ZN4Aska6detail12SpookyHashV23MixEPKmRmS4_S4_S4_S4_S4_S4_S4_S4_S4_S4_S4_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6detail12SpookyHashV23MixEPKmRmS4_S4_S4_S4_S4_S4_S4_S4_S4_S4_S4_
               (long *param_1,ulong *param_2,ulong *param_3,ulong *param_4,ulong *param_5,
               ulong *param_6,ulong *param_7,ulong *param_8,ulong *param_9,ulong *param_10,
               ulong *param_11,ulong *param_12,ulong *param_13)

{
  *param_2 = *param_2 + *param_1;
  *param_4 = *param_4 ^ *param_12;
  *param_13 = *param_13 ^ *param_2;
  *param_2 = *param_2 >> 0x35 | *param_2 << 0xb;
  *param_13 = *param_13 + *param_3;
  *param_3 = *param_3 + param_1[1];
  *param_5 = *param_5 ^ *param_13;
  *param_2 = *param_2 ^ *param_3;
  *param_3 = *param_3 >> 0x20 | *param_3 << 0x20;
  *param_2 = *param_2 + *param_4;
  *param_4 = *param_4 + param_1[2];
  *param_6 = *param_6 ^ *param_2;
  *param_3 = *param_3 ^ *param_4;
  *param_4 = *param_4 >> 0x15 | *param_4 << 0x2b;
  *param_3 = *param_3 + *param_5;
  *param_5 = *param_5 + param_1[3];
  *param_7 = *param_7 ^ *param_3;
  *param_4 = *param_4 ^ *param_5;
  *param_5 = *param_5 >> 0x21 | *param_5 << 0x1f;
  *param_4 = *param_4 + *param_6;
  *param_6 = *param_6 + param_1[4];
  *param_8 = *param_8 ^ *param_4;
  *param_5 = *param_5 ^ *param_6;
  *param_6 = *param_6 >> 0x2f | *param_6 << 0x11;
  *param_5 = *param_5 + *param_7;
  *param_7 = *param_7 + param_1[5];
  *param_9 = *param_9 ^ *param_5;
  *param_6 = *param_6 ^ *param_7;
  *param_7 = *param_7 >> 0x24 | *param_7 << 0x1c;
  *param_6 = *param_6 + *param_8;
  *param_8 = *param_8 + param_1[6];
  *param_10 = *param_10 ^ *param_6;
  *param_7 = *param_7 ^ *param_8;
  *param_8 = *param_8 >> 0x19 | *param_8 << 0x27;
  *param_7 = *param_7 + *param_9;
  *param_9 = *param_9 + param_1[7];
  *param_11 = *param_11 ^ *param_7;
  *param_8 = *param_8 ^ *param_9;
  *param_9 = *param_9 >> 7 | *param_9 << 0x39;
  *param_8 = *param_8 + *param_10;
  *param_10 = *param_10 + param_1[8];
  *param_12 = *param_12 ^ *param_8;
  *param_9 = *param_9 ^ *param_10;
  *param_10 = *param_10 >> 9 | *param_10 << 0x37;
  *param_9 = *param_9 + *param_11;
  *param_11 = *param_11 + param_1[9];
  *param_13 = *param_13 ^ *param_9;
  *param_10 = *param_10 ^ *param_11;
  *param_11 = *param_11 >> 10 | *param_11 << 0x36;
  *param_10 = *param_10 + *param_12;
  *param_12 = *param_12 + param_1[10];
  *param_2 = *param_2 ^ *param_10;
  *param_11 = *param_11 ^ *param_12;
  *param_12 = *param_12 >> 0x2a | *param_12 << 0x16;
  *param_11 = *param_11 + *param_13;
  *param_13 = *param_13 + param_1[0xb];
  *param_3 = *param_3 ^ *param_11;
  *param_12 = *param_12 ^ *param_13;
  *param_13 = *param_13 >> 0x12 | *param_13 << 0x2e;
  *param_12 = *param_12 + *param_2;
  return;
}

// ==== Aska::detail::SpookyHashV2::Init(unsigned long, unsigned long)
// vaddr 0x1f8beb0 | ghidra 0x208beb0 | size 16 | symbol _ZN4Aska6detail12SpookyHashV24InitEmm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6detail12SpookyHashV24InitEmm(long param_1,undefined8 param_2,undefined8 param_3)

{
  *(undefined8 *)(param_1 + 0x120) = 0;
  *(undefined1 *)(param_1 + 0x128) = 0;
  *(undefined8 *)(param_1 + 0xc0) = param_2;
  *(undefined8 *)(param_1 + 200) = param_3;
  return;
}

// ==== Aska::detail::SpookyHashV2::Update(void const*, unsigned long)
// vaddr 0x1f8bec0 | ghidra 0x208bec0 | size 680 | symbol _ZN4Aska6detail12SpookyHashV26UpdateEPKvm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6detail12SpookyHashV26UpdateEPKvm(long param_1,ulong param_2,ulong param_3)

{
  byte bVar1;
  ulong uVar2;
  ulong uVar3;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  
  bVar1 = *(byte *)(param_1 + 0x128);
  uVar2 = (ulong)bVar1;
  if (uVar2 + param_3 < 0xc0) {
    memcpy(param_1 + uVar2,param_2,param_3);
    *(char *)(param_1 + 0x128) = (char)(uVar2 + param_3);
    *(ulong *)(param_1 + 0x120) = *(long *)(param_1 + 0x120) + param_3;
  }
  else {
    uStack_58 = *(undefined8 *)(param_1 + 0xc0);
    if (*(ulong *)(param_1 + 0x120) < 0xc0) {
      uStack_a8 = *(undefined8 *)(param_1 + 200);
      uStack_b0 = 0xdeadbeefdeadbeef;
      uStack_98 = 0xdeadbeefdeadbeef;
      uStack_80 = 0xdeadbeefdeadbeef;
      uStack_68 = 0xdeadbeefdeadbeef;
      uStack_a0 = uStack_58;
      uStack_90 = uStack_a8;
      uStack_88 = uStack_58;
      uStack_78 = uStack_a8;
      uStack_70 = uStack_58;
      uStack_60 = uStack_a8;
    }
    else {
      uStack_60 = *(undefined8 *)(param_1 + 200);
      uStack_68 = *(undefined8 *)(param_1 + 0xd0);
      uStack_70 = *(undefined8 *)(param_1 + 0xd8);
      uStack_78 = *(undefined8 *)(param_1 + 0xe0);
      uStack_80 = *(undefined8 *)(param_1 + 0xe8);
      uStack_88 = *(undefined8 *)(param_1 + 0xf0);
      uStack_90 = *(undefined8 *)(param_1 + 0xf8);
      uStack_98 = *(undefined8 *)(param_1 + 0x100);
      uStack_a0 = *(undefined8 *)(param_1 + 0x108);
      uStack_a8 = *(undefined8 *)(param_1 + 0x110);
      uStack_b0 = *(undefined8 *)(param_1 + 0x118);
    }
    *(ulong *)(param_1 + 0x120) = *(ulong *)(param_1 + 0x120) + param_3;
    if (bVar1 != 0) {
      uVar3 = (ulong)(byte)(0xc0 - bVar1);
      memcpy(param_1 + uVar2,param_2,uVar3);
      Aska::detail::SpookyHashV2::Mix(unsigned long const*, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&)(param_1,&uStack_58,&uStack_60,&uStack_68,&uStack_70,&uStack_78,&uStack_80,
                      &uStack_88,&uStack_90,&uStack_98,&uStack_a0,&uStack_a8,&uStack_b0);
      Aska::detail::SpookyHashV2::Mix(unsigned long const*, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&)(param_1 + 0x60,&uStack_58,&uStack_60,&uStack_68,&uStack_70,&uStack_78,
                      &uStack_80,&uStack_88,&uStack_90,&uStack_98,&uStack_a0,&uStack_a8,&uStack_b0);
      param_2 = param_2 + uVar3;
      param_3 = param_3 - uVar3;
    }
    uVar2 = param_2 + (param_3 / 0x60) * 0x60;
    param_3 = (param_2 - uVar2) + param_3;
    if (param_2 < uVar2) {
      do {
        Aska::detail::SpookyHashV2::Mix(unsigned long const*, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&)(param_2,&uStack_58,&uStack_60,&uStack_68,&uStack_70,&uStack_78,&uStack_80,
                        &uStack_88,&uStack_90,&uStack_98,&uStack_a0,&uStack_a8,&uStack_b0);
        param_2 = param_2 + 0x60;
      } while (param_2 < uVar2);
    }
    *(char *)(param_1 + 0x128) = (char)param_3;
    memcpy(param_1,uVar2,param_3 & 0xff);
    *(undefined8 *)(param_1 + 0xc0) = uStack_58;
    *(undefined8 *)(param_1 + 200) = uStack_60;
    *(undefined8 *)(param_1 + 0xd0) = uStack_68;
    *(undefined8 *)(param_1 + 0xd8) = uStack_70;
    *(undefined8 *)(param_1 + 0xe0) = uStack_78;
    *(undefined8 *)(param_1 + 0xe8) = uStack_80;
    *(undefined8 *)(param_1 + 0xf0) = uStack_88;
    *(undefined8 *)(param_1 + 0xf8) = uStack_90;
    *(undefined8 *)(param_1 + 0x100) = uStack_98;
    *(undefined8 *)(param_1 + 0x108) = uStack_a0;
    *(undefined8 *)(param_1 + 0x110) = uStack_a8;
    *(undefined8 *)(param_1 + 0x118) = uStack_b0;
  }
  return;
}

// ==== Aska::detail::SpookyHashV2::Final(unsigned long*, unsigned long*)
// vaddr 0x1f8c168 | ghidra 0x208c168 | size 892 | symbol _ZN4Aska6detail12SpookyHashV25FinalEPmS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6detail12SpookyHashV25FinalEPmS2_(long *param_1,ulong *param_2,ulong *param_3)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  ulong uVar13;
  ulong uVar14;
  ulong uVar15;
  ulong uVar16;
  ulong uVar17;
  ulong uVar18;
  ulong uVar19;
  ulong uVar20;
  ulong uVar21;
  ulong uVar22;
  ulong uVar23;
  ulong uVar24;
  byte bVar25;
  long lStack_c0;
  long lStack_b8;
  long lStack_b0;
  long lStack_a8;
  long lStack_a0;
  long lStack_98;
  long lStack_90;
  long lStack_88;
  long lStack_80;
  long lStack_78;
  long lStack_70;
  long lStack_68;
  
  if (0xbf < (ulong)param_1[0x24]) {
    lStack_68 = param_1[0x18];
    lStack_70 = param_1[0x19];
    bVar25 = *(byte *)(param_1 + 0x25);
    lStack_78 = param_1[0x1a];
    lStack_80 = param_1[0x1b];
    lStack_88 = param_1[0x1c];
    lStack_90 = param_1[0x1d];
    lStack_98 = param_1[0x1e];
    lStack_a0 = param_1[0x1f];
    lStack_a8 = param_1[0x20];
    lStack_b0 = param_1[0x21];
    lStack_b8 = param_1[0x22];
    lStack_c0 = param_1[0x23];
    if (0x5f < bVar25) {
      Aska::detail::SpookyHashV2::Mix(unsigned long const*, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&, unsigned long&)(param_1,&lStack_68,&lStack_70,&lStack_78,&lStack_80,&lStack_88,&lStack_90,
                      &lStack_98,&lStack_a0,&lStack_a8,&lStack_b0,&lStack_b8,&lStack_c0);
      param_1 = param_1 + 0xc;
      bVar25 = bVar25 + 0xa0;
    }
    lVar12 = lStack_68;
    lVar11 = lStack_70;
    lVar10 = lStack_78;
    lVar9 = lStack_80;
    lVar8 = lStack_88;
    lVar7 = lStack_90;
    lVar6 = lStack_98;
    lVar5 = lStack_a0;
    lVar4 = lStack_a8;
    lVar3 = lStack_b0;
    lVar2 = lStack_b8;
    lVar1 = lStack_c0;
    memset((long)param_1 + (ulong)bVar25,0,0x60 - (ulong)bVar25);
    *(byte *)((long)param_1 + 0x5f) = bVar25;
    uVar13 = lVar11 + param_1[1];
    uVar15 = uVar13 + lVar1 + param_1[0xb];
    uVar16 = lVar10 + param_1[2] ^ uVar15;
    uVar14 = lVar12 + *param_1 + uVar16;
    uVar17 = lVar9 + param_1[3] ^ uVar14;
    uVar13 = (uVar13 >> 0x14 | uVar13 << 0x2c) + uVar17;
    uVar18 = lVar8 + param_1[4] ^ uVar13;
    uVar16 = (uVar16 >> 0x31 | uVar16 << 0xf) + uVar18;
    uVar19 = lVar7 + param_1[5] ^ uVar16;
    uVar17 = (uVar17 >> 0x1e | uVar17 << 0x22) + uVar19;
    uVar20 = lVar6 + param_1[6] ^ uVar17;
    uVar18 = (uVar18 >> 0x2b | uVar18 << 0x15) + uVar20;
    uVar21 = lVar5 + param_1[7] ^ uVar18;
    uVar19 = (uVar19 >> 0x1a | uVar19 << 0x26) + uVar21;
    uVar22 = lVar4 + param_1[8] ^ uVar19;
    uVar20 = (uVar20 >> 0x1f | uVar20 << 0x21) + uVar22;
    uVar23 = lVar3 + param_1[9] ^ uVar20;
    uVar21 = (uVar21 >> 0x36 | uVar21 << 10) + uVar23;
    uVar24 = lVar2 + param_1[10] ^ uVar21;
    uVar22 = (uVar22 >> 0x33 | uVar22 << 0xd) + uVar24;
    uVar15 = uVar15 ^ uVar22;
    uVar23 = (uVar23 >> 0x1a | uVar23 << 0x26) + uVar15;
    uVar14 = uVar14 ^ uVar23;
    uVar24 = (uVar24 >> 0xb | uVar24 << 0x35) + uVar14;
    uVar13 = uVar13 ^ uVar24;
    uVar15 = (uVar15 >> 0x16 | uVar15 << 0x2a) + uVar13;
    uVar16 = uVar16 ^ uVar15;
    uVar14 = (uVar14 >> 10 | uVar14 << 0x36) + uVar16;
    uVar17 = uVar17 ^ uVar14;
    uVar13 = (uVar13 >> 0x14 | uVar13 << 0x2c) + uVar17;
    uVar18 = uVar18 ^ uVar13;
    uVar16 = (uVar16 >> 0x31 | uVar16 << 0xf) + uVar18;
    uVar19 = uVar19 ^ uVar16;
    uVar17 = (uVar17 >> 0x1e | uVar17 << 0x22) + uVar19;
    uVar20 = uVar20 ^ uVar17;
    uVar18 = (uVar18 >> 0x2b | uVar18 << 0x15) + uVar20;
    uVar21 = uVar21 ^ uVar18;
    uVar19 = (uVar19 >> 0x1a | uVar19 << 0x26) + uVar21;
    uVar22 = uVar22 ^ uVar19;
    uVar20 = (uVar20 >> 0x1f | uVar20 << 0x21) + uVar22;
    uVar23 = uVar23 ^ uVar20;
    uVar21 = (uVar21 >> 0x36 | uVar21 << 10) + uVar23;
    uVar24 = uVar24 ^ uVar21;
    uVar22 = (uVar22 >> 0x33 | uVar22 << 0xd) + uVar24;
    uVar15 = uVar15 ^ uVar22;
    uVar23 = (uVar23 >> 0x1a | uVar23 << 0x26) + uVar15;
    uVar14 = uVar14 ^ uVar23;
    uVar24 = (uVar24 >> 0xb | uVar24 << 0x35) + uVar14;
    uVar13 = uVar13 ^ uVar24;
    uVar15 = (uVar15 >> 0x16 | uVar15 << 0x2a) + uVar13;
    uVar16 = uVar16 ^ uVar15;
    uVar14 = (uVar14 >> 10 | uVar14 << 0x36) + uVar16;
    uVar17 = uVar17 ^ uVar14;
    uVar13 = (uVar13 >> 0x14 | uVar13 << 0x2c) + uVar17;
    uVar18 = uVar18 ^ uVar13;
    uVar19 = uVar19 ^ (uVar16 >> 0x31 | uVar16 << 0xf) + uVar18;
    uVar20 = uVar20 ^ (uVar17 >> 0x1e | uVar17 << 0x22) + uVar19;
    uVar21 = uVar21 ^ (uVar18 >> 0x2b | uVar18 << 0x15) + uVar20;
    uVar22 = uVar22 ^ (uVar19 >> 0x1a | uVar19 << 0x26) + uVar21;
    uVar23 = uVar23 ^ (uVar20 >> 0x1f | uVar20 << 0x21) + uVar22;
    uVar24 = uVar24 ^ (uVar21 >> 0x36 | uVar21 << 10) + uVar23;
    uVar14 = uVar14 ^ (uVar23 >> 0x1a | uVar23 << 0x26) +
                      (uVar15 ^ (uVar22 >> 0x33 | uVar22 << 0xd) + uVar24);
    *param_2 = uVar14 >> 10 | uVar14 << 0x36;
    *param_3 = uVar13 ^ (uVar24 >> 0xb | uVar24 << 0x35) + uVar14;
    return;
  }
  *param_2 = param_1[0x18];
  *param_3 = param_1[0x19];
  (*(code *)PTR__ZN4Aska6detail12SpookyHashV25ShortEPKvmPmS4__02c99218)
            (param_1,param_1[0x24],param_2,param_3);
  return;
}
