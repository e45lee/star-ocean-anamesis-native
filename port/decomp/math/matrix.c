// port/decomp/math/matrix.c: Ghidra decompiles for the math subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:09 UTC: tools/decomp.sh '--into' 'math/matrix' 'Aska::Matrix::'

// ==== Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)
// vaddr 0x11acee8 | ghidra 0x12acee8 | size 700 | symbol _ZN4Aska6Matrix3MulEPKS0_S2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Matrix3MulEPKS0_S2_(undefined8 *param_1,float *param_2,float *param_3)

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
  float fVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  float fVar47;
  float fVar48;
  
  fVar1 = param_2[0xc];
  fVar5 = param_2[0xd];
  fVar17 = param_3[3];
  fVar19 = param_3[7];
  fVar9 = param_2[0xe];
  fVar13 = param_2[0xf];
  fVar21 = param_3[0xb];
  fVar23 = param_3[0xf];
  fVar25 = param_3[2];
  fVar27 = param_3[6];
  fVar29 = param_3[10];
  fVar31 = param_3[0xe];
  fVar33 = param_3[1];
  fVar35 = param_3[5];
  fVar37 = param_3[9];
  fVar39 = param_3[0xd];
  fVar41 = *param_3;
  fVar43 = param_3[4];
  fVar45 = param_3[8];
  fVar47 = param_3[0xc];
  fVar2 = param_2[8];
  fVar6 = param_2[9];
  fVar10 = param_2[10];
  fVar14 = param_2[0xb];
  fVar3 = param_2[4];
  fVar7 = param_2[5];
  fVar18 = param_3[3];
  fVar20 = param_3[7];
  fVar11 = param_2[6];
  fVar15 = param_2[7];
  fVar22 = param_3[0xb];
  fVar24 = param_3[0xf];
  fVar26 = param_3[2];
  fVar28 = param_3[6];
  fVar30 = param_3[10];
  fVar32 = param_3[0xe];
  fVar34 = param_3[1];
  fVar36 = param_3[5];
  fVar38 = param_3[9];
  fVar40 = param_3[0xd];
  fVar42 = *param_3;
  fVar44 = param_3[4];
  fVar46 = param_3[8];
  fVar48 = param_3[0xc];
  fVar4 = *param_2;
  fVar8 = param_2[1];
  fVar12 = param_2[2];
  fVar16 = param_2[3];
  param_1[1] = CONCAT44(fVar4 * fVar18 + fVar8 * fVar20 + fVar12 * fVar22 + fVar16 * fVar24,
                        fVar4 * fVar26 + fVar8 * fVar28 + fVar12 * fVar30 + fVar16 * fVar32);
  *param_1 = CONCAT44(fVar4 * fVar34 + fVar8 * fVar36 + fVar12 * fVar38 + fVar16 * fVar40,
                      fVar4 * fVar42 + fVar8 * fVar44 + fVar12 * fVar46 + fVar16 * fVar48);
  param_1[3] = CONCAT44(fVar3 * fVar18 + fVar7 * fVar20 + fVar11 * fVar22 + fVar15 * fVar24,
                        fVar3 * fVar26 + fVar7 * fVar28 + fVar11 * fVar30 + fVar15 * fVar32);
  param_1[2] = CONCAT44(fVar3 * fVar34 + fVar7 * fVar36 + fVar11 * fVar38 + fVar15 * fVar40,
                        fVar3 * fVar42 + fVar7 * fVar44 + fVar11 * fVar46 + fVar15 * fVar48);
  param_1[5] = CONCAT44(fVar2 * fVar17 + fVar6 * fVar19 + fVar10 * fVar21 + fVar14 * fVar23,
                        fVar2 * fVar25 + fVar6 * fVar27 + fVar10 * fVar29 + fVar14 * fVar31);
  param_1[4] = CONCAT44(fVar2 * fVar33 + fVar6 * fVar35 + fVar10 * fVar37 + fVar14 * fVar39,
                        fVar2 * fVar41 + fVar6 * fVar43 + fVar10 * fVar45 + fVar14 * fVar47);
  param_1[7] = CONCAT44(fVar1 * fVar17 + fVar5 * fVar19 + fVar9 * fVar21 + fVar13 * fVar23,
                        fVar1 * fVar25 + fVar5 * fVar27 + fVar9 * fVar29 + fVar13 * fVar31);
  param_1[6] = CONCAT44(fVar1 * fVar33 + fVar5 * fVar35 + fVar9 * fVar37 + fVar13 * fVar39,
                        fVar1 * fVar41 + fVar5 * fVar43 + fVar9 * fVar45 + fVar13 * fVar47);
  return;
}

// ==== Aska::Matrix::InvertLowError(Aska::Matrix*) const
// vaddr 0x129574c | ghidra 0x139574c | size 884 | symbol _ZNK4Aska6Matrix14InvertLowErrorEPS0_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZNK4Aska6Matrix14InvertLowErrorEPS0_(float *param_1,float *param_2)

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
  
  fVar3 = param_1[4];
  fVar9 = param_1[5];
  fVar5 = *param_1;
  fVar7 = param_1[1];
  fVar10 = param_1[6];
  fVar11 = param_1[7];
  fVar8 = param_1[2];
  fVar12 = param_1[3];
  fVar1 = param_1[0xc];
  fVar6 = param_1[0xd];
  fVar13 = param_1[8];
  fVar15 = param_1[9];
  fVar20 = param_1[0xe];
  fVar17 = param_1[0xf];
  fVar19 = param_1[10];
  fVar21 = param_1[0xb];
  fVar2 = fVar5 * fVar9 - fVar7 * fVar3;
  fVar4 = fVar5 * fVar10 - fVar3 * fVar8;
  fVar5 = fVar5 * fVar11 - fVar3 * fVar12;
  fVar16 = fVar15 * fVar17 - fVar6 * fVar21;
  fVar18 = fVar19 * fVar17 - fVar20 * fVar21;
  fVar3 = fVar7 * fVar10 - fVar9 * fVar8;
  fVar14 = fVar15 * fVar20 - fVar6 * fVar19;
  *param_2 = fVar11 * fVar14 + (fVar9 * fVar18 - fVar10 * fVar16);
  fVar21 = fVar13 * fVar17 - fVar1 * fVar21;
  fVar17 = fVar13 * fVar20 - fVar1 * fVar19;
  param_2[4] = (fVar21 * param_1[6] - param_1[4] * fVar18) - fVar17 * param_1[7];
  fVar8 = fVar8 * fVar11 - fVar10 * fVar12;
  fVar1 = fVar13 * fVar6 - fVar15 * fVar1;
  param_2[8] = (fVar16 * param_1[4] - fVar21 * param_1[5]) + fVar1 * param_1[7];
  fVar6 = fVar7 * fVar11 - fVar9 * fVar12;
  param_2[0xc] = (fVar17 * param_1[5] - fVar14 * param_1[4]) - fVar1 * param_1[6];
  param_2[1] = (fVar16 * param_1[2] - fVar18 * param_1[1]) - fVar14 * param_1[3];
  param_2[5] = (fVar18 * *param_1 - fVar21 * param_1[2]) + fVar17 * param_1[3];
  param_2[9] = (fVar21 * param_1[1] - fVar16 * *param_1) - fVar1 * param_1[3];
  param_2[0xd] = (fVar14 * *param_1 - fVar17 * param_1[1]) + fVar1 * param_1[2];
  fVar9 = (fVar8 * param_1[0xd] - fVar6 * param_1[0xe]) + fVar3 * param_1[0xf];
  param_2[2] = fVar9;
  fVar12 = fVar8 * fVar1 +
           ((fVar3 * fVar21 + fVar5 * fVar14 + (fVar2 * fVar18 - fVar4 * fVar16)) - fVar6 * fVar17);
  fVar10 = (fVar5 * param_1[0xe] - fVar8 * param_1[0xc]) - fVar4 * param_1[0xf];
  param_2[6] = fVar10;
  fVar17 = 1.0 / fVar12;
  fVar11 = (fVar6 * param_1[0xc] - fVar5 * param_1[0xd]) + fVar2 * param_1[0xf];
  param_2[10] = fVar11;
  fVar1 = _UNK_027e519c;
  fVar13 = (fVar4 * param_1[0xd] - fVar3 * param_1[0xc]) - fVar2 * param_1[0xe];
  param_2[0xe] = fVar13;
  fVar21 = (fVar6 * param_1[10] - fVar8 * param_1[9]) - fVar3 * param_1[0xb];
  param_2[3] = fVar21;
  fVar7 = (fVar8 * param_1[8] - fVar5 * param_1[10]) + fVar4 * param_1[0xb];
  param_2[7] = fVar7;
  fVar5 = (fVar5 * param_1[9] - fVar6 * param_1[8]) - fVar2 * param_1[0xb];
  param_2[0xb] = fVar5;
  fVar6 = param_1[8];
  fVar8 = param_1[9];
  fVar14 = param_1[10];
  *param_2 = fVar17 * *param_2;
  param_2[1] = fVar17 * param_2[1];
  param_2[2] = fVar17 * fVar9;
  param_2[3] = fVar17 * fVar21;
  param_2[4] = fVar17 * param_2[4];
  param_2[5] = fVar17 * param_2[5];
  param_2[6] = fVar17 * fVar10;
  param_2[7] = fVar17 * fVar7;
  param_2[8] = fVar17 * param_2[8];
  param_2[9] = fVar17 * param_2[9];
  param_2[10] = fVar17 * fVar11;
  param_2[0xb] = fVar17 * fVar5;
  param_2[0xc] = fVar17 * param_2[0xc];
  param_2[0xd] = fVar17 * param_2[0xd];
  param_2[0xe] = fVar17 * fVar13;
  param_2[0xf] = fVar17 * ((fVar3 * fVar6 - fVar4 * fVar8) + fVar2 * fVar14);
  return fVar1 < ABS(fVar12);
}

// ==== Aska::Matrix::RotateY(float)
// vaddr 0x1e890f4 | ghidra 0x1f890f4 | size 424 | symbol _ZN4Aska6Matrix7RotateYEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix7RotateYEf(float param_1,float *param_2)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  fVar2 = param_1 + (float)(int)(param_1 * _UNK_027ebdf4) * _UNK_027edb30;
  fVar3 = fVar2 * fVar2;
  bVar1 = ((int)(param_1 * _UNK_027ebdf4) & 1U) != 0;
  if (bVar1) {
    fVar2 = -fVar2;
  }
  fVar6 = *param_2;
  fVar7 = param_2[1];
  fVar8 = param_2[2];
  fVar9 = param_2[3];
  fVar4 = fVar3 * (fVar3 * (fVar3 * (fVar3 * (fVar3 * (fVar3 * (fVar3 * _UNK_02964910 +
                                                               _UNK_02964914) + _UNK_02964918) +
                                             _UNK_0296491c) + _UNK_02964920) + _UNK_02964924) + -0.5
                  );
  fVar5 = -1.0 - fVar4;
  if (!bVar1) {
    fVar5 = fVar4 + 1.0;
  }
  fVar2 = fVar2 * (fVar3 * (fVar3 * (fVar3 * (fVar3 * (fVar3 * (fVar3 * (fVar3 * _UNK_02964928 +
                                                                        _UNK_0296492c) +
                                                               _UNK_02964930) + _UNK_02964934) +
                                             _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) + 1.0)
  ;
  *param_2 = fVar5 * fVar6 + fVar2 * param_2[8];
  param_2[1] = fVar5 * fVar7 + fVar2 * param_2[9];
  param_2[2] = fVar5 * fVar8 + fVar2 * param_2[10];
  param_2[3] = fVar5 * fVar9 + fVar2 * param_2[0xb];
  param_2[8] = fVar5 * param_2[8] - fVar6 * fVar2;
  param_2[9] = fVar5 * param_2[9] - fVar7 * fVar2;
  param_2[10] = fVar5 * param_2[10] - fVar8 * fVar2;
  param_2[0xb] = fVar5 * param_2[0xb] - fVar9 * fVar2;
  return;
}

// ==== Aska::Matrix::Invert()
// vaddr 0x1e89480 | ghidra 0x1f89480 | size 856 | symbol _ZN4Aska6Matrix6InvertEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

void _ZN4Aska6Matrix6InvertEv(ulong *param_1)

{
  long lVar1;
  float *pfVar2;
  bool bVar3;
  bool bVar4;
  long lVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  float fVar9;
  ulong uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  undefined8 uStack_10;
  undefined8 uStack_8;
  
  uVar10 = *param_1;
  lVar5 = 0;
  uStack_38 = param_1[1];
  uStack_40 = uVar10;
  uStack_28 = param_1[3];
  uStack_30 = param_1[2];
  uStack_18 = param_1[5];
  uStack_20 = param_1[4];
  uStack_8 = param_1[7];
  uStack_10 = param_1[6];
  do {
    fVar11 = (float)uVar10;
    if ((fVar11 < 0.0) || (fVar9 = _UNK_027fac84, _UNK_027fac84 <= fVar11)) {
      bVar4 = false;
      if ((_UNK_02964944 < fVar11) && (bVar4 = false, !NAN(fVar11))) {
        bVar4 = fVar11 < 0.0;
      }
      fVar9 = _UNK_02964944;
      if (!bVar4) {
        fVar9 = fVar11;
      }
    }
    lVar1 = lVar5 * 0x10;
    pfVar2 = (float *)(&uStack_40 + lVar5 * 2);
    fVar14 = *(float *)((long)&uStack_38 + lVar1 + 4);
    fVar9 = 1.0 / fVar9;
    fVar11 = *pfVar2;
    fVar15 = *(float *)((long)&uStack_40 + lVar1 + 4);
    *(float *)(&uStack_38 + lVar5 * 2) = fVar9 * *(float *)(&uStack_38 + lVar5 * 2);
    *(float *)((long)&uStack_38 + lVar1 + 4) = fVar9 * fVar14;
    pfVar8 = (float *)((ulong)pfVar2 | 0xc);
    pfVar7 = (float *)((ulong)pfVar2 | 8);
    pfVar6 = (float *)((ulong)pfVar2 | 4);
    *pfVar2 = fVar9 * fVar11;
    *(float *)((long)&uStack_40 + lVar1 + 4) = fVar9 * fVar15;
    *(float *)((long)&uStack_40 + lVar5 * 0x14) = fVar9;
    if (lVar5 == 3) {
      fVar12 = fVar9 * uStack_18._4_4_;
      fVar11 = _UNK_027f7cb8;
      fVar14 = uStack_18._4_4_;
      fVar15 = fVar12;
code_r0x01f89624:
      uStack_18 = CONCAT44(fVar11 - fVar15,(float)uStack_18 - fVar14 * *pfVar7);
      if (lVar5 != 1) {
        uStack_20._4_4_ = uStack_20._4_4_ - fVar14 * *pfVar6;
        if (lVar5 != 0) goto code_r0x01f8966c;
        uStack_20 = CONCAT44(uStack_20._4_4_,-fVar12);
code_r0x01f8969c:
        fVar14 = *(float *)((long)&uStack_30 + lVar5 * 4);
        fVar12 = fVar9 * fVar14;
        if (lVar5 == 3) {
          uStack_28._4_4_ = -fVar12;
        }
        else {
          uStack_28._4_4_ = uStack_28._4_4_ - fVar14 * *pfVar8;
        }
        bVar4 = false;
        fVar11 = (float)uStack_28;
        fVar15 = fVar14 * *pfVar7;
        goto code_r0x01f896dc;
      }
      uStack_20._4_4_ = -fVar12;
code_r0x01f8966c:
      uStack_20 = CONCAT44(uStack_20._4_4_,(float)uStack_20 - fVar14 * *pfVar2);
      if (lVar5 != 1) goto code_r0x01f8969c;
      bVar4 = false;
      bVar3 = true;
code_r0x01f89714:
      fVar15 = *(float *)((long)&uStack_40 + lVar5 * 4);
      fVar9 = fVar9 * fVar15;
      fVar11 = _UNK_027f7cb8;
      fVar14 = fVar9;
      if (lVar5 != 3) {
        fVar14 = fVar15 * *pfVar8;
        fVar11 = uStack_38._4_4_;
      }
      fVar12 = _UNK_027f7cb8;
      fVar13 = fVar9;
      if (!bVar4) {
        fVar13 = fVar15 * *pfVar7;
        fVar12 = (float)uStack_38;
      }
      uStack_38 = CONCAT44(fVar11 - fVar14,fVar12 - fVar13);
      fVar11 = _UNK_027f7cb8;
      if (!bVar3) {
        fVar9 = fVar15 * *pfVar6;
        fVar11 = uStack_40._4_4_;
      }
      uStack_40 = CONCAT44(fVar11 - fVar9,(float)uStack_40);
      lVar5 = lVar5 + 1;
      uStack_40 = CONCAT44(fVar11 - fVar9,(float)uStack_40 - fVar15 * *pfVar2);
      if (lVar5 == 4) {
        param_1[1] = uStack_38;
        *param_1 = uStack_40;
        param_1[3] = uStack_28;
        param_1[2] = uStack_30;
        param_1[5] = uStack_18;
        param_1[4] = uStack_20;
        param_1[7] = uStack_8;
        param_1[6] = uStack_10;
        return;
      }
    }
    else {
      fVar11 = *(float *)((long)&uStack_10 + lVar5 * 4);
      fVar14 = fVar9 * fVar11;
      fVar15 = uStack_8._4_4_ - fVar11 * *pfVar8;
      if (lVar5 == 2) {
        uStack_8 = CONCAT44(fVar15,-fVar14);
code_r0x01f895a0:
        uStack_10._4_4_ = uStack_10._4_4_ - fVar11 * *pfVar6;
        if (lVar5 != 0) goto code_r0x01f895b8;
        uStack_10 = CONCAT44(uStack_10._4_4_,-fVar14);
code_r0x01f8960c:
        fVar14 = *(float *)((long)&uStack_20 + lVar5 * 4);
        fVar12 = fVar9 * fVar14;
        fVar15 = fVar14 * *pfVar8;
        fVar11 = uStack_18._4_4_;
        goto code_r0x01f89624;
      }
      uStack_8 = CONCAT44(fVar15,(float)uStack_8 - fVar11 * *pfVar7);
      if (lVar5 != 1) goto code_r0x01f895a0;
      uStack_10._4_4_ = -fVar14;
code_r0x01f895b8:
      uStack_10 = CONCAT44(uStack_10._4_4_,(float)uStack_10 - fVar11 * *pfVar2);
      if (lVar5 != 2) goto code_r0x01f8960c;
      bVar4 = true;
      fVar12 = fVar9 * (float)uStack_28;
      uStack_28._4_4_ = uStack_28._4_4_ - (float)uStack_28 * *pfVar8;
      fVar11 = _UNK_027f7cb8;
      fVar14 = (float)uStack_28;
      fVar15 = fVar12;
code_r0x01f896dc:
      uStack_28 = CONCAT44(uStack_28._4_4_,fVar11 - fVar15);
      fVar11 = uStack_30._4_4_ - fVar14 * *pfVar6;
      uStack_30 = CONCAT44(fVar11,(float)uStack_30);
      if (lVar5 != 0) {
        bVar3 = false;
        uStack_30 = CONCAT44(fVar11,(float)uStack_30 - fVar14 * *pfVar2);
        goto code_r0x01f89714;
      }
      uStack_30 = CONCAT44(fVar11,-fVar12);
      lVar5 = 1;
    }
    uVar10 = (ulong)*(uint *)((long)&uStack_40 + lVar5 * 0x14);
  } while( true );
}

// ==== Aska::Matrix::Create(Aska::Quaternion const*)
// vaddr 0x1f38c08 | ghidra 0x2038c08 | size 188 | symbol _ZN4Aska6Matrix6CreateEPKNS_10QuaternionE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Matrix6CreateEPKNS_10QuaternionE(float *param_1,float *param_2)

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
  
  fVar1 = *param_2;
  fVar2 = param_2[1];
  fVar4 = param_2[2];
  fVar6 = param_2[3];
  fVar7 = fVar1 * fVar2 - fVar4 * fVar6;
  fVar9 = fVar1 * fVar2 + fVar4 * fVar6;
  fVar10 = fVar1 * fVar4 + fVar2 * fVar6;
  fVar3 = fVar1 * fVar4 - fVar2 * fVar6;
  fVar5 = fVar2 * fVar4 - fVar1 * fVar6;
  fVar6 = fVar2 * fVar4 + fVar1 * fVar6;
  fVar8 = fVar1 * fVar1 + fVar4 * fVar4;
  fVar1 = fVar1 * fVar1 + fVar2 * fVar2;
  param_1[8] = fVar3 + fVar3;
  param_1[9] = fVar6 + fVar6;
  param_1[3] = 0.0;
  param_1[7] = 0.0;
  param_1[0xb] = 0.0;
  param_1[0xc] = 0.0;
  param_1[0xd] = 0.0;
  param_1[0xe] = 0.0;
  param_1[1] = fVar7 + fVar7;
  param_1[2] = fVar10 + fVar10;
  param_1[5] = 1.0 - (fVar8 + fVar8);
  param_1[6] = fVar5 + fVar5;
  *param_1 = (fVar2 * fVar2 + fVar4 * fVar4) * -2.0 + 1.0;
  param_1[4] = fVar9 + fVar9;
  param_1[10] = 1.0 - (fVar1 + fVar1);
  param_1[0xf] = 1.0;
  return;
}

