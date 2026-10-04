// port/decomp/anim/controllers.c: Ghidra decompiles for the anim subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileAt.java, tools/resolve_decomp.py
// run      2026-10-04 06:28 UTC: tools/decomp_at.sh '--into' 'anim/controllers' '0x209c508' '0x209f6f0' '0x20a05c8' '0x209c9b8' '0x20cf4ac' '0x20c4d90' '0x20dee48' '0x20ab770' '0x20a798c' '0x20e9ebc' '0x20d97a8'

// ==== Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0>, false, false, (Aska::kTYPE_AAFCALCCNTR)0>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)
// vaddr 0x1f9c508 | ghidra 0x209c508 | size 1200 | symbol _ZN4Aska20AafCalcCommonFunctor20CalcAndSetSubFunctorINS_11AafCalcTypeILNS_17kTYPE_AAFCALCCNTRE0ELNS_19kTYPE_AAFCALCANDSETE0ELNS_18kTYPE_AAFCALCSPEEDE0ELNS_13kTYPE_AAFCALCE0ELNS_22kTYPE_AAFLOOPCONDITIONE0EEELb0ELb0ELS3_0EEclEPNS_10AafHandlerEPNS_11IAnimatableEPNS_11IControllerEffj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20AafCalcCommonFunctor20CalcAndSetSubFunctorINS_11AafCalcTypeILNS_17kTYPE_AAFCALCCNTRE0ELNS_19kTYPE_AAFCALCANDSETE0ELNS_18kTYPE_AAFCALCSPEEDE0ELNS_13kTYPE_AAFCALCE0ELNS_22kTYPE_AAFLOOPCONDITIONE0EEELb0ELb0ELS3_0EEclEPNS_10AafHandlerEPNS_11IAnimatableEPNS_11IControllerEffj
               (ulong param_1,undefined8 param_2,long param_3,undefined8 param_4,undefined8 param_5,
               undefined4 param_6)

{
  undefined8 uVar1;
  undefined4 uVar2;
  char cVar3;
  ushort uVar4;
  bool bVar5;
  ulong uVar6;
  long lVar7;
  undefined8 *puVar8;
  uint uVar9;
  long lVar10;
  uint uVar11;
  long lVar12;
  uint uVar13;
  long *plVar14;
  byte *pbVar15;
  undefined8 uVar16;
  undefined8 *puVar17;
  float fVar18;
  float fVar19;
  int iStack_8c;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined4 uStack_70;
  undefined1 auStack_60 [16];
  undefined1 auStack_48 [4];
  undefined4 uStack_44;
  
  uStack_44 = 0xffffffff;
  lVar7 = *(long *)(param_3 + 0x28);
  lVar10 = 0;
  uVar4 = *(ushort *)(lVar7 + 0xe);
  uVar11 = (uint)uVar4;
  if ((uVar4 == 0) || (*(long *)(param_3 + 0x118) == 0)) {
    lVar12 = 0;
  }
  else {
    fVar19 = (float)param_1;
    fVar18 = fVar19 / *(float *)(lVar7 + 0x2c);
    if (0.0 <= fVar18) {
      uVar9 = (uint)fVar18;
      uVar13 = uVar11 - 1;
      fVar18 = *(float *)(lVar7 + 0x10);
      if ((uVar11 != uVar9 && (int)uVar9 <= (int)(uint)uVar4) && fVar19 <= *(float *)(lVar7 + 0x10))
      {
        uVar13 = uVar9;
        fVar18 = fVar19;
      }
    }
    else {
      uVar13 = 0;
      fVar18 = 0.0;
    }
    param_1 = (ulong)(uint)fVar18;
    lVar10 = *(long *)(*(long *)(param_3 + 0x118) + (long)(int)uVar13 * 8);
    lVar12 = *(long *)(param_3 + 0x10) + (ulong)*(uint *)(lVar7 + 0x28) + (long)(int)uVar13 * 0xc;
  }
  if (uVar11 == 0) {
    lVar10 = *(long *)(param_3 + 0xe0);
    uVar2 = *(undefined4 *)(param_3 + 0x48);
    bVar5 = false;
    cVar3 = *(char *)(param_3 + 0xf7);
  }
  else {
    if (lVar10 == 0) {
      if (*(short *)(lVar7 + 8) != 0) {
        return;
      }
      bVar5 = true;
    }
    else {
      bVar5 = false;
    }
    uVar2 = *(undefined4 *)(lVar12 + 8);
    *(long *)(param_3 + 0xe0) = lVar10;
    *(undefined4 *)(param_3 + 0x48) = uVar2;
    cVar3 = *(char *)(param_3 + 0xf7);
  }
  if (cVar3 != '\0') {
    if ((*(float *)(param_3 + 0xe8) <= (float)param_1) &&
       ((float)param_1 < *(float *)(param_3 + 0xec))) {
      if (*(uint *)(param_3 + 0x38) != 0) {
        lVar10 = (ulong)*(uint *)(param_3 + 0x38) * 0x30;
        pbVar15 = (byte *)(*(long *)(param_3 + 0x80) + 0x2e);
        do {
          if ((*pbVar15 & 0x27) == 0) {
            uStack_78 = *(undefined8 *)
                         (*(long *)(param_3 + 0x78) + (ulong)*(ushort *)(pbVar15 + -2) * 0x10 + 8);
            uStack_80 = *(undefined8 *)(pbVar15 + -0x2e);
            plVar14 = *(long **)(pbVar15 + -0x26);
            (**(code **)(*plVar14 + 0x140))
                      (param_1,*(undefined4 *)(param_3 + 0xe8),*(undefined4 *)(param_3 + 0xf0),
                       plVar14,auStack_60);
            (**(code **)(*plVar14 + 0x168))(plVar14,auStack_60,&uStack_80);
          }
          lVar10 = lVar10 + -0x30;
          pbVar15 = pbVar15 + 0x30;
        } while (lVar10 != 0);
        return;
      }
      return;
    }
    if (*(char *)(param_3 + 0xf8) != '\0') {
      *(undefined1 *)(param_3 + 0xf7) = 0;
    }
  }
  auStack_48[0] = 0;
  if (!bVar5) {
    uStack_88 = 0;
    iStack_8c = 0;
    puVar17 = *(undefined8 **)(param_3 + 0xc0);
    uVar1 = *(undefined8 *)(param_3 + 200);
    uVar16 = *(undefined8 *)(param_3 + 0xd0);
    void Aska::AafCalcCommonFunctor::CheckCache<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0> >(Aska::AafHandler*, unsigned int*, unsigned int*, Aska::AafControllerInfo**, int&, int&, unsigned short*, unsigned short*, int&, unsigned int, Aska::IAnimatable*, float, Aska::FrameSortDataForSearchOld*, unsigned int)(param_1,param_3,*(undefined8 *)(param_3 + 0xb0),*(undefined8 *)(param_3 + 0xb8),
                    puVar17,&uStack_88,&iStack_8c,uVar1,uVar16,(long)&uStack_88 + 4,
                    *(undefined4 *)(param_3 + 0x3c),param_4,lVar10,uVar2);
    if (uStack_88._4_4_ != 0) {
      lVar10 = (ulong)uStack_88._4_4_ << 3;
      do {
        puVar8 = (undefined8 *)*puVar17;
        uStack_78 = *(undefined8 *)
                     (*(long *)(param_3 + 0x78) + (ulong)*(ushort *)((long)puVar8 + 0x2c) * 0x10 + 8
                     );
        uStack_80 = *puVar8;
        plVar14 = (long *)puVar8[1];
        (**(code **)(*plVar14 + 0x60))(param_1,plVar14,auStack_60);
        (**(code **)(*plVar14 + 0x168))(plVar14,auStack_60,&uStack_80);
        lVar10 = lVar10 + -8;
        puVar17 = puVar17 + 1;
      } while (lVar10 != 0);
    }
    if ((0 < (int)uStack_88) || (0 < iStack_8c)) {
      void Aska::AafCalcCommonFunctor::Local_CalcAndSet_OutofRange<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0>, false, false>(bool&, Aska::AafHandler*, unsigned int&, float, float, unsigned int, unsigned int, unsigned int, unsigned short*, unsigned short*)(param_1,uStack_70,auStack_48,param_3,&uStack_44,param_6,uStack_88 & 0xffffffff
                      ,iStack_8c,uVar16,uVar1);
    }
  }
  if ((((*(uint *)(param_3 + 0xc) ^ 0xffffffff) & 0x120) == 0) && (*(uint *)(param_3 + 0x40) != 0))
  {
    lVar10 = (ulong)*(uint *)(param_3 + 0x40) * 0x30;
    pbVar15 = (byte *)(*(long *)(param_3 + 0x90) + 0x2e);
    do {
      uStack_78 = *(undefined8 *)
                   (*(long *)(param_3 + 0x78) + (ulong)*(ushort *)(pbVar15 + -2) * 0x10 + 8);
      if ((*pbVar15 & 7) == 0) {
        plVar14 = *(long **)(pbVar15 + -0x26);
        (**(code **)(*plVar14 + 0x148))(plVar14,auStack_60,1);
        uStack_80 = *(undefined8 *)(pbVar15 + -0x2e);
        (**(code **)(*plVar14 + 0x168))(plVar14,auStack_60,&uStack_80);
      }
      lVar10 = lVar10 + -0x30;
      pbVar15 = pbVar15 + 0x30;
    } while (lVar10 != 0);
    *(uint *)(param_3 + 0xc) = *(uint *)(param_3 + 0xc) & 0xffffffdf;
  }
  if (*(uint *)(param_3 + 0x44) != 0) {
    lVar10 = (ulong)*(uint *)(param_3 + 0x44) * 0x30;
    pbVar15 = (byte *)(*(long *)(param_3 + 0x98) + 0x2e);
    do {
      uStack_78 = *(undefined8 *)
                   (*(long *)(param_3 + 0x78) + (ulong)*(ushort *)(pbVar15 + -2) * 0x10 + 8);
      if ((*pbVar15 & 7) == 0) {
        plVar14 = *(long **)(pbVar15 + -0x26);
        uVar6 = (**(code **)(*plVar14 + 0x1d8))(plVar14);
        if ((uVar6 & 1) != 0) {
          (**(code **)(*plVar14 + 0x60))(param_1,plVar14,auStack_60);
        }
        uVar6 = (**(code **)(*plVar14 + 0x1d8))(plVar14);
        if ((uVar6 & 1) != 0) {
          uStack_80 = *(undefined8 *)(pbVar15 + -0x2e);
          (**(code **)(*plVar14 + 0x168))(plVar14,auStack_60,&uStack_80);
        }
      }
      lVar10 = lVar10 + -0x30;
      pbVar15 = pbVar15 + 0x30;
    } while (lVar10 != 0);
  }
  if ((*(char *)(param_3 + 0xfa) != '\0') && (*(uint *)(param_3 + 0x44) != 0)) {
    lVar10 = (ulong)*(uint *)(param_3 + 0x44) * 0x30;
    pbVar15 = (byte *)(*(long *)(param_3 + 0x98) + 0x2e);
    do {
      uStack_78 = *(undefined8 *)
                   (*(long *)(param_3 + 0x78) + (ulong)*(ushort *)(pbVar15 + -2) * 0x10 + 8);
      if ((*pbVar15 & 7) == 0) {
        plVar14 = *(long **)(pbVar15 + -0x26);
        uVar6 = (**(code **)(*plVar14 + 0x1d8))(plVar14);
        if ((uVar6 & 1) == 0) {
          (**(code **)(*plVar14 + 0x60))(param_1,plVar14,auStack_60);
        }
        uVar6 = (**(code **)(*plVar14 + 0x1d8))(plVar14);
        if ((uVar6 & 1) == 0) {
          uStack_80 = *(undefined8 *)(pbVar15 + -0x2e);
          (**(code **)(*plVar14 + 0x168))(plVar14,auStack_60,&uStack_80);
        }
      }
      lVar10 = lVar10 + -0x30;
      pbVar15 = pbVar15 + 0x30;
    } while (lVar10 != 0);
  }
  return;
}

