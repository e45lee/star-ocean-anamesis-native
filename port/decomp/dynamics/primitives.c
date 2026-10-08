// port/decomp/dynamics/primitives.c: Ghidra decompiles for the dynamics subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 14:42 UTC: tools/decomp.sh '--into' 'dynamics/primitives' ' Aska::(DynamicsPrimitive\w*|DynamicsSphere|DynamicsCube|DynamicsCapsule|DynamicsPlane|DynamicsSquare|DYNAMICS_\w*)::[~\w<>]+\('

// ==== Aska::DYNAMICS_SPHERE::TestIntersectionSphere(Aska::Vector const*, float, Aska::Vector*)
// vaddr 0x20761e0 | ghidra 0x21761e0 | size 276 | symbol _ZN4Aska15DYNAMICS_SPHERE22TestIntersectionSphereEPKNS_6VectorEfPS1_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska15DYNAMICS_SPHERE22TestIntersectionSphereEPKNS_6VectorEfPS1_
          (float param_1,long param_2,float *param_3,float *param_4)

{
  undefined8 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  fVar7 = *param_3 - *(float *)(param_2 + 0x30);
  fVar6 = param_3[1] - *(float *)(param_2 + 0x34);
  fVar5 = param_3[2] - *(float *)(param_2 + 0x38);
  fVar4 = fVar7 * fVar7 + fVar6 * fVar6 + fVar5 * fVar5;
  fVar3 = SQRT(fVar4);
  if (NAN(fVar3)) {
    fVar3 = (float)sqrtf(fVar4);
  }
  fVar3 = fVar3 - (*(float *)(param_2 + 0x20) + param_1);
  if (fVar3 <= 0.0) {
    fVar2 = SQRT(fVar4);
    if (NAN(fVar2)) {
      fVar2 = (float)sqrtf(fVar4);
    }
    if (_UNK_027e519c <= fVar2) {
      fVar2 = 1.0 / fVar2;
      fVar7 = fVar7 * fVar2;
      fVar6 = fVar6 * fVar2;
      fVar5 = fVar5 * fVar2;
    }
    uVar1 = 1;
    *param_4 = *param_3 - fVar3 * fVar7;
    param_4[1] = param_3[1] - fVar3 * fVar6;
    param_4[2] = param_3[2] - fVar3 * fVar5;
    param_4[3] = param_3[3];
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// ==== Aska::DynamicsPrimitiveElement::~DynamicsPrimitiveElement()
// vaddr 0x207666c | ghidra 0x217666c | size 76 | symbol _ZN4Aska24DynamicsPrimitiveElementD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska24DynamicsPrimitiveElementD2Ev(long *param_1)

{
  int iVar1;
  long *plVar2;
  
  plVar2 = (long *)param_1[7];
  *param_1 = (long)(PTR__ZTVN4Aska24DynamicsPrimitiveElementE_02cbbef0 + 0x10);
  if (plVar2 != (long *)0x0) {
    iVar1 = (int)plVar2[5] + -1;
    *(int *)(plVar2 + 5) = iVar1;
    if (iVar1 == 0) {
      (**(code **)(*plVar2 + 8))();
    }
    param_1[7] = 0;
  }
  (*(code *)PTR__ZN4Aska15DynamicsHandlerD2Ev_02cb53e0)(param_1);
  return;
}

// ==== Aska::DynamicsPrimitiveElement::~DynamicsPrimitiveElement()
// vaddr 0x20767d4 | ghidra 0x21767d4 | size 84 | symbol _ZN4Aska24DynamicsPrimitiveElementD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska24DynamicsPrimitiveElementD0Ev(long *param_1)

{
  int iVar1;
  long *plVar2;
  
  plVar2 = (long *)param_1[7];
  *param_1 = (long)(PTR__ZTVN4Aska24DynamicsPrimitiveElementE_02cbbef0 + 0x10);
  if (plVar2 != (long *)0x0) {
    iVar1 = (int)plVar2[5] + -1;
    *(int *)(plVar2 + 5) = iVar1;
    if (iVar1 == 0) {
      (**(code **)(*plVar2 + 8))();
    }
    param_1[7] = 0;
  }
  Aska::DynamicsHandler::~DynamicsHandler()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsPrimitiveElement::Run(int)
// vaddr 0x2076830 | ghidra 0x2176830 | size 24 | symbol _ZN4Aska24DynamicsPrimitiveElement3RunEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska24DynamicsPrimitiveElement3RunEi(long param_1)

{
  if (*(long **)(param_1 + 0x38) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x02176840. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + 0x38) + 0x38))();
    return;
  }
  return;
}

// ==== Aska::DynamicsPrimitive::Clone(Aska::IAnimatable const*)
// vaddr 0x209f600 | ghidra 0x219f600 | size 88 | symbol _ZN4Aska17DynamicsPrimitive5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska17DynamicsPrimitive5CloneEPKNS_11IAnimatableE(long param_1,long param_2)

{
  bool bVar1;
  ulong uVar2;
  
  uVar2 = Aska::IAnimatable::Clone(Aska::IAnimatable const*)();
  bVar1 = (uVar2 & 1) != 0;
  if (bVar1) {
    *(undefined8 *)(param_1 + 0x20) = *(undefined8 *)(param_2 + 0x20);
    **(undefined4 **)(param_1 + 0x50) = **(undefined4 **)(param_2 + 0x50);
    *(undefined4 *)(*(long *)(param_1 + 0x50) + 4) = *(undefined4 *)(*(long *)(param_2 + 0x50) + 4);
  }
  return bVar1;
}

// ==== Aska::DynamicsPrimitive::Get(unsigned long, void*) const
// vaddr 0x209f658 | ghidra 0x219f658 | size 76 | symbol _ZNK4Aska17DynamicsPrimitive3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska17DynamicsPrimitive3GetEmPv(long param_1,undefined8 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  if ((short)((ulong)param_2 >> 0x20) != 0) {
    return 0;
  }
  if ((short)param_2 == 0x13) {
    uVar1 = *(undefined4 *)(*(long *)(param_1 + 0x50) + 4);
  }
  else {
    if ((short)param_2 != 0x12) {
      return 0;
    }
    uVar1 = **(undefined4 **)(param_1 + 0x50);
  }
  *param_3 = uVar1;
  return 1;
}

// ==== Aska::DynamicsPrimitive::Set(unsigned long, void const*)
// vaddr 0x209f6a4 | ghidra 0x219f6a4 | size 76 | symbol _ZN4Aska17DynamicsPrimitive3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska17DynamicsPrimitive3SetEmPKv(long param_1,undefined8 param_2,undefined4 *param_3)

{
  if ((short)((ulong)param_2 >> 0x20) == 0) {
    if ((short)param_2 == 0x13) {
      *(undefined4 *)(*(long *)(param_1 + 0x50) + 4) = *param_3;
      return 0;
    }
    if ((short)param_2 == 0x12) {
      **(undefined4 **)(param_1 + 0x50) = *param_3;
      return 0;
    }
  }
  return 0;
}

// ==== Aska::DynamicsCube::Run()
// vaddr 0x209f6f0 | ghidra 0x219f6f0 | size 844 | symbol _ZN4Aska12DynamicsCube3RunEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12DynamicsCube3RunEv(long param_1)

{
  long lVar1;
  undefined8 *puVar2;
  byte bVar3;
  long *plVar4;
  undefined8 *puVar5;
  undefined8 uVar6;
  long lVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  
  plVar4 = *(long **)(param_1 + 0x20);
  if (plVar4 != (long *)0x0) {
    fVar10 = *(float *)(param_1 + 0x160);
    fVar9 = *(float *)(param_1 + 0x164);
    fVar8 = *(float *)(param_1 + 0x168);
    if ((*(byte *)(plVar4 + 0x25) & 1) != 0) {
      (**(code **)(*plVar4 + 0xa8))(plVar4);
    }
    puVar2 = (undefined8 *)(**(code **)(*plVar4 + 0x98))(plVar4);
    uVar6 = *puVar2;
    puVar5 = (undefined8 *)(param_1 + 0xd0);
    *(undefined8 *)(param_1 + 0xd8) = puVar2[1];
    *puVar5 = uVar6;
    uVar6 = puVar2[2];
    *(undefined8 *)(param_1 + 0xe8) = puVar2[3];
    *(undefined8 *)(param_1 + 0xe0) = uVar6;
    uVar6 = puVar2[4];
    *(undefined8 *)(param_1 + 0xf8) = puVar2[5];
    *(undefined8 *)(param_1 + 0xf0) = uVar6;
    uVar6 = puVar2[6];
    *(undefined8 *)(param_1 + 0x108) = puVar2[7];
    *(undefined8 *)(param_1 + 0x100) = uVar6;
    Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const(param_1 + 0x30,param_1 + 0x80,puVar5);
    *(float *)(param_1 + 0x160) = *(float *)(param_1 + 0x80);
    *(float *)(param_1 + 0x164) = *(float *)(param_1 + 0x84);
    *(float *)(param_1 + 0x168) = *(float *)(param_1 + 0x88);
    *(undefined4 *)(param_1 + 0x16c) = *(undefined4 *)(param_1 + 0x8c);
    *(float *)(param_1 + 0x150) = *(float *)(param_1 + 0x80) - fVar10;
    *(float *)(param_1 + 0x154) = *(float *)(param_1 + 0x84) - fVar9;
    *(float *)(param_1 + 0x158) = *(float *)(param_1 + 0x88) - fVar8;
    *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x8c);
    Aska::Vector::ApplyMatrixNoTransport(Aska::Vector*, Aska::Matrix const*) const(PTR__ZN4Aska17DynamicsPrimitive8m_vUnitXE_02cc2828,param_1 + 0xa0,puVar5);
    Aska::Vector::ApplyMatrixNoTransport(Aska::Vector*, Aska::Matrix const*) const(PTR__ZN4Aska17DynamicsPrimitive8m_vUnitYE_02cbf898,param_1 + 0xb0,puVar5);
    Aska::Vector::ApplyMatrixNoTransport(Aska::Vector*, Aska::Matrix const*) const(PTR__ZN4Aska17DynamicsPrimitive8m_vUnitZE_02cbcaa8,param_1 + 0xc0,puVar5);
    fVar9 = *(float *)(param_1 + 0xa0) * *(float *)(param_1 + 0xa0) +
            *(float *)(param_1 + 0xa4) * *(float *)(param_1 + 0xa4) +
            *(float *)(param_1 + 0xa8) * *(float *)(param_1 + 0xa8);
    fVar8 = SQRT(fVar9);
    if (NAN(fVar8)) {
      fVar8 = (float)sqrtf(fVar9);
    }
    fVar9 = _UNK_027e519c;
    if (_UNK_027e519c <= fVar8) {
      fVar8 = 1.0 / fVar8;
      *(float *)(param_1 + 0xa0) = fVar8 * *(float *)(param_1 + 0xa0);
      *(float *)(param_1 + 0xa4) = fVar8 * *(float *)(param_1 + 0xa4);
      *(float *)(param_1 + 0xa8) = fVar8 * *(float *)(param_1 + 0xa8);
    }
    fVar10 = *(float *)(param_1 + 0xb0) * *(float *)(param_1 + 0xb0) +
             *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0xb4) +
             *(float *)(param_1 + 0xb8) * *(float *)(param_1 + 0xb8);
    fVar8 = SQRT(fVar10);
    if (NAN(fVar8)) {
      fVar8 = (float)sqrtf(fVar10);
    }
    if (fVar9 <= fVar8) {
      fVar8 = 1.0 / fVar8;
      *(float *)(param_1 + 0xb0) = fVar8 * *(float *)(param_1 + 0xb0);
      *(float *)(param_1 + 0xb4) = fVar8 * *(float *)(param_1 + 0xb4);
      *(float *)(param_1 + 0xb8) = fVar8 * *(float *)(param_1 + 0xb8);
    }
    fVar10 = *(float *)(param_1 + 0xc0) * *(float *)(param_1 + 0xc0) +
             *(float *)(param_1 + 0xc4) * *(float *)(param_1 + 0xc4) +
             *(float *)(param_1 + 200) * *(float *)(param_1 + 200);
    fVar8 = SQRT(fVar10);
    if (NAN(fVar8)) {
      fVar8 = (float)sqrtf(fVar10);
    }
    if (fVar9 <= fVar8) {
      fVar8 = 1.0 / fVar8;
      *(float *)(param_1 + 0xc0) = fVar8 * *(float *)(param_1 + 0xc0);
      *(float *)(param_1 + 0xc4) = fVar8 * *(float *)(param_1 + 0xc4);
      *(float *)(param_1 + 200) = fVar8 * *(float *)(param_1 + 200);
    }
    lVar1 = _UNK_027dbb38;
    lVar7 = _UNK_027dbb30;
    bVar3 = *(byte *)(plVar4 + 0x25);
    if ((bVar3 >> 2 & 1) == 0) {
      if ((*(byte *)((long)plVar4 + 0x129) & 3) == 0) {
        fVar8 = *(float *)((long)plVar4 + 0x4c);
        fVar9 = *(float *)((long)plVar4 + 0x5c);
        fVar10 = *(float *)((long)plVar4 + 0x6c);
        plVar4[0x27] = CONCAT44((int)plVar4[0xe],*(float *)(plVar4 + 0xc));
        plVar4[0x26] = CONCAT44(*(float *)(plVar4 + 10),*(float *)(plVar4 + 8));
        plVar4[0x29] = CONCAT44(*(undefined4 *)((long)plVar4 + 0x74),*(float *)((long)plVar4 + 100))
        ;
        plVar4[0x28] = CONCAT44(*(float *)((long)plVar4 + 0x54),*(float *)((long)plVar4 + 0x44));
        *(float *)((long)plVar4 + 0x13c) =
             -(*(float *)(plVar4 + 8) * fVar8 + *(float *)(plVar4 + 10) * fVar9 +
              *(float *)(plVar4 + 0xc) * fVar10);
        *(float *)((long)plVar4 + 0x14c) =
             -(fVar8 * *(float *)((long)plVar4 + 0x44) + fVar9 * *(float *)((long)plVar4 + 0x54) +
              fVar10 * *(float *)((long)plVar4 + 100));
        plVar4[0x2b] = CONCAT44((int)plVar4[0xf],*(float *)(plVar4 + 0xd));
        plVar4[0x2a] = CONCAT44(*(float *)(plVar4 + 0xb),*(float *)(plVar4 + 9));
        plVar4[0x2d] = lVar1;
        plVar4[0x2c] = lVar7;
        *(float *)((long)plVar4 + 0x15c) =
             -(fVar8 * *(float *)(plVar4 + 9) + fVar9 * *(float *)(plVar4 + 0xb) +
              fVar10 * *(float *)(plVar4 + 0xd));
      }
      else {
        Aska::Matrix::InvertLowError(Aska::Matrix*) const(plVar4 + 8,plVar4 + 0x26);
        bVar3 = *(byte *)(plVar4 + 0x25);
      }
      *(byte *)(plVar4 + 0x25) = bVar3 | 4;
    }
    lVar7 = plVar4[0x26];
    *(long *)(param_1 + 0x118) = plVar4[0x27];
    *(long *)(param_1 + 0x110) = lVar7;
    lVar7 = plVar4[0x28];
    *(long *)(param_1 + 0x128) = plVar4[0x29];
    *(long *)(param_1 + 0x120) = lVar7;
    lVar7 = plVar4[0x2a];
    *(long *)(param_1 + 0x138) = plVar4[0x2b];
    *(long *)(param_1 + 0x130) = lVar7;
    lVar7 = plVar4[0x2c];
    *(long *)(param_1 + 0x148) = plVar4[0x2d];
    *(long *)(param_1 + 0x140) = lVar7;
  }
  return;
}

// ==== Aska::DynamicsCube::Reset()
// vaddr 0x209fa3c | ghidra 0x219fa3c | size 16 | symbol _ZN4Aska12DynamicsCube5ResetEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska12DynamicsCube5ResetEv(long param_1)

{
  undefined8 uVar1;
  
  uVar1 = _UNK_027dbb30;
  *(undefined8 *)(param_1 + 0x158) = _UNK_027dbb38;
  *(undefined8 *)(param_1 + 0x150) = uVar1;
  return;
}

// ==== Aska::DynamicsCube::CreateParticleObject()
// vaddr 0x209fa4c | ghidra 0x219fa4c | size 76 | symbol _ZN4Aska12DynamicsCube20CreateParticleObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12DynamicsCube20CreateParticleObjectEv(long param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(400,PTR__ZSt7nothrow_02cb9a80);
  if (plVar2 != (long *)0x0) {
    plVar2[0x26] = param_1;
    *(undefined2 *)(plVar2 + 0x27) = 1;
    puVar1 = PTR__ZTVN4Aska29ParticleDynamicsCubeDeflectorE_02cc19c0 + 0x10;
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
    *plVar2 = (long)puVar1;
  }
  return;
}

// ==== Aska::DynamicsCube::Clone(Aska::IAnimatable const*)
// vaddr 0x209fa98 | ghidra 0x219fa98 | size 120 | symbol _ZN4Aska12DynamicsCube5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska12DynamicsCube5CloneEPKNS_11IAnimatableE(long param_1,long param_2)