// ==== Aska::Matrix::Create(Aska::Quaternion const*, Aska::Vector const*)
// vaddr 0x1f38cc4 | ghidra 0x2038cc4 | size 176 | symbol _ZN4Aska6Matrix6CreateEPKNS_10QuaternionEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix6CreateEPKNS_10QuaternionEPKNS_6VectorE
               (undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined1 auVar8 [16];
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  
  uVar2 = _UNK_027dbb38;
  uVar1 = _UNK_027dbb30;
  uVar7 = param_3[1];
  uVar6 = *param_3;
  auVar8 = NEON_fmov(0x3f800000,4);
  fVar3 = (float)*param_2;
  fVar4 = (float)((ulong)*param_2 >> 0x20);
  fVar5 = (float)param_2[1];
  fVar9 = fVar5 + fVar5;
  fVar10 = (float)((ulong)param_2[1] >> 0x20);
  fVar10 = fVar10 + fVar10;
  fVar11 = (fVar3 + fVar3) * fVar3;
  fVar12 = (fVar4 + fVar4) * fVar3;
  fVar13 = (fVar4 + fVar4) * fVar4;
  param_1[1] = CONCAT44((int)uVar6,fVar9 * fVar3 + fVar10 * fVar4);
  *param_1 = CONCAT44(fVar12 - fVar10 * fVar5,(auVar8._0_4_ - fVar13) - fVar9 * fVar5);
  param_1[3] = CONCAT44((int)((ulong)uVar6 >> 0x20),fVar9 * fVar4 - fVar10 * fVar3);
  param_1[2] = CONCAT44((auVar8._4_4_ - fVar11) - fVar9 * fVar5,fVar12 + fVar10 * fVar5);
  param_1[5] = CONCAT44((int)uVar7,(auVar8._8_4_ - fVar11) - fVar13);
  param_1[4] = CONCAT44(fVar9 * fVar4 + fVar10 * fVar3,fVar9 * fVar3 - fVar10 * fVar4);
  param_1[7] = uVar2;
  param_1[6] = uVar1;
  return;
}

// ==== Aska::Matrix::CreateWithoutNormalize(Aska::Quaternion const*)
// vaddr 0x1f38d74 | ghidra 0x2038d74 | size 184 | symbol _ZN4Aska6Matrix22CreateWithoutNormalizeEPKNS_10QuaternionE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Matrix22CreateWithoutNormalizeEPKNS_10QuaternionE(float *param_1,float *param_2)

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
  
  fVar1 = *param_2;
  fVar3 = param_2[1];
  fVar5 = param_2[2];
  fVar7 = param_2[3];
  param_1[3] = 0.0;
  param_1[7] = 0.0;
  fVar10 = fVar3 * fVar3;
  fVar11 = fVar5 * fVar5;
  fVar6 = fVar1 * fVar1 + fVar7 * fVar7;
  fVar8 = fVar1 * fVar3 - fVar5 * fVar7;
  fVar12 = fVar1 * fVar3 + fVar5 * fVar7;
  fVar13 = fVar1 * fVar5 + fVar3 * fVar7;
  fVar9 = fVar7 * fVar7 - fVar1 * fVar1;
  fVar2 = fVar1 * fVar5 - fVar3 * fVar7;
  fVar4 = fVar3 * fVar5 + fVar1 * fVar7;
  fVar1 = fVar3 * fVar5 - fVar1 * fVar7;
  param_1[1] = fVar8 + fVar8;
  param_1[2] = fVar13 + fVar13;
  param_1[8] = fVar2 + fVar2;
  param_1[9] = fVar4 + fVar4;
  param_1[0xb] = 0.0;
  param_1[0xc] = 0.0;
  param_1[0xd] = 0.0;
  param_1[0xe] = 0.0;
  param_1[5] = (fVar10 + fVar9) - fVar11;
  param_1[6] = fVar1 + fVar1;
  *param_1 = (fVar6 - fVar10) - fVar11;
  param_1[4] = fVar12 + fVar12;
  param_1[10] = fVar11 + (fVar9 - fVar10);
  param_1[0xf] = fVar11 + fVar10 + fVar6;
  return;
}

// ==== Aska::Matrix::CreateWithoutNormalize(Aska::Quaternion const*, Aska::Vector const*)
// vaddr 0x1f38e2c | ghidra 0x2038e2c | size 196 | symbol _ZN4Aska6Matrix22CreateWithoutNormalizeEPKNS_10QuaternionEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Matrix22CreateWithoutNormalizeEPKNS_10QuaternionEPKNS_6VectorE
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
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  
  fVar1 = *param_2;
  fVar3 = param_2[1];
  fVar4 = param_2[2];
  fVar6 = param_2[3];
  fVar9 = fVar3 * fVar3;
  fVar10 = fVar4 * fVar4;
  fVar5 = fVar1 * fVar1 + fVar6 * fVar6;
  fVar7 = fVar1 * fVar3 - fVar4 * fVar6;
  fVar12 = fVar1 * fVar3 + fVar4 * fVar6;
  fVar13 = fVar1 * fVar4 + fVar3 * fVar6;
  fVar8 = fVar6 * fVar6 - fVar1 * fVar1;
  fVar11 = fVar3 * fVar4 - fVar1 * fVar6;
  fVar2 = fVar1 * fVar4 - fVar3 * fVar6;
  fVar3 = fVar3 * fVar4 + fVar1 * fVar6;
  param_1[1] = fVar7 + fVar7;
  param_1[2] = fVar13 + fVar13;
  *param_1 = (fVar5 - fVar9) - fVar10;
  fVar1 = *param_3;
  param_1[4] = fVar12 + fVar12;
  param_1[5] = (fVar9 + fVar8) - fVar10;
  param_1[6] = fVar11 + fVar11;
  param_1[3] = fVar1;
  fVar1 = param_3[1];
  param_1[8] = fVar2 + fVar2;
  param_1[9] = fVar3 + fVar3;
  param_1[10] = fVar10 + (fVar8 - fVar9);
  param_1[7] = fVar1;
  fVar1 = param_3[2];
  param_1[0xd] = 0.0;
  param_1[0xe] = 0.0;
  param_1[0xb] = fVar1;
  param_1[0xc] = 0.0;
  param_1[0xf] = fVar10 + fVar9 + fVar5;
  return;
}

// ==== Aska::Matrix::CreateWithNormalize(Aska::Quaternion const*)
// vaddr 0x1f38ef0 | ghidra 0x2038ef0 | size 284 | symbol _ZN4Aska6Matrix19CreateWithNormalizeEPKNS_10QuaternionE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Matrix19CreateWithNormalizeEPKNS_10QuaternionE(float *param_1,float *param_2)

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
  
  fVar4 = *param_2;
  fVar5 = param_2[1];
  fVar6 = param_2[2];
  fVar7 = param_2[3];
  fVar2 = fVar4 * fVar4 + fVar5 * fVar5 + fVar6 * fVar6 + fVar7 * fVar7;
  fVar1 = SQRT(fVar2);
  if (NAN(fVar1)) {
    fVar1 = (float)sqrtf(fVar2);
  }
  fVar1 = 1.0 / fVar1;
  fVar4 = fVar4 * fVar1;
  fVar5 = fVar5 * fVar1;
  fVar6 = fVar6 * fVar1;
  fVar7 = fVar7 * fVar1;
  fVar2 = fVar4 * fVar5 - fVar7 * fVar6;
  fVar9 = fVar4 * fVar5 + fVar7 * fVar6;
  fVar10 = fVar4 * fVar6 + fVar7 * fVar5;
  fVar1 = fVar4 * fVar6 - fVar7 * fVar5;
  fVar3 = fVar5 * fVar6 - fVar7 * fVar4;
  fVar7 = fVar5 * fVar6 + fVar7 * fVar4;
  fVar8 = fVar4 * fVar4 + fVar6 * fVar6;
  fVar4 = fVar4 * fVar4 + fVar5 * fVar5;
  param_1[1] = fVar2 + fVar2;
  param_1[2] = fVar10 + fVar10;
  param_1[8] = fVar1 + fVar1;
  param_1[9] = fVar7 + fVar7;
  param_1[3] = 0.0;
  param_1[7] = 0.0;
  param_1[0xb] = 0.0;
  param_1[0xc] = 0.0;
  param_1[0xd] = 0.0;
  param_1[0xe] = 0.0;
  param_1[5] = 1.0 - (fVar8 + fVar8);
  param_1[6] = fVar3 + fVar3;
  *param_1 = (fVar5 * fVar5 + fVar6 * fVar6) * -2.0 + 1.0;
  param_1[4] = fVar9 + fVar9;
  param_1[10] = 1.0 - (fVar4 + fVar4);
  param_1[0xf] = 1.0;
  return;
}

// ==== Aska::Matrix::CreateWithNormalize(Aska::Quaternion const*, Aska::Vector const*)
// vaddr 0x1f3900c | ghidra 0x203900c | size 308 | symbol _ZN4Aska6Matrix19CreateWithNormalizeEPKNS_10QuaternionEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix19CreateWithNormalizeEPKNS_10QuaternionEPKNS_6VectorE
               (float *param_1,float *param_2,float *param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  
  fVar5 = *param_2;
  fVar6 = param_2[1];
  fVar7 = param_2[2];
  fVar8 = param_2[3];
  fVar4 = fVar5 * fVar5 + fVar6 * fVar6 + fVar7 * fVar7 + fVar8 * fVar8;
  fVar3 = SQRT(fVar4);
  if (NAN(fVar3)) {
    fVar3 = (float)sqrtf(fVar4);
  }
  fVar3 = 1.0 / fVar3;
  fVar5 = fVar5 * fVar3;
  fVar6 = fVar6 * fVar3;
  fVar7 = fVar7 * fVar3;
  fVar8 = fVar8 * fVar3;
  fVar3 = fVar5 * fVar6 - fVar8 * fVar7;
  fVar9 = fVar5 * fVar6 + fVar8 * fVar7;
  fVar4 = fVar5 * fVar7 + fVar8 * fVar6;
  param_1[2] = fVar4 + fVar4;
  *param_1 = (fVar6 * fVar6 + fVar7 * fVar7) * -2.0 + 1.0;
  param_1[1] = fVar3 + fVar3;
  fVar3 = *param_3;
  fVar4 = fVar5 * fVar5 + fVar7 * fVar7;
  fVar10 = fVar6 * fVar7 - fVar8 * fVar5;
  param_1[4] = fVar9 + fVar9;
  param_1[5] = 1.0 - (fVar4 + fVar4);
  param_1[6] = fVar10 + fVar10;
  param_1[3] = fVar3;
  fVar4 = fVar6 * fVar7 + fVar8 * fVar5;
  fVar9 = fVar5 * fVar5 + fVar6 * fVar6;
  fVar3 = fVar5 * fVar7 - fVar8 * fVar6;
  param_1[7] = param_3[1];
  param_1[8] = fVar3 + fVar3;
  param_1[9] = fVar4 + fVar4;
  param_1[10] = 1.0 - (fVar9 + fVar9);
  uVar2 = _UNK_027dbb38;
  uVar1 = _UNK_027dbb30;
  param_1[0xb] = param_3[2];
  *(undefined8 *)(param_1 + 0xe) = uVar2;
  *(undefined8 *)(param_1 + 0xc) = uVar1;
  return;
}

// ==== Aska::Matrix::Mul(Aska::Matrix const*)
// vaddr 0x1f39140 | ghidra 0x2039140 | size 140 | symbol _ZN4Aska6Matrix3MulEPKS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Matrix3MulEPKS0_(undefined8 *param_1,undefined8 *param_2)

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
  
  fVar1 = (float)*param_1;
  fVar17 = (float)*param_2;
  fVar18 = (float)((ulong)*param_2 >> 0x20);
  fVar19 = (float)param_2[1];
  fVar20 = (float)((ulong)param_2[1] >> 0x20);
  fVar2 = (float)((ulong)*param_1 >> 0x20);
  fVar21 = (float)param_2[2];
  fVar22 = (float)((ulong)param_2[2] >> 0x20);
  fVar23 = (float)param_2[3];
  fVar24 = (float)((ulong)param_2[3] >> 0x20);
  fVar5 = (float)param_1[2];
  fVar6 = (float)((ulong)param_1[2] >> 0x20);
  fVar9 = (float)param_1[4];
  fVar10 = (float)((ulong)param_1[4] >> 0x20);
  fVar13 = (float)param_1[6];
  fVar14 = (float)((ulong)param_1[6] >> 0x20);
  fVar3 = (float)param_1[1];
  fVar25 = (float)param_2[4];
  fVar26 = (float)((ulong)param_2[4] >> 0x20);
  fVar27 = (float)param_2[5];
  fVar28 = (float)((ulong)param_2[5] >> 0x20);
  fVar4 = (float)((ulong)param_1[1] >> 0x20);
  fVar29 = (float)param_2[6];
  fVar30 = (float)((ulong)param_2[6] >> 0x20);
  fVar31 = (float)param_2[7];
  fVar32 = (float)((ulong)param_2[7] >> 0x20);
  fVar7 = (float)param_1[3];
  fVar8 = (float)((ulong)param_1[3] >> 0x20);
  fVar11 = (float)param_1[5];
  fVar12 = (float)((ulong)param_1[5] >> 0x20);
  fVar15 = (float)param_1[7];
  fVar16 = (float)((ulong)param_1[7] >> 0x20);
  param_1[1] = CONCAT44(fVar20 * fVar1 + fVar24 * fVar2 + fVar28 * fVar3 + fVar32 * fVar4,
                        fVar19 * fVar1 + fVar23 * fVar2 + fVar27 * fVar3 + fVar31 * fVar4);
  *param_1 = CONCAT44(fVar18 * fVar1 + fVar22 * fVar2 + fVar26 * fVar3 + fVar30 * fVar4,
                      fVar17 * fVar1 + fVar21 * fVar2 + fVar25 * fVar3 + fVar29 * fVar4);
  param_1[3] = CONCAT44(fVar32 * fVar8 + fVar28 * fVar7 + fVar20 * fVar5 + fVar24 * fVar6,
                        fVar31 * fVar8 + fVar27 * fVar7 + fVar19 * fVar5 + fVar23 * fVar6);
  param_1[2] = CONCAT44(fVar30 * fVar8 + fVar26 * fVar7 + fVar18 * fVar5 + fVar22 * fVar6,
                        fVar29 * fVar8 + fVar25 * fVar7 + fVar17 * fVar5 + fVar21 * fVar6);
  param_1[5] = CONCAT44(fVar32 * fVar12 + fVar28 * fVar11 + fVar20 * fVar9 + fVar24 * fVar10,
                        fVar31 * fVar12 + fVar27 * fVar11 + fVar19 * fVar9 + fVar23 * fVar10);
  param_1[4] = CONCAT44(fVar30 * fVar12 + fVar26 * fVar11 + fVar18 * fVar9 + fVar22 * fVar10,
                        fVar29 * fVar12 + fVar25 * fVar11 + fVar17 * fVar9 + fVar21 * fVar10);
  param_1[7] = CONCAT44(fVar32 * fVar16 + fVar28 * fVar15 + fVar20 * fVar13 + fVar24 * fVar14,
                        fVar31 * fVar16 + fVar27 * fVar15 + fVar19 * fVar13 + fVar23 * fVar14);
  param_1[6] = CONCAT44(fVar30 * fVar16 + fVar26 * fVar15 + fVar18 * fVar13 + fVar22 * fVar14,
                        fVar29 * fVar16 + fVar25 * fVar15 + fVar17 * fVar13 + fVar21 * fVar14);
  return;
}

