// port/decomp/math/framework.c: Ghidra decompiles for the math subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:09 UTC: tools/decomp.sh '--into' 'math/framework' 'Framework::(CVector|CMatrix|CQuaternion)::'

// ==== Framework::CVector::IsLegal() const
// vaddr 0x11d5728 | ghidra 0x12d5728 | size 148 | symbol _ZNK9Framework7CVector7IsLegalEv | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZNK9Framework7CVector7IsLegalEv(undefined4 *param_1)

{
  int iVar1;
  ulong uVar2;
  undefined4 uVar3;
  
  uVar3 = *param_1;
  iVar1 = __isnanf(uVar3);
  if (iVar1 == 0) {
    uVar2 = __isfinitef(uVar3);
    if ((int)uVar2 == 0) {
      return uVar2;
    }
    uVar3 = param_1[1];
    iVar1 = __isnanf(uVar3);
    if (iVar1 == 0) {
      uVar2 = __isfinitef(uVar3);
      if ((int)uVar2 == 0) {
        return uVar2;
      }
      uVar3 = param_1[2];
      iVar1 = __isnanf(uVar3);
      if (iVar1 == 0) {
        uVar2 = __isfinitef(uVar3);
        if ((int)uVar2 == 0) {
          return uVar2;
        }
        uVar3 = param_1[3];
        iVar1 = __isnanf(uVar3);
        if (iVar1 == 0) {
          iVar1 = __isfinitef(uVar3);
          return (ulong)(iVar1 != 0);
        }
      }
    }
  }
  return 0;
}

// ==== Framework::CMatrix::IsLegal() const
// vaddr 0x123b6ec | ghidra 0x133b6ec | size 484 | symbol _ZNK9Framework7CMatrix7IsLegalEv | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZNK9Framework7CMatrix7IsLegalEv(undefined4 *param_1)

