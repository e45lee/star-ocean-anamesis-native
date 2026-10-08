// port/decomp/dynamics/manager.c: Ghidra decompiles for the dynamics subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-08 14:44 UTC: tools/decomp.sh '--into' 'dynamics/manager' ' Aska::(Dynamics|DynamicsManager|DynamicsHandler|DynamicsListHandler<[^(]*>|DynamicsWait|DynamicsCommandNotify|CollisionHandler)::[~\w<>]+\('

// ==== Aska::Dynamics::Clone(Aska::IAnimatable const*)
// vaddr 0x2075c38 | ghidra 0x2175c38 | size 4 | symbol _ZN4Aska8Dynamics5CloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8Dynamics5CloneEPKNS_11IAnimatableE(void)

{
  (*(code *)PTR__ZN4Aska11IAnimatable5CloneEPKS0__02c96b68)();
  return;
}

// ==== Aska::Dynamics::CreateClone(Aska::IAnimatable const*)
// vaddr 0x2075c3c | ghidra 0x2175c3c | size 8 | symbol _ZN4Aska8Dynamics11CreateCloneEPKNS_11IAnimatableE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska8Dynamics11CreateCloneEPKNS_11IAnimatableE(void)

{
  return 0;
}

// ==== Aska::Dynamics::Get(unsigned long, void*) const
// vaddr 0x2075c44 | ghidra 0x2175c44 | size 8 | symbol _ZNK4Aska8Dynamics3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska8Dynamics3GetEmPv(void)

{
  return 0;
}

// ==== Aska::Dynamics::Set(unsigned long, void const*)
// vaddr 0x2075c4c | ghidra 0x2175c4c | size 8 | symbol _ZN4Aska8Dynamics3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska8Dynamics3SetEmPKv(void)

{
  return 0;
}

// ==== Aska::Dynamics::OnMakeListFromDynamicsManager()
// vaddr 0x2075c84 | ghidra 0x2175c84 | size 4 | symbol _ZN4Aska8Dynamics29OnMakeListFromDynamicsManagerEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8Dynamics29OnMakeListFromDynamicsManagerEv(void)

{
  return;
}

// ==== Aska::Dynamics::GetType() const
// vaddr 0x2075c88 | ghidra 0x2175c88 | size 8 | symbol _ZNK4Aska8Dynamics7GetTypeEv | lib libSOA-3.7.0.so | 2026-10-08
undefined1 _ZNK4Aska8Dynamics7GetTypeEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x18);
}

// ==== Aska::Dynamics::SetType(unsigned char)
// vaddr 0x2075c90 | ghidra 0x2175c90 | size 8 | symbol _ZN4Aska8Dynamics7SetTypeEh | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8Dynamics7SetTypeEh(long param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::Dynamics::GetClassID(int) const
// vaddr 0x207619c | ghidra 0x217619c | size 40 | symbol _ZNK4Aska8Dynamics10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska8Dynamics10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar2 = 0xf000f001;
  if (param_2 != 1) {
    uVar2 = 0xf000;
  }
  uVar1 = 0xf001f032;
  if (param_2 != 0) {
    uVar1 = uVar2;
  }
  return uVar1;
}

// ==== Aska::Dynamics::Run()
// vaddr 0x20761c4 | ghidra 0x21761c4 | size 4 | symbol _ZN4Aska8Dynamics3RunEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8Dynamics3RunEv(void)

{
  return;
}

// ==== Aska::Dynamics::DeleteThis()
// vaddr 0x20761c8 | ghidra 0x21761c8 | size 20 | symbol _ZN4Aska8Dynamics10DeleteThisEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8Dynamics10DeleteThisEv(long *param_1)

{
  if (param_1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x021761d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 8))();
    return;
  }
  return;
}

// ==== Aska::Dynamics::AddRefEx()
// vaddr 0x20761dc | ghidra 0x21761dc | size 4 | symbol _ZN4Aska8Dynamics8AddRefExEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska8Dynamics8AddRefExEv(void)

{
  return;
}

// ==== Aska::DynamicsHandler::GetType() const
// vaddr 0x2076828 | ghidra 0x2176828 | size 8 | symbol _ZNK4Aska15DynamicsHandler7GetTypeEv | lib libSOA-3.7.0.so | 2026-10-08
undefined1 _ZNK4Aska15DynamicsHandler7GetTypeEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x35);
}

// ==== Aska::DynamicsHandler::IsNeedToSortByProcessHeaviness()
// vaddr 0x2076848 | ghidra 0x2176848 | size 8 | symbol _ZN4Aska15DynamicsHandler30IsNeedToSortByProcessHeavinessEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska15DynamicsHandler30IsNeedToSortByProcessHeavinessEv(void)

{
  return 0;
}

// ==== Aska::DynamicsHandler::IsHeavierHandler(Aska::DynamicsHandler*)
// vaddr 0x2076850 | ghidra 0x2176850 | size 8 | symbol _ZN4Aska15DynamicsHandler16IsHeavierHandlerEPS0_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska15DynamicsHandler16IsHeavierHandlerEPS0_(void)

{
  return 0;
}

// ==== Aska::DynamicsHandler::OnMakeListFromDynamicsManager()
// vaddr 0x2076858 | ghidra 0x2176858 | size 4 | symbol _ZN4Aska15DynamicsHandler29OnMakeListFromDynamicsManagerEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsHandler29OnMakeListFromDynamicsManagerEv(void)

{
  return;
}

// ==== Aska::DynamicsHandler::IsAddToDynList()
// vaddr 0x207685c | ghidra 0x217685c | size 36 | symbol _ZN4Aska15DynamicsHandler14IsAddToDynListEv | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska15DynamicsHandler14IsAddToDynListEv(long *param_1)

{
  char cVar1;
  
  cVar1 = (**(code **)(*param_1 + 0x10))();
  return cVar1 != '\x02';
}

// ==== Aska::DynamicsHandler::GetClassID(int) const
// vaddr 0x2076880 | ghidra 0x2176880 | size 8 | symbol _ZNK4Aska15DynamicsHandler10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska15DynamicsHandler10GetClassIDEi(void)

{
  return 0xf200;
}

// ==== Aska::CollisionHandler::DecompressData(void const*)
// vaddr 0x209c210 | ghidra 0x219c210 | size 240 | symbol _ZN4Aska16CollisionHandler14DecompressDataEPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN4Aska16CollisionHandler14DecompressDataEPKv(long param_1,undefined8 param_2)

{
  undefined8 uVar1;
  ulong uVar2;
  undefined4 uVar3;
  undefined *puStack_d0;
  undefined1 *puStack_c8;
  undefined1 auStack_c0 [104];
  undefined4 auStack_58 [2];
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  
  auStack_58[0] = 4;
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_40 = 0x10;
  Aska::Event::Event()(auStack_c0);
  uVar2 = Aska::Event::Create(bool, bool)(auStack_c0,1,0);
  uVar3 = 0;
  if ((uVar2 & 1) != 0) {
    puStack_d0 = PTR__ZTVN4Aska11EventNotifyE_02cb7e68 + 0x10;
    uStack_48 = 0;
    puStack_c8 = auStack_c0;
    uVar2 = Aska::DecompressQueue::Add(void const*, Aska::DecompressInfo*, int, Aska::INotify*, Aska::IMemoryManager*, Aska::IMemoryManager*, Aska::IMemoryManager*, Aska::IMemoryManager*)(*(undefined8 *)PTR__ZN4Aska6Global18m_pDecompressQueueE_02cc0f20,param_2
                            ,auStack_58,0,&puStack_d0,0,0,0,0);
    if ((uVar2 & 1) == 0) {
      uVar3 = 0;
    }
    else {
      Aska::Event::Wait(unsigned int) const(auStack_c0,0);
      uVar1 = uStack_48;
      if ((*(char *)(param_1 + 0x54) == '\0') && (*(long *)(param_1 + 8) != 0)) {
        operator delete[](void*)();
      }
      *(undefined8 *)(param_1 + 8) = uVar1;
      *(undefined1 *)(param_1 + 0x54) = 0;
      uVar3 = 1;
    }
  }
  Aska::Event::Exit()(auStack_c0);
  return uVar3;
}

// ==== Aska::CollisionHandler::SetData(void const*)
// vaddr 0x209c300 | ghidra 0x219c300 | size 60 | symbol _ZN4Aska16CollisionHandler7SetDataEPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska16CollisionHandler7SetDataEPKv(long param_1,undefined8 param_2)

{
  if ((*(char *)(param_1 + 0x54) == '\0') && (*(long *)(param_1 + 8) != 0)) {
    operator delete[](void*)();
  }
  *(undefined8 *)(param_1 + 8) = param_2;
  *(undefined1 *)(param_1 + 0x54) = 0;
  return 1;
}

// ==== Aska::CollisionHandler::AttachData(void const*)
// vaddr 0x209c33c | ghidra 0x219c33c | size 64 | symbol _ZN4Aska16CollisionHandler10AttachDataEPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska16CollisionHandler10AttachDataEPKv(long param_1,undefined8 param_2)

{
  if ((*(char *)(param_1 + 0x54) == '\0') && (*(long *)(param_1 + 8) != 0)) {
    operator delete[](void*)();
  }
  *(undefined8 *)(param_1 + 8) = param_2;
  *(undefined1 *)(param_1 + 0x54) = 1;
  return 1;
}

// ==== Aska::CollisionHandler::GetAcfHeader(Aska::AFF::AskaFile*)
// vaddr 0x209c37c | ghidra 0x219c37c | size 92 | symbol _ZN4Aska16CollisionHandler12GetAcfHeaderEPNS_3AFF8AskaFileE | lib libSOA-3.7.0.so | 2026-10-08
long _ZN4Aska16CollisionHandler12GetAcfHeaderEPNS_3AFF8AskaFileE(long param_1)

{
  ulong uVar1;
  long lVar2;
  undefined *puStack_20;
  long lStack_18;
  
  puStack_20 = PTR__ZTVN4Aska10ArfHandlerE_02cbeb70 + 0x10;
  lStack_18 = 0;
  uVar1 = Aska::ArfHandler::Attach(Aska::AFF::AskaResource const*)(&puStack_20,param_1 + 0x10);
  lVar2 = param_1 + 0x10;
  if ((uVar1 & 1) != 0) {
    if (lStack_18 == 0) {
      lVar2 = 0;
    }
    else {
      lVar2 = 0;
      if (*(uint *)(lStack_18 + 0xc) != 0) {
        lVar2 = lStack_18 + (ulong)*(uint *)(lStack_18 + 0xc);
      }
    }
  }
  return lVar2;
}

// ==== Aska::CollisionHandler::CreateData()
// vaddr 0x209c3d8 | ghidra 0x219c3d8 | size 244 | symbol _ZN4Aska16CollisionHandler10CreateDataEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska16CollisionHandler10CreateDataEv(long param_1)

{
  int iVar1;
  uint uVar2;
  ulong uVar3;
  int *piVar4;
  int *piVar5;
  undefined *puStack_30;
  long lStack_28;
  
  piVar5 = *(int **)(param_1 + 8);
  if (piVar5 != (int *)0x0) {
    iVar1 = *piVar5;
    while (iVar1 != 0x41434620) {
      if (piVar5[3] == 0) {
        return 0;
      }
      piVar5 = (int *)((long)piVar5 + (ulong)(uint)piVar5[3]);
      iVar1 = *piVar5;
    }
    puStack_30 = PTR__ZTVN4Aska10ArfHandlerE_02cbeb70 + 0x10;
    lStack_28 = 0;
    uVar3 = Aska::ArfHandler::Attach(Aska::AFF::AskaResource const*)(&puStack_30,piVar5 + 4);
    piVar4 = piVar5 + 4;
    if ((uVar3 & 1) != 0) {
      if (lStack_28 == 0) {
        piVar4 = (int *)0x0;
      }
      else {
        piVar4 = (int *)0x0;
        if (*(uint *)(lStack_28 + 0xc) != 0) {
          piVar4 = (int *)(lStack_28 + (ulong)*(uint *)(lStack_28 + 0xc));
        }
      }
    }
    if (((short)*piVar4 == 7) && (*(int **)(param_1 + 0x10) = piVar4, ((ulong)piVar4 & 0xf) == 0)) {
      *(ulong *)(param_1 + 0x18) = (ulong)(uint)piVar4[3] + (long)piVar5;
      *(ulong *)(param_1 + 0x20) = (ulong)(uint)piVar4[4] + (long)piVar5;
      uVar2 = piVar4[5];
      *(ulong *)(param_1 + 0x28) = (ulong)uVar2 + (long)piVar5;
      if (((ulong)uVar2 + (long)piVar5 & 0xf) == 0) {
        *(undefined4 *)(param_1 + 0x50) = 0x3f800000;
        *(undefined1 *)(param_1 + 0x55) = 1;
        return 1;
      }
    }
  }
  return 0;
}

// ==== Aska::CollisionHandler::PreAttachObject()
// vaddr 0x209c4cc | ghidra 0x219c4cc | size 156 | symbol _ZN4Aska16CollisionHandler15PreAttachObjectEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska16CollisionHandler15PreAttachObjectEv(long param_1)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  
  if (*(char *)(param_1 + 0x55) != '\0') {
    uVar3 = (ulong)*(ushort *)(*(long *)(param_1 + 0x10) + 2);
    lVar2 = *(ushort *)(*(long *)(param_1 + 0x10) + 4) + uVar3;
    if (*(long *)(param_1 + 0x30) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 0x38) = 0;
      *(undefined8 *)(param_1 + 0x40) = 0;
      *(long *)(param_1 + 0x30) = 0;
    }
    if ((int)lVar2 != 0) {
      lVar2 = lVar2 * 8;
      lVar1 = operator new[](unsigned long, std::nothrow_t const&)(lVar2,PTR__ZSt7nothrow_02cb9a80);
      if (lVar1 == 0) {
        return 0;
      }
      memset(lVar1,0,lVar2);
      *(long *)(param_1 + 0x30) = lVar1;
      *(long *)(param_1 + 0x38) = lVar1;
      *(ulong *)(param_1 + 0x40) = lVar1 + uVar3 * 8;
      *(undefined1 *)(param_1 + 0x56) = 1;
      return 1;
    }
  }
  return 0;
}

// ==== Aska::CollisionHandler::AttachObject(Aska::AsfHandler*)
// vaddr 0x209c568 | ghidra 0x219c568 | size 352 | symbol _ZN4Aska16CollisionHandler12AttachObjectEPNS_10AsfHandlerE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska16CollisionHandler12AttachObjectEPNS_10AsfHandlerE(long param_1,long param_2)

{
  long lVar1;
  undefined8 uVar2;
  long lVar3;
  long *plVar4;
  long lVar5;
  ulong uVar6;
  
  if (param_2 == 0) {
    return 0;
  }
  if (*(char *)(param_1 + 0x55) == '\0') {
    return 0;
  }
  if (*(int *)(param_2 + 0xb0) == 0) {
code_r0x0219c6b0:
    uVar2 = 0;
  }
  else {
    if (*(char *)(param_1 + 0x56) == '\0') {
      uVar6 = (ulong)*(ushort *)(*(long *)(param_1 + 0x10) + 2);
      lVar3 = *(ushort *)(*(long *)(param_1 + 0x10) + 4) + uVar6;
      if (*(long *)(param_1 + 0x30) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 0x38) = 0;
        *(undefined8 *)(param_1 + 0x40) = 0;
        *(long *)(param_1 + 0x30) = 0;
      }
      if ((int)lVar3 == 0) goto code_r0x0219c6b0;
      lVar3 = lVar3 * 8;
      plVar4 = (long *)operator new[](unsigned long, std::nothrow_t const&)(lVar3,PTR__ZSt7nothrow_02cb9a80);
      if (plVar4 == (long *)0x0) {
        return 0;
      }
      memset(plVar4,0,lVar3);
      *(long **)(param_1 + 0x30) = plVar4;
      *(long **)(param_1 + 0x38) = plVar4;
      *(long **)(param_1 + 0x40) = plVar4 + uVar6;
      *(undefined1 *)(param_1 + 0x56) = 1;
    }
    else {
      plVar4 = *(long **)(param_1 + 0x38);
    }
    lVar3 = *(long *)(param_1 + 0x10);
    *(long *)(param_1 + 0x48) = param_2;
    if ((ulong)*(ushort *)(lVar3 + 2) != 0) {
      lVar5 = (ulong)*(ushort *)(lVar3 + 2) << 6;
      lVar3 = *(long *)(param_1 + 0x18) + 0x10;
      do {
        lVar1 = Aska::AsfHandler::QuickSearchByNameEx(char const*) const(param_2,lVar3);
        if (lVar1 != 0) {
          *plVar4 = lVar1 + 0x30;
        }
        plVar4 = plVar4 + 1;
        lVar5 = lVar5 + -0x40;
        lVar3 = lVar3 + 0x40;
      } while (lVar5 != 0);
      lVar3 = *(long *)(param_1 + 0x10);
    }
    if ((ulong)*(ushort *)(lVar3 + 4) != 0) {
      plVar4 = *(long **)(param_1 + 0x40);
      lVar5 = (ulong)*(ushort *)(lVar3 + 4) << 6;
      lVar3 = *(long *)(param_1 + 0x20) + 0x10;
      do {
        lVar1 = Aska::AsfHandler::QuickSearchByNameEx(char const*) const(param_2,lVar3);
        if (lVar1 != 0) {
          *plVar4 = lVar1 + 0x30;
        }
        plVar4 = plVar4 + 1;
        lVar5 = lVar5 + -0x40;
        lVar3 = lVar3 + 0x40;
      } while (lVar5 != 0);
    }
    uVar2 = 1;
    *(undefined1 *)(param_1 + 0x57) = 1;
  }
  return uVar2;
}

