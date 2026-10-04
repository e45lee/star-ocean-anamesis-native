// port/decomp/math/quaternion.c: Ghidra decompiles for the math subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:09 UTC: tools/decomp.sh '--into' 'math/quaternion' 'Aska::Quaternion::'

// ==== Aska::Quaternion::Create(Aska::Matrix const*)
// vaddr 0x1f576d0 | ghidra 0x20576d0 | size 408 | symbol _ZN4Aska10Quaternion6CreateEPKNS_6MatrixE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska10Quaternion6CreateEPKNS_6MatrixE(float *param_1,float *param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  float fVar6;
  float fVar7;
  
  fVar6 = *param_2 + param_2[5] + param_2[10] + param_2[0xf];
  if (1.0 <= fVar6) {
    fVar7 = SQRT(fVar6);
    if (NAN(fVar7)) {
      fVar7 = (float)sqrtf(fVar6);
    }
    param_1[3] = fVar7 * 0.5;
    fVar7 = 0.5 / fVar7;
    *param_1 = fVar7 * (param_2[9] - param_2[6]);
    param_1[1] = fVar7 * (param_2[2] - param_2[8]);
    param_1[2] = fVar7 * (param_2[4] - param_2[1]);
  }
  else {
    uVar3 = (ulong)(*param_2 <= param_2[5]);
    uVar1 = 2;
    if (param_2[10] <= param_2[uVar3 * 5]) {
      uVar1 = uVar3;
    }
    lVar5 = (long)*(int *)(&UNK_029715cc + uVar1 * 4);
    lVar4 = (long)*(int *)(&UNK_029715cc + lVar5 * 4);
    fVar7 = ((param_2[uVar1 * 5] - param_2[lVar5 * 5]) - param_2[lVar4 * 5]) + 1.0;
    fVar6 = SQRT(fVar7);
    if (NAN(fVar6)) {
      fVar6 = (float)sqrtf(fVar7);
    }
    param_1[uVar1] = fVar6 * 0.5;
    uVar2 = _UNK_027dbb30;
    if (fVar6 == 0.0) {
      *(undefined8 *)(param_1 + 2) = _UNK_027dbb38;
      *(undefined8 *)param_1 = uVar2;
    }
    else {
      fVar6 = 0.5 / fVar6;
      param_1[lVar5] = fVar6 * (param_2[uVar1 * 4 + lVar5] + param_2[lVar5 * 4 + uVar1]);
      param_1[lVar4] = fVar6 * (param_2[uVar1 * 4 + lVar4] + param_2[lVar4 * 4 + uVar1]);
      param_1[3] = -(fVar6 * (param_2[lVar5 * 4 + lVar4] - param_2[lVar4 * 4 + lVar5]));
    }
  }
  return;
}

// ==== Aska::Quaternion::Create(Aska::Vector const*)
// vaddr 0x1f57868 | ghidra 0x2057868 | size 488 | symbol _ZN4Aska10Quaternion6CreateEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska10Quaternion6CreateEPKNS_6VectorE(float *param_1,float *param_2)

