// port/decomp/particles/render_manager.c: Ghidra decompiles for the particles subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 13:23 UTC: tools/decomp.sh '--into' 'particles/render_manager' 'Aska::ParticleRenderManager::'

// ==== Aska::ParticleRenderManager::ParticleRenderManager()
// vaddr 0x2369bf0 | ghidra 0x2469bf0 | size 544 | symbol _ZN4Aska21ParticleRenderManagerC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManagerC2Ev(long *param_1)

{
  Aska::IParticleRenderManager::IParticleRenderManager()();
  *param_1 = (long)(PTR__ZTVN4Aska21ParticleRenderManagerE_02cbe648 + 0x10);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2813);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2818);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x281d);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2822);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2827);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x282c);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2831);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2836);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x283b);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2840);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2845);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x284a);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x284f);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2854);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2859);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x285e);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2863);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2868);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x286d);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2872);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2877);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x287c);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2881);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2886);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x288b);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2890);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x2895);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x289a);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x289f);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x28a4);
  Aska::PrimitiveBuffer::PrimitiveBuffer()(param_1 + 0x28a9);
  *(undefined4 *)(param_1 + 0x2812) = 0;
  return;
}

// ==== Aska::ParticleRenderManager::~ParticleRenderManager()
// vaddr 0x2369e10 | ghidra 0x2469e10 | size 552 | symbol _ZN4Aska21ParticleRenderManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManagerD1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska21ParticleRenderManagerE_02cbe648 + 0x10);
  Aska::ParticleRenderManager::Release()();
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x28a9);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x28a4);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x289f);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x289a);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2895);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2890);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x288b);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2886);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2881);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x287c);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2877);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2872);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x286d);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2868);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2863);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x285e);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2859);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2854);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x284f);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x284a);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2845);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2840);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x283b);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2836);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2831);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x282c);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2827);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2822);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x281d);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2818);
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(param_1 + 0x2813);
  (*(code *)PTR__ZN4Aska22IParticleRenderManagerD2Ev_02ca1780)(param_1);
  return;
}

// ==== Aska::ParticleRenderManager::~ParticleRenderManager()
// vaddr 0x236a038 | ghidra 0x246a038 | size 24 | symbol _ZN4Aska21ParticleRenderManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManagerD0Ev(undefined8 param_1)

