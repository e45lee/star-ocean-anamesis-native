// port/decomp/dynamics/rigidbody.c: Ghidra decompiles for the dynamics subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 14:44 UTC: tools/decomp.sh '--into' 'dynamics/rigidbody' ' Aska::RigidBody\w*::[~\w<>]+\('

// ==== Aska::RigidBodyConstraintBase::~RigidBodyConstraintBase()
// vaddr 0x234bdf0 | ghidra 0x244bdf0 | size 108 | symbol _ZN4Aska23RigidBodyConstraintBaseD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23RigidBodyConstraintBaseD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska23RigidBodyConstraintBaseE_02cc1610;
  param_1[5] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  if (param_1[8] != 0) {
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x58))();
    if ((long *)param_1[8] != (long *)0x0) {
      (**(code **)(*(long *)param_1[8] + 8))();
    }
    param_1[8] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RigidBodyConstraintBase::Attach(Aska::AsfHandler const*, Aska::AFF::AskaChunk const*)
// vaddr 0x234be5c | ghidra 0x244be5c | size 96 | symbol _ZN4Aska23RigidBodyConstraintBase6AttachEPKNS_10AsfHandlerEPKNS_3AFF9AskaChunkE | lib libSOA-3.7.0.so | 2026-10-08
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

// ==== Aska::RigidBodyConstraintNail::CreateBullet()
// vaddr 0x234bebc | ghidra 0x244bebc | size 660 | symbol _ZN4Aska23RigidBodyConstraintNail12CreateBulletEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska23RigidBodyConstraintNail12CreateBulletEv(long param_1)

{
  undefined8 uVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  long lVar5;
  long *plVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  undefined4 uStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  undefined4 uStack_44;
  
  lVar2 = *(long *)(param_1 + 0x30);
  if ((lVar2 == 0) || (plVar4 = *(long **)(lVar2 + 0x20), plVar4 == (long *)0x0)) {
code_r0x0244c0c0:
    uVar1 = 0;
  }
  else {
    lVar2 = *(long *)(lVar2 + 0x30);
    plVar6 = *(long **)(param_1 + 0x20);
    if ((*(byte *)(plVar4 + 0x25) & 1) != 0) {
      (**(code **)(*plVar4 + 0xa8))(plVar4);
    }
    if ((*(byte *)(plVar6 + 0x25) & 1) != 0) {
      (**(code **)(*plVar6 + 0xa8))(plVar6);
    }
    fVar7 = *(float *)((long)plVar6 + 0x4c);
    fVar8 = *(float *)((long)plVar6 + 0x5c);
    fVar9 = *(float *)((long)plVar6 + 0x6c);
    fStack_50 = fVar7 - *(float *)((long)plVar4 + 0x4c);
    fStack_4c = fVar8 - *(float *)((long)plVar4 + 0x5c);
    fStack_48 = fVar9 - *(float *)((long)plVar4 + 0x6c);
    uStack_44 = 0;
    lVar3 = *(long *)(param_1 + 0x38);
    if ((lVar3 == 0) || (lVar5 = *(long *)(lVar3 + 0x30), lVar5 == 0)) {
      lVar3 = operator new(unsigned long, std::nothrow_t const&)(0x188,PTR__ZSt7nothrow_02cb9a80);
      if (lVar3 == 0) {
        return 0;
      }
      btPoint2PointConstraint::btPoint2PointConstraint(btRigidBody&, btVector3 const&)(lVar3,lVar2,&fStack_50);
      lVar2 = *(long *)(lVar3 + 0x20);
      *(float *)(lVar2 + 0x38) = fVar7;
      *(float *)(lVar2 + 0x3c) = fVar8;
      *(float *)(lVar2 + 0x40) = fVar9;
      *(undefined4 *)(lVar2 + 0x44) = 0;
      *(undefined8 *)(lVar3 + 0x174) = 0;
      *(undefined8 *)(lVar3 + 0x16c) = 0;
    }
    else {
      if (*(long *)(lVar3 + 0x20) == 0) goto code_r0x0244c0c0;
      fVar11 = *(float *)(lVar5 + 0x3c);
      fVar10 = -*(float *)(lVar5 + 0x38);
      fVar12 = *(float *)(lVar5 + 0x40);
      fVar8 = *(float *)(lVar2 + 0x38) +
              *(float *)(lVar2 + 8) * fStack_50 + *(float *)(lVar2 + 0xc) * fStack_4c +
              *(float *)(lVar2 + 0x10) * fStack_48;
      fVar9 = *(float *)(lVar2 + 0x3c) +
              fStack_50 * *(float *)(lVar2 + 0x18) + fStack_4c * *(float *)(lVar2 + 0x1c) +
              fStack_48 * *(float *)(lVar2 + 0x20);
      fVar7 = *(float *)(lVar2 + 0x40) +
              fStack_50 * *(float *)(lVar2 + 0x28) + fStack_4c * *(float *)(lVar2 + 0x2c) +
              fStack_48 * *(float *)(lVar2 + 0x30);
      fStack_60 = ((*(float *)(lVar5 + 8) * fVar10 - *(float *)(lVar5 + 0x18) * fVar11) -
                  *(float *)(lVar5 + 0x28) * fVar12) +
                  *(float *)(lVar5 + 8) * fVar8 + *(float *)(lVar5 + 0x18) * fVar9 +
                  *(float *)(lVar5 + 0x28) * fVar7;
      fStack_5c = ((*(float *)(lVar5 + 0xc) * fVar10 - *(float *)(lVar5 + 0x1c) * fVar11) -
                  *(float *)(lVar5 + 0x2c) * fVar12) +
                  *(float *)(lVar5 + 0xc) * fVar8 + *(float *)(lVar5 + 0x1c) * fVar9 +
                  *(float *)(lVar5 + 0x2c) * fVar7;
      fStack_58 = ((*(float *)(lVar5 + 0x10) * fVar10 - *(float *)(lVar5 + 0x20) * fVar11) -
                  *(float *)(lVar5 + 0x30) * fVar12) +
                  *(float *)(lVar5 + 0x10) * fVar8 + *(float *)(lVar5 + 0x20) * fVar9 +
                  *(float *)(lVar5 + 0x30) * fVar7;
      uStack_54 = 0;
      lVar3 = operator new(unsigned long, std::nothrow_t const&)(0x188,PTR__ZSt7nothrow_02cb9a80);
      if (lVar3 == 0) {
        return 0;
      }
      btPoint2PointConstraint::btPoint2PointConstraint(btRigidBody&, btRigidBody&, btVector3 const&, btVector3 const&)(lVar3,lVar2,lVar5,&fStack_50,&fStack_60);
    }
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x50))(*(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28
                                 ),lVar3,0);
    uVar1 = 1;
    *(long *)(param_1 + 0x40) = lVar3;
  }
  return uVar1;
}

// ==== Aska::RigidBodyConstraintHinge::CreateBullet()
// vaddr 0x234c150 | ghidra 0x244c150 | size 1256 | symbol _ZN4Aska24RigidBodyConstraintHinge12CreateBulletEv | lib libSOA-3.7.0.so | 2026-10-08
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