// ==== void Aska::AafCalcCommonFunctor::CheckCache<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0> >(Aska::AafHandler*, unsigned int*, unsigned int*, Aska::AafControllerInfo**, int&, int&, unsigned short*, unsigned short*, int&, unsigned int, Aska::IAnimatable*, float, Aska::FrameSortDataForSearchOld*, unsigned int)
// vaddr 0x1f9c9b8 | ghidra 0x209c9b8 | size 512 | symbol _ZN4Aska20AafCalcCommonFunctor10CheckCacheINS_11AafCalcTypeILNS_17kTYPE_AAFCALCCNTRE0ELNS_19kTYPE_AAFCALCANDSETE0ELNS_18kTYPE_AAFCALCSPEEDE0ELNS_13kTYPE_AAFCALCE0ELNS_22kTYPE_AAFLOOPCONDITIONE0EEEEEvPNS_10AafHandlerEPjSB_PPNS_17AafControllerInfoERiSF_PtSG_SF_jPNS_11IAnimatableEfPNS_25FrameSortDataForSearchOldEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20AafCalcCommonFunctor10CheckCacheINS_11AafCalcTypeILNS_17kTYPE_AAFCALCCNTRE0ELNS_19kTYPE_AAFCALCANDSETE0ELNS_18kTYPE_AAFCALCSPEEDE0ELNS_13kTYPE_AAFCALCE0ELNS_22kTYPE_AAFLOOPCONDITIONE0EEEEEvPNS_10AafHandlerEPjSB_PPNS_17AafControllerInfoERiSF_PtSG_SF_jPNS_11IAnimatableEfPNS_25FrameSortDataForSearchOldEj
               (undefined8 param_1,long param_2,long param_3,undefined8 param_4,long param_5,
               int *param_6,int *param_7,long param_8,long param_9,int *param_10,uint param_11,
               undefined8 param_12,undefined8 param_13,undefined4 param_14)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  float fVar10;
  float fVar11;
  
  iVar1 = *(int *)(param_2 + 0xa8);
  iVar4 = iVar1 << 2;
  memset(param_3,0,iVar4);
  lVar9 = *(long *)(param_2 + 0x88);
  if (param_11 != 0) {
    uVar5 = 0;
    lVar6 = lVar9;
    do {
      if ((*(byte *)(lVar6 + 0x2e) & 7) == 0) {
        lVar7 = *(long *)(lVar6 + 0x18);
        fVar11 = (float)param_1;
        if (*(float *)(lVar7 + 0xc) <= fVar11) {
          if (fVar11 <= *(float *)(lVar7 + 0x10)) {
            iVar3 = *param_10;
            lVar8 = *(long *)(lVar6 + 8);
            *param_10 = iVar3 + 1;
            *(long *)(param_5 + (long)iVar3 * 8) = lVar6;
            if ((*(byte *)(lVar6 + 0x2e) >> 4 & 1) == 0) {
              bVar2 = *(byte *)(lVar8 + 0xd);
              lVar8 = lVar8 + 0x10;
              fVar10 = *(float *)(lVar8 + (ulong)bVar2 * 4);
              if (fVar10 <= fVar11) {
                fVar10 = *(float *)(lVar8 + (ulong)(bVar2 ^ 1) * 4);
                if ((fVar10 < fVar11) && (fVar10 != *(float *)(lVar7 + 0x10)))
                goto code_r0x0209cb88;
              }
              else if (fVar10 != *(float *)(lVar7 + 0xc)) goto code_r0x0209cb88;
            }
            else {
code_r0x0209cb88:
              lVar7 = (uVar5 >> 5 & 0x7ffffff) * 4;
              *(uint *)(param_3 + lVar7) =
                   *(uint *)(param_3 + lVar7) | 1 << (ulong)((uint)uVar5 & 0x1f);
            }
          }
          else {
            iVar3 = *param_7;
            *param_7 = iVar3 + 1;
            *(short *)(param_9 + (long)iVar3 * 2) = (short)uVar5;
          }
        }
        else {
          iVar3 = *param_6;
          *param_6 = iVar3 + 1;
          *(short *)(param_8 + (long)iVar3 * 2) = (short)uVar5;
        }
      }
      uVar5 = uVar5 + 1;
      lVar6 = lVar6 + 0x30;
    } while (param_11 != uVar5);
  }
  if (0 < *param_10) {
    memcpy(param_4,param_3,iVar4);
    (*(code *)
      PTR__ZN4Aska10AafHandler34Function_RenewalAllControllerCacheEfPjS1_jPNS_17AafControllerInfoEjPNS_25FrameSortDataForSearchOldEjb_02cae0f0
    )(param_1,param_4,param_3,iVar1,lVar9,param_11,param_13,param_14,
      *(uint *)(param_2 + 0xc) >> 6 & 1);
    return;
  }
  return;
}

// ==== Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0>, true, false, (Aska::kTYPE_AAFCALCCNTR)0>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)
// vaddr 0x1f9f6f0 | ghidra 0x209f6f0 | size 1028 | symbol _ZN4Aska20AafCalcCommonFunctor20CalcAndSetSubFunctorINS_11AafCalcTypeILNS_17kTYPE_AAFCALCCNTRE0ELNS_19kTYPE_AAFCALCANDSETE0ELNS_18kTYPE_AAFCALCSPEEDE0ELNS_13kTYPE_AAFCALCE0ELNS_22kTYPE_AAFLOOPCONDITIONE0EEELb1ELb0ELS3_0EEclEPNS_10AafHandlerEPNS_11IAnimatableEPNS_11IControllerEffj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20AafCalcCommonFunctor20CalcAndSetSubFunctorINS_11AafCalcTypeILNS_17kTYPE_AAFCALCCNTRE0ELNS_19kTYPE_AAFCALCANDSETE0ELNS_18kTYPE_AAFCALCSPEEDE0ELNS_13kTYPE_AAFCALCE0ELNS_22kTYPE_AAFLOOPCONDITIONE0EEELb1ELb0ELS3_0EEclEPNS_10AafHandlerEPNS_11IAnimatableEPNS_11IControllerEffj
               (ulong param_1,undefined8 param_2,long param_3,undefined8 param_4,undefined8 param_5,
               undefined4 param_6)

{
  undefined8 uVar1;
  ushort uVar2;
  bool bVar3;
  ulong uVar4;
  long lVar5;
  undefined8 *puVar6;
  long lVar7;
  uint uVar8;
  undefined4 uVar9;
  long lVar10;
  uint uVar11;
  long *plVar12;
  byte *pbVar13;
  undefined8 uVar14;
  undefined8 *puVar15;
  float fVar16;
  float fVar17;
  int iStack_9c;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined4 uStack_80;
  undefined1 auStack_70 [16];
  undefined1 auStack_48 [4];
  undefined4 uStack_44;
  
  uStack_44 = 0xffffffff;
  lVar5 = *(long *)(param_3 + 0x28);
  lVar7 = 0;
  uVar2 = *(ushort *)(lVar5 + 0xe);
  fVar17 = (float)param_1;
  uVar8 = (uint)uVar2;
  if ((uVar2 == 0) || (*(long *)(param_3 + 0x118) == 0)) {
    lVar10 = 0;
    if (uVar8 != 0) goto code_r0x0209fa20;
code_r0x0209f764:
    lVar7 = *(long *)(param_3 + 0xe0);
    uVar9 = *(undefined4 *)(param_3 + 0x48);
  }
  else {
    fVar16 = fVar17 / *(float *)(lVar5 + 0x2c);
    if (0.0 <= fVar16) {
      uVar11 = (uint)fVar16;
      if (uVar8 == uVar11 || (int)(uint)uVar2 < (int)uVar11) {
        fVar16 = *(float *)(lVar5 + 0x10);
      }
      else {
        fVar16 = *(float *)(lVar5 + 0x10);
        if (fVar17 <= *(float *)(lVar5 + 0x10)) goto code_r0x0209fa04;
      }
      fVar17 = fVar16;
      param_1 = (ulong)(uint)fVar17;
      uVar11 = uVar8 - 1;
    }
    else {
      fVar17 = 0.0;
      uVar11 = 0;
      param_1 = 0;
    }
code_r0x0209fa04:
    lVar7 = *(long *)(*(long *)(param_3 + 0x118) + (long)(int)uVar11 * 8);
    lVar10 = *(long *)(param_3 + 0x10) + (ulong)*(uint *)(lVar5 + 0x28) + (long)(int)uVar11 * 0xc;
    if (uVar8 == 0) goto code_r0x0209f764;
code_r0x0209fa20:
    if (lVar7 == 0) {
      bVar3 = false;
      if (*(short *)(lVar5 + 8) != 0) {
        return;
      }
    }
    else {
      bVar3 = true;
    }
    uVar9 = *(undefined4 *)(lVar10 + 8);
    *(long *)(param_3 + 0xe0) = lVar7;
    *(undefined4 *)(param_3 + 0x48) = uVar9;
    auStack_48[0] = 0;
    if (!bVar3) goto code_r0x0209f860;
  }
  auStack_48[0] = 0;
  uStack_98 = 0;
  iStack_9c = 0;
  puVar15 = *(undefined8 **)(param_3 + 0xc0);
  uVar1 = *(undefined8 *)(param_3 + 200);
  uVar14 = *(undefined8 *)(param_3 + 0xd0);
  void Aska::AafCalcCommonFunctor::CheckCache<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0> >(Aska::AafHandler*, unsigned int*, unsigned int*, Aska::AafControllerInfo**, int&, int&, unsigned short*, unsigned short*, int&, unsigned int, Aska::IAnimatable*, float, Aska::FrameSortDataForSearchOld*, unsigned int)(fVar17,param_3,*(undefined8 *)(param_3 + 0xb0),*(undefined8 *)(param_3 + 0xb8),
                  puVar15,&uStack_98,&iStack_9c,uVar1,uVar14,(long)&uStack_98 + 4,
                  *(undefined4 *)(param_3 + 0x3c),param_4,lVar7,uVar9);
  if (uStack_98._4_4_ != 0) {
    lVar5 = (ulong)uStack_98._4_4_ << 3;
    do {
      puVar6 = (undefined8 *)*puVar15;
      uStack_88 = *(undefined8 *)
                   (*(long *)(param_3 + 0x78) + (ulong)*(ushort *)((long)puVar6 + 0x2c) * 0x10 + 8);
      uStack_90 = *puVar6;
      plVar12 = (long *)puVar6[1];
      (**(code **)(*plVar12 + 0x60))(fVar17,plVar12,auStack_70);
      (**(code **)(*plVar12 + 0x178))(plVar12,auStack_70,&uStack_90);
      lVar5 = lVar5 + -8;
      puVar15 = puVar15 + 1;
    } while (lVar5 != 0);
  }
  if ((0 < (int)uStack_98) || (0 < iStack_9c)) {
    void Aska::AafCalcCommonFunctor::Local_CalcAndSet_OutofRange<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0>, true, false>(bool&, Aska::AafHandler*, unsigned int&, float, float, unsigned int, unsigned int, unsigned int, unsigned short*, unsigned short*)(fVar17,uStack_80,auStack_48,param_3,&uStack_44,param_6,uStack_98 & 0xffffffff,
                    iStack_9c,uVar14,uVar1);
  }
code_r0x0209f860:
  if ((((*(uint *)(param_3 + 0xc) ^ 0xffffffff) & 0x120) == 0) && (*(uint *)(param_3 + 0x40) != 0))
  {
    lVar5 = (ulong)*(uint *)(param_3 + 0x40) * 0x30;
    pbVar13 = (byte *)(*(long *)(param_3 + 0x90) + 0x2e);
    do {
      uStack_88 = *(undefined8 *)
                   (*(long *)(param_3 + 0x78) + (ulong)*(ushort *)(pbVar13 + -2) * 0x10 + 8);
      if ((*pbVar13 & 7) == 0) {
        plVar12 = *(long **)(pbVar13 + -0x26);
        (**(code **)(*plVar12 + 0x148))(plVar12,auStack_70,1);
        uStack_90 = *(undefined8 *)(pbVar13 + -0x2e);
        (**(code **)(*plVar12 + 0x178))(plVar12,auStack_70,&uStack_90);
      }
      lVar5 = lVar5 + -0x30;
      pbVar13 = pbVar13 + 0x30;
    } while (lVar5 != 0);
    *(uint *)(param_3 + 0xc) = *(uint *)(param_3 + 0xc) & 0xffffffdf;
  }
  if (*(uint *)(param_3 + 0x44) != 0) {
    lVar5 = (ulong)*(uint *)(param_3 + 0x44) * 0x30;
    pbVar13 = (byte *)(*(long *)(param_3 + 0x98) + 0x2e);
    do {
      uStack_88 = *(undefined8 *)
                   (*(long *)(param_3 + 0x78) + (ulong)*(ushort *)(pbVar13 + -2) * 0x10 + 8);
      if ((*pbVar13 & 7) == 0) {
        plVar12 = *(long **)(pbVar13 + -0x26);
        uVar4 = (**(code **)(*plVar12 + 0x1d8))(plVar12);
        if ((uVar4 & 1) != 0) {
          (**(code **)(*plVar12 + 0x60))(param_1,plVar12,auStack_70);
        }
        uVar4 = (**(code **)(*plVar12 + 0x1d8))(plVar12);
        if ((uVar4 & 1) != 0) {
          uStack_90 = *(undefined8 *)(pbVar13 + -0x2e);
          (**(code **)(*plVar12 + 0x178))(plVar12,auStack_70,&uStack_90);
        }
      }
      lVar5 = lVar5 + -0x30;
      pbVar13 = pbVar13 + 0x30;
    } while (lVar5 != 0);
  }
  if ((*(char *)(param_3 + 0xfa) != '\0') && (*(uint *)(param_3 + 0x44) != 0)) {
    lVar5 = (ulong)*(uint *)(param_3 + 0x44) * 0x30;
    pbVar13 = (byte *)(*(long *)(param_3 + 0x98) + 0x2e);
    do {
      uStack_88 = *(undefined8 *)
                   (*(long *)(param_3 + 0x78) + (ulong)*(ushort *)(pbVar13 + -2) * 0x10 + 8);
      if ((*pbVar13 & 7) == 0) {
        plVar12 = *(long **)(pbVar13 + -0x26);
        uVar4 = (**(code **)(*plVar12 + 0x1d8))(plVar12);
        if ((uVar4 & 1) == 0) {
          (**(code **)(*plVar12 + 0x60))(fVar17,plVar12,auStack_70);
        }
        uVar4 = (**(code **)(*plVar12 + 0x1d8))(plVar12);
        if ((uVar4 & 1) == 0) {
          uStack_90 = *(undefined8 *)(pbVar13 + -0x2e);
          (**(code **)(*plVar12 + 0x178))(plVar12,auStack_70,&uStack_90);
        }
      }
      lVar5 = lVar5 + -0x30;
      pbVar13 = pbVar13 + 0x30;
    } while (lVar5 != 0);
  }
  return;
}