// ==== Aska::Matrix::MulFromLeft(Aska::Matrix const*)
// vaddr 0x1f391cc | ghidra 0x20391cc | size 700 | symbol _ZN4Aska6Matrix11MulFromLeftEPKS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Matrix11MulFromLeftEPKS0_(float *param_1,float *param_2)

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
  
  fVar1 = param_2[0xc];
  fVar5 = param_2[0xd];
  fVar9 = param_2[0xe];
  fVar13 = param_2[0xf];
  fVar17 = param_1[2];
  fVar19 = param_1[6];
  fVar20 = param_1[10];
  fVar21 = *param_1;
  fVar23 = param_1[4];
  fVar24 = param_1[8];
  fVar2 = param_2[8];
  fVar6 = param_2[9];
  fVar10 = param_2[10];
  fVar14 = param_2[0xb];
  fVar3 = param_2[4];
  fVar7 = param_2[5];
  fVar11 = param_2[6];
  fVar15 = param_2[7];
  fVar18 = param_1[2];
  fVar22 = *param_1;
  fVar4 = *param_2;
  fVar8 = param_2[1];
  fVar12 = param_2[2];
  fVar16 = param_2[3];
  *(ulong *)(param_1 + 2) =
       CONCAT44(fVar4 * param_1[3] + fVar8 * param_1[7] + fVar12 * param_1[0xb] +
                fVar16 * param_1[0xf],
                fVar4 * fVar18 + fVar8 * param_1[6] + fVar12 * param_1[10] + fVar16 * param_1[0xe]);
  *(ulong *)param_1 =
       CONCAT44(fVar4 * param_1[1] + fVar8 * param_1[5] + fVar12 * param_1[9] +
                fVar16 * param_1[0xd],
                fVar4 * fVar22 + fVar8 * param_1[4] + fVar12 * param_1[8] + fVar16 * param_1[0xc]);
  *(ulong *)(param_1 + 6) =
       CONCAT44(fVar3 * param_1[3] + fVar7 * param_1[7] + fVar11 * param_1[0xb] +
                fVar15 * param_1[0xf],
                fVar3 * fVar18 + fVar7 * param_1[6] + fVar11 * param_1[10] + fVar15 * param_1[0xe]);
  *(ulong *)(param_1 + 4) =
       CONCAT44(fVar3 * param_1[1] + fVar7 * param_1[5] + fVar11 * param_1[9] +
                fVar15 * param_1[0xd],
                fVar3 * fVar22 + fVar7 * param_1[4] + fVar11 * param_1[8] + fVar15 * param_1[0xc]);
  *(ulong *)(param_1 + 10) =
       CONCAT44(fVar2 * param_1[3] + fVar6 * param_1[7] + fVar10 * param_1[0xb] +
                fVar14 * param_1[0xf],
                fVar2 * fVar17 + fVar6 * fVar19 + fVar10 * fVar20 + fVar14 * param_1[0xe]);
  *(ulong *)(param_1 + 8) =
       CONCAT44(fVar2 * param_1[1] + fVar6 * param_1[5] + fVar10 * param_1[9] +
                fVar14 * param_1[0xd],
                fVar2 * fVar21 + fVar6 * fVar23 + fVar10 * fVar24 + fVar14 * param_1[0xc]);
  *(ulong *)(param_1 + 0xe) =
       CONCAT44(fVar1 * param_1[3] + fVar5 * param_1[7] + fVar9 * param_1[0xb] +
                fVar13 * param_1[0xf],
                fVar1 * fVar17 + fVar5 * fVar19 + fVar9 * fVar20 + fVar13 * param_1[0xe]);
  *(ulong *)(param_1 + 0xc) =
       CONCAT44(fVar1 * param_1[1] + fVar5 * param_1[5] + fVar9 * param_1[9] + fVar13 * param_1[0xd]
                ,fVar1 * fVar21 + fVar5 * fVar23 + fVar9 * fVar24 + fVar13 * param_1[0xc]);
  return;
}

// ==== Aska::Matrix::SetRotation(Aska::Vector const*, EnumRotateType)
// vaddr 0x1f39488 | ghidra 0x2039488 | size 1228 | symbol _ZN4Aska6Matrix11SetRotationEPKNS_6VectorE14EnumRotateType | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix11SetRotationEPKNS_6VectorE14EnumRotateType
               (float *param_1,float *param_2,undefined4 param_3)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
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
  
  uVar2 = (uint)(*param_2 * _UNK_027ebdf4);
  uVar4 = (uint)(param_2[1] * _UNK_027ebdf4);
  bVar1 = (uVar2 & 1) != 0;
  uVar3 = (uint)(param_2[2] * _UNK_027ebdf4);
  fVar5 = *param_2 - (float)(int)uVar2 * _UNK_027e3fd0;
  fVar7 = param_2[1] - (float)(int)uVar4 * _UNK_027e3fd0;
  fVar10 = param_2[2] - (float)(int)uVar3 * _UNK_027e3fd0;
  fVar11 = fVar5 * fVar5;
  fVar14 = fVar7 * fVar7;
  fVar15 = fVar10 * fVar10;
  if (bVar1) {
    fVar5 = -fVar5;
  }
  fVar9 = fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (_UNK_02964914 -
                                                                     fVar11 * _UNK_02970cbc) +
                                                           _UNK_02964918) + _UNK_0296491c) +
                                       _UNK_02964920) + _UNK_02964924) + -0.5);
  fVar12 = fVar14 * (fVar14 * (fVar14 * (fVar14 * (fVar14 * (fVar14 * (_UNK_02964914 -
                                                                      fVar14 * _UNK_02970cbc) +
                                                            _UNK_02964918) + _UNK_0296491c) +
                                        _UNK_02964920) + _UNK_02964924) + -0.5);
  fVar8 = fVar15 * (fVar15 * (fVar15 * (fVar15 * (fVar15 * (fVar15 * (_UNK_02964914 -
                                                                     fVar15 * _UNK_02970cbc) +
                                                           _UNK_02964918) + _UNK_0296491c) +
                                       _UNK_02964920) + _UNK_02964924) + -0.5);
  fVar13 = fVar12 + 1.0;
  fVar6 = -1.0 - fVar9;
  if (!bVar1) {
    fVar6 = fVar9 + 1.0;
  }
  fVar9 = fVar8 + 1.0;
  if ((uVar4 & 1) != 0) {
    fVar7 = -fVar7;
    fVar13 = -1.0 - fVar12;
  }
  fVar7 = fVar7 * (fVar14 * (fVar14 * (fVar14 * (fVar14 * (fVar14 * (fVar14 * (_UNK_0296492c -
                                                                              fVar14 * _UNK_02970cc0
                                                                              ) + _UNK_02964930) +
                                                          _UNK_02964934) + _UNK_02964938) +
                                      _UNK_0296493c) + _UNK_02964940) + 1.0);
  if ((uVar3 & 1) != 0) {
    fVar10 = -fVar10;
    fVar9 = -1.0 - fVar8;
  }
  fVar5 = fVar5 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (_UNK_0296492c -
                                                                              fVar11 * _UNK_02970cc0
                                                                              ) + _UNK_02964930) +
                                                          _UNK_02964934) + _UNK_02964938) +
                                      _UNK_0296493c) + _UNK_02964940) + 1.0);
  fVar10 = fVar10 * (fVar15 * (fVar15 * (fVar15 * (fVar15 * (fVar15 * (fVar15 * (_UNK_0296492c -
                                                                                fVar15 * 
                                                  _UNK_02970cc0) + _UNK_02964930) + _UNK_02964934) +
                                                  _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) +
                    1.0);
  switch(param_3) {
  case 1:
    param_1[4] = fVar10;
    param_1[5] = fVar6 * fVar9;
    param_1[6] = -(fVar5 * fVar9);
    *param_1 = fVar13 * fVar9;
    param_1[1] = fVar5 * fVar7 - fVar6 * fVar13 * fVar10;
    param_1[8] = -(fVar7 * fVar9);
    param_1[9] = fVar5 * fVar13 + fVar6 * fVar7 * fVar10;
    param_1[2] = fVar6 * fVar7 + fVar5 * fVar13 * fVar10;
    param_1[10] = fVar6 * fVar13 - fVar5 * fVar7 * fVar10;
    return;
  case 2:
    *param_1 = fVar13 * fVar9;
    param_1[1] = -fVar10;
    param_1[2] = fVar7 * fVar9;
    param_1[4] = fVar5 * fVar7 + fVar6 * fVar13 * fVar10;
    param_1[5] = fVar6 * fVar9;
    param_1[8] = fVar5 * fVar13 * fVar10 - fVar6 * fVar7;
    param_1[9] = fVar5 * fVar9;
    param_1[6] = fVar6 * fVar7 * fVar10 - fVar5 * fVar13;
    param_1[10] = fVar6 * fVar13 + fVar5 * fVar7 * fVar10;
    return;
  case 3:
    param_1[8] = fVar7 * -fVar6;
    param_1[9] = fVar5;
    *param_1 = fVar13 * fVar9 - fVar5 * fVar7 * fVar10;
    param_1[1] = fVar10 * -fVar6;
    param_1[4] = fVar13 * fVar10 + fVar5 * fVar7 * fVar9;
    param_1[5] = fVar6 * fVar9;
    param_1[2] = fVar7 * fVar9 + fVar5 * fVar13 * fVar10;
    param_1[6] = fVar7 * fVar10 - fVar5 * fVar13 * fVar9;
    break;
  case 4:
    param_1[4] = fVar6 * fVar10;
    param_1[5] = fVar6 * fVar9;
    param_1[2] = fVar6 * fVar7;
    param_1[6] = -fVar5;
    *param_1 = fVar13 * fVar9 + fVar5 * fVar7 * fVar10;
    param_1[1] = fVar5 * fVar7 * fVar9 - fVar13 * fVar10;
    param_1[8] = fVar5 * fVar13 * fVar10 - fVar7 * fVar9;
    param_1[9] = fVar7 * fVar10 + fVar5 * fVar13 * fVar9;
    break;
  case 5:
    param_1[2] = fVar7;
    *param_1 = fVar13 * fVar9;
    param_1[1] = -(fVar13 * fVar10);
    param_1[6] = -(fVar5 * fVar13);
    param_1[4] = fVar6 * fVar10 + fVar5 * fVar7 * fVar9;
    param_1[5] = fVar6 * fVar9 - fVar5 * fVar7 * fVar10;
    param_1[8] = fVar5 * fVar10 - fVar6 * fVar7 * fVar9;
    param_1[9] = fVar5 * fVar9 + fVar6 * fVar7 * fVar10;
    break;
  default:
    param_1[8] = -fVar7;
    param_1[9] = fVar5 * fVar13;
    *param_1 = fVar13 * fVar9;
    param_1[1] = fVar5 * fVar7 * fVar9 - fVar6 * fVar10;
    param_1[4] = fVar13 * fVar10;
    param_1[5] = fVar6 * fVar9 + fVar5 * fVar7 * fVar10;
    param_1[2] = fVar5 * fVar10 + fVar6 * fVar7 * fVar9;
    param_1[6] = fVar6 * fVar7 * fVar10 - fVar5 * fVar9;
  }
  param_1[10] = fVar6 * fVar13;
  return;
}

// ==== Aska::Matrix::Rotate(Aska::Quaternion const*)
// vaddr 0x1f39954 | ghidra 0x2039954 | size 212 | symbol _ZN4Aska6Matrix6RotateEPKNS_10QuaternionE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Matrix6RotateEPKNS_10QuaternionE(undefined8 param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  undefined4 uStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  undefined4 uStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  undefined8 uStack_24;
  undefined8 uStack_1c;
  undefined4 uStack_14;
  
  fVar1 = *param_2;
  fVar2 = param_2[1];
  fVar3 = param_2[2];
  fVar4 = param_2[3];
  fStack_4c = fVar1 * fVar2 - fVar3 * fVar4;
  fStack_40 = fVar1 * fVar2 + fVar3 * fVar4;
  fStack_48 = fVar1 * fVar3 + fVar2 * fVar4;
  fStack_30 = fVar1 * fVar3 - fVar2 * fVar4;
  fStack_38 = fVar2 * fVar3 - fVar1 * fVar4;
  fStack_2c = fVar2 * fVar3 + fVar1 * fVar4;
  fVar4 = fVar1 * fVar1 + fVar3 * fVar3;
  fVar1 = fVar1 * fVar1 + fVar2 * fVar2;
  fStack_4c = fStack_4c + fStack_4c;
  fStack_48 = fStack_48 + fStack_48;
  fStack_40 = fStack_40 + fStack_40;
  fStack_38 = fStack_38 + fStack_38;
  fStack_30 = fStack_30 + fStack_30;
  fStack_2c = fStack_2c + fStack_2c;
  fStack_50 = (fVar2 * fVar2 + fVar3 * fVar3) * -2.0 + 1.0;
  fStack_3c = 1.0 - (fVar4 + fVar4);
  fStack_28 = 1.0 - (fVar1 + fVar1);
  uStack_44 = 0;
  uStack_34 = 0;
  uStack_24 = 0;
  uStack_1c = 0;
  uStack_14 = 0x3f800000;
  Aska::Matrix::MulFromLeft(Aska::Matrix const*)(param_1,&fStack_50);
  return;
}

// ==== Aska::Matrix::SetRotationByUnitVector(Aska::Vector const*)
// vaddr 0x1f39a28 | ghidra 0x2039a28 | size 440 | symbol _ZN4Aska6Matrix23SetRotationByUnitVectorEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix23SetRotationByUnitVectorEPKNS_6VectorE(float *param_1,float *param_2)

{
  bool bVar1;
  uint uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  
  fVar3 = param_2[2];
  uVar2 = (uint)(param_2[3] * _UNK_027ebdf4);
  fVar4 = param_2[3] + (float)(int)uVar2 * _UNK_027edb30;
  bVar1 = (uVar2 & 1) != 0;
  fVar5 = fVar4;
  if (bVar1) {
    fVar5 = -fVar4;
  }
  fVar4 = fVar4 * fVar4;
  fVar6 = *param_2;
  fVar7 = param_2[1];
  fVar8 = fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * _UNK_02964910 +
                                                               _UNK_02964914) + _UNK_02964918) +
                                             _UNK_0296491c) + _UNK_02964920) + _UNK_02964924) + -0.5
                  );
  fVar9 = -1.0 - fVar8;
  if (!bVar1) {
    fVar9 = fVar8 + 1.0;
  }
  fVar5 = fVar5 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * _UNK_02964928 +
                                                                        _UNK_0296492c) +
                                                               _UNK_02964930) + _UNK_02964934) +
                                             _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) + 1.0)
  ;
  fVar4 = 1.0 - fVar9;
  fVar8 = fVar6 * fVar7 * fVar4;
  fVar10 = fVar6 * fVar3 * fVar4;
  fVar4 = fVar7 * fVar3 * fVar4;
  *param_1 = fVar6 * fVar6 + (1.0 - fVar6 * fVar6) * fVar9;
  param_1[1] = fVar8 - fVar3 * fVar5;
  param_1[2] = fVar7 * fVar5 + fVar10;
  param_1[4] = fVar3 * fVar5 + fVar8;
  param_1[5] = fVar7 * fVar7 + (1.0 - fVar7 * fVar7) * fVar9;
  param_1[6] = fVar4 - fVar6 * fVar5;
  param_1[8] = fVar10 - fVar7 * fVar5;
  param_1[9] = fVar6 * fVar5 + fVar4;
  param_1[10] = fVar3 * fVar3 + (1.0 - fVar3 * fVar3) * fVar9;
  return;
}

