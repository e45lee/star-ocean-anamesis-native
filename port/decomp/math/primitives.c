// port/decomp/math/primitives.c: Ghidra decompiles for the math subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:09 UTC: tools/decomp.sh '--into' 'math/primitives' 'Aska::(Segment|Line|Ray|Box|Sphere|Plane|AABB|AABB_MinMax)::'

// ==== Aska::Segment::SquaredDistance(Aska::Segment const*, float*, float*) const
// vaddr 0x20aa82c | ghidra 0x21aa82c | size 2336 | symbol _ZNK4Aska7Segment15SquaredDistanceEPKS0_PfS3_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float _ZNK4Aska7Segment15SquaredDistanceEPKS0_PfS3_
                (float *param_1,float *param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  
  fVar1 = *param_1;
  fVar24 = *param_2;
  fVar25 = param_2[1];
  fVar2 = param_1[1];
  fVar20 = param_2[2];
  fVar17 = param_1[2];
  fVar19 = param_1[4] * param_1[4] + param_1[5] * param_1[5] + param_1[6] * param_1[6];
  fVar21 = SQRT(fVar19);
  if (NAN(fVar21)) {
    fVar21 = (float)sqrtf(fVar19);
  }
  fVar23 = param_2[4] * param_2[4] + param_2[5] * param_2[5] + param_2[6] * param_2[6];
  fVar22 = SQRT(fVar23);
  if (NAN(fVar22)) {
    fVar22 = (float)sqrtf(fVar23);
  }
  if (fVar19 == 0.0) {
    if (param_3 != (float *)0x0) {
      *param_3 = 0.0;
    }
    fVar19 = param_2[4];
    fVar20 = param_2[5];
    fVar24 = param_2[6];
    fVar21 = *param_1 - *param_2;
    fVar2 = param_1[1] - param_2[1];
    fVar1 = param_1[2] - param_2[2];
    fVar25 = fVar21 * fVar19 + fVar2 * fVar20 + fVar1 * fVar24;
    fVar17 = 0.0;
    if (0.0 < fVar25) {
      fVar17 = fVar19 * fVar19 + fVar20 * fVar20 + fVar24 * fVar24;
      if (fVar25 < fVar17) {
        fVar17 = fVar25 / fVar17;
        fVar21 = fVar21 - fVar19 * fVar17;
        fVar2 = fVar2 - fVar20 * fVar17;
        fVar1 = fVar1 - fVar24 * fVar17;
      }
      else {
        fVar21 = fVar21 - fVar19;
        fVar2 = fVar2 - fVar20;
        fVar1 = fVar1 - fVar24;
        fVar17 = 1.0;
      }
    }
    if (param_4 != (float *)0x0) {
      *param_4 = fVar17;
    }
code_r0x021aad78:
    return fVar21 * fVar21 + fVar2 * fVar2 + fVar1 * fVar1;
  }
  if (fVar23 == 0.0) {
    if (param_4 != (float *)0x0) {
      *param_4 = 0.0;
    }
    fVar19 = param_1[4];
    fVar20 = param_1[5];
    fVar24 = param_1[6];
    fVar21 = *param_2 - *param_1;
    fVar2 = param_2[1] - param_1[1];
    fVar1 = param_2[2] - param_1[2];
    fVar25 = fVar21 * fVar19 + fVar2 * fVar20 + fVar1 * fVar24;
    fVar17 = 0.0;
    if (0.0 < fVar25) {
      fVar17 = fVar19 * fVar19 + fVar20 * fVar20 + fVar24 * fVar24;
      if (fVar25 < fVar17) {
        fVar17 = fVar25 / fVar17;
        fVar21 = fVar21 - fVar19 * fVar17;
        fVar2 = fVar2 - fVar20 * fVar17;
        fVar1 = fVar1 - fVar24 * fVar17;
      }
      else {
        fVar21 = fVar21 - fVar19;
        fVar2 = fVar2 - fVar20;
        fVar1 = fVar1 - fVar24;
        fVar17 = 1.0;
      }
    }
    if (param_3 != (float *)0x0) {
      *param_3 = fVar17;
    }
    goto code_r0x021aad78;
  }
  fVar8 = param_1[4];
  fVar11 = param_1[5];
  fVar4 = param_1[6];
  fVar7 = fVar8 * fVar8 + fVar11 * fVar11 + fVar4 * fVar4;
  fVar3 = SQRT(fVar7);
  if (NAN(fVar3)) {
    fVar3 = (float)sqrtf(fVar7);
  }
  fVar7 = _UNK_027e519c;
  if (_UNK_027e519c <= fVar3) {
    fVar3 = 1.0 / fVar3;
    fVar8 = fVar3 * fVar8;
    fVar11 = fVar3 * fVar11;
    fVar4 = fVar3 * fVar4;
  }
  fVar3 = param_2[4];
  fVar12 = param_2[5];
  fVar6 = param_2[6];
  fVar9 = fVar3 * fVar3 + fVar12 * fVar12 + fVar6 * fVar6;
  fVar5 = SQRT(fVar9);
  if (NAN(fVar5)) {
    fVar5 = (float)sqrtf(fVar9);
  }
  fVar20 = fVar20 - fVar17;
  fVar24 = fVar24 - fVar1;
  fVar25 = fVar25 - fVar2;
  if (fVar7 <= fVar5) {
    fVar5 = 1.0 / fVar5;
    fVar3 = fVar5 * fVar3;
    fVar12 = fVar5 * fVar12;
    fVar6 = fVar5 * fVar6;
  }
  fVar1 = fVar24 * fVar24 + fVar25 * fVar25 + fVar20 * fVar20;
  fVar2 = SQRT(fVar1);
  if (NAN(fVar2)) {
    fVar2 = (float)sqrtf(fVar1);
  }
  fVar17 = fVar20;
  fVar5 = fVar24;
  fVar9 = fVar25;
  if (fVar7 <= fVar2) {
    fVar2 = 1.0 / fVar2;
    fVar5 = fVar24 * fVar2;
    fVar9 = fVar25 * fVar2;
    fVar17 = fVar20 * fVar2;
  }
  fVar2 = SQRT(fVar1);
  fVar18 = fVar4 * fVar6 + fVar11 * fVar12 + fVar8 * fVar3;
  if (NAN(fVar2)) {
    fVar2 = (float)sqrtf(fVar1);
  }
  fVar15 = fVar19 * fVar23 * (fVar18 * fVar18 + -1.0);
  fVar10 = 1.0;
  fVar14 = ABS(fVar15);
  fVar16 = -1.0;
  if (0.0 <= fVar15) {
    fVar16 = 1.0;
  }
  fVar13 = param_1[4] * param_2[4] + param_1[5] * param_2[5] + param_1[6] * param_2[6];
  fVar15 = fVar24 * param_1[4] + fVar25 * param_1[5] + fVar20 * param_1[6];
  fVar20 = fVar24 * param_2[4] + fVar25 * param_2[5] + fVar20 * param_2[6];
  if (fVar14 < fVar7) {
    if (fVar13 < 0.0) {
      fVar2 = 0.0;
      if (0.0 < fVar15) {
        if (fVar15 <= fVar19) goto code_r0x021aaf24;
        fVar13 = fVar13 - fVar20;
        if (fVar13 < fVar23) {
          fVar16 = fVar13 / fVar23;
          fVar1 = (fVar1 + fVar19) - fVar13 * fVar16;
          goto code_r0x021ab110;
        }
        fVar2 = (fVar20 - fVar13) + (fVar20 - fVar13);
code_r0x021ab078:
        fVar1 = fVar1 + fVar19 + fVar23 + fVar2;
code_r0x021ab13c:
        fVar10 = 1.0;
        fVar16 = 1.0;
        goto joined_r0x021ab0f8;
      }
    }
    else {
      if (fVar19 <= fVar15) goto code_r0x021ab024;
      if (0.0 <= fVar15) {
code_r0x021aaed8:
        fVar10 = fVar15 / fVar19;
        fVar1 = fVar1 - fVar15 * fVar10;
        goto joined_r0x021ab040;
      }
      if (fVar13 <= -fVar15) {
code_r0x021ab0b8:
        fVar1 = fVar1 + fVar23 + fVar20 + fVar20;
        fVar16 = 1.0;
        fVar10 = 0.0;
        goto joined_r0x021ab0f8;
      }
      fVar2 = -fVar15 / fVar13;
      fVar1 = fVar1 + fVar2 * (fVar20 + fVar20 + fVar23 * fVar2);
    }
    goto joined_r0x021ab0f8;
  }
  fVar24 = fVar17 * fVar6 + fVar9 * fVar12 + fVar5 * fVar3;
  fVar17 = fVar17 * fVar4 + fVar9 * fVar11 + fVar5 * fVar8;
  fVar21 = fVar16 * fVar23 * fVar21 * fVar2 * (fVar18 * fVar24 - fVar17);
  fVar16 = fVar16 * fVar19 * fVar22 * fVar2 * (fVar24 - fVar18 * fVar17);
  if (0.0 <= fVar21) {
    if (fVar21 <= fVar14) {
      if (fVar16 < 0.0) {
        fVar16 = 0.0;
        fVar2 = 0.0;
        if (0.0 < fVar15) {
          if (fVar19 <= fVar15) {
            fVar1 = fVar1 + fVar19;
code_r0x021ab110:
            fVar1 = fVar1 + fVar15 * -2.0;
            goto joined_r0x021ab0f8;
          }
code_r0x021aaf24:
          fVar16 = 0.0;
          fVar10 = fVar15 / fVar19;
          fVar1 = fVar1 - fVar15 * fVar10;
          goto joined_r0x021ab0f8;
        }
joined_r0x021ab0f8:
        fVar10 = 0.0;
        fVar16 = fVar2;
        goto joined_r0x021ab0f8;
      }
      if (fVar14 < fVar16) {
        fVar2 = fVar15 + fVar13;
        if (0.0 < fVar2) {
          if (fVar19 <= fVar2) {
            fVar1 = fVar19 + fVar1 + fVar23;
            goto code_r0x021ab130;
          }
          fVar10 = fVar2 / fVar19;
          fVar1 = (fVar1 + fVar23 + fVar20 + fVar20) - fVar2 * fVar10;
          goto code_r0x021ab0a8;
        }
        fVar2 = 1.0;
        fVar1 = fVar23 + fVar1 + fVar20 + fVar20;
        goto joined_r0x021ab0f8;
      }
      fVar10 = (1.0 / fVar14) * fVar21;
      fVar16 = (1.0 / fVar14) * fVar16;
      fVar20 = (fVar10 * (fVar19 * fVar10 + fVar15 * -2.0) +
               fVar16 * (fVar23 * fVar16 + fVar20 + fVar20)) - fVar13 * fVar16 * (fVar10 + fVar10);
code_r0x021aafd0:
      fVar1 = fVar1 + fVar20;
      goto joined_r0x021ab0f8;
    }
    if (0.0 <= fVar16) {
      if ((fVar14 < fVar16) && (fVar15 + fVar13 <= fVar19)) {
        if (fVar15 + fVar13 <= 0.0) goto code_r0x021ab0b8;
        goto code_r0x021ab08c;
      }
      fVar2 = fVar13 - fVar20;
      if (0.0 < fVar2) {
        if (fVar2 < fVar23) {
          fVar16 = fVar2 / fVar23;
          fVar1 = (fVar1 + fVar19) - fVar2 * fVar16;
          goto code_r0x021ab110;
        }
        goto code_r0x021ab060;
      }
    }
    else {
      if (fVar15 < fVar19) {
        fVar2 = 0.0;
        if (0.0 < fVar15) goto code_r0x021aaf24;
        goto joined_r0x021ab0f8;
      }
      fVar2 = fVar13 - fVar20;
      if (0.0 < fVar2) {
        if (fVar2 < fVar23) {
          fVar16 = fVar2 / fVar23;
          fVar1 = (fVar1 + fVar19 + fVar15 * -2.0) - fVar2 * fVar16;
          goto joined_r0x021ab0f8;
        }
code_r0x021ab060:
        fVar2 = (fVar15 + (fVar13 - fVar20)) * -2.0;
        goto code_r0x021ab078;
      }
    }
code_r0x021ab024:
    fVar1 = fVar1 + fVar19 + fVar15 * -2.0;
joined_r0x021ab040:
    fVar16 = 0.0;
  }
  else {
    if (0.0 <= fVar16) {
      if ((fVar16 <= fVar14) || (fVar15 + fVar13 < 0.0)) goto code_r0x021aae70;
      if (fVar19 <= fVar15 + fVar13) {
        fVar1 = fVar1 + fVar19 + fVar23;
code_r0x021ab130:
        fVar20 = fVar20 - (fVar15 + fVar13);
        fVar1 = fVar1 + fVar20 + fVar20;
        goto code_r0x021ab13c;
      }
code_r0x021ab08c:
      fVar10 = (fVar15 + fVar13) / fVar19;
      fVar1 = fVar20 + fVar20 + ((fVar1 + fVar23) - (fVar15 + fVar13) * fVar10);
    }
    else {
      if (0.0 <= fVar15) {
        if (fVar15 < fVar19) goto code_r0x021aaed8;
        goto code_r0x021ab024;
      }
code_r0x021aae70:
      fVar10 = 0.0;
      if (0.0 <= fVar20) goto joined_r0x021ab040;
      if (-fVar20 < fVar23) {
        fVar16 = -fVar20 / fVar23;
        fVar20 = fVar20 * fVar16;
        goto code_r0x021aafd0;
      }
      fVar1 = fVar1 + fVar23 + fVar20 + fVar20;
    }
code_r0x021ab0a8:
    fVar16 = 1.0;
  }
joined_r0x021ab0f8:
  if (param_3 != (float *)0x0) {
    *param_3 = fVar10;
  }
  if (param_4 == (float *)0x0) {
    return fVar1;
  }
  *param_4 = fVar16;
  return fVar1;
}

// ==== Aska::Segment::SquaredDistance(Aska::Vector const*, float*) const
// vaddr 0x20ab14c | ghidra 0x21ab14c | size 164 | symbol _ZNK4Aska7Segment15SquaredDistanceEPKNS_6VectorEPf | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK4Aska7Segment15SquaredDistanceEPKNS_6VectorEPf
                (float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  fVar7 = param_1[4];
  fVar3 = *param_2 - *param_1;
  fVar1 = (float)*(undefined8 *)(param_2 + 1) - (float)*(undefined8 *)(param_1 + 1);
  fVar2 = (float)((ulong)*(undefined8 *)(param_2 + 1) >> 0x20) -
          (float)((ulong)*(undefined8 *)(param_1 + 1) >> 0x20);
  fVar5 = (float)*(undefined8 *)(param_1 + 5);
  fVar6 = (float)((ulong)*(undefined8 *)(param_1 + 5) >> 0x20);
  fVar8 = fVar3 * fVar7 + fVar1 * fVar5 + fVar2 * fVar6;
  fVar4 = 0.0;
  if (0.0 < fVar8) {
    fVar4 = fVar7 * fVar7 + fVar5 * fVar5 + fVar6 * fVar6;
    if (fVar4 <= fVar8) {
      fVar3 = fVar3 - fVar7;
      fVar1 = fVar1 - fVar5;
      fVar2 = fVar2 - fVar6;
      fVar4 = 1.0;
    }
    else {
      fVar4 = fVar8 / fVar4;
      fVar3 = fVar3 - fVar7 * fVar4;
      fVar1 = fVar1 - fVar5 * fVar4;
      fVar2 = fVar2 - fVar6 * fVar4;
    }
  }
  if (param_3 != (float *)0x0) {
    *param_3 = fVar4;
  }
  return fVar3 * fVar3 + fVar1 * fVar1 + fVar2 * fVar2;
}

// ==== Aska::AABB::ComputeVertices(Aska::Vector*) const
// vaddr 0x2330c3c | ghidra 0x2430c3c | size 64 | symbol _ZNK4Aska4AABB15ComputeVerticesEPNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska4AABB15ComputeVerticesEPNS_6VectorE(long param_1,undefined8 param_2)

{
  undefined4 uStack_40;
  undefined8 uStack_3c;
  undefined8 uStack_34;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  uStack_40 = *(undefined4 *)(param_1 + 0x10);
  uStack_2c = *(undefined4 *)(param_1 + 0x14);
  uStack_34 = 0;
  uStack_3c = 0;
  uStack_18 = *(undefined4 *)(param_1 + 0x18);
  uStack_20 = 0;
  uStack_28 = 0;
  uStack_14 = 0;
  Aska::AABB::ComputeVertices(Aska::Vector*, Aska::Vector const*) const(param_1,param_2,&uStack_40);
  return;
}

