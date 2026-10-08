// port/decomp/dynamics/adm.c: Ghidra decompiles for the dynamics subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 14:41 UTC: tools/decomp.sh '--into' 'dynamics/adm' ' Aska::(ArticulatedDynamics\w*|ADM\w*)(<[^(]*>)?::[~\w<>]+\('

// ==== Aska::ArticulatedDynamicsManagerBase::Scale(float, Aska::AsfHandler*)
// vaddr 0x2072c94 | ghidra 0x2172c94 | size 604 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase5ScaleEfPNS_10AsfHandlerE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase5ScaleEfPNS_10AsfHandlerE
               (undefined8 param_1,long param_2)

{
  long lVar1;
  ulong uVar2;
  int iVar3;
  long lVar4;
  float *pfVar5;
  long lVar6;
  float fVar7;
  
  fVar7 = (float)param_1;
  if ((fVar7 != 1.0) && (param_2 != 0)) {
    for (lVar1 = Aska::AsfHandler::SearchFirstByKind(unsigned char) const(param_2,0xc); lVar1 != 0;
        lVar1 = Aska::AsfHandler::SearchNextByKind(unsigned char, Aska::IAnimatable const*) const(param_2,0xc,lVar1)) {
      if ((*(long *)(lVar1 + 0x198) != 0) &&
         (uVar2 = Aska::IAnimatable::IsThisIt(unsigned short) const(*(long *)(lVar1 + 0x198),0xf171), (uVar2 & 1) != 0)) {
        lVar4 = *(long *)(lVar1 + 0x198);
        *(float *)(lVar4 + 0xf4) = *(float *)(lVar4 + 0xf4) * fVar7;
        *(float *)(lVar4 + 0x40) = *(float *)(lVar4 + 0x40) * fVar7;
        *(float *)(lVar4 + 0x44) = *(float *)(lVar4 + 0x44) * fVar7;
        *(float *)(lVar4 + 0x48) = *(float *)(lVar4 + 0x48) * fVar7;
        if (0 < (long)*(short *)(lVar4 + 0x60)) {
          lVar6 = *(long *)(lVar4 + 0x70);
          uVar2 = (long)*(short *)(lVar4 + 0x60) & 0xffffffff;
          do {
            Aska::ADMJoint::Scale(float)(param_1,lVar6);
            uVar2 = uVar2 - 1;
            lVar6 = lVar6 + 0x1c0;
          } while (uVar2 != 0);
        }
        iVar3 = (int)*(short *)(lVar4 + 0x62);
        if (0 < *(short *)(lVar4 + 0x62)) {
          pfVar5 = *(float **)(lVar4 + 0x78);
          do {
            iVar3 = iVar3 + -1;
            pfVar5[9] = pfVar5[9] * fVar7;
            pfVar5[10] = pfVar5[10] * fVar7;
            *pfVar5 = *pfVar5 * fVar7;
            pfVar5[1] = pfVar5[1] * fVar7;
            pfVar5[2] = pfVar5[2] * fVar7;
            pfVar5 = pfVar5 + 0x14;
          } while (iVar3 != 0);
        }
      }
    }
    for (lVar1 = Aska::AsfHandler::SearchFirstByKind(unsigned char) const(param_2,0x13); lVar1 != 0;
        lVar1 = Aska::AsfHandler::SearchNextByKind(unsigned char, Aska::IAnimatable const*) const(param_2,0x13,lVar1)) {
      if ((*(long *)(lVar1 + 0x198) != 0) &&
         (uVar2 = Aska::IAnimatable::IsThisIt(unsigned short) const(*(long *)(lVar1 + 0x198),0xf151), (uVar2 & 1) != 0)) {
        lVar4 = *(long *)(lVar1 + 0x198);
        *(float *)(lVar4 + 0x90) = *(float *)(lVar4 + 0x90) * fVar7;
        *(float *)(lVar4 + 0x94) = *(float *)(lVar4 + 0x94) * fVar7;
        *(float *)(lVar4 + 0x98) = *(float *)(lVar4 + 0x98) * fVar7;
      }
    }
    for (lVar1 = Aska::AsfHandler::SearchFirstByKind(unsigned char) const(param_2,0x14); lVar1 != 0;
        lVar1 = Aska::AsfHandler::SearchNextByKind(unsigned char, Aska::IAnimatable const*) const(param_2,0x14,lVar1)) {
      if ((*(long *)(lVar1 + 0x198) != 0) &&
         (uVar2 = Aska::IAnimatable::IsThisIt(unsigned short) const(*(long *)(lVar1 + 0x198),0xf152), (uVar2 & 1) != 0)) {
        *(float *)(*(long *)(lVar1 + 0x198) + 0x80) =
             *(float *)(*(long *)(lVar1 + 0x198) + 0x80) * fVar7;
      }
    }
    for (lVar1 = Aska::AsfHandler::SearchFirstByKind(unsigned char) const(param_2,0x15); lVar1 != 0;
        lVar1 = Aska::AsfHandler::SearchNextByKind(unsigned char, Aska::IAnimatable const*) const(param_2,0x15,lVar1)) {
      if ((*(long *)(lVar1 + 0x198) != 0) &&
         (uVar2 = Aska::IAnimatable::IsThisIt(unsigned short) const(*(long *)(lVar1 + 0x198),0xf153), (uVar2 & 1) != 0)) {
        lVar4 = *(long *)(lVar1 + 0x198);
        *(float *)(lVar4 + 0xe0) = *(float *)(lVar4 + 0xe0) * fVar7;
        *(float *)(lVar4 + 0xb0) = *(float *)(lVar4 + 0xb0) * fVar7;
        *(float *)(lVar4 + 0xb4) = *(float *)(lVar4 + 0xb4) * fVar7;
        *(float *)(lVar4 + 0xb8) = *(float *)(lVar4 + 0xb8) * fVar7;
      }
    }
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::SimulateNotifyHandler(float)
// vaddr 0x2072f00 | ghidra 0x2172f00 | size 508 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase21SimulateNotifyHandlerEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase21SimulateNotifyHandlerEf
               (undefined8 param_1,long *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  long *plVar4;
  ulong uVar5;
  undefined4 uVar6;
  
  if ((int)param_2[0x1d] == 1) {
    iVar3 = (int)param_2[0x23];
    if (iVar3 == 1) {
      uVar2 = (uint)*(byte *)((long)param_2 + 0xe1);
      if (*(byte *)((long)param_2 + 0xe1) != 0) {
        *(undefined1 *)((long)param_2 + 0xe2) = 1;
        uVar1 = *(undefined4 *)((long)param_2 + 0x114);
        uVar6 = *(undefined4 *)((long)param_2 + 0x11c);
        if ((0 < (long)*(short *)((long)param_2 + 100)) &&
           (plVar4 = (long *)param_2[0x29], plVar4 != (long *)0x0)) {
          uVar5 = (long)*(short *)((long)param_2 + 100) & 0xffffffff;
          do {
            if ((long *)*plVar4 != (long *)0x0) {
              (**(code **)(*(long *)*plVar4 + 0x78))();
            }
            uVar5 = uVar5 - 1;
            plVar4 = plVar4 + 1;
          } while (uVar5 != 0);
        }
        if ((0 < (long)*(short *)((long)param_2 + 0x66)) &&
           (plVar4 = (long *)param_2[0x2a], plVar4 != (long *)0x0)) {
          uVar5 = (long)*(short *)((long)param_2 + 0x66) & 0xffffffff;
          do {
            if ((long *)*plVar4 != (long *)0x0) {
              (**(code **)(*(long *)*plVar4 + 0x78))();
            }
            uVar5 = uVar5 - 1;
            plVar4 = plVar4 + 1;
          } while (uVar5 != 0);
        }
        (**(code **)(*param_2 + 0x70))(param_1,uVar6,param_2,uVar1);
        *(undefined2 *)((long)param_2 + 0xe2) = 0x100;
        uVar2 = (int)param_2[0x23] - 1;
      }
      *(uint *)(param_2 + 0x23) = uVar2;
      *(undefined4 *)(param_2 + 0x1d) = 0;
    }
    else {
      if (*(char *)((long)param_2 + 0xe1) != '\0') {
        *(undefined1 *)((long)param_2 + 0xe2) = 1;
        if ((0 < (long)*(short *)((long)param_2 + 100)) &&
           (plVar4 = (long *)param_2[0x29], plVar4 != (long *)0x0)) {
          uVar5 = (long)*(short *)((long)param_2 + 100) & 0xffffffff;
          do {
            if ((long *)*plVar4 != (long *)0x0) {
              (**(code **)(*(long *)*plVar4 + 0x78))();
            }
            uVar5 = uVar5 - 1;
            plVar4 = plVar4 + 1;
          } while (uVar5 != 0);
        }
        if ((0 < (long)*(short *)((long)param_2 + 0x66)) &&
           (plVar4 = (long *)param_2[0x2a], plVar4 != (long *)0x0)) {
          uVar5 = (long)*(short *)((long)param_2 + 0x66) & 0xffffffff;
          do {
            if ((long *)*plVar4 != (long *)0x0) {
              (**(code **)(*(long *)*plVar4 + 0x78))();
            }
            uVar5 = uVar5 - 1;
            plVar4 = plVar4 + 1;
          } while (uVar5 != 0);
        }
        uVar1 = *(undefined4 *)((long)param_2 + 0xec);
        (**(code **)(*param_2 + 0x70))(param_1,0,param_2,*(undefined4 *)((long)param_2 + 0x114));
        iVar3 = (int)param_2[0x23];
        *(undefined4 *)((long)param_2 + 0xec) = uVar1;
        *(undefined1 *)((long)param_2 + 0xe2) = 0;
      }
      *(int *)(param_2 + 0x23) = iVar3 + -1;
      if (iVar3 + -1 == 0 || iVar3 < 1) {
        *(undefined4 *)(param_2 + 0x1d) = 0;
        *(undefined1 *)(param_2 + 0x1c) = *(undefined1 *)((long)param_2 + 0xe1);
      }
      else {
        *(undefined1 *)(param_2 + 0x1c) = 0;
      }
    }
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x02173018. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_2 + 0x70))(param_1,0,param_2,1);
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::ConvergeMain(int, float, float)
// vaddr 0x20730fc | ghidra 0x21730fc | size 216 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase12ConvergeMainEiff | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase12ConvergeMainEiff
               (undefined8 param_1,undefined8 param_2,long *param_3,undefined4 param_4)

{
  long *plVar1;
  ulong uVar2;
  
  if (*(char *)((long)param_3 + 0xe1) != '\0') {
    *(undefined1 *)((long)param_3 + 0xe2) = 1;
    if ((0 < (long)*(short *)((long)param_3 + 100)) &&
       (plVar1 = (long *)param_3[0x29], plVar1 != (long *)0x0)) {
      uVar2 = (long)*(short *)((long)param_3 + 100) & 0xffffffff;
      do {
        if ((long *)*plVar1 != (long *)0x0) {
          (**(code **)(*(long *)*plVar1 + 0x78))();
        }
        uVar2 = uVar2 - 1;
        plVar1 = plVar1 + 1;
      } while (uVar2 != 0);
    }
    if ((0 < (long)*(short *)((long)param_3 + 0x66)) &&
       (plVar1 = (long *)param_3[0x2a], plVar1 != (long *)0x0)) {
      uVar2 = (long)*(short *)((long)param_3 + 0x66) & 0xffffffff;
      do {
        if ((long *)*plVar1 != (long *)0x0) {
          (**(code **)(*(long *)*plVar1 + 0x78))();
        }
        uVar2 = uVar2 - 1;
        plVar1 = plVar1 + 1;
      } while (uVar2 != 0);
    }
    (**(code **)(*param_3 + 0x70))(param_2,param_1,param_3,param_4);
    *(undefined2 *)((long)param_3 + 0xe2) = 0x100;
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::ResetPrimitives()
// vaddr 0x20731d4 | ghidra 0x21731d4 | size 144 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase15ResetPrimitivesEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase15ResetPrimitivesEv(long param_1)

{
  long *plVar1;
  ulong uVar2;
  
  plVar1 = *(long **)(param_1 + 0x148);
  if ((plVar1 != (long *)0x0) && (0 < *(short *)(param_1 + 100))) {
    uVar2 = (ulong)(uint)(int)*(short *)(param_1 + 100);
    do {
      if ((long *)*plVar1 != (long *)0x0) {
        (**(code **)(*(long *)*plVar1 + 0x78))();
      }
      uVar2 = uVar2 - 1;
      plVar1 = plVar1 + 1;
    } while (uVar2 != 0);
  }
  plVar1 = *(long **)(param_1 + 0x150);
  if ((plVar1 != (long *)0x0) && (0 < *(short *)(param_1 + 0x66))) {
    uVar2 = (ulong)(uint)(int)*(short *)(param_1 + 0x66);
    do {
      if ((long *)*plVar1 != (long *)0x0) {
        (**(code **)(*(long *)*plVar1 + 0x78))();
      }
      uVar2 = uVar2 - 1;
      plVar1 = plVar1 + 1;
    } while (uVar2 != 0);
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::AddWorldCollision(Aska::DynamicsPrimitive*, unsigned char)
// vaddr 0x2073264 | ghidra 0x2173264 | size 164 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase17AddWorldCollisionEPNS_17DynamicsPrimitiveEh | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase17AddWorldCollisionEPNS_17DynamicsPrimitiveEh
               (long *param_1,undefined1 param_2)

{
  byte bVar1;
  undefined *puVar2;
  undefined *puVar3;
  ulong uVar4;
  long lVar5;
  
  puVar3 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_pWorldCollisionListE_02cc4750;
  puVar2 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase28m_ucDeleteWorldCollisionListE_02cb8738;
  if (param_1 != (long *)0x0) {
    bVar1 = *PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0;
    uVar4 = (ulong)bVar1;
    if (uVar4 < 0x10) {
      if (bVar1 != 0) {
        lVar5 = 0;
        do {
          if (*(long **)(
                        PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_pWorldCollisionListE_02cc4750
                        + lVar5 * 8) == param_1) {
            return;
          }
          lVar5 = lVar5 + 1;
        } while (lVar5 < (long)uVar4);
      }
      if ((ulong)(byte)*PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98
          != 0) {
        lVar5 = 0;
        do {
          if (*(long **)(
                        PTR__ZN4Aska30ArticulatedDynamicsManagerBase22m_pWorldConstraintListE_02cbc740
                        + lVar5 * 8) == param_1) {
            return;
          }
          lVar5 = lVar5 + 1;
        } while (lVar5 < (long)(ulong)(byte)*
                                            PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98
                );
      }
      *PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0 = bVar1 + 1;
      puVar2[uVar4] = param_2;
      *(long **)(puVar3 + uVar4 * 8) = param_1;
                    /* WARNING: Could not recover jumptable at 0x02173300. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_1 + 0x48))();
      return;
    }
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::WorldCollisionOrConstraintExists(Aska::DynamicsPrimitive*)
// vaddr 0x2073308 | ghidra 0x2173308 | size 128 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase32WorldCollisionOrConstraintExistsEPNS_17DynamicsPrimitiveE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska30ArticulatedDynamicsManagerBase32WorldCollisionOrConstraintExistsEPNS_17DynamicsPrimitiveE
          (long param_1)

{
  long lVar1;
  
  if ((ulong)(byte)*PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0 != 0)
  {
    lVar1 = 0;
    do {
      if (*(long *)(PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_pWorldCollisionListE_02cc4750 +
                   lVar1 * 8) == param_1) {
        return 1;
      }
      lVar1 = lVar1 + 1;
    } while (lVar1 < (long)(ulong)(byte)*
                                        PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0
            );
  }
  if ((ulong)(byte)*PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98 != 0
     ) {
    lVar1 = 0;
    do {
      if (*(long *)(PTR__ZN4Aska30ArticulatedDynamicsManagerBase22m_pWorldConstraintListE_02cbc740 +
                   lVar1 * 8) == param_1) {
        return 1;
      }
      lVar1 = lVar1 + 1;
    } while (lVar1 < (long)(ulong)(byte)*
                                        PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98
            );
    return 0;
  }
  return 0;
}

// ==== Aska::ArticulatedDynamicsManagerBase::DeleteWorldCollision(Aska::DynamicsPrimitive*, bool)
// vaddr 0x2073388 | ghidra 0x2173388 | size 284 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase20DeleteWorldCollisionEPNS_17DynamicsPrimitiveEb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase20DeleteWorldCollisionEPNS_17DynamicsPrimitiveEb
               (long *param_1,ulong param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  uint uVar4;
  uint uVar5;
  
  puVar3 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_pWorldCollisionListE_02cc4750;
  puVar2 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0;
  uVar4 = (uint)(byte)*PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0;
  if (*PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0 != 0) {
    if ((param_2 & 1) == 0) {
      uVar5 = 0;
      do {
        if (*(long **)(puVar3 + (long)(int)uVar5 * 8) == param_1) {
          if ((uVar4 & 0xff) == 1) goto code_r0x02173480;
          uVar1 = ~uVar5 + (uVar4 & 0xff);
          memmove(puVar3 + (long)(int)uVar5 * 8,puVar3 + (long)(int)uVar5 * 8 + 8,
                          -(ulong)(uVar1 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar1 << 3);
          uVar4 = uVar4 - 1;
          uVar5 = uVar5 - 1;
          *puVar2 = (char)uVar4;
        }
        uVar5 = uVar5 + 1;
      } while ((int)uVar5 < (int)(uVar4 & 0xff));
    }
    else {
      uVar5 = 0;
      do {
        if (*(long **)(puVar3 + (long)(int)uVar5 * 8) == param_1) {
          (**(code **)(*param_1 + 0x40))(param_1);
          uVar4 = (byte)*puVar2 - 1;
          if (uVar4 == 0) {
code_r0x02173480:
            puVar3 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_pWorldCollisionListE_02cc4750;
            *puVar2 = 0;
            *(undefined8 *)puVar3 = 0;
            return;
          }
          uVar1 = ~uVar5 + (uint)(byte)*puVar2;
          memmove(puVar3 + (long)(int)uVar5 * 8,puVar3 + (long)(int)uVar5 * 8 + 8,
                          -(ulong)(uVar1 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar1 << 3);
          uVar5 = uVar5 - 1;
          *puVar2 = (char)uVar4;
        }
        uVar5 = uVar5 + 1;
      } while ((int)uVar5 < (int)(uVar4 & 0xff));
    }
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::DeleteAllWorldCollision(unsigned char)
// vaddr 0x20734a4 | ghidra 0x21734a4 | size 308 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase23DeleteAllWorldCollisionEh | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase23DeleteAllWorldCollisionEh(char param_1)

{
  uint uVar1;
  uint uVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  uint uVar6;
  ulong uVar7;
  ulong uVar8;
  int iVar9;
  uint uVar10;
  long lVar11;
  
  puVar5 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_pWorldCollisionListE_02cc4750;
  puVar4 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0;
  puVar3 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase28m_ucDeleteWorldCollisionListE_02cb8738;
  uVar7 = (ulong)(byte)*PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0;
  if (*PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0 != 0) {
    lVar11 = 0;
    do {
      if ((*(long **)(puVar5 + lVar11 * 8) != (long *)0x0) && (puVar3[lVar11] == param_1)) {
        (**(code **)(**(long **)(puVar5 + lVar11 * 8) + 0x40))();
        uVar7 = (ulong)(byte)*puVar4;
        *(undefined8 *)(puVar5 + lVar11 * 8) = 0;
      }
      lVar11 = lVar11 + 1;
      uVar6 = (uint)uVar7;
    } while (lVar11 < (long)uVar7);
    if (uVar6 != 0) {
      iVar9 = 0;
      uVar8 = 0;
      uVar10 = 1;
      while (*(long *)(puVar5 + uVar8 * 8) != 0) {
        uVar8 = uVar8 + 1;
        uVar10 = uVar10 + 1;
        iVar9 = iVar9 + -1;
        if ((long)uVar7 <= (long)uVar8) goto joined_r0x021735a4;
      }
      uVar1 = uVar10;
      if ((int)uVar10 <= (int)uVar6) {
        uVar1 = uVar6;
      }
      uVar1 = uVar1 + iVar9;
      if (uVar1 < 2) goto code_r0x02173594;
      uVar2 = uVar10;
      if ((int)uVar10 <= (int)uVar6) {
        uVar2 = uVar6;
      }
      if ((uVar1 & 0xfffffffe) == 0) goto code_r0x02173594;
      if ((int)uVar10 <= (int)uVar6) {
        uVar10 = uVar6;
      }
      uVar8 = (uVar2 + iVar9 & 0xfffffffe) + uVar8;
      uVar10 = uVar10 + iVar9 & 0xfffffffe;
      do {
        uVar10 = uVar10 - 2;
      } while (uVar10 != 0);
      if (uVar1 != (uVar1 & 0xfffffffe)) {
code_r0x02173594:
        do {
          uVar10 = (int)uVar8 + 1;
          uVar8 = (ulong)uVar10;
        } while ((int)uVar10 < (int)uVar6);
      }
joined_r0x021735a4:
      while ((uVar6 != 0 && (*(long *)(puVar5 + (ulong)((uint)uVar7 & 0xff) * 8 + -8) == 0))) {
        uVar10 = (uint)uVar7 - 1;
        uVar7 = (ulong)uVar10;
        uVar6 = uVar10 & 0xff;
        *puVar4 = (char)uVar10;
      }
    }
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::CountWorldCollision()
// vaddr 0x20735d8 | ghidra 0x21735d8 | size 192 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase19CountWorldCollisionEv | lib libSOA-3.7.0.so | 2026-10-08
int _ZN4Aska30ArticulatedDynamicsManagerBase19CountWorldCollisionEv(void)

{
  long *plVar1;
  byte bVar2;
  long *plVar3;
  long *plVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  long *plVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  
  bVar2 = *PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0;
  uVar5 = (ulong)bVar2;
  if (uVar5 == 0) {
    return 0;
  }
  if (bVar2 < 4) {
    lVar6 = 0;
  }
  else {
    lVar6 = uVar5 - (uVar5 & 3);
    if (lVar6 != 0) {
      iVar9 = 0;
      iVar10 = 0;
      plVar8 = (long *)(
                       PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_pWorldCollisionListE_02cc4750
                       + 0x10);
      iVar11 = 0;
      iVar12 = 0;
      lVar7 = lVar6;
      do {
        plVar1 = plVar8 + -2;
        plVar3 = plVar8 + -1;
        plVar4 = plVar8 + 1;
        lVar15 = *plVar8;
        lVar7 = lVar7 + -4;
        plVar8 = plVar8 + 4;
        lVar13 = -(ulong)(*plVar1 == 0);
        lVar14 = -(ulong)(*plVar3 == 0);
        lVar15 = -(ulong)(lVar15 == 0);
        lVar16 = -(ulong)(*plVar4 == 0);
        iVar9 = iVar9 - CONCAT13(~(byte)((ulong)lVar13 >> 0x18),
                                 CONCAT12(~(byte)((ulong)lVar13 >> 0x10),
                                          CONCAT11(~(byte)((ulong)lVar13 >> 8),~(byte)lVar13)));
        iVar10 = iVar10 - CONCAT13(~(byte)((ulong)lVar14 >> 0x18),
                                   CONCAT12(~(byte)((ulong)lVar14 >> 0x10),
                                            CONCAT11(~(byte)((ulong)lVar14 >> 8),~(byte)lVar14)));
        iVar11 = iVar11 - CONCAT13(~(byte)((ulong)lVar15 >> 0x18),
                                   CONCAT12(~(byte)((ulong)lVar15 >> 0x10),
                                            CONCAT11(~(byte)((ulong)lVar15 >> 8),~(byte)lVar15)));
        iVar12 = iVar12 - CONCAT13(~(byte)((ulong)lVar16 >> 0x18),
                                   CONCAT12(~(byte)((ulong)lVar16 >> 0x10),
                                            CONCAT11(~(byte)((ulong)lVar16 >> 8),~(byte)lVar16)));
      } while (lVar7 != 0);
      iVar9 = iVar11 + iVar9 + iVar12 + iVar10;
      if ((bVar2 & 3) == 0) {
        return iVar9;
      }
      goto code_r0x0217367c;
    }
  }
  iVar9 = 0;
code_r0x0217367c:
  do {
    lVar7 = lVar6 * 8;
    lVar6 = lVar6 + 1;
    if (*(long *)(PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_pWorldCollisionListE_02cc4750 +
                 lVar7) != 0) {
      iVar9 = iVar9 + 1;
    }
  } while (lVar6 < (long)uVar5);
  return iVar9;
}

// ==== Aska::ArticulatedDynamicsManagerBase::CountWorldConstraint()
// vaddr 0x2073698 | ghidra 0x2173698 | size 192 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase20CountWorldConstraintEv | lib libSOA-3.7.0.so | 2026-10-08
int _ZN4Aska30ArticulatedDynamicsManagerBase20CountWorldConstraintEv(void)

{
  long *plVar1;
  byte bVar2;
  long *plVar3;
  long *plVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  long *plVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  
  bVar2 = *PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98;
  uVar5 = (ulong)bVar2;
  if (uVar5 == 0) {
    return 0;
  }
  if (bVar2 < 4) {
    lVar6 = 0;
  }
  else {
    lVar6 = uVar5 - (uVar5 & 3);
    if (lVar6 != 0) {
      iVar9 = 0;
      iVar10 = 0;
      plVar8 = (long *)(
                       PTR__ZN4Aska30ArticulatedDynamicsManagerBase22m_pWorldConstraintListE_02cbc740
                       + 0x10);
      iVar11 = 0;
      iVar12 = 0;
      lVar7 = lVar6;
      do {
        plVar1 = plVar8 + -2;
        plVar3 = plVar8 + -1;
        plVar4 = plVar8 + 1;
        lVar15 = *plVar8;
        lVar7 = lVar7 + -4;
        plVar8 = plVar8 + 4;
        lVar13 = -(ulong)(*plVar1 == 0);
        lVar14 = -(ulong)(*plVar3 == 0);
        lVar15 = -(ulong)(lVar15 == 0);
        lVar16 = -(ulong)(*plVar4 == 0);
        iVar9 = iVar9 - CONCAT13(~(byte)((ulong)lVar13 >> 0x18),
                                 CONCAT12(~(byte)((ulong)lVar13 >> 0x10),
                                          CONCAT11(~(byte)((ulong)lVar13 >> 8),~(byte)lVar13)));
        iVar10 = iVar10 - CONCAT13(~(byte)((ulong)lVar14 >> 0x18),
                                   CONCAT12(~(byte)((ulong)lVar14 >> 0x10),
                                            CONCAT11(~(byte)((ulong)lVar14 >> 8),~(byte)lVar14)));
        iVar11 = iVar11 - CONCAT13(~(byte)((ulong)lVar15 >> 0x18),
                                   CONCAT12(~(byte)((ulong)lVar15 >> 0x10),
                                            CONCAT11(~(byte)((ulong)lVar15 >> 8),~(byte)lVar15)));
        iVar12 = iVar12 - CONCAT13(~(byte)((ulong)lVar16 >> 0x18),
                                   CONCAT12(~(byte)((ulong)lVar16 >> 0x10),
                                            CONCAT11(~(byte)((ulong)lVar16 >> 8),~(byte)lVar16)));
      } while (lVar7 != 0);
      iVar9 = iVar11 + iVar9 + iVar12 + iVar10;
      if ((bVar2 & 3) == 0) {
        return iVar9;
      }
      goto code_r0x0217373c;
    }
  }
  iVar9 = 0;
code_r0x0217373c:
  do {
    lVar7 = lVar6 * 8;
    lVar6 = lVar6 + 1;
    if (*(long *)(PTR__ZN4Aska30ArticulatedDynamicsManagerBase22m_pWorldConstraintListE_02cbc740 +
                 lVar7) != 0) {
      iVar9 = iVar9 + 1;
    }
  } while (lVar6 < (long)uVar5);
  return iVar9;
}

// ==== Aska::ArticulatedDynamicsManagerBase::AddWorldConstraint(Aska::DynamicsPrimitive*, unsigned char)
// vaddr 0x2073758 | ghidra 0x2173758 | size 168 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase18AddWorldConstraintEPNS_17DynamicsPrimitiveEh | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase18AddWorldConstraintEPNS_17DynamicsPrimitiveEh
               (long *param_1,undefined1 param_2)

{
  byte bVar1;
  undefined *puVar2;
  undefined *puVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  
  puVar3 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase29m_ucDeleteWorldConstraintListE_02cc0bd8;
  puVar2 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase22m_pWorldConstraintListE_02cbc740;
  if (param_1 != (long *)0x0) {
    bVar1 = *PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98;
    if (bVar1 < 0x10) {
      if ((ulong)(byte)*PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0
          != 0) {
        lVar6 = 0;
        do {
          if (*(long **)(
                        PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_pWorldCollisionListE_02cc4750
                        + lVar6 * 8) == param_1) {
            return;
          }
          lVar6 = lVar6 + 1;
        } while (lVar6 < (long)(ulong)(byte)*
                                            PTR__ZN4Aska30ArticulatedDynamicsManagerBase18m_ucWorldCollisionE_02cc13e0
                );
      }
      uVar4 = 0;
      uVar5 = uVar4;
      if (bVar1 != 0) {
        do {
          if (*(long **)(
                        PTR__ZN4Aska30ArticulatedDynamicsManagerBase22m_pWorldConstraintListE_02cbc740
                        + uVar4 * 8) == param_1) {
            return;
          }
          uVar4 = uVar4 + 1;
          uVar5 = (ulong)bVar1;
        } while ((long)uVar4 < (long)(ulong)bVar1);
      }
      *PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98 = bVar1 + 1;
      puVar3[uVar5] = param_2;
      *(long **)(puVar2 + uVar5 * 8) = param_1;
                    /* WARNING: Could not recover jumptable at 0x021737f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_1 + 0x48))();
      return;
    }
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::DeleteWorldConstraint(Aska::DynamicsPrimitive*, bool)
// vaddr 0x2073800 | ghidra 0x2173800 | size 284 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase21DeleteWorldConstraintEPNS_17DynamicsPrimitiveEb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase21DeleteWorldConstraintEPNS_17DynamicsPrimitiveEb
               (long *param_1,ulong param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined *puVar3;
  uint uVar4;
  uint uVar5;
  
  puVar3 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98;
  puVar2 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase22m_pWorldConstraintListE_02cbc740;
  uVar4 = (uint)(byte)*PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98;
  if (*PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98 != 0) {
    if ((param_2 & 1) == 0) {
      uVar5 = 0;
      do {
        if (*(long **)(puVar2 + (long)(int)uVar5 * 8) == param_1) {
          if ((uVar4 & 0xff) == 1) goto code_r0x021738f8;
          uVar1 = ~uVar5 + (uVar4 & 0xff);
          memmove(puVar2 + (long)(int)uVar5 * 8,puVar2 + (long)(int)uVar5 * 8 + 8,
                          -(ulong)(uVar1 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar1 << 3);
          uVar4 = uVar4 - 1;
          uVar5 = uVar5 - 1;
          *puVar3 = (char)uVar4;
        }
        uVar5 = uVar5 + 1;
      } while ((int)uVar5 < (int)(uVar4 & 0xff));
    }
    else {
      uVar5 = 0;
      do {
        if (*(long **)(puVar2 + (long)(int)uVar5 * 8) == param_1) {
          (**(code **)(*param_1 + 0x40))(param_1);
          uVar4 = (byte)*puVar3 - 1;
          if (uVar4 == 0) {
code_r0x021738f8:
            puVar2 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase22m_pWorldConstraintListE_02cbc740;
            *puVar3 = 0;
            *(undefined8 *)puVar2 = 0;
            return;
          }
          uVar1 = ~uVar5 + (uint)(byte)*puVar3;
          memmove(puVar2 + (long)(int)uVar5 * 8,puVar2 + (long)(int)uVar5 * 8 + 8,
                          -(ulong)(uVar1 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar1 << 3);
          uVar5 = uVar5 - 1;
          *puVar3 = (char)uVar4;
        }
        uVar5 = uVar5 + 1;
      } while ((int)uVar5 < (int)(uVar4 & 0xff));
    }
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::DeleteAllWorldConstraint(unsigned char)
// vaddr 0x207391c | ghidra 0x217391c | size 308 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase24DeleteAllWorldConstraintEh | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase24DeleteAllWorldConstraintEh(char param_1)

{
  uint uVar1;
  uint uVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  uint uVar6;
  ulong uVar7;
  ulong uVar8;
  int iVar9;
  uint uVar10;
  long lVar11;
  
  puVar5 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98;
  puVar4 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase29m_ucDeleteWorldConstraintListE_02cc0bd8;
  puVar3 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase22m_pWorldConstraintListE_02cbc740;
  uVar7 = (ulong)(byte)*PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98;
  if (*PTR__ZN4Aska30ArticulatedDynamicsManagerBase19m_ucWorldConstraintE_02cc1c98 != 0) {
    lVar11 = 0;
    do {
      if ((*(long **)(puVar3 + lVar11 * 8) != (long *)0x0) && (puVar4[lVar11] == param_1)) {
        (**(code **)(**(long **)(puVar3 + lVar11 * 8) + 0x40))();
        uVar7 = (ulong)(byte)*puVar5;
        *(undefined8 *)(puVar3 + lVar11 * 8) = 0;
      }
      lVar11 = lVar11 + 1;
      uVar6 = (uint)uVar7;
    } while (lVar11 < (long)uVar7);
    if (uVar6 != 0) {
      iVar9 = 0;
      uVar8 = 0;
      uVar10 = 1;
      while (*(long *)(puVar3 + uVar8 * 8) != 0) {
        uVar8 = uVar8 + 1;
        uVar10 = uVar10 + 1;
        iVar9 = iVar9 + -1;
        if ((long)uVar7 <= (long)uVar8) goto joined_r0x02173a1c;
      }
      uVar1 = uVar10;
      if ((int)uVar10 <= (int)uVar6) {
        uVar1 = uVar6;
      }
      uVar1 = uVar1 + iVar9;
      if (uVar1 < 2) goto code_r0x02173a0c;
      uVar2 = uVar10;
      if ((int)uVar10 <= (int)uVar6) {
        uVar2 = uVar6;
      }
      if ((uVar1 & 0xfffffffe) == 0) goto code_r0x02173a0c;
      if ((int)uVar10 <= (int)uVar6) {
        uVar10 = uVar6;
      }
      uVar8 = (uVar2 + iVar9 & 0xfffffffe) + uVar8;
      uVar10 = uVar10 + iVar9 & 0xfffffffe;
      do {
        uVar10 = uVar10 - 2;
      } while (uVar10 != 0);
      if (uVar1 != (uVar1 & 0xfffffffe)) {
code_r0x02173a0c:
        do {
          uVar10 = (int)uVar8 + 1;
          uVar8 = (ulong)uVar10;
        } while ((int)uVar10 < (int)uVar6);
      }
joined_r0x02173a1c:
      while ((uVar6 != 0 && (*(long *)(puVar3 + (ulong)((uint)uVar7 & 0xff) * 8 + -8) == 0))) {
        uVar10 = (uint)uVar7 - 1;
        uVar7 = (ulong)uVar10;
        uVar6 = uVar10 & 0xff;
        *puVar5 = (char)uVar10;
      }
    }
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::MakeDynamicsPrimitiveListWithDependencyOfADM(Aska::DynamicsPrimitive**)
// vaddr 0x2073a50 | ghidra 0x2173a50 | size 292 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase44MakeDynamicsPrimitiveListWithDependencyOfADMEPPNS_17DynamicsPrimitiveE | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN4Aska30ArticulatedDynamicsManagerBase44MakeDynamicsPrimitiveListWithDependencyOfADMEPPNS_17DynamicsPrimitiveE
               (long param_1,long param_2)

{
  uint uVar1;
  uint uVar2;
  short sVar3;
  long lVar4;
  long lVar5;
  
  sVar3 = *(short *)(param_1 + 100);
  if (sVar3 < 1) {
    uVar1 = 0;
  }
  else {
    lVar4 = 0;
    uVar1 = 0;
    do {
      lVar5 = *(long *)(*(long *)(param_1 + 0x148) + lVar4 * 8);
      if ((lVar5 != 0) && (*(long *)(*(long *)(lVar5 + 0x50) + 0x10) != 0)) {
        *(long *)(param_2 + (ulong)uVar1 * 8) = lVar5;
        sVar3 = *(short *)(param_1 + 100);
        uVar1 = uVar1 + 1;
      }
      lVar4 = lVar4 + 1;
    } while (lVar4 < sVar3);
  }
  sVar3 = *(short *)(param_1 + 0x66);
  if (0 < sVar3) {
    lVar4 = 0;
    do {
      lVar5 = *(long *)(*(long *)(param_1 + 0x150) + lVar4 * 8);
      if ((lVar5 != 0) && (*(long *)(*(long *)(lVar5 + 0x50) + 0x10) != 0)) {
        *(long *)(param_2 + (ulong)uVar1 * 8) = lVar5;
        sVar3 = *(short *)(param_1 + 0x66);
        uVar1 = uVar1 + 1;
      }
      lVar4 = lVar4 + 1;
    } while (lVar4 < sVar3);
  }
  for (lVar4 = *(long *)(param_1 + 0x170); param_1 + 0x160 != lVar4; lVar4 = *(long *)(lVar4 + 0x10)
      ) {
    lVar5 = *(long *)(lVar4 + 0x38);
    uVar2 = uVar1;
    if ((lVar5 != 0) && (*(long *)(*(long *)(lVar5 + 0x50) + 0x10) != 0)) {
      uVar2 = uVar1 + 1;
      *(long *)(param_2 + (ulong)uVar1 * 8) = lVar5;
    }
    uVar1 = uVar2;
  }
  *(undefined1 *)(param_1 + 0x122) = 0;
  if (((*(byte *)(param_1 + 0x9a) >> 1 & 1) != 0) && (uVar1 != 0)) {
    lVar4 = 0;
    do {
      if (*(long *)(*(long *)(*(long *)(param_2 + lVar4 * 8) + 0x50) + 0x10) == param_1) {
        *(undefined1 *)(param_1 + 0x122) = 1;
        break;
      }
      lVar4 = lVar4 + 1;
    } while ((uint)lVar4 < uVar1);
  }
  *(bool *)(param_1 + 0x121) = uVar1 != 0;
  return uVar1;
}

// ==== Aska::ArticulatedDynamicsManagerBase::UpdateDynamicsPrimitiveListWithDependencyOfADM(unsigned int)
// vaddr 0x2073b74 | ghidra 0x2173b74 | size 536 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase46UpdateDynamicsPrimitiveListWithDependencyOfADMEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase46UpdateDynamicsPrimitiveListWithDependencyOfADMEj
               (long param_1,int param_2)

{
  long *plVar1;
  short sVar2;
  long lVar3;
  ulong uVar4;
  
  if (*(char *)(param_1 + 0x122) == '\0') {
    if (param_2 == 0) {
      sVar2 = *(short *)(param_1 + 100);
      if (0 < sVar2) {
        lVar3 = 0;
        do {
          plVar1 = *(long **)(*(long *)(param_1 + 0x148) + lVar3 * 8);
          if ((plVar1 != (long *)0x0) && (*(long *)(plVar1[10] + 0x10) != 0)) {
            (**(code **)(*plVar1 + 0x38))();
            sVar2 = *(short *)(param_1 + 100);
          }
          lVar3 = lVar3 + 1;
        } while (lVar3 < sVar2);
      }
      sVar2 = *(short *)(param_1 + 0x66);
      if (0 < sVar2) {
        lVar3 = 0;
        do {
          plVar1 = *(long **)(*(long *)(param_1 + 0x150) + lVar3 * 8);
          if ((plVar1 != (long *)0x0) && (*(long *)(plVar1[10] + 0x10) != 0)) {
            (**(code **)(*plVar1 + 0x38))();
            sVar2 = *(short *)(param_1 + 0x66);
          }
          lVar3 = lVar3 + 1;
        } while (lVar3 < sVar2);
      }
      for (lVar3 = *(long *)(param_1 + 0x170); param_1 + 0x160 != lVar3;
          lVar3 = *(long *)(lVar3 + 0x10)) {
        plVar1 = *(long **)(lVar3 + 0x38);
        if ((plVar1 != (long *)0x0) && (*(long *)(plVar1[10] + 0x10) != 0)) {
          (**(code **)(*plVar1 + 0x38))();
        }
      }
    }
  }
  else {
    if ((param_2 != 0) || (*(char *)(param_1 + 0xe2) != '\0')) {
      if ((*(char *)(param_1 + 0xe0) != '\0') &&
         ((*(char *)(param_1 + 0xd9) == '\0' && (0 < (long)*(short *)(param_1 + 0x60))))) {
        lVar3 = 0;
        uVar4 = (long)*(short *)(param_1 + 0x60) & 0xffffffff;
        do {
          Aska::ADMJoint::Flush()(*(long *)(param_1 + 0x70) + lVar3);
          uVar4 = uVar4 - 1;
          lVar3 = lVar3 + 0x1c0;
        } while (uVar4 != 0);
      }
      *(undefined2 *)(param_1 + 0xe0) = 0x101;
    }
    sVar2 = *(short *)(param_1 + 100);
    if (0 < sVar2) {
      lVar3 = 0;
      do {
        plVar1 = *(long **)(*(long *)(param_1 + 0x148) + lVar3 * 8);
        if ((plVar1 != (long *)0x0) && (*(long *)(plVar1[10] + 0x10) == param_1)) {
          (**(code **)(*plVar1 + 0x38))();
          sVar2 = *(short *)(param_1 + 100);
        }
        lVar3 = lVar3 + 1;
      } while (lVar3 < sVar2);
    }
    sVar2 = *(short *)(param_1 + 0x66);
    if (0 < sVar2) {
      lVar3 = 0;
      do {
        plVar1 = *(long **)(*(long *)(param_1 + 0x150) + lVar3 * 8);
        if ((plVar1 != (long *)0x0) && (*(long *)(plVar1[10] + 0x10) == param_1)) {
          (**(code **)(*plVar1 + 0x38))();
          sVar2 = *(short *)(param_1 + 0x66);
        }
        lVar3 = lVar3 + 1;
      } while (lVar3 < sVar2);
    }
    for (lVar3 = *(long *)(param_1 + 0x170); param_1 + 0x160 != lVar3;
        lVar3 = *(long *)(lVar3 + 0x10)) {
      plVar1 = *(long **)(lVar3 + 0x38);
      if ((plVar1 != (long *)0x0) && (*(long *)(plVar1[10] + 0x10) == param_1)) {
        (**(code **)(*plVar1 + 0x38))();
      }
    }
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::Flush()
// vaddr 0x2073d8c | ghidra 0x2173d8c | size 92 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase5FlushEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase5FlushEv(long param_1)

{
  long lVar1;
  ulong uVar2;
  
  if (((*(char *)(param_1 + 0xe0) != '\0') && (*(char *)(param_1 + 0xd9) == '\0')) &&
     (0 < (long)*(short *)(param_1 + 0x60))) {
    lVar1 = 0;
    uVar2 = (long)*(short *)(param_1 + 0x60) & 0xffffffff;
    do {
      Aska::ADMJoint::Flush()(*(long *)(param_1 + 0x70) + lVar1);
      uVar2 = uVar2 - 1;
      lVar1 = lVar1 + 0x1c0;
    } while (uVar2 != 0);
  }
  *(undefined2 *)(param_1 + 0xe0) = 0x101;
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::AllocConstraintList(unsigned char**, int)
// vaddr 0x2073de8 | ghidra 0x2173de8 | size 32 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase19AllocConstraintListEPPhi | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska30ArticulatedDynamicsManagerBase19AllocConstraintListEPPhi
          (long param_1,long *param_2,int param_3)

{
  long lVar1;
  
  lVar1 = *param_2;
  *(short *)(param_1 + 0x66) = (short)param_3;
  *(long *)(param_1 + 0x150) = lVar1;
  *param_2 = lVar1 + (param_3 << 3);
  return 1;
}

// ==== Aska::ArticulatedDynamicsManagerBase::InitParentOfRoots(unsigned char**, int)
// vaddr 0x2073e08 | ghidra 0x2173e08 | size 464 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase17InitParentOfRootsEPPhi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase17InitParentOfRootsEPPhi
               (long param_1,long *param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  short sVar3;
  long lVar4;
  undefined8 *puVar5;
  ulong uVar6;
  int iVar7;
  long lVar8;
  long lVar9;
  undefined8 uVar10;
  
  if (param_3 == 0) {
    *(undefined4 *)(param_1 + 0xb0) = 0;
    *(undefined8 *)(param_1 + 0xa0) = 0;
    *(undefined8 *)(param_1 + 0xa8) = 0;
  }
  else {
    *(int *)(param_1 + 0xb0) = param_3;
    *(long *)(param_1 + 0xa0) = *param_2;
    lVar4 = *param_2 + (long)param_3 * 0xa0;
    *param_2 = lVar4;
    *(long *)(param_1 + 0xa8) = lVar4;
    *param_2 = *param_2 + (long)*(int *)(param_1 + 0xb0) * 8;
    sVar3 = *(short *)(param_1 + 0x60);
    if (0 < (long)sVar3) {
      uVar6 = 0;
      iVar7 = 0;
      lVar4 = 0xffffffff;
      lVar8 = 0x1b0;
      do {
        if (*(char *)(*(long *)(param_1 + 0x70) + lVar8 + -0x17) == '\0') {
          lVar9 = *(long *)(param_1 + 0xa8) + (long)(int)lVar4 * 8;
          *(int *)(lVar9 + 4) = *(int *)(lVar9 + 4) + 1;
        }
        else {
          lVar9 = *(long *)(*(long *)(*(long *)(param_1 + 0x70) + lVar8) + 0xc0);
          if (lVar9 == 0) {
            puVar5 = (undefined8 *)0x0;
          }
          else {
            if ((*(byte *)(*(long **)(lVar9 + 0xe8) + 0x25) & 1) != 0) {
              (**(code **)(**(long **)(lVar9 + 0xe8) + 0xa8))();
            }
            uVar10 = *(undefined8 *)(lVar9 + 0x10);
            puVar5 = (undefined8 *)(*(long *)(param_1 + 0xa0) + (long)iVar7 * 0xa0);
            puVar5[1] = *(undefined8 *)(lVar9 + 0x18);
            *puVar5 = uVar10;
            uVar10 = *(undefined8 *)(lVar9 + 0x20);
            iVar7 = iVar7 + 1;
            puVar5[3] = *(undefined8 *)(lVar9 + 0x28);
            puVar5[2] = uVar10;
            uVar10 = *(undefined8 *)(lVar9 + 0x30);
            puVar5[5] = *(undefined8 *)(lVar9 + 0x38);
            puVar5[4] = uVar10;
            uVar10 = *(undefined8 *)(lVar9 + 0x40);
            puVar5[7] = *(undefined8 *)(lVar9 + 0x48);
            puVar5[6] = uVar10;
            *(undefined4 *)(puVar5 + 8) = *(undefined4 *)(lVar9 + 0x50);
            *(undefined4 *)((long)puVar5 + 0x44) = *(undefined4 *)(lVar9 + 0x54);
            *(undefined4 *)(puVar5 + 9) = *(undefined4 *)(lVar9 + 0x58);
            *(undefined4 *)((long)puVar5 + 0x4c) = *(undefined4 *)(lVar9 + 0x5c);
            *(undefined4 *)(puVar5 + 10) = *(undefined4 *)(lVar9 + 0x60);
            *(undefined4 *)((long)puVar5 + 0x54) = *(undefined4 *)(lVar9 + 100);
            *(undefined4 *)(puVar5 + 0xb) = *(undefined4 *)(lVar9 + 0x68);
            *(undefined4 *)((long)puVar5 + 0x5c) = *(undefined4 *)(lVar9 + 0x6c);
            *(undefined4 *)(puVar5 + 0xc) = *(undefined4 *)(lVar9 + 0x70);
            *(undefined4 *)((long)puVar5 + 100) = *(undefined4 *)(lVar9 + 0x74);
            *(undefined4 *)(puVar5 + 0xd) = *(undefined4 *)(lVar9 + 0x78);
            *(undefined4 *)((long)puVar5 + 0x6c) = *(undefined4 *)(lVar9 + 0x7c);
            *(undefined4 *)(puVar5 + 0xe) = *(undefined4 *)(lVar9 + 0x90);
            *(undefined4 *)((long)puVar5 + 0x74) = *(undefined4 *)(lVar9 + 0x94);
            *(undefined4 *)(puVar5 + 0xf) = *(undefined4 *)(lVar9 + 0x98);
            uVar2 = *(undefined4 *)(lVar9 + 0x9c);
            puVar5[0x10] = 0;
            *(undefined4 *)((long)puVar5 + 0x7c) = uVar2;
          }
          lVar4 = (long)(int)lVar4 + 1;
          puVar1 = (undefined4 *)(*(long *)(param_1 + 0xa8) + lVar4 * 8);
          *puVar1 = (int)uVar6;
          puVar1[1] = 1;
          *(undefined8 **)(*(long *)(param_1 + 0x70) + lVar8 + -0x80) = puVar5;
        }
        uVar6 = uVar6 + 1;
        lVar8 = lVar8 + 0x1c0;
      } while (((long)sVar3 & 0xffffffffU) != uVar6);
    }
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::InitJoints(unsigned char**)
// vaddr 0x2073fd8 | ghidra 0x2173fd8 | size 556 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase10InitJointsEPPh | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska30ArticulatedDynamicsManagerBase10InitJointsEPPh(long param_1,long *param_2)

{
  uint uVar1;
  short sVar2;
  long lVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  ulong uVar11;
  long lVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  
  sVar2 = *(short *)(param_1 + 0x60);
  if (sVar2 < 1) {
    lVar9 = *(long *)(param_1 + 0x70);
  }
  else {
    lVar9 = 0;
    lVar10 = (long)sVar2;
    do {
      lVar12 = *(long *)(param_1 + 0x70) + lVar9;
      Aska::ADMJoint::Init()(lVar12);
      lVar10 = lVar10 + -1;
      lVar9 = lVar9 + 0x1c0;
      *(undefined1 *)(lVar12 + 0x19e) = 0xff;
      *(undefined1 *)(lVar12 + 0x198) = 0;
    } while (lVar10 != 0);
    lVar9 = *(long *)(param_1 + 0x70);
    if (0 < sVar2) {
      lVar10 = 0;
      do {
        uVar1 = *(uint *)(lVar9 + lVar10 * 0x1c0 + 0x168);
        uVar11 = (ulong)uVar1;
        if (0 < (int)uVar1) {
          lVar9 = lVar9 + lVar10 * 0x1c0;
          lVar12 = 0;
          do {
            lVar8 = *(long *)(lVar9 + 0x160) + lVar12;
            lVar3 = *(long *)(lVar8 + 0x48);
            fVar13 = *(float *)(lVar9 + 0x10) - *(float *)(lVar3 + 0x10);
            fVar14 = *(float *)(lVar9 + 0x14) - *(float *)(lVar3 + 0x14);
            fVar15 = *(float *)(lVar9 + 0x18) - *(float *)(lVar3 + 0x18);
            fVar14 = fVar13 * fVar13 + fVar14 * fVar14 + fVar15 * fVar15;
            fVar13 = SQRT(fVar14);
            if (NAN(fVar13)) {
              fVar13 = (float)sqrtf(fVar14);
            }
            *(float *)(lVar8 + 0x28) = fVar13;
            if ((*(byte *)(lVar8 + 0x20) >> 4 & 1) != 0) {
              *(undefined1 *)(*(long *)(lVar8 + 0x48) + 0x198) = 1;
            }
            uVar11 = uVar11 - 1;
            lVar12 = lVar12 + 0x50;
          } while (uVar11 != 0);
          lVar9 = *(long *)(param_1 + 0x70);
        }
        lVar10 = lVar10 + 1;
      } while (lVar10 != sVar2);
    }
  }
  iVar6 = *(int *)(param_1 + 0xb0);
  if (0 < iVar6) {
    bVar4 = 0;
    do {
      iVar5 = *(int *)(*(long *)(param_1 + 0xa8) + (ulong)bVar4 * 8 + 4);
      if (0 < iVar5) {
        uVar11 = (ulong)(iVar5 - 1U) + 1;
        lVar10 = lVar9 + (ulong)*(uint *)(*(long *)(param_1 + 0xa8) + (ulong)bVar4 * 8) * 0x1c0;
        if (uVar11 < 2) {
          lVar12 = 0;
code_r0x02174190:
          iVar5 = iVar5 - (int)lVar12;
          pbVar7 = (byte *)(lVar10 + 0x19e);
          do {
            *pbVar7 = bVar4;
            iVar5 = iVar5 + -1;
            pbVar7 = pbVar7 + 0x1c0;
          } while (iVar5 != 0);
        }
        else {
          uVar1 = ~(iVar5 - 1U) & 1;
          lVar12 = uVar11 - uVar1;
          if (lVar12 == 0) goto code_r0x02174190;
          lVar3 = lVar10 + lVar12 * 0x1c0;
          lVar8 = lVar12;
          do {
            *(byte *)(lVar10 + 0x19e) = bVar4;
            *(byte *)(lVar10 + 0x35e) = bVar4;
            lVar8 = lVar8 + -2;
            lVar10 = lVar10 + 0x380;
          } while (lVar8 != 0);
          lVar10 = lVar3;
          if (uVar1 != 0) goto code_r0x02174190;
        }
        iVar6 = *(int *)(param_1 + 0xb0);
      }
      bVar4 = bVar4 + 1;
    } while ((int)(uint)bVar4 < iVar6);
  }
  *(short *)(param_1 + 0x98) = (short)iVar6;
  *(long *)(param_1 + 0x90) = *param_2;
  *param_2 = *param_2 + (long)(short)((short)iVar6 + 3U & 0xfffc);
  return 1;
}

// ==== Aska::ArticulatedDynamicsManagerBase::ReserveJointParamsForUpdate()
// vaddr 0x2074204 | ghidra 0x2174204 | size 144 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase27ReserveJointParamsForUpdateEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase27ReserveJointParamsForUpdateEv(long param_1)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  
  if (0 < (long)*(short *)(param_1 + 0x60)) {
    uVar2 = (long)*(short *)(param_1 + 0x60) & 0xffffffff;
    lVar3 = 0x1b0;
    do {
      lVar4 = *(long *)(param_1 + 0x70);
      lVar1 = *(long *)(lVar4 + lVar3);
      if (lVar1 != 0) {
        if ((*(byte *)(lVar1 + 0xf8) & 1) == 0) {
          Aska::HierarchicalObjectContainer::UpdateHierarchically()(lVar1);
        }
        lVar4 = lVar4 + lVar3;
        *(undefined4 *)(lVar1 + 0x60) = *(undefined4 *)(lVar4 + -0x140);
        *(undefined4 *)(lVar1 + 100) = *(undefined4 *)(lVar4 + -0x13c);
        *(undefined4 *)(lVar1 + 0x68) = *(undefined4 *)(lVar4 + -0x138);
        *(undefined4 *)(lVar1 + 0x6c) = *(undefined4 *)(lVar4 + -0x134);
      }
      uVar2 = uVar2 - 1;
      lVar3 = lVar3 + 0x1c0;
    } while (uVar2 != 0);
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::PrepareCalc(float)
// vaddr 0x2074294 | ghidra 0x2174294 | size 976 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase11PrepareCalcEf | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska30ArticulatedDynamicsManagerBase11PrepareCalcEf(float param_1,long param_2)

{
  float *pfVar1;
  long lVar2;
  long lVar3;
  short sVar4;
  undefined8 uVar5;
  bool bVar6;
  long *plVar7;
  undefined8 uVar8;
  float *pfVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  undefined4 *puVar14;
  long lVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  
  if (*(char *)(param_2 + 0xd8) != '\0') {
    lVar11 = *(long *)(param_2 + 0x70);
    sVar4 = *(short *)(param_2 + 0x60);
    lVar12 = (long)sVar4;
    lVar13 = lVar11 + lVar12 * 0x1c0;
    lVar15 = lVar11;
    if (((*(char *)(param_2 + 0xdc) != '\0') &&
        (fVar19 = *(float *)(param_2 + 0xf0), fVar19 < _UNK_029c49e4)) && (sVar4 != 0)) {
      puVar14 = (undefined4 *)(lVar11 + 0xf0);
      lVar15 = lVar12 * 0x1c0;
      do {
        fVar16 = (float)puVar14[0x21];
        lVar10 = *(long *)(puVar14 + 0x30);
        if (*(char *)((long)puVar14 + 0xa9) != '\0') {
          if ((*(byte *)(lVar10 + 0xf8) & 1) == 0) {
            Aska::HierarchicalObjectContainer::UpdateHierarchically()(lVar10);
          }
          *(undefined4 *)(lVar10 + 0x50) = *puVar14;
          *(undefined4 *)(lVar10 + 0x54) = puVar14[1];
          *(undefined4 *)(lVar10 + 0x58) = puVar14[2];
          *(undefined4 *)(lVar10 + 0x5c) = puVar14[3];
        }
        if ((fVar19 * fVar16 < 0.5) && (*(char *)((long)puVar14 + 0xaa) != '\0')) {
          if ((*(byte *)(lVar10 + 0xf8) & 1) == 0) {
            Aska::HierarchicalObjectContainer::UpdateHierarchically()(lVar10);
          }
          *(undefined4 *)(lVar10 + 0x60) = puVar14[4];
          *(undefined4 *)(lVar10 + 100) = puVar14[5];
          *(undefined4 *)(lVar10 + 0x68) = puVar14[6];
          *(undefined4 *)(lVar10 + 0x6c) = puVar14[7];
        }
        lVar15 = lVar15 + -0x1c0;
        puVar14 = puVar14 + 0x70;
      } while (lVar15 != 0);
      lVar15 = *(long *)(param_2 + 0x70);
    }
    if (lVar15 != lVar13) {
      do {
        Aska::ADMJoint::PrepareCalc()(lVar15);
        lVar15 = lVar15 + 0x1c0;
      } while (lVar13 != lVar15);
      if (*(long *)(param_2 + 0x70) != lVar13) {
        plVar7 = (long *)(*(long *)(param_2 + 0x70) + 0x130);
        do {
          lVar15 = *plVar7 + 0x60;
          if (*plVar7 == 0) {
            lVar15 = 0;
          }
          Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(plVar7 + -0x10,plVar7 + -8,plVar7 + -6,plVar7 + -2,plVar7 + -4,lVar15);
          plVar7 = plVar7 + 0x38;
        } while ((long)plVar7 + (lVar12 * -0x1c0 - lVar11) != 0x130);
      }
    }
    if ((*(char *)(param_2 + 0xd9) == '\0') &&
       (plVar7 = *(long **)(param_2 + 0x108), plVar7 != (long *)0x0)) {
      if ((*(byte *)(plVar7 + 0x25) & 1) != 0) {
        (**(code **)(*plVar7 + 0xa8))();
        plVar7 = *(long **)(param_2 + 0x108);
      }
      uVar8 = (**(code **)(*plVar7 + 0x98))();
      Aska::Vector::ApplyMatrixNoTransport(Aska::Vector*, Aska::Matrix const*) const(param_2 + 0x50,param_2 + 0x40,uVar8);
    }
    lVar15 = *(long *)(param_2 + 0x70);
    if (*(char *)(param_2 + 0xda) == '\0') {
      bVar6 = false;
      if (*(long *)(param_2 + 0x100) != 0) {
        bVar6 = (*(ushort *)(*(long *)(param_2 + 0x100) + 0x198) & 0x2101) != 0;
      }
      if ((!bVar6) && (*(float *)(param_2 + 0xf0) < _UNK_029c49e4)) {
        if (*(char *)(param_2 + 0xe1) == '\0') {
          return;
        }
        if (((*(char *)(param_2 + 0xd9) == '\0') && (*(char *)(param_2 + 0xdc) == '\0')) &&
           (*(char *)(param_2 + 0xe4) == '\0')) {
          return;
        }
        *(undefined1 *)(param_2 + 0xd9) = 0;
        *(undefined1 *)(param_2 + 0xe4) = 0;
        uVar5 = _UNK_027dbb38;
        uVar8 = _UNK_027dbb30;
        if (sVar4 == 0) {
          return;
        }
        lVar11 = 0;
        lVar13 = lVar15;
        do {
          lVar10 = lVar15 + lVar11;
          fVar19 = *(float *)(lVar10 + 0x10c);
          *(undefined4 *)(lVar10 + 0x10) = *(undefined4 *)(lVar10 + 0xbc);
          *(undefined4 *)(lVar10 + 0x14) = *(undefined4 *)(lVar10 + 0xcc);
          *(undefined4 *)(lVar10 + 0x18) = *(undefined4 *)(lVar10 + 0xdc);
          *(undefined4 *)(lVar10 + 0x1c) = 0x3f800000;
          if (fVar19 == *(float *)(lVar10 + 0x6c)) {
            fVar16 = *(float *)(lVar10 + 0x104);
            pfVar9 = (float *)(lVar10 + 100);
            pfVar1 = (float *)(lVar13 + 100);
            if (fVar16 != *pfVar9) goto code_r0x0217461c;
            lVar3 = lVar15 + lVar11;
            fVar17 = *(float *)(lVar3 + 0x108);
            if ((fVar17 != *(float *)(lVar3 + 0x68)) ||
               (fVar18 = *(float *)(lVar3 + 0x100), lVar2 = lVar13,
               fVar18 != *(float *)(lVar3 + 0x60))) goto code_r0x0217461c;
          }
          else {
            fVar16 = *(float *)(lVar10 + 0x104);
            pfVar1 = (float *)(lVar10 + 100);
code_r0x0217461c:
            pfVar9 = pfVar1;
            lVar2 = lVar15 + lVar11;
            fVar18 = *(float *)(lVar2 + 0x100);
            fVar17 = *(float *)(lVar2 + 0x108);
            *(float *)(lVar2 + 0x8c) = fVar19;
            *(float *)(lVar2 + 0x80) = fVar18;
            *(float *)(lVar2 + 0x84) = fVar16;
            *(float *)(lVar2 + 0x88) = fVar17;
          }
          lVar3 = lVar15 + lVar11;
          lVar11 = lVar11 + 0x1c0;
          lVar13 = lVar13 + 0x1c0;
          *(float *)(lVar3 + 0x60) = fVar18;
          *pfVar9 = fVar16;
          *(float *)(lVar2 + 0x68) = fVar17;
          *(float *)(lVar10 + 0x6c) = fVar19;
          *(undefined8 *)(lVar3 + 0x58) = uVar5;
          *(undefined8 *)(lVar3 + 0x50) = uVar8;
          if (lVar12 * 0x1c0 - lVar11 == 0) {
            return;
          }
        } while( true );
      }
    }
    if (sVar4 != 0) {
      lVar11 = 0;
      param_1 = 1.0 / param_1;
      do {
        lVar13 = lVar15 + lVar11;
        *(undefined8 *)(lVar13 + 0x68) = *(undefined8 *)(lVar13 + 0x108);
        *(undefined8 *)(lVar13 + 0x60) = *(undefined8 *)(lVar13 + 0x100);
        lVar11 = lVar11 + 0x1c0;
        *(float *)(lVar13 + 0x10) = *(float *)(lVar13 + 0xbc);
        *(float *)(lVar13 + 0x14) = *(float *)(lVar13 + 0xcc);
        *(float *)(lVar13 + 0x18) = *(float *)(lVar13 + 0xdc);
        *(undefined4 *)(lVar13 + 0x1c) = 0x3f800000;
        *(float *)(lVar13 + 0x50) =
             param_1 * (*(float *)(lVar13 + 0xbc) - *(float *)(lVar13 + 0x20));
        *(float *)(lVar13 + 0x54) =
             param_1 * (*(float *)(lVar13 + 0xcc) - *(float *)(lVar13 + 0x24));
        *(float *)(lVar13 + 0x58) =
             param_1 * (*(float *)(lVar13 + 0xdc) - *(float *)(lVar13 + 0x28));
      } while (lVar12 * 0x1c0 - lVar11 != 0);
    }
    if (*(char *)(param_2 + 0xd9) == '\0') {
      *(undefined1 *)(param_2 + 0xd9) = 1;
    }
  }
  *(undefined2 *)(param_2 + 0xe0) = 0;
  return;
}

// ==== Aska::ADMJoint::PrepareCalc()
// vaddr 0x2074664 | ghidra 0x2174664 | size 476 | symbol _ZN4Aska8ADMJoint11PrepareCalcEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8ADMJoint11PrepareCalcEv(long param_1)

{
  char cVar1;
  long lVar2;
  long lVar3;
  undefined8 *puVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  float fVar8;
  undefined8 uVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  
  lVar6 = *(long *)(param_1 + 0x1b0);
  if (lVar6 != 0) {
    if ((*(byte *)(*(long **)(lVar6 + 0xe8) + 0x25) & 1) != 0) {
      (**(code **)(**(long **)(lVar6 + 0xe8) + 0xa8))();
    }
    if (((*(char *)(param_1 + 0x199) == '\0') || (lVar2 = *(long *)(lVar6 + 0xc0), lVar2 == 0)) ||
       (puVar4 = *(undefined8 **)(param_1 + 0x130), puVar4 == (undefined8 *)0x0)) {
      cVar1 = *(char *)(param_1 + 0x1bc);
    }
    else {
      uVar9 = *(undefined8 *)(lVar2 + 0x10);
      puVar4[1] = *(undefined8 *)(lVar2 + 0x18);
      *puVar4 = uVar9;
      uVar9 = *(undefined8 *)(lVar2 + 0x20);
      puVar4[3] = *(undefined8 *)(lVar2 + 0x28);
      puVar4[2] = uVar9;
      uVar9 = *(undefined8 *)(lVar2 + 0x30);
      puVar4[5] = *(undefined8 *)(lVar2 + 0x38);
      puVar4[4] = uVar9;
      uVar9 = *(undefined8 *)(lVar2 + 0x40);
      puVar4[7] = *(undefined8 *)(lVar2 + 0x48);
      puVar4[6] = uVar9;
      cVar1 = *(char *)(param_1 + 0x1bc);
    }
    if (cVar1 == '\0') {
      *(undefined4 *)(param_1 + 0xf0) = *(undefined4 *)(lVar6 + 0x50);
      *(undefined4 *)(param_1 + 0xf4) = *(undefined4 *)(lVar6 + 0x54);
      *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(lVar6 + 0x58);
      *(undefined4 *)(param_1 + 0xfc) = *(undefined4 *)(lVar6 + 0x5c);
    }
    else {
      Aska::Vector::ApplyQuaternion(Aska::Vector*, Aska::Quaternion const*) const(param_1 + 0xa0,&fStack_50,lVar6 + 0x60);
      fVar8 = *(float *)(lVar6 + 0x80);
      fVar10 = *(float *)(lVar6 + 0x84);
      fVar11 = *(float *)(lVar6 + 0x50);
      fVar12 = *(float *)(lVar6 + 0x54);
      fVar13 = *(float *)(lVar6 + 0x88);
      fVar14 = *(float *)(lVar6 + 0x58);
      *(undefined4 *)(param_1 + 0xfc) = 0x3f800000;
      *(float *)(param_1 + 0xf0) = fVar8 + fVar11 + fStack_50;
      *(float *)(param_1 + 0xf4) = fVar10 + fVar12 + fStack_4c;
      *(float *)(param_1 + 0xf8) = fVar13 + fVar14 + fStack_48;
    }
    uVar5 = (ulong)*(uint *)(param_1 + 0x168);
    *(undefined4 *)(param_1 + 0x100) = *(undefined4 *)(lVar6 + 0x60);
    *(undefined4 *)(param_1 + 0x104) = *(undefined4 *)(lVar6 + 100);
    *(undefined4 *)(param_1 + 0x108) = *(undefined4 *)(lVar6 + 0x68);
    *(undefined4 *)(param_1 + 0x10c) = *(undefined4 *)(lVar6 + 0x6c);
    *(undefined4 *)(param_1 + 0x110) = *(undefined4 *)(lVar6 + 0x70);
    *(undefined4 *)(param_1 + 0x114) = *(undefined4 *)(lVar6 + 0x74);
    *(undefined4 *)(param_1 + 0x118) = *(undefined4 *)(lVar6 + 0x78);
    *(undefined4 *)(param_1 + 0x11c) = *(undefined4 *)(lVar6 + 0x7c);
    if (0 < (int)*(uint *)(param_1 + 0x168)) {
      lVar6 = 0;
      do {
        lVar7 = *(long *)(param_1 + 0x160);
        lVar2 = lVar7 + lVar6;
        if ((*(byte *)(lVar2 + 0x20) >> 4 & 1) != 0) {
          lVar3 = *(long *)(lVar2 + 0x48);
          fVar8 = *(float *)(param_1 + 0x10) - *(float *)(lVar3 + 0x10);
          fVar10 = *(float *)(param_1 + 0x14) - *(float *)(lVar3 + 0x14);
          fVar11 = *(float *)(param_1 + 0x18) - *(float *)(lVar3 + 0x18);
          fVar10 = fVar8 * fVar8 + fVar10 * fVar10 + fVar11 * fVar11;
          fVar8 = SQRT(fVar10);
          if (NAN(fVar8)) {
            fVar8 = (float)sqrtf(fVar10);
          }
          *(float *)(lVar7 + lVar6 + 0x28) = fVar8;
          *(undefined1 *)(*(long *)(lVar2 + 0x48) + 0x198) = 1;
        }
        uVar5 = uVar5 - 1;
        lVar6 = lVar6 + 0x50;
      } while (uVar5 != 0);
    }
    return;
  }
  return;
}

// ==== Aska::ADMJoint::Flush()
// vaddr 0x2074840 | ghidra 0x2174840 | size 336 | symbol _ZN4Aska8ADMJoint5FlushEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8ADMJoint5FlushEv(long param_1)

{
  undefined4 uVar1;
  char cVar2;
  byte bVar3;
  long lVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  
  lVar4 = *(long *)(param_1 + 0x1b0);
  if (*(char *)(param_1 + 0x1bc) == '\0') {
    if ((*(byte *)(lVar4 + 0xf8) & 1) == 0) {
      Aska::HierarchicalObjectContainer::UpdateHierarchically()(lVar4);
    }
    *(undefined4 *)(lVar4 + 0x50) = *(undefined4 *)(param_1 + 0xf0);
    *(undefined4 *)(lVar4 + 0x54) = *(undefined4 *)(param_1 + 0xf4);
    *(undefined4 *)(lVar4 + 0x58) = *(undefined4 *)(param_1 + 0xf8);
    *(undefined4 *)(lVar4 + 0x5c) = *(undefined4 *)(param_1 + 0xfc);
    cVar2 = *(char *)(param_1 + 0x19a);
  }
  else {
    Aska::Vector::ApplyQuaternion(Aska::Vector*, Aska::Quaternion const*) const(param_1 + 0xa0,&fStack_50,param_1 + 0x100);
    fVar5 = *(float *)(param_1 + 0xf0);
    fVar6 = *(float *)(param_1 + 0xf4);
    fVar9 = *(float *)(param_1 + 0xf8);
    fVar7 = *(float *)(lVar4 + 0x80);
    fVar8 = *(float *)(lVar4 + 0x84);
    fVar10 = *(float *)(lVar4 + 0x88);
    uVar1 = *(undefined4 *)(param_1 + 0xfc);
    if ((*(byte *)(lVar4 + 0xf8) & 1) == 0) {
      Aska::HierarchicalObjectContainer::UpdateHierarchically()(lVar4);
    }
    *(float *)(lVar4 + 0x50) = (fVar5 - fStack_50) - fVar7;
    *(float *)(lVar4 + 0x54) = (fVar6 - fStack_4c) - fVar8;
    *(float *)(lVar4 + 0x58) = (fVar9 - fStack_48) - fVar10;
    *(undefined4 *)(lVar4 + 0x5c) = uVar1;
    cVar2 = *(char *)(param_1 + 0x19a);
  }
  if (cVar2 == '\0') {
    bVar3 = *(byte *)(lVar4 + 0xf8);
  }
  else {
    if ((*(byte *)(lVar4 + 0xf8) & 1) == 0) {
      Aska::HierarchicalObjectContainer::UpdateHierarchically()(lVar4);
    }
    *(undefined4 *)(lVar4 + 0x60) = *(undefined4 *)(param_1 + 0x100);
    *(undefined4 *)(lVar4 + 100) = *(undefined4 *)(param_1 + 0x104);
    *(undefined4 *)(lVar4 + 0x68) = *(undefined4 *)(param_1 + 0x108);
    *(undefined4 *)(lVar4 + 0x6c) = *(undefined4 *)(param_1 + 0x10c);
    bVar3 = *(byte *)(lVar4 + 0xf8);
  }
  if ((bVar3 & 1) == 0) {
    Aska::HierarchicalObjectContainer::UpdateHierarchically()(lVar4);
  }
  *(undefined4 *)(lVar4 + 0x70) = *(undefined4 *)(param_1 + 0x110);
  *(undefined4 *)(lVar4 + 0x74) = *(undefined4 *)(param_1 + 0x114);
  *(undefined4 *)(lVar4 + 0x78) = *(undefined4 *)(param_1 + 0x118);
  *(undefined4 *)(lVar4 + 0x7c) = *(undefined4 *)(param_1 + 0x11c);
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::GetDt() const
// vaddr 0x2074990 | ghidra 0x2174990 | size 128 | symbol _ZNK4Aska30ArticulatedDynamicsManagerBase5GetDtEv | lib libSOA-3.7.0.so | 2026-10-08
undefined1  [16] _ZNK4Aska30ArticulatedDynamicsManagerBase5GetDtEv(long param_1)

{
  uint uVar1;
  undefined4 extraout_s0;
  undefined4 extraout_var;
  undefined8 extraout_var_00;
  undefined1 auVar2 [16];
  
  if (*(int *)(param_1 + 0xe8) != 1) {
    if (*(char *)(param_1 + 0x120) != '\0') {
      return ZEXT416(*(uint *)(param_1 + 0xf8));
    }
    if (*(char *)(param_1 + 0xe3) == '\0') {
                    /* WARNING: Could not recover jumptable at 0x02174a0c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)**(undefined8 **)PTR__ZN4Aska14DynamicsCommon9m_pIVSyncE_02cbb790)
                (*(undefined8 **)PTR__ZN4Aska14DynamicsCommon9m_pIVSyncE_02cbb790,0);
      auVar2._4_4_ = extraout_var;
      auVar2._0_4_ = extraout_s0;
      auVar2._8_8_ = extraout_var_00;
      return auVar2;
    }
    *(undefined1 *)(param_1 + 0xe3) = 0;
  }
  uVar1 = (**(code **)(**(long **)PTR__ZN4Aska14DynamicsCommon9m_pIVSyncE_02cbb790 + 0x10))();
  return ZEXT416((uint)(1.0 / (float)uVar1));
}

// ==== Aska::ArticulatedDynamicsManagerBase::CheckGroupLink(Aska::ADMJoint*, int)
// vaddr 0x2074a10 | ghidra 0x2174a10 | size 180 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase14CheckGroupLinkEPNS_8ADMJointEi | lib libSOA-3.7.0.so | 2026-10-08
undefined4
_ZN4Aska30ArticulatedDynamicsManagerBase14CheckGroupLinkEPNS_8ADMJointEi
          (undefined8 param_1,long param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  
  iVar1 = *(int *)(param_2 + 0x168);
  if (iVar1 < 1) {
    uVar2 = 0;
  }
  else {
    lVar4 = 0;
    uVar2 = 0;
    lVar5 = 0x48;
    do {
      lVar3 = *(long *)(param_2 + 0x160);
      if ((*(char *)(param_2 + 0x19e) != -1) && (*(char *)(*(long *)(lVar3 + lVar5) + 0x19e) != -1))
      {
        return uVar2;
      }
      if (*(long *)(*(long *)(lVar3 + lVar5) + 0x130) == param_2 + 0xb0) {
        *(char *)(param_2 + 0x19e) = (char)param_3;
        *(char *)(*(long *)(lVar3 + lVar5) + 0x19e) = (char)param_3;
        _ZN4Aska30ArticulatedDynamicsManagerBase14CheckGroupLinkEPNS_8ADMJointEi
                  (param_1,*(undefined8 *)(lVar3 + lVar5),param_3);
        uVar2 = 1;
      }
      lVar4 = lVar4 + 1;
      lVar5 = lVar5 + 0x50;
    } while (lVar4 < iVar1);
  }
  return uVar2;
}

// ==== Aska::ArticulatedDynamicsManagerBase::CheckMoveLarge(float)
// vaddr 0x2074ac4 | ghidra 0x2174ac4 | size 184 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase14CheckMoveLargeEf | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska30ArticulatedDynamicsManagerBase14CheckMoveLargeEf(float param_1,long param_2)

{
  long lVar1;
  int iVar2;
  long lVar3;
  float *pfVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  iVar2 = 0;
  if ((long)*(short *)(param_2 + 0x62) == 0) {
    fVar7 = 0.0;
  }
  else {
    lVar3 = (long)*(short *)(param_2 + 0x62) * 0x50;
    fVar7 = 0.0;
    pfVar4 = (float *)(*(long *)(param_2 + 0x78) + 0x28);
    do {
      if ((*(byte *)(pfVar4 + -2) >> 4 & 1) != 0) {
        lVar1 = *(long *)(pfVar4 + 8);
        fVar8 = *pfVar4;
        fVar6 = *(float *)(lVar1 + 0x50) * *(float *)(lVar1 + 0x50) +
                *(float *)(lVar1 + 0x54) * *(float *)(lVar1 + 0x54) +
                *(float *)(lVar1 + 0x58) * *(float *)(lVar1 + 0x58);
        fVar5 = SQRT(fVar6);
        if (NAN(fVar5)) {
          fVar5 = (float)sqrtf(fVar6);
        }
        fVar7 = fVar7 + fVar8 * fVar5;
        iVar2 = iVar2 + 1;
      }
      lVar3 = lVar3 + -0x50;
      pfVar4 = pfVar4 + 0x14;
    } while (lVar3 != 0);
  }
  return param_1 <= fVar7 / (float)iVar2;
}

// ==== Aska::ArticulatedDynamicsManagerBase::Run()
// vaddr 0x2074b7c | ghidra 0x2174b7c | size 956 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase3RunEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska30ArticulatedDynamicsManagerBase3RunEv(long *param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  long *plVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  undefined4 uVar8;
  
  if ((char)param_1[0x1b] == '\0') {
    return;
  }
  if (*(char *)((long)param_1 + 0xdb) != '\0') {
    return;
  }
  if ((int)param_1[0x1d] != 1) {
    if ((char)param_1[0x24] != '\0') {
      uVar7 = (ulong)*(uint *)(param_1 + 0x1f);
      goto code_r0x02174be0;
    }
    if (*(char *)((long)param_1 + 0xe3) == '\0') {
      uVar7 = (**(code **)**(undefined8 **)PTR__ZN4Aska14DynamicsCommon9m_pIVSyncE_02cbb790)
                        (*(undefined8 **)PTR__ZN4Aska14DynamicsCommon9m_pIVSyncE_02cbb790,0);
      goto code_r0x02174be0;
    }
    *(undefined1 *)((long)param_1 + 0xe3) = 0;
  }
  uVar2 = (**(code **)(**(long **)PTR__ZN4Aska14DynamicsCommon9m_pIVSyncE_02cbb790 + 0x10))();
  uVar7 = (ulong)(uint)(1.0 / (float)uVar2);
code_r0x02174be0:
  if ((int)param_1[0x1d] == 1) {
    lVar5 = param_1[0x23];
    Aska::ArticulatedDynamicsManagerBase::PrepareCalc(float)(uVar7,param_1);
    if ((int)lVar5 == 1) {
      iVar3 = (int)param_1[0x23];
      if (*(char *)((long)param_1 + 0xe1) != '\0') {
        iVar1 = *(int *)((long)param_1 + 0x114);
        uVar8 = *(undefined4 *)((long)param_1 + 0x11c);
        *(undefined1 *)((long)param_1 + 0xe2) = 1;
        if ((0 < (long)*(short *)((long)param_1 + 100)) &&
           (plVar4 = (long *)param_1[0x29], plVar4 != (long *)0x0)) {
          uVar6 = (long)*(short *)((long)param_1 + 100) & 0xffffffff;
          do {
            if ((long *)*plVar4 != (long *)0x0) {
              (**(code **)(*(long *)*plVar4 + 0x78))();
            }
            uVar6 = uVar6 - 1;
            plVar4 = plVar4 + 1;
          } while (uVar6 != 0);
        }
        if ((0 < (long)*(short *)((long)param_1 + 0x66)) &&
           (plVar4 = (long *)param_1[0x2a], plVar4 != (long *)0x0)) {
          uVar6 = (long)*(short *)((long)param_1 + 0x66) & 0xffffffff;
          do {
            if ((long *)*plVar4 != (long *)0x0) {
              (**(code **)(*(long *)*plVar4 + 0x78))();
            }
            uVar6 = uVar6 - 1;
            plVar4 = plVar4 + 1;
          } while (uVar6 != 0);
        }
        (**(code **)(*param_1 + 0x70))(uVar7,uVar8,param_1,iVar3 * iVar1);
        iVar3 = (int)param_1[0x23];
        *(undefined2 *)((long)param_1 + 0xe2) = 0x100;
      }
      *(int *)(param_1 + 0x23) = iVar3 + -1;
      *(undefined4 *)(param_1 + 0x1d) = 0;
      if ((((char)param_1[0x1c] != '\0') && (*(char *)((long)param_1 + 0xd9) == '\0')) &&
         (0 < (long)(short)param_1[0xc])) {
        lVar5 = 0;
        uVar7 = (long)(short)param_1[0xc] & 0xffffffff;
        do {
          Aska::ADMJoint::Flush()(param_1[0xe] + lVar5);
          uVar7 = uVar7 - 1;
          lVar5 = lVar5 + 0x1c0;
        } while (uVar7 != 0);
      }
    }
    else {
      if (*(char *)((long)param_1 + 0xe1) != '\0') {
        *(undefined1 *)((long)param_1 + 0xe2) = 1;
        if ((0 < (long)*(short *)((long)param_1 + 100)) &&
           (plVar4 = (long *)param_1[0x29], plVar4 != (long *)0x0)) {
          uVar6 = (long)*(short *)((long)param_1 + 100) & 0xffffffff;
          do {
            if ((long *)*plVar4 != (long *)0x0) {
              (**(code **)(*(long *)*plVar4 + 0x78))();
            }
            uVar6 = uVar6 - 1;
            plVar4 = plVar4 + 1;
          } while (uVar6 != 0);
        }
        if ((0 < (long)*(short *)((long)param_1 + 0x66)) &&
           (plVar4 = (long *)param_1[0x2a], plVar4 != (long *)0x0)) {
          uVar6 = (long)*(short *)((long)param_1 + 0x66) & 0xffffffff;
          do {
            if ((long *)*plVar4 != (long *)0x0) {
              (**(code **)(*(long *)*plVar4 + 0x78))();
            }
            uVar6 = uVar6 - 1;
            plVar4 = plVar4 + 1;
          } while (uVar6 != 0);
        }
        uVar8 = *(undefined4 *)((long)param_1 + 0xec);
        (**(code **)(*param_1 + 0x70))(uVar7,0,param_1,*(undefined4 *)((long)param_1 + 0x114));
        *(undefined4 *)((long)param_1 + 0xec) = uVar8;
        *(undefined1 *)((long)param_1 + 0xe2) = 0;
      }
      lVar5 = param_1[0x23];
      *(int *)(param_1 + 0x23) = (int)lVar5 + -1;
      if ((int)lVar5 < 2) {
        *(undefined4 *)(param_1 + 0x1d) = 0;
        *(char *)(param_1 + 0x1c) = *(char *)((long)param_1 + 0xe1);
        if (((*(char *)((long)param_1 + 0xe1) != '\0') && (*(char *)((long)param_1 + 0xd9) == '\0'))
           && (0 < (long)(short)param_1[0xc])) {
          lVar5 = 0;
          uVar7 = (long)(short)param_1[0xc] & 0xffffffff;
          do {
            Aska::ADMJoint::Flush()(param_1[0xe] + lVar5);
            uVar7 = uVar7 - 1;
            lVar5 = lVar5 + 0x1c0;
          } while (uVar7 != 0);
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x1c) = 0;
      }
    }
    *(undefined1 *)((long)param_1 + 0xe1) = 1;
    *(undefined1 *)(param_1 + 0x1c) = 1;
    *(undefined1 *)((long)param_1 + 0xe3) = 1;
  }
  else {
    if (_UNK_027e519c <= (float)uVar7) {
      Aska::ArticulatedDynamicsManagerBase::PrepareCalc(float)(uVar7,param_1);
      (**(code **)(*param_1 + 0x70))(uVar7,0,param_1,1);
      if ((((char)param_1[0x1c] != '\0') && (*(char *)((long)param_1 + 0xd9) == '\0')) &&
         (0 < (long)(short)param_1[0xc])) {
        lVar5 = 0;
        uVar7 = (long)(short)param_1[0xc] & 0xffffffff;
        do {
          Aska::ADMJoint::Flush()(param_1[0xe] + lVar5);
          uVar7 = uVar7 - 1;
          lVar5 = lVar5 + 0x1c0;
        } while (uVar7 != 0);
      }
    }
    else if ((((char)param_1[0x1c] != '\0') && (*(char *)((long)param_1 + 0xd9) == '\0')) &&
            (0 < (long)(short)param_1[0xc])) {
      lVar5 = 0;
      uVar7 = (long)(short)param_1[0xc] & 0xffffffff;
      do {
        Aska::ADMJoint::Flush()(param_1[0xe] + lVar5);
        uVar7 = uVar7 - 1;
        lVar5 = lVar5 + 0x1c0;
      } while (uVar7 != 0);
    }
    *(undefined2 *)(param_1 + 0x1c) = 0x101;
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::Converge(int, float, int)
// vaddr 0x2074f38 | ghidra 0x2174f38 | size 396 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase8ConvergeEifi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase8ConvergeEifi
               (undefined8 param_1,long *param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  long *plVar5;
  ulong uVar6;
  
  *(undefined2 *)(param_2 + 0x1c) = 0x101;
  if (param_4 < 1) {
    uVar3 = (**(code **)(**(long **)PTR__ZN4Aska14DynamicsCommon9m_pIVSyncE_02cbb790 + 0x10))();
    *(undefined1 *)((long)param_2 + 0xe4) = 1;
    Aska::ArticulatedDynamicsManagerBase::PrepareCalc(float)(1.0 / (float)uVar3,param_2);
    if (*(char *)((long)param_2 + 0xe1) != '\0') {
      *(undefined1 *)((long)param_2 + 0xe2) = 1;
      if ((0 < (long)*(short *)((long)param_2 + 100)) &&
         (plVar5 = (long *)param_2[0x29], plVar5 != (long *)0x0)) {
        uVar6 = (long)*(short *)((long)param_2 + 100) & 0xffffffff;
        do {
          if ((long *)*plVar5 != (long *)0x0) {
            (**(code **)(*(long *)*plVar5 + 0x78))();
          }
          uVar6 = uVar6 - 1;
          plVar5 = plVar5 + 1;
        } while (uVar6 != 0);
      }
      if ((0 < (long)*(short *)((long)param_2 + 0x66)) &&
         (plVar5 = (long *)param_2[0x2a], plVar5 != (long *)0x0)) {
        uVar6 = (long)*(short *)((long)param_2 + 0x66) & 0xffffffff;
        do {
          if ((long *)*plVar5 != (long *)0x0) {
            (**(code **)(*(long *)*plVar5 + 0x78))();
          }
          uVar6 = uVar6 - 1;
          plVar5 = plVar5 + 1;
        } while (uVar6 != 0);
      }
      (**(code **)(*param_2 + 0x70))(1.0 / (float)uVar3,param_1,param_2,param_3);
      *(undefined2 *)((long)param_2 + 0xe2) = 0x100;
    }
    if ((((char)param_2[0x1c] != '\0') && (*(char *)((long)param_2 + 0xd9) == '\0')) &&
       (0 < (long)(short)param_2[0xc])) {
      lVar4 = 0;
      uVar6 = (long)(short)param_2[0xc] & 0xffffffff;
      do {
        Aska::ADMJoint::Flush()(param_2[0xe] + lVar4);
        uVar6 = uVar6 - 1;
        lVar4 = lVar4 + 0x1c0;
      } while (uVar6 != 0);
    }
    *(undefined2 *)(param_2 + 0x1c) = 0x101;
  }
  else {
    iVar1 = param_4;
    if (param_4 <= param_3) {
      iVar1 = param_3;
    }
    iVar2 = 0;
    if (param_4 != 0) {
      iVar2 = iVar1 / param_4;
    }
    *(int *)(param_2 + 0x23) = param_4;
    *(int *)((long)param_2 + 0x11c) = (int)param_1;
    *(undefined4 *)(param_2 + 0x1d) = 1;
    *(int *)((long)param_2 + 0x114) = iVar2;
    *(float *)(param_2 + 0x22) = (float)iVar2;
    *(undefined1 *)((long)param_2 + 0xe4) = 1;
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::RemoveExtraPrimitive(Aska::DynamicsPrimitive*)
// vaddr 0x20750c4 | ghidra 0x21750c4 | size 220 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase20RemoveExtraPrimitiveEPNS_17DynamicsPrimitiveE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska30ArticulatedDynamicsManagerBase20RemoveExtraPrimitiveEPNS_17DynamicsPrimitiveE
          (long param_1,long *param_2)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0x170);
  if (param_1 + 0x160 != lVar3) {
    do {
      if (*(long **)(lVar3 + 0x38) == param_2) {
        if (param_2 != (long *)0x0) {
          Aska::DynamicsManager::Delete(Aska::DynamicsHandler*)(*(undefined8 *)PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38,lVar3);
          plVar2 = *(long **)(lVar3 + 0x38);
          if (plVar2 != (long *)0x0) {
            iVar1 = (int)plVar2[5] + -1;
            *(int *)(plVar2 + 5) = iVar1;
            if (iVar1 == 0) {
              (**(code **)(*plVar2 + 8))();
            }
            *(undefined8 *)(lVar3 + 0x38) = 0;
          }
          (**(code **)(*(long *)(param_1 + 0x158) + 0x28))((long *)(param_1 + 0x158),lVar3);
          Aska::TPoolFast<Aska::DynamicsPrimitiveElement, true>::Sink(Aska::DynamicsPrimitiveElement*)(PTR__ZN4Aska6Global27m_dynamicsPrimitiveListPoolE_02cb76c8,lVar3);
          iVar1 = (int)param_2[5] + -1;
          *(int *)(param_2 + 5) = iVar1;
          if (iVar1 == 0) {
            (**(code **)(*param_2 + 8))(param_2);
            return 1;
          }
        }
        return 1;
      }
      lVar3 = *(long *)(lVar3 + 0x10);
    } while (param_1 + 0x160 != lVar3);
  }
  return 0;
}

// ==== Aska::ArticulatedDynamicsManagerBase::RemoveExtraCollision(Aska::DynamicsPrimitive*)
// vaddr 0x20751a0 | ghidra 0x21751a0 | size 220 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase20RemoveExtraCollisionEPNS_17DynamicsPrimitiveE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska30ArticulatedDynamicsManagerBase20RemoveExtraCollisionEPNS_17DynamicsPrimitiveE
          (long param_1,long *param_2)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  
  lVar3 = *(long *)(param_1 + 0x170);
  if (param_1 + 0x160 != lVar3) {
    do {
      if (*(long **)(lVar3 + 0x38) == param_2) {
        if (param_2 != (long *)0x0) {
          Aska::DynamicsManager::Delete(Aska::DynamicsHandler*)(*(undefined8 *)PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38,lVar3);
          plVar2 = *(long **)(lVar3 + 0x38);
          if (plVar2 != (long *)0x0) {
            iVar1 = (int)plVar2[5] + -1;
            *(int *)(plVar2 + 5) = iVar1;
            if (iVar1 == 0) {
              (**(code **)(*plVar2 + 8))();
            }
            *(undefined8 *)(lVar3 + 0x38) = 0;
          }
          (**(code **)(*(long *)(param_1 + 0x158) + 0x28))((long *)(param_1 + 0x158),lVar3);
          Aska::TPoolFast<Aska::DynamicsPrimitiveElement, true>::Sink(Aska::DynamicsPrimitiveElement*)(PTR__ZN4Aska6Global27m_dynamicsPrimitiveListPoolE_02cb76c8,lVar3);
          iVar1 = (int)param_2[5] + -1;
          *(int *)(param_2 + 5) = iVar1;
          if (iVar1 == 0) {
            (**(code **)(*param_2 + 8))(param_2);
            return 1;
          }
        }
        return 1;
      }
      lVar3 = *(long *)(lVar3 + 0x10);
    } while (param_1 + 0x160 != lVar3);
  }
  return 0;
}

// ==== Aska::ArticulatedDynamicsManagerBase::RemoveAllExtraPrimitive()
// vaddr 0x207527c | ghidra 0x217527c | size 216 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase23RemoveAllExtraPrimitiveEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska30ArticulatedDynamicsManagerBase23RemoveAllExtraPrimitiveEv(long param_1)

{
  int iVar1;
  undefined *puVar2;
  undefined *puVar3;
  long *plVar4;
  long lVar5;
  long *plVar6;
  long lVar7;
  
  puVar3 = PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38;
  puVar2 = PTR__ZN4Aska6Global27m_dynamicsPrimitiveListPoolE_02cb76c8;
  if (param_1 + 0x160 != *(long *)(param_1 + 0x170)) {
    lVar5 = *(long *)(param_1 + 0x170);
    do {
      plVar6 = *(long **)(lVar5 + 0x38);
      lVar7 = *(long *)(lVar5 + 0x10);
      if (plVar6 != (long *)0x0) {
        Aska::DynamicsManager::Delete(Aska::DynamicsHandler*)(*(undefined8 *)puVar3,lVar5);
        plVar4 = *(long **)(lVar5 + 0x38);
        if (plVar4 != (long *)0x0) {
          iVar1 = (int)plVar4[5] + -1;
          *(int *)(plVar4 + 5) = iVar1;
          if (iVar1 == 0) {
            (**(code **)(*plVar4 + 8))();
          }
          *(undefined8 *)(lVar5 + 0x38) = 0;
        }
        (**(code **)(*(long *)(param_1 + 0x158) + 0x28))((long *)(param_1 + 0x158),lVar5);
        Aska::TPoolFast<Aska::DynamicsPrimitiveElement, true>::Sink(Aska::DynamicsPrimitiveElement*)(puVar2,lVar5);
        iVar1 = (int)plVar6[5] + -1;
        *(int *)(plVar6 + 5) = iVar1;
        if (iVar1 == 0) {
          (**(code **)(*plVar6 + 8))(plVar6);
        }
      }
      lVar5 = lVar7;
    } while (param_1 + 0x160 != lVar7);
  }
  return 0;
}

// ==== Aska::ArticulatedDynamicsManagerBase::RemoveAllExtraCollision()
// vaddr 0x2075354 | ghidra 0x2175354 | size 216 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase23RemoveAllExtraCollisionEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska30ArticulatedDynamicsManagerBase23RemoveAllExtraCollisionEv(long param_1)

{
  int iVar1;
  undefined *puVar2;
  undefined *puVar3;
  long *plVar4;
  long lVar5;
  long *plVar6;
  long lVar7;
  
  puVar3 = PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38;
  puVar2 = PTR__ZN4Aska6Global27m_dynamicsPrimitiveListPoolE_02cb76c8;
  if (param_1 + 0x160 != *(long *)(param_1 + 0x170)) {
    lVar5 = *(long *)(param_1 + 0x170);
    do {
      plVar6 = *(long **)(lVar5 + 0x38);
      lVar7 = *(long *)(lVar5 + 0x10);
      if (plVar6 != (long *)0x0) {
        Aska::DynamicsManager::Delete(Aska::DynamicsHandler*)(*(undefined8 *)puVar3,lVar5);
        plVar4 = *(long **)(lVar5 + 0x38);
        if (plVar4 != (long *)0x0) {
          iVar1 = (int)plVar4[5] + -1;
          *(int *)(plVar4 + 5) = iVar1;
          if (iVar1 == 0) {
            (**(code **)(*plVar4 + 8))();
          }
          *(undefined8 *)(lVar5 + 0x38) = 0;
        }
        (**(code **)(*(long *)(param_1 + 0x158) + 0x28))((long *)(param_1 + 0x158),lVar5);
        Aska::TPoolFast<Aska::DynamicsPrimitiveElement, true>::Sink(Aska::DynamicsPrimitiveElement*)(puVar2,lVar5);
        iVar1 = (int)plVar6[5] + -1;
        *(int *)(plVar6 + 5) = iVar1;
        if (iVar1 == 0) {
          (**(code **)(*plVar6 + 8))(plVar6);
        }
      }
      lVar5 = lVar7;
    } while (param_1 + 0x160 != lVar7);
  }
  return 0;
}

// ==== Aska::ArticulatedDynamicsManagerBase::AddExtraCollision(Aska::DynamicsPrimitive*, unsigned long, unsigned long, unsigned int)
// vaddr 0x207542c | ghidra 0x217542c | size 44 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase17AddExtraCollisionEPNS_17DynamicsPrimitiveEmmj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase17AddExtraCollisionEPNS_17DynamicsPrimitiveEmmj
               (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined4 param_5)

{
  (*(code *)
    PTR__ZN4Aska30ArticulatedDynamicsManagerBase21AddExtraPrimitiveMainERNS_21DynamicsPrimitiveListEPNS_17DynamicsPrimitiveEmmj_02c94eb0
  )(param_1,param_1 + 0x158,param_2,param_3,param_4,param_5);
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::AddExtraPrimitiveMain(Aska::DynamicsPrimitiveList&, Aska::DynamicsPrimitive*, unsigned long, unsigned long, unsigned int)
// vaddr 0x2075458 | ghidra 0x2175458 | size 368 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase21AddExtraPrimitiveMainERNS_21DynamicsPrimitiveListEPNS_17DynamicsPrimitiveEmmj | lib libSOA-3.7.0.so | 2026-10-08
undefined4
_ZN4Aska30ArticulatedDynamicsManagerBase21AddExtraPrimitiveMainERNS_21DynamicsPrimitiveListEPNS_17DynamicsPrimitiveEmmj
          (undefined8 param_1,long *param_2,long *param_3,undefined8 param_4,undefined8 param_5,
          undefined4 param_6)

{
  int iVar1;
  undefined *puVar2;
  long lVar3;
  ulong uVar4;
  long *plVar5;
  long *plVar6;
  
  if (param_3 != (long *)0x0) {
    *(int *)(param_3 + 5) = (int)param_3[5] + 1;
    lVar3 = Aska::TPoolFast<Aska::DynamicsPrimitiveElement, true>::Scoop()(PTR__ZN4Aska6Global27m_dynamicsPrimitiveListPoolE_02cb76c8);
    if (lVar3 == 0) {
code_r0x0217558c:
      iVar1 = (int)param_3[5] + -1;
      *(int *)(param_3 + 5) = iVar1;
      if (iVar1 == 0) {
        (**(code **)(*param_3 + 8))(param_3);
      }
    }
    else {
      *(long **)(lVar3 + 0x38) = param_3;
      (**(code **)(*param_3 + 0x48))(param_3);
      Aska::DynamicsHandler::SetDispatchHandle(int, unsigned long)(lVar3,0,param_4);
      Aska::DynamicsHandler::SetDispatchHandle(int, unsigned long)(lVar3,1,param_5);
      (**(code **)(*param_2 + 0x10))(param_2,lVar3);
      puVar2 = PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38;
      uVar4 = Aska::DynamicsManager::Add(Aska::DynamicsHandler*, unsigned int)(*(undefined8 *)PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38,lVar3
                              ,param_6);
      if ((uVar4 & 1) != 0) {
        return 1;
      }
      for (plVar6 = (long *)param_2[3]; param_2 + 1 != plVar6; plVar6 = (long *)plVar6[2]) {
        if ((long *)plVar6[7] == param_3) {
          Aska::DynamicsManager::Delete(Aska::DynamicsHandler*)(*(undefined8 *)puVar2,plVar6);
          plVar5 = (long *)plVar6[7];
          if (plVar5 != (long *)0x0) {
            iVar1 = (int)plVar5[5] + -1;
            *(int *)(plVar5 + 5) = iVar1;
            if (iVar1 == 0) {
              (**(code **)(*plVar5 + 8))();
            }
            plVar6[7] = 0;
          }
          (**(code **)(*param_2 + 0x28))(param_2,plVar6);
          Aska::TPoolFast<Aska::DynamicsPrimitiveElement, true>::Sink(Aska::DynamicsPrimitiveElement*)(PTR__ZN4Aska6Global27m_dynamicsPrimitiveListPoolE_02cb76c8,plVar6);
          goto code_r0x0217558c;
        }
      }
    }
  }
  return 0;
}

// ==== Aska::ArticulatedDynamicsManagerBase::AddExtraCollisionFromCollisionHandler(Aska::CollisionHandler const*, unsigned short, unsigned short, unsigned long, unsigned long, unsigned int)
// vaddr 0x20755c8 | ghidra 0x21755c8 | size 840 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase37AddExtraCollisionFromCollisionHandlerEPKNS_16CollisionHandlerEttmmj | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska30ArticulatedDynamicsManagerBase37AddExtraCollisionFromCollisionHandlerEPKNS_16CollisionHandlerEttmmj
               (long param_1,long param_2,ushort param_3,ushort param_4,undefined8 param_5,
               undefined8 param_6,undefined4 param_7)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  long lVar4;
  short *psVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  short sVar8;
  long lVar9;
  long lVar10;
  undefined *puVar11;
  long *plVar12;
  ulong uVar13;
  long lVar14;
  long lVar15;
  ulong uVar16;
  code *pcVar17;
  long *plVar18;
  long lVar19;
  ulong uVar20;
  ulong uVar21;
  float fVar22;
  float fVar23;
  
  lVar10 = _UNK_027dbb38;
  lVar9 = _UNK_027dbb30;
  if (((param_2 != 0) && (*(char *)(param_2 + 0x57) != '\0')) &&
     (uVar13 = (ulong)*(ushort *)(*(long *)(param_2 + 0x10) + 4), uVar13 != 0)) {
    lVar14 = *(long *)(param_2 + 0x20);
    uVar21 = 0;
    puVar1 = PTR__ZTVN4Aska15DynamicsCapsuleE_02cc38f0 + 0x10;
    puVar2 = PTR__ZTVN4Aska12DynamicsCubeE_02cb9c70 + 0x10;
    puVar3 = PTR__ZTVN4Aska15DYNAMICS_SPHEREE_02cb7648 + 0x10;
    do {
      lVar15 = *(long *)(*(long *)(param_2 + 0x40) + uVar21 * 8);
      if ((lVar15 != 0) && (lVar15 = *(long *)(lVar15 + 0xe8), lVar15 != 0)) {
        lVar4 = lVar14 + uVar21 * 0x40;
        uVar16 = (ulong)*(ushort *)(lVar4 + 0x38);
        if (uVar16 != 0) {
          uVar20 = (ulong)*(ushort *)(lVar4 + 0x36);
          lVar4 = uVar20 + uVar16;
          do {
            psVar5 = (short *)(*(long *)(param_2 + 8) +
                              (ulong)*(uint *)(*(long *)(param_2 + 0x28) + uVar20 * 4));
            if (((psVar5[4] & param_3) != 0) || ((psVar5[5] & param_4) != 0)) {
              sVar8 = *psVar5;
              if (sVar8 == 2) {
                plVar12 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xf0,PTR__ZSt7nothrow_02cb9a80);
                if (plVar12 != (long *)0x0) {
                  plVar12[2] = 0;
                  *(undefined4 *)(plVar12 + 5) = 0;
                  *plVar12 = (long)puVar1;
                  plVar12[1] = 0;
                  *(undefined1 *)(plVar12 + 3) = 1;
                  plVar12[7] = lVar10;
                  plVar12[6] = lVar9;
                  plVar12[4] = lVar15;
                  plVar12[8] = 0;
                  *(undefined1 *)(plVar12 + 9) = 0;
                  plVar18 = plVar12 + 0xc;
                  *plVar18 = 0;
                  *(undefined4 *)(plVar12 + 0xd) = 0;
                  plVar12[0xe] = 0;
                  plVar12[10] = (long)plVar18;
                  fVar22 = *(float *)(psVar5 + 0x10);
                  plVar12[0x14] = 0;
                  *(undefined4 *)(plVar12 + 0x15) = 0;
                  *(undefined4 *)((long)plVar12 + 0xac) = 0x3f800000;
                  *(undefined4 *)((long)plVar12 + 0xb4) = 0;
                  *(undefined4 *)(plVar12 + 0x17) = 0;
                  *(undefined4 *)((long)plVar12 + 0xbc) = 0x3f800000;
                  *(float *)(plVar12 + 0x16) = fVar22;
                  *plVar18 = 0;
                  fVar23 = *(float *)(psVar5 + 8);
                  uVar6 = *(undefined4 *)(psVar5 + 10);
                  uVar7 = *(undefined4 *)(psVar5 + 0xc);
                  *(undefined4 *)((long)plVar12 + 0x3c) = 0x3f800000;
                  *(undefined4 *)((long)plVar12 + 0x34) = uVar6;
                  *(undefined4 *)(plVar12 + 7) = uVar7;
                  *(float *)(plVar12 + 6) = fVar23 + fVar22 * -0.5;
                  lVar19 = *plVar12;
                  *(undefined4 *)(plVar12 + 0x1c) = *(undefined4 *)(psVar5 + 0x12);
code_r0x021758ac:
                  pcVar17 = *(code **)(lVar19 + 0x38);
code_r0x021758b0:
                  (*pcVar17)(plVar12);
                  Aska::ArticulatedDynamicsManagerBase::AddExtraPrimitiveMain(Aska::DynamicsPrimitiveList&, Aska::DynamicsPrimitive*, unsigned long, unsigned long, unsigned int)(param_1,param_1 + 0x158,plVar12,param_5,param_6,param_7);
                }
              }
              else if (sVar8 == 1) {
                plVar12 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x170,PTR__ZSt7nothrow_02cb9a80);
                if (plVar12 != (long *)0x0) {
                  plVar12[2] = 0;
                  *(undefined4 *)(plVar12 + 5) = 0;
                  *(undefined4 *)((long)plVar12 + 0x3c) = 0x3f800000;
                  *plVar12 = (long)puVar2;
                  plVar12[1] = 0;
                  *(undefined1 *)(plVar12 + 3) = 1;
                  plVar12[4] = lVar15;
                  plVar12[8] = 0;
                  *(undefined1 *)(plVar12 + 9) = 0;
                  *(undefined4 *)(plVar12 + 0xd) = 0;
                  plVar12[0xe] = 0;
                  plVar12[0xc] = 0;
                  plVar12[10] = (long)(plVar12 + 0xc);
                  lVar19 = *plVar12;
                  *(undefined4 *)(plVar12 + 6) = *(undefined4 *)(psVar5 + 8);
                  *(undefined4 *)((long)plVar12 + 0x34) = *(undefined4 *)(psVar5 + 10);
                  *(undefined4 *)(plVar12 + 7) = *(undefined4 *)(psVar5 + 0xc);
                  *(undefined4 *)(plVar12 + 0x12) = *(undefined4 *)(psVar5 + 0x10);
                  *(undefined4 *)((long)plVar12 + 0x94) = *(undefined4 *)(psVar5 + 0x12);
                  *(undefined4 *)(plVar12 + 0x13) = *(undefined4 *)(psVar5 + 0x14);
                  *(undefined4 *)((long)plVar12 + 0x9c) = *(undefined4 *)(psVar5 + 0x16);
                  goto code_r0x021758ac;
                }
              }
              else if ((sVar8 == 0) &&
                      (plVar12 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xc0,PTR__ZSt7nothrow_02cb9a80),
                      plVar12 != (long *)0x0)) {
                plVar12[2] = 0;
                *(undefined1 *)(plVar12 + 3) = 1;
                *(undefined4 *)(plVar12 + 5) = 0;
                *(undefined4 *)((long)plVar12 + 0x3c) = 0x3f800000;
                plVar12[4] = lVar15;
                plVar12[8] = 0;
                *(undefined1 *)(plVar12 + 9) = 0;
                puVar11 = PTR__ZTVN4Aska14DynamicsSphereE_02cc30e8;
                *(undefined4 *)(plVar12 + 0xe) = 0;
                plVar12[0xf] = 0;
                plVar12[0xc] = (long)puVar3;
                *plVar12 = (long)(puVar11 + 0x10);
                plVar12[1] = 0;
                plVar12[0xd] = 0;
                plVar12[10] = (long)(plVar12 + 0xd);
                *(undefined4 *)(plVar12 + 6) = *(undefined4 *)(psVar5 + 8);
                *(undefined4 *)((long)plVar12 + 0x34) = *(undefined4 *)(psVar5 + 10);
                *(undefined4 *)(plVar12 + 7) = *(undefined4 *)(psVar5 + 0xc);
                *(undefined4 *)(plVar12 + 0x10) = *(undefined4 *)(psVar5 + 0x10);
                pcVar17 = *(code **)(puVar11 + 0x48);
                goto code_r0x021758b0;
              }
            }
            uVar20 = uVar20 + 1;
          } while ((long)uVar20 < lVar4);
        }
      }
      uVar21 = uVar21 + 1;
    } while (uVar21 != uVar13);
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::AddExtraCollisionFromCollisionHandler(Aska::AsfHandler const*, Aska::CollisionHandler const*, unsigned short, unsigned short, unsigned long, unsigned long, unsigned int)
// vaddr 0x2075910 | ghidra 0x2175910 | size 172 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase37AddExtraCollisionFromCollisionHandlerEPKNS_10AsfHandlerEPKNS_16CollisionHandlerEttmmj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase37AddExtraCollisionFromCollisionHandlerEPKNS_10AsfHandlerEPKNS_16CollisionHandlerEttmmj
               (undefined8 param_1,undefined8 param_2,undefined4 param_3,undefined4 param_4,
               undefined8 param_5,undefined8 param_6,undefined4 param_7)

{
  long lVar1;
  ulong uVar2;
  
  for (lVar1 = Aska::AsfHandler::SearchFirstByKind(unsigned char) const(param_1,0xc); lVar1 != 0; lVar1 = Aska::AsfHandler::SearchNextByKind(unsigned char, Aska::IAnimatable const*) const(param_1,0xc,lVar1))
  {
    if ((*(long *)(lVar1 + 0x198) != 0) &&
       (uVar2 = Aska::IAnimatable::IsThisIt(unsigned short) const(*(long *)(lVar1 + 0x198),0xf172), (uVar2 & 1) != 0)) {
      Aska::ArticulatedDynamicsManagerBase::AddExtraCollisionFromCollisionHandler(Aska::CollisionHandler const*, unsigned short, unsigned short, unsigned long, unsigned long, unsigned int)(*(undefined8 *)(lVar1 + 0x198),param_2,param_3,param_4,param_5,param_6,param_7
                     );
    }
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::DumpOpen(char const*, int)
// vaddr 0x20759bc | ghidra 0x21759bc | size 8 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase8DumpOpenEPKci | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska30ArticulatedDynamicsManagerBase8DumpOpenEPKci(void)

{
  return 0;
}

// ==== Aska::ArticulatedDynamicsManagerBase::Dump(char const*, int)
// vaddr 0x20759c4 | ghidra 0x21759c4 | size 8 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase4DumpEPKci | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska30ArticulatedDynamicsManagerBase4DumpEPKci(void)

{
  return 0;
}

// ==== Aska::ArticulatedDynamicsManagerBase::DumpClose(char const*)
// vaddr 0x20759cc | ghidra 0x21759cc | size 8 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase9DumpCloseEPKc | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska30ArticulatedDynamicsManagerBase9DumpCloseEPKc(void)

{
  return 0;
}

// ==== Aska::ArticulatedDynamicsManagerBase::SearchOrginalData(Aska::AsfHandler*, Aska::AsfHandler*, int)
// vaddr 0x20759d4 | ghidra 0x21759d4 | size 132 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase17SearchOrginalDataEPNS_10AsfHandlerES2_i | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska30ArticulatedDynamicsManagerBase17SearchOrginalDataEPNS_10AsfHandlerES2_i
               (undefined8 param_1,long param_2,undefined8 param_3,int param_4)

{
  long lVar1;
  long lVar2;
  
  if (param_4 < 0) {
    if (*(long *)(param_2 + 0x78) == 0) {
      lVar2 = 0;
    }
    else {
      lVar2 = *(long *)(param_2 + 0x508);
      lVar1 = *(long *)(param_2 + 0x78) + (long)(int)(param_4 << 5 ^ 0xffffffe0) + 0x20;
      if ((((lVar2 == 0) || (*(int *)(lVar2 + 0xb0) < 1)) ||
          (lVar2 = Aska::AsfHandler::QuickSearch(char const*) const(lVar2,lVar1), lVar2 == 0)) ||
         (lVar2 = *(long *)(lVar2 + 0x38), lVar2 == 0)) {
        lVar2 = (*(code *)
                  PTR__ZNK4Aska10AsfHandler37QuickSearchByNameFromExternalLinkListEPKc_02c9df78)
                          (param_2,lVar1);
        return lVar2;
      }
    }
  }
  else {
    lVar2 = *(long *)(*(long *)(*(long *)(param_2 + 0xd8) + (long)param_4 * 8) + 0x38);
  }
  return lVar2;
}

// ==== Aska::ArticulatedDynamicsManagerBase::~ArticulatedDynamicsManagerBase()
// vaddr 0x2075a5c | ghidra 0x2175a5c | size 416 | symbol _ZN4Aska30ArticulatedDynamicsManagerBaseD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBaseD2Ev(long *param_1)

{
  undefined *puVar1;
  int iVar2;
  long *plVar3;
  undefined *puVar4;
  long *plVar5;
  long *plVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  long *plVar9;
  long *plVar10;
  
  plVar6 = param_1 + 0x2b;
  *param_1 = (long)(PTR__ZTVN4Aska30ArticulatedDynamicsManagerBaseE_02cc0c60 + 0x10);
  *(undefined1 *)(param_1 + 0x1b) = 0;
  puVar4 = PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38;
  puVar1 = PTR__ZN4Aska6Global27m_dynamicsPrimitiveListPoolE_02cb76c8;
  plVar10 = (long *)param_1[0x2e];
  while (plVar3 = plVar10, param_1 + 0x2c != plVar3) {
    plVar9 = (long *)plVar3[7];
    plVar10 = (long *)plVar3[2];
    if (plVar9 != (long *)0x0) {
      Aska::DynamicsManager::Delete(Aska::DynamicsHandler*)(*(undefined8 *)puVar4,plVar3);
      plVar5 = (long *)plVar3[7];
      if (plVar5 != (long *)0x0) {
        iVar2 = (int)plVar5[5] + -1;
        *(int *)(plVar5 + 5) = iVar2;
        if (iVar2 == 0) {
          (**(code **)(*plVar5 + 8))();
        }
        plVar3[7] = 0;
      }
      (**(code **)(*plVar6 + 0x28))(plVar6,plVar3);
      Aska::TPoolFast<Aska::DynamicsPrimitiveElement, true>::Sink(Aska::DynamicsPrimitiveElement*)(puVar1,plVar3);
      iVar2 = (int)plVar9[5] + -1;
      *(int *)(plVar9 + 5) = iVar2;
      if (iVar2 == 0) {
        (**(code **)(*plVar9 + 8))(plVar9);
      }
    }
  }
  if (0 < (long)(short)param_1[0xc]) {
    puVar7 = (undefined8 *)param_1[0xe];
    puVar8 = puVar7 + (long)(short)param_1[0xc] * 0x38;
    do {
      (**(code **)*puVar7)(puVar7);
      puVar7 = puVar7 + 0x38;
    } while (puVar7 < puVar8);
  }
  if (param_1[0xd] != 0) {
    operator delete[](void*)();
    param_1[0xd] = 0;
  }
  puVar1 = PTR__ZTVN4Aska5TListINS_24DynamicsPrimitiveElementEEE_02cbed28 + 0x10;
  param_1[0x2c] = (long)(PTR__ZTVN4Aska24DynamicsPrimitiveElementE_02cbbef0 + 0x10);
  *plVar6 = (long)puVar1;
  plVar6 = (long *)param_1[0x33];
  if (plVar6 != (long *)0x0) {
    iVar2 = (int)plVar6[5] + -1;
    *(int *)(plVar6 + 5) = iVar2;
    if (iVar2 == 0) {
      (**(code **)(*plVar6 + 8))();
    }
    param_1[0x33] = 0;
  }
  Aska::DynamicsHandler::~DynamicsHandler()(param_1 + 0x2c);
  *param_1 = (long)(PTR__ZTVN4Aska20TInheritSmartPointerINS_8DynamicsELb0EEE_02cb8cb0 + 0x10);
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1);
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::~ArticulatedDynamicsManagerBase()
// vaddr 0x2075bfc | ghidra 0x2175bfc | size 4 | symbol _ZN4Aska30ArticulatedDynamicsManagerBaseD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBaseD0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x2175c00);
  (*pcVar1)();
}

// ==== Aska::ArticulatedDynamicsManagerBase::GetClassID(int) const
// vaddr 0x2075c00 | ghidra 0x2175c00 | size 56 | symbol _ZNK4Aska30ArticulatedDynamicsManagerBase10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska30ArticulatedDynamicsManagerBase10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar2 = 0xf000f001;
  if (param_2 != 0) {
    if (param_2 != 2) {
      uVar2 = 0xf000;
    }
    uVar1 = 0xf001f032;
    if (param_2 != 1) {
      uVar1 = uVar2;
    }
    return uVar1;
  }
  return 0xf000f171;
}

// ==== Aska::ArticulatedDynamicsManagerBase::DeleteThis()
// vaddr 0x2075c54 | ghidra 0x2175c54 | size 32 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase10DeleteThisEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase10DeleteThisEv(long *param_1)

{
  int iVar1;
  
  iVar1 = (int)param_1[5] + -1;
  *(int *)(param_1 + 5) = iVar1;
  if (iVar1 != 0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x02175c70. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 8))();
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::AddRefEx()
// vaddr 0x2075c74 | ghidra 0x2175c74 | size 16 | symbol _ZN4Aska30ArticulatedDynamicsManagerBase8AddRefExEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska30ArticulatedDynamicsManagerBase8AddRefExEv(long param_1)

{
  *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
  return;
}

// ==== Aska::ArticulatedDynamicsManagerBase::GetDefaultTaskLevel() const
// vaddr 0x2075c98 | ghidra 0x2175c98 | size 8 | symbol _ZNK4Aska30ArticulatedDynamicsManagerBase19GetDefaultTaskLevelEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska30ArticulatedDynamicsManagerBase19GetDefaultTaskLevelEv(void)

{
  return 0x400;
}

// ==== Aska::ADMObject::Clone(Aska::IAnimatable const*)
// vaddr 0x209efc4 | ghidra 0x219efc4 | size 92 | symbol _ZN4Aska9ADMObject5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska9ADMObject5CloneEPKNS_11IAnimatableE(long param_1,long param_2)

{
  ulong uVar1;
  long *plVar2;
  undefined8 uVar3;
  
  uVar1 = Aska::HierarchicalObject::Clone(Aska::IAnimatable const*)();
  if ((uVar1 & 1) == 0) {
    uVar3 = 0;
  }
  else {
    plVar2 = *(long **)(param_2 + 0x198);
    if (plVar2 != (long *)0x0) {
      plVar2 = (long *)(**(code **)(*plVar2 + 0x20))(plVar2,plVar2);
      if (plVar2 == (long *)0x0) {
        return 0;
      }
      *(long **)(param_1 + 0x198) = plVar2;
      (**(code **)(*plVar2 + 0x48))();
    }
    uVar3 = 1;
  }
  return uVar3;
}

// ==== Aska::ADMObject::CreateClone(Aska::IAnimatable const*)
// vaddr 0x209f020 | ghidra 0x219f020 | size 104 | symbol _ZN4Aska9ADMObject11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska9ADMObject11CreateCloneEPKNS_11IAnimatableE(undefined8 param_1,undefined8 param_2)

{
  long *plVar1;
  ulong uVar2;
  
  plVar1 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x1a0,PTR__ZSt7nothrow_02cb9a80);
  if (plVar1 != (long *)0x0) {
    Aska::ADMObject::ADMObject()(plVar1);
    uVar2 = (**(code **)(*plVar1 + 0x18))(plVar1,param_2);
    if ((uVar2 & 1) == 0) {
      (**(code **)(*plVar1 + 8))(plVar1);
      plVar1 = (long *)0x0;
    }
  }
  return plVar1;
}

// ==== Aska::ADMObject::ADMObject()
// vaddr 0x209f088 | ghidra 0x219f088 | size 296 | symbol _ZN4Aska9ADMObjectC2Ev | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska9ADMObjectC2Ev(long *param_1)

{
  byte bVar1;
  byte bVar2;
  long lVar3;
  long lVar4;
  undefined *puVar5;
  undefined4 uVar6;
  code *pcVar7;
  long *plVar8;
  long *plVar9;
  long *plVar10;
  
  pcVar7 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
  *param_1 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined2 *)((long)param_1 + 0x24) = 0;
  *(undefined1 *)((long)param_1 + 0x26) = 0;
  uVar6 = (*pcVar7)();
  *(undefined4 *)(param_1 + 4) = uVar6;
  puVar5 = PTR__ZTVN4Aska27HierarchicalObjectContainerE_02cb81a8;
  *param_1 = (long)(PTR__ZTVN4Aska18HierarchicalObjectE_02cb6bb0 + 0x10);
  plVar8 = param_1 + 6;
  *plVar8 = (long)(puVar5 + 0x10);
  *(undefined4 *)(param_1 + 0x14) = 0x3f800000;
  *(undefined4 *)((long)param_1 + 0xac) = 0x3f800000;
  lVar4 = _UNK_027dbb38;
  lVar3 = _UNK_027dbb30;
  bVar1 = *(byte *)(param_1 + 0x25);
  bVar2 = *(byte *)((long)param_1 + 0x129);
  *(byte *)((long)param_1 + 0x129) = bVar2 & 0xfc;
  *(undefined8 *)((long)param_1 + 0xa4) = 0x3f8000003f800000;
  param_1[0x11] = lVar4;
  param_1[0x10] = lVar3;
  param_1[0x13] = lVar4;
  param_1[0x12] = lVar3;
  *(byte *)(param_1 + 0x25) = bVar1 & 0xde | 1;
  plVar9 = param_1 + 0x18;
  do {
    plVar10 = (long *)((long)plVar9 + 0x7fU & 0xffffffffffffff81);
    Hint_Prefetch(plVar9,0,2,0);
    plVar9 = plVar10;
  } while (plVar10 < param_1 + 0x1a);
  param_1[0x20] = (long)plVar8;
  param_1[0x21] = (long)plVar8;
  param_1[0x1b] = lVar4;
  param_1[0x1a] = lVar3;
  param_1[0x1d] = lVar4;
  param_1[0x1c] = lVar3;
  param_1[0x17] = lVar4;
  param_1[0x16] = lVar3;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined8 *)((long)param_1 + 0xc4) = 0;
  param_1[0x1e] = 0;
  param_1[0x1f] = 0;
  param_1[0x22] = 0;
  param_1[0x23] = 0;
  param_1[5] = 0;
  *(byte *)((long)param_1 + 0x129) = bVar2 & 0xf8;
  *(undefined4 *)((long)param_1 + 0xcc) = 0x3f800000;
  param_1[0x23] = (long)param_1;
  param_1[0x24] = (long)(param_1 + 8);
  param_1[0x30] = 0;
  param_1[0x31] = 0;
  *(undefined4 *)(param_1 + 0x32) = 0;
  *(undefined1 *)((long)param_1 + 0x197) = 0;
  puVar5 = PTR__ZTVN4Aska9ADMObjectE_02cc23d8;
  *(undefined2 *)((long)param_1 + 0x194) = 1;
  *(byte *)(param_1 + 0x25) = bVar1 & 200 | 1;
  *param_1 = (long)(puVar5 + 0x10);
  param_1[0x33] = 0;
  return;
}

// ==== Aska::ADMObject::Get(unsigned long, void*) const
// vaddr 0x209f1b0 | ghidra 0x219f1b0 | size 84 | symbol _ZNK4Aska9ADMObject3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska9ADMObject3GetEmPv(long param_1,undefined8 param_2,undefined8 param_3)

{
  ulong uVar1;
  long *plVar2;
  undefined8 uVar3;
  
  uVar1 = Aska::HierarchicalObject::Get(unsigned long, void*) const();
  if (((uVar1 & 1) == 0) &&
     ((plVar2 = *(long **)(param_1 + 0x198), plVar2 == (long *)0x0 ||
      (uVar1 = (**(code **)(*plVar2 + 0x28))(plVar2,param_2,param_3), (uVar1 & 1) == 0)))) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

// ==== Aska::ADMObject::Set(unsigned long, void const*)
// vaddr 0x209f204 | ghidra 0x219f204 | size 84 | symbol _ZN4Aska9ADMObject3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska9ADMObject3SetEmPKv(long param_1,undefined8 param_2,undefined8 param_3)

{
  ulong uVar1;
  long *plVar2;
  undefined8 uVar3;
  
  uVar1 = Aska::HierarchicalObject::Set(unsigned long, void const*)();
  if (((uVar1 & 1) == 0) &&
     ((plVar2 = *(long **)(param_1 + 0x198), plVar2 == (long *)0x0 ||
      (uVar1 = (**(code **)(*plVar2 + 0x30))(plVar2,param_2,param_3), (uVar1 & 1) == 0)))) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

// ==== Aska::ADMObject::~ADMObject()
// vaddr 0x209f260 | ghidra 0x219f260 | size 60 | symbol _ZN4Aska9ADMObjectD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska9ADMObjectD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska9ADMObjectE_02cc23d8 + 0x10);
  if ((long *)param_1[0x33] != (long *)0x0) {
    (**(code **)(*(long *)param_1[0x33] + 0x40))();
    param_1[0x33] = 0;
  }
  (*(code *)PTR__ZN4Aska18HierarchicalObjectD2Ev_02ca75e8)(param_1);
  return;
}

// ==== Aska::ADMObject::~ADMObject()
// vaddr 0x209f29c | ghidra 0x219f29c | size 68 | symbol _ZN4Aska9ADMObjectD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska9ADMObjectD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska9ADMObjectE_02cc23d8 + 0x10);
  if ((long *)param_1[0x33] != (long *)0x0) {
    (**(code **)(*(long *)param_1[0x33] + 0x40))();
    param_1[0x33] = 0;
  }
  Aska::HierarchicalObject::~HierarchicalObject()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::ADMObject::GetClassID(int) const
// vaddr 0x209f2e0 | ghidra 0x219f2e0 | size 88 | symbol _ZNK4Aska9ADMObject10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska9ADMObject10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf111f14f;
  }
  if (param_2 == 1) {
    return 0xf000f002f111;
  }
  uVar2 = 0xf000f001;
  if (param_2 != 3) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf000f001f002;
  if (param_2 != 2) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::ADMHandler::ADMHandler(Aska::AsfHandler*)
// vaddr 0x23244bc | ghidra 0x24244bc | size 128 | symbol _ZN4Aska10ADMHandlerC2EPNS_10AsfHandlerE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10ADMHandlerC1EPNS_10AsfHandlerE(long *param_1,long param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined1 *)((long)param_1 + 0x36) = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  *(undefined4 *)(param_1 + 9) = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  puVar2 = PTR__ZTVN4Aska10ADMHandler11FlushNotifyE_02cc2bb8;
  puVar1 = PTR__ZTVN4Aska10ADMHandlerE_02cbc060;
  *(undefined4 *)(param_1 + 6) = 0x100;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 0;
  *(undefined1 *)((long)param_1 + 0x34) = 1;
  param_1[0xb] = (long)(puVar2 + 0x10);
  param_1[10] = (long)(puVar1 + 0x70);
  Aska::DynamicsHandler::SetDispatchHandle(int, unsigned long)(param_1,0,param_2);
  param_1[0xc] = param_2;
  *(undefined1 *)((long)param_1 + 0x36) = 1;
  return;
}

// ==== Aska::ADMHandler::Attach(Aska::AsfHandler*)
// vaddr 0x232453c | ghidra 0x242453c | size 52 | symbol _ZN4Aska10ADMHandler6AttachEPNS_10AsfHandlerE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10ADMHandler6AttachEPNS_10AsfHandlerE(long param_1,undefined8 param_2)

{
  Aska::DynamicsHandler::SetDispatchHandle(int, unsigned long)(param_1,0,param_2);
  *(undefined8 *)(param_1 + 0x60) = param_2;
  *(undefined1 *)(param_1 + 0x36) = 1;
  return;
}

// ==== Aska::ADMHandler::~ADMHandler()
// vaddr 0x2324570 | ghidra 0x2424570 | size 112 | symbol _ZN4Aska10ADMHandlerD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10ADMHandlerD2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  long lVar3;
  
  puVar1 = PTR__ZTVN4Aska10ADMHandlerE_02cbc060 + 0x70;
  *param_1 = (long)(PTR__ZTVN4Aska10ADMHandlerE_02cbc060 + 0x10);
  param_1[10] = (long)puVar1;
  if (0 < (int)param_1[9]) {
    plVar2 = (long *)param_1[7];
    while (plVar2 != (long *)0x0) {
      lVar3 = *plVar2;
      plVar2[0x35] = 0;
      plVar2 = (long *)plVar2[2];
      (**(code **)(lVar3 + 0x40))();
    }
    *(undefined4 *)(param_1 + 9) = 0;
    param_1[7] = 0;
    param_1[8] = 0;
  }
  (*(code *)PTR__ZN4Aska15DynamicsHandlerD2Ev_02cb53e0)(param_1);
  return;
}

// ==== Aska::ADMHandler::Clear()
// vaddr 0x23245e0 | ghidra 0x24245e0 | size 80 | symbol _ZN4Aska10ADMHandler5ClearEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10ADMHandler5ClearEv(long param_1)

{
  long *plVar1;
  long lVar2;
  
  if (0 < *(int *)(param_1 + 0x48)) {
    plVar1 = *(long **)(param_1 + 0x38);
    while (plVar1 != (long *)0x0) {
      lVar2 = *plVar1;
      plVar1[0x35] = 0;
      plVar1 = (long *)plVar1[2];
      (**(code **)(lVar2 + 0x40))();
    }
    *(undefined4 *)(param_1 + 0x48) = 0;
    *(long *)(param_1 + 0x38) = 0;
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  return;
}

// ==== non-virtual thunk to Aska::ADMHandler::~ADMHandler()
// vaddr 0x2324630 | ghidra 0x2424630 | size 112 | symbol _ZThn80_N4Aska10ADMHandlerD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn80_N4Aska10ADMHandlerD1Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  long lVar3;
  
  puVar1 = PTR__ZTVN4Aska10ADMHandlerE_02cbc060;
  param_1[-10] = (long)(PTR__ZTVN4Aska10ADMHandlerE_02cbc060 + 0x10);
  *param_1 = (long)(puVar1 + 0x70);
  if (0 < (int)param_1[-1]) {
    plVar2 = (long *)param_1[-3];
    while (plVar2 != (long *)0x0) {
      lVar3 = *plVar2;
      plVar2[0x35] = 0;
      plVar2 = (long *)plVar2[2];
      (**(code **)(lVar3 + 0x40))();
    }
    *(undefined4 *)(param_1 + -1) = 0;
    param_1[-3] = 0;
    param_1[-2] = 0;
  }
  (*(code *)PTR__ZN4Aska15DynamicsHandlerD2Ev_02cb53e0)(param_1 + -10);
  return;
}

// ==== Aska::ADMHandler::~ADMHandler()
// vaddr 0x23246a0 | ghidra 0x24246a0 | size 120 | symbol _ZN4Aska10ADMHandlerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10ADMHandlerD0Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  long lVar3;
  
  puVar1 = PTR__ZTVN4Aska10ADMHandlerE_02cbc060 + 0x70;
  *param_1 = (long)(PTR__ZTVN4Aska10ADMHandlerE_02cbc060 + 0x10);
  param_1[10] = (long)puVar1;
  if (0 < (int)param_1[9]) {
    plVar2 = (long *)param_1[7];
    while (plVar2 != (long *)0x0) {
      lVar3 = *plVar2;
      plVar2[0x35] = 0;
      plVar2 = (long *)plVar2[2];
      (**(code **)(lVar3 + 0x40))();
    }
    *(undefined4 *)(param_1 + 9) = 0;
    param_1[7] = 0;
    param_1[8] = 0;
  }
  Aska::DynamicsHandler::~DynamicsHandler()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::ADMHandler::~ADMHandler()
// vaddr 0x2324718 | ghidra 0x2424718 | size 120 | symbol _ZThn80_N4Aska10ADMHandlerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZThn80_N4Aska10ADMHandlerD0Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  long lVar3;
  long *plVar4;
  
  puVar1 = PTR__ZTVN4Aska10ADMHandlerE_02cbc060;
  plVar4 = param_1 + -10;
  *plVar4 = (long)(PTR__ZTVN4Aska10ADMHandlerE_02cbc060 + 0x10);
  *param_1 = (long)(puVar1 + 0x70);
  if (0 < (int)param_1[-1]) {
    plVar2 = (long *)param_1[-3];
    while (plVar2 != (long *)0x0) {
      lVar3 = *plVar2;
      plVar2[0x35] = 0;
      plVar2 = (long *)plVar2[2];
      (**(code **)(lVar3 + 0x40))();
    }
    *(undefined4 *)(param_1 + -1) = 0;
    param_1[-3] = 0;
    param_1[-2] = 0;
  }
  Aska::DynamicsHandler::~DynamicsHandler()(plVar4);
  (*(code *)PTR__ZdlPv_02ca4758)(plVar4);
  return;
}

// ==== Aska::ADMHandler::Run(int)
// vaddr 0x2324790 | ghidra 0x2424790 | size 448 | symbol _ZN4Aska10ADMHandler3RunEi | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska10ADMHandler3RunEi(long param_1)

{
  float fVar1;
  char cVar2;
  ulong uVar3;
  int *piVar4;
  long *plVar5;
  long lVar6;
  float fVar7;
  
  piVar4 = (int *)(param_1 + 0x68);
  *piVar4 = 0;
  fVar1 = _UNK_027e519c;
  plVar5 = *(long **)(param_1 + 0x38);
  if (plVar5 == (long *)0x0) {
    lVar6 = *(long *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
  }
  else {
    do {
      cVar2 = (**(code **)(*plVar5 + 0x58))(plVar5);
      if (((cVar2 != '\x02') && (*(char *)((long)plVar5 + 0xdb) == '\0')) &&
         (*(char *)((long)plVar5 + 0xdf) == '\0')) {
        fVar7 = (float)Aska::ArticulatedDynamicsManagerBase::GetDt() const(plVar5);
        *(float *)(plVar5 + 7) = fVar7;
        if (fVar1 < fVar7) {
          *piVar4 = *piVar4 + 1;
        }
      }
      plVar5 = (long *)plVar5[2];
    } while (plVar5 != (long *)0x0);
    plVar5 = *(long **)(param_1 + 0x38);
    lVar6 = *(long *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
    if (plVar5 != (long *)0x0) {
      do {
        cVar2 = (**(code **)(*plVar5 + 0x58))(plVar5);
        if (((cVar2 != '\x02') && (*(char *)((long)plVar5 + 0xdb) == '\0')) &&
           ((*(char *)((long)plVar5 + 0xdf) == '\0' && (fVar1 < *(float *)(plVar5 + 7))))) {
          Aska::ArticulatedDynamicsManagerBase::PrepareCalc(float)(plVar5);
          while (uVar3 = Aska::SimpleMessageDispatcher::PostSyncMessageSingle(unsigned short, int*, Aska::INotify*, void*, void*, unsigned int*, signed char)(lVar6,0,piVar4,plVar5 + 6,plVar5,0,0,1), (uVar3 & 1) == 0)
          {
            Aska::Event::Wait(unsigned int) const(lVar6 + 0x148,0);
          }
        }
        plVar5 = (long *)plVar5[2];
      } while (plVar5 != (long *)0x0);
    }
  }
  uVar3 = Aska::SimpleMessageDispatcher::PostSyncMessageEnd(unsigned short, int*, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(lVar6,0x12,piVar4,param_1 + 0x58,param_1,0,*(undefined8 *)(param_1 + 0x20)
                          ,*(undefined8 *)(param_1 + 0x28),0,1);
  if ((uVar3 & 1) == 0) {
    do {
      Aska::Event::Wait(unsigned int) const(lVar6 + 0x148,0);
      uVar3 = Aska::SimpleMessageDispatcher::PostSyncMessageEnd(unsigned short, int*, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(lVar6,0x12,piVar4,param_1 + 0x58,param_1,0,
                              *(undefined8 *)(param_1 + 0x20),*(undefined8 *)(param_1 + 0x28),0,1);
    } while ((uVar3 & 1) == 0);
  }
  return;
}

// ==== Aska::ADMHandler::CallFlush()
// vaddr 0x23249fc | ghidra 0x24249fc | size 172 | symbol _ZN4Aska10ADMHandler9CallFlushEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10ADMHandler9CallFlushEv(long param_1)

{
  char cVar1;
  long *plVar2;
  
  plVar2 = *(long **)(param_1 + 0x38);
  if (plVar2 != (long *)0x0) {
    do {
      while (((cVar1 = (**(code **)(*plVar2 + 0x58))(plVar2), cVar1 == '\x02' ||
              (*(char *)((long)plVar2 + 0xdf) != '\0')) || (*(char *)((long)plVar2 + 0xdb) != '\0'))
            ) {
        plVar2 = (long *)plVar2[2];
        if (plVar2 == (long *)0x0) goto code_r0x02424a58;
      }
      Aska::ArticulatedDynamicsManagerBase::Flush()(plVar2);
      plVar2 = (long *)plVar2[2];
    } while (plVar2 != (long *)0x0);
code_r0x02424a58:
    for (plVar2 = *(long **)(param_1 + 0x38); plVar2 != (long *)0x0; plVar2 = (long *)plVar2[2]) {
      cVar1 = (**(code **)(*plVar2 + 0x58))(plVar2);
      if ((cVar1 != '\x02') && (*(char *)((long)plVar2 + 0xdf) != '\0')) {
        (**(code **)(*plVar2 + 0x38))(plVar2);
      }
    }
  }
  return;
}

// ==== Aska::ADMHandler::IsHeavierHandler(Aska::DynamicsHandler*)
// vaddr 0x2324aa8 | ghidra 0x2424aa8 | size 204 | symbol _ZN4Aska10ADMHandler16IsHeavierHandlerEPNS_15DynamicsHandlerE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska10ADMHandler16IsHeavierHandlerEPNS_15DynamicsHandlerE(long param_1,long param_2)

{
  char *pcVar1;
  byte *pbVar2;
  byte *pbVar3;
  short *psVar4;
  short *psVar5;
  int iVar6;
  bool bVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  long lVar11;
  int iVar12;
  uint uVar13;
  
  lVar11 = *(long *)(param_1 + 0x38);
  if (lVar11 == 0) {
    uVar9 = 0;
    uVar8 = 0;
    lVar11 = *(long *)(param_2 + 0x38);
  }
  else {
    uVar8 = 0;
    uVar9 = 0;
    do {
      pcVar1 = (char *)(lVar11 + 0x9b);
      psVar4 = (short *)(lVar11 + 0x60);
      psVar5 = (short *)(lVar11 + 0x62);
      pbVar2 = (byte *)(lVar11 + 0x122);
      pbVar3 = (byte *)(lVar11 + 0xdf);
      lVar11 = *(long *)(lVar11 + 0x10);
      iVar12 = (int)*psVar4;
      iVar6 = *psVar5 + iVar12;
      if (*pcVar1 == '\0') {
        iVar12 = 1;
      }
      uVar8 = uVar8 + iVar12 * iVar6;
      uVar9 = uVar9 + *pbVar2 + (uint)*pbVar3;
    } while (lVar11 != 0);
    lVar11 = *(long *)(param_2 + 0x38);
  }
  if (lVar11 == 0) {
    uVar10 = 0;
    bVar7 = uVar9 == 0;
  }
  else {
    uVar13 = 0;
    uVar10 = 0;
    do {
      pcVar1 = (char *)(lVar11 + 0x9b);
      psVar4 = (short *)(lVar11 + 0x60);
      psVar5 = (short *)(lVar11 + 0x62);
      pbVar2 = (byte *)(lVar11 + 0x122);
      pbVar3 = (byte *)(lVar11 + 0xdf);
      lVar11 = *(long *)(lVar11 + 0x10);
      iVar12 = (int)*psVar4;
      iVar6 = *psVar5 + iVar12;
      if (*pcVar1 == '\0') {
        iVar12 = 1;
      }
      uVar10 = uVar10 + iVar12 * iVar6;
      uVar13 = uVar13 + *pbVar2 + (uint)*pbVar3;
    } while (lVar11 != 0);
    bVar7 = uVar9 == uVar13;
    if (uVar9 < uVar13) {
      return true;
    }
  }
  return uVar8 < uVar10 && bVar7;
}

// ==== Aska::ADMHandler::SortProcessSequence()
// vaddr 0x2324b74 | ghidra 0x2424b74 | size 1280 | symbol _ZN4Aska10ADMHandler19SortProcessSequenceEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10ADMHandler19SortProcessSequenceEv(long param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  bool bVar7;
  char cVar8;
  uint uVar9;
  long lVar10;
  long lVar11;
  ulong uVar12;
  int *piVar13;
  long *plVar14;
  ulong uVar15;
  uint uVar16;
  long lVar17;
  long lVar18;
  byte bVar19;
  long lVar20;
  ulong uVar21;
  uint uVar22;
  long lVar23;
  long *plVar24;
  long *plVar25;
  ulong uVar26;
  long lVar27;
  long alStack_7e0 [240];
  
  uVar2 = *(uint *)(param_1 + 0x48);
  uVar26 = (ulong)uVar2;
  if (0 < (int)uVar2) {
    iVar6 = uVar2 + 0x3e;
    if (-1 < (int)(uVar2 + 0x1f)) {
      iVar6 = uVar2 + 0x1f;
    }
    uVar1 = iVar6 >> 5;
    uVar5 = uVar1 * uVar2;
    lVar23 = (ulong)(uVar5 + uVar1) * 4;
    lVar10 = operator new[](unsigned long, std::nothrow_t const&)(lVar23 + uVar26 * 8,PTR__ZSt7nothrow_02cb9a80);
    if (lVar10 != 0) {
      lVar17 = lVar10 + (long)(int)uVar2 * 8;
      memset(lVar17,0,lVar23);
      plVar14 = (long *)(param_1 + 0x38);
      plVar24 = (long *)*plVar14;
      if (plVar24 != (long *)0x0) {
        lVar27 = 0;
        lVar23 = lVar17 + (ulong)uVar5 * 4;
        bVar7 = false;
        do {
          *(undefined1 *)((long)plVar24 + 0xdf) = 0;
          *(long **)(lVar10 + lVar27 * 8) = plVar24;
          cVar8 = (**(code **)(*plVar24 + 0x58))(plVar24);
          if (cVar8 != '\x02') {
            uVar9 = Aska::ArticulatedDynamicsManagerBase::MakeDynamicsPrimitiveListWithDependencyOfADM(Aska::DynamicsPrimitive**)(plVar24,alStack_7e0);
            plVar25 = (long *)*plVar14;
            if (plVar25 != (long *)0x0) {
              uVar22 = 0;
              iVar6 = uVar1 * (int)lVar27;
              if (uVar9 != 0) {
code_r0x02424d94:
                if ((plVar25 != plVar24) &&
                   (cVar8 = (**(code **)(*plVar25 + 0x58))(plVar25), cVar8 != '\x02')) {
                  uVar15 = (ulong)(iVar6 + (uVar22 >> 5));
                  uVar3 = *(uint *)(lVar17 + uVar15 * 4);
                  uVar4 = 1 << (ulong)(uVar22 & 0x1f);
                  uVar16 = 0;
                  if ((uVar3 & uVar4) != 0) goto code_r0x02424eb8;
                  do {
                    if (*(long **)(*(long *)(alStack_7e0[uVar16] + 0x50) + 0x10) == plVar25)
                    goto code_r0x02424e90;
                    uVar16 = uVar16 + 1;
                  } while (uVar16 < uVar9);
                  if ((int)plVar24[0x16] < 1) {
                    bVar19 = 0;
                  }
                  else {
                    lVar18 = 0;
                    do {
                      lVar20 = *(long *)(plVar24[0xe] +
                                         (long)*(int *)(plVar24[0x15] + lVar18 * 8) * 0x1c0 + 0x1b0)
                      ;
                      if (lVar20 != 0) {
                        if ((int)plVar25[0x16] < 1) {
                          do {
                            lVar20 = *(long *)(lVar20 + 0xc0);
                          } while (lVar20 != 0);
                        }
                        else {
                          do {
                            lVar11 = 0;
                            piVar13 = (int *)plVar25[0x15];
                            do {
                              if (*(long *)(plVar25[0xe] + (long)*piVar13 * 0x1c0 + 0x1b0) == lVar20
                                 ) goto code_r0x02424e90;
                              lVar11 = lVar11 + 1;
                              piVar13 = piVar13 + 2;
                            } while (lVar11 < (int)plVar25[0x16]);
                            lVar20 = *(long *)(lVar20 + 0xc0);
                          } while (lVar20 != 0);
                        }
                      }
                      lVar18 = lVar18 + 1;
                      bVar19 = 0;
                    } while (lVar18 < (int)plVar24[0x16]);
                  }
                  goto code_r0x02424ea0;
                }
                goto code_r0x02424eb8;
              }
              do {
                if ((plVar25 != plVar24) &&
                   (cVar8 = (**(code **)(*plVar25 + 0x58))(plVar25), cVar8 != '\x02')) {
                  uVar15 = (ulong)(iVar6 + (uVar22 >> 5));
                  uVar9 = *(uint *)(lVar17 + uVar15 * 4);
                  uVar16 = 1 << (ulong)(uVar22 & 0x1f);
                  if ((uVar9 & uVar16) == 0) {
                    if (0 < (int)plVar24[0x16]) {
                      lVar18 = 0;
                      do {
                        lVar20 = *(long *)(plVar24[0xe] +
                                           (long)*(int *)(plVar24[0x15] + lVar18 * 8) * 0x1c0 +
                                          0x1b0);
                        if (lVar20 != 0) {
                          if ((int)plVar25[0x16] < 1) {
                            do {
                              lVar20 = *(long *)(lVar20 + 0xc0);
                            } while (lVar20 != 0);
                          }
                          else {
                            do {
                              lVar11 = 0;
                              piVar13 = (int *)plVar25[0x15];
                              do {
                                if (*(long *)(plVar25[0xe] + (long)*piVar13 * 0x1c0 + 0x1b0) ==
                                    lVar20) {
                                  bVar19 = 1;
                                  *(uint *)(lVar17 + uVar15 * 4) = uVar9 | uVar16;
                                  *(undefined1 *)((long)plVar24 + 0xdf) = 1;
                                  goto code_r0x02424d64;
                                }
                                lVar11 = lVar11 + 1;
                                piVar13 = piVar13 + 2;
                              } while (lVar11 < (int)plVar25[0x16]);
                              lVar20 = *(long *)(lVar20 + 0xc0);
                            } while (lVar20 != 0);
                          }
                        }
                        lVar18 = lVar18 + 1;
                      } while (lVar18 < (int)plVar24[0x16]);
                    }
                    bVar19 = 0;
code_r0x02424d64:
                    bVar7 = (bool)(bVar7 | lVar27 < (int)uVar22 & bVar19);
                  }
                }
                plVar25 = (long *)plVar25[2];
                uVar22 = uVar22 + 1;
              } while (plVar25 != (long *)0x0);
            }
          }
code_r0x02424ec4:
          plVar24 = (long *)plVar24[2];
          lVar27 = lVar27 + 1;
        } while (plVar24 != (long *)0x0);
        if (bVar7) {
          *(undefined4 *)(param_1 + 0x48) = 0;
          *plVar14 = 0;
          *(undefined8 *)(param_1 + 0x40) = 0;
          if (0 < (int)uVar2) {
            lVar27 = 0;
            lVar18 = 0;
            uVar9 = uVar2;
            do {
              lVar20 = 0;
              uVar15 = 0;
              uVar22 = uVar9;
              do {
                uVar21 = uVar15 >> 5 & 0x7ffffff;
                uVar16 = 1 << (ulong)((uint)uVar15 & 0x1f);
                if ((*(uint *)(lVar23 + uVar21 * 4) & uVar16) == 0) {
                  uVar12 = 0;
                  do {
                    if ((*(uint *)(lVar17 + (ulong)(uint)((int)lVar20 + (int)uVar12) * 4) &
                        (*(uint *)(lVar10 + (long)(int)uVar2 * 8 + (ulong)uVar5 * 4 + uVar12 * 4) ^
                        0xffffffff)) != 0) break;
                    uVar12 = uVar12 + 1;
                  } while (uVar12 < uVar1);
                  if (uVar1 <= (uint)uVar12) {
                    lVar27 = *(long *)(lVar10 + uVar15 * 8);
                    if (*plVar14 == 0) {
                      *(undefined8 *)(lVar27 + 8) = 0;
                      *(undefined8 *)(lVar27 + 0x10) = 0;
                      *plVar14 = lVar27;
                    }
                    else {
                      *(long *)(lVar18 + 0x10) = lVar27;
                      *(undefined8 *)(lVar27 + 8) = *(undefined8 *)(param_1 + 0x40);
                      *(undefined8 *)(lVar27 + 0x10) = 0;
                    }
                    *(long *)(param_1 + 0x40) = lVar27;
                    *(undefined1 *)(param_1 + 0x36) = 1;
                    lVar18 = uVar21 * 4;
                    *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
                    uVar22 = uVar22 - 1;
                    *(uint *)(lVar23 + lVar18) = *(uint *)(lVar23 + lVar18) | uVar16;
                    lVar18 = lVar27;
                  }
                }
                uVar15 = uVar15 + 1;
                lVar20 = lVar20 + (ulong)uVar1;
              } while (uVar15 != uVar26);
              if (uVar22 == 0) goto code_r0x0242504c;
              bVar7 = uVar9 != uVar22;
              uVar9 = uVar22;
            } while (bVar7);
            if (0 < (int)uVar2) {
              uVar15 = 0;
              do {
                lVar17 = lVar27;
                if ((*(uint *)(lVar23 + (uVar15 >> 5 & 0x7ffffff) * 4) &
                    1 << (ulong)((uint)uVar15 & 0x1f)) == 0) {
                  lVar17 = *(long *)(lVar10 + uVar15 * 8);
                  if (*plVar14 == 0) {
                    *(undefined8 *)(lVar17 + 8) = 0;
                    *(undefined8 *)(lVar17 + 0x10) = 0;
                    *plVar14 = lVar17;
                  }
                  else {
                    *(long *)(lVar27 + 0x10) = lVar17;
                    *(undefined8 *)(lVar17 + 8) = *(undefined8 *)(param_1 + 0x40);
                    *(undefined8 *)(lVar17 + 0x10) = 0;
                  }
                  *(long *)(param_1 + 0x40) = lVar17;
                  *(undefined1 *)(param_1 + 0x36) = 1;
                  *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
                }
                uVar15 = uVar15 + 1;
                lVar27 = lVar17;
              } while (uVar26 != uVar15);
            }
          }
        }
      }
code_r0x0242504c:
      operator delete[](void*)(lVar10);
    }
  }
  return;
code_r0x02424e90:
  bVar19 = 1;
  *(uint *)(lVar17 + uVar15 * 4) = uVar3 | uVar4;
  *(undefined1 *)((long)plVar24 + 0xdf) = 1;
code_r0x02424ea0:
  bVar7 = (bool)(bVar7 | lVar27 < (int)uVar22 & bVar19);
code_r0x02424eb8:
  plVar25 = (long *)plVar25[2];
  uVar22 = uVar22 + 1;
  if (plVar25 == (long *)0x0) goto code_r0x02424ec4;
  goto code_r0x02424d94;
}

// ==== Aska::ADMHandler::CeckNeedToSort(unsigned int*, unsigned int, Aska::ArticulatedDynamicsManagerBase*, Aska::ArticulatedDynamicsManagerBase*, Aska::DynamicsPrimitive**, unsigned int)
// vaddr 0x2325074 | ghidra 0x2425074 | size 224 | symbol _ZN4Aska10ADMHandler14CeckNeedToSortEPjjPNS_30ArticulatedDynamicsManagerBaseES3_PPNS_17DynamicsPrimitiveEj | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska10ADMHandler14CeckNeedToSortEPjjPNS_30ArticulatedDynamicsManagerBaseES3_PPNS_17DynamicsPrimitiveEj
          (undefined8 param_1,uint *param_2,uint param_3,long param_4,long param_5,long param_6,
          uint param_7)

{
  long lVar1;
  long lVar2;
  long lVar3;
  int *piVar4;
  
  if (param_7 != 0) {
    lVar1 = 0;
    do {
      if (*(long *)(*(long *)(*(long *)(param_6 + lVar1 * 8) + 0x50) + 0x10) == param_5) {
code_r0x0242513c:
        *param_2 = *param_2 | param_3;
        *(undefined1 *)(param_4 + 0xdf) = 1;
        return 1;
      }
      lVar1 = lVar1 + 1;
    } while ((uint)lVar1 < param_7);
  }
  if (0 < *(int *)(param_4 + 0xb0)) {
    lVar1 = 0;
    do {
      lVar2 = *(long *)(*(long *)(param_4 + 0x70) +
                        (long)*(int *)(*(long *)(param_4 + 0xa8) + lVar1 * 8) * 0x1c0 + 0x1b0);
      if (lVar2 != 0) {
        if (*(int *)(param_5 + 0xb0) < 1) {
          do {
            lVar2 = *(long *)(lVar2 + 0xc0);
          } while (lVar2 != 0);
        }
        else {
          do {
            lVar3 = 0;
            piVar4 = *(int **)(param_5 + 0xa8);
            do {
              if (*(long *)(*(long *)(param_5 + 0x70) + (long)*piVar4 * 0x1c0 + 0x1b0) == lVar2)
              goto code_r0x0242513c;
              lVar3 = lVar3 + 1;
              piVar4 = piVar4 + 2;
            } while (lVar3 < *(int *)(param_5 + 0xb0));
            lVar2 = *(long *)(lVar2 + 0xc0);
          } while (lVar2 != 0);
        }
      }
      lVar1 = lVar1 + 1;
    } while (lVar1 < *(int *)(param_4 + 0xb0));
  }
  return 0;
}

// ==== Aska::ADMHandler::CheckDependentADM(Aska::ArticulatedDynamicsManagerBase*, Aska::ArticulatedDynamicsManagerBase*)
// vaddr 0x2325154 | ghidra 0x2425154 | size 168 | symbol _ZN4Aska10ADMHandler17CheckDependentADMEPNS_30ArticulatedDynamicsManagerBaseES2_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska10ADMHandler17CheckDependentADMEPNS_30ArticulatedDynamicsManagerBaseES2_
          (undefined8 param_1,long param_2,long param_3)

{
  long lVar1;
  long lVar2;
  long lVar3;
  int *piVar4;
  
  if (0 < *(int *)(param_2 + 0xb0)) {
    lVar1 = 0;
    do {
      lVar2 = *(long *)(*(long *)(param_2 + 0x70) +
                        (long)*(int *)(*(long *)(param_2 + 0xa8) + lVar1 * 8) * 0x1c0 + 0x1b0);
      if (lVar2 != 0) {
        if (*(int *)(param_3 + 0xb0) < 1) {
          do {
            lVar2 = *(long *)(lVar2 + 0xc0);
          } while (lVar2 != 0);
        }
        else {
          do {
            lVar3 = 0;
            piVar4 = *(int **)(param_3 + 0xa8);
            do {
              if (*(long *)(*(long *)(param_3 + 0x70) + (long)*piVar4 * 0x1c0 + 0x1b0) == lVar2) {
                return 1;
              }
              lVar3 = lVar3 + 1;
              piVar4 = piVar4 + 2;
            } while (lVar3 < *(int *)(param_3 + 0xb0));
            lVar2 = *(long *)(lVar2 + 0xc0);
          } while (lVar2 != 0);
        }
      }
      lVar1 = lVar1 + 1;
    } while (lVar1 < *(int *)(param_2 + 0xb0));
  }
  return 0;
}

// ==== Aska::ADMHandler::OnMakeListFromDynamicsManager()
// vaddr 0x23251fc | ghidra 0x24251fc | size 36 | symbol _ZN4Aska10ADMHandler29OnMakeListFromDynamicsManagerEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10ADMHandler29OnMakeListFromDynamicsManagerEv(long param_1)

{
  if (*(char *)(param_1 + 0x36) != '\0') {
    Aska::ADMHandler::SortProcessSequence()(param_1);
    *(undefined1 *)(param_1 + 0x36) = 0;
  }
  return;
}

// ==== Aska::ADMHandler::IsAddToDynList()
// vaddr 0x2325220 | ghidra 0x2425220 | size 84 | symbol _ZN4Aska10ADMHandler14IsAddToDynListEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska10ADMHandler14IsAddToDynListEv(long param_1)

{
  char cVar1;
  long *plVar2;
  
  if (0 < *(int *)(param_1 + 0x48)) {
    for (plVar2 = *(long **)(param_1 + 0x38); plVar2 != (long *)0x0; plVar2 = (long *)plVar2[2]) {
      cVar1 = (**(code **)(*plVar2 + 0x58))(plVar2);
      if (cVar1 != '\x02') {
        return 1;
      }
    }
  }
  return 0;
}

// ==== Aska::ADMHandler::Add(Aska::ArticulatedDynamicsManagerBase*)
// vaddr 0x2325274 | ghidra 0x2425274 | size 100 | symbol _ZN4Aska10ADMHandler3AddEPNS_30ArticulatedDynamicsManagerBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10ADMHandler3AddEPNS_30ArticulatedDynamicsManagerBaseE(long param_1,long *param_2)

{
  if (*(long *)(param_1 + 0x38) == 0) {
    param_2[1] = 0;
    param_2[2] = 0;
    *(long **)(param_1 + 0x38) = param_2;
  }
  else {
    *(long **)(*(long *)(param_1 + 0x40) + 0x10) = param_2;
    param_2[1] = *(long *)(param_1 + 0x40);
    param_2[2] = 0;
  }
  *(long **)(param_1 + 0x40) = param_2;
  *(undefined1 *)(param_1 + 0x36) = 1;
  *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
  (**(code **)(*param_2 + 0x48))(param_2);
  (*(code *)PTR__ZN4Aska15DynamicsHandler25SetDirtyToDynamicsManagerEj_02cb3898)(param_1,5);
  return;
}

// ==== Aska::ADMHandler::Insert(Aska::ArticulatedDynamicsManagerBase*, Aska::ArticulatedDynamicsManagerBase*)
// vaddr 0x23252d8 | ghidra 0x24252d8 | size 220 | symbol _ZN4Aska10ADMHandler6InsertEPNS_30ArticulatedDynamicsManagerBaseES2_ | lib libSOA-3.7.0.so | 2026-10-08
undefined4
_ZN4Aska10ADMHandler6InsertEPNS_30ArticulatedDynamicsManagerBaseES2_
          (long param_1,long param_2,long *param_3)

{
  long lVar1;
  int iVar2;
  undefined4 uVar3;
  
  lVar1 = *(long *)(param_1 + 0x38);
  if (param_2 == 0) {
    if (lVar1 == 0) {
      param_3[1] = 0;
      param_3[2] = 0;
      iVar2 = *(int *)(param_1 + 0x48) + 1;
      *(long **)(param_1 + 0x38) = param_3;
      *(long **)(param_1 + 0x40) = param_3;
      *(int *)(param_1 + 0x48) = iVar2;
      *(undefined1 *)(param_1 + 0x36) = 1;
    }
    else {
      *(long **)(lVar1 + 8) = param_3;
      param_3[1] = 0;
      param_3[2] = *(long *)(param_1 + 0x38);
      *(long **)(param_1 + 0x38) = param_3;
      iVar2 = *(int *)(param_1 + 0x48);
    }
    *(int *)(param_1 + 0x48) = iVar2 + 1;
code_r0x02425380:
    uVar3 = 1;
    *(undefined1 *)(param_1 + 0x36) = 1;
    (**(code **)(*param_3 + 0x48))(param_3);
    Aska::DynamicsHandler::SetDirtyToDynamicsManager(unsigned int)(param_1,5);
  }
  else {
    for (; lVar1 != 0; lVar1 = *(long *)(lVar1 + 0x10)) {
      if (lVar1 == param_2) {
        lVar1 = *(long *)(param_2 + 0x10);
        param_3[1] = param_2;
        param_3[2] = lVar1;
        if (lVar1 == 0) {
          *(long **)(param_1 + 0x40) = param_3;
        }
        else {
          *(long **)(lVar1 + 8) = param_3;
        }
        *(long **)(param_2 + 0x10) = param_3;
        *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
        goto code_r0x02425380;
      }
    }
    uVar3 = 0;
  }
  return uVar3;
}

// ==== Aska::ADMHandler::Delete(Aska::ArticulatedDynamicsManagerBase*)
// vaddr 0x23253b4 | ghidra 0x24253b4 | size 172 | symbol _ZN4Aska10ADMHandler6DeleteEPNS_30ArticulatedDynamicsManagerBaseE | lib libSOA-3.7.0.so | 2026-10-08
undefined4
_ZN4Aska10ADMHandler6DeleteEPNS_30ArticulatedDynamicsManagerBaseE(long param_1,long *param_2)

{
  long lVar1;
  long lVar2;
  long *plVar3;
  long *plVar4;
  
  plVar3 = (long *)(param_1 + 0x38);
  plVar4 = (long *)*plVar3;
  while( true ) {
    if (plVar4 == (long *)0x0) {
      return 0;
    }
    if (plVar4 == param_2) break;
    plVar4 = (long *)plVar4[2];
  }
  lVar1 = param_2[1];
  lVar2 = param_2[2];
  if (lVar1 == 0) {
    if (lVar2 == 0) {
      *(undefined4 *)(param_1 + 0x48) = 0;
      *plVar3 = 0;
      *(undefined8 *)(param_1 + 0x40) = 0;
      goto code_r0x02425420;
    }
    *(undefined8 *)(lVar2 + 8) = 0;
    *plVar3 = lVar2;
  }
  else if (lVar2 == 0) {
    *(undefined8 *)(lVar1 + 0x10) = 0;
    *(long *)(param_1 + 0x40) = lVar1;
  }
  else {
    *(long *)(lVar1 + 0x10) = lVar2;
    *(long *)(lVar2 + 8) = lVar1;
  }
  *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + -1;
code_r0x02425420:
  *(undefined1 *)(param_1 + 0x36) = 1;
  (**(code **)(*param_2 + 0x40))(param_2);
  Aska::DynamicsHandler::SetDirtyToDynamicsManager(unsigned int)(param_1,5);
  return 1;
}

// ==== Aska::ADMHandler::DeleteFromList(Aska::ArticulatedDynamicsManagerBase*)
// vaddr 0x2325460 | ghidra 0x2425460 | size 120 | symbol _ZN4Aska10ADMHandler14DeleteFromListEPNS_30ArticulatedDynamicsManagerBaseE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10ADMHandler14DeleteFromListEPNS_30ArticulatedDynamicsManagerBaseE
               (long param_1,long *param_2)

{
  long lVar1;
  long lVar2;
  
  lVar1 = param_2[1];
  lVar2 = param_2[2];
  if (lVar1 == 0) {
    if (lVar2 == 0) {
      *(undefined4 *)(param_1 + 0x48) = 0;
      *(undefined8 *)(param_1 + 0x38) = 0;
      *(undefined8 *)(param_1 + 0x40) = 0;
      goto code_r0x011f7150;
    }
    *(undefined8 *)(lVar2 + 8) = 0;
    *(long *)(param_1 + 0x38) = lVar2;
  }
  else if (lVar2 == 0) {
    *(undefined8 *)(lVar1 + 0x10) = 0;
    *(long *)(param_1 + 0x40) = lVar1;
  }
  else {
    *(long *)(lVar1 + 0x10) = lVar2;
    *(long *)(lVar2 + 8) = lVar1;
  }
  *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + -1;
code_r0x011f7150:
  *(undefined1 *)(param_1 + 0x36) = 1;
  (**(code **)(*param_2 + 0x40))(param_2);
  (*(code *)PTR__ZN4Aska15DynamicsHandler25SetDirtyToDynamicsManagerEj_02cb3898)(param_1,5);
  return;
}

// ==== Aska::ADMHandler::DeleteAll()
// vaddr 0x23254d8 | ghidra 0x24254d8 | size 100 | symbol _ZN4Aska10ADMHandler9DeleteAllEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10ADMHandler9DeleteAllEv(long param_1)

{
  long *plVar1;
  long lVar2;
  
  if (*(int *)(param_1 + 0x48) < 1) {
    return;
  }
  plVar1 = *(long **)(param_1 + 0x38);
  while (plVar1 != (long *)0x0) {
    lVar2 = *plVar1;
    plVar1 = (long *)plVar1[2];
    (**(code **)(lVar2 + 0x40))();
  }
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(long *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  (*(code *)PTR__ZN4Aska15DynamicsHandler25SetDirtyToDynamicsManagerEj_02cb3898)(param_1,5);
  return;
}

// ==== Aska::ADMHandler::Import(Aska::ADMHandler*)
// vaddr 0x232553c | ghidra 0x242553c | size 220 | symbol _ZN4Aska10ADMHandler6ImportEPS0_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x024255fc: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02425600) */

void _ZN4Aska10ADMHandler6ImportEPS0_(long param_1,long param_2)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  if (*(int *)(param_2 + 0x48) < 1) {
    return;
  }
  plVar1 = (long *)(param_2 + 0x38);
  lVar2 = *plVar1;
  do {
    if (lVar2 == 0) {
      (*(code *)PTR__ZN4Aska15DynamicsHandler25SetDirtyToDynamicsManagerEj_02cb3898)(param_1,5);
      return;
    }
    lVar4 = *(long *)(lVar2 + 8);
    lVar3 = *(long *)(lVar2 + 0x10);
    if (lVar4 == 0) {
      if (lVar3 != 0) {
        *(undefined8 *)(lVar3 + 8) = 0;
        *plVar1 = lVar3;
        goto code_r0x024255a8;
      }
      *(undefined4 *)(param_2 + 0x48) = 0;
      *plVar1 = 0;
      *(undefined8 *)(param_2 + 0x40) = 0;
    }
    else {
      if (lVar3 == 0) {
        *(undefined8 *)(lVar4 + 0x10) = 0;
        *(long *)(param_2 + 0x40) = lVar4;
      }
      else {
        *(long *)(lVar4 + 0x10) = lVar3;
        *(long *)(lVar3 + 8) = lVar4;
      }
code_r0x024255a8:
      *(int *)(param_2 + 0x48) = *(int *)(param_2 + 0x48) + -1;
    }
    *(undefined1 *)(param_2 + 0x36) = 1;
    if (*(long *)(param_1 + 0x38) == 0) {
      *(long *)(lVar2 + 8) = 0;
      *(undefined8 *)(lVar2 + 0x10) = 0;
      *(long *)(param_1 + 0x38) = lVar2;
    }
    else {
      *(long *)(*(long *)(param_1 + 0x40) + 0x10) = lVar2;
      *(undefined8 *)(lVar2 + 8) = *(undefined8 *)(param_1 + 0x40);
      *(undefined8 *)(lVar2 + 0x10) = 0;
    }
    *(long *)(param_1 + 0x40) = lVar2;
    *(undefined1 *)(param_1 + 0x36) = 1;
    *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
    lVar2 = *plVar1;
  } while( true );
}

// ==== Aska::ADMHandler::Export(Aska::ADMHandler*)
// vaddr 0x2325618 | ghidra 0x2425618 | size 240 | symbol _ZN4Aska10ADMHandler6ExportEPS0_ | lib libSOA-3.7.0.so | 2026-10-08
int _ZN4Aska10ADMHandler6ExportEPS0_(long param_1,long param_2)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  int iVar5;
  
  plVar1 = (long *)(param_1 + 0x38);
  iVar5 = 0;
  lVar3 = *plVar1;
  do {
    do {
      lVar2 = lVar3;
      if (lVar2 == 0) {
        if (iVar5 != 0) {
          Aska::DynamicsHandler::SetDirtyToDynamicsManager(unsigned int)(param_1,5);
          Aska::DynamicsHandler::SetDirtyToDynamicsManager(unsigned int)(param_2,5);
        }
        return iVar5;
      }
      lVar3 = *(long *)(lVar2 + 0x10);
    } while (*(long *)(lVar2 + 0x1a8) != param_2);
    lVar4 = *(long *)(lVar2 + 8);
    if (lVar4 == 0) {
      if (lVar3 != 0) {
        *(undefined8 *)(lVar3 + 8) = 0;
        *plVar1 = lVar3;
        goto code_r0x0242569c;
      }
      *(undefined4 *)(param_1 + 0x48) = 0;
      *plVar1 = 0;
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    else {
      if (lVar3 == 0) {
        *(undefined8 *)(lVar4 + 0x10) = 0;
        *(long *)(param_1 + 0x40) = lVar4;
      }
      else {
        *(long *)(lVar4 + 0x10) = lVar3;
        *(long *)(lVar3 + 8) = lVar4;
      }
code_r0x0242569c:
      *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + -1;
    }
    *(undefined1 *)(param_1 + 0x36) = 1;
    if (*(long *)(param_2 + 0x38) == 0) {
      *(long *)(lVar2 + 8) = 0;
      *(undefined8 *)(lVar2 + 0x10) = 0;
      *(long *)(param_2 + 0x38) = lVar2;
    }
    else {
      *(long *)(*(long *)(param_2 + 0x40) + 0x10) = lVar2;
      *(undefined8 *)(lVar2 + 8) = *(undefined8 *)(param_2 + 0x40);
      *(undefined8 *)(lVar2 + 0x10) = 0;
    }
    *(long *)(param_2 + 0x40) = lVar2;
    iVar5 = 1;
    *(undefined1 *)(param_2 + 0x36) = 1;
    *(int *)(param_2 + 0x48) = *(int *)(param_2 + 0x48) + 1;
  } while( true );
}

// ==== Aska::ADMHandler::ExportAll()
// vaddr 0x2325708 | ghidra 0x2425708 | size 256 | symbol _ZN4Aska10ADMHandler9ExportAllEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x02425748: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x024257e0) */

void _ZN4Aska10ADMHandler9ExportAllEv(long param_1)

{
  long lVar1;
  long lVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  
  plVar3 = (long *)(param_1 + 0x38);
  lVar5 = *plVar3;
  do {
    lVar4 = lVar5;
    if (lVar4 == 0) {
      return;
    }
    lVar1 = *(long *)(lVar4 + 0x1a8);
    lVar5 = *(long *)(lVar4 + 0x10);
  } while (lVar1 == param_1);
  lVar2 = *(long *)(lVar4 + 8);
  if (lVar2 == 0) {
    if (lVar5 == 0) {
      *(undefined4 *)(param_1 + 0x48) = 0;
      *plVar3 = 0;
      *(undefined8 *)(param_1 + 0x40) = 0;
      goto code_r0x024257a4;
    }
    *(undefined8 *)(lVar5 + 8) = 0;
    *plVar3 = lVar5;
  }
  else if (lVar5 == 0) {
    *(undefined8 *)(lVar2 + 0x10) = 0;
    *(long *)(param_1 + 0x40) = lVar2;
  }
  else {
    *(long *)(lVar2 + 0x10) = lVar5;
    *(long *)(lVar5 + 8) = lVar2;
  }
  *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + -1;
code_r0x024257a4:
  *(undefined1 *)(param_1 + 0x36) = 1;
  if (*(long *)(lVar1 + 0x38) == 0) {
    *(long *)(lVar4 + 8) = 0;
    *(undefined8 *)(lVar4 + 0x10) = 0;
    *(long *)(lVar1 + 0x38) = lVar4;
  }
  else {
    *(long *)(*(long *)(lVar1 + 0x40) + 0x10) = lVar4;
    *(undefined8 *)(lVar4 + 8) = *(undefined8 *)(lVar1 + 0x40);
    *(undefined8 *)(lVar4 + 0x10) = 0;
  }
  *(long *)(lVar1 + 0x40) = lVar4;
  *(int *)(lVar1 + 0x48) = *(int *)(lVar1 + 0x48) + 1;
  *(undefined1 *)(lVar1 + 0x36) = 1;
  (*(code *)PTR__ZN4Aska15DynamicsHandler25SetDirtyToDynamicsManagerEj_02cb3898)(lVar1,5);
  return;
}

// ==== Aska::ADMHandler::Update()
// vaddr 0x2325808 | ghidra 0x2425808 | size 56 | symbol _ZN4Aska10ADMHandler6UpdateEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska10ADMHandler6UpdateEv(long param_1)

{
  long *plVar1;
  long *plVar2;
  
  plVar1 = *(long **)(param_1 + 0x38);
  while (plVar1 != (long *)0x0) {
    plVar2 = (long *)plVar1[2];
    (**(code **)(*plVar1 + 0x68))(plVar1,0,0,0);
    plVar1 = plVar2;
  }
  return;
}

// ==== Aska::ADMHandler::IsNeedToSortByProcessHeaviness()
// vaddr 0x2325844 | ghidra 0x2425844 | size 8 | symbol _ZN4Aska10ADMHandler30IsNeedToSortByProcessHeavinessEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska10ADMHandler30IsNeedToSortByProcessHeavinessEv(void)

{
  return 1;
}

// ==== Aska::ADMJoint::InitCalcData()
// vaddr 0x232584c | ghidra 0x242584c | size 588 | symbol _ZN4Aska8ADMJoint12InitCalcDataEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska8ADMJoint12InitCalcDataEv(long param_1)

{
  undefined4 uVar1;
  bool bVar2;
  long lVar3;
  float fVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  float fVar7;
  float fVar8;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  undefined4 uStack_54;
  
  lVar3 = *(long *)(param_1 + 0x1b0);
  if (lVar3 != 0) {
    if ((*(byte *)(*(long **)(lVar3 + 0xe8) + 0x25) & 1) != 0) {
      (**(code **)(**(long **)(lVar3 + 0xe8) + 0xa8))();
    }
    if ((((((*(float *)(lVar3 + 0xb0) == 0.0) && (*(float *)(lVar3 + 0xb4) == 0.0)) &&
          (*(float *)(lVar3 + 0xb8) == 0.0)) &&
         ((*(float *)(lVar3 + 0xa0) == 0.0 && (*(float *)(lVar3 + 0xa4) == 0.0)))) &&
        ((*(float *)(lVar3 + 0xa8) == 0.0 &&
         ((*(float *)(lVar3 + 0x80) == 0.0 && (*(float *)(lVar3 + 0x84) == 0.0)))))) &&
       (*(float *)(lVar3 + 0x88) == 0.0)) {
      bVar2 = *(char *)(param_1 + 0x1bc) == '\0';
    }
    else {
      bVar2 = false;
      *(undefined1 *)(param_1 + 0x1bc) = 1;
    }
    fVar4 = *(float *)(lVar3 + 0x50);
    fVar7 = *(float *)(lVar3 + 0x54);
    fVar8 = *(float *)(lVar3 + 0x58);
    uVar1 = *(undefined4 *)(lVar3 + 0x5c);
    if (!bVar2) {
      fStack_60 = *(float *)(lVar3 + 0xb0) * *(float *)(lVar3 + 0x70);
      fStack_5c = *(float *)(lVar3 + 0xb4) * *(float *)(lVar3 + 0x74);
      fStack_58 = *(float *)(lVar3 + 0xb8) * *(float *)(lVar3 + 0x78);
      uStack_54 = *(undefined4 *)(lVar3 + 0xbc);
      *(float *)(param_1 + 0xa0) = *(float *)(lVar3 + 0xa0) - fStack_60;
      *(float *)(param_1 + 0xa4) = *(float *)(lVar3 + 0xa4) - fStack_5c;
      *(float *)(param_1 + 0xa8) = *(float *)(lVar3 + 0xa8) - fStack_58;
      *(undefined4 *)(param_1 + 0xac) = *(undefined4 *)(lVar3 + 0xac);
      Aska::Vector::ApplyQuaternion(Aska::Vector*, Aska::Quaternion const*) const((float *)(param_1 + 0xa0),&fStack_60,lVar3 + 0x60);
      fVar4 = *(float *)(lVar3 + 0x80) + fStack_60 + fVar4;
      fVar7 = *(float *)(lVar3 + 0x84) + fStack_5c + fVar7;
      fVar8 = *(float *)(lVar3 + 0x88) + fStack_58 + fVar8;
    }
    uVar5 = *(undefined8 *)(lVar3 + 0x10);
    *(undefined8 *)(param_1 + 0xb8) = *(undefined8 *)(lVar3 + 0x18);
    *(undefined8 *)(param_1 + 0xb0) = uVar5;
    uVar5 = *(undefined8 *)(lVar3 + 0x20);
    *(undefined8 *)(param_1 + 200) = *(undefined8 *)(lVar3 + 0x28);
    *(undefined8 *)(param_1 + 0xc0) = uVar5;
    uVar5 = *(undefined8 *)(lVar3 + 0x30);
    *(undefined8 *)(param_1 + 0xd8) = *(undefined8 *)(lVar3 + 0x38);
    *(undefined8 *)(param_1 + 0xd0) = uVar5;
    uVar6 = *(undefined8 *)(lVar3 + 0x48);
    uVar5 = *(undefined8 *)(lVar3 + 0x40);
    *(float *)(param_1 + 0xf0) = fVar4;
    *(float *)(param_1 + 0xf4) = fVar7;
    *(float *)(param_1 + 0xf8) = fVar8;
    *(undefined4 *)(param_1 + 0xfc) = uVar1;
    *(undefined8 *)(param_1 + 0xe8) = uVar6;
    *(undefined8 *)(param_1 + 0xe0) = uVar5;
    *(undefined4 *)(param_1 + 0x100) = *(undefined4 *)(lVar3 + 0x60);
    *(undefined4 *)(param_1 + 0x104) = *(undefined4 *)(lVar3 + 100);
    *(undefined4 *)(param_1 + 0x108) = *(undefined4 *)(lVar3 + 0x68);
    *(undefined4 *)(param_1 + 0x10c) = *(undefined4 *)(lVar3 + 0x6c);
    *(undefined4 *)(param_1 + 0x110) = *(undefined4 *)(lVar3 + 0x70);
    *(undefined4 *)(param_1 + 0x114) = *(undefined4 *)(lVar3 + 0x74);
    *(undefined4 *)(param_1 + 0x118) = *(undefined4 *)(lVar3 + 0x78);
    *(undefined4 *)(param_1 + 0x11c) = *(undefined4 *)(lVar3 + 0x7c);
    *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(lVar3 + 0x90);
    *(undefined4 *)(param_1 + 0x124) = *(undefined4 *)(lVar3 + 0x94);
    *(undefined4 *)(param_1 + 0x128) = *(undefined4 *)(lVar3 + 0x98);
    *(undefined4 *)(param_1 + 300) = *(undefined4 *)(lVar3 + 0x9c);
  }
  *(undefined8 *)(param_1 + 0x130) = 0;
  return 1;
}

// ==== Aska::ADMJoint::SetRoot(unsigned short)
// vaddr 0x2325a98 | ghidra 0x2425a98 | size 12 | symbol _ZN4Aska8ADMJoint7SetRootEt | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8ADMJoint7SetRootEt(long param_1,undefined4 param_2)

{
  *(byte *)(param_1 + 0x199) = (byte)((uint)param_2 >> 8) & 1;
  return;
}

// ==== Aska::ADMJoint::CheckLengthFromParent()
// vaddr 0x2325aa4 | ghidra 0x2425aa4 | size 96 | symbol _ZN4Aska8ADMJoint21CheckLengthFromParentEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska8ADMJoint21CheckLengthFromParentEv(long param_1)

{
  long lVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  lVar1 = *(long *)(param_1 + 0x130);
  if ((lVar1 == 0) ||
     (fVar2 = *(float *)(param_1 + 0xbc) - *(float *)(lVar1 + 0xc),
     fVar3 = *(float *)(param_1 + 0xcc) - *(float *)(lVar1 + 0x1c),
     fVar4 = *(float *)(param_1 + 0xdc) - *(float *)(lVar1 + 0x2c),
     fVar2 * fVar2 + fVar3 * fVar3 + fVar4 * fVar4 <= _UNK_027e519c)) {
    *(byte *)(param_1 + 0x19c) = *(byte *)(param_1 + 0x19c) | 4;
  }
  return;
}

// ==== Aska::ADMJoint::Init()
// vaddr 0x2325b04 | ghidra 0x2425b04 | size 172 | symbol _ZN4Aska8ADMJoint4InitEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8ADMJoint4InitEv(long param_1)

{
  long lVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 uVar6;
  
  lVar1 = *(long *)(param_1 + 0x130) + 0x60;
  if (*(long *)(param_1 + 0x130) == 0) {
    lVar1 = 0;
  }
  Aska::MatrixCalcFunc(Aska::Matrix*, Aska::Vector const*, Aska::Quaternion const*, Aska::Quaternion const*, Aska::Vector const*, Aska::Vector const*, Aska::Matrix const*)(param_1 + 0xb0,param_1 + 0xf0,param_1 + 0x100,param_1 + 0x120,param_1 + 0x110,
                  lVar1);
  uVar2 = *(undefined4 *)(param_1 + 0x100);
  uVar3 = *(undefined4 *)(param_1 + 0x104);
  uVar4 = *(undefined4 *)(param_1 + 0x108);
  *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_1 + 0xbc);
  *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_1 + 0xcc);
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0xbc);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0xcc);
  uVar5 = *(undefined4 *)(param_1 + 0x10c);
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined8 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0xdc);
  *(undefined4 *)(param_1 + 0x1c) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0xdc);
  *(undefined4 *)(param_1 + 0x2c) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  *(undefined4 *)(param_1 + 100) = uVar3;
  *(undefined4 *)(param_1 + 0x68) = uVar4;
  *(undefined4 *)(param_1 + 0x6c) = uVar5;
  *(undefined4 *)(param_1 + 0x70) = uVar2;
  *(undefined4 *)(param_1 + 0x74) = uVar3;
  *(undefined4 *)(param_1 + 0x78) = uVar4;
  *(undefined4 *)(param_1 + 0x7c) = uVar5;
  *(undefined4 *)(param_1 + 0x80) = uVar2;
  *(undefined4 *)(param_1 + 0x84) = uVar3;
  *(undefined4 *)(param_1 + 0x88) = uVar4;
  *(undefined4 *)(param_1 + 0x8c) = uVar5;
  if ((*(long *)(param_1 + 0x1b0) == 0) || (*(long *)(*(long *)(param_1 + 0x1b0) + 200) == 0)) {
    uVar6 = 0;
  }
  else {
    uVar6 = 1;
  }
  *(undefined1 *)(param_1 + 0x19a) = uVar6;
  *(undefined1 *)(param_1 + 0x19f) = 0;
  return;
}

// ==== Aska::ADMJoint::DefaultParam()
// vaddr 0x2325bb0 | ghidra 0x2425bb0 | size 36 | symbol _ZN4Aska8ADMJoint12DefaultParamEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8ADMJoint12DefaultParamEv(long param_1)

{
  *(undefined4 *)(param_1 + 0x178) = 0;
  *(undefined2 *)(param_1 + 0x19c) = 0x100;
  *(undefined4 *)(param_1 + 0x180) = 0x3f800000;
  *(undefined8 *)(param_1 + 0x170) = 0x3cf5c28f;
  return;
}

// ==== Aska::ADMJoint::Scale(float)
// vaddr 0x2325bd4 | ghidra 0x2425bd4 | size 240 | symbol _ZN4Aska8ADMJoint5ScaleEf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8ADMJoint5ScaleEf(float param_1,long param_2)

{
  long lVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  *(float *)(param_2 + 0x10) = *(float *)(param_2 + 0x10) * param_1;
  *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) * param_1;
  *(float *)(param_2 + 0x18) = *(float *)(param_2 + 0x18) * param_1;
  *(float *)(param_2 + 0x20) = *(float *)(param_2 + 0x20) * param_1;
  *(float *)(param_2 + 0x24) = *(float *)(param_2 + 0x24) * param_1;
  *(float *)(param_2 + 0x28) = *(float *)(param_2 + 0x28) * param_1;
  *(float *)(param_2 + 0x30) = *(float *)(param_2 + 0x30) * param_1;
  *(float *)(param_2 + 0x34) = *(float *)(param_2 + 0x34) * param_1;
  *(float *)(param_2 + 0x38) = *(float *)(param_2 + 0x38) * param_1;
  *(float *)(param_2 + 0x40) = *(float *)(param_2 + 0x40) * param_1;
  *(float *)(param_2 + 0x44) = *(float *)(param_2 + 0x44) * param_1;
  *(float *)(param_2 + 0x48) = *(float *)(param_2 + 0x48) * param_1;
  *(float *)(param_2 + 0x50) = *(float *)(param_2 + 0x50) * param_1;
  *(float *)(param_2 + 0x54) = *(float *)(param_2 + 0x54) * param_1;
  *(float *)(param_2 + 0x58) = *(float *)(param_2 + 0x58) * param_1;
  *(float *)(param_2 + 0x188) = *(float *)(param_2 + 0x188) * param_1;
  if (*(char *)(param_2 + 0x1bc) != '\0') {
    lVar1 = *(long *)(param_2 + 0x1b0);
    fVar5 = *(float *)(lVar1 + 0x74);
    fVar3 = *(float *)(lVar1 + 0xb4);
    fVar2 = *(float *)(lVar1 + 0xb8);
    fVar4 = *(float *)(lVar1 + 0x78);
    *(float *)(param_2 + 0xa0) =
         *(float *)(lVar1 + 0xa0) - *(float *)(lVar1 + 0xb0) * *(float *)(lVar1 + 0x70);
    *(float *)(param_2 + 0xa4) = *(float *)(lVar1 + 0xa4) - fVar3 * fVar5;
    *(float *)(param_2 + 0xa8) = *(float *)(lVar1 + 0xa8) - fVar2 * fVar4;
    *(undefined4 *)(param_2 + 0xac) = *(undefined4 *)(lVar1 + 0xac);
  }
  return;
}

// ==== Aska::ADMJoint::Get(unsigned long, void*) const
// vaddr 0x2325cc4 | ghidra 0x2425cc4 | size 656 | symbol _ZNK4Aska8ADMJoint3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska8ADMJoint3GetEmPv(long param_1,uint param_2,byte *param_3)

{
  byte bVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  long lVar4;
  ulong uVar5;
  undefined4 *puVar6;
  
  switch(param_2 & 0xffff) {
  case 0x2a:
    *(undefined4 *)param_3 = *(undefined4 *)(param_1 + 0x50);
    *(undefined4 *)(param_3 + 4) = *(undefined4 *)(param_1 + 0x54);
    *(undefined4 *)(param_3 + 8) = *(undefined4 *)(param_1 + 0x58);
    uVar3 = *(undefined4 *)(param_1 + 0x5c);
    goto code_r0x02425d04;
  case 0x2b:
    *(undefined4 *)param_3 = *(undefined4 *)(param_1 + 0x170);
    goto code_r0x02425dc4;
  case 0x2c:
    *(undefined4 *)param_3 = *(undefined4 *)(param_1 + 0x188);
    goto code_r0x02425dc4;
  case 0x2d:
    *(undefined4 *)param_3 = *(undefined4 *)(param_1 + 0x174);
    goto code_r0x02425dc4;
  case 0x2e:
    *(undefined4 *)param_3 = *(undefined4 *)(param_1 + 0x180);
    goto code_r0x02425dc4;
  case 0x2f:
    *(undefined4 *)param_3 = *(undefined4 *)(param_1 + 0x178);
    goto code_r0x02425dc4;
  case 0x30:
    bVar1 = *(byte *)(param_1 + 0x19d);
code_r0x02425d4c:
    bVar1 = bVar1 & 1;
    break;
  case 0x31:
    bVar1 = *(byte *)(param_1 + 0x19d) >> 7 ^ 1;
    break;
  case 0x32:
    bVar1 = *(byte *)(param_1 + 0x19d) >> 6 & 1;
    break;
  case 0x33:
    bVar1 = *(byte *)(param_1 + 0x19d) >> 5 & 1;
    break;
  case 0x34:
    bVar1 = *(byte *)(param_1 + 0x19d);
code_r0x02425d80:
    bVar1 = bVar1 >> 1 & 1;
    break;
  case 0x35:
    bVar1 = *(byte *)(param_1 + 0x19d);
code_r0x02425d8c:
    bVar1 = bVar1 >> 2 & 1;
    break;
  case 0x36:
    bVar1 = *(byte *)(param_1 + 0x19d) >> 4 & 1;
    break;
  default:
    lVar4 = *(long *)(param_1 + 0x160);
    uVar5 = (ulong)(param_2 >> 0x18);
    puVar6 = (undefined4 *)(lVar4 + uVar5 * 0x50);
    if (puVar6 == (undefined4 *)0x0) {
      return 0;
    }
    if (*(int *)(param_1 + 0x168) <= (int)(param_2 >> 0x18)) {
      return 0;
    }
    uVar2 = 0;
    switch(param_2 & 0xffff) {
    case 0x38:
      bVar1 = *(byte *)(lVar4 + uVar5 * 0x50 + 0x21);
      goto code_r0x02425dc0;
    case 0x39:
      *(undefined4 *)param_3 = *(undefined4 *)(lVar4 + uVar5 * 0x50 + 0x24);
      break;
    case 0x3a:
      *(undefined4 *)param_3 = *(undefined4 *)(lVar4 + uVar5 * 0x50 + 0x28);
      break;
    case 0x3b:
      *(undefined4 *)param_3 = *(undefined4 *)(lVar4 + uVar5 * 0x50 + 0x34);
      break;
    case 0x3c:
      bVar1 = *(byte *)(lVar4 + uVar5 * 0x50 + 0x20);
      goto code_r0x02425d4c;
    case 0x3d:
      bVar1 = *(byte *)(lVar4 + uVar5 * 0x50 + 0x20);
      goto code_r0x02425d80;
    case 0x3e:
      *(undefined4 *)param_3 = *(undefined4 *)(lVar4 + uVar5 * 0x50 + 0x38);
      break;
    case 0x3f:
      *(undefined4 *)param_3 = *(undefined4 *)(lVar4 + uVar5 * 0x50 + 0x3c);
      break;
    case 0x40:
      bVar1 = *(byte *)(lVar4 + uVar5 * 0x50 + 0x20);
      goto code_r0x02425d8c;
    case 0x41:
      lVar4 = lVar4 + uVar5 * 0x50;
      *(undefined4 *)param_3 = *puVar6;
      *(undefined4 *)(param_3 + 4) = *(undefined4 *)(lVar4 + 4);
      *(undefined4 *)(param_3 + 8) = *(undefined4 *)(lVar4 + 8);
      uVar3 = *(undefined4 *)(lVar4 + 0xc);
      goto code_r0x02425d04;
    case 0x42:
      bVar1 = *(byte *)(lVar4 + uVar5 * 0x50 + 0x20) >> 3 & 1;
      goto code_r0x02425dc0;
    case 0x43:
      lVar4 = lVar4 + uVar5 * 0x50;
      *(undefined4 *)param_3 = *(undefined4 *)(lVar4 + 0x10);
      *(undefined4 *)(param_3 + 4) = *(undefined4 *)(lVar4 + 0x14);
      *(undefined4 *)(param_3 + 8) = *(undefined4 *)(lVar4 + 0x18);
      uVar3 = *(undefined4 *)(lVar4 + 0x1c);
code_r0x02425d04:
      *(undefined4 *)(param_3 + 0xc) = uVar3;
      break;
    default:
      goto code_r0x02425dc8;
    case 0x48:
      *(undefined4 *)param_3 = *(undefined4 *)(lVar4 + uVar5 * 0x50 + 0x2c);
      break;
    case 0x49:
      *(undefined4 *)param_3 = *(undefined4 *)(lVar4 + uVar5 * 0x50 + 0x30);
    }
    goto code_r0x02425dc4;
  case 0x46:
    *(undefined4 *)param_3 = *(undefined4 *)(param_1 + 0x17c);
    goto code_r0x02425dc4;
  case 0x47:
    bVar1 = *(byte *)(param_1 + 0x19b);
    break;
  case 0x4a:
    bVar1 = *(char *)(param_1 + 0x19c) == '\x01';
  }
code_r0x02425dc0:
  *param_3 = bVar1;
code_r0x02425dc4:
  uVar2 = 1;
code_r0x02425dc8:
  return uVar2;
}

// ==== Aska::ADMJoint::Set(unsigned long, void const*)
// vaddr 0x2325f54 | ghidra 0x2425f54 | size 860 | symbol _ZN4Aska8ADMJoint3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska8ADMJoint3SetEmPKv(long param_1,uint param_2,float *param_3)

{
  bool bVar1;
  undefined8 uVar2;
  byte bVar3;
  long lVar4;
  byte bVar5;
  ulong uVar6;
  float *pfVar7;
  long lVar8;
  float fVar9;
  
  switch(param_2 & 0xffff) {
  case 0x2b:
    fVar9 = *param_3;
    if (1.0 < fVar9) {
      fVar9 = 1.0;
    }
    *(float *)(param_1 + 0x170) = fVar9;
    break;
  case 0x2c:
    *(float *)(param_1 + 0x188) = *param_3;
    break;
  case 0x2d:
    *(float *)(param_1 + 0x174) = *param_3;
    break;
  case 0x2e:
    *(float *)(param_1 + 0x180) = *param_3;
    break;
  case 0x2f:
    *(float *)(param_1 + 0x178) = *param_3;
    break;
  case 0x30:
    if (*(char *)param_3 == '\0') {
      bVar3 = *(byte *)(param_1 + 0x19d) & 0xfe;
    }
    else {
      bVar3 = *(byte *)(param_1 + 0x19d) | 1;
    }
    goto code_r0x024260f4;
  case 0x31:
    if (*(char *)param_3 == '\0') {
      bVar3 = *(byte *)(param_1 + 0x19d) | 0x80;
    }
    else {
      bVar3 = *(byte *)(param_1 + 0x19d) & 0x7f;
    }
    goto code_r0x024260f4;
  case 0x32:
    bVar3 = *(byte *)(param_1 + 0x19d);
    if (*(char *)param_3 == '\0') {
      bVar5 = 0xbf;
code_r0x024260f0:
      bVar3 = bVar3 & bVar5;
    }
    else {
      bVar3 = bVar3 | 0x40;
    }
    goto code_r0x024260f4;
  case 0x33:
    bVar3 = *(byte *)(param_1 + 0x19d);
    if (*(char *)param_3 == '\0') {
      bVar5 = 0xdf;
      goto code_r0x024260f0;
    }
    bVar3 = bVar3 | 0x20;
    goto code_r0x024260f4;
  case 0x34:
    bVar3 = *(byte *)(param_1 + 0x19d);
    if (*(char *)param_3 == '\0') {
      bVar5 = 0xfd;
      goto code_r0x024260f0;
    }
    bVar3 = bVar3 | 2;
    goto code_r0x024260f4;
  case 0x35:
    bVar3 = *(byte *)(param_1 + 0x19d);
    if (*(char *)param_3 == '\0') {
      bVar5 = 0xfb;
      goto code_r0x024260f0;
    }
    bVar3 = bVar3 | 4;
    goto code_r0x024260f4;
  case 0x36:
    bVar3 = *(byte *)(param_1 + 0x19d);
    if (*(char *)param_3 == '\0') {
      bVar5 = 0xef;
      goto code_r0x024260f0;
    }
    bVar3 = bVar3 | 0x10;
code_r0x024260f4:
    *(byte *)(param_1 + 0x19d) = bVar3;
    break;
  default:
    lVar4 = *(long *)(param_1 + 0x160);
    uVar6 = (ulong)(param_2 >> 0x18);
    pfVar7 = (float *)(lVar4 + uVar6 * 0x50);
    if (pfVar7 == (float *)0x0) {
      return 0;
    }
    if (*(int *)(param_1 + 0x168) <= (int)(param_2 >> 0x18)) {
      return 0;
    }
    uVar2 = 0;
    switch(param_2 & 0xffff) {
    case 0x38:
      *(char *)(lVar4 + uVar6 * 0x50 + 0x21) = *(char *)param_3;
      break;
    case 0x39:
      *(float *)(lVar4 + uVar6 * 0x50 + 0x24) = *param_3;
      break;
    case 0x3a:
      *(float *)(lVar4 + uVar6 * 0x50 + 0x28) = *param_3;
      break;
    case 0x3b:
      *(float *)(lVar4 + uVar6 * 0x50 + 0x34) = *param_3;
      break;
    case 0x3c:
      lVar4 = lVar4 + uVar6 * 0x50;
      bVar1 = *(char *)param_3 == '\0';
      bVar3 = *(byte *)(lVar4 + 0x20) & 0xfe;
      bVar5 = *(byte *)(lVar4 + 0x20) | 1;
      goto code_r0x02426250;
    case 0x3d:
      lVar4 = lVar4 + uVar6 * 0x50;
      bVar1 = *(char *)param_3 == '\0';
      bVar3 = *(byte *)(lVar4 + 0x20) & 0xfd;
      bVar5 = *(byte *)(lVar4 + 0x20) | 2;
      goto code_r0x02426250;
    case 0x3e:
      lVar8 = lVar4 + uVar6 * 0x50;
      fVar9 = *(float *)(lVar8 + 0x3c);
      *(float *)(lVar8 + 0x38) = *param_3;
      goto joined_r0x024261c4;
    case 0x3f:
      fVar9 = *param_3;
      *(float *)(lVar4 + uVar6 * 0x50 + 0x3c) = fVar9;
joined_r0x024261c4:
      if (fVar9 != 0.0) {
        lVar4 = lVar4 + uVar6 * 0x50;
        *(byte *)(lVar4 + 0x20) = *(byte *)(lVar4 + 0x20) | 2;
      }
      break;
    case 0x40:
      lVar4 = lVar4 + uVar6 * 0x50;
      bVar1 = *(char *)param_3 == '\0';
      bVar3 = *(byte *)(lVar4 + 0x20) & 0xfb;
      bVar5 = *(byte *)(lVar4 + 0x20) | 4;
      goto code_r0x02426250;
    case 0x41:
      *pfVar7 = *param_3;
      lVar4 = lVar4 + uVar6 * 0x50;
      *(float *)(lVar4 + 4) = param_3[1];
      *(float *)(lVar4 + 8) = param_3[2];
      *(float *)(lVar4 + 0xc) = param_3[3];
      break;
    case 0x42:
      lVar4 = lVar4 + uVar6 * 0x50;
      bVar1 = *(char *)param_3 == '\0';
      bVar3 = *(byte *)(lVar4 + 0x20) & 0xf7;
      bVar5 = *(byte *)(lVar4 + 0x20) | 8;
code_r0x02426250:
      if (bVar1) {
        bVar5 = bVar3;
      }
      *(byte *)(lVar4 + 0x20) = bVar5;
      break;
    case 0x43:
      lVar4 = lVar4 + uVar6 * 0x50;
      *(float *)(lVar4 + 0x10) = *param_3;
      *(float *)(lVar4 + 0x14) = param_3[1];
      *(float *)(lVar4 + 0x18) = param_3[2];
      *(float *)(lVar4 + 0x1c) = param_3[3];
      break;
    default:
      goto code_r0x024260fc;
    case 0x48:
      *(float *)(lVar4 + uVar6 * 0x50 + 0x2c) = *param_3;
      break;
    case 0x49:
      *(float *)(lVar4 + uVar6 * 0x50 + 0x30) = *param_3;
    }
    break;
  case 0x46:
    *(float *)(param_1 + 0x17c) = *param_3;
    break;
  case 0x47:
    *(char *)(param_1 + 0x19b) = *(char *)param_3;
  }
  uVar2 = 1;
code_r0x024260fc:
  return uVar2;
}

// ==== Aska::ADMJoint::ReleaseAll()
// vaddr 0x23262b0 | ghidra 0x24262b0 | size 4 | symbol _ZN4Aska8ADMJoint10ReleaseAllEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8ADMJoint10ReleaseAllEv(void)

{
  return;
}

// ==== Aska::ADMJoint::~ADMJoint()
// vaddr 0x23262b4 | ghidra 0x24262b4 | size 20 | symbol _ZN4Aska8ADMJointD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8ADMJointD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska8ADMJointE_02cbdbb0 + 0x10);
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)();
  return;
}

// ==== Aska::ADMJoint::~ADMJoint()
// vaddr 0x23262c8 | ghidra 0x24262c8 | size 40 | symbol _ZN4Aska8ADMJointD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8ADMJointD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska8ADMJointE_02cbdbb0 + 0x10);
  Aska::IAnimatable::~IAnimatable()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::ADMJoint::GetClassID(int) const
// vaddr 0x23262f0 | ghidra 0x24262f0 | size 24 | symbol _ZNK4Aska8ADMJoint10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska8ADMJoint10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0xf000f02e;
  if (param_2 != 0) {
    uVar1 = 0xf000;
  }
  return uVar1;
}

// ==== Aska::ArticulatedDynamicsManager::Attach(Aska::ADMHandler const*, Aska::AFF::AsfArticulatedDynamicsManager const*, bool)
// vaddr 0x2326308 | ghidra 0x2426308 | size 2712 | symbol _ZN4Aska26ArticulatedDynamicsManager6AttachEPKNS_10ADMHandlerEPKNS_3AFF29AsfArticulatedDynamicsManagerEb | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska26ArticulatedDynamicsManager6AttachEPKNS_10ADMHandlerEPKNS_3AFF29AsfArticulatedDynamicsManagerEb
          (long *param_1,long param_2,long param_3,ulong param_4)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  undefined *puVar4;
  byte *pbVar5;
  int *piVar6;
  undefined1 *puVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  byte bVar16;
  byte bVar17;
  ushort uVar18;
  ushort uVar19;
  undefined8 uVar20;
  undefined1 uVar21;
  byte bVar22;
  long lVar23;
  ulong uVar24;
  long lVar25;
  long lVar26;
  ulong uVar27;
  long lVar28;
  long lVar29;
  long lVar30;
  ushort *puVar31;
  ulong uVar32;
  undefined8 uVar33;
  int *piVar34;
  undefined2 *puVar35;
  undefined2 *puVar36;
  undefined2 *puVar37;
  undefined2 *puVar38;
  undefined2 *puVar39;
  undefined4 *puVar40;
  undefined4 *puVar41;
  short sVar42;
  undefined8 *puVar43;
  ulong uVar44;
  ulong uVar45;
  byte *pbVar46;
  undefined4 *puVar47;
  long lVar48;
  long lVar49;
  ulong uVar50;
  int iVar51;
  float fVar52;
  int iVar53;
  int iVar54;
  int iVar55;
  int iVar56;
  int iVar57;
  int iVar58;
  int iVar59;
  undefined2 uVar60;
  ulong uVar61;
  int iStack_80;
  int iStack_7c;
  long lStack_78;
  
  if (param_3 == 0) {
    if (*(char *)((long)param_1 + 0xe5) == '\0') {
      return 1;
    }
    param_3 = param_1[0x36];
    if (param_3 == 0) {
      return 0;
    }
code_r0x02426370:
    if (param_2 != 0) goto code_r0x02426374;
code_r0x02426354:
    lVar48 = param_1[0x35];
    if (param_1[0x35] == 0) {
      return 0;
    }
  }
  else {
    param_1[0x36] = param_3;
    if ((*(byte *)(param_3 + 0x118) >> 2 & 1) == 0) goto code_r0x02426370;
    *(undefined1 *)((long)param_1 + 0xe5) = 1;
    if (param_2 == 0) goto code_r0x02426354;
code_r0x02426374:
    param_1[0x35] = param_2;
    lVar48 = param_2;
  }
  lVar48 = *(long *)(lVar48 + 0x60);
  uVar8 = *(uint *)(param_3 + 0x128);
  uVar9 = *(uint *)(param_3 + 300);
  uVar10 = *(uint *)(param_3 + 0x130);
  uVar61 = *(ulong *)(param_3 + 0x138);
  uVar11 = *(uint *)(param_3 + 0x140);
  *(int *)((long)param_1 + 0x8c) =
       (*(int *)PTR__ZN4Aska30ArticulatedDynamicsManagerBase10m_uiExSeedE_02cc4440 +
       *(int *)PTR__ZN4Aska30ArticulatedDynamicsManagerBase12m_uiBaseSeedE_02cc3f60) * 0x19660d +
       0x78dde6be;
  if (*(char *)(param_3 + 0x144) != '\0') {
    (**(code **)(*param_1 + 0x60))(param_1);
  }
  uVar18 = *(ushort *)(param_3 + 0x11a);
  uVar44 = (ulong)uVar18;
  if (uVar44 == 0) {
    return 0;
  }
  piVar6 = (int *)((ulong)uVar8 + param_3);
  if ((param_2 != 0) && ((param_4 & 1) == 0)) {
    lVar30 = 0;
    piVar34 = piVar6;
    do {
      if (*piVar34 < 0) {
        return 1;
      }
      lVar30 = lVar30 + 1;
      piVar34 = piVar34 + 0xc;
    } while (lVar30 < (long)uVar44);
  }
  lVar30 = 0;
  puVar47 = (undefined4 *)((ulong)uVar10 + param_3);
  lVar26 = (ulong)uVar11 + param_3;
  iStack_7c = 0;
  piVar34 = piVar6;
  do {
    if (((*(byte *)((long)piVar34 + 0x1f) & 1) != 0) &&
       (lVar23 = Aska::ArticulatedDynamicsManagerBase::SearchOrginalData(Aska::AsfHandler*, Aska::AsfHandler*, int)(param_1,lVar48,0,*piVar34), lVar23 != 0)) {
      if (*(long *)(lVar23 + 0xf0) == 0) {
        return 1;
      }
      if (*(long *)(*(long *)(lVar23 + 0xf0) + 0xe8) == 0) {
        return 1;
      }
      iStack_7c = iStack_7c + 1;
    }
    lVar30 = lVar30 + 1;
    piVar34 = piVar34 + 0xc;
  } while (lVar30 < (long)uVar44);
  if (uVar18 < 8) {
    lVar30 = 0;
code_r0x02426554:
    iVar51 = 0;
code_r0x02426558:
    lVar23 = uVar44 - lVar30;
    puVar31 = (ushort *)((long)piVar6 + lVar30 * 0x30 + 0x1e);
    do {
      lVar23 = lVar23 + -1;
      if ((*puVar31 & 0x81) == 0x80) {
        iVar51 = iVar51 + 1;
      }
      puVar31 = puVar31 + 0x18;
    } while (lVar23 != 0);
  }
  else {
    lVar30 = uVar44 - (uVar44 & 7);
    if (lVar30 == 0) goto code_r0x02426554;
    iVar51 = 0;
    iVar53 = 0;
    iVar54 = 0;
    iVar55 = 0;
    puVar35 = (undefined2 *)((long)piVar6 + 0xde);
    iVar56 = 0;
    iVar57 = 0;
    iVar58 = 0;
    iVar59 = 0;
    lVar23 = lVar30;
    do {
      puVar36 = puVar35 + -0x60;
      uVar60 = *puVar35;
      puVar37 = puVar35 + -0x48;
      puVar1 = puVar35 + 0x18;
      puVar38 = puVar35 + -0x30;
      puVar2 = puVar35 + 0x30;
      puVar39 = puVar35 + -0x18;
      puVar3 = puVar35 + 0x48;
      lVar23 = lVar23 + -8;
      puVar35 = puVar35 + 0xc0;
      uVar24 = CONCAT26(*puVar3,CONCAT24(*puVar2,CONCAT22(*puVar1,uVar60))) & 0x81008100810081;
      uVar27 = CONCAT26(*puVar39,CONCAT24(*puVar38,CONCAT22(*puVar37,*puVar36))) & 0x81008100810081;
      iVar56 = iVar56 + (uint)(-((short)uVar24 == 0x80) & 1);
      iVar57 = iVar57 + (uint)(-((short)(uVar24 >> 0x10) == 0x80) & 1);
      iVar58 = iVar58 + (uint)(-((short)(uVar24 >> 0x20) == 0x80) & 1);
      iVar59 = iVar59 + (uint)(-((short)(uVar24 >> 0x30) == 0x80) & 1);
      iVar51 = iVar51 + (uint)(-((short)uVar27 == 0x80) & 1);
      iVar53 = iVar53 + (uint)(-((short)(uVar27 >> 0x10) == 0x80) & 1);
      iVar54 = iVar54 + (uint)(-((short)(uVar27 >> 0x20) == 0x80) & 1);
      iVar55 = iVar55 + (uint)(-((short)(uVar27 >> 0x30) == 0x80) & 1);
    } while (lVar23 != 0);
    iVar51 = iVar56 + iVar51 + iVar57 + iVar53 + iVar58 + iVar54 + iVar59 + iVar55;
    if ((uVar18 & 7) != 0) goto code_r0x02426558;
  }
  *(int *)(param_1 + 0x11) = iVar51;
  bVar16 = *(byte *)(param_3 + 0x126);
  uVar50 = (ulong)bVar16;
  bVar17 = *(byte *)(param_3 + 0x127);
  uVar45 = (ulong)bVar17;
  uVar19 = *(ushort *)(param_3 + 0x124);
  uVar27 = (ulong)uVar19;
  uVar24 = (**(code **)(*param_1 + 0x78))(param_1,uVar18,uVar27,uVar50,uVar45,iStack_7c);
  if (param_1[0xd] == 0) {
    uVar32 = param_1[0x10];
code_r0x024265fc:
    if (uVar32 == 0) goto code_r0x02426610;
    lVar30 = param_1[0xd];
    uVar33 = _UNK_027dbb30;
    uVar20 = _UNK_027dbb38;
  }
  else {
    Aska::ArticulatedDynamicsManagerBase::ReserveJointParamsForUpdate()(param_1);
    uVar32 = param_1[0x10];
    if (uVar24 <= uVar32) goto code_r0x024265fc;
    if (param_1[0xd] != 0) {
      operator delete[](void*)();
    }
    param_1[0x10] = 0;
code_r0x02426610:
    lVar30 = operator new[](unsigned long, unsigned long, bool)(uVar24,0x10,1);
    param_1[0xd] = lVar30;
    param_1[0x10] = uVar24;
    uVar33 = _UNK_027dbb30;
    uVar20 = _UNK_027dbb38;
  }
  _UNK_027dbb30 = uVar33;
  _UNK_027dbb38 = uVar20;
  if (lVar30 == 0) {
    param_1[0x10] = 0;
    return 0;
  }
  uVar12 = *(undefined4 *)(param_3 + 0x114);
  puVar4 = PTR__ZTVN4Aska8ADMJointE_02cbdbb0 + 0x10;
  uVar24 = lVar30 + (uVar44 + 1) * 0x1c0 + 0xf & 0xfffffffffffffff0;
  lVar23 = 0x1bc;
  param_1[0x1a] = uVar24;
  lStack_78 = uVar24 + (uint)((int)(uVar44 + 1) << 6);
  *(undefined4 *)(param_1 + 0x1e) = uVar12;
  param_1[0xe] = lVar30;
  uVar24 = uVar44;
  while( true ) {
    puVar7 = (undefined1 *)(lVar30 + lVar23);
    *(undefined **)(puVar7 + -0x1bc) = puVar4;
    *(undefined8 *)(puVar7 + -0x6c) = 0;
    *(undefined4 *)(puVar7 + -100) = 0;
    *(undefined8 *)(puVar7 + -0x5c) = 0;
    *(undefined4 *)(puVar7 + -0x54) = 0;
    *(undefined4 *)(puVar7 + -0x48) = 0;
    *(undefined8 *)(puVar7 + -0x2c) = 0;
    *(undefined2 *)(puVar7 + -0x22) = 1;
    *(undefined8 *)(puVar7 + -0xc) = 0;
    *(undefined8 *)(puVar7 + -0x114) = uVar20;
    *(undefined8 *)(puVar7 + -0x11c) = uVar33;
    *puVar7 = 0;
    if (uVar24 == 0) break;
    lVar30 = param_1[0xe];
    uVar24 = uVar24 - 1;
    lVar23 = lVar23 + 0x1c0;
  }
  iStack_80 = 0;
  *(ushort *)(param_1 + 0xc) = uVar18;
  uVar12 = *(undefined4 *)(param_3 + 0x100);
  lVar23 = 0;
  lVar30 = 0;
  *(undefined4 *)(param_1 + 8) = uVar12;
  uVar13 = *(undefined4 *)(param_3 + 0x104);
  *(undefined4 *)((long)param_1 + 0x44) = uVar13;
  uVar14 = *(undefined4 *)(param_3 + 0x108);
  pbVar46 = (byte *)(piVar6 + 8);
  uVar21 = 1;
  *(undefined4 *)(param_1 + 9) = uVar14;
  uVar15 = *(undefined4 *)(param_3 + 0x10c);
  *(undefined4 *)((long)param_1 + 0x54) = uVar13;
  *(undefined4 *)(param_1 + 0xb) = uVar14;
  lVar49 = param_1[0xe];
  *(undefined4 *)((long)param_1 + 0x4c) = uVar15;
  *(undefined4 *)(param_1 + 10) = uVar12;
  *(undefined4 *)((long)param_1 + 0x5c) = uVar15;
  puVar43 = (undefined8 *)(param_1[0x1a] + 0x20);
  *(undefined4 *)((long)param_1 + 0xf4) = *(undefined4 *)(param_3 + 0x110);
  lVar28 = lVar26;
  do {
    lVar29 = lVar49 + lVar23;
    lVar25 = Aska::ArticulatedDynamicsManagerBase::SearchOrginalData(Aska::AsfHandler*, Aska::AsfHandler*, int)(param_1,lVar48,0,*(int *)(pbVar46 + -0x20));
    if (lVar25 == 0) {
      lVar25 = 0;
      uVar21 = 0;
    }
    else {
      lVar25 = lVar25 + 0x30;
      *(long *)(lVar29 + 0x1b0) = lVar25;
    }
    uVar24 = Aska::ADMJoint::InitCalcData()(lVar29);
    if ((uVar24 & 1) == 0) goto code_r0x02426c6c;
    if (lVar25 != 0) {
      uVar33 = *(undefined8 *)(lVar25 + 0x10);
      puVar43[-3] = *(undefined8 *)(lVar25 + 0x18);
      puVar43[-4] = uVar33;
      uVar33 = *(undefined8 *)(lVar25 + 0x20);
      puVar43[-1] = *(undefined8 *)(lVar25 + 0x28);
      puVar43[-2] = uVar33;
      uVar33 = *(undefined8 *)(lVar25 + 0x30);
      puVar43[1] = *(undefined8 *)(lVar25 + 0x38);
      *puVar43 = uVar33;
      uVar33 = *(undefined8 *)(lVar25 + 0x40);
      puVar43[3] = *(undefined8 *)(lVar25 + 0x48);
      puVar43[2] = uVar33;
    }
    Aska::ADMJoint::SetRoot(unsigned short)(lVar29,*(undefined2 *)(pbVar46 + -2));
    lVar49 = lVar49 + lVar23;
    *(byte *)(lVar49 + 0x19c) = pbVar46[-2] & 1;
    *(byte *)(lVar49 + 0x19d) =
         ((byte)*(undefined2 *)(pbVar46 + -2) & 0xf0 | (*pbVar46 != 0) << 3) ^ 0x80;
    fVar52 = *(float *)(pbVar46 + -8);
    if (1.0 < fVar52) {
      fVar52 = 1.0;
    }
    *(float *)(lVar49 + 0x170) = fVar52;
    *(int *)(lVar49 + 0x174) = *(int *)(pbVar46 + -0x14);
    *(int *)(lVar49 + 0x188) = *(int *)(pbVar46 + -0x18);
    *(int *)(lVar49 + 0x180) = *(int *)(pbVar46 + -0x1c);
    *(int *)(lVar49 + 0x178) = *(int *)(pbVar46 + -0x10);
    *(int *)(lVar49 + 0x17c) = *(int *)(pbVar46 + -0xc);
    uVar12 = 0x3f000000;
    if (*(char *)(param_3 + 0x146) == '\0') {
      uVar12 = 0x3f800000;
    }
    *(undefined4 *)(lVar49 + 0x184) = uVar12;
    *(uint *)(lVar49 + 0x168) = (uint)*(ushort *)(pbVar46 + -4);
    bVar22 = *pbVar46;
    if (bVar22 != 0) {
      *(uint *)(lVar49 + 0x158) = (uint)bVar22;
      *(long *)(lVar49 + 0x150) = lVar28;
      lVar28 = lVar28 + (ulong)bVar22;
      iStack_80 = iStack_80 + (uint)bVar22;
    }
    lVar49 = param_1[0xe];
    lVar30 = lVar30 + 1;
    lVar23 = lVar23 + 0x1c0;
    puVar43 = puVar43 + 8;
    pbVar46 = pbVar46 + 0x30;
  } while (lVar30 < (long)uVar44);
  lVar49 = lVar49 + uVar44 * 0x1c0;
  *(undefined8 *)(lVar49 + 0x1b0) = *(undefined8 *)(lVar49 + -0x10);
  Aska::ArticulatedDynamicsManagerBase::InitParentOfRoots(unsigned char**, int)(param_1,&lStack_78,iStack_7c);
  uVar24 = 0;
  iVar51 = 0;
  uVar32 = lStack_78 + 0xfU & 0xfffffffffffffff0;
  param_1[0xf] = uVar32;
  lStack_78 = uVar32 + uVar27 * 0x50;
  *(ushort *)((long)param_1 + 0x62) = uVar19;
  while( true ) {
    lVar23 = param_1[0xe];
    lVar30 = lVar23 + uVar24 * 0x1c0;
    *(ulong *)(lVar30 + 0x160) = uVar32 + (long)iVar51 * 0x50;
    if (uVar19 != 0) {
      lVar23 = lVar23 + uVar24 * 0x1c0;
      pbVar46 = (byte *)(lVar23 + 0x19c);
      uVar32 = uVar27;
      puVar40 = (undefined4 *)((ulong)uVar9 + param_3 + 0x30);
      do {
        if (uVar24 == (uint)puVar40[-0xc]) {
          lVar49 = param_1[0xf];
          lVar28 = (long)iVar51;
          puVar41 = (undefined4 *)(lVar49 + (long)iVar51 * 0x50);
          *(long *)(puVar41 + 0x10) = lVar30;
          lVar25 = param_1[0xe];
          iVar53 = puVar40[-0xb];
          pbVar5 = (byte *)(puVar41 + 8);
          *(long *)(puVar41 + 0x12) = lVar25 + (long)iVar53 * 0x1c0;
          puVar41[0xd] = puVar40[-10];
          *(bool *)((long)puVar41 + 0x21) = *(char *)(puVar40 + -4) != '\0';
          puVar41[9] = puVar40[-9];
          puVar41[0xb] = puVar40[-8];
          puVar41[0xc] = puVar40[-7];
          bVar22 = *(char *)((long)puVar40 + -0xf) != '\0';
          *(byte *)(puVar41 + 8) = bVar22;
          fVar52 = (float)puVar40[-6];
          if ((fVar52 != 0.0) || ((float)puVar40[-5] != 0.0)) {
            bVar22 = bVar22 | 2;
            *pbVar5 = bVar22;
            fVar52 = (float)puVar40[-6];
          }
          lVar29 = lVar49 + lVar28 * 0x50;
          *(float *)(lVar29 + 0x38) = fVar52;
          *(undefined4 *)(lVar29 + 0x3c) = puVar40[-5];
          if (*(char *)((long)puVar40 + -0xe) != '\0') {
            bVar22 = bVar22 | 4;
            *pbVar5 = bVar22;
          }
          iVar51 = iVar51 + 1;
          if (*(char *)((long)puVar40 + -0xd) != '\0') {
            bVar22 = bVar22 | 8;
            *pbVar5 = bVar22;
          }
          lVar49 = lVar49 + lVar28 * 0x50;
          *puVar41 = *puVar40;
          *(undefined4 *)(lVar49 + 4) = puVar40[1];
          *(undefined4 *)(lVar49 + 8) = puVar40[2];
          *(undefined4 *)(lVar49 + 0xc) = puVar40[3];
          *(undefined4 *)(lVar49 + 0x10) = puVar40[4];
          *(undefined4 *)(lVar49 + 0x14) = puVar40[5];
          *(undefined4 *)(lVar49 + 0x18) = puVar40[6];
          *(undefined4 *)(lVar49 + 0x1c) = puVar40[7];
          lVar49 = *(long *)(lVar25 + (long)iVar53 * 0x1c0 + 0x1b0);
          if ((lVar49 != 0) && (*(long *)(lVar49 + 0xc0) == *(long *)(lVar23 + 0x1b0))) {
            *pbVar5 = bVar22 | 0x10;
            *pbVar46 = *pbVar46 | 8;
            *(byte *)(*(long *)(puVar41 + 0x12) + 0x19c) =
                 *(byte *)(*(long *)(puVar41 + 0x12) + 0x19c) | 2;
          }
        }
        uVar32 = uVar32 - 1;
        puVar40 = puVar40 + 0x14;
      } while (uVar32 != 0);
    }
    uVar24 = uVar24 + 1;
    if (uVar24 == uVar44) break;
    uVar32 = param_1[0xf];
  }
  uVar24 = 0;
  *(undefined4 *)(param_1 + 0x19) = *(undefined4 *)(param_3 + 0x120);
  param_1[0x18] = param_3 + (uVar61 >> 0x20);
  param_1[0x17] = param_3 + (uVar61 & 0xffffffff);
  do {
    lVar30 = param_1[0xe];
    if (((*(char *)(lVar30 + uVar24 * 0x1c0 + 0x199) == '\0') &&
        (lVar23 = *(long *)(lVar30 + uVar24 * 0x1c0 + 0x1b0), lVar23 != 0)) &&
       (lVar23 = *(long *)(lVar23 + 0xc0), lVar23 != 0)) {
      uVar61 = 0;
      lVar49 = lVar30;
      do {
        if ((uVar24 != uVar61) && (*(long *)(lVar49 + 0x1b0) == lVar23)) {
          lVar30 = lVar30 + uVar24 * 0x1c0;
          *(long *)(lVar30 + 400) = lVar49;
          *(long *)(lVar30 + 0x130) = lVar49 + 0xb0;
          break;
        }
        uVar61 = uVar61 + 1;
        lVar49 = lVar49 + 0x1c0;
      } while ((long)uVar61 < (long)uVar44);
    }
    Aska::ADMJoint::CheckLengthFromParent()();
    uVar24 = uVar24 + 1;
  } while (uVar24 != uVar44);
  uVar61 = Aska::ArticulatedDynamicsManagerBase::InitJoints(unsigned char**)(param_1,&lStack_78);
  if ((uVar61 & 1) == 0) {
code_r0x02426c6c:
    if (0 < (long)(short)param_1[0xc]) {
      lVar48 = 0;
      uVar61 = (long)(short)param_1[0xc] & 0xffffffff;
      do {
        Aska::ADMJoint::ReleaseAll()(param_1[0xe] + lVar48);
        uVar61 = uVar61 - 1;
        lVar48 = lVar48 + 0x1c0;
      } while (uVar61 != 0);
    }
    return 0;
  }
  if (bVar16 != 0) {
    lVar30 = 0;
    param_1[0x29] = lStack_78;
    *(ushort *)((long)param_1 + 100) = (ushort)bVar16;
    sVar42 = 0;
    lVar23 = lStack_78;
    lStack_78 = lStack_78 + uVar50 * 8;
    while( true ) {
      lVar49 = Aska::ArticulatedDynamicsManagerBase::SearchOrginalData(Aska::AsfHandler*, Aska::AsfHandler*, int)(param_1,lVar48,0,puVar47[lVar30]);
      if (lVar49 != 0) {
        sVar42 = sVar42 + 1;
        *(undefined8 *)(lVar23 + lVar30 * 8) = *(undefined8 *)(lVar49 + 0x198);
      }
      if (uVar50 - 1 == lVar30) break;
      lVar23 = param_1[0x29];
      lVar30 = lVar30 + 1;
    }
    puVar47 = puVar47 + (ulong)(bVar16 - 1) + 1;
    *(short *)((long)param_1 + 100) = sVar42;
  }
  if (bVar17 != 0) {
    uVar61 = Aska::ArticulatedDynamicsManagerBase::AllocConstraintList(unsigned char**, int)(param_1,&lStack_78,uVar45);
    if ((uVar61 & 1) == 0) goto code_r0x02426c6c;
    puVar43 = (undefined8 *)param_1[0x2a];
    do {
      lVar30 = Aska::ArticulatedDynamicsManagerBase::SearchOrginalData(Aska::AsfHandler*, Aska::AsfHandler*, int)(param_1,lVar48,0,*puVar47);
      if (lVar30 == 0) {
        uVar33 = 0;
      }
      else {
        uVar33 = *(undefined8 *)(lVar30 + 0x198);
      }
      *puVar43 = uVar33;
      uVar45 = uVar45 - 1;
      puVar47 = puVar47 + 1;
      puVar43 = puVar43 + 1;
    } while (uVar45 != 0);
    param_1[0x25] = lVar26;
    *(int *)((long)param_1 + 0x124) = iStack_80;
  }
  bVar16 = *(byte *)(param_3 + 0x118);
  if ((bVar16 & 1) != 0) {
    *(byte *)((long)param_1 + 0x9a) = *(byte *)((long)param_1 + 0x9a) | 1;
    bVar16 = *(byte *)(param_3 + 0x118);
  }
  if ((bVar16 >> 1 & 1) != 0) {
    *(byte *)((long)param_1 + 0x9a) = *(byte *)((long)param_1 + 0x9a) | 2;
  }
  *(undefined1 *)((long)param_1 + 0x9b) = *(undefined1 *)(param_3 + 0x146);
  if (*(char *)(param_3 + 0x119) != '\0') {
    iVar51 = *(int *)(param_3 + 0x11c);
    if (iVar51 < 0) {
      if (*(long *)(lVar48 + 0x78) != 0) {
        lVar26 = *(long *)(lVar48 + 0x508);
        lVar30 = *(long *)(lVar48 + 0x78) + (long)(int)(iVar51 << 5 ^ 0xffffffe0) + 0x20;
        if (((lVar26 == 0) || (*(int *)(lVar26 + 0xb0) < 1)) ||
           ((lVar26 = Aska::AsfHandler::QuickSearch(char const*) const(lVar26,lVar30), lVar26 == 0 ||
            (lVar26 = *(long *)(lVar26 + 0x38), lVar26 == 0)))) {
          lVar26 = Aska::AsfHandler::QuickSearchByNameFromExternalLinkList(char const*) const(lVar48,lVar30);
          goto joined_r0x02426d0c;
        }
        goto code_r0x02426d10;
      }
    }
    else {
      lVar26 = *(long *)(*(long *)(*(long *)(lVar48 + 0xd8) + (long)iVar51 * 8) + 0x38);
joined_r0x02426d0c:
      if (lVar26 != 0) {
code_r0x02426d10:
        param_1[0x20] = lVar26;
      }
    }
  }
  if (*(char *)(param_3 + 0x147) == '\0') goto code_r0x02426d8c;
  iVar51 = *(int *)(param_3 + 0x148);
  if (iVar51 < 0) {
    if (*(long *)(lVar48 + 0x78) == 0) goto code_r0x02426d8c;
    lVar26 = *(long *)(lVar48 + 0x508);
    lVar30 = *(long *)(lVar48 + 0x78) + (long)(int)(iVar51 << 5 ^ 0xffffffe0) + 0x20;
    if ((((lVar26 == 0) || (*(int *)(lVar26 + 0xb0) < 1)) ||
        (lVar26 = Aska::AsfHandler::QuickSearch(char const*) const(lVar26,lVar30), lVar26 == 0)) ||
       (lVar26 = *(long *)(lVar26 + 0x38), lVar26 == 0)) {
      lVar26 = Aska::AsfHandler::QuickSearchByNameFromExternalLinkList(char const*) const(lVar48,lVar30);
      goto joined_r0x02426d84;
    }
  }
  else {
    lVar26 = *(long *)(*(long *)(*(long *)(lVar48 + 0xd8) + (long)iVar51 * 8) + 0x38);
joined_r0x02426d84:
    if (lVar26 == 0) goto code_r0x02426d8c;
  }
  param_1[0x21] = lVar26;
code_r0x02426d8c:
  *(undefined1 *)(param_1 + 0x1b) = uVar21;
  return 1;
}

// ==== Aska::ArticulatedDynamicsManager::CalcBufferSize(int, int, int, int, int)
// vaddr 0x2326da0 | ghidra 0x2426da0 | size 68 | symbol _ZN4Aska26ArticulatedDynamicsManager14CalcBufferSizeEiiiii | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska26ArticulatedDynamicsManager14CalcBufferSizeEiiiii
               (undefined8 param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  return (((long)param_3 * 0x50 | 3U) + (long)param_6 +
          (((long)(param_2 + 1) << 9 | 0xfU) + (long)param_6 * 0xa8 & 0xfffffffffffffff0) &
         0xfffffffffffffffc) + ((long)param_5 + (long)param_4) * 8;
}

// ==== Aska::ArticulatedDynamicsManager::Simulate(float, unsigned int, float)
// vaddr 0x2326de4 | ghidra 0x2426de4 | size 232 | symbol _ZN4Aska26ArticulatedDynamicsManager8SimulateEfjf | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska26ArticulatedDynamicsManager8SimulateEfjf
          (float param_1,undefined8 param_2,long param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  
  if (*(char *)(param_3 + 0xe1) != '\0') {
    iVar2 = *(int *)(param_3 + 0xec);
    fVar4 = *(float *)PTR__ZN4Aska30ArticulatedDynamicsManagerBase9m_fBaseDtE_02cba288;
    iVar1 = iVar2;
    if (iVar2 < 3) {
      iVar1 = 2;
    }
    if (*(char *)(param_3 + 0x122) == '\0') {
      iVar1 = iVar2;
    }
    if ((((*PTR__ZN4Aska30ArticulatedDynamicsManagerBase8m_bDtDivE_02cbf9f8 != '\0') &&
         (*(char *)(param_3 + 0xdd) != '\0')) && (*(char *)(param_3 + 0xdc) == '\0')) &&
       (iVar1 = iVar1 * (int)(param_1 / fVar4), iVar1 < 2)) {
      iVar1 = 1;
    }
    fVar3 = fVar4;
    if (iVar1 < 2) {
      fVar3 = param_1;
    }
    if (*(char *)(param_3 + 0xdc) == '\0') {
      if (fVar4 <= fVar3) {
        fVar4 = fVar3 / fVar4;
      }
      else {
        fVar4 = fVar4 / fVar3 + 0.5;
      }
      iVar2 = (int)fVar4;
      if (iVar2 < 2) {
        iVar2 = 1;
      }
    }
    else {
      iVar2 = 1;
    }
    void Aska::ArticulatedDynamicsManager::SimulateMain<Aska::ArticulatedDynamicsManager>(Aska::ArticulatedDynamicsManager*, Aska::ADMJoint*, Aska::ADMJoint*, unsigned int, int, int, unsigned int, float, float, unsigned int, float)(fVar3,1.0 / fVar3,param_2,param_3,*(long *)(param_3 + 0x70),
                    *(long *)(param_3 + 0x70) + (long)*(short *)(param_3 + 0x60) * 0x1c0,
                    (long)*(short *)(param_3 + 0x60),0,iVar1,iVar2,param_4);
    return 1;
  }
  return 0;
}

// ==== Aska::ArticulatedDynamicsManager::Clone(Aska::IAnimatable const*)
// vaddr 0x2327254 | ghidra 0x2427254 | size 4 | symbol _ZN4Aska26ArticulatedDynamicsManager5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska26ArticulatedDynamicsManager5CloneEPKNS_11IAnimatableE(void)

{
  (*(code *)PTR__ZN4Aska11IAnimatable5CloneEPKS0__02c96b68)();
  return;
}

// ==== Aska::ArticulatedDynamicsManager::CreateClone(Aska::IAnimatable const*)
// vaddr 0x2327258 | ghidra 0x2427258 | size 420 | symbol _ZN4Aska26ArticulatedDynamicsManager11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska26ArticulatedDynamicsManager11CreateCloneEPKNS_11IAnimatableE
                 (long param_1,undefined8 param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  undefined *puVar5;
  long *plVar6;
  ulong uVar7;
  long lVar8;
  
  plVar6 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x1c0,PTR__ZSt7nothrow_02cb9a80);
  if (plVar6 != (long *)0x0) {
    lVar8 = *(long *)(param_1 + 0x20);
    *(undefined4 *)(plVar6 + 5) = 0;
    puVar1 = PTR__ZTVN4Aska30ArticulatedDynamicsManagerBaseE_02cc0c60 + 0x10;
    puVar2 = PTR__ZTVN4Aska30ArticulatedDynamicsManagerBase14SimulateNotifyE_02cbb950 + 0x10;
    plVar6[0x12] = 0;
    *(undefined2 *)((long)plVar6 + 0x9a) = 0;
    *(undefined4 *)(plVar6 + 0x11) = 0;
    plVar6[0x10] = 0;
    *(undefined4 *)(plVar6 + 0x16) = 0;
    plVar6[0x14] = 0;
    plVar6[0x15] = 0;
    *(undefined8 *)((long)plVar6 + 0xd5) = 0;
    plVar6[0x1a] = 0;
    *(undefined1 *)((long)plVar6 + 0xdf) = 0;
    *(undefined4 *)((long)plVar6 + 0xe2) = 0;
    *(undefined2 *)(plVar6 + 0x24) = 0;
    *(undefined1 *)((long)plVar6 + 0x122) = 0;
    *(undefined4 *)((long)plVar6 + 0xf4) = 0x44750000;
    *(undefined4 *)(plVar6 + 0x1f) = 0x3c88ab7c;
    plVar6[0x20] = 0;
    plVar6[0x21] = 0;
    *(undefined4 *)((long)plVar6 + 0x134) = 0;
    *plVar6 = (long)puVar1;
    plVar6[6] = (long)puVar2;
    puVar1 = PTR__ZTVN4Aska26DefaultLandScapeConstraintE_02cbb230 + 0x10;
    plVar6[2] = 0;
    plVar6[1] = 0;
    *(undefined1 *)(plVar6 + 3) = 1;
    plVar6[9] = 0;
    plVar6[8] = 0;
    plVar6[0xd] = 0;
    plVar6[0xc] = 0;
    plVar6[0xf] = 0;
    plVar6[0xe] = 0;
    *(undefined1 *)((long)plVar6 + 0xdd) = 1;
    *(undefined1 *)(plVar6 + 0x1c) = 1;
    *(undefined1 *)((long)plVar6 + 0xe1) = 1;
    *(undefined4 *)(plVar6 + 0x1d) = 0;
    *(undefined4 *)((long)plVar6 + 0xec) = 1;
    *(undefined8 *)((long)plVar6 + 0x124) = 0;
    *(undefined8 *)((long)plVar6 + 300) = 0;
    plVar6[0x27] = (long)puVar1;
    *(undefined4 *)(plVar6 + 0x32) = 0x100;
    puVar2 = PTR__ZTVN4Aska21DynamicsPrimitiveListE_02cb7d10;
    *(undefined1 *)((long)plVar6 + 0x194) = 1;
    puVar5 = PTR__ZTVN4Aska24DynamicsPrimitiveElementE_02cbbef0;
    plVar6[0x2d] = (long)(plVar6 + 0x2c);
    plVar6[0x2e] = (long)(plVar6 + 0x2c);
    uVar4 = *PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_bDefaultEnableWorldE_02cc3dd8;
    uVar3 = *(undefined4 *)
             PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_uiDefaultDynamicsIDE_02cc08d0;
    puVar1 = PTR__ZTVN4Aska26ArticulatedDynamicsManagerE_02cbdd58 + 0x10;
    *(undefined4 *)(plVar6 + 0x28) = 0;
    plVar6[0x29] = 0;
    plVar6[0x2a] = 0;
    *(undefined1 *)((long)plVar6 + 0x196) = 0;
    plVar6[0x2f] = 0;
    plVar6[0x30] = 0;
    plVar6[0x31] = 0;
    plVar6[0x33] = 0;
    *(undefined4 *)(plVar6 + 0x34) = 0;
    plVar6[0x2c] = (long)(puVar5 + 0x10);
    plVar6[0x2b] = (long)(puVar2 + 0x10);
    plVar6[0x35] = 0;
    plVar6[0x36] = 0;
    plVar6[4] = lVar8;
    *(undefined1 *)((long)plVar6 + 0xde) = uVar4;
    *(undefined4 *)((long)plVar6 + 0x9c) = uVar3;
    *plVar6 = (long)puVar1;
    uVar7 = Aska::IAnimatable::Clone(Aska::IAnimatable const*)(plVar6,param_2);
    if ((uVar7 & 1) == 0) {
      (**(code **)(*plVar6 + 8))(plVar6);
      plVar6 = (long *)0x0;
    }
  }
  return plVar6;
}

// ==== Aska::ArticulatedDynamicsManager::Get(unsigned long, void*) const
// vaddr 0x23273fc | ghidra 0x24273fc | size 344 | symbol _ZNK4Aska26ArticulatedDynamicsManager3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska26ArticulatedDynamicsManager3GetEmPv(long param_1,ulong param_2,byte *param_3)

{
  uint uVar1;
  long *plVar2;
  ulong uVar3;
  byte bVar4;
  undefined4 uVar5;
  
  if ((param_2 & 0xffff00000000) != 0) {
    return 0;
  }
  switch((uint)param_2 & 0xffff) {
  case 0xf:
    bVar4 = *(byte *)(param_1 + 0xdb);
    break;
  case 0x10:
    bVar4 = *(byte *)(param_1 + 0xdc);
    break;
  default:
    uVar1 = (uint)(param_2 >> 0x10) & 0xff;
    if (((int)uVar1 < (int)*(short *)(param_1 + 0x60)) &&
       (plVar2 = (long *)(*(long *)(param_1 + 0x70) + (ulong)uVar1 * 0x1c0),
       uVar3 = (**(code **)(*plVar2 + 0x28))(plVar2,param_2,param_3), (uVar3 & 1) != 0)) {
      return 1;
    }
    if ((int)*(short *)(param_1 + 0x66) <= (int)uVar1) {
      return 0;
    }
    plVar2 = *(long **)(*(long *)(param_1 + 0x150) + (ulong)uVar1 * 8);
    if (plVar2 != (long *)0x0) {
      uVar3 = (**(code **)(*plVar2 + 0x28))(plVar2,param_2,param_3);
      if ((uVar3 & 1) != 0) {
        return 1;
      }
      return 0;
    }
    return 0;
  case 0x21:
    bVar4 = *(byte *)(param_1 + 0x9b);
    break;
  case 0x22:
    bVar4 = *(byte *)(param_1 + 0x9a) & 1;
    break;
  case 0x23:
    bVar4 = *(byte *)(param_1 + 0x9a) >> 1 & 1;
    break;
  case 0x24:
    bVar4 = *PTR__ZN4Aska30ArticulatedDynamicsManagerBase8m_bDtDivE_02cbf9f8;
    break;
  case 0x25:
    uVar5 = *(undefined4 *)(param_1 + 0xec);
    goto code_r0x02427530;
  case 0x26:
    *(undefined4 *)param_3 = *(undefined4 *)(param_1 + 0x40);
    *(undefined4 *)(param_3 + 4) = *(undefined4 *)(param_1 + 0x44);
    *(undefined4 *)(param_3 + 8) = *(undefined4 *)(param_1 + 0x48);
    *(undefined4 *)(param_3 + 0xc) = *(undefined4 *)(param_1 + 0x4c);
    return 1;
  case 0x27:
    uVar5 = *(undefined4 *)(param_1 + 0xf4);
    goto code_r0x02427530;
  case 0x28:
    uVar5 = *(undefined4 *)(param_1 + 0xf0);
code_r0x02427530:
    *(undefined4 *)param_3 = uVar5;
    return 1;
  case 0x45:
    bVar4 = *(byte *)(param_1 + 0xda);
  }
  *param_3 = bVar4;
  return 1;
}

// ==== Aska::ArticulatedDynamicsManager::Set(unsigned long, void const*)
// vaddr 0x2327554 | ghidra 0x2427554 | size 584 | symbol _ZN4Aska26ArticulatedDynamicsManager3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska26ArticulatedDynamicsManager3SetEmPKv(long param_1,ulong param_2,byte *param_3)

{
  uint uVar1;
  byte bVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  byte bVar6;
  long *plVar7;
  ulong uVar8;
  long lVar9;
  long lVar10;
  undefined4 uVar11;
  
  if ((param_2 & 0xffff00000000) != 0) {
    return 0;
  }
  switch((uint)param_2 & 0xffff) {
  case 0xf:
    *(byte *)(param_1 + 0xdb) = *param_3;
    break;
  case 0x10:
    *(byte *)(param_1 + 0xdc) = *param_3;
    break;
  default:
    uVar1 = (uint)(param_2 >> 0x10) & 0xff;
    if (((int)*(short *)(param_1 + 0x60) <= (int)uVar1) ||
       (plVar7 = (long *)(*(long *)(param_1 + 0x70) + (ulong)uVar1 * 0x1c0),
       uVar8 = (**(code **)(*plVar7 + 0x30))(plVar7,param_2,param_3), (uVar8 & 1) == 0)) {
      if ((int)*(short *)(param_1 + 0x66) <= (int)uVar1) {
        return 0;
      }
      plVar7 = *(long **)(*(long *)(param_1 + 0x150) + (ulong)uVar1 * 8);
      if (plVar7 == (long *)0x0) {
        return 0;
      }
      uVar8 = (**(code **)(*plVar7 + 0x30))(plVar7,param_2,param_3);
      if ((uVar8 & 1) == 0) {
        return 0;
      }
    }
    break;
  case 0x21:
    bVar6 = *param_3;
    if (*(byte *)(param_1 + 0x9b) != bVar6) {
      *(byte *)(param_1 + 0x9b) = bVar6;
      if (0 < (long)*(short *)(param_1 + 0x60)) {
        uVar11 = 0x3f800000;
        if (bVar6 != 0) {
          uVar11 = 0x3f000000;
        }
        lVar9 = ((long)*(short *)(param_1 + 0x60) & 0xffffffffU) - 1;
        *(undefined4 *)(*(long *)(param_1 + 0x70) + 0x184) = uVar11;
        if (lVar9 != 0) {
          lVar10 = 0x344;
          do {
            lVar9 = lVar9 + -1;
            uVar11 = 0x3f800000;
            if (*(char *)(param_1 + 0x9b) != '\0') {
              uVar11 = 0x3f000000;
            }
            *(undefined4 *)(*(long *)(param_1 + 0x70) + lVar10) = uVar11;
            lVar10 = lVar10 + 0x1c0;
          } while (lVar9 != 0);
          return 1;
        }
      }
    }
    break;
  case 0x22:
    bVar6 = *(byte *)(param_1 + 0x9a) | 1;
    if (*param_3 == 0) {
      bVar6 = *(byte *)(param_1 + 0x9a) & 0xfe;
    }
    *(byte *)(param_1 + 0x9a) = bVar6;
    break;
  case 0x23:
    bVar6 = *(byte *)(param_1 + 0x9a);
    if ((bVar6 >> 1 & 1) != *param_3) {
      bVar2 = bVar6 | 2;
      if (*param_3 == 0) {
        bVar2 = bVar6 & 0xfd;
      }
      *(byte *)(param_1 + 0x9a) = bVar2;
      if (*(long *)(param_1 + 0x1a8) != 0) {
        Aska::DynamicsHandler::SetDirtyChangeParameter()();
        return 1;
      }
    }
    break;
  case 0x24:
    *PTR__ZN4Aska30ArticulatedDynamicsManagerBase8m_bDtDivE_02cbf9f8 = *param_3;
    break;
  case 0x25:
    *(undefined4 *)(param_1 + 0xec) = *(undefined4 *)param_3;
    break;
  case 0x26:
    uVar11 = *(undefined4 *)param_3;
    *(undefined4 *)(param_1 + 0x40) = uVar11;
    uVar3 = *(undefined4 *)(param_3 + 4);
    *(undefined4 *)(param_1 + 0x44) = uVar3;
    uVar4 = *(undefined4 *)(param_3 + 8);
    *(undefined4 *)(param_1 + 0x48) = uVar4;
    uVar5 = *(undefined4 *)(param_3 + 0xc);
    *(undefined4 *)(param_1 + 0x54) = uVar3;
    *(undefined4 *)(param_1 + 0x58) = uVar4;
    *(undefined4 *)(param_1 + 0x4c) = uVar5;
    *(undefined4 *)(param_1 + 0x50) = uVar11;
    *(undefined4 *)(param_1 + 0x5c) = uVar5;
    break;
  case 0x27:
    *(undefined4 *)(param_1 + 0xf4) = *(undefined4 *)param_3;
    break;
  case 0x28:
    *(undefined4 *)(param_1 + 0xf0) = *(undefined4 *)param_3;
    break;
  case 0x45:
    *(byte *)(param_1 + 0xda) = *param_3;
  }
  return 1;
}

// ==== Aska::ArticulatedDynamicsManager::~ArticulatedDynamicsManager()
// vaddr 0x232779c | ghidra 0x242779c | size 24 | symbol _ZN4Aska26ArticulatedDynamicsManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska26ArticulatedDynamicsManagerD0Ev(undefined8 param_1)

{
  Aska::ArticulatedDynamicsManagerBase::~ArticulatedDynamicsManagerBase()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::ArticulatedDynamicsManager::GetClassID(int) const
// vaddr 0x23277b4 | ghidra 0x24277b4 | size 80 | symbol _ZNK4Aska26ArticulatedDynamicsManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska26ArticulatedDynamicsManager10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf000f171f172;
  }
  uVar2 = 0xf000f001;
  if (param_2 == 1) {
    return 0xf000f171;
  }
  if (param_2 != 3) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf001f032;
  if (param_2 != 2) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::ArticulatedDynamicsManager::CallSimulate(float, unsigned int, float)
// vaddr 0x2327804 | ghidra 0x2427804 | size 4 | symbol _ZN4Aska26ArticulatedDynamicsManager12CallSimulateEfjf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska26ArticulatedDynamicsManager12CallSimulateEfjf(void)

{
  (*(code *)PTR__ZN4Aska26ArticulatedDynamicsManager8SimulateEfjf_02cad9d0)();
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

// ==== Aska::ADMJoint::ExternalForce(float, float, float, Aska::Vector const*, Aska::ADM_CALC_DATA*, bool)
// vaddr 0x2329698 | ghidra 0x2429698 | size 300 | symbol _ZN4Aska8ADMJoint13ExternalForceEfffPKNS_6VectorEPNS_13ADM_CALC_DATAEb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8ADMJoint13ExternalForceEfffPKNS_6VectorEPNS_13ADM_CALC_DATAEb
               (float param_1,float param_2,float param_3,long param_4,float *param_5,long param_6,
               uint param_7)

{
  undefined4 uVar1;
  undefined4 uVar2;
  byte bVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  if ((*(byte *)(param_4 + 0x19c) & 1) == 0) {
    bVar3 = *(byte *)(param_4 + 0x19d);
    fVar5 = 0.0;
    fVar4 = 0.0;
    if ((bVar3 & 1) != 0) {
      fVar4 = 0.0 - param_3;
    }
    if ((((bVar3 >> 1 & 1) == 0) && ((param_7 & 1) == 0)) || (*(float *)(param_4 + 0x180) <= 0.0)) {
      fVar6 = 0.0;
    }
    else {
      if ((param_7 & 1) == 0) {
        if ((*(char *)(param_4 + 0x19b) == '\0') || (0.0 <= *(float *)(param_4 + 0x54))) {
          fVar6 = *(float *)(param_4 + 0x178);
        }
        else {
          fVar6 = *(float *)(param_4 + 0x17c);
        }
      }
      else {
        fVar6 = 1.0;
      }
      fVar6 = fVar6 / *(float *)(param_4 + 0x180);
      if (param_2 <= fVar6) {
        fVar6 = param_2;
      }
      fVar5 = 0.0 - *(float *)(param_4 + 0x50) * fVar6;
      fVar4 = fVar4 - *(float *)(param_4 + 0x54) * fVar6;
      fVar6 = 0.0 - fVar6 * *(float *)(param_4 + 0x58);
    }
    fVar7 = fVar5 * param_1 + *(float *)(param_4 + 0x50);
    fVar5 = fVar4 * param_1 + *(float *)(param_4 + 0x54);
    *(float *)(param_4 + 0x50) = fVar7;
    *(float *)(param_4 + 0x54) = fVar5;
    fVar4 = fVar6 * param_1 + *(float *)(param_4 + 0x58);
    *(float *)(param_4 + 0x58) = fVar4;
    fVar6 = *(float *)(param_4 + 0x10) + fVar7 * param_1;
    fVar5 = *(float *)(param_4 + 0x14) + fVar5 * param_1;
    fVar4 = *(float *)(param_4 + 0x18) + fVar4 * param_1;
    if ((bVar3 >> 6 & 1) != 0) {
      fVar6 = fVar6 + *param_5 * param_1;
      fVar5 = fVar5 + param_5[1] * param_1;
      fVar4 = fVar4 + param_5[2] * param_1;
    }
    *(float *)(param_4 + 0x10) = fVar6;
    *(float *)(param_4 + 0x14) = fVar5;
    *(float *)(param_4 + 0x18) = fVar4;
  }
  else {
    uVar1 = *(undefined4 *)(param_6 + 0x1c);
    uVar2 = *(undefined4 *)(param_6 + 0x2c);
    *(undefined4 *)(param_4 + 0x10) = *(undefined4 *)(param_6 + 0xc);
    *(undefined4 *)(param_4 + 0x14) = uVar1;
    *(undefined4 *)(param_4 + 0x18) = uVar2;
  }
  *(undefined4 *)(param_4 + 0x1c) = 0x3f800000;
  return;
}

// ==== Aska::ArticulatedDynamicsManagerMP::Constraint(Aska::LinkListParam*, int)
// vaddr 0x232ae04 | ghidra 0x242ae04 | size 216 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP10ConstraintEPNS_13LinkListParamEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28ArticulatedDynamicsManagerMP10ConstraintEPNS_13LinkListParamEi
               (ulong param_1,int param_2)

{
  ulong uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  if (0 < param_2) {
    uVar1 = param_1 + (long)param_2 * 0x50;
    do {
      fVar5 = *(float *)(param_1 + 0x40);
      fVar3 = *(float *)(param_1 + 0x10) * *(float *)(param_1 + 0x10) +
              *(float *)(param_1 + 0x14) * *(float *)(param_1 + 0x14) +
              *(float *)(param_1 + 0x18) * *(float *)(param_1 + 0x18);
      fVar2 = SQRT(fVar3);
      if (NAN(fVar2)) {
        fVar2 = (float)sqrtf(fVar3);
      }
      fVar5 = fVar5 / fVar2;
      fVar3 = fVar5 * *(float *)(param_1 + 0x10);
      fVar4 = fVar5 * *(float *)(param_1 + 0x14);
      fVar5 = fVar5 * *(float *)(param_1 + 0x18);
      fVar2 = (fVar3 * *(float *)(param_1 + 0x20) + fVar4 * *(float *)(param_1 + 0x24) +
              fVar5 * *(float *)(param_1 + 0x28)) /
              (*(float *)(param_1 + 0x40) * *(float *)(param_1 + 0x40));
      *(float *)(param_1 + 0x10) = fVar3;
      *(float *)(param_1 + 0x14) = fVar4;
      *(float *)(param_1 + 0x18) = fVar5;
      *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) - fVar3 * fVar2;
      *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) - fVar4 * fVar2;
      *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) - fVar5 * fVar2;
      param_1 = param_1 + 0x50;
    } while (param_1 < uVar1);
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerMP::Attach(Aska::ADMHandler const*, Aska::AFF::AsfArticulatedDynamicsManager const*, bool)
// vaddr 0x232aedc | ghidra 0x242aedc | size 3344 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP6AttachEPKNS_10ADMHandlerEPKNS_3AFF29AsfArticulatedDynamicsManagerEb | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska28ArticulatedDynamicsManagerMP6AttachEPKNS_10ADMHandlerEPKNS_3AFF29AsfArticulatedDynamicsManagerEb
          (long *param_1,long param_2,long param_3,ulong param_4)

{
  bool bVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  undefined *puVar5;
  int *piVar6;
  long lVar7;
  long lVar8;
  undefined1 *puVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  byte bVar19;
  ushort uVar20;
  ushort uVar21;
  undefined8 uVar22;
  byte bVar23;
  int iVar24;
  long lVar25;
  ulong uVar26;
  long lVar27;
  long lVar28;
  undefined4 *puVar29;
  long lVar30;
  long lVar31;
  long lVar32;
  ushort *puVar33;
  ulong uVar34;
  undefined8 uVar35;
  int *piVar36;
  undefined2 *puVar37;
  byte *pbVar38;
  undefined2 *puVar39;
  undefined2 *puVar40;
  undefined2 *puVar41;
  undefined2 *puVar42;
  byte bVar43;
  byte *pbVar44;
  undefined4 *puVar45;
  long lVar46;
  long lVar47;
  short sVar48;
  ulong uVar49;
  ulong uVar50;
  ulong uVar51;
  int iVar52;
  ulong uVar53;
  undefined8 *puVar54;
  undefined4 *puVar55;
  long lVar56;
  float fVar57;
  int iVar58;
  int iVar59;
  int iVar60;
  int iVar61;
  int iVar62;
  int iVar63;
  int iVar64;
  undefined2 uVar65;
  long lStack_68;
  
  if (param_3 == 0) {
    if (*(char *)((long)param_1 + 0xe5) != '\0') {
      return 1;
    }
    param_3 = param_1[0x36];
    if (param_3 == 0) {
      return 0;
    }
code_r0x0242af44:
    if (param_2 != 0) goto code_r0x0242af48;
code_r0x0242af28:
    lVar56 = param_1[0x35];
    if (param_1[0x35] == 0) {
      return 0;
    }
  }
  else {
    param_1[0x36] = param_3;
    if ((*(byte *)(param_3 + 0x118) >> 2 & 1) == 0) goto code_r0x0242af44;
    *(undefined1 *)((long)param_1 + 0xe5) = 1;
    if (param_2 == 0) goto code_r0x0242af28;
code_r0x0242af48:
    param_1[0x35] = param_2;
    lVar56 = param_2;
  }
  lVar56 = *(long *)(lVar56 + 0x60);
  *(int *)((long)param_1 + 0x8c) =
       (*(int *)PTR__ZN4Aska30ArticulatedDynamicsManagerBase10m_uiExSeedE_02cc4440 +
       *(int *)PTR__ZN4Aska30ArticulatedDynamicsManagerBase12m_uiBaseSeedE_02cc3f60) * 0x19660d +
       0x78dde6be;
  uVar10 = *(uint *)(param_3 + 0x13c);
  uVar11 = *(uint *)(param_3 + 300);
  uVar12 = *(uint *)(param_3 + 0x130);
  uVar13 = *(uint *)(param_3 + 0x138);
  uVar14 = *(uint *)(param_3 + 0x140);
  piVar6 = (int *)((ulong)*(uint *)(param_3 + 0x128) + param_3);
  if (*(char *)(param_3 + 0x144) != '\0') {
    (**(code **)(*param_1 + 0x60))(param_1);
  }
  uVar20 = *(ushort *)(param_3 + 0x11a);
  uVar51 = (ulong)uVar20;
  if (param_2 == 0) {
code_r0x0242aff0:
    if (uVar20 != 0) goto code_r0x0242aff4;
    iVar52 = 0;
    iVar24 = 0;
    bVar1 = true;
  }
  else {
    if (uVar20 == 0) {
      return 0;
    }
    if ((param_4 & 1) == 0) {
      lVar32 = 0;
      piVar36 = piVar6;
      do {
        if (*piVar36 < 0) {
          return 1;
        }
        lVar32 = lVar32 + 1;
        piVar36 = piVar36 + 0xc;
      } while (lVar32 < (long)uVar51);
      goto code_r0x0242aff0;
    }
code_r0x0242aff4:
    lVar32 = 0;
    iVar52 = 0;
    piVar36 = piVar6;
    do {
      if (((*(byte *)((long)piVar36 + 0x1f) & 1) != 0) &&
         (lVar25 = Aska::ArticulatedDynamicsManagerBase::SearchOrginalData(Aska::AsfHandler*, Aska::AsfHandler*, int)(param_1,lVar56,0,*piVar36), lVar25 != 0)) {
        if (*(long *)(lVar25 + 0xf0) == 0) {
          return 1;
        }
        if (*(long *)(*(long *)(lVar25 + 0xf0) + 0xe8) == 0) {
          return 1;
        }
        iVar52 = iVar52 + 1;
      }
      lVar32 = lVar32 + 1;
      piVar36 = piVar36 + 0xc;
    } while (lVar32 < (long)uVar51);
    if (uVar20 < 8) {
      lVar32 = 0;
code_r0x0242b128:
      iVar24 = 0;
code_r0x0242b12c:
      lVar25 = uVar51 - lVar32;
      puVar33 = (ushort *)((long)piVar6 + lVar32 * 0x30 + 0x1e);
      do {
        lVar25 = lVar25 + -1;
        if ((*puVar33 & 0x81) == 0x80) {
          iVar24 = iVar24 + 1;
        }
        puVar33 = puVar33 + 0x18;
      } while (lVar25 != 0);
    }
    else {
      lVar32 = uVar51 - (uVar51 & 7);
      if (lVar32 == 0) goto code_r0x0242b128;
      puVar37 = (undefined2 *)((long)piVar6 + 0xde);
      iVar24 = 0;
      iVar58 = 0;
      iVar59 = 0;
      iVar60 = 0;
      iVar61 = 0;
      iVar62 = 0;
      iVar63 = 0;
      iVar64 = 0;
      lVar25 = lVar32;
      do {
        puVar39 = puVar37 + -0x60;
        uVar65 = *puVar37;
        puVar40 = puVar37 + -0x48;
        puVar2 = puVar37 + 0x18;
        puVar41 = puVar37 + -0x30;
        puVar3 = puVar37 + 0x30;
        puVar42 = puVar37 + -0x18;
        puVar4 = puVar37 + 0x48;
        lVar25 = lVar25 + -8;
        puVar37 = puVar37 + 0xc0;
        uVar26 = CONCAT26(*puVar4,CONCAT24(*puVar3,CONCAT22(*puVar2,uVar65))) & 0x81008100810081;
        uVar49 = CONCAT26(*puVar42,CONCAT24(*puVar41,CONCAT22(*puVar40,*puVar39))) &
                 0x81008100810081;
        iVar61 = iVar61 + (uint)(-((short)uVar26 == 0x80) & 1);
        iVar62 = iVar62 + (uint)(-((short)(uVar26 >> 0x10) == 0x80) & 1);
        iVar63 = iVar63 + (uint)(-((short)(uVar26 >> 0x20) == 0x80) & 1);
        iVar64 = iVar64 + (uint)(-((short)(uVar26 >> 0x30) == 0x80) & 1);
        iVar24 = iVar24 + (uint)(-((short)uVar49 == 0x80) & 1);
        iVar58 = iVar58 + (uint)(-((short)(uVar49 >> 0x10) == 0x80) & 1);
        iVar59 = iVar59 + (uint)(-((short)(uVar49 >> 0x20) == 0x80) & 1);
        iVar60 = iVar60 + (uint)(-((short)(uVar49 >> 0x30) == 0x80) & 1);
      } while (lVar25 != 0);
      iVar24 = iVar61 + iVar24 + iVar62 + iVar58 + iVar63 + iVar59 + iVar64 + iVar60;
      if ((uVar20 & 7) != 0) goto code_r0x0242b12c;
    }
    bVar1 = false;
  }
  *(int *)(param_1 + 0x11) = iVar24;
  uVar21 = *(ushort *)(param_3 + 0x124);
  uVar50 = (ulong)uVar21;
  bVar19 = *(byte *)(param_3 + 0x126);
  uVar49 = (ulong)bVar19;
  bVar43 = *(byte *)(param_3 + 0x127);
  uVar53 = (ulong)bVar43;
  uVar26 = (**(code **)(*param_1 + 0x78))(param_1,uVar51,uVar50,uVar49,uVar53);
  if (uVar26 == 0) {
    return 1;
  }
  if (param_1[0xd] == 0) {
    uVar34 = param_1[0x10];
code_r0x0242b1dc:
    if (uVar34 == 0) goto code_r0x0242b1f8;
    lVar32 = param_1[0xd];
    uVar35 = _UNK_027dbb30;
    uVar22 = _UNK_027dbb38;
  }
  else {
    Aska::ArticulatedDynamicsManagerBase::ReserveJointParamsForUpdate()(param_1);
    uVar34 = param_1[0x10];
    if (uVar26 <= uVar34) goto code_r0x0242b1dc;
    if (param_1[0xd] != 0) {
      operator delete[](void*)();
    }
    param_1[0x10] = 0;
code_r0x0242b1f8:
    lVar32 = operator new[](unsigned long, unsigned long, bool)(uVar26,0x10,1);
    param_1[0xd] = lVar32;
    param_1[0x10] = uVar26;
    uVar35 = _UNK_027dbb30;
    uVar22 = _UNK_027dbb38;
  }
  _UNK_027dbb30 = uVar35;
  _UNK_027dbb38 = uVar22;
  if (lVar32 == 0) {
    param_1[0x10] = 0;
    return 1;
  }
  puVar55 = (undefined4 *)((ulong)uVar12 + param_3);
  lVar28 = (ulong)uVar13 + param_3;
  uVar15 = *(undefined4 *)(param_3 + 0x114);
  puVar5 = PTR__ZTVN4Aska8ADMJointE_02cbdbb0 + 0x10;
  uVar26 = lVar32 + (uVar51 + 1) * 0x1c0 + 0xf & 0xfffffffffffffff0;
  lVar7 = (ulong)uVar10 + param_3;
  lVar8 = (ulong)uVar14 + param_3;
  lVar25 = 0x1bc;
  param_1[0x1a] = uVar26;
  lStack_68 = uVar26 + (uint)((int)(uVar51 + 1) << 6);
  *(undefined4 *)(param_1 + 0x1e) = uVar15;
  param_1[0xe] = lVar32;
  uVar26 = uVar51;
  while( true ) {
    puVar9 = (undefined1 *)(lVar32 + lVar25);
    *(undefined **)(puVar9 + -0x1bc) = puVar5;
    *(undefined8 *)(puVar9 + -0x6c) = 0;
    *(undefined4 *)(puVar9 + -100) = 0;
    *(undefined8 *)(puVar9 + -0x5c) = 0;
    *(undefined4 *)(puVar9 + -0x54) = 0;
    *(undefined4 *)(puVar9 + -0x48) = 0;
    *(undefined8 *)(puVar9 + -0x2c) = 0;
    *(undefined2 *)(puVar9 + -0x22) = 1;
    *(undefined8 *)(puVar9 + -0xc) = 0;
    *(undefined8 *)(puVar9 + -0x114) = uVar22;
    *(undefined8 *)(puVar9 + -0x11c) = uVar35;
    *puVar9 = 0;
    if (uVar26 == 0) break;
    lVar32 = param_1[0xe];
    uVar26 = uVar26 - 1;
    lVar25 = lVar25 + 0x1c0;
  }
  *(ushort *)(param_1 + 0xc) = uVar20;
  uVar15 = *(undefined4 *)(param_3 + 0x100);
  lVar32 = param_1[0xe];
  *(undefined4 *)(param_1 + 8) = uVar15;
  uVar16 = *(undefined4 *)(param_3 + 0x104);
  *(undefined4 *)((long)param_1 + 0x44) = uVar16;
  uVar17 = *(undefined4 *)(param_3 + 0x108);
  *(undefined4 *)(param_1 + 9) = uVar17;
  uVar18 = *(undefined4 *)(param_3 + 0x10c);
  *(undefined4 *)((long)param_1 + 0x54) = uVar16;
  *(undefined4 *)(param_1 + 0xb) = uVar17;
  *(undefined4 *)((long)param_1 + 0x4c) = uVar18;
  *(undefined4 *)(param_1 + 10) = uVar15;
  *(undefined4 *)((long)param_1 + 0x5c) = uVar18;
  *(undefined4 *)((long)param_1 + 0xf4) = *(undefined4 *)(param_3 + 0x110);
  if (bVar1) {
    iVar24 = 0;
  }
  else {
    iVar24 = 0;
    puVar54 = (undefined8 *)param_1[0x1a];
    lVar27 = 0;
    lVar25 = 0;
    pbVar38 = (byte *)(piVar6 + 8);
    lVar30 = lVar8;
    do {
      lVar46 = Aska::ArticulatedDynamicsManagerBase::SearchOrginalData(Aska::AsfHandler*, Aska::AsfHandler*, int)(param_1,lVar56,0,*(int *)(pbVar38 + -0x20));
      if (lVar46 == 0) {
        return 1;
      }
      lVar47 = lVar32 + lVar27;
      *(long *)(lVar47 + 0x1b0) = lVar46 + 0x30;
      uVar26 = Aska::ADMJoint::InitCalcData()(lVar47);
      if ((uVar26 & 1) == 0) goto code_r0x0242b8a4;
      uVar35 = *(undefined8 *)(lVar46 + 0x40);
      puVar54[1] = *(undefined8 *)(lVar46 + 0x48);
      *puVar54 = uVar35;
      uVar35 = *(undefined8 *)(lVar46 + 0x50);
      puVar54[3] = *(undefined8 *)(lVar46 + 0x58);
      puVar54[2] = uVar35;
      uVar35 = *(undefined8 *)(lVar46 + 0x60);
      puVar54[5] = *(undefined8 *)(lVar46 + 0x68);
      puVar54[4] = uVar35;
      uVar35 = *(undefined8 *)(lVar46 + 0x70);
      puVar54[7] = *(undefined8 *)(lVar46 + 0x78);
      puVar54[6] = uVar35;
      *(byte *)(lVar47 + 0x199) = pbVar38[-1] & 1;
      *(byte *)(lVar47 + 0x19c) = pbVar38[-2] & 1;
      *(byte *)(lVar47 + 0x19d) =
           ((byte)*(undefined2 *)(pbVar38 + -2) & 0xf0 | (*pbVar38 != 0) << 3) ^ 0x80;
      fVar57 = *(float *)(pbVar38 + -8);
      if (1.0 < *(float *)(pbVar38 + -8)) {
        fVar57 = 1.0;
      }
      *(float *)(lVar47 + 0x170) = fVar57;
      *(int *)(lVar47 + 0x174) = *(int *)(pbVar38 + -0x14);
      *(int *)(lVar47 + 0x188) = *(int *)(pbVar38 + -0x18);
      *(int *)(lVar47 + 0x180) = *(int *)(pbVar38 + -0x1c);
      *(int *)(lVar47 + 0x178) = *(int *)(pbVar38 + -0x10);
      *(int *)(lVar47 + 0x17c) = *(int *)(pbVar38 + -0xc);
      *(undefined4 *)(lVar47 + 0x184) = 0x3f800000;
      *(byte *)(lVar47 + 0x19b) = (byte)((ushort)*(undefined2 *)(pbVar38 + -2) >> 9) & 1;
      *(uint *)(lVar47 + 0x168) = (uint)*(ushort *)(pbVar38 + -4);
      bVar23 = *pbVar38;
      if (bVar23 != 0) {
        *(uint *)(lVar32 + lVar27 + 0x158) = (uint)bVar23;
        *(long *)(lVar32 + lVar27 + 0x150) = lVar30;
        lVar30 = lVar30 + (ulong)bVar23;
        iVar24 = iVar24 + (uint)bVar23;
      }
      lVar32 = param_1[0xe];
      lVar25 = lVar25 + 1;
      lVar27 = lVar27 + 0x1c0;
      pbVar38 = pbVar38 + 0x30;
      puVar54 = puVar54 + 8;
    } while (lVar25 < (long)uVar51);
  }
  lVar32 = lVar32 + uVar51 * 0x1c0;
  *(undefined8 *)(lVar32 + 0x1b0) = *(undefined8 *)(lVar32 + -0x10);
  Aska::ArticulatedDynamicsManagerBase::InitParentOfRoots(unsigned char**, int)(param_1,&lStack_68,iVar52);
  uVar26 = lStack_68 + 0xfU & 0xfffffffffffffff0;
  param_1[0xf] = uVar26;
  lStack_68 = uVar26 + uVar50 * 0x50;
  *(ushort *)((long)param_1 + 0x62) = uVar21;
  if (bVar1) {
    *(undefined4 *)(param_1 + 0x19) = *(undefined4 *)(param_3 + 0x120);
    param_1[0x17] = lVar28;
    param_1[0x18] = lVar7;
  }
  else {
    uVar34 = 0;
    iVar52 = 0;
    while( true ) {
      lVar25 = param_1[0xe];
      lVar32 = lVar25 + uVar34 * 0x1c0;
      *(ulong *)(lVar32 + 0x160) = uVar26 + (long)iVar52 * 0x50;
      if (uVar21 != 0) {
        uVar26 = uVar50;
        puVar45 = (undefined4 *)((ulong)uVar11 + param_3 + 0x30);
        do {
          if (uVar34 == (uint)puVar45[-0xc]) {
            lVar27 = param_1[0xf];
            lVar30 = (long)iVar52;
            puVar29 = (undefined4 *)(lVar27 + (long)iVar52 * 0x50);
            *(long *)(puVar29 + 0x10) = lVar32;
            lVar46 = param_1[0xe];
            lVar47 = (long)(int)puVar45[-0xb];
            pbVar38 = (byte *)(puVar29 + 8);
            *(long *)(puVar29 + 0x12) = lVar46 + lVar47 * 0x1c0;
            puVar29[0xd] = puVar45[-10];
            *(bool *)((long)puVar29 + 0x21) = *(char *)(puVar45 + -4) != '\0';
            puVar29[9] = puVar45[-9];
            puVar29[0xb] = puVar45[-8];
            puVar29[0xc] = puVar45[-7];
            bVar23 = *(char *)((long)puVar45 + -0xf) != '\0';
            *(byte *)(puVar29 + 8) = bVar23;
            fVar57 = (float)puVar45[-6];
            if ((fVar57 != 0.0) || ((float)puVar45[-5] != 0.0)) {
              bVar23 = bVar23 | 2;
              *pbVar38 = bVar23;
              fVar57 = (float)puVar45[-6];
            }
            lVar31 = lVar27 + lVar30 * 0x50;
            *(float *)(lVar31 + 0x38) = fVar57;
            *(undefined4 *)(lVar31 + 0x3c) = puVar45[-5];
            if (*(char *)((long)puVar45 + -0xe) != '\0') {
              bVar23 = bVar23 | 4;
              *pbVar38 = bVar23;
            }
            iVar52 = iVar52 + 1;
            if (*(char *)((long)puVar45 + -0xd) != '\0') {
              bVar23 = bVar23 | 8;
              *pbVar38 = bVar23;
            }
            lVar27 = lVar27 + lVar30 * 0x50;
            *puVar29 = *puVar45;
            *(undefined4 *)(lVar27 + 4) = puVar45[1];
            *(undefined4 *)(lVar27 + 8) = puVar45[2];
            *(undefined4 *)(lVar27 + 0xc) = puVar45[3];
            *(undefined4 *)(lVar27 + 0x10) = puVar45[4];
            *(undefined4 *)(lVar27 + 0x14) = puVar45[5];
            *(undefined4 *)(lVar27 + 0x18) = puVar45[6];
            *(undefined4 *)(lVar27 + 0x1c) = puVar45[7];
            if (*(long *)(*(long *)(lVar46 + lVar47 * 0x1c0 + 0x1b0) + 0xc0) ==
                *(long *)(lVar25 + uVar34 * 0x1c0 + 0x1b0)) {
              *pbVar38 = bVar23 | 0x10;
              lVar46 = lVar46 + lVar47 * 0x1c0;
              *(byte *)(lVar46 + 0x19c) = *(byte *)(lVar46 + 0x19c) | 2;
            }
          }
          uVar26 = uVar26 - 1;
          puVar45 = puVar45 + 0x14;
        } while (uVar26 != 0);
      }
      uVar34 = uVar34 + 1;
      if (uVar34 == uVar51) break;
      uVar26 = param_1[0xf];
    }
    *(undefined4 *)(param_1 + 0x19) = *(undefined4 *)(param_3 + 0x120);
    param_1[0x17] = lVar28;
    param_1[0x18] = lVar7;
    if (!bVar1) {
      uVar26 = 0;
      do {
        lVar32 = param_1[0xe];
        if ((*(char *)(lVar32 + uVar26 * 0x1c0 + 0x199) == '\0') &&
           (lVar25 = *(long *)(*(long *)(lVar32 + uVar26 * 0x1c0 + 0x1b0) + 0xc0), lVar25 != 0)) {
          uVar34 = 0;
          lVar28 = lVar32;
          do {
            if ((uVar26 != uVar34) && (*(long *)(lVar28 + 0x1b0) == lVar25)) {
              lVar32 = lVar32 + uVar26 * 0x1c0;
              *(long *)(lVar32 + 400) = lVar28;
              *(long *)(lVar32 + 0x130) = lVar28 + 0xb0;
              break;
            }
            uVar34 = uVar34 + 1;
            lVar28 = lVar28 + 0x1c0;
          } while ((long)uVar34 < (long)uVar51);
        }
        Aska::ADMJoint::CheckLengthFromParent()();
        uVar26 = uVar26 + 1;
      } while (uVar26 != uVar51);
    }
  }
  uVar51 = Aska::ArticulatedDynamicsManagerBase::InitJoints(unsigned char**)(param_1,&lStack_68);
  if ((uVar51 & 1) == 0) {
code_r0x0242b8a4:
    if (0 < (long)(short)param_1[0xc]) {
      lVar56 = 0;
      uVar51 = (long)(short)param_1[0xc] & 0xffffffff;
      do {
        Aska::ADMJoint::ReleaseAll()(param_1[0xe] + lVar56);
        uVar51 = uVar51 - 1;
        lVar56 = lVar56 + 0x1c0;
      } while (uVar51 != 0);
    }
    return 0;
  }
  if (bVar19 != 0) {
    param_1[0x29] = lStack_68;
    *(ushort *)((long)param_1 + 100) = (ushort)bVar19;
    lVar32 = 0;
    sVar48 = 0;
    lVar25 = lStack_68;
    lStack_68 = lStack_68 + uVar49 * 8;
    while( true ) {
      lVar28 = Aska::ArticulatedDynamicsManagerBase::SearchOrginalData(Aska::AsfHandler*, Aska::AsfHandler*, int)(param_1,lVar56,0,puVar55[lVar32]);
      if (lVar28 != 0) {
        sVar48 = sVar48 + 1;
        *(undefined8 *)(lVar25 + lVar32 * 8) = *(undefined8 *)(lVar28 + 0x198);
      }
      if (uVar49 - 1 == lVar32) break;
      lVar25 = param_1[0x29];
      lVar32 = lVar32 + 1;
    }
    puVar55 = puVar55 + (ulong)(bVar19 - 1) + 1;
    *(short *)((long)param_1 + 100) = sVar48;
  }
  if (bVar43 != 0) {
    uVar51 = Aska::ArticulatedDynamicsManagerBase::AllocConstraintList(unsigned char**, int)(param_1,&lStack_68);
    if ((uVar51 & 1) == 0) goto code_r0x0242b8a4;
    puVar54 = (undefined8 *)param_1[0x2a];
    do {
      lVar32 = Aska::ArticulatedDynamicsManagerBase::SearchOrginalData(Aska::AsfHandler*, Aska::AsfHandler*, int)(param_1,lVar56,0,*puVar55);
      if (lVar32 == 0) {
        uVar35 = 0;
      }
      else {
        uVar35 = *(undefined8 *)(lVar32 + 0x198);
      }
      *puVar54 = uVar35;
      uVar53 = uVar53 - 1;
      puVar55 = puVar55 + 1;
      puVar54 = puVar54 + 1;
    } while (uVar53 != 0);
    *(int *)((long)param_1 + 0x124) = iVar24;
    param_1[0x25] = lVar8;
  }
  bVar19 = *(byte *)(param_3 + 0x118);
  if ((bVar19 & 1) != 0) {
    *(byte *)((long)param_1 + 0x9a) = *(byte *)((long)param_1 + 0x9a) | 1;
    bVar19 = *(byte *)(param_3 + 0x118);
  }
  if ((bVar19 >> 1 & 1) != 0) {
    *(byte *)((long)param_1 + 0x9a) = *(byte *)((long)param_1 + 0x9a) | 2;
  }
  *(undefined1 *)((long)param_1 + 0x9b) = *(undefined1 *)(param_3 + 0x146);
  if (*(char *)(param_3 + 0x119) != '\0') {
    iVar52 = *(int *)(param_3 + 0x11c);
    if (iVar52 < 0) {
      if (*(long *)(lVar56 + 0x78) != 0) {
        lVar25 = *(long *)(lVar56 + 0x508);
        lVar32 = *(long *)(lVar56 + 0x78) + (long)(int)(iVar52 << 5 ^ 0xffffffe0) + 0x20;
        if ((((lVar25 == 0) || (*(int *)(lVar25 + 0xb0) < 1)) ||
            (lVar25 = Aska::AsfHandler::QuickSearch(char const*) const(lVar25,lVar32), lVar25 == 0)) ||
           (lVar25 = *(long *)(lVar25 + 0x38), lVar25 == 0)) {
          lVar25 = Aska::AsfHandler::QuickSearchByNameFromExternalLinkList(char const*) const(lVar56,lVar32);
          goto joined_r0x0242b944;
        }
        goto code_r0x0242b948;
      }
    }
    else {
      lVar25 = *(long *)(*(long *)(*(long *)(lVar56 + 0xd8) + (long)iVar52 * 8) + 0x38);
joined_r0x0242b944:
      if (lVar25 != 0) {
code_r0x0242b948:
        param_1[0x20] = lVar25;
      }
    }
  }
  if (*(char *)(param_3 + 0x147) != '\0') {
    iVar52 = *(int *)(param_3 + 0x148);
    if (iVar52 < 0) {
      if (*(long *)(lVar56 + 0x78) != 0) {
        lVar25 = *(long *)(lVar56 + 0x508);
        lVar32 = *(long *)(lVar56 + 0x78) + (long)(int)(iVar52 << 5 ^ 0xffffffe0) + 0x20;
        if (((lVar25 == 0) || (*(int *)(lVar25 + 0xb0) < 1)) ||
           ((lVar25 = Aska::AsfHandler::QuickSearch(char const*) const(lVar25,lVar32), lVar25 == 0 ||
            (lVar25 = *(long *)(lVar25 + 0x38), lVar25 == 0)))) {
          lVar25 = Aska::AsfHandler::QuickSearchByNameFromExternalLinkList(char const*) const(lVar56,lVar32);
          goto joined_r0x0242b9bc;
        }
        goto code_r0x0242b9c0;
      }
    }
    else {
      lVar25 = *(long *)(*(long *)(*(long *)(lVar56 + 0xd8) + (long)iVar52 * 8) + 0x38);
joined_r0x0242b9bc:
      if (lVar25 != 0) {
code_r0x0242b9c0:
        param_1[0x21] = lVar25;
      }
    }
  }
  if (uVar21 != 0) {
    uVar51 = 0;
    do {
      pbVar38 = (byte *)(param_1[0xf] + uVar51 * 0x50 + 0x20);
      bVar19 = *pbVar38;
      if ((bVar19 >> 4 & 1) != 0) {
        lVar56 = *(long *)(param_1[0xf] + uVar51 * 0x50 + 0x48);
        iVar52 = *(int *)(lVar56 + 0x168);
        if (0 < iVar52) {
          bVar43 = 0;
          pbVar44 = (byte *)(*(long *)(lVar56 + 0x160) + 0x20);
          lVar56 = 1;
          do {
            bVar23 = *pbVar44 >> 4 & 1;
            bVar43 = bVar43 | bVar23;
            if (bVar23 != 0) break;
            bVar1 = lVar56 < iVar52;
            pbVar44 = pbVar44 + 0x50;
            lVar56 = lVar56 + 1;
          } while (bVar1);
          if (bVar43 != 0) goto code_r0x0242ba30;
        }
        *pbVar38 = bVar19 | 0x20;
      }
code_r0x0242ba30:
      uVar51 = uVar51 + 1;
    } while (uVar51 != uVar50);
  }
  if ((long)(short)param_1[0xc] < 1) {
    iVar52 = 0;
    uVar51 = 0;
  }
  else {
    uVar26 = param_1[0xe];
    uVar51 = 0;
    iVar52 = 0;
    uVar49 = uVar26 + (long)(short)param_1[0xc] * 0x1c0;
    do {
      iVar24 = iVar52;
      if (*(char *)(uVar26 + 0x199) != '\0') {
        uVar51 = (ulong)((int)uVar51 + 1);
        iVar24 = Aska::ArticulatedDynamicsManagerMP::CalcIKLinkCnt(Aska::ADMJoint*)(param_1,uVar26);
        if (iVar24 <= iVar52) {
          iVar24 = iVar52;
        }
      }
      iVar52 = iVar24;
      uVar26 = uVar26 + 0x1c0;
    } while (uVar26 < uVar49);
  }
  *(int *)(param_1 + 0x3c) = (int)uVar51;
  *(int *)((long)param_1 + 0x1e4) = iVar52;
  lVar56 = (long)*(short *)((long)param_1 + 0x62);
  if (lVar56 == 0) {
    iVar24 = 0;
  }
  else {
    lVar32 = param_1[0xf];
    uVar26 = (lVar56 * 0x50 - 0x50U) / 0x50 + 1;
    if ((uVar26 < 2) || (uVar49 = uVar26 & 0x7fffffffffffffe, uVar49 == 0)) {
      iVar24 = 0;
      lVar25 = lVar32;
    }
    else {
      iVar58 = 0;
      iVar24 = 0;
      pbVar38 = (byte *)(lVar32 + 0x70);
      uVar50 = uVar49;
      do {
        uVar50 = uVar50 - 2;
        iVar58 = iVar58 + (pbVar38[-0x50] >> 4 & 1);
        iVar24 = iVar24 + (*pbVar38 >> 4 & 1);
        pbVar38 = pbVar38 + 0xa0;
      } while (uVar50 != 0);
      iVar24 = iVar24 + iVar58;
      lVar25 = lVar32 + uVar49 * 0x50;
      if (uVar26 == uVar49) goto code_r0x0242bb50;
    }
    do {
      pbVar38 = (byte *)(lVar25 + 0x20);
      lVar25 = lVar25 + 0x50;
      iVar24 = iVar24 + (*pbVar38 >> 4 & 1);
    } while (lVar32 + lVar56 * 0x50 != lVar25);
  }
code_r0x0242bb50:
  lVar56 = (-(uVar51 >> 0x1f) & 0xfffffff000000000 | uVar51 << 4) + (long)iVar52 * 0x14 +
           (long)iVar24 * 0x50;
  *(int *)(param_1 + 0x3d) = iVar24;
  if (lVar56 != 0) {
    if (param_1[0x37] != 0) {
      operator delete[](void*)();
    }
    lVar56 = operator new[](unsigned long, unsigned long, bool)(lVar56,0x10,1);
    lStack_68 = lVar56 + (long)(int)param_1[0x3d] * 0x50;
    iVar52 = *(int *)((long)param_1 + 0x1e4);
    param_1[0x37] = lVar56;
    param_1[0x38] = lStack_68;
    lStack_68 = lStack_68 + (long)(int)param_1[0x3c] * 0x10;
    param_1[0x3e] = lStack_68;
    lStack_68 = lStack_68 + (ulong)(uint)(iVar52 * 0xc);
    *(int *)(param_1 + 0x3f) = iVar52;
    param_1[0x39] = lVar56;
    param_1[0x3a] = lStack_68;
    lStack_68 = lStack_68 + (long)iVar52 * 4;
    param_1[0x3b] = lStack_68;
    lStack_68 = lStack_68 + (long)iVar52 * 4;
    Aska::ArticulatedDynamicsManagerMP::CreateLinkList()(param_1);
    Aska::ArticulatedDynamicsManagerMP::InitializeLinkList()(param_1);
  }
  *(undefined1 *)(param_1 + 0x1b) = 1;
  return 1;
}

// ==== Aska::ArticulatedDynamicsManagerMP::CalcLinkListBufferSize()
// vaddr 0x232bbec | ghidra 0x242bbec | size 336 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP22CalcLinkListBufferSizeEv | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska28ArticulatedDynamicsManagerMP22CalcLinkListBufferSizeEv(long param_1)

{
  int iVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  int iVar5;
  byte *pbVar6;
  ulong uVar7;
  ulong uVar8;
  int iVar9;
  ulong uVar10;
  ulong uVar11;
  
  if ((long)*(short *)(param_1 + 0x60) < 1) {
    iVar9 = 0;
    uVar10 = 0;
  }
  else {
    uVar8 = *(ulong *)(param_1 + 0x70);
    uVar10 = 0;
    iVar9 = 0;
    uVar11 = uVar8 + (long)*(short *)(param_1 + 0x60) * 0x1c0;
    do {
      iVar1 = iVar9;
      if (*(char *)(uVar8 + 0x199) != '\0') {
        uVar10 = (ulong)((int)uVar10 + 1);
        iVar1 = Aska::ArticulatedDynamicsManagerMP::CalcIKLinkCnt(Aska::ADMJoint*)(param_1,uVar8);
        if (iVar1 <= iVar9) {
          iVar1 = iVar9;
        }
      }
      iVar9 = iVar1;
      uVar8 = uVar8 + 0x1c0;
    } while (uVar8 < uVar11);
  }
  *(int *)(param_1 + 0x1e0) = (int)uVar10;
  *(int *)(param_1 + 0x1e4) = iVar9;
  lVar2 = (long)*(short *)(param_1 + 0x62);
  if (lVar2 == 0) {
    iVar1 = 0;
  }
  else {
    lVar3 = *(long *)(param_1 + 0x78);
    uVar8 = (lVar2 * 0x50 - 0x50U) / 0x50 + 1;
    if ((uVar8 < 2) || (uVar11 = uVar8 & 0x7fffffffffffffe, uVar11 == 0)) {
      iVar1 = 0;
      lVar4 = lVar3;
    }
    else {
      iVar5 = 0;
      iVar1 = 0;
      pbVar6 = (byte *)(lVar3 + 0x70);
      uVar7 = uVar11;
      do {
        uVar7 = uVar7 - 2;
        iVar5 = iVar5 + (pbVar6[-0x50] >> 4 & 1);
        iVar1 = iVar1 + (*pbVar6 >> 4 & 1);
        pbVar6 = pbVar6 + 0xa0;
      } while (uVar7 != 0);
      iVar1 = iVar1 + iVar5;
      lVar4 = lVar3 + uVar11 * 0x50;
      if (uVar8 == uVar11) goto code_r0x0242bd10;
    }
    do {
      pbVar6 = (byte *)(lVar4 + 0x20);
      lVar4 = lVar4 + 0x50;
      iVar1 = iVar1 + (*pbVar6 >> 4 & 1);
    } while (lVar3 + lVar2 * 0x50 != lVar4);
  }
code_r0x0242bd10:
  *(int *)(param_1 + 0x1e8) = iVar1;
  return (-(uVar10 >> 0x1f) & 0xfffffff000000000 | uVar10 << 4) + (long)iVar9 * 0xc +
         (long)iVar9 * 8 + (long)iVar1 * 0x50;
}

// ==== Aska::ArticulatedDynamicsManagerMP::CreateLinkList()
// vaddr 0x232bd3c | ghidra 0x242bd3c | size 344 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP14CreateLinkListEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska28ArticulatedDynamicsManagerMP14CreateLinkListEv(long param_1)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  ulong uVar4;
  int iVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  int iVar9;
  long lVar10;
  long lVar11;
  ulong uVar12;
  int iVar13;
  long *plVar14;
  long lVar15;
  
  uVar3 = _UNK_027dbb08;
  uVar2 = _UNK_027dbb00;
  uVar4 = (ulong)*(uint *)(param_1 + 0x1e8);
  if (0 < (int)*(uint *)(param_1 + 0x1e8)) {
    lVar6 = 0;
    do {
      uVar4 = uVar4 - 1;
      puVar1 = (undefined8 *)(*(long *)(param_1 + 0x1c8) + lVar6);
      lVar6 = lVar6 + 0x50;
      *puVar1 = 0;
      *(undefined4 *)(puVar1 + 1) = 0;
      *(undefined4 *)(puVar1 + 8) = 0;
      puVar1[6] = 0;
      puVar1[7] = 0;
      *(undefined8 *)((long)puVar1 + 0x14) = uVar3;
      *(undefined8 *)((long)puVar1 + 0xc) = uVar2;
      *(undefined8 *)((long)puVar1 + 0x24) = uVar3;
      *(undefined8 *)((long)puVar1 + 0x1c) = uVar2;
      *(undefined4 *)((long)puVar1 + 0x2c) = 0x3f800000;
    } while (uVar4 != 0);
  }
  if ((long)*(short *)(param_1 + 0x62) != 0) {
    lVar6 = *(long *)(param_1 + 0x78);
    uVar4 = 0;
    iVar5 = 0;
    lVar7 = lVar6 + (long)*(short *)(param_1 + 0x62) * 0x50;
    do {
      if (((*(byte *)(lVar6 + 0x20) >> 4 & 1) != 0) &&
         (lVar11 = *(long *)(lVar6 + 0x40), *(char *)(lVar11 + 0x199) != '\0')) {
        iVar13 = *(int *)(lVar11 + 0x168);
        lVar8 = *(long *)(param_1 + 0x1c8) + (long)iVar5 * 0x50;
        lVar10 = lVar8;
        if (iVar13 < 1) {
code_r0x0242be48:
          iVar5 = iVar5 + 1;
          *(undefined8 *)(lVar10 + 0x30) = *(undefined8 *)(lVar6 + 0x40);
          *(undefined8 *)(lVar10 + 0x38) = *(undefined8 *)(lVar6 + 0x48);
          *(undefined4 *)(lVar10 + 0x40) = *(undefined4 *)(lVar6 + 0x28);
          iVar9 = 1;
        }
        else {
          iVar9 = 0;
          do {
            lVar15 = 0;
            plVar14 = (long *)(*(long *)(lVar11 + 0x160) + 0x48);
            while ((*(byte *)(plVar14 + -5) >> 4 & 1) == 0) {
              lVar15 = lVar15 + 1;
              plVar14 = plVar14 + 10;
              if (iVar13 <= lVar15) goto code_r0x0242be38;
            }
            if (plVar14 == (long *)0x48) break;
            lVar11 = *plVar14;
            iVar5 = iVar5 + 1;
            iVar9 = iVar9 + 1;
            *(long *)(lVar10 + 0x30) = plVar14[-1];
            *(long *)(lVar10 + 0x38) = *plVar14;
            *(int *)(lVar10 + 0x40) = (int)plVar14[-4];
            iVar13 = *(int *)(lVar11 + 0x168);
            lVar10 = lVar10 + 0x50;
          } while (0 < iVar13);
code_r0x0242be38:
          if (iVar9 < 1) goto code_r0x0242be48;
        }
        uVar12 = -(uVar4 >> 0x1f) & 0xfffffff000000000 | uVar4 << 4;
        uVar4 = (ulong)((int)uVar4 + 1);
        *(long *)(*(long *)(param_1 + 0x1c0) + uVar12) = lVar8;
        *(int *)(*(long *)(param_1 + 0x1c0) + uVar12 + 8) = iVar9;
      }
      lVar6 = lVar6 + 0x50;
    } while (lVar6 != lVar7);
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerMP::InitializeLinkList()
// vaddr 0x232be94 | ghidra 0x242be94 | size 568 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP18InitializeLinkListEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28ArticulatedDynamicsManagerMP18InitializeLinkListEv(long param_1)

{
  long *plVar1;
  float *pfVar2;
  long lVar3;
  long lVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined4 uVar16;
  float fVar17;
  
  uVar5 = *(uint *)(param_1 + 0x1e8);
  uVar11 = (ulong)uVar5;
  if (0 < (int)uVar5) {
    lVar8 = 0x38;
    uVar9 = uVar11;
    do {
      uVar9 = uVar9 - 1;
      plVar1 = (long *)(*(long *)(param_1 + 0x1c8) + lVar8);
      lVar3 = plVar1[-1];
      lVar4 = *plVar1;
      lVar8 = lVar8 + 0x50;
      *(float *)(plVar1 + -5) = *(float *)(lVar4 + 0x10) - *(float *)(lVar3 + 0x10);
      *(float *)((long)plVar1 + -0x24) = *(float *)(lVar4 + 0x14) - *(float *)(lVar3 + 0x14);
      *(float *)(plVar1 + -4) = *(float *)(lVar4 + 0x18) - *(float *)(lVar3 + 0x18);
      *(undefined4 *)((long)plVar1 + -0x1c) = *(undefined4 *)(lVar4 + 0x1c);
      *(float *)(plVar1 + -3) = *(float *)(lVar4 + 0x50) - *(float *)(lVar3 + 0x50);
      *(float *)((long)plVar1 + -0x14) = *(float *)(lVar4 + 0x54) - *(float *)(lVar3 + 0x54);
      *(float *)(plVar1 + -2) = *(float *)(lVar4 + 0x58) - *(float *)(lVar3 + 0x58);
      *(undefined4 *)((long)plVar1 + -0xc) = *(undefined4 *)(lVar4 + 0x5c);
    } while (uVar9 != 0);
  }
  uVar6 = *(uint *)(param_1 + 0x1e0);
  if (0 < (int)uVar6) {
    uVar9 = 0;
    uVar16 = *(undefined4 *)PTR__ZN4Aska30ArticulatedDynamicsManagerBase9m_fBaseDtE_02cba288;
    do {
      uVar10 = *(ulong *)(*(long *)(param_1 + 0x1c0) + uVar9 * 0x10);
      if (uVar10 != 0) {
        iVar7 = *(int *)(*(long *)(param_1 + 0x1c0) + uVar9 * 0x10 + 8);
        if (0 < iVar7) {
          uVar12 = uVar10;
          do {
            fVar17 = *(float *)(uVar12 + 0x40);
            fVar14 = *(float *)(uVar12 + 0x10) * *(float *)(uVar12 + 0x10) +
                     *(float *)(uVar12 + 0x14) * *(float *)(uVar12 + 0x14) +
                     *(float *)(uVar12 + 0x18) * *(float *)(uVar12 + 0x18);
            fVar13 = SQRT(fVar14);
            if (NAN(fVar13)) {
              fVar13 = (float)sqrtf(fVar14);
            }
            fVar17 = fVar17 / fVar13;
            fVar14 = fVar17 * *(float *)(uVar12 + 0x10);
            fVar15 = fVar17 * *(float *)(uVar12 + 0x14);
            fVar17 = fVar17 * *(float *)(uVar12 + 0x18);
            fVar13 = (fVar14 * *(float *)(uVar12 + 0x20) + fVar15 * *(float *)(uVar12 + 0x24) +
                     fVar17 * *(float *)(uVar12 + 0x28)) /
                     (*(float *)(uVar12 + 0x40) * *(float *)(uVar12 + 0x40));
            *(float *)(uVar12 + 0x10) = fVar14;
            *(float *)(uVar12 + 0x14) = fVar15;
            *(float *)(uVar12 + 0x18) = fVar17;
            *(float *)(uVar12 + 0x20) = *(float *)(uVar12 + 0x20) - fVar14 * fVar13;
            *(float *)(uVar12 + 0x24) = *(float *)(uVar12 + 0x24) - fVar15 * fVar13;
            *(float *)(uVar12 + 0x28) = *(float *)(uVar12 + 0x28) - fVar17 * fVar13;
            uVar12 = uVar12 + 0x50;
          } while (uVar12 < uVar10 + (long)iVar7 * 0x50);
        }
        void Aska::ArticulatedDynamicsManagerMP::GetAcceleration<Aska::ArticulatedDynamicsManagerMP, Aska::ADMJoint>(Aska::ArticulatedDynamicsManagerMP*, float, Aska::LinkListParam*, int)(uVar16,param_1,uVar10,iVar7);
      }
      uVar9 = uVar9 + 1;
    } while (uVar9 != uVar6);
  }
  if (0 < (int)uVar5) {
    lVar8 = 0;
    do {
      uVar11 = uVar11 - 1;
      pfVar2 = (float *)(*(long *)(param_1 + 0x1c8) + lVar8);
      lVar8 = lVar8 + 0x50;
      pfVar2[8] = pfVar2[8] - *pfVar2 * 0.5;
      pfVar2[9] = pfVar2[9] - pfVar2[1] * 0.5;
      pfVar2[10] = pfVar2[10] - pfVar2[2] * 0.5;
    } while (uVar11 != 0);
  }
  return;
}

// ==== Aska::ArticulatedDynamicsManagerMP::~ArticulatedDynamicsManagerMP()
// vaddr 0x232c0cc | ghidra 0x242c0cc | size 52 | symbol _ZN4Aska28ArticulatedDynamicsManagerMPD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28ArticulatedDynamicsManagerMPD1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska28ArticulatedDynamicsManagerMPE_02cb70b0 + 0x10);
  if (param_1[0x37] != 0) {
    operator delete[](void*)();
    param_1[0x37] = 0;
  }
  (*(code *)PTR__ZN4Aska30ArticulatedDynamicsManagerBaseD2Ev_02cb2ea8)(param_1);
  return;
}

// ==== Aska::ArticulatedDynamicsManagerMP::~ArticulatedDynamicsManagerMP()
// vaddr 0x232c100 | ghidra 0x242c100 | size 60 | symbol _ZN4Aska28ArticulatedDynamicsManagerMPD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28ArticulatedDynamicsManagerMPD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska28ArticulatedDynamicsManagerMPE_02cb70b0 + 0x10);
  if (param_1[0x37] != 0) {
    operator delete[](void*)();
    param_1[0x37] = 0;
  }
  Aska::ArticulatedDynamicsManagerBase::~ArticulatedDynamicsManagerBase()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::ArticulatedDynamicsManagerMP::CalcBufferSize(int, int, int, int, int)
// vaddr 0x232c13c | ghidra 0x242c13c | size 68 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP14CalcBufferSizeEiiiii | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska28ArticulatedDynamicsManagerMP14CalcBufferSizeEiiiii
               (undefined8 param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  return (((long)param_3 * 0x50 | 3U) + (long)param_6 +
          (((long)(param_2 + 1) << 9 | 0xfU) + (long)param_6 * 0xa8 & 0xfffffffffffffff0) &
         0xfffffffffffffffc) + ((long)param_5 + (long)param_4) * 8;
}

// ==== Aska::ArticulatedDynamicsManagerMP::Simulate(float, unsigned int, float)
// vaddr 0x232c180 | ghidra 0x242c180 | size 232 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP8SimulateEfjf | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska28ArticulatedDynamicsManagerMP8SimulateEfjf
          (float param_1,undefined8 param_2,long param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  
  if (*(char *)(param_3 + 0xe1) != '\0') {
    iVar2 = *(int *)(param_3 + 0xec);
    fVar4 = *(float *)PTR__ZN4Aska30ArticulatedDynamicsManagerBase9m_fBaseDtE_02cba288;
    iVar1 = iVar2;
    if (iVar2 < 3) {
      iVar1 = 2;
    }
    if (*(char *)(param_3 + 0x122) == '\0') {
      iVar1 = iVar2;
    }
    if ((((*PTR__ZN4Aska30ArticulatedDynamicsManagerBase8m_bDtDivE_02cbf9f8 != '\0') &&
         (*(char *)(param_3 + 0xdd) != '\0')) && (*(char *)(param_3 + 0xdc) == '\0')) &&
       (iVar1 = iVar1 * (int)(param_1 / fVar4), iVar1 < 2)) {
      iVar1 = 1;
    }
    fVar3 = fVar4;
    if (iVar1 < 2) {
      fVar3 = param_1;
    }
    if (*(char *)(param_3 + 0xdc) == '\0') {
      if (fVar4 <= fVar3) {
        fVar4 = fVar3 / fVar4;
      }
      else {
        fVar4 = fVar4 / fVar3 + 0.5;
      }
      iVar2 = (int)fVar4;
      if (iVar2 < 2) {
        iVar2 = 1;
      }
    }
    else {
      iVar2 = 1;
    }
    void Aska::ArticulatedDynamicsManagerMP::SimulateMain<Aska::ArticulatedDynamicsManagerMP>(Aska::ArticulatedDynamicsManagerMP*, Aska::ADMJoint*, Aska::ADMJoint*, unsigned int, int, int, unsigned int, float, float, unsigned int, float)(fVar3,1.0 / fVar3,param_2,param_3,*(long *)(param_3 + 0x70),
                    *(long *)(param_3 + 0x70) + (long)*(short *)(param_3 + 0x60) * 0x1c0,
                    (long)*(short *)(param_3 + 0x60),0,iVar1,iVar2,param_4);
    return 1;
  }
  return 0;
}

// ==== Aska::ArticulatedDynamicsManagerMP::Clone(Aska::IAnimatable const*)
// vaddr 0x232c5f0 | ghidra 0x242c5f0 | size 4 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28ArticulatedDynamicsManagerMP5CloneEPKNS_11IAnimatableE(void)

{
  (*(code *)PTR__ZN4Aska11IAnimatable5CloneEPKS0__02c96b68)();
  return;
}

// ==== Aska::ArticulatedDynamicsManagerMP::CreateClone(Aska::IAnimatable const*)
// vaddr 0x232c5f4 | ghidra 0x242c5f4 | size 440 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
long * _ZN4Aska28ArticulatedDynamicsManagerMP11CreateCloneEPKNS_11IAnimatableE
                 (long param_1,undefined8 param_2)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined1 uVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  long *plVar7;
  ulong uVar8;
  long lVar9;
  
  plVar7 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x200,PTR__ZSt7nothrow_02cb9a80);
  if (plVar7 != (long *)0x0) {
    lVar9 = *(long *)(param_1 + 0x20);
    *(undefined4 *)(plVar7 + 5) = 0;
    puVar4 = PTR__ZTVN4Aska30ArticulatedDynamicsManagerBase14SimulateNotifyE_02cbb950;
    puVar1 = PTR__ZTVN4Aska30ArticulatedDynamicsManagerBaseE_02cc0c60 + 0x10;
    plVar7[0x12] = 0;
    *(undefined2 *)((long)plVar7 + 0x9a) = 0;
    *(undefined4 *)(plVar7 + 0x11) = 0;
    plVar7[0x10] = 0;
    *(undefined4 *)(plVar7 + 0x16) = 0;
    plVar7[0x14] = 0;
    plVar7[0x15] = 0;
    *(undefined8 *)((long)plVar7 + 0xd5) = 0;
    plVar7[0x1a] = 0;
    *(undefined1 *)((long)plVar7 + 0xdf) = 0;
    *(undefined4 *)((long)plVar7 + 0xe2) = 0;
    *(undefined2 *)(plVar7 + 0x24) = 0;
    *(undefined1 *)((long)plVar7 + 0x122) = 0;
    *(undefined4 *)((long)plVar7 + 0xf4) = 0x44750000;
    *(undefined4 *)(plVar7 + 0x1f) = 0x3c88ab7c;
    *(undefined4 *)((long)plVar7 + 0x134) = 0;
    *plVar7 = (long)puVar1;
    puVar1 = PTR__ZTVN4Aska26DefaultLandScapeConstraintE_02cbb230;
    plVar7[6] = (long)(puVar4 + 0x10);
    plVar7[2] = 0;
    plVar7[1] = 0;
    *(undefined1 *)(plVar7 + 3) = 1;
    plVar7[9] = 0;
    plVar7[8] = 0;
    plVar7[0xd] = 0;
    plVar7[0xc] = 0;
    plVar7[0xf] = 0;
    plVar7[0xe] = 0;
    *(undefined1 *)((long)plVar7 + 0xdd) = 1;
    *(undefined1 *)(plVar7 + 0x1c) = 1;
    *(undefined1 *)((long)plVar7 + 0xe1) = 1;
    *(undefined4 *)(plVar7 + 0x1d) = 0;
    *(undefined4 *)((long)plVar7 + 0xec) = 1;
    plVar7[0x21] = 0;
    plVar7[0x20] = 0;
    *(undefined8 *)((long)plVar7 + 300) = 0;
    *(undefined8 *)((long)plVar7 + 0x124) = 0;
    plVar7[0x27] = (long)(puVar1 + 0x10);
    *(undefined4 *)(plVar7 + 0x28) = 0;
    plVar7[0x2a] = 0;
    plVar7[0x29] = 0;
    *(undefined4 *)(plVar7 + 0x32) = 0x100;
    puVar4 = PTR__ZTVN4Aska21DynamicsPrimitiveListE_02cb7d10;
    *(undefined1 *)((long)plVar7 + 0x194) = 1;
    puVar1 = PTR__ZTVN4Aska24DynamicsPrimitiveElementE_02cbbef0 + 0x10;
    plVar7[0x2d] = (long)(plVar7 + 0x2c);
    plVar7[0x2e] = (long)(plVar7 + 0x2c);
    puVar6 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_bDefaultEnableWorldE_02cc3dd8;
    puVar5 = PTR__ZN4Aska30ArticulatedDynamicsManagerBase21m_uiDefaultDynamicsIDE_02cc08d0;
    plVar7[0x2f] = 0;
    *(undefined1 *)((long)plVar7 + 0x196) = 0;
    plVar7[0x31] = 0;
    plVar7[0x30] = 0;
    plVar7[0x33] = 0;
    *(undefined4 *)(plVar7 + 0x34) = 0;
    plVar7[0x2c] = (long)puVar1;
    plVar7[0x2b] = (long)(puVar4 + 0x10);
    puVar1 = PTR__ZTVN4Aska28ArticulatedDynamicsManagerMPE_02cb70b0;
    uVar3 = *puVar6;
    uVar2 = *(undefined4 *)puVar5;
    plVar7[0x36] = 0;
    plVar7[0x35] = 0;
    plVar7[4] = lVar9;
    *plVar7 = (long)(puVar1 + 0x10);
    plVar7[0x3b] = 0;
    *(undefined1 *)((long)plVar7 + 0xde) = uVar3;
    *(undefined4 *)((long)plVar7 + 0x9c) = uVar2;
    plVar7[0x3a] = 0;
    plVar7[0x39] = 0;
    plVar7[0x38] = 0;
    plVar7[0x37] = 0;
    uVar8 = Aska::IAnimatable::Clone(Aska::IAnimatable const*)(plVar7,param_2);
    if ((uVar8 & 1) == 0) {
      (**(code **)(*plVar7 + 8))(plVar7);
      plVar7 = (long *)0x0;
    }
  }
  return plVar7;
}

// ==== Aska::ArticulatedDynamicsManagerMP::Get(unsigned long, void*) const
// vaddr 0x232c7ac | ghidra 0x242c7ac | size 344 | symbol _ZNK4Aska28ArticulatedDynamicsManagerMP3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska28ArticulatedDynamicsManagerMP3GetEmPv(long param_1,ulong param_2,byte *param_3)

{
  uint uVar1;
  long *plVar2;
  ulong uVar3;
  byte bVar4;
  undefined4 uVar5;
  
  if ((param_2 & 0xffff00000000) != 0) {
    return 0;
  }
  switch((uint)param_2 & 0xffff) {
  case 0xf:
    bVar4 = *(byte *)(param_1 + 0xdb);
    break;
  case 0x10:
    bVar4 = *(byte *)(param_1 + 0xdc);
    break;
  default:
    uVar1 = (uint)(param_2 >> 0x10) & 0xff;
    if (((int)uVar1 < (int)*(short *)(param_1 + 0x60)) &&
       (plVar2 = (long *)(*(long *)(param_1 + 0x70) + (ulong)uVar1 * 0x1c0),
       uVar3 = (**(code **)(*plVar2 + 0x28))(plVar2,param_2,param_3), (uVar3 & 1) != 0)) {
      return 1;
    }
    if ((int)*(short *)(param_1 + 0x66) <= (int)uVar1) {
      return 0;
    }
    plVar2 = *(long **)(*(long *)(param_1 + 0x150) + (ulong)uVar1 * 8);
    if (plVar2 != (long *)0x0) {
      uVar3 = (**(code **)(*plVar2 + 0x28))(plVar2,param_2,param_3);
      if ((uVar3 & 1) != 0) {
        return 1;
      }
      return 0;
    }
    return 0;
  case 0x21:
    bVar4 = *(byte *)(param_1 + 0x9b);
    break;
  case 0x22:
    bVar4 = *(byte *)(param_1 + 0x9a) & 1;
    break;
  case 0x23:
    bVar4 = *(byte *)(param_1 + 0x9a) >> 1 & 1;
    break;
  case 0x24:
    bVar4 = *PTR__ZN4Aska30ArticulatedDynamicsManagerBase8m_bDtDivE_02cbf9f8;
    break;
  case 0x25:
    uVar5 = *(undefined4 *)(param_1 + 0xec);
    goto code_r0x0242c8e0;
  case 0x26:
    *(undefined4 *)param_3 = *(undefined4 *)(param_1 + 0x40);
    *(undefined4 *)(param_3 + 4) = *(undefined4 *)(param_1 + 0x44);
    *(undefined4 *)(param_3 + 8) = *(undefined4 *)(param_1 + 0x48);
    *(undefined4 *)(param_3 + 0xc) = *(undefined4 *)(param_1 + 0x4c);
    return 1;
  case 0x27:
    uVar5 = *(undefined4 *)(param_1 + 0xf4);
    goto code_r0x0242c8e0;
  case 0x28:
    uVar5 = *(undefined4 *)(param_1 + 0xf0);
code_r0x0242c8e0:
    *(undefined4 *)param_3 = uVar5;
    return 1;
  case 0x45:
    bVar4 = *(byte *)(param_1 + 0xda);
  }
  *param_3 = bVar4;
  return 1;
}

// ==== Aska::ArticulatedDynamicsManagerMP::Set(unsigned long, void const*)
// vaddr 0x232c904 | ghidra 0x242c904 | size 584 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska28ArticulatedDynamicsManagerMP3SetEmPKv(long param_1,ulong param_2,byte *param_3)

{
  uint uVar1;
  byte bVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  byte bVar6;
  long *plVar7;
  ulong uVar8;
  long lVar9;
  long lVar10;
  undefined4 uVar11;
  
  if ((param_2 & 0xffff00000000) != 0) {
    return 0;
  }
  switch((uint)param_2 & 0xffff) {
  case 0xf:
    *(byte *)(param_1 + 0xdb) = *param_3;
    break;
  case 0x10:
    *(byte *)(param_1 + 0xdc) = *param_3;
    break;
  default:
    uVar1 = (uint)(param_2 >> 0x10) & 0xff;
    if (((int)*(short *)(param_1 + 0x60) <= (int)uVar1) ||
       (plVar7 = (long *)(*(long *)(param_1 + 0x70) + (ulong)uVar1 * 0x1c0),
       uVar8 = (**(code **)(*plVar7 + 0x30))(plVar7,param_2,param_3), (uVar8 & 1) == 0)) {
      if ((int)*(short *)(param_1 + 0x66) <= (int)uVar1) {
        return 0;
      }
      plVar7 = *(long **)(*(long *)(param_1 + 0x150) + (ulong)uVar1 * 8);
      if (plVar7 == (long *)0x0) {
        return 0;
      }
      uVar8 = (**(code **)(*plVar7 + 0x30))(plVar7,param_2,param_3);
      if ((uVar8 & 1) == 0) {
        return 0;
      }
    }
    break;
  case 0x21:
    bVar6 = *param_3;
    if (*(byte *)(param_1 + 0x9b) != bVar6) {
      *(byte *)(param_1 + 0x9b) = bVar6;
      if (0 < (long)*(short *)(param_1 + 0x60)) {
        uVar11 = 0x3f800000;
        if (bVar6 != 0) {
          uVar11 = 0x3f000000;
        }
        lVar9 = ((long)*(short *)(param_1 + 0x60) & 0xffffffffU) - 1;
        *(undefined4 *)(*(long *)(param_1 + 0x70) + 0x184) = uVar11;
        if (lVar9 != 0) {
          lVar10 = 0x344;
          do {
            lVar9 = lVar9 + -1;
            uVar11 = 0x3f800000;
            if (*(char *)(param_1 + 0x9b) != '\0') {
              uVar11 = 0x3f000000;
            }
            *(undefined4 *)(*(long *)(param_1 + 0x70) + lVar10) = uVar11;
            lVar10 = lVar10 + 0x1c0;
          } while (lVar9 != 0);
          return 1;
        }
      }
    }
    break;
  case 0x22:
    bVar6 = *(byte *)(param_1 + 0x9a) | 1;
    if (*param_3 == 0) {
      bVar6 = *(byte *)(param_1 + 0x9a) & 0xfe;
    }
    *(byte *)(param_1 + 0x9a) = bVar6;
    break;
  case 0x23:
    bVar6 = *(byte *)(param_1 + 0x9a);
    if ((bVar6 >> 1 & 1) != *param_3) {
      bVar2 = bVar6 | 2;
      if (*param_3 == 0) {
        bVar2 = bVar6 & 0xfd;
      }
      *(byte *)(param_1 + 0x9a) = bVar2;
      if (*(long *)(param_1 + 0x1a8) != 0) {
        Aska::DynamicsHandler::SetDirtyChangeParameter()();
        return 1;
      }
    }
    break;
  case 0x24:
    *PTR__ZN4Aska30ArticulatedDynamicsManagerBase8m_bDtDivE_02cbf9f8 = *param_3;
    break;
  case 0x25:
    *(undefined4 *)(param_1 + 0xec) = *(undefined4 *)param_3;
    break;
  case 0x26:
    uVar11 = *(undefined4 *)param_3;
    *(undefined4 *)(param_1 + 0x40) = uVar11;
    uVar3 = *(undefined4 *)(param_3 + 4);
    *(undefined4 *)(param_1 + 0x44) = uVar3;
    uVar4 = *(undefined4 *)(param_3 + 8);
    *(undefined4 *)(param_1 + 0x48) = uVar4;
    uVar5 = *(undefined4 *)(param_3 + 0xc);
    *(undefined4 *)(param_1 + 0x54) = uVar3;
    *(undefined4 *)(param_1 + 0x58) = uVar4;
    *(undefined4 *)(param_1 + 0x4c) = uVar5;
    *(undefined4 *)(param_1 + 0x50) = uVar11;
    *(undefined4 *)(param_1 + 0x5c) = uVar5;
    break;
  case 0x27:
    *(undefined4 *)(param_1 + 0xf4) = *(undefined4 *)param_3;
    break;
  case 0x28:
    *(undefined4 *)(param_1 + 0xf0) = *(undefined4 *)param_3;
    break;
  case 0x45:
    *(byte *)(param_1 + 0xda) = *param_3;
  }
  return 1;
}

// ==== Aska::ArticulatedDynamicsManagerMP::CalcIKLinkCnt(Aska::ADMJoint*)
// vaddr 0x232cb4c | ghidra 0x242cb4c | size 208 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP13CalcIKLinkCntEPNS_8ADMJointE | lib libSOA-3.7.0.so | 2026-10-08
int _ZN4Aska28ArticulatedDynamicsManagerMP13CalcIKLinkCntEPNS_8ADMJointE
              (undefined8 param_1,long param_2)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  int iVar5;
  
  uVar1 = *(uint *)(param_2 + 0x168);
  iVar5 = 0;
  while( true ) {
    if (uVar1 == 0) {
      return iVar5;
    }
    uVar4 = 0;
    lVar3 = 0;
    iVar2 = 0;
    do {
      if ((*(byte *)(*(long *)(param_2 + 0x160) + (long)(int)uVar4 * 0x50 + 0x20) >> 4 & 1) != 0) {
        lVar3 = *(long *)(*(long *)(param_2 + 0x160) + (long)(int)uVar4 * 0x50 + 0x48);
        iVar2 = iVar2 + 1;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < uVar1);
    if (iVar2 != 1) break;
    uVar1 = *(uint *)(lVar3 + 0x168);
    iVar5 = iVar5 + 1;
    param_2 = lVar3;
  }
  if (iVar2 == 0) {
    return iVar5;
  }
  lVar3 = *(long *)(param_2 + 0x160);
  uVar4 = 0;
  do {
    if ((*(byte *)(lVar3 + (long)(int)uVar4 * 0x50 + 0x20) >> 4 & 1) != 0) {
      iVar2 = _ZN4Aska28ArticulatedDynamicsManagerMP13CalcIKLinkCntEPNS_8ADMJointE
                        (param_1,*(undefined8 *)(lVar3 + (long)(int)uVar4 * 0x50 + 0x48));
      iVar5 = iVar2 + iVar5;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar1);
  return iVar5;
}

// ==== Aska::ArticulatedDynamicsManagerMP::GetClassID(int) const
// vaddr 0x232d234 | ghidra 0x242d234 | size 80 | symbol _ZNK4Aska28ArticulatedDynamicsManagerMP10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska28ArticulatedDynamicsManagerMP10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf000f171f173;
  }
  uVar2 = 0xf000f001;
  if (param_2 == 1) {
    return 0xf000f171;
  }
  if (param_2 != 3) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf001f032;
  if (param_2 != 2) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::ArticulatedDynamicsManagerMP::CallSimulate(float, unsigned int, float)
// vaddr 0x232d284 | ghidra 0x242d284 | size 4 | symbol _ZN4Aska28ArticulatedDynamicsManagerMP12CallSimulateEfjf | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska28ArticulatedDynamicsManagerMP12CallSimulateEfjf(void)

{
  (*(code *)PTR__ZN4Aska28ArticulatedDynamicsManagerMP8SimulateEfjf_02ca16b8)();
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

// ==== Aska::ADMJoint::ExternalForceMP(float, float, float, Aska::Vector const*, Aska::ADM_CALC_DATA*, bool)
// vaddr 0x232f31c | ghidra 0x242f31c | size 340 | symbol _ZN4Aska8ADMJoint15ExternalForceMPEfffPKNS_6VectorEPNS_13ADM_CALC_DATAEb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8ADMJoint15ExternalForceMPEfffPKNS_6VectorEPNS_13ADM_CALC_DATAEb
               (float param_1,float param_2,long param_3,float *param_4,long param_5,uint param_6)

{
  undefined4 uVar1;
  undefined4 uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  if ((*(byte *)(param_3 + 0x19c) & 1) == 0) {
    if (((*(byte *)(param_3 + 0x19d) >> 1 & 1) == 0) && ((param_6 & 1) == 0)) {
      fVar6 = *(float *)(param_3 + 0x50);
      fVar4 = *(float *)(param_3 + 0x54);
      fVar3 = *(float *)(param_3 + 0x58);
    }
    else {
      if (*(float *)(param_3 + 0x180) <= 0.0) {
        fVar6 = *(float *)(param_3 + 0x50);
        fVar5 = 0.0;
        fVar8 = 0.0;
        fVar7 = 0.0;
        fVar4 = *(float *)(param_3 + 0x54);
        fVar3 = *(float *)(param_3 + 0x58);
      }
      else {
        if ((param_6 & 1) == 0) {
          if ((*(char *)(param_3 + 0x19b) == '\0') || (0.0 <= *(float *)(param_3 + 0x54))) {
            fVar7 = *(float *)(param_3 + 0x178);
          }
          else {
            fVar7 = *(float *)(param_3 + 0x17c);
          }
        }
        else {
          fVar7 = 1.0;
        }
        fVar6 = *(float *)(param_3 + 0x50);
        fVar7 = fVar7 / *(float *)(param_3 + 0x180);
        if (param_2 <= fVar7) {
          fVar7 = param_2;
        }
        fVar4 = *(float *)(param_3 + 0x54);
        fVar3 = *(float *)(param_3 + 0x58);
        fVar5 = 0.0 - fVar6 * fVar7;
        fVar8 = 0.0 - fVar4 * fVar7;
        fVar7 = 0.0 - fVar7 * fVar3;
      }
      fVar6 = fVar5 * param_1 + fVar6;
      fVar4 = fVar8 * param_1 + fVar4;
      fVar3 = fVar7 * param_1 + fVar3;
      *(float *)(param_3 + 0x50) = fVar6;
      *(float *)(param_3 + 0x54) = fVar4;
      *(float *)(param_3 + 0x58) = fVar3;
    }
    fVar5 = *(float *)(param_3 + 0x10) + fVar6 * param_1;
    fVar6 = *(float *)(param_3 + 0x14) + fVar4 * param_1;
    fVar4 = *(float *)(param_3 + 0x18) + fVar3 * param_1;
    if ((*(byte *)(param_3 + 0x19d) >> 6 & 1) != 0) {
      fVar5 = fVar5 + *param_4 * param_1;
      fVar6 = fVar6 + param_4[1] * param_1;
      fVar4 = fVar4 + param_4[2] * param_1;
    }
    *(float *)(param_3 + 0x10) = fVar5;
    *(float *)(param_3 + 0x14) = fVar6;
    *(float *)(param_3 + 0x18) = fVar4;
  }
  else {
    uVar1 = *(undefined4 *)(param_5 + 0x1c);
    uVar2 = *(undefined4 *)(param_5 + 0x2c);
    *(undefined4 *)(param_3 + 0x10) = *(undefined4 *)(param_5 + 0xc);
    *(undefined4 *)(param_3 + 0x14) = uVar1;
    *(undefined4 *)(param_3 + 0x18) = uVar2;
  }
  *(undefined4 *)(param_3 + 0x1c) = 0x3f800000;
  return;
}