{
  bool bVar1;
  uint uVar2;
  float *pfVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  
  pfVar3 = &fStack_30;
  fVar6 = *param_2 * *param_2 + param_2[1] * param_2[1] + param_2[2] * param_2[2];
  fVar4 = SQRT(fVar6);
  if (NAN(fVar4)) {
    fVar4 = (float)sqrtf(fVar6);
  }
  if (_UNK_027e519c <= fVar4) {
    fVar6 = *param_2 / fVar4;
    fStack_2c = param_2[1] / fVar4;
    fStack_28 = param_2[2] / fVar4;
    fStack_24 = param_2[3];
  }
  else {
    fStack_24 = param_2[3];
    fVar6 = *param_2;
    pfVar3 = param_2;
  }
  uVar2 = (uint)(fStack_24 * 0.5 * _UNK_027ebdf4);
  fVar5 = fStack_24 * 0.5 + (float)(int)uVar2 * _UNK_027edb30;
  bVar1 = (uVar2 & 1) == 0;
  fVar4 = -fVar5;
  if (bVar1) {
    fVar4 = fVar5;
  }
  fVar5 = fVar5 * fVar5;
  fVar7 = fVar5 * (fVar5 * (fVar5 * (fVar5 * (fVar5 * _UNK_02964910 + _UNK_02964914) + _UNK_02964918
                                    ) + _UNK_0296491c) + _UNK_02964920) + _UNK_02964924;
  fVar4 = fVar4 * (fVar5 * (fVar5 * (fVar5 * (fVar5 * (fVar5 * (fVar5 * (fVar5 * _UNK_02964928 +
                                                                        _UNK_0296492c) +
                                                               _UNK_02964930) + _UNK_02964934) +
                                             _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) + 1.0)
  ;
  *param_1 = fVar6 * fVar4;
  param_1[1] = pfVar3[1] * fVar4;
  fVar5 = fVar5 * (fVar5 * fVar7 + -0.5);
  fVar6 = -1.0 - fVar5;
  if (bVar1) {
    fVar6 = fVar5 + 1.0;
  }
  param_1[2] = pfVar3[2] * fVar4;
  param_1[3] = fVar6;
  return;
}

// ==== Aska::Quaternion::Create(Aska::Vector const*, Aska::Vector const*)
// vaddr 0x1f57a50 | ghidra 0x2057a50 | size 668 | symbol _ZN4Aska10Quaternion6CreateEPKNS_6VectorES3_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska10Quaternion6CreateEPKNS_6VectorES3_(undefined8 *param_1,float *param_2,float *param_3)

{
  undefined8 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  
  fVar3 = _UNK_027e519c;
  uVar1 = _UNK_027dbb30;
  fVar5 = *param_2;
  fVar2 = param_2[1];
  fVar6 = *param_3;
  fVar7 = param_3[1];
  fVar8 = param_3[2];
  fVar4 = param_2[2];
  fVar10 = fVar2 * fVar8 - fVar7 * fVar4;
  fVar9 = fVar5 * fVar7 - fVar2 * fVar6;
  fVar7 = fVar5 * fVar6 + fVar2 * fVar7 + fVar4 * fVar8;
  fVar6 = fVar4 * fVar6 - fVar5 * fVar8;
  fStack_44 = 1.0;
  if (((_UNK_027e519c <= ABS(fVar10)) || (_UNK_027e519c <= ABS(fVar6))) ||
     (_UNK_027e519c <= ABS(fVar9))) {
    fVar4 = fVar10 * fVar10 + fVar6 * fVar6 + fVar9 * fVar9;
    fVar2 = SQRT(fVar4);
    fStack_50 = fVar10;
    fStack_4c = fVar6;
    fStack_48 = fVar9;
    if (NAN(fVar2)) {
      fVar2 = (float)sqrtf(fVar4);
    }
    if (fVar3 <= fVar2) {
      fVar2 = 1.0 / fVar2;
      fStack_50 = fVar2 * fVar10;
      fStack_4c = fVar2 * fVar6;
      fStack_48 = fVar2 * fVar9;
    }
    fStack_44 = 0.0;
    if ((fVar7 <= 1.0) && (-1.0 <= fVar7)) {
      fVar3 = fVar7 * fVar7;
      fStack_44 = fVar7 * (fVar3 * (fVar3 * (fVar3 * (fVar3 * (fVar3 * (fVar3 * (fVar3 * 
                                                  _UNK_0297158c + _UNK_02971590) + _UNK_02971594) +
                                                  _UNK_02971598) + _UNK_0297159c) + _UNK_029715a0) +
                                   _UNK_029715a4) + _UNK_029715a8) + _UNK_027f7284;
    }
    goto code_r0x02057cc8;
  }
  if (0.0 < fVar7) {
    param_1[1] = _UNK_027dbb38;
    *param_1 = uVar1;
    return;
  }
  if (fVar4 == 0.0) {
    if (fVar2 != 0.0) {
      fVar9 = 0.0;
      if (fVar5 == 0.0) goto code_r0x02057c50;
      fVar6 = -fVar5;
      fVar10 = fVar2;
    }
  }
  else if (fVar2 == 0.0) {
    if (fVar5 == 0.0) {
code_r0x02057c50:
      fVar9 = 0.0;
      fVar4 = 1.0;
    }
    else {
      fVar9 = -fVar5;
    }
    fVar6 = 0.0;
    fVar10 = fVar4;
  }
  else {
    fVar9 = -fVar2;
    fVar10 = 0.0;
    fVar6 = fVar4;
  }
  fStack_44 = 1.0;
  fVar4 = fVar10 * fVar10 + fVar6 * fVar6 + fVar9 * fVar9;
  fVar2 = SQRT(fVar4);
  fStack_50 = fVar10;
  fStack_4c = fVar6;
  fStack_48 = fVar9;
  if (NAN(fVar2)) {
    fVar2 = (float)sqrtf(fVar4);
  }
  if (fVar3 <= fVar2) {
    fVar2 = 1.0 / fVar2;
    fStack_50 = fVar2 * fVar10;
    fStack_4c = fVar2 * fVar6;
    fStack_48 = fVar2 * fVar9;
  }
  fStack_44 = 3.1415927;
code_r0x02057cc8:
  Aska::Quaternion::Create(Aska::Vector const*)(param_1,&fStack_50);
  return;
}

// ==== Aska::Quaternion::CreateFromEuler(float, float, float, EnumRotateType)
// vaddr 0x1f57cec | ghidra 0x2057cec | size 964 | symbol _ZN4Aska10Quaternion15CreateFromEulerEfff14EnumRotateType | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10Quaternion15CreateFromEulerEfff14EnumRotateType
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,float *param_4,
               undefined4 param_5)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  undefined8 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined8 uStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined8 uStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  
  uStack_60 = 0;
  uStack_40 = 0x3f800000;
  uStack_38 = 0;
  uStack_50 = 0x3f80000000000000;
  uStack_48 = 0;
  uStack_58 = 0x3f800000;
  uStack_54 = param_3;
  uStack_44 = param_2;
  uStack_34 = param_1;
  Aska::Quaternion::Create(Aska::Vector const*)(&fStack_70,&uStack_40);
  Aska::Quaternion::Create(Aska::Vector const*)(&fStack_80,&uStack_50);
  Aska::Quaternion::Create(Aska::Vector const*)(&fStack_90,&uStack_60);
  fVar4 = fStack_80;
  fVar5 = fStack_74;
  fVar7 = fStack_8c;
  fVar8 = fStack_78;
  switch(param_5) {
  case 1:
    fVar4 = fStack_90;
    fStack_90 = fStack_80;
    fVar5 = fStack_84;
    fVar7 = fStack_7c;
    fVar8 = fStack_88;
    fStack_88 = fStack_78;
    fStack_7c = fStack_8c;
    fStack_84 = fStack_74;
  default:
    fVar6 = (fStack_84 * fVar4 + fStack_90 * fVar5 + fVar7 * fVar8) - fStack_88 * fStack_7c;
    fVar9 = fVar4 * fStack_88 + fVar5 * fVar7 + (fStack_84 * fStack_7c - fStack_90 * fVar8);
    fVar10 = fVar5 * fStack_88 + ((fStack_84 * fVar8 + fStack_90 * fStack_7c) - fVar4 * fVar7);
    fVar4 = ((fStack_84 * fVar5 - fVar4 * fStack_90) - fVar7 * fStack_7c) - fVar8 * fStack_88;
    *param_4 = fVar6;
    param_4[1] = fVar9;
    param_4[2] = fVar10;
    param_4[3] = fVar4;
    goto code_r0x02057fb4;
  case 2:
    fVar4 = fStack_90;
    fStack_90 = fStack_70;
    fVar5 = fStack_84;
    fVar7 = fStack_6c;
    fVar8 = fStack_88;
    fStack_88 = fStack_68;
    fStack_6c = fStack_8c;
    fStack_84 = fStack_64;
    break;
  case 3:
    fVar4 = fStack_70;
    fVar5 = fStack_64;
    fVar8 = fStack_68;
    break;
  case 4:
    fVar4 = fStack_70;
    fStack_70 = fStack_80;
    fVar5 = fStack_64;
    fVar7 = fStack_7c;
    fVar8 = fStack_68;
    fStack_68 = fStack_78;
    fStack_7c = fStack_6c;
    fStack_64 = fStack_74;
    goto code_r0x02057f20;
  case 5:
    fVar7 = fStack_6c;
code_r0x02057f20:
    fVar6 = (fStack_64 * fVar4 + fStack_70 * fVar5 + fVar7 * fVar8) - fStack_68 * fStack_7c;
    fVar9 = fVar4 * fStack_68 + fVar5 * fVar7 + (fStack_64 * fStack_7c - fStack_70 * fVar8);
    fVar10 = fVar5 * fStack_68 + ((fStack_64 * fVar8 + fStack_70 * fStack_7c) - fVar4 * fVar7);
    fVar4 = ((fStack_64 * fVar5 - fVar4 * fStack_70) - fVar7 * fStack_7c) - fVar8 * fStack_68;
    *param_4 = fVar6;
    param_4[1] = fVar9;
    param_4[2] = fVar10;
    param_4[3] = fVar4;
    fStack_70 = fStack_90;
    fStack_64 = fStack_84;
    fStack_6c = fStack_8c;
    fStack_68 = fStack_88;
    goto code_r0x02057fb4;
  }
  fVar6 = (fStack_84 * fVar4 + fStack_90 * fVar5 + fVar7 * fVar8) - fStack_88 * fStack_6c;
  fVar9 = fVar4 * fStack_88 + fVar5 * fVar7 + (fStack_84 * fStack_6c - fStack_90 * fVar8);
  fVar10 = fVar5 * fStack_88 + ((fStack_84 * fVar8 + fStack_90 * fStack_6c) - fVar4 * fVar7);
  fVar4 = ((fStack_84 * fVar5 - fVar4 * fStack_90) - fVar7 * fStack_6c) - fVar8 * fStack_88;
  *param_4 = fVar6;
  param_4[1] = fVar9;
  param_4[2] = fVar10;
  param_4[3] = fVar4;
  fStack_70 = fStack_80;
  fStack_64 = fStack_74;
  fStack_6c = fStack_7c;
  fStack_68 = fStack_78;
code_r0x02057fb4:
  pfVar3 = param_4 + 2;
  pfVar2 = param_4 + 1;
  pfVar1 = param_4 + 3;
  fVar5 = (fVar4 * fStack_70 + fVar6 * fStack_64 + fVar9 * fStack_68) - fVar10 * fStack_6c;
  fVar7 = fStack_70 * fVar10 + fStack_64 * fVar9 + (fVar4 * fStack_6c - fVar6 * fStack_68);
  fVar8 = fStack_64 * fVar10 + ((fVar4 * fStack_68 + fVar6 * fStack_6c) - fStack_70 * fVar9);
  fVar6 = ((fVar4 * fStack_64 - fStack_70 * fVar6) - fVar9 * fStack_6c) - fStack_68 * fVar10;
  *param_4 = fVar5;
  *pfVar2 = fVar7;
  fVar5 = fVar5 * fVar5 + fVar7 * fVar7 + fVar8 * fVar8 + fVar6 * fVar6;
  fVar4 = SQRT(fVar5);
  *pfVar3 = fVar8;
  *pfVar1 = fVar6;
  if (NAN(fVar4)) {
    fVar4 = (float)sqrtf(fVar5);
  }
  fVar4 = 1.0 / fVar4;
  *param_4 = *param_4 * fVar4;
  *pfVar2 = fVar4 * *pfVar2;
  *pfVar3 = fVar4 * *pfVar3;
  *pfVar1 = fVar4 * *pfVar1;
  return;
}