{
  int iVar1;
  ulong uVar2;
  undefined4 uVar3;
  
  uVar3 = *param_1;
  iVar1 = __isnanf(uVar3);
  if (iVar1 == 0) {
    uVar2 = __isfinitef(uVar3);
    if ((int)uVar2 == 0) {
      return uVar2;
    }
    uVar3 = param_1[1];
    iVar1 = __isnanf(uVar3);
    if (iVar1 == 0) {
      uVar2 = __isfinitef(uVar3);
      if ((int)uVar2 == 0) {
        return uVar2;
      }
      uVar3 = param_1[2];
      iVar1 = __isnanf(uVar3);
      if (iVar1 == 0) {
        uVar2 = __isfinitef(uVar3);
        if ((int)uVar2 == 0) {
          return uVar2;
        }
        uVar3 = param_1[3];
        iVar1 = __isnanf(uVar3);
        if (iVar1 == 0) {
          uVar2 = __isfinitef(uVar3);
          if ((int)uVar2 == 0) {
            return uVar2;
          }
          uVar3 = param_1[4];
          iVar1 = __isnanf(uVar3);
          if (iVar1 == 0) {
            uVar2 = __isfinitef(uVar3);
            if ((int)uVar2 == 0) {
              return uVar2;
            }
            uVar3 = param_1[5];
            iVar1 = __isnanf(uVar3);
            if (iVar1 == 0) {
              uVar2 = __isfinitef(uVar3);
              if ((int)uVar2 == 0) {
                return uVar2;
              }
              uVar3 = param_1[6];
              iVar1 = __isnanf(uVar3);
              if (iVar1 == 0) {
                uVar2 = __isfinitef(uVar3);
                if ((int)uVar2 == 0) {
                  return uVar2;
                }
                uVar3 = param_1[7];
                iVar1 = __isnanf(uVar3);
                if (iVar1 == 0) {
                  uVar2 = __isfinitef(uVar3);
                  if ((int)uVar2 == 0) {
                    return uVar2;
                  }
                  uVar3 = param_1[8];
                  iVar1 = __isnanf(uVar3);
                  if (iVar1 == 0) {
                    uVar2 = __isfinitef(uVar3);
                    if ((int)uVar2 == 0) {
                      return uVar2;
                    }
                    uVar3 = param_1[9];
                    iVar1 = __isnanf(uVar3);
                    if (iVar1 == 0) {
                      uVar2 = __isfinitef(uVar3);
                      if ((int)uVar2 == 0) {
                        return uVar2;
                      }
                      uVar3 = param_1[10];
                      iVar1 = __isnanf(uVar3);
                      if (iVar1 == 0) {
                        uVar2 = __isfinitef(uVar3);
                        if ((int)uVar2 == 0) {
                          return uVar2;
                        }
                        uVar3 = param_1[0xb];
                        iVar1 = __isnanf(uVar3);
                        if (iVar1 == 0) {
                          uVar2 = __isfinitef(uVar3);
                          if ((int)uVar2 == 0) {
                            return uVar2;
                          }
                          uVar3 = param_1[0xc];
                          iVar1 = __isnanf(uVar3);
                          if (iVar1 == 0) {
                            uVar2 = __isfinitef(uVar3);
                            if ((int)uVar2 == 0) {
                              return uVar2;
                            }
                            uVar3 = param_1[0xd];
                            iVar1 = __isnanf(uVar3);
                            if (iVar1 == 0) {
                              uVar2 = __isfinitef(uVar3);
                              if ((int)uVar2 == 0) {
                                return uVar2;
                              }
                              uVar3 = param_1[0xe];
                              iVar1 = __isnanf(uVar3);
                              if (iVar1 == 0) {
                                uVar2 = __isfinitef(uVar3);
                                if ((int)uVar2 == 0) {
                                  return uVar2;
                                }
                                uVar3 = param_1[0xf];
                                iVar1 = __isnanf(uVar3);
                                if (iVar1 == 0) {
                                  iVar1 = __isfinitef(uVar3);
                                  return (ulong)(iVar1 != 0);
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}

// ==== Framework::CMatrix::Translate(Framework::CVector const&)
// vaddr 0x1e89020 | ghidra 0x1f89020 | size 24 | symbol _ZN9Framework7CMatrix9TranslateERKNS_7CVectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CMatrix9TranslateERKNS_7CVectorE(long param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = param_2[1];
  uVar2 = param_2[2];
  *(undefined4 *)(param_1 + 0xc) = *param_2;
  *(undefined4 *)(param_1 + 0x1c) = uVar1;
  *(undefined4 *)(param_1 + 0x2c) = uVar2;
  return;
}

// ==== Framework::CMatrix::AddTranslate(Framework::CVector const&)
// vaddr 0x1e89038 | ghidra 0x1f89038 | size 48 | symbol _ZN9Framework7CMatrix12AddTranslateERKNS_7CVectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CMatrix12AddTranslateERKNS_7CVectorE(long param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  
  fVar1 = param_2[1];
  fVar2 = param_2[2];
  *(float *)(param_1 + 0xc) = *(float *)(param_1 + 0xc) + *param_2;
  *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x1c) + fVar1;
  *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + fVar2;
  return;
}

// ==== Framework::CMatrix::Translate() const
// vaddr 0x1e89068 | ghidra 0x1f89068 | size 28 | symbol _ZNK9Framework7CMatrix9TranslateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework7CMatrix9TranslateEv(undefined4 *param_1,long param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = *(undefined4 *)(param_2 + 0x1c);
  uVar2 = *(undefined4 *)(param_2 + 0x2c);
  *param_1 = *(undefined4 *)(param_2 + 0xc);
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  param_1[3] = 0x3f800000;
  return;
}

// ==== Framework::CMatrix::AddTranslateX(float)
// vaddr 0x1e89084 | ghidra 0x1f89084 | size 16 | symbol _ZN9Framework7CMatrix13AddTranslateXEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CMatrix13AddTranslateXEf(float param_1,long param_2)

{
  *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) + param_1;
  return;
}

// ==== Framework::CMatrix::AddTranslateY(float)
// vaddr 0x1e89094 | ghidra 0x1f89094 | size 16 | symbol _ZN9Framework7CMatrix13AddTranslateYEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CMatrix13AddTranslateYEf(float param_1,long param_2)

{
  *(float *)(param_2 + 0x1c) = *(float *)(param_2 + 0x1c) + param_1;
  return;
}

// ==== Framework::CMatrix::AddTranslateZ(float)
// vaddr 0x1e890a4 | ghidra 0x1f890a4 | size 16 | symbol _ZN9Framework7CMatrix13AddTranslateZEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CMatrix13AddTranslateZEf(float param_1,long param_2)

{
  *(float *)(param_2 + 0x2c) = *(float *)(param_2 + 0x2c) + param_1;
  return;
}

// ==== Framework::CMatrix::RotateYWithoutTranslate(float)
// vaddr 0x1e890b4 | ghidra 0x1f890b4 | size 64 | symbol _ZN9Framework7CMatrix23RotateYWithoutTranslateEf | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework7CMatrix23RotateYWithoutTranslateEf(long param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = *(undefined4 *)(param_1 + 0xc);
  uVar2 = *(undefined4 *)(param_1 + 0x1c);
  uVar3 = *(undefined4 *)(param_1 + 0x2c);
  Aska::Matrix::RotateY(float)();
  *(undefined4 *)(param_1 + 0xc) = uVar1;
  *(undefined4 *)(param_1 + 0x1c) = uVar2;
  *(undefined4 *)(param_1 + 0x2c) = uVar3;
  return param_1;
}

// ==== Framework::CMatrix::AngleY() const
// vaddr 0x1e8929c | ghidra 0x1f8929c | size 176 | symbol _ZNK9Framework7CMatrix6AngleYEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK9Framework7CMatrix6AngleYEv(float *param_1)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [12];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  
  auVar4 = *(undefined1 (*) [12])(param_1 + 8);
  fVar7 = *param_1 * _UNK_027f7c00;
  fVar8 = param_1[1] * _UNK_027f7c04;
  fVar9 = param_1[4] * _UNK_027f7c00;
  fVar10 = param_1[5] * _UNK_027f7c04;
  auVar5._0_4_ = auVar4._0_4_ * _UNK_027f7c00;
  auVar5._4_4_ = auVar4._4_4_ * _UNK_027f7c04;
  auVar5._8_4_ = auVar4._8_4_ * _UNK_027f7c08;
  auVar5._12_4_ = _UNK_027f7c0c * 0.0;
  auVar11._4_4_ = fVar8;
  auVar11._0_4_ = fVar7;
  auVar11._8_4_ = param_1[2] * _UNK_027f7c08;
  auVar11._12_4_ = _UNK_027f7c0c * 0.0;
  auVar12._4_4_ = fVar8;
  auVar12._0_4_ = fVar7;
  auVar12._8_4_ = param_1[2] * _UNK_027f7c08;
  auVar12._12_4_ = _UNK_027f7c0c * 0.0;
  auVar12 = NEON_ext(auVar11,auVar12,8,1);
  auVar13._4_4_ = fVar10;
  auVar13._0_4_ = fVar9;
  auVar13._8_4_ = param_1[6] * _UNK_027f7c08;
  auVar13._12_4_ = _UNK_027f7c0c * 0.0;
  auVar1._4_4_ = fVar10;
  auVar1._0_4_ = fVar9;
  auVar1._8_4_ = param_1[6] * _UNK_027f7c08;
  auVar1._12_4_ = _UNK_027f7c0c * 0.0;
  auVar11 = NEON_ext(auVar13,auVar1,8,1);
  auVar13 = NEON_ext(auVar5,auVar5,8,1);
  auVar2._4_4_ = param_1[0xd] * _UNK_027f7c04;
  auVar2._0_4_ = param_1[0xc] * _UNK_027f7c00;
  auVar2._8_4_ = param_1[0xe] * _UNK_027f7c08;
  auVar2._12_4_ = _UNK_027f7c0c * 1.0;
  auVar3._4_4_ = param_1[0xd] * _UNK_027f7c04;
  auVar3._0_4_ = param_1[0xc] * _UNK_027f7c00;
  auVar3._8_4_ = param_1[0xe] * _UNK_027f7c08;
  auVar3._12_4_ = _UNK_027f7c0c * 1.0;
  NEON_ext(auVar2,auVar3,8,1);
  auVar6._4_4_ = auVar11._0_4_ + fVar9 + auVar11._4_4_ + fVar10;
  auVar6._0_4_ = auVar12._0_4_ + fVar7 + auVar12._4_4_ + fVar8;
  auVar6._8_8_ = 0;
  (*(code *)PTR_atan2f_02cad788)(auVar6,auVar13._0_4_ + auVar5._0_4_ + auVar13._4_4_ + auVar5._4_4_)
  ;
  return;
}

// ==== Framework::CMatrix::ExtractRotate() const
// vaddr 0x1e8934c | ghidra 0x1f8934c | size 72 | symbol _ZNK9Framework7CMatrix13ExtractRotateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework7CMatrix13ExtractRotateEv(undefined8 *param_1,undefined8 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  
  uVar3 = *(undefined4 *)(param_2 + 1);
  uVar1 = *(undefined4 *)(param_2 + 2);
  uVar2 = *(undefined4 *)((long)param_2 + 0x14);
  uVar4 = *(undefined4 *)(param_2 + 3);
  uVar7 = param_2[4];
  uVar5 = *(undefined4 *)(param_2 + 5);
  uVar8 = param_2[6];
  uVar6 = *(undefined4 *)(param_2 + 7);
  *param_1 = *param_2;
  *(undefined4 *)(param_1 + 1) = uVar3;
  *(undefined4 *)((long)param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 2) = uVar1;
  *(undefined4 *)((long)param_1 + 0x14) = uVar2;
  *(undefined4 *)(param_1 + 3) = uVar4;
  *(undefined4 *)((long)param_1 + 0x1c) = 0;
  param_1[4] = uVar7;
  *(undefined4 *)(param_1 + 5) = uVar5;
  *(undefined4 *)((long)param_1 + 0x2c) = 0;
  param_1[6] = uVar8;
  *(undefined4 *)(param_1 + 7) = uVar6;
  *(undefined4 *)((long)param_1 + 0x3c) = 0x3f800000;
  return;
}

// ==== Framework::CMatrix::ExtractRotate(Framework::CMatrix const&)
// vaddr 0x1e89394 | ghidra 0x1f89394 | size 60 | symbol _ZN9Framework7CMatrix13ExtractRotateERKS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CMatrix13ExtractRotateERKS0_(undefined8 *param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = *param_2;
  param_1[1] = param_2[1];
  *param_1 = uVar1;
  uVar1 = param_2[2];
  param_1[3] = param_2[3];
  param_1[2] = uVar1;
  uVar1 = param_2[4];
  param_1[5] = param_2[5];
  param_1[4] = uVar1;
  uVar2 = param_2[7];
  uVar1 = param_2[6];
  *(undefined4 *)((long)param_1 + 0xc) = *(undefined4 *)((long)param_1 + 0xc);
  *(undefined4 *)((long)param_1 + 0x1c) = *(undefined4 *)((long)param_1 + 0x1c);
  *(undefined4 *)((long)param_1 + 0x2c) = *(undefined4 *)((long)param_1 + 0x2c);
  param_1[7] = uVar2;
  param_1[6] = uVar1;
  return;
}

// ==== Framework::CMatrix::Inverse()
// vaddr 0x1e893d0 | ghidra 0x1f893d0 | size 152 | symbol _ZN9Framework7CMatrix7InverseEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework7CMatrix7InverseEv(float *param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  uVar2 = _UNK_027dbb38;
  uVar1 = _UNK_027dbb30;
  fVar3 = param_1[2];
  fVar4 = param_1[3];
  fVar5 = param_1[6];
  fVar6 = param_1[7];
  fVar7 = param_1[0xb];
  *(ulong *)(param_1 + 2) =
       CONCAT44(-(*param_1 * fVar4 + param_1[4] * fVar6 + param_1[8] * fVar7),param_1[8]);
  *(ulong *)param_1 = CONCAT44(param_1[4],*param_1);
  *(ulong *)(param_1 + 6) =
       CONCAT44(-(param_1[1] * fVar4 + param_1[5] * fVar6 + param_1[9] * fVar7),param_1[9]);
  *(ulong *)(param_1 + 4) = CONCAT44(param_1[5],param_1[1]);
  *(ulong *)(param_1 + 10) =
       CONCAT44(-(fVar3 * fVar4 + fVar5 * fVar6 + param_1[10] * fVar7),param_1[10]);
  *(ulong *)(param_1 + 8) = CONCAT44(fVar5,fVar3);
  *(undefined8 *)(param_1 + 0xe) = uVar2;
  *(undefined8 *)(param_1 + 0xc) = uVar1;
  return;
}

// ==== Framework::CMatrix::InverseMathematical()
// vaddr 0x1e89468 | ghidra 0x1f89468 | size 24 | symbol _ZN9Framework7CMatrix19InverseMathematicalEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN9Framework7CMatrix19InverseMathematicalEv(undefined8 param_1)

{
  Aska::Matrix::Invert()();
  return param_1;
}

// ==== Framework::CMatrix::LookAtMatrixZPUp(Framework::CVector const&, Framework::CVector const&, Framework::CVector const&, float)
// vaddr 0x1e897d8 | ghidra 0x1f897d8 | size 24 | symbol _ZN9Framework7CMatrix16LookAtMatrixZPUpERKNS_7CVectorES3_S3_f | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN9Framework7CMatrix16LookAtMatrixZPUpERKNS_7CVectorES3_S3_f(undefined8 param_1)

{
  Aska::Matrix::SetLookAtMatrixZPUp(Aska::Vector const*, Aska::Vector const*, Aska::Vector const*, float)();
  return param_1;
}

// ==== Framework::CMatrix::SetRowVector(unsigned int, Framework::CVector const&)
// vaddr 0x1e897f0 | ghidra 0x1f897f0 | size 40 | symbol _ZN9Framework7CMatrix12SetRowVectorEjRKNS_7CVectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CMatrix12SetRowVectorEjRKNS_7CVectorE
               (long param_1,int param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(param_1 + (long)param_2 * 0x10);
  *puVar1 = *param_3;
  puVar1[1] = param_3[1];
  puVar1[2] = param_3[2];
  puVar1[3] = param_3[3];
  return;
}

// ==== Framework::CMatrix::ApplyScale(float)
// vaddr 0x1e89818 | ghidra 0x1f89818 | size 32 | symbol _ZN9Framework7CMatrix10ApplyScaleEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CMatrix10ApplyScaleEf(float param_1,undefined8 *param_2)

{
  param_2[1] = CONCAT44((float)((ulong)param_2[1] >> 0x20) * param_1,(float)param_2[1] * param_1);
  *param_2 = CONCAT44((float)((ulong)*param_2 >> 0x20) * param_1,(float)*param_2 * param_1);
  param_2[3] = CONCAT44((float)((ulong)param_2[3] >> 0x20) * param_1,(float)param_2[3] * param_1);
  param_2[2] = CONCAT44((float)((ulong)param_2[2] >> 0x20) * param_1,(float)param_2[2] * param_1);
  param_2[5] = CONCAT44((float)((ulong)param_2[5] >> 0x20) * param_1,(float)param_2[5] * param_1);
  param_2[4] = CONCAT44((float)((ulong)param_2[4] >> 0x20) * param_1,(float)param_2[4] * param_1);
  return;
}

// ==== Framework::CMatrix::ApplyScale(Framework::CVector const&)
// vaddr 0x1e89838 | ghidra 0x1f89838 | size 108 | symbol _ZN9Framework7CMatrix10ApplyScaleERKNS_7CVectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CMatrix10ApplyScaleERKNS_7CVectorE(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar1 = *param_2;
  fVar2 = param_2[1];
  fVar3 = param_2[2];
  *param_1 = fVar1 * *param_1;
  param_1[1] = fVar1 * param_1[1];
  param_1[2] = fVar1 * param_1[2];
  param_1[3] = fVar1 * param_1[3];
  param_1[4] = fVar2 * param_1[4];
  param_1[5] = fVar2 * param_1[5];
  param_1[6] = fVar2 * param_1[6];
  param_1[7] = fVar2 * param_1[7];
  param_1[8] = fVar3 * param_1[8];
  param_1[9] = fVar3 * param_1[9];
  param_1[10] = fVar3 * param_1[10];
  param_1[0xb] = fVar3 * param_1[0xb];
  return;
}

// ==== Framework::CMatrix::PutBasisVector(int) const
// vaddr 0x1e898a4 | ghidra 0x1f898a4 | size 96 | symbol _ZNK9Framework7CMatrix14PutBasisVectorEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework7CMatrix14PutBasisVectorEi(undefined4 *param_1,long param_2,uint param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (3 < param_3) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02964948/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Math_Matrix.cpp"*/,0x91,&UNK_0296499f/*"Invalid nAxis=%d"*/,param_3);
  }
  puVar1 = (undefined4 *)(param_2 + (long)(int)param_3 * 4);
  uVar2 = puVar1[4];
  uVar3 = puVar1[8];
  *param_1 = *puVar1;
  param_1[1] = uVar2;
  param_1[2] = uVar3;
  param_1[3] = 0x3f800000;
  return;
}

// ==== Framework::CMatrix::PutPRS(Framework::CVector*, Framework::CQuaternion*, Framework::CVector*) const
// vaddr 0x1e89904 | ghidra 0x1f89904 | size 4 | symbol _ZNK9Framework7CMatrix6PutPRSEPNS_7CVectorEPNS_11CQuaternionES2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework7CMatrix6PutPRSEPNS_7CVectorEPNS_11CQuaternionES2_(void)

{
  (*(code *)PTR__ZNK4Aska6Matrix6PutPRSEPNS_6VectorEPNS_10QuaternionES2__02ca43f0)();
  return;
}

// ==== Framework::CMatrix::ExtractRotateX() const
// vaddr 0x1e89908 | ghidra 0x1f89908 | size 52 | symbol _ZNK9Framework7CMatrix14ExtractRotateXEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework7CMatrix14ExtractRotateXEv(undefined4 *param_1,long param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar1 = *(undefined4 *)(param_2 + 0x14);
  uVar3 = *(undefined4 *)(param_2 + 0x18);
  uVar2 = *(undefined4 *)(param_2 + 0x24);
  uVar4 = *(undefined4 *)(param_2 + 0x28);
  *(undefined8 *)(param_1 + 3) = 0;
  *(undefined8 *)(param_1 + 1) = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  *(undefined8 *)(param_1 + 0xb) = 0;
  *(undefined8 *)(param_1 + 0xd) = 0;
  *param_1 = 0x3f800000;
  param_1[5] = uVar1;
  param_1[6] = uVar3;
  param_1[9] = uVar2;
  param_1[10] = uVar4;
  param_1[0xf] = 0x3f800000;
  return;
}

// ==== Framework::CMatrix::ExtractRotateY() const
// vaddr 0x1e8993c | ghidra 0x1f8993c | size 64 | symbol _ZNK9Framework7CMatrix14ExtractRotateYEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK9Framework7CMatrix14ExtractRotateYEv(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  
  uVar6 = _UNK_027dbb28;
  uVar5 = _UNK_027dbb20;
  uVar1 = *param_2;
  uVar2 = param_2[2];
  uVar3 = param_2[8];
  uVar4 = param_2[10];
  *(undefined8 *)(param_1 + 0xb) = 0;
  *(undefined8 *)(param_1 + 0xd) = 0;
  *param_1 = uVar1;
  param_1[1] = 0;
  param_1[2] = uVar2;
  param_1[7] = 0;
  param_1[8] = uVar3;
  param_1[9] = 0;
  param_1[10] = uVar4;
  *(undefined8 *)(param_1 + 5) = uVar6;
  *(undefined8 *)(param_1 + 3) = uVar5;
  param_1[0xf] = 0x3f800000;
  return;
}

// ==== Framework::CMatrix::ExtractRotateZ() const
// vaddr 0x1e8997c | ghidra 0x1f8997c | size 48 | symbol _ZNK9Framework7CMatrix14ExtractRotateZEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework7CMatrix14ExtractRotateZEv(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar1 = *param_2;
  uVar3 = param_2[1];
  uVar2 = param_2[4];
  uVar4 = param_2[5];
  *(undefined8 *)(param_1 + 2) = 0;
  *(undefined8 *)(param_1 + 6) = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + 0xb) = 0;
  *(undefined8 *)(param_1 + 0xd) = 0;
  param_1[10] = 0x3f800000;
  *param_1 = uVar1;
  param_1[1] = uVar3;
  param_1[4] = uVar2;
  param_1[5] = uVar4;
  param_1[0xf] = 0x3f800000;
  return;
}