{
  bool bVar1;
  ulong uVar2;
  
  uVar2 = Aska::IAnimatable::Clone(Aska::IAnimatable const*)();
  bVar1 = (uVar2 & 1) != 0;
  if (bVar1) {
    *(undefined8 *)(param_1 + 0x20) = *(undefined8 *)(param_2 + 0x20);
    **(undefined4 **)(param_1 + 0x50) = **(undefined4 **)(param_2 + 0x50);
    *(undefined4 *)(*(long *)(param_1 + 0x50) + 4) = *(undefined4 *)(*(long *)(param_2 + 0x50) + 4);
    *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(param_2 + 0x90);
    *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(param_2 + 0x94);
    *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(param_2 + 0x98);
    *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_2 + 0x9c);
  }
  return bVar1;
}

// ==== Aska::DynamicsCube::CreateClone(Aska::IAnimatable const*)
// vaddr 0x209fb10 | ghidra 0x219fb10 | size 216 | symbol _ZN4Aska12DynamicsCube11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska12DynamicsCube11CreateCloneEPKNS_11IAnimatableE(undefined8 param_1,long param_2)

{
  long lVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  
  plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x170,PTR__ZSt7nothrow_02cb9a80);
  if (plVar2 != (long *)0x0) {
    plVar2[2] = 0;
    *(undefined4 *)(plVar2 + 5) = 0;
    plVar2[4] = 0;
    plVar2[8] = 0;
    *(undefined1 *)(plVar2 + 9) = 0;
    *(undefined1 *)(plVar2 + 3) = 1;
    lVar1 = _UNK_027dbb38;
    lVar4 = _UNK_027dbb30;
    *plVar2 = (long)(PTR__ZTVN4Aska12DynamicsCubeE_02cb9c70 + 0x10);
    plVar2[1] = 0;
    plVar2[7] = lVar1;
    plVar2[6] = lVar4;
    plVar2[0xc] = 0;
    *(undefined4 *)(plVar2 + 0xd) = 0;
    plVar2[0xe] = 0;
    plVar2[10] = (long)(plVar2 + 0xc);
    uVar3 = Aska::IAnimatable::Clone(Aska::IAnimatable const*)(plVar2,param_2);
    if ((uVar3 & 1) == 0) {
      (**(code **)(*plVar2 + 8))(plVar2);
      plVar2 = (long *)0x0;
    }
    else {
      plVar2[4] = *(long *)(param_2 + 0x20);
      *(undefined4 *)plVar2[10] = **(undefined4 **)(param_2 + 0x50);
      *(undefined4 *)(plVar2[10] + 4) = *(undefined4 *)(*(long *)(param_2 + 0x50) + 4);
      lVar4 = *(long *)(param_2 + 0x90);
      plVar2[0x13] = *(long *)(param_2 + 0x98);
      plVar2[0x12] = lVar4;
    }
  }
  return plVar2;
}

// ==== Aska::DynamicsCube::Get(unsigned long, void*) const
// vaddr 0x209fbe8 | ghidra 0x219fbe8 | size 116 | symbol _ZNK4Aska12DynamicsCube3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska12DynamicsCube3GetEmPv(long param_1,ulong param_2,undefined4 *param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if ((param_2 & 0xffff00000000) == 0) {
    uVar1 = (uint)param_2 & 0xffff;
    if (uVar1 == 0x13) {
      puVar2 = (undefined4 *)(*(long *)(param_1 + 0x50) + 4);
      goto code_r0x0219fc4c;
    }
    if (uVar1 == 0x12) {
      puVar2 = *(undefined4 **)(param_1 + 0x50);
      goto code_r0x0219fc4c;
    }
  }
  if ((param_2 & 0xffff0000ffff) != 0x14) {
    return 0;
  }
  *param_3 = *(undefined4 *)(param_1 + 0x90);
  param_3[1] = *(undefined4 *)(param_1 + 0x94);
  puVar2 = (undefined4 *)(param_1 + 0x9c);
  param_3[2] = *(undefined4 *)(param_1 + 0x98);
  param_3 = param_3 + 3;
code_r0x0219fc4c:
  *param_3 = *puVar2;
  return 1;
}

// ==== Aska::DynamicsCube::Set(unsigned long, void const*)
// vaddr 0x209fc5c | ghidra 0x219fc5c | size 120 | symbol _ZN4Aska12DynamicsCube3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska12DynamicsCube3SetEmPKv(long param_1,ulong param_2,undefined4 *param_3)

{
  uint uVar1;
  
  if ((param_2 & 0xffff00000000) == 0) {
    uVar1 = (uint)param_2 & 0xffff;
    if (uVar1 == 0x13) {
      *(undefined4 *)(*(long *)(param_1 + 0x50) + 4) = *param_3;
    }
    else if (uVar1 == 0x12) {
      **(undefined4 **)(param_1 + 0x50) = *param_3;
    }
  }
  if ((param_2 & 0xffff0000ffff) == 0x14) {
    *(undefined4 *)(param_1 + 0x90) = *param_3;
    *(undefined4 *)(param_1 + 0x94) = param_3[1];
    *(undefined4 *)(param_1 + 0x98) = param_3[2];
    *(undefined4 *)(param_1 + 0x9c) = param_3[3];
    return 1;
  }
  return 0;
}

// ==== Aska::DynamicsSphere::Run()
// vaddr 0x209fcd4 | ghidra 0x219fcd4 | size 164 | symbol _ZN4Aska14DynamicsSphere3RunEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska14DynamicsSphere3RunEv(long param_1)

{
  undefined8 uVar1;
  long *plVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  plVar2 = *(long **)(param_1 + 0x20);
  if (plVar2 != (long *)0x0) {
    fVar5 = *(float *)(param_1 + 0xb0);
    fVar4 = *(float *)(param_1 + 0xb4);
    fVar3 = *(float *)(param_1 + 0xb8);
    if ((*(byte *)(plVar2 + 0x25) & 1) != 0) {
      (**(code **)(*plVar2 + 0xa8))(plVar2);
    }
    uVar1 = (**(code **)(*plVar2 + 0x98))(plVar2);
    Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const(param_1 + 0x30,param_1 + 0x90,uVar1);
    *(float *)(param_1 + 0xb0) = *(float *)(param_1 + 0x90);
    *(float *)(param_1 + 0xb4) = *(float *)(param_1 + 0x94);
    *(float *)(param_1 + 0xb8) = *(float *)(param_1 + 0x98);
    *(undefined4 *)(param_1 + 0xbc) = *(undefined4 *)(param_1 + 0x9c);
    *(float *)(param_1 + 0xa0) = *(float *)(param_1 + 0x90) - fVar5;
    *(float *)(param_1 + 0xa4) = *(float *)(param_1 + 0x94) - fVar4;
    *(float *)(param_1 + 0xa8) = *(float *)(param_1 + 0x98) - fVar3;
    *(undefined4 *)(param_1 + 0xac) = *(undefined4 *)(param_1 + 0x9c);
  }
  return;
}

// ==== Aska::DynamicsSphere::Reset()
// vaddr 0x209fd78 | ghidra 0x219fd78 | size 16 | symbol _ZN4Aska14DynamicsSphere5ResetEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska14DynamicsSphere5ResetEv(long param_1)

{
  undefined8 uVar1;
  
  uVar1 = _UNK_027dbb30;
  *(undefined8 *)(param_1 + 0xa8) = _UNK_027dbb38;
  *(undefined8 *)(param_1 + 0xa0) = uVar1;
  return;
}

// ==== Aska::DynamicsSphere::CreateParticleObject()
// vaddr 0x209fd88 | ghidra 0x219fd88 | size 76 | symbol _ZN4Aska14DynamicsSphere20CreateParticleObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska14DynamicsSphere20CreateParticleObjectEv(long param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x150,PTR__ZSt7nothrow_02cb9a80);
  if (plVar2 != (long *)0x0) {
    plVar2[0x26] = param_1;
    *(undefined2 *)(plVar2 + 0x27) = 1;
    puVar1 = PTR__ZTVN4Aska31ParticleDynamicsSphereDeflectorE_02cb8b90 + 0x10;
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
    *plVar2 = (long)puVar1;
  }
  return;
}

// ==== Aska::DynamicsSphere::Clone(Aska::IAnimatable const*)
// vaddr 0x209fdd4 | ghidra 0x219fdd4 | size 96 | symbol _ZN4Aska14DynamicsSphere5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska14DynamicsSphere5CloneEPKNS_11IAnimatableE(long param_1,long param_2)

{
  bool bVar1;
  ulong uVar2;
  
  uVar2 = Aska::IAnimatable::Clone(Aska::IAnimatable const*)();
  bVar1 = (uVar2 & 1) != 0;
  if (bVar1) {
    *(undefined8 *)(param_1 + 0x20) = *(undefined8 *)(param_2 + 0x20);
    **(undefined4 **)(param_1 + 0x50) = **(undefined4 **)(param_2 + 0x50);
    *(undefined4 *)(*(long *)(param_1 + 0x50) + 4) = *(undefined4 *)(*(long *)(param_2 + 0x50) + 4);
    *(undefined4 *)(param_1 + 0x80) = *(undefined4 *)(param_2 + 0x80);
  }
  return bVar1;
}

// ==== Aska::DynamicsSphere::CreateClone(Aska::IAnimatable const*)
// vaddr 0x209fe34 | ghidra 0x219fe34 | size 232 | symbol _ZN4Aska14DynamicsSphere11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska14DynamicsSphere11CreateCloneEPKNS_11IAnimatableE(undefined8 param_1,long param_2)

{
  long lVar1;
  undefined *puVar2;
  undefined *puVar3;
  long *plVar4;
  ulong uVar5;
  
  plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xc0,PTR__ZSt7nothrow_02cb9a80);
  if (plVar4 != (long *)0x0) {
    plVar4[2] = 0;
    *(undefined4 *)(plVar4 + 5) = 0;
    plVar4[4] = 0;
    plVar4[8] = 0;
    *(undefined1 *)(plVar4 + 9) = 0;
    *(undefined1 *)(plVar4 + 3) = 1;
    puVar3 = PTR__ZTVN4Aska14DynamicsSphereE_02cc30e8;
    puVar2 = PTR__ZTVN4Aska15DYNAMICS_SPHEREE_02cb7648;
    lVar1 = _UNK_027dbb30;
    plVar4[7] = _UNK_027dbb38;
    plVar4[6] = lVar1;
    plVar4[0xc] = (long)(puVar2 + 0x10);
    *plVar4 = (long)(puVar3 + 0x10);
    plVar4[1] = 0;
    plVar4[0xd] = 0;
    *(undefined4 *)(plVar4 + 0xe) = 0;
    plVar4[0xf] = 0;
    plVar4[10] = (long)(plVar4 + 0xd);
    uVar5 = Aska::IAnimatable::Clone(Aska::IAnimatable const*)(plVar4,param_2);
    if ((uVar5 & 1) == 0) {
      (**(code **)(*plVar4 + 8))(plVar4);
      plVar4 = (long *)0x0;
    }
    else {
      plVar4[4] = *(long *)(param_2 + 0x20);
      *(undefined4 *)plVar4[10] = **(undefined4 **)(param_2 + 0x50);
      *(undefined4 *)(plVar4[10] + 4) = *(undefined4 *)(*(long *)(param_2 + 0x50) + 4);
      *(undefined4 *)(plVar4 + 0x10) = *(undefined4 *)(param_2 + 0x80);
    }
  }
  return plVar4;
}

// ==== Aska::DynamicsSphere::Get(unsigned long, void*) const
// vaddr 0x209ff1c | ghidra 0x219ff1c | size 88 | symbol _ZNK4Aska14DynamicsSphere3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska14DynamicsSphere3GetEmPv(long param_1,ulong param_2,undefined4 *param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if ((param_2 & 0xffff00000000) == 0) {
    uVar1 = (uint)param_2 & 0xffff;
    if (uVar1 == 0x13) {
      puVar2 = (undefined4 *)(*(long *)(param_1 + 0x50) + 4);
      goto code_r0x0219ff64;
    }
    if (uVar1 == 0x12) {
      puVar2 = *(undefined4 **)(param_1 + 0x50);
      goto code_r0x0219ff64;
    }
  }
  if ((param_2 & 0xffff0000ffff) != 0x14) {
    return 0;
  }
  puVar2 = (undefined4 *)(param_1 + 0x80);
code_r0x0219ff64:
  *param_3 = *puVar2;
  return 1;
}

// ==== Aska::DynamicsSphere::Set(unsigned long, void const*)
// vaddr 0x209ff74 | ghidra 0x219ff74 | size 96 | symbol _ZN4Aska14DynamicsSphere3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska14DynamicsSphere3SetEmPKv(long param_1,ulong param_2,undefined4 *param_3)

{
  uint uVar1;
  
  if ((param_2 & 0xffff00000000) == 0) {
    uVar1 = (uint)param_2 & 0xffff;
    if (uVar1 == 0x13) {
      *(undefined4 *)(*(long *)(param_1 + 0x50) + 4) = *param_3;
    }
    else if (uVar1 == 0x12) {
      **(undefined4 **)(param_1 + 0x50) = *param_3;
    }
  }
  if ((param_2 & 0xffff0000ffff) == 0x14) {
    *(undefined4 *)(param_1 + 0x80) = *param_3;
    return 1;
  }
  return 0;
}

// ==== Aska::DynamicsCapsule::Run()
// vaddr 0x209ffd4 | ghidra 0x219ffd4 | size 716 | symbol _ZN4Aska15DynamicsCapsule3RunEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15DynamicsCapsule3RunEv(long param_1)

{
  long lVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  byte bVar5;
  long *plVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  float fVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  float fVar16;
  undefined8 uVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  
  plVar6 = *(long **)(param_1 + 0x20);
  if (plVar6 != (long *)0x0) {
    fVar21 = *(float *)(param_1 + 0xd0);
    fVar20 = *(float *)(param_1 + 0xd4);
    bVar5 = *(byte *)(plVar6 + 0x25);
    fVar19 = *(float *)(param_1 + 0xd8);
    if ((bVar5 & 1) != 0) {
      (**(code **)(*plVar6 + 0xa8))(plVar6);
      bVar5 = *(byte *)(plVar6 + 0x25);
    }
    lVar2 = _UNK_027dbb38;
    lVar1 = _UNK_027dbb30;
    if ((bVar5 >> 2 & 1) == 0) {
      if ((*(byte *)((long)plVar6 + 0x129) & 3) == 0) {
        fVar9 = *(float *)((long)plVar6 + 0x4c);
        fVar8 = *(float *)((long)plVar6 + 0x5c);
        fVar18 = *(float *)((long)plVar6 + 0x6c);
        plVar6[0x27] = CONCAT44((int)plVar6[0xe],*(float *)(plVar6 + 0xc));
        plVar6[0x26] = CONCAT44(*(float *)(plVar6 + 10),*(float *)(plVar6 + 8));
        plVar6[0x29] = CONCAT44(*(undefined4 *)((long)plVar6 + 0x74),*(float *)((long)plVar6 + 100))
        ;
        plVar6[0x28] = CONCAT44(*(float *)((long)plVar6 + 0x54),*(float *)((long)plVar6 + 0x44));
        *(float *)((long)plVar6 + 0x13c) =
             -(*(float *)(plVar6 + 8) * fVar9 + *(float *)(plVar6 + 10) * fVar8 +
              *(float *)(plVar6 + 0xc) * fVar18);
        *(float *)((long)plVar6 + 0x14c) =
             -(fVar9 * *(float *)((long)plVar6 + 0x44) + fVar8 * *(float *)((long)plVar6 + 0x54) +
              fVar18 * *(float *)((long)plVar6 + 100));
        plVar6[0x2b] = CONCAT44((int)plVar6[0xf],*(float *)(plVar6 + 0xd));
        plVar6[0x2a] = CONCAT44(*(float *)(plVar6 + 0xb),*(float *)(plVar6 + 9));
        plVar6[0x2d] = lVar2;
        plVar6[0x2c] = lVar1;
        *(float *)((long)plVar6 + 0x15c) =
             -(fVar9 * *(float *)(plVar6 + 9) + fVar8 * *(float *)(plVar6 + 0xb) +
              fVar18 * *(float *)(plVar6 + 0xd));
      }
      else {
        Aska::Matrix::InvertLowError(Aska::Matrix*) const(plVar6 + 8,plVar6 + 0x26);
        bVar5 = *(byte *)(plVar6 + 0x25);
      }
      *(byte *)(plVar6 + 0x25) = bVar5 | 4;
    }
    uVar3 = (**(code **)(*plVar6 + 0x98))(plVar6);
    Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const(param_1 + 0x30,param_1 + 0x80,uVar3);
    *(float *)(param_1 + 0xd0) = *(float *)(param_1 + 0x80);
    *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0x84);
    *(float *)(param_1 + 0xd8) = *(float *)(param_1 + 0x88);
    *(undefined4 *)(param_1 + 0xdc) = *(undefined4 *)(param_1 + 0x8c);
    *(float *)(param_1 + 0xc0) = *(float *)(param_1 + 0x80) - fVar21;
    *(float *)(param_1 + 0xc4) = *(float *)(param_1 + 0x84) - fVar20;
    *(float *)(param_1 + 200) = *(float *)(param_1 + 0x88) - fVar19;
    *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(param_1 + 0x8c);
    puVar4 = (undefined8 *)(**(code **)(*plVar6 + 0x98))(plVar6);
    uVar11 = puVar4[1];
    uVar3 = *puVar4;
    uVar14 = puVar4[3];
    uVar12 = puVar4[2];
    uVar17 = puVar4[5];
    uVar15 = puVar4[4];
    fVar20 = (float)uVar3;
    fVar21 = (float)uVar12;
    uStack_58 = puVar4[7];
    uStack_60 = puVar4[6];
    fVar9 = (float)uVar15;
    fVar19 = SQRT(fVar20 * fVar20 + fVar21 * fVar21 + fVar9 * fVar9);
    uStack_90 = uVar3;
    uStack_88 = uVar11;
    uStack_80 = uVar12;
    uStack_78 = uVar14;
    uStack_70 = uVar15;
    uStack_68 = uVar17;
    if (NAN(fVar19)) {
      fVar19 = (float)sqrtf();
    }
    fVar18 = (float)((ulong)uVar3 >> 0x20);
    fVar13 = (float)((ulong)uVar12 >> 0x20);
    fVar16 = (float)((ulong)uVar15 >> 0x20);
    fVar8 = SQRT(fVar18 * fVar18 + fVar13 * fVar13 + fVar16 * fVar16);
    if (NAN(fVar8)) {
      fVar8 = (float)sqrtf();
    }
    fVar10 = (float)uVar11 * (float)uVar11 + (float)uVar14 * (float)uVar14 +
             (float)uVar17 * (float)uVar17;
    fVar7 = SQRT(fVar10);
    fVar19 = 1.0 / fVar19;
    fVar8 = 1.0 / fVar8;
    if (NAN(fVar7)) {
      fVar7 = (float)sqrtf(fVar10);
    }
    uStack_90 = CONCAT44(fVar8 * fVar18,fVar19 * fVar20);
    fVar7 = 1.0 / fVar7;
    uStack_88 = CONCAT44(uStack_88._4_4_,fVar7 * (float)uStack_88);
    uStack_78 = CONCAT44(uStack_78._4_4_,fVar7 * (float)uStack_78);
    uStack_80 = CONCAT44(fVar8 * fVar13,fVar19 * fVar21);
    uStack_70 = CONCAT44(fVar8 * fVar16,fVar19 * fVar9);
    uStack_68 = CONCAT44(uStack_68._4_4_,fVar7 * (float)uStack_68);
    Aska::Vector::ApplyMatrixNoTransport(Aska::Vector*, Aska::Matrix const*) const(param_1 + 0xb0,param_1 + 0x90,&uStack_90);
  }
  return;
}

