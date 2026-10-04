// port/decomp/lib_jpeg/jpeg_util.c: Ghidra decompiles for the lib_jpeg subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:06 UTC: tools/decomp.sh '--into' 'lib_jpeg/jpeg_util' 'Aska::JpegUtil::'

// ==== Aska::JpegUtil::FnGrayscaleLineReader::operator()(unsigned char*, unsigned char const*, int) const
// vaddr 0x21ea458 | ghidra 0x22ea458 | size 212 | symbol _ZNK4Aska8JpegUtil21FnGrayscaleLineReaderclEPhPKhi | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska8JpegUtil21FnGrayscaleLineReaderclEPhPKhi
               (undefined8 param_1,undefined1 *param_2,undefined1 *param_3,uint param_4)

{
  ulong uVar1;
  int iVar2;
  long lVar3;
  undefined8 *puVar4;
  undefined1 *puVar5;
  long lVar6;
  undefined1 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  
  uVar1 = (ulong)(param_4 - 1);
  if ((int)param_4 < 1) {
    return;
  }
  if (0x1f < uVar1 + 1) {
    lVar3 = (uVar1 + 1) - (ulong)(param_4 & 0x1f);
    if (lVar3 == 0) goto code_r0x022ea4a4;
    if ((param_3 + uVar1 + 1 <= param_2) || (param_2 + uVar1 * 4 + 4 <= param_3)) {
      puVar4 = (undefined8 *)(param_3 + 0x10);
      puVar5 = param_2 + 0x40;
      lVar6 = lVar3;
      do {
        uVar9 = puVar4[-1];
        uVar8 = puVar4[-2];
        uVar11 = puVar4[1];
        uVar10 = *puVar4;
        puVar4 = puVar4 + 4;
        lVar6 = lVar6 + -0x20;
        uVar7 = (undefined1)uVar8;
        puVar5[-0x40] = uVar7;
        puVar5[-0x3f] = uVar7;
        puVar5[-0x3e] = uVar7;
        puVar5[-0x3d] = 0xff;
        uVar7 = (undefined1)((ulong)uVar8 >> 8);
        puVar5[-0x3c] = uVar7;
        puVar5[-0x3b] = uVar7;
        puVar5[-0x3a] = uVar7;
        puVar5[-0x39] = 0xff;
        uVar7 = (undefined1)((ulong)uVar8 >> 0x10);
        puVar5[-0x38] = uVar7;
        puVar5[-0x37] = uVar7;
        puVar5[-0x36] = uVar7;
        puVar5[-0x35] = 0xff;
        uVar7 = (undefined1)((ulong)uVar8 >> 0x18);
        puVar5[-0x34] = uVar7;
        puVar5[-0x33] = uVar7;
        puVar5[-0x32] = uVar7;
        puVar5[-0x31] = 0xff;
        uVar7 = (undefined1)((ulong)uVar8 >> 0x20);
        puVar5[-0x30] = uVar7;
        puVar5[-0x2f] = uVar7;
        puVar5[-0x2e] = uVar7;
        puVar5[-0x2d] = 0xff;
        uVar7 = (undefined1)((ulong)uVar8 >> 0x28);
        puVar5[-0x2c] = uVar7;
        puVar5[-0x2b] = uVar7;
        puVar5[-0x2a] = uVar7;
        puVar5[-0x29] = 0xff;
        uVar7 = (undefined1)((ulong)uVar8 >> 0x30);
        puVar5[-0x28] = uVar7;
        puVar5[-0x27] = uVar7;
        puVar5[-0x26] = uVar7;
        puVar5[-0x25] = 0xff;
        uVar7 = (undefined1)((ulong)uVar8 >> 0x38);
        puVar5[-0x24] = uVar7;
        puVar5[-0x23] = uVar7;
        puVar5[-0x22] = uVar7;
        puVar5[-0x21] = 0xff;
        uVar7 = (undefined1)uVar9;
        puVar5[-0x20] = uVar7;
        puVar5[-0x1f] = uVar7;
        puVar5[-0x1e] = uVar7;
        puVar5[-0x1d] = 0xff;
        uVar7 = (undefined1)((ulong)uVar9 >> 8);
        puVar5[-0x1c] = uVar7;
        puVar5[-0x1b] = uVar7;
        puVar5[-0x1a] = uVar7;
        puVar5[-0x19] = 0xff;
        uVar7 = (undefined1)((ulong)uVar9 >> 0x10);
        puVar5[-0x18] = uVar7;
        puVar5[-0x17] = uVar7;
        puVar5[-0x16] = uVar7;
        puVar5[-0x15] = 0xff;
        uVar7 = (undefined1)((ulong)uVar9 >> 0x18);
        puVar5[-0x14] = uVar7;
        puVar5[-0x13] = uVar7;
        puVar5[-0x12] = uVar7;
        puVar5[-0x11] = 0xff;
        uVar7 = (undefined1)((ulong)uVar9 >> 0x20);
        puVar5[-0x10] = uVar7;
        puVar5[-0xf] = uVar7;
        puVar5[-0xe] = uVar7;
        puVar5[-0xd] = 0xff;
        uVar7 = (undefined1)((ulong)uVar9 >> 0x28);
        puVar5[-0xc] = uVar7;
        puVar5[-0xb] = uVar7;
        puVar5[-10] = uVar7;
        puVar5[-9] = 0xff;
        uVar7 = (undefined1)((ulong)uVar9 >> 0x30);
        puVar5[-8] = uVar7;
        puVar5[-7] = uVar7;
        puVar5[-6] = uVar7;
        puVar5[-5] = 0xff;
        uVar7 = (undefined1)((ulong)uVar9 >> 0x38);
        puVar5[-4] = uVar7;
        puVar5[-3] = uVar7;
        puVar5[-2] = uVar7;
        puVar5[-1] = 0xff;
        uVar7 = (undefined1)uVar10;
        *puVar5 = uVar7;
        puVar5[1] = uVar7;
        puVar5[2] = uVar7;
        puVar5[3] = 0xff;
        uVar7 = (undefined1)((ulong)uVar10 >> 8);
        puVar5[4] = uVar7;
        puVar5[5] = uVar7;
        puVar5[6] = uVar7;
        puVar5[7] = 0xff;
        uVar7 = (undefined1)((ulong)uVar10 >> 0x10);
        puVar5[8] = uVar7;
        puVar5[9] = uVar7;
        puVar5[10] = uVar7;
        puVar5[0xb] = 0xff;
        uVar7 = (undefined1)((ulong)uVar10 >> 0x18);
        puVar5[0xc] = uVar7;
        puVar5[0xd] = uVar7;
        puVar5[0xe] = uVar7;
        puVar5[0xf] = 0xff;
        uVar7 = (undefined1)((ulong)uVar10 >> 0x20);
        puVar5[0x10] = uVar7;
        puVar5[0x11] = uVar7;
        puVar5[0x12] = uVar7;
        puVar5[0x13] = 0xff;
        uVar7 = (undefined1)((ulong)uVar10 >> 0x28);
        puVar5[0x14] = uVar7;
        puVar5[0x15] = uVar7;
        puVar5[0x16] = uVar7;
        puVar5[0x17] = 0xff;
        uVar7 = (undefined1)((ulong)uVar10 >> 0x30);
        puVar5[0x18] = uVar7;
        puVar5[0x19] = uVar7;
        puVar5[0x1a] = uVar7;
        puVar5[0x1b] = 0xff;
        uVar7 = (undefined1)((ulong)uVar10 >> 0x38);
        puVar5[0x1c] = uVar7;
        puVar5[0x1d] = uVar7;
        puVar5[0x1e] = uVar7;
        puVar5[0x1f] = 0xff;
        uVar7 = (undefined1)uVar11;
        puVar5[0x20] = uVar7;
        puVar5[0x21] = uVar7;
        puVar5[0x22] = uVar7;
        puVar5[0x23] = 0xff;
        uVar7 = (undefined1)((ulong)uVar11 >> 8);
        puVar5[0x24] = uVar7;
        puVar5[0x25] = uVar7;
        puVar5[0x26] = uVar7;
        puVar5[0x27] = 0xff;
        uVar7 = (undefined1)((ulong)uVar11 >> 0x10);
        puVar5[0x28] = uVar7;
        puVar5[0x29] = uVar7;
        puVar5[0x2a] = uVar7;
        puVar5[0x2b] = 0xff;
        uVar7 = (undefined1)((ulong)uVar11 >> 0x18);
        puVar5[0x2c] = uVar7;
        puVar5[0x2d] = uVar7;
        puVar5[0x2e] = uVar7;
        puVar5[0x2f] = 0xff;
        uVar7 = (undefined1)((ulong)uVar11 >> 0x20);
        puVar5[0x30] = uVar7;
        puVar5[0x31] = uVar7;
        puVar5[0x32] = uVar7;
        puVar5[0x33] = 0xff;
        uVar7 = (undefined1)((ulong)uVar11 >> 0x28);
        puVar5[0x34] = uVar7;
        puVar5[0x35] = uVar7;
        puVar5[0x36] = uVar7;
        puVar5[0x37] = 0xff;
        uVar7 = (undefined1)((ulong)uVar11 >> 0x30);
        puVar5[0x38] = uVar7;
        puVar5[0x39] = uVar7;
        puVar5[0x3a] = uVar7;
        puVar5[0x3b] = 0xff;
        uVar7 = (undefined1)((ulong)uVar11 >> 0x38);
        puVar5[0x3c] = uVar7;
        puVar5[0x3d] = uVar7;
        puVar5[0x3e] = uVar7;
        puVar5[0x3f] = 0xff;
        puVar5 = puVar5 + 0x80;
      } while (lVar6 != 0);
      param_2 = param_2 + lVar3 * 4;
      param_3 = param_3 + lVar3;
      if ((param_4 & 0x1f) == 0) {
        return;
      }
      goto code_r0x022ea4a4;
    }
  }
  lVar3 = 0;
code_r0x022ea4a4:
  iVar2 = param_4 - (int)lVar3;
  do {
    iVar2 = iVar2 + -1;
    *param_2 = *param_3;
    param_2[1] = *param_3;
    uVar7 = *param_3;
    param_2[3] = 0xff;
    param_2[2] = uVar7;
    param_2 = param_2 + 4;
    param_3 = param_3 + 1;
  } while (iVar2 != 0);
  return;
}

// ==== Aska::JpegUtil::FnRGBXLineReader::operator()(unsigned char*, unsigned char const*, int) const
// vaddr 0x21ea52c | ghidra 0x22ea52c | size 212 | symbol _ZNK4Aska8JpegUtil16FnRGBXLineReaderclEPhPKhi | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska8JpegUtil16FnRGBXLineReaderclEPhPKhi
               (undefined8 param_1,undefined1 *param_2,undefined1 *param_3,uint param_4)

