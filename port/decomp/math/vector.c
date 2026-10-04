// port/decomp/math/vector.c: Ghidra decompiles for the math subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:09 UTC: tools/decomp.sh '--into' 'math/vector' 'Aska::Vector::'

// ==== Aska::Vector::ApplyMatrix(Aska::Matrix const*)
// vaddr 0x1f8c4e4 | ghidra 0x208c4e4 | size 172 | symbol _ZN4Aska6Vector11ApplyMatrixEPKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Vector11ApplyMatrixEPKNS_6MatrixE(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar1 = *param_1;
  fVar2 = param_1[1];
  fVar3 = param_1[2];
  fVar4 = param_1[3];
  *param_1 = fVar1 * *param_2 + fVar2 * param_2[1] + fVar3 * param_2[2] + fVar4 * param_2[3];
  param_1[1] = fVar1 * param_2[4] + fVar2 * param_2[5] + fVar3 * param_2[6] + fVar4 * param_2[7];
  param_1[2] = fVar1 * param_2[8] + fVar2 * param_2[9] + fVar3 * param_2[10] + fVar4 * param_2[0xb];
  param_1[3] = fVar1 * param_2[0xc] + fVar2 * param_2[0xd] + fVar3 * param_2[0xe] +
               fVar4 * param_2[0xf];
  return;
}

// ==== Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const
// vaddr 0x1f8c590 | ghidra 0x208c590 | size 120 | symbol _ZNK4Aska6Vector11ApplyMatrixEPS0_PKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
undefined1  [12]
_ZNK4Aska6Vector11ApplyMatrixEPS0_PKNS_6MatrixE
          (undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  float fVar5;
  float fVar7;
  float fVar8;
  undefined1 auVar6 [12];
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
  undefined8 uVar22;
  undefined8 uVar23;
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  undefined8 uVar26;
  undefined8 uVar27;
  undefined1 auVar28 [16];
  undefined1 auVar29 [16];
  
  fVar8 = (float)param_1[1];
  fVar9 = (float)((ulong)param_1[1] >> 0x20);
  fVar5 = (float)*param_1;
  fVar7 = (float)((ulong)*param_1 >> 0x20);
  fVar14 = fVar5 * (float)param_3[2];
  fVar15 = fVar7 * (float)((ulong)param_3[2] >> 0x20);
  fVar16 = fVar8 * (float)param_3[3];
  fVar17 = fVar9 * (float)((ulong)param_3[3] >> 0x20);
  fVar10 = fVar5 * (float)*param_3;
  fVar11 = fVar7 * (float)((ulong)*param_3 >> 0x20);
  fVar12 = fVar8 * (float)param_3[1];
  fVar13 = fVar9 * (float)((ulong)param_3[1] >> 0x20);
  fVar18 = fVar5 * (float)param_3[4];
  fVar19 = fVar7 * (float)((ulong)param_3[4] >> 0x20);
  fVar20 = fVar8 * (float)param_3[5];
  fVar21 = fVar9 * (float)((ulong)param_3[5] >> 0x20);
  fVar5 = fVar5 * *(float *)(param_3 + 6);
  fVar7 = fVar7 * *(float *)((long)param_3 + 0x34);
  fVar9 = fVar9 * *(float *)((long)param_3 + 0x3c);
  auVar28._4_4_ = fVar15;
  auVar28._0_4_ = fVar14;
  auVar28._8_4_ = fVar16;
  auVar28._12_4_ = fVar17;
  auVar2._4_4_ = fVar15;
  auVar2._0_4_ = fVar14;
  auVar2._8_4_ = fVar16;
  auVar2._12_4_ = fVar17;
  auVar28 = NEON_ext(auVar28,auVar2,8,1);
  auVar24._4_4_ = fVar11;
  auVar24._0_4_ = fVar10;
  auVar24._8_4_ = fVar12;
  auVar24._12_4_ = fVar13;
  auVar1._4_4_ = fVar11;
  auVar1._0_4_ = fVar10;
  auVar1._8_4_ = fVar12;
  auVar1._12_4_ = fVar13;
  auVar24 = NEON_ext(auVar24,auVar1,8,1);
  auVar25._4_4_ = fVar7;
  auVar25._0_4_ = fVar5;
  auVar25._8_4_ = fVar8 * *(float *)(param_3 + 7);
  auVar25._12_4_ = fVar9;
  auVar29._4_4_ = fVar7;
  auVar29._0_4_ = fVar5;
  auVar29._8_4_ = fVar8 * *(float *)(param_3 + 7);
  auVar29._12_4_ = fVar9;
  auVar29 = NEON_ext(auVar25,auVar29,8,1);
  auVar3._4_4_ = fVar19;
  auVar3._0_4_ = fVar18;
  auVar3._8_4_ = fVar20;
  auVar3._12_4_ = fVar21;
  auVar4._4_4_ = fVar19;
  auVar4._0_4_ = fVar18;
  auVar4._8_4_ = fVar20;
  auVar4._12_4_ = fVar21;
  auVar25 = NEON_ext(auVar3,auVar4,8,1);
  uVar26 = NEON_rev64(CONCAT44(auVar28._0_4_ + auVar28._4_4_,fVar14 + fVar15),4);
  uVar22 = NEON_rev64(CONCAT44(auVar24._0_4_ + auVar24._4_4_,fVar10 + fVar11),4);
  uVar23 = NEON_rev64(CONCAT44(auVar25._0_4_ + auVar25._4_4_,fVar18 + fVar19),4);
  uVar27 = NEON_rev64(CONCAT44(auVar29._0_4_ + auVar29._4_4_,fVar5 + fVar7),4);
  auVar6._0_4_ = fVar5 + fVar7 + (float)uVar27;
  uVar23 = CONCAT44(auVar6._0_4_,fVar18 + fVar19 + (float)uVar23);
  param_2[1] = uVar23;
  *param_2 = CONCAT44(fVar14 + fVar15 + (float)uVar26,fVar10 + fVar11 + (float)uVar22);
  auVar6._4_4_ = auVar6._0_4_;
  auVar6._8_4_ = auVar6._0_4_;
  return auVar6;
}