// ==== Aska::RigidBodyConstraintSixDOF::CreateBullet()
// vaddr 0x234c638 | ghidra 0x244c638 | size 1940 | symbol _ZN4Aska25RigidBodyConstraintSixDOF12CreateBulletEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska25RigidBodyConstraintSixDOF12CreateBulletEv(long param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined *puVar5;
  undefined *puVar6;
  int iVar7;
  byte bVar8;
  long lVar9;
  undefined8 uVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  long *plVar14;
  long *plVar15;
  float fVar16;
  float fVar17;
  undefined4 uVar18;
  float fVar19;
  float fVar20;
  undefined8 uVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  undefined4 uVar28;
  undefined4 uVar29;
  undefined4 uVar30;
  undefined4 uVar31;
  undefined4 uVar32;
  float fVar33;
  float fStack_120;
  float fStack_11c;
  ulong uStack_118;
  float fStack_110;
  float fStack_10c;
  ulong uStack_108;
  float fStack_100;
  float fStack_fc;
  ulong uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  ulong uStack_d8;
  undefined8 uStack_d0;
  ulong uStack_c8;
  undefined8 uStack_c0;
  ulong uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  
  lVar11 = *(long *)(param_1 + 0x30);
  if ((((lVar11 == 0) || (lVar9 = *(long *)(param_1 + 0x38), lVar9 == 0)) ||
      (lVar12 = *(long *)(lVar11 + 0x30), lVar12 == 0)) ||
     (lVar13 = *(long *)(lVar9 + 0x30), lVar13 == 0)) {
    return 0;
  }
  plVar15 = *(long **)(lVar11 + 0x20);
  if (plVar15 == (long *)0x0) {
    return 0;
  }
  plVar14 = *(long **)(lVar9 + 0x20);
  if (plVar14 != (long *)0x0) {
    if ((*(byte *)(plVar15 + 0x25) & 1) == 0) {
      bVar8 = *(byte *)(plVar14 + 0x25);
    }
    else {
      (**(code **)(*plVar15 + 0xa8))(plVar15);
      bVar8 = *(byte *)(plVar14 + 0x25);
    }
    if ((bVar8 & 1) == 0) {
      bVar8 = *(byte *)(plVar15 + 0x25);
      lVar11 = _UNK_027dbb30;
      lVar9 = _UNK_027dbb38;
    }
    else {
      (**(code **)(*plVar14 + 0xa8))(plVar14);
      bVar8 = *(byte *)(plVar15 + 0x25);
      lVar11 = _UNK_027dbb30;
      lVar9 = _UNK_027dbb38;
    }
    if ((bVar8 >> 2 & 1) == 0) {
      _UNK_027dbb30 = lVar11;
      _UNK_027dbb38 = lVar9;
      if ((*(byte *)((long)plVar15 + 0x129) & 3) == 0) {
        fVar16 = *(float *)((long)plVar15 + 0x4c);
        fVar17 = *(float *)((long)plVar15 + 0x5c);
        fVar19 = *(float *)((long)plVar15 + 0x6c);
        plVar15[0x27] = CONCAT44((int)plVar15[0xe],*(float *)(plVar15 + 0xc));
        plVar15[0x26] = CONCAT44(*(float *)(plVar15 + 10),*(float *)(plVar15 + 8));
        plVar15[0x29] =
             CONCAT44(*(undefined4 *)((long)plVar15 + 0x74),*(float *)((long)plVar15 + 100));
        plVar15[0x28] = CONCAT44(*(float *)((long)plVar15 + 0x54),*(float *)((long)plVar15 + 0x44));
        *(float *)((long)plVar15 + 0x13c) =
             -(*(float *)(plVar15 + 8) * fVar16 + *(float *)(plVar15 + 10) * fVar17 +
              *(float *)(plVar15 + 0xc) * fVar19);
        *(float *)((long)plVar15 + 0x14c) =
             -(fVar16 * *(float *)((long)plVar15 + 0x44) + fVar17 * *(float *)((long)plVar15 + 0x54)
              + fVar19 * *(float *)((long)plVar15 + 100));
        plVar15[0x2b] = CONCAT44((int)plVar15[0xf],*(float *)(plVar15 + 0xd));
        plVar15[0x2a] = CONCAT44(*(float *)(plVar15 + 0xb),*(float *)(plVar15 + 9));
        plVar15[0x2d] = lVar9;
        plVar15[0x2c] = lVar11;
        *(float *)((long)plVar15 + 0x15c) =
             -(fVar16 * *(float *)(plVar15 + 9) + fVar17 * *(float *)(plVar15 + 0xb) +
              fVar19 * *(float *)(plVar15 + 0xd));
      }
      else {
        Aska::Matrix::InvertLowError(Aska::Matrix*) const(plVar15 + 8,plVar15 + 0x26);
        bVar8 = *(byte *)(plVar15 + 0x25);
      }
      *(byte *)(plVar15 + 0x25) = bVar8 | 4;
      bVar8 = *(byte *)(plVar14 + 0x25);
      lVar11 = _UNK_027dbb30;
      lVar9 = _UNK_027dbb38;
    }
    else {
      bVar8 = *(byte *)(plVar14 + 0x25);
    }
    _UNK_027dbb30 = lVar11;
    _UNK_027dbb38 = lVar9;
    if ((bVar8 >> 2 & 1) == 0) {
      if ((*(byte *)((long)plVar14 + 0x129) & 3) == 0) {
        fVar16 = *(float *)((long)plVar14 + 0x4c);
        fVar17 = *(float *)((long)plVar14 + 0x5c);
        fVar19 = *(float *)((long)plVar14 + 0x6c);
        plVar14[0x27] = CONCAT44((int)plVar14[0xe],*(float *)(plVar14 + 0xc));
        plVar14[0x26] = CONCAT44(*(float *)(plVar14 + 10),*(float *)(plVar14 + 8));
        plVar14[0x29] =
             CONCAT44(*(undefined4 *)((long)plVar14 + 0x74),*(float *)((long)plVar14 + 100));
        plVar14[0x28] = CONCAT44(*(float *)((long)plVar14 + 0x54),*(float *)((long)plVar14 + 0x44));
        *(float *)((long)plVar14 + 0x13c) =
             -(*(float *)(plVar14 + 8) * fVar16 + *(float *)(plVar14 + 10) * fVar17 +
              *(float *)(plVar14 + 0xc) * fVar19);
        *(float *)((long)plVar14 + 0x14c) =
             -(fVar16 * *(float *)((long)plVar14 + 0x44) + fVar17 * *(float *)((long)plVar14 + 0x54)
              + fVar19 * *(float *)((long)plVar14 + 100));
        plVar14[0x2b] = CONCAT44((int)plVar14[0xf],*(float *)(plVar14 + 0xd));
        plVar14[0x2a] = CONCAT44(*(float *)(plVar14 + 0xb),*(float *)(plVar14 + 9));
        plVar14[0x2d] = lVar9;
        plVar14[0x2c] = lVar11;
        *(float *)((long)plVar14 + 0x15c) =
             -(fVar16 * *(float *)(plVar14 + 9) + fVar17 * *(float *)(plVar14 + 0xb) +
              fVar19 * *(float *)(plVar14 + 0xd));
      }
      else {
        Aska::Matrix::InvertLowError(Aska::Matrix*) const(plVar14 + 8,plVar14 + 0x26);
        bVar8 = *(byte *)(plVar14 + 0x25);
      }
      *(byte *)(plVar14 + 0x25) = bVar8 | 4;
    }
    Aska::Quaternion::Create(Aska::Matrix const*)(&fStack_90,plVar15 + 0x26);
    Aska::Quaternion::Create(Aska::Matrix const*)(&fStack_a0,plVar14 + 0x26);
    puVar6 = PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798;
    if (((*PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798 & 1) == 0) &&
       (iVar7 = __cxa_guard_acquire(PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798)
       , iVar7 != 0)) {
      if (((*PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0 & 1) == 0) &&
         (iVar7 = __cxa_guard_acquire(PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0),
         puVar5 = PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00, iVar7 != 0)) {
        *(undefined4 *)PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 = 0x3f800000;
        *(undefined8 *)(puVar5 + 0xc) = 0;
        *(undefined8 *)(puVar5 + 4) = 0;
        *(undefined4 *)(puVar5 + 0x14) = 0x3f800000;
        *(undefined8 *)(puVar5 + 0x18) = 0;
        *(undefined8 *)(puVar5 + 0x20) = 0;
        *(undefined8 *)(puVar5 + 0x28) = 0x3f800000;
        __cxa_guard_release(PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0);
      }
      puVar5 = PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0;
      uVar10 = *(undefined8 *)PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00;
      uVar22 = *(undefined8 *)
                (PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 + 0x18);
      uVar21 = *(undefined8 *)
                (PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 + 0x10);
      uVar24 = *(undefined8 *)
                (PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 + 0x28);
      uVar23 = *(undefined8 *)
                (PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 + 0x20);
      *(undefined8 *)(PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 8) =
           *(undefined8 *)(PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 + 8);
      *(undefined8 *)puVar5 = uVar10;
      *(undefined8 *)(puVar5 + 0x18) = uVar22;
      *(undefined8 *)(puVar5 + 0x10) = uVar21;
      *(undefined8 *)(puVar5 + 0x28) = uVar24;
      *(undefined8 *)(puVar5 + 0x20) = uVar23;
      *(undefined8 *)(puVar5 + 0x30) = 0;
      *(undefined8 *)(puVar5 + 0x38) = 0;
      __cxa_guard_release(PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798);
    }
    puVar5 = PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0;
    uStack_d8 = *(ulong *)(PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 8);
    uStack_e0 = *(undefined8 *)PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0;
    uStack_c8 = *(ulong *)(PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 0x18)
    ;
    uStack_d0 = *(undefined8 *)
                 (PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 0x10);
    uStack_b8 = *(ulong *)(PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 0x28)
    ;
    uStack_c0 = *(undefined8 *)
                 (PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 0x20);
    uStack_a8 = *(undefined8 *)
                 (PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 0x38);
    uStack_b0 = *(undefined8 *)
                 (PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 0x30);
    if (((*puVar6 & 1) == 0) &&
       (iVar7 = __cxa_guard_acquire(PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798)
       , iVar7 != 0)) {
      if (((*PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0 & 1) == 0) &&
         (iVar7 = __cxa_guard_acquire(PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0),
         puVar6 = PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00, iVar7 != 0)) {
        *(undefined4 *)PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 = 0x3f800000;
        *(undefined8 *)(puVar6 + 0xc) = 0;
        *(undefined8 *)(puVar6 + 4) = 0;
        *(undefined4 *)(puVar6 + 0x14) = 0x3f800000;
        *(undefined8 *)(puVar6 + 0x18) = 0;
        *(undefined8 *)(puVar6 + 0x20) = 0;
        *(undefined8 *)(puVar6 + 0x28) = 0x3f800000;
        __cxa_guard_release(PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0);
      }
      puVar6 = PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00;
      *(undefined8 *)(puVar5 + 0x30) = 0;
      *(undefined8 *)(puVar5 + 0x38) = 0;
      uVar10 = *(undefined8 *)puVar6;
      uVar22 = *(undefined8 *)(puVar6 + 0x18);
      uVar21 = *(undefined8 *)(puVar6 + 0x10);
      uVar24 = *(undefined8 *)(puVar6 + 0x28);
      uVar23 = *(undefined8 *)(puVar6 + 0x20);
      *(undefined8 *)(puVar5 + 8) = *(undefined8 *)(puVar6 + 8);
      *(undefined8 *)puVar5 = uVar10;
      *(undefined8 *)(puVar5 + 0x18) = uVar22;
      *(undefined8 *)(puVar5 + 0x10) = uVar21;
      *(undefined8 *)(puVar5 + 0x28) = uVar24;
      *(undefined8 *)(puVar5 + 0x20) = uVar23;
      __cxa_guard_release(PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798);
    }
    uStack_e8 = *(undefined8 *)(puVar5 + 0x38);
    uStack_f0 = *(undefined8 *)(puVar5 + 0x30);
    fVar16 = 2.0 / (fStack_90 * fStack_90 + fStack_8c * fStack_8c + fStack_88 * fStack_88 +
                   fStack_84 * fStack_84);
    fVar19 = 2.0 / (fStack_a0 * fStack_a0 + fStack_9c * fStack_9c + fStack_98 * fStack_98 +
                   fStack_94 * fStack_94);
    fVar25 = fStack_8c * fVar16;
    fVar17 = fStack_88 * fVar16;
    fVar26 = fStack_9c * fVar19;
    fVar20 = fStack_98 * fVar19;
    fVar27 = fStack_84 * fStack_90 * fVar16;
    fVar16 = fStack_90 * fStack_90 * fVar16;
    fVar33 = fStack_94 * fStack_a0 * fVar19;
    fVar19 = fStack_a0 * fStack_a0 * fVar19;
    uStack_e0 = CONCAT44(fStack_90 * fVar25 - fStack_84 * fVar17,
                         1.0 - (fStack_8c * fVar25 + fStack_88 * fVar17));
    uStack_d8 = (ulong)(uint)(fStack_90 * fVar17 + fStack_84 * fVar25);
    uStack_d0 = CONCAT44(1.0 - (fVar16 + fStack_88 * fVar17),fStack_90 * fVar25 + fStack_84 * fVar17
                        );
    uStack_c8 = (ulong)(uint)(fStack_8c * fVar17 - fVar27);
    uStack_c0 = CONCAT44(fStack_8c * fVar17 + fVar27,fStack_90 * fVar17 - fStack_84 * fVar25);
    uStack_b8 = (ulong)(uint)(1.0 - (fVar16 + fStack_8c * fVar25));
    _fStack_120 = CONCAT44(fStack_a0 * fVar26 - fStack_94 * fVar20,
                           1.0 - (fStack_9c * fVar26 + fStack_98 * fVar20));
    uStack_118 = (ulong)(uint)(fStack_a0 * fVar20 + fStack_94 * fVar26);
    _fStack_110 = CONCAT44(1.0 - (fVar19 + fStack_98 * fVar20),
                           fStack_a0 * fVar26 + fStack_94 * fVar20);
    uStack_108 = (ulong)(uint)(fStack_9c * fVar20 - fVar33);
    _fStack_100 = CONCAT44(fStack_9c * fVar20 + fVar33,fStack_a0 * fVar20 - fStack_94 * fVar26);
    uStack_f8 = (ulong)(uint)(1.0 - (fVar19 + fStack_9c * fVar26));
    lVar11 = operator new(unsigned long, std::nothrow_t const&)(0x4f8,PTR__ZSt7nothrow_02cb9a80);
    uVar10 = 0;
    if (lVar11 != 0) {
      btGeneric6DofConstraint::btGeneric6DofConstraint(btRigidBody&, btRigidBody&, btTransform const&, btTransform const&, bool)(lVar11,lVar12,lVar13,&uStack_e0,&fStack_120,1);
      lVar9 = *(long *)(param_1 + 0x28);
      uVar1 = *(undefined4 *)(lVar9 + 0x114);
      uVar2 = *(undefined4 *)(lVar9 + 0x118);
      uVar3 = *(undefined4 *)(lVar9 + 0x11c);
      uVar4 = *(undefined4 *)(lVar9 + 0x120);
      uVar18 = *(undefined4 *)(lVar9 + 0x124);
      uVar32 = *(undefined4 *)(lVar9 + 0x128);
      uVar31 = *(undefined4 *)(lVar9 + 300);
      uVar30 = *(undefined4 *)(lVar9 + 0x130);
      uVar29 = *(undefined4 *)(lVar9 + 0x134);
      uVar28 = *(undefined4 *)(lVar9 + 0x138);
      uVar10 = *(undefined8 *)(lVar9 + 0x10c);
      *(undefined4 *)(lVar11 + 0x2e4) = 0;
      *(undefined4 *)(lVar11 + 0x2e0) = uVar1;
      *(undefined4 *)(lVar11 + 0x2e8) = uVar2;
      *(undefined8 *)(lVar11 + 0x2d8) = uVar10;
      fVar17 = _UNK_027edb34;
      *(undefined4 *)(lVar11 + 0x2ec) = uVar3;
      *(undefined4 *)(lVar11 + 0x2f0) = uVar4;
      *(undefined4 *)(lVar11 + 0x2f4) = 0;
      fVar19 = (float)fmodf(uVar18,fVar17);
      fVar16 = _UNK_027edb30;
      if (_UNK_027edb30 <= fVar19) {
        if (_UNK_027e3fd0 < fVar19) {
          fVar19 = fVar19 + _UNK_027edb3c;
        }
      }
      else {
        fVar19 = fVar19 + fVar17;
      }
      *(float *)(lVar11 + 0x364) = fVar19;
      fVar19 = (float)fmodf(uVar32,fVar17);
      if (fVar16 <= fVar19) {
        if (_UNK_027e3fd0 < fVar19) {
          fVar19 = fVar19 + _UNK_027edb3c;
        }
      }
      else {
        fVar19 = fVar19 + fVar17;
      }
      *(float *)(lVar11 + 0x39c) = fVar19;
      fVar19 = (float)fmodf(uVar31,fVar17);
      if (fVar16 <= fVar19) {
        if (_UNK_027e3fd0 < fVar19) {
          fVar19 = fVar19 + _UNK_027edb3c;
        }
      }
      else {
        fVar19 = fVar19 + fVar17;
      }
      *(float *)(lVar11 + 0x3d4) = fVar19;
      fVar19 = (float)fmodf(uVar30,fVar17);
      if (fVar16 <= fVar19) {
        if (_UNK_027e3fd0 < fVar19) {
          fVar19 = fVar19 + _UNK_027edb3c;
        }
      }
      else {
        fVar19 = fVar19 + fVar17;
      }
      *(float *)(lVar11 + 0x368) = fVar19;
      fVar19 = (float)fmodf(uVar29,fVar17);
      if (fVar16 <= fVar19) {
        if (_UNK_027e3fd0 < fVar19) {
          fVar19 = fVar19 + _UNK_027edb3c;
        }
      }
      else {
        fVar19 = fVar19 + fVar17;
      }
      *(float *)(lVar11 + 0x3a0) = fVar19;
      fVar19 = (float)fmodf(uVar28,fVar17);
      puVar6 = PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48;
      if (fVar16 <= fVar19) {
        if (_UNK_027e3fd0 < fVar19) {
          fVar19 = fVar19 + _UNK_027edb3c;
        }
      }
      else {
        fVar19 = fVar19 + fVar17;
      }
      *(float *)(lVar11 + 0x3d8) = fVar19;
      (**(code **)(**(long **)(*(long *)puVar6 + 0x28) + 0x50))
                (*(long **)(*(long *)puVar6 + 0x28),lVar11,0);
      uVar10 = 1;
      *(long *)(param_1 + 0x40) = lVar11;
    }
    return uVar10;
  }
  return 0;
}

