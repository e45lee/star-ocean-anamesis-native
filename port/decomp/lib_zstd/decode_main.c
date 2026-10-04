// port/decomp/lib_zstd/decode_main.c: Ghidra decompiles for the lib_zstd subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:35 UTC: tools/decomp.sh '--into' 'lib_zstd/decode_main' 'Aska::_DecodeMain<false, ?7>::Decode'

// ==== Aska::_DecodeMain<false, 7>::Decode(unsigned char*, unsigned char*, int)
// vaddr 0x1f1b2f4 | ghidra 0x201b2f4 | size 172 | symbol _ZN4Aska11_DecodeMainILb0ELi7EE6DecodeEPhS2_i | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11_DecodeMainILb0ELi7EE6DecodeEPhS2_i
               (undefined8 param_1,undefined8 param_2,int param_3)

{
  long lVar1;
  long lVar2;
  undefined8 uStack_60;
  long lStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  long lStack_40;
  undefined8 uStack_38;
  
  if ((0x10000 < param_3) && (lVar1 = Aska::CreateZSTDStream()(), lVar1 != 0)) {
    lVar2 = Aska::InitializeDecompressStreamZSTD(void**)(lVar1);
    if (lVar2 != 0) {
      lStack_58 = (long)param_3;
      uStack_38 = 0;
      uStack_50 = 0;
      uStack_60 = param_2;
      uStack_48 = param_1;
      lStack_40 = lStack_58;
      while (lVar2 = Aska::DecompressStreamZSTD(void**, Aska::ZSTDOutBuffer*, Aska::ZSTDInBuffer*)(lVar1,&uStack_60,&uStack_48), -1 < lVar2) {
        if (lVar2 == 0) {
          Aska::DeleteZSTDStream(void**)(lVar1);
          return;
        }
        Aska::Thread::Switch()();
      }
    }
    Aska::DeleteZSTDStream(void**)(lVar1);
  }
  Aska::DecompressZSTD(void*, long, void const*, long)(param_2,(long)param_3,param_1,(long)param_3);
  return;
}
