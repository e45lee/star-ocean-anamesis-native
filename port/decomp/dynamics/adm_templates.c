// port/decomp/dynamics/adm_templates.c: Ghidra decompiles for the dynamics subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 14:45 UTC: tools/decomp.sh '--into' 'dynamics/adm_templates' 'Aska::ArticulatedDynamicsManager\w*::\w+<'

// ==== void Aska::ArticulatedDynamicsManager::SimulateMain<Aska::ArticulatedDynamicsManager>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::ADMJoint*, unsigned int, int, int, unsigned int, float, float, unsigned int, float)
// vaddr 0x2326ecc | ghidra 0x2426ecc | size 904 | symbol _ZN4Aska26ArticulatedDynamicsManager12SimulateMainIS0_EEvPT_PNS_8ADMJointES5_jiijffjf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska26ArticulatedDynamicsManager12SimulateMainIS0_EEvPT_PNS_8ADMJointES5_jiijffjf
               (undefined8 param_1,undefined8 param_2,float param_3,long param_4,undefined8 param_5,
               undefined8 param_6,uint param_7,int param_8,int param_9,undefined4 param_10,
               uint param_11)

{
  bool bVar1;
  int iVar2;
  long lVar3;
  int iVar4;
  char cVar5;
  short sVar6;
  byte bVar7;
  int iVar8;
  ulong uVar9;
  uint uVar10;
  ulong uVar11;
  undefined4 *puVar12;
  long lVar13;
  int iVar14;
  long lVar15;
  ulong uVar16;
  int iVar17;
  int iVar18;
  uint uStack_b8;
  
  sVar6 = *(short *)(param_4 + 0x62);
  if (*(char *)(param_4 + 0x9b) == '\x02') {
    iVar17 = (int)*(short *)(param_4 + 0x60);
    bVar7 = 1;
  }
  else {
    iVar17 = 1;
    bVar7 = *(byte *)(param_4 + 0x9a) & 1;
  }
  cVar5 = *(char *)(param_4 + 0xe2);
  iVar8 = (int)*(short *)(param_4 + 100);
  if (*(char *)(param_4 + 0xde) != '\0') {
    iVar8 = (uint)(byte)*PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0
            + iVar8;
  }
  uStack_b8 = 0;
  iVar4 = *(int *)(param_4 + 0x1a0);
  bVar1 = _UNK_027e519c < param_3;
  uVar10 = (uint)(byte)*PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98;
  if (*(char *)(param_4 + 0xde) == '\0') {
    uVar10 = 0;
  }
  uVar9 = (long)sVar6 & 0xffffffff;
  iVar2 = uVar10 + (int)*(short *)(param_4 + 0x66);
  if (*(long *)(param_4 + 0x130) != 0) {
    iVar2 = iVar2 + 1;
  }
  lVar13 = (uVar9 + ((long)sVar6 & 0xffffffffU) * 4) * 0x10;
  do {
    iVar14 = param_8;
    if (param_8 < param_9) {
      do {
        if (*(char *)(param_4 + 0x121) != '\0') {
          Aska::ArticulatedDynamicsManagerBase::UpdateDynamicsPrimitiveListWithDependencyOfADM(unsigned int)(param_4,iVar14);
        }
        void Aska::ArticulatedDynamicsManager::PreprocessBeforeInternalForce<Aska::ArticulatedDynamicsManager>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::ADMJoint*, float, float, unsigned int, unsigned int, bool)(param_1,param_2,param_4,param_5,param_6,param_9,iVar14,cVar5 != '\0');
        if (iVar17 != 0) {
          iVar18 = 0;
          do {
            if (sVar6 != 0) {
              uVar11 = *(ulong *)(param_4 + 0x78);
              if (*(char *)(param_4 + 0x9b) == '\x01') {
                uVar10 = 0;
                do {
                  lVar15 = 0;
                  do {
                    lVar3 = uVar11 + lVar15;
                    if (((*(byte *)(*(long *)(lVar3 + 0x40) + 0x19c) & 1) == 0) ||
                       ((*(byte *)(*(long *)(lVar3 + 0x48) + 0x19c) & 1) == 0)) {
                      void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x1d0(*(undefined4 *)(lVar3 + 0x28),*(undefined4 *)(lVar3 + 0x34),
                                      param_1,*(undefined1 *)(lVar3 + 0x21));
                    }
                    lVar15 = lVar15 + 0x50;
                    uVar16 = uVar11 + (uVar9 * 0x10 - 0x10 >> 4) * 0x50;
                  } while (lVar13 - lVar15 != 0);
                  do {
                    if (((*(byte *)(*(long *)(uVar16 + 0x40) + 0x19c) & 1) == 0) ||
                       ((*(byte *)(*(long *)(uVar16 + 0x48) + 0x19c) & 1) == 0)) {
                      void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x1d0(*(undefined4 *)(uVar16 + 0x28),*(undefined4 *)(uVar16 + 0x34),
                                      param_1,*(undefined1 *)(uVar16 + 0x21));
                    }
                    uVar16 = uVar16 - 0x50;
                  } while (uVar11 <= uVar16);
                  uVar10 = uVar10 + 1;
                } while (uVar10 < param_7);
              }
              else {
                puVar12 = (undefined4 *)(uVar11 + 0x28);
                lVar15 = lVar13;
                do {
                  if (((*(byte *)(*(long *)(puVar12 + 6) + 0x19c) & 1) == 0) ||
                     ((*(byte *)(*(long *)(puVar12 + 8) + 0x19c) & 1) == 0)) {
                    void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x1d0(*puVar12,puVar12[3],param_1,*(undefined1 *)((long)puVar12 + -7))
                    ;
                  }
                  lVar15 = lVar15 + -0x50;
                  puVar12 = puVar12 + 0x14;
                } while (lVar15 != 0);
              }
            }
            if (bVar7 == 0) {
              void Aska::ArticulatedDynamicsManagerBase::StandardIK<Aska::ArticulatedDynamicsManager, false>(Aska::ArticulatedDynamicsManager*, float, float, int)(param_1,param_2,param_4,param_10);
            }
            void Aska::ArticulatedDynamicsManagerBase::CollisionAndConstraint<Aska::ArticulatedDynamicsManager>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::ADMJoint*, unsigned int, unsigned int, float)(param_1,param_4,param_5,param_6,iVar4 + iVar8,iVar2);
            iVar18 = iVar18 + 1;
          } while (iVar18 != iVar17);
        }
        if (bVar7 == 0) {
          void Aska::ArticulatedDynamicsManagerBase::Finalize<Aska::ArticulatedDynamicsManager>(Aska::ArticulatedDynamicsManager*, float, float, int)(param_1,param_2,param_4,param_10);
        }
        else {
          void Aska::ArticulatedDynamicsManagerBase::StandardIK<Aska::ArticulatedDynamicsManager, true>(Aska::ArticulatedDynamicsManager*, float, float, int)(param_1,param_2,param_4,param_10);
        }
        iVar14 = iVar14 + 1;
      } while (iVar14 != param_9);
    }
    if (bVar1 && 0.0 <= param_3) {
      if ((long)*(short *)(param_4 + 0x60) < 1) {
code_r0x02427228:
        *(undefined4 *)(param_4 + 0x118) = 0;
        return;
      }
      uVar11 = *(ulong *)(param_4 + 0x70);
      uVar16 = uVar11 + (long)*(short *)(param_4 + 0x60) * 0x1c0;
      while (((ABS(*(float *)(uVar11 + 0x50)) <= param_3 &&
              (ABS(*(float *)(uVar11 + 0x54)) <= param_3)) &&
             (ABS(*(float *)(uVar11 + 0x58)) <= param_3))) {
        uVar11 = uVar11 + 0x1c0;
        if (uVar16 <= uVar11) goto code_r0x02427228;
      }
    }
    uStack_b8 = uStack_b8 + 1;
    if (param_11 <= uStack_b8) {
      return;
    }
  } while( true );
}

// ==== void Aska::ArticulatedDynamicsManager::PreprocessBeforeInternalForce<Aska::ArticulatedDynamicsManager>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::ADMJoint*, float, float, unsigned int, unsigned int, bool)
// vaddr 0x2327808 | ghidra 0x2427808 | size 516 | symbol _ZN4Aska26ArticulatedDynamicsManager29PreprocessBeforeInternalForceIS0_EEvPT_PNS_8ADMJointES5_ffjjb | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska26ArticulatedDynamicsManager29PreprocessBeforeInternalForceIS0_EEvPT_PNS_8ADMJointES5_ffjjb
               (undefined8 param_1,undefined8 param_2,long param_3,long param_4,undefined8 param_5,
               undefined4 param_6,undefined4 param_7,uint param_8)

{
  long lVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  uint *puVar9;
  uint uVar10;
  undefined4 uVar11;
  
  void Aska::ArticulatedDynamicsManagerBase::InterpolateRoot<Aska::ArticulatedDynamicsManager>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::ADMJoint*, float, unsigned int, unsigned int)();
  void Aska::ArticulatedDynamicsManagerBase::CollisionSetting<Aska::ArticulatedDynamicsManager>(Aska::ArticulatedDynamicsManager*, unsigned int, unsigned int)(param_3,param_6,param_7);
  uVar5 = _UNK_027dbb38;
  uVar4 = _UNK_027dbb30;
  uVar11 = *(undefined4 *)(param_3 + 0xf4);
  uVar2 = *(uint *)(param_3 + 0xb0);
  uVar8 = (ulong)uVar2;
  puVar9 = *(uint **)(param_3 + 0xa8);
  if (*(float *)(param_3 + 0xf0) <= 0.0) {
    if (0 < (int)uVar2) {
      uVar10 = 0;
      do {
        uVar6 = puVar9[1];
        if (uVar6 != 0) {
          lVar7 = param_4 + (ulong)*puVar9 * 0x1c0;
          do {
            *(undefined8 *)(lVar7 + 0x98) = uVar5;
            *(undefined8 *)(lVar7 + 0x90) = uVar4;
            *(undefined8 *)(lVar7 + 0x20) = *(undefined8 *)(lVar7 + 0x10);
            lVar1 = *(long *)(lVar7 + 0x130) + 0x60;
            if (*(long *)(lVar7 + 0x130) == 0) {
              lVar1 = 0;
            }
            uVar6 = uVar6 - 1;
            *(undefined4 *)(lVar7 + 0x18c) = 0;
            *(undefined1 *)(lVar7 + 0x19f) = 0;
            *(undefined4 *)(lVar7 + 0x1b8) = 0x3f4ccccd;
            *(undefined4 *)(lVar7 + 0x28) = *(undefined4 *)(lVar7 + 0x18);
            *(undefined4 *)(lVar7 + 0x2c) = 0x3f800000;
            *(undefined8 *)(lVar7 + 0x108) = *(undefined8 *)(lVar7 + 0x68);
            *(undefined8 *)(lVar7 + 0x100) = *(undefined8 *)(lVar7 + 0x60);
            Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(lVar7 + 0xb0,lVar7 + 0xf0,lVar7 + 0x100,lVar7 + 0x120,lVar7 + 0x110,
                            lVar1);
            Aska::ADMJoint::ExternalForce(float, float, float, Aska::Vector const*, Aska::ADM_CALC_DATA*, bool)(param_1,param_2,uVar11,lVar7,param_3 + 0x40,lVar7 + 0xb0,param_8 & 1);
            lVar7 = lVar7 + 0x1c0;
          } while (uVar6 != 0);
        }
        uVar10 = uVar10 + 1;
        puVar9 = puVar9 + 2;
      } while (uVar10 != uVar2);
    }
  }
  else if (0 < (int)uVar2) {
    lVar7 = 0;
    do {
      void Aska::ArticulatedDynamicsManager::MatrixPreFixAndMotionBlend<true>(Aska::ADM_CALC_DATA*, Aska::ADMJoint*, unsigned int, float, float, float, Aska::Vector*, bool)(param_1,param_2,uVar11,*(long *)(param_3 + 0xa0) + lVar7,
                      param_4 + (ulong)*puVar9 * 0x1c0,puVar9[1],param_3 + 0x40,param_8 & 1);
      lVar7 = lVar7 + 0xa0;
      uVar8 = uVar8 - 1;
      puVar9 = puVar9 + 2;
    } while (uVar8 != 0);
  }
  lVar7 = Aska::DynamicsManager::GetForceEmitterManager()();
  if ((*(int *)(lVar7 + 0x58) != 0) && (*(int *)(param_3 + 0x88) != 0)) {
    iVar3 = *(int *)(param_3 + 0x8c);
    void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)(param_1,param_3,param_4,*(undefined8 *)(lVar7 + 0x50),*(int *)(lVar7 + 0x58),
                    iVar3);
    *(int *)(param_3 + 0x8c) = iVar3 + 0x56b46fd1;
  }
  return;
}

// ==== void Aska::ArticulatedDynamicsManagerBase::StandardIK<Aska::ArticulatedDynamicsManager, false>(Aska::ArticulatedDynamicsManager*, float, float, int)
// vaddr 0x2327a0c | ghidra 0x2427a0c | size 928 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase10StandardIKINS_26ArticulatedDynamicsManagerELb0EEEvPT_ffi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase10StandardIKINS_26ArticulatedDynamicsManagerELb0EEEvPT_ffi
               (undefined8 param_1,long param_2,undefined4 param_3)

{
  undefined8 *puVar1;
  byte *pbVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  byte bVar6;
  byte *pbVar7;
  long lVar8;
  long lVar9;
  byte *pbVar10;
  int iVar11;
  long lVar12;
  byte *pbVar13;
  long lVar14;
  byte *pbVar15;
  long lVar16;
  byte *pbVar17;
  ulong uVar18;
  int *piVar19;
  byte *pbVar20;
  byte *pbVar21;
  byte *pbVar22;
  byte *pbVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  undefined4 uVar26;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined1 auStack_b0 [64];
  
  uVar3 = *(uint *)(param_2 + 0xb0);
  if (0 < (int)uVar3) {
    uVar26 = *(undefined4 *)(param_2 + 0xf0);
    piVar19 = *(int **)(param_2 + 0xa8);
    uVar18 = 0;
    do {
      iVar11 = piVar19[1];
      lVar9 = *(long *)(param_2 + 0x70);
      lVar16 = *(long *)(param_2 + 0xa0);
      lVar12 = (long)*piVar19;
      pbVar22 = (byte *)(lVar9 + lVar12 * 0x1c0);
      lVar14 = lVar16 + uVar18 * 0xa0;
      pbVar23 = pbVar22 + 0xb0;
      if ((pbVar22[0x19d] >> 5 & 1) != 0) {
        lVar8 = lVar9 + lVar12 * 0x1c0;
        *(undefined8 *)(lVar8 + 0x108) = *(undefined8 *)(lVar8 + 0x78);
        *(undefined8 *)(lVar8 + 0x100) = *(undefined8 *)(lVar8 + 0x70);
      }
      if ((*(char *)(lVar9 + lVar12 * 0x1c0 + 0x198) == '\0') &&
         ((*(byte *)(lVar9 + lVar12 * 0x1c0 + 0x19c) & 1) == 0)) {
        lVar8 = lVar9 + lVar12 * 0x1c0;
        puVar1 = (undefined8 *)(lVar8 + 0x10);
        if (lVar14 == 0) {
          uVar25 = *(undefined8 *)(lVar8 + 0x18);
          uVar24 = *puVar1;
        }
        else {
          Aska::Matrix::InvertLowError(Aska::Matrix*) const(lVar14,auStack_b0);
          Aska::Matrix::ApplyVector(Aska::Vector*, Aska::Vector const*) const(auStack_b0,&uStack_c0,puVar1);
          uVar24 = uStack_c0;
          uVar25 = uStack_b8;
        }
        lVar8 = lVar9 + lVar12 * 0x1c0;
        *(undefined8 *)(lVar8 + 0xf8) = uVar25;
        *(undefined8 *)(lVar8 + 0xf0) = uVar24;
      }
      lVar8 = lVar9 + lVar12 * 0x1c0;
      lVar16 = lVar16 + uVar18 * 0xa0 + 0x60;
      if (lVar14 == 0) {
        lVar16 = 0;
      }
      Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pbVar23,lVar8 + 0xf0,lVar8 + 0x100,lVar8 + 0x120,lVar8 + 0x110,lVar16,lVar14);
      if (iVar11 == 1) {
        bVar6 = pbVar22[0x19c];
        pbVar21 = pbVar22;
      }
      else {
        iVar11 = 1 - iVar11;
        pbVar13 = pbVar22;
        pbVar2 = (byte *)(lVar9 + lVar12 * 0x1c0 + 0x35d);
        pbVar20 = pbVar23;
        do {
          pbVar15 = pbVar2;
          pbVar17 = *(byte **)(pbVar15 + -0xd);
          pbVar21 = pbVar15 + -0x19d;
          pbVar23 = pbVar15 + -0xed;
          pbVar2 = pbVar17 + 0xb0;
          if ((pbVar15[-1] & 1) == 0 && pbVar15[-5] == 0) {
            Aska::Matrix::InvertLowError(Aska::Matrix*) const(pbVar2,auStack_b0);
            Aska::Matrix::ApplyVector(Aska::Vector*, Aska::Vector const*) const(auStack_b0,&uStack_c0,pbVar15 + -0x18d);
            *(undefined8 *)(pbVar15 + -0xa5) = uStack_b8;
            *(undefined8 *)(pbVar15 + -0xad) = uStack_c0;
            bVar6 = *pbVar15;
            pbVar10 = (byte *)0x0;
joined_r0x02427bcc:
            if ((bVar6 >> 5 & 1) == 0) goto code_r0x02427bd0;
code_r0x02427cb4:
            pbVar7 = pbVar22 + 0x2c0;
            *(undefined8 *)(pbVar15 + -0x95) = *(undefined8 *)(pbVar15 + -0x125);
            *(undefined8 *)(pbVar15 + -0x9d) = *(undefined8 *)(pbVar15 + -0x12d);
          }
          else {
            if ((pbVar15[-1] >> 1 & 1) != 0) {
              lVar12 = *(long *)(pbVar17 + 0x130);
              lVar9 = lVar12 + 0x60;
              if (lVar12 == 0) {
                lVar9 = 0;
              }
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pbVar2);
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pbVar23,pbVar15 + -0xad,pbVar15 + -0x9d,pbVar15 + -0x7d,
                              pbVar15 + -0x8d,pbVar17 + 0x110,pbVar2);
              void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x5b4(uVar26,param_1,pbVar17,pbVar2,pbVar21,pbVar23,param_3);
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pbVar2,pbVar17 + 0xf0,pbVar17 + 0x100,pbVar17 + 0x120,pbVar17 + 0x110,
                              lVar9,lVar12);
              if ((pbVar17[0x19c] & 1) == 0) {
                *(undefined4 *)(pbVar17 + 0x10) = *(undefined4 *)(pbVar17 + 0xbc);
                *(undefined4 *)(pbVar17 + 0x14) = *(undefined4 *)(pbVar17 + 0xcc);
                *(undefined4 *)(pbVar17 + 0x18) = *(undefined4 *)(pbVar17 + 0xdc);
                pbVar17[0x1c] = 0;
                pbVar17[0x1d] = 0;
                pbVar17[0x1e] = 0x80;
                pbVar17[0x1f] = 0x3f;
              }
              bVar6 = *pbVar15;
              pbVar10 = pbVar17;
              goto joined_r0x02427bcc;
            }
            pbVar10 = (byte *)0x0;
            if ((*pbVar15 >> 5 & 1) != 0) goto code_r0x02427cb4;
code_r0x02427bd0:
            pbVar7 = pbVar15 + -0x9d;
          }
          pbVar22 = pbVar22 + 0x1c0;
          Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pbVar23,pbVar15 + -0xad,pbVar7,pbVar15 + -0x7d,pbVar15 + -0x8d,
                          pbVar17 + 0x110,pbVar2);
          if ((pbVar10 != pbVar13) && ((pbVar13[0x19c] & 1) == 0)) {
            uVar4 = *(undefined4 *)(pbVar20 + 0x1c);
            uVar5 = *(undefined4 *)(pbVar20 + 0x2c);
            *(undefined4 *)(pbVar13 + 0x10) = *(undefined4 *)(pbVar20 + 0xc);
            *(undefined4 *)(pbVar13 + 0x14) = uVar4;
            *(undefined4 *)(pbVar13 + 0x18) = uVar5;
            pbVar13[0x1c] = 0;
            pbVar13[0x1d] = 0;
            pbVar13[0x1e] = 0x80;
            pbVar13[0x1f] = 0x3f;
          }
          iVar11 = iVar11 + 1;
          pbVar13 = pbVar21;
          pbVar2 = pbVar15 + 0x1c0;
          pbVar20 = pbVar23;
        } while (iVar11 != 0);
        bVar6 = pbVar15[-1];
      }
      if ((bVar6 & 1) == 0) {
        uVar4 = *(undefined4 *)(pbVar23 + 0x1c);
        uVar5 = *(undefined4 *)(pbVar23 + 0x2c);
        *(undefined4 *)(pbVar21 + 0x10) = *(undefined4 *)(pbVar23 + 0xc);
        *(undefined4 *)(pbVar21 + 0x14) = uVar4;
        *(undefined4 *)(pbVar21 + 0x18) = uVar5;
        pbVar21[0x1c] = 0;
        pbVar21[0x1d] = 0;
        pbVar21[0x1e] = 0x80;
        pbVar21[0x1f] = 0x3f;
      }
      uVar18 = uVar18 + 1;
      piVar19 = piVar19 + 2;
    } while (uVar18 != uVar3);
  }
  if (0 < (long)*(short *)(param_2 + 0x98)) {
    lVar9 = *(long *)(param_2 + 0x90);
    uVar18 = lVar9 + *(short *)(param_2 + 0x98);
    if (uVar18 <= lVar9 + 1U) {
      uVar18 = lVar9 + 1;
    }
    memset(lVar9,0,uVar18 - lVar9);
  }
  return;
}

// ==== void Aska::ArticulatedDynamicsManagerBase::CollisionAndConstraint<Aska::ArticulatedDynamicsManager>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::ADMJoint*, unsigned int, unsigned int, float)
// vaddr 0x2327dac | ghidra 0x2427dac | size 2608 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase22CollisionAndConstraintINS_26ArticulatedDynamicsManagerEEEvPT_PNS_8ADMJointES6_jjf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska30ArticulatedDynamicsManagerBase22CollisionAndConstraintINS_26ArticulatedDynamicsManagerEEEvPT_PNS_8ADMJointES6_jjf
               (undefined1 param_1 [16],long param_2,long param_3,long param_4,ulong param_5,
               int param_6)