// ==== Aska::Vector::ApplyMatrixNoWeighted(Aska::Matrix const*)
// vaddr 0x1f8c608 | ghidra 0x208c608 | size 128 | symbol _ZN4Aska6Vector21ApplyMatrixNoWeightedEPKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Vector21ApplyMatrixNoWeightedEPKNS_6MatrixE(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  fVar1 = *param_1;
  fVar2 = param_1[1];
  fVar3 = param_1[2];
  *param_1 = param_2[3] + fVar1 * *param_2 + fVar2 * param_2[1] + fVar3 * param_2[2];
  param_1[1] = param_2[7] + fVar1 * param_2[4] + fVar2 * param_2[5] + fVar3 * param_2[6];
  fVar4 = param_2[8];
  fVar6 = param_2[9];
  fVar5 = param_2[10];
  fVar7 = param_2[0xb];
  param_1[3] = 1.0;
  param_1[2] = fVar7 + fVar1 * fVar4 + fVar2 * fVar6 + fVar3 * fVar5;
  return;
}

// ==== Aska::Vector::ApplyMatrixNoWeighted(Aska::Vector*, Aska::Matrix const*) const
// vaddr 0x1f8c688 | ghidra 0x208c688 | size 124 | symbol _ZNK4Aska6Vector21ApplyMatrixNoWeightedEPS0_PKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska6Vector21ApplyMatrixNoWeightedEPS0_PKNS_6MatrixE
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
  
  fVar1 = *param_1;
  fVar2 = param_1[1];
  fVar4 = param_3[4];
  fVar5 = param_3[5];
  fVar8 = param_3[8];
  fVar10 = param_3[9];
  fVar3 = param_1[2];
  fVar6 = param_3[6];
  fVar7 = param_3[7];
  fVar9 = param_3[10];
  fVar11 = param_3[0xb];
  *param_2 = param_3[3] + *param_3 * fVar1 + param_3[1] * fVar2 + param_3[2] * fVar3;
  param_2[1] = fVar7 + fVar1 * fVar4 + fVar2 * fVar5 + fVar3 * fVar6;
  param_2[2] = fVar11 + fVar1 * fVar8 + fVar2 * fVar10 + fVar3 * fVar9;
  param_2[3] = 1.0;
  return;
}