// ==== Framework::CMatrix::ExtractTranslate() const
// vaddr 0x1e899ac | ghidra 0x1f899ac | size 64 | symbol _ZNK9Framework7CMatrix16ExtractTranslateEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK9Framework7CMatrix16ExtractTranslateEv(undefined8 *param_1,long param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  
  uVar1 = *(undefined4 *)(param_2 + 0xc);
  uVar2 = *(undefined4 *)(param_2 + 0x1c);
  uVar3 = *(undefined4 *)(param_2 + 0x2c);
  *param_1 = 0x3f800000;
  *(undefined8 *)((long)param_1 + 0x14) = 0x3f800000;
  *(undefined8 *)((long)param_1 + 0x24) = 0x3f80000000000000;
  uVar5 = _UNK_027dbb38;
  uVar4 = _UNK_027dbb30;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)(param_1 + 1) = 0;
  *(undefined4 *)((long)param_1 + 0xc) = uVar1;
  *(undefined4 *)((long)param_1 + 0x1c) = uVar2;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)((long)param_1 + 0x2c) = uVar3;
  param_1[7] = uVar5;
  param_1[6] = uVar4;
  return;
}

// ==== Framework::CMatrix::Quaternion() const
// vaddr 0x1e899ec | ghidra 0x1f899ec | size 48 | symbol _ZNK9Framework7CMatrix10QuaternionEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework7CMatrix10QuaternionEv(undefined8 *param_1,undefined8 param_2)