{
  undefined1 (*pauVar1) [12];
  undefined1 (*pauVar2) [12];
  byte *pbVar3;
  uint uVar4;
  byte bVar5;
  short sVar6;
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  bool bVar14;
  ulong uVar15;
  uint uVar16;
  int iVar17;
  long lVar18;
  undefined4 *puVar19;
  long *plVar20;
  ulong uVar21;
  long lVar22;
  undefined8 *puVar23;
  int iVar24;
  undefined1 (*pauVar25) [16];
  long lVar26;
  long *plVar27;
  undefined1 auVar28 [12];
  undefined1 auVar29 [12];
  undefined8 uVar34;
  undefined1 auVar30 [16];
  undefined1 auVar31 [16];
  undefined1 auVar32 [16];
  undefined1 auVar33 [16];
  float fVar35;
  float fVar39;
  undefined1 auVar36 [16];
  float fVar41;
  undefined1 auVar37 [16];
  undefined1 auVar38 [16];
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  undefined4 uVar46;
  float fVar47;
  float fVar50;
  undefined1 auVar48 [16];
  undefined1 auVar49 [16];
  undefined1 auVar51 [16];
  undefined1 auVar52 [16];
  undefined1 auVar53 [16];
  float fVar54;
  float fVar55;
  float fVar56;
  float fVar57;
  undefined4 uVar58;
  float fVar59;
  float fVar60;
  float fVar61;
  float fVar62;
  float fVar63;
  float fVar64;
  float fVar65;
  float fVar66;
  float fVar67;
  float fVar68;
  float fVar69;
  float fVar70;
  undefined1 auVar71 [16];
  int iStack_634;
  undefined8 auStack_560 [128];
  undefined1 auStack_160 [64];
  undefined8 uStack_120;
  float fStack_118;
  undefined4 uStack_114;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined4 uStack_e0;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  float fStack_c0;
  float fStack_bc;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  float fVar40;
  
  plVar20 = *(long **)(param_2 + 0x130);
  uVar34 = param_1._8_8_;
  if (plVar20 == (long *)0x0) {
    plVar20 = *(long **)
               PTR__ZN4Aska30ArticulatedDynamicsManagerBase22m_pWorldLandConstraintE_02cc3ab0;
    bVar14 = plVar20 == (long *)0x0;
    if ((-param_6 == (int)param_5) && (plVar20 == (long *)0x0)) {
      return;
    }
  }
  else {
    bVar14 = false;
  }
  if ((int)param_5 < 1) {
    param_5 = 0;
  }
  else {
    sVar6 = *(short *)(param_2 + 100);
    lVar18 = 0;
    uVar21 = 0;
    lVar22 = -((long)sVar6 << 0x20);
    do {
      if ((long)uVar21 < (long)sVar6) {
        puVar23 = (undefined8 *)(*(long *)(param_2 + 0x148) + lVar18);
      }
      else {
        puVar23 = (undefined8 *)
                  (PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_pWorldCollisionListE_02cc4750 +
                  (lVar22 >> 0x1d));
      }
      uVar21 = uVar21 + 1;
      lVar22 = lVar22 + 0x100000000;
      *(undefined8 *)((long)auStack_560 + lVar18) = *puVar23;
      lVar18 = lVar18 + 8;
    } while ((param_5 & 0xffffffff) != uVar21);
  }
  lVar18 = *(long *)(param_2 + 0x170);
  if (param_2 + 0x160 != lVar18) {
    param_5 = (ulong)(int)param_5;
    do {
      auStack_560[param_5] = *(undefined8 *)(lVar18 + 0x38);
      lVar18 = *(long *)(lVar18 + 0x10);
      param_5 = param_5 + 1;
    } while (param_2 + 0x160 != lVar18);
  }
  lVar18 = *(long *)(param_2 + 0x90);
  lVar22 = *(long *)(param_2 + 0x150);
  uVar58 = *(undefined4 *)(param_2 + 0xf4);
  sVar6 = *(short *)(param_2 + 0x66);
  iStack_634 = (int)((ulong)(param_4 - param_3) >> 6) * -0x49249249;
  uVar16 = (uint)(byte)*PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98;
  if (*(char *)(param_2 + 0xde) == '\0') {
    uVar16 = 0;
  }
  do {
    iVar17 = (int)param_5;
    if (iVar17 == 0) {
      iVar24 = 0;
    }
    else {
      iVar24 = *(int *)(param_3 + 0x168);
    }
    if (iVar24 * iVar17 == 0) {
      bVar5 = *(byte *)(param_3 + 0x19c);
    }
    else {
      pauVar2 = (undefined1 (*) [12])(param_3 + 0xb0);
      fVar40 = (float)*(undefined8 *)(param_3 + 0xb8);
      fVar42 = (float)((ulong)*(undefined8 *)(param_3 + 0xb8) >> 0x20);
      fVar54 = (float)*(undefined8 *)*pauVar2;
      fVar55 = (float)((ulong)*(undefined8 *)*pauVar2 >> 0x20);
      auVar52 = *(undefined1 (*) [16])(param_3 + 0xc0);
      pauVar1 = (undefined1 (*) [12])(param_3 + 0xd0);
      fVar69 = (float)*(undefined8 *)(param_3 + 0xd8);
      fVar70 = (float)((ulong)*(undefined8 *)(param_3 + 0xd8) >> 0x20);
      fVar67 = (float)*(undefined8 *)*pauVar1;
      fVar68 = (float)((ulong)*(undefined8 *)*pauVar1 >> 0x20);
      pauVar25 = *(undefined1 (**) [16])(param_3 + 0x160);
      pbVar3 = (byte *)(param_3 + 0x19c);
      auVar71._12_4_ = fVar42;
      auVar71._0_12_ = *pauVar2;
      auVar48._12_4_ = fVar42;
      auVar48._0_12_ = *pauVar2;
      auVar71 = NEON_ext(auVar71,auVar48,8,1);
      fVar66 = auVar52._4_4_;
      fVar65 = auVar52._0_4_;
      fVar47 = auVar52._8_4_;
      fVar43 = auVar52._12_4_;
      fVar56 = fVar54 * fVar66 - fVar55 * fVar65;
      fVar57 = fVar54 * fVar66 - fVar55 * fVar65;
      fVar60 = fVar54 * fVar47 - fVar40 * fVar65;
      fVar61 = fVar54 * fVar47 - fVar40 * fVar65;
      fVar62 = fVar54 * fVar43 - fVar42 * fVar65;
      fVar63 = fVar55 * fVar47 - fVar40 * fVar66;
      fVar64 = fVar55 * fVar47 - fVar40 * fVar66;
      fVar59 = fVar55 * fVar43 - fVar42 * fVar66;
      fVar50 = fVar40 * fVar43 - fVar42 * fVar47;
      fVar42 = (fVar55 * fVar47 - fVar40 * fVar66) * fVar67 +
               ((fVar54 * fVar66 - fVar55 * fVar65) * fVar69 -
               (fVar54 * fVar47 - fVar40 * fVar65) * fVar68);
      fVar43 = (fVar55 * fVar47 - fVar40 * fVar66) * fVar67 +
               ((fVar54 * fVar66 - fVar55 * fVar65) * fVar69 -
               (fVar54 * fVar47 - fVar40 * fVar65) * fVar68);
      fVar44 = fVar63 * fVar67 + (fVar56 * fVar69 - fVar60 * fVar68);
      fVar45 = fVar64 * fVar67 + (fVar57 * fVar69 - fVar61 * fVar68);
      auVar30._4_4_ = fVar43;
      auVar30._0_4_ = fVar42;
      auVar30._8_4_ = fVar44;
      auVar30._12_4_ = fVar45;
      auVar30 = NEON_frecpe(auVar30,4);
      auVar36._4_4_ = fVar43;
      auVar36._0_4_ = fVar42;
      auVar36._8_4_ = fVar44;
      auVar36._12_4_ = fVar45;
      auVar36 = NEON_frecps(auVar30,auVar36,4);
      auVar31._0_4_ = auVar30._0_4_ * auVar36._0_4_;
      auVar31._4_4_ = auVar30._4_4_ * auVar36._4_4_;
      auVar31._8_4_ = auVar30._8_4_ * auVar36._8_4_;
      auVar31._12_4_ = auVar30._12_4_ * auVar36._12_4_;
      auVar49._4_4_ = fVar43;
      auVar49._0_4_ = fVar42;
      auVar49._8_4_ = fVar44;
      auVar49._12_4_ = fVar45;
      auVar30 = NEON_frecps(auVar31,auVar49,4);
      fVar42 = auVar31._0_4_ * auVar30._0_4_;
      fVar43 = auVar31._4_4_ * auVar30._4_4_;
      fVar44 = auVar31._8_4_ * auVar30._8_4_;
      fVar45 = auVar31._12_4_ * auVar30._12_4_;
      auVar36 = NEON_ext(auVar52,auVar52,8,1);
      auVar52._12_4_ = fVar70;
      auVar52._0_12_ = *pauVar1;
      auVar11._12_4_ = fVar70;
      auVar11._0_12_ = *pauVar1;
      auVar30 = NEON_ext(auVar52,auVar11,8,1);
      fVar35 = fVar42 * (fVar66 * fVar69 - fVar47 * fVar68);
      fVar39 = fVar43 * (fVar40 * fVar68 - fVar55 * fVar69);
      fVar63 = fVar44 * fVar63;
      fVar41 = fVar45 * ((fVar59 * fVar69 - fVar50 * fVar68) - fVar64 * fVar70);
      fVar64 = fVar42 * (fVar47 * fVar67 - fVar65 * fVar69);
      fVar40 = fVar43 * (fVar54 * fVar69 - fVar40 * fVar67);
      auVar37._0_8_ = CONCAT44(fVar40,fVar64);
      auVar37._8_4_ = fVar44 * -fVar60;
      auVar37._12_4_ = fVar45 * (fVar61 * fVar70 + (fVar50 * fVar67 - fVar62 * fVar69));
      fVar42 = fVar42 * (fVar65 * fVar68 - fVar66 * fVar67);
      fVar43 = fVar43 * (fVar55 * fVar67 - fVar54 * fVar68);
      fVar44 = fVar44 * fVar56;
      fVar45 = fVar45 * ((fVar62 * fVar68 - fVar59 * fVar67) - fVar57 * fVar70);
      do {
        bVar5 = pauVar25[2][0];
        lVar26 = *(long *)(pauVar25[4] + 8);
        if ((bVar5 & 1) != 0) {
          uStack_e0 = *(undefined4 *)(pauVar25[2] + 4);
          if ((bVar5 >> 3 & 1) == 0) {
            if (0 < iVar17) {
              puVar23 = auStack_560;
              uVar21 = param_5 & 0xffffffff;
              do {
                plVar27 = (long *)*puVar23;
                if ((*(long *)(plVar27[10] + 0x10) != param_2) ||
                   (((*pbVar3 & 1) == 0 && ((*(byte *)(lVar26 + 0x19c) & 1) == 0)))) {
                  auVar49 = *(undefined1 (*) [16])(param_3 + 0x10);
                  auVar28 = auVar49._0_12_;
                  fVar50 = *(float *)(lVar26 + 0x10);
                  fVar56 = *(float *)(lVar26 + 0x14);
                  fVar57 = *(float *)(lVar26 + 0x18);
                  if ((bVar5 >> 2 & 1) != 0) {
                    uVar46 = (undefined4)((ulong)*(undefined8 *)(*pauVar25 + 8) >> 0x20);
                    fVar60 = (float)*(undefined8 *)*pauVar25;
                    fVar62 = (float)((ulong)*(undefined8 *)*pauVar25 >> 0x20);
                    auVar7._12_4_ = uVar46;
                    auVar7._0_12_ = *(undefined1 (*) [12])*pauVar25;
                    auVar8._12_4_ = uVar46;
                    auVar8._0_12_ = *(undefined1 (*) [12])*pauVar25;
                    auVar48 = NEON_ext(auVar7,auVar8,8,1);
                    fVar47 = auVar48._0_4_;
                    fVar59 = fVar54 * fVar60 + auVar71._0_4_ * fVar47 + fVar55 * fVar62 + 0.0;
                    fVar61 = fVar65 * fVar60 + auVar36._0_4_ * fVar47 + fVar66 * fVar62 + 0.0;
                    fVar60 = fVar67 * fVar60 + auVar30._0_4_ * fVar47 + fVar68 * fVar62 + 0.0;
                    auVar28._0_4_ = auVar49._0_4_ + fVar59;
                    auVar28._4_4_ = auVar49._4_4_ + fVar61;
                    auVar28._8_4_ = auVar49._8_4_ + fVar60;
                    fVar50 = fVar50 + fVar59;
                    fVar56 = fVar56 + fVar61;
                    fVar57 = fVar57 + fVar60;
                  }
                  fVar50 = fVar50 - auVar28._0_4_;
                  fVar56 = fVar56 - auVar28._4_4_;
                  fStack_118 = auVar28._8_4_;
                  fVar57 = fVar57 - fStack_118;
                  if ((bVar5 >> 1 & 1) == 0) {
                    uStack_120 = auVar28._0_8_;
                    uStack_114 = 0x3f800000;
                    uStack_110 = CONCAT44(fVar56,fVar50);
                    uStack_108 = CONCAT44(0x3f800000,fVar57);
                    uVar15 = (**(code **)(*plVar27 + 0x80))
                                       (plVar27,auStack_160,bVar5 >> 4 & 1,&uStack_90,&uStack_a0,
                                        &uStack_b0);
                    if ((uVar15 & 1) != 0) {
                      puVar19 = (undefined4 *)plVar27[10];
                      fVar59 = (float)uStack_a0;
code_r0x0242826c:
                      auVar51._8_8_ = uVar34;
                      auVar51._0_8_ = param_1._0_8_;
                      void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x1230(fVar59,(float)uStack_b0,*puVar19,puVar19[1],uVar58,auVar51,
                                      pauVar25,param_3,lVar26,&uStack_90);
                      if ((ulong)*(byte *)(param_3 + 0x19e) != 0xff) {
                        *(undefined1 *)(lVar18 + (ulong)*(byte *)(param_3 + 0x19e)) = 1;
                      }
                      if ((ulong)*(byte *)(lVar26 + 0x19e) != 0xff) {
                        *(undefined1 *)(lVar18 + (ulong)*(byte *)(lVar26 + 0x19e)) = 1;
                      }
                      if (*(long *)(plVar27[10] + 0x10) == param_2) {
                        *(byte *)(param_3 + 0x19f) = *(byte *)(param_3 + 0x19f) | 1;
                        *(byte *)(lVar26 + 0x19f) = *(byte *)(lVar26 + 0x19f) | 1;
                      }
                    }
                  }
                  else {
                    fVar59 = *(float *)(pauVar25[3] + 8);
                    fVar60 = *(float *)(pauVar25[3] + 0xc) - fVar59;
                    fStack_118 = fStack_118 + fVar57 * fVar59;
                    auVar49 = NEON_fmov(0x3f800000,4);
                    fVar61 = fVar60 + auVar49._0_4_;
                    uStack_120 = CONCAT44(auVar28._4_4_ + fVar56 * fVar59,
                                          auVar28._0_4_ + fVar50 * fVar59);
                    uStack_110 = CONCAT44(fVar56 * (fVar60 + auVar49._4_4_),fVar50 * fVar61);
                    uStack_114 = 0x3f800000;
                    uStack_108 = CONCAT44(0x3f800000,fVar57 * (fVar60 + auVar49._8_4_));
                    uVar15 = (**(code **)(*plVar27 + 0x80))
                                       (plVar27,auStack_160,bVar5 >> 4 & 1,&uStack_90,&uStack_a0,
                                        &uStack_b0);
                    if ((uVar15 & 1) != 0) {
                      fVar59 = fVar59 + (1.0 - fVar61) * (float)uStack_a0;
                      uStack_a0 = CONCAT44(uStack_a0._4_4_,fVar59);
                      puVar19 = (undefined4 *)plVar27[10];
                      goto code_r0x0242826c;
                    }
                  }
                }
                uVar21 = uVar21 - 1;
                puVar23 = puVar23 + 1;
              } while (uVar21 != 0);
            }
          }
          else if (0 < iVar17) {
            puVar23 = auStack_560;
            uVar21 = param_5 & 0xffffffff;
            do {
              plVar27 = (long *)*puVar23;
              uStack_88 = CONCAT44(fVar41,fVar63);
              uStack_90 = CONCAT44(fVar39,fVar35);
              uStack_98 = auVar37._8_8_;
              uStack_a0 = auVar37._0_8_;
              uStack_b0 = CONCAT44(fVar43,fVar42);
              auVar12._8_4_ = fVar44;
              auVar12._0_8_ = uStack_b0;
              auVar12._12_4_ = fVar45;
              uStack_a8 = auVar12._8_8_;
              if ((*(long *)(plVar27[10] + 0x10) != param_2) ||
                 (((*pbVar3 & 1) == 0 && ((*(byte *)(lVar26 + 0x19c) & 1) == 0)))) {
                fVar50 = *(float *)(lVar26 + 0x10);
                fVar56 = *(float *)(lVar26 + 0x14);
                fVar57 = *(float *)(lVar26 + 0x18);
                fVar59 = *(float *)(lVar26 + 0x1c);
                auVar38._0_4_ = fVar35 * fVar50;
                auVar38._4_4_ = fVar39 * fVar56;
                auVar38._8_4_ = fVar63 * fVar57;
                auVar38._12_4_ = fVar41 * fVar59;
                fVar60 = fVar64 * fVar50;
                fVar61 = fVar40 * fVar56;
                auVar32._0_4_ = fVar42 * fVar50;
                auVar32._4_4_ = fVar43 * fVar56;
                auVar32._8_4_ = fVar44 * fVar57;
                auVar32._12_4_ = fVar45 * fVar59;
                auVar49 = NEON_ext(auVar38,auVar38,8,1);
                auVar9._4_4_ = fVar61;
                auVar9._0_4_ = fVar60;
                auVar9._8_4_ = auVar37._8_4_ * fVar57;
                auVar9._12_4_ = auVar37._12_4_ * fVar59;
                auVar10._4_4_ = fVar61;
                auVar10._0_4_ = fVar60;
                auVar10._8_4_ = auVar37._8_4_ * fVar57;
                auVar10._12_4_ = auVar37._12_4_ * fVar59;
                auVar48 = NEON_ext(auVar9,auVar10,8,1);
                auVar52 = NEON_ext(auVar32,auVar32,8,1);
                fVar50 = auVar49._0_4_ + auVar38._0_4_ + auVar49._4_4_ + auVar38._4_4_;
                fVar57 = auVar48._0_4_ + fVar60 + auVar48._4_4_ + fVar61;
                auVar33._4_4_ = fVar57;
                auVar33._0_4_ = fVar50;
                fVar56 = auVar52._0_4_ + auVar32._0_4_ + auVar52._4_4_ + auVar32._4_4_;
                auVar33._12_4_ = 0x3f800000;
                auVar33._8_4_ = fVar56;
                auVar29 = auVar33._0_12_;
                if ((bVar5 >> 2 & 1) == 0) {
                  auVar28 = _UNK_027dbb30;
                  if ((bVar5 >> 1 & 1) == 0) goto code_r0x02428400;
code_r0x02428388:
                  fVar56 = *(float *)(pauVar25[3] + 8);
                  uStack_120 = CONCAT44(auVar28._4_4_ + auVar29._4_4_ * fVar56,
                                        auVar28._0_4_ + auVar29._0_4_ * fVar56);
                  fStack_118 = auVar28._8_4_ + auVar29._8_4_ * fVar56;
                  fVar56 = *(float *)(pauVar25[3] + 0xc) - fVar56;
                  auVar49 = NEON_fmov(0x3f800000,4);
                  fVar50 = auVar29._8_4_ * (fVar56 + auVar49._8_4_);
                  uStack_110 = CONCAT44(auVar29._4_4_ * (fVar56 + auVar49._4_4_),
                                        auVar29._0_4_ * (fVar56 + auVar49._0_4_));
                }
                else {
                  auVar49 = *pauVar25;
                  auVar28 = auVar49._0_12_;
                  auVar29._0_4_ = fVar50 + auVar49._0_4_;
                  auVar29._4_4_ = fVar57 + auVar49._4_4_;
                  auVar29._8_4_ = fVar56 + auVar49._8_4_;
                  if ((bVar5 >> 1 & 1) != 0) goto code_r0x02428388;
code_r0x02428400:
                  uStack_120 = auVar28._0_8_;
                  fStack_118 = auVar28._8_4_;
                  uStack_110 = auVar29._0_8_;
                  fVar50 = auVar29._8_4_;
                }
                uStack_108 = CONCAT44(0x3f800000,fVar50);
                uStack_114 = 0x3f800000;
                uVar15 = (**(code **)(*plVar27 + 0x88))
                                   (plVar27,&uStack_90,&uStack_a0,&uStack_b0,auStack_160,
                                    bVar5 >> 4 & 1,pauVar25 + 1,&fStack_c0,&uStack_c4,&uStack_c8);
                if ((uVar15 & 1) != 0) {
                  auVar13._4_4_ = fStack_bc;
                  auVar13._0_4_ = fStack_c0;
                  auVar13._8_8_ = uStack_b8;
                  auVar49 = NEON_ext(auVar13,auVar13,8,1);
                  fVar59 = fVar65 * fStack_c0;
                  fVar50 = fVar67 * fStack_c0;
                  fVar56 = fVar68 * fStack_bc;
                  fVar57 = auVar49._0_4_;
                  fStack_c0 = fVar54 * fStack_c0 + auVar71._0_4_ * fVar57 + fVar55 * fStack_bc + 0.0
                  ;
                  fStack_bc = fVar59 + auVar36._0_4_ * fVar57 + fVar66 * fStack_bc + 0.0;
                  uStack_b8 = CONCAT44(0x3f800000,fVar50 + auVar30._0_4_ * fVar57 + fVar56 + 0.0);
                  auVar53._8_8_ = uVar34;
                  auVar53._0_8_ = param_1._0_8_;
                  void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x1230(uStack_c4,uStack_c8,*(undefined4 *)plVar27[10],
                                  ((undefined4 *)plVar27[10])[1],uVar58,auVar53,pauVar25,param_3,
                                  lVar26,&fStack_c0);
                  if ((ulong)*(byte *)(param_3 + 0x19e) != 0xff) {
                    *(undefined1 *)(lVar18 + (ulong)*(byte *)(param_3 + 0x19e)) = 1;
                  }
                  if ((ulong)*(byte *)(lVar26 + 0x19e) != 0xff) {
                    *(undefined1 *)(lVar18 + (ulong)*(byte *)(lVar26 + 0x19e)) = 1;
                  }
                  if (*(long *)(plVar27[10] + 0x10) == param_2) {
                    *(byte *)(param_3 + 0x19f) = *(byte *)(param_3 + 0x19f) | 1;
                    *(byte *)(lVar26 + 0x19f) = *(byte *)(lVar26 + 0x19f) | 1;
                  }
                }
              }
              uVar21 = uVar21 - 1;
              puVar23 = puVar23 + 1;
            } while (uVar21 != 0);
          }
        }
        if ((*(char *)(param_3 + 0x19f) != '\0') || (*(char *)(lVar26 + 0x19f) != '\0')) {
          if (*(long *)(lVar26 + 400) == *(long *)pauVar25[4]) {
            *(byte *)(lVar26 + 0x19f) = *(byte *)(lVar26 + 0x19f) | 2;
          }
          if (*(long *)(param_3 + 400) == *(long *)(pauVar25[4] + 8)) {
            *(byte *)(param_3 + 0x19f) = *(byte *)(param_3 + 0x19f) | 2;
          }
          void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x1d0(*(undefined4 *)(pauVar25[2] + 8),*(undefined4 *)(pauVar25[3] + 4),
                          param_1._0_4_,pauVar25[2][1],param_3,lVar26);
        }
        iVar24 = iVar24 + -1;
        pauVar25 = pauVar25 + 5;
      } while (iVar24 != 0);
      bVar5 = *pbVar3;
    }
    if ((bVar5 & 1) == 0) {
      if (((sVar6 != 0) && ((*(byte *)(param_3 + 0x19d) >> 3 & 1) != 0)) &&
         (uVar4 = *(uint *)(param_3 + 0x158), uVar4 != 0)) {
        uVar21 = 0;
        do {
          plVar27 = *(long **)(lVar22 + (ulong)*(byte *)(*(long *)(param_3 + 0x150) + uVar21) * 8);
          if ((plVar27 != (long *)0x0) &&
             (uVar15 = (**(code **)(*plVar27 + 0x98))(plVar27,param_3 + 0x10,&uStack_a0),
             (uVar15 & 1) != 0)) {
            *(undefined8 *)(param_3 + 0x18) = uStack_98;
            *(undefined8 *)(param_3 + 0x10) = uStack_a0;
            *(float *)(param_3 + 0x18c) = *(float *)(param_3 + 0x18c) + *(float *)plVar27[10];
            if ((ulong)*(byte *)(param_3 + 0x19e) != 0xff) {
              *(undefined1 *)(lVar18 + (ulong)*(byte *)(param_3 + 0x19e)) = 1;
            }
            if (*(long *)(plVar27[10] + 0x10) == param_2) {
              *(byte *)(param_3 + 0x19f) = *(byte *)(param_3 + 0x19f) | 1;
            }
          }
          uVar21 = uVar21 + 1;
        } while (uVar4 != uVar21);
      }
      if (uVar16 != 0) {
        uVar21 = (ulong)uVar16;
        plVar27 = (long *)
                  PTR__ZN4Aska30ArticulatedDynamicsManagerBase22m_pWorldConstraintListE_02cbc740;
        do {
          uVar15 = (**(code **)(*(long *)*plVar27 + 0x98))
                             ((long *)*plVar27,param_3 + 0x10,&uStack_a0);
          if ((uVar15 & 1) != 0) {
            *(undefined8 *)(param_3 + 0x18) = uStack_98;
            *(undefined8 *)(param_3 + 0x10) = uStack_a0;
            *(float *)(param_3 + 0x18c) =
                 *(float *)(param_3 + 0x18c) + **(float **)(*plVar27 + 0x50);
            if ((ulong)*(byte *)(param_3 + 0x19e) != 0xff) {
              *(undefined1 *)(lVar18 + (ulong)*(byte *)(param_3 + 0x19e)) = 1;
            }
          }
          uVar21 = uVar21 - 1;
          plVar27 = plVar27 + 1;
        } while (uVar21 != 0);
      }
      if ((!bVar14) && ((*(byte *)(param_3 + 0x19d) >> 4 & 1) != 0)) {
        uStack_90 = CONCAT44(*(float *)(param_3 + 0x14) - *(float *)(param_3 + 0x188),
                             *(undefined4 *)(param_3 + 0x10));
        uStack_88 = CONCAT44(0x3f800000,*(undefined4 *)(param_3 + 0x18));
        uVar21 = (**(code **)(*plVar20 + 0x18))(plVar20,&uStack_90,&uStack_b0,&fStack_c0,0);
        if ((uVar21 & 1) != 0) {
          *(float *)(param_3 + 0x14) = (float)uStack_b0 + *(float *)(param_3 + 0x188);
          *(float *)(param_3 + 0x18c) = *(float *)(param_3 + 0x18c) + fStack_c0;
          if ((ulong)*(byte *)(param_3 + 0x19e) != 0xff) {
            *(undefined1 *)(lVar18 + (ulong)*(byte *)(param_3 + 0x19e)) = 1;
          }
        }
      }
    }
    param_3 = param_3 + 0x1c0;
    iStack_634 = iStack_634 + -1;
    if (iStack_634 == 0) {
      return;
    }
  } while( true );
}

