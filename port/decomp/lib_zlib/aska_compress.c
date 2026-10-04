// port/decomp/lib_zlib/aska_compress.c: Ghidra decompiles for the lib_zlib subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:06 UTC: tools/decomp.sh '--into' 'lib_zlib/aska_compress' ' AskaU?n?[Cc]ompress\w*\('

// ==== AskaCompressZlib(unsigned char*, unsigned long*, unsigned char*, unsigned long)
// vaddr 0x25a6fc8 | ghidra 0x26a6fc8 | size 184 | symbol _Z16AskaCompressZlibPhPmS_m | lib libSOA-3.7.0.so | 2026-10-04
ulong _Z16AskaCompressZlibPhPmS_m
                (undefined8 param_1,ulong *param_2,undefined8 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  undefined8 uStack_90;
  undefined4 uStack_88;
  undefined8 uStack_78;
  undefined4 uStack_70;
  ulong uStack_68;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  
  uStack_70 = (undefined4)*param_2;
  if ((*param_2 & 0xffffffff00000000) == 0) {
    uStack_48 = 0;
    uStack_40 = 0;
    uStack_50 = 0;
    uStack_90 = param_3;
    uStack_88 = param_4;
    uStack_78 = param_1;
    uVar3 = deflateInit2_(&uStack_90,0xffffffff,8,0xf,8,0,&UNK_02a33db0/*"1.2.5"*/,0x70);
    if ((int)uVar3 == 0) {
      uVar2 = deflate(&uStack_90,4);
      if (uVar2 == 1) {
        *param_2 = uStack_68;
        uVar3 = deflateEnd(&uStack_90);
      }
      else {
        deflateEnd(&uStack_90);
        uVar1 = 0xfffffffb;
        if (uVar2 != 0) {
          uVar1 = uVar2;
        }
        uVar3 = (ulong)uVar1;
      }
    }
  }
  else {
    uVar3 = 0xfffffffb;
  }
  return uVar3;
}

// ==== AskaCompress(unsigned char*, unsigned long*, unsigned char*, unsigned long, int)
// vaddr 0x25a7080 | ghidra 0x26a7080 | size 188 | symbol _Z12AskaCompressPhPmS_mi | lib libSOA-3.7.0.so | 2026-10-04
ulong _Z12AskaCompressPhPmS_mi
                (undefined8 param_1,ulong *param_2,undefined8 param_3,undefined4 param_4,
                undefined4 param_5)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  undefined8 uStack_90;
  undefined4 uStack_88;
  undefined8 uStack_78;
  undefined4 uStack_70;
  ulong uStack_68;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  
  uStack_70 = (undefined4)*param_2;
  if ((*param_2 & 0xffffffff00000000) == 0) {
    uStack_48 = 0;
    uStack_40 = 0;
    uStack_50 = 0;
    uStack_90 = param_3;
    uStack_88 = param_4;
    uStack_78 = param_1;
    uVar3 = deflateInit2_(&uStack_90,0xffffffff,8,param_5,8,0,&UNK_02a33db0/*"1.2.5"*/,0x70);
    if ((int)uVar3 == 0) {
      uVar2 = deflate(&uStack_90,4);
      if (uVar2 == 1) {
        *param_2 = uStack_68;
        uVar3 = deflateEnd(&uStack_90);
      }
      else {
        deflateEnd(&uStack_90);
        uVar1 = 0xfffffffb;
        if (uVar2 != 0) {
          uVar1 = uVar2;
        }
        uVar3 = (ulong)uVar1;
      }
    }
  }
  else {
    uVar3 = 0xfffffffb;
  }
  return uVar3;
}

// ==== AskaUncompressZlib(unsigned char*, unsigned long*, unsigned char*, unsigned long)
// vaddr 0x25a713c | ghidra 0x26a713c | size 200 | symbol _Z18AskaUncompressZlibPhPmS_m | lib libSOA-3.7.0.so | 2026-10-04
int _Z18AskaUncompressZlibPhPmS_m
              (undefined8 param_1,ulong *param_2,undefined8 param_3,ulong param_4)

