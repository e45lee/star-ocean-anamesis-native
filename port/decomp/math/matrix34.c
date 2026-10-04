// port/decomp/math/matrix34.c: Ghidra decompiles for the math subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:09 UTC: tools/decomp.sh '--into' 'math/matrix34' 'Aska::Matrix34::'

// ==== Aska::Matrix34::Create(Aska::Quaternion const*)
// vaddr 0x1f3cbb8 | ghidra 0x203cbb8 | size 176 | symbol _ZN4Aska8Matrix346CreateEPKNS_10QuaternionE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Matrix346CreateEPKNS_10QuaternionE(float *param_1,float *param_2)

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
  param_1[3] = 0.0;
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
  param_1[7] = 0.0;
  param_1[1] = fVar7 + fVar7;
  param_1[2] = fVar10 + fVar10;
  param_1[5] = 1.0 - (fVar8 + fVar8);
  param_1[6] = fVar5 + fVar5;
  *param_1 = (fVar2 * fVar2 + fVar4 * fVar4) * -2.0 + 1.0;
  param_1[4] = fVar9 + fVar9;
  param_1[10] = 1.0 - (fVar1 + fVar1);
  param_1[0xb] = 0.0;
  return;
}

// ==== Aska::Matrix34::Create(Aska::Quaternion const*, Aska::Vector const*)
// vaddr 0x1f3cc68 | ghidra 0x203cc68 | size 188 | symbol _ZN4Aska8Matrix346CreateEPKNS_10QuaternionEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Matrix346CreateEPKNS_10QuaternionEPKNS_6VectorE
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
  
  fVar1 = *param_2;
  fVar2 = param_2[1];
  fVar4 = param_2[2];
  fVar6 = param_2[3];
  fVar7 = fVar1 * fVar2 - fVar4 * fVar6;
  fVar10 = fVar1 * fVar2 + fVar4 * fVar6;
  fVar11 = fVar1 * fVar4 + fVar2 * fVar6;
  fVar3 = fVar1 * fVar4 - fVar2 * fVar6;
  fVar5 = fVar2 * fVar4 - fVar1 * fVar6;
  fVar6 = fVar2 * fVar4 + fVar1 * fVar6;
  fVar9 = fVar1 * fVar1 + fVar4 * fVar4;
  fVar8 = fVar1 * fVar1 + fVar2 * fVar2;
  param_1[1] = fVar7 + fVar7;
  param_1[2] = fVar11 + fVar11;
  *param_1 = (fVar2 * fVar2 + fVar4 * fVar4) * -2.0 + 1.0;
  fVar1 = *param_3;
  param_1[4] = fVar10 + fVar10;
  param_1[5] = 1.0 - (fVar9 + fVar9);
  param_1[6] = fVar5 + fVar5;
  param_1[3] = fVar1;
  fVar1 = param_3[1];
  param_1[8] = fVar3 + fVar3;
  param_1[9] = fVar6 + fVar6;
  param_1[7] = fVar1;
  param_1[10] = 1.0 - (fVar8 + fVar8);
  param_1[0xb] = param_3[2];
  return;
}

// ==== Aska::Matrix34::CreateWithNormalize(Aska::Quaternion const*)
// vaddr 0x1f3cd24 | ghidra 0x203cd24 | size 272 | symbol _ZN4Aska8Matrix3419CreateWithNormalizeEPKNS_10QuaternionE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Matrix3419CreateWithNormalizeEPKNS_10QuaternionE(float *param_1,float *param_2)

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
  param_1[5] = 1.0 - (fVar8 + fVar8);
  param_1[6] = fVar3 + fVar3;
  *param_1 = (fVar5 * fVar5 + fVar6 * fVar6) * -2.0 + 1.0;
  param_1[4] = fVar9 + fVar9;
  param_1[10] = 1.0 - (fVar4 + fVar4);
  param_1[0xb] = 0.0;
  return;
}

// ==== Aska::Matrix34::CreateWithNormalize(Aska::Quaternion const*, Aska::Vector const*)
// vaddr 0x1f3ce34 | ghidra 0x203ce34 | size 296 | symbol _ZN4Aska8Matrix3419CreateWithNormalizeEPKNS_10QuaternionEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Matrix3419CreateWithNormalizeEPKNS_10QuaternionEPKNS_6VectorE
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
  fVar1 = fVar4 * fVar5 - fVar7 * fVar6;
  fVar9 = fVar4 * fVar5 + fVar7 * fVar6;
  fVar10 = fVar4 * fVar6 + fVar7 * fVar5;
  fVar2 = fVar4 * fVar6 - fVar7 * fVar5;
  fVar3 = fVar5 * fVar6 - fVar7 * fVar4;
  fVar7 = fVar5 * fVar6 + fVar7 * fVar4;
  fVar8 = fVar4 * fVar4 + fVar6 * fVar6;
  fVar4 = fVar4 * fVar4 + fVar5 * fVar5;
  param_1[1] = fVar1 + fVar1;
  param_1[2] = fVar10 + fVar10;
  *param_1 = (fVar5 * fVar5 + fVar6 * fVar6) * -2.0 + 1.0;
  fVar1 = *param_3;
  param_1[4] = fVar9 + fVar9;
  param_1[5] = 1.0 - (fVar8 + fVar8);
  param_1[6] = fVar3 + fVar3;
  param_1[3] = fVar1;
  fVar1 = param_3[1];
  param_1[8] = fVar2 + fVar2;
  param_1[9] = fVar7 + fVar7;
  param_1[7] = fVar1;
  param_1[10] = 1.0 - (fVar4 + fVar4);
  param_1[0xb] = param_3[2];
  return;
}

// ==== Aska::Matrix34::SetRotation(Aska::Vector const*, EnumRotateType)
// vaddr 0x1f3cf5c | ghidra 0x203cf5c | size 1228 | symbol _ZN4Aska8Matrix3411SetRotationEPKNS_6VectorE14EnumRotateType | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska8Matrix3411SetRotationEPKNS_6VectorE14EnumRotateType
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

