// port/decomp/dynamics/adm_local.c: Ghidra decompiles for the dynamics subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileAt.java, tools/resolve_decomp.py
// run      2026-10-08 15:03 UTC: tools/decomp_at.sh '--into' 'dynamics/adm_local' '0x24297c4' '0x2429994' '0x2429d78' '0x242a08c' '0x242a9f4' '0x242ac84'

// ==== void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)
// vaddr 0x23297c4 | ghidra 0x24297c4 | size 464 | symbol _Z39Functor_ExternalForceEmitterCalculationIN4Aska26ArticulatedDynamicsManagerENS0_20DynamicsForceEmitterEEvPT_PNS0_8ADMJointEPPT0_jfj | lib libSOA-3.7.0.so | 2026-10-08
void _Z39Functor_ExternalForceEmitterCalculationIN4Aska26ArticulatedDynamicsManagerENS0_20DynamicsForceEmitterEEvPT_PNS0_8ADMJointEPPT0_jfj
               (undefined8 param_1,long param_2,long param_3,long param_4,uint param_5,uint param_6)

{
  float *pfVar1;
  uint uVar2;
  short sVar3;
  long *plVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  long *plVar8;
  uint uVar9;
  ulong uVar10;
  float fVar11;
  float fStack_190;
  float fStack_18c;
  float fStack_188;
  long alStack_180 [32];
  
  sVar3 = *(short *)(param_2 + 0x60);
  uVar2 = *(uint *)(param_2 + 0x9c);
  uVar9 = 0;
  do {
    uVar5 = 0;
    do {
      lVar6 = *(long *)(param_4 + (ulong)uVar9 * 8);
      if (((lVar6 != 0) && (*(char *)(lVar6 + 0x19c) != '\0')) &&
         ((*(uint *)(lVar6 + 0x198) & uVar2) == 0)) {
        alStack_180[uVar5] = lVar6;
        uVar5 = uVar5 + 1;
      }
      uVar9 = uVar9 + 1;
    } while ((uVar9 < param_5) && (uVar5 < 0x20));
    if (uVar5 != 0) {
      uVar10 = 0;
      do {
        if ((-1 < *(char *)(param_3 + uVar10 * 0x1c0 + 0x19d)) &&
           ((*(byte *)(param_3 + uVar10 * 0x1c0 + 0x19c) & 1) == 0)) {
          lVar6 = param_3 + uVar10 * 0x1c0;
          pfVar1 = (float *)(lVar6 + 0x10);
          fVar11 = (float)param_1 / *(float *)(lVar6 + 0x180);
          if (*(float *)(lVar6 + 0x180) <= 0.0) {
            fVar11 = (float)param_1;
          }
          plVar8 = alStack_180;
          uVar7 = (ulong)uVar5;
          do {
            plVar4 = (long *)*plVar8;
            if (plVar4 != (long *)0x0) {
              param_6 = param_6 * 0x19660d + 0x3c6ef35f;
              (**(code **)(*plVar4 + 0x168))
                        (param_1,(float)(param_6 & 0x7fffff | 0x3f800000) + -1.0,plVar4,pfVar1,
                         &fStack_190);
              *pfVar1 = *pfVar1 + fVar11 * fStack_190;
              *(float *)(lVar6 + 0x14) = *(float *)(lVar6 + 0x14) + fVar11 * fStack_18c;
              *(float *)(lVar6 + 0x18) = *(float *)(lVar6 + 0x18) + fVar11 * fStack_188;
            }
            uVar7 = uVar7 - 1;
            plVar8 = plVar8 + 1;
          } while (uVar7 != 0);
        }
        uVar10 = uVar10 + 1;
      } while (uVar10 < ((long)sVar3 & 0xffffffffU));
    }
  } while (uVar9 < param_5);
  return;
}