{
  Aska::ParticleRenderManager::~ParticleRenderManager()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::ParticleRenderManager::ReleaseBuffers()
// vaddr 0x236a050 | ghidra 0x246a050 | size 4 | symbol _ZN4Aska21ParticleRenderManager14ReleaseBuffersEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager14ReleaseBuffersEv(void)

{
  return;
}

// ==== Aska::ParticleRenderManager::Release()
// vaddr 0x236a054 | ghidra 0x246a054 | size 1144 | symbol _ZN4Aska21ParticleRenderManager7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager7ReleaseEv(long *param_1)

{
  uint *puVar1;
  uint uVar2;
  long *plVar3;
  long lVar4;
  
  if (param_1[0x2814] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2813);
  }
  if (param_1[0x2819] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2818);
  }
  if (param_1[0x281e] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x281d);
  }
  if (param_1[0x2823] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2822);
  }
  if (param_1[0x2828] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2827);
  }
  if (param_1[0x282d] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x282c);
  }
  if (param_1[0x2832] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2831);
  }
  if (param_1[0x2837] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2836);
  }
  if (param_1[0x283c] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x283b);
  }
  if (param_1[0x2841] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2840);
  }
  if (param_1[0x2846] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2845);
  }
  if (param_1[0x284b] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x284a);
  }
  if (param_1[0x2850] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x284f);
  }
  if (param_1[0x2855] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2854);
  }
  if (param_1[0x285a] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2859);
  }
  if (param_1[0x285f] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x285e);
  }
  if (param_1[0x2864] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2863);
  }
  if (param_1[0x2869] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2868);
  }
  if (param_1[0x286e] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x286d);
  }
  if (param_1[0x2873] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2872);
  }
  if (param_1[0x2878] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2877);
  }
  if (param_1[0x287d] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x287c);
  }
  if (param_1[0x2882] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2881);
  }
  if (param_1[0x2887] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2886);
  }
  if (param_1[0x288c] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x288b);
  }
  if (param_1[0x2891] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2890);
  }
  if (param_1[0x2896] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x2895);
  }
  if (param_1[0x289b] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x289a);
  }
  if (param_1[0x28a0] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x289f);
  }
  if (param_1[0x28a5] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x28a4);
  }
  if (param_1[0x28aa] != 0) {
    Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 0x28a9);
  }
  lVar4 = 0;
  plVar3 = param_1 + 1;
  *(undefined4 *)(param_1 + 0x2812) = 0;
  do {
    puVar1 = (uint *)((long)param_1 + (long)((int)(uint)lVar4 >> 5) * 4 + 0x14008);
    uVar2 = 1 << (ulong)((uint)lVar4 & 0x1f);
    if ((*puVar1 & uVar2) != 0) {
      Aska::PrimitiveBuffer::ReleaseBuffer()(plVar3);
      *puVar1 = *puVar1 & (uVar2 ^ 0xffffffff);
    }
    lVar4 = lVar4 + 1;
    plVar3 = plVar3 + 10;
  } while (lVar4 != 0x400);
                    /* WARNING: Could not recover jumptable at 0x0246a4c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x30))(param_1);
  return;
}

// ==== Aska::ParticleRenderManager::Init()
// vaddr 0x236a4cc | ghidra 0x246a4cc | size 8 | symbol _ZN4Aska21ParticleRenderManager4InitEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska21ParticleRenderManager4InitEv(void)

{
  return 1;
}

// ==== Aska::ParticleRenderManager::PreAllocateBuffers()
// vaddr 0x236a4d4 | ghidra 0x246a4d4 | size 292 | symbol _ZN4Aska21ParticleRenderManager18PreAllocateBuffersEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager18PreAllocateBuffersEv(long param_1)

{
  int iVar1;
  long *plVar2;
  undefined2 *puVar3;
  uint uVar4;
  uint uVar5;
  ulong uVar6;
  uint uVar7;
  long lVar8;
  int iVar9;
  undefined1 *puVar10;
  long lVar11;
  ulong uVar12;
  long lVar13;
  undefined1 auStack_10060 [65536];
  
  uVar12 = 2;
  lVar13 = 4;
  do {
    lVar8 = param_1 + uVar12 * 0x28;
    plVar2 = (long *)(lVar8 + 82000);
    if (*plVar2 == 0) {
      uVar4 = (int)uVar12 * 2 - 2;
      if (uVar4 < 0x8001) {
        uVar7 = 0;
        iVar9 = 0;
        uVar5 = 0;
        puVar10 = auStack_10060;
        if (uVar4 != 0) {
          uVar5 = 0x8000 / uVar4;
          puVar10 = auStack_10060;
        }
        do {
          lVar11 = 0;
          iVar1 = iVar9;
          do {
            puVar3 = (undefined2 *)(puVar10 + lVar11);
            lVar11 = lVar11 + 4;
            *puVar3 = (short)iVar1;
            iVar1 = iVar1 + 1;
            puVar3[1] = (short)iVar1;
          } while (lVar13 != lVar11);
          uVar7 = uVar7 + 1;
          iVar9 = iVar9 + (int)uVar12;
          puVar10 = puVar10 + lVar13;
        } while (uVar7 != uVar5);
      }
      uVar6 = Aska::PrimitiveBuffer::CreateIndexBuffer(int, void const*, unsigned int, bool)(lVar8 + 0x14048,0x8000,auStack_10060,4,0);
      if ((uVar6 & 1) == 0) {
        Aska::IndexBuffer::Release()(*plVar2);
      }
      else {
        *(int *)(param_1 + 0x14090) = *(int *)(param_1 + 0x14090) + 0x8000;
      }
    }
    Aska::ParticleRenderManager::GetPolyStripIndexBuffer(int)(param_1,uVar12 & 0xffffffff);
    uVar12 = uVar12 + 1;
    lVar13 = lVar13 + 4;
  } while (uVar12 != 0x10);
  return;
}

// ==== Aska::ParticleRenderManager::GetLineIndexBuffer(int)
// vaddr 0x236a5f8 | ghidra 0x246a5f8 | size 472 | symbol _ZN4Aska21ParticleRenderManager18GetLineIndexBufferEi | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long _ZN4Aska21ParticleRenderManager18GetLineIndexBufferEi(long param_1,int param_2)

{
  long *plVar1;
  undefined2 *puVar2;
  uint uVar3;
  int iVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  short sVar9;
  short sVar10;
  short sVar11;
  short sVar12;
  long lVar13;
  long lVar14;
  short *psVar15;
  int iVar16;
  long lVar17;
  int iVar18;
  undefined2 *puVar19;
  short *psVar20;
  ulong uVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  short sVar31;
  short sVar32;
  short sVar33;
  short sVar34;
  short sVar35;
  short sVar36;
  short sVar37;
  short sVar38;
  undefined2 auStack_10020 [16];
  short asStack_10000 [32752];
  
  lVar17 = param_1 + (long)(int)(param_2 - 2U) * 0x28;
  plVar1 = (long *)(lVar17 + 0x140a0);
  lVar13 = *plVar1;
  if (lVar13 == 0) {
    iVar16 = param_2 * 2 + -2;
    iVar4 = 0;
    if (iVar16 != 0) {
      iVar4 = 0x8000 / iVar16;
    }
    if ((0 < iVar4) && (1 < param_2)) {
      uVar21 = (ulong)(param_2 - 2U);
      uVar3 = param_2 + 0xfU & 0xf;
      lVar13 = (uVar21 + 1) - (ulong)uVar3;
      iVar16 = 0;
      iVar18 = 0;
      psVar20 = asStack_10000;
      puVar19 = auStack_10020;
      do {
        puVar2 = puVar19 + uVar21 * 2 + 2;
        if ((uVar21 + 1 < 0x10) || (lVar13 == 0)) {
          iVar22 = 0;
          iVar23 = iVar18;
code_r0x0246a74c:
          iVar22 = (param_2 + -1) - iVar22;
          do {
            *puVar19 = (short)iVar23;
            iVar23 = iVar23 + 1;
            iVar22 = iVar22 + -1;
            puVar19[1] = (short)iVar23;
            puVar19 = puVar19 + 2;
          } while (iVar22 != 0);
        }
        else {
          sVar38 = (short)iVar18;
          iVar22 = (int)lVar13;
          puVar19 = puVar19 + lVar13 * 2;
          iVar23 = iVar18 + (int)_UNK_0294ee30;
          iVar24 = iVar18 + (int)((ulong)_UNK_0294ee30 >> 0x20);
          iVar25 = iVar18 + (int)_UNK_0294ee38;
          iVar26 = iVar18 + (int)((ulong)_UNK_0294ee38 >> 0x20);
          iVar27 = iVar18 + (int)_UNK_0294ee20;
          iVar28 = iVar18 + (int)((ulong)_UNK_0294ee20 >> 0x20);
          iVar29 = iVar18 + (int)_UNK_0294ee28;
          iVar30 = iVar18 + (int)((ulong)_UNK_0294ee28 >> 0x20);
          sVar31 = sVar38 + (short)_UNK_029d9e30;
          sVar32 = sVar38 + (short)((ulong)_UNK_029d9e30 >> 0x10);
          sVar33 = sVar38 + (short)((ulong)_UNK_029d9e30 >> 0x20);
          sVar34 = sVar38 + (short)((ulong)_UNK_029d9e30 >> 0x30);
          sVar35 = sVar38 + (short)_UNK_029d9e38;
          sVar36 = sVar38 + (short)((ulong)_UNK_029d9e38 >> 0x10);
          sVar37 = sVar38 + (short)((ulong)_UNK_029d9e38 >> 0x20);
          sVar38 = sVar38 + (short)((ulong)_UNK_029d9e38 >> 0x30);
          lVar14 = lVar13;
          psVar15 = psVar20;
          do {
            sVar5 = (short)iVar27;
            sVar6 = (short)iVar28;
            sVar7 = (short)iVar29;
            sVar8 = (short)iVar30;
            sVar9 = (short)iVar23;
            sVar10 = (short)iVar24;
            sVar11 = (short)iVar25;
            sVar12 = (short)iVar26;
            iVar27 = iVar27 + 0x10;
            iVar28 = iVar28 + 0x10;
            iVar29 = iVar29 + 0x10;
            iVar30 = iVar30 + 0x10;
            iVar23 = iVar23 + 0x10;
            iVar24 = iVar24 + 0x10;
            iVar25 = iVar25 + 0x10;
            iVar26 = iVar26 + 0x10;
            lVar14 = lVar14 + -0x10;
            psVar15[-0x10] = sVar31;
            psVar15[-0xf] = sVar5 + 1;
            psVar15[-0xe] = sVar32;
            psVar15[-0xd] = sVar6 + 1;
            psVar15[-0xc] = sVar33;
            psVar15[-0xb] = sVar7 + 1;
            psVar15[-10] = sVar34;
            psVar15[-9] = sVar8 + 1;
            psVar15[-8] = sVar35;
            psVar15[-7] = sVar9 + 1;
            psVar15[-6] = sVar36;
            psVar15[-5] = sVar10 + 1;
            psVar15[-4] = sVar37;
            psVar15[-3] = sVar11 + 1;
            psVar15[-2] = sVar38;
            psVar15[-1] = sVar12 + 1;
            *psVar15 = sVar31 + 8;
            psVar15[1] = sVar5 + 9;
            psVar15[2] = sVar32 + 8;
            psVar15[3] = sVar6 + 9;
            psVar15[4] = sVar33 + 8;
            psVar15[5] = sVar7 + 9;
            psVar15[6] = sVar34 + 8;
            psVar15[7] = sVar8 + 9;
            psVar15[8] = sVar35 + 8;
            psVar15[9] = sVar9 + 9;
            psVar15[10] = sVar36 + 8;
            psVar15[0xb] = sVar10 + 9;
            psVar15[0xc] = sVar37 + 8;
            psVar15[0xd] = sVar11 + 9;
            psVar15[0xe] = sVar38 + 8;
            psVar15[0xf] = sVar12 + 9;
            sVar31 = sVar31 + 0x10;
            sVar32 = sVar32 + 0x10;
            sVar33 = sVar33 + 0x10;
            sVar34 = sVar34 + 0x10;
            sVar35 = sVar35 + 0x10;
            sVar36 = sVar36 + 0x10;
            sVar37 = sVar37 + 0x10;
            sVar38 = sVar38 + 0x10;
            psVar15 = psVar15 + 0x20;
          } while (lVar14 != 0);
          iVar23 = iVar18 + iVar22;
          if (uVar3 != 0) goto code_r0x0246a74c;
        }
        iVar16 = iVar16 + 1;
        iVar18 = iVar18 + param_2;
        psVar20 = psVar20 + uVar21 * 2 + 2;
        puVar19 = puVar2;
      } while (iVar16 != iVar4);
    }
    uVar21 = Aska::PrimitiveBuffer::CreateIndexBuffer(int, void const*, unsigned int, bool)(lVar17 + 0x14098,0x8000,auStack_10020,4,0);
    if ((uVar21 & 1) == 0) {
      Aska::IndexBuffer::Release()(*plVar1);
      lVar13 = 0;
    }
    else {
      *(int *)(param_1 + 0x14090) = *(int *)(param_1 + 0x14090) + 0x8000;
      lVar13 = *plVar1;
    }
  }
  return lVar13;
}

// ==== Aska::ParticleRenderManager::GetPolyStripIndexBuffer(int)
// vaddr 0x236a7d0 | ghidra 0x246a7d0 | size 472 | symbol _ZN4Aska21ParticleRenderManager23GetPolyStripIndexBufferEi | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long _ZN4Aska21ParticleRenderManager23GetPolyStripIndexBufferEi(long param_1,int param_2)

{
  uint uVar1;
  long *plVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  short sVar9;
  short sVar10;
  short sVar11;
  long lVar12;
  ulong uVar13;
  short *psVar14;
  short *psVar15;
  ulong uVar16;
  long lVar17;
  int iVar18;
  int iVar19;
  short *psVar20;
  ulong uVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  short sVar26;
  short sVar27;
  short sVar28;
  short sVar29;
  short asStack_10020 [32768];
  
  psVar15 = asStack_10020;
  psVar20 = asStack_10020;
  lVar17 = param_1 + (long)param_2 * 0x28;
  plVar2 = (long *)(lVar17 + 0x142a8);
  lVar12 = *plVar2;
  if (lVar12 == 0) {
    uVar4 = param_2 * 2;
    iVar5 = 0;
    if (uVar4 + 2 != 0) {
      iVar5 = 0x8000 / (int)(uVar4 + 2);
    }
    if (0 < iVar5) {
      sVar11 = (short)uVar4 + -1;
      iVar18 = 0;
      iVar19 = 0;
      if (param_2 < 1) {
        do {
          psVar15 = psVar20;
          if (iVar19 != 0) {
            psVar15 = psVar20 + 1;
            *psVar20 = (short)iVar18;
          }
          iVar19 = iVar19 + 1;
          psVar20 = psVar15 + 1;
          *psVar15 = sVar11 + (short)iVar18;
          iVar18 = iVar18 + uVar4;
        } while (iVar5 != iVar19);
      }
      else {
        uVar3 = uVar4;
        if ((int)uVar4 < 2) {
          uVar3 = 1;
        }
        uVar13 = (ulong)(uVar3 - 1) + 1;
        uVar21 = uVar13 - (uVar3 & 0xf);
        do {
          sVar6 = (short)iVar19 * (short)uVar4;
          psVar20 = psVar15;
          if (iVar19 != 0) {
            psVar20 = psVar15 + 1;
            *psVar15 = sVar6;
          }
          if ((uVar13 < 0x10) || (uVar21 == 0)) {
            uVar16 = 0;
code_r0x0246a8fc:
            do {
              psVar15 = psVar20;
              sVar7 = (short)uVar16;
              uVar1 = (int)uVar16 + 1;
              uVar16 = (ulong)uVar1;
              psVar14 = psVar15 + 1;
              *psVar15 = (short)iVar18 + sVar7;
              psVar20 = psVar14;
            } while ((int)uVar1 < (int)uVar4);
          }
          else {
            psVar14 = psVar20 + uVar21;
            psVar15 = psVar20 + 8;
            uVar16 = uVar21;
            uVar22 = _UNK_0294ee20;
            uVar23 = _UNK_0294ee28;
            uVar24 = _UNK_0294ee30;
            uVar25 = _UNK_0294ee38;
            do {
              sVar26 = (short)uVar22 + sVar6;
              sVar27 = (short)((ulong)uVar22 >> 0x20) + sVar6;
              sVar7 = (short)uVar23 + sVar6;
              sVar8 = (short)((ulong)uVar23 >> 0x20) + sVar6;
              sVar28 = (short)uVar24 + sVar6;
              sVar29 = (short)((ulong)uVar24 >> 0x20) + sVar6;
              sVar9 = (short)uVar25 + sVar6;
              sVar10 = (short)((ulong)uVar25 >> 0x20) + sVar6;
              uVar22 = CONCAT44((int)((ulong)uVar22 >> 0x20) + 0x10,(int)uVar22 + 0x10);
              uVar23 = CONCAT44((int)((ulong)uVar23 >> 0x20) + 0x10,(int)uVar23 + 0x10);
              uVar24 = CONCAT44((int)((ulong)uVar24 >> 0x20) + 0x10,(int)uVar24 + 0x10);
              uVar25 = CONCAT44((int)((ulong)uVar25 >> 0x20) + 0x10,(int)uVar25 + 0x10);
              uVar16 = uVar16 - 0x10;
              *(ulong *)(psVar15 + -4) = CONCAT26(sVar10,CONCAT24(sVar9,CONCAT22(sVar29,sVar28)));
              *(ulong *)(psVar15 + -8) = CONCAT26(sVar8,CONCAT24(sVar7,CONCAT22(sVar27,sVar26)));
              *(ulong *)(psVar15 + 4) =
                   CONCAT26(sVar10 + 8,CONCAT24(sVar9 + 8,CONCAT22(sVar29 + 8,sVar28 + 8)));
              *(ulong *)psVar15 =
                   CONCAT26(sVar8 + 8,CONCAT24(sVar7 + 8,CONCAT22(sVar27 + 8,sVar26 + 8)));
              psVar15 = psVar15 + 0x10;
            } while (uVar16 != 0);
            if ((uVar3 & 0xf) != 0) {
              uVar16 = uVar21 & 0xffffffff;
              psVar20 = psVar14;
              goto code_r0x0246a8fc;
            }
            psVar15 = psVar20 + (uVar21 - 1);
          }
          iVar19 = iVar19 + 1;
          psVar15 = psVar15 + 2;
          iVar18 = iVar18 + uVar4;
          *psVar14 = sVar11 + sVar6;
        } while (iVar19 != iVar5);
      }
    }
    uVar13 = Aska::PrimitiveBuffer::CreateIndexBuffer(int, void const*, unsigned int, bool)(lVar17 + 0x142a0,0x8000,asStack_10020,4,0);
    if ((uVar13 & 1) == 0) {
      Aska::IndexBuffer::Release()(*plVar2);
      lVar12 = 0;
    }
    else {
      *(int *)(param_1 + 0x14090) = *(int *)(param_1 + 0x14090) + 0x8000;
      lVar12 = *plVar2;
    }
  }
  return lVar12;
}

// ==== Aska::ParticleRenderManager::AllocBuffer(unsigned char, int, int)
// vaddr 0x236a9a8 | ghidra 0x246a9a8 | size 588 | symbol _ZN4Aska21ParticleRenderManager11AllocBufferEhii | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN4Aska21ParticleRenderManager11AllocBufferEhii
               (long *param_1,undefined1 param_2,int param_3,int param_4)

{
  long *plVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  ushort uVar5;
  ulong uVar6;
  int iVar7;
  undefined2 *puVar8;
  undefined2 *puVar9;
  uint *puVar10;
  int iVar11;
  uint uVar12;
  undefined2 uVar13;
  uint uVar14;
  uint uVar15;
  undefined2 auStack_10030 [32768];
  
  puVar8 = auStack_10030;
  switch(param_2) {
  case 2:
    param_3 = param_3 << 1;
    break;
  case 3:
  case 5:
  case 6:
    plVar1 = param_1 + 0x28aa;
    if (*plVar1 != 0) {
code_r0x0246a9fc:
      param_3 = param_3 * param_4 * 4;
      break;
    }
    iVar7 = 0;
    do {
      if (iVar7 == 0) {
        uVar13 = 0;
        iVar11 = 0;
        puVar9 = puVar8;
      }
      else {
        uVar13 = (undefined2)iVar7;
        *puVar8 = uVar13;
        puVar9 = puVar8 + 1;
        iVar11 = iVar7;
      }
      *puVar9 = uVar13;
      uVar5 = (ushort)iVar11;
      iVar7 = iVar7 + 4;
      puVar9[1] = uVar5 | 1;
      puVar8 = puVar9 + 5;
      puVar9[2] = uVar5 | 2;
      puVar9[3] = uVar5 | 3;
      puVar9[4] = uVar5 | 3;
    } while (iVar7 != 0x5554);
    uVar6 = Aska::PrimitiveBuffer::CreateIndexBuffer(int, void const*, unsigned int, bool)(param_1 + 0x28a9,0x8000,auStack_10030,4,0);
    if ((uVar6 & 1) == 0) {
      Aska::IndexBuffer::Release()(*plVar1);
    }
    else {
      *(int *)(param_1 + 0x2812) = (int)param_1[0x2812] + 0x8000;
      if (*plVar1 != 0) goto code_r0x0246a9fc;
    }
    goto code_r0x0246abd8;
  case 4:
    param_3 = param_3 * param_4 * 2;
  }
  puVar2 = (uint *)(param_1 + 0x2811);
  uVar3 = *puVar2;
  uVar14 = uVar3 - 1;
  do {
    if (uVar14 == 0x3ff) {
      uVar14 = 0;
      goto code_r0x0246ab20;
    }
    uVar15 = uVar14 + 1;
    puVar10 = (uint *)((long)param_1 + (long)((int)uVar15 >> 5) * 4 + 0x14008);
    uVar4 = *puVar10;
    uVar12 = 1 << (ulong)(uVar15 & 0x1f);
    *puVar2 = uVar14 + 2;
    uVar14 = uVar15;
  } while ((uVar4 & uVar12) != 0);
  goto code_r0x0246ab58;
  while( true ) {
    puVar10 = (uint *)((long)param_1 + (long)((int)uVar15 >> 5) * 4 + 0x14008);
    uVar12 = 1 << (ulong)(uVar15 & 0x1f);
    uVar14 = uVar15 + 1;
    if ((*puVar10 & uVar12) == 0) break;
code_r0x0246ab20:
    uVar15 = uVar14;
    *puVar2 = uVar15;
    if (uVar3 == uVar15) goto code_r0x0246abd8;
  }
  *puVar2 = uVar15 + 1;
code_r0x0246ab58:
  *puVar10 = *puVar10 | uVar12;
  if (uVar15 != 0xffffffff) {
    *(undefined4 *)(param_1 + (long)(int)uVar15 * 10 + 6) = 0;
    *(int *)((long)param_1 + (long)(int)uVar15 * 0x50 + 0x34) = param_3;
    param_1[(long)(int)uVar15 * 10 + 9] = 0;
    *(undefined4 *)((long)param_1 + (long)(int)uVar15 * 0x50 + 0x3c) = 0;
    *(undefined4 *)(param_1 + (long)(int)uVar15 * 10 + 8) = 0;
    *(undefined4 *)(param_1 + (long)(int)uVar15 * 10 + 7) = 0x60;
    *(undefined1 *)(param_1 + (long)(int)uVar15 * 10 + 10) = 0;
    uVar6 = Aska::PrimitiveBuffer::CreateVertexBuffer(int, unsigned long, int, void const*, unsigned int, bool)(param_1 + (long)(int)uVar15 * 10 + 1,param_3,0x2002201204,0x60,0,1,1);
    if ((uVar6 & 1) == 0) {
      (**(code **)(*param_1 + 0x40))(param_1,uVar15);
code_r0x0246abd8:
      uVar15 = 0xffffffff;
    }
  }
  return uVar15;
}

// ==== Aska::ParticleRenderManager::GetSpriteIndexBuffer()
// vaddr 0x236abf4 | ghidra 0x246abf4 | size 220 | symbol _ZN4Aska21ParticleRenderManager20GetSpriteIndexBufferEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska21ParticleRenderManager20GetSpriteIndexBufferEv(long param_1)

{
  long *plVar1;
  ushort uVar2;
  long lVar3;
  ulong uVar4;
  int iVar5;
  ushort *puVar6;
  ushort *puVar7;
  int iVar8;
  ushort auStack_10020 [32768];
  
  puVar6 = auStack_10020;
  plVar1 = (long *)(param_1 + 0x14550);
  lVar3 = *plVar1;
  if (lVar3 == 0) {
    iVar5 = 0;
    do {
      if (iVar5 == 0) {
        iVar8 = 0;
        puVar7 = puVar6;
      }
      else {
        *puVar6 = (ushort)iVar5;
        puVar7 = puVar6 + 1;
        iVar8 = iVar5;
      }
      uVar2 = (ushort)iVar8;
      *puVar7 = uVar2;
      iVar5 = iVar5 + 4;
      puVar7[1] = uVar2 | 1;
      puVar6 = puVar7 + 5;
      puVar7[2] = uVar2 | 2;
      puVar7[3] = uVar2 | 3;
      puVar7[4] = uVar2 | 3;
    } while (iVar5 != 0x5554);
    uVar4 = Aska::PrimitiveBuffer::CreateIndexBuffer(int, void const*, unsigned int, bool)(param_1 + 0x14548,0x8000,auStack_10020,4,0);
    if ((uVar4 & 1) == 0) {
      Aska::IndexBuffer::Release()(*plVar1);
      lVar3 = 0;
    }
    else {
      *(int *)(param_1 + 0x14090) = *(int *)(param_1 + 0x14090) + 0x8000;
      lVar3 = *plVar1;
    }
  }
  return lVar3;
}

// ==== Aska::ParticleRenderManager::DeleteBuffer(int)
// vaddr 0x236acd0 | ghidra 0x246acd0 | size 76 | symbol _ZN4Aska21ParticleRenderManager12DeleteBufferEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager12DeleteBufferEi(long param_1,uint param_2)

{
  uint *puVar1;
  
  Aska::PrimitiveBuffer::ReleaseBuffer()(param_1 + 8 + (long)(int)param_2 * 0x50);
  puVar1 = (uint *)(param_1 + 8 + (long)((int)param_2 >> 5) * 4 + 0x14000);
  *puVar1 = *puVar1 & (1 << (ulong)(param_2 & 0x1f) ^ 0xffffffffU);
  return;
}

// ==== Aska::ParticleRenderManager::LockBuffer(int, unsigned char, int, int)
// vaddr 0x236ad1c | ghidra 0x246ad1c | size 100 | symbol _ZN4Aska21ParticleRenderManager10LockBufferEihii | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska21ParticleRenderManager10LockBufferEihii(long param_1,int param_2)

{
  undefined8 uVar1;
  byte *pbVar2;
  
  pbVar2 = (byte *)(param_1 + (long)param_2 * 0x50 + 0x50);
  if ((*pbVar2 | 2) == 2) {
    *pbVar2 = 1;
    param_1 = param_1 + (long)param_2 * 0x50;
    *(undefined4 *)(param_1 + (long)*(int *)(param_1 + 0x30) * 4 + 0x3c) = 0;
    uVar1 = Aska::PrimitiveBuffer::NativeVertexBuffer()();
    *(undefined8 *)(param_1 + 0x48) = uVar1;
    return uVar1;
  }
  return *(undefined8 *)(param_1 + (long)param_2 * 0x50 + 0x48);
}

// ==== Aska::ParticleRenderManager::UnlockBuffer(int, bool)
// vaddr 0x236ad80 | ghidra 0x246ad80 | size 128 | symbol _ZN4Aska21ParticleRenderManager12UnlockBufferEib | lib libSOA-3.7.0.so | 2026-10-08
int _ZN4Aska21ParticleRenderManager12UnlockBufferEib(long param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  char *pcVar4;
  long lVar5;
  char cVar6;
  
  pcVar4 = (char *)(param_1 + (long)param_2 * 0x50 + 0x50);
  if (*pcVar4 == '\x01') {
    lVar5 = (long)param_2;
    lVar3 = param_1 + lVar5 * 0x50;
    uVar2 = *(uint *)(lVar3 + 0x30);
    iVar1 = *(int *)(lVar3 + (long)(int)uVar2 * 4 + 0x3c);
    if (((iVar1 < 1) || (*(int *)(param_1 + lVar5 * 0x50 + (long)(int)(uVar2 ^ 1) * 4 + 0x3c) == 0))
       || ((param_3 & 1) != 0)) {
      cVar6 = '\0';
    }
    else {
      cVar6 = '\x02';
    }
    *pcVar4 = cVar6;
    *(undefined8 *)(param_1 + lVar5 * 0x50 + 0x48) = 0;
    return iVar1;
  }
  return 0;
}

// ==== Aska::ParticleRenderManager::FillVerts(int, Aska::ParticleFillContext const*, Aska::ParticleContext const*, int, Aska::Vector*, Aska::Vector*)
// vaddr 0x236ae00 | ghidra 0x246ae00 | size 128 | symbol _ZN4Aska21ParticleRenderManager9FillVertsEiPKNS_19ParticleFillContextEPKNS_15ParticleContextEiPNS_6VectorES8_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager9FillVertsEiPKNS_19ParticleFillContextEPKNS_15ParticleContextEiPNS_6VectorES8_
               (long *param_1,int param_2,long param_3,undefined8 param_4,int param_5)

{
  if ((0 < param_5) && ((char)param_1[(long)param_2 * 10 + 10] == '\x01')) {
    switch(*(undefined2 *)(param_3 + 0x18)) {
    case 1:
                    /* WARNING: Could not recover jumptable at 0x0246ae64. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_1 + 0x78))();
      return;
    case 2:
                    /* WARNING: Could not recover jumptable at 0x0246ae70. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_1 + 0x90))();
      return;
    case 3:
    case 5:
    case 6:
                    /* WARNING: Could not recover jumptable at 0x0246ae48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_1 + 0x80))();
      return;
    case 4:
                    /* WARNING: Could not recover jumptable at 0x0246ae7c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_1 + 0x88))();
      return;
    default:
                    /* WARNING: Could not recover jumptable at 0x0246ae58. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_1 + 0x70))();
      return;
    }
  }
  return;
}

// ==== Aska::ParticleRenderManager::SetTextures(Aska::ParticleDrawContext const*)
// vaddr 0x236ae80 | ghidra 0x246ae80 | size 228 | symbol _ZN4Aska21ParticleRenderManager11SetTexturesEPKNS_19ParticleDrawContextE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x0246aed0: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0246af18: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0246aed4) */
/* WARNING: Removing unreachable block (ram,0x0246af1c) */

