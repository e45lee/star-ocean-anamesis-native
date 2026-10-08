// port/decomp/particles/object.c: Ghidra decompiles for the particles subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 13:22 UTC: tools/decomp.sh '--into' 'particles/object' 'Aska::IParticleObject::'

// ==== Aska::IParticleObject::operator new(unsigned long)
// vaddr 0x1f4ed94 | ghidra 0x204ed94 | size 80 | symbol _ZN4Aska15IParticleObjectnwEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObjectnwEm(undefined8 param_1)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  long *plVar4;
  int extraout_w1;
  int extraout_w1_00;
  int extraout_w1_01;
  int extraout_w1_02;
  
  lVar2 = Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)(param_1,0x10,1);
  if (lVar2 != 0) {
    return;
  }
  uVar3 = __cxa_allocate_exception(8);
  std::bad_alloc::bad_alloc()();
  __cxa_throw(uVar3,PTR__ZTISt9bad_alloc_02cb8ab8,PTR__ZNSt20bad_array_new_lengthD2Ev_02cb7060);
  if (extraout_w1 < 0) {
    __cxa_call_unexpected();
  }
  uVar3 = _Unwind_Resume();
  lVar2 = Aska::IParticleObject::operator new[](unsigned long, unsigned long, bool)(uVar3,0x10,1);
  if (lVar2 != 0) {
    return;
  }
  uVar3 = __cxa_allocate_exception(8);
  std::bad_alloc::bad_alloc()();
  __cxa_throw(uVar3,PTR__ZTISt9bad_alloc_02cb8ab8,PTR__ZNSt20bad_array_new_lengthD2Ev_02cb7060);
  if (extraout_w1_00 < 0) {
    __cxa_call_unexpected();
  }
  uVar3 = _Unwind_Resume();
  lVar2 = Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(uVar3,0x10,1);
  if (lVar2 != 0) {
    return;
  }
  uVar3 = __cxa_allocate_exception(8);
  std::bad_alloc::bad_alloc()();
  __cxa_throw(uVar3,PTR__ZTISt9bad_alloc_02cb8ab8,PTR__ZNSt20bad_array_new_lengthD2Ev_02cb7060);
  if (extraout_w1_01 < 0) {
    __cxa_call_unexpected();
  }
  uVar3 = _Unwind_Resume();
  lVar2 = Aska::IParticleEmitter::operator new[](unsigned long, unsigned long, bool)(uVar3,0x10,1);
  if (lVar2 != 0) {
    return;
  }
  uVar3 = __cxa_allocate_exception(8);
  std::bad_alloc::bad_alloc()();
  __cxa_throw(uVar3,PTR__ZTISt9bad_alloc_02cb8ab8,PTR__ZNSt20bad_array_new_lengthD2Ev_02cb7060);
  if (extraout_w1_02 < 0) {
    __cxa_call_unexpected();
  }
  plVar4 = (long *)_Unwind_Resume();
  puVar1 = 
  PTR__ZTVN4Aska13TDynamicArrayINS_6detail9SmallHeap8HeapInfoENS_10TAllocatorIS3_EEEE_02cc4218;
  plVar4[2] = 0;
  plVar4[3] = 0;
  plVar4[5] = 0;
  *plVar4 = (long)(puVar1 + 0x10);
  plVar4[1] = 0;
  return;
}

// ==== Aska::IParticleObject::operator new[](unsigned long)
// vaddr 0x1f4ede4 | ghidra 0x204ede4 | size 80 | symbol _ZN4Aska15IParticleObjectnaEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObjectnaEm(undefined8 param_1)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  long *plVar4;
  int extraout_w1;
  int extraout_w1_00;
  int extraout_w1_01;
  
  lVar2 = Aska::IParticleObject::operator new[](unsigned long, unsigned long, bool)(param_1,0x10,1);
  if (lVar2 != 0) {
    return;
  }
  uVar3 = __cxa_allocate_exception(8);
  std::bad_alloc::bad_alloc()();
  __cxa_throw(uVar3,PTR__ZTISt9bad_alloc_02cb8ab8,PTR__ZNSt20bad_array_new_lengthD2Ev_02cb7060);
  if (extraout_w1 < 0) {
    __cxa_call_unexpected();
  }
  uVar3 = _Unwind_Resume();
  lVar2 = Aska::IParticleEmitter::operator new(unsigned long, unsigned long, bool)(uVar3,0x10,1);
  if (lVar2 != 0) {
    return;
  }
  uVar3 = __cxa_allocate_exception(8);
  std::bad_alloc::bad_alloc()();
  __cxa_throw(uVar3,PTR__ZTISt9bad_alloc_02cb8ab8,PTR__ZNSt20bad_array_new_lengthD2Ev_02cb7060);
  if (extraout_w1_00 < 0) {
    __cxa_call_unexpected();
  }
  uVar3 = _Unwind_Resume();
  lVar2 = Aska::IParticleEmitter::operator new[](unsigned long, unsigned long, bool)(uVar3,0x10,1);
  if (lVar2 != 0) {
    return;
  }
  uVar3 = __cxa_allocate_exception(8);
  std::bad_alloc::bad_alloc()();
  __cxa_throw(uVar3,PTR__ZTISt9bad_alloc_02cb8ab8,PTR__ZNSt20bad_array_new_lengthD2Ev_02cb7060);
  if (extraout_w1_01 < 0) {
    __cxa_call_unexpected();
  }
  plVar4 = (long *)_Unwind_Resume();
  puVar1 = 
  PTR__ZTVN4Aska13TDynamicArrayINS_6detail9SmallHeap8HeapInfoENS_10TAllocatorIS3_EEEE_02cc4218;
  plVar4[2] = 0;
  plVar4[3] = 0;
  plVar4[5] = 0;
  *plVar4 = (long)(puVar1 + 0x10);
  plVar4[1] = 0;
  return;
}

// ==== Aska::IParticleObject::Prepare()
// vaddr 0x219d238 | ghidra 0x229d238 | size 160 | symbol _ZN4Aska15IParticleObject7PrepareEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObject7PrepareEv(long param_1)

{
  int iVar1;
  uint3 uVar2;
  
  uVar2 = *(uint3 *)(param_1 + 500);
  if ((uVar2 & 0x2000) != 0) {
    iVar1 = *(int *)(*(long *)(param_1 + 0x1e0) + -4);
    if (iVar1 != 0) {
      memset(*(long *)(param_1 + 0x1e0),0,(ulong)(iVar1 - 1) * 4 + 4);
      uVar2 = *(uint3 *)(param_1 + 500);
    }
    *(char *)(param_1 + 0x1f6) = (char)(uVar2 >> 0x10);
    *(ushort *)(param_1 + 500) = (ushort)uVar2 & 0xdfff;
  }
  if (((*(float *)(param_1 + 0x174) == 0.0) && (*(long *)(param_1 + 0x140) != 0)) &&
     (*(long *)(*(long *)(param_1 + 0x140) + 0x10) != 0)) {
    (*(code *)PTR__ZN4Aska15IParticleObject17CalcAnimationSizeEii_02ca5e00)
              (param_1,*(undefined2 *)(param_1 + 0x10c),*(undefined2 *)(param_1 + 0x10e));
    return;
  }
  return;
}

// ==== Aska::IParticleObject::Reset()
// vaddr 0x219d2d8 | ghidra 0x229d2d8 | size 20 | symbol _ZN4Aska15IParticleObject5ResetEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObject5ResetEv(long param_1)

{
  *(undefined4 *)(param_1 + 0x1f0) = 0;
  *(ushort *)(param_1 + 500) = *(ushort *)(param_1 + 500) | 0x2000;
  return;
}

// ==== Aska::IParticleObject::BeginParticles()
// vaddr 0x219d2ec | ghidra 0x229d2ec | size 24 | symbol _ZN4Aska15IParticleObject14BeginParticlesEv | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska15IParticleObject14BeginParticlesEv(long param_1)

{
  *(undefined4 *)(param_1 + 0x1d8) = 0;
  return 0 < *(int *)(param_1 + 0x1e8);
}

// ==== Aska::IParticleObject::IParticleObject(unsigned int, unsigned int, unsigned int)
// vaddr 0x21a12e0 | ghidra 0x22a12e0 | size 328 | symbol _ZN4Aska15IParticleObjectC1Ejjj | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15IParticleObjectC2Ejjj
               (long *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  undefined *puVar7;
  long lVar8;
  undefined1 auVar9 [16];
  long lVar10;
  
  puVar7 = PTR__ZTVN4Aska15IParticleObjectE_02cb6eb0;
  lVar10 = _UNK_027f7c68;
  lVar8 = _UNK_027f7c60;
  param_1[0x1e] = 0x3f8000003a83126f;
  lVar6 = _UNK_027dbb28;
  lVar5 = _UNK_027dbb20;
  lVar4 = _UNK_027dbb18;
  lVar3 = _UNK_027dbb10;
  lVar2 = _UNK_027dbb08;
  lVar1 = _UNK_027dbb00;
  *param_1 = (long)(puVar7 + 0x10);
  *(undefined4 *)(param_1 + 0x21) = 0;
  param_1[0x22] = 0;
  *(undefined4 *)((long)param_1 + 0x10c) = 0x10001;
  *(undefined4 *)(param_1 + 0x26) = 0;
  param_1[0x20] = 0;
  param_1[0x1f] = 0;
  *(undefined4 *)(param_1 + 0x23) = 1;
  param_1[0x25] = 0;
  param_1[0x24] = 0;
  param_1[0x1d] = lVar10;
  param_1[0x1c] = lVar8;
  *(undefined8 *)((long)param_1 + 0x134) = 0x3f800000;
  param_1[0x2e] = 0;
  param_1[0x2f] = 0x43fa00003f800000;
  *(undefined4 *)(param_1 + 0x30) = 0x449c4000;
  *(undefined4 *)((long)param_1 + 0x184) = 0x459c4000;
  *(undefined4 *)(param_1 + 0x31) = 0x3f800000;
  *(undefined4 *)((long)param_1 + 0x18c) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x35) = param_2;
  *(undefined2 *)((long)param_1 + 0x1ac) = 0xc;
  *(undefined1 *)((long)param_1 + 0x1af) = 2;
  param_1[0x2b] = 0;
  param_1[0x2a] = 0;
  param_1[0x2d] = 0;
  param_1[0x2c] = 0;
  param_1[0x29] = 0;
  param_1[0x28] = 0;
  param_1[0x34] = 0;
  param_1[0x33] = 0;
  param_1[0x32] = 0;
  *(undefined1 *)((long)param_1 + 0x1ae) = 1;
  *(undefined1 *)(param_1 + 0x36) = 0;
  *(undefined1 *)((long)param_1 + 0x1b1) = 1;
  *(undefined2 *)((long)param_1 + 0x1b2) = 0;
  param_1[0x38] = 0;
  param_1[0x37] = 0;
  auVar9 = NEON_fmov(0x3f800000,4);
  lVar10 = auVar9._8_8_;
  param_1[0x17] = lVar10;
  lVar8 = auVar9._0_8_;
  param_1[0x16] = lVar8;
  param_1[0x19] = lVar10;
  param_1[0x18] = lVar8;
  param_1[0x1b] = lVar10;
  param_1[0x1a] = lVar8;
  lVar10 = _UNK_027dbb38;
  lVar8 = _UNK_027dbb30;
  *(undefined4 *)(param_1 + 0x39) = param_3;
  *(undefined4 *)((long)param_1 + 0x1cc) = param_4;
  *(undefined4 *)(param_1 + 0x3e) = 0;
  param_1[0x3b] = 0;
  param_1[0x3a] = 0;
  param_1[0x3d] = 0;
  param_1[0x3c] = 0;
  *(undefined2 *)((long)param_1 + 500) = 0;
  *(undefined1 *)((long)param_1 + 0x1f7) = 0;
  *(undefined1 *)(param_1 + 0x3f) = 0;
  param_1[0x140] = 0;
  *(undefined1 *)(param_1 + 0x141) = 0;
  param_1[3] = lVar2;
  param_1[2] = lVar1;
  param_1[5] = lVar4;
  param_1[4] = lVar3;
  param_1[7] = lVar6;
  param_1[6] = lVar5;
  param_1[9] = lVar10;
  param_1[8] = lVar8;
  param_1[0xb] = lVar2;
  param_1[10] = lVar1;
  param_1[0xd] = lVar4;
  param_1[0xc] = lVar3;
  param_1[0xf] = lVar6;
  param_1[0xe] = lVar5;
  param_1[0x11] = lVar10;
  param_1[0x10] = lVar8;
  *(byte *)((long)param_1 + 0x1f6) =
       (byte)(((uint)(*(byte *)((long)param_1 + 0x1f6) >> 4) << 0x14) >> 0x10) | 2;
  param_1[0x13] = 0;
  param_1[0x12] = 0;
  param_1[0x15] = 0;
  param_1[0x14] = 0;
  return;
}

// ==== Aska::IParticleObject::~IParticleObject()
// vaddr 0x21a1428 | ghidra 0x22a1428 | size 140 | symbol _ZN4Aska15IParticleObjectD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObjectD2Ev(long *param_1)

{
  long lVar1;
  
  lVar1 = param_1[0x33];
  *param_1 = (long)(PTR__ZTVN4Aska15IParticleObjectE_02cb6eb0 + 0x10);
  if (lVar1 != 0) {
    Aska::ParticleDynamicsContext::~ParticleDynamicsContext()(lVar1);
    operator delete(void*)(lVar1);
    param_1[0x33] = 0;
  }
  if (param_1[0x34] != 0) {
    operator delete(void*)();
    param_1[0x34] = 0;
  }
  if (param_1[0x37] != 0) {
    Aska::ParticleManager::Free(void*)();
    param_1[0x37] = 0;
  }
  if (param_1[0x38] != 0) {
    Aska::ParticleManager::Free(void*)();
    param_1[0x38] = 0;
  }
  if (param_1[0x3c] != 0) {
    param_1[0x3c] = param_1[0x3c] + -4;
    operator delete[](void*)();
    param_1[0x3c] = 0;
  }
  return;
}

// ==== Aska::IParticleObject::Free()
// vaddr 0x21a15bc | ghidra 0x22a15bc | size 48 | symbol _ZN4Aska15IParticleObject4FreeEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObject4FreeEv(long param_1)

{
  if (*(long *)(param_1 + 0x1b8) != 0) {
    Aska::ParticleManager::Free(void*)();
    *(undefined8 *)(param_1 + 0x1b8) = 0;
  }
  if (*(long *)(param_1 + 0x1c0) != 0) {
    Aska::ParticleManager::Free(void*)();
    *(undefined8 *)(param_1 + 0x1c0) = 0;
  }
  return;
}

// ==== Aska::IParticleObject::~IParticleObject()
// vaddr 0x21a15ec | ghidra 0x22a15ec | size 64 | symbol _ZN4Aska15IParticleObjectD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObjectD0Ev(long param_1)

{
  Aska::IParticleObject::~IParticleObject()();
  if (param_1 == 0) {
    return;
  }
  if (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPv_02cb5c60)
              (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838,param_1);
    return;
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::IParticleObject::operator delete(void*)
// vaddr 0x21a162c | ghidra 0x22a162c | size 44 | symbol _ZN4Aska15IParticleObjectdlEPv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObjectdlEPv(long param_1)

{
  if (param_1 == 0) {
    return;
  }
  if (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPv_02cb5c60)
              (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838,param_1);
    return;
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::IParticleObject::Attach(Aska::AFF::AsfParticleEmitter const*)
// vaddr 0x21a1658 | ghidra 0x22a1658 | size 668 | symbol _ZN4Aska15IParticleObject6AttachEPKNS_3AFF18AsfParticleEmitterE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Type propagation algorithm not settling */

void _ZN4Aska15IParticleObject6AttachEPKNS_3AFF18AsfParticleEmitterE(long param_1,long param_2)

{
  long lVar1;
  byte bVar2;
  ushort uVar3;
  char cVar4;
  
  *(undefined8 *)(param_1 + 0x110) = *(undefined8 *)(param_2 + 400);
  *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(param_2 + 0x214);
  *(undefined4 *)(param_1 + 0xe4) = *(undefined4 *)(param_2 + 0x218);
  *(undefined4 *)(param_1 + 0xe8) = *(undefined4 *)(param_2 + 0x210);
  *(undefined4 *)(param_1 + 0xec) = *(undefined4 *)(param_2 + 0x21c);
  *(undefined4 *)(param_1 + 0xf0) = *(undefined4 *)(param_2 + 0x224);
  *(undefined4 *)(param_1 + 0xf4) = *(undefined4 *)(param_2 + 600);
  *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(param_2 + 0x240);
  *(undefined4 *)(param_1 + 0xfc) = *(undefined4 *)(param_2 + 0x244);
  *(undefined4 *)(param_1 + 0x100) = *(undefined4 *)(param_2 + 0x248);
  *(undefined4 *)(param_1 + 0x104) = *(undefined4 *)(param_2 + 0x274);
  *(undefined4 *)(param_1 + 0x108) = *(undefined4 *)(param_2 + 0x27c);
  *(undefined1 *)(param_1 + 0x1f8) = *(undefined1 *)(param_2 + 0x1de);
  *(undefined1 *)(param_1 + 0x1f7) = *(undefined1 *)(param_2 + 0x1df);
  *(undefined2 *)(param_1 + 0x1ac) = *(undefined2 *)(param_2 + 0x1c4);
  *(undefined1 *)(param_1 + 0x1af) = *(undefined1 *)(param_2 + 0x1e2);
  uVar3 = *(ushort *)(param_2 + 0x1c2);
  if ((uVar3 >> 1 & 1) != 0) {
    *(ushort *)(param_1 + 500) = *(ushort *)(param_1 + 500) | 2;
    uVar3 = *(ushort *)(param_2 + 0x1c2);
  }
  if ((uVar3 >> 3 & 1) == 0) {
    uVar3 = *(ushort *)(param_2 + 0x1c6);
  }
  else {
    *(ushort *)(param_1 + 500) = *(ushort *)(param_1 + 500) | 0x80;
    uVar3 = *(ushort *)(param_2 + 0x1c6);
  }
  if ((uVar3 & 1) != 0) {
    *(ushort *)(param_1 + 500) = *(ushort *)(param_1 + 500) | 8;
    uVar3 = *(ushort *)(param_2 + 0x1c6);
  }
  if ((uVar3 >> 2 & 1) == 0) {
    cVar4 = *(char *)(param_2 + 0x1d3);
  }
  else {
    *(ushort *)(param_1 + 500) = *(ushort *)(param_1 + 500) | 0x10;
    cVar4 = *(char *)(param_2 + 0x1d3);
  }
  if (cVar4 < '\0') {
    *(ushort *)(param_1 + 500) = *(ushort *)(param_1 + 500) | 0x20;
    bVar2 = *(byte *)(param_2 + 0x1e3);
  }
  else {
    bVar2 = *(byte *)(param_2 + 0x1e3);
  }
  if ((bVar2 & 1) == 0) {
    uVar3 = *(ushort *)(param_2 + 0x1c2);
  }
  else {
    *(ushort *)(param_1 + 500) = *(ushort *)(param_1 + 500) | 0x100;
    uVar3 = *(ushort *)(param_2 + 0x1c2);
  }
  if ((uVar3 & 1) != 0) {
    *(ushort *)(param_1 + 500) = *(ushort *)(param_1 + 500) | 4;
    uVar3 = *(ushort *)(param_2 + 0x1c2);
  }
  if ((uVar3 >> 5 & 1) != 0) {
    *(ushort *)(param_1 + 500) = *(ushort *)(param_1 + 500) | 0x4000;
    uVar3 = *(ushort *)(param_2 + 0x1c2);
  }
  if ((uVar3 >> 6 & 1) != 0) {
    *(ushort *)(param_1 + 500) = *(ushort *)(param_1 + 500) | 0x8000;
  }
  *(undefined4 *)(param_1 + 0x17c) = *(undefined4 *)(param_2 + 0x2b8);
  *(undefined4 *)(param_1 + 0x180) = *(undefined4 *)(param_2 + 700);
  *(undefined4 *)(param_1 + 0x184) = *(undefined4 *)(param_2 + 0x2c0);
  *(undefined4 *)(param_1 + 0x188) = *(undefined4 *)(param_2 + 0x2c4);
  *(undefined4 *)(param_1 + 0x18c) = *(undefined4 *)(param_2 + 0x2c8);
  *(undefined1 *)(param_1 + 0x1b1) = *(undefined1 *)(param_2 + 0x1e4);
  *(undefined1 *)(param_1 + 0x1b0) = *(undefined1 *)(param_2 + 0x1c8);
  *(undefined1 *)(param_1 + 0x1b2) = *(undefined1 *)(param_2 + 0x1e1);
  *(undefined1 *)(param_1 + 0x1b4) = *(undefined1 *)(param_2 + 0x1d1);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_2 + 0x130);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_2 + 0x134);
  *(undefined4 *)(param_1 + 0xa8) = *(undefined4 *)(param_2 + 0x138);
  *(undefined4 *)(param_1 + 0xac) = *(undefined4 *)(param_2 + 0x13c);
  *(undefined4 *)(param_1 + 0xb0) = *(undefined4 *)(param_2 + 0x140);
  *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(param_2 + 0x144);
  *(undefined4 *)(param_1 + 0xb8) = *(undefined4 *)(param_2 + 0x148);
  *(undefined4 *)(param_1 + 0xbc) = *(undefined4 *)(param_2 + 0x14c);
  *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_2 + 0x150);
  *(undefined4 *)(param_1 + 0xc4) = *(undefined4 *)(param_2 + 0x154);
  *(undefined4 *)(param_1 + 200) = *(undefined4 *)(param_2 + 0x158);
  *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(param_2 + 0x15c);
  *(undefined4 *)(param_1 + 0xd0) = *(undefined4 *)(param_2 + 0x160);
  *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(param_2 + 0x164);
  *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(param_2 + 0x168);
  *(undefined4 *)(param_1 + 0xdc) = *(undefined4 *)(param_2 + 0x16c);
  if (*(uint *)(param_2 + 0x290) != 0) {
    lVar1 = param_2 + (ulong)*(uint *)(param_2 + 0x290);
    *(undefined4 *)(param_1 + 0x178) = *(undefined4 *)(lVar1 + 0x80);
    bVar2 = *(byte *)(lVar1 + 0x7a);
    if ((bVar2 >> 4 & 1) != 0) {
      *(byte *)(param_1 + 0x1f6) = *(byte *)(param_1 + 0x1f6) | 1;
      bVar2 = *(byte *)(lVar1 + 0x7a);
    }
    if ((bVar2 >> 5 & 1) == 0) {
      *(byte *)(param_1 + 0x1f6) = *(byte *)(param_1 + 0x1f6) & 0xfd;
    }
  }
  if (*(uint *)(param_2 + 0x29c) != 0) {
    *(ulong *)(param_1 + 400) = param_2 + (ulong)*(uint *)(param_2 + 0x29c);
  }
  return;
}

