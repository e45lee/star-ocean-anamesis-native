// port/decomp/render/shader_cache.c: Ghidra decompiles for the render subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 14:40 UTC: tools/decomp.sh '--into' 'render/shader_cache' 'AHSLBase::CreateCompressedShaderCache' 'AHSLCacheManagerV2::BuildLinkedDiskCacheL2'

// ==== Aska::AHSLCacheManagerV2::BuildLinkedDiskCacheL2(Aska::ShaderDiskCache const*)
// vaddr 0x20ad2a8 | ghidra 0x21ad2a8 | size 616 | symbol _ZN4Aska18AHSLCacheManagerV222BuildLinkedDiskCacheL2EPKNS_15ShaderDiskCacheE | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska18AHSLCacheManagerV222BuildLinkedDiskCacheL2EPKNS_15ShaderDiskCacheE
              (long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  long lVar6;
  long *plVar7;
  ulong uVar8;
  long lVar9;
  undefined8 uVar10;
  int iVar11;
  byte abStack_160d0 [8];
  undefined8 uStack_160c8;
  long lStack_160c0;
  undefined1 auStack_16060 [45056];
  undefined1 auStack_b060 [45056];
  
  if ((*(byte *)(param_2 + 10) >> 5 & 1) != 0) {
    return 1;
  }
  lVar1 = param_2 + 0xc;
  abStack_160d0[0] = 0;
  uStack_160c8 = 0;
  lStack_160c0 = 0;
  Aska::ShaderKeyUtil::Attach(unsigned char const*)(abStack_160d0,lVar1);
  iVar4 = Aska::ShaderKeyUtil::GetKind()(abStack_160d0);
  iVar5 = Aska::ShaderKeyUtil::GetTarget()(abStack_160d0);
  lVar2 = param_1 + 0x18;
  uVar10 = *(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  param_1 = param_1 + 0x174b0;
  lVar6 = Aska::AHSLBase::UncompressShaderCache(Aska::ShaderDiskCache*, Aska::ShaderDiskCache const*, unsigned char*)(lVar2,auStack_16060,param_2,param_1);
  lVar9 = (ulong)*(ushort *)(lVar6 + 6) + lVar6;
  if (iVar5 == 1) {
    plVar7 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x48,PTR__ZSt7nothrow_02cb9a80);
    if (plVar7 != (long *)0x0) {
      Aska::Shader::Shader()(plVar7);
      *plVar7 = (long)(PTR__ZTVN4Aska11PixelShaderE_02cba750 + 0x10);
    }
    *(long **)(lVar9 + 0x20) = plVar7;
    uVar8 = Aska::RenderDeviceGL::CreateShaderFromMemory(char const*, Aska::PixelShader*, Aska::AHSLShaderConstListKind::E, unsigned char const*, int, Aska::ConstAssign**, unsigned short*, unsigned short*)(uVar10,(ulong)*(ushort *)(lVar9 + 0x1a) + lVar6,plVar7,iVar4 == 2,lVar1,
                            0xffffffff,lVar9 + 0x28,lVar9 + 0x1e,lVar9 + 0x10);
  }
  else {
    iVar11 = 0;
    if (iVar5 != 0) goto code_r0x021ad440;
    plVar7 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x178,PTR__ZSt7nothrow_02cb9a80);
    if (plVar7 != (long *)0x0) {
      Aska::Shader::Shader()(plVar7);
      puVar3 = PTR__ZTVN4Aska12VertexShaderE_02cbfe20;
      plVar7[0x2e] = 0;
      *plVar7 = (long)(puVar3 + 0x10);
    }
    *(long **)(lVar9 + 0x20) = plVar7;
    uVar8 = Aska::RenderDeviceGL::CreateShaderFromMemory(char const*, Aska::VertexShader*, Aska::AHSLShaderConstListKind::E, unsigned char const*, int, Aska::ConstAssign**, unsigned short*, unsigned short*)(uVar10,(ulong)*(ushort *)(lVar9 + 0x1a) + lVar6,plVar7,iVar4 == 2,lVar1,
                            0xffffffff,lVar9 + 0x28,lVar9 + 0x1e,lVar9 + 0x10);
  }
  if ((uVar8 & 1) == 0) {
    iVar11 = 0;
  }
  else {
    iVar11 = 1;
  }
code_r0x021ad440:
  if ((*(byte *)(param_2 + 10) & 3) != 0) {
    Aska::AHSLBase::CreateCompressedShaderCache(Aska::ShaderDiskCache*, void*, unsigned char*)(lVar2,lVar6,param_2,param_1);
  }
  if (iVar11 == 0) {
    lVar9 = Aska::AHSLBase::UncompressShaderCache(Aska::ShaderDiskCache*, Aska::ShaderDiskCache const*, unsigned char*)(lVar2,auStack_b060,param_2,param_1);
    lVar1 = (ulong)*(ushort *)(lVar9 + 6) + lVar9;
    if (*(long **)(lVar1 + 0x20) != (long *)0x0) {
      (**(code **)(**(long **)(lVar1 + 0x20) + 8))();
      *(undefined8 *)(lVar1 + 0x20) = 0;
    }
    if (*(long *)(lVar1 + 0x28) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(lVar1 + 0x28) = 0;
    }
    if ((*(byte *)(param_2 + 10) & 3) != 0) {
      Aska::AHSLBase::CreateCompressedShaderCache(Aska::ShaderDiskCache*, void*, unsigned char*)(lVar2,lVar9,param_2,param_1);
    }
  }
  if (((abStack_160d0[0] & 1) != 0) && (lStack_160c0 != 0)) {
    operator delete[](void*)();
  }
  return iVar11;
}

// ==== Aska::AHSLBase::CreateCompressedShaderCache(Aska::ShaderDiskCache*, void*, unsigned char*)
// vaddr 0x20b2eec | ghidra 0x21b2eec | size 148 | symbol _ZN4Aska8AHSLBase27CreateCompressedShaderCacheEPNS_15ShaderDiskCacheEPvPh | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska8AHSLBase27CreateCompressedShaderCacheEPNS_15ShaderDiskCacheEPvPh
          (long param_1,long param_2,long param_3,undefined8 param_4)

{
  long lVar1;
  short sVar2;
  undefined8 uVar3;
  uint uVar4;
  
  uVar4 = *(int *)(param_1 + 8) - 5;
  if (uVar4 < 7) {
    uVar4 = *(uint *)(&UNK_029c5da0/*"0"*/ + (long)(int)uVar4 * 4);
  }
  else {
    uVar4 = 0;
  }
  lVar1 = (ulong)*(ushort *)(param_2 + 6) + (ulong)uVar4;
  memcpy(param_3,param_2,lVar1);
  uVar3 = Aska::ShaderCompression::CompressLZwordDic(void*, int, void*, unsigned char*)(lVar1 + param_2,(uint)*(ushort *)(param_2 + 4) - (int)lVar1,
                          lVar1 + param_3,param_4);
  if ((int)uVar3 != 0) {
    sVar2 = (short)uVar3;
    uVar3 = 1;
    *(short *)(param_3 + 2) = sVar2 + (short)lVar1;
    *(undefined1 *)(param_3 + 10) = 3;
  }
  return uVar3;
}