// ==== Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0>, false, true, (Aska::kTYPE_AAFCALCCNTR)0>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)
// vaddr 0x1fa05c8 | ghidra 0x20a05c8 | size 1204 | symbol _ZN4Aska20AafCalcCommonFunctor20CalcAndSetSubFunctorINS_11AafCalcTypeILNS_17kTYPE_AAFCALCCNTRE0ELNS_19kTYPE_AAFCALCANDSETE0ELNS_18kTYPE_AAFCALCSPEEDE0ELNS_13kTYPE_AAFCALCE0ELNS_22kTYPE_AAFLOOPCONDITIONE0EEELb0ELb1ELS3_0EEclEPNS_10AafHandlerEPNS_11IAnimatableEPNS_11IControllerEffj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20AafCalcCommonFunctor20CalcAndSetSubFunctorINS_11AafCalcTypeILNS_17kTYPE_AAFCALCCNTRE0ELNS_19kTYPE_AAFCALCANDSETE0ELNS_18kTYPE_AAFCALCSPEEDE0ELNS_13kTYPE_AAFCALCE0ELNS_22kTYPE_AAFLOOPCONDITIONE0EEELb0ELb1ELS3_0EEclEPNS_10AafHandlerEPNS_11IAnimatableEPNS_11IControllerEffj
               (ulong param_1,undefined4 param_2,undefined8 param_3,long param_4,undefined8 param_5,
               undefined8 param_6,undefined4 param_7)

{
  undefined8 uVar1;
  undefined4 uVar2;
  char cVar3;
  ushort uVar4;
  bool bVar5;
  ulong uVar6;
  long lVar7;
  undefined8 *puVar8;
  uint uVar9;
  long lVar10;
  uint uVar11;
  long lVar12;
  uint uVar13;
  long *plVar14;
  byte *pbVar15;
  undefined8 uVar16;
  undefined8 *puVar17;
  float fVar18;
  float fVar19;
  int iStack_8c;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined4 uStack_70;
  undefined1 auStack_60 [16];
  undefined1 auStack_48 [4];
  undefined4 uStack_44;
  
  uStack_44 = 0xffffffff;
  lVar7 = *(long *)(param_4 + 0x28);
  lVar10 = 0;
  uVar4 = *(ushort *)(lVar7 + 0xe);
  uVar11 = (uint)uVar4;
  if ((uVar4 == 0) || (*(long *)(param_4 + 0x118) == 0)) {
    lVar12 = 0;
  }
  else {
    fVar19 = (float)param_1;
    fVar18 = fVar19 / *(float *)(lVar7 + 0x2c);
    if (0.0 <= fVar18) {
      uVar9 = (uint)fVar18;
      uVar13 = uVar11 - 1;
      fVar18 = *(float *)(lVar7 + 0x10);
      if ((uVar11 != uVar9 && (int)uVar9 <= (int)(uint)uVar4) && fVar19 <= *(float *)(lVar7 + 0x10))
      {
        uVar13 = uVar9;
        fVar18 = fVar19;
      }
    }
    else {
      uVar13 = 0;
      fVar18 = 0.0;
    }
    param_1 = (ulong)(uint)fVar18;
    lVar10 = *(long *)(*(long *)(param_4 + 0x118) + (long)(int)uVar13 * 8);
    lVar12 = *(long *)(param_4 + 0x10) + (ulong)*(uint *)(lVar7 + 0x28) + (long)(int)uVar13 * 0xc;
  }
  if (uVar11 == 0) {
    lVar10 = *(long *)(param_4 + 0xe0);
    uVar2 = *(undefined4 *)(param_4 + 0x48);
    bVar5 = false;
    cVar3 = *(char *)(param_4 + 0xf7);
  }
  else {
    if (lVar10 == 0) {
      if (*(short *)(lVar7 + 8) != 0) {
        return;
      }
      bVar5 = true;
    }
    else {
      bVar5 = false;
    }
    uVar2 = *(undefined4 *)(lVar12 + 8);
    *(long *)(param_4 + 0xe0) = lVar10;
    *(undefined4 *)(param_4 + 0x48) = uVar2;
    cVar3 = *(char *)(param_4 + 0xf7);
  }
  uStack_70 = param_2;
  if (cVar3 != '\0') {
    if ((*(float *)(param_4 + 0xe8) <= (float)param_1) &&
       ((float)param_1 < *(float *)(param_4 + 0xec))) {
      if (*(uint *)(param_4 + 0x38) != 0) {
        lVar10 = (ulong)*(uint *)(param_4 + 0x38) * 0x30;
        pbVar15 = (byte *)(*(long *)(param_4 + 0x80) + 0x2e);
        do {
          if ((*pbVar15 & 0x27) == 0) {
            uStack_78 = *(undefined8 *)
                         (*(long *)(param_4 + 0x78) + (ulong)*(ushort *)(pbVar15 + -2) * 0x10 + 8);
            uStack_80 = *(undefined8 *)(pbVar15 + -0x2e);
            plVar14 = *(long **)(pbVar15 + -0x26);
            (**(code **)(*plVar14 + 0x140))
                      (param_1,*(undefined4 *)(param_4 + 0xe8),*(undefined4 *)(param_4 + 0xf0),
                       plVar14,auStack_60);
            (**(code **)(*plVar14 + 0x168))(plVar14,auStack_60,&uStack_80);
          }
          lVar10 = lVar10 + -0x30;
          pbVar15 = pbVar15 + 0x30;
        } while (lVar10 != 0);
        return;
      }
      return;
    }
    if (*(char *)(param_4 + 0xf8) != '\0') {
      *(undefined1 *)(param_4 + 0xf7) = 0;
    }
  }
  auStack_48[0] = 0;
  if (!bVar5) {
    uStack_88 = 0;
    iStack_8c = 0;
    puVar17 = *(undefined8 **)(param_4 + 0xc0);
    uVar1 = *(undefined8 *)(param_4 + 200);
    uVar16 = *(undefined8 *)(param_4 + 0xd0);
    void Aska::AafCalcCommonFunctor::CheckCache<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0> >(Aska::AafHandler*, unsigned int*, unsigned int*, Aska::AafControllerInfo**, int&, int&, unsigned short*, unsigned short*, int&, unsigned int, Aska::IAnimatable*, float, Aska::FrameSortDataForSearchOld*, unsigned int)(param_1,param_4,*(undefined8 *)(param_4 + 0xb0),*(undefined8 *)(param_4 + 0xb8),
                    puVar17,&uStack_88,&iStack_8c,uVar1,uVar16,(long)&uStack_88 + 4,
                    *(undefined4 *)(param_4 + 0x3c),param_5,lVar10,uVar2);
    if (uStack_88._4_4_ != 0) {
      lVar10 = (ulong)uStack_88._4_4_ << 3;
      do {
        puVar8 = (undefined8 *)*puVar17;
        uStack_78 = *(undefined8 *)
                     (*(long *)(param_4 + 0x78) + (ulong)*(ushort *)((long)puVar8 + 0x2c) * 0x10 + 8
                     );
        uStack_80 = *puVar8;
        plVar14 = (long *)puVar8[1];
        (**(code **)(*plVar14 + 0x60))(param_1,plVar14,auStack_60);
        (**(code **)(*plVar14 + 0x188))(plVar14,auStack_60,&uStack_80);
        lVar10 = lVar10 + -8;
        puVar17 = puVar17 + 1;
      } while (lVar10 != 0);
    }
    if ((0 < (int)uStack_88) || (0 < iStack_8c)) {
      void Aska::AafCalcCommonFunctor::Local_CalcAndSet_OutofRange<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0>, false, true>(bool&, Aska::AafHandler*, unsigned int&, float, float, unsigned int, unsigned int, unsigned int, unsigned short*, unsigned short*)(param_1,uStack_70,auStack_48,param_4,&uStack_44,param_7,uStack_88 & 0xffffffff
                      ,iStack_8c,uVar16,uVar1);
    }
  }
  if ((((*(uint *)(param_4 + 0xc) ^ 0xffffffff) & 0x120) == 0) && (*(uint *)(param_4 + 0x40) != 0))
  {
    lVar10 = (ulong)*(uint *)(param_4 + 0x40) * 0x30;
    pbVar15 = (byte *)(*(long *)(param_4 + 0x90) + 0x2e);
    do {
      uStack_78 = *(undefined8 *)
                   (*(long *)(param_4 + 0x78) + (ulong)*(ushort *)(pbVar15 + -2) * 0x10 + 8);
      if ((*pbVar15 & 7) == 0) {
        plVar14 = *(long **)(pbVar15 + -0x26);
        (**(code **)(*plVar14 + 0x148))(plVar14,auStack_60,1);
        uStack_80 = *(undefined8 *)(pbVar15 + -0x2e);
        (**(code **)(*plVar14 + 0x188))(plVar14,auStack_60,&uStack_80);
      }
      lVar10 = lVar10 + -0x30;
      pbVar15 = pbVar15 + 0x30;
    } while (lVar10 != 0);
    *(uint *)(param_4 + 0xc) = *(uint *)(param_4 + 0xc) & 0xffffffdf;
  }
  if (*(uint *)(param_4 + 0x44) != 0) {
    lVar10 = (ulong)*(uint *)(param_4 + 0x44) * 0x30;
    pbVar15 = (byte *)(*(long *)(param_4 + 0x98) + 0x2e);
    do {
      uStack_78 = *(undefined8 *)
                   (*(long *)(param_4 + 0x78) + (ulong)*(ushort *)(pbVar15 + -2) * 0x10 + 8);
      if ((*pbVar15 & 7) == 0) {
        plVar14 = *(long **)(pbVar15 + -0x26);
        uVar6 = (**(code **)(*plVar14 + 0x1d8))(plVar14);
        if ((uVar6 & 1) != 0) {
          (**(code **)(*plVar14 + 0x60))(param_1,plVar14,auStack_60);
        }
        uVar6 = (**(code **)(*plVar14 + 0x1d8))(plVar14);
        if ((uVar6 & 1) != 0) {
          uStack_80 = *(undefined8 *)(pbVar15 + -0x2e);
          (**(code **)(*plVar14 + 0x188))(plVar14,auStack_60,&uStack_80);
        }
      }
      lVar10 = lVar10 + -0x30;
      pbVar15 = pbVar15 + 0x30;
    } while (lVar10 != 0);
  }
  if ((*(char *)(param_4 + 0xfa) != '\0') && (*(uint *)(param_4 + 0x44) != 0)) {
    lVar10 = (ulong)*(uint *)(param_4 + 0x44) * 0x30;
    pbVar15 = (byte *)(*(long *)(param_4 + 0x98) + 0x2e);
    do {
      uStack_78 = *(undefined8 *)
                   (*(long *)(param_4 + 0x78) + (ulong)*(ushort *)(pbVar15 + -2) * 0x10 + 8);
      if ((*pbVar15 & 7) == 0) {
        plVar14 = *(long **)(pbVar15 + -0x26);
        uVar6 = (**(code **)(*plVar14 + 0x1d8))(plVar14);
        if ((uVar6 & 1) == 0) {
          (**(code **)(*plVar14 + 0x60))(param_1,plVar14,auStack_60);
        }
        uVar6 = (**(code **)(*plVar14 + 0x1d8))(plVar14);
        if ((uVar6 & 1) == 0) {
          uStack_80 = *(undefined8 *)(pbVar15 + -0x2e);
          (**(code **)(*plVar14 + 0x188))(plVar14,auStack_60,&uStack_80);
        }
      }
      lVar10 = lVar10 + -0x30;
      pbVar15 = pbVar15 + 0x30;
    } while (lVar10 != 0);
  }
  return;
}