// ==== Aska::Quaternion::Mul(Aska::Quaternion*, int) const
// vaddr 0x1f580b0 | ghidra 0x20580b0 | size 428 | symbol _ZNK4Aska10Quaternion3MulEPS0_i | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK4Aska10Quaternion3MulEPS0_i(float *param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  
  fVar4 = _UNK_027e519c;
  if (param_3 == 1) {
    fVar6 = *param_1;
  }
  else {
    fVar6 = *param_1;
    fVar1 = param_1[1];
    fVar2 = param_1[2];
    fStack_44 = param_1[3];
    fVar5 = fVar6 * fVar6 + fVar1 * fVar1 + fVar2 * fVar2;
    if (_UNK_027e519c <= fVar5) {
      fVar3 = SQRT(fVar5);
      fStack_50 = fVar6;
      fStack_4c = fVar1;
      fStack_48 = fVar2;
      if (NAN(fVar3)) {
        fVar3 = (float)sqrtf(fVar5);
      }
      if (fVar4 <= fVar3) {
        fVar3 = 1.0 / fVar3;
        fStack_50 = fVar3 * fVar6;
        fStack_4c = fVar3 * fVar1;
        fStack_48 = fVar3 * fVar2;
      }
      fVar4 = param_1[3];
      fStack_44 = 0.0;
      if ((fVar4 <= 1.0) && (-1.0 <= fVar4)) {
        fVar6 = fVar4 * fVar4;
        fStack_44 = fVar4 * (fVar6 * (fVar6 * (fVar6 * (fVar6 * (fVar6 * (fVar6 * (fVar6 * 
                                                  _UNK_0297158c + _UNK_02971590) + _UNK_02971594) +
                                                  _UNK_02971598) + _UNK_0297159c) + _UNK_029715a0) +
                                     _UNK_029715a4) + _UNK_029715a8) + _UNK_027f7284;
        fStack_44 = fStack_44 + fStack_44;
      }
      fStack_44 = fStack_44 * (float)param_3;
      Aska::Quaternion::Create(Aska::Vector const*)(param_2,&fStack_50);
      return;
    }
  }
  *param_2 = fVar6;
  param_2[1] = param_1[1];
  param_2[2] = param_1[2];
  param_2[3] = param_1[3];
  return;
}