{
  int iVar1;
  undefined8 uStack_90;
  int iStack_88;
  undefined8 uStack_78;
  undefined4 uStack_70;
  ulong uStack_68;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  iStack_88 = (int)param_4;
  if (((param_4 & 0xffffffff00000000) != 0) ||
     (uStack_70 = (undefined4)*param_2, (*param_2 & 0xffffffff00000000) != 0)) {
    return -5;
  }
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_90 = param_3;
  uStack_78 = param_1;
  iVar1 = inflateInit2_(&uStack_90,0xf,&UNK_02a33db0/*"1.2.5"*/,0x70);
  if (iVar1 != 0) {
    return iVar1;
  }
  iVar1 = inflate(&uStack_90,4);
  if (iVar1 == 1) {
    *param_2 = uStack_68;
    iVar1 = inflateEnd(&uStack_90);
    return iVar1;
  }
  inflateEnd(&uStack_90);
  if (iVar1 != 2) {
    if (iVar1 != -5) {
      return iVar1;
    }
    if (iStack_88 != 0) {
      return -5;
    }
  }
  return -3;
}

// ==== AskaUncompress(unsigned char*, unsigned long*, unsigned char*, unsigned long, int)
// vaddr 0x25a7204 | ghidra 0x26a7204 | size 200 | symbol _Z14AskaUncompressPhPmS_mi | lib libSOA-3.7.0.so | 2026-10-04
int _Z14AskaUncompressPhPmS_mi
              (undefined8 param_1,ulong *param_2,undefined8 param_3,ulong param_4,undefined4 param_5
              )

{
  int iVar1;
  undefined8 uStack_90;
  int iStack_88;
  undefined8 uStack_78;
  undefined4 uStack_70;
  ulong uStack_68;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  iStack_88 = (int)param_4;
  if (((param_4 & 0xffffffff00000000) != 0) ||
     (uStack_70 = (undefined4)*param_2, (*param_2 & 0xffffffff00000000) != 0)) {
    return -5;
  }
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_90 = param_3;
  uStack_78 = param_1;
  iVar1 = inflateInit2_(&uStack_90,param_5,&UNK_02a33db0/*"1.2.5"*/,0x70);
  if (iVar1 != 0) {
    return iVar1;
  }
  iVar1 = inflate(&uStack_90,4);
  if (iVar1 == 1) {
    *param_2 = uStack_68;
    iVar1 = inflateEnd(&uStack_90);
    return iVar1;
  }
  inflateEnd(&uStack_90);
  if (iVar1 != 2) {
    if (iVar1 != -5) {
      return iVar1;
    }
    if (iStack_88 != 0) {
      return -5;
    }
  }
  return -3;
}

// ==== AskaCompressGzipStrict(unsigned char*, unsigned long*, unsigned char*, unsigned long)
// vaddr 0x25a72cc | ghidra 0x26a72cc | size 184 | symbol _Z22AskaCompressGzipStrictPhPmS_m | lib libSOA-3.7.0.so | 2026-10-04
ulong _Z22AskaCompressGzipStrictPhPmS_m
                (undefined8 param_1,ulong *param_2,undefined8 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  undefined8 uStack_90;
  undefined4 uStack_88;
  undefined8 uStack_78;
  undefined4 uStack_70;
  ulong uStack_68;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  
  uStack_70 = (undefined4)*param_2;
  if ((*param_2 & 0xffffffff00000000) == 0) {
    uStack_48 = 0;
    uStack_40 = 0;
    uStack_50 = 0;
    uStack_90 = param_3;
    uStack_88 = param_4;
    uStack_78 = param_1;
    uVar3 = deflateInit2_(&uStack_90,0xffffffff,8,0x1f,8,0,&UNK_02a33db0/*"1.2.5"*/,0x70);
    if ((int)uVar3 == 0) {
      uVar2 = deflate(&uStack_90,4);
      if (uVar2 == 1) {
        *param_2 = uStack_68;
        uVar3 = deflateEnd(&uStack_90);
      }
      else {
        deflateEnd(&uStack_90);
        uVar1 = 0xfffffffb;
        if (uVar2 != 0) {
          uVar1 = uVar2;
        }
        uVar3 = (ulong)uVar1;
      }
    }
  }
  else {
    uVar3 = 0xfffffffb;
  }
  return uVar3;
}

// ==== AskaUncompressGzipStrict(unsigned char*, unsigned long*, unsigned char*, unsigned long)
// vaddr 0x25a7384 | ghidra 0x26a7384 | size 200 | symbol _Z24AskaUncompressGzipStrictPhPmS_m | lib libSOA-3.7.0.so | 2026-10-04
int _Z24AskaUncompressGzipStrictPhPmS_m
              (undefined8 param_1,ulong *param_2,undefined8 param_3,ulong param_4)