// ==== Aska::CollisionHandler::GetAcfObject(int, Aska::AcfObject*) const
// vaddr 0x209c6c8 | ghidra 0x219c6c8 | size 124 | symbol _ZNK4Aska16CollisionHandler12GetAcfObjectEiPNS_9AcfObjectE | lib libSOA-3.7.0.so | 2026-10-08
ushort * _ZNK4Aska16CollisionHandler12GetAcfObjectEiPNS_9AcfObjectE
                   (long param_1,uint param_2,long param_3)

{
  ushort *puVar1;
  ushort uVar2;
  uint uVar3;
  long lVar4;
  
  if (*(char *)(param_1 + 0x55) != '\x01') {
    return (ushort *)0x0;
  }
  uVar2 = *(ushort *)(*(long *)(param_1 + 0x10) + 6);
  if (param_3 == 0) {
    uVar3 = 0;
    if (uVar2 == 0) {
      return (ushort *)0x0;
    }
  }
  else {
    uVar3 = *(ushort *)(param_3 + 2) + 1;
    if (uVar2 <= uVar3) {
      return (ushort *)0x0;
    }
  }
  lVar4 = (long)(int)uVar3;
  do {
    puVar1 = (ushort *)
             (*(long *)(param_1 + 8) + (ulong)*(uint *)(*(long *)(param_1 + 0x28) + lVar4 * 4));
    if (*puVar1 == param_2) {
      return puVar1;
    }
    lVar4 = lVar4 + 1;
  } while (lVar4 < (long)(ulong)uVar2);
  return (ushort *)0x0;
}

// ==== Aska::CollisionHandler::GetObjectLinkedWithBranch(Aska::AcfSphereTreeBranch*) const
// vaddr 0x209c744 | ghidra 0x219c744 | size 40 | symbol _ZNK4Aska16CollisionHandler25GetObjectLinkedWithBranchEPNS_19AcfSphereTreeBranchE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZNK4Aska16CollisionHandler25GetObjectLinkedWithBranchEPNS_19AcfSphereTreeBranchE
          (long param_1,long param_2)

{
  if (*(ushort *)(param_2 + 0x32) < *(ushort *)(*(long *)(param_1 + 0x10) + 2)) {
    return *(undefined8 *)(*(long *)(param_1 + 0x38) + (ulong)*(ushort *)(param_2 + 0x32) * 8);
  }
  return 0;
}

// ==== Aska::CollisionHandler::GetObjectLinkedWithLeaf(Aska::AcfSphereTreeLeaf*) const
// vaddr 0x209c76c | ghidra 0x219c76c | size 40 | symbol _ZNK4Aska16CollisionHandler23GetObjectLinkedWithLeafEPNS_17AcfSphereTreeLeafE | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZNK4Aska16CollisionHandler23GetObjectLinkedWithLeafEPNS_17AcfSphereTreeLeafE
          (long param_1,long param_2)

{
  if (*(ushort *)(param_2 + 0x32) < *(ushort *)(*(long *)(param_1 + 0x10) + 4)) {
    return *(undefined8 *)(*(long *)(param_1 + 0x40) + (ulong)*(ushort *)(param_2 + 0x32) * 8);
  }
  return 0;
}

// ==== Aska::CollisionHandler::EnableCollision(unsigned int, bool)
// vaddr 0x209c794 | ghidra 0x219c794 | size 4 | symbol _ZN4Aska16CollisionHandler15EnableCollisionEjb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16CollisionHandler15EnableCollisionEjb(void)

{
  return;
}

// ==== Aska::CollisionHandler::SearchByName(char const*, int) const
// vaddr 0x209c798 | ghidra 0x219c798 | size 148 | symbol _ZNK4Aska16CollisionHandler12SearchByNameEPKci | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK4Aska16CollisionHandler12SearchByNameEPKci(long param_1,undefined8 param_2,int param_3)

{
  int iVar1;
  ulong uVar2;
  ushort *puVar3;
  long lVar4;
  
  if ((*(char *)(param_1 + 0x55) != '\0') &&
     (uVar2 = (ulong)*(ushort *)(*(long *)(param_1 + 0x10) + 4), uVar2 != 0)) {
    lVar4 = uVar2 << 6;
    puVar3 = (ushort *)(*(long *)(param_1 + 0x20) + 0x38);
    do {
      iVar1 = strcmp(param_2,puVar3 + -0x14);
      if (iVar1 == 0) {
        if ((int)(uint)*puVar3 <= param_3) {
          return 0;
        }
        return *(long *)(param_1 + 8) +
               (ulong)*(uint *)(*(long *)(param_1 + 0x28) +
                               (long)(int)((uint)puVar3[-1] + param_3) * 4);
      }
      lVar4 = lVar4 + -0x40;
      puVar3 = puVar3 + 0x20;
    } while (lVar4 != 0);
  }
  return 0;
}

// ==== Aska::CollisionHandler::SearchByName(char const*) const
// vaddr 0x209c82c | ghidra 0x219c82c | size 128 | symbol _ZNK4Aska16CollisionHandler12SearchByNameEPKc | lib libSOA-3.7.0.so | 2026-10-08
long _ZNK4Aska16CollisionHandler12SearchByNameEPKc(long param_1,undefined8 param_2)

{
  long lVar1;
  int iVar2;
  undefined8 uVar3;
  long lVar4;
  
  if ((*(char *)(param_1 + 0x55) != '\0') && (*(short *)(*(long *)(param_1 + 0x10) + 6) != 0)) {
    lVar4 = 0;
    do {
      lVar1 = *(long *)(param_1 + 8) + (ulong)*(uint *)(*(long *)(param_1 + 0x28) + lVar4 * 4);
      uVar3 = Aska::AcfObject::GetString()(lVar1);
      iVar2 = strcmp(param_2,uVar3);
      if (iVar2 == 0) {
        return lVar1;
      }
      lVar4 = lVar4 + 1;
    } while (lVar4 < (long)(ulong)*(ushort *)(*(long *)(param_1 + 0x10) + 6));
  }
  return 0;
}

// ==== Aska::CollisionHandler::SearchIndexByName(char const*) const
// vaddr 0x209c8ac | ghidra 0x219c8ac | size 124 | symbol _ZNK4Aska16CollisionHandler17SearchIndexByNameEPKc | lib libSOA-3.7.0.so | 2026-10-08
ulong _ZNK4Aska16CollisionHandler17SearchIndexByNameEPKc(long param_1,undefined8 param_2)

{
  int iVar1;
  undefined8 uVar2;
  ulong uVar3;
  ulong uVar4;
  
  if (*(char *)(param_1 + 0x55) == '\0') {
    uVar3 = 0;
  }
  else {
    uVar4 = (ulong)*(ushort *)(*(long *)(param_1 + 0x10) + 6);
    if (uVar4 != 0) {
      uVar3 = 0;
      do {
        uVar2 = Aska::AcfObject::GetString()(*(long *)(param_1 + 8) +
                                (ulong)*(uint *)(*(long *)(param_1 + 0x28) + uVar3 * 4));
        iVar1 = strcmp(param_2,uVar2);
        if (iVar1 == 0) goto code_r0x0219c914;
        uVar3 = uVar3 + 1;
      } while ((long)uVar3 < (long)uVar4);
    }
    uVar3 = 0xffffffff;
  }
code_r0x0219c914:
  return uVar3 & 0xffffffff;
}

// ==== Aska::CollisionHandler::Get(unsigned long, void*) const
// vaddr 0x209c928 | ghidra 0x219c928 | size 296 | symbol _ZNK4Aska16CollisionHandler3GetEmPv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska16CollisionHandler3GetEmPv(long param_1,ulong param_2,float *param_3)

{
  short *psVar1;
  uint uVar2;
  short sVar3;
  undefined8 uVar4;
  float fVar5;
  
  if (*(long *)(param_1 + 0x10) == 0) {
    return 0;
  }
  if ((param_2 & 0xffff00000000) != 0) {
    return 0;
  }
  uVar2 = (uint)(param_2 >> 0x10) & 0xffff;
  if (*(ushort *)(*(long *)(param_1 + 0x10) + 6) <= uVar2) {
    return 0;
  }
  psVar1 = (short *)(*(long *)(param_1 + 8) +
                    (ulong)*(uint *)(*(long *)(param_1 + 0x28) + (ulong)uVar2 * 4));
  if (psVar1 == (short *)0x0) {
    return 0;
  }
  sVar3 = *psVar1;
  if (sVar3 == 2) {
    uVar2 = (uint)param_2 & 0xffff;
    if (uVar2 != 4) {
      if (uVar2 == 3) goto code_r0x0219c9f0;
      if ((param_2 & 0xffff) != 0) {
        return 0;
      }
      goto code_r0x0219ca00;
    }
    *param_3 = *(float *)(psVar1 + 8) + *(float *)(psVar1 + 0x10) * -0.5;
code_r0x0219ca2c:
    param_3[1] = *(float *)(psVar1 + 10);
    param_3[2] = *(float *)(psVar1 + 0xc);
  }
  else {
    if (sVar3 == 1) {
      uVar4 = 0;
      switch(param_2 & 0xffff) {
      case 0:
code_r0x0219c9f0:
        fVar5 = *(float *)(psVar1 + 0x12);
        break;
      case 1:
        goto code_r0x0219ca00;
      case 2:
        fVar5 = *(float *)(psVar1 + 0x14);
        break;
      default:
        goto code_r0x0219ca4c;
      case 4:
        goto code_r0x0219ca08;
      }
    }
    else {
      if (sVar3 != 0) {
        return 0;
      }
      uVar2 = (uint)param_2 & 0xffff;
      if (uVar2 == 4) {
code_r0x0219ca08:
        *param_3 = *(float *)(psVar1 + 8);
        goto code_r0x0219ca2c;
      }
      if (uVar2 != 3) {
        return 0;
      }
code_r0x0219ca00:
      fVar5 = *(float *)(psVar1 + 0x10);
    }
    *param_3 = fVar5;
  }
  uVar4 = 1;
code_r0x0219ca4c:
  return uVar4;
}

// ==== Aska::CollisionHandler::GetAcfObject(unsigned int, void const*, Aska::AcfObject const*, unsigned long)
// vaddr 0x209ca50 | ghidra 0x219ca50 | size 224 | symbol _ZN4Aska16CollisionHandler12GetAcfObjectEjPKvPKNS_9AcfObjectEm | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska16CollisionHandler12GetAcfObjectEjPKvPKNS_9AcfObjectEm
          (int param_1,float *param_2,short *param_3)

{
  short sVar1;
  undefined8 uVar2;
  float fVar3;
  
  if (param_3 == (short *)0x0) {
    return 0;
  }
  sVar1 = *param_3;
  if (sVar1 == 2) {
    if (param_1 != 4) {
      if (param_1 == 3) goto code_r0x0219cad0;
      if (param_1 != 0) {
        return 0;
      }
      goto code_r0x0219cae0;
    }
    *param_2 = *(float *)(param_3 + 8) + *(float *)(param_3 + 0x10) * -0.5;
code_r0x0219cb0c:
    param_2[1] = *(float *)(param_3 + 10);
    param_2[2] = *(float *)(param_3 + 0xc);
  }
  else {
    if (sVar1 == 1) {
      uVar2 = 0;
      switch(param_1) {
      case 0:
code_r0x0219cad0:
        fVar3 = *(float *)(param_3 + 0x12);
        break;
      case 1:
        goto code_r0x0219cae0;
      case 2:
        fVar3 = *(float *)(param_3 + 0x14);
        break;
      default:
        goto code_r0x0219cb2c;
      case 4:
        goto code_r0x0219cae8;
      }
    }
    else {
      if (sVar1 != 0) {
        return 0;
      }
      if (param_1 == 4) {
code_r0x0219cae8:
        *param_2 = *(float *)(param_3 + 8);
        goto code_r0x0219cb0c;
      }
      if (param_1 != 3) {
        return 0;
      }
code_r0x0219cae0:
      fVar3 = *(float *)(param_3 + 0x10);
    }
    *param_2 = fVar3;
  }
  uVar2 = 1;
code_r0x0219cb2c:
  return uVar2;
}

// ==== Aska::CollisionHandler::Set(unsigned long, void const*)
// vaddr 0x209cb30 | ghidra 0x219cb30 | size 152 | symbol _ZN4Aska16CollisionHandler3SetEmPKv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska16CollisionHandler3SetEmPKv(long param_1,ulong param_2,undefined8 param_3)

{
  ulong uVar1;
  undefined8 uVar2;
  ulong uVar3;
  char acStack_24 [4];
  long lStack_18;
  
  if ((((*(long *)(param_1 + 0x10) == 0) ||
       (uVar3 = param_2 >> 0x10 & 0xffff,
       (uint)*(ushort *)(*(long *)(param_1 + 0x10) + 6) <= (uint)uVar3)) ||
      (lStack_18 = 0, (param_2 & 0xffff00000000) != 0)) ||
     (uVar1 = Aska::CollisionHandler::SetAcfObject(bool*, Aska::Vector**, unsigned int, void const*, Aska::AcfObject const*, unsigned long)(acStack_24,&lStack_18,(uint)param_2 & 0xffff,param_3,
                              *(long *)(param_1 + 8) +
                              (ulong)*(uint *)(*(long *)(param_1 + 0x28) + uVar3 * 4)),
     (uVar1 & 1) == 0)) {
    uVar2 = 0;
  }
  else {
    if ((acStack_24[0] != '\0') && (lStack_18 != 0)) {
      Aska::CollisionHandler::UpdateBounding(unsigned int, Aska::Vector*)(param_1,uVar3);
    }
    uVar2 = 1;
  }
  return uVar2;
}

// ==== Aska::CollisionHandler::SetAcfObject(bool*, Aska::Vector**, unsigned int, void const*, Aska::AcfObject const*, unsigned long)
// vaddr 0x209cbc8 | ghidra 0x219cbc8 | size 524 | symbol _ZN4Aska16CollisionHandler12SetAcfObjectEPbPPNS_6VectorEjPKvPKNS_9AcfObjectEm | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska16CollisionHandler12SetAcfObjectEPbPPNS_6VectorEjPKvPKNS_9AcfObjectEm
          (undefined1 *param_1,long *param_2,int param_3,float *param_4,short *param_5)