{
  undefined1 *puVar1;
  ulong uVar2;
  int iVar3;
  long lVar4;
  undefined1 *puVar5;
  long lVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  undefined1 uVar12;
  undefined1 uVar13;
  undefined1 uVar14;
  undefined1 uVar15;
  undefined1 uVar16;
  undefined1 uVar17;
  undefined1 uVar18;
  undefined1 uVar19;
  undefined1 uVar20;
  undefined1 uVar21;
  undefined1 uVar22;
  undefined1 uVar23;
  undefined1 uVar24;
  undefined1 uVar25;
  undefined1 uVar26;
  undefined1 uVar27;
  undefined1 uVar28;
  undefined1 uVar29;
  undefined1 uVar30;
  undefined1 uVar31;
  undefined1 uVar32;
  undefined1 uVar33;
  undefined1 uVar34;
  undefined1 uVar35;
  undefined1 uVar36;
  undefined1 uVar37;
  undefined1 uVar38;
  undefined1 uVar39;
  undefined1 uVar40;
  undefined1 uVar41;
  undefined1 uVar42;
  undefined1 uVar43;
  undefined1 uVar44;
  undefined1 uVar45;
  undefined1 uVar46;
  undefined1 uVar47;
  undefined1 uVar48;
  undefined1 uVar49;
  undefined1 uVar50;
  undefined1 uVar51;
  undefined1 uVar52;
  undefined1 uVar53;
  undefined1 uVar54;
  undefined1 uVar55;
  undefined1 uVar56;
  undefined1 uVar57;
  undefined1 uVar58;
  undefined1 uVar59;
  undefined1 uVar60;
  undefined1 uVar61;
  undefined1 uVar62;
  undefined1 uVar63;
  undefined1 uVar64;
  undefined1 uVar65;
  undefined1 uVar66;
  undefined1 uVar67;
  undefined1 uVar68;
  undefined1 uVar69;
  undefined1 uVar70;
  undefined1 uVar71;
  undefined1 uVar72;
  undefined1 uVar73;
  undefined1 uVar74;
  undefined1 uVar75;
  undefined1 uVar76;
  undefined1 uVar77;
  undefined1 uVar78;
  undefined1 uVar79;
  undefined1 uVar80;
  undefined1 uVar81;
  undefined1 uVar82;
  undefined1 uVar83;
  undefined1 uVar84;
  undefined1 uVar85;
  undefined1 uVar86;
  undefined1 uVar87;
  undefined1 uVar88;
  undefined1 uVar89;
  undefined1 uVar90;
  undefined1 uVar91;
  undefined1 uVar92;
  undefined1 uVar93;
  undefined1 uVar94;
  undefined1 uVar95;
  undefined1 uVar96;
  undefined1 uVar97;
  undefined1 uVar98;
  undefined1 uVar99;
  undefined1 uVar100;
  undefined1 uVar101;
  
  uVar2 = (ulong)(param_4 - 1);
  if ((int)param_4 < 1) {
    return;
  }
  if (0x1f < uVar2 + 1) {
    lVar4 = (uVar2 + 1) - (ulong)(param_4 & 0x1f);
    if (lVar4 == 0) goto code_r0x022ea57c;
    if ((param_3 + uVar2 * 3 + 3 <= param_2) || (param_2 + uVar2 * 4 + 4 <= param_3)) {
      puVar5 = param_2 + 0x40;
      puVar1 = param_3;
      lVar6 = lVar4;
      do {
        uVar22 = puVar1[1];
        uVar38 = puVar1[2];
        uVar7 = puVar1[3];
        uVar23 = puVar1[4];
        uVar39 = puVar1[5];
        uVar8 = puVar1[6];
        uVar24 = puVar1[7];
        uVar40 = puVar1[8];
        uVar9 = puVar1[9];
        uVar25 = puVar1[10];
        uVar41 = puVar1[0xb];
        uVar10 = puVar1[0xc];
        uVar26 = puVar1[0xd];
        uVar42 = puVar1[0xe];
        uVar11 = puVar1[0xf];
        uVar27 = puVar1[0x10];
        uVar43 = puVar1[0x11];
        uVar12 = puVar1[0x12];
        uVar28 = puVar1[0x13];
        uVar44 = puVar1[0x14];
        uVar13 = puVar1[0x15];
        uVar29 = puVar1[0x16];
        uVar45 = puVar1[0x17];
        uVar14 = puVar1[0x18];
        uVar30 = puVar1[0x19];
        uVar46 = puVar1[0x1a];
        uVar15 = puVar1[0x1b];
        uVar31 = puVar1[0x1c];
        uVar47 = puVar1[0x1d];
        uVar16 = puVar1[0x1e];
        uVar32 = puVar1[0x1f];
        uVar48 = puVar1[0x20];
        uVar17 = puVar1[0x21];
        uVar33 = puVar1[0x22];
        uVar49 = puVar1[0x23];
        uVar18 = puVar1[0x24];
        uVar34 = puVar1[0x25];
        uVar50 = puVar1[0x26];
        uVar19 = puVar1[0x27];
        uVar35 = puVar1[0x28];
        uVar51 = puVar1[0x29];
        uVar20 = puVar1[0x2a];
        uVar36 = puVar1[0x2b];
        uVar52 = puVar1[0x2c];
        uVar21 = puVar1[0x2d];
        uVar37 = puVar1[0x2e];
        uVar53 = puVar1[0x2f];
        lVar6 = lVar6 + -0x20;
        uVar54 = puVar1[0x30];
        uVar70 = puVar1[0x31];
        uVar86 = puVar1[0x32];
        uVar55 = puVar1[0x33];
        uVar71 = puVar1[0x34];
        uVar87 = puVar1[0x35];
        uVar56 = puVar1[0x36];
        uVar72 = puVar1[0x37];
        uVar88 = puVar1[0x38];
        uVar57 = puVar1[0x39];
        uVar73 = puVar1[0x3a];
        uVar89 = puVar1[0x3b];
        uVar58 = puVar1[0x3c];
        uVar74 = puVar1[0x3d];
        uVar90 = puVar1[0x3e];
        uVar59 = puVar1[0x3f];
        uVar75 = puVar1[0x40];
        uVar91 = puVar1[0x41];
        uVar60 = puVar1[0x42];
        uVar76 = puVar1[0x43];
        uVar92 = puVar1[0x44];
        uVar61 = puVar1[0x45];
        uVar77 = puVar1[0x46];
        uVar93 = puVar1[0x47];
        uVar62 = puVar1[0x48];
        uVar78 = puVar1[0x49];
        uVar94 = puVar1[0x4a];
        uVar63 = puVar1[0x4b];
        uVar79 = puVar1[0x4c];
        uVar95 = puVar1[0x4d];
        uVar64 = puVar1[0x4e];
        uVar80 = puVar1[0x4f];
        uVar96 = puVar1[0x50];
        uVar65 = puVar1[0x51];
        uVar81 = puVar1[0x52];
        uVar97 = puVar1[0x53];
        uVar66 = puVar1[0x54];
        uVar82 = puVar1[0x55];
        uVar98 = puVar1[0x56];
        uVar67 = puVar1[0x57];
        uVar83 = puVar1[0x58];
        uVar99 = puVar1[0x59];
        uVar68 = puVar1[0x5a];
        uVar84 = puVar1[0x5b];
        uVar100 = puVar1[0x5c];
        uVar69 = puVar1[0x5d];
        uVar85 = puVar1[0x5e];
        uVar101 = puVar1[0x5f];
        puVar5[-0x40] = *puVar1;
        puVar5[-0x3f] = uVar22;
        puVar5[-0x3e] = uVar38;
        puVar5[-0x3d] = 0xff;
        puVar5[-0x3c] = uVar7;
        puVar5[-0x3b] = uVar23;
        puVar5[-0x3a] = uVar39;
        puVar5[-0x39] = 0xff;
        puVar5[-0x38] = uVar8;
        puVar5[-0x37] = uVar24;
        puVar5[-0x36] = uVar40;
        puVar5[-0x35] = 0xff;
        puVar5[-0x34] = uVar9;
        puVar5[-0x33] = uVar25;
        puVar5[-0x32] = uVar41;
        puVar5[-0x31] = 0xff;
        puVar5[-0x30] = uVar10;
        puVar5[-0x2f] = uVar26;
        puVar5[-0x2e] = uVar42;
        puVar5[-0x2d] = 0xff;
        puVar5[-0x2c] = uVar11;
        puVar5[-0x2b] = uVar27;
        puVar5[-0x2a] = uVar43;
        puVar5[-0x29] = 0xff;
        puVar5[-0x28] = uVar12;
        puVar5[-0x27] = uVar28;
        puVar5[-0x26] = uVar44;
        puVar5[-0x25] = 0xff;
        puVar5[-0x24] = uVar13;
        puVar5[-0x23] = uVar29;
        puVar5[-0x22] = uVar45;
        puVar5[-0x21] = 0xff;
        puVar5[-0x20] = uVar14;
        puVar5[-0x1f] = uVar30;
        puVar5[-0x1e] = uVar46;
        puVar5[-0x1d] = 0xff;
        puVar5[-0x1c] = uVar15;
        puVar5[-0x1b] = uVar31;
        puVar5[-0x1a] = uVar47;
        puVar5[-0x19] = 0xff;
        puVar5[-0x18] = uVar16;
        puVar5[-0x17] = uVar32;
        puVar5[-0x16] = uVar48;
        puVar5[-0x15] = 0xff;
        puVar5[-0x14] = uVar17;
        puVar5[-0x13] = uVar33;
        puVar5[-0x12] = uVar49;
        puVar5[-0x11] = 0xff;
        puVar5[-0x10] = uVar18;
        puVar5[-0xf] = uVar34;
        puVar5[-0xe] = uVar50;
        puVar5[-0xd] = 0xff;
        puVar5[-0xc] = uVar19;
        puVar5[-0xb] = uVar35;
        puVar5[-10] = uVar51;
        puVar5[-9] = 0xff;
        puVar5[-8] = uVar20;
        puVar5[-7] = uVar36;
        puVar5[-6] = uVar52;
        puVar5[-5] = 0xff;
        puVar5[-4] = uVar21;
        puVar5[-3] = uVar37;
        puVar5[-2] = uVar53;
        puVar5[-1] = 0xff;
        *puVar5 = uVar54;
        puVar5[1] = uVar70;
        puVar5[2] = uVar86;
        puVar5[3] = 0xff;
        puVar5[4] = uVar55;
        puVar5[5] = uVar71;
        puVar5[6] = uVar87;
        puVar5[7] = 0xff;
        puVar5[8] = uVar56;
        puVar5[9] = uVar72;
        puVar5[10] = uVar88;
        puVar5[0xb] = 0xff;
        puVar5[0xc] = uVar57;
        puVar5[0xd] = uVar73;
        puVar5[0xe] = uVar89;
        puVar5[0xf] = 0xff;
        puVar5[0x10] = uVar58;
        puVar5[0x11] = uVar74;
        puVar5[0x12] = uVar90;
        puVar5[0x13] = 0xff;
        puVar5[0x14] = uVar59;
        puVar5[0x15] = uVar75;
        puVar5[0x16] = uVar91;
        puVar5[0x17] = 0xff;
        puVar5[0x18] = uVar60;
        puVar5[0x19] = uVar76;
        puVar5[0x1a] = uVar92;
        puVar5[0x1b] = 0xff;
        puVar5[0x1c] = uVar61;
        puVar5[0x1d] = uVar77;
        puVar5[0x1e] = uVar93;
        puVar5[0x1f] = 0xff;
        puVar5[0x20] = uVar62;
        puVar5[0x21] = uVar78;
        puVar5[0x22] = uVar94;
        puVar5[0x23] = 0xff;
        puVar5[0x24] = uVar63;
        puVar5[0x25] = uVar79;
        puVar5[0x26] = uVar95;
        puVar5[0x27] = 0xff;
        puVar5[0x28] = uVar64;
        puVar5[0x29] = uVar80;
        puVar5[0x2a] = uVar96;
        puVar5[0x2b] = 0xff;
        puVar5[0x2c] = uVar65;
        puVar5[0x2d] = uVar81;
        puVar5[0x2e] = uVar97;
        puVar5[0x2f] = 0xff;
        puVar5[0x30] = uVar66;
        puVar5[0x31] = uVar82;
        puVar5[0x32] = uVar98;
        puVar5[0x33] = 0xff;
        puVar5[0x34] = uVar67;
        puVar5[0x35] = uVar83;
        puVar5[0x36] = uVar99;
        puVar5[0x37] = 0xff;
        puVar5[0x38] = uVar68;
        puVar5[0x39] = uVar84;
        puVar5[0x3a] = uVar100;
        puVar5[0x3b] = 0xff;
        puVar5[0x3c] = uVar69;
        puVar5[0x3d] = uVar85;
        puVar5[0x3e] = uVar101;
        puVar5[0x3f] = 0xff;
        puVar5 = puVar5 + 0x80;
        puVar1 = puVar1 + 0x60;
      } while (lVar6 != 0);
      param_2 = param_2 + lVar4 * 4;
      param_3 = param_3 + lVar4 * 3;
      if ((param_4 & 0x1f) == 0) {
        return;
      }
      goto code_r0x022ea57c;
    }
  }
  lVar4 = 0;
code_r0x022ea57c:
  iVar3 = param_4 - (int)lVar4;
  do {
    iVar3 = iVar3 + -1;
    *param_2 = *param_3;
    param_2[1] = param_3[1];
    uVar7 = param_3[2];
    param_2[3] = 0xff;
    param_3 = param_3 + 3;
    param_2[2] = uVar7;
    param_2 = param_2 + 4;
  } while (iVar3 != 0);
  return;
}

// ==== Aska::JpegUtil::FnCMYKLineReader::operator()(unsigned char*, unsigned char const*, int) const
// vaddr 0x21ea600 | ghidra 0x22ea600 | size 884 | symbol _ZNK4Aska8JpegUtil16FnCMYKLineReaderclEPhPKhi | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK4Aska8JpegUtil16FnCMYKLineReaderclEPhPKhi
               (undefined8 param_1,byte *param_2,byte *param_3,uint param_4)

