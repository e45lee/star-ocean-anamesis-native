// port/decomp/render/material.c: Ghidra decompiles for the render subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:45 UTC: tools/decomp.sh '--into' 'render/material' 'Aska::MaterialList::' 'Aska::MaterialContext::' 'Aska::ShaderConstantManager::' 'Aska::ShaderConstantHandler::' 'Aska::UniformValueBuffer2::' 'Aska::AhslConst::'

// ==== Aska::ShaderConstantManager::~ShaderConstantManager()
// vaddr 0x20bce30 | ghidra 0x21bce30 | size 316 | symbol _ZN4Aska21ShaderConstantManagerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska21ShaderConstantManagerD2Ev(undefined8 *param_1)

{
  uint uVar1;
  uint uVar2;
  long *plVar3;
  byte bVar4;
  uint uVar5;
  uint uVar6;
  ulong uVar7;
  long *plVar8;
  long lVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  long lVar13;
  ulong uVar14;
  
  if ((long *)*param_1 != (long *)0x0) {
    lVar9 = *(long *)PTR__ZN4Aska6Global27m_pShaderConstantBufferPoolE_02cc0a58;
    plVar8 = (long *)*param_1;
    do {
      plVar3 = (long *)*plVar8;
      if ((plVar8[1] != 0) && (-1 < (short)plVar8[2])) {
        bVar4 = *(byte *)((long)plVar8 + 0x12);
        iVar11 = (int)((ulong)(plVar8[1] - *(long *)(lVar9 + 0x30)) >> 4);
        iVar12 = iVar11 + 0x3f;
        if (-1 < iVar11) {
          iVar12 = iVar11;
        }
        uVar10 = (uint)bVar4;
        if (bVar4 != 0) {
          uVar1 = iVar12 >> 6;
          uVar14 = 0xffffffffffffffff >> ((ulong)(0x40 - bVar4) & 0x3f);
          uVar7 = -(ulong)(uVar1 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar1 << 3;
          uVar5 = iVar11 + uVar1 * -0x40;
          if (0x3f < uVar10) {
            uVar14 = 0xffffffffffffffff;
          }
          uVar2 = 0;
          if (uVar10 < 0x40) {
            uVar2 = uVar10;
          }
          uVar6 = 0x40 - uVar5;
          if ((int)uVar2 <= (int)uVar6) {
            uVar6 = uVar2;
          }
          iVar12 = uVar10 - uVar6;
          *(ulong *)(*(long *)(lVar9 + 0x18) + uVar7) =
               *(ulong *)(*(long *)(lVar9 + 0x18) + uVar7) &
               (uVar14 << ((ulong)uVar5 & 0x3f) ^ 0xffffffffffffffff);
          if (iVar12 != 0) {
            lVar13 = (long)(int)uVar1 * 8;
            do {
              lVar13 = lVar13 + 8;
              iVar11 = 0x40;
              if (iVar12 < 0x40) {
                iVar11 = iVar12;
              }
              uVar14 = 0;
              if (iVar12 < 0x40) {
                uVar14 = ~(0xffffffffffffffffU >> ((ulong)(0x40 - iVar12) & 0x3f));
              }
              if (0x3f < iVar11) {
                iVar11 = 0x40;
              }
              iVar12 = iVar12 - iVar11;
              *(ulong *)(*(long *)(lVar9 + 0x18) + lVar13) =
                   uVar14 & *(ulong *)(*(long *)(lVar9 + 0x18) + lVar13);
            } while (iVar12 != 0);
          }
        }
        *(uint *)(lVar9 + 0x3c) = *(int *)(lVar9 + 0x3c) - uVar10;
      }
      plVar8[1] = 0;
      uVar14 = ((long)plVar8 - *(long *)(lVar9 + 0x78) >> 3) * -0x5555555555555555;
      lVar13 = (uVar14 >> 6 & 0x3ffffff) * 8;
      *(ulong *)(*(long *)(lVar9 + 0x60) + lVar13) =
           *(ulong *)(*(long *)(lVar9 + 0x60) + lVar13) &
           (1L << (uVar14 & 0x3f) ^ 0xffffffffffffffffU);
      *(int *)(lVar9 + 0x84) = *(int *)(lVar9 + 0x84) + -1;
      plVar8 = plVar3;
    } while (plVar3 != (long *)0x0);
  }
  return;
}

// ==== Aska::ShaderConstantManager::IsRGBZero(int, int) const
// vaddr 0x20bcf6c | ghidra 0x21bcf6c | size 204 | symbol _ZNK4Aska21ShaderConstantManager9IsRGBZeroEii | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZNK4Aska21ShaderConstantManager9IsRGBZeroEii(long *param_1,uint param_2,uint param_3)

{
  long *plVar1;
  long *plVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  
  plVar1 = (long *)*param_1;
  while( true ) {
    if (plVar1 == (long *)0x0) {
      plVar2 = (long *)param_1[1];
      if (plVar2 == (long *)0x0) {
        return false;
      }
      do {
        for (plVar1 = (long *)*plVar2; plVar1 != (long *)0x0; plVar1 = (long *)*plVar1) {
          if (((*(ushort *)(plVar1 + 2) & 0x7fff) == param_2) &&
             ((*(byte *)((long)plVar1 + 0x13) & 0xf) == param_3)) goto code_r0x021bcfe4;
        }
        plVar2 = (long *)plVar2[1];
        if (plVar2 == (long *)0x0) {
          return false;
        }
      } while( true );
    }
    if (((*(ushort *)(plVar1 + 2) & 0x7fff) == param_2) &&
       ((*(byte *)((long)plVar1 + 0x13) & 0xf) == param_3)) break;
    plVar1 = (long *)*plVar1;
  }
code_r0x021bcfe4:
  if (*(char *)((long)plVar1 + 0x12) == '\0') {
    return false;
  }
  uVar4 = (*(undefined8 **)((long)plVar1 + 8))[1];
  uVar3 = **(undefined8 **)((long)plVar1 + 8);
  return ((ABS((float)uVar3) <= (float)_UNK_029c6420 &&
          ABS((float)((ulong)uVar3 >> 0x20)) <= (float)((ulong)_UNK_029c6420 >> 0x20)) &&
         ABS((float)uVar4) <= (float)_UNK_029c6428) &&
         ABS((float)((ulong)uVar4 >> 0x20)) <= (float)((ulong)_UNK_029c6428 >> 0x20);
}

// ==== Aska::ShaderConstantManager::SearchShaderConstantF(int, int, Aska::Vector**) const
// vaddr 0x20bd038 | ghidra 0x21bd038 | size 144 | symbol _ZNK4Aska21ShaderConstantManager21SearchShaderConstantFEiiPPNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
undefined1
_ZNK4Aska21ShaderConstantManager21SearchShaderConstantFEiiPPNS_6VectorE
          (long *param_1,uint param_2,uint param_3,undefined8 *param_4)

{
  long *plVar1;
  long *plVar2;
  
  plVar1 = (long *)*param_1;
  while( true ) {
    if (plVar1 == (long *)0x0) {
      plVar2 = (long *)param_1[1];
      if (plVar2 == (long *)0x0) {
        return 0;
      }
      do {
        for (plVar1 = (long *)*plVar2; plVar1 != (long *)0x0; plVar1 = (long *)*plVar1) {
          if (((*(ushort *)(plVar1 + 2) & 0x7fff) == param_2) &&
             ((*(byte *)((long)plVar1 + 0x13) & 0xf) == param_3)) goto code_r0x021bd0b0;
        }
        plVar2 = (long *)plVar2[1];
        if (plVar2 == (long *)0x0) {
          return 0;
        }
      } while( true );
    }
    if (((*(ushort *)(plVar1 + 2) & 0x7fff) == param_2) &&
       ((*(byte *)((long)plVar1 + 0x13) & 0xf) == param_3)) break;
    plVar1 = (long *)*plVar1;
  }
code_r0x021bd0b0:
  *param_4 = *(undefined8 *)((long)plVar1 + 8);
  return *(undefined1 *)((long)plVar1 + 0x12);
}

// ==== Aska::ShaderConstantManager::GetConstImmState(int, int) const
// vaddr 0x20bd0c8 | ghidra 0x21bd0c8 | size 400 | symbol _ZNK4Aska21ShaderConstantManager16GetConstImmStateEii | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int _ZNK4Aska21ShaderConstantManager16GetConstImmStateEii(long *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  long *plVar2;
  long *plVar3;
  float fVar4;
  undefined8 uVar5;
  float fVar6;
  float fVar7;
  undefined8 uVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined1 auVar16 [16];
  
  if (*(char *)param_1[2] == '\0') {
    return 0;
  }
  plVar2 = (long *)*param_1;
  while( true ) {
    if (plVar2 == (long *)0x0) {
      plVar3 = (long *)param_1[1];
      if (plVar3 == (long *)0x0) {
        return 0;
      }
      do {
        for (plVar2 = (long *)*plVar3; plVar2 != (long *)0x0; plVar2 = (long *)*plVar2) {
          if (((*(ushort *)(plVar2 + 2) & 0x7fff) == param_2) &&
             ((*(byte *)((long)plVar2 + 0x13) & 0xf) == param_3)) goto code_r0x021bd14c;
        }
        plVar3 = (long *)plVar3[1];
        if (plVar3 == (long *)0x0) {
          return 0;
        }
      } while( true );
    }
    if (((*(ushort *)(plVar2 + 2) & 0x7fff) == param_2) &&
       ((*(byte *)((long)plVar2 + 0x13) & 0xf) == param_3)) break;
    plVar2 = (long *)*plVar2;
  }
code_r0x021bd14c:
  if (*(char *)((long)plVar2 + 0x12) == '\0') {
    return 0;
  }
  auVar16 = NEON_fmov(0xbf800000,4);
  uVar8 = (*(undefined8 **)((long)plVar2 + 8))[1];
  uVar5 = **(undefined8 **)((long)plVar2 + 8);
  fVar4 = (float)uVar5;
  fVar10 = ABS(fVar4);
  fVar6 = (float)((ulong)uVar5 >> 0x20);
  fVar11 = ABS(fVar6);
  fVar7 = (float)uVar8;
  fVar12 = ABS(fVar7);
  fVar9 = (float)((ulong)uVar8 >> 0x20);
  fVar13 = ABS(fVar9);
  fVar14 = (float)((ulong)_UNK_029c6420 >> 0x20);
  fVar15 = (float)((ulong)_UNK_029c6428 >> 0x20);
  fVar4 = fVar4 + auVar16._0_4_;
  fVar6 = fVar6 + auVar16._4_4_;
  fVar7 = fVar7 + auVar16._8_4_;
  fVar9 = fVar9 + auVar16._12_4_;
  if (fVar15 < fVar13 ||
      ((float)_UNK_029c6428 < fVar12 || ((float)_UNK_029c6420 < fVar10 || fVar14 < fVar11))) {
    if ((((float)_UNK_029c6420 < ABS(fVar4) || fVar14 < ABS(fVar6)) ||
        (float)_UNK_029c6428 < ABS(fVar7)) || fVar15 < ABS(fVar9)) {
      return 0;
    }
    uVar1 = 2;
  }
  else {
    uVar1 = 0;
  }
  fVar14 = (float)((ulong)_UNK_029c6430 >> 0x20);
  fVar15 = (float)((ulong)_UNK_029c6438 >> 0x20);
  if (((float)_UNK_029c6438 < fVar12 || ((float)_UNK_029c6430 < fVar10 || fVar14 < fVar11)) ||
      fVar15 < fVar13) {
    if ((((float)_UNK_029c6430 < ABS(fVar4) || fVar14 < ABS(fVar6)) ||
        (float)_UNK_029c6438 < ABS(fVar7)) || fVar15 < ABS(fVar9)) {
      return 0;
    }
    return (uVar1 | 1) + 1;
  }
  return uVar1 + 1;
}

// ==== Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)
// vaddr 0x20bd258 | ghidra 0x21bd258 | size 632 | symbol _ZN4Aska21ShaderConstantManager20SetShaderConstantFUCEiiPKNS_6VectorEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska21ShaderConstantManager20SetShaderConstantFUCEiiPKNS_6VectorEi
          (long *param_1,uint param_2,uint param_3,long param_4,uint param_5)

{
  ulong *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined8 *puVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  long *plVar10;
  long lVar11;
  ulong uVar12;
  long lVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  
  for (plVar10 = (long *)*param_1; plVar10 != (long *)0x0; plVar10 = (long *)*plVar10) {
    if (((*(ushort *)(plVar10 + 2) & 0x7fff) == param_2) &&
       ((*(byte *)((long)plVar10 + 0x13) & 0xf) == param_3)) {
      if ((int)param_5 < 1) {
        return 0;
      }
      lVar13 = plVar10[1];
      lVar11 = 0;
      while (puVar5 = (undefined8 *)(param_4 + lVar11 * 0x10), uVar15 = puVar5[1], uVar14 = *puVar5,
            puVar5 = (undefined8 *)(lVar13 + lVar11 * 0x10), uVar17 = puVar5[1], uVar16 = *puVar5,
            (float)((ulong)uVar15 >> 0x20) == (float)((ulong)uVar17 >> 0x20) &&
            ((float)uVar15 == (float)uVar17 &&
            ((float)uVar14 == (float)uVar16 &&
            (float)((ulong)uVar14 >> 0x20) == (float)((ulong)uVar16 >> 0x20)))) {
        lVar11 = lVar11 + 1;
        if ((int)param_5 <= (int)lVar11) {
          return 0;
        }
      }
      if ((short)*(ushort *)(plVar10 + 2) < 0) {
        lVar13 = Aska::TPoolFast<Aska::Vector, false>::Scoop(int)(*(undefined8 *)
                                  PTR__ZN4Aska6Global27m_pShaderConstantBufferPoolE_02cc0a58,param_5
                                );
        if (lVar13 == 0) {
          return 0;
        }
        plVar10[1] = lVar13;
        *(ushort *)(plVar10 + 2) = *(ushort *)(plVar10 + 2) & 0x7fff;
      }
      memcpy(lVar13,param_4,(ulong)*(byte *)((long)plVar10 + 0x12) << 4);
      *(byte *)((long)plVar10 + 0x13) = *(byte *)((long)plVar10 + 0x13) | 0x80;
      goto code_r0x021bd49c;
    }
  }
  lVar11 = *(long *)PTR__ZN4Aska6Global27m_pShaderConstantBufferPoolE_02cc0a58;
  uVar2 = *(uint *)(lVar11 + 0x6c);
  if (*(uint *)(lVar11 + 0x84) < uVar2) {
    uVar3 = *(uint *)(lVar11 + 0x80);
    uVar12 = (ulong)uVar3;
    *(uint *)(lVar11 + 0x84) = *(uint *)(lVar11 + 0x84) + 1;
    puVar1 = (ulong *)(*(long *)(lVar11 + 0x60) + (ulong)(uVar3 >> 6) * 8);
    uVar7 = *puVar1;
    uVar8 = 1L << (uVar12 & 0x3f);
    uVar9 = uVar8 & uVar7;
    while (uVar9 != 0) {
      uVar3 = (int)uVar12 + 1;
      uVar4 = 0;
      if (uVar2 != 0) {
        uVar4 = uVar3 / uVar2;
      }
      uVar3 = uVar3 - uVar4 * uVar2;
      uVar12 = (ulong)uVar3;
      puVar1 = (ulong *)(*(long *)(lVar11 + 0x60) + (ulong)(uVar3 >> 6) * 8);
      uVar7 = *puVar1;
      uVar8 = 1L << (uVar3 & 0x3f);
      uVar9 = uVar8 & uVar7;
    }
    *puVar1 = uVar8 | uVar7;
    lVar13 = *(long *)(lVar11 + 0x78);
    uVar4 = 0;
    if (uVar2 != 0) {
      uVar4 = (uVar3 + 1) / uVar2;
    }
    plVar10 = (long *)(lVar13 + (ulong)uVar3 * 0x18);
    *(uint *)(lVar11 + 0x80) = (uVar3 + 1) - uVar4 * uVar2;
    if (plVar10 != (long *)0x0) {
      lVar6 = Aska::TPoolFast<Aska::Vector, false>::Scoop(int)(lVar11,(ulong)param_5);
      if (lVar6 == 0) {
        uVar12 = ((long)plVar10 - *(long *)(lVar11 + 0x78) >> 3) * -0x5555555555555555;
        lVar13 = (uVar12 >> 6 & 0x3ffffff) * 8;
        *(ulong *)(*(long *)(lVar11 + 0x60) + lVar13) =
             *(ulong *)(*(long *)(lVar11 + 0x60) + lVar13) &
             (1L << (uVar12 & 0x3f) ^ 0xffffffffffffffffU);
        *(int *)(lVar11 + 0x84) = *(int *)(lVar11 + 0x84) + -1;
        return 0;
      }
      lVar13 = lVar13 + (ulong)uVar3 * 0x18;
      *(long *)(lVar13 + 8) = lVar6;
      *(char *)(lVar13 + 0x12) = (char)param_5;
      *(byte *)(lVar13 + 0x13) = *(byte *)(lVar13 + 0x13) | 0x80;
      *plVar10 = *param_1;
      *(ushort *)(lVar13 + 0x10) = (ushort)param_2 & 0x7fff;
      *(byte *)(lVar13 + 0x13) = (byte)param_3 & 0xf | 0x80;
      *param_1 = (long)plVar10;
      memcpy(lVar6,param_4,
                      -(ulong)(param_5 >> 0x1f) & 0xfffffff000000000 | (ulong)param_5 << 4);
code_r0x021bd49c:
      *(short *)((long)param_1 + 0x1a) = *(short *)((long)param_1 + 0x1a) + 1;
      *(byte *)((long)param_1 + 0x1c) = *(byte *)((long)param_1 + 0x1c) | 1;
      return 1;
    }
  }
  return 0;
}

// ==== Aska::ShaderConstantManager::SetShaderConstantRefF(int, int, Aska::Vector const*, int)
// vaddr 0x20bd4d0 | ghidra 0x21bd4d0 | size 260 | symbol _ZN4Aska21ShaderConstantManager21SetShaderConstantRefFEiiPKNS_6VectorEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska21ShaderConstantManager21SetShaderConstantRefFEiiPKNS_6VectorEi
          (long *param_1,ushort param_2,byte param_3,undefined8 param_4,undefined1 param_5)

{
  ulong *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  long lVar5;
  long *plVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  lVar5 = *(long *)PTR__ZN4Aska6Global27m_pShaderConstantBufferPoolE_02cc0a58;
  uVar2 = *(uint *)(lVar5 + 0x6c);
  if (uVar2 <= *(uint *)(lVar5 + 0x84)) {
    return 0;
  }
  uVar3 = *(uint *)(lVar5 + 0x80);
  uVar7 = (ulong)uVar3;
  *(uint *)(lVar5 + 0x84) = *(uint *)(lVar5 + 0x84) + 1;
  puVar1 = (ulong *)(*(long *)(lVar5 + 0x60) + (ulong)(uVar3 >> 6) * 8);
  uVar8 = *puVar1;
  uVar9 = 1L << (uVar7 & 0x3f);
  uVar10 = uVar9 & uVar8;
  while (uVar10 != 0) {
    uVar3 = (int)uVar7 + 1;
    uVar4 = 0;
    if (uVar2 != 0) {
      uVar4 = uVar3 / uVar2;
    }
    uVar3 = uVar3 - uVar4 * uVar2;
    uVar7 = (ulong)uVar3;
    puVar1 = (ulong *)(*(long *)(lVar5 + 0x60) + (ulong)(uVar3 >> 6) * 8);
    uVar8 = *puVar1;
    uVar9 = 1L << (uVar3 & 0x3f);
    uVar10 = uVar9 & uVar8;
  }
  *puVar1 = uVar9 | uVar8;
  uVar4 = 0;
  if (uVar2 != 0) {
    uVar4 = (uVar3 + 1) / uVar2;
  }
  plVar6 = (long *)(*(long *)(lVar5 + 0x78) + (ulong)uVar3 * 0x18);
  *(uint *)(lVar5 + 0x80) = (uVar3 + 1) - uVar4 * uVar2;
  if (plVar6 != (long *)0x0) {
    lVar5 = *(long *)(lVar5 + 0x78) + (ulong)uVar3 * 0x18;
    *plVar6 = *param_1;
    *(undefined8 *)(lVar5 + 8) = param_4;
    *(ushort *)(lVar5 + 0x10) = param_2 | 0x8000;
    *(undefined1 *)(lVar5 + 0x12) = param_5;
    *(byte *)(lVar5 + 0x13) = param_3 & 0xf | 0x80;
    *param_1 = (long)plVar6;
    *(short *)((long)param_1 + 0x1a) = *(short *)((long)param_1 + 0x1a) + 1;
    *(byte *)((long)param_1 + 0x1c) = *(byte *)((long)param_1 + 0x1c) | 1;
    return 1;
  }
  return 0;
}

// ==== Aska::ShaderConstantManager::GetShaderConstantF(int, int, Aska::Vector**) const
// vaddr 0x20bd5d4 | ghidra 0x21bd5d4 | size 80 | symbol _ZNK4Aska21ShaderConstantManager18GetShaderConstantFEiiPPNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
undefined1
_ZNK4Aska21ShaderConstantManager18GetShaderConstantFEiiPPNS_6VectorE
          (long *param_1,uint param_2,uint param_3,long *param_4)

{
  param_1 = (long *)*param_1;
  if (param_1 == (long *)0x0) {
    return 0;
  }
  while (((*(ushort *)(param_1 + 2) & 0x7fff) != param_2 ||
         ((*(byte *)((long)param_1 + 0x13) & 0xf) != param_3))) {
    param_1 = (long *)*param_1;
    if (param_1 == (long *)0x0) {
      return 0;
    }
  }
  *param_4 = param_1[1];
  return *(undefined1 *)((long)param_1 + 0x12);
}

// ==== Aska::ShaderConstantManager::SearchConstInfo(int, int) const
// vaddr 0x20bd624 | ghidra 0x21bd624 | size 120 | symbol _ZNK4Aska21ShaderConstantManager15SearchConstInfoEii | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK4Aska21ShaderConstantManager15SearchConstInfoEii(long *param_1,uint param_2,uint param_3)

