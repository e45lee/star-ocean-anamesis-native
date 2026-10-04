// port/decomp/hash/utf8.c: Ghidra decompiles for the hash subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:07 UTC: tools/decomp.sh '--into' 'hash/utf8' 'Aska::Utf8::'

// ==== Aska::Utf8::GetByteSizeAt_(unsigned char)
// vaddr 0x1f17d24 | ghidra 0x2017d24 | size 76 | symbol _ZN4Aska4Utf814GetByteSizeAt_Eh | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska4Utf814GetByteSizeAt_Eh(uint param_1)

{
  if ((param_1 >> 7 & 1) == 0) {
    return 1;
  }
  if ((param_1 & 0xe0) == 0xc0) {
    return 2;
  }
  if ((param_1 & 0xf0) == 0xe0) {
    return 3;
  }
  return (ulong)((param_1 & 0xf8) == 0xf0) << 2;
}

// ==== Aska::Utf8::ToUcs4(char32_t*, char const*, unsigned long)
// vaddr 0x1f17d70 | ghidra 0x2017d70 | size 232 | symbol _ZN4Aska4Utf86ToUcs4EPDiPKcm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska4Utf86ToUcs4EPDiPKcm(long param_1,byte *param_2,ulong param_3)

{
  byte *pbVar1;
  ulong uVar2;
  uint uVar3;
  
  uVar2 = 0;
  if ((((param_1 != 0) && (param_2 != (byte *)0x0)) && (uVar2 = 0, param_3 != 0)) &&
     (uVar3 = (uint)*param_2, *param_2 != 0)) {
    uVar2 = 0;
    do {
      if (uVar3 >> 7 == 0) {
code_r0x02017d9c:
        param_2 = param_2 + 1;
        *(uint *)(param_1 + uVar2 * 4) = uVar3;
      }
      else if ((uVar3 & 0xe0) == 0xc0) {
        pbVar1 = param_2 + 1;
        param_2 = param_2 + 2;
        *(uint *)(param_1 + uVar2 * 4) = *pbVar1 & 0x3f | (uVar3 & 0x1f) << 6;
      }
      else if ((uVar3 & 0xf0) == 0xe0) {
        *(uint *)(param_1 + uVar2 * 4) =
             (uVar3 & 0xf) << 0xc | (param_2[1] & 0x3f) << 6 | param_2[2] & 0x3f;
        param_2 = param_2 + 3;
      }
      else {
        if ((uVar3 & 0xf8) != 0xf0) goto code_r0x02017d9c;
        *(uint *)(param_1 + uVar2 * 4) =
             (uVar3 & 7) << 0x12 | (param_2[1] & 0x3f) << 0xc | (param_2[2] & 0x3f) << 6 |
             param_2[3] & 0x3f;
        param_2 = param_2 + 4;
      }
      uVar2 = uVar2 + 1;
    } while ((uVar2 < param_3) && (uVar3 = (uint)*param_2, uVar3 != 0));
  }
  return uVar2;
}

// ==== Aska::Utf8::ToUcs2(char16_t*, char const*, unsigned long)
// vaddr 0x1f17e58 | ghidra 0x2017e58 | size 188 | symbol _ZN4Aska4Utf86ToUcs2EPDsPKcm | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN4Aska4Utf86ToUcs2EPDsPKcm(long param_1,byte *param_2,ulong param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  ulong uVar3;
  uint uVar4;
  
  uVar3 = 0;
  if ((((param_1 != 0) && (param_2 != (byte *)0x0)) && (uVar3 = 0, param_3 != 0)) &&
     (uVar4 = (uint)*param_2, *param_2 != 0)) {
    uVar3 = 0;
    do {
      if (uVar4 >> 7 == 0) {
code_r0x02017e84:
        param_2 = param_2 + 1;
        *(short *)(param_1 + uVar3 * 2) = (short)uVar4;
      }
      else if ((uVar4 & 0xe0) == 0xc0) {
        pbVar1 = param_2 + 1;
        param_2 = param_2 + 2;
        *(ushort *)(param_1 + uVar3 * 2) = *pbVar1 & 0x3f | (ushort)((uVar4 & 0x1f) << 6);
      }
      else if ((uVar4 & 0xf0) == 0xe0) {
        pbVar1 = param_2 + 1;
        pbVar2 = param_2 + 2;
        param_2 = param_2 + 3;
        *(ushort *)(param_1 + uVar3 * 2) =
             (ushort)(uVar4 << 0xc) | (*pbVar1 & 0x3f) << 6 | *pbVar2 & 0x3f;
      }
      else {
        if ((uVar4 & 0xf8) != 0xf0) goto code_r0x02017e84;
        *(short *)(param_1 + uVar3 * 2) = (short)uVar4;
        param_2 = param_2 + 4;
      }
      uVar3 = uVar3 + 1;
    } while ((uVar3 < param_3) && (uVar4 = (uint)*param_2, uVar4 != 0));
  }
  return uVar3;
}