// ==== Aska::Quaternion::Slerp(Aska::Quaternion const*, Aska::Quaternion const*, float)
// vaddr 0x1f5825c | ghidra 0x205825c | size 928 | symbol _ZN4Aska10Quaternion5SlerpEPKS0_S2_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska10Quaternion5SlerpEPKS0_S2_f
               (float param_1,float *param_2,undefined8 *param_3,undefined8 *param_4)

{
  uint uVar1;
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
  
  fVar4 = (float)*param_3;
  fVar5 = (float)*param_4;
  fVar6 = fVar4 * fVar5 + (float)((ulong)*param_3 >> 0x20) * (float)((ulong)*param_4 >> 0x20) +
          (float)param_3[1] * (float)param_4[1] +
          (float)((ulong)param_3[1] >> 0x20) * (float)((ulong)param_4[1] >> 0x20);
  fVar7 = -fVar6;
  if (0.0 <= fVar6) {
    fVar7 = fVar6;
  }
  if ((fVar7 <= 1.0) && (-1.0 <= fVar7)) {
    fVar9 = fVar7 * fVar7;
    fVar7 = fVar7 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * _UNK_0297158c +
                                                                          _UNK_02971590) +
                                                                 _UNK_02971594) + _UNK_02971598) +
                                               _UNK_0297159c) + _UNK_029715a0) + _UNK_029715a4) +
                    _UNK_029715a8) + _UNK_027f7284;
    if (_UNK_027e6ae4 < fVar7) {
      fVar9 = (1.0 - param_1) * fVar7;
      uVar1 = (uint)(fVar9 * _UNK_027ebdf4);
      uVar2 = (uint)(fVar7 * param_1 * _UNK_027ebdf4);
      fVar9 = fVar9 - (float)(int)uVar1 * _UNK_027e3fd0;
      fVar3 = fVar7 * param_1 - (float)(int)uVar2 * _UNK_027e3fd0;
      fVar8 = fVar7 - (float)(int)(fVar7 * _UNK_027ebdf4) * _UNK_027e3fd0;
      fVar10 = fVar9 * fVar9;
      fVar11 = fVar3 * fVar3;
      fVar12 = fVar8 * fVar8;
      if ((uVar1 & 1) != 0) {
        fVar9 = -fVar9;
      }
      if ((uVar2 & 1) != 0) {
        fVar3 = -fVar3;
      }
      if (((int)(fVar7 * _UNK_027ebdf4) & 1U) != 0) {
        fVar8 = -fVar8;
      }
      fVar10 = fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (_UNK_0296492c -
                                                                          fVar10 * _UNK_02970cc0) +
                                                                _UNK_02964930) + _UNK_02964934) +
                                            _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) + 1.0;
      fVar3 = fVar3 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (_UNK_0296492c -
                                                                                  fVar11 * 
                                                  _UNK_02970cc0) + _UNK_02964930) + _UNK_02964934) +
                                                  _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) +
                      1.0);
      fVar7 = -(fVar9 * fVar10);
      if (0.0 <= fVar6) {
        fVar7 = fVar9 * fVar10;
      }
      fVar9 = 1.0 / (fVar8 * (fVar12 * (fVar12 * (fVar12 * (fVar12 * (fVar12 * (fVar12 * (
                                                  _UNK_0296492c - fVar12 * _UNK_02970cc0) +
                                                  _UNK_02964930) + _UNK_02964934) + _UNK_02964938) +
                                                 _UNK_0296493c) + _UNK_02964940) + 1.0));
      fVar4 = fVar9 * (fVar7 * fVar4 + fVar3 * fVar5);
      *param_2 = fVar4;
      fVar5 = fVar9 * (fVar7 * *(float *)((long)param_3 + 4) + fVar3 * *(float *)((long)param_4 + 4)
                      );
      param_2[1] = fVar5;
      fVar6 = fVar9 * (fVar7 * *(float *)(param_3 + 1) + fVar3 * *(float *)(param_4 + 1));
      param_2[2] = fVar6;
      fVar9 = fVar9 * (fVar7 * *(float *)((long)param_3 + 0xc) +
                      fVar3 * *(float *)((long)param_4 + 0xc));
      goto code_r0x02058598;
    }
  }
  fVar9 = 1.0 - param_1;
  fVar7 = -param_1;
  if (0.0 <= fVar6) {
    fVar7 = param_1;
  }
  fVar4 = fVar9 * fVar4 + fVar7 * fVar5;
  *param_2 = fVar4;
  fVar5 = fVar9 * *(float *)((long)param_3 + 4) + fVar7 * *(float *)((long)param_4 + 4);
  param_2[1] = fVar5;
  fVar6 = fVar9 * *(float *)(param_3 + 1) + fVar7 * *(float *)(param_4 + 1);
  param_2[2] = fVar6;
  fVar9 = fVar9 * *(float *)((long)param_3 + 0xc) + fVar7 * *(float *)((long)param_4 + 0xc);
code_r0x02058598:
  fVar4 = fVar9 * fVar9 + fVar4 * fVar4 + fVar5 * fVar5 + fVar6 * fVar6;
  fVar7 = SQRT(fVar4);
  param_2[3] = fVar9;
  if (NAN(fVar7)) {
    fVar7 = (float)sqrtf(fVar4);
  }
  fVar7 = 1.0 / fVar7;
  *param_2 = *param_2 * fVar7;
  param_2[1] = fVar7 * param_2[1];
  param_2[2] = fVar7 * param_2[2];
  param_2[3] = fVar7 * param_2[3];
  return;
}

// ==== Aska::Quaternion::Squad(Aska::Quaternion const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Quaternion const*, float)
// vaddr 0x1f585fc | ghidra 0x20585fc | size 112 | symbol _ZN4Aska10Quaternion5SquadEPKS0_S2_S2_S2_f | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10Quaternion5SquadEPKS0_S2_S2_S2_f
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6)