{
  long *plVar1;
  
  for (plVar1 = (long *)*param_1; plVar1 != (long *)0x0; plVar1 = (long *)*plVar1) {
    if (((*(ushort *)(plVar1 + 2) & 0x7fff) == param_2) &&
       ((*(byte *)((long)plVar1 + 0x13) & 0xf) == param_3)) {
      return (long)plVar1;
    }
  }
  do {
    param_1 = (long *)param_1[1];
    if (param_1 == (long *)0x0) {
      return 0;
    }
    for (plVar1 = (long *)*param_1; plVar1 != (long *)0x0; plVar1 = (long *)*plVar1) {
      if (((*(ushort *)(plVar1 + 2) & 0x7fff) == param_2) &&
         ((*(byte *)((long)plVar1 + 0x13) & 0xf) == param_3)) {
        return (long)plVar1;
      }
    }
  } while( true );
}

// ==== Aska::ShaderConstantManager::Clone(Aska::ShaderConstantManager const*)
// vaddr 0x20bd69c | ghidra 0x21bd69c | size 72 | symbol _ZN4Aska21ShaderConstantManager5CloneEPKS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska21ShaderConstantManager5CloneEPKS0_(undefined8 param_1,long *param_2)

{
  for (param_2 = (long *)*param_2; param_2 != (long *)0x0; param_2 = (long *)*param_2) {
    bool Aska::ShaderConstantManager::SetShaderConstantF_lockable<true>(int, int, Aska::Vector const*, int)(param_1,*(ushort *)(param_2 + 2) & 0x7fff,*(byte *)((long)param_2 + 0x13) & 0xf,
                    param_2[1],*(undefined1 *)((long)param_2 + 0x12));
  }
  return;
}

// ==== Aska::ShaderConstantManager::UpdatePacket(Aska::UniformValueBuffer2*, Aska::ShaderCache*)
// vaddr 0x20bd6e4 | ghidra 0x21bd6e4 | size 276 | symbol _ZN4Aska21ShaderConstantManager12UpdatePacketEPNS_19UniformValueBuffer2EPNS_11ShaderCacheE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska21ShaderConstantManager12UpdatePacketEPNS_19UniformValueBuffer2EPNS_11ShaderCacheE
          (long *param_1,undefined8 param_2,long param_3)

{
  uint uVar1;
  ushort uVar2;
  long *plVar3;
  long *plVar4;
  uint *puVar5;
  uint uVar6;
  
  if (*(short *)(param_3 + 0x50) == 0) {
    Aska::UniformValueBuffer2::Reset(Aska::UniformValueBuffer2::MemoryOperation)(param_2,1);
  }
  else {
    Aska::UniformValueBuffer2::Reset(Aska::UniformValueBuffer2::MemoryOperation)(param_2,0);
    Aska::UniformValueBuffer2::ReserveMemory(int)(param_2,*(undefined2 *)(param_3 + 0x10));
    uVar2 = *(ushort *)(param_3 + 0x50);
    if (uVar2 != 0) {
      puVar5 = *(uint **)(param_3 + 0x20);
      uVar6 = 0;
code_r0x021bd72c:
      uVar1 = *puVar5;
      for (plVar3 = (long *)*param_1; plVar3 != (long *)0x0; plVar3 = (long *)*plVar3) {
        if ((uVar1 >> 0x15 == (*(ushort *)(plVar3 + 2) & 0x7fff)) &&
           ((uVar1 & 0x1f) == (*(byte *)((long)plVar3 + 0x13) & 0xf))) goto code_r0x021bd7ac;
      }
      for (plVar4 = (long *)param_1[1]; plVar4 != (long *)0x0; plVar4 = (long *)plVar4[1]) {
        for (plVar3 = (long *)*plVar4; plVar3 != (long *)0x0; plVar3 = (long *)*plVar3) {
          if ((uVar1 >> 0x15 == (*(ushort *)(plVar3 + 2) & 0x7fff)) &&
             ((uVar1 & 0x1f) == (*(byte *)((long)plVar3 + 0x13) & 0xf))) goto code_r0x021bd7ac;
        }
      }
      goto code_r0x021bd7c4;
    }
  }
  return 1;
code_r0x021bd7ac:
  Aska::UniformValueBuffer2::Add(int, int, void*)(param_2,uVar1 >> 0xc & 0xff,uVar1 >> 1 & 0x7f0,*(undefined8 *)((long)plVar3 + 8));
code_r0x021bd7c4:
  uVar6 = uVar6 + 1;
  puVar5 = puVar5 + 1;
  if (uVar6 == uVar2) {
    return 1;
  }
  goto code_r0x021bd72c;
}

// ==== bool Aska::ShaderConstantManager::SetShaderConstantF_lockable<true>(int, int, Aska::Vector const*, int)
// vaddr 0x20bd9f4 | ghidra 0x21bd9f4 | size 552 | symbol _ZN4Aska21ShaderConstantManager27SetShaderConstantF_lockableILb1EEEbiiPKNS_6VectorEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska21ShaderConstantManager27SetShaderConstantF_lockableILb1EEEbiiPKNS_6VectorEi
          (long *param_1,uint param_2,uint param_3,undefined8 param_4,uint param_5)

{
  ulong *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  long *plVar10;
  long lVar11;
  ulong uVar12;
  long lVar13;
  
  uVar9 = (ulong)param_5;
  for (plVar10 = (long *)*param_1; plVar10 != (long *)0x0; plVar10 = (long *)*plVar10) {
    if (((*(ushort *)(plVar10 + 2) & 0x7fff) == param_2) &&
       ((*(byte *)((long)plVar10 + 0x13) & 0xf) == param_3)) {
      if ((short)*(ushort *)(plVar10 + 2) < 0) {
        lVar11 = Aska::TPoolFast<Aska::Vector, false>::Scoop(int)(*(undefined8 *)
                                  PTR__ZN4Aska6Global27m_pShaderConstantBufferPoolE_02cc0a58,uVar9);
        if (lVar11 == 0) {
          return 0;
        }
        plVar10[1] = lVar11;
        *(ushort *)(plVar10 + 2) = *(ushort *)(plVar10 + 2) & 0x7fff;
      }
      else {
        lVar11 = plVar10[1];
      }
      memcpy(lVar11,param_4,(ulong)*(byte *)((long)plVar10 + 0x12) << 4);
      *(byte *)((long)plVar10 + 0x13) = *(byte *)((long)plVar10 + 0x13) | 0x80;
      goto code_r0x021bdbe8;
    }
  }
  lVar11 = *(long *)PTR__ZN4Aska6Global27m_pShaderConstantBufferPoolE_02cc0a58;
  uVar2 = *(uint *)(lVar11 + 0x6c);
  if (*(uint *)(lVar11 + 0x84) < uVar2) {
    uVar3 = *(uint *)(lVar11 + 0x80);
    uVar12 = (ulong)uVar3;
    *(uint *)(lVar11 + 0x84) = *(uint *)(lVar11 + 0x84) + 1;
    puVar1 = (ulong *)(*(long *)(lVar11 + 0x60) + (ulong)(uVar3 >> 6) * 8);
    uVar6 = *puVar1;
    uVar7 = 1L << (uVar12 & 0x3f);
    uVar8 = uVar7 & uVar6;
    while (uVar8 != 0) {
      uVar3 = (int)uVar12 + 1;
      uVar4 = 0;
      if (uVar2 != 0) {
        uVar4 = uVar3 / uVar2;
      }
      uVar3 = uVar3 - uVar4 * uVar2;
      uVar12 = (ulong)uVar3;
      puVar1 = (ulong *)(*(long *)(lVar11 + 0x60) + (ulong)(uVar3 >> 6) * 8);
      uVar6 = *puVar1;
      uVar7 = 1L << (uVar3 & 0x3f);
      uVar8 = uVar7 & uVar6;
    }
    *puVar1 = uVar7 | uVar6;
    lVar13 = *(long *)(lVar11 + 0x78);
    uVar4 = 0;
    if (uVar2 != 0) {
      uVar4 = (uVar3 + 1) / uVar2;
    }
    plVar10 = (long *)(lVar13 + (ulong)uVar3 * 0x18);
    *(uint *)(lVar11 + 0x80) = (uVar3 + 1) - uVar4 * uVar2;
    if (plVar10 != (long *)0x0) {
      lVar5 = Aska::TPoolFast<Aska::Vector, false>::Scoop(int)(lVar11,uVar9);
      if (lVar5 == 0) {
        uVar9 = ((long)plVar10 - *(long *)(lVar11 + 0x78) >> 3) * -0x5555555555555555;
        lVar13 = (uVar9 >> 6 & 0x3ffffff) * 8;
        *(ulong *)(*(long *)(lVar11 + 0x60) + lVar13) =
             *(ulong *)(*(long *)(lVar11 + 0x60) + lVar13) &
             (1L << (uVar9 & 0x3f) ^ 0xffffffffffffffffU);
        *(int *)(lVar11 + 0x84) = *(int *)(lVar11 + 0x84) + -1;
        return 0;
      }
      lVar13 = lVar13 + (ulong)uVar3 * 0x18;
      *plVar10 = *param_1;
      *(long *)(lVar13 + 8) = lVar5;
      *(ushort *)(lVar13 + 0x10) = (ushort)param_2 & 0x7fff;
      *(char *)(lVar13 + 0x12) = (char)param_5;
      *(byte *)(lVar13 + 0x13) = (byte)param_3 & 0xf | 0x80;
      *param_1 = (long)plVar10;
      memcpy(lVar5,param_4,-(ulong)(param_5 >> 0x1f) & 0xfffffff000000000 | uVar9 << 4);
code_r0x021bdbe8:
      *(short *)((long)param_1 + 0x1a) = *(short *)((long)param_1 + 0x1a) + 1;
      *(byte *)((long)param_1 + 0x1c) = *(byte *)((long)param_1 + 0x1c) | 1;
      return 1;
    }
  }
  return 0;
}

// ==== Aska::MaterialList::MaterialList()
// vaddr 0x20c15ac | ghidra 0x21c15ac | size 372 | symbol _ZN4Aska12MaterialListC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialListC2Ev(undefined8 *param_1)

{
  undefined *puVar1;
  long *plVar2;
  long *plVar3;
  
  puVar1 = PTR__ZTVN4Aska21RenderPassManagerListE_02cb83a8 + 0x10;
  plVar3 = param_1 + 7;
  param_1[8] = PTR__ZTVN4Aska11LinkElementE_02cc16d0 + 0x10;
  *plVar3 = (long)puVar1;
  *(undefined4 *)((long)param_1 + 0x22) = 0xff0000;
  param_1[9] = param_1 + 8;
  param_1[10] = param_1 + 8;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[1] = 0;
  param_1[6] = 0;
  *(undefined4 *)(param_1 + 0xb) = 0;
  *(ushort *)(param_1 + 4) = *(ushort *)(param_1 + 4) & 0xffac;
  Aska::RenderPass::RenderPass()(param_1 + 0xc);
  plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x3c0,PTR__ZSt7nothrow_02cb9a80);
  if (plVar2 != (long *)0x0) {
    *plVar2 = (long)(PTR__ZTVN4Aska17RenderPassManagerE_02cbcfd8 + 0x10);
    plVar2[6] = 0;
    *(undefined4 *)(plVar2 + 0xf) = 0;
    *(undefined4 *)(plVar2 + 0x12) = 0;
    plVar2[0x13] = 0;
    plVar2[0x15] = 0;
    plVar2[0x1e] = 0;
    plVar2[0x20] = 0;
    *(undefined4 *)(plVar2 + 0x14) = 0x40008;
    *(undefined4 *)(plVar2 + 0x1f) = 0x40008;
    plVar2[0x29] = 0;
    plVar2[2] = 0;
    plVar2[1] = 0;
    plVar2[4] = 0;
    plVar2[3] = 0;
    *(undefined4 *)(plVar2 + 5) = 4;
    plVar2[0x17] = 0;
    plVar2[0x16] = 0;
    plVar2[0x19] = 0;
    plVar2[0x18] = 0;
    plVar2[0x24] = 0;
    plVar2[0x23] = 0;
    plVar2[0x22] = 0;
    plVar2[0x21] = 0;
    *(undefined2 *)(plVar2 + 0x2a) = 8;
    *(undefined2 *)(plVar2 + 0x35) = 8;
    *(undefined2 *)((long)plVar2 + 0x152) = 4;
    *(undefined2 *)((long)plVar2 + 0x1aa) = 4;
    plVar2[0x2b] = 0;
    plVar2[0x34] = 0;
    plVar2[0x2d] = 0;
    plVar2[0x2c] = 0;
    plVar2[0x2f] = 0;
    plVar2[0x2e] = 0;
    plVar2[0x36] = 0;
    plVar2[0x3a] = 0;
    plVar2[0x39] = 0;
    plVar2[0x38] = 0;
    plVar2[0x37] = 0;
    Aska::RenderPass::RenderPass()(plVar2 + 0x3f);
    *(undefined1 *)((long)plVar2 + 0x7d) = 0;
    plVar2[0x10] = 0;
    plVar2[0x11] = 0;
    (**(code **)(*plVar3 + 0x10))(plVar3,plVar2);
  }
  *(undefined1 *)((long)param_1 + 0x2e) = 0;
  *param_1 = 0;
  *(ushort *)(param_1 + 4) = *(ushort *)(param_1 + 4) & 0xe053 | 4;
  *(undefined2 *)((long)param_1 + 0x2b) = 0xff;
  return;
}

// ==== Aska::MaterialContext::MaterialContext()
// vaddr 0x2143ef0 | ghidra 0x2243ef0 | size 180 | symbol _ZN4Aska15MaterialContextC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15MaterialContextC2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska15MaterialContextE_02cbceb8 + 0x10);
  param_1[1] = 0;
  memset(param_1 + 4,0,0x200);
  *(undefined8 *)((long)param_1 + 0x17) = 0;
  param_1[2] = 0;
  *(undefined4 *)((long)param_1 + 0x234) = 0;
  *(undefined2 *)(param_1 + 0x47) = 0;
  *(undefined1 *)(param_1 + 0x46) = 0xff;
  param_1[0x45] = 0;
  param_1[0x44] = 0;
  *(undefined8 *)((long)param_1 + 0x23a) = 0xffffffffffffffff;
  *(undefined1 *)((long)param_1 + 0x242) = 0xff;
  *(undefined1 *)((long)param_1 + 0x243) = 0xff;
  *(undefined1 *)((long)param_1 + 0x244) = 0;
  *(ushort *)((long)param_1 + 0x245) = *(ushort *)((long)param_1 + 0x245) & 0x8000 | 0x2001;
  *(undefined1 *)((long)param_1 + 0x247) = 0;
  *(undefined1 *)(param_1 + 0x49) = 3;
  *(undefined2 *)((long)param_1 + 0x231) = 0;
  *(undefined1 *)((long)param_1 + 0x233) = 0;
  *(undefined1 *)((long)param_1 + 0x249) = 0;
  *(undefined2 *)((long)param_1 + 0x24a) = 0;
  *(undefined2 *)(param_1 + 0x4a) = 0;
  param_1[0x4c] = 0;
  param_1[0x4b] = 0;
  *(undefined2 *)(param_1 + 0x4d) = 0;
  param_1[0x4f] = 0;
  param_1[0x4e] = 0;
  param_1[0x51] = 0;
  param_1[0x50] = 0;
  return;
}

// ==== Aska::MaterialContext::Reset()
// vaddr 0x2143fa4 | ghidra 0x2243fa4 | size 164 | symbol _ZN4Aska15MaterialContext5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15MaterialContext5ResetEv(long param_1)

{
  *(undefined8 *)(param_1 + 0x17) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  memset(param_1 + 0x20,0,0x200);
  *(undefined4 *)(param_1 + 0x234) = 0;
  *(undefined2 *)(param_1 + 0x238) = 0;
  *(undefined1 *)(param_1 + 0x230) = 0xff;
  *(undefined8 *)(param_1 + 0x228) = 0;
  *(undefined8 *)(param_1 + 0x220) = 0;
  *(undefined8 *)(param_1 + 0x23a) = 0xffffffffffffffff;
  *(undefined1 *)(param_1 + 0x242) = 0xff;
  *(undefined1 *)(param_1 + 0x243) = 0xff;
  *(undefined1 *)(param_1 + 0x244) = 0;
  *(ushort *)(param_1 + 0x245) = *(ushort *)(param_1 + 0x245) & 0x8000 | 0x2001;
  *(undefined1 *)(param_1 + 0x247) = 0;
  *(undefined1 *)(param_1 + 0x248) = 3;
  *(undefined2 *)(param_1 + 0x231) = 0;
  *(undefined1 *)(param_1 + 0x233) = 0;
  *(undefined1 *)(param_1 + 0x249) = 0;
  *(undefined2 *)(param_1 + 0x24a) = 0;
  *(undefined2 *)(param_1 + 0x250) = 0;
  *(undefined8 *)(param_1 + 0x260) = 0;
  *(undefined8 *)(param_1 + 600) = 0;
  *(undefined2 *)(param_1 + 0x268) = 0;
  *(undefined8 *)(param_1 + 0x278) = 0;
  *(undefined8 *)(param_1 + 0x270) = 0;
  *(undefined8 *)(param_1 + 0x288) = 0;
  *(undefined8 *)(param_1 + 0x280) = 0;
  return;
}

// ==== Aska::MaterialContext::SetDefault(Aska::TextureSamplerMode*)
// vaddr 0x2144048 | ghidra 0x2244048 | size 36 | symbol _ZN4Aska15MaterialContext10SetDefaultEPNS_18TextureSamplerModeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15MaterialContext10SetDefaultEPNS_18TextureSamplerModeE(undefined2 *param_1)

{
  *(undefined1 *)((long)param_1 + 7) = 0;
  *(undefined1 *)(param_1 + 1) = 0;
  *(undefined1 *)(param_1 + 3) = 1;
  param_1[2] = 0x40;
  *param_1 = 0x400;
  return;
}

// ==== Aska::MaterialContext::AddShaderTexture(Aska::ShaderContext::ShaderTexKind, Aska::TEXTUREINFO*, int)
// vaddr 0x214406c | ghidra 0x224406c | size 364 | symbol _ZN4Aska15MaterialContext16AddShaderTextureENS_13ShaderContext13ShaderTexKindEPNS_11TEXTUREINFOEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska15MaterialContext16AddShaderTextureENS_13ShaderContext13ShaderTexKindEPNS_11TEXTUREINFOEi
          (long param_1,byte param_2,undefined8 param_3,uint param_4)

{
  long lVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  uint uVar8;
  int iVar9;
  byte bVar10;
  undefined8 uVar12;
  ulong uVar11;
  
  bVar10 = *(byte *)(param_1 + 0x1b);
  if (0xb < (int)(bVar10 + param_4)) {
    return 0;
  }
  if (0x10 < (int)(bVar10 + param_4 + (uint)*(byte *)(param_1 + 0x1c))) {
    return 0;
  }
  if ((int)param_4 < 1) {
    iVar6 = 0;
  }
  else {
    uVar8 = 0;
    lVar7 = 0;
    do {
      uVar4 = (uint)bVar10;
      uVar11 = (ulong)uVar4;
      if ((int)lVar7 < (int)uVar4) {
        lVar7 = (long)(int)lVar7;
        do {
          if (param_2 < *(byte *)(param_1 + lVar7 + 0x10)) break;
          lVar7 = lVar7 + 1;
        } while (lVar7 < (long)uVar11);
      }
      iVar6 = (int)lVar7;
      if (iVar6 < (int)uVar4) {
        do {
          lVar1 = param_1 + uVar11;
          uVar11 = uVar11 - 1;
          *(undefined1 *)(lVar1 + 0x10) = *(undefined1 *)(lVar1 + 0xf);
        } while ((long)iVar6 < (long)uVar11);
      }
      *(byte *)(param_1 + iVar6 + 0x10) = param_2;
      uVar8 = uVar8 + 1;
      bVar10 = *(char *)(param_1 + 0x1b) + 1;
      *(byte *)(param_1 + 0x1b) = bVar10;
    } while (uVar8 != param_4);
  }
  iVar5 = -param_4;
  iVar6 = iVar6 + iVar5 + 1;
  if (iVar6 == -1) {
    return 0;
  }
  uVar8 = (uint)*(byte *)(param_1 + 0x247);
  if (iVar6 < (int)(bVar10 - param_4)) {
    iVar9 = bVar10 - 1;
    do {
      puVar2 = (undefined8 *)(param_1 + 0x20 + (long)(int)(iVar5 + uVar8 + iVar9) * 0x20);
      uVar12 = puVar2[2];
      puVar3 = (undefined8 *)(param_1 + 0x20 + (long)(int)(uVar8 + iVar9) * 0x20);
      puVar3[3] = puVar2[3];
      puVar3[2] = uVar12;
      uVar12 = *puVar2;
      iVar9 = iVar9 + -1;
      puVar3[1] = puVar2[1];
      *puVar3 = uVar12;
      uVar8 = (uint)*(byte *)(param_1 + 0x247);
    } while (iVar6 < iVar5 + iVar9 + 1);
  }
  memcpy(param_1 + (long)(int)(uVar8 + iVar6) * 0x20 + 0x20,param_3,
                  -(ulong)(param_4 >> 0x1f) & 0xffffffe000000000 | (ulong)param_4 << 5);
  return 1;
}

// ==== Aska::MaterialContext::RemoveShaderTexture(Aska::ShaderContext::ShaderTexKind, int)
// vaddr 0x21441d8 | ghidra 0x22441d8 | size 316 | symbol _ZN4Aska15MaterialContext19RemoveShaderTextureENS_13ShaderContext13ShaderTexKindEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska15MaterialContext19RemoveShaderTextureENS_13ShaderContext13ShaderTexKindEi
          (long param_1,char param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  ulong uVar4;
  int iVar5;
  long lVar6;
  long lVar7;
  
  bVar1 = *(byte *)(param_1 + 0x1b);
  uVar4 = (ulong)bVar1;
  if (uVar4 != 0) {
    lVar6 = 0;
    lVar7 = -param_1;
    do {
      lVar7 = lVar7 + -0x20;
      if (*(char *)(param_1 + 0x10 + lVar6) == param_2) {
        bVar2 = *(byte *)(param_1 + 0x1c);
        iVar5 = (int)lVar6;
        if ((uint)bVar2 + iVar5 == -1) {
          return 0;
        }
        if ((int)((uint)bVar2 + param_3 + iVar5) <
            (int)((uint)bVar1 + (uint)*(byte *)(param_1 + 0x247))) {
          uVar3 = (((uint)bVar1 - param_3) + ((uint)*(byte *)(param_1 + 0x247) - (uint)bVar2)) -
                  iVar5;
          memcpy((ulong)bVar2 * 0x20 - lVar7,
                          param_1 + (long)(int)((uint)bVar2 + param_3 + iVar5) * 0x20 + 0x20,
                          -(ulong)(uVar3 >> 0x1f) & 0xffffffe000000000 | (ulong)uVar3 << 5);
          uVar4 = (ulong)*(byte *)(param_1 + 0x1b);
        }
        if ((int)uVar4 != 0) {
          lVar6 = 0;
          do {
            if (*(char *)(param_1 + 0x10 + lVar6) == param_2) {
              iVar5 = (int)lVar6;
              if ((uint)*(byte *)(param_1 + 0x1c) + iVar5 == -1) {
                return 1;
              }
              if (param_3 + iVar5 < (int)uVar4) {
                lVar6 = (long)(iVar5 + param_3) + 0x10;
                do {
                  lVar7 = lVar6 + -0xf;
                  *(undefined1 *)((param_1 - param_3) + lVar6) = *(undefined1 *)(param_1 + lVar6);
                  uVar4 = (ulong)*(byte *)(param_1 + 0x1b);
                  lVar6 = lVar6 + 1;
                } while (lVar7 < (long)uVar4);
              }
              *(char *)(param_1 + 0x1b) = (char)uVar4 - (char)param_3;
              return 1;
            }
            lVar6 = lVar6 + 1;
          } while (lVar6 < (long)uVar4);
          return 1;
        }
        return 1;
      }
      lVar6 = lVar6 + 1;
    } while (lVar6 < (long)uVar4);
  }
  return 0;
}

