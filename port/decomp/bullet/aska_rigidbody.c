// port/decomp/bullet/aska_rigidbody.c: Ghidra decompiles for the bullet subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:11 UTC: tools/decomp.sh '--into' 'bullet/aska_rigidbody' 'Aska::RigidBodyManager::' 'Aska::Global::InstantiateRigidBodyManager' 'Aska::AsfHandler::SetupRigidBodyPrimitive' 'Aska::AsfHandler::SetupRigidBodyConstraint' 'Aska::AsfHandler::ClearRigidBodyPrimitiveList' 'Aska::AsfHandler::RemoveRigidBodyPrimitive' 'Aska::RigidBodyPrimitiveBase::LocalCreateBullet' 'Aska::RigidBodyPrimitiveSphere::CreateBullet' 'Aska::RigidBodyConstraintBase::Attach' 'Aska::RigidBodyConstraintHinge::CreateBullet'

// ==== Aska::AsfHandler::ClearRigidBodyPrimitiveList()
// vaddr 0x20ceec0 | ghidra 0x21ceec0 | size 364 | symbol _ZN4Aska10AsfHandler27ClearRigidBodyPrimitiveListEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AsfHandler27ClearRigidBodyPrimitiveListEv(long param_1)

{
  uint uVar1;
  undefined8 *puVar2;
  long *plVar3;
  long lVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  
  lVar4 = *(long *)(param_1 + 0x500);
  if (lVar4 != 0) {
    Aska::AsfHandler::RemoveRigidBodyPrimitive()(param_1);
    uVar1 = *(uint *)(lVar4 + 0x10);
    plVar3 = *(long **)(param_1 + 0x4f8);
    if (uVar1 != 0) {
      puVar2 = (undefined8 *)*plVar3;
      puVar5 = puVar2;
      do {
        puVar6 = puVar5 + 9;
        (**(code **)*puVar5)(puVar5);
        puVar5 = puVar6;
      } while (puVar6 < puVar2 + (ulong)uVar1 * 9);
      plVar3 = *(long **)(param_1 + 0x4f8);
    }
    uVar1 = *(uint *)(lVar4 + 0x14);
    if (uVar1 != 0) {
      puVar2 = (undefined8 *)plVar3[1];
      puVar5 = puVar2;
      do {
        puVar6 = puVar5 + 9;
        (**(code **)*puVar5)(puVar5);
        puVar5 = puVar6;
      } while (puVar6 < puVar2 + (ulong)uVar1 * 9);
      plVar3 = *(long **)(param_1 + 0x4f8);
    }
    uVar1 = *(uint *)(lVar4 + 0x18);
    if (uVar1 != 0) {
      puVar2 = (undefined8 *)plVar3[2];
      puVar5 = puVar2;
      do {
        puVar6 = puVar5 + 9;
        (**(code **)*puVar5)(puVar5);
        puVar5 = puVar6;
      } while (puVar6 < puVar2 + (ulong)uVar1 * 9);
      plVar3 = *(long **)(param_1 + 0x4f8);
    }
    uVar1 = *(uint *)(lVar4 + 0x1c);
    if (uVar1 != 0) {
      puVar2 = (undefined8 *)plVar3[3];
      puVar5 = puVar2;
      do {
        puVar6 = puVar5 + 9;
        (**(code **)*puVar5)(puVar5);
        puVar5 = puVar6;
      } while (puVar6 < puVar2 + (ulong)uVar1 * 9);
      plVar3 = *(long **)(param_1 + 0x4f8);
    }
    uVar1 = *(uint *)(lVar4 + 0x20);
    if (uVar1 != 0) {
      puVar2 = (undefined8 *)plVar3[4];
      puVar5 = puVar2;
      do {
        puVar6 = puVar5 + 9;
        (**(code **)*puVar5)(puVar5);
        puVar5 = puVar6;
      } while (puVar6 < puVar2 + (ulong)uVar1 * 9);
      plVar3 = *(long **)(param_1 + 0x4f8);
    }
    uVar1 = *(uint *)(lVar4 + 0x24);
    if (uVar1 != 0) {
      puVar2 = (undefined8 *)plVar3[5];
      puVar5 = puVar2;
      do {
        puVar6 = puVar5 + 9;
        (**(code **)*puVar5)(puVar5);
        puVar5 = puVar6;
      } while (puVar6 < puVar2 + (ulong)uVar1 * 9);
    }
    *(undefined8 *)(param_1 + 0x500) = 0;
  }
  return;
}

// ==== Aska::AsfHandler::SetupRigidBodyPrimitive()
// vaddr 0x20cf088 | ghidra 0x21cf088 | size 1012 | symbol _ZN4Aska10AsfHandler23SetupRigidBodyPrimitiveEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10AsfHandler23SetupRigidBodyPrimitiveEv(long param_1)