// ==== Aska::Matrix34::SetRotationByUnitVector(Aska::Vector const*)
// vaddr 0x1f3d428 | ghidra 0x203d428 | size 440 | symbol _ZN4Aska8Matrix3423SetRotationByUnitVectorEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska8Matrix3423SetRotationByUnitVectorEPKNS_6VectorE(float *param_1,float *param_2)

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

// ==== Aska::Matrix34::Rotate(Aska::Vector const*, EnumRotateType)
// vaddr 0x1f3d5e0 | ghidra 0x203d5e0 | size 2520 | symbol _ZN4Aska8Matrix346RotateEPKNS_6VectorE14EnumRotateType | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska8Matrix346RotateEPKNS_6VectorE14EnumRotateType
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
    goto code_r0x0203df84;
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
    goto code_r0x0203df84;
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
    goto code_r0x0203df7c;
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
code_r0x0203df7c:
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
code_r0x0203df84:
  param_1[10] = fVar9 * fVar24 + fVar15 + fVar21;
  param_1[0xb] = fVar6 * fVar25 + fVar7 * fVar5 + fVar8 * fVar24;
  return;
}

// ==== Aska::Matrix34::RotateByUnitVector(Aska::Vector const*)
// vaddr 0x1f3dfb8 | ghidra 0x203dfb8 | size 660 | symbol _ZN4Aska8Matrix3418RotateByUnitVectorEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska8Matrix3418RotateByUnitVectorEPKNS_6VectorE(float *param_1,float *param_2)

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

// ==== Aska::Matrix34::SetTranslate(Aska::Vector const*)
// vaddr 0x1f3e24c | ghidra 0x203e24c | size 28 | symbol _ZN4Aska8Matrix3412SetTranslateEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Matrix3412SetTranslateEPKNS_6VectorE(long param_1,undefined4 *param_2)

{
  *(undefined4 *)(param_1 + 0xc) = *param_2;
  *(undefined4 *)(param_1 + 0x1c) = param_2[1];
  *(undefined4 *)(param_1 + 0x2c) = param_2[2];
  return;
}

// ==== Aska::Matrix34::Translate(Aska::Vector const*)
// vaddr 0x1f3e268 | ghidra 0x203e268 | size 52 | symbol _ZN4Aska8Matrix349TranslateEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Matrix349TranslateEPKNS_6VectorE(long param_1,float *param_2)

{
  *(float *)(param_1 + 0xc) = *param_2 + *(float *)(param_1 + 0xc);
  *(float *)(param_1 + 0x1c) = param_2[1] + *(float *)(param_1 + 0x1c);
  *(float *)(param_1 + 0x2c) = param_2[2] + *(float *)(param_1 + 0x2c);
  return;
}

// ==== Aska::Matrix34::InvertLowError()
// vaddr 0x1f3e29c | ghidra 0x203e29c | size 360 | symbol _ZN4Aska8Matrix3414InvertLowErrorEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Matrix3414InvertLowErrorEv(float *param_1)

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
  
  fVar4 = param_1[4];
  fVar3 = param_1[5];
  fVar1 = *param_1;
  fVar2 = param_1[1];
  fVar5 = param_1[6];
  fVar7 = param_1[7];
  fVar6 = param_1[2];
  fVar8 = param_1[3];
  fVar9 = param_1[8];
  fVar10 = param_1[9];
  fVar11 = param_1[10];
  fVar12 = param_1[0xb];
  fVar13 = fVar1 * fVar3 - fVar2 * fVar4;
  fVar15 = fVar1 * fVar5 - fVar4 * fVar6;
  fVar17 = fVar1 * fVar7 - fVar4 * fVar8;
  fVar14 = fVar2 * fVar5 - fVar3 * fVar6;
  fVar16 = fVar2 * fVar7 - fVar3 * fVar8;
  fVar8 = fVar6 * fVar7 - fVar5 * fVar8;
  fVar7 = 1.0 / (fVar14 * fVar9 + (fVar13 * fVar11 - fVar15 * fVar10));
  *(ulong *)(param_1 + 2) =
       CONCAT44(fVar7 * ((fVar16 * fVar11 - fVar8 * fVar10) - fVar14 * fVar12),fVar7 * fVar14);
  *(ulong *)param_1 =
       CONCAT44(fVar7 * (fVar10 * fVar6 - fVar11 * fVar2),fVar7 * (fVar11 * fVar3 - fVar10 * fVar5))
  ;
  *(ulong *)(param_1 + 6) =
       CONCAT44(fVar7 * ((fVar8 * fVar9 - fVar17 * fVar11) + fVar15 * fVar12),-(fVar15 * fVar7));
  *(ulong *)(param_1 + 4) =
       CONCAT44(fVar7 * (fVar11 * fVar1 - fVar9 * fVar6),fVar7 * (fVar9 * fVar5 - fVar11 * fVar4));
  *(ulong *)(param_1 + 10) =
       CONCAT44(fVar7 * ((fVar17 * fVar10 - fVar16 * fVar9) - fVar13 * fVar12),fVar7 * fVar13);
  *(ulong *)(param_1 + 8) =
       CONCAT44(fVar7 * (fVar9 * fVar2 - fVar10 * fVar1),fVar7 * (fVar10 * fVar4 - fVar9 * fVar3));
  return;
}

// ==== Aska::Matrix34::MulVector(Aska::Vector const*)
// vaddr 0x1f3e404 | ghidra 0x203e404 | size 172 | symbol _ZN4Aska8Matrix349MulVectorEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Matrix349MulVectorEPKNS_6VectorE(float *param_1,float *param_2)

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
  return;
}

// ==== Aska::Matrix34::MulVector(Aska::Matrix34*, Aska::Vector const*) const
// vaddr 0x1f3e4b0 | ghidra 0x203e4b0 | size 196 | symbol _ZNK4Aska8Matrix349MulVectorEPS0_PKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska8Matrix349MulVectorEPS0_PKNS_6VectorE(float *param_1,float *param_2,float *param_3)

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
  return;
}