// ==== Aska::Matrix::Rotate(Aska::Vector const*, EnumRotateType)
// vaddr 0x1f39be0 | ghidra 0x2039be0 | size 2520 | symbol _ZN4Aska6Matrix6RotateEPKNS_6VectorE14EnumRotateType | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix6RotateEPKNS_6VectorE14EnumRotateType
               (float *param_1,float *param_2,undefined4 param_3)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
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
  
  uVar3 = (uint)(*param_2 * _UNK_027ebdf4);
  uVar2 = (uint)(param_2[1] * _UNK_027ebdf4);
  bVar1 = (uVar3 & 1) != 0;
  uVar4 = (uint)(param_2[2] * _UNK_027ebdf4);
  fVar5 = *param_2 - (float)(int)uVar3 * _UNK_027e3fd0;
  fVar22 = param_2[1] - (float)(int)uVar2 * _UNK_027e3fd0;
  fVar21 = param_2[2] - (float)(int)uVar4 * _UNK_027e3fd0;
  fVar29 = fVar5 * fVar5;
  fVar14 = fVar22 * fVar22;
  fVar15 = fVar21 * fVar21;
  if (bVar1) {
    fVar5 = -fVar5;
  }
  fVar24 = fVar29 * (fVar29 * (fVar29 * (fVar29 * (fVar29 * (fVar29 * (_UNK_02964914 -
                                                                      fVar29 * _UNK_02970cbc) +
                                                            _UNK_02964918) + _UNK_0296491c) +
                                        _UNK_02964920) + _UNK_02964924) + -0.5);
  fVar25 = fVar14 * (fVar14 * (fVar14 * (fVar14 * (fVar14 * (fVar14 * (_UNK_02964914 -
                                                                      fVar14 * _UNK_02970cbc) +
                                                            _UNK_02964918) + _UNK_0296491c) +
                                        _UNK_02964920) + _UNK_02964924) + -0.5);
  fVar11 = fVar15 * (fVar15 * (fVar15 * (fVar15 * (fVar15 * (fVar15 * (_UNK_02964914 -
                                                                      fVar15 * _UNK_02970cbc) +
                                                            _UNK_02964918) + _UNK_0296491c) +
                                        _UNK_02964920) + _UNK_02964924) + -0.5);
  fVar17 = *param_1;
  fVar13 = param_1[1];
  fVar12 = param_1[2];
  fVar6 = param_1[3];
  fVar20 = param_1[4];
  fVar19 = param_1[5];
  fVar10 = param_1[6];
  fVar7 = param_1[7];
  fVar18 = param_1[8];
  fVar16 = param_1[9];
  fVar26 = fVar25 + 1.0;
  fVar9 = param_1[10];
  fVar8 = param_1[0xb];
  fVar23 = -1.0 - fVar24;
  if (!bVar1) {
    fVar23 = fVar24 + 1.0;
  }
  fVar5 = fVar5 * (fVar29 * (fVar29 * (fVar29 * (fVar29 * (fVar29 * (fVar29 * (_UNK_0296492c -
                                                                              fVar29 * _UNK_02970cc0
                                                                              ) + _UNK_02964930) +
                                                          _UNK_02964934) + _UNK_02964938) +
                                      _UNK_0296493c) + _UNK_02964940) + 1.0);
  if ((uVar2 & 1) != 0) {
    fVar22 = -fVar22;
    fVar26 = -1.0 - fVar25;
  }
  bVar1 = (uVar4 & 1) != 0;
  if (bVar1) {
    fVar21 = -fVar21;
  }
  fVar22 = fVar22 * (fVar14 * (fVar14 * (fVar14 * (fVar14 * (fVar14 * (fVar14 * (_UNK_0296492c -
                                                                                fVar14 * 
                                                  _UNK_02970cc0) + _UNK_02964930) + _UNK_02964934) +
                                                  _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) +
                    1.0);
  fVar14 = -1.0 - fVar11;
  if (!bVar1) {
    fVar14 = fVar11 + 1.0;
  }
  fVar21 = fVar21 * (fVar15 * (fVar15 * (fVar15 * (fVar15 * (fVar15 * (fVar15 * (_UNK_0296492c -
                                                                                fVar15 * 
                                                  _UNK_02970cc0) + _UNK_02964930) + _UNK_02964934) +
                                                  _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) +
                    1.0);
  switch(param_3) {
  case 1:
    fVar30 = fVar23 * fVar14;
    fVar25 = -(fVar22 * fVar14);
    fVar28 = fVar26 * fVar14;
    fVar29 = fVar5 * fVar14;
    fVar11 = fVar23 * fVar22 + fVar5 * fVar26 * fVar21;
    fVar27 = fVar5 * fVar22 - fVar23 * fVar26 * fVar21;
    fVar24 = fVar23 * fVar26 - fVar5 * fVar22 * fVar21;
    fVar5 = fVar5 * fVar26 + fVar23 * fVar22 * fVar21;
    param_1[6] = (fVar12 * fVar21 + fVar10 * fVar30) - fVar9 * fVar29;
    param_1[7] = (fVar6 * fVar21 + fVar7 * fVar30) - fVar8 * fVar29;
    fVar15 = fVar12 * fVar25;
    param_1[4] = (fVar17 * fVar21 + fVar20 * fVar30) - fVar18 * fVar29;
    param_1[5] = (fVar13 * fVar21 + fVar19 * fVar30) - fVar16 * fVar29;
    *param_1 = fVar18 * fVar11 + fVar17 * fVar28 + fVar20 * fVar27;
    param_1[1] = fVar16 * fVar11 + fVar13 * fVar28 + fVar19 * fVar27;
    param_1[2] = fVar9 * fVar11 + fVar12 * fVar28 + fVar10 * fVar27;
    param_1[3] = fVar8 * fVar11 + fVar6 * fVar28 + fVar7 * fVar27;
    param_1[8] = fVar18 * fVar24 + (fVar20 * fVar5 - fVar17 * fVar22 * fVar14);
    param_1[9] = fVar16 * fVar24 + (fVar19 * fVar5 - fVar13 * fVar22 * fVar14);
    break;
  case 2:
    fVar27 = fVar26 * fVar14;
    fVar30 = fVar22 * fVar14;
    fVar15 = fVar5 * fVar22;
    fVar29 = fVar23 * fVar14;
    fVar11 = fVar5 * fVar26;
    fVar5 = fVar5 * fVar14;
    fVar28 = fVar15 + fVar23 * fVar26 * fVar21;
    fVar14 = fVar23 * fVar22 * fVar21 - fVar11;
    fVar25 = fVar11 * fVar21 - fVar23 * fVar22;
    fVar24 = fVar23 * fVar26 + fVar15 * fVar21;
    param_1[2] = fVar9 * fVar30 + (fVar12 * fVar27 - fVar10 * fVar21);
    param_1[3] = fVar8 * fVar30 + (fVar6 * fVar27 - fVar7 * fVar21);
    *param_1 = fVar18 * fVar30 + (fVar17 * fVar27 - fVar20 * fVar21);
    param_1[1] = fVar16 * fVar30 + (fVar13 * fVar27 - fVar19 * fVar21);
    fVar21 = fVar12 * fVar25;
    param_1[4] = fVar18 * fVar14 + fVar20 * fVar29 + fVar17 * fVar28;
    param_1[5] = fVar16 * fVar14 + fVar19 * fVar29 + fVar13 * fVar28;
    param_1[6] = fVar9 * fVar14 + fVar10 * fVar29 + fVar12 * fVar28;
    param_1[7] = fVar8 * fVar14 + fVar7 * fVar29 + fVar6 * fVar28;
    param_1[8] = fVar18 * fVar24 + fVar20 * fVar5 + fVar17 * fVar25;
    param_1[9] = fVar16 * fVar24 + fVar19 * fVar5 + fVar13 * fVar25;
    fVar15 = fVar10 * fVar5;
    goto code_r0x0203a584;
  case 3:
    fVar27 = fVar23 * fVar14;
    fVar25 = -(fVar23 * fVar22);
    fVar24 = fVar23 * fVar26;
    fVar11 = fVar26 * fVar26 - fVar5 * fVar22 * fVar21;
    fVar15 = fVar26 * fVar21 + fVar5 * fVar22 * fVar14;
    fVar29 = fVar22 * fVar14 + fVar5 * fVar26 * fVar21;
    fVar14 = fVar22 * fVar21 - fVar5 * fVar26 * fVar14;
    fVar21 = fVar12 * fVar25;
    param_1[8] = fVar18 * fVar24 + (fVar20 * fVar5 - fVar17 * fVar23 * fVar22);
    param_1[9] = fVar16 * fVar24 + (fVar19 * fVar5 - fVar13 * fVar23 * fVar22);
    *param_1 = fVar18 * fVar29 + (fVar17 * fVar11 - fVar20 * fVar27);
    param_1[1] = fVar16 * fVar29 + (fVar13 * fVar11 - fVar19 * fVar27);
    param_1[2] = fVar9 * fVar29 + (fVar12 * fVar11 - fVar10 * fVar27);
    param_1[3] = fVar8 * fVar29 + (fVar6 * fVar11 - fVar7 * fVar27);
    param_1[4] = fVar18 * fVar14 + fVar20 * fVar27 + fVar17 * fVar15;
    param_1[5] = fVar16 * fVar14 + fVar19 * fVar27 + fVar13 * fVar15;
    param_1[6] = fVar9 * fVar14 + fVar10 * fVar27 + fVar12 * fVar15;
    param_1[7] = fVar8 * fVar14 + fVar7 * fVar27 + fVar6 * fVar15;
    fVar15 = fVar10 * fVar5;
    goto code_r0x0203a584;
  case 4:
    fVar30 = fVar23 * fVar22;
    fVar28 = fVar23 * fVar21;
    fVar31 = fVar23 * fVar14;
    fVar24 = fVar26 * fVar14 + fVar5 * fVar22 * fVar21;
    fVar27 = fVar5 * fVar22 * fVar14 - fVar26 * fVar21;
    fVar29 = fVar18 * fVar5;
    fVar32 = fVar16 * fVar5;
    fVar25 = fVar5 * fVar26 * fVar21 - fVar22 * fVar14;
    fVar15 = fVar8 * fVar5;
    fVar11 = fVar9 * fVar5;
    fVar5 = fVar22 * fVar21 + fVar5 * fVar26 * fVar14;
    param_1[4] = (fVar17 * fVar28 + fVar20 * fVar31) - fVar29;
    param_1[5] = (fVar13 * fVar28 + fVar19 * fVar31) - fVar32;
    param_1[6] = (fVar12 * fVar28 + fVar10 * fVar31) - fVar11;
    param_1[7] = (fVar6 * fVar28 + fVar7 * fVar31) - fVar15;
    fVar22 = fVar18 * fVar23 * fVar26 + fVar17 * fVar25 + fVar20 * fVar5;
    fVar21 = fVar16 * fVar23 * fVar26 + fVar13 * fVar25 + fVar19 * fVar5;
    *param_1 = fVar18 * fVar30 + fVar17 * fVar24 + fVar20 * fVar27;
    param_1[1] = fVar16 * fVar30 + fVar13 * fVar24 + fVar19 * fVar27;
    param_1[2] = fVar9 * fVar30 + fVar12 * fVar24 + fVar10 * fVar27;
    param_1[3] = fVar8 * fVar30 + fVar6 * fVar24 + fVar7 * fVar27;
    goto code_r0x0203a57c;
  case 5:
    fVar15 = fVar26 * fVar14;
    fVar29 = fVar26 * fVar21;
    fVar24 = fVar5 * fVar22;
    fVar27 = fVar5 * fVar26;
    fVar25 = fVar5 * fVar21 - fVar23 * fVar22 * fVar14;
    fVar5 = fVar5 * fVar14 + fVar23 * fVar22 * fVar21;
    fVar11 = fVar23 * fVar21 + fVar24 * fVar14;
    fVar14 = fVar23 * fVar14 - fVar24 * fVar21;
    *param_1 = fVar18 * fVar22 + (fVar17 * fVar15 - fVar20 * fVar29);
    param_1[1] = fVar16 * fVar22 + (fVar13 * fVar15 - fVar19 * fVar29);
    param_1[2] = fVar9 * fVar22 + (fVar12 * fVar15 - fVar10 * fVar29);
    param_1[3] = fVar8 * fVar22 + (fVar6 * fVar15 - fVar7 * fVar29);
    fVar22 = fVar18 * fVar23 * fVar26 + fVar17 * fVar25 + fVar20 * fVar5;
    fVar21 = fVar16 * fVar23 * fVar26 + fVar13 * fVar25 + fVar19 * fVar5;
    param_1[4] = (fVar17 * fVar11 + fVar20 * fVar14) - fVar18 * fVar27;
    param_1[5] = (fVar13 * fVar11 + fVar19 * fVar14) - fVar16 * fVar27;
    param_1[6] = (fVar12 * fVar11 + fVar10 * fVar14) - fVar9 * fVar27;
    param_1[7] = (fVar6 * fVar11 + fVar7 * fVar14) - fVar8 * fVar27;
code_r0x0203a57c:
    fVar24 = fVar23 * fVar26;
    fVar15 = fVar12 * fVar25;
    param_1[8] = fVar22;
    param_1[9] = fVar21;
    break;
  default:
    fVar15 = fVar5 * fVar22;
    fVar27 = fVar26 * fVar14;
    fVar11 = fVar5 * fVar21;
    fVar30 = fVar26 * fVar21;
    fVar29 = fVar5 * fVar14;
    fVar5 = fVar5 * fVar26;
    fVar24 = fVar23 * fVar26;
    fVar29 = fVar23 * fVar22 * fVar21 - fVar29;
    fVar26 = fVar15 * fVar14 - fVar23 * fVar21;
    fVar11 = fVar11 + fVar23 * fVar22 * fVar14;
    fVar21 = fVar23 * fVar14 + fVar15 * fVar21;
    fVar25 = -fVar22;
    param_1[8] = fVar18 * fVar24 + (fVar20 * fVar5 - fVar17 * fVar22);
    param_1[9] = fVar16 * fVar24 + (fVar19 * fVar5 - fVar13 * fVar22);
    fVar15 = fVar12 * fVar25;
    *param_1 = fVar18 * fVar11 + fVar17 * fVar27 + fVar20 * fVar26;
    param_1[1] = fVar16 * fVar11 + fVar13 * fVar27 + fVar19 * fVar26;
    param_1[2] = fVar9 * fVar11 + fVar12 * fVar27 + fVar10 * fVar26;
    param_1[3] = fVar8 * fVar11 + fVar6 * fVar27 + fVar7 * fVar26;
    param_1[4] = fVar18 * fVar29 + fVar17 * fVar30 + fVar20 * fVar21;
    param_1[5] = fVar16 * fVar29 + fVar13 * fVar30 + fVar19 * fVar21;
    param_1[6] = fVar9 * fVar29 + fVar12 * fVar30 + fVar10 * fVar21;
    param_1[7] = fVar8 * fVar29 + fVar6 * fVar30 + fVar7 * fVar21;
  }
  fVar21 = fVar10 * fVar5;
code_r0x0203a584:
  param_1[10] = fVar9 * fVar24 + fVar15 + fVar21;
  param_1[0xb] = fVar6 * fVar25 + fVar7 * fVar5 + fVar8 * fVar24;
  return;
}

// ==== Aska::Matrix::RotateByUnitVector(Aska::Vector const*)
// vaddr 0x1f3a5b8 | ghidra 0x203a5b8 | size 660 | symbol _ZN4Aska6Matrix18RotateByUnitVectorEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix18RotateByUnitVectorEPKNS_6VectorE(float *param_1,float *param_2)

{
  bool bVar1;
  uint uVar2;
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
  
  fVar12 = param_2[2];
  uVar2 = (uint)(param_2[3] * _UNK_027ebdf4);
  fVar13 = param_2[3] + (float)(int)uVar2 * _UNK_027edb30;
  bVar1 = (uVar2 & 1) != 0;
  fVar14 = fVar13;
  if (bVar1) {
    fVar14 = -fVar13;
  }
  fVar13 = fVar13 * fVar13;
  fVar15 = *param_2;
  fVar17 = param_2[1];
  fVar19 = fVar13 * (fVar13 * (fVar13 * (fVar13 * (fVar13 * (fVar13 * (fVar13 * _UNK_02964910 +
                                                                      _UNK_02964914) + _UNK_02964918
                                                            ) + _UNK_0296491c) + _UNK_02964920) +
                              _UNK_02964924) + -0.5);
  fVar6 = *param_1;
  fVar7 = param_1[1];
  fVar8 = param_1[2];
  fVar3 = param_1[4];
  fVar4 = param_1[5];
  fVar5 = param_1[6];
  fVar9 = param_1[8];
  fVar10 = param_1[9];
  fVar11 = param_1[10];
  fVar16 = -1.0 - fVar19;
  if (!bVar1) {
    fVar16 = fVar19 + 1.0;
  }
  fVar14 = fVar14 * (fVar13 * (fVar13 * (fVar13 * (fVar13 * (fVar13 * (fVar13 * (fVar13 * 
                                                  _UNK_02964928 + _UNK_0296492c) + _UNK_02964930) +
                                                  _UNK_02964934) + _UNK_02964938) + _UNK_0296493c) +
                              _UNK_02964940) + 1.0);
  fVar19 = 1.0 - fVar16;
  fVar18 = fVar15 * fVar15 + (1.0 - fVar15 * fVar15) * fVar16;
  fVar13 = fVar15 * fVar17 * fVar19;
  fVar20 = fVar15 * fVar12 * fVar19;
  fVar19 = fVar17 * fVar12 * fVar19;
  fVar21 = fVar17 * fVar17 + (1.0 - fVar17 * fVar17) * fVar16;
  fVar16 = fVar12 * fVar12 + (1.0 - fVar12 * fVar12) * fVar16;
  fVar22 = fVar13 - fVar12 * fVar14;
  fVar23 = fVar17 * fVar14 + fVar20;
  fVar13 = fVar12 * fVar14 + fVar13;
  fVar12 = fVar19 - fVar15 * fVar14;
  fVar20 = fVar20 - fVar17 * fVar14;
  fVar19 = fVar15 * fVar14 + fVar19;
  *param_1 = fVar9 * fVar23 + fVar6 * fVar18 + fVar3 * fVar22;
  param_1[1] = fVar10 * fVar23 + fVar7 * fVar18 + fVar4 * fVar22;
  param_1[2] = fVar11 * fVar23 + fVar8 * fVar18 + fVar5 * fVar22;
  param_1[4] = fVar9 * fVar12 + fVar3 * fVar21 + fVar6 * fVar13;
  param_1[5] = fVar10 * fVar12 + fVar4 * fVar21 + fVar7 * fVar13;
  param_1[6] = fVar11 * fVar12 + fVar5 * fVar21 + fVar8 * fVar13;
  param_1[8] = fVar9 * fVar16 + fVar6 * fVar20 + fVar3 * fVar19;
  param_1[9] = fVar10 * fVar16 + fVar7 * fVar20 + fVar4 * fVar19;
  param_1[10] = fVar11 * fVar16 + fVar8 * fVar20 + fVar5 * fVar19;
  return;
}

// ==== Aska::Matrix::SetTranslate(Aska::Vector const*)
// vaddr 0x1f3a84c | ghidra 0x203a84c | size 28 | symbol _ZN4Aska6Matrix12SetTranslateEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Matrix12SetTranslateEPKNS_6VectorE(long param_1,undefined4 *param_2)

{
  *(undefined4 *)(param_1 + 0xc) = *param_2;
  *(undefined4 *)(param_1 + 0x1c) = param_2[1];
  *(undefined4 *)(param_1 + 0x2c) = param_2[2];
  return;
}

// ==== Aska::Matrix::Translate(Aska::Vector const*)
// vaddr 0x1f3a868 | ghidra 0x203a868 | size 228 | symbol _ZN4Aska6Matrix9TranslateEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Matrix9TranslateEPKNS_6VectorE(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar1 = param_1[0xc];
  fVar3 = param_1[0xd];
  *param_1 = *param_1 + *param_2 * fVar1;
  fVar2 = param_1[0xe];
  fVar4 = param_1[0xf];
  param_1[1] = param_1[1] + *param_2 * fVar3;
  param_1[2] = param_1[2] + *param_2 * fVar2;
  param_1[3] = param_1[3] + *param_2 * fVar4;
  param_1[4] = param_1[4] + param_2[1] * fVar1;
  param_1[5] = param_1[5] + param_2[1] * fVar3;
  param_1[6] = param_1[6] + param_2[1] * fVar2;
  param_1[7] = param_1[7] + param_2[1] * fVar4;
  param_1[8] = param_1[8] + param_2[2] * fVar1;
  param_1[9] = param_1[9] + param_2[2] * fVar3;
  param_1[10] = param_1[10] + param_2[2] * fVar2;
  param_1[0xb] = param_1[0xb] + param_2[2] * fVar4;
  return;
}

// ==== Aska::Matrix::Scale(Aska::Vector const*)
// vaddr 0x1f3a94c | ghidra 0x203a94c | size 48 | symbol _ZN4Aska6Matrix5ScaleEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Matrix5ScaleEPKNS_6VectorE(undefined8 *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar1 = *param_2;
  fVar2 = param_2[2];
  fVar3 = param_2[1];
  param_1[1] = CONCAT44(fVar1 * (float)((ulong)param_1[1] >> 0x20),fVar1 * (float)param_1[1]);
  *param_1 = CONCAT44(fVar1 * (float)((ulong)*param_1 >> 0x20),fVar1 * (float)*param_1);
  param_1[3] = CONCAT44((float)((ulong)param_1[3] >> 0x20) * fVar3,(float)param_1[3] * fVar3);
  param_1[2] = CONCAT44((float)((ulong)param_1[2] >> 0x20) * fVar3,(float)param_1[2] * fVar3);
  param_1[5] = CONCAT44((float)((ulong)param_1[5] >> 0x20) * fVar2,(float)param_1[5] * fVar2);
  param_1[4] = CONCAT44((float)((ulong)param_1[4] >> 0x20) * fVar2,(float)param_1[4] * fVar2);
  return;
}

// ==== Aska::Matrix::MakeClip(float, float, Aska::Vector*, Aska::Vector*)
// vaddr 0x1f3a97c | ghidra 0x203a97c | size 164 | symbol _ZN4Aska6Matrix8MakeClipEffPNS_6VectorES2_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix8MakeClipEffPNS_6VectorES2_
               (float param_1,float param_2,float *param_3,float *param_4,float *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  fVar6 = param_5[1];
  fVar3 = param_5[2];
  fVar8 = param_4[1];
  fVar4 = param_4[2];
  fVar5 = *param_5;
  fVar7 = *param_4;
  param_3[2] = 0.0;
  param_3[3] = 0.0;
  param_3[0] = 0.0;
  param_3[1] = 0.0;
  param_3[6] = 0.0;
  param_3[7] = 0.0;
  param_3[4] = 0.0;
  param_3[5] = 0.0;
  param_3[10] = 0.0;
  param_3[0xb] = 0.0;
  param_3[8] = 0.0;
  param_3[9] = 0.0;
  param_3[0xe] = 0.0;
  param_3[0xf] = 0.0;
  param_3[0xc] = 0.0;
  fVar2 = _UNK_02970cc8;
  fVar1 = _UNK_02970cc4;
  param_3[0xd] = 0.0;
  param_3[10] = (fVar3 + fVar4) / (fVar3 - fVar4);
  param_3[0xb] = (fVar3 * fVar4 * -2.0) / (fVar3 - fVar4);
  *param_3 = (param_1 + param_1) / (fVar2 - (ABS(fVar7 + (fVar5 - fVar7) * 0.5) + fVar1));
  param_3[5] = ((param_1 + param_1) * param_2) /
               (fVar2 - (ABS(fVar8 + (fVar6 - fVar8) * 0.5) + fVar1));
  param_3[0xe] = 1.0;
  return;
}

// ==== Aska::Matrix::MakeClipToScreen(float, Aska::Vector*, Aska::Vector*, float, float, float, float)
// vaddr 0x1f3aa20 | ghidra 0x203aa20 | size 144 | symbol _ZN4Aska6Matrix16MakeClipToScreenEfPNS_6VectorES2_ffff | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix16MakeClipToScreenEfPNS_6VectorES2_ffff
               (undefined1 param_1 [16],float param_2,float param_3,float param_4,float param_5,
               float *param_6,float *param_7,float *param_8)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar2 = *param_8;
  fVar3 = param_8[1];
  fVar4 = *param_7;
  fVar5 = param_7[1];
  param_6[2] = 0.0;
  param_6[3] = 0.0;
  param_6[0] = 0.0;
  param_6[1] = 0.0;
  param_6[6] = 0.0;
  param_6[7] = 0.0;
  param_6[4] = 0.0;
  param_6[5] = 0.0;
  param_6[10] = 0.0;
  param_6[0xb] = 0.0;
  param_6[8] = 0.0;
  param_6[9] = 0.0;
  param_6[0xe] = 0.0;
  param_6[0xf] = 0.0;
  param_6[0xc] = 0.0;
  param_6[0xd] = 0.0;
  param_6[3] = param_2;
  fVar1 = _UNK_02970cc4;
  param_6[10] = (param_4 - param_5) * 0.5;
  param_6[0xb] = (param_4 + param_5) * 0.5;
  param_6[7] = param_3;
  fVar3 = _UNK_02970cc8 - (ABS(fVar5 + (fVar3 - fVar5) * 0.5) + fVar1);
  *param_6 = (_UNK_02970cc8 - (ABS(fVar4 + (fVar2 - fVar4) * 0.5) + fVar1)) * 0.5;
  param_6[5] = fVar3 * 0.5;
  param_6[0xf] = 1.0;
  return;
}

