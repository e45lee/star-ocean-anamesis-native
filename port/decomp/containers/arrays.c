// port/decomp/containers/arrays.c: Ghidra decompiles for the containers subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileAt.java, tools/resolve_decomp.py
// run      2026-10-04 05:12 UTC: tools/decomp_at.sh '--into' 'containers/arrays' '12ab274' '12ab4c4' '139a42c' '139a570' '15a9ca0' '15ac47c' '15ac518' '15ac5b4' '15b0c30' '17bf598' '17bf744' '17bfd7c' '17c00dc' '17c0324' '17c09c4' '17c0b70' '17dde6c' '17de048' '17de100' '17e540c' '18dd284' '18e743c' '18e944c' '18f5acc' '18f6c88' '1f13114' '1f13128' '1f13130' '1f131b4' '1f131d0' '1f131d8' '1f5e220' '1fc69d8' '2013f9c' '20213e4' '2021408' '2037d18' '20388d8' '204f618' '2071280' '2071d70' '21dd8fc' '21e7324' '21e8264' '2200320' '2200a50' '2201e70' '2230370' '22303d8' '22327ac' '2260494' '22606a0' '226d440' '227f980' '227fc78' '2280d80' '22815fc' '22ebecc' '22ec0fc' '2322e68' '2322eec' '2322fc8' '2323540' '232378c' '233b348' '24669b4' '2466d58' '2468644' '2468e78' '270e880'

// ==== Aska::TArray<Framework::TStaticString<256ul>, false>::Resize(long, bool)
// vaddr 0x11ab274 | ghidra 0x12ab274 | size 532 | symbol _ZN4Aska6TArrayIN9Framework13TStaticStringILm256EEELb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIN9Framework13TStaticStringILm256EEELb0EE6ResizeElb
               (long param_1,long param_2,ulong param_3)