// ==== FUN_02429994
// vaddr 0x2329994 | ghidra 0x2429994 | size 0 | symbol FUN_02429994 | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_02429994(float param_1,float param_2,float param_3,char param_4,long param_5,long param_6)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar12;
  ulong uVar9;
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  float fVar13;
  float fVar14;
  undefined8 uVar15;
  undefined1 auVar16 [16];
  float fVar17;
  undefined8 uVar18;
  undefined1 auVar19 [16];
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  undefined1 auVar25 [16];
  undefined1 auVar26 [16];
  float fVar27;
  undefined1 auVar28 [16];
  undefined1 auVar29 [16];
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  undefined8 uVar35;
  float fVar36;
  undefined8 uVar37;
  float fVar38;
  float fVar39;
  uint uVar40;
  
  fVar34 = *(float *)(param_5 + 0x10);
  fVar38 = *(float *)(param_5 + 0x14);
  uVar18 = *(undefined8 *)(param_5 + 0x10);
  fVar30 = *(float *)(param_5 + 0x18);
  fVar27 = *(float *)(param_5 + 0x1c);
  uVar35 = *(undefined8 *)(param_5 + 0x18);
  fVar36 = *(float *)(param_6 + 0x10);
  fVar24 = *(float *)(param_6 + 0x14);
  uVar15 = *(undefined8 *)(param_6 + 0x10);
  fVar20 = *(float *)(param_6 + 0x18);
  fVar17 = *(float *)(param_6 + 0x1c);
  uVar37 = *(undefined8 *)(param_6 + 0x18);
  uVar40 = *(uint *)(param_5 + 0x180);
  uVar9 = (ulong)uVar40;
  fVar39 = *(float *)(param_6 + 0x180);
  bVar1 = *(byte *)(param_5 + 0x19c);
  bVar2 = *(byte *)(param_6 + 0x19c);
  if (param_4 != '\x01') {
    if (param_4 == '\0') {
      fVar6 = fVar36 - fVar34;
      fVar7 = fVar24 - fVar38;
      fVar8 = fVar20 - fVar30;
      fVar17 = fVar17 - fVar27;
      auVar10._4_4_ = fVar7;
      auVar10._0_4_ = fVar6;
      auVar10._8_4_ = fVar8;
      auVar10._12_4_ = fVar17;
      auVar26._4_4_ = fVar7;
      auVar26._0_4_ = fVar6;
      auVar26._8_4_ = fVar8;
      auVar26._12_4_ = fVar17;
      auVar10 = NEON_ext(auVar10,auVar26,8,1);
      fVar27 = fVar6 * fVar6 + auVar10._0_4_ * auVar10._0_4_;
      fVar12 = fVar7 * fVar7 + 0.0;
      fVar17 = fVar27 + fVar12;
      uVar18 = CONCAT44(fVar27 + fVar12,fVar17);
      uVar15 = NEON_frsqrte(uVar18,4);
      fVar12 = (float)uVar15;
      fVar27 = (float)((ulong)uVar15 >> 0x20);
      uVar18 = NEON_frsqrts(CONCAT44(fVar27 * fVar27,fVar12 * fVar12),uVar18,4);
      fVar27 = *(float *)(param_5 + 0x184);
      fVar12 = fVar17 * fVar12 * (float)uVar18;
      if ((bVar1 & 1) == 0) {
        if ((bVar2 & 1) == 0) {
          auVar16._4_4_ = uVar40;
          auVar16._0_4_ = uVar40;
          auVar16._8_4_ = uVar40;
          auVar16._12_4_ = uVar40;
          auVar19._4_4_ = fVar39;
          auVar19._0_4_ = fVar39;
          auVar19._8_4_ = fVar39;
          auVar19._12_4_ = fVar39;
        }
        else {
          auVar16 = ZEXT816(0);
          auVar19 = NEON_fmov(0x3f800000,4);
        }
      }
      else {
        auVar16 = NEON_fmov(0x3f800000,4);
        auVar19 = ZEXT816(0);
      }
      auVar29._4_4_ = fVar17;
      auVar29._0_4_ = fVar17;
      auVar29._8_4_ = fVar17;
      auVar29._12_4_ = fVar17;
      auVar10 = NEON_frsqrte(auVar29,4);
      auVar28._0_4_ = auVar19._0_4_ + auVar16._0_4_;
      auVar28._4_4_ = auVar19._4_4_ + auVar16._4_4_;
      auVar28._8_4_ = auVar19._8_4_ + auVar16._8_4_;
      auVar28._12_4_ = auVar19._12_4_ + auVar16._12_4_;
      fVar21 = (fVar12 - param_1) * fVar27 * 0.5;
      fVar22 = (fVar12 - param_1) * fVar27 * 0.5;
      fVar23 = (fVar12 - param_1) * fVar27 * 0.5;
      fVar31 = auVar10._0_4_;
      auVar25._0_4_ = fVar31 * fVar31;
      fVar32 = auVar10._4_4_;
      auVar25._4_4_ = fVar32 * fVar32;
      fVar33 = auVar10._8_4_;
      auVar25._8_4_ = fVar33 * fVar33;
      auVar25._12_4_ = auVar10._12_4_ * auVar10._12_4_;
      auVar10 = NEON_frsqrts(auVar25,auVar29,4);
      auVar26 = NEON_frecpe(auVar28,4);
      auVar29 = NEON_frecps(auVar26,auVar28,4);
      fVar39 = (fVar12 - param_1) * auVar26._0_4_ * auVar29._0_4_ * fVar27;
      fVar17 = (fVar12 - param_1) * auVar26._4_4_ * auVar29._4_4_ * fVar27;
      fVar27 = (fVar12 - param_1) * auVar26._8_4_ * auVar29._8_4_ * fVar27;
      fVar12 = auVar19._0_4_ * fVar39;
      fVar13 = auVar19._4_4_ * fVar17;
      fVar14 = auVar19._8_4_ * fVar27;
      fVar39 = auVar16._0_4_ * fVar39;
      fVar17 = auVar16._4_4_ * fVar17;
      fVar27 = auVar16._8_4_ * fVar27;
      bVar3 = false;
      if ((fVar39 == 0.0) && (bVar3 = false, !NAN(fVar12))) {
        bVar3 = fVar12 == 0.0;
      }
      fVar6 = fVar6 * fVar31 * auVar10._0_4_;
      fVar7 = fVar7 * fVar32 * auVar10._4_4_;
      fVar8 = fVar8 * fVar33 * auVar10._8_4_;
      bVar4 = false;
      if ((fVar17 == 0.0) && (bVar4 = false, !NAN(fVar13))) {
        bVar4 = fVar13 == 0.0;
      }
      bVar5 = false;
      if ((fVar27 == 0.0) && (bVar5 = false, !NAN(fVar14))) {
        bVar5 = fVar14 == 0.0;
      }
      uVar15 = CONCAT44(fVar24 - fVar7 * (float)((uint)fVar17 ^
                                                ((uint)fVar17 ^ (uint)fVar22) & -(uint)bVar4),
                        fVar36 - fVar6 * (float)((uint)fVar39 ^
                                                ((uint)fVar39 ^ (uint)fVar21) & -(uint)bVar3));
      uVar18 = CONCAT44(fVar38 + fVar7 * (float)((uint)fVar13 ^
                                                ((uint)fVar13 ^ (uint)fVar22) & -(uint)bVar4),
                        fVar34 + fVar6 * (float)((uint)fVar12 ^
                                                ((uint)fVar12 ^ (uint)fVar21) & -(uint)bVar3));
      uVar35 = CONCAT44(0x3f800000,
                        fVar30 + fVar8 * (float)((uint)fVar14 ^
                                                ((uint)fVar14 ^ (uint)fVar23) & -(uint)bVar5));
      uVar37 = CONCAT44(0x3f800000,
                        fVar20 - fVar8 * (float)((uint)fVar27 ^
                                                ((uint)fVar27 ^ (uint)fVar23) & -(uint)bVar5));
    }
    goto LAB_02429d4c;
  }
  fVar7 = fVar36 - fVar34;
  fVar8 = fVar24 - fVar38;
  fVar13 = fVar20 - fVar30;
  fVar12 = fVar7 * fVar7 + fVar8 * fVar8 + fVar13 * fVar13;
  fVar6 = SQRT(fVar12);
  if (NAN(fVar6)) {
    fVar6 = (float)sqrtf(fVar12);
    if ((bVar1 & 1) != 0) goto LAB_02429afc;
LAB_02429a98:
    if ((bVar2 & 1) != 0) {
      fVar39 = 1.0;
      uVar9 = 0;
    }
    auVar11._8_8_ = 0;
    auVar11._0_8_ = uVar9;
  }
  else {
    if ((bVar1 & 1) == 0) goto LAB_02429a98;
LAB_02429afc:
    auVar11 = ZEXT816(0x3f800000);
    fVar39 = 0.0;
  }
  fVar14 = SQRT(fVar12);
  if (NAN(fVar14)) {
    uVar18 = auVar11._8_8_;
    fVar14 = (float)sqrtf(fVar12);
    auVar11._8_8_ = uVar18;
  }
  if (_UNK_027e519c <= fVar14) {
    fVar14 = 1.0 / fVar14;
    fVar7 = fVar7 * fVar14;
    fVar8 = fVar8 * fVar14;
    fVar13 = fVar13 * fVar14;
  }
  fVar6 = param_2 * param_3 * (fVar6 - param_1);
  fVar12 = auVar11._0_4_;
  if ((fVar39 == 0.0) && (fVar12 == 0.0)) {
    fVar6 = fVar6 * 0.5;
    fVar7 = fVar6 * fVar7;
    fVar8 = fVar6 * fVar8;
    fVar6 = fVar6 * fVar13;
    uVar18 = CONCAT44(fVar38 + fVar8,fVar34 + fVar7);
    fVar14 = fVar6;
  }
  else {
    fVar21 = fVar6 * (fVar39 / (fVar39 + fVar12));
    fVar14 = fVar21 * fVar13;
    uVar18 = CONCAT44(fVar38 + fVar21 * fVar8,fVar34 + fVar21 * fVar7);
    fVar6 = fVar6 * (fVar12 / (fVar39 + fVar12));
    fVar7 = fVar6 * fVar7;
    fVar8 = fVar6 * fVar8;
    fVar6 = fVar6 * fVar13;
  }
  uVar35 = CONCAT44(fVar27,fVar30 + fVar14);
  uVar15 = CONCAT44(fVar24 - fVar8,fVar36 - fVar7);
  uVar37 = CONCAT44(fVar17,fVar20 - fVar6);
LAB_02429d4c:
  *(undefined8 *)(param_5 + 0x18) = uVar35;
  *(undefined8 *)(param_5 + 0x10) = uVar18;
  *(undefined8 *)(param_6 + 0x18) = uVar37;
  *(undefined8 *)(param_6 + 0x10) = uVar15;
  return;
}

// ==== FUN_02429d78
// vaddr 0x2329d78 | ghidra 0x2429d78 | size 0 | symbol FUN_02429d78 | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Removing unreachable block (ram,0x02429f38) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_02429d78(float param_1,float param_2,long param_3,long param_4,undefined8 param_5,
                 undefined8 param_6,uint param_7)

{
  int iVar1;
  float fVar2;
  float fVar3;
  ulong uVar4;
  ulong uVar5;
  float fVar6;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  
  fVar6 = _UNK_029e2c84;
  fVar2 = (_UNK_029e2c84 / param_2) * 0.5;
  if (fVar2 <= 1.0) {
    fVar2 = 1.0;
  }
  void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x8c8(fVar2,&uStack_70);
  if ((*(byte *)(param_3 + 0x19d) >> 2 & 1) != 0) {
    fVar2 = *(float *)(param_3 + 0x170);
    if (1.0 < *(float *)(param_3 + 0x170)) {
      fVar2 = 1.0;
    }
    if (param_7 != 1) {
      if (fVar6 <= param_2) {
        if (1 < (int)param_7) {
          fVar2 = 1.0 - fVar2;
          iVar1 = param_7 + 1;
          do {
            iVar1 = iVar1 + -1;
            fVar2 = fVar2 * fVar2;
          } while (2 < iVar1);
LAB_02429ee0:
          fVar2 = 1.0 - fVar2;
        }
      }
      else if ((param_7 & 1) == 0) {
        uVar4 = (ulong)(uint)(1.0 - fVar2);
        if (0 < (int)param_7) {
          iVar1 = 0;
          uVar5 = uVar4;
          do {
            uVar4 = (ulong)(uint)SQRT((float)uVar5);
            if (NAN(SQRT((float)uVar5))) {
              uVar4 = sqrtf(uVar5);
            }
            iVar1 = iVar1 + 2;
            uVar5 = uVar4;
          } while (iVar1 < (int)param_7);
        }
        fVar2 = 1.0 - (float)uVar4;
      }
      else {
        fVar2 = 1.0 - fVar2;
        if (param_7 != 3) {
          fVar2 = (float)powf(fVar2,1.0 / (float)(int)param_7);
          goto LAB_02429ee0;
        }
        fVar3 = SQRT(fVar2);
        if (NAN(fVar3)) {
          fVar3 = (float)sqrtf(fVar2);
        }
        fVar3 = 1.0 - (fVar2 * fVar2 * _UNK_029e2c8c + fVar3 * _UNK_029e2c88 + fVar2 * _UNK_029e2c90
                      + _UNK_029e2c94);
        fVar2 = 0.0;
        if ((0.0 <= fVar3) && (fVar2 = fVar3, 1.0 < fVar3)) {
          fVar2 = 1.0;
        }
      }
    }
    Aska::Quaternion::Slerp(Aska::Quaternion const*, Aska::Quaternion const*, float)(fVar2,&uStack_60,&uStack_70,param_3 + 0x70);
    uStack_68 = uStack_58;
    uStack_70 = uStack_60;
  }
  fVar2 = _UNK_027e519c;
  if (param_1 <= _UNK_027e519c) goto LAB_02429f54;
  param_1 = *(float *)(param_3 + 0x174) * param_1;
  if (param_7 == 1) {
LAB_02429f28:
    fVar6 = param_1;
    if (param_1 <= fVar2) goto LAB_02429f54;
  }
  else {
    if (fVar6 <= param_2) {
      if (1 < (int)param_7) {
        param_1 = 1.0 - param_1;
        iVar1 = param_7 + 1;
        do {
          iVar1 = iVar1 + -1;
          param_1 = param_1 * param_1;
        } while (2 < iVar1);
        param_1 = 1.0 - param_1;
      }
      goto LAB_02429f28;
    }
    if ((param_7 & 1) == 0) {
      uVar4 = (ulong)(uint)(1.0 - param_1);
      if (0 < (int)param_7) {
        iVar1 = 0;
        uVar5 = uVar4;
        do {
          uVar4 = (ulong)(uint)SQRT((float)uVar5);
          if (NAN(SQRT((float)uVar5))) {
            uVar4 = sqrtf(uVar5);
          }
          iVar1 = iVar1 + 2;
          uVar5 = uVar4;
        } while (iVar1 < (int)param_7);
      }
      param_1 = 1.0 - (float)uVar4;
      goto LAB_02429f28;
    }
    fVar6 = 1.0;
    param_1 = 1.0 - param_1;
    if (param_7 != 3) {
      param_1 = (float)powf(param_1,1.0 / (float)(int)param_7);
      param_1 = 1.0 - param_1;
      goto LAB_02429f28;
    }
    fVar3 = SQRT(param_1);
    if (NAN(fVar3)) {
      fVar3 = (float)sqrtf(param_1);
    }
    param_1 = 1.0 - (param_1 * param_1 * _UNK_029e2c8c + fVar3 * _UNK_029e2c88 +
                     param_1 * _UNK_029e2c90 + _UNK_029e2c94);
    if (param_1 < 0.0) goto LAB_02429f54;
    if (param_1 <= 1.0) goto LAB_02429f28;
  }
  Aska::Quaternion::Slerp(Aska::Quaternion const*, Aska::Quaternion const*, float)(fVar6,&uStack_60,&uStack_70,param_3 + 0x80);
  uStack_68 = uStack_58;
  uStack_70 = uStack_60;
LAB_02429f54:
  *(undefined8 *)(param_4 + 0x58) = uStack_68;
  *(undefined8 *)(param_4 + 0x50) = uStack_70;
  return;
}