// ==== void Aska::ArticulatedDynamicsManagerBase::StandardIK<Aska::ArticulatedDynamicsManager, true>(Aska::ArticulatedDynamicsManager*, float, float, int)
// vaddr 0x23287dc | ghidra 0x24287dc | size 1052 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase10StandardIKINS_26ArticulatedDynamicsManagerELb1EEEvPT_ffi | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska30ArticulatedDynamicsManagerBase10StandardIKINS_26ArticulatedDynamicsManagerELb1EEEvPT_ffi
               (undefined8 param_1,undefined8 param_2,long param_3,undefined4 param_4)

{
  undefined8 *puVar1;
  uint uVar2;
  float fVar3;
  float fVar4;
  char cVar5;
  byte bVar6;
  float fVar7;
  float fVar8;
  float *pfVar9;
  float *pfVar10;
  long lVar11;
  ulong uVar12;
  int *piVar13;
  float *pfVar14;
  long lVar15;
  float *pfVar16;
  long lVar17;
  float *pfVar18;
  int iVar19;
  long lVar20;
  float *pfVar21;
  float *pfVar22;
  long lVar23;
  float *pfVar24;
  float *pfVar25;
  float *pfVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  undefined4 uVar29;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined1 auStack_d0 [64];
  
  fVar8 = _UNK_0286c774;
  fVar7 = _UNK_02807bf4;
  uVar2 = *(uint *)(param_3 + 0xb0);
  if (0 < (int)uVar2) {
    uVar12 = 0;
    uVar29 = *(undefined4 *)(param_3 + 0xf0);
    piVar13 = *(int **)(param_3 + 0xa8);
    do {
      lVar17 = (long)*piVar13;
      lVar15 = *(long *)(param_3 + 0x70);
      lVar23 = *(long *)(param_3 + 0xa0);
      iVar19 = piVar13[1];
      pfVar26 = (float *)(lVar15 + lVar17 * 0x1c0);
      cVar5 = *(char *)(param_3 + 0xdc);
      lVar20 = lVar23 + uVar12 * 0xa0;
      pfVar21 = pfVar26 + 0x2c;
      if ((*(byte *)((long)pfVar26 + 0x19d) >> 5 & 1) != 0) {
        lVar11 = lVar15 + lVar17 * 0x1c0;
        *(undefined8 *)(lVar11 + 0x108) = *(undefined8 *)(lVar11 + 0x78);
        *(undefined8 *)(lVar11 + 0x100) = *(undefined8 *)(lVar11 + 0x70);
      }
      if ((*(char *)(lVar15 + lVar17 * 0x1c0 + 0x198) == '\0') &&
         ((*(byte *)(lVar15 + lVar17 * 0x1c0 + 0x19c) & 1) == 0)) {
        lVar11 = lVar15 + lVar17 * 0x1c0;
        puVar1 = (undefined8 *)(lVar11 + 0x10);
        if (lVar20 == 0) {
          uVar28 = *(undefined8 *)(lVar11 + 0x18);
          uVar27 = *puVar1;
        }
        else {
          Aska::Matrix::InvertLowError(Aska::Matrix*) const(lVar20,auStack_d0);
          Aska::Matrix::ApplyVector(Aska::Vector*, Aska::Vector const*) const(auStack_d0,&uStack_e0,puVar1);
          uVar27 = uStack_e0;
          uVar28 = uStack_d8;
        }
        lVar11 = lVar15 + lVar17 * 0x1c0;
        *(undefined8 *)(lVar11 + 0xf8) = uVar28;
        *(undefined8 *)(lVar11 + 0xf0) = uVar27;
      }
      lVar11 = lVar15 + lVar17 * 0x1c0;
      lVar23 = lVar23 + uVar12 * 0xa0 + 0x60;
      if (lVar20 == 0) {
        lVar23 = 0;
      }
      Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar21,lVar11 + 0xf0,lVar11 + 0x100,lVar11 + 0x120,lVar11 + 0x110,lVar23,
                      lVar20);
      if (iVar19 == 1) {
        bVar6 = *(byte *)(pfVar26 + 0x67);
        pfVar14 = pfVar26;
      }
      else {
        iVar19 = 1 - iVar19;
        pfVar9 = (float *)(lVar15 + lVar17 * 0x1c0 + 0x378);
        pfVar22 = pfVar26;
        pfVar24 = pfVar21;
        do {
          pfVar18 = pfVar9;
          pfVar25 = *(float **)(pfVar18 + -10);
          pfVar14 = pfVar18 + -0x6e;
          lVar15 = *(long *)(pfVar25 + 0x4c);
          pfVar9 = pfVar25 + 0x2c;
          if ((*(byte *)((long)pfVar18 + -0x19) >> 1 & 1) != 0) {
            fVar3 = *pfVar18 * fVar7;
            if (*pfVar18 * fVar7 <= fVar8) {
              fVar3 = fVar8;
            }
            *pfVar18 = fVar3;
          }
          pfVar21 = pfVar18 + -0x42;
          if ((*(byte *)(pfVar18 + -7) & 1) == 0 && *(char *)(pfVar18 + -8) == '\0') {
            Aska::Matrix::InvertLowError(Aska::Matrix*) const(pfVar9,auStack_d0);
            Aska::Matrix::ApplyVector(Aska::Vector*, Aska::Vector const*) const(auStack_d0,&uStack_e0,pfVar18 + -0x6a);
            *(undefined8 *)(pfVar18 + -0x30) = uStack_d8;
            *(undefined8 *)(pfVar18 + -0x32) = uStack_e0;
            bVar6 = *(byte *)((long)pfVar18 + -0x1b);
            pfVar16 = (float *)0x0;
joined_r0x024289f8:
            if ((bVar6 >> 5 & 1) == 0) goto code_r0x024289fc;
code_r0x02428af4:
            pfVar10 = pfVar26 + 0xb0;
            *(undefined8 *)(pfVar18 + -0x2c) = *(undefined8 *)(pfVar18 + -0x50);
            *(undefined8 *)(pfVar18 + -0x2e) = *(undefined8 *)(pfVar18 + -0x52);
          }
          else {
            if ((*(byte *)(pfVar18 + -7) >> 1 & 1) != 0) {
              lVar17 = lVar15 + 0x60;
              if (lVar15 == 0) {
                lVar17 = 0;
              }
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar9);
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar21,pfVar18 + -0x32,pfVar18 + -0x2e,pfVar18 + -0x26,
                              pfVar18 + -0x2a,pfVar25 + 0x44,pfVar9);
              void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x5b4(uVar29,param_1,pfVar25,pfVar9,pfVar14,pfVar21,param_4);
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar9,pfVar25 + 0x3c,pfVar25 + 0x40,pfVar25 + 0x48,pfVar25 + 0x44,
                              lVar17,lVar15);
              if (((uint)pfVar25[0x67] & 1) == 0) {
                pfVar25[4] = pfVar25[0x2f];
                pfVar25[5] = pfVar25[0x33];
                pfVar25[6] = pfVar25[0x37];
                pfVar25[7] = 1.0;
              }
              void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x14c0(param_2,pfVar25,pfVar9,cVar5 != '\0');
              bVar6 = *(byte *)((long)pfVar18 + -0x1b);
              pfVar16 = pfVar25;
              goto joined_r0x024289f8;
            }
            pfVar16 = (float *)0x0;
            if ((*(byte *)((long)pfVar18 + -0x1b) >> 5 & 1) != 0) goto code_r0x02428af4;
code_r0x024289fc:
            pfVar10 = pfVar18 + -0x2e;
          }
          pfVar26 = pfVar26 + 0x70;
          Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar21,pfVar18 + -0x32,pfVar10,pfVar18 + -0x26,pfVar18 + -0x2a,
                          pfVar25 + 0x44,pfVar9);
          if (pfVar16 != pfVar22) {
            if (((uint)pfVar22[0x67] & 1) == 0) {
              fVar3 = pfVar24[7];
              fVar4 = pfVar24[0xb];
              pfVar22[4] = pfVar24[3];
              pfVar22[5] = fVar3;
              pfVar22[6] = fVar4;
              pfVar22[7] = 1.0;
            }
            void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x14c0(param_2,pfVar22,pfVar24,cVar5 != '\0');
          }
          iVar19 = iVar19 + 1;
          pfVar9 = pfVar18 + 0x70;
          pfVar22 = pfVar14;
          pfVar24 = pfVar21;
        } while (iVar19 != 0);
        bVar6 = *(byte *)(pfVar18 + -7);
      }
      if ((bVar6 & 1) == 0) {
        fVar3 = pfVar21[7];
        fVar4 = pfVar21[0xb];
        pfVar14[4] = pfVar21[3];
        pfVar14[5] = fVar3;
        pfVar14[6] = fVar4;
        pfVar14[7] = 1.0;
      }
      void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x14c0(param_2,pfVar14,pfVar21,cVar5 != '\0');
      uVar12 = uVar12 + 1;
      piVar13 = piVar13 + 2;
    } while (uVar12 != uVar2);
  }
  return;
}

// ==== void Aska::ArticulatedDynamicsManagerBase::Finalize<Aska::ArticulatedDynamicsManager>(Aska::ArticulatedDynamicsManager*, float, float, int)
// vaddr 0x2328bf8 | ghidra 0x2428bf8 | size 1188 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase8FinalizeINS_26ArticulatedDynamicsManagerEEEvPT_ffi | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska30ArticulatedDynamicsManagerBase8FinalizeINS_26ArticulatedDynamicsManagerEEEvPT_ffi
               (undefined1 param_1 [16],undefined1 param_2 [16],long param_3)

{
  undefined8 *puVar1;
  float *pfVar2;
  uint uVar3;
  float fVar4;
  char cVar5;
  byte bVar6;
  undefined8 uVar7;
  float fVar8;
  float fVar9;
  float *pfVar10;
  float *pfVar11;
  long lVar12;
  float *pfVar13;
  int iVar14;
  long lVar15;
  float *pfVar16;
  float *pfVar17;
  long lVar18;
  long lVar19;
  float *pfVar20;
  long lVar21;
  ulong uVar22;
  int *piVar23;
  float *pfVar24;
  float fVar25;
  float fVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  
  fVar9 = _UNK_0286c774;
  fVar8 = _UNK_02807bf4;
  uVar3 = *(uint *)(param_3 + 0xb0);
  uVar7 = param_2._0_8_;
  if (0 < (int)uVar3) {
    piVar23 = *(int **)(param_3 + 0xa8);
    fVar25 = param_2._0_4_ * _UNK_029e2c84 * 0.5;
    uVar22 = 0;
    if (fVar25 <= 1.0) {
      fVar25 = 1.0;
    }
    do {
      iVar14 = piVar23[1];
      lVar18 = *(long *)(param_3 + 0x70);
      cVar5 = *(char *)(param_3 + 0xdc);
      lVar19 = (long)*piVar23;
      pfVar13 = (float *)(lVar18 + lVar19 * 0x1c0);
      pfVar17 = pfVar13 + 0x2c;
      if (*(char *)(*(long *)(param_3 + 0x90) + (ulong)*(byte *)((long)pfVar13 + 0x19e)) == '\0') {
        if (iVar14 != 1) {
          iVar14 = 1 - iVar14;
          pfVar16 = (float *)(lVar18 + lVar19 * 0x1c0 + 0x378);
          pfVar10 = pfVar13;
          pfVar11 = pfVar17;
          do {
            pfVar13 = pfVar16 + -0x6e;
            pfVar17 = pfVar16 + -0x42;
            if ((*(byte *)((long)pfVar16 + -0x19) >> 1 & 1) != 0) {
              fVar26 = *(float *)(*(long *)(pfVar16 + -10) + 0x1b8) * fVar8;
              if (fVar26 <= fVar9) {
                fVar26 = fVar9;
              }
              *pfVar16 = fVar26;
            }
            if (pfVar10 != (float *)0x0) {
              void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x14c0(uVar7,pfVar10,pfVar11,cVar5 != '\0');
            }
            iVar14 = iVar14 + 1;
            pfVar16 = pfVar16 + 0x70;
            pfVar10 = pfVar13;
            pfVar11 = pfVar17;
          } while (iVar14 != 0);
        }
        void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x14c0(uVar7,pfVar13,pfVar17,cVar5 != '\0');
      }
      else {
        lVar21 = *(long *)(param_3 + 0xa0);
        lVar15 = lVar21 + uVar22 * 0xa0;
        if ((*(char *)(lVar18 + lVar19 * 0x1c0 + 0x198) == '\0') &&
           ((*(byte *)(lVar18 + lVar19 * 0x1c0 + 0x19c) & 1) == 0)) {
          lVar12 = lVar18 + lVar19 * 0x1c0;
          puVar1 = (undefined8 *)(lVar12 + 0x10);
          if (lVar15 == 0) {
            uVar28 = *(undefined8 *)(lVar12 + 0x18);
            uVar27 = *puVar1;
          }
          else {
            Aska::Matrix::InvertLowError(Aska::Matrix*) const(lVar15,&uStack_c0);
            Aska::Matrix::ApplyVector(Aska::Vector*, Aska::Vector const*) const(&uStack_c0,&uStack_d0,puVar1);
            uVar27 = uStack_d0;
            uVar28 = uStack_c8;
          }
          lVar12 = lVar18 + lVar19 * 0x1c0;
          *(undefined8 *)(lVar12 + 0xf8) = uVar28;
          *(undefined8 *)(lVar12 + 0xf0) = uVar27;
        }
        lVar12 = lVar18 + lVar19 * 0x1c0;
        lVar21 = lVar21 + uVar22 * 0xa0 + 0x60;
        if (lVar15 == 0) {
          lVar21 = 0;
        }
        Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar17,lVar12 + 0xf0,lVar12 + 0x100,lVar12 + 0x120,lVar12 + 0x110,lVar21,
                        lVar15);
        if (iVar14 == 1) {
          bVar6 = *(byte *)(pfVar13 + 0x67);
        }
        else {
          iVar14 = 1 - iVar14;
          pfVar16 = pfVar13;
          pfVar10 = pfVar17;
          pfVar11 = (float *)(lVar18 + lVar19 * 0x1c0 + 0x378);
          do {
            pfVar24 = pfVar11;
            pfVar20 = *(float **)(pfVar24 + -10);
            pfVar13 = pfVar24 + -0x6e;
            lVar18 = *(long *)(pfVar20 + 0x4c);
            pfVar11 = pfVar20 + 0x2c;
            if ((*(byte *)((long)pfVar24 + -0x19) >> 1 & 1) != 0) {
              fVar26 = pfVar20[0x6e] * fVar8;
              if (fVar26 <= fVar9) {
                fVar26 = fVar9;
              }
              *pfVar24 = fVar26;
            }
            pfVar17 = pfVar24 + -0x42;
            if ((*(byte *)(pfVar24 + -7) & 1) == 0 && *(char *)(pfVar24 + -8) == '\0') {
              Aska::Matrix::InvertLowError(Aska::Matrix*) const(pfVar11,&uStack_c0);
              Aska::Matrix::ApplyVector(Aska::Vector*, Aska::Vector const*) const(&uStack_c0,&uStack_d0,pfVar24 + -0x6a);
              *(undefined8 *)(pfVar24 + -0x30) = uStack_c8;
              *(undefined8 *)(pfVar24 + -0x32) = uStack_d0;
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar17,pfVar24 + -0x32,pfVar24 + -0x2e,pfVar24 + -0x26,
                              pfVar24 + -0x2a,pfVar20 + 0x44,pfVar11);
              pfVar20 = (float *)0x0;
            }
            else if ((*(byte *)(pfVar24 + -7) >> 1 & 1) == 0) {
              pfVar20 = (float *)0x0;
            }
            else {
              lVar19 = lVar18 + 0x60;
              pfVar2 = pfVar20 + 0x44;
              if (lVar18 == 0) {
                lVar19 = 0;
              }
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar11,pfVar20 + 0x3c,pfVar20 + 0x40,pfVar20 + 0x48,pfVar2,lVar19,
                              lVar18);
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar17);
              void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x8c8(fVar25,&uStack_c0,pfVar11,pfVar13,pfVar17);
              *(undefined8 *)(pfVar20 + 0x42) = uStack_b8;
              *(undefined8 *)(pfVar20 + 0x40) = uStack_c0;
              *(byte *)((long)pfVar24 + -0x19) =
                   *(byte *)((long)pfVar24 + -0x19) | *(byte *)((long)pfVar20 + 0x19f) & 1;
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar11,pfVar20 + 0x3c,pfVar20 + 0x40,pfVar20 + 0x48,pfVar2,lVar19,
                              lVar18);
              if (((uint)pfVar20[0x67] & 1) == 0) {
                pfVar20[4] = pfVar20[0x2f];
                pfVar20[5] = pfVar20[0x33];
                pfVar20[6] = pfVar20[0x37];
                pfVar20[7] = 1.0;
              }
              void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x14c0(uVar7,pfVar20,pfVar11,cVar5 != '\0');
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar17,pfVar24 + -0x32,pfVar24 + -0x2e,pfVar24 + -0x26,
                              pfVar24 + -0x2a,pfVar2,pfVar11);
            }
            if (pfVar20 != pfVar16) {
              if (((uint)pfVar16[0x67] & 1) == 0) {
                fVar26 = pfVar10[7];
                fVar4 = pfVar10[0xb];
                pfVar16[4] = pfVar10[3];
                pfVar16[5] = fVar26;
                pfVar16[6] = fVar4;
                pfVar16[7] = 1.0;
              }
              void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x14c0(uVar7,pfVar16,pfVar10,cVar5 != '\0');
            }
            iVar14 = iVar14 + 1;
            pfVar16 = pfVar13;
            pfVar10 = pfVar17;
            pfVar11 = pfVar24 + 0x70;
          } while (iVar14 != 0);
          bVar6 = *(byte *)(pfVar24 + -7);
        }
        if ((bVar6 & 1) == 0) {
          fVar26 = pfVar17[7];
          fVar4 = pfVar17[0xb];
          pfVar13[4] = pfVar17[3];
          pfVar13[5] = fVar26;
          pfVar13[6] = fVar4;
          pfVar13[7] = 1.0;
        }
        void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManager, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x14c0(uVar7,pfVar13,pfVar17,cVar5 != '\0');
      }
      uVar22 = uVar22 + 1;
      piVar23 = piVar23 + 2;
    } while (uVar22 != uVar3);
  }
  return;
}