{
  float fVar1;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  
  Aska::Quaternion::SquadSlerp(Aska::Quaternion const*, Aska::Quaternion const*, float)(auStack_40);
  Aska::Quaternion::SquadSlerp(Aska::Quaternion const*, Aska::Quaternion const*, float)(param_1,auStack_50,param_5,param_6);
  fVar1 = 1.0 - (float)param_1;
  Aska::Quaternion::SquadSlerp(Aska::Quaternion const*, Aska::Quaternion const*, float)((fVar1 + fVar1) * (float)param_1,param_2,auStack_40,auStack_50);
  return;
}

// ==== Aska::Quaternion::SquadSlerp(Aska::Quaternion const*, Aska::Quaternion const*, float)
// vaddr 0x1f5866c | ghidra 0x205866c | size 892 | symbol _ZN4Aska10Quaternion10SquadSlerpEPKS0_S2_f | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska10Quaternion10SquadSlerpEPKS0_S2_f
               (float param_1,float *param_2,undefined8 *param_3,undefined8 *param_4)

{
  uint uVar1;
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
  
  fVar4 = (float)*param_3;
  fVar5 = (float)*param_4;
  fVar6 = fVar4 * fVar5 + (float)((ulong)*param_3 >> 0x20) * (float)((ulong)*param_4 >> 0x20) +
          (float)param_3[1] * (float)param_4[1] +
          (float)((ulong)param_3[1] >> 0x20) * (float)((ulong)param_4[1] >> 0x20);
  if ((fVar6 <= 1.0) && (-1.0 <= fVar6)) {
    fVar8 = fVar6 * fVar6;
    fVar6 = fVar6 * (fVar8 * (fVar8 * (fVar8 * (fVar8 * (fVar8 * (fVar8 * (fVar8 * _UNK_0297158c +
                                                                          _UNK_02971590) +
                                                                 _UNK_02971594) + _UNK_02971598) +
                                               _UNK_0297159c) + _UNK_029715a0) + _UNK_029715a4) +
                    _UNK_029715a8) + _UNK_027f7284;
    if (_UNK_027e6ae4 < fVar6) {
      fVar9 = (1.0 - param_1) * fVar6;
      uVar1 = (uint)(fVar9 * _UNK_027ebdf4);
      fVar9 = fVar9 - (float)(int)uVar1 * _UNK_027e3fd0;
      uVar2 = (uint)(fVar6 * param_1 * _UNK_027ebdf4);
      fVar8 = fVar9;
      if ((uVar1 & 1) != 0) {
        fVar8 = -fVar9;
      }
      fVar3 = fVar6 * param_1 - (float)(int)uVar2 * _UNK_027e3fd0;
      fVar7 = fVar6 - (float)(int)(fVar6 * _UNK_027ebdf4) * _UNK_027e3fd0;
      fVar9 = fVar9 * fVar9;
      fVar10 = fVar3 * fVar3;
      fVar11 = fVar7 * fVar7;
      if ((uVar2 & 1) != 0) {
        fVar3 = -fVar3;
      }
      if (((int)(fVar6 * _UNK_027ebdf4) & 1U) != 0) {
        fVar7 = -fVar7;
      }
      fVar8 = fVar8 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (_UNK_0296492c -
                                                                            fVar9 * _UNK_02970cc0) +
                                                                   _UNK_02964930) + _UNK_02964934) +
                                                 _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) +
                      1.0);
      fVar3 = fVar3 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (_UNK_0296492c -
                                                                                  fVar10 * 
                                                  _UNK_02970cc0) + _UNK_02964930) + _UNK_02964934) +
                                                  _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) +
                      1.0);
      fVar9 = 1.0 / (fVar7 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (fVar11 * (
                                                  _UNK_0296492c - fVar11 * _UNK_02970cc0) +
                                                  _UNK_02964930) + _UNK_02964934) + _UNK_02964938) +
                                                 _UNK_0296493c) + _UNK_02964940) + 1.0));
      fVar4 = fVar9 * (fVar8 * fVar4 + fVar3 * fVar5);
      *param_2 = fVar4;
      fVar5 = fVar9 * (fVar8 * *(float *)((long)param_3 + 4) + fVar3 * *(float *)((long)param_4 + 4)
                      );
      param_2[1] = fVar5;
      fVar6 = fVar9 * (fVar8 * *(float *)(param_3 + 1) + fVar3 * *(float *)(param_4 + 1));
      param_2[2] = fVar6;
      fVar9 = fVar9 * (fVar8 * *(float *)((long)param_3 + 0xc) +
                      fVar3 * *(float *)((long)param_4 + 0xc));
      goto code_r0x02058984;
    }
  }
  fVar8 = 1.0 - param_1;
  fVar4 = fVar8 * fVar4 + param_1 * fVar5;
  *param_2 = fVar4;
  fVar5 = fVar8 * *(float *)((long)param_3 + 4) + *(float *)((long)param_4 + 4) * param_1;
  param_2[1] = fVar5;
  fVar6 = fVar8 * *(float *)(param_3 + 1) + *(float *)(param_4 + 1) * param_1;
  param_2[2] = fVar6;
  fVar9 = fVar8 * *(float *)((long)param_3 + 0xc) + *(float *)((long)param_4 + 0xc) * param_1;
code_r0x02058984:
  fVar5 = fVar9 * fVar9 + fVar4 * fVar4 + fVar5 * fVar5 + fVar6 * fVar6;
  fVar4 = SQRT(fVar5);
  param_2[3] = fVar9;
  if (NAN(fVar4)) {
    fVar4 = (float)sqrtf(fVar5);
  }
  fVar4 = 1.0 / fVar4;
  *param_2 = *param_2 * fVar4;
  param_2[1] = fVar4 * param_2[1];
  param_2[2] = fVar4 * param_2[2];
  param_2[3] = fVar4 * param_2[3];
  return;
}

