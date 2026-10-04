// port/decomp/containers/legacy_tree.c: Ghidra decompiles for the containers subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 05:14 UTC: tools/decomp.sh '--into' 'containers/legacy_tree' 'Aska::TBinaryTree<Aska::AddressNode>::' 'Aska::THash<Aska::AddressNode>::' 'Aska::TAddressManager<Aska::AddressNode>::' 'Aska::TPoolLegacy<Aska::AddressNode, false>::' 'Aska::TBitArray<unsigned int, false>::' 'Aska::AddressNode::'

// ==== Aska::AddressNode::Compare(void const*)
// vaddr 0x1f29ab0 | ghidra 0x2029ab0 | size 48 | symbol _ZN4Aska11AddressNode7CompareEPKv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska11AddressNode7CompareEPKv(long *param_1,ulong *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  ulong *puVar3;
  ulong uVar4;
  
  uVar4 = *param_2;
  puVar3 = (ulong *)(**(code **)(*param_1 + 0x30))();
  uVar1 = 0xffffffff;
  if (*puVar3 < uVar4) {
    uVar1 = 1;
  }
  uVar2 = 0;
  if (uVar4 != *puVar3) {
    uVar2 = uVar1;
  }
  return uVar2;
}

// ==== Aska::TAddressManager<Aska::AddressNode>::Register(void const*)
// vaddr 0x1f2d9d0 | ghidra 0x202d9d0 | size 184 | symbol _ZN4Aska15TAddressManagerINS_11AddressNodeEE8RegisterEPKv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska15TAddressManagerINS_11AddressNodeEE8RegisterEPKv(long *param_1,undefined8 param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  ulong uVar6;
  long *plVar7;
  
  uVar1 = (**(code **)(*param_1 + 0x60))();
  uVar6 = (ulong)uVar1;
  if (*(uint *)(param_1 + 0xb) <= uVar1) {
    uVar6 = 0;
  }
  plVar7 = (long *)(param_1[10] + uVar6 * 8);
  param_1[0xc] = (long)plVar7;
  plVar3 = (long *)*plVar7;
  while (plVar3 != (long *)0x0) {
    while (iVar2 = (**(code **)(*plVar3 + 0x20))(plVar3,param_2), iVar2 < 0) {
      plVar7 = (long *)(*plVar7 + 0x18);
      plVar3 = (long *)*plVar7;
      if (plVar3 == (long *)0x0) goto code_r0x0202da50;
    }
    if (iVar2 == 0) goto code_r0x0202da6c;
    plVar7 = (long *)(*plVar7 + 0x20);
    plVar3 = (long *)*plVar7;
  }
code_r0x0202da50:
  lVar4 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar7 = lVar4;
  lVar5 = 0;
  if (lVar4 != 0) {
code_r0x0202da6c:
    if (plVar7 == (long *)0x0) {
      lVar5 = 0;
    }
    else {
      lVar5 = *plVar7;
    }
  }
  return lVar5;
}

// ==== Aska::AddressNode::~AddressNode()
// vaddr 0x1f2df3c | ghidra 0x202df3c | size 4 | symbol _ZN4Aska11AddressNodeD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11AddressNodeD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::AddressNode::SetKey(void const*)
// vaddr 0x1f2df40 | ghidra 0x202df40 | size 28 | symbol _ZN4Aska11AddressNode6SetKeyEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11AddressNode6SetKeyEPKv(long param_1,undefined8 *param_2)