{
  int iVar1;
  undefined8 uStack_90;
  int iStack_88;
  undefined8 uStack_78;
  undefined4 uStack_70;
  ulong uStack_68;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  iStack_88 = (int)param_4;
  if (((param_4 & 0xffffffff00000000) != 0) ||
     (uStack_70 = (undefined4)*param_2, (*param_2 & 0xffffffff00000000) != 0)) {
    return -5;
  }
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_90 = param_3;
  uStack_78 = param_1;
  iVar1 = inflateInit2_(&uStack_90,0x1f,&UNK_02a33db0/*"1.2.5"*/,0x70);
  if (iVar1 != 0) {
    return iVar1;
  }
  iVar1 = inflate(&uStack_90,4);
  if (iVar1 == 1) {
    *param_2 = uStack_68;
    iVar1 = inflateEnd(&uStack_90);
    return iVar1;
  }
  inflateEnd(&uStack_90);
  if (iVar1 != 2) {
    if (iVar1 != -5) {
      return iVar1;
    }
    if (iStack_88 != 0) {
      return -5;
    }
  }
  return -3;
}

// ==== AskaCompressRawFormat(unsigned char*, unsigned long*, unsigned char*, unsigned long)
// vaddr 0x25a744c | ghidra 0x26a744c | size 184 | symbol _Z21AskaCompressRawFormatPhPmS_m | lib libSOA-3.7.0.so | 2026-10-04
ulong _Z21AskaCompressRawFormatPhPmS_m
                (undefined8 param_1,ulong *param_2,undefined8 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  undefined8 uStack_90;
  undefined4 uStack_88;
  undefined8 uStack_78;
  undefined4 uStack_70;
  ulong uStack_68;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  
  uStack_70 = (undefined4)*param_2;
  if ((*param_2 & 0xffffffff00000000) == 0) {
    uStack_48 = 0;
    uStack_40 = 0;
    uStack_50 = 0;
    uStack_90 = param_3;
    uStack_88 = param_4;
    uStack_78 = param_1;
    uVar3 = deflateInit2_(&uStack_90,0xffffffff,8,0xfffffff1,8,0,&UNK_02a33db0/*"1.2.5"*/,0x70);
    if ((int)uVar3 == 0) {
      uVar2 = deflate(&uStack_90,4);
      if (uVar2 == 1) {
        *param_2 = uStack_68;
        uVar3 = deflateEnd(&uStack_90);
      }
      else {
        deflateEnd(&uStack_90);
        uVar1 = 0xfffffffb;
        if (uVar2 != 0) {
          uVar1 = uVar2;
        }
        uVar3 = (ulong)uVar1;
      }
    }
  }
  else {
    uVar3 = 0xfffffffb;
  }
  return uVar3;
}

// ==== AskaUncompressRawFormat(unsigned char*, unsigned long*, unsigned char*, unsigned long)
// vaddr 0x25a7504 | ghidra 0x26a7504 | size 200 | symbol _Z23AskaUncompressRawFormatPhPmS_m | lib libSOA-3.7.0.so | 2026-10-04
int _Z23AskaUncompressRawFormatPhPmS_m
              (undefined8 param_1,ulong *param_2,undefined8 param_3,ulong param_4)

{
  int iVar1;
  undefined8 uStack_90;
  int iStack_88;
  undefined8 uStack_78;
  undefined4 uStack_70;
  ulong uStack_68;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  iStack_88 = (int)param_4;
  if (((param_4 & 0xffffffff00000000) != 0) ||
     (uStack_70 = (undefined4)*param_2, (*param_2 & 0xffffffff00000000) != 0)) {
    return -5;
  }
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_90 = param_3;
  uStack_78 = param_1;
  iVar1 = inflateInit2_(&uStack_90,0xfffffff1,&UNK_02a33db0/*"1.2.5"*/,0x70);
  if (iVar1 != 0) {
    return iVar1;
  }
  iVar1 = inflate(&uStack_90,4);
  if (iVar1 == 1) {
    *param_2 = uStack_68;
    iVar1 = inflateEnd(&uStack_90);
    return iVar1;
  }
  inflateEnd(&uStack_90);
  if (iVar1 != 2) {
    if (iVar1 != -5) {
      return iVar1;
    }
    if (iStack_88 != 0) {
      return -5;
    }
  }
  return -3;
}

// ==== AskaUncompressAuto(unsigned char*, unsigned long*, unsigned char*, unsigned long)
// vaddr 0x25a75cc | ghidra 0x26a75cc | size 200 | symbol _Z18AskaUncompressAutoPhPmS_m | lib libSOA-3.7.0.so | 2026-10-04
int _Z18AskaUncompressAutoPhPmS_m
              (undefined8 param_1,ulong *param_2,undefined8 param_3,ulong param_4)