{
  int iVar1;
  long lVar2;
  ulong uVar3;
  ulong *puVar4;
  undefined8 uVar5;
  long *plVar6;
  int *piVar7;
  long lVar8;
  long *plVar9;
  
  lVar8 = *(long *)(param_1 + 0x500);
  if (lVar8 != 0) {
    piVar7 = (int *)(lVar8 + 0x30);
    uVar5 = *(undefined8 *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48;
    puVar4 = *(ulong **)(param_1 + 0x4f8);
    if (*(uint *)(lVar8 + 0x10) != 0) {
      plVar6 = (long *)*puVar4;
      plVar9 = plVar6 + (ulong)*(uint *)(lVar8 + 0x10) * 9;
      do {
        iVar1 = *piVar7;
        if (iVar1 < 0) {
          if ((*(long *)(param_1 + 0x78) == 0) || (*(long *)(param_1 + 0x508) == 0)) {
            lVar2 = 0;
          }
          else {
            lVar2 = Aska::AsfHandler::QuickSearchExternalLinkByName(char const*) const(param_1,*(long *)(param_1 + 0x78) +
                                            (long)(int)(iVar1 << 5 ^ 0xffffffe0) + 0x20);
          }
        }
        else {
          lVar2 = *(long *)(*(long *)(*(long *)(param_1 + 0xd8) + (long)iVar1 * 8) + 0x38);
        }
        plVar6[4] = lVar2;
        if ((plVar6[6] == 0) && (uVar3 = (**(code **)(*plVar6 + 0x68))(plVar6), (uVar3 & 1) == 0)) {
          return 0;
        }
        Aska::RigidBodyManager::Add(Aska::RigidBodyPrimitiveBase*)(uVar5,plVar6);
        plVar6 = plVar6 + 9;
        piVar7 = piVar7 + 0x10;
      } while (plVar6 < plVar9);
      puVar4 = *(ulong **)(param_1 + 0x4f8);
    }
    if (*(uint *)(lVar8 + 0x14) != 0) {
      plVar6 = (long *)puVar4[1];
      plVar9 = plVar6 + (ulong)*(uint *)(lVar8 + 0x14) * 9;
      do {
        iVar1 = *piVar7;
        if (iVar1 < 0) {
          if ((*(long *)(param_1 + 0x78) == 0) || (*(long *)(param_1 + 0x508) == 0)) {
            lVar2 = 0;
          }
          else {
            lVar2 = Aska::AsfHandler::QuickSearchExternalLinkByName(char const*) const(param_1,*(long *)(param_1 + 0x78) +
                                            (long)(int)(iVar1 << 5 ^ 0xffffffe0) + 0x20);
          }
        }
        else {
          lVar2 = *(long *)(*(long *)(*(long *)(param_1 + 0xd8) + (long)iVar1 * 8) + 0x38);
        }
        plVar6[4] = lVar2;
        if ((plVar6[6] == 0) && (uVar3 = (**(code **)(*plVar6 + 0x68))(plVar6), (uVar3 & 1) == 0)) {
          return 0;
        }
        Aska::RigidBodyManager::Add(Aska::RigidBodyPrimitiveBase*)(uVar5,plVar6);
        plVar6 = plVar6 + 9;
        piVar7 = piVar7 + 0x10;
      } while (plVar6 < plVar9);
      puVar4 = *(ulong **)(param_1 + 0x4f8);
    }
    if (*(uint *)(lVar8 + 0x18) != 0) {
      plVar6 = (long *)puVar4[2];
      plVar9 = plVar6 + (ulong)*(uint *)(lVar8 + 0x18) * 9;
      do {
        iVar1 = *piVar7;
        if (iVar1 < 0) {
          if ((*(long *)(param_1 + 0x78) == 0) || (*(long *)(param_1 + 0x508) == 0)) {
            lVar2 = 0;
          }
          else {
            lVar2 = Aska::AsfHandler::QuickSearchExternalLinkByName(char const*) const(param_1,*(long *)(param_1 + 0x78) +
                                            (long)(int)(iVar1 << 5 ^ 0xffffffe0) + 0x20);
          }
        }
        else {
          lVar2 = *(long *)(*(long *)(*(long *)(param_1 + 0xd8) + (long)iVar1 * 8) + 0x38);
        }
        plVar6[4] = lVar2;
        if ((plVar6[6] == 0) && (uVar3 = (**(code **)(*plVar6 + 0x68))(plVar6), (uVar3 & 1) == 0)) {
          return 0;
        }
        Aska::RigidBodyManager::Add(Aska::RigidBodyPrimitiveBase*)(uVar5,plVar6);
        plVar6 = plVar6 + 9;
        piVar7 = piVar7 + 0x10;
      } while (plVar6 < plVar9);
      puVar4 = *(ulong **)(param_1 + 0x4f8);
    }
    if (*(uint *)(lVar8 + 0x1c) != 0) {
      plVar6 = (long *)puVar4[3];
      plVar9 = plVar6 + (ulong)*(uint *)(lVar8 + 0x1c) * 9;
      do {
        iVar1 = *piVar7;
        if (iVar1 < 0) {
          if ((*(long *)(param_1 + 0x78) == 0) || (*(long *)(param_1 + 0x508) == 0)) {
            lVar2 = 0;
          }
          else {
            lVar2 = Aska::AsfHandler::QuickSearchExternalLinkByName(char const*) const(param_1,*(long *)(param_1 + 0x78) +
                                            (long)(int)(iVar1 << 5 ^ 0xffffffe0) + 0x20);
          }
        }
        else {
          lVar2 = *(long *)(*(long *)(*(long *)(param_1 + 0xd8) + (long)iVar1 * 8) + 0x38);
        }
        plVar6[4] = lVar2;
        if ((plVar6[6] == 0) && (uVar3 = (**(code **)(*plVar6 + 0x68))(plVar6), (uVar3 & 1) == 0)) {
          return 0;
        }
        Aska::RigidBodyManager::Add(Aska::RigidBodyPrimitiveBase*)(uVar5,plVar6);
        plVar6 = plVar6 + 9;
        piVar7 = piVar7 + 0x10;
      } while (plVar6 < plVar9);
      puVar4 = *(ulong **)(param_1 + 0x4f8);
    }
    if (*(uint *)(lVar8 + 0x20) != 0) {
      plVar6 = (long *)puVar4[4];
      plVar9 = plVar6 + (ulong)*(uint *)(lVar8 + 0x20) * 9;
      do {
        iVar1 = *piVar7;
        if (iVar1 < 0) {
          if ((*(long *)(param_1 + 0x78) == 0) || (*(long *)(param_1 + 0x508) == 0)) {
            lVar2 = 0;
          }
          else {
            lVar2 = Aska::AsfHandler::QuickSearchExternalLinkByName(char const*) const(param_1,*(long *)(param_1 + 0x78) +
                                            (long)(int)(iVar1 << 5 ^ 0xffffffe0) + 0x20);
          }
        }
        else {
          lVar2 = *(long *)(*(long *)(*(long *)(param_1 + 0xd8) + (long)iVar1 * 8) + 0x38);
        }
        plVar6[4] = lVar2;
        if ((plVar6[6] == 0) && (uVar3 = (**(code **)(*plVar6 + 0x68))(plVar6), (uVar3 & 1) == 0)) {
          return 0;
        }
        Aska::RigidBodyManager::Add(Aska::RigidBodyPrimitiveBase*)(uVar5,plVar6);
        plVar6 = plVar6 + 9;
        piVar7 = piVar7 + 0x10;
      } while (plVar6 < plVar9);
      puVar4 = *(ulong **)(param_1 + 0x4f8);
    }
    if (*(uint *)(lVar8 + 0x24) != 0) {
      plVar6 = (long *)puVar4[5];
      plVar9 = plVar6 + (ulong)*(uint *)(lVar8 + 0x24) * 9;
      do {
        iVar1 = *piVar7;
        if (iVar1 < 0) {
          if ((*(long *)(param_1 + 0x78) == 0) || (*(long *)(param_1 + 0x508) == 0)) {
            lVar8 = 0;
          }
          else {
            lVar8 = Aska::AsfHandler::QuickSearchExternalLinkByName(char const*) const(param_1,*(long *)(param_1 + 0x78) +
                                            (long)(int)(iVar1 << 5 ^ 0xffffffe0) + 0x20);
          }
        }
        else {
          lVar8 = *(long *)(*(long *)(*(long *)(param_1 + 0xd8) + (long)iVar1 * 8) + 0x38);
        }
        plVar6[4] = lVar8;
        if ((plVar6[6] == 0) && (uVar3 = (**(code **)(*plVar6 + 0x68))(plVar6), (uVar3 & 1) == 0)) {
          return 0;
        }
        Aska::RigidBodyManager::Add(Aska::RigidBodyPrimitiveBase*)(uVar5,plVar6);
        plVar6 = plVar6 + 9;
        piVar7 = piVar7 + 0x10;
      } while (plVar6 < plVar9);
    }
  }
  return 1;
}

// ==== Aska::AsfHandler::SetupRigidBodyConstraint()
// vaddr 0x20cf47c | ghidra 0x21cf47c | size 428 | symbol _ZN4Aska10AsfHandler24SetupRigidBodyConstraintEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10AsfHandler24SetupRigidBodyConstraintEv(long param_1)

{
  uint uVar1;
  long *plVar2;
  long lVar3;
  ulong uVar4;
  
  if (0 < *(int *)(param_1 + 0xb0)) {
    uVar1 = *(uint *)(param_1 + 0x140);
    if (uVar1 != 0) {
      uVar4 = 0;
      do {
        lVar3 = *(long *)(*(long *)(*(long *)(param_1 + 0x390) + uVar4 * 8) + 0x38);
        if (((lVar3 != 0) && (plVar2 = *(long **)(lVar3 + 0x198), plVar2 != (long *)0x0)) &&
           (plVar2[8] == 0)) {
          (**(code **)(*plVar2 + 0x68))();
        }
        uVar4 = uVar4 + 1;
      } while (uVar1 != uVar4);
      if (*(int *)(param_1 + 0xb0) < 1) {
        return 1;
      }
    }
    uVar1 = *(uint *)(param_1 + 0x144);
    if (uVar1 != 0) {
      uVar4 = 0;
      do {
        lVar3 = *(long *)(*(long *)(*(long *)(param_1 + 0x398) + uVar4 * 8) + 0x38);
        if (((lVar3 != 0) && (plVar2 = *(long **)(lVar3 + 0x198), plVar2 != (long *)0x0)) &&
           (plVar2[8] == 0)) {
          (**(code **)(*plVar2 + 0x68))();
        }
        uVar4 = uVar4 + 1;
      } while (uVar1 != uVar4);
      if (*(int *)(param_1 + 0xb0) < 1) {
        return 1;
      }
    }
    uVar1 = *(uint *)(param_1 + 0x148);
    if (uVar1 != 0) {
      uVar4 = 0;
      do {
        lVar3 = *(long *)(*(long *)(*(long *)(param_1 + 0x3a0) + uVar4 * 8) + 0x38);
        if (((lVar3 != 0) && (plVar2 = *(long **)(lVar3 + 0x198), plVar2 != (long *)0x0)) &&
           (plVar2[8] == 0)) {
          (**(code **)(*plVar2 + 0x68))();
        }
        uVar4 = uVar4 + 1;
      } while (uVar1 != uVar4);
      if (*(int *)(param_1 + 0xb0) < 1) {
        return 1;
      }
    }
    uVar1 = *(uint *)(param_1 + 0x14c);
    if (uVar1 != 0) {
      uVar4 = 0;
      do {
        lVar3 = *(long *)(*(long *)(*(long *)(param_1 + 0x3a8) + uVar4 * 8) + 0x38);
        if (((lVar3 != 0) && (plVar2 = *(long **)(lVar3 + 0x198), plVar2 != (long *)0x0)) &&
           (plVar2[8] == 0)) {
          (**(code **)(*plVar2 + 0x68))();
        }
        uVar4 = uVar4 + 1;
      } while (uVar1 != uVar4);
      if (*(int *)(param_1 + 0xb0) < 1) {
        return 1;
      }
    }
    uVar1 = *(uint *)(param_1 + 0x150);
    if (uVar1 != 0) {
      uVar4 = 0;
      do {
        lVar3 = *(long *)(*(long *)(*(long *)(param_1 + 0x3b0) + uVar4 * 8) + 0x38);
        if (((lVar3 != 0) && (plVar2 = *(long **)(lVar3 + 0x198), plVar2 != (long *)0x0)) &&
           (plVar2[8] == 0)) {
          (**(code **)(*plVar2 + 0x68))();
        }
        uVar4 = uVar4 + 1;
      } while (uVar1 != uVar4);
    }
  }
  return 1;
}

// ==== Aska::AsfHandler::RemoveRigidBodyPrimitive()
// vaddr 0x20d0850 | ghidra 0x21d0850 | size 340 | symbol _ZN4Aska10AsfHandler24RemoveRigidBodyPrimitiveEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10AsfHandler24RemoveRigidBodyPrimitiveEv(long param_1)

{
  ulong *puVar1;
  undefined8 uVar2;
  ulong uVar3;
  long lVar4;
  ulong uVar5;
  
  lVar4 = *(long *)(param_1 + 0x500);
  if (lVar4 != 0) {
    uVar2 = *(undefined8 *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48;
    puVar1 = *(ulong **)(param_1 + 0x4f8);
    if (*(uint *)(lVar4 + 0x10) != 0) {
      uVar3 = *puVar1;
      uVar5 = uVar3 + (ulong)*(uint *)(lVar4 + 0x10) * 0x48;
      do {
        Aska::RigidBodyManager::Remove(Aska::RigidBodyPrimitiveBase*)(uVar2,uVar3);
        uVar3 = uVar3 + 0x48;
      } while (uVar3 < uVar5);
      puVar1 = *(ulong **)(param_1 + 0x4f8);
    }
    if (*(uint *)(lVar4 + 0x14) != 0) {
      uVar3 = puVar1[1];
      uVar5 = uVar3 + (ulong)*(uint *)(lVar4 + 0x14) * 0x48;
      do {
        Aska::RigidBodyManager::Remove(Aska::RigidBodyPrimitiveBase*)(uVar2,uVar3);
        uVar3 = uVar3 + 0x48;
      } while (uVar3 < uVar5);
      puVar1 = *(ulong **)(param_1 + 0x4f8);
    }
    if (*(uint *)(lVar4 + 0x18) != 0) {
      uVar3 = puVar1[2];
      uVar5 = uVar3 + (ulong)*(uint *)(lVar4 + 0x18) * 0x48;
      do {
        Aska::RigidBodyManager::Remove(Aska::RigidBodyPrimitiveBase*)(uVar2,uVar3);
        uVar3 = uVar3 + 0x48;
      } while (uVar3 < uVar5);
      puVar1 = *(ulong **)(param_1 + 0x4f8);
    }
    if (*(uint *)(lVar4 + 0x1c) != 0) {
      uVar3 = puVar1[3];
      uVar5 = uVar3 + (ulong)*(uint *)(lVar4 + 0x1c) * 0x48;
      do {
        Aska::RigidBodyManager::Remove(Aska::RigidBodyPrimitiveBase*)(uVar2,uVar3);
        uVar3 = uVar3 + 0x48;
      } while (uVar3 < uVar5);
      puVar1 = *(ulong **)(param_1 + 0x4f8);
    }
    if (*(uint *)(lVar4 + 0x20) != 0) {
      uVar3 = puVar1[4];
      uVar5 = uVar3 + (ulong)*(uint *)(lVar4 + 0x20) * 0x48;
      do {
        Aska::RigidBodyManager::Remove(Aska::RigidBodyPrimitiveBase*)(uVar2,uVar3);
        uVar3 = uVar3 + 0x48;
      } while (uVar3 < uVar5);
      puVar1 = *(ulong **)(param_1 + 0x4f8);
    }
    if (*(uint *)(lVar4 + 0x24) != 0) {
      uVar3 = puVar1[5];
      uVar5 = uVar3 + (ulong)*(uint *)(lVar4 + 0x24) * 0x48;
      do {
        Aska::RigidBodyManager::Remove(Aska::RigidBodyPrimitiveBase*)(uVar2,uVar3);
        uVar3 = uVar3 + 0x48;
      } while (uVar3 < uVar5);
    }
  }
  return;
}

// ==== Aska::RigidBodyConstraintBase::Attach(Aska::AsfHandler const*, Aska::AFF::AskaChunk const*)
// vaddr 0x234be5c | ghidra 0x244be5c | size 96 | symbol _ZN4Aska23RigidBodyConstraintBase6AttachEPKNS_10AsfHandlerEPKNS_3AFF9AskaChunkE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska23RigidBodyConstraintBase6AttachEPKNS_10AsfHandlerEPKNS_3AFF9AskaChunkE
          (long param_1,undefined8 param_2,long param_3)

{
  long lVar1;
  
  *(long *)(param_1 + 0x28) = param_3;
  if ((-1 < *(int *)(param_3 + 0x104)) &&
     (lVar1 = Aska::AsfHandler::SearchRigidBody(int, int) const(param_2,*(undefined1 *)(param_3 + 0x100)), lVar1 != 0)) {
    *(long *)(param_1 + 0x30) = lVar1;
  }
  if ((-1 < *(int *)(param_3 + 0x108)) &&
     (lVar1 = Aska::AsfHandler::SearchRigidBody(int, int) const(param_2,*(undefined1 *)(param_3 + 0x101)), lVar1 != 0)) {
    *(long *)(param_1 + 0x38) = lVar1;
  }
  return 1;
}

// ==== Aska::RigidBodyConstraintHinge::CreateBullet()
// vaddr 0x234c150 | ghidra 0x244c150 | size 1256 | symbol _ZN4Aska24RigidBodyConstraintHinge12CreateBulletEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska24RigidBodyConstraintHinge12CreateBulletEv(long param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  long lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  byte bVar9;
  long lVar10;
  undefined8 uVar11;
  long *plVar12;
  long *plVar13;
  long lVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  undefined4 uVar19;
  float fVar20;
  undefined4 uVar21;
  float fVar22;
  undefined4 uVar23;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined8 uStack_80;
  undefined8 uStack_78;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  undefined4 uStack_64;
  
  lVar10 = *(long *)(param_1 + 0x30);
  if ((lVar10 != 0) && (plVar13 = *(long **)(lVar10 + 0x20), plVar13 != (long *)0x0)) {
    uVar11 = *(undefined8 *)(lVar10 + 0x30);
    plVar12 = *(long **)(param_1 + 0x20);
    if ((*(byte *)(plVar13 + 0x25) & 1) != 0) {
      (**(code **)(*plVar13 + 0xa8))(plVar13);
    }
    if ((*(byte *)(plVar12 + 0x25) & 1) != 0) {
      (**(code **)(*plVar12 + 0xa8))(plVar12);
    }
    fVar18 = *(float *)((long)plVar12 + 0x4c);
    fVar20 = *(float *)((long)plVar12 + 0x5c);
    fVar22 = *(float *)((long)plVar12 + 0x6c);
    uStack_64 = 0;
    fStack_70 = fVar18 - *(float *)((long)plVar13 + 0x4c);
    fStack_6c = fVar20 - *(float *)((long)plVar13 + 0x5c);
    fStack_68 = fVar22 - *(float *)((long)plVar13 + 0x6c);
    uVar8 = (**(code **)(*plVar12 + 0x98))(plVar12);
    uVar7 = _UNK_027ed898;
    uVar6 = _UNK_027ed890;
    lVar14 = _UNK_027dbb38;
    lVar10 = _UNK_027dbb30;
    uStack_78 = _UNK_027ed898;
    uStack_80 = _UNK_027ed890;
    bVar9 = *(byte *)(plVar13 + 0x25);
    if ((bVar9 >> 2 & 1) == 0) {
      if ((*(byte *)((long)plVar13 + 0x129) & 3) == 0) {
        fVar15 = *(float *)((long)plVar13 + 0x4c);
        fVar16 = *(float *)((long)plVar13 + 0x5c);
        fVar17 = *(float *)((long)plVar13 + 0x6c);
        plVar13[0x27] = CONCAT44((int)plVar13[0xe],*(float *)(plVar13 + 0xc));
        plVar13[0x26] = CONCAT44(*(float *)(plVar13 + 10),*(float *)(plVar13 + 8));
        plVar13[0x29] =
             CONCAT44(*(undefined4 *)((long)plVar13 + 0x74),*(float *)((long)plVar13 + 100));
        plVar13[0x28] = CONCAT44(*(float *)((long)plVar13 + 0x54),*(float *)((long)plVar13 + 0x44));
        *(float *)((long)plVar13 + 0x13c) =
             -(*(float *)(plVar13 + 8) * fVar15 + *(float *)(plVar13 + 10) * fVar16 +
              *(float *)(plVar13 + 0xc) * fVar17);
        *(float *)((long)plVar13 + 0x14c) =
             -(fVar15 * *(float *)((long)plVar13 + 0x44) + fVar16 * *(float *)((long)plVar13 + 0x54)
              + fVar17 * *(float *)((long)plVar13 + 100));
        plVar13[0x2b] = CONCAT44((int)plVar13[0xf],*(float *)(plVar13 + 0xd));
        plVar13[0x2a] = CONCAT44(*(float *)(plVar13 + 0xb),*(float *)(plVar13 + 9));
        plVar13[0x2d] = lVar14;
        plVar13[0x2c] = lVar10;
        *(float *)((long)plVar13 + 0x15c) =
             -(fVar15 * *(float *)(plVar13 + 9) + fVar16 * *(float *)(plVar13 + 0xb) +
              fVar17 * *(float *)(plVar13 + 0xd));
      }
      else {
        Aska::Matrix::InvertLowError(Aska::Matrix*) const(plVar13 + 8,plVar13 + 0x26);
        bVar9 = *(byte *)(plVar13 + 0x25);
      }
      *(byte *)(plVar13 + 0x25) = bVar9 | 4;
    }
    Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(&uStack_80,plVar13 + 0x26);
    Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(&uStack_80,uVar8);
    uStack_90 = (undefined4)uStack_80;
    uStack_8c = uStack_80._4_4_;
    uStack_88 = (undefined4)uStack_78;
    uStack_84 = 0;
    lVar10 = *(long *)(param_1 + 0x38);
    if ((lVar10 == 0) || (lVar14 = *(long *)(lVar10 + 0x30), lVar14 == 0)) {
      lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x318,PTR__ZSt7nothrow_02cb9a80);
      if (lVar10 == 0) {
        return 0;
      }
      btHingeConstraint::btHingeConstraint(btRigidBody&, btVector3 const&, btVector3&, bool)(lVar10,uVar11,&fStack_70,&uStack_90,0);
      if (lVar10 != 0) {
code_r0x0244c528:
        fVar20 = _UNK_027edb34;
        lVar14 = *(long *)(param_1 + 0x28);
        uVar23 = *(undefined4 *)(lVar14 + 0x110);
        uVar1 = *(undefined4 *)(lVar14 + 0x114);
        uVar2 = *(undefined4 *)(lVar14 + 0x118);
        uVar3 = *(undefined4 *)(lVar14 + 0x128);
        uVar19 = *(undefined4 *)(lVar14 + 0x120);
        uVar21 = *(undefined4 *)(lVar14 + 0x124);
        fVar22 = (float)fmodf(*(undefined4 *)(lVar14 + 0x10c),_UNK_027edb34);
        fVar18 = _UNK_027edb30;
        if (_UNK_027edb30 <= fVar22) {
          if (_UNK_027e3fd0 < fVar22) {
            fVar22 = fVar22 + _UNK_027edb3c;
          }
        }
        else {
          fVar22 = fVar22 + fVar20;
        }
        *(float *)(lVar10 + 0x2ec) = fVar22;
        fVar22 = (float)fmodf(uVar23,fVar20);
        if (fVar18 <= fVar22) {
          if (_UNK_027e3fd0 < fVar22) {
            fVar22 = fVar22 + _UNK_027edb3c;
          }
        }
        else {
          fVar22 = fVar22 + fVar20;
        }
        *(float *)(lVar10 + 0x2f0) = fVar22;
        *(undefined4 *)(lVar10 + 0x2e4) = uVar1;
        *(undefined4 *)(lVar10 + 0x2e8) = uVar2;
        *(undefined4 *)(lVar10 + 0x2e0) = 0x3f666666;
        iVar4 = *(int *)(*(long *)(param_1 + 0x28) + 0x11c);
        *(undefined4 *)(lVar10 + 0x2dc) = uVar3;
        *(bool *)(lVar10 + 0x30d) = iVar4 != 0;
        btHingeConstraint::setMotorTarget(float, float)(uVar19,uVar21,lVar10);
        (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28)
                    + 0x50))
                  (*(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28),
                   lVar10,0);
        *(long *)(param_1 + 0x40) = lVar10;
        return 1;
      }
    }
    else {
      plVar13 = *(long **)(lVar10 + 0x20);
      if (plVar13 != (long *)0x0) {
        bVar9 = *(byte *)(plVar13 + 0x25);
        if ((bVar9 & 1) != 0) {
          (**(code **)(*plVar13 + 0xa8))(plVar13);
          bVar9 = *(byte *)(plVar13 + 0x25);
        }
        lVar5 = _UNK_027dbb38;
        lVar10 = _UNK_027dbb30;
        fVar16 = *(float *)((long)plVar13 + 0x4c);
        fVar17 = *(float *)((long)plVar13 + 0x5c);
        fVar15 = *(float *)((long)plVar13 + 0x6c);
        uStack_94 = 0;
        fStack_a0 = fVar18 - fVar16;
        fStack_9c = fVar20 - fVar17;
        fStack_98 = fVar22 - fVar15;
        uStack_a8 = uVar7;
        uStack_b0 = uVar6;
        if ((bVar9 >> 2 & 1) == 0) {
          if ((*(byte *)((long)plVar13 + 0x129) & 3) == 0) {
            plVar13[0x27] = CONCAT44((int)plVar13[0xe],*(float *)(plVar13 + 0xc));
            plVar13[0x26] = CONCAT44(*(float *)(plVar13 + 10),*(float *)(plVar13 + 8));
            plVar13[0x29] =
                 CONCAT44(*(undefined4 *)((long)plVar13 + 0x74),*(float *)((long)plVar13 + 100));
            plVar13[0x28] =
                 CONCAT44(*(float *)((long)plVar13 + 0x54),*(float *)((long)plVar13 + 0x44));
            *(float *)((long)plVar13 + 0x13c) =
                 -(*(float *)(plVar13 + 8) * fVar16 + *(float *)(plVar13 + 10) * fVar17 +
                  *(float *)(plVar13 + 0xc) * fVar15);
            *(float *)((long)plVar13 + 0x14c) =
                 -(fVar16 * *(float *)((long)plVar13 + 0x44) +
                   fVar17 * *(float *)((long)plVar13 + 0x54) +
                  fVar15 * *(float *)((long)plVar13 + 100));
            plVar13[0x2b] = CONCAT44((int)plVar13[0xf],*(float *)(plVar13 + 0xd));
            plVar13[0x2a] = CONCAT44(*(float *)(plVar13 + 0xb),*(float *)(plVar13 + 9));
            plVar13[0x2d] = lVar5;
            plVar13[0x2c] = lVar10;
            *(float *)((long)plVar13 + 0x15c) =
                 -(fVar16 * *(float *)(plVar13 + 9) + fVar17 * *(float *)(plVar13 + 0xb) +
                  fVar15 * *(float *)(plVar13 + 0xd));
          }
          else {
            Aska::Matrix::InvertLowError(Aska::Matrix*) const(plVar13 + 8,plVar13 + 0x26);
            bVar9 = *(byte *)(plVar13 + 0x25);
          }
          *(byte *)(plVar13 + 0x25) = bVar9 | 4;
        }
        Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(&uStack_b0,plVar13 + 0x26);
        Aska::Vector::ApplyMatrixNoTransport(Aska::Matrix const*)(&uStack_b0,uVar8);
        uStack_c0 = (undefined4)uStack_b0;
        uStack_bc = uStack_b0._4_4_;
        uStack_b8 = (undefined4)uStack_a8;
        uStack_b4 = 0;
        lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x318,PTR__ZSt7nothrow_02cb9a80);
        if (lVar10 != 0) {
          btHingeConstraint::btHingeConstraint(btRigidBody&, btRigidBody&, btVector3 const&, btVector3 const&, btVector3&, btVector3&, bool)(lVar10,uVar11,lVar14,&fStack_70,&fStack_a0,&uStack_90,&uStack_c0,0);
          goto code_r0x0244c528;
        }
      }
    }
  }
  return 0;
}