// ==== Aska::RigidBodyConstraintSlider::CreateBullet()
// vaddr 0x234cdcc | ghidra 0x244cdcc | size 1276 | symbol _ZN4Aska25RigidBodyConstraintSlider12CreateBulletEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska25RigidBodyConstraintSlider12CreateBulletEv(long param_1)

{
  long lVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  undefined8 uVar5;
  byte bVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long *plVar10;
  float fVar11;
  float fVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  float fVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  undefined4 uStack_84;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  undefined4 uStack_74;
  undefined8 uStack_70;
  undefined8 uStack_68;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  
  lVar7 = *(long *)(param_1 + 0x30);
  if ((((lVar7 == 0) || (lVar8 = *(long *)(lVar7 + 0x30), lVar8 == 0)) ||
      (*(long *)(param_1 + 0x38) == 0)) ||
     ((lVar9 = *(long *)(*(long *)(param_1 + 0x38) + 0x30), lVar9 == 0 ||
      (plVar10 = *(long **)(lVar7 + 0x20), plVar10 == (long *)0x0)))) {
    uVar5 = 0;
  }
  else {
    bVar6 = *(byte *)(plVar10 + 0x25);
    if ((bVar6 & 1) != 0) {
      (**(code **)(*plVar10 + 0xa8))(plVar10);
      bVar6 = *(byte *)(plVar10 + 0x25);
    }
    lVar1 = _UNK_027dbb38;
    lVar7 = _UNK_027dbb30;
    if ((bVar6 >> 2 & 1) == 0) {
      if ((*(byte *)((long)plVar10 + 0x129) & 3) == 0) {
        fVar11 = *(float *)((long)plVar10 + 0x4c);
        fVar12 = *(float *)((long)plVar10 + 0x5c);
        fVar15 = *(float *)((long)plVar10 + 0x6c);
        plVar10[0x27] = CONCAT44((int)plVar10[0xe],*(float *)(plVar10 + 0xc));
        plVar10[0x26] = CONCAT44(*(float *)(plVar10 + 10),*(float *)(plVar10 + 8));
        plVar10[0x29] =
             CONCAT44(*(undefined4 *)((long)plVar10 + 0x74),*(float *)((long)plVar10 + 100));
        plVar10[0x28] = CONCAT44(*(float *)((long)plVar10 + 0x54),*(float *)((long)plVar10 + 0x44));
        *(float *)((long)plVar10 + 0x13c) =
             -(*(float *)(plVar10 + 8) * fVar11 + *(float *)(plVar10 + 10) * fVar12 +
              *(float *)(plVar10 + 0xc) * fVar15);
        *(float *)((long)plVar10 + 0x14c) =
             -(fVar11 * *(float *)((long)plVar10 + 0x44) + fVar12 * *(float *)((long)plVar10 + 0x54)
              + fVar15 * *(float *)((long)plVar10 + 100));
        plVar10[0x2b] = CONCAT44((int)plVar10[0xf],*(float *)(plVar10 + 0xd));
        plVar10[0x2a] = CONCAT44(*(float *)(plVar10 + 0xb),*(float *)(plVar10 + 9));
        plVar10[0x2d] = lVar1;
        plVar10[0x2c] = lVar7;
        *(float *)((long)plVar10 + 0x15c) =
             -(fVar11 * *(float *)(plVar10 + 9) + fVar12 * *(float *)(plVar10 + 0xb) +
              fVar15 * *(float *)(plVar10 + 0xd));
      }
      else {
        Aska::Matrix::InvertLowError(Aska::Matrix*) const(plVar10 + 8,plVar10 + 0x26);
        bVar6 = *(byte *)(plVar10 + 0x25);
      }
      *(byte *)(plVar10 + 0x25) = bVar6 | 4;
    }
    Aska::Quaternion::Create(Aska::Matrix const*)(&fStack_60,plVar10 + 0x26);
    puVar3 = PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798;
    if (((*PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798 & 1) == 0) &&
       (iVar4 = __cxa_guard_acquire(PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798)
       , iVar4 != 0)) {
      if (((*PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0 & 1) == 0) &&
         (iVar4 = __cxa_guard_acquire(PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0),
         puVar2 = PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00, iVar4 != 0)) {
        *(undefined4 *)PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 = 0x3f800000;
        *(undefined8 *)(puVar2 + 0xc) = 0;
        *(undefined8 *)(puVar2 + 4) = 0;
        *(undefined4 *)(puVar2 + 0x14) = 0x3f800000;
        *(undefined8 *)(puVar2 + 0x18) = 0;
        *(undefined8 *)(puVar2 + 0x20) = 0;
        *(undefined8 *)(puVar2 + 0x28) = 0x3f800000;
        __cxa_guard_release(PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0);
      }
      puVar2 = PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0;
      uVar5 = *(undefined8 *)PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00;
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
      *(undefined8 *)puVar2 = uVar5;
      *(undefined8 *)(puVar2 + 0x18) = uVar14;
      *(undefined8 *)(puVar2 + 0x10) = uVar13;
      *(undefined8 *)(puVar2 + 0x28) = uVar17;
      *(undefined8 *)(puVar2 + 0x20) = uVar16;
      *(undefined8 *)(puVar2 + 0x30) = 0;
      *(undefined8 *)(puVar2 + 0x38) = 0;
      __cxa_guard_release(PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798);
    }
    puVar2 = PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0;
    uStack_68 = *(undefined8 *)
                 (PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 0x38);
    uStack_70 = *(undefined8 *)
                 (PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 0x30);
    fVar11 = 2.0 / (fStack_60 * fStack_60 + fStack_5c * fStack_5c + fStack_58 * fStack_58 +
                   fStack_54 * fStack_54);
    fVar15 = fStack_5c * fVar11;
    fVar12 = fStack_58 * fVar11;
    fStack_7c = fStack_54 * fStack_60 * fVar11;
    fVar11 = fStack_60 * fStack_60 * fVar11;
    fStack_9c = fStack_60 * fVar15 - fStack_54 * fVar12;
    fStack_98 = fStack_60 * fVar12 + fStack_54 * fVar15;
    fStack_90 = fStack_60 * fVar15 + fStack_54 * fVar12;
    fStack_88 = fStack_5c * fVar12 - fStack_7c;
    fStack_80 = fStack_60 * fVar12 - fStack_54 * fVar15;
    fStack_7c = fStack_5c * fVar12 + fStack_7c;
    fStack_a0 = 1.0 - (fStack_5c * fVar15 + fStack_58 * fVar12);
    fStack_8c = 1.0 - (fVar11 + fStack_58 * fVar12);
    fStack_78 = 1.0 - (fVar11 + fStack_5c * fVar15);
    uStack_94 = 0;
    uStack_84 = 0;
    uStack_74 = 0;
    if (((*puVar3 & 1) == 0) &&
       (iVar4 = __cxa_guard_acquire(PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798)
       , iVar4 != 0)) {
      if (((*PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0 & 1) == 0) &&
         (iVar4 = __cxa_guard_acquire(PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0),
         puVar3 = PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00, iVar4 != 0)) {
        *(undefined4 *)PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 = 0x3f800000;
        *(undefined8 *)(puVar3 + 0xc) = 0;
        *(undefined8 *)(puVar3 + 4) = 0;
        *(undefined4 *)(puVar3 + 0x14) = 0x3f800000;
        *(undefined8 *)(puVar3 + 0x18) = 0;
        *(undefined8 *)(puVar3 + 0x20) = 0;
        *(undefined8 *)(puVar3 + 0x28) = 0x3f800000;
        __cxa_guard_release(PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0);
      }
      puVar3 = PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00;
      *(undefined8 *)(puVar2 + 0x30) = 0;
      *(undefined8 *)(puVar2 + 0x38) = 0;
      uVar5 = *(undefined8 *)puVar3;
      uVar14 = *(undefined8 *)(puVar3 + 0x18);
      uVar13 = *(undefined8 *)(puVar3 + 0x10);
      uVar17 = *(undefined8 *)(puVar3 + 0x28);
      uVar16 = *(undefined8 *)(puVar3 + 0x20);
      *(undefined8 *)(puVar2 + 8) = *(undefined8 *)(puVar3 + 8);
      *(undefined8 *)puVar2 = uVar5;
      *(undefined8 *)(puVar2 + 0x18) = uVar14;
      *(undefined8 *)(puVar2 + 0x10) = uVar13;
      *(undefined8 *)(puVar2 + 0x28) = uVar17;
      *(undefined8 *)(puVar2 + 0x20) = uVar16;
      __cxa_guard_release(PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798);
    }
    uStack_d8 = *(undefined8 *)(puVar2 + 8);
    uStack_e0 = *(undefined8 *)puVar2;
    uStack_c8 = *(undefined8 *)(puVar2 + 0x18);
    uStack_d0 = *(undefined8 *)(puVar2 + 0x10);
    uStack_b8 = *(undefined8 *)(puVar2 + 0x28);
    uStack_c0 = *(undefined8 *)(puVar2 + 0x20);
    uStack_a8 = *(undefined8 *)(puVar2 + 0x38);
    uStack_b0 = *(undefined8 *)(puVar2 + 0x30);
    lVar7 = operator new(unsigned long, std::nothrow_t const&)(0x450,PTR__ZSt7nothrow_02cb9a80);
    uVar5 = 0;
    if (lVar7 != 0) {
      btSliderConstraint::btSliderConstraint(btRigidBody&, btRigidBody&, btTransform const&, btTransform const&, bool)(lVar7,lVar9,lVar8,&uStack_e0,&fStack_a0,1);
      lVar8 = *(long *)(param_1 + 0x28);
      *(undefined4 *)(lVar7 + 0xe4) = *(undefined4 *)(lVar8 + 0x10c);
      *(undefined4 *)(lVar7 + 0xe8) = *(undefined4 *)(lVar8 + 0x110);
      fVar12 = _UNK_027edb34;
      fVar15 = (float)fmodf(*(undefined4 *)(lVar8 + 0x114),_UNK_027edb34);
      fVar11 = _UNK_027edb30;
      if (_UNK_027edb30 <= fVar15) {
        if (_UNK_027e3fd0 < fVar15) {
          fVar15 = fVar15 + _UNK_027edb3c;
        }
      }
      else {
        fVar15 = fVar15 + fVar12;
      }
      *(float *)(lVar7 + 0xec) = fVar15;
      fVar15 = (float)fmodf(*(undefined4 *)(*(long *)(param_1 + 0x28) + 0x118),fVar12);
      if (fVar11 <= fVar15) {
        if (_UNK_027e3fd0 < fVar15) {
          fVar15 = fVar15 + _UNK_027edb3c;
        }
      }
      else {
        fVar15 = fVar15 + fVar12;
      }
      *(float *)(lVar7 + 0xf0) = fVar15;
      lVar8 = *(long *)(param_1 + 0x28);
      *(undefined4 *)(lVar7 + 0xf4) = *(undefined4 *)(lVar8 + 0x11c);
      *(undefined4 *)(lVar7 + 0xf8) = *(undefined4 *)(lVar8 + 0x120);
      *(undefined4 *)(lVar7 + 0xfc) = *(undefined4 *)(lVar8 + 0x124);
      *(undefined4 *)(lVar7 + 0x104) = *(undefined4 *)(lVar8 + 0x128);
      *(undefined4 *)(lVar7 + 0x108) = *(undefined4 *)(lVar8 + 300);
      *(undefined4 *)(lVar7 + 0x110) = *(undefined4 *)(lVar8 + 0x130);
      *(bool *)(lVar7 + 0x430) = *(int *)(lVar8 + 0x134) != 0;
      if (*(int *)(lVar8 + 0x134) != 0) {
        *(undefined4 *)(lVar7 + 0x434) = *(undefined4 *)(lVar8 + 0x138);
        *(undefined4 *)(lVar7 + 0x438) = *(undefined4 *)(lVar8 + 0x13c);
      }
      *(bool *)(lVar7 + 0x440) = *(int *)(lVar8 + 0x140) != 0;
      if (*(int *)(lVar8 + 0x140) != 0) {
        *(undefined4 *)(lVar7 + 0x444) = *(undefined4 *)(lVar8 + 0x144);
        *(undefined4 *)(lVar7 + 0x448) = *(undefined4 *)(lVar8 + 0x148);
      }
      (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                  0x50))(*(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 +
                                   0x28),lVar7,0);
      uVar5 = 1;
      *(long *)(param_1 + 0x40) = lVar7;
    }
  }
  return uVar5;
}