{
  float fVar1;
  short sVar2;
  undefined8 uVar3;
  float fVar4;
  float fVar5;
  
  if (param_1 != (undefined1 *)0x0) {
    *param_1 = 0;
  }
  sVar2 = *param_5;
  if (sVar2 == 2) {
    *param_2 = (long)(param_5 + 8);
    if (param_3 == 4) {
      *(float *)(param_5 + 8) = *param_4 + *(float *)(param_5 + 0x10) * 0.5;
code_r0x0219cd08:
      *(float *)(*param_2 + 4) = param_4[1];
      *(float *)(*param_2 + 8) = param_4[2];
      goto joined_r0x0219cc1c;
    }
    if (param_3 == 3) {
      fVar4 = *param_4;
      fVar5 = *(float *)(param_5 + 0x10);
      *(float *)(param_5 + 0x12) = fVar4;
    }
    else {
      if (param_3 != 0) {
        return 0;
      }
      fVar5 = *param_4;
      fVar4 = *(float *)(param_5 + 0x10);
      *(float *)(param_5 + 0x10) = fVar5;
      *(float *)*param_2 = (*(float *)(param_5 + 8) - fVar4 * 0.5) + fVar5 * 0.5;
      fVar5 = *(float *)(param_5 + 0x10);
      fVar4 = *(float *)(param_5 + 0x12);
    }
    fVar4 = fVar5 * 0.5 + fVar4;
code_r0x0219cdb8:
    *(float *)(param_5 + 0xe) = fVar4;
  }
  else {
    if (sVar2 == 1) {
      uVar3 = 0;
      *param_2 = (long)(param_5 + 8);
      switch(param_3) {
      case 0:
        fVar1 = *param_4;
        fVar5 = fVar1 * fVar1 + *(float *)(param_5 + 0x10) * *(float *)(param_5 + 0x10) +
                *(float *)(param_5 + 0x14) * *(float *)(param_5 + 0x14);
        fVar4 = SQRT(fVar5);
        *(float *)(param_5 + 0x12) = fVar1;
        if (!NAN(fVar4)) goto code_r0x0219cdb8;
        goto code_r0x0219cdb0;
      case 1:
        fVar4 = *param_4;
        fVar5 = fVar4 * fVar4 + *(float *)(param_5 + 0x12) * *(float *)(param_5 + 0x12) +
                *(float *)(param_5 + 0x14) * *(float *)(param_5 + 0x14);
        *(float *)(param_5 + 0x10) = fVar4;
        break;
      case 2:
        fVar4 = *param_4;
        fVar5 = *(float *)(param_5 + 0x10) * *(float *)(param_5 + 0x10) +
                *(float *)(param_5 + 0x12) * *(float *)(param_5 + 0x12) + fVar4 * fVar4;
        *(float *)(param_5 + 0x14) = fVar4;
        break;
      default:
        goto code_r0x0219cdc8;
      case 4:
        goto code_r0x0219cce4;
      }
      fVar4 = SQRT(fVar5);
      if (NAN(fVar4)) {
code_r0x0219cdb0:
        fVar4 = (float)sqrtf(fVar5,0);
      }
      goto code_r0x0219cdb8;
    }
    if (sVar2 != 0) {
      return 0;
    }
    *param_2 = (long)(param_5 + 8);
    if (param_3 == 4) {
code_r0x0219cce4:
      *(float *)(param_5 + 8) = *param_4;
      goto code_r0x0219cd08;
    }
    if (param_3 != 3) {
      return 0;
    }
    fVar4 = *param_4;
    *(float *)(param_5 + 0xe) = fVar4;
    *(float *)(param_5 + 0x10) = fVar4;
  }
joined_r0x0219cc1c:
  uVar3 = 1;
  if (param_1 != (undefined1 *)0x0) {
    uVar3 = 1;
    *param_1 = 1;
  }
code_r0x0219cdc8:
  return uVar3;
}

// ==== Aska::CollisionHandler::UpdateBounding(unsigned int, Aska::Vector*)
// vaddr 0x209cdd4 | ghidra 0x219cdd4 | size 1436 | symbol _ZN4Aska16CollisionHandler14UpdateBoundingEjPNS_6VectorE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16CollisionHandler14UpdateBoundingEjPNS_6VectorE
               (long param_1,uint param_2,float *param_3)

{
  ushort uVar1;
  ulong uVar2;
  long lVar3;
  uint uVar4;
  long lVar5;
  float *pfVar6;
  ulong uVar7;
  float *pfVar8;
  float *pfVar9;
  ulong uVar10;
  ushort *puVar11;
  float fVar12;
  float fVar13;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
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
  
  uVar2 = (ulong)*(ushort *)(*(long *)(param_1 + 0x10) + 4);
  if (uVar2 == 0) {
    lVar5 = 0;
    pfVar9 = (float *)0x0;
  }
  else {
    lVar5 = 0;
    pfVar6 = *(float **)(param_1 + 0x20);
    do {
      pfVar9 = pfVar6;
      if ((*(ushort *)((long)pfVar9 + 0x36) <= param_2) &&
         (param_2 < (uint)*(ushort *)(pfVar9 + 0xe) + (uint)*(ushort *)((long)pfVar9 + 0x36)))
      break;
      lVar5 = lVar5 + 1;
      pfVar6 = pfVar9 + 0x10;
    } while (lVar5 < (long)uVar2);
  }
  fVar13 = (*pfVar9 - *param_3) * (*pfVar9 - *param_3) +
           (pfVar9[1] - param_3[1]) * (pfVar9[1] - param_3[1]) +
           (pfVar9[2] - param_3[2]) * (pfVar9[2] - param_3[2]);
  fVar12 = SQRT(fVar13);
  if (NAN(fVar12)) {
    fVar12 = (float)sqrtf(fVar13);
  }
  if (pfVar9[3] < fVar12 + param_3[3]) {
    pfVar9[3] = fVar12 + param_3[3];
    uVar2 = (ulong)*(ushort *)(*(long *)(param_1 + 0x10) + 2);
    if (uVar2 != 0) {
      pfVar8 = *(float **)(param_1 + 0x18);
      uVar7 = 0;
      pfVar6 = pfVar8;
      do {
        uVar1 = *(ushort *)((long)pfVar6 + 0x36);
        uVar4 = (uint)lVar5;
        if (((uVar4 == (uVar1 & 0x7fff)) && (uVar1 != 0xffff)) && ((short)uVar1 < 0)) {
code_r0x0219cf60:
          lVar5 = *(long *)(*(long *)(param_1 + 0x38) + (ulong)*(ushort *)((long)pfVar6 + 0x32) * 8)
          ;
          if (lVar5 == 0) {
            return;
          }
          lVar3 = *(long *)(*(long *)(param_1 + 0x40) + (ulong)*(ushort *)((long)pfVar9 + 0x32) * 8)
          ;
          if (lVar3 == 0) {
            return;
          }
          if ((*(byte *)(lVar5 + 0xf8) & 1) != 0) {
            Aska::HierarchicalObjectContainer::MakeMatrix()(lVar5);
          }
          if ((*(byte *)(lVar3 + 0xf8) & 1) != 0) {
            Aska::HierarchicalObjectContainer::MakeMatrix()(lVar3);
          }
          fStack_70 = *pfVar6;
          fStack_6c = pfVar6[1];
          fStack_68 = pfVar6[2];
          fVar12 = pfVar6[3];
          fStack_80 = *pfVar9;
          fStack_7c = pfVar9[1];
          fStack_78 = pfVar9[2];
          fStack_74 = pfVar9[3];
          if (((fStack_70 == 0.0) && (fStack_6c == 0.0)) && (fStack_68 == 0.0)) {
            fStack_70 = *(float *)(lVar5 + 0x1c);
            fStack_6c = *(float *)(lVar5 + 0x2c);
            fStack_68 = *(float *)(lVar5 + 0x3c);
            if (fStack_80 != 0.0) goto code_r0x0219d090;
code_r0x0219d05c:
            if ((fStack_7c != 0.0) || (fStack_78 != 0.0)) goto code_r0x0219d090;
            fStack_80 = *(float *)(lVar3 + 0x1c);
            fStack_7c = *(float *)(lVar3 + 0x2c);
            fStack_78 = *(float *)(lVar3 + 0x3c);
            fStack_64 = fVar12;
          }
          else {
            fStack_64 = 1.0;
            Aska::Vector::ApplyMatrix(Aska::Matrix const*)(&fStack_70,lVar5 + 0x10);
            if (fStack_80 == 0.0) goto code_r0x0219d05c;
code_r0x0219d090:
            fVar13 = fStack_74;
            fStack_74 = 1.0;
            fStack_64 = fVar12;
            Aska::Vector::ApplyMatrix(Aska::Matrix const*)(&fStack_80,lVar3 + 0x10);
            fStack_74 = fVar13;
          }
          fVar13 = (fStack_70 - fStack_80) * (fStack_70 - fStack_80) +
                   (fStack_6c - fStack_7c) * (fStack_6c - fStack_7c) +
                   (fStack_68 - fStack_78) * (fStack_68 - fStack_78);
          fVar12 = SQRT(fVar13);
          if (NAN(fVar12)) {
            fVar12 = (float)sqrtf(fVar13);
          }
          if (fVar12 + fStack_74 <= fStack_64) {
            return;
          }
          pfVar6[3] = fVar12 + fStack_74;
          goto code_r0x0219d2cc;
        }
        uVar1 = *(ushort *)(pfVar6 + 0xe);
        if (((uVar4 == (uVar1 & 0x7fff)) && (uVar1 != 0xffff)) && ((short)uVar1 < 0))
        goto code_r0x0219cf60;
        uVar1 = *(ushort *)((long)pfVar6 + 0x3a);
        if (((uVar4 == (uVar1 & 0x7fff)) && (uVar1 != 0xffff)) && ((short)uVar1 < 0))
        goto code_r0x0219cf60;
        uVar1 = *(ushort *)(pfVar6 + 0xf);
        if (((uVar4 == (uVar1 & 0x7fff)) && (uVar1 != 0xffff)) && ((short)uVar1 < 0))
        goto code_r0x0219cf60;
        uVar1 = *(ushort *)((long)pfVar6 + 0x3e);
        if (((uVar4 == (uVar1 & 0x7fff)) && (uVar1 != 0xffff)) && ((short)uVar1 < 0))
        goto code_r0x0219cf60;
        uVar7 = uVar7 + 1;
        pfVar6 = pfVar6 + 0x10;
      } while ((long)uVar7 < (long)uVar2);
    }
  }
  return;
code_r0x0219d2cc:
  uVar10 = 0;
  puVar11 = (ushort *)((long)pfVar8 + 0x3e);
  while( true ) {
    uVar1 = puVar11[-4];
    uVar4 = (uint)uVar7;
    if (((uVar4 == uVar1) && (uVar1 != 0xffff)) && (-1 < (short)uVar1)) break;
    uVar1 = puVar11[-3];
    if (((uVar4 == uVar1) && (uVar1 != 0xffff)) && (-1 < (short)uVar1)) break;
    uVar1 = puVar11[-2];
    if (((uVar4 == uVar1) && (uVar1 != 0xffff)) && (-1 < (short)uVar1)) break;
    uVar1 = puVar11[-1];
    if (((uVar4 == uVar1) && (uVar1 != 0xffff)) && (-1 < (short)uVar1)) break;
    uVar1 = *puVar11;
    if (((uVar4 == uVar1) && (uVar1 != 0xffff)) && (-1 < (short)uVar1)) break;
    uVar10 = uVar10 + 1;
    puVar11 = puVar11 + 0x20;
    if ((long)uVar2 <= (long)uVar10) {
      return;
    }
  }
  lVar5 = *(long *)(*(long *)(param_1 + 0x38) + (ulong)*(ushort *)((long)pfVar6 + 0x32) * 8);
  if (lVar5 == 0) {
    return;
  }
  lVar3 = *(long *)(*(long *)(param_1 + 0x38) + (ulong)puVar11[-6] * 8);
  if (lVar3 == 0) {
    return;
  }
  if ((*(byte *)(lVar5 + 0xf8) & 1) != 0) {
    Aska::HierarchicalObjectContainer::MakeMatrix()(lVar5);
  }
  if ((*(byte *)(lVar3 + 0xf8) & 1) != 0) {
    Aska::HierarchicalObjectContainer::MakeMatrix()(lVar3);
  }
  fStack_90 = *pfVar6;
  fStack_8c = pfVar6[1];
  fStack_88 = pfVar6[2];
  fVar12 = pfVar6[3];
  fStack_a0 = *(float *)(puVar11 + -0x1f);
  fStack_9c = *(float *)(puVar11 + -0x1d);
  fStack_98 = *(float *)(puVar11 + -0x1b);
  fStack_94 = *(float *)(puVar11 + -0x19);
  if (((fStack_90 == 0.0) && (fStack_8c == 0.0)) && (fStack_88 == 0.0)) {
    fStack_90 = *(float *)(lVar5 + 0x1c);
    fStack_8c = *(float *)(lVar5 + 0x2c);
    fStack_88 = *(float *)(lVar5 + 0x3c);
    if (fStack_a0 != 0.0) goto code_r0x0219d250;
code_r0x0219d1f8:
    if ((fStack_9c != 0.0) || (fStack_98 != 0.0)) goto code_r0x0219d250;
    fStack_a0 = *(float *)(lVar3 + 0x1c);
    fStack_9c = *(float *)(lVar3 + 0x2c);
    fStack_98 = *(float *)(lVar3 + 0x3c);
    fStack_84 = fVar12;
  }
  else {
    fStack_84 = 1.0;
    Aska::Vector::ApplyMatrix(Aska::Matrix const*)(&fStack_90,lVar5 + 0x10);
    if (fStack_a0 == 0.0) goto code_r0x0219d1f8;
code_r0x0219d250:
    fVar13 = fStack_94;
    fStack_94 = 1.0;
    fStack_84 = fVar12;
    Aska::Vector::ApplyMatrix(Aska::Matrix const*)(&fStack_a0,lVar3 + 0x10);
    fStack_94 = fVar13;
  }
  fVar13 = (fStack_90 - fStack_a0) * (fStack_90 - fStack_a0) +
           (fStack_8c - fStack_9c) * (fStack_8c - fStack_9c) +
           (fStack_88 - fStack_98) * (fStack_88 - fStack_98);
  fVar12 = SQRT(fVar13);
  if (NAN(fVar12)) {
    fVar12 = (float)sqrtf(fVar13);
  }
  if (fVar12 + fStack_84 <= fStack_94) {
    return;
  }
  *(float *)(puVar11 + -0x19) = fVar12 + fStack_84;
  if ((int)uVar10 == 0) {
    return;
  }
  uVar7 = uVar10 & 0xffffffff;
  goto code_r0x0219d2cc;
}

// ==== Aska::CollisionHandler::EnableAcfNode(Aska::AcfSphereTreeLeaf const*, unsigned short, bool)
// vaddr 0x209d370 | ghidra 0x219d370 | size 4 | symbol _ZN4Aska16CollisionHandler13EnableAcfNodeEPKNS_17AcfSphereTreeLeafEtb | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16CollisionHandler13EnableAcfNodeEPKNS_17AcfSphereTreeLeafEtb(void)

{
  return;
}

// ==== Aska::CollisionHandler::Detach()
// vaddr 0x209d374 | ghidra 0x219d374 | size 80 | symbol _ZN4Aska16CollisionHandler6DetachEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16CollisionHandler6DetachEv(long param_1)

{
  if (*(long *)(param_1 + 0x30) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x38) = 0;
    *(undefined8 *)(param_1 + 0x40) = 0;
    *(long *)(param_1 + 0x30) = 0;
  }
  if ((*(char *)(param_1 + 0x54) == '\0') && (*(long *)(param_1 + 8) != 0)) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 8) = 0;
  }
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  return;
}

// ==== Aska::CollisionHandler::UpdateLocalBounding(Aska::AcfPrimitiveData_sphere*)
// vaddr 0x209d3c4 | ghidra 0x219d3c4 | size 12 | symbol _ZN4Aska16CollisionHandler19UpdateLocalBoundingEPNS_23AcfPrimitiveData_sphereE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16CollisionHandler19UpdateLocalBoundingEPNS_23AcfPrimitiveData_sphereE(long param_1)

{
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_1 + 0x10);
  return;
}