// ==== Aska::AABB::ComputeVertices(Aska::Vector*, Aska::Vector const*) const
// vaddr 0x2330c7c | ghidra 0x2430c7c | size 676 | symbol _ZNK4Aska4AABB15ComputeVerticesEPNS_6VectorEPKS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska4AABB15ComputeVerticesEPNS_6VectorEPKS1_(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  
  fVar1 = *param_1;
  fVar2 = param_1[1];
  fVar3 = *param_3;
  fVar6 = param_3[1];
  fVar9 = param_1[2];
  fVar10 = param_3[2];
  fVar4 = param_3[4];
  fVar7 = param_3[5];
  fVar11 = param_3[6];
  fVar5 = param_3[8];
  fVar8 = param_3[9];
  fVar12 = param_3[10];
  param_2[0x1f] = param_1[3];
  param_2[0x1c] = ((fVar1 - fVar3) - fVar4) - fVar5;
  param_2[0x1d] = ((fVar2 - fVar6) - fVar7) - fVar8;
  param_2[0x1e] = ((fVar9 - fVar10) - fVar11) - fVar12;
  fVar1 = *param_1;
  fVar2 = param_1[1];
  fVar3 = *param_3;
  fVar6 = param_3[1];
  fVar9 = param_1[2];
  fVar10 = param_3[2];
  fVar4 = param_3[4];
  fVar7 = param_3[5];
  fVar11 = param_3[6];
  fVar5 = param_3[8];
  fVar8 = param_3[9];
  fVar12 = param_3[10];
  param_2[0xf] = param_1[3];
  param_2[0xc] = ((fVar1 + fVar3) - fVar4) - fVar5;
  param_2[0xd] = ((fVar2 + fVar6) - fVar7) - fVar8;
  param_2[0xe] = ((fVar9 + fVar10) - fVar11) - fVar12;
  fVar1 = *param_1;
  fVar2 = param_1[1];
  fVar3 = *param_3;
  fVar6 = param_3[1];
  fVar9 = param_1[2];
  fVar10 = param_3[2];
  fVar4 = param_3[4];
  fVar7 = param_3[5];
  fVar11 = param_3[6];
  fVar5 = param_3[8];
  fVar8 = param_3[9];
  fVar12 = param_3[10];
  param_2[7] = param_1[3];
  param_2[4] = (fVar1 + fVar3 + fVar4) - fVar5;
  param_2[5] = (fVar2 + fVar6 + fVar7) - fVar8;
  param_2[6] = (fVar9 + fVar10 + fVar11) - fVar12;
  fVar1 = *param_1;
  fVar2 = param_1[1];
  fVar3 = *param_3;
  fVar6 = param_3[1];
  fVar9 = param_1[2];
  fVar10 = param_3[2];
  fVar4 = param_3[4];
  fVar7 = param_3[5];
  fVar11 = param_3[6];
  fVar5 = param_3[8];
  fVar8 = param_3[9];
  fVar12 = param_3[10];
  param_2[0x17] = param_1[3];
  param_2[0x14] = ((fVar1 - fVar3) + fVar4) - fVar5;
  param_2[0x15] = ((fVar2 - fVar6) + fVar7) - fVar8;
  param_2[0x16] = ((fVar9 - fVar10) + fVar11) - fVar12;
  fVar1 = *param_1;
  fVar2 = param_1[1];
  fVar3 = *param_3;
  fVar6 = param_3[1];
  fVar9 = param_1[2];
  fVar10 = param_3[2];
  fVar4 = param_3[4];
  fVar7 = param_3[5];
  fVar11 = param_3[6];
  fVar5 = param_3[8];
  fVar8 = param_3[9];
  fVar12 = param_3[10];
  param_2[0x1b] = param_1[3];
  param_2[0x18] = ((fVar1 - fVar3) - fVar4) + fVar5;
  param_2[0x19] = ((fVar2 - fVar6) - fVar7) + fVar8;
  param_2[0x1a] = ((fVar9 - fVar10) - fVar11) + fVar12;
  fVar1 = *param_1;
  fVar2 = param_1[1];
  fVar3 = *param_3;
  fVar6 = param_3[1];
  fVar9 = param_1[2];
  fVar10 = param_3[2];
  fVar4 = param_3[4];
  fVar7 = param_3[5];
  fVar11 = param_3[6];
  fVar5 = param_3[8];
  fVar8 = param_3[9];
  fVar12 = param_3[10];
  param_2[0xb] = param_1[3];
  param_2[8] = ((fVar1 + fVar3) - fVar4) + fVar5;
  param_2[9] = ((fVar2 + fVar6) - fVar7) + fVar8;
  param_2[10] = ((fVar9 + fVar10) - fVar11) + fVar12;
  fVar1 = *param_1;
  fVar2 = param_1[1];
  fVar3 = *param_3;
  fVar6 = param_3[1];
  fVar9 = param_1[2];
  fVar10 = param_3[2];
  fVar4 = param_3[4];
  fVar7 = param_3[5];
  fVar11 = param_3[6];
  fVar5 = param_3[8];
  fVar8 = param_3[9];
  fVar12 = param_3[10];
  param_2[3] = param_1[3];
  *param_2 = fVar1 + fVar3 + fVar4 + fVar5;
  param_2[1] = fVar2 + fVar6 + fVar7 + fVar8;
  param_2[2] = fVar9 + fVar10 + fVar11 + fVar12;
  fVar1 = *param_1;
  fVar2 = param_1[1];
  fVar3 = *param_3;
  fVar6 = param_3[1];
  fVar9 = param_1[2];
  fVar10 = param_3[2];
  fVar4 = param_3[4];
  fVar7 = param_3[5];
  fVar11 = param_3[6];
  fVar5 = param_3[8];
  fVar8 = param_3[9];
  fVar12 = param_3[10];
  param_2[0x13] = param_1[3];
  param_2[0x10] = (fVar1 - fVar3) + fVar4 + fVar5;
  param_2[0x11] = (fVar2 - fVar6) + fVar7 + fVar8;
  param_2[0x12] = (fVar9 - fVar10) + fVar11 + fVar12;
  return;
}

// ==== Aska::Box::ComputeVertices(Aska::Vector*) const
// vaddr 0x2330f20 | ghidra 0x2430f20 | size 228 | symbol _ZNK4Aska3Box15ComputeVerticesEPNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK4Aska3Box15ComputeVerticesEPNS_6VectorE(undefined8 *param_1,undefined8 *param_2)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  
  if (((bRam0000000002e75af0 & 1) == 0) && (iVar1 = __cxa_guard_acquire(0x2e75af0), iVar1 != 0)) {
    uRam0000000002e75b08 = _UNK_027ed8b8;
    uRam0000000002e75b00 = _UNK_027ed8b0;
    __cxa_guard_release(0x2e75af0);
  }
  fVar2 = (float)param_1[2];
  fVar4 = (float)uRam0000000002e75b00;
  fVar7 = (float)((ulong)uRam0000000002e75b00 >> 0x20);
  fVar9 = (float)uRam0000000002e75b08;
  fVar11 = (float)((ulong)uRam0000000002e75b08 >> 0x20);
  fVar3 = (float)((ulong)param_1[2] >> 0x20);
  fVar6 = (float)param_1[4] * fVar4 * fVar2;
  fVar8 = (float)((ulong)param_1[4] >> 0x20) * fVar7 * fVar2;
  fVar10 = (float)param_1[5] * fVar9 * fVar2;
  fVar12 = (float)((ulong)param_1[5] >> 0x20) * fVar11 * fVar2;
  fVar5 = (float)param_1[3];
  fVar14 = (float)param_1[6] * fVar4 * fVar3;
  fVar15 = (float)((ulong)param_1[6] >> 0x20) * fVar7 * fVar3;
  fVar16 = (float)param_1[7] * fVar9 * fVar3;
  fVar17 = (float)((ulong)param_1[7] >> 0x20) * fVar11 * fVar3;
  fVar2 = (float)*param_1;
  fVar18 = fVar2 + fVar6;
  fVar3 = (float)((ulong)*param_1 >> 0x20);
  fVar19 = fVar3 + fVar8;
  fVar20 = *(float *)(param_1 + 1) + fVar10;
  fVar21 = fVar12 + 1.0;
  fVar2 = fVar2 - fVar6;
  fVar3 = fVar3 - fVar8;
  fVar10 = *(float *)(param_1 + 1) - fVar10;
  fVar12 = 1.0 - fVar12;
  fVar6 = (float)param_1[8] * fVar4 * fVar5;
  fVar8 = (float)((ulong)param_1[8] >> 0x20) * fVar7 * fVar5;
  fVar4 = (float)param_1[9] * fVar9 * fVar5;
  fVar5 = (float)((ulong)param_1[9] >> 0x20) * fVar11 * fVar5;
  fVar7 = fVar14 + fVar18;
  fVar9 = fVar15 + fVar19;
  fVar11 = fVar16 + fVar20;
  fVar13 = fVar17 + fVar21;
  fVar18 = fVar18 - fVar14;
  fVar19 = fVar19 - fVar15;
  fVar20 = fVar20 - fVar16;
  fVar21 = fVar21 - fVar17;
  fVar22 = fVar14 + fVar2;
  fVar23 = fVar15 + fVar3;
  fVar24 = fVar16 + fVar10;
  fVar25 = fVar17 + fVar12;
  fVar2 = fVar2 - fVar14;
  fVar3 = fVar3 - fVar15;
  fVar10 = fVar10 - fVar16;
  fVar12 = fVar12 - fVar17;
  param_2[1] = CONCAT44(fVar5 + fVar13,fVar4 + fVar11);
  *param_2 = CONCAT44(fVar8 + fVar9,fVar6 + fVar7);
  param_2[3] = CONCAT44(fVar13 - fVar5,fVar11 - fVar4);
  param_2[2] = CONCAT44(fVar9 - fVar8,fVar7 - fVar6);
  param_2[5] = CONCAT44(fVar5 + fVar21,fVar4 + fVar20);
  param_2[4] = CONCAT44(fVar8 + fVar19,fVar6 + fVar18);
  param_2[7] = CONCAT44(fVar21 - fVar5,fVar20 - fVar4);
  param_2[6] = CONCAT44(fVar19 - fVar8,fVar18 - fVar6);
  param_2[9] = CONCAT44(fVar5 + fVar25,fVar4 + fVar24);
  param_2[8] = CONCAT44(fVar8 + fVar23,fVar6 + fVar22);
  param_2[0xb] = CONCAT44(fVar25 - fVar5,fVar24 - fVar4);
  param_2[10] = CONCAT44(fVar23 - fVar8,fVar22 - fVar6);
  param_2[0xd] = CONCAT44(fVar5 + fVar12,fVar4 + fVar10);
  param_2[0xc] = CONCAT44(fVar8 + fVar3,fVar6 + fVar2);
  param_2[0xf] = CONCAT44(fVar12 - fVar5,fVar10 - fVar4);
  param_2[0xe] = CONCAT44(fVar3 - fVar8,fVar2 - fVar6);
  return;
}

// ==== Aska::Box::ComputePlanes(Aska::Plane*, bool) const
// vaddr 0x2331004 | ghidra 0x2431004 | size 564 | symbol _ZNK4Aska3Box13ComputePlanesEPNS_5PlaneEb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK4Aska3Box13ComputePlanesEPNS_5PlaneEb(undefined8 *param_1,undefined8 *param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  
  fVar4 = -1.0;
  if ((param_3 & 1) == 0) {
    fVar4 = 1.0;
  }
  if (((bRam0000000002e75af0 & 1) == 0) && (iVar2 = __cxa_guard_acquire(0x2e75af0), iVar2 != 0)) {
    uRam0000000002e75b08 = _UNK_027ed8b8;
    uRam0000000002e75b00 = _UNK_027ed8b0;
    __cxa_guard_release(0x2e75af0);
  }
  fVar9 = (float)param_1[2];
  fVar3 = (float)uRam0000000002e75b00;
  fVar5 = (float)((ulong)uRam0000000002e75b00 >> 0x20);
  fVar6 = (float)uRam0000000002e75b08;
  fVar15 = (float)((ulong)uRam0000000002e75b08 >> 0x20);
  fVar22 = (float)((ulong)param_1[2] >> 0x20);
  fVar7 = (float)param_1[3];
  fVar10 = (float)param_1[4];
  fVar8 = fVar10 * fVar3 * fVar9;
  fVar11 = (float)((ulong)param_1[4] >> 0x20) * fVar5 * fVar9;
  fVar12 = (float)param_1[5] * fVar6 * fVar9;
  fVar13 = (float)((ulong)param_1[5] >> 0x20) * fVar15 * fVar9;
  fVar14 = (float)param_1[6] * fVar3 * fVar22;
  fVar16 = (float)((ulong)param_1[6] >> 0x20) * fVar5 * fVar22;
  fVar18 = (float)param_1[7] * fVar6 * fVar22;
  fVar20 = (float)((ulong)param_1[7] >> 0x20) * fVar15 * fVar22;
  fVar3 = (float)param_1[8] * fVar3 * fVar7;
  fVar5 = (float)((ulong)param_1[8] >> 0x20) * fVar5 * fVar7;
  fVar6 = (float)param_1[9] * fVar6 * fVar7;
  fVar7 = (float)((ulong)param_1[9] >> 0x20) * fVar15 * fVar7;
  fVar9 = (float)*param_1;
  fVar22 = (float)((ulong)*param_1 >> 0x20);
  fVar15 = fVar3 + fVar14 + fVar9 + fVar8;
  fVar17 = fVar5 + fVar16 + fVar22 + fVar11;
  fVar19 = fVar6 + fVar18 + *(float *)(param_1 + 1) + fVar12;
  fVar21 = fVar7 + fVar20 + fVar13 + 1.0;
  fVar3 = ((fVar9 - fVar8) - fVar14) - fVar3;
  fVar5 = ((fVar22 - fVar11) - fVar16) - fVar5;
  fVar6 = ((*(float *)(param_1 + 1) - fVar12) - fVar18) - fVar6;
  fVar7 = ((1.0 - fVar13) - fVar20) - fVar7;
  fVar9 = *(float *)((long)param_1 + 0x24);
  fVar22 = *(float *)(param_1 + 5);
  uVar1 = *(undefined4 *)((long)param_1 + 0x2c);
  param_2[1] = CONCAT44(fVar21,fVar19);
  *param_2 = CONCAT44(fVar17,fVar15);
  *(undefined4 *)((long)param_2 + 0x1c) = uVar1;
  *(float *)(param_2 + 2) = fVar4 * fVar10;
  *(float *)((long)param_2 + 0x14) = fVar4 * fVar9;
  *(float *)(param_2 + 3) = fVar4 * fVar22;
  fVar22 = *(float *)(param_1 + 4);
  fVar10 = *(float *)((long)param_1 + 0x24);
  fVar8 = *(float *)(param_1 + 5);
  uVar1 = *(undefined4 *)((long)param_1 + 0x2c);
  fVar9 = -fVar4;
  *(float *)(param_2 + 4) = fVar3;
  *(ulong *)((long)param_2 + 0x24) = CONCAT44(fVar6,fVar5);
  *(float *)((long)param_2 + 0x2c) = fVar7;
  *(undefined4 *)((long)param_2 + 0x3c) = uVar1;
  *(float *)(param_2 + 6) = fVar22 * fVar9;
  *(float *)((long)param_2 + 0x34) = fVar10 * fVar9;
  *(float *)(param_2 + 7) = fVar8 * fVar9;
  fVar22 = *(float *)(param_1 + 6);
  fVar10 = *(float *)((long)param_1 + 0x34);
  fVar8 = *(float *)(param_1 + 7);
  uVar1 = *(undefined4 *)((long)param_1 + 0x3c);
  *(float *)(param_2 + 8) = fVar15;
  *(float *)((long)param_2 + 0x44) = fVar17;
  *(float *)(param_2 + 9) = fVar19;
  *(float *)((long)param_2 + 0x4c) = fVar21;
  *(undefined4 *)((long)param_2 + 0x5c) = uVar1;
  *(float *)(param_2 + 10) = fVar4 * fVar22;
  *(float *)((long)param_2 + 0x54) = fVar4 * fVar10;
  *(float *)(param_2 + 0xb) = fVar4 * fVar8;
  fVar22 = *(float *)(param_1 + 6);
  fVar10 = *(float *)((long)param_1 + 0x34);
  fVar8 = *(float *)(param_1 + 7);
  uVar1 = *(undefined4 *)((long)param_1 + 0x3c);
  *(float *)(param_2 + 0xc) = fVar3;
  *(float *)((long)param_2 + 100) = fVar5;
  *(float *)(param_2 + 0xd) = fVar6;
  *(float *)((long)param_2 + 0x6c) = fVar7;
  *(undefined4 *)((long)param_2 + 0x7c) = uVar1;
  *(float *)(param_2 + 0xe) = fVar22 * fVar9;
  *(float *)((long)param_2 + 0x74) = fVar10 * fVar9;
  *(float *)(param_2 + 0xf) = fVar8 * fVar9;
  fVar22 = *(float *)(param_1 + 8);
  fVar10 = *(float *)((long)param_1 + 0x44);
  fVar8 = *(float *)(param_1 + 9);
  uVar1 = *(undefined4 *)((long)param_1 + 0x4c);
  *(float *)(param_2 + 0x10) = fVar15;
  *(float *)((long)param_2 + 0x84) = fVar17;
  *(float *)(param_2 + 0x11) = fVar19;
  *(float *)((long)param_2 + 0x8c) = fVar21;
  *(undefined4 *)((long)param_2 + 0x9c) = uVar1;
  *(float *)(param_2 + 0x12) = fVar4 * fVar22;
  *(float *)((long)param_2 + 0x94) = fVar4 * fVar10;
  *(float *)(param_2 + 0x13) = fVar4 * fVar8;
  fVar4 = *(float *)(param_1 + 8);
  fVar22 = *(float *)((long)param_1 + 0x44);
  fVar10 = *(float *)(param_1 + 9);
  uVar1 = *(undefined4 *)((long)param_1 + 0x4c);
  *(float *)(param_2 + 0x14) = fVar3;
  *(float *)((long)param_2 + 0xa4) = fVar5;
  *(float *)(param_2 + 0x15) = fVar6;
  *(float *)((long)param_2 + 0xac) = fVar7;
  *(float *)(param_2 + 0x16) = fVar4 * fVar9;
  *(float *)((long)param_2 + 0xb4) = fVar22 * fVar9;
  *(float *)(param_2 + 0x17) = fVar10 * fVar9;
  *(undefined4 *)((long)param_2 + 0xbc) = uVar1;
  return;
}

// ==== Aska::Box::SquaredDistance(Aska::Line const*, float*, float*, float*, float*) const
// vaddr 0x2331238 | ghidra 0x2431238 | size 1360 | symbol _ZNK4Aska3Box15SquaredDistanceEPKNS_4LineEPfS4_S4_S4_ | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK4Aska3Box15SquaredDistanceEPKNS_4LineEPfS4_S4_S4_
                (undefined8 *param_1,undefined8 *param_2,float *param_3,float *param_4,
                float *param_5,float *param_6)