// ==== Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)
// vaddr 0x1f8c704 | ghidra 0x208c704 | size 116 | symbol _ZN4Aska6Vector22ApplyMatrixNoTransportEPKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Vector22ApplyMatrixNoTransportEPKNS_6MatrixE(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar1 = *param_1;
  fVar2 = param_1[1];
  fVar3 = param_1[2];
  *param_1 = fVar1 * *param_2 + fVar2 * param_2[1] + fVar3 * param_2[2];
  param_1[1] = fVar1 * param_2[4] + fVar2 * param_2[5] + fVar3 * param_2[6];
  fVar4 = param_2[8];
  fVar5 = param_2[9];
  fVar6 = param_2[10];
  param_1[3] = 1.0;
  param_1[2] = fVar1 * fVar4 + fVar2 * fVar5 + fVar3 * fVar6;
  return;
}

// ==== Aska::Vector::ApplyMatrixNoTransport(Aska::Vector*, Aska::Matrix const*) const
// vaddr 0x1f8c778 | ghidra 0x208c778 | size 112 | symbol _ZNK4Aska6Vector22ApplyMatrixNoTransportEPS0_PKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska6Vector22ApplyMatrixNoTransportEPS0_PKNS_6MatrixE
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
  
  fVar1 = *param_1;
  fVar2 = param_1[1];
  fVar4 = param_3[4];
  fVar5 = param_3[5];
  fVar7 = param_3[8];
  fVar9 = param_3[9];
  fVar3 = param_1[2];
  fVar6 = param_3[6];
  fVar8 = param_3[10];
  *param_2 = *param_3 * fVar1 + param_3[1] * fVar2 + param_3[2] * fVar3;
  param_2[1] = fVar1 * fVar4 + fVar2 * fVar5 + fVar3 * fVar6;
  param_2[2] = fVar1 * fVar7 + fVar2 * fVar9 + fVar3 * fVar8;
  param_2[3] = 1.0;
  return;
}

// ==== Aska::Vector::ApplyQuaternion(Aska::Quaternion const*)
// vaddr 0x1f8c7e8 | ghidra 0x208c7e8 | size 216 | symbol _ZN4Aska6Vector15ApplyQuaternionEPKNS_10QuaternionE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6Vector15ApplyQuaternionEPKNS_10QuaternionE(float *param_1,float *param_2)

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
  fVar2 = param_2[1];
  fVar4 = param_2[2];
  fVar6 = param_2[3];
  fVar8 = *param_1;
  fVar9 = param_1[1];
  fVar10 = param_1[2];
  fVar7 = fVar1 * fVar2 - fVar4 * fVar6;
  fVar12 = fVar1 * fVar2 + fVar4 * fVar6;
  fVar13 = fVar1 * fVar4 + fVar2 * fVar6;
  fVar3 = fVar1 * fVar4 - fVar2 * fVar6;
  fVar5 = fVar2 * fVar4 - fVar1 * fVar6;
  fVar6 = fVar2 * fVar4 + fVar1 * fVar6;
  fVar11 = fVar1 * fVar1 + fVar4 * fVar4;
  fVar1 = fVar1 * fVar1 + fVar2 * fVar2;
  *param_1 = (fVar13 + fVar13) * fVar10 +
             fVar8 * ((fVar2 * fVar2 + fVar4 * fVar4) * -2.0 + 1.0) + fVar9 * (fVar7 + fVar7);
  param_1[1] = (fVar5 + fVar5) * fVar10 +
               fVar8 * (fVar12 + fVar12) + fVar9 * (1.0 - (fVar11 + fVar11));
  param_1[2] = (1.0 - (fVar1 + fVar1)) * fVar10 + fVar8 * (fVar3 + fVar3) + fVar9 * (fVar6 + fVar6);
  return;
}