// ==== FUN_0242a08c
// vaddr 0x232a08c | ghidra 0x242a08c | size 0 | symbol FUN_0242a08c | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0242a08c(float param_1,undefined1 (*param_2) [16],float *param_3,long param_4,long param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar9;
  float fVar10;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  float fVar11;
  float fVar13;
  float fVar14;
  undefined1 auVar12 [16];
  float fVar15;
  byte bVar16;
  float fVar17;
  int iVar18;
  byte bVar24;
  byte bVar25;
  float fVar27;
  float fVar28;
  float fVar29;
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  byte bVar26;
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  float fVar30;
  float fVar31;
  float fVar37;
  float fVar38;
  undefined1 auVar32 [16];
  undefined1 auVar33 [16];
  float fVar39;
  undefined1 auVar34 [16];
  undefined1 auVar35 [16];
  undefined1 auVar36 [16];
  undefined1 auVar40 [16];
  undefined1 auVar41 [16];
  undefined1 auVar42 [16];
  undefined1 auVar43 [16];
  undefined1 auVar44 [16];
  undefined1 auVar45 [16];
  undefined1 auVar46 [16];
  undefined1 auVar47 [16];
  undefined1 auVar51 [16];
  undefined1 auVar52 [16];
  undefined1 auVar53 [16];
  undefined1 auVar54 [16];
  float fVar55;
  float fVar61;
  float fVar62;
  undefined1 auVar56 [16];
  undefined1 auVar57 [16];
  undefined1 auVar58 [16];
  undefined1 auVar63 [16];
  undefined1 auVar64 [16];
  undefined1 auVar65 [16];
  undefined1 auVar66 [16];
  undefined1 auVar67 [16];
  undefined1 auVar68 [16];
  undefined1 auVar69 [16];
  undefined1 auVar70 [16];
  undefined1 auVar74 [16];
  undefined1 auVar75 [16];
  undefined1 auVar76 [16];
  float fVar77;
  undefined8 uVar78;
  float fVar79;
  float fVar80;
  float fVar81;
  float fVar82;
  undefined8 uVar83;
  float fVar85;
  float fVar86;
  undefined1 auVar84 [16];
  float fVar87;
  undefined1 auVar88 [16];
  undefined1 auVar89 [16];
  undefined1 auVar90 [16];
  undefined1 auVar91 [16];
  undefined1 auVar92 [16];
  float fVar93;
  float fVar94;
  float fVar95;
  float fVar96;
  float fVar97;
  undefined1 auVar48 [16];
  undefined1 auVar49 [16];
  undefined1 auVar50 [16];
  undefined1 auVar59 [16];
  undefined1 auVar60 [16];
  undefined1 auVar71 [16];
  undefined1 auVar72 [16];
  undefined1 auVar73 [16];
  
  uVar78 = *(undefined8 *)(param_3 + 0x14);
  *(undefined8 *)(*param_2 + 8) = *(undefined8 *)(param_3 + 0x16);
  *(undefined8 *)*param_2 = uVar78;
  if ((*(byte *)(param_4 + 0x19c) >> 2 & 1) == 0) {
    fVar37 = *param_3;
    fVar38 = param_3[1];
    fVar39 = param_3[2];
    fVar27 = param_3[3];
    fVar1 = param_3[4];
    fVar2 = param_3[5];
    fVar3 = param_3[6];
    fVar17 = param_3[7];
    fVar28 = param_3[8];
    fVar29 = param_3[9];
    fVar30 = param_3[10];
    fVar31 = param_3[0xb];
    param_1 = _UNK_027e519c / param_1;
    auVar12 = NEON_fmov(0x3f800000,4);
    fVar11 = auVar12._0_4_;
    fVar13 = auVar12._4_4_;
    fVar14 = auVar12._8_4_;
    fVar15 = auVar12._12_4_;
    fVar4 = *(float *)(param_5 + 0xc) - fVar27;
    fVar9 = *(float *)(param_5 + 0x1c) - fVar17;
    fVar10 = *(float *)(param_5 + 0x2c) - fVar31;
    fVar55 = *(float *)(param_4 + 0x10) - fVar27;
    fVar61 = *(float *)(param_4 + 0x14) - fVar17;
    fVar62 = *(float *)(param_4 + 0x18) - fVar31;
    auVar75._0_4_ = fVar4 * fVar4;
    auVar75._4_4_ = fVar9 * fVar9;
    auVar75._8_4_ = fVar10 * fVar10;
    auVar67._0_4_ = fVar55 * fVar55;
    auVar67._4_4_ = fVar61 * fVar61;
    auVar67._8_4_ = fVar62 * fVar62;
    auVar75._12_4_ = 0;
    auVar67._12_4_ = 0;
    auVar12 = NEON_ext(auVar75,auVar75,8,1);
    auVar84 = NEON_ext(auVar67,auVar67,8,1);
    uVar78 = NEON_rev64(CONCAT44(auVar12._0_4_ + auVar12._4_4_,auVar75._0_4_ + auVar75._4_4_),4);
    uVar83 = NEON_rev64(CONCAT44(auVar84._0_4_ + auVar84._4_4_,auVar67._0_4_ + auVar67._4_4_),4);
    auVar92._0_4_ = auVar75._0_4_ + auVar75._4_4_ + (float)uVar78;
    auVar74._0_4_ = auVar67._0_4_ + auVar67._4_4_ + (float)uVar83;
    auVar92._4_4_ = auVar92._0_4_;
    auVar92._8_4_ = auVar92._0_4_;
    auVar92._12_4_ = auVar92._0_4_;
    auVar74._4_4_ = auVar74._0_4_;
    auVar74._8_4_ = auVar74._0_4_;
    auVar74._12_4_ = auVar74._0_4_;
    auVar12 = NEON_frsqrte(auVar92,4);
    auVar84 = NEON_frsqrte(auVar74,4);
    fVar77 = auVar12._0_4_;
    auVar88._0_4_ = fVar77 * fVar77;
    fVar79 = auVar12._4_4_;
    auVar88._4_4_ = fVar79 * fVar79;
    fVar80 = auVar12._8_4_;
    auVar88._8_4_ = fVar80 * fVar80;
    fVar81 = auVar12._12_4_;
    auVar88._12_4_ = fVar81 * fVar81;
    fVar82 = auVar84._0_4_;
    auVar90._0_4_ = fVar82 * fVar82;
    fVar85 = auVar84._4_4_;
    auVar90._4_4_ = fVar85 * fVar85;
    fVar86 = auVar84._8_4_;
    auVar90._8_4_ = fVar86 * fVar86;
    fVar87 = auVar84._12_4_;
    auVar90._12_4_ = fVar87 * fVar87;
    auVar12 = NEON_frsqrts(auVar88,auVar92,4);
    auVar84 = NEON_frsqrts(auVar90,auVar74,4);
    fVar77 = fVar77 * auVar12._0_4_;
    fVar79 = fVar79 * auVar12._4_4_;
    fVar80 = fVar80 * auVar12._8_4_;
    fVar81 = fVar81 * auVar12._12_4_;
    fVar82 = fVar82 * auVar84._0_4_;
    fVar85 = fVar85 * auVar84._4_4_;
    fVar86 = fVar86 * auVar84._8_4_;
    fVar87 = fVar87 * auVar84._12_4_;
    auVar89._0_4_ = fVar77 * fVar77;
    auVar89._4_4_ = fVar79 * fVar79;
    auVar89._8_4_ = fVar80 * fVar80;
    auVar89._12_4_ = fVar81 * fVar81;
    auVar91._0_4_ = fVar82 * fVar82;
    auVar91._4_4_ = fVar85 * fVar85;
    auVar91._8_4_ = fVar86 * fVar86;
    auVar91._12_4_ = fVar87 * fVar87;
    auVar12 = NEON_frsqrts(auVar89,auVar92,4);
    auVar84 = NEON_frsqrts(auVar91,auVar74,4);
    fVar4 = fVar4 * fVar77 * auVar12._0_4_;
    fVar9 = fVar9 * fVar79 * auVar12._4_4_;
    fVar10 = fVar10 * fVar80 * auVar12._8_4_;
    fVar55 = fVar55 * fVar82 * auVar84._0_4_;
    fVar61 = fVar61 * fVar85 * auVar84._4_4_;
    fVar62 = fVar62 * fVar86 * auVar84._8_4_;
    auVar12._0_4_ = fVar4 * fVar55;
    auVar12._4_4_ = fVar9 * fVar61;
    auVar12._8_4_ = fVar10 * fVar62;
    auVar12._12_4_ = 0;
    auVar84 = NEON_ext(auVar12,auVar12,8,1);
    uVar78 = NEON_rev64(CONCAT44(auVar84._0_4_ + auVar84._4_4_,auVar12._0_4_ + auVar12._4_4_),4);
    auVar84._0_4_ = auVar12._0_4_ + auVar12._4_4_ + (float)uVar78;
    auVar84._4_4_ = auVar84._0_4_;
    auVar84._8_4_ = auVar84._0_4_;
    auVar84._12_4_ = auVar84._0_4_;
    if (((auVar84._0_4_ < fVar11 - param_1 || auVar84._0_4_ < fVar13 - param_1) ||
        auVar84._0_4_ < fVar14 - param_1) || auVar84._0_4_ < fVar15 - param_1) {
      auVar5._0_4_ = (fVar9 * fVar62 - fVar10 * fVar61) * _UNK_029c49f0;
      auVar5._4_4_ = (fVar4 * fVar62 - fVar10 * fVar55) * _UNK_029c49f4;
      auVar5._8_4_ = (fVar4 * fVar61 - fVar9 * fVar55) * _UNK_029c49f8;
      auVar5._12_4_ = 0x3f800000;
      auVar68._0_4_ = auVar5._0_4_ * auVar5._0_4_;
      auVar68._4_4_ = auVar5._4_4_ * auVar5._4_4_;
      auVar68._8_4_ = auVar5._8_4_ * auVar5._8_4_;
      auVar68._12_4_ = 0;
      auVar12 = NEON_ext(auVar68,auVar68,8,1);
      uVar78 = NEON_rev64(CONCAT44(auVar12._0_4_ + auVar12._4_4_,auVar68._0_4_ + auVar68._4_4_),4);
      if (auVar68._0_4_ + auVar68._4_4_ + (float)uVar78 != 0.0) {
        auVar12 = NEON_fmov(0xbf800000,4);
        auVar63._0_4_ = -(uint)(auVar84._0_4_ < auVar12._0_4_);
        auVar63._4_4_ = -(uint)(auVar84._0_4_ < auVar12._4_4_);
        auVar63._8_4_ = -(uint)(auVar84._0_4_ < auVar12._8_4_);
        auVar63._12_4_ = -(uint)(auVar84._0_4_ < auVar12._12_4_);
        auVar84 = auVar84 ^ (auVar84 ^ auVar12) & auVar63;
        fVar4 = auVar84._0_4_;
        fVar79 = ABS(fVar4);
        fVar55 = auVar84._4_4_;
        fVar80 = ABS(fVar55);
        fVar61 = auVar84._8_4_;
        fVar81 = ABS(fVar61);
        fVar62 = auVar84._12_4_;
        fVar82 = ABS(fVar62);
        fVar87 = fVar37 * fVar2 - fVar38 * fVar1;
        fVar93 = fVar37 * fVar2 - fVar38 * fVar1;
        fVar96 = fVar37 * fVar3 - fVar39 * fVar1;
        fVar97 = fVar37 * fVar3 - fVar39 * fVar1;
        fVar85 = fVar37 * fVar17 - fVar27 * fVar1;
        fVar94 = fVar38 * fVar3 - fVar39 * fVar2;
        fVar95 = fVar38 * fVar3 - fVar39 * fVar2;
        fVar86 = fVar38 * fVar17 - fVar27 * fVar2;
        fVar77 = fVar39 * fVar17 - fVar27 * fVar3;
        auVar19._0_4_ =
             (fVar38 * fVar3 - fVar39 * fVar2) * fVar28 +
             ((fVar37 * fVar2 - fVar38 * fVar1) * fVar30 -
             (fVar37 * fVar3 - fVar39 * fVar1) * fVar29);
        auVar19._4_4_ =
             (fVar38 * fVar3 - fVar39 * fVar2) * fVar28 +
             ((fVar37 * fVar2 - fVar38 * fVar1) * fVar30 -
             (fVar37 * fVar3 - fVar39 * fVar1) * fVar29);
        auVar19._8_4_ = fVar94 * fVar28 + (fVar87 * fVar30 - fVar96 * fVar29);
        auVar19._12_4_ = fVar95 * fVar28 + (fVar93 * fVar30 - fVar97 * fVar29);
        auVar12 = NEON_frecpe(auVar19,4);
        auVar84 = NEON_frecps(auVar12,auVar19,4);
        auVar32._0_4_ = auVar12._0_4_ * auVar84._0_4_;
        auVar32._4_4_ = auVar12._4_4_ * auVar84._4_4_;
        auVar32._8_4_ = auVar12._8_4_ * auVar84._8_4_;
        auVar32._12_4_ = auVar12._12_4_ * auVar84._12_4_;
        auVar12 = NEON_frecps(auVar32,auVar19,4);
        fVar17 = auVar32._0_4_ * auVar12._0_4_;
        fVar27 = auVar32._4_4_ * auVar12._4_4_;
        fVar9 = auVar32._8_4_ * auVar12._8_4_;
        fVar10 = auVar32._12_4_ * auVar12._12_4_;
        auVar33._0_4_ = (fVar2 * fVar30 - fVar3 * fVar29) * fVar17;
        auVar33._4_4_ = (fVar39 * fVar29 - fVar38 * fVar30) * fVar27;
        auVar33._8_4_ = fVar94 * fVar9;
        auVar33._12_4_ = ((fVar86 * fVar30 - fVar77 * fVar29) - fVar95 * fVar31) * fVar10;
        auVar40._0_4_ = (fVar3 * fVar28 - fVar1 * fVar30) * fVar17;
        auVar40._4_4_ = (fVar37 * fVar30 - fVar39 * fVar28) * fVar27;
        auVar40._8_4_ = -fVar96 * fVar9;
        auVar40._12_4_ = (fVar97 * fVar31 + (fVar77 * fVar28 - fVar85 * fVar30)) * fVar10;
        auVar20._0_4_ = (fVar1 * fVar29 - fVar2 * fVar28) * fVar17;
        auVar20._4_4_ = (fVar38 * fVar28 - fVar37 * fVar29) * fVar27;
        auVar20._8_4_ = fVar87 * fVar9;
        auVar20._12_4_ = ((fVar85 * fVar29 - fVar86 * fVar28) - fVar93 * fVar31) * fVar10;
        auVar92 = NEON_ext(auVar5,auVar5,8,1);
        auVar12 = NEON_ext(auVar33,auVar33,8,1);
        auVar84 = NEON_ext(auVar40,auVar40,8,1);
        auVar75 = NEON_ext(auVar20,auVar20,8,1);
        fVar2 = auVar92._0_4_;
        fVar1 = auVar33._0_4_ * auVar5._0_4_ + auVar12._0_4_ * fVar2 +
                auVar33._4_4_ * auVar5._4_4_ + 0.0;
        fVar3 = auVar40._0_4_ * auVar5._0_4_ + auVar84._0_4_ * fVar2 +
                auVar40._4_4_ * auVar5._4_4_ + 0.0;
        fVar2 = auVar20._0_4_ * auVar5._0_4_ + auVar75._0_4_ * fVar2 +
                auVar20._4_4_ * auVar5._4_4_ + 0.0;
        auVar6._0_4_ = fVar1 * fVar1;
        auVar6._4_4_ = fVar3 * fVar3;
        auVar6._8_4_ = fVar2 * fVar2;
        auVar6._12_4_ = 0;
        auVar12 = NEON_ext(auVar6,auVar6,8,1);
        uVar78 = NEON_rev64(CONCAT44(auVar12._0_4_ + auVar12._4_4_,auVar6._0_4_ + auVar6._4_4_),4);
        auVar7._0_4_ = auVar6._0_4_ + auVar6._4_4_ + (float)uVar78;
        auVar7._4_4_ = auVar7._0_4_;
        auVar7._8_4_ = auVar7._0_4_;
        auVar7._12_4_ = auVar7._0_4_;
        auVar12 = NEON_frsqrte(auVar7,4);
        fVar17 = auVar12._0_4_;
        auVar41._0_4_ = fVar17 * fVar17;
        fVar37 = auVar12._4_4_;
        auVar41._4_4_ = fVar37 * fVar37;
        fVar38 = auVar12._8_4_;
        auVar41._8_4_ = fVar38 * fVar38;
        fVar39 = auVar12._12_4_;
        auVar41._12_4_ = fVar39 * fVar39;
        auVar12 = NEON_frsqrts(auVar41,auVar7,4);
        fVar17 = fVar17 * auVar12._0_4_;
        fVar37 = fVar37 * auVar12._4_4_;
        fVar38 = fVar38 * auVar12._8_4_;
        fVar39 = fVar39 * auVar12._12_4_;
        auVar42._0_4_ = fVar17 * fVar17;
        auVar42._4_4_ = fVar37 * fVar37;
        auVar42._8_4_ = fVar38 * fVar38;
        auVar42._12_4_ = fVar39 * fVar39;
        auVar12 = NEON_frsqrts(auVar42,auVar7,4);
        if (((fVar79 < fVar11 && fVar80 < fVar13) && fVar81 < fVar14) && fVar82 < fVar15) {
          if (((0.5 <= fVar79 && 0.5 <= fVar80) && 0.5 <= fVar81) && 0.5 <= fVar82) {
            if (((0.0 <= fVar4 && 0.0 <= fVar55) && 0.0 <= fVar61) && 0.0 <= fVar62) {
              auVar23._0_4_ = (fVar11 - fVar4) * 0.5;
              auVar23._4_4_ = (fVar13 - fVar55) * 0.5;
              auVar23._8_4_ = (fVar14 - fVar61) * 0.5;
              auVar23._12_4_ = (fVar15 - fVar62) * 0.5;
              auVar84 = NEON_frsqrte(auVar23,4);
              fVar27 = auVar84._0_4_;
              auVar53._0_4_ = fVar27 * fVar27;
              fVar28 = auVar84._4_4_;
              auVar53._4_4_ = fVar28 * fVar28;
              fVar29 = auVar84._8_4_;
              auVar53._8_4_ = fVar29 * fVar29;
              fVar30 = auVar84._12_4_;
              auVar53._12_4_ = fVar30 * fVar30;
              auVar84 = NEON_frsqrts(auVar53,auVar23,4);
              fVar27 = fVar27 * auVar84._0_4_;
              fVar28 = fVar28 * auVar84._4_4_;
              fVar29 = fVar29 * auVar84._8_4_;
              fVar30 = fVar30 * auVar84._12_4_;
              auVar65._0_4_ = fVar27 * fVar27;
              auVar65._4_4_ = fVar28 * fVar28;
              auVar65._8_4_ = fVar29 * fVar29;
              auVar65._12_4_ = fVar30 * fVar30;
              auVar84 = NEON_frsqrts(auVar65,auVar23,4);
              auVar54._0_4_ = fVar27 * auVar84._0_4_;
              auVar54._4_4_ = fVar28 * auVar84._4_4_;
              auVar54._8_4_ = fVar29 * auVar84._8_4_;
              auVar54._12_4_ = fVar30 * auVar84._12_4_;
              auVar84 = NEON_frecpe(auVar54,4);
              auVar36._0_4_ =
                   auVar23._0_4_ *
                   (auVar23._0_4_ *
                    (auVar23._0_4_ * (auVar23._0_4_ * 0.077038154 + -0.688284) + 2.0209458) +
                   -2.403395) + fVar11;
              auVar36._4_4_ =
                   auVar23._4_4_ *
                   (auVar23._4_4_ *
                    (auVar23._4_4_ * (auVar23._4_4_ * 0.077038154 + -0.688284) + 2.0209458) +
                   -2.403395) + fVar13;
              auVar36._8_4_ =
                   auVar23._8_4_ *
                   (auVar23._8_4_ *
                    (auVar23._8_4_ * (auVar23._8_4_ * 0.077038154 + -0.688284) + 2.0209458) +
                   -2.403395) + fVar14;
              auVar36._12_4_ =
                   auVar23._12_4_ *
                   (auVar23._12_4_ *
                    (auVar23._12_4_ * (auVar23._12_4_ * 0.077038154 + -0.688284) + 2.0209458) +
                   -2.403395) + fVar15;
              auVar75 = NEON_frecps(auVar84,auVar54,4);
              auVar57._0_4_ = auVar84._0_4_ * auVar75._0_4_;
              auVar57._4_4_ = auVar84._4_4_ * auVar75._4_4_;
              auVar57._8_4_ = auVar84._8_4_ * auVar75._8_4_;
              auVar57._12_4_ = auVar84._12_4_ * auVar75._12_4_;
              auVar75 = NEON_frecpe(auVar36,4);
              auVar84 = NEON_frecps(auVar75,auVar36,4);
              auVar45._0_4_ = auVar75._0_4_ * auVar84._0_4_;
              auVar45._4_4_ = auVar75._4_4_ * auVar84._4_4_;
              auVar45._8_4_ = auVar75._8_4_ * auVar84._8_4_;
              auVar45._12_4_ = auVar75._12_4_ * auVar84._12_4_;
              auVar84 = NEON_frecps(auVar45,auVar36,4);
              auVar75 = NEON_frecps(auVar57,auVar54,4);
              fVar27 = auVar57._0_4_ * auVar75._0_4_;
              fVar28 = auVar57._4_4_ * auVar75._4_4_;
              fVar29 = auVar57._8_4_ * auVar75._8_4_;
              fVar30 = auVar57._12_4_ * auVar75._12_4_;
              fVar27 = fVar27 + fVar27 * auVar23._0_4_ *
                                         (auVar23._0_4_ *
                                          (auVar23._0_4_ *
                                           (auVar23._0_4_ *
                                            (auVar23._0_4_ *
                                             (auVar23._0_4_ * 3.479331e-05 + 0.000791535) +
                                            -0.040055536) + 0.20121253) + -0.32556581) + 0.16666667)
                                         * auVar45._0_4_ * auVar84._0_4_;
              fVar28 = fVar28 + fVar28 * auVar23._4_4_ *
                                         (auVar23._4_4_ *
                                          (auVar23._4_4_ *
                                           (auVar23._4_4_ *
                                            (auVar23._4_4_ *
                                             (auVar23._4_4_ * 3.479331e-05 + 0.000791535) +
                                            -0.040055536) + 0.20121253) + -0.32556581) + 0.16666667)
                                         * auVar45._4_4_ * auVar84._4_4_;
              fVar29 = fVar29 + fVar29 * auVar23._8_4_ *
                                         (auVar23._8_4_ *
                                          (auVar23._8_4_ *
                                           (auVar23._8_4_ *
                                            (auVar23._8_4_ *
                                             (auVar23._8_4_ * 3.479331e-05 + 0.000791535) +
                                            -0.040055536) + 0.20121253) + -0.32556581) + 0.16666667)
                                         * auVar45._8_4_ * auVar84._8_4_;
              fVar30 = fVar30 + fVar30 * auVar23._12_4_ *
                                         (auVar23._12_4_ *
                                          (auVar23._12_4_ *
                                           (auVar23._12_4_ *
                                            (auVar23._12_4_ *
                                             (auVar23._12_4_ * 3.479331e-05 + 0.000791535) +
                                            -0.040055536) + 0.20121253) + -0.32556581) + 0.16666667)
                                         * auVar45._12_4_ * auVar84._12_4_;
              auVar21._0_4_ = fVar27 + fVar27;
              auVar21._4_4_ = fVar28 + fVar28;
              auVar21._8_4_ = fVar29 + fVar29;
              auVar21._12_4_ = fVar30 + fVar30;
              goto LAB_0242a85c;
            }
            auVar22._0_4_ = fVar4 * 0.5 + 0.5;
            auVar22._4_4_ = fVar55 * 0.5 + 0.5;
            auVar22._8_4_ = fVar61 * 0.5 + 0.5;
            auVar22._12_4_ = fVar62 * 0.5 + 0.5;
            auVar84 = NEON_frsqrte(auVar22,4);
            fVar27 = auVar84._0_4_;
            auVar51._0_4_ = fVar27 * fVar27;
            fVar28 = auVar84._4_4_;
            auVar51._4_4_ = fVar28 * fVar28;
            fVar29 = auVar84._8_4_;
            auVar51._8_4_ = fVar29 * fVar29;
            fVar30 = auVar84._12_4_;
            auVar51._12_4_ = fVar30 * fVar30;
            auVar84 = NEON_frsqrts(auVar51,auVar22,4);
            fVar27 = fVar27 * auVar84._0_4_;
            fVar28 = fVar28 * auVar84._4_4_;
            fVar29 = fVar29 * auVar84._8_4_;
            fVar30 = fVar30 * auVar84._12_4_;
            auVar64._0_4_ = fVar27 * fVar27;
            auVar64._4_4_ = fVar28 * fVar28;
            auVar64._8_4_ = fVar29 * fVar29;
            auVar64._12_4_ = fVar30 * fVar30;
            auVar84 = NEON_frsqrts(auVar64,auVar22,4);
            auVar52._0_4_ = fVar27 * auVar84._0_4_;
            auVar52._4_4_ = fVar28 * auVar84._4_4_;
            auVar52._8_4_ = fVar29 * auVar84._8_4_;
            auVar52._12_4_ = fVar30 * auVar84._12_4_;
            auVar84 = NEON_frecpe(auVar52,4);
            auVar34._0_4_ =
                 auVar22._0_4_ *
                 (auVar22._0_4_ *
                  (auVar22._0_4_ * (auVar22._0_4_ * 0.077038154 + -0.688284) + 2.0209458) +
                 -2.403395) + fVar11;
            auVar34._4_4_ =
                 auVar22._4_4_ *
                 (auVar22._4_4_ *
                  (auVar22._4_4_ * (auVar22._4_4_ * 0.077038154 + -0.688284) + 2.0209458) +
                 -2.403395) + fVar13;
            auVar34._8_4_ =
                 auVar22._8_4_ *
                 (auVar22._8_4_ *
                  (auVar22._8_4_ * (auVar22._8_4_ * 0.077038154 + -0.688284) + 2.0209458) +
                 -2.403395) + fVar14;
            auVar34._12_4_ =
                 auVar22._12_4_ *
                 (auVar22._12_4_ *
                  (auVar22._12_4_ * (auVar22._12_4_ * 0.077038154 + -0.688284) + 2.0209458) +
                 -2.403395) + fVar15;
            auVar75 = NEON_frecps(auVar84,auVar52,4);
            auVar56._0_4_ = auVar84._0_4_ * auVar75._0_4_;
            auVar56._4_4_ = auVar84._4_4_ * auVar75._4_4_;
            auVar56._8_4_ = auVar84._8_4_ * auVar75._8_4_;
            auVar56._12_4_ = auVar84._12_4_ * auVar75._12_4_;
            auVar75 = NEON_frecpe(auVar34,4);
            auVar84 = NEON_frecps(auVar75,auVar34,4);
            auVar43._0_4_ = auVar75._0_4_ * auVar84._0_4_;
            auVar43._4_4_ = auVar75._4_4_ * auVar84._4_4_;
            auVar43._8_4_ = auVar75._8_4_ * auVar84._8_4_;
            auVar43._12_4_ = auVar75._12_4_ * auVar84._12_4_;
            auVar84 = NEON_frecps(auVar43,auVar34,4);
            auVar75 = NEON_frecps(auVar56,auVar52,4);
            fVar4 = auVar56._0_4_ * auVar75._0_4_;
            fVar55 = auVar56._4_4_ * auVar75._4_4_;
            fVar61 = auVar56._8_4_ * auVar75._8_4_;
            fVar62 = auVar56._12_4_ * auVar75._12_4_;
            fVar4 = fVar4 + fVar4 * auVar22._0_4_ *
                                    (auVar22._0_4_ *
                                     (auVar22._0_4_ *
                                      (auVar22._0_4_ *
                                       (auVar22._0_4_ * (auVar22._0_4_ * 3.479331e-05 + 0.000791535)
                                       + -0.040055536) + 0.20121253) + -0.32556581) + 0.16666667) *
                                    auVar43._0_4_ * auVar84._0_4_;
            fVar55 = fVar55 + fVar55 * auVar22._4_4_ *
                                       (auVar22._4_4_ *
                                        (auVar22._4_4_ *
                                         (auVar22._4_4_ *
                                          (auVar22._4_4_ *
                                           (auVar22._4_4_ * 3.479331e-05 + 0.000791535) +
                                          -0.040055536) + 0.20121253) + -0.32556581) + 0.16666667) *
                                       auVar43._4_4_ * auVar84._4_4_;
            fVar61 = fVar61 + fVar61 * auVar22._8_4_ *
                                       (auVar22._8_4_ *
                                        (auVar22._8_4_ *
                                         (auVar22._8_4_ *
                                          (auVar22._8_4_ *
                                           (auVar22._8_4_ * 3.479331e-05 + 0.000791535) +
                                          -0.040055536) + 0.20121253) + -0.32556581) + 0.16666667) *
                                       auVar43._8_4_ * auVar84._8_4_;
            fVar62 = fVar62 + fVar62 * auVar22._12_4_ *
                                       (auVar22._12_4_ *
                                        (auVar22._12_4_ *
                                         (auVar22._12_4_ *
                                          (auVar22._12_4_ *
                                           (auVar22._12_4_ * 3.479331e-05 + 0.000791535) +
                                          -0.040055536) + 0.20121253) + -0.32556581) + 0.16666667) *
                                       auVar43._12_4_ * auVar84._12_4_;
            fVar27 = 3.1415927;
            fVar4 = fVar4 + fVar4;
            fVar55 = fVar55 + fVar55;
            fVar61 = fVar61 + fVar61;
            fVar62 = fVar62 + fVar62;
          }
          else {
            fVar27 = 1.5707964;
            if (((fVar79 <= 1.1920929e-07 || fVar80 <= 1.1920929e-07) || fVar81 <= 1.1920929e-07) ||
                fVar82 <= 1.1920929e-07) {
              auVar21._8_4_ = 1.5707964;
              auVar21._0_8_ = 0x3fc90fdb3fc90fdb;
              auVar21._12_4_ = 1.5707964;
              goto LAB_0242a85c;
            }
            fVar28 = fVar4 * fVar4;
            fVar29 = fVar55 * fVar55;
            fVar30 = fVar61 * fVar61;
            fVar31 = fVar62 * fVar62;
            auVar44._0_4_ =
                 fVar28 * (fVar28 * (fVar28 * (fVar28 * 0.077038154 + -0.688284) + 2.0209458) +
                          -2.403395) + fVar11;
            auVar44._4_4_ =
                 fVar29 * (fVar29 * (fVar29 * (fVar29 * 0.077038154 + -0.688284) + 2.0209458) +
                          -2.403395) + fVar13;
            auVar44._8_4_ =
                 fVar30 * (fVar30 * (fVar30 * (fVar30 * 0.077038154 + -0.688284) + 2.0209458) +
                          -2.403395) + fVar14;
            auVar44._12_4_ =
                 fVar31 * (fVar31 * (fVar31 * (fVar31 * 0.077038154 + -0.688284) + 2.0209458) +
                          -2.403395) + fVar15;
            auVar75 = NEON_frecpe(auVar44,4);
            auVar84 = NEON_frecps(auVar75,auVar44,4);
            auVar35._0_4_ = auVar75._0_4_ * auVar84._0_4_;
            auVar35._4_4_ = auVar75._4_4_ * auVar84._4_4_;
            auVar35._8_4_ = auVar75._8_4_ * auVar84._8_4_;
            auVar35._12_4_ = auVar75._12_4_ * auVar84._12_4_;
            auVar84 = NEON_frecps(auVar35,auVar44,4);
            fVar4 = fVar4 * (fVar28 * (fVar28 * (fVar28 * (fVar28 * (fVar28 * (fVar28 * 3.479331e-05
                                                                              + 0.000791535) +
                                                                    -0.040055536) + 0.20121253) +
                                                -0.32556581) + 0.16666667) *
                             auVar35._0_4_ * auVar84._0_4_ + fVar11);
            fVar55 = fVar55 * (fVar29 * (fVar29 * (fVar29 * (fVar29 * (fVar29 * (fVar29 * 
                                                  3.479331e-05 + 0.000791535) + -0.040055536) +
                                                  0.20121253) + -0.32556581) + 0.16666667) *
                               auVar35._4_4_ * auVar84._4_4_ + fVar13);
            fVar61 = fVar61 * (fVar30 * (fVar30 * (fVar30 * (fVar30 * (fVar30 * (fVar30 * 
                                                  3.479331e-05 + 0.000791535) + -0.040055536) +
                                                  0.20121253) + -0.32556581) + 0.16666667) *
                               auVar35._8_4_ * auVar84._8_4_ + fVar14);
            fVar62 = fVar62 * (fVar31 * (fVar31 * (fVar31 * (fVar31 * (fVar31 * (fVar31 * 
                                                  3.479331e-05 + 0.000791535) + -0.040055536) +
                                                  0.20121253) + -0.32556581) + 0.16666667) *
                               auVar35._12_4_ * auVar84._12_4_ + fVar15);
          }
          auVar21._0_4_ = fVar27 - fVar4;
          auVar21._4_4_ = fVar27 - fVar55;
          auVar21._8_4_ = fVar27 - fVar61;
          auVar21._12_4_ = fVar27 - fVar62;
        }
        else {
          iVar18 = -(uint)(((fVar4 <= 0.0 && fVar55 <= 0.0) && fVar61 <= 0.0) && fVar62 <= 0.0);
          bVar16 = (byte)iVar18;
          bVar24 = (byte)((uint)iVar18 >> 8);
          bVar25 = (byte)((uint)iVar18 >> 0x10);
          bVar26 = (byte)((uint)iVar18 >> 0x18);
          auVar21._0_8_ =
               CONCAT17(bVar26,CONCAT16(bVar25,CONCAT15(bVar24,CONCAT14(bVar16,iVar18)))) &
               0x40490fdb40490fdb;
          auVar21[8] = bVar16 & 0xdb;
          auVar21[9] = bVar24 & 0xf;
          auVar21[10] = bVar25 & 0x49;
          auVar21[0xb] = bVar26 & 0x40;
          auVar21[0xc] = bVar16 & 0xdb;
          auVar21[0xd] = bVar24 & 0xf;
          auVar21[0xe] = bVar25 & 0x49;
          auVar21[0xf] = bVar26 & 0x40;
        }
LAB_0242a85c:
        fVar27 = auVar21._0_4_ * 0.5;
        fVar28 = auVar21._4_4_ * 0.5;
        fVar29 = auVar21._8_4_ * 0.5;
        fVar30 = auVar21._12_4_ * 0.5;
        fVar31 = fVar27 * fVar27;
        fVar4 = fVar28 * fVar28;
        fVar55 = fVar29 * fVar29;
        fVar9 = fVar30 * fVar30;
        auVar84 = *param_2;
        fVar61 = auVar84._0_4_;
        fVar10 = auVar84._4_4_;
        fVar62 = auVar84._8_4_;
        fVar11 = auVar84._12_4_;
        auVar75 = NEON_ext(auVar84,auVar84,4,1);
        auVar76._4_4_ = auVar75._12_4_;
        auVar76._0_4_ = auVar75._4_4_;
        auVar76._8_4_ = 0.0 - fVar10;
        auVar76._12_4_ = 0.0 - fVar11;
        auVar59._0_8_ = auVar75._0_8_;
        auVar59._8_4_ = auVar75._4_4_;
        auVar59._12_4_ = auVar75._12_4_;
        auVar58._8_8_ = auVar59._8_8_;
        auVar58._0_4_ = auVar75._0_4_;
        auVar58._4_4_ = fVar61;
        auVar60._0_12_ = auVar58._0_12_;
        auVar60._12_4_ = fVar10;
        auVar92 = NEON_ext(auVar60,auVar76,0xc,1);
        auVar46._0_4_ =
             fVar27 * fVar31 *
             (fVar31 * (fVar31 * (fVar31 * (fVar31 * (fVar31 * (fVar31 * -6.5797845e-13 +
                                                               1.5884676e-10) + -2.5036849e-08) +
                                           2.7556557e-06) + -0.00019841248) + 0.008333333) +
             -0.16666667);
        auVar46._4_4_ =
             fVar28 * fVar4 *
             (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * (fVar4 * -6.5797845e-13 + 1.5884676e-10) +
                                                 -2.5036849e-08) + 2.7556557e-06) + -0.00019841248)
                      + 0.008333333) + -0.16666667);
        auVar46._8_4_ =
             fVar29 * fVar55 *
             (fVar55 * (fVar55 * (fVar55 * (fVar55 * (fVar55 * (fVar55 * -6.5797845e-13 +
                                                               1.5884676e-10) + -2.5036849e-08) +
                                           2.7556557e-06) + -0.00019841248) + 0.008333333) +
             -0.16666667);
        auVar46._12_4_ =
             fVar30 * fVar9 *
             (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * -6.5797845e-13 + 1.5884676e-10) +
                                                 -2.5036849e-08) + 2.7556557e-06) + -0.00019841248)
                      + 0.008333333) + -0.16666667);
        fVar15 = fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * (fVar9 * -9.773531e-12 +
                                                                      2.0620272e-09) +
                                                             -2.7536933e-07) + 2.4800687e-05) +
                                           -0.0013888867) + 0.041666664) + -0.5) + fVar15;
        auVar8._0_4_ = fVar1 * fVar17 * auVar12._0_4_ * (fVar27 + auVar46._0_4_);
        auVar8._4_4_ = fVar3 * fVar37 * auVar12._4_4_ * (fVar28 + auVar46._4_4_);
        auVar8._8_4_ = fVar2 * fVar38 * auVar12._8_4_ * (fVar29 + auVar46._8_4_);
        auVar8._12_4_ = fVar39 * auVar12._12_4_ * 1.0 * (fVar30 + auVar46._12_4_);
        auVar47._4_12_ = auVar46._4_12_;
        auVar47._0_4_ = auVar8._0_4_;
        auVar49._0_8_ = auVar47._0_8_;
        auVar49._8_4_ = auVar8._4_4_;
        auVar49._12_4_ = auVar46._12_4_;
        auVar48._8_8_ = auVar49._8_8_;
        auVar48._4_4_ = auVar8._0_4_;
        auVar48._0_4_ = auVar8._0_4_;
        auVar50._0_12_ = auVar48._0_12_;
        auVar50._12_4_ = auVar8._4_4_;
        auVar69._4_4_ = auVar8._8_4_;
        auVar69._0_4_ = auVar8._8_4_;
        auVar69._8_4_ = auVar8._8_4_;
        auVar69._12_4_ = auVar8._8_4_;
        auVar66._4_4_ = fVar62;
        auVar66._0_4_ = fVar61;
        auVar66._8_4_ = fVar61;
        auVar66._12_4_ = fVar62;
        auVar12 = NEON_rev64(auVar8,4);
        auVar70._4_12_ = auVar69._4_12_;
        auVar70._0_4_ = auVar8._0_4_;
        auVar72._0_8_ = auVar70._0_8_;
        auVar72._8_4_ = auVar8._4_4_;
        auVar72._12_4_ = auVar8._8_4_;
        auVar71._8_8_ = auVar72._8_8_;
        auVar71._4_4_ = auVar8._8_4_;
        auVar71._0_4_ = auVar8._0_4_;
        auVar73._0_12_ = auVar71._0_12_;
        auVar73._12_4_ = auVar8._8_4_;
        auVar75 = NEON_ext(auVar50,auVar50,4,1);
        auVar67 = NEON_ext(auVar66,auVar84,0xc,1);
        auVar12 = NEON_ext(auVar12,auVar75,0xc,1);
        auVar84 = NEON_ext(auVar73,auVar73,8,1);
        *(float *)(*param_2 + 8) =
             (auVar92._8_4_ * auVar12._8_4_ - auVar67._8_4_ * auVar84._8_4_) +
             auVar8._8_4_ * fVar11 + fVar15 * fVar62;
        *(float *)(*param_2 + 0xc) =
             (auVar92._12_4_ * auVar12._12_4_ - auVar67._12_4_ * auVar84._12_4_) +
             fVar15 * fVar11 + (0.0 - fVar61) * auVar8._0_4_;
        *(float *)*param_2 =
             (auVar92._0_4_ * auVar12._0_4_ - auVar67._0_4_ * auVar84._0_4_) +
             auVar8._0_4_ * fVar11 + fVar15 * fVar61;
        *(float *)(*param_2 + 4) =
             (auVar92._4_4_ * auVar12._4_4_ - auVar67._4_4_ * auVar84._4_4_) +
             auVar8._4_4_ * fVar11 + fVar15 * fVar10;
        return;
      }
    }
  }
  return;
}