{
  byte *pbVar1;
  byte *pbVar2;
  uint3 uVar3;
  uint5 uVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  int iVar8;
  long lVar9;
  int iVar10;
  long lVar11;
  float fVar12;
  ulong uVar13;
  undefined1 auVar14 [16];
  float fVar15;
  ulong uVar16;
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  float fVar21;
  float fVar22;
  undefined1 auVar20 [16];
  ulong uVar23;
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  undefined1 auVar26 [16];
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined1 auVar29 [16];
  undefined1 auVar30 [16];
  undefined1 auVar31 [16];
  undefined1 auVar32 [16];
  undefined1 auVar33 [16];
  undefined1 auVar34 [16];
  undefined1 auVar35 [16];
  undefined1 auVar36 [16];
  undefined1 auVar37 [16];
  ulong uVar38;
  undefined1 in_q20 [16];
  undefined1 auVar39 [16];
  undefined1 auVar40 [16];
  undefined1 auVar41 [16];
  undefined1 auVar42 [16];
  undefined1 auVar43 [16];
  ulong uVar44;
  undefined1 in_q21 [16];
  undefined1 auVar45 [16];
  undefined1 auVar46 [16];
  undefined1 auVar47 [16];
  undefined1 auVar48 [16];
  undefined1 auVar49 [16];
  undefined1 auVar50 [16];
  undefined1 auVar51 [16];
  undefined1 auVar52 [16];
  undefined1 in_q23 [16];
  undefined1 auVar53 [16];
  undefined1 auVar54 [16];
  undefined1 auVar55 [16];
  undefined1 auVar56 [16];
  undefined1 auVar57 [16];
  undefined1 in_q24 [16];
  undefined1 auVar58 [16];
  undefined1 auVar59 [16];
  undefined1 auVar60 [16];
  undefined1 auVar61 [16];
  undefined1 auVar62 [16];
  undefined1 auVar63 [16];
  undefined1 auVar64 [16];
  undefined1 auVar65 [16];
  undefined1 auVar66 [16];
  undefined1 in_q26 [16];
  undefined1 auVar67 [16];
  undefined1 auVar68 [16];
  undefined1 auVar69 [16];
  undefined1 auVar70 [16];
  undefined1 in_q27 [16];
  undefined1 auVar71 [16];
  undefined1 auVar72 [16];
  float fVar73;
  ulong uVar74;
  float fVar79;
  float fVar80;
  undefined1 auVar75 [16];
  undefined1 auVar76 [16];
  undefined1 auVar77 [16];
  undefined1 auVar78 [16];
  float fVar81;
  float fVar82;
  ulong uVar83;
  float fVar86;
  float fVar87;
  undefined1 in_q29 [16];
  undefined1 auVar84 [16];
  undefined1 auVar85 [16];
  float fVar88;
  float fVar89;
  ulong uVar90;
  float fVar93;
  float fVar94;
  undefined1 in_q30 [16];
  undefined1 auVar91 [16];
  undefined1 auVar92 [16];
  float fVar95;
  
  if ((int)param_4 < 1) {
    return;
  }
  uVar13 = (ulong)(param_4 - 1) + 1;
  if (0xf < uVar13) {
    lVar9 = uVar13 - (param_4 & 0xf);
    if (lVar9 == 0) goto code_r0x022ea64c;
    lVar11 = (ulong)(param_4 - 1) * 4 + 4;
    if ((param_3 + lVar11 <= param_2) || (param_2 + lVar11 <= param_3)) {
      pbVar1 = param_3 + lVar9 * 4;
      pbVar2 = param_2 + lVar9 * 4;
      lVar11 = lVar9;
      do {
        auVar17[0] = *param_3;
        auVar24[0] = param_3[1];
        auVar30[0] = param_3[2];
        auVar34[0] = param_3[3];
        auVar17[1] = param_3[4];
        auVar24[1] = param_3[5];
        auVar30[1] = param_3[6];
        auVar34[1] = param_3[7];
        auVar17[2] = param_3[8];
        auVar24[2] = param_3[9];
        auVar30[2] = param_3[10];
        auVar34[2] = param_3[0xb];
        auVar17[3] = param_3[0xc];
        auVar24[3] = param_3[0xd];
        auVar30[3] = param_3[0xe];
        auVar34[3] = param_3[0xf];
        auVar17[4] = param_3[0x10];
        auVar24[4] = param_3[0x11];
        auVar30[4] = param_3[0x12];
        auVar34[4] = param_3[0x13];
        auVar17[5] = param_3[0x14];
        auVar24[5] = param_3[0x15];
        auVar30[5] = param_3[0x16];
        auVar34[5] = param_3[0x17];
        auVar17[6] = param_3[0x18];
        auVar24[6] = param_3[0x19];
        auVar30[6] = param_3[0x1a];
        auVar34[6] = param_3[0x1b];
        auVar17[7] = param_3[0x1c];
        auVar24[7] = param_3[0x1d];
        auVar30[7] = param_3[0x1e];
        auVar34[7] = param_3[0x1f];
        auVar17[8] = param_3[0x20];
        auVar24[8] = param_3[0x21];
        auVar30[8] = param_3[0x22];
        auVar34[8] = param_3[0x23];
        auVar17[9] = param_3[0x24];
        auVar24[9] = param_3[0x25];
        auVar30[9] = param_3[0x26];
        auVar34[9] = param_3[0x27];
        auVar17[10] = param_3[0x28];
        auVar24[10] = param_3[0x29];
        auVar30[10] = param_3[0x2a];
        auVar34[10] = param_3[0x2b];
        auVar17[0xb] = param_3[0x2c];
        auVar24[0xb] = param_3[0x2d];
        auVar30[0xb] = param_3[0x2e];
        auVar34[0xb] = param_3[0x2f];
        auVar17[0xc] = param_3[0x30];
        auVar24[0xc] = param_3[0x31];
        auVar30[0xc] = param_3[0x32];
        auVar34[0xc] = param_3[0x33];
        auVar17[0xd] = param_3[0x34];
        auVar24[0xd] = param_3[0x35];
        auVar30[0xd] = param_3[0x36];
        auVar34[0xd] = param_3[0x37];
        auVar17[0xe] = param_3[0x38];
        auVar24[0xe] = param_3[0x39];
        auVar30[0xe] = param_3[0x3a];
        auVar34[0xe] = param_3[0x3b];
        auVar17[0xf] = param_3[0x3c];
        auVar24[0xf] = param_3[0x3d];
        auVar30[0xf] = param_3[0x3e];
        auVar34[0xf] = param_3[0x3f];
        param_3 = param_3 + 0x40;
        lVar11 = lVar11 + -0x10;
        auVar14 = NEON_ext(auVar17,auVar17,8,1);
        auVar75 = NEON_ext(auVar34,auVar34,8,1);
        auVar39._1_15_ = in_q20._1_15_;
        auVar39[0] = auVar17[0];
        auVar45._1_15_ = in_q21._1_15_;
        auVar45[0] = auVar17[4];
        auVar49 = NEON_ext(auVar24,auVar24,8,1);
        auVar53._1_15_ = in_q23._1_15_;
        auVar53[0] = auVar24[0];
        auVar58._1_15_ = in_q24._1_15_;
        auVar58[0] = auVar24[4];
        auVar84._1_15_ = in_q29._1_15_;
        auVar84[0] = auVar34[0];
        auVar18._1_15_ = auVar17._1_15_;
        auVar18[0] = auVar34[4];
        auVar25._1_15_ = auVar24._1_15_;
        auVar25[0] = auVar14[0];
        auVar91._1_15_ = in_q30._1_15_;
        auVar91[0] = auVar75[0];
        auVar29._1_15_ = auVar14._1_15_;
        auVar29[0] = auVar14[4];
        uVar3 = CONCAT12(auVar17[1],auVar39._0_2_);
        uVar4 = CONCAT14(auVar17[2],(uint)uVar3);
        uVar38 = CONCAT26((short)(CONCAT17(0x3f,(int7)CONCAT91(in_q20._7_9_,auVar17[3]) << 0x30) >>
                                 0x30),(uint6)uVar4) & 0xff00ff00ff00ff;
        auVar76._1_15_ = auVar75._1_15_;
        auVar76[0] = auVar75[4];
        uVar3 = CONCAT12(auVar34[1],auVar84._0_2_);
        uVar4 = CONCAT14(auVar34[2],(uint)uVar3);
        uVar83 = CONCAT26((short)(CONCAT17(0x3f,(int7)CONCAT91(in_q29._7_9_,auVar34[3]) << 0x30) >>
                                 0x30),(uint6)uVar4) & 0xff00ff00ff00ff;
        uVar23 = CONCAT26((short)(CONCAT17(0x3f,(int7)CONCAT91(auVar24._7_9_,auVar14[3]) << 0x30) >>
                                 0x30),
                          (uint6)CONCAT14(auVar14[2],(uint)CONCAT12(auVar14[1],auVar25._0_2_))) &
                 0xff00ff00ff00ff;
        uVar90 = CONCAT26((short)(CONCAT17(0x3f,(int7)CONCAT91(in_q30._7_9_,auVar75[3]) << 0x30) >>
                                 0x30),
                          (uint6)CONCAT14(auVar75[2],(uint)CONCAT12(auVar75[1],auVar91._0_2_))) &
                 0xff00ff00ff00ff;
        auVar62 = NEON_ext(auVar30,auVar30,8,1);
        auVar67._1_15_ = in_q26._1_15_;
        auVar67[0] = auVar30[0];
        auVar71._1_15_ = in_q27._1_15_;
        auVar71[0] = auVar30[4];
        uVar3 = CONCAT12(auVar17[5],auVar45._0_2_);
        uVar4 = CONCAT14(auVar17[6],(uint)uVar3);
        uVar44 = CONCAT26((short)(CONCAT17(0x3f,(int7)CONCAT91(in_q21._7_9_,auVar17[7]) << 0x30) >>
                                 0x30),(uint6)uVar4) & 0xff00ff00ff00ff;
        auVar31._1_15_ = auVar30._1_15_;
        auVar31[0] = auVar49[0];
        uVar3 = CONCAT12(auVar34[5],auVar18._0_2_);
        uVar4 = CONCAT14(auVar34[6],(uint)uVar3);
        uVar16 = CONCAT26((short)(CONCAT17(0x3f,(int7)CONCAT91(auVar17._7_9_,auVar34[7]) << 0x30) >>
                                 0x30),(uint6)uVar4) & 0xff00ff00ff00ff;
        uVar13 = CONCAT26((short)(CONCAT17(0x3f,(int7)CONCAT91(auVar14._7_9_,auVar14[7]) << 0x30) >>
                                 0x30),
                          (uint6)CONCAT14(auVar14[6],(uint)CONCAT12(auVar14[5],auVar29._0_2_))) &
                 0xff00ff00ff00ff;
        auVar40._2_2_ = 0;
        auVar40._0_2_ = (ushort)uVar38;
        auVar40._4_2_ = (short)(uVar38 >> 0x10);
        auVar40._6_2_ = 0;
        auVar40._8_2_ = (short)(uVar38 >> 0x20);
        auVar40._10_2_ = 0;
        auVar40._12_2_ = (short)(uVar38 >> 0x30);
        auVar40._14_2_ = 0;
        uVar74 = CONCAT26((short)(CONCAT17(0x3f,(int7)CONCAT91(auVar75._7_9_,auVar75[7]) << 0x30) >>
                                 0x30),
                          (uint6)CONCAT14(auVar75[6],(uint)CONCAT12(auVar75[5],auVar76._0_2_))) &
                 0xff00ff00ff00ff;
        auVar85._2_2_ = 0;
        auVar85._0_2_ = (ushort)uVar83;
        auVar85._4_2_ = (short)(uVar83 >> 0x10);
        auVar85._6_2_ = 0;
        auVar85._8_2_ = (short)(uVar83 >> 0x20);
        auVar85._10_2_ = 0;
        auVar85._12_2_ = (short)(uVar83 >> 0x30);
        auVar85._14_2_ = 0;
        auVar26._2_2_ = 0;
        auVar26._0_2_ = (ushort)uVar23;
        auVar26._4_2_ = (short)(uVar23 >> 0x10);
        auVar26._6_2_ = 0;
        auVar26._8_2_ = (short)(uVar23 >> 0x20);
        auVar26._10_2_ = 0;
        auVar26._12_2_ = (short)(uVar23 >> 0x30);
        auVar26._14_2_ = 0;
        auVar92._2_2_ = 0;
        auVar92._0_2_ = (ushort)uVar90;
        auVar92._4_2_ = (short)(uVar90 >> 0x10);
        auVar92._6_2_ = 0;
        auVar92._8_2_ = (short)(uVar90 >> 0x20);
        auVar92._10_2_ = 0;
        auVar92._12_2_ = (short)(uVar90 >> 0x30);
        auVar92._14_2_ = 0;
        auVar35._1_15_ = auVar34._1_15_;
        auVar35[0] = auVar49[4];
        uVar3 = CONCAT12(auVar24[1],auVar53._0_2_);
        uVar4 = CONCAT14(auVar24[2],(uint)uVar3);
        uVar38 = CONCAT26((short)(CONCAT17(0x3f,(int7)CONCAT91(in_q23._7_9_,auVar24[3]) << 0x30) >>
                                 0x30),(uint6)uVar4) & 0xff00ff00ff00ff;
        auVar46._2_2_ = 0;
        auVar46._0_2_ = (ushort)uVar44;
        auVar46._4_2_ = (short)(uVar44 >> 0x10);
        auVar46._6_2_ = 0;
        auVar46._8_2_ = (short)(uVar44 >> 0x20);
        auVar46._10_2_ = 0;
        auVar46._12_2_ = (short)(uVar44 >> 0x30);
        auVar46._14_2_ = 0;
        uVar23 = CONCAT26((short)(CONCAT17(0x3f,(int7)CONCAT91(auVar30._7_9_,auVar49[3]) << 0x30) >>
                                 0x30),
                          (uint6)CONCAT14(auVar49[2],(uint)CONCAT12(auVar49[1],auVar31._0_2_))) &
                 0xff00ff00ff00ff;
        auVar19._2_2_ = 0;
        auVar19._0_2_ = (ushort)uVar16;
        auVar19._4_2_ = (short)(uVar16 >> 0x10);
        auVar19._6_2_ = 0;
        auVar19._8_2_ = (short)(uVar16 >> 0x20);
        auVar19._10_2_ = 0;
        auVar19._12_2_ = (short)(uVar16 >> 0x30);
        auVar19._14_2_ = 0;
        auVar43._2_2_ = 0;
        auVar43._0_2_ = (ushort)uVar13;
        auVar43._4_2_ = (short)(uVar13 >> 0x10);
        auVar43._6_2_ = 0;
        auVar43._8_2_ = (short)(uVar13 >> 0x20);
        auVar43._10_2_ = 0;
        auVar43._12_2_ = (short)(uVar13 >> 0x30);
        auVar43._14_2_ = 0;
        auVar41 = NEON_ucvtf(auVar40,4);
        auVar77._2_2_ = 0;
        auVar77._0_2_ = (ushort)uVar74;
        auVar77._4_2_ = (short)(uVar74 >> 0x10);
        auVar77._6_2_ = 0;
        auVar77._8_2_ = (short)(uVar74 >> 0x20);
        auVar77._10_2_ = 0;
        auVar77._12_2_ = (short)(uVar74 >> 0x30);
        auVar77._14_2_ = 0;
        in_q29 = NEON_ucvtf(auVar85,4);
        auVar27 = NEON_ucvtf(auVar26,4);
        in_q30 = NEON_ucvtf(auVar92,4);
        uVar3 = CONCAT12(auVar24[5],auVar58._0_2_);
        uVar4 = CONCAT14(auVar24[6],(uint)uVar3);
        uVar16 = CONCAT26((short)(CONCAT17(0x3f,(int7)CONCAT91(in_q24._7_9_,auVar24[7]) << 0x30) >>
                                 0x30),(uint6)uVar4) & 0xff00ff00ff00ff;
        auVar50._1_15_ = auVar49._1_15_;
        auVar50[0] = auVar62[0];
        uVar13 = CONCAT26((short)(CONCAT17(0x3f,(int7)CONCAT91(auVar34._7_9_,auVar49[7]) << 0x30) >>
                                 0x30),
                          (uint6)CONCAT14(auVar49[6],(uint)CONCAT12(auVar49[5],auVar35._0_2_))) &
                 0xff00ff00ff00ff;
        auVar54._2_2_ = 0;
        auVar54._0_2_ = (ushort)uVar38;
        auVar54._4_2_ = (short)(uVar38 >> 0x10);
        auVar54._6_2_ = 0;
        auVar54._8_2_ = (short)(uVar38 >> 0x20);
        auVar54._10_2_ = 0;
        auVar54._12_2_ = (short)(uVar38 >> 0x30);
        auVar54._14_2_ = 0;
        auVar47 = NEON_ucvtf(auVar46,4);
        auVar32._2_2_ = 0;
        auVar32._0_2_ = (ushort)uVar23;
        auVar32._4_2_ = (short)(uVar23 >> 0x10);
        auVar32._6_2_ = 0;
        auVar32._8_2_ = (short)(uVar23 >> 0x20);
        auVar32._10_2_ = 0;
        auVar32._12_2_ = (short)(uVar23 >> 0x30);
        auVar32._14_2_ = 0;
        auVar75 = NEON_ucvtf(auVar19,4);
        auVar14 = NEON_ucvtf(auVar43,4);
        auVar78 = NEON_ucvtf(auVar77,4);
        fVar82 = in_q29._0_4_;
        fVar86 = in_q29._4_4_;
        fVar87 = in_q29._8_4_;
        fVar88 = in_q29._12_4_;
        fVar89 = in_q30._0_4_;
        fVar93 = in_q30._4_4_;
        fVar94 = in_q30._8_4_;
        fVar95 = in_q30._12_4_;
        auVar63._1_15_ = auVar62._1_15_;
        auVar63[0] = auVar62[4];
        uVar3 = CONCAT12(auVar30[1],auVar67._0_2_);
        uVar4 = CONCAT14(auVar30[2],(uint)uVar3);
        uVar23 = CONCAT26((short)(CONCAT17(0x3f,(int7)CONCAT91(in_q26._7_9_,auVar30[3]) << 0x30) >>
                                 0x30),(uint6)uVar4) & 0xff00ff00ff00ff;
        auVar59._2_2_ = 0;
        auVar59._0_2_ = (ushort)uVar16;
        auVar59._4_2_ = (short)(uVar16 >> 0x10);
        auVar59._6_2_ = 0;
        auVar59._8_2_ = (short)(uVar16 >> 0x20);
        auVar59._10_2_ = 0;
        auVar59._12_2_ = (short)(uVar16 >> 0x30);
        auVar59._14_2_ = 0;
        uVar16 = CONCAT26((short)(CONCAT17(0x3f,(int7)CONCAT91(auVar49._7_9_,auVar62[3]) << 0x30) >>
                                 0x30),
                          (uint6)CONCAT14(auVar62[2],(uint)CONCAT12(auVar62[1],auVar50._0_2_))) &
                 0xff00ff00ff00ff;
        auVar36._2_2_ = 0;
        auVar36._0_2_ = (ushort)uVar13;
        auVar36._4_2_ = (short)(uVar13 >> 0x10);
        auVar36._6_2_ = 0;
        auVar36._8_2_ = (short)(uVar13 >> 0x20);
        auVar36._10_2_ = 0;
        auVar36._12_2_ = (short)(uVar13 >> 0x30);
        auVar36._14_2_ = 0;
        auVar55 = NEON_ucvtf(auVar54,4);
        auVar49 = NEON_ucvtf(auVar32,4);
        fVar15 = auVar75._0_4_;
        fVar21 = auVar75._4_4_;
        fVar12 = auVar75._8_4_;
        fVar22 = auVar75._12_4_;
        fVar73 = auVar78._0_4_;
        fVar79 = auVar78._4_4_;
        fVar80 = auVar78._8_4_;
        fVar81 = auVar78._12_4_;
        uVar3 = CONCAT12(auVar30[5],auVar71._0_2_);
        uVar4 = CONCAT14(auVar30[6],(uint)uVar3);
        uVar38 = CONCAT26((short)(CONCAT17(0x3f,(int7)CONCAT91(in_q27._7_9_,auVar30[7]) << 0x30) >>
                                 0x30),(uint6)uVar4) & 0xff00ff00ff00ff;
        uVar13 = CONCAT26((short)(CONCAT17(0x3f,(int7)CONCAT91(auVar62._7_9_,auVar62[7]) << 0x30) >>
                                 0x30),
                          (uint6)CONCAT14(auVar62[6],(uint)CONCAT12(auVar62[5],auVar63._0_2_))) &
                 0xff00ff00ff00ff;
        auVar68._2_2_ = 0;
        auVar68._0_2_ = (ushort)uVar23;
        auVar68._4_2_ = (short)(uVar23 >> 0x10);
        auVar68._6_2_ = 0;
        auVar68._8_2_ = (short)(uVar23 >> 0x20);
        auVar68._10_2_ = 0;
        auVar68._12_2_ = (short)(uVar23 >> 0x30);
        auVar68._14_2_ = 0;
        auVar60 = NEON_ucvtf(auVar59,4);
        auVar51._2_2_ = 0;
        auVar51._0_2_ = (ushort)uVar16;
        auVar51._4_2_ = (short)(uVar16 >> 0x10);
        auVar51._6_2_ = 0;
        auVar51._8_2_ = (short)(uVar16 >> 0x20);
        auVar51._10_2_ = 0;
        auVar51._12_2_ = (short)(uVar16 >> 0x30);
        auVar51._14_2_ = 0;
        auVar62 = NEON_ucvtf(auVar36,4);
        auVar72._2_2_ = 0;
        auVar72._0_2_ = (ushort)uVar38;
        auVar72._4_2_ = (short)(uVar38 >> 0x10);
        auVar72._6_2_ = 0;
        auVar72._8_2_ = (short)(uVar38 >> 0x20);
        auVar72._10_2_ = 0;
        auVar72._12_2_ = (short)(uVar38 >> 0x30);
        auVar72._14_2_ = 0;
        auVar64._2_2_ = 0;
        auVar64._0_2_ = (ushort)uVar13;
        auVar64._4_2_ = (short)(uVar13 >> 0x10);
        auVar64._6_2_ = 0;
        auVar64._8_2_ = (short)(uVar13 >> 0x20);
        auVar64._10_2_ = 0;
        auVar64._12_2_ = (short)(uVar13 >> 0x30);
        auVar64._14_2_ = 0;
        auVar69 = NEON_ucvtf(auVar68,4);
        auVar78 = NEON_ucvtf(auVar51,4);
        auVar42._0_4_ = (int)(auVar41._0_4_ * fVar82 * 0.003921569 + 0.5);
        auVar42._4_4_ = (int)(auVar41._4_4_ * fVar86 * 0.003921569 + 0.5);
        auVar42._8_4_ = (int)(auVar41._8_4_ * fVar87 * 0.003921569 + 0.5);
        auVar42._12_4_ = (int)(auVar41._12_4_ * fVar88 * 0.003921569 + 0.5);
        auVar28._0_4_ = (int)(auVar27._0_4_ * fVar89 * 0.003921569 + 0.5);
        auVar28._4_4_ = (int)(auVar27._4_4_ * fVar93 * 0.003921569 + 0.5);
        auVar28._8_4_ = (int)(auVar27._8_4_ * fVar94 * 0.003921569 + 0.5);
        auVar28._12_4_ = (int)(auVar27._12_4_ * fVar95 * 0.003921569 + 0.5);
        in_q27 = NEON_ucvtf(auVar72,4);
        auVar65 = NEON_ucvtf(auVar64,4);
        auVar48._0_4_ = (int)(auVar47._0_4_ * fVar15 * 0.003921569 + 0.5);
        auVar48._4_4_ = (int)(auVar47._4_4_ * fVar21 * 0.003921569 + 0.5);
        auVar48._8_4_ = (int)(auVar47._8_4_ * fVar12 * 0.003921569 + 0.5);
        auVar48._12_4_ = (int)(auVar47._12_4_ * fVar22 * 0.003921569 + 0.5);
        auVar57._0_4_ = (int)(auVar14._0_4_ * fVar73 * 0.003921569 + 0.5);
        auVar57._4_4_ = (int)(auVar14._4_4_ * fVar79 * 0.003921569 + 0.5);
        auVar57._8_4_ = (int)(auVar14._8_4_ * fVar80 * 0.003921569 + 0.5);
        auVar57._12_4_ = (int)(auVar14._12_4_ * fVar81 * 0.003921569 + 0.5);
        auVar14._8_8_ = 0xff000000ff;
        auVar14._0_8_ = 0xff000000ff;
        auVar43 = NEON_smin(auVar42,auVar14,4);
        auVar75._8_8_ = 0xff000000ff;
        auVar75._0_8_ = 0xff000000ff;
        auVar29 = NEON_smin(auVar28,auVar75,4);
        auVar56._0_4_ = (int)(auVar55._0_4_ * fVar82 * 0.003921569 + 0.5);
        auVar56._4_4_ = (int)(auVar55._4_4_ * fVar86 * 0.003921569 + 0.5);
        auVar56._8_4_ = (int)(auVar55._8_4_ * fVar87 * 0.003921569 + 0.5);
        auVar56._12_4_ = (int)(auVar55._12_4_ * fVar88 * 0.003921569 + 0.5);
        auVar27._8_8_ = 0xff000000ff;
        auVar27._0_8_ = 0xff000000ff;
        in_q21 = NEON_smin(auVar48,auVar27,4);
        auVar33._0_4_ = (int)(auVar49._0_4_ * fVar89 * 0.003921569 + 0.5);
        auVar33._4_4_ = (int)(auVar49._4_4_ * fVar93 * 0.003921569 + 0.5);
        auVar33._8_4_ = (int)(auVar49._8_4_ * fVar94 * 0.003921569 + 0.5);
        auVar33._12_4_ = (int)(auVar49._12_4_ * fVar95 * 0.003921569 + 0.5);
        auVar49._8_8_ = 0xff000000ff;
        auVar49._0_8_ = 0xff000000ff;
        auVar14 = NEON_smin(auVar57,auVar49,4);
        auVar61._0_4_ = (int)(auVar60._0_4_ * fVar15 * 0.003921569 + 0.5);
        auVar61._4_4_ = (int)(auVar60._4_4_ * fVar21 * 0.003921569 + 0.5);
        auVar61._8_4_ = (int)(auVar60._8_4_ * fVar12 * 0.003921569 + 0.5);
        auVar61._12_4_ = (int)(auVar60._12_4_ * fVar22 * 0.003921569 + 0.5);
        auVar37._0_4_ = (int)(auVar62._0_4_ * fVar73 * 0.003921569 + 0.5);
        auVar37._4_4_ = (int)(auVar62._4_4_ * fVar79 * 0.003921569 + 0.5);
        auVar37._8_4_ = (int)(auVar62._8_4_ * fVar80 * 0.003921569 + 0.5);
        auVar37._12_4_ = (int)(auVar62._12_4_ * fVar81 * 0.003921569 + 0.5);
        auVar62._8_8_ = 0xff000000ff;
        auVar62._0_8_ = 0xff000000ff;
        auVar57 = NEON_smin(auVar56,auVar62,4);
        auVar41._8_8_ = 0xff000000ff;
        auVar41._0_8_ = 0xff000000ff;
        auVar27 = NEON_smin(auVar33,auVar41,4);
        auVar5._2_2_ = in_q21._0_2_;
        auVar5._0_2_ = auVar43._12_2_;
        auVar5._4_2_ = in_q21._4_2_;
        auVar5._6_2_ = in_q21._8_2_;
        auVar5._8_2_ = in_q21._12_2_;
        auVar5._10_6_ = 0;
        in_q20 = auVar5 << 0x30;
        auVar70._0_4_ = (int)(auVar69._0_4_ * fVar82 * 0.003921569 + 0.5);
        auVar70._4_4_ = (int)(auVar69._4_4_ * fVar86 * 0.003921569 + 0.5);
        auVar70._8_4_ = (int)(auVar69._8_4_ * fVar87 * 0.003921569 + 0.5);
        auVar70._12_4_ = (int)(auVar69._12_4_ * fVar88 * 0.003921569 + 0.5);
        auVar47._8_8_ = 0xff000000ff;
        auVar47._0_8_ = 0xff000000ff;
        in_q24 = NEON_smin(auVar61,auVar47,4);
        auVar52._0_4_ = (int)(auVar78._0_4_ * fVar89 * 0.003921569 + 0.5);
        auVar52._4_4_ = (int)(auVar78._4_4_ * fVar93 * 0.003921569 + 0.5);
        auVar52._8_4_ = (int)(auVar78._8_4_ * fVar94 * 0.003921569 + 0.5);
        auVar52._12_4_ = (int)(auVar78._12_4_ * fVar95 * 0.003921569 + 0.5);
        auVar78._8_8_ = 0xff000000ff;
        auVar78._0_8_ = 0xff000000ff;
        auVar49 = NEON_smin(auVar37,auVar78,4);
        auVar20._0_4_ = (int)(in_q27._0_4_ * fVar15 * 0.003921569 + 0.5);
        auVar20._4_4_ = (int)(in_q27._4_4_ * fVar21 * 0.003921569 + 0.5);
        auVar20._8_4_ = (int)(in_q27._8_4_ * fVar12 * 0.003921569 + 0.5);
        auVar20._12_4_ = (int)(in_q27._12_4_ * fVar22 * 0.003921569 + 0.5);
        auVar66._0_4_ = (int)(auVar65._0_4_ * fVar73 * 0.003921569 + 0.5);
        auVar66._4_4_ = (int)(auVar65._4_4_ * fVar79 * 0.003921569 + 0.5);
        auVar66._8_4_ = (int)(auVar65._8_4_ * fVar80 * 0.003921569 + 0.5);
        auVar66._12_4_ = (int)(auVar65._12_4_ * fVar81 * 0.003921569 + 0.5);
        auVar55._8_8_ = 0xff000000ff;
        auVar55._0_8_ = 0xff000000ff;
        auVar47 = NEON_smin(auVar70,auVar55,4);
        auVar60._8_8_ = 0xff000000ff;
        auVar60._0_8_ = 0xff000000ff;
        auVar62 = NEON_smin(auVar52,auVar60,4);
        auVar6._2_2_ = in_q24._0_2_;
        auVar6._0_2_ = auVar57._12_2_;
        auVar6._4_2_ = in_q24._4_2_;
        auVar6._6_2_ = in_q24._8_2_;
        auVar6._8_2_ = in_q24._12_2_;
        auVar6._10_6_ = 0;
        in_q23 = auVar6 << 0x30;
        auVar65._8_8_ = 0xff000000ff;
        auVar65._0_8_ = 0xff000000ff;
        auVar75 = NEON_smin(auVar20,auVar65,4);
        auVar69._8_8_ = 0xff000000ff;
        auVar69._0_8_ = 0xff000000ff;
        auVar41 = NEON_smin(auVar66,auVar69,4);
        auVar7._2_2_ = auVar75._0_2_;
        auVar7._0_2_ = auVar47._12_2_;
        auVar7._4_2_ = auVar75._4_2_;
        auVar7._6_2_ = auVar75._8_2_;
        auVar7._8_2_ = auVar75._12_2_;
        auVar7._10_6_ = 0;
        in_q26 = auVar7 << 0x30;
        *param_2 = auVar43[0];
        param_2[1] = auVar57[0];
        param_2[2] = auVar47[0];
        param_2[3] = 0xff;
        param_2[4] = auVar43[4];
        param_2[5] = auVar57[4];
        param_2[6] = auVar47[4];
        param_2[7] = 0xff;
        param_2[8] = auVar43[8];
        param_2[9] = auVar57[8];
        param_2[10] = auVar47[8];
        param_2[0xb] = 0xff;
        param_2[0xc] = auVar43[0xc];
        param_2[0xd] = auVar57[0xc];
        param_2[0xe] = auVar47[0xc];
        param_2[0xf] = 0xff;
        param_2[0x10] = in_q21[0];
        param_2[0x11] = in_q24[0];
        param_2[0x12] = auVar75[0];
        param_2[0x13] = 0xff;
        param_2[0x14] = in_q21[4];
        param_2[0x15] = in_q24[4];
        param_2[0x16] = auVar75[4];
        param_2[0x17] = 0xff;
        param_2[0x18] = in_q21[8];
        param_2[0x19] = in_q24[8];
        param_2[0x1a] = auVar75[8];
        param_2[0x1b] = 0xff;
        param_2[0x1c] = in_q21[0xc];
        param_2[0x1d] = in_q24[0xc];
        param_2[0x1e] = auVar75[0xc];
        param_2[0x1f] = 0xff;
        param_2[0x20] = auVar29[0];
        param_2[0x21] = auVar27[0];
        param_2[0x22] = auVar62[0];
        param_2[0x23] = 0xff;
        param_2[0x24] = auVar29[4];
        param_2[0x25] = auVar27[4];
        param_2[0x26] = auVar62[4];
        param_2[0x27] = 0xff;
        param_2[0x28] = auVar29[8];
        param_2[0x29] = auVar27[8];
        param_2[0x2a] = auVar62[8];
        param_2[0x2b] = 0xff;
        param_2[0x2c] = auVar29[0xc];
        param_2[0x2d] = auVar27[0xc];
        param_2[0x2e] = auVar62[0xc];
        param_2[0x2f] = 0xff;
        param_2[0x30] = auVar14[0];
        param_2[0x31] = auVar49[0];
        param_2[0x32] = auVar41[0];
        param_2[0x33] = 0xff;
        param_2[0x34] = auVar14[4];
        param_2[0x35] = auVar49[4];
        param_2[0x36] = auVar41[4];
        param_2[0x37] = 0xff;
        param_2[0x38] = auVar14[8];
        param_2[0x39] = auVar49[8];
        param_2[0x3a] = auVar41[8];
        param_2[0x3b] = 0xff;
        param_2[0x3c] = auVar14[0xc];
        param_2[0x3d] = auVar49[0xc];
        param_2[0x3e] = auVar41[0xc];
        param_2[0x3f] = 0xff;
        param_2 = param_2 + 0x40;
      } while (lVar11 != 0);
      param_3 = pbVar1;
      param_2 = pbVar2;
      if ((param_4 & 0xf) == 0) {
        return;
      }
      goto code_r0x022ea64c;
    }
  }
  lVar9 = 0;
code_r0x022ea64c:
  fVar15 = _UNK_027f3ac4;
  iVar8 = param_4 - (int)lVar9;
  do {
    fVar12 = (float)NEON_ucvtf((uint)*param_3);
    fVar22 = (float)NEON_ucvtf((uint)param_3[3]);
    fVar21 = (float)NEON_ucvtf((uint)param_3[1]);
    iVar10 = (int)(fVar12 * fVar22 * fVar15 + 0.5);
    fVar12 = (float)NEON_ucvtf((uint)param_3[2]);
    if (0xfe < iVar10) {
      iVar10 = 0xff;
    }
    *param_2 = (byte)iVar10;
    iVar10 = (int)(fVar21 * fVar22 * fVar15 + 0.5);
    if (0xfe < iVar10) {
      iVar10 = 0xff;
    }
    param_2[1] = (byte)iVar10;
    iVar10 = (int)(fVar12 * fVar22 * fVar15 + 0.5);
    if (0xfe < iVar10) {
      iVar10 = 0xff;
    }
    param_2[3] = 0xff;
    iVar8 = iVar8 + -1;
    param_3 = param_3 + 4;
    param_2[2] = (byte)iVar10;
    param_2 = param_2 + 4;
  } while (iVar8 != 0);
  return;
}