// ==== Aska::RigidBodyConstraintCone::CreateBullet()
// vaddr 0x234d2c8 | ghidra 0x244d2c8 | size 764 | symbol _ZN4Aska23RigidBodyConstraintCone12CreateBulletEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska23RigidBodyConstraintCone12CreateBulletEv(long param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined *puVar7;
  undefined *puVar8;
  int iVar9;
  long lVar10;
  long lVar11;
  undefined8 uVar12;
  long lVar13;
  long lVar14;
  long *plVar15;
  long *plVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  
  lVar10 = *(long *)(param_1 + 0x30);
  if (((((lVar10 == 0) || (lVar13 = *(long *)(lVar10 + 0x30), lVar13 == 0)) ||
       (lVar11 = *(long *)(param_1 + 0x38), lVar11 == 0)) ||
      ((lVar14 = *(long *)(lVar11 + 0x30), lVar14 == 0 ||
       (plVar15 = *(long **)(lVar10 + 0x20), plVar15 == (long *)0x0)))) ||
     (plVar16 = *(long **)(lVar11 + 0x20), plVar16 == (long *)0x0)) {
    uVar12 = 0;
  }
  else {
    if ((*(byte *)(plVar15 + 0x25) & 1) != 0) {
      (**(code **)(*plVar15 + 0xa8))(plVar15);
    }
    if ((*(byte *)(plVar16 + 0x25) & 1) != 0) {
      (**(code **)(*plVar16 + 0xa8))(plVar16);
    }
    puVar8 = PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798;
    uVar1 = *(undefined4 *)((long)plVar15 + 0x4c);
    uVar2 = *(undefined4 *)((long)plVar15 + 0x5c);
    uVar3 = *(undefined4 *)((long)plVar15 + 0x6c);
    uVar4 = *(undefined4 *)((long)plVar16 + 0x4c);
    uVar5 = *(undefined4 *)((long)plVar16 + 0x5c);
    uVar6 = *(undefined4 *)((long)plVar16 + 0x6c);
    if (((*PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798 & 1) == 0) &&
       (iVar9 = __cxa_guard_acquire(PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798)
       , iVar9 != 0)) {
      if (((*PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0 & 1) == 0) &&
         (iVar9 = __cxa_guard_acquire(PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0),
         puVar7 = PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00, iVar9 != 0)) {
        *(undefined4 *)PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 = 0x3f800000;
        *(undefined8 *)(puVar7 + 0xc) = 0;
        *(undefined8 *)(puVar7 + 4) = 0;
        *(undefined4 *)(puVar7 + 0x14) = 0x3f800000;
        *(undefined8 *)(puVar7 + 0x18) = 0;
        *(undefined8 *)(puVar7 + 0x20) = 0;
        *(undefined8 *)(puVar7 + 0x28) = 0x3f800000;
        __cxa_guard_release(PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0);
      }
      puVar7 = PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0;
      uVar12 = *(undefined8 *)PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00;
      uVar18 = *(undefined8 *)
                (PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 + 0x18);
      uVar17 = *(undefined8 *)
                (PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 + 0x10);
      uVar20 = *(undefined8 *)
                (PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 + 0x28);
      uVar19 = *(undefined8 *)
                (PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 + 0x20);
      *(undefined8 *)(PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 8) =
           *(undefined8 *)(PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 + 8);
      *(undefined8 *)puVar7 = uVar12;
      *(undefined8 *)(puVar7 + 0x18) = uVar18;
      *(undefined8 *)(puVar7 + 0x10) = uVar17;
      *(undefined8 *)(puVar7 + 0x28) = uVar20;
      *(undefined8 *)(puVar7 + 0x20) = uVar19;
      *(undefined8 *)(puVar7 + 0x30) = 0;
      *(undefined8 *)(puVar7 + 0x38) = 0;
      __cxa_guard_release(PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798);
    }
    puVar7 = PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0;
    uStack_64 = 0;
    uStack_98 = *(undefined8 *)
                 (PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 8);
    uStack_a0 = *(undefined8 *)PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0;
    uStack_88 = *(undefined8 *)
                 (PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 0x18);
    uStack_90 = *(undefined8 *)
                 (PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 0x10);
    uStack_78 = *(undefined8 *)
                 (PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 0x28);
    uStack_80 = *(undefined8 *)
                 (PTR__ZZN11btTransform11getIdentityEvE17identityTransform_02cbd2b0 + 0x20);
    uStack_70 = uVar1;
    uStack_6c = uVar2;
    uStack_68 = uVar3;
    if (((*puVar8 & 1) == 0) &&
       (iVar9 = __cxa_guard_acquire(PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798)
       , iVar9 != 0)) {
      if (((*PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0 & 1) == 0) &&
         (iVar9 = __cxa_guard_acquire(PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0),
         puVar8 = PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00, iVar9 != 0)) {
        *(undefined4 *)PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00 = 0x3f800000;
        *(undefined8 *)(puVar8 + 0xc) = 0;
        *(undefined8 *)(puVar8 + 4) = 0;
        *(undefined4 *)(puVar8 + 0x14) = 0x3f800000;
        *(undefined8 *)(puVar8 + 0x18) = 0;
        *(undefined8 *)(puVar8 + 0x20) = 0;
        *(undefined8 *)(puVar8 + 0x28) = 0x3f800000;
        __cxa_guard_release(PTR__ZGVZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc0ff0);
      }
      puVar8 = PTR__ZZN11btMatrix3x311getIdentityEvE14identityMatrix_02cc1f00;
      *(undefined8 *)(puVar7 + 0x30) = 0;
      *(undefined8 *)(puVar7 + 0x38) = 0;
      uVar12 = *(undefined8 *)puVar8;
      uVar18 = *(undefined8 *)(puVar8 + 0x18);
      uVar17 = *(undefined8 *)(puVar8 + 0x10);
      uVar20 = *(undefined8 *)(puVar8 + 0x28);
      uVar19 = *(undefined8 *)(puVar8 + 0x20);
      *(undefined8 *)(puVar7 + 8) = *(undefined8 *)(puVar8 + 8);
      *(undefined8 *)puVar7 = uVar12;
      *(undefined8 *)(puVar7 + 0x18) = uVar18;
      *(undefined8 *)(puVar7 + 0x10) = uVar17;
      *(undefined8 *)(puVar7 + 0x28) = uVar20;
      *(undefined8 *)(puVar7 + 0x20) = uVar19;
      __cxa_guard_release(PTR__ZGVZN11btTransform11getIdentityEvE17identityTransform_02cbe798);
    }
    uStack_d8 = *(undefined8 *)(puVar7 + 8);
    uStack_e0 = *(undefined8 *)puVar7;
    uStack_c8 = *(undefined8 *)(puVar7 + 0x18);
    uStack_d0 = *(undefined8 *)(puVar7 + 0x10);
    uStack_b8 = *(undefined8 *)(puVar7 + 0x28);
    uStack_c0 = *(undefined8 *)(puVar7 + 0x20);
    uStack_a4 = 0;
    uStack_b0 = uVar4;
    uStack_ac = uVar5;
    uStack_a8 = uVar6;
    lVar10 = operator new(unsigned long, std::nothrow_t const&)(0x280,PTR__ZSt7nothrow_02cb9a80);
    uVar12 = 0;
    if (lVar10 != 0) {
      btConeTwistConstraint::btConeTwistConstraint(btRigidBody&, btRigidBody&, btTransform const&, btTransform const&)(lVar10,lVar14,lVar13,&uStack_a0,&uStack_e0);
      lVar13 = *(long *)(param_1 + 0x28);
      uVar1 = *(undefined4 *)(lVar13 + 0x120);
      uVar2 = *(undefined4 *)(lVar13 + 0x124);
      uVar3 = *(undefined4 *)(lVar13 + 0x114);
      uVar12 = *(undefined8 *)(lVar13 + 0x10c);
      *(undefined4 *)(lVar10 + 0x1ec) = *(undefined4 *)(lVar13 + 0x11c);
      *(undefined4 *)(lVar10 + 0x1f0) = uVar1;
      *(undefined4 *)(lVar10 + 500) = uVar2;
      *(undefined8 *)(lVar10 + 0x1dc) = uVar12;
      *(undefined4 *)(lVar10 + 0x1e4) = uVar3;
      *(undefined4 *)(lVar10 + 0x1e8) = *(undefined4 *)(lVar13 + 0x118);
      *(undefined4 *)(lVar10 + 0x1f8) = *(undefined4 *)(lVar13 + 0x128);
      *(bool *)(lVar10 + 0x23c) = *(int *)(lVar13 + 300) != 0;
      *(bool *)(lVar10 + 600) = *(int *)(lVar13 + 0x130) != 0;
      if (*(int *)(lVar13 + 0x130) != 0) {
        uVar1 = *(undefined4 *)(lVar13 + 0x134);
        *(undefined1 *)(lVar10 + 0x259) = 0;
        *(undefined4 *)(lVar10 + 0x26c) = uVar1;
      }
      (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                  0x50))(*(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 +
                                   0x28),lVar10,0);
      uVar12 = 1;
      *(long *)(param_1 + 0x40) = lVar10;
    }
  }
  return uVar12;
}

// ==== Aska::RigidBodyConstraintBase::CreateBullet()
// vaddr 0x234d5c4 | ghidra 0x244d5c4 | size 8 | symbol _ZN4Aska23RigidBodyConstraintBase12CreateBulletEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska23RigidBodyConstraintBase12CreateBulletEv(void)

{
  return 0;
}

// ==== Aska::RigidBodyConstraintNail::~RigidBodyConstraintNail()
// vaddr 0x234d5cc | ghidra 0x244d5cc | size 108 | symbol _ZN4Aska23RigidBodyConstraintNailD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23RigidBodyConstraintNailD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska23RigidBodyConstraintBaseE_02cc1610;
  param_1[5] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  if (param_1[8] != 0) {
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x58))();
    if ((long *)param_1[8] != (long *)0x0) {
      (**(code **)(*(long *)param_1[8] + 8))();
    }
    param_1[8] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RigidBodyConstraintHinge::~RigidBodyConstraintHinge()
// vaddr 0x234d638 | ghidra 0x244d638 | size 108 | symbol _ZN4Aska24RigidBodyConstraintHingeD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska24RigidBodyConstraintHingeD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska23RigidBodyConstraintBaseE_02cc1610;
  param_1[5] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  if (param_1[8] != 0) {
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x58))();
    if ((long *)param_1[8] != (long *)0x0) {
      (**(code **)(*(long *)param_1[8] + 8))();
    }
    param_1[8] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RigidBodyConstraintSixDOF::~RigidBodyConstraintSixDOF()
// vaddr 0x234d6a4 | ghidra 0x244d6a4 | size 108 | symbol _ZN4Aska25RigidBodyConstraintSixDOFD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska25RigidBodyConstraintSixDOFD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska23RigidBodyConstraintBaseE_02cc1610;
  param_1[5] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  if (param_1[8] != 0) {
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x58))();
    if ((long *)param_1[8] != (long *)0x0) {
      (**(code **)(*(long *)param_1[8] + 8))();
    }
    param_1[8] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RigidBodyConstraintBase::~RigidBodyConstraintBase()
// vaddr 0x234d710 | ghidra 0x244d710 | size 100 | symbol _ZN4Aska23RigidBodyConstraintBaseD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23RigidBodyConstraintBaseD2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska23RigidBodyConstraintBaseE_02cc1610;
  param_1[5] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  if (param_1[8] != 0) {
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x58))();
    if ((long *)param_1[8] != (long *)0x0) {
      (**(code **)(*(long *)param_1[8] + 8))();
    }
    param_1[8] = 0;
  }
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1);
  return;
}

// ==== Aska::RigidBodyConstraintSlider::~RigidBodyConstraintSlider()
// vaddr 0x234d774 | ghidra 0x244d774 | size 108 | symbol _ZN4Aska25RigidBodyConstraintSliderD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska25RigidBodyConstraintSliderD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska23RigidBodyConstraintBaseE_02cc1610;
  param_1[5] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  if (param_1[8] != 0) {
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x58))();
    if ((long *)param_1[8] != (long *)0x0) {
      (**(code **)(*(long *)param_1[8] + 8))();
    }
    param_1[8] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RigidBodyConstraintCone::~RigidBodyConstraintCone()
// vaddr 0x234d7e0 | ghidra 0x244d7e0 | size 108 | symbol _ZN4Aska23RigidBodyConstraintConeD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23RigidBodyConstraintConeD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska23RigidBodyConstraintBaseE_02cc1610;
  param_1[5] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  if (param_1[8] != 0) {
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x58))();
    if ((long *)param_1[8] != (long *)0x0) {
      (**(code **)(*(long *)param_1[8] + 8))();
    }
    param_1[8] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RigidBodyManager::InitBullet()