{
  if (param_2 != (undefined8 *)0x0) {
    *(undefined8 *)(param_1 + 0x28) = *param_2;
    return;
  }
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::FreeTable()
// vaddr 0x1f310c4 | ghidra 0x20310c4 | size 536 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEE9FreeTableEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_11AddressNodeEE9FreeTableEv(long *param_1)

{
  int iVar1;
  long lVar2;
  long *plVar3;
  long *plVar4;
  ulong uVar5;
  long *plVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  long *plVar10;
  
  iVar8 = *(int *)((long)param_1 + 0x8c);
  iVar1 = (int)param_1[0xb];
  plVar4 = (long *)param_1[10];
  if (iVar8 == *(int *)((long)param_1 + 0x3c)) {
    iVar9 = iVar8 + -1;
    if (0 < iVar8) {
      lVar2 = 0;
      uVar7 = 0;
      if (*(uint *)((long)param_1 + 0x2c) != 0) goto code_r0x0203112c;
      do {
        do {
          uVar7 = uVar7 + 1;
          lVar2 = lVar2 + 0x30;
        } while (*(uint *)((long)param_1 + 0x2c) <= uVar7);
code_r0x0203112c:
      } while ((*(uint *)(param_1[4] + (ulong)(uVar7 >> 5) * 4) & 1 << (ulong)(uVar7 & 0x1f)) == 0);
      Hint_Prefetch((long *)(param_1[8] + lVar2),0,2,0);
      plVar6 = (long *)(param_1[8] + lVar2);
      do {
        if (iVar9 < 1) {
          plVar10 = (long *)0x0;
        }
        else {
          do {
            do {
              uVar7 = uVar7 + 1;
            } while (*(uint *)((long)param_1 + 0x2c) <= uVar7);
          } while ((*(uint *)(param_1[4] + (ulong)(uVar7 >> 5) * 4) & 1 << (ulong)(uVar7 & 0x1f)) ==
                   0);
          plVar10 = (long *)(param_1[8] + (ulong)uVar7 * 0x30);
          Hint_Prefetch(plVar10,0,2,0);
          iVar9 = iVar9 + -1;
        }
        (**(code **)(*plVar6 + 0x18))(plVar6);
        plVar3 = (long *)param_1[8];
        if (((plVar3 != (long *)0x0) && (plVar3 <= plVar6)) &&
           (plVar6 < plVar3 + (ulong)*(uint *)((long)param_1 + 0x2c) * 6)) {
          uVar5 = ((long)plVar6 - (long)plVar3 >> 4) * -0x5555555555555555;
          (**(code **)plVar3[(uVar5 & 0xffffffff) * 6])();
          lVar2 = (uVar5 >> 5 & 0x7ffffff) * 4;
          *(uint *)(param_1[4] + lVar2) =
               *(uint *)(param_1[4] + lVar2) & (1 << (ulong)((uint)uVar5 & 0x1f) ^ 0xffffffffU);
          *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
        }
        *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
        plVar6 = plVar10;
      } while (plVar10 != (long *)0x0);
    }
  }
  else if (iVar1 != 0) {
    plVar6 = plVar4 + (iVar1 - 1);
    iVar8 = iVar1;
    do {
      (**(code **)(*param_1 + 0x18))(param_1,plVar6);
      iVar8 = iVar8 + -1;
      plVar6 = plVar6 + -1;
    } while (iVar8 != 0);
  }
  param_1[0xc] = 0;
  *(undefined4 *)(param_1 + 0xb) = 0;
  param_1[10] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  *(undefined1 *)(param_1 + 0x11) = 0;
  param_1[0xe] = 0;
  if (((plVar4 != (long *)0x0) && (iVar1 != 0)) && (plVar4 != param_1 + 0xd)) {
    (*(code *)PTR__ZdaPv_02cb5db8)(plVar4);
    return;
  }
  return;
}

// ==== Aska::THash<Aska::AddressNode>::~THash()
// vaddr 0x1f312dc | ghidra 0x20312dc | size 40 | symbol _ZN4Aska5THashINS_11AddressNodeEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashINS_11AddressNodeEED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska5THashINS_11AddressNodeEEE_02cc0728 + 0x10);
  Aska::TBinaryTree<Aska::AddressNode>::FreeTable()();
  (*(code *)PTR__ZN4Aska11TBinaryTreeINS_11AddressNodeEED2Ev_02c9c878)(param_1);
  return;
}

// ==== Aska::THash<Aska::AddressNode>::~THash()
// vaddr 0x1f31304 | ghidra 0x2031304 | size 48 | symbol _ZN4Aska5THashINS_11AddressNodeEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashINS_11AddressNodeEED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska5THashINS_11AddressNodeEEE_02cc0728 + 0x10);
  Aska::TBinaryTree<Aska::AddressNode>::FreeTable()();
  Aska::TBinaryTree<Aska::AddressNode>::~TBinaryTree()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::AllocNode(void const*)