// ==== Aska::JpegUtil::FnASKAEngineAllocator::Malloc(unsigned long) const
// vaddr 0x21ea974 | ghidra 0x22ea974 | size 20 | symbol _ZNK4Aska8JpegUtil21FnASKAEngineAllocator6MallocEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska8JpegUtil21FnASKAEngineAllocator6MallocEm(undefined8 param_1,undefined8 param_2)

{
  (*(code *)PTR__Znammb_02c9d8d8)(param_2,0x10,1);
  return;
}

// ==== Aska::JpegUtil::FnASKAEngineAllocator::Free(void*) const
// vaddr 0x21ea988 | ghidra 0x22ea988 | size 16 | symbol _ZNK4Aska8JpegUtil21FnASKAEngineAllocator4FreeEPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska8JpegUtil21FnASKAEngineAllocator4FreeEPv(undefined8 param_1,long param_2)

{
  if (param_2 != 0) {
    (*(code *)PTR__ZdaPv_02cb5db8)(param_2);
    return;
  }
  return;
}

// ==== Aska::JpegUtil::GetInfo(unsigned int*, unsigned int*, Aska::JpegUtil::ColorSpace*, bool*, bool*, void const*, unsigned long)
// vaddr 0x25e9fc0 | ghidra 0x26e9fc0 | size 120 | symbol _ZN4Aska8JpegUtil7GetInfoEPjS1_PNS0_10ColorSpaceEPbS4_PKvm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8JpegUtil7GetInfoEPjS1_PNS0_10ColorSpaceEPbS4_PKvm
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7)

{
  undefined *puStack_18;
  undefined *puStack_8;
  
  puStack_8 = &UNK_02c86c58;
  puStack_18 = &UNK_02c86c70;
  Aska::JpegUtil::GetInfo(unsigned int*, unsigned int*, Aska::JpegUtil::ColorSpace*, bool*, bool*, void const*, unsigned long)+0x78(0,0,0,0,param_1,param_2,param_3,param_4,param_5,param_6,param_7,&puStack_8,
                  &puStack_8,&puStack_8,&puStack_18);
  return;
}

// ==== Aska::JpegUtil::Decode(void*, unsigned long, unsigned int, unsigned int, void const*, unsigned long, Aska::JpegUtil::ILineScanner const&, Aska::JpegUtil::ILineScanner const&, Aska::JpegUtil::ILineScanner const&, Aska::JpegUtil::IAllocator const&)
// vaddr 0x25ea338 | ghidra 0x26ea338 | size 60 | symbol _ZN4Aska8JpegUtil6DecodeEPvmjjPKvmRKNS0_12ILineScannerES6_S6_RKNS0_10IAllocatorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8JpegUtil6DecodeEPvmjjPKvmRKNS0_12ILineScannerES6_S6_RKNS0_10IAllocatorE(void)

{
  Aska::JpegUtil::GetInfo(unsigned int*, unsigned int*, Aska::JpegUtil::ColorSpace*, bool*, bool*, void const*, unsigned long)+0x78();
  return;
}