// ==== Aska::DynamicsCapsule::Reset()
// vaddr 0x20a02a0 | ghidra 0x21a02a0 | size 16 | symbol _ZN4Aska15DynamicsCapsule5ResetEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15DynamicsCapsule5ResetEv(long param_1)

{
  undefined8 uVar1;
  
  uVar1 = _UNK_027dbb30;
  *(undefined8 *)(param_1 + 200) = _UNK_027dbb38;
  *(undefined8 *)(param_1 + 0xc0) = uVar1;
  return;
}

// ==== Aska::DynamicsCapsule::CreateParticleObject()
// vaddr 0x20a02b0 | ghidra 0x21a02b0 | size 76 | symbol _ZN4Aska15DynamicsCapsule20CreateParticleObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsCapsule20CreateParticleObjectEv(long param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x170,PTR__ZSt7nothrow_02cb9a80);
  if (plVar2 != (long *)0x0) {
    plVar2[0x26] = param_1;
    *(undefined2 *)(plVar2 + 0x27) = 1;
    puVar1 = PTR__ZTVN4Aska32ParticleDynamicsCapsuleDeflectorE_02cc1fe8 + 0x10;
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
    *plVar2 = (long)puVar1;
  }
  return;
}

// ==== Aska::DynamicsCapsule::Clone(Aska::IAnimatable const*)
// vaddr 0x20a02fc | ghidra 0x21a02fc | size 192 | symbol _ZN4Aska15DynamicsCapsule5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska15DynamicsCapsule5CloneEPKNS_11IAnimatableE(long param_1,long param_2)

{
  bool bVar1;
  ulong uVar2;
  
  uVar2 = Aska::IAnimatable::Clone(Aska::IAnimatable const*)();
  bVar1 = (uVar2 & 1) != 0;
  if (bVar1) {
    *(undefined8 *)(param_1 + 0x20) = *(undefined8 *)(param_2 + 0x20);
    **(undefined4 **)(param_1 + 0x50) = **(undefined4 **)(param_2 + 0x50);
    *(undefined4 *)(*(long *)(param_1 + 0x50) + 4) = *(undefined4 *)(*(long *)(param_2 + 0x50) + 4);
    *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_2 + 0xa0);
    *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_2 + 0xa4);
    *(undefined4 *)(param_1 + 0xa8) = *(undefined4 *)(param_2 + 0xa8);
    *(undefined4 *)(param_1 + 0xac) = *(undefined4 *)(param_2 + 0xac);
    *(undefined4 *)(param_1 + 0xb0) = *(undefined4 *)(param_2 + 0xb0);
    *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(param_1 + 0xb8) = *(undefined4 *)(param_2 + 0xb8);
    *(undefined4 *)(param_1 + 0xbc) = *(undefined4 *)(param_2 + 0xbc);
    *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(param_2 + 0xe0);
    **(undefined4 **)(param_1 + 0x50) = **(undefined4 **)(param_2 + 0x50);
    *(undefined4 *)(*(long *)(param_1 + 0x50) + 4) = *(undefined4 *)(*(long *)(param_2 + 0x50) + 4);
  }
  return bVar1;
}

// ==== Aska::DynamicsCapsule::CreateClone(Aska::IAnimatable const*)
// vaddr 0x20a03bc | ghidra 0x21a03bc | size 264 | symbol _ZN4Aska15DynamicsCapsule11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * _ZN4Aska15DynamicsCapsule11CreateCloneEPKNS_11IAnimatableE(undefined8 param_1,long param_2)

{
  long lVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  
  plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0xf0,PTR__ZSt7nothrow_02cb9a80);
  if (plVar2 != (long *)0x0) {
    plVar2[2] = 0;
    *(undefined4 *)(plVar2 + 5) = 0;
    plVar2[4] = 0;
    plVar2[8] = 0;
    *(undefined1 *)(plVar2 + 9) = 0;
    *(undefined1 *)(plVar2 + 3) = 1;
    lVar1 = _UNK_027dbb38;
    lVar4 = _UNK_027dbb30;
    *plVar2 = (long)(PTR__ZTVN4Aska15DynamicsCapsuleE_02cc38f0 + 0x10);
    plVar2[1] = 0;
    plVar2[7] = lVar1;
    plVar2[6] = lVar4;
    plVar2[0xc] = 0;
    *(undefined4 *)(plVar2 + 0xd) = 0;
    plVar2[0xe] = 0;
    plVar2[10] = (long)(plVar2 + 0xc);
    uVar3 = Aska::IAnimatable::Clone(Aska::IAnimatable const*)(plVar2,param_2);
    if ((uVar3 & 1) == 0) {
      (**(code **)(*plVar2 + 8))(plVar2);
      plVar2 = (long *)0x0;
    }
    else {
      plVar2[4] = *(long *)(param_2 + 0x20);
      *(undefined4 *)plVar2[10] = **(undefined4 **)(param_2 + 0x50);
      *(undefined4 *)(plVar2[10] + 4) = *(undefined4 *)(*(long *)(param_2 + 0x50) + 4);
      lVar4 = *(long *)(param_2 + 0xa0);
      plVar2[0x15] = *(long *)(param_2 + 0xa8);
      plVar2[0x14] = lVar4;
      lVar4 = *(long *)(param_2 + 0xb0);
      plVar2[0x17] = *(long *)(param_2 + 0xb8);
      plVar2[0x16] = lVar4;
      *(undefined4 *)(plVar2 + 0x1c) = *(undefined4 *)(param_2 + 0xe0);
      *(undefined4 *)plVar2[10] = **(undefined4 **)(param_2 + 0x50);
      *(undefined4 *)(plVar2[10] + 4) = *(undefined4 *)(*(long *)(param_2 + 0x50) + 4);
    }
  }
  return plVar2;
}

// ==== Aska::DynamicsCapsule::Get(unsigned long, void*) const
// vaddr 0x20a04c4 | ghidra 0x21a04c4 | size 176 | symbol _ZNK4Aska15DynamicsCapsule3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska15DynamicsCapsule3GetEmPv(long param_1,undefined8 param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  
  if ((short)((ulong)param_2 >> 0x20) == 0) {
    switch((uint)param_2 & 0xffff) {
    case 0x12:
      fVar1 = **(float **)(param_1 + 0x50);
      break;
    case 0x13:
      fVar1 = *(float *)(*(long *)(param_1 + 0x50) + 4);
      break;
    case 0x14:
      fVar2 = *(float *)(param_1 + 0xb0) * *(float *)(param_1 + 0xb0) +
              *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0xb4) +
              *(float *)(param_1 + 0xb8) * *(float *)(param_1 + 0xb8);
      fVar1 = SQRT(fVar2);
      if (NAN(fVar1)) {
        fVar1 = (float)sqrtf(fVar2);
      }
      *param_3 = fVar1;
      return 1;
    case 0x15:
      fVar1 = *(float *)(param_1 + 0xe0);
      break;
    default:
      return 0;
    }
    *param_3 = fVar1;
    return 1;
  }
  return 0;
}

// ==== Aska::DynamicsCapsule::Set(unsigned long, void const*)
// vaddr 0x20a0574 | ghidra 0x21a0574 | size 308 | symbol _ZN4Aska15DynamicsCapsule3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN4Aska15DynamicsCapsule3SetEmPKv(long param_1,undefined8 param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  if ((short)((ulong)param_2 >> 0x20) == 0) {
    switch((uint)param_2 & 0xffff) {
    case 0x12:
      **(float **)(param_1 + 0x50) = *param_3;
      return 0;
    case 0x13:
      *(float *)(*(long *)(param_1 + 0x50) + 4) = *param_3;
      return 0;
    case 0x14:
      fVar4 = *(float *)(param_1 + 0xb0);
      fVar5 = *(float *)(param_1 + 0xb4);
      fVar2 = *(float *)(param_1 + 0xb8);
      fVar6 = *param_3;
      fVar3 = fVar4 * fVar4 + fVar5 * fVar5 + fVar2 * fVar2;
      fVar1 = SQRT(fVar3);
      if (NAN(fVar1)) {
        fVar1 = (float)sqrtf(fVar3);
      }
      if (_UNK_027e519c <= fVar1) {
        fVar1 = 1.0 / fVar1;
        fVar4 = fVar1 * fVar4;
        fVar5 = fVar1 * fVar5;
        fVar2 = fVar1 * fVar2;
      }
      *(float *)(param_1 + 0xb0) = fVar6 * fVar4;
      *(float *)(param_1 + 0xb4) = fVar6 * fVar5;
      *(float *)(param_1 + 0xb8) = fVar6 * fVar2;
      *(undefined4 *)(param_1 + 0xbc) = 0x3f800000;
      break;
    case 0x15:
      *(float *)(param_1 + 0xe0) = *param_3;
      break;
    default:
      goto code_r0x021a0598;
    }
    return 1;
  }
code_r0x021a0598:
  return 0;
}

// ==== Aska::DynamicsPlane::Run()
// vaddr 0x20a06a8 | ghidra 0x21a06a8 | size 304 | symbol _ZN4Aska13DynamicsPlane3RunEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13DynamicsPlane3RunEv(long param_1)

{
  undefined8 uVar1;
  long *plVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  plVar2 = *(long **)(param_1 + 0x20);
  if (plVar2 != (long *)0x0) {
    fVar5 = *(float *)(param_1 + 0xb0);
    fVar4 = *(float *)(param_1 + 0xb4);
    fVar3 = *(float *)(param_1 + 0xb8);
    if ((*(byte *)(plVar2 + 0x25) & 1) != 0) {
      (**(code **)(*plVar2 + 0xa8))(plVar2);
    }
    uVar1 = (**(code **)(*plVar2 + 0x98))(plVar2);
    Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const(param_1 + 0x30,param_1 + 0x90,uVar1);
    *(float *)(param_1 + 0xb0) = *(float *)(param_1 + 0x90);
    *(float *)(param_1 + 0xb4) = *(float *)(param_1 + 0x94);
    *(float *)(param_1 + 0xb8) = *(float *)(param_1 + 0x98);
    *(undefined4 *)(param_1 + 0xbc) = *(undefined4 *)(param_1 + 0x9c);
    *(float *)(param_1 + 0xa0) = *(float *)(param_1 + 0x90) - fVar5;
    *(float *)(param_1 + 0xa4) = *(float *)(param_1 + 0x94) - fVar4;
    *(float *)(param_1 + 0xa8) = *(float *)(param_1 + 0x98) - fVar3;
    *(undefined4 *)(param_1 + 0xac) = *(undefined4 *)(param_1 + 0x9c);
    uVar1 = (**(code **)(*plVar2 + 0x98))(plVar2);
    Aska::Vector::ApplyMatrixNoTransport(Aska::Vector*, Aska::Matrix const*) const(PTR__ZN4Aska17DynamicsPrimitive8m_vUnitYE_02cbf898,param_1 + 0x80,uVar1);
    fVar4 = *(float *)(param_1 + 0x80) * *(float *)(param_1 + 0x80) +
            *(float *)(param_1 + 0x84) * *(float *)(param_1 + 0x84) +
            *(float *)(param_1 + 0x88) * *(float *)(param_1 + 0x88);
    fVar3 = SQRT(fVar4);
    if (NAN(fVar3)) {
      fVar3 = (float)sqrtf(fVar4);
    }
    if (_UNK_027e519c <= fVar3) {
      fVar3 = 1.0 / fVar3;
      *(float *)(param_1 + 0x80) = fVar3 * *(float *)(param_1 + 0x80);
      *(float *)(param_1 + 0x84) = fVar3 * *(float *)(param_1 + 0x84);
      *(float *)(param_1 + 0x88) = fVar3 * *(float *)(param_1 + 0x88);
    }
  }
  return;
}

// ==== Aska::DynamicsPlane::Reset()
// vaddr 0x20a07d8 | ghidra 0x21a07d8 | size 16 | symbol _ZN4Aska13DynamicsPlane5ResetEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska13DynamicsPlane5ResetEv(long param_1)

{
  undefined8 uVar1;
  
  uVar1 = _UNK_027dbb30;
  *(undefined8 *)(param_1 + 0xa8) = _UNK_027dbb38;
  *(undefined8 *)(param_1 + 0xa0) = uVar1;
  return;
}

// ==== Aska::DynamicsPlane::CreateParticleObject()
// vaddr 0x20a07e8 | ghidra 0x21a07e8 | size 76 | symbol _ZN4Aska13DynamicsPlane20CreateParticleObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13DynamicsPlane20CreateParticleObjectEv(long param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x160,PTR__ZSt7nothrow_02cb9a80);
  if (plVar2 != (long *)0x0) {
    plVar2[0x26] = param_1;
    *(undefined2 *)(plVar2 + 0x27) = 1;
    puVar1 = PTR__ZTVN4Aska30ParticleDynamicsPlaneDeflectorE_02cba098 + 0x10;
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
    *plVar2 = (long)puVar1;
  }
  return;
}

// ==== Aska::DynamicsSquare::Run()
// vaddr 0x20a0834 | ghidra 0x21a0834 | size 556 | symbol _ZN4Aska14DynamicsSquare3RunEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska14DynamicsSquare3RunEv(long param_1)