// ==== Aska::Global::InstantiateRigidBodyManager()
// vaddr 0x234d84c | ghidra 0x244d84c | size 308 | symbol _ZN4Aska6Global27InstantiateRigidBodyManagerEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Global27InstantiateRigidBodyManagerEv(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined4 uVar4;
  long *plVar5;
  ulong uVar6;
  undefined8 uVar7;
  code *pcVar8;
  long lVar9;
  
  lVar9 = *(long *)PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620;
  if (lVar9 == 0) {
    uVar7 = 0;
  }
  else {
    plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xa8,PTR__ZSt7nothrow_02cb9a80);
    puVar1 = PTR__ZTVN4Aska4TaskE_02cbe020;
    if (plVar5 == (long *)0x0) {
      *(undefined8 *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 = 0;
      uVar7 = 0;
    }
    else {
      plVar5[2] = 0;
      plVar5[1] = 0;
      pcVar8 = *(code **)(puVar1 + 0x68);
      *plVar5 = (long)(puVar1 + 0x10);
      plVar5[3] = 0;
      *(undefined2 *)((long)plVar5 + 0x24) = 0;
      *(undefined1 *)((long)plVar5 + 0x26) = 0;
      uVar4 = (*pcVar8)(plVar5);
      *(undefined4 *)(plVar5 + 4) = uVar4;
      puVar2 = PTR__ZTVN4Aska16RigidBodyManagerE_02cbcdf8;
      *(undefined1 *)(plVar5 + 0xe) = 1;
      plVar5[0xc] = (long)(plVar5 + 0xb);
      plVar5[0xd] = (long)(plVar5 + 0xb);
      puVar1 = PTR__ZTVN4Aska5TListINS_22RigidBodyPrimitiveBaseEEE_02cb9770;
      *plVar5 = (long)(puVar2 + 0x10);
      puVar3 = PTR__ZTVN4Aska22RigidBodyPrimitiveBaseE_02cc25b8;
      plVar5[0x13] = 0;
      plVar5[0x12] = 0;
      plVar5[0x11] = 0;
      *(undefined4 *)(plVar5 + 0x14) = 0;
      plVar5[0x10] = 0;
      plVar5[0xf] = 0;
      plVar5[9] = 0;
      plVar5[8] = 0;
      plVar5[7] = 0;
      plVar5[6] = 0;
      plVar5[5] = 0;
      puVar2 = PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48;
      plVar5[0xb] = (long)(puVar3 + 0x10);
      plVar5[10] = (long)(puVar1 + 0x10);
      *(long **)puVar2 = plVar5;
      uVar6 = Aska::RigidBodyManager::InitBullet()(plVar5);
      if ((uVar6 & 1) == 0) {
        uVar7 = 0;
        if (*(long **)puVar2 != (long *)0x0) {
          (**(code **)(**(long **)puVar2 + 8))();
          uVar7 = 0;
          *(undefined8 *)puVar2 = 0;
        }
      }
      else {
        Aska::TaskManager::Add(Aska::Task*)(lVar9,*(undefined8 *)puVar2);
        uVar7 = 1;
      }
    }
  }
  return uVar7;
}