// ==== Aska::Matrix34::ApplyVector(Aska::Vector*, Aska::Vector const*) const
// vaddr 0x1f3e574 | ghidra 0x203e574 | size 256 | symbol _ZNK4Aska8Matrix3411ApplyVectorEPNS_6VectorEPKS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska8Matrix3411ApplyVectorEPNS_6VectorEPKS1_(float *param_1,float *param_2,float *param_3)

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
  
  fVar3 = *param_3;
  fVar1 = param_3[1];
  fVar5 = param_3[2];
  fVar4 = param_3[3];
  fVar2 = *param_1 * fVar3 + param_1[1] * fVar1 + param_1[2] * fVar5 + param_1[3] * fVar4;
  if (param_2 != param_3) {
    *param_2 = fVar2;
    param_2[1] = param_1[4] * *param_3 + param_1[5] * param_3[1] + param_1[6] * param_3[2] +
                 param_1[7] * param_3[3];
    param_2[2] = param_1[8] * *param_3 + param_1[9] * param_3[1] + param_1[10] * param_3[2] +
                 param_1[0xb] * param_3[3];
    param_2[3] = param_3[3];
    return;
  }
  fVar6 = param_1[4];
  fVar7 = param_1[5];
  fVar10 = param_1[8];
  fVar12 = param_1[9];
  fVar8 = param_1[6];
  fVar9 = param_1[7];
  fVar11 = param_1[10];
  fVar13 = param_1[0xb];
  *param_2 = fVar2;
  param_2[1] = fVar3 * fVar6 + fVar1 * fVar7 + fVar5 * fVar8 + fVar4 * fVar9;
  param_2[2] = fVar3 * fVar10 + fVar1 * fVar12 + fVar5 * fVar11 + fVar4 * fVar13;
  param_2[3] = fVar4;
  return;
}