// ==== Aska::MaterialContext::MakeShaderConstant(Aska::ShaderConstantManager*)
// vaddr 0x2144314 | ghidra 0x2244314 | size 1204 | symbol _ZN4Aska15MaterialContext18MakeShaderConstantEPNS_21ShaderConstantManagerE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint _ZN4Aska15MaterialContext18MakeShaderConstantEPNS_21ShaderConstantManagerE
               (long param_1,undefined8 param_2)

{
  int iVar1;
  float *pfVar2;
  long lVar3;
  short sVar4;
  int iVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  undefined *puVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  undefined8 uVar22;
  float *pfVar23;
  char cVar24;
  int iVar25;
  long lVar26;
  char *pcVar27;
  char cVar28;
  undefined4 uVar29;
  float fVar30;
  undefined4 uVar31;
  float fVar32;
  undefined8 uStack_330;
  undefined8 uStack_328;
  undefined8 uStack_320;
  undefined8 uStack_318;
  undefined8 uStack_310;
  undefined8 uStack_308;
  undefined8 uStack_300;
  undefined8 uStack_2f8;
  undefined8 uStack_2f0;
  undefined8 uStack_2e8;
  undefined8 uStack_2e0;
  undefined8 uStack_2d8;
  undefined8 uStack_2d0;
  undefined8 uStack_2c8;
  undefined8 uStack_2c0;
  undefined8 uStack_2b8;
  undefined8 uStack_2b0;
  undefined8 uStack_2a8;
  undefined8 uStack_2a0;
  undefined8 uStack_298;
  undefined8 uStack_290;
  undefined8 uStack_288;
  undefined8 uStack_280;
  undefined8 uStack_278;
  undefined8 uStack_270;
  undefined8 uStack_268;
  undefined8 uStack_260;
  undefined8 uStack_258;
  undefined8 uStack_250;
  undefined8 uStack_248;
  undefined8 uStack_240;
  undefined8 uStack_238;
  undefined8 uStack_230;
  undefined8 uStack_228;
  undefined8 uStack_220;
  undefined8 uStack_218;
  undefined8 uStack_210;
  undefined8 uStack_208;
  undefined8 uStack_200;
  undefined8 uStack_1f8;
  float fStack_1f0;
  undefined4 uStack_1ec;
  undefined4 uStack_1e8;
  undefined4 uStack_1e4;
  undefined8 uStack_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 uStack_1a8;
  undefined8 uStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  float afStack_170 [64];
  
  uVar6 = _UNK_027dbb08;
  uVar22 = _UNK_027dbb00;
  *(undefined1 *)(param_1 + 0x244) = 0;
  puVar16 = PTR__ZN4Aska15MaterialContext19m_mPostRotateMatrixE_02cc05d0;
  puVar15 = PTR__ZN4Aska15MaterialContext18m_mPreRotateMatrixE_02cbd580;
  puVar14 = PTR__ZN4Aska15MaterialContext17m_mPreScaleMatrixE_02cb8258;
  puVar13 = PTR__ZN4Aska15MaterialContext18m_mPostScaleMatrixE_02cb81e8;
  uVar12 = _UNK_027dbb38;
  uVar11 = _UNK_027dbb30;
  uVar10 = _UNK_027dbb28;
  uVar9 = _UNK_027dbb20;
  uVar8 = _UNK_027dbb18;
  uVar7 = _UNK_027dbb10;
  lVar26 = 0;
  cVar24 = '\0';
  pcVar27 = (char *)(param_1 + 0x23a);
  cVar28 = '\x02';
  pfVar23 = afStack_170 + 4;
  do {
    if (*pcVar27 != -1) {
      uStack_1e8 = (undefined4)uVar6;
      uStack_1e4 = (undefined4)((ulong)uVar6 >> 0x20);
      uVar17 = uStack_1e4;
      uStack_1ec = (undefined4)((ulong)uVar22 >> 0x20);
      uVar31 = uStack_1ec;
      uStack_1d8 = uVar8;
      uStack_1c8 = uVar10;
      uStack_1d0 = uVar9;
      uStack_1b8 = uVar12;
      uStack_1c0 = uVar11;
      pfVar2 = (float *)(*(long *)(param_1 + 0x280) + lVar26);
      fStack_1f0 = 1.0 / *pfVar2;
      uStack_268 = uVar6;
      uStack_270 = uVar22;
      uStack_258 = uVar8;
      uStack_260 = uVar7;
      uStack_248 = uVar10;
      uStack_250 = uVar9;
      uStack_238 = uVar12;
      uStack_240 = uVar11;
      uStack_1e0._0_4_ = (undefined4)uVar7;
      uVar18 = (undefined4)uStack_1e0;
      uStack_1e0 = CONCAT44(1.0 / pfVar2[1],(undefined4)uStack_1e0);
      uVar29 = cosf(pfVar2[4]);
      uStack_270 = CONCAT44(uStack_270._4_4_,uVar29);
      fVar30 = (float)sinf(*(undefined4 *)(*(long *)(param_1 + 0x280) + lVar26 + 0x10));
      uStack_270 = CONCAT44(fVar30,(undefined4)uStack_270);
      uStack_2a8 = uVar6;
      uStack_298 = uVar8;
      uStack_288 = uVar10;
      uStack_290 = uVar9;
      uStack_278 = uVar12;
      uStack_280 = uVar11;
      uStack_260 = CONCAT44((undefined4)uStack_270,-fVar30);
      lVar3 = *(long *)(param_1 + 0x280) + lVar26;
      uStack_2b0 = CONCAT44(uVar31,*(undefined4 *)(lVar3 + 0x14));
      uStack_230 = uVar22;
      uStack_220 = uVar7;
      uStack_208 = uVar10;
      uStack_210 = uVar9;
      uStack_1f8 = uVar12;
      uStack_200 = uVar11;
      uStack_2a0 = CONCAT44(*(undefined4 *)(lVar3 + 0x18),uVar18);
      uStack_228 = CONCAT44(uVar17,-*(float *)(lVar3 + 8));
      uStack_2f0 = uVar22;
      uStack_2e0 = uVar7;
      uStack_2c8 = uVar10;
      uStack_2d0 = uVar9;
      uStack_2b8 = uVar12;
      uStack_2c0 = uVar11;
      uStack_218._4_4_ = (undefined4)((ulong)uVar8 >> 0x20);
      uStack_218 = CONCAT44(uStack_218._4_4_,*(undefined4 *)(lVar3 + 0xc));
      uStack_2e8 = CONCAT44(uVar17,*(undefined4 *)(lVar3 + 0x1c));
      uStack_328 = uVar6;
      uStack_330 = uVar22;
      uStack_318 = uVar8;
      uStack_320 = uVar7;
      uStack_308 = uVar10;
      uStack_310 = uVar9;
      uStack_2f8 = uVar12;
      uStack_300 = uVar11;
      uStack_2d8 = CONCAT44(uStack_218._4_4_,-*(float *)(lVar3 + 0x20));
      uVar31 = cosf(*(undefined4 *)(lVar3 + 0x24));
      uStack_330 = CONCAT44(uStack_330._4_4_,uVar31);
      fVar30 = (float)sinf(*(undefined4 *)(*(long *)(param_1 + 0x280) + lVar26 + 0x24));
      uStack_330 = CONCAT44(fVar30,(undefined4)uStack_330);
      uStack_1a8 = uVar6;
      uStack_1b0 = uVar22;
      uStack_320 = CONCAT44((undefined4)uStack_330,-fVar30);
      uStack_198 = uVar8;
      uStack_1a0 = uVar7;
      uStack_188 = uVar10;
      uStack_190 = uVar9;
      uStack_178 = uVar12;
      uStack_180 = uVar11;
      Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_1b0,puVar15);
      Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_1b0,&uStack_270);
      Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_1b0,puVar16);
      Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_1b0,&uStack_230);
      Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_1b0,puVar14);
      Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_1b0,&fStack_1f0);
      Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_1b0,puVar13);
      Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_1b0,puVar14);
      Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_1b0,&uStack_2b0);
      Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_1b0,puVar13);
      Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_1b0,&uStack_2f0);
      Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_1b0,puVar15);
      Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_1b0,&uStack_330);
      Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&uStack_1b0,puVar16);
      uVar19 = (uint)*(byte *)(*(long *)(param_1 + 0x280) + lVar26 + 0x28);
      fVar30 = (float)uStack_1a8;
      fVar32 = (float)uStack_198;
      if (uVar19 != 0) {
        uVar19 = uVar19 + 1 & 0x1fe;
        iVar25 = (int)(float)uStack_1a8;
        iVar1 = uVar19 + 2;
        if (iVar25 < (int)(uVar19 + 4)) {
          iVar5 = iVar1;
          if (iVar25 <= (int)(-4 - uVar19)) goto code_r0x022445e0;
        }
        else {
          iVar5 = -iVar1;
code_r0x022445e0:
          fVar30 = (float)uStack_1a8 - (float)(int)(iVar5 + iVar25 & 0xfffffffe);
          uStack_1a8 = CONCAT44(uStack_1a8._4_4_,fVar30);
        }
        iVar25 = (int)(float)uStack_198;
        if (iVar25 < (int)(uVar19 + 4)) {
          if ((int)(-4 - uVar19) < iVar25) goto code_r0x02244638;
        }
        else {
          iVar1 = -iVar1;
        }
        fVar32 = (float)uStack_198 - (float)(int)(iVar1 + iVar25 & 0xfffffffe);
        uStack_198 = CONCAT44(uStack_198._4_4_,fVar32);
      }
code_r0x02244638:
      pfVar23[-2] = fVar30;
      pfVar23[-1] = 1.0;
      pfVar23[2] = fVar32;
      pfVar23[3] = 1.0;
      *pfVar23 = (float)uStack_1a0;
      pfVar23[1] = uStack_1a0._4_4_;
      pfVar23[-4] = (float)uStack_1b0;
      pfVar23[-3] = uStack_1b0._4_4_;
      *(char *)(param_1 + 0x244) = cVar28;
      cVar24 = cVar28;
    }
    lVar26 = lVar26 + 0x2c;
    pcVar27 = pcVar27 + 1;
    cVar28 = cVar28 + '\x02';
    pfVar23 = pfVar23 + 8;
  } while (lVar26 != 0x160);
  if (cVar24 == '\0') {
    uVar19 = 0;
    sVar4 = *(short *)(param_1 + 0x238);
  }
  else {
    uVar19 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(param_2,0x40,0,afStack_170);
    sVar4 = *(short *)(param_1 + 0x238);
  }
  if ((sVar4 != 0) && (lVar26 = *(long *)(param_1 + 0x288), lVar26 != 0)) {
    if (sVar4 == 0x200) {
      fVar30 = *(float *)(lVar26 + 8);
      fVar32 = 0.0;
      if (_UNK_027e519c <= fVar30) {
        fVar32 = 1.0 / fVar30;
      }
      uStack_1b0 = CONCAT44(*(undefined4 *)(lVar26 + 4),*(undefined4 *)(lVar26 + 0x34));
      uStack_1a8 = CONCAT44(fVar32,fVar30);
      uVar20 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(param_2,0x59,0,&uStack_1b0,1);
      uVar21 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(param_2,0x5a,0,*(long *)(param_1 + 0x288) + 0x20,1);
      uVar19 = uVar19 | uVar20 | uVar21;
      uVar22 = 0x5b;
      fStack_1f0 = *(float *)(*(long *)(param_1 + 0x288) + 0x38);
      pfVar23 = &fStack_1f0;
      uStack_1ec = 0;
      uStack_1e8 = 0;
      uStack_1e4 = 0;
    }
    else {
      if (sVar4 != 0x100) goto code_r0x022447a0;
      uVar20 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(param_2,0x59,0,lVar26,1);
      uVar19 = uVar19 | uVar20;
      uVar22 = 0x5a;
      pfVar23 = (float *)(*(long *)(param_1 + 0x288) + 0x10);
    }
    uVar20 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(param_2,uVar22,0,pfVar23,1);
    uVar19 = uVar19 | uVar20;
  }
code_r0x022447a0:
  return uVar19 & 1;
}

// ==== Aska::MaterialContext::Apply(unsigned long, Aska::RenderDeviceGL*, Aska::ShaderNodeHandler*)
// vaddr 0x21447c8 | ghidra 0x22447c8 | size 84 | symbol _ZN4Aska15MaterialContext5ApplyEmPNS_14RenderDeviceGLEPNS_17ShaderNodeHandlerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15MaterialContext5ApplyEmPNS_14RenderDeviceGLEPNS_17ShaderNodeHandlerE(void)

