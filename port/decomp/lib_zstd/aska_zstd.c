// port/decomp/lib_zstd/aska_zstd.c: Ghidra decompiles for the lib_zstd subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:06 UTC: tools/decomp.sh '--into' 'lib_zstd/aska_zstd' 'Aska::\w*ZSTD\w*\('

// ==== Aska::CompressZSTD(void*, long, void const*, long)
// vaddr 0x221eaa0 | ghidra 0x231eaa0 | size 8 | symbol _ZN4Aska12CompressZSTDEPvlPKvl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12CompressZSTDEPvlPKvl(void)

{
  (*(code *)PTR_ZSTD_compress_02cae2f0)();
  return;
}

// ==== Aska::DecompressZSTD(void*, long, void const*, long)
// vaddr 0x221eaa8 | ghidra 0x231eaa8 | size 4 | symbol _ZN4Aska14DecompressZSTDEPvlPKvl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14DecompressZSTDEPvlPKvl(void)

{
  (*(code *)PTR_ZSTD_decompress_02ca9b30)();
  return;
}

// ==== Aska::CreateZSTDStream()
// vaddr 0x221eaac | ghidra 0x231eaac | size 4 | symbol _ZN4Aska16CreateZSTDStreamEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16CreateZSTDStreamEv(void)

{
  (*(code *)PTR_ZSTD_createDStream_02caaad8)();
  return;
}

// ==== Aska::DeleteZSTDStream(void**)
// vaddr 0x221eab0 | ghidra 0x231eab0 | size 4 | symbol _ZN4Aska16DeleteZSTDStreamEPPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DeleteZSTDStreamEPPv(void)

{
  (*(code *)PTR_ZSTD_freeDStream_02cabc50)();
  return;
}

// ==== Aska::GetStreamInSizeZSTD()
// vaddr 0x221eab4 | ghidra 0x231eab4 | size 4 | symbol _ZN4Aska19GetStreamInSizeZSTDEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19GetStreamInSizeZSTDEv(void)

{
  (*(code *)PTR_ZSTD_DStreamInSize_02c92318)();
  return;
}

// ==== Aska::GetStreamOutSizeZSTD()
// vaddr 0x221eab8 | ghidra 0x231eab8 | size 4 | symbol _ZN4Aska20GetStreamOutSizeZSTDEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20GetStreamOutSizeZSTDEv(void)

{
  (*(code *)PTR_ZSTD_DStreamOutSize_02ca3ce8)();
  return;
}

// ==== Aska::InitializeDecompressStreamZSTD(void**)
// vaddr 0x221eabc | ghidra 0x231eabc | size 4 | symbol _ZN4Aska30InitializeDecompressStreamZSTDEPPv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska30InitializeDecompressStreamZSTDEPPv(void)

{
  (*(code *)PTR_ZSTD_initDStream_02cab6e0)();
  return;
}

// ==== Aska::DecompressStreamZSTD(void**, Aska::ZSTDOutBuffer*, Aska::ZSTDInBuffer*)
// vaddr 0x221eac0 | ghidra 0x231eac0 | size 4 | symbol _ZN4Aska20DecompressStreamZSTDEPPvPNS_13ZSTDOutBufferEPNS_12ZSTDInBufferE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20DecompressStreamZSTDEPPvPNS_13ZSTDOutBufferEPNS_12ZSTDInBufferE(void)

{
  (*(code *)PTR_ZSTD_decompressStream_02cb30a8)();
  return;
}

// ==== Aska::CompressSizeZSTD(long)
// vaddr 0x221eac4 | ghidra 0x231eac4 | size 4 | symbol _ZN4Aska16CompressSizeZSTDEl | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16CompressSizeZSTDEl(void)

{
  (*(code *)PTR_ZSTD_compressBound_02ca38b0)();
  return;
}

// ==== Aska::IsErrorZSTD(long)
// vaddr 0x221eac8 | ghidra 0x231eac8 | size 24 | symbol _ZN4Aska11IsErrorZSTDEl | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska11IsErrorZSTDEl(void)

{
  int iVar1;
  
  iVar1 = ZSTD_isError();
  return iVar1 != 0;
}