// vaddr 0x1f31334 | ghidra 0x2031334 | size 368 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEE9AllocNodeEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_11AddressNodeEE9AllocNodeEPKv(long param_1,undefined8 param_2)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  if (*(uint *)(param_1 + 0x3c) < *(uint *)(param_1 + 0x2c)) {
    lVar5 = *(long *)(param_1 + 0x20);
    uVar3 = *(uint *)(param_1 + 0x38);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0x2c) <= uVar6) {
        uVar6 = 0;
      }
      uVar2 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar2 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x30;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0x30);
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0x38) = uVar6 + 1;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) + 1;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar2;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x30);
    puVar1 = PTR__ZTVN4Aska11AddressNodeE_02cb6f68 + 0x10;
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)puVar1;
    plVar4 = (long *)(*(long *)(param_1 + 0x40) + (ulong)uVar6 * 0x30);
    if (plVar4 == (long *)0x0) goto code_r0x02031400;
  }
  else {
code_r0x02031400:
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    puVar1 = PTR__ZTVN4Aska11AddressNodeE_02cb6f68;
    if (plVar4 == (long *)0x0) {
      return (long *)0x0;
    }
    plVar4[4] = 0;
    plVar4[3] = 0;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar1 + 0x10);
  }
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 1;
  if (*(long *)(param_1 + 0x70) == 0) {
    *(long **)(param_1 + 0x70) = plVar4;
    lVar5 = *(long *)(param_1 + 0x78);
    if (lVar5 == 0) {
      lVar7 = 0;
      goto code_r0x02031458;
    }
  }
  else {
    lVar5 = *(long *)(param_1 + 0x78);
    lVar7 = 0;
    if (lVar5 == 0) goto code_r0x02031458;
  }
  *(long **)(lVar5 + 0x10) = plVar4;
  lVar7 = *(long *)(param_1 + 0x78);
code_r0x02031458:
  plVar4[1] = lVar7;
  plVar4[2] = 0;
  *(long **)(param_1 + 0x78) = plVar4;
  (**(code **)(*plVar4 + 0x28))(plVar4,param_2);
  (**(code **)(*plVar4 + 0x10))(plVar4);
  return plVar4;
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::FreeNode(Aska::AddressNode**)
// vaddr 0x1f314a4 | ghidra 0x20314a4 | size 400 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEE8FreeNodeEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_11AddressNodeEE8FreeNodeEPPS1_(long *param_1,ulong *param_2)

{
  long *plVar1;
  ulong uVar2;
  long *plVar3;
  long lVar4;
  
  uVar2 = *param_2;
  if (uVar2 != 0) {
    if (param_1[0xe] == uVar2) {
      param_1[0xe] = *(long *)(uVar2 + 0x10);
      uVar2 = *param_2;
    }
    if (param_1[0xf] == uVar2) {
      param_1[0xf] = *(long *)(uVar2 + 8);
      uVar2 = *param_2;
    }
    if (param_1[0x10] == uVar2) {
      param_1[0x10] = *(long *)(uVar2 + 8);
      uVar2 = *param_2;
    }
    lVar4 = *(long *)(uVar2 + 0x10);
    if (*(long *)(uVar2 + 8) != 0) {
      *(long *)(*(long *)(uVar2 + 8) + 0x10) = lVar4;
    }
    if (lVar4 != 0) {
      *(undefined8 *)(lVar4 + 8) = *(undefined8 *)(*param_2 + 8);
    }
    *(undefined8 *)(*param_2 + 0x10) = 0;
    *(undefined8 *)(*param_2 + 8) = 0;
    plVar1 = (long *)*param_2;
    if (plVar1[4] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar1 = (long *)*param_2;
    }
    if (plVar1[3] != 0) {
      (**(code **)(*param_1 + 0x18))(param_1);
      plVar1 = (long *)*param_2;
    }
    (**(code **)(*plVar1 + 0x18))();
    *(int *)((long)param_1 + 0x8c) = *(int *)((long)param_1 + 0x8c) + -1;
    plVar3 = (long *)param_1[8];
    plVar1 = (long *)*param_2;
    if (((plVar3 == (long *)0x0) || (plVar1 < plVar3)) ||
       (plVar3 + (ulong)*(uint *)((long)param_1 + 0x2c) * 6 <= plVar1)) {
      if (plVar1 != (long *)0x0) {
        (**(code **)(*plVar1 + 8))();
      }
    }
    else {
      uVar2 = ((long)plVar1 - (long)plVar3 >> 4) * -0x5555555555555555;
      (**(code **)plVar3[(uVar2 & 0xffffffff) * 6])();
      lVar4 = (uVar2 >> 5 & 0x7ffffff) * 4;
      *(uint *)(param_1[4] + lVar4) =
           *(uint *)(param_1[4] + lVar4) & (1 << (ulong)((uint)uVar2 & 0x1f) ^ 0xffffffffU);
      *(int *)((long)param_1 + 0x3c) = *(int *)((long)param_1 + 0x3c) + -1;
    }
    *param_2 = 0;
  }
  return;
}