{
  undefined1 (*pauVar1) [12];
  undefined1 (*pauVar2) [12];
  undefined1 (*pauVar3) [12];
  undefined1 (*pauVar4) [12];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  bool bVar10;
  bool bVar11;
  bool bVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  float fVar16;
  float fVar17;
  undefined4 uVar18;
  float fVar19;
  float fVar20;
  undefined4 uVar21;
  float fVar22;
  float fVar23;
  undefined4 uVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  undefined4 uVar31;
  undefined1 auVar32 [16];
  undefined1 auVar33 [16];
  undefined1 auVar34 [16];
  float fVar35;
  undefined1 auVar36 [16];
  float fVar37;
  undefined1 auVar38 [16];
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  undefined4 uStack_54;
  float fStack_50;
  float fStack_4c;
  undefined8 uStack_48;
  float fStack_34;
  
  pauVar3 = (undefined1 (*) [12])(param_2 + 2);
  uVar31 = (undefined4)((ulong)param_2[3] >> 0x20);
  fVar29 = (float)*(undefined8 *)*pauVar3;
  fVar30 = (float)((ulong)*(undefined8 *)*pauVar3 >> 0x20);
  pauVar2 = (undefined1 (*) [12])(param_1 + 4);
  uVar18 = (undefined4)((ulong)param_1[5] >> 0x20);
  fVar16 = (float)*(undefined8 *)*pauVar2;
  fVar17 = (float)((ulong)*(undefined8 *)*pauVar2 >> 0x20);
  pauVar4 = (undefined1 (*) [12])(param_1 + 6);
  uVar21 = (undefined4)((ulong)param_1[7] >> 0x20);
  fVar19 = (float)*(undefined8 *)*pauVar4;
  fVar20 = (float)((ulong)*(undefined8 *)*pauVar4 >> 0x20);
  pauVar1 = (undefined1 (*) [12])(param_1 + 8);
  uVar24 = (undefined4)((ulong)param_1[9] >> 0x20);
  fVar22 = (float)*(undefined8 *)*pauVar1;
  fVar23 = (float)((ulong)*(undefined8 *)*pauVar1 >> 0x20);
  fVar25 = (float)*param_2 - (float)*param_1;
  fVar26 = (float)((ulong)*param_2 >> 0x20) - (float)((ulong)*param_1 >> 0x20);
  fVar27 = (float)param_2[1] - (float)param_1[1];
  fVar28 = (float)((ulong)param_2[1] >> 0x20) - (float)((ulong)param_1[1] >> 0x20);
  auVar32._12_4_ = uVar18;
  auVar32._0_12_ = *pauVar2;
  auVar33._12_4_ = uVar18;
  auVar33._0_12_ = *pauVar2;
  auVar32 = NEON_ext(auVar32,auVar33,8,1);
  auVar34._12_4_ = uVar21;
  auVar34._0_12_ = *pauVar4;
  auVar36._12_4_ = uVar21;
  auVar36._0_12_ = *pauVar4;
  auVar33 = NEON_ext(auVar34,auVar36,8,1);
  auVar8._12_4_ = uVar31;
  auVar8._0_12_ = *pauVar3;
  auVar9._12_4_ = uVar31;
  auVar9._0_12_ = *pauVar3;
  auVar36 = NEON_ext(auVar8,auVar9,8,1);
  auVar38._4_4_ = fVar26;
  auVar38._0_4_ = fVar25;
  auVar38._8_4_ = fVar27;
  auVar38._12_4_ = fVar28;
  auVar7._4_4_ = fVar26;
  auVar7._0_4_ = fVar25;
  auVar7._8_4_ = fVar27;
  auVar7._12_4_ = fVar28;
  auVar38 = NEON_ext(auVar38,auVar7,8,1);
  auVar5._12_4_ = uVar24;
  auVar5._0_12_ = *pauVar1;
  auVar6._12_4_ = uVar24;
  auVar6._0_12_ = *pauVar1;
  auVar34 = NEON_ext(auVar5,auVar6,8,1);
  fVar35 = auVar36._0_4_;
  fVar37 = auVar38._0_4_;
  fVar27 = fVar29 * fVar16 + fVar35 * auVar32._0_4_ + fVar30 * fVar17 + 0.0;
  fVar28 = fVar29 * fVar19 + fVar35 * auVar33._0_4_ + fVar30 * fVar20 + 0.0;
  fStack_50 = fVar25 * fVar16 + fVar37 * auVar32._0_4_ + fVar26 * fVar17 + 0.0;
  fStack_4c = fVar25 * fVar19 + fVar37 * auVar33._0_4_ + fVar26 * fVar20 + 0.0;
  fVar16 = fVar29 * fVar22 + fVar35 * auVar34._0_4_ + fVar30 * fVar23 + 0.0;
  fVar17 = fVar25 * fVar22 + fVar37 * auVar34._0_4_ + fVar26 * fVar23 + 0.0;
  bVar12 = fVar27 < 0.0;
  if (bVar12) {
    fStack_50 = -fStack_50;
    fVar27 = -fVar27;
  }
  _fStack_60 = CONCAT44(fVar28,fVar27);
  if (0.0 <= fVar28) {
    bVar10 = false;
    if (0.0 <= fVar16) goto code_r0x02431364;
code_r0x02431378:
    fVar17 = -fVar17;
    fVar16 = -fVar16;
    bVar11 = true;
  }
  else {
    fStack_4c = -fStack_4c;
    fVar28 = -fVar28;
    bVar10 = true;
    _fStack_60 = CONCAT44(fVar28,fVar27);
    if (fVar16 < 0.0) goto code_r0x02431378;
code_r0x02431364:
    bVar11 = false;
  }
  uStack_48 = CONCAT44(0x3f800000,fVar17);
  _fStack_58 = CONCAT44(0x3f800000,fVar16);
  fStack_34 = 0.0;
  if (fVar27 <= 0.0) {
    if (fVar28 <= 0.0) {
      if (0.0 < fVar16) {
        if (param_3 != (float *)0x0) {
          *param_3 = (*(float *)(param_1 + 3) - fVar17) / fVar16;
        }
        *(undefined4 *)((ulong)&fStack_50 | 8) = *(undefined4 *)(param_1 + 3);
        fVar27 = *(float *)(param_1 + 2);
        if (-fVar27 <= fStack_50) {
          if (fVar27 < fStack_50) {
            fStack_34 = (fStack_50 - fVar27) * (fStack_50 - fVar27);
            goto code_r0x024315a0;
          }
        }
        else {
          fStack_34 = (fStack_50 + fVar27) * (fStack_50 + fVar27);
          fVar27 = -fVar27;
code_r0x024315a0:
          fStack_34 = fStack_34 + 0.0;
          fStack_50 = fVar27;
        }
        fVar27 = *(float *)((long)param_1 + 0x14);
        if (-fVar27 <= fStack_4c) {
          if (fStack_4c <= fVar27) goto joined_r0x0243144c;
          fVar16 = (fStack_4c - fVar27) * (fStack_4c - fVar27);
        }
        else {
          fVar16 = (fStack_4c + fVar27) * (fStack_4c + fVar27);
          fVar27 = -fVar27;
        }
        fStack_34 = fVar16 + fStack_34;
        fStack_4c = fVar27;
        goto joined_r0x0243144c;
      }
      fVar27 = *(float *)(param_1 + 2);
      if (-fVar27 <= fStack_50) {
        if (fVar27 < fStack_50) {
          fStack_34 = (fStack_50 - fVar27) * (fStack_50 - fVar27);
          goto code_r0x024314c4;
        }
      }
      else {
        fStack_34 = (fStack_50 + fVar27) * (fStack_50 + fVar27);
        fVar27 = -fVar27;
code_r0x024314c4:
        fStack_34 = fStack_34 + 0.0;
        fStack_50 = fVar27;
      }
      fVar27 = *(float *)((long)param_1 + 0x14);
      if (-fVar27 <= fStack_4c) {
        if (fVar27 < fStack_4c) {
          fVar16 = (fStack_4c - fVar27) * (fStack_4c - fVar27);
          goto code_r0x02431504;
        }
      }
      else {
        fVar16 = (fStack_4c + fVar27) * (fStack_4c + fVar27);
        fVar27 = -fVar27;
code_r0x02431504:
        fStack_34 = fVar16 + fStack_34;
        fStack_4c = fVar27;
      }
      fVar27 = *(float *)(param_1 + 3);
      if (-fVar27 <= fVar17) {
        if (fVar27 < fVar17) {
          fVar16 = (fVar17 - fVar27) * (fVar17 - fVar27);
          goto code_r0x02431540;
        }
      }
      else {
        fVar16 = (fVar17 + fVar27) * (fVar17 + fVar27);
        fVar27 = -fVar27;
code_r0x02431540:
        fStack_34 = fVar16 + fStack_34;
        uStack_48 = (ulong)(uint)fVar27;
      }
      if (param_3 != (float *)0x0) {
        *param_3 = 0.0;
      }
      goto joined_r0x0243144c;
    }
    if (fVar16 <= 0.0) {
      if (param_3 != (float *)0x0) {
        *param_3 = (*(float *)((long)param_1 + 0x14) - fStack_4c) / fVar28;
      }
      *(undefined4 *)((ulong)&fStack_50 | 4) = *(undefined4 *)((long)param_1 + 0x14);
      fVar27 = *(float *)(param_1 + 2);
      if (-fVar27 <= fStack_50) {
        if (fVar27 < fStack_50) {
          fStack_34 = (fStack_50 - fVar27) * (fStack_50 - fVar27);
          goto code_r0x02431638;
        }
      }
      else {
        fStack_34 = (fStack_50 + fVar27) * (fStack_50 + fVar27);
        fVar27 = -fVar27;
code_r0x02431638:
        fStack_34 = fStack_34 + 0.0;
        fStack_50 = fVar27;
      }
      fVar27 = *(float *)(param_1 + 3);
      if (-fVar27 <= fVar17) {
        if (fVar17 <= fVar27) goto joined_r0x0243144c;
        fVar16 = (fVar17 - fVar27) * (fVar17 - fVar27);
      }
      else {
        fVar16 = (fVar17 + fVar27) * (fVar17 + fVar27);
        fVar27 = -fVar27;
      }
      fStack_34 = fVar16 + fStack_34;
      uStack_48 = (ulong)(uint)fVar27;
      goto joined_r0x0243144c;
    }
    uVar13 = 1;
    uVar14 = 2;
    uVar15 = 0;
  }
  else {
    if (fVar28 <= 0.0) {
      if (fVar16 <= 0.0) {
        if (param_3 != (float *)0x0) {
          *param_3 = (*(float *)(param_1 + 2) - fStack_50) / fVar27;
        }
        fStack_50 = *(float *)(param_1 + 2);
        fVar27 = *(float *)((long)param_1 + 0x14);
        if (-fVar27 <= fStack_4c) {
          if (fVar27 < fStack_4c) {
            fStack_34 = (fStack_4c - fVar27) * (fStack_4c - fVar27);
            goto code_r0x024316cc;
          }
        }
        else {
          fStack_34 = (fStack_4c + fVar27) * (fStack_4c + fVar27);
          fVar27 = -fVar27;
code_r0x024316cc:
          fStack_34 = fStack_34 + 0.0;
          fStack_4c = fVar27;
        }
        fVar27 = *(float *)(param_1 + 3);
        if (-fVar27 <= fVar17) {
          if (fVar17 <= fVar27) goto joined_r0x0243144c;
          fVar16 = (fVar17 - fVar27) * (fVar17 - fVar27);
        }
        else {
          fVar16 = (fVar17 + fVar27) * (fVar17 + fVar27);
          fVar27 = -fVar27;
        }
        fStack_34 = fVar16 + fStack_34;
        uStack_48 = (ulong)(uint)fVar27;
        goto joined_r0x0243144c;
      }
      uVar14 = 2;
      uVar15 = 1;
    }
    else {
      if (0.0 < fVar16) {
        Aska::Box::CaseNoZeros(Aska::Vector*, Aska::Vector const*, float*, float*) const(param_1,&fStack_50,&fStack_60,param_3,&fStack_34);
        goto joined_r0x0243144c;
      }
      uVar14 = 1;
      uVar15 = 2;
    }
    uVar13 = 0;
  }
  Aska::Box::Case0(int, int, int, Aska::Vector*, Aska::Vector const*, float*, float*) const(param_1,uVar13,uVar14,uVar15,&fStack_50,&fStack_60,param_3,&fStack_34);
joined_r0x0243144c:
  if (bVar12) {
    fStack_50 = -fStack_50;
  }
  if (bVar10) {
    fStack_4c = -fStack_4c;
  }
  if (bVar11) {
    uStack_48._0_4_ = -(float)uStack_48;
  }
  if (param_4 != (float *)0x0) {
    *param_4 = fStack_50;
  }
  if (param_5 != (float *)0x0) {
    *param_5 = fStack_4c;
  }
  if (param_6 != (float *)0x0) {
    *param_6 = (float)uStack_48;
  }
  return fStack_34;
}

// ==== Aska::Box::CaseNoZeros(Aska::Vector*, Aska::Vector const*, float*, float*) const
// vaddr 0x2331788 | ghidra 0x2431788 | size 216 | symbol _ZNK4Aska3Box11CaseNoZerosEPNS_6VectorEPKS1_PfS5_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska3Box11CaseNoZerosEPNS_6VectorEPKS1_PfS5_
               (long param_1,float *param_2,float *param_3,undefined8 param_4,undefined8 param_5)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  undefined4 uStack_14;
  
  fStack_20 = *param_2 - *(float *)(param_1 + 0x10);
  fStack_1c = param_2[1] - *(float *)(param_1 + 0x14);
  fStack_18 = param_2[2] - *(float *)(param_1 + 0x18);
  uStack_14 = 0x3f800000;
  if (*param_3 * fStack_1c <= param_3[1] * fStack_20) {
    if (*param_3 * fStack_18 <= fStack_20 * param_3[2]) {
      uVar2 = 1;
      uVar3 = 2;
      uVar1 = 0;
      goto code_r0x02431844;
    }
  }
  else if (param_3[1] * fStack_18 <= fStack_1c * param_3[2]) {
    uVar1 = 1;
    uVar2 = 2;
    uVar3 = 0;
    goto code_r0x02431844;
  }
  uVar1 = 2;
  uVar3 = 1;
  uVar2 = 0;
code_r0x02431844:
  Aska::Box::Face(int, int, int, Aska::Vector*, Aska::Vector const*, Aska::Vector const*, float*, float*) const(param_1,uVar1,uVar2,uVar3,param_2,param_3,&fStack_20,param_4,param_5);
  return;
}

// ==== Aska::Box::Case0(int, int, int, Aska::Vector*, Aska::Vector const*, float*, float*) const
// vaddr 0x2331860 | ghidra 0x2431860 | size 496 | symbol _ZNK4Aska3Box5Case0EiiiPNS_6VectorEPKS1_PfS5_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska3Box5Case0EiiiPNS_6VectorEPKS1_PfS5_
               (long param_1,uint param_2,uint param_3,uint param_4,long param_5,long param_6,
               float *param_7,float *param_8)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  
  uVar2 = -(ulong)(param_2 >> 0x1f) & 0xfffffffc00000000 | (ulong)param_2 << 2;
  param_1 = param_1 + 0x10;
  uVar4 = -(ulong)(param_3 >> 0x1f) & 0xfffffffc00000000 | (ulong)param_3 << 2;
  fVar6 = *(float *)(param_5 + uVar2) - *(float *)(param_1 + uVar2);
  fVar7 = *(float *)(param_5 + uVar4) - *(float *)(param_1 + uVar4);
  fVar8 = fVar6 * *(float *)(param_6 + uVar4);
  fVar9 = fVar7 * *(float *)(param_6 + uVar2);
  lVar1 = (long)(int)param_2;
  lVar3 = (long)(int)param_3;
  if (fVar9 <= fVar8) {
    lVar5 = lVar3 * 4;
    *(float *)(param_5 + lVar1 * 4) = *(float *)(param_1 + uVar2);
    fVar10 = *(float *)(param_6 + lVar1 * 4);
    fVar7 = *(float *)(param_5 + lVar5) + *(float *)(param_1 + lVar5);
    fVar9 = fVar8 - fVar10 * fVar7;
    if (0.0 <= fVar9) {
      fVar8 = 1.0 / (fVar10 * fVar10 + *(float *)(param_6 + lVar5) * *(float *)(param_6 + lVar5));
      *param_8 = *param_8 + fVar9 * fVar9 * fVar8;
      *(float *)(param_5 + lVar5) = -*(float *)(param_1 + lVar5);
      if (param_7 == (float *)0x0) goto code_r0x024319ec;
      fVar6 = -(fVar8 * (fVar6 * *(float *)(param_6 + lVar1 * 4) +
                        fVar7 * *(float *)(param_6 + lVar3 * 4)));
    }
    else {
      *(float *)(param_5 + lVar3 * 4) = *(float *)(param_5 + lVar5) - fVar8 * (1.0 / fVar10);
      if (param_7 == (float *)0x0) goto code_r0x024319ec;
      fVar6 = -(fVar6 * (1.0 / fVar10));
    }
  }
  else {
    lVar5 = lVar1 * 4;
    *(float *)(param_5 + lVar3 * 4) = *(float *)(param_1 + uVar4);
    fVar10 = *(float *)(param_6 + lVar3 * 4);
    fVar6 = *(float *)(param_5 + lVar5) + *(float *)(param_1 + lVar5);
    fVar8 = fVar9 - fVar10 * fVar6;
    if (0.0 <= fVar8) {
      fVar9 = 1.0 / (fVar10 * fVar10 + *(float *)(param_6 + lVar5) * *(float *)(param_6 + lVar5));
      *param_8 = *param_8 + fVar8 * fVar8 * fVar9;
      *(float *)(param_5 + lVar5) = -*(float *)(param_1 + lVar5);
      if (param_7 == (float *)0x0) goto code_r0x024319ec;
      fVar6 = -(fVar9 * (fVar6 * *(float *)(param_6 + lVar1 * 4) +
                        fVar7 * *(float *)(param_6 + lVar3 * 4)));
    }
    else {
      *(float *)(param_5 + lVar1 * 4) = *(float *)(param_5 + lVar5) - fVar9 * (1.0 / fVar10);
      if (param_7 == (float *)0x0) goto code_r0x024319ec;
      fVar6 = -(fVar7 * (1.0 / fVar10));
    }
  }
  *param_7 = fVar6;