// ==== Aska::Matrix34::SetLookAtMatrixXP(Aska::Vector const*, Aska::Vector const*, float)
// vaddr 0x1f3e674 | ghidra 0x203e674 | size 1024 | symbol _ZN4Aska8Matrix3417SetLookAtMatrixXPEPKNS_6VectorES3_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska8Matrix3417SetLookAtMatrixXPEPKNS_6VectorES3_f
               (float param_1,undefined8 *param_2,float *param_3,float *param_4)

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
  undefined8 uVar23;
  
  fVar8 = *param_4;
  fVar5 = param_4[1];
  uVar23 = *(undefined8 *)param_4;
  fVar6 = param_4[2];
  fVar3 = (float)*(undefined8 *)(param_4 + 2);
  fVar4 = fVar8 * fVar8 + fVar5 * fVar5 + fVar6 * fVar6;
  fVar2 = SQRT(fVar4);
  if (NAN(fVar2)) {
    fVar2 = (float)sqrtf(fVar4);
  }
  fVar4 = _UNK_027e519c;
  if (_UNK_027e519c <= fVar2) {
    fVar2 = 1.0 / fVar2;
    uVar23 = CONCAT44(fVar5 * fVar2,fVar8 * fVar2);
    fVar3 = fVar6 * fVar2;
  }
  fVar6 = (float)((ulong)uVar23 >> 0x20);
  fVar2 = 0.0;
  fVar5 = fVar6;
  if (ABS(fVar6) <= _UNK_02970cd0) {
    fVar2 = 1.0;
    fVar5 = 0.0;
  }
  fVar11 = param_4[1] * fVar5 - param_4[2] * fVar2;
  fVar9 = param_4[2] * 0.0 - *param_4 * fVar5;
  fVar2 = *param_4 * fVar2 - param_4[1] * 0.0;
  fVar8 = fVar2 * fVar2 + fVar11 * fVar11 + fVar9 * fVar9;
  fVar5 = SQRT(fVar8);
  if (NAN(fVar5)) {
    fVar5 = (float)sqrtf(fVar8);
  }
  if (fVar4 <= fVar5) {
    fVar5 = 1.0 / fVar5;
    fVar11 = fVar5 * fVar11;
    fVar9 = fVar5 * fVar9;
    fVar2 = fVar5 * fVar2;
  }
  fVar22 = (float)uVar23;
  fVar12 = *param_3;
  fVar15 = param_3[1];
  fVar16 = fVar6 * fVar11 - fVar22 * fVar9;
  fVar5 = param_3[2];
  fVar10 = fVar3 * fVar9 - fVar6 * fVar2;
  fVar14 = fVar22 * fVar2 - fVar3 * fVar11;
  fVar17 = fVar3 * 0.0 + fVar16 * 0.0;
  fVar19 = fVar6 * 0.0 + fVar14 * 0.0;
  fVar21 = fVar22 * 0.0 + fVar10 * 0.0;
  fVar13 = fVar2 * 0.0;
  fVar18 = fVar9 * 0.0;
  fVar20 = fVar11 * 0.0;
  fVar8 = param_1 + (float)(int)(param_1 * _UNK_027ebdf4) * _UNK_027edb30;
  bVar1 = ((int)(param_1 * _UNK_027ebdf4) & 1U) != 0;
  fVar4 = fVar8;
  if (bVar1) {
    fVar4 = -fVar8;
  }
  fVar8 = fVar8 * fVar8;
  fVar7 = fVar8 * (fVar8 * (fVar8 * (fVar8 * (fVar8 * (fVar8 * (fVar8 * _UNK_02964910 +
                                                               _UNK_02964914) + _UNK_02964918) +
                                             _UNK_0296491c) + _UNK_02964920) + _UNK_02964924) + -0.5
                  );
  fVar4 = fVar4 * (fVar8 * (fVar8 * (fVar8 * (fVar8 * (fVar8 * (fVar8 * (fVar8 * _UNK_02964928 +
                                                                        _UNK_0296492c) +
                                                               _UNK_02964930) + _UNK_02964934) +
                                             _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) + 1.0)
  ;
  fVar8 = -1.0 - fVar7;
  if (!bVar1) {
    fVar8 = fVar7 + 1.0;
  }
  param_2[1] = CONCAT44((fVar20 + fVar21) - (fVar5 * fVar11 + fVar12 * fVar22 + fVar15 * fVar10),
                        fVar11 + fVar21);
  *param_2 = CONCAT44(fVar20 + fVar4 * fVar22 + fVar8 * fVar10,
                      fVar20 + (fVar8 * fVar22 - fVar10 * fVar4));
  param_2[3] = CONCAT44((fVar18 + fVar19) - (fVar5 * fVar9 + fVar6 * fVar12 + fVar15 * fVar14),
                        fVar9 + fVar19);
  param_2[2] = CONCAT44(fVar18 + fVar4 * fVar6 + fVar8 * fVar14,
                        fVar18 + (fVar8 * fVar6 - fVar14 * fVar4));
  param_2[5] = CONCAT44((fVar13 + fVar17) - (fVar5 * fVar2 + fVar12 * fVar3 + fVar15 * fVar16),
                        fVar2 + fVar17);
  param_2[4] = CONCAT44(fVar13 + fVar4 * fVar3 + fVar8 * fVar16,
                        fVar13 + (fVar8 * fVar3 - fVar16 * fVar4));
  return;
}

// ==== Aska::Matrix34::SetLookAtMatrixXN(Aska::Vector const*, Aska::Vector const*, float)
// vaddr 0x1f3ea74 | ghidra 0x203ea74 | size 1020 | symbol _ZN4Aska8Matrix3417SetLookAtMatrixXNEPKNS_6VectorES3_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska8Matrix3417SetLookAtMatrixXNEPKNS_6VectorES3_f
               (float param_1,undefined8 *param_2,float *param_3,float *param_4)

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
  
  fVar2 = *param_4;
  fVar4 = param_4[1];
  fVar6 = param_4[2];
  fVar11 = -fVar2;
  fVar9 = -fVar4;
  fVar4 = fVar2 * fVar2 + fVar4 * fVar4 + fVar6 * fVar6;
  fVar2 = SQRT(fVar4);
  fVar6 = -fVar6;
  if (NAN(fVar2)) {
    fVar2 = (float)sqrtf(fVar4);
  }
  fVar4 = _UNK_027e519c;
  if (_UNK_027e519c <= fVar2) {
    fVar2 = 1.0 / fVar2;
    fVar11 = fVar2 * fVar11;
    fVar9 = fVar2 * fVar9;
    fVar6 = fVar2 * fVar6;
  }
  fVar2 = 0.0;
  fVar3 = fVar9;
  if (ABS(fVar9) <= _UNK_02970cd0) {
    fVar2 = 1.0;
    fVar3 = 0.0;
  }
  fVar7 = fVar3 * fVar9 - fVar2 * fVar6;
  fVar8 = fVar6 * 0.0 - fVar3 * fVar11;
  fVar2 = fVar2 * fVar11 - fVar9 * 0.0;
  fVar5 = fVar2 * fVar2 + fVar7 * fVar7 + fVar8 * fVar8;
  fVar3 = SQRT(fVar5);
  if (NAN(fVar3)) {
    fVar3 = (float)sqrtf(fVar5);
  }
  if (fVar4 <= fVar3) {
    fVar3 = 1.0 / fVar3;
    fVar7 = fVar3 * fVar7;
    fVar8 = fVar3 * fVar8;
    fVar2 = fVar3 * fVar2;
  }
  fVar5 = *param_3;
  fVar12 = param_3[1];
  fVar3 = param_3[2];
  fVar13 = fVar6 * fVar8 - fVar9 * fVar2;
  fVar14 = fVar11 * fVar2 - fVar6 * fVar7;
  fVar15 = fVar9 * fVar7 - fVar11 * fVar8;
  fVar16 = fVar11 * 0.0 + fVar13 * 0.0;
  fVar19 = fVar6 * 0.0 + fVar15 * 0.0;
  fVar10 = fVar2 * 0.0;
  fVar20 = fVar8 * 0.0;
  fVar22 = fVar7 * 0.0;
  fVar21 = fVar9 * 0.0 + fVar14 * 0.0;
  fVar17 = param_1 + (float)(int)(param_1 * _UNK_027ebdf4) * _UNK_027edb30;
  bVar1 = ((int)(param_1 * _UNK_027ebdf4) & 1U) != 0;
  fVar4 = fVar17;
  if (bVar1) {
    fVar4 = -fVar17;
  }
  fVar17 = fVar17 * fVar17;
  fVar18 = fVar17 * (fVar17 * (fVar17 * (fVar17 * (fVar17 * (fVar17 * (fVar17 * _UNK_02964910 +
                                                                      _UNK_02964914) + _UNK_02964918
                                                            ) + _UNK_0296491c) + _UNK_02964920) +
                              _UNK_02964924) + -0.5);
  fVar4 = fVar4 * (fVar17 * (fVar17 * (fVar17 * (fVar17 * (fVar17 * (fVar17 * (fVar17 * 
                                                  _UNK_02964928 + _UNK_0296492c) + _UNK_02964930) +
                                                  _UNK_02964934) + _UNK_02964938) + _UNK_0296493c) +
                            _UNK_02964940) + 1.0);
  fVar17 = -1.0 - fVar18;
  if (!bVar1) {
    fVar17 = fVar18 + 1.0;
  }
  param_2[1] = CONCAT44((fVar22 + fVar16) - (fVar3 * fVar7 + fVar11 * fVar5 + fVar12 * fVar13),
                        fVar7 + fVar16);
  *param_2 = CONCAT44(fVar22 + fVar4 * fVar11 + fVar17 * fVar13,
                      fVar22 + (fVar17 * fVar11 - fVar13 * fVar4));
  param_2[3] = CONCAT44((fVar20 + fVar21) - (fVar3 * fVar8 + fVar9 * fVar5 + fVar12 * fVar14),
                        fVar8 + fVar21);
  param_2[2] = CONCAT44(fVar20 + fVar4 * fVar9 + fVar17 * fVar14,
                        fVar20 + (fVar17 * fVar9 - fVar14 * fVar4));
  param_2[5] = CONCAT44((fVar10 + fVar19) - (fVar3 * fVar2 + fVar6 * fVar5 + fVar12 * fVar15),
                        fVar2 + fVar19);
  param_2[4] = CONCAT44(fVar10 + fVar4 * fVar6 + fVar17 * fVar15,
                        fVar10 + (fVar17 * fVar6 - fVar15 * fVar4));
  return;
}