{
  undefined1 *puVar1;
  ushort uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  
  if (param_2 == 0) {
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar3 = *(long *)(param_1 + 0x10);
  if (lVar3 < param_2) {
    lVar3 = param_2 << 1;
    lVar5 = *(long *)(param_1 + 8);
  }
  else {
    lVar5 = lVar3 + 3;
    if (-1 < lVar3) {
      lVar5 = lVar3;
    }
    if (((lVar5 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar3 = param_2 * 2,
       lVar3 - *(long *)(param_1 + 0x28) == 0 || lVar3 < *(long *)(param_1 + 0x28))) {
      if (((param_3 & 1) == 0) && (lVar3 = *(long *)(param_1 + 0x18), lVar3 < param_2)) {
        lVar5 = param_2 - lVar3;
        lVar3 = lVar3 << 8;
        do {
          lVar5 = lVar5 + -1;
          *(undefined1 *)(*(long *)(param_1 + 8) + lVar3) = 0;
          lVar3 = lVar3 + 0x100;
        } while (lVar5 != 0);
      }
      goto code_r0x012ab45c;
    }
    lVar5 = *(long *)(param_1 + 8);
  }
  if (lVar5 == 0) {
    lVar3 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar3 = param_2;
    }
    puVar1 = (undefined1 *)operator new[](unsigned long, std::nothrow_t const&)(lVar3 << 8,PTR__ZSt7nothrow_02cb9a80);
    *(undefined1 **)(param_1 + 8) = puVar1;
    if (puVar1 == (undefined1 *)0x0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    if ((0 < param_2) && ((param_3 & 1) == 0)) {
      lVar5 = param_2 + -1;
      *puVar1 = 0;
      if (lVar5 != 0) {
        lVar4 = 0x100;
        do {
          lVar5 = lVar5 + -1;
          *(undefined1 *)(*(long *)(param_1 + 8) + lVar4) = 0;
          lVar4 = lVar4 + 0x100;
        } while (lVar5 != 0);
      }
    }
    uVar2 = *(ushort *)(param_1 + 0x30) & 0xfffe;
code_r0x012ab450:
    *(ushort *)(param_1 + 0x30) = uVar2;
  }
  else {
    lVar4 = operator new[](unsigned long, std::nothrow_t const&)(param_2 << 9,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar4;
    if (lVar4 == 0) {
      uVar2 = *(ushort *)(param_1 + 0x30) | 1;
      goto code_r0x012ab450;
    }
    lVar8 = *(long *)(param_1 + 0x18);
    lVar9 = param_2;
    if (lVar8 <= param_2) {
      lVar9 = lVar8;
    }
    lVar6 = lVar4;
    lVar7 = lVar5;
    if (0 < lVar9) {
      do {
        memcpy(lVar6,lVar7,0x100);
        lVar9 = lVar9 + -1;
        lVar6 = lVar6 + 0x100;
        lVar7 = lVar7 + 0x100;
      } while (lVar9 != 0);
    }
    if (lVar8 < param_2) {
      lVar9 = lVar8 * 0x100;
      *(undefined1 *)(lVar4 + lVar9) = 0;
      if (lVar8 + 1 != param_2) {
        lVar8 = (param_2 + -1) - lVar8;
        do {
          lVar9 = lVar9 + 0x100;
          lVar8 = lVar8 + -1;
          *(undefined1 *)(*(long *)(param_1 + 8) + lVar9) = 0;
        } while (lVar8 != 0);
      }
    }
    operator delete[](void*)(lVar5);
    *(long *)(param_1 + 0x10) = lVar3;
    *(long *)(param_1 + 0x18) = param_2;
  }
  *(long *)(param_1 + 0x10) = lVar3;
code_r0x012ab45c:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TArray<unsigned int, false>::Resize(long, bool)
// vaddr 0x11ab4c4 | ghidra 0x12ab4c4 | size 460 | symbol _ZN4Aska6TArrayIjLb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIjLb0EE6ResizeElb(long param_1,ulong param_2)

{
  ulong uVar1;
  long lVar2;
  undefined8 *puVar3;
  ulong uVar4;
  ushort uVar5;
  long lVar6;
  ulong uVar7;
  undefined4 *puVar8;
  ulong uVar9;
  undefined4 *puVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  ulong uVar13;
  ulong uVar14;
  ulong uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  
  if (param_2 == 0) {
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar6 = *(long *)(param_1 + 0x10);
  if (lVar6 < (long)param_2) {
    uVar15 = param_2 << 1;
  }
  else {
    lVar2 = lVar6 + 3;
    if (-1 < lVar6) {
      lVar2 = lVar6;
    }
    if (((lVar2 >> 2 < (long)param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (uVar15 = param_2 * 2,
       uVar15 - *(long *)(param_1 + 0x28) == 0 || (long)uVar15 < *(long *)(param_1 + 0x28)))
    goto code_r0x012ab640;
  }
  uVar14 = *(ulong *)(param_1 + 8);
  if (uVar14 == 0) {
    uVar15 = *(ulong *)(param_1 + 0x28);
    if ((long)*(ulong *)(param_1 + 0x28) <= (long)param_2) {
      uVar15 = param_2;
    }
    lVar6 = operator new[](unsigned long, std::nothrow_t const&)(uVar15 << 2,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar6;
    if (lVar6 == 0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    uVar5 = *(ushort *)(param_1 + 0x30) & 0xfffe;
code_r0x012ab638:
    *(ushort *)(param_1 + 0x30) = uVar5;
  }
  else {
    uVar4 = operator new[](unsigned long, std::nothrow_t const&)(param_2 << 3,PTR__ZSt7nothrow_02cb9a80);
    *(ulong *)(param_1 + 8) = uVar4;
    if (uVar4 == 0) {
      uVar5 = *(ushort *)(param_1 + 0x30) | 1;
      goto code_r0x012ab638;
    }
    uVar7 = *(ulong *)(param_1 + 0x18);
    uVar1 = param_2;
    if ((long)uVar7 <= (long)param_2) {
      uVar1 = uVar7;
    }
    if (0 < (long)uVar1) {
      if (uVar1 < 8) {
code_r0x012ab560:
        uVar9 = 0;
      }
      else {
        uVar9 = uVar1 & 0xfffffffffffffff8;
        if (uVar9 != 0) {
          uVar13 = param_2;
          if ((long)uVar7 <= (long)param_2) {
            uVar13 = uVar7;
          }
          if ((uVar4 < uVar14 + uVar1 * 4) &&
             (uVar14 < uVar4 + (-4 - (uVar13 << 2 ^ 0xfffffffffffffffc)))) goto code_r0x012ab560;
          puVar11 = (undefined8 *)(uVar4 + 0x10);
          puVar12 = (undefined8 *)(uVar14 + 0x10);
          uVar13 = uVar9;
          do {
            puVar3 = puVar12 + -1;
            uVar16 = puVar12[-2];
            uVar18 = puVar12[1];
            uVar17 = *puVar12;
            uVar13 = uVar13 - 8;
            puVar12 = puVar12 + 4;
            puVar11[-1] = *puVar3;
            puVar11[-2] = uVar16;
            puVar11[1] = uVar18;
            *puVar11 = uVar17;
            puVar11 = puVar11 + 4;
          } while (uVar13 != 0);
          if (uVar1 == uVar9) goto code_r0x012ab598;
        }
      }
      uVar7 = ~uVar7;
      if ((long)uVar7 < (long)~param_2) {
        uVar7 = ~param_2;
      }
      lVar6 = ~uVar9 - uVar7;
      puVar8 = (undefined4 *)(uVar14 + uVar9 * 4);
      puVar10 = (undefined4 *)(uVar4 + uVar9 * 4);
      do {
        lVar6 = lVar6 + -1;
        *puVar10 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar10 = puVar10 + 1;
      } while (lVar6 != 0);
    }
code_r0x012ab598:
    operator delete[](void*)(uVar14);
    *(ulong *)(param_1 + 0x10) = uVar15;
    *(ulong *)(param_1 + 0x18) = param_2;
  }
  *(ulong *)(param_1 + 0x10) = uVar15;
code_r0x012ab640:
  *(ulong *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TArray<CMovableObject::SphereInfo, false>::ForceRealloc(long, long, CMovableObject::SphereInfo const*, StBoolean<false>)
// vaddr 0x129a42c | ghidra 0x139a42c | size 324 | symbol _ZN4Aska6TArrayIN14CMovableObject10SphereInfoELb0EE12ForceReallocEllPKS2_9StBooleanILb0EE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6TArrayIN14CMovableObject10SphereInfoELb0EE12ForceReallocEllPKS2_9StBooleanILb0EE
               (long param_1,long param_2,long param_3,long param_4)

{
  undefined4 *puVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  long lVar4;
  undefined4 *puVar5;
  long lVar6;
  undefined4 *puVar7;
  long lVar8;
  long lVar9;
  undefined8 uVar10;
  
  lVar9 = *(long *)(param_1 + 8);
  lVar4 = operator new[](unsigned long, std::nothrow_t const&)(param_3 * 0x30,PTR__ZSt7nothrow_02cb9a80);
  *(long *)(param_1 + 8) = lVar4;
  if (lVar4 == 0) {
    *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
  }
  else {
    if (param_4 == 0) {
      lVar8 = *(long *)(param_1 + 0x18);
      lVar6 = param_2;
      if (lVar8 <= param_2) {
        lVar6 = lVar8;
      }
      if (0 < lVar6) {
        puVar5 = (undefined4 *)(lVar9 + 0x10);
        puVar7 = (undefined4 *)(lVar4 + 0x10);
        do {
          lVar6 = lVar6 + -1;
          puVar7[-4] = puVar5[-4];
          puVar7[-3] = puVar5[-3];
          puVar7[-2] = puVar5[-2];
          puVar7[-1] = puVar5[-1];
          *puVar7 = *puVar5;
          puVar1 = puVar5 + 4;
          puVar5 = puVar5 + 0xc;
          puVar7[4] = *puVar1;
          puVar7 = puVar7 + 0xc;
        } while (lVar6 != 0);
        lVar8 = *(long *)(param_1 + 0x18);
      }
      uVar3 = _UNK_027dbb38;
      uVar10 = _UNK_027dbb30;
      if (lVar8 < param_2) {
        lVar4 = param_2 - lVar8;
        lVar8 = lVar8 * 0x30;
        do {
          lVar4 = lVar4 + -1;
          puVar2 = (undefined8 *)(*(long *)(param_1 + 8) + lVar8);
          lVar8 = lVar8 + 0x30;
          puVar2[1] = uVar3;
          *puVar2 = uVar10;
          *(undefined4 *)(puVar2 + 2) = 0;
          *(undefined4 *)(puVar2 + 4) = 0;
        } while (lVar4 != 0);
      }
    }
    else if (0 < param_2) {
      puVar5 = (undefined4 *)(param_4 + 0x20);
      puVar7 = (undefined4 *)(lVar4 + 0x20);
      lVar4 = param_2;
      do {
        uVar10 = *(undefined8 *)(puVar5 + -8);
        lVar4 = lVar4 + -1;
        *(undefined8 *)(puVar7 + -6) = *(undefined8 *)(puVar5 + -6);
        *(undefined8 *)(puVar7 + -8) = uVar10;
        puVar7[-4] = puVar5[-4];
        *puVar7 = *puVar5;
        puVar5 = puVar5 + 0xc;
        puVar7 = puVar7 + 0xc;
      } while (lVar4 != 0);
    }
    if (lVar9 != 0) {
      operator delete[](void*)(lVar9);
    }
    *(long *)(param_1 + 0x10) = param_3;
    *(long *)(param_1 + 0x18) = param_2;
  }
  return;
}

// ==== Aska::TArray<CMovableObject::SphereInfo, false>::Resize(long, bool)
// vaddr 0x129a570 | ghidra 0x139a570 | size 420 | symbol _ZN4Aska6TArrayIN14CMovableObject10SphereInfoELb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska6TArrayIN14CMovableObject10SphereInfoELb0EE6ResizeElb
               (long param_1,long param_2,ulong param_3)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  
  uVar3 = _UNK_027dbb38;
  uVar2 = _UNK_027dbb30;
  if (param_2 == 0) {
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar5 = *(long *)(param_1 + 0x10);
  if (lVar5 < param_2) {
    lVar5 = param_2 << 1;
    lVar6 = *(long *)(param_1 + 8);
  }
  else {
    lVar6 = lVar5 + 3;
    if (-1 < lVar5) {
      lVar6 = lVar5;
    }
    if (((lVar6 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar5 = param_2 * 2,
       lVar5 - *(long *)(param_1 + 0x28) == 0 || lVar5 < *(long *)(param_1 + 0x28))) {
      if (((param_3 & 1) == 0) && (lVar5 = *(long *)(param_1 + 0x18), lVar5 < param_2)) {
        lVar6 = param_2 - lVar5;
        lVar5 = lVar5 * 0x30;
        do {
          lVar6 = lVar6 + -1;
          puVar4 = (undefined8 *)(*(long *)(param_1 + 8) + lVar5);
          lVar5 = lVar5 + 0x30;
          puVar4[1] = uVar3;
          *puVar4 = uVar2;
          *(undefined4 *)(puVar4 + 2) = 0;
          *(undefined4 *)(puVar4 + 4) = 0;
        } while (lVar6 != 0);
      }
      goto code_r0x0139a6f0;
    }
    lVar6 = *(long *)(param_1 + 8);
  }
  if (lVar6 == 0) {
    lVar5 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar5 = param_2;
    }
    puVar4 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(lVar5 * 0x30,PTR__ZSt7nothrow_02cb9a80);
    *(undefined8 **)(param_1 + 8) = puVar4;
    uVar3 = _UNK_027dbb38;
    uVar2 = _UNK_027dbb30;
    if (puVar4 == (undefined8 *)0x0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    if ((0 < param_2) && ((param_3 & 1) == 0)) {
      lVar6 = param_2 + -1;
      *(undefined4 *)(puVar4 + 2) = 0;
      *(undefined4 *)(puVar4 + 4) = 0;
      puVar4[1] = uVar3;
      *puVar4 = uVar2;
      if (lVar6 != 0) {
        lVar7 = 0;
        do {
          lVar6 = lVar6 + -1;
          lVar1 = *(long *)(param_1 + 8) + lVar7;
          lVar7 = lVar7 + 0x30;
          *(undefined8 *)(lVar1 + 0x38) = uVar3;
          *(undefined8 *)(lVar1 + 0x30) = uVar2;
          *(undefined4 *)(lVar1 + 0x40) = 0;
          *(undefined4 *)(lVar1 + 0x50) = 0;
        } while (lVar6 != 0);
      }
    }
    *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) & 0xfffe;
  }
  else {
    Aska::TArray<CMovableObject::SphereInfo, false>::ForceRealloc(long, long, CMovableObject::SphereInfo const*, StBoolean<false>)(param_1,param_2,lVar5,0);
  }
  *(long *)(param_1 + 0x10) = lVar5;
code_r0x0139a6f0:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TStack<unsigned int, 10>::CopyElement(unsigned int const*, unsigned int*)
// vaddr 0x14a9ca0 | ghidra 0x15a9ca0 | size 16 | symbol _ZN4Aska6TStackIjLi10EE11CopyElementEPKjPj | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska6TStackIjLi10EE11CopyElementEPKjPj
          (undefined8 param_1,undefined4 *param_2,undefined4 *param_3)

{
  *param_3 = *param_2;
  return 1;
}

// ==== Aska::TStack<Aska::ASON::AValue*, 10>::CopyElement(Aska::ASON::AValue* const*, Aska::ASON::AValue**)
// vaddr 0x14ac47c | ghidra 0x15ac47c | size 16 | symbol _ZN4Aska6TStackIPNS_4ASON6AValueELi10EE11CopyElementEPKS3_PS3_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska6TStackIPNS_4ASON6AValueELi10EE11CopyElementEPKS3_PS3_
          (undefined8 param_1,undefined8 *param_2,undefined8 *param_3)

{
  *param_3 = *param_2;
  return 1;
}

// ==== Aska::TStack<Aska::ASON::AValue::AMap*, 10>::CopyElement(Aska::ASON::AValue::AMap* const*, Aska::ASON::AValue::AMap**)
// vaddr 0x14ac518 | ghidra 0x15ac518 | size 16 | symbol _ZN4Aska6TStackIPNS_4ASON6AValue4AMapELi10EE11CopyElementEPKS4_PS4_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska6TStackIPNS_4ASON6AValue4AMapELi10EE11CopyElementEPKS4_PS4_
          (undefined8 param_1,undefined8 *param_2,undefined8 *param_3)

{
  *param_3 = *param_2;
  return 1;
}

// ==== Aska::TStack<Aska::ASON::AValue::AArray*, 10>::CopyElement(Aska::ASON::AValue::AArray* const*, Aska::ASON::AValue::AArray**)
// vaddr 0x14ac5b4 | ghidra 0x15ac5b4 | size 16 | symbol _ZN4Aska6TStackIPNS_4ASON6AValue6AArrayELi10EE11CopyElementEPKS4_PS4_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska6TStackIPNS_4ASON6AValue6AArrayELi10EE11CopyElementEPKS4_PS4_
          (undefined8 param_1,undefined8 *param_2,undefined8 *param_3)

{
  *param_3 = *param_2;
  return 1;
}

// ==== Aska::TBitArray<unsigned int, false>::Alloc(unsigned int, unsigned int const*)
// vaddr 0x14b0c30 | ghidra 0x15b0c30 | size 236 | symbol _ZN4Aska9TBitArrayIjLb0EE5AllocEjPKj | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska9TBitArrayIjLb0EE5AllocEjPKj(long param_1,uint param_2,long param_3)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  uint *puVar4;
  
  uVar3 = (ulong)param_2 + 0x1f >> 5;
  uVar2 = (uint)uVar3;
  if (((param_3 == 0) && (*(char *)(param_1 + 0x20) != '\0')) &&
     (uVar1 = *(uint *)(param_1 + 0x18), uVar2 <= uVar1)) {
    *(uint *)(param_1 + 0x1c) = param_2;
    if (uVar1 == 0) {
      return 1;
    }
    param_3 = *(long *)(param_1 + 0x10);
    uVar3 = (ulong)(uVar1 << 2);
  }
  else {
    if ((*(long *)(param_1 + 0x10) != 0) && (*(char *)(param_1 + 0x20) != '\0')) {
      operator delete[](void*)();
      *(undefined1 *)(param_1 + 0x20) = 0;
    }
    *(long *)(param_1 + 0x10) = 0;
    *(undefined8 *)(param_1 + 0x18) = 0;
    if (param_2 == 0) {
      return 1;
    }
    puVar4 = (uint *)(param_1 + 0x18);
    *puVar4 = uVar2;
    *(uint *)(param_1 + 0x1c) = param_2;
    if (param_3 == 0) {
      param_3 = operator new[](unsigned long, std::nothrow_t const&)(uVar3 << 2,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x10) = param_3;
      *(undefined1 *)(param_1 + 0x20) = 1;
      if (param_3 == 0) {
        *(undefined1 *)(param_1 + 0x20) = 0;
        puVar4[0] = 0;
        puVar4[1] = 0;
        return 0;
      }
    }
    else {
      *(long *)(param_1 + 0x10) = param_3;
      *(undefined1 *)(param_1 + 0x20) = 0;
    }
    if (uVar2 == 0) {
      return 1;
    }
    uVar3 = uVar3 << 2;
  }
  memset(param_3,0,uVar3);
  return 1;
}

// ==== Aska::TArray<CBattleEvaluationInfo, false>::SetAt(long, CBattleEvaluationInfo const&)
// vaddr 0x16bf598 | ghidra 0x17bf598 | size 428 | symbol _ZN4Aska6TArrayI21CBattleEvaluationInfoLb0EE5SetAtElRKS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayI21CBattleEvaluationInfoLb0EE5SetAtElRKS1_
               (long param_1,long param_2,long param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  long lVar3;
  undefined8 uVar4;
  undefined *puStack_78;
  undefined4 uStack_70;
  undefined4 uStack_68;
  undefined *puStack_60;
  undefined8 uStack_58;
  undefined1 uStack_50;
  undefined *puStack_48;
  undefined4 uStack_40;
  undefined8 uStack_38;
  
  if (-1 < param_2) {
    if (param_2 < *(long *)(param_1 + 0x18)) {
      lVar3 = *(long *)(param_1 + 8) + param_2 * 0x70;
      *(undefined1 *)(lVar3 + 8) = *(undefined1 *)(param_3 + 8);
      *(undefined8 *)(lVar3 + 0x18) = *(undefined8 *)(param_3 + 0x18);
      *(undefined1 *)(lVar3 + 0x20) = *(undefined1 *)(param_3 + 0x20);
      *(undefined4 *)(lVar3 + 0x30) = *(undefined4 *)(param_3 + 0x30);
      *(undefined4 *)(lVar3 + 0x38) = *(undefined4 *)(param_3 + 0x38);
      *(undefined8 *)(lVar3 + 0x48) = *(undefined8 *)(param_3 + 0x48);
      *(undefined1 *)(lVar3 + 0x50) = *(undefined1 *)(param_3 + 0x50);
      *(undefined4 *)(lVar3 + 0x60) = *(undefined4 *)(param_3 + 0x60);
      *(undefined8 *)(lVar3 + 0x68) = *(undefined8 *)(param_3 + 0x68);
    }
    else {
      uVar1 = *(undefined1 *)(param_3 + 8);
      uVar4 = *(undefined8 *)(param_3 + 0x18);
      uVar2 = *(undefined1 *)(param_3 + 0x20);
      puStack_78 = PTR__ZTVN9Framework7CHash32E_02cba528 + 0x10;
      uStack_70 = *(undefined4 *)(param_3 + 0x30);
      uStack_68 = *(undefined4 *)(param_3 + 0x38);
      uStack_58 = *(undefined8 *)(param_3 + 0x48);
      uStack_50 = *(undefined1 *)(param_3 + 0x50);
      uStack_40 = *(undefined4 *)(param_3 + 0x60);
      uStack_38 = *(undefined8 *)(param_3 + 0x68);
      puStack_48 = puStack_78;
      Aska::TArray<CBattleEvaluationInfo, false>::Resize(long, bool)(param_1,param_2 + 1,0);
      lVar3 = *(long *)(param_1 + 8) + param_2 * 0x70;
      *(undefined1 *)(lVar3 + 8) = uVar1;
      *(undefined8 *)(lVar3 + 0x18) = uVar4;
      *(undefined1 *)(lVar3 + 0x20) = uVar2;
      *(undefined4 *)(lVar3 + 0x30) = uStack_70;
      *(undefined4 *)(lVar3 + 0x38) = uStack_68;
      *(undefined8 *)(lVar3 + 0x48) = uStack_58;
      *(undefined1 *)(lVar3 + 0x50) = uStack_50;
      *(undefined4 *)(lVar3 + 0x60) = uStack_40;
      puStack_60 = PTR__ZTV22CParameterPropertyBaseILj114EE_02cb7f30;
      *(undefined8 *)(lVar3 + 0x68) = uStack_38;
      puStack_60 = puStack_60 + 0x10;
      Framework::CHash32::~CHash32()(&puStack_48);
      Framework::CHash32::~CHash32()(&puStack_78);
    }
  }
  return;
}

// ==== Aska::TArray<CBattleEvaluationInfo, false>::Resize(long, bool)
// vaddr 0x16bf744 | ghidra 0x17bf744 | size 792 | symbol _ZN4Aska6TArrayI21CBattleEvaluationInfoLb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayI21CBattleEvaluationInfoLb0EE6ResizeElb(long param_1,long param_2,ulong param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  long *plVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  
  if (param_2 == 0) {
    if (((*(long **)(param_1 + 8) != (long *)0x0) && (0 < *(long *)(param_1 + 0x18))) &&
       ((**(code **)(**(long **)(param_1 + 8) + 0x10))(), 1 < *(long *)(param_1 + 0x18))) {
      lVar7 = 1;
      lVar8 = 0x70;
      do {
        (**(code **)(*(long *)(*(long *)(param_1 + 8) + lVar8) + 0x10))();
        lVar7 = lVar7 + 1;
        lVar8 = lVar8 + 0x70;
      } while (lVar7 < *(long *)(param_1 + 0x18));
    }
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar7 = *(long *)(param_1 + 0x10);
  if (lVar7 < param_2) {
    lVar7 = param_2 << 1;
    lVar8 = *(long *)(param_1 + 8);
  }
  else {
    lVar8 = lVar7 + 3;
    if (-1 < lVar7) {
      lVar8 = lVar7;
    }
    if (((lVar8 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar7 = param_2 * 2,
       lVar7 - *(long *)(param_1 + 0x28) == 0 || lVar7 < *(long *)(param_1 + 0x28))) {
      if (((param_3 & 1) == 0) && (lVar7 = *(long *)(param_1 + 0x18), lVar7 < param_2)) {
        lVar8 = param_2 - lVar7;
        lVar7 = lVar7 * 0x70 + 0x40;
        puVar1 = PTR__ZTV21CBattleEvaluationInfo_02cbb298 + 0x10;
        puVar2 = PTR__ZTV22CParameterPropertyBaseILj113EE_02cbfb58 + 0x10;
        puVar3 = PTR__ZTV23CParameterPropertyValueIjLj113E18CPropertyConverterE_02cbf818 + 0x10;
        puVar4 = PTR__ZTV22CParameterPropertyBaseILj114EE_02cb7f30 + 0x10;
        puVar5 = PTR__ZTV23CParameterPropertyValueImLj114E18CPropertyConverterE_02cb9530 + 0x10;
        do {
          plVar6 = (long *)(*(long *)(param_1 + 8) + lVar7);
          *(undefined1 *)(plVar6 + -7) = 1;
          plVar6[-8] = (long)puVar1;
          plVar6[-6] = (long)puVar2;
          plVar6[-5] = 0;
          *(undefined1 *)(plVar6 + -4) = 0;
          Framework::CHash32::CHash32()(plVar6 + -3);
          plVar6[-6] = (long)puVar3;
          *plVar6 = (long)puVar4;
          plVar6[1] = 0;
          *(undefined1 *)(plVar6 + 2) = 0;
          Framework::CHash32::CHash32()(plVar6 + 3);
          lVar8 = lVar8 + -1;
          lVar7 = lVar7 + 0x70;
          *plVar6 = (long)puVar5;
        } while (lVar8 != 0);
      }
      if (param_2 < *(long *)(param_1 + 0x18)) {
        lVar8 = param_2 * 0x70;
        lVar7 = param_2;
        do {
          (**(code **)(*(long *)(*(long *)(param_1 + 8) + lVar8) + 0x10))();
          lVar7 = lVar7 + 1;
          lVar8 = lVar8 + 0x70;
        } while (lVar7 < *(long *)(param_1 + 0x18));
      }
      goto code_r0x017bfa28;
    }
    lVar8 = *(long *)(param_1 + 8);
  }
  if (lVar8 == 0) {
    lVar7 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar7 = param_2;
    }
    lVar8 = operator new[](unsigned long, std::nothrow_t const&)(lVar7 * 0x70,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar8;
    if (lVar8 == 0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    if ((0 < param_2) && ((param_3 & 1) == 0)) {
      lVar9 = 0x40;
      puVar1 = PTR__ZTV21CBattleEvaluationInfo_02cbb298 + 0x10;
      puVar2 = PTR__ZTV22CParameterPropertyBaseILj113EE_02cbfb58 + 0x10;
      puVar3 = PTR__ZTV23CParameterPropertyValueIjLj113E18CPropertyConverterE_02cbf818 + 0x10;
      puVar4 = PTR__ZTV22CParameterPropertyBaseILj114EE_02cb7f30 + 0x10;
      puVar5 = PTR__ZTV23CParameterPropertyValueImLj114E18CPropertyConverterE_02cb9530 + 0x10;
      lVar10 = param_2;
      while( true ) {
        lVar10 = lVar10 + -1;
        plVar6 = (long *)(lVar8 + lVar9);
        *(undefined1 *)(plVar6 + -7) = 1;
        plVar6[-8] = (long)puVar1;
        plVar6[-6] = (long)puVar2;
        plVar6[-5] = 0;
        *(undefined1 *)(plVar6 + -4) = 0;
        Framework::CHash32::CHash32()(plVar6 + -3);
        plVar6[-6] = (long)puVar3;
        *plVar6 = (long)puVar4;
        plVar6[1] = 0;
        *(undefined1 *)(plVar6 + 2) = 0;
        Framework::CHash32::CHash32()(plVar6 + 3);
        *plVar6 = (long)puVar5;
        if (lVar10 == 0) break;
        lVar8 = *(long *)(param_1 + 8);
        lVar9 = lVar9 + 0x70;
      }
    }
    *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) & 0xfffe;
  }
  else {
    Aska::TArray<CBattleEvaluationInfo, false>::ForceRealloc(long, long, CBattleEvaluationInfo const*, StBoolean<false>)(param_1,param_2,lVar7,0);
  }
  *(long *)(param_1 + 0x10) = lVar7;
code_r0x017bfa28:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TArray<CPersonStatusInfo, false>::Resize(long, bool)
// vaddr 0x16bfd7c | ghidra 0x17bfd7c | size 528 | symbol _ZN4Aska6TArrayI17CPersonStatusInfoLb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayI17CPersonStatusInfoLb0EE6ResizeElb(long param_1,long param_2,ulong param_3)

{
  long lVar1;
  long lVar2;
  long lVar3;
  
  if (param_2 == 0) {
    if (((*(long *)(param_1 + 8) != 0) && (0 < *(long *)(param_1 + 0x18))) &&
       (CPersonStatusInfo::~CPersonStatusInfo()(), 1 < *(long *)(param_1 + 0x18))) {
      lVar1 = 1;
      lVar2 = 0x1690;
      do {
        CPersonStatusInfo::~CPersonStatusInfo()(*(long *)(param_1 + 8) + lVar2);
        lVar1 = lVar1 + 1;
        lVar2 = lVar2 + 0x1690;
      } while (lVar1 < *(long *)(param_1 + 0x18));
    }
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar1 = *(long *)(param_1 + 0x10);
  if (lVar1 < param_2) {
    lVar1 = param_2 << 1;
    lVar2 = *(long *)(param_1 + 8);
  }
  else {
    lVar2 = lVar1 + 3;
    if (-1 < lVar1) {
      lVar2 = lVar1;
    }
    if (((lVar2 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar1 = param_2 * 2,
       lVar1 - *(long *)(param_1 + 0x28) == 0 || lVar1 < *(long *)(param_1 + 0x28))) {
      if (((param_3 & 1) == 0) && (lVar1 = *(long *)(param_1 + 0x18), lVar1 < param_2)) {
        lVar2 = lVar1 * 0x1690;
        lVar1 = param_2 - lVar1;
        do {
          CPersonStatusInfo::CPersonStatusInfo()(*(long *)(param_1 + 8) + lVar2);
          lVar1 = lVar1 + -1;
          lVar2 = lVar2 + 0x1690;
        } while (lVar1 != 0);
      }
      if (param_2 < *(long *)(param_1 + 0x18)) {
        lVar2 = param_2 * 0x1690;
        lVar1 = param_2;
        do {
          CPersonStatusInfo::~CPersonStatusInfo()(*(long *)(param_1 + 8) + lVar2);
          lVar1 = lVar1 + 1;
          lVar2 = lVar2 + 0x1690;
        } while (lVar1 < *(long *)(param_1 + 0x18));
      }
      goto code_r0x017bff64;
    }
    lVar2 = *(long *)(param_1 + 8);
  }
  if (lVar2 == 0) {
    lVar1 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar1 = param_2;
    }
    lVar2 = operator new[](unsigned long, std::nothrow_t const&)(lVar1 * 0x1690,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar2;
    if (lVar2 == 0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    if ((0 < param_2) && ((param_3 & 1) == 0)) {
      CPersonStatusInfo::CPersonStatusInfo()();
      lVar2 = param_2 + -1;
      if (lVar2 != 0) {
        lVar3 = 0x1690;
        do {
          CPersonStatusInfo::CPersonStatusInfo()(*(long *)(param_1 + 8) + lVar3);
          lVar2 = lVar2 + -1;
          lVar3 = lVar3 + 0x1690;
        } while (lVar2 != 0);
      }
    }
    *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) & 0xfffe;
  }
  else {
    Aska::TArray<CPersonStatusInfo, false>::ForceRealloc(long, long, CPersonStatusInfo const*, StBoolean<false>)(param_1,param_2,lVar1,0);
  }
  *(long *)(param_1 + 0x10) = lVar1;
code_r0x017bff64:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TArray<CPlayerLogInfo, false>::SetAt(long, CPlayerLogInfo const&)
// vaddr 0x16c00dc | ghidra 0x17c00dc | size 584 | symbol _ZN4Aska6TArrayI14CPlayerLogInfoLb0EE5SetAtElRKS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayI14CPlayerLogInfoLb0EE5SetAtElRKS1_(long param_1,long param_2,long param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  long lVar3;
  undefined8 uVar4;
  undefined *puStack_b8;
  undefined4 uStack_b0;
  undefined4 uStack_a8;
  undefined *puStack_a0;
  undefined8 uStack_98;
  undefined1 uStack_90;
  undefined *puStack_88;
  undefined4 uStack_80;
  undefined4 uStack_78;
  undefined *puStack_70;
  undefined8 uStack_68;
  undefined1 uStack_60;
  undefined *puStack_58;
  undefined4 uStack_50;
  undefined4 uStack_48;
  
  if (-1 < param_2) {
    if (param_2 < *(long *)(param_1 + 0x18)) {
      lVar3 = *(long *)(param_1 + 8) + param_2 * 0xa0;
      *(undefined1 *)(lVar3 + 8) = *(undefined1 *)(param_3 + 8);
      *(undefined8 *)(lVar3 + 0x18) = *(undefined8 *)(param_3 + 0x18);
      *(undefined1 *)(lVar3 + 0x20) = *(undefined1 *)(param_3 + 0x20);
      *(undefined4 *)(lVar3 + 0x30) = *(undefined4 *)(param_3 + 0x30);
      *(undefined4 *)(lVar3 + 0x38) = *(undefined4 *)(param_3 + 0x38);
      *(undefined8 *)(lVar3 + 0x48) = *(undefined8 *)(param_3 + 0x48);
      *(undefined1 *)(lVar3 + 0x50) = *(undefined1 *)(param_3 + 0x50);
      *(undefined4 *)(lVar3 + 0x60) = *(undefined4 *)(param_3 + 0x60);
      *(undefined4 *)(lVar3 + 0x68) = *(undefined4 *)(param_3 + 0x68);
      *(undefined8 *)(lVar3 + 0x78) = *(undefined8 *)(param_3 + 0x78);
      *(undefined1 *)(lVar3 + 0x80) = *(undefined1 *)(param_3 + 0x80);
      *(undefined4 *)(lVar3 + 0x90) = *(undefined4 *)(param_3 + 0x90);
      *(undefined4 *)(lVar3 + 0x98) = *(undefined4 *)(param_3 + 0x98);
    }
    else {
      uVar1 = *(undefined1 *)(param_3 + 8);
      uVar4 = *(undefined8 *)(param_3 + 0x18);
      uVar2 = *(undefined1 *)(param_3 + 0x20);
      puStack_b8 = PTR__ZTVN9Framework7CHash32E_02cba528 + 0x10;
      uStack_b0 = *(undefined4 *)(param_3 + 0x30);
      uStack_a8 = *(undefined4 *)(param_3 + 0x38);
      uStack_98 = *(undefined8 *)(param_3 + 0x48);
      uStack_90 = *(undefined1 *)(param_3 + 0x50);
      uStack_80 = *(undefined4 *)(param_3 + 0x60);
      puStack_a0 = PTR__ZTV23CParameterPropertyValueIjLj81E18CPropertyConverterE_02cc0da8 + 0x10;
      uStack_78 = *(undefined4 *)(param_3 + 0x68);
      uStack_68 = *(undefined8 *)(param_3 + 0x78);
      uStack_60 = *(undefined1 *)(param_3 + 0x80);
      uStack_50 = *(undefined4 *)(param_3 + 0x90);
      uStack_48 = *(undefined4 *)(param_3 + 0x98);
      puStack_88 = puStack_b8;
      puStack_58 = puStack_b8;
      Aska::TArray<CPlayerLogInfo, false>::Resize(long, bool)(param_1,param_2 + 1,0);
      lVar3 = *(long *)(param_1 + 8) + param_2 * 0xa0;
      *(undefined1 *)(lVar3 + 8) = uVar1;
      *(undefined8 *)(lVar3 + 0x18) = uVar4;
      *(undefined1 *)(lVar3 + 0x20) = uVar2;
      *(undefined4 *)(lVar3 + 0x30) = uStack_b0;
      *(undefined4 *)(lVar3 + 0x38) = uStack_a8;
      *(undefined8 *)(lVar3 + 0x48) = uStack_98;
      *(undefined1 *)(lVar3 + 0x50) = uStack_90;
      *(undefined4 *)(lVar3 + 0x60) = uStack_80;
      *(undefined4 *)(lVar3 + 0x68) = uStack_78;
      *(undefined8 *)(lVar3 + 0x78) = uStack_68;
      *(undefined1 *)(lVar3 + 0x80) = uStack_60;
      *(undefined4 *)(lVar3 + 0x90) = uStack_50;
      puStack_70 = PTR__ZTV22CParameterPropertyBaseILj82EE_02cc4fc8;
      *(undefined4 *)(lVar3 + 0x98) = uStack_48;
      puStack_70 = puStack_70 + 0x10;
      Framework::CHash32::~CHash32()(&puStack_58);
      puStack_a0 = PTR__ZTV22CParameterPropertyBaseILj81EE_02cc0f08 + 0x10;
      Framework::CHash32::~CHash32()(&puStack_88);
      Framework::CHash32::~CHash32()(&puStack_b8);
    }
  }
  return;
}

// ==== Aska::TArray<CPlayerLogInfo, false>::Resize(long, bool)
// vaddr 0x16c0324 | ghidra 0x17c0324 | size 892 | symbol _ZN4Aska6TArrayI14CPlayerLogInfoLb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayI14CPlayerLogInfoLb0EE6ResizeElb(long param_1,long param_2,ulong param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined8 *puVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  
  if (param_2 == 0) {
    if (((*(long **)(param_1 + 8) != (long *)0x0) && (0 < *(long *)(param_1 + 0x18))) &&
       ((**(code **)(**(long **)(param_1 + 8) + 0x10))(), 1 < *(long *)(param_1 + 0x18))) {
      lVar9 = 1;
      lVar10 = 0xa0;
      do {
        (**(code **)(*(long *)(*(long *)(param_1 + 8) + lVar10) + 0x10))();
        lVar9 = lVar9 + 1;
        lVar10 = lVar10 + 0xa0;
      } while (lVar9 < *(long *)(param_1 + 0x18));
    }
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar9 = *(long *)(param_1 + 0x10);
  if (lVar9 < param_2) {
    lVar9 = param_2 << 1;
    lVar10 = *(long *)(param_1 + 8);
  }
  else {
    lVar10 = lVar9 + 3;
    if (-1 < lVar9) {
      lVar10 = lVar9;
    }
    if (((lVar10 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar9 = param_2 * 2,
       lVar9 - *(long *)(param_1 + 0x28) == 0 || lVar9 < *(long *)(param_1 + 0x28))) {
      if (((param_3 & 1) == 0) && (lVar9 = *(long *)(param_1 + 0x18), lVar9 < param_2)) {
        lVar10 = param_2 - lVar9;
        puVar1 = PTR__ZTV14CPlayerLogInfo_02cbeb30 + 0x10;
        puVar2 = PTR__ZTV22CParameterPropertyBaseILj80EE_02cb6c00 + 0x10;
        puVar3 = PTR__ZTV23CParameterPropertyValueIiLj80E18CPropertyConverterE_02cc1480 + 0x10;
        puVar4 = PTR__ZTV22CParameterPropertyBaseILj81EE_02cc0f08 + 0x10;
        puVar5 = PTR__ZTV23CParameterPropertyValueIjLj81E18CPropertyConverterE_02cc0da8 + 0x10;
        puVar6 = PTR__ZTV22CParameterPropertyBaseILj82EE_02cc4fc8 + 0x10;
        lVar9 = lVar9 * 0xa0 + 0x48;
        puVar7 = PTR__ZTV23CParameterPropertyValueIjLj82E18CPropertyConverterE_02cbf198 + 0x10;
        do {
          puVar8 = (undefined8 *)(*(long *)(param_1 + 8) + lVar9);
          *(undefined1 *)(puVar8 + -8) = 1;
          puVar8[-9] = puVar1;
          puVar8[-7] = puVar2;
          puVar8[-6] = 0;
          *(undefined1 *)(puVar8 + -5) = 0;
          Framework::CHash32::CHash32()(puVar8 + -4);
          puVar8[-7] = puVar3;
          puVar8[-1] = puVar4;
          *puVar8 = 0;
          *(undefined1 *)(puVar8 + 1) = 0;
          Framework::CHash32::CHash32()(puVar8 + 2);
          puVar8[-1] = puVar5;
          puVar8[5] = puVar6;
          puVar8[6] = 0;
          *(undefined1 *)(puVar8 + 7) = 0;
          Framework::CHash32::CHash32()(puVar8 + 8);
          lVar10 = lVar10 + -1;
          lVar9 = lVar9 + 0xa0;
          puVar8[5] = puVar7;
        } while (lVar10 != 0);
      }
      if (param_2 < *(long *)(param_1 + 0x18)) {
        lVar10 = param_2 * 0xa0;
        lVar9 = param_2;
        do {
          (**(code **)(*(long *)(*(long *)(param_1 + 8) + lVar10) + 0x10))();
          lVar9 = lVar9 + 1;
          lVar10 = lVar10 + 0xa0;
        } while (lVar9 < *(long *)(param_1 + 0x18));
      }
      goto code_r0x017c066c;
    }
    lVar10 = *(long *)(param_1 + 8);
  }
  if (lVar10 == 0) {
    lVar9 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar9 = param_2;
    }
    lVar10 = operator new[](unsigned long, std::nothrow_t const&)(lVar9 * 0xa0,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar10;
    if (lVar10 == 0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    if ((0 < param_2) && ((param_3 & 1) == 0)) {
      lVar11 = 0x48;
      puVar1 = PTR__ZTV14CPlayerLogInfo_02cbeb30 + 0x10;
      puVar2 = PTR__ZTV22CParameterPropertyBaseILj80EE_02cb6c00 + 0x10;
      puVar3 = PTR__ZTV23CParameterPropertyValueIiLj80E18CPropertyConverterE_02cc1480 + 0x10;
      puVar4 = PTR__ZTV22CParameterPropertyBaseILj81EE_02cc0f08 + 0x10;
      puVar5 = PTR__ZTV23CParameterPropertyValueIjLj81E18CPropertyConverterE_02cc0da8 + 0x10;
      puVar6 = PTR__ZTV22CParameterPropertyBaseILj82EE_02cc4fc8 + 0x10;
      puVar7 = PTR__ZTV23CParameterPropertyValueIjLj82E18CPropertyConverterE_02cbf198 + 0x10;
      lVar12 = param_2;
      while( true ) {
        lVar12 = lVar12 + -1;
        puVar8 = (undefined8 *)(lVar10 + lVar11);
        *(undefined1 *)(puVar8 + -8) = 1;
        puVar8[-9] = puVar1;
        puVar8[-7] = puVar2;
        puVar8[-6] = 0;
        *(undefined1 *)(puVar8 + -5) = 0;
        Framework::CHash32::CHash32()(puVar8 + -4);
        puVar8[-7] = puVar3;
        puVar8[-1] = puVar4;
        *puVar8 = 0;
        *(undefined1 *)(puVar8 + 1) = 0;
        Framework::CHash32::CHash32()(puVar8 + 2);
        puVar8[-1] = puVar5;
        puVar8[5] = puVar6;
        puVar8[6] = 0;
        *(undefined1 *)(puVar8 + 7) = 0;
        Framework::CHash32::CHash32()(puVar8 + 8);
        puVar8[5] = puVar7;
        if (lVar12 == 0) break;
        lVar10 = *(long *)(param_1 + 8);
        lVar11 = lVar11 + 0xa0;
      }
    }
    *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) & 0xfffe;
  }
  else {
    Aska::TArray<CPlayerLogInfo, false>::ForceRealloc(long, long, CPlayerLogInfo const*, StBoolean<false>)(param_1,param_2,lVar9,0);
  }
  *(long *)(param_1 + 0x10) = lVar9;
code_r0x017c066c:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TArray<CEnemyInfo, false>::SetAt(long, CEnemyInfo const&)
// vaddr 0x16c09c4 | ghidra 0x17c09c4 | size 428 | symbol _ZN4Aska6TArrayI10CEnemyInfoLb0EE5SetAtElRKS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayI10CEnemyInfoLb0EE5SetAtElRKS1_(long param_1,long param_2,long param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  long lVar3;
  undefined8 uVar4;
  undefined *puStack_78;
  undefined4 uStack_70;
  undefined4 uStack_68;
  undefined *puStack_60;
  undefined8 uStack_58;
  undefined1 uStack_50;
  undefined *puStack_48;
  undefined4 uStack_40;
  undefined4 uStack_38;
  
  if (-1 < param_2) {
    if (param_2 < *(long *)(param_1 + 0x18)) {
      lVar3 = *(long *)(param_1 + 8) + param_2 * 0x70;
      *(undefined1 *)(lVar3 + 8) = *(undefined1 *)(param_3 + 8);
      *(undefined8 *)(lVar3 + 0x18) = *(undefined8 *)(param_3 + 0x18);
      *(undefined1 *)(lVar3 + 0x20) = *(undefined1 *)(param_3 + 0x20);
      *(undefined4 *)(lVar3 + 0x30) = *(undefined4 *)(param_3 + 0x30);
      *(undefined4 *)(lVar3 + 0x38) = *(undefined4 *)(param_3 + 0x38);
      *(undefined8 *)(lVar3 + 0x48) = *(undefined8 *)(param_3 + 0x48);
      *(undefined1 *)(lVar3 + 0x50) = *(undefined1 *)(param_3 + 0x50);
      *(undefined4 *)(lVar3 + 0x60) = *(undefined4 *)(param_3 + 0x60);
      *(undefined4 *)(lVar3 + 0x68) = *(undefined4 *)(param_3 + 0x68);
    }
    else {
      uVar1 = *(undefined1 *)(param_3 + 8);
      uVar4 = *(undefined8 *)(param_3 + 0x18);
      uVar2 = *(undefined1 *)(param_3 + 0x20);
      puStack_78 = PTR__ZTVN9Framework7CHash32E_02cba528 + 0x10;
      uStack_70 = *(undefined4 *)(param_3 + 0x30);
      uStack_68 = *(undefined4 *)(param_3 + 0x38);
      uStack_58 = *(undefined8 *)(param_3 + 0x48);
      uStack_50 = *(undefined1 *)(param_3 + 0x50);
      uStack_40 = *(undefined4 *)(param_3 + 0x60);
      uStack_38 = *(undefined4 *)(param_3 + 0x68);
      puStack_48 = puStack_78;
      Aska::TArray<CEnemyInfo, false>::Resize(long, bool)(param_1,param_2 + 1,0);
      lVar3 = *(long *)(param_1 + 8) + param_2 * 0x70;
      *(undefined1 *)(lVar3 + 8) = uVar1;
      *(undefined8 *)(lVar3 + 0x18) = uVar4;
      *(undefined1 *)(lVar3 + 0x20) = uVar2;
      *(undefined4 *)(lVar3 + 0x30) = uStack_70;
      *(undefined4 *)(lVar3 + 0x38) = uStack_68;
      *(undefined8 *)(lVar3 + 0x48) = uStack_58;
      *(undefined1 *)(lVar3 + 0x50) = uStack_50;
      *(undefined4 *)(lVar3 + 0x60) = uStack_40;
      puStack_60 = PTR__ZTV22CParameterPropertyBaseILj47EE_02cba780;
      *(undefined4 *)(lVar3 + 0x68) = uStack_38;
      puStack_60 = puStack_60 + 0x10;
      Framework::CHash32::~CHash32()(&puStack_48);
      Framework::CHash32::~CHash32()(&puStack_78);
    }
  }
  return;
}

// ==== Aska::TArray<CEnemyInfo, false>::Resize(long, bool)
// vaddr 0x16c0b70 | ghidra 0x17c0b70 | size 792 | symbol _ZN4Aska6TArrayI10CEnemyInfoLb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayI10CEnemyInfoLb0EE6ResizeElb(long param_1,long param_2,ulong param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  long *plVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  
  if (param_2 == 0) {
    if (((*(long **)(param_1 + 8) != (long *)0x0) && (0 < *(long *)(param_1 + 0x18))) &&
       ((**(code **)(**(long **)(param_1 + 8) + 0x10))(), 1 < *(long *)(param_1 + 0x18))) {
      lVar7 = 1;
      lVar8 = 0x70;
      do {
        (**(code **)(*(long *)(*(long *)(param_1 + 8) + lVar8) + 0x10))();
        lVar7 = lVar7 + 1;
        lVar8 = lVar8 + 0x70;
      } while (lVar7 < *(long *)(param_1 + 0x18));
    }
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar7 = *(long *)(param_1 + 0x10);
  if (lVar7 < param_2) {
    lVar7 = param_2 << 1;
    lVar8 = *(long *)(param_1 + 8);
  }
  else {
    lVar8 = lVar7 + 3;
    if (-1 < lVar7) {
      lVar8 = lVar7;
    }
    if (((lVar8 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar7 = param_2 * 2,
       lVar7 - *(long *)(param_1 + 0x28) == 0 || lVar7 < *(long *)(param_1 + 0x28))) {
      if (((param_3 & 1) == 0) && (lVar7 = *(long *)(param_1 + 0x18), lVar7 < param_2)) {
        lVar8 = param_2 - lVar7;
        lVar7 = lVar7 * 0x70 + 0x40;
        puVar1 = PTR__ZTV10CEnemyInfo_02cbcac0 + 0x10;
        puVar2 = PTR__ZTV22CParameterPropertyBaseILj46EE_02cc4ed0 + 0x10;
        puVar3 = PTR__ZTV23CParameterPropertyValueIjLj46E18CPropertyConverterE_02cbb308 + 0x10;
        puVar4 = PTR__ZTV22CParameterPropertyBaseILj47EE_02cba780 + 0x10;
        puVar5 = PTR__ZTV23CParameterPropertyValueIjLj47E18CPropertyConverterE_02cc0678 + 0x10;
        do {
          plVar6 = (long *)(*(long *)(param_1 + 8) + lVar7);
          *(undefined1 *)(plVar6 + -7) = 1;
          plVar6[-8] = (long)puVar1;
          plVar6[-6] = (long)puVar2;
          plVar6[-5] = 0;
          *(undefined1 *)(plVar6 + -4) = 0;
          Framework::CHash32::CHash32()(plVar6 + -3);
          plVar6[-6] = (long)puVar3;
          *plVar6 = (long)puVar4;
          plVar6[1] = 0;
          *(undefined1 *)(plVar6 + 2) = 0;
          Framework::CHash32::CHash32()(plVar6 + 3);
          lVar8 = lVar8 + -1;
          lVar7 = lVar7 + 0x70;
          *plVar6 = (long)puVar5;
        } while (lVar8 != 0);
      }
      if (param_2 < *(long *)(param_1 + 0x18)) {
        lVar8 = param_2 * 0x70;
        lVar7 = param_2;
        do {
          (**(code **)(*(long *)(*(long *)(param_1 + 8) + lVar8) + 0x10))();
          lVar7 = lVar7 + 1;
          lVar8 = lVar8 + 0x70;
        } while (lVar7 < *(long *)(param_1 + 0x18));
      }
      goto code_r0x017c0e54;
    }
    lVar8 = *(long *)(param_1 + 8);
  }
  if (lVar8 == 0) {
    lVar7 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar7 = param_2;
    }
    lVar8 = operator new[](unsigned long, std::nothrow_t const&)(lVar7 * 0x70,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar8;
    if (lVar8 == 0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    if ((0 < param_2) && ((param_3 & 1) == 0)) {
      lVar9 = 0x40;
      puVar1 = PTR__ZTV10CEnemyInfo_02cbcac0 + 0x10;
      puVar2 = PTR__ZTV22CParameterPropertyBaseILj46EE_02cc4ed0 + 0x10;
      puVar3 = PTR__ZTV23CParameterPropertyValueIjLj46E18CPropertyConverterE_02cbb308 + 0x10;
      puVar4 = PTR__ZTV22CParameterPropertyBaseILj47EE_02cba780 + 0x10;
      puVar5 = PTR__ZTV23CParameterPropertyValueIjLj47E18CPropertyConverterE_02cc0678 + 0x10;
      lVar10 = param_2;
      while( true ) {
        lVar10 = lVar10 + -1;
        plVar6 = (long *)(lVar8 + lVar9);
        *(undefined1 *)(plVar6 + -7) = 1;
        plVar6[-8] = (long)puVar1;
        plVar6[-6] = (long)puVar2;
        plVar6[-5] = 0;
        *(undefined1 *)(plVar6 + -4) = 0;
        Framework::CHash32::CHash32()(plVar6 + -3);
        plVar6[-6] = (long)puVar3;
        *plVar6 = (long)puVar4;
        plVar6[1] = 0;
        *(undefined1 *)(plVar6 + 2) = 0;
        Framework::CHash32::CHash32()(plVar6 + 3);
        *plVar6 = (long)puVar5;
        if (lVar10 == 0) break;
        lVar8 = *(long *)(param_1 + 8);
        lVar9 = lVar9 + 0x70;
      }
    }
    *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) & 0xfffe;
  }
  else {
    Aska::TArray<CEnemyInfo, false>::ForceRealloc(long, long, CEnemyInfo const*, StBoolean<false>)(param_1,param_2,lVar7,0);
  }
  *(long *)(param_1 + 0x10) = lVar7;
code_r0x017c0e54:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TArray<std::__ndk1::shared_ptr<CMasterParameterRankElement>, false>::ForceRealloc(long, long, std::__ndk1::shared_ptr<CMasterParameterRankElement> const*, StBoolean<false>)
// vaddr 0x16dde6c | ghidra 0x17dde6c | size 340 | symbol _ZN4Aska6TArrayINSt6__ndk110shared_ptrI27CMasterParameterRankElementEELb0EE12ForceReallocEllPKS4_9StBooleanILb0EE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayINSt6__ndk110shared_ptrI27CMasterParameterRankElementEELb0EE12ForceReallocEllPKS4_9StBooleanILb0EE
               (long param_1,long param_2,long param_3,long param_4)

{
  undefined8 *puVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  long *plVar5;
  long lVar6;
  long *plVar7;
  
  lVar4 = *(long *)(param_1 + 8);
  lVar2 = operator new[](unsigned long, std::nothrow_t const&)(param_3 << 4,PTR__ZSt7nothrow_02cb9a80);
  *(long *)(param_1 + 8) = lVar2;
  if (lVar2 == 0) {
    *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
    return;
  }
  if (param_4 == 0) {
    lVar3 = *(long *)(param_1 + 0x18);
    lVar6 = param_2;
    if (lVar3 <= param_2) {
      lVar6 = lVar3;
    }
    if (0 < lVar6) {
      plVar5 = (long *)(lVar4 + 8);
      plVar7 = (long *)(lVar2 + 8);
      do {
        plVar7[-1] = plVar5[-1];
        lVar2 = *plVar5;
        *plVar7 = lVar2;
        if (lVar2 != 0) {
          std::__ndk1::__shared_weak_count::__add_shared()();
        }
        lVar6 = lVar6 + -1;
        plVar5 = plVar5 + 2;
        plVar7 = plVar7 + 2;
      } while (lVar6 != 0);
      lVar3 = *(long *)(param_1 + 0x18);
    }
    if (lVar3 < param_2) {
      lVar2 = lVar3 << 4;
      lVar3 = param_2 - lVar3;
      do {
        lVar3 = lVar3 + -1;
        puVar1 = (undefined8 *)(*(long *)(param_1 + 8) + lVar2);
        lVar2 = lVar2 + 0x10;
        *puVar1 = 0;
        puVar1[1] = 0;
      } while (lVar3 != 0);
    }
  }
  else if (0 < param_2) {
    plVar5 = (long *)(param_4 + 8);
    plVar7 = (long *)(lVar2 + 8);
    lVar2 = param_2;
    do {
      lVar6 = *plVar5;
      plVar7[-1] = plVar5[-1];
      *plVar7 = lVar6;
      if (lVar6 != 0) {
        std::__ndk1::__shared_weak_count::__add_shared()();
      }
      lVar2 = lVar2 + -1;
      plVar5 = plVar5 + 2;
      plVar7 = plVar7 + 2;
    } while (lVar2 != 0);
  }
  lVar2 = *(long *)(param_1 + 0x18);
  if (lVar2 < 1) {
    if (lVar4 == 0) goto code_r0x017ddfa8;
  }
  else {
    lVar6 = 0;
    plVar5 = (long *)(lVar4 + 8);
    do {
      if (*plVar5 != 0) {
        std::__ndk1::__shared_weak_count::__release_shared()();
        lVar2 = *(long *)(param_1 + 0x18);
      }
      lVar6 = lVar6 + 1;
      plVar5 = plVar5 + 2;
    } while (lVar6 < lVar2);
  }
  operator delete[](void*)(lVar4);
code_r0x017ddfa8:
  *(long *)(param_1 + 0x10) = param_3;
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TArray<std::__ndk1::shared_ptr<CMasterParameterRankElement>, false>::SetAt(long, std::__ndk1::shared_ptr<CMasterParameterRankElement> const&)
// vaddr 0x16de048 | ghidra 0x17de048 | size 184 | symbol _ZN4Aska6TArrayINSt6__ndk110shared_ptrI27CMasterParameterRankElementEELb0EE5SetAtElRKS4_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x017de0d4: Changing call to branch */

void _ZN4Aska6TArrayINSt6__ndk110shared_ptrI27CMasterParameterRankElementEELb0EE5SetAtElRKS4_
               (long param_1,long param_2,undefined8 *param_3)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  long lVar3;
  long lVar4;
  
  if (-1 < param_2) {
    if (param_2 < *(long *)(param_1 + 0x18)) {
      uVar2 = *param_3;
      lVar4 = param_3[1];
      puVar1 = (undefined8 *)(*(long *)(param_1 + 8) + param_2 * 0x10);
      if (lVar4 != 0) {
        std::__ndk1::__shared_weak_count::__add_shared()(lVar4);
      }
      lVar3 = puVar1[1];
      *puVar1 = uVar2;
      puVar1[1] = lVar4;
    }
    else {
      uVar2 = *param_3;
      lVar3 = param_3[1];
      if (lVar3 != 0) {
        std::__ndk1::__shared_weak_count::__add_shared()(lVar3);
      }
      Aska::TArray<std::__ndk1::shared_ptr<CMasterParameterRankElement>, false>::Resize(long, bool)(param_1,param_2 + 1,0);
      puVar1 = (undefined8 *)(*(long *)(param_1 + 8) + param_2 * 0x10);
      if (lVar3 != 0) {
        std::__ndk1::__shared_weak_count::__add_shared()(lVar3);
      }
      lVar4 = puVar1[1];
      *puVar1 = uVar2;
      puVar1[1] = lVar3;
      if (lVar4 != 0) goto code_r0x011f1b20;
    }
    lVar4 = lVar3;
    if (lVar4 != 0) {
code_r0x011f1b20:
      (*(code *)PTR__ZNSt6__ndk119__shared_weak_count16__release_sharedEv_02cb0d80)(lVar4);
      return;
    }
  }
  return;
}

// ==== Aska::TArray<std::__ndk1::shared_ptr<CMasterParameterRankElement>, false>::Resize(long, bool)
// vaddr 0x16de100 | ghidra 0x17de100 | size 508 | symbol _ZN4Aska6TArrayINSt6__ndk110shared_ptrI27CMasterParameterRankElementEELb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayINSt6__ndk110shared_ptrI27CMasterParameterRankElementEELb0EE6ResizeElb
               (long param_1,long param_2,ulong param_3)

{
  long *plVar1;
  long lVar2;
  undefined8 *puVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  
  if (param_2 == 0) {
    if ((*(long *)(param_1 + 8) != 0) && (lVar4 = *(long *)(param_1 + 0x18), 0 < lVar4)) {
      lVar5 = 1;
      lVar6 = 8;
      lVar2 = *(long *)(*(long *)(param_1 + 8) + 8);
      while( true ) {
        if (lVar2 != 0) {
          std::__ndk1::__shared_weak_count::__release_shared()();
          lVar4 = *(long *)(param_1 + 0x18);
        }
        if (lVar4 <= lVar5) break;
        lVar5 = lVar5 + 1;
        lVar6 = lVar6 + 0x10;
        lVar2 = *(long *)(*(long *)(param_1 + 8) + lVar6);
      }
    }
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar4 = *(long *)(param_1 + 0x10);
  if (lVar4 < param_2) {
    lVar4 = param_2 << 1;
    lVar5 = *(long *)(param_1 + 8);
  }
  else {
    lVar5 = lVar4 + 3;
    if (-1 < lVar4) {
      lVar5 = lVar4;
    }
    if (((lVar5 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar4 = param_2 * 2,
       lVar4 - *(long *)(param_1 + 0x28) == 0 || lVar4 < *(long *)(param_1 + 0x28))) {
      plVar1 = (long *)(param_1 + 0x18);
      if (((param_3 & 1) == 0) && (lVar4 = *plVar1, lVar4 < param_2)) {
        lVar5 = lVar4 << 4;
        lVar4 = param_2 - lVar4;
        do {
          lVar4 = lVar4 + -1;
          puVar3 = (undefined8 *)(*(long *)(param_1 + 8) + lVar5);
          lVar5 = lVar5 + 0x10;
          *puVar3 = 0;
          puVar3[1] = 0;
        } while (lVar4 != 0);
      }
      lVar4 = *plVar1;
      if (param_2 < lVar4) {
        uVar7 = param_2 << 4 | 8;
        lVar5 = param_2;
        do {
          if (*(long *)(*(long *)(param_1 + 8) + uVar7) != 0) {
            std::__ndk1::__shared_weak_count::__release_shared()();
            lVar4 = *plVar1;
          }
          lVar5 = lVar5 + 1;
          uVar7 = uVar7 + 0x10;
        } while (lVar5 < lVar4);
      }
      goto code_r0x017de2d8;
    }
    lVar5 = *(long *)(param_1 + 8);
  }
  if (lVar5 == 0) {
    lVar4 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar4 = param_2;
    }
    puVar3 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(lVar4 << 4,PTR__ZSt7nothrow_02cb9a80);
    *(undefined8 **)(param_1 + 8) = puVar3;
    if (puVar3 == (undefined8 *)0x0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    if ((0 < param_2) && ((param_3 & 1) == 0)) {
      lVar5 = param_2 + -1;
      *puVar3 = 0;
      puVar3[1] = 0;
      if (lVar5 != 0) {
        lVar6 = 0x10;
        do {
          lVar5 = lVar5 + -1;
          puVar3 = (undefined8 *)(*(long *)(param_1 + 8) + lVar6);
          lVar6 = lVar6 + 0x10;
          *puVar3 = 0;
          puVar3[1] = 0;
        } while (lVar5 != 0);
      }
    }
    *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) & 0xfffe;
  }
  else {
    Aska::TArray<std::__ndk1::shared_ptr<CMasterParameterRankElement>, false>::ForceRealloc(long, long, std::__ndk1::shared_ptr<CMasterParameterRankElement> const*, StBoolean<false>)(param_1,param_2,lVar4,0);
  }
  *(long *)(param_1 + 0x10) = lVar4;
code_r0x017de2d8:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TArrayIterator<Aska::TDynamicArray<Aska::TPair<unsigned char, unsigned int>, Aska::TAllocator<Aska::TPair<unsigned char, unsigned int> > > > Aska::TDynamicArray<Aska::TPair<unsigned char, unsigned int>, Aska::TAllocator<Aska::TPair<unsigned char, unsigned int> > >::Insert_<Aska::Memory::TConstruct1<Aska::TAllocator<Aska::TPair<unsigned char, unsigned int> >, unsigned char> >(Aska::TPair<unsigned char, unsigned int> const*, unsigned long, Aska::Memory::TConstruct1<Aska::TAllocator<Aska::TPair<unsigned char, unsigned int> >, unsigned char> const&)
// vaddr 0x16e540c | ghidra 0x17e540c | size 404 | symbol _ZN4Aska13TDynamicArrayINS_5TPairIhjEENS_10TAllocatorIS2_EEE7Insert_INS_6Memory11TConstruct1IS4_hEEEENS_14TArrayIteratorIS5_EEPKS2_mRKT_ | lib libSOA-3.7.0.so | 2026-10-04
undefined1 *
_ZN4Aska13TDynamicArrayINS_5TPairIhjEENS_10TAllocatorIS2_EEE7Insert_INS_6Memory11TConstruct1IS4_hEEEENS_14TArrayIteratorIS5_EEPKS2_mRKT_
          (long param_1,undefined1 *param_2,long param_3,long param_4)

{
  ulong uVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  ulong uVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  long lVar8;
  undefined1 *puVar9;
  
  if (param_3 != 0) {
    puVar4 = *(undefined1 **)(param_1 + 0x10);
    uVar1 = param_3 + ((long)puVar4 - *(long *)(param_1 + 8) >> 3);
    lVar8 = *(long *)(param_1 + 0x18) - *(long *)(param_1 + 8);
    if ((ulong)(lVar8 >> 3) < uVar1) {
      uVar5 = lVar8 >> 2;
      if (uVar1 <= uVar5) {
        uVar1 = uVar5;
      }
      if ((uVar1 >> 0x3d == 0) &&
         (puVar4 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(uVar1 << 3,4), puVar4 != (undefined1 *)0x0)) {
        puVar6 = *(undefined1 **)(param_1 + 8);
        puVar9 = puVar4;
        if (puVar6 != param_2) {
          lVar8 = 0;
          do {
            puVar9 = puVar6 + lVar8;
            puVar7 = puVar4 + lVar8;
            lVar8 = lVar8 + 8;
            *puVar7 = *puVar9;
            *(undefined4 *)(puVar7 + 4) = *(undefined4 *)(puVar9 + 4);
          } while (puVar9 + 8 != param_2);
          puVar9 = puVar4 + ((ulong)(param_2 + (-8 - (long)puVar6)) & 0xfffffffffffffff8) + 8;
        }
        puVar6 = puVar9 + param_3 * 8;
        *puVar9 = **(undefined1 **)(param_4 + 8);
        puVar7 = *(undefined1 **)(param_1 + 0x10);
        if (puVar7 != param_2) {
          lVar8 = 0;
          do {
            puVar2 = param_2 + lVar8;
            puVar3 = puVar6 + lVar8;
            lVar8 = lVar8 + 8;
            *puVar3 = *puVar2;
            *(undefined4 *)(puVar3 + 4) = *(undefined4 *)(puVar2 + 4);
          } while (puVar2 + 8 != puVar7);
          puVar6 = puVar6 + ((ulong)(puVar7 + (-8 - (long)param_2)) & 0xfffffffffffffff8) + 8;
        }
        Aska::MemoryManagerAdapter::AlignedFree(void*)(*(undefined8 *)(param_1 + 8));
        *(undefined1 **)(param_1 + 8) = puVar4;
        *(undefined1 **)(param_1 + 0x10) = puVar6;
        *(undefined1 **)(param_1 + 0x18) = puVar4 + uVar1 * 8;
        param_2 = puVar9;
      }
    }
    else {
      while (puVar4 != param_2) {
        puVar4[param_3 * 8 + -8] = puVar4[-8];
        *(undefined4 *)(puVar4 + param_3 * 8 + -4) = *(undefined4 *)(puVar4 + -4);
        puVar4 = puVar4 + -8;
      }
      *param_2 = **(undefined1 **)(param_4 + 8);
      *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + param_3 * 8;
    }
  }
  return param_2;
}

// ==== Aska::TArray<CGameResourceDownloader::tDownloadNodeInitializer, false>::Clear()
// vaddr 0x17dd284 | ghidra 0x18dd284 | size 188 | symbol _ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EE5ClearEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIN23CGameResourceDownloader24tDownloadNodeInitializerELb0EE5ClearEv
               (long param_1)

{
  long *plVar1;
  code *pcVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  
  lVar5 = *(long *)(param_1 + 8);
  if ((lVar5 != 0) && (0 < *(long *)(param_1 + 0x18))) {
    lVar3 = 0;
    lVar4 = 1;
    do {
      plVar1 = *(long **)(lVar5 + lVar3 + 0x40);
      if ((long *)(lVar5 + lVar3 + 0x20) == plVar1) {
        pcVar2 = *(code **)(*plVar1 + 0x20);
code_r0x018dd2ec:
        (*pcVar2)();
      }
      else if (plVar1 != (long *)0x0) {
        pcVar2 = *(code **)(*plVar1 + 0x28);
        goto code_r0x018dd2ec;
      }
      if ((*(byte *)(lVar5 + lVar3) & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(*(undefined8 *)(lVar5 + lVar3 + 0x10));
      }
      if (*(long *)(param_1 + 0x18) <= lVar4) break;
      lVar5 = *(long *)(param_1 + 8);
      lVar3 = lVar3 + 0x50;
      lVar4 = lVar4 + 1;
    } while( true );
  }
  if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
    if (*(long *)(param_1 + 8) != 0) {
      operator delete[](void*)();
      *(undefined8 *)(param_1 + 8) = 0;
    }
    *(undefined8 *)(param_1 + 0x10) = 0;
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  return;
}

// ==== Aska::TArray<CMetaInfo, false>::Resize(long, bool)
// vaddr 0x17e743c | ghidra 0x18e743c | size 604 | symbol _ZN4Aska6TArrayI9CMetaInfoLb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayI9CMetaInfoLb0EE6ResizeElb(long param_1,long param_2,ulong param_3)

{
  undefined *puVar1;
  long lVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  
  if (param_2 == 0) {
    if (((*(long **)(param_1 + 8) != (long *)0x0) && (0 < *(long *)(param_1 + 0x18))) &&
       ((**(code **)(**(long **)(param_1 + 8) + 0x10))(), 1 < *(long *)(param_1 + 0x18))) {
      lVar4 = 1;
      lVar5 = 0x28;
      do {
        (**(code **)(*(long *)(*(long *)(param_1 + 8) + lVar5) + 0x10))();
        lVar4 = lVar4 + 1;
        lVar5 = lVar5 + 0x28;
      } while (lVar4 < *(long *)(param_1 + 0x18));
    }
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar4 = *(long *)(param_1 + 0x10);
  if (lVar4 < param_2) {
    lVar4 = param_2 << 1;
    lVar5 = *(long *)(param_1 + 8);
  }
  else {
    lVar5 = lVar4 + 3;
    if (-1 < lVar4) {
      lVar5 = lVar4;
    }
    if (((lVar5 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar4 = param_2 * 2,
       lVar4 - *(long *)(param_1 + 0x28) == 0 || lVar4 < *(long *)(param_1 + 0x28))) {
      if (((param_3 & 1) == 0) && (lVar4 = *(long *)(param_1 + 0x18), lVar4 < param_2)) {
        lVar5 = param_2 - lVar4;
        lVar4 = lVar4 * 0x28;
        puVar1 = PTR__ZTV9CMetaInfo_02cc00d0 + 0x10;
        do {
          lVar5 = lVar5 + -1;
          plVar3 = (long *)(*(long *)(param_1 + 8) + lVar4);
          lVar4 = lVar4 + 0x28;
          *(undefined1 *)(plVar3 + 1) = 1;
          *plVar3 = (long)puVar1;
          plVar3[3] = 0;
          plVar3[4] = 0;
          plVar3[2] = 0;
        } while (lVar5 != 0);
      }
      if (param_2 < *(long *)(param_1 + 0x18)) {
        lVar5 = param_2 * 0x28;
        lVar4 = param_2;
        do {
          (**(code **)(*(long *)(*(long *)(param_1 + 8) + lVar5) + 0x10))();
          lVar4 = lVar4 + 1;
          lVar5 = lVar5 + 0x28;
        } while (lVar4 < *(long *)(param_1 + 0x18));
      }
      goto code_r0x018e7674;
    }
    lVar5 = *(long *)(param_1 + 8);
  }
  if (lVar5 == 0) {
    lVar4 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar4 = param_2;
    }
    plVar3 = (long *)operator new[](unsigned long, std::nothrow_t const&)(lVar4 * 0x28,PTR__ZSt7nothrow_02cb9a80);
    *(long **)(param_1 + 8) = plVar3;
    puVar1 = PTR__ZTV9CMetaInfo_02cc00d0;
    if (plVar3 == (long *)0x0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    if ((0 < param_2) && ((param_3 & 1) == 0)) {
      lVar5 = param_2 + -1;
      plVar3[3] = 0;
      plVar3[4] = 0;
      *(undefined1 *)(plVar3 + 1) = 1;
      *plVar3 = (long)(puVar1 + 0x10);
      plVar3[2] = 0;
      if (lVar5 != 0) {
        lVar6 = 0;
        do {
          lVar5 = lVar5 + -1;
          lVar2 = *(long *)(param_1 + 8) + lVar6;
          lVar6 = lVar6 + 0x28;
          *(undefined1 *)(lVar2 + 0x30) = 1;
          *(undefined **)(lVar2 + 0x28) = puVar1 + 0x10;
          *(undefined8 *)(lVar2 + 0x40) = 0;
          *(undefined8 *)(lVar2 + 0x48) = 0;
          *(undefined8 *)(lVar2 + 0x38) = 0;
        } while (lVar5 != 0);
      }
    }
    *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) & 0xfffe;
  }
  else {
    Aska::TArray<CMetaInfo, false>::ForceRealloc(long, long, CMetaInfo const*, StBoolean<false>)(param_1,param_2,lVar4,0);
  }
  *(long *)(param_1 + 0x10) = lVar4;
code_r0x018e7674:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TArray<CGameResourceDownloader::CDownloadNode*, false>::Resize(long, bool)
// vaddr 0x17e944c | ghidra 0x18e944c | size 252 | symbol _ZN4Aska6TArrayIPN23CGameResourceDownloader13CDownloadNodeELb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIPN23CGameResourceDownloader13CDownloadNodeELb0EE6ResizeElb
               (long param_1,long param_2)

{
  long lVar1;
  ushort uVar2;
  long lVar3;
  
  if (param_2 == 0) {
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar3 = *(long *)(param_1 + 0x10);
  if (lVar3 < param_2) {
    lVar3 = param_2 << 1;
  }
  else {
    lVar1 = lVar3 + 3;
    if (-1 < lVar3) {
      lVar1 = lVar3;
    }
    if (((lVar1 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar3 = param_2 * 2,
       lVar3 - *(long *)(param_1 + 0x28) == 0 || lVar3 < *(long *)(param_1 + 0x28)))
    goto code_r0x018e952c;
  }
  if (*(long *)(param_1 + 8) == 0) {
    lVar3 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar3 = param_2;
    }
    lVar1 = operator new[](unsigned long, std::nothrow_t const&)(lVar3 << 3,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar1;
    if (lVar1 == 0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    uVar2 = *(ushort *)(param_1 + 0x30) & 0xfffe;
code_r0x018e9524:
    *(ushort *)(param_1 + 0x30) = uVar2;
  }
  else {
    lVar1 = operator new[](unsigned long, void*, unsigned long)(param_2 << 4,*(long *)(param_1 + 8),4);
    if (lVar1 == 0) {
      uVar2 = *(ushort *)(param_1 + 0x30) | 1;
      goto code_r0x018e9524;
    }
    *(long *)(param_1 + 8) = lVar1;
    *(long *)(param_1 + 0x10) = lVar3;
    *(long *)(param_1 + 0x18) = param_2;
  }
  *(long *)(param_1 + 0x10) = lVar3;
code_r0x018e952c:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TArray<CMetaInfo, false>::SetAt(long, CMetaInfo const&)
// vaddr 0x17f5acc | ghidra 0x18f5acc | size 836 | symbol _ZN4Aska6TArrayI9CMetaInfoLb0EE5SetAtElRKS1_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x018f5db8: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x018f5dbc) */

void _ZN4Aska6TArrayI9CMetaInfoLb0EE5SetAtElRKS1_(long param_1,long param_2,long param_3)

{
  undefined8 uVar1;
  undefined1 uVar2;
  undefined **ppuVar3;
  ulong uVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  long lVar8;
  undefined *puVar9;
  undefined **ppuVar10;
  undefined *puVar11;
  long lVar12;
  long lVar13;
  undefined *puStack_78;
  undefined1 uStack_70;
  undefined8 uStack_68;
  ulong uStack_60;
  long lStack_58;
  
  puVar9 = PTR__ZTV9CMetaInfo_02cc00d0;
  if (param_2 < 0) {
    return;
  }
  if (param_2 < *(long *)(param_1 + 0x18)) {
    lVar13 = *(long *)(param_1 + 8);
    lVar8 = lVar13 + param_2 * 0x28;
    *(undefined1 *)(lVar8 + 8) = *(undefined1 *)(param_3 + 8);
    if (lVar8 == param_3) {
      return;
    }
    ppuVar3 = (undefined **)(lVar8 + 0x10);
    uVar7 = *(ulong *)(param_3 + 0x18);
    lVar12 = *(long *)(param_3 + 0x20);
    puVar9 = (undefined *)(ulong)*(byte *)ppuVar3;
    if ((*(byte *)(param_3 + 0x10) & 1) == 0) {
      lVar12 = param_3 + 0x11;
      uVar7 = (ulong)(*(byte *)(param_3 + 0x10) >> 1);
    }
    if ((*(byte *)ppuVar3 & 1) == 0) {
      uVar4 = 0x16;
      lVar5 = uVar7 - 0x16;
      if (uVar7 < 0x16 || lVar5 == 0) {
code_r0x018f5b4c:
        if (((ulong)puVar9 & 1) == 0) {
          lVar8 = lVar8 + 0x11;
        }
        else {
          lVar8 = *(long *)(lVar13 + param_2 * 0x28 + 0x20);
        }
        if (uVar7 != 0) {
          memmove(lVar8,lVar12,uVar7);
        }
        *(undefined1 *)(lVar8 + uVar7) = 0;
        if ((*(byte *)ppuVar3 & 1) == 0) {
          *(byte *)ppuVar3 = (byte)(uVar7 << 1);
          return;
        }
        *(ulong *)(lVar13 + param_2 * 0x28 + 0x18) = uVar7;
        return;
      }
    }
    else {
      puVar9 = *ppuVar3;
      uVar4 = ((ulong)puVar9 & 0xfffffffffffffffe) - 1;
      lVar5 = uVar7 - uVar4;
      if (uVar7 < uVar4 || lVar5 == 0) goto code_r0x018f5b4c;
    }
    if (((ulong)puVar9 & 1) == 0) {
      uVar6 = (ulong)(((uint)puVar9 & 0xfe) >> 1);
    }
    else {
      uVar6 = *(ulong *)(lVar13 + param_2 * 0x28 + 0x18);
    }
    goto code_r0x011ddaa0;
  }
  uStack_70 = *(undefined1 *)(param_3 + 8);
  uStack_60 = 0;
  lStack_58 = 0;
  uStack_68 = 0;
  puStack_78 = PTR__ZTV9CMetaInfo_02cc00d0 + 0x10;
  if ((*(byte *)(param_3 + 0x10) & 1) == 0) {
    lStack_58 = *(long *)(param_3 + 0x20);
    uStack_60 = *(ulong *)(param_3 + 0x18);
    uStack_68 = *(ulong *)(param_3 + 0x10);
  }
  else {
    uVar7 = *(ulong *)(param_3 + 0x18);
    uVar1 = *(undefined8 *)(param_3 + 0x20);
    if (uVar7 < 0x17) {
      lVar8 = (long)&uStack_68 + 1;
      uStack_68 = (uVar7 & 0x7f) << 1;
      if (uVar7 != 0) goto code_r0x018f5c4c;
    }
    else {
      uVar4 = uVar7 + 0x10 & 0xfffffffffffffff0;
      if (uVar4 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
      }
      lVar8 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar4,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
      if (lVar8 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
      }
      uStack_68 = uVar4 | 1;
      uStack_60 = uVar7;
      lStack_58 = lVar8;
code_r0x018f5c4c:
      memcpy(lVar8,uVar1,uVar7);
    }
    *(undefined1 *)(lVar8 + uVar7) = 0;
  }
  uVar2 = uStack_70;
  Aska::TArray<CMetaInfo, false>::Resize(long, bool)(param_1,param_2 + 1,0);
  lVar8 = *(long *)(param_1 + 8);
  ppuVar10 = (undefined **)(lVar8 + param_2 * 0x28);
  *(undefined1 *)(ppuVar10 + 1) = uVar2;
  if (ppuVar10 == &puStack_78) goto code_r0x018f5ddc;
  ppuVar3 = ppuVar10 + 2;
  puVar11 = (undefined *)(ulong)*(byte *)ppuVar3;
  uVar7 = uStack_60;
  lVar13 = lStack_58;
  if ((uStack_68 & 1) == 0) {
    uVar7 = uStack_68 >> 1 & 0x7f;
    lVar13 = (long)&uStack_68 + 1;
  }
  if ((*(byte *)ppuVar3 & 1) == 0) {
    uVar4 = 0x16;
    lVar5 = uVar7 - 0x16;
    if (0x15 < uVar7 && lVar5 != 0) {
code_r0x018f5ce4:
      if (((ulong)puVar11 & 1) == 0) {
        uVar6 = (ulong)(((uint)puVar11 & 0xfe) >> 1);
      }
      else {
        uVar6 = *(ulong *)(lVar8 + param_2 * 0x28 + 0x18);
      }
code_r0x011ddaa0:
      (*(code *)
        PTR__ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE21__grow_by_and_replaceEmmmmmmPKc_02ca6d40
      )(ppuVar3,uVar4,lVar5,uVar6,0,uVar6,uVar7);
      return;
    }
  }
  else {
    puVar11 = *ppuVar3;
    uVar4 = ((ulong)puVar11 & 0xfffffffffffffffe) - 1;
    lVar5 = uVar7 - uVar4;
    if (uVar4 <= uVar7 && lVar5 != 0) goto code_r0x018f5ce4;
  }
  if (((ulong)puVar11 & 1) == 0) {
    lVar12 = (long)ppuVar10 + 0x11;
  }
  else {
    lVar12 = *(long *)(lVar8 + param_2 * 0x28 + 0x20);
  }
  if (uVar7 != 0) {
    memmove(lVar12,lVar13,uVar7);
  }
  *(undefined1 *)(lVar12 + uVar7) = 0;
  if (((ulong)*ppuVar3 & 1) == 0) {
    *(byte *)ppuVar3 = (byte)(uVar7 << 1);
  }
  else {
    *(ulong *)(lVar8 + param_2 * 0x28 + 0x18) = uVar7;
  }
code_r0x018f5ddc:
  puStack_78 = puVar9 + 0x10;
  if ((uStack_68 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(lStack_58);
  }
  return;
}

// ==== Aska::TArray<CGameResourceDownloader::CJournalFileWriter::tWriteInfo, false>::Resize(long, bool)
// vaddr 0x17f6c88 | ghidra 0x18f6c88 | size 348 | symbol _ZN4Aska6TArrayIN23CGameResourceDownloader18CJournalFileWriter10tWriteInfoELb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIN23CGameResourceDownloader18CJournalFileWriter10tWriteInfoELb0EE6ResizeElb
               (long param_1,long param_2)

{
  long lVar1;
  ushort uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  
  if (param_2 == 0) {
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar3 = *(long *)(param_1 + 0x10);
  if (lVar3 < param_2) {
    lVar3 = param_2 << 1;
  }
  else {
    lVar4 = lVar3 + 3;
    if (-1 < lVar3) {
      lVar4 = lVar3;
    }
    if (((lVar4 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar3 = param_2 * 2,
       lVar3 - *(long *)(param_1 + 0x28) == 0 || lVar3 < *(long *)(param_1 + 0x28)))
    goto code_r0x018f6dc0;
  }
  lVar4 = *(long *)(param_1 + 8);
  if (lVar4 == 0) {
    lVar3 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar3 = param_2;
    }
    lVar4 = operator new[](unsigned long, std::nothrow_t const&)(lVar3 * 0x168,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar4;
    if (lVar4 == 0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    uVar2 = *(ushort *)(param_1 + 0x30) & 0xfffe;
code_r0x018f6db8:
    *(ushort *)(param_1 + 0x30) = uVar2;
  }
  else {
    lVar1 = operator new[](unsigned long, std::nothrow_t const&)(param_2 * 0x2d0,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar1;
    if (lVar1 == 0) {
      uVar2 = *(ushort *)(param_1 + 0x30) | 1;
      goto code_r0x018f6db8;
    }
    lVar6 = param_2;
    if (*(long *)(param_1 + 0x18) <= param_2) {
      lVar6 = *(long *)(param_1 + 0x18);
    }
    lVar5 = lVar4;
    if (0 < lVar6) {
      do {
        memcpy(lVar1,lVar5,0x168);
        lVar6 = lVar6 + -1;
        lVar1 = lVar1 + 0x168;
        lVar5 = lVar5 + 0x168;
      } while (lVar6 != 0);
    }
    operator delete[](void*)(lVar4);
    *(long *)(param_1 + 0x10) = lVar3;
    *(long *)(param_1 + 0x18) = param_2;
  }
  *(long *)(param_1 + 0x10) = lVar3;
code_r0x018f6dc0:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== FUN_01f13114
// vaddr 0x1e13114 | ghidra 0x1f13114 | size 0 | symbol FUN_01f13114 | lib libSOA-3.7.0.so | 2026-10-04
void FUN_01f13114(undefined8 param_1,undefined8 *param_2)

{
  *param_2 = &UNK_02ba0ba8;
  return;
}

// ==== FUN_01f13128
// vaddr 0x1e13128 | ghidra 0x1f13128 | size 0 | symbol FUN_01f13128 | lib libSOA-3.7.0.so | 2026-10-04
void FUN_01f13128(void)

{
  return;
}

// ==== FUN_01f13130
// vaddr 0x1e13130 | ghidra 0x1f13130 | size 0 | symbol FUN_01f13130 | lib libSOA-3.7.0.so | 2026-10-04
void FUN_01f13130(void)

{
  undefined1 auStack_8 [8];
  
  (**(code **)(**(long **)PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278 + 0x460
              ))(auStack_8);
  return;
}

// ==== FUN_01f131b4
// vaddr 0x1e131b4 | ghidra 0x1f131b4 | size 0 | symbol FUN_01f131b4 | lib libSOA-3.7.0.so | 2026-10-04
void FUN_01f131b4(long param_1,undefined8 *param_2)

{
  *param_2 = &UNK_02ba0c28;
  param_2[1] = *(undefined8 *)(param_1 + 8);
  return;
}

// ==== FUN_01f131d0
// vaddr 0x1e131d0 | ghidra 0x1f131d0 | size 0 | symbol FUN_01f131d0 | lib libSOA-3.7.0.so | 2026-10-04
void FUN_01f131d0(void)

{
  return;
}

// ==== FUN_01f131d8
// vaddr 0x1e131d8 | ghidra 0x1f131d8 | size 0 | symbol FUN_01f131d8 | lib libSOA-3.7.0.so | 2026-10-04
void FUN_01f131d8(long param_1,char *param_2,long *param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 8);
  uVar2 = 3;
  if (*param_3 != 0x3ea && *param_2 == '\0') {
    uVar2 = 0;
  }
  *puVar1 = uVar2;
  puVar1[1] = 0;
  return;
}

// ==== Aska::TArray<Framework::CAnimationBlendContainer::_tBlendMotionData, false>::Resize(long, bool)
// vaddr 0x1e5e220 | ghidra 0x1f5e220 | size 312 | symbol _ZN4Aska6TArrayIN9Framework24CAnimationBlendContainer17_tBlendMotionDataELb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIN9Framework24CAnimationBlendContainer17_tBlendMotionDataELb0EE6ResizeElb
               (long param_1,long param_2)

{
  undefined8 *puVar1;
  ushort uVar2;
  long lVar3;
  long lVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  undefined8 uVar7;
  
  if (param_2 == 0) {
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar3 = *(long *)(param_1 + 0x10);
  if (lVar3 < param_2) {
    lVar3 = param_2 << 1;
  }
  else {
    lVar4 = lVar3 + 3;
    if (-1 < lVar3) {
      lVar4 = lVar3;
    }
    if (((lVar4 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar3 = param_2 * 2,
       lVar3 - *(long *)(param_1 + 0x28) == 0 || lVar3 < *(long *)(param_1 + 0x28)))
    goto code_r0x01f5e338;
  }
  puVar6 = *(undefined8 **)(param_1 + 8);
  if (puVar6 == (undefined8 *)0x0) {
    lVar3 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar3 = param_2;
    }
    lVar4 = operator new[](unsigned long, std::nothrow_t const&)(lVar3 << 4,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar4;
    if (lVar4 == 0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    uVar2 = *(ushort *)(param_1 + 0x30) & 0xfffe;
code_r0x01f5e330:
    *(ushort *)(param_1 + 0x30) = uVar2;
  }
  else {
    puVar1 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(param_2 << 5,PTR__ZSt7nothrow_02cb9a80);
    *(undefined8 **)(param_1 + 8) = puVar1;
    if (puVar1 == (undefined8 *)0x0) {
      uVar2 = *(ushort *)(param_1 + 0x30) | 1;
      goto code_r0x01f5e330;
    }
    lVar4 = param_2;
    if (*(long *)(param_1 + 0x18) <= param_2) {
      lVar4 = *(long *)(param_1 + 0x18);
    }
    puVar5 = puVar6;
    if (0 < lVar4) {
      do {
        uVar7 = *puVar5;
        lVar4 = lVar4 + -1;
        puVar1[1] = puVar5[1];
        *puVar1 = uVar7;
        puVar1 = puVar1 + 2;
        puVar5 = puVar5 + 2;
      } while (lVar4 != 0);
    }
    operator delete[](void*)(puVar6);
    *(long *)(param_1 + 0x10) = lVar3;
    *(long *)(param_1 + 0x18) = param_2;
  }
  *(long *)(param_1 + 0x10) = lVar3;
code_r0x01f5e338:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TArrayIterator<Aska::TDynamicArray<Framework::Cocos::Blending::tRenderResult::tRenderState*, Aska::TAllocator<Framework::Cocos::Blending::tRenderResult::tRenderState*> > > Aska::TDynamicArray<Framework::Cocos::Blending::tRenderResult::tRenderState*, Aska::TAllocator<Framework::Cocos::Blending::tRenderResult::tRenderState*> >::Insert_<Aska::Memory::TUninitializedFillN<Framework::Cocos::Blending::tRenderResult::tRenderState*> >(Framework::Cocos::Blending::tRenderResult::tRenderState* const*, unsigned long, Aska::Memory::TUninitializedFillN<Framework::Cocos::Blending::tRenderResult::tRenderState*> const&)
// vaddr 0x1ec69d8 | ghidra 0x1fc69d8 | size 872 | symbol _ZN4Aska13TDynamicArrayIPN9Framework5Cocos8Blending13tRenderResult12tRenderStateENS_10TAllocatorIS6_EEE7Insert_INS_6Memory19TUninitializedFillNIS6_EEEENS_14TArrayIteratorIS9_EEPKS6_mRKT_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 *
_ZN4Aska13TDynamicArrayIPN9Framework5Cocos8Blending13tRenderResult12tRenderStateENS_10TAllocatorIS6_EEE7Insert_INS_6Memory19TUninitializedFillNIS6_EEEENS_14TArrayIteratorIS9_EEPKS6_mRKT_
          (long param_1,undefined8 *param_2,long param_3,ulong *param_4)

{
  undefined8 *puVar1;
  bool bVar2;
  undefined8 *puVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  long lVar9;
  undefined8 *puVar10;
  ulong uVar11;
  undefined8 *puVar12;
  ulong uVar13;
  undefined8 *puVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  
  if (param_3 == 0) {
    return param_2;
  }
  puVar3 = *(undefined8 **)(param_1 + 0x10);
  uVar6 = param_3 + ((long)puVar3 - *(long *)(param_1 + 8) >> 3);
  lVar9 = *(long *)(param_1 + 0x18) - *(long *)(param_1 + 8);
  if (uVar6 <= (ulong)(lVar9 >> 3)) {
    while (puVar3 != param_2) {
      puVar3[param_3 + -1] = puVar3[-1];
      puVar3 = puVar3 + -1;
    }
    uVar6 = *param_4;
    if (uVar6 != 0) {
      puVar7 = (undefined8 *)param_4[1];
      puVar3 = param_2;
      if (((3 < uVar6) && (uVar4 = uVar6 & 0xfffffffffffffffc, uVar4 != 0)) &&
         (((undefined8 *)((long)puVar7 + 1U) <= param_2 || (param_2 + uVar6 <= puVar7)))) {
        uVar15 = *puVar7;
        puVar3 = param_2 + 2;
        uVar5 = uVar4;
        do {
          puVar3[-1] = uVar15;
          puVar3[-2] = uVar15;
          puVar3[1] = uVar15;
          *puVar3 = uVar15;
          uVar5 = uVar5 - 4;
          puVar3 = puVar3 + 4;
        } while (uVar5 != 0);
        bVar2 = uVar6 == uVar4;
        uVar6 = uVar6 - uVar4;
        puVar3 = param_2 + uVar4;
        if (bVar2) goto code_r0x01fc6b24;
      }
      do {
        uVar6 = uVar6 - 1;
        *puVar3 = *puVar7;
        puVar3 = puVar3 + 1;
      } while (uVar6 != 0);
    }
code_r0x01fc6b24:
    *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + param_3 * 8;
    return param_2;
  }
  uVar4 = lVar9 >> 2;
  if (uVar6 <= uVar4) {
    uVar6 = uVar4;
  }
  if (uVar6 >> 0x3d != 0) {
    return param_2;
  }
  puVar3 = (undefined8 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(uVar6 << 3,8);
  if (puVar3 == (undefined8 *)0x0) {
    return param_2;
  }
  puVar7 = *(undefined8 **)(param_1 + 8);
  if (puVar7 == param_2) {
    uVar4 = *param_4;
    puVar7 = puVar3;
  }
  else {
    uVar5 = (long)param_2 + (-8 - (long)puVar7);
    uVar4 = (uVar5 >> 3) + 1;
    puVar10 = puVar3;
    if (((uVar4 < 4) || (uVar11 = uVar4 & 0x3ffffffffffffffc, uVar11 == 0)) ||
       ((puVar3 < (undefined8 *)((long)puVar7 + (uVar5 & 0xfffffffffffffff8) + 8) &&
        (puVar7 < (undefined8 *)((long)puVar3 + (uVar5 + 8 & 0xfffffffffffffff8)))))) {
code_r0x01fc6ba8:
      do {
        puVar8 = puVar7 + 1;
        *puVar10 = *puVar7;
        puVar7 = puVar8;
        puVar10 = puVar10 + 1;
      } while (param_2 != puVar8);
    }
    else {
      puVar10 = puVar7 + 2;
      puVar7 = puVar7 + uVar11;
      puVar8 = puVar3 + 2;
      uVar13 = uVar11;
      do {
        puVar12 = puVar10 + -1;
        uVar15 = puVar10[-2];
        uVar17 = puVar10[1];
        uVar16 = *puVar10;
        puVar10 = puVar10 + 4;
        uVar13 = uVar13 - 4;
        puVar8[-1] = *puVar12;
        puVar8[-2] = uVar15;
        puVar8[1] = uVar17;
        *puVar8 = uVar16;
        puVar8 = puVar8 + 4;
      } while (uVar13 != 0);
      puVar10 = puVar3 + uVar11;
      if (uVar4 != uVar11) goto code_r0x01fc6ba8;
    }
    puVar7 = (undefined8 *)((long)puVar3 + (uVar5 & 0xfffffffffffffff8) + 8);
    uVar4 = *param_4;
  }
  if (uVar4 != 0) {
    puVar8 = (undefined8 *)param_4[1];
    puVar10 = puVar7;
    if (((3 < uVar4) && (uVar5 = uVar4 & 0xfffffffffffffffc, uVar5 != 0)) &&
       (((undefined8 *)((long)puVar8 + 1U) <= puVar7 || (puVar7 + uVar4 <= puVar8)))) {
      uVar15 = *puVar8;
      puVar10 = puVar7 + 2;
      uVar11 = uVar5;
      do {
        puVar10[-1] = uVar15;
        puVar10[-2] = uVar15;
        puVar10[1] = uVar15;
        *puVar10 = uVar15;
        uVar11 = uVar11 - 4;
        puVar10 = puVar10 + 4;
      } while (uVar11 != 0);
      bVar2 = uVar4 == uVar5;
      uVar4 = uVar4 - uVar5;
      puVar10 = puVar7 + uVar5;
      if (bVar2) goto code_r0x01fc6c4c;
    }
    do {
      uVar4 = uVar4 - 1;
      *puVar10 = *puVar8;
      puVar10 = puVar10 + 1;
    } while (uVar4 != 0);
  }
code_r0x01fc6c4c:
  puVar8 = *(undefined8 **)(param_1 + 0x10);
  puVar10 = puVar7 + param_3;
  if (puVar8 == param_2) goto code_r0x01fc6d10;
  uVar5 = (long)puVar8 + (-8 - (long)param_2);
  uVar11 = uVar5 >> 3;
  uVar4 = uVar11 + 1;
  puVar12 = puVar10;
  if (((uVar4 < 4) || (uVar13 = uVar4 & 0x3ffffffffffffffc, uVar13 == 0)) ||
     ((puVar10 < param_2 + uVar11 + 1 && (param_2 < puVar7 + uVar11 + param_3 + 1)))) {
code_r0x01fc6cf4:
    do {
      puVar14 = param_2 + 1;
      *puVar12 = *param_2;
      puVar12 = puVar12 + 1;
      param_2 = puVar14;
    } while (puVar8 != puVar14);
  }
  else {
    puVar12 = param_2 + 2;
    param_2 = param_2 + uVar13;
    puVar14 = puVar7 + param_3 + 2;
    uVar11 = uVar13;
    do {
      puVar1 = puVar12 + -1;
      uVar15 = puVar12[-2];
      uVar17 = puVar12[1];
      uVar16 = *puVar12;
      puVar12 = puVar12 + 4;
      uVar11 = uVar11 - 4;
      puVar14[-1] = *puVar1;
      puVar14[-2] = uVar15;
      puVar14[1] = uVar17;
      *puVar14 = uVar16;
      puVar14 = puVar14 + 4;
    } while (uVar11 != 0);
    puVar12 = puVar10 + uVar13;
    if (uVar4 != uVar13) goto code_r0x01fc6cf4;
  }
  puVar10 = (undefined8 *)((long)puVar10 + (uVar5 & 0xfffffffffffffff8) + 8);
code_r0x01fc6d10:
  Aska::MemoryManagerAdapter::AlignedFree(void*)(*(undefined8 *)(param_1 + 8));
  *(undefined8 **)(param_1 + 8) = puVar3;
  *(undefined8 **)(param_1 + 0x10) = puVar10;
  *(undefined8 **)(param_1 + 0x18) = puVar3 + uVar6;
  return puVar7;
}

// ==== Aska::TArrayIterator<Aska::TDynamicArray<Aska::ASON::WorkBufferContext, Aska::TAllocator<Aska::ASON::WorkBufferContext> > > Aska::TDynamicArray<Aska::ASON::WorkBufferContext, Aska::TAllocator<Aska::ASON::WorkBufferContext> >::Insert_<Aska::Memory::TUninitializedFillN<Aska::ASON::WorkBufferContext> >(Aska::ASON::WorkBufferContext const*, unsigned long, Aska::Memory::TUninitializedFillN<Aska::ASON::WorkBufferContext> const&)
// vaddr 0x1f13f9c | ghidra 0x2013f9c | size 468 | symbol _ZN4Aska13TDynamicArrayINS_4ASON17WorkBufferContextENS_10TAllocatorIS2_EEE7Insert_INS_6Memory19TUninitializedFillNIS2_EEEENS_14TArrayIteratorIS5_EEPKS2_mRKT_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 *
_ZN4Aska13TDynamicArrayINS_4ASON17WorkBufferContextENS_10TAllocatorIS2_EEE7Insert_INS_6Memory19TUninitializedFillNIS2_EEEENS_14TArrayIteratorIS5_EEPKS2_mRKT_
          (long param_1,undefined8 *param_2,long param_3,long *param_4)

{
  ulong uVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  ulong uVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  long lVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  
  if (param_3 != 0) {
    puVar4 = *(undefined8 **)(param_1 + 0x10);
    uVar1 = param_3 + ((long)puVar4 - *(long *)(param_1 + 8) >> 5);
    lVar8 = *(long *)(param_1 + 0x18) - *(long *)(param_1 + 8);
    if ((ulong)(lVar8 >> 5) < uVar1) {
      uVar5 = lVar8 >> 4;
      if (uVar1 <= uVar5) {
        uVar1 = uVar5;
      }
      if ((uVar1 >> 0x3b == 0) &&
         (puVar4 = (undefined8 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(uVar1 << 5,8), puVar4 != (undefined8 *)0x0)) {
        puVar6 = *(undefined8 **)(param_1 + 8);
        if (puVar6 == param_2) {
          lVar8 = *param_4;
          puVar6 = puVar4;
        }
        else {
          lVar8 = 0;
          do {
            puVar9 = (undefined8 *)((long)puVar6 + lVar8);
            uVar10 = puVar9[2];
            puVar7 = (undefined8 *)((long)puVar4 + lVar8);
            lVar8 = lVar8 + 0x20;
            puVar7[3] = puVar9[3];
            puVar7[2] = uVar10;
            uVar10 = *puVar9;
            puVar7[1] = puVar9[1];
            *puVar7 = uVar10;
          } while ((long)param_2 - (long)puVar6 != lVar8);
          puVar6 = (undefined8 *)
                   ((long)puVar4 +
                   ((long)param_2 + (-0x20 - (long)puVar6) & 0xffffffffffffffe0U) + 0x20);
          lVar8 = *param_4;
        }
        if (lVar8 != 0) {
          puVar7 = (undefined8 *)param_4[1];
          puVar9 = puVar6;
          do {
            uVar10 = puVar7[2];
            lVar8 = lVar8 + -1;
            puVar9[3] = puVar7[3];
            puVar9[2] = uVar10;
            uVar10 = *puVar7;
            puVar9[1] = puVar7[1];
            *puVar9 = uVar10;
            puVar9 = puVar9 + 4;
          } while (lVar8 != 0);
        }
        puVar7 = *(undefined8 **)(param_1 + 0x10);
        puVar9 = puVar6 + param_3 * 4;
        if (puVar7 != param_2) {
          lVar8 = 0;
          do {
            puVar2 = (undefined8 *)((long)param_2 + lVar8);
            uVar10 = puVar2[2];
            puVar3 = (undefined8 *)((long)puVar9 + lVar8);
            lVar8 = lVar8 + 0x20;
            puVar3[3] = puVar2[3];
            puVar3[2] = uVar10;
            uVar10 = *puVar2;
            puVar3[1] = puVar2[1];
            *puVar3 = uVar10;
          } while ((long)puVar7 - (long)param_2 != lVar8);
          puVar9 = (undefined8 *)
                   ((long)puVar9 +
                   ((long)puVar7 + (-0x20 - (long)param_2) & 0xffffffffffffffe0U) + 0x20);
        }
        Aska::MemoryManagerAdapter::AlignedFree(void*)(*(undefined8 *)(param_1 + 8));
        *(undefined8 **)(param_1 + 8) = puVar4;
        *(undefined8 **)(param_1 + 0x10) = puVar9;
        *(undefined8 **)(param_1 + 0x18) = puVar4 + uVar1 * 4;
        param_2 = puVar6;
      }
    }
    else {
      if (puVar4 != param_2) {
        puVar4 = puVar4 + -4;
        do {
          uVar10 = puVar4[2];
          puVar6 = puVar4 + param_3 * 4;
          puVar6[3] = puVar4[3];
          puVar6[2] = uVar10;
          puVar9 = puVar4 + -4;
          uVar10 = *puVar4;
          puVar6[1] = puVar4[1];
          *puVar6 = uVar10;
          puVar4 = puVar9;
        } while ((long)puVar9 - (long)param_2 != -0x20);
      }
      lVar8 = *param_4;
      if (lVar8 != 0) {
        puVar6 = (undefined8 *)param_4[1];
        puVar4 = param_2;
        do {
          uVar10 = puVar6[2];
          lVar8 = lVar8 + -1;
          puVar4[3] = puVar6[3];
          puVar4[2] = uVar10;
          uVar10 = *puVar6;
          puVar4[1] = puVar6[1];
          *puVar4 = uVar10;
          puVar4 = puVar4 + 4;
        } while (lVar8 != 0);
      }
      *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + param_3 * 0x20;
    }
  }
  return param_2;
}

// ==== Aska::TList<Aska::ReadRequest>::AddTop(Aska::ReadRequest*)
// vaddr 0x1f213e4 | ghidra 0x20213e4 | size 36 | symbol _ZN4Aska5TListINS_11ReadRequestEE6AddTopEPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TListINS_11ReadRequestEE6AddTopEPS1_(long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x18);
  *(long *)(param_2 + 8) = param_1 + 8;
  *(long *)(param_2 + 0x10) = lVar1;
  *(long *)(lVar1 + 8) = param_2;
  *(long *)(param_1 + 0x18) = param_2;
  *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + 1;
  return;
}

// ==== Aska::TList<Aska::ReadRequest>::Insert(Aska::ReadRequest*, Aska::ReadRequest*)
// vaddr 0x1f21408 | ghidra 0x2021408 | size 32 | symbol _ZN4Aska5TListINS_11ReadRequestEE6InsertEPS1_S3_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TListINS_11ReadRequestEE6InsertEPS1_S3_(long param_1,long param_2,long param_3)

{
  long lVar1;
  
  lVar1 = *(long *)(param_2 + 0x10);
  *(long *)(param_3 + 8) = param_2;
  *(long *)(param_3 + 0x10) = lVar1;
  *(long *)(lVar1 + 8) = param_3;
  *(long *)(param_2 + 0x10) = param_3;
  *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + 1;
  return;
}

// ==== Aska::TPriorityQueue<Aska::MappingQueue::EventItem, true>::Acquire(Aska::MappingQueue::EventItem*, unsigned long, unsigned long*)
// vaddr 0x1f37d18 | ghidra 0x2037d18 | size 492 | symbol _ZN4Aska14TPriorityQueueINS_12MappingQueue9EventItemELb1EE7AcquireEPS2_mPm | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska14TPriorityQueueINS_12MappingQueue9EventItemELb1EE7AcquireEPS2_mPm
          (long param_1,long *param_2,ulong param_3,undefined8 *param_4)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  undefined4 uVar5;
  long *plVar6;
  ulong uVar7;
  
  lVar1 = param_1 + 8;
  Aska::CriticalSection::Enter() const(lVar1);
  Aska::CriticalSection::Enter() const(lVar1);
  if ((*(int *)(param_1 + 0x80) < 1) || (plVar6 = *(long **)(param_1 + 0x48), plVar6 == (long *)0x0)
     ) {
code_r0x02037da0:
    Aska::CriticalSection::Leave() const(lVar1);
code_r0x02037da8:
    if (param_4 == (undefined8 *)0x0) {
      uVar5 = 0;
    }
    else {
      uVar5 = 0;
      *param_4 = 0;
    }
  }
  else {
    if ((plVar6[3] == 0) || ((plVar6[3] & param_3) != 0)) {
      Aska::CriticalSection::Leave() const(lVar1);
    }
    else {
      do {
        if ((long *)(param_1 + 0x38) == plVar6) goto code_r0x02037da0;
        plVar6 = (long *)plVar6[2];
      } while ((plVar6[3] != 0) && ((plVar6[3] & param_3) == 0));
      Aska::CriticalSection::Leave() const(lVar1);
      if (plVar6 == (long *)0x0) goto code_r0x02037da8;
    }
    if (plVar6 + 5 != param_2) {
      *param_2 = plVar6[5];
      param_2[1] = plVar6[6];
      param_2[2] = plVar6[7];
      param_2[3] = plVar6[8];
    }
    if (param_4 != (undefined8 *)0x0) {
      *param_4 = plVar6;
    }
    if ((long *)(param_1 + 0x38) != plVar6) {
      lVar3 = plVar6[1];
      lVar4 = plVar6[2];
      if (lVar3 != 0) {
        *(long *)(lVar3 + 0x10) = lVar4;
      }
      if (lVar4 != 0) {
        *(long *)(lVar4 + 8) = lVar3;
      }
      if (0 < *(int *)(param_1 + 0x80)) {
        *(int *)(param_1 + 0x80) = *(int *)(param_1 + 0x80) + -1;
      }
      plVar6[1] = 0;
      plVar6[2] = 0;
    }
    Aska::CriticalSection::Enter() const(lVar1);
    plVar2 = *(long **)(param_1 + 200);
    if (((plVar2 == (long *)0x0) || (plVar6 < plVar2)) ||
       (plVar2 + (ulong)*(uint *)(param_1 + 0xb4) * 9 <= plVar6)) {
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    else {
      uVar7 = ((long)plVar6 - (long)plVar2 >> 3) * -0x71c71c71c71c71c7;
      (**(code **)plVar2[(uVar7 & 0xffffffff) * 9])();
      lVar3 = (uVar7 >> 5 & 0x7ffffff) * 4;
      *(uint *)(*(long *)(param_1 + 0xa8) + lVar3) =
           *(uint *)(*(long *)(param_1 + 0xa8) + lVar3) &
           (1 << (ulong)((uint)uVar7 & 0x1f) ^ 0xffffffffU);
      *(int *)(param_1 + 0xc4) = *(int *)(param_1 + 0xc4) + -1;
    }
    Aska::CriticalSection::Leave() const(lVar1);
    uVar5 = 1;
  }
  Aska::CriticalSection::Leave() const(lVar1);
  return uVar5;
}

// ==== Aska::TPriorityQueue<Aska::MappingQueue::EventItem, true>::CreateElement()
// vaddr 0x1f388d8 | ghidra 0x20388d8 | size 336 | symbol _ZN4Aska14TPriorityQueueINS_12MappingQueue9EventItemELb1EE13CreateElementEv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska14TPriorityQueueINS_12MappingQueue9EventItemELb1EE13CreateElementEv(long param_1)

{
  uint uVar1;
  undefined *puVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  Aska::CriticalSection::Enter() const(param_1 + 8);
  if (*(uint *)(param_1 + 0xc4) < *(uint *)(param_1 + 0xb4)) {
    lVar5 = *(long *)(param_1 + 0xa8);
    uVar3 = *(uint *)(param_1 + 0xc0);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0xb4) <= uVar6) {
        uVar6 = 0;
      }
      uVar1 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar1 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 200) + (ulong)uVar6 * 0x48;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0x48);
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0xc0) = uVar6 + 1;
    *(uint *)(param_1 + 0xc4) = *(uint *)(param_1 + 0xc4) + 1;
    puVar2 = PTR__ZTVN4Aska13TEventElementINS_12MappingQueue9EventItemEEE_02cbe428;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar1;
    plVar4 = (long *)(*(long *)(param_1 + 200) + (ulong)uVar6 * 0x48);
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar2 + 0x10);
    plVar4[3] = 0;
    *(undefined1 *)(plVar4 + 4) = 1;
    plVar4[8] = 0;
    plVar4[7] = 0;
    plVar4[6] = 0;
    plVar4[5] = 0;
    plVar4 = (long *)(*(long *)(param_1 + 200) + (ulong)uVar6 * 0x48);
    if (plVar4 != (long *)0x0) goto code_r0x02038a10;
  }
  if (*(char *)(param_1 + 0xd9) == '\0') {
    plVar4 = (long *)0x0;
  }
  else {
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x48,PTR__ZSt7nothrow_02cb9a80);
    puVar2 = PTR__ZTVN4Aska13TEventElementINS_12MappingQueue9EventItemEEE_02cbe428;
    if (plVar4 != (long *)0x0) {
      plVar4[3] = 0;
      plVar4[2] = 0;
      plVar4[1] = 0;
      *(undefined1 *)(plVar4 + 4) = 1;
      plVar4[8] = 0;
      plVar4[7] = 0;
      *plVar4 = (long)(puVar2 + 0x10);
      plVar4[6] = 0;
      plVar4[5] = 0;
    }
  }
code_r0x02038a10:
  Aska::CriticalSection::Leave() const(param_1 + 8);
  return plVar4;
}

// ==== Aska::TArrayIterator<Aska::TDynamicArray<Aska::detail::SmallHeap::HeapInfo, Aska::TAllocator<Aska::detail::SmallHeap::HeapInfo> > > Aska::TDynamicArray<Aska::detail::SmallHeap::HeapInfo, Aska::TAllocator<Aska::detail::SmallHeap::HeapInfo> >::Insert_<Aska::Memory::TConstruct1<Aska::TAllocator<Aska::detail::SmallHeap::HeapInfo>, void*> >(Aska::detail::SmallHeap::HeapInfo const*, unsigned long, Aska::Memory::TConstruct1<Aska::TAllocator<Aska::detail::SmallHeap::HeapInfo>, void*> const&)
// vaddr 0x1f4f618 | ghidra 0x204f618 | size 464 | symbol _ZN4Aska13TDynamicArrayINS_6detail9SmallHeap8HeapInfoENS_10TAllocatorIS3_EEE7Insert_INS_6Memory11TConstruct1IS5_PvEEEENS_14TArrayIteratorIS6_EEPKS3_mRKT_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 *
_ZN4Aska13TDynamicArrayINS_6detail9SmallHeap8HeapInfoENS_10TAllocatorIS3_EEE7Insert_INS_6Memory11TConstruct1IS5_PvEEEENS_14TArrayIteratorIS6_EEPKS3_mRKT_
          (long param_1,undefined8 *param_2,long param_3,long param_4)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  ulong uVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  ulong uVar6;
  long lVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  
  if (param_3 != 0) {
    puVar2 = *(undefined8 **)(param_1 + 0x10);
    lVar7 = *(long *)(param_1 + 0x18) - *(long *)(param_1 + 8) >> 4;
    uVar6 = param_3 + ((long)puVar2 - *(long *)(param_1 + 8) >> 4) * -0x5555555555555555;
    if ((ulong)(lVar7 * -0x5555555555555555) < uVar6) {
      uVar3 = lVar7 * 0x5555555555555556;
      if (uVar6 <= uVar3) {
        uVar6 = uVar3;
      }
      if ((uVar6 < 0x555555555555556) &&
         (puVar2 = (undefined8 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(uVar6 * 0x30,8), puVar2 != (undefined8 *)0x0)) {
        puVar1 = puVar2;
        for (puVar4 = *(undefined8 **)(param_1 + 8); puVar4 != param_2; puVar4 = puVar4 + 6) {
          uVar10 = puVar4[4];
          puVar1[5] = puVar4[5];
          puVar1[4] = uVar10;
          uVar10 = puVar4[2];
          puVar1[3] = puVar4[3];
          puVar1[2] = uVar10;
          uVar10 = *puVar4;
          puVar1[1] = puVar4[1];
          *puVar1 = uVar10;
          puVar1 = puVar1 + 6;
        }
        *puVar1 = **(undefined8 **)(param_4 + 8);
        Aska::detail::FixedSizeHeap::FixedSizeHeap()(puVar1 + 1);
        puVar5 = *(undefined8 **)(param_1 + 0x10);
        puVar9 = puVar1 + param_3 * 6;
        puVar4 = puVar9;
        if (puVar5 != param_2) {
          do {
            uVar10 = param_2[4];
            puVar4[5] = param_2[5];
            puVar4[4] = uVar10;
            uVar10 = param_2[2];
            puVar4[3] = param_2[3];
            puVar4[2] = uVar10;
            puVar8 = param_2 + 6;
            uVar10 = *param_2;
            puVar9 = puVar4 + 6;
            puVar4[1] = param_2[1];
            *puVar4 = uVar10;
            param_2 = puVar8;
            puVar4 = puVar9;
          } while (puVar5 != puVar8);
          param_2 = *(undefined8 **)(param_1 + 0x10);
        }
        puVar4 = *(undefined8 **)(param_1 + 8);
        if (puVar4 != param_2) {
          do {
            Aska::detail::FixedSizeHeap::~FixedSizeHeap()(puVar4 + 1);
            puVar4 = puVar4 + 6;
          } while (param_2 != puVar4);
          puVar4 = *(undefined8 **)(param_1 + 8);
        }
        Aska::MemoryManagerAdapter::AlignedFree(void*)(puVar4);
        *(undefined8 **)(param_1 + 8) = puVar2;
        *(undefined8 **)(param_1 + 0x10) = puVar9;
        *(undefined8 **)(param_1 + 0x18) = puVar2 + uVar6 * 6;
        param_2 = puVar1;
      }
    }
    else {
      if (puVar2 != param_2) {
        puVar2 = puVar2 + -6;
        do {
          uVar10 = puVar2[4];
          puVar4 = puVar2 + param_3 * 6;
          puVar4[5] = puVar2[5];
          puVar4[4] = uVar10;
          uVar10 = puVar2[2];
          puVar4[3] = puVar2[3];
          puVar4[2] = uVar10;
          uVar10 = *puVar2;
          puVar4[1] = puVar2[1];
          *puVar4 = uVar10;
          Aska::detail::FixedSizeHeap::~FixedSizeHeap()(puVar2 + 1);
          puVar2 = puVar2 + -6;
        } while ((long)puVar2 - (long)param_2 != -0x30);
      }
      *param_2 = **(undefined8 **)(param_4 + 8);
      Aska::detail::FixedSizeHeap::FixedSizeHeap()(param_2 + 1);
      *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + param_3 * 0x30;
    }
  }
  return param_2;
}

// ==== Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> >::Reserve(unsigned long)
// vaddr 0x1f71280 | ghidra 0x2071280 | size 256 | symbol _ZN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEE7ReserveEm | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEE7ReserveEm
               (long param_1,ulong param_2)

{
  long lVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  undefined8 uVar8;
  
  if ((param_2 < 0x555555555555556) &&
     ((ulong)((*(long *)(param_1 + 0x18) - *(long *)(param_1 + 8) >> 4) * -0x5555555555555555) <
      param_2)) {
    lVar1 = *(long *)PTR__ZN4Aska11SoundMemory10m_pMemHeapE_02cbbc38;
    if (lVar1 == 0) {
      lVar1 = Aska::Global::GetAvailableMemoryManager()();
    }
    puVar2 = (undefined8 *)Aska::MemoryManager::AlignedMalloc(unsigned long, long)(lVar1,param_2 * 0x30,8);
    if (puVar2 != (undefined8 *)0x0) {
      puVar4 = *(undefined8 **)(param_1 + 8);
      puVar7 = *(undefined8 **)(param_1 + 0x10);
      puVar5 = puVar2;
      puVar6 = puVar2;
      if (puVar4 != puVar7) {
        do {
          uVar8 = puVar4[4];
          puVar5[5] = puVar4[5];
          puVar5[4] = uVar8;
          uVar8 = puVar4[2];
          puVar5[3] = puVar4[3];
          puVar5[2] = uVar8;
          puVar3 = puVar4 + 6;
          uVar8 = *puVar4;
          puVar6 = puVar5 + 6;
          puVar5[1] = puVar4[1];
          *puVar5 = uVar8;
          puVar4 = puVar3;
          puVar5 = puVar6;
        } while (puVar7 != puVar3);
        puVar7 = *(undefined8 **)(param_1 + 8);
        puVar4 = *(undefined8 **)(param_1 + 0x10);
        if (puVar7 != puVar4) {
          do {
            Aska::detail::FixedSizeHeap::~FixedSizeHeap()(puVar7 + 1);
            puVar7 = puVar7 + 6;
          } while (puVar4 != puVar7);
          puVar4 = *(undefined8 **)(param_1 + 8);
        }
      }
      if (puVar4 != (undefined8 *)0x0) {
        operator delete[](void*)(puVar4);
      }
      *(undefined8 **)(param_1 + 8) = puVar2;
      *(undefined8 **)(param_1 + 0x10) = puVar6;
      *(undefined8 **)(param_1 + 0x18) = puVar2 + param_2 * 6;
    }
  }
  return;
}

// ==== Aska::TArrayIterator<Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> > > Aska::TDynamicArray<Aska::AudioSmallHeap::HeapInfo, Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo> >::Insert_<Aska::Memory::TConstruct1<Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo>, void*> >(Aska::AudioSmallHeap::HeapInfo const*, unsigned long, Aska::Memory::TConstruct1<Aska::AudioAllocator<Aska::AudioSmallHeap::HeapInfo>, void*> const&)
// vaddr 0x1f71d70 | ghidra 0x2071d70 | size 492 | symbol _ZN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEE7Insert_INS_6Memory11TConstruct1IS4_PvEEEENS_14TArrayIteratorIS5_EEPKS2_mRKT_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 *
_ZN4Aska13TDynamicArrayINS_14AudioSmallHeap8HeapInfoENS_14AudioAllocatorIS2_EEE7Insert_INS_6Memory11TConstruct1IS4_PvEEEENS_14TArrayIteratorIS5_EEPKS2_mRKT_
          (long param_1,undefined8 *param_2,long param_3,long param_4)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  ulong uVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  ulong uVar6;
  long lVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  
  if (param_3 != 0) {
    puVar2 = *(undefined8 **)(param_1 + 0x10);
    lVar7 = *(long *)(param_1 + 0x18) - *(long *)(param_1 + 8) >> 4;
    uVar6 = param_3 + ((long)puVar2 - *(long *)(param_1 + 8) >> 4) * -0x5555555555555555;
    if ((ulong)(lVar7 * -0x5555555555555555) < uVar6) {
      uVar3 = lVar7 * 0x5555555555555556;
      if (uVar6 <= uVar3) {
        uVar6 = uVar3;
      }
      if (uVar6 < 0x555555555555556) {
        lVar7 = *(long *)PTR__ZN4Aska11SoundMemory10m_pMemHeapE_02cbbc38;
        if (lVar7 == 0) {
          lVar7 = Aska::Global::GetAvailableMemoryManager()();
        }
        puVar2 = (undefined8 *)Aska::MemoryManager::AlignedMalloc(unsigned long, long)(lVar7,uVar6 * 0x30,8);
        if (puVar2 != (undefined8 *)0x0) {
          puVar1 = puVar2;
          for (puVar4 = *(undefined8 **)(param_1 + 8); puVar4 != param_2; puVar4 = puVar4 + 6) {
            uVar10 = puVar4[4];
            puVar1[5] = puVar4[5];
            puVar1[4] = uVar10;
            uVar10 = puVar4[2];
            puVar1[3] = puVar4[3];
            puVar1[2] = uVar10;
            uVar10 = *puVar4;
            puVar1[1] = puVar4[1];
            *puVar1 = uVar10;
            puVar1 = puVar1 + 6;
          }
          *puVar1 = **(undefined8 **)(param_4 + 8);
          Aska::detail::FixedSizeHeap::FixedSizeHeap()(puVar1 + 1);
          puVar5 = *(undefined8 **)(param_1 + 0x10);
          puVar9 = puVar1 + param_3 * 6;
          puVar4 = puVar9;
          if (puVar5 != param_2) {
            do {
              uVar10 = param_2[4];
              puVar4[5] = param_2[5];
              puVar4[4] = uVar10;
              uVar10 = param_2[2];
              puVar4[3] = param_2[3];
              puVar4[2] = uVar10;
              puVar8 = param_2 + 6;
              uVar10 = *param_2;
              puVar9 = puVar4 + 6;
              puVar4[1] = param_2[1];
              *puVar4 = uVar10;
              param_2 = puVar8;
              puVar4 = puVar9;
            } while (puVar5 != puVar8);
            param_2 = *(undefined8 **)(param_1 + 0x10);
          }
          puVar4 = *(undefined8 **)(param_1 + 8);
          if (puVar4 != param_2) {
            do {
              Aska::detail::FixedSizeHeap::~FixedSizeHeap()(puVar4 + 1);
              puVar4 = puVar4 + 6;
            } while (param_2 != puVar4);
            param_2 = *(undefined8 **)(param_1 + 8);
          }
          if (param_2 != (undefined8 *)0x0) {
            operator delete[](void*)(param_2);
          }
          *(undefined8 **)(param_1 + 8) = puVar2;
          *(undefined8 **)(param_1 + 0x10) = puVar9;
          *(undefined8 **)(param_1 + 0x18) = puVar2 + uVar6 * 6;
          param_2 = puVar1;
        }
      }
    }
    else {
      if (puVar2 != param_2) {
        puVar2 = puVar2 + -6;
        do {
          uVar10 = puVar2[4];
          puVar4 = puVar2 + param_3 * 6;
          puVar4[5] = puVar2[5];
          puVar4[4] = uVar10;
          uVar10 = puVar2[2];
          puVar4[3] = puVar2[3];
          puVar4[2] = uVar10;
          uVar10 = *puVar2;
          puVar4[1] = puVar2[1];
          *puVar4 = uVar10;
          Aska::detail::FixedSizeHeap::~FixedSizeHeap()(puVar2 + 1);
          puVar2 = puVar2 + -6;
        } while ((long)puVar2 - (long)param_2 != -0x30);
      }
      *param_2 = **(undefined8 **)(param_4 + 8);
      Aska::detail::FixedSizeHeap::FixedSizeHeap()(param_2 + 1);
      *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + param_3 * 0x30;
    }
  }
  return param_2;
}

// ==== Aska::TStack<StackItem, 32>::Push(StackItem const&)
// vaddr 0x20dd8fc | ghidra 0x21dd8fc | size 392 | symbol _ZN4Aska6TStackI9StackItemLi32EE4PushERKS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6TStackI9StackItemLi32EE4PushERKS1_(undefined8 *param_1,undefined8 param_2)

{
  int iVar1;
  undefined8 *puVar2;
  int iVar3;
  undefined1 auVar4 [16];
  undefined8 *puVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  int iVar9;
  
  iVar9 = *(int *)((long)param_1 + 0x214);
  iVar3 = *(int *)(param_1 + 0x42);
  iVar1 = iVar9 + 1;
  if (iVar3 <= iVar1) {
    puVar5 = (undefined8 *)param_1[0x41];
    puVar2 = param_1 + 1;
    if (iVar3 < 3) {
      if (puVar5 != puVar2) {
        if (puVar5 != (undefined8 *)0x0) {
          operator delete[](void*)();
          iVar9 = *(int *)((long)param_1 + 0x214);
        }
        param_1[0x41] = puVar2;
      }
      *(undefined4 *)(param_1 + 0x42) = 0x20;
      if (0x1f < iVar9) {
        *(undefined4 *)((long)param_1 + 0x214) = 0x1f;
      }
    }
    else {
      if (puVar5 != puVar2) {
        return 0;
      }
      uVar6 = (long)iVar3 << 4;
      auVar4._8_8_ = 0;
      auVar4._0_8_ = uVar6;
      lVar8 = (long)iVar3 << 8;
      lVar7 = lVar8;
      if (SUB168(auVar4 * ZEXT816(0x10),8) != 0) {
        lVar7 = -1;
      }
      lVar7 = operator new[](unsigned long, std::nothrow_t const&)(lVar7,PTR__ZSt7nothrow_02cb9a80);
      if (lVar7 == 0) {
        return 0;
      }
      memset(lVar7,0,lVar8);
      param_1[0x41] = lVar7;
      *(int *)(param_1 + 0x42) = (int)uVar6;
      if (-1 < iVar9) {
        lVar8 = (long)iVar9;
        uVar6 = (**(code **)*param_1)(param_1,param_1 + lVar8 * 2 + 1,lVar7 + lVar8 * 0x10);
        if ((uVar6 & 1) == 0) {
          return 0;
        }
        lVar7 = lVar8 + 1;
        lVar8 = lVar8 * 0x10;
        while( true ) {
          lVar7 = lVar7 + -1;
          if (lVar7 < 1) break;
          uVar6 = (**(code **)*param_1)
                            (param_1,(long)param_1 + lVar8 + -8,param_1[0x41] + lVar8 + -0x10);
          lVar8 = lVar8 + -0x10;
          if ((uVar6 & 1) == 0) {
            return 0;
          }
        }
      }
    }
  }
  uVar6 = (**(code **)*param_1)(param_1,param_2,param_1[0x41] + (long)iVar1 * 0x10);
  if ((uVar6 & 1) == 0) {
    return 0;
  }
  *(int *)((long)param_1 + 0x214) = iVar1;
  return 1;
}

// ==== Aska::TPriorityQueue<Aska::_AsyncStream::EvItem, true>::Acquire(Aska::_AsyncStream::EvItem*, unsigned long, unsigned long*)
// vaddr 0x20e7324 | ghidra 0x21e7324 | size 636 | symbol _ZN4Aska14TPriorityQueueINS_12_AsyncStream6EvItemELb1EE7AcquireEPS2_mPm | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska14TPriorityQueueINS_12_AsyncStream6EvItemELb1EE7AcquireEPS2_mPm
          (long param_1,long *param_2,ulong param_3,undefined8 *param_4)

{
  long lVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  long *plVar5;
  int *piVar6;
  long lVar7;
  long lVar8;
  undefined4 uVar9;
  long *plVar10;
  ulong uVar11;
  long *plVar12;
  
  lVar1 = param_1 + 8;
  Aska::CriticalSection::Enter() const(lVar1);
  Aska::CriticalSection::Enter() const(lVar1);
  if ((*(int *)(param_1 + 0xb0) < 1) ||
     (plVar10 = *(long **)(param_1 + 0x48), plVar10 == (long *)0x0)) {
code_r0x021e73b8:
    Aska::CriticalSection::Leave() const(lVar1);
joined_r0x021e73c0:
    if (param_4 == (undefined8 *)0x0) {
      uVar9 = 0;
    }
    else {
      uVar9 = 0;
      *param_4 = 0;
    }
    goto code_r0x021e7580;
  }
  if ((plVar10[3] == 0) || ((plVar10[3] & param_3) != 0)) {
    Aska::CriticalSection::Leave() const(lVar1);
  }
  else {
    do {
      if ((long *)(param_1 + 0x38) == plVar10) goto code_r0x021e73b8;
      plVar10 = (long *)plVar10[2];
    } while ((plVar10[3] != 0) && ((plVar10[3] & param_3) == 0));
    Aska::CriticalSection::Leave() const(lVar1);
    if (plVar10 == (long *)0x0) goto joined_r0x021e73c0;
  }
  if (plVar10 + 5 != param_2) {
    *(int *)param_2 = (int)plVar10[5];
    param_2[1] = plVar10[6];
    param_2[2] = plVar10[7];
    param_2[3] = plVar10[8];
    param_2[4] = plVar10[9];
    param_2[5] = plVar10[10];
    param_2[6] = plVar10[0xb];
    param_2[7] = plVar10[0xc];
    plVar12 = param_2 + 8;
    plVar5 = (long *)*plVar12;
    if ((long *)plVar10[0xd] != plVar5) {
      piVar6 = (int *)param_2[9];
      if (piVar6 == (int *)0x0) {
code_r0x021e7454:
        if (plVar5 != (long *)0x0) {
          (**(code **)(*plVar5 + 8))();
        }
        if (param_2[9] != 0) {
          Aska::TSharedPointerCode::DeleteCounter(int*)();
        }
      }
      else {
        do {
          iVar2 = *piVar6;
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar4) {
            *piVar6 = iVar2 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        if (iVar2 + -1 == 0) {
          plVar5 = (long *)*plVar12;
          goto code_r0x021e7454;
        }
      }
      *plVar12 = 0;
      param_2[9] = 0;
      piVar6 = (int *)plVar10[0xe];
      param_2[9] = (long)piVar6;
      param_2[8] = plVar10[0xd];
      if (piVar6 != (int *)0x0) {
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar6,0x10);
          if (bVar4) {
            *piVar6 = *piVar6 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
      }
    }
  }
  if (param_4 != (undefined8 *)0x0) {
    *param_4 = plVar10;
  }
  if ((long *)(param_1 + 0x38) != plVar10) {
    lVar7 = plVar10[1];
    lVar8 = plVar10[2];
    if (lVar7 != 0) {
      *(long *)(lVar7 + 0x10) = lVar8;
    }
    if (lVar8 != 0) {
      *(long *)(lVar8 + 8) = lVar7;
    }
    if (0 < *(int *)(param_1 + 0xb0)) {
      *(int *)(param_1 + 0xb0) = *(int *)(param_1 + 0xb0) + -1;
    }
    plVar10[1] = 0;
    plVar10[2] = 0;
  }
  Aska::CriticalSection::Enter() const(lVar1);
  plVar5 = *(long **)(param_1 + 0xf8);
  if (((plVar5 == (long *)0x0) || (plVar10 < plVar5)) ||
     (plVar5 + (ulong)*(uint *)(param_1 + 0xe4) * 0xf <= plVar10)) {
    (**(code **)(*plVar10 + 8))(plVar10);
  }
  else {
    uVar11 = ((long)plVar10 - (long)plVar5 >> 3) * -0x1111111111111111;
    (**(code **)plVar5[(uVar11 & 0xffffffff) * 0xf])();
    lVar7 = (uVar11 >> 5 & 0x7ffffff) * 4;
    *(uint *)(*(long *)(param_1 + 0xd8) + lVar7) =
         *(uint *)(*(long *)(param_1 + 0xd8) + lVar7) &
         (1 << (ulong)((uint)uVar11 & 0x1f) ^ 0xffffffffU);
    *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + -1;
  }
  Aska::CriticalSection::Leave() const(lVar1);
  uVar9 = 1;
code_r0x021e7580:
  Aska::CriticalSection::Leave() const(lVar1);
  return uVar9;
}

// ==== Aska::TStack<StackItem, 32>::CopyElement(StackItem const*, StackItem*)
// vaddr 0x20e8264 | ghidra 0x21e8264 | size 32 | symbol _ZN4Aska6TStackI9StackItemLi32EE11CopyElementEPKS1_PS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska6TStackI9StackItemLi32EE11CopyElementEPKS1_PS1_
          (undefined8 param_1,undefined8 *param_2,undefined8 *param_3)

{
  if (param_2 != param_3) {
    *param_3 = *param_2;
    param_3[1] = param_2[1];
  }
  return 1;
}

// ==== Aska::TPriorityQueue<Aska::DecodeTextureEventItem, true>::CreateElement()
// vaddr 0x2100320 | ghidra 0x2200320 | size 364 | symbol _ZN4Aska14TPriorityQueueINS_22DecodeTextureEventItemELb1EE13CreateElementEv | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN4Aska14TPriorityQueueINS_22DecodeTextureEventItemELb1EE13CreateElementEv(long param_1)

{
  uint uVar1;
  undefined *puVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  
  Aska::CriticalSection::Enter() const(param_1 + 8);
  if (*(uint *)(param_1 + 0xd4) < *(uint *)(param_1 + 0xc4)) {
    lVar5 = *(long *)(param_1 + 0xb8);
    uVar3 = *(uint *)(param_1 + 0xd0);
    do {
      uVar6 = uVar3;
      if (*(uint *)(param_1 + 0xc4) <= uVar6) {
        uVar6 = 0;
      }
      uVar1 = 1 << (ulong)(uVar6 & 0x1f);
      uVar3 = uVar6 + 1;
    } while ((uVar1 & *(uint *)(lVar5 + (ulong)(uVar6 >> 5) * 4)) != 0);
    uVar8 = *(long *)(param_1 + 0xd8) + (ulong)uVar6 * 0x58;
    uVar9 = uVar8;
    do {
      uVar10 = uVar9 + 0x7f & 0xffffffffffffff81;
      Hint_Prefetch(uVar9,0,2,0);
      uVar9 = uVar10;
    } while (uVar10 < uVar8 + 0x58);
    lVar7 = (ulong)(uVar6 >> 5) * 4;
    *(uint *)(param_1 + 0xd0) = uVar6 + 1;
    *(uint *)(param_1 + 0xd4) = *(uint *)(param_1 + 0xd4) + 1;
    puVar2 = PTR__ZTVN4Aska13TEventElementINS_22DecodeTextureEventItemEEE_02cbba38;
    *(uint *)(lVar5 + lVar7) = *(uint *)(lVar5 + lVar7) | uVar1;
    plVar4 = (long *)(*(long *)(param_1 + 0xd8) + (ulong)uVar6 * 0x58);
    *(undefined1 *)(plVar4 + 4) = 1;
    plVar4[2] = 0;
    plVar4[1] = 0;
    *plVar4 = (long)(puVar2 + 0x10);
    plVar4[3] = 0;
    plVar4[9] = 0;
    plVar4[8] = 0;
    plVar4[7] = 0;
    plVar4[6] = 0;
    plVar4[5] = 0;
    *(ushort *)(plVar4 + 10) = *(ushort *)(plVar4 + 10) & 0xf800 | 1;
    plVar4 = (long *)(*(long *)(param_1 + 0xd8) + (ulong)uVar6 * 0x58);
    if (plVar4 != (long *)0x0) goto code_r0x02200474;
  }
  if (*(char *)(param_1 + 0xe9) == '\0') {
    plVar4 = (long *)0x0;
  }
  else {
    plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x58,PTR__ZSt7nothrow_02cb9a80);
    puVar2 = PTR__ZTVN4Aska13TEventElementINS_22DecodeTextureEventItemEEE_02cbba38;
    if (plVar4 != (long *)0x0) {
      plVar4[3] = 0;
      plVar4[9] = 0;
      plVar4[2] = 0;
      plVar4[1] = 0;
      *(undefined1 *)(plVar4 + 4) = 1;
      plVar4[8] = 0;
      plVar4[7] = 0;
      plVar4[6] = 0;
      plVar4[5] = 0;
      *plVar4 = (long)(puVar2 + 0x10);
      *(undefined2 *)(plVar4 + 10) = 1;
    }
  }
code_r0x02200474:
  Aska::CriticalSection::Leave() const(param_1 + 8);
  return plVar4;
}

// ==== Aska::TPriorityQueue<Aska::DecodeTextureEventItem, true>::Acquire(Aska::DecodeTextureEventItem*, unsigned long, unsigned long*)
// vaddr 0x2100a50 | ghidra 0x2200a50 | size 460 | symbol _ZN4Aska14TPriorityQueueINS_22DecodeTextureEventItemELb1EE7AcquireEPS1_mPm | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska14TPriorityQueueINS_22DecodeTextureEventItemELb1EE7AcquireEPS1_mPm
          (long param_1,undefined8 param_2,ulong param_3,undefined8 *param_4)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  undefined4 uVar5;
  long *plVar6;
  ulong uVar7;
  
  lVar1 = param_1 + 8;
  Aska::CriticalSection::Enter() const(lVar1);
  Aska::CriticalSection::Enter() const(lVar1);
  if ((*(int *)(param_1 + 0x90) < 1) || (plVar6 = *(long **)(param_1 + 0x48), plVar6 == (long *)0x0)
     ) {
code_r0x02200ad8:
    Aska::CriticalSection::Leave() const(lVar1);
code_r0x02200ae0:
    if (param_4 == (undefined8 *)0x0) {
      uVar5 = 0;
    }
    else {
      uVar5 = 0;
      *param_4 = 0;
    }
  }
  else {
    if ((plVar6[3] == 0) || ((plVar6[3] & param_3) != 0)) {
      Aska::CriticalSection::Leave() const(lVar1);
    }
    else {
      do {
        if ((long *)(param_1 + 0x38) == plVar6) goto code_r0x02200ad8;
        plVar6 = (long *)plVar6[2];
      } while ((plVar6[3] != 0) && ((plVar6[3] & param_3) == 0));
      Aska::CriticalSection::Leave() const(lVar1);
      if (plVar6 == (long *)0x0) goto code_r0x02200ae0;
    }
    Aska::DecodeTextureEventItem::operator=(Aska::DecodeTextureEventItem const&)(param_2,plVar6 + 5);
    if (param_4 != (undefined8 *)0x0) {
      *param_4 = plVar6;
    }
    if ((long *)(param_1 + 0x38) != plVar6) {
      lVar3 = plVar6[1];
      lVar4 = plVar6[2];
      if (lVar3 != 0) {
        *(long *)(lVar3 + 0x10) = lVar4;
      }
      if (lVar4 != 0) {
        *(long *)(lVar4 + 8) = lVar3;
      }
      if (0 < *(int *)(param_1 + 0x90)) {
        *(int *)(param_1 + 0x90) = *(int *)(param_1 + 0x90) + -1;
      }
      plVar6[1] = 0;
      plVar6[2] = 0;
    }
    Aska::CriticalSection::Enter() const(lVar1);
    plVar2 = *(long **)(param_1 + 0xd8);
    if (((plVar2 == (long *)0x0) || (plVar6 < plVar2)) ||
       (plVar2 + (ulong)*(uint *)(param_1 + 0xc4) * 0xb <= plVar6)) {
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    else {
      uVar7 = ((long)plVar6 - (long)plVar2 >> 3) * 0x2e8ba2e8ba2e8ba3;
      (**(code **)plVar2[(uVar7 & 0xffffffff) * 0xb])();
      lVar3 = (uVar7 >> 5 & 0x7ffffff) * 4;
      *(uint *)(*(long *)(param_1 + 0xb8) + lVar3) =
           *(uint *)(*(long *)(param_1 + 0xb8) + lVar3) &
           (1 << (ulong)((uint)uVar7 & 0x1f) ^ 0xffffffffU);
      *(int *)(param_1 + 0xd4) = *(int *)(param_1 + 0xd4) + -1;
    }
    Aska::CriticalSection::Leave() const(lVar1);
    uVar5 = 1;
  }
  Aska::CriticalSection::Leave() const(lVar1);
  return uVar5;
}

// ==== Aska::TArrayIterator<Aska::TDynamicArray<short, Aska::detail::TSmallHeapAllocator<short> > > Aska::TDynamicArray<short, Aska::detail::TSmallHeapAllocator<short> >::Insert_<Aska::Memory::TUninitializedFillN<short> >(short const*, unsigned long, Aska::Memory::TUninitializedFillN<short> const&)
// vaddr 0x2101e70 | ghidra 0x2201e70 | size 864 | symbol _ZN4Aska13TDynamicArrayIsNS_6detail19TSmallHeapAllocatorIsEEE7Insert_INS_6Memory19TUninitializedFillNIsEEEENS_14TArrayIteratorIS4_EEPKsmRKT_ | lib libSOA-3.7.0.so | 2026-10-04
undefined2 *
_ZN4Aska13TDynamicArrayIsNS_6detail19TSmallHeapAllocatorIsEEE7Insert_INS_6Memory19TUninitializedFillNIsEEEENS_14TArrayIteratorIS4_EEPKsmRKT_
          (long param_1,undefined2 *param_2,long param_3,ulong *param_4)

{
  undefined2 uVar1;
  undefined8 *puVar2;
  bool bVar3;
  undefined2 *puVar4;
  ulong uVar5;
  ulong uVar6;
  undefined2 *puVar7;
  undefined2 *puVar8;
  ulong uVar9;
  undefined2 *puVar10;
  ulong uVar11;
  undefined2 *puVar12;
  ulong uVar13;
  undefined8 *puVar14;
  undefined8 *puVar15;
  undefined2 *puVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  
  if (param_3 == 0) {
    return param_2;
  }
  puVar4 = *(undefined2 **)(param_1 + 0x10);
  uVar6 = param_3 + ((long)puVar4 - *(long *)(param_1 + 8) >> 1);
  uVar9 = *(long *)(param_1 + 0x18) - *(long *)(param_1 + 8);
  if (uVar6 <= (ulong)((long)uVar9 >> 1)) {
    while (puVar4 != param_2) {
      puVar4[param_3 + -1] = puVar4[-1];
      puVar4 = puVar4 + -1;
    }
    uVar6 = *param_4;
    if (uVar6 != 0) {
      puVar7 = (undefined2 *)param_4[1];
      puVar4 = param_2;
      if (((0xf < uVar6) && (uVar9 = uVar6 & 0xfffffffffffffff0, uVar9 != 0)) &&
         (((undefined2 *)((long)puVar7 + 1U) <= param_2 || (param_2 + uVar6 <= puVar7)))) {
        uVar1 = *puVar7;
        uVar17 = CONCAT26(uVar1,CONCAT24(uVar1,CONCAT22(uVar1,uVar1)));
        uVar18 = CONCAT26(uVar1,CONCAT24(uVar1,CONCAT22(uVar1,uVar1)));
        puVar14 = (undefined8 *)(param_2 + 8);
        uVar5 = uVar9;
        do {
          puVar14[-1] = uVar18;
          puVar14[-2] = uVar17;
          puVar14[1] = uVar18;
          *puVar14 = uVar17;
          uVar5 = uVar5 - 0x10;
          puVar14 = puVar14 + 4;
        } while (uVar5 != 0);
        bVar3 = uVar6 == uVar9;
        uVar6 = uVar6 - uVar9;
        puVar4 = param_2 + uVar9;
        if (bVar3) goto code_r0x02202020;
      }
      do {
        uVar6 = uVar6 - 1;
        *puVar4 = *puVar7;
        puVar4 = puVar4 + 1;
      } while (uVar6 != 0);
    }
code_r0x02202020:
    *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + param_3 * 2;
    return param_2;
  }
  if (uVar6 <= uVar9) {
    uVar6 = uVar9;
  }
  if ((long)uVar6 < 0) {
    return param_2;
  }
  puVar4 = (undefined2 *)Aska::detail::SmallHeapProxy::Allocate(unsigned long)(uVar6 << 1);
  if (puVar4 == (undefined2 *)0x0) {
    return param_2;
  }
  puVar7 = *(undefined2 **)(param_1 + 8);
  if (puVar7 == param_2) {
    uVar9 = *param_4;
    puVar7 = puVar4;
  }
  else {
    uVar5 = (long)param_2 + (-2 - (long)puVar7);
    uVar9 = (uVar5 >> 1) + 1;
    puVar10 = puVar4;
    if (((uVar9 < 0x10) || (uVar11 = uVar9 & 0xfffffffffffffff0, uVar11 == 0)) ||
       ((puVar4 < (undefined2 *)((long)puVar7 + (uVar5 & 0xfffffffffffffffe) + 2) &&
        (puVar7 < (undefined2 *)((long)puVar4 + (uVar5 + 2 & 0xfffffffffffffffe)))))) {
code_r0x02202034:
      do {
        puVar8 = puVar7 + 1;
        *puVar10 = *puVar7;
        puVar7 = puVar8;
        puVar10 = puVar10 + 1;
      } while (param_2 != puVar8);
    }
    else {
      puVar14 = (undefined8 *)(puVar7 + 8);
      puVar7 = puVar7 + uVar11;
      puVar15 = (undefined8 *)(puVar4 + 8);
      uVar13 = uVar11;
      do {
        puVar2 = puVar14 + -1;
        uVar17 = puVar14[-2];
        uVar19 = puVar14[1];
        uVar18 = *puVar14;
        puVar14 = puVar14 + 4;
        uVar13 = uVar13 - 0x10;
        puVar15[-1] = *puVar2;
        puVar15[-2] = uVar17;
        puVar15[1] = uVar19;
        *puVar15 = uVar18;
        puVar15 = puVar15 + 4;
      } while (uVar13 != 0);
      puVar10 = puVar4 + uVar11;
      if (uVar9 != uVar11) goto code_r0x02202034;
    }
    puVar7 = (undefined2 *)((long)puVar4 + (uVar5 & 0xfffffffffffffffe) + 2);
    uVar9 = *param_4;
  }
  if (uVar9 != 0) {
    puVar8 = (undefined2 *)param_4[1];
    puVar10 = puVar7;
    if (((0xf < uVar9) && (uVar5 = uVar9 & 0xfffffffffffffff0, uVar5 != 0)) &&
       (((undefined2 *)((long)puVar8 + 1U) <= puVar7 || (puVar7 + uVar9 <= puVar8)))) {
      uVar1 = *puVar8;
      uVar17 = CONCAT26(uVar1,CONCAT24(uVar1,CONCAT22(uVar1,uVar1)));
      uVar18 = CONCAT26(uVar1,CONCAT24(uVar1,CONCAT22(uVar1,uVar1)));
      puVar14 = (undefined8 *)(puVar7 + 8);
      uVar11 = uVar5;
      do {
        puVar14[-1] = uVar18;
        puVar14[-2] = uVar17;
        puVar14[1] = uVar18;
        *puVar14 = uVar17;
        uVar11 = uVar11 - 0x10;
        puVar14 = puVar14 + 4;
      } while (uVar11 != 0);
      bVar3 = uVar9 == uVar5;
      uVar9 = uVar9 - uVar5;
      puVar10 = puVar7 + uVar5;
      if (bVar3) goto code_r0x022020d8;
    }
    do {
      uVar9 = uVar9 - 1;
      *puVar10 = *puVar8;
      puVar10 = puVar10 + 1;
    } while (uVar9 != 0);
  }
code_r0x022020d8:
  puVar8 = *(undefined2 **)(param_1 + 0x10);
  puVar10 = puVar7 + param_3;
  if (puVar8 == param_2) goto code_r0x0220219c;
  uVar5 = (long)puVar8 + (-2 - (long)param_2);
  uVar11 = uVar5 >> 1;
  uVar9 = uVar11 + 1;
  puVar12 = puVar10;
  if (((uVar9 < 0x10) || (uVar13 = uVar9 & 0xfffffffffffffff0, uVar13 == 0)) ||
     ((puVar10 < param_2 + uVar11 + 1 && (param_2 < puVar7 + uVar11 + param_3 + 1)))) {
code_r0x02202180:
    do {
      puVar16 = param_2 + 1;
      *puVar12 = *param_2;
      puVar12 = puVar12 + 1;
      param_2 = puVar16;
    } while (puVar8 != puVar16);
  }
  else {
    puVar14 = (undefined8 *)(param_2 + 8);
    param_2 = param_2 + uVar13;
    puVar15 = (undefined8 *)(puVar7 + param_3 + 8);
    uVar11 = uVar13;
    do {
      puVar2 = puVar14 + -1;
      uVar17 = puVar14[-2];
      uVar19 = puVar14[1];
      uVar18 = *puVar14;
      puVar14 = puVar14 + 4;
      uVar11 = uVar11 - 0x10;
      puVar15[-1] = *puVar2;
      puVar15[-2] = uVar17;
      puVar15[1] = uVar19;
      *puVar15 = uVar18;
      puVar15 = puVar15 + 4;
    } while (uVar11 != 0);
    puVar12 = puVar10 + uVar13;
    if (uVar9 != uVar13) goto code_r0x02202180;
  }
  puVar10 = (undefined2 *)((long)puVar10 + (uVar5 & 0xfffffffffffffffe) + 2);
code_r0x0220219c:
  Aska::detail::SmallHeapProxy::Free(void*, unsigned long)(*(undefined8 *)(param_1 + 8),0);
  *(undefined2 **)(param_1 + 8) = puVar4;
  *(undefined2 **)(param_1 + 0x10) = puVar10;
  *(undefined2 **)(param_1 + 0x18) = puVar4 + uVar6;
  return puVar7;
}

// ==== Aska::TList<Aska::LinkElement>::Add(Aska::LinkElement*)
// vaddr 0x2130370 | ghidra 0x2230370 | size 36 | symbol _ZN4Aska5TListINS_11LinkElementEE3AddEPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TListINS_11LinkElementEE3AddEPS1_(long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x10);
  *(long *)(param_2 + 8) = lVar1;
  *(long *)(param_2 + 0x10) = param_1 + 8;
  *(long *)(param_1 + 0x10) = param_2;
  *(long *)(lVar1 + 0x10) = param_2;
  *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;
  return;
}

// ==== Aska::TList<Aska::LinkElement>::Delete(Aska::LinkElement*)
// vaddr 0x21303d8 | ghidra 0x22303d8 | size 64 | symbol _ZN4Aska5TListINS_11LinkElementEE6DeleteEPS1_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5TListINS_11LinkElementEE6DeleteEPS1_(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  if ((param_1 + 8 != param_2) && (param_2 != 0)) {
    lVar1 = *(long *)(param_2 + 8);
    lVar2 = *(long *)(param_2 + 0x10);
    if (lVar1 != 0) {
      *(long *)(lVar1 + 0x10) = lVar2;
    }
    if (lVar2 != 0) {
      *(long *)(lVar2 + 8) = lVar1;
    }
    if (0 < *(int *)(param_1 + 0x20)) {
      *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + -1;
    }
    *(long *)(param_2 + 8) = 0;
    *(undefined8 *)(param_2 + 0x10) = 0;
  }
  return;
}

// ==== Aska::TArray<Aska::GuideEffector::GUIDEDOBJ, false>::Resize(long, bool)
// vaddr 0x21327ac | ghidra 0x22327ac | size 336 | symbol _ZN4Aska6TArrayINS_13GuideEffector9GUIDEDOBJELb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayINS_13GuideEffector9GUIDEDOBJELb0EE6ResizeElb(long param_1,long param_2)

{
  undefined8 *puVar1;
  ushort uVar2;
  long lVar3;
  long lVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  undefined8 uVar7;
  
  if (param_2 == 0) {
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar3 = *(long *)(param_1 + 0x10);
  if (lVar3 < param_2) {
    lVar3 = param_2 << 1;
  }
  else {
    lVar4 = lVar3 + 3;
    if (-1 < lVar3) {
      lVar4 = lVar3;
    }
    if (((lVar4 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar3 = param_2 * 2,
       lVar3 - *(long *)(param_1 + 0x28) == 0 || lVar3 < *(long *)(param_1 + 0x28)))
    goto code_r0x022328dc;
  }
  puVar6 = *(undefined8 **)(param_1 + 8);
  if (puVar6 == (undefined8 *)0x0) {
    lVar3 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar3 = param_2;
    }
    lVar4 = operator new[](unsigned long, std::nothrow_t const&)(lVar3 * 0x30,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar4;
    if (lVar4 == 0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    uVar2 = *(ushort *)(param_1 + 0x30) & 0xfffe;
code_r0x022328d4:
    *(ushort *)(param_1 + 0x30) = uVar2;
  }
  else {
    puVar1 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)(param_2 * 0x60,PTR__ZSt7nothrow_02cb9a80);
    *(undefined8 **)(param_1 + 8) = puVar1;
    if (puVar1 == (undefined8 *)0x0) {
      uVar2 = *(ushort *)(param_1 + 0x30) | 1;
      goto code_r0x022328d4;
    }
    lVar4 = param_2;
    if (*(long *)(param_1 + 0x18) <= param_2) {
      lVar4 = *(long *)(param_1 + 0x18);
    }
    puVar5 = puVar6;
    if (0 < lVar4) {
      do {
        uVar7 = puVar5[4];
        lVar4 = lVar4 + -1;
        puVar1[5] = puVar5[5];
        puVar1[4] = uVar7;
        uVar7 = puVar5[2];
        puVar1[3] = puVar5[3];
        puVar1[2] = uVar7;
        uVar7 = *puVar5;
        puVar1[1] = puVar5[1];
        *puVar1 = uVar7;
        puVar1 = puVar1 + 6;
        puVar5 = puVar5 + 6;
      } while (lVar4 != 0);
    }
    operator delete[](void*)(puVar6);
    *(long *)(param_1 + 0x10) = lVar3;
    *(long *)(param_1 + 0x18) = param_2;
  }
  *(long *)(param_1 + 0x10) = lVar3;
code_r0x022328dc:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== TOMQuickSort<Aska::RenderableObject, float, 64, 10>::Descend(Aska::RenderableObject**, int, int, Aska::ObjectManager::RenderableObjectContext*)
// vaddr 0x2160494 | ghidra 0x2260494 | size 524 | symbol _ZN12TOMQuickSortIN4Aska16RenderableObjectEfLi64ELi10EE7DescendEPPS1_iiPNS0_13ObjectManager23RenderableObjectContextE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN12TOMQuickSortIN4Aska16RenderableObjectEfLi64ELi10EE7DescendEPPS1_iiPNS0_13ObjectManager23RenderableObjectContextE
               (long param_1,uint param_2,uint param_3,long param_4)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  ulong uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  long lVar9;
  long lVar10;
  int iVar11;
  long lVar12;
  int iVar13;
  long lVar14;
  ulong uVar15;
  int iVar16;
  float fVar17;
  int aiStack_210 [64];
  uint auStack_110 [64];
  
  if (param_2 == param_3) {
    return;
  }
  uVar5 = 0;
  iVar6 = param_3 - 1;
  uVar7 = param_2;
  do {
    if ((int)(iVar6 - uVar7) < 10) {
      if ((int)uVar5 == 0) {
        if ((int)param_3 <= (int)(param_2 + 1)) {
          return;
        }
        lVar9 = (long)(int)(param_2 + 1);
        uVar7 = param_2;
        do {
          lVar10 = *(long *)(param_1 + lVar9 * 8);
          uVar5 = (ulong)uVar7;
          if ((int)param_2 <= (int)uVar7) {
            fVar17 = *(float *)(param_4 + (ulong)*(ushort *)(lVar10 + 0x1b8) * 8 + 4);
            uVar15 = (long)(int)uVar7;
            do {
              lVar14 = *(long *)(param_1 + uVar15 * 8);
              if (fVar17 <= *(float *)(param_4 + (ulong)*(ushort *)(lVar14 + 0x1b8) * 8 + 4)) {
                uVar5 = uVar15 & 0xffffffff;
                break;
              }
              uVar5 = uVar15 - 1;
              *(long *)(param_1 + uVar15 * 8 + 8) = lVar14;
              bVar1 = (long)(int)param_2 < (long)uVar15;
              uVar15 = uVar5;
            } while (bVar1);
          }
          lVar9 = lVar9 + 1;
          uVar7 = uVar7 + 1;
          *(long *)(param_1 + (long)((int)uVar5 + 1) * 8) = lVar10;
          if ((uint)lVar9 == param_3) {
            return;
          }
        } while( true );
      }
      uVar5 = (long)(int)uVar5 - 1;
      uVar7 = auStack_110[uVar5];
      iVar6 = aiStack_210[uVar5];
    }
    iVar2 = uVar7 + iVar6;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 1;
    }
    fVar17 = *(float *)(param_4 + (ulong)*(ushort *)
                                          (*(long *)(param_1 + (long)(iVar2 >> 1) * 8) + 0x1b8) * 8
                       + 4);
    iVar2 = iVar6;
    uVar3 = uVar7;
    while( true ) {
      lVar9 = 0;
      lVar10 = (long)(int)uVar3;
      do {
        lVar14 = *(long *)(param_1 + (long)(int)uVar3 * 8 + lVar9 * 8);
        lVar9 = lVar9 + 1;
      } while (fVar17 < *(float *)(param_4 + (ulong)*(ushort *)(lVar14 + 0x1b8) * 8 + 4));
      lVar12 = 0;
      do {
        lVar4 = *(long *)(param_1 + (long)iVar2 * 8 + lVar12 * 8);
        lVar12 = lVar12 + -1;
      } while (*(float *)(param_4 + (ulong)*(ushort *)(lVar4 + 0x1b8) * 8 + 4) < fVar17);
      iVar8 = (int)lVar9;
      iVar11 = (int)lVar12;
      if (iVar2 + iVar11 + 1 <= (int)(uVar3 + iVar8 + -1)) break;
      uVar3 = uVar3 + iVar8;
      *(long *)(param_1 + lVar10 * 8 + lVar9 * 8 + -8) = lVar4;
      *(long *)(param_1 + (long)iVar2 * 8 + lVar12 * 8 + 8) = lVar14;
      iVar2 = iVar2 + iVar11;
    }
    iVar13 = ~uVar7 + uVar3 + iVar8;
    iVar16 = ((iVar6 + -1) - iVar2) - iVar11;
    if (iVar16 < iVar13) {
      if (10 < iVar13) {
        uVar15 = -(uVar5 >> 0x1f & 1) & 0xfffffffc00000000 | (uVar5 & 0xffffffff) << 2;
        *(uint *)((long)auStack_110 + uVar15) = uVar7;
        uVar5 = (ulong)((int)uVar5 + 1);
        *(uint *)((long)aiStack_210 + uVar15) = uVar3 + iVar8 + -2;
      }
      uVar7 = iVar2 + iVar11 + 2;
    }
    else {
      if (10 < iVar16) {
        uVar15 = -(uVar5 >> 0x1f & 1) & 0xfffffffc00000000 | (uVar5 & 0xffffffff) << 2;
        uVar5 = (ulong)((int)uVar5 + 1);
        *(int *)((long)aiStack_210 + uVar15) = iVar6;
        *(int *)((long)auStack_110 + uVar15) = iVar2 + iVar11 + 2;
      }
      iVar6 = uVar3 + iVar8 + -2;
    }
  } while( true );
}

// ==== TOMQuickSort<Aska::RenderableObject, float, 64, 10>::Ascend(Aska::RenderableObject**, int, int, Aska::ObjectManager::RenderableObjectContext*)
// vaddr 0x21606a0 | ghidra 0x22606a0 | size 524 | symbol _ZN12TOMQuickSortIN4Aska16RenderableObjectEfLi64ELi10EE6AscendEPPS1_iiPNS0_13ObjectManager23RenderableObjectContextE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN12TOMQuickSortIN4Aska16RenderableObjectEfLi64ELi10EE6AscendEPPS1_iiPNS0_13ObjectManager23RenderableObjectContextE
               (long param_1,uint param_2,uint param_3,long param_4)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  ulong uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  long lVar9;
  long lVar10;
  int iVar11;
  long lVar12;
  int iVar13;
  long lVar14;
  ulong uVar15;
  int iVar16;
  float fVar17;
  int aiStack_210 [64];
  uint auStack_110 [64];
  
  if (param_2 == param_3) {
    return;
  }
  uVar5 = 0;
  iVar6 = param_3 - 1;
  uVar7 = param_2;
  do {
    if ((int)(iVar6 - uVar7) < 10) {
      if ((int)uVar5 == 0) {
        if ((int)param_3 <= (int)(param_2 + 1)) {
          return;
        }
        lVar9 = (long)(int)(param_2 + 1);
        uVar7 = param_2;
        do {
          lVar10 = *(long *)(param_1 + lVar9 * 8);
          uVar5 = (ulong)uVar7;
          if ((int)param_2 <= (int)uVar7) {
            fVar17 = *(float *)(param_4 + (ulong)*(ushort *)(lVar10 + 0x1b8) * 8 + 4);
            uVar15 = (long)(int)uVar7;
            do {
              lVar14 = *(long *)(param_1 + uVar15 * 8);
              if (*(float *)(param_4 + (ulong)*(ushort *)(lVar14 + 0x1b8) * 8 + 4) <= fVar17) {
                uVar5 = uVar15 & 0xffffffff;
                break;
              }
              uVar5 = uVar15 - 1;
              *(long *)(param_1 + uVar15 * 8 + 8) = lVar14;
              bVar1 = (long)(int)param_2 < (long)uVar15;
              uVar15 = uVar5;
            } while (bVar1);
          }
          lVar9 = lVar9 + 1;
          uVar7 = uVar7 + 1;
          *(long *)(param_1 + (long)((int)uVar5 + 1) * 8) = lVar10;
          if ((uint)lVar9 == param_3) {
            return;
          }
        } while( true );
      }
      uVar5 = (long)(int)uVar5 - 1;
      uVar7 = auStack_110[uVar5];
      iVar6 = aiStack_210[uVar5];
    }
    iVar2 = uVar7 + iVar6;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 1;
    }
    fVar17 = *(float *)(param_4 + (ulong)*(ushort *)
                                          (*(long *)(param_1 + (long)(iVar2 >> 1) * 8) + 0x1b8) * 8
                       + 4);
    iVar2 = iVar6;
    uVar3 = uVar7;
    while( true ) {
      lVar9 = 0;
      lVar10 = (long)(int)uVar3;
      do {
        lVar14 = *(long *)(param_1 + (long)(int)uVar3 * 8 + lVar9 * 8);
        lVar9 = lVar9 + 1;
      } while (*(float *)(param_4 + (ulong)*(ushort *)(lVar14 + 0x1b8) * 8 + 4) < fVar17);
      lVar12 = 0;
      do {
        lVar4 = *(long *)(param_1 + (long)iVar2 * 8 + lVar12 * 8);
        lVar12 = lVar12 + -1;
      } while (fVar17 < *(float *)(param_4 + (ulong)*(ushort *)(lVar4 + 0x1b8) * 8 + 4));
      iVar8 = (int)lVar9;
      iVar11 = (int)lVar12;
      if (iVar2 + iVar11 + 1 <= (int)(uVar3 + iVar8 + -1)) break;
      uVar3 = uVar3 + iVar8;
      *(long *)(param_1 + lVar10 * 8 + lVar9 * 8 + -8) = lVar4;
      *(long *)(param_1 + (long)iVar2 * 8 + lVar12 * 8 + 8) = lVar14;
      iVar2 = iVar2 + iVar11;
    }
    iVar13 = ~uVar7 + uVar3 + iVar8;
    iVar16 = ((iVar6 + -1) - iVar2) - iVar11;
    if (iVar16 < iVar13) {
      if (10 < iVar13) {
        uVar15 = -(uVar5 >> 0x1f & 1) & 0xfffffffc00000000 | (uVar5 & 0xffffffff) << 2;
        *(uint *)((long)auStack_110 + uVar15) = uVar7;
        uVar5 = (ulong)((int)uVar5 + 1);
        *(uint *)((long)aiStack_210 + uVar15) = uVar3 + iVar8 + -2;
      }
      uVar7 = iVar2 + iVar11 + 2;
    }
    else {
      if (10 < iVar16) {
        uVar15 = -(uVar5 >> 0x1f & 1) & 0xfffffffc00000000 | (uVar5 & 0xffffffff) << 2;
        uVar5 = (ulong)((int)uVar5 + 1);
        *(int *)((long)aiStack_210 + uVar15) = iVar6;
        *(int *)((long)auStack_110 + uVar15) = iVar2 + iVar11 + 2;
      }
      iVar6 = uVar3 + iVar8 + -2;
    }
  } while( true );
}

// ==== Aska::TArrayQuickSort<Aska::Occluder, float, 64, 10>::Ascend(Aska::Occluder**, int, int)
// vaddr 0x216d440 | ghidra 0x226d440 | size 484 | symbol _ZN4Aska15TArrayQuickSortINS_8OccluderEfLi64ELi10EE6AscendEPPS1_ii | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TArrayQuickSortINS_8OccluderEfLi64ELi10EE6AscendEPPS1_ii
               (long param_1,uint param_2,uint param_3)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  ulong uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  long lVar9;
  long lVar10;
  int iVar11;
  long lVar12;
  int iVar13;
  long lVar14;
  ulong uVar15;
  int iVar16;
  float fVar17;
  int aiStack_210 [64];
  uint auStack_110 [64];
  
  if (param_2 == param_3) {
    return;
  }
  uVar5 = 0;
  iVar6 = param_3 - 1;
  uVar7 = param_2;
  do {
    if ((int)(iVar6 - uVar7) < 10) {
      if ((int)uVar5 == 0) {
        if ((int)param_3 <= (int)(param_2 + 1)) {
          return;
        }
        lVar9 = (long)(int)(param_2 + 1);
        uVar7 = param_2;
        do {
          lVar10 = *(long *)(param_1 + lVar9 * 8);
          uVar5 = (ulong)uVar7;
          if ((int)param_2 <= (int)uVar7) {
            fVar17 = *(float *)(lVar10 + 0x1a4);
            uVar15 = (long)(int)uVar7;
            do {
              lVar14 = *(long *)(param_1 + uVar15 * 8);
              if (*(float *)(lVar14 + 0x1a4) <= fVar17) {
                uVar5 = uVar15 & 0xffffffff;
                break;
              }
              uVar5 = uVar15 - 1;
              *(long *)(param_1 + uVar15 * 8 + 8) = lVar14;
              bVar1 = (long)(int)param_2 < (long)uVar15;
              uVar15 = uVar5;
            } while (bVar1);
          }
          lVar9 = lVar9 + 1;
          uVar7 = uVar7 + 1;
          *(long *)(param_1 + (long)((int)uVar5 + 1) * 8) = lVar10;
          if ((uint)lVar9 == param_3) {
            return;
          }
        } while( true );
      }
      uVar5 = (long)(int)uVar5 - 1;
      uVar7 = auStack_110[uVar5];
      iVar6 = aiStack_210[uVar5];
    }
    iVar2 = uVar7 + iVar6;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 1;
    }
    fVar17 = *(float *)(*(long *)(param_1 + (long)(iVar2 >> 1) * 8) + 0x1a4);
    iVar2 = iVar6;
    uVar3 = uVar7;
    while( true ) {
      lVar9 = 0;
      lVar10 = (long)(int)uVar3;
      do {
        lVar14 = *(long *)(param_1 + (long)(int)uVar3 * 8 + lVar9 * 8);
        lVar9 = lVar9 + 1;
      } while (*(float *)(lVar14 + 0x1a4) < fVar17);
      lVar12 = 0;
      do {
        lVar4 = *(long *)(param_1 + (long)iVar2 * 8 + lVar12 * 8);
        lVar12 = lVar12 + -1;
      } while (fVar17 < *(float *)(lVar4 + 0x1a4));
      iVar8 = (int)lVar9;
      iVar11 = (int)lVar12;
      if (iVar2 + iVar11 + 1 <= (int)(uVar3 + iVar8 + -1)) break;
      uVar3 = uVar3 + iVar8;
      *(long *)(param_1 + lVar10 * 8 + lVar9 * 8 + -8) = lVar4;
      *(long *)(param_1 + (long)iVar2 * 8 + lVar12 * 8 + 8) = lVar14;
      iVar2 = iVar2 + iVar11;
    }
    iVar13 = ~uVar7 + uVar3 + iVar8;
    iVar16 = ((iVar6 + -1) - iVar2) - iVar11;
    if (iVar16 < iVar13) {
      if (10 < iVar13) {
        uVar15 = -(uVar5 >> 0x1f & 1) & 0xfffffffc00000000 | (uVar5 & 0xffffffff) << 2;
        *(uint *)((long)auStack_110 + uVar15) = uVar7;
        uVar5 = (ulong)((int)uVar5 + 1);
        *(uint *)((long)aiStack_210 + uVar15) = uVar3 + iVar8 + -2;
      }
      uVar7 = iVar2 + iVar11 + 2;
    }
    else {
      if (10 < iVar16) {
        uVar15 = -(uVar5 >> 0x1f & 1) & 0xfffffffc00000000 | (uVar5 & 0xffffffff) << 2;
        uVar5 = (ulong)((int)uVar5 + 1);
        *(int *)((long)aiStack_210 + uVar15) = iVar6;
        *(int *)((long)auStack_110 + uVar15) = iVar2 + iVar11 + 2;
      }
      iVar6 = uVar3 + iVar8 + -2;
    }
  } while( true );
}

// ==== Aska::TArrayIterator<Aska::TDynamicArray<unsigned char, Aska::TAllocator<unsigned char> > > Aska::TDynamicArray<unsigned char, Aska::TAllocator<unsigned char> >::Insert_<Aska::Memory::TUninitializedFillN<unsigned char> >(unsigned char const*, unsigned long, Aska::Memory::TUninitializedFillN<unsigned char> const&)
// vaddr 0x217f980 | ghidra 0x227f980 | size 760 | symbol _ZN4Aska13TDynamicArrayIhNS_10TAllocatorIhEEE7Insert_INS_6Memory19TUninitializedFillNIhEEEENS_14TArrayIteratorIS3_EEPKhmRKT_ | lib libSOA-3.7.0.so | 2026-10-04
undefined1 *
_ZN4Aska13TDynamicArrayIhNS_10TAllocatorIhEEE7Insert_INS_6Memory19TUninitializedFillNIhEEEENS_14TArrayIteratorIS3_EEPKhmRKT_
          (long param_1,undefined1 *param_2,long param_3,ulong *param_4)

{
  undefined1 uVar1;
  undefined8 *puVar2;
  bool bVar3;
  undefined1 *puVar4;
  ulong uVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined8 *puVar8;
  undefined1 *puVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  ulong uVar13;
  undefined8 *puVar14;
  ulong uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  
  if (param_3 == 0) {
    return param_2;
  }
  puVar4 = *(undefined1 **)(param_1 + 0x10);
  puVar9 = puVar4 + (param_3 - *(long *)(param_1 + 8));
  puVar6 = (undefined1 *)(*(long *)(param_1 + 0x18) - *(long *)(param_1 + 8));
  if (puVar9 <= puVar6) {
    while (puVar4 != param_2) {
      puVar4[param_3 + -1] = puVar4[-1];
      puVar4 = puVar4 + -1;
    }
    uVar5 = *param_4;
    if (uVar5 != 0) {
      puVar4 = (undefined1 *)param_4[1];
      puVar9 = param_2;
      if (((0x1f < uVar5) && (uVar13 = uVar5 & 0xffffffffffffffe0, uVar13 != 0)) &&
         ((puVar4 + 1 <= param_2 || (param_2 + uVar5 <= puVar4)))) {
        uVar1 = *puVar4;
        uVar16 = CONCAT17(uVar1,CONCAT16(uVar1,CONCAT15(uVar1,CONCAT14(uVar1,CONCAT13(uVar1,CONCAT12
                                                  (uVar1,CONCAT11(uVar1,uVar1)))))));
        uVar17 = CONCAT17(uVar1,CONCAT16(uVar1,CONCAT15(uVar1,CONCAT14(uVar1,CONCAT13(uVar1,CONCAT12
                                                  (uVar1,CONCAT11(uVar1,uVar1)))))));
        puVar8 = (undefined8 *)(param_2 + 0x10);
        uVar15 = uVar13;
        do {
          puVar8[-1] = uVar17;
          puVar8[-2] = uVar16;
          puVar8[1] = uVar17;
          *puVar8 = uVar16;
          uVar15 = uVar15 - 0x20;
          puVar8 = puVar8 + 4;
        } while (uVar15 != 0);
        bVar3 = uVar5 == uVar13;
        uVar5 = uVar5 - uVar13;
        puVar9 = param_2 + uVar13;
        if (bVar3) goto code_r0x0227fb04;
      }
      do {
        uVar5 = uVar5 - 1;
        *puVar9 = *puVar4;
        puVar9 = puVar9 + 1;
      } while (uVar5 != 0);
    }
code_r0x0227fb04:
    *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + param_3;
    return param_2;
  }
  puVar6 = (undefined1 *)((long)puVar6 * 2);
  if (puVar9 <= puVar6) {
    puVar9 = puVar6;
  }
  puVar4 = (undefined1 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(puVar9,1);
  if (puVar4 == (undefined1 *)0x0) {
    return param_2;
  }
  puVar7 = *(undefined1 **)(param_1 + 8);
  puVar6 = puVar4;
  if (puVar7 != param_2) {
    uVar5 = (long)param_2 - (long)puVar7;
    if (((uVar5 < 0x20) || (uVar13 = uVar5 & 0xffffffffffffffe0, uVar13 == 0)) ||
       ((puVar4 < param_2 && (puVar7 < puVar4 + uVar5)))) {
code_r0x0227fb18:
      do {
        puVar10 = puVar7 + 1;
        *puVar6 = *puVar7;
        puVar6 = puVar6 + 1;
        puVar7 = puVar10;
      } while (param_2 != puVar10);
    }
    else {
      puVar8 = (undefined8 *)(puVar7 + 0x10);
      puVar14 = (undefined8 *)(puVar4 + 0x10);
      uVar15 = uVar13;
      do {
        puVar2 = puVar8 + -1;
        uVar16 = puVar8[-2];
        uVar18 = puVar8[1];
        uVar17 = *puVar8;
        puVar8 = puVar8 + 4;
        uVar15 = uVar15 - 0x20;
        puVar14[-1] = *puVar2;
        puVar14[-2] = uVar16;
        puVar14[1] = uVar18;
        *puVar14 = uVar17;
        puVar14 = puVar14 + 4;
      } while (uVar15 != 0);
      puVar6 = puVar4 + uVar13;
      puVar7 = puVar7 + uVar13;
      if (uVar5 != uVar13) goto code_r0x0227fb18;
    }
    puVar6 = puVar4 + uVar5;
  }
  uVar5 = *param_4;
  if (uVar5 != 0) {
    puVar10 = (undefined1 *)param_4[1];
    puVar7 = puVar6;
    if (((0x1f < uVar5) && (uVar13 = uVar5 & 0xffffffffffffffe0, uVar13 != 0)) &&
       ((puVar10 + 1 <= puVar6 || (puVar6 + uVar5 <= puVar10)))) {
      uVar1 = *puVar10;
      uVar16 = CONCAT17(uVar1,CONCAT16(uVar1,CONCAT15(uVar1,CONCAT14(uVar1,CONCAT13(uVar1,CONCAT12(
                                                  uVar1,CONCAT11(uVar1,uVar1)))))));
      uVar17 = CONCAT17(uVar1,CONCAT16(uVar1,CONCAT15(uVar1,CONCAT14(uVar1,CONCAT13(uVar1,CONCAT12(
                                                  uVar1,CONCAT11(uVar1,uVar1)))))));
      puVar8 = (undefined8 *)(puVar6 + 0x10);
      uVar15 = uVar13;
      do {
        puVar8[-1] = uVar17;
        puVar8[-2] = uVar16;
        puVar8[1] = uVar17;
        *puVar8 = uVar16;
        uVar15 = uVar15 - 0x20;
        puVar8 = puVar8 + 4;
      } while (uVar15 != 0);
      bVar3 = uVar5 == uVar13;
      uVar5 = uVar5 - uVar13;
      puVar7 = puVar6 + uVar13;
      if (bVar3) goto code_r0x0227fbb4;
    }
    do {
      uVar5 = uVar5 - 1;
      *puVar7 = *puVar10;
      puVar7 = puVar7 + 1;
    } while (uVar5 != 0);
  }
code_r0x0227fbb4:
  puVar10 = *(undefined1 **)(param_1 + 0x10);
  puVar7 = puVar6 + param_3;
  uVar5 = (long)puVar10 - (long)param_2;
  if (uVar5 == 0) goto code_r0x0227fc0c;
  puVar11 = puVar7;
  if (((uVar5 < 0x20) || (uVar13 = uVar5 & 0xffffffffffffffe0, uVar13 == 0)) ||
     ((puVar7 < puVar10 && (param_2 < puVar6 + (long)(puVar10 + (param_3 - (long)param_2)))))) {
code_r0x0227fbf8:
    do {
      puVar12 = param_2 + 1;
      *puVar11 = *param_2;
      puVar11 = puVar11 + 1;
      param_2 = puVar12;
    } while (puVar10 != puVar12);
  }
  else {
    puVar8 = (undefined8 *)(param_2 + 0x10);
    puVar14 = (undefined8 *)(puVar6 + param_3 + 0x10);
    uVar15 = uVar13;
    do {
      puVar2 = puVar8 + -1;
      uVar16 = puVar8[-2];
      uVar18 = puVar8[1];
      uVar17 = *puVar8;
      puVar8 = puVar8 + 4;
      uVar15 = uVar15 - 0x20;
      puVar14[-1] = *puVar2;
      puVar14[-2] = uVar16;
      puVar14[1] = uVar18;
      *puVar14 = uVar17;
      puVar14 = puVar14 + 4;
    } while (uVar15 != 0);
    puVar11 = puVar7 + uVar13;
    param_2 = param_2 + uVar13;
    if (uVar5 != uVar13) goto code_r0x0227fbf8;
  }
  puVar7 = puVar7 + uVar5;
code_r0x0227fc0c:
  Aska::MemoryManagerAdapter::AlignedFree(void*)(*(undefined8 *)(param_1 + 8));
  *(undefined1 **)(param_1 + 8) = puVar4;
  *(undefined1 **)(param_1 + 0x10) = puVar7;
  *(undefined1 **)(param_1 + 0x18) = puVar4 + (long)puVar9;
  return puVar6;
}

// ==== Aska::TArrayIterator<Aska::TDynamicArray<Aska::ShaderKeyValue*, Aska::TAllocator<Aska::ShaderKeyValue*> > > Aska::TDynamicArray<Aska::ShaderKeyValue*, Aska::TAllocator<Aska::ShaderKeyValue*> >::Insert_<Aska::Memory::TUninitializedFillN<Aska::ShaderKeyValue*> >(Aska::ShaderKeyValue* const*, unsigned long, Aska::Memory::TUninitializedFillN<Aska::ShaderKeyValue*> const&)
// vaddr 0x217fc78 | ghidra 0x227fc78 | size 872 | symbol _ZN4Aska13TDynamicArrayIPNS_14ShaderKeyValueENS_10TAllocatorIS2_EEE7Insert_INS_6Memory19TUninitializedFillNIS2_EEEENS_14TArrayIteratorIS5_EEPKS2_mRKT_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 *
_ZN4Aska13TDynamicArrayIPNS_14ShaderKeyValueENS_10TAllocatorIS2_EEE7Insert_INS_6Memory19TUninitializedFillNIS2_EEEENS_14TArrayIteratorIS5_EEPKS2_mRKT_
          (long param_1,undefined8 *param_2,long param_3,ulong *param_4)

{
  undefined8 *puVar1;
  bool bVar2;
  undefined8 *puVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  long lVar9;
  undefined8 *puVar10;
  ulong uVar11;
  undefined8 *puVar12;
  ulong uVar13;
  undefined8 *puVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  
  if (param_3 == 0) {
    return param_2;
  }
  puVar3 = *(undefined8 **)(param_1 + 0x10);
  uVar6 = param_3 + ((long)puVar3 - *(long *)(param_1 + 8) >> 3);
  lVar9 = *(long *)(param_1 + 0x18) - *(long *)(param_1 + 8);
  if (uVar6 <= (ulong)(lVar9 >> 3)) {
    while (puVar3 != param_2) {
      puVar3[param_3 + -1] = puVar3[-1];
      puVar3 = puVar3 + -1;
    }
    uVar6 = *param_4;
    if (uVar6 != 0) {
      puVar7 = (undefined8 *)param_4[1];
      puVar3 = param_2;
      if (((3 < uVar6) && (uVar4 = uVar6 & 0xfffffffffffffffc, uVar4 != 0)) &&
         (((undefined8 *)((long)puVar7 + 1U) <= param_2 || (param_2 + uVar6 <= puVar7)))) {
        uVar15 = *puVar7;
        puVar3 = param_2 + 2;
        uVar5 = uVar4;
        do {
          puVar3[-1] = uVar15;
          puVar3[-2] = uVar15;
          puVar3[1] = uVar15;
          *puVar3 = uVar15;
          uVar5 = uVar5 - 4;
          puVar3 = puVar3 + 4;
        } while (uVar5 != 0);
        bVar2 = uVar6 == uVar4;
        uVar6 = uVar6 - uVar4;
        puVar3 = param_2 + uVar4;
        if (bVar2) goto code_r0x0227fdc4;
      }
      do {
        uVar6 = uVar6 - 1;
        *puVar3 = *puVar7;
        puVar3 = puVar3 + 1;
      } while (uVar6 != 0);
    }
code_r0x0227fdc4:
    *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + param_3 * 8;
    return param_2;
  }
  uVar4 = lVar9 >> 2;
  if (uVar6 <= uVar4) {
    uVar6 = uVar4;
  }
  if (uVar6 >> 0x3d != 0) {
    return param_2;
  }
  puVar3 = (undefined8 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(uVar6 << 3,8);
  if (puVar3 == (undefined8 *)0x0) {
    return param_2;
  }
  puVar7 = *(undefined8 **)(param_1 + 8);
  if (puVar7 == param_2) {
    uVar4 = *param_4;
    puVar7 = puVar3;
  }
  else {
    uVar5 = (long)param_2 + (-8 - (long)puVar7);
    uVar4 = (uVar5 >> 3) + 1;
    puVar10 = puVar3;
    if (((uVar4 < 4) || (uVar11 = uVar4 & 0x3ffffffffffffffc, uVar11 == 0)) ||
       ((puVar3 < (undefined8 *)((long)puVar7 + (uVar5 & 0xfffffffffffffff8) + 8) &&
        (puVar7 < (undefined8 *)((long)puVar3 + (uVar5 + 8 & 0xfffffffffffffff8)))))) {
code_r0x0227fe48:
      do {
        puVar8 = puVar7 + 1;
        *puVar10 = *puVar7;
        puVar7 = puVar8;
        puVar10 = puVar10 + 1;
      } while (param_2 != puVar8);
    }
    else {
      puVar10 = puVar7 + 2;
      puVar7 = puVar7 + uVar11;
      puVar8 = puVar3 + 2;
      uVar13 = uVar11;
      do {
        puVar12 = puVar10 + -1;
        uVar15 = puVar10[-2];
        uVar17 = puVar10[1];
        uVar16 = *puVar10;
        puVar10 = puVar10 + 4;
        uVar13 = uVar13 - 4;
        puVar8[-1] = *puVar12;
        puVar8[-2] = uVar15;
        puVar8[1] = uVar17;
        *puVar8 = uVar16;
        puVar8 = puVar8 + 4;
      } while (uVar13 != 0);
      puVar10 = puVar3 + uVar11;
      if (uVar4 != uVar11) goto code_r0x0227fe48;
    }
    puVar7 = (undefined8 *)((long)puVar3 + (uVar5 & 0xfffffffffffffff8) + 8);
    uVar4 = *param_4;
  }
  if (uVar4 != 0) {
    puVar8 = (undefined8 *)param_4[1];
    puVar10 = puVar7;
    if (((3 < uVar4) && (uVar5 = uVar4 & 0xfffffffffffffffc, uVar5 != 0)) &&
       (((undefined8 *)((long)puVar8 + 1U) <= puVar7 || (puVar7 + uVar4 <= puVar8)))) {
      uVar15 = *puVar8;
      puVar10 = puVar7 + 2;
      uVar11 = uVar5;
      do {
        puVar10[-1] = uVar15;
        puVar10[-2] = uVar15;
        puVar10[1] = uVar15;
        *puVar10 = uVar15;
        uVar11 = uVar11 - 4;
        puVar10 = puVar10 + 4;
      } while (uVar11 != 0);
      bVar2 = uVar4 == uVar5;
      uVar4 = uVar4 - uVar5;
      puVar10 = puVar7 + uVar5;
      if (bVar2) goto code_r0x0227feec;
    }
    do {
      uVar4 = uVar4 - 1;
      *puVar10 = *puVar8;
      puVar10 = puVar10 + 1;
    } while (uVar4 != 0);
  }
code_r0x0227feec:
  puVar8 = *(undefined8 **)(param_1 + 0x10);
  puVar10 = puVar7 + param_3;
  if (puVar8 == param_2) goto code_r0x0227ffb0;
  uVar5 = (long)puVar8 + (-8 - (long)param_2);
  uVar11 = uVar5 >> 3;
  uVar4 = uVar11 + 1;
  puVar12 = puVar10;
  if (((uVar4 < 4) || (uVar13 = uVar4 & 0x3ffffffffffffffc, uVar13 == 0)) ||
     ((puVar10 < param_2 + uVar11 + 1 && (param_2 < puVar7 + uVar11 + param_3 + 1)))) {
code_r0x0227ff94:
    do {
      puVar14 = param_2 + 1;
      *puVar12 = *param_2;
      puVar12 = puVar12 + 1;
      param_2 = puVar14;
    } while (puVar8 != puVar14);
  }
  else {
    puVar12 = param_2 + 2;
    param_2 = param_2 + uVar13;
    puVar14 = puVar7 + param_3 + 2;
    uVar11 = uVar13;
    do {
      puVar1 = puVar12 + -1;
      uVar15 = puVar12[-2];
      uVar17 = puVar12[1];
      uVar16 = *puVar12;
      puVar12 = puVar12 + 4;
      uVar11 = uVar11 - 4;
      puVar14[-1] = *puVar1;
      puVar14[-2] = uVar15;
      puVar14[1] = uVar17;
      *puVar14 = uVar16;
      puVar14 = puVar14 + 4;
    } while (uVar11 != 0);
    puVar12 = puVar10 + uVar13;
    if (uVar4 != uVar13) goto code_r0x0227ff94;
  }
  puVar10 = (undefined8 *)((long)puVar10 + (uVar5 & 0xfffffffffffffff8) + 8);
code_r0x0227ffb0:
  Aska::MemoryManagerAdapter::AlignedFree(void*)(*(undefined8 *)(param_1 + 8));
  *(undefined8 **)(param_1 + 8) = puVar3;
  *(undefined8 **)(param_1 + 0x10) = puVar10;
  *(undefined8 **)(param_1 + 0x18) = puVar3 + uVar6;
  return puVar7;
}

// ==== Aska::TArrayIterator<Aska::TDynamicArray<Aska::ShaderProgramValue*, Aska::TAllocator<Aska::ShaderProgramValue*> > > Aska::TDynamicArray<Aska::ShaderProgramValue*, Aska::TAllocator<Aska::ShaderProgramValue*> >::Insert_<Aska::Memory::TUninitializedFillN<Aska::ShaderProgramValue*> >(Aska::ShaderProgramValue* const*, unsigned long, Aska::Memory::TUninitializedFillN<Aska::ShaderProgramValue*> const&)
// vaddr 0x2180d80 | ghidra 0x2280d80 | size 872 | symbol _ZN4Aska13TDynamicArrayIPNS_18ShaderProgramValueENS_10TAllocatorIS2_EEE7Insert_INS_6Memory19TUninitializedFillNIS2_EEEENS_14TArrayIteratorIS5_EEPKS2_mRKT_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 *
_ZN4Aska13TDynamicArrayIPNS_18ShaderProgramValueENS_10TAllocatorIS2_EEE7Insert_INS_6Memory19TUninitializedFillNIS2_EEEENS_14TArrayIteratorIS5_EEPKS2_mRKT_
          (long param_1,undefined8 *param_2,long param_3,ulong *param_4)

{
  undefined8 *puVar1;
  bool bVar2;
  undefined8 *puVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  long lVar9;
  undefined8 *puVar10;
  ulong uVar11;
  undefined8 *puVar12;
  ulong uVar13;
  undefined8 *puVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  
  if (param_3 == 0) {
    return param_2;
  }
  puVar3 = *(undefined8 **)(param_1 + 0x10);
  uVar6 = param_3 + ((long)puVar3 - *(long *)(param_1 + 8) >> 3);
  lVar9 = *(long *)(param_1 + 0x18) - *(long *)(param_1 + 8);
  if (uVar6 <= (ulong)(lVar9 >> 3)) {
    while (puVar3 != param_2) {
      puVar3[param_3 + -1] = puVar3[-1];
      puVar3 = puVar3 + -1;
    }
    uVar6 = *param_4;
    if (uVar6 != 0) {
      puVar7 = (undefined8 *)param_4[1];
      puVar3 = param_2;
      if (((3 < uVar6) && (uVar4 = uVar6 & 0xfffffffffffffffc, uVar4 != 0)) &&
         (((undefined8 *)((long)puVar7 + 1U) <= param_2 || (param_2 + uVar6 <= puVar7)))) {
        uVar15 = *puVar7;
        puVar3 = param_2 + 2;
        uVar5 = uVar4;
        do {
          puVar3[-1] = uVar15;
          puVar3[-2] = uVar15;
          puVar3[1] = uVar15;
          *puVar3 = uVar15;
          uVar5 = uVar5 - 4;
          puVar3 = puVar3 + 4;
        } while (uVar5 != 0);
        bVar2 = uVar6 == uVar4;
        uVar6 = uVar6 - uVar4;
        puVar3 = param_2 + uVar4;
        if (bVar2) goto code_r0x02280ecc;
      }
      do {
        uVar6 = uVar6 - 1;
        *puVar3 = *puVar7;
        puVar3 = puVar3 + 1;
      } while (uVar6 != 0);
    }
code_r0x02280ecc:
    *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + param_3 * 8;
    return param_2;
  }
  uVar4 = lVar9 >> 2;
  if (uVar6 <= uVar4) {
    uVar6 = uVar4;
  }
  if (uVar6 >> 0x3d != 0) {
    return param_2;
  }
  puVar3 = (undefined8 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(uVar6 << 3,8);
  if (puVar3 == (undefined8 *)0x0) {
    return param_2;
  }
  puVar7 = *(undefined8 **)(param_1 + 8);
  if (puVar7 == param_2) {
    uVar4 = *param_4;
    puVar7 = puVar3;
  }
  else {
    uVar5 = (long)param_2 + (-8 - (long)puVar7);
    uVar4 = (uVar5 >> 3) + 1;
    puVar10 = puVar3;
    if (((uVar4 < 4) || (uVar11 = uVar4 & 0x3ffffffffffffffc, uVar11 == 0)) ||
       ((puVar3 < (undefined8 *)((long)puVar7 + (uVar5 & 0xfffffffffffffff8) + 8) &&
        (puVar7 < (undefined8 *)((long)puVar3 + (uVar5 + 8 & 0xfffffffffffffff8)))))) {
code_r0x02280f50:
      do {
        puVar8 = puVar7 + 1;
        *puVar10 = *puVar7;
        puVar7 = puVar8;
        puVar10 = puVar10 + 1;
      } while (param_2 != puVar8);
    }
    else {
      puVar10 = puVar7 + 2;
      puVar7 = puVar7 + uVar11;
      puVar8 = puVar3 + 2;
      uVar13 = uVar11;
      do {
        puVar12 = puVar10 + -1;
        uVar15 = puVar10[-2];
        uVar17 = puVar10[1];
        uVar16 = *puVar10;
        puVar10 = puVar10 + 4;
        uVar13 = uVar13 - 4;
        puVar8[-1] = *puVar12;
        puVar8[-2] = uVar15;
        puVar8[1] = uVar17;
        *puVar8 = uVar16;
        puVar8 = puVar8 + 4;
      } while (uVar13 != 0);
      puVar10 = puVar3 + uVar11;
      if (uVar4 != uVar11) goto code_r0x02280f50;
    }
    puVar7 = (undefined8 *)((long)puVar3 + (uVar5 & 0xfffffffffffffff8) + 8);
    uVar4 = *param_4;
  }
  if (uVar4 != 0) {
    puVar8 = (undefined8 *)param_4[1];
    puVar10 = puVar7;
    if (((3 < uVar4) && (uVar5 = uVar4 & 0xfffffffffffffffc, uVar5 != 0)) &&
       (((undefined8 *)((long)puVar8 + 1U) <= puVar7 || (puVar7 + uVar4 <= puVar8)))) {
      uVar15 = *puVar8;
      puVar10 = puVar7 + 2;
      uVar11 = uVar5;
      do {
        puVar10[-1] = uVar15;
        puVar10[-2] = uVar15;
        puVar10[1] = uVar15;
        *puVar10 = uVar15;
        uVar11 = uVar11 - 4;
        puVar10 = puVar10 + 4;
      } while (uVar11 != 0);
      bVar2 = uVar4 == uVar5;
      uVar4 = uVar4 - uVar5;
      puVar10 = puVar7 + uVar5;
      if (bVar2) goto code_r0x02280ff4;
    }
    do {
      uVar4 = uVar4 - 1;
      *puVar10 = *puVar8;
      puVar10 = puVar10 + 1;
    } while (uVar4 != 0);
  }
code_r0x02280ff4:
  puVar8 = *(undefined8 **)(param_1 + 0x10);
  puVar10 = puVar7 + param_3;
  if (puVar8 == param_2) goto code_r0x022810b8;
  uVar5 = (long)puVar8 + (-8 - (long)param_2);
  uVar11 = uVar5 >> 3;
  uVar4 = uVar11 + 1;
  puVar12 = puVar10;
  if (((uVar4 < 4) || (uVar13 = uVar4 & 0x3ffffffffffffffc, uVar13 == 0)) ||
     ((puVar10 < param_2 + uVar11 + 1 && (param_2 < puVar7 + uVar11 + param_3 + 1)))) {
code_r0x0228109c:
    do {
      puVar14 = param_2 + 1;
      *puVar12 = *param_2;
      puVar12 = puVar12 + 1;
      param_2 = puVar14;
    } while (puVar8 != puVar14);
  }
  else {
    puVar12 = param_2 + 2;
    param_2 = param_2 + uVar13;
    puVar14 = puVar7 + param_3 + 2;
    uVar11 = uVar13;
    do {
      puVar1 = puVar12 + -1;
      uVar15 = puVar12[-2];
      uVar17 = puVar12[1];
      uVar16 = *puVar12;
      puVar12 = puVar12 + 4;
      uVar11 = uVar11 - 4;
      puVar14[-1] = *puVar1;
      puVar14[-2] = uVar15;
      puVar14[1] = uVar17;
      *puVar14 = uVar16;
      puVar14 = puVar14 + 4;
    } while (uVar11 != 0);
    puVar12 = puVar10 + uVar13;
    if (uVar4 != uVar13) goto code_r0x0228109c;
  }
  puVar10 = (undefined8 *)((long)puVar10 + (uVar5 & 0xfffffffffffffff8) + 8);
code_r0x022810b8:
  Aska::MemoryManagerAdapter::AlignedFree(void*)(*(undefined8 *)(param_1 + 8));
  *(undefined8 **)(param_1 + 8) = puVar3;
  *(undefined8 **)(param_1 + 0x10) = puVar10;
  *(undefined8 **)(param_1 + 0x18) = puVar3 + uVar6;
  return puVar7;
}

// ==== Aska::TArray<Aska::ASKA_OGL_STATESET0*, false>::Resize(long, bool)
// vaddr 0x21815fc | ghidra 0x22815fc | size 252 | symbol _ZN4Aska6TArrayIPNS_18ASKA_OGL_STATESET0ELb0EE6ResizeElb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIPNS_18ASKA_OGL_STATESET0ELb0EE6ResizeElb(long param_1,long param_2)

{
  long lVar1;
  ushort uVar2;
  long lVar3;
  
  if (param_2 == 0) {
    if ((*(byte *)(param_1 + 0x32) & 1) != 0) {
      if (*(long *)(param_1 + 8) != 0) {
        operator delete[](void*)();
        *(undefined8 *)(param_1 + 8) = 0;
      }
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  lVar3 = *(long *)(param_1 + 0x10);
  if (lVar3 < param_2) {
    lVar3 = param_2 << 1;
  }
  else {
    lVar1 = lVar3 + 3;
    if (-1 < lVar3) {
      lVar1 = lVar3;
    }
    if (((lVar1 >> 2 < param_2) || ((*(ushort *)(param_1 + 0x32) & 1) == 0)) ||
       (lVar3 = param_2 * 2,
       lVar3 - *(long *)(param_1 + 0x28) == 0 || lVar3 < *(long *)(param_1 + 0x28)))
    goto code_r0x022816dc;
  }
  if (*(long *)(param_1 + 8) == 0) {
    lVar3 = *(long *)(param_1 + 0x28);
    if (*(long *)(param_1 + 0x28) <= param_2) {
      lVar3 = param_2;
    }
    lVar1 = operator new[](unsigned long, std::nothrow_t const&)(lVar3 << 3,PTR__ZSt7nothrow_02cb9a80);
    *(long *)(param_1 + 8) = lVar1;
    if (lVar1 == 0) {
      *(ushort *)(param_1 + 0x30) = *(ushort *)(param_1 + 0x30) | 1;
      return;
    }
    uVar2 = *(ushort *)(param_1 + 0x30) & 0xfffe;
code_r0x022816d4:
    *(ushort *)(param_1 + 0x30) = uVar2;
  }
  else {
    lVar1 = operator new[](unsigned long, void*, unsigned long)(param_2 << 4,*(long *)(param_1 + 8),4);
    if (lVar1 == 0) {
      uVar2 = *(ushort *)(param_1 + 0x30) | 1;
      goto code_r0x022816d4;
    }
    *(long *)(param_1 + 8) = lVar1;
    *(long *)(param_1 + 0x10) = lVar3;
    *(long *)(param_1 + 0x18) = param_2;
  }
  *(long *)(param_1 + 0x10) = lVar3;
code_r0x022816dc:
  *(long *)(param_1 + 0x18) = param_2;
  return;
}

// ==== Aska::TMultipleBuffer<true>::CreateBuffer(bool, Aska::GpuResource*, int, Aska::GPURESOURCECREATION*, Aska::IGpuResourceHandler*)
// vaddr 0x21ebecc | ghidra 0x22ebecc | size 560 | symbol _ZN4Aska15TMultipleBufferILb1EE12CreateBufferEbPNS_11GpuResourceEiPNS_19GPURESOURCECREATIONEPNS_19IGpuResourceHandlerE | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska15TMultipleBufferILb1EE12CreateBufferEbPNS_11GpuResourceEiPNS_19GPURESOURCECREATIONEPNS_19IGpuResourceHandlerE
          (long *param_1,ulong param_2,long param_3,undefined4 param_4,undefined8 *param_5,
          long param_6)

{
  int *piVar1;
  uint *puVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  long lVar6;
  undefined8 *puVar7;
  long lVar8;
  uint *puVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  undefined8 uVar14;
  
  if (param_6 == 0) {
    return 0;
  }
  if (param_3 == 0) {
    lVar6 = *(long *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0;
    DataMemoryBarrier(2,3);
    piVar1 = (int *)(lVar6 + 0xea9fc);
    if (*piVar1 < 8000) {
      puVar2 = (uint *)(lVar6 + 0xea9f8);
      uVar11 = *puVar2;
      uVar10 = uVar11 + 0x1f;
      if (-1 < (int)uVar11) {
        uVar10 = uVar11;
      }
      puVar9 = (uint *)(lVar6 + (long)((int)uVar10 >> 5) * 4 + 8);
      uVar10 = *puVar9;
      uVar13 = 1 << (ulong)(uVar11 & 0x1f);
      uVar12 = uVar13 | uVar10;
      do {
        uVar3 = 0;
        if ((int)uVar11 < 8000) {
          uVar3 = uVar11;
        }
        if ((uVar13 & uVar10) == 0) {
          do {
            uVar11 = *puVar9;
            if (uVar11 != uVar10) {
              ClearExclusiveLocal();
              break;
            }
            cVar4 = '\x01';
            bVar5 = (bool)ExclusiveMonitorPass(puVar9,0x10);
            if (bVar5) {
              *puVar9 = uVar12;
              cVar4 = ExclusiveMonitorsStatus();
            }
          } while (cVar4 != '\0');
          if ((uVar10 == uVar11) && (uVar10 != *puVar9)) goto code_r0x022ec058;
        }
        DataMemoryBarrier(2,3);
        if (7999 < *piVar1) break;
        uVar11 = 0;
        if ((int)uVar3 < 7999) {
          uVar11 = uVar3 + 1;
        }
        uVar10 = uVar11 + 0x1f;
        if (-1 < (int)uVar11) {
          uVar10 = uVar11;
        }
        puVar9 = (uint *)(lVar6 + (long)((int)uVar10 >> 5) * 4 + 8);
        uVar10 = *puVar9;
        uVar13 = 1 << (ulong)(uVar11 & 0x1f);
        uVar12 = uVar10 | uVar13;
      } while( true );
    }
    *param_1 = 0;
    return 0;
  }
  *param_1 = param_3;
  *(undefined4 *)(param_3 + 0x68) = *(undefined4 *)(param_3 + 0x50);
  *(undefined4 *)(param_3 + 0x6c) = 0;
  lVar6 = Aska::GpuResource::GetBody(Aska::IMemoryManager*)(param_3,0);
  param_1[3] = lVar6;
  *(undefined1 *)((long)param_1 + 0x3f) = 1;
code_r0x022ebf1c:
  *(undefined4 *)(param_1 + 6) = param_4;
  *(long *)(*param_1 + 0x40) = param_6;
  puVar7 = (undefined8 *)*param_1;
  uVar14 = *param_5;
  puVar7[1] = param_5[1];
  *puVar7 = uVar14;
  if ((param_2 & 1) == 0) {
    return 1;
  }
  lVar6 = operator new[](unsigned long, std::nothrow_t const&)((int)param_1[6],PTR__ZSt7nothrow_02cb9a80);
  param_1[4] = lVar6;
  *(bool *)((long)param_1 + 0x3d) = lVar6 != 0;
  if (lVar6 != 0) {
    return 1;
  }
code_r0x022ec0dc:
  Aska::TMultipleBuffer<true>::DeleteBuffer()(param_1);
  return 0;
code_r0x022ec058:
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar5) {
      *piVar1 = *piVar1 + 1;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  DataMemoryBarrier(2,3);
  uVar10 = 0;
  if ((int)uVar3 < 7999) {
    uVar10 = uVar3 + 1;
  }
  do {
    cVar4 = '\x01';
    bVar5 = (bool)ExclusiveMonitorPass(puVar2,0x10);
    if (bVar5) {
      *puVar2 = uVar10;
      cVar4 = ExclusiveMonitorsStatus();
    }
  } while (cVar4 != '\0');
  lVar8 = lVar6 + (long)(int)uVar3 * 0x78;
  *(char *)(lVar8 + 0x469) = *(char *)(lVar8 + 0x469) + '\x01';
  *param_1 = lVar8 + 0x3f8;
  lVar8 = operator new[](unsigned long, std::nothrow_t const&)(param_4,PTR__ZSt7nothrow_02cb9a80);
  param_1[3] = lVar8;
  if (lVar8 == 0) goto code_r0x022ec0dc;
  lVar6 = lVar6 + (long)(int)uVar3 * 0x78;
  *(long *)(lVar6 + 0x458) = lVar8;
  *(undefined4 *)(lVar6 + 0x448) = param_4;
  goto code_r0x022ebf1c;
}

// ==== Aska::TMultipleBuffer<true>::DeleteBuffer()
// vaddr 0x21ec0fc | ghidra 0x22ec0fc | size 176 | symbol _ZN4Aska15TMultipleBufferILb1EE12DeleteBufferEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska15TMultipleBufferILb1EE12DeleteBufferEv(long *param_1)

{
  if (*(char *)((long)param_1 + 0x3f) == '\0') {
    if (param_1[3] != 0) {
      operator delete[](void*)();
      param_1[3] = 0;
    }
    if (*param_1 != 0) {
      Aska::RenderManagerBase::MarkForDelete(Aska::GpuResource*, bool)(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,*param_1,0);
    }
  }
  else {
    param_1[3] = 0;
  }
  *param_1 = 0;
  if (param_1[1] != 0) {
    Aska::RenderManagerBase::MarkForDelete(Aska::GpuResource*, bool)(*(undefined8 *)PTR__ZN4Aska12g_pRenderDevE_02cbb1a0,param_1[1],0);
    param_1[1] = 0;
  }
  if (*(char *)((long)param_1 + 0x3f) == '\0') {
    if (param_1[3] == 0) goto code_r0x022ec17c;
    operator delete[](void*)();
  }
  param_1[3] = 0;
code_r0x022ec17c:
  if (param_1[4] != 0) {
    operator delete[](void*)();
    param_1[4] = 0;
  }
  if (param_1[5] != 0) {
    operator delete[](void*)();
    param_1[5] = 0;
  }
  *(undefined1 *)(param_1 + 8) = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  return;
}

// ==== Aska::RingBuffer::Open(void const*, unsigned long)
// vaddr 0x2222e68 | ghidra 0x2322e68 | size 132 | symbol _ZN4Aska10RingBuffer4OpenEPKvm | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska10RingBuffer4OpenEPKvm(long *param_1,long param_2,long param_3)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  int *piVar4;
  
  if (param_1[2] != 0) {
    return 0;
  }
  if (param_2 == 0) {
    return 0;
  }
  if (param_3 == 0) {
    return 0;
  }
  if (*param_1 == 0) goto code_r0x02322ed0;
  piVar4 = (int *)param_1[1];
  if (piVar4 == (int *)0x0) {
code_r0x02322ebc:
    operator delete[](void*)();
code_r0x02322ec0:
    if (param_1[1] != 0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar1 = *piVar4;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar4,0x10);
      if (bVar3) {
        *piVar4 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 == 0) {
      if (*param_1 != 0) goto code_r0x02322ebc;
      goto code_r0x02322ec0;
    }
  }
  *param_1 = 0;
  param_1[1] = 0;
code_r0x02322ed0:
  param_1[2] = param_2;
  param_1[3] = param_3;
  param_1[4] = 0;
  param_1[5] = 0;
  *(undefined4 *)(param_1 + 6) = 0;
  return 1;
}

// ==== Aska::RingBuffer::Reset()
// vaddr 0x2222eec | ghidra 0x2322eec | size 12 | symbol _ZN4Aska10RingBuffer5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10RingBuffer5ResetEv(long param_1)

{
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  return;
}

// ==== Aska::RingBuffer::Close()
// vaddr 0x2222fc8 | ghidra 0x2322fc8 | size 28 | symbol _ZN4Aska10RingBuffer5CloseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska10RingBuffer5CloseEv(long param_1)

{
  if (*(long *)(param_1 + 0x10) != 0) {
    *(undefined8 *)(param_1 + 0x18) = 0;
    *(long *)(param_1 + 0x10) = 0;
    *(undefined8 *)(param_1 + 0x28) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
  return;
}

// ==== Aska::RingBuffer::PushFront(void**, unsigned long)
// vaddr 0x2223540 | ghidra 0x2323540 | size 200 | symbol _ZN4Aska10RingBuffer9PushFrontEPPvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska10RingBuffer9PushFrontEPPvm(long param_1,long *param_2,long param_3)

{
  int *piVar1;
  ulong uVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  
  if (param_3 != 0) {
    uVar2 = *(ulong *)(param_1 + 0x20);
    uVar6 = *(ulong *)(param_1 + 0x28);
    if ((uVar2 == uVar6) && (0 < *(int *)(param_1 + 0x30))) {
      return 0;
    }
    if (uVar2 < uVar6) {
      if (uVar6 < uVar2 + param_3) {
        return 0;
      }
      lVar7 = *(long *)(param_1 + 0x10) + uVar2;
    }
    else {
      lVar7 = *(long *)(param_1 + 0x10) + uVar2;
      if ((*(ulong *)(param_1 + 0x18) < uVar2 + param_3) &&
         (param_3 = *(ulong *)(param_1 + 0x18) - uVar2, param_3 == 0)) {
        return 0;
      }
    }
    *param_2 = lVar7;
    uVar6 = *(ulong *)(param_1 + 0x18);
    uVar2 = *(long *)(param_1 + 0x20) + param_3;
    if ((long)uVar2 < 0) {
      uVar5 = 0;
      if (uVar6 != 0) {
        uVar5 = -uVar2 / uVar6;
      }
      lVar7 = uVar6 - (-uVar2 - uVar5 * uVar6);
    }
    else {
      uVar5 = 0;
      if (uVar6 != 0) {
        uVar5 = uVar2 / uVar6;
      }
      lVar7 = uVar2 - uVar5 * uVar6;
    }
    *(long *)(param_1 + 0x20) = lVar7;
    piVar1 = (int *)(param_1 + 0x30);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 + (int)param_3;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
  return param_3;
}

// ==== Aska::RingBuffer::PopBack(void**, unsigned long)
// vaddr 0x222378c | ghidra 0x232378c | size 200 | symbol _ZN4Aska10RingBuffer7PopBackEPPvm | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska10RingBuffer7PopBackEPPvm(long param_1,long *param_2,long param_3)

{
  int *piVar1;
  ulong uVar2;
  char cVar3;
  bool bVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  
  if (param_3 != 0) {
    uVar2 = *(ulong *)(param_1 + 0x20);
    uVar6 = *(ulong *)(param_1 + 0x28);
    if ((uVar2 == uVar6) && (*(int *)(param_1 + 0x30) == 0)) {
      return 0;
    }
    if (uVar6 < uVar2) {
      if (uVar2 < uVar6 + param_3) {
        return 0;
      }
      lVar7 = *(long *)(param_1 + 0x10) + uVar6;
    }
    else {
      lVar7 = *(long *)(param_1 + 0x10) + uVar6;
      if ((*(ulong *)(param_1 + 0x18) < uVar6 + param_3) &&
         (param_3 = *(ulong *)(param_1 + 0x18) - uVar6, param_3 == 0)) {
        return 0;
      }
    }
    *param_2 = lVar7;
    uVar6 = *(ulong *)(param_1 + 0x18);
    uVar2 = *(long *)(param_1 + 0x28) + param_3;
    if ((long)uVar2 < 0) {
      uVar5 = 0;
      if (uVar6 != 0) {
        uVar5 = -uVar2 / uVar6;
      }
      lVar7 = uVar6 - (-uVar2 - uVar5 * uVar6);
    }
    else {
      uVar5 = 0;
      if (uVar6 != 0) {
        uVar5 = uVar2 / uVar6;
      }
      lVar7 = uVar2 - uVar5 * uVar6;
    }
    *(long *)(param_1 + 0x28) = lVar7;
    piVar1 = (int *)(param_1 + 0x30);
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar4) {
        *piVar1 = *piVar1 - (int)param_3;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
  }
  return param_3;
}

// ==== Aska::TPriorityQueue<Aska::ResourceReadyQueue::EvItem, true>::Acquire(Aska::ResourceReadyQueue::EvItem*, unsigned long, unsigned long*)
// vaddr 0x223b348 | ghidra 0x233b348 | size 460 | symbol _ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EE7AcquireEPS2_mPm | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN4Aska14TPriorityQueueINS_18ResourceReadyQueue6EvItemELb1EE7AcquireEPS2_mPm
          (long param_1,long *param_2,ulong param_3,undefined8 *param_4)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  undefined4 uVar5;
  long *plVar6;
  ulong uVar7;
  
  lVar1 = param_1 + 8;
  Aska::CriticalSection::Enter() const(lVar1);
  Aska::CriticalSection::Enter() const(lVar1);
  if ((*(int *)(param_1 + 0xc0) < 1) || (plVar6 = *(long **)(param_1 + 0x48), plVar6 == (long *)0x0)
     ) {
code_r0x0233b3d0:
    Aska::CriticalSection::Leave() const(lVar1);
code_r0x0233b3d8:
    if (param_4 == (undefined8 *)0x0) {
      uVar5 = 0;
    }
    else {
      uVar5 = 0;
      *param_4 = 0;
    }
  }
  else {
    if ((plVar6[3] == 0) || ((plVar6[3] & param_3) != 0)) {
      Aska::CriticalSection::Leave() const(lVar1);
    }
    else {
      do {
        if ((long *)(param_1 + 0x38) == plVar6) goto code_r0x0233b3d0;
        plVar6 = (long *)plVar6[2];
      } while ((plVar6[3] != 0) && ((plVar6[3] & param_3) == 0));
      Aska::CriticalSection::Leave() const(lVar1);
      if (plVar6 == (long *)0x0) goto code_r0x0233b3d8;
    }
    if (plVar6 + 5 != param_2) {
      Aska::ResourceReadyQueue::EvItem::Copy(Aska::ResourceReadyQueue::EvItem const*)(param_2);
    }
    if (param_4 != (undefined8 *)0x0) {
      *param_4 = plVar6;
    }
    if ((long *)(param_1 + 0x38) != plVar6) {
      lVar3 = plVar6[1];
      lVar4 = plVar6[2];
      if (lVar3 != 0) {
        *(long *)(lVar3 + 0x10) = lVar4;
      }
      if (lVar4 != 0) {
        *(long *)(lVar4 + 8) = lVar3;
      }
      if (0 < *(int *)(param_1 + 0xc0)) {
        *(int *)(param_1 + 0xc0) = *(int *)(param_1 + 0xc0) + -1;
      }
      plVar6[1] = 0;
      plVar6[2] = 0;
    }
    Aska::CriticalSection::Enter() const(lVar1);
    plVar2 = *(long **)(param_1 + 0x108);
    if (((plVar2 == (long *)0x0) || (plVar6 < plVar2)) ||
       (plVar2 + (ulong)*(uint *)(param_1 + 0xf4) * 0x11 <= plVar6)) {
      (**(code **)(*plVar6 + 8))(plVar6);
    }
    else {
      uVar7 = ((long)plVar6 - (long)plVar2 >> 3) * -0xf0f0f0f0f0f0f0f;
      (**(code **)plVar2[(uVar7 & 0xffffffff) * 0x11])();
      lVar3 = (uVar7 >> 5 & 0x7ffffff) * 4;
      *(uint *)(*(long *)(param_1 + 0xe8) + lVar3) =
           *(uint *)(*(long *)(param_1 + 0xe8) + lVar3) &
           (1 << (ulong)((uint)uVar7 & 0x1f) ^ 0xffffffffU);
      *(int *)(param_1 + 0x104) = *(int *)(param_1 + 0x104) + -1;
    }
    Aska::CriticalSection::Leave() const(lVar1);
    uVar5 = 1;
  }
  Aska::CriticalSection::Leave() const(lVar1);
  return uVar5;
}

// ==== Aska::TArrayIterator<Aska::TDynamicArray<Aska::detail::VertexId, Aska::detail::TSmallHeapAllocator<Aska::detail::VertexId> > > Aska::TDynamicArray<Aska::detail::VertexId, Aska::detail::TSmallHeapAllocator<Aska::detail::VertexId> >::Insert_<Aska::Memory::TUninitializedFillN<Aska::detail::VertexId> >(Aska::detail::VertexId const*, unsigned long, Aska::Memory::TUninitializedFillN<Aska::detail::VertexId> const&)
// vaddr 0x23669b4 | ghidra 0x24669b4 | size 872 | symbol _ZN4Aska13TDynamicArrayINS_6detail8VertexIdENS1_19TSmallHeapAllocatorIS2_EEE7Insert_INS_6Memory19TUninitializedFillNIS2_EEEENS_14TArrayIteratorIS5_EEPKS2_mRKT_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 *
_ZN4Aska13TDynamicArrayINS_6detail8VertexIdENS1_19TSmallHeapAllocatorIS2_EEE7Insert_INS_6Memory19TUninitializedFillNIS2_EEEENS_14TArrayIteratorIS5_EEPKS2_mRKT_
          (long param_1,undefined8 *param_2,long param_3,ulong *param_4)

{
  undefined8 *puVar1;
  bool bVar2;
  undefined8 *puVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  long lVar9;
  undefined8 *puVar10;
  ulong uVar11;
  undefined8 *puVar12;
  ulong uVar13;
  undefined8 *puVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  
  if (param_3 == 0) {
    return param_2;
  }
  puVar3 = *(undefined8 **)(param_1 + 0x10);
  uVar6 = param_3 + ((long)puVar3 - *(long *)(param_1 + 8) >> 3);
  lVar9 = *(long *)(param_1 + 0x18) - *(long *)(param_1 + 8);
  if (uVar6 <= (ulong)(lVar9 >> 3)) {
    while (puVar3 != param_2) {
      puVar3[param_3 + -1] = puVar3[-1];
      puVar3 = puVar3 + -1;
    }
    uVar6 = *param_4;
    if (uVar6 != 0) {
      puVar7 = (undefined8 *)param_4[1];
      puVar3 = param_2;
      if (((3 < uVar6) && (uVar4 = uVar6 & 0xfffffffffffffffc, uVar4 != 0)) &&
         (((undefined8 *)((long)puVar7 + 1U) <= param_2 || (param_2 + uVar6 <= puVar7)))) {
        uVar15 = *puVar7;
        puVar3 = param_2 + 2;
        uVar5 = uVar4;
        do {
          puVar3[-1] = uVar15;
          puVar3[-2] = uVar15;
          puVar3[1] = uVar15;
          *puVar3 = uVar15;
          uVar5 = uVar5 - 4;
          puVar3 = puVar3 + 4;
        } while (uVar5 != 0);
        bVar2 = uVar6 == uVar4;
        uVar6 = uVar6 - uVar4;
        puVar3 = param_2 + uVar4;
        if (bVar2) goto code_r0x02466afc;
      }
      do {
        uVar6 = uVar6 - 1;
        *puVar3 = *puVar7;
        puVar3 = puVar3 + 1;
      } while (uVar6 != 0);
    }
code_r0x02466afc:
    *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + param_3 * 8;
    return param_2;
  }
  uVar4 = lVar9 >> 2;
  if (uVar6 <= uVar4) {
    uVar6 = uVar4;
  }
  if (uVar6 >> 0x3d != 0) {
    return param_2;
  }
  puVar3 = (undefined8 *)Aska::detail::SmallHeapProxy::Allocate(unsigned long)(uVar6 << 3);
  if (puVar3 == (undefined8 *)0x0) {
    return param_2;
  }
  puVar7 = *(undefined8 **)(param_1 + 8);
  if (puVar7 == param_2) {
    uVar4 = *param_4;
    puVar7 = puVar3;
  }
  else {
    uVar5 = (long)param_2 + (-8 - (long)puVar7);
    uVar4 = (uVar5 >> 3) + 1;
    puVar10 = puVar3;
    if (((uVar4 < 4) || (uVar11 = uVar4 & 0x3ffffffffffffffc, uVar11 == 0)) ||
       ((puVar3 < (undefined8 *)((long)puVar7 + (uVar5 & 0xfffffffffffffff8) + 8) &&
        (puVar7 < (undefined8 *)((long)puVar3 + (uVar5 + 8 & 0xfffffffffffffff8)))))) {
code_r0x02466b80:
      do {
        puVar8 = puVar7 + 1;
        *puVar10 = *puVar7;
        puVar7 = puVar8;
        puVar10 = puVar10 + 1;
      } while (param_2 != puVar8);
    }
    else {
      puVar10 = puVar7 + 2;
      puVar7 = puVar7 + uVar11;
      puVar8 = puVar3 + 2;
      uVar13 = uVar11;
      do {
        puVar12 = puVar10 + -1;
        uVar15 = puVar10[-2];
        uVar17 = puVar10[1];
        uVar16 = *puVar10;
        puVar10 = puVar10 + 4;
        uVar13 = uVar13 - 4;
        puVar8[-1] = *puVar12;
        puVar8[-2] = uVar15;
        puVar8[1] = uVar17;
        *puVar8 = uVar16;
        puVar8 = puVar8 + 4;
      } while (uVar13 != 0);
      puVar10 = puVar3 + uVar11;
      if (uVar4 != uVar11) goto code_r0x02466b80;
    }
    puVar7 = (undefined8 *)((long)puVar3 + (uVar5 & 0xfffffffffffffff8) + 8);
    uVar4 = *param_4;
  }
  if (uVar4 != 0) {
    puVar8 = (undefined8 *)param_4[1];
    puVar10 = puVar7;
    if (((3 < uVar4) && (uVar5 = uVar4 & 0xfffffffffffffffc, uVar5 != 0)) &&
       (((undefined8 *)((long)puVar8 + 1U) <= puVar7 || (puVar7 + uVar4 <= puVar8)))) {
      uVar15 = *puVar8;
      puVar10 = puVar7 + 2;
      uVar11 = uVar5;
      do {
        puVar10[-1] = uVar15;
        puVar10[-2] = uVar15;
        puVar10[1] = uVar15;
        *puVar10 = uVar15;
        uVar11 = uVar11 - 4;
        puVar10 = puVar10 + 4;
      } while (uVar11 != 0);
      bVar2 = uVar4 == uVar5;
      uVar4 = uVar4 - uVar5;
      puVar10 = puVar7 + uVar5;
      if (bVar2) goto code_r0x02466c24;
    }
    do {
      uVar4 = uVar4 - 1;
      *puVar10 = *puVar8;
      puVar10 = puVar10 + 1;
    } while (uVar4 != 0);
  }
code_r0x02466c24:
  puVar8 = *(undefined8 **)(param_1 + 0x10);
  puVar10 = puVar7 + param_3;
  if (puVar8 == param_2) goto code_r0x02466ce8;
  uVar5 = (long)puVar8 + (-8 - (long)param_2);
  uVar11 = uVar5 >> 3;
  uVar4 = uVar11 + 1;
  puVar12 = puVar10;
  if (((uVar4 < 4) || (uVar13 = uVar4 & 0x3ffffffffffffffc, uVar13 == 0)) ||
     ((puVar10 < param_2 + uVar11 + 1 && (param_2 < puVar7 + uVar11 + param_3 + 1)))) {
code_r0x02466ccc:
    do {
      puVar14 = param_2 + 1;
      *puVar12 = *param_2;
      puVar12 = puVar12 + 1;
      param_2 = puVar14;
    } while (puVar8 != puVar14);
  }
  else {
    puVar12 = param_2 + 2;
    param_2 = param_2 + uVar13;
    puVar14 = puVar7 + param_3 + 2;
    uVar11 = uVar13;
    do {
      puVar1 = puVar12 + -1;
      uVar15 = puVar12[-2];
      uVar17 = puVar12[1];
      uVar16 = *puVar12;
      puVar12 = puVar12 + 4;
      uVar11 = uVar11 - 4;
      puVar14[-1] = *puVar1;
      puVar14[-2] = uVar15;
      puVar14[1] = uVar17;
      *puVar14 = uVar16;
      puVar14 = puVar14 + 4;
    } while (uVar11 != 0);
    puVar12 = puVar10 + uVar13;
    if (uVar4 != uVar13) goto code_r0x02466ccc;
  }
  puVar10 = (undefined8 *)((long)puVar10 + (uVar5 & 0xfffffffffffffff8) + 8);
code_r0x02466ce8:
  Aska::detail::SmallHeapProxy::Free(void*, unsigned long)(*(undefined8 *)(param_1 + 8),0);
  *(undefined8 **)(param_1 + 8) = puVar3;
  *(undefined8 **)(param_1 + 0x10) = puVar10;
  *(undefined8 **)(param_1 + 0x18) = puVar3 + uVar6;
  return puVar7;
}

// ==== Aska::TArrayIterator<Aska::TDynamicArray<Aska::detail::MeshsetInfo*, Aska::detail::TSmallHeapAllocator<Aska::detail::MeshsetInfo*> > > Aska::TDynamicArray<Aska::detail::MeshsetInfo*, Aska::detail::TSmallHeapAllocator<Aska::detail::MeshsetInfo*> >::Insert_<Aska::Memory::TUninitializedFillN<Aska::detail::MeshsetInfo*> >(Aska::detail::MeshsetInfo* const*, unsigned long, Aska::Memory::TUninitializedFillN<Aska::detail::MeshsetInfo*> const&)
// vaddr 0x2366d58 | ghidra 0x2466d58 | size 872 | symbol _ZN4Aska13TDynamicArrayIPNS_6detail11MeshsetInfoENS1_19TSmallHeapAllocatorIS3_EEE7Insert_INS_6Memory19TUninitializedFillNIS3_EEEENS_14TArrayIteratorIS6_EEPKS3_mRKT_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 *
_ZN4Aska13TDynamicArrayIPNS_6detail11MeshsetInfoENS1_19TSmallHeapAllocatorIS3_EEE7Insert_INS_6Memory19TUninitializedFillNIS3_EEEENS_14TArrayIteratorIS6_EEPKS3_mRKT_
          (long param_1,undefined8 *param_2,long param_3,ulong *param_4)

{
  undefined8 *puVar1;
  bool bVar2;
  undefined8 *puVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  long lVar9;
  undefined8 *puVar10;
  ulong uVar11;
  undefined8 *puVar12;
  ulong uVar13;
  undefined8 *puVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  
  if (param_3 == 0) {
    return param_2;
  }
  puVar3 = *(undefined8 **)(param_1 + 0x10);
  uVar6 = param_3 + ((long)puVar3 - *(long *)(param_1 + 8) >> 3);
  lVar9 = *(long *)(param_1 + 0x18) - *(long *)(param_1 + 8);
  if (uVar6 <= (ulong)(lVar9 >> 3)) {
    while (puVar3 != param_2) {
      puVar3[param_3 + -1] = puVar3[-1];
      puVar3 = puVar3 + -1;
    }
    uVar6 = *param_4;
    if (uVar6 != 0) {
      puVar7 = (undefined8 *)param_4[1];
      puVar3 = param_2;
      if (((3 < uVar6) && (uVar4 = uVar6 & 0xfffffffffffffffc, uVar4 != 0)) &&
         (((undefined8 *)((long)puVar7 + 1U) <= param_2 || (param_2 + uVar6 <= puVar7)))) {
        uVar15 = *puVar7;
        puVar3 = param_2 + 2;
        uVar5 = uVar4;
        do {
          puVar3[-1] = uVar15;
          puVar3[-2] = uVar15;
          puVar3[1] = uVar15;
          *puVar3 = uVar15;
          uVar5 = uVar5 - 4;
          puVar3 = puVar3 + 4;
        } while (uVar5 != 0);
        bVar2 = uVar6 == uVar4;
        uVar6 = uVar6 - uVar4;
        puVar3 = param_2 + uVar4;
        if (bVar2) goto code_r0x02466ea0;
      }
      do {
        uVar6 = uVar6 - 1;
        *puVar3 = *puVar7;
        puVar3 = puVar3 + 1;
      } while (uVar6 != 0);
    }
code_r0x02466ea0:
    *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + param_3 * 8;
    return param_2;
  }
  uVar4 = lVar9 >> 2;
  if (uVar6 <= uVar4) {
    uVar6 = uVar4;
  }
  if (uVar6 >> 0x3d != 0) {
    return param_2;
  }
  puVar3 = (undefined8 *)Aska::detail::SmallHeapProxy::Allocate(unsigned long)(uVar6 << 3);
  if (puVar3 == (undefined8 *)0x0) {
    return param_2;
  }
  puVar7 = *(undefined8 **)(param_1 + 8);
  if (puVar7 == param_2) {
    uVar4 = *param_4;
    puVar7 = puVar3;
  }
  else {
    uVar5 = (long)param_2 + (-8 - (long)puVar7);
    uVar4 = (uVar5 >> 3) + 1;
    puVar10 = puVar3;
    if (((uVar4 < 4) || (uVar11 = uVar4 & 0x3ffffffffffffffc, uVar11 == 0)) ||
       ((puVar3 < (undefined8 *)((long)puVar7 + (uVar5 & 0xfffffffffffffff8) + 8) &&
        (puVar7 < (undefined8 *)((long)puVar3 + (uVar5 + 8 & 0xfffffffffffffff8)))))) {
code_r0x02466f24:
      do {
        puVar8 = puVar7 + 1;
        *puVar10 = *puVar7;
        puVar7 = puVar8;
        puVar10 = puVar10 + 1;
      } while (param_2 != puVar8);
    }
    else {
      puVar10 = puVar7 + 2;
      puVar7 = puVar7 + uVar11;
      puVar8 = puVar3 + 2;
      uVar13 = uVar11;
      do {
        puVar12 = puVar10 + -1;
        uVar15 = puVar10[-2];
        uVar17 = puVar10[1];
        uVar16 = *puVar10;
        puVar10 = puVar10 + 4;
        uVar13 = uVar13 - 4;
        puVar8[-1] = *puVar12;
        puVar8[-2] = uVar15;
        puVar8[1] = uVar17;
        *puVar8 = uVar16;
        puVar8 = puVar8 + 4;
      } while (uVar13 != 0);
      puVar10 = puVar3 + uVar11;
      if (uVar4 != uVar11) goto code_r0x02466f24;
    }
    puVar7 = (undefined8 *)((long)puVar3 + (uVar5 & 0xfffffffffffffff8) + 8);
    uVar4 = *param_4;
  }
  if (uVar4 != 0) {
    puVar8 = (undefined8 *)param_4[1];
    puVar10 = puVar7;
    if (((3 < uVar4) && (uVar5 = uVar4 & 0xfffffffffffffffc, uVar5 != 0)) &&
       (((undefined8 *)((long)puVar8 + 1U) <= puVar7 || (puVar7 + uVar4 <= puVar8)))) {
      uVar15 = *puVar8;
      puVar10 = puVar7 + 2;
      uVar11 = uVar5;
      do {
        puVar10[-1] = uVar15;
        puVar10[-2] = uVar15;
        puVar10[1] = uVar15;
        *puVar10 = uVar15;
        uVar11 = uVar11 - 4;
        puVar10 = puVar10 + 4;
      } while (uVar11 != 0);
      bVar2 = uVar4 == uVar5;
      uVar4 = uVar4 - uVar5;
      puVar10 = puVar7 + uVar5;
      if (bVar2) goto code_r0x02466fc8;
    }
    do {
      uVar4 = uVar4 - 1;
      *puVar10 = *puVar8;
      puVar10 = puVar10 + 1;
    } while (uVar4 != 0);
  }
code_r0x02466fc8:
  puVar8 = *(undefined8 **)(param_1 + 0x10);
  puVar10 = puVar7 + param_3;
  if (puVar8 == param_2) goto code_r0x0246708c;
  uVar5 = (long)puVar8 + (-8 - (long)param_2);
  uVar11 = uVar5 >> 3;
  uVar4 = uVar11 + 1;
  puVar12 = puVar10;
  if (((uVar4 < 4) || (uVar13 = uVar4 & 0x3ffffffffffffffc, uVar13 == 0)) ||
     ((puVar10 < param_2 + uVar11 + 1 && (param_2 < puVar7 + uVar11 + param_3 + 1)))) {
code_r0x02467070:
    do {
      puVar14 = param_2 + 1;
      *puVar12 = *param_2;
      puVar12 = puVar12 + 1;
      param_2 = puVar14;
    } while (puVar8 != puVar14);
  }
  else {
    puVar12 = param_2 + 2;
    param_2 = param_2 + uVar13;
    puVar14 = puVar7 + param_3 + 2;
    uVar11 = uVar13;
    do {
      puVar1 = puVar12 + -1;
      uVar15 = puVar12[-2];
      uVar17 = puVar12[1];
      uVar16 = *puVar12;
      puVar12 = puVar12 + 4;
      uVar11 = uVar11 - 4;
      puVar14[-1] = *puVar1;
      puVar14[-2] = uVar15;
      puVar14[1] = uVar17;
      *puVar14 = uVar16;
      puVar14 = puVar14 + 4;
    } while (uVar11 != 0);
    puVar12 = puVar10 + uVar13;
    if (uVar4 != uVar13) goto code_r0x02467070;
  }
  puVar10 = (undefined8 *)((long)puVar10 + (uVar5 & 0xfffffffffffffff8) + 8);
code_r0x0246708c:
  Aska::detail::SmallHeapProxy::Free(void*, unsigned long)(*(undefined8 *)(param_1 + 8),0);
  *(undefined8 **)(param_1 + 8) = puVar3;
  *(undefined8 **)(param_1 + 0x10) = puVar10;
  *(undefined8 **)(param_1 + 0x18) = puVar3 + uVar6;
  return puVar7;
}

// ==== Aska::TArrayIterator<Aska::TDynamicArray<Aska::TPair<Aska::detail::FontId, Aska::detail::FontManager::FontMapValue>, Aska::detail::TSmallHeapAllocator<Aska::TPair<Aska::detail::FontId, Aska::detail::FontManager::FontMapValue> > > > Aska::TDynamicArray<Aska::TPair<Aska::detail::FontId, Aska::detail::FontManager::FontMapValue>, Aska::detail::TSmallHeapAllocator<Aska::TPair<Aska::detail::FontId, Aska::detail::FontManager::FontMapValue> > >::Insert_<Aska::Memory::TConstruct2<Aska::detail::TSmallHeapAllocator<Aska::TPair<Aska::detail::FontId, Aska::detail::FontManager::FontMapValue> >, Aska::detail::FontId, Aska::detail::FontManager::FontMapValue> >(Aska::TPair<Aska::detail::FontId, Aska::detail::FontManager::FontMapValue> const*, unsigned long, Aska::Memory::TConstruct2<Aska::detail::TSmallHeapAllocator<Aska::TPair<Aska::detail::FontId, Aska::detail::FontManager::FontMapValue> >, Aska::detail::FontId, Aska::detail::FontManager::FontMapValue> const&)
// vaddr 0x2368644 | ghidra 0x2468644 | size 404 | symbol _ZN4Aska13TDynamicArrayINS_5TPairINS_6detail6FontIdENS2_11FontManager12FontMapValueEEENS2_19TSmallHeapAllocatorIS6_EEE7Insert_INS_6Memory11TConstruct2IS8_S3_S5_EEEENS_14TArrayIteratorIS9_EEPKS6_mRKT_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 *
_ZN4Aska13TDynamicArrayINS_5TPairINS_6detail6FontIdENS2_11FontManager12FontMapValueEEENS2_19TSmallHeapAllocatorIS6_EEE7Insert_INS_6Memory11TConstruct2IS8_S3_S5_EEEENS_14TArrayIteratorIS9_EEPKS6_mRKT_
          (long param_1,undefined8 *param_2,long param_3,long param_4)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  ulong uVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  ulong uVar6;
  long lVar7;
  undefined8 uVar8;
  
  if (param_3 != 0) {
    puVar2 = *(undefined8 **)(param_1 + 0x10);
    lVar7 = *(long *)(param_1 + 0x18) - *(long *)(param_1 + 8) >> 3;
    uVar6 = param_3 + ((long)puVar2 - *(long *)(param_1 + 8) >> 3) * -0x5555555555555555;
    if ((ulong)(lVar7 * -0x5555555555555555) < uVar6) {
      uVar3 = lVar7 * 0x5555555555555556;
      if (uVar6 <= uVar3) {
        uVar6 = uVar3;
      }
      if ((uVar6 < 0xaaaaaaaaaaaaaab) &&
         (puVar2 = (undefined8 *)Aska::detail::SmallHeapProxy::Allocate(unsigned long)(uVar6 * 0x18), puVar2 != (undefined8 *)0x0)) {
        puVar1 = puVar2;
        for (puVar4 = *(undefined8 **)(param_1 + 8); puVar4 != param_2; puVar4 = puVar4 + 3) {
          *puVar1 = *puVar4;
          uVar8 = puVar4[1];
          puVar1[2] = puVar4[2];
          puVar1[1] = uVar8;
          puVar1 = puVar1 + 3;
        }
        puVar5 = *(undefined8 **)(param_4 + 0x10);
        *puVar1 = **(undefined8 **)(param_4 + 8);
        uVar8 = *puVar5;
        puVar4 = puVar1 + param_3 * 3;
        puVar1[2] = puVar5[1];
        puVar1[1] = uVar8;
        puVar5 = *(undefined8 **)(param_1 + 0x10);
        for (; puVar5 != param_2; param_2 = param_2 + 3) {
          *puVar4 = *param_2;
          uVar8 = param_2[1];
          puVar4[2] = param_2[2];
          puVar4[1] = uVar8;
          puVar4 = puVar4 + 3;
        }
        Aska::detail::SmallHeapProxy::Free(void*, unsigned long)(*(undefined8 *)(param_1 + 8),0);
        *(undefined8 **)(param_1 + 8) = puVar2;
        *(undefined8 **)(param_1 + 0x10) = puVar4;
        *(undefined8 **)(param_1 + 0x18) = puVar2 + uVar6 * 3;
        param_2 = puVar1;
      }
    }
    else {
      while (puVar2 != param_2) {
        puVar2[param_3 * 3 + -3] = puVar2[-3];
        uVar8 = puVar2[-2];
        puVar2[param_3 * 3 + -1] = puVar2[-1];
        puVar2[param_3 * 3 + -2] = uVar8;
        puVar2 = puVar2 + -3;
      }
      puVar2 = *(undefined8 **)(param_4 + 0x10);
      *param_2 = **(undefined8 **)(param_4 + 8);
      uVar8 = *puVar2;
      param_2[2] = puVar2[1];
      param_2[1] = uVar8;
      *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + param_3 * 0x18;
    }
  }
  return param_2;
}

// ==== Aska::TArrayIterator<Aska::TDynamicArray<Aska::GlyphMetric, Aska::TAllocator<Aska::GlyphMetric> > > Aska::TDynamicArray<Aska::GlyphMetric, Aska::TAllocator<Aska::GlyphMetric> >::Insert_<Aska::Memory::TUninitializedCopy<Aska::Glyph const*> >(Aska::GlyphMetric const*, unsigned long, Aska::Memory::TUninitializedCopy<Aska::Glyph const*> const&)
// vaddr 0x2368e78 | ghidra 0x2468e78 | size 752 | symbol _ZN4Aska13TDynamicArrayINS_11GlyphMetricENS_10TAllocatorIS1_EEE7Insert_INS_6Memory18TUninitializedCopyIPKNS_5GlyphEEEEENS_14TArrayIteratorIS4_EEPKS1_mRKT_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 *
_ZN4Aska13TDynamicArrayINS_11GlyphMetricENS_10TAllocatorIS1_EEE7Insert_INS_6Memory18TUninitializedCopyIPKNS_5GlyphEEEEENS_14TArrayIteratorIS4_EEPKS1_mRKT_
          (long param_1,undefined8 *param_2,long param_3,long *param_4)

{
  ulong uVar1;
  long lVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  ulong uVar5;
  undefined1 *puVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  long lVar9;
  undefined8 *puVar10;
  ulong uVar11;
  undefined8 *puVar12;
  ulong uVar13;
  undefined8 *puVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  
  if (param_3 == 0) {
    return param_2;
  }
  puVar4 = *(undefined8 **)(param_1 + 0x10);
  uVar1 = param_3 + ((long)puVar4 - *(long *)(param_1 + 8) >> 3);
  lVar9 = *(long *)(param_1 + 0x18) - *(long *)(param_1 + 8);
  if (uVar1 <= (ulong)(lVar9 >> 3)) {
    while (puVar4 != param_2) {
      puVar4[param_3 + -1] = puVar4[-1];
      puVar4 = puVar4 + -1;
    }
    lVar2 = param_4[1];
    puVar4 = param_2;
    for (lVar9 = *param_4; lVar9 != lVar2; lVar9 = lVar9 + 0x10) {
      *(undefined1 *)puVar4 = *(undefined1 *)(lVar9 + 8);
      *(undefined1 *)((long)puVar4 + 1) = *(undefined1 *)(lVar9 + 9);
      *(undefined1 *)((long)puVar4 + 2) = *(undefined1 *)(lVar9 + 10);
      *(undefined1 *)((long)puVar4 + 3) = *(undefined1 *)(lVar9 + 0xb);
      *(undefined2 *)((long)puVar4 + 4) = *(undefined2 *)(lVar9 + 0xc);
      *(undefined1 *)((long)puVar4 + 6) = *(undefined1 *)(lVar9 + 0xe);
      puVar4 = puVar4 + 1;
    }
    *(long *)(param_1 + 0x10) = *(long *)(param_1 + 0x10) + param_3 * 8;
    return param_2;
  }
  uVar5 = lVar9 >> 2;
  if (uVar1 <= uVar5) {
    uVar1 = uVar5;
  }
  if (uVar1 >> 0x3d != 0) {
    return param_2;
  }
  puVar4 = (undefined8 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(uVar1 << 3,2);
  if (puVar4 == (undefined8 *)0x0) {
    return param_2;
  }
  puVar8 = *(undefined8 **)(param_1 + 8);
  puVar10 = puVar4;
  if (puVar8 != param_2) {
    puVar6 = (undefined1 *)((long)param_2 + (-8 - (long)puVar8));
    uVar5 = ((ulong)puVar6 >> 3) + 1;
    if (((uVar5 < 4) || (uVar11 = uVar5 & 0x3ffffffffffffffc, uVar11 == 0)) ||
       ((puVar4 < (undefined8 *)((long)puVar8 + ((ulong)puVar6 & 0xfffffffffffffff8) + 8) &&
        (puVar8 < (undefined8 *)((long)puVar4 + ((ulong)(puVar6 + 8) & 0xfffffffffffffff8)))))) {
code_r0x02469020:
      do {
        puVar7 = puVar8 + 1;
        *puVar10 = *puVar8;
        puVar8 = puVar7;
        puVar10 = puVar10 + 1;
      } while (param_2 != puVar7);
    }
    else {
      puVar10 = puVar8 + 2;
      puVar8 = puVar8 + uVar11;
      puVar7 = puVar4 + 2;
      uVar13 = uVar11;
      do {
        puVar12 = puVar10 + -1;
        uVar15 = puVar10[-2];
        uVar17 = puVar10[1];
        uVar16 = *puVar10;
        puVar10 = puVar10 + 4;
        uVar13 = uVar13 - 4;
        puVar7[-1] = *puVar12;
        puVar7[-2] = uVar15;
        puVar7[1] = uVar17;
        *puVar7 = uVar16;
        puVar7 = puVar7 + 4;
      } while (uVar13 != 0);
      puVar10 = puVar4 + uVar11;
      if (uVar5 != uVar11) goto code_r0x02469020;
    }
    puVar10 = (undefined8 *)((long)puVar4 + ((ulong)puVar6 & 0xfffffffffffffff8) + 8);
  }
  lVar2 = param_4[1];
  puVar8 = puVar10;
  for (lVar9 = *param_4; lVar9 != lVar2; lVar9 = lVar9 + 0x10) {
    *(undefined1 *)puVar8 = *(undefined1 *)(lVar9 + 8);
    *(undefined1 *)((long)puVar8 + 1) = *(undefined1 *)(lVar9 + 9);
    *(undefined1 *)((long)puVar8 + 2) = *(undefined1 *)(lVar9 + 10);
    *(undefined1 *)((long)puVar8 + 3) = *(undefined1 *)(lVar9 + 0xb);
    *(undefined2 *)((long)puVar8 + 4) = *(undefined2 *)(lVar9 + 0xc);
    *(undefined1 *)((long)puVar8 + 6) = *(undefined1 *)(lVar9 + 0xe);
    puVar8 = puVar8 + 1;
  }
  puVar7 = *(undefined8 **)(param_1 + 0x10);
  puVar8 = puVar10 + param_3;
  if (puVar7 == param_2) goto code_r0x02469150;
  puVar6 = (undefined1 *)((long)puVar7 + (-8 - (long)param_2));
  uVar11 = (ulong)puVar6 >> 3;
  uVar5 = uVar11 + 1;
  puVar12 = puVar8;
  if (((uVar5 < 4) || (uVar13 = uVar5 & 0x3ffffffffffffffc, uVar13 == 0)) ||
     ((puVar8 < param_2 + uVar11 + 1 && (param_2 < puVar10 + uVar11 + param_3 + 1)))) {
code_r0x02469134:
    do {
      puVar14 = param_2 + 1;
      *puVar12 = *param_2;
      puVar12 = puVar12 + 1;
      param_2 = puVar14;
    } while (puVar7 != puVar14);
  }
  else {
    puVar12 = param_2 + 2;
    param_2 = param_2 + uVar13;
    puVar14 = puVar10 + param_3 + 2;
    uVar11 = uVar13;
    do {
      puVar3 = puVar12 + -1;
      uVar15 = puVar12[-2];
      uVar17 = puVar12[1];
      uVar16 = *puVar12;
      puVar12 = puVar12 + 4;
      uVar11 = uVar11 - 4;
      puVar14[-1] = *puVar3;
      puVar14[-2] = uVar15;
      puVar14[1] = uVar17;
      *puVar14 = uVar16;
      puVar14 = puVar14 + 4;
    } while (uVar11 != 0);
    puVar12 = puVar8 + uVar13;
    if (uVar5 != uVar13) goto code_r0x02469134;
  }
  puVar8 = (undefined8 *)((long)puVar8 + ((ulong)puVar6 & 0xfffffffffffffff8) + 8);
code_r0x02469150:
  Aska::MemoryManagerAdapter::AlignedFree(void*)(*(undefined8 *)(param_1 + 8));
  *(undefined8 **)(param_1 + 8) = puVar4;
  *(undefined8 **)(param_1 + 0x10) = puVar8;
  *(undefined8 **)(param_1 + 0x18) = puVar4 + uVar1;
  return puVar10;
}

// ==== _make_words
// vaddr 0x260e880 | ghidra 0x270e880 | size 648 | symbol _make_words | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */

long _make_words(long param_1,long param_2,long param_3)

{
  char cVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  uint uVar6;
  long lVar7;
  uint *puVar8;
  long lVar9;
  uint uVar10;
  int iStack_c8;
  uint auStack_c4 [33];
  
  lVar4 = param_3;
  if (param_3 == 0) {
    lVar4 = param_2;
  }
  lVar2 = ogg_malloc(lVar4 << 2);
  memset(auStack_c4,0,0x84);
  lVar4 = 1;
  uVar5 = 0x1f;
  if (0 < param_2) {
    lVar4 = 0;
    lVar3 = 0;
    do {
      cVar1 = *(char *)(param_1 + lVar4);
      lVar7 = (long)cVar1;
      uVar5 = (ulong)(param_3 == 0);
      if (0 < lVar7) {
        uVar6 = auStack_c4[lVar7];
        if ((cVar1 < ' ') && (uVar6 >> (ulong)((int)cVar1 & 0x1f) != 0)) goto code_r0x0270eae0;
        *(uint *)(lVar2 + lVar3 * 4) = uVar6;
        lVar9 = lVar7;
        if ((uVar6 & 1) == 0) {
          puVar8 = auStack_c4 + (int)cVar1;
          uVar10 = uVar6;
          do {
            *puVar8 = uVar10 + 1;
            if (lVar9 < 2) goto code_r0x0270e978;
            puVar8 = puVar8 + -1;
            uVar10 = *puVar8;
            lVar9 = lVar9 + -1;
          } while ((uVar10 & 1) == 0);
        }
        else {
          puVar8 = auStack_c4 + lVar7;
        }
        if (lVar9 == 1) {
          auStack_c4[1] = auStack_c4[1] + 1;
        }
        else {
          *puVar8 = (&iStack_c8)[lVar9] << 1;
        }
code_r0x0270e978:
        lVar9 = lVar7 + 1;
        while (uVar5 = 1, lVar9 < 0x21) {
          uVar10 = auStack_c4[lVar7 + 1];
          uVar5 = 1;
          if (uVar10 >> 1 != uVar6) break;
          auStack_c4[lVar7 + 1] = auStack_c4[lVar7] << 1;
          lVar9 = lVar7 + 2;
          lVar7 = lVar7 + 1;
          uVar6 = uVar10;
        }
      }
      lVar3 = lVar3 + uVar5;
      lVar4 = lVar4 + 1;
    } while (lVar4 < param_2);
    lVar4 = 1;
    uVar5 = 0x1f;
    if (lVar3 == 1) {
      lVar4 = 1;
      uVar5 = 0x1f;
      if (auStack_c4[2] == 2) goto code_r0x0270ea1c;
    }
  }
  do {
    if (((ulong)auStack_c4[lVar4] & 0xffffffffUL >> (uVar5 & 0x3f)) != 0) {
code_r0x0270eae0:
      ogg_free(lVar2);
      return 0;
    }
    lVar4 = lVar4 + 1;
    uVar5 = uVar5 - 1;
  } while (lVar4 < 0x21);
code_r0x0270ea1c:
  if (0 < param_2) {
    lVar4 = 0;
    if (param_3 == 0) {
      do {
        if ((long)*(char *)(param_1 + lVar4) < 1) {
          uVar6 = 0;
        }
        else {
          uVar6 = 0;
          lVar3 = 0;
          do {
            uVar10 = (uint)lVar3;
            lVar3 = lVar3 + 1;
            uVar6 = uVar6 << 1 | *(uint *)(lVar2 + lVar4 * 4) >> (ulong)(uVar10 & 0x1f) & 1;
          } while (lVar3 < *(char *)(param_1 + lVar4));
        }
        *(uint *)(lVar2 + lVar4 * 4) = uVar6;
        lVar4 = lVar4 + 1;
      } while (lVar4 != param_2);
    }
    else {
      lVar3 = 0;
      do {
        cVar1 = *(char *)(param_1 + lVar4);
        if ((long)cVar1 < 1) {
          uVar6 = 0;
        }
        else {
          uVar6 = 0;
          lVar7 = 0;
          do {
            uVar10 = (uint)lVar7;
            lVar7 = lVar7 + 1;
            uVar6 = uVar6 << 1 | *(uint *)(lVar2 + lVar3 * 4) >> (ulong)(uVar10 & 0x1f) & 1;
          } while (lVar7 < cVar1);
        }
        lVar7 = lVar3;
        if (cVar1 != '\0') {
          lVar7 = lVar3 + 1;
          *(uint *)(lVar2 + lVar3 * 4) = uVar6;
        }
        lVar4 = lVar4 + 1;
        lVar3 = lVar7;
      } while (lVar4 != param_2);
    }
  }
  return lVar2;
}