{
  long lVar1;
  undefined8 uVar2;
  byte bVar3;
  long *plVar4;
  long lVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  
  plVar4 = *(long **)(param_1 + 0x20);
  if (plVar4 != (long *)0x0) {
    fVar11 = *(float *)(param_1 + 0xf0);
    fVar10 = *(float *)(param_1 + 0xf4);
    bVar3 = *(byte *)(plVar4 + 0x25);
    fVar9 = *(float *)(param_1 + 0xf8);
    if ((bVar3 & 1) != 0) {
      (**(code **)(*plVar4 + 0xa8))(plVar4);
      bVar3 = *(byte *)(plVar4 + 0x25);
    }
    lVar1 = _UNK_027dbb38;
    lVar5 = _UNK_027dbb30;
    if ((bVar3 >> 2 & 1) == 0) {
      if ((*(byte *)((long)plVar4 + 0x129) & 3) == 0) {
        fVar6 = *(float *)((long)plVar4 + 0x4c);
        fVar7 = *(float *)((long)plVar4 + 0x5c);
        fVar8 = *(float *)((long)plVar4 + 0x6c);
        plVar4[0x27] = CONCAT44((int)plVar4[0xe],*(float *)(plVar4 + 0xc));
        plVar4[0x26] = CONCAT44(*(float *)(plVar4 + 10),*(float *)(plVar4 + 8));
        plVar4[0x29] = CONCAT44(*(undefined4 *)((long)plVar4 + 0x74),*(float *)((long)plVar4 + 100))
        ;
        plVar4[0x28] = CONCAT44(*(float *)((long)plVar4 + 0x54),*(float *)((long)plVar4 + 0x44));
        *(float *)((long)plVar4 + 0x13c) =
             -(*(float *)(plVar4 + 8) * fVar6 + *(float *)(plVar4 + 10) * fVar7 +
              *(float *)(plVar4 + 0xc) * fVar8);
        *(float *)((long)plVar4 + 0x14c) =
             -(fVar6 * *(float *)((long)plVar4 + 0x44) + fVar7 * *(float *)((long)plVar4 + 0x54) +
              fVar8 * *(float *)((long)plVar4 + 100));
        plVar4[0x2b] = CONCAT44((int)plVar4[0xf],*(float *)(plVar4 + 0xd));
        plVar4[0x2a] = CONCAT44(*(float *)(plVar4 + 0xb),*(float *)(plVar4 + 9));
        plVar4[0x2d] = lVar1;
        plVar4[0x2c] = lVar5;
        *(float *)((long)plVar4 + 0x15c) =
             -(fVar6 * *(float *)(plVar4 + 9) + fVar7 * *(float *)(plVar4 + 0xb) +
              fVar8 * *(float *)(plVar4 + 0xd));
      }
      else {
        Aska::Matrix::InvertLowError(Aska::Matrix*) const(plVar4 + 8,plVar4 + 0x26);
        bVar3 = *(byte *)(plVar4 + 0x25);
      }
      *(byte *)(plVar4 + 0x25) = bVar3 | 4;
    }
    uVar2 = (**(code **)(*plVar4 + 0x98))(plVar4);
    Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const(param_1 + 0x30,param_1 + 0xd0,uVar2);
    *(float *)(param_1 + 0xf0) = *(float *)(param_1 + 0xd0);
    *(float *)(param_1 + 0xf4) = *(float *)(param_1 + 0xd4);
    *(float *)(param_1 + 0xf8) = *(float *)(param_1 + 0xd8);
    *(undefined4 *)(param_1 + 0xfc) = *(undefined4 *)(param_1 + 0xdc);
    *(float *)(param_1 + 0xe0) = *(float *)(param_1 + 0xd0) - fVar11;
    *(float *)(param_1 + 0xe4) = *(float *)(param_1 + 0xd4) - fVar10;
    *(float *)(param_1 + 0xe8) = *(float *)(param_1 + 0xd8) - fVar9;
    *(undefined4 *)(param_1 + 0xec) = *(undefined4 *)(param_1 + 0xdc);
    uVar2 = (**(code **)(*plVar4 + 0x98))(plVar4);
    Aska::Vector::ApplyMatrixNoTransport(Aska::Vector*, Aska::Matrix const*) const(PTR__ZN4Aska17DynamicsPrimitive8m_vUnitYE_02cbf898,param_1 + 0xc0,uVar2);
    fVar10 = *(float *)(param_1 + 0xc0) * *(float *)(param_1 + 0xc0) +
             *(float *)(param_1 + 0xc4) * *(float *)(param_1 + 0xc4) +
             *(float *)(param_1 + 200) * *(float *)(param_1 + 200);
    fVar9 = SQRT(fVar10);
    if (NAN(fVar9)) {
      fVar9 = (float)sqrtf(fVar10);
    }
    if (_UNK_027e519c <= fVar9) {
      fVar9 = 1.0 / fVar9;
      *(float *)(param_1 + 0xc0) = fVar9 * *(float *)(param_1 + 0xc0);
      *(float *)(param_1 + 0xc4) = fVar9 * *(float *)(param_1 + 0xc4);
      *(float *)(param_1 + 200) = fVar9 * *(float *)(param_1 + 200);
    }
    lVar5 = plVar4[0x26];
    *(long *)(param_1 + 0x88) = plVar4[0x27];
    *(long *)(param_1 + 0x80) = lVar5;
    lVar5 = plVar4[0x28];
    *(long *)(param_1 + 0x98) = plVar4[0x29];
    *(long *)(param_1 + 0x90) = lVar5;
    lVar5 = plVar4[0x2a];
    *(long *)(param_1 + 0xa8) = plVar4[0x2b];
    *(long *)(param_1 + 0xa0) = lVar5;
    lVar5 = plVar4[0x2c];
    *(long *)(param_1 + 0xb8) = plVar4[0x2d];
    *(long *)(param_1 + 0xb0) = lVar5;
  }
  return;
}

// ==== Aska::DynamicsSquare::Reset()
// vaddr 0x20a0a60 | ghidra 0x21a0a60 | size 16 | symbol _ZN4Aska14DynamicsSquare5ResetEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska14DynamicsSquare5ResetEv(long param_1)

{
  undefined8 uVar1;
  
  uVar1 = _UNK_027dbb30;
  *(undefined8 *)(param_1 + 0xe8) = _UNK_027dbb38;
  *(undefined8 *)(param_1 + 0xe0) = uVar1;
  return;
}

// ==== Aska::DynamicsSquare::CreateParticleObject()
// vaddr 0x20a0a70 | ghidra 0x21a0a70 | size 76 | symbol _ZN4Aska14DynamicsSquare20CreateParticleObjectEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska14DynamicsSquare20CreateParticleObjectEv(long param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x160,PTR__ZSt7nothrow_02cb9a80);
  if (plVar2 != (long *)0x0) {
    plVar2[0x26] = param_1;
    *(undefined2 *)(plVar2 + 0x27) = 1;
    puVar1 = PTR__ZTVN4Aska31ParticleDynamicsSquareDeflectorE_02cc4938 + 0x10;
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
    *plVar2 = (long)puVar1;
  }
  return;
}

// ==== Aska::DynamicsSquare::Get(unsigned long, void*) const
// vaddr 0x20a0abc | ghidra 0x21a0abc | size 108 | symbol _ZNK4Aska14DynamicsSquare3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska14DynamicsSquare3GetEmPv(long param_1,undefined8 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  if ((short)((ulong)param_2 >> 0x20) == 0) {
    switch((uint)param_2 & 0xffff) {
    case 0x12:
      uVar1 = **(undefined4 **)(param_1 + 0x50);
      break;
    case 0x13:
      uVar1 = *(undefined4 *)(*(long *)(param_1 + 0x50) + 4);
      break;
    case 0x14:
      uVar1 = *(undefined4 *)(param_1 + 0x100);
      break;
    case 0x15:
      uVar1 = *(undefined4 *)(param_1 + 0x104);
      break;
    default:
      return 0;
    }
    *param_3 = uVar1;
    return 1;
  }
  return 0;
}

// ==== Aska::DynamicsSquare::Set(unsigned long, void const*)
// vaddr 0x20a0b28 | ghidra 0x21a0b28 | size 136 | symbol _ZN4Aska14DynamicsSquare3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska14DynamicsSquare3SetEmPKv(long param_1,undefined8 param_2,undefined4 *param_3)

{
  if ((short)((ulong)param_2 >> 0x20) == 0) {
    switch((uint)param_2 & 0xffff) {
    case 0x12:
      **(undefined4 **)(param_1 + 0x50) = *param_3;
      return 0;
    case 0x13:
      *(undefined4 *)(*(long *)(param_1 + 0x50) + 4) = *param_3;
      return 0;
    case 0x14:
      *(undefined4 *)(param_1 + 0x100) = *param_3;
      return 1;
    case 0x15:
      *(undefined4 *)(param_1 + 0x104) = *param_3;
      return 1;
    default:
      return 0;
    }
  }
  return 0;
}

// ==== Aska::DynamicsPrimitive::~DynamicsPrimitive()
// vaddr 0x20a0e38 | ghidra 0x21a0e38 | size 40 | symbol _ZN4Aska17DynamicsPrimitiveD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17DynamicsPrimitiveD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska20TInheritSmartPointerINS_8DynamicsELb0EEE_02cb8cb0 + 0x10);
  Aska::IAnimatable::~IAnimatable()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsPrimitive::GetClassID(int) const
// vaddr 0x20a0e60 | ghidra 0x21a0e60 | size 60 | symbol _ZNK4Aska17DynamicsPrimitive10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska17DynamicsPrimitive10GetClassIDEi(undefined8 param_1,int param_2)

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
  return 0xf032f150;
}

// ==== Aska::DynamicsPrimitive::DeleteThis()
// vaddr 0x20a0e9c | ghidra 0x21a0e9c | size 32 | symbol _ZN4Aska17DynamicsPrimitive10DeleteThisEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17DynamicsPrimitive10DeleteThisEv(long *param_1)

{
  int iVar1;
  
  iVar1 = (int)param_1[5] + -1;
  *(int *)(param_1 + 5) = iVar1;
  if (iVar1 != 0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x021a0eb8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 8))();
  return;
}

// ==== Aska::DynamicsPrimitive::AddRefEx()
// vaddr 0x20a0ebc | ghidra 0x21a0ebc | size 16 | symbol _ZN4Aska17DynamicsPrimitive8AddRefExEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17DynamicsPrimitive8AddRefExEv(long param_1)

{
  *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
  return;
}

// ==== Aska::DynamicsPrimitive::CreateParticleObject()
// vaddr 0x20a0ecc | ghidra 0x21a0ecc | size 8 | symbol _ZN4Aska17DynamicsPrimitive20CreateParticleObjectEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska17DynamicsPrimitive20CreateParticleObjectEv(void)

{
  return 0;
}

// ==== Aska::DynamicsPrimitive::Update(float, bool)
// vaddr 0x20a0ed4 | ghidra 0x21a0ed4 | size 4 | symbol _ZN4Aska17DynamicsPrimitive6UpdateEfb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17DynamicsPrimitive6UpdateEfb(void)

{
  return;
}

// ==== Aska::DynamicsPrimitive::Reset()
// vaddr 0x20a0ed8 | ghidra 0x21a0ed8 | size 4 | symbol _ZN4Aska17DynamicsPrimitive5ResetEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska17DynamicsPrimitive5ResetEv(void)

{
  return;
}

// ==== Aska::DynamicsPrimitive::TestIntersection(Aska::DYNAMICS_CAPSULE*, bool, Aska::Vector*, float*, float*)
// vaddr 0x20a0edc | ghidra 0x21a0edc | size 8 | symbol _ZN4Aska17DynamicsPrimitive16TestIntersectionEPNS_16DYNAMICS_CAPSULEEbPNS_6VectorEPfS5_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska17DynamicsPrimitive16TestIntersectionEPNS_16DYNAMICS_CAPSULEEbPNS_6VectorEPfS5_(void)

{
  return 0;
}

// ==== Aska::DynamicsPrimitive::TestIntersectionLocal(__Float32x4_t&, __Float32x4_t&, __Float32x4_t&, Aska::DYNAMICS_CAPSULE*, bool, Aska::Vector const*, Aska::Vector*, float*, float*)
// vaddr 0x20a0ee4 | ghidra 0x21a0ee4 | size 8 | symbol _ZN4Aska17DynamicsPrimitive21TestIntersectionLocalER13__Float32x4_tS2_S2_PNS_16DYNAMICS_CAPSULEEbPKNS_6VectorEPS5_PfS9_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska17DynamicsPrimitive21TestIntersectionLocalER13__Float32x4_tS2_S2_PNS_16DYNAMICS_CAPSULEEbPKNS_6VectorEPS5_PfS9_
          (void)

{
  return 0;
}

// ==== Aska::DynamicsPrimitive::TestIntersectionSphere(Aska::Vector const*, float, Aska::Vector*)
// vaddr 0x20a0eec | ghidra 0x21a0eec | size 8 | symbol _ZN4Aska17DynamicsPrimitive22TestIntersectionSphereEPKNS_6VectorEfPS1_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska17DynamicsPrimitive22TestIntersectionSphereEPKNS_6VectorEfPS1_(void)

{
  return 0;
}

// ==== Aska::DynamicsPrimitive::TestIntersection(Aska::Vector const*, float, Aska::Vector*)
// vaddr 0x20a0ef4 | ghidra 0x21a0ef4 | size 8 | symbol _ZN4Aska17DynamicsPrimitive16TestIntersectionEPKNS_6VectorEfPS1_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska17DynamicsPrimitive16TestIntersectionEPKNS_6VectorEfPS1_(void)

{
  return 0;
}

// ==== Aska::DynamicsCapsule::~DynamicsCapsule()
// vaddr 0x20a0efc | ghidra 0x21a0efc | size 40 | symbol _ZN4Aska15DynamicsCapsuleD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsCapsuleD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska20TInheritSmartPointerINS_8DynamicsELb0EEE_02cb8cb0 + 0x10);
  Aska::IAnimatable::~IAnimatable()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsCapsule::GetClassID(int) const