// vaddr 0x234d980 | ghidra 0x244d980 | size 488 | symbol _ZN4Aska16RigidBodyManager10InitBulletEv | lib libSOA-3.7.0.so | 2026-10-08
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
// vaddr 0x234db98 | ghidra 0x244db98 | size 168 | symbol _ZN4Aska16RigidBodyManagerC1Ev | lib libSOA-3.7.0.so | 2026-10-08
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
// vaddr 0x234dc40 | ghidra 0x244dc40 | size 192 | symbol _ZN4Aska16RigidBodyManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-08
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
// vaddr 0x234dd00 | ghidra 0x244dd00 | size 148 | symbol _ZN4Aska16RigidBodyManager12DeleteBulletEv | lib libSOA-3.7.0.so | 2026-10-08
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
// vaddr 0x234dda8 | ghidra 0x244dda8 | size 24 | symbol _ZN4Aska16RigidBodyManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16RigidBodyManagerD0Ev(undefined8 param_1)

{
  Aska::RigidBodyManager::~RigidBodyManager()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RigidBodyManager::Add(Aska::RigidBodyPrimitiveBase*)
// vaddr 0x234ddc0 | ghidra 0x244ddc0 | size 36 | symbol _ZN4Aska16RigidBodyManager3AddEPNS_22RigidBodyPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
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
// vaddr 0x234de08 | ghidra 0x244de08 | size 64 | symbol _ZN4Aska16RigidBodyManager6RemoveEPNS_22RigidBodyPrimitiveBaseE | lib libSOA-3.7.0.so | 2026-10-08
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
// vaddr 0x234de88 | ghidra 0x244de88 | size 272 | symbol _ZN4Aska16RigidBodyManager8SimulateEv | lib libSOA-3.7.0.so | 2026-10-08
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
// vaddr 0x234df98 | ghidra 0x244df98 | size 104 | symbol _ZN4Aska16RigidBodyManager10ResetSceneEv | lib libSOA-3.7.0.so | 2026-10-08
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
// vaddr 0x234e000 | ghidra 0x244e000 | size 20 | symbol _ZN4Aska16RigidBodyManager3RunEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16RigidBodyManager3RunEi(long param_1)

{
  if (0 < *(int *)(param_1 + 0xa0)) {
    (*(code *)PTR__ZN4Aska16RigidBodyManager8SimulateEv_02c93cc8)();
    return;
  }
  return;
}

// ==== Aska::RigidBodyManager::Get(unsigned long, void*) const
// vaddr 0x234e014 | ghidra 0x244e014 | size 8 | symbol _ZNK4Aska16RigidBodyManager3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska16RigidBodyManager3GetEmPv(void)

{
  return 0;
}

// ==== Aska::RigidBodyManager::Set(unsigned long, void const*)
// vaddr 0x234e01c | ghidra 0x244e01c | size 124 | symbol _ZN4Aska16RigidBodyManager3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
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
// vaddr 0x234e098 | ghidra 0x244e098 | size 64 | symbol _ZNK4Aska16RigidBodyManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
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
// vaddr 0x234e0d8 | ghidra 0x244e0d8 | size 8 | symbol _ZNK4Aska16RigidBodyManager15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska16RigidBodyManager15GetDefaultLevelEv(void)

{
  return 0x4000;
}

// ==== Aska::RigidBodyPrimitiveBase::~RigidBodyPrimitiveBase()
// vaddr 0x234e318 | ghidra 0x244e318 | size 180 | symbol _ZN4Aska22RigidBodyPrimitiveBaseD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22RigidBodyPrimitiveBaseD0Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska22RigidBodyPrimitiveBaseE_02cc25b8 + 0x10);
  plVar1 = (long *)param_1[6];
  if (((plVar1 != (long *)0x0) && (param_1[7] != 0)) && (param_1[8] != 0)) {
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x90))(*(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28
                                 ),plVar1);
    (**(code **)(*plVar1 + 8))(plVar1);
    (*(code *)**(undefined8 **)param_1[7])();
    (*(code *)**(undefined8 **)param_1[8])();
    if (param_1[6] != 0) {
      operator delete[](void*)();
    }
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[6] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RigidBodyPrimitiveBase::Reset()
// vaddr 0x234e3cc | ghidra 0x244e3cc | size 212 | symbol _ZN4Aska22RigidBodyPrimitiveBase5ResetEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22RigidBodyPrimitiveBase5ResetEv(long param_1)

{
  undefined4 uVar1;
  undefined8 uVar2;
  long lVar3;
  long lVar4;
  
  lVar3 = *(long *)(param_1 + 0x30);
  if ((lVar3 != 0) && (lVar4 = *(long *)(lVar3 + 0x200), lVar4 != 0)) {
    *(undefined8 *)(lVar4 + 0x10) = *(undefined8 *)(lVar4 + 0x90);
    *(undefined8 *)(lVar4 + 8) = *(undefined8 *)(lVar4 + 0x88);
    *(undefined8 *)(lVar4 + 0x20) = *(undefined8 *)(lVar4 + 0xa0);
    *(undefined8 *)(lVar4 + 0x18) = *(undefined8 *)(lVar4 + 0x98);
    *(undefined8 *)(lVar4 + 0x30) = *(undefined8 *)(lVar4 + 0xb0);
    *(undefined8 *)(lVar4 + 0x28) = *(undefined8 *)(lVar4 + 0xa8);
    *(undefined8 *)(lVar4 + 0x40) = *(undefined8 *)(lVar4 + 0xc0);
    *(undefined8 *)(lVar4 + 0x38) = *(undefined8 *)(lVar4 + 0xb8);
    *(undefined8 *)(lVar3 + 0x1d4) = 0;
    *(undefined8 *)(lVar3 + 0x1cc) = 0;
    *(undefined8 *)(lVar3 + 0x1c4) = 0;
    *(undefined8 *)(lVar3 + 0x1bc) = 0;
    btRigidBody::setCenterOfMassTransform(btTransform const&)(lVar3,lVar4 + 8);
    uVar2 = *(undefined8 *)(lVar4 + 0x88);
    *(undefined8 *)(lVar3 + 0x50) = *(undefined8 *)(lVar4 + 0x90);
    *(undefined8 *)(lVar3 + 0x48) = uVar2;
    uVar2 = *(undefined8 *)(lVar4 + 0x98);
    *(undefined8 *)(lVar3 + 0x60) = *(undefined8 *)(lVar4 + 0xa0);
    *(undefined8 *)(lVar3 + 0x58) = uVar2;
    uVar2 = *(undefined8 *)(lVar4 + 0xa8);
    *(undefined8 *)(lVar3 + 0x70) = *(undefined8 *)(lVar4 + 0xb0);
    *(undefined8 *)(lVar3 + 0x68) = uVar2;
    uVar2 = *(undefined8 *)(lVar4 + 0xb8);
    *(undefined8 *)(lVar3 + 0x80) = *(undefined8 *)(lVar4 + 0xc0);
    *(undefined8 *)(lVar3 + 0x78) = uVar2;
    uVar2 = *(undefined8 *)(*(long *)(param_1 + 0x28) + 0x18);
    uVar1 = *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x20);
    *(undefined4 *)(lVar3 + 0x154) = 0;
    *(undefined8 *)(lVar3 + 0x148) = uVar2;
    *(undefined4 *)(lVar3 + 0x150) = uVar1;
    uVar2 = *(undefined8 *)(*(long *)(param_1 + 0x28) + 0x24);
    uVar1 = *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x2c);
    *(undefined4 *)(lVar3 + 0x164) = 0;
    *(undefined8 *)(lVar3 + 0x158) = uVar2;
    *(undefined4 *)(lVar3 + 0x160) = uVar1;
    btCollisionObject::forceActivationState(int)(lVar3,1);
    btCollisionObject::activate(bool)(lVar3,0);
    *(undefined4 *)(lVar3 + 0xe8) = 0;
  }
  return;
}

// ==== Aska::RigidBodyPrimitiveBase::SetTransform(Aska::Vector const*, Aska::Quaternion const*)
// vaddr 0x234e4a0 | ghidra 0x244e4a0 | size 332 | symbol _ZN4Aska22RigidBodyPrimitiveBase12SetTransformEPKNS_6VectorEPKNS_10QuaternionE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22RigidBodyPrimitiveBase12SetTransformEPKNS_6VectorEPKNS_10QuaternionE
               (long param_1,undefined8 *param_2,float *param_3)

{
  long lVar1;
  long lVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
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
  undefined4 uStack_24;
  undefined8 uStack_20;
  uint uStack_18;
  undefined4 uStack_14;
  
  lVar2 = *(long *)(param_1 + 0x30);
  if ((lVar2 != 0) && (lVar1 = *(long *)(lVar2 + 0x200), lVar1 != 0)) {
    fVar3 = *param_3;
    fVar4 = param_3[1];
    fVar5 = param_3[2];
    fVar6 = param_3[3];
    fVar7 = 2.0 / (fVar3 * fVar3 + fVar4 * fVar4 + fVar5 * fVar5 + fVar6 * fVar6);
    fVar9 = fVar4 * fVar7;
    fVar8 = fVar5 * fVar7;
    fStack_2c = fVar6 * fVar3 * fVar7;
    fVar7 = fVar3 * fVar3 * fVar7;
    fStack_4c = fVar3 * fVar9 - fVar6 * fVar8;
    fStack_48 = fVar3 * fVar8 + fVar6 * fVar9;
    fStack_50 = 1.0 - (fVar4 * fVar9 + fVar5 * fVar8);
    uStack_20 = *param_2;
    uStack_18 = *(uint *)(param_2 + 1);
    fStack_40 = fVar3 * fVar9 + fVar6 * fVar8;
    fStack_38 = fVar4 * fVar8 - fStack_2c;
    fStack_30 = fVar3 * fVar8 - fVar6 * fVar9;
    fStack_2c = fVar4 * fVar8 + fStack_2c;
    uStack_44 = 0;
    fStack_3c = 1.0 - (fVar7 + fVar5 * fVar8);
    fStack_28 = 1.0 - (fVar7 + fVar4 * fVar9);
    uStack_34 = 0;
    uStack_24 = 0;
    uStack_14 = 0;
    *(ulong *)(lVar1 + 0x10) = (ulong)(uint)fStack_48;
    *(ulong *)(lVar1 + 8) = CONCAT44(fStack_4c,fStack_50);
    *(ulong *)(lVar1 + 0x20) = (ulong)(uint)fStack_38;
    *(ulong *)(lVar1 + 0x18) = CONCAT44(fStack_3c,fStack_40);
    *(ulong *)(lVar1 + 0x30) = (ulong)(uint)fStack_28;
    *(ulong *)(lVar1 + 0x28) = CONCAT44(fStack_2c,fStack_30);
    *(ulong *)(lVar1 + 0x40) = (ulong)uStack_18;
    *(undefined8 *)(lVar1 + 0x38) = uStack_20;
    btRigidBody::setCenterOfMassTransform(btTransform const&)(lVar2,&fStack_50);
    *(ulong *)(lVar2 + 0x50) = CONCAT44(uStack_44,fStack_48);
    *(ulong *)(lVar2 + 0x48) = CONCAT44(fStack_4c,fStack_50);
    *(ulong *)(lVar2 + 0x60) = CONCAT44(uStack_34,fStack_38);
    *(ulong *)(lVar2 + 0x58) = CONCAT44(fStack_3c,fStack_40);
    *(ulong *)(lVar2 + 0x70) = CONCAT44(uStack_24,fStack_28);
    *(ulong *)(lVar2 + 0x68) = CONCAT44(fStack_2c,fStack_30);
    *(ulong *)(lVar2 + 0x80) = CONCAT44(uStack_14,uStack_18);
    *(undefined8 *)(lVar2 + 0x78) = uStack_20;
    btCollisionObject::forceActivationState(int)(lVar2,1);
    btCollisionObject::activate(bool)(lVar2,0);
  }
  return;
}

// ==== Aska::RigidBodyPrimitiveBase::SetLinearVelocity(Aska::Vector const*)
// vaddr 0x234e5ec | ghidra 0x244e5ec | size 68 | symbol _ZN4Aska22RigidBodyPrimitiveBase17SetLinearVelocityEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22RigidBodyPrimitiveBase17SetLinearVelocityEPKNS_6VectorE
               (long param_1,undefined8 *param_2)

{
  undefined4 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x30);
  if (lVar2 != 0) {
    uVar1 = *(undefined4 *)(param_2 + 1);
    *(undefined8 *)(lVar2 + 0x148) = *param_2;
    *(undefined4 *)(lVar2 + 0x150) = uVar1;
    *(undefined4 *)(lVar2 + 0x154) = 0;
    btCollisionObject::forceActivationState(int)(lVar2,1);
    (*(code *)PTR__ZN17btCollisionObject8activateEb_02cb2248)(lVar2,0);
    return;
  }
  return;
}