// ==== void Aska::ArticulatedDynamicsManagerBase::InterpolateRoot<Aska::ArticulatedDynamicsManager>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::ADMJoint*, float, unsigned int, unsigned int)
// vaddr 0x232909c | ghidra 0x242909c | size 604 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase15InterpolateRootINS_26ArticulatedDynamicsManagerEEEvPT_PNS_8ADMJointES6_fjj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase15InterpolateRootINS_26ArticulatedDynamicsManagerEEEvPT_PNS_8ADMJointES6_fjj
               (long param_1,long param_2,undefined8 param_3,uint param_4,int param_5)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  int iVar6;
  ulong uVar7;
  uint *puVar8;
  int iVar9;
  int iVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined1 auStack_c0 [64];
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  undefined4 uStack_74;
  
  if (1 < param_4) {
    if (param_4 - param_5 == 1) {
      iVar10 = *(int *)(param_1 + 0xb0);
      if (0 < iVar10) {
        puVar8 = *(uint **)(param_1 + 0xa8);
        iVar6 = 0;
        do {
          uVar3 = (ulong)*puVar8;
          if ((*(byte *)(param_2 + uVar3 * 0x1c0 + 0x19c) & 1) != 0) {
            uVar1 = puVar8[1];
            lVar5 = param_2 + uVar3 * 0x1c0;
            *(undefined8 *)(lVar5 + 0xf8) = *(undefined8 *)(lVar5 + 0x48);
            *(undefined8 *)(lVar5 + 0xf0) = *(undefined8 *)(lVar5 + 0x40);
            if (uVar1 != 1) {
              iVar9 = 1 - uVar1;
              lVar5 = param_2 + 0xb0 + uVar3 * 0x1c0;
              do {
                lVar4 = *(long *)(lVar5 + 0x80) + 0x60;
                if (*(long *)(lVar5 + 0x80) == 0) {
                  lVar4 = 0;
                }
                Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(lVar5,lVar5 + 0x40,lVar5 + 0x50,lVar5 + 0x70,lVar5 + 0x60,lVar4);
                iVar9 = iVar9 + 1;
                lVar5 = lVar5 + 0x1c0;
              } while (iVar9 != 0);
            }
          }
          iVar6 = iVar6 + 1;
          puVar8 = puVar8 + 2;
        } while (iVar6 != iVar10);
      }
    }
    else {
      uVar1 = *(uint *)(param_1 + 0xb0);
      if (0 < (int)uVar1) {
        puVar8 = *(uint **)(param_1 + 0xa8);
        fVar14 = 1.0 / (float)(int)(param_4 - param_5);
        uVar3 = 0;
        fVar15 = 1.0 - fVar14;
        do {
          uVar7 = (ulong)*puVar8;
          if ((*(byte *)(param_2 + uVar7 * 0x1c0 + 0x19c) & 1) != 0) {
            uVar2 = puVar8[1];
            lVar5 = *(long *)(param_1 + 0xa0) + uVar3 * 0xa0;
            lVar4 = param_2 + uVar7 * 0x1c0;
            if (param_5 == 0) {
              fVar11 = *(float *)(lVar4 + 0xbc);
              fVar12 = *(float *)(lVar4 + 0xcc);
              fVar13 = *(float *)(lVar4 + 0xdc);
              *(undefined8 *)(lVar4 + 0x48) = *(undefined8 *)(lVar4 + 0xf8);
              *(undefined8 *)(lVar4 + 0x40) = *(undefined8 *)(lVar4 + 0xf0);
              *(float *)(lVar4 + 0x30) = fVar11;
              *(float *)(lVar4 + 0x34) = fVar12;
              *(float *)(lVar4 + 0x38) = fVar13;
              *(undefined4 *)(lVar4 + 0x3c) = 0x3f800000;
            }
            else {
              fVar11 = *(float *)(lVar4 + 0x30);
              fVar12 = *(float *)(lVar4 + 0x34);
              fVar13 = *(float *)(lVar4 + 0x38);
            }
            lVar4 = param_2 + uVar7 * 0x1c0;
            uStack_74 = *(undefined4 *)(lVar4 + 0x1c);
            fStack_80 = fVar14 * fVar11 + fVar15 * *(float *)(lVar4 + 0x10);
            fStack_7c = fVar14 * fVar12 + fVar15 * *(float *)(lVar4 + 0x14);
            fStack_78 = fVar14 * fVar13 + fVar15 * *(float *)(lVar4 + 0x18);
            if (lVar5 != 0) {
              Aska::Matrix::InvertLowError(Aska::Matrix*) const(lVar5,auStack_c0);
              Aska::Vector::ApplyMatrix(Aska::Matrix const*)(&fStack_80,auStack_c0);
              lVar5 = param_2 + uVar7 * 0x1c0;
              *(ulong *)(lVar5 + 0xf8) = CONCAT44(uStack_74,fStack_78);
              *(ulong *)(lVar5 + 0xf0) = CONCAT44(fStack_7c,fStack_80);
            }
            if (uVar2 != 1) {
              iVar10 = 1 - uVar2;
              lVar5 = param_2 + 0xb0 + uVar7 * 0x1c0;
              do {
                lVar4 = *(long *)(lVar5 + 0x80) + 0x60;
                if (*(long *)(lVar5 + 0x80) == 0) {
                  lVar4 = 0;
                }
                Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(lVar5,lVar5 + 0x40,lVar5 + 0x50,lVar5 + 0x70,lVar5 + 0x60,lVar4);
                iVar10 = iVar10 + 1;
                lVar5 = lVar5 + 0x1c0;
              } while (iVar10 != 0);
            }
          }
          uVar3 = uVar3 + 1;
          puVar8 = puVar8 + 2;
        } while (uVar3 != uVar1);
      }
    }
  }
  return;
}

// ==== void Aska::ArticulatedDynamicsManagerBase::CollisionSetting<Aska::ArticulatedDynamicsManager>(Aska::ArticulatedDynamicsManager*, unsigned int, unsigned int)
// vaddr 0x23292f8 | ghidra 0x24292f8 | size 392 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase16CollisionSettingINS_26ArticulatedDynamicsManagerEEEvPT_jj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase16CollisionSettingINS_26ArticulatedDynamicsManagerEEEvPT_jj
               (long param_1,uint param_2,int param_3)

{
  int iVar1;
  long *plVar2;
  long *plVar3;
  long lVar4;
  ulong uVar5;
  float fVar6;
  
  plVar3 = *(long **)(param_1 + 0x148);
  iVar1 = param_2 - param_3;
  fVar6 = (float)(param_3 + 1) / (float)param_2;
  if ((plVar3 != (long *)0x0) && ((long)*(short *)(param_1 + 100) != 0)) {
    uVar5 = (long)*(short *)(param_1 + 100) & 0xffffffff;
    do {
      plVar2 = (long *)*plVar3;
      if (plVar2 != (long *)0x0) {
        (**(code **)(*plVar2 + 0x70))(fVar6,plVar2,iVar1 == 1);
      }
      uVar5 = uVar5 - 1;
      plVar3 = plVar3 + 1;
    } while (uVar5 != 0);
  }
  plVar3 = (long *)PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_pWorldCollisionListE_02cc4750;
  for (uVar5 = (ulong)(byte)*
                            PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0
      ; uVar5 != 0; uVar5 = uVar5 - 1) {
    plVar2 = (long *)*plVar3;
    if (plVar2 != (long *)0x0) {
      (**(code **)(*plVar2 + 0x70))(fVar6,plVar2,iVar1 == 1);
    }
    plVar3 = plVar3 + 1;
  }
  for (lVar4 = *(long *)(param_1 + 0x170); param_1 + 0x160 != lVar4; lVar4 = *(long *)(lVar4 + 0x10)
      ) {
    plVar3 = *(long **)(lVar4 + 0x38);
    if (plVar3 != (long *)0x0) {
      (**(code **)(*plVar3 + 0x70))(fVar6,plVar3,iVar1 == 1);
    }
  }
  plVar3 = *(long **)(param_1 + 0x150);
  if ((plVar3 != (long *)0x0) && ((long)*(short *)(param_1 + 0x66) != 0)) {
    uVar5 = (long)*(short *)(param_1 + 0x66) & 0xffffffff;
    do {
      plVar2 = (long *)*plVar3;
      if (plVar2 != (long *)0x0) {
        (**(code **)(*plVar2 + 0x70))(fVar6,plVar2,iVar1 == 1);
      }
      uVar5 = uVar5 - 1;
      plVar3 = plVar3 + 1;
    } while (uVar5 != 0);
  }
  plVar3 = (long *)PTR__ZN4Aska30ArticulatedDynamicsManagerBase22m_pWorldConstraintListE_02cbc740;
  for (uVar5 = (ulong)(byte)*
                            PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98
      ; uVar5 != 0; uVar5 = uVar5 - 1) {
    plVar2 = (long *)*plVar3;
    if (plVar2 != (long *)0x0) {
      (**(code **)(*plVar2 + 0x70))(fVar6,plVar2,iVar1 == 1);
    }
    plVar3 = plVar3 + 1;
  }
  return;
}

// ==== void Aska::ArticulatedDynamicsManager::MatrixPreFixAndMotionBlend<true>(Aska::ADM_CALC_DATA*, Aska::ADMJoint*, unsigned int, float, float, float, Aska::Vector*, bool)
// vaddr 0x2329480 | ghidra 0x2429480 | size 536 | symbol _ZN4Aska26ArticulatedDynamicsManager26MatrixPreFixAndMotionBlendILb1EEEvPNS_13ADM_CALC_DATAEPNS_8ADMJointEjfffPNS_6VectorEb | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska26ArticulatedDynamicsManager26MatrixPreFixAndMotionBlendILb1EEEvPNS_13ADM_CALC_DATAEPNS_8ADMJointEjfffPNS_6VectorEb
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               long param_5,int param_6,undefined8 param_7,uint param_8)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  float fVar4;
  undefined4 *puVar5;
  long lVar6;
  float *pfVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  float fVar11;
  float fVar12;
  
  fVar4 = _UNK_027e519c;
  uVar3 = _UNK_027dbb38;
  uVar2 = _UNK_027dbb30;
  if (param_6 != 0) {
    puVar10 = (undefined4 *)(param_5 + 0x1b8);
    do {
      lVar6 = *(long *)(puVar10 + -0x22);
      param_6 = param_6 + -1;
      if ((float)puVar10[-0x11] <= fVar4) {
        fVar11 = (float)puVar10[-0x53];
        puVar9 = puVar10 + -0x2c;
        puVar5 = puVar10 + -0x2e;
        puVar8 = puVar10 + -0x2d;
        pfVar7 = (float *)(puVar10 + -0x2b);
      }
      else {
        fVar11 = (float)puVar10[-0x53];
        puVar5 = (undefined4 *)(param_5 + 0x100);
        pfVar7 = (float *)(param_5 + 0x10c);
        puVar8 = (undefined4 *)(param_5 + 0x104);
        if ((float)puVar10[-0x2b] == fVar11) {
          fVar12 = (float)puVar10[-0x2d];
          if (((fVar12 == (float)puVar10[-0x55]) && ((float)puVar10[-0x2c] == (float)puVar10[-0x54])
              ) && ((float)puVar10[-0x2e] == (float)puVar10[-0x56])) {
            puVar9 = (undefined4 *)(param_5 + 0x108);
            goto code_r0x024295c0;
          }
        }
        else {
          fVar12 = (float)puVar10[-0x2d];
        }
        puVar10[-0x4e] = puVar10[-0x2e];
        puVar10[-0x4d] = fVar12;
        puVar9 = (undefined4 *)(param_5 + 0x108);
        puVar10[-0x4c] = puVar10[-0x2c];
        puVar10[-0x4b] = puVar10[-0x2b];
      }
code_r0x024295c0:
      puVar10[-0xb] = 0;
      *(undefined1 *)((long)puVar10 + -0x19) = 0;
      *(undefined8 *)(puVar10 + -0x66) = *(undefined8 *)(puVar10 + -0x6a);
      puVar10[-100] = puVar10[-0x68];
      puVar10[-99] = 0x3f800000;
      *(undefined8 *)(puVar10 + -0x48) = uVar3;
      *(undefined8 *)(puVar10 + -0x4a) = uVar2;
      *puVar10 = 0x3f4ccccd;
      *puVar5 = puVar10[-0x56];
      *puVar8 = puVar10[-0x55];
      *puVar9 = puVar10[-0x54];
      lVar1 = lVar6 + 0x60;
      if (lVar6 == 0) {
        lVar1 = 0;
      }
      *pfVar7 = fVar11;
      Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(puVar10 + -0x42,puVar10 + -0x32,puVar5,puVar10 + -0x26,puVar10 + -0x2a,lVar1);
      Aska::ADMJoint::ExternalForce(float, float, float, Aska::Vector const*, Aska::ADM_CALC_DATA*, bool)(param_1,param_2,param_3,puVar10 + -0x6e,param_7,puVar10 + -0x42,param_8 & 1);
      puVar10 = puVar10 + 0x70;
      param_5 = param_5 + 0x1c0;
    } while (param_6 != 0);
  }
  return;
}

// ==== void Aska::ArticulatedDynamicsManagerMP::SimulateMain<Aska::ArticulatedDynamicsManagerMP>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::ADMJoint*, unsigned int, int, int, unsigned int, float, float, unsigned int, float)
// vaddr 0x232c268 | ghidra 0x242c268 | size 904 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP12SimulateMainIS0_EEvPT_PNS_8ADMJointES5_jiijffjf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska28ArticulatedDynamicsManagerMP12SimulateMainIS0_EEvPT_PNS_8ADMJointES5_jiijffjf
               (undefined8 param_1,undefined8 param_2,float param_3,long param_4,undefined8 param_5,
               undefined8 param_6,uint param_7,int param_8,int param_9,undefined4 param_10,
               uint param_11)

{
  bool bVar1;
  int iVar2;
  long lVar3;
  int iVar4;
  char cVar5;
  short sVar6;
  byte bVar7;
  int iVar8;
  ulong uVar9;
  uint uVar10;
  ulong uVar11;
  undefined4 *puVar12;
  long lVar13;
  int iVar14;
  long lVar15;
  ulong uVar16;
  int iVar17;
  int iVar18;
  uint uStack_b8;
  
  sVar6 = *(short *)(param_4 + 0x62);
  if (*(char *)(param_4 + 0x9b) == '\x02') {
    iVar17 = (int)*(short *)(param_4 + 0x60);
    bVar7 = 1;
  }
  else {
    iVar17 = 1;
    bVar7 = *(byte *)(param_4 + 0x9a) & 1;
  }
  cVar5 = *(char *)(param_4 + 0xe2);
  iVar8 = (int)*(short *)(param_4 + 100);
  if (*(char *)(param_4 + 0xde) != '\0') {
    iVar8 = (uint)(byte)*PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0
            + iVar8;
  }
  uStack_b8 = 0;
  iVar4 = *(int *)(param_4 + 0x1a0);
  bVar1 = _UNK_027e519c < param_3;
  uVar10 = (uint)(byte)*PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98;
  if (*(char *)(param_4 + 0xde) == '\0') {
    uVar10 = 0;
  }
  uVar9 = (long)sVar6 & 0xffffffff;
  iVar2 = uVar10 + (int)*(short *)(param_4 + 0x66);
  if (*(long *)(param_4 + 0x130) != 0) {
    iVar2 = iVar2 + 1;
  }
  lVar13 = (uVar9 + ((long)sVar6 & 0xffffffffU) * 4) * 0x10;
  do {
    iVar14 = param_8;
    if (param_8 < param_9) {
      do {
        if (*(char *)(param_4 + 0x121) != '\0') {
          Aska::ArticulatedDynamicsManagerBase::UpdateDynamicsPrimitiveListWithDependencyOfADM(unsigned int)(param_4,iVar14);
        }
        void Aska::ArticulatedDynamicsManagerMP::PreprocessBeforeInternalForce<Aska::ArticulatedDynamicsManagerMP>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::ADMJoint*, float, float, unsigned int, unsigned int, bool)(param_1,param_2,param_4,param_5,param_6,param_9,iVar14,cVar5 != '\0');
        if (iVar17 != 0) {
          iVar18 = 0;
          do {
            if (sVar6 != 0) {
              uVar11 = *(ulong *)(param_4 + 0x78);
              if (*(char *)(param_4 + 0x9b) == '\x01') {
                uVar10 = 0;
                do {
                  lVar15 = 0;
                  do {
                    lVar3 = uVar11 + lVar15;
                    if (((*(byte *)(*(long *)(lVar3 + 0x40) + 0x19c) & 1) == 0) ||
                       ((*(byte *)(*(long *)(lVar3 + 0x48) + 0x19c) & 1) == 0)) {
                      void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x1d0(*(undefined4 *)(lVar3 + 0x28),*(undefined4 *)(lVar3 + 0x34),
                                      param_1,*(undefined1 *)(lVar3 + 0x21));
                    }
                    lVar15 = lVar15 + 0x50;
                    uVar16 = uVar11 + (uVar9 * 0x10 - 0x10 >> 4) * 0x50;
                  } while (lVar13 - lVar15 != 0);
                  do {
                    if (((*(byte *)(*(long *)(uVar16 + 0x40) + 0x19c) & 1) == 0) ||
                       ((*(byte *)(*(long *)(uVar16 + 0x48) + 0x19c) & 1) == 0)) {
                      void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x1d0(*(undefined4 *)(uVar16 + 0x28),*(undefined4 *)(uVar16 + 0x34),
                                      param_1,*(undefined1 *)(uVar16 + 0x21));
                    }
                    uVar16 = uVar16 - 0x50;
                  } while (uVar11 <= uVar16);
                  uVar10 = uVar10 + 1;
                } while (uVar10 < param_7);
              }
              else {
                puVar12 = (undefined4 *)(uVar11 + 0x28);
                lVar15 = lVar13;
                do {
                  if (((*(byte *)(*(long *)(puVar12 + 6) + 0x19c) & 1) == 0) ||
                     ((*(byte *)(*(long *)(puVar12 + 8) + 0x19c) & 1) == 0)) {
                    void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x1d0(*puVar12,puVar12[3],param_1,*(undefined1 *)((long)puVar12 + -7))
                    ;
                  }
                  lVar15 = lVar15 + -0x50;
                  puVar12 = puVar12 + 0x14;
                } while (lVar15 != 0);
              }
            }
            if (bVar7 == 0) {
              void Aska::ArticulatedDynamicsManagerBase::StandardIK<Aska::ArticulatedDynamicsManagerMP, false>(Aska::ArticulatedDynamicsManagerMP*, float, float, int)(param_1,param_2,param_4,param_10);
            }
            void Aska::ArticulatedDynamicsManagerBase::CollisionAndConstraint<Aska::ArticulatedDynamicsManagerMP>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::ADMJoint*, unsigned int, unsigned int, float)(param_1,param_4,param_5,param_6,iVar4 + iVar8,iVar2);
            iVar18 = iVar18 + 1;
          } while (iVar18 != iVar17);
        }
        if (bVar7 == 0) {
          void Aska::ArticulatedDynamicsManagerBase::Finalize<Aska::ArticulatedDynamicsManagerMP>(Aska::ArticulatedDynamicsManagerMP*, float, float, int)(param_1,param_2,param_4,param_10);
        }
        else {
          void Aska::ArticulatedDynamicsManagerBase::StandardIK<Aska::ArticulatedDynamicsManagerMP, true>(Aska::ArticulatedDynamicsManagerMP*, float, float, int)(param_1,param_2,param_4,param_10);
        }
        iVar14 = iVar14 + 1;
      } while (iVar14 != param_9);
    }
    if (bVar1 && 0.0 <= param_3) {
      if ((long)*(short *)(param_4 + 0x60) < 1) {
code_r0x0242c5c4:
        *(undefined4 *)(param_4 + 0x118) = 0;
        return;
      }
      uVar11 = *(ulong *)(param_4 + 0x70);
      uVar16 = uVar11 + (long)*(short *)(param_4 + 0x60) * 0x1c0;
      while (((ABS(*(float *)(uVar11 + 0x50)) <= param_3 &&
              (ABS(*(float *)(uVar11 + 0x54)) <= param_3)) &&
             (ABS(*(float *)(uVar11 + 0x58)) <= param_3))) {
        uVar11 = uVar11 + 0x1c0;
        if (uVar16 <= uVar11) goto code_r0x0242c5c4;
      }
    }
    uStack_b8 = uStack_b8 + 1;
    if (param_11 <= uStack_b8) {
      return;
    }
  } while( true );
}

// ==== void Aska::ArticulatedDynamicsManagerMP::GetAcceleration<Aska::ArticulatedDynamicsManagerMP, Aska::ADMJoint>(Aska::ArticulatedDynamicsManagerMP*, float, Aska::LinkListParam*, int)
// vaddr 0x232cc1c | ghidra 0x242cc1c | size 1560 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP15GetAccelerationIS0_NS_8ADMJointEEEvPT_fPNS_13LinkListParamEi | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska28ArticulatedDynamicsManagerMP15GetAccelerationIS0_NS_8ADMJointEEEvPT_fPNS_13LinkListParamEi
               (float param_1,long param_2,float *param_3,uint param_4)