{
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  Aska::Quaternion::Create(Aska::Matrix const*)(&uStack_20,param_2);
  param_1[1] = uStack_18;
  *param_1 = uStack_20;
  return;
}

// ==== Framework::CMatrix::GetInverse() const
// vaddr 0x1e89a1c | ghidra 0x1f89a1c | size 180 | symbol _ZNK9Framework7CMatrix10GetInverseEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK9Framework7CMatrix10GetInverseEv(undefined8 *param_1,undefined8 *param_2)

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
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  
  uVar2 = _UNK_027dbb38;
  uVar1 = _UNK_027dbb30;
  fVar12 = (float)((ulong)*param_2 >> 0x20);
  fVar8 = (float)((ulong)param_2[2] >> 0x20);
  fVar13 = (float)param_2[1];
  fVar9 = (float)param_2[3];
  fVar14 = (float)((ulong)param_2[1] >> 0x20);
  fVar10 = (float)((ulong)param_2[3] >> 0x20);
  fVar11 = (float)*param_2;
  fVar7 = (float)param_2[2];
  fVar4 = (float)((ulong)param_2[4] >> 0x20);
  fVar5 = (float)param_2[5];
  fVar6 = (float)((ulong)param_2[5] >> 0x20);
  fVar3 = (float)param_2[4];
  param_1[1] = CONCAT44(-(fVar14 * fVar11 + fVar10 * fVar7 + fVar6 * fVar3),fVar3);
  *param_1 = CONCAT44(fVar7,fVar11);
  param_1[3] = CONCAT44(-(fVar12 * fVar14 + fVar8 * fVar10 + fVar4 * fVar6),fVar4);
  param_1[2] = CONCAT44(fVar8,fVar12);
  param_1[5] = CONCAT44(-(fVar13 * fVar14 + fVar9 * fVar10 + fVar5 * fVar6),fVar5);
  param_1[4] = CONCAT44(fVar9,fVar13);
  param_1[7] = uVar2;
  param_1[6] = uVar1;
  return;
}

// ==== Framework::CMatrix::GetInverseMathematical() const
// vaddr 0x1e89ad0 | ghidra 0x1f89ad0 | size 40 | symbol _ZNK9Framework7CMatrix22GetInverseMathematicalEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework7CMatrix22GetInverseMathematicalEv(undefined8 *param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  
  uVar1 = *param_2;
  param_1[1] = param_2[1];
  *param_1 = uVar1;
  uVar1 = param_2[2];
  param_1[3] = param_2[3];
  param_1[2] = uVar1;
  uVar1 = param_2[4];
  param_1[5] = param_2[5];
  param_1[4] = uVar1;
  uVar1 = param_2[6];
  param_1[7] = param_2[7];
  param_1[6] = uVar1;
  (*(code *)PTR__ZN4Aska6Matrix6InvertEv_02c9da38)(param_1);
  return;
}

// ==== Framework::CMatrix::MakeIdentity()
// vaddr 0x1e89af8 | ghidra 0x1f89af8 | size 44 | symbol _ZN9Framework7CMatrix12MakeIdentityEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework7CMatrix12MakeIdentityEv(undefined8 *param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb28;
  uVar4 = _UNK_027dbb20;
  uVar3 = _UNK_027dbb18;
  uVar2 = _UNK_027dbb10;
  uVar1 = _UNK_027dbb00;
  param_1[1] = _UNK_027dbb08;
  *param_1 = uVar1;
  param_1[3] = uVar3;
  param_1[2] = uVar2;
  param_1[5] = uVar5;
  param_1[4] = uVar4;
  param_1[7] = uVar7;
  param_1[6] = uVar6;
  return;
}