// ==== Aska::Vector::ApplyQuaternion(Aska::Vector*, Aska::Quaternion const*) const
// vaddr 0x1f8c8c0 | ghidra 0x208c8c0 | size 236 | symbol _ZNK4Aska6Vector15ApplyQuaternionEPS0_PKNS_10QuaternionE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska6Vector15ApplyQuaternionEPS0_PKNS_10QuaternionE
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
  
  fVar1 = *param_3;
  fVar3 = param_3[1];
  fVar5 = param_3[2];
  fVar6 = param_3[3];
  fVar7 = fVar1 * fVar3 - fVar5 * fVar6;
  fVar9 = fVar1 * fVar3 + fVar5 * fVar6;
  fVar10 = fVar1 * fVar5 + fVar3 * fVar6;
  fVar8 = fVar1 * fVar1 + fVar5 * fVar5;
  fVar2 = fVar1 * fVar5 - fVar3 * fVar6;
  fVar4 = fVar3 * fVar5 - fVar1 * fVar6;
  fVar6 = fVar3 * fVar5 + fVar1 * fVar6;
  fVar1 = fVar1 * fVar1 + fVar3 * fVar3;
  *param_2 = (fVar10 + fVar10) * param_1[2] +
             *param_1 * ((fVar3 * fVar3 + fVar5 * fVar5) * -2.0 + 1.0) +
             param_1[1] * (fVar7 + fVar7);
  param_2[1] = (fVar9 + fVar9) * *param_1 + (1.0 - (fVar8 + fVar8)) * param_1[1] +
               (fVar4 + fVar4) * param_1[2];
  param_2[2] = (fVar2 + fVar2) * *param_1 + (fVar6 + fVar6) * param_1[1] +
               (1.0 - (fVar1 + fVar1)) * param_1[2];
  return;
}