{
  long in_x3;
  undefined8 uVar1;
  
  uVar1 = *(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  if (*(long *)(in_x3 + 0x30) != 0) {
    Aska::RenderDeviceGL::SetVertexShaderConstant(Aska::UniformValueBuffer2*)(uVar1,in_x3 + 0x28);
  }
  if (*(long *)(in_x3 + 0x40) != 0) {
    (*(code *)
      PTR__ZN4Aska14RenderDeviceGL22SetPixelShaderConstantEPNS_19UniformValueBuffer2E_02c9e408)
              (uVar1,in_x3 + 0x38);
    return;
  }
  return;
}

// ==== Aska::MaterialContext::ApplyToCommandBuffer(unsigned long, Aska::TLongInt<unsigned long, 1>*, Aska::CommandBufferManager*)
// vaddr 0x214481c | ghidra 0x224481c | size 4 | symbol _ZN4Aska15MaterialContext20ApplyToCommandBufferEmPNS_8TLongIntImLi1EEEPNS_20CommandBufferManagerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15MaterialContext20ApplyToCommandBufferEmPNS_8TLongIntImLi1EEEPNS_20CommandBufferManagerE
               (void)

{
  return;
}

// ==== Aska::ShaderConstantHandler::~ShaderConstantHandler()
// vaddr 0x2144820 | ghidra 0x2244820 | size 4 | symbol _ZN4Aska21ShaderConstantHandlerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska21ShaderConstantHandlerD2Ev(void)

{
  return;
}

// ==== Aska::MaterialContext::~MaterialContext()
// vaddr 0x2144824 | ghidra 0x2244824 | size 4 | symbol _ZN4Aska15MaterialContextD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15MaterialContextD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::MaterialList::GetAllocBufSize(int, Aska::AFF::Meshset const*) const
// vaddr 0x2144828 | ghidra 0x2244828 | size 80 | symbol _ZNK4Aska12MaterialList15GetAllocBufSizeEiPKNS_3AFF7MeshsetE | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK4Aska12MaterialList15GetAllocBufSizeEiPKNS_3AFF7MeshsetE
               (undefined8 param_1,int param_2,long param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = param_2 * 0x2a0 | 0x10;
  if (0 < param_2) {
    do {
      if (*(short *)(param_3 + 0x1c) != 0) {
        uVar1 = uVar1 + 0x40;
      }
      uVar2 = (uint)*(byte *)(*(int *)(param_3 + 0x14) + param_3 + 0x19);
      if (uVar2 != 0) {
        uVar1 = uVar1 + uVar2 * 0x2c;
      }
      param_2 = param_2 + -1;
      param_3 = param_3 + *(int *)(param_3 + 0xc);
    } while (param_2 != 0);
  }
  return uVar1;
}

// ==== Aska::MaterialList::Alloc(int, void*)
// vaddr 0x2144878 | ghidra 0x2244878 | size 280 | symbol _ZN4Aska12MaterialList5AllocEiPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska12MaterialList5AllocEiPv(long *param_1,int param_2,long param_3)

{
  ulong uVar1;
  ushort uVar2;
  long lVar3;
  long lVar4;
  
  if ((int)param_1[0xb] != 0) {
    if (param_2 != 0) {
      lVar3 = param_3 + 0x10;
      lVar4 = (long)param_2 * 0x2a0;
      do {
        Aska::MaterialContext::MaterialContext()(lVar3);
        lVar4 = lVar4 + -0x2a0;
        lVar3 = lVar3 + 0x2a0;
      } while (lVar4 != 0);
    }
    lVar3 = param_1[10];
    param_1[2] = ((long)param_2 * 0x2a0 | 0x10U) + param_3;
    param_1[3] = param_3;
    uVar1 = Aska::RenderPassManager::Init(int)(lVar3,param_2);
    if ((uVar1 & 1) != 0) {
      param_1[6] = (long)(param_1 + 0xc);
      uVar1 = Aska::RenderPass::Init(int, void*)(param_1 + 0xc,param_2,0);
      if ((((uVar1 & 1) != 0) && (uVar1 = Aska::RenderPass::Create(int)(param_1[6],0), (uVar1 & 1) != 0)) &&
         (uVar1 = Aska::RenderPass::Create(int)(*(undefined8 *)(lVar3 + 0x18),0), (uVar1 & 1) != 0)) {
        *(undefined1 *)((long)param_1 + 0x22) = 0;
        *(char *)((long)param_1 + 0x23) = (char)param_2;
        return 1;
      }
    }
  }
  uVar2 = *(ushort *)(param_1 + 4);
  if ((uVar2 & 3) != 0) {
    if (param_1[3] != 0) {
      if (*param_1 != 0) {
        operator delete[](void*)();
        uVar2 = *(ushort *)(param_1 + 4);
        *param_1 = 0;
      }
      *(undefined2 *)((long)param_1 + 0x22) = 0;
      param_1[2] = 0;
      param_1[3] = 0;
      param_1[1] = 0;
    }
    *(ushort *)(param_1 + 4) = uVar2 & 0xfffc;
  }
  return 0;
}

// ==== Aska::MaterialList::DeleteBuffer()
// vaddr 0x2144990 | ghidra 0x2244990 | size 76 | symbol _ZN4Aska12MaterialList12DeleteBufferEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList12DeleteBufferEv(long *param_1)

{
  ushort uVar1;
  
  uVar1 = *(ushort *)(param_1 + 4);
  if ((uVar1 & 3) != 0) {
    if (param_1[3] != 0) {
      if (*param_1 != 0) {
        operator delete[](void*)();
        uVar1 = *(ushort *)(param_1 + 4);
        *param_1 = 0;
      }
      *(undefined2 *)((long)param_1 + 0x22) = 0;
      param_1[2] = 0;
      param_1[3] = 0;
      param_1[1] = 0;
    }
    *(ushort *)(param_1 + 4) = uVar1 & 0xfffc;
  }
  return;
}

// ==== Aska::MaterialList::Connect(int, int, Aska::MaterialData const*)
// vaddr 0x21449dc | ghidra 0x22449dc | size 36 | symbol _ZN4Aska12MaterialList7ConnectEiiPKNS_12MaterialDataE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList7ConnectEiiPKNS_12MaterialDataE
               (long param_1,int param_2,undefined8 param_3,undefined8 param_4)

{
  ushort *puVar1;
  undefined8 *puVar2;
  
  puVar2 = (undefined8 *)(*(long *)(param_1 + 0x18) + (long)param_2 * 0x2a0);
  *puVar2 = param_4;
  puVar1 = (ushort *)((long)puVar2 + 0x255);
  *puVar1 = *puVar1 | 1;
  return;
}

// ==== Aska::MaterialList::SetPerPixelLightCount(int)
// vaddr 0x2144a00 | ghidra 0x2244a00 | size 188 | symbol _ZN4Aska12MaterialList21SetPerPixelLightCountEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList21SetPerPixelLightCountEi(long param_1,int param_2)

{
  int iVar1;
  int iVar2;
  ulong uVar3;
  byte *pbVar4;
  long lVar5;
  
  if (*(char *)(param_1 + 0x24) != param_2) {
    uVar3 = (ulong)*(byte *)(param_1 + 0x22);
    iVar2 = param_2;
    if (3 < param_2) {
      iVar2 = 4;
    }
    iVar1 = 3;
    if (-1 < param_2) {
      iVar1 = iVar2;
    }
    *(char *)(param_1 + 0x24) = (char)param_2;
    if (uVar3 != 0) {
      lVar5 = 600;
      do {
        uVar3 = uVar3 - 1;
        *(char *)(*(long *)(param_1 + 0x18) + lVar5) = (char)iVar1;
        lVar5 = lVar5 + 0x2a0;
      } while (uVar3 != 0);
    }
    if ((*(byte *)(param_1 + 0x20) >> 6 & 1) != 0) {
      pbVar4 = (byte *)(param_1 + iVar1 + 0x26);
      if (*pbVar4 < 2) {
        *pbVar4 = 1;
      }
      if (*(char *)(param_1 + 0x2b) < iVar1) {
        *(char *)(param_1 + 0x2b) = (char)iVar1;
      }
    }
    for (lVar5 = *(long *)(param_1 + 0x50); param_1 + 0x40 != lVar5; lVar5 = *(long *)(lVar5 + 0x10)
        ) {
      Aska::RenderPass::InvalidateShaders()(*(undefined8 *)(lVar5 + 0x18));
      Aska::RenderPassManager::InvalidateShaders(bool)(lVar5,0);
    }
  }
  return;
}

// ==== Aska::MaterialList::EnablePerMatLightContext(bool)
// vaddr 0x2144abc | ghidra 0x2244abc | size 32 | symbol _ZN4Aska12MaterialList24EnablePerMatLightContextEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList24EnablePerMatLightContextEb(long param_1,ushort param_2)

{
  if ((param_2 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x2a) = 0;
    *(undefined4 *)(param_1 + 0x26) = 0;
  }
  *(ushort *)(param_1 + 0x20) =
       *(ushort *)(param_1 + 0x20) & 0xff80 |
       *(ushort *)(param_1 + 0x20) & 0x3f | (param_2 & 1) << 6;
  return;
}

// ==== Aska::MaterialList::SetPerMatLightContext(int, int, Aska::MaterialList::LightFreq)
// vaddr 0x2144adc | ghidra 0x2244adc | size 56 | symbol _ZN4Aska12MaterialList21SetPerMatLightContextEiiNS0_9LightFreqE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList21SetPerMatLightContextEiiNS0_9LightFreqE
               (long param_1,int param_2,int param_3,byte param_4)

{
  byte *pbVar1;
  
  *(char *)(*(long *)(param_1 + 0x18) + (long)param_2 * 0x2a0 + 600) = (char)param_3;
  pbVar1 = (byte *)(param_1 + param_3 + 0x26);
  if (*pbVar1 < 2) {
    *pbVar1 = param_4;
  }
  if (*(char *)(param_1 + 0x2b) < param_3) {
    *(char *)(param_1 + 0x2b) = (char)param_3;
  }
  return;
}

// ==== Aska::MaterialList::UpdatePunchthroughZprepass()
// vaddr 0x2144b14 | ghidra 0x2244b14 | size 104 | symbol _ZN4Aska12MaterialList26UpdatePunchthroughZprepassEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList26UpdatePunchthroughZprepassEv(long param_1)

{
  ushort uVar1;
  long lVar2;
  byte *pbVar3;
  
  uVar1 = 0;
  if ((ulong)*(byte *)(param_1 + 0x22) != 0) {
    if (*(long *)(param_1 + 0x18) == 0) {
      uVar1 = (uRam0000000000000245 & 4) << 6;
    }
    else {
      lVar2 = 0;
      pbVar3 = (byte *)(*(long *)(param_1 + 0x18) + 0x255);
      do {
        if ((*pbVar3 >> 2 & 1) != 0) {
          uVar1 = 0x100;
          goto code_r0x02244b64;
        }
        lVar2 = lVar2 + 1;
        pbVar3 = pbVar3 + 0x2a0;
      } while (lVar2 < (long)(ulong)*(byte *)(param_1 + 0x22));
      uVar1 = 0;
    }
  }
code_r0x02244b64:
  *(ushort *)(param_1 + 0x20) = *(ushort *)(param_1 + 0x20) & 0xfeff | uVar1;
  return;
}

// ==== Aska::MaterialList::SetAmbientBRDFCapability(int, bool)
// vaddr 0x2144b7c | ghidra 0x2244b7c | size 112 | symbol _ZN4Aska12MaterialList24SetAmbientBRDFCapabilityEib | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList24SetAmbientBRDFCapabilityEib(long param_1,int param_2,ushort param_3)

{
  ushort *puVar1;
  ushort uVar2;
  long lVar3;
  long lVar4;
  
  puVar1 = (ushort *)(*(long *)(param_1 + 0x18) + (long)param_2 * 0x2a0 + 0x255);
  uVar2 = *puVar1;
  *puVar1 = uVar2 & 0xfe00 | uVar2 & 0xff | (param_3 & 1) << 8;
  uVar2 = *(ushort *)(param_1 + 0x20);
  if ((param_3 & 1) == 0) {
    uVar2 = uVar2 & 0xfdff;
    *(ushort *)(param_1 + 0x20) = uVar2;
    if ((ulong)*(byte *)(param_1 + 0x22) != 0) {
      lVar3 = 0;
      lVar4 = *(long *)(param_1 + 0x18) + 0x255;
      do {
        if ((*(byte *)(lVar4 + 1) & 1) != 0) goto code_r0x02244be0;
        lVar3 = lVar3 + 1;
        lVar4 = lVar4 + 0x2a0;
      } while (lVar3 < (long)(ulong)*(byte *)(param_1 + 0x22));
    }
    return;
  }
code_r0x02244be0:
  *(ushort *)(param_1 + 0x20) = uVar2 | 0x200;
  return;
}

// ==== Aska::MaterialList::DisableAmbientBRDFCapability()
// vaddr 0x2144bec | ghidra 0x2244bec | size 64 | symbol _ZN4Aska12MaterialList28DisableAmbientBRDFCapabilityEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList28DisableAmbientBRDFCapabilityEv(long param_1)

{
  ulong uVar1;
  long lVar2;
  
  uVar1 = (ulong)*(byte *)(param_1 + 0x22);
  if (uVar1 != 0) {
    lVar2 = 0x255;
    do {
      uVar1 = uVar1 - 1;
      *(ushort *)(*(long *)(param_1 + 0x18) + lVar2) =
           *(ushort *)(*(long *)(param_1 + 0x18) + lVar2) & 0xfeff;
      lVar2 = lVar2 + 0x2a0;
    } while (uVar1 != 0);
  }
  *(ushort *)(param_1 + 0x20) = *(ushort *)(param_1 + 0x20) & 0xfdff;
  return;
}

// ==== Aska::MaterialList::Activate(void const*, Aska::AFF::MaterialInfo const*, int, Aska::AofhMeshset**)
// vaddr 0x2144c2c | ghidra 0x2244c2c | size 1680 | symbol _ZN4Aska12MaterialList8ActivateEPKvPKNS_3AFF12MaterialInfoEiPPNS_11AofhMeshsetE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList8ActivateEPKvPKNS_3AFF12MaterialInfoEiPPNS_11AofhMeshsetE
               (long param_1,undefined8 param_2,byte *param_3,uint param_4,long param_5)

{
  undefined8 *puVar1;
  long lVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  byte bVar6;
  ushort uVar7;
  short sVar8;
  int iVar9;
  ushort uVar10;
  ushort uVar11;
  ushort uVar12;
  ushort uVar13;
  ushort uVar14;
  ushort uVar15;
  uint uVar16;
  uint uVar17;
  undefined1 uVar18;
  uint uVar19;
  long lVar20;
  long lVar21;
  ulong uVar22;
  long *plVar23;
  undefined1 *puVar24;
  undefined1 *puVar25;
  float *pfVar26;
  long lVar27;
  ulong uVar28;
  long lVar29;
  undefined8 uVar30;
  ushort *puVar31;
  long lVar32;
  ulong uVar33;
  long lVar34;
  uint uVar35;
  undefined8 *puVar36;
  byte bVar37;
  float fVar38;
  float fVar39;
  undefined1 auStack_a0 [48];
  
  uVar7 = *(ushort *)(param_1 + 0x20);
  *(ushort *)(param_1 + 0x20) = uVar7 | 1;
  uVar13 = uVar7 & 0xffcf | 1 | (*param_3 & 0xf) << 4;
  *(ushort *)(param_1 + 0x20) = uVar13;
  uVar13 = uVar13 & 0x5f | (param_3[3] & 1) << 7;
  *(ushort *)(param_1 + 0x20) = uVar7 & 0xff00 | uVar13;
  uVar13 = uVar7 & 0xfe00 | uVar13 | (ushort)param_3[4] << 8;
  *(ushort *)(param_1 + 0x20) = uVar13;
  uVar13 = uVar13 & 0xfbdf | (ushort)param_3[5] << 10;
  *(ushort *)(param_1 + 0x20) = uVar13;
  bVar37 = param_3[6];
  *(undefined8 *)(param_1 + 8) = param_2;
  *(char *)(param_1 + 0x22) = (char)param_4;
  *(ushort *)(param_1 + 0x20) = uVar13 & 0xf7df | (ushort)bVar37 << 0xb;
  if (param_4 != 0) {
    lVar20 = *(long *)(param_1 + 0x50);
    if (0 < (int)param_4) {
      uVar33 = 0;
      do {
        lVar21 = *(long *)(*(long *)(param_1 + 0x18) + uVar33 * 0x2a0);
        uVar35 = (uint)*(byte *)(lVar21 + 0x16);
        if (*(byte *)(lVar21 + 0x16) != 0) {
          lVar32 = *(long *)(param_1 + 0x68) + uVar33 * 0x1b8;
          puVar31 = (ushort *)(*(int *)(lVar21 + 0x20) + lVar21);
          do {
            lVar21 = (long)*(int *)(puVar31 + 2) + (long)puVar31;
            uVar16 = Aska::AhslConst::AofConvertToNativeConstant(int, Aska::Vector const*, Aska::Vector*)(*puVar31,lVar21,auStack_a0);
            if (uVar16 == 0) {
              Aska::ShaderConstantManager::SetShaderConstantRefF(int, int, Aska::Vector const*, int)(lVar32,*puVar31,(char)puVar31[1],lVar21,
                              *(byte *)((long)puVar31 + 3) >> 2);
            }
            else {
              uVar17 = (uint)*puVar31;
              uVar18 = (undefined1)puVar31[1];
              uVar19 = (uint)(*(byte *)((long)puVar31 + 3) >> 2);
              if (1 < (int)uVar16) {
                Aska::ShaderConstantManager::SetShaderConstantRefF(int, int, Aska::Vector const*, int)(lVar32,uVar17,uVar18,lVar21,uVar19);
                uVar18 = (undefined1)puVar31[1];
                uVar17 = *puVar31 + 1;
                uVar19 = uVar16;
              }
              bool Aska::ShaderConstantManager::SetShaderConstantF_lockable<false>(int, int, Aska::Vector const*, int)(lVar32,uVar17,uVar18,auStack_a0,uVar19);
            }
            uVar35 = uVar35 - 1;
            puVar31 = puVar31 + 4;
          } while (uVar35 != 0);
        }
        uVar33 = uVar33 + 1;
      } while (uVar33 != param_4);
      if (0 < (int)param_4) {
        puVar36 = *(undefined8 **)(param_1 + 0x10);
        uVar33 = 0;
        do {
          lVar32 = *(long *)(param_1 + 0x18);
          plVar23 = (long *)(lVar32 + uVar33 * 0x2a0);
          lVar34 = *plVar23;
          lVar21 = *(long *)(*(long *)(param_1 + 0x68) + uVar33 * 0x1b8 + 0x20);
          iVar9 = *(int *)(lVar34 + 0x1c);
          *(undefined2 *)(lVar21 + 0x80) = 0;
          *(undefined8 *)(lVar21 + 0x70) = 0;
          *(undefined8 *)(lVar21 + 0x78) = 0;
          *(long *)(lVar21 + 8) = iVar9 + lVar34;
          bVar37 = *(byte *)(lVar34 + 0x18);
          *(byte *)((long)plVar23 + 599) = bVar37;
          *(byte *)((long)plVar23 + 0x2c) = bVar37;
          if ((ulong)bVar37 != 0) {
            memcpy(lVar32 + uVar33 * 0x2a0 + 0x30,*(int *)(lVar34 + 0x2c) + lVar34,
                            (ulong)bVar37 << 5);
          }
          lVar21 = lVar32 + uVar33 * 0x2a0;
          *(undefined1 *)(lVar21 + 0x241) = *(undefined1 *)(lVar34 + 0x1b);
          puVar31 = (ushort *)(lVar21 + 0x255);
          *(undefined1 *)(lVar21 + 0x242) = *(undefined1 *)(lVar34 + 0x40);
          uVar7 = *puVar31;
          uVar12 = uVar7 & 0xfffd | (*(byte *)(lVar34 + 0xb0) & 0x7f) << 1;
          *puVar31 = uVar12;
          *(undefined1 *)(lVar21 + 0x243) = *(undefined1 *)(lVar34 + 0xb1);
          uVar14 = uVar12 & 0xffef | (*(byte *)(lVar34 + 0x41) & 0xf) << 4;
          *puVar31 = uVar14;
          uVar11 = (*(byte *)(lVar34 + 0x42) & 7) << 5;
          *puVar31 = uVar14 & 0xffdf | uVar11;
          uVar15 = uVar14 & 0xefdf | uVar11;
          uVar13 = (ushort)*(byte *)(lVar34 + 0x29) << 0xc;
          uVar10 = uVar15 | uVar13;
          *puVar31 = uVar10;
          *(undefined1 *)(lVar21 + 0x25a) = *(undefined1 *)(lVar34 + 0x2a);
          uVar12 = uVar12 & 3 | (ushort)((*(uint *)(lVar34 + 0x3c) >> 3 & 1) << 2);
          *puVar31 = uVar14 & 0xefd8 | uVar11 | uVar13 | uVar12;
          uVar13 = uVar14 & 0xefd0 | uVar11 | uVar13;
          uVar12 = uVar12 | (ushort)((*(uint *)(lVar34 + 0x3c) & 1) << 3);
          *puVar31 = uVar13 | uVar12;
          uVar13 = uVar13 & 0xc000;
          uVar14 = (ushort)((*(uint *)(lVar34 + 0x3c) >> 8 & 1) << 0xd);
          *puVar31 = uVar13 | uVar10 & 0x1ff0 | uVar12 | uVar14;
          sVar8 = *(short *)(**(long **)(param_5 + uVar33 * 8) + 0x1c);
          *(short *)(lVar21 + 0x248) = sVar8;
          *puVar31 = uVar13 | uVar10 & 0x1f00 | uVar14 |
                     uVar15 & 0x70 | uVar12 | (uVar7 >> 7 & 1 | (ushort)(sVar8 != 0)) << 7;
          *(long *)(*(long *)(param_1 + 0x68) + uVar33 * 0x1b8 + 0x28) =
               *(long *)(param_5 + uVar33 * 8) + 0x40;
          *(undefined1 *)(lVar21 + 0x25b) = *(undefined1 *)(lVar34 + 0x2b);
          *(uint *)(lVar21 + 0x244) = (uint)*(byte *)(*(int *)(lVar34 + 0x1c) + lVar34 + 0xf);
          uVar35 = *(uint *)(lVar34 + 0x3c);
          if ((uVar35 >> 5 & 1) == 0) {
            if ((uVar35 >> 7 & 1) == 0) goto code_r0x022450a4;
code_r0x02244e00:
            *puVar31 = *puVar31 | 0x400;
            uVar35 = *(uint *)(lVar34 + 0x3c);
            if ((uVar35 >> 6 & 1) != 0) goto code_r0x02244e14;
code_r0x022450a8:
            if ((uVar35 >> 4 & 1) == 0) goto code_r0x022450ac;
code_r0x02244e28:
            *puVar31 = *puVar31 | 0x100;
            *(ushort *)(param_1 + 0x20) = *(ushort *)(param_1 + 0x20) | 0x200;
            uVar22 = (ulong)*(byte *)(lVar34 + 0x28);
            if (uVar22 == 0) goto code_r0x02244e48;
code_r0x022450b4:
            puVar24 = (undefined1 *)(lVar34 + 0x25);
            puVar25 = (undefined1 *)(lVar32 + uVar33 * 0x2a0 + 0x261);
            uVar28 = uVar22;
            do {
              uVar28 = uVar28 - 1;
              puVar25[-1] = puVar24[-1];
              *puVar25 = *puVar24;
              puVar24 = puVar24 + 2;
              puVar25 = puVar25 + 0x18;
            } while (uVar28 != 0);
            *(char *)(lVar32 + uVar33 * 0x2a0 + 0x259) = (char)uVar22;
            *(ushort *)(param_1 + 0x20) = *(ushort *)(param_1 + 0x20) | 8;
            if (*(char *)(lVar34 + 0x19) == '\0') goto code_r0x022450f8;
code_r0x02244e50:
            lVar21 = lVar32 + uVar33 * 0x2a0;
            iVar9 = *(int *)(lVar34 + 0x30);
            *(undefined8 **)(lVar21 + 0x290) = puVar36;
            bVar37 = *(byte *)(lVar34 + 0x19);
            if ((ulong)bVar37 != 0) {
              puVar1 = (undefined8 *)(iVar9 + lVar34);
              uVar30 = *(undefined8 *)((long)puVar1 + 0x1c);
              lVar29 = lVar32 + uVar33 * 0x2a0;
              plVar23 = (long *)(lVar21 + 0x290);
              *(undefined8 *)((long)puVar36 + 0x24) = *(undefined8 *)((long)puVar1 + 0x24);
              *(undefined8 *)((long)puVar36 + 0x1c) = uVar30;
              uVar30 = puVar1[2];
              puVar36[3] = puVar1[3];
              puVar36[2] = uVar30;
              uVar30 = *puVar1;
              puVar36[1] = puVar1[1];
              *puVar36 = uVar30;
              uVar18 = *(undefined1 *)(puVar1 + 5);
              *(undefined1 *)(lVar29 + 0x253) = 0xff;
              *(undefined1 *)(lVar29 + 0x24a) = uVar18;
              *(undefined1 *)(*plVar23 + 0x28) = *(undefined1 *)((long)puVar1 + 0x29);
              if (1 < *(byte *)(lVar34 + 0x19)) {
                lVar27 = 0;
                lVar21 = 0;
                do {
                  uVar30 = *(undefined8 *)((long)puVar1 + lVar27 + 0x48);
                  lVar2 = *plVar23 + lVar27;
                  *(undefined8 *)(lVar2 + 0x50) = *(undefined8 *)((long)puVar1 + lVar27 + 0x50);
                  *(undefined8 *)(lVar2 + 0x48) = uVar30;
                  uVar30 = *(undefined8 *)((long)puVar1 + lVar27 + 0x3c);
                  *(undefined8 *)(lVar2 + 0x44) = *(undefined8 *)((long)puVar1 + lVar27 + 0x44);
                  *(undefined8 *)(lVar2 + 0x3c) = uVar30;
                  uVar30 = *(undefined8 *)((long)puVar1 + lVar27 + 0x2c);
                  *(undefined8 *)(lVar2 + 0x34) = *(undefined8 *)((long)puVar1 + lVar27 + 0x34);
                  *(undefined8 *)(lVar2 + 0x2c) = uVar30;
                  *(undefined1 *)(lVar32 + uVar33 * 0x2a0 + 0x24b + lVar21) =
                       *(undefined1 *)((long)puVar1 + lVar27 + 0x54);
                  *(undefined1 *)(lVar29 + 0x253) = 0xff;
                  *(undefined1 *)(*plVar23 + lVar27 + 0x54) =
                       *(undefined1 *)((long)puVar1 + lVar27 + 0x55);
                  lVar2 = lVar21 + 2;
                  lVar21 = lVar21 + 1;
                  lVar27 = lVar27 + 0x2c;
                } while (lVar2 < (long)(ulong)*(byte *)(lVar34 + 0x19));
              }
            }
            bVar6 = *(byte *)(lVar34 + 0x13);
            puVar36 = (undefined8 *)((long)puVar36 + (ulong)bVar37 * 0x2c);
          }
          else {
            *puVar31 = *puVar31 | 0x200;
            uVar35 = *(uint *)(lVar34 + 0x3c);
            if ((uVar35 >> 7 & 1) != 0) goto code_r0x02244e00;
code_r0x022450a4:
            if ((uVar35 >> 6 & 1) == 0) goto code_r0x022450a8;
code_r0x02244e14:
            *puVar31 = *puVar31 | 0x800;
            if ((*(uint *)(lVar34 + 0x3c) >> 4 & 1) != 0) goto code_r0x02244e28;
code_r0x022450ac:
            uVar22 = (ulong)*(byte *)(lVar34 + 0x28);
            if (uVar22 != 0) goto code_r0x022450b4;
code_r0x02244e48:
            if (*(char *)(lVar34 + 0x19) != '\0') goto code_r0x02244e50;
code_r0x022450f8:
            bVar6 = *(byte *)(lVar34 + 0x13);
          }
          if ((bVar6 >> 1 & 1) != 0) {
            lVar21 = lVar32 + uVar33 * 0x2a0;
            *(ushort *)(param_1 + 0x20) = *(ushort *)(param_1 + 0x20) | 0x20;
            *(undefined1 *)(lVar21 + 0x240) = *(undefined1 *)(lVar34 + 0x60);
            *(undefined4 *)(lVar21 + 0x230) = *(undefined4 *)(lVar34 + 0x50);
            *(undefined4 *)(lVar21 + 0x234) = *(undefined4 *)(lVar34 + 0x54);
            *(undefined4 *)(lVar21 + 0x238) = *(undefined4 *)(lVar34 + 0x58);
            *(undefined4 *)(lVar21 + 0x23c) = *(undefined4 *)(lVar34 + 0x5c);
          }
          if (*(short *)(**(long **)(param_5 + uVar33 * 8) + 0x1c) != 0) {
            lVar32 = lVar32 + uVar33 * 0x2a0;
            *(undefined8 **)(lVar32 + 0x298) = puVar36;
            fVar3 = *(float *)(lVar34 + 0x80);
            fVar4 = *(float *)(lVar34 + 0x84);
            fVar39 = *(float *)(lVar34 + 0x88);
            fVar5 = *(float *)(lVar34 + 0x8c);
            bVar37 = *(byte *)(lVar34 + 0xad);
            *(float *)(puVar36 + 4) = fVar3;
            *(float *)((long)puVar36 + 0x24) = fVar4;
            *(float *)(puVar36 + 5) = fVar39;
            *(float *)((long)puVar36 + 0x2c) = fVar5;
            lVar21 = *(long *)(lVar32 + 0x298);
            fVar38 = (float)NEON_ucvtf((uint)bVar37);
            fVar38 = 1.0 / fVar38;
            *(float *)(lVar21 + 0x10) = fVar38 * fVar3;
            *(float *)(lVar21 + 0x14) = fVar38 * fVar4;
            *(float *)(lVar21 + 0x18) = fVar38 * fVar39;
            *(float *)(lVar21 + 0x1c) = fVar38 * fVar5;
            fVar39 = *(float *)(lVar34 + 0x90);
            pfVar26 = *(float **)(lVar32 + 0x298);
            fVar3 = *(float *)(lVar34 + 0x9c);
            puVar36 = puVar36 + 8;
            *(undefined8 *)(pfVar26 + 1) = *(undefined8 *)(lVar34 + 0x94);
            pfVar26[3] = fVar3;
            *pfVar26 = fVar38 * fVar39;
            *(uint *)(*(long *)(lVar32 + 0x298) + 0x30) = (uint)*(byte *)(lVar34 + 0xad);
            *(undefined4 *)(*(long *)(lVar32 + 0x298) + 0x34) = *(undefined4 *)(lVar34 + 0x90);
            *(undefined4 *)(*(long *)(lVar32 + 0x298) + 0x38) = *(undefined4 *)(lVar34 + 0xa0);
          }
          uVar33 = uVar33 + 1;
        } while (uVar33 != param_4);
      }
    }
    lVar20 = *(long *)(lVar20 + 0x18);
    if (*(char *)(lVar20 + 0x26) != '\0') {
      lVar21 = 0;
      lVar32 = 0x20;
      do {
        lVar34 = *(long *)(param_1 + 0x68) + lVar32;
        lVar27 = lVar34 + -0x20;
        lVar29 = *(long *)(lVar20 + 8) + lVar32;
        *(long *)(lVar29 + -0x18) = lVar27;
        if (lVar27 != 0) {
          *(undefined8 *)(lVar29 + -0x10) = *(undefined8 *)(lVar34 + -0x10);
        }
        lVar21 = lVar21 + 1;
        *(undefined8 *)(*(long *)(lVar20 + 8) + lVar32 + 8) =
             *(undefined8 *)(*(long *)(param_1 + 0x68) + lVar32 + 8);
        plVar23 = (long *)(*(long *)(param_1 + 0x68) + lVar32);
        lVar34 = *(long *)(*(long *)(lVar20 + 8) + lVar32);
        lVar32 = lVar32 + 0x1b8;
        uVar30 = *(undefined8 *)(*plVar23 + 8);
        *(undefined1 *)(lVar34 + 0x10) = 0;
        *(undefined8 *)(lVar34 + 8) = uVar30;
      } while (lVar21 < (long)(ulong)*(byte *)(lVar20 + 0x26));
    }
    if (*(long *)(param_1 + 0xa0) != 0) {
      *(long *)(lVar20 + 0x48) = *(long *)(param_1 + 0xa0);
    }
    *(long *)(param_1 + 0xa0) = lVar20;
    *(long *)(lVar20 + 0x38) = param_1 + 0x60;
    *(ushort *)(lVar20 + 0x2f) = *(ushort *)(lVar20 + 0x2f) | 8;
  }
  return;
}

// ==== bool Aska::ShaderConstantManager::SetShaderConstantF_lockable<false>(int, int, Aska::Vector const*, int)
// vaddr 0x21452bc | ghidra 0x22452bc | size 552 | symbol _ZN4Aska21ShaderConstantManager27SetShaderConstantF_lockableILb0EEEbiiPKNS_6VectorEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska21ShaderConstantManager27SetShaderConstantF_lockableILb0EEEbiiPKNS_6VectorEi
          (long *param_1,uint param_2,uint param_3,undefined8 param_4,uint param_5)

{
  ulong *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  long *plVar10;
  long lVar11;
  ulong uVar12;
  long lVar13;
  
  uVar9 = (ulong)param_5;
  for (plVar10 = (long *)*param_1; plVar10 != (long *)0x0; plVar10 = (long *)*plVar10) {
    if (((*(ushort *)(plVar10 + 2) & 0x7fff) == param_2) &&
       ((*(byte *)((long)plVar10 + 0x13) & 0xf) == param_3)) {
      if ((short)*(ushort *)(plVar10 + 2) < 0) {
        lVar11 = Aska::TPoolFast<Aska::Vector, false>::Scoop(int)(*(undefined8 *)
                                  PTR__ZN4Aska6Global27m_pShaderConstantBufferPoolE_02cc0a58,uVar9);
        if (lVar11 == 0) {
          return 0;
        }
        plVar10[1] = lVar11;
        *(ushort *)(plVar10 + 2) = *(ushort *)(plVar10 + 2) & 0x7fff;
      }
      else {
        lVar11 = plVar10[1];
      }
      memcpy(lVar11,param_4,(ulong)*(byte *)((long)plVar10 + 0x12) << 4);
      *(byte *)((long)plVar10 + 0x13) = *(byte *)((long)plVar10 + 0x13) | 0x80;
      goto code_r0x022454b0;
    }
  }
  lVar11 = *(long *)PTR__ZN4Aska6Global27m_pShaderConstantBufferPoolE_02cc0a58;
  uVar2 = *(uint *)(lVar11 + 0x6c);
  if (*(uint *)(lVar11 + 0x84) < uVar2) {
    uVar3 = *(uint *)(lVar11 + 0x80);
    uVar12 = (ulong)uVar3;
    *(uint *)(lVar11 + 0x84) = *(uint *)(lVar11 + 0x84) + 1;
    puVar1 = (ulong *)(*(long *)(lVar11 + 0x60) + (ulong)(uVar3 >> 6) * 8);
    uVar6 = *puVar1;
    uVar7 = 1L << (uVar12 & 0x3f);
    uVar8 = uVar7 & uVar6;
    while (uVar8 != 0) {
      uVar3 = (int)uVar12 + 1;
      uVar4 = 0;
      if (uVar2 != 0) {
        uVar4 = uVar3 / uVar2;
      }
      uVar3 = uVar3 - uVar4 * uVar2;
      uVar12 = (ulong)uVar3;
      puVar1 = (ulong *)(*(long *)(lVar11 + 0x60) + (ulong)(uVar3 >> 6) * 8);
      uVar6 = *puVar1;
      uVar7 = 1L << (uVar3 & 0x3f);
      uVar8 = uVar7 & uVar6;
    }
    *puVar1 = uVar7 | uVar6;
    lVar13 = *(long *)(lVar11 + 0x78);
    uVar4 = 0;
    if (uVar2 != 0) {
      uVar4 = (uVar3 + 1) / uVar2;
    }
    plVar10 = (long *)(lVar13 + (ulong)uVar3 * 0x18);
    *(uint *)(lVar11 + 0x80) = (uVar3 + 1) - uVar4 * uVar2;
    if (plVar10 != (long *)0x0) {
      lVar5 = Aska::TPoolFast<Aska::Vector, false>::Scoop(int)(lVar11,uVar9);
      if (lVar5 == 0) {
        uVar9 = ((long)plVar10 - *(long *)(lVar11 + 0x78) >> 3) * -0x5555555555555555;
        lVar13 = (uVar9 >> 6 & 0x3ffffff) * 8;
        *(ulong *)(*(long *)(lVar11 + 0x60) + lVar13) =
             *(ulong *)(*(long *)(lVar11 + 0x60) + lVar13) &
             (1L << (uVar9 & 0x3f) ^ 0xffffffffffffffffU);
        *(int *)(lVar11 + 0x84) = *(int *)(lVar11 + 0x84) + -1;
        return 0;
      }
      lVar13 = lVar13 + (ulong)uVar3 * 0x18;
      *plVar10 = *param_1;
      *(long *)(lVar13 + 8) = lVar5;
      *(ushort *)(lVar13 + 0x10) = (ushort)param_2 & 0x7fff;
      *(char *)(lVar13 + 0x12) = (char)param_5;
      *(byte *)(lVar13 + 0x13) = (byte)param_3 & 0xf | 0x80;
      *param_1 = (long)plVar10;
      memcpy(lVar5,param_4,-(ulong)(param_5 >> 0x1f) & 0xfffffff000000000 | uVar9 << 4);
code_r0x022454b0:
      *(short *)((long)param_1 + 0x1a) = *(short *)((long)param_1 + 0x1a) + 1;
      *(byte *)((long)param_1 + 0x1c) = *(byte *)((long)param_1 + 0x1c) | 1;
      return 1;
    }
  }
  return 0;
}

// ==== Aska::MaterialList::Create(int)
// vaddr 0x21454e4 | ghidra 0x22454e4 | size 680 | symbol _ZN4Aska12MaterialList6CreateEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska12MaterialList6CreateEi(long *param_1,uint param_2)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  long *plVar4;
  ushort uVar5;
  ulong uVar6;
  undefined8 uVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long *plVar11;
  long lVar12;
  undefined8 *puVar13;
  long lVar14;
  
  if ((((int)param_1[0xb] != 0) && (lVar9 = param_1[10], lVar9 != 0)) &&
     (uVar3 = Aska::RenderPassManager::Init(int)(lVar9,param_2), (uVar3 & 1) != 0)) {
    param_1[6] = (long)(param_1 + 0xc);
    uVar3 = Aska::RenderPass::Init(int, void*)(param_1 + 0xc,param_2,0);
    if (((uVar3 & 1) != 0) && (uVar3 = Aska::RenderPass::Create(int)(param_1[6],1), (uVar3 & 1) != 0)) {
      plVar4 = (long *)operator new[](unsigned long, std::nothrow_t const&)((long)(int)((param_2 * 0x480 | 0x30) + param_2 * 0x2c),
                                       PTR__ZSt7nothrow_02cb9a80);
      *param_1 = (long)plVar4;
      if (plVar4 != (long *)0x0) {
        if (param_2 != 0) {
          plVar11 = plVar4 + 2;
          lVar14 = (long)(int)param_2 * 0x2a0;
          do {
            Aska::MaterialContext::MaterialContext()(plVar11);
            lVar14 = lVar14 + -0x2a0;
            plVar11 = plVar11 + 0x54;
          } while (lVar14 != 0);
        }
        uVar3 = (long)plVar4 + (long)(int)param_2 * 0x2a0 + 0xf & 0xfffffffffffffff0;
        lVar14 = uVar3 + (long)(int)(param_2 * 0xc0);
        *(undefined1 *)((long)param_1 + 0x22) = 0;
        param_1[1] = lVar14;
        param_1[2] = uVar3;
        param_1[3] = (long)plVar4;
        *(char *)((long)param_1 + 0x23) = (char)param_2;
        if (0 < (int)param_2) {
          lVar14 = lVar14 + 0x10;
          uVar6 = (ulong)param_2;
          lVar12 = 0;
          lVar10 = 0x20;
          puVar13 = (undefined8 *)(lVar14 + (long)(int)param_2 * 0x120);
          while( true ) {
            uVar6 = uVar6 - 1;
            *plVar4 = uVar3 + lVar12;
            *(ushort *)((long)plVar4 + 0x255) = *(ushort *)((long)plVar4 + 0x255) | 1;
            plVar4[0x52] = (long)puVar13;
            *(undefined1 *)(puVar13 + 5) = 0;
            puVar13[4] = 0;
            puVar13[1] = 0;
            *puVar13 = 0;
            puVar13[3] = 0;
            puVar13[2] = 0;
            Aska::ShaderNodeModifier::Create(int, void*)(*(undefined8 *)(*(long *)(param_1[6] + 8) + lVar10),0x120,lVar14);
            *(undefined1 *)(*plVar4 + 0x13) = 0;
            if (uVar6 == 0) break;
            uVar3 = param_1[2];
            puVar13 = (undefined8 *)((long)puVar13 + 0x2c);
            lVar12 = lVar12 + 0xc0;
            lVar10 = lVar10 + 0x1b8;
            lVar14 = lVar14 + 0x120;
            plVar4 = plVar4 + 0x54;
          }
        }
        lVar9 = *(long *)(lVar9 + 0x18);
        if ((lVar9 != 0) && (uVar3 = Aska::RenderPass::Create(int)(lVar9,1), (uVar3 & 1) != 0)) {
          lVar14 = param_1[6];
          if (*(char *)(lVar9 + 0x26) != '\0') {
            lVar12 = 0;
            lVar10 = 0x20;
            do {
              lVar8 = *(long *)(lVar14 + 8) + lVar10;
              lVar2 = lVar8 + -0x20;
              lVar1 = *(long *)(lVar9 + 8) + lVar10;
              *(long *)(lVar1 + -0x18) = lVar2;
              if (lVar2 != 0) {
                *(undefined8 *)(lVar1 + -0x10) = *(undefined8 *)(lVar8 + -0x10);
              }
              lVar12 = lVar12 + 1;
              *(undefined8 *)(*(long *)(lVar9 + 8) + lVar10 + 8) =
                   *(undefined8 *)(*(long *)(lVar14 + 8) + lVar10 + 8);
              plVar4 = (long *)(*(long *)(lVar14 + 8) + lVar10);
              lVar8 = *(long *)(*(long *)(lVar9 + 8) + lVar10);
              lVar10 = lVar10 + 0x1b8;
              uVar7 = *(undefined8 *)(*plVar4 + 8);
              *(undefined1 *)(lVar8 + 0x10) = 0;
              *(undefined8 *)(lVar8 + 8) = uVar7;
            } while (lVar12 < (long)(ulong)*(byte *)(lVar9 + 0x26));
          }
          if (*(long *)(lVar14 + 0x40) != 0) {
            *(long *)(lVar9 + 0x48) = *(long *)(lVar14 + 0x40);
          }
          *(long *)(lVar14 + 0x40) = lVar9;
          *(long *)(lVar9 + 0x38) = lVar14;
          *(ushort *)(lVar9 + 0x2f) = *(ushort *)(lVar9 + 0x2f) | 8;
          *(ushort *)(param_1 + 4) = *(ushort *)(param_1 + 4) | 2;
          return 1;
        }
      }
    }
  }
  uVar5 = *(ushort *)(param_1 + 4);
  if ((uVar5 & 3) != 0) {
    if (param_1[3] != 0) {
      if (*param_1 != 0) {
        operator delete[](void*)();
        uVar5 = *(ushort *)(param_1 + 4);
        *param_1 = 0;
      }
      *(undefined2 *)((long)param_1 + 0x22) = 0;
      param_1[2] = 0;
      param_1[3] = 0;
      param_1[1] = 0;
    }
    *(ushort *)(param_1 + 4) = uVar5 & 0xfffc;
  }
  return 0;
}