// ==== Framework::CMatrix::MakeTranslate(Framework::CVector const&)
// vaddr 0x1e89b24 | ghidra 0x1f89b24 | size 64 | symbol _ZN9Framework7CMatrix13MakeTranslateERKNS_7CVectorE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework7CMatrix13MakeTranslateERKNS_7CVectorE(undefined8 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  
  uVar9 = _UNK_027dbb38;
  uVar8 = _UNK_027dbb30;
  uVar7 = _UNK_027dbb28;
  uVar6 = _UNK_027dbb20;
  uVar5 = _UNK_027dbb18;
  uVar4 = _UNK_027dbb10;
  uVar3 = _UNK_027dbb00;
  param_1[1] = _UNK_027dbb08;
  *param_1 = uVar3;
  param_1[3] = uVar5;
  param_1[2] = uVar4;
  param_1[5] = uVar7;
  param_1[4] = uVar6;
  param_1[7] = uVar9;
  param_1[6] = uVar8;
  uVar1 = param_2[1];
  uVar2 = param_2[2];
  *(undefined4 *)((long)param_1 + 0xc) = *param_2;
  *(undefined4 *)((long)param_1 + 0x1c) = uVar1;
  *(undefined4 *)((long)param_1 + 0x2c) = uVar2;
  return;
}

// ==== Framework::CMatrix::MakeTranslateX(float)
// vaddr 0x1e89b64 | ghidra 0x1f89b64 | size 56 | symbol _ZN9Framework7CMatrix14MakeTranslateXEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework7CMatrix14MakeTranslateXEf(undefined8 *param_1,undefined4 param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb28;
  uVar4 = _UNK_027dbb20;
  uVar3 = _UNK_027dbb18;
  uVar2 = _UNK_027dbb10;
  uVar1 = _UNK_027dbb00;
  param_1[1] = _UNK_027dbb08;
  *param_1 = uVar1;
  param_1[3] = uVar3;
  param_1[2] = uVar2;
  *(undefined4 *)((long)param_1 + 0xc) = param_2;
  *(undefined4 *)((long)param_1 + 0x1c) = 0;
  param_1[5] = uVar5;
  param_1[4] = uVar4;
  param_1[7] = uVar7;
  param_1[6] = uVar6;
  *(undefined4 *)((long)param_1 + 0x2c) = 0;
  return;
}

// ==== Framework::CMatrix::MakeTranslateY(float)
// vaddr 0x1e89b9c | ghidra 0x1f89b9c | size 56 | symbol _ZN9Framework7CMatrix14MakeTranslateYEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework7CMatrix14MakeTranslateYEf(undefined8 *param_1,undefined4 param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb28;
  uVar4 = _UNK_027dbb20;
  uVar3 = _UNK_027dbb18;
  uVar2 = _UNK_027dbb10;
  uVar1 = _UNK_027dbb00;
  param_1[1] = _UNK_027dbb08;
  *param_1 = uVar1;
  param_1[3] = uVar3;
  param_1[2] = uVar2;
  *(undefined4 *)((long)param_1 + 0xc) = 0;
  *(undefined4 *)((long)param_1 + 0x1c) = param_2;
  param_1[5] = uVar5;
  param_1[4] = uVar4;
  param_1[7] = uVar7;
  param_1[6] = uVar6;
  *(undefined4 *)((long)param_1 + 0x2c) = 0;
  return;
}

// ==== Framework::CMatrix::MakeTranslateZ(float)
// vaddr 0x1e89bd4 | ghidra 0x1f89bd4 | size 56 | symbol _ZN9Framework7CMatrix14MakeTranslateZEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework7CMatrix14MakeTranslateZEf(undefined8 *param_1,undefined4 param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb28;
  uVar4 = _UNK_027dbb20;
  uVar3 = _UNK_027dbb18;
  uVar2 = _UNK_027dbb10;
  uVar1 = _UNK_027dbb00;
  param_1[1] = _UNK_027dbb08;
  *param_1 = uVar1;
  param_1[3] = uVar3;
  param_1[2] = uVar2;
  *(undefined4 *)((long)param_1 + 0xc) = 0;
  *(undefined4 *)((long)param_1 + 0x1c) = 0;
  param_1[5] = uVar5;
  param_1[4] = uVar4;
  param_1[7] = uVar7;
  param_1[6] = uVar6;
  *(undefined4 *)((long)param_1 + 0x2c) = param_2;
  return;
}

// ==== Framework::CMatrix::MakeRotate(Framework::CVector const&, unsigned int)
// vaddr 0x1e89c0c | ghidra 0x1f89c0c | size 64 | symbol _ZN9Framework7CMatrix10MakeRotateERKNS_7CVectorEj | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework7CMatrix10MakeRotateERKNS_7CVectorEj
               (undefined8 *param_1,undefined8 param_2,undefined4 param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb28;
  uVar4 = _UNK_027dbb20;
  uVar3 = _UNK_027dbb18;
  uVar2 = _UNK_027dbb10;
  uVar1 = _UNK_027dbb00;
  param_1[1] = _UNK_027dbb08;
  *param_1 = uVar1;
  param_1[3] = uVar3;
  param_1[2] = uVar2;
  param_1[5] = uVar5;
  param_1[4] = uVar4;
  param_1[7] = uVar7;
  param_1[6] = uVar6;
  (*(code *)PTR__ZN4Aska6Matrix11SetRotationEPKNS_6VectorE14EnumRotateType_02cb5590)
            (param_1,param_2,param_3);
  return;
}

// ==== Framework::CMatrix::MakeRotateX(float)
// vaddr 0x1e89c4c | ghidra 0x1f89c4c | size 368 | symbol _ZN9Framework7CMatrix11MakeRotateXEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework7CMatrix11MakeRotateXEf(undefined8 *param_1,float param_2)

{
  undefined8 uVar1;
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
  
  fVar10 = _UNK_02964910;
  fVar9 = _UNK_027edb30;
  fVar12 = _UNK_027ebdf4;
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb20;
  uVar4 = _UNK_027dbb18;
  uVar3 = _UNK_027dbb10;
  uVar2 = _UNK_027dbb08;
  uVar1 = _UNK_027dbb00;
  param_1[5] = _UNK_027dbb28;
  param_1[4] = uVar5;
  param_1[7] = uVar7;
  param_1[6] = uVar6;
  param_1[1] = uVar2;
  *param_1 = uVar1;
  param_1[3] = uVar4;
  param_1[2] = uVar3;
  fVar9 = param_2 + (float)(int)(param_2 * fVar12) * fVar9;
  bVar8 = ((int)(param_2 * fVar12) & 1U) != 0;
  fVar12 = fVar9;
  if (bVar8) {
    fVar12 = -fVar9;
  }
  fVar9 = fVar9 * fVar9;
  fVar11 = fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * fVar10 + _UNK_02964914) +
                                                       _UNK_02964918) + _UNK_0296491c) +
                                     _UNK_02964920) + _UNK_02964924) + -0.5);
  fVar10 = fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * _UNK_02964928 +
                                                                _UNK_0296492c) + _UNK_02964930) +
                                              _UNK_02964934) + _UNK_02964938) + _UNK_0296493c) +
                   _UNK_02964940) + 1.0;
  fVar9 = -1.0 - fVar11;
  if (!bVar8) {
    fVar9 = fVar11 + 1.0;
  }
  *param_1 = 0x3f800000;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 1) = 0;
  *(float *)((long)param_1 + 0x14) = fVar9;
  *(float *)(param_1 + 3) = -(fVar12 * fVar10);
  *(float *)((long)param_1 + 0x24) = fVar12 * fVar10;
  *(float *)(param_1 + 5) = fVar9;
  return;
}

// ==== Framework::CMatrix::MakeRotateY(float)
// vaddr 0x1e89dbc | ghidra 0x1f89dbc | size 376 | symbol _ZN9Framework7CMatrix11MakeRotateYEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework7CMatrix11MakeRotateYEf(float *param_1,float param_2)