// ==== Aska::JpegUtil::GetPlaneInfo(unsigned int*, unsigned int*, unsigned int*, unsigned int*, unsigned int*, void const*, unsigned long)
// vaddr 0x25ea3e0 | ghidra 0x26ea3e0 | size 1204 | symbol _ZN4Aska8JpegUtil12GetPlaneInfoEPjS1_S1_S1_S1_PKvm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8JpegUtil12GetPlaneInfoEPjS1_S1_S1_S1_PKvm
               (ulong param_1,long param_2,long param_3,ulong param_4,long param_5,
               undefined8 param_6,uint *param_7)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  float fVar8;
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  byte bVar12;
  byte bVar13;
  byte bVar14;
  undefined *puVar15;
  bool bVar16;
  bool bVar17;
  bool bVar18;
  bool bVar19;
  int iVar20;
  undefined8 uVar21;
  ulong uVar22;
  int iVar23;
  long lVar24;
  long lVar25;
  long lVar26;
  uint uVar27;
  float *pfVar28;
  uint *puVar29;
  uint uVar30;
  ulong uVar31;
  long lVar32;
  ulong uVar33;
  ulong uVar34;
  uint *puVar35;
  uint *puVar36;
  uint *puVar37;
  int *piVar38;
  int iVar40;
  int iVar41;
  undefined1 auVar39 [16];
  uint5 uVar42;
  uint5 uVar43;
  uint5 uVar44;
  byte bVar47;
  byte bVar48;
  byte bVar49;
  byte bVar50;
  byte bVar51;
  byte bVar52;
  undefined1 auVar45 [16];
  undefined1 auVar46 [16];
  undefined1 auVar53 [16];
  undefined1 auVar54 [16];
  undefined1 *apuStack_c48 [3];
  undefined1 auStack_c30 [128];
  undefined1 auStack_bb0 [128];
  undefined1 auStack_b30 [128];
  uint auStack_ab0 [48];
  undefined8 auStack_9f0 [6];
  int iStack_9c0;
  uint uStack_9b8;
  undefined1 uStack_997;
  undefined4 uStack_994;
  undefined1 uStack_990;
  uint uStack_978;
  uint uStack_958;
  long lStack_8d0;
  int iStack_870;
  long lStack_778;
  undefined8 uStack_770;
  uint *puStack_768;
  ulong uStack_760;
  uint *puStack_758;
  ulong uStack_750;
  undefined8 uStack_748;
  long lStack_740;
  code *pcStack_738;
  long lStack_728;
  uint uStack_71c;
  int iStack_718;
  uint uStack_714;
  uint *puStack_710;
  undefined1 auStack_708 [168];
  undefined8 uStack_660;
  long lStack_658;
  uint uStack_630;
  uint uStack_62c;
  int iStack_628;
  long alStack_5a8 [13];
  long lStack_540;
  uint uStack_4e0;
  uint uStack_4dc;
  long lStack_3e8;
  undefined1 auStack_378 [168];
  undefined8 auStack_2d0 [6];
  int iStack_2a0;
  int iStack_29c;
  int iStack_298;
  long lStack_1b0;
  int iStack_150;
  int iStack_14c;
  long lStack_58;
  
  lVar26 = tpidr_el0;
  lStack_58 = *(long *)(lVar26 + 0x28);
  uVar34 = param_4;
  auStack_2d0[0] = jpeg_std_error(auStack_378);
  jpeg_CreateDecompress(auStack_2d0,0x5a,0x278);
  puVar35 = param_7;
  jpeg_mem_src(auStack_2d0,param_6);
  iVar20 = jpeg_read_header(auStack_2d0,1);
  if (iVar20 == 1) {
    lVar24 = (long)iStack_298;
    if (iStack_298 < 1) {
      uVar30 = 0;
      uVar27 = 0;
    }
    else {
      lVar25 = 0;
      uVar27 = 0;
      uVar30 = 0;
      puVar29 = (uint *)(lStack_1b0 + 0xc);
      do {
        puVar36 = puVar29 + -1;
        uVar4 = *puVar29;
        lVar25 = lVar25 + 1;
        puVar29 = puVar29 + 0x18;
        uVar1 = *puVar36 ^ uVar27;
        uVar2 = uVar4 ^ uVar30;
        if ((int)*puVar36 <= (int)uVar27) {
          uVar1 = 0;
        }
        if ((int)uVar4 <= (int)uVar30) {
          uVar2 = 0;
        }
        uVar27 = uVar1 ^ uVar27;
        uVar30 = uVar2 ^ uVar30;
      } while (lVar25 < lVar24);
    }
    if (0 < iStack_298) {
      bVar16 = uVar27 >> 0x10 != 0;
      uVar2 = uVar27 >> ((ulong)bVar16 << 4);
      uVar1 = iStack_14c * 8;
      bVar17 = (uVar2 & 0xff00) != 0;
      uVar4 = 0;
      if (uVar1 != 0) {
        uVar4 = ((iStack_29c + uVar1) - 1) / uVar1;
      }
      uVar2 = uVar2 >> ((ulong)bVar17 << 3);
      bVar18 = (uVar2 & 0xf0) != 0;
      uVar2 = uVar2 >> ((ulong)bVar18 << 2);
      bVar19 = (uVar2 & 0xc) != 0;
      uVar27 = (uint)bVar16 << 4 | (uint)bVar17 << 3 | (uint)bVar18 << 2 |
               (uint)(uVar27 != 0) | (uint)bVar19 << 1;
      if ((2 << ((ulong)bVar19 << 1) & uVar2) != 0) {
        uVar27 = uVar27 + 1;
      }
      bVar16 = uVar30 >> 0x10 != 0;
      uVar1 = uVar30 >> ((ulong)bVar16 << 4);
      bVar17 = (uVar1 & 0xff00) != 0;
      uVar1 = uVar1 >> ((ulong)bVar17 << 3);
      bVar18 = (uVar1 & 0xf0) != 0;
      uVar1 = uVar1 >> ((ulong)bVar18 << 2);
      bVar19 = (uVar1 & 0xc) != 0;
      uVar30 = (uint)bVar16 << 4 | (uint)bVar17 << 3 | (uint)bVar18 << 2 |
               (uint)(uVar30 != 0) | (uint)bVar19 << 1;
      if ((2 << ((ulong)bVar19 << 1) & uVar1) != 0) {
        uVar30 = uVar30 + 1;
      }
      lVar25 = 0;
      if (param_1 == 0) {
        puVar29 = (uint *)(lStack_1b0 + 0xc);
        do {
          uVar1 = puVar29[-1];
          uVar2 = *puVar29;
          bVar16 = uVar1 >> 0x10 != 0;
          uVar3 = uVar1 >> ((ulong)bVar16 << 4);
          bVar17 = (uVar3 & 0xff00) != 0;
          uVar3 = uVar3 >> ((ulong)bVar17 << 3);
          bVar18 = (uVar3 & 0xf0) != 0;
          uVar3 = uVar3 >> ((ulong)bVar18 << 2);
          bVar19 = (uVar3 & 0xc) != 0;
          if (param_2 != 0) {
            *(uint *)(param_2 + lVar25 * 4) = uVar2 * uVar4 * 8;
          }
          uVar1 = (uVar27 - ((uint)bVar16 << 4 | (uint)bVar17 << 3 | (uint)bVar18 << 2 |
                            (uint)(uVar1 != 0) | (uint)bVar19 << 1)) -
                  (uint)((2 << ((ulong)bVar19 << 1) & uVar3) != 0);
          if (param_4 != 0) {
            *(uint *)(param_4 + lVar25 * 4) = uVar1;
          }
          if (param_5 != 0) {
            uVar3 = *puVar29;
            bVar16 = uVar3 >> 0x10 != 0;
            uVar5 = uVar3 >> ((ulong)bVar16 << 4);
            bVar17 = (uVar5 & 0xff00) != 0;
            uVar5 = uVar5 >> ((ulong)bVar17 << 3);
            bVar18 = (uVar5 & 0xf0) != 0;
            uVar5 = uVar5 >> ((ulong)bVar18 << 2);
            bVar19 = (uVar5 & 0xc) != 0;
            puVar35 = (uint *)((ulong)bVar19 << 1);
            *(uint *)(param_5 + lVar25 * 4) =
                 (uVar30 - ((uint)bVar16 << 4 | (uint)bVar17 << 3 | (uint)bVar18 << 2 |
                           (uint)(uVar3 != 0) | (uint)bVar19 << 1)) -
                 (uint)((2 << (long)puVar35 & uVar5) != 0);
          }
          if (param_3 != 0) {
            *(int *)(param_3 + lVar25 * 4) =
                 (int)(uVar2 * uVar4 + (1 << (ulong)(uVar1 & 0x1f)) + -1) >> (uVar1 & 0x1f);
          }
          lVar25 = lVar25 + 1;
          puVar29 = puVar29 + 0x18;
        } while (lVar25 < lVar24);
      }
      else {
        puVar29 = (uint *)(lStack_1b0 + 0xc);
        uVar1 = iStack_150 * 8;
        uVar2 = 0;
        if (uVar1 != 0) {
          uVar2 = ((iStack_2a0 + uVar1) - 1) / uVar1;
        }
        do {
          uVar3 = puVar29[-1];
          uVar5 = *puVar29;
          bVar16 = uVar3 >> 0x10 != 0;
          uVar7 = uVar3 >> ((ulong)bVar16 << 4);
          bVar17 = (uVar7 & 0xff00) != 0;
          uVar7 = uVar7 >> ((ulong)bVar17 << 3);
          bVar18 = (uVar7 & 0xf0) != 0;
          uVar7 = uVar7 >> ((ulong)bVar18 << 2);
          bVar19 = (uVar7 & 0xc) != 0;
          uVar6 = 2 << ((ulong)bVar19 << 1);
          uVar34 = (ulong)uVar6;
          uVar1 = (uint)bVar16 << 4 | (uint)bVar17 << 3 | (uint)bVar18 << 2 |
                  (uint)(uVar3 != 0) | (uint)bVar19 << 1;
          *(uint *)(param_1 + lVar25 * 4) = uVar2 * 8 * uVar3;
          if (param_2 != 0) {
            *(uint *)(param_2 + lVar25 * 4) = uVar5 * uVar4 * 8;
          }
          uVar3 = (uVar27 - uVar1) - (uint)((uVar6 & uVar7) != 0);
          if (param_4 != 0) {
            *(uint *)(param_4 + lVar25 * 4) = uVar3;
          }
          if (param_5 != 0) {
            uVar1 = *puVar29;
            bVar16 = uVar1 >> 0x10 != 0;
            uVar6 = uVar1 >> ((ulong)bVar16 << 4);
            bVar17 = (uVar6 & 0xff00) != 0;
            uVar6 = uVar6 >> ((ulong)bVar17 << 3);
            bVar18 = (uVar6 & 0xf0) != 0;
            uVar6 = uVar6 >> ((ulong)bVar18 << 2);
            bVar19 = (uVar6 & 0xc) != 0;
            uVar34 = (ulong)bVar19 << 1;
            uVar1 = (uint)bVar16 << 4 | (uint)bVar17 << 3 | (uint)bVar18 << 2 |
                    (uint)(uVar1 != 0) | (uint)bVar19 << 1;
            *(uint *)(param_5 + lVar25 * 4) = (uVar30 - uVar1) - (uint)((2 << uVar34 & uVar6) != 0);
          }
          puVar35 = (uint *)(ulong)uVar1;
          if (param_3 != 0) {
            *(int *)(param_3 + lVar25 * 4) =
                 (int)(uVar5 * uVar4 + (1 << (ulong)(uVar3 & 0x1f)) + -1) >> (uVar3 & 0x1f);
          }
          lVar25 = lVar25 + 1;
          puVar29 = puVar29 + 0x18;
        } while (lVar25 < lVar24);
      }
    }
    jpeg_destroy_decompress(auStack_2d0);
    uVar21 = 0;
  }
  else {
    jpeg_destroy_decompress(auStack_2d0);
    uVar21 = 0xffffffff;
  }
  if (*(long *)(lVar26 + 0x28) == lStack_58) {
    return;
  }
  auVar53 = __stack_chk_fail(uVar21);
  puVar29 = auVar53._8_8_;
  lVar24 = auVar53._0_8_;
  lVar26 = tpidr_el0;
  lStack_3e8 = *(long *)(lVar26 + 0x28);
  uStack_660 = jpeg_std_error(auStack_708);
  jpeg_CreateDecompress(&uStack_660,0x5a,0x278);
  uVar22 = uVar34;
  jpeg_mem_src(&uStack_660,puVar35,uVar34);
  iVar20 = jpeg_read_header(&uStack_660,1);
  puVar15 = PTR_GLJ_REAL_IDCT8X8_SCALES_02cbf8b0;
  if (iVar20 == 1) {
    if (lVar24 != 0) {
      if (iStack_628 == 1) {
        lVar25 = 0;
        do {
          fVar8 = (float)NEON_ucvtf((uint)*(ushort *)
                                           (alStack_5a8[*(int *)(lStack_540 + 0x10)] + lVar25 * 2));
          *(float *)(lVar24 + lVar25 * 4) = (float)*(double *)(puVar15 + lVar25 * 8) * fVar8;
          lVar25 = lVar25 + 1;
        } while (lVar25 != 0x40);
      }
      else {
        if (iStack_628 != 3) goto code_r0x026ea9bc;
        lVar25 = 0;
        pfVar28 = (float *)(lVar24 + 0x100);
        do {
          lVar24 = lVar25 * 8;
          lVar32 = lVar25 * 2;
          lVar25 = lVar25 + 1;
          fVar8 = (float)NEON_ucvtf((uint)*(ushort *)
                                           (alStack_5a8[*(int *)(lStack_540 + 0x10)] + lVar32));
          pfVar28[-0x40] = (float)*(double *)(puVar15 + lVar24) * fVar8;
          fVar8 = (float)NEON_ucvtf((uint)*(ushort *)
                                           (alStack_5a8[*(int *)(lStack_540 + 0x70)] + lVar32));
          *pfVar28 = (float)*(double *)(puVar15 + lVar24) * fVar8;
          fVar8 = (float)NEON_ucvtf((uint)*(ushort *)
                                           (alStack_5a8[*(int *)(lStack_540 + 0xd0)] + lVar32));
          pfVar28[0x40] = (float)*(double *)(puVar15 + lVar24) * fVar8;
          pfVar28 = pfVar28 + 1;
        } while (lVar25 != 0x40);
      }
    }
    lStack_728 = lVar26;
    if (puVar29 != (uint *)0x0) {
      uVar34 = (ulong)uStack_630;
      puVar35 = (uint *)(ulong)uStack_4e0;
      param_1 = (ulong)uStack_62c;
      param_7 = (uint *)(ulong)uStack_4dc;
      if (iStack_628 < 1) {
        uVar27 = 0;
      }
      else {
        lVar26 = 0;
        uVar27 = 0;
        puVar36 = (uint *)(lStack_540 + 8);
        do {
          lVar26 = lVar26 + 1;
          uVar30 = *puVar36 ^ uVar27;
          if ((int)*puVar36 <= (int)uVar27) {
            uVar30 = 0;
          }
          uVar27 = uVar30 ^ uVar27;
          puVar36 = puVar36 + 0x18;
        } while (lVar26 < iStack_628);
      }
      lVar26 = jpeg_read_coefficients(&uStack_660);
      auVar53._8_8_ = puVar29;
      auVar53._0_8_ = lVar26;
      if (0 < iStack_628) {
        bVar16 = uVar27 >> 0x10 != 0;
        uVar30 = uVar27 >> ((ulong)bVar16 << 4);
        bVar17 = (uVar30 & 0xff00) != 0;
        uVar30 = uVar30 >> ((ulong)bVar17 << 3);
        bVar18 = (uVar30 & 0xf0) != 0;
        uVar30 = uVar30 >> ((ulong)bVar18 << 2);
        bVar19 = (uVar30 & 0xc) != 0;
        uStack_4e0 = uStack_4e0 * 8;
        uVar1 = 0;
        if (uStack_4e0 != 0) {
          uVar1 = ((uStack_630 + uStack_4e0) - 1) / uStack_4e0;
        }
        uStack_4dc = uStack_4dc * 8;
        uStack_714 = 0;
        if (uStack_4dc != 0) {
          uStack_714 = ((uStack_62c + uStack_4dc) - 1) / uStack_4dc;
        }
        iStack_718 = uVar1 << 3;
        uStack_71c = (uint)bVar16 << 4 | (uint)bVar17 << 3 | (uint)bVar18 << 2 |
                     (uint)(uVar27 != 0) | (uint)bVar19 << 1;
        lVar24 = 0;
        iVar20 = iStack_628;
        if ((2 << ((ulong)bVar19 << 1) & uVar30) != 0) {
          uStack_71c = uStack_71c + 1;
        }
        do {
          lVar25 = lStack_540;
          puVar36 = (uint *)(lStack_540 + lVar24 * 0x60 + 0x20);
          if (*puVar36 == 0) {
            iVar23 = *(int *)(lStack_540 + lVar24 * 0x60 + 0xc);
            puVar37 = puVar29;
          }
          else {
            lVar32 = lStack_540 + lVar24 * 0x60;
            piVar38 = (int *)(lVar32 + 0xc);
            iVar23 = *piVar38;
            uVar34 = 0;
            param_7 = (uint *)(lVar32 + 0x1c);
            puStack_710 = puVar29;
            do {
              uVar22 = uVar34;
              param_1 = (**(code **)(lStack_658 + 0x40))
                                  (&uStack_660,*(undefined8 *)(lVar26 + lVar24 * 8),uVar34,iVar23,0)
              ;
              iVar23 = *piVar38;
              if (0 < iVar23) {
                uVar27 = *param_7;
                lVar32 = 0;
                do {
                  if (uVar27 != 0) {
                    uVar30 = 0;
                    do {
                      uVar22 = 0x80;
                      memcpy(puVar29,*(long *)(param_1 + lVar32 * 8) + (ulong)uVar30 * 0x80
                                      ,0x80);
                      uVar27 = *param_7;
                      uVar30 = uVar30 + 1;
                      puVar29 = puVar29 + 0x20;
                    } while (uVar30 < uVar27);
                    iVar23 = *piVar38;
                  }
                  lVar32 = lVar32 + 1;
                } while (lVar32 < iVar23);
              }
              uVar27 = iVar23 + (int)uVar34;
              uVar34 = (ulong)uVar27;
              puVar35 = puVar29;
              puVar37 = puStack_710;
              iVar20 = iStack_628;
            } while (uVar27 < *puVar36);
          }
          uVar27 = *(uint *)(lVar25 + lVar24 * 0x60 + 8);
          lVar24 = lVar24 + 1;
          bVar16 = uVar27 >> 0x10 != 0;
          uVar30 = uVar27 >> ((ulong)bVar16 << 4);
          bVar17 = (uVar30 & 0xff00) != 0;
          uVar30 = uVar30 >> ((ulong)bVar17 << 3);
          bVar18 = (uVar30 & 0xf0) != 0;
          uVar30 = uVar30 >> ((ulong)bVar18 << 2);
          bVar19 = (uVar30 & 0xc) != 0;
          uVar30 = (uStack_71c -
                   ((uint)bVar16 << 4 | (uint)bVar17 << 3 | (uint)bVar18 << 2 |
                   (uint)(uVar27 != 0) | (uint)bVar19 << 1)) -
                   (uint)((2 << ((ulong)bVar19 << 1) & uVar30) != 0);
          puVar29 = (uint *)((long)puVar37 +
                            (long)(int)(((int)((1 << (ulong)(uVar30 & 0x1f)) + iVar23 * uStack_714 +
                                              -1) >> (uVar30 & 0x1f)) *
                                       (iStack_718 * uVar27 << (ulong)(uVar30 + 3 & 0x1f))) * 2);
          auVar53._8_8_ = puVar29;
        } while (lVar24 < iVar20);
      }
    }
    jpeg_destroy_decompress(&uStack_660);
    uVar21 = 0;
    lVar26 = lStack_728;
  }
  else {
code_r0x026ea9bc:
    jpeg_destroy_decompress(&uStack_660);
    uVar21 = 0xffffffff;
  }
  if (*(long *)(lVar26 + 0x28) == lStack_3e8) {
    return;
  }
  auVar54 = __stack_chk_fail(uVar21);
  pcStack_738 = _ZN4Aska8JpegUtil9DecodeYuvEPPjPKvm;
  lVar24 = tpidr_el0;
  lStack_778 = *(long *)(lVar24 + 0x28);
  uStack_770 = auVar53._8_8_;
  puStack_768 = param_7;
  uStack_760 = param_1;
  puStack_758 = puVar35;
  uStack_750 = uVar34;
  uStack_748 = auVar53._0_8_;
  lStack_740 = lVar26;
  auStack_9f0[0] = jpeg_std_error(auStack_ab0 + 6);
  jpeg_CreateDecompress(auStack_9f0,0x5a,0x278);
  jpeg_mem_src(auStack_9f0,auVar54._8_8_,uVar22);
  iVar20 = jpeg_read_header(auStack_9f0,1);
  if ((iVar20 != 1) || (uVar34 = (ulong)(int)uStack_9b8, (uStack_9b8 | 2) != 3)) {
    jpeg_destroy_decompress(auStack_9f0);
    uVar21 = 0xffffffff;
    goto code_r0x026eb0ec;
  }
  if (auVar54._0_8_ != 0) {
    lVar26 = 0;
    uVar27 = 0;
    puVar35 = (uint *)(lStack_8d0 + 0xc);
    do {
      lVar26 = lVar26 + 1;
      uVar30 = *puVar35 ^ uVar27;
      if ((int)*puVar35 <= (int)uVar27) {
        uVar30 = 0;
      }
      uVar27 = uVar30 ^ uVar27;
      puVar35 = puVar35 + 0x18;
    } while (lVar26 < (long)uVar34);
    bVar16 = uVar27 >> 0x10 != 0;
    uVar30 = iStack_870 * 8;
    uVar1 = uVar27 >> ((ulong)bVar16 << 4);
    bVar17 = (uVar1 & 0xff00) != 0;
    uVar2 = 0;
    if (uVar30 != 0) {
      uVar2 = ((iStack_9c0 + uVar30) - 1) / uVar30;
    }
    uVar1 = uVar1 >> ((ulong)bVar17 << 3);
    bVar18 = (uVar1 & 0xf0) != 0;
    uVar1 = uVar1 >> ((ulong)bVar18 << 2);
    bVar19 = (uVar1 & 0xc) != 0;
    uVar27 = (uint)bVar16 << 4 | (uint)bVar17 << 3 | (uint)bVar18 << 2 |
             (uint)(uVar27 != 0) | (uint)bVar19 << 1;
    if ((2 << ((ulong)bVar19 << 1) & uVar1) != 0) {
      uVar27 = uVar27 + 1;
    }
    uVar22 = uVar34;
    if ((long)uVar34 < 2) {
      uVar22 = 1;
    }
    iVar20 = uVar2 * 8;
    if (uVar22 < 4) {
      uVar31 = 0;
code_r0x026eaf54:
      puVar35 = (uint *)(lStack_8d0 + uVar31 * 0x60 + 0xc);
      do {
        uVar22 = uVar31 + 1;
        auStack_ab0[uVar31 + 3] = iVar20 * puVar35[-1];
        uVar30 = *puVar35;
        bVar16 = uVar30 >> 0x10 != 0;
        uVar1 = uVar30 >> ((ulong)bVar16 << 4);
        bVar17 = (uVar1 & 0xff00) != 0;
        uVar1 = uVar1 >> ((ulong)bVar17 << 3);
        bVar18 = (uVar1 & 0xf0) != 0;
        uVar1 = uVar1 >> ((ulong)bVar18 << 2);
        bVar19 = (uVar1 & 0xc) != 0;
        auStack_ab0[uVar31] =
             (uVar27 - ((uint)bVar16 << 4 | (uint)bVar17 << 3 | (uint)bVar18 << 2 |
                       (uint)(uVar30 != 0) | (uint)bVar19 << 1)) -
             (uint)((2 << ((ulong)bVar19 << 1) & uVar1) != 0);
        uVar31 = uVar22;
        puVar35 = puVar35 + 0x18;
      } while ((long)uVar22 < (long)uVar34);
    }
    else {
      uVar31 = uVar22 & 0x7ffffffffffffffc;
      if (uVar31 == 0) goto code_r0x026eaf54;
      piVar38 = (int *)(lStack_8d0 + 200);
      puVar35 = auStack_ab0;
      puVar29 = auStack_ab0 + 3;
      uVar33 = uVar31;
      do {
        iVar23 = piVar38[-0x30];
        uVar33 = uVar33 - 4;
        iVar40 = piVar38[-0x18];
        iVar41 = piVar38[0x18];
        puVar29[2] = iVar20 * *piVar38;
        puVar29[3] = iVar20 * iVar41;
        *puVar29 = iVar20 * iVar23;
        puVar29[1] = iVar20 * iVar40;
        uVar30 = piVar38[-0x2f];
        auVar39._4_4_ = piVar38[-0x17];
        auVar39._0_4_ = uVar30;
        auVar39._8_4_ = piVar38[1];
        puVar36 = (uint *)(piVar38 + 0x19);
        piVar38 = piVar38 + 0x60;
        auVar39._12_4_ = *puVar36;
        uVar42 = CONCAT14(-(0xffff < auVar39._4_4_),(uint)(-(0xffff < uVar30) & 0x10)) &
                 0x10ffffffff;
        bVar47 = -(0xffff < auVar39._8_4_) & 0x10;
        bVar50 = -(0xffff < auVar39._12_4_) & 0x10;
        bVar12 = (byte)(uVar42 >> 0x20);
        auVar9._4_4_ = -(uint)bVar12;
        auVar9._0_4_ = -(int)uVar42;
        auVar9._8_4_ = -(uint)bVar47;
        auVar9._12_4_ = -(uint)bVar50;
        auVar53 = NEON_ushl(auVar39,auVar9,4);
        uVar43 = CONCAT14(-((auVar53._4_4_ & 0xff00) != 0),
                          (uint)(-((auVar53._0_4_ & 0xff00) != 0) & 8)) & 0x8ffffffff;
        bVar48 = -((auVar53._8_4_ & 0xff00) != 0) & 8;
        bVar51 = -((auVar53._12_4_ & 0xff00) != 0) & 8;
        bVar13 = (byte)(uVar43 >> 0x20);
        auVar10._4_4_ = -(uint)bVar13;
        auVar10._0_4_ = -(int)uVar43;
        auVar10._8_4_ = -(uint)bVar48;
        auVar10._12_4_ = -(uint)bVar51;
        auVar53 = NEON_ushl(auVar53,auVar10,4);
        uVar44 = CONCAT14(-((auVar53._4_4_ & 0xf0) != 0),(uint)(-((auVar53._0_4_ & 0xf0) != 0) & 4))
                 & 0x4ffffffff;
        bVar49 = -((auVar53._8_4_ & 0xf0) != 0) & 4;
        bVar52 = -((auVar53._12_4_ & 0xf0) != 0) & 4;
        bVar14 = (byte)(uVar44 >> 0x20);
        auVar11._4_4_ = -(uint)bVar14;
        auVar11._0_4_ = -(int)uVar44;
        auVar11._8_4_ = -(uint)bVar49;
        auVar11._12_4_ = -(uint)bVar52;
        auVar53 = NEON_ushl(auVar53,auVar11,4);
        auVar45._0_5_ =
             CONCAT14(-((auVar53._4_4_ & 0xc) != 0),(uint)(-((auVar53._0_4_ & 0xc) != 0) & 2)) &
             0x2ffffffff;
        auVar45._5_3_ = 0;
        auVar45[8] = -((auVar53._8_4_ & 0xc) != 0) & 2;
        auVar45._9_3_ = 0;
        auVar45[0xc] = -((auVar53._12_4_ & 0xc) != 0) & 2;
        auVar45._13_3_ = 0;
        auVar46[8] = 2;
        auVar46._0_8_ = 0x200000002;
        auVar46._9_3_ = 0;
        auVar46[0xc] = 2;
        auVar46._13_3_ = 0;
        auVar46 = NEON_ushl(auVar46,auVar45,4);
        puVar35[2] = (uVar27 - (byte)(bVar47 | ~-(auVar39._8_4_ == 0) & 1U | bVar48 | bVar49 |
                                     auVar45[8])) - (uint)((auVar46._8_4_ & auVar53._8_4_) != 0);
        puVar35[3] = (uVar27 - (byte)(bVar50 | ~-(auVar39._12_4_ == 0) & 1U | bVar51 | bVar52 |
                                     auVar45[0xc])) - (uint)((auVar46._12_4_ & auVar53._12_4_) != 0)
        ;
        *puVar35 = (uVar27 - (byte)((byte)uVar42 | ~-(uVar30 == 0) & 1U | (byte)uVar43 |
                                    (byte)uVar44 | (byte)auVar45._0_5_)) -
                   (uint)((auVar46._0_4_ & auVar53._0_4_) != 0);
        puVar35[1] = (uVar27 - (byte)(bVar12 | ~-(auVar39._4_4_ == 0) & 1U | bVar13 | bVar14 |
                                     (byte)(auVar45._0_5_ >> 0x20))) -
                     (uint)((auVar46._4_4_ & auVar53._4_4_) != 0);
        puVar35 = puVar35 + 4;
        puVar29 = puVar29 + 4;
      } while (uVar33 != 0);
      if (uVar22 != uVar31) goto code_r0x026eaf54;
    }
    apuStack_c48[0] = auStack_b30;
    apuStack_c48[1] = auStack_bb0;
    apuStack_c48[2] = auStack_c30;
    uStack_997 = 1;
    uStack_990 = 0;
    uStack_994 = 0;
    jpeg_start_decompress(auStack_9f0);
    if (uStack_958 < uStack_978) {
      do {
        if (0 < (int)uStack_9b8) {
          lVar26 = 0;
          do {
            uVar27 = 0x10 >> (ulong)(auStack_ab0[lVar26] & 0x1f);
            if (0 < (int)uVar27) {
              uVar30 = auStack_ab0[lVar26 + 3];
              lVar25 = 0;
              lVar32 = (long)(int)uVar30 *
                       (long)(int)(uStack_958 >> (ulong)(auStack_ab0[lVar26] & 0x1f));
              do {
                *(long *)(apuStack_c48[lVar26] + lVar25 * 8) =
                     *(long *)(auVar54._0_8_ + lVar26 * 8) + lVar32;
                lVar25 = lVar25 + 1;
                lVar32 = lVar32 + (int)uVar30;
              } while (lVar25 < (int)uVar27);
            }
            lVar26 = lVar26 + 1;
          } while (lVar26 < (int)uStack_9b8);
        }
        jpeg_read_raw_data(auStack_9f0,apuStack_c48,0x10);
      } while (uStack_958 < uStack_978);
    }
    jpeg_finish_decompress(auStack_9f0);
  }
  jpeg_destroy_decompress(auStack_9f0);
  uVar21 = 0;