// ==== bool LocalSetController<false>(Aska::AafHandler*, Aska::AafControllerInfo*, unsigned char**, unsigned char**)
// vaddr 0x1fa798c | ghidra 0x20a798c | size 404 | symbol _Z18LocalSetControllerILb0EEbPN4Aska10AafHandlerEPNS0_17AafControllerInfoEPPhS6_ | lib libSOA-3.7.0.so | 2026-10-04
uint _Z18LocalSetControllerILb0EEbPN4Aska10AafHandlerEPNS0_17AafControllerInfoEPPhS6_
               (undefined8 param_1,long param_2,long *param_3,undefined8 param_4)

{
  uint uVar1;
  ulong uVar2;
  undefined4 uVar3;
  long lVar4;
  long lStack_38;
  long lStack_28;
  
  lStack_28 = 0;
  lVar4 = *(long *)(param_2 + 0x10);
  lStack_38 = 0;
  switch(*(undefined1 *)(lVar4 + 4)) {
  case 0:
    uVar2 = LocalSetControllerF32(unsigned long&, void*&, bool, Aska::AafHandler*, Aska::AafControllerInfo*, unsigned char**)(&lStack_38,&lStack_28,0,param_1,param_2,param_3);
    break;
  case 1:
    uVar2 = LocalSetControllerU24(unsigned long&, void*&, bool, Aska::AafHandler*, Aska::AafControllerInfo*, unsigned char**)(&lStack_38,&lStack_28,0,param_1,param_2,param_3);
    break;
  case 2:
    uVar2 = LocalSetControllerU16(unsigned long&, void*&, bool, Aska::AafHandler*, Aska::AafControllerInfo*, unsigned char**)(&lStack_38,&lStack_28,0,param_1,param_2,param_3);
    break;
  case 3:
    uVar2 = LocalSetControllerQuaternionU32EX(unsigned long&, void*&, bool, Aska::AafHandler*, Aska::AafControllerInfo*, unsigned char**)(&lStack_38,&lStack_28,0,param_1,param_2,param_3);
    break;
  case 4:
    uVar2 = LocalSetControllerQuaternionU48EX(unsigned long&, void*&, bool, Aska::AafHandler*, Aska::AafControllerInfo*, unsigned char**)(&lStack_38,&lStack_28,0,param_1,param_2,param_3);
    break;
  default:
    goto code_r0x020a7a7c;
  }
  uVar1 = 0;
  if ((uVar2 & 1) != 0) {
code_r0x020a7a7c:
    *param_3 = *param_3 + lStack_38;
    if (*(long *)(param_2 + 8) == 0) {
      uVar1 = 0;
    }
    else {
      if (*(long *)(param_2 + 0x18) != 0) {
        *(undefined1 *)(*(long *)(param_2 + 8) + 0xe) =
             *(undefined1 *)(*(long *)(param_2 + 0x18) + 6);
        *(undefined1 *)(*(long *)(param_2 + 8) + 0xf) =
             *(undefined1 *)(*(long *)(param_2 + 0x18) + 5);
      }
      if ((lStack_28 == 0) && ((*(byte *)(lVar4 + 5) >> 6 & 1) != 0)) {
        lStack_28 = lVar4;
      }
      uVar3 = 1;
      if (-1 < *(char *)(lVar4 + 5)) {
        uVar3 = 2;
      }
      (**(code **)(**(long **)(param_2 + 8) + 200))(*(long **)(param_2 + 8),param_4,uVar3);
      uVar1 = (**(code **)(**(long **)(param_2 + 8) + 0x10))(*(long **)(param_2 + 8),lStack_28);
    }
  }
  return uVar1 & 1;
}

// ==== Aska::TAafNormalController<Aska::AafType<Aska::AafControlPoint_Normal, false, false, 0u> >::CalcValueSub(void*, float, bool)
// vaddr 0x1fab770 | ghidra 0x20ab770 | size 1720 | symbol _ZN4Aska20TAafNormalControllerINS_7AafTypeINS_22AafControlPoint_NormalELb0ELb0ELj0EEEE12CalcValueSubEPvfb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20TAafNormalControllerINS_7AafTypeINS_22AafControlPoint_NormalELb0ELb0ELj0EEEE12CalcValueSubEPvfb
               (ulong param_1,long *param_2,float *param_3,uint param_4)