code_r0x024319ec:
  uVar2 = -(ulong)(param_4 >> 0x1f) & 0xfffffffc00000000 | (ulong)param_4 << 2;
  fVar6 = *(float *)(param_1 + uVar2);
  fVar7 = *(float *)(param_5 + uVar2);
  lVar1 = (long)(int)param_4;
  if (-fVar6 <= fVar7) {
    if (fVar7 <= fVar6) {
      return;
    }
    *param_8 = (fVar7 - fVar6) * (fVar7 - fVar6) + *param_8;
    fVar6 = *(float *)(param_1 + lVar1 * 4);
  }
  else {
    *param_8 = (fVar7 + fVar6) * (fVar7 + fVar6) + *param_8;
    fVar6 = -*(float *)(param_1 + lVar1 * 4);
  }
  *(float *)(param_5 + lVar1 * 4) = fVar6;
  return;
}

// ==== Aska::Box::Case00(int, int, int, Aska::Vector*, Aska::Vector const*, float*, float*) const
// vaddr 0x2331a50 | ghidra 0x2431a50 | size 264 | symbol _ZNK4Aska3Box6Case00EiiiPNS_6VectorEPKS1_PfS5_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska3Box6Case00EiiiPNS_6VectorEPKS1_PfS5_
               (long param_1,int param_2,uint param_3,uint param_4,long param_5,long param_6,
               float *param_7,float *param_8)

{
  long lVar1;
  ulong uVar2;
  float *pfVar3;
  long lVar4;
  float fVar5;
  float fVar6;
  
  lVar1 = (long)param_2;
  if (param_7 == (float *)0x0) {
    pfVar3 = (float *)(param_5 + lVar1 * 4);
  }
  else {
    lVar4 = lVar1 * 4;
    pfVar3 = (float *)(param_5 + lVar4);
    *param_7 = (*(float *)(param_1 + 0x10 + lVar4) - *pfVar3) / *(float *)(param_6 + lVar4);
  }
  lVar4 = param_1 + 0x10;
  *pfVar3 = *(float *)(param_1 + 0x10 + lVar1 * 4);
  uVar2 = -(ulong)(param_3 >> 0x1f) & 0xfffffffc00000000 | (ulong)param_3 << 2;
  fVar5 = *(float *)(lVar4 + uVar2);
  fVar6 = *(float *)(param_5 + uVar2);
  lVar1 = (long)(int)param_3;
  if (-fVar5 <= fVar6) {
    if (fVar6 <= fVar5) goto code_r0x02431af0;
    *param_8 = (fVar6 - fVar5) * (fVar6 - fVar5) + *param_8;
    fVar5 = *(float *)(lVar4 + lVar1 * 4);
  }
  else {
    *param_8 = (fVar6 + fVar5) * (fVar6 + fVar5) + *param_8;
    fVar5 = -*(float *)(lVar4 + lVar1 * 4);
  }
  *(float *)(param_5 + lVar1 * 4) = fVar5;
code_r0x02431af0:
  param_1 = param_1 + 0x10;
  uVar2 = -(ulong)(param_4 >> 0x1f) & 0xfffffffc00000000 | (ulong)param_4 << 2;
  fVar5 = *(float *)(param_1 + uVar2);
  fVar6 = *(float *)(param_5 + uVar2);
  lVar1 = (long)(int)param_4;
  if (-fVar5 <= fVar6) {
    if (fVar6 <= fVar5) {
      return;
    }
    *param_8 = (fVar6 - fVar5) * (fVar6 - fVar5) + *param_8;
    fVar5 = *(float *)(param_1 + lVar1 * 4);
  }
  else {
    *param_8 = (fVar6 + fVar5) * (fVar6 + fVar5) + *param_8;
    fVar5 = -*(float *)(param_1 + lVar1 * 4);
  }
  *(float *)(param_5 + lVar1 * 4) = fVar5;
  return;
}

// ==== Aska::Box::Case000(Aska::Vector*, float*) const
// vaddr 0x2331b58 | ghidra 0x2431b58 | size 268 | symbol _ZNK4Aska3Box7Case000EPNS_6VectorEPf | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska3Box7Case000EPNS_6VectorEPf(long param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  
  fVar1 = *(float *)(param_1 + 0x10);
  fVar2 = *param_2;
  if (-fVar1 <= fVar2) {
    if (fVar1 < fVar2) {
      *param_3 = (fVar2 - fVar1) * (fVar2 - fVar1) + *param_3;
      fVar1 = *(float *)(param_1 + 0x10);
      goto code_r0x02431bac;
    }
  }
  else {
    *param_3 = (fVar2 + fVar1) * (fVar2 + fVar1) + *param_3;
    fVar1 = -*(float *)(param_1 + 0x10);
code_r0x02431bac:
    *param_2 = fVar1;
  }
  fVar1 = *(float *)(param_1 + 0x14);
  fVar2 = param_2[1];
  if (-fVar1 <= fVar2) {
    if (fVar2 <= fVar1) goto code_r0x02431c08;
    *param_3 = (fVar2 - fVar1) * (fVar2 - fVar1) + *param_3;
    fVar1 = *(float *)(param_1 + 0x14);
  }
  else {
    *param_3 = (fVar2 + fVar1) * (fVar2 + fVar1) + *param_3;
    fVar1 = -*(float *)(param_1 + 0x14);
  }
  param_2[1] = fVar1;
code_r0x02431c08:
  fVar1 = *(float *)(param_1 + 0x18);
  fVar2 = param_2[2];
  if (-fVar1 <= fVar2) {
    if (fVar2 <= fVar1) {
      return;
    }
    *param_3 = (fVar2 - fVar1) * (fVar2 - fVar1) + *param_3;
    fVar1 = *(float *)(param_1 + 0x18);
  }
  else {
    *param_3 = (fVar2 + fVar1) * (fVar2 + fVar1) + *param_3;
    fVar1 = -*(float *)(param_1 + 0x18);
  }
  param_2[2] = fVar1;
  return;
}

// ==== Aska::Box::SquaredDistance(Aska::Segment const*, float*, float*, float*, float*) const
// vaddr 0x2331c64 | ghidra 0x2431c64 | size 304 | symbol _ZNK4Aska3Box15SquaredDistanceEPKNS_7SegmentEPfS4_S4_S4_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska3Box15SquaredDistanceEPKNS_7SegmentEPfS4_S4_S4_
               (undefined8 param_1,float *param_2,float *param_3,undefined4 *param_4,
               undefined4 *param_5,undefined4 *param_6)

{
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  undefined4 uStack_74;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined4 uStack_38;
  float fStack_34;
  
  uStack_58 = *(undefined8 *)(param_2 + 2);
  uStack_60 = *(undefined8 *)param_2;
  uStack_48 = *(undefined8 *)(param_2 + 6);
  uStack_50 = *(undefined8 *)(param_2 + 4);
  Aska::Box::SquaredDistance(Aska::Line const*, float*, float*, float*, float*) const(param_1,&uStack_60,&fStack_34,&uStack_38,&uStack_64,&uStack_68);
  if (0.0 <= fStack_34) {
    if (fStack_34 <= 1.0) {
      if (param_3 != (float *)0x0) {
        *param_3 = fStack_34;
      }
      if (param_4 != (undefined4 *)0x0) {
        *param_4 = uStack_38;
      }
      if (param_5 != (undefined4 *)0x0) {
        *param_5 = uStack_64;
      }
      if (param_6 != (undefined4 *)0x0) {
        *param_6 = uStack_68;
      }
    }
    else {
      fStack_80 = *param_2 + param_2[4];
      fStack_7c = param_2[1] + param_2[5];
      uStack_74 = 0x3f800000;
      fStack_78 = param_2[2] + param_2[6];
      Aska::Box::SquaredDistance(Aska::Vector const*, float*, float*, float*) const(param_1,&fStack_80,param_4,param_5,param_6);
      if (param_3 != (float *)0x0) {
        *param_3 = 1.0;
      }
    }
  }
  else {
    Aska::Box::SquaredDistance(Aska::Vector const*, float*, float*, float*) const(param_1,param_2,param_4,param_5,param_6);
    if (param_3 != (float *)0x0) {
      *param_3 = 0.0;
    }
  }
  return;
}

// ==== Aska::Box::SquaredDistance(Aska::Vector const*, float*, float*, float*) const
// vaddr 0x2331d94 | ghidra 0x2431d94 | size 312 | symbol _ZNK4Aska3Box15SquaredDistanceEPKNS_6VectorEPfS4_S4_ | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK4Aska3Box15SquaredDistanceEPKNS_6VectorEPfS4_S4_
                (float *param_1,float *param_2,float *param_3,float *param_4,float *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  fVar1 = *param_2 - *param_1;
  fVar7 = (float)*(undefined8 *)(param_2 + 1) - (float)*(undefined8 *)(param_1 + 1);
  fVar8 = (float)((ulong)*(undefined8 *)(param_2 + 1) >> 0x20) -
          (float)((ulong)*(undefined8 *)(param_1 + 1) >> 0x20);
  fVar5 = param_1[4];
  fVar4 = fVar1 * param_1[8] + fVar7 * (float)*(undefined8 *)(param_1 + 9) +
          fVar8 * (float)((ulong)*(undefined8 *)(param_1 + 9) >> 0x20);
  fVar3 = fVar1 * param_1[0xc] + param_1[0xd] * fVar7 + param_1[0xe] * fVar8;
  if (-fVar5 <= fVar4) {
    fVar2 = 0.0;
    if (fVar5 < fVar4) {
      fVar2 = (fVar4 - fVar5) * (fVar4 - fVar5);
      goto code_r0x02431e30;
    }
  }
  else {
    fVar2 = (fVar4 + fVar5) * (fVar4 + fVar5);
    fVar5 = -fVar5;
code_r0x02431e30:
    fVar2 = fVar2 + 0.0;
    fVar4 = fVar5;
  }
  fVar6 = param_1[5];
  fVar5 = fVar1 * param_1[0x10] + param_1[0x11] * fVar7 + param_1[0x12] * fVar8;
  if (-fVar6 <= fVar3) {
    if (fVar6 < fVar3) {
      fVar1 = (fVar3 - fVar6) * (fVar3 - fVar6);
      fVar3 = fVar6;
      goto code_r0x02431e70;
    }
  }
  else {
    fVar1 = (fVar3 + fVar6) * (fVar3 + fVar6);
    fVar3 = -fVar6;
code_r0x02431e70:
    fVar2 = fVar2 + fVar1;
  }
  fVar1 = param_1[6];
  if (-fVar1 <= fVar5) {
    if (fVar5 <= fVar1) goto code_r0x02431eb0;
    fVar7 = (fVar5 - fVar1) * (fVar5 - fVar1);
    fVar5 = fVar1;
  }
  else {
    fVar7 = (fVar5 + fVar1) * (fVar5 + fVar1);
    fVar5 = -fVar1;
  }
  fVar2 = fVar2 + fVar7;
code_r0x02431eb0:
  if (param_3 != (float *)0x0) {
    *param_3 = fVar4;
  }
  if (param_4 != (float *)0x0) {
    *param_4 = fVar3;
  }
  if (param_5 != (float *)0x0) {
    *param_5 = fVar5;
  }
  return fVar2;
}

// ==== Aska::AABB::SquaredDistance(Aska::Vector const*, float*, float*) const
// vaddr 0x2331ecc | ghidra 0x2431ecc | size 224 | symbol _ZNK4Aska4AABB15SquaredDistanceEPKNS_6VectorEPfS4_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska4AABB15SquaredDistanceEPKNS_6VectorEPfS4_
               (float *param_1,float *param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  
  fVar8 = param_1[4];
  fVar4 = param_1[5];
  fVar6 = *param_2 - *param_1;
  fVar1 = param_1[6];
  fVar2 = param_2[1] - param_1[1];
  fVar3 = param_2[2] - param_1[2];
  if (-fVar8 <= fVar6) {
    fVar5 = 0.0;
    if (fVar6 <= fVar8) goto code_r0x02431f20;
    fVar5 = fVar6 - fVar8;
  }
  else {
    fVar5 = fVar6 + fVar8;
  }
  fVar5 = fVar5 * fVar5 + 0.0;
code_r0x02431f20:
  fVar10 = (fVar2 + fVar4) * (fVar2 + fVar4);
  fVar12 = (fVar2 - fVar4) * (fVar2 - fVar4);
  fVar7 = (fVar6 - fVar8) * (fVar6 - fVar8);
  if (0.0 <= fVar6) {
    fVar7 = (fVar6 + fVar8) * (fVar6 + fVar8);
  }
  fVar6 = (fVar3 + fVar1) * (fVar3 + fVar1);
  fVar11 = (fVar3 - fVar1) * (fVar3 - fVar1);
  fVar8 = fVar12;
  if (0.0 <= fVar2) {
    fVar8 = fVar10;
  }
  fVar9 = fVar11;
  if (0.0 <= fVar3) {
    fVar9 = fVar6;
  }
  if (param_3 != (float *)0x0) {
    if (-fVar4 <= fVar2) {
      fVar10 = fVar12;
    }
    if (-fVar1 <= fVar3) {
      fVar6 = fVar11;
    }
    *param_3 = fVar6 + fVar10 + fVar5;
  }
  if (param_4 != (float *)0x0) {
    *param_4 = fVar7 + 0.0 + fVar8 + fVar9;
  }
  return;
}

// ==== Aska::AABB_MinMax::SquaredDistance(Aska::Vector const*, float*, float*) const
// vaddr 0x2331fac | ghidra 0x2431fac | size 316 | symbol _ZNK4Aska11AABB_MinMax15SquaredDistanceEPKNS_6VectorEPfS4_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska11AABB_MinMax15SquaredDistanceEPKNS_6VectorEPfS4_
               (float *param_1,float *param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  
  fVar1 = *param_2;
  fVar7 = param_2[1];
  fVar8 = *param_1;
  fVar9 = param_1[1];
  fVar3 = param_2[2];
  fVar5 = param_1[2];
  fVar11 = param_1[4];
  fVar10 = param_1[5];
  fVar6 = param_1[6];
  if (fVar8 <= fVar1) {
    if (fVar11 < fVar1) {
      fVar4 = fVar1 - fVar11;
      fVar2 = fVar1 - fVar8;
    }
    else {
      fVar2 = fVar11 - fVar1;
      if (fVar11 - fVar1 <= fVar1 - fVar8) {
        fVar2 = fVar1 - fVar8;
      }
      fVar4 = 0.0;
    }
  }
  else {
    fVar4 = fVar8 - fVar1;
    fVar2 = fVar11 - fVar1;
  }
  if (fVar9 <= fVar7) {
    if (fVar7 <= fVar10) {
      fVar1 = fVar10 - fVar7;
      if (fVar10 - fVar7 <= fVar7 - fVar9) {
        fVar1 = fVar7 - fVar9;
      }
      fVar8 = 0.0;
    }
    else {
      fVar8 = fVar7 - fVar10;
      fVar1 = fVar7 - fVar9;
    }
  }
  else {
    fVar8 = fVar9 - fVar7;
    fVar1 = fVar10 - fVar7;
  }
  if (fVar5 <= fVar3) {
    if (fVar3 <= fVar6) {
      fVar7 = fVar6 - fVar3;
      if (fVar6 - fVar3 <= fVar3 - fVar5) {
        fVar7 = fVar3 - fVar5;
      }
      fVar9 = 0.0;
    }
    else {
      fVar9 = fVar3 - fVar6;
      fVar7 = fVar3 - fVar5;
    }
  }
  else {
    fVar9 = fVar5 - fVar3;
    fVar7 = fVar6 - fVar3;
  }
  if (param_3 != (float *)0x0) {
    *param_3 = fVar4 * fVar4 + 0.0 + fVar8 * fVar8 + fVar9 * fVar9;
  }
  if (param_4 != (float *)0x0) {
    *param_4 = fVar2 * fVar2 + 0.0 + fVar1 * fVar1 + fVar7 * fVar7;
  }
  return;
}

// ==== Aska::AABB_MinMax::CalcDistance(Aska::Vector const*) const
// vaddr 0x23320e8 | ghidra 0x24320e8 | size 140 | symbol _ZNK4Aska11AABB_MinMax12CalcDistanceEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK4Aska11AABB_MinMax12CalcDistanceEPKNS_6VectorE(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar3 = *param_2;
  fVar2 = param_2[1];
  fVar1 = param_2[2];
  if (*param_1 <= fVar3) {
    fVar4 = 0.0;
    if (param_1[4] < fVar3) {
      fVar4 = fVar3 - param_1[4];
    }
  }
  else {
    fVar4 = *param_1 - fVar3;
  }
  fVar3 = 0.0;
  if (param_1[1] <= fVar2) {
    if (param_1[5] < fVar2) {
      fVar3 = fVar2 - param_1[5];
    }
  }
  else {
    fVar3 = param_1[1] - fVar2;
  }
  fVar3 = fVar4 + 0.0 + fVar3;
  if (fVar1 < param_1[2]) {
    return fVar3 + (param_1[2] - fVar1);
  }
  fVar2 = 0.0;
  if (param_1[6] < fVar1) {
    fVar2 = fVar1 - param_1[6];
  }
  return fVar3 + fVar2;
}