// ==== Aska::RigidBodyManager::InitBullet()
// vaddr 0x234d980 | ghidra 0x244d980 | size 488 | symbol _ZN4Aska16RigidBodyManager10InitBulletEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska16RigidBodyManager10InitBulletEv(long param_1)

{
  long lVar1;
  long lVar2;
  long *plVar3;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined4 uStack_38;
  
  lVar1 = operator new(unsigned long, std::nothrow_t const&)(0xb0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar1 == 0) {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    uStack_50 = 0;
    uStack_60 = 0;
    uStack_58 = 0;
    uStack_40 = _UNK_029e3bb8;
    uStack_48 = _UNK_029e3bb0;
    uStack_38 = 1;
    btDefaultCollisionConfiguration::btDefaultCollisionConfiguration(btDefaultCollisionConstructionInfo const&)(lVar1,&uStack_60);
    *(long *)(param_1 + 0x30) = lVar1;
    lVar2 = operator new(unsigned long, std::nothrow_t const&)(0x2988,PTR__ZSt7nothrow_02cb9a80);
    if (lVar2 == 0) {
      *(undefined8 *)(param_1 + 0x38) = 0;
    }
    else {
      btCollisionDispatcher::btCollisionDispatcher(btCollisionConfiguration*)(lVar2,lVar1);
      *(long *)(param_1 + 0x38) = lVar2;
      lVar1 = operator new(unsigned long, std::nothrow_t const&)(0xe0,PTR__ZSt7nothrow_02cb9a80);
      if (lVar1 == 0) {
        *(undefined8 *)(param_1 + 0x40) = 0;
      }
      else {
        btDbvtBroadphase::btDbvtBroadphase(btOverlappingPairCache*)(lVar1,0);
        *(long *)(param_1 + 0x40) = lVar1;
        lVar1 = operator new(unsigned long, std::nothrow_t const&)(0xf0,PTR__ZSt7nothrow_02cb9a80);
        if (lVar1 == 0) {
          *(undefined8 *)(param_1 + 0x48) = 0;
        }
        else {
          btSequentialImpulseConstraintSolver::btSequentialImpulseConstraintSolver()(lVar1);
          *(long *)(param_1 + 0x48) = lVar1;
          plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x178,PTR__ZSt7nothrow_02cb9a80);
          if (plVar3 != (long *)0x0) {
            btDiscreteDynamicsWorld::btDiscreteDynamicsWorld(btDispatcher*, btBroadphaseInterface*, btConstraintSolver*, btCollisionConfiguration*)(plVar3,*(undefined8 *)(param_1 + 0x38),*(undefined8 *)(param_1 + 0x40),
                            lVar1,*(undefined8 *)(param_1 + 0x30));
            *(long **)(param_1 + 0x28) = plVar3;
            uStack_60 = 0xc475000000000000;
            uStack_58 = 0;
            (**(code **)(*plVar3 + 0x70))(plVar3,&uStack_60);
            return 1;
          }
          *(undefined8 *)(param_1 + 0x28) = 0;
        }
      }
    }
  }
  CProfileNode::CleanupMemory()(PTR__ZN15CProfileManager4RootE_02cbcdc8);
  if (*(long **)(param_1 + 0x28) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x28) + 8))();
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  plVar3 = *(long **)(param_1 + 0x30);
  if (plVar3 != (long *)0x0) {
    (**(code **)(*plVar3 + 8))();
    *(long *)(param_1 + 0x30) = 0;
  }
  if (*(long **)(param_1 + 0x38) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x38) + 8))();
    *(undefined8 *)(param_1 + 0x38) = 0;
  }
  if (*(long **)(param_1 + 0x40) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x40) + 8))();
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (*(long **)(param_1 + 0x48) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x48) + 8))();
    *(undefined8 *)(param_1 + 0x48) = 0;
  }
  return 0;
}