{
  float *pfVar1;
  float *pfVar2;
  long *plVar3;
  float *pfVar4;
  uint uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  int iVar13;
  float *pfVar14;
  long lVar15;
  float *pfVar16;
  float *pfVar17;
  ulong uVar18;
  ulong uVar19;
  int iVar20;
  ulong uVar21;
  long lVar22;
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
  
  fVar30 = *(float *)(param_2 + 0xf4);
  memset(*(undefined8 *)(param_2 + 0x1d0),0,
                  -(ulong)(param_4 >> 0x1f) & 0xfffffffc00000000 | (ulong)param_4 << 2);
  uVar6 = _UNK_027dbb38;
  uVar7 = _UNK_027dbb30;
  if (0 < (int)param_4) {
    pfVar14 = param_3 + (long)(int)param_4 * 0x14;
    pfVar16 = pfVar14;
    if (pfVar14 <= param_3 + 0x14) {
      pfVar16 = param_3 + 0x14;
    }
    uVar21 = ((long)pfVar16 + ~(ulong)param_3) / 0x50 + 1;
    pfVar16 = param_3;
    if ((1 < uVar21) && (uVar18 = uVar21 & 0x7fffffffffffffe, uVar18 != 0)) {
      pfVar16 = param_3 + uVar18 * 0x14;
      uVar19 = uVar18;
      pfVar17 = param_3;
      do {
        *(undefined8 *)(pfVar17 + 2) = uVar6;
        *(undefined8 *)pfVar17 = uVar7;
        *(undefined8 *)(pfVar17 + 0x16) = uVar6;
        *(undefined8 *)(pfVar17 + 0x14) = uVar7;
        uVar19 = uVar19 - 2;
        pfVar17 = pfVar17 + 0x28;
      } while (uVar19 != 0);
      uVar6 = _UNK_027dbb38;
      uVar7 = _UNK_027dbb30;
      if (uVar21 == uVar18) goto code_r0x0242ccec;
    }
    do {
      pfVar17 = pfVar16 + 0x14;
      *(undefined8 *)(pfVar16 + 2) = uVar6;
      *(undefined8 *)pfVar16 = uVar7;
      pfVar16 = pfVar17;
    } while (pfVar17 < pfVar14);
  }
code_r0x0242ccec:
  fVar24 = _UNK_029e2e84;
  pfVar16 = *(float **)(param_2 + 0x1d0);
  pfVar14 = *(float **)(param_2 + 0x1d8);
  fVar31 = fVar30;
  if ((*(byte *)(*(long *)(param_3 + 0xe) + 0x19d) & 1) == 0) {
    fVar31 = 0.0;
  }
  fVar23 = *(float *)(*(long *)(param_3 + 0xe) + 0x180);
  *pfVar16 = fVar31 * param_3[5] * param_1 +
             (param_3[4] * param_3[8] + param_3[5] * param_3[9] + param_3[6] * param_3[10]) *
             _UNK_029e2e84;
  lVar22 = (long)(int)param_4;
  plVar3 = (long *)(param_2 + 0x1f0);
  **(undefined4 **)(param_2 + 0x1f0) = 0;
  fVar25 = _UNK_029e2e88;
  fVar26 = (param_3[4] * param_3[4] + param_3[5] * param_3[5] + param_3[6] * param_3[6]) / fVar23;
  fVar28 = _UNK_029e2e88;
  if (fVar26 != 0.0) {
    fVar28 = -fVar26;
  }
  *(float *)(*(long *)(param_2 + 0x1f0) + 4) = fVar28;
  if (1 < (int)param_4) {
    pfVar17 = (float *)(*plVar3 + 8);
    fVar23 = (param_3[4] * param_3[0x18] + param_3[5] * param_3[0x19] + param_3[6] * param_3[0x1a])
             / fVar23;
    iVar13 = 1;
    while( true ) {
      *pfVar17 = fVar23;
code_r0x0242cde0:
      uVar21 = lVar22 - 1;
      iVar20 = (int)uVar21;
      if (iVar20 <= iVar13) break;
      fVar26 = *(float *)(*(long *)(param_3 + (long)iVar13 * 0x14 + 0xc) + 0x180);
      fVar23 = *(float *)(*(long *)(param_3 + (long)iVar13 * 0x14 + 0xe) + 0x180);
      fVar28 = fVar30;
      if ((*(byte *)(*(long *)(param_3 + (long)iVar13 * 0x14 + 0xc) + 0x19d) & 1) == 0) {
        fVar28 = 0.0;
      }
      fVar27 = fVar30;
      if ((*(byte *)(*(long *)(param_3 + (long)iVar13 * 0x14 + 0xe) + 0x19d) & 1) == 0) {
        fVar27 = 0.0;
      }
      pfVar16[iVar13] =
           (fVar28 - fVar27) * param_3[(long)iVar13 * 0x14 + 5] * param_1 +
           (param_3[(long)iVar13 * 0x14 + 4] * param_3[(long)iVar13 * 0x14 + 8] +
            param_3[(long)iVar13 * 0x14 + 5] * param_3[(long)iVar13 * 0x14 + 9] +
           param_3[(long)iVar13 * 0x14 + 6] * param_3[(long)iVar13 * 0x14 + 10]) * fVar24;
      uVar5 = iVar13 * 3;
      *(float *)(*plVar3 + (ulong)uVar5 * 4) =
           (param_3[(long)iVar13 * 0x14 + 4] * param_3[(long)iVar13 * 0x14 + -0x10] +
            param_3[(long)iVar13 * 0x14 + 5] * param_3[(long)iVar13 * 0x14 + -0xf] +
           param_3[(long)iVar13 * 0x14 + 6] * param_3[(long)iVar13 * 0x14 + -0xe]) / fVar26;
      fVar26 = 1.0 / fVar26 + 1.0 / fVar23;
      fVar27 = param_3[(long)iVar13 * 0x14 + 4] * param_3[(long)iVar13 * 0x14 + 4] +
               param_3[(long)iVar13 * 0x14 + 5] * param_3[(long)iVar13 * 0x14 + 5] +
               param_3[(long)iVar13 * 0x14 + 6] * param_3[(long)iVar13 * 0x14 + 6];
      fVar28 = fVar25;
      if (fVar26 * fVar27 != 0.0) {
        fVar28 = -(fVar26 * fVar27);
      }
      *(float *)(*plVar3 + (ulong)(uVar5 + 1) * 4) = fVar28;
      lVar15 = (long)iVar13;
      lVar11 = (long)iVar13;
      lVar8 = (long)iVar13;
      lVar12 = (long)iVar13;
      lVar9 = (long)iVar13;
      lVar10 = (long)iVar13;
      iVar13 = iVar13 + 1;
      fVar23 = (param_3[lVar15 * 0x14 + 4] * param_3[lVar8 * 0x14 + 0x18] +
                param_3[lVar11 * 0x14 + 5] * param_3[lVar12 * 0x14 + 0x19] +
               param_3[lVar9 * 0x14 + 6] * param_3[lVar10 * 0x14 + 0x1a]) / fVar23;
      pfVar17 = (float *)(*plVar3 + (ulong)(uVar5 + 2) * 4);
    }
    if (1 < (int)param_4) {
      fVar23 = *(float *)(*(long *)(param_3 + uVar21 * 0x14 + 0xc) + 0x180);
      fVar28 = fVar30;
      if ((*(byte *)(*(long *)(param_3 + uVar21 * 0x14 + 0xc) + 0x19d) & 1) == 0) {
        fVar28 = 0.0;
      }
      fVar26 = 1.0 / fVar23 + 1.0 / *(float *)(*(long *)(param_3 + uVar21 * 0x14 + 0xe) + 0x180);
      if ((*(byte *)(*(long *)(param_3 + uVar21 * 0x14 + 0xe) + 0x19d) & 1) == 0) {
        fVar30 = 0.0;
      }
      pfVar16[uVar21] =
           (fVar28 - fVar30) * param_3[uVar21 * 0x14 + 5] * param_1 +
           (param_3[uVar21 * 0x14 + 4] * param_3[uVar21 * 0x14 + 8] +
            param_3[uVar21 * 0x14 + 5] * param_3[uVar21 * 0x14 + 9] +
           param_3[uVar21 * 0x14 + 6] * param_3[uVar21 * 0x14 + 10]) * fVar24;
      uVar5 = iVar20 * 3;
      *(float *)(*plVar3 + (ulong)uVar5 * 4) =
           (param_3[uVar21 * 0x14 + 4] * param_3[lVar22 * 0x14 + -0x24] +
            param_3[uVar21 * 0x14 + 5] * param_3[lVar22 * 0x14 + -0x23] +
           param_3[uVar21 * 0x14 + 6] * param_3[lVar22 * 0x14 + -0x22]) / fVar23;
      fVar30 = param_3[uVar21 * 0x14 + 4] * param_3[uVar21 * 0x14 + 4] +
               param_3[uVar21 * 0x14 + 5] * param_3[uVar21 * 0x14 + 5] +
               param_3[uVar21 * 0x14 + 6] * param_3[uVar21 * 0x14 + 6];
      if (fVar26 * fVar30 != 0.0) {
        fVar25 = -(fVar26 * fVar30);
      }
      *(float *)(*plVar3 + (ulong)(uVar5 + 1) * 4) = fVar25;
      *(undefined4 *)(*plVar3 + (ulong)(uVar5 + 2) * 4) = 0;
    }
    Aska::BandMatrix<3u>::SolveLinearEquation(float*, float*, int)(plVar3,pfVar14,pfVar16,param_4);
    fVar30 = *(float *)(*(long *)(param_3 + 0xe) + 0x180);
    if (param_4 == 1) {
      fVar24 = param_3[4];
      *param_3 = -(fVar24 * (*pfVar14 / fVar30));
      lVar15 = 0;
      param_3[1] = -(fVar24 * (*pfVar14 / fVar30)) - fVar31 * param_1;
      fVar24 = fVar24 * (*pfVar14 / fVar30);
      fVar30 = _UNK_027f7cb8;
    }
    else {
      fVar24 = *pfVar14 / fVar30;
      fVar30 = pfVar14[1] / fVar30;
      *param_3 = fVar30 * param_3[0x18] - param_3[4] * fVar24;
      param_3[1] = (fVar30 * param_3[0x19] - param_3[5] * fVar24) - fVar31 * param_1;
      param_3[2] = fVar30 * param_3[0x1a] - param_3[6] * fVar24;
      if (2 < (int)param_4) {
        pfVar16 = param_3 + 0x17;
        lVar15 = (uVar21 & 0xffffffff) - 1;
        pfVar17 = pfVar14 + 1;
        fVar30 = param_3[0x18];
        fVar24 = param_3[0x19];
        fVar31 = param_3[0x1a];
        fVar28 = param_3[4];
        fVar25 = param_3[5];
        fVar23 = param_3[6];
        do {
          fVar29 = fVar31;
          fVar27 = fVar24;
          fVar26 = fVar30;
          lVar15 = lVar15 + -1;
          fVar31 = *(float *)(*(long *)(pfVar16 + 0xb) + 0x180);
          fVar24 = pfVar17[-1] / *(float *)(*(long *)(pfVar16 + 9) + 0x180);
          fVar30 = (1.0 / *(float *)(*(long *)(pfVar16 + 9) + 0x180) + 1.0 / fVar31) * *pfVar17;
          pfVar2 = pfVar16 + 0x15;
          pfVar4 = pfVar16 + 0x16;
          pfVar1 = pfVar16 + 0x17;
          pfVar17 = pfVar17 + 1;
          fVar32 = *pfVar17;
          *pfVar16 = 1.0;
          fVar32 = fVar32 / fVar31;
          pfVar16[-3] = (fVar28 * fVar24 - fVar26 * fVar30) + *pfVar2 * fVar32;
          pfVar16[-2] = (fVar25 * fVar24 - fVar27 * fVar30) + *pfVar4 * fVar32;
          pfVar16[-1] = (fVar23 * fVar24 - fVar29 * fVar30) + *pfVar1 * fVar32;
          pfVar16 = pfVar16 + 0x14;
          fVar30 = *pfVar2;
          fVar24 = *pfVar4;
          fVar31 = *pfVar1;
          fVar28 = fVar26;
          fVar25 = fVar27;
          fVar23 = fVar29;
        } while (lVar15 != 0);
        if (param_4 == 1) {
          return;
        }
      }
      pfVar16 = param_3 + (long)iVar20 * 0x14;
      lVar22 = lVar22 + -2;
      fVar30 = pfVar14[lVar22] / *(float *)(*(long *)(pfVar16 + 0xc) + 0x180);
      fVar24 = pfVar14[iVar20] *
               (1.0 / *(float *)(*(long *)(pfVar16 + 0xc) + 0x180) +
               1.0 / *(float *)(*(long *)(pfVar16 + 0xe) + 0x180));
      *pfVar16 = fVar30 * param_3[lVar22 * 0x14 + 4] - fVar24 * pfVar16[4];
      pfVar16[1] = fVar30 * param_3[lVar22 * 0x14 + 5] - fVar24 * pfVar16[5];
      lVar15 = (long)iVar20;
      fVar30 = fVar30 * param_3[lVar22 * 0x14 + 6];
      fVar24 = fVar24 * pfVar16[6];
    }
    param_3[lVar15 * 0x14 + 2] = fVar30 - fVar24;
    return;
  }
  iVar13 = 1;
  goto code_r0x0242cde0;
}

// ==== void Aska::ArticulatedDynamicsManagerMP::PreprocessBeforeInternalForce<Aska::ArticulatedDynamicsManagerMP>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::ADMJoint*, float, float, unsigned int, unsigned int, bool)
// vaddr 0x232d288 | ghidra 0x242d288 | size 528 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP29PreprocessBeforeInternalForceIS0_EEvPT_PNS_8ADMJointES5_ffjjb | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska28ArticulatedDynamicsManagerMP29PreprocessBeforeInternalForceIS0_EEvPT_PNS_8ADMJointES5_ffjjb
               (undefined8 param_1,undefined8 param_2,long param_3,long param_4,undefined8 param_5,
               undefined4 param_6,undefined4 param_7,uint param_8)

{
  long lVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  uint *puVar9;
  uint uVar10;
  undefined4 uVar11;
  
  void Aska::ArticulatedDynamicsManagerBase::InterpolateRoot<Aska::ArticulatedDynamicsManagerMP>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::ADMJoint*, float, unsigned int, unsigned int)();
  void Aska::ArticulatedDynamicsManagerBase::CollisionSetting<Aska::ArticulatedDynamicsManagerMP>(Aska::ArticulatedDynamicsManagerMP*, unsigned int, unsigned int)(param_3,param_6,param_7);
  void Aska::ArticulatedDynamicsManagerMP::CalcPenduramAccel<Aska::ArticulatedDynamicsManagerMP, Aska::ADMJoint>(Aska::ArticulatedDynamicsManagerMP*, float)(param_1,param_3);
  uVar5 = _UNK_027dbb38;
  uVar4 = _UNK_027dbb30;
  uVar11 = *(undefined4 *)(param_3 + 0xf4);
  uVar2 = *(uint *)(param_3 + 0xb0);
  uVar8 = (ulong)uVar2;
  puVar9 = *(uint **)(param_3 + 0xa8);
  if (*(float *)(param_3 + 0xf0) <= 0.0) {
    if (0 < (int)uVar2) {
      uVar10 = 0;
      do {
        uVar6 = puVar9[1];
        if (uVar6 != 0) {
          lVar7 = param_4 + (ulong)*puVar9 * 0x1c0;
          do {
            *(undefined8 *)(lVar7 + 0x98) = uVar5;
            *(undefined8 *)(lVar7 + 0x90) = uVar4;
            *(undefined8 *)(lVar7 + 0x20) = *(undefined8 *)(lVar7 + 0x10);
            lVar1 = *(long *)(lVar7 + 0x130) + 0x60;
            if (*(long *)(lVar7 + 0x130) == 0) {
              lVar1 = 0;
            }
            uVar6 = uVar6 - 1;
            *(undefined4 *)(lVar7 + 0x18c) = 0;
            *(undefined1 *)(lVar7 + 0x19f) = 0;
            *(undefined4 *)(lVar7 + 0x1b8) = 0x3f4ccccd;
            *(undefined4 *)(lVar7 + 0x28) = *(undefined4 *)(lVar7 + 0x18);
            *(undefined4 *)(lVar7 + 0x2c) = 0x3f800000;
            *(undefined8 *)(lVar7 + 0x108) = *(undefined8 *)(lVar7 + 0x68);
            *(undefined8 *)(lVar7 + 0x100) = *(undefined8 *)(lVar7 + 0x60);
            Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(lVar7 + 0xb0,lVar7 + 0xf0,lVar7 + 0x100,lVar7 + 0x120,lVar7 + 0x110,
                            lVar1);
            Aska::ADMJoint::ExternalForceMP(float, float, float, Aska::Vector const*, Aska::ADM_CALC_DATA*, bool)(param_1,param_2,uVar11,lVar7,param_3 + 0x40,lVar7 + 0xb0,param_8 & 1);
            lVar7 = lVar7 + 0x1c0;
          } while (uVar6 != 0);
        }
        uVar10 = uVar10 + 1;
        puVar9 = puVar9 + 2;
      } while (uVar10 != uVar2);
    }
  }
  else if (0 < (int)uVar2) {
    lVar7 = 0;
    do {
      void Aska::ArticulatedDynamicsManagerMP::MatrixPreFixAndMotionBlend<true>(Aska::ADM_CALC_DATA*, Aska::ADMJoint*, unsigned int, float, float, float, Aska::Vector*, bool)(param_1,param_2,uVar11,*(long *)(param_3 + 0xa0) + lVar7,
                      param_4 + (ulong)*puVar9 * 0x1c0,puVar9[1],param_3 + 0x40,param_8 & 1);
      lVar7 = lVar7 + 0xa0;
      uVar8 = uVar8 - 1;
      puVar9 = puVar9 + 2;
    } while (uVar8 != 0);
  }
  lVar7 = Aska::DynamicsManager::GetForceEmitterManager()();
  if ((*(int *)(lVar7 + 0x58) != 0) && (*(int *)(param_3 + 0x88) != 0)) {
    iVar3 = *(int *)(param_3 + 0x8c);
    void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)(param_1,param_3,param_4,*(undefined8 *)(lVar7 + 0x50),*(int *)(lVar7 + 0x58),
                    iVar3);
    *(int *)(param_3 + 0x8c) = iVar3 + 0x56b46fd1;
  }
  return;
}

// ==== void Aska::ArticulatedDynamicsManagerBase::StandardIK<Aska::ArticulatedDynamicsManagerMP, false>(Aska::ArticulatedDynamicsManagerMP*, float, float, int)
// vaddr 0x232d498 | ghidra 0x242d498 | size 928 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase10StandardIKINS_28ArticulatedDynamicsManagerMPELb0EEEvPT_ffi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase10StandardIKINS_28ArticulatedDynamicsManagerMPELb0EEEvPT_ffi
               (undefined8 param_1,long param_2,undefined4 param_3)

{
  undefined8 *puVar1;
  byte *pbVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  byte bVar6;
  byte *pbVar7;
  long lVar8;
  long lVar9;
  byte *pbVar10;
  int iVar11;
  long lVar12;
  byte *pbVar13;
  long lVar14;
  byte *pbVar15;
  long lVar16;
  byte *pbVar17;
  ulong uVar18;
  int *piVar19;
  byte *pbVar20;
  byte *pbVar21;
  byte *pbVar22;
  byte *pbVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  undefined4 uVar26;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined1 auStack_b0 [64];
  
  uVar3 = *(uint *)(param_2 + 0xb0);
  if (0 < (int)uVar3) {
    uVar26 = *(undefined4 *)(param_2 + 0xf0);
    piVar19 = *(int **)(param_2 + 0xa8);
    uVar18 = 0;
    do {
      iVar11 = piVar19[1];
      lVar9 = *(long *)(param_2 + 0x70);
      lVar16 = *(long *)(param_2 + 0xa0);
      lVar12 = (long)*piVar19;
      pbVar22 = (byte *)(lVar9 + lVar12 * 0x1c0);
      lVar14 = lVar16 + uVar18 * 0xa0;
      pbVar23 = pbVar22 + 0xb0;
      if ((pbVar22[0x19d] >> 5 & 1) != 0) {
        lVar8 = lVar9 + lVar12 * 0x1c0;
        *(undefined8 *)(lVar8 + 0x108) = *(undefined8 *)(lVar8 + 0x78);
        *(undefined8 *)(lVar8 + 0x100) = *(undefined8 *)(lVar8 + 0x70);
      }
      if ((*(char *)(lVar9 + lVar12 * 0x1c0 + 0x198) == '\0') &&
         ((*(byte *)(lVar9 + lVar12 * 0x1c0 + 0x19c) & 1) == 0)) {
        lVar8 = lVar9 + lVar12 * 0x1c0;
        puVar1 = (undefined8 *)(lVar8 + 0x10);
        if (lVar14 == 0) {
          uVar25 = *(undefined8 *)(lVar8 + 0x18);
          uVar24 = *puVar1;
        }
        else {
          Aska::Matrix::InvertLowError(Aska::Matrix*) const(lVar14,auStack_b0);
          Aska::Matrix::ApplyVector(Aska::Vector*, Aska::Vector const*) const(auStack_b0,&uStack_c0,puVar1);
          uVar24 = uStack_c0;
          uVar25 = uStack_b8;
        }
        lVar8 = lVar9 + lVar12 * 0x1c0;
        *(undefined8 *)(lVar8 + 0xf8) = uVar25;
        *(undefined8 *)(lVar8 + 0xf0) = uVar24;
      }
      lVar8 = lVar9 + lVar12 * 0x1c0;
      lVar16 = lVar16 + uVar18 * 0xa0 + 0x60;
      if (lVar14 == 0) {
        lVar16 = 0;
      }
      Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pbVar23,lVar8 + 0xf0,lVar8 + 0x100,lVar8 + 0x120,lVar8 + 0x110,lVar16,lVar14);
      if (iVar11 == 1) {
        bVar6 = pbVar22[0x19c];
        pbVar21 = pbVar22;
      }
      else {
        iVar11 = 1 - iVar11;
        pbVar13 = pbVar22;
        pbVar2 = (byte *)(lVar9 + lVar12 * 0x1c0 + 0x35d);
        pbVar20 = pbVar23;
        do {
          pbVar15 = pbVar2;
          pbVar17 = *(byte **)(pbVar15 + -0xd);
          pbVar21 = pbVar15 + -0x19d;
          pbVar23 = pbVar15 + -0xed;
          pbVar2 = pbVar17 + 0xb0;
          if ((pbVar15[-1] & 1) == 0 && pbVar15[-5] == 0) {
            Aska::Matrix::InvertLowError(Aska::Matrix*) const(pbVar2,auStack_b0);
            Aska::Matrix::ApplyVector(Aska::Vector*, Aska::Vector const*) const(auStack_b0,&uStack_c0,pbVar15 + -0x18d);
            *(undefined8 *)(pbVar15 + -0xa5) = uStack_b8;
            *(undefined8 *)(pbVar15 + -0xad) = uStack_c0;
            bVar6 = *pbVar15;
            pbVar10 = (byte *)0x0;
joined_r0x0242d658:
            if ((bVar6 >> 5 & 1) == 0) goto code_r0x0242d65c;
code_r0x0242d740:
            pbVar7 = pbVar22 + 0x2c0;
            *(undefined8 *)(pbVar15 + -0x95) = *(undefined8 *)(pbVar15 + -0x125);
            *(undefined8 *)(pbVar15 + -0x9d) = *(undefined8 *)(pbVar15 + -0x12d);
          }
          else {
            if ((pbVar15[-1] >> 1 & 1) != 0) {
              lVar12 = *(long *)(pbVar17 + 0x130);
              lVar9 = lVar12 + 0x60;
              if (lVar12 == 0) {
                lVar9 = 0;
              }
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pbVar2);
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pbVar23,pbVar15 + -0xad,pbVar15 + -0x9d,pbVar15 + -0x7d,
                              pbVar15 + -0x8d,pbVar17 + 0x110,pbVar2);
              void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x5b4(uVar26,param_1,pbVar17,pbVar2,pbVar21,pbVar23,param_3);
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pbVar2,pbVar17 + 0xf0,pbVar17 + 0x100,pbVar17 + 0x120,pbVar17 + 0x110,
                              lVar9,lVar12);
              if ((pbVar17[0x19c] & 1) == 0) {
                *(undefined4 *)(pbVar17 + 0x10) = *(undefined4 *)(pbVar17 + 0xbc);
                *(undefined4 *)(pbVar17 + 0x14) = *(undefined4 *)(pbVar17 + 0xcc);
                *(undefined4 *)(pbVar17 + 0x18) = *(undefined4 *)(pbVar17 + 0xdc);
                pbVar17[0x1c] = 0;
                pbVar17[0x1d] = 0;
                pbVar17[0x1e] = 0x80;
                pbVar17[0x1f] = 0x3f;
              }
              bVar6 = *pbVar15;
              pbVar10 = pbVar17;
              goto joined_r0x0242d658;
            }
            pbVar10 = (byte *)0x0;
            if ((*pbVar15 >> 5 & 1) != 0) goto code_r0x0242d740;
code_r0x0242d65c:
            pbVar7 = pbVar15 + -0x9d;
          }
          pbVar22 = pbVar22 + 0x1c0;
          Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pbVar23,pbVar15 + -0xad,pbVar7,pbVar15 + -0x7d,pbVar15 + -0x8d,
                          pbVar17 + 0x110,pbVar2);
          if ((pbVar10 != pbVar13) && ((pbVar13[0x19c] & 1) == 0)) {
            uVar4 = *(undefined4 *)(pbVar20 + 0x1c);
            uVar5 = *(undefined4 *)(pbVar20 + 0x2c);
            *(undefined4 *)(pbVar13 + 0x10) = *(undefined4 *)(pbVar20 + 0xc);
            *(undefined4 *)(pbVar13 + 0x14) = uVar4;
            *(undefined4 *)(pbVar13 + 0x18) = uVar5;
            pbVar13[0x1c] = 0;
            pbVar13[0x1d] = 0;
            pbVar13[0x1e] = 0x80;
            pbVar13[0x1f] = 0x3f;
          }
          iVar11 = iVar11 + 1;
          pbVar13 = pbVar21;
          pbVar2 = pbVar15 + 0x1c0;
          pbVar20 = pbVar23;
        } while (iVar11 != 0);
        bVar6 = pbVar15[-1];
      }
      if ((bVar6 & 1) == 0) {
        uVar4 = *(undefined4 *)(pbVar23 + 0x1c);
        uVar5 = *(undefined4 *)(pbVar23 + 0x2c);
        *(undefined4 *)(pbVar21 + 0x10) = *(undefined4 *)(pbVar23 + 0xc);
        *(undefined4 *)(pbVar21 + 0x14) = uVar4;
        *(undefined4 *)(pbVar21 + 0x18) = uVar5;
        pbVar21[0x1c] = 0;
        pbVar21[0x1d] = 0;
        pbVar21[0x1e] = 0x80;
        pbVar21[0x1f] = 0x3f;
      }
      uVar18 = uVar18 + 1;
      piVar19 = piVar19 + 2;
    } while (uVar18 != uVar3);
  }
  if (0 < (long)*(short *)(param_2 + 0x98)) {
    lVar9 = *(long *)(param_2 + 0x90);
    uVar18 = lVar9 + *(short *)(param_2 + 0x98);
    if (uVar18 <= lVar9 + 1U) {
      uVar18 = lVar9 + 1;
    }
    memset(lVar9,0,uVar18 - lVar9);
  }
  return;
}