// ==== Aska::Matrix::MulVector(Aska::Vector const*)
// vaddr 0x1f3aab0 | ghidra 0x203aab0 | size 228 | symbol _ZN4Aska6Matrix9MulVectorEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Matrix9MulVectorEPKNS_6VectorE(float *param_1,float *param_2)

{
  *param_1 = *param_2 * *param_1;
  param_1[1] = param_2[1] * param_1[1];
  param_1[2] = param_2[2] * param_1[2];
  param_1[3] = param_2[3] * param_1[3];
  param_1[4] = *param_2 * param_1[4];
  param_1[5] = param_2[1] * param_1[5];
  param_1[6] = param_2[2] * param_1[6];
  param_1[7] = param_2[3] * param_1[7];
  param_1[8] = *param_2 * param_1[8];
  param_1[9] = param_2[1] * param_1[9];
  param_1[10] = param_2[2] * param_1[10];
  param_1[0xb] = param_2[3] * param_1[0xb];
  param_1[0xc] = *param_2 * param_1[0xc];
  param_1[0xd] = param_2[1] * param_1[0xd];
  param_1[0xe] = param_2[2] * param_1[0xe];
  param_1[0xf] = param_2[3] * param_1[0xf];
  return;
}

// ==== Aska::Matrix::MulVector(Aska::Matrix*, Aska::Vector const*) const
// vaddr 0x1f3ab94 | ghidra 0x203ab94 | size 260 | symbol _ZNK4Aska6Matrix9MulVectorEPS0_PKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska6Matrix9MulVectorEPS0_PKNS_6VectorE(float *param_1,float *param_2,float *param_3)

{
  *param_2 = *param_1 * *param_3;
  param_2[1] = param_1[1] * param_3[1];
  param_2[2] = param_1[2] * param_3[2];
  param_2[3] = param_1[3] * param_3[3];
  param_2[4] = param_1[4] * *param_3;
  param_2[5] = param_1[5] * param_3[1];
  param_2[6] = param_1[6] * param_3[2];
  param_2[7] = param_1[7] * param_3[3];
  param_2[8] = param_1[8] * *param_3;
  param_2[9] = param_1[9] * param_3[1];
  param_2[10] = param_1[10] * param_3[2];
  param_2[0xb] = param_1[0xb] * param_3[3];
  param_2[0xc] = param_1[0xc] * *param_3;
  param_2[0xd] = param_1[0xd] * param_3[1];
  param_2[0xe] = param_1[0xe] * param_3[2];
  param_2[0xf] = param_1[0xf] * param_3[3];
  return;
}

// ==== Aska::Matrix::ApplyVector(Aska::Vector*, Aska::Vector const*) const
// vaddr 0x1f3ac98 | ghidra 0x203ac98 | size 328 | symbol _ZNK4Aska6Matrix11ApplyVectorEPNS_6VectorEPKS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska6Matrix11ApplyVectorEPNS_6VectorEPKS1_(float *param_1,float *param_2,float *param_3)

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
  
  fVar1 = *param_3;
  fVar2 = param_3[1];
  fVar5 = param_3[2];
  fVar4 = param_3[3];
  fVar3 = *param_1 * fVar1 + param_1[1] * fVar2 + param_1[2] * fVar5 + param_1[3] * fVar4;
  if (param_3 != param_2) {
    *param_2 = fVar3;
    param_2[1] = param_1[4] * *param_3 + param_1[5] * param_3[1] + param_1[6] * param_3[2] +
                 param_1[7] * param_3[3];
    param_2[2] = param_1[8] * *param_3 + param_1[9] * param_3[1] + param_1[10] * param_3[2] +
                 param_1[0xb] * param_3[3];
    param_2[3] = param_1[0xc] * *param_3 + param_1[0xd] * param_3[1] + param_1[0xe] * param_3[2] +
                 param_1[0xf] * param_3[3];
    return;
  }
  fVar6 = param_1[4];
  fVar7 = param_1[5];
  fVar10 = param_1[8];
  fVar11 = param_1[9];
  fVar14 = param_1[0xc];
  fVar16 = param_1[0xd];
  fVar8 = param_1[6];
  fVar9 = param_1[7];
  fVar12 = param_1[10];
  fVar13 = param_1[0xb];
  fVar15 = param_1[0xe];
  fVar17 = param_1[0xf];
  *param_3 = fVar3;
  param_3[1] = fVar1 * fVar6 + fVar2 * fVar7 + fVar5 * fVar8 + fVar4 * fVar9;
  param_3[2] = fVar1 * fVar10 + fVar2 * fVar11 + fVar5 * fVar12 + fVar4 * fVar13;
  param_2[3] = fVar1 * fVar14 + fVar2 * fVar16 + fVar5 * fVar15 + fVar4 * fVar17;
  return;
}

// ==== Aska::Matrix::SetLookAtMatrixXP(Aska::Vector const*, Aska::Vector const*, float)
// vaddr 0x1f3ade0 | ghidra 0x203ade0 | size 856 | symbol _ZN4Aska6Matrix17SetLookAtMatrixXPEPKNS_6VectorES3_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix17SetLookAtMatrixXPEPKNS_6VectorES3_f
               (float param_1,long param_2,undefined4 *param_3,float *param_4)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  bool bVar8;
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
  float fStack_100;
  float fStack_fc;
  undefined8 uStack_f8;
  float fStack_f0;
  float fStack_ec;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb28;
  uVar4 = _UNK_027dbb20;
  uVar3 = _UNK_027dbb18;
  uVar2 = _UNK_027dbb08;
  uStack_b8 = _UNK_027dbb08;
  uStack_c0 = _UNK_027dbb00;
  uStack_a8 = _UNK_027dbb18;
  uStack_b0 = _UNK_027dbb10;
  uStack_98 = _UNK_027dbb28;
  uStack_a0 = _UNK_027dbb20;
  uStack_88 = _UNK_027dbb38;
  uStack_90 = _UNK_027dbb30;
  fVar12 = *param_4;
  fVar15 = param_4[1];
  fVar10 = param_4[2];
  fVar11 = fVar12 * fVar12 + fVar15 * fVar15 + fVar10 * fVar10;
  fVar9 = SQRT(fVar11);
  if (NAN(fVar9)) {
    fVar9 = (float)sqrtf(fVar11);
  }
  fVar11 = _UNK_027e519c;
  if (_UNK_027e519c <= fVar9) {
    fVar9 = 1.0 / fVar9;
    fVar12 = fVar9 * fVar12;
    fVar15 = fVar9 * fVar15;
    fVar10 = fVar9 * fVar10;
  }
  fVar19 = fVar15 * 0.0 - fVar10;
  fVar18 = fVar10 * 0.0 - fVar12 * 0.0;
  fVar17 = fVar12 - fVar15 * 0.0;
  fVar13 = fVar17 * fVar17 + fVar19 * fVar19 + fVar18 * fVar18;
  fVar9 = SQRT(fVar13);
  if (NAN(fVar9)) {
    fVar9 = (float)sqrtf(fVar13);
  }
  if (fVar11 <= fVar9) {
    fVar9 = 1.0 / fVar9;
    fVar19 = fVar9 * fVar19;
    fVar18 = fVar9 * fVar18;
    fVar17 = fVar9 * fVar17;
  }
  fVar16 = fVar18 * fVar10 - fVar17 * fVar15;
  fVar21 = fVar17 * fVar12 - fVar19 * fVar10;
  fVar20 = fVar19 * fVar15 - fVar18 * fVar12;
  fVar13 = fVar20 * fVar20 + fVar16 * fVar16 + fVar21 * fVar21;
  fVar9 = SQRT(fVar13);
  if (NAN(fVar9)) {
    fVar9 = (float)sqrtf(fVar13);
  }
  if (fVar11 <= fVar9) {
    fVar9 = 1.0 / fVar9;
    fVar16 = fVar16 * fVar9;
    fVar21 = fVar9 * fVar21;
    fVar20 = fVar9 * fVar20;
  }
  uStack_f8 = uVar2;
  uStack_e8 = uVar3;
  uStack_c8 = uVar7;
  uStack_d0 = uVar6;
  fVar11 = param_1 + (float)(int)(param_1 * _UNK_027ebdf4) * _UNK_027edb30;
  uStack_d8 = uVar5;
  uStack_e0 = uVar4;
  bVar8 = ((int)(param_1 * _UNK_027ebdf4) & 1U) != 0;
  fVar9 = fVar11;
  if (bVar8) {
    fVar9 = -fVar11;
  }
  fVar11 = fVar11 * fVar11;
  fVar13 = fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * _UNK_02964910 +
                                                                      _UNK_02964914) + _UNK_02964918
                                                            ) + _UNK_0296491c) + _UNK_02964920) +
                              _UNK_02964924) + -0.5);
  fVar14 = fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * _UNK_02964928 +
                                                                      _UNK_0296492c) + _UNK_02964930
                                                            ) + _UNK_02964934) + _UNK_02964938) +
                              _UNK_0296493c) + _UNK_02964940) + 1.0;
  fVar11 = -1.0 - fVar13;
  if (!bVar8) {
    fVar11 = fVar13 + 1.0;
  }
  uStack_c0 = CONCAT44(fVar16,fVar12);
  uStack_b8 = CONCAT44(uStack_b8._4_4_,fVar19);
  uStack_b0 = CONCAT44(fVar21,fVar15);
  uStack_a8 = CONCAT44(uStack_a8._4_4_,fVar18);
  uStack_a0 = CONCAT44(fVar20,fVar10);
  uStack_98 = CONCAT44(uStack_98._4_4_,fVar17);
  _fStack_100 = CONCAT44(fVar9 * fVar14,fVar11);
  _fStack_f0 = CONCAT44(fVar11,-(fVar9 * fVar14));
  Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)(param_2,&uStack_c0,&fStack_100);
  *(undefined4 *)(param_2 + 0xc) = *param_3;
  *(undefined4 *)(param_2 + 0x1c) = param_3[1];
  uVar1 = param_3[2];
  *(undefined4 *)(param_2 + 0x3c) = 0x3f800000;
  *(undefined4 *)(param_2 + 0x2c) = uVar1;
  return;
}

// ==== Aska::Matrix::SetLookAtMatrixXN(Aska::Vector const*, Aska::Vector const*, float)
// vaddr 0x1f3b138 | ghidra 0x203b138 | size 844 | symbol _ZN4Aska6Matrix17SetLookAtMatrixXNEPKNS_6VectorES3_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix17SetLookAtMatrixXNEPKNS_6VectorES3_f
               (float param_1,long param_2,undefined4 *param_3,float *param_4)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  bool bVar8;
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
  float fStack_e0;
  float fStack_dc;
  undefined8 uStack_d8;
  float fStack_d0;
  float fStack_cc;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb28;
  uVar4 = _UNK_027dbb20;
  uVar3 = _UNK_027dbb18;
  uVar2 = _UNK_027dbb08;
  uStack_98 = _UNK_027dbb08;
  uStack_a0 = _UNK_027dbb00;
  uStack_88 = _UNK_027dbb18;
  uStack_90 = _UNK_027dbb10;
  uStack_78 = _UNK_027dbb28;
  uStack_80 = _UNK_027dbb20;
  uStack_68 = _UNK_027dbb38;
  uStack_70 = _UNK_027dbb30;
  fVar12 = *param_4;
  fVar14 = param_4[1];
  fVar16 = param_4[2];
  fVar10 = fVar12 * fVar12 + fVar14 * fVar14 + fVar16 * fVar16;
  fVar9 = SQRT(fVar10);
  if (NAN(fVar9)) {
    fVar9 = (float)sqrtf(fVar10);
  }
  fVar10 = _UNK_027e519c;
  fVar12 = -fVar12;
  fVar14 = -fVar14;
  fVar16 = -fVar16;
  if (_UNK_027e519c <= fVar9) {
    fVar9 = 1.0 / fVar9;
    fVar12 = fVar9 * fVar12;
    fVar14 = fVar9 * fVar14;
    fVar16 = fVar9 * fVar16;
  }
  fVar19 = fVar14 * 0.0 - fVar16;
  fVar18 = fVar16 * 0.0 - fVar12 * 0.0;
  fVar17 = fVar12 - fVar14 * 0.0;
  fVar11 = fVar17 * fVar17 + fVar19 * fVar19 + fVar18 * fVar18;
  fVar9 = SQRT(fVar11);
  if (NAN(fVar9)) {
    fVar9 = (float)sqrtf(fVar11);
  }
  if (fVar10 <= fVar9) {
    fVar9 = 1.0 / fVar9;
    fVar19 = fVar19 * fVar9;
    fVar18 = fVar9 * fVar18;
    fVar17 = fVar17 * fVar9;
  }
  fVar15 = fVar16 * fVar18 - fVar14 * fVar17;
  fVar20 = fVar12 * fVar17 - fVar16 * fVar19;
  fVar13 = fVar14 * fVar19 - fVar12 * fVar18;
  fVar11 = fVar13 * fVar13 + fVar15 * fVar15 + fVar20 * fVar20;
  fVar9 = SQRT(fVar11);
  if (NAN(fVar9)) {
    fVar9 = (float)sqrtf(fVar11);
  }
  if (fVar10 <= fVar9) {
    fVar9 = 1.0 / fVar9;
    fVar15 = fVar15 * fVar9;
    fVar20 = fVar9 * fVar20;
    fVar13 = fVar9 * fVar13;
  }
  uStack_90 = CONCAT44(fVar20,fVar14);
  uStack_c8 = uVar3;
  uStack_a8 = uVar7;
  uStack_b0 = uVar6;
  uStack_d8 = uVar2;
  uStack_b8 = uVar5;
  uStack_c0 = uVar4;
  fVar10 = param_1 + (float)(int)(param_1 * _UNK_027ebdf4) * _UNK_027edb30;
  bVar8 = ((int)(param_1 * _UNK_027ebdf4) & 1U) != 0;
  fVar9 = fVar10;
  if (bVar8) {
    fVar9 = -fVar10;
  }
  fVar10 = fVar10 * fVar10;
  fVar14 = fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * _UNK_02964910 +
                                                                      _UNK_02964914) + _UNK_02964918
                                                            ) + _UNK_0296491c) + _UNK_02964920) +
                              _UNK_02964924) + -0.5);
  fVar11 = fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * _UNK_02964928 +
                                                                      _UNK_0296492c) + _UNK_02964930
                                                            ) + _UNK_02964934) + _UNK_02964938) +
                              _UNK_0296493c) + _UNK_02964940) + 1.0;
  fVar10 = -1.0 - fVar14;
  if (!bVar8) {
    fVar10 = fVar14 + 1.0;
  }
  uStack_a0 = CONCAT44(fVar15,fVar12);
  uStack_80 = CONCAT44(fVar13,fVar16);
  uStack_98 = CONCAT44(uStack_98._4_4_,fVar19);
  uStack_88 = CONCAT44(uStack_88._4_4_,fVar18);
  uStack_78 = CONCAT44(uStack_78._4_4_,fVar17);
  _fStack_e0 = CONCAT44(fVar9 * fVar11,fVar10);
  _fStack_d0 = CONCAT44(fVar10,-(fVar9 * fVar11));
  Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)(param_2,&uStack_a0,&fStack_e0);
  *(undefined4 *)(param_2 + 0xc) = *param_3;
  *(undefined4 *)(param_2 + 0x1c) = param_3[1];
  uVar1 = param_3[2];
  *(undefined4 *)(param_2 + 0x3c) = 0x3f800000;
  *(undefined4 *)(param_2 + 0x2c) = uVar1;
  return;
}