// ==== Aska::Vector::GetEuler(Aska::Matrix const*)
// vaddr 0x1f8c9ac | ghidra 0x208c9ac | size 1008 | symbol _ZN4Aska6Vector8GetEulerEPKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6Vector8GetEulerEPKNS_6MatrixE(float *param_1,long param_2)

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
  undefined8 uVar10;
  undefined8 uVar11;
  
  uVar11 = *(undefined8 *)(param_2 + 0x28);
  uVar10 = *(undefined8 *)(param_2 + 0x20);
  fVar8 = (float)((ulong)*(undefined8 *)(param_2 + 0x10) >> 0x20);
  fVar7 = (float)*(undefined8 *)(param_2 + 0x10);
  fVar5 = (float)*(undefined8 *)(param_2 + 0x18);
  fVar2 = SQRT(fVar5 * fVar5 + fVar7 * fVar7 + fVar8 * fVar8);
  if (NAN(fVar2)) {
    fVar2 = (float)sqrtf();
  }
  fVar1 = (float)((ulong)uVar10 >> 0x20);
  fVar9 = (float)uVar10;
  fVar6 = (float)uVar11;
  fVar3 = fVar6 * fVar6 + fVar9 * fVar9 + fVar1 * fVar1;
  fVar1 = SQRT(fVar3);
  fVar2 = 1.0 / fVar2;
  if (NAN(fVar1)) {
    fVar1 = (float)sqrtf(fVar3);
  }
  fVar4 = fVar5 * fVar2;
  fVar3 = fVar4;
  if (fVar4 < 0.0) {
    fVar3 = -(fVar5 * fVar2);
  }
  fVar5 = 0.0;
  if (fVar3 <= 1.0) {
    if (_UNK_02970cd8 <= fVar3) {
      fVar3 = fVar3 + _UNK_02970cdc;
      fVar5 = fVar3 * (fVar3 * (fVar3 * (fVar3 * _UNK_02970ce0 + _UNK_02970ce4) + _UNK_02970ce8) +
                      _UNK_02970cec) + _UNK_02970cf0;
      fVar3 = fVar3 * _UNK_02970cf4;
    }
    else {
      fVar5 = fVar3 * (fVar3 * (fVar3 * (fVar3 * _UNK_02970cf8 + _UNK_02970cfc) + _UNK_02970d00) +
                      _UNK_02970d04);
      fVar3 = fVar3 * _UNK_02970d08;
    }
    fVar5 = (float)((uint)fVar4 & 0x80000000 | (uint)(fVar5 / (1.0 - fVar3)));
  }
  fVar4 = (float)(int)(fVar5 * _UNK_029689d0) * _UNK_027edb30 - fVar5;
  fVar4 = fVar4 * fVar4;
  fVar4 = fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * _UNK_02964910 +
                                                               _UNK_02964914) + _UNK_02964918) +
                                             _UNK_0296491c) + _UNK_02964920) + _UNK_02964924) + -0.5
                  );
  fVar3 = -1.0 - fVar4;
  if (((int)(fVar5 * _UNK_029689d0) & 1U) == 0) {
    fVar3 = fVar4 + 1.0;
  }
  *param_1 = -fVar5;
  if (fVar3 == 0.0) {
    param_1[1] = 0.0;
    param_1[2] = 0.0;
  }
  else {
    fVar8 = (fVar8 * fVar2) / fVar3;
    fVar5 = 0.0;
    if ((fVar8 <= 1.0) && (fVar5 = 0.0, -1.0 <= fVar8)) {
      fVar5 = fVar8 * fVar8;
      fVar5 = fVar8 * (fVar5 * (fVar5 * (fVar5 * (fVar5 * (fVar5 * (fVar5 * (fVar5 * _UNK_0297158c +
                                                                            _UNK_02971590) +
                                                                   _UNK_02971594) + _UNK_02971598) +
                                                 _UNK_0297159c) + _UNK_029715a0) + _UNK_029715a4) +
                      _UNK_029715a8) + _UNK_027f7284;
    }
    fVar6 = (fVar6 * (1.0 / fVar1)) / fVar3;
    fVar8 = -fVar5;
    if (fVar7 * fVar2 * fVar3 <= _UNK_027f7cb8) {
      fVar8 = fVar5;
    }
    param_1[2] = fVar8;
    fVar2 = 0.0;
    if ((fVar6 <= 1.0) && (fVar2 = 0.0, -1.0 <= fVar6)) {
      fVar2 = fVar6 * fVar6;
      fVar2 = fVar6 * (fVar2 * (fVar2 * (fVar2 * (fVar2 * (fVar2 * (fVar2 * (fVar2 * _UNK_0297158c +
                                                                            _UNK_02971590) +
                                                                   _UNK_02971594) + _UNK_02971598) +
                                                 _UNK_0297159c) + _UNK_029715a0) + _UNK_029715a4) +
                      _UNK_029715a8) + _UNK_027f7284;
    }
    param_1[1] = fVar2;
    if (0.0 < fVar9 * (1.0 / fVar1) * fVar3) {
      param_1[1] = -fVar2;
    }
  }
  return;
}