// ==== void Aska::ArticulatedDynamicsManagerBase::CollisionAndConstraint<Aska::ArticulatedDynamicsManagerMP>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::ADMJoint*, unsigned int, unsigned int, float)
// vaddr 0x232d838 | ghidra 0x242d838 | size 2608 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase22CollisionAndConstraintINS_28ArticulatedDynamicsManagerMPEEEvPT_PNS_8ADMJointES6_jjf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska30ArticulatedDynamicsManagerBase22CollisionAndConstraintINS_28ArticulatedDynamicsManagerMPEEEvPT_PNS_8ADMJointES6_jjf
               (undefined1 param_1 [16],long param_2,long param_3,long param_4,ulong param_5,
               int param_6)

{
  undefined1 (*pauVar1) [12];
  undefined1 (*pauVar2) [12];
  byte *pbVar3;
  uint uVar4;
  byte bVar5;
  short sVar6;
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  bool bVar14;
  ulong uVar15;
  uint uVar16;
  int iVar17;
  long lVar18;
  undefined4 *puVar19;
  long *plVar20;
  ulong uVar21;
  long lVar22;
  undefined8 *puVar23;
  int iVar24;
  undefined1 (*pauVar25) [16];
  long lVar26;
  long *plVar27;
  undefined1 auVar28 [12];
  undefined1 auVar29 [12];
  undefined8 uVar34;
  undefined1 auVar30 [16];
  undefined1 auVar31 [16];
  undefined1 auVar32 [16];
  undefined1 auVar33 [16];
  float fVar35;
  float fVar39;
  undefined1 auVar36 [16];
  float fVar41;
  undefined1 auVar37 [16];
  undefined1 auVar38 [16];
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  undefined4 uVar46;
  float fVar47;
  float fVar50;
  undefined1 auVar48 [16];
  undefined1 auVar49 [16];
  undefined1 auVar51 [16];
  undefined1 auVar52 [16];
  undefined1 auVar53 [16];
  float fVar54;
  float fVar55;
  float fVar56;
  float fVar57;
  undefined4 uVar58;
  float fVar59;
  float fVar60;
  float fVar61;
  float fVar62;
  float fVar63;
  float fVar64;
  float fVar65;
  float fVar66;
  float fVar67;
  float fVar68;
  float fVar69;
  float fVar70;
  undefined1 auVar71 [16];
  int iStack_634;
  undefined8 auStack_560 [128];
  undefined1 auStack_160 [64];
  undefined8 uStack_120;
  float fStack_118;
  undefined4 uStack_114;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined4 uStack_e0;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  float fStack_c0;
  float fStack_bc;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  float fVar40;
  
  plVar20 = *(long **)(param_2 + 0x130);
  uVar34 = param_1._8_8_;
  if (plVar20 == (long *)0x0) {
    plVar20 = *(long **)
               PTR__ZN4Aska30ArticulatedDynamicsManagerBase22m_pWorldLandConstraintE_02cc3ab0;
    bVar14 = plVar20 == (long *)0x0;
    if ((-param_6 == (int)param_5) && (plVar20 == (long *)0x0)) {
      return;
    }
  }
  else {
    bVar14 = false;
  }
  if ((int)param_5 < 1) {
    param_5 = 0;
  }
  else {
    sVar6 = *(short *)(param_2 + 100);
    lVar18 = 0;
    uVar21 = 0;
    lVar22 = -((long)sVar6 << 0x20);
    do {
      if ((long)uVar21 < (long)sVar6) {
        puVar23 = (undefined8 *)(*(long *)(param_2 + 0x148) + lVar18);
      }
      else {
        puVar23 = (undefined8 *)
                  (PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_pWorldCollisionListE_02cc4750 +
                  (lVar22 >> 0x1d));
      }
      uVar21 = uVar21 + 1;
      lVar22 = lVar22 + 0x100000000;
      *(undefined8 *)((long)auStack_560 + lVar18) = *puVar23;
      lVar18 = lVar18 + 8;
    } while ((param_5 & 0xffffffff) != uVar21);
  }
  lVar18 = *(long *)(param_2 + 0x170);
  if (param_2 + 0x160 != lVar18) {
    param_5 = (ulong)(int)param_5;
    do {
      auStack_560[param_5] = *(undefined8 *)(lVar18 + 0x38);
      lVar18 = *(long *)(lVar18 + 0x10);
      param_5 = param_5 + 1;
    } while (param_2 + 0x160 != lVar18);
  }
  lVar18 = *(long *)(param_2 + 0x90);
  lVar22 = *(long *)(param_2 + 0x150);
  uVar58 = *(undefined4 *)(param_2 + 0xf4);
  sVar6 = *(short *)(param_2 + 0x66);
  iStack_634 = (int)((ulong)(param_4 - param_3) >> 6) * -0x49249249;
  uVar16 = (uint)(byte)*PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98;
  if (*(char *)(param_2 + 0xde) == '\0') {
    uVar16 = 0;
  }
  do {
    iVar17 = (int)param_5;
    if (iVar17 == 0) {
      iVar24 = 0;
    }
    else {
      iVar24 = *(int *)(param_3 + 0x168);
    }
    if (iVar24 * iVar17 == 0) {
      bVar5 = *(byte *)(param_3 + 0x19c);
    }
    else {
      pauVar2 = (undefined1 (*) [12])(param_3 + 0xb0);
      fVar40 = (float)*(undefined8 *)(param_3 + 0xb8);
      fVar42 = (float)((ulong)*(undefined8 *)(param_3 + 0xb8) >> 0x20);
      fVar54 = (float)*(undefined8 *)*pauVar2;
      fVar55 = (float)((ulong)*(undefined8 *)*pauVar2 >> 0x20);
      auVar52 = *(undefined1 (*) [16])(param_3 + 0xc0);
      pauVar1 = (undefined1 (*) [12])(param_3 + 0xd0);
      fVar69 = (float)*(undefined8 *)(param_3 + 0xd8);
      fVar70 = (float)((ulong)*(undefined8 *)(param_3 + 0xd8) >> 0x20);
      fVar67 = (float)*(undefined8 *)*pauVar1;
      fVar68 = (float)((ulong)*(undefined8 *)*pauVar1 >> 0x20);
      pauVar25 = *(undefined1 (**) [16])(param_3 + 0x160);
      pbVar3 = (byte *)(param_3 + 0x19c);
      auVar71._12_4_ = fVar42;
      auVar71._0_12_ = *pauVar2;
      auVar48._12_4_ = fVar42;
      auVar48._0_12_ = *pauVar2;
      auVar71 = NEON_ext(auVar71,auVar48,8,1);
      fVar66 = auVar52._4_4_;
      fVar65 = auVar52._0_4_;
      fVar47 = auVar52._8_4_;
      fVar43 = auVar52._12_4_;
      fVar56 = fVar54 * fVar66 - fVar55 * fVar65;
      fVar57 = fVar54 * fVar66 - fVar55 * fVar65;
      fVar60 = fVar54 * fVar47 - fVar40 * fVar65;
      fVar61 = fVar54 * fVar47 - fVar40 * fVar65;
      fVar62 = fVar54 * fVar43 - fVar42 * fVar65;
      fVar63 = fVar55 * fVar47 - fVar40 * fVar66;
      fVar64 = fVar55 * fVar47 - fVar40 * fVar66;
      fVar59 = fVar55 * fVar43 - fVar42 * fVar66;
      fVar50 = fVar40 * fVar43 - fVar42 * fVar47;
      fVar42 = (fVar55 * fVar47 - fVar40 * fVar66) * fVar67 +
               ((fVar54 * fVar66 - fVar55 * fVar65) * fVar69 -
               (fVar54 * fVar47 - fVar40 * fVar65) * fVar68);
      fVar43 = (fVar55 * fVar47 - fVar40 * fVar66) * fVar67 +
               ((fVar54 * fVar66 - fVar55 * fVar65) * fVar69 -
               (fVar54 * fVar47 - fVar40 * fVar65) * fVar68);
      fVar44 = fVar63 * fVar67 + (fVar56 * fVar69 - fVar60 * fVar68);
      fVar45 = fVar64 * fVar67 + (fVar57 * fVar69 - fVar61 * fVar68);
      auVar30._4_4_ = fVar43;
      auVar30._0_4_ = fVar42;
      auVar30._8_4_ = fVar44;
      auVar30._12_4_ = fVar45;
      auVar30 = NEON_frecpe(auVar30,4);
      auVar36._4_4_ = fVar43;
      auVar36._0_4_ = fVar42;
      auVar36._8_4_ = fVar44;
      auVar36._12_4_ = fVar45;
      auVar36 = NEON_frecps(auVar30,auVar36,4);
      auVar31._0_4_ = auVar30._0_4_ * auVar36._0_4_;
      auVar31._4_4_ = auVar30._4_4_ * auVar36._4_4_;
      auVar31._8_4_ = auVar30._8_4_ * auVar36._8_4_;
      auVar31._12_4_ = auVar30._12_4_ * auVar36._12_4_;
      auVar49._4_4_ = fVar43;
      auVar49._0_4_ = fVar42;
      auVar49._8_4_ = fVar44;
      auVar49._12_4_ = fVar45;
      auVar30 = NEON_frecps(auVar31,auVar49,4);
      fVar42 = auVar31._0_4_ * auVar30._0_4_;
      fVar43 = auVar31._4_4_ * auVar30._4_4_;
      fVar44 = auVar31._8_4_ * auVar30._8_4_;
      fVar45 = auVar31._12_4_ * auVar30._12_4_;
      auVar36 = NEON_ext(auVar52,auVar52,8,1);
      auVar52._12_4_ = fVar70;
      auVar52._0_12_ = *pauVar1;
      auVar11._12_4_ = fVar70;
      auVar11._0_12_ = *pauVar1;
      auVar30 = NEON_ext(auVar52,auVar11,8,1);
      fVar35 = fVar42 * (fVar66 * fVar69 - fVar47 * fVar68);
      fVar39 = fVar43 * (fVar40 * fVar68 - fVar55 * fVar69);
      fVar63 = fVar44 * fVar63;
      fVar41 = fVar45 * ((fVar59 * fVar69 - fVar50 * fVar68) - fVar64 * fVar70);
      fVar64 = fVar42 * (fVar47 * fVar67 - fVar65 * fVar69);
      fVar40 = fVar43 * (fVar54 * fVar69 - fVar40 * fVar67);
      auVar37._0_8_ = CONCAT44(fVar40,fVar64);
      auVar37._8_4_ = fVar44 * -fVar60;
      auVar37._12_4_ = fVar45 * (fVar61 * fVar70 + (fVar50 * fVar67 - fVar62 * fVar69));
      fVar42 = fVar42 * (fVar65 * fVar68 - fVar66 * fVar67);
      fVar43 = fVar43 * (fVar55 * fVar67 - fVar54 * fVar68);
      fVar44 = fVar44 * fVar56;
      fVar45 = fVar45 * ((fVar62 * fVar68 - fVar59 * fVar67) - fVar57 * fVar70);
      do {
        bVar5 = pauVar25[2][0];
        lVar26 = *(long *)(pauVar25[4] + 8);
        if ((bVar5 & 1) != 0) {
          uStack_e0 = *(undefined4 *)(pauVar25[2] + 4);
          if ((bVar5 >> 3 & 1) == 0) {
            if (0 < iVar17) {
              puVar23 = auStack_560;
              uVar21 = param_5 & 0xffffffff;
              do {
                plVar27 = (long *)*puVar23;
                if ((*(long *)(plVar27[10] + 0x10) != param_2) ||
                   (((*pbVar3 & 1) == 0 && ((*(byte *)(lVar26 + 0x19c) & 1) == 0)))) {
                  auVar49 = *(undefined1 (*) [16])(param_3 + 0x10);
                  auVar28 = auVar49._0_12_;
                  fVar50 = *(float *)(lVar26 + 0x10);
                  fVar56 = *(float *)(lVar26 + 0x14);
                  fVar57 = *(float *)(lVar26 + 0x18);
                  if ((bVar5 >> 2 & 1) != 0) {
                    uVar46 = (undefined4)((ulong)*(undefined8 *)(*pauVar25 + 8) >> 0x20);
                    fVar60 = (float)*(undefined8 *)*pauVar25;
                    fVar62 = (float)((ulong)*(undefined8 *)*pauVar25 >> 0x20);
                    auVar7._12_4_ = uVar46;
                    auVar7._0_12_ = *(undefined1 (*) [12])*pauVar25;
                    auVar8._12_4_ = uVar46;
                    auVar8._0_12_ = *(undefined1 (*) [12])*pauVar25;
                    auVar48 = NEON_ext(auVar7,auVar8,8,1);
                    fVar47 = auVar48._0_4_;
                    fVar59 = fVar54 * fVar60 + auVar71._0_4_ * fVar47 + fVar55 * fVar62 + 0.0;
                    fVar61 = fVar65 * fVar60 + auVar36._0_4_ * fVar47 + fVar66 * fVar62 + 0.0;
                    fVar60 = fVar67 * fVar60 + auVar30._0_4_ * fVar47 + fVar68 * fVar62 + 0.0;
                    auVar28._0_4_ = auVar49._0_4_ + fVar59;
                    auVar28._4_4_ = auVar49._4_4_ + fVar61;
                    auVar28._8_4_ = auVar49._8_4_ + fVar60;
                    fVar50 = fVar50 + fVar59;
                    fVar56 = fVar56 + fVar61;
                    fVar57 = fVar57 + fVar60;
                  }
                  fVar50 = fVar50 - auVar28._0_4_;
                  fVar56 = fVar56 - auVar28._4_4_;
                  fStack_118 = auVar28._8_4_;
                  fVar57 = fVar57 - fStack_118;
                  if ((bVar5 >> 1 & 1) == 0) {
                    uStack_120 = auVar28._0_8_;
                    uStack_114 = 0x3f800000;
                    uStack_110 = CONCAT44(fVar56,fVar50);
                    uStack_108 = CONCAT44(0x3f800000,fVar57);
                    uVar15 = (**(code **)(*plVar27 + 0x80))
                                       (plVar27,auStack_160,bVar5 >> 4 & 1,&uStack_90,&uStack_a0,
                                        &uStack_b0);
                    if ((uVar15 & 1) != 0) {
                      puVar19 = (undefined4 *)plVar27[10];
                      fVar59 = (float)uStack_a0;
code_r0x0242dcf8:
                      auVar51._8_8_ = uVar34;
                      auVar51._0_8_ = param_1._0_8_;
                      void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x1230(fVar59,(float)uStack_b0,*puVar19,puVar19[1],uVar58,auVar51,
                                      pauVar25,param_3,lVar26,&uStack_90);
                      if ((ulong)*(byte *)(param_3 + 0x19e) != 0xff) {
                        *(undefined1 *)(lVar18 + (ulong)*(byte *)(param_3 + 0x19e)) = 1;
                      }
                      if ((ulong)*(byte *)(lVar26 + 0x19e) != 0xff) {
                        *(undefined1 *)(lVar18 + (ulong)*(byte *)(lVar26 + 0x19e)) = 1;
                      }
                      if (*(long *)(plVar27[10] + 0x10) == param_2) {
                        *(byte *)(param_3 + 0x19f) = *(byte *)(param_3 + 0x19f) | 1;
                        *(byte *)(lVar26 + 0x19f) = *(byte *)(lVar26 + 0x19f) | 1;
                      }
                    }
                  }
                  else {
                    fVar59 = *(float *)(pauVar25[3] + 8);
                    fVar60 = *(float *)(pauVar25[3] + 0xc) - fVar59;
                    fStack_118 = fStack_118 + fVar57 * fVar59;
                    auVar49 = NEON_fmov(0x3f800000,4);
                    fVar61 = fVar60 + auVar49._0_4_;
                    uStack_120 = CONCAT44(auVar28._4_4_ + fVar56 * fVar59,
                                          auVar28._0_4_ + fVar50 * fVar59);
                    uStack_110 = CONCAT44(fVar56 * (fVar60 + auVar49._4_4_),fVar50 * fVar61);
                    uStack_114 = 0x3f800000;
                    uStack_108 = CONCAT44(0x3f800000,fVar57 * (fVar60 + auVar49._8_4_));
                    uVar15 = (**(code **)(*plVar27 + 0x80))
                                       (plVar27,auStack_160,bVar5 >> 4 & 1,&uStack_90,&uStack_a0,
                                        &uStack_b0);
                    if ((uVar15 & 1) != 0) {
                      fVar59 = fVar59 + (1.0 - fVar61) * (float)uStack_a0;
                      uStack_a0 = CONCAT44(uStack_a0._4_4_,fVar59);
                      puVar19 = (undefined4 *)plVar27[10];
                      goto code_r0x0242dcf8;
                    }
                  }
                }
                uVar21 = uVar21 - 1;
                puVar23 = puVar23 + 1;
              } while (uVar21 != 0);
            }
          }
          else if (0 < iVar17) {
            puVar23 = auStack_560;
            uVar21 = param_5 & 0xffffffff;
            do {
              plVar27 = (long *)*puVar23;
              uStack_88 = CONCAT44(fVar41,fVar63);
              uStack_90 = CONCAT44(fVar39,fVar35);
              uStack_98 = auVar37._8_8_;
              uStack_a0 = auVar37._0_8_;
              uStack_b0 = CONCAT44(fVar43,fVar42);
              auVar12._8_4_ = fVar44;
              auVar12._0_8_ = uStack_b0;
              auVar12._12_4_ = fVar45;
              uStack_a8 = auVar12._8_8_;
              if ((*(long *)(plVar27[10] + 0x10) != param_2) ||
                 (((*pbVar3 & 1) == 0 && ((*(byte *)(lVar26 + 0x19c) & 1) == 0)))) {
                fVar50 = *(float *)(lVar26 + 0x10);
                fVar56 = *(float *)(lVar26 + 0x14);
                fVar57 = *(float *)(lVar26 + 0x18);
                fVar59 = *(float *)(lVar26 + 0x1c);
                auVar38._0_4_ = fVar35 * fVar50;
                auVar38._4_4_ = fVar39 * fVar56;
                auVar38._8_4_ = fVar63 * fVar57;
                auVar38._12_4_ = fVar41 * fVar59;
                fVar60 = fVar64 * fVar50;
                fVar61 = fVar40 * fVar56;
                auVar32._0_4_ = fVar42 * fVar50;
                auVar32._4_4_ = fVar43 * fVar56;
                auVar32._8_4_ = fVar44 * fVar57;
                auVar32._12_4_ = fVar45 * fVar59;
                auVar49 = NEON_ext(auVar38,auVar38,8,1);
                auVar9._4_4_ = fVar61;
                auVar9._0_4_ = fVar60;
                auVar9._8_4_ = auVar37._8_4_ * fVar57;
                auVar9._12_4_ = auVar37._12_4_ * fVar59;
                auVar10._4_4_ = fVar61;
                auVar10._0_4_ = fVar60;
                auVar10._8_4_ = auVar37._8_4_ * fVar57;
                auVar10._12_4_ = auVar37._12_4_ * fVar59;
                auVar48 = NEON_ext(auVar9,auVar10,8,1);
                auVar52 = NEON_ext(auVar32,auVar32,8,1);
                fVar50 = auVar49._0_4_ + auVar38._0_4_ + auVar49._4_4_ + auVar38._4_4_;
                fVar57 = auVar48._0_4_ + fVar60 + auVar48._4_4_ + fVar61;
                auVar33._4_4_ = fVar57;
                auVar33._0_4_ = fVar50;
                fVar56 = auVar52._0_4_ + auVar32._0_4_ + auVar52._4_4_ + auVar32._4_4_;
                auVar33._12_4_ = 0x3f800000;
                auVar33._8_4_ = fVar56;
                auVar29 = auVar33._0_12_;
                if ((bVar5 >> 2 & 1) == 0) {
                  auVar28 = _UNK_027dbb30;
                  if ((bVar5 >> 1 & 1) == 0) goto code_r0x0242de8c;
code_r0x0242de14:
                  fVar56 = *(float *)(pauVar25[3] + 8);
                  uStack_120 = CONCAT44(auVar28._4_4_ + auVar29._4_4_ * fVar56,
                                        auVar28._0_4_ + auVar29._0_4_ * fVar56);
                  fStack_118 = auVar28._8_4_ + auVar29._8_4_ * fVar56;
                  fVar56 = *(float *)(pauVar25[3] + 0xc) - fVar56;
                  auVar49 = NEON_fmov(0x3f800000,4);
                  fVar50 = auVar29._8_4_ * (fVar56 + auVar49._8_4_);
                  uStack_110 = CONCAT44(auVar29._4_4_ * (fVar56 + auVar49._4_4_),
                                        auVar29._0_4_ * (fVar56 + auVar49._0_4_));
                }
                else {
                  auVar49 = *pauVar25;
                  auVar28 = auVar49._0_12_;
                  auVar29._0_4_ = fVar50 + auVar49._0_4_;
                  auVar29._4_4_ = fVar57 + auVar49._4_4_;
                  auVar29._8_4_ = fVar56 + auVar49._8_4_;
                  if ((bVar5 >> 1 & 1) != 0) goto code_r0x0242de14;
code_r0x0242de8c:
                  uStack_120 = auVar28._0_8_;
                  fStack_118 = auVar28._8_4_;
                  uStack_110 = auVar29._0_8_;
                  fVar50 = auVar29._8_4_;
                }
                uStack_108 = CONCAT44(0x3f800000,fVar50);
                uStack_114 = 0x3f800000;
                uVar15 = (**(code **)(*plVar27 + 0x88))
                                   (plVar27,&uStack_90,&uStack_a0,&uStack_b0,auStack_160,
                                    bVar5 >> 4 & 1,pauVar25 + 1,&fStack_c0,&uStack_c4,&uStack_c8);
                if ((uVar15 & 1) != 0) {
                  auVar13._4_4_ = fStack_bc;
                  auVar13._0_4_ = fStack_c0;
                  auVar13._8_8_ = uStack_b8;
                  auVar49 = NEON_ext(auVar13,auVar13,8,1);
                  fVar59 = fVar65 * fStack_c0;
                  fVar50 = fVar67 * fStack_c0;
                  fVar56 = fVar68 * fStack_bc;
                  fVar57 = auVar49._0_4_;
                  fStack_c0 = fVar54 * fStack_c0 + auVar71._0_4_ * fVar57 + fVar55 * fStack_bc + 0.0
                  ;
                  fStack_bc = fVar59 + auVar36._0_4_ * fVar57 + fVar66 * fStack_bc + 0.0;
                  uStack_b8 = CONCAT44(0x3f800000,fVar50 + auVar30._0_4_ * fVar57 + fVar56 + 0.0);
                  auVar53._8_8_ = uVar34;
                  auVar53._0_8_ = param_1._0_8_;
                  void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x1230(uStack_c4,uStack_c8,*(undefined4 *)plVar27[10],
                                  ((undefined4 *)plVar27[10])[1],uVar58,auVar53,pauVar25,param_3,
                                  lVar26,&fStack_c0);
                  if ((ulong)*(byte *)(param_3 + 0x19e) != 0xff) {
                    *(undefined1 *)(lVar18 + (ulong)*(byte *)(param_3 + 0x19e)) = 1;
                  }
                  if ((ulong)*(byte *)(lVar26 + 0x19e) != 0xff) {
                    *(undefined1 *)(lVar18 + (ulong)*(byte *)(lVar26 + 0x19e)) = 1;
                  }
                  if (*(long *)(plVar27[10] + 0x10) == param_2) {
                    *(byte *)(param_3 + 0x19f) = *(byte *)(param_3 + 0x19f) | 1;
                    *(byte *)(lVar26 + 0x19f) = *(byte *)(lVar26 + 0x19f) | 1;
                  }
                }
              }
              uVar21 = uVar21 - 1;
              puVar23 = puVar23 + 1;
            } while (uVar21 != 0);
          }
        }
        if ((*(char *)(param_3 + 0x19f) != '\0') || (*(char *)(lVar26 + 0x19f) != '\0')) {
          if (*(long *)(lVar26 + 400) == *(long *)pauVar25[4]) {
            *(byte *)(lVar26 + 0x19f) = *(byte *)(lVar26 + 0x19f) | 2;
          }
          if (*(long *)(param_3 + 400) == *(long *)(pauVar25[4] + 8)) {
            *(byte *)(param_3 + 0x19f) = *(byte *)(param_3 + 0x19f) | 2;
          }
          void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x1d0(*(undefined4 *)(pauVar25[2] + 8),*(undefined4 *)(pauVar25[3] + 4),
                          param_1._0_4_,pauVar25[2][1],param_3,lVar26);
        }
        iVar24 = iVar24 + -1;
        pauVar25 = pauVar25 + 5;
      } while (iVar24 != 0);
      bVar5 = *pbVar3;
    }
    if ((bVar5 & 1) == 0) {
      if (((sVar6 != 0) && ((*(byte *)(param_3 + 0x19d) >> 3 & 1) != 0)) &&
         (uVar4 = *(uint *)(param_3 + 0x158), uVar4 != 0)) {
        uVar21 = 0;
        do {
          plVar27 = *(long **)(lVar22 + (ulong)*(byte *)(*(long *)(param_3 + 0x150) + uVar21) * 8);
          if ((plVar27 != (long *)0x0) &&
             (uVar15 = (**(code **)(*plVar27 + 0x98))(plVar27,param_3 + 0x10,&uStack_a0),
             (uVar15 & 1) != 0)) {
            *(undefined8 *)(param_3 + 0x18) = uStack_98;
            *(undefined8 *)(param_3 + 0x10) = uStack_a0;
            *(float *)(param_3 + 0x18c) = *(float *)(param_3 + 0x18c) + *(float *)plVar27[10];
            if ((ulong)*(byte *)(param_3 + 0x19e) != 0xff) {
              *(undefined1 *)(lVar18 + (ulong)*(byte *)(param_3 + 0x19e)) = 1;
            }
            if (*(long *)(plVar27[10] + 0x10) == param_2) {
              *(byte *)(param_3 + 0x19f) = *(byte *)(param_3 + 0x19f) | 1;
            }
          }
          uVar21 = uVar21 + 1;
        } while (uVar4 != uVar21);
      }
      if (uVar16 != 0) {
        uVar21 = (ulong)uVar16;
        plVar27 = (long *)
                  PTR__ZN4Aska30ArticulatedDynamicsManagerBase22m_pWorldConstraintListE_02cbc740;
        do {
          uVar15 = (**(code **)(*(long *)*plVar27 + 0x98))
                             ((long *)*plVar27,param_3 + 0x10,&uStack_a0);
          if ((uVar15 & 1) != 0) {
            *(undefined8 *)(param_3 + 0x18) = uStack_98;
            *(undefined8 *)(param_3 + 0x10) = uStack_a0;
            *(float *)(param_3 + 0x18c) =
                 *(float *)(param_3 + 0x18c) + **(float **)(*plVar27 + 0x50);
            if ((ulong)*(byte *)(param_3 + 0x19e) != 0xff) {
              *(undefined1 *)(lVar18 + (ulong)*(byte *)(param_3 + 0x19e)) = 1;
            }
          }
          uVar21 = uVar21 - 1;
          plVar27 = plVar27 + 1;
        } while (uVar21 != 0);
      }
      if ((!bVar14) && ((*(byte *)(param_3 + 0x19d) >> 4 & 1) != 0)) {
        uStack_90 = CONCAT44(*(float *)(param_3 + 0x14) - *(float *)(param_3 + 0x188),
                             *(undefined4 *)(param_3 + 0x10));
        uStack_88 = CONCAT44(0x3f800000,*(undefined4 *)(param_3 + 0x18));
        uVar21 = (**(code **)(*plVar20 + 0x18))(plVar20,&uStack_90,&uStack_b0,&fStack_c0,0);
        if ((uVar21 & 1) != 0) {
          *(float *)(param_3 + 0x14) = (float)uStack_b0 + *(float *)(param_3 + 0x188);
          *(float *)(param_3 + 0x18c) = *(float *)(param_3 + 0x18c) + fStack_c0;
          if ((ulong)*(byte *)(param_3 + 0x19e) != 0xff) {
            *(undefined1 *)(lVar18 + (ulong)*(byte *)(param_3 + 0x19e)) = 1;
          }
        }
      }
    }
    param_3 = param_3 + 0x1c0;
    iStack_634 = iStack_634 + -1;
    if (iStack_634 == 0) {
      return;
    }
  } while( true );
}