// ==== Aska::THash<Aska::AddressNode>::RegistEx(void const*)
// vaddr 0x1f31634 | ghidra 0x2031634 | size 176 | symbol _ZN4Aska5THashINS_11AddressNodeEE8RegistExEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska5THashINS_11AddressNodeEE8RegistExEPKv(long *param_1,undefined8 param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  
  uVar1 = (**(code **)(*param_1 + 0x60))();
  uVar5 = (ulong)uVar1;
  if (*(uint *)(param_1 + 0xb) <= uVar1) {
    uVar5 = 0;
  }
  plVar6 = (long *)(param_1[10] + uVar5 * 8);
  param_1[0xc] = (long)plVar6;
  plVar3 = (long *)*plVar6;
  while (plVar3 != (long *)0x0) {
    while (iVar2 = (**(code **)(*plVar3 + 0x20))(plVar3,param_2), iVar2 < 0) {
      plVar6 = (long *)(*plVar6 + 0x18);
      plVar3 = (long *)*plVar6;
      if (plVar3 == (long *)0x0) goto code_r0x020316b4;
    }
    if (iVar2 == 0) {
      return plVar6;
    }
    plVar6 = (long *)(*plVar6 + 0x20);
    plVar3 = (long *)*plVar6;
  }
code_r0x020316b4:
  lVar4 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar6 = lVar4;
  if (lVar4 == 0) {
    plVar6 = (long *)0x0;
  }
  return plVar6;
}