{
  undefined8 uVar1;
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
  
  fVar10 = _UNK_02964910;
  fVar9 = _UNK_027edb30;
  fVar12 = _UNK_027ebdf4;
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb20;
  uVar4 = _UNK_027dbb18;
  uVar3 = _UNK_027dbb10;
  uVar2 = _UNK_027dbb08;
  uVar1 = _UNK_027dbb00;
  *(undefined8 *)(param_1 + 10) = _UNK_027dbb28;
  *(undefined8 *)(param_1 + 8) = uVar5;
  *(undefined8 *)(param_1 + 0xe) = uVar7;
  *(undefined8 *)(param_1 + 0xc) = uVar6;
  *(undefined8 *)(param_1 + 2) = uVar2;
  *(undefined8 *)param_1 = uVar1;
  *(undefined8 *)(param_1 + 6) = uVar4;
  *(undefined8 *)(param_1 + 4) = uVar3;
  fVar9 = param_2 + (float)(int)(param_2 * fVar12) * fVar9;
  bVar8 = ((int)(param_2 * fVar12) & 1U) != 0;
  fVar12 = fVar9;
  if (bVar8) {
    fVar12 = -fVar9;
  }
  fVar9 = fVar9 * fVar9;
  fVar11 = fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * fVar10 + _UNK_02964914) +
                                                       _UNK_02964918) + _UNK_0296491c) +
                                     _UNK_02964920) + _UNK_02964924) + -0.5);
  fVar10 = fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * _UNK_02964928 +
                                                                _UNK_0296492c) + _UNK_02964930) +
                                              _UNK_02964934) + _UNK_02964938) + _UNK_0296493c) +
                   _UNK_02964940) + 1.0;
  fVar9 = -1.0 - fVar11;
  if (!bVar8) {
    fVar9 = fVar11 + 1.0;
  }
  param_1[4] = 0.0;
  param_1[5] = 1.0;
  param_1[1] = 0.0;
  param_1[9] = 0.0;
  param_1[6] = 0.0;
  *param_1 = fVar9;
  param_1[8] = -(fVar12 * fVar10);
  param_1[2] = fVar12 * fVar10;
  param_1[10] = fVar9;
  return;
}

// ==== Framework::CMatrix::MakeRotateZ(float)
// vaddr 0x1e89f34 | ghidra 0x1f89f34 | size 368 | symbol _ZN9Framework7CMatrix11MakeRotateZEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework7CMatrix11MakeRotateZEf(float *param_1,float param_2)

{
  undefined8 uVar1;
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
  
  fVar10 = _UNK_02964910;
  fVar9 = _UNK_027edb30;
  fVar12 = _UNK_027ebdf4;
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb20;
  uVar4 = _UNK_027dbb18;
  uVar3 = _UNK_027dbb10;
  uVar2 = _UNK_027dbb08;
  uVar1 = _UNK_027dbb00;
  *(undefined8 *)(param_1 + 10) = _UNK_027dbb28;
  *(undefined8 *)(param_1 + 8) = uVar5;
  *(undefined8 *)(param_1 + 0xe) = uVar7;
  *(undefined8 *)(param_1 + 0xc) = uVar6;
  *(undefined8 *)(param_1 + 2) = uVar2;
  *(undefined8 *)param_1 = uVar1;
  *(undefined8 *)(param_1 + 6) = uVar4;
  *(undefined8 *)(param_1 + 4) = uVar3;
  fVar9 = param_2 + (float)(int)(param_2 * fVar12) * fVar9;
  bVar8 = ((int)(param_2 * fVar12) & 1U) != 0;
  fVar12 = fVar9;
  if (bVar8) {
    fVar12 = -fVar9;
  }
  fVar9 = fVar9 * fVar9;
  fVar11 = fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * fVar10 + _UNK_02964914) +
                                                       _UNK_02964918) + _UNK_0296491c) +
                                     _UNK_02964920) + _UNK_02964924) + -0.5);
  fVar10 = fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * _UNK_02964928 +
                                                                _UNK_0296492c) + _UNK_02964930) +
                                              _UNK_02964934) + _UNK_02964938) + _UNK_0296493c) +
                   _UNK_02964940) + 1.0;
  fVar9 = -1.0 - fVar11;
  if (!bVar8) {
    fVar9 = fVar11 + 1.0;
  }
  param_1[8] = 0.0;
  param_1[9] = 0.0;
  param_1[2] = 0.0;
  param_1[6] = 0.0;
  *param_1 = fVar9;
  param_1[1] = -(fVar12 * fVar10);
  param_1[4] = fVar12 * fVar10;
  param_1[5] = fVar9;
  param_1[10] = 1.0;
  return;
}

// ==== Framework::CMatrix::MakeScale(Framework::CVector const&)
// vaddr 0x1e8a0a4 | ghidra 0x1f8a0a4 | size 64 | symbol _ZN9Framework7CMatrix9MakeScaleERKNS_7CVectorE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework7CMatrix9MakeScaleERKNS_7CVectorE(float *param_1,float *param_2)

{
  undefined8 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  uVar1 = _UNK_027dbb30;
  *(undefined8 *)(param_1 + 0xe) = _UNK_027dbb38;
  *(undefined8 *)(param_1 + 0xc) = uVar1;
  fVar4 = param_2[1];
  fVar5 = param_2[2];
  fVar6 = *param_2 * 0.0;
  *param_1 = *param_2;
  param_1[1] = fVar6;
  fVar2 = fVar4 * 0.0;
  fVar3 = fVar5 * 0.0;
  param_1[2] = fVar6;
  param_1[3] = fVar6;
  param_1[4] = fVar2;
  param_1[5] = fVar4;
  param_1[6] = fVar2;
  param_1[7] = fVar2;
  param_1[8] = fVar3;
  param_1[9] = fVar3;
  param_1[10] = fVar5;
  param_1[0xb] = fVar3;
  return;
}

// ==== Framework::CMatrix::MakeScaleX(float)
// vaddr 0x1e8a0e4 | ghidra 0x1f8a0e4 | size 40 | symbol _ZN9Framework7CMatrix10MakeScaleXEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework7CMatrix10MakeScaleXEf(float *param_1,float param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  float fVar3;
  
  uVar2 = _UNK_027dbb38;
  uVar1 = _UNK_027dbb30;
  fVar3 = param_2 * 0.0;
  *param_1 = param_2;
  param_1[1] = fVar3;
  param_1[2] = fVar3;
  param_1[3] = fVar3;
  param_1[10] = 0.0;
  param_1[0xb] = 0.0;
  param_1[8] = 0.0;
  param_1[9] = 0.0;
  *(undefined8 *)(param_1 + 0xe) = uVar2;
  *(undefined8 *)(param_1 + 0xc) = uVar1;
  param_1[6] = 0.0;
  param_1[7] = 0.0;
  param_1[4] = 0.0;
  param_1[5] = 0.0;
  return;
}

// ==== Framework::CMatrix::MakeScaleY(float)
// vaddr 0x1e8a10c | ghidra 0x1f8a10c | size 40 | symbol _ZN9Framework7CMatrix10MakeScaleYEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework7CMatrix10MakeScaleYEf(undefined8 *param_1,float param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  float fVar3;
  
  uVar2 = _UNK_027dbb38;
  uVar1 = _UNK_027dbb30;
  fVar3 = param_2 * 0.0;
  *param_1 = 0;
  param_1[1] = 0;
  *(float *)(param_1 + 2) = fVar3;
  *(float *)((long)param_1 + 0x14) = param_2;
  *(float *)(param_1 + 3) = fVar3;
  *(float *)((long)param_1 + 0x1c) = fVar3;
  param_1[7] = uVar2;
  param_1[6] = uVar1;
  param_1[4] = 0;
  param_1[5] = 0;
  return;
}

