// port/decomp/math/collision_math.c: Ghidra decompiles for the math subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:09 UTC: tools/decomp.sh '--into' 'math/collision_math' 'Collision::Math::'

// ==== Collision::Math::CalcLength_LineLine(Framework::CVector const&, Framework::CVector const&, Framework::CVector const&, Framework::CVector const&, Framework::CVector*, Framework::CVector*)
// vaddr 0x11e05f4 | ghidra 0x12e05f4 | size 1680 | symbol _ZN9Collision4Math19CalcLength_LineLineERKN9Framework7CVectorES4_S4_S4_PS2_S5_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1  [16]
_ZN9Collision4Math19CalcLength_LineLineERKN9Framework7CVectorES4_S4_S4_PS2_S5_
          (float *param_1,float *param_2,float *param_3,float *param_4,float *param_5,float *param_6
          )

{
  undefined1 auVar1 [16];
  float *pfVar2;
  float *pfVar3;
  float fVar4;
  undefined1 auVar5 [16];
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar14;
  ulong uVar13;
  undefined8 uVar15;
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
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  undefined4 uStack_a4;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  
  fVar11 = param_2[1] * param_4[2] - param_2[2] * param_4[1];
  fVar21 = param_2[2] * *param_4 - param_4[2] * *param_2;
  fVar22 = param_4[1] * *param_2 - param_2[1] * *param_4;
  fVar10 = *param_3;
  fVar19 = param_3[1];
  fVar20 = *param_1;
  fVar23 = param_1[1];
  fVar16 = param_3[2];
  fVar18 = param_1[2];
  fVar6 = fVar22 * fVar22 + fVar11 * fVar11 + fVar21 * fVar21;
  fVar4 = SQRT(fVar6);
  if (NAN(fVar4)) {
    fVar4 = (float)sqrtf(fVar6);
  }
  fVar6 = _UNK_027e519c;
  fVar10 = fVar10 - fVar20;
  fVar19 = fVar19 - fVar23;
  fVar16 = fVar16 - fVar18;
  if (_UNK_027e519c <= fVar4) {
    fVar4 = 1.0 / fVar4;
    fVar11 = fVar11 * fVar4;
    fVar21 = fVar4 * fVar21;
    fVar22 = fVar4 * fVar22;
  }
  fVar25 = *param_2;
  fVar26 = param_2[1];
  fVar29 = param_2[2];
  fVar4 = fVar10 * fVar11 + fVar19 * fVar21 + fVar16 * fVar22;
  fVar23 = *param_1 + fVar11 * fVar4;
  fVar7 = param_1[1] + fVar21 * fVar4;
  fVar11 = param_1[2] + fVar22 * fVar4;
  fVar28 = fVar23 + fVar25;
  fVar27 = fVar7 + fVar26;
  fVar24 = fVar11 + fVar29;
  uStack_94 = 0x3f800000;
  fVar8 = *param_3;
  fVar9 = param_3[1];
  fVar30 = *param_4;
  fVar31 = param_4[1];
  fVar20 = param_3[2];
  fVar32 = param_4[2];
  fVar17 = fVar8 + fVar30;
  fVar34 = fVar9 + fVar31;
  fVar33 = fVar20 + fVar32;
  fVar21 = fVar8 - fVar23;
  fVar22 = fVar17 - fVar23;
  fVar12 = fVar9 - fVar7;
  fVar14 = fVar34 - fVar7;
  fVar4 = fVar20 - fVar11;
  fVar18 = fVar33 - fVar11;
  uStack_a4 = 0x3f800000;
  fStack_b0 = fVar17;
  fStack_ac = fVar34;
  fStack_a8 = fVar33;
  fStack_a0 = fVar28;
  fStack_9c = fVar27;
  fStack_98 = fVar24;
  if ((fVar12 * fVar25 - fVar21 * fVar26) * (fVar14 * fVar25 - fVar22 * fVar26) +
      (fVar4 * fVar26 - fVar12 * fVar29) * (fVar18 * fVar26 - fVar14 * fVar29) +
      (fVar21 * fVar29 - fVar4 * fVar25) * (fVar22 * fVar29 - fVar18 * fVar25) <= 0.0) {
    fVar23 = fVar23 - fVar8;
    fVar8 = fVar28 - fVar8;
    fVar7 = fVar7 - fVar9;
    fVar9 = fVar27 - fVar9;
    fVar11 = fVar11 - fVar20;
    fVar20 = fVar24 - fVar20;
    if ((fVar7 * fVar30 - fVar23 * fVar31) * (fVar9 * fVar30 - fVar8 * fVar31) +
        (fVar11 * fVar31 - fVar7 * fVar32) * (fVar20 * fVar31 - fVar9 * fVar32) +
        (fVar23 * fVar32 - fVar11 * fVar30) * (fVar8 * fVar32 - fVar20 * fVar30) <= 0.0) {
      fVar21 = fVar26 * fVar32 - fVar29 * fVar31;
      fVar20 = fVar29 * fVar30 - fVar32 * fVar25;
      fVar18 = fVar31 * fVar25 - fVar26 * fVar30;
      fVar11 = fVar18 * fVar18 + fVar21 * fVar21 + fVar20 * fVar20;
      fVar4 = SQRT(fVar11);
      if (NAN(fVar4)) {
        fVar4 = (float)sqrtf(fVar11);
      }
      if (fVar6 <= fVar4) {
        fVar4 = 1.0 / fVar4;
        fVar21 = fVar21 * fVar4;
        fVar20 = fVar4 * fVar20;
        fVar18 = fVar4 * fVar18;
      }
      if (param_5 != (float *)0x0) {
        fVar4 = *param_2;
        fVar11 = param_2[1];
        fVar22 = param_2[2];
        fVar8 = fVar4 * fVar4 + fVar11 * fVar11 + fVar22 * fVar22;
        fVar23 = SQRT(fVar8);
        if (NAN(fVar23)) {
          fVar23 = (float)sqrtf(fVar8);
        }
        if (fVar6 <= fVar23) {
          fVar23 = 1.0 / fVar23;
          fVar4 = fVar23 * fVar4;
          fVar11 = fVar23 * fVar11;
          fVar22 = fVar23 * fVar22;
        }
        fVar23 = fVar16 * fVar22 + fVar19 * fVar11 + fVar10 * fVar4;
        fVar12 = param_1[1];
        fVar8 = param_1[2];
        *param_5 = *param_1 + fVar23 * fVar4;
        param_5[1] = fVar12 + fVar23 * fVar11;
        param_5[2] = fVar8 + fVar23 * fVar22;
        param_5[3] = 1.0;
      }
      uVar13 = CONCAT44(0,ABS(fVar10 * fVar21 + fVar19 * fVar20 + fVar16 * fVar18));
      uVar15 = 0;
      auVar5._8_8_ = 0;
      auVar5._0_8_ = uVar13;
      if (param_6 == (float *)0x0) {
        return auVar5;
      }
      fVar4 = *param_4;
      fVar11 = param_4[1];
      fVar18 = param_4[2];
      fVar21 = fVar4 * fVar4 + fVar11 * fVar11 + fVar18 * fVar18;
      fVar20 = SQRT(fVar21);
      if (NAN(fVar20)) {
        fVar20 = (float)sqrtf(fVar21);
      }
      auVar1._8_8_ = uVar15;
      auVar1._0_8_ = uVar13;
      if (fVar6 <= fVar20) {
        fVar20 = 1.0 / fVar20;
        fVar4 = fVar20 * fVar4;
        fVar11 = fVar20 * fVar11;
        fVar18 = fVar20 * fVar18;
      }
      fVar6 = (-(fVar19 * fVar11) - fVar10 * fVar4) - fVar16 * fVar18;
      fVar16 = param_3[1];
      fVar10 = param_3[2];
      *param_6 = *param_3 + fVar6 * fVar4;
      param_6[1] = fVar16 + fVar6 * fVar11;
      param_6[2] = fVar10 + fVar6 * fVar18;
      param_6[3] = 1.0;
      return auVar1;
    }
    fVar10 = fVar30 * fVar30 + fVar31 * fVar31 + fVar32 * fVar32;
    fVar4 = SQRT(fVar10);
    if (NAN(fVar4)) {
      fVar4 = (float)sqrtf(fVar10);
    }
    if (fVar6 <= fVar4) {
      fVar4 = 1.0 / fVar4;
      fVar30 = fVar4 * fVar30;
      fVar31 = fVar4 * fVar31;
      fVar32 = fVar4 * fVar32;
    }
    fVar4 = fVar11 * fVar32 + fVar7 * fVar31 + fVar23 * fVar30;
    fVar6 = fVar20 * fVar32 + fVar9 * fVar31 + fVar8 * fVar30;
    fVar23 = fVar23 - fVar4 * fVar30;
    fVar8 = fVar8 - fVar6 * fVar30;
    fVar7 = fVar7 - fVar4 * fVar31;
    fVar9 = fVar9 - fVar6 * fVar31;
    fVar11 = fVar11 - fVar4 * fVar32;
    fVar20 = fVar20 - fVar6 * fVar32;
    pfVar2 = param_3;
    param_2 = param_4;
    pfVar3 = param_6;
    if (fVar20 * fVar20 + fVar8 * fVar8 + fVar9 * fVar9 <=
        fVar11 * fVar11 + fVar23 * fVar23 + fVar7 * fVar7) {
      if (param_5 != (float *)0x0) {
        *param_5 = fVar28;
        param_5[1] = fVar27;
        param_5[2] = fVar24;
        param_5[3] = 1.0;
      }
      param_1 = &fStack_a0;
    }
    else if (param_5 != (float *)0x0) {
      *param_5 = *param_1;
      param_5[1] = param_1[1];
      param_5[2] = param_1[2];
      param_5[3] = param_1[3];
    }
  }
  else {
    fVar11 = fVar25 * fVar25 + fVar26 * fVar26 + fVar29 * fVar29;
    fVar10 = SQRT(fVar11);
    if (NAN(fVar10)) {
      fVar10 = (float)sqrtf(fVar11);
    }
    if (fVar6 <= fVar10) {
      fVar10 = 1.0 / fVar10;
      fVar25 = fVar10 * fVar25;
      fVar26 = fVar10 * fVar26;
      fVar29 = fVar10 * fVar29;
    }
    fVar6 = fVar4 * fVar29 + fVar12 * fVar26 + fVar21 * fVar25;
    fVar10 = fVar18 * fVar29 + fVar14 * fVar26 + fVar22 * fVar25;
    fVar21 = fVar21 - fVar6 * fVar25;
    fVar22 = fVar22 - fVar10 * fVar25;
    fVar12 = fVar12 - fVar6 * fVar26;
    fVar14 = fVar14 - fVar10 * fVar26;
    fVar4 = fVar4 - fVar6 * fVar29;
    fVar18 = fVar18 - fVar10 * fVar29;
    pfVar2 = param_1;
    pfVar3 = param_5;
    if (fVar18 * fVar18 + fVar22 * fVar22 + fVar14 * fVar14 <=
        fVar4 * fVar4 + fVar21 * fVar21 + fVar12 * fVar12) {
      if (param_6 != (float *)0x0) {
        *param_6 = fVar17;
        param_6[1] = fVar34;
        param_6[2] = fVar33;
        param_6[3] = 1.0;
      }
      param_1 = &fStack_b0;
    }
    else {
      param_1 = param_3;
      if (param_6 != (float *)0x0) {
        *param_6 = *param_3;
        param_6[1] = param_3[1];
        param_6[2] = param_3[2];
        param_6[3] = param_3[3];
      }
    }
  }
  auVar5 = Collision::Math::CalcLength_LinePoint(Framework::CVector const&, Framework::CVector const&, Framework::CVector const&, Framework::CVector*)(pfVar2,param_2,param_1,pfVar3);
  return auVar5;
}