// ==== Aska::Matrix34::SetLookAtMatrixYP(Aska::Vector const*, Aska::Vector const*, float)
// vaddr 0x1f3ee70 | ghidra 0x203ee70 | size 1000 | symbol _ZN4Aska8Matrix3417SetLookAtMatrixYPEPKNS_6VectorES3_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska8Matrix3417SetLookAtMatrixYPEPKNS_6VectorES3_f
               (float param_1,undefined8 *param_2,float *param_3,float *param_4)

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
  undefined8 uVar23;
  
  fVar10 = *param_4;
  fVar6 = param_4[1];
  uVar23 = *(undefined8 *)param_4;
  fVar8 = param_4[2];
  fVar3 = (float)*(undefined8 *)(param_4 + 2);
  fVar4 = fVar10 * fVar10 + fVar6 * fVar6 + fVar8 * fVar8;
  fVar2 = SQRT(fVar4);
  if (NAN(fVar2)) {
    fVar2 = (float)sqrtf(fVar4);
  }
  fVar4 = _UNK_027e519c;
  if (_UNK_027e519c <= fVar2) {
    fVar2 = 1.0 / fVar2;
    uVar23 = CONCAT44(fVar6 * fVar2,fVar10 * fVar2);
    fVar3 = fVar8 * fVar2;
  }
  fVar8 = (float)((ulong)uVar23 >> 0x20);
  fVar6 = (float)uVar23;
  fVar2 = fVar8;
  if (ABS(fVar8) <= _UNK_02970cd0) {
    fVar2 = 0.0;
  }
  fVar11 = fVar3 * 0.0 - fVar2 * fVar8;
  fVar7 = fVar2 * fVar6 - fVar3;
  fVar2 = fVar8 - fVar6 * 0.0;
  fVar5 = fVar2 * fVar2 + fVar11 * fVar11 + fVar7 * fVar7;
  fVar10 = SQRT(fVar5);
  if (NAN(fVar10)) {
    fVar10 = (float)sqrtf(fVar5);
  }
  if (fVar4 <= fVar10) {
    fVar10 = 1.0 / fVar10;
    fVar11 = fVar10 * fVar11;
    fVar7 = fVar10 * fVar7;
    fVar2 = fVar10 * fVar2;
  }
  fVar5 = *param_3;
  fVar12 = param_3[1];
  fVar10 = param_3[2];
  fVar13 = fVar8 * fVar2 - fVar3 * fVar7;
  fVar14 = fVar3 * fVar11 - fVar6 * fVar2;
  fVar15 = fVar6 * fVar7 - fVar8 * fVar11;
  fVar16 = fVar8 * 0.0 + fVar14 * 0.0;
  fVar19 = fVar6 * 0.0 + fVar13 * 0.0;
  fVar17 = fVar3 * 0.0 + fVar15 * 0.0;
  fVar9 = fVar2 * 0.0;
  fVar18 = fVar7 * 0.0;
  fVar22 = fVar11 * 0.0;
  fVar20 = param_1 + (float)(int)(param_1 * _UNK_027ebdf4) * _UNK_027edb30;
  bVar1 = ((int)(param_1 * _UNK_027ebdf4) & 1U) != 0;
  fVar4 = fVar20;
  if (bVar1) {
    fVar4 = -fVar20;
  }
  fVar20 = fVar20 * fVar20;
  fVar21 = fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * _UNK_02964910 +
                                                                      _UNK_02964914) + _UNK_02964918
                                                            ) + _UNK_0296491c) + _UNK_02964920) +
                              _UNK_02964924) + -0.5);
  fVar4 = fVar4 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * 
                                                  _UNK_02964928 + _UNK_0296492c) + _UNK_02964930) +
                                                  _UNK_02964934) + _UNK_02964938) + _UNK_0296493c) +
                            _UNK_02964940) + 1.0);
  fVar20 = -1.0 - fVar21;
  if (!bVar1) {
    fVar20 = fVar21 + 1.0;
  }
  param_2[1] = CONCAT44((fVar22 + fVar19) - (fVar10 * fVar11 + fVar6 * fVar12 + fVar5 * fVar13),
                        fVar11 + fVar19);
  *param_2 = CONCAT44(fVar22 + fVar20 * fVar6 + fVar4 * fVar13,
                      fVar22 + (fVar20 * fVar13 - fVar6 * fVar4));
  param_2[3] = CONCAT44((fVar18 + fVar16) - (fVar10 * fVar7 + fVar8 * fVar12 + fVar5 * fVar14),
                        fVar7 + fVar16);
  param_2[2] = CONCAT44(fVar18 + fVar20 * fVar8 + fVar4 * fVar14,
                        fVar18 + (fVar20 * fVar14 - fVar8 * fVar4));
  param_2[5] = CONCAT44((fVar9 + fVar17) - (fVar10 * fVar2 + fVar3 * fVar12 + fVar5 * fVar15),
                        fVar2 + fVar17);
  param_2[4] = CONCAT44(fVar9 + fVar20 * fVar3 + fVar4 * fVar15,
                        fVar9 + (fVar20 * fVar15 - fVar3 * fVar4));
  return;
}