// ==== Aska::Matrix::SetLookAtMatrixYP(Aska::Vector const*, Aska::Vector const*, float)
// vaddr 0x1f3b484 | ghidra 0x203b484 | size 864 | symbol _ZN4Aska6Matrix17SetLookAtMatrixYPEPKNS_6VectorES3_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix17SetLookAtMatrixYPEPKNS_6VectorES3_f
               (float param_1,long param_2,undefined4 *param_3,float *param_4)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  bool bVar8;
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
  float fStack_100;
  float fStack_fc;
  undefined8 uStack_f8;
  float fStack_f0;
  float fStack_ec;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb28;
  uVar4 = _UNK_027dbb20;
  uVar3 = _UNK_027dbb18;
  uVar2 = _UNK_027dbb08;
  uStack_b8 = _UNK_027dbb08;
  uStack_c0 = _UNK_027dbb00;
  uStack_a8 = _UNK_027dbb18;
  uStack_b0 = _UNK_027dbb10;
  uStack_98 = _UNK_027dbb28;
  uStack_a0 = _UNK_027dbb20;
  uStack_88 = _UNK_027dbb38;
  uStack_90 = _UNK_027dbb30;
  fVar12 = *param_4;
  fVar15 = param_4[1];
  fVar10 = param_4[2];
  fVar11 = fVar12 * fVar12 + fVar15 * fVar15 + fVar10 * fVar10;
  fVar9 = SQRT(fVar11);
  if (NAN(fVar9)) {
    fVar9 = (float)sqrtf(fVar11);
  }
  fVar11 = _UNK_027e519c;
  if (_UNK_027e519c <= fVar9) {
    fVar9 = 1.0 / fVar9;
    fVar12 = fVar9 * fVar12;
    fVar15 = fVar9 * fVar15;
    fVar10 = fVar9 * fVar10;
  }
  fVar18 = fVar10 * 0.0 - fVar15 * 0.0;
  fVar17 = fVar12 * 0.0 - fVar10;
  fVar16 = fVar15 - fVar12 * 0.0;
  fVar13 = fVar16 * fVar16 + fVar18 * fVar18 + fVar17 * fVar17;
  fVar9 = SQRT(fVar13);
  if (NAN(fVar9)) {
    fVar9 = (float)sqrtf(fVar13);
  }
  if (fVar11 <= fVar9) {
    fVar9 = 1.0 / fVar9;
    fVar18 = fVar9 * fVar18;
    fVar17 = fVar9 * fVar17;
    fVar16 = fVar9 * fVar16;
  }
  fVar20 = fVar16 * fVar15 - fVar17 * fVar10;
  fVar21 = fVar18 * fVar10 - fVar16 * fVar12;
  fVar19 = fVar17 * fVar12 - fVar18 * fVar15;
  fVar13 = fVar19 * fVar19 + fVar20 * fVar20 + fVar21 * fVar21;
  fVar9 = SQRT(fVar13);
  if (NAN(fVar9)) {
    fVar9 = (float)sqrtf(fVar13);
  }
  if (fVar11 <= fVar9) {
    fVar9 = 1.0 / fVar9;
    fVar20 = fVar20 * fVar9;
    fVar21 = fVar9 * fVar21;
    fVar19 = fVar9 * fVar19;
  }
  uStack_f8 = uVar2;
  uStack_e8 = uVar3;
  uStack_c8 = uVar7;
  uStack_d0 = uVar6;
  fVar11 = param_1 + (float)(int)(param_1 * _UNK_027ebdf4) * _UNK_027edb30;
  uStack_d8 = uVar5;
  uStack_e0 = uVar4;
  bVar8 = ((int)(param_1 * _UNK_027ebdf4) & 1U) != 0;
  fVar9 = fVar11;
  if (bVar8) {
    fVar9 = -fVar11;
  }
  fVar11 = fVar11 * fVar11;
  fVar13 = fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * _UNK_02964910 +
                                                                      _UNK_02964914) + _UNK_02964918
                                                            ) + _UNK_0296491c) + _UNK_02964920) +
                              _UNK_02964924) + -0.5);
  fVar14 = fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * _UNK_02964928 +
                                                                      _UNK_0296492c) + _UNK_02964930
                                                            ) + _UNK_02964934) + _UNK_02964938) +
                              _UNK_0296493c) + _UNK_02964940) + 1.0;
  fVar11 = -1.0 - fVar13;
  if (!bVar8) {
    fVar11 = fVar13 + 1.0;
  }
  uStack_c0 = CONCAT44(fVar12,fVar20);
  uStack_b0 = CONCAT44(fVar15,fVar21);
  uStack_a0 = CONCAT44(fVar10,fVar19);
  uStack_b8 = CONCAT44(uStack_b8._4_4_,fVar18);
  uStack_a8 = CONCAT44(uStack_a8._4_4_,fVar17);
  uStack_98 = CONCAT44(uStack_98._4_4_,fVar16);
  _fStack_100 = CONCAT44(fVar9 * fVar14,fVar11);
  _fStack_f0 = CONCAT44(fVar11,-(fVar9 * fVar14));
  Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)(param_2,&uStack_c0,&fStack_100);
  *(undefined4 *)(param_2 + 0xc) = *param_3;
  *(undefined4 *)(param_2 + 0x1c) = param_3[1];
  uVar1 = param_3[2];
  *(undefined4 *)(param_2 + 0x3c) = 0x3f800000;
  *(undefined4 *)(param_2 + 0x2c) = uVar1;
  return;
}

// ==== Aska::Matrix::SetLookAtMatrixYN(Aska::Vector const*, Aska::Vector const*, float)
// vaddr 0x1f3b7e4 | ghidra 0x203b7e4 | size 844 | symbol _ZN4Aska6Matrix17SetLookAtMatrixYNEPKNS_6VectorES3_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix17SetLookAtMatrixYNEPKNS_6VectorES3_f
               (float param_1,long param_2,undefined4 *param_3,float *param_4)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  bool bVar8;
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
  float fStack_e0;
  float fStack_dc;
  undefined8 uStack_d8;
  float fStack_d0;
  float fStack_cc;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb28;
  uVar4 = _UNK_027dbb20;
  uVar3 = _UNK_027dbb18;
  uVar2 = _UNK_027dbb08;
  uStack_98 = _UNK_027dbb08;
  uStack_a0 = _UNK_027dbb00;
  uStack_88 = _UNK_027dbb18;
  uStack_90 = _UNK_027dbb10;
  uStack_78 = _UNK_027dbb28;
  uStack_80 = _UNK_027dbb20;
  uStack_68 = _UNK_027dbb38;
  uStack_70 = _UNK_027dbb30;
  fVar12 = *param_4;
  fVar14 = param_4[1];
  fVar15 = param_4[2];
  fVar10 = fVar12 * fVar12 + fVar14 * fVar14 + fVar15 * fVar15;
  fVar9 = SQRT(fVar10);
  if (NAN(fVar9)) {
    fVar9 = (float)sqrtf(fVar10);
  }
  fVar10 = _UNK_027e519c;
  fVar12 = -fVar12;
  fVar14 = -fVar14;
  fVar15 = -fVar15;
  if (_UNK_027e519c <= fVar9) {
    fVar9 = 1.0 / fVar9;
    fVar12 = fVar9 * fVar12;
    fVar14 = fVar9 * fVar14;
    fVar15 = fVar9 * fVar15;
  }
  fVar19 = fVar15 * 0.0 - fVar14 * 0.0;
  fVar18 = fVar12 * 0.0 - fVar15;
  fVar17 = fVar14 - fVar12 * 0.0;
  fVar11 = fVar17 * fVar17 + fVar19 * fVar19 + fVar18 * fVar18;
  fVar9 = SQRT(fVar11);
  if (NAN(fVar9)) {
    fVar9 = (float)sqrtf(fVar11);
  }
  if (fVar10 <= fVar9) {
    fVar9 = 1.0 / fVar9;
    fVar19 = fVar19 * fVar9;
    fVar18 = fVar9 * fVar18;
    fVar17 = fVar9 * fVar17;
  }
  fVar20 = fVar14 * fVar17 - fVar15 * fVar18;
  fVar16 = fVar15 * fVar19 - fVar12 * fVar17;
  fVar13 = fVar12 * fVar18 - fVar14 * fVar19;
  fVar11 = fVar13 * fVar13 + fVar20 * fVar20 + fVar16 * fVar16;
  fVar9 = SQRT(fVar11);
  if (NAN(fVar9)) {
    fVar9 = (float)sqrtf(fVar11);
  }
  if (fVar10 <= fVar9) {
    fVar9 = 1.0 / fVar9;
    fVar20 = fVar20 * fVar9;
    fVar16 = fVar9 * fVar16;
    fVar13 = fVar9 * fVar13;
  }
  uStack_a0 = CONCAT44(fVar12,fVar20);
  uStack_c8 = uVar3;
  uStack_a8 = uVar7;
  uStack_b0 = uVar6;
  uStack_d8 = uVar2;
  uStack_b8 = uVar5;
  uStack_c0 = uVar4;
  fVar10 = param_1 + (float)(int)(param_1 * _UNK_027ebdf4) * _UNK_027edb30;
  bVar8 = ((int)(param_1 * _UNK_027ebdf4) & 1U) != 0;
  fVar9 = fVar10;
  if (bVar8) {
    fVar9 = -fVar10;
  }
  fVar10 = fVar10 * fVar10;
  fVar12 = fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * _UNK_02964910 +
                                                                      _UNK_02964914) + _UNK_02964918
                                                            ) + _UNK_0296491c) + _UNK_02964920) +
                              _UNK_02964924) + -0.5);
  fVar11 = fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * _UNK_02964928 +
                                                                      _UNK_0296492c) + _UNK_02964930
                                                            ) + _UNK_02964934) + _UNK_02964938) +
                              _UNK_0296493c) + _UNK_02964940) + 1.0;
  fVar10 = -1.0 - fVar12;
  if (!bVar8) {
    fVar10 = fVar12 + 1.0;
  }
  uStack_90 = CONCAT44(fVar14,fVar16);
  uStack_80 = CONCAT44(fVar15,fVar13);
  uStack_98 = CONCAT44(uStack_98._4_4_,fVar19);
  uStack_88 = CONCAT44(uStack_88._4_4_,fVar18);
  uStack_78 = CONCAT44(uStack_78._4_4_,fVar17);
  _fStack_e0 = CONCAT44(fVar9 * fVar11,fVar10);
  _fStack_d0 = CONCAT44(fVar10,-(fVar9 * fVar11));
  Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)(param_2,&uStack_a0,&fStack_e0);
  *(undefined4 *)(param_2 + 0xc) = *param_3;
  *(undefined4 *)(param_2 + 0x1c) = param_3[1];
  uVar1 = param_3[2];
  *(undefined4 *)(param_2 + 0x3c) = 0x3f800000;
  *(undefined4 *)(param_2 + 0x2c) = uVar1;
  return;
}

// ==== Aska::Matrix::SetLookAtMatrixZPUp(Aska::Vector const*, Aska::Vector const*, Aska::Vector const*, float)
// vaddr 0x1f3bb30 | ghidra 0x203bb30 | size 928 | symbol _ZN4Aska6Matrix19SetLookAtMatrixZPUpEPKNS_6VectorES3_S3_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix19SetLookAtMatrixZPUpEPKNS_6VectorES3_S3_f
               (float param_1,undefined8 *param_2,undefined4 *param_3,float *param_4,float *param_5)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  bool bVar10;
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
  float fStack_100;
  float fStack_fc;
  undefined8 uStack_f8;
  float fStack_f0;
  float fStack_ec;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  
  uVar9 = _UNK_027dbb38;
  uVar8 = _UNK_027dbb30;
  uVar7 = _UNK_027dbb28;
  uVar6 = _UNK_027dbb20;
  uVar5 = _UNK_027dbb18;
  uVar4 = _UNK_027dbb10;
  uVar3 = _UNK_027dbb08;
  uVar2 = _UNK_027dbb00;
  uStack_b8 = _UNK_027dbb08;
  uStack_c0 = _UNK_027dbb00;
  uStack_a8 = _UNK_027dbb18;
  uStack_b0 = _UNK_027dbb10;
  uStack_98 = _UNK_027dbb28;
  uStack_a0 = _UNK_027dbb20;
  uStack_88 = _UNK_027dbb38;
  uStack_90 = _UNK_027dbb30;
  fVar17 = *param_4;
  if (fVar17 == 0.0) {
    fVar18 = param_4[1];
    if ((fVar18 == 0.0) && (param_4[2] == 0.0)) {
      param_2[1] = _UNK_027dbb08;
      *param_2 = uVar2;
      param_2[3] = uVar5;
      param_2[2] = uVar4;
      param_2[5] = uVar7;
      param_2[4] = uVar6;
      param_2[7] = uVar9;
      param_2[6] = uVar8;
      return;
    }
  }
  else {
    fVar18 = param_4[1];
  }
  fVar15 = param_4[2];
  fVar12 = fVar17 * fVar17 + fVar18 * fVar18 + fVar15 * fVar15;
  fVar11 = SQRT(fVar12);
  if (NAN(fVar11)) {
    fVar11 = (float)sqrtf(fVar12);
  }
  fVar12 = _UNK_027e519c;
  if (_UNK_027e519c <= fVar11) {
    fVar11 = 1.0 / fVar11;
    fVar18 = fVar11 * fVar18;
    fVar15 = fVar11 * fVar15;
    fVar17 = fVar11 * fVar17;
  }
  fVar21 = param_5[1] * param_4[2] - param_5[2] * param_4[1];
  fVar20 = param_5[2] * *param_4 - param_4[2] * *param_5;
  fVar19 = param_4[1] * *param_5 - param_5[1] * *param_4;
  fVar13 = fVar19 * fVar19 + fVar21 * fVar21 + fVar20 * fVar20;
  fVar11 = SQRT(fVar13);
  if (NAN(fVar11)) {
    fVar11 = (float)sqrtf(fVar13);
  }
  if (fVar12 <= fVar11) {
    fVar11 = 1.0 / fVar11;
    fVar21 = fVar21 * fVar11;
    fVar20 = fVar11 * fVar20;
    fVar19 = fVar11 * fVar19;
  }
  fVar22 = fVar19 * fVar18 - fVar20 * fVar15;
  fVar16 = fVar21 * fVar15 - fVar19 * fVar17;
  fVar23 = fVar20 * fVar17 - fVar21 * fVar18;
  fVar13 = fVar23 * fVar23 + fVar22 * fVar22 + fVar16 * fVar16;
  fVar11 = SQRT(fVar13);
  if (NAN(fVar11)) {
    fVar11 = (float)sqrtf(fVar13);
  }
  if (fVar12 <= fVar11) {
    fVar11 = 1.0 / fVar11;
    fVar22 = fVar11 * fVar22;
    fVar16 = fVar11 * fVar16;
    fVar23 = fVar23 * fVar11;
  }
  uStack_f8 = uVar3;
  uStack_e8 = uVar5;
  uStack_c8 = uVar9;
  uStack_d0 = uVar8;
  fVar12 = param_1 + (float)(int)(param_1 * _UNK_027ebdf4) * _UNK_027edb30;
  uStack_d8 = uVar7;
  uStack_e0 = uVar6;
  bVar10 = ((int)(param_1 * _UNK_027ebdf4) & 1U) != 0;
  fVar11 = fVar12;
  if (bVar10) {
    fVar11 = -fVar12;
  }
  fVar12 = fVar12 * fVar12;
  fVar13 = fVar12 * (fVar12 * (fVar12 * (fVar12 * (fVar12 * (fVar12 * (fVar12 * _UNK_02964910 +
                                                                      _UNK_02964914) + _UNK_02964918
                                                            ) + _UNK_0296491c) + _UNK_02964920) +
                              _UNK_02964924) + -0.5);
  fVar14 = fVar12 * (fVar12 * (fVar12 * (fVar12 * (fVar12 * (fVar12 * (fVar12 * _UNK_02964928 +
                                                                      _UNK_0296492c) + _UNK_02964930
                                                            ) + _UNK_02964934) + _UNK_02964938) +
                              _UNK_0296493c) + _UNK_02964940) + 1.0;
  fVar12 = -1.0 - fVar13;
  if (!bVar10) {
    fVar12 = fVar13 + 1.0;
  }
  uStack_c0 = CONCAT44(fVar22,fVar21);
  uStack_b0 = CONCAT44(fVar16,fVar20);
  uStack_a0 = CONCAT44(fVar23,fVar19);
  uStack_b8 = CONCAT44(uStack_b8._4_4_,fVar17);
  uStack_a8 = CONCAT44(uStack_a8._4_4_,fVar18);
  uStack_98 = CONCAT44(uStack_98._4_4_,fVar15);
  _fStack_100 = CONCAT44(fVar11 * fVar14,fVar12);
  _fStack_f0 = CONCAT44(fVar12,-(fVar11 * fVar14));
  Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)(param_2,&uStack_c0,&fStack_100);
  *(undefined4 *)((long)param_2 + 0xc) = *param_3;
  *(undefined4 *)((long)param_2 + 0x1c) = param_3[1];
  uVar1 = param_3[2];
  *(undefined4 *)((long)param_2 + 0x3c) = 0x3f800000;
  *(undefined4 *)((long)param_2 + 0x2c) = uVar1;
  return;
}

// ==== Aska::Matrix::SetLookAtMatrixZP(Aska::Vector const*, Aska::Vector const*, float)
// vaddr 0x1f3bed0 | ghidra 0x203bed0 | size 1028 | symbol _ZN4Aska6Matrix17SetLookAtMatrixZPEPKNS_6VectorES3_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix17SetLookAtMatrixZPEPKNS_6VectorES3_f
               (float param_1,undefined8 *param_2,undefined4 *param_3,float *param_4)

