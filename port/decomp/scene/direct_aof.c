// port/decomp/scene/direct_aof.c: Ghidra decompiles for the scene subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:40 UTC: tools/decomp.sh '--into' 'scene/direct_aof' 'Aska::DirectAofHandler::' 'Framework::CDirectAofTextRenderer::' 'Framework::CDirectAofPrimitiveRenderer::' 'Aska::DirectAofPrimitive::' 'Aska::DirectAofPrimitiveBase::'

// ==== Framework::CDirectAofPrimitiveRenderer::CDirectAofPrimitiveRenderer()
// vaddr 0x1e76c9c | ghidra 0x1f76c9c | size 76 | symbol _ZN9Framework27CDirectAofPrimitiveRendererC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework27CDirectAofPrimitiveRendererC1Ev(long *param_1)

{
  Aska::AofObject::AofObject()();
  *param_1 = (long)(PTR__ZTVN9Framework27CDirectAofPrimitiveRendererE_02cc4db0 + 0x10);
  memset(param_1 + 0xd6,0,0xdc);
  *(undefined4 *)((long)param_1 + 0x78c) = 0;
  *(undefined4 *)(param_1 + 0xf2) = 0;
  *(undefined4 *)((long)param_1 + 0x794) = 0;
  param_1[0xf3] = 0;
  *(undefined2 *)(param_1 + 0xf4) = 0;
  *(undefined1 *)((long)param_1 + 0x7a2) = 0;
  return;
}

// ==== Framework::CDirectAofPrimitiveRenderer::Initialize(Framework::CDirectAofPrimitiveRenderer::iType, unsigned int, bool)
// vaddr 0x1e76ce8 | ghidra 0x1f76ce8 | size 360 | symbol _ZN9Framework27CDirectAofPrimitiveRenderer10InitializeENS0_5iTypeEjb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework27CDirectAofPrimitiveRenderer10InitializeENS0_5iTypeEjb
               (long *param_1,uint param_2,undefined4 param_3,byte param_4)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  long lVar4;
  
  if (param_1[0xec] != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962c19/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DirectAofPrimitiveRenderer.cpp"*/,0x7f,&UNK_02962c7f/*"m_pDirectAofHandler isn't null.(%08x)"*/);
  }
  *(uint *)((long)param_1 + 0x79c) = param_2;
  *(byte *)((long)param_1 + 0x7a1) = param_4 & 1;
  if (3 < param_2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962c19/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DirectAofPrimitiveRenderer.cpp"*/,0x8a,&UNK_02962ca5/*"The argument 'aType' has gotten illegal value.(%d)"*/,param_2);
  }
  Aska::DirectAofHandler::SetDefaultMaterial(Aska::DirectMaterial*)(param_1 + 0xd6);
  *(undefined2 *)((long)param_1 + 0x6b3) = 0xa102;
  *(undefined1 *)((long)param_1 + 0x6b5) = 1;
  *(ushort *)((long)param_1 + 0x6bf) = *(ushort *)((long)param_1 + 0x6bf) & 0xfffe;
  Framework::CDirectAofPrimitiveRenderer::Reserve(unsigned int)(param_1,param_3);
  (**(code **)(*param_1 + 0x248))(param_1,2);
  (**(code **)(*param_1 + 0x160))(param_1,0xe5);
  puVar2 = PTR__ZN9Framework10TSingletonINS_9CCamera2DEE11m_pInstanceE_02cbe730;
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonINS_9CCamera2DEE11m_pInstanceE_02cbe730;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961da1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/./TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar2;
  }
  lVar4 = *(long *)(lVar4 + 8);
  param_1[0x34] = lVar4;
  uVar1 = *(uint *)(param_1 + 0x33) & 0xff3ffffd;
  if (lVar4 != 0) {
    uVar1 = *(uint *)(param_1 + 0x33) | 0x800000;
  }
  *(uint *)(param_1 + 0x33) = uVar1 | 0x400002;
  *(undefined4 *)((long)param_1 + 0x78c) = 0;
  *(undefined4 *)(param_1 + 0xf2) = 0;
  *(undefined1 *)(param_1 + 0xf4) = 1;
  iVar3 = iRam0000000002cc7090 + 1;
  *(int *)(param_1 + 0xf3) = iRam0000000002cc7090;
  iRam0000000002cc7090 = iVar3;
                    /* WARNING: Could not recover jumptable at 0x01f76e4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x2e0))(param_1);
  return;
}

// ==== Framework::CDirectAofPrimitiveRenderer::Reserve(unsigned int)
// vaddr 0x1e76e50 | ghidra 0x1f76e50 | size 700 | symbol _ZN9Framework27CDirectAofPrimitiveRenderer7ReserveEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework27CDirectAofPrimitiveRenderer7ReserveEj(long *param_1,uint param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long *plVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  
  uVar3 = *(uint *)(param_1 + 0xf1);
  if (uVar3 < param_2) {
    *(uint *)(param_1 + 0xf1) = param_2;
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x410,PTR__ZSt7nothrow_02cb9a80);
    if (plVar4 == (long *)0x0) {
      param_1[0xec] = 0;
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962c19/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DirectAofPrimitiveRenderer.cpp"*/,0xd5,&UNK_02962cd8/*"m_pDirectAofHandler is null."*/);
    }
    else {
      memset(plVar4,0,0x410);
      Aska::DirectAofPrimitive::DirectAofPrimitive()(plVar4);
      puVar1 = PTR__ZTVN9Framework20DirectAofPrimitiveExE_02cc2700 + 0xb8;
      puVar2 = PTR__ZTVN9Framework20DirectAofPrimitiveExE_02cc2700 + 0xe0;
      *plVar4 = (long)(PTR__ZTVN9Framework20DirectAofPrimitiveExE_02cc2700 + 0x10);
      plVar4[0x14] = (long)puVar2;
      plVar4[0x13] = (long)puVar1;
      param_1[0xec] = (long)plVar4;
    }
    plVar8 = param_1 + 0xec;
    Aska::DirectAofHandler::Create(int, bool, char const*)(*plVar8,1,*(undefined1 *)((long)param_1 + 0x7a1),0);
    iVar10 = 0;
    do {
      Aska::DirectAofHandler::Open()(*plVar8);
      if (*(int *)((long)param_1 + 0x79c) == 2) {
        Aska::detail::DirectAofPrimitiveImpl::BeginQuadMesh(Aska::DirectMaterial*, unsigned long) const(param_1[0xec] + 0x3e0,param_1 + 0xd6,(int)param_1[0xf1]);
        Framework::DirectAofPrimitiveEx::AddDummy(Framework::CDirectAofPrimitiveRenderer::iType, unsigned int)(plVar4,*(undefined4 *)((long)param_1 + 0x79c),(int)param_1[0xf1]);
        iVar11 = 4;
      }
      else if (*(int *)((long)param_1 + 0x79c) == 0) {
        Aska::detail::DirectAofPrimitiveImpl::BeginRectMesh(Aska::DirectMaterial*, unsigned long) const(param_1[0xec] + 0x3e0,param_1 + 0xd6,(int)param_1[0xf1]);
        Framework::DirectAofPrimitiveEx::AddDummy(Framework::CDirectAofPrimitiveRenderer::iType, unsigned int)(plVar4,*(undefined4 *)((long)param_1 + 0x79c),(int)param_1[0xf1]);
        iVar11 = 2;
      }
      else {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962c19/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DirectAofPrimitiveRenderer.cpp"*/,0xfc,&UNK_02962cf5/*"Not implement."*/);
        iVar11 = 0;
      }
      Aska::DirectAofHandler::EndMesh()(*plVar8);
      Aska::DirectAofHandler::Close(Aska::Vector const*, bool)(*plVar8,0,0);
      Aska::DirectAofHandler::FlipBuffer(int)(*plVar8,0);
      iVar10 = iVar10 + 1;
      iVar9 = 1;
      if (*(char *)((long)param_1 + 0x7a1) != '\0') {
        iVar9 = 2;
      }
    } while (iVar10 < iVar9);
    *(undefined4 *)((long)param_1 + 0x794) = 0;
    uVar3 = iVar11 * uVar3;
    lVar6 = (ulong)(uint)((int)param_1[0xf1] * iVar11) << 4;
    lVar5 = operator new[](unsigned long, std::nothrow_t const&)(lVar6,PTR__ZSt7nothrow_02cb9a80);
    lVar7 = param_1[0xee];
    if (lVar7 != 0) {
      memcpy(lVar5,lVar7,(ulong)uVar3 << 4);
      operator delete[](void*)(lVar7);
      param_1[0xee] = 0;
    }
    param_1[0xee] = lVar5;
    lVar5 = operator new[](unsigned long, std::nothrow_t const&)(lVar6,PTR__ZSt7nothrow_02cb9a80);
    lVar7 = param_1[0xef];
    if (lVar7 != 0) {
      memcpy(lVar5,lVar7,(ulong)uVar3 << 4);
      operator delete[](void*)(lVar7);
      param_1[0xef] = 0;
    }
    param_1[0xef] = lVar5;
    lVar5 = operator new[](unsigned long, std::nothrow_t const&)(lVar6,PTR__ZSt7nothrow_02cb9a80);
    lVar6 = param_1[0xf0];
    if (lVar6 != 0) {
      memcpy(lVar5,lVar6,(ulong)uVar3 << 4);
      operator delete[](void*)(lVar6);
      param_1[0xf0] = 0;
    }
    param_1[0xf0] = lVar5;
                    /* WARNING: Could not recover jumptable at 0x01f77108. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 0x2d0))(param_1,*plVar8,1);
    return;
  }
  return;
}

// ==== Framework::CDirectAofPrimitiveRenderer::IsInitialized() const
// vaddr 0x1e7710c | ghidra 0x1f7710c | size 16 | symbol _ZNK9Framework27CDirectAofPrimitiveRenderer13IsInitializedEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework27CDirectAofPrimitiveRenderer13IsInitializedEv(long param_1)

{
  return *(long *)(param_1 + 0x760) != 0;
}

// ==== Framework::CDirectAofPrimitiveRenderer::Release()
// vaddr 0x1e7711c | ghidra 0x1f7711c | size 68 | symbol _ZN9Framework27CDirectAofPrimitiveRenderer7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework27CDirectAofPrimitiveRenderer7ReleaseEv(long param_1)

{
  Aska::Task::Remove()();
  if (*(long *)(param_1 + 0x780) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x780) = 0;
  }
  if (*(long *)(param_1 + 0x778) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x778) = 0;
  }
  if (*(long *)(param_1 + 0x770) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x770) = 0;
  }
  return;
}

// ==== Framework::CDirectAofPrimitiveRenderer::Texture(Aska::Texture*)
// vaddr 0x1e77160 | ghidra 0x1f77160 | size 72 | symbol _ZN9Framework27CDirectAofPrimitiveRenderer7TextureEPN4Aska7TextureE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework27CDirectAofPrimitiveRenderer7TextureEPN4Aska7TextureE
               (long param_1,undefined8 param_2)

{
  if (*(long *)(param_1 + 0x760) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962c19/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DirectAofPrimitiveRenderer.cpp"*/,0xbc,&UNK_0296203b/*"IsInitialized() is null."*/);
  }
  *(undefined8 *)(param_1 + 0x768) = param_2;
  *(undefined1 *)(param_1 + 0x7a0) = 1;
  return;
}

// ==== Framework::CDirectAofPrimitiveRenderer::DirectMaterial(Aska::DirectMaterial&)
// vaddr 0x1e771a8 | ghidra 0x1f771a8 | size 228 | symbol _ZN9Framework27CDirectAofPrimitiveRenderer14DirectMaterialERN4Aska14DirectMaterialE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework27CDirectAofPrimitiveRenderer14DirectMaterialERN4Aska14DirectMaterialE
               (long param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  
  if (*(long *)(param_1 + 0x760) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962c19/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DirectAofPrimitiveRenderer.cpp"*/,0xc4,&UNK_0296203b/*"IsInitialized() is null."*/);
  }
  *(undefined1 *)(param_1 + 0x6c0) = *(undefined1 *)(param_2 + 2);
  uVar1 = *param_2;
  *(undefined8 *)(param_1 + 0x6b8) = param_2[1];
  *(undefined8 *)(param_1 + 0x6b0) = uVar1;
  *(undefined4 *)(param_1 + 0x6d0) = *(undefined4 *)(param_2 + 4);
  *(undefined4 *)(param_1 + 0x6d4) = *(undefined4 *)((long)param_2 + 0x24);
  *(undefined4 *)(param_1 + 0x6d8) = *(undefined4 *)(param_2 + 5);
  *(undefined4 *)(param_1 + 0x6dc) = *(undefined4 *)((long)param_2 + 0x2c);
  *(undefined4 *)(param_1 + 0x6e0) = *(undefined4 *)(param_2 + 6);
  *(undefined4 *)(param_1 + 0x6e4) = *(undefined4 *)((long)param_2 + 0x34);
  *(undefined4 *)(param_1 + 0x6e8) = *(undefined4 *)(param_2 + 7);
  *(undefined4 *)(param_1 + 0x6ec) = *(undefined4 *)((long)param_2 + 0x3c);
  *(undefined4 *)(param_1 + 0x6f0) = *(undefined4 *)(param_2 + 8);
  *(undefined4 *)(param_1 + 0x6f4) = *(undefined4 *)((long)param_2 + 0x44);
  *(undefined4 *)(param_1 + 0x6f8) = *(undefined4 *)(param_2 + 9);
  *(undefined4 *)(param_1 + 0x6fc) = *(undefined4 *)((long)param_2 + 0x4c);
  *(undefined4 *)(param_1 + 0x700) = *(undefined4 *)(param_2 + 10);
  *(undefined4 *)(param_1 + 0x704) = *(undefined4 *)((long)param_2 + 0x54);
  *(undefined4 *)(param_1 + 0x708) = *(undefined4 *)(param_2 + 0xb);
  *(undefined4 *)(param_1 + 0x70c) = *(undefined4 *)((long)param_2 + 0x5c);
  memcpy(param_1 + 0x710,param_2 + 0xc,0x48);
  *(undefined1 *)(param_1 + 0x7a0) = 1;
  return;
}

// ==== Framework::DirectAofPrimitiveEx::AddDummy(Framework::CDirectAofPrimitiveRenderer::iType, unsigned int)
// vaddr 0x1e7728c | ghidra 0x1f7728c | size 416 | symbol _ZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEj
               (long param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined *puVar6;
  int iVar7;
  long lVar8;
  long lVar9;
  
  if (((*
        PTR__ZGVZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE5vZero_02cb9e70
       & 1) == 0) &&
     (iVar7 = __cxa_guard_acquire(
                             PTR__ZGVZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE5vZero_02cb9e70
                             ),
     puVar6 = 
     PTR__ZZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE5vZero_02cbaee8
     , iVar7 != 0)) {
    *(undefined8 *)
     PTR__ZZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE5vZero_02cbaee8
         = 0;
    *(undefined8 *)(puVar6 + 8) = 0;
    __cxa_guard_release(
                   PTR__ZGVZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE5vZero_02cb9e70
                   );
  }
  if (((*
        PTR__ZGVZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE6vDummy_02cbc7c8
       & 1) == 0) &&
     (iVar7 = __cxa_guard_acquire(
                             PTR__ZGVZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE6vDummy_02cbc7c8
                             ),
     puVar6 = 
     PTR__ZZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE6vDummy_02cb9c48
     , iVar7 != 0)) {
    uVar1 = *(undefined4 *)
             PTR__ZZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE5vZero_02cbaee8
    ;
    uVar3 = *(undefined4 *)
             (
             PTR__ZZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE5vZero_02cbaee8
             + 4);
    uVar2 = *(undefined4 *)
             (
             PTR__ZZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE5vZero_02cbaee8
             + 8);
    uVar4 = *(undefined4 *)
             (
             PTR__ZZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE5vZero_02cbaee8
             + 0xc);
    *(undefined4 *)
     PTR__ZZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE6vDummy_02cb9c48
         = uVar1;
    *(undefined4 *)(puVar6 + 4) = uVar3;
    *(undefined4 *)(puVar6 + 8) = uVar2;
    *(undefined4 *)(puVar6 + 0xc) = uVar4;
    *(undefined4 *)(puVar6 + 0x10) = uVar1;
    *(undefined4 *)(puVar6 + 0x14) = uVar3;
    *(undefined4 *)(puVar6 + 0x18) = uVar2;
    *(undefined4 *)(puVar6 + 0x1c) = uVar4;
    *(undefined4 *)(puVar6 + 0x20) = uVar1;
    *(undefined4 *)(puVar6 + 0x24) = uVar3;
    *(undefined4 *)(puVar6 + 0x28) = uVar2;
    *(undefined4 *)(puVar6 + 0x2c) = uVar4;
    *(undefined4 *)(puVar6 + 0x30) = uVar1;
    *(undefined4 *)(puVar6 + 0x34) = uVar3;
    *(undefined4 *)(puVar6 + 0x38) = uVar2;
    *(undefined4 *)(puVar6 + 0x3c) = uVar4;
    __cxa_guard_release(
                   PTR__ZGVZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE6vDummy_02cbc7c8
                   );
  }
  lVar9 = *(long *)(param_1 + 0x368);
  lVar8 = *(long *)(param_1 + 0x360);
  if (param_2 == 2) {
    Aska::detail::DirectAofPrimitiveImpl::AddQuad(Aska::Vector const*, Aska::Vector const*, Aska::Vector const*)(param_1 + 0x3e0,
                    PTR__ZZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE6vDummy_02cb9c48
                    ,
                    PTR__ZZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE6vDummy_02cb9c48
                    ,
                    PTR__ZZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE6vDummy_02cb9c48
                   );
  }
  else if (param_2 == 0) {
    Aska::detail::DirectAofPrimitiveImpl::AddRect(Aska::Vector const*, Aska::Vector const*, Aska::Vector const*)(param_1 + 0x3e0,
                    PTR__ZZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE6vDummy_02cb9c48
                    ,
                    PTR__ZZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE6vDummy_02cb9c48
                    ,
                    PTR__ZZN9Framework20DirectAofPrimitiveEx8AddDummyENS_27CDirectAofPrimitiveRenderer5iTypeEjE6vDummy_02cb9c48
                   );
  }
  else {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962c19/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DirectAofPrimitiveRenderer.cpp"*/,0x4e,&UNK_02962cf5/*"Not implement."*/);
  }
  if (param_3 != 1) {
    memset(*(undefined8 *)(param_1 + 0x368),0,
                    (param_3 + -1) * ((int)*(undefined8 *)(param_1 + 0x368) - (int)lVar9));
    uVar5 = param_3 * 6 - 6;
    *(ulong *)(param_1 + 0x368) = lVar9 + (ulong)(uint)(param_3 << 2) * 0x28;
    *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + (param_3 + -1) * 4;
    memset(*(undefined8 *)(param_1 + 0x360),0,(ulong)uVar5 << 1);
    *(ulong *)(param_1 + 0x360) = lVar8 + (ulong)(uint)(param_3 * 6) * 2;
    *(uint *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + uVar5;
  }
  return;
}

// ==== Framework::CDirectAofPrimitiveRenderer::PreliminarilyPrepare(Aska::LightManager*)
// vaddr 0x1e7742c | ghidra 0x1f7742c | size 484 | symbol _ZN9Framework27CDirectAofPrimitiveRenderer20PreliminarilyPrepareEPN4Aska12LightManagerE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN9Framework27CDirectAofPrimitiveRenderer20PreliminarilyPrepareEPN4Aska12LightManagerE
          (long param_1,undefined8 param_2)

{
  undefined8 uVar1;
  uint uVar2;
  long lVar3;
  
  if ((*(long *)(param_1 + 0x760) != 0) && (*(int *)(param_1 + 0x78c) != 0)) {
    if (*(uint *)(param_1 + 0x788) < *(uint *)(param_1 + 0x78c)) {
      Framework::CDirectAofPrimitiveRenderer::Reserve(unsigned int)(param_1,*(undefined4 *)(param_1 + 0x78c));
    }
    if (*(int *)(param_1 + 0x78c) != *(int *)(param_1 + 0x790)) {
      *(undefined4 *)(param_1 + 0x790) = *(undefined4 *)(param_1 + 0x78c);
      *(undefined4 *)(param_1 + 0x794) = 0;
    }
    uVar2 = 1;
    if (*(char *)(param_1 + 0x7a1) != '\0') {
      uVar2 = 2;
    }
    if (*(uint *)(param_1 + 0x794) < uVar2) {
      *(int *)(param_1 + 0x794) = *(int *)(param_1 + 0x794) + 1;
      Aska::DirectAofHandler::Open()(*(undefined8 *)(param_1 + 0x760));
      if (*(int *)(param_1 + 0x79c) == 2) {
        Aska::detail::DirectAofPrimitiveImpl::BeginQuadMesh(Aska::DirectMaterial*, unsigned long) const(*(long *)(param_1 + 0x760) + 0x3e0,param_1 + 0x6b0,
                        *(undefined4 *)(param_1 + 0x78c));
        if (*(int *)(param_1 + 0x78c) != 0) {
          lVar3 = 0;
          uVar2 = 0;
          do {
            Aska::detail::DirectAofPrimitiveImpl::AddQuad(Aska::Vector const*, Aska::Vector const*, Aska::Vector const*)(*(long *)(param_1 + 0x760) + 0x3e0,*(long *)(param_1 + 0x770) + lVar3,
                            *(long *)(param_1 + 0x778) + lVar3,*(long *)(param_1 + 0x780) + lVar3);
            uVar2 = uVar2 + 1;
            lVar3 = lVar3 + 0x40;
          } while (uVar2 < *(uint *)(param_1 + 0x78c));
        }
      }
      else if (*(int *)(param_1 + 0x79c) == 0) {
        Aska::detail::DirectAofPrimitiveImpl::BeginRectMesh(Aska::DirectMaterial*, unsigned long) const(*(long *)(param_1 + 0x760) + 0x3e0,param_1 + 0x6b0,
                        *(undefined4 *)(param_1 + 0x78c));
        if (*(int *)(param_1 + 0x78c) != 0) {
          lVar3 = 0;
          uVar2 = 0;
          do {
            Aska::detail::DirectAofPrimitiveImpl::AddRect(Aska::Vector const*, Aska::Vector const*, Aska::Vector const*)(*(long *)(param_1 + 0x760) + 0x3e0,*(long *)(param_1 + 0x770) + lVar3,
                            *(long *)(param_1 + 0x778) + lVar3,*(long *)(param_1 + 0x780) + lVar3);
            uVar2 = uVar2 + 1;
            lVar3 = lVar3 + 0x20;
          } while (uVar2 < *(uint *)(param_1 + 0x78c));
        }
      }
      else {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962c19/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DirectAofPrimitiveRenderer.cpp"*/,0x14d,&UNK_02962cf5/*"Not implement."*/);
      }
      Aska::DirectAofHandler::EndMesh()(*(undefined8 *)(param_1 + 0x760));
      Aska::DirectAofHandler::Close(Aska::Vector const*, bool)(*(undefined8 *)(param_1 + 0x760),0,0);
    }
    if (*(char *)(param_1 + 0x7a0) != '\0') {
      uVar1 = 0;
      if (*(undefined8 **)(param_1 + 0x768) != (undefined8 *)0x0) {
        uVar1 = **(undefined8 **)(param_1 + 0x768);
      }
      *(undefined8 *)(param_1 + 0x710) = uVar1;
      Aska::DirectAofHandler::SetDirectMaterial(int, Aska::DirectMaterial*)(*(undefined8 *)(param_1 + 0x760),0,param_1 + 0x6b0);
      *(undefined1 *)(param_1 + 0x7a0) = 0;
    }
    uVar1 = (*(code *)PTR__ZN4Aska9AofObject20PreliminarilyPrepareEPNS_12LightManagerE_02c923a8)
                      (param_1,param_2);
    return uVar1;
  }
  return 0;
}

// ==== Framework::CDirectAofPrimitiveRenderer::PrepareForRendering(Aska::RENDERINFO const*)
// vaddr 0x1e77610 | ghidra 0x1f77610 | size 28 | symbol _ZN9Framework27CDirectAofPrimitiveRenderer19PrepareForRenderingEPKN4Aska10RENDERINFOE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN9Framework27CDirectAofPrimitiveRenderer19PrepareForRenderingEPKN4Aska10RENDERINFOE(long param_1)

{
  undefined8 uVar1;
  
  if ((*(long *)(param_1 + 0x760) != 0) && (*(int *)(param_1 + 0x78c) != 0)) {
    uVar1 = (*(code *)PTR__ZN4Aska9AofObject19PrepareForRenderingEPKNS_10RENDERINFOE_02cb4b60)();
    return uVar1;
  }
  return 0;
}

// ==== Framework::CDirectAofPrimitiveRenderer::Render(Aska::RenderContext*, int)
// vaddr 0x1e7762c | ghidra 0x1f7762c | size 4 | symbol _ZN9Framework27CDirectAofPrimitiveRenderer6RenderEPN4Aska13RenderContextEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework27CDirectAofPrimitiveRenderer6RenderEPN4Aska13RenderContextEi(void)

{
  (*(code *)PTR__ZN4Aska9AofObject6RenderEPNS_13RenderContextEi_02cab7a8)();
  return;
}

// ==== Framework::CDirectAofPrimitiveRenderer::Type() const
// vaddr 0x1e77630 | ghidra 0x1f77630 | size 52 | symbol _ZNK9Framework27CDirectAofPrimitiveRenderer4TypeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework27CDirectAofPrimitiveRenderer4TypeEv(long param_1)

{
  if (*(long *)(param_1 + 0x760) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962c19/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DirectAofPrimitiveRenderer.cpp"*/,0x179,&UNK_0296203b/*"IsInitialized() is null."*/);
  }
  return *(undefined4 *)(param_1 + 0x79c);
}

// ==== Framework::CDirectAofPrimitiveRenderer::NumPrimitives() const
// vaddr 0x1e77664 | ghidra 0x1f77664 | size 52 | symbol _ZNK9Framework27CDirectAofPrimitiveRenderer13NumPrimitivesEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework27CDirectAofPrimitiveRenderer13NumPrimitivesEv(long param_1)

{
  if (*(long *)(param_1 + 0x760) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962c19/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DirectAofPrimitiveRenderer.cpp"*/,0x17f,&UNK_0296203b/*"IsInitialized() is null."*/);
  }
  return *(undefined4 *)(param_1 + 0x788);
}

// ==== Framework::CDirectAofPrimitiveRenderer::PutCounter() const
// vaddr 0x1e77698 | ghidra 0x1f77698 | size 52 | symbol _ZNK9Framework27CDirectAofPrimitiveRenderer10PutCounterEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework27CDirectAofPrimitiveRenderer10PutCounterEv(long param_1)

{
  if (*(long *)(param_1 + 0x760) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962c19/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DirectAofPrimitiveRenderer.cpp"*/,0x185,&UNK_0296203b/*"IsInitialized() is null."*/);
  }
  return *(undefined4 *)(param_1 + 0x78c);
}

// ==== Framework::CDirectAofPrimitiveRenderer::Reset()
// vaddr 0x1e776cc | ghidra 0x1f776cc | size 56 | symbol _ZN9Framework27CDirectAofPrimitiveRenderer5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework27CDirectAofPrimitiveRenderer5ResetEv(long param_1)

{
  if (*(long *)(param_1 + 0x760) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962c19/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DirectAofPrimitiveRenderer.cpp"*/,0x18b,&UNK_0296203b/*"IsInitialized() is null."*/);
  }
  *(undefined4 *)(param_1 + 0x78c) = 0;
  *(undefined1 *)(param_1 + 0x7a2) = 0;
  return;
}

// ==== Framework::CDirectAofPrimitiveRenderer::cpTexture() const
// vaddr 0x1e77704 | ghidra 0x1f77704 | size 52 | symbol _ZNK9Framework27CDirectAofPrimitiveRenderer9cpTextureEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework27CDirectAofPrimitiveRenderer9cpTextureEv(long param_1)

{
  if (*(long *)(param_1 + 0x760) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962c19/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DirectAofPrimitiveRenderer.cpp"*/,0x199,&UNK_0296203b/*"IsInitialized() is null."*/);
  }
  return *(undefined8 *)(param_1 + 0x768);
}

// ==== Framework::CDirectAofPrimitiveRenderer::crDirectMaterial() const
// vaddr 0x1e77738 | ghidra 0x1f77738 | size 52 | symbol _ZNK9Framework27CDirectAofPrimitiveRenderer16crDirectMaterialEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework27CDirectAofPrimitiveRenderer16crDirectMaterialEv(long param_1)

{
  if (*(long *)(param_1 + 0x760) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962c19/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DirectAofPrimitiveRenderer.cpp"*/,0x19f,&UNK_0296203b/*"IsInitialized() is null."*/);
  }
  return param_1 + 0x6b0;
}

// ==== Framework::CDirectAofPrimitiveRenderer::Put(Framework::tSpriteParameter_Rect const&)
// vaddr 0x1e7776c | ghidra 0x1f7776c | size 296 | symbol _ZN9Framework27CDirectAofPrimitiveRenderer3PutERKNS_21tSpriteParameter_RectE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework27CDirectAofPrimitiveRenderer3PutERKNS_21tSpriteParameter_RectE
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long lVar2;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined8 uStack_68;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  float fStack_40;
  float fStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  
  if (*(long *)(param_1 + 0x760) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962c19/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DirectAofPrimitiveRenderer.cpp"*/,0x1a9,&UNK_0296203b/*"IsInitialized() is null."*/);
  }
  *(undefined4 *)(param_1 + 0x794) = 0;
  uStack_50 = *(undefined8 *)(param_2 + 0x1c);
  uStack_48 = *(undefined4 *)(param_2 + 0x18);
  uStack_44 = 0x3f800000;
  uStack_70 = *(undefined4 *)(param_2 + 0x2c);
  uStack_6c = *(undefined4 *)(param_2 + 0x30);
  uStack_68 = 0x3f80000000000000;
  Aska::ToColorv(unsigned int)(&uStack_a0,*(undefined4 *)(param_2 + 0x3c));
  uStack_88 = uStack_98;
  uStack_90 = uStack_a0;
  uStack_38 = *(undefined4 *)(param_2 + 0x18);
  fStack_40 = *(float *)(param_2 + 0x1c) + *(float *)(param_2 + 0x24);
  fStack_3c = *(float *)(param_2 + 0x20) + *(float *)(param_2 + 0x28);
  uStack_34 = 0x3f800000;
  uStack_60 = *(undefined4 *)(param_2 + 0x34);
  uStack_5c = *(undefined4 *)(param_2 + 0x38);
  uStack_58 = 0x3f80000000000000;
  Aska::ToColorv(unsigned int)(&uStack_a0,*(undefined4 *)(param_2 + 0x3c));
  lVar2 = (ulong)(uint)(*(int *)(param_1 + 0x78c) << 1) * 0x10;
  puVar1 = (undefined8 *)(*(long *)(param_1 + 0x770) + lVar2);
  puVar1[3] = CONCAT44(uStack_34,uStack_38);
  puVar1[2] = CONCAT44(fStack_3c,fStack_40);
  puVar1[1] = CONCAT44(uStack_44,uStack_48);
  *puVar1 = uStack_50;
  puVar1 = (undefined8 *)(*(long *)(param_1 + 0x778) + lVar2);
  puVar1[3] = uStack_58;
  puVar1[2] = CONCAT44(uStack_5c,uStack_60);
  puVar1[1] = uStack_68;
  *puVar1 = CONCAT44(uStack_6c,uStack_70);
  puVar1 = (undefined8 *)(*(long *)(param_1 + 0x780) + lVar2);
  puVar1[3] = uStack_98;
  puVar1[2] = uStack_a0;
  puVar1[1] = uStack_88;
  *puVar1 = uStack_90;
  *(int *)(param_1 + 0x78c) = *(int *)(param_1 + 0x78c) + 1;
  return;
}

// ==== Framework::CDirectAofPrimitiveRenderer::Put(Framework::tSpriteParameter_Quad const&)
// vaddr 0x1e77894 | ghidra 0x1f77894 | size 424 | symbol _ZN9Framework27CDirectAofPrimitiveRenderer3PutERKNS_21tSpriteParameter_QuadE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework27CDirectAofPrimitiveRenderer3PutERKNS_21tSpriteParameter_QuadE
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  long lVar2;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined8 uStack_a8;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined8 uStack_98;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined8 uStack_88;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined8 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined8 uStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined8 uStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  
  if (*(long *)(param_1 + 0x760) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962c19/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DirectAofPrimitiveRenderer.cpp"*/,0x1cf,&UNK_0296203b/*"IsInitialized() is null."*/);
  }
  *(undefined4 *)(param_1 + 0x794) = 0;
  uStack_70 = *(undefined8 *)(param_2 + 0x1c);
  uStack_68 = *(undefined4 *)(param_2 + 0x18);
  uStack_64 = 0x3f800000;
  uStack_b0 = *(undefined4 *)(param_2 + 0x24);
  uStack_ac = *(undefined4 *)(param_2 + 0x28);
  uStack_a8 = 0x3f80000000000000;
  Aska::ToColorv(unsigned int)(&uStack_100,*(undefined4 *)(param_2 + 0x2c));
  uStack_e8 = uStack_f8;
  uStack_f0 = uStack_100;
  uStack_60 = *(undefined8 *)(param_2 + 0x30);
  uStack_58 = *(undefined4 *)(param_2 + 0x18);
  uStack_54 = 0x3f800000;
  uStack_a0 = *(undefined4 *)(param_2 + 0x38);
  uStack_9c = *(undefined4 *)(param_2 + 0x3c);
  uStack_98 = 0x3f80000000000000;
  Aska::ToColorv(unsigned int)(&uStack_100,*(undefined4 *)(param_2 + 0x40));
  uStack_d8 = uStack_f8;
  uStack_e0 = uStack_100;
  uStack_50 = *(undefined8 *)(param_2 + 0x44);
  uStack_48 = *(undefined4 *)(param_2 + 0x18);
  uStack_44 = 0x3f800000;
  uStack_90 = *(undefined4 *)(param_2 + 0x4c);
  uStack_8c = *(undefined4 *)(param_2 + 0x50);
  uStack_88 = 0x3f80000000000000;
  Aska::ToColorv(unsigned int)(&uStack_100,*(undefined4 *)(param_2 + 0x54));
  uStack_c8 = uStack_f8;
  uStack_d0 = uStack_100;
  uStack_40 = *(undefined8 *)(param_2 + 0x58);
  uStack_38 = *(undefined4 *)(param_2 + 0x18);
  uStack_34 = 0x3f800000;
  uStack_80 = *(undefined4 *)(param_2 + 0x60);
  uStack_7c = *(undefined4 *)(param_2 + 100);
  uStack_78 = 0x3f80000000000000;
  Aska::ToColorv(unsigned int)(&uStack_100,*(undefined4 *)(param_2 + 0x68));
  lVar2 = (ulong)(uint)(*(int *)(param_1 + 0x78c) << 2) * 0x10;
  puVar1 = (undefined8 *)(*(long *)(param_1 + 0x770) + lVar2);
  puVar1[7] = CONCAT44(uStack_34,uStack_38);
  puVar1[6] = uStack_40;
  puVar1[5] = CONCAT44(uStack_44,uStack_48);
  puVar1[4] = uStack_50;
  puVar1[3] = CONCAT44(uStack_54,uStack_58);
  puVar1[2] = uStack_60;
  puVar1[1] = CONCAT44(uStack_64,uStack_68);
  *puVar1 = uStack_70;
  puVar1 = (undefined8 *)(*(long *)(param_1 + 0x778) + lVar2);
  puVar1[7] = uStack_78;
  puVar1[6] = CONCAT44(uStack_7c,uStack_80);
  puVar1[5] = uStack_88;
  puVar1[4] = CONCAT44(uStack_8c,uStack_90);
  puVar1[3] = uStack_98;
  puVar1[2] = CONCAT44(uStack_9c,uStack_a0);
  puVar1[1] = uStack_a8;
  *puVar1 = CONCAT44(uStack_ac,uStack_b0);
  puVar1 = (undefined8 *)(*(long *)(param_1 + 0x780) + lVar2);
  puVar1[7] = uStack_f8;
  puVar1[6] = uStack_100;
  puVar1[5] = uStack_c8;
  puVar1[4] = uStack_d0;
  puVar1[3] = uStack_d8;
  puVar1[2] = uStack_e0;
  puVar1[1] = uStack_e8;
  *puVar1 = uStack_f0;
  *(int *)(param_1 + 0x78c) = *(int *)(param_1 + 0x78c) + 1;
  return;
}

// ==== Framework::CDirectAofPrimitiveRenderer::Position(Framework::CVector const&)
// vaddr 0x1e77a3c | ghidra 0x1f77a3c | size 68 | symbol _ZN9Framework27CDirectAofPrimitiveRenderer8PositionERKNS_7CVectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework27CDirectAofPrimitiveRenderer8PositionERKNS_7CVectorE
               (long param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = *param_2;
  uVar2 = param_2[1];
  uVar3 = param_2[2];
  if ((*(byte *)(param_1 + 0x128) & 1) == 0) {
    Aska::HierarchicalObjectContainer::UpdateHierarchically()(param_1 + 0x30);
  }
  *(undefined4 *)(param_1 + 0x80) = uVar1;
  *(undefined4 *)(param_1 + 0x84) = uVar2;
  *(undefined4 *)(param_1 + 0x88) = uVar3;
  *(undefined4 *)(param_1 + 0x8c) = 0x3f800000;
  return;
}

// ==== Framework::CDirectAofPrimitiveRenderer::Priority(float)
// vaddr 0x1e77a80 | ghidra 0x1f77a80 | size 60 | symbol _ZN9Framework27CDirectAofPrimitiveRenderer8PriorityEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework27CDirectAofPrimitiveRenderer8PriorityEf(undefined4 param_1,long param_2)

{
  if ((*(byte *)(param_2 + 0x128) & 1) == 0) {
    Aska::HierarchicalObjectContainer::UpdateHierarchically()(param_2 + 0x30);
  }
  *(undefined8 *)(param_2 + 0x80) = 0;
  *(undefined4 *)(param_2 + 0x88) = param_1;
  *(undefined4 *)(param_2 + 0x8c) = 0x3f800000;
  return;
}

// ==== Framework::CDirectAofPrimitiveRenderer::~CDirectAofPrimitiveRenderer()
// vaddr 0x1e77abc | ghidra 0x1f77abc | size 88 | symbol _ZN9Framework27CDirectAofPrimitiveRendererD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework27CDirectAofPrimitiveRendererD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework27CDirectAofPrimitiveRendererE_02cc4db0 + 0x10);
  Aska::Task::Remove()();
  if (param_1[0xf0] != 0) {
    operator delete[](void*)();
    param_1[0xf0] = 0;
  }
  if (param_1[0xef] != 0) {
    operator delete[](void*)();
    param_1[0xef] = 0;
  }
  if (param_1[0xee] != 0) {
    operator delete[](void*)();
    param_1[0xee] = 0;
  }
  (*(code *)PTR__ZN4Aska9AofObjectD2Ev_02c9f068)(param_1);
  return;
}

// ==== Framework::CDirectAofPrimitiveRenderer::~CDirectAofPrimitiveRenderer()
// vaddr 0x1e77b14 | ghidra 0x1f77b14 | size 96 | symbol _ZN9Framework27CDirectAofPrimitiveRendererD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework27CDirectAofPrimitiveRendererD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework27CDirectAofPrimitiveRendererE_02cc4db0 + 0x10);
  Aska::Task::Remove()();
  if (param_1[0xf0] != 0) {
    operator delete[](void*)();
    param_1[0xf0] = 0;
  }
  if (param_1[0xef] != 0) {
    operator delete[](void*)();
    param_1[0xef] = 0;
  }
  if (param_1[0xee] != 0) {
    operator delete[](void*)();
    param_1[0xee] = 0;
  }
  Aska::AofObject::~AofObject()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DirectAofHandler::IsDirectAof() const
// vaddr 0x1e77e74 | ghidra 0x1f77e74 | size 8 | symbol _ZNK4Aska16DirectAofHandler11IsDirectAofEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16DirectAofHandler11IsDirectAofEv(void)

{
  return 1;
}

// ==== Framework::CDirectAofTextRenderer::CDirectAofTextRenderer()
// vaddr 0x1e77ecc | ghidra 0x1f77ecc | size 400 | symbol _ZN9Framework22CDirectAofTextRendererC2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework22CDirectAofTextRendererC1Ev(long *param_1)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  
  Aska::AofObject::AofObject()();
  *param_1 = (long)(PTR__ZTVN9Framework22CDirectAofTextRendererE_02cc4b08 + 0x10);
  Aska::FontHandle::FontHandle()(param_1 + 0xd6);
  param_1[0xd8] = (long)(PTR__ZTVN4Aska19TTextCompositorBaseINS_4Utf8EEE_02cc36d8 + 0x10);
  Aska::FontHandle::FontHandle()(param_1 + 0xd9);
  uVar3 = _UNK_02951628;
  uVar2 = _UNK_02951620;
  *(undefined4 *)(param_1 + 0xdc) = 0;
  param_1[0xdb] = 0;
  param_1[0xda] = 0;
  *(undefined8 *)((long)param_1 + 0x6ec) = uVar3;
  *(undefined8 *)((long)param_1 + 0x6e4) = uVar2;
  *(undefined4 *)((long)param_1 + 0x6f4) = 0xffffffff;
  puVar1 = PTR__ZTVN4Aska15TTextCompositorINS_4Utf8EEE_02cbd340 + 0x10;
  *(undefined2 *)(param_1 + 0xdf) = 8;
  *(undefined1 *)((long)param_1 + 0x6fa) = 0;
  param_1[0xd8] = (long)puVar1;
  memset(param_1 + 0xe0,0,0xd5);
  *(undefined1 *)((long)param_1 + 0x7d5) = 0;
  *(undefined4 *)(param_1 + 0xfb) = 0;
  param_1[0xff] = 0;
  param_1[0xfe] = 0;
  param_1[0x103] = 0;
  param_1[0x102] = 0;
  param_1[0x101] = 0;
  param_1[0x100] = 0;
  param_1[0xfd] = 0;
  param_1[0xfc] = 0;
  *(undefined4 *)((long)param_1 + 0x7f4) = 0;
  *(undefined4 *)(param_1 + 0xff) = 0;
  *(undefined4 *)(param_1 + 0x102) = 0;
  param_1[0x100] = 0;
  param_1[0x101] = 0;
  *(undefined4 *)((long)param_1 + 0x814) = 0;
  *(undefined4 *)(param_1 + 0x103) = 0;
  *(undefined4 *)(param_1 + 0x104) = 0;
  puVar4 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(200,PTR__ZSt7nothrow_02cb9a80);
  if (puVar4 == (undefined8 *)0x0) {
    puVar5 = (undefined8 *)0x0;
  }
  else {
    *puVar4 = 4;
    puVar5 = puVar4 + 1;
    *puVar5 = 0;
    puVar4[2] = 0;
    puVar4[3] = 0;
    puVar4[8] = 0;
    puVar4[9] = 0;
    puVar4[7] = 0;
    puVar4[0xe] = 0;
    puVar4[0xf] = 0;
    puVar4[0xd] = 0;
    puVar4[0x14] = 0;
    puVar4[0x15] = 0;
    puVar4[0x13] = 0;
  }
  param_1[0xfc] = (long)puVar5;
  *(undefined4 *)(param_1 + 0xfe) = 0;
  param_1[0xfd] = 4;
  *(undefined4 *)((long)param_1 + 0x7f4) = 0;
  *(undefined4 *)(param_1 + 0xff) = 0;
  puVar4 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(200,PTR__ZSt7nothrow_02cb9a80);
  if (puVar4 == (undefined8 *)0x0) {
    puVar5 = (undefined8 *)0x0;
  }
  else {
    *puVar4 = 4;
    puVar5 = puVar4 + 1;
    *puVar5 = 0;
    puVar4[2] = 0;
    puVar4[3] = 0;
    puVar4[8] = 0;
    puVar4[9] = 0;
    puVar4[7] = 0;
    puVar4[0xe] = 0;
    puVar4[0xf] = 0;
    puVar4[0xd] = 0;
    puVar4[0x14] = 0;
    puVar4[0x15] = 0;
    puVar4[0x13] = 0;
  }
  param_1[0x100] = (long)puVar5;
  *(undefined4 *)(param_1 + 0x102) = 0;
  param_1[0x101] = 4;
  *(undefined4 *)((long)param_1 + 0x814) = 0;
  *(undefined4 *)(param_1 + 0x103) = 0;
  return;
}

// ==== Framework::CDirectAofTextRenderer::tPutPool::Setup()
// vaddr 0x1e7805c | ghidra 0x1f7805c | size 108 | symbol _ZN9Framework22CDirectAofTextRenderer8tPutPool5SetupEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CDirectAofTextRenderer8tPutPool5SetupEv(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(200,PTR__ZSt7nothrow_02cb9a80);
  if (puVar1 == (undefined8 *)0x0) {
    puVar2 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = 4;
    puVar2 = puVar1 + 1;
    *puVar2 = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[8] = 0;
    puVar1[9] = 0;
    puVar1[7] = 0;
    puVar1[0xe] = 0;
    puVar1[0xf] = 0;
    puVar1[0xd] = 0;
    puVar1[0x14] = 0;
    puVar1[0x15] = 0;
    puVar1[0x13] = 0;
  }
  *(undefined4 *)(param_1 + 2) = 0;
  *param_1 = puVar2;
  param_1[1] = 4;
  *(undefined4 *)((long)param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 3) = 0;
  return;
}

// ==== Framework::CDirectAofTextRenderer::~CDirectAofTextRenderer()
// vaddr 0x1e780c8 | ghidra 0x1f780c8 | size 192 | symbol _ZN9Framework22CDirectAofTextRendererD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CDirectAofTextRendererD1Ev(long *param_1)

{
  long lVar1;
  long lVar2;
  
  *param_1 = (long)(PTR__ZTVN9Framework22CDirectAofTextRendererE_02cc4b08 + 0x10);
  Aska::Task::Remove()();
  lVar2 = param_1[0x100];
  if (lVar2 != 0) {
    lVar1 = *(long *)(lVar2 + -8);
    if (lVar1 != 0) {
      lVar1 = lVar1 * 0x30;
      do {
        if ((*(byte *)(lVar2 + lVar1 + -0x30) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar2 + lVar1 + -0x20));
        }
        lVar1 = lVar1 + -0x30;
      } while (lVar1 != 0);
    }
    operator delete[](void*)((long *)(lVar2 + -8));
    param_1[0x100] = 0;
  }
  lVar2 = param_1[0xfc];
  if (lVar2 != 0) {
    lVar1 = *(long *)(lVar2 + -8);
    if (lVar1 != 0) {
      lVar1 = lVar1 * 0x30;
      do {
        if ((*(byte *)(lVar2 + lVar1 + -0x30) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar2 + lVar1 + -0x20));
        }
        lVar1 = lVar1 + -0x30;
      } while (lVar1 != 0);
    }
    operator delete[](void*)((long *)(lVar2 + -8));
    param_1[0xfc] = 0;
  }
  (*(code *)PTR__ZN4Aska9AofObjectD2Ev_02c9f068)(param_1);
  return;
}

// ==== Framework::CDirectAofTextRenderer::Release()
// vaddr 0x1e78188 | ghidra 0x1f78188 | size 4 | symbol _ZN9Framework22CDirectAofTextRenderer7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CDirectAofTextRenderer7ReleaseEv(void)

{
  (*(code *)PTR__ZN4Aska4Task6RemoveEv_02cb3550)();
  return;
}

// ==== Framework::CDirectAofTextRenderer::~CDirectAofTextRenderer()
// vaddr 0x1e7818c | ghidra 0x1f7818c | size 24 | symbol _ZN9Framework22CDirectAofTextRendererD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CDirectAofTextRendererD0Ev(undefined8 param_1)

{
  Framework::CDirectAofTextRenderer::~CDirectAofTextRenderer()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CDirectAofTextRenderer::Initialize(int, Aska::FontHandle, Framework::CSTLVector<unsigned long> const&, unsigned int, bool)
// vaddr 0x1e781a4 | ghidra 0x1f781a4 | size 480 | symbol _ZN9Framework22CDirectAofTextRenderer10InitializeEiN4Aska10FontHandleERKNS_10CSTLVectorImEEjb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CDirectAofTextRenderer10InitializeEiN4Aska10FontHandleERKNS_10CSTLVectorImEEjb
               (long *param_1,int param_2,long param_3,long *param_4,uint param_5,byte param_6)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  long lVar4;
  long lVar5;
  undefined4 uVar6;
  
  param_1[0xd6] = param_3;
  *(byte *)((long)param_1 + 0x7d4) = param_6 & 1;
  lVar4 = Aska::FontManagerProxy::Find(Aska::FontHandle const&)(param_1 + 0xd6);
  if (lVar4 == 0) {
    lVar4 = 0;
  }
  else {
    lVar4 = *(long *)(lVar4 + 0x68);
  }
  param_1[0xd9] = param_1[0xd6];
  lVar5 = Aska::FontHandle::ToFont() const(param_1 + 0xd6);
  if (lVar5 != 0) {
    uVar6 = NEON_ucvtf((uint)*(byte *)(lVar5 + 0x58));
    *(undefined4 *)((long)param_1 + 0x6e4) = uVar6;
    uVar6 = NEON_ucvtf((uint)*(byte *)(lVar5 + 0x59));
    *(undefined4 *)(param_1 + 0xdd) = uVar6;
  }
  param_1[0xda] = 0;
  *(undefined8 *)((long)param_1 + 0x6e4) = 0x41c0000041c00000;
  *(undefined4 *)((long)param_1 + 0x6ec) = 0x40400000;
  *(undefined4 *)((long)param_1 + 0x6f4) = 0xffffffff;
  Aska::DirectAofText::SetDefaultMaterial(Aska::DirectMaterial*)(param_1 + 0xe2);
  *(undefined2 *)((long)param_1 + 0x713) = 0xa102;
  *(undefined1 *)((long)param_1 + 0x715) = 1;
  *(ushort *)((long)param_1 + 0x71f) = *(ushort *)((long)param_1 + 0x71f) & 0xfffe;
  *(undefined2 *)((long)param_1 + 0x77e) = 0x201;
  lVar5 = *(long *)*param_4;
  param_1[0xf2] = lVar4;
  param_1[0xee] = lVar5;
  if (1 < param_2) {
    param_1[0xf0] = *(long *)(*param_4 + 8);
  }
  if (param_5 < 9) {
    param_5 = 8;
  }
  Framework::CDirectAofTextRenderer::Reserve(unsigned int)(param_1,param_5);
  (**(code **)(*param_1 + 0x248))(param_1,2);
  (**(code **)(*param_1 + 0x160))(param_1,0xe5);
  puVar2 = PTR__ZN9Framework10TSingletonINS_9CCamera2DEE11m_pInstanceE_02cbe730;
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonINS_9CCamera2DEE11m_pInstanceE_02cbe730;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029612b1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar2;
  }
  lVar4 = *(long *)(lVar4 + 8);
  param_1[0x34] = lVar4;
  uVar1 = *(uint *)(param_1 + 0x33) & 0xff3ffffd;
  if (lVar4 != 0) {
    uVar1 = *(uint *)(param_1 + 0x33) | 0x800000;
  }
  *(uint *)(param_1 + 0x33) = uVar1 | 0x400002;
  (**(code **)(*param_1 + 200))(0,0,0,param_1);
  iVar3 = iRam0000000002cc7094 + 1;
  *(int *)(param_1 + 0xfa) = iRam0000000002cc7094;
  iRam0000000002cc7094 = iVar3;
  *(ushort *)((long)param_1 + 0x24) = *(ushort *)((long)param_1 + 0x24) & 0xfffd;
  return;
}

// ==== Framework::CDirectAofTextRenderer::Reserve(unsigned int)
// vaddr 0x1e78384 | ghidra 0x1f78384 | size 900 | symbol _ZN9Framework22CDirectAofTextRenderer7ReserveEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CDirectAofTextRenderer7ReserveEj(long *param_1,uint param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  uint uVar3;
  undefined4 uVar4;
  long lVar5;
  long *plVar6;
  ulong uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  long lVar11;
  undefined *apuStack_c0 [2];
  undefined8 uStack_b0;
  long lStack_80;
  long lStack_78;
  undefined4 uStack_68;
  undefined4 uStack_64;
  
  if (*(uint *)(param_1 + 0xf9) < param_2) {
    plVar6 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x3f0,PTR__ZSt7nothrow_02cb9a80);
    if (plVar6 != (long *)0x0) {
      memset(plVar6,0,0x3f0);
      Aska::DirectAofText::DirectAofText()(plVar6);
      puVar1 = PTR__ZTVN9Framework15DirectAofTextExE_02cba3d0 + 0xb8;
      puVar2 = PTR__ZTVN9Framework15DirectAofTextExE_02cba3d0 + 0xe0;
      *plVar6 = (long)(PTR__ZTVN9Framework15DirectAofTextExE_02cba3d0 + 0x10);
      plVar6[0x14] = (long)puVar2;
      plVar6[0x13] = (long)puVar1;
    }
    uVar7 = Aska::DirectAofHandler::Create(int, bool, char const*)(plVar6,1,*(undefined1 *)((long)param_1 + 0x7d4),&UNK_02909eab/*"Text"*/);
    if ((uVar7 & 1) != 0) {
      memcpy((ulong)apuStack_c0 | 8,param_1 + 0xd9,0x33);
      apuStack_c0[0] = PTR__ZTVN4Aska15TTextCompositorINS_4Utf8EEE_02cbd340 + 0x10;
      lStack_78 = param_1[0xe1];
      lStack_80 = param_1[0xe0];
      iVar9 = param_2 - 1;
      uStack_b0 = -0x3b86000000000000;
      if (iVar9 == 0) {
        iVar9 = 0;
        do {
          Aska::DirectAofHandler::Open()(plVar6);
          Aska::DirectAofText::BeginStringMesh(Aska::DirectMaterial*, unsigned long)(plVar6,param_1 + 0xe2,param_2);
          plVar6[0x7c] = 0;
          lVar11 = plVar6[0x6d];
          lVar5 = plVar6[0x6e];
          uVar3 = (int)*(short *)((long)plVar6 + 0x3dc) &
                  ((int)*(short *)((long)plVar6 + 0x3dc) >> 0xf ^ 0xffffffffU);
          *(ushort *)((long)plVar6 + 0x3ec) =
               (ushort)(uVar3 >> 8) & 0xff | (ushort)((uVar3 & 0xff00ff) << 8);
          uVar4 = *(undefined4 *)((long)plVar6 + 0x374);
          uStack_68 = uStack_b0._4_4_;
          uStack_64 = (undefined4)uStack_b0;
          lStack_80 = uStack_b0;
          lStack_78 = uStack_b0;
          void Aska::TTextCompositor<Aska::Utf8>::ComposeString_<Aska::DirectAofText::CharPrinter>(float*, float*, Aska::Vector*, unsigned long, char const*, Aska::DirectAofText::CharPrinter) const(apuStack_c0,&uStack_64,&uStack_68,&lStack_80,0xffffffffffffffff,
                          &UNK_02a4f23f/*"a"*/,plVar6);
          uStack_b0 = CONCAT44(uStack_68,uStack_64);
          if (plVar6[0x7c] != 0) {
            uVar3 = *(byte *)((long)plVar6 + 0x353) + 0xffff;
            Aska::detail::AnimationGroupContainer::AddPrimitive(Aska::AofhMeshset*, unsigned short, unsigned int, unsigned int)(plVar6 + 0x70,
                            *(undefined8 *)(plVar6[0x1a] + (ulong)(uVar3 & 0xffff) * 8),uVar3,
                            (int)lVar5,uVar4);
          }
          *(undefined4 *)(lVar11 + 0xc) = 0;
          *(undefined4 *)(lVar11 + 0x38) = 0;
          *(undefined4 *)(lVar11 + 100) = 0;
          *(undefined4 *)(lVar11 + 0x90) = 0;
          Aska::DirectAofHandler::EndMesh()(plVar6);
          Aska::DirectAofHandler::Close(Aska::Vector const*, bool)(plVar6,&UNK_02962e30,0);
          Aska::DirectAofHandler::FlipBuffer(int)(plVar6,0);
          iVar9 = iVar9 + 1;
          uVar3 = param_2;
          if (*(char *)((long)param_1 + 0x7d4) != '\0') {
            uVar3 = param_2 + 1;
          }
        } while (iVar9 < (int)uVar3);
      }
      else {
        iVar10 = 0;
        do {
          Aska::DirectAofHandler::Open()(plVar6);
          Aska::DirectAofText::BeginStringMesh(Aska::DirectMaterial*, unsigned long)(plVar6,param_1 + 0xe2,param_2);
          plVar6[0x7c] = 0;
          lVar11 = plVar6[0x6d];
          lVar5 = plVar6[0x6e];
          uVar3 = (int)*(short *)((long)plVar6 + 0x3dc) &
                  ((int)*(short *)((long)plVar6 + 0x3dc) >> 0xf ^ 0xffffffffU);
          *(ushort *)((long)plVar6 + 0x3ec) =
               (ushort)(uVar3 >> 8) & 0xff | (ushort)((uVar3 & 0xff00ff) << 8);
          uVar4 = *(undefined4 *)((long)plVar6 + 0x374);
          uStack_68 = uStack_b0._4_4_;
          uStack_64 = (undefined4)uStack_b0;
          lStack_80 = uStack_b0;
          lStack_78 = uStack_b0;
          void Aska::TTextCompositor<Aska::Utf8>::ComposeString_<Aska::DirectAofText::CharPrinter>(float*, float*, Aska::Vector*, unsigned long, char const*, Aska::DirectAofText::CharPrinter) const(apuStack_c0,&uStack_64,&uStack_68,&lStack_80,0xffffffffffffffff,
                          &UNK_02a4f23f/*"a"*/,plVar6);
          uStack_b0 = CONCAT44(uStack_68,uStack_64);
          if (plVar6[0x7c] != 0) {
            uVar3 = *(byte *)((long)plVar6 + 0x353) + 0xffff;
            Aska::detail::AnimationGroupContainer::AddPrimitive(Aska::AofhMeshset*, unsigned short, unsigned int, unsigned int)(plVar6 + 0x70,
                            *(undefined8 *)(plVar6[0x1a] + (ulong)(uVar3 & 0xffff) * 8),uVar3,
                            (int)lVar5,uVar4);
          }
          *(undefined4 *)(lVar11 + 0xc) = 0;
          *(undefined4 *)(lVar11 + 0x38) = 0;
          *(undefined4 *)(lVar11 + 100) = 0;
          *(undefined4 *)(lVar11 + 0x90) = 0;
          memset(plVar6[0x6d],0,iVar9 * 0xb0);
          plVar6[0x6d] = lVar11 + (ulong)(param_2 << 2) * 0x2c;
          *(int *)((long)plVar6 + 0x374) = *(int *)((long)plVar6 + 0x374) + iVar9 * 4;
          Aska::DirectAofHandler::EndMesh()(plVar6);
          Aska::DirectAofHandler::Close(Aska::Vector const*, bool)(plVar6,&UNK_02962e30,0);
          Aska::DirectAofHandler::FlipBuffer(int)(plVar6,0);
          iVar10 = iVar10 + 1;
          iVar8 = 1;
          if (*(char *)((long)param_1 + 0x7d4) != '\0') {
            iVar8 = 2;
          }
        } while (iVar10 < iVar8);
      }
    }
    (**(code **)(*param_1 + 0x2d0))(param_1,plVar6,1);
    param_1[0xf8] = (long)plVar6;
    *(uint *)(param_1 + 0xf9) = param_2;
    *(undefined4 *)((long)param_1 + 0x7f4) = 0;
    *(undefined4 *)((long)param_1 + 0x814) = 0;
  }
  return;
}

// ==== Framework::CDirectAofTextRenderer::Priority(float)
// vaddr 0x1e78708 | ghidra 0x1f78708 | size 24 | symbol _ZN9Framework22CDirectAofTextRenderer8PriorityEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CDirectAofTextRenderer8PriorityEf(undefined8 param_1,long *param_2)

{
                    /* WARNING: Could not recover jumptable at 0x01f7871c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_2 + 200))(0,0,param_1);
  return;
}

// ==== Framework::CDirectAofTextRenderer::PreliminarilyPrepare(Aska::LightManager*)
// vaddr 0x1e78720 | ghidra 0x1f78720 | size 904 | symbol _ZN9Framework22CDirectAofTextRenderer20PreliminarilyPrepareEPN4Aska12LightManagerE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint _ZN9Framework22CDirectAofTextRenderer20PreliminarilyPrepareEPN4Aska12LightManagerE
               (long param_1,undefined8 param_2)

{
  long lVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  char cVar5;
  bool bVar6;
  uint uVar7;
  int iVar8;
  long lVar9;
  ulong uVar10;
  long lVar11;
  int iVar12;
  undefined8 *puVar13;
  undefined *apuStack_c0 [2];
  undefined8 uStack_b0;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  float fStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined8 uStack_80;
  undefined8 uStack_78;
  uint uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  
  DataMemoryBarrier(2,3);
  if ((*(int *)(param_1 + 0x7d8) == 0) && (lVar9 = *(long *)(param_1 + 0x7c0), lVar9 != 0)) {
    uStack_6c = *(uint *)(param_1 + 0x820);
    uVar10 = (ulong)uStack_6c;
    if (1 < uStack_6c) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962e40/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Array.h"*/,0x25,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar10,2);
    }
    lVar11 = param_1 + uVar10 * 0x20;
    uVar7 = *(uint *)(lVar11 + 0x7f0);
    if (*(uint *)(param_1 + 0x7c8) < uVar7) {
      Framework::CDirectAofTextRenderer::Reserve(unsigned int)(param_1,uVar7);
      lVar9 = *(long *)(param_1 + 0x7c0);
    }
    if ((*(int *)(lVar11 + 0x7f4) == 0) || (*(int *)(lVar11 + 0x7f0) != *(int *)(lVar11 + 0x7f8))) {
      lVar1 = param_1 + uVar10 * 0x20;
      *(undefined4 *)(lVar11 + 0x7f4) = 1;
      *(int *)(lVar11 + 0x7f8) = *(int *)(lVar11 + 0x7f0);
      lVar11 = *(long *)(lVar1 + 0x7e0);
      uVar2 = *(uint *)(lVar1 + 0x7ec);
      uVar10 = (ulong)uVar2;
      memcpy((ulong)apuStack_c0 | 8,param_1 + 0x6c8,0x33);
      apuStack_c0[0] = PTR__ZTVN4Aska15TTextCompositorINS_4Utf8EEE_02cbd340 + 0x10;
      uStack_78 = *(undefined8 *)(param_1 + 0x708);
      uStack_80 = *(undefined8 *)(param_1 + 0x700);
      Aska::DirectAofHandler::Open()(lVar9);
      if (uVar7 == 0) {
        Aska::DirectAofText::BeginStringMesh(Aska::DirectMaterial*, unsigned long)(lVar9,param_1 + 0x710,*(undefined4 *)(param_1 + 0x7c8));
        uStack_78 = _UNK_02962d98;
        uStack_80 = _UNK_02962d90;
        uStack_b0 = 0xc47a000000000000;
        iVar12 = *(int *)(param_1 + 0x7c8);
        lVar11 = *(long *)(lVar9 + 0x368);
        uVar3 = *(undefined4 *)(lVar9 + 0x370);
        uVar7 = (int)*(short *)(lVar9 + 0x3dc) &
                ((int)*(short *)(lVar9 + 0x3dc) >> 0xf ^ 0xffffffffU);
        uVar4 = *(undefined4 *)(lVar9 + 0x374);
        *(ushort *)(lVar9 + 0x3ec) = (ushort)(uVar7 >> 8) & 0xff | (ushort)((uVar7 & 0xff00ff) << 8)
        ;
        *(undefined8 *)(lVar9 + 0x3e0) = 0;
        uStack_68 = 0xc47a0000;
        uStack_64 = 0;
        void Aska::TTextCompositor<Aska::Utf8>::ComposeString_<Aska::DirectAofText::CharPrinter>(float*, float*, Aska::Vector*, unsigned long, char const*, Aska::DirectAofText::CharPrinter) const(apuStack_c0,&uStack_64,&uStack_68,&uStack_80,0xffffffffffffffff,
                        &UNK_02a4f23f/*"a"*/,lVar9);
        uStack_b0 = CONCAT44(uStack_68,uStack_64);
        if (*(long *)(lVar9 + 0x3e0) != 0) {
          uVar7 = *(byte *)(lVar9 + 0x353) + 0xffff;
          Aska::detail::AnimationGroupContainer::AddPrimitive(Aska::AofhMeshset*, unsigned short, unsigned int, unsigned int)(lVar9 + 0x380,
                          *(undefined8 *)(*(long *)(lVar9 + 0xd0) + (ulong)(uVar7 & 0xffff) * 8),
                          uVar7,uVar3,uVar4);
        }
        iVar8 = iVar12 + -1;
        *(undefined4 *)(lVar11 + 0xc) = 0;
        *(undefined4 *)(lVar11 + 0x38) = 0;
        *(undefined4 *)(lVar11 + 100) = 0;
        *(undefined4 *)(lVar11 + 0x90) = 0;
        if (iVar8 != 0) {
          memset(*(undefined8 *)(lVar9 + 0x368),0,iVar8 * 0xb0);
          *(ulong *)(lVar9 + 0x368) = lVar11 + (ulong)(uint)(iVar12 << 2) * 0x2c;
          *(int *)(lVar9 + 0x374) = *(int *)(lVar9 + 0x374) + iVar8 * 4;
        }
        Aska::DirectAofHandler::EndMesh()(lVar9);
        iVar12 = 0;
        *(uint *)(param_1 + 0x198) = *(uint *)(param_1 + 0x198) | 1;
      }
      else {
        Aska::DirectAofText::BeginStringMesh(Aska::DirectMaterial*, unsigned long)(lVar9,param_1 + 0x710,uVar7);
        iVar12 = 0;
        if (uVar2 != 0) {
          puVar13 = (undefined8 *)(lVar11 + 0x18);
          do {
            uStack_a4 = *(undefined4 *)puVar13;
            uStack_a0 = *(undefined4 *)((long)puVar13 + 4);
            uStack_78 = *puVar13;
            uStack_80 = *puVar13;
            uStack_b0 = *puVar13;
            uStack_9c = *(undefined4 *)(puVar13 + 1);
            uStack_98 = *(undefined4 *)(puVar13 + 1);
            fStack_94 = (float)(int)*(float *)((long)puVar13 + 0x14);
            uStack_90 = *(undefined4 *)(puVar13 + 2);
            uStack_8c = *(undefined4 *)((long)puVar13 + 0xc);
            if ((*(byte *)(puVar13 + -3) & 1) == 0) {
              lVar11 = (long)puVar13 + -0x17;
            }
            else {
              lVar11 = puVar13[-1];
            }
            uVar3 = *(undefined4 *)(lVar9 + 0x370);
            uVar4 = *(undefined4 *)(lVar9 + 0x374);
            uVar7 = (int)*(short *)(lVar9 + 0x3dc) &
                    ((int)*(short *)(lVar9 + 0x3dc) >> 0xf ^ 0xffffffffU);
            *(undefined8 *)(lVar9 + 0x3e0) = 0;
            *(ushort *)(lVar9 + 0x3ec) =
                 (ushort)(uVar7 >> 8) & 0xff | (ushort)((uVar7 & 0xff00ff) << 8);
            uStack_68 = uStack_a0;
            uStack_64 = uStack_a4;
            void Aska::TTextCompositor<Aska::Utf8>::ComposeString_<Aska::DirectAofText::CharPrinter>(float*, float*, Aska::Vector*, unsigned long, char const*, Aska::DirectAofText::CharPrinter) const(apuStack_c0,&uStack_64,&uStack_68,&uStack_80,0xffffffffffffffff,lVar11,
                            lVar9);
            uStack_b0 = CONCAT44(uStack_68,uStack_64);
            iVar8 = 0;
            if (*(long *)(lVar9 + 0x3e0) != 0) {
              uVar7 = *(byte *)(lVar9 + 0x353) + 0xffff;
              Aska::detail::AnimationGroupContainer::AddPrimitive(Aska::AofhMeshset*, unsigned short, unsigned int, unsigned int)(lVar9 + 0x380,
                              *(undefined8 *)(*(long *)(lVar9 + 0xd0) + (ulong)(uVar7 & 0xffff) * 8)
                              ,uVar7,uVar3,uVar4);
              iVar8 = (int)*(undefined8 *)(lVar9 + 0x3e0);
            }
            iVar12 = iVar12 + iVar8;
            uVar10 = uVar10 - 1;
            puVar13 = puVar13 + 6;
          } while (uVar10 != 0);
        }
        Aska::DirectAofHandler::EndMesh()(lVar9);
      }
      Aska::DirectAofHandler::Close(Aska::Vector const*, bool)(lVar9,&UNK_02962e30,0);
      *(int *)(param_1 + 0x7cc) = iVar12;
    }
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass((undefined4 *)(param_1 + 0x7d8),0x10);
      if (bVar6) {
        *(undefined4 *)(param_1 + 0x7d8) = 1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    uVar7 = Aska::AofObject::PreliminarilyPrepare(Aska::LightManager*)(param_1,param_2);
  }
  else {
    uVar7 = 0;
  }
  return uVar7 & 1;
}

// ==== Framework::CDirectAofTextRenderer::Reset()
// vaddr 0x1e78aa8 | ghidra 0x1f78aa8 | size 136 | symbol _ZN9Framework22CDirectAofTextRenderer5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CDirectAofTextRenderer5ResetEv(long param_1)

{
  uint uVar1;
  char cVar2;
  bool bVar3;
  
  DataMemoryBarrier(2,3);
  if (*(int *)(param_1 + 0x7d8) != 0) {
    uVar1 = ~*(uint *)(param_1 + 0x820) & 1;
    if (1 < uVar1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962e40/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Array.h"*/,0x25,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,(ulong)uVar1,2);
    }
    *(undefined8 *)(param_1 + (ulong)uVar1 * 0x20 + 0x7ec) = 0;
    *(uint *)(param_1 + 0x820) = uVar1;
    *(undefined1 *)(param_1 + 0x7d5) = 0;
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass((undefined4 *)(param_1 + 0x7d8),0x10);
      if (bVar3) {
        *(undefined4 *)(param_1 + 0x7d8) = 0;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
  return;
}

// ==== Framework::CDirectAofTextRenderer::Put(float, float, char const*, float, float, float, unsigned int)
// vaddr 0x1e78b30 | ghidra 0x1f78b30 | size 440 | symbol _ZN9Framework22CDirectAofTextRenderer3PutEffPKcfffj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CDirectAofTextRenderer3PutEffPKcfffj
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,long *param_6,char *param_7,undefined4 param_8)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;
  int iVar4;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  
  uStack_78 = 0;
  uStack_70 = 0;
  uStack_80 = 0;
  uVar2 = strlen(param_7);
  if (uVar2 < 0x16 || uVar2 - 0x16 == 0) {
    if (uVar2 != 0) {
      memcpy((ulong)&uStack_80 | 1,param_7,uVar2);
    }
    *(undefined1 *)((long)&uStack_80 + uVar2 + 1) = 0;
    uStack_80 = CONCAT71(uStack_80._1_7_,(char)(uVar2 << 1));
  }
  else {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&uStack_80,0x16,uVar2 - 0x16,0,0,0,uVar2,param_7);
  }
  DataMemoryBarrier(2,3);
  uStack_68 = param_1;
  uStack_64 = param_2;
  uStack_60 = param_3;
  uStack_5c = param_8;
  uStack_58 = param_4;
  uStack_54 = param_5;
  if ((int)param_6[0xfb] != 0) {
    (**(code **)(*param_6 + 0x2e0))(param_6);
  }
  uVar1 = *(uint *)(param_6 + 0x104);
  if ((param_7 == (char *)0x0) || (*param_7 == '\0')) {
    iVar4 = 0;
  }
  else {
    iVar4 = 0;
    do {
      lVar3 = Aska::Utf8::GetByteSizeAt_(unsigned char)();
      if (lVar3 == 0) {
        lVar3 = 1;
      }
      param_7 = param_7 + lVar3;
      iVar4 = iVar4 + 1;
    } while (*param_7 != '\0');
  }
  uVar2 = (ulong)uVar1;
  if (1 < uVar1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962e40/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Array.h"*/,0x25,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar2,2);
  }
  *(int *)(param_6 + uVar2 * 4 + 0xfe) = (int)param_6[uVar2 * 4 + 0xfe] + iVar4;
  if (1 < uVar1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962e40/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Array.h"*/,0x25,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,(ulong)uVar1,2);
  }
  Framework::CDirectAofTextRenderer::tPutPool::PushBackPool(Framework::CDirectAofTextRenderer::tString const&)(param_6 + (ulong)uVar1 * 4 + 0xfc,&uStack_80);
  if ((uStack_80 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_70);
  }
  return;
}

// ==== Framework::CDirectAofTextRenderer::tPutPool::PushBackPool(Framework::CDirectAofTextRenderer::tString const&)
// vaddr 0x1e78ce8 | ghidra 0x1f78ce8 | size 336 | symbol _ZN9Framework22CDirectAofTextRenderer8tPutPool12PushBackPoolERKNS0_7tStringE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CDirectAofTextRenderer8tPutPool12PushBackPoolERKNS0_7tStringE
               (long *param_1,ulong *param_2)

{
  uint uVar1;
  ulong uVar2;
  byte *pbVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  ulong *puVar8;
  byte *pbVar9;
  long lVar10;
  
  uVar1 = *(uint *)((long)param_1 + 0xc);
  if (*(uint *)(param_1 + 1) <= uVar1) {
    Framework::CDirectAofTextRenderer::tPutPool::_ExpandCore(unsigned int)(param_1,*(uint *)(param_1 + 1) << 1);
    uVar1 = *(uint *)((long)param_1 + 0xc);
  }
  uVar6 = (ulong)uVar1;
  lVar10 = *param_1;
  puVar8 = (ulong *)(lVar10 + uVar6 * 0x30);
  if (puVar8 == param_2) goto code_r0x01f78dfc;
  uVar2 = param_2[1];
  pbVar3 = (byte *)param_2[2];
  uVar7 = (ulong)(byte)*puVar8;
  if (((byte)*param_2 & 1) == 0) {
    pbVar3 = (byte *)((long)param_2 + 1);
    uVar2 = (ulong)(byte)((byte)*param_2 >> 1);
  }
  if (((byte)*puVar8 & 1) == 0) {
    uVar4 = 0x16;
    lVar5 = uVar2 - 0x16;
    if (0x15 < uVar2 && lVar5 != 0) {
code_r0x01f78d84:
      if ((uVar7 & 1) == 0) {
        uVar7 = (ulong)(((uint)uVar7 & 0xfe) >> 1);
      }
      else {
        uVar7 = *(ulong *)(lVar10 + uVar6 * 0x30 + 8);
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar8,uVar4,lVar5,uVar7,0,uVar7,uVar2);
      goto code_r0x01f78dfc;
    }
  }
  else {
    uVar7 = *puVar8;
    uVar4 = (uVar7 & 0xfffffffffffffffe) - 1;
    lVar5 = uVar2 - uVar4;
    if (uVar4 <= uVar2 && lVar5 != 0) goto code_r0x01f78d84;
  }
  if ((uVar7 & 1) == 0) {
    pbVar9 = (byte *)((long)puVar8 + 1);
  }
  else {
    pbVar9 = *(byte **)(lVar10 + uVar6 * 0x30 + 0x10);
  }
  if (uVar2 != 0) {
    memmove(pbVar9,pbVar3,uVar2);
  }
  pbVar9[uVar2] = 0;
  if ((*puVar8 & 1) == 0) {
    *(byte *)puVar8 = (byte)(uVar2 << 1);
  }
  else {
    *(ulong *)(lVar10 + uVar6 * 0x30 + 8) = uVar2;
  }
code_r0x01f78dfc:
  lVar10 = lVar10 + uVar6 * 0x30;
  *(ulong *)(lVar10 + 0x28) = param_2[5];
  uVar6 = param_2[3];
  *(ulong *)(lVar10 + 0x20) = param_2[4];
  *(ulong *)(lVar10 + 0x18) = uVar6;
  *(int *)((long)param_1 + 0xc) = *(int *)((long)param_1 + 0xc) + 1;
  *(undefined4 *)((long)param_1 + 0x14) = 0;
  return;
}

// ==== Framework::CDirectAofTextRenderer::Put(Framework::CDirectAofTextRenderer::tString const&)
// vaddr 0x1e78e38 | ghidra 0x1f78e38 | size 272 | symbol _ZN9Framework22CDirectAofTextRenderer3PutERKNS0_7tStringE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CDirectAofTextRenderer3PutERKNS0_7tStringE(long *param_1,byte *param_2)

{
  uint uVar1;
  byte bVar2;
  long lVar3;
  byte *pbVar4;
  ulong uVar5;
  int iVar6;
  
  DataMemoryBarrier(2,3);
  if ((int)param_1[0xfb] != 0) {
    (**(code **)(*param_1 + 0x2e0))(param_1);
  }
  uVar1 = *(uint *)(param_1 + 0x104);
  if ((*param_2 & 1) == 0) {
    pbVar4 = param_2 + 1;
    bVar2 = *pbVar4;
joined_r0x01f78e94:
    if (bVar2 != 0) {
      iVar6 = 0;
      do {
        lVar3 = Aska::Utf8::GetByteSizeAt_(unsigned char)();
        if (lVar3 == 0) {
          lVar3 = 1;
        }
        pbVar4 = pbVar4 + lVar3;
        iVar6 = iVar6 + 1;
      } while (*pbVar4 != 0);
      goto code_r0x01f78ec0;
    }
  }
  else {
    pbVar4 = *(byte **)(param_2 + 0x10);
    if (pbVar4 != (byte *)0x0) {
      bVar2 = *pbVar4;
      goto joined_r0x01f78e94;
    }
  }
  iVar6 = 0;
code_r0x01f78ec0:
  uVar5 = (ulong)uVar1;
  if (1 < uVar1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962e40/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Array.h"*/,0x25,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar5,2);
  }
  *(int *)(param_1 + uVar5 * 4 + 0xfe) = (int)param_1[uVar5 * 4 + 0xfe] + iVar6;
  if (1 < uVar1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962e40/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Array.h"*/,0x25,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,(ulong)uVar1,2);
  }
  Framework::CDirectAofTextRenderer::tPutPool::PushBackPool(Framework::CDirectAofTextRenderer::tString const&)(param_1 + (ulong)uVar1 * 4 + 0xfc,param_2);
  return;
}

// ==== Framework::CDirectAofTextRenderer::Put(Framework::CDirectAofTextRenderer::tString const&, unsigned int)
// vaddr 0x1e78f48 | ghidra 0x1f78f48 | size 196 | symbol _ZN9Framework22CDirectAofTextRenderer3PutERKNS0_7tStringEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CDirectAofTextRenderer3PutERKNS0_7tStringEj
               (long *param_1,undefined8 param_2,int param_3)

{
  uint uVar1;
  ulong uVar2;
  
  DataMemoryBarrier(2,3);
  if ((int)param_1[0xfb] != 0) {
    (**(code **)(*param_1 + 0x2e0))(param_1);
  }
  uVar1 = *(uint *)(param_1 + 0x104);
  uVar2 = (ulong)uVar1;
  if (1 < uVar1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962e40/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Array.h"*/,0x25,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar2,2);
  }
  *(int *)(param_1 + uVar2 * 4 + 0xfe) = (int)param_1[uVar2 * 4 + 0xfe] + param_3;
  if (1 < uVar1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962e40/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Array.h"*/,0x25,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,(ulong)uVar1,2);
  }
  Framework::CDirectAofTextRenderer::tPutPool::PushBackPool(Framework::CDirectAofTextRenderer::tString const&)(param_1 + (ulong)uVar1 * 4 + 0xfc,param_2);
  return;
}

// ==== Framework::CDirectAofTextRenderer::AddPutCounter(unsigned long, Framework::CDirectAofTextRenderer::tSizeCache&)
// vaddr 0x1e7900c | ghidra 0x1f7900c | size 708 | symbol _ZN9Framework22CDirectAofTextRenderer13AddPutCounterEmRNS0_10tSizeCacheE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CDirectAofTextRenderer13AddPutCounterEmRNS0_10tSizeCacheE
               (long *param_1,ulong param_2,ushort *param_3)

{
  byte *pbVar1;
  long lVar2;
  uint uVar3;
  byte *pbVar4;
  uint uVar5;
  ushort uVar6;
  bool bVar7;
  ulong uVar8;
  long lVar9;
  ulong uVar10;
  undefined8 *puVar11;
  uint uVar12;
  long lVar13;
  undefined8 *puVar14;
  long lVar15;
  ulong uVar16;
  ulong uVar17;
  ulong uVar18;
  long lVar19;
  undefined8 uVar20;
  
  uVar5 = *(uint *)(param_1 + 0x104);
  uVar3 = ~uVar5 & 1;
  uVar16 = (ulong)uVar5;
  if (1 < uVar5) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962e40/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Array.h"*/,0x25,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar16,2);
  }
  if (*(int *)(param_3 + 2) == 0) {
    param_3[2] = 1;
    param_3[3] = 0;
    DataMemoryBarrier(2,3);
    if ((int)param_1[0xfb] != 0) {
      (**(code **)(*param_1 + 0x2e0))(param_1);
    }
    uVar6 = *param_3;
    uVar18 = (ulong)uVar6;
    uVar17 = (ulong)uVar5;
    if (1 < uVar5) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962e40/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Array.h"*/,0x25,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar17,2);
    }
    uVar12 = *(uint *)(param_1 + uVar17 * 4 + 0xfd);
    uVar5 = *(int *)((long)param_1 + uVar17 * 0x20 + 0x7ec) + (uint)uVar6;
    if (uVar12 < uVar5) {
      if (uVar12 < 5) {
        uVar12 = 4;
      }
      do {
        bVar7 = uVar12 < uVar5;
        uVar12 = uVar12 << 1;
      } while (bVar7);
      Framework::CDirectAofTextRenderer::tPutPool::_ExpandCore(unsigned int)(param_1 + uVar17 * 4 + 0xfc);
    }
    if (1 < uVar3) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962e40/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Array.h"*/,0x25,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,(ulong)uVar3,2);
    }
    if (uVar6 != 0) {
      lVar13 = param_1[(ulong)uVar3 * 4 + 0xfc];
      lVar9 = param_1[uVar16 * 4 + 0xfc];
      uVar17 = param_2 >> 0x20 & 0xffff;
      if (lVar9 == lVar13) {
        lVar19 = uVar17 * 0x30;
        puVar11 = (undefined8 *)(lVar13 + lVar19 + 0x18);
        puVar14 = (undefined8 *)(lVar9 + lVar19 + 0x18);
        do {
          uVar18 = uVar18 - 1;
          puVar14[2] = puVar11[2];
          uVar20 = *puVar11;
          puVar14[1] = puVar11[1];
          *puVar14 = uVar20;
          puVar11 = puVar11 + 6;
          puVar14 = puVar14 + 6;
        } while (uVar18 != 0);
      }
      else {
        lVar15 = uVar17 * 0x30;
        lVar19 = 0;
        lVar13 = lVar13 + lVar15;
        lVar9 = lVar9 + lVar15;
        do {
          pbVar1 = (byte *)(lVar13 + lVar19);
          uVar17 = *(ulong *)(pbVar1 + 8);
          pbVar4 = *(byte **)(pbVar1 + 0x10);
          uVar10 = (ulong)*(byte *)(lVar9 + lVar19);
          if ((*pbVar1 & 1) == 0) {
            pbVar4 = pbVar1 + 1;
            uVar17 = (ulong)(*pbVar1 >> 1);
          }
          if ((*(byte *)(lVar9 + lVar19) & 1) == 0) {
            uVar8 = 0x16;
            lVar15 = uVar17 - 0x16;
            if (0x15 < uVar17 && lVar15 != 0) goto code_r0x01f791c4;
code_r0x01f7919c:
            if ((uVar10 & 1) == 0) {
              lVar15 = lVar9 + lVar19 + 1;
            }
            else {
              lVar15 = *(long *)(lVar9 + lVar19 + 0x10);
            }
            if (uVar17 != 0) {
              memmove(lVar15,pbVar4,uVar17);
            }
            *(undefined1 *)(lVar15 + uVar17) = 0;
            if ((*(byte *)(lVar9 + lVar19) & 1) == 0) {
              *(char *)(lVar9 + lVar19) = (char)(uVar17 << 1);
            }
            else {
              *(ulong *)(lVar9 + lVar19 + 8) = uVar17;
            }
          }
          else {
            uVar10 = *(ulong *)(lVar9 + lVar19);
            uVar8 = (uVar10 & 0xfffffffffffffffe) - 1;
            lVar15 = uVar17 - uVar8;
            if (uVar17 < uVar8 || lVar15 == 0) goto code_r0x01f7919c;
code_r0x01f791c4:
            if ((uVar10 & 1) == 0) {
              uVar10 = (ulong)(((uint)uVar10 & 0xfe) >> 1);
            }
            else {
              uVar10 = *(ulong *)(lVar9 + lVar19 + 8);
            }
            string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(lVar9 + lVar19,uVar8,lVar15,uVar10,0,uVar10,uVar17);
          }
          lVar15 = lVar13 + lVar19;
          lVar2 = lVar9 + lVar19;
          uVar18 = uVar18 - 1;
          lVar19 = lVar19 + 0x30;
          *(undefined8 *)(lVar2 + 0x28) = *(undefined8 *)(lVar15 + 0x28);
          uVar20 = *(undefined8 *)(lVar15 + 0x18);
          *(undefined8 *)(lVar2 + 0x20) = *(undefined8 *)(lVar15 + 0x20);
          *(undefined8 *)(lVar2 + 0x18) = uVar20;
        } while (uVar18 != 0);
      }
    }
    *(undefined4 *)((long)param_1 + uVar16 * 0x20 + 0x7f4) = 0;
  }
  *(uint *)((long)param_1 + uVar16 * 0x20 + 0x7ec) =
       *(int *)((long)param_1 + uVar16 * 0x20 + 0x7ec) + (uint)*param_3;
  *(uint *)(param_1 + uVar16 * 4 + 0xfe) = (int)param_1[uVar16 * 4 + 0xfe] + (uint)param_3[1];
  return;
}

// ==== Framework::CDirectAofTextRenderer::CalcStringRect(char const*, float, float) const
// vaddr 0x1e792d0 | ghidra 0x1f792d0 | size 168 | symbol _ZNK9Framework22CDirectAofTextRenderer14CalcStringRectEPKcff | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework22CDirectAofTextRenderer14CalcStringRectEPKcff
               (float *param_1,undefined4 param_2,undefined4 param_3,long param_4,undefined8 param_5
               )

{
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined *apuStack_90 [2];
  undefined8 uStack_80;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_38;
  
  memcpy((ulong)apuStack_90 | 8,param_4 + 0x6c8,0x33);
  apuStack_90[0] = PTR__ZTVN4Aska15TTextCompositorINS_4Utf8EEE_02cbd340 + 0x10;
  uStack_98 = 0;
  uStack_48 = *(undefined8 *)(param_4 + 0x708);
  uStack_50 = *(undefined8 *)(param_4 + 0x700);
  uStack_38 = 0;
  uStack_80 = 0;
  uStack_a0 = 0;
  uStack_6c = param_2;
  uStack_68 = param_2;
  uStack_64 = param_3;
  void Aska::TTextCompositor<Aska::Utf8>::ComposeString_<Aska::TTextCompositor<Aska::Utf8>::BinCharPrinter>(float*, float*, Aska::Vector*, unsigned long, char const*, Aska::TTextCompositor<Aska::Utf8>::BinCharPrinter) const(apuStack_90,(long)&uStack_38 + 4,&uStack_38,&uStack_a0,0xffffffffffffffff,param_5)
  ;
  *param_1 = (float)uStack_98 - (float)uStack_a0;
  param_1[1] = uStack_98._4_4_ - uStack_a0._4_4_;
  return;
}

// ==== Framework::CDirectAofTextRenderer::CharCount() const
// vaddr 0x1e79378 | ghidra 0x1f79378 | size 84 | symbol _ZNK9Framework22CDirectAofTextRenderer9CharCountEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework22CDirectAofTextRenderer9CharCountEv(long param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 0x820);
  if (1 < uVar1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962e40/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Array.h"*/,0x2c,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,(ulong)uVar1,2);
  }
  return *(undefined4 *)(param_1 + (ulong)uVar1 * 0x20 + 0x7f0);
}

// ==== Framework::CDirectAofTextRenderer::PutCounter() const
// vaddr 0x1e793cc | ghidra 0x1f793cc | size 84 | symbol _ZNK9Framework22CDirectAofTextRenderer10PutCounterEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework22CDirectAofTextRenderer10PutCounterEv(long param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 0x820);
  if (1 < uVar1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02962e40/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/STL_Array.h"*/,0x2c,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,(ulong)uVar1,2);
  }
  return *(undefined4 *)(param_1 + (ulong)uVar1 * 0x20 + 0x7ec);
}

// ==== Framework::CDirectAofTextRenderer::tPutPool::Terminate()
// vaddr 0x1e79420 | ghidra 0x1f79420 | size 100 | symbol _ZN9Framework22CDirectAofTextRenderer8tPutPool9TerminateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CDirectAofTextRenderer8tPutPool9TerminateEv(long *param_1)

{
  long lVar1;
  long lVar2;
  
  lVar2 = *param_1;
  if (lVar2 != 0) {
    lVar1 = *(long *)(lVar2 + -8);
    if (lVar1 != 0) {
      lVar1 = lVar1 * 0x30;
      do {
        if ((*(byte *)(lVar2 + lVar1 + -0x30) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar2 + lVar1 + -0x20));
        }
        lVar1 = lVar1 + -0x30;
      } while (lVar1 != 0);
    }
    operator delete[](void*)((long *)(lVar2 + -8));
    *param_1 = 0;
  }
  return;
}

// ==== Framework::CDirectAofTextRenderer::tPutPool::_ExpandCore(unsigned int)
// vaddr 0x1e79484 | ghidra 0x1f79484 | size 464 | symbol _ZN9Framework22CDirectAofTextRenderer8tPutPool11_ExpandCoreEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CDirectAofTextRenderer8tPutPool11_ExpandCoreEj(undefined8 *param_1,uint param_2)

{
  long lVar1;
  byte *pbVar2;
  byte *pbVar3;
  uint uVar4;
  ulong *puVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  ulong *puVar9;
  ulong uVar10;
  long lVar11;
  ulong uVar12;
  undefined8 uVar13;
  
  if (param_2 < 5) {
    param_2 = 4;
  }
  uVar10 = (ulong)param_2;
  uVar4 = *(uint *)(param_1 + 1);
  uVar12 = (ulong)uVar4;
  *(uint *)(param_1 + 1) = param_2;
  puVar5 = (ulong *)operator new[](unsigned long, std::nothrow_t const&)((uVar10 + (ulong)param_2 * 2) * 0x10 | 8,
                                    PTR__ZSt7nothrow_02cb9a80);
  puVar9 = puVar5;
  if (puVar5 != (ulong *)0x0) {
    puVar9 = puVar5 + 1;
    *puVar5 = uVar10;
    if (param_2 != 0) {
      lVar7 = uVar10 * 0x30;
      puVar5 = puVar9;
      do {
        puVar5[1] = 0;
        puVar5[2] = 0;
        *puVar5 = 0;
        lVar7 = lVar7 + -0x30;
        puVar5 = puVar5 + 6;
      } while (lVar7 != 0);
    }
  }
  puVar5 = (ulong *)*param_1;
  if (puVar5 != (ulong *)0x0) {
    if (uVar4 != 0) {
      lVar7 = 0;
      do {
        lVar1 = (long)puVar9 + lVar7;
        if (puVar9 != puVar5) {
          pbVar2 = (byte *)((long)puVar5 + lVar7);
          uVar10 = *(ulong *)(pbVar2 + 8);
          pbVar3 = *(byte **)(pbVar2 + 0x10);
          uVar8 = (ulong)*(byte *)((long)puVar9 + lVar7);
          if ((*pbVar2 & 1) == 0) {
            pbVar3 = pbVar2 + 1;
            uVar10 = (ulong)(*pbVar2 >> 1);
          }
          if ((*(byte *)((long)puVar9 + lVar7) & 1) == 0) {
            uVar6 = 0x16;
            lVar11 = uVar10 - 0x16;
            if (0x15 < uVar10 && lVar11 != 0) {
code_r0x01f79568:
              if ((uVar8 & 1) == 0) {
                uVar8 = (ulong)(((uint)uVar8 & 0xfe) >> 1);
              }
              else {
                uVar8 = *(ulong *)((long)puVar9 + lVar7 + 8);
              }
              string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(lVar1,uVar6,lVar11,uVar8,0,uVar8,uVar10);
              goto code_r0x01f795d4;
            }
          }
          else {
            uVar8 = *(ulong *)((long)puVar9 + lVar7);
            uVar6 = (uVar8 & 0xfffffffffffffffe) - 1;
            lVar11 = uVar10 - uVar6;
            if (uVar6 <= uVar10 && lVar11 != 0) goto code_r0x01f79568;
          }
          if ((uVar8 & 1) == 0) {
            lVar11 = (long)puVar9 + lVar7 + 1;
          }
          else {
            lVar11 = *(long *)((long)puVar9 + lVar7 + 0x10);
          }
          if (uVar10 != 0) {
            memmove(lVar11,pbVar3,uVar10);
          }
          *(undefined1 *)(lVar11 + uVar10) = 0;
          if ((*(byte *)((long)puVar9 + lVar7) & 1) == 0) {
            *(char *)((long)puVar9 + lVar7) = (char)(uVar10 << 1);
          }
          else {
            *(ulong *)((long)puVar9 + lVar7 + 8) = uVar10;
          }
        }
code_r0x01f795d4:
        uVar12 = uVar12 - 1;
        *(undefined8 *)(lVar1 + 0x28) = *(undefined8 *)((long)puVar5 + lVar7 + 0x28);
        uVar13 = *(undefined8 *)((long)puVar5 + lVar7 + 0x18);
        *(undefined8 *)(lVar1 + 0x20) = *(undefined8 *)((long)puVar5 + lVar7 + 0x20);
        *(undefined8 *)(lVar1 + 0x18) = uVar13;
        puVar5 = (ulong *)*param_1;
        lVar7 = lVar7 + 0x30;
      } while (uVar12 != 0);
      if (puVar5 == (ulong *)0x0) goto code_r0x01f79638;
    }
    uVar10 = puVar5[-1];
    if (uVar10 != 0) {
      lVar7 = uVar10 * 0x30;
      do {
        if ((*(byte *)((long)puVar5 + lVar7 + -0x30) & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)((long)puVar5 + lVar7 + -0x20));
        }
        lVar7 = lVar7 + -0x30;
      } while (lVar7 != 0);
    }
    operator delete[](void*)(puVar5 + -1);
    *param_1 = 0;
  }
code_r0x01f79638:
  *param_1 = puVar9;
  return;
}

// ==== Framework::CDirectAofTextRenderer::tPutPool::Expand(unsigned int)
// vaddr 0x1e79654 | ghidra 0x1f79654 | size 40 | symbol _ZN9Framework22CDirectAofTextRenderer8tPutPool6ExpandEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework22CDirectAofTextRenderer8tPutPool6ExpandEj(long param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(param_1 + 8);
  if (*(uint *)(param_1 + 8) < 5) {
    uVar1 = 4;
  }
  do {
    uVar2 = uVar1;
    uVar1 = uVar2 << 1;
  } while (uVar2 < param_2);
  (*(code *)PTR__ZN9Framework22CDirectAofTextRenderer8tPutPool11_ExpandCoreEj_02ca8830)
            (param_1,uVar2);
  return;
}

// ==== Aska::DirectAofHandler::Create(int, bool, char const*)
// vaddr 0x2106454 | ghidra 0x2206454 | size 516 | symbol _ZN4Aska16DirectAofHandler6CreateEibPKc | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska16DirectAofHandler6CreateEibPKc(long param_1,uint param_2,byte param_3,char *param_4)

{
  ulong uVar1;
  ulong uVar2;
  undefined1 auVar3 [16];
  char *pcVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  char *pcVar8;
  ulong uVar9;
  char *pcVar10;
  ulong uVar11;
  ulong uVar12;
  undefined8 *puVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  
  if (0xfe < param_2 - 1) {
    return 0;
  }
  if (*(long *)(param_1 + 0xb0) != 0) {
    return 0;
  }
  if (*(long *)(param_1 + 0xd0) != 0) {
    return 0;
  }
  *(undefined1 *)(param_1 + 0x352) = 0;
  *(byte *)(param_1 + 0x350) = *(byte *)(param_1 + 0x350) & 0xfe | param_3 & 1;
  lVar5 = operator new(unsigned long, std::nothrow_t const&)(0xd0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar5 == 0) {
    return 0;
  }
  memset(lVar5,0,0xd0);
  if (param_4 != (char *)0x0) {
    if (*param_4 == '\0') {
      uVar9 = 0;
    }
    else {
      uVar9 = 0;
      do {
        lVar6 = uVar9 + 1;
        uVar9 = uVar9 + 1;
      } while (param_4[lVar6] != '\0');
    }
    uVar1 = uVar9;
    if (0x1e < uVar9) {
      uVar1 = 0x1f;
    }
    if (uVar1 != 0) {
      uVar7 = uVar1 - 1;
      pcVar10 = (char *)(lVar5 + 0xb0);
      *pcVar10 = *param_4;
      if (uVar7 != 0) {
        pcVar8 = param_4 + 1;
        uVar12 = uVar7;
        if ((0x1f < uVar7) && (uVar11 = uVar7 & 0xffffffffffffffe0, uVar11 != 0)) {
          uVar2 = 0xffffffffffffffe0;
          if (0xffffffffffffffe0 < ~uVar9) {
            uVar2 = ~uVar9;
          }
          if ((param_4 + uVar1 <= (char *)(lVar5 + 0xb1U)) ||
             ((char *)(lVar5 + (0xaf - uVar2)) <= pcVar8)) {
            pcVar8 = pcVar8 + uVar11;
            uVar12 = uVar7 - uVar11;
            pcVar10 = pcVar10 + uVar11;
            puVar13 = (undefined8 *)(lVar5 + 0xc1);
            param_4 = param_4 + 0x11;
            uVar9 = uVar11;
            do {
              pcVar4 = param_4 + -8;
              uVar14 = *(undefined8 *)(param_4 + -0x10);
              uVar16 = *(undefined8 *)(param_4 + 8);
              uVar15 = *(undefined8 *)param_4;
              uVar9 = uVar9 - 0x20;
              param_4 = param_4 + 0x20;
              puVar13[-1] = *(undefined8 *)pcVar4;
              puVar13[-2] = uVar14;
              puVar13[1] = uVar16;
              *puVar13 = uVar15;
              puVar13 = puVar13 + 4;
            } while (uVar9 != 0);
            if (uVar7 == uVar11) goto code_r0x022065ac;
          }
        }
        do {
          pcVar10 = pcVar10 + 1;
          uVar12 = uVar12 - 1;
          *pcVar10 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (uVar12 != 0);
      }
    }
  }
code_r0x022065ac:
  *(undefined2 *)(lVar5 + 0x74) = 0;
  *(byte *)(param_1 + 0xa8) = *(byte *)(param_1 + 0xa8) & 0xf7;
  auVar3._8_8_ = 0;
  auVar3._0_8_ = (long)(int)param_2;
  uVar9 = -(ulong)(param_2 >> 0x1f) & 0xfffffff800000000 | (ulong)param_2 << 3;
  if (SUB168(auVar3 * ZEXT816(8),8) != 0) {
    uVar9 = 0xffffffffffffffff;
  }
  lVar6 = operator new[](unsigned long, std::nothrow_t const&)(uVar9,PTR__ZSt7nothrow_02cb9a80);
  *(long *)(param_1 + 0xd0) = lVar6;
  if (lVar6 != 0) {
    memset(lVar6,0,(long)(int)param_2 << 3);
    uVar16 = _UNK_029ca768;
    uVar15 = _UNK_029ca760;
    uVar14 = _UNK_029ca750;
    *(undefined8 *)(param_1 + 0x338) = _UNK_029ca758;
    *(undefined8 *)(param_1 + 0x330) = uVar14;
    *(undefined8 *)(param_1 + 0x348) = uVar16;
    *(undefined8 *)(param_1 + 0x340) = uVar15;
    uVar9 = Aska::MaterialList::Create(int)(param_1 + 0xe8,(ulong)param_2);
    if ((uVar9 & 1) != 0) {
      *(long *)(param_1 + 0xb0) = lVar5;
      *(char *)(param_1 + 0x352) = (char)param_2;
      return 1;
    }
    if (*(long *)(param_1 + 0xd0) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0xd0) = 0;
    }
  }
  operator delete(void*)(lVar5);
  return 0;
}

// ==== Aska::DirectAofHandler::OnOpen()
// vaddr 0x2106658 | ghidra 0x2206658 | size 4 | symbol _ZN4Aska16DirectAofHandler6OnOpenEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandler6OnOpenEv(void)

{
  return;
}

// ==== Aska::DirectAofHandler::Open()
// vaddr 0x210665c | ghidra 0x220665c | size 52 | symbol _ZN4Aska16DirectAofHandler4OpenEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16DirectAofHandler4OpenEv(long *param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  lVar4 = _UNK_029ca768;
  lVar3 = _UNK_029ca760;
  lVar2 = _UNK_029ca758;
  lVar1 = _UNK_029ca750;
  *(undefined1 *)((long)param_1 + 0x353) = 0;
  *(undefined4 *)(param_1 + 0x19) = 0;
  param_1[0x67] = lVar2;
  param_1[0x66] = lVar1;
  param_1[0x69] = lVar4;
  param_1[0x68] = lVar3;
  *(byte *)(param_1 + 0x15) = *(byte *)(param_1 + 0x15) & 0xfe;
                    /* WARNING: Could not recover jumptable at 0x0220668c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x70))();
  return;
}

// ==== Aska::DirectAofHandler::DirectAofHandler()
// vaddr 0x2106690 | ghidra 0x2206690 | size 116 | symbol _ZN4Aska16DirectAofHandlerC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandlerC2Ev(long *param_1)

{
  undefined *puVar1;
  
  Aska::AofHandler::AofHandler()();
  puVar1 = PTR__ZTVN4Aska16DirectAofHandlerE_02cbfc98;
  *param_1 = (long)(PTR__ZTVN4Aska16DirectAofHandlerE_02cbfc98 + 0x10);
  *(byte *)(param_1 + 0x6a) = *(byte *)(param_1 + 0x6a) & 0xe0 | 8;
  param_1[0x14] = (long)(puVar1 + 0xe0);
  param_1[0x13] = (long)(puVar1 + 0xb8);
  *(undefined4 *)((long)param_1 + 0x352) = 0;
  param_1[0x6e] = 0;
  param_1[0x6d] = 0;
  param_1[0x6c] = 0;
  param_1[0x6b] = 0;
  *(undefined1 *)((long)param_1 + 0x351) = 1;
  *(undefined4 *)(param_1 + 0x6f) = 1;
  *(undefined1 *)((long)param_1 + 0x94) = 1;
  return;
}

// ==== Aska::DirectAofHandler::UpdatePrim()
// vaddr 0x2106704 | ghidra 0x2206704 | size 16 | symbol _ZN4Aska16DirectAofHandler10UpdatePrimEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandler10UpdatePrimEv(long param_1)

{
  *(undefined1 *)(param_1 + 0x351) = 1;
  *(undefined4 *)(param_1 + 0x378) = 1;
  return;
}

// ==== Aska::DirectAofHandler::~DirectAofHandler()
// vaddr 0x2106714 | ghidra 0x2206714 | size 200 | symbol _ZN4Aska16DirectAofHandlerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandlerD1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  
  lVar3 = param_1[0x1a];
  puVar1 = PTR__ZTVN4Aska16DirectAofHandlerE_02cbfc98 + 0xb8;
  puVar2 = PTR__ZTVN4Aska16DirectAofHandlerE_02cbfc98 + 0xe0;
  *param_1 = (long)(PTR__ZTVN4Aska16DirectAofHandlerE_02cbfc98 + 0x10);
  param_1[0x14] = (long)puVar2;
  param_1[0x13] = (long)puVar1;
  if (lVar3 != 0) {
    uVar4 = (ulong)*(byte *)((long)param_1 + 0x352);
    if (*(byte *)((long)param_1 + 0x352) != 0) {
      lVar6 = 0;
      do {
        lVar5 = *(long *)(lVar3 + lVar6 * 8);
        if (lVar5 != 0) {
          Aska::PrimitiveBuffer::ReleaseBuffer()(lVar5 + 0x40);
          Aska::PrimitiveBuffer::~PrimitiveBuffer()(lVar5 + 0x40);
          operator delete(void*)(lVar5);
          lVar3 = param_1[0x1a];
          uVar4 = (ulong)*(byte *)((long)param_1 + 0x352);
        }
        lVar6 = lVar6 + 1;
      } while (lVar6 < (long)uVar4);
      if (lVar3 == 0) goto code_r0x022067a4;
    }
    operator delete[](void*)();
    param_1[0x1a] = 0;
  }
code_r0x022067a4:
  Aska::MaterialList::DeleteBuffer()(param_1 + 0x1d);
  *(byte *)(param_1 + 0x15) = *(byte *)(param_1 + 0x15) & 0xf8;
  if (param_1[0x16] != 0) {
    operator delete(void*)();
    param_1[0x16] = 0;
  }
  (*(code *)PTR__ZN4Aska10AofHandlerD2Ev_02cb0080)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::DirectAofHandler::~DirectAofHandler()
// vaddr 0x21067dc | ghidra 0x22067dc | size 8 | symbol _ZThn152_N4Aska16DirectAofHandlerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn152_N4Aska16DirectAofHandlerD1Ev(long param_1)

{
  (*(code *)PTR__ZN4Aska16DirectAofHandlerD1Ev_02c96548)(param_1 + -0x98);
  return;
}

// ==== non-virtual thunk to Aska::DirectAofHandler::~DirectAofHandler()
// vaddr 0x21067e4 | ghidra 0x22067e4 | size 8 | symbol _ZThn160_N4Aska16DirectAofHandlerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn160_N4Aska16DirectAofHandlerD1Ev(long param_1)

{
  (*(code *)PTR__ZN4Aska16DirectAofHandlerD1Ev_02c96548)(param_1 + -0xa0);
  return;
}

// ==== Aska::DirectAofHandler::~DirectAofHandler()
// vaddr 0x21067ec | ghidra 0x22067ec | size 24 | symbol _ZN4Aska16DirectAofHandlerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandlerD0Ev(undefined8 param_1)

{
  Aska::DirectAofHandler::~DirectAofHandler()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::DirectAofHandler::~DirectAofHandler()
// vaddr 0x2106804 | ghidra 0x2206804 | size 28 | symbol _ZThn152_N4Aska16DirectAofHandlerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn152_N4Aska16DirectAofHandlerD0Ev(long param_1)

{
  Aska::DirectAofHandler::~DirectAofHandler()(param_1 + -0x98);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1 + -0x98);
  return;
}

// ==== non-virtual thunk to Aska::DirectAofHandler::~DirectAofHandler()
// vaddr 0x2106820 | ghidra 0x2206820 | size 28 | symbol _ZThn160_N4Aska16DirectAofHandlerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn160_N4Aska16DirectAofHandlerD0Ev(long param_1)

{
  Aska::DirectAofHandler::~DirectAofHandler()(param_1 + -0xa0);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1 + -0xa0);
  return;
}

// ==== Aska::DirectAofHandler::OnClose(Aska::Vector const*, bool)
// vaddr 0x210683c | ghidra 0x220683c | size 4 | symbol _ZN4Aska16DirectAofHandler7OnCloseEPKNS_6VectorEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandler7OnCloseEPKNS_6VectorEb(void)

{
  return;
}

// ==== Aska::DirectAofHandler::Close(Aska::Vector const*, bool)
// vaddr 0x2106840 | ghidra 0x2206840 | size 796 | symbol _ZN4Aska16DirectAofHandler5CloseEPKNS_6VectorEb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16DirectAofHandler5CloseEPKNS_6VectorEb(long *param_1,undefined4 *param_2,uint param_3)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  int iVar7;
  byte bVar8;
  long lVar9;
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  float fVar13;
  undefined1 auVar16 [12];
  float fVar21;
  float fVar22;
  undefined1 auVar17 [16];
  undefined1 auVar15 [12];
  undefined1 auVar19 [16];
  undefined8 uVar23;
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  float fVar26;
  float fVar27;
  float fVar28;
  ulong uVar29;
  undefined8 uVar30;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  undefined1 auVar14 [12];
  undefined1 auVar18 [16];
  undefined1 auVar20 [16];
  
  if ((int)param_1[0x19] == 0) {
    bVar8 = *(byte *)(param_1 + 0x15) & 0xfe;
  }
  else {
    if (param_2 == (undefined4 *)0x0) {
      auVar10 = *(undefined1 (*) [16])(param_1 + 0x66);
      fVar26 = (auVar10._0_4_ + *(float *)(param_1 + 0x68)) * 0.5;
      fVar27 = (auVar10._4_4_ + *(float *)((long)param_1 + 0x344)) * 0.5;
      fVar28 = (auVar10._8_4_ + *(float *)(param_1 + 0x69)) * 0.5;
      fVar13 = auVar10._0_4_ - fVar26;
      fVar21 = auVar10._4_4_ - fVar27;
      fVar22 = auVar10._8_4_ - fVar28;
      auVar17._0_4_ = fVar13 * fVar13;
      auVar17._4_4_ = fVar21 * fVar21;
      auVar17._8_4_ = fVar22 * fVar22;
      auVar17._12_4_ = 0;
      auVar24 = NEON_ext(auVar17,auVar17,8,1);
      uVar23 = NEON_rev64(CONCAT44(auVar24._0_4_ + auVar24._4_4_,auVar17._0_4_ + auVar17._4_4_),4);
      fVar13 = auVar17._0_4_ + auVar17._4_4_ + (float)uVar23;
      if (*(float *)((long)param_1 + 0x33c) <= fVar13) {
        auVar17 = NEON_frsqrte(auVar10,4);
        auVar24._0_4_ = auVar17._0_4_ * auVar17._0_4_;
        auVar24._4_4_ = auVar17._4_4_ * auVar17._4_4_;
        auVar24._8_4_ = auVar17._8_4_ * auVar17._8_4_;
        auVar24._12_4_ = auVar17._12_4_ * auVar17._12_4_;
        lVar9 = 3;
        uVar23 = _UNK_027dbb30;
        uVar29 = _UNK_027dbb38;
      }
      else {
        auVar10._4_4_ = fVar13;
        auVar10._0_4_ = fVar13;
        auVar10._8_4_ = fVar13;
        auVar10._12_4_ = fVar13;
        auVar17 = NEON_frsqrte(auVar10,4);
        lVar9 = 0;
        auVar24._0_4_ = auVar17._0_4_ * auVar17._0_4_;
        auVar24._4_4_ = auVar17._4_4_ * auVar17._4_4_;
        auVar24._8_4_ = auVar17._8_4_ * auVar17._8_4_;
        auVar24._12_4_ = auVar17._12_4_ * auVar17._12_4_;
        uVar23 = CONCAT44(fVar27,fVar26);
        uVar29 = (ulong)(uint)fVar28;
      }
      auVar24 = NEON_frsqrts(auVar24,auVar10,4);
      fStack_40 = auVar10._0_4_ * auVar17._0_4_ * auVar24._0_4_;
      fStack_3c = auVar10._4_4_ * auVar17._4_4_ * auVar24._4_4_;
      fStack_38 = auVar10._8_4_ * auVar17._8_4_ * auVar24._8_4_;
      fStack_34 = auVar10._12_4_ * auVar17._12_4_ * auVar24._12_4_;
      uVar30 = CONCAT44(*(undefined4 *)((ulong)&fStack_40 | lVar9 << 2),(int)uVar29);
      iVar7 = __isnanf();
      auVar2._8_8_ = uVar30;
      auVar2._0_8_ = uVar23;
      auVar12._8_8_ = uVar30;
      auVar12._0_8_ = uVar23;
      auVar1._8_8_ = uVar30;
      auVar1._0_8_ = uVar23;
      iVar7 = -(uint)(iVar7 == 0);
      auVar11._0_4_ =
           CONCAT13(~(byte)((uint)iVar7 >> 0x18),
                    CONCAT12(~(byte)((uint)iVar7 >> 0x10),
                             CONCAT11(~(byte)((uint)iVar7 >> 8),~(byte)iVar7)));
      lVar9 = param_1[0x16];
      auVar25._0_12_ = auVar2._0_12_;
      auVar25._12_4_ = 0;
      auVar11._4_4_ = auVar11._0_4_;
      auVar11._8_4_ = auVar11._0_4_;
      auVar11._12_4_ = auVar11._0_4_;
      auVar12 = auVar12 ^ (auVar1 ^ auVar25) & auVar11;
      *(int *)(lVar9 + 0x10) = auVar12._0_4_;
      *(long *)(lVar9 + 0x14) = auVar12._4_8_;
      *(int *)(lVar9 + 0x1c) = auVar12._12_4_;
    }
    else {
      lVar9 = param_1[0x16];
      *(undefined4 *)(lVar9 + 0x10) = *param_2;
      *(undefined4 *)(lVar9 + 0x14) = param_2[1];
      *(undefined4 *)(lVar9 + 0x18) = param_2[2];
      *(undefined4 *)(lVar9 + 0x1c) = param_2[3];
    }
    if ((param_3 & 1) != 0) {
      auVar10 = *(undefined1 (*) [16])(param_1 + 0x66);
      lVar9 = param_1[0x16];
      fVar13 = (*(float *)(param_1 + 0x68) + auVar10._0_4_) * _UNK_029626a0;
      fVar21 = (*(float *)((long)param_1 + 0x344) + auVar10._4_4_) * _UNK_029626a4;
      auVar14._0_8_ = CONCAT44(fVar21,fVar13);
      auVar14._8_4_ = (*(float *)(param_1 + 0x69) + auVar10._8_4_) * _UNK_029626a8;
      auVar18._12_4_ = _UNK_029626ac * 1.0;
      auVar18._0_12_ = auVar14;
      *(float *)(lVar9 + 0x20) = fVar13;
      uVar23 = CONCAT44(auVar14._8_4_,fVar21);
      *(undefined4 *)(lVar9 + 0x2c) = 0x3f800000;
      *(undefined8 *)(lVar9 + 0x24) = uVar23;
      auVar15 = auVar14;
      if ((bRam0000000002dce270 & 1) == 0) {
        iVar7 = __cxa_guard_acquire(0x2dce270);
        auVar3._8_8_ = auVar18._8_8_;
        auVar3._0_8_ = auVar14._0_8_;
        auVar15 = auVar3._0_12_;
        if (iVar7 != 0) {
          uRam0000000002dce228 = UNK_027dbb00._8_8_;
          uRam0000000002dce220 = (undefined8)UNK_027dbb00;
          __cxa_guard_release(0x2dce270);
          auVar4._8_8_ = auVar18._8_8_;
          auVar4._0_8_ = auVar14._0_8_;
          auVar15 = auVar4._0_12_;
        }
      }
      auVar19._12_4_ = 0x3f800000;
      auVar19._0_12_ = auVar15;
      if ((bRam0000000002dce278 & 1) == 0) {
        uVar23 = auVar19._8_8_;
        iVar7 = __cxa_guard_acquire();
        auVar19._8_8_ = uVar23;
        auVar19._0_8_ = auVar15._0_8_;
        if (iVar7 != 0) {
          uRam0000000002dce238 = UNK_027dbb10._8_8_;
          uRam0000000002dce230 = (undefined8)UNK_027dbb10;
          __cxa_guard_release(0x2dce278);
        }
      }
      auVar16._0_8_ = CONCAT44(auVar10._4_4_ - auVar19._4_4_,auVar10._0_4_ - auVar19._0_4_);
      auVar16._8_4_ = auVar10._8_4_ - auVar19._8_4_;
      auVar20._12_4_ = auVar10._12_4_ - auVar19._12_4_;
      auVar20._0_12_ = auVar16;
      auVar15 = auVar16;
      if ((bRam0000000002dce280 & 1) == 0) {
        iVar7 = __cxa_guard_acquire();
        auVar5._8_8_ = auVar20._8_8_;
        auVar5._0_8_ = auVar16._0_8_;
        auVar15 = auVar5._0_12_;
        if (iVar7 != 0) {
          uRam0000000002dce248 = UNK_027dbb20._8_8_;
          uRam0000000002dce240 = (undefined8)UNK_027dbb20;
          __cxa_guard_release(0x2dce280);
          auVar6._8_8_ = auVar20._8_8_;
          auVar6._0_8_ = auVar16._0_8_;
          auVar15 = auVar6._0_12_;
        }
      }
      uVar23 = uRam0000000002dce220;
      lVar9 = param_1[0x16];
      *(undefined8 *)(lVar9 + 0x38) = uRam0000000002dce228;
      *(undefined8 *)(lVar9 + 0x30) = uVar23;
      uVar23 = uRam0000000002dce230;
      lVar9 = param_1[0x16];
      *(undefined8 *)(lVar9 + 0x48) = uRam0000000002dce238;
      *(undefined8 *)(lVar9 + 0x40) = uVar23;
      uVar23 = uRam0000000002dce240;
      lVar9 = param_1[0x16];
      *(undefined8 *)(lVar9 + 0x58) = uRam0000000002dce248;
      *(undefined8 *)(lVar9 + 0x50) = uVar23;
      lVar9 = param_1[0x16];
      *(int *)(lVar9 + 0x60) = auVar15._0_4_;
      *(long *)(lVar9 + 100) = auVar15._4_8_;
      *(undefined4 *)(lVar9 + 0x6c) = 0x3f800000;
      *(byte *)(param_1 + 0x15) = *(byte *)(param_1 + 0x15) | 8;
    }
    if (*(byte *)((long)param_1 + 0x353) != *(byte *)((long)param_1 + 0x352)) {
      return;
    }
    *(ushort *)(param_1[0x16] + 0x70) = (ushort)*(byte *)((long)param_1 + 0x353);
    Aska::MaterialList::SetActiveMaterialCount(unsigned char)(param_1 + 0x1d,*(undefined1 *)((long)param_1 + 0x353));
    bVar8 = *(byte *)(param_1 + 0x15) | 1;
  }
  *(byte *)(param_1 + 0x15) = bVar8;
                    /* WARNING: Could not recover jumptable at 0x02206b44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x78))(param_1,param_2,param_3 & 1);
  return;
}

// ==== Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)
// vaddr 0x2106b5c | ghidra 0x2206b5c | size 352 | symbol _ZN4Aska16DirectAofHandler9BeginMeshEPNS_14DirectMaterialEii | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska16DirectAofHandler9BeginMeshEPNS_14DirectMaterialEii
          (long param_1,long param_2,uint param_3,uint param_4)

{
  byte bVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  
  if (param_2 == 0) {
    return 0;
  }
  if ((int)param_3 < 1) {
    return 0;
  }
  if ((int)param_4 < 0) {
    return 0;
  }
  if (*(char *)(param_2 + 2) == '\x01') {
    Aska::RenderablePrimitive::PrepareIndexBufferForQuadList(int)((int)param_3 >> 2);
  }
  if ((int)param_3 < 0x10000) {
    if (0xffff < (int)param_4) {
      return 0;
    }
    bVar1 = *(byte *)(param_1 + 0x353);
    if ((uint)*(byte *)(param_1 + 0x352) <= (uint)bVar1) {
      *(undefined4 *)(param_1 + 200) = 0;
      return 0;
    }
    lVar4 = *(long *)(*(long *)(param_1 + 0xd0) + (ulong)(uint)bVar1 * 8);
    if (lVar4 == 0) {
      uVar3 = Aska::DirectAofHandler::AddMeshset(int, Aska::DirectMaterial const&, int, int)(param_1,bVar1,param_2,param_3,param_4);
      if ((uVar3 & 1) == 0) {
        return 0;
      }
    }
    else if ((*(uint *)(lVar4 + 0x174) < param_4) || (*(uint *)(lVar4 + 0x178) < param_3)) {
      if ((*(byte *)(param_1 + 0x350) >> 2 & 1) == 0) {
        return 0;
      }
      plVar2 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x10,PTR__ZSt7nothrow_02cb9a80);
      if (plVar2 == (long *)0x0) {
        return 0;
      }
      *plVar2 = (long)(PTR__ZTVN4Aska27DirectAofHandlerDelayDeleteE_02cc3318 + 0x10);
      plVar2[1] = lVar4;
      Aska::DeleteManager::AddMain(void*, unsigned char, unsigned char, Aska::IDeleteHandler*)(PTR__ZN4Aska6Global21m_systemDeleteManagerE_02cb77c0,plVar2,4,0,0);
      *(undefined8 *)(*(long *)(param_1 + 0xd0) + (ulong)bVar1 * 8) = 0;
      uVar3 = Aska::DirectAofHandler::AddMeshset(int, Aska::DirectMaterial const&, int, int)(param_1,bVar1,param_2,param_3,param_4);
      if ((uVar3 & 1) == 0) {
        return 0;
      }
    }
    Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*)(param_1,param_2);
    return 1;
  }
  return 0;
}

// ==== Aska::DirectAofHandler::AddMeshset(int, Aska::DirectMaterial const&, int, int)
// vaddr 0x2106cbc | ghidra 0x2206cbc | size 464 | symbol _ZN4Aska16DirectAofHandler10AddMeshsetEiRKNS_14DirectMaterialEii | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_ZN4Aska16DirectAofHandler10AddMeshsetEiRKNS_14DirectMaterialEii
          (long *param_1,int param_2,long param_3,undefined4 param_4,int param_5)

{
  undefined8 *puVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  undefined8 *puVar5;
  undefined8 uVar6;
  ulong uVar7;
  byte bVar8;
  undefined8 *puVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  
  *(undefined8 *)(param_1[0x1a] + (long)param_2 * 8) = 0;
  puVar5 = (undefined8 *)operator new(unsigned long, std::nothrow_t const&)(0x230,PTR__ZSt7nothrow_02cb9a80);
  if (puVar5 == (undefined8 *)0x0) {
    return 0;
  }
  puVar1 = puVar5 + 8;
  Aska::PrimitiveBuffer::PrimitiveBuffer()(puVar1);
  *(undefined4 *)(puVar5 + 0xd) = 0;
  *(undefined1 *)((long)puVar5 + 0x6c) = 0;
  puVar5[8] = PTR__ZTVN4Aska13MeshPrimitiveE_02cbcfd0 + 0x10;
  memset(puVar5 + 0x30,0,0xb0);
  puVar9 = (undefined8 *)((long)puVar5 + _UNK_029ca770);
  lVar10 = (long)puVar5 + _UNK_029ca778;
  lVar11 = (long)puVar5 + _UNK_029ca780;
  lVar12 = (long)puVar5 + _UNK_029ca788;
  puVar9[6] = 0;
  puVar9[7] = 0;
  puVar9[4] = 0;
  puVar9[5] = 0;
  puVar9[2] = 0;
  puVar9[3] = 0;
  *puVar9 = 0;
  puVar9[1] = 0;
  puVar5[1] = lVar10;
  *puVar5 = puVar9;
  puVar5[3] = lVar12;
  puVar5[2] = lVar11;
  puVar5[4] = 0;
  *(undefined1 *)(param_1[0x16] + 0x7c) = *(undefined1 *)(param_3 + 4);
  bVar2 = *(byte *)(param_1 + 0x6a);
  bVar8 = bVar2 & 7 | (*(byte *)(param_3 + 6) & 1) << 3;
  *(byte *)(param_1 + 0x6a) = bVar2 & 0xf0 | bVar8;
  *(byte *)(param_1 + 0x6a) = bVar2 & 0xe0 | bVar8 | (*(byte *)(param_3 + 6) >> 1 & 1) << 4;
  uVar3 = *(undefined1 *)(param_3 + 2);
  *(undefined1 *)((long)puVar5 + 0x91) = 0xff;
  *(undefined1 *)(puVar5 + 0x16) = uVar3;
  uVar6 = (**(code **)(*param_1 + 0x88))(param_1);
  *(undefined8 *)(puVar5[3] + 0x10) = uVar6;
  uVar4 = (**(code **)(*param_1 + 0x90))(param_1);
  *(undefined2 *)(puVar5[3] + 0x18) = uVar4;
  bVar8 = *(byte *)(param_1 + 0x6a);
  if (0 < param_5) {
    uVar7 = Aska::PrimitiveBuffer::CreateIndexBuffer(int, void const*, unsigned int, bool)(puVar1,param_5,0,4,bVar8 & 1);
    if ((uVar7 & 1) == 0) goto code_r0x02206e64;
    bVar8 = *(byte *)(param_1 + 0x6a) | 2;
    *(byte *)(param_1 + 0x6a) = bVar8;
  }
  uVar7 = Aska::PrimitiveBuffer::CreateVertexBuffer(int, unsigned long, int, void const*, unsigned int, bool)(puVar1,param_4,*(undefined8 *)(puVar5[3] + 0x10),
                          *(undefined2 *)(puVar5[3] + 0x18),0,1,bVar8 & 1);
  if ((uVar7 & 1) != 0) {
    *(int *)((long)puVar5 + 0x174) = param_5;
    *(undefined4 *)(puVar5 + 0x2f) = param_4;
    *(undefined8 **)(param_1[0x1a] + (long)param_2 * 8) = puVar5;
    (**(code **)(*param_1 + 0x80))(param_1,param_2);
    return 1;
  }
code_r0x02206e64:
  Aska::PrimitiveBuffer::~PrimitiveBuffer()(puVar1);
  operator delete(void*)(puVar5);
  return 0;
}

// ==== Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*)
// vaddr 0x2106e8c | ghidra 0x2206e8c | size 276 | symbol _ZN4Aska16DirectAofHandler9BeginMeshEPNS_14DirectMaterialE | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16DirectAofHandler9BeginMeshEPNS_14DirectMaterialE(long *param_1,long param_2)

{
  byte bVar1;
  int iVar2;
  undefined8 uVar3;
  long lVar4;
  undefined1 uVar5;
  long lVar6;
  
  bVar1 = *(byte *)((long)param_1 + 0x353);
  param_1[0x6e] = 0;
  lVar6 = *(long *)(param_1[0x1a] + (ulong)bVar1 * 8);
  param_1[0x6b] = lVar6;
  if (param_2 == 0) {
    if (lVar6 == 0) {
      return 1;
    }
  }
  else {
    uVar5 = 0;
    if (*(char *)(param_2 + 5) != '\0') {
      uVar5 = 2;
    }
    *(undefined1 *)(param_1 + 0x17) = uVar5;
    *(byte *)(param_1[0x16] + 0x93) = (byte)(*(ushort *)(param_2 + 0xf) >> 3) & 1;
    if (lVar6 == 0) {
      return 1;
    }
    if ((*(long *)(param_2 + 0xa0) != 0) ||
       (iVar2 = memcmp(lVar6 + 0x180,param_2,0xb0), iVar2 != 0)) {
      uVar3 = (**(code **)(*param_1 + 0x88))(param_1);
      Aska::MaterialList::SetDirectMaterial(int, Aska::DirectMaterial*, Aska::RenderablePrimitive*, unsigned long)(param_1 + 0x1d,(ulong)bVar1,param_2,lVar6 + 0x40,uVar3);
      memcpy(lVar6 + 0x180,param_2,0xb0);
    }
  }
  if ((*(byte *)(param_1 + 0x6a) >> 1 & 1) != 0) {
    lVar4 = Aska::PrimitiveBuffer::NativeIndexBuffer()(lVar6 + 0x40);
    param_1[0x6c] = lVar4;
  }
  lVar4 = Aska::PrimitiveBuffer::NativeVertexBuffer()(lVar6 + 0x40);
  param_1[0x6d] = lVar4;
  bVar1 = *(byte *)(*(long *)(lVar6 + 0x18) + 0x18);
  *(char *)((long)param_1 + 0x353) = *(char *)((long)param_1 + 0x353) + '\x01';
  *(ushort *)((long)param_1 + 0x354) = (ushort)bVar1;
  return 1;
}

// ==== Aska::DirectAofHandler::Sync(Aska::RenderablePrimitive*, unsigned int, unsigned int)
// vaddr 0x2106fa0 | ghidra 0x2206fa0 | size 16 | symbol _ZN4Aska16DirectAofHandler4SyncEPNS_19RenderablePrimitiveEjj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandler4SyncEPNS_19RenderablePrimitiveEjj
               (undefined8 param_1,undefined8 param_2,undefined4 param_3,undefined4 param_4)

{
  (*(code *)PTR__ZN4Aska15PrimitiveBuffer4SyncEjj_02cb5d28)(param_2,param_3,param_4);
  return;
}

// ==== Aska::DirectAofHandler::EndMesh()
// vaddr 0x2106fb0 | ghidra 0x2206fb0 | size 212 | symbol _ZN4Aska16DirectAofHandler7EndMeshEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandler7EndMeshEv(long param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  long lVar6;
  long lVar7;
  
  lVar6 = *(long *)(param_1 + 0x358);
  if (lVar6 != 0) {
    lVar7 = *(long *)(lVar6 + 8);
    Aska::PrimitiveBuffer::Sync(unsigned int, unsigned int)(lVar6 + 0x40,*(undefined4 *)(param_1 + 0x374),*(undefined4 *)(param_1 + 0x370));
    uVar2 = *(undefined4 *)(param_1 + 0x374);
    lVar6 = *(long *)(param_1 + 0x358);
    *(undefined4 *)(lVar7 + 0x10) = uVar2;
    *(undefined4 *)(lVar7 + 0x14) = *(undefined4 *)(param_1 + 0x370);
    *(undefined4 *)(lVar6 + 0x168) = uVar2;
    iVar4 = Aska::PrimitiveBuffer::Static::GetStripHeadCount(Aska::PrimType::Type)(*(undefined1 *)(lVar7 + 0x18));
    iVar5 = Aska::PrimitiveBuffer::Static::GetPrimUnitCount(Aska::PrimType::Type)(*(undefined1 *)(lVar7 + 0x18));
    piVar1 = (int *)(lVar7 + 0x14);
    if ((*(byte *)(param_1 + 0x350) & 2) == 0) {
      piVar1 = (int *)(lVar7 + 0x10);
    }
    iVar3 = 0;
    if (iVar5 != 0) {
      iVar3 = (*piVar1 - iVar4) / iVar5;
    }
    *(int *)(lVar6 + 0x16c) = iVar3;
    *(ushort *)(lVar6 + 0x170) = (ushort)*(byte *)(lVar7 + 0x18);
    *(undefined1 *)(param_1 + 0x351) = 1;
    *(undefined4 *)(param_1 + 0x378) = 1;
    *(int *)(param_1 + 200) = *(int *)(param_1 + 200) + *(int *)(lVar7 + 0x10);
    *(int *)(param_1 + 0xcc) = *(int *)(param_1 + 0xcc) + *(int *)(lVar7 + 0x14);
    *(undefined8 *)(param_1 + 0x360) = 0;
    *(undefined8 *)(param_1 + 0x368) = 0;
    *(undefined8 *)(param_1 + 0x358) = 0;
  }
  return;
}

// ==== Aska::DirectAofHandler::SetPrimCount(int, int, int)
// vaddr 0x2107084 | ghidra 0x2207084 | size 164 | symbol _ZN4Aska16DirectAofHandler12SetPrimCountEiii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandler12SetPrimCountEiii
               (long param_1,int param_2,uint param_3,uint param_4)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  
  lVar5 = *(long *)(*(long *)(param_1 + 0xd0) + (long)param_2 * 8);
  lVar6 = *(long *)(lVar5 + 8);
  Aska::PrimitiveBuffer::Sync(unsigned int, unsigned int)(lVar5 + 0x40,param_3,param_4);
  *(uint *)(lVar6 + 0x10) = param_3 & 0xffff;
  *(uint *)(lVar6 + 0x14) = param_4 & 0xffff;
  *(uint *)(lVar5 + 0x168) = param_3 & 0xffff;
  iVar3 = Aska::PrimitiveBuffer::Static::GetStripHeadCount(Aska::PrimType::Type)(*(undefined1 *)(lVar6 + 0x18));
  iVar4 = Aska::PrimitiveBuffer::Static::GetPrimUnitCount(Aska::PrimType::Type)(*(undefined1 *)(lVar6 + 0x18));
  puVar1 = (uint *)(lVar6 + 0x14);
  if ((*(byte *)(param_1 + 0x350) & 2) == 0) {
    puVar1 = (uint *)(lVar6 + 0x10);
  }
  iVar2 = 0;
  if (iVar4 != 0) {
    iVar2 = (int)(*puVar1 - iVar3) / iVar4;
  }
  *(int *)(lVar5 + 0x16c) = iVar2;
  *(ushort *)(lVar5 + 0x170) = (ushort)*(byte *)(lVar6 + 0x18);
  *(undefined1 *)(param_1 + 0x351) = 1;
  *(undefined4 *)(param_1 + 0x378) = 1;
  return;
}

// ==== Aska::DirectAofHandler::AddVertex(Aska::Vector const*, Aska::Vector const*, unsigned int)
// vaddr 0x2107128 | ghidra 0x2207128 | size 176 | symbol _ZN4Aska16DirectAofHandler9AddVertexEPKNS_6VectorES3_j | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandler9AddVertexEPKNS_6VectorES3_j
               (long param_1,undefined1 (*param_2) [16],undefined4 *param_3,uint param_4)

{
  ushort uVar1;
  undefined4 *puVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined8 uVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  
  if (*(long *)(param_1 + 0x358) != 0) {
    auVar6 = *param_2;
    auVar7 = NEON_fmax(auVar6,*(undefined1 (*) [16])(param_1 + 0x330),4);
    auVar4 = NEON_fmin(auVar6,*(undefined1 (*) [16])(param_1 + 0x340),4);
    auVar3._0_4_ = auVar6._0_4_ * auVar6._0_4_;
    auVar3._4_4_ = auVar6._4_4_ * auVar6._4_4_;
    auVar3._8_4_ = auVar6._8_4_ * auVar6._8_4_;
    auVar3._12_4_ = 0;
    auVar6 = NEON_ext(auVar3,auVar3,8,1);
    uVar5 = NEON_rev64(CONCAT44(auVar6._0_4_ + auVar6._4_4_,auVar3._0_4_ + auVar3._4_4_),4);
    auVar6._0_4_ = auVar3._0_4_ + auVar3._4_4_ + (float)uVar5;
    auVar6._4_4_ = auVar6._0_4_;
    auVar6._8_4_ = auVar6._0_4_;
    auVar6._12_4_ = auVar6._0_4_;
    auVar6 = NEON_fmax(auVar6,*(undefined1 (*) [16])(param_1 + 0x330),4);
    *(long *)(param_1 + 0x338) = auVar7._8_8_;
    *(long *)(param_1 + 0x330) = auVar7._0_8_;
    *(long *)(param_1 + 0x348) = auVar4._8_8_;
    *(long *)(param_1 + 0x340) = auVar4._0_8_;
    *(int *)(param_1 + 0x33c) = auVar6._12_4_;
    puVar2 = *(undefined4 **)(param_1 + 0x368);
    *puVar2 = *(undefined4 *)*param_2;
    puVar2[1] = *(undefined4 *)(*param_2 + 4);
    puVar2[2] = *(undefined4 *)(*param_2 + 8);
    puVar2[3] = *param_3;
    puVar2[4] = param_3[1];
    puVar2[5] = param_3[2];
    puVar2[6] = param_4 & 0xff000000 |
                param_4 & 0xff00 | param_4 >> 0x10 & 0xff | (param_4 & 0xff) << 0x10;
    uVar1 = *(ushort *)(*(long *)(*(long *)(param_1 + 0x358) + 0x18) + 0x18);
    *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
    *(ulong *)(param_1 + 0x368) = *(long *)(param_1 + 0x368) + (ulong)uVar1;
  }
  return;
}

// ==== Aska::DirectAofHandler::AddVertexT(Aska::Vector const*, Aska::Vector const*, Aska::Vector const*, float, float, unsigned int)
// vaddr 0x21071d8 | ghidra 0x22071d8 | size 204 | symbol _ZN4Aska16DirectAofHandler10AddVertexTEPKNS_6VectorES3_S3_ffj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandler10AddVertexTEPKNS_6VectorES3_S3_ffj
               (undefined4 param_1,undefined4 param_2,long param_3,undefined1 (*param_4) [16],
               undefined4 *param_5,undefined4 *param_6,uint param_7)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined8 uVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  
  if (*(long *)(param_3 + 0x358) != 0) {
    auVar6 = *param_4;
    auVar7 = NEON_fmax(auVar6,*(undefined1 (*) [16])(param_3 + 0x330),4);
    auVar4 = NEON_fmin(auVar6,*(undefined1 (*) [16])(param_3 + 0x340),4);
    auVar3._0_4_ = auVar6._0_4_ * auVar6._0_4_;
    auVar3._4_4_ = auVar6._4_4_ * auVar6._4_4_;
    auVar3._8_4_ = auVar6._8_4_ * auVar6._8_4_;
    auVar3._12_4_ = 0;
    auVar6 = NEON_ext(auVar3,auVar3,8,1);
    uVar5 = NEON_rev64(CONCAT44(auVar6._0_4_ + auVar6._4_4_,auVar3._0_4_ + auVar3._4_4_),4);
    auVar6._0_4_ = auVar3._0_4_ + auVar3._4_4_ + (float)uVar5;
    auVar6._4_4_ = auVar6._0_4_;
    auVar6._8_4_ = auVar6._0_4_;
    auVar6._12_4_ = auVar6._0_4_;
    auVar6 = NEON_fmax(auVar6,*(undefined1 (*) [16])(param_3 + 0x330),4);
    *(long *)(param_3 + 0x338) = auVar7._8_8_;
    *(long *)(param_3 + 0x330) = auVar7._0_8_;
    *(long *)(param_3 + 0x348) = auVar4._8_8_;
    *(long *)(param_3 + 0x340) = auVar4._0_8_;
    *(int *)(param_3 + 0x33c) = auVar6._12_4_;
    puVar2 = *(undefined4 **)(param_3 + 0x368);
    *puVar2 = *(undefined4 *)*param_4;
    puVar2[1] = *(undefined4 *)(*param_4 + 4);
    puVar2[2] = *(undefined4 *)(*param_4 + 8);
    puVar2[3] = *param_5;
    puVar2[4] = param_5[1];
    uVar1 = param_5[2];
    puVar2[7] = param_1;
    puVar2[8] = param_2;
    puVar2[5] = uVar1;
    puVar2[6] = param_7 & 0xff000000 |
                param_7 & 0xff00 | param_7 >> 0x10 & 0xff | (param_7 & 0xff) << 0x10;
    puVar2[9] = *param_6;
    puVar2[10] = param_6[1];
    puVar2[0xb] = param_6[2];
    puVar2[0xc] = param_6[3];
    *(ulong *)(param_3 + 0x368) = *(long *)(param_3 + 0x368) + (ulong)*(ushort *)(param_3 + 0x354);
    *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
  }
  return;
}

// ==== Aska::DirectAofHandler::GetIndexBuffer(int, int*)
// vaddr 0x21072a4 | ghidra 0x22072a4 | size 60 | symbol _ZN4Aska16DirectAofHandler14GetIndexBufferEiPi | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska16DirectAofHandler14GetIndexBufferEiPi(long param_1,int param_2,undefined4 *param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  if (param_2 < (int)(uint)*(byte *)(param_1 + 0x353)) {
    lVar2 = *(long *)(*(long *)(param_1 + 0xd0) + (long)param_2 * 8);
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = 2;
    }
    uVar1 = Aska::PrimitiveBuffer::NativeIndexBuffer()(lVar2 + 0x40);
    return uVar1;
  }
  return 0;
}

// ==== Aska::DirectAofHandler::GetVertexBuffer(int, int*)
// vaddr 0x21072e0 | ghidra 0x22072e0 | size 52 | symbol _ZN4Aska16DirectAofHandler15GetVertexBufferEiPi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska16DirectAofHandler15GetVertexBufferEiPi(long param_1,int param_2,uint *param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  if (param_2 < (int)(uint)*(byte *)(param_1 + 0x353)) {
    lVar2 = *(long *)(*(long *)(param_1 + 0xd0) + (long)param_2 * 8);
    if (param_3 != (uint *)0x0) {
      *param_3 = (uint)*(ushort *)(*(long *)(lVar2 + 0x18) + 0x18);
    }
    uVar1 = (*(code *)PTR__ZN4Aska15PrimitiveBuffer18NativeVertexBufferEv_02ca21e8)(lVar2 + 0x40);
    return uVar1;
  }
  return 0;
}

// ==== Aska::DirectAofHandler::FlipBuffer(int)
// vaddr 0x2107314 | ghidra 0x2207314 | size 40 | symbol _ZN4Aska16DirectAofHandler10FlipBufferEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandler10FlipBufferEi(long param_1,int param_2)

{
  if (((*(byte *)(param_1 + 0x350) & 1) != 0) && (param_2 < (int)(uint)*(byte *)(param_1 + 0x353)))
  {
    (*(code *)PTR__ZN4Aska15PrimitiveBuffer10FlipBufferEv_02cac178)
              (*(long *)(*(long *)(param_1 + 0xd0) + (long)param_2 * 8) + 0x40);
    return;
  }
  return;
}

// ==== Aska::DirectAofHandler::GetVertexAsmbit_() const
// vaddr 0x210733c | ghidra 0x220733c | size 12 | symbol _ZNK4Aska16DirectAofHandler16GetVertexAsmbit_Ev | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16DirectAofHandler16GetVertexAsmbit_Ev(void)

{
  return 0x10010161;
}

// ==== Aska::DirectAofHandler::GetVertexStride_() const
// vaddr 0x2107348 | ghidra 0x2207348 | size 8 | symbol _ZNK4Aska16DirectAofHandler16GetVertexStride_Ev | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska16DirectAofHandler16GetVertexStride_Ev(void)

{
  return 0x34;
}

// ==== Aska::DirectAofHandler::OnAddMeshset(int)
// vaddr 0x2107350 | ghidra 0x2207350 | size 4 | symbol _ZN4Aska16DirectAofHandler12OnAddMeshsetEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandler12OnAddMeshsetEi(void)

{
  return;
}

// ==== Aska::DirectAofHandler::Sphere(Aska::DirectMaterial*, float, int, int, unsigned int)
// vaddr 0x2107354 | ghidra 0x2207354 | size 1636 | symbol _ZN4Aska16DirectAofHandler6SphereEPNS_14DirectMaterialEfiij | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16DirectAofHandler6SphereEPNS_14DirectMaterialEfiij
               (float param_1,long *param_2,long param_3,int param_4,int param_5,uint param_6)

{
  int iVar1;
  char cVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined8 uVar8;
  short sVar9;
  short sVar10;
  short sVar11;
  short sVar12;
  float fVar13;
  ulong uVar14;
  byte bVar15;
  float *pfVar16;
  long lVar17;
  short *psVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  undefined1 auVar26 [16];
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  undefined1 auVar33 [16];
  undefined1 auVar34 [16];
  undefined1 auVar35 [16];
  float fVar36;
  float fVar37;
  float fVar38;
  undefined8 uStack_a0;
  undefined4 uStack_98;
  float fStack_94;
  
  cVar2 = *(char *)(param_3 + 2);
  iVar20 = param_5 * param_4;
  sVar12 = (short)param_4;
  if (cVar2 == '\x02') {
    uVar14 = Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)(param_2,param_3,iVar20,iVar20 * 8);
    fVar13 = _UNK_027e3fd0;
    if ((uVar14 & 1) == 0) goto code_r0x02207988;
    if (0 < param_5) {
      if (0 < param_4) {
        iVar20 = 0;
        do {
          iVar21 = 0;
          fVar30 = ((((float)iVar20 - (float)param_5 * 0.5) + 0.5) * fVar13) / (float)(param_5 + -1)
          ;
          do {
            fVar22 = (float)cosf(fVar30);
            fVar31 = (((float)iVar21 + (float)iVar21) * fVar13) / (float)param_4;
            fVar23 = (float)cosf(fVar31);
            fVar31 = (float)sinf(fVar31);
            fVar24 = (float)sinf(fVar30);
            if (param_2[0x6b] != 0) {
              fVar29 = fVar22 * fVar23 * param_1;
              fVar25 = fVar24 * param_1;
              auVar28 = *(undefined1 (*) [16])(param_2 + 0x66);
              fVar32 = fVar22 * fVar31 * param_1;
              auVar26._4_4_ = fVar25;
              auVar26._0_4_ = fVar29;
              auVar26._8_4_ = fVar32;
              auVar26._12_4_ = 0x3f800000;
              fVar36 = fVar29 * fVar29;
              fVar37 = fVar25 * fVar25;
              auVar33 = NEON_fmax(auVar26,auVar28,4);
              param_2[0x67] = auVar33._8_8_;
              param_2[0x66] = auVar33._0_8_;
              auVar6._4_4_ = fVar37;
              auVar6._0_4_ = fVar36;
              auVar6._8_4_ = fVar32 * fVar32;
              auVar6._12_4_ = 0;
              auVar7._4_4_ = fVar37;
              auVar7._0_4_ = fVar36;
              auVar7._8_4_ = fVar32 * fVar32;
              auVar7._12_4_ = 0;
              auVar33 = NEON_ext(auVar6,auVar7,8,1);
              uVar8 = NEON_rev64(CONCAT44(auVar33._0_4_ + auVar33._4_4_,fVar36 + fVar37),4);
              auVar34._0_4_ = fVar36 + fVar37 + (float)uVar8;
              auVar34._4_4_ = auVar34._0_4_;
              auVar34._8_4_ = auVar34._0_4_;
              auVar34._12_4_ = auVar34._0_4_;
              auVar28 = NEON_fmax(auVar34,auVar28,4);
              *(int *)((long)param_2 + 0x33c) = auVar28._12_4_;
              pfVar16 = (float *)param_2[0x6d];
              auVar28 = NEON_fmin(auVar26,*(undefined1 (*) [16])(param_2 + 0x68),4);
              param_2[0x69] = auVar28._8_8_;
              param_2[0x68] = auVar28._0_8_;
              *pfVar16 = fVar29;
              pfVar16[1] = fVar25;
              pfVar16[2] = fVar32;
              pfVar16[3] = fVar22 * fVar23;
              pfVar16[4] = fVar24;
              pfVar16[5] = fVar22 * fVar31;
              pfVar16[6] = (float)(param_6 >> 0x10 & 0xff | param_6 & 0xff00ff00 |
                                  (param_6 & 0xff) << 0x10);
              param_2[0x6d] =
                   param_2[0x6d] + (ulong)*(ushort *)(*(long *)(param_2[0x6b] + 0x18) + 0x18);
              *(int *)((long)param_2 + 0x374) = *(int *)((long)param_2 + 0x374) + 1;
            }
            iVar21 = iVar21 + 1;
          } while (param_4 != iVar21);
          iVar20 = iVar20 + 1;
        } while (iVar20 != param_5);
      }
      if ((1 < param_5) && (0 < param_4)) {
        iVar20 = 0;
        do {
          sVar9 = (short)iVar20 * sVar12;
          iVar20 = iVar20 + 1;
          iVar21 = 0;
          sVar10 = (short)iVar20 * sVar12;
          do {
            while (param_2[0x6b] == 0) {
              iVar21 = iVar21 + 1;
              if (param_4 <= iVar21) goto code_r0x02207650;
            }
            psVar18 = (short *)param_2[0x6c];
            sVar3 = (short)iVar21 + sVar9;
            param_2[0x6c] = (long)(psVar18 + 1);
            *psVar18 = sVar3;
            psVar18 = (short *)param_2[0x6c];
            sVar4 = (short)iVar21 + sVar10;
            iVar21 = iVar21 + 1;
            param_2[0x6c] = (long)(psVar18 + 1);
            *psVar18 = sVar4;
            *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 2;
            if (param_2[0x6b] != 0) {
              psVar18 = (short *)param_2[0x6c];
              sVar5 = 0;
              if (param_4 != 0) {
                sVar5 = (short)(iVar21 / param_4);
              }
              sVar11 = (short)iVar21 - sVar5 * sVar12;
              sVar5 = sVar11 + sVar9;
              param_2[0x6c] = (long)(psVar18 + 1);
              *psVar18 = sVar5;
              psVar18 = (short *)param_2[0x6c];
              param_2[0x6c] = (long)(psVar18 + 1);
              *psVar18 = sVar3;
              *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 2;
              if (param_2[0x6b] != 0) {
                psVar18 = (short *)param_2[0x6c];
                param_2[0x6c] = (long)(psVar18 + 1);
                *psVar18 = sVar4;
                psVar18 = (short *)param_2[0x6c];
                sVar11 = sVar11 + sVar10;
                param_2[0x6c] = (long)(psVar18 + 1);
                *psVar18 = sVar11;
                *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 2;
                if (param_2[0x6b] != 0) {
                  psVar18 = (short *)param_2[0x6c];
                  param_2[0x6c] = (long)(psVar18 + 1);
                  *psVar18 = sVar11;
                  psVar18 = (short *)param_2[0x6c];
                  param_2[0x6c] = (long)(psVar18 + 1);
                  *psVar18 = sVar5;
                  *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 2;
                }
              }
            }
          } while (iVar21 < param_4);
code_r0x02207650:
        } while (iVar20 != param_5 + -1);
      }
    }
  }
  else {
    *(undefined1 *)(param_3 + 2) = 0;
    uVar14 = Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)(param_2,param_3,iVar20,iVar20 * 6);
    fVar13 = _UNK_027e3fd0;
    if ((uVar14 & 1) == 0) goto code_r0x02207988;
    if (0 < param_5) {
      fVar30 = (float)(param_5 + -1);
      if (param_4 < 1) {
        iVar20 = 0;
        do {
          cosf(((((float)iVar20 - (float)param_5 * 0.5) + 0.5) * fVar13) / fVar30);
          iVar20 = iVar20 + 1;
        } while (param_5 != iVar20);
      }
      else {
        iVar20 = 0;
        do {
          fVar23 = ((((float)iVar20 - (float)param_5 * 0.5) + 0.5) * fVar13) / fVar30;
          fVar22 = (float)cosf(fVar23);
          iVar21 = 0;
          do {
            fVar24 = (((float)iVar21 + (float)iVar21) * fVar13) / (float)param_4;
            fVar31 = (float)cosf(fVar24);
            fVar24 = (float)sinf(fVar24);
            fVar25 = (float)sinf(fVar23);
            if (param_2[0x6b] != 0) {
              fVar32 = fVar22 * fVar31 * param_1;
              fVar29 = fVar25 * param_1;
              auVar6 = *(undefined1 (*) [16])(param_2 + 0x66);
              fVar36 = fVar22 * fVar24 * param_1;
              auVar27._4_4_ = fVar29;
              auVar27._0_4_ = fVar32;
              auVar27._8_4_ = fVar36;
              auVar27._12_4_ = 0x3f800000;
              fVar37 = fVar32 * fVar32;
              fVar38 = fVar29 * fVar29;
              auVar28 = NEON_fmax(auVar27,auVar6,4);
              param_2[0x67] = auVar28._8_8_;
              param_2[0x66] = auVar28._0_8_;
              auVar28._4_4_ = fVar38;
              auVar28._0_4_ = fVar37;
              auVar28._8_4_ = fVar36 * fVar36;
              auVar28._12_4_ = 0;
              auVar33._4_4_ = fVar38;
              auVar33._0_4_ = fVar37;
              auVar33._8_4_ = fVar36 * fVar36;
              auVar33._12_4_ = 0;
              auVar28 = NEON_ext(auVar28,auVar33,8,1);
              uVar8 = NEON_rev64(CONCAT44(auVar28._0_4_ + auVar28._4_4_,fVar37 + fVar38),4);
              auVar35._0_4_ = fVar37 + fVar38 + (float)uVar8;
              auVar35._4_4_ = auVar35._0_4_;
              auVar35._8_4_ = auVar35._0_4_;
              auVar35._12_4_ = auVar35._0_4_;
              auVar28 = NEON_fmax(auVar35,auVar6,4);
              *(int *)((long)param_2 + 0x33c) = auVar28._12_4_;
              pfVar16 = (float *)param_2[0x6d];
              auVar28 = NEON_fmin(auVar27,*(undefined1 (*) [16])(param_2 + 0x68),4);
              param_2[0x69] = auVar28._8_8_;
              param_2[0x68] = auVar28._0_8_;
              *pfVar16 = fVar32;
              pfVar16[1] = fVar29;
              pfVar16[2] = fVar36;
              pfVar16[3] = fVar22 * fVar31;
              pfVar16[4] = fVar25;
              pfVar16[5] = fVar22 * fVar24;
              pfVar16[6] = (float)(param_6 >> 0x10 & 0xff | param_6 & 0xff00ff00 |
                                  (param_6 & 0xff) << 0x10);
              param_2[0x6d] =
                   param_2[0x6d] + (ulong)*(ushort *)(*(long *)(param_2[0x6b] + 0x18) + 0x18);
              *(int *)((long)param_2 + 0x374) = *(int *)((long)param_2 + 0x374) + 1;
            }
            iVar21 = iVar21 + 1;
          } while (param_4 != iVar21);
          iVar20 = iVar20 + 1;
        } while (iVar20 != param_5);
      }
      if ((1 < param_5) && (0 < param_4)) {
        iVar21 = 0;
        iVar20 = 0;
        do {
          sVar9 = (short)iVar20;
          iVar20 = iVar20 + 1;
          iVar19 = 0;
          do {
            iVar1 = iVar19 + 1;
            sVar10 = 0;
            sVar3 = (short)iVar19;
            if (param_4 + -1 != iVar19) {
              sVar10 = sVar3 + 1;
            }
            if (param_2[0x6b] != 0) {
              psVar18 = (short *)param_2[0x6c];
              sVar4 = sVar12 + (short)iVar21 + sVar3;
              param_2[0x6c] = (long)(psVar18 + 1);
              *psVar18 = (short)iVar21 + sVar3;
              psVar18 = (short *)param_2[0x6c];
              sVar3 = sVar10 + sVar9 * sVar12;
              param_2[0x6c] = (long)(psVar18 + 1);
              *psVar18 = sVar3;
              psVar18 = (short *)param_2[0x6c];
              param_2[0x6c] = (long)(psVar18 + 1);
              *psVar18 = sVar4;
              *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 3;
              if (param_2[0x6b] != 0) {
                psVar18 = (short *)param_2[0x6c];
                param_2[0x6c] = (long)(psVar18 + 1);
                *psVar18 = sVar3;
                psVar18 = (short *)param_2[0x6c];
                param_2[0x6c] = (long)(psVar18 + 1);
                *psVar18 = sVar10 + (short)iVar20 * sVar12;
                psVar18 = (short *)param_2[0x6c];
                param_2[0x6c] = (long)(psVar18 + 1);
                *psVar18 = sVar4;
                *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 3;
              }
            }
            iVar19 = iVar1;
          } while (param_4 != iVar1);
          iVar21 = iVar21 + param_4;
        } while (iVar20 != param_5 + -1);
      }
    }
  }
  Aska::DirectAofHandler::EndMesh()(param_2);
  uStack_a0 = 0;
  uStack_98 = 0;
  fStack_94 = param_1;
  if ((int)param_2[0x19] == 0) {
    bVar15 = *(byte *)(param_2 + 0x15) & 0xfe;
  }
  else {
    lVar17 = param_2[0x16];
    *(undefined4 *)(lVar17 + 0x10) = 0;
    *(undefined8 *)(lVar17 + 0x14) = 0;
    *(float *)(lVar17 + 0x1c) = param_1;
    if (*(byte *)((long)param_2 + 0x353) != *(byte *)((long)param_2 + 0x352)) goto code_r0x02207988;
    *(ushort *)(param_2[0x16] + 0x70) = (ushort)*(byte *)((long)param_2 + 0x353);
    Aska::MaterialList::SetActiveMaterialCount(unsigned char)(param_2 + 0x1d,*(undefined1 *)((long)param_2 + 0x353));
    bVar15 = *(byte *)(param_2 + 0x15) | 1;
  }
  *(byte *)(param_2 + 0x15) = bVar15;
  (**(code **)(*param_2 + 0x78))(param_2,&uStack_a0,0);
code_r0x02207988:
  *(char *)(param_3 + 2) = cVar2;
  return;
}

// ==== Aska::DirectAofHandler::Circle(Aska::DirectMaterial*, float, int, unsigned int)
// vaddr 0x21079b8 | ghidra 0x22079b8 | size 1380 | symbol _ZN4Aska16DirectAofHandler6CircleEPNS_14DirectMaterialEfij | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16DirectAofHandler6CircleEPNS_14DirectMaterialEfij
               (float param_1,long *param_2,long param_3,int param_4,uint param_5)

{
  char cVar1;
  ushort uVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined8 uVar8;
  undefined4 uVar9;
  bool bVar10;
  int iVar11;
  ulong uVar12;
  byte bVar13;
  float *pfVar14;
  undefined2 *puVar15;
  long lVar16;
  short *psVar17;
  float fVar18;
  undefined8 uVar21;
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined8 uVar22;
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  undefined1 auVar26 [16];
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined1 auVar29 [16];
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  undefined8 uStack_80;
  undefined4 uStack_78;
  float fStack_74;
  
  cVar1 = *(char *)(param_3 + 2);
  iVar11 = param_4 + 2;
  if (cVar1 == '\x02') {
    uVar12 = Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)(param_2,param_3,iVar11,iVar11 * 2);
    if ((uVar12 & 1) == 0) goto code_r0x02207ef4;
    if (param_4 < 1) {
      if (param_2[0x6b] != 0) goto code_r0x02207e34;
    }
    else {
      iVar11 = 0;
      fVar33 = _UNK_027edb34 / (float)param_4;
      uVar21 = UNK_027dbb20._8_8_;
      uVar22 = (undefined8)UNK_027dbb20;
      do {
        fVar32 = fVar33 * (float)iVar11;
        fVar18 = (float)cosf(fVar32);
        fVar32 = (float)sinf(fVar32);
        if (param_2[0x6b] == 0) {
          lVar16 = 0;
        }
        else {
          fVar18 = fVar18 * param_1;
          fVar32 = fVar32 * param_1;
          auVar19 = *(undefined1 (*) [16])(param_2 + 0x66);
          auVar23._4_4_ = fVar32;
          auVar23._0_4_ = fVar18;
          auVar23._8_4_ = 0;
          auVar23._12_4_ = 0x3f800000;
          fVar30 = fVar18 * fVar18;
          fVar31 = fVar32 * fVar32;
          auVar26 = NEON_fmax(auVar23,auVar19,4);
          param_2[0x67] = auVar26._8_8_;
          param_2[0x66] = auVar26._0_8_;
          auVar6._4_4_ = fVar31;
          auVar6._0_4_ = fVar30;
          auVar6._8_8_ = 0;
          auVar7._4_4_ = fVar31;
          auVar7._0_4_ = fVar30;
          auVar7._8_8_ = 0;
          auVar26 = NEON_ext(auVar6,auVar7,8,1);
          uVar8 = NEON_rev64(CONCAT44(auVar26._0_4_ + auVar26._4_4_,fVar30 + fVar31),4);
          auVar27._0_4_ = fVar30 + fVar31 + (float)uVar8;
          auVar27._4_4_ = auVar27._0_4_;
          auVar27._8_4_ = auVar27._0_4_;
          auVar27._12_4_ = auVar27._0_4_;
          auVar19 = NEON_fmax(auVar27,auVar19,4);
          *(int *)((long)param_2 + 0x33c) = auVar19._12_4_;
          pfVar14 = (float *)param_2[0x6d];
          auVar3._12_4_ = (int)((ulong)param_2[0x69] >> 0x20);
          auVar3._0_12_ = *(undefined1 (*) [12])(param_2 + 0x68);
          auVar19 = NEON_fmin(auVar23,auVar3,4);
          param_2[0x69] = auVar19._8_8_;
          param_2[0x68] = auVar19._0_8_;
          *pfVar14 = fVar18;
          pfVar14[1] = fVar32;
          pfVar14[6] = (float)(param_5 >> 0x10 & 0xff | param_5 & 0xff00ff00 |
                              (param_5 & 0xff) << 0x10);
          *(undefined8 *)(pfVar14 + 4) = uVar21;
          *(undefined8 *)(pfVar14 + 2) = uVar22;
          lVar16 = param_2[0x6b];
          param_2[0x6d] = param_2[0x6d] + (ulong)*(ushort *)(*(long *)(lVar16 + 0x18) + 0x18);
          *(int *)((long)param_2 + 0x374) = *(int *)((long)param_2 + 0x374) + 1;
        }
        iVar11 = iVar11 + 1;
      } while (param_4 != iVar11);
      bVar10 = lVar16 == 0;
      if (1 < param_4) {
        iVar11 = 0;
        do {
          if (!bVar10) {
            psVar17 = (short *)param_2[0x6c];
            param_2[0x6c] = (long)(psVar17 + 1);
            *psVar17 = (short)iVar11;
            *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 1;
            if (param_2[0x6b] == 0) {
              lVar16 = 0;
            }
            else {
              psVar17 = (short *)param_2[0x6c];
              param_2[0x6c] = (long)(psVar17 + 1);
              *psVar17 = (short)iVar11 + 1;
              lVar16 = param_2[0x6b];
              *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 1;
            }
          }
          iVar11 = iVar11 + 1;
          bVar10 = lVar16 == 0;
        } while (iVar11 < param_4 + -1);
      }
      if (!bVar10) {
code_r0x02207e34:
        psVar17 = (short *)param_2[0x6c];
        param_2[0x6c] = (long)(psVar17 + 1);
        *psVar17 = (short)param_4 + -1;
        *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 1;
        if (param_2[0x6b] != 0) goto code_r0x02207e58;
      }
    }
  }
  else {
    *(undefined1 *)(param_3 + 2) = 4;
    uVar12 = Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)(param_2,param_3,iVar11,iVar11);
    if ((uVar12 & 1) == 0) goto code_r0x02207ef4;
    if (0 < param_4) {
      iVar11 = 0;
      fVar33 = _UNK_027edb34 / (float)param_4;
      uVar21 = UNK_027dbb20._8_8_;
      uVar22 = (undefined8)UNK_027dbb20;
      do {
        fVar32 = fVar33 * (float)iVar11;
        fVar18 = (float)cosf(fVar32);
        fVar32 = (float)sinf(fVar32);
        if (param_2[0x6b] != 0) {
          fVar18 = fVar18 * param_1;
          fVar32 = fVar32 * param_1;
          auVar19 = *(undefined1 (*) [16])(param_2 + 0x66);
          auVar24._4_4_ = fVar32;
          auVar24._0_4_ = fVar18;
          auVar24._8_4_ = 0;
          auVar24._12_4_ = 0x3f800000;
          fVar30 = fVar18 * fVar18;
          fVar31 = fVar32 * fVar32;
          auVar26 = NEON_fmax(auVar24,auVar19,4);
          param_2[0x67] = auVar26._8_8_;
          param_2[0x66] = auVar26._0_8_;
          auVar26._4_4_ = fVar31;
          auVar26._0_4_ = fVar30;
          auVar26._8_8_ = 0;
          auVar25._4_4_ = fVar31;
          auVar25._0_4_ = fVar30;
          auVar25._8_8_ = 0;
          auVar26 = NEON_ext(auVar26,auVar25,8,1);
          uVar8 = NEON_rev64(CONCAT44(auVar26._0_4_ + auVar26._4_4_,fVar30 + fVar31),4);
          auVar28._0_4_ = fVar30 + fVar31 + (float)uVar8;
          auVar28._4_4_ = auVar28._0_4_;
          auVar28._8_4_ = auVar28._0_4_;
          auVar28._12_4_ = auVar28._0_4_;
          auVar19 = NEON_fmax(auVar28,auVar19,4);
          *(int *)((long)param_2 + 0x33c) = auVar19._12_4_;
          pfVar14 = (float *)param_2[0x6d];
          auVar19._12_4_ = (int)((ulong)param_2[0x69] >> 0x20);
          auVar19._0_12_ = *(undefined1 (*) [12])(param_2 + 0x68);
          auVar19 = NEON_fmin(auVar24,auVar19,4);
          param_2[0x69] = auVar19._8_8_;
          param_2[0x68] = auVar19._0_8_;
          *pfVar14 = fVar18;
          pfVar14[1] = fVar32;
          pfVar14[6] = (float)(param_5 >> 0x10 & 0xff | param_5 & 0xff00ff00 |
                              (param_5 & 0xff) << 0x10);
          *(undefined8 *)(pfVar14 + 4) = uVar21;
          *(undefined8 *)(pfVar14 + 2) = uVar22;
          param_2[0x6d] = param_2[0x6d] + (ulong)*(ushort *)(*(long *)(param_2[0x6b] + 0x18) + 0x18)
          ;
          *(int *)((long)param_2 + 0x374) = *(int *)((long)param_2 + 0x374) + 1;
        }
        iVar11 = iVar11 + 1;
      } while (param_4 != iVar11);
    }
    if (((bRam0000000002dce260 & 1) == 0) && (iVar11 = __cxa_guard_acquire(0x2dce260), iVar11 != 0)) {
      fRam0000000002dce258 = UNK_027dbb30._8_4_;
      uRam0000000002dce25c = UNK_027dbb30._12_4_;
      fRam0000000002dce250 = (float)UNK_027dbb30;
      fRam0000000002dce254 = UNK_027dbb30._4_4_;
      __cxa_guard_release(0x2dce260);
    }
    uVar9 = uRam0000000002dce25c;
    fVar33 = fRam0000000002dce250;
    lVar16 = 0;
    if (param_2[0x6b] != 0) {
      auVar5._4_4_ = fRam0000000002dce254;
      auVar5._0_4_ = fRam0000000002dce250;
      auVar5._8_4_ = fRam0000000002dce258;
      auVar4._4_4_ = fRam0000000002dce254;
      auVar4._0_4_ = fRam0000000002dce250;
      auVar4._8_4_ = fRam0000000002dce258;
      auVar19 = *(undefined1 (*) [16])(param_2 + 0x66);
      auVar29._0_4_ = fRam0000000002dce250 * fRam0000000002dce250;
      auVar29._4_4_ = fRam0000000002dce254 * fRam0000000002dce254;
      auVar29._8_4_ = fRam0000000002dce258 * fRam0000000002dce258;
      auVar29._12_4_ = 0;
      auVar26 = NEON_ext(auVar29,auVar29,8,1);
      auVar4._12_4_ = uRam0000000002dce25c;
      auVar25 = NEON_fmax(auVar4,auVar19,4);
      param_2[0x67] = auVar25._8_8_;
      param_2[0x66] = auVar25._0_8_;
      uVar22 = NEON_rev64(CONCAT44(auVar26._0_4_ + auVar26._4_4_,auVar29._0_4_ + auVar29._4_4_),4);
      auVar20._0_4_ = auVar29._0_4_ + auVar29._4_4_ + (float)uVar22;
      auVar20._4_4_ = auVar20._0_4_;
      auVar20._8_4_ = auVar20._0_4_;
      auVar20._12_4_ = auVar20._0_4_;
      auVar19 = NEON_fmax(auVar20,auVar19,4);
      *(int *)((long)param_2 + 0x33c) = auVar19._12_4_;
      pfVar14 = (float *)param_2[0x6d];
      auVar5._12_4_ = uVar9;
      auVar19 = NEON_fmin(auVar5,*(undefined1 (*) [16])(param_2 + 0x68),4);
      param_2[0x69] = auVar19._8_8_;
      param_2[0x68] = auVar19._0_8_;
      *pfVar14 = fVar33;
      pfVar14[1] = fRam0000000002dce254;
      fVar33 = fRam0000000002dce258;
      pfVar14[3] = 0.0;
      pfVar14[4] = 1.0;
      pfVar14[5] = 0.0;
      pfVar14[6] = (float)(param_5 >> 0x10 & 0xff | param_5 & 0xff00ff00 | (param_5 & 0xff) << 0x10)
      ;
      pfVar14[2] = fVar33;
      uVar2 = *(ushort *)(*(long *)(param_2[0x6b] + 0x18) + 0x18);
      *(int *)((long)param_2 + 0x374) = *(int *)((long)param_2 + 0x374) + 1;
      param_2[0x6d] = param_2[0x6d] + (ulong)uVar2;
      lVar16 = 0;
      if (param_2[0x6b] != 0) {
        psVar17 = (short *)param_2[0x6c];
        param_2[0x6c] = (long)(psVar17 + 1);
        *psVar17 = (short)param_4;
        lVar16 = param_2[0x6b];
        *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 1;
      }
    }
    bVar10 = lVar16 == 0;
    if (0 < param_4) {
      iVar11 = 0;
      do {
        if (!bVar10) {
          puVar15 = (undefined2 *)param_2[0x6c];
          param_2[0x6c] = (long)(puVar15 + 1);
          *puVar15 = (short)iVar11;
          lVar16 = param_2[0x6b];
          *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 1;
        }
        iVar11 = iVar11 + 1;
        bVar10 = lVar16 == 0;
      } while (param_4 != iVar11);
    }
    if (bVar10) goto code_r0x02207e74;
code_r0x02207e58:
    puVar15 = (undefined2 *)param_2[0x6c];
    param_2[0x6c] = (long)(puVar15 + 1);
    *puVar15 = 0;
    *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 1;
  }
code_r0x02207e74:
  Aska::DirectAofHandler::EndMesh()(param_2);
  uStack_80 = 0;
  uStack_78 = 0;
  fStack_74 = param_1;
  if ((int)param_2[0x19] == 0) {
    bVar13 = *(byte *)(param_2 + 0x15) & 0xfe;
  }
  else {
    lVar16 = param_2[0x16];
    *(undefined4 *)(lVar16 + 0x10) = 0;
    *(undefined8 *)(lVar16 + 0x14) = 0;
    *(float *)(lVar16 + 0x1c) = param_1;
    if (*(byte *)((long)param_2 + 0x353) != *(byte *)((long)param_2 + 0x352)) goto code_r0x02207ef4;
    *(ushort *)(param_2[0x16] + 0x70) = (ushort)*(byte *)((long)param_2 + 0x353);
    Aska::MaterialList::SetActiveMaterialCount(unsigned char)(param_2 + 0x1d,*(undefined1 *)((long)param_2 + 0x353));
    bVar13 = *(byte *)(param_2 + 0x15) | 1;
  }
  *(byte *)(param_2 + 0x15) = bVar13;
  (**(code **)(*param_2 + 0x78))(param_2,&uStack_80,0);
code_r0x02207ef4:
  *(char *)(param_3 + 2) = cVar1;
  return;
}

// ==== Aska::DirectAofHandler::Box(Aska::DirectMaterial*, Aska::Vector const*, int, int, int, unsigned int*, Aska::Vector const*)
// vaddr 0x2107f1c | ghidra 0x2207f1c | size 2864 | symbol _ZN4Aska16DirectAofHandler3BoxEPNS_14DirectMaterialEPKNS_6VectorEiiiPjS5_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16DirectAofHandler3BoxEPNS_14DirectMaterialEPKNS_6VectorEiiiPjS5_
               (long param_1,long param_2,float *param_3,int param_4,int param_5,int param_6,
               long param_7,undefined8 *param_8)

{
  uint uVar1;
  char cVar2;
  ushort uVar3;
  int iVar4;
  short sVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  int iVar22;
  ulong uVar23;
  long lVar24;
  int iVar25;
  long lVar26;
  char cVar27;
  int iVar28;
  long lVar29;
  short *psVar30;
  long lVar31;
  long lVar32;
  long lVar33;
  float *pfVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  undefined1 auVar42 [16];
  undefined1 auVar43 [16];
  float fVar44;
  float fVar45;
  undefined1 auVar46 [16];
  undefined1 auVar47 [16];
  float fVar48;
  undefined1 auVar49 [16];
  undefined1 auVar50 [16];
  undefined1 auVar51 [16];
  undefined1 auVar52 [16];
  undefined1 auVar53 [16];
  undefined1 auVar54 [16];
  undefined1 auVar55 [16];
  float fVar56;
  undefined8 uVar57;
  undefined1 auVar58 [16];
  undefined1 auVar59 [16];
  undefined1 auVar60 [16];
  undefined1 auVar61 [16];
  undefined1 auVar62 [16];
  undefined8 uStack_e0;
  undefined4 uStack_d8;
  float fStack_d4;
  int aiStack_d0 [10];
  int aiStack_a8 [4];
  int iStack_98;
  int iStack_94;
  undefined8 uStack_90;
  undefined8 uStack_88;
  float afStack_80 [5];
  float fStack_6c;
  float fStack_68;
  undefined4 uStack_64;
  
  cVar2 = *(char *)(param_2 + 2);
  cVar27 = cVar2;
  if (cVar2 != '\x02') {
    cVar27 = '\0';
    *(undefined1 *)(param_2 + 2) = 0;
  }
  iVar28 = param_6 * param_4 + (param_6 + param_4) * param_5;
  iVar4 = iVar28 * 8;
  uStack_64 = 0x3f800000;
  afStack_80[3] = 1.0;
  if (param_8 == (undefined8 *)0x0) {
    param_8 = &uStack_90;
    uStack_88 = _UNK_027dbb38;
    uStack_90 = _UNK_027dbb30;
  }
  aiStack_d0[0] = 0;
  aiStack_d0[5] = 0;
  aiStack_d0[3] = (int)_UNK_029ca798;
  aiStack_d0[4] = (int)((ulong)_UNK_029ca798 >> 0x20);
  aiStack_d0[1] = (int)_UNK_029ca790;
  aiStack_d0[2] = (int)((ulong)_UNK_029ca790 >> 0x20);
  aiStack_d0[6] = 2;
  aiStack_d0[7] = 0;
  aiStack_d0[8] = 1;
  if (cVar27 == '\x02') {
    iVar22 = iVar28 * 0x10;
  }
  else {
    iVar22 = iVar28 * 0xc;
  }
  aiStack_a8[0] = param_4;
  aiStack_a8[1] = param_5;
  aiStack_a8[2] = param_5;
  aiStack_a8[3] = param_6;
  iStack_98 = param_6;
  iStack_94 = param_4;
  uVar23 = Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)(param_1,param_2,iVar4,iVar22);
  if ((uVar23 & 1) != 0) {
    lVar29 = 0;
    iVar22 = 1;
    iVar25 = 2;
    do {
      lVar31 = (long)aiStack_d0[lVar29 * 3];
      uVar1 = *(uint *)(param_7 + lVar29 * 4);
      lVar32 = (long)iVar25;
      afStack_80[lVar31] = 0.0;
      afStack_80[iVar22] = 0.0;
      afStack_80[iVar25] = -1.0;
      if (param_4 < 1) {
        afStack_80[lVar32] = 1.0;
      }
      else {
        iVar25 = 0;
        lVar24 = (long)iVar22;
        fVar35 = (float)param_4;
        fVar37 = (float)param_5;
        fVar36 = (float)(uVar1 & 0xff000000 |
                        uVar1 & 0xff00 | uVar1 >> 0x10 & 0xff | (uVar1 & 0xff) << 0x10);
        do {
          while (0 < param_5) {
            lVar33 = *(long *)(param_1 + 0x358);
            fVar38 = (float)iVar25;
            iVar25 = iVar25 + 1;
            iVar22 = 0;
            do {
              fVar40 = param_3[lVar31];
              fVar44 = param_3[lVar24];
              fVar39 = *(float *)((long)param_8 + lVar31 * 4) - fVar40;
              fVar56 = *(float *)((long)param_8 + lVar24 * 4) - fVar44;
              fVar41 = fVar39 + (fVar38 / fVar35) * (fVar40 + fVar40);
              fVar39 = fVar39 + ((float)iVar25 / fVar35) * (fVar40 + fVar40);
              fVar40 = fVar56 + ((float)iVar22 / fVar37) * (fVar44 + fVar44);
              afStack_80[lVar31 + 4] = fVar41;
              lVar26 = lVar32 * 4;
              afStack_80[lVar24 + 4] = fVar40;
              iVar22 = iVar22 + 1;
              fVar45 = param_3[lVar32];
              fVar48 = *(float *)((long)param_8 + lVar26);
              fVar56 = fVar56 + ((float)iVar22 / fVar37) * (fVar44 + fVar44);
              afStack_80[lVar32 + 4] = fVar48 - fVar45;
              if (lVar33 == 0) {
                afStack_80[lVar31 + 4] = fVar39;
                afStack_80[lVar24 + 4] = fVar40;
                afStack_80[lVar32 + 4] = fVar48 - fVar45;
code_r0x022083ac:
                afStack_80[lVar31 + 4] = fVar41;
                afStack_80[lVar24 + 4] = fVar56;
                afStack_80[lVar32 + 4] = fVar48 - fVar45;
code_r0x022083bc:
                afStack_80[lVar31 + 4] = fVar39;
                lVar33 = 0;
                afStack_80[lVar24 + 4] = fVar56;
                afStack_80[lVar32 + 4] = fVar48 - fVar45;
              }
              else {
                auVar19._4_4_ = fStack_6c;
                auVar19._0_4_ = afStack_80[4];
                auVar19._8_4_ = fStack_68;
                auVar19._12_4_ = uStack_64;
                auVar18 = *(undefined1 (*) [16])(param_1 + 0x330);
                fVar44 = afStack_80[4] * afStack_80[4];
                fVar45 = fStack_6c * fStack_6c;
                auVar58 = NEON_fmax(auVar19,auVar18,4);
                *(long *)(param_1 + 0x338) = auVar58._8_8_;
                *(long *)(param_1 + 0x330) = auVar58._0_8_;
                auVar58._4_4_ = fVar45;
                auVar58._0_4_ = fVar44;
                auVar58._8_4_ = fStack_68 * fStack_68;
                auVar58._12_4_ = 0;
                auVar51._4_4_ = fVar45;
                auVar51._0_4_ = fVar44;
                auVar51._8_4_ = fStack_68 * fStack_68;
                auVar51._12_4_ = 0;
                auVar58 = NEON_ext(auVar58,auVar51,8,1);
                uVar57 = NEON_rev64(CONCAT44(auVar58._0_4_ + auVar58._4_4_,fVar44 + fVar45),4);
                auVar59._0_4_ = fVar44 + fVar45 + (float)uVar57;
                auVar59._4_4_ = auVar59._0_4_;
                auVar59._8_4_ = auVar59._0_4_;
                auVar59._12_4_ = auVar59._0_4_;
                auVar58 = NEON_fmax(auVar59,auVar18,4);
                *(undefined4 *)(param_1 + 0x33c) = auVar58._12_4_;
                pfVar34 = *(float **)(param_1 + 0x368);
                auVar58 = NEON_fmin(auVar19,*(undefined1 (*) [16])(param_1 + 0x340),4);
                *(long *)(param_1 + 0x348) = auVar58._8_8_;
                *(long *)(param_1 + 0x340) = auVar58._0_8_;
                *pfVar34 = afStack_80[4];
                pfVar34[1] = fStack_6c;
                pfVar34[4] = afStack_80[1];
                pfVar34[5] = afStack_80[2];
                pfVar34[6] = fVar36;
                pfVar34[2] = fStack_68;
                pfVar34[3] = afStack_80[0];
                lVar33 = *(long *)(param_1 + 0x358);
                uVar3 = *(ushort *)(*(long *)(lVar33 + 0x18) + 0x18);
                *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
                *(ulong *)(param_1 + 0x368) = *(long *)(param_1 + 0x368) + (ulong)uVar3;
                fVar45 = param_3[lVar32];
                fVar48 = *(float *)((long)param_8 + lVar26);
                afStack_80[lVar31 + 4] = fVar39;
                afStack_80[lVar24 + 4] = fVar40;
                afStack_80[lVar32 + 4] = fVar48 - fVar45;
                if (lVar33 == 0) goto code_r0x022083ac;
                auVar18._4_4_ = fStack_6c;
                auVar18._0_4_ = afStack_80[4];
                auVar18._8_4_ = fStack_68;
                auVar18._12_4_ = uStack_64;
                auVar58 = *(undefined1 (*) [16])(param_1 + 0x330);
                auVar60._0_4_ = afStack_80[4] * afStack_80[4];
                auVar60._4_4_ = fStack_6c * fStack_6c;
                auVar60._8_4_ = fStack_68 * fStack_68;
                auVar51 = NEON_fmax(auVar18,auVar58,4);
                auVar60._12_4_ = 0;
                *(long *)(param_1 + 0x338) = auVar51._8_8_;
                *(long *)(param_1 + 0x330) = auVar51._0_8_;
                auVar51 = NEON_ext(auVar60,auVar60,8,1);
                uVar57 = NEON_rev64(CONCAT44(auVar51._0_4_ + auVar51._4_4_,
                                             auVar60._0_4_ + auVar60._4_4_),4);
                auVar52._0_4_ = auVar60._0_4_ + auVar60._4_4_ + (float)uVar57;
                auVar52._4_4_ = auVar52._0_4_;
                auVar52._8_4_ = auVar52._0_4_;
                auVar52._12_4_ = auVar52._0_4_;
                auVar58 = NEON_fmax(auVar52,auVar58,4);
                *(undefined4 *)(param_1 + 0x33c) = auVar58._12_4_;
                pfVar34 = *(float **)(param_1 + 0x368);
                auVar58 = NEON_fmin(auVar18,*(undefined1 (*) [16])(param_1 + 0x340),4);
                *(long *)(param_1 + 0x348) = auVar58._8_8_;
                *(long *)(param_1 + 0x340) = auVar58._0_8_;
                *pfVar34 = afStack_80[4];
                pfVar34[1] = fStack_6c;
                pfVar34[4] = afStack_80[1];
                pfVar34[5] = afStack_80[2];
                pfVar34[6] = fVar36;
                pfVar34[2] = fStack_68;
                pfVar34[3] = afStack_80[0];
                lVar33 = *(long *)(param_1 + 0x358);
                uVar3 = *(ushort *)(*(long *)(lVar33 + 0x18) + 0x18);
                *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
                *(ulong *)(param_1 + 0x368) = *(long *)(param_1 + 0x368) + (ulong)uVar3;
                fVar45 = param_3[lVar32];
                fVar48 = *(float *)((long)param_8 + lVar26);
                afStack_80[lVar31 + 4] = fVar41;
                afStack_80[lVar24 + 4] = fVar56;
                afStack_80[lVar32 + 4] = fVar48 - fVar45;
                if (lVar33 == 0) goto code_r0x022083bc;
                auVar11._4_4_ = fStack_6c;
                auVar11._0_4_ = afStack_80[4];
                auVar11._8_4_ = fStack_68;
                auVar10._4_4_ = fStack_6c;
                auVar10._0_4_ = afStack_80[4];
                auVar10._8_4_ = fStack_68;
                auVar58 = *(undefined1 (*) [16])(param_1 + 0x330);
                auVar53._0_4_ = afStack_80[4] * afStack_80[4];
                auVar53._4_4_ = fStack_6c * fStack_6c;
                auVar53._8_4_ = fStack_68 * fStack_68;
                auVar10._12_4_ = uStack_64;
                auVar51 = NEON_fmax(auVar10,auVar58,4);
                auVar53._12_4_ = 0;
                *(long *)(param_1 + 0x338) = auVar51._8_8_;
                *(long *)(param_1 + 0x330) = auVar51._0_8_;
                auVar51 = NEON_ext(auVar53,auVar53,8,1);
                uVar57 = NEON_rev64(CONCAT44(auVar51._0_4_ + auVar51._4_4_,
                                             auVar53._0_4_ + auVar53._4_4_),4);
                auVar49._0_4_ = auVar53._0_4_ + auVar53._4_4_ + (float)uVar57;
                auVar49._4_4_ = auVar49._0_4_;
                auVar49._8_4_ = auVar49._0_4_;
                auVar49._12_4_ = auVar49._0_4_;
                auVar58 = NEON_fmax(auVar49,auVar58,4);
                *(undefined4 *)(param_1 + 0x33c) = auVar58._12_4_;
                pfVar34 = *(float **)(param_1 + 0x368);
                auVar11._12_4_ = uStack_64;
                auVar58 = NEON_fmin(auVar11,*(undefined1 (*) [16])(param_1 + 0x340),4);
                *(long *)(param_1 + 0x348) = auVar58._8_8_;
                *(long *)(param_1 + 0x340) = auVar58._0_8_;
                *pfVar34 = afStack_80[4];
                pfVar34[1] = fStack_6c;
                pfVar34[4] = afStack_80[1];
                pfVar34[5] = afStack_80[2];
                pfVar34[6] = fVar36;
                pfVar34[2] = fStack_68;
                pfVar34[3] = afStack_80[0];
                lVar33 = *(long *)(param_1 + 0x358);
                uVar3 = *(ushort *)(*(long *)(lVar33 + 0x18) + 0x18);
                *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
                *(ulong *)(param_1 + 0x368) = *(long *)(param_1 + 0x368) + (ulong)uVar3;
                fVar40 = param_3[lVar32];
                fVar41 = *(float *)((long)param_8 + lVar26);
                afStack_80[lVar31 + 4] = fVar39;
                afStack_80[lVar24 + 4] = fVar56;
                afStack_80[lVar32 + 4] = fVar41 - fVar40;
                if (lVar33 == 0) {
                  lVar33 = 0;
                }
                else {
                  auVar7._4_4_ = fStack_6c;
                  auVar7._0_4_ = afStack_80[4];
                  auVar7._8_4_ = fStack_68;
                  auVar6._4_4_ = fStack_6c;
                  auVar6._0_4_ = afStack_80[4];
                  auVar6._8_4_ = fStack_68;
                  auVar58 = *(undefined1 (*) [16])(param_1 + 0x330);
                  auVar46._0_4_ = afStack_80[4] * afStack_80[4];
                  auVar46._4_4_ = fStack_6c * fStack_6c;
                  auVar46._8_4_ = fStack_68 * fStack_68;
                  auVar6._12_4_ = uStack_64;
                  auVar51 = NEON_fmax(auVar6,auVar58,4);
                  auVar46._12_4_ = 0;
                  *(long *)(param_1 + 0x338) = auVar51._8_8_;
                  *(long *)(param_1 + 0x330) = auVar51._0_8_;
                  auVar51 = NEON_ext(auVar46,auVar46,8,1);
                  uVar57 = NEON_rev64(CONCAT44(auVar51._0_4_ + auVar51._4_4_,
                                               auVar46._0_4_ + auVar46._4_4_),4);
                  auVar42._0_4_ = auVar46._0_4_ + auVar46._4_4_ + (float)uVar57;
                  auVar42._4_4_ = auVar42._0_4_;
                  auVar42._8_4_ = auVar42._0_4_;
                  auVar42._12_4_ = auVar42._0_4_;
                  auVar58 = NEON_fmax(auVar42,auVar58,4);
                  *(undefined4 *)(param_1 + 0x33c) = auVar58._12_4_;
                  pfVar34 = *(float **)(param_1 + 0x368);
                  auVar7._12_4_ = uStack_64;
                  auVar12._12_4_ = (int)((ulong)*(undefined8 *)(param_1 + 0x348) >> 0x20);
                  auVar12._0_12_ = *(undefined1 (*) [12])(param_1 + 0x340);
                  auVar58 = NEON_fmin(auVar7,auVar12,4);
                  *(long *)(param_1 + 0x348) = auVar58._8_8_;
                  *(long *)(param_1 + 0x340) = auVar58._0_8_;
                  *pfVar34 = afStack_80[4];
                  pfVar34[1] = fStack_6c;
                  pfVar34[4] = afStack_80[1];
                  pfVar34[5] = afStack_80[2];
                  pfVar34[6] = fVar36;
                  pfVar34[2] = fStack_68;
                  pfVar34[3] = afStack_80[0];
                  lVar33 = *(long *)(param_1 + 0x358);
                  *(ulong *)(param_1 + 0x368) =
                       *(long *)(param_1 + 0x368) +
                       (ulong)*(ushort *)(*(long *)(lVar33 + 0x18) + 0x18);
                  *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
                }
              }
            } while (param_5 != iVar22);
            if (iVar25 == param_4) goto code_r0x022083f0;
          }
          iVar25 = iVar25 + 1;
        } while (iVar25 != param_4);
code_r0x022083f0:
        uVar1 = *(uint *)(param_7 + lVar29 * 4 + 0xc);
        afStack_80[lVar32] = 1.0;
        if (0 < param_4) {
          iVar22 = 0;
          fVar36 = (float)(uVar1 >> 0x10 & 0xff | uVar1 & 0xff00ff00 | (uVar1 & 0xff) << 0x10);
          do {
            if (0 < param_5) {
              lVar33 = *(long *)(param_1 + 0x358);
              iVar25 = 0;
              do {
                fVar56 = param_3[lVar31];
                fVar41 = param_3[lVar24];
                fVar38 = *(float *)((long)param_8 + lVar31 * 4) - fVar56;
                fVar39 = *(float *)((long)param_8 + lVar24 * 4) - fVar41;
                fVar40 = fVar38 + ((float)(iVar22 + 1) / fVar35) * (fVar56 + fVar56);
                fVar38 = fVar38 + ((float)iVar22 / fVar35) * (fVar56 + fVar56);
                fVar56 = fVar39 + ((float)iVar25 / fVar37) * (fVar41 + fVar41);
                afStack_80[lVar31 + 4] = fVar40;
                lVar26 = lVar32 * 4;
                afStack_80[lVar24 + 4] = fVar56;
                iVar25 = iVar25 + 1;
                fVar44 = param_3[lVar32];
                fVar45 = *(float *)((long)param_8 + lVar26);
                fVar39 = fVar39 + ((float)iVar25 / fVar37) * (fVar41 + fVar41);
                afStack_80[lVar32 + 4] = fVar44 + fVar45;
                if (lVar33 == 0) {
                  afStack_80[lVar31 + 4] = fVar38;
                  afStack_80[lVar24 + 4] = fVar56;
                  afStack_80[lVar32 + 4] = fVar44 + fVar45;
code_r0x02208740:
                  afStack_80[lVar31 + 4] = fVar40;
                  afStack_80[lVar24 + 4] = fVar39;
                  afStack_80[lVar32 + 4] = fVar44 + fVar45;
code_r0x02208750:
                  afStack_80[lVar31 + 4] = fVar38;
                  lVar33 = 0;
                  afStack_80[lVar24 + 4] = fVar39;
                  afStack_80[lVar32 + 4] = fVar44 + fVar45;
                }
                else {
                  auVar20._4_4_ = fStack_6c;
                  auVar20._0_4_ = afStack_80[4];
                  auVar20._8_4_ = fStack_68;
                  auVar20._12_4_ = uStack_64;
                  auVar58 = *(undefined1 (*) [16])(param_1 + 0x330);
                  fVar41 = afStack_80[4] * afStack_80[4];
                  fVar44 = fStack_6c * fStack_6c;
                  auVar51 = NEON_fmax(auVar20,auVar58,4);
                  *(long *)(param_1 + 0x338) = auVar51._8_8_;
                  *(long *)(param_1 + 0x330) = auVar51._0_8_;
                  auVar16._4_4_ = fVar44;
                  auVar16._0_4_ = fVar41;
                  auVar16._8_4_ = fStack_68 * fStack_68;
                  auVar16._12_4_ = 0;
                  auVar17._4_4_ = fVar44;
                  auVar17._0_4_ = fVar41;
                  auVar17._8_4_ = fStack_68 * fStack_68;
                  auVar17._12_4_ = 0;
                  auVar51 = NEON_ext(auVar16,auVar17,8,1);
                  uVar57 = NEON_rev64(CONCAT44(auVar51._0_4_ + auVar51._4_4_,fVar41 + fVar44),4);
                  auVar61._0_4_ = fVar41 + fVar44 + (float)uVar57;
                  auVar61._4_4_ = auVar61._0_4_;
                  auVar61._8_4_ = auVar61._0_4_;
                  auVar61._12_4_ = auVar61._0_4_;
                  auVar58 = NEON_fmax(auVar61,auVar58,4);
                  *(undefined4 *)(param_1 + 0x33c) = auVar58._12_4_;
                  pfVar34 = *(float **)(param_1 + 0x368);
                  auVar58 = NEON_fmin(auVar20,*(undefined1 (*) [16])(param_1 + 0x340),4);
                  *(long *)(param_1 + 0x348) = auVar58._8_8_;
                  *(long *)(param_1 + 0x340) = auVar58._0_8_;
                  *pfVar34 = afStack_80[4];
                  pfVar34[1] = fStack_6c;
                  pfVar34[4] = afStack_80[1];
                  pfVar34[5] = afStack_80[2];
                  pfVar34[6] = fVar36;
                  pfVar34[2] = fStack_68;
                  pfVar34[3] = afStack_80[0];
                  lVar33 = *(long *)(param_1 + 0x358);
                  uVar3 = *(ushort *)(*(long *)(lVar33 + 0x18) + 0x18);
                  *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
                  *(ulong *)(param_1 + 0x368) = *(long *)(param_1 + 0x368) + (ulong)uVar3;
                  fVar44 = param_3[lVar32];
                  fVar45 = *(float *)((long)param_8 + lVar26);
                  afStack_80[lVar31 + 4] = fVar38;
                  afStack_80[lVar24 + 4] = fVar56;
                  afStack_80[lVar32 + 4] = fVar44 + fVar45;
                  if (lVar33 == 0) goto code_r0x02208740;
                  auVar21._4_4_ = fStack_6c;
                  auVar21._0_4_ = afStack_80[4];
                  auVar21._8_4_ = fStack_68;
                  auVar21._12_4_ = uStack_64;
                  auVar58 = *(undefined1 (*) [16])(param_1 + 0x330);
                  auVar62._0_4_ = afStack_80[4] * afStack_80[4];
                  auVar62._4_4_ = fStack_6c * fStack_6c;
                  auVar62._8_4_ = fStack_68 * fStack_68;
                  auVar51 = NEON_fmax(auVar21,auVar58,4);
                  auVar62._12_4_ = 0;
                  *(long *)(param_1 + 0x338) = auVar51._8_8_;
                  *(long *)(param_1 + 0x330) = auVar51._0_8_;
                  auVar51 = NEON_ext(auVar62,auVar62,8,1);
                  uVar57 = NEON_rev64(CONCAT44(auVar51._0_4_ + auVar51._4_4_,
                                               auVar62._0_4_ + auVar62._4_4_),4);
                  auVar54._0_4_ = auVar62._0_4_ + auVar62._4_4_ + (float)uVar57;
                  auVar54._4_4_ = auVar54._0_4_;
                  auVar54._8_4_ = auVar54._0_4_;
                  auVar54._12_4_ = auVar54._0_4_;
                  auVar58 = NEON_fmax(auVar54,auVar58,4);
                  *(undefined4 *)(param_1 + 0x33c) = auVar58._12_4_;
                  pfVar34 = *(float **)(param_1 + 0x368);
                  auVar58 = NEON_fmin(auVar21,*(undefined1 (*) [16])(param_1 + 0x340),4);
                  *(long *)(param_1 + 0x348) = auVar58._8_8_;
                  *(long *)(param_1 + 0x340) = auVar58._0_8_;
                  *pfVar34 = afStack_80[4];
                  pfVar34[1] = fStack_6c;
                  pfVar34[4] = afStack_80[1];
                  pfVar34[5] = afStack_80[2];
                  pfVar34[6] = fVar36;
                  pfVar34[2] = fStack_68;
                  pfVar34[3] = afStack_80[0];
                  lVar33 = *(long *)(param_1 + 0x358);
                  uVar3 = *(ushort *)(*(long *)(lVar33 + 0x18) + 0x18);
                  *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
                  *(ulong *)(param_1 + 0x368) = *(long *)(param_1 + 0x368) + (ulong)uVar3;
                  fVar44 = param_3[lVar32];
                  fVar45 = *(float *)((long)param_8 + lVar26);
                  afStack_80[lVar31 + 4] = fVar40;
                  afStack_80[lVar24 + 4] = fVar39;
                  afStack_80[lVar32 + 4] = fVar44 + fVar45;
                  if (lVar33 == 0) goto code_r0x02208750;
                  auVar14._4_4_ = fStack_6c;
                  auVar14._0_4_ = afStack_80[4];
                  auVar14._8_4_ = fStack_68;
                  auVar13._4_4_ = fStack_6c;
                  auVar13._0_4_ = afStack_80[4];
                  auVar13._8_4_ = fStack_68;
                  auVar58 = *(undefined1 (*) [16])(param_1 + 0x330);
                  auVar55._0_4_ = afStack_80[4] * afStack_80[4];
                  auVar55._4_4_ = fStack_6c * fStack_6c;
                  auVar55._8_4_ = fStack_68 * fStack_68;
                  auVar13._12_4_ = uStack_64;
                  auVar51 = NEON_fmax(auVar13,auVar58,4);
                  auVar55._12_4_ = 0;
                  *(long *)(param_1 + 0x338) = auVar51._8_8_;
                  *(long *)(param_1 + 0x330) = auVar51._0_8_;
                  auVar51 = NEON_ext(auVar55,auVar55,8,1);
                  uVar57 = NEON_rev64(CONCAT44(auVar51._0_4_ + auVar51._4_4_,
                                               auVar55._0_4_ + auVar55._4_4_),4);
                  auVar50._0_4_ = auVar55._0_4_ + auVar55._4_4_ + (float)uVar57;
                  auVar50._4_4_ = auVar50._0_4_;
                  auVar50._8_4_ = auVar50._0_4_;
                  auVar50._12_4_ = auVar50._0_4_;
                  auVar58 = NEON_fmax(auVar50,auVar58,4);
                  *(undefined4 *)(param_1 + 0x33c) = auVar58._12_4_;
                  pfVar34 = *(float **)(param_1 + 0x368);
                  auVar14._12_4_ = uStack_64;
                  auVar58 = NEON_fmin(auVar14,*(undefined1 (*) [16])(param_1 + 0x340),4);
                  *(long *)(param_1 + 0x348) = auVar58._8_8_;
                  *(long *)(param_1 + 0x340) = auVar58._0_8_;
                  *pfVar34 = afStack_80[4];
                  pfVar34[1] = fStack_6c;
                  pfVar34[4] = afStack_80[1];
                  pfVar34[5] = afStack_80[2];
                  pfVar34[6] = fVar36;
                  pfVar34[2] = fStack_68;
                  pfVar34[3] = afStack_80[0];
                  lVar33 = *(long *)(param_1 + 0x358);
                  uVar3 = *(ushort *)(*(long *)(lVar33 + 0x18) + 0x18);
                  *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
                  *(ulong *)(param_1 + 0x368) = *(long *)(param_1 + 0x368) + (ulong)uVar3;
                  fVar56 = param_3[lVar32];
                  fVar40 = *(float *)((long)param_8 + lVar26);
                  afStack_80[lVar31 + 4] = fVar38;
                  afStack_80[lVar24 + 4] = fVar39;
                  afStack_80[lVar32 + 4] = fVar56 + fVar40;
                  if (lVar33 == 0) {
                    lVar33 = 0;
                  }
                  else {
                    auVar9._4_4_ = fStack_6c;
                    auVar9._0_4_ = afStack_80[4];
                    auVar9._8_4_ = fStack_68;
                    auVar8._4_4_ = fStack_6c;
                    auVar8._0_4_ = afStack_80[4];
                    auVar8._8_4_ = fStack_68;
                    auVar58 = *(undefined1 (*) [16])(param_1 + 0x330);
                    auVar47._0_4_ = afStack_80[4] * afStack_80[4];
                    auVar47._4_4_ = fStack_6c * fStack_6c;
                    auVar47._8_4_ = fStack_68 * fStack_68;
                    auVar8._12_4_ = uStack_64;
                    auVar51 = NEON_fmax(auVar8,auVar58,4);
                    auVar47._12_4_ = 0;
                    *(long *)(param_1 + 0x338) = auVar51._8_8_;
                    *(long *)(param_1 + 0x330) = auVar51._0_8_;
                    auVar51 = NEON_ext(auVar47,auVar47,8,1);
                    uVar57 = NEON_rev64(CONCAT44(auVar51._0_4_ + auVar51._4_4_,
                                                 auVar47._0_4_ + auVar47._4_4_),4);
                    auVar43._0_4_ = auVar47._0_4_ + auVar47._4_4_ + (float)uVar57;
                    auVar43._4_4_ = auVar43._0_4_;
                    auVar43._8_4_ = auVar43._0_4_;
                    auVar43._12_4_ = auVar43._0_4_;
                    auVar58 = NEON_fmax(auVar43,auVar58,4);
                    *(undefined4 *)(param_1 + 0x33c) = auVar58._12_4_;
                    pfVar34 = *(float **)(param_1 + 0x368);
                    auVar9._12_4_ = uStack_64;
                    auVar15._12_4_ = (int)((ulong)*(undefined8 *)(param_1 + 0x348) >> 0x20);
                    auVar15._0_12_ = *(undefined1 (*) [12])(param_1 + 0x340);
                    auVar58 = NEON_fmin(auVar9,auVar15,4);
                    *(long *)(param_1 + 0x348) = auVar58._8_8_;
                    *(long *)(param_1 + 0x340) = auVar58._0_8_;
                    *pfVar34 = afStack_80[4];
                    pfVar34[1] = fStack_6c;
                    pfVar34[4] = afStack_80[1];
                    pfVar34[5] = afStack_80[2];
                    pfVar34[6] = fVar36;
                    pfVar34[2] = fStack_68;
                    pfVar34[3] = afStack_80[0];
                    lVar33 = *(long *)(param_1 + 0x358);
                    *(ulong *)(param_1 + 0x368) =
                         *(long *)(param_1 + 0x368) +
                         (ulong)*(ushort *)(*(long *)(lVar33 + 0x18) + 0x18);
                    *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
                  }
                }
              } while (param_5 != iVar25);
            }
            iVar22 = iVar22 + 1;
          } while (iVar22 != param_4);
        }
      }
      lVar29 = lVar29 + 1;
      if (lVar29 == 3) goto code_r0x02208780;
      param_4 = aiStack_a8[lVar29 * 2];
      param_5 = aiStack_a8[lVar29 * 2 + 1];
      iVar22 = aiStack_d0[lVar29 * 3 + 1];
      iVar25 = aiStack_d0[lVar29 * 3 + 2];
    } while( true );
  }
code_r0x02208a24:
  *(char *)(param_2 + 2) = cVar2;
  return;
code_r0x02208780:
  if (*(char *)(param_2 + 2) == '\x02') {
    if (0 < iVar28) {
      iVar28 = 0;
      do {
        if (*(long *)(param_1 + 0x358) != 0) {
          psVar30 = *(short **)(param_1 + 0x360);
          *(short **)(param_1 + 0x360) = psVar30 + 1;
          sVar5 = (short)iVar28;
          *psVar30 = sVar5;
          psVar30 = *(short **)(param_1 + 0x360);
          *(short **)(param_1 + 0x360) = psVar30 + 1;
          *psVar30 = sVar5 + 1;
          *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + 2;
          if (*(long *)(param_1 + 0x358) != 0) {
            psVar30 = *(short **)(param_1 + 0x360);
            *(short **)(param_1 + 0x360) = psVar30 + 1;
            *psVar30 = sVar5 + 1;
            psVar30 = *(short **)(param_1 + 0x360);
            *(short **)(param_1 + 0x360) = psVar30 + 1;
            *psVar30 = sVar5 + 3;
            *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + 2;
            if (*(long *)(param_1 + 0x358) != 0) {
              psVar30 = *(short **)(param_1 + 0x360);
              *(short **)(param_1 + 0x360) = psVar30 + 1;
              *psVar30 = sVar5 + 3;
              psVar30 = *(short **)(param_1 + 0x360);
              *(short **)(param_1 + 0x360) = psVar30 + 1;
              *psVar30 = sVar5 + 2;
              *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + 2;
              if (*(long *)(param_1 + 0x358) != 0) {
                psVar30 = *(short **)(param_1 + 0x360);
                *(short **)(param_1 + 0x360) = psVar30 + 1;
                *psVar30 = sVar5 + 2;
                psVar30 = *(short **)(param_1 + 0x360);
                *(short **)(param_1 + 0x360) = psVar30 + 1;
                *psVar30 = sVar5;
                *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + 2;
              }
            }
          }
        }
        iVar28 = iVar28 + 4;
      } while (iVar28 < iVar4);
    }
  }
  else if (*(char *)(param_2 + 2) == '\0') {
    if (0 < iVar28) {
      iVar28 = 0;
      do {
        if (*(long *)(param_1 + 0x358) != 0) {
          psVar30 = *(short **)(param_1 + 0x360);
          sVar5 = (short)iVar28;
          *(short **)(param_1 + 0x360) = psVar30 + 1;
          *psVar30 = sVar5 + 1;
          psVar30 = *(short **)(param_1 + 0x360);
          *(short **)(param_1 + 0x360) = psVar30 + 1;
          *psVar30 = sVar5 + 2;
          psVar30 = *(short **)(param_1 + 0x360);
          *(short **)(param_1 + 0x360) = psVar30 + 1;
          *psVar30 = sVar5;
          *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + 3;
          if (*(long *)(param_1 + 0x358) != 0) {
            psVar30 = *(short **)(param_1 + 0x360);
            *(short **)(param_1 + 0x360) = psVar30 + 1;
            *psVar30 = sVar5 + 1;
            psVar30 = *(short **)(param_1 + 0x360);
            *(short **)(param_1 + 0x360) = psVar30 + 1;
            *psVar30 = sVar5 + 3;
            psVar30 = *(short **)(param_1 + 0x360);
            *(short **)(param_1 + 0x360) = psVar30 + 1;
            *psVar30 = sVar5 + 2;
            *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + 3;
          }
        }
        iVar28 = iVar28 + 4;
      } while (iVar28 < iVar4);
    }
  }
  else if (0 < iVar28) {
    iVar28 = 0;
    do {
      if (*(long *)(param_1 + 0x358) != 0) {
        psVar30 = *(short **)(param_1 + 0x360);
        sVar5 = (short)iVar28;
        *(short **)(param_1 + 0x360) = psVar30 + 1;
        *psVar30 = sVar5 + 3;
        psVar30 = *(short **)(param_1 + 0x360);
        *(short **)(param_1 + 0x360) = psVar30 + 1;
        *psVar30 = sVar5 + 2;
        *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + 2;
        if (*(long *)(param_1 + 0x358) != 0) {
          psVar30 = *(short **)(param_1 + 0x360);
          *(short **)(param_1 + 0x360) = psVar30 + 1;
          *psVar30 = sVar5;
          psVar30 = *(short **)(param_1 + 0x360);
          *(short **)(param_1 + 0x360) = psVar30 + 1;
          *psVar30 = sVar5 + 1;
          *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + 2;
        }
      }
      iVar28 = iVar28 + 4;
    } while (iVar28 < iVar4);
  }
  Aska::DirectAofHandler::EndMesh()(param_1);
  fVar36 = *param_3 * *param_3 + param_3[1] * param_3[1] + param_3[2] * param_3[2];
  fStack_d4 = SQRT(fVar36);
  if (NAN(fStack_d4)) {
    fStack_d4 = (float)sqrtf(fVar36);
  }
  uStack_e0 = 0;
  uStack_d8 = 0;
  Aska::DirectAofHandler::Close(Aska::Vector const*, bool)(param_1,&uStack_e0,1);
  goto code_r0x02208a24;
}

// ==== Aska::DirectAofHandler::Box(Aska::DirectMaterial*, Aska::Vector const*, int, int, int, unsigned int, Aska::Vector const*)
// vaddr 0x2108a4c | ghidra 0x2208a4c | size 40 | symbol _ZN4Aska16DirectAofHandler3BoxEPNS_14DirectMaterialEPKNS_6VectorEiiijS5_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandler3BoxEPNS_14DirectMaterialEPKNS_6VectorEiiijS5_(void)

{
  Aska::DirectAofHandler::Box(Aska::DirectMaterial*, Aska::Vector const*, int, int, int, unsigned int*, Aska::Vector const*)();
  return;
}

// ==== Aska::DirectAofHandler::BoxT(Aska::DirectMaterial*, Aska::Vector const*, int, int, int, unsigned int*)
// vaddr 0x2108a74 | ghidra 0x2208a74 | size 2796 | symbol _ZN4Aska16DirectAofHandler4BoxTEPNS_14DirectMaterialEPKNS_6VectorEiiiPj | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16DirectAofHandler4BoxTEPNS_14DirectMaterialEPKNS_6VectorEiiiPj
               (long param_1,long param_2,float *param_3,int param_4,int param_5,int param_6,
               long param_7)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  short sVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  ulong uVar15;
  long lVar16;
  long lVar17;
  long lVar18;
  int iVar19;
  int iVar20;
  long lVar21;
  float *pfVar22;
  short *psVar23;
  long lVar24;
  ulong uVar25;
  int iVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  undefined1 auVar34 [16];
  undefined1 auVar35 [16];
  undefined1 auVar36 [16];
  float fVar37;
  undefined1 auVar38 [16];
  undefined1 auVar39 [16];
  undefined1 auVar40 [16];
  undefined1 auVar41 [16];
  undefined1 auVar42 [16];
  float fVar43;
  undefined1 auVar44 [16];
  undefined1 auVar45 [16];
  undefined1 auVar46 [16];
  undefined1 auVar47 [16];
  undefined1 auVar48 [16];
  undefined8 uVar49;
  undefined1 auVar50 [16];
  undefined1 auVar51 [16];
  undefined1 auVar52 [16];
  undefined1 auVar53 [16];
  undefined1 auVar54 [16];
  float fVar55;
  undefined8 uStack_e0;
  undefined4 uStack_d8;
  float fStack_d4;
  uint auStack_d0 [10];
  int aiStack_a8 [4];
  int iStack_98;
  int iStack_94;
  float afStack_90 [9];
  float fStack_6c;
  float fStack_68;
  undefined4 uStack_64;
  
  cVar2 = *(char *)(param_2 + 2);
  if (cVar2 != '\x02') {
    *(undefined1 *)(param_2 + 2) = 0;
  }
  auStack_d0[0] = 0;
  auStack_d0[5] = 0;
  iVar20 = param_6 * param_4 + (param_6 + param_4) * param_5;
  iVar3 = iVar20 * 8;
  uStack_64 = 0x3f800000;
  afStack_90[7] = 1.0;
  afStack_90[3] = 1.0;
  auStack_d0[3] = (uint)_UNK_029ca798;
  auStack_d0[4] = (uint)((ulong)_UNK_029ca798 >> 0x20);
  auStack_d0[1] = (uint)_UNK_029ca790;
  auStack_d0[2] = (uint)((ulong)_UNK_029ca790 >> 0x20);
  auStack_d0[6] = 2;
  auStack_d0[7] = 0;
  auStack_d0[8] = 1;
  if (cVar2 != '\x02') {
    iVar19 = iVar20 * 0xc;
  }
  else {
    iVar19 = iVar20 * 0x10;
  }
  aiStack_a8[0] = param_4;
  aiStack_a8[1] = param_5;
  aiStack_a8[2] = param_5;
  aiStack_a8[3] = param_6;
  iStack_98 = param_6;
  iStack_94 = param_4;
  uVar15 = Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)(param_1,param_2,iVar3,iVar19);
  if ((uVar15 & 1) != 0) {
    lVar21 = 0;
    uVar15 = 1;
    uVar25 = 2;
    do {
      lVar17 = (long)(int)auStack_d0[lVar21 * 3];
      uVar1 = *(uint *)(param_7 + lVar21 * 4);
      lVar16 = (long)(int)uVar15;
      uVar15 = -(uVar15 >> 0x1f) & 0xfffffffc00000000 | uVar15 << 2;
      lVar18 = (long)(int)uVar25;
      uVar25 = -(uVar25 >> 0x1f) & 0xfffffffc00000000 | uVar25 << 2;
      afStack_90[lVar17 + 4] = 0.0;
      *(undefined4 *)((long)afStack_90 + uVar15 + 0x10) = 0;
      *(undefined4 *)((long)afStack_90 + uVar25 + 0x10) = 0xbf800000;
      afStack_90[lVar17] = 0.0;
      *(undefined4 *)((long)afStack_90 + uVar15) = 0xbf800000;
      *(undefined4 *)((long)afStack_90 + uVar25) = 0;
      if (param_4 < 1) {
        afStack_90[lVar18 + 4] = 1.0;
        afStack_90[lVar16] = 1.0;
      }
      else {
        iVar19 = 0;
        fVar27 = (float)param_4;
        fVar29 = (float)param_5;
        fVar28 = (float)(uVar1 & 0xff000000 |
                        uVar1 & 0xff00 | uVar1 >> 0x10 & 0xff | (uVar1 & 0xff) << 0x10);
        do {
          while (0 < param_5) {
            fVar30 = (float)iVar19;
            iVar19 = iVar19 + 1;
            iVar26 = 0;
            do {
              fVar31 = param_3[lVar17];
              fVar43 = param_3[lVar16];
              fVar32 = (fVar30 / fVar27) * (fVar31 + fVar31) - fVar31;
              fVar33 = ((float)iVar26 / fVar29) * (fVar43 + fVar43) - fVar43;
              afStack_90[lVar17 + 8] = fVar32;
              afStack_90[lVar16 + 8] = fVar33;
              fVar37 = param_3[lVar18];
              iVar26 = iVar26 + 1;
              fVar31 = ((float)iVar19 / fVar27) * (fVar31 + fVar31) - fVar31;
              afStack_90[lVar18 + 8] = -fVar37;
              fVar43 = ((float)iVar26 / fVar29) * (fVar43 + fVar43) - fVar43;
              if (*(long *)(param_1 + 0x358) == 0) {
                afStack_90[lVar17 + 8] = fVar31;
                afStack_90[lVar16 + 8] = fVar33;
                afStack_90[lVar18 + 8] = -fVar37;
code_r0x02208ef4:
                afStack_90[lVar17 + 8] = fVar32;
                fVar37 = -fVar37;
                afStack_90[lVar16 + 8] = fVar43;
                afStack_90[lVar18 + 8] = fVar37;
code_r0x02208f04:
                afStack_90[lVar17 + 8] = fVar31;
                afStack_90[lVar16 + 8] = fVar43;
                afStack_90[lVar18 + 8] = fVar37;
              }
              else {
                auVar44._4_4_ = fStack_6c;
                auVar44._0_4_ = afStack_90[8];
                auVar44._8_4_ = fStack_68;
                auVar44._12_4_ = uStack_64;
                auVar34 = *(undefined1 (*) [16])(param_1 + 0x330);
                fVar37 = afStack_90[8] * afStack_90[8];
                fVar55 = fStack_6c * fStack_6c;
                auVar50 = NEON_fmax(auVar44,auVar34,4);
                *(long *)(param_1 + 0x338) = auVar50._8_8_;
                *(long *)(param_1 + 0x330) = auVar50._0_8_;
                auVar50._4_4_ = fVar55;
                auVar50._0_4_ = fVar37;
                auVar50._8_4_ = fStack_68 * fStack_68;
                auVar50._12_4_ = 0;
                auVar40._4_4_ = fVar55;
                auVar40._0_4_ = fVar37;
                auVar40._8_4_ = fStack_68 * fStack_68;
                auVar40._12_4_ = 0;
                auVar50 = NEON_ext(auVar50,auVar40,8,1);
                uVar49 = NEON_rev64(CONCAT44(auVar50._0_4_ + auVar50._4_4_,fVar37 + fVar55),4);
                auVar51._0_4_ = fVar37 + fVar55 + (float)uVar49;
                auVar51._4_4_ = auVar51._0_4_;
                auVar51._8_4_ = auVar51._0_4_;
                auVar51._12_4_ = auVar51._0_4_;
                auVar50 = NEON_fmax(auVar51,auVar34,4);
                *(undefined4 *)(param_1 + 0x33c) = auVar50._12_4_;
                pfVar22 = *(float **)(param_1 + 0x368);
                auVar50 = NEON_fmin(auVar44,*(undefined1 (*) [16])(param_1 + 0x340),4);
                *(long *)(param_1 + 0x348) = auVar50._8_8_;
                *(long *)(param_1 + 0x340) = auVar50._0_8_;
                *pfVar22 = afStack_90[8];
                pfVar22[1] = fStack_6c;
                pfVar22[4] = afStack_90[5];
                pfVar22[5] = afStack_90[6];
                pfVar22[6] = fVar28;
                pfVar22[7] = 0.0;
                pfVar22[8] = 0.0;
                pfVar22[9] = afStack_90[0];
                pfVar22[10] = afStack_90[1];
                pfVar22[0xb] = afStack_90[2];
                pfVar22[0xc] = afStack_90[3];
                pfVar22[2] = fStack_68;
                pfVar22[3] = afStack_90[4];
                pfVar22 = (float *)(*(long *)(param_1 + 0x368) + (ulong)*(ushort *)(param_1 + 0x354)
                                   );
                *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
                lVar24 = *(long *)(param_1 + 0x358);
                *(float **)(param_1 + 0x368) = pfVar22;
                afStack_90[lVar17 + 8] = fVar31;
                afStack_90[lVar16 + 8] = fVar33;
                fVar37 = param_3[lVar18];
                afStack_90[lVar18 + 8] = -fVar37;
                if (lVar24 == 0) goto code_r0x02208ef4;
                auVar34._4_4_ = fStack_6c;
                auVar34._0_4_ = afStack_90[8];
                auVar34._8_4_ = fStack_68;
                auVar34._12_4_ = uStack_64;
                auVar50 = *(undefined1 (*) [16])(param_1 + 0x330);
                auVar52._0_4_ = afStack_90[8] * afStack_90[8];
                auVar52._4_4_ = fStack_6c * fStack_6c;
                auVar52._8_4_ = fStack_68 * fStack_68;
                auVar44 = NEON_fmax(auVar34,auVar50,4);
                auVar40 = NEON_fmin(auVar34,*(undefined1 (*) [16])(param_1 + 0x340),4);
                auVar52._12_4_ = 0;
                *(long *)(param_1 + 0x338) = auVar44._8_8_;
                *(long *)(param_1 + 0x330) = auVar44._0_8_;
                *(long *)(param_1 + 0x348) = auVar40._8_8_;
                *(long *)(param_1 + 0x340) = auVar40._0_8_;
                auVar40 = NEON_ext(auVar52,auVar52,8,1);
                uVar49 = NEON_rev64(CONCAT44(auVar40._0_4_ + auVar40._4_4_,
                                             auVar52._0_4_ + auVar52._4_4_),4);
                auVar45._0_4_ = auVar52._0_4_ + auVar52._4_4_ + (float)uVar49;
                auVar45._4_4_ = auVar45._0_4_;
                auVar45._8_4_ = auVar45._0_4_;
                auVar45._12_4_ = auVar45._0_4_;
                auVar50 = NEON_fmax(auVar45,auVar50,4);
                *(undefined4 *)(param_1 + 0x33c) = auVar50._12_4_;
                *pfVar22 = afStack_90[8];
                pfVar22[1] = fStack_6c;
                pfVar22[4] = afStack_90[5];
                pfVar22[5] = afStack_90[6];
                pfVar22[6] = fVar28;
                pfVar22[7] = 0.0;
                pfVar22[8] = 1.0;
                pfVar22[9] = afStack_90[0];
                pfVar22[10] = afStack_90[1];
                pfVar22[0xb] = afStack_90[2];
                pfVar22[0xc] = afStack_90[3];
                pfVar22[2] = fStack_68;
                pfVar22[3] = afStack_90[4];
                *(ulong *)(param_1 + 0x368) =
                     *(long *)(param_1 + 0x368) + (ulong)*(ushort *)(param_1 + 0x354);
                *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
                fVar37 = param_3[lVar18];
                lVar24 = *(long *)(param_1 + 0x358);
                afStack_90[lVar17 + 8] = fVar32;
                afStack_90[lVar16 + 8] = fVar43;
                fVar37 = -fVar37;
                afStack_90[lVar18 + 8] = fVar37;
                if (lVar24 == 0) goto code_r0x02208f04;
                auVar11._4_4_ = fStack_6c;
                auVar11._0_4_ = afStack_90[8];
                auVar11._8_4_ = fStack_68;
                auVar11._12_4_ = uStack_64;
                auVar50 = *(undefined1 (*) [16])(param_1 + 0x330);
                auVar46._0_4_ = afStack_90[8] * afStack_90[8];
                auVar46._4_4_ = fStack_6c * fStack_6c;
                auVar46._8_4_ = fStack_68 * fStack_68;
                auVar40 = NEON_fmax(auVar11,auVar50,4);
                auVar46._12_4_ = 0;
                *(long *)(param_1 + 0x338) = auVar40._8_8_;
                *(long *)(param_1 + 0x330) = auVar40._0_8_;
                auVar40 = NEON_ext(auVar46,auVar46,8,1);
                uVar49 = NEON_rev64(CONCAT44(auVar40._0_4_ + auVar40._4_4_,
                                             auVar46._0_4_ + auVar46._4_4_),4);
                auVar41._0_4_ = auVar46._0_4_ + auVar46._4_4_ + (float)uVar49;
                auVar41._4_4_ = auVar41._0_4_;
                auVar41._8_4_ = auVar41._0_4_;
                auVar41._12_4_ = auVar41._0_4_;
                auVar50 = NEON_fmax(auVar41,auVar50,4);
                *(undefined4 *)(param_1 + 0x33c) = auVar50._12_4_;
                pfVar22 = *(float **)(param_1 + 0x368);
                auVar50 = NEON_fmin(auVar11,*(undefined1 (*) [16])(param_1 + 0x340),4);
                *(long *)(param_1 + 0x348) = auVar50._8_8_;
                *(long *)(param_1 + 0x340) = auVar50._0_8_;
                *pfVar22 = afStack_90[8];
                pfVar22[1] = fStack_6c;
                pfVar22[4] = afStack_90[5];
                pfVar22[5] = afStack_90[6];
                pfVar22[6] = fVar28;
                pfVar22[7] = 1.0;
                pfVar22[8] = 0.0;
                pfVar22[9] = afStack_90[0];
                pfVar22[10] = afStack_90[1];
                pfVar22[0xb] = afStack_90[2];
                pfVar22[0xc] = afStack_90[3];
                pfVar22[2] = fStack_68;
                pfVar22[3] = afStack_90[4];
                pfVar22 = (float *)(*(long *)(param_1 + 0x368) + (ulong)*(ushort *)(param_1 + 0x354)
                                   );
                *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
                lVar24 = *(long *)(param_1 + 0x358);
                *(float **)(param_1 + 0x368) = pfVar22;
                afStack_90[lVar17 + 8] = fVar31;
                afStack_90[lVar16 + 8] = fVar43;
                afStack_90[lVar18 + 8] = -param_3[lVar18];
                if (lVar24 != 0) {
                  auVar6._4_4_ = fStack_6c;
                  auVar6._0_4_ = afStack_90[8];
                  auVar6._8_4_ = fStack_68;
                  auVar5._4_4_ = fStack_6c;
                  auVar5._0_4_ = afStack_90[8];
                  auVar5._8_4_ = fStack_68;
                  auVar50 = *(undefined1 (*) [16])(param_1 + 0x330);
                  auVar38._0_4_ = afStack_90[8] * afStack_90[8];
                  auVar38._4_4_ = fStack_6c * fStack_6c;
                  auVar38._8_4_ = fStack_68 * fStack_68;
                  auVar5._12_4_ = uStack_64;
                  auVar34 = NEON_fmax(auVar5,auVar50,4);
                  auVar6._12_4_ = uStack_64;
                  auVar40 = NEON_fmin(auVar6,*(undefined1 (*) [16])(param_1 + 0x340),4);
                  auVar38._12_4_ = 0;
                  *(long *)(param_1 + 0x338) = auVar34._8_8_;
                  *(long *)(param_1 + 0x330) = auVar34._0_8_;
                  *(long *)(param_1 + 0x348) = auVar40._8_8_;
                  *(long *)(param_1 + 0x340) = auVar40._0_8_;
                  auVar40 = NEON_ext(auVar38,auVar38,8,1);
                  uVar49 = NEON_rev64(CONCAT44(auVar40._0_4_ + auVar40._4_4_,
                                               auVar38._0_4_ + auVar38._4_4_),4);
                  auVar35._0_4_ = auVar38._0_4_ + auVar38._4_4_ + (float)uVar49;
                  auVar35._4_4_ = auVar35._0_4_;
                  auVar35._8_4_ = auVar35._0_4_;
                  auVar35._12_4_ = auVar35._0_4_;
                  auVar50 = NEON_fmax(auVar35,auVar50,4);
                  *(undefined4 *)(param_1 + 0x33c) = auVar50._12_4_;
                  *pfVar22 = afStack_90[8];
                  pfVar22[1] = fStack_6c;
                  pfVar22[4] = afStack_90[5];
                  pfVar22[5] = afStack_90[6];
                  pfVar22[6] = fVar28;
                  pfVar22[7] = 1.0;
                  pfVar22[8] = 1.0;
                  pfVar22[9] = afStack_90[0];
                  pfVar22[10] = afStack_90[1];
                  pfVar22[0xb] = afStack_90[2];
                  pfVar22[0xc] = afStack_90[3];
                  pfVar22[2] = fStack_68;
                  pfVar22[3] = afStack_90[4];
                  *(ulong *)(param_1 + 0x368) =
                       *(long *)(param_1 + 0x368) + (ulong)*(ushort *)(param_1 + 0x354);
                  *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
                }
              }
            } while (param_5 != iVar26);
            if (iVar19 == param_4) goto code_r0x02208f30;
          }
          iVar19 = iVar19 + 1;
        } while (iVar19 != param_4);
code_r0x02208f30:
        uVar1 = *(uint *)(param_7 + lVar21 * 4 + 0xc);
        afStack_90[lVar18 + 4] = 1.0;
        afStack_90[lVar16] = 1.0;
        if (0 < param_4) {
          iVar19 = 0;
          fVar28 = (float)(uVar1 >> 0x10 & 0xff | uVar1 & 0xff00ff00 | (uVar1 & 0xff) << 0x10);
          do {
            if (0 < param_5) {
              iVar26 = 0;
              do {
                fVar31 = param_3[lVar17];
                fVar43 = param_3[lVar16];
                fVar32 = ((float)(iVar19 + 1) / fVar27) * (fVar31 + fVar31) - fVar31;
                fVar37 = ((float)iVar26 / fVar29) * (fVar43 + fVar43) - fVar43;
                afStack_90[lVar17 + 8] = fVar32;
                afStack_90[lVar16 + 8] = fVar37;
                fVar30 = param_3[lVar18];
                iVar26 = iVar26 + 1;
                fVar31 = ((float)iVar19 / fVar27) * (fVar31 + fVar31) - fVar31;
                afStack_90[lVar18 + 8] = fVar30;
                fVar43 = ((float)iVar26 / fVar29) * (fVar43 + fVar43) - fVar43;
                if (*(long *)(param_1 + 0x358) == 0) {
                  afStack_90[lVar17 + 8] = fVar31;
                  afStack_90[lVar16 + 8] = fVar37;
                  afStack_90[lVar18 + 8] = fVar30;
code_r0x02209258:
                  afStack_90[lVar17 + 8] = fVar32;
                  afStack_90[lVar16 + 8] = fVar43;
                  afStack_90[lVar18 + 8] = fVar30;
code_r0x02209264:
                  afStack_90[lVar17 + 8] = fVar31;
                  afStack_90[lVar16 + 8] = fVar43;
                  afStack_90[lVar18 + 8] = fVar30;
                }
                else {
                  auVar12._4_4_ = fStack_6c;
                  auVar12._0_4_ = afStack_90[8];
                  auVar12._8_4_ = fStack_68;
                  auVar12._12_4_ = uStack_64;
                  auVar50 = *(undefined1 (*) [16])(param_1 + 0x330);
                  fVar30 = afStack_90[8] * afStack_90[8];
                  fVar33 = fStack_6c * fStack_6c;
                  auVar40 = NEON_fmax(auVar12,auVar50,4);
                  *(long *)(param_1 + 0x338) = auVar40._8_8_;
                  *(long *)(param_1 + 0x330) = auVar40._0_8_;
                  auVar9._4_4_ = fVar33;
                  auVar9._0_4_ = fVar30;
                  auVar9._8_4_ = fStack_68 * fStack_68;
                  auVar9._12_4_ = 0;
                  auVar10._4_4_ = fVar33;
                  auVar10._0_4_ = fVar30;
                  auVar10._8_4_ = fStack_68 * fStack_68;
                  auVar10._12_4_ = 0;
                  auVar40 = NEON_ext(auVar9,auVar10,8,1);
                  uVar49 = NEON_rev64(CONCAT44(auVar40._0_4_ + auVar40._4_4_,fVar30 + fVar33),4);
                  auVar53._0_4_ = fVar30 + fVar33 + (float)uVar49;
                  auVar53._4_4_ = auVar53._0_4_;
                  auVar53._8_4_ = auVar53._0_4_;
                  auVar53._12_4_ = auVar53._0_4_;
                  auVar50 = NEON_fmax(auVar53,auVar50,4);
                  *(undefined4 *)(param_1 + 0x33c) = auVar50._12_4_;
                  pfVar22 = *(float **)(param_1 + 0x368);
                  auVar50 = NEON_fmin(auVar12,*(undefined1 (*) [16])(param_1 + 0x340),4);
                  *(long *)(param_1 + 0x348) = auVar50._8_8_;
                  *(long *)(param_1 + 0x340) = auVar50._0_8_;
                  *pfVar22 = afStack_90[8];
                  pfVar22[1] = fStack_6c;
                  pfVar22[4] = afStack_90[5];
                  pfVar22[5] = afStack_90[6];
                  pfVar22[6] = fVar28;
                  pfVar22[7] = 0.0;
                  pfVar22[8] = 0.0;
                  pfVar22[9] = afStack_90[4];
                  pfVar22[10] = afStack_90[5];
                  pfVar22[0xb] = afStack_90[6];
                  pfVar22[0xc] = afStack_90[7];
                  pfVar22[2] = fStack_68;
                  pfVar22[3] = afStack_90[4];
                  pfVar22 = (float *)(*(long *)(param_1 + 0x368) +
                                     (ulong)*(ushort *)(param_1 + 0x354));
                  lVar24 = *(long *)(param_1 + 0x358);
                  *(float **)(param_1 + 0x368) = pfVar22;
                  *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
                  afStack_90[lVar17 + 8] = fVar31;
                  afStack_90[lVar16 + 8] = fVar37;
                  fVar30 = param_3[lVar18];
                  afStack_90[lVar18 + 8] = fVar30;
                  if (lVar24 == 0) goto code_r0x02209258;
                  auVar13._4_4_ = fStack_6c;
                  auVar13._0_4_ = afStack_90[8];
                  auVar13._8_4_ = fStack_68;
                  auVar13._12_4_ = uStack_64;
                  auVar50 = *(undefined1 (*) [16])(param_1 + 0x330);
                  auVar54._0_4_ = afStack_90[8] * afStack_90[8];
                  auVar54._4_4_ = fStack_6c * fStack_6c;
                  auVar54._8_4_ = fStack_68 * fStack_68;
                  auVar34 = NEON_fmax(auVar13,auVar50,4);
                  auVar40 = NEON_fmin(auVar13,*(undefined1 (*) [16])(param_1 + 0x340),4);
                  auVar54._12_4_ = 0;
                  *(long *)(param_1 + 0x338) = auVar34._8_8_;
                  *(long *)(param_1 + 0x330) = auVar34._0_8_;
                  *(long *)(param_1 + 0x348) = auVar40._8_8_;
                  *(long *)(param_1 + 0x340) = auVar40._0_8_;
                  auVar40 = NEON_ext(auVar54,auVar54,8,1);
                  uVar49 = NEON_rev64(CONCAT44(auVar40._0_4_ + auVar40._4_4_,
                                               auVar54._0_4_ + auVar54._4_4_),4);
                  auVar47._0_4_ = auVar54._0_4_ + auVar54._4_4_ + (float)uVar49;
                  auVar47._4_4_ = auVar47._0_4_;
                  auVar47._8_4_ = auVar47._0_4_;
                  auVar47._12_4_ = auVar47._0_4_;
                  auVar50 = NEON_fmax(auVar47,auVar50,4);
                  *(undefined4 *)(param_1 + 0x33c) = auVar50._12_4_;
                  *pfVar22 = afStack_90[8];
                  pfVar22[1] = fStack_6c;
                  pfVar22[4] = afStack_90[5];
                  pfVar22[5] = afStack_90[6];
                  pfVar22[6] = fVar28;
                  pfVar22[7] = 0.0;
                  pfVar22[8] = 1.0;
                  pfVar22[9] = afStack_90[4];
                  pfVar22[10] = afStack_90[5];
                  pfVar22[0xb] = afStack_90[6];
                  pfVar22[0xc] = afStack_90[7];
                  pfVar22[2] = fStack_68;
                  pfVar22[3] = afStack_90[4];
                  *(ulong *)(param_1 + 0x368) =
                       *(long *)(param_1 + 0x368) + (ulong)*(ushort *)(param_1 + 0x354);
                  *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
                  fVar30 = param_3[lVar18];
                  lVar24 = *(long *)(param_1 + 0x358);
                  afStack_90[lVar17 + 8] = fVar32;
                  afStack_90[lVar16 + 8] = fVar43;
                  afStack_90[lVar18 + 8] = fVar30;
                  if (lVar24 == 0) goto code_r0x02209264;
                  auVar14._4_4_ = fStack_6c;
                  auVar14._0_4_ = afStack_90[8];
                  auVar14._8_4_ = fStack_68;
                  auVar14._12_4_ = uStack_64;
                  auVar50 = *(undefined1 (*) [16])(param_1 + 0x330);
                  auVar48._0_4_ = afStack_90[8] * afStack_90[8];
                  auVar48._4_4_ = fStack_6c * fStack_6c;
                  auVar48._8_4_ = fStack_68 * fStack_68;
                  auVar40 = NEON_fmax(auVar14,auVar50,4);
                  auVar48._12_4_ = 0;
                  *(long *)(param_1 + 0x338) = auVar40._8_8_;
                  *(long *)(param_1 + 0x330) = auVar40._0_8_;
                  auVar40 = NEON_ext(auVar48,auVar48,8,1);
                  uVar49 = NEON_rev64(CONCAT44(auVar40._0_4_ + auVar40._4_4_,
                                               auVar48._0_4_ + auVar48._4_4_),4);
                  auVar42._0_4_ = auVar48._0_4_ + auVar48._4_4_ + (float)uVar49;
                  auVar42._4_4_ = auVar42._0_4_;
                  auVar42._8_4_ = auVar42._0_4_;
                  auVar42._12_4_ = auVar42._0_4_;
                  auVar50 = NEON_fmax(auVar42,auVar50,4);
                  *(undefined4 *)(param_1 + 0x33c) = auVar50._12_4_;
                  pfVar22 = *(float **)(param_1 + 0x368);
                  auVar50 = NEON_fmin(auVar14,*(undefined1 (*) [16])(param_1 + 0x340),4);
                  *(long *)(param_1 + 0x348) = auVar50._8_8_;
                  *(long *)(param_1 + 0x340) = auVar50._0_8_;
                  *pfVar22 = afStack_90[8];
                  pfVar22[1] = fStack_6c;
                  pfVar22[4] = afStack_90[5];
                  pfVar22[5] = afStack_90[6];
                  pfVar22[6] = fVar28;
                  pfVar22[7] = 1.0;
                  pfVar22[8] = 0.0;
                  pfVar22[9] = afStack_90[4];
                  pfVar22[10] = afStack_90[5];
                  pfVar22[0xb] = afStack_90[6];
                  pfVar22[0xc] = afStack_90[7];
                  pfVar22[2] = fStack_68;
                  pfVar22[3] = afStack_90[4];
                  pfVar22 = (float *)(*(long *)(param_1 + 0x368) +
                                     (ulong)*(ushort *)(param_1 + 0x354));
                  lVar24 = *(long *)(param_1 + 0x358);
                  *(float **)(param_1 + 0x368) = pfVar22;
                  *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
                  afStack_90[lVar17 + 8] = fVar31;
                  afStack_90[lVar16 + 8] = fVar43;
                  afStack_90[lVar18 + 8] = param_3[lVar18];
                  if (lVar24 != 0) {
                    auVar8._4_4_ = fStack_6c;
                    auVar8._0_4_ = afStack_90[8];
                    auVar8._8_4_ = fStack_68;
                    auVar7._4_4_ = fStack_6c;
                    auVar7._0_4_ = afStack_90[8];
                    auVar7._8_4_ = fStack_68;
                    auVar50 = *(undefined1 (*) [16])(param_1 + 0x330);
                    auVar39._0_4_ = afStack_90[8] * afStack_90[8];
                    auVar39._4_4_ = fStack_6c * fStack_6c;
                    auVar39._8_4_ = fStack_68 * fStack_68;
                    auVar7._12_4_ = uStack_64;
                    auVar34 = NEON_fmax(auVar7,auVar50,4);
                    auVar8._12_4_ = uStack_64;
                    auVar40 = NEON_fmin(auVar8,*(undefined1 (*) [16])(param_1 + 0x340),4);
                    auVar39._12_4_ = 0;
                    *(long *)(param_1 + 0x338) = auVar34._8_8_;
                    *(long *)(param_1 + 0x330) = auVar34._0_8_;
                    *(long *)(param_1 + 0x348) = auVar40._8_8_;
                    *(long *)(param_1 + 0x340) = auVar40._0_8_;
                    auVar40 = NEON_ext(auVar39,auVar39,8,1);
                    uVar49 = NEON_rev64(CONCAT44(auVar40._0_4_ + auVar40._4_4_,
                                                 auVar39._0_4_ + auVar39._4_4_),4);
                    auVar36._0_4_ = auVar39._0_4_ + auVar39._4_4_ + (float)uVar49;
                    auVar36._4_4_ = auVar36._0_4_;
                    auVar36._8_4_ = auVar36._0_4_;
                    auVar36._12_4_ = auVar36._0_4_;
                    auVar50 = NEON_fmax(auVar36,auVar50,4);
                    *(undefined4 *)(param_1 + 0x33c) = auVar50._12_4_;
                    *pfVar22 = afStack_90[8];
                    pfVar22[1] = fStack_6c;
                    pfVar22[4] = afStack_90[5];
                    pfVar22[5] = afStack_90[6];
                    pfVar22[6] = fVar28;
                    pfVar22[7] = 1.0;
                    pfVar22[8] = 1.0;
                    pfVar22[9] = afStack_90[4];
                    pfVar22[10] = afStack_90[5];
                    pfVar22[0xb] = afStack_90[6];
                    pfVar22[0xc] = afStack_90[7];
                    pfVar22[2] = fStack_68;
                    pfVar22[3] = afStack_90[4];
                    *(ulong *)(param_1 + 0x368) =
                         *(long *)(param_1 + 0x368) + (ulong)*(ushort *)(param_1 + 0x354);
                    *(int *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + 1;
                  }
                }
              } while (param_5 != iVar26);
            }
            iVar19 = iVar19 + 1;
          } while (iVar19 != param_4);
        }
      }
      lVar21 = lVar21 + 1;
      if (lVar21 == 3) goto code_r0x0220928c;
      param_4 = aiStack_a8[lVar21 * 2];
      param_5 = aiStack_a8[lVar21 * 2 + 1];
      uVar15 = (ulong)auStack_d0[lVar21 * 3 + 1];
      uVar25 = (ulong)auStack_d0[lVar21 * 3 + 2];
    } while( true );
  }
code_r0x02209534:
  *(char *)(param_2 + 2) = cVar2;
  return;
code_r0x0220928c:
  if (*(char *)(param_2 + 2) == '\x02') {
    if (0 < iVar20) {
      iVar20 = 0;
      do {
        if (*(long *)(param_1 + 0x358) != 0) {
          psVar23 = *(short **)(param_1 + 0x360);
          *(short **)(param_1 + 0x360) = psVar23 + 1;
          sVar4 = (short)iVar20;
          *psVar23 = sVar4;
          psVar23 = *(short **)(param_1 + 0x360);
          *(short **)(param_1 + 0x360) = psVar23 + 1;
          *psVar23 = sVar4 + 1;
          *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + 2;
          if (*(long *)(param_1 + 0x358) != 0) {
            psVar23 = *(short **)(param_1 + 0x360);
            *(short **)(param_1 + 0x360) = psVar23 + 1;
            *psVar23 = sVar4 + 1;
            psVar23 = *(short **)(param_1 + 0x360);
            *(short **)(param_1 + 0x360) = psVar23 + 1;
            *psVar23 = sVar4 + 3;
            *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + 2;
            if (*(long *)(param_1 + 0x358) != 0) {
              psVar23 = *(short **)(param_1 + 0x360);
              *(short **)(param_1 + 0x360) = psVar23 + 1;
              *psVar23 = sVar4 + 3;
              psVar23 = *(short **)(param_1 + 0x360);
              *(short **)(param_1 + 0x360) = psVar23 + 1;
              *psVar23 = sVar4 + 2;
              *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + 2;
              if (*(long *)(param_1 + 0x358) != 0) {
                psVar23 = *(short **)(param_1 + 0x360);
                *(short **)(param_1 + 0x360) = psVar23 + 1;
                *psVar23 = sVar4 + 2;
                psVar23 = *(short **)(param_1 + 0x360);
                *(short **)(param_1 + 0x360) = psVar23 + 1;
                *psVar23 = sVar4;
                *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + 2;
              }
            }
          }
        }
        iVar20 = iVar20 + 4;
      } while (iVar20 < iVar3);
    }
  }
  else if (*(char *)(param_2 + 2) == '\0') {
    if (0 < iVar20) {
      iVar20 = 0;
      do {
        if (*(long *)(param_1 + 0x358) != 0) {
          psVar23 = *(short **)(param_1 + 0x360);
          sVar4 = (short)iVar20;
          *(short **)(param_1 + 0x360) = psVar23 + 1;
          *psVar23 = sVar4 + 1;
          psVar23 = *(short **)(param_1 + 0x360);
          *(short **)(param_1 + 0x360) = psVar23 + 1;
          *psVar23 = sVar4 + 2;
          psVar23 = *(short **)(param_1 + 0x360);
          *(short **)(param_1 + 0x360) = psVar23 + 1;
          *psVar23 = sVar4;
          *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + 3;
          if (*(long *)(param_1 + 0x358) != 0) {
            psVar23 = *(short **)(param_1 + 0x360);
            *(short **)(param_1 + 0x360) = psVar23 + 1;
            *psVar23 = sVar4 + 1;
            psVar23 = *(short **)(param_1 + 0x360);
            *(short **)(param_1 + 0x360) = psVar23 + 1;
            *psVar23 = sVar4 + 3;
            psVar23 = *(short **)(param_1 + 0x360);
            *(short **)(param_1 + 0x360) = psVar23 + 1;
            *psVar23 = sVar4 + 2;
            *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + 3;
          }
        }
        iVar20 = iVar20 + 4;
      } while (iVar20 < iVar3);
    }
  }
  else if (0 < iVar20) {
    iVar20 = 0;
    do {
      if (*(long *)(param_1 + 0x358) != 0) {
        psVar23 = *(short **)(param_1 + 0x360);
        sVar4 = (short)iVar20;
        *(short **)(param_1 + 0x360) = psVar23 + 1;
        *psVar23 = sVar4 + 3;
        psVar23 = *(short **)(param_1 + 0x360);
        *(short **)(param_1 + 0x360) = psVar23 + 1;
        *psVar23 = sVar4 + 2;
        *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + 2;
        if (*(long *)(param_1 + 0x358) != 0) {
          psVar23 = *(short **)(param_1 + 0x360);
          *(short **)(param_1 + 0x360) = psVar23 + 1;
          *psVar23 = sVar4;
          psVar23 = *(short **)(param_1 + 0x360);
          *(short **)(param_1 + 0x360) = psVar23 + 1;
          *psVar23 = sVar4 + 1;
          *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + 2;
        }
      }
      iVar20 = iVar20 + 4;
    } while (iVar20 < iVar3);
  }
  Aska::DirectAofHandler::EndMesh()(param_1);
  fVar28 = *param_3 * *param_3 + param_3[1] * param_3[1] + param_3[2] * param_3[2];
  fStack_d4 = SQRT(fVar28);
  if (NAN(fStack_d4)) {
    fStack_d4 = (float)sqrtf(fVar28);
  }
  uStack_e0 = 0;
  uStack_d8 = 0;
  Aska::DirectAofHandler::Close(Aska::Vector const*, bool)(param_1,&uStack_e0,1);
  goto code_r0x02209534;
}

// ==== Aska::DirectAofHandler::BoxT(Aska::DirectMaterial*, Aska::Vector const*, int, int, int, unsigned int)
// vaddr 0x2109560 | ghidra 0x2209560 | size 40 | symbol _ZN4Aska16DirectAofHandler4BoxTEPNS_14DirectMaterialEPKNS_6VectorEiiij | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandler4BoxTEPNS_14DirectMaterialEPKNS_6VectorEiiij(void)

{
  Aska::DirectAofHandler::BoxT(Aska::DirectMaterial*, Aska::Vector const*, int, int, int, unsigned int*)();
  return;
}

// ==== Aska::DirectAofHandler::Capsule(Aska::DirectMaterial*, Aska::Segment const*, float, int, int, unsigned int)
// vaddr 0x2109588 | ghidra 0x2209588 | size 4776 | symbol _ZN4Aska16DirectAofHandler7CapsuleEPNS_14DirectMaterialEPKNS_7SegmentEfiij | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16DirectAofHandler7CapsuleEPNS_14DirectMaterialEPKNS_7SegmentEfiij
               (float param_1,long *param_2,long param_3,long param_4,int param_5,uint param_6,
               uint param_7)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  short sVar4;
  float fVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  short sVar9;
  uint uVar10;
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  undefined1 auVar26 [16];
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined8 uVar29;
  short sVar30;
  short sVar31;
  short sVar32;
  short sVar33;
  short sVar34;
  short sVar35;
  float fVar36;
  ulong uVar37;
  byte bVar38;
  float *pfVar39;
  long lVar40;
  uint uVar41;
  int iVar42;
  short *psVar43;
  uint uVar44;
  int iVar45;
  float fVar46;
  float fVar47;
  float fVar48;
  float fVar49;
  undefined1 auVar50 [16];
  undefined1 auVar51 [16];
  undefined1 auVar52 [16];
  undefined1 auVar53 [16];
  undefined1 auVar54 [16];
  undefined1 auVar55 [16];
  undefined1 auVar56 [16];
  undefined1 auVar57 [16];
  undefined1 auVar58 [16];
  undefined1 auVar59 [16];
  undefined1 auVar60 [16];
  undefined1 auVar61 [16];
  float fVar62;
  float fVar63;
  undefined1 auVar64 [16];
  undefined1 auVar65 [16];
  undefined1 auVar66 [16];
  undefined1 auVar67 [16];
  undefined1 auVar68 [16];
  undefined1 auVar69 [16];
  undefined1 auVar70 [16];
  undefined1 auVar71 [16];
  undefined1 auVar72 [16];
  undefined1 auVar73 [16];
  undefined1 auVar74 [16];
  float fVar75;
  float fVar76;
  float fVar77;
  float fVar78;
  float fVar79;
  float fStack_d4;
  undefined4 uStack_c4;
  undefined8 uStack_b0;
  undefined4 uStack_a8;
  float fStack_a4;
  
  fStack_d4 = SQRT(*(float *)(param_4 + 0x10) * *(float *)(param_4 + 0x10) +
                   *(float *)(param_4 + 0x14) * *(float *)(param_4 + 0x14) +
                   *(float *)(param_4 + 0x18) * *(float *)(param_4 + 0x18));
  if (NAN(fStack_d4)) {
    fStack_d4 = (float)sqrtf();
  }
  cVar3 = *(char *)(param_3 + 2);
  if (cVar3 != '\x02') {
    *(undefined1 *)(param_3 + 2) = 0;
  }
  uVar1 = param_6;
  if ((int)param_6 < 0) {
    uVar1 = param_6 + 1;
  }
  iVar45 = param_5;
  if ((param_6 & 1) != 0) {
    iVar45 = 0;
  }
  uVar1 = ((int)uVar1 >> 1) - 1;
  iVar45 = param_6 * param_5 + param_5 + iVar45;
  sVar35 = (short)param_5;
  if (cVar3 != '\x02') {
    uVar37 = Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)(param_2,param_3,iVar45,iVar45 * 6);
    fVar36 = _UNK_027e3fd0;
    if ((uVar37 & 1) == 0) goto code_r0x0220a7fc;
    uVar10 = param_6 - 1;
    if (0 < (int)param_6) {
      uVar44 = param_6;
      if (-1 < (int)uVar10) {
        uVar44 = uVar10;
      }
      auVar61 = NEON_fmov(0x3f800000,4);
      fVar46 = ((((float)((int)uVar44 >> 1) - (float)(int)uVar10 * 0.5) + 0.5) * _UNK_027e3fd0) /
               (float)(int)(param_6 - 2);
      uVar44 = 0;
      fVar75 = (float)param_5;
      fVar5 = (float)(param_7 >> 0x10 & 0xff | param_7 & 0xff00ff00 | (param_7 & 0xff) << 0x10);
      do {
        fVar76 = ((((float)(int)uVar44 - (float)(int)param_6 * 0.5) + 0.5) * fVar36) /
                 (float)(int)uVar10;
        fVar47 = (float)cosf(fVar76);
        fVar76 = (float)sinf(fVar76);
        if (0 < param_5) {
          fVar49 = fVar76 * param_1;
          iVar45 = 0;
          uStack_c4 = auVar61._12_4_;
          if (fVar76 <= 0.0) {
            do {
              fVar77 = (((float)iVar45 + (float)iVar45) * fVar36) / fVar75;
              fVar48 = (float)cosf(fVar77);
              fVar77 = (float)sinf(fVar77);
              if (param_2[0x6b] != 0) {
                auVar21 = *(undefined1 (*) [16])(param_2 + 0x66);
                fVar62 = fVar47 * fVar48 * param_1;
                fVar63 = fVar47 * fVar77 * param_1;
                auVar57._4_4_ = fVar62;
                auVar57._0_4_ = fVar49;
                auVar57._8_4_ = fVar63;
                auVar57._12_4_ = uStack_c4;
                fVar78 = fVar49 * fVar49;
                fVar79 = fVar62 * fVar62;
                auVar51 = NEON_fmax(auVar57,auVar21,4);
                param_2[0x67] = auVar51._8_8_;
                param_2[0x66] = auVar51._0_8_;
                auVar51._4_4_ = fVar79;
                auVar51._0_4_ = fVar78;
                auVar51._8_4_ = fVar63 * fVar63;
                auVar51._12_4_ = 0;
                auVar64._4_4_ = fVar79;
                auVar64._0_4_ = fVar78;
                auVar64._8_4_ = fVar63 * fVar63;
                auVar64._12_4_ = 0;
                auVar51 = NEON_ext(auVar51,auVar64,8,1);
                uVar29 = NEON_rev64(CONCAT44(auVar51._0_4_ + auVar51._4_4_,fVar78 + fVar79),4);
                auVar71._0_4_ = fVar78 + fVar79 + (float)uVar29;
                auVar71._4_4_ = auVar71._0_4_;
                auVar71._8_4_ = auVar71._0_4_;
                auVar71._12_4_ = auVar71._0_4_;
                auVar64 = NEON_fmax(auVar71,auVar21,4);
                auVar51 = NEON_fmin(auVar57,*(undefined1 (*) [16])(param_2 + 0x68),4);
                *(int *)((long)param_2 + 0x33c) = auVar64._12_4_;
                param_2[0x69] = auVar51._8_8_;
                param_2[0x68] = auVar51._0_8_;
                pfVar39 = (float *)param_2[0x6d];
                pfVar39[2] = fVar63;
                pfVar39[3] = fVar76;
                *pfVar39 = fVar49;
                pfVar39[1] = fVar62;
                pfVar39[4] = fVar47 * fVar48;
                pfVar39[5] = fVar47 * fVar77;
                pfVar39[6] = fVar5;
                param_2[0x6d] =
                     param_2[0x6d] + (ulong)*(ushort *)(*(long *)(param_2[0x6b] + 0x18) + 0x18);
                *(int *)((long)param_2 + 0x374) = *(int *)((long)param_2 + 0x374) + 1;
              }
              iVar45 = iVar45 + 1;
            } while (param_5 != iVar45);
          }
          else {
            fVar49 = fStack_d4 + fVar49;
            do {
              fVar77 = (((float)iVar45 + (float)iVar45) * fVar36) / fVar75;
              fVar48 = (float)cosf(fVar77);
              fVar77 = (float)sinf(fVar77);
              if (param_2[0x6b] != 0) {
                auVar51 = *(undefined1 (*) [16])(param_2 + 0x66);
                fVar62 = fVar47 * fVar48 * param_1;
                fVar63 = fVar47 * fVar77 * param_1;
                auVar56._4_4_ = fVar62;
                auVar56._0_4_ = fVar49;
                auVar56._8_4_ = fVar63;
                auVar56._12_4_ = uStack_c4;
                fVar78 = fVar49 * fVar49;
                fVar79 = fVar62 * fVar62;
                auVar64 = NEON_fmax(auVar56,auVar51,4);
                param_2[0x67] = auVar64._8_8_;
                param_2[0x66] = auVar64._0_8_;
                auVar21._4_4_ = fVar79;
                auVar21._0_4_ = fVar78;
                auVar21._8_4_ = fVar63 * fVar63;
                auVar21._12_4_ = 0;
                auVar22._4_4_ = fVar79;
                auVar22._0_4_ = fVar78;
                auVar22._8_4_ = fVar63 * fVar63;
                auVar22._12_4_ = 0;
                auVar64 = NEON_ext(auVar21,auVar22,8,1);
                uVar29 = NEON_rev64(CONCAT44(auVar64._0_4_ + auVar64._4_4_,fVar78 + fVar79),4);
                auVar70._0_4_ = fVar78 + fVar79 + (float)uVar29;
                auVar70._4_4_ = auVar70._0_4_;
                auVar70._8_4_ = auVar70._0_4_;
                auVar70._12_4_ = auVar70._0_4_;
                auVar64 = NEON_fmax(auVar70,auVar51,4);
                auVar51 = NEON_fmin(auVar56,*(undefined1 (*) [16])(param_2 + 0x68),4);
                *(int *)((long)param_2 + 0x33c) = auVar64._12_4_;
                param_2[0x69] = auVar51._8_8_;
                param_2[0x68] = auVar51._0_8_;
                pfVar39 = (float *)param_2[0x6d];
                pfVar39[2] = fVar63;
                pfVar39[3] = fVar76;
                *pfVar39 = fVar49;
                pfVar39[1] = fVar62;
                pfVar39[4] = fVar47 * fVar48;
                pfVar39[5] = fVar47 * fVar77;
                pfVar39[6] = fVar5;
                param_2[0x6d] =
                     param_2[0x6d] + (ulong)*(ushort *)(*(long *)(param_2[0x6b] + 0x18) + 0x18);
                *(int *)((long)param_2 + 0x374) = *(int *)((long)param_2 + 0x374) + 1;
              }
              iVar45 = iVar45 + 1;
            } while (param_5 != iVar45);
          }
        }
        if ((fVar76 == 0.0) && (0 < param_5)) {
          iVar45 = 0;
          fVar49 = fStack_d4 + fVar76 * param_1;
          do {
            fVar77 = (((float)iVar45 + (float)iVar45) * fVar36) / fVar75;
            fVar48 = (float)cosf(fVar77);
            fVar77 = (float)sinf(fVar77);
            if (param_2[0x6b] != 0) {
              auVar51 = *(undefined1 (*) [16])(param_2 + 0x66);
              fVar62 = fVar47 * fVar48 * param_1;
              fVar63 = fVar47 * fVar77 * param_1;
              auVar58._4_4_ = fVar62;
              auVar58._0_4_ = fVar49;
              auVar58._8_4_ = fVar63;
              auVar58._12_4_ = 0x3f800000;
              fVar78 = fVar49 * fVar49;
              fVar79 = fVar62 * fVar62;
              auVar64 = NEON_fmax(auVar58,auVar51,4);
              param_2[0x67] = auVar64._8_8_;
              param_2[0x66] = auVar64._0_8_;
              auVar23._4_4_ = fVar79;
              auVar23._0_4_ = fVar78;
              auVar23._8_4_ = fVar63 * fVar63;
              auVar23._12_4_ = 0;
              auVar24._4_4_ = fVar79;
              auVar24._0_4_ = fVar78;
              auVar24._8_4_ = fVar63 * fVar63;
              auVar24._12_4_ = 0;
              auVar64 = NEON_ext(auVar23,auVar24,8,1);
              uVar29 = NEON_rev64(CONCAT44(auVar64._0_4_ + auVar64._4_4_,fVar78 + fVar79),4);
              auVar72._0_4_ = fVar78 + fVar79 + (float)uVar29;
              auVar72._4_4_ = auVar72._0_4_;
              auVar72._8_4_ = auVar72._0_4_;
              auVar72._12_4_ = auVar72._0_4_;
              auVar64 = NEON_fmax(auVar72,auVar51,4);
              auVar51 = NEON_fmin(auVar58,*(undefined1 (*) [16])(param_2 + 0x68),4);
              *(int *)((long)param_2 + 0x33c) = auVar64._12_4_;
              param_2[0x69] = auVar51._8_8_;
              param_2[0x68] = auVar51._0_8_;
              pfVar39 = (float *)param_2[0x6d];
              pfVar39[2] = fVar63;
              pfVar39[3] = fVar76;
              *pfVar39 = fVar49;
              pfVar39[1] = fVar62;
              pfVar39[4] = fVar47 * fVar48;
              pfVar39[5] = fVar47 * fVar77;
              pfVar39[6] = fVar5;
              param_2[0x6d] =
                   param_2[0x6d] + (ulong)*(ushort *)(*(long *)(param_2[0x6b] + 0x18) + 0x18);
              *(int *)((long)param_2 + 0x374) = *(int *)((long)param_2 + 0x374) + 1;
            }
            iVar45 = iVar45 + 1;
          } while (param_5 != iVar45);
        }
        if (((param_6 & 1) == 0) && (uVar44 == uVar1)) {
          fVar47 = (float)cosf(fVar46);
          fVar76 = (float)sinf(fVar46);
          if (0 < param_5) {
            fVar49 = fVar76 * param_1;
            iVar45 = 0;
            do {
              fVar77 = (((float)iVar45 + (float)iVar45) * fVar36) / fVar75;
              fVar48 = (float)cosf(fVar77);
              fVar77 = (float)sinf(fVar77);
              if (param_2[0x6b] != 0) {
                auVar51 = *(undefined1 (*) [16])(param_2 + 0x66);
                fVar62 = fVar47 * fVar48 * param_1;
                fVar63 = fVar47 * fVar77 * param_1;
                auVar59._4_4_ = fVar62;
                auVar59._0_4_ = fVar49;
                auVar59._8_4_ = fVar63;
                auVar59._12_4_ = 0x3f800000;
                fVar78 = fVar49 * fVar49;
                fVar79 = fVar62 * fVar62;
                auVar64 = NEON_fmax(auVar59,auVar51,4);
                param_2[0x67] = auVar64._8_8_;
                param_2[0x66] = auVar64._0_8_;
                auVar25._4_4_ = fVar79;
                auVar25._0_4_ = fVar78;
                auVar25._8_4_ = fVar63 * fVar63;
                auVar25._12_4_ = 0;
                auVar26._4_4_ = fVar79;
                auVar26._0_4_ = fVar78;
                auVar26._8_4_ = fVar63 * fVar63;
                auVar26._12_4_ = 0;
                auVar64 = NEON_ext(auVar25,auVar26,8,1);
                uVar29 = NEON_rev64(CONCAT44(auVar64._0_4_ + auVar64._4_4_,fVar78 + fVar79),4);
                auVar73._0_4_ = fVar78 + fVar79 + (float)uVar29;
                auVar73._4_4_ = auVar73._0_4_;
                auVar73._8_4_ = auVar73._0_4_;
                auVar73._12_4_ = auVar73._0_4_;
                auVar64 = NEON_fmax(auVar73,auVar51,4);
                auVar51 = NEON_fmin(auVar59,*(undefined1 (*) [16])(param_2 + 0x68),4);
                *(int *)((long)param_2 + 0x33c) = auVar64._12_4_;
                param_2[0x69] = auVar51._8_8_;
                param_2[0x68] = auVar51._0_8_;
                pfVar39 = (float *)param_2[0x6d];
                pfVar39[2] = fVar63;
                pfVar39[3] = fVar76;
                *pfVar39 = fVar49;
                pfVar39[1] = fVar62;
                pfVar39[4] = fVar47 * fVar48;
                pfVar39[5] = fVar47 * fVar77;
                pfVar39[6] = fVar5;
                param_2[0x6d] =
                     param_2[0x6d] + (ulong)*(ushort *)(*(long *)(param_2[0x6b] + 0x18) + 0x18);
                *(int *)((long)param_2 + 0x374) = *(int *)((long)param_2 + 0x374) + 1;
              }
              iVar45 = iVar45 + 1;
            } while (param_5 != iVar45);
            if (0 < param_5) {
              iVar45 = 0;
              fVar49 = fStack_d4 + fVar49;
              do {
                fVar77 = (((float)iVar45 + (float)iVar45) * fVar36) / fVar75;
                fVar48 = (float)cosf(fVar77);
                fVar77 = (float)sinf(fVar77);
                if (param_2[0x6b] != 0) {
                  auVar51 = *(undefined1 (*) [16])(param_2 + 0x66);
                  fVar62 = fVar47 * fVar48 * param_1;
                  fVar63 = fVar47 * fVar77 * param_1;
                  auVar60._4_4_ = fVar62;
                  auVar60._0_4_ = fVar49;
                  auVar60._8_4_ = fVar63;
                  auVar60._12_4_ = 0x3f800000;
                  fVar78 = fVar49 * fVar49;
                  fVar79 = fVar62 * fVar62;
                  auVar64 = NEON_fmax(auVar60,auVar51,4);
                  param_2[0x67] = auVar64._8_8_;
                  param_2[0x66] = auVar64._0_8_;
                  auVar27._4_4_ = fVar79;
                  auVar27._0_4_ = fVar78;
                  auVar27._8_4_ = fVar63 * fVar63;
                  auVar27._12_4_ = 0;
                  auVar28._4_4_ = fVar79;
                  auVar28._0_4_ = fVar78;
                  auVar28._8_4_ = fVar63 * fVar63;
                  auVar28._12_4_ = 0;
                  auVar64 = NEON_ext(auVar27,auVar28,8,1);
                  uVar29 = NEON_rev64(CONCAT44(auVar64._0_4_ + auVar64._4_4_,fVar78 + fVar79),4);
                  auVar74._0_4_ = fVar78 + fVar79 + (float)uVar29;
                  auVar74._4_4_ = auVar74._0_4_;
                  auVar74._8_4_ = auVar74._0_4_;
                  auVar74._12_4_ = auVar74._0_4_;
                  auVar64 = NEON_fmax(auVar74,auVar51,4);
                  auVar51 = NEON_fmin(auVar60,*(undefined1 (*) [16])(param_2 + 0x68),4);
                  *(int *)((long)param_2 + 0x33c) = auVar64._12_4_;
                  param_2[0x69] = auVar51._8_8_;
                  param_2[0x68] = auVar51._0_8_;
                  pfVar39 = (float *)param_2[0x6d];
                  pfVar39[2] = fVar63;
                  pfVar39[3] = fVar76;
                  *pfVar39 = fVar49;
                  pfVar39[1] = fVar62;
                  pfVar39[4] = fVar47 * fVar48;
                  pfVar39[5] = fVar47 * fVar77;
                  pfVar39[6] = fVar5;
                  param_2[0x6d] =
                       param_2[0x6d] + (ulong)*(ushort *)(*(long *)(param_2[0x6b] + 0x18) + 0x18);
                  *(int *)((long)param_2 + 0x374) = *(int *)((long)param_2 + 0x374) + 1;
                }
                iVar45 = iVar45 + 1;
              } while (param_5 != iVar45);
            }
          }
        }
        uVar44 = uVar44 + 1;
      } while (uVar44 != param_6);
      if (1 < (int)param_6) {
        iVar45 = 0;
        uVar44 = 0;
        do {
          if (0 < param_5) {
            sVar32 = (short)uVar44;
            sVar33 = sVar32 + (short)iVar45;
            iVar42 = 0;
            sVar30 = sVar33 * sVar35;
            sVar31 = (sVar32 + 1) * sVar35;
            sVar34 = (sVar32 + 2) * sVar35;
            sVar33 = (sVar33 + 1) * sVar35;
            sVar32 = (sVar32 + 3) * sVar35;
            do {
              sVar9 = 0;
              sVar4 = (short)iVar42;
              if (iVar42 - param_5 != -1) {
                sVar9 = sVar4 + 1;
              }
              if (param_2[0x6b] != 0) {
                psVar43 = (short *)param_2[0x6c];
                param_2[0x6c] = (long)(psVar43 + 1);
                *psVar43 = sVar9 + sVar30;
                psVar43 = (short *)param_2[0x6c];
                sVar6 = sVar30 + sVar4;
                param_2[0x6c] = (long)(psVar43 + 1);
                *psVar43 = sVar6;
                psVar43 = (short *)param_2[0x6c];
                sVar7 = sVar9 + sVar33;
                param_2[0x6c] = (long)(psVar43 + 1);
                *psVar43 = sVar7;
                *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 3;
                if (param_2[0x6b] != 0) {
                  psVar43 = (short *)param_2[0x6c];
                  param_2[0x6c] = (long)(psVar43 + 1);
                  *psVar43 = sVar6;
                  psVar43 = (short *)param_2[0x6c];
                  param_2[0x6c] = (long)(psVar43 + 1);
                  *psVar43 = sVar33 + sVar4;
                  psVar43 = (short *)param_2[0x6c];
                  param_2[0x6c] = (long)(psVar43 + 1);
                  *psVar43 = sVar7;
                  *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 3;
                }
              }
              iVar42 = iVar42 + 1;
              if (uVar44 == uVar1) {
                sVar6 = sVar34 + sVar4;
                sVar7 = sVar9 + sVar34;
                if (param_2[0x6b] != 0) {
                  psVar43 = (short *)param_2[0x6c];
                  param_2[0x6c] = (long)(psVar43 + 1);
                  *psVar43 = sVar9 + sVar31;
                  psVar43 = (short *)param_2[0x6c];
                  sVar8 = sVar31 + sVar4;
                  param_2[0x6c] = (long)(psVar43 + 1);
                  *psVar43 = sVar8;
                  psVar43 = (short *)param_2[0x6c];
                  param_2[0x6c] = (long)(psVar43 + 1);
                  *psVar43 = sVar7;
                  *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 3;
                  if (param_2[0x6b] != 0) {
                    psVar43 = (short *)param_2[0x6c];
                    param_2[0x6c] = (long)(psVar43 + 1);
                    *psVar43 = sVar8;
                    psVar43 = (short *)param_2[0x6c];
                    param_2[0x6c] = (long)(psVar43 + 1);
                    *psVar43 = sVar6;
                    psVar43 = (short *)param_2[0x6c];
                    param_2[0x6c] = (long)(psVar43 + 1);
                    *psVar43 = sVar7;
                    *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 3;
                  }
                }
                if (((param_6 & 1) == 0) && (param_2[0x6b] != 0)) {
                  psVar43 = (short *)param_2[0x6c];
                  sVar9 = sVar9 + sVar32;
                  param_2[0x6c] = (long)(psVar43 + 1);
                  *psVar43 = sVar7;
                  psVar43 = (short *)param_2[0x6c];
                  param_2[0x6c] = (long)(psVar43 + 1);
                  *psVar43 = sVar6;
                  psVar43 = (short *)param_2[0x6c];
                  param_2[0x6c] = (long)(psVar43 + 1);
                  *psVar43 = sVar9;
                  *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 3;
                  if (param_2[0x6b] != 0) {
                    psVar43 = (short *)param_2[0x6c];
                    param_2[0x6c] = (long)(psVar43 + 1);
                    *psVar43 = sVar6;
                    psVar43 = (short *)param_2[0x6c];
                    param_2[0x6c] = (long)(psVar43 + 1);
                    *psVar43 = sVar32 + sVar4;
                    psVar43 = (short *)param_2[0x6c];
                    param_2[0x6c] = (long)(psVar43 + 1);
                    *psVar43 = sVar9;
                    *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 3;
                  }
                }
              }
            } while (iVar42 != param_5);
          }
          uVar41 = uVar44 + 1;
          uVar2 = param_6 | 0xfffffffe;
          if (uVar44 != uVar1) {
            uVar2 = 0;
          }
          iVar45 = iVar45 - uVar2;
          uVar44 = uVar41;
        } while (uVar41 != uVar10);
      }
    }
  }
  else {
    uVar37 = Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)(param_2,param_3,iVar45,iVar45 * 8);
    fVar36 = _UNK_027e3fd0;
    if ((uVar37 & 1) == 0) goto code_r0x0220a7fc;
    uVar10 = param_6 - 1;
    if (0 < (int)param_6) {
      uVar44 = param_6;
      if (-1 < (int)uVar10) {
        uVar44 = uVar10;
      }
      auVar61 = NEON_fmov(0x3f800000,4);
      fVar46 = ((((float)((int)uVar44 >> 1) - (float)(int)uVar10 * 0.5) + 0.5) * _UNK_027e3fd0) /
               (float)(int)(param_6 - 2);
      uVar44 = 0;
      fVar75 = (float)param_5;
      fVar5 = (float)(param_7 >> 0x10 & 0xff | param_7 & 0xff00ff00 | (param_7 & 0xff) << 0x10);
      do {
        fVar76 = ((((float)(int)uVar44 - (float)(int)param_6 * 0.5) + 0.5) * fVar36) /
                 (float)(int)uVar10;
        fVar47 = (float)cosf(fVar76);
        fVar76 = (float)sinf(fVar76);
        if (0 < param_5) {
          fVar49 = fVar76 * param_1;
          iVar45 = 0;
          uStack_c4 = auVar61._12_4_;
          if (fVar76 <= 0.0) {
            do {
              fVar77 = (((float)iVar45 + (float)iVar45) * fVar36) / fVar75;
              fVar48 = (float)cosf(fVar77);
              fVar77 = (float)sinf(fVar77);
              if (param_2[0x6b] != 0) {
                auVar51 = *(undefined1 (*) [16])(param_2 + 0x66);
                fVar62 = fVar47 * fVar48 * param_1;
                fVar63 = fVar47 * fVar77 * param_1;
                auVar52._4_4_ = fVar62;
                auVar52._0_4_ = fVar49;
                auVar52._8_4_ = fVar63;
                auVar52._12_4_ = uStack_c4;
                fVar78 = fVar49 * fVar49;
                fVar79 = fVar62 * fVar62;
                auVar64 = NEON_fmax(auVar52,auVar51,4);
                param_2[0x67] = auVar64._8_8_;
                param_2[0x66] = auVar64._0_8_;
                auVar19._4_4_ = fVar79;
                auVar19._0_4_ = fVar78;
                auVar19._8_4_ = fVar63 * fVar63;
                auVar19._12_4_ = 0;
                auVar20._4_4_ = fVar79;
                auVar20._0_4_ = fVar78;
                auVar20._8_4_ = fVar63 * fVar63;
                auVar20._12_4_ = 0;
                auVar64 = NEON_ext(auVar19,auVar20,8,1);
                uVar29 = NEON_rev64(CONCAT44(auVar64._0_4_ + auVar64._4_4_,fVar78 + fVar79),4);
                auVar66._0_4_ = fVar78 + fVar79 + (float)uVar29;
                auVar66._4_4_ = auVar66._0_4_;
                auVar66._8_4_ = auVar66._0_4_;
                auVar66._12_4_ = auVar66._0_4_;
                auVar64 = NEON_fmax(auVar66,auVar51,4);
                auVar51 = NEON_fmin(auVar52,*(undefined1 (*) [16])(param_2 + 0x68),4);
                *(int *)((long)param_2 + 0x33c) = auVar64._12_4_;
                param_2[0x69] = auVar51._8_8_;
                param_2[0x68] = auVar51._0_8_;
                pfVar39 = (float *)param_2[0x6d];
                pfVar39[2] = fVar63;
                pfVar39[3] = fVar76;
                *pfVar39 = fVar49;
                pfVar39[1] = fVar62;
                pfVar39[4] = fVar47 * fVar48;
                pfVar39[5] = fVar47 * fVar77;
                pfVar39[6] = fVar5;
                param_2[0x6d] =
                     param_2[0x6d] + (ulong)*(ushort *)(*(long *)(param_2[0x6b] + 0x18) + 0x18);
                *(int *)((long)param_2 + 0x374) = *(int *)((long)param_2 + 0x374) + 1;
              }
              iVar45 = iVar45 + 1;
            } while (param_5 != iVar45);
          }
          else {
            fVar49 = fStack_d4 + fVar49;
            do {
              fVar77 = (((float)iVar45 + (float)iVar45) * fVar36) / fVar75;
              fVar48 = (float)cosf(fVar77);
              fVar77 = (float)sinf(fVar77);
              if (param_2[0x6b] != 0) {
                auVar51 = *(undefined1 (*) [16])(param_2 + 0x66);
                fVar62 = fVar47 * fVar48 * param_1;
                fVar63 = fVar47 * fVar77 * param_1;
                auVar50._4_4_ = fVar62;
                auVar50._0_4_ = fVar49;
                auVar50._8_4_ = fVar63;
                auVar50._12_4_ = uStack_c4;
                fVar78 = fVar49 * fVar49;
                fVar79 = fVar62 * fVar62;
                auVar64 = NEON_fmax(auVar50,auVar51,4);
                param_2[0x67] = auVar64._8_8_;
                param_2[0x66] = auVar64._0_8_;
                auVar11._4_4_ = fVar79;
                auVar11._0_4_ = fVar78;
                auVar11._8_4_ = fVar63 * fVar63;
                auVar11._12_4_ = 0;
                auVar12._4_4_ = fVar79;
                auVar12._0_4_ = fVar78;
                auVar12._8_4_ = fVar63 * fVar63;
                auVar12._12_4_ = 0;
                auVar64 = NEON_ext(auVar11,auVar12,8,1);
                uVar29 = NEON_rev64(CONCAT44(auVar64._0_4_ + auVar64._4_4_,fVar78 + fVar79),4);
                auVar65._0_4_ = fVar78 + fVar79 + (float)uVar29;
                auVar65._4_4_ = auVar65._0_4_;
                auVar65._8_4_ = auVar65._0_4_;
                auVar65._12_4_ = auVar65._0_4_;
                auVar64 = NEON_fmax(auVar65,auVar51,4);
                auVar51 = NEON_fmin(auVar50,*(undefined1 (*) [16])(param_2 + 0x68),4);
                *(int *)((long)param_2 + 0x33c) = auVar64._12_4_;
                param_2[0x69] = auVar51._8_8_;
                param_2[0x68] = auVar51._0_8_;
                pfVar39 = (float *)param_2[0x6d];
                pfVar39[2] = fVar63;
                pfVar39[3] = fVar76;
                *pfVar39 = fVar49;
                pfVar39[1] = fVar62;
                pfVar39[4] = fVar47 * fVar48;
                pfVar39[5] = fVar47 * fVar77;
                pfVar39[6] = fVar5;
                param_2[0x6d] =
                     param_2[0x6d] + (ulong)*(ushort *)(*(long *)(param_2[0x6b] + 0x18) + 0x18);
                *(int *)((long)param_2 + 0x374) = *(int *)((long)param_2 + 0x374) + 1;
              }
              iVar45 = iVar45 + 1;
            } while (param_5 != iVar45);
          }
        }
        if ((fVar76 == 0.0) && (0 < param_5)) {
          iVar45 = 0;
          fVar49 = fStack_d4 + fVar76 * param_1;
          do {
            fVar77 = (((float)iVar45 + (float)iVar45) * fVar36) / fVar75;
            fVar48 = (float)cosf(fVar77);
            fVar77 = (float)sinf(fVar77);
            if (param_2[0x6b] != 0) {
              auVar51 = *(undefined1 (*) [16])(param_2 + 0x66);
              fVar62 = fVar47 * fVar48 * param_1;
              fVar63 = fVar47 * fVar77 * param_1;
              auVar53._4_4_ = fVar62;
              auVar53._0_4_ = fVar49;
              auVar53._8_4_ = fVar63;
              auVar53._12_4_ = 0x3f800000;
              fVar78 = fVar49 * fVar49;
              fVar79 = fVar62 * fVar62;
              auVar64 = NEON_fmax(auVar53,auVar51,4);
              param_2[0x67] = auVar64._8_8_;
              param_2[0x66] = auVar64._0_8_;
              auVar13._4_4_ = fVar79;
              auVar13._0_4_ = fVar78;
              auVar13._8_4_ = fVar63 * fVar63;
              auVar13._12_4_ = 0;
              auVar14._4_4_ = fVar79;
              auVar14._0_4_ = fVar78;
              auVar14._8_4_ = fVar63 * fVar63;
              auVar14._12_4_ = 0;
              auVar64 = NEON_ext(auVar13,auVar14,8,1);
              uVar29 = NEON_rev64(CONCAT44(auVar64._0_4_ + auVar64._4_4_,fVar78 + fVar79),4);
              auVar67._0_4_ = fVar78 + fVar79 + (float)uVar29;
              auVar67._4_4_ = auVar67._0_4_;
              auVar67._8_4_ = auVar67._0_4_;
              auVar67._12_4_ = auVar67._0_4_;
              auVar64 = NEON_fmax(auVar67,auVar51,4);
              auVar51 = NEON_fmin(auVar53,*(undefined1 (*) [16])(param_2 + 0x68),4);
              *(int *)((long)param_2 + 0x33c) = auVar64._12_4_;
              param_2[0x69] = auVar51._8_8_;
              param_2[0x68] = auVar51._0_8_;
              pfVar39 = (float *)param_2[0x6d];
              pfVar39[2] = fVar63;
              pfVar39[3] = fVar76;
              *pfVar39 = fVar49;
              pfVar39[1] = fVar62;
              pfVar39[4] = fVar47 * fVar48;
              pfVar39[5] = fVar47 * fVar77;
              pfVar39[6] = fVar5;
              param_2[0x6d] =
                   param_2[0x6d] + (ulong)*(ushort *)(*(long *)(param_2[0x6b] + 0x18) + 0x18);
              *(int *)((long)param_2 + 0x374) = *(int *)((long)param_2 + 0x374) + 1;
            }
            iVar45 = iVar45 + 1;
          } while (param_5 != iVar45);
        }
        if (((param_6 & 1) == 0) && (uVar44 == uVar1)) {
          fVar47 = (float)cosf(fVar46);
          fVar76 = (float)sinf(fVar46);
          if (0 < param_5) {
            fVar49 = fVar76 * param_1;
            iVar45 = 0;
            do {
              fVar77 = (((float)iVar45 + (float)iVar45) * fVar36) / fVar75;
              fVar48 = (float)cosf(fVar77);
              fVar77 = (float)sinf(fVar77);
              if (param_2[0x6b] != 0) {
                auVar51 = *(undefined1 (*) [16])(param_2 + 0x66);
                fVar62 = fVar47 * fVar48 * param_1;
                fVar63 = fVar47 * fVar77 * param_1;
                auVar54._4_4_ = fVar62;
                auVar54._0_4_ = fVar49;
                auVar54._8_4_ = fVar63;
                auVar54._12_4_ = 0x3f800000;
                fVar78 = fVar49 * fVar49;
                fVar79 = fVar62 * fVar62;
                auVar64 = NEON_fmax(auVar54,auVar51,4);
                param_2[0x67] = auVar64._8_8_;
                param_2[0x66] = auVar64._0_8_;
                auVar15._4_4_ = fVar79;
                auVar15._0_4_ = fVar78;
                auVar15._8_4_ = fVar63 * fVar63;
                auVar15._12_4_ = 0;
                auVar16._4_4_ = fVar79;
                auVar16._0_4_ = fVar78;
                auVar16._8_4_ = fVar63 * fVar63;
                auVar16._12_4_ = 0;
                auVar64 = NEON_ext(auVar15,auVar16,8,1);
                uVar29 = NEON_rev64(CONCAT44(auVar64._0_4_ + auVar64._4_4_,fVar78 + fVar79),4);
                auVar68._0_4_ = fVar78 + fVar79 + (float)uVar29;
                auVar68._4_4_ = auVar68._0_4_;
                auVar68._8_4_ = auVar68._0_4_;
                auVar68._12_4_ = auVar68._0_4_;
                auVar64 = NEON_fmax(auVar68,auVar51,4);
                auVar51 = NEON_fmin(auVar54,*(undefined1 (*) [16])(param_2 + 0x68),4);
                *(int *)((long)param_2 + 0x33c) = auVar64._12_4_;
                param_2[0x69] = auVar51._8_8_;
                param_2[0x68] = auVar51._0_8_;
                pfVar39 = (float *)param_2[0x6d];
                pfVar39[2] = fVar63;
                pfVar39[3] = fVar76;
                *pfVar39 = fVar49;
                pfVar39[1] = fVar62;
                pfVar39[4] = fVar47 * fVar48;
                pfVar39[5] = fVar47 * fVar77;
                pfVar39[6] = fVar5;
                param_2[0x6d] =
                     param_2[0x6d] + (ulong)*(ushort *)(*(long *)(param_2[0x6b] + 0x18) + 0x18);
                *(int *)((long)param_2 + 0x374) = *(int *)((long)param_2 + 0x374) + 1;
              }
              iVar45 = iVar45 + 1;
            } while (param_5 != iVar45);
            if (0 < param_5) {
              iVar45 = 0;
              fVar49 = fStack_d4 + fVar49;
              do {
                fVar77 = (((float)iVar45 + (float)iVar45) * fVar36) / fVar75;
                fVar48 = (float)cosf(fVar77);
                fVar77 = (float)sinf(fVar77);
                if (param_2[0x6b] != 0) {
                  auVar51 = *(undefined1 (*) [16])(param_2 + 0x66);
                  fVar62 = fVar47 * fVar48 * param_1;
                  fVar63 = fVar47 * fVar77 * param_1;
                  auVar55._4_4_ = fVar62;
                  auVar55._0_4_ = fVar49;
                  auVar55._8_4_ = fVar63;
                  auVar55._12_4_ = 0x3f800000;
                  fVar78 = fVar49 * fVar49;
                  fVar79 = fVar62 * fVar62;
                  auVar64 = NEON_fmax(auVar55,auVar51,4);
                  param_2[0x67] = auVar64._8_8_;
                  param_2[0x66] = auVar64._0_8_;
                  auVar17._4_4_ = fVar79;
                  auVar17._0_4_ = fVar78;
                  auVar17._8_4_ = fVar63 * fVar63;
                  auVar17._12_4_ = 0;
                  auVar18._4_4_ = fVar79;
                  auVar18._0_4_ = fVar78;
                  auVar18._8_4_ = fVar63 * fVar63;
                  auVar18._12_4_ = 0;
                  auVar64 = NEON_ext(auVar17,auVar18,8,1);
                  uVar29 = NEON_rev64(CONCAT44(auVar64._0_4_ + auVar64._4_4_,fVar78 + fVar79),4);
                  auVar69._0_4_ = fVar78 + fVar79 + (float)uVar29;
                  auVar69._4_4_ = auVar69._0_4_;
                  auVar69._8_4_ = auVar69._0_4_;
                  auVar69._12_4_ = auVar69._0_4_;
                  auVar64 = NEON_fmax(auVar69,auVar51,4);
                  auVar51 = NEON_fmin(auVar55,*(undefined1 (*) [16])(param_2 + 0x68),4);
                  *(int *)((long)param_2 + 0x33c) = auVar64._12_4_;
                  param_2[0x69] = auVar51._8_8_;
                  param_2[0x68] = auVar51._0_8_;
                  pfVar39 = (float *)param_2[0x6d];
                  pfVar39[2] = fVar63;
                  pfVar39[3] = fVar76;
                  *pfVar39 = fVar49;
                  pfVar39[1] = fVar62;
                  pfVar39[4] = fVar47 * fVar48;
                  pfVar39[5] = fVar47 * fVar77;
                  pfVar39[6] = fVar5;
                  param_2[0x6d] =
                       param_2[0x6d] + (ulong)*(ushort *)(*(long *)(param_2[0x6b] + 0x18) + 0x18);
                  *(int *)((long)param_2 + 0x374) = *(int *)((long)param_2 + 0x374) + 1;
                }
                iVar45 = iVar45 + 1;
              } while (param_5 != iVar45);
            }
          }
        }
        uVar44 = uVar44 + 1;
      } while (uVar44 != param_6);
      if (1 < (int)param_6) {
        iVar45 = 0;
        uVar44 = 0;
        do {
          if (0 < param_5) {
            sVar32 = (short)uVar44;
            sVar33 = (short)iVar45 + sVar32;
            iVar42 = 0;
            sVar30 = sVar33 * sVar35;
            sVar31 = (sVar32 + 1) * sVar35;
            sVar34 = (sVar32 + 2) * sVar35;
            sVar33 = (sVar33 + 1) * sVar35;
            sVar32 = (sVar32 + 3) * sVar35;
            do {
              sVar9 = (short)iVar42;
              if (param_2[0x6b] == 0) {
                sVar4 = 0;
                if (param_5 != 0) {
                  sVar4 = (short)((iVar42 + 1) / param_5);
                }
                sVar4 = (short)(iVar42 + 1) - sVar4 * sVar35;
              }
              else {
                psVar43 = (short *)param_2[0x6c];
                sVar6 = sVar9 + sVar30;
                sVar7 = sVar9 + sVar33;
                param_2[0x6c] = (long)(psVar43 + 1);
                *psVar43 = sVar6;
                psVar43 = (short *)param_2[0x6c];
                param_2[0x6c] = (long)(psVar43 + 1);
                *psVar43 = sVar7;
                *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 2;
                sVar4 = 0;
                if (param_5 != 0) {
                  sVar4 = (short)((iVar42 + 1) / param_5);
                }
                sVar4 = (short)(iVar42 + 1) - sVar4 * sVar35;
                if (param_2[0x6b] != 0) {
                  psVar43 = (short *)param_2[0x6c];
                  sVar8 = sVar4 + sVar30;
                  param_2[0x6c] = (long)(psVar43 + 1);
                  *psVar43 = sVar8;
                  psVar43 = (short *)param_2[0x6c];
                  param_2[0x6c] = (long)(psVar43 + 1);
                  *psVar43 = sVar6;
                  *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 2;
                  if (param_2[0x6b] != 0) {
                    psVar43 = (short *)param_2[0x6c];
                    param_2[0x6c] = (long)(psVar43 + 1);
                    *psVar43 = sVar7;
                    psVar43 = (short *)param_2[0x6c];
                    sVar6 = sVar4 + sVar33;
                    param_2[0x6c] = (long)(psVar43 + 1);
                    *psVar43 = sVar6;
                    *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 2;
                    if (param_2[0x6b] != 0) {
                      psVar43 = (short *)param_2[0x6c];
                      param_2[0x6c] = (long)(psVar43 + 1);
                      *psVar43 = sVar6;
                      psVar43 = (short *)param_2[0x6c];
                      param_2[0x6c] = (long)(psVar43 + 1);
                      *psVar43 = sVar8;
                      *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 2;
                    }
                  }
                }
              }
              if (uVar44 == uVar1) {
                sVar6 = sVar9 + sVar34;
                if (param_2[0x6b] != 0) {
                  psVar43 = (short *)param_2[0x6c];
                  sVar7 = sVar9 + sVar31;
                  param_2[0x6c] = (long)(psVar43 + 1);
                  *psVar43 = sVar7;
                  psVar43 = (short *)param_2[0x6c];
                  param_2[0x6c] = (long)(psVar43 + 1);
                  *psVar43 = sVar6;
                  *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 2;
                  if (param_2[0x6b] != 0) {
                    psVar43 = (short *)param_2[0x6c];
                    sVar8 = sVar4 + sVar31;
                    param_2[0x6c] = (long)(psVar43 + 1);
                    *psVar43 = sVar8;
                    psVar43 = (short *)param_2[0x6c];
                    param_2[0x6c] = (long)(psVar43 + 1);
                    *psVar43 = sVar7;
                    *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 2;
                    if (param_2[0x6b] != 0) {
                      psVar43 = (short *)param_2[0x6c];
                      param_2[0x6c] = (long)(psVar43 + 1);
                      *psVar43 = sVar6;
                      psVar43 = (short *)param_2[0x6c];
                      param_2[0x6c] = (long)(psVar43 + 1);
                      *psVar43 = sVar4 + sVar34;
                      *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 2;
                      if (param_2[0x6b] != 0) {
                        psVar43 = (short *)param_2[0x6c];
                        param_2[0x6c] = (long)(psVar43 + 1);
                        *psVar43 = sVar4 + sVar34;
                        psVar43 = (short *)param_2[0x6c];
                        param_2[0x6c] = (long)(psVar43 + 1);
                        *psVar43 = sVar8;
                        *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 2;
                      }
                    }
                  }
                }
                if (((param_6 & 1) == 0) && (param_2[0x6b] != 0)) {
                  psVar43 = (short *)param_2[0x6c];
                  sVar9 = sVar9 + sVar32;
                  param_2[0x6c] = (long)(psVar43 + 1);
                  *psVar43 = sVar6;
                  psVar43 = (short *)param_2[0x6c];
                  param_2[0x6c] = (long)(psVar43 + 1);
                  *psVar43 = sVar9;
                  *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 2;
                  if (param_2[0x6b] != 0) {
                    psVar43 = (short *)param_2[0x6c];
                    param_2[0x6c] = (long)(psVar43 + 1);
                    *psVar43 = sVar4 + sVar34;
                    psVar43 = (short *)param_2[0x6c];
                    param_2[0x6c] = (long)(psVar43 + 1);
                    *psVar43 = sVar6;
                    *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 2;
                    if (param_2[0x6b] != 0) {
                      psVar43 = (short *)param_2[0x6c];
                      sVar6 = sVar4 + sVar32;
                      param_2[0x6c] = (long)(psVar43 + 1);
                      *psVar43 = sVar9;
                      psVar43 = (short *)param_2[0x6c];
                      param_2[0x6c] = (long)(psVar43 + 1);
                      *psVar43 = sVar6;
                      *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 2;
                      if (param_2[0x6b] != 0) {
                        psVar43 = (short *)param_2[0x6c];
                        param_2[0x6c] = (long)(psVar43 + 1);
                        *psVar43 = sVar6;
                        psVar43 = (short *)param_2[0x6c];
                        param_2[0x6c] = (long)(psVar43 + 1);
                        *psVar43 = sVar4 + sVar34;
                        *(int *)(param_2 + 0x6e) = (int)param_2[0x6e] + 2;
                      }
                    }
                  }
                }
              }
              iVar42 = iVar42 + 1;
            } while (iVar42 < param_5);
          }
          uVar41 = uVar44 + 1;
          uVar2 = param_6 | 0xfffffffe;
          if (uVar44 != uVar1) {
            uVar2 = 0;
          }
          iVar45 = iVar45 - uVar2;
          uVar44 = uVar41;
        } while (uVar41 != uVar10);
      }
    }
  }
  Aska::DirectAofHandler::EndMesh()(param_2);
  uStack_b0 = 0;
  uStack_a8 = 0;
  fStack_a4 = fStack_d4 + param_1;
  if ((int)param_2[0x19] == 0) {
    bVar38 = *(byte *)(param_2 + 0x15) & 0xfe;
  }
  else {
    lVar40 = param_2[0x16];
    *(undefined4 *)(lVar40 + 0x10) = 0;
    *(undefined8 *)(lVar40 + 0x14) = 0;
    *(float *)(lVar40 + 0x1c) = fStack_a4;
    if (*(byte *)((long)param_2 + 0x353) != *(byte *)((long)param_2 + 0x352)) goto code_r0x0220a7fc;
    *(ushort *)(param_2[0x16] + 0x70) = (ushort)*(byte *)((long)param_2 + 0x353);
    Aska::MaterialList::SetActiveMaterialCount(unsigned char)(param_2 + 0x1d,*(undefined1 *)((long)param_2 + 0x353));
    bVar38 = *(byte *)(param_2 + 0x15) | 1;
  }
  *(byte *)(param_2 + 0x15) = bVar38;
  (**(code **)(*param_2 + 0x78))(param_2,&uStack_b0,0);
code_r0x0220a7fc:
  *(char *)(param_3 + 2) = cVar3;
  return;
}

// ==== Aska::DirectAofHandler::Square(Aska::DirectMaterial*, float, float, int, int, unsigned int)
// vaddr 0x210a830 | ghidra 0x220a830 | size 4248 | symbol _ZN4Aska16DirectAofHandler6SquareEPNS_14DirectMaterialEffiij | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Removing unreachable block (ram,0x0220aec4) */
/* WARNING: Removing unreachable block (ram,0x0220aedc) */
/* WARNING: Removing unreachable block (ram,0x0220aee8) */
/* WARNING: Removing unreachable block (ram,0x0220afa0) */
/* WARNING: Removing unreachable block (ram,0x0220b018) */
/* WARNING: Removing unreachable block (ram,0x0220b0b8) */
/* WARNING: Removing unreachable block (ram,0x0220b130) */
/* WARNING: Removing unreachable block (ram,0x0220b190) */
/* WARNING: Removing unreachable block (ram,0x0220b1a4) */
/* WARNING: Removing unreachable block (ram,0x0220b1ac) */
/* WARNING: Removing unreachable block (ram,0x0220b1b0) */
/* WARNING: Removing unreachable block (ram,0x0220b1e0) */
/* WARNING: Removing unreachable block (ram,0x0220b204) */
/* WARNING: Removing unreachable block (ram,0x0220b208) */
/* WARNING: Removing unreachable block (ram,0x0220b29c) */
/* WARNING: Removing unreachable block (ram,0x0220b2a8) */
/* WARNING: Removing unreachable block (ram,0x0220b2b4) */
/* WARNING: Removing unreachable block (ram,0x0220b2bc) */
/* WARNING: Removing unreachable block (ram,0x0220b2c4) */
/* WARNING: Removing unreachable block (ram,0x0220b2cc) */
/* WARNING: Removing unreachable block (ram,0x0220b2d4) */
/* WARNING: Removing unreachable block (ram,0x0220b2dc) */
/* WARNING: Removing unreachable block (ram,0x0220b33c) */
/* WARNING: Removing unreachable block (ram,0x0220b348) */
/* WARNING: Removing unreachable block (ram,0x0220b358) */

void _ZN4Aska16DirectAofHandler6SquareEPNS_14DirectMaterialEffiij
               (float param_1,float param_2,long param_3,long param_4,int param_5,int param_6,
               uint param_7)

{
  int iVar1;
  char cVar2;
  ushort uVar3;
  short sVar4;
  short sVar5;
  uint uVar6;
  uint uVar7;
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [12];
  short sVar25;
  bool bVar26;
  ulong uVar27;
  int iVar28;
  int iVar29;
  undefined2 *puVar30;
  int iVar31;
  long lVar32;
  float *pfVar33;
  short *psVar34;
  long lVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  undefined1 auVar39 [16];
  undefined1 auVar40 [16];
  float fVar41;
  undefined1 auVar42 [16];
  undefined1 auVar43 [16];
  undefined1 auVar44 [16];
  undefined1 auVar45 [16];
  undefined1 auVar46 [16];
  undefined1 auVar47 [16];
  undefined1 auVar48 [16];
  undefined1 auVar49 [16];
  undefined1 auVar50 [16];
  float fVar51;
  undefined1 auVar52 [16];
  undefined1 auVar53 [16];
  undefined1 auVar54 [16];
  undefined1 auVar55 [16];
  undefined4 uVar56;
  undefined1 auVar57 [16];
  undefined1 auVar58 [16];
  undefined1 auVar59 [16];
  undefined1 auVar60 [16];
  undefined1 auVar61 [16];
  undefined1 auVar62 [16];
  undefined1 auVar63 [16];
  undefined1 auVar64 [16];
  undefined8 uVar65;
  undefined1 auVar66 [16];
  undefined1 auVar67 [16];
  undefined1 auVar68 [16];
  undefined1 auVar69 [16];
  undefined1 auVar70 [16];
  undefined8 uStack_70;
  undefined4 uStack_68;
  float fStack_64;
  
  cVar2 = *(char *)(param_4 + 2);
  bVar26 = cVar2 != '\x02';
  if (bVar26) {
    *(undefined1 *)(param_4 + 2) = 0;
  }
  iVar28 = param_6 * param_5;
  fVar38 = param_1 * 0.5;
  auVar39._0_8_ = CONCAT44(0,fVar38);
  fVar36 = param_2 * 0.5;
  if (iVar28 == 1) {
    if (bVar26) {
      uVar27 = Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)(param_3,param_4,4,6);
      if ((uVar27 & 1) == 0) goto code_r0x0220b8a4;
      if (*(long *)(param_3 + 0x358) != 0) {
        fVar41 = -fVar38;
        uVar56 = (undefined4)((ulong)*(undefined8 *)(param_3 + 0x338) >> 0x20);
        auVar24 = *(undefined1 (*) [12])(param_3 + 0x330);
        fVar37 = -fVar36;
        auVar54._0_8_ = CONCAT44(0,fVar41);
        auVar63._8_4_ = fVar37;
        auVar63._0_8_ = auVar54._0_8_;
        auVar63._12_4_ = 0x3f800000;
        auVar68._0_4_ = fVar41 * fVar41;
        auVar68._4_4_ = 0;
        auVar68._8_4_ = fVar37 * fVar37;
        auVar68._12_4_ = 0;
        auVar15._12_4_ = uVar56;
        auVar15._0_12_ = *(undefined1 (*) [12])(param_3 + 0x330);
        auVar46 = NEON_fmax(auVar63,auVar15,4);
        *(long *)(param_3 + 0x338) = auVar46._8_8_;
        *(long *)(param_3 + 0x330) = auVar46._0_8_;
        auVar46 = NEON_ext(auVar68,auVar68,8,1);
        uVar65 = NEON_rev64(CONCAT44(auVar46._0_4_ + auVar46._4_4_,auVar68._0_4_ + 0.0),4);
        auVar49._0_4_ = auVar68._0_4_ + 0.0 + (float)uVar65;
        auVar49._4_4_ = auVar49._0_4_;
        auVar49._8_4_ = auVar49._0_4_;
        auVar49._12_4_ = auVar49._0_4_;
        auVar16._12_4_ = uVar56;
        auVar16._0_12_ = auVar24;
        auVar46 = NEON_fmax(auVar49,auVar16,4);
        *(undefined4 *)(param_3 + 0x33c) = auVar46._12_4_;
        pfVar33 = *(float **)(param_3 + 0x368);
        uVar7 = param_7 >> 0x10 & 0xff;
        uVar6 = (param_7 & 0xff) << 0x10;
        fVar51 = (float)(uVar7 | param_7 & 0xff00ff00 | uVar6);
        auVar46 = NEON_fmin(auVar63,*(undefined1 (*) [16])(param_3 + 0x340),4);
        *(long *)(param_3 + 0x348) = auVar46._8_8_;
        *(long *)(param_3 + 0x340) = auVar46._0_8_;
        *pfVar33 = fVar41;
        pfVar33[1] = 0.0;
        pfVar33[2] = fVar37;
        pfVar33[3] = 0.0;
        pfVar33[4] = 1.0;
        pfVar33[5] = 0.0;
        pfVar33[6] = fVar51;
        pfVar33 = (float *)(*(long *)(param_3 + 0x368) +
                           (ulong)*(ushort *)(*(long *)(*(long *)(param_3 + 0x358) + 0x18) + 0x18));
        *(float **)(param_3 + 0x368) = pfVar33;
        *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
        if (*(long *)(param_3 + 0x358) != 0) {
          auVar54._8_4_ = fVar36;
          auVar54._12_4_ = 0x3f800000;
          uVar56 = (undefined4)((ulong)*(undefined8 *)(param_3 + 0x338) >> 0x20);
          auVar24 = *(undefined1 (*) [12])(param_3 + 0x330);
          auVar64._0_4_ = fVar41 * fVar41;
          auVar64._4_4_ = 0;
          auVar64._8_4_ = fVar36 * fVar36;
          auVar64._12_4_ = 0;
          auVar67 = NEON_ext(auVar64,auVar64,8,1);
          auVar57 = NEON_fmin(auVar54,*(undefined1 (*) [16])(param_3 + 0x340),4);
          auVar17._12_4_ = uVar56;
          auVar17._0_12_ = *(undefined1 (*) [12])(param_3 + 0x330);
          auVar46 = NEON_fmax(auVar54,auVar17,4);
          uVar65 = NEON_rev64(CONCAT44(auVar67._0_4_ + auVar67._4_4_,auVar64._0_4_ + 0.0),4);
          *(long *)(param_3 + 0x338) = auVar46._8_8_;
          *(long *)(param_3 + 0x330) = auVar46._0_8_;
          *(long *)(param_3 + 0x348) = auVar57._8_8_;
          *(long *)(param_3 + 0x340) = auVar57._0_8_;
          auVar55._0_4_ = auVar64._0_4_ + 0.0 + (float)uVar65;
          auVar55._4_4_ = auVar55._0_4_;
          auVar55._8_4_ = auVar55._0_4_;
          auVar55._12_4_ = auVar55._0_4_;
          auVar18._12_4_ = uVar56;
          auVar18._0_12_ = auVar24;
          auVar46 = NEON_fmax(auVar55,auVar18,4);
          *(undefined4 *)(param_3 + 0x33c) = auVar46._12_4_;
          *pfVar33 = fVar41;
          pfVar33[1] = 0.0;
          pfVar33[2] = fVar36;
          pfVar33[3] = 0.0;
          pfVar33[4] = 1.0;
          pfVar33[5] = 0.0;
          pfVar33[6] = fVar51;
          uVar3 = *(ushort *)(*(long *)(*(long *)(param_3 + 0x358) + 0x18) + 0x18);
          *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
          *(ulong *)(param_3 + 0x368) = *(long *)(param_3 + 0x368) + (ulong)uVar3;
          if (*(long *)(param_3 + 0x358) != 0) {
            auVar46 = *(undefined1 (*) [16])(param_3 + 0x330);
            auVar40._8_4_ = fVar36;
            auVar40._0_8_ = auVar39._0_8_;
            auVar40._12_4_ = 0x3f800000;
            auVar59._0_4_ = fVar38 * fVar38;
            auVar59._4_4_ = 0;
            auVar59._8_4_ = fVar36 * fVar36;
            auVar59._12_4_ = 0;
            auVar57 = NEON_fmax(auVar40,auVar46,4);
            *(long *)(param_3 + 0x338) = auVar57._8_8_;
            *(long *)(param_3 + 0x330) = auVar57._0_8_;
            auVar57 = NEON_ext(auVar59,auVar59,8,1);
            uVar65 = NEON_rev64(CONCAT44(auVar57._0_4_ + auVar57._4_4_,auVar59._0_4_ + 0.0),4);
            auVar50._0_4_ = auVar59._0_4_ + 0.0 + (float)uVar65;
            auVar50._4_4_ = auVar50._0_4_;
            auVar50._8_4_ = auVar50._0_4_;
            auVar50._12_4_ = auVar50._0_4_;
            auVar46 = NEON_fmax(auVar50,auVar46,4);
            *(undefined4 *)(param_3 + 0x33c) = auVar46._12_4_;
            pfVar33 = *(float **)(param_3 + 0x368);
            fVar51 = (float)(uVar7 | param_7 & 0xff00ff00 | uVar6);
            auVar19._12_4_ = (int)((ulong)*(undefined8 *)(param_3 + 0x348) >> 0x20);
            auVar19._0_12_ = *(undefined1 (*) [12])(param_3 + 0x340);
            auVar46 = NEON_fmin(auVar40,auVar19,4);
            *(long *)(param_3 + 0x348) = auVar46._8_8_;
            *(long *)(param_3 + 0x340) = auVar46._0_8_;
            *pfVar33 = fVar38;
            pfVar33[1] = 0.0;
            pfVar33[2] = fVar36;
            pfVar33[3] = 0.0;
            pfVar33[4] = 1.0;
            pfVar33[5] = 0.0;
            pfVar33[6] = fVar51;
            uVar3 = *(ushort *)(*(long *)(*(long *)(param_3 + 0x358) + 0x18) + 0x18);
            *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
            pfVar33 = (float *)(*(long *)(param_3 + 0x368) + (ulong)uVar3);
            *(float **)(param_3 + 0x368) = pfVar33;
            if (*(long *)(param_3 + 0x358) != 0) {
              auVar44._8_4_ = fVar37;
              auVar44._0_8_ = auVar39._0_8_;
              auVar44._12_4_ = 0x3f800000;
              auVar39 = *(undefined1 (*) [16])(param_3 + 0x330);
              fVar41 = fVar38 * fVar38;
              auVar20._4_4_ = 0;
              auVar20._0_4_ = fVar41;
              auVar20._8_4_ = fVar37 * fVar37;
              auVar20._12_4_ = 0;
              auVar21._4_4_ = 0;
              auVar21._0_4_ = fVar41;
              auVar21._8_4_ = fVar37 * fVar37;
              auVar21._12_4_ = 0;
              auVar67 = NEON_ext(auVar20,auVar21,8,1);
              auVar57 = NEON_fmin(auVar44,*(undefined1 (*) [16])(param_3 + 0x340),4);
              auVar46 = NEON_fmax(auVar44,auVar39,4);
              uVar65 = NEON_rev64(CONCAT44(auVar67._0_4_ + auVar67._4_4_,fVar41 + 0.0),4);
              *(long *)(param_3 + 0x338) = auVar46._8_8_;
              *(long *)(param_3 + 0x330) = auVar46._0_8_;
              *(long *)(param_3 + 0x348) = auVar57._8_8_;
              *(long *)(param_3 + 0x340) = auVar57._0_8_;
              auVar45._0_4_ = fVar41 + 0.0 + (float)uVar65;
              auVar45._4_4_ = auVar45._0_4_;
              auVar45._8_4_ = auVar45._0_4_;
              auVar45._12_4_ = auVar45._0_4_;
              auVar39 = NEON_fmax(auVar45,auVar39,4);
              *(undefined4 *)(param_3 + 0x33c) = auVar39._12_4_;
              *pfVar33 = fVar38;
              pfVar33[1] = 0.0;
              pfVar33[2] = fVar37;
              pfVar33[3] = 0.0;
              pfVar33[4] = 1.0;
              pfVar33[5] = 0.0;
              pfVar33[6] = fVar51;
              uVar3 = *(ushort *)(*(long *)(*(long *)(param_3 + 0x358) + 0x18) + 0x18);
              *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
              *(ulong *)(param_3 + 0x368) = *(long *)(param_3 + 0x368) + (ulong)uVar3;
              if (*(long *)(param_3 + 0x358) != 0) {
                puVar30 = *(undefined2 **)(param_3 + 0x360);
                *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                *puVar30 = 0;
                puVar30 = *(undefined2 **)(param_3 + 0x360);
                *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                *puVar30 = 3;
                puVar30 = *(undefined2 **)(param_3 + 0x360);
                *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                *puVar30 = 2;
                *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 3;
                if (*(long *)(param_3 + 0x358) != 0) {
                  puVar30 = *(undefined2 **)(param_3 + 0x360);
                  *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                  *puVar30 = 0;
                  puVar30 = *(undefined2 **)(param_3 + 0x360);
                  *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                  *puVar30 = 2;
                  puVar30 = *(undefined2 **)(param_3 + 0x360);
                  *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                  *puVar30 = 1;
                  *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 3;
                }
              }
            }
          }
        }
      }
    }
    else {
      uVar27 = Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)(param_3,param_4,4,0xc);
      if ((uVar27 & 1) == 0) goto code_r0x0220b8a4;
      if (*(long *)(param_3 + 0x358) != 0) {
        fVar41 = -fVar38;
        uVar56 = (undefined4)((ulong)*(undefined8 *)(param_3 + 0x338) >> 0x20);
        auVar24 = *(undefined1 (*) [12])(param_3 + 0x330);
        fVar37 = -fVar36;
        auVar52._0_8_ = CONCAT44(0,fVar41);
        auVar60._8_4_ = fVar37;
        auVar60._0_8_ = auVar52._0_8_;
        auVar60._12_4_ = 0x3f800000;
        auVar66._0_4_ = fVar41 * fVar41;
        auVar66._4_4_ = 0;
        auVar66._8_4_ = fVar37 * fVar37;
        auVar66._12_4_ = 0;
        auVar8._12_4_ = uVar56;
        auVar8._0_12_ = *(undefined1 (*) [12])(param_3 + 0x330);
        auVar46 = NEON_fmax(auVar60,auVar8,4);
        *(long *)(param_3 + 0x338) = auVar46._8_8_;
        *(long *)(param_3 + 0x330) = auVar46._0_8_;
        auVar46 = NEON_ext(auVar66,auVar66,8,1);
        uVar65 = NEON_rev64(CONCAT44(auVar46._0_4_ + auVar46._4_4_,auVar66._0_4_ + 0.0),4);
        auVar47._0_4_ = auVar66._0_4_ + 0.0 + (float)uVar65;
        auVar47._4_4_ = auVar47._0_4_;
        auVar47._8_4_ = auVar47._0_4_;
        auVar47._12_4_ = auVar47._0_4_;
        auVar9._12_4_ = uVar56;
        auVar9._0_12_ = auVar24;
        auVar46 = NEON_fmax(auVar47,auVar9,4);
        *(undefined4 *)(param_3 + 0x33c) = auVar46._12_4_;
        pfVar33 = *(float **)(param_3 + 0x368);
        uVar7 = param_7 >> 0x10 & 0xff;
        uVar6 = (param_7 & 0xff) << 0x10;
        fVar51 = (float)(uVar7 | param_7 & 0xff00ff00 | uVar6);
        auVar46 = NEON_fmin(auVar60,*(undefined1 (*) [16])(param_3 + 0x340),4);
        *(long *)(param_3 + 0x348) = auVar46._8_8_;
        *(long *)(param_3 + 0x340) = auVar46._0_8_;
        *pfVar33 = fVar41;
        pfVar33[1] = 0.0;
        pfVar33[2] = fVar37;
        pfVar33[3] = 0.0;
        pfVar33[4] = 1.0;
        pfVar33[5] = 0.0;
        pfVar33[6] = fVar51;
        pfVar33 = (float *)(*(long *)(param_3 + 0x368) +
                           (ulong)*(ushort *)(*(long *)(*(long *)(param_3 + 0x358) + 0x18) + 0x18));
        *(float **)(param_3 + 0x368) = pfVar33;
        *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
        if (*(long *)(param_3 + 0x358) != 0) {
          auVar52._8_4_ = fVar36;
          auVar52._12_4_ = 0x3f800000;
          uVar56 = (undefined4)((ulong)*(undefined8 *)(param_3 + 0x338) >> 0x20);
          auVar24 = *(undefined1 (*) [12])(param_3 + 0x330);
          auVar61._0_4_ = fVar41 * fVar41;
          auVar61._4_4_ = 0;
          auVar61._8_4_ = fVar36 * fVar36;
          auVar61._12_4_ = 0;
          auVar67 = NEON_ext(auVar61,auVar61,8,1);
          auVar57 = NEON_fmin(auVar52,*(undefined1 (*) [16])(param_3 + 0x340),4);
          auVar10._12_4_ = uVar56;
          auVar10._0_12_ = *(undefined1 (*) [12])(param_3 + 0x330);
          auVar46 = NEON_fmax(auVar52,auVar10,4);
          uVar65 = NEON_rev64(CONCAT44(auVar67._0_4_ + auVar67._4_4_,auVar61._0_4_ + 0.0),4);
          *(long *)(param_3 + 0x338) = auVar46._8_8_;
          *(long *)(param_3 + 0x330) = auVar46._0_8_;
          *(long *)(param_3 + 0x348) = auVar57._8_8_;
          *(long *)(param_3 + 0x340) = auVar57._0_8_;
          auVar53._0_4_ = auVar61._0_4_ + 0.0 + (float)uVar65;
          auVar53._4_4_ = auVar53._0_4_;
          auVar53._8_4_ = auVar53._0_4_;
          auVar53._12_4_ = auVar53._0_4_;
          auVar11._12_4_ = uVar56;
          auVar11._0_12_ = auVar24;
          auVar46 = NEON_fmax(auVar53,auVar11,4);
          *(undefined4 *)(param_3 + 0x33c) = auVar46._12_4_;
          *pfVar33 = fVar41;
          pfVar33[1] = 0.0;
          pfVar33[2] = fVar36;
          pfVar33[3] = 0.0;
          pfVar33[4] = 1.0;
          pfVar33[5] = 0.0;
          pfVar33[6] = fVar51;
          uVar3 = *(ushort *)(*(long *)(*(long *)(param_3 + 0x358) + 0x18) + 0x18);
          *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
          *(ulong *)(param_3 + 0x368) = *(long *)(param_3 + 0x368) + (ulong)uVar3;
          if (*(long *)(param_3 + 0x358) != 0) {
            auVar46 = *(undefined1 (*) [16])(param_3 + 0x330);
            auVar39._8_4_ = fVar36;
            auVar39._12_4_ = 0x3f800000;
            auVar58._0_4_ = fVar38 * fVar38;
            auVar58._4_4_ = 0;
            auVar58._8_4_ = fVar36 * fVar36;
            auVar58._12_4_ = 0;
            auVar57 = NEON_fmax(auVar39,auVar46,4);
            *(long *)(param_3 + 0x338) = auVar57._8_8_;
            *(long *)(param_3 + 0x330) = auVar57._0_8_;
            auVar57 = NEON_ext(auVar58,auVar58,8,1);
            uVar65 = NEON_rev64(CONCAT44(auVar57._0_4_ + auVar57._4_4_,auVar58._0_4_ + 0.0),4);
            auVar48._0_4_ = auVar58._0_4_ + 0.0 + (float)uVar65;
            auVar48._4_4_ = auVar48._0_4_;
            auVar48._8_4_ = auVar48._0_4_;
            auVar48._12_4_ = auVar48._0_4_;
            auVar46 = NEON_fmax(auVar48,auVar46,4);
            *(undefined4 *)(param_3 + 0x33c) = auVar46._12_4_;
            pfVar33 = *(float **)(param_3 + 0x368);
            fVar51 = (float)(uVar7 | param_7 & 0xff00ff00 | uVar6);
            auVar12._12_4_ = (int)((ulong)*(undefined8 *)(param_3 + 0x348) >> 0x20);
            auVar12._0_12_ = *(undefined1 (*) [12])(param_3 + 0x340);
            auVar46 = NEON_fmin(auVar39,auVar12,4);
            *(long *)(param_3 + 0x348) = auVar46._8_8_;
            *(long *)(param_3 + 0x340) = auVar46._0_8_;
            *pfVar33 = fVar38;
            pfVar33[1] = 0.0;
            pfVar33[2] = fVar36;
            pfVar33[3] = 0.0;
            pfVar33[4] = 1.0;
            pfVar33[5] = 0.0;
            pfVar33[6] = fVar51;
            uVar3 = *(ushort *)(*(long *)(*(long *)(param_3 + 0x358) + 0x18) + 0x18);
            *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
            pfVar33 = (float *)(*(long *)(param_3 + 0x368) + (ulong)uVar3);
            *(float **)(param_3 + 0x368) = pfVar33;
            if (*(long *)(param_3 + 0x358) != 0) {
              auVar42._8_4_ = fVar37;
              auVar42._0_8_ = auVar39._0_8_;
              auVar42._12_4_ = 0x3f800000;
              auVar39 = *(undefined1 (*) [16])(param_3 + 0x330);
              fVar41 = fVar38 * fVar38;
              auVar13._4_4_ = 0;
              auVar13._0_4_ = fVar41;
              auVar13._8_4_ = fVar37 * fVar37;
              auVar13._12_4_ = 0;
              auVar14._4_4_ = 0;
              auVar14._0_4_ = fVar41;
              auVar14._8_4_ = fVar37 * fVar37;
              auVar14._12_4_ = 0;
              auVar67 = NEON_ext(auVar13,auVar14,8,1);
              auVar57 = NEON_fmin(auVar42,*(undefined1 (*) [16])(param_3 + 0x340),4);
              auVar46 = NEON_fmax(auVar42,auVar39,4);
              uVar65 = NEON_rev64(CONCAT44(auVar67._0_4_ + auVar67._4_4_,fVar41 + 0.0),4);
              *(long *)(param_3 + 0x338) = auVar46._8_8_;
              *(long *)(param_3 + 0x330) = auVar46._0_8_;
              *(long *)(param_3 + 0x348) = auVar57._8_8_;
              *(long *)(param_3 + 0x340) = auVar57._0_8_;
              auVar43._0_4_ = fVar41 + 0.0 + (float)uVar65;
              auVar43._4_4_ = auVar43._0_4_;
              auVar43._8_4_ = auVar43._0_4_;
              auVar43._12_4_ = auVar43._0_4_;
              auVar39 = NEON_fmax(auVar43,auVar39,4);
              *(undefined4 *)(param_3 + 0x33c) = auVar39._12_4_;
              *pfVar33 = fVar38;
              pfVar33[1] = 0.0;
              pfVar33[2] = fVar37;
              pfVar33[3] = 0.0;
              pfVar33[4] = 1.0;
              pfVar33[5] = 0.0;
              pfVar33[6] = fVar51;
              uVar3 = *(ushort *)(*(long *)(*(long *)(param_3 + 0x358) + 0x18) + 0x18);
              *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
              *(ulong *)(param_3 + 0x368) = *(long *)(param_3 + 0x368) + (ulong)uVar3;
              if (*(long *)(param_3 + 0x358) != 0) {
                puVar30 = *(undefined2 **)(param_3 + 0x360);
                *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                *puVar30 = 0;
                puVar30 = *(undefined2 **)(param_3 + 0x360);
                *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                *puVar30 = 1;
                *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
                if (*(long *)(param_3 + 0x358) != 0) {
                  puVar30 = *(undefined2 **)(param_3 + 0x360);
                  *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                  *puVar30 = 1;
                  puVar30 = *(undefined2 **)(param_3 + 0x360);
                  *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                  *puVar30 = 2;
                  *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
                  if (*(long *)(param_3 + 0x358) != 0) {
                    puVar30 = *(undefined2 **)(param_3 + 0x360);
                    *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                    *puVar30 = 2;
                    puVar30 = *(undefined2 **)(param_3 + 0x360);
                    *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                    *puVar30 = 3;
                    *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
                    if (*(long *)(param_3 + 0x358) != 0) {
                      puVar30 = *(undefined2 **)(param_3 + 0x360);
                      *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                      *puVar30 = 3;
                      puVar30 = *(undefined2 **)(param_3 + 0x360);
                      *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                      *puVar30 = 0;
                      *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
                      if (*(long *)(param_3 + 0x358) != 0) {
                        puVar30 = *(undefined2 **)(param_3 + 0x360);
                        *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                        *puVar30 = 0;
                        puVar30 = *(undefined2 **)(param_3 + 0x360);
                        *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                        *puVar30 = 2;
                        *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
                        if (*(long *)(param_3 + 0x358) != 0) {
                          puVar30 = *(undefined2 **)(param_3 + 0x360);
                          *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                          *puVar30 = 1;
                          puVar30 = *(undefined2 **)(param_3 + 0x360);
                          *(undefined2 **)(param_3 + 0x360) = puVar30 + 1;
                          *puVar30 = 3;
                          *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
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
  else {
    iVar29 = param_5 + 1;
    iVar1 = param_6 + 1;
    if (bVar26) {
      uVar27 = Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)(param_3,param_4,iVar1 * iVar29,iVar28 * 6);
      if ((uVar27 & 1) == 0) goto code_r0x0220b8a4;
      if (-1 < param_5) {
        if (-1 < param_6) {
          lVar32 = *(long *)(param_3 + 0x358);
          iVar28 = 0;
          do {
            fVar51 = ((float)iVar28 / (float)param_5) * param_1 - fVar38;
            iVar31 = 0;
            lVar35 = lVar32;
            do {
              if (lVar35 != 0) {
                auVar39 = *(undefined1 (*) [16])(param_3 + 0x330);
                auVar67._4_4_ = 0;
                auVar67._0_4_ = fVar51;
                fVar37 = ((float)iVar31 / (float)param_6) * param_2 - fVar36;
                auVar67._8_4_ = fVar37;
                auVar67._12_4_ = 0x3f800000;
                fVar41 = fVar51 * fVar51;
                auVar46 = NEON_fmax(auVar67,auVar39,4);
                *(long *)(param_3 + 0x338) = auVar46._8_8_;
                *(long *)(param_3 + 0x330) = auVar46._0_8_;
                auVar46._4_4_ = 0;
                auVar46._0_4_ = fVar41;
                auVar46._8_4_ = fVar37 * fVar37;
                auVar46._12_4_ = 0;
                auVar57._4_4_ = 0;
                auVar57._0_4_ = fVar41;
                auVar57._8_4_ = fVar37 * fVar37;
                auVar57._12_4_ = 0;
                auVar46 = NEON_ext(auVar46,auVar57,8,1);
                uVar65 = NEON_rev64(CONCAT44(auVar46._0_4_ + auVar46._4_4_,fVar41 + 0.0),4);
                auVar70._0_4_ = fVar41 + 0.0 + (float)uVar65;
                auVar70._4_4_ = auVar70._0_4_;
                auVar70._8_4_ = auVar70._0_4_;
                auVar70._12_4_ = auVar70._0_4_;
                auVar39 = NEON_fmax(auVar70,auVar39,4);
                *(int *)(param_3 + 0x33c) = auVar39._12_4_;
                pfVar33 = *(float **)(param_3 + 0x368);
                auVar39 = NEON_fmin(auVar67,*(undefined1 (*) [16])(param_3 + 0x340),4);
                *(long *)(param_3 + 0x348) = auVar39._8_8_;
                *(long *)(param_3 + 0x340) = auVar39._0_8_;
                *pfVar33 = fVar51;
                pfVar33[1] = 0.0;
                pfVar33[2] = fVar37;
                pfVar33[3] = 0.0;
                pfVar33[4] = 1.0;
                pfVar33[5] = 0.0;
                pfVar33[6] = (float)(param_7 >> 0x10 & 0xff | param_7 & 0xff00ff00 |
                                    (param_7 & 0xff) << 0x10);
                lVar32 = *(long *)(param_3 + 0x358);
                *(ulong *)(param_3 + 0x368) =
                     *(long *)(param_3 + 0x368) +
                     (ulong)*(ushort *)(*(long *)(lVar32 + 0x18) + 0x18);
                *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
                lVar35 = lVar32;
              }
              iVar31 = iVar31 + 1;
            } while (iVar1 != iVar31);
            iVar28 = iVar28 + 1;
          } while (iVar28 != iVar29);
        }
        if ((0 < param_5) && (0 < param_6)) {
          iVar29 = 0;
          iVar28 = 0;
          do {
            iVar31 = 0;
            sVar4 = (short)iVar29;
            do {
              if (*(long *)(param_3 + 0x358) != 0) {
                psVar34 = *(short **)(param_3 + 0x360);
                sVar25 = (short)iVar31;
                *(short **)(param_3 + 0x360) = psVar34 + 1;
                *psVar34 = sVar4 + sVar25;
                psVar34 = *(short **)(param_3 + 0x360);
                sVar5 = (short)param_6 + sVar4 + sVar25;
                *(short **)(param_3 + 0x360) = psVar34 + 1;
                *psVar34 = sVar5 + 1;
                psVar34 = *(short **)(param_3 + 0x360);
                sVar5 = sVar5 + 2;
                *(short **)(param_3 + 0x360) = psVar34 + 1;
                *psVar34 = sVar5;
                *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 3;
                if (*(long *)(param_3 + 0x358) != 0) {
                  psVar34 = *(short **)(param_3 + 0x360);
                  *(short **)(param_3 + 0x360) = psVar34 + 1;
                  *psVar34 = sVar4 + sVar25;
                  psVar34 = *(short **)(param_3 + 0x360);
                  *(short **)(param_3 + 0x360) = psVar34 + 1;
                  *psVar34 = sVar5;
                  psVar34 = *(short **)(param_3 + 0x360);
                  *(short **)(param_3 + 0x360) = psVar34 + 1;
                  *psVar34 = sVar4 + sVar25 + 1;
                  *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 3;
                }
              }
              iVar31 = iVar31 + 1;
            } while (param_6 != iVar31);
            iVar28 = iVar28 + 1;
            iVar29 = iVar29 + iVar1;
          } while (iVar28 != param_5);
        }
      }
    }
    else {
      uVar27 = Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)(param_3,param_4,iVar1 * iVar29,iVar28 * 8);
      if ((uVar27 & 1) == 0) goto code_r0x0220b8a4;
      if (-1 < param_5) {
        if (-1 < param_6) {
          lVar32 = *(long *)(param_3 + 0x358);
          iVar28 = 0;
          do {
            fVar51 = ((float)iVar28 / (float)param_5) * param_1 - fVar38;
            iVar31 = 0;
            lVar35 = lVar32;
            do {
              if (lVar35 != 0) {
                auVar39 = *(undefined1 (*) [16])(param_3 + 0x330);
                auVar62._4_4_ = 0;
                auVar62._0_4_ = fVar51;
                fVar37 = ((float)iVar31 / (float)param_6) * param_2 - fVar36;
                auVar62._8_4_ = fVar37;
                auVar62._12_4_ = 0x3f800000;
                fVar41 = fVar51 * fVar51;
                auVar46 = NEON_fmax(auVar62,auVar39,4);
                *(long *)(param_3 + 0x338) = auVar46._8_8_;
                *(long *)(param_3 + 0x330) = auVar46._0_8_;
                auVar22._4_4_ = 0;
                auVar22._0_4_ = fVar41;
                auVar22._8_4_ = fVar37 * fVar37;
                auVar22._12_4_ = 0;
                auVar23._4_4_ = 0;
                auVar23._0_4_ = fVar41;
                auVar23._8_4_ = fVar37 * fVar37;
                auVar23._12_4_ = 0;
                auVar46 = NEON_ext(auVar22,auVar23,8,1);
                uVar65 = NEON_rev64(CONCAT44(auVar46._0_4_ + auVar46._4_4_,fVar41 + 0.0),4);
                auVar69._0_4_ = fVar41 + 0.0 + (float)uVar65;
                auVar69._4_4_ = auVar69._0_4_;
                auVar69._8_4_ = auVar69._0_4_;
                auVar69._12_4_ = auVar69._0_4_;
                auVar39 = NEON_fmax(auVar69,auVar39,4);
                *(int *)(param_3 + 0x33c) = auVar39._12_4_;
                pfVar33 = *(float **)(param_3 + 0x368);
                auVar39 = NEON_fmin(auVar62,*(undefined1 (*) [16])(param_3 + 0x340),4);
                *(long *)(param_3 + 0x348) = auVar39._8_8_;
                *(long *)(param_3 + 0x340) = auVar39._0_8_;
                *pfVar33 = fVar51;
                pfVar33[1] = 0.0;
                pfVar33[2] = fVar37;
                pfVar33[3] = 0.0;
                pfVar33[4] = 1.0;
                pfVar33[5] = 0.0;
                pfVar33[6] = (float)(param_7 >> 0x10 & 0xff | param_7 & 0xff00ff00 |
                                    (param_7 & 0xff) << 0x10);
                lVar32 = *(long *)(param_3 + 0x358);
                *(ulong *)(param_3 + 0x368) =
                     *(long *)(param_3 + 0x368) +
                     (ulong)*(ushort *)(*(long *)(lVar32 + 0x18) + 0x18);
                *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
                lVar35 = lVar32;
              }
              iVar31 = iVar31 + 1;
            } while (iVar1 != iVar31);
            iVar28 = iVar28 + 1;
          } while (iVar28 != iVar29);
        }
        if ((0 < param_5) && (0 < param_6)) {
          iVar29 = 0;
          iVar28 = 0;
          do {
            iVar31 = 0;
            do {
              if (*(long *)(param_3 + 0x358) != 0) {
                psVar34 = *(short **)(param_3 + 0x360);
                sVar4 = (short)iVar29 + (short)iVar31;
                *(short **)(param_3 + 0x360) = psVar34 + 1;
                *psVar34 = sVar4;
                psVar34 = *(short **)(param_3 + 0x360);
                *(short **)(param_3 + 0x360) = psVar34 + 1;
                *psVar34 = sVar4 + 1;
                *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
                if (*(long *)(param_3 + 0x358) != 0) {
                  psVar34 = *(short **)(param_3 + 0x360);
                  *(short **)(param_3 + 0x360) = psVar34 + 1;
                  *psVar34 = sVar4 + 1;
                  psVar34 = *(short **)(param_3 + 0x360);
                  sVar25 = (short)param_6 + (short)iVar29 + (short)iVar31;
                  sVar5 = sVar25 + 2;
                  *(short **)(param_3 + 0x360) = psVar34 + 1;
                  *psVar34 = sVar5;
                  *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
                  if (*(long *)(param_3 + 0x358) != 0) {
                    psVar34 = *(short **)(param_3 + 0x360);
                    sVar25 = sVar25 + 1;
                    *(short **)(param_3 + 0x360) = psVar34 + 1;
                    *psVar34 = sVar5;
                    psVar34 = *(short **)(param_3 + 0x360);
                    *(short **)(param_3 + 0x360) = psVar34 + 1;
                    *psVar34 = sVar25;
                    *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
                    if (*(long *)(param_3 + 0x358) != 0) {
                      psVar34 = *(short **)(param_3 + 0x360);
                      *(short **)(param_3 + 0x360) = psVar34 + 1;
                      *psVar34 = sVar4;
                      psVar34 = *(short **)(param_3 + 0x360);
                      *(short **)(param_3 + 0x360) = psVar34 + 1;
                      *psVar34 = sVar25;
                      *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
                    }
                  }
                }
              }
              iVar31 = iVar31 + 1;
            } while (param_6 != iVar31);
            iVar28 = iVar28 + 1;
            iVar29 = iVar29 + iVar1;
          } while (iVar28 != param_5);
        }
      }
    }
  }
  Aska::DirectAofHandler::EndMesh()(param_3);
  fVar36 = fVar38 * fVar38 + fVar36 * fVar36;
  fStack_64 = SQRT(fVar36);
  if (NAN(fStack_64)) {
    fStack_64 = (float)sqrtf(fVar36);
  }
  uStack_70 = 0;
  uStack_68 = 0;
  Aska::DirectAofHandler::Close(Aska::Vector const*, bool)(param_3,&uStack_70,1);
code_r0x0220b8a4:
  *(char *)(param_4 + 2) = cVar2;
  return;
}

// ==== Aska::DirectAofHandler::Cone(Aska::DirectMaterial*, float, float, int, int, unsigned int, Aska::Vector const*, bool)
// vaddr 0x210b8c8 | ghidra 0x220b8c8 | size 3256 | symbol _ZN4Aska16DirectAofHandler4ConeEPNS_14DirectMaterialEffiijPKNS_6VectorEb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16DirectAofHandler4ConeEPNS_14DirectMaterialEffiijPKNS_6VectorEb
               (float param_1,float param_2,long param_3,long param_4,int param_5,int param_6,
               uint param_7,float *param_8,uint param_9)

{
  bool bVar1;
  float *pfVar2;
  char cVar3;
  short sVar4;
  undefined2 uVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  undefined1 auVar26 [16];
  undefined1 auVar27 [16];
  short sVar28;
  bool bVar29;
  ulong uVar30;
  float *pfVar31;
  long lVar32;
  int iVar33;
  int iVar34;
  int iVar35;
  short *psVar36;
  int iVar37;
  undefined2 *puVar38;
  int iVar39;
  int iVar40;
  undefined1 auVar41 [16];
  undefined1 auVar42 [16];
  undefined1 auVar43 [16];
  float fVar44;
  float fVar45;
  float fVar46;
  float fVar47;
  float fVar48;
  float fVar49;
  undefined8 uVar50;
  undefined1 auVar51 [16];
  undefined1 auVar52 [16];
  undefined1 auVar53 [16];
  float fVar54;
  float fVar55;
  float fVar56;
  float fVar57;
  float fStack_cc;
  undefined8 uStack_c0;
  undefined8 uStack_b0;
  undefined4 uStack_a8;
  float fStack_a4;
  
  if (param_6 < 4) {
    param_6 = 3;
  }
  cVar3 = *(char *)(param_4 + 2);
  pfVar2 = (float *)PTR__ZN4Aska6Vector10zeroVectorE_02cc0768;
  if (param_8 != (float *)0x0) {
    pfVar2 = param_8;
  }
  if (cVar3 != '\x02') {
    *(undefined1 *)(param_4 + 2) = 0;
  }
  fVar56 = SQRT(param_1 * param_1 + param_2 * param_2);
  if (NAN(fVar56)) {
    fVar56 = (float)sqrtf();
  }
  iVar39 = param_6 * (param_5 << 1 | 1U) + 1;
  sVar28 = (short)param_6;
  if (*(char *)(param_4 + 2) == '\x02') {
    uVar30 = Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)(param_3,param_4,iVar39,param_6 * (param_5 * 4 + 4));
    if ((uVar30 & 1) == 0) goto code_r0x0220c54c;
    fVar49 = pfVar2[1];
    fVar44 = *pfVar2 + 0.0;
    fVar46 = fVar49 + 0.0;
    fVar47 = pfVar2[2] + 0.0;
    lVar32 = 0;
    if (*(long *)(param_3 + 0x358) != 0) {
      auVar51._0_4_ = fVar44 * fVar44;
      auVar51._4_4_ = fVar46 * fVar46;
      auVar51._8_4_ = fVar47 * fVar47;
      auVar51._12_4_ = 0;
      auVar41 = NEON_ext(auVar51,auVar51,8,1);
      uVar50 = NEON_rev64(CONCAT44(auVar41._0_4_ + auVar41._4_4_,auVar51._0_4_ + auVar51._4_4_),4);
      auVar42._0_4_ = auVar51._0_4_ + auVar51._4_4_ + (float)uVar50;
      auVar42._4_4_ = auVar42._0_4_;
      auVar42._8_4_ = auVar42._0_4_;
      auVar42._12_4_ = auVar42._0_4_;
      auVar18._4_4_ = fVar46;
      auVar18._0_4_ = fVar44;
      auVar18._8_4_ = fVar47;
      auVar18._12_4_ = 0x3f800000;
      auVar52 = NEON_fmax(auVar18,*(undefined1 (*) [16])(param_3 + 0x330),4);
      auVar41 = NEON_fmax(auVar42,*(undefined1 (*) [16])(param_3 + 0x330),4);
      *(long *)(param_3 + 0x338) = auVar52._8_8_;
      *(long *)(param_3 + 0x330) = auVar52._0_8_;
      *(int *)(param_3 + 0x33c) = auVar41._12_4_;
      pfVar31 = *(float **)(param_3 + 0x368);
      auVar19._4_4_ = fVar46;
      auVar19._0_4_ = fVar44;
      auVar19._8_4_ = fVar47;
      auVar19._12_4_ = 0x3f800000;
      auVar41 = NEON_fmin(auVar19,*(undefined1 (*) [16])(param_3 + 0x340),4);
      *(long *)(param_3 + 0x348) = auVar41._8_8_;
      *(long *)(param_3 + 0x340) = auVar41._0_8_;
      *pfVar31 = fVar44;
      pfVar31[1] = fVar46;
      pfVar31[2] = fVar47;
      pfVar31[3] = 0.0;
      pfVar31[4] = -1.0;
      pfVar31[5] = 0.0;
      pfVar31[6] = (float)(param_7 >> 0x10 & 0xff | param_7 & 0xff00ff00 | (param_7 & 0xff) << 0x10)
      ;
      lVar32 = *(long *)(param_3 + 0x358);
      *(ulong *)(param_3 + 0x368) =
           *(long *)(param_3 + 0x368) + (ulong)*(ushort *)(*(long *)(lVar32 + 0x18) + 0x18);
      *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
      fVar49 = pfVar2[1];
    }
    if (param_5 < 1) {
code_r0x0220bdf0:
      bVar29 = 0 < param_6;
      if (param_6 < 1) {
        bVar29 = false;
      }
      else {
        iVar39 = 1;
        while( true ) {
          if (lVar32 != 0) {
            puVar38 = *(undefined2 **)(param_3 + 0x360);
            *(undefined2 **)(param_3 + 0x360) = puVar38 + 1;
            *puVar38 = 0;
            psVar36 = *(short **)(param_3 + 0x360);
            *(short **)(param_3 + 0x360) = psVar36 + 1;
            *psVar36 = sVar28 * ((short)param_5 + -1) + (short)iVar39;
            *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
          }
          if (param_6 <= iVar39) break;
          lVar32 = *(long *)(param_3 + 0x358);
          iVar39 = iVar39 + 1;
        }
      }
      bVar1 = bVar29;
      if (0 < param_5) {
        bVar1 = false;
        if (!bVar29) goto code_r0x0220bfa4;
        iVar39 = 0;
        iVar40 = 1;
        do {
          iVar33 = 0;
          iVar34 = iVar39 * param_6 + param_6;
          do {
            iVar37 = iVar39 * param_6 + 1 + iVar33;
            if (*(long *)(param_3 + 0x358) != 0) {
              puVar38 = *(undefined2 **)(param_3 + 0x360);
              *(undefined2 **)(param_3 + 0x360) = puVar38 + 1;
              *puVar38 = (short)iVar34;
              psVar36 = *(short **)(param_3 + 0x360);
              *(short **)(param_3 + 0x360) = psVar36 + 1;
              *psVar36 = (short)iVar40 + (short)iVar33;
              *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
            }
            iVar33 = iVar33 + 1;
            iVar34 = iVar37;
          } while (iVar33 < param_6);
          iVar39 = iVar39 + 1;
          iVar40 = iVar40 + param_6;
        } while (iVar39 != param_5);
        bVar1 = true;
      }
      if (-1 < param_5) goto code_r0x0220bfa4;
    }
    else {
      if (0 < param_6) {
        iVar39 = 0;
        fVar44 = _UNK_027edb34 / (float)param_6;
        do {
          iVar39 = iVar39 + 1;
          iVar40 = 0;
          fVar46 = ((float)iVar39 * param_1) / (float)param_5;
          uStack_c0 = (ulong)(uint)fVar49 << 0x20;
          do {
            fStack_cc = (float)((ulong)uStack_c0 >> 0x20);
            fVar57 = fVar44 * (float)iVar40;
            fVar47 = (float)cosf(fVar57);
            fVar45 = fVar46 * fVar47 + *pfVar2;
            uStack_c0 = CONCAT44(fVar49,fVar45);
            fVar47 = (float)sinf(fVar57);
            fVar47 = fVar46 * fVar47 + pfVar2[2];
            lVar32 = 0;
            if (*(long *)(param_3 + 0x358) != 0) {
              fVar57 = fVar45 * fVar45;
              fVar48 = fVar49 * fVar49;
              auVar6._4_4_ = fVar48;
              auVar6._0_4_ = fVar57;
              auVar6._8_4_ = fVar47 * fVar47;
              auVar6._12_4_ = 0;
              auVar7._4_4_ = fVar48;
              auVar7._0_4_ = fVar57;
              auVar7._8_4_ = fVar47 * fVar47;
              auVar7._12_4_ = 0;
              auVar41 = NEON_ext(auVar6,auVar7,8,1);
              uVar50 = NEON_rev64(CONCAT44(auVar41._0_4_ + auVar41._4_4_,fVar57 + fVar48),4);
              fVar57 = fVar57 + fVar48 + (float)uVar50;
              auVar20._8_4_ = fVar47;
              auVar20._0_8_ = uStack_c0;
              auVar20._12_4_ = 0x3f800000;
              auVar52 = NEON_fmax(auVar20,*(undefined1 (*) [16])(param_3 + 0x330),4);
              auVar8._4_4_ = fVar57;
              auVar8._0_4_ = fVar57;
              auVar8._8_4_ = fVar57;
              auVar8._12_4_ = fVar57;
              auVar41 = NEON_fmax(auVar8,*(undefined1 (*) [16])(param_3 + 0x330),4);
              *(long *)(param_3 + 0x338) = auVar52._8_8_;
              *(long *)(param_3 + 0x330) = auVar52._0_8_;
              *(int *)(param_3 + 0x33c) = auVar41._12_4_;
              auVar21._8_4_ = fVar47;
              auVar21._0_8_ = uStack_c0;
              auVar21._12_4_ = 0x3f800000;
              auVar41 = NEON_fmin(auVar21,*(undefined1 (*) [16])(param_3 + 0x340),4);
              *(long *)(param_3 + 0x348) = auVar41._8_8_;
              *(long *)(param_3 + 0x340) = auVar41._0_8_;
              pfVar31 = *(float **)(param_3 + 0x368);
              *pfVar31 = fVar45;
              pfVar31[1] = fStack_cc;
              pfVar31[2] = fVar47;
              pfVar31[3] = 0.0;
              pfVar31[4] = -1.0;
              pfVar31[5] = 0.0;
              pfVar31[6] = (float)(param_7 >> 0x10 & 0xff | param_7 & 0xff00ff00 |
                                  (param_7 & 0xff) << 0x10);
              lVar32 = *(long *)(param_3 + 0x358);
              *(ulong *)(param_3 + 0x368) =
                   *(long *)(param_3 + 0x368) + (ulong)*(ushort *)(*(long *)(lVar32 + 0x18) + 0x18);
              *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
            }
            iVar40 = iVar40 + 1;
          } while (iVar40 < param_6);
        } while (iVar39 != param_5);
        goto code_r0x0220bdf0;
      }
      bVar1 = false;
code_r0x0220bfa4:
      iVar39 = 0;
      fVar44 = _UNK_027edb34 / (float)param_6;
      do {
        if (bVar1) {
          iVar40 = 0;
          fVar46 = ((float)iVar39 * param_1) / (float)param_5;
          do {
            fVar49 = fVar44 * (float)iVar40;
            fVar47 = (float)cosf(fVar49);
            fVar49 = (float)sinf(fVar49);
            fVar57 = fVar46 * fVar47 + *pfVar2;
            fVar45 = (1.0 - (float)iVar39 / (float)param_5) * param_2 + pfVar2[1];
            fVar48 = fVar46 * fVar49 + pfVar2[2];
            if (*(long *)(param_3 + 0x358) != 0) {
              fVar54 = fVar57 * fVar57;
              fVar55 = fVar45 * fVar45;
              auVar12._4_4_ = fVar55;
              auVar12._0_4_ = fVar54;
              auVar12._8_4_ = fVar48 * fVar48;
              auVar12._12_4_ = 0;
              auVar13._4_4_ = fVar55;
              auVar13._0_4_ = fVar54;
              auVar13._8_4_ = fVar48 * fVar48;
              auVar13._12_4_ = 0;
              auVar41 = NEON_ext(auVar12,auVar13,8,1);
              uVar50 = NEON_rev64(CONCAT44(auVar41._0_4_ + auVar41._4_4_,fVar54 + fVar55),4);
              fVar54 = fVar54 + fVar55 + (float)uVar50;
              auVar22._4_4_ = fVar45;
              auVar22._0_4_ = fVar57;
              auVar22._8_4_ = fVar48;
              auVar22._12_4_ = 0x3f800000;
              auVar52 = NEON_fmax(auVar22,*(undefined1 (*) [16])(param_3 + 0x330),4);
              auVar14._4_4_ = fVar54;
              auVar14._0_4_ = fVar54;
              auVar14._8_4_ = fVar54;
              auVar14._12_4_ = fVar54;
              auVar41 = NEON_fmax(auVar14,*(undefined1 (*) [16])(param_3 + 0x330),4);
              *(long *)(param_3 + 0x338) = auVar52._8_8_;
              *(long *)(param_3 + 0x330) = auVar52._0_8_;
              *(int *)(param_3 + 0x33c) = auVar41._12_4_;
              pfVar31 = *(float **)(param_3 + 0x368);
              auVar23._4_4_ = fVar45;
              auVar23._0_4_ = fVar57;
              auVar23._8_4_ = fVar48;
              auVar23._12_4_ = 0x3f800000;
              auVar41 = NEON_fmin(auVar23,*(undefined1 (*) [16])(param_3 + 0x340),4);
              *(long *)(param_3 + 0x348) = auVar41._8_8_;
              *(long *)(param_3 + 0x340) = auVar41._0_8_;
              *pfVar31 = fVar57;
              pfVar31[1] = fVar45;
              pfVar31[2] = fVar48;
              pfVar31[3] = (fVar47 * param_2) / fVar56;
              pfVar31[4] = param_1 / fVar56;
              pfVar31[5] = (fVar49 * param_2) / fVar56;
              pfVar31[6] = (float)(param_7 >> 0x10 & 0xff | param_7 & 0xff00ff00 |
                                  (param_7 & 0xff) << 0x10);
              *(ulong *)(param_3 + 0x368) =
                   *(long *)(param_3 + 0x368) +
                   (ulong)*(ushort *)(*(long *)(*(long *)(param_3 + 0x358) + 0x18) + 0x18);
              *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
            }
            iVar40 = iVar40 + 1;
          } while (iVar40 < param_6);
        }
        bVar29 = iVar39 != param_5;
        iVar39 = iVar39 + 1;
      } while (bVar29);
    }
    iVar39 = param_6 * param_5 + 1;
    if (bVar1) {
      iVar40 = 0;
      do {
        if (*(long *)(param_3 + 0x358) != 0) {
          psVar36 = *(short **)(param_3 + 0x360);
          *(short **)(param_3 + 0x360) = psVar36 + 1;
          *psVar36 = (short)iVar39 + (short)iVar40;
          psVar36 = *(short **)(param_3 + 0x360);
          *(short **)(param_3 + 0x360) = psVar36 + 1;
          *psVar36 = ((short)param_5 * sVar28 * 2 | 1U) + (short)iVar40;
          *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
        }
        iVar40 = iVar40 + 1;
      } while (iVar40 < param_6);
    }
    if ((0 < param_5) && (bVar1)) {
      iVar40 = 0;
      iVar33 = param_6 * (param_5 + 1) + 1;
      do {
        iVar39 = iVar39 + param_6;
        iVar37 = 0;
        iVar34 = param_6 + -1;
        do {
          iVar35 = iVar37;
          if (*(long *)(param_3 + 0x358) != 0) {
            psVar36 = *(short **)(param_3 + 0x360);
            *(short **)(param_3 + 0x360) = psVar36 + 1;
            *psVar36 = (short)iVar34 + (short)iVar39;
            psVar36 = *(short **)(param_3 + 0x360);
            *(short **)(param_3 + 0x360) = psVar36 + 1;
            *psVar36 = (short)iVar33 + (short)iVar35;
            *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
          }
          iVar37 = iVar35 + 1;
          iVar34 = iVar35;
        } while (iVar35 + 1 < param_6);
        iVar40 = iVar40 + 1;
        iVar33 = iVar33 + param_6;
      } while (iVar40 != param_5);
    }
  }
  else {
    uVar30 = Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)(param_3,param_4,iVar39,param_6 * (param_5 * 0xc + -3));
    if ((uVar30 & 1) == 0) goto code_r0x0220c54c;
    fVar49 = pfVar2[1];
    fVar44 = *pfVar2 + 0.0;
    fVar46 = fVar49 + 0.0;
    fVar47 = pfVar2[2] + 0.0;
    lVar32 = 0;
    if (*(long *)(param_3 + 0x358) != 0) {
      auVar53._0_4_ = fVar44 * fVar44;
      auVar53._4_4_ = fVar46 * fVar46;
      auVar53._8_4_ = fVar47 * fVar47;
      auVar53._12_4_ = 0;
      auVar41 = NEON_ext(auVar53,auVar53,8,1);
      uVar50 = NEON_rev64(CONCAT44(auVar41._0_4_ + auVar41._4_4_,auVar53._0_4_ + auVar53._4_4_),4);
      auVar43._0_4_ = auVar53._0_4_ + auVar53._4_4_ + (float)uVar50;
      auVar43._4_4_ = auVar43._0_4_;
      auVar43._8_4_ = auVar43._0_4_;
      auVar43._12_4_ = auVar43._0_4_;
      auVar41._4_4_ = fVar46;
      auVar41._0_4_ = fVar44;
      auVar41._8_4_ = fVar47;
      auVar41._12_4_ = 0x3f800000;
      auVar52 = NEON_fmax(auVar41,*(undefined1 (*) [16])(param_3 + 0x330),4);
      auVar41 = NEON_fmax(auVar43,*(undefined1 (*) [16])(param_3 + 0x330),4);
      *(long *)(param_3 + 0x338) = auVar52._8_8_;
      *(long *)(param_3 + 0x330) = auVar52._0_8_;
      *(int *)(param_3 + 0x33c) = auVar41._12_4_;
      pfVar31 = *(float **)(param_3 + 0x368);
      auVar52._4_4_ = fVar46;
      auVar52._0_4_ = fVar44;
      auVar52._8_4_ = fVar47;
      auVar52._12_4_ = 0x3f800000;
      auVar41 = NEON_fmin(auVar52,*(undefined1 (*) [16])(param_3 + 0x340),4);
      *(long *)(param_3 + 0x348) = auVar41._8_8_;
      *(long *)(param_3 + 0x340) = auVar41._0_8_;
      *pfVar31 = fVar44;
      pfVar31[1] = fVar46;
      pfVar31[2] = fVar47;
      pfVar31[3] = 0.0;
      pfVar31[4] = -1.0;
      pfVar31[5] = 0.0;
      pfVar31[6] = (float)(param_7 >> 0x10 & 0xff | param_7 & 0xff00ff00 | (param_7 & 0xff) << 0x10)
      ;
      lVar32 = *(long *)(param_3 + 0x358);
      *(ulong *)(param_3 + 0x368) =
           *(long *)(param_3 + 0x368) + (ulong)*(ushort *)(*(long *)(lVar32 + 0x18) + 0x18);
      *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
      fVar49 = pfVar2[1];
    }
    if (param_5 < 1) {
code_r0x0220beec:
      bVar1 = 0 < param_6;
      if (param_6 < 1) {
        bVar1 = false;
      }
      else {
        iVar39 = param_6;
        iVar40 = 1;
        while( true ) {
          if (lVar32 != 0) {
            puVar38 = *(undefined2 **)(param_3 + 0x360);
            *(undefined2 **)(param_3 + 0x360) = puVar38 + 1;
            *puVar38 = (short)iVar39;
            puVar38 = *(undefined2 **)(param_3 + 0x360);
            *(undefined2 **)(param_3 + 0x360) = puVar38 + 1;
            *puVar38 = 0;
            puVar38 = *(undefined2 **)(param_3 + 0x360);
            *(undefined2 **)(param_3 + 0x360) = puVar38 + 1;
            *puVar38 = (short)iVar40;
            *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 3;
          }
          if (param_6 <= iVar40) break;
          lVar32 = *(long *)(param_3 + 0x358);
          iVar39 = iVar40;
          iVar40 = iVar40 + 1;
        }
      }
    }
    else {
      if (0 < param_6) {
        iVar39 = 0;
        fVar44 = _UNK_027edb34 / (float)param_6;
        do {
          iVar39 = iVar39 + 1;
          iVar40 = 0;
          fVar46 = ((float)iVar39 * param_1) / (float)param_5;
          uStack_c0 = (ulong)(uint)fVar49 << 0x20;
          do {
            fStack_cc = (float)((ulong)uStack_c0 >> 0x20);
            fVar57 = fVar44 * (float)iVar40;
            fVar47 = (float)cosf(fVar57);
            fVar45 = fVar46 * fVar47 + *pfVar2;
            uStack_c0 = CONCAT44(fVar49,fVar45);
            fVar47 = (float)sinf(fVar57);
            fVar47 = fVar46 * fVar47 + pfVar2[2];
            lVar32 = 0;
            if (*(long *)(param_3 + 0x358) != 0) {
              fVar57 = fVar45 * fVar45;
              fVar48 = fVar49 * fVar49;
              auVar9._4_4_ = fVar48;
              auVar9._0_4_ = fVar57;
              auVar9._8_4_ = fVar47 * fVar47;
              auVar9._12_4_ = 0;
              auVar10._4_4_ = fVar48;
              auVar10._0_4_ = fVar57;
              auVar10._8_4_ = fVar47 * fVar47;
              auVar10._12_4_ = 0;
              auVar41 = NEON_ext(auVar9,auVar10,8,1);
              uVar50 = NEON_rev64(CONCAT44(auVar41._0_4_ + auVar41._4_4_,fVar57 + fVar48),4);
              fVar57 = fVar57 + fVar48 + (float)uVar50;
              auVar24._8_4_ = fVar47;
              auVar24._0_8_ = uStack_c0;
              auVar24._12_4_ = 0x3f800000;
              auVar52 = NEON_fmax(auVar24,*(undefined1 (*) [16])(param_3 + 0x330),4);
              auVar11._4_4_ = fVar57;
              auVar11._0_4_ = fVar57;
              auVar11._8_4_ = fVar57;
              auVar11._12_4_ = fVar57;
              auVar41 = NEON_fmax(auVar11,*(undefined1 (*) [16])(param_3 + 0x330),4);
              *(long *)(param_3 + 0x338) = auVar52._8_8_;
              *(long *)(param_3 + 0x330) = auVar52._0_8_;
              *(int *)(param_3 + 0x33c) = auVar41._12_4_;
              auVar25._8_4_ = fVar47;
              auVar25._0_8_ = uStack_c0;
              auVar25._12_4_ = 0x3f800000;
              auVar41 = NEON_fmin(auVar25,*(undefined1 (*) [16])(param_3 + 0x340),4);
              *(long *)(param_3 + 0x348) = auVar41._8_8_;
              *(long *)(param_3 + 0x340) = auVar41._0_8_;
              pfVar31 = *(float **)(param_3 + 0x368);
              *pfVar31 = fVar45;
              pfVar31[1] = fStack_cc;
              pfVar31[2] = fVar47;
              pfVar31[3] = 0.0;
              pfVar31[4] = -1.0;
              pfVar31[5] = 0.0;
              pfVar31[6] = (float)(param_7 >> 0x10 & 0xff | param_7 & 0xff00ff00 |
                                  (param_7 & 0xff) << 0x10);
              lVar32 = *(long *)(param_3 + 0x358);
              *(ulong *)(param_3 + 0x368) =
                   *(long *)(param_3 + 0x368) + (ulong)*(ushort *)(*(long *)(lVar32 + 0x18) + 0x18);
              *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
            }
            iVar40 = iVar40 + 1;
          } while (iVar40 < param_6);
        } while (iVar39 != param_5);
        goto code_r0x0220beec;
      }
      bVar1 = false;
    }
    if (param_5 < 2) {
code_r0x0220c2cc:
      if (-1 < param_5) goto code_r0x0220c2d0;
    }
    else {
      if (bVar1) {
        iVar40 = 1;
        iVar39 = 1;
        do {
          iVar33 = 0;
          iVar34 = param_6 + iVar39 * param_6;
          do {
            iVar37 = param_6 + iVar40 + iVar33;
            if (*(long *)(param_3 + 0x358) != 0) {
              psVar36 = *(short **)(param_3 + 0x360);
              *(short **)(param_3 + 0x360) = psVar36 + 1;
              *psVar36 = (short)iVar34;
              psVar36 = *(short **)(param_3 + 0x360);
              sVar4 = (short)iVar34 - sVar28;
              *(short **)(param_3 + 0x360) = psVar36 + 1;
              *psVar36 = sVar4;
              puVar38 = *(undefined2 **)(param_3 + 0x360);
              *(undefined2 **)(param_3 + 0x360) = puVar38 + 1;
              uVar5 = (undefined2)iVar37;
              *puVar38 = uVar5;
              *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 3;
              if (*(long *)(param_3 + 0x358) != 0) {
                puVar38 = *(undefined2 **)(param_3 + 0x360);
                *(undefined2 **)(param_3 + 0x360) = puVar38 + 1;
                *puVar38 = uVar5;
                psVar36 = *(short **)(param_3 + 0x360);
                *(short **)(param_3 + 0x360) = psVar36 + 1;
                *psVar36 = sVar4;
                psVar36 = *(short **)(param_3 + 0x360);
                *(short **)(param_3 + 0x360) = psVar36 + 1;
                *psVar36 = (short)iVar40 + (short)iVar33;
                *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 3;
              }
            }
            iVar33 = iVar33 + 1;
            iVar34 = iVar37;
          } while (iVar33 < param_6);
          iVar39 = iVar39 + 1;
          iVar40 = iVar40 + param_6;
        } while (iVar39 != param_5);
        goto code_r0x0220c2cc;
      }
code_r0x0220c2d0:
      iVar39 = 0;
      fVar44 = _UNK_027edb34 / (float)param_6;
      do {
        if (bVar1) {
          iVar40 = 0;
          fVar46 = ((float)iVar39 * param_1) / (float)param_5;
          do {
            fVar49 = fVar44 * (float)iVar40;
            fVar47 = (float)cosf(fVar49);
            fVar49 = (float)sinf(fVar49);
            fVar57 = fVar46 * fVar47 + *pfVar2;
            fVar45 = (1.0 - (float)iVar39 / (float)param_5) * param_2 + pfVar2[1];
            fVar48 = fVar46 * fVar49 + pfVar2[2];
            if (*(long *)(param_3 + 0x358) != 0) {
              fVar54 = fVar57 * fVar57;
              fVar55 = fVar45 * fVar45;
              auVar15._4_4_ = fVar55;
              auVar15._0_4_ = fVar54;
              auVar15._8_4_ = fVar48 * fVar48;
              auVar15._12_4_ = 0;
              auVar16._4_4_ = fVar55;
              auVar16._0_4_ = fVar54;
              auVar16._8_4_ = fVar48 * fVar48;
              auVar16._12_4_ = 0;
              auVar41 = NEON_ext(auVar15,auVar16,8,1);
              uVar50 = NEON_rev64(CONCAT44(auVar41._0_4_ + auVar41._4_4_,fVar54 + fVar55),4);
              fVar54 = fVar54 + fVar55 + (float)uVar50;
              auVar26._4_4_ = fVar45;
              auVar26._0_4_ = fVar57;
              auVar26._8_4_ = fVar48;
              auVar26._12_4_ = 0x3f800000;
              auVar52 = NEON_fmax(auVar26,*(undefined1 (*) [16])(param_3 + 0x330),4);
              auVar17._4_4_ = fVar54;
              auVar17._0_4_ = fVar54;
              auVar17._8_4_ = fVar54;
              auVar17._12_4_ = fVar54;
              auVar41 = NEON_fmax(auVar17,*(undefined1 (*) [16])(param_3 + 0x330),4);
              *(long *)(param_3 + 0x338) = auVar52._8_8_;
              *(long *)(param_3 + 0x330) = auVar52._0_8_;
              *(int *)(param_3 + 0x33c) = auVar41._12_4_;
              pfVar31 = *(float **)(param_3 + 0x368);
              auVar27._4_4_ = fVar45;
              auVar27._0_4_ = fVar57;
              auVar27._8_4_ = fVar48;
              auVar27._12_4_ = 0x3f800000;
              auVar41 = NEON_fmin(auVar27,*(undefined1 (*) [16])(param_3 + 0x340),4);
              *(long *)(param_3 + 0x348) = auVar41._8_8_;
              *(long *)(param_3 + 0x340) = auVar41._0_8_;
              *pfVar31 = fVar57;
              pfVar31[1] = fVar45;
              pfVar31[2] = fVar48;
              pfVar31[3] = (fVar47 * param_2) / fVar56;
              pfVar31[4] = param_1 / fVar56;
              pfVar31[5] = (fVar49 * param_2) / fVar56;
              pfVar31[6] = (float)(param_7 >> 0x10 & 0xff | param_7 & 0xff00ff00 |
                                  (param_7 & 0xff) << 0x10);
              *(ulong *)(param_3 + 0x368) =
                   *(long *)(param_3 + 0x368) +
                   (ulong)*(ushort *)(*(long *)(*(long *)(param_3 + 0x358) + 0x18) + 0x18);
              *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
            }
            iVar40 = iVar40 + 1;
          } while (iVar40 < param_6);
        }
        bVar29 = iVar39 != param_5;
        iVar39 = iVar39 + 1;
      } while (bVar29);
    }
    if ((0 < param_5) && (bVar1)) {
      iVar39 = 0;
      iVar40 = param_5 * param_6 + 1;
      iVar33 = param_6 * (param_5 + 1) + 1;
      do {
        iVar34 = 0;
        iVar37 = param_6 * 2 + (iVar39 + param_5) * param_6;
        do {
          iVar35 = iVar33 + iVar34;
          if (*(long *)(param_3 + 0x358) != 0) {
            psVar36 = *(short **)(param_3 + 0x360);
            sVar4 = (short)iVar37 - sVar28;
            *(short **)(param_3 + 0x360) = psVar36 + 1;
            *psVar36 = sVar4;
            psVar36 = *(short **)(param_3 + 0x360);
            *(short **)(param_3 + 0x360) = psVar36 + 1;
            *psVar36 = (short)iVar37;
            puVar38 = *(undefined2 **)(param_3 + 0x360);
            *(undefined2 **)(param_3 + 0x360) = puVar38 + 1;
            uVar5 = (undefined2)iVar35;
            *puVar38 = uVar5;
            *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 3;
            if (*(long *)(param_3 + 0x358) != 0) {
              psVar36 = *(short **)(param_3 + 0x360);
              *(short **)(param_3 + 0x360) = psVar36 + 1;
              *psVar36 = sVar4;
              puVar38 = *(undefined2 **)(param_3 + 0x360);
              *(undefined2 **)(param_3 + 0x360) = puVar38 + 1;
              *puVar38 = uVar5;
              psVar36 = *(short **)(param_3 + 0x360);
              *(short **)(param_3 + 0x360) = psVar36 + 1;
              *psVar36 = (short)iVar40 + (short)iVar34;
              *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 3;
            }
          }
          iVar34 = iVar34 + 1;
          iVar37 = iVar35;
        } while (iVar34 < param_6);
        iVar39 = iVar39 + 1;
        iVar40 = iVar40 + param_6;
        iVar33 = iVar33 + param_6;
      } while (iVar39 != param_5);
    }
  }
  Aska::DirectAofHandler::EndMesh()(param_3);
  if ((param_9 & 1) != 0) {
    fStack_a4 = param_1;
    if (param_1 <= param_2) {
      fStack_a4 = param_2;
    }
    uStack_b0 = 0;
    uStack_a8 = 0;
    Aska::DirectAofHandler::Close(Aska::Vector const*, bool)(param_3,&uStack_b0,1);
  }
code_r0x0220c54c:
  *(char *)(param_4 + 2) = cVar3;
  return;
}

// ==== Aska::DirectAofHandler::Cylinder(Aska::DirectMaterial*, float, float, int, int, unsigned int, Aska::Vector const*, bool)
// vaddr 0x210c580 | ghidra 0x220c580 | size 4128 | symbol _ZN4Aska16DirectAofHandler8CylinderEPNS_14DirectMaterialEffiijPKNS_6VectorEb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16DirectAofHandler8CylinderEPNS_14DirectMaterialEffiijPKNS_6VectorEb
               (float param_1,float param_2,long param_3,long param_4,int param_5,int param_6,
               uint param_7,float *param_8,uint param_9)

{
  short sVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  char cVar5;
  ushort uVar6;
  short sVar7;
  short sVar8;
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  short sVar19;
  short sVar20;
  short sVar21;
  undefined4 uVar22;
  bool bVar23;
  ulong uVar24;
  long lVar25;
  undefined2 *puVar26;
  int iVar27;
  int iVar28;
  float *pfVar29;
  short *psVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  float fVar34;
  undefined1 auVar35 [16];
  float fVar36;
  float fVar37;
  undefined1 auVar38 [16];
  undefined1 auVar39 [16];
  undefined1 auVar40 [16];
  undefined1 auVar41 [16];
  undefined1 auVar42 [16];
  undefined1 auVar43 [16];
  undefined1 auVar44 [16];
  undefined1 auVar45 [16];
  undefined1 auVar46 [16];
  undefined1 auVar47 [16];
  undefined1 auVar48 [16];
  undefined1 auVar49 [16];
  undefined1 auVar50 [16];
  undefined8 uVar51;
  undefined1 auVar52 [16];
  undefined1 auVar53 [16];
  undefined1 auVar54 [16];
  undefined1 auVar55 [16];
  float fVar56;
  undefined1 auVar57 [16];
  undefined1 auVar58 [16];
  undefined1 auVar59 [16];
  undefined1 auVar60 [16];
  undefined1 auVar61 [16];
  undefined1 auVar62 [16];
  float fVar63;
  float fVar64;
  float fVar65;
  float fVar66;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined4 uStack_a8;
  float fStack_a4;
  
  if (param_6 < 4) {
    param_6 = 3;
  }
  cVar5 = *(char *)(param_4 + 2);
  pfVar4 = (float *)PTR__ZN4Aska6Vector10zeroVectorE_02cc0768;
  if (param_8 != (float *)0x0) {
    pfVar4 = param_8;
  }
  sVar8 = (short)param_6;
  if (cVar5 == '\x02') {
    iVar32 = param_6 * 2;
    uVar24 = Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)(param_3,param_4,param_6 * (param_5 * 3 + 1) + 2,
                             iVar32 * (param_5 * 3 + 4));
    if ((uVar24 & 1) == 0) goto code_r0x0220d56c;
    fVar66 = *pfVar4;
    fVar65 = pfVar4[2];
    fVar64 = param_2 * 0.5;
    fVar36 = fVar64 + pfVar4[1];
    auVar57._4_4_ = fVar36;
    auVar57._0_4_ = fVar66;
    auVar57._8_4_ = fVar65;
    auVar57._12_4_ = pfVar4[3];
    auVar58._8_8_ = auVar57._8_8_;
    if (*(long *)(param_3 + 0x358) == 0) {
      lVar25 = 0;
      auVar58._4_4_ = pfVar4[1] - fVar64;
      auVar58._0_4_ = fVar66;
    }
    else {
      auVar38._0_4_ = fVar66 * fVar66;
      auVar38._4_4_ = fVar36 * fVar36;
      auVar38._8_4_ = fVar65 * fVar65;
      auVar38._12_4_ = 0;
      auVar52 = NEON_ext(auVar38,auVar38,8,1);
      uVar51 = NEON_rev64(CONCAT44(auVar52._0_4_ + auVar52._4_4_,auVar38._0_4_ + auVar38._4_4_),4);
      auVar39._0_4_ = auVar38._0_4_ + auVar38._4_4_ + (float)uVar51;
      auVar39._4_4_ = auVar39._0_4_;
      auVar39._8_4_ = auVar39._0_4_;
      auVar39._12_4_ = auVar39._0_4_;
      auVar53 = NEON_fmax(auVar57,*(undefined1 (*) [16])(param_3 + 0x330),4);
      auVar52 = NEON_fmax(auVar39,*(undefined1 (*) [16])(param_3 + 0x330),4);
      *(long *)(param_3 + 0x338) = auVar53._8_8_;
      *(long *)(param_3 + 0x330) = auVar53._0_8_;
      *(undefined4 *)(param_3 + 0x33c) = auVar52._12_4_;
      pfVar29 = *(float **)(param_3 + 0x368);
      fVar34 = (float)(param_7 >> 0x10 & 0xff | param_7 & 0xff00ff00 | (param_7 & 0xff) << 0x10);
      auVar52 = NEON_fmin(auVar57,*(undefined1 (*) [16])(param_3 + 0x340),4);
      *(long *)(param_3 + 0x348) = auVar52._8_8_;
      *(long *)(param_3 + 0x340) = auVar52._0_8_;
      *pfVar29 = fVar66;
      pfVar29[1] = fVar36;
      pfVar29[2] = fVar65;
      pfVar29[3] = 0.0;
      pfVar29[4] = 1.0;
      pfVar29[5] = 0.0;
      pfVar29[6] = fVar34;
      pfVar29 = (float *)(*(long *)(param_3 + 0x368) +
                         (ulong)*(ushort *)(*(long *)(*(long *)(param_3 + 0x358) + 0x18) + 0x18));
      *(float **)(param_3 + 0x368) = pfVar29;
      *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
      fVar36 = pfVar4[1] - fVar64;
      auVar58._4_4_ = fVar36;
      auVar58._0_4_ = fVar66;
      if (*(long *)(param_3 + 0x358) == 0) {
        lVar25 = 0;
      }
      else {
        auVar40._0_4_ = fVar66 * fVar66;
        auVar40._4_4_ = fVar36 * fVar36;
        auVar40._8_4_ = fVar65 * fVar65;
        auVar40._12_4_ = 0;
        auVar52 = NEON_ext(auVar40,auVar40,8,1);
        uVar51 = NEON_rev64(CONCAT44(auVar52._0_4_ + auVar52._4_4_,auVar40._0_4_ + auVar40._4_4_),4)
        ;
        auVar35._0_4_ = auVar40._0_4_ + auVar40._4_4_ + (float)uVar51;
        auVar35._4_4_ = auVar35._0_4_;
        auVar35._8_4_ = auVar35._0_4_;
        auVar35._12_4_ = auVar35._0_4_;
        auVar41 = NEON_fmax(auVar58,*(undefined1 (*) [16])(param_3 + 0x330),4);
        auVar53 = NEON_fmin(auVar58,*(undefined1 (*) [16])(param_3 + 0x340),4);
        auVar52 = NEON_fmax(auVar35,*(undefined1 (*) [16])(param_3 + 0x330),4);
        *(long *)(param_3 + 0x338) = auVar41._8_8_;
        *(long *)(param_3 + 0x330) = auVar41._0_8_;
        *(long *)(param_3 + 0x348) = auVar53._8_8_;
        *(long *)(param_3 + 0x340) = auVar53._0_8_;
        *(undefined4 *)(param_3 + 0x33c) = auVar52._12_4_;
        *pfVar29 = fVar66;
        pfVar29[1] = fVar36;
        pfVar29[2] = fVar65;
        pfVar29[3] = 0.0;
        pfVar29[4] = -1.0;
        pfVar29[5] = 0.0;
        pfVar29[6] = fVar34;
        lVar25 = *(long *)(param_3 + 0x358);
        uVar6 = *(ushort *)(*(long *)(lVar25 + 0x18) + 0x18);
        *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
        *(ulong *)(param_3 + 0x368) = *(long *)(param_3 + 0x368) + (ulong)uVar6;
      }
    }
    uStack_b8 = auVar58._8_8_;
    uVar22 = auVar58._12_4_;
    if (0 < param_5) {
      iVar33 = 0;
      fVar66 = (float)(param_7 >> 0x10 & 0xff | param_7 & 0xff00ff00 | (param_7 & 0xff) << 0x10);
      fVar65 = _UNK_027edb34 / (float)param_6;
      do {
        iVar33 = iVar33 + 1;
        if (0 < param_6) {
          iVar31 = 0;
          fVar36 = ((float)iVar33 * param_1) / (float)param_5;
          do {
            fVar63 = fVar65 * (float)iVar31;
            fVar34 = (float)cosf(fVar63);
            fVar34 = fVar36 * fVar34 + *pfVar4;
            fVar63 = (float)sinf(fVar63);
            fVar63 = fVar36 * fVar63 + pfVar4[2];
            fVar37 = fVar64 + pfVar4[1];
            auVar59._4_4_ = fVar37;
            auVar59._0_4_ = fVar34;
            auVar59._8_4_ = fVar63;
            auVar59._12_4_ = uStack_b8._4_4_;
            auVar60._8_8_ = auVar59._8_8_;
            if (*(long *)(param_3 + 0x358) == 0) {
              lVar25 = 0;
            }
            else {
              auVar43._0_4_ = fVar34 * fVar34;
              auVar43._4_4_ = fVar37 * fVar37;
              auVar43._8_4_ = fVar63 * fVar63;
              auVar43._12_4_ = 0;
              auVar52 = NEON_ext(auVar43,auVar43,8,1);
              uVar51 = NEON_rev64(CONCAT44(auVar52._0_4_ + auVar52._4_4_,
                                           auVar43._0_4_ + auVar43._4_4_),4);
              auVar44._0_4_ = auVar43._0_4_ + auVar43._4_4_ + (float)uVar51;
              auVar44._4_4_ = auVar44._0_4_;
              auVar44._8_4_ = auVar44._0_4_;
              auVar44._12_4_ = auVar44._0_4_;
              auVar53 = NEON_fmax(auVar59,*(undefined1 (*) [16])(param_3 + 0x330),4);
              auVar52 = NEON_fmax(auVar44,*(undefined1 (*) [16])(param_3 + 0x330),4);
              *(long *)(param_3 + 0x338) = auVar53._8_8_;
              *(long *)(param_3 + 0x330) = auVar53._0_8_;
              *(undefined4 *)(param_3 + 0x33c) = auVar52._12_4_;
              auVar52 = NEON_fmin(auVar59,*(undefined1 (*) [16])(param_3 + 0x340),4);
              *(long *)(param_3 + 0x348) = auVar52._8_8_;
              *(long *)(param_3 + 0x340) = auVar52._0_8_;
              pfVar29 = *(float **)(param_3 + 0x368);
              pfVar29[2] = fVar63;
              *pfVar29 = fVar34;
              pfVar29[1] = fVar37;
              pfVar29[3] = 0.0;
              pfVar29[4] = 1.0;
              pfVar29[5] = 0.0;
              pfVar29[6] = fVar66;
              pfVar29 = (float *)(*(long *)(param_3 + 0x368) +
                                 (ulong)*(ushort *)
                                         (*(long *)(*(long *)(param_3 + 0x358) + 0x18) + 0x18));
              *(float **)(param_3 + 0x368) = pfVar29;
              *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
              fVar37 = pfVar4[1] - fVar64;
              auVar60._4_4_ = fVar37;
              auVar60._0_4_ = fVar34;
              if (*(long *)(param_3 + 0x358) == 0) {
                lVar25 = 0;
              }
              else {
                auVar45._0_4_ = fVar34 * fVar34;
                auVar45._4_4_ = fVar37 * fVar37;
                auVar45._8_4_ = fVar63 * fVar63;
                auVar45._12_4_ = 0;
                auVar52 = NEON_ext(auVar45,auVar45,8,1);
                uVar51 = NEON_rev64(CONCAT44(auVar52._0_4_ + auVar52._4_4_,
                                             auVar45._0_4_ + auVar45._4_4_),4);
                auVar46._0_4_ = auVar45._0_4_ + auVar45._4_4_ + (float)uVar51;
                auVar46._4_4_ = auVar46._0_4_;
                auVar46._8_4_ = auVar46._0_4_;
                auVar46._12_4_ = auVar46._0_4_;
                auVar41 = NEON_fmax(auVar60,*(undefined1 (*) [16])(param_3 + 0x330),4);
                auVar53 = NEON_fmin(auVar60,*(undefined1 (*) [16])(param_3 + 0x340),4);
                auVar52 = NEON_fmax(auVar46,*(undefined1 (*) [16])(param_3 + 0x330),4);
                *(long *)(param_3 + 0x338) = auVar41._8_8_;
                *(long *)(param_3 + 0x330) = auVar41._0_8_;
                *(long *)(param_3 + 0x348) = auVar53._8_8_;
                *(long *)(param_3 + 0x340) = auVar53._0_8_;
                *(undefined4 *)(param_3 + 0x33c) = auVar52._12_4_;
                *pfVar29 = fVar34;
                pfVar29[1] = fVar37;
                pfVar29[2] = fVar63;
                pfVar29[3] = 0.0;
                pfVar29[4] = -1.0;
                pfVar29[5] = 0.0;
                pfVar29[6] = fVar66;
                lVar25 = *(long *)(param_3 + 0x358);
                *(ulong *)(param_3 + 0x368) =
                     *(long *)(param_3 + 0x368) +
                     (ulong)*(ushort *)(*(long *)(lVar25 + 0x18) + 0x18);
                *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
              }
            }
            iVar31 = iVar31 + 1;
            uStack_b8 = auVar60._8_8_;
          } while (iVar31 < param_6);
        }
        uVar22 = uStack_b8._4_4_;
      } while (iVar33 != param_5);
    }
    uStack_b8._4_4_ = uVar22;
    if (0 < param_6) {
      iVar31 = 1;
      iVar33 = param_6 * (param_5 + -1) * 2 + 3;
      while( true ) {
        if (lVar25 != 0) {
          puVar26 = *(undefined2 **)(param_3 + 0x360);
          *(undefined2 **)(param_3 + 0x360) = puVar26 + 1;
          *puVar26 = 0;
          psVar30 = *(short **)(param_3 + 0x360);
          *(short **)(param_3 + 0x360) = psVar30 + 1;
          *psVar30 = (short)iVar33 + -1;
          *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
          if (*(long *)(param_3 + 0x358) != 0) {
            puVar26 = *(undefined2 **)(param_3 + 0x360);
            *(undefined2 **)(param_3 + 0x360) = puVar26 + 1;
            *puVar26 = 1;
            psVar30 = *(short **)(param_3 + 0x360);
            *(short **)(param_3 + 0x360) = psVar30 + 1;
            *psVar30 = (short)iVar33;
            *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
          }
        }
        if (param_6 <= iVar31) break;
        lVar25 = *(long *)(param_3 + 0x358);
        iVar31 = iVar31 + 1;
        iVar33 = iVar33 + 2;
      }
    }
    if (param_5 < 1) {
code_r0x0220cca4:
      if (-1 < param_5) goto code_r0x0220cca8;
      bVar23 = true;
    }
    else {
      if (0 < param_6) {
        iVar31 = 0;
        iVar33 = 0;
        sVar7 = sVar8 * -2;
        do {
          iVar27 = 0;
          iVar28 = 0;
          do {
            if (*(long *)(param_3 + 0x358) != 0) {
              psVar30 = *(short **)(param_3 + 0x360);
              sVar21 = (short)iVar31;
              sVar19 = (short)iVar28;
              *(short **)(param_3 + 0x360) = psVar30 + 1;
              *psVar30 = sVar21 + sVar19 + 2;
              psVar30 = *(short **)(param_3 + 0x360);
              sVar20 = 0;
              if (iVar32 <= iVar28 + 2) {
                sVar20 = sVar7;
              }
              *(short **)(param_3 + 0x360) = psVar30 + 1;
              *psVar30 = sVar21 + sVar20 + sVar19 + 4;
              *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
              if (*(long *)(param_3 + 0x358) != 0) {
                psVar30 = *(short **)(param_3 + 0x360);
                sVar20 = 0;
                if (iVar32 <= iVar28 + 3) {
                  sVar20 = sVar7;
                }
                *(short **)(param_3 + 0x360) = psVar30 + 1;
                sVar1 = 0;
                if (iVar32 <= iVar28 + 1) {
                  sVar1 = sVar7;
                }
                *psVar30 = sVar21 + sVar1 + sVar19 + 3;
                psVar30 = *(short **)(param_3 + 0x360);
                *(short **)(param_3 + 0x360) = psVar30 + 1;
                *psVar30 = sVar21 + sVar20 + sVar19 + 5;
                *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
              }
            }
            iVar27 = iVar27 + 1;
            iVar28 = iVar28 + 2;
          } while (iVar27 < param_6);
          iVar33 = iVar33 + 1;
          iVar31 = iVar31 + iVar32;
        } while (iVar33 != param_5);
        goto code_r0x0220cca4;
      }
code_r0x0220cca8:
      if (param_6 < 1) goto code_r0x0220d524;
      iVar32 = 0;
      fVar66 = _UNK_027edb34 / (float)param_6;
      do {
        iVar33 = 0;
        do {
          fVar36 = fVar66 * (float)iVar33;
          fVar65 = (float)cosf(fVar36);
          fVar36 = (float)sinf(fVar36);
          fVar34 = fVar65 * param_1 + *pfVar4;
          fVar64 = ((float)iVar32 / (float)param_5 + -0.5) * param_2 + pfVar4[1];
          fVar63 = fVar36 * param_1 + pfVar4[2];
          if (*(long *)(param_3 + 0x358) != 0) {
            fVar37 = fVar34 * fVar34;
            fVar56 = fVar64 * fVar64;
            auVar9._4_4_ = fVar56;
            auVar9._0_4_ = fVar37;
            auVar9._8_4_ = fVar63 * fVar63;
            auVar9._12_4_ = 0;
            auVar10._4_4_ = fVar56;
            auVar10._0_4_ = fVar37;
            auVar10._8_4_ = fVar63 * fVar63;
            auVar10._12_4_ = 0;
            auVar52 = NEON_ext(auVar9,auVar10,8,1);
            uVar51 = NEON_rev64(CONCAT44(auVar52._0_4_ + auVar52._4_4_,fVar37 + fVar56),4);
            fVar37 = fVar37 + fVar56 + (float)uVar51;
            auVar15._4_4_ = fVar64;
            auVar15._0_4_ = fVar34;
            auVar15._8_4_ = fVar63;
            auVar15._12_4_ = uStack_b8._4_4_;
            auVar53 = NEON_fmax(auVar15,*(undefined1 (*) [16])(param_3 + 0x330),4);
            auVar11._4_4_ = fVar37;
            auVar11._0_4_ = fVar37;
            auVar11._8_4_ = fVar37;
            auVar11._12_4_ = fVar37;
            auVar52 = NEON_fmax(auVar11,*(undefined1 (*) [16])(param_3 + 0x330),4);
            *(long *)(param_3 + 0x338) = auVar53._8_8_;
            *(long *)(param_3 + 0x330) = auVar53._0_8_;
            *(int *)(param_3 + 0x33c) = auVar52._12_4_;
            pfVar29 = *(float **)(param_3 + 0x368);
            auVar16._4_4_ = fVar64;
            auVar16._0_4_ = fVar34;
            auVar16._8_4_ = fVar63;
            auVar16._12_4_ = uStack_b8._4_4_;
            auVar52 = NEON_fmin(auVar16,*(undefined1 (*) [16])(param_3 + 0x340),4);
            *(long *)(param_3 + 0x348) = auVar52._8_8_;
            *(long *)(param_3 + 0x340) = auVar52._0_8_;
            *pfVar29 = fVar34;
            pfVar29[1] = fVar64;
            pfVar29[2] = fVar63;
            pfVar29[3] = fVar65;
            pfVar29[4] = 0.0;
            pfVar29[5] = fVar36;
            pfVar29[6] = (float)(param_7 >> 0x10 & 0xff | param_7 & 0xff00ff00 |
                                (param_7 & 0xff) << 0x10);
            *(ulong *)(param_3 + 0x368) =
                 *(long *)(param_3 + 0x368) +
                 (ulong)*(ushort *)(*(long *)(*(long *)(param_3 + 0x358) + 0x18) + 0x18);
            *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
          }
          iVar33 = iVar33 + 1;
        } while (iVar33 < param_6);
        bVar23 = iVar32 != param_5;
        iVar32 = iVar32 + 1;
      } while (bVar23);
      bVar23 = false;
    }
    iVar32 = param_6 * param_5 * 2;
    if (0 < param_6) {
      iVar33 = 0;
      do {
        if (*(long *)(param_3 + 0x358) != 0) {
          psVar30 = *(short **)(param_3 + 0x360);
          *(short **)(param_3 + 0x360) = psVar30 + 1;
          *psVar30 = (short)iVar32 + 2 + (short)iVar33;
          psVar30 = *(short **)(param_3 + 0x360);
          *(short **)(param_3 + 0x360) = psVar30 + 1;
          *psVar30 = (short)param_5 * sVar8 * 3 + 2 + (short)iVar33;
          *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
        }
        iVar33 = iVar33 + 1;
      } while (iVar33 < param_6);
    }
    if ((!bVar23) && (0 < param_6)) {
      iVar33 = 0;
      do {
        iVar31 = 0;
        do {
          iVar27 = iVar31 + 1;
          if (*(long *)(param_3 + 0x358) != 0) {
            psVar30 = *(short **)(param_3 + 0x360);
            *(short **)(param_3 + 0x360) = psVar30 + 1;
            *psVar30 = (short)iVar32 + (short)iVar31 + 2;
            psVar30 = *(short **)(param_3 + 0x360);
            sVar7 = 0;
            if (param_6 <= iVar27) {
              sVar7 = -sVar8;
            }
            *(short **)(param_3 + 0x360) = psVar30 + 1;
            *psVar30 = (short)iVar32 + sVar7 + (short)iVar31 + 3;
            *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 2;
          }
          iVar31 = iVar27;
        } while (iVar27 < param_6);
        bVar23 = iVar33 != param_5;
        iVar33 = iVar33 + 1;
        iVar32 = iVar32 + param_6;
      } while (bVar23);
    }
  }
  else {
    *(undefined1 *)(param_4 + 2) = 0;
    uVar24 = Aska::DirectAofHandler::BeginMesh(Aska::DirectMaterial*, int, int)(param_3,param_4,param_6 * (param_5 * 3 + 1) + 2,
                             (param_5 * 0xc + 8) * param_6);
    if ((uVar24 & 1) == 0) goto code_r0x0220d56c;
    fVar66 = *pfVar4;
    fVar65 = pfVar4[2];
    fVar64 = param_2 * 0.5;
    fVar36 = fVar64 + pfVar4[1];
    auVar52._4_4_ = fVar36;
    auVar52._0_4_ = fVar66;
    auVar52._8_4_ = fVar65;
    auVar52._12_4_ = pfVar4[3];
    auVar53._8_8_ = auVar52._8_8_;
    if (*(long *)(param_3 + 0x358) == 0) {
      lVar25 = 0;
      auVar53._4_4_ = pfVar4[1] - fVar64;
      auVar53._0_4_ = fVar66;
    }
    else {
      auVar41._0_4_ = fVar66 * fVar66;
      auVar41._4_4_ = fVar36 * fVar36;
      auVar41._8_4_ = fVar65 * fVar65;
      auVar41._12_4_ = 0;
      auVar54 = NEON_ext(auVar41,auVar41,8,1);
      uVar51 = NEON_rev64(CONCAT44(auVar54._0_4_ + auVar54._4_4_,auVar41._0_4_ + auVar41._4_4_),4);
      auVar54._0_4_ = auVar41._0_4_ + auVar41._4_4_ + (float)uVar51;
      auVar54._4_4_ = auVar54._0_4_;
      auVar54._8_4_ = auVar54._0_4_;
      auVar54._12_4_ = auVar54._0_4_;
      auVar55 = NEON_fmax(auVar52,*(undefined1 (*) [16])(param_3 + 0x330),4);
      auVar41 = NEON_fmax(auVar54,*(undefined1 (*) [16])(param_3 + 0x330),4);
      *(long *)(param_3 + 0x338) = auVar55._8_8_;
      *(long *)(param_3 + 0x330) = auVar55._0_8_;
      *(undefined4 *)(param_3 + 0x33c) = auVar41._12_4_;
      pfVar29 = *(float **)(param_3 + 0x368);
      fVar34 = (float)(param_7 >> 0x10 & 0xff | param_7 & 0xff00ff00 | (param_7 & 0xff) << 0x10);
      auVar52 = NEON_fmin(auVar52,*(undefined1 (*) [16])(param_3 + 0x340),4);
      *(long *)(param_3 + 0x348) = auVar52._8_8_;
      *(long *)(param_3 + 0x340) = auVar52._0_8_;
      *pfVar29 = fVar66;
      pfVar29[1] = fVar36;
      pfVar29[2] = fVar65;
      pfVar29[3] = 0.0;
      pfVar29[4] = 1.0;
      pfVar29[5] = 0.0;
      pfVar29[6] = fVar34;
      pfVar29 = (float *)(*(long *)(param_3 + 0x368) +
                         (ulong)*(ushort *)(*(long *)(*(long *)(param_3 + 0x358) + 0x18) + 0x18));
      *(float **)(param_3 + 0x368) = pfVar29;
      *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
      fVar36 = pfVar4[1] - fVar64;
      auVar53._4_4_ = fVar36;
      auVar53._0_4_ = fVar66;
      if (*(long *)(param_3 + 0x358) == 0) {
        lVar25 = 0;
      }
      else {
        auVar42._0_4_ = fVar66 * fVar66;
        auVar42._4_4_ = fVar36 * fVar36;
        auVar42._8_4_ = fVar65 * fVar65;
        auVar42._12_4_ = 0;
        auVar52 = NEON_ext(auVar42,auVar42,8,1);
        uVar51 = NEON_rev64(CONCAT44(auVar52._0_4_ + auVar52._4_4_,auVar42._0_4_ + auVar42._4_4_),4)
        ;
        auVar55._0_4_ = auVar42._0_4_ + auVar42._4_4_ + (float)uVar51;
        auVar55._4_4_ = auVar55._0_4_;
        auVar55._8_4_ = auVar55._0_4_;
        auVar55._12_4_ = auVar55._0_4_;
        auVar54 = NEON_fmax(auVar53,*(undefined1 (*) [16])(param_3 + 0x330),4);
        auVar41 = NEON_fmin(auVar53,*(undefined1 (*) [16])(param_3 + 0x340),4);
        auVar52 = NEON_fmax(auVar55,*(undefined1 (*) [16])(param_3 + 0x330),4);
        *(long *)(param_3 + 0x338) = auVar54._8_8_;
        *(long *)(param_3 + 0x330) = auVar54._0_8_;
        *(long *)(param_3 + 0x348) = auVar41._8_8_;
        *(long *)(param_3 + 0x340) = auVar41._0_8_;
        *(undefined4 *)(param_3 + 0x33c) = auVar52._12_4_;
        *pfVar29 = fVar66;
        pfVar29[1] = fVar36;
        pfVar29[2] = fVar65;
        pfVar29[3] = 0.0;
        pfVar29[4] = -1.0;
        pfVar29[5] = 0.0;
        pfVar29[6] = fVar34;
        lVar25 = *(long *)(param_3 + 0x358);
        uVar6 = *(ushort *)(*(long *)(lVar25 + 0x18) + 0x18);
        *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
        *(ulong *)(param_3 + 0x368) = *(long *)(param_3 + 0x368) + (ulong)uVar6;
      }
    }
    uStack_b8 = auVar53._8_8_;
    uVar22 = auVar53._12_4_;
    if (0 < param_5) {
      iVar32 = 0;
      fVar66 = (float)(param_7 >> 0x10 & 0xff | param_7 & 0xff00ff00 | (param_7 & 0xff) << 0x10);
      fVar65 = _UNK_027edb34 / (float)param_6;
      do {
        iVar32 = iVar32 + 1;
        if (0 < param_6) {
          iVar33 = 0;
          fVar36 = ((float)iVar32 * param_1) / (float)param_5;
          do {
            fVar63 = fVar65 * (float)iVar33;
            fVar34 = (float)cosf(fVar63);
            fVar34 = fVar36 * fVar34 + *pfVar4;
            fVar63 = (float)sinf(fVar63);
            fVar63 = fVar36 * fVar63 + pfVar4[2];
            fVar37 = fVar64 + pfVar4[1];
            auVar61._4_4_ = fVar37;
            auVar61._0_4_ = fVar34;
            auVar61._8_4_ = fVar63;
            auVar61._12_4_ = uStack_b8._4_4_;
            auVar62._8_8_ = auVar61._8_8_;
            if (*(long *)(param_3 + 0x358) == 0) {
              lVar25 = 0;
            }
            else {
              auVar47._0_4_ = fVar34 * fVar34;
              auVar47._4_4_ = fVar37 * fVar37;
              auVar47._8_4_ = fVar63 * fVar63;
              auVar47._12_4_ = 0;
              auVar52 = NEON_ext(auVar47,auVar47,8,1);
              uVar51 = NEON_rev64(CONCAT44(auVar52._0_4_ + auVar52._4_4_,
                                           auVar47._0_4_ + auVar47._4_4_),4);
              auVar48._0_4_ = auVar47._0_4_ + auVar47._4_4_ + (float)uVar51;
              auVar48._4_4_ = auVar48._0_4_;
              auVar48._8_4_ = auVar48._0_4_;
              auVar48._12_4_ = auVar48._0_4_;
              auVar53 = NEON_fmax(auVar61,*(undefined1 (*) [16])(param_3 + 0x330),4);
              auVar52 = NEON_fmax(auVar48,*(undefined1 (*) [16])(param_3 + 0x330),4);
              *(long *)(param_3 + 0x338) = auVar53._8_8_;
              *(long *)(param_3 + 0x330) = auVar53._0_8_;
              *(undefined4 *)(param_3 + 0x33c) = auVar52._12_4_;
              auVar52 = NEON_fmin(auVar61,*(undefined1 (*) [16])(param_3 + 0x340),4);
              *(long *)(param_3 + 0x348) = auVar52._8_8_;
              *(long *)(param_3 + 0x340) = auVar52._0_8_;
              pfVar29 = *(float **)(param_3 + 0x368);
              pfVar29[2] = fVar63;
              *pfVar29 = fVar34;
              pfVar29[1] = fVar37;
              pfVar29[3] = 0.0;
              pfVar29[4] = 1.0;
              pfVar29[5] = 0.0;
              pfVar29[6] = fVar66;
              pfVar29 = (float *)(*(long *)(param_3 + 0x368) +
                                 (ulong)*(ushort *)
                                         (*(long *)(*(long *)(param_3 + 0x358) + 0x18) + 0x18));
              *(float **)(param_3 + 0x368) = pfVar29;
              *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
              fVar37 = pfVar4[1] - fVar64;
              auVar62._4_4_ = fVar37;
              auVar62._0_4_ = fVar34;
              if (*(long *)(param_3 + 0x358) == 0) {
                lVar25 = 0;
              }
              else {
                auVar49._0_4_ = fVar34 * fVar34;
                auVar49._4_4_ = fVar37 * fVar37;
                auVar49._8_4_ = fVar63 * fVar63;
                auVar49._12_4_ = 0;
                auVar52 = NEON_ext(auVar49,auVar49,8,1);
                uVar51 = NEON_rev64(CONCAT44(auVar52._0_4_ + auVar52._4_4_,
                                             auVar49._0_4_ + auVar49._4_4_),4);
                auVar50._0_4_ = auVar49._0_4_ + auVar49._4_4_ + (float)uVar51;
                auVar50._4_4_ = auVar50._0_4_;
                auVar50._8_4_ = auVar50._0_4_;
                auVar50._12_4_ = auVar50._0_4_;
                auVar41 = NEON_fmax(auVar62,*(undefined1 (*) [16])(param_3 + 0x330),4);
                auVar53 = NEON_fmin(auVar62,*(undefined1 (*) [16])(param_3 + 0x340),4);
                auVar52 = NEON_fmax(auVar50,*(undefined1 (*) [16])(param_3 + 0x330),4);
                *(long *)(param_3 + 0x338) = auVar41._8_8_;
                *(long *)(param_3 + 0x330) = auVar41._0_8_;
                *(long *)(param_3 + 0x348) = auVar53._8_8_;
                *(long *)(param_3 + 0x340) = auVar53._0_8_;
                *(undefined4 *)(param_3 + 0x33c) = auVar52._12_4_;
                *pfVar29 = fVar34;
                pfVar29[1] = fVar37;
                pfVar29[2] = fVar63;
                pfVar29[3] = 0.0;
                pfVar29[4] = -1.0;
                pfVar29[5] = 0.0;
                pfVar29[6] = fVar66;
                lVar25 = *(long *)(param_3 + 0x358);
                *(ulong *)(param_3 + 0x368) =
                     *(long *)(param_3 + 0x368) +
                     (ulong)*(ushort *)(*(long *)(lVar25 + 0x18) + 0x18);
                *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
              }
            }
            iVar33 = iVar33 + 1;
            uStack_b8 = auVar62._8_8_;
          } while (iVar33 < param_6);
        }
        uVar22 = uStack_b8._4_4_;
      } while (iVar32 != param_5);
    }
    uStack_b8._4_4_ = uVar22;
    if (0 < param_6) {
      iVar31 = param_6 * 2;
      iVar33 = 5;
      sVar7 = sVar8 * -2;
      iVar32 = 1;
      while( true ) {
        if (lVar25 != 0) {
          puVar26 = *(undefined2 **)(param_3 + 0x360);
          *(undefined2 **)(param_3 + 0x360) = puVar26 + 1;
          *puVar26 = 0;
          puVar26 = *(undefined2 **)(param_3 + 0x360);
          *(undefined2 **)(param_3 + 0x360) = puVar26 + 1;
          *puVar26 = (short)(iVar33 + -3);
          psVar30 = *(short **)(param_3 + 0x360);
          sVar20 = 0;
          if (iVar31 <= iVar33 + -3) {
            sVar20 = sVar7;
          }
          sVar21 = (short)iVar33;
          *(short **)(param_3 + 0x360) = psVar30 + 1;
          *psVar30 = sVar20 + sVar21 + -1;
          *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 3;
          if (*(long *)(param_3 + 0x358) != 0) {
            puVar26 = *(undefined2 **)(param_3 + 0x360);
            *(undefined2 **)(param_3 + 0x360) = puVar26 + 1;
            *puVar26 = 1;
            psVar30 = *(short **)(param_3 + 0x360);
            sVar20 = 0;
            if (iVar31 <= iVar33 + -4) {
              sVar20 = sVar7;
            }
            sVar19 = 0;
            if (iVar31 <= iVar33 + -2) {
              sVar19 = sVar7;
            }
            *(short **)(param_3 + 0x360) = psVar30 + 1;
            *psVar30 = sVar19 + sVar21;
            psVar30 = *(short **)(param_3 + 0x360);
            *(short **)(param_3 + 0x360) = psVar30 + 1;
            *psVar30 = sVar20 + sVar21 + -2;
            *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 3;
          }
        }
        if (param_6 <= iVar32) break;
        lVar25 = *(long *)(param_3 + 0x358);
        iVar32 = iVar32 + 1;
        iVar33 = iVar33 + 2;
      }
    }
    if (param_5 < 2) {
code_r0x0220d2f0:
      if (-1 < param_5) goto code_r0x0220d2f4;
    }
    else {
      if (0 < param_6) {
        iVar31 = param_6 * 2;
        iVar33 = 0;
        iVar32 = 1;
        do {
          iVar27 = 0;
          sVar7 = (short)iVar31 + (short)iVar33;
          iVar28 = 0;
          do {
            iVar2 = 0;
            if (iVar31 <= iVar28 + 2) {
              iVar2 = iVar31;
            }
            iVar3 = 0;
            if (iVar31 <= iVar28 + 1) {
              iVar3 = iVar31;
            }
            if (*(long *)(param_3 + 0x358) != 0) {
              psVar30 = *(short **)(param_3 + 0x360);
              sVar19 = (short)iVar28;
              sVar20 = (short)iVar33 + sVar19;
              *(short **)(param_3 + 0x360) = psVar30 + 1;
              *psVar30 = (sVar20 - (short)iVar2) + 4;
              psVar30 = *(short **)(param_3 + 0x360);
              sVar21 = sVar7 + sVar19;
              *(short **)(param_3 + 0x360) = psVar30 + 1;
              *psVar30 = sVar21 + 2;
              psVar30 = *(short **)(param_3 + 0x360);
              *(short **)(param_3 + 0x360) = psVar30 + 1;
              *psVar30 = (sVar21 - (short)iVar2) + 4;
              *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 3;
              if (*(long *)(param_3 + 0x358) != 0) {
                psVar30 = *(short **)(param_3 + 0x360);
                *(short **)(param_3 + 0x360) = psVar30 + 1;
                *psVar30 = (sVar20 - (short)iVar3) + 3;
                psVar30 = *(short **)(param_3 + 0x360);
                sVar20 = 0;
                if (iVar31 <= iVar28 + 3) {
                  sVar20 = sVar8 * -2;
                }
                *(short **)(param_3 + 0x360) = psVar30 + 1;
                *psVar30 = sVar7 + sVar20 + sVar19 + 5;
                psVar30 = *(short **)(param_3 + 0x360);
                *(short **)(param_3 + 0x360) = psVar30 + 1;
                *psVar30 = (sVar21 - (short)iVar3) + 3;
                *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 3;
              }
            }
            iVar27 = iVar27 + 1;
            iVar28 = iVar28 + 2;
          } while (iVar27 < param_6);
          iVar32 = iVar32 + 1;
          iVar33 = iVar33 + iVar31;
        } while (iVar32 != param_5);
        goto code_r0x0220d2f0;
      }
code_r0x0220d2f4:
      if (0 < param_6) {
        iVar32 = 0;
        fVar66 = _UNK_027edb34 / (float)param_6;
        do {
          iVar33 = 0;
          do {
            fVar36 = fVar66 * (float)iVar33;
            fVar65 = (float)cosf(fVar36);
            fVar36 = (float)sinf(fVar36);
            fVar34 = fVar65 * param_1 + *pfVar4;
            fVar64 = ((float)iVar32 / (float)param_5 + -0.5) * param_2 + pfVar4[1];
            fVar63 = fVar36 * param_1 + pfVar4[2];
            if (*(long *)(param_3 + 0x358) != 0) {
              fVar37 = fVar34 * fVar34;
              fVar56 = fVar64 * fVar64;
              auVar12._4_4_ = fVar56;
              auVar12._0_4_ = fVar37;
              auVar12._8_4_ = fVar63 * fVar63;
              auVar12._12_4_ = 0;
              auVar13._4_4_ = fVar56;
              auVar13._0_4_ = fVar37;
              auVar13._8_4_ = fVar63 * fVar63;
              auVar13._12_4_ = 0;
              auVar52 = NEON_ext(auVar12,auVar13,8,1);
              uVar51 = NEON_rev64(CONCAT44(auVar52._0_4_ + auVar52._4_4_,fVar37 + fVar56),4);
              fVar37 = fVar37 + fVar56 + (float)uVar51;
              auVar17._4_4_ = fVar64;
              auVar17._0_4_ = fVar34;
              auVar17._8_4_ = fVar63;
              auVar17._12_4_ = uStack_b8._4_4_;
              auVar53 = NEON_fmax(auVar17,*(undefined1 (*) [16])(param_3 + 0x330),4);
              auVar14._4_4_ = fVar37;
              auVar14._0_4_ = fVar37;
              auVar14._8_4_ = fVar37;
              auVar14._12_4_ = fVar37;
              auVar52 = NEON_fmax(auVar14,*(undefined1 (*) [16])(param_3 + 0x330),4);
              *(long *)(param_3 + 0x338) = auVar53._8_8_;
              *(long *)(param_3 + 0x330) = auVar53._0_8_;
              *(int *)(param_3 + 0x33c) = auVar52._12_4_;
              pfVar29 = *(float **)(param_3 + 0x368);
              auVar18._4_4_ = fVar64;
              auVar18._0_4_ = fVar34;
              auVar18._8_4_ = fVar63;
              auVar18._12_4_ = uStack_b8._4_4_;
              auVar52 = NEON_fmin(auVar18,*(undefined1 (*) [16])(param_3 + 0x340),4);
              *(long *)(param_3 + 0x348) = auVar52._8_8_;
              *(long *)(param_3 + 0x340) = auVar52._0_8_;
              *pfVar29 = fVar34;
              pfVar29[1] = fVar64;
              pfVar29[2] = fVar63;
              pfVar29[3] = fVar65;
              pfVar29[4] = 0.0;
              pfVar29[5] = fVar36;
              pfVar29[6] = (float)(param_7 >> 0x10 & 0xff | param_7 & 0xff00ff00 |
                                  (param_7 & 0xff) << 0x10);
              *(ulong *)(param_3 + 0x368) =
                   *(long *)(param_3 + 0x368) +
                   (ulong)*(ushort *)(*(long *)(*(long *)(param_3 + 0x358) + 0x18) + 0x18);
              *(int *)(param_3 + 0x374) = *(int *)(param_3 + 0x374) + 1;
            }
            iVar33 = iVar33 + 1;
          } while (iVar33 < param_6);
          bVar23 = iVar32 != param_5;
          iVar32 = iVar32 + 1;
        } while (bVar23);
      }
    }
    if ((0 < param_5) && (0 < param_6)) {
      iVar31 = param_5 * 2 * param_6;
      iVar32 = 0;
      iVar33 = param_6 * (param_5 * 2 + 1);
      do {
        iVar32 = iVar32 + 1;
        iVar27 = 1;
        do {
          iVar28 = 0;
          if (param_6 <= iVar27) {
            iVar28 = param_6;
          }
          if (*(long *)(param_3 + 0x358) != 0) {
            psVar30 = *(short **)(param_3 + 0x360);
            sVar7 = (short)iVar31 + (short)iVar27;
            sVar8 = sVar7 + 1;
            *(short **)(param_3 + 0x360) = psVar30 + 1;
            *psVar30 = sVar8;
            psVar30 = *(short **)(param_3 + 0x360);
            *(short **)(param_3 + 0x360) = psVar30 + 1;
            *psVar30 = (sVar7 - (short)iVar28) + 2;
            psVar30 = *(short **)(param_3 + 0x360);
            sVar20 = (short)iVar33 + (short)iVar27;
            sVar7 = (sVar20 - (short)iVar28) + 2;
            *(short **)(param_3 + 0x360) = psVar30 + 1;
            *psVar30 = sVar7;
            *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 3;
            if (*(long *)(param_3 + 0x358) != 0) {
              psVar30 = *(short **)(param_3 + 0x360);
              *(short **)(param_3 + 0x360) = psVar30 + 1;
              *psVar30 = sVar8;
              psVar30 = *(short **)(param_3 + 0x360);
              *(short **)(param_3 + 0x360) = psVar30 + 1;
              *psVar30 = sVar7;
              psVar30 = *(short **)(param_3 + 0x360);
              *(short **)(param_3 + 0x360) = psVar30 + 1;
              *psVar30 = sVar20 + 1;
              *(int *)(param_3 + 0x370) = *(int *)(param_3 + 0x370) + 3;
            }
          }
          bVar23 = iVar27 < param_6;
          iVar27 = iVar27 + 1;
        } while (bVar23);
        iVar33 = iVar33 + param_6;
        iVar31 = iVar31 + param_6;
      } while (iVar32 != param_5);
    }
  }
code_r0x0220d524:
  Aska::DirectAofHandler::EndMesh()(param_3);
  if ((param_9 & 1) != 0) {
    fVar66 = param_1 * param_1 + param_2 * param_2;
    fStack_a4 = SQRT(fVar66);
    if (NAN(fStack_a4)) {
      fStack_a4 = (float)sqrtf(fVar66);
    }
    uStack_b0 = 0;
    uStack_a8 = 0;
    Aska::DirectAofHandler::Close(Aska::Vector const*, bool)(param_3,&uStack_b0,1);
  }
code_r0x0220d56c:
  *(char *)(param_4 + 2) = cVar5;
  return;
}

// ==== Aska::DirectAofHandler::MakeRenderContext(Aska::RenderContext*, Aska::AofObject*, Aska::RENDERINFO const*, Aska::RenderPass*, Aska::CommandBufferManager*)
// vaddr 0x210d5a0 | ghidra 0x220d5a0 | size 308 | symbol _ZN4Aska16DirectAofHandler17MakeRenderContextEPNS_13RenderContextEPNS_9AofObjectEPKNS_10RENDERINFOEPNS_10RenderPassEPNS_20CommandBufferManagerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandler17MakeRenderContextEPNS_13RenderContextEPNS_9AofObjectEPKNS_10RENDERINFOEPNS_10RenderPassEPNS_20CommandBufferManagerE
               (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  long lVar5;
  long lVar6;
  long *plVar7;
  
  if (*(char *)(param_1 + 0x351) != '\0') {
    piVar1 = (int *)(param_1 + 0x378);
    do {
      iVar2 = *piVar1;
      if (iVar2 != 1) {
        ClearExclusiveLocal();
        if (iVar2 != 1) {
          if (iVar2 == 2) {
            do {
            } while (*piVar1 != 0);
          }
          goto code_r0x0220d6a0;
        }
        break;
      }
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = 2;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    for (lVar5 = *(long *)(param_1 + 0x138); param_1 + 0x128 != lVar5;
        lVar5 = *(long *)(lVar5 + 0x10)) {
      Aska::RenderPassManager::InvalidateCommandBufferManager()(lVar5);
    }
    if (*(char *)(param_1 + 0x353) != '\0') {
      lVar5 = 0;
      do {
        lVar6 = *(long *)(*(long *)(param_1 + 0xd0) + lVar5 * 8);
        plVar7 = (long *)(lVar6 + 0x40);
        *(undefined4 *)(lVar6 + 0x68) = *(undefined4 *)(lVar6 + 0x168);
        *(undefined4 *)(lVar6 + 0x5c) = *(undefined4 *)(lVar6 + 0x16c);
        *(undefined2 *)(lVar6 + 0x58) = *(undefined2 *)(lVar6 + 0x170);
        (**(code **)(*plVar7 + 0x18))(plVar7);
        if ((*(byte *)(param_1 + 0x350) & 1) != 0) {
          Aska::PrimitiveBuffer::FlipBuffer()(plVar7);
        }
        lVar5 = lVar5 + 1;
      } while (lVar5 < (long)(ulong)*(byte *)(param_1 + 0x353));
    }
    DataMemoryBarrier(2,3);
    *piVar1 = 0;
code_r0x0220d6a0:
    *(undefined1 *)(param_1 + 0x351) = 0;
  }
  (*(code *)
    PTR__ZN4Aska10AofHandler17MakeRenderContextEPNS_13RenderContextEPNS_9AofObjectEPKNS_10RENDERINFOEPNS_10RenderPassEPNS_20CommandBufferManagerE_02c94e10
  )(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}

// ==== Aska::DirectAofHandler::UpdateKickBuffer()
// vaddr 0x210d6d4 | ghidra 0x220d6d4 | size 116 | symbol _ZN4Aska16DirectAofHandler16UpdateKickBufferEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandler16UpdateKickBufferEv(long param_1)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  
  if (*(char *)(param_1 + 0x353) != '\0') {
    lVar3 = 0;
    do {
      lVar1 = *(long *)(*(long *)(param_1 + 0xd0) + lVar3 * 8);
      plVar2 = (long *)(lVar1 + 0x40);
      *(undefined4 *)(lVar1 + 0x68) = *(undefined4 *)(lVar1 + 0x168);
      *(undefined4 *)(lVar1 + 0x5c) = *(undefined4 *)(lVar1 + 0x16c);
      *(undefined2 *)(lVar1 + 0x58) = *(undefined2 *)(lVar1 + 0x170);
      (**(code **)(*plVar2 + 0x18))(plVar2);
      if ((*(byte *)(param_1 + 0x350) & 1) != 0) {
        Aska::PrimitiveBuffer::FlipBuffer()(plVar2);
      }
      lVar3 = lVar3 + 1;
    } while (lVar3 < (long)(ulong)*(byte *)(param_1 + 0x353));
  }
  return;
}

// ==== Aska::DirectAofHandler::SetDirectMaterial(int, Aska::DirectMaterial*)
// vaddr 0x210d748 | ghidra 0x220d748 | size 144 | symbol _ZN4Aska16DirectAofHandler17SetDirectMaterialEiPNS_14DirectMaterialE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska16DirectAofHandler17SetDirectMaterialEiPNS_14DirectMaterialE
               (long *param_1,int param_2,long param_3)

{
  byte bVar1;
  byte bVar2;
  undefined8 uVar3;
  long lVar4;
  
  if (param_3 != 0) {
    lVar4 = *(long *)(param_1[0x1a] + (long)param_2 * 8);
    uVar3 = (**(code **)(*param_1 + 0x88))(param_1);
    Aska::MaterialList::SetDirectMaterial(int, Aska::DirectMaterial*, Aska::RenderablePrimitive*, unsigned long)(param_1 + 0x1d,param_2,param_3,lVar4 + 0x40,uVar3);
    *(undefined1 *)(param_1[0x16] + 0x7c) = *(undefined1 *)(param_3 + 4);
    bVar2 = *(byte *)(param_1 + 0x6a);
    bVar1 = bVar2 & 7 | (*(byte *)(param_3 + 6) & 1) << 3;
    *(byte *)(param_1 + 0x6a) = bVar2 & 0xf0 | bVar1;
    *(byte *)(param_1 + 0x6a) = bVar2 & 0xe0 | bVar1 | (*(byte *)(param_3 + 6) >> 1 & 1) << 4;
  }
  return;
}

// ==== Aska::DirectAofHandler::SetDefaultMaterial(Aska::DirectMaterial*)
// vaddr 0x210d7d8 | ghidra 0x220d7d8 | size 144 | symbol _ZN4Aska16DirectAofHandler18SetDefaultMaterialEPNS_14DirectMaterialE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0220d848: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0220d858: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0220d84c) */
/* WARNING: Removing unreachable block (ram,0x0220d85c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska16DirectAofHandler18SetDefaultMaterialEPNS_14DirectMaterialE(long param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined1 auVar3 [16];
  
  memset(param_1,0,0xb0);
  *(undefined1 *)(param_1 + 0xc) = 1;
  *(undefined1 *)(param_1 + 6) = 1;
  uVar2 = _UNK_029ca7a8;
  uVar1 = _UNK_029ca7a0;
  *(undefined2 *)(param_1 + 4) = 3;
  *(undefined1 *)(param_1 + 0xd) = 0xff;
  auVar3 = NEON_fmov(0x3f800000,4);
  *(undefined2 *)(param_1 + 0xf) = 0x83;
  *(long *)(param_1 + 0x28) = auVar3._8_8_;
  *(long *)(param_1 + 0x20) = auVar3._0_8_;
  *(undefined8 *)(param_1 + 0x38) = uVar2;
  *(undefined8 *)(param_1 + 0x30) = uVar1;
  auVar3 = _UNK_029ca7b0;
  *(undefined8 *)(param_1 + 0x40) = 0x3f8000003f800000;
  *(undefined8 *)(param_1 + 0x58) = 0x3f8000003ca3d70a;
  *(long *)(param_1 + 0x50) = auVar3._8_8_;
  *(long *)(param_1 + 0x48) = auVar3._0_8_;
  (*(code *)PTR__ZN4Aska15MaterialContext10SetDefaultEPNS_18TextureSamplerModeE_02c96b70)
            (param_1 + 0x68);
  return;
}

// ==== Aska::DirectAofPrimitive::Instantiate()
// vaddr 0x210d918 | ghidra 0x220d918 | size 96 | symbol _ZN4Aska18DirectAofPrimitive11InstantiateEv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska18DirectAofPrimitive11InstantiateEv(void)

{
  undefined *puVar1;
  undefined *puVar2;
  long *plVar3;
  
  plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x410,PTR__ZSt7nothrow_02cb9a80);
  if (plVar3 != (long *)0x0) {
    Aska::DirectAofPrimitiveBase::DirectAofPrimitiveBase()(plVar3);
    puVar1 = PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0xb8;
    puVar2 = PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0xe0;
    *plVar3 = (long)(PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0x10);
    plVar3[0x14] = (long)puVar2;
    plVar3[0x13] = (long)puVar1;
    Aska::detail::DirectAofPrimitiveImpl::DirectAofPrimitiveImpl(Aska::DirectAofPrimitive*)(plVar3 + 0x7c,plVar3);
  }
  return plVar3;
}

// ==== Aska::DirectAofPrimitive::SetDefaultMaterial(Aska::DirectMaterial*)
// vaddr 0x210d978 | ghidra 0x220d978 | size 44 | symbol _ZN4Aska18DirectAofPrimitive18SetDefaultMaterialEPNS_14DirectMaterialE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18DirectAofPrimitive18SetDefaultMaterialEPNS_14DirectMaterialE(long param_1)

{
  Aska::DirectAofHandler::SetDefaultMaterial(Aska::DirectMaterial*)();
  *(byte *)(param_1 + 6) = *(byte *)(param_1 + 6) | 2;
  *(ushort *)(param_1 + 0xf) = *(ushort *)(param_1 + 0xf) & 0xfffe;
  return;
}

// ==== Aska::DirectAofPrimitive::DirectAofPrimitive()
// vaddr 0x210d9a4 | ghidra 0x220d9a4 | size 64 | symbol _ZN4Aska18DirectAofPrimitiveC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18DirectAofPrimitiveC1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  Aska::DirectAofPrimitiveBase::DirectAofPrimitiveBase()();
  puVar1 = PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0xb8;
  puVar2 = PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0xe0;
  *param_1 = (long)(PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0x10);
  param_1[0x14] = (long)puVar2;
  param_1[0x13] = (long)puVar1;
  (*(code *)PTR__ZN4Aska6detail22DirectAofPrimitiveImplC2EPNS_18DirectAofPrimitiveE_02cabf38)
            (param_1 + 0x7c,param_1);
  return;
}

// ==== Aska::DirectAofPrimitive::~DirectAofPrimitive()
// vaddr 0x210d9e4 | ghidra 0x220d9e4 | size 64 | symbol _ZN4Aska18DirectAofPrimitiveD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18DirectAofPrimitiveD2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar1 = PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0xb8;
  puVar2 = PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0xe0;
  *param_1 = (long)(PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0x10);
  param_1[0x14] = (long)puVar2;
  param_1[0x13] = (long)puVar1;
  Aska::detail::DirectAofPrimitiveImpl::~DirectAofPrimitiveImpl()(param_1 + 0x7c);
  (*(code *)PTR__ZN4Aska22DirectAofPrimitiveBaseD2Ev_02cb2e18)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::DirectAofPrimitive::~DirectAofPrimitive()
// vaddr 0x210da24 | ghidra 0x220da24 | size 64 | symbol _ZThn152_N4Aska18DirectAofPrimitiveD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn152_N4Aska18DirectAofPrimitiveD1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar1 = PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0xb8;
  puVar2 = PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0x10;
  param_1[1] = (long)(PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0xe0);
  *param_1 = (long)puVar1;
  param_1[-0x13] = (long)puVar2;
  Aska::detail::DirectAofPrimitiveImpl::~DirectAofPrimitiveImpl()(param_1 + 0x69);
  (*(code *)PTR__ZN4Aska22DirectAofPrimitiveBaseD2Ev_02cb2e18)(param_1 + -0x13);
  return;
}

// ==== non-virtual thunk to Aska::DirectAofPrimitive::~DirectAofPrimitive()
// vaddr 0x210da64 | ghidra 0x220da64 | size 64 | symbol _ZThn160_N4Aska18DirectAofPrimitiveD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn160_N4Aska18DirectAofPrimitiveD1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar1 = PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0xb8;
  puVar2 = PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0xe0;
  param_1[-0x14] = (long)(PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0x10);
  *param_1 = (long)puVar2;
  param_1[-1] = (long)puVar1;
  Aska::detail::DirectAofPrimitiveImpl::~DirectAofPrimitiveImpl()(param_1 + 0x68);
  (*(code *)PTR__ZN4Aska22DirectAofPrimitiveBaseD2Ev_02cb2e18)(param_1 + -0x14);
  return;
}

// ==== Aska::DirectAofPrimitive::~DirectAofPrimitive()
// vaddr 0x210daa4 | ghidra 0x220daa4 | size 72 | symbol _ZN4Aska18DirectAofPrimitiveD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18DirectAofPrimitiveD0Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar1 = PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0xb8;
  puVar2 = PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0xe0;
  *param_1 = (long)(PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0x10);
  param_1[0x14] = (long)puVar2;
  param_1[0x13] = (long)puVar1;
  Aska::detail::DirectAofPrimitiveImpl::~DirectAofPrimitiveImpl()(param_1 + 0x7c);
  Aska::DirectAofPrimitiveBase::~DirectAofPrimitiveBase()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::DirectAofPrimitive::~DirectAofPrimitive()
// vaddr 0x210daec | ghidra 0x220daec | size 72 | symbol _ZThn152_N4Aska18DirectAofPrimitiveD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn152_N4Aska18DirectAofPrimitiveD0Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  long *plVar3;
  
  puVar1 = PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0xb8;
  puVar2 = PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0x10;
  plVar3 = param_1 + -0x13;
  param_1[1] = (long)(PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0xe0);
  *param_1 = (long)puVar1;
  *plVar3 = (long)puVar2;
  Aska::detail::DirectAofPrimitiveImpl::~DirectAofPrimitiveImpl()(param_1 + 0x69);
  Aska::DirectAofPrimitiveBase::~DirectAofPrimitiveBase()(plVar3);
  (*(code *)PTR__ZdlPv_02ca4758)(plVar3);
  return;
}

// ==== non-virtual thunk to Aska::DirectAofPrimitive::~DirectAofPrimitive()
// vaddr 0x210db34 | ghidra 0x220db34 | size 72 | symbol _ZThn160_N4Aska18DirectAofPrimitiveD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn160_N4Aska18DirectAofPrimitiveD0Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  long *plVar3;
  
  puVar1 = PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0xb8;
  puVar2 = PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0xe0;
  plVar3 = param_1 + -0x14;
  *plVar3 = (long)(PTR__ZTVN4Aska18DirectAofPrimitiveE_02cc3808 + 0x10);
  *param_1 = (long)puVar2;
  param_1[-1] = (long)puVar1;
  Aska::detail::DirectAofPrimitiveImpl::~DirectAofPrimitiveImpl()(param_1 + 0x68);
  Aska::DirectAofPrimitiveBase::~DirectAofPrimitiveBase()(plVar3);
  (*(code *)PTR__ZdlPv_02ca4758)(plVar3);
  return;
}

// ==== Aska::DirectAofPrimitive::GetVertexAsmbit_() const
// vaddr 0x210db7c | ghidra 0x220db7c | size 12 | symbol _ZNK4Aska18DirectAofPrimitive16GetVertexAsmbit_Ev | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska18DirectAofPrimitive16GetVertexAsmbit_Ev(void)

{
  return 0x50000161;
}

// ==== Aska::DirectAofPrimitive::GetVertexStride_() const
// vaddr 0x210db88 | ghidra 0x220db88 | size 8 | symbol _ZNK4Aska18DirectAofPrimitive16GetVertexStride_Ev | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska18DirectAofPrimitive16GetVertexStride_Ev(void)

{
  return 0x28;
}

// ==== Aska::DirectAofPrimitive::AddVertices(int, Aska::Vector const*, Aska::Vector const&, unsigned int const*)
// vaddr 0x210db90 | ghidra 0x220db90 | size 512 | symbol _ZN4Aska18DirectAofPrimitive11AddVerticesEiPKNS_6VectorERS2_PKj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18DirectAofPrimitive11AddVerticesEiPKNS_6VectorERS2_PKj
               (long param_1,uint param_2,float *param_3,float *param_4,uint *param_5)

{
  uint uVar1;
  uint uVar2;
  float *pfVar3;
  ulong uVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fStack_24;
  
  if (param_2 != 0) {
    fVar15 = *(float *)(param_1 + 0x330);
    fVar14 = *(float *)(param_1 + 0x334);
    fVar13 = *(float *)(param_1 + 0x338);
    fVar12 = *(float *)(param_1 + 0x33c);
    fVar11 = *(float *)(param_1 + 0x340);
    fVar10 = *(float *)(param_1 + 0x344);
    fVar9 = *(float *)(param_1 + 0x348);
    fVar8 = *(float *)(param_1 + 0x34c);
    pfVar3 = param_3;
    do {
      pfVar6 = (float *)(param_1 + 0x330);
      if (fVar15 <= *pfVar3) {
        pfVar6 = pfVar3;
      }
      fVar15 = *pfVar6;
      *(float *)(param_1 + 0x330) = fVar15;
      pfVar5 = pfVar3 + 1;
      pfVar6 = (float *)(param_1 + 0x334);
      if (fVar14 <= *pfVar5) {
        pfVar6 = pfVar5;
      }
      fVar14 = *pfVar6;
      *(float *)(param_1 + 0x334) = fVar14;
      pfVar7 = pfVar3 + 2;
      pfVar6 = (float *)(param_1 + 0x338);
      if (fVar13 <= *pfVar7) {
        pfVar6 = pfVar7;
      }
      fVar13 = *pfVar6;
      *(float *)(param_1 + 0x338) = fVar13;
      fStack_24 = *pfVar3 * *pfVar3 + *pfVar5 + *pfVar5 + *pfVar7 + *pfVar7;
      pfVar6 = (float *)(param_1 + 0x33c);
      if (fVar12 <= fStack_24) {
        pfVar6 = &fStack_24;
      }
      fVar12 = *pfVar6;
      *(float *)(param_1 + 0x33c) = fVar12;
      pfVar6 = (float *)(param_1 + 0x340);
      if (*pfVar3 <= fVar11) {
        pfVar6 = pfVar3;
      }
      fVar11 = *pfVar6;
      *(float *)(param_1 + 0x340) = fVar11;
      pfVar6 = (float *)(param_1 + 0x344);
      if (*pfVar5 <= fVar10) {
        pfVar6 = pfVar5;
      }
      fVar10 = *pfVar6;
      *(float *)(param_1 + 0x344) = fVar10;
      pfVar6 = (float *)(param_1 + 0x348);
      if (*pfVar7 <= fVar9) {
        pfVar6 = pfVar7;
      }
      fVar9 = *pfVar6;
      *(float *)(param_1 + 0x348) = fVar9;
      pfVar6 = (float *)(param_1 + 0x34c);
      if (pfVar3[3] <= fVar8) {
        pfVar6 = pfVar3 + 3;
      }
      fVar8 = *pfVar6;
      pfVar3 = pfVar3 + 4;
      *(float *)(param_1 + 0x34c) = fVar8;
    } while (pfVar3 != param_3 + (long)(int)param_2 * 4);
  }
  pfVar3 = *(float **)(param_1 + 0x368);
  if (0 < (int)param_2) {
    uVar4 = (ulong)param_2;
    uVar1 = (int)*(short *)(param_1 + 0x3dc) &
            ((int)*(short *)(param_1 + 0x3dc) >> 0xf ^ 0xffffffffU);
    pfVar5 = param_3 + 2;
    pfVar6 = pfVar3;
    do {
      uVar4 = uVar4 - 1;
      *pfVar6 = pfVar5[-2];
      pfVar6[1] = pfVar5[-1];
      pfVar6[2] = *pfVar5;
      pfVar6[3] = *param_4;
      pfVar6[4] = param_4[1];
      pfVar6[5] = param_4[2];
      uVar2 = *param_5;
      *(ushort *)(pfVar6 + 9) = (ushort)(uVar1 >> 8) & 0xff | (ushort)((uVar1 & 0xff00ff) << 8);
      *(undefined2 *)((long)pfVar6 + 0x26) = 0;
      pfVar6[6] = (float)(uVar2 & 0xff000000 |
                         uVar2 & 0xff00 | uVar2 >> 0x10 & 0xff | (uVar2 & 0xff) << 0x10);
      pfVar6 = pfVar6 + 10;
      param_5 = param_5 + 1;
      pfVar5 = pfVar5 + 4;
    } while (uVar4 != 0);
    pfVar3 = pfVar3 + (ulong)(param_2 - 1) * 10 + 10;
  }
  *(float **)(param_1 + 0x368) = pfVar3;
  *(uint *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + param_2;
  return;
}

// ==== Aska::DirectAofPrimitive::AddVerticesT(int, Aska::Vector const*, Aska::Vector const&, Aska::Vector const*, unsigned int const*)
// vaddr 0x210dd90 | ghidra 0x220dd90 | size 540 | symbol _ZN4Aska18DirectAofPrimitive12AddVerticesTEiPKNS_6VectorERS2_S3_PKj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18DirectAofPrimitive12AddVerticesTEiPKNS_6VectorERS2_S3_PKj
               (long param_1,uint param_2,float *param_3,float *param_4,long param_5,uint *param_6)

{
  uint uVar1;
  uint uVar2;
  float *pfVar3;
  ulong uVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fStack_34;
  
  if (param_2 != 0) {
    fVar15 = *(float *)(param_1 + 0x330);
    fVar14 = *(float *)(param_1 + 0x334);
    fVar13 = *(float *)(param_1 + 0x338);
    fVar12 = *(float *)(param_1 + 0x33c);
    fVar11 = *(float *)(param_1 + 0x340);
    fVar10 = *(float *)(param_1 + 0x344);
    fVar9 = *(float *)(param_1 + 0x348);
    fVar8 = *(float *)(param_1 + 0x34c);
    pfVar3 = param_3;
    do {
      pfVar5 = (float *)(param_1 + 0x330);
      if (fVar15 <= *pfVar3) {
        pfVar5 = pfVar3;
      }
      fVar15 = *pfVar5;
      *(float *)(param_1 + 0x330) = fVar15;
      pfVar6 = pfVar3 + 1;
      pfVar5 = (float *)(param_1 + 0x334);
      if (fVar14 <= *pfVar6) {
        pfVar5 = pfVar6;
      }
      fVar14 = *pfVar5;
      *(float *)(param_1 + 0x334) = fVar14;
      pfVar7 = pfVar3 + 2;
      pfVar5 = (float *)(param_1 + 0x338);
      if (fVar13 <= *pfVar7) {
        pfVar5 = pfVar7;
      }
      fVar13 = *pfVar5;
      *(float *)(param_1 + 0x338) = fVar13;
      fStack_34 = *pfVar3 * *pfVar3 + *pfVar6 + *pfVar6 + *pfVar7 + *pfVar7;
      pfVar5 = (float *)(param_1 + 0x33c);
      if (fVar12 <= fStack_34) {
        pfVar5 = &fStack_34;
      }
      fVar12 = *pfVar5;
      *(float *)(param_1 + 0x33c) = fVar12;
      pfVar5 = (float *)(param_1 + 0x340);
      if (*pfVar3 <= fVar11) {
        pfVar5 = pfVar3;
      }
      fVar11 = *pfVar5;
      *(float *)(param_1 + 0x340) = fVar11;
      pfVar5 = (float *)(param_1 + 0x344);
      if (*pfVar6 <= fVar10) {
        pfVar5 = pfVar6;
      }
      fVar10 = *pfVar5;
      *(float *)(param_1 + 0x344) = fVar10;
      pfVar5 = (float *)(param_1 + 0x348);
      if (*pfVar7 <= fVar9) {
        pfVar5 = pfVar7;
      }
      fVar9 = *pfVar5;
      *(float *)(param_1 + 0x348) = fVar9;
      pfVar5 = (float *)(param_1 + 0x34c);
      if (pfVar3[3] <= fVar8) {
        pfVar5 = pfVar3 + 3;
      }
      fVar8 = *pfVar5;
      pfVar3 = pfVar3 + 4;
      *(float *)(param_1 + 0x34c) = fVar8;
    } while (pfVar3 != param_3 + (long)(int)param_2 * 4);
  }
  pfVar3 = *(float **)(param_1 + 0x368);
  if (0 < (int)param_2) {
    uVar4 = (ulong)param_2;
    pfVar5 = (float *)(param_5 + 4);
    uVar1 = (int)*(short *)(param_1 + 0x3dc) &
            ((int)*(short *)(param_1 + 0x3dc) >> 0xf ^ 0xffffffffU);
    param_3 = param_3 + 1;
    pfVar6 = pfVar3;
    do {
      uVar4 = uVar4 - 1;
      *pfVar6 = param_3[-1];
      pfVar6[1] = *param_3;
      pfVar7 = param_3 + 1;
      param_3 = param_3 + 4;
      pfVar6[2] = *pfVar7;
      pfVar6[3] = *param_4;
      pfVar6[4] = param_4[1];
      pfVar6[5] = param_4[2];
      uVar2 = *param_6;
      pfVar6[6] = (float)(uVar2 & 0xff000000 |
                         uVar2 & 0xff00 | uVar2 >> 0x10 & 0xff | (uVar2 & 0xff) << 0x10);
      fVar15 = pfVar5[-1];
      fVar14 = *pfVar5;
      *(ushort *)(pfVar6 + 9) = (ushort)(uVar1 >> 8) & 0xff | (ushort)((uVar1 & 0xff00ff) << 8);
      *(undefined2 *)((long)pfVar6 + 0x26) = 0;
      pfVar5 = pfVar5 + 4;
      pfVar6[7] = fVar15;
      pfVar6[8] = fVar14;
      pfVar6 = pfVar6 + 10;
      param_6 = param_6 + 1;
    } while (uVar4 != 0);
    pfVar3 = pfVar3 + (ulong)(param_2 - 1) * 10 + 10;
  }
  *(float **)(param_1 + 0x368) = pfVar3;
  *(uint *)(param_1 + 0x374) = *(int *)(param_1 + 0x374) + param_2;
  return;
}

// ==== Aska::DirectAofPrimitive::SetVertices(int, void*, Aska::Vector const*, Aska::Vector const&, unsigned int const*)
// vaddr 0x210dfac | ghidra 0x220dfac | size 124 | symbol _ZN4Aska18DirectAofPrimitive11SetVerticesEiPvPKNS_6VectorERS3_PKj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18DirectAofPrimitive11SetVerticesEiPvPKNS_6VectorERS3_PKj
               (long param_1,uint param_2,undefined4 *param_3,long param_4,undefined4 *param_5,
               uint *param_6)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  undefined4 *puVar4;
  
  if (0 < (int)param_2) {
    uVar3 = (ulong)param_2;
    uVar1 = (int)*(short *)(param_1 + 0x3dc) &
            ((int)*(short *)(param_1 + 0x3dc) >> 0xf ^ 0xffffffffU);
    puVar4 = (undefined4 *)(param_4 + 8);
    do {
      uVar3 = uVar3 - 1;
      *param_3 = puVar4[-2];
      param_3[1] = puVar4[-1];
      param_3[2] = *puVar4;
      param_3[3] = *param_5;
      param_3[4] = param_5[1];
      param_3[5] = param_5[2];
      uVar2 = *param_6;
      *(ushort *)(param_3 + 9) = (ushort)(uVar1 >> 8) & 0xff | (ushort)((uVar1 & 0xff00ff) << 8);
      *(undefined2 *)((long)param_3 + 0x26) = 0;
      param_3[6] = uVar2 & 0xff000000 |
                   uVar2 & 0xff00 | uVar2 >> 0x10 & 0xff | (uVar2 & 0xff) << 0x10;
      param_3 = param_3 + 10;
      param_6 = param_6 + 1;
      puVar4 = puVar4 + 4;
    } while (uVar3 != 0);
  }
  return;
}

// ==== Aska::DirectAofPrimitive::SetVerticesT(int, void*, Aska::Vector const*, Aska::Vector const&, Aska::Vector const*, unsigned int const*)
// vaddr 0x210e028 | ghidra 0x220e028 | size 144 | symbol _ZN4Aska18DirectAofPrimitive12SetVerticesTEiPvPKNS_6VectorERS3_S4_PKj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18DirectAofPrimitive12SetVerticesTEiPvPKNS_6VectorERS3_S4_PKj
               (long param_1,uint param_2,undefined4 *param_3,long param_4,undefined4 *param_5,
               long param_6,uint *param_7)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  ulong uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  if (0 < (int)param_2) {
    uVar6 = (ulong)param_2;
    puVar7 = (undefined4 *)(param_6 + 4);
    puVar8 = (undefined4 *)(param_4 + 4);
    uVar2 = (int)*(short *)(param_1 + 0x3dc) &
            ((int)*(short *)(param_1 + 0x3dc) >> 0xf ^ 0xffffffffU);
    do {
      uVar6 = uVar6 - 1;
      *param_3 = puVar8[-1];
      param_3[1] = *puVar8;
      puVar1 = puVar8 + 1;
      puVar8 = puVar8 + 4;
      param_3[2] = *puVar1;
      param_3[3] = *param_5;
      param_3[4] = param_5[1];
      param_3[5] = param_5[2];
      uVar5 = *param_7;
      param_3[6] = uVar5 & 0xff000000 |
                   uVar5 & 0xff00 | uVar5 >> 0x10 & 0xff | (uVar5 & 0xff) << 0x10;
      uVar3 = puVar7[-1];
      uVar4 = *puVar7;
      *(ushort *)(param_3 + 9) = (ushort)(uVar2 >> 8) & 0xff | (ushort)((uVar2 & 0xff00ff) << 8);
      *(undefined2 *)((long)param_3 + 0x26) = 0;
      puVar7 = puVar7 + 4;
      param_3[7] = uVar3;
      param_3[8] = uVar4;
      param_3 = param_3 + 10;
      param_7 = param_7 + 1;
    } while (uVar6 != 0);
  }
  return;
}

// ==== Aska::DirectAofPrimitiveBase::DirectAofPrimitiveBase()
// vaddr 0x210e0b8 | ghidra 0x220e0b8 | size 60 | symbol _ZN4Aska22DirectAofPrimitiveBaseC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska22DirectAofPrimitiveBaseC1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  Aska::DirectAofHandler::DirectAofHandler()();
  puVar1 = PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0xb8;
  puVar2 = PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0xe0;
  *param_1 = (long)(PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0x10);
  param_1[0x14] = (long)puVar2;
  param_1[0x13] = (long)puVar1;
  (*(code *)PTR__ZN4Aska6detail23AnimationGroupContainerC1Ev_02cb4088)(param_1 + 0x70);
  return;
}

// ==== Aska::DirectAofPrimitiveBase::~DirectAofPrimitiveBase()
// vaddr 0x210e0f4 | ghidra 0x220e0f4 | size 64 | symbol _ZN4Aska22DirectAofPrimitiveBaseD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska22DirectAofPrimitiveBaseD2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar1 = PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0xb8;
  puVar2 = PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0xe0;
  *param_1 = (long)(PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0x10);
  param_1[0x14] = (long)puVar2;
  param_1[0x13] = (long)puVar1;
  Aska::detail::AnimationGroupContainer::~AnimationGroupContainer()(param_1 + 0x70);
  (*(code *)PTR__ZN4Aska16DirectAofHandlerD1Ev_02c96548)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::DirectAofPrimitiveBase::~DirectAofPrimitiveBase()
// vaddr 0x210e134 | ghidra 0x220e134 | size 64 | symbol _ZThn152_N4Aska22DirectAofPrimitiveBaseD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn152_N4Aska22DirectAofPrimitiveBaseD1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar1 = PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0xb8;
  puVar2 = PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0x10;
  param_1[1] = (long)(PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0xe0);
  *param_1 = (long)puVar1;
  param_1[-0x13] = (long)puVar2;
  Aska::detail::AnimationGroupContainer::~AnimationGroupContainer()(param_1 + 0x5d);
  (*(code *)PTR__ZN4Aska16DirectAofHandlerD1Ev_02c96548)(param_1 + -0x13);
  return;
}

// ==== non-virtual thunk to Aska::DirectAofPrimitiveBase::~DirectAofPrimitiveBase()
// vaddr 0x210e174 | ghidra 0x220e174 | size 64 | symbol _ZThn160_N4Aska22DirectAofPrimitiveBaseD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn160_N4Aska22DirectAofPrimitiveBaseD1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar1 = PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0xb8;
  puVar2 = PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0xe0;
  param_1[-0x14] = (long)(PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0x10);
  *param_1 = (long)puVar2;
  param_1[-1] = (long)puVar1;
  Aska::detail::AnimationGroupContainer::~AnimationGroupContainer()(param_1 + 0x5c);
  (*(code *)PTR__ZN4Aska16DirectAofHandlerD1Ev_02c96548)(param_1 + -0x14);
  return;
}

// ==== Aska::DirectAofPrimitiveBase::~DirectAofPrimitiveBase()
// vaddr 0x210e1b4 | ghidra 0x220e1b4 | size 72 | symbol _ZN4Aska22DirectAofPrimitiveBaseD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska22DirectAofPrimitiveBaseD0Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar1 = PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0xb8;
  puVar2 = PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0xe0;
  *param_1 = (long)(PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0x10);
  param_1[0x14] = (long)puVar2;
  param_1[0x13] = (long)puVar1;
  Aska::detail::AnimationGroupContainer::~AnimationGroupContainer()(param_1 + 0x70);
  Aska::DirectAofHandler::~DirectAofHandler()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::DirectAofPrimitiveBase::~DirectAofPrimitiveBase()
// vaddr 0x210e1fc | ghidra 0x220e1fc | size 72 | symbol _ZThn152_N4Aska22DirectAofPrimitiveBaseD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn152_N4Aska22DirectAofPrimitiveBaseD0Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  long *plVar3;
  
  puVar1 = PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0xb8;
  puVar2 = PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0x10;
  plVar3 = param_1 + -0x13;
  param_1[1] = (long)(PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0xe0);
  *param_1 = (long)puVar1;
  *plVar3 = (long)puVar2;
  Aska::detail::AnimationGroupContainer::~AnimationGroupContainer()(param_1 + 0x5d);
  Aska::DirectAofHandler::~DirectAofHandler()(plVar3);
  (*(code *)PTR__ZdlPv_02ca4758)(plVar3);
  return;
}

// ==== non-virtual thunk to Aska::DirectAofPrimitiveBase::~DirectAofPrimitiveBase()
// vaddr 0x210e244 | ghidra 0x220e244 | size 72 | symbol _ZThn160_N4Aska22DirectAofPrimitiveBaseD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn160_N4Aska22DirectAofPrimitiveBaseD0Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  long *plVar3;
  
  puVar1 = PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0xb8;
  puVar2 = PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0xe0;
  plVar3 = param_1 + -0x14;
  *plVar3 = (long)(PTR__ZTVN4Aska22DirectAofPrimitiveBaseE_02cbc098 + 0x10);
  *param_1 = (long)puVar2;
  param_1[-1] = (long)puVar1;
  Aska::detail::AnimationGroupContainer::~AnimationGroupContainer()(param_1 + 0x5c);
  Aska::DirectAofHandler::~DirectAofHandler()(plVar3);
  (*(code *)PTR__ZdlPv_02ca4758)(plVar3);
  return;
}

// ==== Aska::DirectAofPrimitiveBase::CreateSkinMatrices() const
// vaddr 0x210e28c | ghidra 0x220e28c | size 32 | symbol _ZNK4Aska22DirectAofPrimitiveBase18CreateSkinMatricesEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska22DirectAofPrimitiveBase18CreateSkinMatricesEv(void)

{
  undefined8 uVar1;
  
  uVar1 = operator new(unsigned long)(0x90);
  Aska::SkinMatricesSimple::SkinMatricesSimple()();
  return uVar1;
}

// ==== Aska::DirectAofPrimitiveBase::OnOpen()
// vaddr 0x210e2ac | ghidra 0x220e2ac | size 12 | symbol _ZN4Aska22DirectAofPrimitiveBase6OnOpenEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska22DirectAofPrimitiveBase6OnOpenEv(long param_1)

{
  *(undefined2 *)(param_1 + 0x3dc) = 0xffff;
  return;
}

// ==== Aska::DirectAofPrimitiveBase::OnClose(Aska::Vector const*, bool)
// vaddr 0x210e2b8 | ghidra 0x220e2b8 | size 92 | symbol _ZN4Aska22DirectAofPrimitiveBase7OnCloseEPKNS_6VectorEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska22DirectAofPrimitiveBase7OnCloseEPKNS_6VectorEb(long param_1)

{
  undefined8 uVar1;
  ulong uVar2;
  
  if (*(long *)(param_1 + 0xe0) == 0) {
    *(short *)(*(long *)(param_1 + 0xb0) + 0x76) = (short)*(undefined4 *)(param_1 + 0x390);
    uVar1 = Aska::detail::AnimationGroupContainer::CreateBonePalette()(param_1 + 0x380);
    *(undefined8 *)(param_1 + 0xe0) = uVar1;
  }
  uVar2 = Aska::detail::AnimationGroupContainer::RefreshPriority(Aska::DirectAofHandler*)(param_1 + 0x380,param_1);
  if ((uVar2 & 1) != 0) {
    *(undefined1 *)(param_1 + 0x3de) = 1;
  }
  return;
}

// ==== Aska::DirectAofPrimitiveBase::OnAddMeshset(int)
// vaddr 0x210e314 | ghidra 0x220e314 | size 56 | symbol _ZN4Aska22DirectAofPrimitiveBase12OnAddMeshsetEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska22DirectAofPrimitiveBase12OnAddMeshsetEi(long param_1,int param_2)

{
  long lVar1;
  long *plVar2;
  
  lVar1 = *(long *)(param_1 + 0xb0);
  *(undefined2 *)(lVar1 + 0x76) = 1;
  *(short *)(lVar1 + 0x78) = *(short *)(lVar1 + 0x78) + 1;
  plVar2 = *(long **)(*(long *)(param_1 + 0xd0) + (long)param_2 * 8);
  *(undefined1 *)(*plVar2 + 0x1a) = 0xff;
  *(undefined1 *)(plVar2[1] + 0x19) = 1;
  return;
}

// ==== Aska::DirectAofPrimitiveBase::OnSkinMatricesCreated(Aska::AofObject&)
// vaddr 0x210e34c | ghidra 0x220e34c | size 28 | symbol _ZN4Aska22DirectAofPrimitiveBase21OnSkinMatricesCreatedERNS_9AofObjectE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska22DirectAofPrimitiveBase21OnSkinMatricesCreatedERNS_9AofObjectE
               (undefined8 param_1,long param_2)

{
  if (*(long *)(param_2 + 0x3a0) != 0) {
    (*(code *)
      PTR__ZN4Aska16SkinMatricesBase11InitPaletteEPNS_9AofObjectEPNS_22DirectAofPrimitiveBaseE_02c9b2f8
    )(*(long *)(param_2 + 0x3a0),param_2,param_1);
    return;
  }
  return;
}

// ==== Aska::DirectAofPrimitiveBase::GetShaderContextFlag() const
// vaddr 0x210e368 | ghidra 0x220e368 | size 4 | symbol _ZNK4Aska22DirectAofPrimitiveBase20GetShaderContextFlagEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska22DirectAofPrimitiveBase20GetShaderContextFlagEv(void)

{
  (*(code *)PTR__ZNK4Aska10AofHandler20GetShaderContextFlagEv_02c98c90)();
  return;
}

// ==== Aska::DirectAofPrimitiveBase::UpdateMeshset(Aska::VertexHandle const&)
// vaddr 0x210e36c | ghidra 0x220e36c | size 112 | symbol _ZN4Aska22DirectAofPrimitiveBase13UpdateMeshsetERKNS_12VertexHandleE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska22DirectAofPrimitiveBase13UpdateMeshsetERKNS_12VertexHandleE
               (long param_1,ushort *param_2)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  
  uVar1 = (uint)param_2[1];
  if ((*param_2 & param_2[1]) == 0xffff) {
    if ((param_2[2] == 0xffff) && (param_2[3] == 0xffff)) {
      return;
    }
    uVar1 = 0xffff;
  }
  lVar2 = *(long *)(*(long *)(param_1 + 0xd0) + (ulong)uVar1 * 8);
  lVar3 = *(long *)(lVar2 + 8);
  if (lVar3 == 0) {
    return;
  }
  Aska::DirectAofHandler::Sync(Aska::RenderablePrimitive*, unsigned int, unsigned int)(param_1,lVar2 + 0x40,*(undefined4 *)(lVar3 + 0x10),*(undefined4 *)(lVar3 + 0x14));
  (*(code *)PTR__ZN4Aska16DirectAofHandler10UpdatePrimEv_02c92fb0)(param_1);
  return;
}


// FAILED to create function at 029ca82c Aska::DirectAofPrimitiveBase::s_skinWeight
// FAILED to create function at 02ba7ed8 Framework::CDirectAofPrimitiveRenderer::vtable
// FAILED to create function at 02ba81d0 Framework::CDirectAofPrimitiveRenderer::typeinfo
// FAILED to create function at 02ba8308 Framework::CDirectAofTextRenderer::vtable
// FAILED to create function at 02ba8600 Framework::CDirectAofTextRenderer::typeinfo
// FAILED to create function at 02c4d0f8 Aska::DirectAofHandler::vtable
// FAILED to create function at 02c4d200 Aska::DirectAofHandler::typeinfo
// FAILED to create function at 02c4d258 Aska::DirectAofPrimitive::vtable
// FAILED to create function at 02c4d360 Aska::DirectAofPrimitive::typeinfo
// FAILED to create function at 02c4d378 Aska::DirectAofPrimitiveBase::vtable
// FAILED to create function at 02c4d480 Aska::DirectAofPrimitiveBase::typeinfo
// FAILED to create function at 02d00400 Framework::DirectAofPrimitiveEx::AddDummy(Framework::CDirectAofPrimitiveRenderer::iType,unsigned_int)::vZero
// FAILED to create function at 02d00410 Framework::DirectAofPrimitiveEx::AddDummy(Framework::CDirectAofPrimitiveRenderer::iType,unsigned_int)::vZero
// FAILED to create function at 02d00420 Framework::DirectAofPrimitiveEx::AddDummy(Framework::CDirectAofPrimitiveRenderer::iType,unsigned_int)::vDummy
// FAILED to create function at 02d00460 Framework::DirectAofPrimitiveEx::AddDummy(Framework::CDirectAofPrimitiveRenderer::iType,unsigned_int)::vDummy