// ==== Aska::AABB_MinMax::SquaredDistance(Aska::Segment const*, float*) const
// vaddr 0x2332174 | ghidra 0x2432174 | size 160 | symbol _ZNK4Aska11AABB_MinMax15SquaredDistanceEPKNS_7SegmentEPf | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska11AABB_MinMax15SquaredDistanceEPKNS_7SegmentEPf
               (float *param_1,undefined8 param_2,undefined8 param_3)

{
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  undefined4 uStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  undefined4 uStack_40;
  undefined8 uStack_3c;
  undefined8 uStack_34;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  fStack_60 = (param_1[4] + *param_1) * 0.5;
  fStack_5c = (param_1[5] + param_1[1]) * 0.5;
  fStack_58 = (param_1[6] + param_1[2]) * 0.5;
  uStack_54 = 0x3f800000;
  fStack_44 = param_1[7];
  fStack_50 = (param_1[4] - *param_1) * 0.5;
  fStack_4c = (param_1[5] - param_1[1]) * 0.5;
  fStack_48 = (param_1[6] - param_1[2]) * 0.5;
  uStack_40 = 0x3f800000;
  uStack_34 = 0;
  uStack_3c = 0;
  uStack_2c = 0x3f800000;
  uStack_28 = 0;
  uStack_20 = 0;
  uStack_18 = 0x3f800000;
  Aska::Box::SquaredDistance(Aska::Segment const*, float*, float*, float*, float*) const(&fStack_60,param_2,param_3,0,0,0);
  return;
}

// ==== Aska::AABB::CalcDistance(Aska::Plane const*) const
// vaddr 0x2332214 | ghidra 0x2432214 | size 152 | symbol _ZNK4Aska4AABB12CalcDistanceEPKNS_5PlaneE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float _ZNK4Aska4AABB12CalcDistanceEPKNS_5PlaneE(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar1 = param_2[4];
  fVar2 = param_2[5];
  fVar4 = param_2[6];
  fVar3 = (fVar1 * *param_1 + fVar2 * param_1[1] + fVar4 * param_1[2]) -
          (fVar1 * *param_2 + fVar2 * param_2[1] + fVar4 * param_2[2]);
  fVar2 = ((ABS(fVar3) - ABS(fVar1 * param_1[4])) - ABS(fVar2 * param_1[5])) -
          ABS(fVar4 * param_1[6]);
  fVar1 = 0.0;
  if ((_UNK_029e3078 < fVar2) && (fVar1 = fVar2, fVar3 < 0.0)) {
    fVar1 = -fVar2;
  }
  return fVar1;
}

// ==== Aska::AABB::CalcDistance(Aska::Vector const*) const
// vaddr 0x23322ac | ghidra 0x24322ac | size 108 | symbol _ZNK4Aska4AABB12CalcDistanceEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
undefined1  [16] _ZNK4Aska4AABB12CalcDistanceEPKNS_6VectorE(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined1 auVar4 [16];
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  int iVar13;
  int iVar14;
  
  fVar3 = ABS(*param_1 - *param_2) - param_1[4];
  fVar1 = ABS((float)*(undefined8 *)(param_1 + 1) - (float)*(undefined8 *)(param_2 + 1)) -
          (float)*(undefined8 *)(param_1 + 5);
  fVar2 = ABS((float)((ulong)*(undefined8 *)(param_1 + 1) >> 0x20) -
              (float)((ulong)*(undefined8 *)(param_2 + 1) >> 0x20)) -
          (float)((ulong)*(undefined8 *)(param_1 + 5) >> 0x20);
  if (fVar3 <= 0.0) {
    fVar3 = 0.0;
  }
  iVar13 = -(uint)(fVar1 < 0.0);
  iVar14 = -(uint)(fVar2 < 0.0);
  bVar5 = SUB41(fVar1,0) & ~(byte)iVar13;
  bVar6 = (byte)((uint)fVar1 >> 8) & ~(byte)((uint)iVar13 >> 8);
  bVar7 = (byte)((uint)fVar1 >> 0x10) & ~(byte)((uint)iVar13 >> 0x10);
  bVar8 = (byte)((uint)fVar1 >> 0x18) & ~(byte)((uint)iVar13 >> 0x18);
  bVar9 = SUB41(fVar2,0) & ~(byte)iVar14;
  bVar10 = (byte)((uint)fVar2 >> 8) & ~(byte)((uint)iVar14 >> 8);
  bVar11 = (byte)((uint)fVar2 >> 0x10) & ~(byte)((uint)iVar14 >> 0x10);
  bVar12 = (byte)((uint)fVar2 >> 0x18) & ~(byte)((uint)iVar14 >> 0x18);
  fVar1 = SQRT(fVar3 * fVar3 +
               (float)CONCAT13(bVar8,CONCAT12(bVar7,CONCAT11(bVar6,bVar5))) *
               (float)CONCAT13(bVar8,CONCAT12(bVar7,CONCAT11(bVar6,bVar5))) +
               (float)CONCAT13(bVar12,CONCAT12(bVar11,CONCAT11(bVar10,bVar9))) *
               (float)CONCAT13(bVar12,CONCAT12(bVar11,CONCAT11(bVar10,bVar9))));
  if (NAN(fVar1)) {
    auVar4 = (*(code *)PTR_sqrtf_02cb04c0)();
    return auVar4;
  }
  return ZEXT416((uint)fVar1);
}

// ==== Aska::AABB::ClipIntersection(Aska::AABB const*)
// vaddr 0x2332318 | ghidra 0x2432318 | size 192 | symbol _ZN4Aska4AABB16ClipIntersectionEPKS0_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska4AABB16ClipIntersectionEPKS0_(undefined1 (*param_1) [12],undefined1 (*param_2) [16])

{
  undefined1 (*pauVar1) [12];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined1 auVar14 [16];
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  undefined1 auVar23 [16];
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
  
  fVar20 = (float)*(undefined8 *)(*param_1 + 8);
  fVar22 = (float)((ulong)*(undefined8 *)(*param_1 + 8) >> 0x20);
  fVar16 = (float)*(undefined8 *)*param_1;
  fVar18 = (float)((ulong)*(undefined8 *)*param_1 >> 0x20);
  pauVar1 = (undefined1 (*) [12])(param_1[1] + 4);
  fVar12 = (float)*(undefined8 *)param_1[2];
  fVar13 = (float)((ulong)*(undefined8 *)param_1[2] >> 0x20);
  fVar10 = (float)*(undefined8 *)*pauVar1;
  fVar11 = (float)((ulong)*(undefined8 *)*pauVar1 >> 0x20);
  auVar9 = *param_2;
  auVar4 = param_2[1];
  fVar15 = ABS(fVar16 - auVar9._0_4_);
  fVar17 = ABS(fVar18 - auVar9._4_4_);
  fVar19 = ABS(fVar20 - auVar9._8_4_);
  fVar21 = ABS(fVar22 - auVar9._12_4_);
  if (fVar12 + auVar4._8_4_ < fVar19 ||
      (fVar10 + auVar4._0_4_ < fVar15 || fVar11 + auVar4._4_4_ < fVar17)) {
    return 0;
  }
  auVar28._0_8_ = CONCAT44(-(uint)(auVar9._4_4_ < fVar18),-(uint)(auVar9._0_4_ < fVar16));
  auVar28._8_4_ = -(uint)(auVar9._8_4_ < fVar20);
  auVar28._12_4_ = -(uint)(auVar9._12_4_ < fVar22);
  auVar30._8_8_ = auVar28._8_8_;
  auVar30._0_8_ = auVar28._0_8_;
  auVar32._8_8_ = auVar28._8_8_;
  auVar32._0_8_ = auVar28._0_8_;
  auVar25._12_4_ = fVar13;
  auVar25._0_12_ = *pauVar1;
  auVar31 = auVar4 ^ (auVar4 ^ auVar25) & auVar30;
  auVar26._12_4_ = fVar13;
  auVar26._0_12_ = *pauVar1;
  auVar25 = NEON_fmax(auVar26,auVar4,4);
  auVar2._12_4_ = fVar13;
  auVar2._0_12_ = *pauVar1;
  auVar26 = NEON_fmin(auVar2,auVar4,4);
  auVar27._0_4_ = -(uint)(auVar4._0_4_ < fVar10);
  auVar27._4_4_ = -(uint)(auVar4._4_4_ < fVar11);
  auVar27._8_4_ = -(uint)(auVar4._8_4_ < fVar12);
  auVar27._12_4_ = -(uint)(auVar4._12_4_ < fVar13);
  auVar3._12_4_ = fVar13;
  auVar3._0_12_ = *pauVar1;
  auVar33._12_4_ = fVar13;
  auVar33._0_12_ = *pauVar1;
  auVar33 = auVar33 ^ (auVar3 ^ auVar4) & auVar32;
  fVar10 = fVar15 - auVar31._0_4_;
  fVar11 = fVar17 - auVar31._4_4_;
  fVar12 = fVar19 - auVar31._8_4_;
  fVar13 = fVar21 - auVar31._12_4_;
  auVar6._12_4_ = fVar22;
  auVar6._0_12_ = *param_1;
  auVar7._12_4_ = fVar22;
  auVar7._0_12_ = *param_1;
  auVar8._12_4_ = fVar22;
  auVar8._0_12_ = *param_1;
  auVar29._12_4_ = fVar22;
  auVar29._0_12_ = *param_1;
  auVar29 = auVar29 ^ (auVar8 ^ auVar9) & auVar28;
  fVar16 = (auVar33._0_4_ - fVar10) * 0.5;
  fVar18 = (auVar33._4_4_ - fVar11) * 0.5;
  fVar20 = (auVar33._8_4_ - fVar12) * 0.5;
  fVar22 = (auVar33._12_4_ - fVar13) * 0.5;
  auVar23._0_8_ =
       CONCAT44(-(uint)(fVar17 + auVar26._4_4_ < auVar25._4_4_),
                -(uint)(fVar15 + auVar26._0_4_ < auVar25._0_4_));
  auVar23._8_4_ = -(uint)(fVar19 + auVar26._8_4_ < auVar25._8_4_);
  auVar23._12_4_ = -(uint)(fVar21 + auVar26._12_4_ < auVar25._12_4_);
  auVar14._8_8_ = auVar23._8_8_;
  auVar14._0_8_ = auVar23._0_8_;
  fVar10 = auVar29._0_4_ + fVar10 + fVar16;
  fVar11 = auVar29._4_4_ + fVar11 + fVar18;
  fVar12 = auVar29._8_4_ + fVar12 + fVar20;
  fVar13 = auVar29._12_4_ + fVar13 + fVar22;
  auVar5._4_4_ = fVar18;
  auVar5._0_4_ = fVar16;
  auVar5._8_4_ = fVar20;
  auVar5._12_4_ = fVar22;
  auVar24._4_4_ = fVar18;
  auVar24._0_4_ = fVar16;
  auVar24._8_4_ = fVar20;
  auVar24._12_4_ = fVar22;
  auVar24 = auVar24 ^ (auVar5 ^ auVar26) & auVar23;
  auVar4._4_4_ = fVar11;
  auVar4._0_4_ = fVar10;
  auVar4._8_4_ = fVar12;
  auVar4._12_4_ = fVar13;
  auVar31._4_4_ = fVar11;
  auVar31._0_4_ = fVar10;
  auVar31._8_4_ = fVar12;
  auVar31._12_4_ = fVar13;
  auVar31 = auVar31 ^ (auVar4 ^ auVar7 ^ (auVar6 ^ auVar9) & auVar27) & auVar14;
  *(long *)(*param_1 + 8) = auVar31._8_8_;
  *(long *)*param_1 = auVar31._0_8_;
  *(long *)param_1[2] = auVar24._8_8_;
  *(long *)(param_1[1] + 4) = auVar24._0_8_;
  *(undefined4 *)param_1[1] = 0x3f800000;
  *(undefined4 *)(param_1[2] + 4) = 0x3f800000;
  return 1;
}

// ==== Aska::AABB::IsContained(Aska::Vector const*, float) const
// vaddr 0x23323d8 | ghidra 0x24323d8 | size 148 | symbol _ZNK4Aska4AABB11IsContainedEPKNS_6VectorEf | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska4AABB11IsContainedEPKNS_6VectorEf(float param_1,float *param_2,float *param_3)

{
  if (((*param_2 - param_2[4]) - param_1 <= *param_3) &&
     (*param_3 <= *param_2 + param_2[4] + param_1)) {
    if (((param_2[1] - param_2[5]) - param_1 <= param_3[1]) &&
       (param_3[1] <= param_2[1] + param_2[5] + param_1)) {
      if (((param_2[2] - param_2[6]) - param_1 <= param_3[2]) &&
         (param_3[2] <= param_2[2] + param_2[6] + param_1)) {
        return 1;
      }
    }
  }
  return 0;
}

// ==== Aska::AABB::CalcOverlappedStatus(Aska::Sphere const*, float) const
// vaddr 0x233246c | ghidra 0x243246c | size 460 | symbol _ZNK4Aska4AABB20CalcOverlappedStatusEPKNS_6SphereEf | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK4Aska4AABB20CalcOverlappedStatusEPKNS_6SphereEf(float param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  fVar1 = param_3[3];
  fVar4 = 0.0;
  fVar9 = *param_3 - (*param_2 + param_2[4]);
  param_1 = param_1 + 0.0;
  fVar2 = -fVar1;
  if (fVar9 <= fVar1) {
    if (fVar9 < fVar2) {
      fVar4 = fVar1 + fVar9;
    }
  }
  else {
    fVar4 = fVar9 - fVar1;
  }
  if (fVar4 <= param_1) {
    fVar9 = (*param_2 - param_2[4]) - *param_3;
    if (fVar9 <= fVar1) {
      fVar7 = 0.0;
      if (fVar9 < fVar2) {
        fVar7 = fVar1 + fVar9;
      }
    }
    else {
      fVar7 = fVar9 - fVar1;
    }
    if (fVar7 <= param_1) {
      fVar9 = param_3[1] - (param_2[1] + param_2[5]);
      if (fVar9 <= fVar1) {
        fVar8 = 0.0;
        if (fVar9 < fVar2) {
          fVar8 = fVar1 + fVar9;
        }
      }
      else {
        fVar8 = fVar9 - fVar1;
      }
      if (fVar8 <= param_1) {
        fVar9 = (param_2[1] - param_2[5]) - param_3[1];
        if (fVar9 <= fVar1) {
          fVar5 = 0.0;
          if (fVar9 < fVar2) {
            fVar5 = fVar1 + fVar9;
          }
        }
        else {
          fVar5 = fVar9 - fVar1;
        }
        if (fVar5 <= param_1) {
          fVar9 = param_3[2] - (param_2[2] + param_2[6]);
          if (fVar9 <= fVar1) {
            fVar6 = 0.0;
            if (fVar9 < fVar2) {
              fVar6 = fVar1 + fVar9;
            }
          }
          else {
            fVar6 = fVar9 - fVar1;
          }
          if (fVar6 <= param_1) {
            fVar9 = (param_2[2] - param_2[6]) - param_3[2];
            if (fVar9 <= fVar1) {
              fVar3 = 0.0;
              if (fVar9 < fVar2) {
                fVar3 = fVar1 + fVar9;
              }
            }
            else {
              fVar3 = fVar9 - fVar1;
            }
            if (fVar3 <= param_1) {
              return -(uint)(((((fVar4 != 0.0 && fVar7 != 0.0) && fVar8 != 0.0) && fVar5 != 0.0) &&
                             fVar6 != 0.0) && fVar3 != 0.0);
            }
          }
        }
      }
    }
  }
  return 1;
}

// ==== Aska::AABB::CalcOverlappedStatus(Aska::Box const*, float) const
// vaddr 0x2332638 | ghidra 0x2432638 | size 536 | symbol _ZNK4Aska4AABB20CalcOverlappedStatusEPKNS_3BoxEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int _ZNK4Aska4AABB20CalcOverlappedStatusEPKNS_3BoxEf(float param_1,long param_2,long param_3)