code_r0x026eb0ec:
  if (*(long *)(lVar24 + 0x28) != lStack_778) {
    __stack_chk_fail(uVar21);
    return;
  }
  return;
}

// ==== Aska::JpegUtil::DecodeQuantCoef(float*, short*, void const*, unsigned long)
// vaddr 0x25ea894 | ghidra 0x26ea894 | size 1116 | symbol _ZN4Aska8JpegUtil15DecodeQuantCoefEPfPsPKvm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8JpegUtil15DecodeQuantCoefEPfPsPKvm
               (long param_1,ulong param_2,ulong param_3,ulong param_4)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  float fVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  byte bVar7;
  byte bVar8;
  byte bVar9;
  undefined *puVar10;
  bool bVar11;
  bool bVar12;
  bool bVar13;
  bool bVar14;
  int iVar15;
  undefined8 uVar16;
  ulong uVar17;
  int iVar18;
  long lVar19;
  long lVar20;
  float *pfVar21;
  ulong uVar22;
  long lVar23;
  long lVar24;
  uint *puVar25;
  ulong uVar26;
  uint uVar27;
  ulong unaff_x23;
  uint *unaff_x24;
  uint uVar28;
  uint *puVar29;
  ulong uVar30;
  int *piVar31;
  int iVar35;
  int iVar36;
  undefined1 auVar32 [16];
  undefined1 auVar33 [16];
  undefined1 auVar34 [16];
  uint5 uVar37;
  uint5 uVar38;
  uint5 uVar39;
  byte bVar41;
  byte bVar42;
  byte bVar43;
  byte bVar44;
  byte bVar45;
  byte bVar46;
  undefined1 auVar40 [16];
  undefined1 auVar47 [16];
  undefined1 *apuStack_8c8 [3];
  undefined1 auStack_8b0 [128];
  undefined1 auStack_830 [128];
  undefined1 auStack_7b0 [128];
  uint auStack_730 [48];
  undefined8 auStack_670 [6];
  int iStack_640;
  uint uStack_638;
  undefined1 uStack_617;
  undefined4 uStack_614;
  undefined1 uStack_610;
  uint uStack_5f8;
  uint uStack_5d8;
  long lStack_550;
  int iStack_4f0;
  long lStack_3f8;
  ulong uStack_3f0;
  uint *puStack_3e8;
  ulong uStack_3e0;
  ulong uStack_3d8;
  ulong uStack_3d0;
  long lStack_3c8;
  long lStack_3c0;
  code *pcStack_3b8;
  long lStack_3a8;
  uint uStack_39c;
  int iStack_398;
  uint uStack_394;
  ulong uStack_390;
  undefined1 auStack_388 [168];
  undefined8 uStack_2e0;
  long lStack_2d8;
  uint uStack_2b0;
  uint uStack_2ac;
  int iStack_2a8;
  long alStack_228 [13];
  long lStack_1c0;
  uint uStack_160;
  uint uStack_15c;
  long lStack_68;
  
  lVar20 = tpidr_el0;
  lStack_68 = *(long *)(lVar20 + 0x28);
  uStack_2e0 = jpeg_std_error(auStack_388);
  jpeg_CreateDecompress(&uStack_2e0,0x5a,0x278);
  uVar17 = param_4;
  jpeg_mem_src(&uStack_2e0,param_3,param_4);
  iVar15 = jpeg_read_header(&uStack_2e0,1);
  puVar10 = PTR_GLJ_REAL_IDCT8X8_SCALES_02cbf8b0;
  if (iVar15 == 1) {
    if (param_1 != 0) {
      if (iStack_2a8 == 1) {
        lVar19 = 0;
        do {
          fVar4 = (float)NEON_ucvtf((uint)*(ushort *)
                                           (alStack_228[*(int *)(lStack_1c0 + 0x10)] + lVar19 * 2));
          *(float *)(param_1 + lVar19 * 4) = (float)*(double *)(puVar10 + lVar19 * 8) * fVar4;
          lVar19 = lVar19 + 1;
        } while (lVar19 != 0x40);
      }
      else {
        if (iStack_2a8 != 3) goto code_r0x026ea9bc;
        lVar19 = 0;
        pfVar21 = (float *)(param_1 + 0x100);
        do {
          lVar23 = lVar19 * 8;
          lVar24 = lVar19 * 2;
          lVar19 = lVar19 + 1;
          fVar4 = (float)NEON_ucvtf((uint)*(ushort *)
                                           (alStack_228[*(int *)(lStack_1c0 + 0x10)] + lVar24));
          pfVar21[-0x40] = (float)*(double *)(puVar10 + lVar23) * fVar4;
          fVar4 = (float)NEON_ucvtf((uint)*(ushort *)
                                           (alStack_228[*(int *)(lStack_1c0 + 0x70)] + lVar24));
          *pfVar21 = (float)*(double *)(puVar10 + lVar23) * fVar4;
          fVar4 = (float)NEON_ucvtf((uint)*(ushort *)
                                           (alStack_228[*(int *)(lStack_1c0 + 0xd0)] + lVar24));
          pfVar21[0x40] = (float)*(double *)(puVar10 + lVar23) * fVar4;
          pfVar21 = pfVar21 + 1;
        } while (lVar19 != 0x40);
      }
    }
    lStack_3a8 = lVar20;
    if (param_2 != 0) {
      param_4 = (ulong)uStack_2b0;
      param_3 = (ulong)uStack_160;
      unaff_x23 = (ulong)uStack_2ac;
      unaff_x24 = (uint *)(ulong)uStack_15c;
      if (iStack_2a8 < 1) {
        uVar28 = 0;
      }
      else {
        lVar20 = 0;
        uVar28 = 0;
        puVar29 = (uint *)(lStack_1c0 + 8);
        do {
          lVar20 = lVar20 + 1;
          uVar27 = *puVar29 ^ uVar28;
          if ((int)*puVar29 <= (int)uVar28) {
            uVar27 = 0;
          }
          uVar28 = uVar27 ^ uVar28;
          puVar29 = puVar29 + 0x18;
        } while (lVar20 < iStack_2a8);
      }
      param_1 = jpeg_read_coefficients(&uStack_2e0);
      if (0 < iStack_2a8) {
        bVar11 = uVar28 >> 0x10 != 0;
        uVar27 = uVar28 >> ((ulong)bVar11 << 4);
        bVar12 = (uVar27 & 0xff00) != 0;
        uVar27 = uVar27 >> ((ulong)bVar12 << 3);
        bVar13 = (uVar27 & 0xf0) != 0;
        uVar27 = uVar27 >> ((ulong)bVar13 << 2);
        bVar14 = (uVar27 & 0xc) != 0;
        uStack_160 = uStack_160 * 8;
        uVar2 = 0;
        if (uStack_160 != 0) {
          uVar2 = ((uStack_2b0 + uStack_160) - 1) / uStack_160;
        }
        uStack_15c = uStack_15c * 8;
        uStack_394 = 0;
        if (uStack_15c != 0) {
          uStack_394 = ((uStack_2ac + uStack_15c) - 1) / uStack_15c;
        }
        iStack_398 = uVar2 << 3;
        uStack_39c = (uint)bVar11 << 4 | (uint)bVar12 << 3 | (uint)bVar13 << 2 |
                     (uint)(uVar28 != 0) | (uint)bVar14 << 1;
        lVar20 = 0;
        iVar15 = iStack_2a8;
        if ((2 << ((ulong)bVar14 << 1) & uVar27) != 0) {
          uStack_39c = uStack_39c + 1;
        }
        do {
          lVar19 = lStack_1c0;
          puVar29 = (uint *)(lStack_1c0 + lVar20 * 0x60 + 0x20);
          if (*puVar29 == 0) {
            iVar18 = *(int *)(lStack_1c0 + lVar20 * 0x60 + 0xc);
            uVar30 = param_2;
          }
          else {
            lVar23 = lStack_1c0 + lVar20 * 0x60;
            piVar31 = (int *)(lVar23 + 0xc);
            iVar18 = *piVar31;
            param_4 = 0;
            unaff_x24 = (uint *)(lVar23 + 0x1c);
            uStack_390 = param_2;
            do {
              uVar17 = param_4;
              unaff_x23 = (**(code **)(lStack_2d8 + 0x40))
                                    (&uStack_2e0,*(undefined8 *)(param_1 + lVar20 * 8),param_4,
                                     iVar18,0);
              iVar18 = *piVar31;
              if (0 < iVar18) {
                uVar28 = *unaff_x24;
                lVar23 = 0;
                do {
                  if (uVar28 != 0) {
                    uVar27 = 0;
                    do {
                      uVar17 = 0x80;
                      memcpy(param_2,*(long *)(unaff_x23 + lVar23 * 8) +
                                              (ulong)uVar27 * 0x80,0x80);
                      uVar28 = *unaff_x24;
                      uVar27 = uVar27 + 1;
                      param_2 = param_2 + 0x80;
                    } while (uVar27 < uVar28);
                    iVar18 = *piVar31;
                  }
                  lVar23 = lVar23 + 1;
                } while (lVar23 < iVar18);
              }
              uVar28 = iVar18 + (int)param_4;
              param_4 = (ulong)uVar28;
              param_3 = param_2;
              uVar30 = uStack_390;
              iVar15 = iStack_2a8;
            } while (uVar28 < *puVar29);
          }
          uVar28 = *(uint *)(lVar19 + lVar20 * 0x60 + 8);
          lVar20 = lVar20 + 1;
          bVar11 = uVar28 >> 0x10 != 0;
          uVar27 = uVar28 >> ((ulong)bVar11 << 4);
          bVar12 = (uVar27 & 0xff00) != 0;
          uVar27 = uVar27 >> ((ulong)bVar12 << 3);
          bVar13 = (uVar27 & 0xf0) != 0;
          uVar27 = uVar27 >> ((ulong)bVar13 << 2);
          bVar14 = (uVar27 & 0xc) != 0;
          uVar27 = (uStack_39c -
                   ((uint)bVar11 << 4 | (uint)bVar12 << 3 | (uint)bVar13 << 2 |
                   (uint)(uVar28 != 0) | (uint)bVar14 << 1)) -
                   (uint)((2 << ((ulong)bVar14 << 1) & uVar27) != 0);
          param_2 = uVar30 + (long)(int)(((int)((1 << (ulong)(uVar27 & 0x1f)) + iVar18 * uStack_394
                                               + -1) >> (uVar27 & 0x1f)) *
                                        (iStack_398 * uVar28 << (ulong)(uVar27 + 3 & 0x1f))) * 2;
        } while (lVar20 < iVar15);
      }
    }
    jpeg_destroy_decompress(&uStack_2e0);
    uVar16 = 0;
    lVar20 = lStack_3a8;
  }
  else {
code_r0x026ea9bc:
    jpeg_destroy_decompress(&uStack_2e0);
    uVar16 = 0xffffffff;
  }
  if (*(long *)(lVar20 + 0x28) == lStack_68) {
    return;
  }
  auVar47 = __stack_chk_fail(uVar16);
  pcStack_3b8 = _ZN4Aska8JpegUtil9DecodeYuvEPPjPKvm;
  lVar19 = tpidr_el0;
  lStack_3f8 = *(long *)(lVar19 + 0x28);
  uStack_3f0 = param_2;
  puStack_3e8 = unaff_x24;
  uStack_3e0 = unaff_x23;
  uStack_3d8 = param_3;
  uStack_3d0 = param_4;
  lStack_3c8 = param_1;
  lStack_3c0 = lVar20;
  auStack_670[0] = jpeg_std_error(auStack_730 + 6);
  jpeg_CreateDecompress(auStack_670,0x5a,0x278);
  jpeg_mem_src(auStack_670,auVar47._8_8_,uVar17);
  iVar15 = jpeg_read_header(auStack_670,1);
  if ((iVar15 != 1) || (uVar17 = (ulong)(int)uStack_638, (uStack_638 | 2) != 3)) {
    jpeg_destroy_decompress(auStack_670);
    uVar16 = 0xffffffff;
    goto code_r0x026eb0ec;
  }
  if (auVar47._0_8_ != 0) {
    lVar20 = 0;
    uVar28 = 0;
    puVar29 = (uint *)(lStack_550 + 0xc);
    do {
      lVar20 = lVar20 + 1;
      uVar27 = *puVar29 ^ uVar28;
      if ((int)*puVar29 <= (int)uVar28) {
        uVar27 = 0;
      }
      uVar28 = uVar27 ^ uVar28;
      puVar29 = puVar29 + 0x18;
    } while (lVar20 < (long)uVar17);
    bVar11 = uVar28 >> 0x10 != 0;
    uVar27 = iStack_4f0 * 8;
    uVar2 = uVar28 >> ((ulong)bVar11 << 4);
    bVar12 = (uVar2 & 0xff00) != 0;
    uVar3 = 0;
    if (uVar27 != 0) {
      uVar3 = ((iStack_640 + uVar27) - 1) / uVar27;
    }
    uVar2 = uVar2 >> ((ulong)bVar12 << 3);
    bVar13 = (uVar2 & 0xf0) != 0;
    uVar2 = uVar2 >> ((ulong)bVar13 << 2);
    bVar14 = (uVar2 & 0xc) != 0;
    uVar28 = (uint)bVar11 << 4 | (uint)bVar12 << 3 | (uint)bVar13 << 2 |
             (uint)(uVar28 != 0) | (uint)bVar14 << 1;
    if ((2 << ((ulong)bVar14 << 1) & uVar2) != 0) {
      uVar28 = uVar28 + 1;
    }
    uVar30 = uVar17;
    if ((long)uVar17 < 2) {
      uVar30 = 1;
    }
    iVar15 = uVar3 * 8;
    if (uVar30 < 4) {
      uVar22 = 0;
code_r0x026eaf54:
      puVar29 = (uint *)(lStack_550 + uVar22 * 0x60 + 0xc);
      do {
        uVar30 = uVar22 + 1;
        auStack_730[uVar22 + 3] = iVar15 * puVar29[-1];
        uVar27 = *puVar29;
        bVar11 = uVar27 >> 0x10 != 0;
        uVar2 = uVar27 >> ((ulong)bVar11 << 4);
        bVar12 = (uVar2 & 0xff00) != 0;
        uVar2 = uVar2 >> ((ulong)bVar12 << 3);
        bVar13 = (uVar2 & 0xf0) != 0;
        uVar2 = uVar2 >> ((ulong)bVar13 << 2);
        bVar14 = (uVar2 & 0xc) != 0;
        auStack_730[uVar22] =
             (uVar28 - ((uint)bVar11 << 4 | (uint)bVar12 << 3 | (uint)bVar13 << 2 |
                       (uint)(uVar27 != 0) | (uint)bVar14 << 1)) -
             (uint)((2 << ((ulong)bVar14 << 1) & uVar2) != 0);
        uVar22 = uVar30;
        puVar29 = puVar29 + 0x18;
      } while ((long)uVar30 < (long)uVar17);
    }
    else {
      uVar22 = uVar30 & 0x7ffffffffffffffc;
      if (uVar22 == 0) goto code_r0x026eaf54;
      piVar31 = (int *)(lStack_550 + 200);
      puVar29 = auStack_730;
      puVar25 = auStack_730 + 3;
      uVar26 = uVar22;
      do {
        iVar18 = piVar31[-0x30];
        uVar26 = uVar26 - 4;
        iVar35 = piVar31[-0x18];
        iVar36 = piVar31[0x18];
        puVar25[2] = iVar15 * *piVar31;
        puVar25[3] = iVar15 * iVar36;
        *puVar25 = iVar15 * iVar18;
        puVar25[1] = iVar15 * iVar35;
        uVar27 = piVar31[-0x2f];
        auVar32._4_4_ = piVar31[-0x17];
        auVar32._0_4_ = uVar27;
        auVar32._8_4_ = piVar31[1];
        puVar1 = (uint *)(piVar31 + 0x19);
        piVar31 = piVar31 + 0x60;
        auVar32._12_4_ = *puVar1;
        uVar37 = CONCAT14(-(0xffff < auVar32._4_4_),(uint)(-(0xffff < uVar27) & 0x10)) &
                 0x10ffffffff;
        bVar41 = -(0xffff < auVar32._8_4_) & 0x10;
        bVar44 = -(0xffff < auVar32._12_4_) & 0x10;
        bVar7 = (byte)(uVar37 >> 0x20);
        auVar34._4_4_ = -(uint)bVar7;
        auVar34._0_4_ = -(int)uVar37;
        auVar34._8_4_ = -(uint)bVar41;
        auVar34._12_4_ = -(uint)bVar44;
        auVar33 = NEON_ushl(auVar32,auVar34,4);
        uVar38 = CONCAT14(-((auVar33._4_4_ & 0xff00) != 0),
                          (uint)(-((auVar33._0_4_ & 0xff00) != 0) & 8)) & 0x8ffffffff;
        bVar42 = -((auVar33._8_4_ & 0xff00) != 0) & 8;
        bVar45 = -((auVar33._12_4_ & 0xff00) != 0) & 8;
        bVar8 = (byte)(uVar38 >> 0x20);
        auVar5._4_4_ = -(uint)bVar8;
        auVar5._0_4_ = -(int)uVar38;
        auVar5._8_4_ = -(uint)bVar42;
        auVar5._12_4_ = -(uint)bVar45;
        auVar33 = NEON_ushl(auVar33,auVar5,4);
        uVar39 = CONCAT14(-((auVar33._4_4_ & 0xf0) != 0),(uint)(-((auVar33._0_4_ & 0xf0) != 0) & 4))
                 & 0x4ffffffff;
        bVar43 = -((auVar33._8_4_ & 0xf0) != 0) & 4;
        bVar46 = -((auVar33._12_4_ & 0xf0) != 0) & 4;
        bVar9 = (byte)(uVar39 >> 0x20);
        auVar6._4_4_ = -(uint)bVar9;
        auVar6._0_4_ = -(int)uVar39;
        auVar6._8_4_ = -(uint)bVar43;
        auVar6._12_4_ = -(uint)bVar46;
        auVar34 = NEON_ushl(auVar33,auVar6,4);
        auVar40._0_5_ =
             CONCAT14(-((auVar34._4_4_ & 0xc) != 0),(uint)(-((auVar34._0_4_ & 0xc) != 0) & 2)) &
             0x2ffffffff;
        auVar40._5_3_ = 0;
        auVar40[8] = -((auVar34._8_4_ & 0xc) != 0) & 2;
        auVar40._9_3_ = 0;
        auVar40[0xc] = -((auVar34._12_4_ & 0xc) != 0) & 2;
        auVar40._13_3_ = 0;
        auVar33[8] = 2;
        auVar33._0_8_ = 0x200000002;
        auVar33._9_3_ = 0;
        auVar33[0xc] = 2;
        auVar33._13_3_ = 0;
        auVar33 = NEON_ushl(auVar33,auVar40,4);
        puVar29[2] = (uVar28 - (byte)(bVar41 | ~-(auVar32._8_4_ == 0) & 1U | bVar42 | bVar43 |
                                     auVar40[8])) - (uint)((auVar33._8_4_ & auVar34._8_4_) != 0);
        puVar29[3] = (uVar28 - (byte)(bVar44 | ~-(auVar32._12_4_ == 0) & 1U | bVar45 | bVar46 |
                                     auVar40[0xc])) - (uint)((auVar33._12_4_ & auVar34._12_4_) != 0)
        ;
        *puVar29 = (uVar28 - (byte)((byte)uVar37 | ~-(uVar27 == 0) & 1U | (byte)uVar38 |
                                    (byte)uVar39 | (byte)auVar40._0_5_)) -
                   (uint)((auVar33._0_4_ & auVar34._0_4_) != 0);
        puVar29[1] = (uVar28 - (byte)(bVar7 | ~-(auVar32._4_4_ == 0) & 1U | bVar8 | bVar9 |
                                     (byte)(auVar40._0_5_ >> 0x20))) -
                     (uint)((auVar33._4_4_ & auVar34._4_4_) != 0);
        puVar29 = puVar29 + 4;
        puVar25 = puVar25 + 4;
      } while (uVar26 != 0);
      if (uVar30 != uVar22) goto code_r0x026eaf54;
    }
    apuStack_8c8[0] = auStack_7b0;
    apuStack_8c8[1] = auStack_830;
    apuStack_8c8[2] = auStack_8b0;
    uStack_617 = 1;
    uStack_610 = 0;
    uStack_614 = 0;
    jpeg_start_decompress(auStack_670);
    if (uStack_5d8 < uStack_5f8) {
      do {
        if (0 < (int)uStack_638) {
          lVar20 = 0;
          do {
            uVar28 = 0x10 >> (ulong)(auStack_730[lVar20] & 0x1f);
            if (0 < (int)uVar28) {
              uVar27 = auStack_730[lVar20 + 3];
              lVar23 = 0;
              lVar24 = (long)(int)uVar27 *
                       (long)(int)(uStack_5d8 >> (ulong)(auStack_730[lVar20] & 0x1f));
              do {
                *(long *)(apuStack_8c8[lVar20] + lVar23 * 8) =
                     *(long *)(auVar47._0_8_ + lVar20 * 8) + lVar24;
                lVar23 = lVar23 + 1;
                lVar24 = lVar24 + (int)uVar27;
              } while (lVar23 < (int)uVar28);
            }
            lVar20 = lVar20 + 1;
          } while (lVar20 < (int)uStack_638);
        }
        jpeg_read_raw_data(auStack_670,apuStack_8c8,0x10);
      } while (uStack_5d8 < uStack_5f8);
    }
    jpeg_finish_decompress(auStack_670);
  }
  jpeg_destroy_decompress(auStack_670);
  uVar16 = 0;