// ==== Aska::RigidBodyManager::RigidBodyManager()
// vaddr 0x234db98 | ghidra 0x244db98 | size 168 | symbol _ZN4Aska16RigidBodyManagerC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RigidBodyManagerC2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined4 uVar3;
  code *pcVar4;
  
  puVar1 = PTR__ZTVN4Aska4TaskE_02cbe020;
  param_1[2] = 0;
  param_1[1] = 0;
  pcVar4 = *(code **)(puVar1 + 0x68);
  *param_1 = (long)(puVar1 + 0x10);
  param_1[3] = 0;
  *(undefined2 *)((long)param_1 + 0x24) = 0;
  *(undefined1 *)((long)param_1 + 0x26) = 0;
  uVar3 = (*pcVar4)();
  *(undefined4 *)(param_1 + 4) = uVar3;
  puVar2 = PTR__ZTVN4Aska16RigidBodyManagerE_02cbcdf8;
  *(undefined1 *)(param_1 + 0xe) = 1;
  param_1[0xc] = (long)(param_1 + 0xb);
  param_1[0xd] = (long)(param_1 + 0xb);
  puVar1 = PTR__ZTVN4Aska5TListINS_22RigidBodyPrimitiveBaseEEE_02cb9770;
  *param_1 = (long)(puVar2 + 0x10);
  puVar2 = PTR__ZTVN4Aska22RigidBodyPrimitiveBaseE_02cc25b8;
  param_1[0x10] = 0;
  param_1[0xf] = 0;
  param_1[0x12] = 0;
  param_1[0x11] = 0;
  param_1[8] = 0;
  param_1[7] = 0;
  param_1[0x13] = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  param_1[9] = 0;
  param_1[0xb] = (long)(puVar2 + 0x10);
  param_1[10] = (long)(puVar1 + 0x10);
  param_1[6] = 0;
  param_1[5] = 0;
  return;
}