// ==== Aska::Quaternion::CalcEuler(Aska::Vector*, EnumRotateType) const
// vaddr 0x1f589e8 | ghidra 0x20589e8 | size 816 | symbol _ZNK4Aska10Quaternion9CalcEulerEPNS_6VectorE14EnumRotateType | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK4Aska10Quaternion9CalcEulerEPNS_6VectorE14EnumRotateType
               (float *param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined1 auStack_a0 [64];
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  
  fVar4 = *param_1;
  fVar5 = param_1[1];
  fVar6 = param_1[2];
  fVar7 = param_1[3];
  fVar2 = fVar4 * fVar4 + fVar5 * fVar5 + fVar6 * fVar6 + fVar7 * fVar7;
  fVar1 = SQRT(fVar2);
  if (NAN(fVar1)) {
    fVar1 = (float)sqrtf(fVar2);
  }
  fVar1 = 1.0 / fVar1;
  fVar4 = fVar1 * fVar4;
  fVar5 = fVar1 * fVar5;
  fVar6 = fVar1 * fVar6;
  fVar1 = fVar1 * fVar7;
  fStack_60 = fVar4;
  fStack_5c = fVar5;
  fStack_58 = fVar6;
  fStack_54 = fVar1;
  if (ABS(fVar4) < _UNK_027e519c) {
    if (ABS(fVar5) < _UNK_027e519c) {
      param_2[0] = 0.0;
      param_2[1] = 0.0;
      fVar1 = (float)atan2f(fVar6,fVar1);
      fVar1 = fVar1 + fVar1;
      goto code_r0x02058cf4;
    }
    if (ABS(fVar6) < _UNK_027e519c) {
      *param_2 = 0.0;
      fVar1 = (float)atan2f(fVar5,fVar1);
      param_2[1] = fVar1 + fVar1;
      param_2[2] = 0.0;
      return;
    }
  }
  else if ((ABS(fVar5) < _UNK_027e519c) && (ABS(fVar6) < _UNK_027e519c)) {
    fVar1 = (float)atan2f(fVar4,fVar1);
    *param_2 = fVar1 + fVar1;
    param_2[1] = 0.0;
    param_2[2] = 0.0;
    return;
  }
  if (param_3 != 0) {
    Aska::Matrix::Create(Aska::Quaternion const*)(auStack_a0,&fStack_60);
    Aska::Matrix::CalcEuler(Aska::Vector*, EnumRotateType) const(auStack_a0,param_2,param_3);
    return;
  }
  fVar2 = fVar1 * fVar5 - fVar6 * fVar4;
  fVar2 = fVar2 + fVar2;
  if (_UNK_029715ac <= ABS(fVar2)) {
    fVar5 = (float)atan2f(fVar4,fVar1);
    fVar1 = _UNK_027e3fd0;
    fVar5 = fVar5 + fVar5;
    *param_2 = fVar5;
    fVar4 = _UNK_027edb3c;
    if ((fVar1 < fVar5) || (fVar4 = _UNK_027edb34, fVar5 < _UNK_027edb30)) {
      *param_2 = fVar5 + fVar4;
    }
    param_2[1] = *(float *)(&UNK_029715c4 + (ulong)(fVar2 < 0.0) * 4);
    param_2[2] = 0.0;
    return;
  }
  fVar7 = fVar5 * fVar6 + fVar1 * fVar4;
  fVar3 = fVar5 * fVar5 + fVar4 * fVar4;
  fVar7 = (float)atan2f(fVar7 + fVar7,1.0 - (fVar3 + fVar3));
  *param_2 = fVar7;
  fVar7 = fVar2;
  if (fVar2 < 0.0) {
    fVar7 = -fVar2;
  }
  fVar3 = 0.0;
  if (fVar7 <= 1.0) {
    if (_UNK_02970cd8 <= fVar7) {
      fVar7 = fVar7 + _UNK_02970cdc;
      fVar3 = fVar7 * (fVar7 * (fVar7 * (fVar7 * _UNK_02970ce0 + _UNK_02970ce4) + _UNK_02970ce8) +
                      _UNK_02970cec) + _UNK_02970cf0;
      fVar7 = fVar7 * _UNK_02970cf4;
    }
    else {
      fVar3 = fVar7 * (fVar7 * (fVar7 * (fVar7 * _UNK_02970cf8 + _UNK_02970cfc) + _UNK_02970d00) +
                      _UNK_02970d04);
      fVar7 = fVar7 * _UNK_02970d08;
    }
    fVar3 = (float)((uint)fVar2 & 0x80000000 | (uint)(fVar3 / (1.0 - fVar7)));
  }
  param_2[1] = fVar3;
  fVar1 = fVar1 * fVar6 + fVar4 * fVar5;
  fVar2 = fVar6 * fVar6 + fVar5 * fVar5;
  fVar1 = (float)atan2f(fVar1 + fVar1,1.0 - (fVar2 + fVar2));
code_r0x02058cf4:
  param_2[2] = fVar1;
  return;
}

// ==== Aska::Quaternion::IsRotation() const
// vaddr 0x1f58d18 | ghidra 0x2058d18 | size 280 | symbol _ZNK4Aska10Quaternion10IsRotationEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZNK4Aska10Quaternion10IsRotationEv(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar2 = *param_1 * *param_1 + param_1[1] * param_1[1] + param_1[2] * param_1[2] +
          param_1[3] * param_1[3];
  fVar1 = SQRT(fVar2);
  if (NAN(fVar1)) {
    fVar1 = (float)sqrtf(fVar2);
  }
  fVar2 = _UNK_027daba4;
  fVar3 = 1.0 / fVar1;
  if (fVar1 <= _UNK_027e519c) {
    fVar3 = 1.0;
  }
  fVar1 = 1.0 - fVar3 * param_1[3] * fVar3 * param_1[3];
  fVar5 = *param_1 * fVar3;
  fVar4 = param_1[1] * fVar3;
  fVar3 = fVar3 * param_1[2];
  if (ABS(fVar1) <= _UNK_027daba4) {
    fVar1 = fVar5 * fVar5 + fVar4 * fVar4 + fVar3 * fVar3;
  }
  else {
    fVar1 = SQRT(fVar1);
    if (NAN(fVar1)) {
      fVar1 = (float)sqrtf();
    }
    fVar1 = 1.0 / fVar1;
    fVar1 = 1.0 - (fVar3 * fVar1 * fVar3 * fVar1 +
                  fVar5 * fVar1 * fVar5 * fVar1 + fVar4 * fVar1 * fVar4 * fVar1);
  }
  return ABS(fVar1) < fVar2;
}