// ==== Aska::IParticleObject::AddRef()
// vaddr 0x21a18f4 | ghidra 0x22a18f4 | size 16 | symbol _ZN4Aska15IParticleObject6AddRefEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObject6AddRefEv(long param_1)

{
  *(int *)(param_1 + 0x118) = *(int *)(param_1 + 0x118) + 1;
  return;
}

// ==== Aska::IParticleObject::Release()
// vaddr 0x21a1904 | ghidra 0x22a1904 | size 36 | symbol _ZN4Aska15IParticleObject7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObject7ReleaseEv(long *param_1)

{
  int iVar1;
  long lVar2;
  
  lVar2 = param_1[0x23];
  iVar1 = (int)lVar2 + -1;
  *(int *)(param_1 + 0x23) = iVar1;
  if ((param_1 != (long *)0x0) && (iVar1 == 0 || (int)lVar2 < 1)) {
                    /* WARNING: Could not recover jumptable at 0x022a1920. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 8))();
    return;
  }
  return;
}

// ==== Aska::IParticleObject::SetEmitterLink(Aska::IParticleEmitter*, int, unsigned char, float, float)
// vaddr 0x21a1928 | ghidra 0x22a1928 | size 24 | symbol _ZN4Aska15IParticleObject14SetEmitterLinkEPNS_16IParticleEmitterEihff | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObject14SetEmitterLinkEPNS_16IParticleEmitterEihff
               (undefined4 param_1,undefined4 param_2,long param_3,undefined8 param_4,
               undefined4 param_5,undefined1 param_6)

{
  *(undefined8 *)(param_3 + 0x120) = param_4;
  *(undefined4 *)(param_3 + 0x130) = param_1;
  *(undefined4 *)(param_3 + 0x134) = param_2;
  *(undefined4 *)(param_3 + 0x138) = param_5;
  *(undefined1 *)(param_3 + 0x1b3) = param_6;
  return;
}

// ==== Aska::IParticleObject::SetAnimation(int)
// vaddr 0x21a1940 | ghidra 0x22a1940 | size 240 | symbol _ZN4Aska15IParticleObject12SetAnimationEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObject12SetAnimationEi(long param_1,int param_2)

{
  uint *puVar1;
  long lVar2;
  char cVar3;
  long lVar4;
  long lVar5;
  ushort *puVar6;
  ushort uVar7;
  int iVar8;
  
  lVar5 = *(long *)(param_1 + 0x140);
  iVar8 = -1;
  lVar2 = lVar5 + (ulong)*(uint *)(lVar5 + 0x34);
  lVar4 = lVar2;
  do {
    iVar8 = iVar8 + 1;
    if (param_2 == iVar8) {
      if (lVar4 != 0) goto code_r0x022a1984;
      break;
    }
    puVar1 = (uint *)(lVar4 + 0x34);
    lVar4 = 0;
    if (*puVar1 != 0) {
      lVar4 = lVar5 + (ulong)*puVar1;
    }
  } while (lVar4 != 0);
  param_2 = 0;
  lVar4 = lVar2;
code_r0x022a1984:
  if (*(int *)(lVar4 + 0x10) == 1) {
    uVar7 = *(ushort *)(param_1 + 500) | 0x800;
  }
  else {
    if (*(int *)(lVar4 + 0x10) == 0) goto code_r0x022a19c0;
    uVar7 = *(ushort *)(param_1 + 500) & 0xf7ff;
  }
  *(ushort *)(param_1 + 500) = uVar7;
code_r0x022a19c0:
  puVar6 = (ushort *)(param_1 + 500);
  *(long *)(param_1 + 0x148) = lVar4;
  *(ulong *)(param_1 + 0x158) = lVar5 + (ulong)*(uint *)(lVar4 + 0x30);
  *puVar6 = *puVar6 | 0x1000;
  if (*(int *)(lVar4 + 0x18) == 0) {
    *(undefined4 *)(lVar4 + 0x18) = 1;
  }
  cVar3 = *(char *)(lVar4 + 0x1c);
  if (((*(char *)(lVar4 + 0x1d) != cVar3) || (*(char *)(lVar4 + 0x1e) != cVar3)) ||
     (*(char *)(lVar4 + 0x1f) != cVar3)) {
    *puVar6 = *puVar6 & 0xefff;
  }
  *(int *)(param_1 + 0x16c) = param_2;
  *(undefined4 *)(param_1 + 0x174) = 0;
  return;
}

// ==== Aska::IParticleObject::CalcAnimationSize(int, int)
// vaddr 0x21a1a30 | ghidra 0x22a1a30 | size 176 | symbol _ZN4Aska15IParticleObject17CalcAnimationSizeEii | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObject17CalcAnimationSizeEii
               (long param_1,undefined4 param_2,undefined4 param_3)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  float fVar7;
  undefined8 uVar8;
  float fVar9;
  float fVar10;
  
  fVar7 = *(float *)(param_1 + 0x174);
  if ((((fVar7 == 0.0) && (lVar3 = *(long *)(param_1 + 0x148), lVar3 != 0)) &&
      (*(long *)(param_1 + 0x158) != 0)) && (uVar5 = *(uint *)(lVar3 + 0x10), uVar5 != 0)) {
    uVar6 = *(uint *)(lVar3 + 0x18);
    uVar4 = 0;
    uVar8 = NEON_scvtf(CONCAT44(param_3,param_2),4);
    do {
      if (uVar6 != 0) {
        uVar5 = 0;
        do {
          uVar1 = (ulong)uVar5;
          uVar5 = uVar5 + 1;
          lVar2 = *(long *)(param_1 + 0x160) +
                  (ulong)*(ushort *)(*(long *)(param_1 + 0x158) + (ulong)uVar4 * 0x10 + uVar1 * 2) *
                  0x40;
          fVar9 = ((float)*(undefined8 *)(lVar2 + 0x18) - (float)*(undefined8 *)(lVar2 + 0x10)) *
                  (float)uVar8 * (float)*(undefined8 *)(lVar2 + 8) * 0.5;
          fVar10 = ((float)((ulong)*(undefined8 *)(lVar2 + 0x18) >> 0x20) -
                   (float)((ulong)*(undefined8 *)(lVar2 + 0x10) >> 0x20)) *
                   (float)((ulong)uVar8 >> 0x20) *
                   (float)((ulong)*(undefined8 *)(lVar2 + 8) >> 0x20) * 0.5;
          if (fVar9 <= fVar10) {
            fVar9 = fVar10;
          }
          if (fVar7 <= fVar9) {
            fVar7 = fVar9;
          }
          *(float *)(param_1 + 0x174) = fVar7;
          uVar6 = *(uint *)(lVar3 + 0x18);
        } while (uVar5 < uVar6);
        uVar5 = *(uint *)(lVar3 + 0x10);
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < uVar5);
  }
  return;
}

// ==== Aska::IParticleObject::GetAnimBlendModes() const
// vaddr 0x21a1ae0 | ghidra 0x22a1ae0 | size 108 | symbol _ZNK4Aska15IParticleObject17GetAnimBlendModesEv | lib libSOA-3.7.0.so | 2026-10-08
uint _ZNK4Aska15IParticleObject17GetAnimBlendModesEv(long param_1)

{
  byte bVar1;
  long lVar2;
  
  if ((*(ushort *)(param_1 + 500) >> 0xe & 1) != 0) {
    bVar1 = *(byte *)(param_1 + 0x1af);
    return (uint)bVar1 << 0x10 | (uint)bVar1 << 0x18 | (uint)CONCAT11(bVar1,bVar1);
  }
  lVar2 = *(long *)(param_1 + 0x148);
  if (lVar2 != 0) {
    return (uint)*(byte *)(lVar2 + 0x1c) << 0x18 | (uint)*(byte *)(lVar2 + 0x1d) << 0x10 |
           (uint)*(byte *)(lVar2 + 0x1e) << 8 | (uint)*(byte *)(lVar2 + 0x1f);
  }
  bVar1 = *(byte *)(param_1 + 0x1af);
  return (uint)bVar1 << 0x10 | (uint)bVar1 << 0x18 | (uint)bVar1 << 8 | (uint)bVar1;
}

// ==== Aska::IParticleObject::GetAnimationSize() const
// vaddr 0x21a1b4c | ghidra 0x22a1b4c | size 16 | symbol _ZNK4Aska15IParticleObject16GetAnimationSizeEv | lib libSOA-3.7.0.so | 2026-10-08
float _ZNK4Aska15IParticleObject16GetAnimationSizeEv(long param_1)

{
  return *(float *)(param_1 + 0x174) * *(float *)(param_1 + 0x170);
}

// ==== Aska::IParticleObject::GetAnimationFrameTime(unsigned int) const
// vaddr 0x21a1b5c | ghidra 0x22a1b5c | size 68 | symbol _ZNK4Aska15IParticleObject21GetAnimationFrameTimeEj | lib libSOA-3.7.0.so | 2026-10-08
float _ZNK4Aska15IParticleObject21GetAnimationFrameTimeEj(long param_1,uint param_2)

{
  float fVar1;
  
  fVar1 = 0.0;
  if ((*(long *)(param_1 + 0x148) != 0) && (param_2 < *(uint *)(*(long *)(param_1 + 0x148) + 0x10)))
  {
    if (param_2 == 0) {
      fVar1 = 0.0;
    }
    else {
      fVar1 = *(float *)(*(long *)(param_1 + 0x158) + (ulong)(param_2 - 1) * 0x10 + 8);
    }
    fVar1 = *(float *)(*(long *)(param_1 + 0x158) + (ulong)param_2 * 0x10 + 8) - fVar1;
  }
  return fVar1;
}

// ==== Aska::IParticleObject::GetNextParticlePosition(Aska::Vector*)
// vaddr 0x21a1ba0 | ghidra 0x22a1ba0 | size 140 | symbol _ZN4Aska15IParticleObject23GetNextParticlePositionEPNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska15IParticleObject23GetNextParticlePositionEPNS_6VectorE(long param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  
  if (param_2 == (undefined4 *)0x0) {
    return 0;
  }
  uVar2 = *(uint *)(param_1 + 0x1d8);
  do {
    uVar3 = uVar2;
    if (*(int *)(param_1 + 0x1d0) <= (int)uVar3) {
      return 0;
    }
    *(uint *)(param_1 + 0x1d8) = uVar3 + 1;
    uVar2 = uVar3 + 1;
  } while ((*(uint *)(*(long *)(param_1 + 0x1e0) + (long)((int)uVar3 >> 5) * 4) &
           1 << (ulong)(uVar3 & 0x1f)) == 0);
  puVar1 = (undefined4 *)(*(long *)(param_1 + 0x1b8) + (ulong)(*(int *)(param_1 + 0x1c8) * uVar3));
  *param_2 = *puVar1;
  param_2[1] = puVar1[1];
  param_2[2] = puVar1[2];
  param_2[3] = puVar1[3];
  return 1;
}

// ==== Aska::IParticleObject::Alloc(int, int)
// vaddr 0x21a1c2c | ghidra 0x22a1c2c | size 268 | symbol _ZN4Aska15IParticleObject5AllocEii | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska15IParticleObject5AllocEii(long param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  long lVar3;
  ulong uVar4;
  undefined8 uVar5;
  
  if (0x7fff < param_2) {
    param_2 = 0x8000;
  }
  if (0xf < param_3) {
    param_3 = 0x10;
  }
  if (param_2 < 1) {
    return 0;
  }
  if (*(long *)(param_1 + 0x1b8) != 0) {
    Aska::ParticleManager::Free(void*)();
    *(undefined8 *)(param_1 + 0x1b8) = 0;
  }
  if (*(long *)(param_1 + 0x1c0) != 0) {
    Aska::ParticleManager::Free(void*)();
    *(undefined8 *)(param_1 + 0x1c0) = 0;
  }
  iVar1 = param_3;
  if (param_3 < 2) {
    iVar1 = 1;
  }
  iVar2 = *(int *)(param_1 + 0x1c8) * param_2;
  lVar3 = Aska::ParticleManager::Malloc(unsigned long)(iVar2);
  *(long *)(param_1 + 0x1b8) = lVar3;
  uVar5 = 0;
  if (lVar3 == 0) goto code_r0x022a1d24;
  *(int *)(param_1 + 0x1d0) = param_2;
  memset(lVar3,0,iVar2);
  uVar4 = Aska::BitArray::Alloc(int)(param_1 + 0x1e0,param_2);
  if ((uVar4 & 1) == 0) {
code_r0x022a1d00:
    if (*(long *)(param_1 + 0x1b8) != 0) {
      Aska::ParticleManager::Free(void*)();
      *(undefined8 *)(param_1 + 0x1b8) = 0;
    }
    uVar5 = 0;
    if (*(long *)(param_1 + 0x1c0) != 0) {
      Aska::ParticleManager::Free(void*)();
      uVar5 = 0;
      *(undefined8 *)(param_1 + 0x1c0) = 0;
    }
  }
  else {
    if (1 < param_3) {
      uVar4 = (long)((iVar1 + -1) * param_2) * 0x70;
      lVar3 = Aska::ParticleManager::Malloc(unsigned long)(uVar4 & 0xfffffff0);
      *(long *)(param_1 + 0x1c0) = lVar3;
      if (lVar3 == 0) goto code_r0x022a1d00;
      memset(lVar3,0,uVar4);
    }
    uVar5 = 1;
  }
code_r0x022a1d24:
  *(int *)(param_1 + 0x1d4) = iVar1;
  return uVar5;
}

// ==== Aska::IParticleObject::GetMemoryFootprint() const
// vaddr 0x21a1d38 | ghidra 0x22a1d38 | size 64 | symbol _ZNK4Aska15IParticleObject18GetMemoryFootprintEv | lib libSOA-3.7.0.so | 2026-10-08
int _ZNK4Aska15IParticleObject18GetMemoryFootprintEv(long param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (*(long *)(param_1 + 0x1e0) != 0) {
    iVar1 = *(int *)(*(long *)(param_1 + 0x1e0) + -4) * 4 + 4;
  }
  return iVar1 + *(int *)(param_1 + 0x1cc) +
         (*(int *)(param_1 + 0x1d4) * 0x70 + -0x70 + *(int *)(param_1 + 0x1c8)) *
         *(int *)(param_1 + 0x1d0);
}

// ==== Aska::IParticleObject::GatherActive(float, int, int*, int*)
// vaddr 0x21a1d78 | ghidra 0x22a1d78 | size 284 | symbol _ZN4Aska15IParticleObject12GatherActiveEfiPiS1_ | lib libSOA-3.7.0.so | 2026-10-08
uint _ZN4Aska15IParticleObject12GatherActiveEfiPiS1_
               (float param_1,long param_2,int param_3,long param_4,int *param_5)

{
  long lVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  
  iVar2 = *(int *)(param_2 + 0x1d0);
  iVar3 = *(int *)(param_2 + 0x1d4);
  *(undefined4 *)(param_4 + (long)(param_3 + -1) * 4) = 0;
  uVar7 = *(uint *)(param_2 + 0x1dc);
  uVar4 = *(uint *)(param_2 + 0x1ec);
  uVar5 = (uint)(0 < param_3 && (int)uVar7 < iVar2);
  iVar6 = 0;
  if (uVar4 == 0) {
    if (uVar5 != 0) {
      uVar5 = 0;
      do {
        if ((*(uint *)(*(long *)(param_2 + 0x1e0) + (long)((int)uVar7 >> 5) * 4) &
            1 << (ulong)(uVar7 & 0x1f)) != 0) {
          *(uint *)(param_4 + (long)iVar6 * 4) = uVar7;
          uVar7 = *(uint *)(param_2 + 0x1dc);
          iVar6 = iVar6 + 1;
          uVar5 = uVar5 + iVar3;
        }
        uVar7 = uVar7 + 1;
        *(uint *)(param_2 + 0x1dc) = uVar7;
      } while (((int)uVar5 < param_3) && ((int)uVar7 < iVar2));
    }
  }
  else if (uVar5 != 0) {
    uVar5 = 0;
    do {
      if ((*(uint *)(*(long *)(param_2 + 0x1e0) + (long)((int)uVar7 >> 5) * 4) &
          1 << (ulong)(uVar7 & 0x1f)) != 0) {
        if ((uVar7 & uVar4) == 0) {
          *(uint *)(param_4 + (long)iVar6 * 4) = uVar7;
          iVar6 = iVar6 + 1;
          uVar5 = uVar5 + iVar3;
        }
        else {
          lVar1 = *(long *)(param_2 + 0x1b8) + (ulong)(*(int *)(param_2 + 0x1c8) * uVar7);
          *(undefined4 *)(lVar1 + 0x2c) = 0;
          *(float *)(lVar1 + 0xc) = *(float *)(lVar1 + 0xc) + param_1;
        }
      }
      uVar7 = *(int *)(param_2 + 0x1dc) + 1;
      *(uint *)(param_2 + 0x1dc) = uVar7;
    } while (((int)uVar5 < param_3) && ((int)uVar7 < iVar2));
  }
  *(uint *)(param_2 + 0x1e8) = *(int *)(param_2 + 0x1e8) + uVar5;
  *param_5 = iVar6;
  return uVar5;
}

// ==== Aska::IParticleObject::AttachTexture(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)
// vaddr 0x21a1e94 | ghidra 0x22a1e94 | size 468 | symbol _ZN4Aska15IParticleObject13AttachTextureEPKNS_3AFF18AsfParticleEmitterE9StBooleanILb1EE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObject13AttachTextureEPKNS_3AFF18AsfParticleEmitterE9StBooleanILb1EE
               (long param_1,long param_2)

{
  uint *puVar1;
  long lVar2;
  byte bVar3;
  char cVar4;
  long lVar5;
  byte bVar6;
  uint uVar7;
  long lVar8;
  ushort *puVar9;
  uint uVar10;
  
  if (*(int *)(param_2 + 0x1b0) == 0) {
    uVar10 = *(uint *)(param_2 + 0x290);
    goto joined_r0x022a1f50;
  }
  lVar2 = param_2 + *(int *)(param_2 + 0x1b0);
  *(long *)(param_1 + 0x140) = lVar2;
  *(undefined1 *)(param_1 + 0x1ae) = 1;
  lVar5 = lVar2 + (ulong)*(uint *)(lVar2 + 0x34);
  if (lVar5 != 0) {
    bVar6 = 1;
    do {
      bVar3 = *(byte *)(lVar5 + 0x18);
      if (bVar6 < bVar3) {
        *(byte *)(param_1 + 0x1ae) = bVar3;
        bVar6 = bVar3;
      }
      puVar1 = (uint *)(lVar5 + 0x34);
      lVar5 = 0;
      if (*puVar1 != 0) {
        lVar5 = lVar2 + (ulong)*puVar1;
      }
    } while (lVar5 != 0);
  }
  *(ulong *)(param_1 + 0x160) =
       lVar2 + (ulong)*(uint *)(lVar2 + (ulong)*(uint *)(lVar2 + 0x30) + 0x18);
  *(undefined4 *)(param_1 + 0x168) = *(undefined4 *)(lVar2 + (ulong)*(uint *)(lVar2 + 0x30) + 0x10);
  bVar6 = *(byte *)(param_2 + (ulong)*(uint *)(param_2 + 0x290) + 0x76);
  uVar7 = (uint)bVar6;
  lVar5 = lVar2 + (ulong)*(uint *)(lVar2 + 0x34);
  uVar10 = ~(uint)bVar6;
  lVar8 = lVar5;
  do {
    uVar10 = uVar10 + 1;
    if (uVar10 == 0) {
      if (lVar8 != 0) goto code_r0x022a1f64;
      break;
    }
    puVar1 = (uint *)(lVar8 + 0x34);
    lVar8 = 0;
    if (*puVar1 != 0) {
      lVar8 = lVar2 + (ulong)*puVar1;
    }
  } while (lVar8 != 0);
  uVar7 = 0;
  lVar8 = lVar5;
code_r0x022a1f64:
  if (*(int *)(lVar8 + 0x10) == 1) {
    uVar10 = *(uint3 *)(param_1 + 500) | 0x800;
code_r0x022a1fb4:
    *(short *)(param_1 + 500) = (short)uVar10;
  }
  else {
    if (*(int *)(lVar8 + 0x10) != 0) {
      uVar10 = *(ushort *)(param_1 + 500) & 0xfffff7ff | (uint)*(byte *)(param_1 + 0x1f6) << 0x10;
      goto code_r0x022a1fb4;
    }
    uVar10 = (uint)*(uint3 *)(param_1 + 500);
  }
  puVar9 = (ushort *)(param_1 + 500);
  *(long *)(param_1 + 0x148) = lVar8;
  *(ulong *)(param_1 + 0x158) = lVar2 + (ulong)*(uint *)(lVar8 + 0x30);
  *(char *)(param_1 + 0x1f6) = (char)(uVar10 >> 0x10);
  *puVar9 = (ushort)uVar10 | 0x1000;
  if (*(int *)(lVar8 + 0x18) == 0) {
    *(undefined4 *)(lVar8 + 0x18) = 1;
  }
  cVar4 = *(char *)(lVar8 + 0x1c);
  if (((*(char *)(lVar8 + 0x1d) != cVar4) || (*(char *)(lVar8 + 0x1e) != cVar4)) ||
     (*(char *)(lVar8 + 0x1f) != cVar4)) {
    *puVar9 = *puVar9 & 0xefff;
  }
  *(uint *)(param_1 + 0x16c) = uVar7;
  *(undefined4 *)(param_1 + 0x174) = 0;
  if (*(int *)(*(long *)(param_1 + 0x148) + 0x10) == 1) {
    *(ushort *)(param_1 + 500) = *(ushort *)(param_1 + 500) | 0x800;
  }
  uVar10 = *(uint *)(param_2 + 0x290);
joined_r0x022a1f50:
  if ((uVar10 != 0) && ((*(byte *)(param_2 + (ulong)uVar10 + 0x7a) >> 3 & 1) != 0)) {
    *(ushort *)(param_1 + 500) = *(ushort *)(param_1 + 500) | 0x40;
  }
  return;
}

// ==== Aska::IParticleObject::AttachDynamics(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)
// vaddr 0x21a2068 | ghidra 0x22a2068 | size 772 | symbol _ZN4Aska15IParticleObject14AttachDynamicsEPKNS_3AFF18AsfParticleEmitterE9StBooleanILb1EE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska15IParticleObject14AttachDynamicsEPKNS_3AFF18AsfParticleEmitterE9StBooleanILb1EE
          (long param_1,long param_2)

{
  ulong uVar1;
  int iVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined8 *puVar7;
  undefined *puVar8;
  int *piVar9;
  int *piVar10;
  ulong uVar11;
  int *piVar12;
  int *piVar13;
  undefined8 *puVar14;
  ulong uVar15;
  long lVar16;
  long lVar17;
  ulong uVar18;
  ulong uVar19;
  long lVar20;
  undefined8 uVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  
  lVar16 = *(long *)(param_1 + 0x198);
  if (lVar16 != 0) {
    Aska::ParticleDynamicsContext::~ParticleDynamicsContext()(lVar16);
    operator delete(void*)(lVar16);
  }
  piVar9 = (int *)operator new(unsigned long, std::nothrow_t const&)(0x48,PTR__ZSt7nothrow_02cb9a80);
  if (piVar9 == (int *)0x0) {
    *(undefined8 *)(param_1 + 0x198) = 0;
    return 0;
  }
  *piVar9 = 0;
  piVar9[6] = 0;
  piVar9[2] = 0;
  piVar9[3] = 0;
  piVar9[4] = 0;
  piVar9[5] = 0;
  piVar9[8] = 0;
  piVar9[9] = 0;
  piVar9[10] = 0;
  piVar9[0xb] = 0;
  piVar9[0xe] = 0;
  piVar9[0xf] = 0;
  piVar9[0x10] = 0;
  piVar9[0x11] = 0;
  *(int **)(param_1 + 0x198) = piVar9;
  *(bool *)(piVar9 + 0xd) = *(char *)(param_2 + 0x1e0) != '\0';
  piVar9[0xc] = *(int *)(param_2 + 0x248);
  uVar18 = (ulong)*(uint *)(param_2 + 0x294);
  if (*(uint *)(param_2 + 0x294) != 0) {
    piVar12 = (int *)(param_2 + uVar18) + 1;
    iVar2 = *(int *)(param_2 + uVar18);
    uVar19 = (ulong)iVar2;
    *piVar9 = iVar2;
    puVar8 = PTR__ZSt7nothrow_02cb9a80;
    if (0 < iVar2) {
      auVar3._8_8_ = 0;
      auVar3._0_8_ = uVar19;
      lVar20 = uVar19 * 4;
      lVar16 = lVar20;
      if (SUB168(auVar3 * ZEXT816(4),8) != 0) {
        lVar16 = -1;
      }
      piVar10 = (int *)operator new[](unsigned long, std::nothrow_t const&)(lVar16,PTR__ZSt7nothrow_02cb9a80);
      auVar4._8_8_ = 0;
      auVar4._0_8_ = uVar19;
      lVar17 = uVar19 * 8;
      lVar16 = lVar17;
      if (SUB168(auVar4 * ZEXT816(8),8) != 0) {
        lVar16 = -1;
      }
      *(int **)(piVar9 + 2) = piVar10;
      lVar16 = operator new[](unsigned long, std::nothrow_t const&)(lVar16,puVar8);
      *(long *)(piVar9 + 4) = lVar16;
      if ((lVar16 != 0) && (lVar16 + lVar17 != lVar16)) {
        memset(lVar16,0,lVar17);
      }
      if ((piVar10 == (int *)0x0) || (lVar16 == 0)) {
        Aska::ParticleDynamicsContext::~ParticleDynamicsContext()(piVar9);
        goto code_r0x022a2314;
      }
      if (lVar20 != 0) {
        uVar1 = (lVar20 - 4U >> 2) + 1;
        if ((7 < uVar1) && (uVar11 = uVar1 & 0x7ffffffffffffff8, uVar11 != 0)) {
          piVar13 = piVar10 + 4;
          piVar12 = piVar12 + uVar11;
          piVar10 = piVar10 + uVar11;
          puVar14 = (undefined8 *)(param_2 + uVar18 + 0x14);
          uVar15 = uVar11;
          do {
            puVar7 = puVar14 + -1;
            uVar21 = puVar14[-2];
            uVar23 = puVar14[1];
            uVar22 = *puVar14;
            uVar15 = uVar15 - 8;
            puVar14 = puVar14 + 4;
            *(undefined8 *)(piVar13 + -2) = *puVar7;
            *(undefined8 *)(piVar13 + -4) = uVar21;
            *(undefined8 *)(piVar13 + 2) = uVar23;
            *(undefined8 *)piVar13 = uVar22;
            piVar13 = piVar13 + 8;
          } while (uVar15 != 0);
          if (uVar1 == uVar11) goto code_r0x022a21f4;
        }
        piVar12 = piVar12 + -1;
        do {
          piVar12 = piVar12 + 1;
          *piVar10 = *piVar12;
          piVar10 = piVar10 + 1;
        } while ((int *)(param_2 + uVar18 + uVar19 * 4) != piVar12);
      }
    }
  }
code_r0x022a21f4:
  uVar18 = (ulong)*(uint *)(param_2 + 0x298);
  if (*(uint *)(param_2 + 0x298) != 0) {
    piVar12 = (int *)(param_2 + uVar18) + 1;
    iVar2 = *(int *)(param_2 + uVar18);
    uVar19 = (ulong)iVar2;
    piVar9[6] = iVar2;
    puVar8 = PTR__ZSt7nothrow_02cb9a80;
    if (0 < iVar2) {
      auVar5._8_8_ = 0;
      auVar5._0_8_ = uVar19;
      lVar20 = uVar19 * 4;
      lVar16 = lVar20;
      if (SUB168(auVar5 * ZEXT816(4),8) != 0) {
        lVar16 = -1;
      }
      piVar10 = (int *)operator new[](unsigned long, std::nothrow_t const&)(lVar16,PTR__ZSt7nothrow_02cb9a80);
      auVar6._8_8_ = 0;
      auVar6._0_8_ = uVar19;
      lVar17 = uVar19 * 8;
      lVar16 = lVar17;
      if (SUB168(auVar6 * ZEXT816(8),8) != 0) {
        lVar16 = -1;
      }
      *(int **)(piVar9 + 8) = piVar10;
      lVar16 = operator new[](unsigned long, std::nothrow_t const&)(lVar16,puVar8);
      *(long *)(piVar9 + 10) = lVar16;
      if ((lVar16 != 0) && (lVar16 + lVar17 != lVar16)) {
        memset(lVar16,0,lVar17);
      }
      if ((piVar10 == (int *)0x0) || (lVar16 == 0)) {
        piVar9 = *(int **)(param_1 + 0x198);
        if (piVar9 == (int *)0x0) {
          return 0;
        }
        Aska::ParticleDynamicsContext::~ParticleDynamicsContext()(piVar9);
code_r0x022a2314:
        operator delete(void*)(piVar9);
        *(undefined8 *)(param_1 + 0x198) = 0;
        return 0;
      }
      if (lVar20 != 0) {
        uVar1 = (lVar20 - 4U >> 2) + 1;
        if ((7 < uVar1) && (uVar11 = uVar1 & 0x7ffffffffffffff8, uVar11 != 0)) {
          piVar12 = piVar12 + uVar11;
          puVar14 = (undefined8 *)(param_2 + uVar18 + 0x14);
          piVar9 = piVar10 + 4;
          uVar15 = uVar11;
          do {
            puVar7 = puVar14 + -1;
            uVar21 = puVar14[-2];
            uVar23 = puVar14[1];
            uVar22 = *puVar14;
            puVar14 = puVar14 + 4;
            uVar15 = uVar15 - 8;
            *(undefined8 *)(piVar9 + -2) = *puVar7;
            *(undefined8 *)(piVar9 + -4) = uVar21;
            *(undefined8 *)(piVar9 + 2) = uVar23;
            *(undefined8 *)piVar9 = uVar22;
            piVar9 = piVar9 + 8;
          } while (uVar15 != 0);
          piVar10 = piVar10 + uVar11;
          if (uVar1 == uVar11) {
            return 1;
          }
        }
        piVar12 = piVar12 + -1;
        do {
          piVar12 = piVar12 + 1;
          *piVar10 = *piVar12;
          piVar10 = piVar10 + 1;
        } while ((int *)(param_2 + uVar18 + uVar19 * 4) != piVar12);
      }
    }
  }
  return 1;
}

// ==== Aska::IParticleObject::InitDynamics(Aska::AsfHandler*, StBoolean<true>)
// vaddr 0x21a236c | ghidra 0x22a236c | size 512 | symbol _ZN4Aska15IParticleObject12InitDynamicsEPNS_10AsfHandlerE9StBooleanILb1EE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

byte _ZN4Aska15IParticleObject12InitDynamicsEPNS_10AsfHandlerE9StBooleanILb1EE
               (long param_1,long param_2)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  bool bVar4;
  long *plVar5;
  long lVar6;
  byte bVar7;
  long lVar8;
  int *piVar9;
  int *piVar10;
  long *plVar11;
  int *piVar12;
  long lVar13;
  
  piVar10 = *(int **)(param_1 + 0x198);
  if (piVar10 == (int *)0x0) {
    bVar7 = 0;
  }
  else {
    if (*piVar10 < 1) {
      bVar4 = false;
    }
    else {
      plVar11 = *(long **)(piVar10 + 4);
      bVar4 = false;
      lVar13 = (long)*piVar10 << 3;
      piVar9 = *(int **)(piVar10 + 2);
      do {
        piVar12 = piVar9;
        if (bVar4) {
          *plVar11 = 0;
        }
        else if (*plVar11 == 0) {
          piVar12 = piVar9 + 1;
          iVar1 = *piVar9;
          if (0 < *(int *)(param_2 + 0xb0)) {
            if (iVar1 < 0) {
              if ((*(long *)(param_2 + 0x78) == 0) || (*(long *)(param_2 + 0x508) == 0))
              goto code_r0x022a2434;
              plVar5 = (long *)Aska::AsfHandler::QuickSearchExternalLinkByName(char const*) const(param_2,*(long *)(param_2 + 0x78) +
                                                       (long)(int)(iVar1 << 5 ^ 0xffffffe0) + 0x20);
            }
            else {
              plVar5 = *(long **)(*(long *)(*(long *)(param_2 + 0xd8) + (long)iVar1 * 8) + 0x38);
            }
            if (plVar5 != (long *)0x0) {
              lVar6 = (**(code **)(*plVar5 + 0x180))();
              if (lVar6 == 0) {
                bVar4 = true;
              }
              *plVar11 = lVar6;
            }
          }
        }
code_r0x022a2434:
        plVar11 = plVar11 + 1;
        lVar13 = lVar13 + -8;
        piVar9 = piVar12;
      } while (lVar13 != 0);
    }
    uVar3 = _UNK_027dbb38;
    uVar2 = _UNK_027dbb30;
    if (0 < piVar10[6]) {
      plVar11 = *(long **)(piVar10 + 10);
      lVar13 = (long)piVar10[6] << 3;
      piVar10 = *(int **)(piVar10 + 8);
      do {
        piVar9 = piVar10;
        if (*plVar11 == 0) {
          if (bVar4 == false) {
            piVar9 = piVar10 + 1;
            iVar1 = *piVar10;
            if (0 < *(int *)(param_2 + 0xb0)) {
              if (iVar1 < 0) {
                if ((*(long *)(param_2 + 0x78) == 0) || (*(long *)(param_2 + 0x508) == 0))
                goto code_r0x022a253c;
                lVar6 = Aska::AsfHandler::QuickSearchExternalLinkByName(char const*) const(param_2,*(long *)(param_2 + 0x78) +
                                                (long)(int)(iVar1 << 5 ^ 0xffffffe0) + 0x20);
              }
              else {
                lVar6 = *(long *)(*(long *)(*(long *)(param_2 + 0xd8) + (long)iVar1 * 8) + 0x38);
              }
              if ((lVar6 != 0) && (*(long **)(lVar6 + 0x198) != (long *)0x0)) {
                lVar6 = (**(code **)(**(long **)(lVar6 + 0x198) + 0x68))();
                *plVar11 = lVar6;
                bVar4 = lVar6 == 0;
                lVar8 = *(long *)(*(long *)(lVar6 + 0x130) + 0x20);
                if (lVar8 != 0) {
                  *(undefined4 *)(lVar6 + 0x110) = *(undefined4 *)(lVar8 + 0x80);
                  *(undefined4 *)(lVar6 + 0x114) = *(undefined4 *)(lVar8 + 0x84);
                  *(undefined4 *)(lVar6 + 0x118) = *(undefined4 *)(lVar8 + 0x88);
                  *(undefined4 *)(lVar6 + 0x11c) = *(undefined4 *)(lVar8 + 0x8c);
                }
                *(undefined8 *)(lVar6 + 0x128) = uVar3;
                *(undefined8 *)(lVar6 + 0x120) = uVar2;
                goto code_r0x022a2540;
              }
            }
code_r0x022a253c:
            bVar4 = false;
          }
          else {
            *plVar11 = 0;
            bVar4 = true;
          }
        }
code_r0x022a2540:
        lVar13 = lVar13 + -8;
        plVar11 = plVar11 + 1;
        piVar10 = piVar9;
      } while (lVar13 != 0);
    }
    bVar7 = bVar4 ^ 1;
  }
  return bVar7;
}

// ==== Aska::IParticleObject::SetLandscapeConstraint(Aska::ILandscapeConstraint*, StBoolean<true>)
// vaddr 0x21a256c | ghidra 0x22a256c | size 16 | symbol _ZN4Aska15IParticleObject22SetLandscapeConstraintEPNS_20ILandscapeConstraintE9StBooleanILb1EE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObject22SetLandscapeConstraintEPNS_20ILandscapeConstraintE9StBooleanILb1EE
               (long param_1,undefined8 param_2)

{
  if (*(long *)(param_1 + 0x198) != 0) {
    *(undefined8 *)(*(long *)(param_1 + 0x198) + 0x38) = param_2;
  }
  return;
}

// ==== Aska::IParticleObject::DynamicsPrepare(Aska::Matrix*, StBoolean<true>)
// vaddr 0x21a257c | ghidra 0x22a257c | size 208 | symbol _ZN4Aska15IParticleObject15DynamicsPrepareEPNS_6MatrixE9StBooleanILb1EE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObject15DynamicsPrepareEPNS_6MatrixE9StBooleanILb1EE
               (long param_1,undefined8 param_2)

{
  long *plVar1;
  int *piVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  
  piVar2 = *(int **)(param_1 + 0x198);
  if (*piVar2 != 0) {
    plVar3 = *(long **)(piVar2 + 4);
    lVar4 = (long)*piVar2 << 3;
    do {
      plVar1 = (long *)*plVar3;
      if (plVar1 != (long *)0x0) {
        (**(code **)(*plVar1 + 0x10))(plVar1,param_2);
      }
      lVar4 = lVar4 + -8;
      plVar3 = plVar3 + 1;
    } while (lVar4 != 0);
  }
  lVar4 = *(long *)(piVar2 + 0x10);
  if ((lVar4 != 0) && (0 < *(long *)(lVar4 + 0x18))) {
    lVar5 = 0;
    do {
      plVar3 = *(long **)(*(long *)(lVar4 + 8) + lVar5 * 8);
      (**(code **)(*plVar3 + 0x10))(plVar3,param_2);
      lVar5 = lVar5 + 1;
    } while (lVar5 < *(long *)(lVar4 + 0x18));
  }
  if (piVar2[6] != 0) {
    plVar3 = *(long **)(piVar2 + 10);
    lVar4 = (long)piVar2[6] << 3;
    do {
      plVar1 = (long *)*plVar3;
      if (plVar1 != (long *)0x0) {
        (**(code **)(*plVar1 + 0x10))(piVar2[0xc],plVar1,param_2);
      }
      lVar4 = lVar4 + -8;
      plVar3 = plVar3 + 1;
    } while (lVar4 != 0);
  }
  return;
}

// ==== Aska::IParticleObject::AddManualForceEmitter(Aska::ParticleDynamicsForceEmitter*)
// vaddr 0x21a264c | ghidra 0x22a264c | size 216 | symbol _ZN4Aska15IParticleObject21AddManualForceEmitterEPNS_28ParticleDynamicsForceEmitterE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska15IParticleObject21AddManualForceEmitterEPNS_28ParticleDynamicsForceEmitterE
          (long param_1,long param_2)

{
  undefined *puVar1;
  long *plVar2;
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  
  lVar6 = *(long *)(param_1 + 0x198);
  if (lVar6 == 0) {
code_r0x022a2710:
    uVar3 = 0;
  }
  else {
    lVar5 = *(long *)(lVar6 + 0x40);
    if (lVar5 == 0) {
      plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x38,PTR__ZSt7nothrow_02cb9a80);
      puVar1 = PTR__ZTVN4Aska6TArrayIPNS_28ParticleDynamicsForceEmitterELb0EEE_02cb6e68;
      if (plVar2 != (long *)0x0) {
        plVar2[4] = 0;
        plVar2[3] = 0;
        plVar2[2] = 0;
        plVar2[1] = 0;
        plVar2[5] = 8;
        *plVar2 = (long)(puVar1 + 0x10);
        *(undefined4 *)(plVar2 + 6) = 0;
      }
      *(long **)(lVar6 + 0x40) = plVar2;
      lVar5 = *(long *)(*(long *)(param_1 + 0x198) + 0x40);
      if (lVar5 == 0) goto code_r0x022a2710;
    }
    lVar6 = *(long *)(lVar5 + 0x18);
    if (0 < (int)lVar6) {
      lVar4 = 0;
      do {
        if (*(long *)(*(long *)(lVar5 + 8) + lVar4 * 8) == param_2) goto code_r0x022a2708;
        lVar4 = lVar4 + 1;
      } while (lVar4 < (int)lVar6);
    }
    if (-1 < lVar6) {
      Aska::TArray<Aska::ParticleDynamicsForceEmitter*, false>::Resize(long, bool)(lVar5,lVar6 + 1,0);
      *(long *)(*(long *)(lVar5 + 8) + lVar6 * 8) = param_2;
    }
code_r0x022a2708:
    uVar3 = 1;
  }
  return uVar3;
}

// ==== Aska::IParticleObject::AttachCurveMotion(Aska::AFF::AsfParticleEmitter const*, StBoolean<true>)
// vaddr 0x21a2724 | ghidra 0x22a2724 | size 112 | symbol _ZN4Aska15IParticleObject17AttachCurveMotionEPKNS_3AFF18AsfParticleEmitterE9StBooleanILb1EE | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska15IParticleObject17AttachCurveMotionEPKNS_3AFF18AsfParticleEmitterE9StBooleanILb1EE
               (long param_1,long param_2)

{
  long lVar1;
  long *plVar2;
  
  if (*(long *)(param_1 + 0x1a0) != 0) {
    operator delete(void*)();
  }
  plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x18,PTR__ZSt7nothrow_02cb9a80);
  if (plVar2 == (long *)0x0) {
    *(undefined8 *)(param_1 + 0x1a0) = 0;
  }
  else {
    *(long **)(param_1 + 0x1a0) = plVar2;
    lVar1 = param_2 + (ulong)*(uint *)(param_2 + 0x2a0);
    *plVar2 = lVar1;
    plVar2[1] = lVar1 + 0x10;
    *(float *)(plVar2 + 2) = *(float *)(param_2 + 0x24c) + *(float *)(param_2 + 0x250);
  }
  return plVar2 != (long *)0x0;
}

// ==== Aska::IParticleObject::TailProcedure(int const*, int, Aska::ParticleContext*)
// vaddr 0x21a2794 | ghidra 0x22a2794 | size 40 | symbol _ZN4Aska15IParticleObject13TailProcedureEPKiiPNS_15ParticleContextE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObject13TailProcedureEPKiiPNS_15ParticleContextE(long param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x1f7);
  if (cVar1 == '\x02') {
    (*(code *)
      PTR__ZN4Aska15IParticleObject28Tail_ConnectionMode_RelativeEPKiiPNS_15ParticleContextE_02c9fe28
    )();
    return;
  }
  if (cVar1 != '\x01') {
    if (cVar1 == '\0') {
      (*(code *)
        PTR__ZN4Aska15IParticleObject25Tail_ConnectionMode_TrailEPKiiPNS_15ParticleContextE_02c9d2a8
      )();
      return;
    }
    return;
  }
  (*(code *)
    PTR__ZN4Aska15IParticleObject26Tail_ConnectionMode_NoCopyEPKiiPNS_15ParticleContextE_02c9d908)()
  ;
  return;
}

// ==== Aska::IParticleObject::Tail_ConnectionMode_Trail(int const*, int, Aska::ParticleContext*)
// vaddr 0x21a27bc | ghidra 0x22a27bc | size 2528 | symbol _ZN4Aska15IParticleObject25Tail_ConnectionMode_TrailEPKiiPNS_15ParticleContextE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObject25Tail_ConnectionMode_TrailEPKiiPNS_15ParticleContextE
               (long param_1,long param_2,uint param_3,long param_4)

{
  undefined4 *puVar1;
  float *pfVar2;
  undefined4 *puVar3;
  long lVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  undefined8 *puVar9;
  undefined4 *puVar10;
  long lVar11;
  long lVar12;
  ulong uVar13;
  undefined4 *puVar14;
  float fVar15;
  
  if (*(byte *)(param_1 + 0x1f8) < 4) {
    iVar5 = *(int *)(param_1 + 0x1d4);
    lVar12 = (long)iVar5;
    switch(*(byte *)(param_1 + 0x1f8)) {
    case 0:
      if (0 < (int)param_3) {
        uVar13 = 0;
        puVar14 = (undefined4 *)(param_4 + lVar12 * 0x50 + -0x28);
        iVar8 = iVar5;
        while( true ) {
          iVar7 = *(int *)(param_2 + uVar13 * 4);
          lVar4 = *(long *)(param_1 + 0x1c0);
          iVar8 = (iVar8 + -1) * iVar7;
          puVar3 = (undefined4 *)
                   (*(long *)(param_1 + 0x1b8) + (ulong)(uint)(*(int *)(param_1 + 0x1c8) * iVar7));
          if (2 < iVar5) {
            puVar9 = (undefined8 *)(lVar4 + (lVar12 + -3) * 0x70 + (long)iVar8 * 0x70);
            puVar10 = puVar14;
            lVar11 = lVar12;
            do {
              lVar11 = lVar11 + -1;
              puVar10[-10] = *(undefined4 *)(puVar9 + 0xe);
              puVar10[-9] = *(undefined4 *)((long)puVar9 + 0x74);
              puVar10[-8] = *(undefined4 *)(puVar9 + 0xf);
              puVar10[-7] = *(undefined4 *)((long)puVar9 + 0x7c);
              puVar10[-6] = *(undefined4 *)(puVar9 + 0x12);
              puVar10[-5] = *(undefined4 *)((long)puVar9 + 0x94);
              puVar10[-4] = *(undefined4 *)(puVar9 + 0x13);
              puVar10[-3] = *(undefined4 *)((long)puVar9 + 0x9c);
              puVar10[-2] = *(undefined4 *)(puVar9 + 0x16);
              puVar10[-1] = *(undefined4 *)((long)puVar9 + 0xb4);
              *puVar10 = *(undefined4 *)(puVar9 + 0x17);
              puVar10[1] = *(undefined4 *)((long)puVar9 + 0xbc);
              puVar10[2] = *(undefined4 *)(puVar9 + 0x18);
              puVar10[3] = *(undefined4 *)((long)puVar9 + 0xc4);
              puVar10[4] = *(undefined4 *)(puVar9 + 0x19);
              puVar10[5] = *(undefined4 *)((long)puVar9 + 0xcc);
              puVar10[6] = *(undefined4 *)(puVar9 + 0x1a);
              puVar10[7] = *(undefined4 *)((long)puVar9 + 0xd4);
              puVar10[8] = *(undefined4 *)(puVar9 + 0x1b);
              puVar10[9] = *(undefined4 *)((long)puVar9 + 0xdc);
              puVar10 = puVar10 + -0x14;
              puVar9[0xf] = puVar9[1];
              puVar9[0xe] = *puVar9;
              puVar9[0x13] = puVar9[5];
              puVar9[0x12] = puVar9[4];
              puVar9[0x17] = puVar9[9];
              puVar9[0x16] = puVar9[8];
              puVar9[0x19] = puVar9[0xb];
              puVar9[0x18] = puVar9[10];
              puVar9[0x1b] = puVar9[0xd];
              puVar9[0x1a] = puVar9[0xc];
              puVar9 = puVar9 + -0xe;
            } while (2 < lVar11);
          }
          uVar6 = *puVar3;
          lVar11 = lVar4 + (long)iVar8 * 0x70;
          uVar13 = uVar13 + 1;
          *(undefined4 *)(lVar4 + (long)iVar8 * 0x70) = uVar6;
          *(undefined4 *)(lVar11 + 4) = puVar3[1];
          *(undefined4 *)(lVar11 + 8) = puVar3[2];
          *(undefined4 *)(lVar11 + 0xc) = puVar3[3];
          *(undefined4 *)(lVar11 + 0x20) = puVar3[8];
          *(undefined4 *)(lVar11 + 0x24) = puVar3[9];
          *(undefined4 *)(lVar11 + 0x28) = puVar3[10];
          *(undefined4 *)(lVar11 + 0x2c) = puVar3[0xb];
          *(undefined4 *)(lVar11 + 0x60) = puVar3[4];
          *(undefined4 *)(lVar11 + 100) = puVar3[5];
          *(undefined4 *)(lVar11 + 0x68) = puVar3[6];
          *(undefined4 *)(param_4 + 0x50) = uVar6;
          *(undefined4 *)(param_4 + 0x54) = *(undefined4 *)(lVar11 + 4);
          *(undefined4 *)(param_4 + 0x58) = *(undefined4 *)(lVar11 + 8);
          *(undefined4 *)(param_4 + 0x5c) = *(undefined4 *)(lVar11 + 0xc);
          *(undefined4 *)(param_4 + 0x60) = *(undefined4 *)(lVar11 + 0x20);
          *(undefined4 *)(param_4 + 100) = *(undefined4 *)(lVar11 + 0x24);
          *(undefined4 *)(param_4 + 0x68) = *(undefined4 *)(lVar11 + 0x28);
          *(undefined4 *)(param_4 + 0x6c) = *(undefined4 *)(lVar11 + 0x2c);
          *(undefined4 *)(param_4 + 0x70) = *(undefined4 *)(lVar11 + 0x40);
          *(undefined4 *)(param_4 + 0x74) = *(undefined4 *)(lVar11 + 0x44);
          *(undefined4 *)(param_4 + 0x78) = *(undefined4 *)(lVar11 + 0x48);
          *(undefined4 *)(param_4 + 0x7c) = *(undefined4 *)(lVar11 + 0x4c);
          *(undefined4 *)(param_4 + 0x80) = *(undefined4 *)(lVar11 + 0x50);
          *(undefined4 *)(param_4 + 0x84) = *(undefined4 *)(lVar11 + 0x54);
          *(undefined4 *)(param_4 + 0x88) = *(undefined4 *)(lVar11 + 0x58);
          *(undefined4 *)(param_4 + 0x8c) = *(undefined4 *)(lVar11 + 0x5c);
          *(undefined4 *)(param_4 + 0x90) = *(undefined4 *)(lVar11 + 0x60);
          *(undefined4 *)(param_4 + 0x94) = *(undefined4 *)(lVar11 + 100);
          *(undefined4 *)(param_4 + 0x98) = *(undefined4 *)(lVar11 + 0x68);
          *(undefined4 *)(param_4 + 0x9c) = *(undefined4 *)(lVar11 + 0x6c);
          if (uVar13 == param_3) break;
          iVar8 = *(int *)(param_1 + 0x1d4);
          param_4 = param_4 + lVar12 * 0x50;
          puVar14 = puVar14 + lVar12 * 0x14;
        }
      }
      break;
    case 1:
      if (0 < (int)param_3) {
        uVar13 = 0;
        puVar14 = (undefined4 *)(param_4 + lVar12 * 0x50 + -0x28);
        iVar8 = iVar5;
        while( true ) {
          iVar7 = *(int *)(param_2 + uVar13 * 4);
          lVar4 = *(long *)(param_1 + 0x1c0);
          iVar8 = (iVar8 + -1) * iVar7;
          puVar3 = (undefined4 *)
                   (*(long *)(param_1 + 0x1b8) + (ulong)(uint)(*(int *)(param_1 + 0x1c8) * iVar7));
          if (2 < iVar5) {
            puVar9 = (undefined8 *)(lVar4 + (lVar12 + -3) * 0x70 + (long)iVar8 * 0x70);
            puVar10 = puVar14;
            lVar11 = lVar12;
            do {
              lVar11 = lVar11 + -1;
              puVar9[0x17] = puVar9[9];
              puVar9[0x16] = puVar9[8];
              puVar9[0x19] = puVar9[0xb];
              puVar9[0x18] = puVar9[10];
              puVar9[0xf] = puVar9[1];
              puVar9[0xe] = *puVar9;
              puVar9[0x1b] = puVar9[0xd];
              puVar9[0x1a] = puVar9[0xc];
              puVar10[-10] = (int)*puVar9;
              puVar10[-9] = *(undefined4 *)((long)puVar9 + 0x74);
              puVar10[-8] = *(undefined4 *)(puVar9 + 0xf);
              puVar10[-7] = *(undefined4 *)((long)puVar9 + 0x7c);
              puVar10[-6] = *(undefined4 *)(puVar9 + 0x12);
              puVar10[-5] = *(undefined4 *)((long)puVar9 + 0x94);
              puVar10[-4] = *(undefined4 *)(puVar9 + 0x13);
              puVar10[-3] = *(undefined4 *)((long)puVar9 + 0x9c);
              puVar10[-2] = *(undefined4 *)(puVar9 + 0x16);
              puVar10[-1] = *(undefined4 *)((long)puVar9 + 0xb4);
              *puVar10 = *(undefined4 *)(puVar9 + 0x17);
              puVar10[1] = *(undefined4 *)((long)puVar9 + 0xbc);
              puVar10[2] = *(undefined4 *)(puVar9 + 0x18);
              puVar10[3] = *(undefined4 *)((long)puVar9 + 0xc4);
              puVar10[4] = *(undefined4 *)(puVar9 + 0x19);
              puVar10[5] = *(undefined4 *)((long)puVar9 + 0xcc);
              puVar10[6] = *(undefined4 *)(puVar9 + 0x1a);
              puVar10[7] = *(undefined4 *)((long)puVar9 + 0xd4);
              puVar10[8] = *(undefined4 *)(puVar9 + 0x1b);
              puVar1 = (undefined4 *)((long)puVar9 + 0xdc);
              puVar9 = puVar9 + -0xe;
              puVar10[9] = *puVar1;
              puVar10 = puVar10 + -0x14;
            } while (2 < lVar11);
          }
          uVar6 = *puVar3;
          lVar11 = lVar4 + (long)iVar8 * 0x70;
          uVar13 = uVar13 + 1;
          *(undefined4 *)(lVar4 + (long)iVar8 * 0x70) = uVar6;
          *(undefined4 *)(lVar11 + 4) = puVar3[1];
          *(undefined4 *)(lVar11 + 8) = puVar3[2];
          *(undefined4 *)(lVar11 + 0xc) = puVar3[3];
          *(undefined4 *)(lVar11 + 0x60) = puVar3[4];
          *(undefined4 *)(lVar11 + 100) = puVar3[5];
          *(undefined4 *)(lVar11 + 0x68) = puVar3[6];
          *(undefined4 *)(param_4 + 0x50) = uVar6;
          *(undefined4 *)(param_4 + 0x54) = *(undefined4 *)(lVar11 + 4);
          *(undefined4 *)(param_4 + 0x58) = *(undefined4 *)(lVar11 + 8);
          *(undefined4 *)(param_4 + 0x5c) = *(undefined4 *)(lVar11 + 0xc);
          *(undefined4 *)(param_4 + 0x60) = *(undefined4 *)(lVar11 + 0x20);
          *(undefined4 *)(param_4 + 100) = *(undefined4 *)(lVar11 + 0x24);
          *(undefined4 *)(param_4 + 0x68) = *(undefined4 *)(lVar11 + 0x28);
          *(undefined4 *)(param_4 + 0x6c) = *(undefined4 *)(lVar11 + 0x2c);
          *(undefined4 *)(param_4 + 0x70) = *(undefined4 *)(lVar11 + 0x40);
          *(undefined4 *)(param_4 + 0x74) = *(undefined4 *)(lVar11 + 0x44);
          *(undefined4 *)(param_4 + 0x78) = *(undefined4 *)(lVar11 + 0x48);
          *(undefined4 *)(param_4 + 0x7c) = *(undefined4 *)(lVar11 + 0x4c);
          *(undefined4 *)(param_4 + 0x80) = *(undefined4 *)(lVar11 + 0x50);
          *(undefined4 *)(param_4 + 0x84) = *(undefined4 *)(lVar11 + 0x54);
          *(undefined4 *)(param_4 + 0x88) = *(undefined4 *)(lVar11 + 0x58);
          *(undefined4 *)(param_4 + 0x8c) = *(undefined4 *)(lVar11 + 0x5c);
          *(undefined4 *)(param_4 + 0x90) = *(undefined4 *)(lVar11 + 0x60);
          *(undefined4 *)(param_4 + 0x94) = *(undefined4 *)(lVar11 + 100);
          *(undefined4 *)(param_4 + 0x98) = *(undefined4 *)(lVar11 + 0x68);
          *(undefined4 *)(param_4 + 0x9c) = *(undefined4 *)(lVar11 + 0x6c);
          if (uVar13 == param_3) break;
          iVar8 = *(int *)(param_1 + 0x1d4);
          param_4 = param_4 + lVar12 * 0x50;
          puVar14 = puVar14 + lVar12 * 0x14;
        }
      }
      break;
    case 2:
      if (0 < (int)param_3) {
        uVar13 = 0;
        puVar14 = (undefined4 *)(param_4 + lVar12 * 0x50 + -0x28);
        iVar8 = iVar5;
        while( true ) {
          iVar7 = *(int *)(param_2 + uVar13 * 4);
          lVar4 = *(long *)(param_1 + 0x1c0);
          iVar8 = (iVar8 + -1) * iVar7;
          puVar3 = (undefined4 *)
                   (*(long *)(param_1 + 0x1b8) + (ulong)(uint)(*(int *)(param_1 + 0x1c8) * iVar7));
          if (2 < iVar5) {
            puVar9 = (undefined8 *)(lVar4 + (lVar12 + -3) * 0x70 + (long)iVar8 * 0x70);
            puVar10 = puVar14;
            lVar11 = lVar12;
            do {
              lVar11 = lVar11 + -1;
              puVar9[0xf] = puVar9[1];
              puVar9[0xe] = *puVar9;
              puVar9[0x13] = puVar9[5];
              puVar9[0x12] = puVar9[4];
              puVar9[0x17] = puVar9[9];
              puVar9[0x16] = puVar9[8];
              puVar9[0x19] = puVar9[0xb];
              puVar9[0x18] = puVar9[10];
              puVar9[0x1b] = puVar9[0xd];
              puVar9[0x1a] = puVar9[0xc];
              puVar10[-10] = *(undefined4 *)(puVar9 + 0xe);
              puVar10[-9] = *(undefined4 *)((long)puVar9 + 0x74);
              puVar10[-8] = *(undefined4 *)(puVar9 + 0xf);
              puVar10[-7] = *(undefined4 *)((long)puVar9 + 0x7c);
              puVar10[-6] = *(undefined4 *)(puVar9 + 0x12);
              puVar10[-5] = *(undefined4 *)((long)puVar9 + 0x94);
              puVar10[-4] = *(undefined4 *)(puVar9 + 0x13);
              puVar10[-3] = *(undefined4 *)((long)puVar9 + 0x9c);
              puVar10[-2] = *(undefined4 *)(puVar9 + 0x16);
              puVar10[-1] = *(undefined4 *)((long)puVar9 + 0xb4);
              *puVar10 = *(undefined4 *)(puVar9 + 0x17);
              puVar10[1] = *(undefined4 *)((long)puVar9 + 0xbc);
              puVar10[2] = *(undefined4 *)(puVar9 + 0x18);
              puVar10[3] = *(undefined4 *)((long)puVar9 + 0xc4);
              puVar10[4] = *(undefined4 *)(puVar9 + 0x19);
              puVar10[5] = *(undefined4 *)((long)puVar9 + 0xcc);
              puVar10[6] = *(undefined4 *)(puVar9 + 0x1a);
              puVar10[7] = *(undefined4 *)((long)puVar9 + 0xd4);
              puVar10[8] = *(undefined4 *)(puVar9 + 0x1b);
              puVar10[9] = *(undefined4 *)((long)puVar9 + 0xdc);
              pfVar2 = (float *)((long)puVar9 + 0x9c);
              puVar9 = puVar9 + -0xe;
              fVar15 = *pfVar2 - *(float *)(param_1 + 0xf8);
              if (fVar15 < 0.0) {
                fVar15 = 0.0;
              }
              puVar10[-3] = fVar15;
              puVar10 = puVar10 + -0x14;
            } while (2 < lVar11);
          }
          uVar6 = *puVar3;
          lVar11 = lVar4 + (long)iVar8 * 0x70;
          uVar13 = uVar13 + 1;
          *(undefined4 *)(lVar4 + (long)iVar8 * 0x70) = uVar6;
          *(undefined4 *)(lVar11 + 4) = puVar3[1];
          *(undefined4 *)(lVar11 + 8) = puVar3[2];
          *(undefined4 *)(lVar11 + 0xc) = puVar3[3];
          *(undefined4 *)(lVar11 + 0x20) = puVar3[8];
          *(undefined4 *)(lVar11 + 0x24) = puVar3[9];
          *(undefined4 *)(lVar11 + 0x28) = puVar3[10];
          *(undefined4 *)(lVar11 + 0x2c) = puVar3[0xb];
          *(undefined4 *)(lVar11 + 0x60) = puVar3[4];
          *(undefined4 *)(lVar11 + 100) = puVar3[5];
          *(undefined4 *)(lVar11 + 0x68) = puVar3[6];
          *(undefined4 *)(param_4 + 0x50) = uVar6;
          *(undefined4 *)(param_4 + 0x54) = *(undefined4 *)(lVar11 + 4);
          *(undefined4 *)(param_4 + 0x58) = *(undefined4 *)(lVar11 + 8);
          *(undefined4 *)(param_4 + 0x5c) = *(undefined4 *)(lVar11 + 0xc);
          *(undefined4 *)(param_4 + 0x60) = *(undefined4 *)(lVar11 + 0x20);
          *(undefined4 *)(param_4 + 100) = *(undefined4 *)(lVar11 + 0x24);
          *(undefined4 *)(param_4 + 0x68) = *(undefined4 *)(lVar11 + 0x28);
          *(undefined4 *)(param_4 + 0x6c) = *(undefined4 *)(lVar11 + 0x2c);
          *(undefined4 *)(param_4 + 0x70) = *(undefined4 *)(lVar11 + 0x40);
          *(undefined4 *)(param_4 + 0x74) = *(undefined4 *)(lVar11 + 0x44);
          *(undefined4 *)(param_4 + 0x78) = *(undefined4 *)(lVar11 + 0x48);
          *(undefined4 *)(param_4 + 0x7c) = *(undefined4 *)(lVar11 + 0x4c);
          *(undefined4 *)(param_4 + 0x80) = *(undefined4 *)(lVar11 + 0x50);
          *(undefined4 *)(param_4 + 0x84) = *(undefined4 *)(lVar11 + 0x54);
          *(undefined4 *)(param_4 + 0x88) = *(undefined4 *)(lVar11 + 0x58);
          *(undefined4 *)(param_4 + 0x8c) = *(undefined4 *)(lVar11 + 0x5c);
          *(undefined4 *)(param_4 + 0x90) = *(undefined4 *)(lVar11 + 0x60);
          *(undefined4 *)(param_4 + 0x94) = *(undefined4 *)(lVar11 + 100);
          *(undefined4 *)(param_4 + 0x98) = *(undefined4 *)(lVar11 + 0x68);
          *(undefined4 *)(param_4 + 0x9c) = *(undefined4 *)(lVar11 + 0x6c);
          fVar15 = *(float *)(lVar11 + 0x2c) - *(float *)(param_1 + 0xf8);
          if (fVar15 < 0.0) {
            fVar15 = 0.0;
          }
          *(float *)(param_4 + 0x6c) = fVar15;
          if (uVar13 == param_3) break;
          iVar8 = *(int *)(param_1 + 0x1d4);
          param_4 = param_4 + lVar12 * 0x50;
          puVar14 = puVar14 + lVar12 * 0x14;
        }
      }
      break;
    case 3:
      if (0 < (int)param_3) {
        uVar13 = 0;
        puVar14 = (undefined4 *)(param_4 + lVar12 * 0x50 + -0x28);
        iVar8 = iVar5;
        while( true ) {
          iVar7 = *(int *)(param_2 + uVar13 * 4);
          lVar4 = *(long *)(param_1 + 0x1c0);
          iVar8 = (iVar8 + -1) * iVar7;
          puVar3 = (undefined4 *)
                   (*(long *)(param_1 + 0x1b8) + (ulong)(uint)(*(int *)(param_1 + 0x1c8) * iVar7));
          if (2 < iVar5) {
            puVar9 = (undefined8 *)(lVar4 + (lVar12 + -3) * 0x70 + (long)iVar8 * 0x70);
            puVar10 = puVar14;
            lVar11 = lVar12;
            do {
              lVar11 = lVar11 + -1;
              *(undefined4 *)((long)puVar9 + 0x9c) = *(undefined4 *)((long)puVar9 + 0x2c);
              puVar9[0x17] = puVar9[9];
              puVar9[0x16] = puVar9[8];
              puVar9[0x19] = puVar9[0xb];
              puVar9[0x18] = puVar9[10];
              *(undefined4 *)(puVar9 + 0x1a) = *(undefined4 *)(puVar9 + 0xc);
              *(undefined4 *)((long)puVar9 + 0xd4) = *(undefined4 *)((long)puVar9 + 100);
              puVar9[0xf] = puVar9[1];
              puVar9[0xe] = *puVar9;
              *(undefined4 *)(puVar9 + 0x1b) = *(undefined4 *)(puVar9 + 0xd);
              *(undefined4 *)((long)puVar9 + 0xdc) = *(undefined4 *)((long)puVar9 + 0x6c);
              puVar10[-10] = (int)*puVar9;
              puVar10[-9] = *(undefined4 *)((long)puVar9 + 0x74);
              puVar10[-8] = *(undefined4 *)(puVar9 + 0xf);
              puVar10[-7] = *(undefined4 *)((long)puVar9 + 0x7c);
              puVar10[-6] = *(undefined4 *)(puVar9 + 0x12);
              puVar10[-5] = *(undefined4 *)((long)puVar9 + 0x94);
              puVar10[-4] = *(undefined4 *)(puVar9 + 0x13);
              puVar10[-3] = *(undefined4 *)((long)puVar9 + 0x9c);
              puVar10[-2] = *(undefined4 *)(puVar9 + 0x16);
              puVar10[-1] = *(undefined4 *)((long)puVar9 + 0xb4);
              *puVar10 = *(undefined4 *)(puVar9 + 0x17);
              puVar10[1] = *(undefined4 *)((long)puVar9 + 0xbc);
              puVar10[2] = *(undefined4 *)(puVar9 + 0x18);
              puVar10[3] = *(undefined4 *)((long)puVar9 + 0xc4);
              puVar10[4] = *(undefined4 *)(puVar9 + 0x19);
              puVar10[5] = *(undefined4 *)((long)puVar9 + 0xcc);
              puVar10[6] = *(undefined4 *)(puVar9 + 0x1a);
              puVar10[7] = *(undefined4 *)((long)puVar9 + 0xd4);
              puVar10[8] = *(undefined4 *)(puVar9 + 0x1b);
              puVar10[9] = *(undefined4 *)((long)puVar9 + 0xdc);
              pfVar2 = (float *)((long)puVar9 + 0x9c);
              puVar9 = puVar9 + -0xe;
              fVar15 = *pfVar2 - *(float *)(param_1 + 0xf8);
              if (fVar15 < 0.0) {
                fVar15 = 0.0;
              }
              puVar10[-3] = fVar15;
              puVar10 = puVar10 + -0x14;
            } while (2 < lVar11);
          }
          uVar6 = *puVar3;
          lVar11 = lVar4 + (long)iVar8 * 0x70;
          uVar13 = uVar13 + 1;
          *(undefined4 *)(lVar4 + (long)iVar8 * 0x70) = uVar6;
          *(undefined4 *)(lVar11 + 4) = puVar3[1];
          *(undefined4 *)(lVar11 + 8) = puVar3[2];
          *(undefined4 *)(lVar11 + 0xc) = puVar3[3];
          *(undefined4 *)(lVar11 + 0x2c) = puVar3[0xb];
          *(undefined4 *)(lVar11 + 0x60) = puVar3[4];
          *(undefined4 *)(lVar11 + 100) = puVar3[5];
          *(undefined4 *)(lVar11 + 0x68) = puVar3[6];
          *(undefined4 *)(param_4 + 0x50) = uVar6;
          *(undefined4 *)(param_4 + 0x54) = *(undefined4 *)(lVar11 + 4);
          *(undefined4 *)(param_4 + 0x58) = *(undefined4 *)(lVar11 + 8);
          *(undefined4 *)(param_4 + 0x5c) = *(undefined4 *)(lVar11 + 0xc);
          *(undefined4 *)(param_4 + 0x60) = *(undefined4 *)(lVar11 + 0x20);
          *(undefined4 *)(param_4 + 100) = *(undefined4 *)(lVar11 + 0x24);
          *(undefined4 *)(param_4 + 0x68) = *(undefined4 *)(lVar11 + 0x28);
          *(undefined4 *)(param_4 + 0x6c) = *(undefined4 *)(lVar11 + 0x2c);
          *(undefined4 *)(param_4 + 0x70) = *(undefined4 *)(lVar11 + 0x40);
          *(undefined4 *)(param_4 + 0x74) = *(undefined4 *)(lVar11 + 0x44);
          *(undefined4 *)(param_4 + 0x78) = *(undefined4 *)(lVar11 + 0x48);
          *(undefined4 *)(param_4 + 0x7c) = *(undefined4 *)(lVar11 + 0x4c);
          *(undefined4 *)(param_4 + 0x80) = *(undefined4 *)(lVar11 + 0x50);
          *(undefined4 *)(param_4 + 0x84) = *(undefined4 *)(lVar11 + 0x54);
          *(undefined4 *)(param_4 + 0x88) = *(undefined4 *)(lVar11 + 0x58);
          *(undefined4 *)(param_4 + 0x8c) = *(undefined4 *)(lVar11 + 0x5c);
          *(undefined4 *)(param_4 + 0x90) = *(undefined4 *)(lVar11 + 0x60);
          *(undefined4 *)(param_4 + 0x94) = *(undefined4 *)(lVar11 + 100);
          *(undefined4 *)(param_4 + 0x98) = *(undefined4 *)(lVar11 + 0x68);
          *(undefined4 *)(param_4 + 0x9c) = *(undefined4 *)(lVar11 + 0x6c);
          fVar15 = *(float *)(lVar11 + 0x2c) - *(float *)(param_1 + 0xf8);
          if (fVar15 < 0.0) {
            fVar15 = 0.0;
          }
          *(float *)(param_4 + 0x6c) = fVar15;
          if (uVar13 == param_3) break;
          iVar8 = *(int *)(param_1 + 0x1d4);
          param_4 = param_4 + lVar12 * 0x50;
          puVar14 = puVar14 + lVar12 * 0x14;
        }
      }
    }
  }
  return;
}

// ==== Aska::IParticleObject::Tail_ConnectionMode_NoCopy(int const*, int, Aska::ParticleContext*)
// vaddr 0x21a319c | ghidra 0x22a319c | size 2400 | symbol _ZN4Aska15IParticleObject26Tail_ConnectionMode_NoCopyEPKiiPNS_15ParticleContextE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObject26Tail_ConnectionMode_NoCopyEPKiiPNS_15ParticleContextE
               (long param_1,long param_2,uint param_3,long param_4)

{
  float *pfVar1;
  long lVar2;
  long lVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  undefined8 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  long lVar11;
  long lVar12;
  ulong uVar13;
  undefined4 *puVar14;
  float fVar15;
  
  if (*(byte *)(param_1 + 0x1f8) < 4) {
    iVar4 = *(int *)(param_1 + 0x1d4);
    lVar12 = (long)iVar4;
    switch(*(byte *)(param_1 + 0x1f8)) {
    case 0:
      if (0 < (int)param_3) {
        uVar13 = 0;
        puVar14 = (undefined4 *)(param_4 + lVar12 * 0x50 + -0x28);
        iVar5 = iVar4;
        while( true ) {
          iVar6 = *(int *)(param_2 + uVar13 * 4);
          lVar3 = *(long *)(param_1 + 0x1c0);
          lVar7 = ((long)iVar5 + -1) * (long)iVar6;
          lVar2 = *(long *)(param_1 + 0x1b8) + (ulong)(uint)(*(int *)(param_1 + 0x1c8) * iVar6);
          if (2 < iVar4) {
            puVar8 = (undefined8 *)(lVar3 + (lVar12 + -2) * 0x70 + lVar7 * 0x70 + -0x50);
            puVar10 = puVar14;
            lVar11 = lVar12;
            do {
              lVar11 = lVar11 + -1;
              puVar10[-10] = *(undefined4 *)(puVar8 + 10);
              puVar10[-9] = *(undefined4 *)((long)puVar8 + 0x54);
              puVar10[-8] = *(undefined4 *)(puVar8 + 0xb);
              puVar10[-7] = *(undefined4 *)((long)puVar8 + 0x5c);
              puVar10[-6] = *(undefined4 *)(puVar8 + 0xe);
              puVar10[-5] = *(undefined4 *)((long)puVar8 + 0x74);
              puVar10[-4] = *(undefined4 *)(puVar8 + 0xf);
              puVar10[-3] = *(undefined4 *)((long)puVar8 + 0x7c);
              puVar10[-2] = *(undefined4 *)(puVar8 + 0x12);
              puVar10[-1] = *(undefined4 *)((long)puVar8 + 0x94);
              *puVar10 = *(undefined4 *)(puVar8 + 0x13);
              puVar10[1] = *(undefined4 *)((long)puVar8 + 0x9c);
              puVar10[2] = *(undefined4 *)(puVar8 + 0x14);
              puVar10[3] = *(undefined4 *)((long)puVar8 + 0xa4);
              puVar10[4] = *(undefined4 *)(puVar8 + 0x15);
              puVar10[5] = *(undefined4 *)((long)puVar8 + 0xac);
              puVar10[6] = *(undefined4 *)(puVar8 + 0x16);
              puVar10[7] = *(undefined4 *)((long)puVar8 + 0xb4);
              puVar10[8] = *(undefined4 *)(puVar8 + 0x17);
              puVar10[9] = *(undefined4 *)((long)puVar8 + 0xbc);
              puVar10 = puVar10 + -0x14;
              puVar8[0xf] = puVar8[1];
              puVar8[0xe] = *puVar8;
              puVar8[0x13] = puVar8[5];
              puVar8[0x12] = puVar8[4];
              puVar8[0x15] = puVar8[7];
              puVar8[0x14] = puVar8[6];
              puVar8[0x17] = puVar8[9];
              puVar8[0x16] = puVar8[8];
              puVar8 = puVar8 + -0xe;
            } while (2 < lVar11);
          }
          lVar11 = lVar3 + lVar7 * 0x70;
          uVar13 = uVar13 + 1;
          *(undefined4 *)(lVar11 + 0x20) = *(undefined4 *)(lVar2 + 0x20);
          *(undefined4 *)(lVar11 + 0x24) = *(undefined4 *)(lVar2 + 0x24);
          *(undefined4 *)(lVar11 + 0x28) = *(undefined4 *)(lVar2 + 0x28);
          *(undefined4 *)(lVar11 + 0x2c) = *(undefined4 *)(lVar2 + 0x2c);
          *(undefined4 *)(lVar11 + 0x60) = *(undefined4 *)(lVar2 + 0x10);
          *(undefined4 *)(lVar11 + 100) = *(undefined4 *)(lVar2 + 0x14);
          *(undefined4 *)(lVar11 + 0x68) = *(undefined4 *)(lVar2 + 0x18);
          *(undefined4 *)(param_4 + 0x50) = *(undefined4 *)(lVar3 + lVar7 * 0x70);
          *(undefined4 *)(param_4 + 0x54) = *(undefined4 *)(lVar11 + 4);
          *(undefined4 *)(param_4 + 0x58) = *(undefined4 *)(lVar11 + 8);
          *(undefined4 *)(param_4 + 0x5c) = *(undefined4 *)(lVar11 + 0xc);
          *(undefined4 *)(param_4 + 0x60) = *(undefined4 *)(lVar11 + 0x20);
          *(undefined4 *)(param_4 + 100) = *(undefined4 *)(lVar11 + 0x24);
          *(undefined4 *)(param_4 + 0x68) = *(undefined4 *)(lVar11 + 0x28);
          *(undefined4 *)(param_4 + 0x6c) = *(undefined4 *)(lVar11 + 0x2c);
          *(undefined4 *)(param_4 + 0x70) = *(undefined4 *)(lVar11 + 0x40);
          *(undefined4 *)(param_4 + 0x74) = *(undefined4 *)(lVar11 + 0x44);
          *(undefined4 *)(param_4 + 0x78) = *(undefined4 *)(lVar11 + 0x48);
          *(undefined4 *)(param_4 + 0x7c) = *(undefined4 *)(lVar11 + 0x4c);
          *(undefined4 *)(param_4 + 0x80) = *(undefined4 *)(lVar11 + 0x50);
          *(undefined4 *)(param_4 + 0x84) = *(undefined4 *)(lVar11 + 0x54);
          *(undefined4 *)(param_4 + 0x88) = *(undefined4 *)(lVar11 + 0x58);
          *(undefined4 *)(param_4 + 0x8c) = *(undefined4 *)(lVar11 + 0x5c);
          *(undefined4 *)(param_4 + 0x90) = *(undefined4 *)(lVar11 + 0x60);
          *(undefined4 *)(param_4 + 0x94) = *(undefined4 *)(lVar11 + 100);
          *(undefined4 *)(param_4 + 0x98) = *(undefined4 *)(lVar11 + 0x68);
          *(undefined4 *)(param_4 + 0x9c) = *(undefined4 *)(lVar11 + 0x6c);
          if (uVar13 == param_3) break;
          iVar5 = *(int *)(param_1 + 0x1d4);
          param_4 = param_4 + lVar12 * 0x50;
          puVar14 = puVar14 + lVar12 * 0x14;
        }
      }
      break;
    case 1:
      if (0 < (int)param_3) {
        uVar13 = 0;
        puVar14 = (undefined4 *)(param_4 + lVar12 * 0x50 + -0x28);
        iVar5 = iVar4;
        while( true ) {
          iVar6 = *(int *)(param_2 + uVar13 * 4);
          lVar3 = *(long *)(param_1 + 0x1c0);
          lVar7 = ((long)iVar5 + -1) * (long)iVar6;
          lVar2 = *(long *)(param_1 + 0x1b8) + (ulong)(uint)(*(int *)(param_1 + 0x1c8) * iVar6);
          if (2 < iVar4) {
            puVar8 = (undefined8 *)(lVar3 + (lVar12 + -2) * 0x70 + lVar7 * 0x70 + -0x30);
            puVar10 = puVar14;
            lVar11 = lVar12;
            do {
              lVar11 = lVar11 + -1;
              puVar8[0xf] = puVar8[1];
              puVar8[0xe] = *puVar8;
              puVar8[0x11] = puVar8[3];
              puVar8[0x10] = puVar8[2];
              puVar8[0x13] = puVar8[5];
              puVar8[0x12] = puVar8[4];
              puVar10[-10] = *(undefined4 *)(puVar8 + 6);
              puVar10[-9] = *(undefined4 *)((long)puVar8 + 0x34);
              puVar10[-8] = *(undefined4 *)(puVar8 + 7);
              puVar10[-7] = *(undefined4 *)((long)puVar8 + 0x3c);
              puVar10[-6] = *(undefined4 *)(puVar8 + 10);
              puVar10[-5] = *(undefined4 *)((long)puVar8 + 0x54);
              puVar10[-4] = *(undefined4 *)(puVar8 + 0xb);
              puVar10[-3] = *(undefined4 *)((long)puVar8 + 0x5c);
              puVar10[-2] = *(undefined4 *)(puVar8 + 0xe);
              puVar10[-1] = *(undefined4 *)((long)puVar8 + 0x74);
              *puVar10 = *(undefined4 *)(puVar8 + 0xf);
              puVar10[1] = *(undefined4 *)((long)puVar8 + 0x7c);
              puVar10[2] = *(undefined4 *)(puVar8 + 0x10);
              puVar10[3] = *(undefined4 *)((long)puVar8 + 0x84);
              puVar10[4] = *(undefined4 *)(puVar8 + 0x11);
              puVar10[5] = *(undefined4 *)((long)puVar8 + 0x8c);
              puVar10[6] = *(undefined4 *)(puVar8 + 0x12);
              puVar10[7] = *(undefined4 *)((long)puVar8 + 0x94);
              puVar10[8] = *(undefined4 *)(puVar8 + 0x13);
              puVar9 = (undefined4 *)((long)puVar8 + 0x9c);
              puVar8 = puVar8 + -0xe;
              puVar10[9] = *puVar9;
              puVar10 = puVar10 + -0x14;
            } while (2 < lVar11);
          }
          lVar11 = lVar3 + lVar7 * 0x70;
          uVar13 = uVar13 + 1;
          *(undefined4 *)(lVar11 + 0x60) = *(undefined4 *)(lVar2 + 0x10);
          *(undefined4 *)(lVar11 + 100) = *(undefined4 *)(lVar2 + 0x14);
          *(undefined4 *)(lVar11 + 0x68) = *(undefined4 *)(lVar2 + 0x18);
          *(undefined4 *)(param_4 + 0x50) = *(undefined4 *)(lVar3 + lVar7 * 0x70);
          *(undefined4 *)(param_4 + 0x54) = *(undefined4 *)(lVar11 + 4);
          *(undefined4 *)(param_4 + 0x58) = *(undefined4 *)(lVar11 + 8);
          *(undefined4 *)(param_4 + 0x5c) = *(undefined4 *)(lVar11 + 0xc);
          *(undefined4 *)(param_4 + 0x60) = *(undefined4 *)(lVar11 + 0x20);
          *(undefined4 *)(param_4 + 100) = *(undefined4 *)(lVar11 + 0x24);
          *(undefined4 *)(param_4 + 0x68) = *(undefined4 *)(lVar11 + 0x28);
          *(undefined4 *)(param_4 + 0x6c) = *(undefined4 *)(lVar11 + 0x2c);
          *(undefined4 *)(param_4 + 0x70) = *(undefined4 *)(lVar11 + 0x40);
          *(undefined4 *)(param_4 + 0x74) = *(undefined4 *)(lVar11 + 0x44);
          *(undefined4 *)(param_4 + 0x78) = *(undefined4 *)(lVar11 + 0x48);
          *(undefined4 *)(param_4 + 0x7c) = *(undefined4 *)(lVar11 + 0x4c);
          *(undefined4 *)(param_4 + 0x80) = *(undefined4 *)(lVar11 + 0x50);
          *(undefined4 *)(param_4 + 0x84) = *(undefined4 *)(lVar11 + 0x54);
          *(undefined4 *)(param_4 + 0x88) = *(undefined4 *)(lVar11 + 0x58);
          *(undefined4 *)(param_4 + 0x8c) = *(undefined4 *)(lVar11 + 0x5c);
          *(undefined4 *)(param_4 + 0x90) = *(undefined4 *)(lVar11 + 0x60);
          *(undefined4 *)(param_4 + 0x94) = *(undefined4 *)(lVar11 + 100);
          *(undefined4 *)(param_4 + 0x98) = *(undefined4 *)(lVar11 + 0x68);
          *(undefined4 *)(param_4 + 0x9c) = *(undefined4 *)(lVar11 + 0x6c);
          if (uVar13 == param_3) break;
          iVar5 = *(int *)(param_1 + 0x1d4);
          param_4 = param_4 + lVar12 * 0x50;
          puVar14 = puVar14 + lVar12 * 0x14;
        }
      }
      break;
    case 2:
      if (0 < (int)param_3) {
        uVar13 = 0;
        puVar14 = (undefined4 *)(param_4 + lVar12 * 0x50 + -0x28);
        iVar5 = iVar4;
        while( true ) {
          iVar6 = *(int *)(param_2 + uVar13 * 4);
          lVar3 = *(long *)(param_1 + 0x1c0);
          lVar7 = ((long)iVar5 + -1) * (long)iVar6;
          lVar2 = *(long *)(param_1 + 0x1b8) + (ulong)(uint)(*(int *)(param_1 + 0x1c8) * iVar6);
          if (2 < iVar4) {
            puVar8 = (undefined8 *)(lVar3 + (lVar12 + -2) * 0x70 + lVar7 * 0x70 + -0x50);
            puVar10 = puVar14;
            lVar11 = lVar12;
            do {
              lVar11 = lVar11 + -1;
              puVar8[0xf] = puVar8[1];
              puVar8[0xe] = *puVar8;
              puVar8[0x13] = puVar8[5];
              puVar8[0x12] = puVar8[4];
              puVar8[0x15] = puVar8[7];
              puVar8[0x14] = puVar8[6];
              puVar8[0x17] = puVar8[9];
              puVar8[0x16] = puVar8[8];
              puVar10[-10] = *(undefined4 *)(puVar8 + 10);
              puVar10[-9] = *(undefined4 *)((long)puVar8 + 0x54);
              puVar10[-8] = *(undefined4 *)(puVar8 + 0xb);
              puVar10[-7] = *(undefined4 *)((long)puVar8 + 0x5c);
              puVar10[-6] = *(undefined4 *)(puVar8 + 0xe);
              puVar10[-5] = *(undefined4 *)((long)puVar8 + 0x74);
              puVar10[-4] = *(undefined4 *)(puVar8 + 0xf);
              puVar10[-3] = *(undefined4 *)((long)puVar8 + 0x7c);
              puVar10[-2] = *(undefined4 *)(puVar8 + 0x12);
              puVar10[-1] = *(undefined4 *)((long)puVar8 + 0x94);
              *puVar10 = *(undefined4 *)(puVar8 + 0x13);
              puVar10[1] = *(undefined4 *)((long)puVar8 + 0x9c);
              puVar10[2] = *(undefined4 *)(puVar8 + 0x14);
              puVar10[3] = *(undefined4 *)((long)puVar8 + 0xa4);
              puVar10[4] = *(undefined4 *)(puVar8 + 0x15);
              puVar10[5] = *(undefined4 *)((long)puVar8 + 0xac);
              puVar10[6] = *(undefined4 *)(puVar8 + 0x16);
              puVar10[7] = *(undefined4 *)((long)puVar8 + 0xb4);
              puVar10[8] = *(undefined4 *)(puVar8 + 0x17);
              puVar10[9] = *(undefined4 *)((long)puVar8 + 0xbc);
              pfVar1 = (float *)((long)puVar8 + 0x7c);
              puVar8 = puVar8 + -0xe;
              fVar15 = *pfVar1 - *(float *)(param_1 + 0xf8);
              if (fVar15 < 0.0) {
                fVar15 = 0.0;
              }
              puVar10[-3] = fVar15;
              puVar10 = puVar10 + -0x14;
            } while (2 < lVar11);
          }
          lVar11 = lVar3 + lVar7 * 0x70;
          uVar13 = uVar13 + 1;
          *(undefined4 *)(lVar11 + 0x20) = *(undefined4 *)(lVar2 + 0x20);
          *(undefined4 *)(lVar11 + 0x24) = *(undefined4 *)(lVar2 + 0x24);
          *(undefined4 *)(lVar11 + 0x28) = *(undefined4 *)(lVar2 + 0x28);
          *(undefined4 *)(lVar11 + 0x2c) = *(undefined4 *)(lVar2 + 0x2c);
          *(undefined4 *)(lVar11 + 0x60) = *(undefined4 *)(lVar2 + 0x10);
          *(undefined4 *)(lVar11 + 100) = *(undefined4 *)(lVar2 + 0x14);
          *(undefined4 *)(lVar11 + 0x68) = *(undefined4 *)(lVar2 + 0x18);
          *(undefined4 *)(param_4 + 0x50) = *(undefined4 *)(lVar3 + lVar7 * 0x70);
          *(undefined4 *)(param_4 + 0x54) = *(undefined4 *)(lVar11 + 4);
          *(undefined4 *)(param_4 + 0x58) = *(undefined4 *)(lVar11 + 8);
          *(undefined4 *)(param_4 + 0x5c) = *(undefined4 *)(lVar11 + 0xc);
          *(undefined4 *)(param_4 + 0x60) = *(undefined4 *)(lVar11 + 0x20);
          *(undefined4 *)(param_4 + 100) = *(undefined4 *)(lVar11 + 0x24);
          *(undefined4 *)(param_4 + 0x68) = *(undefined4 *)(lVar11 + 0x28);
          *(undefined4 *)(param_4 + 0x6c) = *(undefined4 *)(lVar11 + 0x2c);
          *(undefined4 *)(param_4 + 0x70) = *(undefined4 *)(lVar11 + 0x40);
          *(undefined4 *)(param_4 + 0x74) = *(undefined4 *)(lVar11 + 0x44);
          *(undefined4 *)(param_4 + 0x78) = *(undefined4 *)(lVar11 + 0x48);
          *(undefined4 *)(param_4 + 0x7c) = *(undefined4 *)(lVar11 + 0x4c);
          *(undefined4 *)(param_4 + 0x80) = *(undefined4 *)(lVar11 + 0x50);
          *(undefined4 *)(param_4 + 0x84) = *(undefined4 *)(lVar11 + 0x54);
          *(undefined4 *)(param_4 + 0x88) = *(undefined4 *)(lVar11 + 0x58);
          *(undefined4 *)(param_4 + 0x8c) = *(undefined4 *)(lVar11 + 0x5c);
          *(undefined4 *)(param_4 + 0x90) = *(undefined4 *)(lVar11 + 0x60);
          *(undefined4 *)(param_4 + 0x94) = *(undefined4 *)(lVar11 + 100);
          *(undefined4 *)(param_4 + 0x98) = *(undefined4 *)(lVar11 + 0x68);
          *(undefined4 *)(param_4 + 0x9c) = *(undefined4 *)(lVar11 + 0x6c);
          fVar15 = *(float *)(lVar11 + 0x2c) - *(float *)(param_1 + 0xf8);
          if (fVar15 < 0.0) {
            fVar15 = 0.0;
          }
          *(float *)(param_4 + 0x6c) = fVar15;
          if (uVar13 == param_3) break;
          iVar5 = *(int *)(param_1 + 0x1d4);
          param_4 = param_4 + lVar12 * 0x50;
          puVar14 = puVar14 + lVar12 * 0x14;
        }
      }
      break;
    case 3:
      if (0 < (int)param_3) {
        uVar13 = 0;
        puVar14 = (undefined4 *)(param_4 + lVar12 * 0x50 + -0x28);
        iVar5 = iVar4;
        while( true ) {
          iVar6 = *(int *)(param_2 + uVar13 * 4);
          lVar3 = *(long *)(param_1 + 0x1c0);
          lVar7 = ((long)iVar5 + -1) * (long)iVar6;
          lVar2 = *(long *)(param_1 + 0x1b8) + (ulong)(uint)(*(int *)(param_1 + 0x1c8) * iVar6);
          if (2 < iVar4) {
            puVar9 = (undefined4 *)(lVar3 + (lVar12 + -2) * 0x70 + lVar7 * 0x70 + -0x44);
            puVar10 = puVar14;
            lVar11 = lVar12;
            do {
              *(undefined8 *)(puVar9 + 0x23) = *(undefined8 *)(puVar9 + 7);
              *(undefined8 *)(puVar9 + 0x21) = *(undefined8 *)(puVar9 + 5);
              puVar9[0x1c] = *puVar9;
              *(undefined8 *)(puVar9 + 0x27) = *(undefined8 *)(puVar9 + 0xb);
              *(undefined8 *)(puVar9 + 0x25) = *(undefined8 *)(puVar9 + 9);
              lVar11 = lVar11 + -1;
              *(undefined8 *)(puVar9 + 0x2b) = *(undefined8 *)(puVar9 + 0xf);
              *(undefined8 *)(puVar9 + 0x29) = *(undefined8 *)(puVar9 + 0xd);
              puVar10[-10] = puVar9[0x11];
              puVar10[-9] = puVar9[0x12];
              puVar10[-8] = puVar9[0x13];
              puVar10[-7] = puVar9[0x14];
              puVar10[-6] = puVar9[0x19];
              puVar10[-5] = puVar9[0x1a];
              puVar10[-4] = puVar9[0x1b];
              puVar10[-3] = puVar9[0x1c];
              puVar10[-2] = puVar9[0x21];
              puVar10[-1] = puVar9[0x22];
              *puVar10 = puVar9[0x23];
              puVar10[1] = puVar9[0x24];
              puVar10[2] = puVar9[0x25];
              puVar10[3] = puVar9[0x26];
              puVar10[4] = puVar9[0x27];
              puVar10[5] = puVar9[0x28];
              puVar10[6] = puVar9[0x29];
              puVar10[7] = puVar9[0x2a];
              puVar10[8] = puVar9[0x2b];
              puVar10[9] = puVar9[0x2c];
              pfVar1 = (float *)(puVar9 + 0x1c);
              puVar9 = puVar9 + -0x1c;
              fVar15 = *pfVar1 - *(float *)(param_1 + 0xf8);
              if (fVar15 < 0.0) {
                fVar15 = 0.0;
              }
              puVar10[-3] = fVar15;
              puVar10 = puVar10 + -0x14;
            } while (2 < lVar11);
          }
          lVar11 = lVar3 + lVar7 * 0x70;
          uVar13 = uVar13 + 1;
          *(undefined4 *)(lVar11 + 0x2c) = *(undefined4 *)(lVar2 + 0x2c);
          *(undefined4 *)(lVar11 + 0x60) = *(undefined4 *)(lVar2 + 0x10);
          *(undefined4 *)(lVar11 + 100) = *(undefined4 *)(lVar2 + 0x14);
          *(undefined4 *)(lVar11 + 0x68) = *(undefined4 *)(lVar2 + 0x18);
          *(undefined4 *)(param_4 + 0x50) = *(undefined4 *)(lVar3 + lVar7 * 0x70);
          *(undefined4 *)(param_4 + 0x54) = *(undefined4 *)(lVar11 + 4);
          *(undefined4 *)(param_4 + 0x58) = *(undefined4 *)(lVar11 + 8);
          *(undefined4 *)(param_4 + 0x5c) = *(undefined4 *)(lVar11 + 0xc);
          *(undefined4 *)(param_4 + 0x60) = *(undefined4 *)(lVar11 + 0x20);
          *(undefined4 *)(param_4 + 100) = *(undefined4 *)(lVar11 + 0x24);
          *(undefined4 *)(param_4 + 0x68) = *(undefined4 *)(lVar11 + 0x28);
          *(undefined4 *)(param_4 + 0x6c) = *(undefined4 *)(lVar11 + 0x2c);
          *(undefined4 *)(param_4 + 0x70) = *(undefined4 *)(lVar11 + 0x40);
          *(undefined4 *)(param_4 + 0x74) = *(undefined4 *)(lVar11 + 0x44);
          *(undefined4 *)(param_4 + 0x78) = *(undefined4 *)(lVar11 + 0x48);
          *(undefined4 *)(param_4 + 0x7c) = *(undefined4 *)(lVar11 + 0x4c);
          *(undefined4 *)(param_4 + 0x80) = *(undefined4 *)(lVar11 + 0x50);
          *(undefined4 *)(param_4 + 0x84) = *(undefined4 *)(lVar11 + 0x54);
          *(undefined4 *)(param_4 + 0x88) = *(undefined4 *)(lVar11 + 0x58);
          *(undefined4 *)(param_4 + 0x8c) = *(undefined4 *)(lVar11 + 0x5c);
          *(undefined4 *)(param_4 + 0x90) = *(undefined4 *)(lVar11 + 0x60);
          *(undefined4 *)(param_4 + 0x94) = *(undefined4 *)(lVar11 + 100);
          *(undefined4 *)(param_4 + 0x98) = *(undefined4 *)(lVar11 + 0x68);
          *(undefined4 *)(param_4 + 0x9c) = *(undefined4 *)(lVar11 + 0x6c);
          fVar15 = *(float *)(lVar11 + 0x2c) - *(float *)(param_1 + 0xf8);
          if (fVar15 < 0.0) {
            fVar15 = 0.0;
          }
          *(float *)(param_4 + 0x6c) = fVar15;
          if (uVar13 == param_3) break;
          iVar5 = *(int *)(param_1 + 0x1d4);
          param_4 = param_4 + lVar12 * 0x50;
          puVar14 = puVar14 + lVar12 * 0x14;
        }
      }
    }
  }
  return;
}

// ==== Aska::IParticleObject::Tail_ConnectionMode_Relative(int const*, int, Aska::ParticleContext*)
// vaddr 0x21a3afc | ghidra 0x22a3afc | size 2344 | symbol _ZN4Aska15IParticleObject28Tail_ConnectionMode_RelativeEPKiiPNS_15ParticleContextE | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska15IParticleObject28Tail_ConnectionMode_RelativeEPKiiPNS_15ParticleContextE
               (long param_1,long param_2,uint param_3,long param_4)

{
  float *pfVar1;
  long lVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  long lVar7;
  ulong uVar8;
  undefined4 *puVar9;
  long lVar10;
  long lVar11;
  undefined8 *puVar12;
  undefined4 *puVar13;
  ulong uVar14;
  long lVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  
  iVar4 = *(int *)(param_1 + 0x1dc);
  if (*(int *)(param_1 + 0x1d0) <= *(int *)(param_1 + 0x1dc)) {
    iVar4 = *(int *)(param_1 + 0x1d0) + -1;
  }
  pfVar1 = (float *)(*(long *)(param_1 + 0x1b8) + (ulong)(uint)(*(int *)(param_1 + 0x1c8) * iVar4));
  fVar19 = *pfVar1;
  fVar20 = pfVar1[1];
  fVar17 = pfVar1[2];
  fVar3 = pfVar1[3];
  iVar4 = *(int *)(param_1 + 0x1d4);
  lVar15 = (long)iVar4;
  fVar18 = fVar19 * fVar19 + fVar20 * fVar20 + fVar17 * fVar17;
  fVar16 = SQRT(fVar18);
  uVar14 = (ulong)param_3;
  if (NAN(fVar16)) {
    fVar16 = (float)sqrtf(fVar18);
  }
  if (_UNK_027e519c <= fVar16) {
    fVar16 = 1.0 / fVar16;
    fVar19 = fVar16 * fVar19;
    fVar20 = fVar16 * fVar20;
    fVar17 = fVar16 * fVar17;
  }
  if (*(byte *)(param_1 + 0x1f8) < 4) {
    fVar16 = *(float *)(param_1 + 0xfc);
    fVar19 = fVar16 * fVar19;
    fVar20 = fVar16 * fVar20;
    fVar16 = fVar16 * fVar17;
    switch(*(byte *)(param_1 + 0x1f8)) {
    case 0:
      if (0 < (int)param_3) {
        uVar8 = 0;
        puVar9 = (undefined4 *)(param_4 + lVar15 * 0x50 + -0x28);
        do {
          iVar5 = *(int *)(param_2 + uVar8 * 4);
          lVar10 = *(long *)(param_1 + 0x1c0);
          lVar2 = *(long *)(param_1 + 0x1b8) + (ulong)(uint)(*(int *)(param_1 + 0x1c8) * iVar5);
          lVar11 = ((long)*(int *)(param_1 + 0x1d4) + -1) * (long)iVar5;
          if (2 < iVar4) {
            puVar12 = (undefined8 *)(lVar10 + (lVar15 + -2) * 0x70 + lVar11 * 0x70 + -0x50);
            puVar6 = puVar9;
            lVar7 = lVar15;
            do {
              lVar7 = lVar7 + -1;
              puVar12[0xf] = puVar12[1];
              puVar12[0xe] = *puVar12;
              puVar12[0x13] = puVar12[5];
              puVar12[0x12] = puVar12[4];
              puVar12[0x15] = puVar12[7];
              puVar12[0x14] = puVar12[6];
              puVar12[0x17] = puVar12[9];
              puVar12[0x16] = puVar12[8];
              puVar6[-10] = fVar19;
              puVar6[-9] = fVar20;
              puVar6[-8] = fVar16;
              puVar6[-7] = fVar3;
              puVar6[-6] = *(undefined4 *)(puVar12 + 0xe);
              puVar6[-5] = *(undefined4 *)((long)puVar12 + 0x74);
              puVar6[-4] = *(undefined4 *)(puVar12 + 0xf);
              puVar6[-3] = *(undefined4 *)((long)puVar12 + 0x7c);
              puVar6[-2] = *(undefined4 *)(puVar12 + 0x12);
              puVar6[-1] = *(undefined4 *)((long)puVar12 + 0x94);
              *puVar6 = *(undefined4 *)(puVar12 + 0x13);
              puVar6[1] = *(undefined4 *)((long)puVar12 + 0x9c);
              puVar6[2] = *(undefined4 *)(puVar12 + 0x14);
              puVar6[3] = *(undefined4 *)((long)puVar12 + 0xa4);
              puVar6[4] = *(undefined4 *)(puVar12 + 0x15);
              puVar6[5] = *(undefined4 *)((long)puVar12 + 0xac);
              puVar6[6] = *(undefined4 *)(puVar12 + 0x16);
              puVar6[7] = *(undefined4 *)((long)puVar12 + 0xb4);
              puVar6[8] = *(undefined4 *)(puVar12 + 0x17);
              puVar13 = (undefined4 *)((long)puVar12 + 0xbc);
              puVar12 = puVar12 + -0xe;
              puVar6[9] = *puVar13;
              puVar6 = puVar6 + -0x14;
            } while (2 < lVar7);
          }
          lVar10 = lVar10 + lVar11 * 0x70;
          uVar8 = uVar8 + 1;
          *(undefined4 *)(lVar10 + 0x20) = *(undefined4 *)(lVar2 + 0x20);
          puVar9 = puVar9 + lVar15 * 0x14;
          *(undefined4 *)(lVar10 + 0x24) = *(undefined4 *)(lVar2 + 0x24);
          *(undefined4 *)(lVar10 + 0x28) = *(undefined4 *)(lVar2 + 0x28);
          *(undefined4 *)(lVar10 + 0x2c) = *(undefined4 *)(lVar2 + 0x2c);
          *(undefined4 *)(lVar10 + 0x60) = *(undefined4 *)(lVar2 + 0x10);
          *(undefined4 *)(lVar10 + 100) = *(undefined4 *)(lVar2 + 0x14);
          *(undefined4 *)(lVar10 + 0x68) = *(undefined4 *)(lVar2 + 0x18);
          *(float *)(param_4 + 0x50) = fVar19;
          *(float *)(param_4 + 0x54) = fVar20;
          *(float *)(param_4 + 0x58) = fVar16;
          *(float *)(param_4 + 0x5c) = fVar3;
          *(undefined4 *)(param_4 + 0x60) = *(undefined4 *)(lVar10 + 0x20);
          *(undefined4 *)(param_4 + 100) = *(undefined4 *)(lVar10 + 0x24);
          *(undefined4 *)(param_4 + 0x68) = *(undefined4 *)(lVar10 + 0x28);
          *(undefined4 *)(param_4 + 0x6c) = *(undefined4 *)(lVar10 + 0x2c);
          *(undefined4 *)(param_4 + 0x70) = *(undefined4 *)(lVar10 + 0x40);
          *(undefined4 *)(param_4 + 0x74) = *(undefined4 *)(lVar10 + 0x44);
          *(undefined4 *)(param_4 + 0x78) = *(undefined4 *)(lVar10 + 0x48);
          *(undefined4 *)(param_4 + 0x7c) = *(undefined4 *)(lVar10 + 0x4c);
          *(undefined4 *)(param_4 + 0x80) = *(undefined4 *)(lVar10 + 0x50);
          *(undefined4 *)(param_4 + 0x84) = *(undefined4 *)(lVar10 + 0x54);
          *(undefined4 *)(param_4 + 0x88) = *(undefined4 *)(lVar10 + 0x58);
          *(undefined4 *)(param_4 + 0x8c) = *(undefined4 *)(lVar10 + 0x5c);
          *(undefined4 *)(param_4 + 0x90) = *(undefined4 *)(lVar10 + 0x60);
          *(undefined4 *)(param_4 + 0x94) = *(undefined4 *)(lVar10 + 100);
          *(undefined4 *)(param_4 + 0x98) = *(undefined4 *)(lVar10 + 0x68);
          *(undefined4 *)(param_4 + 0x9c) = *(undefined4 *)(lVar10 + 0x6c);
          param_4 = param_4 + lVar15 * 0x50;
        } while (uVar8 != uVar14);
      }
      break;
    case 1:
      if (0 < (int)param_3) {
        uVar8 = 0;
        puVar9 = (undefined4 *)(param_4 + lVar15 * 0x50 + -0x10);
        do {
          iVar5 = *(int *)(param_2 + uVar8 * 4);
          lVar10 = *(long *)(param_1 + 0x1c0);
          lVar2 = *(long *)(param_1 + 0x1b8) + (ulong)(uint)(*(int *)(param_1 + 0x1c8) * iVar5);
          lVar11 = ((long)*(int *)(param_1 + 0x1d4) + -1) * (long)iVar5;
          if (2 < iVar4) {
            puVar12 = (undefined8 *)(lVar10 + (lVar15 + -2) * 0x70 + lVar11 * 0x70 + -0x30);
            puVar6 = puVar9;
            lVar7 = lVar15;
            do {
              lVar7 = lVar7 + -1;
              puVar12[0xf] = puVar12[1];
              puVar12[0xe] = *puVar12;
              puVar12[0x11] = puVar12[3];
              puVar12[0x10] = puVar12[2];
              puVar12[0x13] = puVar12[5];
              puVar12[0x12] = puVar12[4];
              puVar6[-0x10] = fVar19;
              puVar6[-0xf] = fVar20;
              puVar6[-0xe] = fVar16;
              puVar6[-0xd] = fVar3;
              puVar6[-0xc] = *(undefined4 *)(puVar12 + 10);
              puVar6[-0xb] = *(undefined4 *)((long)puVar12 + 0x54);
              puVar6[-10] = *(undefined4 *)(puVar12 + 0xb);
              puVar6[-9] = *(undefined4 *)((long)puVar12 + 0x5c);
              *puVar6 = *(undefined4 *)(puVar12 + 0x12);
              puVar6[1] = *(undefined4 *)((long)puVar12 + 0x94);
              puVar6[2] = *(undefined4 *)(puVar12 + 0x13);
              puVar13 = (undefined4 *)((long)puVar12 + 0x9c);
              puVar12 = puVar12 + -0xe;
              puVar6[3] = *puVar13;
              puVar6 = puVar6 + -0x14;
            } while (2 < lVar7);
          }
          lVar10 = lVar10 + lVar11 * 0x70;
          uVar8 = uVar8 + 1;
          *(undefined4 *)(lVar10 + 0x60) = *(undefined4 *)(lVar2 + 0x10);
          puVar9 = puVar9 + lVar15 * 0x14;
          *(undefined4 *)(lVar10 + 100) = *(undefined4 *)(lVar2 + 0x14);
          *(undefined4 *)(lVar10 + 0x68) = *(undefined4 *)(lVar2 + 0x18);
          *(float *)(param_4 + 0x50) = fVar19;
          *(float *)(param_4 + 0x54) = fVar20;
          *(float *)(param_4 + 0x58) = fVar16;
          *(float *)(param_4 + 0x5c) = fVar3;
          *(undefined4 *)(param_4 + 0x60) = *(undefined4 *)(lVar10 + 0x20);
          *(undefined4 *)(param_4 + 100) = *(undefined4 *)(lVar10 + 0x24);
          *(undefined4 *)(param_4 + 0x68) = *(undefined4 *)(lVar10 + 0x28);
          *(undefined4 *)(param_4 + 0x6c) = *(undefined4 *)(lVar10 + 0x2c);
          *(undefined4 *)(param_4 + 0x70) = *(undefined4 *)(lVar10 + 0x40);
          *(undefined4 *)(param_4 + 0x74) = *(undefined4 *)(lVar10 + 0x44);
          *(undefined4 *)(param_4 + 0x78) = *(undefined4 *)(lVar10 + 0x48);
          *(undefined4 *)(param_4 + 0x7c) = *(undefined4 *)(lVar10 + 0x4c);
          *(undefined4 *)(param_4 + 0x80) = *(undefined4 *)(lVar10 + 0x50);
          *(undefined4 *)(param_4 + 0x84) = *(undefined4 *)(lVar10 + 0x54);
          *(undefined4 *)(param_4 + 0x88) = *(undefined4 *)(lVar10 + 0x58);
          *(undefined4 *)(param_4 + 0x8c) = *(undefined4 *)(lVar10 + 0x5c);
          *(undefined4 *)(param_4 + 0x90) = *(undefined4 *)(lVar10 + 0x60);
          *(undefined4 *)(param_4 + 0x94) = *(undefined4 *)(lVar10 + 100);
          *(undefined4 *)(param_4 + 0x98) = *(undefined4 *)(lVar10 + 0x68);
          *(undefined4 *)(param_4 + 0x9c) = *(undefined4 *)(lVar10 + 0x6c);
          param_4 = param_4 + lVar15 * 0x50;
        } while (uVar8 != uVar14);
      }
      break;
    case 2:
      if (0 < (int)param_3) {
        uVar8 = 0;
        puVar9 = (undefined4 *)(param_4 + lVar15 * 0x50 + -0x28);
        do {
          iVar5 = *(int *)(param_2 + uVar8 * 4);
          lVar10 = *(long *)(param_1 + 0x1c0);
          lVar2 = *(long *)(param_1 + 0x1b8) + (ulong)(uint)(*(int *)(param_1 + 0x1c8) * iVar5);
          lVar11 = ((long)*(int *)(param_1 + 0x1d4) + -1) * (long)iVar5;
          if (2 < iVar4) {
            puVar12 = (undefined8 *)(lVar10 + (lVar15 + -2) * 0x70 + lVar11 * 0x70 + -0x50);
            puVar6 = puVar9;
            lVar7 = lVar15;
            do {
              lVar7 = lVar7 + -1;
              puVar12[0xf] = puVar12[1];
              puVar12[0xe] = *puVar12;
              puVar12[0x13] = puVar12[5];
              puVar12[0x12] = puVar12[4];
              puVar12[0x15] = puVar12[7];
              puVar12[0x14] = puVar12[6];
              puVar12[0x17] = puVar12[9];
              puVar12[0x16] = puVar12[8];
              puVar6[-10] = fVar19;
              puVar6[-9] = fVar20;
              puVar6[-8] = fVar16;
              puVar6[-7] = fVar3;
              puVar6[-6] = *(undefined4 *)(puVar12 + 0xe);
              puVar6[-5] = *(undefined4 *)((long)puVar12 + 0x74);
              puVar6[-4] = *(undefined4 *)(puVar12 + 0xf);
              puVar6[-3] = *(undefined4 *)((long)puVar12 + 0x7c);
              puVar6[-2] = *(undefined4 *)(puVar12 + 0x12);
              puVar6[-1] = *(undefined4 *)((long)puVar12 + 0x94);
              *puVar6 = *(undefined4 *)(puVar12 + 0x13);
              puVar6[1] = *(undefined4 *)((long)puVar12 + 0x9c);
              puVar6[2] = *(undefined4 *)(puVar12 + 0x14);
              puVar6[3] = *(undefined4 *)((long)puVar12 + 0xa4);
              puVar6[4] = *(undefined4 *)(puVar12 + 0x15);
              puVar6[5] = *(undefined4 *)((long)puVar12 + 0xac);
              puVar6[6] = *(undefined4 *)(puVar12 + 0x16);
              puVar6[7] = *(undefined4 *)((long)puVar12 + 0xb4);
              puVar6[8] = *(undefined4 *)(puVar12 + 0x17);
              puVar6[9] = *(undefined4 *)((long)puVar12 + 0xbc);
              pfVar1 = (float *)((long)puVar12 + 0x7c);
              puVar12 = puVar12 + -0xe;
              fVar17 = *pfVar1 - *(float *)(param_1 + 0xf8);
              if (fVar17 < 0.0) {
                fVar17 = 0.0;
              }
              puVar6[-3] = fVar17;
              puVar6 = puVar6 + -0x14;
            } while (2 < lVar7);
          }
          lVar10 = lVar10 + lVar11 * 0x70;
          uVar8 = uVar8 + 1;
          puVar9 = puVar9 + lVar15 * 0x14;
          *(undefined4 *)(lVar10 + 0x20) = *(undefined4 *)(lVar2 + 0x20);
          *(undefined4 *)(lVar10 + 0x24) = *(undefined4 *)(lVar2 + 0x24);
          *(undefined4 *)(lVar10 + 0x28) = *(undefined4 *)(lVar2 + 0x28);
          *(undefined4 *)(lVar10 + 0x2c) = *(undefined4 *)(lVar2 + 0x2c);
          *(undefined4 *)(lVar10 + 0x60) = *(undefined4 *)(lVar2 + 0x10);
          *(undefined4 *)(lVar10 + 100) = *(undefined4 *)(lVar2 + 0x14);
          *(undefined4 *)(lVar10 + 0x68) = *(undefined4 *)(lVar2 + 0x18);
          *(float *)(param_4 + 0x50) = fVar19;
          *(float *)(param_4 + 0x54) = fVar20;
          *(float *)(param_4 + 0x58) = fVar16;
          *(float *)(param_4 + 0x5c) = fVar3;
          *(undefined4 *)(param_4 + 0x60) = *(undefined4 *)(lVar10 + 0x20);
          *(undefined4 *)(param_4 + 100) = *(undefined4 *)(lVar10 + 0x24);
          *(undefined4 *)(param_4 + 0x68) = *(undefined4 *)(lVar10 + 0x28);
          *(undefined4 *)(param_4 + 0x6c) = *(undefined4 *)(lVar10 + 0x2c);
          *(undefined4 *)(param_4 + 0x70) = *(undefined4 *)(lVar10 + 0x40);
          *(undefined4 *)(param_4 + 0x74) = *(undefined4 *)(lVar10 + 0x44);
          *(undefined4 *)(param_4 + 0x78) = *(undefined4 *)(lVar10 + 0x48);
          *(undefined4 *)(param_4 + 0x7c) = *(undefined4 *)(lVar10 + 0x4c);
          *(undefined4 *)(param_4 + 0x80) = *(undefined4 *)(lVar10 + 0x50);
          *(undefined4 *)(param_4 + 0x84) = *(undefined4 *)(lVar10 + 0x54);
          *(undefined4 *)(param_4 + 0x88) = *(undefined4 *)(lVar10 + 0x58);
          *(undefined4 *)(param_4 + 0x8c) = *(undefined4 *)(lVar10 + 0x5c);
          *(undefined4 *)(param_4 + 0x90) = *(undefined4 *)(lVar10 + 0x60);
          *(undefined4 *)(param_4 + 0x94) = *(undefined4 *)(lVar10 + 100);
          *(undefined4 *)(param_4 + 0x98) = *(undefined4 *)(lVar10 + 0x68);
          *(undefined4 *)(param_4 + 0x9c) = *(undefined4 *)(lVar10 + 0x6c);
          fVar17 = *(float *)(lVar10 + 0x2c) - *(float *)(param_1 + 0xf8);
          if (fVar17 < 0.0) {
            fVar17 = 0.0;
          }
          *(float *)(param_4 + 0x6c) = fVar17;
          param_4 = param_4 + lVar15 * 0x50;
        } while (uVar8 != uVar14);
      }
      break;
    case 3:
      if (0 < (int)param_3) {
        uVar8 = 0;
        puVar9 = (undefined4 *)(param_4 + lVar15 * 0x50 + -0x28);
        do {
          iVar5 = *(int *)(param_2 + uVar8 * 4);
          lVar10 = *(long *)(param_1 + 0x1c0);
          lVar2 = *(long *)(param_1 + 0x1b8) + (ulong)(uint)(*(int *)(param_1 + 0x1c8) * iVar5);
          lVar11 = ((long)*(int *)(param_1 + 0x1d4) + -1) * (long)iVar5;
          if (2 < iVar4) {
            puVar13 = (undefined4 *)(lVar10 + (lVar15 + -2) * 0x70 + lVar11 * 0x70 + -0x44);
            puVar6 = puVar9;
            lVar7 = lVar15;
            do {
              *(undefined8 *)(puVar13 + 0x23) = *(undefined8 *)(puVar13 + 7);
              *(undefined8 *)(puVar13 + 0x21) = *(undefined8 *)(puVar13 + 5);
              puVar13[0x1c] = *puVar13;
              *(undefined8 *)(puVar13 + 0x27) = *(undefined8 *)(puVar13 + 0xb);
              *(undefined8 *)(puVar13 + 0x25) = *(undefined8 *)(puVar13 + 9);
              *(undefined8 *)(puVar13 + 0x2b) = *(undefined8 *)(puVar13 + 0xf);
              *(undefined8 *)(puVar13 + 0x29) = *(undefined8 *)(puVar13 + 0xd);
              puVar6[-10] = fVar19;
              puVar6[-9] = fVar20;
              puVar6[-8] = fVar16;
              puVar6[-7] = fVar3;
              lVar7 = lVar7 + -1;
              puVar6[-6] = puVar13[0x19];
              puVar6[-5] = puVar13[0x1a];
              puVar6[-4] = puVar13[0x1b];
              puVar6[-3] = puVar13[0x1c];
              puVar6[-2] = puVar13[0x21];
              puVar6[-1] = puVar13[0x22];
              *puVar6 = puVar13[0x23];
              puVar6[1] = puVar13[0x24];
              puVar6[2] = puVar13[0x25];
              puVar6[3] = puVar13[0x26];
              puVar6[4] = puVar13[0x27];
              puVar6[5] = puVar13[0x28];
              puVar6[6] = puVar13[0x29];
              puVar6[7] = puVar13[0x2a];
              puVar6[8] = puVar13[0x2b];
              puVar6[9] = puVar13[0x2c];
              pfVar1 = (float *)(puVar13 + 0x1c);
              puVar13 = puVar13 + -0x1c;
              fVar17 = *pfVar1 - *(float *)(param_1 + 0xf8);
              if (fVar17 < 0.0) {
                fVar17 = 0.0;
              }
              puVar6[-3] = fVar17;
              puVar6 = puVar6 + -0x14;
            } while (2 < lVar7);
          }
          lVar10 = lVar10 + lVar11 * 0x70;
          uVar8 = uVar8 + 1;
          puVar9 = puVar9 + lVar15 * 0x14;
          *(undefined4 *)(lVar10 + 0x2c) = *(undefined4 *)(lVar2 + 0x2c);
          *(undefined4 *)(lVar10 + 0x60) = *(undefined4 *)(lVar2 + 0x10);
          *(undefined4 *)(lVar10 + 100) = *(undefined4 *)(lVar2 + 0x14);
          *(undefined4 *)(lVar10 + 0x68) = *(undefined4 *)(lVar2 + 0x18);
          *(float *)(param_4 + 0x50) = fVar19;
          *(float *)(param_4 + 0x54) = fVar20;
          *(float *)(param_4 + 0x58) = fVar16;
          *(float *)(param_4 + 0x5c) = fVar3;
          *(undefined4 *)(param_4 + 0x60) = *(undefined4 *)(lVar10 + 0x20);
          *(undefined4 *)(param_4 + 100) = *(undefined4 *)(lVar10 + 0x24);
          *(undefined4 *)(param_4 + 0x68) = *(undefined4 *)(lVar10 + 0x28);
          *(undefined4 *)(param_4 + 0x6c) = *(undefined4 *)(lVar10 + 0x2c);
          *(undefined4 *)(param_4 + 0x70) = *(undefined4 *)(lVar10 + 0x40);
          *(undefined4 *)(param_4 + 0x74) = *(undefined4 *)(lVar10 + 0x44);
          *(undefined4 *)(param_4 + 0x78) = *(undefined4 *)(lVar10 + 0x48);
          *(undefined4 *)(param_4 + 0x7c) = *(undefined4 *)(lVar10 + 0x4c);
          *(undefined4 *)(param_4 + 0x80) = *(undefined4 *)(lVar10 + 0x50);
          *(undefined4 *)(param_4 + 0x84) = *(undefined4 *)(lVar10 + 0x54);
          *(undefined4 *)(param_4 + 0x88) = *(undefined4 *)(lVar10 + 0x58);
          *(undefined4 *)(param_4 + 0x8c) = *(undefined4 *)(lVar10 + 0x5c);
          *(undefined4 *)(param_4 + 0x90) = *(undefined4 *)(lVar10 + 0x60);
          *(undefined4 *)(param_4 + 0x94) = *(undefined4 *)(lVar10 + 100);
          *(undefined4 *)(param_4 + 0x98) = *(undefined4 *)(lVar10 + 0x68);
          *(undefined4 *)(param_4 + 0x9c) = *(undefined4 *)(lVar10 + 0x6c);
          fVar17 = *(float *)(lVar10 + 0x2c) - *(float *)(param_1 + 0xf8);
          if (fVar17 < 0.0) {
            fVar17 = 0.0;
          }
          *(float *)(param_4 + 0x6c) = fVar17;
          param_4 = param_4 + lVar15 * 0x50;
        } while (uVar8 != uVar14);
      }
    }
  }
  return;
}

// ==== Aska::IParticleObject::LightingProcedure(float, int const*, int, Aska::ParticleContext*)
// vaddr 0x21a4424 | ghidra 0x22a4424 | size 108 | symbol _ZN4Aska15IParticleObject17LightingProcedureEfPKiiPNS_15ParticleContextE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObject17LightingProcedureEfPKiiPNS_15ParticleContextE
               (float param_1,long param_2,int *param_3,uint param_4,long param_5)

{
  long lVar1;
  int iVar2;
  ulong uVar3;
  float *pfVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  if ((*(char *)(param_2 + 0x1b0) != '\0') && (0 < (int)param_4)) {
    iVar2 = *(int *)(param_2 + 0x1d4);
    uVar3 = (ulong)param_4;
    pfVar4 = (float *)(param_5 + 0x48);
    do {
      uVar3 = uVar3 - 1;
      lVar1 = *(long *)(param_2 + 0x1b8) + (ulong)(uint)(*(int *)(param_2 + 0x1c8) * *param_3);
      fVar7 = *(float *)(lVar1 + 0x18);
      fVar6 = *(float *)(lVar1 + 0x10) + *(float *)(lVar1 + 0x14) * param_1;
      fVar5 = *(float *)(lVar1 + 0x14) + fVar7 * param_1;
      *(float *)(lVar1 + 0x10) = fVar6;
      *(float *)(lVar1 + 0x14) = fVar5;
      pfVar4[-2] = fVar6;
      pfVar4[-1] = fVar5;
      *pfVar4 = fVar7;
      pfVar4 = pfVar4 + (long)iVar2 * 0x14;
      param_3 = param_3 + 1;
    } while (uVar3 != 0);
  }
  return;
}

// ==== Aska::IParticleObject::ExtendProcedure(Aska::ParticleContext*, int)
// vaddr 0x21a4490 | ghidra 0x22a4490 | size 636 | symbol _ZN4Aska15IParticleObject15ExtendProcedureEPNS_15ParticleContextEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObject15ExtendProcedureEPNS_15ParticleContextEi
               (long param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  long lVar5;
  float *pfVar6;
  long lVar7;
  float *pfVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  
  uVar4 = *(uint *)(param_1 + 0x1d4);
  lVar5 = (long)(int)uVar4;
  fVar9 = *(float *)(param_1 + 0xe8);
  if ((*(ushort *)(param_1 + 500) >> 8 & 1) == 0) {
    if (((fVar9 != 1.0) && (param_3 != 0)) && (1 < (int)uVar4)) {
      pfVar6 = param_2 + 0x16;
      do {
        fVar11 = *param_2;
        fVar13 = param_2[1];
        fVar14 = param_2[2];
        param_3 = param_3 + -1;
        lVar7 = (ulong)uVar4 - 1;
        pfVar8 = pfVar6;
        fVar17 = fVar11;
        fVar16 = fVar13;
        fVar15 = fVar14;
        do {
          fVar1 = pfVar8[-2];
          fVar2 = pfVar8[-1];
          fVar3 = *pfVar8;
          fVar11 = fVar9 * (fVar1 - fVar17) + fVar11;
          fVar13 = fVar9 * (fVar2 - fVar16) + fVar13;
          fVar14 = fVar9 * (fVar3 - fVar15) + fVar14;
          lVar7 = lVar7 + -1;
          pfVar8[-2] = fVar11;
          pfVar8[-1] = fVar13;
          *pfVar8 = fVar14;
          pfVar8 = pfVar8 + 0x14;
          fVar17 = fVar1;
          fVar16 = fVar2;
          fVar15 = fVar3;
        } while (lVar7 != 0);
        param_2 = param_2 + lVar5 * 0x14;
        pfVar6 = pfVar6 + lVar5 * 0x14;
      } while (param_3 != 0);
    }
  }
  else if (((fVar9 != 0.0) && (param_3 != 0)) && (1 < (int)uVar4)) {
    pfVar6 = param_2 + 0x16;
    do {
      fVar11 = *param_2;
      fVar13 = param_2[1];
      fVar14 = param_2[2];
      param_3 = param_3 + -1;
      lVar7 = (ulong)uVar4 - 1;
      pfVar8 = pfVar6;
      fVar17 = fVar14;
      fVar16 = fVar13;
      fVar15 = fVar11;
      do {
        fVar1 = pfVar8[-2];
        fVar2 = pfVar8[-1];
        fVar3 = *pfVar8;
        fVar15 = fVar1 - fVar15;
        fVar16 = fVar2 - fVar16;
        fVar17 = fVar3 - fVar17;
        fVar12 = fVar15 * fVar15 + fVar16 * fVar16 + fVar17 * fVar17;
        fVar10 = SQRT(fVar12);
        if (NAN(fVar10)) {
          fVar10 = (float)sqrtf(fVar12);
        }
        fVar12 = 1.0;
        if (fVar10 != 0.0) {
          fVar12 = (fVar9 / (float)(int)(uVar4 - 1)) / fVar10 + 1.0;
        }
        fVar11 = fVar15 * fVar12 + fVar11;
        fVar13 = fVar16 * fVar12 + fVar13;
        fVar14 = fVar17 * fVar12 + fVar14;
        lVar7 = lVar7 + -1;
        pfVar8[-2] = fVar11;
        pfVar8[-1] = fVar13;
        *pfVar8 = fVar14;
        pfVar8 = pfVar8 + 0x14;
        fVar17 = fVar3;
        fVar16 = fVar2;
        fVar15 = fVar1;
      } while (lVar7 != 0);
      param_2 = param_2 + lVar5 * 0x14;
      pfVar6 = pfVar6 + lVar5 * 0x14;
    } while (param_3 != 0);
  }
  return;
}

// ==== Aska::IParticleObject::operator new(unsigned long, unsigned long, bool)
// vaddr 0x21a470c | ghidra 0x22a470c | size 56 | symbol _ZN4Aska15IParticleObjectnwEmmb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObjectnwEmmb(undefined8 param_1,undefined8 param_2)

{
  if (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager13AlignedMallocEml_02cae360)
              (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838,param_1,param_2);
    return;
  }
  (*(code *)PTR__Znwmmb_02c9f858)(param_1,param_2,1);
  return;
}

// ==== Aska::IParticleObject::operator new[](unsigned long, unsigned long, bool)
// vaddr 0x21a4744 | ghidra 0x22a4744 | size 56 | symbol _ZN4Aska15IParticleObjectnaEmmb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObjectnaEmmb(undefined8 param_1,undefined8 param_2)

{
  if (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager13AlignedMallocEml_02cae360)
              (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838,param_1,param_2);
    return;
  }
  (*(code *)PTR__Znammb_02c9d8d8)(param_1,param_2,1);
  return;
}

// ==== Aska::IParticleObject::operator delete(void*, std::nothrow_t const&)
// vaddr 0x21a477c | ghidra 0x22a477c | size 44 | symbol _ZN4Aska15IParticleObjectdlEPvRKSt9nothrow_t | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObjectdlEPvRKSt9nothrow_t(long param_1)

{
  if (param_1 == 0) {
    return;
  }
  if (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPv_02cb5c60)
              (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838,param_1);
    return;
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::IParticleObject::operator delete[](void*, std::nothrow_t const&)
// vaddr 0x21a47a8 | ghidra 0x22a47a8 | size 44 | symbol _ZN4Aska15IParticleObjectdaEPvRKSt9nothrow_t | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObjectdaEPvRKSt9nothrow_t(long param_1)

{
  if (param_1 == 0) {
    return;
  }
  if (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPv_02cb5c60)
              (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838,param_1);
    return;
  }
  (*(code *)PTR__ZdaPv_02cb5db8)(param_1);
  return;
}

// ==== Aska::IParticleObject::operator delete[](void*)
// vaddr 0x21a47d4 | ghidra 0x22a47d4 | size 44 | symbol _ZN4Aska15IParticleObjectdaEPv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15IParticleObjectdaEPv(long param_1)

{
  if (param_1 == 0) {
    return;
  }
  if (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager9LocalFreeEPv_02cb5c60)
              (*(long *)PTR__ZN4Aska15ParticleManager9gpMemHeapE_02cba838,param_1);
    return;
  }
  (*(code *)PTR__ZdaPv_02cb5db8)(param_1);
  return;
}


// FAILED to create function at 02c52328 Aska::IParticleObject::vtable
// FAILED to create function at 02c52370 Aska::IParticleObject::typeinfo