{
  float *pfVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  bool bVar11;
  bool bVar12;
  bool bVar13;
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
  float fStack_120;
  float fStack_11c;
  undefined8 uStack_118;
  float fStack_110;
  float fStack_10c;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  
  uVar10 = _UNK_027dbb38;
  uVar9 = _UNK_027dbb30;
  uVar8 = _UNK_027dbb28;
  uVar7 = _UNK_027dbb20;
  uVar6 = _UNK_027dbb18;
  uVar5 = _UNK_027dbb10;
  uVar4 = _UNK_027dbb08;
  uVar3 = _UNK_027dbb00;
  uStack_b8 = _UNK_027dbb08;
  uStack_c0 = _UNK_027dbb00;
  uStack_a8 = _UNK_027dbb18;
  uStack_b0 = _UNK_027dbb10;
  uStack_98 = _UNK_027dbb28;
  uStack_a0 = _UNK_027dbb20;
  uStack_88 = _UNK_027dbb38;
  uStack_90 = _UNK_027dbb30;
  fVar19 = *param_4;
  if (fVar19 == 0.0) {
    fVar20 = param_4[1];
    if ((fVar20 == 0.0) && (param_4[2] == 0.0)) {
      param_2[1] = _UNK_027dbb08;
      *param_2 = uVar3;
      param_2[3] = uVar6;
      param_2[2] = uVar5;
      param_2[5] = uVar8;
      param_2[4] = uVar7;
      param_2[7] = uVar10;
      param_2[6] = uVar9;
      return;
    }
  }
  else {
    fVar20 = param_4[1];
  }
  uStack_d8 = _UNK_027f7c08;
  uStack_e0 = _UNK_027f7c00;
  uStack_c8 = _UNK_027ed898;
  uStack_d0 = _UNK_027ed890;
  fVar17 = param_4[2];
  fVar15 = fVar19 * fVar19 + fVar20 * fVar20 + fVar17 * fVar17;
  fVar14 = SQRT(fVar15);
  if (NAN(fVar14)) {
    fVar14 = (float)sqrtf(fVar15);
  }
  fVar15 = _UNK_027e519c;
  if (_UNK_027e519c <= fVar14) {
    fVar14 = 1.0 / fVar14;
    fVar20 = fVar14 * fVar20;
    fVar17 = fVar14 * fVar17;
    fVar19 = fVar14 * fVar19;
  }
  bVar11 = false;
  bVar12 = false;
  bVar13 = false;
  if (_UNK_02970ccc <= fVar20) {
    bVar11 = false;
    bVar12 = false;
    bVar13 = true;
    if (!NAN(fVar20) && !NAN(_UNK_02970cd0)) {
      bVar11 = fVar20 < _UNK_02970cd0;
      bVar12 = fVar20 == _UNK_02970cd0;
      bVar13 = false;
    }
  }
  pfVar1 = (float *)&uStack_e0;
  if (bVar12 || bVar11 != bVar13) {
    pfVar1 = (float *)&uStack_d0;
  }
  fVar23 = pfVar1[1] * param_4[2] - pfVar1[2] * param_4[1];
  fVar22 = pfVar1[2] * *param_4 - param_4[2] * *pfVar1;
  fVar21 = param_4[1] * *pfVar1 - pfVar1[1] * *param_4;
  fVar16 = fVar21 * fVar21 + fVar23 * fVar23 + fVar22 * fVar22;
  fVar14 = SQRT(fVar16);
  if (NAN(fVar14)) {
    fVar14 = (float)sqrtf(fVar16);
  }
  if (fVar15 <= fVar14) {
    fVar14 = 1.0 / fVar14;
    fVar23 = fVar23 * fVar14;
    fVar22 = fVar14 * fVar22;
    fVar21 = fVar14 * fVar21;
  }
  fVar25 = fVar21 * fVar20 - fVar22 * fVar17;
  fVar18 = fVar23 * fVar17 - fVar21 * fVar19;
  fVar24 = fVar22 * fVar19 - fVar23 * fVar20;
  fVar16 = fVar24 * fVar24 + fVar25 * fVar25 + fVar18 * fVar18;
  fVar14 = SQRT(fVar16);
  if (NAN(fVar14)) {
    fVar14 = (float)sqrtf(fVar16);
  }
  if (fVar15 <= fVar14) {
    fVar14 = 1.0 / fVar14;
    fVar25 = fVar14 * fVar25;
    fVar18 = fVar14 * fVar18;
    fVar24 = fVar24 * fVar14;
  }
  uStack_c0 = CONCAT44(fVar25,fVar23);
  uStack_b0 = CONCAT44(fVar18,fVar22);
  uStack_a0 = CONCAT44(fVar24,fVar21);
  uStack_b8 = CONCAT44(uStack_b8._4_4_,fVar19);
  uStack_a8 = CONCAT44(uStack_a8._4_4_,fVar20);
  uStack_98 = CONCAT44(uStack_98._4_4_,fVar17);
  if (param_1 == 0.0) {
    param_2[1] = uStack_b8;
    *param_2 = uStack_c0;
    param_2[3] = uStack_a8;
    param_2[2] = uStack_b0;
    param_2[5] = uStack_98;
    param_2[4] = uStack_a0;
    param_2[7] = uVar10;
    param_2[6] = uVar9;
  }
  else {
    uStack_108 = uVar6;
    uStack_f8 = uVar8;
    uStack_100 = uVar7;
    uStack_e8 = uVar10;
    uStack_f0 = uVar9;
    fVar20 = param_1 + (float)(int)(param_1 * _UNK_027ebdf4) * _UNK_027edb30;
    bVar11 = ((int)(param_1 * _UNK_027ebdf4) & 1U) != 0;
    fVar19 = fVar20;
    if (bVar11) {
      fVar19 = -fVar20;
    }
    fVar20 = fVar20 * fVar20;
    uStack_118 = uVar4;
    fVar17 = fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * _UNK_02964910 +
                                                                        _UNK_02964914) +
                                                              _UNK_02964918) + _UNK_0296491c) +
                                          _UNK_02964920) + _UNK_02964924) + -0.5);
    fVar14 = fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * _UNK_02964928 +
                                                                        _UNK_0296492c) +
                                                              _UNK_02964930) + _UNK_02964934) +
                                          _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) + 1.0;
    fVar20 = -1.0 - fVar17;
    if (!bVar11) {
      fVar20 = fVar17 + 1.0;
    }
    _fStack_120 = CONCAT44(fVar19 * fVar14,fVar20);
    _fStack_110 = CONCAT44(fVar20,-(fVar19 * fVar14));
    Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)(param_2,&uStack_c0,&fStack_120);
  }
  *(undefined4 *)((long)param_2 + 0xc) = *param_3;
  *(undefined4 *)((long)param_2 + 0x1c) = param_3[1];
  uVar2 = param_3[2];
  *(undefined4 *)((long)param_2 + 0x3c) = 0x3f800000;
  *(undefined4 *)((long)param_2 + 0x2c) = uVar2;
  return;
}

// ==== Aska::Matrix::SetLookAtMatrixZN(Aska::Vector const*, Aska::Vector const*, float)
// vaddr 0x1f3c2d4 | ghidra 0x203c2d4 | size 844 | symbol _ZN4Aska6Matrix17SetLookAtMatrixZNEPKNS_6VectorES3_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix17SetLookAtMatrixZNEPKNS_6VectorES3_f
               (float param_1,long param_2,undefined4 *param_3,float *param_4)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  bool bVar8;
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
  float fStack_e0;
  float fStack_dc;
  undefined8 uStack_d8;
  float fStack_d0;
  float fStack_cc;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb28;
  uVar4 = _UNK_027dbb20;
  uVar3 = _UNK_027dbb18;
  uVar2 = _UNK_027dbb08;
  uStack_98 = _UNK_027dbb08;
  uStack_a0 = _UNK_027dbb00;
  uStack_88 = _UNK_027dbb18;
  uStack_90 = _UNK_027dbb10;
  uStack_78 = _UNK_027dbb28;
  uStack_80 = _UNK_027dbb20;
  uStack_68 = _UNK_027dbb38;
  uStack_70 = _UNK_027dbb30;
  fVar12 = *param_4;
  fVar14 = param_4[1];
  fVar15 = param_4[2];
  fVar10 = fVar12 * fVar12 + fVar14 * fVar14 + fVar15 * fVar15;
  fVar9 = SQRT(fVar10);
  if (NAN(fVar9)) {
    fVar9 = (float)sqrtf(fVar10);
  }
  fVar10 = _UNK_027e519c;
  fVar12 = -fVar12;
  fVar14 = -fVar14;
  fVar15 = -fVar15;
  if (_UNK_027e519c <= fVar9) {
    fVar9 = 1.0 / fVar9;
    fVar12 = fVar9 * fVar12;
    fVar14 = fVar9 * fVar14;
    fVar15 = fVar9 * fVar15;
  }
  fVar20 = fVar15 - fVar14 * 0.0;
  fVar18 = fVar12 * 0.0 - fVar15 * 0.0;
  fVar19 = fVar14 * 0.0 - fVar12;
  fVar11 = fVar19 * fVar19 + fVar20 * fVar20 + fVar18 * fVar18;
  fVar9 = SQRT(fVar11);
  if (NAN(fVar9)) {
    fVar9 = (float)sqrtf(fVar11);
  }
  if (fVar10 <= fVar9) {
    fVar9 = 1.0 / fVar9;
    fVar20 = fVar20 * fVar9;
    fVar18 = fVar9 * fVar18;
    fVar19 = fVar19 * fVar9;
  }
  fVar16 = fVar14 * fVar19 - fVar15 * fVar18;
  fVar17 = fVar15 * fVar20 - fVar12 * fVar19;
  fVar13 = fVar12 * fVar18 - fVar14 * fVar20;
  fVar11 = fVar13 * fVar13 + fVar16 * fVar16 + fVar17 * fVar17;
  fVar9 = SQRT(fVar11);
  if (NAN(fVar9)) {
    fVar9 = (float)sqrtf(fVar11);
  }
  if (fVar10 <= fVar9) {
    fVar9 = 1.0 / fVar9;
    fVar16 = fVar9 * fVar16;
    fVar17 = fVar9 * fVar17;
    fVar13 = fVar13 * fVar9;
  }
  uStack_88 = CONCAT44(uStack_88._4_4_,fVar14);
  uStack_c8 = uVar3;
  uStack_a8 = uVar7;
  uStack_b0 = uVar6;
  uStack_d8 = uVar2;
  uStack_b8 = uVar5;
  uStack_c0 = uVar4;
  fVar10 = param_1 + (float)(int)(param_1 * _UNK_027ebdf4) * _UNK_027edb30;
  bVar8 = ((int)(param_1 * _UNK_027ebdf4) & 1U) != 0;
  fVar9 = fVar10;
  if (bVar8) {
    fVar9 = -fVar10;
  }
  fVar10 = fVar10 * fVar10;
  fVar14 = fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * _UNK_02964910 +
                                                                      _UNK_02964914) + _UNK_02964918
                                                            ) + _UNK_0296491c) + _UNK_02964920) +
                              _UNK_02964924) + -0.5);
  fVar11 = fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * _UNK_02964928 +
                                                                      _UNK_0296492c) + _UNK_02964930
                                                            ) + _UNK_02964934) + _UNK_02964938) +
                              _UNK_0296493c) + _UNK_02964940) + 1.0;
  fVar10 = -1.0 - fVar14;
  if (!bVar8) {
    fVar10 = fVar14 + 1.0;
  }
  uStack_a0 = CONCAT44(fVar16,fVar20);
  uStack_90 = CONCAT44(fVar17,fVar18);
  uStack_80 = CONCAT44(fVar13,fVar19);
  uStack_98 = CONCAT44(uStack_98._4_4_,fVar12);
  uStack_78 = CONCAT44(uStack_78._4_4_,fVar15);
  _fStack_e0 = CONCAT44(fVar9 * fVar11,fVar10);
  _fStack_d0 = CONCAT44(fVar10,-(fVar9 * fVar11));
  Aska::Matrix::Mul(Aska::Matrix const*, Aska::Matrix const*)(param_2,&uStack_a0,&fStack_e0);
  *(undefined4 *)(param_2 + 0xc) = *param_3;
  *(undefined4 *)(param_2 + 0x1c) = param_3[1];
  uVar1 = param_3[2];
  *(undefined4 *)(param_2 + 0x3c) = 0x3f800000;
  *(undefined4 *)(param_2 + 0x2c) = uVar1;
  return;
}

// ==== Aska::Matrix::SetProjectionShadowMatrixForOmniLight(Aska::Vector const*, Aska::Vector const*)
// vaddr 0x1f3c620 | ghidra 0x203c620 | size 308 | symbol _ZN4Aska6Matrix37SetProjectionShadowMatrixForOmniLightEPKNS_6VectorES3_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Matrix37SetProjectionShadowMatrixForOmniLightEPKNS_6VectorES3_
               (float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  
  fVar1 = *param_2 * *param_3 + param_2[1] * param_3[1] + param_2[2] * param_3[2] +
          param_2[3] * param_3[3];
  *param_1 = fVar1 - *param_2 * *param_3;
  param_1[1] = -(*param_2 * param_3[1]);
  param_1[2] = -(*param_2 * param_3[2]);
  param_1[3] = -(*param_2 * param_3[3]);
  param_1[4] = -(param_2[1] * *param_3);
  param_1[5] = fVar1 - param_2[1] * param_3[1];
  param_1[6] = -(param_2[1] * param_3[2]);
  param_1[7] = -(param_2[1] * param_3[3]);
  param_1[8] = -(param_2[2] * *param_3);
  param_1[9] = -(param_2[2] * param_3[1]);
  param_1[10] = fVar1 - param_2[2] * param_3[2];
  param_1[0xb] = -(param_2[2] * param_3[3]);
  param_1[0xc] = -(param_2[3] * *param_3);
  param_1[0xd] = -(param_2[3] * param_3[1]);
  param_1[0xe] = -(param_2[3] * param_3[2]);
  param_1[0xf] = fVar1 - param_2[3] * param_3[3];
  return;
}

// ==== Aska::Matrix::SetProjectionShadowMatrixForDirectionalLight(Aska::Vector const*, Aska::Vector const*)
// vaddr 0x1f3c754 | ghidra 0x203c754 | size 252 | symbol _ZN4Aska6Matrix44SetProjectionShadowMatrixForDirectionalLightEPKNS_6VectorES3_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Matrix44SetProjectionShadowMatrixForDirectionalLightEPKNS_6VectorES3_
               (float *param_1,float *param_2,float *param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  fVar7 = 1.0 / (*param_2 * *param_3 + param_2[1] * param_3[1] + param_2[2] * param_3[2]);
  fVar3 = *param_2 * fVar7;
  fVar4 = param_2[1] * fVar7;
  fVar7 = param_2[2] * fVar7;
  fVar5 = *param_3 * fVar3;
  fVar6 = param_3[3] * 0.0 + param_3[2] * fVar7 + fVar5 + param_3[1] * fVar4;
  *param_1 = fVar6 - fVar5;
  param_1[1] = -(param_3[1] * fVar3);
  param_1[2] = -(fVar3 * param_3[2]);
  param_1[3] = -(fVar3 * param_3[3]);
  param_1[4] = -(fVar4 * *param_3);
  param_1[5] = fVar6 - fVar4 * param_3[1];
  param_1[6] = -(fVar4 * param_3[2]);
  param_1[7] = -(fVar4 * param_3[3]);
  uVar2 = _UNK_027dbb38;
  uVar1 = _UNK_027dbb30;
  param_1[8] = -(fVar7 * *param_3);
  param_1[9] = -(fVar7 * param_3[1]);
  param_1[10] = fVar6 - fVar7 * param_3[2];
  fVar3 = param_3[3];
  *(undefined8 *)(param_1 + 0xe) = uVar2;
  *(undefined8 *)(param_1 + 0xc) = uVar1;
  param_1[0xb] = -(fVar7 * fVar3);
  return;
}

// ==== Aska::Matrix::PutPRS(Aska::Vector*, Aska::Quaternion*, Aska::Vector*) const
// vaddr 0x1f3c850 | ghidra 0x203c850 | size 872 | symbol _ZNK4Aska6Matrix6PutPRSEPNS_6VectorEPNS_10QuaternionES2_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK4Aska6Matrix6PutPRSEPNS_6VectorEPNS_10QuaternionES2_
               (float *param_1,float *param_2,long param_3,float *param_4)

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
  float fStack_e4;
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  undefined4 uStack_d4;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  undefined4 uStack_c4;
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  undefined4 uStack_b4;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  
  fVar6 = *param_1;
  fStack_e4 = param_1[1];
  fVar8 = param_1[4];
  fVar9 = param_1[5];
  fVar2 = param_1[8];
  fVar3 = param_1[9];
  fVar7 = param_1[2];
  fVar10 = param_1[6];
  fVar4 = param_1[10];
  if (param_4 != (float *)0x0) {
    fVar11 = SQRT(fVar6 * fVar6 + fVar8 * fVar8 + fVar2 * fVar2);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf();
    }
    fVar12 = SQRT(fStack_e4 * fStack_e4 + fVar9 * fVar9 + fVar3 * fVar3);
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf();
    }
    fVar5 = fVar7 * fVar7 + fVar10 * fVar10 + fVar4 * fVar4;
    fVar1 = SQRT(fVar5);
    if (NAN(fVar1)) {
      fVar1 = (float)sqrtf(fVar5);
    }
    fVar5 = 1.0;
    if (_UNK_027e519c <= ABS(fVar11 + -1.0)) {
      fVar5 = fVar11;
    }
    fVar11 = 1.0;
    if (_UNK_027e519c <= ABS(fVar12 + -1.0)) {
      fVar11 = fVar12;
    }
    fVar12 = 1.0;
    if (_UNK_027e519c <= ABS(fVar1 + -1.0)) {
      fVar12 = fVar1;
    }
    *param_4 = fVar5;
    param_4[1] = fVar11;
    param_4[2] = fVar12;
    param_4[3] = 1.0;
  }
  if (param_3 != 0) {
    fVar12 = fVar6 * fVar6 + fVar8 * fVar8 + fVar2 * fVar2;
    fVar11 = SQRT(fVar12);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar12);
    }
    fVar12 = _UNK_027e519c;
    if (_UNK_027e519c <= fVar11) {
      fVar11 = 1.0 / fVar11;
      fVar6 = fVar11 * fVar6;
      fVar8 = fVar11 * fVar8;
      fVar2 = fVar11 * fVar2;
    }
    fVar1 = fStack_e4 * fStack_e4 + fVar9 * fVar9 + fVar3 * fVar3;
    fVar11 = SQRT(fVar1);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar1);
    }
    if (fVar12 <= fVar11) {
      fVar11 = 1.0 / fVar11;
      fStack_e4 = fVar11 * fStack_e4;
      fVar9 = fVar11 * fVar9;
      fVar3 = fVar11 * fVar3;
    }
    fVar1 = fVar7 * fVar7 + fVar10 * fVar10 + fVar4 * fVar4;
    fVar11 = SQRT(fVar1);
    if (NAN(fVar11)) {
      fVar11 = (float)sqrtf(fVar1);
    }
    if (fVar12 <= fVar11) {
      fVar11 = 1.0 / fVar11;
      fVar7 = fVar11 * fVar7;
      fVar10 = fVar11 * fVar10;
      fVar4 = fVar11 * fVar4;
    }
    uStack_a8 = _UNK_027dbb38;
    uStack_b0 = _UNK_027dbb30;
    _fStack_d0 = CONCAT44(fVar9,fVar8);
    _fStack_c0 = CONCAT44(fVar3,fVar2);
    _fStack_e0 = CONCAT44(fStack_e4,fVar6);
    _fStack_d8 = CONCAT44((int)((ulong)_UNK_027dbb08 >> 0x20),fVar7);
    _fStack_c8 = CONCAT44((int)((ulong)_UNK_027dbb18 >> 0x20),fVar10);
    _fStack_b8 = CONCAT44((int)((ulong)_UNK_027dbb28 >> 0x20),fVar4);
    Aska::Quaternion::Create(Aska::Matrix const*)(param_3,&fStack_e0);
  }
  if (param_2 != (float *)0x0) {
    fVar6 = param_1[7];
    fVar8 = param_1[0xb];
    *param_2 = param_1[3];
    param_2[1] = fVar6;
    param_2[2] = fVar8;
    param_2[3] = 1.0;
  }
  return;
}