// ==== Aska::THash<Aska::AddressNode>::Regist(void const*)
// vaddr 0x1f316e4 | ghidra 0x20316e4 | size 64 | symbol _ZN4Aska5THashINS_11AddressNodeEE6RegistEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashINS_11AddressNodeEE6RegistEPKv(long *param_1,undefined8 param_2)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar1;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x68);
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1);
                    /* WARNING: Could not recover jumptable at 0x02031720. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,uVar1);
  return;
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::Register(void const*)
// vaddr 0x1f31724 | ghidra 0x2031724 | size 12 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEE8RegisterEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_11AddressNodeEE8RegisterEPKv(long *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0203172c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x28))();
  return;
}

// ==== Aska::THash<Aska::AddressNode>::Remove(void const*)
// vaddr 0x1f31730 | ghidra 0x2031730 | size 68 | symbol _ZN4Aska5THashINS_11AddressNodeEE6RemoveEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashINS_11AddressNodeEE6RemoveEPKv(long *param_1,undefined8 param_2)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x70);
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1);
                    /* WARNING: Could not recover jumptable at 0x02031770. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,uVar1);
  return;
}

// ==== Aska::THash<Aska::AddressNode>::Remove(Aska::AddressNode**)
// vaddr 0x1f31774 | ghidra 0x2031774 | size 140 | symbol _ZN4Aska5THashINS_11AddressNodeEE6RemoveEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashINS_11AddressNodeEE6RemoveEPPS1_(long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  long lStack_8;
  
  lStack_8 = *param_2;
  if (lStack_8 != 0) {
    plVar2 = (long *)(lStack_8 + 0x20);
    plVar3 = (long *)(lStack_8 + 0x18);
    if (*plVar2 == 0) {
      *param_2 = *plVar3;
      plVar2 = plVar3;
    }
    else {
      plVar1 = plVar3;
      if (*plVar3 == 0) {
        *param_2 = *plVar2;
      }
      else {
        do {
          plVar5 = plVar1;
          lVar4 = *plVar5;
          plVar1 = (long *)(lVar4 + 0x20);
        } while (*(long *)(lVar4 + 0x20) != 0);
        *plVar5 = *(long *)(lVar4 + 0x18);
        *(long *)(lVar4 + 0x18) = *plVar3;
        *(long *)(lVar4 + 0x20) = *plVar2;
        *param_2 = lVar4;
        *plVar3 = 0;
      }
    }
    *plVar2 = 0;
    (**(code **)(*param_1 + 0x18))(param_1,&lStack_8);
  }
  return;
}

// ==== Aska::THash<Aska::AddressNode>::IsRegisted(void const*)
// vaddr 0x1f31800 | ghidra 0x2031800 | size 68 | symbol _ZN4Aska5THashINS_11AddressNodeEE10IsRegistedEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashINS_11AddressNodeEE10IsRegistedEPKv(long *param_1,undefined8 param_2)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x78);
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1);
                    /* WARNING: Could not recover jumptable at 0x02031840. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,uVar1);
  return;
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::IsRegistered(void const*)
// vaddr 0x1f31844 | ghidra 0x2031844 | size 112 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEE12IsRegisteredEPKv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska11TBinaryTreeINS_11AddressNodeEE12IsRegisteredEPKv(long param_1,undefined8 param_2)

{
  int iVar1;
  long *plVar2;
  long *plVar3;
  
  plVar3 = *(long **)(param_1 + 0x60);
  plVar2 = (long *)*plVar3;
  do {
    if (plVar2 == (long *)0x0) {
      return false;
    }
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return *plVar3 != 0;
      }
      plVar3 = (long *)(*plVar3 + 0x20);
      plVar2 = (long *)*plVar3;
      if (plVar2 == (long *)0x0) {
        return false;
      }
    }
    plVar3 = (long *)(*plVar3 + 0x18);
    plVar2 = (long *)*plVar3;
  } while( true );
}

// ==== Aska::THash<Aska::AddressNode>::Search(void const*)
// vaddr 0x1f318b4 | ghidra 0x20318b4 | size 68 | symbol _ZN4Aska5THashINS_11AddressNodeEE6SearchEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashINS_11AddressNodeEE6SearchEPKv(long *param_1,undefined8 param_2)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*param_1 + 0x80);
  uVar1 = (**(code **)(*param_1 + 0x60))(param_1);
                    /* WARNING: Could not recover jumptable at 0x020318f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,param_2,uVar1);
  return;
}

// ==== Aska::THash<Aska::AddressNode>::CalcHashValue(void const*) const
// vaddr 0x1f318f8 | ghidra 0x20318f8 | size 84 | symbol _ZNK4Aska5THashINS_11AddressNodeEE13CalcHashValueEPKv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK4Aska5THashINS_11AddressNodeEE13CalcHashValueEPKv(long param_1,byte *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  
  uVar1 = *(uint *)(param_1 + 0x58);
  uVar2 = 0x811c9dc5;
  lVar4 = strlen(param_2);
  for (; lVar4 != 0; lVar4 = lVar4 + -1) {
    uVar2 = uVar2 * 0x1000193 ^ (uint)*param_2;
    param_2 = param_2 + 1;
  }
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  return uVar2 - uVar3 * uVar1;
}

// ==== Aska::THash<Aska::AddressNode>::Regist(void const*, unsigned int)
// vaddr 0x1f3194c | ghidra 0x203194c | size 168 | symbol _ZN4Aska5THashINS_11AddressNodeEE6RegistEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5THashINS_11AddressNodeEE6RegistEPKvj(long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  
  uVar5 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar5 = 0;
  }
  plVar6 = (long *)(param_1[10] + uVar5 * 8);
  param_1[0xc] = (long)plVar6;
  plVar2 = (long *)*plVar6;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x020319d8;
      plVar6 = (long *)(*plVar6 + 0x20);
      plVar2 = (long *)*plVar6;
      if (plVar2 == (long *)0x0) goto code_r0x020319bc;
    }
    plVar6 = (long *)(*plVar6 + 0x18);
    plVar2 = (long *)*plVar6;
  }
code_r0x020319bc:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar6 = lVar3;
  lVar4 = 0;
  if (lVar3 != 0) {
code_r0x020319d8:
    if (plVar6 == (long *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar6;
    }
  }
  return lVar4;
}

// ==== Aska::THash<Aska::AddressNode>::Remove(void const*, unsigned int)
// vaddr 0x1f319f4 | ghidra 0x20319f4 | size 140 | symbol _ZN4Aska5THashINS_11AddressNodeEE6RemoveEPKvj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5THashINS_11AddressNodeEE6RemoveEPKvj(long *param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0xb) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(param_1[10] + uVar3 * 8);
  param_1[0xc] = (long)plVar4;
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x02031a64;
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) goto code_r0x02031a64;
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  }
code_r0x02031a64:
                    /* WARNING: Could not recover jumptable at 0x02031a7c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x40))(param_1,plVar4);
  return;
}

// ==== Aska::THash<Aska::AddressNode>::IsRegisted(void const*, unsigned int)
// vaddr 0x1f31a80 | ghidra 0x2031a80 | size 132 | symbol _ZN4Aska5THashINS_11AddressNodeEE10IsRegistedEPKvj | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska5THashINS_11AddressNodeEE10IsRegistedEPKvj
               (long param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0x58) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(*(long *)(param_1 + 0x50) + uVar3 * 8);
  plVar2 = (long *)*plVar4;
  do {
    if (plVar2 == (long *)0x0) {
      return false;
    }
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return *plVar4 != 0;
      }
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) {
        return false;
      }
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  } while( true );
}

// ==== Aska::THash<Aska::AddressNode>::Search(void const*, unsigned int)
// vaddr 0x1f31b04 | ghidra 0x2031b04 | size 124 | symbol _ZN4Aska5THashINS_11AddressNodeEE6SearchEPKvj | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska5THashINS_11AddressNodeEE6SearchEPKvj(long param_1,undefined8 param_2,uint param_3)

{
  int iVar1;
  long *plVar2;
  ulong uVar3;
  long *plVar4;
  
  uVar3 = (ulong)param_3;
  if (*(uint *)(param_1 + 0x58) <= param_3) {
    uVar3 = 0;
  }
  plVar4 = (long *)(*(long *)(param_1 + 0x50) + uVar3 * 8);
  plVar2 = (long *)*plVar4;
  do {
    if (plVar2 == (long *)0x0) {
      return 0;
    }
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return *plVar4;
      }
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) {
        return 0;
      }
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  } while( true );
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::~TBinaryTree()
// vaddr 0x1f31b80 | ghidra 0x2031b80 | size 240 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_11AddressNodeEED2Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  *param_1 = (long)(PTR__ZTVN4Aska11TBinaryTreeINS_11AddressNodeEEE_02cb9e00 + 0x10);
  Aska::TBinaryTree<Aska::AddressNode>::FreeTable()();
  plVar2 = param_1 + 4;
  *param_1 = (long)(PTR__ZTVN4Aska11TPoolLegacyINS_11AddressNodeELb0EEE_02cb9ff8 + 0x10);
  if ((*plVar2 != 0) && ((char)param_1[6] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 6) = 0;
  }
  *plVar2 = 0;
  param_1[5] = 0;
  param_1[7] = 0;
  if (param_1[8] == 0) {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
  }
  else if ((char)param_1[9] == '\0') {
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
  }
  else {
    operator delete[](void*)();
    param_1[2] = (long)(PTR__ZTVN4Aska9TBitArrayIjLb0EEE_02cba038 + 0x10);
    param_1[8] = 0;
    if ((param_1[4] != 0) && ((char)param_1[6] != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 6) = 0;
    }
  }
  *plVar2 = 0;
  param_1[5] = 0;
  puVar1 = PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10;
  param_1[2] = (long)puVar1;
  *param_1 = (long)puVar1;
  return;
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::~TBinaryTree()
// vaddr 0x1f31c70 | ghidra 0x2031c70 | size 24 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_11AddressNodeEED0Ev(undefined8 param_1)

{
  Aska::TBinaryTree<Aska::AddressNode>::~TBinaryTree()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::RegistEx(void const*)
// vaddr 0x1f31c88 | ghidra 0x2031c88 | size 136 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEE8RegistExEPKv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska11TBinaryTreeINS_11AddressNodeEE8RegistExEPKv(long *param_1,undefined8 param_2)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long *plVar4;
  
  plVar4 = (long *)param_1[0xc];
  plVar2 = (long *)*plVar4;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return plVar4;
      }
      plVar4 = (long *)(*plVar4 + 0x20);
      plVar2 = (long *)*plVar4;
      if (plVar2 == (long *)0x0) goto code_r0x02031ce0;
    }
    plVar4 = (long *)(*plVar4 + 0x18);
    plVar2 = (long *)*plVar4;
  }
code_r0x02031ce0:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar4 = lVar3;
  if (lVar3 == 0) {
    plVar4 = (long *)0x0;
  }
  return plVar4;
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::Regist(void const*)
// vaddr 0x1f31d10 | ghidra 0x2031d10 | size 144 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEE6RegistEPKv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska11TBinaryTreeINS_11AddressNodeEE6RegistEPKv(long *param_1,undefined8 param_2)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  long *plVar5;
  
  plVar5 = (long *)param_1[0xc];
  plVar2 = (long *)*plVar5;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x02031d84;
      plVar5 = (long *)(*plVar5 + 0x20);
      plVar2 = (long *)*plVar5;
      if (plVar2 == (long *)0x0) goto code_r0x02031d68;
    }
    plVar5 = (long *)(*plVar5 + 0x18);
    plVar2 = (long *)*plVar5;
  }
code_r0x02031d68:
  lVar3 = (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *plVar5 = lVar3;
  lVar4 = 0;
  if (lVar3 != 0) {
code_r0x02031d84:
    if (plVar5 == (long *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar5;
    }
  }
  return lVar4;
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::Remove(void const*)
// vaddr 0x1f31da0 | ghidra 0x2031da0 | size 116 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEE6RemoveEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_11AddressNodeEE6RemoveEPKv(long *param_1,undefined8 param_2)

{
  int iVar1;
  long *plVar2;
  long *plVar3;
  
  plVar3 = (long *)param_1[0xc];
  plVar2 = (long *)*plVar3;
  while (plVar2 != (long *)0x0) {
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) goto code_r0x02031df8;
      plVar3 = (long *)(*plVar3 + 0x20);
      plVar2 = (long *)*plVar3;
      if (plVar2 == (long *)0x0) goto code_r0x02031df8;
    }
    plVar3 = (long *)(*plVar3 + 0x18);
    plVar2 = (long *)*plVar3;
  }
code_r0x02031df8:
                    /* WARNING: Could not recover jumptable at 0x02031e10. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0x40))(param_1,plVar3);
  return;
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::Remove(Aska::AddressNode**)
// vaddr 0x1f31e14 | ghidra 0x2031e14 | size 144 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEE6RemoveEPPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska11TBinaryTreeINS_11AddressNodeEE6RemoveEPPS1_(long *param_1,long *param_2)

{
  long *plVar1;
  long *plVar2;
  undefined8 *puVar3;
  long lVar4;
  long lStack_8;
  
  lStack_8 = *param_2;
  if (lStack_8 != 0) {
    lVar4 = *(long *)(lStack_8 + 0x18);
    if (*(long *)(lStack_8 + 0x20) == 0) {
      *param_2 = lVar4;
      puVar3 = (undefined8 *)(lStack_8 + 0x18);
    }
    else {
      plVar1 = (long *)(lStack_8 + 0x18);
      if (lVar4 == 0) {
        *param_2 = *(long *)(lStack_8 + 0x20);
        puVar3 = (undefined8 *)(lStack_8 + 0x20);
      }
      else {
        do {
          plVar2 = plVar1;
          lVar4 = *plVar2;
          plVar1 = (long *)(lVar4 + 0x20);
        } while (*(long *)(lVar4 + 0x20) != 0);
        *plVar2 = *(long *)(lVar4 + 0x18);
        *(undefined8 *)(lVar4 + 0x18) = *(undefined8 *)(lStack_8 + 0x18);
        puVar3 = (undefined8 *)(lStack_8 + 0x20);
        *(undefined8 *)(lVar4 + 0x20) = *puVar3;
        *param_2 = lVar4;
        *(undefined8 *)(lStack_8 + 0x18) = 0;
      }
    }
    *puVar3 = 0;
    (**(code **)(*param_1 + 0x18))(param_1,&lStack_8);
  }
  return;
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::IsRegisted(void const*)
// vaddr 0x1f31ea4 | ghidra 0x2031ea4 | size 112 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEE10IsRegistedEPKv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska11TBinaryTreeINS_11AddressNodeEE10IsRegistedEPKv(long param_1,undefined8 param_2)

{
  int iVar1;
  long *plVar2;
  long *plVar3;
  
  plVar3 = *(long **)(param_1 + 0x60);
  plVar2 = (long *)*plVar3;
  do {
    if (plVar2 == (long *)0x0) {
      return false;
    }
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return *plVar3 != 0;
      }
      plVar3 = (long *)(*plVar3 + 0x20);
      plVar2 = (long *)*plVar3;
      if (plVar2 == (long *)0x0) {
        return false;
      }
    }
    plVar3 = (long *)(*plVar3 + 0x18);
    plVar2 = (long *)*plVar3;
  } while( true );
}

// ==== Aska::TBinaryTree<Aska::AddressNode>::Search(void const*)
// vaddr 0x1f31f14 | ghidra 0x2031f14 | size 104 | symbol _ZN4Aska11TBinaryTreeINS_11AddressNodeEE6SearchEPKv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska11TBinaryTreeINS_11AddressNodeEE6SearchEPKv(long param_1,undefined8 param_2)

{
  int iVar1;
  long *plVar2;
  long *plVar3;
  
  plVar3 = *(long **)(param_1 + 0x60);
  plVar2 = (long *)*plVar3;
  do {
    if (plVar2 == (long *)0x0) {
      return 0;
    }
    while (iVar1 = (**(code **)(*plVar2 + 0x20))(plVar2,param_2), -1 < iVar1) {
      if (iVar1 == 0) {
        return *plVar3;
      }
      plVar3 = (long *)(*plVar3 + 0x20);
      plVar2 = (long *)*plVar3;
      if (plVar2 == (long *)0x0) {
        return 0;
      }
    }
    plVar3 = (long *)(*plVar3 + 0x18);
    plVar2 = (long *)*plVar3;
  } while( true );
}

// ==== Aska::TAddressManager<Aska::AddressNode>::~TAddressManager()
// vaddr 0x1f3677c | ghidra 0x203677c | size 48 | symbol _ZN4Aska15TAddressManagerINS_11AddressNodeEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TAddressManagerINS_11AddressNodeEED0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska5THashINS_11AddressNodeEEE_02cc0728 + 0x10);
  Aska::TBinaryTree<Aska::AddressNode>::FreeTable()();
  Aska::TBinaryTree<Aska::AddressNode>::~TBinaryTree()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::TAddressManager<Aska::AddressNode>::IsRegistered(void const*)
// vaddr 0x1f367ac | ghidra 0x20367ac | size 152 | symbol _ZN4Aska15TAddressManagerINS_11AddressNodeEE12IsRegisteredEPKv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska15TAddressManagerINS_11AddressNodeEE12IsRegisteredEPKv
               (long *param_1,undefined8 param_2)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  ulong uVar4;
  long *plVar5;
  
  uVar1 = (**(code **)(*param_1 + 0x60))();
  uVar4 = (ulong)uVar1;
  if (*(uint *)(param_1 + 0xb) <= uVar1) {
    uVar4 = 0;
  }
  plVar5 = (long *)(param_1[10] + uVar4 * 8);
  plVar3 = (long *)*plVar5;
  do {
    if (plVar3 == (long *)0x0) {
      return false;
    }
    while (iVar2 = (**(code **)(*plVar3 + 0x20))(plVar3,param_2), -1 < iVar2) {
      if (iVar2 == 0) {
        return *plVar5 != 0;
      }
      plVar5 = (long *)(*plVar5 + 0x20);
      plVar3 = (long *)*plVar5;
      if (plVar3 == (long *)0x0) {
        return false;
      }
    }
    plVar5 = (long *)(*plVar5 + 0x18);
    plVar3 = (long *)*plVar5;
  } while( true );
}

// ==== Aska::TAddressManager<Aska::AddressNode>::CalcHashValue(void const*) const
// vaddr 0x1f36844 | ghidra 0x2036844 | size 132 | symbol _ZNK4Aska15TAddressManagerINS_11AddressNodeEE13CalcHashValueEPKv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK4Aska15TAddressManagerINS_11AddressNodeEE13CalcHashValueEPKv(long param_1,byte *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = *(uint *)(param_1 + 0x58);
  uVar2 = 0;
  if (uVar1 != 0) {
    uVar2 = *param_2 / uVar1;
  }
  uVar2 = (uint)param_2[1] + ((uint)*param_2 - uVar2 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[2] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[3] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[4] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[5] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[6] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  uVar2 = (uint)param_2[7] + (uVar2 - uVar3 * uVar1) * 8;
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar2 / uVar1;
  }
  return uVar2 - uVar3 * uVar1;
}


// FAILED to create function at 02bb0b00 Aska::AddressNode::vtable
// FAILED to create function at 02bb0b50 Aska::AddressNode::typeinfo
// FAILED to create function at 02bb10f8 Aska::THash<Aska::AddressNode>::vtable
// FAILED to create function at 02bb11b0 Aska::TBinaryTree<Aska::AddressNode>::typeinfo
// FAILED to create function at 02bb11d0 Aska::THash<Aska::AddressNode>::typeinfo
// FAILED to create function at 02bb11e8 Aska::TBinaryTree<Aska::AddressNode>::vtable
// FAILED to create function at 02bb1a98 Aska::TAddressManager<Aska::AddressNode>::vtable
// FAILED to create function at 02bb1b30 Aska::TAddressManager<Aska::AddressNode>::typeinfo