// ==== Aska::RigidBodyManager::~RigidBodyManager()
// vaddr 0x234dc40 | ghidra 0x244dc40 | size 192 | symbol _ZN4Aska16RigidBodyManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RigidBodyManagerD1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska16RigidBodyManagerE_02cbcdf8 + 0x10);
  CProfileNode::CleanupMemory()(PTR__ZN15CProfileManager4RootE_02cbcdc8);
  if ((long *)param_1[5] != (long *)0x0) {
    (**(code **)(*(long *)param_1[5] + 8))();
    param_1[5] = 0;
  }
  if ((long *)param_1[6] != (long *)0x0) {
    (**(code **)(*(long *)param_1[6] + 8))();
    param_1[6] = 0;
  }
  if ((long *)param_1[7] != (long *)0x0) {
    (**(code **)(*(long *)param_1[7] + 8))();
    param_1[7] = 0;
  }
  if ((long *)param_1[8] != (long *)0x0) {
    (**(code **)(*(long *)param_1[8] + 8))();
    param_1[8] = 0;
  }
  if ((long *)param_1[9] != (long *)0x0) {
    (**(code **)(*(long *)param_1[9] + 8))();
    param_1[9] = 0;
  }
  param_1[10] = (long)(PTR__ZTVN4Aska5TListINS_22RigidBodyPrimitiveBaseEEE_02cb9770 + 0x10);
  Aska::RigidBodyPrimitiveBase::~RigidBodyPrimitiveBase()(param_1 + 0xb);
  (*(code *)PTR__ZN4Aska4TaskD1Ev_02c92d10)(param_1);
  return;
}

// ==== Aska::RigidBodyManager::DeleteBullet()
// vaddr 0x234dd00 | ghidra 0x244dd00 | size 148 | symbol _ZN4Aska16RigidBodyManager12DeleteBulletEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RigidBodyManager12DeleteBulletEv(long param_1)

{
  CProfileNode::CleanupMemory()(PTR__ZN15CProfileManager4RootE_02cbcdc8);
  if (*(long **)(param_1 + 0x28) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x28) + 8))();
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  if (*(long **)(param_1 + 0x30) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x30) + 8))();
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  if (*(long **)(param_1 + 0x38) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x38) + 8))();
    *(undefined8 *)(param_1 + 0x38) = 0;
  }
  if (*(long **)(param_1 + 0x40) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x40) + 8))();
    *(undefined8 *)(param_1 + 0x40) = 0;
  }
  if (*(long **)(param_1 + 0x48) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x48) + 8))();
    *(undefined8 *)(param_1 + 0x48) = 0;
  }
  return;
}

// ==== Aska::RigidBodyManager::~RigidBodyManager()
// vaddr 0x234dda8 | ghidra 0x244dda8 | size 24 | symbol _ZN4Aska16RigidBodyManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RigidBodyManagerD0Ev(undefined8 param_1)

{
  Aska::RigidBodyManager::~RigidBodyManager()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RigidBodyManager::Add(Aska::RigidBodyPrimitiveBase*)
// vaddr 0x234ddc0 | ghidra 0x244ddc0 | size 36 | symbol _ZN4Aska16RigidBodyManager3AddEPNS_22RigidBodyPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RigidBodyManager3AddEPNS_22RigidBodyPrimitiveBaseE(long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x60);
  *(long *)(param_2 + 8) = lVar1;
  *(long *)(param_2 + 0x10) = param_1 + 0x58;
  *(long *)(param_1 + 0x60) = param_2;
  *(long *)(lVar1 + 0x10) = param_2;
  *(int *)(param_1 + 0xa0) = *(int *)(param_1 + 0xa0) + 1;
  return;
}

// ==== Aska::RigidBodyManager::Remove(Aska::RigidBodyPrimitiveBase*)
// vaddr 0x234de08 | ghidra 0x244de08 | size 64 | symbol _ZN4Aska16RigidBodyManager6RemoveEPNS_22RigidBodyPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RigidBodyManager6RemoveEPNS_22RigidBodyPrimitiveBaseE(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  if ((param_1 + 0x58 != param_2) && (param_2 != 0)) {
    lVar1 = *(long *)(param_2 + 8);
    lVar2 = *(long *)(param_2 + 0x10);
    if (lVar1 != 0) {
      *(long *)(lVar1 + 0x10) = lVar2;
    }
    if (lVar2 != 0) {
      *(long *)(lVar2 + 8) = lVar1;
    }
    if (0 < *(int *)(param_1 + 0xa0)) {
      *(int *)(param_1 + 0xa0) = *(int *)(param_1 + 0xa0) + -1;
    }
    *(long *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = 0;
  }
  return;
}

// ==== Aska::RigidBodyManager::Simulate()
// vaddr 0x234de88 | ghidra 0x244de88 | size 272 | symbol _ZN4Aska16RigidBodyManager8SimulateEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16RigidBodyManager8SimulateEv(long param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  long *plVar5;
  long *plVar6;
  long lVar7;
  undefined8 uVar8;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  
  plVar5 = *(long **)(param_1 + 0x28);
  uVar8 = (**(code **)**(undefined8 **)PTR__ZN4Aska14DynamicsCommon9m_pIVSyncE_02cbb790)
                    (*(undefined8 **)PTR__ZN4Aska14DynamicsCommon9m_pIVSyncE_02cbb790,0);
  if (_UNK_027e519c < (float)uVar8) {
    (**(code **)(*plVar5 + 0x40))(uVar8,_UNK_029671ec,plVar5,0x7fffffff);
  }
  for (plVar5 = *(long **)(param_1 + 0x68); (long *)(param_1 + 0x58) != plVar5;
      plVar5 = (long *)plVar5[2]) {
    lVar7 = plVar5[6];
    if (lVar7 != 0) {
      btMatrix3x3::getRotation(btQuaternion&) const(lVar7 + 8,&uStack_60);
      uVar4 = uStack_54;
      uVar3 = uStack_58;
      uVar2 = uStack_5c;
      uVar1 = uStack_60;
      plVar6 = (long *)plVar5[4];
      (**(code **)(*plVar6 + 200))
                (*(undefined4 *)(lVar7 + 0x38),*(undefined4 *)(lVar7 + 0x3c),
                 *(undefined4 *)(lVar7 + 0x40),plVar6);
      (**(code **)(*plVar6 + 0xf0))(uVar1,uVar2,uVar3,uVar4,plVar6);
      (**(code **)(*plVar5 + 0x38))(plVar5);
    }
  }
  return;
}