// ==== Aska::RigidBodyPrimitiveBase::SetAngularVelocity(Aska::Vector const*)
// vaddr 0x234e630 | ghidra 0x244e630 | size 68 | symbol _ZN4Aska22RigidBodyPrimitiveBase18SetAngularVelocityEPKNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22RigidBodyPrimitiveBase18SetAngularVelocityEPKNS_6VectorE
               (long param_1,undefined8 *param_2)

{
  undefined4 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x30);
  if (lVar2 != 0) {
    uVar1 = *(undefined4 *)(param_2 + 1);
    *(undefined8 *)(lVar2 + 0x158) = *param_2;
    *(undefined4 *)(lVar2 + 0x160) = uVar1;
    *(undefined4 *)(lVar2 + 0x164) = 0;
    btCollisionObject::forceActivationState(int)(lVar2,1);
    (*(code *)PTR__ZN17btCollisionObject8activateEb_02cb2248)(lVar2,0);
    return;
  }
  return;
}

// ==== Aska::RigidBodyPrimitiveBase::LocalCreateBullet()
// vaddr 0x234e674 | ghidra 0x244e674 | size 916 | symbol _ZN4Aska22RigidBodyPrimitiveBase17LocalCreateBulletEv | lib libSOA-3.7.0.so | 2026-10-08
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

// ==== Aska::RigidBodyPrimitiveBase::Get(unsigned long, void*) const
// vaddr 0x234ea08 | ghidra 0x244ea08 | size 200 | symbol _ZNK4Aska22RigidBodyPrimitiveBase3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska22RigidBodyPrimitiveBase3GetEmPv(long param_1,ulong param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  long lVar2;
  
  if ((param_2 & 0xffff00000000) != 0) {
    return 0;
  }
  lVar2 = *(long *)(param_1 + 0x28);
  if (lVar2 == 0) {
    return 0;
  }
  switch((uint)param_2 & 0xffff) {
  case 2:
    *param_3 = *(undefined4 *)(lVar2 + 4);
    break;
  case 3:
    *param_3 = *(undefined4 *)(lVar2 + 8);
    break;
  case 4:
    *param_3 = *(undefined4 *)(lVar2 + 0xc);
    break;
  case 5:
    *param_3 = *(undefined4 *)(lVar2 + 0x10);
    break;
  case 6:
    *param_3 = *(undefined4 *)(lVar2 + 0x14);
    break;
  case 7:
    *param_3 = *(undefined4 *)(lVar2 + 0x18);
    param_3[1] = *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x1c);
    uVar1 = *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x20);
    goto code_r0x0244eac4;
  case 8:
    *param_3 = *(undefined4 *)(lVar2 + 0x24);
    param_3[1] = *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x28);
    uVar1 = *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x2c);
code_r0x0244eac4:
    param_3[2] = uVar1;
    break;
  default:
    return 0;
  }
  return 1;
}

// ==== Aska::RigidBodyPrimitiveBase::Set(unsigned long, void const*)
// vaddr 0x234ead0 | ghidra 0x244ead0 | size 204 | symbol _ZN4Aska22RigidBodyPrimitiveBase3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska22RigidBodyPrimitiveBase3SetEmPKv(long param_1,undefined8 param_2,undefined4 *param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  uVar1 = 0;
  if (((short)((ulong)param_2 >> 0x20) == 0) && (lVar2 = *(long *)(param_1 + 0x28), lVar2 != 0)) {
    switch((uint)param_2 & 0xffff) {
    case 2:
      *(undefined4 *)(lVar2 + 4) = *param_3;
      break;
    case 3:
      *(undefined4 *)(lVar2 + 8) = *param_3;
      break;
    case 4:
      *(undefined4 *)(lVar2 + 0xc) = *param_3;
      break;
    case 5:
      *(undefined4 *)(lVar2 + 0x10) = *param_3;
      break;
    case 6:
      *(undefined4 *)(lVar2 + 0x14) = *param_3;
      break;
    case 7:
      *(undefined4 *)(lVar2 + 0x18) = *param_3;
      *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x1c) = param_3[1];
      *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x20) = param_3[2];
      break;
    case 8:
      *(undefined4 *)(lVar2 + 0x24) = *param_3;
      *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x28) = param_3[1];
      *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x2c) = param_3[2];
      break;
    default:
      return 0;
    }
    uVar1 = 1;
  }
  return uVar1;
}

// ==== Aska::RigidBodyPrimitiveSphere::CreateBullet()
// vaddr 0x234eb9c | ghidra 0x244eb9c | size 164 | symbol _ZN4Aska24RigidBodyPrimitiveSphere12CreateBulletEv | lib libSOA-3.7.0.so | 2026-10-08
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

// ==== Aska::RigidBodyPrimitiveSphere::Get(unsigned long, void*) const
// vaddr 0x234ec40 | ghidra 0x244ec40 | size 212 | symbol _ZNK4Aska24RigidBodyPrimitiveSphere3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZNK4Aska24RigidBodyPrimitiveSphere3GetEmPv(long param_1,ulong param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x28);
  if (((param_2 & 0xffff0000ffff) == 0x11) && (lVar2 != 0)) {
    uVar1 = *(undefined4 *)(lVar2 + 0x30);
    goto code_r0x0244ec58;
  }
  if ((param_2 & 0xffff00000000) != 0) {
    return 0;
  }
  if (lVar2 == 0) {
    return 0;
  }
  switch((uint)param_2 & 0xffff) {
  case 2:
    uVar1 = *(undefined4 *)(lVar2 + 4);
    break;
  case 3:
    uVar1 = *(undefined4 *)(lVar2 + 8);
    break;
  case 4:
    uVar1 = *(undefined4 *)(lVar2 + 0xc);
    break;
  case 5:
    uVar1 = *(undefined4 *)(lVar2 + 0x10);
    break;
  case 6:
    uVar1 = *(undefined4 *)(lVar2 + 0x14);
    break;
  case 7:
    *param_3 = *(undefined4 *)(lVar2 + 0x18);
    param_3[1] = *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x1c);
    uVar1 = *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x20);
    goto code_r0x0244ed0c;
  case 8:
    *param_3 = *(undefined4 *)(lVar2 + 0x24);
    param_3[1] = *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x28);
    uVar1 = *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x2c);
code_r0x0244ed0c:
    param_3[2] = uVar1;
    return 1;
  default:
    return 0;
  }
code_r0x0244ec58:
  *param_3 = uVar1;
  return 1;
}

// ==== Aska::RigidBodyPrimitiveCube::CreateBullet()
// vaddr 0x234ed14 | ghidra 0x244ed14 | size 300 | symbol _ZN4Aska22RigidBodyPrimitiveCube12CreateBulletEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska22RigidBodyPrimitiveCube12CreateBulletEv(long param_1)

{
  undefined8 uVar1;
  long lVar2;
  long lVar3;
  code *pcVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  long *plVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  
  if (*(long *)(param_1 + 0x28) != 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(0x348,0x10,1);
    *(long *)(param_1 + 0x30) = lVar2;
    if (lVar2 != 0) {
      lVar3 = *(long *)(param_1 + 0x28);
      plVar8 = (long *)(lVar2 + _UNK_029e3c30);
      *(long *)(param_1 + 0x40) = lVar2 + _UNK_029e3c38;
      *(long **)(param_1 + 0x38) = plVar8;
      fVar9 = *(float *)(lVar3 + 0x30);
      fVar10 = *(float *)(lVar3 + 0x34);
      fVar11 = *(float *)(lVar3 + 0x38);
      btPolyhedralConvexShape::btPolyhedralConvexShape()(plVar8);
      pcVar4 = *(code **)(PTR__ZTV10btBoxShape_02cbaac8 + 0x68);
      *plVar8 = (long)(PTR__ZTV10btBoxShape_02cbaac8 + 0x10);
      *(undefined4 *)(lVar2 + 0x240) = 0;
      fVar5 = (float)(*pcVar4)(plVar8);
      fVar6 = (float)(**(code **)(*plVar8 + 0x58))(plVar8);
      fVar7 = (float)(**(code **)(*plVar8 + 0x58))(plVar8);
      *(undefined4 *)(lVar2 + 0x26c) = 0;
      *(float *)(lVar2 + 0x260) = fVar9 * 0.5 * *(float *)(lVar2 + 0x250) - fVar5;
      *(float *)(lVar2 + 0x264) = fVar10 * 0.5 * *(float *)(lVar2 + 0x254) - fVar6;
      *(float *)(lVar2 + 0x268) = fVar11 * 0.5 * *(float *)(lVar2 + 600) - fVar7;
      uVar1 = (*(code *)PTR__ZN4Aska22RigidBodyPrimitiveBase17LocalCreateBulletEv_02caf1f8)(param_1)
      ;
      return uVar1;
    }
  }
  return 0;
}

// ==== Aska::RigidBodyPrimitiveCube::Get(unsigned long, void*) const
// vaddr 0x234ee40 | ghidra 0x244ee40 | size 272 | symbol _ZNK4Aska22RigidBodyPrimitiveCube3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska22RigidBodyPrimitiveCube3GetEmPv(long param_1,ulong param_2,float *param_3)

{
  float fVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x28);
  if (((param_2 & 0xffff0000ffff) == 0x11) && (lVar2 != 0)) {
    *param_3 = *(float *)(lVar2 + 0x30) * 0.5;
    param_3[1] = *(float *)(*(long *)(param_1 + 0x28) + 0x34) * 0.5;
    param_3[2] = *(float *)(*(long *)(param_1 + 0x28) + 0x38) * 0.5;
    return 1;
  }
  if ((param_2 & 0xffff00000000) != 0) {
    return 0;
  }
  if (lVar2 == 0) {
    return 0;
  }
  switch((uint)param_2 & 0xffff) {
  case 2:
    *param_3 = *(float *)(lVar2 + 4);
    break;
  case 3:
    *param_3 = *(float *)(lVar2 + 8);
    break;
  case 4:
    *param_3 = *(float *)(lVar2 + 0xc);
    break;
  case 5:
    *param_3 = *(float *)(lVar2 + 0x10);
    break;
  case 6:
    *param_3 = *(float *)(lVar2 + 0x14);
    break;
  case 7:
    *param_3 = *(float *)(lVar2 + 0x18);
    param_3[1] = *(float *)(*(long *)(param_1 + 0x28) + 0x1c);
    fVar1 = *(float *)(*(long *)(param_1 + 0x28) + 0x20);
    goto code_r0x0244ef48;
  case 8:
    *param_3 = *(float *)(lVar2 + 0x24);
    param_3[1] = *(float *)(*(long *)(param_1 + 0x28) + 0x28);
    fVar1 = *(float *)(*(long *)(param_1 + 0x28) + 0x2c);
code_r0x0244ef48:
    param_3[2] = fVar1;
    break;
  default:
    return 0;
  }
  return 1;
}

// ==== Aska::RigidBodyPrimitiveCapsule::CreateBullet()
// vaddr 0x234ef50 | ghidra 0x244ef50 | size 140 | symbol _ZN4Aska25RigidBodyPrimitiveCapsule12CreateBulletEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska25RigidBodyPrimitiveCapsule12CreateBulletEv(long param_1)

{
  undefined8 uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  if (*(long *)(param_1 + 0x28) != 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(0x350,0x10,1);
    *(long *)(param_1 + 0x30) = lVar2;
    if (lVar2 != 0) {
      lVar3 = *(long *)(param_1 + 0x28);
      lVar4 = lVar2 + _UNK_029e3c40;
      *(long *)(param_1 + 0x40) = lVar2 + _UNK_029e3c48;
      *(long *)(param_1 + 0x38) = lVar4;
      if (*(char *)(lVar3 + 0x30) == '\x02') {
        btCapsuleShapeZ::btCapsuleShapeZ(float, float)(*(undefined4 *)(lVar3 + 0x34),*(undefined4 *)(lVar3 + 0x38),lVar4);
      }
      else if (*(char *)(lVar3 + 0x30) == '\0') {
        btCapsuleShapeX::btCapsuleShapeX(float, float)(lVar4);
      }
      else {
        btCapsuleShape::btCapsuleShape(float, float)(lVar4);
      }
      uVar1 = (*(code *)PTR__ZN4Aska22RigidBodyPrimitiveBase17LocalCreateBulletEv_02caf1f8)(param_1)
      ;
      return uVar1;
    }
  }
  return 0;
}