// ==== Aska::Vector::SquaredDistanceToTriangle(Aska::Vector const*, Aska::Vector const*, Aska::Vector const*, Aska::Vector*) const
// vaddr 0x1f8cd9c | ghidra 0x208cd9c | size 908 | symbol _ZNK4Aska6Vector25SquaredDistanceToTriangleEPKS0_S2_S2_PS0_ | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK4Aska6Vector25SquaredDistanceToTriangleEPKS0_S2_S2_PS0_
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
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  
  fVar1 = *param_2;
  fVar2 = param_2[1];
  fVar6 = param_2[2];
  fVar13 = fVar1 - *param_1;
  fVar15 = fVar2 - param_1[1];
  fVar5 = *param_3 - fVar1;
  fVar4 = param_3[1] - fVar2;
  fVar1 = *param_4 - fVar1;
  fVar2 = param_4[1] - fVar2;
  fVar17 = fVar6 - param_1[2];
  fVar3 = param_3[2] - fVar6;
  fVar6 = param_4[2] - fVar6;
  fVar9 = fVar5 * fVar5 + fVar4 * fVar4 + fVar3 * fVar3;
  fVar14 = fVar5 * fVar1 + fVar4 * fVar2 + fVar3 * fVar6;
  fVar8 = fVar1 * fVar1 + fVar2 * fVar2 + fVar6 * fVar6;
  fVar12 = fVar13 * fVar5 + fVar15 * fVar4 + fVar17 * fVar3;
  fVar11 = fVar13 * fVar1 + fVar15 * fVar2 + fVar17 * fVar6;
  fVar7 = fVar14 * fVar11 - fVar12 * fVar8;
  fVar10 = fVar12 * fVar14 - fVar9 * fVar11;
  fVar16 = ABS(fVar9 * fVar8 - fVar14 * fVar14);
  fVar13 = fVar13 * fVar13 + fVar15 * fVar15 + fVar17 * fVar17;
  if (fVar7 + fVar10 <= fVar16) {
    if (0.0 <= fVar7) {
      if (0.0 <= fVar10) {
        fVar16 = 1.0 / fVar16;
        fVar7 = fVar7 * fVar16;
        fVar10 = fVar10 * fVar16;
        fVar9 = fVar9 * fVar7 + fVar14 * fVar10;
        fVar8 = fVar14 * fVar7 + fVar8 * fVar10;
code_r0x0208d060:
        fVar11 = fVar7 * (fVar12 + fVar12 + fVar9) + fVar10 * (fVar11 + fVar11 + fVar8);
      }
      else {
        fVar10 = 0.0;
        if (0.0 <= fVar12) {
code_r0x0208d0c0:
          fVar10 = 0.0;
          fVar7 = 0.0;
          goto code_r0x0208d0c4;
        }
        if (fVar9 <= -fVar12) {
          fVar13 = fVar13 + fVar9 + fVar12 + fVar12;
          fVar7 = 1.0;
          goto code_r0x0208d0c4;
        }
code_r0x0208d09c:
        fVar10 = 0.0;
        fVar7 = -fVar12 / fVar9;
        fVar11 = fVar12 * fVar7;
      }
code_r0x0208d074:
      fVar13 = fVar13 + fVar11;
      goto code_r0x0208d0c4;
    }
    if ((0.0 <= fVar10) || (0.0 <= fVar12)) {
      if (0.0 <= fVar11) {
code_r0x0208d07c:
        fVar7 = 0.0;
        fVar10 = 0.0;
        goto code_r0x0208d0c4;
      }
      if (-fVar11 < fVar8) goto code_r0x0208cfb0;
      goto code_r0x0208d020;
    }
    if (fVar9 <= -fVar12) goto code_r0x0208d0a8;
    fVar7 = -fVar12 / fVar9;
    fVar9 = fVar12 * fVar7;
code_r0x0208d0b4:
    fVar13 = fVar13 + fVar9;
    fVar10 = 0.0;
  }
  else {
    if (0.0 <= fVar7) {
      if (0.0 <= fVar10) {
        fVar7 = ((fVar8 + fVar11) - fVar14) - fVar12;
        if (0.0 < fVar7) goto code_r0x0208cfd0;
      }
      else {
        fVar10 = fVar9 + fVar12;
        if (fVar10 <= fVar14 + fVar11) {
          if (fVar10 <= 0.0) goto code_r0x0208d0a8;
          if (0.0 <= fVar12) goto code_r0x0208d0c0;
          goto code_r0x0208d09c;
        }
        fVar10 = fVar10 - (fVar14 + fVar11);
        fVar7 = fVar8 + fVar9 + fVar14 * -2.0;
        if (fVar10 < fVar7) {
          fVar10 = fVar10 / fVar7;
          fVar7 = 1.0 - fVar10;
          fVar9 = fVar14 * fVar10 + fVar9 * fVar7;
          fVar8 = fVar8 * fVar10 + fVar14 * fVar7;
          goto code_r0x0208d060;
        }
      }
    }
    else {
      fVar7 = fVar8 + fVar11;
      if (fVar12 + fVar14 < fVar7) {
        fVar7 = fVar7 - (fVar12 + fVar14);
code_r0x0208cfd0:
        fVar10 = fVar8 + fVar9 + fVar14 * -2.0;
        if (fVar7 < fVar10) {
          fVar7 = fVar7 / fVar10;
          fVar10 = 1.0 - fVar7;
          fVar9 = fVar9 * fVar7 + fVar14 * fVar10;
          fVar8 = fVar14 * fVar7 + fVar8 * fVar10;
          goto code_r0x0208d060;
        }
code_r0x0208d0a8:
        fVar7 = 1.0;
        fVar9 = fVar9 + fVar12 + fVar12;
        goto code_r0x0208d0b4;
      }
      if (0.0 < fVar7) {
        if (0.0 <= fVar11) goto code_r0x0208d07c;
code_r0x0208cfb0:
        fVar7 = 0.0;
        fVar10 = -fVar11 / fVar8;
        fVar11 = fVar11 * fVar10;
        goto code_r0x0208d074;
      }
    }
code_r0x0208d020:
    fVar7 = 0.0;
    fVar13 = fVar13 + fVar8 + fVar11 + fVar11;
    fVar10 = 1.0;
  }