{
  int iVar1;
  undefined8 uStack_90;
  int iStack_88;
  undefined8 uStack_78;
  undefined4 uStack_70;
  ulong uStack_68;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  iStack_88 = (int)param_4;
  if (((param_4 & 0xffffffff00000000) != 0) ||
     (uStack_70 = (undefined4)*param_2, (*param_2 & 0xffffffff00000000) != 0)) {
    return -5;
  }
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_90 = param_3;
  uStack_78 = param_1;
  iVar1 = inflateInit2_(&uStack_90,0x2f,&UNK_02a33db0/*"1.2.5"*/,0x70);
  if (iVar1 != 0) {
    return iVar1;
  }
  iVar1 = inflate(&uStack_90,4);
  if (iVar1 == 1) {
    *param_2 = uStack_68;
    iVar1 = inflateEnd(&uStack_90);
    return iVar1;
  }
  inflateEnd(&uStack_90);
  if (iVar1 != 2) {
    if (iVar1 != -5) {
      return iVar1;
    }
    if (iStack_88 != 0) {
      return -5;
    }
  }
  return -3;
}

// ==== AskaCompressGzip(unsigned char*, unsigned long*, unsigned char*, unsigned long)
// vaddr 0x25a7694 | ghidra 0x26a7694 | size 184 | symbol _Z16AskaCompressGzipPhPmS_m | lib libSOA-3.7.0.so | 2026-10-04
ulong _Z16AskaCompressGzipPhPmS_m
                (undefined8 param_1,ulong *param_2,undefined8 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  undefined8 uStack_90;
  undefined4 uStack_88;
  undefined8 uStack_78;
  undefined4 uStack_70;
  ulong uStack_68;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  
  uStack_70 = (undefined4)*param_2;
  if ((*param_2 & 0xffffffff00000000) == 0) {
    uStack_48 = 0;
    uStack_40 = 0;
    uStack_50 = 0;
    uStack_90 = param_3;
    uStack_88 = param_4;
    uStack_78 = param_1;
    uVar3 = deflateInit2_(&uStack_90,0xffffffff,8,0xfffffff1,8,0,&UNK_02a33db0/*"1.2.5"*/,0x70);
    if ((int)uVar3 == 0) {
      uVar2 = deflate(&uStack_90,4);
      if (uVar2 == 1) {
        *param_2 = uStack_68;
        uVar3 = deflateEnd(&uStack_90);
      }
      else {
        deflateEnd(&uStack_90);
        uVar1 = 0xfffffffb;
        if (uVar2 != 0) {
          uVar1 = uVar2;
        }
        uVar3 = (ulong)uVar1;
      }
    }
  }
  else {
    uVar3 = 0xfffffffb;
  }
  return uVar3;
}

// ==== AskaUncompressGzip(unsigned char*, unsigned long*, unsigned char*, unsigned long)
// vaddr 0x25a774c | ghidra 0x26a774c | size 200 | symbol _Z18AskaUncompressGzipPhPmS_m | lib libSOA-3.7.0.so | 2026-10-04
int _Z18AskaUncompressGzipPhPmS_m
              (undefined8 param_1,ulong *param_2,undefined8 param_3,ulong param_4)

{
  int iVar1;
  undefined8 uStack_90;
  int iStack_88;
  undefined8 uStack_78;
  undefined4 uStack_70;
  ulong uStack_68;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  iStack_88 = (int)param_4;
  if (((param_4 & 0xffffffff00000000) != 0) ||
     (uStack_70 = (undefined4)*param_2, (*param_2 & 0xffffffff00000000) != 0)) {
    return -5;
  }
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_90 = param_3;
  uStack_78 = param_1;
  iVar1 = inflateInit2_(&uStack_90,0xfffffff1,&UNK_02a33db0/*"1.2.5"*/,0x70);
  if (iVar1 != 0) {
    return iVar1;
  }
  iVar1 = inflate(&uStack_90,4);
  if (iVar1 == 1) {
    *param_2 = uStack_68;
    iVar1 = inflateEnd(&uStack_90);
    return iVar1;
  }
  inflateEnd(&uStack_90);
  if (iVar1 != 2) {
    if (iVar1 != -5) {
      return iVar1;
    }
    if (iStack_88 != 0) {
      return -5;
    }
  }
  return -3;
}