{
  float *pfVar1;
  undefined4 *puVar2;
  long lVar3;
  float *pfVar4;
  float *pfVar5;
  uint uVar6;
  byte bVar7;
  uint uVar8;
  bool bVar9;
  bool bVar10;
  undefined4 uVar11;
  ulong uVar12;
  int iVar13;
  uint uVar14;
  float *pfVar15;
  float *pfVar16;
  uint uVar17;
  ulong uVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  
  lVar3 = (ulong)*(ushort *)(param_2[7] + 6) + param_2[7];
  uVar6 = *(uint *)(lVar3 + 0x14);
  uVar8 = uVar6 - 1;
  if (uVar6 == 0 || uVar8 == 0) {
    *param_3 = *(float *)param_2[4];
    if ((int)param_2[1] == 1) {
      return;
    }
code_r0x020ab7c0:
    *(undefined4 *)(param_2 + 1) = 1;
    return;
  }
  fVar20 = *(float *)(lVar3 + 0xc);
  fVar19 = *(float *)(lVar3 + 0x10);
  puVar2 = (undefined4 *)(lVar3 + 0x18);
  pfVar4 = (float *)(puVar2 + uVar6);
  uVar6 = uVar6 - 2;
  fVar24 = (float)param_1;
  if ((param_4 & 1) == 0) {
    fVar21 = fVar19 - fVar20;
    if (fVar24 <= fVar19) {
      if (fVar20 <= fVar24) goto code_r0x020ab7e0;
      switch(*(undefined1 *)(lVar3 + 8)) {
      case 0:
        goto code_r0x020ab94c;
      case 1:
        iVar13 = (int)param_2[8];
        if (iVar13 == 0) goto code_r0x020abde8;
        bVar7 = *(byte *)((long)param_2 + 0xd);
        uVar6 = bVar7 ^ 1;
        *(char *)((long)param_2 + 0xd) = (char)uVar6;
        if (iVar13 == -1) {
code_r0x020abdbc:
          *(undefined4 *)((long)param_2 + (ulong)bVar7 * 4 + 0x10) = *(undefined4 *)(lVar3 + 0x1c);
          param_2[(ulong)bVar7 + 4] = (long)(pfVar4 + 3);
        }
        else {
          *(undefined4 *)((long)param_2 + (ulong)uVar6 * 4 + 0x10) = *puVar2;
          param_2[(ulong)uVar6 + 4] = (long)pfVar4;
          if (iVar13 != 1) goto code_r0x020abdbc;
        }
        (**(code **)(*param_2 + 0x1c8))(param_2);
        *(undefined4 *)(param_2 + 8) = 0;
code_r0x020abde8:
        (**(code **)(*param_2 + 0x150))(param_1,param_2,param_3);
        *(undefined4 *)(param_2 + 1) = 0xffffffff;
        return;
      case 2:
        goto code_r0x020abb58;
      case 3:
        goto code_r0x020abb70;
      case 4:
        goto code_r0x020abbbc;
      default:
        goto code_r0x020abcc0;
      }
    }
    switch(*(undefined1 *)(lVar3 + 9)) {
    case 0:
      uVar14 = *(uint *)(param_2 + 8);
      if (uVar14 != uVar6) {
        bVar7 = *(byte *)((long)param_2 + 0xd);
        uVar17 = bVar7 ^ 1;
        *(char *)((long)param_2 + 0xd) = (char)uVar17;
        if (uVar14 + 1 != uVar6) {
          *(undefined4 *)((long)param_2 + (ulong)uVar17 * 4 + 0x10) = puVar2[(int)uVar6];
          param_2[(ulong)uVar17 + 4] = (long)(pfVar4 + (long)(int)uVar6 * 3);
        }
        if (uVar14 != uVar8) {
          *(undefined4 *)((long)param_2 + (ulong)bVar7 * 4 + 0x10) = puVar2[(int)uVar8];
          param_2[(ulong)bVar7 + 4] = (long)(pfVar4 + (long)(int)uVar8 * 3);
        }
        (**(code **)(*param_2 + 0x1c8))(param_2);
        *(uint *)(param_2 + 8) = uVar6;
      }
      uVar11 = 1;
      bVar7 = *(byte *)((long)param_2 + 0xd) ^ 1;
      goto code_r0x020ab9bc;
    case 1:
      uVar14 = *(uint *)(param_2 + 8);
      if (uVar14 != uVar6) {
        bVar7 = *(byte *)((long)param_2 + 0xd);
        uVar17 = bVar7 ^ 1;
        *(char *)((long)param_2 + 0xd) = (char)uVar17;
        if (uVar14 + 1 != uVar6) {
          *(undefined4 *)((long)param_2 + (ulong)uVar17 * 4 + 0x10) = puVar2[(int)uVar6];
          param_2[(ulong)uVar17 + 4] = (long)(pfVar4 + (long)(int)uVar6 * 3);
        }
        if (uVar14 != uVar8) {
          *(undefined4 *)((long)param_2 + (ulong)bVar7 * 4 + 0x10) = puVar2[(int)uVar8];
          param_2[(ulong)bVar7 + 4] = (long)(pfVar4 + (long)(int)uVar8 * 3);
        }
        (**(code **)(*param_2 + 0x1c8))(param_2);
        *(uint *)(param_2 + 8) = uVar6;
      }
      (**(code **)(*param_2 + 0x158))(param_1,param_2,param_3);
      goto code_r0x020ab7c0;
    case 2:
code_r0x020abb58:
      if (fVar21 == 0.0) {
        iVar13 = 0;
        fVar22 = 0.0;
      }
      else {
        fVar23 = (fVar24 - fVar20) / fVar21;
        fVar22 = fVar24 - fVar21 * (float)(int)fVar23;
        iVar13 = (int)fVar23;
      }
      bVar10 = false;
      *(int *)(param_2 + 1) = iVar13;
      fVar21 = 0.0;
      break;
    case 3:
code_r0x020abb70:
      fVar23 = 0.0;
      fVar22 = 0.0;
      if (fVar21 != 0.0) {
        fVar23 = (float)(int)((fVar24 - fVar20) / fVar21);
        fVar22 = fVar24 - fVar21 * fVar23;
      }
      bVar10 = (int)fVar23 != 0;
      *(int *)(param_2 + 1) = (int)fVar23;
      fVar21 = 0.0;
      if (bVar10) {
        fVar21 = fVar23;
      }
      break;
    case 4:
code_r0x020abbbc:
      if (fVar21 != 0.0) {
        fVar22 = (fVar24 - fVar20) / fVar21;
        uVar14 = (uint)fVar22;
        fVar24 = fVar24 - fVar21 * (float)(int)fVar22;
        param_1 = (ulong)(uint)fVar24;
        *(uint *)(param_2 + 1) = uVar14;
        if ((uVar14 & 1) != 0) {
          bVar10 = false;
          fVar22 = (fVar20 + fVar20 + fVar21) - fVar24;
          fVar21 = 0.0;
          break;
        }
        goto code_r0x020abcc0;
      }
      bVar10 = false;
      *(undefined4 *)(param_2 + 1) = 0;
      fVar21 = 0.0;
      fVar22 = 0.0;
      fVar23 = 0.0;
      bVar9 = bVar10;
      if (fVar20 < 0.0) goto code_r0x020ab7fc;
      goto code_r0x020abccc;
    default:
code_r0x020abcc0:
      fVar24 = (float)param_1;
      goto joined_r0x020abcc8;
    }
    fVar23 = fVar21;
    bVar9 = bVar10;
    if (fVar20 < fVar22) goto code_r0x020ab7fc;
code_r0x020abccc:
    bVar10 = bVar9;
    iVar13 = (int)param_2[8];
    if (iVar13 != 0) {
      bVar7 = *(byte *)((long)param_2 + 0xd);
      uVar6 = bVar7 ^ 1;
      *(char *)((long)param_2 + 0xd) = (char)uVar6;
      if (iVar13 == -1) {
code_r0x020abd04:
        *(undefined4 *)((long)param_2 + (ulong)bVar7 * 4 + 0x10) = *(undefined4 *)(lVar3 + 0x1c);
        param_2[(ulong)bVar7 + 4] = (long)(pfVar4 + 3);
      }
      else {
        *(undefined4 *)((long)param_2 + (ulong)uVar6 * 4 + 0x10) = *puVar2;
        param_2[(ulong)uVar6 + 4] = (long)pfVar4;
        if (iVar13 != 1) goto code_r0x020abd04;
      }
      (**(code **)(*param_2 + 0x1c8))(param_2);
      *(undefined4 *)(param_2 + 8) = 0;
    }
    bVar7 = *(byte *)((long)param_2 + 0xd);
  }
  else {
code_r0x020ab7e0:
    if ((int)param_2[1] == 0) goto code_r0x020abcc0;
    *(undefined4 *)(param_2 + 1) = 0;
joined_r0x020abcc8:
    bVar10 = false;
    fVar21 = 0.0;
    fVar22 = (float)param_1;
    fVar23 = fVar21;
    bVar9 = false;
    if (fVar24 <= fVar20) goto code_r0x020abccc;
code_r0x020ab7fc:
    fVar23 = fVar21;
    if (fVar22 < fVar19) {
      uVar12 = (ulong)*(byte *)((long)param_2 + 0xd);
      uVar14 = *(uint *)(param_2 + 8);
      uVar6 = *(byte *)((long)param_2 + 0xd) ^ 1;
      pfVar5 = (float *)((long)param_2 + uVar12 * 4 + 0x10);
      pfVar1 = (float *)((long)param_2 + (ulong)uVar6 * 4 + 0x10);
      uVar18 = (ulong)uVar14;
      pfVar15 = pfVar1;
      pfVar16 = pfVar5;
      do {
        uVar17 = (uint)uVar18;
        if (*pfVar16 <= fVar22) {
          if (fVar22 < *pfVar15) goto code_r0x020aba58;
          iVar13 = 1;
        }
        else {
          iVar13 = -1;
        }
        uVar18 = (long)iVar13 + (long)(int)uVar17;
        pfVar16 = (float *)(puVar2 + uVar18);
        pfVar15 = pfVar16 + 1;
      } while( true );
    }
    uVar14 = *(uint *)(param_2 + 8);
    if (uVar14 != uVar6) {
      bVar7 = *(byte *)((long)param_2 + 0xd);
      uVar17 = bVar7 ^ 1;
      *(char *)((long)param_2 + 0xd) = (char)uVar17;
      if (uVar14 + 1 != uVar6) {
        *(undefined4 *)((long)param_2 + (ulong)uVar17 * 4 + 0x10) = puVar2[(int)uVar6];
        param_2[(ulong)uVar17 + 4] = (long)(pfVar4 + (long)(int)uVar6 * 3);
      }
      if (uVar14 != uVar8) {
        *(undefined4 *)((long)param_2 + (ulong)bVar7 * 4 + 0x10) = puVar2[(int)uVar8];
        param_2[(ulong)bVar7 + 4] = (long)(pfVar4 + (long)(int)uVar8 * 3);
      }
      (**(code **)(*param_2 + 0x1c8))(param_2);
      *(uint *)(param_2 + 8) = uVar6;
    }
    bVar7 = *(byte *)((long)param_2 + 0xd) ^ 1;
  }
  fVar19 = *(float *)param_2[(ulong)bVar7 + 4];
  *param_3 = fVar19;
joined_r0x020abb50:
  if (bVar10) {
    *param_3 = fVar19 + fVar23 * (pfVar4[(ulong)uVar8 * 3] - *pfVar4);
  }
  return;
code_r0x020aba58:
  if (uVar14 != uVar17) {
    *(char *)((long)param_2 + 0xd) = (char)uVar6;
    if (uVar14 + 1 != uVar17) {
      *pfVar1 = (float)puVar2[(int)uVar17];
      param_2[(ulong)uVar6 + 4] = (long)(pfVar4 + (long)(int)uVar17 * 3);
    }
    lVar3 = (long)(int)uVar17 + 1;
    if (uVar14 != (uint)lVar3) {
      *pfVar5 = (float)puVar2[lVar3];
      param_2[uVar12 + 4] = (long)(pfVar4 + lVar3 * 3);
    }
    (**(code **)(*param_2 + 0x1c8))(param_2);
    uVar12 = (ulong)*(byte *)((long)param_2 + 0xd);
    *(uint *)(param_2 + 8) = uVar17;
  }
  fVar19 = (fVar22 - *(float *)((long)param_2 + uVar12 * 4 + 0x10)) / *(float *)(param_2 + 3);
  fVar20 = fVar19 + -1.0;
  fVar19 = fVar19 * fVar19 * fVar20 * ((float *)param_2[(ulong)((uint)uVar12 ^ 1) + 4])[1] +
           ((float *)param_2[uVar12 + 4])[2] * fVar20 * fVar19 * fVar20 +
           *(float *)param_2[(ulong)((uint)uVar12 ^ 1) + 4] *
           fVar19 * fVar19 * (3.0 - (fVar19 + fVar19)) +
           *(float *)param_2[uVar12 + 4] * fVar20 * fVar20 * (fVar19 + fVar19 + 1.0);
  *param_3 = fVar19;
  goto joined_r0x020abb50;
code_r0x020ab94c:
  iVar13 = (int)param_2[8];
  if (iVar13 != 0) {
    bVar7 = *(byte *)((long)param_2 + 0xd);
    uVar6 = bVar7 ^ 1;
    *(char *)((long)param_2 + 0xd) = (char)uVar6;
    if (iVar13 == -1) {
code_r0x020ab984:
      *(undefined4 *)((long)param_2 + (ulong)bVar7 * 4 + 0x10) = *(undefined4 *)(lVar3 + 0x1c);
      param_2[(ulong)bVar7 + 4] = (long)(pfVar4 + 3);
    }
    else {
      *(undefined4 *)((long)param_2 + (ulong)uVar6 * 4 + 0x10) = *puVar2;
      param_2[(ulong)uVar6 + 4] = (long)pfVar4;
      if (iVar13 != 1) goto code_r0x020ab984;
    }
    (**(code **)(*param_2 + 0x1c8))(param_2);
    *(undefined4 *)(param_2 + 8) = 0;
  }
  bVar7 = *(byte *)((long)param_2 + 0xd);
  uVar11 = 0xffffffff;
code_r0x020ab9bc:
  *param_3 = *(float *)param_2[(ulong)bVar7 + 4];
  *(undefined4 *)(param_2 + 1) = uVar11;
  return;
}

// ==== Aska::TAafNormalController<Aska::AafType<Aska::AafControlPoint_Vector, false, false, 0u> >::CalcValueSub(void*, float, bool)
// vaddr 0x1fc4d90 | ghidra 0x20c4d90 | size 1888 | symbol _ZN4Aska20TAafNormalControllerINS_7AafTypeINS_22AafControlPoint_VectorELb0ELb0ELj0EEEE12CalcValueSubEPvfb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20TAafNormalControllerINS_7AafTypeINS_22AafControlPoint_VectorELb0ELb0ELj0EEEE12CalcValueSubEPvfb
               (ulong param_1,long *param_2,float *param_3,uint param_4)