// ==== FUN_0242a9f4
// vaddr 0x232a9f4 | ghidra 0x242a9f4 | size 0 | symbol FUN_0242a9f4 | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0242a9f4(float param_1,float param_2,float param_3,float param_4,float param_5,
                 float param_6,long param_7,long param_8,long param_9,float *param_10)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  param_5 = param_6 * param_6 * param_5;
  param_5 = param_5 + param_5;
  if ((param_5 < param_2) ||
     (param_5 * param_5 <
      param_6 * param_6 *
      (*(float *)(param_8 + 0x50) * *(float *)(param_8 + 0x50) +
       *(float *)(param_8 + 0x54) * *(float *)(param_8 + 0x54) +
      *(float *)(param_8 + 0x58) * *(float *)(param_8 + 0x58)))) {
    param_2 = (*(float *)(param_7 + 0x30) * param_4 + 1.0) * param_2;
  }
  fVar5 = *param_10;
  fVar6 = param_10[1];
  fVar7 = param_10[2];
  fVar2 = fVar5 * fVar5 + fVar6 * fVar6 + fVar7 * fVar7;
  fVar1 = SQRT(fVar2);
  if (NAN(fVar1)) {
    fVar1 = (float)sqrtf(fVar2);
  }
  fVar2 = fVar5;
  fVar3 = fVar6;
  fVar4 = fVar7;
  if (_UNK_027e519c <= fVar1) {
    fVar1 = 1.0 / fVar1;
    fVar2 = fVar1 * fVar5;
    fVar3 = fVar1 * fVar6;
    fVar4 = fVar1 * fVar7;
  }
  *(float *)(param_8 + 0x90) = *(float *)(param_8 + 0x90) + fVar2;
  *(float *)(param_8 + 0x94) = *(float *)(param_8 + 0x94) + fVar3;
  *(float *)(param_8 + 0x98) = *(float *)(param_8 + 0x98) + fVar4;
  *(float *)(param_9 + 0x90) = *(float *)(param_9 + 0x90) + fVar2;
  *(float *)(param_9 + 0x94) = *(float *)(param_9 + 0x94) + fVar3;
  *(float *)(param_9 + 0x98) = *(float *)(param_9 + 0x98) + fVar4;
  fVar5 = param_2 * fVar5;
  param_3 = *(float *)(param_7 + 0x2c) * param_3;
  *(float *)(param_8 + 0x18c) = *(float *)(param_8 + 0x18c) + param_3;
  *(float *)(param_9 + 0x18c) = param_3 + *(float *)(param_9 + 0x18c);
  fVar6 = param_2 * fVar6;
  param_2 = param_2 * fVar7;
  if ((*(byte *)(param_8 + 0x19c) & 1) == 0) {
    if ((*(byte *)(param_9 + 0x19c) & 1) == 0) {
      fVar2 = *(float *)(param_8 + 0x180) + *(float *)(param_9 + 0x180);
      fVar1 = *(float *)(param_8 + 0x180) / fVar2;
      if (fVar2 <= 0.0) {
        fVar1 = 0.5;
      }
      fVar7 = fVar1 * (fVar1 - param_1);
      fVar3 = (fVar1 + -1.0) * (fVar1 - param_1);
      fVar2 = fVar5 + fVar5 * fVar3;
      fVar1 = fVar6 + fVar6 * fVar3;
      param_1 = param_2 + param_2 * fVar3;
      *(float *)(param_8 + 0x10) = *(float *)(param_8 + 0x10) + fVar5 + fVar5 * fVar7;
      *(float *)(param_8 + 0x14) = *(float *)(param_8 + 0x14) + fVar6 + fVar6 * fVar7;
      *(float *)(param_8 + 0x18) = *(float *)(param_8 + 0x18) + param_2 + param_2 * fVar7;
    }
    else {
      fVar7 = _UNK_027e5198;
      if (param_1 <= _UNK_029e2c98) {
        fVar7 = 1.0 / (1.0 - param_1);
      }
      fVar2 = fVar5 * fVar7;
      fVar1 = fVar6 * fVar7;
      param_1 = param_2 * fVar7;
      param_9 = param_8;
    }
  }
  else {
    if ((*(byte *)(param_9 + 0x19c) & 1) != 0) {
      return;
    }
    if (_UNK_027e6ae4 <= param_1) {
      param_1 = 1.0 / param_1;
      fVar2 = param_1 * fVar5;
      fVar1 = param_1 * fVar6;
      param_1 = param_1 * param_2;
    }
    else {
      fVar2 = fVar5 * _UNK_027e5198;
      fVar1 = fVar6 * _UNK_027e5198;
      param_1 = param_2 * _UNK_027e5198;
    }
  }
  *(float *)(param_9 + 0x10) = fVar2 + *(float *)(param_9 + 0x10);
  *(float *)(param_9 + 0x14) = fVar1 + *(float *)(param_9 + 0x14);
  *(float *)(param_9 + 0x18) = param_1 + *(float *)(param_9 + 0x18);
  return;
}