// ==== Aska::Quaternion::Ln(Aska::Quaternion*) const
// vaddr 0x1f58e30 | ghidra 0x2058e30 | size 448 | symbol _ZNK4Aska10Quaternion2LnEPS0_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK4Aska10Quaternion2LnEPS0_(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  param_2[3] = 0.0;
  fVar2 = param_1[3];
  if (ABS(fVar2) < 1.0) {
    fVar1 = 0.0;
    if ((fVar2 <= 1.0) && (-1.0 <= fVar2)) {
      fVar1 = fVar2 * fVar2;
      fVar1 = fVar2 * (fVar1 * (fVar1 * (fVar1 * (fVar1 * (fVar1 * (fVar1 * (fVar1 * _UNK_0297158c +
                                                                            _UNK_02971590) +
                                                                   _UNK_02971594) + _UNK_02971598) +
                                                 _UNK_0297159c) + _UNK_029715a0) + _UNK_029715a4) +
                      _UNK_029715a8) + _UNK_027f7284;
    }
    fVar3 = fVar1 + (float)(int)(fVar1 * _UNK_027ebdf4) * _UNK_027edb30;
    fVar2 = fVar3;
    if (((int)(fVar1 * _UNK_027ebdf4) & 1U) != 0) {
      fVar2 = -fVar3;
    }
    fVar3 = fVar3 * fVar3;
    fVar2 = fVar2 * (fVar3 * (fVar3 * (fVar3 * (fVar3 * (fVar3 * (fVar3 * (fVar3 * _UNK_02964928 +
                                                                          _UNK_0296492c) +
                                                                 _UNK_02964930) + _UNK_02964934) +
                                               _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) +
                    1.0);
    if (_UNK_027e519c <= ABS(fVar2)) {
      fVar1 = fVar1 / fVar2;
      *param_2 = fVar1 * *param_1;
      param_2[1] = fVar1 * param_1[1];
      param_2[2] = fVar1 * param_1[2];
      return;
    }
  }
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  param_2[2] = param_1[2];
  return;
}

// ==== Aska::Quaternion::Exp(Aska::Quaternion*) const
// vaddr 0x1f58ff0 | ghidra 0x2058ff0 | size 460 | symbol _ZNK4Aska10Quaternion3ExpEPS0_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK4Aska10Quaternion3ExpEPS0_(float *param_1,float *param_2)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar3 = *param_1 * *param_1 + param_1[1] * param_1[1] + param_1[2] * param_1[2];
  fVar2 = SQRT(fVar3);
  if (NAN(fVar2)) {
    fVar2 = (float)sqrtf(fVar3);
  }
  fVar4 = fVar2 + (float)(int)(fVar2 * _UNK_027ebdf4) * _UNK_027edb30;
  bVar1 = ((int)(fVar2 * _UNK_027ebdf4) & 1U) != 0;
  fVar3 = fVar4;
  if (bVar1) {
    fVar3 = -fVar4;
  }
  fVar4 = fVar4 * fVar4;
  fVar5 = fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * _UNK_02964910 +
                                                               _UNK_02964914) + _UNK_02964918) +
                                             _UNK_0296491c) + _UNK_02964920) + _UNK_02964924) + -0.5
                  );
  fVar3 = fVar3 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * _UNK_02964928 +
                                                                        _UNK_0296492c) +
                                                               _UNK_02964930) + _UNK_02964934) +
                                             _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) + 1.0)
  ;
  fVar4 = -1.0 - fVar5;
  if (!bVar1) {
    fVar4 = fVar5 + 1.0;
  }
  bVar1 = _UNK_027e519c <= ABS(fVar3);
  param_2[3] = fVar4;
  if (bVar1) {
    fVar3 = fVar3 / fVar2;
    *param_2 = fVar3 * *param_1;
    param_2[1] = fVar3 * param_1[1];
    param_2[2] = fVar3 * param_1[2];
  }
  else {
    *param_2 = *param_1;
    param_2[1] = param_1[1];
    param_2[2] = param_1[2];
  }
  return;
}