{
  bool bVar1;
  float *pfVar2;
  uint uVar3;
  uint uVar4;
  long lVar5;
  long lVar6;
  uint uVar7;
  ulong uVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fStack_24;
  undefined8 uStack_20;
  float fStack_18;
  
  fVar9 = *(float *)(param_3 + 0x20);
  fVar10 = *(float *)(param_3 + 0x24);
  fVar11 = *(float *)(param_3 + 0x28);
  fVar12 = *(float *)(param_3 + 0x30);
  fVar13 = *(float *)(param_3 + 0x34);
  fVar14 = *(float *)(param_3 + 0x38);
  fVar15 = *(float *)(param_3 + 0x10);
  fVar16 = *(float *)(param_3 + 0x14);
  fVar17 = *(float *)(param_3 + 0x40);
  fVar18 = *(float *)(param_3 + 0x44);
  fVar19 = *(float *)(param_3 + 0x48);
  fVar20 = *(float *)(param_3 + 0x18);
  lVar5 = 0;
  uVar7 = 1;
  lVar6 = 0;
  while( true ) {
    pfVar2 = (float *)(param_2 + lVar6 * 4);
    fVar21 = *pfVar2;
    fVar22 = pfVar2[4];
    fStack_18 = (float)_UNK_027dbb38;
    fVar23 = fStack_18;
    uStack_20 = _UNK_027dbb30;
    *(undefined4 *)((long)&uStack_20 + (lVar5 >> 0x1e)) = 0x3f800000;
    fVar24 = *(float *)(param_3 + (lVar5 >> 0x1e)) - (fVar21 + fVar22);
    fVar26 = ((ABS(fVar24) -
              ABS(fVar15 * (fVar9 * (float)uStack_20 + fVar10 * uStack_20._4_4_ + fVar11 * fStack_18
                           ))) -
             ABS(fVar16 * ((float)uStack_20 * fVar12 + uStack_20._4_4_ * fVar13 + fStack_18 * fVar14
                          ))) -
             ABS(fVar20 * ((float)uStack_20 * fVar17 + uStack_20._4_4_ * fVar18 + fStack_18 * fVar19
                          ));
    fVar25 = 0.0;
    if ((_UNK_029e3078 < fVar26) && (fVar25 = fVar26, fVar24 < 0.0)) {
      fVar25 = -fVar26;
    }
    if (param_1 + 0.0 < fVar25) {
      return 1;
    }
    uVar4 = (uint)(char)((byte)lVar6 ^ 0xff);
    uVar3 = -uVar4;
    if (-1 < (int)uVar4) {
      uVar3 = uVar4;
    }
    uVar8 = -(ulong)(uVar3 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar3 << 2;
    fVar24 = 1.0;
    if (-1 >= (int)uVar4) {
      fVar24 = -1.0;
    }
    uStack_20 = _UNK_027dbb30;
    fStack_18 = fVar23;
    *(float *)((long)&fStack_24 + uVar8) = fVar24;
    fVar21 = *(float *)(param_3 + (uVar8 - 4)) * fVar24 - fVar24 * (fVar21 - fVar22);
    fVar22 = ((ABS(fVar21) -
              ABS(fVar15 * (fVar9 * (float)uStack_20 + fVar10 * uStack_20._4_4_ + fVar11 * fStack_18
                           ))) -
             ABS(fVar16 * ((float)uStack_20 * fVar12 + uStack_20._4_4_ * fVar13 + fStack_18 * fVar14
                          ))) -
             ABS(fVar20 * ((float)uStack_20 * fVar17 + uStack_20._4_4_ * fVar18 + fStack_18 * fVar19
                          ));
    fVar23 = 0.0;
    if ((_UNK_029e3078 < fVar22) && (fVar23 = fVar22, fVar21 < 0.0)) {
      fVar23 = -fVar22;
    }
    if (param_1 + 0.0 < fVar23) break;
    uVar7 = uVar7 & fVar25 != 0.0 & (uint)(fVar23 != 0.0);
    lVar5 = lVar5 + 0x100000000;
    bVar1 = 1 < lVar6;
    lVar6 = lVar6 + 1;
    if (bVar1) {
      return -uVar7;
    }
  }
  return 1;
}

// ==== Aska::AABB::SeparateByPositive(Aska::OrthogonalPlane const&)
// vaddr 0x2332850 | ghidra 0x2432850 | size 36 | symbol _ZN4Aska4AABB18SeparateByPositiveERKNS_15OrthogonalPlaneE | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska4AABB18SeparateByPositiveERKNS_15OrthogonalPlaneE
               (undefined8 param_1,undefined8 param_2)

{
  uint uVar1;
  undefined1 auStack_30 [32];
  
  uVar1 = Aska::AABB::Separate(Aska::OrthogonalPlane const&, Aska::AABB*, Aska::AABB*) const(param_1,param_2,param_1,auStack_30);
  return uVar1 & 1;
}

// ==== Aska::AABB::Separate(Aska::OrthogonalPlane const&, Aska::AABB*, Aska::AABB*) const
// vaddr 0x2332874 | ghidra 0x2432874 | size 444 | symbol _ZNK4Aska4AABB8SeparateERKNS_15OrthogonalPlaneEPS0_S4_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZNK4Aska4AABB8SeparateERKNS_15OrthogonalPlaneEPS0_S4_
               (undefined8 *param_1,float *param_2,long param_3,long param_4)

{
  long lVar1;
  long lVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char cVar6;
  uint uVar7;
  uint uVar8;
  bool bVar9;
  long lVar10;
  long lVar11;
  ulong uVar12;
  ulong uVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float afStack_224 [4];
  float afStack_214 [125];
  undefined8 uStack_20;
  undefined8 uStack_18;
  undefined8 uStack_10;
  undefined8 uStack_8;
  
  uStack_8 = param_1[1];
  uStack_10 = *param_1;
  uStack_18 = param_1[3];
  uStack_20 = param_1[2];
  cVar6 = *(char *)(param_2 + 1);
  fVar15 = *param_2;
  iVar3 = -(int)cVar6;
  if (-1 < cVar6) {
    iVar3 = (int)cVar6;
  }
  lVar10 = (long)iVar3 + -1;
  lVar11 = lVar10 * 4;
  uVar7 = iVar3 % 3;
  fVar18 = *(float *)((long)&uStack_10 + lVar11) + *(float *)((long)&uStack_20 + lVar11);
  fVar17 = *(float *)((long)&uStack_10 + lVar11) - *(float *)((long)&uStack_20 + lVar11);
  uVar8 = (iVar3 + 1) % 3;
  fVar16 = (fVar15 + fVar18) * 0.5;
  fVar14 = (fVar15 + fVar17) * 0.5;
  bVar9 = _UNK_029e3078 <= fVar15 - fVar17 && _UNK_029e3078 <= fVar18 - fVar15;
  if (cVar6 < 0) {
    lVar1 = param_4 + 0x10;
    uVar12 = -(ulong)(uVar7 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar7 << 2;
    *(float *)(lVar1 + lVar11) = fVar18 - fVar16;
    uVar4 = *(undefined4 *)((long)&uStack_20 + uVar12);
    uVar13 = -(ulong)(uVar8 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar8 << 2;
    *(undefined4 *)(lVar1 + uVar12) = uVar4;
    uVar5 = *(undefined4 *)((long)&uStack_20 + uVar13);
    lVar2 = param_3 + 0x10;
    *(undefined4 *)(lVar1 + uVar13) = uVar5;
    *(float *)(lVar2 + lVar11) = fVar14 - fVar17;
    *(undefined4 *)(lVar2 + uVar12) = uVar4;
    *(undefined4 *)(lVar2 + uVar13) = uVar5;
    *(float *)(param_4 + lVar11) = fVar16;
    uVar4 = *(undefined4 *)((long)&uStack_10 + uVar12);
    *(undefined4 *)(param_4 + uVar12) = uVar4;
    uVar5 = *(undefined4 *)((long)&uStack_10 + uVar13);
    *(undefined4 *)(param_4 + uVar13) = uVar5;
    *(float *)(param_3 + lVar11) = fVar14;
    *(undefined4 *)(param_3 + uVar12) = uVar4;
    *(undefined4 *)(param_3 + uVar13) = uVar5;
    if (*(float *)(lVar2 + lVar11) < 0.0) {
      *(undefined4 *)(lVar2 + lVar10 * 4) = 0;
    }
    if (*(float *)(lVar1 + lVar10 * 4) < 0.0) {
      *(undefined4 *)(lVar1 + lVar10 * 4) = 0;
    }
  }
  else {
    lVar1 = param_3 + 0x10;
    uVar12 = -(ulong)(uVar7 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar7 << 2;
    *(float *)(lVar1 + lVar11) = fVar18 - fVar16;
    uVar4 = *(undefined4 *)((long)&uStack_20 + uVar12);
    uVar13 = -(ulong)(uVar8 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar8 << 2;
    *(undefined4 *)(lVar1 + uVar12) = uVar4;
    uVar5 = *(undefined4 *)((long)&uStack_20 + uVar13);
    lVar2 = param_4 + 0x10;
    *(undefined4 *)(lVar1 + uVar13) = uVar5;
    *(float *)(lVar2 + lVar11) = fVar14 - fVar17;
    *(undefined4 *)(lVar2 + uVar12) = uVar4;
    *(undefined4 *)(lVar2 + uVar13) = uVar5;
    *(float *)(param_3 + lVar11) = fVar16;
    uVar4 = *(undefined4 *)((long)&uStack_10 + uVar12);
    *(undefined4 *)(param_3 + uVar12) = uVar4;
    uVar5 = *(undefined4 *)((long)&uStack_10 + uVar13);
    *(undefined4 *)(param_3 + uVar13) = uVar5;
    *(float *)(param_4 + lVar11) = fVar14;
    *(undefined4 *)(param_4 + uVar12) = uVar4;
    *(undefined4 *)(param_4 + uVar13) = uVar5;
    if (*(float *)(lVar1 + lVar11) < 0.0) {
      *(undefined4 *)(lVar1 + lVar10 * 4) = 0;
    }
    if (*(float *)(lVar2 + lVar10 * 4) < 0.0) {
      *(undefined4 *)(lVar2 + lVar10 * 4) = 0;
      return bVar9;
    }
  }
  return bVar9;
}

// ==== Aska::AABB::SeparateByPositive(int, float)
// vaddr 0x2332a30 | ghidra 0x2432a30 | size 52 | symbol _ZN4Aska4AABB18SeparateByPositiveEif | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska4AABB18SeparateByPositiveEif(undefined4 param_1,undefined8 param_2,char param_3)

{
  uint uVar1;
  undefined1 auStack_30 [32];
  undefined4 uStack_8;
  char cStack_4;
  
  cStack_4 = param_3 + '\x01';
  uStack_8 = param_1;
  uVar1 = Aska::AABB::Separate(Aska::OrthogonalPlane const&, Aska::AABB*, Aska::AABB*) const(param_2,&uStack_8,param_2,auStack_30);
  return uVar1 & 1;
}

// ==== Aska::AABB::SeparateByNegative(Aska::OrthogonalPlane const&)
// vaddr 0x2332a64 | ghidra 0x2432a64 | size 36 | symbol _ZN4Aska4AABB18SeparateByNegativeERKNS_15OrthogonalPlaneE | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska4AABB18SeparateByNegativeERKNS_15OrthogonalPlaneE
               (undefined8 param_1,undefined8 param_2)

{
  uint uVar1;
  undefined1 auStack_30 [32];
  
  uVar1 = Aska::AABB::Separate(Aska::OrthogonalPlane const&, Aska::AABB*, Aska::AABB*) const(param_1,param_2,auStack_30,param_1);
  return uVar1 & 1;
}

// ==== Aska::AABB::SeparateByNegative(int, float)
// vaddr 0x2332a88 | ghidra 0x2432a88 | size 52 | symbol _ZN4Aska4AABB18SeparateByNegativeEif | lib libSOA-3.7.0.so | 2026-10-04
uint _ZN4Aska4AABB18SeparateByNegativeEif(undefined4 param_1,undefined8 param_2,char param_3)

{
  uint uVar1;
  undefined1 auStack_30 [32];
  undefined4 uStack_8;
  char cStack_4;
  
  cStack_4 = param_3 + '\x01';
  uStack_8 = param_1;
  uVar1 = Aska::AABB::Separate(Aska::OrthogonalPlane const&, Aska::AABB*, Aska::AABB*) const(param_2,&uStack_8,auStack_30,param_2);
  return uVar1 & 1;
}

// ==== Aska::Box::CalcDistance(Aska::Plane const*) const
// vaddr 0x2332abc | ghidra 0x2432abc | size 236 | symbol _ZNK4Aska3Box12CalcDistanceEPKNS_5PlaneE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float _ZNK4Aska3Box12CalcDistanceEPKNS_5PlaneE(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar1 = param_2[4];
  fVar2 = param_2[5];
  fVar4 = param_2[6];
  fVar3 = (fVar1 * *param_1 + fVar2 * param_1[1] + fVar4 * param_1[2]) -
          (fVar1 * *param_2 + fVar2 * param_2[1] + fVar4 * param_2[2]);
  fVar2 = ((ABS(fVar3) -
           ABS(param_1[4] * (fVar1 * param_1[8] + fVar2 * param_1[9] + fVar4 * param_1[10]))) -
          ABS(param_1[5] * (fVar1 * param_1[0xc] + fVar2 * param_1[0xd] + fVar4 * param_1[0xe]))) -
          ABS(param_1[6] * (fVar1 * param_1[0x10] + fVar2 * param_1[0x11] + fVar4 * param_1[0x12]));
  fVar1 = 0.0;
  if ((_UNK_029e3078 < fVar2) && (fVar1 = fVar2, fVar3 < 0.0)) {
    fVar1 = -fVar2;
  }
  return fVar1;
}

// ==== Aska::Box::CalcDistance(Aska::Plane const*, Aska::Matrix const*) const
// vaddr 0x2332ba8 | ghidra 0x2432ba8 | size 348 | symbol _ZNK4Aska3Box12CalcDistanceEPKNS_5PlaneEPKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float _ZNK4Aska3Box12CalcDistanceEPKNS_5PlaneEPKNS_6MatrixE
                (float *param_1,float *param_2,undefined8 param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  fStack_38 = param_1[0x12];
  fStack_34 = param_1[2];
  fStack_60 = param_1[8];
  fStack_50 = param_1[9];
  fStack_5c = param_1[0xc];
  fStack_4c = param_1[0xd];
  fStack_58 = param_1[0x10];
  fStack_48 = param_1[0x11];
  fStack_54 = *param_1;
  fStack_44 = param_1[1];
  fStack_40 = param_1[10];
  fStack_3c = param_1[0xe];
  uStack_28 = _UNK_027dbb38;
  uStack_30 = _UNK_027dbb30;
  Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&fStack_60,param_3);
  fVar2 = param_2[4];
  fVar3 = param_2[5];
  fVar4 = param_2[6];
  fVar1 = (fStack_54 * fVar2 + fStack_44 * fVar3 + fStack_34 * fVar4) -
          (fVar2 * *param_2 + fVar3 * param_2[1] + fVar4 * param_2[2]);
  fVar3 = ((ABS(fVar1) -
           ABS((fStack_60 * fVar2 + fStack_50 * fVar3 + fStack_40 * fVar4) * param_1[4])) -
          ABS((fStack_5c * fVar2 + fStack_4c * fVar3 + fStack_3c * fVar4) * param_1[5])) -
          ABS((fStack_58 * fVar2 + fStack_48 * fVar3 + fStack_38 * fVar4) * param_1[6]);
  fVar2 = 0.0;
  if ((_UNK_029e3078 < fVar3) && (fVar2 = fVar3, fVar1 < 0.0)) {
    fVar2 = -fVar3;
  }
  return fVar2;
}

// ==== Aska::Box::CalcDistanceByAABB(Aska::Plane const*, Aska::Matrix const*) const
// vaddr 0x2332d04 | ghidra 0x2432d04 | size 520 | symbol _ZNK4Aska3Box18CalcDistanceByAABBEPKNS_5PlaneEPKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float _ZNK4Aska3Box18CalcDistanceByAABBEPKNS_5PlaneEPKNS_6MatrixE
                (float *param_1,undefined8 *param_2,long param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  if (&uStack_30 != param_2) {
    uStack_28 = param_2[1];
    uStack_30 = *param_2;
    uStack_18 = param_2[3];
    uStack_20 = param_2[2];
  }
  fStack_70 = param_1[8];
  fStack_60 = param_1[9];
  fStack_6c = param_1[0xc];
  fStack_5c = param_1[0xd];
  fStack_68 = param_1[0x10];
  fStack_58 = param_1[0x11];
  fStack_64 = *param_1;
  fStack_54 = param_1[1];
  fStack_50 = param_1[10];
  fStack_4c = param_1[0xe];
  fStack_48 = param_1[0x12];
  fStack_44 = param_1[2];
  uStack_38 = _UNK_027dbb38;
  uStack_40 = _UNK_027dbb30;
  if (param_3 != 0) {
    Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&fStack_70,param_3);
  }
  Aska::Matrix::Invert()(&fStack_70);
  fVar1 = *param_1;
  fVar2 = param_1[1];
  fVar3 = param_1[2];
  fStack_70 = fStack_70 + fVar1 * (float)uStack_40;
  fStack_6c = fStack_6c + fVar1 * uStack_40._4_4_;
  fStack_68 = fStack_68 + fVar1 * (float)uStack_38;
  fStack_64 = fStack_64 + fVar1 * uStack_38._4_4_;
  fStack_60 = fVar2 * (float)uStack_40 + fStack_60;
  fStack_5c = fVar2 * uStack_40._4_4_ + fStack_5c;
  fStack_58 = fVar2 * (float)uStack_38 + fStack_58;
  fStack_54 = fVar2 * uStack_38._4_4_ + fStack_54;
  fStack_50 = fVar3 * (float)uStack_40 + fStack_50;
  fStack_4c = fVar3 * uStack_40._4_4_ + fStack_4c;
  fStack_48 = fVar3 * (float)uStack_38 + fStack_48;
  fStack_44 = fVar3 * uStack_38._4_4_ + fStack_44;
  Aska::Plane::ApplyMatrix(Aska::Matrix const*)(&uStack_30,&fStack_70);
  fVar2 = ((float)uStack_20 * *param_1 + uStack_20._4_4_ * param_1[1] +
          (float)uStack_18 * param_1[2]) -
          ((float)uStack_20 * (float)uStack_30 + uStack_20._4_4_ * uStack_30._4_4_ +
          (float)uStack_18 * (float)uStack_28);
  fVar3 = ((ABS(fVar2) - ABS((float)uStack_20 * param_1[4])) - ABS(uStack_20._4_4_ * param_1[5])) -
          ABS((float)uStack_18 * param_1[6]);
  fVar1 = 0.0;
  if ((_UNK_029e3078 < fVar3) && (fVar1 = fVar3, fVar2 < 0.0)) {
    fVar1 = -fVar3;
  }
  return fVar1;
}

// ==== Aska::Plane::ApplyMatrix(Aska::Matrix const*)
// vaddr 0x2332f0c | ghidra 0x2432f0c | size 292 | symbol _ZN4Aska5Plane11ApplyMatrixEPKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska5Plane11ApplyMatrixEPKNS_6MatrixE(undefined8 *param_1,undefined8 param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  undefined4 uStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  
  Aska::Plane::ComputeVertices(Aska::Vector*, float) const(_UNK_027e6ae0,param_1,&fStack_50);
  Aska::Vector::ApplyMatrix(Aska::Matrix const*)(&fStack_50,param_2);
  Aska::Vector::ApplyMatrix(Aska::Matrix const*)(&fStack_40,param_2);
  Aska::Vector::ApplyMatrix(Aska::Matrix const*)(&fStack_30,param_2);
  fVar2 = (fStack_3c - fStack_4c) * (fStack_28 - fStack_38) -
          (fStack_38 - fStack_48) * (fStack_2c - fStack_3c);
  fVar3 = (fStack_38 - fStack_48) * (fStack_30 - fStack_40) -
          (fStack_40 - fStack_50) * (fStack_28 - fStack_38);
  fVar1 = (fStack_40 - fStack_50) * (fStack_2c - fStack_3c) -
          (fStack_3c - fStack_4c) * (fStack_30 - fStack_40);
  *(float *)(param_1 + 2) = fVar2;
  *(float *)((long)param_1 + 0x14) = fVar3;
  *(float *)(param_1 + 3) = fVar1;
  fVar2 = fVar2 * fVar2 + fVar3 * fVar3 + fVar1 * fVar1;
  fVar1 = SQRT(fVar2);
  *(undefined4 *)((long)param_1 + 0x1c) = 0x3f800000;
  if (NAN(fVar1)) {
    fVar1 = (float)sqrtf(fVar2);
  }
  if (_UNK_027e519c <= fVar1) {
    fVar1 = 1.0 / fVar1;
    *(float *)(param_1 + 2) = fVar1 * *(float *)(param_1 + 2);
    *(float *)((long)param_1 + 0x14) = fVar1 * *(float *)((long)param_1 + 0x14);
    *(float *)(param_1 + 3) = fVar1 * *(float *)(param_1 + 3);
  }
  param_1[1] = CONCAT44(uStack_44,fStack_48);
  *param_1 = CONCAT44(fStack_4c,fStack_50);
  return;
}

// ==== Aska::Box::IsContained(Aska::Vector const*, Aska::Matrix const*, float) const
// vaddr 0x2333030 | ghidra 0x2433030 | size 508 | symbol _ZNK4Aska3Box11IsContainedEPKNS_6VectorEPKNS_6MatrixEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZNK4Aska3Box11IsContainedEPKNS_6VectorEPKNS_6MatrixEf
          (float param_1,float *param_2,undefined8 *param_3,long param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  uStack_28 = param_3[1];
  uStack_30 = *param_3;
  fStack_70 = param_2[8];
  fStack_60 = param_2[9];
  fStack_6c = param_2[0xc];
  fStack_5c = param_2[0xd];
  fStack_68 = param_2[0x10];
  fStack_58 = param_2[0x11];
  fStack_64 = *param_2;
  fStack_54 = param_2[1];
  fStack_50 = param_2[10];
  fStack_4c = param_2[0xe];
  fStack_48 = param_2[0x12];
  fStack_44 = param_2[2];
  uStack_38 = _UNK_027dbb38;
  uStack_40 = _UNK_027dbb30;
  if (param_4 != 0) {
    Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&fStack_70,param_4);
  }
  Aska::Matrix::Invert()(&fStack_70);
  fVar1 = *param_2;
  fVar2 = param_2[1];
  fVar3 = param_2[2];
  fStack_70 = fStack_70 + fVar1 * (float)uStack_40;
  fStack_6c = fStack_6c + fVar1 * uStack_40._4_4_;
  fStack_68 = fStack_68 + fVar1 * (float)uStack_38;
  fStack_64 = fStack_64 + fVar1 * uStack_38._4_4_;
  fStack_60 = fVar2 * (float)uStack_40 + fStack_60;
  fStack_5c = fVar2 * uStack_40._4_4_ + fStack_5c;
  fStack_58 = fVar2 * (float)uStack_38 + fStack_58;
  fStack_54 = fVar2 * uStack_38._4_4_ + fStack_54;
  fStack_50 = fVar3 * (float)uStack_40 + fStack_50;
  fStack_4c = fVar3 * uStack_40._4_4_ + fStack_4c;
  fStack_48 = fVar3 * (float)uStack_38 + fStack_48;
  fStack_44 = fVar3 * uStack_38._4_4_ + fStack_44;
  Aska::Vector::ApplyMatrix(Aska::Matrix const*)(&uStack_30,&fStack_70);
  if (((*param_2 - param_2[4]) - param_1 <= (float)uStack_30) &&
     ((float)uStack_30 <= *param_2 + param_2[4] + param_1)) {
    if (((param_2[1] - param_2[5]) - param_1 <= uStack_30._4_4_) &&
       (uStack_30._4_4_ <= param_2[1] + param_2[5] + param_1)) {
      if (((param_2[2] - param_2[6]) - param_1 <= (float)uStack_28) &&
         ((float)uStack_28 <= param_2[2] + param_2[6] + param_1)) {
        return 1;
      }
    }
  }
  return 0;
}