{
  undefined4 *puVar1;
  long lVar2;
  float *pfVar3;
  float *pfVar4;
  uint uVar5;
  byte bVar6;
  uint uVar7;
  bool bVar8;
  bool bVar9;
  float *pfVar10;
  ulong uVar11;
  float *pfVar12;
  int iVar13;
  uint uVar14;
  undefined4 uVar15;
  float *pfVar16;
  uint uVar17;
  ulong uVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  
  lVar2 = (ulong)*(ushort *)(param_2[7] + 6) + param_2[7];
  uVar5 = *(uint *)(lVar2 + 0x14);
  uVar7 = uVar5 - 1;
  if (uVar5 == 0 || uVar7 == 0) {
    fVar19 = *(float *)((undefined8 *)param_2[4] + 1);
    *(undefined8 *)param_3 = *(undefined8 *)param_2[4];
    param_3[2] = fVar19;
    param_3[3] = 1.0;
    if ((int)param_2[1] == 1) {
      return;
    }
code_r0x020c4dec:
    *(undefined4 *)(param_2 + 1) = 1;
    return;
  }
  fVar21 = *(float *)(lVar2 + 0xc);
  fVar19 = *(float *)(lVar2 + 0x10);
  puVar1 = (undefined4 *)(lVar2 + 0x18);
  pfVar3 = (float *)(puVar1 + uVar5);
  uVar5 = uVar5 - 2;
  fVar20 = (float)param_1;
  if ((param_4 & 1) == 0) {
    fVar22 = fVar19 - fVar21;
    if (fVar20 <= fVar19) {
      if (fVar21 <= fVar20) goto code_r0x020c4e0c;
      switch(*(undefined1 *)(lVar2 + 8)) {
      case 0:
        goto code_r0x020c4f7c;
      case 1:
        iVar13 = (int)param_2[8];
        if (iVar13 == 0) goto code_r0x020c54b0;
        bVar6 = *(byte *)((long)param_2 + 0xd);
        uVar5 = bVar6 ^ 1;
        *(char *)((long)param_2 + 0xd) = (char)uVar5;
        if (iVar13 == -1) {
code_r0x020c5484:
          *(undefined4 *)((long)param_2 + (ulong)bVar6 * 4 + 0x10) = *(undefined4 *)(lVar2 + 0x1c);
          param_2[(ulong)bVar6 + 4] = (long)(pfVar3 + 9);
        }
        else {
          *(undefined4 *)((long)param_2 + (ulong)uVar5 * 4 + 0x10) = *puVar1;
          param_2[(ulong)uVar5 + 4] = (long)pfVar3;
          if (iVar13 != 1) goto code_r0x020c5484;
        }
        (**(code **)(*param_2 + 0x1c8))(param_2);
        *(undefined4 *)(param_2 + 8) = 0;
code_r0x020c54b0:
        (**(code **)(*param_2 + 0x150))(param_1,param_2,param_3);
        *(undefined4 *)(param_2 + 1) = 0xffffffff;
        return;
      case 2:
        goto code_r0x020c51e8;
      case 3:
        goto code_r0x020c5200;
      case 4:
        goto code_r0x020c524c;
      default:
        goto code_r0x020c5350;
      }
    }
    switch(*(undefined1 *)(lVar2 + 9)) {
    case 0:
      uVar14 = *(uint *)(param_2 + 8);
      if (uVar14 != uVar5) {
        bVar6 = *(byte *)((long)param_2 + 0xd);
        uVar17 = bVar6 ^ 1;
        *(char *)((long)param_2 + 0xd) = (char)uVar17;
        if (uVar14 + 1 != uVar5) {
          *(undefined4 *)((long)param_2 + (ulong)uVar17 * 4 + 0x10) = puVar1[(int)uVar5];
          param_2[(ulong)uVar17 + 4] = (long)(pfVar3 + (long)(int)uVar5 * 9);
        }
        if (uVar14 != uVar7) {
          *(undefined4 *)((long)param_2 + (ulong)bVar6 * 4 + 0x10) = puVar1[(int)uVar7];
          param_2[(ulong)bVar6 + 4] = (long)(pfVar3 + (long)(int)uVar7 * 9);
        }
        (**(code **)(*param_2 + 0x1c8))(param_2);
        *(uint *)(param_2 + 8) = uVar5;
      }
      uVar15 = 1;
      bVar6 = *(byte *)((long)param_2 + 0xd) ^ 1;
      goto code_r0x020c4ff0;
    case 1:
      uVar14 = *(uint *)(param_2 + 8);
      if (uVar14 != uVar5) {
        bVar6 = *(byte *)((long)param_2 + 0xd);
        uVar17 = bVar6 ^ 1;
        *(char *)((long)param_2 + 0xd) = (char)uVar17;
        if (uVar14 + 1 != uVar5) {
          *(undefined4 *)((long)param_2 + (ulong)uVar17 * 4 + 0x10) = puVar1[(int)uVar5];
          param_2[(ulong)uVar17 + 4] = (long)(pfVar3 + (long)(int)uVar5 * 9);
        }
        if (uVar14 != uVar7) {
          *(undefined4 *)((long)param_2 + (ulong)bVar6 * 4 + 0x10) = puVar1[(int)uVar7];
          param_2[(ulong)bVar6 + 4] = (long)(pfVar3 + (long)(int)uVar7 * 9);
        }
        (**(code **)(*param_2 + 0x1c8))(param_2);
        *(uint *)(param_2 + 8) = uVar5;
      }
      (**(code **)(*param_2 + 0x158))(param_1,param_2,param_3);
      goto code_r0x020c4dec;
    case 2:
code_r0x020c51e8:
      if (fVar22 == 0.0) {
        iVar13 = 0;
        fVar23 = 0.0;
      }
      else {
        fVar24 = (fVar20 - fVar21) / fVar22;
        fVar23 = fVar20 - fVar22 * (float)(int)fVar24;
        iVar13 = (int)fVar24;
      }
      bVar9 = false;
      *(int *)(param_2 + 1) = iVar13;
      fVar22 = 0.0;
      break;
    case 3:
code_r0x020c5200:
      fVar24 = 0.0;
      fVar23 = 0.0;
      if (fVar22 != 0.0) {
        fVar24 = (float)(int)((fVar20 - fVar21) / fVar22);
        fVar23 = fVar20 - fVar22 * fVar24;
      }
      bVar9 = (int)fVar24 != 0;
      *(int *)(param_2 + 1) = (int)fVar24;
      fVar22 = 0.0;
      if (bVar9) {
        fVar22 = fVar24;
      }
      break;
    case 4:
code_r0x020c524c:
      if (fVar22 != 0.0) {
        fVar23 = (fVar20 - fVar21) / fVar22;
        uVar14 = (uint)fVar23;
        fVar20 = fVar20 - fVar22 * (float)(int)fVar23;
        param_1 = (ulong)(uint)fVar20;
        *(uint *)(param_2 + 1) = uVar14;
        if ((uVar14 & 1) != 0) {
          bVar9 = false;
          fVar23 = (fVar21 + fVar21 + fVar22) - fVar20;
          fVar22 = 0.0;
          break;
        }
        goto code_r0x020c5350;
      }
      bVar9 = false;
      *(undefined4 *)(param_2 + 1) = 0;
      fVar22 = 0.0;
      fVar23 = 0.0;
      fVar24 = 0.0;
      bVar8 = bVar9;
      if (fVar21 < 0.0) goto code_r0x020c4e28;
      goto code_r0x020c535c;
    default:
code_r0x020c5350:
      fVar20 = (float)param_1;
      goto joined_r0x020c5358;
    }
    fVar24 = fVar22;
    bVar8 = bVar9;
    if (fVar21 < fVar23) goto code_r0x020c4e28;
code_r0x020c535c:
    bVar9 = bVar8;
    iVar13 = (int)param_2[8];
    if (iVar13 != 0) {
      bVar6 = *(byte *)((long)param_2 + 0xd);
      uVar5 = bVar6 ^ 1;
      *(char *)((long)param_2 + 0xd) = (char)uVar5;
      if (iVar13 == -1) {
code_r0x020c5394:
        *(undefined4 *)((long)param_2 + (ulong)bVar6 * 4 + 0x10) = *(undefined4 *)(lVar2 + 0x1c);
        param_2[(ulong)bVar6 + 4] = (long)(pfVar3 + 9);
      }
      else {
        *(undefined4 *)((long)param_2 + (ulong)uVar5 * 4 + 0x10) = *puVar1;
        param_2[(ulong)uVar5 + 4] = (long)pfVar3;
        if (iVar13 != 1) goto code_r0x020c5394;
      }
      (**(code **)(*param_2 + 0x1c8))(param_2);
      *(undefined4 *)(param_2 + 8) = 0;
    }
    bVar6 = *(byte *)((long)param_2 + 0xd);
  }
  else {
code_r0x020c4e0c:
    if ((int)param_2[1] == 0) goto code_r0x020c5350;
    *(undefined4 *)(param_2 + 1) = 0;
joined_r0x020c5358:
    bVar9 = false;
    fVar22 = 0.0;
    fVar23 = (float)param_1;
    fVar24 = fVar22;
    bVar8 = false;
    if (fVar20 <= fVar21) goto code_r0x020c535c;
code_r0x020c4e28:
    fVar24 = fVar22;
    if (fVar23 < fVar19) {
      uVar11 = (ulong)*(byte *)((long)param_2 + 0xd);
      uVar14 = *(uint *)(param_2 + 8);
      uVar5 = *(byte *)((long)param_2 + 0xd) ^ 1;
      pfVar4 = (float *)((long)param_2 + uVar11 * 4 + 0x10);
      pfVar10 = (float *)((long)param_2 + (ulong)uVar5 * 4 + 0x10);
      uVar18 = (ulong)uVar14;
      pfVar12 = pfVar10;
      pfVar16 = pfVar4;
      do {
        uVar17 = (uint)uVar18;
        if (*pfVar16 <= fVar23) {
          if (fVar23 < *pfVar12) goto code_r0x020c5094;
          iVar13 = 1;
        }
        else {
          iVar13 = -1;
        }
        uVar18 = (long)iVar13 + (long)(int)uVar17;
        pfVar16 = (float *)(puVar1 + uVar18);
        pfVar12 = pfVar16 + 1;
      } while( true );
    }
    uVar14 = *(uint *)(param_2 + 8);
    if (uVar14 != uVar5) {
      bVar6 = *(byte *)((long)param_2 + 0xd);
      uVar17 = bVar6 ^ 1;
      *(char *)((long)param_2 + 0xd) = (char)uVar17;
      if (uVar14 + 1 != uVar5) {
        *(undefined4 *)((long)param_2 + (ulong)uVar17 * 4 + 0x10) = puVar1[(int)uVar5];
        param_2[(ulong)uVar17 + 4] = (long)(pfVar3 + (long)(int)uVar5 * 9);
      }
      if (uVar14 != uVar7) {
        *(undefined4 *)((long)param_2 + (ulong)bVar6 * 4 + 0x10) = puVar1[(int)uVar7];
        param_2[(ulong)bVar6 + 4] = (long)(pfVar3 + (long)(int)uVar7 * 9);
      }
      (**(code **)(*param_2 + 0x1c8))(param_2);
      *(uint *)(param_2 + 8) = uVar5;
    }
    bVar6 = *(byte *)((long)param_2 + 0xd) ^ 1;
  }
  pfVar10 = (float *)param_2[(ulong)bVar6 + 4];
  fVar19 = *pfVar10;
  fVar21 = pfVar10[1];
  fVar20 = pfVar10[2];
  *param_3 = fVar19;
  param_3[1] = fVar21;
  param_3[2] = fVar20;
  param_3[3] = 1.0;
joined_r0x020c51e0:
  if (bVar9) {
    pfVar10 = pfVar3 + (ulong)uVar7 * 9;
    fVar22 = pfVar3[1];
    fVar23 = pfVar3[2];
    fVar26 = pfVar10[1];
    fVar25 = pfVar10[2];
    *param_3 = fVar24 * (*pfVar10 - *pfVar3) + fVar19;
    param_3[1] = fVar24 * (fVar26 - fVar22) + fVar21;
    param_3[2] = fVar24 * (fVar25 - fVar23) + fVar20;
  }
  return;
code_r0x020c5094:
  if (uVar14 != uVar17) {
    *(char *)((long)param_2 + 0xd) = (char)uVar5;
    if (uVar14 + 1 != uVar17) {
      *pfVar10 = (float)puVar1[(int)uVar17];
      param_2[(ulong)uVar5 + 4] = (long)(pfVar3 + (long)(int)uVar17 * 9);
    }
    lVar2 = (long)(int)uVar17 + 1;
    if (uVar14 != (uint)lVar2) {
      *pfVar4 = (float)puVar1[lVar2];
      param_2[uVar11 + 4] = (long)(pfVar3 + lVar2 * 9);
    }
    (**(code **)(*param_2 + 0x1c8))(param_2);
    uVar11 = (ulong)*(byte *)((long)param_2 + 0xd);
    *(uint *)(param_2 + 8) = uVar17;
  }
  pfVar12 = (float *)param_2[uVar11 + 4];
  pfVar10 = (float *)param_2[(ulong)((uint)uVar11 ^ 1) + 4];
  fVar19 = (fVar23 - *(float *)((long)param_2 + uVar11 * 4 + 0x10)) / *(float *)(param_2 + 3);
  fVar22 = fVar19 + -1.0;
  fVar26 = fVar19 * fVar19 * fVar22;
  fVar23 = fVar19 * fVar19 * (3.0 - (fVar19 + fVar19));
  fVar20 = fVar22 * fVar19 * fVar22;
  fVar22 = fVar22 * fVar22 * (fVar19 + fVar19 + 1.0);
  fVar19 = fVar23 * *pfVar10 + *pfVar12 * fVar22 + fVar20 * pfVar12[6] + fVar26 * pfVar10[3];
  fVar21 = fVar23 * pfVar10[1] + pfVar12[1] * fVar22 + fVar20 * pfVar12[7] + fVar26 * pfVar10[4];
  fVar20 = pfVar12[2] * fVar22 + fVar23 * pfVar10[2] + fVar20 * pfVar12[8] + fVar26 * pfVar10[5];
  param_3[3] = 1.0;
  *param_3 = fVar19;
  param_3[1] = fVar21;
  param_3[2] = fVar20;
  goto joined_r0x020c51e0;
code_r0x020c4f7c:
  iVar13 = (int)param_2[8];
  if (iVar13 != 0) {
    bVar6 = *(byte *)((long)param_2 + 0xd);
    uVar5 = bVar6 ^ 1;
    *(char *)((long)param_2 + 0xd) = (char)uVar5;
    if (iVar13 == -1) {
code_r0x020c4fb4:
      *(undefined4 *)((long)param_2 + (ulong)bVar6 * 4 + 0x10) = *(undefined4 *)(lVar2 + 0x1c);
      param_2[(ulong)bVar6 + 4] = (long)(pfVar3 + 9);
    }
    else {
      *(undefined4 *)((long)param_2 + (ulong)uVar5 * 4 + 0x10) = *puVar1;
      param_2[(ulong)uVar5 + 4] = (long)pfVar3;
      if (iVar13 != 1) goto code_r0x020c4fb4;
    }
    (**(code **)(*param_2 + 0x1c8))(param_2);
    *(undefined4 *)(param_2 + 8) = 0;
  }
  bVar6 = *(byte *)((long)param_2 + 0xd);
  uVar15 = 0xffffffff;
code_r0x020c4ff0:
  fVar19 = *(float *)((undefined8 *)param_2[(ulong)bVar6 + 4] + 1);
  *(undefined8 *)param_3 = *(undefined8 *)param_2[(ulong)bVar6 + 4];
  param_3[2] = fVar19;
  param_3[3] = 1.0;
  *(undefined4 *)(param_2 + 1) = uVar15;
  return;
}