code_r0x026eb0ec:
  if (*(long *)(lVar19 + 0x28) == lStack_3f8) {
    return;
  }
  __stack_chk_fail(uVar16);
  return;
}

// ==== Aska::JpegUtil::DecodeYuv(unsigned int**, void const*, unsigned long)
// vaddr 0x25eacf0 | ghidra 0x26eacf0 | size 1064 | symbol _ZN4Aska8JpegUtil9DecodeYuvEPPjPKvm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8JpegUtil9DecodeYuvEPPjPKvm(long param_1,undefined8 param_2,undefined8 param_3)

{
  uint *puVar1;
  ulong uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  long lVar7;
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  byte bVar10;
  byte bVar11;
  byte bVar12;
  bool bVar13;
  bool bVar14;
  bool bVar15;
  bool bVar16;
  int iVar17;
  undefined8 uVar18;
  ulong uVar19;
  uint uVar20;
  long lVar21;
  long lVar22;
  uint *puVar23;
  ulong uVar24;
  long lVar25;
  int *piVar26;
  uint *puVar27;
  ulong uVar28;
  int iVar32;
  int iVar33;
  undefined1 auVar29 [16];
  undefined1 auVar30 [16];
  undefined1 auVar31 [16];
  uint5 uVar34;
  uint5 uVar35;
  uint5 uVar36;
  byte bVar38;
  byte bVar39;
  byte bVar40;
  byte bVar41;
  byte bVar42;
  byte bVar43;
  undefined1 auVar37 [16];
  undefined1 *apuStack_518 [3];
  undefined1 auStack_500 [128];
  undefined1 auStack_480 [128];
  undefined1 auStack_400 [128];
  uint auStack_380 [48];
  undefined8 auStack_2c0 [6];
  int iStack_290;
  uint uStack_288;
  undefined1 uStack_267;
  undefined4 uStack_264;
  undefined1 uStack_260;
  uint uStack_248;
  uint uStack_228;
  long lStack_1a0;
  int iStack_140;
  long lStack_48;
  
  lVar7 = tpidr_el0;
  lStack_48 = *(long *)(lVar7 + 0x28);
  auStack_2c0[0] = jpeg_std_error(auStack_380 + 6);
  jpeg_CreateDecompress(auStack_2c0,0x5a,0x278);
  jpeg_mem_src(auStack_2c0,param_2,param_3);
  iVar17 = jpeg_read_header(auStack_2c0,1);
  if ((iVar17 != 1) || (uVar19 = (ulong)(int)uStack_288, (uStack_288 | 2) != 3)) {
    jpeg_destroy_decompress(auStack_2c0);
    uVar18 = 0xffffffff;
    goto code_r0x026eb0ec;
  }
  if (param_1 != 0) {
    lVar21 = 0;
    uVar20 = 0;
    puVar23 = (uint *)(lStack_1a0 + 0xc);
    do {
      lVar21 = lVar21 + 1;
      uVar3 = *puVar23 ^ uVar20;
      if ((int)*puVar23 <= (int)uVar20) {
        uVar3 = 0;
      }
      uVar20 = uVar3 ^ uVar20;
      puVar23 = puVar23 + 0x18;
    } while (lVar21 < (long)uVar19);
    bVar13 = uVar20 >> 0x10 != 0;
    uVar3 = iStack_140 * 8;
    uVar5 = uVar20 >> ((ulong)bVar13 << 4);
    bVar14 = (uVar5 & 0xff00) != 0;
    uVar6 = 0;
    if (uVar3 != 0) {
      uVar6 = ((iStack_290 + uVar3) - 1) / uVar3;
    }
    uVar5 = uVar5 >> ((ulong)bVar14 << 3);
    bVar15 = (uVar5 & 0xf0) != 0;
    uVar5 = uVar5 >> ((ulong)bVar15 << 2);
    bVar16 = (uVar5 & 0xc) != 0;
    uVar20 = (uint)bVar13 << 4 | (uint)bVar14 << 3 | (uint)bVar15 << 2 |
             (uint)(uVar20 != 0) | (uint)bVar16 << 1;
    if ((2 << ((ulong)bVar16 << 1) & uVar5) != 0) {
      uVar20 = uVar20 + 1;
    }
    uVar2 = uVar19;
    if ((long)uVar19 < 2) {
      uVar2 = 1;
    }
    iVar17 = uVar6 * 8;
    if (uVar2 < 4) {
      uVar24 = 0;
code_r0x026eaf54:
      puVar23 = (uint *)(lStack_1a0 + uVar24 * 0x60 + 0xc);
      do {
        uVar2 = uVar24 + 1;
        auStack_380[uVar24 + 3] = iVar17 * puVar23[-1];
        uVar3 = *puVar23;
        bVar13 = uVar3 >> 0x10 != 0;
        uVar5 = uVar3 >> ((ulong)bVar13 << 4);
        bVar14 = (uVar5 & 0xff00) != 0;
        uVar5 = uVar5 >> ((ulong)bVar14 << 3);
        bVar15 = (uVar5 & 0xf0) != 0;
        uVar5 = uVar5 >> ((ulong)bVar15 << 2);
        bVar16 = (uVar5 & 0xc) != 0;
        auStack_380[uVar24] =
             (uVar20 - ((uint)bVar13 << 4 | (uint)bVar14 << 3 | (uint)bVar15 << 2 |
                       (uint)(uVar3 != 0) | (uint)bVar16 << 1)) -
             (uint)((2 << ((ulong)bVar16 << 1) & uVar5) != 0);
        uVar24 = uVar2;
        puVar23 = puVar23 + 0x18;
      } while ((long)uVar2 < (long)uVar19);
    }
    else {
      uVar24 = uVar2 & 0x7ffffffffffffffc;
      if (uVar24 == 0) goto code_r0x026eaf54;
      piVar26 = (int *)(lStack_1a0 + 200);
      puVar23 = auStack_380;
      puVar27 = auStack_380 + 3;
      uVar28 = uVar24;
      do {
        iVar4 = piVar26[-0x30];
        uVar28 = uVar28 - 4;
        iVar32 = piVar26[-0x18];
        iVar33 = piVar26[0x18];
        puVar27[2] = iVar17 * *piVar26;
        puVar27[3] = iVar17 * iVar33;
        *puVar27 = iVar17 * iVar4;
        puVar27[1] = iVar17 * iVar32;
        uVar3 = piVar26[-0x2f];
        auVar29._4_4_ = piVar26[-0x17];
        auVar29._0_4_ = uVar3;
        auVar29._8_4_ = piVar26[1];
        puVar1 = (uint *)(piVar26 + 0x19);
        piVar26 = piVar26 + 0x60;
        auVar29._12_4_ = *puVar1;
        uVar34 = CONCAT14(-(0xffff < auVar29._4_4_),(uint)(-(0xffff < uVar3) & 0x10)) & 0x10ffffffff
        ;
        bVar38 = -(0xffff < auVar29._8_4_) & 0x10;
        bVar41 = -(0xffff < auVar29._12_4_) & 0x10;
        bVar10 = (byte)(uVar34 >> 0x20);
        auVar31._4_4_ = -(uint)bVar10;
        auVar31._0_4_ = -(int)uVar34;
        auVar31._8_4_ = -(uint)bVar38;
        auVar31._12_4_ = -(uint)bVar41;
        auVar30 = NEON_ushl(auVar29,auVar31,4);
        uVar35 = CONCAT14(-((auVar30._4_4_ & 0xff00) != 0),
                          (uint)(-((auVar30._0_4_ & 0xff00) != 0) & 8)) & 0x8ffffffff;
        bVar39 = -((auVar30._8_4_ & 0xff00) != 0) & 8;
        bVar42 = -((auVar30._12_4_ & 0xff00) != 0) & 8;
        bVar11 = (byte)(uVar35 >> 0x20);
        auVar8._4_4_ = -(uint)bVar11;
        auVar8._0_4_ = -(int)uVar35;
        auVar8._8_4_ = -(uint)bVar39;
        auVar8._12_4_ = -(uint)bVar42;
        auVar30 = NEON_ushl(auVar30,auVar8,4);
        uVar36 = CONCAT14(-((auVar30._4_4_ & 0xf0) != 0),(uint)(-((auVar30._0_4_ & 0xf0) != 0) & 4))
                 & 0x4ffffffff;
        bVar40 = -((auVar30._8_4_ & 0xf0) != 0) & 4;
        bVar43 = -((auVar30._12_4_ & 0xf0) != 0) & 4;
        bVar12 = (byte)(uVar36 >> 0x20);
        auVar9._4_4_ = -(uint)bVar12;
        auVar9._0_4_ = -(int)uVar36;
        auVar9._8_4_ = -(uint)bVar40;
        auVar9._12_4_ = -(uint)bVar43;
        auVar31 = NEON_ushl(auVar30,auVar9,4);
        auVar37._0_5_ =
             CONCAT14(-((auVar31._4_4_ & 0xc) != 0),(uint)(-((auVar31._0_4_ & 0xc) != 0) & 2)) &
             0x2ffffffff;
        auVar37._5_3_ = 0;
        auVar37[8] = -((auVar31._8_4_ & 0xc) != 0) & 2;
        auVar37._9_3_ = 0;
        auVar37[0xc] = -((auVar31._12_4_ & 0xc) != 0) & 2;
        auVar37._13_3_ = 0;
        auVar30[8] = 2;
        auVar30._0_8_ = 0x200000002;
        auVar30._9_3_ = 0;
        auVar30[0xc] = 2;
        auVar30._13_3_ = 0;
        auVar30 = NEON_ushl(auVar30,auVar37,4);
        puVar23[2] = (uVar20 - (byte)(bVar38 | ~-(auVar29._8_4_ == 0) & 1U | bVar39 | bVar40 |
                                     auVar37[8])) - (uint)((auVar30._8_4_ & auVar31._8_4_) != 0);
        puVar23[3] = (uVar20 - (byte)(bVar41 | ~-(auVar29._12_4_ == 0) & 1U | bVar42 | bVar43 |
                                     auVar37[0xc])) - (uint)((auVar30._12_4_ & auVar31._12_4_) != 0)
        ;
        *puVar23 = (uVar20 - (byte)((byte)uVar34 | ~-(uVar3 == 0) & 1U | (byte)uVar35 | (byte)uVar36
                                   | (byte)auVar37._0_5_)) -
                   (uint)((auVar30._0_4_ & auVar31._0_4_) != 0);
        puVar23[1] = (uVar20 - (byte)(bVar10 | ~-(auVar29._4_4_ == 0) & 1U | bVar11 | bVar12 |
                                     (byte)(auVar37._0_5_ >> 0x20))) -
                     (uint)((auVar30._4_4_ & auVar31._4_4_) != 0);
        puVar23 = puVar23 + 4;
        puVar27 = puVar27 + 4;
      } while (uVar28 != 0);
      if (uVar2 != uVar24) goto code_r0x026eaf54;
    }
    apuStack_518[0] = auStack_400;
    apuStack_518[1] = auStack_480;
    apuStack_518[2] = auStack_500;
    uStack_267 = 1;
    uStack_260 = 0;
    uStack_264 = 0;
    jpeg_start_decompress(auStack_2c0);
    if (uStack_228 < uStack_248) {
      do {
        if (0 < (int)uStack_288) {
          lVar21 = 0;
          do {
            uVar20 = 0x10 >> (ulong)(auStack_380[lVar21] & 0x1f);
            if (0 < (int)uVar20) {
              uVar3 = auStack_380[lVar21 + 3];
              lVar22 = 0;
              lVar25 = (long)(int)uVar3 *
                       (long)(int)(uStack_228 >> (ulong)(auStack_380[lVar21] & 0x1f));
              do {
                *(long *)(apuStack_518[lVar21] + lVar22 * 8) =
                     *(long *)(param_1 + lVar21 * 8) + lVar25;
                lVar22 = lVar22 + 1;
                lVar25 = lVar25 + (int)uVar3;
              } while (lVar22 < (int)uVar20);
            }
            lVar21 = lVar21 + 1;
          } while (lVar21 < (int)uStack_288);
        }
        jpeg_read_raw_data(auStack_2c0,apuStack_518,0x10);
      } while (uStack_228 < uStack_248);
    }
    jpeg_finish_decompress(auStack_2c0);
  }
  jpeg_destroy_decompress(auStack_2c0);
  uVar18 = 0;
code_r0x026eb0ec:
  if (*(long *)(lVar7 + 0x28) == lStack_48) {
    return;
  }
  __stack_chk_fail(uVar18);
  return;
}