// ==== Collision::Math::CalcLength_LinePoint(Framework::CVector const&, Framework::CVector const&, Framework::CVector const&, Framework::CVector*)
// vaddr 0x11e0c84 | ghidra 0x12e0c84 | size 536 | symbol _ZN9Collision4Math20CalcLength_LinePointERKN9Framework7CVectorES4_S4_PS2_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x012e0d44: Changing call to branch */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1  [16]
_ZN9Collision4Math20CalcLength_LinePointERKN9Framework7CVectorES4_S4_PS2_
          (float *param_1,float *param_2,float *param_3,float *param_4)

{
  float fVar1;
  undefined1 auVar2 [16];
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
  
  fVar1 = *param_3;
  fVar4 = param_3[1];
  fVar7 = *param_1;
  fVar5 = param_1[1];
  fVar3 = param_3[2];
  fVar9 = param_1[2];
  fVar11 = *param_2;
  fVar12 = param_2[1];
  fVar13 = param_2[2];
  if ((fVar1 - fVar7) * fVar11 + (fVar4 - fVar5) * fVar12 + (fVar3 - fVar9) * fVar13 <= 0.0) {
    if (param_4 != (float *)0x0) {
      *param_4 = fVar7;
      param_4[1] = param_1[1];
      param_4[2] = param_1[2];
      param_4[3] = param_1[3];
      fVar1 = *param_3;
      fVar4 = param_3[1];
      fVar7 = *param_1;
      fVar5 = param_1[1];
      fVar3 = param_3[2];
      fVar9 = param_1[2];
    }
    fVar10 = fVar1 - fVar7;
    fVar8 = fVar4 - fVar5;
    fVar6 = fVar3 - fVar9;
code_r0x012e0e40:
    fVar1 = fVar10 * fVar10 + fVar8 * fVar8;
    fVar6 = fVar6 * fVar6;
  }
  else {
    fVar10 = fVar7 + fVar11;
    fVar8 = fVar5 + fVar12;
    fVar6 = fVar9 + fVar13;
    if ((-(fVar12 * (fVar4 - fVar8)) - fVar11 * (fVar1 - fVar10)) - fVar13 * (fVar3 - fVar6) <= 0.0)
    {
      if (param_4 != (float *)0x0) {
        *param_4 = fVar10;
        param_4[1] = fVar8;
        param_4[2] = fVar6;
        param_4[3] = 1.0;
        fVar1 = *param_3;
        fVar4 = param_3[1];
        fVar3 = param_3[2];
      }
      fVar10 = fVar10 - fVar1;
      fVar8 = fVar8 - fVar4;
      fVar6 = fVar6 - fVar3;
      goto code_r0x012e0e40;
    }
    fVar10 = param_2[3];
    fVar6 = fVar11 * fVar11 + fVar12 * fVar12 + fVar13 * fVar13;
    fVar8 = SQRT(fVar6);
    if (NAN(fVar8)) goto code_r0x011f09a0;
    if (_UNK_027e519c <= fVar8) {
      fVar8 = 1.0 / fVar8;
      fVar11 = fVar8 * fVar11;
      fVar12 = fVar8 * fVar12;
      fVar13 = fVar8 * fVar13;
    }
    fVar1 = (fVar3 - fVar9) * fVar13 + (fVar4 - fVar5) * fVar12 + (fVar1 - fVar7) * fVar11;
    fVar3 = *param_1 + fVar1 * fVar11;
    fVar4 = param_1[1] + fVar1 * fVar12;
    fVar6 = param_1[2] + fVar1 * fVar13;
    if (param_4 != (float *)0x0) {
      *param_4 = fVar3;
      param_4[1] = fVar4;
      param_4[2] = fVar6;
      param_4[3] = fVar10;
    }
    fVar3 = *param_3 - fVar3;
    fVar4 = param_3[1] - fVar4;
    fVar6 = param_3[2] - fVar6;
    fVar1 = fVar3 * fVar3 + fVar4 * fVar4;
    fVar6 = fVar6 * fVar6;
  }
  fVar6 = fVar6 + fVar1;
  if (!NAN(SQRT(fVar6))) {
    return ZEXT416((uint)SQRT(fVar6));
  }
code_r0x011f09a0:
  auVar2 = (*(code *)PTR_sqrtf_02cb04c0)(fVar6);
  return auVar2;
}

// ==== Collision::Math::CalcLength_PointPoint(Framework::CVector const&, Framework::CVector const&)
// vaddr 0x11e0e9c | ghidra 0x12e0e9c | size 68 | symbol _ZN9Collision4Math21CalcLength_PointPointERKN9Framework7CVectorES4_ | lib libSOA-3.7.0.so | 2026-10-04
undefined1  [16]
_ZN9Collision4Math21CalcLength_PointPointERKN9Framework7CVectorES4_(float *param_1,float *param_2)

{
  undefined1 auVar1 [16];
  float fVar2;
  float fVar3;
  
  fVar2 = (float)*(undefined8 *)(param_1 + 1) - (float)*(undefined8 *)(param_2 + 1);
  fVar3 = (float)((ulong)*(undefined8 *)(param_1 + 1) >> 0x20) -
          (float)((ulong)*(undefined8 *)(param_2 + 1) >> 0x20);
  fVar2 = SQRT((*param_1 - *param_2) * (*param_1 - *param_2) + fVar2 * fVar2 + fVar3 * fVar3);
  if (NAN(fVar2)) {
    auVar1 = (*(code *)PTR_sqrtf_02cb04c0)();
    return auVar1;
  }
  return ZEXT416((uint)fVar2);
}