// ==== Framework::CMatrix::MakeScaleZ(float)
// vaddr 0x1e8a134 | ghidra 0x1f8a134 | size 40 | symbol _ZN9Framework7CMatrix10MakeScaleZEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework7CMatrix10MakeScaleZEf(undefined8 *param_1,float param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  float fVar3;
  
  uVar2 = _UNK_027dbb38;
  uVar1 = _UNK_027dbb30;
  fVar3 = param_2 * 0.0;
  param_1[2] = 0;
  param_1[3] = 0;
  *param_1 = 0;
  param_1[1] = 0;
  *(float *)(param_1 + 4) = fVar3;
  *(float *)((long)param_1 + 0x24) = fVar3;
  param_1[7] = uVar2;
  param_1[6] = uVar1;
  *(float *)(param_1 + 5) = param_2;
  *(float *)((long)param_1 + 0x2c) = fVar3;
  return;
}

// ==== Framework::CMatrix::MakeLookAtMatrixZN(Framework::CVector const&, Framework::CVector const&, float)
// vaddr 0x1e8a15c | ghidra 0x1f8a15c | size 64 | symbol _ZN9Framework7CMatrix18MakeLookAtMatrixZNERKNS_7CVectorES3_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework7CMatrix18MakeLookAtMatrixZNERKNS_7CVectorES3_f
               (undefined8 *param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb28;
  uVar4 = _UNK_027dbb20;
  uVar3 = _UNK_027dbb18;
  uVar2 = _UNK_027dbb10;
  uVar1 = _UNK_027dbb00;
  param_1[1] = _UNK_027dbb08;
  *param_1 = uVar1;
  param_1[3] = uVar3;
  param_1[2] = uVar2;
  param_1[5] = uVar5;
  param_1[4] = uVar4;
  param_1[7] = uVar7;
  param_1[6] = uVar6;
  (*(code *)PTR__ZN4Aska6Matrix17SetLookAtMatrixZNEPKNS_6VectorES3_f_02c8f380)
            (param_1,param_2,param_3);
  return;
}

// ==== Framework::CMatrix::MakeLookAtMatrixZPUp(Framework::CVector const&, Framework::CVector const&, Framework::CVector const&, float)
// vaddr 0x1e8a19c | ghidra 0x1f8a19c | size 72 | symbol _ZN9Framework7CMatrix20MakeLookAtMatrixZPUpERKNS_7CVectorES3_S3_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework7CMatrix20MakeLookAtMatrixZPUpERKNS_7CVectorES3_S3_f
               (undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  
  uVar7 = _UNK_027dbb38;
  uVar6 = _UNK_027dbb30;
  uVar5 = _UNK_027dbb28;
  uVar4 = _UNK_027dbb20;
  uVar3 = _UNK_027dbb18;
  uVar2 = _UNK_027dbb10;
  uVar1 = _UNK_027dbb00;
  param_1[1] = _UNK_027dbb08;
  *param_1 = uVar1;
  param_1[3] = uVar3;
  param_1[2] = uVar2;
  param_1[5] = uVar5;
  param_1[4] = uVar4;
  param_1[7] = uVar7;
  param_1[6] = uVar6;
  (*(code *)PTR__ZN4Aska6Matrix19SetLookAtMatrixZPUpEPKNS_6VectorES3_S3_f_02ca09f8)
            (param_1,param_2,param_3,param_4);
  return;
}

// ==== Framework::CMatrix::PrintC(char const*) const
// vaddr 0x1e8a1e4 | ghidra 0x1f8a1e4 | size 4 | symbol _ZNK9Framework7CMatrix6PrintCEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework7CMatrix6PrintCEPKc(void)

{
  return;
}

// ==== Framework::CMatrix::PrintS(char const*) const
// vaddr 0x1e8a1e8 | ghidra 0x1f8a1e8 | size 4 | symbol _ZNK9Framework7CMatrix6PrintSEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework7CMatrix6PrintSEPKc(void)

{
  return;
}

// ==== Framework::CQuaternion::Matrix() const
// vaddr 0x1e8a1ec | ghidra 0x1f8a1ec | size 56 | symbol _ZNK9Framework11CQuaternion6MatrixEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework11CQuaternion6MatrixEv(undefined8 *param_1,undefined8 param_2)

{
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  Aska::Matrix::Create(Aska::Quaternion const*)(&uStack_50,param_2);
  param_1[1] = uStack_48;
  *param_1 = uStack_50;
  param_1[3] = uStack_38;
  param_1[2] = uStack_40;
  param_1[5] = uStack_28;
  param_1[4] = uStack_30;
  param_1[7] = uStack_18;
  param_1[6] = uStack_20;
  return;
}

// ==== Framework::CQuaternion::Set(Framework::CMatrix const&)
// vaddr 0x1e8a224 | ghidra 0x1f8a224 | size 4 | symbol _ZN9Framework11CQuaternion3SetERKNS_7CMatrixE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CQuaternion3SetERKNS_7CMatrixE(void)

{
  (*(code *)PTR__ZN4Aska10Quaternion6CreateEPKNS_6MatrixE_02c96e30)();
  return;
}

// ==== Framework::CQuaternion::Create(Framework::CVector const&, float)
// vaddr 0x1e8a228 | ghidra 0x1f8a228 | size 48 | symbol _ZN9Framework11CQuaternion6CreateERKNS_7CVectorEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CQuaternion6CreateERKNS_7CVectorEf
               (undefined4 param_1,undefined8 param_2,undefined8 *param_3)

{
  undefined8 uStack_20;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  uStack_20 = *param_3;
  uStack_18 = *(undefined4 *)(param_3 + 1);
  uStack_14 = param_1;
  Aska::Quaternion::Create(Aska::Vector const*)(param_2,&uStack_20);
  return;
}

// ==== Framework::CQuaternion::Create(Framework::CVector const&, Framework::CVector const&)
// vaddr 0x1e8a258 | ghidra 0x1f8a258 | size 4 | symbol _ZN9Framework11CQuaternion6CreateERKNS_7CVectorES3_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework11CQuaternion6CreateERKNS_7CVectorES3_(void)

{
  (*(code *)PTR__ZN4Aska10Quaternion6CreateEPKNS_6VectorES3__02c9d548)();
  return;
}

// ==== Framework::CQuaternion::PrintC(char const*) const
// vaddr 0x1e8a25c | ghidra 0x1f8a25c | size 4 | symbol _ZNK9Framework11CQuaternion6PrintCEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework11CQuaternion6PrintCEPKc(void)

{
  return;
}

// ==== Framework::CQuaternion::PrintfC(char const*) const
// vaddr 0x1e8a260 | ghidra 0x1f8a260 | size 4 | symbol _ZNK9Framework11CQuaternion7PrintfCEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework11CQuaternion7PrintfCEPKc(void)

{
  return;
}

// ==== Framework::CQuaternion::PrintS(char const*) const
// vaddr 0x1e8a264 | ghidra 0x1f8a264 | size 4 | symbol _ZNK9Framework11CQuaternion6PrintSEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework11CQuaternion6PrintSEPKc(void)

{
  return;
}

// ==== Framework::CQuaternion::PrintfS(char const*) const
// vaddr 0x1e8a268 | ghidra 0x1f8a268 | size 4 | symbol _ZNK9Framework11CQuaternion7PrintfSEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework11CQuaternion7PrintfSEPKc(void)

{
  return;
}