// ==== Aska::CollisionHandler::UpdateLocalBounding(Aska::AcfPrimitiveData_cube*)
// vaddr 0x209d3d0 | ghidra 0x219d3d0 | size 68 | symbol _ZN4Aska16CollisionHandler19UpdateLocalBoundingEPNS_21AcfPrimitiveData_cubeE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16CollisionHandler19UpdateLocalBoundingEPNS_21AcfPrimitiveData_cubeE(long param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = *(float *)(param_1 + 0x10) * *(float *)(param_1 + 0x10) +
          *(float *)(param_1 + 0x14) * *(float *)(param_1 + 0x14) +
          *(float *)(param_1 + 0x18) * *(float *)(param_1 + 0x18);
  fVar1 = SQRT(fVar2);
  if (NAN(fVar1)) {
    fVar1 = (float)sqrtf(fVar2);
  }
  *(float *)(param_1 + 0xc) = fVar1;
  return;
}

// ==== Aska::CollisionHandler::UpdateLocalBounding(Aska::AcfPrimitiveData_capsule*)
// vaddr 0x209d414 | ghidra 0x219d414 | size 24 | symbol _ZN4Aska16CollisionHandler19UpdateLocalBoundingEPNS_24AcfPrimitiveData_capsuleE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16CollisionHandler19UpdateLocalBoundingEPNS_24AcfPrimitiveData_capsuleE(long param_1)

{
  *(float *)(param_1 + 0xc) = *(float *)(param_1 + 0x10) * 0.5 + *(float *)(param_1 + 0x14);
  return;
}

// ==== Aska::CollisionHandler::MakeMatrix()
// vaddr 0x209d42c | ghidra 0x219d42c | size 108 | symbol _ZN4Aska16CollisionHandler10MakeMatrixEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16CollisionHandler10MakeMatrixEv(long param_1)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  
  lVar3 = *(long *)(param_1 + 0x10);
  if (*(short *)(lVar3 + 4) != 0) {
    lVar4 = 0;
    do {
      lVar1 = *(long *)(*(long *)(param_1 + 0x40) + lVar4 * 8);
      if ((lVar1 != 0) && ((*(byte *)(lVar1 + 0xf8) & 1) != 0)) {
        plVar2 = *(long **)(lVar1 + 0xe8);
        if (plVar2 == (long *)0x0) {
          Aska::HierarchicalObjectContainer::MakeMatrix()();
        }
        else {
          (**(code **)(*plVar2 + 0xa8))(plVar2);
        }
      }
      lVar4 = lVar4 + 1;
    } while (lVar4 < (long)(ulong)*(ushort *)(lVar3 + 4));
  }
  return;
}

// ==== Aska::CollisionHandler::ExpandBounding()
// vaddr 0x209d498 | ghidra 0x219d498 | size 716 | symbol _ZN4Aska16CollisionHandler14ExpandBoundingEv | lib libSOA-3.7.0.so | 2026-10-08
undefined1 _ZN4Aska16CollisionHandler14ExpandBoundingEv(long param_1)

{
  long *plVar1;
  uint uVar2;
  ushort uVar3;
  bool bVar4;
  bool bVar5;
  undefined1 uVar6;
  int iVar7;
  int *piVar8;
  long *plVar9;
  long lVar10;
  int *piVar11;
  long lVar12;
  long lVar13;
  float *pfVar14;
  float *pfVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fStack_f0;
  float fStack_ec;
  float fStack_e8;
  undefined4 uStack_e4;
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  undefined4 uStack_d4;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  float *apfStack_b0 [8];
  
  uVar6 = 0;
  if (*(char *)(param_1 + 0x57) != '\0') {
    uVar6 = 0;
    uStack_c8 = 0;
    uStack_d0 = 0;
    uStack_b8 = 0;
    uStack_c0 = 0;
    pfVar15 = *(float **)(param_1 + 0x18);
    iVar7 = 0;
    lVar13 = 0;
    plVar1 = (long *)(param_1 + 0x38);
    apfStack_b0[0] = pfVar15;
    piVar11 = (int *)&uStack_d0;
joined_r0x0219d544:
    if (iVar7 < 5) {
      lVar12 = (long)iVar7 + 0x1b;
      do {
        uVar3 = *(ushort *)((long)pfVar15 + lVar12 * 2);
        if (-1 < (short)uVar3) {
          if ((*(char *)(param_1 + 0x55) == '\0') ||
             (*(ushort *)(*(long *)(param_1 + 0x10) + 2) <= uVar3)) {
            pfVar15 = (float *)0x0;
          }
          else {
            pfVar15 = (float *)(*(long *)(param_1 + 0x18) + (ulong)uVar3 * 0x40);
          }
          piVar8 = piVar11 + 1;
          *piVar8 = 0;
          *piVar11 = iVar7;
          iVar7 = *piVar8;
          lVar13 = lVar13 + 1;
          apfStack_b0[lVar13] = pfVar15;
          piVar11 = piVar8;
          goto joined_r0x0219d544;
        }
        lVar10 = lVar12 + -0x1b;
        lVar12 = lVar12 + 1;
        iVar7 = iVar7 + 1;
      } while (lVar10 < 4);
    }
    lVar12 = *(long *)(*plVar1 + (ulong)*(ushort *)((long)pfVar15 + 0x32) * 8);
    if (lVar12 != 0) {
      if ((*(byte *)(lVar12 + 0xf8) & 1) != 0) {
        Aska::HierarchicalObjectContainer::MakeMatrix()(lVar12);
      }
      fStack_e0 = *pfVar15;
      fVar18 = pfVar15[3];
      fStack_dc = pfVar15[1];
      fStack_d8 = pfVar15[2];
      uStack_d4 = 0x3f800000;
      Aska::Vector::ApplyMatrix(Aska::Matrix const*)(&fStack_e0,lVar12 + 0x10);
      lVar12 = 0;
      bVar4 = false;
      do {
        uVar3 = *(ushort *)((long)pfVar15 + lVar12 + 0x36);
        if (uVar3 != 0xffff) {
          if ((short)uVar3 < 0) {
            plVar9 = (long *)(param_1 + 0x40);
            if ((*(char *)(param_1 + 0x55) == '\0') ||
               (uVar2 = uVar3 & 0x7fff, *(ushort *)(*(long *)(param_1 + 0x10) + 4) <= uVar2)) {
              pfVar14 = (float *)0x0;
            }
            else {
              pfVar14 = (float *)(*(long *)(param_1 + 0x20) + (ulong)uVar2 * 0x40);
            }
          }
          else {
            plVar9 = plVar1;
            if ((*(char *)(param_1 + 0x55) == '\0') ||
               ((uint)*(ushort *)(*(long *)(param_1 + 0x10) + 2) <= (uint)uVar3)) {
              pfVar14 = (float *)0x0;
            }
            else {
              pfVar14 = (float *)(*(long *)(param_1 + 0x18) + (ulong)uVar3 * 0x40);
            }
          }
          lVar10 = *(long *)(*plVar9 + (ulong)*(ushort *)((long)pfVar14 + 0x32) * 8);
          if (lVar10 != 0) {
            if ((*(byte *)(lVar10 + 0xf8) & 1) != 0) {
              Aska::HierarchicalObjectContainer::MakeMatrix()(lVar10);
            }
            fStack_f0 = *pfVar14;
            fVar19 = pfVar14[3];
            fStack_ec = pfVar14[1];
            fStack_e8 = pfVar14[2];
            uStack_e4 = 0x3f800000;
            Aska::Vector::ApplyMatrix(Aska::Matrix const*)(&fStack_f0,lVar10 + 0x10);
            fVar17 = (fStack_e0 - fStack_f0) * (fStack_e0 - fStack_f0) +
                     (fStack_dc - fStack_ec) * (fStack_dc - fStack_ec) +
                     (fStack_d8 - fStack_e8) * (fStack_d8 - fStack_e8);
            fVar16 = SQRT(fVar17);
            if (NAN(fVar16)) {
              fVar16 = (float)sqrtf(fVar17);
            }
            fVar19 = fVar19 + fVar16;
            bVar5 = fVar18 < fVar19;
            if (!bVar5) {
              fVar19 = fVar18;
            }
            fVar18 = fVar19;
            bVar4 = (bool)(bVar4 | bVar5);
          }
        }
        lVar12 = lVar12 + 2;
      } while (lVar12 != 10);
      if (bVar4) {
        pfVar15[3] = fVar18;
        uVar6 = 1;
      }
    }
    if (lVar13 != 0) {
      piVar11 = piVar11 + -1;
      lVar13 = lVar13 + -1;
      pfVar15 = apfStack_b0[lVar13];
      iVar7 = *piVar11 + 1;
      *piVar11 = iVar7;
      goto joined_r0x0219d544;
    }
  }
  return uVar6;
}

// ==== Aska::CollisionHandler::~CollisionHandler()
// vaddr 0x209d764 | ghidra 0x219d764 | size 104 | symbol _ZN4Aska16CollisionHandlerD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16CollisionHandlerD2Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska16CollisionHandlerE_02cbe6e8 + 0x10);
  if (param_1[6] != 0) {
    operator delete[](void*)();
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[6] = 0;
  }
  plVar1 = param_1 + 1;
  if ((*(char *)((long)param_1 + 0x54) == '\0') && (*plVar1 != 0)) {
    operator delete[](void*)();
    *plVar1 = 0;
  }
  *(undefined4 *)((long)param_1 + 0x54) = 0;
  *plVar1 = 0;
  param_1[2] = 0;
  (*(code *)PTR__ZN4Aska11IAnimatableD2Ev_02cb13b8)(param_1);
  return;
}

// ==== Aska::CollisionHandler::~CollisionHandler()
// vaddr 0x209d7cc | ghidra 0x219d7cc | size 112 | symbol _ZN4Aska16CollisionHandlerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska16CollisionHandlerD0Ev(long *param_1)

{
  long *plVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska16CollisionHandlerE_02cbe6e8 + 0x10);
  if (param_1[6] != 0) {
    operator delete[](void*)();
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[6] = 0;
  }
  plVar1 = param_1 + 1;
  if ((*(char *)((long)param_1 + 0x54) == '\0') && (*plVar1 != 0)) {
    operator delete[](void*)();
    *plVar1 = 0;
  }
  *(undefined4 *)((long)param_1 + 0x54) = 0;
  *plVar1 = 0;
  param_1[2] = 0;
  Aska::IAnimatable::~IAnimatable()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::CollisionHandler::GetClassID(int) const
// vaddr 0x209d83c | ghidra 0x219d83c | size 24 | symbol _ZNK4Aska16CollisionHandler10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska16CollisionHandler10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0xf000f02d;
  if (param_2 != 0) {
    uVar1 = 0xf000;
  }
  return uVar1;
}

// ==== Aska::DynamicsHandler::SetDispatchHandle(int, unsigned long)
// vaddr 0x209d854 | ghidra 0x219d854 | size 48 | symbol _ZN4Aska15DynamicsHandler17SetDispatchHandleEim | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsHandler17SetDispatchHandleEim(long param_1,uint param_2,undefined8 param_3)

{
  long lVar1;
  
  if (param_2 < 2) {
    *(undefined8 *)(param_1 + (long)(int)param_2 * 8 + 0x20) = param_3;
    lVar1 = *(long *)PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38;
    if (lVar1 != 0) {
      *(byte *)(lVar1 + 0x92) = *(byte *)(lVar1 + 0x92) | 4;
    }
  }
  return;
}

// ==== Aska::DynamicsHandler::SetDirtyToDynamicsManager(unsigned int)
// vaddr 0x209d884 | ghidra 0x219d884 | size 40 | symbol _ZN4Aska15DynamicsHandler25SetDirtyToDynamicsManagerEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsHandler25SetDirtyToDynamicsManagerEj(undefined8 param_1,uint param_2)

{
  long lVar1;
  
  lVar1 = *(long *)PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38;
  if (lVar1 != 0) {
    *(byte *)(lVar1 + 0x92) = (byte)(1 << (ulong)(param_2 & 0x1f)) | *(byte *)(lVar1 + 0x92);
  }
  return;
}

// ==== Aska::DynamicsHandler::SetLevel(unsigned int)
// vaddr 0x209d8ac | ghidra 0x219d8ac | size 72 | symbol _ZN4Aska15DynamicsHandler8SetLevelEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsHandler8SetLevelEj(long param_1,undefined4 param_2)

{
  long lVar1;
  undefined4 uStack_14;
  
  uStack_14 = param_2;
  Aska::DynamicsHandler::NormalizedFlag(unsigned int&)(param_1,&uStack_14);
  *(undefined4 *)(param_1 + 0x30) = uStack_14;
  lVar1 = *(long *)PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38;
  if (lVar1 != 0) {
    *(byte *)(lVar1 + 0x92) = *(byte *)(lVar1 + 0x92) | 2;
  }
  return;
}

// ==== Aska::DynamicsHandler::NormalizedFlag(unsigned int&)
// vaddr 0x209d8f4 | ghidra 0x219d8f4 | size 508 | symbol _ZN4Aska15DynamicsHandler14NormalizedFlagERj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsHandler14NormalizedFlagERj(undefined8 param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = *param_2;
  if ((uVar2 & 1) != 0) {
    *param_2 = 1;
    return;
  }
  if ((uVar2 >> 1 & 1) != 0) {
    *param_2 = 2;
    return;
  }
  if ((uVar2 >> 2 & 1) != 0) {
    *param_2 = 4;
    return;
  }
  if ((uVar2 >> 3 & 1) != 0) {
    *param_2 = 8;
    return;
  }
  if ((uVar2 >> 4 & 1) != 0) {
    *param_2 = 0x10;
    return;
  }
  if ((uVar2 >> 5 & 1) != 0) {
    *param_2 = 0x20;
    return;
  }
  if ((uVar2 >> 6 & 1) != 0) {
    *param_2 = 0x40;
    return;
  }
  if ((uVar2 >> 7 & 1) != 0) {
    *param_2 = 0x80;
    return;
  }
  if ((uVar2 >> 8 & 1) != 0) {
    *param_2 = 0x100;
    return;
  }
  if ((uVar2 >> 9 & 1) != 0) {
    *param_2 = 0x200;
    return;
  }
  if ((uVar2 >> 10 & 1) != 0) {
    *param_2 = 0x400;
    return;
  }
  if ((uVar2 >> 0xb & 1) != 0) {
    *param_2 = 0x800;
    return;
  }
  if ((uVar2 >> 0xc & 1) != 0) {
    *param_2 = 0x1000;
    return;
  }
  if ((uVar2 >> 0xd & 1) != 0) {
    *param_2 = 0x2000;
    return;
  }
  if ((uVar2 >> 0xe & 1) != 0) {
    *param_2 = 0x4000;
    return;
  }
  if ((uVar2 >> 0xf & 1) == 0) {
    if ((uVar2 >> 0x10 & 1) != 0) {
      *param_2 = 0x10000;
      return;
    }
    if ((uVar2 >> 0x11 & 1) != 0) {
      *param_2 = 0x20000;
      return;
    }
    if ((uVar2 >> 0x12 & 1) != 0) {
      *param_2 = 0x40000;
      return;
    }
    if ((uVar2 >> 0x13 & 1) != 0) {
      *param_2 = 0x80000;
      return;
    }
    if ((uVar2 >> 0x14 & 1) != 0) {
      *param_2 = 0x100000;
      return;
    }
    if ((uVar2 >> 0x15 & 1) != 0) {
      *param_2 = 0x200000;
      return;
    }
    if ((uVar2 >> 0x16 & 1) != 0) {
      *param_2 = 0x400000;
      return;
    }
    if ((uVar2 >> 0x17 & 1) == 0) {
      if ((uVar2 >> 0x18 & 1) != 0) {
        *param_2 = 0x1000000;
        return;
      }
      if ((uVar2 >> 0x19 & 1) != 0) {
        *param_2 = 0x2000000;
        return;
      }
      if ((uVar2 >> 0x1a & 1) != 0) {
        *param_2 = 0x4000000;
        return;
      }
      if ((uVar2 >> 0x1b & 1) == 0) {
        if ((uVar2 >> 0x1c & 1) != 0) {
          *param_2 = 0x10000000;
          return;
        }
        if ((uVar2 >> 0x1d & 1) == 0) {
          uVar1 = uVar2 & 0x80000000;
          if ((uVar2 & 0x40000000) != 0) {
            uVar1 = 0x40000000;
          }
          *param_2 = uVar1;
          return;
        }
        *param_2 = 0x20000000;
        return;
      }
      *param_2 = 0x8000000;
      return;
    }
    *param_2 = 0x800000;
    return;
  }
  *param_2 = 0x8000;
  return;
}