// ==== Aska::MaterialList::Clone(Aska::MaterialList const*, bool)
// vaddr 0x214578c | ghidra 0x224578c | size 4 | symbol _ZN4Aska12MaterialList5CloneEPKS0_b | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList5CloneEPKS0_b(void)

{
  return;
}

// ==== Aska::MaterialList::SetDirectMaterial(int, Aska::DirectMaterial*, Aska::RenderablePrimitive*, unsigned long)
// vaddr 0x2145790 | ghidra 0x2245790 | size 1756 | symbol _ZN4Aska12MaterialList17SetDirectMaterialEiPNS_14DirectMaterialEPNS_19RenderablePrimitiveEm | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12MaterialList17SetDirectMaterialEiPNS_14DirectMaterialEPNS_19RenderablePrimitiveEm
               (long param_1,int param_2,undefined2 *param_3,undefined8 param_4,undefined8 param_5)

{
  ushort *puVar1;
  byte bVar2;
  ushort uVar3;
  bool bVar4;
  ushort uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  undefined8 *puVar10;
  long lVar11;
  ulong uVar12;
  long lVar13;
  long lVar14;
  byte *pbVar15;
  undefined8 uVar16;
  char cVar17;
  long lVar18;
  long lVar19;
  long lVar20;
  long *plVar21;
  long *plVar22;
  float fVar23;
  undefined1 auVar24 [16];
  float fVar25;
  uint uStack_dc;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  long lStack_a0;
  long lStack_98;
  long lStack_90;
  long lStack_88;
  undefined8 uStack_80;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  lVar19 = *(long *)(param_1 + 0x18);
  plVar21 = (long *)(lVar19 + (long)param_2 * 0x2a0);
  lVar11 = *plVar21;
  *(undefined1 *)(lVar11 + 0x16) = 0;
  *(undefined1 *)(lVar11 + 0x1a) = 0;
  *(undefined1 *)(lVar11 + 0x14) = *(undefined1 *)((long)param_3 + 3);
  lVar18 = (long)param_2;
  *(undefined2 *)(lVar11 + 0x10) = *param_3;
  *(undefined1 *)(lVar11 + 0x15) = *(undefined1 *)((long)param_3 + 5);
  *(undefined2 *)((long)plVar21 + 0x241) = 0;
  *(undefined1 *)((long)plVar21 + 599) = 0;
  *(char *)((long)plVar21 + 0x2c) = '\0';
  uVar5 = *(ushort *)((long)param_3 + 0xf);
  plVar22 = plVar21 + 6;
  plVar21[7] = 0;
  *plVar22 = 0;
  puVar1 = (ushort *)((long)plVar21 + 0x255);
  uVar3 = *puVar1;
  uVar5 = uVar5 & 4;
  *puVar1 = uVar5 | uVar3 & 0xfffb;
  plVar21[9] = 0;
  plVar21[8] = 0;
  uVar5 = uVar5 | uVar3 & 0xfb | (*(ushort *)((long)param_3 + 0xf) >> 7 & 1) << 8;
  *puVar1 = uVar3 & 0xfe00 | uVar5;
  *puVar1 = uVar3 & 0xbc00 | uVar5 | (*(ushort *)((long)param_3 + 0xf) >> 8 & 1) << 9;
  lVar14 = *(long *)(param_1 + 0x68) + (long)param_2 * 0x1b8;
  *(ushort *)(param_1 + 0x20) =
       (*(ushort *)((long)param_3 + 0xf) & 0x80) << 2 | *(ushort *)(param_1 + 0x20);
  *(undefined8 *)(lVar14 + 0x28) = param_4;
  puVar10 = *(undefined8 **)(param_3 + 0x50);
  lVar20 = *(long *)(lVar14 + 0x20);
  if (puVar10 == (undefined8 *)0x0) {
    if (*(long *)(param_3 + 0x30) == 0) {
      cVar17 = '\0';
      lVar11 = *(long *)(param_3 + 0x38);
      if (lVar11 != 0) goto code_r0x0224593c;
code_r0x02245998:
      uStack_dc = 0;
      bVar2 = *(byte *)(param_3 + 8);
    }
    else {
      *plVar22 = *(long *)(param_3 + 0x30);
      cVar17 = '\x01';
      lVar11 = lVar19 + lVar18 * 0x2a0;
      plVar22 = (long *)(lVar11 + 0x50);
      *(undefined8 *)(lVar11 + 0x38) = *(undefined8 *)(param_3 + 0x34);
      lVar11 = *(long *)(param_3 + 0x38);
      if (lVar11 == 0) goto code_r0x02245998;
code_r0x0224593c:
      *plVar22 = lVar11;
      cVar17 = cVar17 + '\x01';
      plVar22[1] = *(long *)(param_3 + 0x3c);
      plVar22 = plVar22 + 4;
      if ((*(byte *)(param_3 + 8) >> 2 & 1) != 0) goto code_r0x02245998;
      uStack_a8 = (undefined2 *)((ulong)uStack_a8 & 0xffffffff);
      uStack_dc = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(*(long *)(param_1 + 0x68) + lVar18 * 0x1b8,5,2,&uStack_b0,1);
      bVar2 = *(byte *)(param_3 + 8);
    }
    if (((bVar2 >> 2 & 1) != 0) && (*(long *)(param_3 + 0x40) != 0)) {
      *plVar22 = *(long *)(param_3 + 0x40);
      cVar17 = cVar17 + '\x01';
      plVar22[1] = *(long *)(param_3 + 0x44);
      plVar22 = plVar22 + 4;
      uVar5 = Aska::detail::CanUseFontVTF(Aska::DirectMaterial const&)(param_3);
      *puVar1 = *puVar1 & 0x8000 | *puVar1 & 0x3fff | (uVar5 & 1) << 0xe;
    }
    if (*(long *)(param_3 + 0x48) != 0) {
      *plVar22 = *(long *)(param_3 + 0x48);
      cVar17 = cVar17 + '\x01';
      plVar22[1] = *(long *)(param_3 + 0x4c);
    }
    *(char *)((long)plVar21 + 599) = cVar17;
    *(char *)((long)plVar21 + 0x2c) = cVar17;
    *(ushort *)(param_1 + 0x20) =
         (*(ushort *)((long)param_3 + 0xf) & 1) << 4 | *(ushort *)(param_1 + 0x20);
    uVar12 = (ulong)*(byte *)((long)param_3 + 0xd);
    if (uVar12 != 0xff) {
      lVar13 = lVar19 + lVar18 * 0x2a0;
      *(byte *)(lVar13 + uVar12 + 0x24a) = *(byte *)((long)param_3 + 0xd);
      *(undefined1 *)(lVar13 + 0x253) = 0xff;
      lVar11 = uVar12 * 0x2c;
      *(undefined4 *)(*(long *)(lVar13 + 0x290) + lVar11) = 0x3f800000;
      *(undefined4 *)(*(long *)(lVar13 + 0x290) + lVar11 + 4) = 0x3f800000;
      *(undefined4 *)(*(long *)(lVar13 + 0x290) + lVar11 + 8) = 0;
      *(undefined4 *)(*(long *)(lVar13 + 0x290) + lVar11 + 0xc) = 0;
      *(undefined4 *)(*(long *)(lVar13 + 0x290) + lVar11 + 0x10) = 0;
      *(undefined4 *)(*(long *)(lVar13 + 0x290) + lVar11 + 0x14) = 0x3f800000;
      *(undefined4 *)(*(long *)(lVar13 + 0x290) + lVar11 + 0x18) = 0x3f800000;
      *(undefined4 *)(*(long *)(lVar13 + 0x290) + lVar11 + 0x1c) = 0;
      *(undefined4 *)(*(long *)(lVar13 + 0x290) + lVar11 + 0x20) = 0;
      *(undefined4 *)(*(long *)(lVar13 + 0x290) + lVar11 + 0x24) = 0;
    }
    *(undefined1 *)((long)plVar21 + 0x241) = *(undefined1 *)(param_3 + 7);
    *(undefined4 *)(lVar19 + lVar18 * 0x2a0 + 0x244) = *(undefined4 *)(param_3 + 4);
    Aska::DirectShaderNode::MakeDirectMaterial(Aska::DirectMaterial*, unsigned long)(lVar20,param_3,param_5);
    if ((*(byte *)((long)param_3 + 0xf) & 1) != 0) {
      uVar9 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar14,5,0,param_3 + 0x20,1);
      uVar6 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar14,2,0,param_3 + 0x18,1);
      uVar7 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar14,0x13,0,param_3 + 0x18,1);
      uVar8 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar14,5,1,param_3 + 0x28,1);
      uStack_dc = uStack_dc | uVar9 | uVar6 | uVar7 | uVar8;
    }
    uVar6 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar14,0x14,0,param_3 + 0x10,1);
    auVar24 = NEON_fmov(0x3f800000,4);
    uStack_70 = 0;
    uStack_68 = 0;
    lVar11 = *(long *)(param_1 + 0x68) + lVar18 * 0x1b8;
    uStack_b0 = auVar24._0_8_;
    uStack_a8 = auVar24._8_8_;
    uVar7 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar11,5,3,&uStack_b0,1);
    uVar8 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar11,5,4,&uStack_70,1);
    uStack_a8 = UNK_027f44a0._8_8_;
    uStack_b0 = (undefined8)UNK_027f44a0;
    lStack_98 = _UNK_027ed898;
    lStack_a0 = _UNK_027ed890;
    uVar9 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(*(long *)(param_1 + 0x68) + lVar18 * 0x1b8,0x40,0,&uStack_b0,2);
    uVar9 = uStack_dc | uVar6 | uVar7 | uVar8 | uVar9;
    if ((*(byte *)(param_3 + 8) >> 2 & 1) != 0) {
      uVar16 = *(undefined8 *)(param_3 + 0x30);
      lVar19 = *(long *)PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
      lVar11 = lVar19 + 0xb0;
      Aska::CriticalSection::Enter() const(lVar11);
      lVar19 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar19,uVar16,1);
      Aska::CriticalSection::Leave() const(lVar11);
      uStack_b0 = auVar24._0_8_;
      uStack_a8 = auVar24._8_8_;
      if (lVar19 != 0) {
        fVar23 = (float)NEON_ucvtf((uint)*(ushort *)(lVar19 + 0x18));
        fVar25 = (float)NEON_ucvtf((uint)*(ushort *)(lVar19 + 0x1a));
        uStack_b0 = CONCAT44(fVar25,fVar23);
        uStack_a8 = (undefined2 *)CONCAT44(1.0 / fVar25,1.0 / fVar23);
      }
      uVar6 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar14,0x5d,0,&uStack_b0,1);
      uVar9 = uVar9 | uVar6;
    }
  }
  else {
    lStack_90 = lVar19 + lVar18 * 0x2a0 + 0x10;
    uStack_b0 = CONCAT71(uStack_b0._1_7_,(char)param_2);
    uStack_a8 = param_3;
    lStack_a0 = lVar20;
    lStack_98 = lVar14;
    lStack_88 = lVar11;
    uStack_80 = param_4;
    (**(code **)*puVar10)(puVar10,&uStack_b0);
    lVar11 = Aska::ShaderNodeModifier::SearchBeforeShading(Aska::ShaderNodeChunk*)(lVar20,*(undefined8 *)(lVar20 + 8));
    uVar9 = 1;
    *(ushort *)(param_1 + 0x20) =
         *(ushort *)(param_1 + 0x20) & 0xffe0 |
         *(ushort *)(param_1 + 0x20) & 0xf | (ushort)(lVar11 != 0) << 4;
  }
  uVar5 = *puVar1;
  if ((((*(ushort *)(param_1 + 0x20) >> 8 & 1) != 0) && ((uVar3 >> 2 & 1) != 0)) &&
     ((uVar5 >> 2 & 1) == 0)) {
    uVar5 = 0;
    if ((ulong)*(byte *)(param_1 + 0x22) == 0) goto code_r0x02245d14;
    uVar5 = uRam0000000000000245;
    if (*(long *)(param_1 + 0x18) != 0) {
      lVar11 = 0;
      pbVar15 = (byte *)(*(long *)(param_1 + 0x18) + 0x255);
      do {
        if ((*pbVar15 >> 2 & 1) != 0) {
          uVar5 = 0x100;
          goto code_r0x02245d14;
        }
        lVar11 = lVar11 + 1;
        pbVar15 = pbVar15 + 0x2a0;
      } while (lVar11 < (long)(ulong)*(byte *)(param_1 + 0x22));
      uVar5 = 0;
      goto code_r0x02245d14;
    }
  }
  uVar5 = (uVar5 & 4) << 6;