// ==== Aska::Matrix::CalcEuler(Aska::Vector*, EnumRotateType) const
// vaddr 0x1f3fe34 | ghidra 0x203fe34 | size 2004 | symbol _ZNK4Aska6Matrix9CalcEulerEPNS_6VectorE14EnumRotateType | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK4Aska6Matrix9CalcEulerEPNS_6VectorE14EnumRotateType
               (ulong *param_1,uint *param_2,undefined4 param_3)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  ulong uVar9;
  float fVar10;
  ulong uVar11;
  float fVar12;
  ulong uVar13;
  float fVar14;
  ulong uVar15;
  float fVar16;
  ulong uVar17;
  
  uVar11 = param_1[1];
  uVar9 = *param_1;
  fVar2 = (float)param_1[3];
  uVar17 = param_1[2];
  uVar15 = param_1[5];
  uVar13 = param_1[4];
  fVar7 = (float)(uVar9 >> 0x20);
  fVar6 = (float)uVar9;
  fVar10 = (float)uVar11;
  fVar5 = fVar10 * fVar10 + fVar6 * fVar6 + fVar7 * fVar7;
  fVar1 = SQRT(fVar5);
  if (NAN(fVar1)) {
    fVar1 = (float)sqrtf(fVar5);
  }
  fVar5 = _UNK_027e519c;
  if (_UNK_027e519c <= fVar1) {
    fVar1 = 1.0 / fVar1;
    uVar9 = CONCAT44(fVar7 * fVar1,fVar6 * fVar1);
    uVar11 = (ulong)(uint)(fVar10 * fVar1);
  }
  fVar10 = (float)(uVar17 >> 0x20);
  fVar7 = (float)uVar17;
  fVar6 = fVar2 * fVar2 + fVar7 * fVar7 + fVar10 * fVar10;
  fVar1 = SQRT(fVar6);
  if (NAN(fVar1)) {
    fVar1 = (float)sqrtf(fVar6);
  }
  fVar6 = (float)uVar11;
  if (fVar5 <= fVar1) {
    fVar1 = 1.0 / fVar1;
    uVar17 = CONCAT44(fVar10 * fVar1,fVar7 * fVar1);
    fVar2 = fVar2 * fVar1;
  }
  fVar14 = (float)(uVar13 >> 0x20);
  fVar10 = (float)uVar13;
  fVar4 = (float)uVar15;
  fVar7 = fVar4 * fVar4 + fVar10 * fVar10 + fVar14 * fVar14;
  fVar1 = SQRT(fVar7);
  if (NAN(fVar1)) {
    fVar1 = (float)sqrtf(fVar7);
  }
  if (fVar5 <= fVar1) {
    fVar1 = 1.0 / fVar1;
    uVar13 = CONCAT44(fVar14 * fVar1,fVar10 * fVar1);
    uVar15 = (ulong)(uint)(fVar4 * fVar1);
  }
  fVar7 = (float)uVar9;
  fVar10 = (float)(uVar9 >> 0x20);
  fVar14 = (float)(uVar13 >> 0x20);
  fVar1 = (float)uVar15;
  if (((((fVar7 + -1.0 < fVar5) && (_UNK_02970cd4 < fVar7 + -1.0)) && (fVar10 < fVar5)) &&
      ((_UNK_02970cd4 < fVar10 && (fVar6 < fVar5)))) && (_UNK_02970cd4 < fVar6)) {
    uVar3 = atan2f(fVar14,uVar15 & 0xffffffff);
    fVar4 = 0.0;
code_r0x020405d8:
    fVar5 = 0.0;
    goto code_r0x020405e0;
  }
  fVar8 = (float)(uVar17 >> 0x20);
  fVar16 = (float)uVar17;
  if (((fVar8 + -1.0 < fVar5) && (_UNK_02970cd4 < fVar8 + -1.0)) &&
     ((fVar16 < fVar5 && (((_UNK_02970cd4 < fVar16 && (fVar2 < fVar5)) && (_UNK_02970cd4 < fVar2))))
     )) {
    fVar4 = (float)atan2f(fVar6,uVar9);
    uVar3 = 0;
    fVar5 = 0.0;
    goto code_r0x020405e0;
  }
  fVar12 = (float)uVar13;
  if ((((fVar1 + -1.0 < fVar5) && (_UNK_02970cd4 < fVar1 + -1.0)) &&
      ((fVar12 < fVar5 && ((_UNK_02970cd4 < fVar12 && (fVar14 < fVar5)))))) &&
     (_UNK_02970cd4 < fVar14)) {
    fVar5 = (float)atan2f(uVar17,fVar8);
    uVar3 = 0;
    fVar4 = 0.0;
    goto code_r0x020405e0;
  }
  switch(param_3) {
  case 1:
    fVar5 = (float)asinf(uVar17);
    fVar6 = (float)cosf();
    if (fVar6 == 0.0) {
code_r0x02040484:
      uVar3 = 0;
      fVar4 = 0.0;
      goto code_r0x020405e0;
    }
    fVar7 = fVar7 / fVar6;
    fVar1 = 1.0;
    if ((fVar7 <= 1.0) && (fVar1 = fVar7, fVar7 < -1.0)) {
      fVar1 = -1.0;
    }
    fVar1 = (float)acosf(fVar1);
    fVar8 = fVar8 / fVar6;
    fVar4 = -fVar1;
    if (fVar6 * fVar12 <= 0.0) {
      fVar4 = fVar1;
    }
    fVar1 = 1.0;
    if ((fVar8 <= 1.0) && (fVar1 = fVar8, fVar8 < -1.0)) {
      fVar1 = -1.0;
    }
    uVar3 = acosf(fVar1);
    break;
  case 2:
    fVar5 = (float)asinf(fVar10);
    fVar5 = -fVar5;
    fVar2 = (float)cosf();
    if (fVar2 == 0.0) goto code_r0x02040484;
    fVar7 = fVar7 / fVar2;
    fVar1 = 1.0;
    if ((fVar7 <= 1.0) && (fVar1 = fVar7, fVar7 < -1.0)) {
      fVar1 = -1.0;
    }
    fVar1 = (float)acosf(fVar1);
    fVar8 = fVar8 / fVar2;
    fVar4 = -fVar1;
    if (0.0 <= fVar2 * fVar6) {
      fVar4 = fVar1;
    }
    fVar6 = 1.0;
    if ((fVar8 <= 1.0) && (fVar6 = fVar8, fVar8 < -1.0)) {
      fVar6 = -1.0;
    }
    goto code_r0x020405a8;
  case 3:
    uVar3 = asinf(fVar14);
    fVar2 = (float)cosf();
    if (fVar2 == 0.0) {
code_r0x02040490:
      fVar4 = 0.0;
      fVar5 = 0.0;
      goto code_r0x020405e0;
    }
    fVar8 = fVar8 / fVar2;
    fVar5 = 1.0;
    if ((fVar8 <= 1.0) && (fVar5 = fVar8, fVar8 < -1.0)) {
      fVar5 = -1.0;
    }
    fVar7 = (float)acosf(fVar5);
    fVar6 = _UNK_027f7cb8;
    fVar1 = fVar1 / fVar2;
    fVar5 = -fVar7;
    if (fVar2 * fVar10 <= _UNK_027f7cb8) {
      fVar5 = fVar7;
    }
    fVar7 = 1.0;
    if ((fVar1 <= 1.0) && (fVar7 = fVar1, fVar1 < -1.0)) {
      fVar7 = -1.0;
    }
    fVar4 = (float)acosf(fVar7);
    if (fVar2 * fVar12 <= fVar6) goto code_r0x020405e0;
    goto code_r0x020402b4;
  case 4:
    uVar3 = asinf(fVar2);
    uVar3 = uVar3 ^ 0x80000000;
    fVar2 = (float)cosf();
    if (fVar2 == 0.0) goto code_r0x02040490;
    fVar8 = fVar8 / fVar2;
    fVar5 = 1.0;
    if ((fVar8 <= 1.0) && (fVar5 = fVar8, fVar8 < -1.0)) {
      fVar5 = -1.0;
    }
    fVar7 = (float)acosf(fVar5);
    fVar1 = fVar1 / fVar2;
    fVar5 = -fVar7;
    if (0.0 <= fVar2 * fVar16) {
      fVar5 = fVar7;
    }
    fVar7 = 1.0;
    if ((fVar1 <= 1.0) && (fVar7 = fVar1, fVar1 < -1.0)) {
      fVar7 = -1.0;
    }
    fVar4 = (float)acosf(fVar7);
    if (0.0 <= fVar2 * fVar6) goto code_r0x020405e0;
code_r0x020402b4:
    fVar4 = -fVar4;
    goto code_r0x020405e0;
  case 5:
    fVar4 = (float)asinf(fVar6);
    fVar6 = (float)cosf();
    if (fVar6 == 0.0) {
      uVar3 = 0;
      fVar5 = 0.0;
      goto code_r0x020405e0;
    }
    fVar7 = fVar7 / fVar6;
    fVar5 = 1.0;
    if ((fVar7 <= 1.0) && (fVar5 = fVar7, fVar7 < -1.0)) {
      fVar5 = -1.0;
    }
    fVar7 = (float)acosf(fVar5);
    fVar1 = fVar1 / fVar6;
    fVar5 = -fVar7;
    if (fVar6 * fVar10 <= 0.0) {
      fVar5 = fVar7;
    }
    fVar7 = 1.0;
    if ((fVar1 <= 1.0) && (fVar7 = fVar1, fVar1 < -1.0)) {
      fVar7 = -1.0;
    }
    uVar3 = acosf(fVar7);
    break;
  default:
    fVar2 = fVar12;
    if (fVar12 < 0.0) {
      fVar2 = -fVar12;
    }
    fVar4 = 0.0;
    if (fVar2 <= 1.0) {
      if (_UNK_02970cd8 <= fVar2) {
        fVar2 = fVar2 + _UNK_02970cdc;
        fVar6 = fVar2 * (fVar2 * (fVar2 * (fVar2 * _UNK_02970ce0 + _UNK_02970ce4) + _UNK_02970ce8) +
                        _UNK_02970cec) + _UNK_02970cf0;
        fVar2 = fVar2 * _UNK_02970cf4;
      }
      else {
        fVar6 = fVar2 * (fVar2 * (fVar2 * (fVar2 * _UNK_02970cf8 + _UNK_02970cfc) + _UNK_02970d00) +
                        _UNK_02970d04);
        fVar2 = fVar2 * _UNK_02970d08;
      }
      fVar4 = (float)((uint)fVar12 & 0x80000000 | (uint)(fVar6 / (1.0 - fVar2)));
    }
    fVar4 = -fVar4;
    fVar2 = (float)cosf();
    if (ABS(fVar2) <= fVar5) {
      uVar3 = atan2f(uVar9 >> 0x20,uVar11 & 0xffffffff);
      goto code_r0x020405d8;
    }
    fVar7 = fVar7 / fVar2;
    fVar5 = 1.0;
    if ((fVar7 <= 1.0) && (fVar5 = fVar7, fVar7 < -1.0)) {
      fVar5 = -1.0;
    }
    fVar6 = (float)acosf(fVar5);
    fVar1 = fVar1 / fVar2;
    fVar5 = -fVar6;
    if (0.0 <= fVar2 * fVar16) {
      fVar5 = fVar6;
    }
    fVar6 = 1.0;
    if ((fVar1 <= 1.0) && (fVar6 = fVar1, fVar1 < -1.0)) {
      fVar6 = -1.0;
    }
code_r0x020405a8:
    uVar3 = acosf(fVar6);
    if (0.0 <= fVar2 * fVar14) goto code_r0x020405e0;
    goto code_r0x020405bc;
  }
  if (0.0 < fVar6 * fVar2) {
code_r0x020405bc:
    uVar3 = uVar3 ^ 0x80000000;
  }
code_r0x020405e0:
  *param_2 = uVar3;
  param_2[1] = (uint)fVar4;
  param_2[2] = (uint)fVar5;
  return;
}

// ==== Aska::Matrix::InvertLowError()
// vaddr 0x20e8d80 | ghidra 0x21e8d80 | size 844 | symbol _ZN4Aska6Matrix14InvertLowErrorEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN4Aska6Matrix14InvertLowErrorEv(float *param_1)

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
  
  fVar1 = _UNK_027e519c;
  fVar2 = param_1[4];
  fVar3 = param_1[5];
  fVar9 = *param_1;
  fVar8 = param_1[1];
  fVar17 = param_1[0xc];
  fVar14 = param_1[0xd];
  fVar19 = param_1[8];
  fVar15 = param_1[9];
  fVar21 = param_1[0xe];
  fVar25 = param_1[0xf];
  fVar22 = param_1[10];
  fVar23 = param_1[0xb];
  fVar4 = param_1[6];
  fVar6 = param_1[7];
  fVar7 = param_1[2];
  fVar5 = param_1[3];
  fVar28 = fVar9 * fVar3 - fVar8 * fVar2;
  fVar18 = fVar19 * fVar25 - fVar17 * fVar23;
  fVar16 = fVar15 * fVar25 - fVar14 * fVar23;
  fVar20 = fVar22 * fVar25 - fVar21 * fVar23;
  fVar29 = fVar9 * fVar4 - fVar2 * fVar7;
  fVar23 = fVar9 * fVar6 - fVar2 * fVar5;
  fVar30 = fVar8 * fVar4 - fVar3 * fVar7;
  fVar31 = fVar7 * fVar6 - fVar4 * fVar5;
  fVar32 = fVar19 * fVar14 - fVar15 * fVar17;
  fVar17 = fVar19 * fVar21 - fVar17 * fVar22;
  fVar19 = fVar15 * fVar21 - fVar14 * fVar22;
  fVar15 = fVar8 * fVar6 - fVar3 * fVar5;
  fVar9 = fVar31 * fVar32 +
          ((fVar30 * fVar18 + fVar23 * fVar19 + (fVar28 * fVar20 - fVar29 * fVar16)) -
          fVar15 * fVar17);
  fVar21 = ABS(fVar9);
  fVar8 = *param_1;
  fVar14 = param_1[1];
  fVar9 = 1.0 / fVar9;
  fVar22 = param_1[2];
  if (fVar21 <= _UNK_027e519c) {
    fVar9 = 1.0;
  }
  fVar24 = param_1[0xc];
  fVar26 = param_1[0xd];
  fVar27 = param_1[0xe];
  fVar10 = param_1[8];
  fVar11 = param_1[9];
  fVar12 = param_1[10];
  fVar13 = param_1[0xb];
  *(ulong *)(param_1 + 2) =
       CONCAT44(fVar9 * ((fVar15 * fVar12 - fVar31 * fVar11) - fVar30 * fVar13),
                fVar9 * ((fVar31 * fVar26 - fVar15 * fVar27) + fVar30 * fVar25));
  *(ulong *)param_1 =
       CONCAT44(fVar9 * ((fVar16 * fVar7 - fVar20 * fVar14) - fVar19 * fVar5),
                fVar9 * ((fVar3 * fVar20 - fVar16 * fVar4) + fVar19 * fVar6));
  *(ulong *)(param_1 + 6) =
       CONCAT44(fVar9 * ((fVar31 * fVar10 - fVar23 * fVar12) + fVar29 * fVar13),
                fVar9 * ((fVar23 * fVar27 - fVar31 * fVar24) - fVar29 * param_1[0xf]));
  *(ulong *)(param_1 + 4) =
       CONCAT44(fVar9 * ((fVar20 * fVar8 - fVar18 * fVar22) + fVar17 * param_1[3]),
                fVar9 * ((fVar18 * fVar4 - fVar20 * fVar2) - fVar17 * fVar6));
  *(ulong *)(param_1 + 10) =
       CONCAT44(fVar9 * ((fVar23 * fVar11 - fVar15 * fVar10) - fVar28 * fVar13),
                fVar9 * ((fVar15 * fVar24 - fVar23 * fVar26) + fVar28 * param_1[0xf]));
  *(ulong *)(param_1 + 8) =
       CONCAT44(fVar9 * ((fVar18 * fVar14 - fVar16 * fVar8) - fVar32 * param_1[3]),
                fVar9 * ((fVar16 * fVar2 - fVar18 * fVar3) + fVar32 * fVar6));
  *(ulong *)(param_1 + 0xe) =
       CONCAT44(fVar9 * ((fVar30 * fVar10 - fVar29 * fVar11) + fVar28 * fVar12),
                fVar9 * ((fVar29 * fVar26 - fVar30 * fVar24) - fVar28 * fVar27));
  *(ulong *)(param_1 + 0xc) =
       CONCAT44(fVar9 * ((fVar19 * fVar8 - fVar17 * fVar14) + fVar32 * fVar22),
                fVar9 * ((fVar17 * param_1[5] - fVar19 * fVar2) - fVar32 * fVar4));
  return fVar1 < fVar21;
}

// ==== Aska::Matrix::Lerp(Aska::Matrix const*, Aska::Matrix const*, float)
// vaddr 0x20eb5c0 | ghidra 0x21eb5c0 | size 388 | symbol _ZN4Aska6Matrix4LerpEPKS0_S2_f | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Matrix4LerpEPKS0_S2_f(float param_1,float *param_2,float *param_3,float *param_4)

{
  *param_2 = *param_3 + (*param_4 - *param_3) * param_1;
  param_2[1] = param_3[1] + (param_4[1] - param_3[1]) * param_1;
  param_2[2] = param_3[2] + (param_4[2] - param_3[2]) * param_1;
  param_2[3] = param_3[3] + (param_4[3] - param_3[3]) * param_1;
  param_2[4] = param_3[4] + (param_4[4] - param_3[4]) * param_1;
  param_2[5] = param_3[5] + (param_4[5] - param_3[5]) * param_1;
  param_2[6] = param_3[6] + (param_4[6] - param_3[6]) * param_1;
  param_2[7] = param_3[7] + (param_4[7] - param_3[7]) * param_1;
  param_2[8] = param_3[8] + (param_4[8] - param_3[8]) * param_1;
  param_2[9] = param_3[9] + (param_4[9] - param_3[9]) * param_1;
  param_2[10] = param_3[10] + (param_4[10] - param_3[10]) * param_1;
  param_2[0xb] = param_3[0xb] + (param_4[0xb] - param_3[0xb]) * param_1;
  param_2[0xc] = param_3[0xc] + (param_4[0xc] - param_3[0xc]) * param_1;
  param_2[0xd] = param_3[0xd] + (param_4[0xd] - param_3[0xd]) * param_1;
  param_2[0xe] = param_3[0xe] + (param_4[0xe] - param_3[0xe]) * param_1;
  param_2[0xf] = param_3[0xf] + (param_4[0xf] - param_3[0xf]) * param_1;
  return;
}


// FAILED to create function at 02970d70 Aska::Matrix::s_unitMatrix