code_r0x0208d0c4:
  if (fVar13 <= 0.0) {
    fVar13 = 0.0;
  }
  if (param_5 != (float *)0x0) {
    fVar5 = fVar5 * fVar7 + fVar10 * fVar1;
    fVar2 = fVar4 * fVar7 + fVar10 * fVar2;
    fVar1 = fVar3 * fVar7 + fVar10 * fVar6;
    param_5[3] = param_4[3];
    *param_5 = fVar5;
    param_5[1] = fVar2;
    param_5[2] = fVar1;
    *param_5 = *param_2 + fVar5;
    param_5[1] = param_2[1] + fVar2;
    param_5[2] = param_2[2] + fVar1;
  }
  return fVar13;
}

// ==== Aska::Vector::IsInsideWithAngle(Aska::Vector const*, float)
// vaddr 0x1f8d128 | ghidra 0x208d128 | size 240 | symbol _ZN4Aska6Vector17IsInsideWithAngleEPKS0_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN4Aska6Vector17IsInsideWithAngleEPKS0_f(float param_1,float *param_2,float *param_3)

{
  uint uVar1;
  float fVar2;
  ulong uVar3;
  uint uVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  fVar2 = _UNK_027e519c;
  fVar8 = *param_2;
  fVar9 = param_2[1];
  fVar7 = param_2[2];
  fVar6 = fVar8 * fVar8 + fVar9 * fVar9 + fVar7 * fVar7;
  if (_UNK_027e519c < ABS(1.0 - fVar6)) {
    fVar5 = SQRT(fVar6);
    if (NAN(fVar5)) {
      fVar5 = (float)sqrtf(fVar6);
    }
    if (fVar2 <= fVar5) {
      fVar5 = 1.0 / fVar5;
      fVar8 = fVar5 * fVar8;
      fVar9 = fVar5 * fVar9;
      fVar7 = fVar5 * fVar7;
    }
  }
  uVar4 = (uint)((param_1 * _UNK_027e3fd4) / _UNK_027e3fd0);
  uVar1 = uVar4;
  if (0xb3 < (int)uVar4) {
    uVar1 = 0xb4;
  }
  uVar3 = (ulong)uVar1;
  if ((int)uVar4 < 1) {
    uVar3 = 0;
  }
  return *(float *)(PTR_g_aRadian2Cos_02cc1ad8 + uVar3 * 4) <=
         *param_3 * fVar8 + param_3[1] * fVar9 + param_3[2] * fVar7;
}


// FAILED to create function at 02cc7230 Aska::Vector::zeroWeightVector
// FAILED to create function at 02dcd940 Aska::Vector::zeroVector