// vaddr 0x20a0f24 | ghidra 0x21a0f24 | size 84 | symbol _ZNK4Aska15DynamicsCapsule10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska15DynamicsCapsule10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf032f150f153;
  }
  if (param_2 == 1) {
    return 0xf032f150;
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

// ==== Aska::DynamicsCapsule::Update(float, bool)
// vaddr 0x20a0f78 | ghidra 0x21a0f78 | size 96 | symbol _ZN4Aska15DynamicsCapsule6UpdateEfb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsCapsule6UpdateEfb(float param_1,long param_2,uint param_3)

{
  if ((param_3 & 1) != 0) {
    *(undefined8 *)(param_2 + 0x80) = *(undefined8 *)(param_2 + 0xd0);
    *(undefined4 *)(param_2 + 0x88) = *(undefined4 *)(param_2 + 0xd8);
    *(undefined4 *)(param_2 + 0x8c) = 0x3f800000;
    return;
  }
  param_1 = 1.0 - param_1;
  *(float *)(param_2 + 0x80) = *(float *)(param_2 + 0xd0) - param_1 * *(float *)(param_2 + 0xc0);
  *(float *)(param_2 + 0x84) = *(float *)(param_2 + 0xd4) - param_1 * *(float *)(param_2 + 0xc4);
  *(float *)(param_2 + 0x88) = *(float *)(param_2 + 0xd8) - param_1 * *(float *)(param_2 + 200);
  *(undefined4 *)(param_2 + 0x8c) = *(undefined4 *)(param_2 + 0xdc);
  return;
}

// ==== Aska::DynamicsCapsule::TestIntersection(Aska::DYNAMICS_CAPSULE*, bool, Aska::Vector*, float*, float*)
// vaddr 0x20a0fd8 | ghidra 0x21a0fd8 | size 12 | symbol _ZN4Aska15DynamicsCapsule16TestIntersectionEPNS_16DYNAMICS_CAPSULEEbPNS_6VectorEPfS5_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsCapsule16TestIntersectionEPNS_16DYNAMICS_CAPSULEEbPNS_6VectorEPfS5_
               (long param_1,undefined8 param_2,uint param_3)

{
  (*(code *)PTR__ZN4Aska16DYNAMICS_CAPSULE16TestIntersectionEPS0_bPNS_6VectorEPfS4__02ca9318)
            (param_1 + 0x60,param_2,param_3 & 1);
  return;
}

// ==== Aska::DynamicsCapsule::TestIntersectionLocal(__Float32x4_t&, __Float32x4_t&, __Float32x4_t&, Aska::DYNAMICS_CAPSULE*, bool, Aska::Vector const*, Aska::Vector*, float*, float*)
// vaddr 0x20a0fe4 | ghidra 0x21a0fe4 | size 20 | symbol _ZN4Aska15DynamicsCapsule21TestIntersectionLocalER13__Float32x4_tS2_S2_PNS_16DYNAMICS_CAPSULEEbPKNS_6VectorEPS5_PfS9_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsCapsule21TestIntersectionLocalER13__Float32x4_tS2_S2_PNS_16DYNAMICS_CAPSULEEbPKNS_6VectorEPS5_PfS9_
               (long param_1)

{
  (*(code *)
    PTR__ZN4Aska16DYNAMICS_CAPSULE21TestIntersectionLocalER13__Float32x4_tS2_S2_PS0_bPKNS_6VectorEPS4_PfS8__02ca0b10
  )(param_1 + 0x60);
  return;
}

// ==== Aska::DynamicsCapsule::TestIntersectionSphere(Aska::Vector const*, float, Aska::Vector*)
// vaddr 0x20a0ff8 | ghidra 0x21a0ff8 | size 8 | symbol _ZN4Aska15DynamicsCapsule22TestIntersectionSphereEPKNS_6VectorEfPS1_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsCapsule22TestIntersectionSphereEPKNS_6VectorEfPS1_(long param_1)

{
  (*(code *)PTR__ZN4Aska16DYNAMICS_CAPSULE22TestIntersectionSphereEPKNS_6VectorEfPS1__02c93f18)
            (param_1 + 0x60);
  return;
}

// ==== Aska::DynamicsCapsule::TestIntersection(Aska::Vector const*, float, Aska::Vector*)
// vaddr 0x20a1000 | ghidra 0x21a1000 | size 8 | symbol _ZN4Aska15DynamicsCapsule16TestIntersectionEPKNS_6VectorEfPS1_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsCapsule16TestIntersectionEPKNS_6VectorEfPS1_(long param_1)

{
  (*(code *)PTR__ZN4Aska16DYNAMICS_CAPSULE16TestIntersectionEPKNS_6VectorEfPS1__02c9d9d0)
            (param_1 + 0x60);
  return;
}

// ==== Aska::DynamicsCube::~DynamicsCube()
// vaddr 0x20a1008 | ghidra 0x21a1008 | size 40 | symbol _ZN4Aska12DynamicsCubeD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12DynamicsCubeD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska20TInheritSmartPointerINS_8DynamicsELb0EEE_02cb8cb0 + 0x10);
  Aska::IAnimatable::~IAnimatable()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsCube::GetClassID(int) const
// vaddr 0x20a1030 | ghidra 0x21a1030 | size 84 | symbol _ZNK4Aska12DynamicsCube10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska12DynamicsCube10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf032f150f151;
  }
  if (param_2 == 1) {
    return 0xf032f150;
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

// ==== Aska::DynamicsCube::Update(float, bool)
// vaddr 0x20a1084 | ghidra 0x21a1084 | size 104 | symbol _ZN4Aska12DynamicsCube6UpdateEfb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12DynamicsCube6UpdateEfb(float param_1,long param_2,uint param_3)

{
  if ((param_3 & 1) == 0) {
    param_1 = 1.0 - param_1;
    *(float *)(param_2 + 0x80) = *(float *)(param_2 + 0x160) - param_1 * *(float *)(param_2 + 0x150)
    ;
    *(float *)(param_2 + 0x84) = *(float *)(param_2 + 0x164) - param_1 * *(float *)(param_2 + 0x154)
    ;
    *(float *)(param_2 + 0x88) = *(float *)(param_2 + 0x168) - param_1 * *(float *)(param_2 + 0x158)
    ;
  }
  else {
    *(undefined4 *)(param_2 + 0x80) = *(undefined4 *)(param_2 + 0x160);
    *(undefined4 *)(param_2 + 0x84) = *(undefined4 *)(param_2 + 0x164);
    *(undefined4 *)(param_2 + 0x88) = *(undefined4 *)(param_2 + 0x168);
  }
  *(undefined4 *)(param_2 + 0x8c) = *(undefined4 *)(param_2 + 0x16c);
  return;
}

// ==== Aska::DynamicsCube::TestIntersection(Aska::DYNAMICS_CAPSULE*, bool, Aska::Vector*, float*, float*)
// vaddr 0x20a10ec | ghidra 0x21a10ec | size 12 | symbol _ZN4Aska12DynamicsCube16TestIntersectionEPNS_16DYNAMICS_CAPSULEEbPNS_6VectorEPfS5_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12DynamicsCube16TestIntersectionEPNS_16DYNAMICS_CAPSULEEbPNS_6VectorEPfS5_
               (long param_1,undefined8 param_2,uint param_3)

{
  (*(code *)
    PTR__ZN4Aska13DYNAMICS_CUBE16TestIntersectionEPNS_16DYNAMICS_CAPSULEEbPNS_6VectorEPfS5__02cabbd0
  )(param_1 + 0x60,param_2,param_3 & 1);
  return;
}

// ==== Aska::DynamicsCube::TestIntersectionLocal(__Float32x4_t&, __Float32x4_t&, __Float32x4_t&, Aska::DYNAMICS_CAPSULE*, bool, Aska::Vector const*, Aska::Vector*, float*, float*)
// vaddr 0x20a10f8 | ghidra 0x21a10f8 | size 20 | symbol _ZN4Aska12DynamicsCube21TestIntersectionLocalER13__Float32x4_tS2_S2_PNS_16DYNAMICS_CAPSULEEbPKNS_6VectorEPS5_PfS9_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12DynamicsCube21TestIntersectionLocalER13__Float32x4_tS2_S2_PNS_16DYNAMICS_CAPSULEEbPKNS_6VectorEPS5_PfS9_
               (long param_1)

{
  (*(code *)
    PTR__ZN4Aska13DYNAMICS_CUBE21TestIntersectionLocalER13__Float32x4_tS2_S2_PNS_16DYNAMICS_CAPSULEEbPKNS_6VectorEPS5_PfS9__02c9d330
  )(param_1 + 0x60);
  return;
}

// ==== Aska::DynamicsCube::TestIntersectionSphere(Aska::Vector const*, float, Aska::Vector*)
// vaddr 0x20a110c | ghidra 0x21a110c | size 8 | symbol _ZN4Aska12DynamicsCube22TestIntersectionSphereEPKNS_6VectorEfPS1_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12DynamicsCube22TestIntersectionSphereEPKNS_6VectorEfPS1_(long param_1)

{
  (*(code *)PTR__ZN4Aska13DYNAMICS_CUBE22TestIntersectionSphereEPKNS_6VectorEfPS1__02cb1070)
            (param_1 + 0x60);
  return;
}

// ==== Aska::DynamicsCube::TestIntersection(Aska::Vector const*, float, Aska::Vector*)
// vaddr 0x20a1114 | ghidra 0x21a1114 | size 8 | symbol _ZN4Aska12DynamicsCube16TestIntersectionEPKNS_6VectorEfPS1_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12DynamicsCube16TestIntersectionEPKNS_6VectorEfPS1_(long param_1)

{
  (*(code *)PTR__ZN4Aska13DYNAMICS_CUBE16TestIntersectionEPKNS_6VectorEfPS1__02c9a6c8)
            (param_1 + 0x60);
  return;
}

// ==== Aska::DynamicsSphere::~DynamicsSphere()
// vaddr 0x20a111c | ghidra 0x21a111c | size 40 | symbol _ZN4Aska14DynamicsSphereD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska14DynamicsSphereD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska20TInheritSmartPointerINS_8DynamicsELb0EEE_02cb8cb0 + 0x10);
  Aska::IAnimatable::~IAnimatable()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsSphere::GetClassID(int) const
// vaddr 0x20a1144 | ghidra 0x21a1144 | size 84 | symbol _ZNK4Aska14DynamicsSphere10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska14DynamicsSphere10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf032f150f152;
  }
  if (param_2 == 1) {
    return 0xf032f150;
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

// ==== Aska::DynamicsSphere::Update(float, bool)
// vaddr 0x20a1198 | ghidra 0x21a1198 | size 92 | symbol _ZN4Aska14DynamicsSphere6UpdateEfb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska14DynamicsSphere6UpdateEfb(float param_1,long param_2,uint param_3)

{
  if ((param_3 & 1) == 0) {
    param_1 = 1.0 - param_1;
    *(float *)(param_2 + 0x90) = *(float *)(param_2 + 0xb0) - param_1 * *(float *)(param_2 + 0xa0);
    *(float *)(param_2 + 0x94) = *(float *)(param_2 + 0xb4) - param_1 * *(float *)(param_2 + 0xa4);
    *(float *)(param_2 + 0x98) = *(float *)(param_2 + 0xb8) - param_1 * *(float *)(param_2 + 0xa8);
  }
  else {
    *(undefined4 *)(param_2 + 0x90) = *(undefined4 *)(param_2 + 0xb0);
    *(undefined4 *)(param_2 + 0x94) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(param_2 + 0x98) = *(undefined4 *)(param_2 + 0xb8);
  }
  *(undefined4 *)(param_2 + 0x9c) = *(undefined4 *)(param_2 + 0xbc);
  return;
}

// ==== Aska::DynamicsSphere::TestIntersection(Aska::DYNAMICS_CAPSULE*, bool, Aska::Vector*, float*, float*)
// vaddr 0x20a11f4 | ghidra 0x21a11f4 | size 320 | symbol _ZN4Aska14DynamicsSphere16TestIntersectionEPNS_16DYNAMICS_CAPSULEEbPNS_6VectorEPfS5_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska14DynamicsSphere16TestIntersectionEPNS_16DYNAMICS_CAPSULEEbPNS_6VectorEPfS5_
          (long param_1,long param_2,undefined8 param_3,float *param_4,float *param_5,float *param_6
          )

{
  float fVar1;
  float fVar2;
  undefined8 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fStack_44;
  
  uVar3 = Aska::Segment::SquaredDistance(Aska::Vector const*, float*) const(param_2 + 0x40,param_1 + 0x90,&fStack_44);
  fVar7 = *(float *)(param_1 + 0x80) + *(float *)(param_2 + 0x80);
  if ((float)uVar3 <= fVar7 * fVar7) {
    fVar8 = (fStack_44 * *(float *)(param_2 + 0x50) + *(float *)(param_2 + 0x40)) -
            *(float *)(param_1 + 0x90);
    fVar2 = *(float *)(param_2 + 0x5c);
    fVar5 = ((float)*(undefined8 *)(param_2 + 0x54) * fStack_44 +
            (float)*(undefined8 *)(param_2 + 0x44)) - (float)*(undefined8 *)(param_1 + 0x94);
    fVar6 = ((float)((ulong)*(undefined8 *)(param_2 + 0x54) >> 0x20) * fStack_44 +
            (float)((ulong)*(undefined8 *)(param_2 + 0x44) >> 0x20)) -
            (float)((ulong)*(undefined8 *)(param_1 + 0x94) >> 0x20);
    fVar4 = fVar8 * fVar8 + fVar5 * fVar5 + fVar6 * fVar6;
    fVar1 = SQRT(fVar4);
    if (NAN(fVar1)) {
      fVar1 = (float)sqrtf(fVar4);
    }
    if (_UNK_027e519c <= fVar1) {
      fVar1 = 1.0 / fVar1;
      fVar8 = fVar8 * fVar1;
      fVar5 = fVar5 * fVar1;
      fVar6 = fVar6 * fVar1;
    }
    *param_4 = fVar8;
    param_4[1] = fVar5;
    param_4[2] = fVar6;
    param_4[3] = fVar2;
    fVar2 = SQRT((float)uVar3);
    *param_5 = fStack_44;
    if (NAN(fVar2)) {
      fVar2 = (float)sqrtf(uVar3);
    }
    uVar3 = 1;
    *param_6 = fVar7 - fVar2;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

// ==== Aska::DynamicsSphere::TestIntersectionLocal(__Float32x4_t&, __Float32x4_t&, __Float32x4_t&, Aska::DYNAMICS_CAPSULE*, bool, Aska::Vector const*, Aska::Vector*, float*, float*)
// vaddr 0x20a1334 | ghidra 0x21a1334 | size 20 | symbol _ZN4Aska14DynamicsSphere21TestIntersectionLocalER13__Float32x4_tS2_S2_PNS_16DYNAMICS_CAPSULEEbPKNS_6VectorEPS5_PfS9_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska14DynamicsSphere21TestIntersectionLocalER13__Float32x4_tS2_S2_PNS_16DYNAMICS_CAPSULEEbPKNS_6VectorEPS5_PfS9_
               (long param_1)

{
  (*(code *)
    PTR__ZN4Aska15DYNAMICS_SPHERE21TestIntersectionLocalER13__Float32x4_tS2_S2_PNS_16DYNAMICS_CAPSULEEbPKNS_6VectorEPS5_PfS9__02ca0c70
  )(param_1 + 0x60);
  return;
}

// ==== Aska::DynamicsSphere::TestIntersectionSphere(Aska::Vector const*, float, Aska::Vector*)
// vaddr 0x20a1348 | ghidra 0x21a1348 | size 276 | symbol _ZN4Aska14DynamicsSphere22TestIntersectionSphereEPKNS_6VectorEfPS1_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska14DynamicsSphere22TestIntersectionSphereEPKNS_6VectorEfPS1_
          (float param_1,long param_2,float *param_3,float *param_4)

{
  undefined8 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  fVar7 = *param_3 - *(float *)(param_2 + 0x90);
  fVar6 = param_3[1] - *(float *)(param_2 + 0x94);
  fVar5 = param_3[2] - *(float *)(param_2 + 0x98);
  fVar4 = fVar7 * fVar7 + fVar6 * fVar6 + fVar5 * fVar5;
  fVar3 = SQRT(fVar4);
  if (NAN(fVar3)) {
    fVar3 = (float)sqrtf(fVar4);
  }
  fVar3 = fVar3 - (*(float *)(param_2 + 0x80) + param_1);
  if (fVar3 <= 0.0) {
    fVar2 = SQRT(fVar4);
    if (NAN(fVar2)) {
      fVar2 = (float)sqrtf(fVar4);
    }
    if (_UNK_027e519c <= fVar2) {
      fVar2 = 1.0 / fVar2;
      fVar7 = fVar7 * fVar2;
      fVar6 = fVar6 * fVar2;
      fVar5 = fVar5 * fVar2;
    }
    uVar1 = 1;
    *param_4 = *param_3 - fVar3 * fVar7;
    param_4[1] = param_3[1] - fVar3 * fVar6;
    param_4[2] = param_3[2] - fVar3 * fVar5;
    param_4[3] = param_3[3];
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// ==== Aska::DynamicsSphere::TestIntersection(Aska::Vector const*, float, Aska::Vector*)
// vaddr 0x20a145c | ghidra 0x21a145c | size 276 | symbol _ZN4Aska14DynamicsSphere16TestIntersectionEPKNS_6VectorEfPS1_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska14DynamicsSphere16TestIntersectionEPKNS_6VectorEfPS1_
          (float param_1,long param_2,float *param_3,float *param_4)

{
  undefined8 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  fVar7 = *param_3 - *(float *)(param_2 + 0x90);
  fVar6 = param_3[1] - *(float *)(param_2 + 0x94);
  fVar5 = param_3[2] - *(float *)(param_2 + 0x98);
  fVar4 = fVar7 * fVar7 + fVar6 * fVar6 + fVar5 * fVar5;
  fVar3 = SQRT(fVar4);
  if (NAN(fVar3)) {
    fVar3 = (float)sqrtf(fVar4);
  }
  fVar3 = fVar3 - (*(float *)(param_2 + 0x80) - param_1);
  if (0.0 <= fVar3) {
    fVar2 = SQRT(fVar4);
    if (NAN(fVar2)) {
      fVar2 = (float)sqrtf(fVar4);
    }
    if (_UNK_027e519c <= fVar2) {
      fVar2 = 1.0 / fVar2;
      fVar7 = fVar7 * fVar2;
      fVar6 = fVar6 * fVar2;
      fVar5 = fVar5 * fVar2;
    }
    uVar1 = 1;
    *param_4 = *param_3 - fVar3 * fVar7;
    param_4[1] = param_3[1] - fVar3 * fVar6;
    param_4[2] = param_3[2] - fVar3 * fVar5;
    param_4[3] = param_3[3];
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// ==== Aska::DynamicsPlane::~DynamicsPlane()
// vaddr 0x20a1570 | ghidra 0x21a1570 | size 40 | symbol _ZN4Aska13DynamicsPlaneD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13DynamicsPlaneD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska20TInheritSmartPointerINS_8DynamicsELb0EEE_02cb8cb0 + 0x10);
  Aska::IAnimatable::~IAnimatable()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsPlane::GetClassID(int) const
// vaddr 0x20a1598 | ghidra 0x21a1598 | size 84 | symbol _ZNK4Aska13DynamicsPlane10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska13DynamicsPlane10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf032f150f154;
  }
  if (param_2 == 1) {
    return 0xf032f150;
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

// ==== Aska::DynamicsPlane::Update(float, bool)
// vaddr 0x20a15ec | ghidra 0x21a15ec | size 92 | symbol _ZN4Aska13DynamicsPlane6UpdateEfb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska13DynamicsPlane6UpdateEfb(float param_1,long param_2,uint param_3)

{
  if ((param_3 & 1) == 0) {
    param_1 = 1.0 - param_1;
    *(float *)(param_2 + 0x90) = *(float *)(param_2 + 0xb0) - param_1 * *(float *)(param_2 + 0xa0);
    *(float *)(param_2 + 0x94) = *(float *)(param_2 + 0xb4) - param_1 * *(float *)(param_2 + 0xa4);
    *(float *)(param_2 + 0x98) = *(float *)(param_2 + 0xb8) - param_1 * *(float *)(param_2 + 0xa8);
  }
  else {
    *(undefined4 *)(param_2 + 0x90) = *(undefined4 *)(param_2 + 0xb0);
    *(undefined4 *)(param_2 + 0x94) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(param_2 + 0x98) = *(undefined4 *)(param_2 + 0xb8);
  }
  *(undefined4 *)(param_2 + 0x9c) = *(undefined4 *)(param_2 + 0xbc);
  return;
}

// ==== Aska::DynamicsPlane::TestIntersection(Aska::Vector const*, float, Aska::Vector*)
// vaddr 0x20a1648 | ghidra 0x21a1648 | size 124 | symbol _ZN4Aska13DynamicsPlane16TestIntersectionEPKNS_6VectorEfPS1_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska13DynamicsPlane16TestIntersectionEPKNS_6VectorEfPS1_
          (float param_1,long param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar2 = param_3[1];
  fVar4 = *(float *)(param_2 + 0x84);
  fVar3 = param_3[2];
  fVar5 = *(float *)(param_2 + 0x88);
  fVar6 = (*param_3 - *(float *)(param_2 + 0x90)) * *(float *)(param_2 + 0x80) +
          (fVar2 - *(float *)(param_2 + 0x94)) * fVar4 +
          (fVar3 - *(float *)(param_2 + 0x98)) * fVar5;
  if (param_1 < fVar6) {
    return 0;
  }
  fVar1 = param_3[3];
  fVar6 = fVar6 - param_1;
  *param_4 = *param_3 - *(float *)(param_2 + 0x80) * fVar6;
  param_4[1] = fVar2 - fVar4 * fVar6;
  param_4[2] = fVar3 - fVar5 * fVar6;
  param_4[3] = fVar1;
  return 1;
}

// ==== Aska::DynamicsSquare::~DynamicsSquare()
// vaddr 0x20a16c4 | ghidra 0x21a16c4 | size 40 | symbol _ZN4Aska14DynamicsSquareD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska14DynamicsSquareD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska20TInheritSmartPointerINS_8DynamicsELb0EEE_02cb8cb0 + 0x10);
  Aska::IAnimatable::~IAnimatable()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsSquare::GetClassID(int) const
// vaddr 0x20a16ec | ghidra 0x21a16ec | size 84 | symbol _ZNK4Aska14DynamicsSquare10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska14DynamicsSquare10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    return 0xf032f150f155;
  }
  if (param_2 == 1) {
    return 0xf032f150;
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

// ==== Aska::DynamicsSquare::Update(float, bool)
// vaddr 0x20a1740 | ghidra 0x21a1740 | size 92 | symbol _ZN4Aska14DynamicsSquare6UpdateEfb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska14DynamicsSquare6UpdateEfb(float param_1,long param_2,uint param_3)

{
  if ((param_3 & 1) == 0) {
    param_1 = 1.0 - param_1;
    *(float *)(param_2 + 0xd0) = *(float *)(param_2 + 0xf0) - param_1 * *(float *)(param_2 + 0xe0);
    *(float *)(param_2 + 0xd4) = *(float *)(param_2 + 0xf4) - param_1 * *(float *)(param_2 + 0xe4);
    *(float *)(param_2 + 0xd8) = *(float *)(param_2 + 0xf8) - param_1 * *(float *)(param_2 + 0xe8);
  }
  else {
    *(undefined4 *)(param_2 + 0xd0) = *(undefined4 *)(param_2 + 0xf0);
    *(undefined4 *)(param_2 + 0xd4) = *(undefined4 *)(param_2 + 0xf4);
    *(undefined4 *)(param_2 + 0xd8) = *(undefined4 *)(param_2 + 0xf8);
  }
  *(undefined4 *)(param_2 + 0xdc) = *(undefined4 *)(param_2 + 0xfc);
  return;
}

// ==== Aska::DynamicsSquare::TestIntersection(Aska::Vector const*, float, Aska::Vector*)
// vaddr 0x20a179c | ghidra 0x21a179c | size 8 | symbol _ZN4Aska14DynamicsSquare16TestIntersectionEPKNS_6VectorEfPS1_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska14DynamicsSquare16TestIntersectionEPKNS_6VectorEfPS1_(long param_1)

{
  (*(code *)PTR__ZN4Aska15DYNAMICS_SQUARE16TestIntersectionEPKNS_6VectorEfPS1__02cab708)
            (param_1 + 0x60);
  return;
}

// ==== Aska::DynamicsPrimitiveListPool::~DynamicsPrimitiveListPool()
// vaddr 0x20a17a4 | ghidra 0x21a17a4 | size 84 | symbol _ZN4Aska25DynamicsPrimitiveListPoolD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska25DynamicsPrimitiveListPoolD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska9TPoolFastINS_24DynamicsPrimitiveElementELb1EEE_02cbf700 + 0x10);
  Aska::TPoolFast<Aska::DynamicsPrimitiveElement, true>::ReleasePool()();
  Aska::FastCriticalSection::~FastCriticalSection()(param_1 + 8);
  param_1[1] = (long)(PTR__ZTVN4Aska9TBitArrayImLb0EEE_02cbeda0 + 0x10);
  if ((param_1[3] != 0) && ((char)param_1[5] != '\0')) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DYNAMICS_CAPSULE::TestIntersection(Aska::DYNAMICS_CAPSULE*, bool, Aska::Vector*, float*, float*)
// vaddr 0x20a1954 | ghidra 0x21a1954 | size 344 | symbol _ZN4Aska16DYNAMICS_CAPSULE16TestIntersectionEPS0_bPNS_6VectorEPfS4_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska16DYNAMICS_CAPSULE16TestIntersectionEPS0_bPNS_6VectorEPfS4_
          (long param_1,long param_2,undefined8 param_3,float *param_4,float *param_5,float *param_6
          )

{
  float fVar1;
  undefined8 uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fStack_48;
  float fStack_44;
  
  uVar2 = Aska::Segment::SquaredDistance(Aska::Segment const*, float*, float*) const(param_1 + 0x20,param_2 + 0x40,&fStack_44,&fStack_48);
  fVar5 = *(float *)(param_1 + 0x80) + *(float *)(param_2 + 0x80);
  if ((float)uVar2 <= fVar5 * fVar5) {
    fVar1 = (*(float *)(param_2 + 0x40) + fStack_48 * *(float *)(param_2 + 0x50)) -
            (*(float *)(param_1 + 0x20) + fStack_44 * *(float *)(param_1 + 0x30));
    fVar3 = ((float)*(undefined8 *)(param_2 + 0x44) +
            (float)*(undefined8 *)(param_2 + 0x54) * fStack_48) -
            ((float)*(undefined8 *)(param_1 + 0x24) +
            (float)*(undefined8 *)(param_1 + 0x34) * fStack_44);
    fVar4 = ((float)((ulong)*(undefined8 *)(param_2 + 0x44) >> 0x20) +
            (float)((ulong)*(undefined8 *)(param_2 + 0x54) >> 0x20) * fStack_48) -
            ((float)((ulong)*(undefined8 *)(param_1 + 0x24) >> 0x20) +
            (float)((ulong)*(undefined8 *)(param_1 + 0x34) >> 0x20) * fStack_44);
    *param_4 = fVar1;
    *(ulong *)(param_4 + 1) = CONCAT44(fVar4,fVar3);
    fVar3 = fVar1 * fVar1 + fVar3 * fVar3 + fVar4 * fVar4;
    fVar1 = SQRT(fVar3);
    param_4[3] = 1.0;
    if (NAN(fVar1)) {
      fVar1 = (float)sqrtf(fVar3);
    }
    if (_UNK_027e519c <= fVar1) {
      fVar1 = 1.0 / fVar1;
      *param_4 = fVar1 * *param_4;
      param_4[1] = fVar1 * param_4[1];
      param_4[2] = fVar1 * param_4[2];
    }
    fVar1 = SQRT((float)uVar2);
    *param_5 = fStack_48;
    if (NAN(fVar1)) {
      fVar1 = (float)sqrtf(uVar2);
    }
    uVar2 = 1;
    *param_6 = fVar5 - fVar1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

// ==== Aska::DYNAMICS_CAPSULE::TestIntersectionLocal(__Float32x4_t&, __Float32x4_t&, __Float32x4_t&, Aska::DYNAMICS_CAPSULE*, bool, Aska::Vector const*, Aska::Vector*, float*, float*)
// vaddr 0x20a1aac | ghidra 0x21a1aac | size 600 | symbol _ZN4Aska16DYNAMICS_CAPSULE21TestIntersectionLocalER13__Float32x4_tS2_S2_PS0_bPKNS_6VectorEPS4_PfS8_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska16DYNAMICS_CAPSULE21TestIntersectionLocalER13__Float32x4_tS2_S2_PS0_bPKNS_6VectorEPS4_PfS8_
          (long param_1,undefined1 (*param_2) [12],undefined1 (*param_3) [12],
          undefined1 (*param_4) [16],long param_5,undefined8 param_6,float *param_7,float *param_8,
          float *param_9,float *param_10)

{
  undefined1 (*pauVar1) [12];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined8 uVar5;
  float fVar6;
  undefined4 uVar7;
  float fVar8;
  float fVar9;
  undefined1 auVar10 [16];
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined1 auVar16 [16];
  float fVar17;
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  float fVar20;
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  undefined4 uStack_54;
  float fStack_48;
  float fStack_44;
  
  fStack_68 = (float)*(undefined8 *)(param_1 + 0x28);
  fStack_64 = (float)((ulong)*(undefined8 *)(param_1 + 0x28) >> 0x20);
  fStack_70 = (float)*(undefined8 *)(param_1 + 0x20);
  fStack_6c = (float)((ulong)*(undefined8 *)(param_1 + 0x20) >> 0x20);
  pauVar1 = (undefined1 (*) [12])(param_1 + 0x30);
  uVar7 = (undefined4)((ulong)*(undefined8 *)(param_1 + 0x38) >> 0x20);
  fVar6 = (float)*(undefined8 *)*pauVar1;
  fVar9 = (float)((ulong)*(undefined8 *)*pauVar1 >> 0x20);
  fVar17 = (float)((ulong)*(undefined8 *)(*param_2 + 8) >> 0x20);
  fVar8 = (float)*(undefined8 *)*param_2;
  fVar12 = (float)((ulong)*(undefined8 *)*param_2 >> 0x20);
  fVar15 = (float)((ulong)*(undefined8 *)(*param_3 + 8) >> 0x20);
  fVar20 = (float)*(undefined8 *)*param_3;
  fVar14 = (float)((ulong)*(undefined8 *)*param_3 >> 0x20);
  auVar4 = *param_4;
  auVar10._12_4_ = uVar7;
  auVar10._0_12_ = *pauVar1;
  auVar16._12_4_ = uVar7;
  auVar16._0_12_ = *pauVar1;
  auVar10 = NEON_ext(auVar10,auVar16,8,1);
  auVar18._0_4_ = fStack_70 * fVar8;
  auVar18._4_4_ = fStack_6c * fVar12;
  auVar18._8_4_ = fStack_68 * (float)*(undefined8 *)(*param_2 + 8);
  auVar18._12_4_ = fStack_64 * fVar17;
  auVar21._0_4_ = fStack_70 * fVar20;
  auVar21._4_4_ = fStack_6c * fVar14;
  auVar21._8_4_ = fStack_68 * (float)*(undefined8 *)(*param_3 + 8);
  auVar21._12_4_ = fStack_64 * fVar15;
  fVar11 = fStack_70 * auVar4._0_4_;
  fVar13 = fStack_6c * auVar4._4_4_;
  fStack_68 = fStack_68 * auVar4._8_4_;
  fStack_64 = fStack_64 * auVar4._12_4_;
  auVar19._12_4_ = fVar17;
  auVar19._0_12_ = *param_2;
  auVar23._12_4_ = fVar17;
  auVar23._0_12_ = *param_2;
  auVar23 = NEON_ext(auVar19,auVar23,8,1);
  auVar24._12_4_ = fVar15;
  auVar24._0_12_ = *param_3;
  auVar3._12_4_ = fVar15;
  auVar3._0_12_ = *param_3;
  auVar24 = NEON_ext(auVar24,auVar3,8,1);
  auVar16 = NEON_ext(auVar4,auVar4,8,1);
  fVar17 = auVar10._0_4_;
  auVar10 = NEON_ext(auVar18,auVar18,8,1);
  auVar19 = NEON_ext(auVar21,auVar21,8,1);
  auVar22._4_4_ = fVar13;
  auVar22._0_4_ = fVar11;
  auVar22._8_4_ = fStack_68;
  auVar22._12_4_ = fStack_64;
  auVar2._4_4_ = fVar13;
  auVar2._0_4_ = fVar11;
  auVar2._8_4_ = fStack_68;
  auVar2._12_4_ = fStack_64;
  auVar22 = NEON_ext(auVar22,auVar2,8,1);
  fStack_60 = fVar8 * fVar6 + fVar17 * auVar23._0_4_ + fVar12 * fVar9 + 0.0;
  fStack_5c = fVar20 * fVar6 + fVar17 * auVar24._0_4_ + fVar14 * fVar9 + 0.0;
  fStack_58 = auVar4._0_4_ * fVar6 + fVar17 * auVar16._0_4_ + auVar4._4_4_ * fVar9 + 0.0;
  uStack_54 = 0x3f800000;
  fVar6 = *(float *)(param_5 + 0x80);
  fVar9 = *(float *)(param_1 + 0x80);
  fVar17 = fVar6 + fVar9;
  fStack_70 = (fVar17 / (fVar9 + fVar6 * *param_7)) *
              (auVar10._0_4_ + auVar18._0_4_ + auVar10._4_4_ + auVar18._4_4_);
  fStack_6c = (fVar17 / (fVar9 + fVar6 * param_7[1])) *
              (auVar19._0_4_ + auVar21._0_4_ + auVar19._4_4_ + auVar21._4_4_);
  fStack_68 = (fVar17 / (fVar9 + fVar6 * param_7[2])) *
              (auVar22._0_4_ + fVar11 + auVar22._4_4_ + fVar13);
  fStack_64 = 1.0;
  fVar6 = (float)Aska::Segment::SquaredDistance(Aska::Segment const*, float*, float*) const(&fStack_70,param_5 + 0x40,&fStack_44,&fStack_48);
  fVar9 = *(float *)(param_1 + 0x80) + *(float *)(param_5 + 0x80);
  if (fVar6 <= fVar9 * fVar9) {
    fVar20 = (fStack_48 * *(float *)(param_5 + 0x50) + *(float *)(param_5 + 0x40)) -
             (fStack_44 * fStack_60 + fStack_70);
    fVar12 = ((float)*(undefined8 *)(param_5 + 0x54) * fStack_48 +
             (float)*(undefined8 *)(param_5 + 0x44)) - (fStack_5c * fStack_44 + fStack_6c);
    fVar11 = ((float)((ulong)*(undefined8 *)(param_5 + 0x54) >> 0x20) * fStack_48 +
             (float)((ulong)*(undefined8 *)(param_5 + 0x44) >> 0x20)) -
             (fStack_58 * fStack_44 + fStack_68);
    fVar17 = *(float *)(param_5 + 0x4c);
    fVar8 = fVar20 * fVar20 + fVar12 * fVar12 + fVar11 * fVar11;
    fVar13 = SQRT(fVar8);
    if (NAN(fVar13)) {
      fVar13 = (float)sqrtf(fVar8);
    }
    if (_UNK_027e519c <= fVar13) {
      fVar13 = 1.0 / fVar13;
      fVar20 = fVar20 * fVar13;
      fVar12 = fVar12 * fVar13;
      fVar11 = fVar11 * fVar13;
    }
    *param_8 = fVar20;
    param_8[1] = fVar12;
    param_8[2] = fVar11;
    param_8[3] = fVar17;
    fVar17 = SQRT(fVar6);
    *param_9 = fStack_48;
    if (NAN(fVar17)) {
      fVar17 = (float)sqrtf(fVar6);
    }
    uVar5 = 1;
    *param_10 = fVar9 - fVar17;
  }
  else {
    uVar5 = 0;
  }
  return uVar5;
}

// ==== Aska::DYNAMICS_CAPSULE::TestIntersectionSphere(Aska::Vector const*, float, Aska::Vector*)
// vaddr 0x20a1d04 | ghidra 0x21a1d04 | size 316 | symbol _ZN4Aska16DYNAMICS_CAPSULE22TestIntersectionSphereEPKNS_6VectorEfPS1_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska16DYNAMICS_CAPSULE22TestIntersectionSphereEPKNS_6VectorEfPS1_
          (float param_1,long param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  undefined8 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fStack_34;
  
  uVar3 = Aska::Segment::SquaredDistance(Aska::Vector const*, float*) const(param_2 + 0x20,param_3,&fStack_34);
  fVar1 = SQRT((float)uVar3);
  if (NAN(fVar1)) {
    fVar1 = (float)sqrtf(uVar3);
  }
  fVar1 = fVar1 - (*(float *)(param_2 + 0x80) + param_1);
  if (fVar1 <= 0.0) {
    fVar7 = (fStack_34 * *(float *)(param_2 + 0x30) + *(float *)(param_2 + 0x20)) - *param_3;
    fVar5 = ((float)*(undefined8 *)(param_2 + 0x34) * fStack_34 +
            (float)*(undefined8 *)(param_2 + 0x24)) - (float)*(undefined8 *)(param_3 + 1);
    fVar6 = ((float)((ulong)*(undefined8 *)(param_2 + 0x34) >> 0x20) * fStack_34 +
            (float)((ulong)*(undefined8 *)(param_2 + 0x24) >> 0x20)) -
            (float)((ulong)*(undefined8 *)(param_3 + 1) >> 0x20);
    fVar4 = fVar7 * fVar7 + fVar5 * fVar5 + fVar6 * fVar6;
    fVar2 = SQRT(fVar4);
    if (NAN(fVar2)) {
      fVar2 = (float)sqrtf(fVar4);
    }
    if (_UNK_027e519c <= fVar2) {
      fVar2 = 1.0 / fVar2;
      fVar7 = fVar7 * fVar2;
      fVar5 = fVar5 * fVar2;
      fVar6 = fVar6 * fVar2;
    }
    *param_4 = *param_3 + fVar1 * fVar7;
    uVar3 = 1;
    param_4[1] = fVar1 * fVar5 + param_3[1];
    fVar2 = param_3[2];
    param_4[3] = 1.0;
    param_4[2] = fVar1 * fVar6 + fVar2;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

// ==== Aska::DYNAMICS_CAPSULE::TestIntersection(Aska::Vector const*, float, Aska::Vector*)
// vaddr 0x20a1e40 | ghidra 0x21a1e40 | size 316 | symbol _ZN4Aska16DYNAMICS_CAPSULE16TestIntersectionEPKNS_6VectorEfPS1_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska16DYNAMICS_CAPSULE16TestIntersectionEPKNS_6VectorEfPS1_
          (float param_1,long param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  undefined8 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fStack_34;
  
  uVar3 = Aska::Segment::SquaredDistance(Aska::Vector const*, float*) const(param_2 + 0x20,param_3,&fStack_34);
  fVar1 = SQRT((float)uVar3);
  if (NAN(fVar1)) {
    fVar1 = (float)sqrtf(uVar3);
  }
  fVar1 = fVar1 - (*(float *)(param_2 + 0x80) - param_1);
  if (0.0 <= fVar1) {
    fVar7 = (fStack_34 * *(float *)(param_2 + 0x30) + *(float *)(param_2 + 0x20)) - *param_3;
    fVar5 = ((float)*(undefined8 *)(param_2 + 0x34) * fStack_34 +
            (float)*(undefined8 *)(param_2 + 0x24)) - (float)*(undefined8 *)(param_3 + 1);
    fVar6 = ((float)((ulong)*(undefined8 *)(param_2 + 0x34) >> 0x20) * fStack_34 +
            (float)((ulong)*(undefined8 *)(param_2 + 0x24) >> 0x20)) -
            (float)((ulong)*(undefined8 *)(param_3 + 1) >> 0x20);
    fVar4 = fVar7 * fVar7 + fVar5 * fVar5 + fVar6 * fVar6;
    fVar2 = SQRT(fVar4);
    if (NAN(fVar2)) {
      fVar2 = (float)sqrtf(fVar4);
    }
    if (_UNK_027e519c <= fVar2) {
      fVar2 = 1.0 / fVar2;
      fVar7 = fVar7 * fVar2;
      fVar5 = fVar5 * fVar2;
      fVar6 = fVar6 * fVar2;
    }
    *param_4 = *param_3 + fVar1 * fVar7;
    uVar3 = 1;
    param_4[1] = fVar1 * fVar5 + param_3[1];
    fVar2 = param_3[2];
    param_4[3] = 1.0;
    param_4[2] = fVar1 * fVar6 + fVar2;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

// ==== Aska::DYNAMICS_CUBE::TestIntersection(Aska::DYNAMICS_CAPSULE*, bool, Aska::Vector*, float*, float*)
// vaddr 0x20a1f7c | ghidra 0x21a1f7c | size 788 | symbol _ZN4Aska13DYNAMICS_CUBE16TestIntersectionEPNS_16DYNAMICS_CAPSULEEbPNS_6VectorEPfS5_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska13DYNAMICS_CUBE16TestIntersectionEPNS_16DYNAMICS_CAPSULEEbPNS_6VectorEPfS5_
          (long param_1,long param_2,ulong param_3,float *param_4,float *param_5,float *param_6)

{
  bool bVar1;
  long lVar2;
  int iVar3;
  undefined8 uVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  
  uVar4 = Aska::Box::SquaredDistance(Aska::Segment const*, float*, float*, float*, float*) const(param_1 + 0x20,param_2 + 0x40,&fStack_54,&fStack_58,&fStack_5c,&fStack_60)
  ;
  fVar8 = _UNK_027e519c;
  fVar10 = *(float *)(param_2 + 0x80);
  fVar6 = (float)uVar4;
  if (fVar6 <= fVar10 * fVar10) {
    if (_UNK_027e519c <= fVar6) {
      fVar7 = (*(float *)(param_2 + 0x50) * fStack_54 + *(float *)(param_2 + 0x40)) -
              (*(float *)(param_1 + 0x20) + fStack_58 * *(float *)(param_1 + 0x40) +
               fStack_5c * *(float *)(param_1 + 0x50) + fStack_60 * *(float *)(param_1 + 0x60));
      fVar9 = ((float)*(undefined8 *)(param_2 + 0x54) * fStack_54 +
              (float)*(undefined8 *)(param_2 + 0x44)) -
              ((float)*(undefined8 *)(param_1 + 0x24) +
               (float)*(undefined8 *)(param_1 + 0x44) * fStack_58 +
               (float)*(undefined8 *)(param_1 + 0x54) * fStack_5c +
              (float)*(undefined8 *)(param_1 + 100) * fStack_60);
      fVar5 = ((float)((ulong)*(undefined8 *)(param_2 + 0x54) >> 0x20) * fStack_54 +
              (float)((ulong)*(undefined8 *)(param_2 + 0x44) >> 0x20)) -
              ((float)((ulong)*(undefined8 *)(param_1 + 0x24) >> 0x20) +
               (float)((ulong)*(undefined8 *)(param_1 + 0x44) >> 0x20) * fStack_58 +
               (float)((ulong)*(undefined8 *)(param_1 + 0x54) >> 0x20) * fStack_5c +
              (float)((ulong)*(undefined8 *)(param_1 + 100) >> 0x20) * fStack_60);
      *param_4 = fVar7;
      *(ulong *)(param_4 + 1) = CONCAT44(fVar5,fVar9);
      fVar9 = fVar7 * fVar7 + fVar9 * fVar9 + fVar5 * fVar5;
      fVar7 = SQRT(fVar9);
      param_4[3] = 1.0;
      if (NAN(fVar7)) {
        fVar7 = (float)sqrtf(fVar9);
      }
      if (fVar8 <= fVar7) {
        fVar7 = 1.0 / fVar7;
        *param_4 = fVar7 * *param_4;
        param_4[1] = fVar7 * param_4[1];
        param_4[2] = fVar7 * param_4[2];
      }
      fVar6 = SQRT(fVar6);
      *param_5 = fStack_54;
      if (NAN(fVar6)) {
        fVar6 = (float)sqrtf(uVar4);
      }
      fVar10 = fVar10 - fVar6;
    }
    else {
      if ((param_3 & 1) == 0) {
        fVar8 = -1.0;
        fVar6 = -1.0;
        fVar7 = fStack_58;
        if (0.0 <= fStack_58) {
          fVar7 = -fStack_58;
        }
        fVar7 = *(float *)(param_1 + 0x30) + fVar7;
        if (0.0 <= fStack_58) {
          fVar6 = 1.0;
        }
        fVar9 = fVar8;
        if (0.0 <= fStack_5c) {
          fVar9 = 1.0;
          fStack_5c = -fStack_5c;
        }
        fStack_5c = *(float *)(param_1 + 0x34) + fStack_5c;
        if (0.0 <= fStack_60) {
          fStack_60 = *(float *)(param_1 + 0x38) - fStack_60;
          fVar8 = 1.0;
        }
        else {
          fStack_60 = fStack_60 + *(float *)(param_1 + 0x38);
        }
      }
      else {
        fVar7 = 1.0;
        fVar8 = -1.0;
        if (0.0 <= *(float *)(param_2 + 0x50)) {
          fVar8 = fVar7;
        }
        fVar9 = -1.0;
        if (0.0 <= *(float *)(param_2 + 0x54)) {
          fVar9 = 1.0;
        }
        fVar5 = -1.0;
        if (0.0 <= *(float *)(param_2 + 0x58)) {
          fVar5 = fVar7;
        }
        bVar1 = 0.0 <= fVar8 * fStack_58;
        if (bVar1) {
          fStack_58 = -fStack_58;
        }
        fVar6 = -1.0;
        if (bVar1) {
          fVar6 = fVar7;
        }
        bVar1 = 0.0 <= fVar9 * fStack_5c;
        fVar7 = *(float *)(param_1 + 0x30) + fStack_58;
        if (bVar1) {
          fStack_5c = -fStack_5c;
        }
        fVar9 = -1.0;
        if (bVar1) {
          fVar9 = 1.0;
        }
        fStack_5c = *(float *)(param_1 + 0x34) + fStack_5c;
        fVar8 = -1.0;
        if (0.0 <= fVar5 * fStack_60) {
          fStack_60 = -fStack_60;
          fVar8 = 1.0;
        }
        fStack_60 = *(float *)(param_1 + 0x38) + fStack_60;
      }
      iVar3 = 2;
      if (fStack_5c <= fStack_60) {
        iVar3 = 1;
      }
      if (fVar7 <= fStack_5c) {
        iVar3 = (uint)(fStack_60 < fVar7) << 1;
      }
      if (iVar3 == 2) {
        lVar2 = 2;
      }
      else {
        lVar2 = 1;
        fStack_60 = fStack_5c;
        fVar8 = fVar9;
        if (iVar3 != 1) {
          if (iVar3 != 0) {
            return 1;
          }
          lVar2 = 0;
          fStack_60 = fVar7;
          fVar8 = fVar6;
        }
      }
      param_1 = param_1 + lVar2 * 0x10;
      fVar6 = *(float *)(param_1 + 0x40);
      fVar7 = *(float *)(param_1 + 0x44);
      fVar9 = *(float *)(param_1 + 0x48);
      param_4[3] = 1.0;
      *param_4 = fVar8 * fVar6;
      param_4[1] = fVar8 * fVar7;
      param_4[2] = fVar8 * fVar9;
      fVar10 = fVar10 + fStack_60;
      *param_5 = fStack_54;
    }
    uVar4 = 1;
    *param_6 = fVar10;
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}

// ==== Aska::DYNAMICS_CUBE::TestIntersectionLocal(__Float32x4_t&, __Float32x4_t&, __Float32x4_t&, Aska::DYNAMICS_CAPSULE*, bool, Aska::Vector const*, Aska::Vector*, float*, float*)
// vaddr 0x20a2290 | ghidra 0x21a2290 | size 1064 | symbol _ZN4Aska13DYNAMICS_CUBE21TestIntersectionLocalER13__Float32x4_tS2_S2_PNS_16DYNAMICS_CAPSULEEbPKNS_6VectorEPS5_PfS9_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska13DYNAMICS_CUBE21TestIntersectionLocalER13__Float32x4_tS2_S2_PNS_16DYNAMICS_CAPSULEEbPKNS_6VectorEPS5_PfS9_
          (long param_1,undefined8 *param_2,float *param_3,float *param_4,long param_5,uint param_6,
          float *param_7,float *param_8,float *param_9,float *param_10)

{
  bool bVar1;
  undefined8 uVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  float extraout_s0;
  float fVar7;
  undefined8 extraout_d0;
  undefined1 auVar8 [16];
  undefined8 extraout_var;
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  float fVar20;
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined8 uVar24;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  float fStack_c4;
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
  
  fVar13 = *(float *)(param_1 + 0x20);
  fVar7 = *(float *)(param_1 + 0x24);
  fVar20 = *(float *)(param_1 + 0x28);
  fVar17 = *(float *)(param_1 + 0x2c);
  fStack_a0 = *(float *)(param_1 + 0x40);
  fStack_9c = *(float *)(param_1 + 0x44);
  fStack_98 = *(float *)(param_1 + 0x48);
  fVar12 = fVar13 * (float)*param_2;
  fVar14 = fVar7 * (float)((ulong)*param_2 >> 0x20);
  fVar15 = fVar20 * (float)param_2[1];
  fVar16 = fVar17 * (float)((ulong)param_2[1] >> 0x20);
  uStack_94 = 0;
  fStack_90 = *(float *)(param_1 + 0x50);
  auVar18._0_4_ = fVar13 * *param_3;
  auVar18._4_4_ = fVar7 * param_3[1];
  auVar18._8_4_ = fVar20 * param_3[2];
  auVar18._12_4_ = fVar17 * param_3[3];
  auVar9._0_4_ = fVar13 * *param_4;
  auVar9._4_4_ = fVar7 * param_4[1];
  auVar9._8_4_ = fVar20 * param_4[2];
  auVar9._12_4_ = fVar17 * param_4[3];
  auVar10._4_4_ = fVar14;
  auVar10._0_4_ = fVar12;
  auVar10._8_4_ = fVar15;
  auVar10._12_4_ = fVar16;
  auVar19._4_4_ = fVar14;
  auVar19._0_4_ = fVar12;
  auVar19._8_4_ = fVar15;
  auVar19._12_4_ = fVar16;
  auVar21 = NEON_ext(auVar10,auVar19,8,1);
  fStack_8c = *(float *)(param_1 + 0x54);
  auVar22 = NEON_ext(auVar18,auVar18,8,1);
  fStack_88 = *(float *)(param_1 + 0x58);
  auVar23 = NEON_ext(auVar9,auVar9,8,1);
  uStack_84 = 0;
  fStack_80 = *(float *)(param_1 + 0x60);
  fStack_7c = *(float *)(param_1 + 100);
  fStack_78 = *(float *)(param_1 + 0x68);
  uStack_74 = 0;
  uStack_b0 = *(undefined8 *)(param_1 + 0x30);
  uStack_a8 = *(undefined8 *)(param_1 + 0x38);
  fVar20 = *(float *)(param_5 + 0x80);
  auVar8._0_4_ = *param_7 * fVar20;
  auVar8._4_4_ = param_7[1] * fVar20;
  auVar8._8_4_ = param_7[2] * fVar20;
  auVar8._12_4_ = param_7[3] * fVar20;
  auVar10 = NEON_frecpe(auVar8,4);
  auVar19 = NEON_frecps(auVar10,auVar8,4);
  auVar11._0_4_ = auVar10._0_4_ * auVar19._0_4_;
  auVar11._4_4_ = auVar10._4_4_ * auVar19._4_4_;
  auVar11._8_4_ = auVar10._8_4_ * auVar19._8_4_;
  auVar11._12_4_ = auVar10._12_4_ * auVar19._12_4_;
  auVar10 = NEON_frecps(auVar11,auVar8,4);
  auVar21._0_8_ =
       CONCAT44((auVar22._0_4_ + auVar18._0_4_ + auVar22._4_4_ + auVar18._4_4_) *
                auVar11._4_4_ * auVar10._4_4_ * fVar20,
                (auVar21._0_4_ + fVar12 + auVar21._4_4_ + fVar14) *
                auVar11._0_4_ * auVar10._0_4_ * fVar20);
  auVar21._8_4_ =
       (auVar23._0_4_ + auVar9._0_4_ + auVar23._4_4_ + auVar9._4_4_) *
       auVar11._8_4_ * auVar10._8_4_ * fVar20;
  auVar21._12_4_ = auVar11._12_4_ * auVar10._12_4_ * fVar20 * 1.0;
  uStack_b8 = auVar21._8_8_;
  uStack_c0 = auVar21._0_8_;
  Aska::Box::SquaredDistance(Aska::Segment const*, float*, float*, float*, float*) const(&uStack_c0,param_5 + 0x40,&fStack_c4,&fStack_c8,&fStack_cc,&fStack_d0);
  fVar13 = _UNK_027e519c;
  uVar2 = 0;
  fVar7 = (float)extraout_d0;
  if (fVar20 * fVar20 < fVar7) {
    return 0;
  }
  if (_UNK_027e519c <= fVar7) {
    fVar17 = (*(float *)(param_5 + 0x50) * fStack_c4 + *(float *)(param_5 + 0x40)) -
             (*(float *)(param_1 + 0x20) + fStack_c8 * *(float *)(param_1 + 0x40) +
              fStack_cc * *(float *)(param_1 + 0x50) + fStack_d0 * *(float *)(param_1 + 0x60));
    fVar12 = ((float)*(undefined8 *)(param_5 + 0x54) * fStack_c4 +
             (float)*(undefined8 *)(param_5 + 0x44)) -
             ((float)*(undefined8 *)(param_1 + 0x24) +
              (float)*(undefined8 *)(param_1 + 0x44) * fStack_c8 +
              (float)*(undefined8 *)(param_1 + 0x54) * fStack_cc +
             (float)*(undefined8 *)(param_1 + 100) * fStack_d0);
    fVar14 = ((float)((ulong)*(undefined8 *)(param_5 + 0x54) >> 0x20) * fStack_c4 +
             (float)((ulong)*(undefined8 *)(param_5 + 0x44) >> 0x20)) -
             ((float)((ulong)*(undefined8 *)(param_1 + 0x24) >> 0x20) +
              (float)((ulong)*(undefined8 *)(param_1 + 0x44) >> 0x20) * fStack_c8 +
              (float)((ulong)*(undefined8 *)(param_1 + 0x54) >> 0x20) * fStack_cc +
             (float)((ulong)*(undefined8 *)(param_1 + 100) >> 0x20) * fStack_d0);
    *param_8 = fVar17;
    *(ulong *)(param_8 + 1) = CONCAT44(fVar14,fVar12);
    fVar12 = fVar17 * fVar17 + fVar12 * fVar12 + fVar14 * fVar14;
    fVar17 = SQRT(fVar12);
    param_8[3] = 1.0;
    uVar24 = extraout_var;
    if (NAN(fVar17)) {
      uVar2 = sqrtf(fVar12,0);
      fVar17 = extraout_s0;
    }
    if (fVar13 <= fVar17) {
      fVar17 = 1.0 / fVar17;
      *param_8 = fVar17 * *param_8;
      param_8[1] = fVar17 * param_8[1];
      param_8[2] = fVar17 * param_8[2];
    }
    fVar7 = SQRT(fVar7);
    *param_9 = fStack_c4;
    if (NAN(fVar7)) {
      auVar22._8_8_ = uVar24;
      auVar22._0_8_ = extraout_d0;
      fVar7 = (float)sqrtf(auVar22,uVar2);
    }
    fVar20 = fVar20 - fVar7;
  }
  else {
    if ((param_6 & 1) == 0) {
      fVar7 = -1.0;
      fVar13 = fStack_c8;
      if (0.0 <= fStack_c8) {
        fVar13 = -fStack_c8;
      }
      fVar17 = -1.0;
      if (0.0 <= fStack_c8) {
        fVar17 = 1.0;
      }
      fVar12 = fStack_cc;
      if (0.0 <= fStack_cc) {
        fVar12 = -fStack_cc;
      }
      fStack_c8 = *(float *)(param_1 + 0x30) + fVar13;
      fVar13 = -1.0;
      if (0.0 <= fStack_cc) {
        fVar13 = 1.0;
      }
      fStack_cc = *(float *)(param_1 + 0x34) + fVar12;
      if (0.0 <= fStack_d0) {
        fStack_d0 = *(float *)(param_1 + 0x38) - fStack_d0;
        fVar7 = 1.0;
      }
      else {
        fStack_d0 = fStack_d0 + *(float *)(param_1 + 0x38);
      }
    }
    else {
      fVar13 = -1.0;
      if (0.0 <= *(float *)(param_5 + 0x50)) {
        fVar13 = 1.0;
      }
      fVar7 = -1.0;
      if (0.0 <= *(float *)(param_5 + 0x54)) {
        fVar7 = 1.0;
      }
      fVar12 = -1.0;
      if (0.0 <= *(float *)(param_5 + 0x58)) {
        fVar12 = 1.0;
      }
      bVar1 = 0.0 <= fVar13 * fStack_c8;
      if (bVar1) {
        fStack_c8 = -fStack_c8;
      }
      fVar17 = -1.0;
      if (bVar1) {
        fVar17 = 1.0;
      }
      bVar1 = 0.0 <= fVar7 * fStack_cc;
      fStack_c8 = *(float *)(param_1 + 0x30) + fStack_c8;
      if (bVar1) {
        fStack_cc = -fStack_cc;
      }
      fVar13 = -1.0;
      if (bVar1) {
        fVar13 = 1.0;
      }
      fStack_cc = *(float *)(param_1 + 0x34) + fStack_cc;
      fVar7 = -1.0;
      if (0.0 <= fVar12 * fStack_d0) {
        fVar7 = 1.0;
        fStack_d0 = -fStack_d0;
      }
      fStack_d0 = *(float *)(param_1 + 0x38) + fStack_d0;
    }
    iVar3 = 2;
    if (fStack_cc <= fStack_d0) {
      iVar3 = 1;
    }
    if (fStack_c8 <= fStack_cc) {
      iVar3 = (uint)(fStack_d0 < fStack_c8) << 1;
    }
    pfVar4 = (float *)(param_1 + 0x60);
    pfVar5 = (float *)(param_1 + 100);
    pfVar6 = (float *)(param_1 + 0x68);
    if (((iVar3 != 2) &&
        (pfVar4 = (float *)(param_1 + 0x50), pfVar5 = (float *)(param_1 + 0x54),
        pfVar6 = (float *)(param_1 + 0x58), fVar7 = fVar13, fStack_d0 = fStack_cc, iVar3 != 1)) &&
       (pfVar4 = (float *)(param_1 + 0x40), pfVar5 = (float *)(param_1 + 0x44),
       pfVar6 = (float *)(param_1 + 0x48), fVar7 = fVar17, fStack_d0 = fStack_c8, iVar3 != 0)) {
      return 1;
    }
    fVar13 = *pfVar4;
    fVar17 = *pfVar5;
    fVar12 = *pfVar6;
    param_8[3] = 1.0;
    *param_8 = fVar7 * fVar13;
    param_8[1] = fVar7 * fVar17;
    param_8[2] = fVar7 * fVar12;
    fVar20 = fVar20 + fStack_d0;
    *param_9 = fStack_c4;
  }
  *param_10 = fVar20;
  return 1;
}

// ==== Aska::DYNAMICS_CUBE::TestIntersectionSphere(Aska::Vector const*, float, Aska::Vector*)
// vaddr 0x20a26b8 | ghidra 0x21a26b8 | size 456 | symbol _ZN4Aska13DYNAMICS_CUBE22TestIntersectionSphereEPKNS_6VectorEfPS1_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska13DYNAMICS_CUBE22TestIntersectionSphereEPKNS_6VectorEfPS1_
          (float param_1,long param_2,undefined8 param_3,float *param_4)

{
  bool bVar1;
  undefined8 uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  
  Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const(param_3,&fStack_30,param_2 + 0xb0);
  uVar2 = 0;
  if ((-*(float *)(param_2 + 0x30) <= fStack_30 + param_1) &&
     (fStack_30 - param_1 <= *(float *)(param_2 + 0x30))) {
    uVar2 = 0;
    if ((-*(float *)(param_2 + 0x34) <= fStack_2c + param_1) &&
       (fStack_2c - param_1 <= *(float *)(param_2 + 0x34))) {
      uVar2 = 0;
      if ((-*(float *)(param_2 + 0x38) <= fStack_28 + param_1) &&
         (fStack_28 - param_1 <= *(float *)(param_2 + 0x38))) {
        fVar4 = fStack_30 * fStack_30 + fStack_2c * fStack_2c + fStack_28 * fStack_28;
        fVar3 = SQRT(fVar4);
        if (NAN(fVar3)) {
          fVar3 = (float)sqrtf(fVar4,0);
        }
        if (_UNK_027e519c <= fVar3) {
          fVar3 = 1.0 / fVar3;
          fStack_30 = fVar3 * fStack_30;
          fStack_2c = fVar3 * fStack_2c;
          fStack_28 = fVar3 * fStack_28;
        }
        fVar3 = _UNK_027ebde8;
        if (fStack_30 != 0.0) {
          fVar3 = ABS((*(float *)(param_2 + 0x30) + param_1) / fStack_30);
        }
        fVar4 = _UNK_027ebde8;
        if (fStack_2c != 0.0) {
          fVar4 = ABS((*(float *)(param_2 + 0x34) + param_1) / fStack_2c);
        }
        fVar5 = _UNK_027ebde8;
        if (fStack_28 != 0.0) {
          fVar5 = ABS((*(float *)(param_2 + 0x38) + param_1) / fStack_28);
        }
        fVar6 = fVar4;
        if (fVar5 <= fVar4) {
          fVar6 = fVar5;
        }
        bVar1 = false;
        if ((fVar3 < fVar5) && (bVar1 = false, !NAN(fVar3) && !NAN(fVar4))) {
          bVar1 = fVar3 < fVar4;
        }
        if (!bVar1) {
          fVar3 = fVar6;
        }
        *param_4 = fStack_30 * fVar3;
        param_4[1] = fStack_2c * fVar3;
        param_4[2] = fVar3 * fStack_28;
        param_4[3] = fStack_24;
        Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const(param_4,param_4,param_2 + 0x70);
        uVar2 = 1;
      }
    }
  }
  return uVar2;
}

// ==== Aska::DYNAMICS_CUBE::TestIntersection(Aska::Vector const*, float, Aska::Vector*)
// vaddr 0x20a2880 | ghidra 0x21a2880 | size 288 | symbol _ZN4Aska13DYNAMICS_CUBE16TestIntersectionEPKNS_6VectorEfPS1_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska13DYNAMICS_CUBE16TestIntersectionEPKNS_6VectorEfPS1_
          (float param_1,long param_2,undefined8 param_3,float *param_4)

{
  bool bVar1;
  float fVar2;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  
  Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const(param_3,&fStack_30,param_2 + 0xb0);
  *param_4 = fStack_30;
  param_4[1] = fStack_2c;
  param_4[2] = fStack_28;
  param_4[3] = fStack_24;
  fVar2 = *(float *)(param_2 + 0x30);
  if (-fVar2 <= fStack_30 - param_1) {
    if (fVar2 < fStack_30 + param_1) {
      fVar2 = fVar2 - param_1;
      goto code_r0x021a28f4;
    }
    bVar1 = false;
  }
  else {
    fVar2 = param_1 - fVar2;
code_r0x021a28f4:
    bVar1 = true;
    *param_4 = fVar2;
  }
  fVar2 = *(float *)(param_2 + 0x34);
  if (-fVar2 <= fStack_2c - param_1) {
    if (fVar2 < fStack_2c + param_1) {
      fVar2 = fVar2 - param_1;
      goto code_r0x021a2934;
    }
  }
  else {
    fVar2 = param_1 - fVar2;
code_r0x021a2934:
    bVar1 = true;
    param_4[1] = fVar2;
  }
  fVar2 = *(float *)(param_2 + 0x38);
  if (-fVar2 <= fStack_28 - param_1) {
    if (fStack_28 + param_1 <= fVar2) {
      if (!bVar1) {
        return 0;
      }
      goto code_r0x021a296c;
    }
    param_1 = fVar2 - param_1;
  }
  else {
    param_1 = param_1 - fVar2;
  }
  param_4[2] = param_1;
code_r0x021a296c:
  Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const(param_4,param_4,param_2 + 0x70);
  return 1;
}

// ==== Aska::DYNAMICS_SPHERE::TestIntersectionLocal(__Float32x4_t&, __Float32x4_t&, __Float32x4_t&, Aska::DYNAMICS_CAPSULE*, bool, Aska::Vector const*, Aska::Vector*, float*, float*)
// vaddr 0x20a29a0 | ghidra 0x21a29a0 | size 468 | symbol _ZN4Aska15DYNAMICS_SPHERE21TestIntersectionLocalER13__Float32x4_tS2_S2_PNS_16DYNAMICS_CAPSULEEbPKNS_6VectorEPS5_PfS9_ | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska15DYNAMICS_SPHERE21TestIntersectionLocalER13__Float32x4_tS2_S2_PNS_16DYNAMICS_CAPSULEEbPKNS_6VectorEPS5_PfS9_
          (long param_1,undefined8 *param_2,undefined8 *param_3,float *param_4,long param_5,
          undefined8 param_6,float *param_7,float *param_8,float *param_9,float *param_10)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined8 uVar4;
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
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  undefined4 uStack_44;
  float fStack_34;
  
  fVar12 = (float)*(undefined8 *)(param_1 + 0x38);
  fVar16 = (float)((ulong)*(undefined8 *)(param_1 + 0x38) >> 0x20);
  fVar5 = (float)*(undefined8 *)(param_1 + 0x30);
  fVar6 = (float)((ulong)*(undefined8 *)(param_1 + 0x30) >> 0x20);
  fVar7 = fVar5 * (float)*param_2;
  fVar8 = fVar6 * (float)((ulong)*param_2 >> 0x20);
  fVar9 = fVar12 * (float)param_2[1];
  fVar10 = fVar16 * (float)((ulong)param_2[1] >> 0x20);
  fVar11 = fVar5 * (float)*param_3;
  fVar13 = fVar6 * (float)((ulong)*param_3 >> 0x20);
  fVar14 = fVar12 * (float)param_3[1];
  fVar15 = fVar16 * (float)((ulong)param_3[1] >> 0x20);
  fVar5 = fVar5 * *param_4;
  fVar6 = fVar6 * param_4[1];
  auVar17._4_4_ = fVar8;
  auVar17._0_4_ = fVar7;
  auVar17._8_4_ = fVar9;
  auVar17._12_4_ = fVar10;
  auVar19._4_4_ = fVar8;
  auVar19._0_4_ = fVar7;
  auVar19._8_4_ = fVar9;
  auVar19._12_4_ = fVar10;
  auVar17 = NEON_ext(auVar17,auVar19,8,1);
  auVar2._4_4_ = fVar13;
  auVar2._0_4_ = fVar11;
  auVar2._8_4_ = fVar14;
  auVar2._12_4_ = fVar15;
  auVar3._4_4_ = fVar13;
  auVar3._0_4_ = fVar11;
  auVar3._8_4_ = fVar14;
  auVar3._12_4_ = fVar15;
  auVar19 = NEON_ext(auVar2,auVar3,8,1);
  auVar18._4_4_ = fVar6;
  auVar18._0_4_ = fVar5;
  auVar18._8_4_ = fVar12 * param_4[2];
  auVar18._12_4_ = fVar16 * param_4[3];
  auVar1._4_4_ = fVar6;
  auVar1._0_4_ = fVar5;
  auVar1._8_4_ = fVar12 * param_4[2];
  auVar1._12_4_ = fVar16 * param_4[3];
  auVar18 = NEON_ext(auVar18,auVar1,8,1);
  uStack_44 = 0x3f800000;
  fVar12 = *(float *)(param_5 + 0x80);
  fVar16 = *(float *)(param_1 + 0x20);
  fVar9 = fVar12 + fVar16;
  fStack_50 = (fVar9 / (fVar16 + fVar12 * *param_7)) *
              (auVar17._0_4_ + fVar7 + auVar17._4_4_ + fVar8);
  fStack_4c = (fVar9 / (fVar12 * param_7[1] + fVar16)) *
              (auVar19._0_4_ + fVar11 + auVar19._4_4_ + fVar13);
  fStack_48 = (fVar9 / (fVar12 * param_7[2] + fVar16)) *
              (auVar18._0_4_ + fVar5 + auVar18._4_4_ + fVar6);
  fVar5 = (float)Aska::Segment::SquaredDistance(Aska::Vector const*, float*) const(param_5 + 0x40,&fStack_50,&fStack_34);
  fVar6 = *(float *)(param_1 + 0x20) + *(float *)(param_5 + 0x80);
  if (fVar5 <= fVar6 * fVar6) {
    fVar7 = (*(float *)(param_5 + 0x40) + fStack_34 * *(float *)(param_5 + 0x50)) - fStack_50;
    fVar12 = ((float)*(undefined8 *)(param_5 + 0x44) +
             (float)*(undefined8 *)(param_5 + 0x54) * fStack_34) - fStack_4c;
    fVar16 = ((float)((ulong)*(undefined8 *)(param_5 + 0x44) >> 0x20) +
             (float)((ulong)*(undefined8 *)(param_5 + 0x54) >> 0x20) * fStack_34) - fStack_48;
    *param_8 = fVar7;
    *(ulong *)(param_8 + 1) = CONCAT44(fVar16,fVar12);
    fVar16 = fVar7 * fVar7 + fVar12 * fVar12 + fVar16 * fVar16;
    fVar12 = SQRT(fVar16);
    param_8[3] = 1.0;
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar16);
    }
    if (_UNK_027e519c <= fVar12) {
      fVar12 = 1.0 / fVar12;
      *param_8 = fVar12 * *param_8;
      param_8[1] = fVar12 * param_8[1];
      param_8[2] = fVar12 * param_8[2];
    }
    fVar12 = SQRT(fVar5);
    *param_9 = fStack_34;
    if (NAN(fVar12)) {
      fVar12 = (float)sqrtf(fVar5);
    }
    uVar4 = 1;
    *param_10 = fVar6 - fVar12;
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}

// ==== Aska::DYNAMICS_SQUARE::TestIntersection(Aska::Vector const*, float, Aska::Vector*)
// vaddr 0x20a2b74 | ghidra 0x21a2b74 | size 272 | symbol _ZN4Aska15DYNAMICS_SQUARE16TestIntersectionEPKNS_6VectorEfPS1_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska15DYNAMICS_SQUARE16TestIntersectionEPKNS_6VectorEfPS1_
          (float param_1,long param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float afStack_40 [2];
  float fStack_38;
  
  fVar7 = (*param_3 - *(float *)(param_2 + 0x70)) * *(float *)(param_2 + 0x60) +
          ((float)*(undefined8 *)(param_3 + 1) - (float)*(undefined8 *)(param_2 + 0x74)) *
          (float)*(undefined8 *)(param_2 + 100) +
          ((float)((ulong)*(undefined8 *)(param_3 + 1) >> 0x20) -
          (float)((ulong)*(undefined8 *)(param_2 + 0x74) >> 0x20)) *
          (float)((ulong)*(undefined8 *)(param_2 + 100) >> 0x20);
  if (fVar7 <= param_1) {
    Aska::Vector::ApplyMatrix(Aska::Vector*, Aska::Matrix const*) const(param_3,afStack_40,param_2 + 0x20);
    if ((((-*(float *)(param_2 + 0xa0) <= afStack_40[0] - param_1) &&
         (afStack_40[0] + param_1 <= *(float *)(param_2 + 0xa0))) &&
        (-*(float *)(param_2 + 0xa4) <= fStack_38 - param_1)) &&
       (fStack_38 + param_1 <= *(float *)(param_2 + 0xa4))) {
      fVar1 = *(float *)(param_2 + 0x60);
      fVar2 = *(float *)(param_2 + 100);
      fVar3 = *(float *)(param_2 + 0x68);
      fVar7 = fVar7 - param_1;
      fVar5 = *param_3;
      fVar6 = param_3[1];
      fVar4 = param_3[2];
      param_4[3] = param_3[3];
      *param_4 = fVar5 - fVar7 * fVar1;
      param_4[1] = fVar6 - fVar7 * fVar2;
      param_4[2] = fVar4 - fVar7 * fVar3;
      return 1;
    }
  }
  return 0;
}

// ==== Aska::DynamicsPrimitiveList::~DynamicsPrimitiveList()
// vaddr 0x20e5d2c | ghidra 0x21e5d2c | size 116 | symbol _ZN4Aska21DynamicsPrimitiveListD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21DynamicsPrimitiveListD0Ev(long *param_1)

{
  undefined *puVar1;
  int iVar2;
  long *plVar3;
  
  plVar3 = (long *)param_1[8];
  puVar1 = PTR__ZTVN4Aska5TListINS_24DynamicsPrimitiveElementEEE_02cbed28 + 0x10;
  param_1[1] = (long)(PTR__ZTVN4Aska24DynamicsPrimitiveElementE_02cbbef0 + 0x10);
  *param_1 = (long)puVar1;
  if (plVar3 != (long *)0x0) {
    iVar2 = (int)plVar3[5] + -1;
    *(int *)(plVar3 + 5) = iVar2;
    if (iVar2 == 0) {
      (**(code **)(*plVar3 + 8))();
    }
    param_1[8] = 0;
  }
  Aska::DynamicsHandler::~DynamicsHandler()(param_1 + 1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}