code_r0x02245d14:
  lVar14 = *(long *)(param_1 + 0x50);
  lVar11 = param_1 + 0x40;
  *(ushort *)(param_1 + 0x20) = *(ushort *)(param_1 + 0x20) & 0xfeff | uVar5;
  for (; lVar11 != lVar14; lVar14 = *(long *)(lVar14 + 0x10)) {
    Aska::RenderPassManager::SetPrimitive(int, Aska::RenderablePrimitive*)(lVar14,param_2,param_4);
    Aska::RenderPassManager::InvalidateShaders(bool)(lVar14,1);
  }
  puVar1 = (ushort *)(*(long *)(param_1 + 0x18) + lVar18 * 0x2a0 + 0x255);
  *puVar1 = *puVar1 | 1;
  uVar5 = *(ushort *)(param_1 + 0x20);
  if ((uVar5 >> 2 & 1) == 0) {
    *(ushort *)(param_1 + 0x8f) = *(ushort *)(param_1 + 0x8f) | 1;
    if (*(long *)(param_1 + 0xa0) != 0) {
      bVar4 = false;
      lVar14 = *(long *)(param_1 + 0xa0);
code_r0x02245da0:
      do {
        do {
          lVar18 = lVar14;
          if (!bVar4) {
            bVar4 = false;
            *(ushort *)(lVar18 + 0x2f) = *(ushort *)(lVar18 + 0x2f) | 1;
            lVar14 = *(long *)(lVar18 + 0x40);
            if (*(long *)(lVar18 + 0x40) != 0) goto code_r0x02245da0;
          }
          bVar4 = false;
          lVar14 = *(long *)(lVar18 + 0x48);
        } while (*(long *)(lVar18 + 0x48) != 0);
        bVar4 = true;
        lVar14 = *(long *)(lVar18 + 0x38);
      } while (*(long *)(lVar18 + 0x38) != param_1 + 0x60);
      uVar5 = *(ushort *)(param_1 + 0x20);
    }
    *(ushort *)(param_1 + 0x20) = uVar5 | 4;
  }
  for (lVar14 = *(long *)(param_1 + 0x50); lVar11 != lVar14; lVar14 = *(long *)(lVar14 + 0x10)) {
    Aska::RenderPassManager::InvalidateRenderState()(lVar14);
    Aska::RenderPassManager::InvalidateCommandBufferManager()(lVar14);
  }
  if ((uVar9 & 1) != 0) {
    for (lVar14 = *(long *)(param_1 + 0x50); lVar11 != lVar14; lVar14 = *(long *)(lVar14 + 0x10)) {
      Aska::RenderPass::InvalidateShaders()(*(undefined8 *)(lVar14 + 0x18));
      Aska::RenderPassManager::InvalidateShaders(bool)(lVar14,0);
    }
  }
  return;
}

// ==== Aska::MaterialList::SetTexSelector_(int, float)
// vaddr 0x2145e6c | ghidra 0x2245e6c | size 60 | symbol _ZN4Aska12MaterialList15SetTexSelector_Eif | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska12MaterialList15SetTexSelector_Eif(undefined4 param_1,long param_2,int param_3)

{
  uint uVar1;
  undefined1 auStack_20 [12];
  undefined4 uStack_14;
  
  uStack_14 = param_1;
  uVar1 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(*(long *)(param_2 + 0x68) + (long)param_3 * 0x1b8,5,2,auStack_20,1);
  return uVar1 & 1;
}

// ==== Aska::MaterialList::SetColorMultiplier_(int, Aska::Vector const&, Aska::Vector const&)
// vaddr 0x2145ea8 | ghidra 0x2245ea8 | size 100 | symbol _ZN4Aska12MaterialList19SetColorMultiplier_EiRKNS_6VectorES3_ | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska12MaterialList19SetColorMultiplier_EiRKNS_6VectorES3_
               (long param_1,int param_2,undefined8 param_3,undefined8 param_4)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0x68) + (long)param_2 * 0x1b8;
  uVar1 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar3,5,3,param_3,1);
  uVar2 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar3,5,4,param_4,1);
  return (uVar1 | uVar2) & 1;
}

// ==== Aska::MaterialList::SetUVMatrix_(int, Aska::Matrix const&)
// vaddr 0x2145f0c | ghidra 0x2245f0c | size 40 | symbol _ZN4Aska12MaterialList12SetUVMatrix_EiRKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList12SetUVMatrix_EiRKNS_6MatrixE
               (long param_1,int param_2,undefined8 param_3)

{
  (*(code *)PTR__ZN4Aska21ShaderConstantManager20SetShaderConstantFUCEiiPKNS_6VectorEi_02c97380)
            (*(long *)(param_1 + 0x68) + (long)param_2 * 0x1b8,0x40,0,param_3,2);
  return;
}

// ==== Aska::MaterialList::SetMaterialColor(int, Aska::Vector*)
// vaddr 0x2145f34 | ghidra 0x2245f34 | size 24 | symbol _ZN4Aska12MaterialList16SetMaterialColorEiPNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList16SetMaterialColorEiPNS_6VectorE
               (undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  (*(code *)PTR__ZN4Aska12MaterialList18SetShaderConstantFEiiiPKNS_6VectorEi_02c90a78)
            (param_1,param_2,0x14,0,param_3,1);
  return;
}

// ==== Aska::MaterialList::SetShaderConstantF(int, int, int, Aska::Vector const*, int)
// vaddr 0x2145f4c | ghidra 0x2245f4c | size 260 | symbol _ZN4Aska12MaterialList18SetShaderConstantFEiiiPKNS_6VectorEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList18SetShaderConstantFEiiiPKNS_6VectorEi
               (long param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined8 param_5,
               undefined4 param_6)

{
  ushort *puVar1;
  bool bVar2;
  ulong uVar3;
  ushort uVar4;
  long lVar5;
  long lVar6;
  
  uVar3 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(*(long *)(param_1 + 0x68) + (long)param_2 * 0x1b8,param_3,param_4,param_5,
                          param_6);
  if ((uVar3 & 1) != 0) {
    puVar1 = (ushort *)(*(long *)(param_1 + 0x18) + (long)param_2 * 0x2a0 + 0x255);
    *puVar1 = *puVar1 | 1;
    uVar4 = *(ushort *)(param_1 + 0x20);
    if ((uVar4 >> 2 & 1) == 0) {
      *(ushort *)(param_1 + 0x8f) = *(ushort *)(param_1 + 0x8f) | 1;
      if (*(long *)(param_1 + 0xa0) != 0) {
        bVar2 = false;
        lVar6 = *(long *)(param_1 + 0xa0);
code_r0x02245fc8:
        do {
          do {
            lVar5 = lVar6;
            if (!bVar2) {
              bVar2 = false;
              *(ushort *)(lVar5 + 0x2f) = *(ushort *)(lVar5 + 0x2f) | 1;
              lVar6 = *(long *)(lVar5 + 0x40);
              if (*(long *)(lVar5 + 0x40) != 0) goto code_r0x02245fc8;
            }
            bVar2 = false;
            lVar6 = *(long *)(lVar5 + 0x48);
          } while (*(long *)(lVar5 + 0x48) != 0);
          bVar2 = true;
          lVar6 = *(long *)(lVar5 + 0x38);
        } while (*(long *)(lVar5 + 0x38) != param_1 + 0x60);
        uVar4 = *(ushort *)(param_1 + 0x20);
      }
      *(ushort *)(param_1 + 0x20) = uVar4 | 4;
    }
    for (lVar6 = *(long *)(param_1 + 0x50); param_1 + 0x40 != lVar6; lVar6 = *(long *)(lVar6 + 0x10)
        ) {
      Aska::RenderPass::InvalidateShaders()(*(undefined8 *)(lVar6 + 0x18));
      Aska::RenderPassManager::InvalidateShaders(bool)(lVar6,0);
    }
  }
  return;
}

// ==== Aska::MaterialList::SetTexSelector(int, float)
// vaddr 0x2146050 | ghidra 0x2246050 | size 272 | symbol _ZN4Aska12MaterialList14SetTexSelectorEif | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList14SetTexSelectorEif(undefined4 param_1,long param_2,int param_3)

{
  ushort *puVar1;
  bool bVar2;
  ulong uVar3;
  ushort uVar4;
  long lVar5;
  long lVar6;
  undefined1 auStack_30 [12];
  undefined4 uStack_24;
  
  uStack_24 = param_1;
  uVar3 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(*(long *)(param_2 + 0x68) + (long)param_3 * 0x1b8,5,2,auStack_30,1);
  if ((uVar3 & 1) != 0) {
    puVar1 = (ushort *)(*(long *)(param_2 + 0x18) + (long)param_3 * 0x2a0 + 0x255);
    *puVar1 = *puVar1 | 1;
    uVar4 = *(ushort *)(param_2 + 0x20);
    if ((uVar4 >> 2 & 1) == 0) {
      *(ushort *)(param_2 + 0x8f) = *(ushort *)(param_2 + 0x8f) | 1;
      if (*(long *)(param_2 + 0xa0) != 0) {
        bVar2 = false;
        lVar6 = *(long *)(param_2 + 0xa0);
code_r0x022460d4:
        do {
          do {
            lVar5 = lVar6;
            if (!bVar2) {
              bVar2 = false;
              *(ushort *)(lVar5 + 0x2f) = *(ushort *)(lVar5 + 0x2f) | 1;
              lVar6 = *(long *)(lVar5 + 0x40);
              if (*(long *)(lVar5 + 0x40) != 0) goto code_r0x022460d4;
            }
            bVar2 = false;
            lVar6 = *(long *)(lVar5 + 0x48);
          } while (*(long *)(lVar5 + 0x48) != 0);
          bVar2 = true;
          lVar6 = *(long *)(lVar5 + 0x38);
        } while (*(long *)(lVar5 + 0x38) != param_2 + 0x60);
        uVar4 = *(ushort *)(param_2 + 0x20);
      }
      *(ushort *)(param_2 + 0x20) = uVar4 | 4;
    }
    for (lVar6 = *(long *)(param_2 + 0x50); param_2 + 0x40 != lVar6; lVar6 = *(long *)(lVar6 + 0x10)
        ) {
      Aska::RenderPass::InvalidateShaders()(*(undefined8 *)(lVar6 + 0x18));
      Aska::RenderPassManager::InvalidateShaders(bool)(lVar6,0);
    }
  }
  return;
}

// ==== Aska::MaterialList::SetColorMultiplier(int, Aska::Vector const&, Aska::Vector const&)
// vaddr 0x2146160 | ghidra 0x2246160 | size 312 | symbol _ZN4Aska12MaterialList18SetColorMultiplierEiRKNS_6VectorES3_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList18SetColorMultiplierEiRKNS_6VectorES3_
               (long param_1,int param_2,undefined8 param_3,undefined8 param_4)

{
  ushort *puVar1;
  bool bVar2;
  ulong uVar3;
  ulong uVar4;
  ushort uVar5;
  long lVar6;
  long lVar7;
  
  lVar7 = *(long *)(param_1 + 0x68) + (long)param_2 * 0x1b8;
  uVar3 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar7,5,3,param_3,1);
  uVar4 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(lVar7,5,4,param_4,1);
  if (((uVar3 & 1) != 0) || ((uVar4 & 1) != 0)) {
    puVar1 = (ushort *)(*(long *)(param_1 + 0x18) + (long)param_2 * 0x2a0 + 0x255);
    *puVar1 = *puVar1 | 1;
    uVar5 = *(ushort *)(param_1 + 0x20);
    if ((uVar5 >> 2 & 1) == 0) {
      *(ushort *)(param_1 + 0x8f) = *(ushort *)(param_1 + 0x8f) | 1;
      if (*(long *)(param_1 + 0xa0) != 0) {
        bVar2 = false;
        lVar7 = *(long *)(param_1 + 0xa0);
code_r0x0224620c:
        do {
          do {
            lVar6 = lVar7;
            if (!bVar2) {
              bVar2 = false;
              *(ushort *)(lVar6 + 0x2f) = *(ushort *)(lVar6 + 0x2f) | 1;
              lVar7 = *(long *)(lVar6 + 0x40);
              if (*(long *)(lVar6 + 0x40) != 0) goto code_r0x0224620c;
            }
            bVar2 = false;
            lVar7 = *(long *)(lVar6 + 0x48);
          } while (*(long *)(lVar6 + 0x48) != 0);
          bVar2 = true;
          lVar7 = *(long *)(lVar6 + 0x38);
        } while (*(long *)(lVar6 + 0x38) != param_1 + 0x60);
        uVar5 = *(ushort *)(param_1 + 0x20);
      }
      *(ushort *)(param_1 + 0x20) = uVar5 | 4;
    }
    for (lVar7 = *(long *)(param_1 + 0x50); param_1 + 0x40 != lVar7; lVar7 = *(long *)(lVar7 + 0x10)
        ) {
      Aska::RenderPass::InvalidateShaders()(*(undefined8 *)(lVar7 + 0x18));
      Aska::RenderPassManager::InvalidateShaders(bool)(lVar7,0);
    }
  }
  return;
}

// ==== Aska::MaterialList::SetUVMatrix(int, Aska::Matrix const&)
// vaddr 0x2146298 | ghidra 0x2246298 | size 264 | symbol _ZN4Aska12MaterialList11SetUVMatrixEiRKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList11SetUVMatrixEiRKNS_6MatrixE(long param_1,int param_2,undefined8 param_3)

{
  ushort *puVar1;
  bool bVar2;
  ulong uVar3;
  ushort uVar4;
  long lVar5;
  long lVar6;
  
  uVar3 = Aska::ShaderConstantManager::SetShaderConstantFUC(int, int, Aska::Vector const*, int)(*(long *)(param_1 + 0x68) + (long)param_2 * 0x1b8,0x40,0,param_3,2);
  if ((uVar3 & 1) != 0) {
    puVar1 = (ushort *)(*(long *)(param_1 + 0x18) + (long)param_2 * 0x2a0 + 0x255);
    *puVar1 = *puVar1 | 1;
    uVar4 = *(ushort *)(param_1 + 0x20);
    if ((uVar4 >> 2 & 1) == 0) {
      *(ushort *)(param_1 + 0x8f) = *(ushort *)(param_1 + 0x8f) | 1;
      if (*(long *)(param_1 + 0xa0) != 0) {
        bVar2 = false;
        lVar6 = *(long *)(param_1 + 0xa0);
code_r0x02246318:
        do {
          do {
            lVar5 = lVar6;
            if (!bVar2) {
              bVar2 = false;
              *(ushort *)(lVar5 + 0x2f) = *(ushort *)(lVar5 + 0x2f) | 1;
              lVar6 = *(long *)(lVar5 + 0x40);
              if (*(long *)(lVar5 + 0x40) != 0) goto code_r0x02246318;
            }
            bVar2 = false;
            lVar6 = *(long *)(lVar5 + 0x48);
          } while (*(long *)(lVar5 + 0x48) != 0);
          bVar2 = true;
          lVar6 = *(long *)(lVar5 + 0x38);
        } while (*(long *)(lVar5 + 0x38) != param_1 + 0x60);
        uVar4 = *(ushort *)(param_1 + 0x20);
      }
      *(ushort *)(param_1 + 0x20) = uVar4 | 4;
    }
    for (lVar6 = *(long *)(param_1 + 0x50); param_1 + 0x40 != lVar6; lVar6 = *(long *)(lVar6 + 0x10)
        ) {
      Aska::RenderPass::InvalidateShaders()(*(undefined8 *)(lVar6 + 0x18));
      Aska::RenderPassManager::InvalidateShaders(bool)(lVar6,0);
    }
  }
  return;
}

// ==== Aska::MaterialList::GetActualPerPixelLightCount() const
// vaddr 0x21463a0 | ghidra 0x22463a0 | size 20 | symbol _ZNK4Aska12MaterialList27GetActualPerPixelLightCountEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK4Aska12MaterialList27GetActualPerPixelLightCountEv(long param_1)

{
  int iVar1;
  
  iVar1 = 3;
  if (*(char *)(param_1 + 0x24) != -1) {
    iVar1 = (int)*(char *)(param_1 + 0x24);
  }
  return iVar1;
}

// ==== Aska::MaterialList::EnableAmbientBRDF(Aska::MaterialList::AmbientBRDFType)
// vaddr 0x21463b4 | ghidra 0x22463b4 | size 376 | symbol _ZN4Aska12MaterialList17EnableAmbientBRDFENS0_15AmbientBRDFTypeE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList17EnableAmbientBRDFENS0_15AmbientBRDFTypeE(long param_1,int param_2)

{
  long lVar1;
  byte bVar2;
  char cVar3;
  ushort uVar4;
  int iVar5;
  ulong uVar6;
  long lVar7;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  bVar2 = *(byte *)(param_1 + 0x22);
  uVar6 = (ulong)bVar2;
  if (param_2 == 0) {
    if (bVar2 != 0) {
      lVar7 = 0x10;
      do {
        lVar1 = 0;
        if (*(long *)(param_1 + 0x18) != 0) {
          lVar1 = *(long *)(param_1 + 0x18) + lVar7;
        }
        if ((*(byte *)(lVar1 + 0x246) & 1) != 0) {
          Aska::MaterialContext::RemoveShaderTexture(Aska::ShaderContext::ShaderTexKind, int)(lVar1,2,1);
        }
        uVar6 = uVar6 - 1;
        lVar7 = lVar7 + 0x2a0;
      } while (uVar6 != 0);
    }
  }
  else {
    if (((bRam0000000002dd04d0 & 1) == 0) && (iVar5 = __cxa_guard_acquire(0x2dd04d0), iVar5 != 0)) {
      bRam0000000002dd04c8 =
           Aska::RenderDeviceGL::IsSupported(Aska::GLExtension::E) const(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,0xf);
      bRam0000000002dd04c8 = bRam0000000002dd04c8 & 1;
      __cxa_guard_release(0x2dd04d0);
    }
    if (bRam0000000002dd04c8 != 0) {
      cVar3 = *(char *)(param_1 + 0x2c);
      uStack_50 = 0x6162405400000000;
      if (param_2 != 1) {
        uStack_50 = 0x7061404200000000;
      }
      uStack_40 = 0;
      uStack_38 = 0;
      uStack_48 = 0x201000002000100;
      if (bVar2 != 0) {
        uStack_48._4_2_ = 0;
        lVar7 = 0x10;
        while( true ) {
          uVar6 = uVar6 - 1;
          uVar4 = uStack_48._4_2_ & 0xffc0;
          lVar1 = 0;
          if (*(long *)(param_1 + 0x18) != 0) {
            lVar1 = *(long *)(param_1 + 0x18) + lVar7;
          }
          uStack_48._0_6_ =
               CONCAT24(uVar4 | ('\0' < cVar3 || *(char *)(lVar1 + 0x24a) != '\0'),
                        (undefined4)uStack_48);
          if ((*(byte *)(lVar1 + 0x246) & 1) != 0) {
            Aska::MaterialContext::AddShaderTexture(Aska::ShaderContext::ShaderTexKind, Aska::TEXTUREINFO*, int)(lVar1,2,&uStack_50,1);
          }
          if (uVar6 == 0) break;
          lVar7 = lVar7 + 0x2a0;
        }
      }
    }
  }
  return;
}

// ==== Aska::MaterialList::EnableShadowNoise(bool)
// vaddr 0x214652c | ghidra 0x224652c | size 340 | symbol _ZN4Aska12MaterialList17EnableShadowNoiseEb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska12MaterialList17EnableShadowNoiseEb(long param_1,ulong param_2)