// ==== FUN_0242ac84
// vaddr 0x232ac84 | ghidra 0x242ac84 | size 0 | symbol FUN_0242ac84 | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0242ac84(float param_1,long param_2,long param_3,uint param_4)

{
  undefined4 uVar1;
  undefined8 uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  uVar2 = _UNK_027dbb30;
  if ((param_4 & 1) == 0) {
    fVar8 = (*(float *)(param_2 + 0x10) - *(float *)(param_2 + 0x20)) * param_1;
    fVar7 = (*(float *)(param_2 + 0x14) - *(float *)(param_2 + 0x24)) * param_1;
    param_1 = (*(float *)(param_2 + 0x18) - *(float *)(param_2 + 0x28)) * param_1;
    if (0.0 < *(float *)(param_2 + 0x18c)) {
      fVar9 = (float)NEON_fminnm(*(float *)(param_2 + 0x18c),0x3f800000);
      fVar4 = *(float *)(param_2 + 0x90) * *(float *)(param_2 + 0x90) +
              *(float *)(param_2 + 0x94) * *(float *)(param_2 + 0x94) +
              *(float *)(param_2 + 0x98) * *(float *)(param_2 + 0x98);
      fVar3 = SQRT(fVar4);
      if (NAN(fVar3)) {
        fVar3 = (float)sqrtf(fVar4);
      }
      fVar9 = 1.0 - fVar9;
      if (fVar3 < _UNK_027e519c) {
        fVar4 = *(float *)(param_2 + 0x90);
        fVar5 = *(float *)(param_2 + 0x94);
        fVar3 = *(float *)(param_2 + 0x98);
      }
      else {
        fVar3 = 1.0 / fVar3;
        fVar4 = fVar3 * *(float *)(param_2 + 0x90);
        fVar5 = fVar3 * *(float *)(param_2 + 0x94);
        fVar3 = fVar3 * *(float *)(param_2 + 0x98);
        *(float *)(param_2 + 0x90) = fVar4;
        *(float *)(param_2 + 0x94) = fVar5;
        *(float *)(param_2 + 0x98) = fVar3;
      }
      fVar6 = fVar8 * fVar4 + fVar7 * fVar5 + param_1 * fVar3;
      fVar8 = fVar4 * fVar6 + fVar9 * (fVar8 - fVar4 * fVar6);
      fVar7 = fVar5 * fVar6 + fVar9 * (fVar7 - fVar5 * fVar6);
      param_1 = fVar3 * fVar6 + fVar9 * (param_1 - fVar3 * fVar6);
    }
    *(float *)(param_2 + 0x50) = fVar8;
    *(float *)(param_2 + 0x54) = fVar7;
    *(float *)(param_2 + 0x58) = param_1;
    *(undefined4 *)(param_2 + 0x5c) = 0x3f800000;
    if (*(char *)(param_2 + 0x19f) != '\0') {
      fVar3 = *(float *)(param_2 + 0x1b8);
      *(float *)(param_2 + 0x50) = fVar3 * fVar8;
      *(float *)(param_2 + 0x54) = fVar3 * fVar7;
      *(float *)(param_2 + 0x58) = fVar3 * param_1;
    }
  }
  else {
    *(undefined8 *)(param_2 + 0x58) = _UNK_027dbb38;
    *(undefined8 *)(param_2 + 0x50) = uVar2;
  }
  uVar2 = *(undefined8 *)(param_3 + 0x54);
  uVar1 = *(undefined4 *)(param_3 + 0x5c);
  *(undefined4 *)(param_2 + 0x60) = *(undefined4 *)(param_3 + 0x50);
  *(undefined8 *)(param_2 + 100) = uVar2;
  *(undefined4 *)(param_2 + 0x6c) = uVar1;
  return;
}