void _ZN4Aska21ParticleRenderManager11SetTexturesEPKNS_19ParticleDrawContextE
               (undefined8 param_1,long param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar2 = *(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  if (*(long *)(param_2 + 0xe0) == 0) {
    if (*(long *)(param_2 + 0xf0) == 0) {
      Aska::RenderState::Static::SetTextureSamplingWrapMode(Aska::RenderDeviceGL*, int, Aska::TexWrap::Mode)(uVar2,2,2);
      Aska::RenderState::Static::SetTextureSamplingFilter(Aska::RenderDeviceGL*, int, Aska::TexSamp::Filter)(uVar2,2,0);
      uVar1 = 2;
    }
    else {
      Aska::RenderState::Static::SetTextureSamplingWrapMode(Aska::RenderDeviceGL*, int, Aska::TexWrap::Mode)(uVar2,1,2);
      Aska::RenderState::Static::SetTextureSamplingFilter(Aska::RenderDeviceGL*, int, Aska::TexSamp::Filter)(uVar2,1,1);
      uVar1 = 1;
    }
  }
  else {
    Aska::RenderState::Static::SetTextureSamplingWrapMode(Aska::RenderDeviceGL*, int, Aska::TexWrap::Mode)(uVar2,0,2);
    Aska::RenderState::Static::SetTextureSamplingFilter(Aska::RenderDeviceGL*, int, Aska::TexSamp::Filter)(uVar2,0,1);
    uVar1 = 0;
  }
  (*(code *)
    PTR__ZN4Aska11RenderState6Static30SetTextureSamplingMipmapFilterEPNS_14RenderDeviceGLEiNS_7TexSamp9MipFilterE_02cad2e8
  )(uVar2,uVar1,0);
  return;
}

// ==== Aska::ParticleRenderManager::SetShadowTexture(Aska::ParticleDrawContext const*)
// vaddr 0x236af64 | ghidra 0x246af64 | size 4 | symbol _ZN4Aska21ParticleRenderManager16SetShadowTextureEPKNS_19ParticleDrawContextE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager16SetShadowTextureEPKNS_19ParticleDrawContextE(void)

{
  return;
}

// ==== Aska::ParticleRenderManager::DrawDot(int, int, Aska::ParticleBuffer*, Aska::ParticleDrawContext*)
// vaddr 0x236af68 | ghidra 0x246af68 | size 232 | symbol _ZN4Aska21ParticleRenderManager7DrawDotEiiPNS_14ParticleBufferEPNS_19ParticleDrawContextE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager7DrawDotEiiPNS_14ParticleBufferEPNS_19ParticleDrawContextE
               (undefined8 param_1,undefined8 param_2,undefined4 param_3,long param_4,long param_5)

{
  undefined *puVar1;
  ulong uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  
  lVar7 = *(long *)(param_4 + 0x10);
  if (*(char *)(param_4 + 0x48) == '\x02') {
    *(undefined1 *)(param_4 + 0x48) = 3;
  }
  puVar1 = PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  uVar4 = *(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  Aska::RenderState::Static::SetAlphaBlendFunction(Aska::RenderDeviceGL*, Aska::AlphaBlend::Operation, Aska::SeparateAlphaBlendMode::E)(uVar4,param_2,*(byte *)(*(long *)(param_5 + 0xd8) + 0xb) & 3);
  lVar6 = *(long *)(lVar7 + 8);
  uVar5 = *(undefined8 *)puVar1;
  if (lVar6 == 0) {
    uVar3 = 0;
  }
  else {
    if (((*(int *)(lVar6 + 0x68) != 0) || (*(long *)(lVar6 + 0x48) == 0)) &&
       (uVar2 = (**(code **)**(undefined8 **)(lVar6 + 0x40))(*(undefined8 **)(lVar6 + 0x40),lVar6),
       (uVar2 & 1) != 0)) {
      *(undefined4 *)(lVar6 + 0x68) = 0;
    }
    uVar3 = *(undefined8 *)(*(long *)(lVar7 + 8) + 0x48);
  }
  Aska::RenderDeviceGL::BindVertexBuffer(unsigned long, void*)(uVar5,uVar3,0);
  Aska::RenderDeviceGL::DrawPrimitive(Aska::PrimType::Type, unsigned int)(uVar4,7,param_3);
  Aska::RenderDeviceGL::BindVertexBuffer(unsigned long, void*)(*(undefined8 *)puVar1,0,0);
  if (*(char *)(param_4 + 0x48) == '\x03') {
    *(undefined1 *)(param_4 + 0x48) = 0;
  }
  return;
}

// ==== Aska::ParticleRenderManager::DrawLine(int, int, Aska::ParticleBuffer*, Aska::ParticleDrawContext*)
// vaddr 0x236b050 | ghidra 0x246b050 | size 1316 | symbol _ZN4Aska21ParticleRenderManager8DrawLineEiiPNS_14ParticleBufferEPNS_19ParticleDrawContextE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska21ParticleRenderManager8DrawLineEiiPNS_14ParticleBufferEPNS_19ParticleDrawContextE
               (long param_1,undefined8 param_2,int param_3,long param_4,long param_5)

{
  long *plVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined *puVar8;
  undefined8 uVar9;
  ulong uVar10;
  undefined8 uVar11;
  undefined2 *puVar12;
  long lVar13;
  short *psVar14;
  int iVar15;
  int iVar16;
  undefined2 *puVar17;
  short *psVar18;
  int iVar19;
  ulong uVar20;
  long lVar21;
  undefined8 uVar22;
  long lVar23;
  uint uVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  short sVar31;
  short sVar32;
  short sVar33;
  short sVar34;
  short sVar35;
  short sVar36;
  short sVar37;
  short sVar38;
  int iVar39;
  int iVar40;
  int iVar41;
  int iVar42;
  int iVar43;
  int iVar44;
  int iVar45;
  int iVar46;
  short sVar47;
  short sVar48;
  short sVar49;
  short sVar50;
  short sVar51;
  short sVar52;
  short sVar53;
  short sVar54;
  int iVar55;
  int iVar56;
  short sVar57;
  short sVar58;
  short sVar59;
  short sVar60;
  short sVar61;
  short sVar62;
  short sVar63;
  short sVar64;
  undefined2 auStack_10060 [16];
  short asStack_10040 [32752];
  
  puVar17 = auStack_10060;
  uVar3 = *(uint *)(param_5 + 0x118);
  uVar6 = uVar3 - 2;
  uVar20 = (ulong)uVar6;
  if (1 < (int)uVar3) {
    lVar21 = *(long *)(param_4 + 0x10);
    if (*(char *)(param_4 + 0x48) == '\x02') {
      *(undefined1 *)(param_4 + 0x48) = 3;
    }
    puVar8 = PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
    uVar24 = 0;
    if (uVar3 != 0) {
      uVar24 = param_3 / (int)uVar3;
    }
    uVar9 = *(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
    uVar7 = 0;
    if (uVar3 != 0) {
      uVar7 = 0x2000 / uVar3;
    }
    Aska::RenderState::Static::SetAlphaBlendFunction(Aska::RenderDeviceGL*, Aska::AlphaBlend::Operation, Aska::SeparateAlphaBlendMode::E)(uVar9,param_2,*(byte *)(*(long *)(param_5 + 0xd8) + 0xb) & 3);
    lVar23 = *(long *)(lVar21 + 8);
    uVar22 = *(undefined8 *)puVar8;
    if (lVar23 == 0) {
      uVar11 = 0;
    }
    else {
      if (((*(int *)(lVar23 + 0x68) != 0) || (*(long *)(lVar23 + 0x48) == 0)) &&
         (uVar10 = (**(code **)**(undefined8 **)(lVar23 + 0x40))
                             (*(undefined8 **)(lVar23 + 0x40),lVar23), (uVar10 & 1) != 0)) {
        *(undefined4 *)(lVar23 + 0x68) = 0;
      }
      uVar11 = *(undefined8 *)(*(long *)(lVar21 + 8) + 0x48);
    }
    Aska::RenderDeviceGL::BindVertexBuffer(unsigned long, void*)(uVar22,uVar11,0);
    iVar39 = (int)_UNK_0294ee30;
    iVar40 = (int)((ulong)_UNK_0294ee30 >> 0x20);
    iVar41 = (int)_UNK_0294ee38;
    iVar42 = (int)((ulong)_UNK_0294ee38 >> 0x20);
    iVar43 = (int)_UNK_0294ee20;
    iVar44 = (int)((ulong)_UNK_0294ee20 >> 0x20);
    iVar45 = (int)_UNK_0294ee28;
    iVar46 = (int)((ulong)_UNK_0294ee28 >> 0x20);
    sVar47 = (short)_UNK_029d9e30;
    sVar48 = (short)((ulong)_UNK_029d9e30 >> 0x10);
    sVar49 = (short)((ulong)_UNK_029d9e30 >> 0x20);
    sVar50 = (short)((ulong)_UNK_029d9e30 >> 0x30);
    sVar51 = (short)_UNK_029d9e38;
    sVar52 = (short)((ulong)_UNK_029d9e38 >> 0x10);
    sVar53 = (short)((ulong)_UNK_029d9e38 >> 0x20);
    sVar54 = (short)((ulong)_UNK_029d9e38 >> 0x30);
    if ((int)uVar7 < (int)uVar24) {
      if (0 < (int)uVar24) {
        iVar5 = uVar3 - 1;
        uVar2 = uVar3 + 0xf & 0xf;
        lVar21 = param_1 + (long)(int)uVar6 * 0x28;
        lVar23 = (uVar20 + 1) - (ulong)uVar2;
        plVar1 = (long *)(lVar21 + 0x140a0);
        iVar4 = 0;
        if (iVar5 * 2 != 0) {
          iVar4 = 0x8000 / (iVar5 * 2);
        }
        do {
          uVar6 = uVar7;
          if ((int)uVar24 <= (int)uVar7) {
            uVar6 = uVar24;
          }
          lVar13 = *plVar1;
          if (lVar13 == 0) {
            if (0 < iVar4) {
              iVar16 = 0;
              iVar15 = 0;
              puVar17 = auStack_10060;
              psVar18 = asStack_10040;
              do {
                if ((uVar20 + 1 < 0x10) || (lVar23 == 0)) {
                  iVar19 = 0;
                  puVar12 = puVar17;
                  iVar25 = iVar15;
code_r0x0246b2c4:
                  iVar19 = iVar5 - iVar19;
                  do {
                    *puVar12 = (short)iVar25;
                    iVar25 = iVar25 + 1;
                    iVar19 = iVar19 + -1;
                    puVar12[1] = (short)iVar25;
                    puVar12 = puVar12 + 2;
                  } while (iVar19 != 0);
                }
                else {
                  sVar38 = (short)iVar15;
                  iVar19 = (int)lVar23;
                  uVar22 = CONCAT44(iVar15 + iVar40,iVar15 + iVar39);
                  iVar25 = iVar15 + iVar41;
                  iVar26 = iVar15 + iVar42;
                  iVar27 = iVar15 + iVar43;
                  iVar28 = iVar15 + iVar44;
                  iVar29 = iVar15 + iVar45;
                  iVar30 = iVar15 + iVar46;
                  sVar31 = sVar38 + sVar47;
                  sVar32 = sVar38 + sVar48;
                  sVar33 = sVar38 + sVar49;
                  sVar34 = sVar38 + sVar50;
                  sVar35 = sVar38 + sVar51;
                  sVar36 = sVar38 + sVar52;
                  sVar37 = sVar38 + sVar53;
                  sVar38 = sVar38 + sVar54;
                  lVar13 = lVar23;
                  psVar14 = psVar18;
                  do {
                    sVar60 = (short)iVar27;
                    sVar57 = (short)iVar28;
                    sVar58 = (short)iVar29;
                    sVar59 = (short)iVar30;
                    sVar64 = (short)uVar22;
                    sVar61 = (short)((ulong)uVar22 >> 0x20);
                    sVar62 = (short)iVar25;
                    sVar63 = (short)iVar26;
                    iVar27 = iVar27 + 0x10;
                    iVar28 = iVar28 + 0x10;
                    iVar29 = iVar29 + 0x10;
                    iVar30 = iVar30 + 0x10;
                    uVar22 = CONCAT44((int)((ulong)uVar22 >> 0x20) + 0x10,(int)uVar22 + 0x10);
                    iVar25 = iVar25 + 0x10;
                    iVar26 = iVar26 + 0x10;
                    lVar13 = lVar13 + -0x10;
                    psVar14[-0x10] = sVar31;
                    psVar14[-0xf] = sVar60 + 1;
                    psVar14[-0xe] = sVar32;
                    psVar14[-0xd] = sVar57 + 1;
                    psVar14[-0xc] = sVar33;
                    psVar14[-0xb] = sVar58 + 1;
                    psVar14[-10] = sVar34;
                    psVar14[-9] = sVar59 + 1;
                    psVar14[-8] = sVar35;
                    psVar14[-7] = sVar64 + 1;
                    psVar14[-6] = sVar36;
                    psVar14[-5] = sVar61 + 1;
                    psVar14[-4] = sVar37;
                    psVar14[-3] = sVar62 + 1;
                    psVar14[-2] = sVar38;
                    psVar14[-1] = sVar63 + 1;
                    *psVar14 = sVar31 + 8;
                    psVar14[1] = sVar60 + 9;
                    psVar14[2] = sVar32 + 8;
                    psVar14[3] = sVar57 + 9;
                    psVar14[4] = sVar33 + 8;
                    psVar14[5] = sVar58 + 9;
                    psVar14[6] = sVar34 + 8;
                    psVar14[7] = sVar59 + 9;
                    psVar14[8] = sVar35 + 8;
                    psVar14[9] = sVar64 + 9;
                    psVar14[10] = sVar36 + 8;
                    psVar14[0xb] = sVar61 + 9;
                    psVar14[0xc] = sVar37 + 8;
                    psVar14[0xd] = sVar62 + 9;
                    psVar14[0xe] = sVar38 + 8;
                    psVar14[0xf] = sVar63 + 9;
                    sVar31 = sVar31 + 0x10;
                    sVar32 = sVar32 + 0x10;
                    sVar33 = sVar33 + 0x10;
                    sVar34 = sVar34 + 0x10;
                    sVar35 = sVar35 + 0x10;
                    sVar36 = sVar36 + 0x10;
                    sVar37 = sVar37 + 0x10;
                    sVar38 = sVar38 + 0x10;
                    psVar14 = psVar14 + 0x20;
                  } while (lVar13 != 0);
                  puVar12 = puVar17 + lVar23 * 2;
                  iVar25 = iVar15 + iVar19;
                  if (uVar2 != 0) goto code_r0x0246b2c4;
                }
                iVar16 = iVar16 + 1;
                puVar17 = puVar17 + uVar20 * 2 + 2;
                iVar15 = iVar15 + uVar3;
                psVar18 = psVar18 + uVar20 * 2 + 2;
              } while (iVar16 != iVar4);
            }
            uVar10 = Aska::PrimitiveBuffer::CreateIndexBuffer(int, void const*, unsigned int, bool)(lVar21 + 0x14098,0x8000,auStack_10060,4,0);
            if ((uVar10 & 1) == 0) {
              Aska::IndexBuffer::Release()(*plVar1);
              lVar13 = 0;
            }
            else {
              *(int *)(param_1 + 0x14090) = *(int *)(param_1 + 0x14090) + 0x8000;
              lVar13 = *plVar1;
            }
          }
          Aska::RenderDeviceGL::DrawIndexedPrimitive(Aska::PrimType::Type, Aska::IndexBuffer&, unsigned int, unsigned long)(uVar9,2,lVar13,uVar6 * iVar5,0);
          uVar24 = uVar24 - uVar6;
        } while (0 < (int)uVar24);
      }
    }
    else {
      lVar23 = param_1 + (long)(int)uVar6 * 0x28;
      plVar1 = (long *)(lVar23 + 0x140a0);
      lVar21 = *plVar1;
      iVar4 = uVar3 - 1;
      if (lVar21 == 0) {
        iVar5 = 0;
        if (iVar4 * 2 != 0) {
          iVar5 = 0x8000 / (iVar4 * 2);
        }
        if (0 < iVar5) {
          uVar20 = (ulong)uVar6;
          uVar6 = uVar3 + 0xf & 0xf;
          lVar21 = (uVar20 + 1) - (ulong)uVar6;
          iVar16 = 0;
          iVar15 = 0;
          psVar18 = asStack_10040;
          do {
            if ((uVar20 + 1 < 0x10) || (lVar21 == 0)) {
              iVar19 = 0;
              puVar12 = puVar17;
              iVar25 = iVar15;
code_r0x0246b49c:
              iVar19 = iVar4 - iVar19;
              do {
                *puVar12 = (short)iVar25;
                iVar25 = iVar25 + 1;
                iVar19 = iVar19 + -1;
                puVar12[1] = (short)iVar25;
                puVar12 = puVar12 + 2;
              } while (iVar19 != 0);
            }
            else {
              sVar38 = (short)iVar15;
              iVar19 = (int)lVar21;
              iVar25 = iVar15 + iVar39;
              iVar26 = iVar15 + iVar40;
              iVar27 = iVar15 + iVar41;
              iVar28 = iVar15 + iVar42;
              iVar29 = iVar15 + iVar43;
              iVar30 = iVar15 + iVar44;
              iVar55 = iVar15 + iVar45;
              iVar56 = iVar15 + iVar46;
              uVar22 = CONCAT26(sVar38 + sVar50,
                                CONCAT24(sVar38 + sVar49,CONCAT22(sVar38 + sVar48,sVar38 + sVar47)))
              ;
              uVar11 = CONCAT26(sVar38 + sVar54,
                                CONCAT24(sVar38 + sVar53,CONCAT22(sVar38 + sVar52,sVar38 + sVar51)))
              ;
              lVar13 = lVar21;
              psVar14 = psVar18;
              do {
                sVar33 = (short)iVar29;
                sVar38 = (short)iVar30;
                sVar31 = (short)iVar55;
                sVar32 = (short)iVar56;
                sVar57 = (short)uVar22;
                sVar58 = (short)((ulong)uVar22 >> 0x10);
                sVar59 = (short)((ulong)uVar22 >> 0x20);
                sVar60 = (short)((ulong)uVar22 >> 0x30);
                sVar61 = (short)uVar11;
                sVar62 = (short)((ulong)uVar11 >> 0x10);
                sVar63 = (short)((ulong)uVar11 >> 0x20);
                sVar64 = (short)((ulong)uVar11 >> 0x30);
                sVar37 = (short)iVar25;
                sVar34 = (short)iVar26;
                sVar35 = (short)iVar27;
                sVar36 = (short)iVar28;
                iVar29 = iVar29 + 0x10;
                iVar30 = iVar30 + 0x10;
                iVar55 = iVar55 + 0x10;
                iVar56 = iVar56 + 0x10;
                iVar25 = iVar25 + 0x10;
                iVar26 = iVar26 + 0x10;
                iVar27 = iVar27 + 0x10;
                iVar28 = iVar28 + 0x10;
                lVar13 = lVar13 + -0x10;
                psVar14[-0x10] = sVar57;
                psVar14[-0xf] = sVar33 + 1;
                psVar14[-0xe] = sVar58;
                psVar14[-0xd] = sVar38 + 1;
                psVar14[-0xc] = sVar59;
                psVar14[-0xb] = sVar31 + 1;
                psVar14[-10] = sVar60;
                psVar14[-9] = sVar32 + 1;
                psVar14[-8] = sVar61;
                psVar14[-7] = sVar37 + 1;
                psVar14[-6] = sVar62;
                psVar14[-5] = sVar34 + 1;
                psVar14[-4] = sVar63;
                psVar14[-3] = sVar35 + 1;
                psVar14[-2] = sVar64;
                psVar14[-1] = sVar36 + 1;
                *psVar14 = sVar57 + 8;
                psVar14[1] = sVar33 + 9;
                psVar14[2] = sVar58 + 8;
                psVar14[3] = sVar38 + 9;
                psVar14[4] = sVar59 + 8;
                psVar14[5] = sVar31 + 9;
                psVar14[6] = sVar60 + 8;
                psVar14[7] = sVar32 + 9;
                psVar14[8] = sVar61 + 8;
                psVar14[9] = sVar37 + 9;
                psVar14[10] = sVar62 + 8;
                psVar14[0xb] = sVar34 + 9;
                psVar14[0xc] = sVar63 + 8;
                psVar14[0xd] = sVar35 + 9;
                psVar14[0xe] = sVar64 + 8;
                psVar14[0xf] = sVar36 + 9;
                uVar22 = CONCAT26(sVar60 + 0x10,
                                  CONCAT24(sVar59 + 0x10,CONCAT22(sVar58 + 0x10,sVar57 + 0x10)));
                uVar11 = CONCAT26(sVar64 + 0x10,
                                  CONCAT24(sVar63 + 0x10,CONCAT22(sVar62 + 0x10,sVar61 + 0x10)));
                psVar14 = psVar14 + 0x20;
              } while (lVar13 != 0);
              puVar12 = puVar17 + lVar21 * 2;
              iVar25 = iVar15 + iVar19;
              if (uVar6 != 0) goto code_r0x0246b49c;
            }
            iVar16 = iVar16 + 1;
            puVar17 = puVar17 + uVar20 * 2 + 2;
            iVar15 = iVar15 + uVar3;
            psVar18 = psVar18 + uVar20 * 2 + 2;
          } while (iVar16 != iVar5);
        }
        uVar20 = Aska::PrimitiveBuffer::CreateIndexBuffer(int, void const*, unsigned int, bool)(lVar23 + 0x14098,0x8000,auStack_10060,4,0);
        if ((uVar20 & 1) == 0) {
          Aska::IndexBuffer::Release()(*plVar1);
          lVar21 = 0;
        }
        else {
          *(int *)(param_1 + 0x14090) = *(int *)(param_1 + 0x14090) + 0x8000;
          lVar21 = *plVar1;
        }
      }
      Aska::RenderDeviceGL::DrawIndexedPrimitive(Aska::PrimType::Type, Aska::IndexBuffer&, unsigned int, unsigned long)(uVar9,2,lVar21,uVar24 * iVar4,0);
    }
    Aska::RenderDeviceGL::BindVertexBuffer(unsigned long, void*)(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,0,0);
    if (*(char *)(param_4 + 0x48) == '\x03') {
      *(undefined1 *)(param_4 + 0x48) = 0;
    }
  }
  return;
}

// ==== Aska::ParticleRenderManager::DrawPolyLine(int, int, Aska::ParticleBuffer*, Aska::ParticleDrawContext*)
// vaddr 0x236b574 | ghidra 0x246b574 | size 388 | symbol _ZN4Aska21ParticleRenderManager12DrawPolyLineEiiPNS_14ParticleBufferEPNS_19ParticleDrawContextE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager12DrawPolyLineEiiPNS_14ParticleBufferEPNS_19ParticleDrawContextE
               (undefined8 param_1,undefined8 param_2,int param_3,long param_4,long param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  ulong uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  long lVar10;
  int iVar11;
  long lVar12;
  
  iVar2 = *(int *)(param_5 + 0x118);
  if (1 < iVar2) {
    lVar12 = *(long *)(param_4 + 0x10);
    if (*(char *)(param_4 + 0x48) == '\x02') {
      *(undefined1 *)(param_4 + 0x48) = 3;
    }
    puVar5 = PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
    iVar3 = iVar2 * 2;
    uVar8 = *(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
    iVar11 = 0;
    if (iVar3 != 0) {
      iVar11 = param_3 / iVar3;
    }
    iVar4 = 0;
    if (iVar3 != 0) {
      iVar4 = 0x2000 / iVar3;
    }
    Aska::RenderState::Static::SetAlphaBlendFunction(Aska::RenderDeviceGL*, Aska::AlphaBlend::Operation, Aska::SeparateAlphaBlendMode::E)(uVar8,param_2,*(byte *)(*(long *)(param_5 + 0xd8) + 0xb) & 3);
    lVar10 = *(long *)(lVar12 + 8);
    uVar9 = *(undefined8 *)puVar5;
    if (lVar10 == 0) {
      uVar7 = 0;
    }
    else {
      if (((*(int *)(lVar10 + 0x68) != 0) || (*(long *)(lVar10 + 0x48) == 0)) &&
         (uVar6 = (**(code **)**(undefined8 **)(lVar10 + 0x40))
                            (*(undefined8 **)(lVar10 + 0x40),lVar10), (uVar6 & 1) != 0)) {
        *(undefined4 *)(lVar10 + 0x68) = 0;
      }
      uVar7 = *(undefined8 *)(*(long *)(lVar12 + 8) + 0x48);
    }
    Aska::RenderDeviceGL::BindVertexBuffer(unsigned long, void*)(uVar9,uVar7,0);
    if (iVar4 < iVar11) {
      if (0 < iVar11) {
        do {
          iVar1 = iVar4;
          if (iVar11 <= iVar4) {
            iVar1 = iVar11;
          }
          uVar9 = Aska::ParticleRenderManager::GetPolyStripIndexBuffer(int)(param_1,iVar2);
          Aska::RenderDeviceGL::DrawIndexedPrimitive(Aska::PrimType::Type, Aska::IndexBuffer&, unsigned int, unsigned long)(uVar8,5,uVar9,iVar1 * (iVar3 + 2) + -4,0);
          iVar11 = iVar11 - iVar1;
        } while (0 < iVar11);
      }
    }
    else {
      uVar9 = Aska::ParticleRenderManager::GetPolyStripIndexBuffer(int)(param_1,iVar2);
      Aska::RenderDeviceGL::DrawIndexedPrimitive(Aska::PrimType::Type, Aska::IndexBuffer&, unsigned int, unsigned long)(uVar8,5,uVar9,iVar11 * (iVar3 + 2) + -4,0);
    }
    Aska::RenderDeviceGL::BindVertexBuffer(unsigned long, void*)(*(undefined8 *)puVar5,0,0);
    if (*(char *)(param_4 + 0x48) == '\x03') {
      *(undefined1 *)(param_4 + 0x48) = 0;
    }
  }
  return;
}

// ==== Aska::ParticleRenderManager::DrawFilterSprite(int*, int, Aska::ParticleBuffer*, Aska::ParticleDrawContext*, int, int)
// vaddr 0x236b6f8 | ghidra 0x246b6f8 | size 96 | symbol _ZN4Aska21ParticleRenderManager16DrawFilterSpriteEPiiPNS_14ParticleBufferEPNS_19ParticleDrawContextEii | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager16DrawFilterSpriteEPiiPNS_14ParticleBufferEPNS_19ParticleDrawContextEii
               (void)

{
  long in_x4;
  undefined8 uVar1;
  undefined4 uStack_30;
  undefined8 uStack_2c;
  undefined4 uStack_24;
  
  uStack_30 = *(undefined4 *)(in_x4 + 0xb8);
  uVar1 = *(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  uStack_2c = 0;
  uStack_24 = 0;
  Aska::RenderDeviceGL::SetPixelShaderConstant(int, void const*, int)(uVar1,0x14,&uStack_30,1);
  Aska::RenderDeviceGL::SetTexture(unsigned int, Aska::GpuResource* const*)(uVar1,2,in_x4 + 0x108);
  return;
}

// ==== Aska::ParticleRenderManager::DrawSprite(int*, int, Aska::ParticleBuffer*, Aska::ParticleDrawContext*, int, int)
// vaddr 0x236b758 | ghidra 0x246b758 | size 896 | symbol _ZN4Aska21ParticleRenderManager10DrawSpriteEPiiPNS_14ParticleBufferEPNS_19ParticleDrawContextEii | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager10DrawSpriteEPiiPNS_14ParticleBufferEPNS_19ParticleDrawContextEii
               (long *param_1,long param_2,int param_3,long param_4,long param_5,undefined4 param_6,
               uint param_7)

{
  long *plVar1;
  long *plVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  ushort uVar7;
  undefined *puVar8;
  ulong uVar9;
  ulong uVar10;
  undefined8 uVar11;
  int iVar12;
  ushort *puVar13;
  ushort *puVar14;
  int iVar15;
  long lVar16;
  undefined8 uVar17;
  int iVar18;
  undefined8 uVar19;
  long lVar20;
  int iVar21;
  int iVar22;
  ushort auStack_10060 [32768];
  
  lVar16 = *(long *)(param_4 + 0x10);
  if (*(char *)(param_4 + 0x48) == '\x02') {
    *(undefined1 *)(param_4 + 0x48) = 3;
  }
  puVar8 = PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  uVar17 = *(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  Aska::IParticleRenderManager::SetSpriteState(Aska::ParticleDrawContext const*, int)(param_1,param_5,param_6);
  (**(code **)(*param_1 + 0x60))(param_1,param_5);
  iVar6 = 0;
  if (param_7 != 0) {
    iVar6 = param_3 / (int)param_7;
  }
  lVar20 = *(long *)(lVar16 + 8);
  uVar19 = *(undefined8 *)puVar8;
  bVar4 = *(byte *)(*(long *)(param_5 + 0xd8) + 0xb);
  iVar3 = iVar6 + 3;
  if (-1 < iVar6) {
    iVar3 = iVar6;
  }
  if (lVar20 == 0) {
    uVar11 = 0;
  }
  else {
    if (((*(int *)(lVar20 + 0x68) != 0) || (*(long *)(lVar20 + 0x48) == 0)) &&
       (uVar9 = (**(code **)**(undefined8 **)(lVar20 + 0x40))
                          (*(undefined8 **)(lVar20 + 0x40),lVar20), (uVar9 & 1) != 0)) {
      *(undefined4 *)(lVar20 + 0x68) = 0;
    }
    uVar11 = *(undefined8 *)(*(long *)(lVar16 + 8) + 0x48);
  }
  Aska::RenderDeviceGL::BindVertexBuffer(unsigned long, void*)(uVar19,uVar11,0);
  if (0 < (int)param_7) {
    plVar1 = param_1 + 0x2812;
    iVar5 = (iVar3 >> 2) * 6;
    uVar9 = 0;
    iVar22 = 0;
    plVar2 = param_1 + 0x28aa;
    do {
      Aska::RenderState::Static::SetAlphaBlendFunction(Aska::RenderDeviceGL*, Aska::AlphaBlend::Operation, Aska::SeparateAlphaBlendMode::E)(uVar17,*(undefined4 *)(param_2 + uVar9 * 4),bVar4 & 3);
      iVar18 = iVar3 >> 2;
      if (iVar6 < 0x2004) {
        lVar16 = *plVar2;
        if (lVar16 == 0) {
          iVar18 = 0;
          puVar13 = auStack_10060;
          do {
            if (iVar18 == 0) {
              iVar21 = 0;
              puVar14 = puVar13;
            }
            else {
              *puVar13 = (ushort)iVar18;
              puVar14 = puVar13 + 1;
              iVar21 = iVar18;
            }
            uVar7 = (ushort)iVar21;
            *puVar14 = uVar7;
            iVar18 = iVar18 + 4;
            puVar14[1] = uVar7 | 1;
            puVar13 = puVar14 + 5;
            puVar14[2] = uVar7 | 2;
            puVar14[3] = uVar7 | 3;
            puVar14[4] = uVar7 | 3;
          } while (iVar18 != 0x5554);
          uVar10 = Aska::PrimitiveBuffer::CreateIndexBuffer(int, void const*, unsigned int, bool)(param_1 + 0x28a9,0x8000,auStack_10060,4,0);
          if ((uVar10 & 1) == 0) {
            Aska::IndexBuffer::Release()(*plVar2);
            lVar16 = 0;
          }
          else {
            *(int *)plVar1 = (int)*plVar1 + 0x8000;
            lVar16 = *plVar2;
          }
        }
        Aska::RenderDeviceGL::DrawIndexedPrimitive(Aska::PrimType::Type, Aska::IndexBuffer&, unsigned int, unsigned long)(uVar17,5,lVar16,iVar5 + -4,iVar22);
        iVar22 = iVar22 + iVar5;
      }
      else {
        do {
          lVar16 = *plVar2;
          iVar21 = iVar18;
          if (0x7ff < iVar18) {
            iVar21 = 0x800;
          }
          if (lVar16 == 0) {
            iVar12 = 0;
            puVar13 = auStack_10060;
            do {
              if (iVar12 == 0) {
                iVar15 = 0;
                puVar14 = puVar13;
              }
              else {
                *puVar13 = (ushort)iVar12;
                puVar14 = puVar13 + 1;
                iVar15 = iVar12;
              }
              uVar7 = (ushort)iVar15;
              *puVar14 = uVar7;
              iVar12 = iVar12 + 4;
              puVar14[1] = uVar7 | 1;
              puVar13 = puVar14 + 5;
              puVar14[2] = uVar7 | 2;
              puVar14[3] = uVar7 | 3;
              puVar14[4] = uVar7 | 3;
            } while (iVar12 != 0x5554);
            uVar10 = Aska::PrimitiveBuffer::CreateIndexBuffer(int, void const*, unsigned int, bool)(param_1 + 0x28a9,0x8000,auStack_10060,4,0);
            if ((uVar10 & 1) == 0) {
              Aska::IndexBuffer::Release()(*plVar2);
              lVar16 = 0;
            }
            else {
              *(int *)plVar1 = (int)*plVar1 + 0x8000;
              lVar16 = *plVar2;
            }
          }
          Aska::RenderDeviceGL::DrawIndexedPrimitive(Aska::PrimType::Type, Aska::IndexBuffer&, unsigned int, unsigned long)(uVar17,5,lVar16,iVar21 * 6 + -4,iVar22);
          iVar18 = iVar18 - iVar21;
          iVar22 = iVar21 * 6 + iVar22;
        } while (0 < iVar18);
      }
      uVar9 = uVar9 + 1;
    } while (uVar9 != param_7);
  }
  Aska::RenderDeviceGL::BindVertexBuffer(unsigned long, void*)(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,0,0);
  if (*(char *)(param_4 + 0x48) == '\x03') {
    *(undefined1 *)(param_4 + 0x48) = 0;
  }
  return;
}

// ==== Aska::ParticleRenderManager::DrawSpriteLine(int*, int, Aska::ParticleBuffer*, Aska::ParticleDrawContext*, int, int)
// vaddr 0x236bad8 | ghidra 0x246bad8 | size 588 | symbol _ZN4Aska21ParticleRenderManager14DrawSpriteLineEPiiPNS_14ParticleBufferEPNS_19ParticleDrawContextEii | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager14DrawSpriteLineEPiiPNS_14ParticleBufferEPNS_19ParticleDrawContextEii
               (long *param_1,undefined4 *param_2,int param_3,long param_4,long param_5,int param_6,
               uint param_7)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined *puVar8;
  ulong uVar9;
  undefined8 uVar10;
  int iVar11;
  ulong uVar12;
  undefined8 uVar13;
  int iVar14;
  long lVar15;
  undefined8 uVar16;
  long lVar17;
  
  iVar2 = *(int *)(param_5 + 0x118);
  if (1 < iVar2) {
    lVar15 = *(long *)(param_4 + 0x10);
    if (*(char *)(param_4 + 0x48) == '\x02') {
      Aska::VertexBuffer::Unlock(unsigned int)(lVar15,param_3);
      *(undefined1 *)(param_4 + 0x48) = 3;
    }
    puVar8 = PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
    uVar13 = *(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
    (**(code **)(*param_1 + 0x60))(param_1,param_5);
    lVar17 = *(long *)(lVar15 + 8);
    uVar16 = *(undefined8 *)puVar8;
    bVar3 = *(byte *)(*(long *)(param_5 + 0xd8) + 0xb);
    if (lVar17 == 0) {
      uVar10 = 0;
    }
    else {
      if (((*(int *)(lVar17 + 0x68) != 0) || (*(long *)(lVar17 + 0x48) == 0)) &&
         (uVar9 = (**(code **)**(undefined8 **)(lVar17 + 0x40))
                            (*(undefined8 **)(lVar17 + 0x40),lVar17), (uVar9 & 1) != 0)) {
        *(undefined4 *)(lVar17 + 0x68) = 0;
      }
      uVar10 = *(undefined8 *)(*(long *)(lVar15 + 8) + 0x48);
    }
    Aska::RenderDeviceGL::BindVertexBuffer(unsigned long, void*)(uVar16,uVar10,0);
    if (0 < (int)param_7) {
      iVar11 = 0;
      if (param_7 != 0) {
        iVar11 = param_3 / (int)param_7;
      }
      iVar4 = iVar2 * 2;
      iVar14 = 0;
      if (param_6 != 0) {
        iVar14 = iVar11 / param_6;
      }
      iVar11 = 0;
      if (iVar4 != 0) {
        iVar11 = 0x2000 / iVar4;
      }
      iVar6 = 0;
      if (iVar4 != 0) {
        iVar6 = iVar14 / iVar4;
      }
      bVar3 = bVar3 & 3;
      uVar9 = (ulong)param_7;
      if (iVar11 < iVar6) {
        uVar12 = 0;
        iVar14 = 0;
        do {
          Aska::RenderState::Static::SetAlphaBlendFunction(Aska::RenderDeviceGL*, Aska::AlphaBlend::Operation, Aska::SeparateAlphaBlendMode::E)(uVar13,param_2[uVar12],bVar3);
          for (iVar7 = iVar6; 0 < iVar7; iVar7 = iVar7 - iVar1) {
            iVar1 = iVar11;
            if (iVar7 <= iVar11) {
              iVar1 = iVar7;
            }
            iVar5 = iVar1 * (iVar4 + 2);
            uVar16 = Aska::ParticleRenderManager::GetPolyStripIndexBuffer(int)(param_1,iVar2);
            Aska::RenderDeviceGL::DrawIndexedPrimitive(Aska::PrimType::Type, Aska::IndexBuffer&, unsigned int, unsigned long)(uVar13,5,uVar16,iVar5 + -4,iVar14);
            iVar14 = iVar5 + iVar14;
          }
          uVar12 = uVar12 + 1;
        } while (uVar12 != uVar9);
      }
      else {
        iVar6 = iVar6 * (iVar4 + 2);
        iVar11 = 0;
        do {
          Aska::RenderState::Static::SetAlphaBlendFunction(Aska::RenderDeviceGL*, Aska::AlphaBlend::Operation, Aska::SeparateAlphaBlendMode::E)(uVar13,*param_2,bVar3);
          uVar16 = Aska::ParticleRenderManager::GetPolyStripIndexBuffer(int)(param_1,iVar2);
          Aska::RenderDeviceGL::DrawIndexedPrimitive(Aska::PrimType::Type, Aska::IndexBuffer&, unsigned int, unsigned long)(uVar13,5,uVar16,iVar6 + -4,iVar11);
          uVar9 = uVar9 - 1;
          iVar11 = iVar11 + iVar6;
          param_2 = param_2 + 1;
        } while (uVar9 != 0);
      }
    }
    Aska::RenderDeviceGL::BindVertexBuffer(unsigned long, void*)(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,0,0);
    if (*(char *)(param_4 + 0x48) == '\x03') {
      *(undefined1 *)(param_4 + 0x48) = 0;
    }
  }
  return;
}

// ==== Aska::ParticleRenderManager::BindShader(Aska::ShaderCache*)
// vaddr 0x236bd24 | ghidra 0x246bd24 | size 36 | symbol _ZN4Aska21ParticleRenderManager10BindShaderEPNS_11ShaderCacheE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager10BindShaderEPNS_11ShaderCacheE
               (undefined8 param_1,undefined8 param_2)

{
  (*(code *)PTR__ZN4Aska18AHSLCacheManagerV214SearchBindedVSEPNS_11ShaderCacheEmi_02ca3228)
            (*(long *)PTR__ZN4Aska6Global20m_pShaderLinkManagerE_02cb93f8 + 8,param_2,0x2002201204,
             0x60);
  return;
}

// ==== Aska::ParticleRenderManager::FillDot(int, Aska::ParticleFillContext const*, Aska::ParticleContext const*, int, Aska::Vector*, Aska::Vector*)
// vaddr 0x236bd48 | ghidra 0x246bd48 | size 432 | symbol _ZN4Aska21ParticleRenderManager7FillDotEiPKNS_19ParticleFillContextEPKNS_15ParticleContextEiPNS_6VectorES8_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager7FillDotEiPKNS_19ParticleFillContextEPKNS_15ParticleContextEiPNS_6VectorES8_
               (long param_1,int param_2,undefined8 param_3,float *param_4,uint param_5,
               float *param_6,float *param_7)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  long lVar10;
  float *pfVar11;
  ulong uVar12;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  
  lVar10 = param_1 + (long)param_2 * 0x50;
  fStack_30 = *param_6;
  fStack_2c = param_6[1];
  fStack_28 = param_6[2];
  fStack_24 = param_6[3];
  fStack_40 = *param_7;
  fStack_3c = param_7[1];
  fStack_38 = param_7[2];
  fStack_34 = param_7[3];
  if (0 < (int)param_5) {
    uVar12 = (ulong)param_5;
    pfVar11 = (float *)(*(long *)(lVar10 + 0x48) +
                        (long)*(int *)(lVar10 + (long)*(int *)(lVar10 + 0x30) * 4 + 0x3c) * 0x60 +
                       0x10);
    while( true ) {
      uVar12 = uVar12 - 1;
      fStack_50 = *param_4;
      fStack_4c = param_4[1];
      fStack_48 = param_4[2];
      fStack_44 = param_4[0x10];
      pfVar6 = &fStack_30;
      if (fStack_50 <= fStack_30) {
        pfVar6 = &fStack_50;
      }
      pfVar1 = &fStack_30;
      if (fStack_4c <= fStack_2c) {
        pfVar1 = &fStack_50;
      }
      pfVar2 = &fStack_30;
      if (fStack_48 <= fStack_28) {
        pfVar2 = &fStack_50;
      }
      pfVar3 = &fStack_30;
      if (fStack_44 <= fStack_24) {
        pfVar3 = &fStack_50;
      }
      pfVar4 = &fStack_40;
      if (fStack_40 <= fStack_50) {
        pfVar4 = &fStack_50;
      }
      pfVar5 = &fStack_40;
      if (fStack_3c <= fStack_4c) {
        pfVar5 = &fStack_50;
      }
      fStack_30 = *pfVar6;
      fStack_40 = *pfVar4;
      fStack_2c = pfVar1[1];
      fStack_3c = pfVar5[1];
      pfVar6 = &fStack_40;
      if (fStack_38 <= fStack_48) {
        pfVar6 = &fStack_50;
      }
      fStack_28 = pfVar2[2];
      fStack_38 = pfVar6[2];
      pfVar6 = &fStack_40;
      if (fStack_34 <= fStack_44) {
        pfVar6 = &fStack_50;
      }
      fStack_24 = pfVar3[3];
      fStack_34 = pfVar6[3];
      fVar8 = param_4[5];
      fVar7 = param_4[6];
      fVar9 = param_4[7];
      *pfVar11 = param_4[4];
      pfVar11[1] = fVar8;
      pfVar11[-4] = fStack_50;
      pfVar11[-3] = fStack_4c;
      pfVar11[2] = fVar7;
      pfVar11[3] = fVar9;
      pfVar11[-2] = fStack_48;
      pfVar11[-1] = fStack_44;
      if (uVar12 == 0) break;
      pfVar11 = pfVar11 + 0x18;
      param_4 = param_4 + 0x14;
    }
  }
  *(ulong *)(param_6 + 2) = CONCAT44(fStack_24,fStack_28);
  *(ulong *)param_6 = CONCAT44(fStack_2c,fStack_30);
  *(ulong *)(param_7 + 2) = CONCAT44(fStack_34,fStack_38);
  *(ulong *)param_7 = CONCAT44(fStack_3c,fStack_40);
  lVar10 = param_1 + (long)param_2 * 0x50 + (long)*(int *)(lVar10 + 0x30) * 4;
  *(uint *)(lVar10 + 0x3c) = *(int *)(lVar10 + 0x3c) + param_5;
  return;
}

// ==== Aska::ParticleRenderManager::FillLine(int, Aska::ParticleFillContext const*, Aska::ParticleContext const*, int, Aska::Vector*, Aska::Vector*)
// vaddr 0x236bef8 | ghidra 0x246bef8 | size 12 | symbol _ZN4Aska21ParticleRenderManager8FillLineEiPKNS_19ParticleFillContextEPKNS_15ParticleContextEiPNS_6VectorES8_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager8FillLineEiPKNS_19ParticleFillContextEPKNS_15ParticleContextEiPNS_6VectorES8_
               (long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0246bf00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x70))();
  return;
}

// ==== Aska::ParticleRenderManager::FillSprite(int, Aska::ParticleFillContext const*, Aska::ParticleContext const*, int, Aska::Vector*, Aska::Vector*)
// vaddr 0x236bf04 | ghidra 0x246bf04 | size 1080 | symbol _ZN4Aska21ParticleRenderManager10FillSpriteEiPKNS_19ParticleFillContextEPKNS_15ParticleContextEiPNS_6VectorES8_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager10FillSpriteEiPKNS_19ParticleFillContextEPKNS_15ParticleContextEiPNS_6VectorES8_
               (long param_1,int param_2,long *param_3,long param_4,uint param_5,float *param_6,
               float *param_7)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  uint uVar6;
  float fVar7;
  char cVar8;
  ulong uVar9;
  long lVar10;
  long lVar11;
  long *plVar12;
  ulong uVar13;
  float *pfVar14;
  long lVar15;
  ulong uVar16;
  ushort *puVar17;
  uint uVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  float fStack_c4;
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  float fStack_b4;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  undefined2 uStack_98;
  undefined2 uStack_96;
  undefined2 uStack_94;
  undefined2 uStack_92;
  long alStack_90 [4];
  
  lVar10 = param_1 + (long)param_2 * 0x50;
  uVar6 = *(uint *)(param_3 + 8);
  uVar9 = (ulong)uVar6;
  lVar11 = *(long *)(lVar10 + 0x48) +
           (long)*(int *)(lVar10 + (long)*(int *)(lVar10 + 0x30) * 4 + 0x3c) * 0x60;
  if (*(char *)((long)param_3 + 0x44) == '\0') {
    if (uVar6 != 0) {
      plVar12 = alStack_90;
      uVar13 = uVar9;
      do {
        *plVar12 = lVar11;
        uVar13 = uVar13 - 1;
        lVar11 = lVar11 + (long)(int)(param_5 << 2) * 0x60;
        plVar12 = plVar12 + 1;
      } while (uVar13 != 0);
    }
  }
  else if (uVar6 != 0) {
    uVar13 = uVar9;
    do {
      uVar13 = uVar13 - 1;
      alStack_90[uVar13 & 0xffffffff] = lVar11;
      lVar11 = lVar11 + (long)(int)(param_5 << 2) * 0x60;
    } while (uVar13 != 0);
  }
  fStack_b0 = *param_6;
  fStack_ac = param_6[1];
  fStack_a8 = param_6[2];
  fStack_a4 = param_6[3];
  fStack_c0 = *param_7;
  fStack_bc = param_7[1];
  fStack_b8 = param_7[2];
  fStack_b4 = param_7[3];
  if (0 < (int)param_5) {
    fVar19 = *(float *)((long)param_3 + 0xc);
    fVar20 = *(float *)(param_3 + 2);
    uVar13 = 0;
    do {
      pfVar14 = (float *)(param_4 + uVar13 * 0x50);
      fStack_d0 = *pfVar14;
      fStack_cc = pfVar14[1];
      fStack_c8 = pfVar14[2];
      fStack_c4 = pfVar14[0x10];
      pfVar1 = &fStack_b0;
      if (fStack_d0 <= fStack_b0) {
        pfVar1 = &fStack_d0;
      }
      pfVar2 = &fStack_b0;
      if (fStack_cc <= fStack_ac) {
        pfVar2 = &fStack_d0;
      }
      pfVar3 = &fStack_b0;
      if (fStack_c8 <= fStack_a8) {
        pfVar3 = &fStack_d0;
      }
      pfVar4 = &fStack_b0;
      if (fStack_c4 <= fStack_a4) {
        pfVar4 = &fStack_d0;
      }
      pfVar5 = &fStack_c0;
      if (fStack_c0 <= fStack_d0) {
        pfVar5 = &fStack_d0;
      }
      fStack_b0 = *pfVar1;
      pfVar1 = &fStack_c0;
      if (fStack_bc <= fStack_cc) {
        pfVar1 = &fStack_d0;
      }
      fStack_c0 = *pfVar5;
      fStack_ac = pfVar2[1];
      fVar22 = pfVar14[0xd];
      fStack_bc = pfVar1[1];
      fStack_a8 = pfVar3[2];
      pfVar1 = &fStack_c0;
      if (fStack_b8 <= fStack_c8) {
        pfVar1 = &fStack_d0;
      }
      fVar21 = pfVar14[8];
      fVar7 = pfVar14[9];
      fStack_b8 = pfVar1[2];
      pfVar1 = &fStack_c0;
      if (fStack_b4 <= fStack_c4) {
        pfVar1 = &fStack_d0;
      }
      uVar18 = (uint)fVar22 >> 0x10;
      uStack_92 = SUB42(pfVar14[0xc],0);
      uStack_96 = SUB42(fVar22,0);
      uStack_98 = (short)((uint)fVar22 >> 0x10);
      uStack_94 = (short)((uint)pfVar14[0xc] >> 0x10);
      fStack_a4 = pfVar4[3];
      fStack_b4 = pfVar1[3];
      if (uVar6 != 0) {
        lVar15 = param_4 + uVar13 * 0x50;
        fVar22 = pfVar14[10];
        fVar23 = pfVar14[0xb];
        cVar8 = *(char *)((long)param_3 + 0x44);
        fVar24 = *(float *)((long)param_3 + 0x1c);
        fVar25 = *(float *)(param_3 + 4);
        lVar11 = *param_3;
        fVar27 = *(float *)(lVar15 + 0x18);
        fVar28 = *(float *)(lVar15 + 0x1c);
        fVar29 = *(float *)(lVar15 + 0x10);
        fVar30 = *(float *)(lVar15 + 0x14);
        plVar12 = alStack_90;
        puVar17 = (ushort *)((ulong)&uStack_98 | 2);
        uVar16 = uVar9;
        while( true ) {
          uVar16 = uVar16 - 1;
          pfVar1 = (float *)(lVar11 + (ulong)uVar18 * 0x40);
          fVar33 = pfVar1[4];
          fVar32 = pfVar1[5];
          fVar42 = pfVar1[2];
          fVar26 = pfVar1[3];
          pfVar14 = (float *)*plVar12;
          fVar31 = pfVar1[0xc];
          fVar38 = *pfVar1;
          fVar39 = pfVar1[1];
          fVar34 = fVar29 * pfVar1[8];
          fVar35 = fVar30 * pfVar1[9];
          fVar36 = fVar27 * pfVar1[10];
          fVar37 = fVar28 * pfVar1[0xb];
          fVar40 = pfVar1[6] - fVar33;
          fVar41 = pfVar1[7] - fVar32;
          pfVar14[8] = fVar33;
          pfVar14[9] = fVar32;
          pfVar14[0x20] = fVar33;
          pfVar14[0x21] = fVar32;
          pfVar14[0x50] = fVar33;
          pfVar14[0x38] = fVar33;
          pfVar14[0x39] = fVar32;
          pfVar14[0x51] = fVar32;
          if (fVar34 <= 0.0) {
            fVar34 = 0.0;
          }
          if (fVar35 <= 0.0) {
            fVar35 = 0.0;
          }
          if (fVar36 <= 0.0) {
            fVar36 = 0.0;
          }
          if (fVar37 <= 0.0) {
            fVar37 = 0.0;
          }
          fVar32 = -fVar31;
          if (cVar8 == '\0') {
            fVar32 = fVar31;
          }
          fVar38 = fVar22 * fVar38;
          fVar33 = -(fVar23 * fVar39);
          fVar32 = fVar21 + fVar32;
          pfVar14[4] = fVar34;
          pfVar14[5] = fVar35;
          pfVar14[0x1c] = fVar34;
          pfVar14[0x1d] = fVar35;
          pfVar14[0x34] = fVar34;
          pfVar14[0x35] = fVar35;
          pfVar14[0x4c] = fVar34;
          pfVar14[0x4d] = fVar35;
          fVar31 = fVar24 * fVar22 * fVar40 * fVar19 * 0.5 * fVar42;
          fVar26 = fVar25 * fVar23 * fVar41 * fVar20 * 0.5 * fVar26;
          *pfVar14 = fStack_d0;
          pfVar14[1] = fStack_cc;
          pfVar14[2] = fStack_c8;
          pfVar14[3] = fStack_c4;
          pfVar14[0x11] = fVar7;
          pfVar14[0x12] = 0.0;
          pfVar14[0x13] = 0.0;
          pfVar14[0x14] = 0.0;
          pfVar14[0x18] = fStack_d0;
          pfVar14[0x19] = fStack_cc;
          pfVar14[0x1a] = fStack_c8;
          pfVar14[0x1b] = fStack_c4;
          pfVar14[0x29] = fVar7;
          pfVar14[0x2a] = 0.0;
          pfVar14[0x2b] = 0.0;
          pfVar14[0x2c] = 1.0;
          pfVar14[0x30] = fStack_d0;
          pfVar14[0x31] = fStack_cc;
          pfVar14[0x32] = fStack_c8;
          pfVar14[0x33] = fStack_c4;
          pfVar14[0x41] = fVar7;
          pfVar14[0x42] = 0.0;
          pfVar14[0x43] = 0.0;
          pfVar14[0x44] = 3.0;
          pfVar14[0x48] = fStack_d0;
          pfVar14[0x49] = fStack_cc;
          pfVar14[0x4a] = fStack_c8;
          pfVar14[0x4b] = fStack_c4;
          pfVar14[0x59] = fVar7;
          pfVar14[0x5a] = 0.0;
          pfVar14[0x5b] = 0.0;
          pfVar14[0x5c] = 2.0;
          pfVar14[10] = fVar40;
          pfVar14[0xb] = fVar41;
          pfVar14[0xc] = fVar38;
          pfVar14[0xd] = fVar33;
          pfVar14[0x22] = fVar40;
          pfVar14[0x23] = fVar41;
          pfVar14[0x24] = fVar38;
          pfVar14[0x25] = fVar33;
          pfVar14[0x3a] = fVar40;
          pfVar14[0x3b] = fVar41;
          pfVar14[0x3c] = fVar38;
          pfVar14[0x3d] = fVar33;
          pfVar14[0x52] = fVar40;
          pfVar14[0x53] = fVar41;
          pfVar14[0x54] = fVar38;
          pfVar14[0x55] = fVar33;
          pfVar14[6] = fVar36;
          pfVar14[7] = fVar37;
          pfVar14[0x1e] = fVar36;
          pfVar14[0x1f] = fVar37;
          pfVar14[0x36] = fVar36;
          pfVar14[0x37] = fVar37;
          pfVar14[0x4e] = fVar36;
          pfVar14[0x4f] = fVar37;
          pfVar14[0xf] = fVar26;
          pfVar14[0x10] = fVar32;
          pfVar14[0x27] = fVar26;
          pfVar14[0x28] = fVar32;
          pfVar14[0x3f] = fVar26;
          pfVar14[0x40] = fVar32;
          pfVar14[0x58] = fVar32;
          pfVar14[0xe] = fVar31;
          pfVar14[0x26] = fVar31;
          pfVar14[0x3e] = fVar31;
          pfVar14[0x56] = fVar31;
          pfVar14[0x57] = fVar26;
          *plVar12 = (long)(pfVar14 + 0x60);
          if (uVar16 == 0) break;
          uVar18 = (uint)*puVar17;
          plVar12 = plVar12 + 1;
          puVar17 = puVar17 + 1;
        }
      }
      uVar13 = uVar13 + 1;
    } while (uVar13 != param_5);
  }
  *(ulong *)(param_6 + 2) = CONCAT44(fStack_a4,fStack_a8);
  *(ulong *)param_6 = CONCAT44(fStack_ac,fStack_b0);
  *(ulong *)(param_7 + 2) = CONCAT44(fStack_b4,fStack_b8);
  *(ulong *)param_7 = CONCAT44(fStack_bc,fStack_c0);
  lVar11 = param_1 + (long)param_2 * 0x50 + (long)*(int *)(lVar10 + 0x30) * 4;
  *(uint *)(lVar11 + 0x3c) = *(int *)(lVar11 + 0x3c) + param_5 * uVar6 * 4;
  return;
}

// ==== Aska::ParticleRenderManager::FillPolyLine(int, Aska::ParticleFillContext const*, Aska::ParticleContext const*, int, Aska::Vector*, Aska::Vector*)
// vaddr 0x236c33c | ghidra 0x246c33c | size 744 | symbol _ZN4Aska21ParticleRenderManager12FillPolyLineEiPKNS_19ParticleFillContextEPKNS_15ParticleContextEiPNS_6VectorES8_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager12FillPolyLineEiPKNS_19ParticleFillContextEPKNS_15ParticleContextEiPNS_6VectorES8_
               (long param_1,int param_2,long param_3,float *param_4,uint param_5,float *param_6,
               float *param_7)

{
  ulong uVar1;
  float *pfVar2;
  float *pfVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  uint uVar8;
  undefined8 uVar9;
  long lVar10;
  int iVar11;
  ulong uVar12;
  long lVar13;
  undefined8 *puVar14;
  float *pfVar15;
  float *pfVar16;
  float *pfVar17;
  uint uVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fStack_110;
  float fStack_10c;
  float fStack_108;
  float fStack_104;
  int aiStack_100 [32];
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  
  lVar10 = param_1 + (long)param_2 * 0x50;
  uVar18 = (uint)*(ushort *)(param_3 + 0x1a);
  lVar13 = *(long *)(lVar10 + 0x48);
  fVar32 = *param_6;
  iVar11 = *(int *)(lVar10 + (long)*(int *)(lVar10 + 0x30) * 4 + 0x3c);
  fVar31 = param_6[1];
  fVar29 = param_6[2];
  fVar27 = param_6[3];
  fVar25 = *param_7;
  fVar23 = param_7[1];
  fVar21 = param_7[2];
  fVar20 = param_7[3];
  fStack_80 = fVar25;
  fStack_7c = fVar23;
  fStack_78 = fVar21;
  fStack_74 = fVar20;
  fStack_70 = fVar32;
  fStack_6c = fVar31;
  fStack_68 = fVar29;
  fStack_64 = fVar27;
  Aska::IParticleRenderManager::SetEdgeIndexConst(Aska::EdgeInfo*, unsigned int)(param_1,aiStack_100,uVar18);
  if (param_5 != 0) {
    fVar19 = *(float *)(param_3 + 0x14);
    uVar12 = 1;
    puVar14 = (undefined8 *)(lVar13 + (long)iVar11 * 0x60 + 0x60);
    pfVar15 = param_4;
    while( true ) {
      fStack_110 = *pfVar15;
      fStack_10c = pfVar15[1];
      uVar9 = *(undefined8 *)pfVar15;
      iVar11 = (int)uVar12;
      uVar8 = 0;
      if (uVar18 != 0) {
        uVar8 = (iVar11 - 1U) / uVar18;
      }
      fStack_108 = pfVar15[2];
      fStack_104 = pfVar15[0x10];
      uVar1 = (ulong)((iVar11 - 1U) - uVar8 * uVar18);
      pfVar17 = &fStack_70;
      if (fStack_110 <= fVar32) {
        pfVar17 = &fStack_110;
      }
      fVar32 = *pfVar17;
      pfVar17 = &fStack_70;
      if (fStack_10c <= fVar31) {
        pfVar17 = &fStack_110;
      }
      pfVar2 = &fStack_70;
      if (fStack_108 <= fVar29) {
        pfVar2 = &fStack_110;
      }
      fStack_70 = fVar32;
      pfVar3 = &fStack_70;
      if (fStack_104 <= fVar27) {
        pfVar3 = &fStack_110;
      }
      pfVar16 = param_4 + (ulong)((iVar11 + aiStack_100[uVar1 * 2]) - 1) * 0x14;
      fVar26 = *pfVar16;
      fVar28 = pfVar16[1];
      fVar30 = pfVar16[2];
      pfVar16 = &fStack_80;
      if (fVar25 <= fStack_110) {
        pfVar16 = &fStack_110;
      }
      fVar25 = *pfVar16;
      fVar31 = pfVar17[1];
      pfVar17 = param_4 + (ulong)((iVar11 + aiStack_100[uVar1 * 2 + 1]) - 1) * 0x14;
      fVar24 = *pfVar17;
      fVar33 = pfVar17[1];
      fVar34 = pfVar17[2];
      pfVar17 = &fStack_80;
      if (fVar23 <= fStack_10c) {
        pfVar17 = &fStack_110;
      }
      fStack_80 = fVar25;
      fStack_6c = fVar31;
      fVar23 = pfVar17[1];
      fVar29 = pfVar2[2];
      fVar4 = pfVar15[4];
      fVar6 = pfVar15[5];
      fStack_7c = fVar23;
      pfVar17 = &fStack_80;
      if (fVar21 <= fStack_108) {
        pfVar17 = &fStack_110;
      }
      fVar21 = pfVar17[2];
      fStack_68 = fVar29;
      fVar27 = pfVar3[3];
      pfVar17 = &fStack_80;
      if (fVar20 <= fStack_104) {
        pfVar17 = &fStack_110;
      }
      fStack_78 = fVar21;
      fVar20 = pfVar17[3];
      fStack_64 = fVar27;
      fVar5 = pfVar15[6];
      fVar7 = pfVar15[7];
      fVar22 = pfVar15[0x13];
      fStack_74 = fVar20;
      *(float *)(puVar14 + -10) = fVar4;
      *(float *)((long)puVar14 + -0x4c) = fVar6;
      *(float *)(puVar14 + -9) = fVar5;
      *(float *)((long)puVar14 + -0x44) = fVar7;
      fVar22 = fVar19 * -2.0 * fVar22;
      *(float *)(puVar14 + -0xc) = fStack_110;
      *(float *)((long)puVar14 + -0x5c) = fStack_10c;
      *(float *)(puVar14 + -0xb) = fStack_108;
      *(float *)(puVar14 + -8) = fVar26 - fVar24;
      *(float *)((long)puVar14 + -0x3c) = fVar28 - fVar33;
      *(float *)(puVar14 + -7) = fVar30 - fVar34;
      *(float *)((long)puVar14 + -0x34) = fVar22;
      *(undefined4 *)(puVar14 + -2) = 0;
      *(float *)(puVar14 + 2) = fVar4;
      *(float *)((long)puVar14 + 0x14) = fVar6;
      *(float *)(puVar14 + 3) = fVar5;
      *(float *)((long)puVar14 + 0x1c) = fVar7;
      *(float *)((long)puVar14 + -0x54) = fStack_104;
      *(float *)(puVar14 + 4) = fVar26 - fVar24;
      *(float *)((long)puVar14 + 0x24) = fVar28 - fVar33;
      *(float *)(puVar14 + 5) = fVar30 - fVar34;
      *(float *)((long)puVar14 + 0x2c) = fVar22;
      *(undefined4 *)(puVar14 + 10) = 0x3f800000;
      puVar14[1] = CONCAT44(fStack_104,fStack_108);
      *puVar14 = uVar9;
      if (param_5 == uVar12) break;
      uVar18 = (uint)*(ushort *)(param_3 + 0x1a);
      puVar14 = puVar14 + 0x18;
      pfVar15 = pfVar15 + 0x14;
      uVar12 = uVar12 + 1;
    }
  }
  *(ulong *)(param_6 + 2) = CONCAT44(fStack_64,fStack_68);
  *(ulong *)param_6 = CONCAT44(fStack_6c,fStack_70);
  *(ulong *)(param_7 + 2) = CONCAT44(fStack_74,fStack_78);
  *(ulong *)param_7 = CONCAT44(fStack_7c,fStack_80);
  lVar10 = param_1 + (long)param_2 * 0x50 + (long)*(int *)(lVar10 + 0x30) * 4;
  *(uint *)(lVar10 + 0x3c) = *(int *)(lVar10 + 0x3c) + param_5 * 2;
  return;
}

// ==== Aska::ParticleRenderManager::FillSpriteLine(int, Aska::ParticleFillContext const*, Aska::ParticleContext const*, int, Aska::Vector*, Aska::Vector*)
// vaddr 0x236c624 | ghidra 0x246c624 | size 1352 | symbol _ZN4Aska21ParticleRenderManager14FillSpriteLineEiPKNS_19ParticleFillContextEPKNS_15ParticleContextEiPNS_6VectorES8_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager14FillSpriteLineEiPKNS_19ParticleFillContextEPKNS_15ParticleContextEiPNS_6VectorES8_
               (long param_1,int param_2,long *param_3,long param_4,uint param_5,float *param_6,
               float *param_7)

{
  long lVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  float fVar5;
  uint uVar6;
  uint uVar7;
  float fVar8;
  float fVar9;
  long lVar10;
  long lVar11;
  float *pfVar12;
  float *pfVar13;
  long *plVar14;
  ulong uVar15;
  ulong uVar16;
  long lVar17;
  float *pfVar18;
  ulong uVar19;
  float *pfVar20;
  ushort *puVar21;
  uint uVar22;
  uint uVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fStack_180;
  float fStack_17c;
  float fStack_178;
  float fStack_174;
  float fStack_170;
  float fStack_16c;
  float fStack_168;
  float fStack_164;
  float fStack_160;
  float fStack_15c;
  float fStack_158;
  float fStack_154;
  int aiStack_148 [32];
  undefined2 uStack_c8;
  undefined2 uStack_c6;
  undefined2 uStack_c4;
  undefined2 uStack_c2;
  long alStack_c0 [4];
  
  lVar10 = param_1 + (long)param_2 * 0x50;
  uVar6 = *(uint *)(param_3 + 8);
  uVar16 = (ulong)uVar6;
  lVar11 = *(long *)(lVar10 + 0x48) +
           (long)*(int *)(lVar10 + (long)*(int *)(lVar10 + 0x30) * 4 + 0x3c) * 0x60;
  if (*(char *)((long)param_3 + 0x44) == '\0') {
    if (0 < (int)uVar6) {
      plVar14 = alStack_c0;
      uVar15 = uVar16;
      do {
        *plVar14 = lVar11;
        uVar15 = uVar15 - 1;
        lVar11 = lVar11 + (long)(int)(param_5 << 1) * 0x60;
        plVar14 = plVar14 + 1;
      } while (uVar15 != 0);
    }
  }
  else if (0 < (int)uVar6) {
    uVar15 = uVar16;
    do {
      uVar15 = uVar15 - 1;
      alStack_c0[(int)uVar15] = lVar11;
      lVar11 = lVar11 + (long)(int)(param_5 << 1) * 0x60;
    } while (uVar15 != 0);
  }
  uVar22 = (uint)*(ushort *)((long)param_3 + 0x1a);
  Aska::IParticleRenderManager::SetEdgeIndexConstSpriteLine(Aska::EdgeInfo*, unsigned int)(param_1,aiStack_148,uVar22);
  fStack_160 = *param_6;
  fStack_15c = param_6[1];
  fVar32 = *(float *)((long)param_3 + 0x14);
  fStack_158 = param_6[2];
  fStack_154 = param_6[3];
  fStack_170 = *param_7;
  fStack_16c = param_7[1];
  fStack_168 = param_7[2];
  fStack_164 = param_7[3];
  if (param_5 != 0) {
    uVar15 = 0;
    while( true ) {
      pfVar12 = (float *)(param_4 + uVar15 * 0x50);
      fStack_180 = *pfVar12;
      fStack_17c = pfVar12[1];
      fStack_178 = pfVar12[2];
      fStack_174 = pfVar12[0x10];
      pfVar18 = &fStack_160;
      if (fStack_180 <= fStack_160) {
        pfVar18 = &fStack_180;
      }
      uVar7 = 0;
      uVar23 = (uint)uVar15;
      if (uVar22 != 0) {
        uVar7 = uVar23 / uVar22;
      }
      pfVar4 = &fStack_160;
      if (fStack_17c <= fStack_15c) {
        pfVar4 = &fStack_180;
      }
      uVar7 = uVar7 * uVar22;
      pfVar2 = &fStack_160;
      if (fStack_178 <= fStack_158) {
        pfVar2 = &fStack_180;
      }
      pfVar20 = (float *)(param_4 + (ulong)uVar7 * 0x50);
      pfVar3 = &fStack_160;
      if (fStack_174 <= fStack_154) {
        pfVar3 = &fStack_180;
      }
      fVar33 = *pfVar20;
      fVar35 = pfVar20[1];
      fVar37 = pfVar20[2];
      pfVar20 = &fStack_170;
      if (fStack_170 <= fStack_180) {
        pfVar20 = &fStack_180;
      }
      pfVar13 = (float *)(param_4 + (ulong)((uVar22 + uVar7) - 1) * 0x50);
      fStack_160 = *pfVar18;
      pfVar18 = &fStack_170;
      if (fStack_16c <= fStack_17c) {
        pfVar18 = &fStack_180;
      }
      fVar28 = *pfVar13 - fVar33;
      fVar30 = pfVar13[1] - fVar35;
      fStack_170 = *pfVar20;
      fStack_16c = pfVar18[1];
      pfVar18 = &fStack_170;
      if (fStack_168 <= fStack_178) {
        pfVar18 = &fStack_180;
      }
      fVar5 = pfVar12[0xd];
      fVar31 = pfVar13[2] - fVar37;
      fStack_15c = pfVar4[1];
      fStack_158 = pfVar2[2];
      pfVar4 = &fStack_170;
      if (fStack_164 <= fStack_174) {
        pfVar4 = &fStack_180;
      }
      fStack_168 = pfVar18[2];
      fVar29 = fVar28 * fVar28 + fVar30 * fVar30 + fVar31 * fVar31;
      fVar24 = SQRT(fVar29);
      uStack_c6 = SUB42(fVar5,0);
      uVar22 = (uint)fVar5 >> 0x10;
      uStack_c8 = (short)((uint)fVar5 >> 0x10);
      uStack_c2 = SUB42(pfVar12[0xc],0);
      fStack_154 = pfVar3[3];
      fStack_164 = pfVar4[3];
      uStack_c4 = (short)((uint)pfVar12[0xc] >> 0x10);
      if (NAN(fVar24)) {
        fVar24 = (float)sqrtf(fVar29);
      }
      fVar9 = fStack_178;
      fVar8 = fStack_17c;
      fVar5 = fStack_180;
      fVar33 = (1.0 / fVar29) *
               (fVar28 * (fStack_180 - fVar33) + fVar30 * (fStack_17c - fVar35) +
               fVar31 * (fStack_178 - fVar37));
      fVar35 = fVar31 * fVar33 * fVar31 * fVar33 +
               fVar28 * fVar33 * fVar28 * fVar33 + fVar30 * fVar33 * fVar30 * fVar33;
      fVar33 = SQRT(fVar35);
      if (NAN(fVar33)) {
        fVar33 = (float)sqrtf(fVar35);
      }
      if (0 < (int)uVar6) {
        fVar33 = (1.0 / fVar24) * fVar33;
        pfVar18 = (float *)(param_4 +
                           (ulong)(aiStack_148[(ulong)(uVar23 - uVar7) * 2] + uVar23) * 0x50);
        pfVar12 = (float *)(param_4 +
                           (ulong)(aiStack_148[(ulong)(uVar23 - uVar7) * 2 + 1] + uVar23) * 0x50);
        fVar35 = *pfVar12;
        fVar24 = pfVar12[1];
        fVar28 = *pfVar18;
        fVar30 = pfVar18[1];
        fVar31 = pfVar18[2];
        fVar29 = pfVar12[2];
        lVar11 = *param_3;
        lVar17 = param_4 + uVar15 * 0x50;
        fVar37 = fVar32 * -2.0 * *(float *)(param_4 + uVar15 * 0x50 + 0x28);
        plVar14 = alStack_c0;
        puVar21 = (ushort *)((ulong)&uStack_c8 | 2);
        uVar19 = uVar16;
        while( true ) {
          uVar19 = uVar19 - 1;
          lVar1 = lVar11 + (ulong)uVar22 * 0x40;
          pfVar18 = (float *)*plVar14;
          fVar25 = *(float *)(lVar17 + 0x10) * *(float *)(lVar1 + 0x20);
          fVar26 = *(float *)(lVar17 + 0x14) * *(float *)(lVar1 + 0x24);
          fVar36 = *(float *)(lVar1 + 0x10);
          fVar38 = *(float *)(lVar1 + 0x14);
          fVar27 = *(float *)(lVar17 + 0x18) * *(float *)(lVar1 + 0x28);
          fVar34 = *(float *)(lVar17 + 0x1c) * *(float *)(lVar1 + 0x2c);
          if (fVar25 <= 0.0) {
            fVar25 = 0.0;
          }
          if (fVar26 <= 0.0) {
            fVar26 = 0.0;
          }
          if (fVar27 <= 0.0) {
            fVar27 = 0.0;
          }
          fVar39 = *(float *)(lVar1 + 0x18) - fVar36;
          fVar40 = *(float *)(lVar1 + 0x1c) - fVar38;
          if (fVar34 <= 0.0) {
            fVar34 = 0.0;
          }
          *pfVar18 = fVar5;
          pfVar18[1] = fVar8;
          pfVar18[2] = fVar9;
          pfVar18[3] = fStack_174;
          pfVar18[0xc] = fVar28 - fVar35;
          pfVar18[0xd] = fVar30 - fVar24;
          pfVar18[0xe] = fVar31 - fVar29;
          pfVar18[0xf] = fVar37;
          *(ulong *)(pfVar18 + 0x12) = CONCAT44(fVar33,fVar33);
          *(ulong *)(pfVar18 + 0x10) = CONCAT44(fVar33,fVar33);
          pfVar18[0x14] = 0.0;
          pfVar18[0x18] = fVar5;
          pfVar18[0x19] = fVar8;
          pfVar18[0x1a] = fVar9;
          pfVar18[0x1b] = fStack_174;
          pfVar18[0x24] = fVar28 - fVar35;
          pfVar18[0x25] = fVar30 - fVar24;
          pfVar18[0x26] = fVar31 - fVar29;
          pfVar18[0x27] = fVar37;
          *(ulong *)(pfVar18 + 0x2a) = CONCAT44(fVar33,fVar33);
          *(ulong *)(pfVar18 + 0x28) = CONCAT44(fVar33,fVar33);
          pfVar18[0x2c] = 1.0;
          pfVar18[8] = fVar36;
          pfVar18[9] = fVar38;
          pfVar18[0x20] = fVar36;
          pfVar18[0x21] = fVar38;
          pfVar18[10] = fVar39;
          pfVar18[0xb] = fVar40;
          pfVar18[0x22] = fVar39;
          pfVar18[0x23] = fVar40;
          pfVar18[4] = fVar25;
          pfVar18[5] = fVar26;
          pfVar18[6] = fVar27;
          pfVar18[7] = fVar34;
          pfVar18[0x1c] = fVar25;
          pfVar18[0x1d] = fVar26;
          pfVar18[0x1e] = fVar27;
          pfVar18[0x1f] = fVar34;
          *plVar14 = (long)(pfVar18 + 0x30);
          if (uVar19 == 0) break;
          uVar22 = (uint)*puVar21;
          plVar14 = plVar14 + 1;
          puVar21 = puVar21 + 1;
        }
      }
      uVar15 = uVar15 + 1;
      if (uVar15 == param_5) break;
      uVar22 = (uint)*(ushort *)((long)param_3 + 0x1a);
    }
  }
  *(ulong *)(param_6 + 2) = CONCAT44(fStack_154,fStack_158);
  *(ulong *)param_6 = CONCAT44(fStack_15c,fStack_160);
  *(ulong *)(param_7 + 2) = CONCAT44(fStack_164,fStack_168);
  *(ulong *)param_7 = CONCAT44(fStack_16c,fStack_170);
  lVar11 = param_1 + (long)param_2 * 0x50 + (long)*(int *)(lVar10 + 0x30) * 4;
  *(uint *)(lVar11 + 0x3c) = *(int *)(lVar11 + 0x3c) + param_5 * uVar6 * 2;
  return;
}

// ==== Aska::ParticleRenderManager::ResetDefaultValue()
// vaddr 0x236cb6c | ghidra 0x246cb6c | size 76 | symbol _ZN4Aska21ParticleRenderManager17ResetDefaultValueEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager17ResetDefaultValueEv(void)

{
  undefined8 uVar1;
  
  uVar1 = *(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  Aska::RenderDeviceGL::SetTexture(unsigned int, Aska::GpuResource* const*)(uVar1,0,0);
  Aska::RenderDeviceGL::SetTexture(unsigned int, Aska::GpuResource* const*)(uVar1,1,0);
  Aska::RenderDeviceGL::SetTexture(unsigned int, Aska::GpuResource* const*)(uVar1,2,0);
  (*(code *)PTR__ZN4Aska11RenderState25RestoreDefaultRenderStateEPNS_14RenderDeviceGLE_02ca5f10)
            (uVar1);
  return;
}

// ==== Aska::ParticleRenderManager::FlipSync(int, int)
// vaddr 0x236cbb8 | ghidra 0x246cbb8 | size 188 | symbol _ZN4Aska21ParticleRenderManager8FlipSyncEii | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21ParticleRenderManager8FlipSyncEii(long param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  long lVar5;
  uint uVar6;
  
  param_1 = param_1 + (long)param_2 * 0x50;
  lVar4 = param_1 + 8;
  Aska::PrimitiveBuffer::Sync(unsigned int, unsigned int)(lVar4,*(undefined4 *)(lVar4 + (long)param_3 * 4 + 0x34),0);
  lVar4 = *(long *)(param_1 + 0x18);
  if (*(long *)(lVar4 + 0x28) != 0) {
    *(long *)(*(long *)(lVar4 + 8) + 0x60) =
         ((long *)(lVar4 + 8))[(ulong)*(byte *)(lVar4 + 0x44) + 3];
    if (*(char *)(lVar4 + 0x48) != '\0') {
      lVar5 = *(long *)(lVar4 + 8);
      if (*(int *)(lVar4 + 0x3c) == 0) {
        *(undefined4 *)(lVar5 + 0x68) = *(undefined4 *)(lVar5 + 0x50);
        *(undefined4 *)(lVar5 + 0x6c) = 0;
      }
      else {
        uVar3 = *(uint *)(lVar4 + 0x40);
        if (*(int *)(lVar5 + 0x68) == 0) {
          *(int *)(lVar5 + 0x68) = *(int *)(lVar4 + 0x3c);
          *(uint *)(lVar5 + 0x6c) = uVar3;
        }
        else {
          uVar6 = *(uint *)(lVar5 + 0x6c);
          uVar1 = uVar6 + *(int *)(lVar5 + 0x68);
          uVar2 = uVar1 + uVar3;
          if (uVar1 + uVar3 <= uVar1) {
            uVar2 = uVar1;
          }
          if (uVar3 < uVar6) {
            *(uint *)(lVar5 + 0x6c) = uVar3;
            uVar6 = uVar3;
          }
          *(uint *)(lVar5 + 0x68) = uVar2 - uVar6;
        }
      }
      *(undefined1 *)(lVar4 + 0x48) = 0;
    }
    *(byte *)(lVar4 + 0x44) = *(byte *)(lVar4 + 0x44) ^ 1;
  }
  return;
}


// FAILED to create function at 02c65dd8 Aska::ParticleRenderManager::vtable
// FAILED to create function at 02c65ec0 Aska::ParticleRenderManager::typeinfo