{
  long lVar1;
  byte bVar2;
  uint7 uVar3;
  undefined8 uVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  undefined8 uStack_90;
  undefined1 uStack_88;
  undefined1 uStack_87;
  undefined1 uStack_85;
  undefined1 uStack_82;
  undefined1 uStack_81;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  bVar2 = *(byte *)(param_1 + 0x22);
  uVar6 = (ulong)bVar2;
  if ((param_2 & 1) == 0) {
    if (bVar2 != 0) {
      lVar7 = 0x10;
      do {
        lVar8 = 0;
        if (*(long *)(param_1 + 0x18) != 0) {
          lVar8 = *(long *)(param_1 + 0x18) + lVar7;
        }
        Aska::MaterialContext::RemoveShaderTexture(Aska::ShaderContext::ShaderTexKind, int)(lVar8,8,3);
        uVar6 = uVar6 - 1;
        lVar7 = lVar7 + 0x2a0;
      } while (uVar6 != 0);
    }
code_r0x02246640:
    uVar4 = 0;
  }
  else {
    memset(&uStack_88,0,0x58);
    uVar4 = 1;
    uStack_85 = 2;
    uStack_90 = *(undefined8 *)PTR__ZN4Aska9AofObject24m_ulShadowNoiseTextureIDE_02cc4b78;
    uStack_82 = 1;
    uStack_87 = 1;
    uStack_81 = 0;
    uStack_70 = _UNK_029cc590;
    uStack_68._4_4_ = (undefined4)((ulong)_UNK_029cc598 >> 0x20);
    uStack_68._0_4_ = CONCAT13(2,(int3)_UNK_029cc598);
    uStack_68._0_7_ = CONCAT16(1,(undefined6)uStack_68);
    uVar3 = (uint7)(undefined7)uStack_68 >> 0x10;
    uStack_68._0_2_ = CONCAT11(1,(char)_UNK_029cc598);
    uStack_68 = (ulong)CONCAT52((int5)uVar3,(undefined2)uStack_68);
    uStack_50 = 0x7372405400000080;
    uStack_48 = 0x1000002000100;
    if (bVar2 != 0) {
      lVar7 = 0;
      lVar8 = 0x10;
      do {
        lVar1 = 0;
        if (*(long *)(param_1 + 0x18) != 0) {
          lVar1 = *(long *)(param_1 + 0x18) + lVar8;
        }
        uVar5 = Aska::MaterialContext::AddShaderTexture(Aska::ShaderContext::ShaderTexKind, Aska::TEXTUREINFO*, int)(lVar1,8,&uStack_90,3);
        if ((uVar5 & 1) == 0) {
          if ((int)lVar7 < 0) {
            lVar7 = 0x10;
            do {
              lVar8 = 0;
              if (*(long *)(param_1 + 0x18) != 0) {
                lVar8 = *(long *)(param_1 + 0x18) + lVar7;
              }
              Aska::MaterialContext::RemoveShaderTexture(Aska::ShaderContext::ShaderTexKind, int)(lVar8,8,3);
              lVar7 = lVar7 + 0x2a0;
            } while( true );
          }
          goto code_r0x02246640;
        }
        lVar7 = lVar7 + 1;
        lVar8 = lVar8 + 0x2a0;
      } while (lVar7 < (long)uVar6);
      uVar4 = 1;
    }
  }
  return uVar4;
}

// ==== Aska::MaterialList::EnableIBL(Aska::Light*, bool, Aska::MaterialList::IBLOffsetType)
// vaddr 0x2146680 | ghidra 0x2246680 | size 1064 | symbol _ZN4Aska12MaterialList9EnableIBLEPNS_5LightEbNS0_13IBLOffsetTypeE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska12MaterialList9EnableIBLEPNS_5LightEbNS0_13IBLOffsetTypeE
          (long param_1,long param_2,byte param_3,int param_4)

{
  byte bVar1;
  byte bVar2;
  long lVar3;
  byte bVar4;
  char cVar5;
  ushort uVar6;
  bool bVar7;
  ulong uVar8;
  ushort uVar9;
  long lVar10;
  ulong uVar11;
  uint uVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  undefined8 uStack_c0;
  undefined1 uStack_b7;
  byte bStack_b6;
  undefined1 uStack_b5;
  ushort uStack_b4;
  undefined1 auStack_b2 [18];
  undefined8 uStack_a0;
  undefined8 uStack_98;
  
  bVar4 = *(byte *)(param_1 + 0x22);
  uVar11 = (ulong)bVar4;
  if (param_2 == 0) {
    if (bVar4 != 0) {
      lVar10 = 0x10;
      do {
        lVar14 = 0;
        if (*(long *)(param_1 + 0x18) != 0) {
          lVar14 = *(long *)(param_1 + 0x18) + lVar10;
        }
        Aska::MaterialContext::RemoveShaderTexture(Aska::ShaderContext::ShaderTexKind, int)(lVar14,3,*(undefined1 *)(param_1 + 0x2d));
        uVar11 = uVar11 - 1;
        lVar10 = lVar10 + 0x2a0;
        *(byte *)(lVar14 + 0x1e) = *(byte *)(lVar14 + 0x1e) & 0x70;
      } while (uVar11 != 0);
    }
    return 0;
  }
  lVar10 = *(long *)(param_2 + 0x418);
  uVar6 = *(ushort *)(param_1 + 0x20);
  cVar5 = *(char *)(param_1 + 0x2c);
  bVar7 = *(long *)(lVar10 + 0x20) != 0;
  bVar1 = bVar7 & param_3;
  uVar12 = 1;
  if ((bVar7 & param_3) != 0) {
    uVar12 = 2;
  }
  lVar14 = (ulong)uVar12 + (ulong)(uVar6 >> 0xb & 1);
  *(char *)(param_1 + 0x2d) = (char)lVar14;
  memset(&uStack_c0,0,0x60);
  uStack_b5 = 2;
  uStack_b7 = 1;
  auStack_b2[1] = 2;
  auStack_b2[0] = 0x82;
  if (bVar1 != 0) {
    uStack_98 = 0x201000002010100;
    uStack_a0 = *(undefined8 *)(lVar10 + 0x10);
  }
  if ((uVar6 & 0x800) != 0) {
    lVar15 = (long)((int)lVar14 + -1);
    lVar13 = lVar15 * 0x20;
    *(undefined8 *)(&stack0xffffffffffffff48 + lVar13) = 0;
    (&uStack_b5)[lVar13] = 2;
    *(undefined2 *)(&uStack_b7 + lVar13) = 0x101;
    auStack_b2[lVar13 + 1] = 2;
    auStack_b2[lVar13] = 0x82;
    *(undefined2 *)(auStack_b2 + lVar13 + -2) = 0;
    (&uStack_c0)[lVar15 * 4] = *(undefined8 *)(lVar10 + 0x18);
  }
  if (bVar4 != 0) {
    if ((uVar6 & 0x800) == 0) {
      lVar14 = 0;
      lVar13 = 0x10;
      do {
        lVar15 = 0;
        if (*(long *)(param_1 + 0x18) != 0) {
          lVar15 = *(long *)(param_1 + 0x18) + lVar13;
        }
        uVar6 = *(ushort *)(lVar15 + 0x245);
        if ((uVar6 >> 9 & 1) == 0) {
          bStack_b6 = bStack_b6 | 1;
          uStack_c0 = *(undefined8 *)(lVar10 + 0x18);
          uStack_b4 = uStack_b4 & 0xffc0;
          if (*(char *)(lVar15 + 0x24a) != '\0' || cVar5 != '\0') {
            uStack_b4 = uStack_b4 | 1;
          }
        }
        else {
          uStack_b4 = uStack_b4 & 0xffc0 | 3;
          uStack_c0 = Aska::Light::GetIBLTextureID(int) const(param_2,0);
        }
        uVar8 = Aska::MaterialContext::AddShaderTexture(Aska::ShaderContext::ShaderTexKind, Aska::TEXTUREINFO*, int)(lVar15,3,&uStack_c0,*(undefined1 *)(param_1 + 0x2d));
        if ((uVar8 & 1) == 0) goto code_r0x02246a58;
        bVar4 = *(byte *)(lVar15 + 0x1e) | 1;
        if ((uVar6 & 0x200) == 0) {
          bVar4 = *(byte *)(lVar15 + 0x1e) & 0xfe;
        }
        bVar2 = bVar4 | 2;
        if (bVar1 == 0) {
          bVar2 = bVar4 & 0xfd;
        }
        bVar4 = bVar2 | 4;
        if (((uint)(param_4 == 1) & (uVar6 & 0x800) >> 0xb) == 0) {
          bVar4 = bVar2 & 0xfb;
        }
        bVar2 = bVar4 | 0x80;
        if (param_4 != 2) {
          bVar2 = bVar4 & 0x7f;
        }
        lVar14 = lVar14 + 1;
        bVar4 = bVar2 | 8;
        if ((uVar6 & 0x400) == 0) {
          bVar4 = bVar2 & 0xf7;
        }
        lVar13 = lVar13 + 0x2a0;
        *(byte *)(lVar15 + 0x1e) = bVar4;
      } while (lVar14 < (long)uVar11);
    }
    else {
      lVar13 = (lVar14 + -1) * 0x20;
      lVar14 = 0;
      lVar15 = 0x10;
      do {
        lVar3 = 0;
        if (*(long *)(param_1 + 0x18) != 0) {
          lVar3 = *(long *)(param_1 + 0x18) + lVar15;
        }
        uVar6 = *(ushort *)(lVar3 + 0x245);
        if ((uVar6 >> 9 & 1) == 0) {
          bStack_b6 = bStack_b6 | 1;
          uStack_c0 = *(undefined8 *)(lVar10 + 0x18);
          if (*(char *)(lVar3 + 0x24a) == '\0' && cVar5 == '\0') {
            uStack_b4 = uStack_b4 & 0xffc0;
            uVar9 = *(ushort *)(auStack_b2 + lVar13 + -2) & 0xffc0;
          }
          else {
            uStack_b4 = uStack_b4 & 0xffc0 | 1;
            uVar9 = *(ushort *)(auStack_b2 + lVar13 + -2) & 0xffc0 | 1;
          }
          *(ushort *)(auStack_b2 + lVar13 + -2) = uVar9;
        }
        else {
          uStack_b4 = uStack_b4 & 0xffc0 | 3;
          uStack_c0 = Aska::Light::GetIBLTextureID(int) const(param_2,0);
        }
        uVar8 = Aska::MaterialContext::AddShaderTexture(Aska::ShaderContext::ShaderTexKind, Aska::TEXTUREINFO*, int)(lVar3,3,&uStack_c0,*(undefined1 *)(param_1 + 0x2d));
        if ((uVar8 & 1) == 0) {
code_r0x02246a58:
          if (-1 < (int)lVar14) {
            return 0;
          }
          lVar10 = 0x10;
          do {
            lVar14 = 0;
            if (*(long *)(param_1 + 0x18) != 0) {
              lVar14 = *(long *)(param_1 + 0x18) + lVar10;
            }
            Aska::MaterialContext::RemoveShaderTexture(Aska::ShaderContext::ShaderTexKind, int)(lVar14,3,*(undefined1 *)(param_1 + 0x2d));
            lVar10 = lVar10 + 0x2a0;
          } while( true );
        }
        bVar4 = *(byte *)(lVar3 + 0x1e) | 1;
        if ((uVar6 & 0x200) == 0) {
          bVar4 = *(byte *)(lVar3 + 0x1e) & 0xfe;
        }
        bVar2 = bVar4 | 2;
        if (bVar1 == 0) {
          bVar2 = bVar4 & 0xfd;
        }
        bVar4 = bVar2 | 4;
        if (((uint)(param_4 == 1) & (uVar6 & 0x800) >> 0xb) == 0) {
          bVar4 = bVar2 & 0xfb;
        }
        bVar2 = bVar4 | 0x80;
        if (param_4 != 2) {
          bVar2 = bVar4 & 0x7f;
        }
        lVar14 = lVar14 + 1;
        bVar4 = bVar2 | 8;
        if ((uVar6 & 0x400) == 0) {
          bVar4 = bVar2 & 0xf7;
        }
        lVar15 = lVar15 + 0x2a0;
        *(byte *)(lVar3 + 0x1e) = bVar4;
      } while (lVar14 < (long)uVar11);
    }
  }
  return 1;
}

// ==== Aska::MaterialList::EnableSecondaryIBL(Aska::Light*)
// vaddr 0x2146aa8 | ghidra 0x2246aa8 | size 372 | symbol _ZN4Aska12MaterialList18EnableSecondaryIBLEPNS_5LightE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska12MaterialList18EnableSecondaryIBLEPNS_5LightE(long param_1,long param_2)

{
  long lVar1;
  byte bVar2;
  char cVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  undefined8 uStack_70;
  undefined1 auStack_68 [6];
  undefined2 uStack_62;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  bVar2 = *(byte *)(param_1 + 0x22);
  uVar5 = (ulong)bVar2;
  if (param_2 == 0) {
    if (bVar2 != 0) {
      lVar6 = 0x10;
      do {
        lVar7 = 0;
        if (*(long *)(param_1 + 0x18) != 0) {
          lVar7 = *(long *)(param_1 + 0x18) + lVar6;
        }
        Aska::MaterialContext::RemoveShaderTexture(Aska::ShaderContext::ShaderTexKind, int)(lVar7,4,*(undefined1 *)(param_1 + 0x2d));
        uVar5 = uVar5 - 1;
        lVar6 = lVar6 + 0x2a0;
      } while (uVar5 != 0);
    }
  }
  else {
    cVar3 = *(char *)(param_1 + 0x2c);
    uStack_60 = 0;
    uStack_38 = 0;
    uStack_40 = 0;
    uStack_48 = 0;
    uStack_50 = 0;
    uStack_58 = 0;
    uStack_70 = *(undefined8 *)(*(long *)(param_2 + 0x418) + 0x18);
    if (bVar2 == 0) {
      return 1;
    }
    lVar6 = 0;
    if (*(long *)(param_1 + 0x18) != 0) {
      lVar6 = *(long *)(param_1 + 0x18) + 0x10;
    }
    auStack_68 = (undefined1  [6])
                 CONCAT15(0,CONCAT14(*(char *)(lVar6 + 0x24a) != '\0' || cVar3 != '\0',0x2000100));
    _auStack_68 = CONCAT26(0x282,auStack_68);
    uVar4 = Aska::MaterialContext::AddShaderTexture(Aska::ShaderContext::ShaderTexKind, Aska::TEXTUREINFO*, int)(lVar6,4,&uStack_70,1);
    if ((uVar4 & 1) != 0) {
      lVar6 = 0;
      lVar7 = 0x2b0;
      do {
        lVar6 = lVar6 + 1;
        if ((long)uVar5 <= lVar6) {
          return 1;
        }
        lVar1 = 0;
        if (*(long *)(param_1 + 0x18) != 0) {
          lVar1 = *(long *)(param_1 + 0x18) + lVar7;
        }
        auStack_68 = (undefined1  [6])
                     CONCAT24(auStack_68._4_2_ & 0xffc0 |
                              (ushort)(*(char *)(lVar1 + 0x24a) != '\0' || cVar3 != '\0'),
                              auStack_68._0_4_);
        uVar4 = Aska::MaterialContext::AddShaderTexture(Aska::ShaderContext::ShaderTexKind, Aska::TEXTUREINFO*, int)(lVar1,4,&uStack_70,1);
        lVar7 = lVar7 + 0x2a0;
      } while ((uVar4 & 1) != 0);
      if ((int)lVar6 < 0) {
        lVar6 = 0x10;
        do {
          lVar7 = 0;
          if (*(long *)(param_1 + 0x18) != 0) {
            lVar7 = *(long *)(param_1 + 0x18) + lVar6;
          }
          Aska::MaterialContext::RemoveShaderTexture(Aska::ShaderContext::ShaderTexKind, int)(lVar7,4,1);
          lVar6 = lVar6 + 0x2a0;
        } while( true );
      }
    }
  }
  return 0;
}

// ==== Aska::MaterialList::SetShaderLod(int)
// vaddr 0x2146c1c | ghidra 0x2246c1c | size 52 | symbol _ZN4Aska12MaterialList12SetShaderLodEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList12SetShaderLodEi(long param_1,undefined1 param_2)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  
  uVar2 = (ulong)*(byte *)(param_1 + 0x22);
  if (uVar2 != 0) {
    lVar3 = 0x10;
    do {
      uVar2 = uVar2 - 1;
      lVar1 = 0;
      if (*(long *)(param_1 + 0x18) != 0) {
        lVar1 = *(long *)(param_1 + 0x18) + lVar3;
      }
      lVar3 = lVar3 + 0x2a0;
      *(undefined1 *)(lVar1 + 0x1d) = param_2;
    } while (uVar2 != 0);
  }
  *(undefined1 *)(param_1 + 0x2c) = param_2;
  return;
}

// ==== Aska::MaterialList::ServeShaderConstantBody()
// vaddr 0x2146c50 | ghidra 0x2246c50 | size 484 | symbol _ZN4Aska12MaterialList23ServeShaderConstantBodyEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12MaterialList23ServeShaderConstantBodyEv(long param_1)

{
  long lVar1;
  long lVar2;
  byte bVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  undefined *puVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  long *plVar13;
  ulong uVar14;
  long *plVar15;
  ulong uVar16;
  float fVar17;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  
  fVar4 = (float)NEON_ucvtf((uint)*(ushort *)
                                   (*(long *)PTR__ZN4Aska6Global14m_pFrameBufferE_02cb8198 + 0x28));
  fVar4 = (float)log10f(SUB42(1.0 / fVar4,0));
  puVar9 = PTR__ZN4Aska6Global17m_pTextureManagerE_02cc19f0;
  fVar8 = _UNK_029cc5ac;
  fVar7 = _UNK_029cc5a8;
  fVar6 = _UNK_029cc5a4;
  fVar5 = _UNK_029cc5a0;
  bVar3 = *(byte *)(param_1 + 0x22);
  if ((ulong)bVar3 != 0) {
    fVar4 = fVar4 * _UNK_029cc5a0;
    uVar14 = 0;
    do {
      lVar2 = 0;
      if (*(long *)(param_1 + 0x18) != 0) {
        lVar2 = *(long *)(param_1 + 0x18) + uVar14 * 0x2a0 + 0x10;
      }
      uVar16 = (ulong)*(byte *)(lVar2 + 0x249);
      if (uVar16 != 0) {
        lVar10 = *(long *)(param_1 + 0x68);
        plVar15 = (long *)(lVar2 + 0x260);
        do {
          lVar11 = lVar2 + (ulong)*(byte *)(plVar15 + -2) * 0x20;
          lVar12 = *(long *)(lVar11 + 0x20);
          if (lVar12 == 0) {
            lVar11 = 0;
          }
          else {
            plVar13 = (long *)(lVar11 + 0x30);
            lVar11 = *plVar13;
            if (lVar11 == 0) {
              lVar11 = *(long *)puVar9;
              lVar1 = lVar11 + 0xb0;
              Aska::CriticalSection::Enter() const(lVar1);
              lVar11 = Aska::TextureManager::QueryTextureEx(unsigned long, bool)(lVar11,lVar12,1);
              Aska::CriticalSection::Leave() const(lVar1);
              *plVar13 = lVar11;
            }
          }
          lVar12 = Aska::Texture::GetBody() const(lVar11);
          if ((lVar11 != plVar15[-1]) || (lVar12 != *plVar15)) {
            plVar15[-1] = lVar11;
            *plVar15 = lVar12;
            fVar17 = (float)log10f(SUB42((float)((uint)*(ushort *)(lVar11 + 0x1a) +
                                                         (uint)*(ushort *)(lVar11 + 0x18)) * 0.5,0))
            ;
            fStack_a0 = fVar17 * fVar5 + fVar6;
            fStack_9c = fVar4 + -5.0 + fStack_a0;
            fVar17 = fVar7;
            if ((*(char *)(lVar11 + 0x15) == '\x06') ||
               (fVar17 = fVar8, *(char *)(lVar11 + 0x15) == '\x02')) {
              fStack_98 = fStack_a0 - fVar17;
            }
            bool Aska::ShaderConstantManager::SetShaderConstantF_lockable<true>(int, int, Aska::Vector const*, int)(lVar10 + uVar14 * 0x1b8,0x51,*(undefined1 *)((long)plVar15 + -0xf),
                            &fStack_a0,1);
          }
          uVar16 = uVar16 - 1;
          plVar15 = plVar15 + 3;
        } while (uVar16 != 0);
      }
      uVar14 = uVar14 + 1;
    } while (uVar14 != bVar3);
  }
  return;
}

// ==== Aska::MaterialList::IsPunchthrough()
// vaddr 0x2146e34 | ghidra 0x2246e34 | size 72 | symbol _ZN4Aska12MaterialList14IsPunchthroughEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska12MaterialList14IsPunchthroughEv(long param_1)

{
  long lVar1;
  byte *pbVar2;
  
  if ((ulong)*(byte *)(param_1 + 0x22) == 0) {
    return 0;
  }
  lVar1 = 0;
  pbVar2 = (byte *)(*(long *)(param_1 + 0x18) + 0x255);
  do {
    if ((*pbVar2 & 0xc) != 0) {
      return 1;
    }
    lVar1 = lVar1 + 1;
    pbVar2 = pbVar2 + 0x2a0;
  } while (lVar1 < (long)(ulong)*(byte *)(param_1 + 0x22));
  return 0;
}

// ==== Aska::MaterialList::IsZprepassOFF()
// vaddr 0x2146e7c | ghidra 0x2246e7c | size 68 | symbol _ZN4Aska12MaterialList13IsZprepassOFFEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska12MaterialList13IsZprepassOFFEv(long param_1)

{
  long lVar1;
  byte *pbVar2;
  
  if ((ulong)*(byte *)(param_1 + 0x22) == 0) {
    return 0;
  }
  lVar1 = 0;
  pbVar2 = (byte *)(*(long *)(param_1 + 0x18) + 0x255);
  do {
    if ((*pbVar2 >> 3 & 1) != 0) {
      return 1;
    }
    lVar1 = lVar1 + 1;
    pbVar2 = pbVar2 + 0x2a0;
  } while (lVar1 < (long)(ulong)*(byte *)(param_1 + 0x22));
  return 0;
}

// ==== Aska::MaterialList::UpdateMaterialContext()
// vaddr 0x2146ec0 | ghidra 0x2246ec0 | size 256 | symbol _ZN4Aska12MaterialList21UpdateMaterialContextEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList21UpdateMaterialContextEv(long param_1)