// ==== void Aska::ArticulatedDynamicsManagerBase::StandardIK<Aska::ArticulatedDynamicsManagerMP, true>(Aska::ArticulatedDynamicsManagerMP*, float, float, int)
// vaddr 0x232e268 | ghidra 0x242e268 | size 1052 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase10StandardIKINS_28ArticulatedDynamicsManagerMPELb1EEEvPT_ffi | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska30ArticulatedDynamicsManagerBase10StandardIKINS_28ArticulatedDynamicsManagerMPELb1EEEvPT_ffi
               (undefined8 param_1,undefined8 param_2,long param_3,undefined4 param_4)

{
  undefined8 *puVar1;
  uint uVar2;
  float fVar3;
  float fVar4;
  char cVar5;
  byte bVar6;
  float fVar7;
  float fVar8;
  float *pfVar9;
  float *pfVar10;
  long lVar11;
  ulong uVar12;
  int *piVar13;
  float *pfVar14;
  long lVar15;
  float *pfVar16;
  long lVar17;
  float *pfVar18;
  int iVar19;
  long lVar20;
  float *pfVar21;
  float *pfVar22;
  long lVar23;
  float *pfVar24;
  float *pfVar25;
  float *pfVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  undefined4 uVar29;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined1 auStack_d0 [64];
  
  fVar8 = _UNK_0286c774;
  fVar7 = _UNK_02807bf4;
  uVar2 = *(uint *)(param_3 + 0xb0);
  if (0 < (int)uVar2) {
    uVar12 = 0;
    uVar29 = *(undefined4 *)(param_3 + 0xf0);
    piVar13 = *(int **)(param_3 + 0xa8);
    do {
      lVar17 = (long)*piVar13;
      lVar15 = *(long *)(param_3 + 0x70);
      lVar23 = *(long *)(param_3 + 0xa0);
      iVar19 = piVar13[1];
      pfVar26 = (float *)(lVar15 + lVar17 * 0x1c0);
      cVar5 = *(char *)(param_3 + 0xdc);
      lVar20 = lVar23 + uVar12 * 0xa0;
      pfVar21 = pfVar26 + 0x2c;
      if ((*(byte *)((long)pfVar26 + 0x19d) >> 5 & 1) != 0) {
        lVar11 = lVar15 + lVar17 * 0x1c0;
        *(undefined8 *)(lVar11 + 0x108) = *(undefined8 *)(lVar11 + 0x78);
        *(undefined8 *)(lVar11 + 0x100) = *(undefined8 *)(lVar11 + 0x70);
      }
      if ((*(char *)(lVar15 + lVar17 * 0x1c0 + 0x198) == '\0') &&
         ((*(byte *)(lVar15 + lVar17 * 0x1c0 + 0x19c) & 1) == 0)) {
        lVar11 = lVar15 + lVar17 * 0x1c0;
        puVar1 = (undefined8 *)(lVar11 + 0x10);
        if (lVar20 == 0) {
          uVar28 = *(undefined8 *)(lVar11 + 0x18);
          uVar27 = *puVar1;
        }
        else {
          Aska::Matrix::InvertLowError(Aska::Matrix*) const(lVar20,auStack_d0);
          Aska::Matrix::ApplyVector(Aska::Vector*, Aska::Vector const*) const(auStack_d0,&uStack_e0,puVar1);
          uVar27 = uStack_e0;
          uVar28 = uStack_d8;
        }
        lVar11 = lVar15 + lVar17 * 0x1c0;
        *(undefined8 *)(lVar11 + 0xf8) = uVar28;
        *(undefined8 *)(lVar11 + 0xf0) = uVar27;
      }
      lVar11 = lVar15 + lVar17 * 0x1c0;
      lVar23 = lVar23 + uVar12 * 0xa0 + 0x60;
      if (lVar20 == 0) {
        lVar23 = 0;
      }
      Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar21,lVar11 + 0xf0,lVar11 + 0x100,lVar11 + 0x120,lVar11 + 0x110,lVar23,
                      lVar20);
      if (iVar19 == 1) {
        bVar6 = *(byte *)(pfVar26 + 0x67);
        pfVar14 = pfVar26;
      }
      else {
        iVar19 = 1 - iVar19;
        pfVar9 = (float *)(lVar15 + lVar17 * 0x1c0 + 0x378);
        pfVar22 = pfVar26;
        pfVar24 = pfVar21;
        do {
          pfVar18 = pfVar9;
          pfVar25 = *(float **)(pfVar18 + -10);
          pfVar14 = pfVar18 + -0x6e;
          lVar15 = *(long *)(pfVar25 + 0x4c);
          pfVar9 = pfVar25 + 0x2c;
          if ((*(byte *)((long)pfVar18 + -0x19) >> 1 & 1) != 0) {
            fVar3 = *pfVar18 * fVar7;
            if (*pfVar18 * fVar7 <= fVar8) {
              fVar3 = fVar8;
            }
            *pfVar18 = fVar3;
          }
          pfVar21 = pfVar18 + -0x42;
          if ((*(byte *)(pfVar18 + -7) & 1) == 0 && *(char *)(pfVar18 + -8) == '\0') {
            Aska::Matrix::InvertLowError(Aska::Matrix*) const(pfVar9,auStack_d0);
            Aska::Matrix::ApplyVector(Aska::Vector*, Aska::Vector const*) const(auStack_d0,&uStack_e0,pfVar18 + -0x6a);
            *(undefined8 *)(pfVar18 + -0x30) = uStack_d8;
            *(undefined8 *)(pfVar18 + -0x32) = uStack_e0;
            bVar6 = *(byte *)((long)pfVar18 + -0x1b);
            pfVar16 = (float *)0x0;
joined_r0x0242e484:
            if ((bVar6 >> 5 & 1) == 0) goto code_r0x0242e488;
code_r0x0242e580:
            pfVar10 = pfVar26 + 0xb0;
            *(undefined8 *)(pfVar18 + -0x2c) = *(undefined8 *)(pfVar18 + -0x50);
            *(undefined8 *)(pfVar18 + -0x2e) = *(undefined8 *)(pfVar18 + -0x52);
          }
          else {
            if ((*(byte *)(pfVar18 + -7) >> 1 & 1) != 0) {
              lVar17 = lVar15 + 0x60;
              if (lVar15 == 0) {
                lVar17 = 0;
              }
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar9);
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar21,pfVar18 + -0x32,pfVar18 + -0x2e,pfVar18 + -0x26,
                              pfVar18 + -0x2a,pfVar25 + 0x44,pfVar9);
              void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x5b4(uVar29,param_1,pfVar25,pfVar9,pfVar14,pfVar21,param_4);
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar9,pfVar25 + 0x3c,pfVar25 + 0x40,pfVar25 + 0x48,pfVar25 + 0x44,
                              lVar17,lVar15);
              if (((uint)pfVar25[0x67] & 1) == 0) {
                pfVar25[4] = pfVar25[0x2f];
                pfVar25[5] = pfVar25[0x33];
                pfVar25[6] = pfVar25[0x37];
                pfVar25[7] = 1.0;
              }
              void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x14c0(param_2,pfVar25,pfVar9,cVar5 != '\0');
              bVar6 = *(byte *)((long)pfVar18 + -0x1b);
              pfVar16 = pfVar25;
              goto joined_r0x0242e484;
            }
            pfVar16 = (float *)0x0;
            if ((*(byte *)((long)pfVar18 + -0x1b) >> 5 & 1) != 0) goto code_r0x0242e580;
code_r0x0242e488:
            pfVar10 = pfVar18 + -0x2e;
          }
          pfVar26 = pfVar26 + 0x70;
          Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar21,pfVar18 + -0x32,pfVar10,pfVar18 + -0x26,pfVar18 + -0x2a,
                          pfVar25 + 0x44,pfVar9);
          if (pfVar16 != pfVar22) {
            if (((uint)pfVar22[0x67] & 1) == 0) {
              fVar3 = pfVar24[7];
              fVar4 = pfVar24[0xb];
              pfVar22[4] = pfVar24[3];
              pfVar22[5] = fVar3;
              pfVar22[6] = fVar4;
              pfVar22[7] = 1.0;
            }
            void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x14c0(param_2,pfVar22,pfVar24,cVar5 != '\0');
          }
          iVar19 = iVar19 + 1;
          pfVar9 = pfVar18 + 0x70;
          pfVar22 = pfVar14;
          pfVar24 = pfVar21;
        } while (iVar19 != 0);
        bVar6 = *(byte *)(pfVar18 + -7);
      }
      if ((bVar6 & 1) == 0) {
        fVar3 = pfVar21[7];
        fVar4 = pfVar21[0xb];
        pfVar14[4] = pfVar21[3];
        pfVar14[5] = fVar3;
        pfVar14[6] = fVar4;
        pfVar14[7] = 1.0;
      }
      void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x14c0(param_2,pfVar14,pfVar21,cVar5 != '\0');
      uVar12 = uVar12 + 1;
      piVar13 = piVar13 + 2;
    } while (uVar12 != uVar2);
  }
  return;
}

// ==== void Aska::ArticulatedDynamicsManagerBase::Finalize<Aska::ArticulatedDynamicsManagerMP>(Aska::ArticulatedDynamicsManagerMP*, float, float, int)
// vaddr 0x232e684 | ghidra 0x242e684 | size 1188 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase8FinalizeINS_28ArticulatedDynamicsManagerMPEEEvPT_ffi | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska30ArticulatedDynamicsManagerBase8FinalizeINS_28ArticulatedDynamicsManagerMPEEEvPT_ffi
               (undefined1 param_1 [16],undefined1 param_2 [16],long param_3)

{
  undefined8 *puVar1;
  float *pfVar2;
  uint uVar3;
  float fVar4;
  char cVar5;
  byte bVar6;
  undefined8 uVar7;
  float fVar8;
  float fVar9;
  float *pfVar10;
  float *pfVar11;
  long lVar12;
  float *pfVar13;
  int iVar14;
  long lVar15;
  float *pfVar16;
  float *pfVar17;
  long lVar18;
  long lVar19;
  float *pfVar20;
  long lVar21;
  ulong uVar22;
  int *piVar23;
  float *pfVar24;
  float fVar25;
  float fVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  
  fVar9 = _UNK_0286c774;
  fVar8 = _UNK_02807bf4;
  uVar3 = *(uint *)(param_3 + 0xb0);
  uVar7 = param_2._0_8_;
  if (0 < (int)uVar3) {
    piVar23 = *(int **)(param_3 + 0xa8);
    fVar25 = param_2._0_4_ * _UNK_029e2c84 * 0.5;
    uVar22 = 0;
    if (fVar25 <= 1.0) {
      fVar25 = 1.0;
    }
    do {
      iVar14 = piVar23[1];
      lVar18 = *(long *)(param_3 + 0x70);
      cVar5 = *(char *)(param_3 + 0xdc);
      lVar19 = (long)*piVar23;
      pfVar13 = (float *)(lVar18 + lVar19 * 0x1c0);
      pfVar17 = pfVar13 + 0x2c;
      if (*(char *)(*(long *)(param_3 + 0x90) + (ulong)*(byte *)((long)pfVar13 + 0x19e)) == '\0') {
        if (iVar14 != 1) {
          iVar14 = 1 - iVar14;
          pfVar16 = (float *)(lVar18 + lVar19 * 0x1c0 + 0x378);
          pfVar10 = pfVar13;
          pfVar11 = pfVar17;
          do {
            pfVar13 = pfVar16 + -0x6e;
            pfVar17 = pfVar16 + -0x42;
            if ((*(byte *)((long)pfVar16 + -0x19) >> 1 & 1) != 0) {
              fVar26 = *(float *)(*(long *)(pfVar16 + -10) + 0x1b8) * fVar8;
              if (fVar26 <= fVar9) {
                fVar26 = fVar9;
              }
              *pfVar16 = fVar26;
            }
            if (pfVar10 != (float *)0x0) {
              void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x14c0(uVar7,pfVar10,pfVar11,cVar5 != '\0');
            }
            iVar14 = iVar14 + 1;
            pfVar16 = pfVar16 + 0x70;
            pfVar10 = pfVar13;
            pfVar11 = pfVar17;
          } while (iVar14 != 0);
        }
        void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x14c0(uVar7,pfVar13,pfVar17,cVar5 != '\0');
      }
      else {
        lVar21 = *(long *)(param_3 + 0xa0);
        lVar15 = lVar21 + uVar22 * 0xa0;
        if ((*(char *)(lVar18 + lVar19 * 0x1c0 + 0x198) == '\0') &&
           ((*(byte *)(lVar18 + lVar19 * 0x1c0 + 0x19c) & 1) == 0)) {
          lVar12 = lVar18 + lVar19 * 0x1c0;
          puVar1 = (undefined8 *)(lVar12 + 0x10);
          if (lVar15 == 0) {
            uVar28 = *(undefined8 *)(lVar12 + 0x18);
            uVar27 = *puVar1;
          }
          else {
            Aska::Matrix::InvertLowError(Aska::Matrix*) const(lVar15,&uStack_c0);
            Aska::Matrix::ApplyVector(Aska::Vector*, Aska::Vector const*) const(&uStack_c0,&uStack_d0,puVar1);
            uVar27 = uStack_d0;
            uVar28 = uStack_c8;
          }
          lVar12 = lVar18 + lVar19 * 0x1c0;
          *(undefined8 *)(lVar12 + 0xf8) = uVar28;
          *(undefined8 *)(lVar12 + 0xf0) = uVar27;
        }
        lVar12 = lVar18 + lVar19 * 0x1c0;
        lVar21 = lVar21 + uVar22 * 0xa0 + 0x60;
        if (lVar15 == 0) {
          lVar21 = 0;
        }
        Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar17,lVar12 + 0xf0,lVar12 + 0x100,lVar12 + 0x120,lVar12 + 0x110,lVar21,
                        lVar15);
        if (iVar14 == 1) {
          bVar6 = *(byte *)(pfVar13 + 0x67);
        }
        else {
          iVar14 = 1 - iVar14;
          pfVar16 = pfVar13;
          pfVar10 = pfVar17;
          pfVar11 = (float *)(lVar18 + lVar19 * 0x1c0 + 0x378);
          do {
            pfVar24 = pfVar11;
            pfVar20 = *(float **)(pfVar24 + -10);
            pfVar13 = pfVar24 + -0x6e;
            lVar18 = *(long *)(pfVar20 + 0x4c);
            pfVar11 = pfVar20 + 0x2c;
            if ((*(byte *)((long)pfVar24 + -0x19) >> 1 & 1) != 0) {
              fVar26 = pfVar20[0x6e] * fVar8;
              if (fVar26 <= fVar9) {
                fVar26 = fVar9;
              }
              *pfVar24 = fVar26;
            }
            pfVar17 = pfVar24 + -0x42;
            if ((*(byte *)(pfVar24 + -7) & 1) == 0 && *(char *)(pfVar24 + -8) == '\0') {
              Aska::Matrix::InvertLowError(Aska::Matrix*) const(pfVar11,&uStack_c0);
              Aska::Matrix::ApplyVector(Aska::Vector*, Aska::Vector const*) const(&uStack_c0,&uStack_d0,pfVar24 + -0x6a);
              *(undefined8 *)(pfVar24 + -0x30) = uStack_c8;
              *(undefined8 *)(pfVar24 + -0x32) = uStack_d0;
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar17,pfVar24 + -0x32,pfVar24 + -0x2e,pfVar24 + -0x26,
                              pfVar24 + -0x2a,pfVar20 + 0x44,pfVar11);
              pfVar20 = (float *)0x0;
            }
            else if ((*(byte *)(pfVar24 + -7) >> 1 & 1) == 0) {
              pfVar20 = (float *)0x0;
            }
            else {
              lVar19 = lVar18 + 0x60;
              pfVar2 = pfVar20 + 0x44;
              if (lVar18 == 0) {
                lVar19 = 0;
              }
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar11,pfVar20 + 0x3c,pfVar20 + 0x40,pfVar20 + 0x48,pfVar2,lVar19,
                              lVar18);
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar17);
              void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x8c8(fVar25,&uStack_c0,pfVar11,pfVar13,pfVar17);
              *(undefined8 *)(pfVar20 + 0x42) = uStack_b8;
              *(undefined8 *)(pfVar20 + 0x40) = uStack_c0;
              *(byte *)((long)pfVar24 + -0x19) =
                   *(byte *)((long)pfVar24 + -0x19) | *(byte *)((long)pfVar20 + 0x19f) & 1;
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar11,pfVar20 + 0x3c,pfVar20 + 0x40,pfVar20 + 0x48,pfVar2,lVar19,
                              lVar18);
              if (((uint)pfVar20[0x67] & 1) == 0) {
                pfVar20[4] = pfVar20[0x2f];
                pfVar20[5] = pfVar20[0x33];
                pfVar20[6] = pfVar20[0x37];
                pfVar20[7] = 1.0;
              }
              void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x14c0(uVar7,pfVar20,pfVar11,cVar5 != '\0');
              Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(pfVar17,pfVar24 + -0x32,pfVar24 + -0x2e,pfVar24 + -0x26,
                              pfVar24 + -0x2a,pfVar2,pfVar11);
            }
            if (pfVar20 != pfVar16) {
              if (((uint)pfVar16[0x67] & 1) == 0) {
                fVar26 = pfVar10[7];
                fVar4 = pfVar10[0xb];
                pfVar16[4] = pfVar10[3];
                pfVar16[5] = fVar26;
                pfVar16[6] = fVar4;
                pfVar16[7] = 1.0;
              }
              void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x14c0(uVar7,pfVar16,pfVar10,cVar5 != '\0');
            }
            iVar14 = iVar14 + 1;
            pfVar16 = pfVar13;
            pfVar10 = pfVar17;
            pfVar11 = pfVar24 + 0x70;
          } while (iVar14 != 0);
          bVar6 = *(byte *)(pfVar24 + -7);
        }
        if ((bVar6 & 1) == 0) {
          fVar26 = pfVar17[7];
          fVar4 = pfVar17[0xb];
          pfVar13[4] = pfVar17[3];
          pfVar13[5] = fVar26;
          pfVar13[6] = fVar4;
          pfVar13[7] = 1.0;
        }
        void Functor_ExternalForceEmitterCalculation<Aska::ArticulatedDynamicsManagerMP, Aska::DynamicsForceEmitter>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::DynamicsForceEmitter**, unsigned int, float, unsigned int)+0x14c0(uVar7,pfVar13,pfVar17,cVar5 != '\0');
      }
      uVar22 = uVar22 + 1;
      piVar23 = piVar23 + 2;
    } while (uVar22 != uVar3);
  }
  return;
}