// ==== Aska::Box::CalcOverlappedStatus(Aska::Sphere const*, Aska::Matrix const*, float) const
// vaddr 0x233322c | ghidra 0x243322c | size 588 | symbol _ZNK4Aska3Box20CalcOverlappedStatusEPKNS_6SphereEPKNS_6MatrixEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK4Aska3Box20CalcOverlappedStatusEPKNS_6SphereEPKNS_6MatrixEf
               (undefined8 param_1,float *param_2,undefined8 *param_3,long param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined4 uStack_38;
  float fStack_34;
  
  uStack_40 = *param_3;
  uStack_38 = *(undefined4 *)(param_3 + 1);
  fStack_34 = *(float *)((long)param_3 + 0xc);
  fStack_80 = param_2[8];
  fStack_70 = param_2[9];
  fStack_7c = param_2[0xc];
  fStack_6c = param_2[0xd];
  fStack_78 = param_2[0x10];
  fStack_68 = param_2[0x11];
  fStack_74 = *param_2;
  fStack_64 = param_2[1];
  fStack_60 = param_2[10];
  fStack_5c = param_2[0xe];
  fStack_58 = param_2[0x12];
  fStack_54 = param_2[2];
  uStack_48 = _UNK_027dbb38;
  uStack_50 = _UNK_027dbb30;
  if (param_4 != 0) {
    Aska::Matrix::MulFromLeft(Aska::Matrix const*)(&fStack_80,param_4);
  }
  fVar1 = fStack_34;
  Aska::Matrix::Invert()(&fStack_80);
  fVar2 = *param_2;
  fVar3 = param_2[1];
  fVar4 = param_2[2];
  fStack_80 = fStack_80 + fVar2 * (float)uStack_50;
  fStack_7c = fStack_7c + fVar2 * uStack_50._4_4_;
  fStack_78 = fStack_78 + fVar2 * (float)uStack_48;
  fStack_74 = fStack_74 + fVar2 * uStack_48._4_4_;
  fStack_70 = fVar3 * (float)uStack_50 + fStack_70;
  fStack_6c = fVar3 * uStack_50._4_4_ + fStack_6c;
  fStack_68 = fVar3 * (float)uStack_48 + fStack_68;
  fStack_64 = fVar3 * uStack_48._4_4_ + fStack_64;
  fStack_60 = fVar4 * (float)uStack_50 + fStack_60;
  fStack_5c = fVar4 * uStack_50._4_4_ + fStack_5c;
  fStack_58 = fVar4 * (float)uStack_48 + fStack_58;
  fStack_54 = fVar4 * uStack_48._4_4_ + fStack_54;
  Aska::Vector::ApplyMatrixNoWeighted(Aska::Matrix const*)(&uStack_40,&fStack_80);
  fVar2 = SQRT(fStack_80 * fStack_80 + fStack_70 * fStack_70 + fStack_60 * fStack_60);
  if (NAN(fVar2)) {
    fVar2 = (float)sqrtf();
  }
  fVar4 = fStack_7c * fStack_7c + fStack_6c * fStack_6c + fStack_5c * fStack_5c;
  fVar3 = SQRT(fVar4);
  if (NAN(fVar3)) {
    fVar3 = (float)sqrtf(fVar4);
  }
  if (fVar2 <= fVar3) {
    fVar2 = fVar3;
  }
  fVar4 = fStack_78 * fStack_78 + fStack_68 * fStack_68 + fStack_58 * fStack_58;
  fVar3 = SQRT(fVar4);
  if (NAN(fVar3)) {
    fVar3 = (float)sqrtf(fVar4);
  }
  if (fVar2 <= fVar3) {
    fVar2 = fVar3;
  }
  fStack_34 = fVar1 * fVar2;
  Aska::AABB::CalcOverlappedStatus(Aska::Sphere const*, float) const(param_1,param_2,&uStack_40);
  return;
}

// ==== Aska::Box::IsIntersected(Aska::Box const*)
// vaddr 0x2333478 | ghidra 0x2433478 | size 1476 | symbol _ZN4Aska3Box13IsIntersectedEPKS0_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN4Aska3Box13IsIntersectedEPKS0_(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
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
  
  fVar19 = param_1[8];
  fVar21 = param_1[9];
  fVar12 = param_2[8];
  fVar14 = param_2[9];
  fVar10 = param_2[0xc];
  fVar11 = param_2[0xd];
  fVar23 = param_1[10];
  fVar15 = param_2[10];
  fVar13 = param_2[0xe];
  fVar38 = param_2[0x10];
  fVar39 = param_2[0x11];
  fVar9 = param_2[0x12];
  fVar1 = param_2[4];
  fVar2 = param_2[5];
  fVar36 = *param_2 - *param_1;
  fVar37 = param_2[1] - param_1[1];
  fVar4 = param_2[6];
  fVar16 = param_2[2] - param_1[2];
  fVar22 = fVar19 * fVar12 + fVar21 * fVar14 + fVar23 * fVar15;
  fVar17 = fVar19 * fVar10 + fVar21 * fVar11 + fVar23 * fVar13;
  fVar3 = param_1[4];
  fVar6 = fVar19 * fVar38 + fVar21 * fVar39 + fVar23 * fVar9;
  fVar18 = ABS(fVar22);
  fVar8 = ABS(fVar17);
  fVar5 = ABS(fVar6);
  fVar19 = fVar36 * fVar19 + fVar37 * fVar21 + fVar16 * fVar23;
  if (ABS(fVar19) <= fVar3 + fVar1 * fVar18 + fVar2 * fVar8 + fVar4 * fVar5) {
    fVar24 = param_1[0xc];
    fVar25 = param_1[0xd];
    fVar27 = param_1[0xe];
    fVar7 = param_1[5];
    fVar21 = fVar24 * fVar12 + fVar25 * fVar14 + fVar27 * fVar15;
    fVar34 = fVar24 * fVar10 + fVar25 * fVar11 + fVar27 * fVar13;
    fVar29 = fVar24 * fVar38 + fVar25 * fVar39 + fVar27 * fVar9;
    fVar23 = ABS(fVar21);
    fVar31 = ABS(fVar34);
    fVar25 = fVar36 * fVar24 + fVar37 * fVar25 + fVar16 * fVar27;
    fVar24 = ABS(fVar29);
    if (ABS(fVar25) <= fVar7 + fVar1 * fVar23 + fVar2 * fVar31 + fVar4 * fVar24) {
      fVar26 = param_1[0x10];
      fVar28 = param_1[0x11];
      fVar33 = param_1[0x12];
      fVar27 = fVar26 * fVar10 + fVar28 * fVar11 + fVar33 * fVar13;
      fVar30 = fVar36 * fVar26 + fVar37 * fVar28 + fVar16 * fVar33;
      fVar20 = fVar26 * fVar12 + fVar28 * fVar14 + fVar33 * fVar15;
      fVar32 = fVar26 * fVar38 + fVar28 * fVar39 + fVar33 * fVar9;
      fVar35 = ABS(fVar20);
      fVar26 = ABS(fVar27);
      fVar28 = param_1[6];
      fVar33 = ABS(fVar32);
      if (((ABS(fVar30) <= fVar28 + fVar1 * fVar35 + fVar2 * fVar26 + fVar4 * fVar33) &&
          (ABS(fVar36 * fVar12 + fVar37 * fVar14 + fVar16 * fVar15) <=
           fVar1 + fVar35 * fVar28 + fVar3 * fVar18 + fVar7 * fVar23)) &&
         (ABS(fVar36 * fVar10 + fVar37 * fVar11 + fVar16 * fVar13) <=
          fVar2 + fVar26 * fVar28 + fVar3 * fVar8 + fVar7 * fVar31)) {
        fVar9 = ABS(fVar36 * fVar38 + fVar37 * fVar39 + fVar16 * fVar9);
        fVar10 = fVar4 + fVar33 * fVar28 + fVar3 * fVar5 + fVar7 * fVar24;
        if (((((((((_UNK_029715ac < fVar18 || _UNK_029715ac < fVar8) || _UNK_029715ac < fVar5) ||
                 _UNK_029715ac < fVar23) || _UNK_029715ac < fVar31) || _UNK_029715ac < fVar24) ||
              _UNK_029715ac < fVar35) || _UNK_029715ac < fVar26) || _UNK_029715ac < fVar33) ||
            fVar10 < fVar9) {
          return fVar9 <= fVar10;
        }
        if (((((ABS(fVar30 * fVar21 - fVar25 * fVar20) <=
                fVar35 * fVar7 + fVar28 * fVar23 + fVar4 * fVar8 + fVar2 * fVar5) &&
              (ABS(fVar30 * fVar34 - fVar25 * fVar27) <=
               fVar26 * fVar7 + fVar28 * fVar31 + fVar4 * fVar18 + fVar1 * fVar5)) &&
             ((ABS(fVar30 * fVar29 - fVar25 * fVar32) <=
               fVar2 * fVar18 + fVar1 * fVar8 + fVar33 * fVar7 + fVar28 * fVar24 &&
              ((ABS(fVar19 * fVar20 - fVar30 * fVar22) <=
                fVar35 * fVar3 + fVar28 * fVar18 + fVar4 * fVar31 + fVar2 * fVar24 &&
               (ABS(fVar19 * fVar27 - fVar30 * fVar17) <=
                fVar26 * fVar3 + fVar28 * fVar8 + fVar4 * fVar23 + fVar1 * fVar24)))))) &&
            (ABS(fVar19 * fVar32 - fVar30 * fVar6) <=
             fVar2 * fVar23 + fVar1 * fVar31 + fVar33 * fVar3 + fVar28 * fVar5)) &&
           ((ABS(fVar25 * fVar22 - fVar19 * fVar21) <=
             fVar26 * fVar4 + fVar2 * fVar33 + fVar18 * fVar7 + fVar3 * fVar23 &&
            (ABS(fVar25 * fVar17 - fVar19 * fVar34) <=
             fVar35 * fVar4 + fVar1 * fVar33 + fVar7 * fVar8 + fVar3 * fVar31)))) {
          return ABS(fVar25 * fVar6 - fVar19 * fVar29) <=
                 fVar35 * fVar2 + fVar1 * fVar26 + fVar7 * fVar5 + fVar3 * fVar24;
        }
      }
    }
  }
  return false;
}