// ==== Aska::Matrix34::SetLookAtMatrixYN(Aska::Vector const*, Aska::Vector const*, float)
// vaddr 0x1f3f258 | ghidra 0x203f258 | size 1008 | symbol _ZN4Aska8Matrix3417SetLookAtMatrixYNEPKNS_6VectorES3_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska8Matrix3417SetLookAtMatrixYNEPKNS_6VectorES3_f
               (float param_1,undefined8 *param_2,float *param_3,float *param_4)

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
  
  fVar2 = *param_4;
  fVar4 = param_4[1];
  fVar6 = param_4[2];
  fVar12 = -fVar2;
  fVar9 = -fVar4;
  fVar4 = fVar2 * fVar2 + fVar4 * fVar4 + fVar6 * fVar6;
  fVar2 = SQRT(fVar4);
  fVar6 = -fVar6;
  if (NAN(fVar2)) {
    fVar2 = (float)sqrtf(fVar4);
  }
  fVar4 = _UNK_027e519c;
  if (_UNK_027e519c <= fVar2) {
    fVar2 = 1.0 / fVar2;
    fVar12 = fVar2 * fVar12;
    fVar9 = fVar2 * fVar9;
    fVar6 = fVar2 * fVar6;
  }
  fVar2 = fVar9;
  if (ABS(fVar9) <= _UNK_02970cd0) {
    fVar2 = 0.0;
  }
  fVar10 = fVar6 * 0.0 - fVar2 * fVar9;
  fVar7 = fVar2 * fVar12 - fVar6;
  fVar2 = fVar9 - fVar12 * 0.0;
  fVar5 = fVar2 * fVar2 + fVar10 * fVar10 + fVar7 * fVar7;
  fVar3 = SQRT(fVar5);
  if (NAN(fVar3)) {
    fVar3 = (float)sqrtf(fVar5);
  }
  if (fVar4 <= fVar3) {
    fVar3 = 1.0 / fVar3;
    fVar10 = fVar3 * fVar10;
    fVar7 = fVar3 * fVar7;
    fVar2 = fVar3 * fVar2;
  }
  fVar5 = *param_3;
  fVar11 = param_3[1];
  fVar3 = param_3[2];
  fVar13 = fVar9 * fVar2 - fVar6 * fVar7;
  fVar14 = fVar6 * fVar10 - fVar12 * fVar2;
  fVar15 = fVar12 * fVar7 - fVar9 * fVar10;
  fVar16 = fVar9 * 0.0 + fVar14 * 0.0;
  fVar19 = fVar12 * 0.0 + fVar13 * 0.0;
  fVar17 = fVar6 * 0.0 + fVar15 * 0.0;
  fVar8 = fVar2 * 0.0;
  fVar18 = fVar7 * 0.0;
  fVar22 = fVar10 * 0.0;
  fVar20 = param_1 + (float)(int)(param_1 * _UNK_027ebdf4) * _UNK_027edb30;
  bVar1 = ((int)(param_1 * _UNK_027ebdf4) & 1U) != 0;
  fVar4 = fVar20;
  if (bVar1) {
    fVar4 = -fVar20;
  }
  fVar20 = fVar20 * fVar20;
  fVar21 = fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * _UNK_02964910 +
                                                                      _UNK_02964914) + _UNK_02964918
                                                            ) + _UNK_0296491c) + _UNK_02964920) +
                              _UNK_02964924) + -0.5);
  fVar4 = fVar4 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * (fVar20 * 
                                                  _UNK_02964928 + _UNK_0296492c) + _UNK_02964930) +
                                                  _UNK_02964934) + _UNK_02964938) + _UNK_0296493c) +
                            _UNK_02964940) + 1.0);
  fVar20 = -1.0 - fVar21;
  if (!bVar1) {
    fVar20 = fVar21 + 1.0;
  }
  param_2[1] = CONCAT44((fVar22 + fVar19) - (fVar3 * fVar10 + fVar12 * fVar11 + fVar5 * fVar13),
                        fVar10 + fVar19);
  *param_2 = CONCAT44(fVar22 + fVar20 * fVar12 + fVar4 * fVar13,
                      fVar22 + (fVar20 * fVar13 - fVar12 * fVar4));
  param_2[3] = CONCAT44((fVar18 + fVar16) - (fVar3 * fVar7 + fVar9 * fVar11 + fVar5 * fVar14),
                        fVar7 + fVar16);
  param_2[2] = CONCAT44(fVar18 + fVar20 * fVar9 + fVar4 * fVar14,
                        fVar18 + (fVar20 * fVar14 - fVar9 * fVar4));
  param_2[5] = CONCAT44((fVar8 + fVar17) - (fVar3 * fVar2 + fVar6 * fVar11 + fVar5 * fVar15),
                        fVar2 + fVar17);
  param_2[4] = CONCAT44(fVar8 + fVar20 * fVar6 + fVar4 * fVar15,
                        fVar8 + (fVar20 * fVar15 - fVar6 * fVar4));
  return;
}