// ==== Aska::DynamicsHandler::SetType(unsigned char)
// vaddr 0x209daf0 | ghidra 0x219daf0 | size 36 | symbol _ZN4Aska15DynamicsHandler7SetTypeEh | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsHandler7SetTypeEh(long param_1,undefined1 param_2)

{
  long lVar1;
  
  *(undefined1 *)(param_1 + 0x35) = param_2;
  lVar1 = *(long *)PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38;
  if (lVar1 != 0) {
    *(byte *)(lVar1 + 0x92) = *(byte *)(lVar1 + 0x92) | 8;
  }
  return;
}

// ==== Aska::DynamicsHandler::SetDirtyChangeParameter()
// vaddr 0x209db14 | ghidra 0x219db14 | size 40 | symbol _ZN4Aska15DynamicsHandler23SetDirtyChangeParameterEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsHandler23SetDirtyChangeParameterEv(long param_1)

{
  long lVar1;
  
  *(undefined1 *)(param_1 + 0x36) = 1;
  lVar1 = *(long *)PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38;
  if (lVar1 != 0) {
    *(byte *)(lVar1 + 0x92) = *(byte *)(lVar1 + 0x92) | 0x40;
  }
  return;
}

// ==== Aska::DynamicsHandler::~DynamicsHandler()
// vaddr 0x209db3c | ghidra 0x219db3c | size 48 | symbol _ZN4Aska15DynamicsHandlerD1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsHandlerD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska15DynamicsHandlerE_02cc3b70 + 0x10);
  if (*(long *)PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38 != 0) {
    (*(code *)PTR__ZN4Aska15DynamicsManager6DeleteEPNS_15DynamicsHandlerE_02c92ba0)
              (*(long *)PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38,param_1);
    return;
  }
  return;
}

// ==== Aska::DynamicsHandler::~DynamicsHandler()
// vaddr 0x209db6c | ghidra 0x219db6c | size 60 | symbol _ZN4Aska15DynamicsHandlerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsHandlerD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska15DynamicsHandlerE_02cc3b70 + 0x10);
  if (*(long *)PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38 != 0) {
    Aska::DynamicsManager::Delete(Aska::DynamicsHandler*)(*(long *)PTR__ZN4Aska6Global18m_pDynamicsManagerE_02cbcb38,param_1);
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsHandler::Run(int)
// vaddr 0x209dba8 | ghidra 0x219dba8 | size 4 | symbol _ZN4Aska15DynamicsHandler3RunEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsHandler3RunEi(void)

{
  return;
}

// ==== Aska::DynamicsManager::Initialize()
// vaddr 0x209df20 | ghidra 0x219df20 | size 116 | symbol _ZN4Aska15DynamicsManager10InitializeEv | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska15DynamicsManager10InitializeEv(long param_1)

{
  bool bVar1;
  ulong uVar2;
  
  uVar2 = Aska::Event::Create(bool, bool)(param_1 + 0x28,1,0);
  bVar1 = (uVar2 & 1) != 0;
  if (bVar1) {
    *(long *)(param_1 + 0x128) = param_1 + 0x28;
    Aska::DynamicsHandler::SetDispatchHandle(int, unsigned long)(param_1 + 0xf0,0,0xffffffff);
    Aska::DynamicsHandler::SetDispatchHandle(int, unsigned long)(param_1 + 0xf0,1,0xffffffff);
    *(undefined1 *)(param_1 + 0x90) = 1;
  }
  return bVar1;
}

// ==== Aska::DynamicsManager::GetForceEmitterManager()
// vaddr 0x209df94 | ghidra 0x219df94 | size 152 | symbol _ZN4Aska15DynamicsManager22GetForceEmitterManagerEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsManager22GetForceEmitterManagerEv(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  long *plVar4;
  long *plVar5;
  
  puVar3 = PTR__ZN4Aska15DynamicsManager22m_pForceEmitterManagerE_02cbfcc8;
  if (*(long *)PTR__ZN4Aska15DynamicsManager22m_pForceEmitterManagerE_02cbfcc8 != 0) {
    return;
  }
  plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x70,PTR__ZSt7nothrow_02cb9a80);
  puVar2 = PTR__ZTVN4Aska27DynamicsForceEmitterManagerE_02cbf088;
  if (plVar4 != (long *)0x0) {
    plVar5 = plVar4 + 2;
    *plVar5 = (long)(PTR__ZTVN4Aska21AnimatableLinkElementE_02cc02b8 + 0x10);
    puVar1 = PTR__ZTVN4Aska14AnimatableListE_02cb9290;
    plVar4[3] = (long)plVar5;
    plVar4[4] = (long)plVar5;
    *(undefined4 *)(plVar4 + 5) = 0;
    *(undefined2 *)(plVar4 + 0xc) = 0;
    plVar4[6] = 0;
    plVar4[9] = 0;
    plVar4[10] = 0;
    *(undefined4 *)(plVar4 + 0xb) = 0;
    plVar4[8] = 0;
    plVar4[1] = (long)(puVar1 + 0x10);
    *plVar4 = (long)(puVar2 + 0x10);
    *(undefined4 *)(plVar4 + 7) = 0;
    *(undefined4 *)((long)plVar4 + 0x3c) = 0x3f800000;
  }
  *(long **)puVar3 = plVar4;
  return;
}

// ==== Aska::DynamicsManager::DynamicsManager()
// vaddr 0x209e080 | ghidra 0x219e080 | size 240 | symbol _ZN4Aska15DynamicsManagerC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsManagerC1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined4 uVar3;
  code *pcVar4;
  
  pcVar4 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
  *param_1 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined2 *)((long)param_1 + 0x24) = 0;
  *(undefined1 *)((long)param_1 + 0x26) = 0;
  uVar3 = (*pcVar4)();
  *(undefined4 *)(param_1 + 4) = uVar3;
  *param_1 = (long)(PTR__ZTVN4Aska15DynamicsManagerE_02cc1ef8 + 0x10);
  Aska::Event::Event()(param_1 + 5);
  *(undefined2 *)(param_1 + 0x12) = 0;
  *(undefined1 *)((long)param_1 + 0x92) = 0;
  *(undefined4 *)((long)param_1 + 0x94) = 0;
  puVar2 = PTR__ZTVN4Aska15DynamicsHandlerE_02cc3b70;
  puVar1 = PTR__ZTVN4Aska5TListINS_15DynamicsHandlerEEE_02cbf460;
  param_1[0x15] = (long)(param_1 + 0x14);
  param_1[0x16] = (long)(param_1 + 0x14);
  *(undefined4 *)(param_1 + 0x1a) = 0x100;
  *(undefined4 *)(param_1 + 0x24) = 0x100;
  *(undefined1 *)((long)param_1 + 0xd6) = 0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  param_1[0x17] = 0;
  *(undefined4 *)(param_1 + 0x1b) = 0;
  param_1[0x1c] = 0;
  param_1[0x1d] = 0;
  param_1[0x20] = 0;
  param_1[0x21] = 0;
  *(undefined1 *)((long)param_1 + 0x126) = 0;
  param_1[0x22] = 0;
  param_1[0x23] = 0;
  *(undefined1 *)((long)param_1 + 0xd4) = 1;
  *(undefined1 *)((long)param_1 + 0x124) = 1;
  *(undefined1 *)((long)param_1 + 0x125) = 1;
  param_1[0x1e] = (long)(PTR__ZTVN4Aska15BarrierDynamicsE_02cc10a0 + 0x10);
  param_1[0x1f] = 0;
  param_1[0x14] = (long)(puVar2 + 0x10);
  param_1[0x13] = (long)(puVar1 + 0x10);
  memset(param_1 + 0x26,0,0x88);
  *(ushort *)((long)param_1 + 0x24) = *(ushort *)((long)param_1 + 0x24) | 2;
  return;
}

// ==== Aska::DynamicsManager::~DynamicsManager()
// vaddr 0x209e170 | ghidra 0x219e170 | size 148 | symbol _ZN4Aska15DynamicsManagerD2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsManagerD1Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska15DynamicsManagerE_02cc1ef8 + 0x10);
  if ((*(char *)((long)param_1 + 0x91) == '\0') && (param_1[0x1c] != 0)) {
    operator delete[](void*)();
  }
  puVar1 = PTR__ZN4Aska15DynamicsManager22m_pForceEmitterManagerE_02cbfcc8;
  if (*(long **)PTR__ZN4Aska15DynamicsManager22m_pForceEmitterManagerE_02cbfcc8 != (long *)0x0) {
    (**(code **)(**(long **)PTR__ZN4Aska15DynamicsManager22m_pForceEmitterManagerE_02cbfcc8 + 8))();
    *(undefined8 *)puVar1 = 0;
  }
  Aska::Event::Exit()(param_1 + 5);
  Aska::DynamicsHandler::~DynamicsHandler()(param_1 + 0x1e);
  param_1[0x13] = (long)(PTR__ZTVN4Aska5TListINS_15DynamicsHandlerEEE_02cbf460 + 0x10);
  Aska::DynamicsHandler::~DynamicsHandler()(param_1 + 0x14);
  Aska::Event::Exit()(param_1 + 5);
  (*(code *)PTR__ZN4Aska4TaskD1Ev_02c92d10)(param_1);
  return;
}

// ==== Aska::DynamicsManager::~DynamicsManager()
// vaddr 0x209e218 | ghidra 0x219e218 | size 24 | symbol _ZN4Aska15DynamicsManagerD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsManagerD0Ev(undefined8 param_1)

{
  Aska::DynamicsManager::~DynamicsManager()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsManager::CheckSameDispatchGroup(Aska::DynamicsHandler*, Aska::DynamicsHandler*)
// vaddr 0x209e230 | ghidra 0x219e230 | size 120 | symbol _ZN4Aska15DynamicsManager22CheckSameDispatchGroupEPNS_15DynamicsHandlerES2_ | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska15DynamicsManager22CheckSameDispatchGroupEPNS_15DynamicsHandlerES2_
               (undefined8 param_1,long param_2,long param_3)

{
  long lVar1;
  
  if (param_3 == 0) {
    return false;
  }
  lVar1 = *(long *)(param_3 + 0x20);
  if (lVar1 != 0) {
    if (*(long *)(param_2 + 0x20) == lVar1) {
      return true;
    }
    if (*(long *)(param_2 + 0x28) == lVar1) {
      return true;
    }
  }
  lVar1 = *(long *)(param_3 + 0x28);
  if (lVar1 != 0) {
    if (*(long *)(param_2 + 0x20) == lVar1) {
      return true;
    }
    if (*(long *)(param_2 + 0x28) == lVar1) {
      return true;
    }
  }
  return param_2 == param_3;
}

// ==== Aska::DynamicsManager::MakeDispatchGroup(Aska::DynamicsHandler**&, Aska::DynamicsHandler**, Aska::DynamicsHandler**)
// vaddr 0x209e2a8 | ghidra 0x219e2a8 | size 124 | symbol _ZN4Aska15DynamicsManager17MakeDispatchGroupERPPNS_15DynamicsHandlerES3_S3_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsManager17MakeDispatchGroupERPPNS_15DynamicsHandlerES3_S3_
               (undefined8 param_1,ulong *param_2,long *param_3,long *param_4)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  plVar1 = param_3;
  do {
    while( true ) {
      do {
        do {
          plVar1 = plVar1 + 1;
          *param_2 = (ulong)plVar1;
          if (param_4 <= plVar1) {
            return;
          }
          lVar2 = *plVar1;
        } while (lVar2 == 0);
        lVar4 = *(long *)(lVar2 + 0x20);
        lVar3 = *param_3;
      } while ((lVar4 != 0) &&
              ((*(long *)(lVar3 + 0x20) == lVar4 || (*(long *)(lVar3 + 0x28) == lVar4))));
      lVar4 = *(long *)(lVar2 + 0x28);
      if (lVar4 != 0) break;
      if (lVar3 != lVar2) {
        return;
      }
    }
  } while (((*(long *)(lVar3 + 0x20) == lVar4) || (lVar3 == lVar2)) ||
          (*(long *)(lVar3 + 0x28) == lVar4));
  return;
}

// ==== Aska::DynamicsManager::Run(int)
// vaddr 0x209e324 | ghidra 0x219e324 | size 304 | symbol _ZN4Aska15DynamicsManager3RunEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsManager3RunEi(long param_1,int param_2)

{
  long *plVar1;
  int iVar2;
  undefined *puVar3;
  undefined *puVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  long *plVar9;
  long *plVar10;
  undefined8 uVar11;
  
  puVar4 = PTR__ZN4Aska21DynamicsCommandNotify23m_DynamicsCommandNotifyE_02cb9390;
  puVar3 = PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8;
  plVar9 = *(long **)(param_1 + 0xe8);
  if (plVar9 != (long *)0x0) {
    iVar2 = *(int *)(param_1 + (long)param_2 * 4 + 0x130);
    if (iVar2 != 0) {
      plVar1 = plVar9 + iVar2;
      if (0 < iVar2) {
        do {
          plVar10 = plVar9 + 1;
          lVar6 = *plVar9;
          if (lVar6 != 0) {
            for (; plVar10 < plVar1; plVar10 = plVar10 + 1) {
              lVar7 = *plVar10;
              if ((lVar7 != 0) &&
                 ((lVar8 = *(long *)(lVar7 + 0x20), lVar8 == 0 ||
                  ((*(long *)(lVar6 + 0x20) != lVar8 && (*(long *)(lVar6 + 0x28) != lVar8)))))) {
                lVar8 = *(long *)(lVar7 + 0x28);
                if (lVar8 == 0) {
                  if (lVar6 != lVar7) break;
                }
                else if (((*(long *)(lVar6 + 0x20) != lVar8) && (lVar6 != lVar7)) &&
                        (*(long *)(lVar6 + 0x28) != lVar8)) break;
              }
            }
            uVar11 = *(undefined8 *)puVar3;
            while (uVar5 = Aska::SimpleMessageDispatcher::PostMessage(unsigned short, Aska::INotify*, void*, void*, unsigned long, unsigned long, unsigned int*, signed char)(uVar11,param_2 + 4,puVar4,plVar9,plVar10,
                                           *(undefined8 *)(lVar6 + 0x20),
                                           *(undefined8 *)(lVar6 + 0x28),0,0), (uVar5 & 1) == 0) {
              Aska::Thread::SleepU(unsigned int)(100);
              lVar6 = *plVar9;
            }
          }
          plVar9 = plVar10;
        } while (plVar10 < plVar1);
      }
      *(long **)(param_1 + 0xe8) = plVar1;
    }
  }
  return;
}

// ==== Aska::DynamicsManager::MakeDynamicsList()
// vaddr 0x209e454 | ghidra 0x219e454 | size 1536 | symbol _ZN4Aska15DynamicsManager16MakeDynamicsListEv | lib libSOA-3.7.0.so | 2026-10-08
/* WARNING: Possible PIC construction at 0x0219e9b0: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0219e9b4) */

void _ZN4Aska15DynamicsManager16MakeDynamicsListEv(long *param_1)