// ==== Aska::RigidBodyPrimitiveCapsule::Get(unsigned long, void*) const
// vaddr 0x234efdc | ghidra 0x244efdc | size 264 | symbol _ZNK4Aska25RigidBodyPrimitiveCapsule3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZNK4Aska25RigidBodyPrimitiveCapsule3GetEmPv(long param_1,undefined8 param_2,uint *param_3)

{
  short sVar1;
  uint uVar2;
  long lVar3;
  
  sVar1 = (short)param_2;
  if ((short)((ulong)param_2 >> 0x20) != 0) {
    return 0;
  }
  lVar3 = *(long *)(param_1 + 0x28);
  if (lVar3 == 0) {
    return 0;
  }
  if (sVar1 == 0x13) {
    *param_3 = *(uint *)(lVar3 + 0x38);
    return 1;
  }
  if (sVar1 == 0x12) {
    *param_3 = *(uint *)(lVar3 + 0x34);
    return 1;
  }
  if (sVar1 == 0x11) {
    *param_3 = (uint)*(byte *)(lVar3 + 0x30);
    return 1;
  }
  switch(sVar1) {
  case 2:
    *param_3 = *(uint *)(lVar3 + 4);
    break;
  case 3:
    *param_3 = *(uint *)(lVar3 + 8);
    break;
  case 4:
    *param_3 = *(uint *)(lVar3 + 0xc);
    break;
  case 5:
    *param_3 = *(uint *)(lVar3 + 0x10);
    break;
  case 6:
    *param_3 = *(uint *)(lVar3 + 0x14);
    break;
  case 7:
    *param_3 = *(uint *)(lVar3 + 0x18);
    param_3[1] = *(uint *)(*(long *)(param_1 + 0x28) + 0x1c);
    uVar2 = *(uint *)(*(long *)(param_1 + 0x28) + 0x20);
    goto code_r0x0244f0d8;
  case 8:
    *param_3 = *(uint *)(lVar3 + 0x24);
    param_3[1] = *(uint *)(*(long *)(param_1 + 0x28) + 0x28);
    uVar2 = *(uint *)(*(long *)(param_1 + 0x28) + 0x2c);
code_r0x0244f0d8:
    param_3[2] = uVar2;
    break;
  default:
    return 0;
  }
  return 1;
}

// ==== Aska::RigidBodyPrimitiveCylinder::CreateBullet()
// vaddr 0x234f0e4 | ghidra 0x244f0e4 | size 228 | symbol _ZN4Aska26RigidBodyPrimitiveCylinder12CreateBulletEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint _ZN4Aska26RigidBodyPrimitiveCylinder12CreateBulletEv(long param_1)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  undefined4 uStack_14;
  
  if (*(long *)(param_1 + 0x28) == 0) {
    uVar1 = 0;
  }
  else {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(0x350,0x10,1);
    *(long *)(param_1 + 0x30) = lVar2;
    uVar1 = 0;
    if (lVar2 != 0) {
      lVar3 = *(long *)(param_1 + 0x28);
      lVar4 = lVar2 + _UNK_029e3c40;
      *(long *)(param_1 + 0x40) = lVar2 + _UNK_029e3c48;
      *(long *)(param_1 + 0x38) = lVar4;
      fStack_20 = *(float *)(lVar3 + 0x34);
      fStack_18 = *(float *)(lVar3 + 0x38);
      fStack_1c = fStack_20;
      if (*(char *)(lVar3 + 0x30) == '\x02') {
        fStack_18 = fStack_18 * 0.5;
        uStack_14 = 0;
        btCylinderShapeZ::btCylinderShapeZ(btVector3 const&)(lVar4,&fStack_20);
      }
      else if (*(char *)(lVar3 + 0x30) == '\0') {
        uStack_14 = 0;
        fStack_20 = fStack_18 * 0.5;
        fStack_18 = fStack_1c;
        btCylinderShapeX::btCylinderShapeX(btVector3 const&)(lVar4,&fStack_20);
      }
      else {
        fStack_1c = fStack_18 * 0.5;
        uStack_14 = 0;
        fStack_18 = fStack_20;
        btCylinderShape::btCylinderShape(btVector3 const&)(lVar4,&fStack_20);
      }
      uVar1 = Aska::RigidBodyPrimitiveBase::LocalCreateBullet()(param_1);
    }
  }
  return uVar1 & 1;
}

// ==== Aska::RigidBodyPrimitiveCylinder::Get(unsigned long, void*) const
// vaddr 0x234f1c8 | ghidra 0x244f1c8 | size 264 | symbol _ZNK4Aska26RigidBodyPrimitiveCylinder3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZNK4Aska26RigidBodyPrimitiveCylinder3GetEmPv(long param_1,undefined8 param_2,uint *param_3)

{
  short sVar1;
  uint uVar2;
  long lVar3;
  
  sVar1 = (short)param_2;
  if ((short)((ulong)param_2 >> 0x20) != 0) {
    return 0;
  }
  lVar3 = *(long *)(param_1 + 0x28);
  if (lVar3 == 0) {
    return 0;
  }
  if (sVar1 == 0x13) {
    *param_3 = *(uint *)(lVar3 + 0x38);
    return 1;
  }
  if (sVar1 == 0x12) {
    *param_3 = *(uint *)(lVar3 + 0x34);
    return 1;
  }
  if (sVar1 == 0x11) {
    *param_3 = (uint)*(byte *)(lVar3 + 0x30);
    return 1;
  }
  switch(sVar1) {
  case 2:
    *param_3 = *(uint *)(lVar3 + 4);
    break;
  case 3:
    *param_3 = *(uint *)(lVar3 + 8);
    break;
  case 4:
    *param_3 = *(uint *)(lVar3 + 0xc);
    break;
  case 5:
    *param_3 = *(uint *)(lVar3 + 0x10);
    break;
  case 6:
    *param_3 = *(uint *)(lVar3 + 0x14);
    break;
  case 7:
    *param_3 = *(uint *)(lVar3 + 0x18);
    param_3[1] = *(uint *)(*(long *)(param_1 + 0x28) + 0x1c);
    uVar2 = *(uint *)(*(long *)(param_1 + 0x28) + 0x20);
    goto code_r0x0244f2c4;
  case 8:
    *param_3 = *(uint *)(lVar3 + 0x24);
    param_3[1] = *(uint *)(*(long *)(param_1 + 0x28) + 0x28);
    uVar2 = *(uint *)(*(long *)(param_1 + 0x28) + 0x2c);
code_r0x0244f2c4:
    param_3[2] = uVar2;
    break;
  default:
    return 0;
  }
  return 1;
}

// ==== Aska::RigidBodyPrimitiveCone::CreateBullet()
// vaddr 0x234f2d0 | ghidra 0x244f2d0 | size 140 | symbol _ZN4Aska22RigidBodyPrimitiveCone12CreateBulletEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska22RigidBodyPrimitiveCone12CreateBulletEv(long param_1)

{
  undefined8 uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  if (*(long *)(param_1 + 0x28) != 0) {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(0x360,0x10,1);
    *(long *)(param_1 + 0x30) = lVar2;
    if (lVar2 != 0) {
      lVar3 = *(long *)(param_1 + 0x28);
      lVar4 = lVar2 + _UNK_029e3c50;
      *(long *)(param_1 + 0x40) = lVar2 + _UNK_029e3c58;
      *(long *)(param_1 + 0x38) = lVar4;
      if (*(char *)(lVar3 + 0x30) == '\x02') {
        btConeShapeZ::btConeShapeZ(float, float)(*(undefined4 *)(lVar3 + 0x34),*(undefined4 *)(lVar3 + 0x38),lVar4);
      }
      else if (*(char *)(lVar3 + 0x30) == '\0') {
        btConeShapeX::btConeShapeX(float, float)(lVar4);
      }
      else {
        btConeShape::btConeShape(float, float)(lVar4);
      }
      uVar1 = (*(code *)PTR__ZN4Aska22RigidBodyPrimitiveBase17LocalCreateBulletEv_02caf1f8)(param_1)
      ;
      return uVar1;
    }
  }
  return 0;
}

// ==== Aska::RigidBodyPrimitiveCone::Get(unsigned long, void*) const
// vaddr 0x234f35c | ghidra 0x244f35c | size 264 | symbol _ZNK4Aska22RigidBodyPrimitiveCone3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska22RigidBodyPrimitiveCone3GetEmPv(long param_1,undefined8 param_2,uint *param_3)

{
  short sVar1;
  uint uVar2;
  long lVar3;
  
  sVar1 = (short)param_2;
  if ((short)((ulong)param_2 >> 0x20) != 0) {
    return 0;
  }
  lVar3 = *(long *)(param_1 + 0x28);
  if (lVar3 == 0) {
    return 0;
  }
  if (sVar1 == 0x13) {
    *param_3 = *(uint *)(lVar3 + 0x38);
    return 1;
  }
  if (sVar1 == 0x12) {
    *param_3 = *(uint *)(lVar3 + 0x34);
    return 1;
  }
  if (sVar1 == 0x11) {
    *param_3 = (uint)*(byte *)(lVar3 + 0x30);
    return 1;
  }
  switch(sVar1) {
  case 2:
    *param_3 = *(uint *)(lVar3 + 4);
    break;
  case 3:
    *param_3 = *(uint *)(lVar3 + 8);
    break;
  case 4:
    *param_3 = *(uint *)(lVar3 + 0xc);
    break;
  case 5:
    *param_3 = *(uint *)(lVar3 + 0x10);
    break;
  case 6:
    *param_3 = *(uint *)(lVar3 + 0x14);
    break;
  case 7:
    *param_3 = *(uint *)(lVar3 + 0x18);
    param_3[1] = *(uint *)(*(long *)(param_1 + 0x28) + 0x1c);
    uVar2 = *(uint *)(*(long *)(param_1 + 0x28) + 0x20);
    goto code_r0x0244f458;
  case 8:
    *param_3 = *(uint *)(lVar3 + 0x24);
    param_3[1] = *(uint *)(*(long *)(param_1 + 0x28) + 0x28);
    uVar2 = *(uint *)(*(long *)(param_1 + 0x28) + 0x2c);
code_r0x0244f458:
    param_3[2] = uVar2;
    break;
  default:
    return 0;
  }
  return 1;
}

// ==== Aska::RigidBodyPrimitivePlane::CreateBullet()
// vaddr 0x234f464 | ghidra 0x244f464 | size 124 | symbol _ZN4Aska23RigidBodyPrimitivePlane12CreateBulletEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint _ZN4Aska23RigidBodyPrimitivePlane12CreateBulletEv(long param_1)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  if (*(long *)(param_1 + 0x28) == 0) {
    uVar1 = 0;
  }
  else {
    lVar2 = operator new[](unsigned long, unsigned long, bool)(0x368,0x10,1);
    *(long *)(param_1 + 0x30) = lVar2;
    uVar1 = 0;
    if (lVar2 != 0) {
      lVar3 = lVar2 + _UNK_029e3c60;
      *(long *)(param_1 + 0x40) = lVar2 + _UNK_029e3c68;
      *(long *)(param_1 + 0x38) = lVar3;
      uStack_20 = 0x3f80000000000000;
      uStack_18 = 0;
      btStaticPlaneShape::btStaticPlaneShape(btVector3 const&, float)(*(undefined4 *)(*(long *)(param_1 + 0x28) + 0x30),lVar3,&uStack_20);
      uVar1 = Aska::RigidBodyPrimitiveBase::LocalCreateBullet()(param_1);
    }
  }
  return uVar1 & 1;
}

// ==== Aska::RigidBodyPrimitivePlane::Get(unsigned long, void*) const
// vaddr 0x234f4e0 | ghidra 0x244f4e0 | size 212 | symbol _ZNK4Aska23RigidBodyPrimitivePlane3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZNK4Aska23RigidBodyPrimitivePlane3GetEmPv(long param_1,ulong param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x28);
  if (((param_2 & 0xffff0000ffff) == 0x11) && (lVar2 != 0)) {
    uVar1 = *(undefined4 *)(lVar2 + 0x30);
    goto code_r0x0244f4f8;
  }
  if ((param_2 & 0xffff00000000) != 0) {
    return 0;
  }
  if (lVar2 == 0) {
    return 0;
  }
  switch((uint)param_2 & 0xffff) {
  case 2:
    uVar1 = *(undefined4 *)(lVar2 + 4);
    break;
  case 3:
    uVar1 = *(undefined4 *)(lVar2 + 8);
    break;
  case 4:
    uVar1 = *(undefined4 *)(lVar2 + 0xc);
    break;
  case 5:
    uVar1 = *(undefined4 *)(lVar2 + 0x10);
    break;
  case 6:
    uVar1 = *(undefined4 *)(lVar2 + 0x14);
    break;
  case 7:
    *param_3 = *(undefined4 *)(lVar2 + 0x18);
    param_3[1] = *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x1c);
    uVar1 = *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x20);
    goto code_r0x0244f5ac;
  case 8:
    *param_3 = *(undefined4 *)(lVar2 + 0x24);
    param_3[1] = *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x28);
    uVar1 = *(undefined4 *)(*(long *)(param_1 + 0x28) + 0x2c);