// ==== void Aska::ArticulatedDynamicsManagerBase::InterpolateRoot<Aska::ArticulatedDynamicsManagerMP>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::ADMJoint*, float, unsigned int, unsigned int)
// vaddr 0x232eb28 | ghidra 0x242eb28 | size 604 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase15InterpolateRootINS_28ArticulatedDynamicsManagerMPEEEvPT_PNS_8ADMJointES6_fjj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase15InterpolateRootINS_28ArticulatedDynamicsManagerMPEEEvPT_PNS_8ADMJointES6_fjj
               (long param_1,long param_2,undefined8 param_3,uint param_4,int param_5)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  long lVar4;
  long lVar5;
  int iVar6;
  ulong uVar7;
  uint *puVar8;
  int iVar9;
  int iVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined1 auStack_c0 [64];
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  undefined4 uStack_74;
  
  if (1 < param_4) {
    if (param_4 - param_5 == 1) {
      iVar10 = *(int *)(param_1 + 0xb0);
      if (0 < iVar10) {
        puVar8 = *(uint **)(param_1 + 0xa8);
        iVar6 = 0;
        do {
          uVar3 = (ulong)*puVar8;
          if ((*(byte *)(param_2 + uVar3 * 0x1c0 + 0x19c) & 1) != 0) {
            uVar1 = puVar8[1];
            lVar5 = param_2 + uVar3 * 0x1c0;
            *(undefined8 *)(lVar5 + 0xf8) = *(undefined8 *)(lVar5 + 0x48);
            *(undefined8 *)(lVar5 + 0xf0) = *(undefined8 *)(lVar5 + 0x40);
            if (uVar1 != 1) {
              iVar9 = 1 - uVar1;
              lVar5 = param_2 + 0xb0 + uVar3 * 0x1c0;
              do {
                lVar4 = *(long *)(lVar5 + 0x80) + 0x60;
                if (*(long *)(lVar5 + 0x80) == 0) {
                  lVar4 = 0;
                }
                Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(lVar5,lVar5 + 0x40,lVar5 + 0x50,lVar5 + 0x70,lVar5 + 0x60,lVar4);
                iVar9 = iVar9 + 1;
                lVar5 = lVar5 + 0x1c0;
              } while (iVar9 != 0);
            }
          }
          iVar6 = iVar6 + 1;
          puVar8 = puVar8 + 2;
        } while (iVar6 != iVar10);
      }
    }
    else {
      uVar1 = *(uint *)(param_1 + 0xb0);
      if (0 < (int)uVar1) {
        puVar8 = *(uint **)(param_1 + 0xa8);
        fVar14 = 1.0 / (float)(int)(param_4 - param_5);
        uVar3 = 0;
        fVar15 = 1.0 - fVar14;
        do {
          uVar7 = (ulong)*puVar8;
          if ((*(byte *)(param_2 + uVar7 * 0x1c0 + 0x19c) & 1) != 0) {
            uVar2 = puVar8[1];
            lVar5 = *(long *)(param_1 + 0xa0) + uVar3 * 0xa0;
            lVar4 = param_2 + uVar7 * 0x1c0;
            if (param_5 == 0) {
              fVar11 = *(float *)(lVar4 + 0xbc);
              fVar12 = *(float *)(lVar4 + 0xcc);
              fVar13 = *(float *)(lVar4 + 0xdc);
              *(undefined8 *)(lVar4 + 0x48) = *(undefined8 *)(lVar4 + 0xf8);
              *(undefined8 *)(lVar4 + 0x40) = *(undefined8 *)(lVar4 + 0xf0);
              *(float *)(lVar4 + 0x30) = fVar11;
              *(float *)(lVar4 + 0x34) = fVar12;
              *(float *)(lVar4 + 0x38) = fVar13;
              *(undefined4 *)(lVar4 + 0x3c) = 0x3f800000;
            }
            else {
              fVar11 = *(float *)(lVar4 + 0x30);
              fVar12 = *(float *)(lVar4 + 0x34);
              fVar13 = *(float *)(lVar4 + 0x38);
            }
            lVar4 = param_2 + uVar7 * 0x1c0;
            uStack_74 = *(undefined4 *)(lVar4 + 0x1c);
            fStack_80 = fVar14 * fVar11 + fVar15 * *(float *)(lVar4 + 0x10);
            fStack_7c = fVar14 * fVar12 + fVar15 * *(float *)(lVar4 + 0x14);
            fStack_78 = fVar14 * fVar13 + fVar15 * *(float *)(lVar4 + 0x18);
            if (lVar5 != 0) {
              Aska::Matrix::InvertLowError(Aska::Matrix*) const(lVar5,auStack_c0);
              Aska::Vector::ApplyMatrix(Aska::Matrix const*)(&fStack_80,auStack_c0);
              lVar5 = param_2 + uVar7 * 0x1c0;
              *(ulong *)(lVar5 + 0xf8) = CONCAT44(uStack_74,fStack_78);
              *(ulong *)(lVar5 + 0xf0) = CONCAT44(fStack_7c,fStack_80);
            }
            if (uVar2 != 1) {
              iVar10 = 1 - uVar2;
              lVar5 = param_2 + 0xb0 + uVar7 * 0x1c0;
              do {
                lVar4 = *(long *)(lVar5 + 0x80) + 0x60;
                if (*(long *)(lVar5 + 0x80) == 0) {
                  lVar4 = 0;
                }
                Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(lVar5,lVar5 + 0x40,lVar5 + 0x50,lVar5 + 0x70,lVar5 + 0x60,lVar4);
                iVar10 = iVar10 + 1;
                lVar5 = lVar5 + 0x1c0;
              } while (iVar10 != 0);
            }
          }
          uVar3 = uVar3 + 1;
          puVar8 = puVar8 + 2;
        } while (uVar3 != uVar1);
      }
    }
  }
  return;
}

// ==== void Aska::ArticulatedDynamicsManagerBase::CollisionSetting<Aska::ArticulatedDynamicsManagerMP>(Aska::ArticulatedDynamicsManagerMP*, unsigned int, unsigned int)
// vaddr 0x232ed84 | ghidra 0x242ed84 | size 392 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase16CollisionSettingINS_28ArticulatedDynamicsManagerMPEEEvPT_jj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase16CollisionSettingINS_28ArticulatedDynamicsManagerMPEEEvPT_jj
               (long param_1,uint param_2,int param_3)

{
  int iVar1;
  long *plVar2;
  long *plVar3;
  long lVar4;
  ulong uVar5;
  float fVar6;
  
  plVar3 = *(long **)(param_1 + 0x148);
  iVar1 = param_2 - param_3;
  fVar6 = (float)(param_3 + 1) / (float)param_2;
  if ((plVar3 != (long *)0x0) && ((long)*(short *)(param_1 + 100) != 0)) {
    uVar5 = (long)*(short *)(param_1 + 100) & 0xffffffff;
    do {
      plVar2 = (long *)*plVar3;
      if (plVar2 != (long *)0x0) {
        (**(code **)(*plVar2 + 0x70))(fVar6,plVar2,iVar1 == 1);
      }
      uVar5 = uVar5 - 1;
      plVar3 = plVar3 + 1;
    } while (uVar5 != 0);
  }
  plVar3 = (long *)PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_pWorldCollisionListE_02cc4750;
  for (uVar5 = (ulong)(byte)*
                            PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0
      ; uVar5 != 0; uVar5 = uVar5 - 1) {
    plVar2 = (long *)*plVar3;
    if (plVar2 != (long *)0x0) {
      (**(code **)(*plVar2 + 0x70))(fVar6,plVar2,iVar1 == 1);
    }
    plVar3 = plVar3 + 1;
  }
  for (lVar4 = *(long *)(param_1 + 0x170); param_1 + 0x160 != lVar4; lVar4 = *(long *)(lVar4 + 0x10)
      ) {
    plVar3 = *(long **)(lVar4 + 0x38);
    if (plVar3 != (long *)0x0) {
      (**(code **)(*plVar3 + 0x70))(fVar6,plVar3,iVar1 == 1);
    }
  }
  plVar3 = *(long **)(param_1 + 0x150);
  if ((plVar3 != (long *)0x0) && ((long)*(short *)(param_1 + 0x66) != 0)) {
    uVar5 = (long)*(short *)(param_1 + 0x66) & 0xffffffff;
    do {
      plVar2 = (long *)*plVar3;
      if (plVar2 != (long *)0x0) {
        (**(code **)(*plVar2 + 0x70))(fVar6,plVar2,iVar1 == 1);
      }
      uVar5 = uVar5 - 1;
      plVar3 = plVar3 + 1;
    } while (uVar5 != 0);
  }
  plVar3 = (long *)PTR__ZN4Aska30ArticulatedDynamicsManagerBase22m_pWorldConstraintListE_02cbc740;
  for (uVar5 = (ulong)(byte)*
                            PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98
      ; uVar5 != 0; uVar5 = uVar5 - 1) {
    plVar2 = (long *)*plVar3;
    if (plVar2 != (long *)0x0) {
      (**(code **)(*plVar2 + 0x70))(fVar6,plVar2,iVar1 == 1);
    }
    plVar3 = plVar3 + 1;
  }
  return;
}

// ==== void Aska::ArticulatedDynamicsManagerMP::CalcPenduramAccel<Aska::ArticulatedDynamicsManagerMP, Aska::ADMJoint>(Aska::ArticulatedDynamicsManagerMP*, float)
// vaddr 0x232ef0c | ghidra 0x242ef0c | size 504 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP17CalcPenduramAccelIS0_NS_8ADMJointEEEvPT_f | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28ArticulatedDynamicsManagerMP17CalcPenduramAccelIS0_NS_8ADMJointEEEvPT_f
               (undefined8 param_1,long param_2)

{
  long lVar1;
  long lVar2;
  long lVar3;
  uint uVar4;
  uint uVar5;
  long lVar6;
  undefined4 *puVar7;
  ulong uVar8;
  long lVar9;
  ulong uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  
  uVar4 = *(uint *)(param_2 + 0x1e0);
  if (0 < (int)uVar4) {
    uVar10 = 0;
    do {
      lVar9 = *(long *)(*(long *)(param_2 + 0x1c0) + uVar10 * 0x10);
      if (lVar9 != 0) {
        lVar6 = *(long *)(lVar9 + 0x30);
        *(undefined4 *)(lVar6 + 0x10) = *(undefined4 *)(lVar6 + 0xbc);
        *(undefined4 *)(lVar6 + 0x14) = *(undefined4 *)(lVar6 + 0xcc);
        *(undefined4 *)(lVar6 + 0x18) = *(undefined4 *)(lVar6 + 0xdc);
        *(undefined4 *)(lVar6 + 0x1c) = 0x3f800000;
        uVar5 = *(uint *)(*(long *)(param_2 + 0x1c0) + uVar10 * 0x10 + 8);
        uVar8 = (ulong)uVar5;
        if ((int)uVar5 < 1) {
          void Aska::ArticulatedDynamicsManagerMP::GetAcceleration<Aska::ArticulatedDynamicsManagerMP, Aska::ADMJoint>(Aska::ArticulatedDynamicsManagerMP*, float, Aska::LinkListParam*, int)(param_1,param_2,lVar9,uVar8);
        }
        else {
          lVar6 = 0;
          do {
            lVar1 = lVar9 + lVar6;
            lVar2 = *(long *)(lVar1 + 0x30);
            lVar3 = *(long *)(lVar1 + 0x38);
            lVar6 = lVar6 + 0x50;
            *(float *)(lVar1 + 0x10) = *(float *)(lVar3 + 0x10) - *(float *)(lVar2 + 0x10);
            *(float *)(lVar1 + 0x14) = *(float *)(lVar3 + 0x14) - *(float *)(lVar2 + 0x14);
            *(float *)(lVar1 + 0x18) = *(float *)(lVar3 + 0x18) - *(float *)(lVar2 + 0x18);
            *(undefined4 *)(lVar1 + 0x1c) = *(undefined4 *)(lVar3 + 0x1c);
            *(float *)(lVar1 + 0x20) = *(float *)(lVar3 + 0x50) - *(float *)(lVar2 + 0x50);
            *(float *)(lVar1 + 0x24) = *(float *)(lVar3 + 0x54) - *(float *)(lVar2 + 0x54);
            *(float *)(lVar1 + 0x28) = *(float *)(lVar3 + 0x58) - *(float *)(lVar2 + 0x58);
            *(undefined4 *)(lVar1 + 0x2c) = *(undefined4 *)(lVar3 + 0x5c);
          } while ((ulong)(lVar9 + lVar6) < (ulong)(lVar9 + (long)(int)uVar5 * 0x50));
          void Aska::ArticulatedDynamicsManagerMP::GetAcceleration<Aska::ArticulatedDynamicsManagerMP, Aska::ADMJoint>(Aska::ArticulatedDynamicsManagerMP*, float, Aska::LinkListParam*, int)(param_1,param_2,lVar9,uVar8);
          if (0 < (int)uVar5) {
            puVar7 = (undefined4 *)(lVar9 + 0x1c);
            do {
              fVar12 = (float)puVar7[2];
              fVar13 = (float)puVar7[3];
              lVar9 = *(long *)(puVar7 + 5);
              fVar11 = (float)puVar7[1] + (float)puVar7[-7];
              puVar7[1] = fVar11;
              puVar7[2] = fVar12 + (float)puVar7[-6];
              fVar14 = (float)param_1;
              puVar7[3] = fVar13 + (float)puVar7[-5];
              puVar7[4] = 0x3f800000;
              *puVar7 = 0x3f800000;
              puVar7[-3] = fVar11 * fVar14 + (float)puVar7[-3];
              puVar7[-2] = (fVar12 + (float)puVar7[-6]) * fVar14 + (float)puVar7[-2];
              puVar7[-1] = (fVar13 + (float)puVar7[-5]) * fVar14 + (float)puVar7[-1];
              lVar6 = *(long *)(puVar7 + 7);
              uVar8 = uVar8 - 1;
              *(float *)(lVar6 + 0x50) = *(float *)(lVar9 + 0x50) + fVar11;
              *(float *)(lVar6 + 0x54) = *(float *)(lVar9 + 0x54) + (float)puVar7[2];
              fVar11 = *(float *)(lVar9 + 0x58);
              fVar12 = (float)puVar7[3];
              puVar7 = puVar7 + 0x14;
              *(undefined4 *)(lVar6 + 0x5c) = 0x3f800000;
              *(float *)(lVar6 + 0x58) = fVar11 + fVar12;
            } while (uVar8 != 0);
          }
        }
      }
      uVar10 = uVar10 + 1;
    } while (uVar10 != uVar4);
  }
  return;
}

// ==== void Aska::ArticulatedDynamicsManagerMP::MatrixPreFixAndMotionBlend<true>(Aska::ADM_CALC_DATA*, Aska::ADMJoint*, unsigned int, float, float, float, Aska::Vector*, bool)
// vaddr 0x232f104 | ghidra 0x242f104 | size 536 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP26MatrixPreFixAndMotionBlendILb1EEEvPNS_13ADM_CALC_DATAEPNS_8ADMJointEjfffPNS_6VectorEb | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska28ArticulatedDynamicsManagerMP26MatrixPreFixAndMotionBlendILb1EEEvPNS_13ADM_CALC_DATAEPNS_8ADMJointEjfffPNS_6VectorEb
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               long param_5,int param_6,undefined8 param_7,uint param_8)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  float fVar4;
  undefined4 *puVar5;
  long lVar6;
  float *pfVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  float fVar11;
  float fVar12;
  
  fVar4 = _UNK_027e519c;
  uVar3 = _UNK_027dbb38;
  uVar2 = _UNK_027dbb30;
  if (param_6 != 0) {
    puVar10 = (undefined4 *)(param_5 + 0x1b8);
    do {
      lVar6 = *(long *)(puVar10 + -0x22);
      param_6 = param_6 + -1;
      if ((float)puVar10[-0x11] <= fVar4) {
        fVar11 = (float)puVar10[-0x53];
        puVar9 = puVar10 + -0x2c;
        puVar5 = puVar10 + -0x2e;
        puVar8 = puVar10 + -0x2d;
        pfVar7 = (float *)(puVar10 + -0x2b);
      }
      else {
        fVar11 = (float)puVar10[-0x53];
        puVar5 = (undefined4 *)(param_5 + 0x100);
        pfVar7 = (float *)(param_5 + 0x10c);
        puVar8 = (undefined4 *)(param_5 + 0x104);
        if ((float)puVar10[-0x2b] == fVar11) {
          fVar12 = (float)puVar10[-0x2d];
          if (((fVar12 == (float)puVar10[-0x55]) && ((float)puVar10[-0x2c] == (float)puVar10[-0x54])
              ) && ((float)puVar10[-0x2e] == (float)puVar10[-0x56])) {
            puVar9 = (undefined4 *)(param_5 + 0x108);
            goto code_r0x0242f244;
          }
        }
        else {
          fVar12 = (float)puVar10[-0x2d];
        }
        puVar10[-0x4e] = puVar10[-0x2e];
        puVar10[-0x4d] = fVar12;
        puVar9 = (undefined4 *)(param_5 + 0x108);
        puVar10[-0x4c] = puVar10[-0x2c];
        puVar10[-0x4b] = puVar10[-0x2b];
      }
code_r0x0242f244:
      puVar10[-0xb] = 0;
      *(undefined1 *)((long)puVar10 + -0x19) = 0;
      *(undefined8 *)(puVar10 + -0x66) = *(undefined8 *)(puVar10 + -0x6a);
      puVar10[-100] = puVar10[-0x68];
      puVar10[-99] = 0x3f800000;
      *(undefined8 *)(puVar10 + -0x48) = uVar3;
      *(undefined8 *)(puVar10 + -0x4a) = uVar2;
      *puVar10 = 0x3f4ccccd;
      *puVar5 = puVar10[-0x56];
      *puVar8 = puVar10[-0x55];
      *puVar9 = puVar10[-0x54];
      lVar1 = lVar6 + 0x60;
      if (lVar6 == 0) {
        lVar1 = 0;
      }
      *pfVar7 = fVar11;
      Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(puVar10 + -0x42,puVar10 + -0x32,puVar5,puVar10 + -0x26,puVar10 + -0x2a,lVar1);
      Aska::ADMJoint::ExternalForceMP(float, float, float, Aska::Vector const*, Aska::ADM_CALC_DATA*, bool)(param_1,param_2,param_3,puVar10 + -0x6e,param_7,puVar10 + -0x42,param_8 & 1);
      puVar10 = puVar10 + 0x70;
      param_5 = param_5 + 0x1c0;
    } while (param_6 != 0);
  }
  return;
}