{
  bool bVar1;
  int *piVar2;
  uint uVar3;
  byte bVar4;
  undefined1 auVar5 [16];
  uint uVar6;
  long *plVar7;
  uint uVar8;
  long *plVar9;
  ulong uVar10;
  uint uVar11;
  int iVar12;
  long *plVar13;
  uint uVar14;
  long lVar15;
  int *piVar16;
  long *plVar17;
  long lVar18;
  ulong uVar19;
  long lVar20;
  ulong uVar21;
  long lVar22;
  long *plVar23;
  long *plVar24;
  long *plVar25;
  long *plVar26;
  long *plVar27;
  
  bVar4 = *(byte *)((long)param_1 + 0x92);
  iVar12 = (int)param_1[0x36];
  if (((bVar4 & 1) == 0) || (*(char *)((long)param_1 + 0x91) != '\0')) {
    if (iVar12 != 0) {
joined_r0x0219e48c:
      if (bVar4 == 0) {
        param_1[0x1d] = param_1[0x1c];
        return;
      }
      *(int *)((long)param_1 + 0x1b4) = iVar12 + 1;
      auVar5._8_8_ = 0;
      auVar5._0_8_ = (long)iVar12;
      lVar15 = (long)iVar12 << 3;
      if (SUB168(auVar5 * ZEXT816(8),8) != 0) {
        lVar15 = -1;
      }
      plVar9 = (long *)operator new[](unsigned long, std::nothrow_t const&)(lVar15,PTR__ZSt7nothrow_02cb9a80);
      plVar27 = (long *)param_1[0x1c];
      if ((bVar4 & 0x60) == 0) {
        uVar8 = 0x1000;
        for (plVar13 = (long *)param_1[0x16]; param_1 + 0x14 != plVar13;
            plVar13 = (long *)plVar13[2]) {
          uVar8 = *(uint *)(plVar13 + 6) | uVar8;
        }
      }
      else {
        plVar24 = (long *)param_1[0x16];
        plVar13 = param_1 + 0x14;
        uVar8 = 0x1000;
        if (plVar13 != plVar24) {
          do {
            if (*(char *)((long)plVar24 + 0x34) == '\0') {
              (**(code **)(*plVar24 + 0x38))(plVar24);
              uVar8 = *(uint *)(plVar24 + 6) | uVar8;
            }
            plVar24 = (long *)plVar24[2];
          } while (plVar13 != plVar24);
          for (plVar24 = (long *)param_1[0x16]; plVar13 != plVar24; plVar24 = (long *)plVar24[2]) {
            if (*(char *)((long)plVar24 + 0x34) == '\x01') {
              (**(code **)(*plVar24 + 0x38))(plVar24);
              uVar8 = *(uint *)(plVar24 + 6) | uVar8;
            }
          }
        }
      }
      memset(param_1 + 0x26,0,0x80);
      lVar15 = 0;
      uVar14 = 0x20;
      uVar11 = 0xffffffff;
      do {
        uVar6 = (uint)lVar15;
        uVar3 = uVar11;
        if ((1 << (ulong)(uVar6 & 0x1f) & uVar8) != 0) {
          uVar3 = uVar6;
          if ((int)uVar14 <= lVar15) {
            uVar3 = uVar14;
          }
          uVar14 = uVar3;
          uVar3 = uVar6;
          if (lVar15 <= (int)uVar11) {
            uVar3 = uVar11;
          }
        }
        uVar11 = uVar3;
        lVar15 = lVar15 + 1;
      } while (lVar15 != 0x20);
      if ((int)uVar14 <= (int)uVar11) {
        plVar13 = param_1 + 0x14;
        lVar15 = (long)(int)uVar14;
        do {
          uVar14 = 1 << (ulong)((uint)lVar15 & 0x1f);
          plVar24 = plVar27;
          if ((uVar14 & uVar8) != 0) {
            plVar26 = (long *)param_1[0x16];
            piVar2 = (int *)((long)param_1 + lVar15 * 4 + 0x130);
            plVar25 = plVar13;
            if (plVar13 != plVar26) {
              do {
                if ((*(char *)((long)plVar26 + 0x34) == '\0') &&
                   ((*(uint *)(plVar26 + 6) & uVar14) != 0)) {
                  uVar10 = (**(code **)(*plVar26 + 0x40))(plVar26);
                  if ((uVar10 & 1) == 0) {
                    iVar12 = -1;
                    piVar16 = (int *)((long)param_1 + 0x1b4);
                  }
                  else {
                    *plVar24 = (long)plVar26;
                    iVar12 = 1;
                    piVar16 = piVar2;
                    plVar24 = plVar24 + 1;
                  }
                  *piVar16 = *piVar16 + iVar12;
                }
                plVar26 = (long *)plVar26[2];
              } while (plVar13 != plVar26);
              plVar25 = (long *)param_1[0x16];
            }
            for (; plVar13 != plVar25; plVar25 = (long *)plVar25[2]) {
              if ((*(char *)((long)plVar25 + 0x34) == '\x01') &&
                 ((*(uint *)(plVar25 + 6) & uVar14) != 0)) {
                uVar10 = (**(code **)(*plVar25 + 0x40))(plVar25);
                if ((uVar10 & 1) == 0) {
                  iVar12 = -1;
                  piVar16 = (int *)((long)param_1 + 0x1b4);
                }
                else {
                  *plVar24 = (long)plVar25;
                  iVar12 = 1;
                  piVar16 = piVar2;
                  plVar24 = plVar24 + 1;
                }
                *piVar16 = *piVar16 + iVar12;
              }
            }
            if ((plVar9 != (long *)0x0) && (plVar25 = plVar9, plVar26 = plVar27, plVar27 != plVar24)
               ) {
code_r0x0219e74c:
              lVar18 = *plVar26;
              *plVar26 = 0;
              plVar17 = (long *)0x0;
              *plVar25 = lVar18;
code_r0x0219e76c:
              plVar25 = plVar25 + 1;
              plVar7 = plVar17;
code_r0x0219e7d8:
              plVar17 = plVar7;
              plVar26 = plVar26 + 1;
              if (plVar24 != plVar26) goto code_r0x0219e7e0;
              plVar26 = plVar17;
              if (plVar17 != (long *)0x0) goto code_r0x0219e74c;
              uVar21 = (long)plVar24 + (-8 - (long)plVar27);
              uVar10 = (uVar21 >> 3) + 1;
              plVar25 = plVar9;
              plVar26 = plVar27;
              if (((uVar10 < 4) || (uVar19 = uVar10 & 0x3ffffffffffffffc, uVar19 == 0)) ||
                 ((uVar21 = uVar21 & 0xfffffffffffffff8,
                  plVar27 < (long *)((long)plVar9 + uVar21 + 8) &&
                  (plVar9 < (long *)((long)plVar27 + uVar21 + 8))))) goto code_r0x0219e888;
              plVar25 = plVar27 + 2;
              uVar21 = uVar19;
              plVar26 = plVar9 + 2;
              do {
                plVar17 = plVar26 + -1;
                lVar18 = plVar26[-2];
                lVar22 = plVar26[1];
                lVar20 = *plVar26;
                uVar21 = uVar21 - 4;
                plVar26 = plVar26 + 4;
                plVar25[-1] = *plVar17;
                plVar25[-2] = lVar18;
                plVar25[1] = lVar22;
                *plVar25 = lVar20;
                plVar25 = plVar25 + 4;
              } while (uVar21 != 0);
              plVar25 = plVar9 + uVar19;
              plVar26 = plVar27 + uVar19;
              if (uVar10 != uVar19) {
code_r0x0219e888:
                do {
                  plVar17 = plVar26 + 1;
                  *plVar26 = *plVar25;
                  plVar25 = plVar25 + 1;
                  plVar26 = plVar17;
                } while (plVar24 != plVar17);
              }
              plVar25 = plVar27 + 2;
              plVar26 = plVar24;
              do {
                uVar10 = (**(code **)(*(long *)*plVar27 + 0x28))();
                if ((uVar10 & 1) != 0) {
                  plVar17 = plVar27;
                  plVar7 = (long *)0x0;
                  while (plVar23 = plVar7, plVar17 = plVar17 + 1, plVar24 != plVar17) {
                    uVar10 = (**(code **)(*(long *)*plVar17 + 0x28))();
                    plVar7 = plVar23;
                    if (((uVar10 & 1) != 0) &&
                       (uVar10 = (**(code **)(*(long *)*plVar27 + 0x30))((long *)*plVar27,*plVar17),
                       plVar7 = plVar17, (uVar10 & 1) == 0)) {
                      plVar7 = plVar23;
                    }
                  }
                  if (plVar23 != (long *)0x0) {
                    lVar18 = *plVar27;
                    uVar10 = (long)plVar23 - (long)plVar27 >> 3;
                    if (uVar10 != 0) {
                      if (uVar10 < 4) {
                        uVar21 = 0;
                      }
                      else {
                        uVar21 = uVar10 & 0xfffffffffffffffc;
                        uVar19 = uVar21;
                        plVar26 = plVar25;
                        if (uVar21 != 0) {
                          do {
                            lVar20 = plVar26[-1];
                            lVar22 = plVar26[1];
                            uVar19 = uVar19 - 4;
                            plVar26[-1] = *plVar26;
                            plVar26[-2] = lVar20;
                            plVar26[1] = plVar26[2];
                            *plVar26 = lVar22;
                            plVar26 = plVar26 + 4;
                          } while (uVar19 != 0);
                          if (uVar10 == uVar21) goto code_r0x0219e96c;
                        }
                      }
                      do {
                        plVar26 = plVar27 + uVar21;
                        uVar21 = uVar21 + 1;
                        *plVar26 = plVar26[1];
                      } while (uVar10 != uVar21);
                    }
code_r0x0219e96c:
                    *plVar23 = lVar18;
                    plVar26 = plVar23;
                  }
                }
                plVar27 = plVar27 + 1;
                plVar25 = plVar25 + 1;
              } while (plVar27 != plVar26);
            }
          }
          bVar1 = lVar15 < (int)uVar11;
          plVar27 = plVar24;
          lVar15 = lVar15 + 1;
        } while (bVar1);
      }
      if (plVar9 != (long *)0x0) {
        operator delete[](void*)(plVar9);
      }
      goto code_r0x011ea100;
    }
  }
  else {
    plVar27 = param_1 + 0x1c;
    if (*plVar27 != 0) {
      operator delete[](void*)();
    }
    if (iVar12 == 0) {
      *plVar27 = 0;
      param_1[0x1d] = 0;
    }
    else {
      lVar15 = operator new[](unsigned long, std::nothrow_t const&)((ulong)(iVar12 + 1) << 3,PTR__ZSt7nothrow_02cb9a80);
      *plVar27 = lVar15;
      if (lVar15 != 0) {
        bVar4 = *(byte *)((long)param_1 + 0x92);
        goto joined_r0x0219e48c;
      }
    }
  }
  *(undefined4 *)((long)param_1 + 0x1b4) = 0;
  *(ushort *)((long)param_1 + 0x24) = *(ushort *)((long)param_1 + 0x24) | 2;
  memset(param_1 + 0x26,0,0x80);
  uVar8 = (**(code **)(*param_1 + 0x58))(param_1);
code_r0x011ea100:
  (*(code *)PTR__ZN4Aska4Task11ChangeLevelEj_02cad070)(param_1,uVar8);
  return;
code_r0x0219e7e0:
  lVar20 = *plVar26;
  plVar7 = plVar17;
  if (lVar20 != 0) {
    lVar22 = *(long *)(lVar20 + 0x20);
    if ((lVar22 != 0) &&
       ((*(long *)(lVar18 + 0x20) == lVar22 || (*(long *)(lVar18 + 0x28) == lVar22))))
    goto code_r0x0219e764;
    lVar22 = *(long *)(lVar20 + 0x28);
    if (lVar22 == 0) {
      if (lVar18 == lVar20) goto code_r0x0219e764;
    }
    else if (((*(long *)(lVar18 + 0x20) == lVar22) || (lVar18 == lVar20)) ||
            (*(long *)(lVar18 + 0x28) == lVar22)) goto code_r0x0219e764;
    plVar7 = plVar26;
    if (plVar17 != (long *)0x0) {
      plVar7 = plVar17;
    }
  }
  goto code_r0x0219e7d8;
code_r0x0219e764:
  *plVar25 = lVar20;
  *plVar26 = 0;
  goto code_r0x0219e76c;
}

// ==== Aska::DynamicsManager::IncrementLevelCount(unsigned int)
// vaddr 0x209ea54 | ghidra 0x219ea54 | size 44 | symbol _ZN4Aska15DynamicsManager19IncrementLevelCountEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsManager19IncrementLevelCountEj(long param_1,uint param_2)

{
  do {
    if ((param_2 & 1) != 0) {
      *(int *)(param_1 + 0x1b0) = *(int *)(param_1 + 0x1b0) + 1;
    }
    param_2 = param_2 >> 1;
  } while (param_2 != 0);
  *(ushort *)(param_1 + 0x24) = *(ushort *)(param_1 + 0x24) & 0xfffd;
  return;
}

// ==== Aska::DynamicsManager::DecrementLevelCount(unsigned int)
// vaddr 0x209ea80 | ghidra 0x219ea80 | size 32 | symbol _ZN4Aska15DynamicsManager19DecrementLevelCountEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsManager19DecrementLevelCountEj(long param_1,uint param_2)

{
  for (; param_2 != 0; param_2 = param_2 >> 1) {
    if ((param_2 & 1) != 0) {
      *(int *)(param_1 + 0x1b0) = *(int *)(param_1 + 0x1b0) + -1;
    }
  }
  return;
}

// ==== Aska::DynamicsManager::Add(Aska::DynamicsHandler*, unsigned int)
// vaddr 0x209eaa0 | ghidra 0x219eaa0 | size 200 | symbol _ZN4Aska15DynamicsManager3AddEPNS_15DynamicsHandlerEj | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska15DynamicsManager3AddEPNS_15DynamicsHandlerEj(long param_1,long param_2,uint param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  if (param_2 == 0) {
code_r0x0219eae8:
    uVar1 = 0;
  }
  else {
    if (*(int *)(param_1 + 0xd8) != 0) {
      for (lVar2 = *(long *)(param_1 + 0xb0); param_1 + 0xa0 != lVar2;
          lVar2 = *(long *)(lVar2 + 0x10)) {
        if (lVar2 == param_2) goto code_r0x0219eae8;
      }
    }
    if (param_3 == 0) {
      param_3 = *(uint *)(param_2 + 0x30);
    }
    Aska::DynamicsHandler::SetLevel(unsigned int)(param_2,param_3);
    do {
      if ((param_3 & 1) != 0) {
        *(int *)(param_1 + 0x1b0) = *(int *)(param_1 + 0x1b0) + 1;
      }
      param_3 = param_3 >> 1;
    } while (param_3 != 0);
    lVar2 = *(long *)(param_1 + 0xa8);
    uVar1 = 1;
    *(ushort *)(param_1 + 0x24) = *(ushort *)(param_1 + 0x24) & 0xfffd;
    *(long *)(param_2 + 8) = lVar2;
    *(long *)(param_2 + 0x10) = param_1 + 0xa0;
    *(long *)(param_1 + 0xa8) = param_2;
    *(long *)(lVar2 + 0x10) = param_2;
    *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0xd8) + 1;
    *(byte *)(param_1 + 0x92) = *(byte *)(param_1 + 0x92) | 1;
  }
  return uVar1;
}

// ==== Aska::DynamicsManager::Exists(Aska::DynamicsHandler*)
// vaddr 0x209eb68 | ghidra 0x219eb68 | size 76 | symbol _ZN4Aska15DynamicsManager6ExistsEPNS_15DynamicsHandlerE | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska15DynamicsManager6ExistsEPNS_15DynamicsHandlerE(long param_1,long param_2)

{
  long lVar1;
  
  if (*(int *)(param_1 + 0xd8) == 0) {
    return 0;
  }
  lVar1 = *(long *)(param_1 + 0xb0);
  if (param_1 + 0xa0 != lVar1) {
    do {
      if (lVar1 == param_2) {
        return 1;
      }
      lVar1 = *(long *)(lVar1 + 0x10);
    } while (param_1 + 0xa0 != lVar1);
    return 0;
  }
  return 0;
}

// ==== Aska::DynamicsManager::AddTop(Aska::DynamicsHandler*, unsigned int)
// vaddr 0x209ebd8 | ghidra 0x219ebd8 | size 200 | symbol _ZN4Aska15DynamicsManager6AddTopEPNS_15DynamicsHandlerEj | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska15DynamicsManager6AddTopEPNS_15DynamicsHandlerEj(long param_1,long param_2,uint param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  if (param_2 == 0) {
code_r0x0219ec20:
    uVar1 = 0;
  }
  else {
    if (*(int *)(param_1 + 0xd8) != 0) {
      for (lVar2 = *(long *)(param_1 + 0xb0); param_1 + 0xa0 != lVar2;
          lVar2 = *(long *)(lVar2 + 0x10)) {
        if (lVar2 == param_2) goto code_r0x0219ec20;
      }
    }
    if (param_3 == 0) {
      param_3 = *(uint *)(param_2 + 0x30);
    }
    Aska::DynamicsHandler::SetLevel(unsigned int)(param_2,param_3);
    do {
      if ((param_3 & 1) != 0) {
        *(int *)(param_1 + 0x1b0) = *(int *)(param_1 + 0x1b0) + 1;
      }
      param_3 = param_3 >> 1;
    } while (param_3 != 0);
    uVar1 = 1;
    lVar2 = *(long *)(param_1 + 0xb0);
    *(ushort *)(param_1 + 0x24) = *(ushort *)(param_1 + 0x24) & 0xfffd;
    *(long *)(param_2 + 8) = param_1 + 0xa0;
    *(long *)(param_2 + 0x10) = lVar2;
    *(long *)(lVar2 + 8) = param_2;
    *(long *)(param_1 + 0xb0) = param_2;
    *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0xd8) + 1;
    *(byte *)(param_1 + 0x92) = *(byte *)(param_1 + 0x92) | 1;
  }
  return uVar1;
}