// ==== Framework::CVector::ToConstrainSelfInRange(Framework::CVector const&, float)
// vaddr 0x1e8a26c | ghidra 0x1f8a26c | size 256 | symbol _ZN9Framework7CVector22ToConstrainSelfInRangeERKS0_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float * _ZN9Framework7CVector22ToConstrainSelfInRangeERKS0_f
                  (float param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar5 = *param_2 - *param_3;
  fVar4 = param_2[1] - param_3[1];
  fVar3 = param_2[2] - param_3[2];
  fVar2 = fVar5 * fVar5 + fVar4 * fVar4 + fVar3 * fVar3;
  fVar1 = SQRT(fVar2);
  if (NAN(fVar1)) {
    fVar1 = (float)sqrtf(fVar2);
  }
  if (param_1 < fVar1) {
    fVar1 = SQRT(fVar2);
    if (NAN(fVar1)) {
      fVar1 = (float)sqrtf(fVar2);
    }
    if (_UNK_027e519c <= fVar1) {
      fVar1 = 1.0 / fVar1;
      fVar5 = fVar5 * fVar1;
      fVar4 = fVar4 * fVar1;
      fVar3 = fVar3 * fVar1;
    }
    fVar1 = param_3[1];
    fVar2 = param_3[2];
    *param_2 = *param_3 + fVar5 * param_1;
    param_2[1] = fVar4 * param_1 + fVar1;
    param_2[2] = fVar3 * param_1 + fVar2;
    param_2[3] = 1.0;
  }
  return param_2;
}

// ==== Framework::CVector::ToConstrainSelfInRangeWithoutY(Framework::CVector const&, float)
// vaddr 0x1e8a36c | ghidra 0x1f8a36c | size 256 | symbol _ZN9Framework7CVector30ToConstrainSelfInRangeWithoutYERKS0_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float * _ZN9Framework7CVector30ToConstrainSelfInRangeWithoutYERKS0_f
                  (float param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  if (ABS(param_2[1] - param_3[1]) <= param_1) {
    fVar2 = *param_2;
    fVar3 = param_2[2];
    fVar6 = *param_3;
    fVar5 = param_3[2];
    fVar8 = fVar2 - fVar6;
    fVar7 = fVar3 - fVar5;
    fVar4 = fVar7 * fVar7 + fVar8 * fVar8 + 0.0;
    fVar1 = SQRT(fVar4);
    if (NAN(fVar1)) {
      fVar1 = (float)sqrtf(fVar4);
    }
    if (param_1 < fVar1) {
      fVar2 = SQRT(fVar4);
      if (NAN(fVar2)) {
        fVar2 = (float)sqrtf(fVar4);
      }
      if (_UNK_027e519c <= fVar2) {
        fVar8 = fVar8 * (1.0 / fVar2);
        fVar7 = fVar7 * (1.0 / fVar2);
      }
      fVar2 = fVar6 + fVar8 * param_1;
      fVar3 = fVar5 + fVar7 * param_1;
    }
    *param_2 = fVar2;
    param_2[2] = fVar3;
  }
  return param_2;
}

// ==== Framework::CVector::ToConstrainSelfOutRange(Framework::CVector const&, float)
// vaddr 0x1e8a46c | ghidra 0x1f8a46c | size 256 | symbol _ZN9Framework7CVector23ToConstrainSelfOutRangeERKS0_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float * _ZN9Framework7CVector23ToConstrainSelfOutRangeERKS0_f
                  (float param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar5 = *param_2 - *param_3;
  fVar4 = param_2[1] - param_3[1];
  fVar3 = param_2[2] - param_3[2];
  fVar2 = fVar5 * fVar5 + fVar4 * fVar4 + fVar3 * fVar3;
  fVar1 = SQRT(fVar2);
  if (NAN(fVar1)) {
    fVar1 = (float)sqrtf(fVar2);
  }
  if (fVar1 < param_1) {
    fVar1 = SQRT(fVar2);
    if (NAN(fVar1)) {
      fVar1 = (float)sqrtf(fVar2);
    }
    if (_UNK_027e519c <= fVar1) {
      fVar1 = 1.0 / fVar1;
      fVar5 = fVar5 * fVar1;
      fVar4 = fVar4 * fVar1;
      fVar3 = fVar3 * fVar1;
    }
    fVar1 = param_3[1];
    fVar2 = param_3[2];
    *param_2 = *param_3 + fVar5 * param_1;
    param_2[1] = fVar4 * param_1 + fVar1;
    param_2[2] = fVar3 * param_1 + fVar2;
    param_2[3] = 1.0;
  }
  return param_2;
}

// ==== Framework::CVector::ToConstrainSelfOutRangeWithoutY(Framework::CVector const&, float)
// vaddr 0x1e8a56c | ghidra 0x1f8a56c | size 260 | symbol _ZN9Framework7CVector31ToConstrainSelfOutRangeWithoutYERKS0_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float * _ZN9Framework7CVector31ToConstrainSelfOutRangeWithoutYERKS0_f
                  (float param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  if (ABS(param_2[1] - param_3[1]) <= param_1 + param_1) {
    fVar2 = *param_2;
    fVar3 = param_2[2];
    fVar6 = *param_3;
    fVar5 = param_3[2];
    fVar8 = fVar2 - fVar6;
    fVar7 = fVar3 - fVar5;
    fVar4 = fVar7 * fVar7 + fVar8 * fVar8 + 0.0;
    fVar1 = SQRT(fVar4);
    if (NAN(fVar1)) {
      fVar1 = (float)sqrtf(fVar4);
    }
    if (fVar1 < param_1) {
      fVar2 = SQRT(fVar4);
      if (NAN(fVar2)) {
        fVar2 = (float)sqrtf(fVar4);
      }
      if (_UNK_027e519c <= fVar2) {
        fVar8 = fVar8 * (1.0 / fVar2);
        fVar7 = fVar7 * (1.0 / fVar2);
      }
      fVar2 = fVar6 + fVar8 * param_1;
      fVar3 = fVar5 + fVar7 * param_1;
    }
    *param_2 = fVar2;
    param_2[2] = fVar3;
  }
  return param_2;
}

// ==== Framework::CVector::TransformNormal(Framework::CMatrix const&)
// vaddr 0x1e8a670 | ghidra 0x1f8a670 | size 24 | symbol _ZN9Framework7CVector15TransformNormalERKNS_7CMatrixE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN9Framework7CVector15TransformNormalERKNS_7CMatrixE(undefined8 param_1)

{
  Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)();
  return param_1;
}

// ==== Framework::CVector::PrintC(char const*) const
// vaddr 0x1e8a688 | ghidra 0x1f8a688 | size 4 | symbol _ZNK9Framework7CVector6PrintCEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework7CVector6PrintCEPKc(void)

{
  return;
}

// ==== Framework::CVector::PrintfC(char const*) const
// vaddr 0x1e8a68c | ghidra 0x1f8a68c | size 4 | symbol _ZNK9Framework7CVector7PrintfCEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework7CVector7PrintfCEPKc(void)

{
  return;
}

// ==== Framework::CVector::PrintS(char const*) const
// vaddr 0x1e8a690 | ghidra 0x1f8a690 | size 4 | symbol _ZNK9Framework7CVector6PrintSEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework7CVector6PrintSEPKc(void)

{
  return;
}

// ==== Framework::CVector::PrintfS(char const*) const
// vaddr 0x1e8a694 | ghidra 0x1f8a694 | size 4 | symbol _ZNK9Framework7CVector7PrintfSEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework7CVector7PrintfSEPKc(void)

{
  return;
}

// ==== Framework::CVector::RegressionTest()
// vaddr 0x1e8a698 | ghidra 0x1f8a698 | size 4 | symbol _ZN9Framework7CVector14RegressionTestEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework7CVector14RegressionTestEv(void)

{
  return;
}