// ==== Aska::RigidBodyManager::ResetScene()
// vaddr 0x234df98 | ghidra 0x244df98 | size 104 | symbol _ZN4Aska16RigidBodyManager10ResetSceneEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RigidBodyManager10ResetSceneEv(long param_1)

{
  long *plVar1;
  long lVar2;
  
  plVar1 = *(long **)(param_1 + 0x28);
  for (lVar2 = *(long *)(param_1 + 0x68); param_1 + 0x58 != lVar2; lVar2 = *(long *)(lVar2 + 0x10))
  {
    Aska::RigidBodyPrimitiveBase::Reset()(lVar2);
  }
  (**(code **)(*(long *)plVar1[0xe] + 0x58))((long *)plVar1[0xe],plVar1[5]);
  plVar1 = (long *)(**(code **)(*plVar1 + 0xa0))(plVar1);
                    /* WARNING: Could not recover jumptable at 0x0244dffc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x28))();
  return;
}

// ==== Aska::RigidBodyManager::Run(int)
// vaddr 0x234e000 | ghidra 0x244e000 | size 20 | symbol _ZN4Aska16RigidBodyManager3RunEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16RigidBodyManager3RunEi(long param_1)

{
  if (0 < *(int *)(param_1 + 0xa0)) {
    (*(code *)PTR__ZN4Aska16RigidBodyManager8SimulateEv_02c93cc8)();
    return;
  }
  return;
}

// ==== Aska::RigidBodyManager::Get(unsigned long, void*) const
// vaddr 0x234e014 | ghidra 0x244e014 | size 8 | symbol _ZNK4Aska16RigidBodyManager3GetEmPv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16RigidBodyManager3GetEmPv(void)

{
  return 0;
}

// ==== Aska::RigidBodyManager::Set(unsigned long, void const*)
// vaddr 0x234e01c | ghidra 0x244e01c | size 124 | symbol _ZN4Aska16RigidBodyManager3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16RigidBodyManager3SetEmPKv(long param_1,ulong param_2)

{
  long *plVar1;
  long lVar2;
  
  if ((param_2 & 0xffff0000ffff) == 5) {
    plVar1 = *(long **)(param_1 + 0x28);
    for (lVar2 = *(long *)(param_1 + 0x68); param_1 + 0x58 != lVar2; lVar2 = *(long *)(lVar2 + 0x10)
        ) {
      Aska::RigidBodyPrimitiveBase::Reset()(lVar2);
    }
    (**(code **)(*(long *)plVar1[0xe] + 0x58))((long *)plVar1[0xe],plVar1[5]);
    plVar1 = (long *)(**(code **)(*plVar1 + 0xa0))(plVar1);
    (**(code **)(*plVar1 + 0x28))();
  }
  return 0;
}

// ==== Aska::RigidBodyManager::GetClassID(int) const
// vaddr 0x234e098 | ghidra 0x244e098 | size 64 | symbol _ZNK4Aska16RigidBodyManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16RigidBodyManager10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 != 0) {
    uVar2 = 0xf000f001;
    if (param_2 != 2) {
      uVar2 = 0xf000;
    }
    uVar1 = 0xf000f001f002;
    if (param_2 != 1) {
      uVar1 = uVar2;
    }
    return uVar1;
  }
  return 0xf002f054;
}

// ==== Aska::RigidBodyManager::GetDefaultLevel() const
// vaddr 0x234e0d8 | ghidra 0x244e0d8 | size 8 | symbol _ZNK4Aska16RigidBodyManager15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16RigidBodyManager15GetDefaultLevelEv(void)

{
  return 0x4000;
}

// ==== Aska::RigidBodyPrimitiveBase::LocalCreateBullet()
// vaddr 0x234e674 | ghidra 0x244e674 | size 916 | symbol _ZN4Aska22RigidBodyPrimitiveBase17LocalCreateBulletEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 _ZN4Aska22RigidBodyPrimitiveBase17LocalCreateBulletEv(long param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined *puVar4;
  int iVar5;
  long lVar6;
  undefined4 uVar7;
  long *plVar8;
  float fVar9;
  undefined8 uVar10;
  long lVar11;
  float fVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  float fVar15;
  undefined8 uVar16;
  undefined8 uVar17;
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
  float afStack_128 [2];
  undefined8 uStack_120;
  undefined4 uStack_118;
  undefined8 uStack_114;
  undefined8 uStack_10c;
  undefined4 uStack_104;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined4 uStack_f0;
  undefined8 uStack_ec;
  undefined8 uStack_e4;
  undefined4 uStack_dc;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined1 uStack_a8;
  undefined8 uStack_a4;
  undefined8 uStack_9c;
  undefined8 uStack_90;
  undefined8 uStack_88;
  
  uStack_90 = 0;
  uStack_88 = 0;
  fVar22 = *(float *)(*(long *)(param_1 + 0x28) + 4);
  if (fVar22 != 0.0) {
    (**(code **)(**(long **)(param_1 + 0x38) + 0x40))(fVar22,*(long **)(param_1 + 0x38),&uStack_90);
  }
  lVar6 = *(long *)(param_1 + 0x20);
  if (lVar6 == 0) {
    uVar7 = 0;
  }
  else {
    fVar9 = *(float *)(lVar6 + 0x90);
    fVar12 = *(float *)(lVar6 + 0x94);
    fVar15 = *(float *)(lVar6 + 0x98);
    fVar18 = *(float *)(lVar6 + 0x9c);
    uVar7 = *(undefined4 *)(lVar6 + 0x80);
    uVar1 = *(undefined4 *)(lVar6 + 0x84);
    uVar2 = *(undefined4 *)(lVar6 + 0x88);
    plVar8 = *(long **)(param_1 + 0x40);
    fVar19 = 2.0 / (fVar9 * fVar9 + fVar12 * fVar12 + fVar15 * fVar15 + fVar18 * fVar18);
    fVar21 = fVar12 * fVar19;
    fVar20 = fVar15 * fVar19;
    fVar27 = fVar18 * fVar9 * fVar19;
    fVar19 = fVar9 * fVar9 * fVar19;
    fVar25 = fVar9 * fVar21 - fVar18 * fVar20;
    fVar26 = fVar9 * fVar20 + fVar18 * fVar21;
    fVar23 = fVar9 * fVar21 + fVar18 * fVar20;
    fVar9 = fVar9 * fVar20 - fVar18 * fVar21;
    fVar24 = fVar12 * fVar20 - fVar27;
    fVar27 = fVar12 * fVar20 + fVar27;
    fVar18 = 1.0 - (fVar12 * fVar21 + fVar15 * fVar20);
    fVar15 = 1.0 - (fVar19 + fVar15 * fVar20);
    fVar12 = 1.0 - (fVar19 + fVar12 * fVar21);
    if (((*PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798 & 1) == 0) &&
       (iVar5 = __cxa_guard_acquire(PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798)
       , iVar5 != 0)) {
      if (((*PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0 & 1) == 0) &&
         (iVar5 = __cxa_guard_acquire(PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0),
         puVar3 = PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00, iVar5 != 0)) {
        *(undefined4 *)PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 = 0x3f800000;
        *(undefined8 *)(puVar3 + 0xc) = 0;
        *(undefined8 *)(puVar3 + 4) = 0;
        *(undefined4 *)(puVar3 + 0x14) = 0x3f800000;
        *(undefined8 *)(puVar3 + 0x18) = 0;
        *(undefined8 *)(puVar3 + 0x20) = 0;
        *(undefined8 *)(puVar3 + 0x28) = 0x3f800000;
        __cxa_guard_release(PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0);
      }
      puVar3 = PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0;
      uVar10 = *(undefined8 *)PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00;
      uVar14 = *(undefined8 *)
                (PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 + 0x18);
      uVar13 = *(undefined8 *)
                (PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 + 0x10);
      uVar17 = *(undefined8 *)
                (PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 + 0x28);
      uVar16 = *(undefined8 *)
                (PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 + 0x20);
      *(undefined8 *)(PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 8) =
           *(undefined8 *)(PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 + 8);
      *(undefined8 *)puVar3 = uVar10;
      *(undefined8 *)(puVar3 + 0x18) = uVar14;
      *(undefined8 *)(puVar3 + 0x10) = uVar13;
      *(undefined8 *)(puVar3 + 0x28) = uVar17;
      *(undefined8 *)(puVar3 + 0x20) = uVar16;
      *(undefined8 *)(puVar3 + 0x30) = 0;
      *(undefined8 *)(puVar3 + 0x38) = 0;
      __cxa_guard_release(PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798);
    }
    puVar3 = PTR__ZTV20btDefaultMotionState_02cb9610;
    *(float *)(plVar8 + 1) = fVar18;
    *(float *)((long)plVar8 + 0xc) = fVar25;
    *(float *)(plVar8 + 2) = fVar26;
    *(undefined4 *)((long)plVar8 + 0x14) = 0;
    *(float *)(plVar8 + 3) = fVar23;
    *(float *)((long)plVar8 + 0x1c) = fVar15;
    *(float *)(plVar8 + 4) = fVar24;
    *(undefined4 *)((long)plVar8 + 0x24) = 0;
    *(float *)(plVar8 + 5) = fVar9;
    *(float *)((long)plVar8 + 0x2c) = fVar27;
    *(float *)(plVar8 + 6) = fVar12;
    *(undefined4 *)((long)plVar8 + 0x34) = 0;
    *(undefined4 *)(plVar8 + 7) = uVar7;
    *(undefined4 *)((long)plVar8 + 0x3c) = uVar1;
    *(undefined4 *)(plVar8 + 8) = uVar2;
    *(undefined4 *)((long)plVar8 + 0x44) = 0;
    puVar4 = PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0;
    *plVar8 = (long)(puVar3 + 0x10);
    lVar6 = *(long *)puVar4;
    plVar8[10] = *(long *)(puVar4 + 8);
    plVar8[9] = lVar6;
    lVar6 = *(long *)(puVar4 + 0x10);
    plVar8[0xc] = *(long *)(puVar4 + 0x18);
    plVar8[0xb] = lVar6;
    lVar6 = *(long *)(puVar4 + 0x20);
    plVar8[0xe] = *(long *)(puVar4 + 0x28);
    plVar8[0xd] = lVar6;
    lVar11 = *(long *)(puVar4 + 0x38);
    lVar6 = *(long *)(puVar4 + 0x30);
    *(undefined4 *)((long)plVar8 + 0xb4) = 0;
    *(undefined4 *)(plVar8 + 0x17) = uVar7;
    *(float *)(plVar8 + 0x11) = fVar18;
    *(float *)((long)plVar8 + 0x8c) = fVar25;
    *(float *)(plVar8 + 0x12) = fVar26;
    *(undefined4 *)((long)plVar8 + 0x94) = 0;
    *(float *)(plVar8 + 0x13) = fVar23;
    *(float *)((long)plVar8 + 0x9c) = fVar15;
    *(float *)(plVar8 + 0x14) = fVar24;
    *(undefined4 *)((long)plVar8 + 0xa4) = 0;
    *(float *)(plVar8 + 0x15) = fVar9;
    *(float *)((long)plVar8 + 0xac) = fVar27;
    *(float *)(plVar8 + 0x16) = fVar12;
    *(undefined4 *)((long)plVar8 + 0xbc) = uVar1;
    *(undefined4 *)(plVar8 + 0x18) = uVar2;
    *(undefined4 *)((long)plVar8 + 0xc4) = 0;
    plVar8[0x19] = 0;
    plVar8[0x10] = lVar11;
    plVar8[0xf] = lVar6;
    uStack_d8 = *(undefined8 *)(param_1 + 0x38);
    uStack_120 = *(undefined8 *)(param_1 + 0x40);
    uStack_c8 = uStack_88;
    uStack_d0 = uStack_90;
    uStack_b0 = 0x3f8000003f4ccccd;
    uStack_a8 = 0;
    uStack_9c = _UNK_029e3c28;
    uStack_a4 = _UNK_029e3c20;
    uStack_118 = 0x3f800000;
    uStack_10c = 0;
    uStack_114 = 0;
    uStack_104 = 0x3f800000;
    uStack_100 = 0;
    uStack_f8 = 0;
    uStack_f0 = 0x3f800000;
    uStack_dc = 0;
    uStack_e4 = 0;
    uStack_ec = 0;
    uStack_b8 = *(undefined8 *)(*(long *)(param_1 + 0x28) + 8);
    uStack_c0 = *(undefined8 *)(*(long *)(param_1 + 0x28) + 0x10);
    afStack_128[0] = fVar22;
    btRigidBody::btRigidBody(btRigidBody::btRigidBodyConstructionInfo const&)(*(undefined8 *)(param_1 + 0x30),afStack_128);
    lVar6 = *(long *)(param_1 + 0x28);
    lVar11 = *(long *)(param_1 + 0x30);
    uVar7 = *(undefined4 *)(lVar6 + 0x18);
    uVar1 = *(undefined4 *)(lVar6 + 0x1c);
    uVar2 = *(undefined4 *)(lVar6 + 0x20);
    *(undefined4 *)(lVar11 + 0x154) = 0;
    *(undefined4 *)(lVar11 + 0x148) = uVar7;
    *(undefined4 *)(lVar11 + 0x14c) = uVar1;
    *(undefined4 *)(lVar11 + 0x150) = uVar2;
    lVar6 = *(long *)(param_1 + 0x28);
    uVar7 = *(undefined4 *)(lVar6 + 0x24);
    uVar1 = *(undefined4 *)(lVar6 + 0x28);
    uVar2 = *(undefined4 *)(lVar6 + 0x2c);
    *(undefined4 *)(lVar11 + 0x164) = 0;
    *(undefined4 *)(lVar11 + 0x158) = uVar7;
    *(undefined4 *)(lVar11 + 0x15c) = uVar1;
    *(undefined4 *)(lVar11 + 0x160) = uVar2;
    btCollisionObject::setActivationState(int)(lVar11,2);
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x88))(*(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28
                                 ),lVar11);
    btCollisionObject::setActivationState(int)(lVar11,2);
    uVar7 = 1;
    btCollisionObject::forceActivationState(int)(lVar11,1);
    btCollisionObject::activate(bool)(lVar11,0);
    *(undefined4 *)(lVar11 + 0xe8) = 0;
  }
  return uVar7;
}

// ==== Aska::RigidBodyPrimitiveSphere::CreateBullet()
// vaddr 0x234eb9c | ghidra 0x244eb9c | size 164 | symbol _ZN4Aska24RigidBodyPrimitiveSphere12CreateBulletEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska24RigidBodyPrimitiveSphere12CreateBulletEv(long param_1)

{
  undefined4 uVar1;
  undefined8 uVar2;
  long lVar3;
  long *plVar4;
  
  if (*(long *)(param_1 + 0x28) != 0) {
    lVar3 = operator new[](unsigned long, unsigned long, bool)(0x348,0x10,1);
    *(long *)(param_1 + 0x30) = lVar3;
    if (lVar3 != 0) {
      plVar4 = (long *)(lVar3 + _UNK_029e3c30);
      *(long *)(param_1 + 0x40) = lVar3 + _UNK_029e3c38;
      *(long **)(param_1 + 0x38) = plVar4;
      uVar1 = *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x30);
      btConvexInternalShape::btConvexInternalShape()(plVar4);
      *plVar4 = (long)(PTR__ZTV13btSphereShape_02cbfb30 + 0x10);
      *(undefined4 *)(lVar3 + 0x240) = 8;
      *(undefined4 *)(lVar3 + 0x260) = uVar1;
      *(undefined4 *)(lVar3 + 0x270) = uVar1;
      uVar2 = (*(code *)PTR__ZN4Aska22RigidBodyPrimitiveBase17LocalCreateBulletEv_02caf1f8)(param_1)
      ;
      return uVar2;
    }
  }
  return 0;
}


// FAILED to create function at 02c64188 Aska::RigidBodyManager::vtable
// FAILED to create function at 02c64230 Aska::RigidBodyManager::typeinfo