// ==== Aska::DynamicsManager::Insert(Aska::DynamicsHandler*, Aska::DynamicsHandler*, unsigned int)
// vaddr 0x209ecc4 | ghidra 0x219ecc4 | size 236 | symbol _ZN4Aska15DynamicsManager6InsertEPNS_15DynamicsHandlerES2_j | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska15DynamicsManager6InsertEPNS_15DynamicsHandlerES2_j
          (long param_1,long param_2,long param_3,uint param_4)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  if ((param_3 != 0) && (*(int *)(param_1 + 0xd8) != 0)) {
    lVar2 = *(long *)(param_1 + 0xb0);
    lVar3 = param_1 + 0xa0;
    lVar4 = lVar2;
    if (lVar3 != lVar2) {
      do {
        if (lVar4 == param_3) {
          return 0;
        }
        plVar1 = (long *)(lVar4 + 0x10);
        lVar4 = *plVar1;
      } while (lVar3 != *plVar1);
      for (; lVar3 != lVar2; lVar2 = *(long *)(lVar2 + 0x10)) {
        if (lVar2 == param_2) {
          if (param_4 == 0) {
            param_4 = *(uint *)(param_3 + 0x30);
          }
          Aska::DynamicsHandler::SetLevel(unsigned int)(param_3,param_4);
          do {
            if ((param_4 & 1) != 0) {
              *(int *)(param_1 + 0x1b0) = *(int *)(param_1 + 0x1b0) + 1;
            }
            param_4 = param_4 >> 1;
          } while (param_4 != 0);
          *(ushort *)(param_1 + 0x24) = *(ushort *)(param_1 + 0x24) & 0xfffd;
          lVar3 = *(long *)(param_2 + 0x10);
          *(long *)(param_3 + 8) = param_2;
          *(long *)(param_3 + 0x10) = lVar3;
          *(long *)(lVar3 + 8) = param_3;
          *(long *)(param_2 + 0x10) = param_3;
          *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0xd8) + 1;
          *(byte *)(param_1 + 0x92) = *(byte *)(param_1 + 0x92) | 1;
          return 1;
        }
      }
    }
  }
  return 0;
}

// ==== Aska::DynamicsManager::Delete(Aska::DynamicsHandler*)
// vaddr 0x209edd0 | ghidra 0x219edd0 | size 232 | symbol _ZN4Aska15DynamicsManager6DeleteEPNS_15DynamicsHandlerE | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsManager6DeleteEPNS_15DynamicsHandlerE(long param_1,long param_2)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  
  if ((param_2 != 0) && (*(int *)(param_1 + 0xd8) != 0)) {
    for (lVar2 = *(long *)(param_1 + 0xb0); param_1 + 0xa0 != lVar2; lVar2 = *(long *)(lVar2 + 0x10)
        ) {
      if (lVar2 == param_2) {
        lVar2 = *(long *)(param_1 + 0xe0);
        if ((lVar2 != 0) && (uVar1 = *(uint *)(param_1 + 0x1b4), 0 < (int)uVar1)) {
          lVar3 = 0;
          while( true ) {
            if (*(long *)(lVar2 + lVar3 * 8) == param_2) {
              *(undefined8 *)(lVar2 + lVar3 * 8) = 0;
            }
            if ((ulong)uVar1 - 1 == lVar3) break;
            lVar2 = *(long *)(param_1 + 0xe0);
            lVar3 = lVar3 + 1;
          }
        }
        if (param_1 + 0xa0 != param_2) {
          lVar2 = *(long *)(param_2 + 8);
          lVar3 = *(long *)(param_2 + 0x10);
          if (lVar2 != 0) {
            *(long *)(lVar2 + 0x10) = lVar3;
          }
          if (lVar3 != 0) {
            *(long *)(lVar3 + 8) = lVar2;
          }
          if (0 < *(int *)(param_1 + 0xd8)) {
            *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0xd8) + -1;
          }
          *(long *)(param_2 + 8) = 0;
          *(undefined8 *)(param_2 + 0x10) = 0;
        }
        for (uVar1 = *(uint *)(param_2 + 0x30); uVar1 != 0; uVar1 = uVar1 >> 1) {
          if ((uVar1 & 1) != 0) {
            *(int *)(param_1 + 0x1b0) = *(int *)(param_1 + 0x1b0) + -1;
          }
        }
        *(byte *)(param_1 + 0x92) = *(byte *)(param_1 + 0x92) | 1;
        return;
      }
    }
  }
  return;
}

// ==== Aska::DynamicsManager::ChangeLevel(Aska::DynamicsHandler*, unsigned int)
// vaddr 0x209eef8 | ghidra 0x219eef8 | size 128 | symbol _ZN4Aska15DynamicsManager11ChangeLevelEPNS_15DynamicsHandlerEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsManager11ChangeLevelEPNS_15DynamicsHandlerEj
               (long param_1,long param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  
  if ((param_2 != 0) && (uVar1 = *(uint *)(param_2 + 0x30), uVar1 != param_3)) {
    for (; uVar2 = param_3, uVar1 != 0; uVar1 = uVar1 >> 1) {
      if ((uVar1 & 1) != 0) {
        *(int *)(param_1 + 0x1b0) = *(int *)(param_1 + 0x1b0) + -1;
      }
    }
    do {
      if ((uVar2 & 1) != 0) {
        *(int *)(param_1 + 0x1b0) = *(int *)(param_1 + 0x1b0) + 1;
      }
      uVar2 = uVar2 >> 1;
    } while (uVar2 != 0);
    *(ushort *)(param_1 + 0x24) = *(ushort *)(param_1 + 0x24) & 0xfffd;
    Aska::DynamicsHandler::SetLevel(unsigned int)(param_2,param_3);
    *(byte *)(param_1 + 0x92) = *(byte *)(param_1 + 0x92) | 2;
  }
  return;
}

// ==== Aska::DynamicsManager::SetDynamicsListBuffer(unsigned char*)
// vaddr 0x209ef78 | ghidra 0x219ef78 | size 76 | symbol _ZN4Aska15DynamicsManager21SetDynamicsListBufferEPh | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska15DynamicsManager21SetDynamicsListBufferEPh(long param_1,long param_2)

{
  if ((*(char *)(param_1 + 0x91) == '\0') && (*(long *)(param_1 + 0xe0) != 0)) {
    operator delete[](void*)();
  }
  *(long *)(param_1 + 0xe0) = param_2;
  *(bool *)(param_1 + 0x91) = param_2 != 0;
  *(byte *)(param_1 + 0x92) = *(byte *)(param_1 + 0x92) | 1;
  return;
}

// ==== Aska::DynamicsManager::GetClassID(int) const
// vaddr 0x209f350 | ghidra 0x219f350 | size 64 | symbol _ZNK4Aska15DynamicsManager10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska15DynamicsManager10GetClassIDEi(undefined8 param_1,int param_2)

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
  return 0xf002f031;
}

// ==== Aska::DynamicsWait::~DynamicsWait()
// vaddr 0x209f390 | ghidra 0x219f390 | size 24 | symbol _ZN4Aska12DynamicsWaitD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12DynamicsWaitD0Ev(undefined8 param_1)

{
  Aska::Task::~Task()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsWait::GetClassID(int) const
// vaddr 0x209f3a8 | ghidra 0x219f3a8 | size 64 | symbol _ZNK4Aska12DynamicsWait10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska12DynamicsWait10GetClassIDEi(undefined8 param_1,int param_2)

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
  return 0xf002f030;
}

// ==== Aska::DynamicsWait::GetDefaultLevel() const
// vaddr 0x209f3e8 | ghidra 0x219f3e8 | size 8 | symbol _ZNK4Aska12DynamicsWait15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZNK4Aska12DynamicsWait15GetDefaultLevelEv(void)

{
  return 0x1000;
}

// ==== Aska::DynamicsWait::Run(int)
// vaddr 0x209f3f0 | ghidra 0x219f3f0 | size 88 | symbol _ZN4Aska12DynamicsWait3RunEi | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska12DynamicsWait3RunEi(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x28);
  if ((*(int *)(lVar1 + 0x1b4) == 0) || (*(long *)(lVar1 + 0xe0) == 0)) {
    if (*(int *)(lVar1 + 0x1b0) < 1) {
      return;
    }
  }
  else {
    Aska::Event::Wait(unsigned int) const(*(undefined8 *)(param_1 + 0x30),0);
    Aska::Event::Reset() const(*(undefined8 *)(param_1 + 0x30));
    lVar1 = *(long *)(param_1 + 0x28);
  }
  (*(code *)PTR__ZN4Aska15DynamicsManager16MakeDynamicsListEv_02c912e8)(lVar1);
  return;
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::DynamicsListHandler()
// vaddr 0x2324184 | ghidra 0x2424184 | size 56 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEEC1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEEC2Ev(long *param_1)

{
  undefined *puVar1;
  
  *(undefined4 *)(param_1 + 6) = 0x100;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined1 *)((long)param_1 + 0x36) = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  *(undefined1 *)((long)param_1 + 0x34) = 1;
  puVar1 = PTR__ZTVN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEEE_02cc3fc0;
  *(undefined4 *)(param_1 + 9) = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 0;
  return;
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::Clear()
// vaddr 0x23241bc | ghidra 0x24241bc | size 12 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE5ClearEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE5ClearEv(long param_1)