// ==== Aska::Quaternion::Intermediate(Aska::Quaternion*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Quaternion const*)
// vaddr 0x1f591bc | ghidra 0x20591bc | size 1604 | symbol _ZN4Aska10Quaternion12IntermediateEPS0_PKS0_S3_S3_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska10Quaternion12IntermediateEPS0_PKS0_S3_S3_
               (float *param_1,float *param_2,float *param_3,float *param_4)

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
  
  fVar2 = *param_3;
  fVar4 = param_3[1];
  fVar6 = param_3[2];
  fVar7 = param_3[3];
  fVar8 = param_2[2];
  fVar9 = param_2[3];
  fVar10 = *param_2;
  fVar11 = param_2[1];
  fVar14 = *param_4;
  fVar15 = param_4[1];
  fVar12 = param_4[2];
  fVar13 = param_4[3];
  fVar16 = fVar7 * fVar9 + fVar10 * fVar2 + fVar11 * fVar4 + fVar8 * fVar6;
  fVar3 = ((fVar7 * fVar10 - fVar9 * fVar2) - fVar8 * fVar4) + fVar11 * fVar6;
  fVar5 = ((fVar7 * fVar11 + fVar8 * fVar2) - fVar9 * fVar4) - fVar10 * fVar6;
  fVar9 = ((fVar7 * fVar8 - fVar11 * fVar2) + fVar10 * fVar4) - fVar9 * fVar6;
  fVar8 = fVar7 * fVar13 + fVar14 * fVar2 + fVar15 * fVar4 + fVar12 * fVar6;
  if (ABS(fVar16) < 1.0) {
    fVar10 = 0.0;
    if ((fVar16 <= 1.0) && (-1.0 <= fVar16)) {
      fVar10 = fVar16 * fVar16;
      fVar10 = fVar16 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * (fVar10 * 
                                                  _UNK_0297158c + _UNK_02971590) + _UNK_02971594) +
                                                  _UNK_02971598) + _UNK_0297159c) + _UNK_029715a0) +
                                  _UNK_029715a4) + _UNK_029715a8) + _UNK_027f7284;
    }
    fVar16 = fVar10 + (float)(int)(fVar10 * _UNK_027ebdf4) * _UNK_027edb30;
    fVar11 = fVar16;
    if (((int)(fVar10 * _UNK_027ebdf4) & 1U) != 0) {
      fVar11 = -fVar16;
    }
    fVar16 = fVar16 * fVar16;
    fVar11 = fVar11 * (fVar16 * (fVar16 * (fVar16 * (fVar16 * (fVar16 * (fVar16 * (fVar16 * 
                                                  _UNK_02964928 + _UNK_0296492c) + _UNK_02964930) +
                                                  _UNK_02964934) + _UNK_02964938) + _UNK_0296493c) +
                                _UNK_02964940) + 1.0);
    if (_UNK_027e519c <= ABS(fVar11)) {
      fVar10 = fVar10 / fVar11;
      fVar3 = fVar3 * fVar10;
      fVar5 = fVar5 * fVar10;
      fVar9 = fVar9 * fVar10;
    }
  }
  fVar10 = ((fVar7 * fVar12 - fVar15 * fVar2) + fVar14 * fVar4) - fVar13 * fVar6;
  fVar11 = ((fVar7 * fVar14 - fVar13 * fVar2) - fVar12 * fVar4) + fVar15 * fVar6;
  fVar2 = ((fVar7 * fVar15 + fVar12 * fVar2) - fVar13 * fVar4) - fVar14 * fVar6;
  if (ABS(fVar8) < 1.0) {
    fVar4 = 0.0;
    if ((fVar8 <= 1.0) && (-1.0 <= fVar8)) {
      fVar4 = fVar8 * fVar8;
      fVar4 = fVar8 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * _UNK_0297158c +
                                                                            _UNK_02971590) +
                                                                   _UNK_02971594) + _UNK_02971598) +
                                                 _UNK_0297159c) + _UNK_029715a0) + _UNK_029715a4) +
                      _UNK_029715a8) + _UNK_027f7284;
    }
    fVar7 = fVar4 + (float)(int)(fVar4 * _UNK_027ebdf4) * _UNK_027edb30;
    fVar6 = fVar7;
    if (((int)(fVar4 * _UNK_027ebdf4) & 1U) != 0) {
      fVar6 = -fVar7;
    }
    fVar7 = fVar7 * fVar7;
    fVar6 = fVar6 * (fVar7 * (fVar7 * (fVar7 * (fVar7 * (fVar7 * (fVar7 * (fVar7 * _UNK_02964928 +
                                                                          _UNK_0296492c) +
                                                                 _UNK_02964930) + _UNK_02964934) +
                                               _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) +
                    1.0);
    if (_UNK_027e519c <= ABS(fVar6)) {
      fVar4 = fVar4 / fVar6;
      fVar11 = fVar11 * fVar4;
      fVar2 = fVar2 * fVar4;
      fVar10 = fVar10 * fVar4;
    }
  }
  fVar6 = (fVar3 + fVar11) * -0.25;
  fVar5 = (fVar5 + fVar2) * -0.25;
  fVar4 = (fVar9 + fVar10) * -0.25;
  fVar3 = fVar4 * fVar4 + fVar5 * fVar5 + fVar6 * fVar6;
  fVar2 = SQRT(fVar3);
  if (NAN(fVar2)) {
    fVar2 = (float)sqrtf(fVar3);
  }
  fVar7 = fVar2 + (float)(int)(fVar2 * _UNK_027ebdf4) * _UNK_027edb30;
  bVar1 = ((int)(fVar2 * _UNK_027ebdf4) & 1U) != 0;
  fVar3 = fVar7;
  if (bVar1) {
    fVar3 = -fVar7;
  }
  fVar7 = fVar7 * fVar7;
  fVar8 = fVar7 * (fVar7 * (fVar7 * (fVar7 * (fVar7 * (fVar7 * (fVar7 * _UNK_02964910 +
                                                               _UNK_02964914) + _UNK_02964918) +
                                             _UNK_0296491c) + _UNK_02964920) + _UNK_02964924) + -0.5
                  );
  fVar3 = fVar3 * (fVar7 * (fVar7 * (fVar7 * (fVar7 * (fVar7 * (fVar7 * (fVar7 * _UNK_02964928 +
                                                                        _UNK_0296492c) +
                                                               _UNK_02964930) + _UNK_02964934) +
                                             _UNK_02964938) + _UNK_0296493c) + _UNK_02964940) + 1.0)
  ;
  fVar7 = -1.0 - fVar8;
  if (!bVar1) {
    fVar7 = fVar8 + 1.0;
  }
  if (_UNK_027e519c <= ABS(fVar3)) {
    fVar3 = fVar3 / fVar2;
    fVar6 = fVar6 * fVar3;
    fVar5 = fVar5 * fVar3;
    fVar4 = fVar4 * fVar3;
  }
  fVar9 = param_3[2];
  fVar2 = param_3[3];
  fVar3 = *param_3;
  fVar8 = param_3[1];
  *param_1 = (fVar6 * fVar2 + fVar7 * fVar3 + fVar4 * fVar8) - fVar5 * fVar9;
  param_1[1] = fVar6 * fVar9 + fVar7 * fVar8 + (fVar5 * fVar2 - fVar4 * fVar3);
  param_1[2] = fVar7 * fVar9 + ((fVar4 * fVar2 + fVar5 * fVar3) - fVar6 * fVar8);
  param_1[3] = ((fVar7 * fVar2 - fVar6 * fVar3) - fVar5 * fVar8) - fVar4 * fVar9;
  return;
}