// ==== Aska::Matrix34::SetLookAtMatrixZP(Aska::Vector const*, Aska::Vector const*, float)
// vaddr 0x1f3f648 | ghidra 0x203f648 | size 1016 | symbol _ZN4Aska8Matrix3417SetLookAtMatrixZPEPKNS_6VectorES3_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska8Matrix3417SetLookAtMatrixZPEPKNS_6VectorES3_f
               (float param_1,undefined8 *param_2,float *param_3,float *param_4)

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
  undefined8 uVar23;
  
  fVar7 = *param_4;
  fVar5 = param_4[1];
  uVar23 = *(undefined8 *)param_4;
  fVar6 = param_4[2];
  fVar3 = (float)*(undefined8 *)(param_4 + 2);
  fVar4 = fVar7 * fVar7 + fVar5 * fVar5 + fVar6 * fVar6;
  fVar2 = SQRT(fVar4);
  if (NAN(fVar2)) {
    fVar2 = (float)sqrtf(fVar4);
  }
  fVar4 = _UNK_027e519c;
  if (_UNK_027e519c <= fVar2) {
    fVar2 = 1.0 / fVar2;
    uVar23 = CONCAT44(fVar5 * fVar2,fVar7 * fVar2);
    fVar3 = fVar6 * fVar2;
  }
  fVar6 = (float)((ulong)uVar23 >> 0x20);
  fVar2 = 0.0;
  fVar5 = fVar6;
  if (ABS(fVar6) <= _UNK_02970cd0) {
    fVar2 = 1.0;
    fVar5 = 0.0;
  }
  fVar11 = param_4[2] * fVar2 - param_4[1] * fVar5;
  fVar8 = *param_4 * fVar5 - param_4[2] * 0.0;
  fVar2 = param_4[1] * 0.0 - *param_4 * fVar2;
  fVar7 = fVar2 * fVar2 + fVar11 * fVar11 + fVar8 * fVar8;
  fVar5 = SQRT(fVar7);
  if (NAN(fVar5)) {
    fVar5 = (float)sqrtf(fVar7);
  }
  if (fVar4 <= fVar5) {
    fVar5 = 1.0 / fVar5;
    fVar11 = fVar5 * fVar11;
    fVar8 = fVar5 * fVar8;
    fVar2 = fVar5 * fVar2;
  }
  fVar22 = (float)uVar23;
  fVar12 = *param_3;
  fVar14 = param_3[1];
  fVar16 = fVar22 * fVar8 - fVar6 * fVar11;
  fVar5 = param_3[2];
  fVar7 = fVar6 * fVar2 - fVar3 * fVar8;
  fVar15 = fVar3 * fVar11 - fVar22 * fVar2;
  fVar17 = fVar2 * 0.0 + fVar16 * 0.0;
  fVar20 = fVar8 * 0.0 + fVar15 * 0.0;
  fVar21 = fVar11 * 0.0 + fVar7 * 0.0;
  fVar13 = fVar3 * 0.0;
  fVar18 = fVar6 * 0.0;
  fVar19 = fVar22 * 0.0;
  fVar9 = param_1 + (float)(int)(param_1 * _UNK_027ebdf4) * _UNK_027edb30;
  bVar1 = ((int)(param_1 * _UNK_027ebdf4) & 1U) != 0;
  fVar4 = fVar9;
  if (bVar1) {
    fVar4 = -fVar9;
  }
  fVar9 = fVar9 * fVar9;
  fVar10 = fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * _UNK_02964910 +
                                                                _UNK_02964914) + _UNK_02964918) +
                                              _UNK_0296491c) + _UNK_02964920) + _UNK_02964924) +
                   -0.5);
  fVar4 = fVar4 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * _UNK_02964928 +
                                                                        _UNK_0296492c) +
                                                               _UNK_02964930) + _UNK_02964934) +
                                             _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) + 1.0)
  ;
  fVar9 = -1.0 - fVar10;
  if (!bVar1) {
    fVar9 = fVar10 + 1.0;
  }
  param_2[1] = CONCAT44((fVar19 + fVar21) - (fVar5 * fVar22 + fVar12 * fVar11 + fVar14 * fVar7),
                        fVar22 + fVar21);
  *param_2 = CONCAT44(fVar19 + fVar4 * fVar11 + fVar9 * fVar7,
                      fVar19 + (fVar9 * fVar11 - fVar7 * fVar4));
  param_2[3] = CONCAT44((fVar18 + fVar20) - (fVar6 * fVar5 + fVar12 * fVar8 + fVar14 * fVar15),
                        fVar6 + fVar20);
  param_2[2] = CONCAT44(fVar18 + fVar4 * fVar8 + fVar9 * fVar15,
                        fVar18 + (fVar9 * fVar8 - fVar15 * fVar4));
  param_2[5] = CONCAT44((fVar13 + fVar17) - (fVar5 * fVar3 + fVar12 * fVar2 + fVar14 * fVar16),
                        fVar3 + fVar17);
  param_2[4] = CONCAT44(fVar13 + fVar4 * fVar2 + fVar9 * fVar16,
                        fVar13 + (fVar9 * fVar2 - fVar16 * fVar4));
  return;
}