// ==== Aska::TAafNormalController<Aska::AafType<Aska::AafControlPoint_Quaternion_Linear, false, false, 0u> >::CalcValueSub(void*, float, bool)
// vaddr 0x1fcf4ac | ghidra 0x20cf4ac | size 1660 | symbol _ZN4Aska20TAafNormalControllerINS_7AafTypeINS_33AafControlPoint_Quaternion_LinearELb0ELb0ELj0EEEE12CalcValueSubEPvfb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska20TAafNormalControllerINS_7AafTypeINS_33AafControlPoint_Quaternion_LinearELb0ELb0ELj0EEEE12CalcValueSubEPvfb
               (ulong param_1,long *param_2,undefined8 *param_3,ulong param_4)

{
  float *pfVar1;
  undefined4 *puVar2;
  long lVar3;
  float *pfVar4;
  float *pfVar5;
  uint uVar6;
  byte bVar7;
  uint uVar8;
  bool bVar9;
  bool bVar10;
  undefined4 uVar11;
  ulong uVar12;
  int iVar13;
  uint uVar14;
  float *pfVar15;
  float *pfVar16;
  uint uVar17;
  ulong uVar18;
  float fVar19;
  undefined8 uVar20;
  undefined8 uVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  
  lVar3 = (ulong)*(ushort *)(param_2[7] + 6) + param_2[7];
  uVar6 = *(uint *)(lVar3 + 0x14);
  uVar8 = uVar6 - 1;
  if (uVar6 == 0 || uVar8 == 0) {
    uVar20 = *(undefined8 *)param_2[4];
    param_3[1] = ((undefined8 *)param_2[4])[1];
    *param_3 = uVar20;
    if ((int)param_2[1] == 1) {
      return;
    }
code_r0x020cf500:
    *(undefined4 *)(param_2 + 1) = 1;
    return;
  }
  fVar22 = *(float *)(lVar3 + 0xc);
  fVar19 = *(float *)(lVar3 + 0x10);
  puVar2 = (undefined4 *)(lVar3 + 0x18);
  pfVar4 = (float *)(puVar2 + uVar6);
  uVar6 = uVar6 - 2;
  fVar26 = (float)param_1;
  if ((param_4 & 1) == 0) {
    fVar23 = fVar19 - fVar22;
    if (fVar26 <= fVar19) {
      if (fVar22 <= fVar26) goto code_r0x020cf520;
      switch(*(undefined1 *)(lVar3 + 8)) {
      case 0:
        goto code_r0x020cf68c;
      case 1:
        iVar13 = (int)param_2[8];
        if (iVar13 == 0) goto code_r0x020cfae8;
        bVar7 = *(byte *)((long)param_2 + 0xd);
        uVar6 = bVar7 ^ 1;
        *(char *)((long)param_2 + 0xd) = (char)uVar6;
        if (iVar13 == -1) {
code_r0x020cfabc:
          *(undefined4 *)((long)param_2 + (ulong)bVar7 * 4 + 0x10) = *(undefined4 *)(lVar3 + 0x1c);
          param_2[(ulong)bVar7 + 4] = (long)(pfVar4 + 4);
        }
        else {
          *(undefined4 *)((long)param_2 + (ulong)uVar6 * 4 + 0x10) = *puVar2;
          param_2[(ulong)uVar6 + 4] = (long)pfVar4;
          if (iVar13 != 1) goto code_r0x020cfabc;
        }
        (**(code **)(*param_2 + 0x1c8))(param_2);
        *(undefined4 *)(param_2 + 8) = 0;
code_r0x020cfae8:
        (**(code **)(*param_2 + 0x150))(param_1,param_2,param_3);
        *(undefined4 *)(param_2 + 1) = 0xffffffff;
        return;
      case 2:
        goto code_r0x020cf844;
      case 3:
        goto code_r0x020cf85c;
      case 4:
        goto code_r0x020cf8a8;
      default:
        goto code_r0x020cf9a4;
      }
    }
    switch(*(undefined1 *)(lVar3 + 9)) {
    case 0:
      uVar14 = *(uint *)(param_2 + 8);
      if (uVar14 != uVar6) {
        bVar7 = *(byte *)((long)param_2 + 0xd);
        uVar17 = bVar7 ^ 1;
        *(char *)((long)param_2 + 0xd) = (char)uVar17;
        if (uVar14 + 1 != uVar6) {
          *(undefined4 *)((long)param_2 + (ulong)uVar17 * 4 + 0x10) = puVar2[(int)uVar6];
          param_2[(ulong)uVar17 + 4] = (long)(pfVar4 + (long)(int)uVar6 * 4);
        }
        if (uVar14 != uVar8) {
          *(undefined4 *)((long)param_2 + (ulong)bVar7 * 4 + 0x10) = puVar2[(int)uVar8];
          param_2[(ulong)bVar7 + 4] = (long)(pfVar4 + (long)(int)uVar8 * 4);
        }
        (**(code **)(*param_2 + 0x1c8))(param_2);
        *(uint *)(param_2 + 8) = uVar6;
      }
      uVar21 = ((undefined8 *)param_2[(ulong)(*(byte *)((long)param_2 + 0xd) ^ 1) + 4])[1];
      uVar20 = *(undefined8 *)param_2[(ulong)(*(byte *)((long)param_2 + 0xd) ^ 1) + 4];
      uVar11 = 1;
      goto code_r0x020cf704;
    case 1:
      uVar14 = *(uint *)(param_2 + 8);
      if (uVar14 != uVar6) {
        bVar7 = *(byte *)((long)param_2 + 0xd);
        uVar17 = bVar7 ^ 1;
        *(char *)((long)param_2 + 0xd) = (char)uVar17;
        if (uVar14 + 1 != uVar6) {
          *(undefined4 *)((long)param_2 + (ulong)uVar17 * 4 + 0x10) = puVar2[(int)uVar6];
          param_2[(ulong)uVar17 + 4] = (long)(pfVar4 + (long)(int)uVar6 * 4);
        }
        if (uVar14 != uVar8) {
          *(undefined4 *)((long)param_2 + (ulong)bVar7 * 4 + 0x10) = puVar2[(int)uVar8];
          param_2[(ulong)bVar7 + 4] = (long)(pfVar4 + (long)(int)uVar8 * 4);
        }
        (**(code **)(*param_2 + 0x1c8))(param_2);
        *(uint *)(param_2 + 8) = uVar6;
      }
      (**(code **)(*param_2 + 0x158))(param_1,param_2,param_3);
      goto code_r0x020cf500;
    case 2:
code_r0x020cf844:
      if (fVar23 == 0.0) {
        iVar13 = 0;
        fVar24 = 0.0;
      }
      else {
        fVar25 = (fVar26 - fVar22) / fVar23;
        fVar24 = fVar26 - fVar23 * (float)(int)fVar25;
        iVar13 = (int)fVar25;
      }
      bVar10 = false;
      *(int *)(param_2 + 1) = iVar13;
      fVar23 = 0.0;
      break;
    case 3:
code_r0x020cf85c:
      fVar25 = 0.0;
      fVar24 = 0.0;
      if (fVar23 != 0.0) {
        fVar25 = (float)(int)((fVar26 - fVar22) / fVar23);
        fVar24 = fVar26 - fVar23 * fVar25;
      }
      bVar10 = (int)fVar25 != 0;
      *(int *)(param_2 + 1) = (int)fVar25;
      fVar23 = 0.0;
      if (bVar10) {
        fVar23 = fVar25;
      }
      break;
    case 4:
code_r0x020cf8a8:
      if (fVar23 != 0.0) {
        fVar24 = (fVar26 - fVar22) / fVar23;
        uVar14 = (uint)fVar24;
        fVar26 = fVar26 - fVar23 * (float)(int)fVar24;
        param_1 = (ulong)(uint)fVar26;
        *(uint *)(param_2 + 1) = uVar14;
        if ((uVar14 & 1) != 0) {
          bVar10 = false;
          fVar24 = (fVar22 + fVar22 + fVar23) - fVar26;
          fVar23 = 0.0;
          break;
        }
        goto code_r0x020cf9a4;
      }
      bVar10 = false;
      *(undefined4 *)(param_2 + 1) = 0;
      fVar23 = 0.0;
      fVar24 = 0.0;
      bVar9 = bVar10;
      if (fVar22 < 0.0) goto code_r0x020cf53c;
      goto code_r0x020cf9b0;
    default:
code_r0x020cf9a4:
      fVar26 = (float)param_1;
      goto joined_r0x020cf9ac;
    }
    bVar9 = bVar10;
    if (fVar22 < fVar24) goto code_r0x020cf53c;
code_r0x020cf9b0:
    bVar10 = bVar9;
    iVar13 = (int)param_2[8];
    if (iVar13 != 0) {
      bVar7 = *(byte *)((long)param_2 + 0xd);
      uVar6 = bVar7 ^ 1;
      *(char *)((long)param_2 + 0xd) = (char)uVar6;
      if (iVar13 == -1) {
code_r0x020cf9e8:
        *(undefined4 *)((long)param_2 + (ulong)bVar7 * 4 + 0x10) = *(undefined4 *)(lVar3 + 0x1c);
        param_2[(ulong)bVar7 + 4] = (long)(pfVar4 + 4);
      }
      else {
        *(undefined4 *)((long)param_2 + (ulong)uVar6 * 4 + 0x10) = *puVar2;
        param_2[(ulong)uVar6 + 4] = (long)pfVar4;
        if (iVar13 != 1) goto code_r0x020cf9e8;
      }
      (**(code **)(*param_2 + 0x1c8))(param_2);
      *(undefined4 *)(param_2 + 8) = 0;
    }
    bVar7 = *(byte *)((long)param_2 + 0xd);
  }
  else {
code_r0x020cf520:
    if ((int)param_2[1] == 0) goto code_r0x020cf9a4;
    *(undefined4 *)(param_2 + 1) = 0;
joined_r0x020cf9ac:
    fVar23 = 0.0;
    bVar10 = false;
    fVar24 = (float)param_1;
    bVar9 = false;
    if (fVar26 <= fVar22) goto code_r0x020cf9b0;
code_r0x020cf53c:
    if (fVar24 < fVar19) {
      uVar12 = (ulong)*(byte *)((long)param_2 + 0xd);
      uVar14 = *(uint *)(param_2 + 8);
      uVar6 = *(byte *)((long)param_2 + 0xd) ^ 1;
      pfVar5 = (float *)((long)param_2 + uVar12 * 4 + 0x10);
      pfVar1 = (float *)((long)param_2 + (ulong)uVar6 * 4 + 0x10);
      uVar18 = (ulong)uVar14;
      pfVar15 = pfVar1;
      pfVar16 = pfVar5;
      do {
        uVar17 = (uint)uVar18;
        if (*pfVar16 <= fVar24) {
          if (fVar24 < *pfVar15) goto code_r0x020cf790;
          iVar13 = 1;
        }
        else {
          iVar13 = -1;
        }
        uVar18 = (long)iVar13 + (long)(int)uVar17;
        pfVar16 = (float *)(puVar2 + uVar18);
        pfVar15 = pfVar16 + 1;
      } while( true );
    }
    uVar14 = *(uint *)(param_2 + 8);
    if (uVar14 != uVar6) {
      bVar7 = *(byte *)((long)param_2 + 0xd);
      uVar17 = bVar7 ^ 1;
      *(char *)((long)param_2 + 0xd) = (char)uVar17;
      if (uVar14 + 1 != uVar6) {
        *(undefined4 *)((long)param_2 + (ulong)uVar17 * 4 + 0x10) = puVar2[(int)uVar6];
        param_2[(ulong)uVar17 + 4] = (long)(pfVar4 + (long)(int)uVar6 * 4);
      }
      if (uVar14 != uVar8) {
        *(undefined4 *)((long)param_2 + (ulong)bVar7 * 4 + 0x10) = puVar2[(int)uVar8];
        param_2[(ulong)bVar7 + 4] = (long)(pfVar4 + (long)(int)uVar8 * 4);
      }
      (**(code **)(*param_2 + 0x1c8))(param_2);
      *(uint *)(param_2 + 8) = uVar6;
    }
    bVar7 = *(byte *)((long)param_2 + 0xd) ^ 1;
  }
  uVar20 = *(undefined8 *)param_2[(ulong)bVar7 + 4];
  param_3[1] = ((undefined8 *)param_2[(ulong)bVar7 + 4])[1];
  *param_3 = uVar20;
joined_r0x020cf83c:
  if (bVar10) {
    pfVar1 = pfVar4 + (ulong)uVar8 * 4;
    uStack_60 = CONCAT44(pfVar1[1] - pfVar4[1],*pfVar1 - *pfVar4);
    uStack_58 = CONCAT44(pfVar1[3] - pfVar4[3],pfVar1[2] - pfVar4[2]);
    Aska::AafControlPoint_Quaternion::AddLoop(Aska::Quaternion*, Aska::Quaternion*, float)(fVar23,param_3,&uStack_60);
  }
  return;
code_r0x020cf790:
  if (uVar14 != uVar17) {
    *(char *)((long)param_2 + 0xd) = (char)uVar6;
    if (uVar14 + 1 != uVar17) {
      *pfVar1 = (float)puVar2[(int)uVar17];
      param_2[(ulong)uVar6 + 4] = (long)(pfVar4 + (long)(int)uVar17 * 4);
    }
    lVar3 = (long)(int)uVar17 + 1;
    if (uVar14 != (uint)lVar3) {
      *pfVar5 = (float)puVar2[lVar3];
      param_2[uVar12 + 4] = (long)(pfVar4 + lVar3 * 4);
    }
    (**(code **)(*param_2 + 0x1c8))(param_2);
    uVar12 = (ulong)*(byte *)((long)param_2 + 0xd);
    *(uint *)(param_2 + 8) = uVar17;
  }
  uStack_58 = ((undefined8 *)param_2[uVar12 + 4])[1];
  uStack_60 = *(undefined8 *)param_2[uVar12 + 4];
  uStack_68 = ((undefined8 *)param_2[(ulong)((uint)uVar12 ^ 1) + 4])[1];
  uStack_70 = *(undefined8 *)param_2[(ulong)((uint)uVar12 ^ 1) + 4];
  Aska::Quaternion::Slerp(Aska::Quaternion const*, Aska::Quaternion const*, float)((fVar24 - *(float *)((long)param_2 + uVar12 * 4 + 0x10)) / *(float *)(param_2 + 3)
                  ,param_3,&uStack_60,&uStack_70);
  goto joined_r0x020cf83c;
code_r0x020cf68c:
  iVar13 = (int)param_2[8];
  if (iVar13 != 0) {
    bVar7 = *(byte *)((long)param_2 + 0xd);
    uVar6 = bVar7 ^ 1;
    *(char *)((long)param_2 + 0xd) = (char)uVar6;
    if (iVar13 == -1) {
code_r0x020cf6c4:
      *(undefined4 *)((long)param_2 + (ulong)bVar7 * 4 + 0x10) = *(undefined4 *)(lVar3 + 0x1c);
      param_2[(ulong)bVar7 + 4] = (long)(pfVar4 + 4);
    }
    else {
      *(undefined4 *)((long)param_2 + (ulong)uVar6 * 4 + 0x10) = *puVar2;
      param_2[(ulong)uVar6 + 4] = (long)pfVar4;
      if (iVar13 != 1) goto code_r0x020cf6c4;
    }
    (**(code **)(*param_2 + 0x1c8))(param_2);
    *(undefined4 *)(param_2 + 8) = 0;
  }
  uVar21 = ((undefined8 *)param_2[(ulong)*(byte *)((long)param_2 + 0xd) + 4])[1];
  uVar20 = *(undefined8 *)param_2[(ulong)*(byte *)((long)param_2 + 0xd) + 4];
  uVar11 = 0xffffffff;
code_r0x020cf704:
  param_3[1] = uVar21;
  *param_3 = uVar20;
  *(undefined4 *)(param_2 + 1) = uVar11;
  return;
}