{
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  return;
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::~DynamicsListHandler()
// vaddr 0x23241c8 | ghidra 0x24241c8 | size 4 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEED1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEED2Ev(void)

{
  (*(code *)PTR__ZN4Aska15DynamicsHandlerD2Ev_02cb53e0)();
  return;
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::~DynamicsListHandler()
// vaddr 0x23241cc | ghidra 0x24241cc | size 24 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEED0Ev(undefined8 param_1)

{
  Aska::DynamicsHandler::~DynamicsHandler()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::GetCount()
// vaddr 0x23241e4 | ghidra 0x24241e4 | size 8 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE8GetCountEv | lib libSOA-3.7.0.so | 2026-10-08
undefined4
_ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE8GetCountEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x48);
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::At(unsigned int)
// vaddr 0x23241ec | ghidra 0x24241ec | size 24 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE2AtEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE2AtEj
               (long param_1,int param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x38);
  if ((lVar1 != 0) && (param_2 != 0)) {
    do {
      lVar1 = *(long *)(lVar1 + 0x10);
    } while (lVar1 != 0);
  }
  return;
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::LOOP_START()
// vaddr 0x2324204 | ghidra 0x2424204 | size 8 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE10LOOP_STARTEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE10LOOP_STARTEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x38);
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::LOOP_END(Aska::ArticulatedDynamicsManagerBase*)
// vaddr 0x232420c | ghidra 0x242420c | size 12 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE8LOOP_ENDEPS1_ | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE8LOOP_ENDEPS1_
               (undefined8 param_1,long param_2)

{
  return param_2 == 0;
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::LOOP_NEXT(Aska::ArticulatedDynamicsManagerBase*&)
// vaddr 0x2324218 | ghidra 0x2424218 | size 12 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE9LOOP_NEXTERPS1_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE9LOOP_NEXTERPS1_
          (undefined8 param_1,long *param_2)

{
  return *(undefined8 *)(*param_2 + 0x10);
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::Add(Aska::ArticulatedDynamicsManagerBase*)
// vaddr 0x2324224 | ghidra 0x2424224 | size 64 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE3AddEPS1_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE3AddEPS1_
               (long param_1,long param_2)

{
  if (*(long *)(param_1 + 0x38) == 0) {
    *(undefined8 *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = 0;
    *(long *)(param_1 + 0x38) = param_2;
  }
  else {
    *(long *)(*(long *)(param_1 + 0x40) + 0x10) = param_2;
    *(undefined8 *)(param_2 + 8) = *(undefined8 *)(param_1 + 0x40);
    *(undefined8 *)(param_2 + 0x10) = 0;
  }
  *(long *)(param_1 + 0x40) = param_2;
  *(undefined1 *)(param_1 + 0x36) = 1;
  *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
  return;
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::AddTop(Aska::ArticulatedDynamicsManagerBase*)
// vaddr 0x2324264 | ghidra 0x2424264 | size 92 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE6AddTopEPS1_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE6AddTopEPS1_
               (long param_1,long param_2)

{
  int iVar1;
  
  if (*(long *)(param_1 + 0x38) == 0) {
    *(undefined8 *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = 0;
    iVar1 = *(int *)(param_1 + 0x48) + 1;
    *(long *)(param_1 + 0x38) = param_2;
    *(long *)(param_1 + 0x40) = param_2;
    *(int *)(param_1 + 0x48) = iVar1;
    *(undefined1 *)(param_1 + 0x36) = 1;
  }
  else {
    *(long *)(*(long *)(param_1 + 0x38) + 8) = param_2;
    *(undefined8 *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = *(undefined8 *)(param_1 + 0x38);
    *(long *)(param_1 + 0x38) = param_2;
    iVar1 = *(int *)(param_1 + 0x48);
  }
  *(int *)(param_1 + 0x48) = iVar1 + 1;
  *(undefined1 *)(param_1 + 0x36) = 1;
  return;
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::Insert(Aska::ArticulatedDynamicsManagerBase*, Aska::ArticulatedDynamicsManagerBase*)
// vaddr 0x23242c0 | ghidra 0x24242c0 | size 192 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE6InsertEPS1_S3_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE6InsertEPS1_S3_
          (long param_1,long param_2,long param_3)

{
  long lVar1;
  int iVar2;
  
  lVar1 = *(long *)(param_1 + 0x38);
  if (param_2 == 0) {
    if (lVar1 == 0) {
      *(undefined8 *)(param_3 + 8) = 0;
      *(undefined8 *)(param_3 + 0x10) = 0;
      iVar2 = *(int *)(param_1 + 0x48) + 1;
      *(long *)(param_1 + 0x38) = param_3;
      *(long *)(param_1 + 0x40) = param_3;
      *(int *)(param_1 + 0x48) = iVar2;
      *(undefined1 *)(param_1 + 0x36) = 1;
    }
    else {
      *(long *)(lVar1 + 8) = param_3;
      *(undefined8 *)(param_3 + 8) = 0;
      *(undefined8 *)(param_3 + 0x10) = *(undefined8 *)(param_1 + 0x38);
      *(long *)(param_1 + 0x38) = param_3;
      iVar2 = *(int *)(param_1 + 0x48);
    }
    *(int *)(param_1 + 0x48) = iVar2 + 1;
    *(undefined1 *)(param_1 + 0x36) = 1;
    return 1;
  }
  if (lVar1 != 0) {
    do {
      if (lVar1 == param_2) {
        lVar1 = *(long *)(param_2 + 0x10);
        *(long *)(param_3 + 8) = param_2;
        *(long *)(param_3 + 0x10) = lVar1;
        if (lVar1 == 0) {
          *(long *)(param_1 + 0x40) = param_3;
        }
        else {
          *(long *)(lVar1 + 8) = param_3;
        }
        *(long *)(param_2 + 0x10) = param_3;
        *(undefined1 *)(param_1 + 0x36) = 1;
        *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
        return 1;
      }
      lVar1 = *(long *)(lVar1 + 0x10);
    } while (lVar1 != 0);
    return 0;
  }
  return 0;
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::Delete(Aska::ArticulatedDynamicsManagerBase*)
// vaddr 0x2324380 | ghidra 0x2424380 | size 140 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE6DeleteEPS1_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE6DeleteEPS1_
          (long param_1,long param_2)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  
  plVar2 = (long *)(param_1 + 0x38);
  lVar3 = *plVar2;
  if (lVar3 == 0) {
    return 0;
  }
  while (lVar3 != param_2) {
    lVar3 = *(long *)(lVar3 + 0x10);
    if (lVar3 == 0) {
      return 0;
    }
  }
  lVar3 = *(long *)(param_2 + 8);
  lVar1 = *(long *)(param_2 + 0x10);
  if (lVar3 == 0) {
    if (lVar1 == 0) {
      *(undefined4 *)(param_1 + 0x48) = 0;
      *plVar2 = 0;
      *(undefined8 *)(param_1 + 0x40) = 0;
      goto code_r0x024243f0;
    }
    *(undefined8 *)(lVar1 + 8) = 0;
    *plVar2 = lVar1;
  }
  else if (lVar1 == 0) {
    *(undefined8 *)(lVar3 + 0x10) = 0;
    *(long *)(param_1 + 0x40) = lVar3;
  }
  else {
    *(long *)(lVar3 + 0x10) = lVar1;
    *(long *)(lVar1 + 8) = lVar3;
  }
  *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + -1;
code_r0x024243f0:
  *(undefined1 *)(param_1 + 0x36) = 1;
  return 1;
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::Exists(Aska::ArticulatedDynamicsManagerBase*)
// vaddr 0x232440c | ghidra 0x242440c | size 40 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE6ExistsEPS1_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE6ExistsEPS1_
          (long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x38);
  while( true ) {
    if (lVar1 == 0) {
      return 0;
    }
    if (lVar1 == param_2) break;
    lVar1 = *(long *)(lVar1 + 0x10);
  }
  return 1;
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::DeleteFromList(Aska::ArticulatedDynamicsManagerBase*)
// vaddr 0x2324434 | ghidra 0x2424434 | size 84 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE14DeleteFromListEPS1_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE14DeleteFromListEPS1_
               (long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  lVar1 = *(long *)(param_2 + 8);
  lVar2 = *(long *)(param_2 + 0x10);
  if (lVar1 == 0) {
    if (lVar2 == 0) {
      *(undefined4 *)(param_1 + 0x48) = 0;
      *(undefined8 *)(param_1 + 0x38) = 0;
      *(undefined8 *)(param_1 + 0x40) = 0;
      goto code_r0x02424470;
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
code_r0x02424470:
  *(undefined1 *)(param_1 + 0x36) = 1;
  return;
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::DeleteAll()
// vaddr 0x2324488 | ghidra 0x2424488 | size 12 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE9DeleteAllEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE9DeleteAllEv(long param_1)

{
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  return;
}

// ==== Aska::DynamicsListHandler<Aska::ArticulatedDynamicsManagerBase>::GetIndex(Aska::ArticulatedDynamicsManagerBase*)
// vaddr 0x2324494 | ghidra 0x2424494 | size 40 | symbol _ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE8GetIndexEPS1_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska19DynamicsListHandlerINS_30ArticulatedDynamicsManagerBaseEE8GetIndexEPS1_
          (long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x38);
  while( true ) {
    if (lVar1 == 0) {
      return 0xffffffff;
    }
    if (lVar1 == param_2) break;
    lVar1 = *(long *)(lVar1 + 0x10);
  }
  return 0;
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::DynamicsListHandler()
// vaddr 0x23383c0 | ghidra 0x24383c0 | size 56 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEEC2Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEEC1Ev(long *param_1)

{
  undefined *puVar1;
  
  *(undefined4 *)(param_1 + 6) = 0x100;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined1 *)((long)param_1 + 0x36) = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  *(undefined1 *)((long)param_1 + 0x34) = 1;
  puVar1 = PTR__ZTVN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEEE_02cbfee0;
  *(undefined4 *)(param_1 + 9) = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 0;
  return;
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::Clear()
// vaddr 0x23383f8 | ghidra 0x24383f8 | size 12 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE5ClearEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE5ClearEv(long param_1)

{
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  return;
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::~DynamicsListHandler()
// vaddr 0x2338404 | ghidra 0x2438404 | size 4 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEED1Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEED2Ev(void)

{
  (*(code *)PTR__ZN4Aska15DynamicsHandlerD2Ev_02cb53e0)();
  return;
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::~DynamicsListHandler()
// vaddr 0x2338408 | ghidra 0x2438408 | size 24 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEED0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEED0Ev(undefined8 param_1)

{
  Aska::DynamicsHandler::~DynamicsHandler()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::GetCount()
// vaddr 0x2338420 | ghidra 0x2438420 | size 8 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE8GetCountEv | lib libSOA-3.7.0.so | 2026-10-08
undefined4 _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE8GetCountEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x48);
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::At(unsigned int)
// vaddr 0x2338428 | ghidra 0x2438428 | size 24 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE2AtEj | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE2AtEj(long param_1,int param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x38);
  if ((lVar1 != 0) && (param_2 != 0)) {
    do {
      lVar1 = *(long *)(lVar1 + 0x10);
    } while (lVar1 != 0);
  }
  return;
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::LOOP_START()
// vaddr 0x2338440 | ghidra 0x2438440 | size 8 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE10LOOP_STARTEv | lib libSOA-3.7.0.so | 2026-10-08
undefined8 _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE10LOOP_STARTEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x38);
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::LOOP_END(Aska::DynamicsPrimitive*)
// vaddr 0x2338448 | ghidra 0x2438448 | size 12 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE8LOOP_ENDEPS1_ | lib libSOA-3.7.0.so | 2026-10-08
bool _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE8LOOP_ENDEPS1_
               (undefined8 param_1,long param_2)

{
  return param_2 == 0;
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::LOOP_NEXT(Aska::DynamicsPrimitive*&)
// vaddr 0x2338454 | ghidra 0x2438454 | size 12 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE9LOOP_NEXTERPS1_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE9LOOP_NEXTERPS1_
          (undefined8 param_1,long *param_2)

{
  return *(undefined8 *)(*param_2 + 0x10);
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::Add(Aska::DynamicsPrimitive*)
// vaddr 0x2338460 | ghidra 0x2438460 | size 64 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE3AddEPS1_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE3AddEPS1_(long param_1,long param_2)

{
  if (*(long *)(param_1 + 0x38) == 0) {
    *(undefined8 *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = 0;
    *(long *)(param_1 + 0x38) = param_2;
  }
  else {
    *(long *)(*(long *)(param_1 + 0x40) + 0x10) = param_2;
    *(undefined8 *)(param_2 + 8) = *(undefined8 *)(param_1 + 0x40);
    *(undefined8 *)(param_2 + 0x10) = 0;
  }
  *(long *)(param_1 + 0x40) = param_2;
  *(undefined1 *)(param_1 + 0x36) = 1;
  *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
  return;
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::AddTop(Aska::DynamicsPrimitive*)
// vaddr 0x23384a0 | ghidra 0x24384a0 | size 92 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE6AddTopEPS1_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE6AddTopEPS1_(long param_1,long param_2)

{
  int iVar1;
  
  if (*(long *)(param_1 + 0x38) == 0) {
    *(undefined8 *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = 0;
    iVar1 = *(int *)(param_1 + 0x48) + 1;
    *(long *)(param_1 + 0x38) = param_2;
    *(long *)(param_1 + 0x40) = param_2;
    *(int *)(param_1 + 0x48) = iVar1;
    *(undefined1 *)(param_1 + 0x36) = 1;
  }
  else {
    *(long *)(*(long *)(param_1 + 0x38) + 8) = param_2;
    *(undefined8 *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = *(undefined8 *)(param_1 + 0x38);
    *(long *)(param_1 + 0x38) = param_2;
    iVar1 = *(int *)(param_1 + 0x48);
  }
  *(int *)(param_1 + 0x48) = iVar1 + 1;
  *(undefined1 *)(param_1 + 0x36) = 1;
  return;
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::Insert(Aska::DynamicsPrimitive*, Aska::DynamicsPrimitive*)
// vaddr 0x23384fc | ghidra 0x24384fc | size 192 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE6InsertEPS1_S3_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE6InsertEPS1_S3_
          (long param_1,long param_2,long param_3)

{
  long lVar1;
  int iVar2;
  
  lVar1 = *(long *)(param_1 + 0x38);
  if (param_2 == 0) {
    if (lVar1 == 0) {
      *(undefined8 *)(param_3 + 8) = 0;
      *(undefined8 *)(param_3 + 0x10) = 0;
      iVar2 = *(int *)(param_1 + 0x48) + 1;
      *(long *)(param_1 + 0x38) = param_3;
      *(long *)(param_1 + 0x40) = param_3;
      *(int *)(param_1 + 0x48) = iVar2;
      *(undefined1 *)(param_1 + 0x36) = 1;
    }
    else {
      *(long *)(lVar1 + 8) = param_3;
      *(undefined8 *)(param_3 + 8) = 0;
      *(undefined8 *)(param_3 + 0x10) = *(undefined8 *)(param_1 + 0x38);
      *(long *)(param_1 + 0x38) = param_3;
      iVar2 = *(int *)(param_1 + 0x48);
    }
    *(int *)(param_1 + 0x48) = iVar2 + 1;
    *(undefined1 *)(param_1 + 0x36) = 1;
    return 1;
  }
  if (lVar1 != 0) {
    do {
      if (lVar1 == param_2) {
        lVar1 = *(long *)(param_2 + 0x10);
        *(long *)(param_3 + 8) = param_2;
        *(long *)(param_3 + 0x10) = lVar1;
        if (lVar1 == 0) {
          *(long *)(param_1 + 0x40) = param_3;
        }
        else {
          *(long *)(lVar1 + 8) = param_3;
        }
        *(long *)(param_2 + 0x10) = param_3;
        *(undefined1 *)(param_1 + 0x36) = 1;
        *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
        return 1;
      }
      lVar1 = *(long *)(lVar1 + 0x10);
    } while (lVar1 != 0);
    return 0;
  }
  return 0;
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::Delete(Aska::DynamicsPrimitive*)
// vaddr 0x23385bc | ghidra 0x24385bc | size 140 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE6DeleteEPS1_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE6DeleteEPS1_(long param_1,long param_2)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  
  plVar2 = (long *)(param_1 + 0x38);
  lVar3 = *plVar2;
  if (lVar3 == 0) {
    return 0;
  }
  while (lVar3 != param_2) {
    lVar3 = *(long *)(lVar3 + 0x10);
    if (lVar3 == 0) {
      return 0;
    }
  }
  lVar3 = *(long *)(param_2 + 8);
  lVar1 = *(long *)(param_2 + 0x10);
  if (lVar3 == 0) {
    if (lVar1 == 0) {
      *(undefined4 *)(param_1 + 0x48) = 0;
      *plVar2 = 0;
      *(undefined8 *)(param_1 + 0x40) = 0;
      goto code_r0x0243862c;
    }
    *(undefined8 *)(lVar1 + 8) = 0;
    *plVar2 = lVar1;
  }
  else if (lVar1 == 0) {
    *(undefined8 *)(lVar3 + 0x10) = 0;
    *(long *)(param_1 + 0x40) = lVar3;
  }
  else {
    *(long *)(lVar3 + 0x10) = lVar1;
    *(long *)(lVar1 + 8) = lVar3;
  }
  *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + -1;
code_r0x0243862c:
  *(undefined1 *)(param_1 + 0x36) = 1;
  return 1;
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::Exists(Aska::DynamicsPrimitive*)
// vaddr 0x2338648 | ghidra 0x2438648 | size 40 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE6ExistsEPS1_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE6ExistsEPS1_(long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x38);
  while( true ) {
    if (lVar1 == 0) {
      return 0;
    }
    if (lVar1 == param_2) break;
    lVar1 = *(long *)(lVar1 + 0x10);
  }
  return 1;
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::DeleteFromList(Aska::DynamicsPrimitive*)
// vaddr 0x2338670 | ghidra 0x2438670 | size 84 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE14DeleteFromListEPS1_ | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE14DeleteFromListEPS1_
               (long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  lVar1 = *(long *)(param_2 + 8);
  lVar2 = *(long *)(param_2 + 0x10);
  if (lVar1 == 0) {
    if (lVar2 == 0) {
      *(undefined4 *)(param_1 + 0x48) = 0;
      *(undefined8 *)(param_1 + 0x38) = 0;
      *(undefined8 *)(param_1 + 0x40) = 0;
      goto code_r0x024386ac;
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
code_r0x024386ac:
  *(undefined1 *)(param_1 + 0x36) = 1;
  return;
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::DeleteAll()
// vaddr 0x23386c4 | ghidra 0x24386c4 | size 12 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE9DeleteAllEv | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE9DeleteAllEv(long param_1)

{
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  return;
}

// ==== Aska::DynamicsListHandler<Aska::DynamicsPrimitive>::GetIndex(Aska::DynamicsPrimitive*)
// vaddr 0x23386d0 | ghidra 0x24386d0 | size 40 | symbol _ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE8GetIndexEPS1_ | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska19DynamicsListHandlerINS_17DynamicsPrimitiveEE8GetIndexEPS1_(long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x38);
  while( true ) {
    if (lVar1 == 0) {
      return 0xffffffff;
    }
    if (lVar1 == param_2) break;
    lVar1 = *(long *)(lVar1 + 0x10);
  }
  return 0;
}

// ==== Aska::DynamicsCommandNotify::SetNotify(Aska::INotify*, Aska::DynamicsCommandNotify::_Arguments*, Aska::INotify*, unsigned int*)
// vaddr 0x2339144 | ghidra 0x2439144 | size 68 | symbol _ZN4Aska21DynamicsCommandNotify9SetNotifyEPNS_7INotifyEPNS0_10_ArgumentsES2_Pj | lib libSOA-3.7.0.so | 2026-10-08
undefined8
_ZN4Aska21DynamicsCommandNotify9SetNotifyEPNS_7INotifyEPNS0_10_ArgumentsES2_Pj
          (undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 uVar1;
  
  if (param_2 != 0) {
    uVar1 = (*(code *)
              PTR__ZN4Aska23SimpleMessageDispatcher11PostMessageEtPNS_7INotifyEPvS3_Pja_02c91b30)
                      (*(undefined8 *)PTR__ZN4Aska6Global20m_pMessageDispatcherE_02cb77c8,0,
                       PTR__ZN4Aska21DynamicsCommandNotify23m_DynamicsCommandNotifyE_02cb9390,
                       param_2,param_1,param_4,0);
    return uVar1;
  }
  return 0;
}

// ==== Aska::DynamicsCommandNotify::Handler(unsigned long)
// vaddr 0x2339188 | ghidra 0x2439188 | size 184 | symbol _ZN4Aska21DynamicsCommandNotify7HandlerEm | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21DynamicsCommandNotify7HandlerEm(undefined8 param_1,long param_2)

{
  long *plVar1;
  uint uVar2;
  undefined8 *puVar3;
  long *plVar4;
  long *plVar5;
  
  plVar5 = *(long **)(param_2 + 0x30);
  plVar1 = *(long **)(param_2 + 0x38);
  if (*(ushort *)(param_2 + 2) == 0) {
    puVar3 = (undefined8 *)*plVar5;
    if (puVar3 != (undefined8 *)0x0) {
      (**(code **)*puVar3)(puVar3,(int)plVar5[1]);
    }
    if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0243922c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)*plVar1)(plVar1,0);
      return;
    }
  }
  else {
    uVar2 = *(ushort *)(param_2 + 2) - 4;
    if (uVar2 < 0x40) {
      for (; plVar5 < plVar1; plVar5 = plVar5 + 1) {
        plVar4 = (long *)*plVar5;
        if (plVar4 != (long *)0x0) {
          (**(code **)(*plVar4 + 0x20))(plVar4,uVar2);
          puVar3 = (undefined8 *)plVar4[3];
          if (puVar3 != (undefined8 *)0x0) {
            (**(code **)*puVar3)(puVar3,plVar4);
          }
        }
      }
    }
  }
  return;
}

// ==== Aska::DynamicsCommandNotify::~DynamicsCommandNotify()
// vaddr 0x2339240 | ghidra 0x2439240 | size 4 | symbol _ZN4Aska21DynamicsCommandNotifyD0Ev | lib libSOA-3.7.0.so | 2026-10-08
void _ZN4Aska21DynamicsCommandNotifyD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}