// ==== Aska::Matrix34::SetLookAtMatrixZN(Aska::Vector const*, Aska::Vector const*, float)
// vaddr 0x1f3fa40 | ghidra 0x203fa40 | size 1012 | symbol _ZN4Aska8Matrix3417SetLookAtMatrixZNEPKNS_6VectorES3_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska8Matrix3417SetLookAtMatrixZNEPKNS_6VectorES3_f
               (float param_1,undefined8 *param_2,float *param_3,float *param_4)

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
  
  fVar2 = *param_4;
  fVar4 = param_4[1];
  fVar6 = param_4[2];
  fVar12 = -fVar2;
  fVar11 = -fVar4;
  fVar4 = fVar2 * fVar2 + fVar4 * fVar4 + fVar6 * fVar6;
  fVar2 = SQRT(fVar4);
  fVar6 = -fVar6;
  if (NAN(fVar2)) {
    fVar2 = (float)sqrtf(fVar4);
  }
  fVar4 = _UNK_027e519c;
  if (_UNK_027e519c <= fVar2) {
    fVar2 = 1.0 / fVar2;
    fVar12 = fVar2 * fVar12;
    fVar11 = fVar2 * fVar11;
    fVar6 = fVar2 * fVar6;
  }
  fVar2 = 0.0;
  fVar16 = fVar6 * 0.0;
  fVar17 = fVar11 * 0.0;
  fVar3 = fVar11;
  if (ABS(fVar11) <= _UNK_02970cd0) {
    fVar2 = 1.0;
    fVar3 = 0.0;
  }
  fVar7 = fVar2 * fVar6 - fVar3 * fVar11;
  fVar8 = fVar3 * fVar12 - fVar16;
  fVar2 = fVar17 - fVar2 * fVar12;
  fVar5 = fVar2 * fVar2 + fVar7 * fVar7 + fVar8 * fVar8;
  fVar3 = SQRT(fVar5);
  if (NAN(fVar3)) {
    fVar3 = (float)sqrtf(fVar5);
  }
  if (fVar4 <= fVar3) {
    fVar3 = 1.0 / fVar3;
    fVar7 = fVar3 * fVar7;
    fVar8 = fVar3 * fVar8;
    fVar2 = fVar3 * fVar2;
  }
  fVar5 = *param_3;
  fVar9 = param_3[1];
  fVar3 = param_3[2];
  fVar13 = fVar11 * fVar2 - fVar6 * fVar8;
  fVar14 = fVar6 * fVar7 - fVar12 * fVar2;
  fVar15 = fVar12 * fVar8 - fVar11 * fVar7;
  fVar18 = fVar2 * 0.0 + fVar15 * 0.0;
  fVar19 = fVar8 * 0.0 + fVar14 * 0.0;
  fVar20 = fVar7 * 0.0 + fVar13 * 0.0;
  fVar22 = fVar12 * 0.0;
  fVar21 = param_1 + (float)(int)(param_1 * _UNK_027ebdf4) * _UNK_027edb30;
  bVar1 = ((int)(param_1 * _UNK_027ebdf4) & 1U) != 0;
  fVar4 = fVar21;
  if (bVar1) {
    fVar4 = -fVar21;
  }
  fVar21 = fVar21 * fVar21;
  fVar10 = fVar21 * (fVar21 * (fVar21 * (fVar21 * (fVar21 * (fVar21 * (fVar21 * _UNK_02964910 +
                                                                      _UNK_02964914) + _UNK_02964918
                                                            ) + _UNK_0296491c) + _UNK_02964920) +
                              _UNK_02964924) + -0.5);
  fVar4 = fVar4 * (fVar21 * (fVar21 * (fVar21 * (fVar21 * (fVar21 * (fVar21 * (fVar21 * 
                                                  _UNK_02964928 + _UNK_0296492c) + _UNK_02964930) +
                                                  _UNK_02964934) + _UNK_02964938) + _UNK_0296493c) +
                            _UNK_02964940) + 1.0);
  fVar21 = -1.0 - fVar10;
  if (!bVar1) {
    fVar21 = fVar10 + 1.0;
  }
  param_2[1] = CONCAT44((fVar22 + fVar20) - (fVar12 * fVar3 + fVar5 * fVar7 + fVar9 * fVar13),
                        fVar12 + fVar20);
  *param_2 = CONCAT44(fVar22 + fVar4 * fVar7 + fVar21 * fVar13,
                      fVar22 + (fVar21 * fVar7 - fVar13 * fVar4));
  param_2[3] = CONCAT44((fVar17 + fVar19) - (fVar11 * fVar3 + fVar5 * fVar8 + fVar9 * fVar14),
                        fVar11 + fVar19);
  param_2[2] = CONCAT44(fVar17 + fVar4 * fVar8 + fVar21 * fVar14,
                        fVar17 + (fVar21 * fVar8 - fVar14 * fVar4));
  param_2[5] = CONCAT44((fVar16 + fVar18) - (fVar6 * fVar3 + fVar5 * fVar2 + fVar9 * fVar15),
                        fVar6 + fVar18);
  param_2[4] = CONCAT44(fVar16 + fVar4 * fVar2 + fVar21 * fVar15,
                        fVar16 + (fVar21 * fVar2 - fVar15 * fVar4));
  return;
}

// ==== Aska::Matrix34::Mul(Aska::Matrix34 const*, Aska::Matrix34 const*)
// vaddr 0x214ab78 | ghidra 0x224ab78 | size 400 | symbol _ZN4Aska8Matrix343MulEPKS0_S2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8Matrix343MulEPKS0_S2_(undefined8 *param_1,float *param_2,float *param_3)

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
  
  fVar4 = param_3[2];
  fVar3 = param_3[3];
  fVar5 = param_3[6];
  fVar1 = param_3[7];
  fVar7 = param_2[8];
  fVar11 = param_2[9];
  fVar14 = param_2[10];
  fVar6 = param_3[10];
  fVar2 = param_3[0xb];
  fVar17 = param_3[1];
  fVar18 = param_3[5];
  fVar19 = param_3[9];
  fVar21 = *param_3;
  fVar22 = param_3[4];
  fVar23 = param_3[8];
  fVar8 = param_2[0xb];
  fVar9 = param_2[4];
  fVar12 = param_2[5];
  fVar15 = param_2[6];
  fVar20 = param_2[7];
  fVar10 = *param_2;
  fVar13 = param_2[1];
  fVar16 = param_2[2];
  param_1[1] = CONCAT44(param_2[3] + fVar10 * fVar3 + fVar13 * fVar1 + fVar16 * fVar2,
                        fVar10 * fVar4 + fVar13 * fVar5 + fVar16 * fVar6);
  *param_1 = CONCAT44(fVar10 * fVar17 + fVar13 * fVar18 + fVar16 * fVar19,
                      fVar10 * fVar21 + fVar13 * fVar22 + fVar16 * fVar23);
  param_1[3] = CONCAT44(fVar20 + fVar9 * fVar3 + fVar12 * fVar1 + fVar15 * fVar2,
                        fVar9 * fVar4 + fVar12 * fVar5 + fVar15 * fVar6);
  param_1[2] = CONCAT44(fVar9 * fVar17 + fVar12 * fVar18 + fVar15 * fVar19,
                        fVar9 * fVar21 + fVar12 * fVar22 + fVar15 * fVar23);
  param_1[5] = CONCAT44(fVar8 + fVar7 * fVar3 + fVar11 * fVar1 + fVar14 * fVar2,
                        fVar7 * fVar4 + fVar11 * fVar5 + fVar14 * fVar6);
  param_1[4] = CONCAT44(fVar7 * fVar17 + fVar11 * fVar18 + fVar14 * fVar19,
                        fVar7 * fVar21 + fVar11 * fVar22 + fVar14 * fVar23);
  return;
}