code_r0x0244f5ac:
    param_3[2] = uVar1;
    return 1;
  default:
    return 0;
  }
code_r0x0244f4f8:
  *param_3 = uVar1;
  return 1;
}

// ==== Aska::RigidBodyPrimitiveSoft::CreateBullet()
// vaddr 0x234f5b4 | ghidra 0x244f5b4 | size 8 | symbol _ZN4Aska22RigidBodyPrimitiveSoft12CreateBulletEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska22RigidBodyPrimitiveSoft12CreateBulletEv(void)

{
  return 0;
}

// ==== Aska::RigidBodyPrimitiveBase::GetClassID(int) const
// vaddr 0x234f5bc | ghidra 0x244f5bc | size 64 | symbol _ZNK4Aska22RigidBodyPrimitiveBase10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska22RigidBodyPrimitiveBase10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 != 0) {
    uVar2 = 0xf000f001;
    if (param_2 != 2) {
      uVar2 = 0xf000;
    }
    uVar1 = 0xf001f032;
    if (param_2 != 1) {
      uVar1 = uVar2;
    }
    return uVar1;
  }
  return 0xf001f032f179;
}

// ==== Aska::RigidBodyPrimitiveBase::CreateBullet()
// vaddr 0x234f5fc | ghidra 0x244f5fc | size 8 | symbol _ZN4Aska22RigidBodyPrimitiveBase12CreateBulletEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska22RigidBodyPrimitiveBase12CreateBulletEv(void)

{
  return 0;
}

// ==== Aska::RigidBodyPrimitiveBase::IsSoftBody()
// vaddr 0x234f604 | ghidra 0x244f604 | size 8 | symbol _ZN4Aska22RigidBodyPrimitiveBase10IsSoftBodyEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska22RigidBodyPrimitiveBase10IsSoftBodyEv(void)

{
  return 0;
}

// ==== Aska::RigidBodyPrimitiveSphere::~RigidBodyPrimitiveSphere()
// vaddr 0x234f60c | ghidra 0x244f60c | size 180 | symbol _ZN4Aska24RigidBodyPrimitiveSphereD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska24RigidBodyPrimitiveSphereD0Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska22RigidBodyPrimitiveBaseE_02cc25b8 + 0x10);
  plVar1 = (long *)param_1[6];
  if (((plVar1 != (long *)0x0) && (param_1[7] != 0)) && (param_1[8] != 0)) {
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x90))(*(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28
                                 ),plVar1);
    (**(code **)(*plVar1 + 8))(plVar1);
    (*(code *)**(undefined8 **)param_1[7])();
    (*(code *)**(undefined8 **)param_1[8])();
    if (param_1[6] != 0) {
      operator delete[](void*)();
    }
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[6] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RigidBodyPrimitiveSphere::GetClassID(int) const
// vaddr 0x234f6c0 | ghidra 0x244f6c0 | size 88 | symbol _ZNK4Aska24RigidBodyPrimitiveSphere10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska24RigidBodyPrimitiveSphere10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf032f179f17a;
  }
  if (param_2 == 1) {
    return 0xf001f032f179;
  }
  uVar2 = 0xf000f001;
  if (param_2 != 3) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf001f032;
  if (param_2 != 2) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::RigidBodyPrimitiveCube::~RigidBodyPrimitiveCube()
// vaddr 0x234f718 | ghidra 0x244f718 | size 180 | symbol _ZN4Aska22RigidBodyPrimitiveCubeD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22RigidBodyPrimitiveCubeD0Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska22RigidBodyPrimitiveBaseE_02cc25b8 + 0x10);
  plVar1 = (long *)param_1[6];
  if (((plVar1 != (long *)0x0) && (param_1[7] != 0)) && (param_1[8] != 0)) {
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x90))(*(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28
                                 ),plVar1);
    (**(code **)(*plVar1 + 8))(plVar1);
    (*(code *)**(undefined8 **)param_1[7])();
    (*(code *)**(undefined8 **)param_1[8])();
    if (param_1[6] != 0) {
      operator delete[](void*)();
    }
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[6] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RigidBodyPrimitiveCube::GetClassID(int) const
// vaddr 0x234f7cc | ghidra 0x244f7cc | size 88 | symbol _ZNK4Aska22RigidBodyPrimitiveCube10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska22RigidBodyPrimitiveCube10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf032f179f17b;
  }
  if (param_2 == 1) {
    return 0xf001f032f179;
  }
  uVar2 = 0xf000f001;
  if (param_2 != 3) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf001f032;
  if (param_2 != 2) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::RigidBodyPrimitiveCapsule::~RigidBodyPrimitiveCapsule()
// vaddr 0x234f824 | ghidra 0x244f824 | size 180 | symbol _ZN4Aska25RigidBodyPrimitiveCapsuleD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska25RigidBodyPrimitiveCapsuleD0Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska22RigidBodyPrimitiveBaseE_02cc25b8 + 0x10);
  plVar1 = (long *)param_1[6];
  if (((plVar1 != (long *)0x0) && (param_1[7] != 0)) && (param_1[8] != 0)) {
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x90))(*(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28
                                 ),plVar1);
    (**(code **)(*plVar1 + 8))(plVar1);
    (*(code *)**(undefined8 **)param_1[7])();
    (*(code *)**(undefined8 **)param_1[8])();
    if (param_1[6] != 0) {
      operator delete[](void*)();
    }
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[6] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RigidBodyPrimitiveCapsule::GetClassID(int) const
// vaddr 0x234f8d8 | ghidra 0x244f8d8 | size 88 | symbol _ZNK4Aska25RigidBodyPrimitiveCapsule10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska25RigidBodyPrimitiveCapsule10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf032f179f17c;
  }
  if (param_2 == 1) {
    return 0xf001f032f179;
  }
  uVar2 = 0xf000f001;
  if (param_2 != 3) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf001f032;
  if (param_2 != 2) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::RigidBodyPrimitiveCylinder::~RigidBodyPrimitiveCylinder()
// vaddr 0x234f930 | ghidra 0x244f930 | size 180 | symbol _ZN4Aska26RigidBodyPrimitiveCylinderD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska26RigidBodyPrimitiveCylinderD0Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska22RigidBodyPrimitiveBaseE_02cc25b8 + 0x10);
  plVar1 = (long *)param_1[6];
  if (((plVar1 != (long *)0x0) && (param_1[7] != 0)) && (param_1[8] != 0)) {
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x90))(*(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28
                                 ),plVar1);
    (**(code **)(*plVar1 + 8))(plVar1);
    (*(code *)**(undefined8 **)param_1[7])();
    (*(code *)**(undefined8 **)param_1[8])();
    if (param_1[6] != 0) {
      operator delete[](void*)();
    }
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[6] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RigidBodyPrimitiveCylinder::GetClassID(int) const
// vaddr 0x234f9e4 | ghidra 0x244f9e4 | size 88 | symbol _ZNK4Aska26RigidBodyPrimitiveCylinder10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska26RigidBodyPrimitiveCylinder10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf032f179f17d;
  }
  if (param_2 == 1) {
    return 0xf001f032f179;
  }
  uVar2 = 0xf000f001;
  if (param_2 != 3) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf001f032;
  if (param_2 != 2) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::RigidBodyPrimitiveCone::~RigidBodyPrimitiveCone()
// vaddr 0x234fa3c | ghidra 0x244fa3c | size 180 | symbol _ZN4Aska22RigidBodyPrimitiveConeD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22RigidBodyPrimitiveConeD0Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska22RigidBodyPrimitiveBaseE_02cc25b8 + 0x10);
  plVar1 = (long *)param_1[6];
  if (((plVar1 != (long *)0x0) && (param_1[7] != 0)) && (param_1[8] != 0)) {
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x90))(*(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28
                                 ),plVar1);
    (**(code **)(*plVar1 + 8))(plVar1);
    (*(code *)**(undefined8 **)param_1[7])();
    (*(code *)**(undefined8 **)param_1[8])();
    if (param_1[6] != 0) {
      operator delete[](void*)();
    }
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[6] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RigidBodyPrimitiveCone::GetClassID(int) const
// vaddr 0x234faf0 | ghidra 0x244faf0 | size 88 | symbol _ZNK4Aska22RigidBodyPrimitiveCone10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska22RigidBodyPrimitiveCone10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf032f179f17e;
  }
  if (param_2 == 1) {
    return 0xf001f032f179;
  }
  uVar2 = 0xf000f001;
  if (param_2 != 3) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf001f032;
  if (param_2 != 2) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::RigidBodyPrimitiveBase::~RigidBodyPrimitiveBase()
// vaddr 0x234fb48 | ghidra 0x244fb48 | size 172 | symbol _ZN4Aska22RigidBodyPrimitiveBaseD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22RigidBodyPrimitiveBaseD1Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska22RigidBodyPrimitiveBaseE_02cc25b8 + 0x10);
  plVar1 = (long *)param_1[6];
  if (((plVar1 != (long *)0x0) && (param_1[7] != 0)) && (param_1[8] != 0)) {
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x90))(*(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28
                                 ),plVar1);
    (**(code **)(*plVar1 + 8))(plVar1);
    (*(code *)**(undefined8 **)param_1[7])();
    (*(code *)**(undefined8 **)param_1[8])();
    if (param_1[6] != 0) {
      operator delete[](void*)();
    }
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[6] = 0;
  }
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1);
  return;
}

// ==== Aska::RigidBodyPrimitivePlane::~RigidBodyPrimitivePlane()
// vaddr 0x234fbf4 | ghidra 0x244fbf4 | size 180 | symbol _ZN4Aska23RigidBodyPrimitivePlaneD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska23RigidBodyPrimitivePlaneD0Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska22RigidBodyPrimitiveBaseE_02cc25b8 + 0x10);
  plVar1 = (long *)param_1[6];
  if (((plVar1 != (long *)0x0) && (param_1[7] != 0)) && (param_1[8] != 0)) {
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x90))(*(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28
                                 ),plVar1);
    (**(code **)(*plVar1 + 8))(plVar1);
    (*(code *)**(undefined8 **)param_1[7])();
    (*(code *)**(undefined8 **)param_1[8])();
    if (param_1[6] != 0) {
      operator delete[](void*)();
    }
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[6] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RigidBodyPrimitivePlane::GetClassID(int) const
// vaddr 0x234fca8 | ghidra 0x244fca8 | size 88 | symbol _ZNK4Aska23RigidBodyPrimitivePlane10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska23RigidBodyPrimitivePlane10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf032f179f17f;
  }
  if (param_2 == 1) {
    return 0xf001f032f179;
  }
  uVar2 = 0xf000f001;
  if (param_2 != 3) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf001f032;
  if (param_2 != 2) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::RigidBodyPrimitiveSoft::~RigidBodyPrimitiveSoft()
// vaddr 0x234fd00 | ghidra 0x244fd00 | size 180 | symbol _ZN4Aska22RigidBodyPrimitiveSoftD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska22RigidBodyPrimitiveSoftD0Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska22RigidBodyPrimitiveBaseE_02cc25b8 + 0x10);
  plVar1 = (long *)param_1[6];
  if (((plVar1 != (long *)0x0) && (param_1[7] != 0)) && (param_1[8] != 0)) {
    (**(code **)(**(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28) +
                0x90))(*(long **)(*(long *)PTR__ZN4Aska6Global19m_pRigidBodyManagerE_02cbda48 + 0x28
                                 ),plVar1);
    (**(code **)(*plVar1 + 8))(plVar1);
    (*(code *)**(undefined8 **)param_1[7])();
    (*(code *)**(undefined8 **)param_1[8])();
    if (param_1[6] != 0) {
      operator delete[](void*)();
    }
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[6] = 0;
  }
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::RigidBodyPrimitiveSoft::GetClassID(int) const
// vaddr 0x234fdb4 | ghidra 0x244fdb4 | size 88 | symbol _ZNK4Aska22RigidBodyPrimitiveSoft10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska22RigidBodyPrimitiveSoft10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf032f179f180;
  }
  if (param_2 == 1) {
    return 0xf001f032f179;
  }
  uVar2 = 0xf000f001;
  if (param_2 != 3) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf001f032;
  if (param_2 != 2) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::RigidBodyPrimitiveSoft::IsSoftBody()
// vaddr 0x234fe0c | ghidra 0x244fe0c | size 8 | symbol _ZN4Aska22RigidBodyPrimitiveSoft10IsSoftBodyEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska22RigidBodyPrimitiveSoft10IsSoftBodyEv(void)

{
  return 1;
}