// FAILED to create function at 029d2fe0 typeinfo name for Aska::JpegUtil::FnGrayscaleLineReader
// FAILED to create function at 029d3010 typeinfo name for Aska::JpegUtil::ILineScanner
// FAILED to create function at 029d3030 typeinfo name for Aska::JpegUtil::FnRGBXLineReader
// FAILED to create function at 029d3060 typeinfo name for Aska::JpegUtil::FnCMYKLineReader
// FAILED to create function at 029d3090 typeinfo name for Aska::JpegUtil::FnASKAEngineAllocator
// FAILED to create function at 029d30c0 typeinfo name for Aska::JpegUtil::IAllocator
// FAILED to create function at 02c564e8 Aska::JpegUtil::FnGrayscaleLineReader::vtable
// FAILED to create function at 02c56500 Aska::JpegUtil::ILineScanner::typeinfo
// FAILED to create function at 02c56510 Aska::JpegUtil::FnGrayscaleLineReader::typeinfo
// FAILED to create function at 02c56528 Aska::JpegUtil::FnRGBXLineReader::vtable
// FAILED to create function at 02c56540 Aska::JpegUtil::FnRGBXLineReader::typeinfo
// FAILED to create function at 02c56558 Aska::JpegUtil::FnCMYKLineReader::vtable
// FAILED to create function at 02c56570 Aska::JpegUtil::FnCMYKLineReader::typeinfo
// FAILED to create function at 02c56588 Aska::JpegUtil::FnASKAEngineAllocator::vtable
// FAILED to create function at 02c565a8 Aska::JpegUtil::IAllocator::typeinfo
// FAILED to create function at 02c565c0 Aska::JpegUtil::FnASKAEngineAllocator::typeinfo