{
  ushort *puVar1;
  bool bVar2;
  uint uVar3;
  ulong uVar4;
  uint uVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  
  uVar4 = (ulong)*(byte *)(param_1 + 0x22);
  if (*(byte *)(param_1 + 0x22) != 0) {
    lVar6 = 0;
    lVar7 = 0;
    uVar5 = 0;
    lVar8 = 0x255;
    do {
      if ((*(byte *)(*(long *)(param_1 + 0x18) + lVar8) & 1) != 0) {
        puVar1 = (ushort *)(*(long *)(param_1 + 0x18) + lVar8);
        uVar3 = Aska::MaterialContext::MakeShaderConstant(Aska::ShaderConstantManager*)((long)puVar1 + -0x245,*(long *)(param_1 + 0x68) + lVar6);
        uVar5 = uVar5 | uVar3;
        *puVar1 = *puVar1 & 0xfffe;
        uVar4 = (ulong)*(byte *)(param_1 + 0x22);
      }
      lVar7 = lVar7 + 1;
      lVar8 = lVar8 + 0x2a0;
      lVar6 = lVar6 + 0x1b8;
    } while (lVar7 < (long)uVar4);
    if ((uVar5 & 1) != 0) {
      *(ushort *)(param_1 + 0x8f) = *(ushort *)(param_1 + 0x8f) | 1;
      if (*(long *)(param_1 + 0xa0) != 0) {
        bVar2 = false;
        lVar7 = *(long *)(param_1 + 0xa0);
code_r0x02246f5c:
        do {
          do {
            lVar8 = lVar7;
            if (!bVar2) {
              bVar2 = false;
              *(ushort *)(lVar8 + 0x2f) = *(ushort *)(lVar8 + 0x2f) | 1;
              lVar7 = *(long *)(lVar8 + 0x40);
              if (*(long *)(lVar8 + 0x40) != 0) goto code_r0x02246f5c;
            }
            bVar2 = false;
            lVar7 = *(long *)(lVar8 + 0x48);
          } while (*(long *)(lVar8 + 0x48) != 0);
          bVar2 = true;
          lVar7 = *(long *)(lVar8 + 0x38);
        } while (*(long *)(lVar8 + 0x38) != param_1 + 0x60);
      }
    }
  }
  *(ushort *)(param_1 + 0x20) = *(ushort *)(param_1 + 0x20) & 0xfffb;
  return;
}

// ==== Aska::MaterialList::SetActiveMaterialCount(unsigned char)
// vaddr 0x2146fc0 | ghidra 0x2246fc0 | size 8 | symbol _ZN4Aska12MaterialList22SetActiveMaterialCountEh | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska12MaterialList22SetActiveMaterialCountEh(long param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x22) = param_2;
  return;
}

// ==== Aska::UniformValueBuffer2::Add(int, int)
// vaddr 0x218ec8c | ghidra 0x228ec8c | size 188 | symbol _ZN4Aska19UniformValueBuffer23AddEii | lib libSOA-3.7.0.so | 2026-10-04
undefined2 * _ZN4Aska19UniformValueBuffer23AddEii(int *param_1,undefined2 param_2,int param_3)

{
  undefined2 *puVar1;
  long lVar2;
  int iVar3;
  long lVar4;
  long lVar5;
  int iVar6;
  
  iVar6 = *param_1;
  iVar3 = param_1[1];
  if (iVar3 < iVar6 + param_3 + 4) {
    lVar2 = (long)iVar3 + 0x200;
    lVar4 = operator new[](unsigned long, std::nothrow_t const&)(lVar2,PTR__ZSt7nothrow_02cb9a80);
    lVar5 = *(long *)(param_1 + 2);
    if (lVar5 != 0) {
      memcpy(lVar4,lVar5,(long)iVar3);
      operator delete[](void*)(lVar5);
      iVar6 = *param_1;
      param_1[2] = 0;
      param_1[3] = 0;
    }
    *(long *)(param_1 + 2) = lVar4;
    param_1[1] = (int)lVar2;
  }
  else {
    lVar4 = *(long *)(param_1 + 2);
  }
  puVar1 = (undefined2 *)(lVar4 + iVar6);
  *puVar1 = param_2;
  puVar1[1] = (short)param_3;
  *param_1 = *param_1 + param_3 + 4;
  return puVar1 + 2;
}

// ==== Aska::UniformValueBuffer2::Alloc(int, int)
// vaddr 0x218ed48 | ghidra 0x228ed48 | size 184 | symbol _ZN4Aska19UniformValueBuffer25AllocEii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19UniformValueBuffer25AllocEii(int *param_1,undefined2 param_2,int param_3)

{
  long lVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  int iVar5;
  
  iVar5 = *param_1;
  iVar2 = param_1[1];
  if (iVar2 < iVar5 + param_3 + 4) {
    lVar1 = (long)iVar2 + 0x200;
    lVar3 = operator new[](unsigned long, std::nothrow_t const&)(lVar1,PTR__ZSt7nothrow_02cb9a80);
    lVar4 = *(long *)(param_1 + 2);
    if (lVar4 != 0) {
      memcpy(lVar3,lVar4,(long)iVar2);
      operator delete[](void*)(lVar4);
      iVar5 = *param_1;
      param_1[2] = 0;
      param_1[3] = 0;
    }
    *(long *)(param_1 + 2) = lVar3;
    param_1[1] = (int)lVar1;
  }
  else {
    lVar3 = *(long *)(param_1 + 2);
  }
  *(undefined2 *)(lVar3 + iVar5) = param_2;
  ((undefined2 *)(lVar3 + iVar5))[1] = (short)param_3;
  *param_1 = *param_1 + param_3 + 4;
  return;
}

// ==== Aska::UniformValueBuffer2::Add(int, int, void*)
// vaddr 0x218ee00 | ghidra 0x228ee00 | size 220 | symbol _ZN4Aska19UniformValueBuffer23AddEiiPv | lib libSOA-3.7.0.so | 2026-10-04
undefined2 *
_ZN4Aska19UniformValueBuffer23AddEiiPv
          (int *param_1,undefined2 param_2,int param_3,undefined8 param_4)

{
  undefined2 *puVar1;
  long lVar2;
  int iVar3;
  long lVar4;
  long lVar5;
  int iVar6;
  
  iVar6 = *param_1;
  iVar3 = param_1[1];
  if (iVar3 < iVar6 + param_3 + 4) {
    lVar2 = (long)iVar3 + 0x200;
    lVar4 = operator new[](unsigned long, std::nothrow_t const&)(lVar2,PTR__ZSt7nothrow_02cb9a80);
    lVar5 = *(long *)(param_1 + 2);
    if (lVar5 != 0) {
      memcpy(lVar4,lVar5,(long)iVar3);
      operator delete[](void*)(lVar5);
      iVar6 = *param_1;
      param_1[2] = 0;
      param_1[3] = 0;
    }
    *(long *)(param_1 + 2) = lVar4;
    param_1[1] = (int)lVar2;
  }
  else {
    lVar4 = *(long *)(param_1 + 2);
  }
  puVar1 = (undefined2 *)(lVar4 + iVar6);
  *puVar1 = param_2;
  puVar1[1] = (short)param_3;
  *param_1 = *param_1 + param_3 + 4;
  memcpy(puVar1 + 2,param_4,(long)param_3);
  return puVar1 + 2;
}

// ==== Aska::UniformValueBuffer2::Realloc(int)
// vaddr 0x218eedc | ghidra 0x228eedc | size 120 | symbol _ZN4Aska19UniformValueBuffer27ReallocEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19UniformValueBuffer27ReallocEi(long param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  long lVar4;
  
  iVar2 = *(int *)(param_1 + 4);
  if (iVar2 != param_2) {
    uVar3 = operator new[](unsigned long, std::nothrow_t const&)((long)param_2,PTR__ZSt7nothrow_02cb9a80);
    lVar4 = *(long *)(param_1 + 8);
    if (lVar4 != 0) {
      iVar1 = param_2;
      if (iVar2 <= param_2) {
        iVar1 = iVar2;
      }
      memcpy(uVar3,lVar4,(long)iVar1);
      operator delete[](void*)(lVar4);
      *(undefined8 *)(param_1 + 8) = 0;
    }
    *(undefined8 *)(param_1 + 8) = uVar3;
    *(int *)(param_1 + 4) = param_2;
  }
  return;
}

// ==== Aska::UniformValueBuffer2::TrimExtraMemory()
// vaddr 0x218ef54 | ghidra 0x228ef54 | size 116 | symbol _ZN4Aska19UniformValueBuffer215TrimExtraMemoryEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19UniformValueBuffer215TrimExtraMemoryEv(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  long lVar5;
  
  iVar2 = *param_1;
  iVar3 = param_1[1];
  if (iVar3 != iVar2) {
    uVar4 = operator new[](unsigned long, std::nothrow_t const&)((long)iVar2,PTR__ZSt7nothrow_02cb9a80);
    lVar5 = *(long *)(param_1 + 2);
    if (lVar5 != 0) {
      iVar1 = iVar2;
      if (iVar3 <= iVar2) {
        iVar1 = iVar3;
      }
      memcpy(uVar4,lVar5,(long)iVar1);
      operator delete[](void*)(lVar5);
      param_1[2] = 0;
      param_1[3] = 0;
    }
    *(undefined8 *)(param_1 + 2) = uVar4;
    param_1[1] = iVar2;
  }
  return;
}

// ==== Aska::UniformValueBuffer2::ReserveMemory(int)
// vaddr 0x218efc8 | ghidra 0x228efc8 | size 120 | symbol _ZN4Aska19UniformValueBuffer213ReserveMemoryEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19UniformValueBuffer213ReserveMemoryEi(long param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  long lVar4;
  
  iVar2 = *(int *)(param_1 + 4);
  if (iVar2 < param_2) {
    uVar3 = operator new[](unsigned long, std::nothrow_t const&)((long)param_2,PTR__ZSt7nothrow_02cb9a80);
    lVar4 = *(long *)(param_1 + 8);
    if (lVar4 != 0) {
      iVar1 = param_2;
      if (iVar2 <= param_2) {
        iVar1 = iVar2;
      }
      memcpy(uVar3,lVar4,(long)iVar1);
      operator delete[](void*)(lVar4);
      *(undefined8 *)(param_1 + 8) = 0;
    }
    *(undefined8 *)(param_1 + 8) = uVar3;
    *(int *)(param_1 + 4) = param_2;
  }
  return;
}

// ==== Aska::UniformValueBuffer2::Reset(Aska::UniformValueBuffer2::MemoryOperation)
// vaddr 0x218f040 | ghidra 0x228f040 | size 48 | symbol _ZN4Aska19UniformValueBuffer25ResetENS0_15MemoryOperationE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19UniformValueBuffer25ResetENS0_15MemoryOperationE(undefined4 *param_1,int param_2)

{
  if (param_2 == 1) {
    if (*(long *)(param_1 + 2) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 2) = 0;
    }
    param_1[1] = 0;
  }
  *param_1 = 0;
  return;
}

// ==== Aska::UniformValueBuffer2::Clone(Aska::UniformValueBuffer2 const&)
// vaddr 0x218f070 | ghidra 0x228f070 | size 108 | symbol _ZN4Aska19UniformValueBuffer25CloneERKS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska19UniformValueBuffer25CloneERKS0_(int *param_1,int *param_2)

{
  int iVar1;
  long lVar2;
  
  param_1[0] = 0;
  param_1[1] = 0;
  if (*(long *)(param_1 + 2) != 0) {
    operator delete[](void*)();
    param_1[2] = 0;
    param_1[3] = 0;
  }
  iVar1 = *param_2;
  if (iVar1 != 0) {
    lVar2 = operator new[](unsigned long, std::nothrow_t const&)((long)iVar1,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 2) = lVar2;
    if (lVar2 != 0) {
      memcpy(lVar2,*(undefined8 *)(param_2 + 2),(long)iVar1);
    }
    *param_1 = iVar1;
    param_1[1] = iVar1;
  }
  return;
}

// ==== Aska::ShaderConstantManager::IsShaderConstantManagerDirty() const
// vaddr 0x21bc900 | ghidra 0x22bc900 | size 84 | symbol _ZNK4Aska21ShaderConstantManager28IsShaderConstantManagerDirtyEv | lib libSOA-3.7.0.so | 2026-10-04
byte _ZNK4Aska21ShaderConstantManager28IsShaderConstantManagerDirtyEv(long param_1)

{
  short sVar1;
  
  if (*(long *)(param_1 + 8) != 0) {
    Aska::ShaderConstantManager::IsShaderConstantManagerDirty() const();
    sVar1 = *(short *)(*(long *)(param_1 + 8) + 0x1a);
    if (sVar1 != *(short *)(param_1 + 0x18)) {
      *(short *)(param_1 + 0x18) = sVar1;
      *(short *)(param_1 + 0x1a) = *(short *)(param_1 + 0x1a) + 1;
      *(byte *)(param_1 + 0x1c) = *(byte *)(param_1 + 0x1c) | 1;
    }
  }
  return *(byte *)(param_1 + 0x1c) & 1;
}

// ==== Aska::ShaderConstantHandler::SetShaderConstant(unsigned long, Aska::ShaderNodeHandler*)
// vaddr 0x21c8730 | ghidra 0x22c8730 | size 116 | symbol _ZN4Aska21ShaderConstantHandler17SetShaderConstantEmPNS_17ShaderNodeHandlerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska21ShaderConstantHandler17SetShaderConstantEmPNS_17ShaderNodeHandlerE
               (undefined8 *param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  
  uVar2 = *(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
  (**(code **)*param_1)(param_1,param_2,uVar2,param_3);
  puVar1 = (undefined8 *)param_1[1];
  if (puVar1 != (undefined8 *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x022c8790. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)*puVar1)(puVar1,param_2,uVar2,param_3);
    return;
  }
  return;
}

// ==== Aska::ShaderConstantHandler::StartOwnGpuConstant()
// vaddr 0x21c87a4 | ghidra 0x22c87a4 | size 4 | symbol _ZN4Aska21ShaderConstantHandler19StartOwnGpuConstantEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska21ShaderConstantHandler19StartOwnGpuConstantEv(void)

{
  return;
}

// ==== Aska::ShaderConstantHandler::EndOwnGpuConstant()
// vaddr 0x21c87a8 | ghidra 0x22c87a8 | size 4 | symbol _ZN4Aska21ShaderConstantHandler17EndOwnGpuConstantEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska21ShaderConstantHandler17EndOwnGpuConstantEv(void)

{
  return;
}

// ==== Aska::AhslConst::GetId(char const*, char const**)
// vaddr 0x2354db4 | ghidra 0x2454db4 | size 124 | symbol _ZN4Aska9AhslConst5GetIdEPKcPS2_ | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska9AhslConst5GetIdEPKcPS2_(undefined8 param_1,long *param_2)

{
  int iVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  long *plVar5;
  
  lVar3 = *param_2;
  iVar2 = 0;
  do {
    plVar5 = param_2;
    iVar1 = strcmp(lVar3,param_1);
    if (iVar1 == 0) {
      return iVar2;
    }
    param_2 = plVar5 + 1;
    lVar3 = *param_2;
    iVar2 = iVar2 + 1;
  } while (lVar3 != 0);
  lVar4 = plVar5[2];
  lVar3 = 2;
  do {
    iVar2 = strcmp(lVar4,param_1);
    if (iVar2 == 0) {
      return (int)lVar3 + 0x3e;
    }
    lVar4 = param_2[lVar3];
    lVar3 = lVar3 + 1;
  } while (lVar4 != 0);
  return -1;
}

// ==== Aska::AhslConst::AofConvertToNativeConstant(int, Aska::Vector const*, Aska::Vector*)
// vaddr 0x2354e30 | ghidra 0x2454e30 | size 912 | symbol _ZN4Aska9AhslConst26AofConvertToNativeConstantEiPKNS_6VectorEPS1_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska9AhslConst26AofConvertToNativeConstantEiPKNS_6VectorEPS1_
          (undefined4 param_1,float *param_2,float *param_3)

{
  bool bVar1;
  undefined8 uVar2;
  uint uVar3;
  float extraout_s0;
  float fVar4;
  float extraout_s0_00;
  float fVar5;
  float extraout_s0_01;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  
  uVar2 = 0;
  switch(param_1) {
  case 8:
    uVar2 = 1;
    *param_3 = *param_2;
    param_3[1] = param_2[1];
    param_3[2] = param_2[2];
    param_3[3] = param_2[3];
    param_3[3] = 1.0 / (param_2[3] - param_2[2]);
    break;
  case 0xb:
    uVar2 = 1;
    *param_3 = *param_2;
    param_3[1] = 1.0 / (param_2[1] - *param_2);
    param_3[2] = param_2[3] - param_2[2];
    param_3[3] = param_2[2];
    break;
  case 0xc:
  case 0xe:
    uVar3 = (uint)(param_2[6] * _UNK_027ebdf4);
    fVar10 = param_2[6] + (float)(int)uVar3 * _UNK_027edb30;
    bVar1 = (uVar3 & 1) == 0;
    fVar8 = -fVar10;
    if (bVar1) {
      fVar8 = fVar10;
    }
    fVar10 = fVar10 * fVar10;
    fVar4 = param_2[5];
    fVar11 = fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * _UNK_02964910 +
                                                                        _UNK_02964914) +
                                                              _UNK_02964918) + _UNK_0296491c) +
                                          _UNK_02964920) + _UNK_02964924) + -0.5);
    fVar12 = *param_2;
    fVar6 = param_2[1];
    fVar8 = fVar8 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * 
                                                  _UNK_02964928 + _UNK_0296492c) + _UNK_02964930) +
                                                  _UNK_02964934) + _UNK_02964938) + _UNK_0296493c) +
                              _UNK_02964940) + 1.0);
    fVar10 = -1.0 - fVar11;
    if (bVar1) {
      fVar10 = fVar11 + 1.0;
    }
    fVar11 = param_2[4] * fVar10;
    fVar7 = param_2[4] * fVar8;
    fVar5 = param_2[2];
    *param_3 = fVar11;
    param_3[1] = -(fVar4 * fVar8);
    param_3[3] = 1.0;
    param_3[2] = fVar5 + fVar12 + (fVar6 * fVar4 * fVar8 - fVar12 * fVar11);
    fVar8 = *param_2;
    fVar11 = param_2[1];
    fVar12 = param_2[3];
    param_3[4] = fVar7;
    param_3[5] = fVar4 * fVar10;
    param_3[7] = 1.0;
    param_3[6] = fVar12 + fVar11 + (-(fVar11 * fVar4 * fVar10) - fVar8 * fVar7);
    uVar2 = 2;
    break;
  case 0x15:
    fVar12 = *param_2;
    fVar11 = param_2[1];
    fVar10 = param_2[2];
    fVar8 = SQRT(fVar12 + 1.0);
    if (NAN(fVar8)) {
      uVar2 = sqrtf(0);
      fVar8 = extraout_s0;
    }
    fVar6 = fVar11 + 1.0;
    fVar4 = SQRT(fVar6);
    fVar12 = fVar12 * 0.5;
    fVar11 = fVar11 * 0.5;
    if (NAN(fVar4)) {
      uVar2 = sqrtf(fVar6,uVar2);
      fVar4 = extraout_s0_00;
    }
    fVar6 = 1.0 - (fVar10 + fVar10);
    if (fVar6 < 0.0) {
      fVar6 = 0.0;
    }
    fVar9 = 2.0 / (fVar12 + fVar11 + 2.0);
    fVar5 = SQRT(fVar9);
    fVar7 = 1.0;
    if (fVar6 + -1.0 < 0.0) {
      fVar7 = fVar6;
    }
    if (NAN(fVar5)) {
      uVar2 = sqrtf(fVar9,uVar2);
      fVar5 = extraout_s0_01;
    }
    fVar6 = (fVar5 + 1.0) * 0.5;
    fVar9 = fVar9 / (fVar9 + 1.0);
    fVar5 = (2.0 / (fVar6 * fVar6) + -2.0) * _UNK_027daba4;
    fVar6 = SQRT(fVar5);
    fVar9 = (1.0 - (fVar9 + fVar9)) * _UNK_029e4188;
    *param_3 = fVar12;
    param_3[1] = fVar11;
    param_3[2] = fVar8 * 0.125;
    param_3[3] = fVar10 * fVar4 * 0.125;
    if (NAN(fVar6)) {
      fVar6 = (float)sqrtf(fVar5,uVar2);
    }
    uVar2 = 3;
    param_3[4] = fVar6;
    param_3[5] = fVar9;
    param_3[6] = 0.0;
    param_3[9] = fVar7;
    param_3[10] = fVar10;
    param_3[7] = 1.0 - fVar10;
    param_3[8] = fVar7;
    param_3[0xb] = 1.0 - fVar10;
  }
  return uVar2;
}

// ==== Aska::AhslConst::AofRecoverFromNativeConstant(int, Aska::Vector const*, Aska::Vector*)
// vaddr 0x23551c0 | ghidra 0x24551c0 | size 136 | symbol _ZN4Aska9AhslConst28AofRecoverFromNativeConstantEiPKNS_6VectorEPS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9AhslConst28AofRecoverFromNativeConstantEiPKNS_6VectorEPS1_
          (int param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  
  if (param_1 == 0xb) {
    *param_3 = *param_2;
    param_3[1] = 1.0 / param_2[1] + *param_2;
    param_3[2] = param_2[3];
    fVar1 = param_2[2];
    fVar2 = param_2[3];
  }
  else {
    if (param_1 != 8) {
      return 0;
    }
    *param_3 = *param_2;
    param_3[1] = param_2[1];
    param_3[2] = param_2[2];
    param_3[3] = param_2[3];
    fVar2 = param_2[2];
    fVar1 = 1.0 / param_2[3];
  }
  param_3[3] = fVar1 + fVar2;
  return 1;
}


// FAILED to create function at 029cc450 Aska::MaterialContext::m_mPreRotateMatrix
// FAILED to create function at 029cc490 Aska::MaterialContext::m_mPostRotateMatrix
// FAILED to create function at 029cc4d0 Aska::MaterialContext::m_mPreScaleMatrix
// FAILED to create function at 029cc510 Aska::MaterialContext::m_mPostScaleMatrix
// FAILED to create function at 029cc5b0 Aska::MaterialList::DIRECTMATERIAL_DIRECTSHADERNODE_BUFSIZE
// FAILED to create function at 02c4ec98 Aska::MaterialContext::vtable
// FAILED to create function at 02c4ecc8 Aska::ShaderConstantHandler::typeinfo
// FAILED to create function at 02c4ece0 Aska::MaterialContext::typeinfo