// ==== Aska::Box::Face(int, int, int, Aska::Vector*, Aska::Vector const*, Aska::Vector const*, float*, float*) const
// vaddr 0x2333a3c | ghidra 0x2433a3c | size 1240 | symbol _ZNK4Aska3Box4FaceEiiiPNS_6VectorEPKS1_S4_PfS5_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska3Box4FaceEiiiPNS_6VectorEPKS1_S4_PfS5_
               (long param_1,uint param_2,uint param_3,uint param_4,long param_5,long param_6,
               long param_7,float *param_8,float *param_9)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float afStack_10 [4];
  
  uVar3 = -(ulong)(param_3 >> 0x1f) & 0xfffffffc00000000 | (ulong)param_3 << 2;
  param_1 = param_1 + 0x10;
  fVar15 = *(float *)(param_1 + uVar3);
  uVar6 = -(ulong)(param_4 >> 0x1f) & 0xfffffffc00000000 | (ulong)param_4 << 2;
  uVar7 = -(ulong)(param_2 >> 0x1f) & 0xfffffffc00000000 | (ulong)param_2 << 2;
  *(float *)((long)afStack_10 + uVar3) = *(float *)(param_5 + uVar3) + fVar15;
  fVar16 = *(float *)(param_1 + uVar6);
  lVar2 = (long)(int)param_3;
  lVar1 = (long)(int)param_4;
  fVar8 = *(float *)(param_5 + uVar6) + fVar16;
  *(float *)((long)afStack_10 + uVar6) = fVar8;
  fVar13 = *(float *)(param_6 + uVar7);
  fVar9 = *(float *)((long)afStack_10 + uVar3);
  fVar12 = *(float *)(param_6 + uVar3);
  fVar10 = *(float *)(param_7 + uVar7);
  fVar11 = *(float *)(param_6 + uVar6);
  lVar4 = (long)(int)param_2;
  if (fVar12 * fVar10 <= fVar13 * fVar9) {
    if (fVar10 * fVar11 <= fVar8 * fVar13) {
      lVar5 = lVar4 * 4;
      lVar1 = lVar1 * 4;
      *(undefined4 *)(param_5 + lVar5) = *(undefined4 *)(param_1 + lVar5);
      lVar2 = lVar2 * 4;
      fVar8 = 1.0 / *(float *)(param_6 + lVar5);
      *(float *)(param_5 + lVar2) =
           *(float *)(param_5 + lVar2) -
           fVar8 * *(float *)(param_6 + lVar2) * *(float *)(param_7 + lVar5);
      *(float *)(param_5 + lVar1) =
           *(float *)(param_5 + lVar1) -
           fVar8 * *(float *)(param_6 + lVar1) * *(float *)(param_7 + lVar5);
      if (param_8 == (float *)0x0) {
        return;
      }
      *param_8 = -(fVar8 * *(float *)(param_7 + lVar4 * 4));
      return;
    }
    fVar16 = fVar13 * fVar10;
    fVar14 = fVar8 * fVar11;
    fVar11 = fVar13 * fVar13 + fVar11 * fVar11;
    fVar13 = fVar9 * fVar11 - fVar12 * (fVar16 + fVar14);
    if (fVar13 <= (fVar11 + fVar11) * fVar15) {
      fVar13 = fVar13 / fVar11;
      fVar9 = fVar9 - fVar13;
      fVar14 = fVar14 + fVar16 + fVar12 * fVar9;
      fVar11 = -fVar14 / (fVar12 * fVar12 + fVar11);
      *param_9 = fVar8 * fVar8 + fVar10 * fVar10 + fVar9 * fVar9 + fVar14 * fVar11 + *param_9;
      if (param_8 != (float *)0x0) {
        *param_8 = fVar11;
      }
      *(undefined4 *)(param_5 + lVar4 * 4) = *(undefined4 *)(param_1 + lVar4 * 4);
      fVar13 = fVar13 - *(float *)(param_1 + lVar2 * 4);
      goto code_r0x02433e80;
    }
    fVar13 = *(float *)(param_7 + lVar2 * 4);
    fVar15 = *param_9;
    fVar14 = fVar14 + fVar16 + fVar12 * fVar13;
    fVar9 = -fVar14 / (fVar12 * fVar12 + fVar11);
    fVar8 = fVar8 * fVar8 + fVar10 * fVar10 + fVar13 * fVar13;
code_r0x02433ce8:
    *param_9 = fVar15 + fVar8 + fVar14 * fVar9;
    if (param_8 != (float *)0x0) {
      *param_8 = fVar9;
    }
    *(undefined4 *)(param_5 + lVar4 * 4) = *(undefined4 *)(param_1 + lVar4 * 4);
    *(undefined4 *)(param_5 + lVar2 * 4) = *(undefined4 *)(param_1 + lVar2 * 4);
  }
  else {
    fVar19 = fVar13 * fVar13;
    if (fVar10 * fVar11 <= fVar8 * fVar13) {
      fVar19 = fVar19 + fVar12 * fVar12;
      fVar13 = fVar9 * fVar12 + fVar13 * fVar10;
      fVar12 = fVar8 * fVar19 - fVar11 * fVar13;
      if ((fVar19 + fVar19) * fVar16 < fVar12) {
        fVar19 = fVar19 + fVar11 * fVar11;
code_r0x02433da0:
        fVar8 = *(float *)(param_7 + lVar1 * 4);
        fVar13 = fVar13 + fVar11 * fVar8;
        fVar19 = -fVar13 / fVar19;
        *param_9 = *param_9 + fVar9 * fVar9 + fVar10 * fVar10 + fVar8 * fVar8 + fVar13 * fVar19;
        if (param_8 != (float *)0x0) {
          *param_8 = fVar19;
        }
        *(undefined4 *)(param_5 + lVar4 * 4) = *(undefined4 *)(param_1 + lVar4 * 4);
        *(float *)(param_5 + lVar2 * 4) = -*(float *)(param_1 + lVar2 * 4);
        *(undefined4 *)(param_5 + lVar1 * 4) = *(undefined4 *)(param_1 + lVar1 * 4);
        return;
      }
      fVar12 = fVar12 / fVar19;
      fVar19 = fVar19 + fVar11 * fVar11;
code_r0x02433ea4:
      fVar8 = fVar8 - fVar12;
      fVar13 = fVar13 + fVar11 * fVar8;
      fVar19 = -fVar13 / fVar19;
      *param_9 = fVar9 * fVar9 + fVar10 * fVar10 + fVar8 * fVar8 + fVar13 * fVar19 + *param_9;
      if (param_8 != (float *)0x0) {
        *param_8 = fVar19;
      }
      *(undefined4 *)(param_5 + lVar4 * 4) = *(undefined4 *)(param_1 + lVar4 * 4);
      *(float *)(param_5 + lVar2 * 4) = -*(float *)(param_1 + lVar2 * 4);
      fVar12 = fVar12 - *(float *)(param_1 + lVar1 * 4);
      goto code_r0x02433f08;
    }
    fVar17 = fVar11 * fVar11;
    fVar13 = fVar13 * fVar10;
    fVar14 = fVar8 * fVar11;
    fVar18 = fVar19 + fVar17;
    fVar20 = fVar9 * fVar18 - fVar12 * (fVar13 + fVar14);
    if (0.0 <= fVar20) {
      if ((fVar18 + fVar18) * fVar15 < fVar20) {
        fVar11 = *(float *)(param_7 + lVar2 * 4);
        fVar15 = *param_9;
        fVar14 = fVar14 + fVar13 + fVar12 * fVar11;
        fVar9 = -fVar14 / (fVar12 * fVar12 + fVar18);
        fVar8 = fVar8 * fVar8 + fVar10 * fVar10 + fVar11 * fVar11;
        goto code_r0x02433ce8;
      }
      fVar9 = fVar9 - fVar20 / fVar18;
      fVar14 = fVar14 + fVar13 + fVar12 * fVar9;
      fVar13 = -fVar14 / (fVar12 * fVar12 + fVar18);
      *param_9 = fVar8 * fVar8 + fVar10 * fVar10 + fVar9 * fVar9 + fVar14 * fVar13 + *param_9;
      if (param_8 != (float *)0x0) {
        *param_8 = fVar13;
      }
      *(undefined4 *)(param_5 + lVar4 * 4) = *(undefined4 *)(param_1 + lVar4 * 4);
      fVar13 = fVar20 / fVar18 - *(float *)(param_1 + lVar2 * 4);
    }
    else {
      fVar19 = fVar19 + fVar12 * fVar12;
      fVar13 = fVar9 * fVar12 + fVar13;
      fVar12 = fVar8 * fVar19 - fVar11 * fVar13;
      if (0.0 <= fVar12) {
        if ((fVar19 + fVar19) * fVar16 < fVar12) {
          fVar19 = fVar19 + fVar17;
          goto code_r0x02433da0;
        }
        fVar12 = fVar12 / fVar19;
        fVar19 = fVar19 + fVar17;
        goto code_r0x02433ea4;
      }
      fVar11 = -(fVar13 + fVar14) / (fVar19 + fVar17);
      *param_9 = fVar8 * fVar8 + fVar9 * fVar9 + fVar10 * fVar10 + (fVar13 + fVar14) * fVar11 +
                 *param_9;
      if (param_8 != (float *)0x0) {
        *param_8 = fVar11;
      }
      *(undefined4 *)(param_5 + lVar4 * 4) = *(undefined4 *)(param_1 + lVar4 * 4);
      fVar13 = -*(float *)(param_1 + lVar2 * 4);
    }
code_r0x02433e80:
    *(float *)(param_5 + lVar2 * 4) = fVar13;
  }
  fVar12 = -*(float *)(param_1 + lVar1 * 4);
code_r0x02433f08:
  *(float *)(param_5 + lVar1 * 4) = fVar12;
  return;
}

// ==== Aska::AABB::SetCone(Aska::Vector const*, Aska::Vector const*, float, float)
// vaddr 0x2333f14 | ghidra 0x2433f14 | size 812 | symbol _ZN4Aska4AABB7SetConeEPKNS_6VectorES3_ff | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska4AABB7SetConeEPKNS_6VectorES3_ff
               (float param_1,float param_2,float *param_3,float *param_4,float *param_5)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  float fVar5;
  bool bVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_74;
  
  fVar14 = *param_4;
  fVar16 = param_4[1];
  fStack_80 = fVar14;
  fVar17 = param_4[2];
  fVar7 = param_1 + (float)(int)(param_1 * _UNK_027ebdf4) * _UNK_027edb30;
  bVar6 = ((int)(param_1 * _UNK_027ebdf4) & 1U) != 0;
  fVar11 = fVar7;
  if (bVar6) {
    fVar11 = -fVar7;
  }
  fVar7 = fVar7 * fVar7;
  fStack_7c = fVar16;
  fStack_78 = fVar17;
  fVar5 = param_4[3];
  fStack_74 = fVar5;
  fVar18 = *param_5;
  fVar15 = param_5[1];
  fVar10 = fVar7 * (fVar7 * (fVar7 * (fVar7 * _UNK_027ebdf8 + _UNK_027ebdfc) + _UNK_027ebe00) +
                   _UNK_027ebe04);
  fVar13 = param_5[2];
  fVar8 = fVar7 * (fVar7 * (fVar7 * (fVar7 * _UNK_027f7ca4 + _UNK_027f7ca8) + _UNK_027f7cac) +
                  _UNK_027f7cb0) + _UNK_027f7cb4;
  fVar12 = SQRT(fVar18 * 0.0 * fVar18 * 0.0 + fVar15 * fVar15 + fVar13 * fVar13);
  fVar7 = _UNK_027ebe08 - fVar10;
  if (!bVar6) {
    fVar7 = fVar10 + _UNK_027ebe0c;
  }
  if (NAN(fVar12)) {
    fVar12 = (float)sqrtf();
  }
  fVar10 = SQRT(fVar13 * fVar13 + fVar18 * fVar18 + fVar15 * 0.0 * fVar15 * 0.0);
  if (NAN(fVar10)) {
    fVar10 = (float)sqrtf();
  }
  fVar14 = fVar18 * param_2 + fVar14;
  fVar9 = fVar18 * fVar18 + fVar15 * fVar15 + fVar13 * 0.0 * fVar13 * 0.0;
  fVar18 = SQRT(fVar9);
  fVar7 = (fVar11 * fVar8 * param_2) / fVar7;
  fVar16 = fVar15 * param_2 + fVar16;
  fVar17 = fVar13 * param_2 + fVar17;
  if (NAN(fVar18)) {
    fVar18 = (float)sqrtf(fVar9);
  }
  fStack_a0 = fVar7 * fVar12 + fVar14;
  fStack_9c = fVar7 * fVar10 + fVar16;
  fStack_98 = fVar7 * fVar18 + fVar17;
  fStack_94 = fVar7 + fVar5;
  pfVar4 = &fStack_a0;
  if (fStack_a0 < fStack_80) {
    pfVar4 = &fStack_80;
  }
  fStack_a0 = *pfVar4;
  fStack_90 = fVar14 - fVar7 * fVar12;
  pfVar4 = &fStack_a0;
  if (fStack_9c < fStack_7c) {
    pfVar4 = &fStack_80;
  }
  fStack_8c = fVar16 - fVar7 * fVar10;
  fStack_88 = fVar17 - fVar7 * fVar18;
  pfVar1 = &fStack_a0;
  if (fStack_98 < fStack_78) {
    pfVar1 = &fStack_80;
  }
  pfVar2 = &fStack_80;
  if (fStack_90 < fStack_80) {
    pfVar2 = &fStack_90;
  }
  fStack_84 = fVar5 - fVar7;
  pfVar3 = &fStack_80;
  if (fStack_8c < fStack_7c) {
    pfVar3 = &fStack_90;
  }
  fStack_9c = pfVar4[1];
  fStack_90 = *pfVar2;
  pfVar4 = &fStack_80;
  if (fStack_88 < fStack_78) {
    pfVar4 = &fStack_90;
  }
  fVar14 = (fStack_a0 + *pfVar2) * 0.5;
  fStack_8c = pfVar3[1];
  fVar16 = pfVar1[2];
  fVar11 = pfVar4[2];
  fVar17 = (fStack_9c + pfVar3[1]) * 0.5;
  *param_3 = fVar14;
  param_3[1] = fVar17;
  param_3[4] = fStack_a0 - fVar14;
  param_3[5] = fStack_9c - fVar17;
  fVar14 = (fVar16 + fVar11) * 0.5;
  param_3[2] = fVar14;
  param_3[3] = (fVar7 + fVar5 + (fVar5 - fVar7)) * 0.5;
  param_3[6] = fVar16 - fVar14;
  param_3[7] = 1e+30;
  return;
}

// ==== Aska::AABB::SetCapsule(Aska::Vector const*, Aska::Vector const*, float)
// vaddr 0x2334240 | ghidra 0x2434240 | size 56 | symbol _ZN4Aska4AABB10SetCapsuleEPKNS_6VectorES3_f | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4AABB10SetCapsuleEPKNS_6VectorES3_f
               (float param_1,undefined8 *param_2,undefined8 *param_3,undefined8 *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  fVar1 = (float)*param_3;
  fVar2 = (float)((ulong)*param_3 >> 0x20);
  fVar3 = (float)param_3[1];
  fVar4 = (float)((ulong)param_3[1] >> 0x20);
  fVar5 = (fVar1 + (float)*param_4) * 0.5;
  fVar6 = (fVar2 + (float)((ulong)*param_4 >> 0x20)) * 0.5;
  fVar7 = (fVar3 + (float)param_4[1]) * 0.5;
  fVar8 = (fVar4 + (float)((ulong)param_4[1] >> 0x20)) * 0.5;
  param_2[1] = CONCAT44(fVar8,fVar7);
  *param_2 = CONCAT44(fVar6,fVar5);
  param_2[3] = CONCAT44(param_1 + ABS(fVar4 - fVar8),param_1 + ABS(fVar3 - fVar7));
  param_2[2] = CONCAT44(param_1 + ABS(fVar2 - fVar6),param_1 + ABS(fVar1 - fVar5));
  *(undefined4 *)((long)param_2 + 0xc) = 0x3f800000;
  *(undefined4 *)((long)param_2 + 0x1c) = 0x3f800000;
  return;
}

// ==== Aska::AABB::SetBox(Aska::Box const*)
// vaddr 0x2334278 | ghidra 0x2434278 | size 184 | symbol _ZN4Aska4AABB6SetBoxEPKNS_3BoxE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4AABB6SetBoxEPKNS_3BoxE(undefined4 *param_1,undefined4 *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = param_2[3];
  fVar1 = (float)param_2[9];
  fVar2 = (float)param_2[10];
  fVar3 = (float)param_2[4];
  fVar4 = (float)param_2[5];
  fVar5 = (float)param_2[0xd];
  fVar6 = (float)param_2[0xe];
  fVar8 = (float)param_2[6];
  fVar9 = (float)param_2[0x11];
  fVar7 = (float)param_2[0x12];
  param_1[4] = ABS(fVar3 * (float)param_2[8]) + ABS(fVar4 * (float)param_2[0xc]) +
               ABS(fVar8 * (float)param_2[0x10]);
  param_1[5] = ABS(fVar3 * fVar1) + ABS(fVar4 * fVar5) + ABS(fVar8 * fVar9);
  param_1[6] = ABS(fVar3 * fVar2) + ABS(fVar4 * fVar6) + ABS(fVar8 * fVar7);
  param_1[7] = 0x7149f2ca;
  return;
}

// ==== Aska::AABB::SetSphere(Aska::Sphere const*)
// vaddr 0x2334330 | ghidra 0x2434330 | size 48 | symbol _ZN4Aska4AABB9SetSphereEPKNS_6SphereE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska4AABB9SetSphereEPKNS_6SphereE(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = param_2[3];
  uVar1 = param_2[3];
  param_1[4] = uVar1;
  param_1[5] = uVar1;
  param_1[6] = uVar1;
  return;
}

// ==== Aska::Plane::ComputeVertices(Aska::Vector*, float) const
// vaddr 0x2334360 | ghidra 0x2434360 | size 496 | symbol _ZNK4Aska5Plane15ComputeVerticesEPNS_6VectorEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK4Aska5Plane15ComputeVerticesEPNS_6VectorEf(float param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  
  fVar1 = *param_2;
  fVar3 = param_2[1];
  fVar2 = param_2[2];
  fVar12 = param_2[3];
  fVar13 = fVar1 + 1.0;
  fVar14 = fVar3 + 1.0;
  fVar15 = fVar2 + 1.0;
  fVar6 = fVar13 * fVar13 + fVar14 * fVar14 + fVar15 * fVar15;
  fVar4 = SQRT(fVar6);
  if (NAN(fVar4)) {
    fVar4 = (float)sqrtf(fVar6);
  }
  if (_UNK_027e519c <= fVar4) {
    fVar4 = 1.0 / fVar4;
    fVar13 = fVar13 * fVar4;
    fVar14 = fVar14 * fVar4;
    fVar15 = fVar15 * fVar4;
  }
  fVar5 = param_2[4];
  fVar7 = param_2[5];
  fVar8 = param_2[6];
  *param_3 = fVar1;
  param_3[1] = fVar3;
  param_3[2] = fVar2;
  param_3[3] = fVar12;
  fVar4 = fVar15 * fVar7 - fVar14 * fVar8;
  fVar6 = fVar13 * fVar8 - fVar15 * fVar5;
  fVar13 = fVar14 * fVar5 - fVar13 * fVar7;
  fVar9 = fVar4 * param_1 + fVar1;
  fVar10 = fVar6 * param_1 + fVar3;
  fVar11 = fVar13 * param_1 + fVar2;
  fVar12 = (fVar7 * fVar13 - fVar8 * fVar6) * param_1 + fVar1;
  fVar14 = (fVar8 * fVar4 - fVar5 * fVar13) * param_1 + fVar3;
  fVar15 = (fVar5 * fVar6 - fVar7 * fVar4) * param_1 + fVar2;
  fVar4 = fVar9;
  fVar6 = fVar11;
  fVar13 = fVar10;
  if (0.0 < fVar8 * ((fVar9 - fVar1) * (fVar14 - fVar10) - (fVar10 - fVar3) * (fVar12 - fVar9)) +
            fVar5 * ((fVar10 - fVar3) * (fVar15 - fVar11) - (fVar11 - fVar2) * (fVar14 - fVar10)) +
            fVar7 * ((fVar11 - fVar2) * (fVar12 - fVar9) - (fVar9 - fVar1) * (fVar15 - fVar11))) {
    fVar4 = fVar12;
    fVar6 = fVar15;
    fVar13 = fVar14;
    fVar14 = fVar10;
    fVar15 = fVar11;
    fVar12 = fVar9;
  }
  param_3[4] = fVar12;
  param_3[5] = fVar14;
  param_3[8] = fVar4;
  param_3[9] = fVar13;
  param_3[6] = fVar15;
  param_3[7] = 1.0;
  param_3[10] = fVar6;
  param_3[0xb] = 1.0;
  return;
}