// ==== Aska::TAafTranslateXYZController<Aska::TAafNormalController<Aska::AafType<Aska::AafControlPoint_Vector_Step, false, false, 0u> > >::SetValueToTarget(void*, Aska::AafSetValueArg*)
// vaddr 0x1fd97a8 | ghidra 0x20d97a8 | size 76 | symbol _ZN4Aska26TAafTranslateXYZControllerINS_20TAafNormalControllerINS_7AafTypeINS_27AafControlPoint_Vector_StepELb0ELb0ELj0EEEEEE16SetValueToTargetEPvPNS_14AafSetValueArgE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska26TAafTranslateXYZControllerINS_20TAafNormalControllerINS_7AafTypeINS_27AafControlPoint_Vector_StepELb0ELb0ELj0EEEEEE16SetValueToTargetEPvPNS_14AafSetValueArgE
               (long *param_1,undefined8 param_2,long param_3)

{
  long lVar1;
  
  lVar1 = *(long *)(param_3 + 8);
  if ((*(byte *)(lVar1 + 0x128) & 1) == 0) {
    Aska::HierarchicalObjectContainer::UpdateHierarchically()(lVar1 + 0x30);
    lVar1 = *(long *)(param_3 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x020d97f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x160))(param_1,lVar1 + 0x80,param_2);
  return;
}

// ==== Aska::TAafRotateQuaternionController<Aska::TAafNormalController<Aska::AafType<Aska::AafControlPoint_Quaternion_Step, false, false, 0u> > >::SetValueToTarget(void*, Aska::AafSetValueArg*)
// vaddr 0x1fdee48 | ghidra 0x20dee48 | size 76 | symbol _ZN4Aska30TAafRotateQuaternionControllerINS_20TAafNormalControllerINS_7AafTypeINS_31AafControlPoint_Quaternion_StepELb0ELb0ELj0EEEEEE16SetValueToTargetEPvPNS_14AafSetValueArgE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska30TAafRotateQuaternionControllerINS_20TAafNormalControllerINS_7AafTypeINS_31AafControlPoint_Quaternion_StepELb0ELb0ELj0EEEEEE16SetValueToTargetEPvPNS_14AafSetValueArgE
               (long *param_1,undefined8 param_2,long param_3)

{
  long lVar1;
  
  lVar1 = *(long *)(param_3 + 8);
  if ((*(byte *)(lVar1 + 0x128) & 1) == 0) {
    Aska::HierarchicalObjectContainer::UpdateHierarchically()(lVar1 + 0x30);
    lVar1 = *(long *)(param_3 + 8);
  }
                    /* WARNING: Could not recover jumptable at 0x020dee90. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x160))(param_1,lVar1 + 0x90,param_2);
  return;
}

// ==== Aska::AafKeyframeData_Quaternion_Linear_U48EX::GetValue(float*) const
// vaddr 0x1fe9ebc | ghidra 0x20e9ebc | size 368 | symbol _ZNK4Aska39AafKeyframeData_Quaternion_Linear_U48EX8GetValueEPf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZNK4Aska39AafKeyframeData_Quaternion_Linear_U48EX8GetValueEPf(uint *param_1,float *param_2)

{
  uint uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  uVar1 = param_1[1];
  fVar2 = (float)(uVar1 >> 0x1f | (*param_1 & 0xffff) << 1) / _UNK_0298ee78;
  fVar3 = 1.0 - fVar2 * fVar2;
  fVar2 = 0.0;
  if ((0.0 <= fVar3) && (fVar2 = fVar3, 1.0 < fVar3)) {
    fVar2 = 1.0;
  }
  fVar3 = (float)(uVar1 & 0x3fff) * _UNK_0298ee7c;
  fVar8 = (float)(uVar1 >> 0xe & 0x3fff) * _UNK_0298ee7c;
  fVar4 = (float)cosf(fVar3);
  fVar5 = (float)sinf(fVar3);
  fVar6 = (float)cosf(fVar8);
  fVar8 = (float)sinf(fVar8);
  fVar3 = fVar5 * fVar6;
  if ((uVar1 & 0x40000000) != 0) {
    fVar3 = -(fVar5 * fVar6);
  }
  fVar6 = 1.0 - fVar2 * fVar2;
  if ((uVar1 & 0x20000000) != 0) {
    fVar4 = -fVar4;
  }
  fVar7 = SQRT(fVar6);
  fVar9 = fVar5 * fVar8;
  if ((uVar1 & 0x10000000) != 0) {
    fVar9 = -(fVar5 * fVar8);
  }
  if (NAN(fVar7)) {
    fVar7 = (float)sqrtf(fVar6);
  }
  fVar3 = fVar3 * fVar7;
  fVar4 = fVar4 * fVar7;
  fVar7 = fVar7 * fVar9;
  fVar5 = fVar2 * fVar2 + fVar3 * fVar3 + fVar4 * fVar4 + fVar7 * fVar7;
  if (_UNK_027e519c < fVar5) {
    fVar6 = SQRT(fVar5);
    if (NAN(fVar6)) {
      fVar6 = (float)sqrtf(fVar5);
    }
    fVar3 = fVar3 / fVar6;
    fVar4 = fVar4 / fVar6;
    fVar7 = fVar7 / fVar6;
    fVar2 = fVar2 / fVar6;
  }
  *param_2 = fVar3;
  param_2[1] = fVar4;
  param_2[2] = fVar7;
  param_2[3] = fVar2;
  return;
}
