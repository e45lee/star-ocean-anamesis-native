// port/decomp/anim/animation_model.c: Ghidra decompiles for the anim subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:28 UTC: tools/decomp.sh '--into' 'anim/animation_model' 'Framework::CAnimationBlendContainer::' 'Framework::CAnimationModel::' 'Framework::CBlendRatePlayer::' 'Framework::CAnimationElement::' 'Framework::CAnimationTimeElement::'

// ==== Framework::CAnimationBlendContainer::CAnimationBlendContainer()
// vaddr 0x1e5b09c | ghidra 0x1f5b09c | size 92 | symbol _ZN9Framework24CAnimationBlendContainerC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainerC1Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar1 = PTR__ZTVN9Framework24CAnimationBlendContainerE_02cbc7e8;
  param_1[6] = 8;
  *(undefined4 *)(param_1 + 0x11) = 0x7fc00000;
  puVar2 = 
  PTR__ZTVN4Aska6TArrayIN9Framework24CAnimationBlendContainer17_tBlendMotionDataELb0EEE_02cc4e98;
  *(undefined4 *)(param_1 + 7) = 0;
  *(undefined4 *)((long)param_1 + 0x74) = 0;
  *(undefined4 *)(param_1 + 0xb) = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  *(undefined2 *)(param_1 + 0x13) = 0;
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[5] = 0;
  param_1[4] = 0;
  param_1[1] = (long)(puVar2 + 0x10);
  *param_1 = (long)(puVar1 + 0x10);
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  return;
}

// ==== Framework::CAnimationBlendContainer::~CAnimationBlendContainer()
// vaddr 0x1e5b0f8 | ghidra 0x1f5b0f8 | size 88 | symbol _ZN9Framework24CAnimationBlendContainerD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainerD1Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework24CAnimationBlendContainerE_02cbc7e8 + 0x10);
  Framework::CAnimationBlendContainer::Release()();
  param_1[1] = (long)(
                     PTR__ZTVN4Aska6TArrayIN9Framework24CAnimationBlendContainer17_tBlendMotionDataELb0EEE_02cc4e98
                     + 0x10);
  *(ushort *)((long)param_1 + 0x3a) = *(ushort *)((long)param_1 + 0x3a) | 1;
  if (param_1[2] != 0) {
    operator delete[](void*)();
    param_1[2] = 0;
  }
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[3] = 0;
  return;
}

// ==== Framework::CAnimationBlendContainer::Release()
// vaddr 0x1e5b150 | ghidra 0x1f5b150 | size 176 | symbol _ZN9Framework24CAnimationBlendContainer7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer7ReleaseEv(long param_1)

{
  long lVar1;
  long lVar2;
  
  if (*(long **)(param_1 + 0x48) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x48) + 0x20))();
    *(undefined8 *)(param_1 + 0x48) = 0;
  }
  if (*(long **)(param_1 + 0x50) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x50) + 8))();
    *(undefined8 *)(param_1 + 0x50) = 0;
  }
  lVar2 = *(long *)(param_1 + 0x60);
  if (lVar2 != 0) {
    lVar1 = *(long *)(lVar2 + -8);
    if (lVar1 != 0) {
      lVar1 = lVar1 * 0x68;
      do {
        Framework::CAnimationElement::~CAnimationElement()(lVar2 + lVar1 + -0x68);
        lVar1 = lVar1 + -0x68;
      } while (lVar1 != 0);
    }
    operator delete[](void*)((long *)(lVar2 + -8));
    *(undefined8 *)(param_1 + 0x60) = 0;
  }
  if (*(long *)(param_1 + 0xa0) != 0) {
    operator delete(void*)();
    *(undefined8 *)(param_1 + 0xa0) = 0;
  }
  if (*(long *)(param_1 + 0xa8) != 0) {
    operator delete(void*)();
    *(undefined8 *)(param_1 + 0xa8) = 0;
  }
  *(undefined1 *)(param_1 + 0x99) = 0;
  return;
}

// ==== Aska::TArray<Framework::CAnimationBlendContainer::_tBlendMotionData, false>::~TArray()
// vaddr 0x1e5b200 | ghidra 0x1f5b200 | size 68 | symbol _ZN4Aska6TArrayIN9Framework24CAnimationBlendContainer17_tBlendMotionDataELb0EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIN9Framework24CAnimationBlendContainer17_tBlendMotionDataELb0EED2Ev
               (long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVN4Aska6TArrayIN9Framework24CAnimationBlendContainer17_tBlendMotionDataELb0EEE_02cc4e98
                   + 0x10);
  *(ushort *)((long)param_1 + 0x32) = *(ushort *)((long)param_1 + 0x32) | 1;
  if (param_1[1] != 0) {
    operator delete[](void*)();
    param_1[1] = 0;
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[2] = 0;
  return;
}

// ==== Framework::CAnimationBlendContainer::~CAnimationBlendContainer()
// vaddr 0x1e5b244 | ghidra 0x1f5b244 | size 80 | symbol _ZN9Framework24CAnimationBlendContainerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainerD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework24CAnimationBlendContainerE_02cbc7e8 + 0x10);
  Framework::CAnimationBlendContainer::Release()();
  param_1[1] = (long)(
                     PTR__ZTVN4Aska6TArrayIN9Framework24CAnimationBlendContainer17_tBlendMotionDataELb0EEE_02cc4e98
                     + 0x10);
  *(ushort *)((long)param_1 + 0x3a) = *(ushort *)((long)param_1 + 0x3a) | 1;
  if (param_1[2] != 0) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CAnimationBlendContainer::Initialize(unsigned int, unsigned int)
// vaddr 0x1e5b294 | ghidra 0x1f5b294 | size 284 | symbol _ZN9Framework24CAnimationBlendContainer10InitializeEjj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer10InitializeEjj
               (long param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  long lVar2;
  ulong *puVar3;
  ulong uVar4;
  ulong *puVar5;
  
  *(undefined4 *)(param_1 + 0x58) = param_2;
  if (*(long *)(param_1 + 0x50) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x47,&UNK_02960528/*"m_pBlendRatePlayer isn't null.(%08x)"*/);
  }
  lVar2 = operator new(unsigned long, std::nothrow_t const&)(0x18,PTR__ZSt7nothrow_02cb9a80);
  if (lVar2 == 0) {
    *(undefined8 *)(param_1 + 0x50) = 0;
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x49,&UNK_0296054d/*"m_pBlendRatePlayer is null."*/);
    lVar2 = *(long *)(param_1 + 0x50);
  }
  else {
    Framework::CBlendRatePlayer::CBlendRatePlayer()(lVar2);
    *(long *)(param_1 + 0x50) = lVar2;
  }
  Framework::CBlendRatePlayer::Initialize(unsigned int)(lVar2,param_3);
  uVar1 = *(uint *)(param_1 + 0x58);
  uVar4 = (ulong)uVar1;
  puVar3 = (ulong *)operator new[](unsigned long, std::nothrow_t const&)(uVar4 * 0x68 + 8,PTR__ZSt7nothrow_02cb9a80);
  if (puVar3 == (ulong *)0x0) {
    *(undefined8 *)(param_1 + 0x60) = 0;
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x4d,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  else {
    *puVar3 = uVar4;
    if (uVar1 != 0) {
      lVar2 = uVar4 * 0x68;
      puVar5 = puVar3 + 1;
      do {
        Framework::CAnimationElement::CAnimationElement()(puVar5);
        lVar2 = lVar2 + -0x68;
        puVar5 = puVar5 + 0xd;
      } while (lVar2 != 0);
    }
    *(ulong **)(param_1 + 0x60) = puVar3 + 1;
  }
  *(undefined8 *)(param_1 + 0x90) = 0xffffffff;
  *(undefined8 *)(param_1 + 0x70) = 0x3f800000;
  return;
}

// ==== Framework::CAnimationBlendContainer::Open()
// vaddr 0x1e5b3b0 | ghidra 0x1f5b3b0 | size 4 | symbol _ZN9Framework24CAnimationBlendContainer4OpenEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer4OpenEv(void)

{
  return;
}

// ==== Framework::CAnimationBlendContainer::AttachAaf(Aska::AsfHandler&, unsigned int, void const*, int, bool)
// vaddr 0x1e5b3b4 | ghidra 0x1f5b3b4 | size 172 | symbol _ZN9Framework24CAnimationBlendContainer9AttachAafERN4Aska10AsfHandlerEjPKvib | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework24CAnimationBlendContainer9AttachAafERN4Aska10AsfHandlerEjPKvib
               (long param_1,undefined8 param_2,uint param_3,undefined8 param_4,undefined4 param_5,
               uint param_6)

{
  long lVar1;
  
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x69,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  if (*(uint *)(param_1 + 0x58) <= param_3) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x6a,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_3);
  }
  lVar1 = *(long *)(param_1 + 0x60) + (ulong)param_3 * 0x68;
  Framework::CAnimationElement::Initialize(Aska::AsfHandler&, void const*, int, bool)(lVar1,param_2,param_4,param_5,param_6 & 1);
  return lVar1;
}

// ==== Framework::CAnimationBlendContainer::DetachAafByIndex(unsigned int)
// vaddr 0x1e5b460 | ghidra 0x1f5b460 | size 36 | symbol _ZN9Framework24CAnimationBlendContainer16DetachAafByIndexEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer16DetachAafByIndexEj(long param_1,uint param_2)

{
  if (param_2 < *(uint *)(param_1 + 0x58)) {
    if (*(long *)(param_1 + 0x60) + (ulong)param_2 * 0x68 != 0) {
      (*(code *)PTR__ZN9Framework17CAnimationElement7ReleaseEv_02cad3f0)();
      return;
    }
  }
  return;
}

// ==== Framework::CAnimationBlendContainer::DetachAafByAnimID(unsigned int)
// vaddr 0x1e5b484 | ghidra 0x1f5b484 | size 76 | symbol _ZN9Framework24CAnimationBlendContainer17DetachAafByAnimIDEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer17DetachAafByAnimIDEj(long param_1,int param_2)

{
  int iVar1;
  ulong uVar2;
  
  if (*(uint *)(param_1 + 0x58) != 0) {
    uVar2 = 0;
    do {
      iVar1 = (int)uVar2;
      if (*(int *)(*(long *)(param_1 + 0x60) + uVar2 * 0x68 + 0x28) == param_2) {
        if (iVar1 < 0) {
          return;
        }
        if (*(long *)(param_1 + 0x60) + (long)iVar1 * 0x68 == 0) {
          return;
        }
        (*(code *)PTR__ZN9Framework17CAnimationElement7ReleaseEv_02cad3f0)();
        return;
      }
      uVar2 = (ulong)(iVar1 + 1U);
    } while (iVar1 + 1U < *(uint *)(param_1 + 0x58));
  }
  return;
}

// ==== Framework::CAnimationBlendContainer::pSearch(int)
// vaddr 0x1e5b4d0 | ghidra 0x1f5b4d0 | size 88 | symbol _ZN9Framework24CAnimationBlendContainer7pSearchEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework24CAnimationBlendContainer7pSearchEi(long param_1,int param_2)

{
  uint uVar1;
  
  if (*(uint *)(param_1 + 0x58) == 0) {
    return 0;
  }
  uVar1 = 0;
  do {
    if (*(int *)(*(long *)(param_1 + 0x60) + (ulong)uVar1 * 0x68 + 0x28) == param_2) {
      if (-1 < (int)uVar1) {
        return *(long *)(param_1 + 0x60) + (long)(int)uVar1 * 0x68;
      }
      return 0;
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < *(uint *)(param_1 + 0x58));
  return 0;
}

// ==== Framework::CAnimationBlendContainer::AttachAet(unsigned int, void const*)
// vaddr 0x1e5b528 | ghidra 0x1f5b528 | size 100 | symbol _ZN9Framework24CAnimationBlendContainer9AttachAetEjPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer9AttachAetEjPKv
               (long param_1,int param_2,undefined8 param_3)

{
  long lVar1;
  int iVar2;
  ulong uVar3;
  
  if (*(uint *)(param_1 + 0x58) != 0) {
    uVar3 = 0;
    do {
      iVar2 = (int)uVar3;
      if (*(int *)(*(long *)(param_1 + 0x60) + uVar3 * 0x68 + 0x28) == param_2) {
        if ((-1 < iVar2) && (lVar1 = *(long *)(param_1 + 0x60) + (long)iVar2 * 0x68, lVar1 != 0)) {
          (*(code *)PTR__ZN9Framework17CAnimationElement9AttachAetEPKv_02ca76d0)(lVar1,param_3);
          return;
        }
        break;
      }
      uVar3 = (ulong)(iVar2 + 1U);
    } while (iVar2 + 1U < *(uint *)(param_1 + 0x58));
  }
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x92,&UNK_02960569/*"A target of Aaf for aet is nothing."*/);
  return;
}

// ==== Framework::CAnimationBlendContainer::ReplaceAafAndAet(unsigned int, void const*, void const*)
// vaddr 0x1e5b58c | ghidra 0x1f5b58c | size 136 | symbol _ZN9Framework24CAnimationBlendContainer16ReplaceAafAndAetEjPKvS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer16ReplaceAafAndAetEjPKvS2_
               (long param_1,uint param_2,undefined8 param_3,undefined8 param_4)

{
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x98,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  if (*(uint *)(param_1 + 0x58) <= param_2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x99,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2);
  }
  (*(code *)PTR__ZN9Framework17CAnimationElement16ReplaceAafAndAetEPKvS2__02cb5e58)
            (*(long *)(param_1 + 0x60) + (ulong)param_2 * 0x68,param_3,param_4);
  return;
}

// ==== Framework::CAnimationBlendContainer::Close()
// vaddr 0x1e5b614 | ghidra 0x1f5b614 | size 20 | symbol _ZN9Framework24CAnimationBlendContainer5CloseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer5CloseEv(long param_1)

{
  if (*(int *)(param_1 + 0x58) != 0) {
    *(undefined1 *)(param_1 + 0x99) = 1;
  }
  return;
}

// ==== Framework::CAnimationBlendContainer::pSearchForIndex(int) const
// vaddr 0x1e5b628 | ghidra 0x1f5b628 | size 72 | symbol _ZNK9Framework24CAnimationBlendContainer15pSearchForIndexEi | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK9Framework24CAnimationBlendContainer15pSearchForIndexEi(long param_1,int param_2)

{
  uint uVar1;
  int *piVar2;
  
  if (*(uint *)(param_1 + 0x58) == 0) {
    return 0xffffffff;
  }
  uVar1 = 0;
  piVar2 = (int *)(*(long *)(param_1 + 0x60) + 0x28);
  do {
    if (*piVar2 == param_2) {
      return uVar1;
    }
    uVar1 = uVar1 + 1;
    piVar2 = piVar2 + 0x1a;
  } while (uVar1 < *(uint *)(param_1 + 0x58));
  return 0xffffffff;
}

// ==== Framework::CAnimationBlendContainer::pSearchEmpty() const
// vaddr 0x1e5b670 | ghidra 0x1f5b670 | size 60 | symbol _ZNK9Framework24CAnimationBlendContainer12pSearchEmptyEv | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK9Framework24CAnimationBlendContainer12pSearchEmptyEv(long param_1)

{
  uint uVar1;
  int *piVar2;
  
  if (*(uint *)(param_1 + 0x58) != 0) {
    uVar1 = 0;
    piVar2 = (int *)(*(long *)(param_1 + 0x60) + 0x28);
    do {
      if (*piVar2 == -1) {
        return uVar1;
      }
      uVar1 = uVar1 + 1;
      piVar2 = piVar2 + 0x1a;
    } while (uVar1 < *(uint *)(param_1 + 0x58));
  }
  return 0xffffffff;
}

// ==== Framework::CAnimationBlendContainer::ProgressBlend(float)
// vaddr 0x1e5b6ac | ghidra 0x1f5b6ac | size 740 | symbol _ZN9Framework24CAnimationBlendContainer13ProgressBlendEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework24CAnimationBlendContainer13ProgressBlendEf(float param_1,long param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  uint uVar7;
  undefined8 *puVar8;
  ulong uVar9;
  long lVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uVar15;
  float fVar16;
  
  fVar16 = *(float *)(param_2 + 0x70);
  iVar4 = __isnanf(fVar16);
  if (((iVar4 != 0) || (iVar4 = __isfinitef(fVar16), iVar4 == 0)) || (fVar16 < 0.0)) {
    Framework::gDoAssert(char const*, int, char const*, ...)((double)fVar16,&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0xdd,&UNK_0296058d/*"m_AnimationSpeed was broken.(%f)"*/);
    fVar16 = *(float *)(param_2 + 0x70);
  }
  if (*(long *)(param_2 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0xe0,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  Framework::CBlendRatePlayer::Progress(float)(fVar16 * param_1,*(undefined8 *)(param_2 + 0x50));
  if (*(int *)(param_2 + 0x58) != 0) {
    uVar7 = 0;
    do {
      puVar8 = (undefined8 *)(*(long *)(param_2 + 0x60) + (ulong)uVar7 * 0x68);
      if ((*(int *)(puVar8 + 5) != -1) &&
         (*(int *)(*(long *)(param_2 + 0x60) + (ulong)uVar7 * 0x68 + 0x50) != 0)) {
        piVar6 = (int *)Framework::CBlendRatePlayer::crPiece(unsigned int) const(*(undefined8 *)(param_2 + 0x50));
        uVar15 = Framework::CBlendRatePlayer::CPiece::Rate() const();
        fVar16 = (float)uVar15;
        if ((fVar16 == 0.0) && (*piVar6 == 2)) {
          (**(code **)*puVar8)(puVar8);
        }
        else {
          if (fVar16 < 0.0) {
            Framework::gDoAssert(char const*, int, char const*, ...)((double)fVar16,&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x106,&UNK_029605ae/*"Internal error.(%f)"*/);
          }
          Framework::CAnimationElement::PresentBlendRate(float)(uVar15,puVar8);
        }
      }
      fVar3 = _UNK_027edb3c;
      fVar2 = _UNK_027edb34;
      fVar1 = _UNK_027edb30;
      fVar16 = _UNK_027e3fd0;
      uVar7 = uVar7 + 1;
    } while (uVar7 < *(uint *)(param_2 + 0x58));
    if (*(uint *)(param_2 + 0x58) != 0) {
      uVar7 = 0;
      do {
        lVar10 = *(long *)(param_2 + 0x60);
        uVar9 = (ulong)uVar7;
        puVar8 = (undefined8 *)(lVar10 + (ulong)uVar7 * 0x68);
        if (((*(int *)(puVar8 + 5) != -1) && (*(char *)(lVar10 + uVar9 * 0x68 + 0x60) == '\0')) &&
           ((*(char *)(lVar10 + uVar9 * 0x68 + 0x61) == '\0' &&
            (iVar4 = Framework::CAnimationElement::DirectionBlendParentElementId() const(puVar8), -1 < iVar4)))) {
          lVar11 = *(long *)(param_2 + 0x60);
          iVar4 = Framework::CAnimationElement::DirectionBlendParentElementId() const(puVar8);
          fVar12 = (float)Framework::CAnimationElement::DirectionBlendRadian() const(lVar11 + (long)iVar4 * 0x68);
          fVar13 = (float)Framework::CAnimationElement::DirectionBlend_RadianCenter() const(puVar8);
          fVar13 = fVar13 - fVar12;
          fVar12 = fVar16;
          fVar14 = fVar1;
          if ((fVar16 < fVar13) || (fVar12 = fVar1, fVar14 = fVar16, fVar13 < fVar1)) {
            fVar13 = (float)fmodf(fVar13 + fVar12,fVar2);
            fVar13 = fVar14 + fVar13;
          }
          fVar12 = fVar13 + fVar2;
          if (fVar1 <= fVar13) {
            fVar12 = fVar13;
          }
          fVar14 = fVar12 + fVar3;
          if (fVar12 <= fVar16) {
            fVar14 = fVar12;
          }
          fVar12 = -fVar14;
          if (0.0 <= fVar14) {
            fVar12 = fVar14;
          }
          fVar14 = (float)Framework::CAnimationElement::DirectionBlend_RadianRange() const(puVar8);
          fVar14 = fVar14 * 0.5;
          fVar13 = 0.0;
          if (fVar12 < fVar14) {
            fVar13 = (fVar14 - fVar12) / fVar14;
          }
          uVar5 = Framework::CAnimationElement::DirectionBlendParentElementId() const(puVar8);
          if (uVar7 != uVar5) {
            lVar10 = *(long *)(lVar10 + uVar9 * 0x68 + 0x38);
            if (fVar13 <= 0.0) {
              if (lVar10 != 0) {
                (**(code **)*puVar8)(puVar8);
              }
            }
            else if (lVar10 == 0) {
              Framework::CAnimationElement::Start(unsigned int)(puVar8,0);
            }
          }
          Framework::CAnimationElement::DirectionBlendRate(float)(fVar13,puVar8);
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 < *(uint *)(param_2 + 0x58));
    }
  }
  return;
}

// ==== Framework::CAnimationBlendContainer::ProgressFrame(float, Framework::CAnimationBlendContainer::tProgressFrame_Arguments const*)
// vaddr 0x1e5b990 | ghidra 0x1f5b990 | size 344 | symbol _ZN9Framework24CAnimationBlendContainer13ProgressFrameEfPKNS0_24tProgressFrame_ArgumentsE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer13ProgressFrameEfPKNS0_24tProgressFrame_ArgumentsE
               (float param_1,long param_2,long param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined8 uVar4;
  float fVar5;
  float fVar6;
  
  if (*(long *)(param_2 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x141,&UNK_027ee29f/*"m_pElements is null."*/);
  }
  fVar5 = *(float *)(param_2 + 0x70);
  iVar1 = __isnanf(fVar5);
  if (((iVar1 != 0) || (iVar1 = __isfinitef(fVar5), iVar1 == 0)) || (fVar5 < 0.0)) {
    Framework::gDoAssert(char const*, int, char const*, ...)((double)fVar5,&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x143,&UNK_0296058d/*"m_AnimationSpeed was broken.(%f)"*/);
    fVar5 = *(float *)(param_2 + 0x70);
  }
  uVar2 = *(uint *)(param_2 + 0x58);
  if (uVar2 != 0) {
    uVar3 = 0;
    do {
      if (*(int *)(*(long *)(param_2 + 0x60) + (ulong)uVar3 * 0x68 + 0x28) != -1) {
        Framework::CAnimationTimeElement::AndFlag(unsigned int)(*(long *)(param_2 + 0x60) + (ulong)uVar3 * 0x68,0xfffffff7);
        uVar2 = *(uint *)(param_2 + 0x58);
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < uVar2);
  }
  if (*(int *)(param_2 + 0x74) != 0) {
    uVar4 = Framework::CTransitionValue::Progress(float)(fVar5 * param_1);
    fVar6 = (float)uVar4;
    *(float *)(param_2 + 0x70) = fVar6;
    iVar1 = __isnanf();
    if (((iVar1 != 0) || (iVar1 = __isfinitef(uVar4), iVar1 == 0)) || (fVar6 < 0.0)) {
      Framework::gDoAssert(char const*, int, char const*, ...)((double)fVar6,&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x153,&UNK_0296058d/*"m_AnimationSpeed was broken.(%f)"*/);
    }
  }
  if (param_3 != 0) {
    return;
  }
  (*(code *)PTR__ZN9Framework24CAnimationBlendContainer20ProgressFrame_DirectEf_02caa7e0)
            (fVar5 * param_1,param_2);
  return;
}

// ==== Framework::CAnimationBlendContainer::ProgressFrame_Direct(float)
// vaddr 0x1e5bae8 | ghidra 0x1f5bae8 | size 764 | symbol _ZN9Framework24CAnimationBlendContainer20ProgressFrame_DirectEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer20ProgressFrame_DirectEf
               (undefined8 param_1,long param_2)

{
  float *pfVar1;
  uint uVar2;
  int iVar3;
  long lVar4;
  long *plVar5;
  uint uVar6;
  long *plVar7;
  long *plVar8;
  ulong uVar9;
  float fVar10;
  float fVar11;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  uVar2 = 0;
  if (*(int *)(param_2 + 0x58) != 0) {
    uVar6 = 0;
    uStack_70 = 0;
    uStack_68 = 0;
    do {
      if (((*(int *)(*(long *)(param_2 + 0x60) + (ulong)uVar6 * 0x68 + 0x28) != -1) &&
          (fVar11 = *(float *)(*(long *)(param_2 + 0x60) + (ulong)uVar6 * 0x68 + 0x54),
          uVar2 = Framework::CAnimationElement::DirectionBlendParentElementId() const(), 0.0 < fVar11)) && (0 < (int)uVar2)) {
        lVar4 = (ulong)(uVar2 >> 5) * 4;
        *(uint *)((long)&uStack_70 + lVar4) =
             *(uint *)((long)&uStack_70 + lVar4) | 1 << (ulong)(uVar2 & 0x1f);
      }
      uVar2 = *(uint *)(param_2 + 0x58);
      uVar6 = uVar6 + 1;
    } while (uVar6 < uVar2);
    if (uVar2 != 0) {
      uVar6 = 0;
      do {
        if ((*(uint *)((long)&uStack_70 + (long)((int)uVar6 >> 5) * 4) & 1 << (ulong)(uVar6 & 0x1f))
            != 0) {
          (**(code **)(*(long *)(*(long *)(param_2 + 0x60) + (ulong)uVar6 * 0x68) + 8))(param_1);
          uVar2 = *(uint *)(param_2 + 0x58);
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < uVar2);
    }
  }
  if ((*(byte *)(param_2 + 0x3a) & 1) != 0) {
    if (*(long *)(param_2 + 0x10) != 0) {
      operator delete[](void*)();
      uVar2 = *(uint *)(param_2 + 0x58);
      *(undefined8 *)(param_2 + 0x10) = 0;
    }
    *(undefined8 *)(param_2 + 0x18) = 0;
  }
  plVar8 = (long *)(param_2 + 0x20);
  *plVar8 = 0;
  *(undefined8 *)(param_2 + 0x28) = 0;
  *(undefined4 *)(param_2 + 0x40) = 0;
  if (uVar2 != 0) {
    uVar2 = 0;
    do {
      lVar4 = *(long *)(param_2 + 0x60);
      uVar9 = (ulong)uVar2;
      plVar7 = (long *)(lVar4 + (ulong)uVar2 * 0x68);
      if ((int)plVar7[5] != -1) {
        if ((*(char *)(lVar4 + uVar9 * 0x68 + 0x60) == '\0') &&
           (*(char *)(lVar4 + uVar9 * 0x68 + 0x61) == '\0')) {
          iVar3 = Framework::CAnimationElement::DirectionBlendParentElementId() const(plVar7);
          if (iVar3 < 0) {
            fVar11 = *(float *)(lVar4 + uVar9 * 0x68 + 0x54);
          }
          else {
            fVar11 = *(float *)(*(long *)(param_2 + 0x60) + (long)iVar3 * 0x68 + 0x54);
            fVar10 = (float)Framework::CAnimationElement::DirectionBlendRate() const(plVar7);
            fVar11 = fVar11 * fVar10;
          }
          if (0.0 < fVar11) {
            if (iVar3 < 0) {
              (**(code **)(*plVar7 + 8))(param_1,plVar7);
              lVar4 = *plVar8;
              plVar5 = plVar7;
            }
            else {
              lVar4 = *(long *)(param_2 + 0x60);
              iVar3 = Framework::CAnimationElement::DirectionBlendParentElementId() const(plVar7);
              plVar5 = (long *)(lVar4 + (long)iVar3 * 0x68);
              lVar4 = *plVar8;
            }
            if (-1 < lVar4) {
              fVar10 = *(float *)(plVar5 + 2);
              Aska::TArray<Framework::CAnimationBlendContainer::_tBlendMotionData, false>::Resize(long, bool)(param_2 + 8,lVar4 + 1,0);
              pfVar1 = (float *)(*(long *)(param_2 + 0x10) + lVar4 * 0x10);
              *pfVar1 = fVar11;
              pfVar1[1] = fVar10;
              *(long **)(pfVar1 + 2) = plVar7;
            }
          }
        }
        else if (0.0 < *(float *)(lVar4 + uVar9 * 0x68 + 0x54)) {
          (**(code **)(*plVar7 + 8))(param_1,plVar7);
          if ((*(char *)(lVar4 + uVar9 * 0x68 + 99) == '\0') ||
             ((*(byte *)(lVar4 + uVar9 * 0x68 + 0xc) >> 2 & 1) == 0)) {
            *(int *)(param_2 + 0x40) = *(int *)(param_2 + 0x40) + 1;
          }
          else {
            (**(code **)*plVar7)(plVar7);
          }
        }
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(param_2 + 0x58));
  }
  if (((*(char *)(param_2 + 0x98) == '\0') && (*(char *)(param_2 + 0x99) != '\0')) &&
     ((*plVar8 != 0 || (*(int *)(param_2 + 0x40) != 0)))) {
    (*(code *)PTR__ZN9Framework24CAnimationBlendContainer13PlayAnimationEPN4Aska9FiberTaskE_02cb1568
    )(param_2);
    return;
  }
  if (*(long **)(param_2 + 0x48) != (long *)0x0) {
    (**(code **)(**(long **)(param_2 + 0x48) + 0x20))();
    *(undefined8 *)(param_2 + 0x48) = 0;
  }
  return;
}

// ==== Framework::CAnimationBlendContainer::PlayAnimation(Aska::FiberTask*)
// vaddr 0x1e5bde4 | ghidra 0x1f5bde4 | size 852 | symbol _ZN9Framework24CAnimationBlendContainer13PlayAnimationEPN4Aska9FiberTaskE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer13PlayAnimationEPN4Aska9FiberTaskE(long param_1)

{
  long *plVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  byte bVar4;
  int iVar5;
  bool bVar6;
  long *plVar7;
  ulong uVar8;
  undefined8 *puVar9;
  uint uVar10;
  char *pcVar11;
  float *pfVar12;
  long lVar13;
  long lVar14;
  float fVar15;
  float fVar16;
  
  plVar7 = *(long **)(param_1 + 0x48);
  iVar5 = *(int *)(param_1 + 0x20);
  if ((plVar7 != (long *)0x0) && ((int)plVar7[5] != iVar5)) {
    (**(code **)(*plVar7 + 0x20))();
    plVar7 = (long *)0x0;
    *(undefined8 *)(param_1 + 0x48) = 0;
  }
  if (0 < iVar5) {
    if (plVar7 == (long *)0x0) {
      plVar7 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x48,PTR__ZSt7nothrow_02cb9a80);
      if (plVar7 == (long *)0x0) {
        *(undefined8 *)(param_1 + 0x48) = 0;
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x241,&UNK_029605c2/*"m_pBlendManager is null."*/);
        plVar7 = *(long **)(param_1 + 0x48);
      }
      else {
        puVar2 = PTR__ZTVN4Aska15AafBlendManager11_CalcNotifyE_02cc3328 + 0x10;
        *plVar7 = (long)(PTR__ZTVN4Aska15AafBlendManagerE_02cb9d28 + 0x10);
        plVar7[2] = (long)puVar2;
        Aska::AafBlendManager::Initialize()(plVar7);
        *(long **)(param_1 + 0x48) = plVar7;
      }
      Aska::AafBlendManager::Create(int)(plVar7,iVar5);
      plVar7 = *(long **)(param_1 + 0x48);
    }
    Aska::AafBlendManager::Open(int)(plVar7,iVar5);
    if (*(long *)(param_1 + 0x20) < 1) {
      Aska::AafBlendManager::Close(unsigned char)(*(undefined8 *)(param_1 + 0x48),2);
    }
    else {
      lVar13 = 0;
      bVar6 = false;
      lVar14 = 8;
      do {
        if ((*(long *)(*(long *)(*(long *)(param_1 + 0x10) + lVar14) + 0x38) != 0) &&
           (uVar8 = Aska::AafBlendManager::AddAaf(Aska::AafHandler*)(*(undefined8 *)(param_1 + 0x48)), (uVar8 & 1) == 0)) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x250,&UNK_029605db/*"Blend animation setting is failed."*/);
          bVar6 = true;
        }
        lVar13 = lVar13 + 1;
        lVar14 = lVar14 + 0x10;
      } while (lVar13 < *(long *)(param_1 + 0x20));
      Aska::AafBlendManager::Close(unsigned char)(*(undefined8 *)(param_1 + 0x48),2);
      if (bVar6) {
        return;
      }
    }
    if (0 < *(long *)(param_1 + 0x20)) {
      lVar13 = 0;
      uVar8 = 0;
      do {
        puVar3 = (undefined4 *)(*(long *)(param_1 + 0x10) + lVar13);
        Aska::AafBlendManager::SetPlayFrame(int, float)(puVar3[1],*(undefined8 *)(param_1 + 0x48),uVar8 & 0xffffffff);
        Aska::AafBlendManager::SetWeight(int, float)(*puVar3,*(undefined8 *)(param_1 + 0x48),uVar8 & 0xffffffff);
        uVar8 = uVar8 + 1;
        lVar13 = lVar13 + 0x10;
      } while ((long)uVar8 < *(long *)(param_1 + 0x20));
    }
    Aska::AafBlendManager::NormalizeWeights()(*(undefined8 *)(param_1 + 0x48));
  }
  lVar13 = *(long *)(param_1 + 0xa0);
  if (lVar13 != 0) {
    lVar14 = *(long *)(lVar13 + 8);
    *(undefined4 *)(lVar13 + 0x30) = *(undefined4 *)(lVar14 + 0x80);
    *(undefined4 *)(lVar13 + 0x34) = *(undefined4 *)(lVar14 + 0x84);
    *(undefined4 *)(lVar13 + 0x38) = *(undefined4 *)(lVar14 + 0x88);
    *(undefined4 *)(lVar13 + 0x3c) = *(undefined4 *)(lVar14 + 0x8c);
  }
  plVar7 = *(long **)(param_1 + 0x48);
  if ((plVar7 != (long *)0x0) && (0 < (int)plVar7[5])) {
    uVar8 = 0;
    fVar16 = 0.0;
    bVar4 = 1;
    lVar13 = 0x10;
    do {
      fVar15 = (float)Aska::AafBlendManager::GetWeight(int) const(plVar7,uVar8 & 0xffffffff);
      plVar7 = *(long **)(param_1 + 0x48);
      uVar8 = uVar8 + 1;
      fVar16 = fVar16 + fVar15;
      plVar1 = (long *)(plVar7[7] + lVar13);
      lVar13 = lVar13 + 0x30;
      bVar4 = bVar4 & *plVar1 == 0;
    } while ((long)uVar8 < (long)(int)plVar7[5]);
    if (!(bool)(fVar16 <= 0.0 | bVar4)) {
      (**(code **)(*plVar7 + 0x10))();
    }
  }
  puVar9 = *(undefined8 **)(param_1 + 0xa0);
  if (puVar9 != (undefined8 *)0x0) {
    (**(code **)*puVar9)(puVar9,*(undefined8 *)(param_1 + 0x48));
  }
  puVar9 = *(undefined8 **)(param_1 + 0xa8);
  if (puVar9 != (undefined8 *)0x0) {
    (**(code **)*puVar9)(puVar9,*(undefined8 *)(param_1 + 0x48));
  }
  puVar9 = *(undefined8 **)(param_1 + 0x68);
  if (puVar9 != (undefined8 *)0x0) {
    (**(code **)*puVar9)(puVar9,0);
  }
  if (*(int *)(param_1 + 0x58) != 0) {
    uVar10 = 0;
    do {
      lVar13 = *(long *)(param_1 + 0x60);
      uVar8 = (ulong)uVar10;
      if (((*(int *)(lVar13 + (ulong)uVar10 * 0x68 + 0x28) != -1) &&
          (((pcVar11 = (char *)(lVar13 + uVar8 * 0x68 + 0x60), *pcVar11 != '\0' ||
            (*(char *)(lVar13 + uVar8 * 0x68 + 0x61) != '\0')) &&
           (pfVar12 = (float *)(lVar13 + uVar8 * 0x68 + 0x54), 0.0 < *pfVar12)))) &&
         (lVar14 = *(long *)(lVar13 + uVar8 * 0x68 + 0x38), lVar14 != 0)) {
        *(uint *)(lVar14 + 0xc) = *(uint *)(lVar14 + 0xc) | 0x20;
        if (*pcVar11 == '\0') {
          Aska::AafHandler::BlendValues(float, float)(*(undefined4 *)(lVar13 + uVar8 * 0x68 + 0x10),*pfVar12);
        }
        else {
          Aska::AafHandler::AddValues(float)();
        }
      }
      uVar10 = uVar10 + 1;
    } while (uVar10 < *(uint *)(param_1 + 0x58));
  }
  return;
}

// ==== Framework::CAnimationBlendContainer::OrAllFlag() const
// vaddr 0x1e5c160 | ghidra 0x1f5c160 | size 188 | symbol _ZNK9Framework24CAnimationBlendContainer9OrAllFlagEv | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK9Framework24CAnimationBlendContainer9OrAllFlagEv(long param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  float fVar5;
  
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x2f6,&UNK_027ee29f/*"m_pElements is null."*/);
    iVar1 = *(int *)(param_1 + 0x58);
  }
  else {
    iVar1 = *(int *)(param_1 + 0x58);
  }
  if (iVar1 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = 0;
    uVar2 = 0;
    do {
      lVar4 = *(long *)(param_1 + 0x60);
      if ((*(int *)(lVar4 + (ulong)uVar2 * 0x68 + 0x28) != -1) &&
         (*(int *)(lVar4 + (ulong)uVar2 * 0x68 + 0x50) != 0)) {
        Framework::CBlendRatePlayer::crPiece(unsigned int) const(*(undefined8 *)(param_1 + 0x50));
        fVar5 = (float)Framework::CBlendRatePlayer::CPiece::Rate() const();
        if (0.0 < fVar5) {
          uVar3 = *(uint *)(lVar4 + (ulong)uVar2 * 0x68 + 0xc) | uVar3;
        }
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(param_1 + 0x58));
  }
  return uVar3;
}

// ==== Framework::CAnimationBlendContainer::NumElements() const
// vaddr 0x1e5c21c | ghidra 0x1f5c21c | size 8 | symbol _ZNK9Framework24CAnimationBlendContainer11NumElementsEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework24CAnimationBlendContainer11NumElementsEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x58);
}

// ==== Framework::CAnimationBlendContainer::rElement(int)
// vaddr 0x1e5c224 | ghidra 0x1f5c224 | size 172 | symbol _ZN9Framework24CAnimationBlendContainer8rElementEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework24CAnimationBlendContainer8rElementEi(long param_1,int param_2)

{
  uint uVar1;
  long lVar2;
  uint uVar3;
  
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x318,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar1 = *(uint *)(param_1 + 0x58);
  }
  else {
    uVar1 = *(uint *)(param_1 + 0x58);
  }
  if (uVar1 != 0) {
    lVar2 = *(long *)(param_1 + 0x60);
    uVar3 = 0;
    do {
      if (*(int *)(lVar2 + (ulong)uVar3 * 0x68 + 0x28) == param_2) {
        if (-1 < (int)uVar3) goto code_r0x01f5c2b4;
        goto code_r0x01f5c294;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < uVar1);
  }
  uVar3 = 0xffffffff;
code_r0x01f5c294:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x31a,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,param_2);
  lVar2 = *(long *)(param_1 + 0x60);
code_r0x01f5c2b4:
  return lVar2 + (long)(int)uVar3 * 0x68;
}

// ==== Framework::CAnimationBlendContainer::crElement(int) const
// vaddr 0x1e5c2d0 | ghidra 0x1f5c2d0 | size 172 | symbol _ZNK9Framework24CAnimationBlendContainer9crElementEi | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework24CAnimationBlendContainer9crElementEi(long param_1,int param_2)

{
  uint uVar1;
  long lVar2;
  uint uVar3;
  
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,800,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar1 = *(uint *)(param_1 + 0x58);
  }
  else {
    uVar1 = *(uint *)(param_1 + 0x58);
  }
  if (uVar1 != 0) {
    lVar2 = *(long *)(param_1 + 0x60);
    uVar3 = 0;
    do {
      if (*(int *)(lVar2 + (ulong)uVar3 * 0x68 + 0x28) == param_2) {
        if (-1 < (int)uVar3) goto code_r0x01f5c360;
        goto code_r0x01f5c340;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < uVar1);
  }
  uVar3 = 0xffffffff;
code_r0x01f5c340:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x322,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,param_2);
  lVar2 = *(long *)(param_1 + 0x60);
code_r0x01f5c360:
  return lVar2 + (long)(int)uVar3 * 0x68;
}

// ==== Framework::CAnimationBlendContainer::IsExist(int) const
// vaddr 0x1e5c37c | ghidra 0x1f5c37c | size 76 | symbol _ZNK9Framework24CAnimationBlendContainer7IsExistEi | lib libSOA-3.7.0.so | 2026-10-04
uint _ZNK9Framework24CAnimationBlendContainer7IsExistEi(long param_1,int param_2)

{
  uint uVar1;
  
  if (*(long *)(param_1 + 0x60) == 0) {
    return 0;
  }
  if (*(uint *)(param_1 + 0x58) != 0) {
    uVar1 = 0;
    do {
      if (*(int *)(*(long *)(param_1 + 0x60) + (ulong)uVar1 * 0x68 + 0x28) == param_2)
      goto code_r0x01f5c3b4;
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)(param_1 + 0x58));
  }
  uVar1 = 0xffffffff;
code_r0x01f5c3b4:
  return uVar1 >> 0x1f ^ 1;
}

// ==== Framework::CAnimationBlendContainer::BlendRateAtLastRequestedElement() const
// vaddr 0x1e5c3c8 | ghidra 0x1f5c3c8 | size 204 | symbol _ZNK9Framework24CAnimationBlendContainer31BlendRateAtLastRequestedElementEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1  [16]
_ZNK9Framework24CAnimationBlendContainer31BlendRateAtLastRequestedElementEv(long param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  undefined4 extraout_s0;
  undefined4 extraout_var;
  undefined8 extraout_var_00;
  undefined1 auVar5 [16];
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,800,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
  }
  else {
    uVar2 = *(uint *)(param_1 + 0x58);
  }
  if (uVar2 != 0) {
    lVar3 = *(long *)(param_1 + 0x60);
    uVar4 = 0;
    do {
      if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
        if (-1 < (int)uVar4) goto code_r0x01f5c458;
        goto code_r0x01f5c438;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < uVar2);
  }
  uVar4 = 0xffffffff;
code_r0x01f5c438:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x322,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x01f5c458:
  if (*(int *)(lVar3 + (long)(int)uVar4 * 0x68 + 0x50) != 0) {
    Framework::CBlendRatePlayer::crPiece(unsigned int) const(*(undefined8 *)(param_1 + 0x50));
    (*(code *)PTR__ZNK9Framework16CBlendRatePlayer6CPiece4RateEv_02c9fde8)();
    auVar5._4_4_ = extraout_var;
    auVar5._0_4_ = extraout_s0;
    auVar5._8_8_ = extraout_var_00;
    return auVar5;
  }
  return ZEXT816(0);
}

// ==== Framework::CAnimationBlendContainer::SetBlendRateElapsedTimeLimitToLastRequestedElement(float)
// vaddr 0x1e5c494 | ghidra 0x1f5c494 | size 200 | symbol _ZN9Framework24CAnimationBlendContainer50SetBlendRateElapsedTimeLimitToLastRequestedElementEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer50SetBlendRateElapsedTimeLimitToLastRequestedElementEf
               (undefined8 param_1,long param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  iVar1 = *(int *)(param_2 + 0x90);
  if (*(long *)(param_2 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,800,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_2 + 0x58);
  }
  else {
    uVar2 = *(uint *)(param_2 + 0x58);
  }
  if (uVar2 != 0) {
    lVar3 = *(long *)(param_2 + 0x60);
    uVar4 = 0;
    do {
      if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
        if (-1 < (int)uVar4) goto code_r0x011e36f0;
        goto code_r0x01f5c50c;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < uVar2);
  }
  uVar4 = 0xffffffff;
code_r0x01f5c50c:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x322,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_2 + 0x60);
code_r0x011e36f0:
  Framework::CBlendRatePlayer::rPiece(unsigned int) const(*(undefined8 *)(param_2 + 0x50),
                  *(undefined4 *)(lVar3 + (long)(int)uVar4 * 0x68 + 0x50));
  (*(code *)PTR__ZN9Framework16CBlendRatePlayer6CPiece28SetBlendRateElapsedTimeLimitEf_02ca9b68)
            (param_1);
  return;
}

// ==== Framework::CAnimationBlendContainer::MakeBlank(float)
// vaddr 0x1e5c55c | ghidra 0x1f5c55c | size 120 | symbol _ZN9Framework24CAnimationBlendContainer9MakeBlankEf | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN9Framework24CAnimationBlendContainer9MakeBlankEf(long param_1)

{
  ulong uVar1;
  undefined8 *puVar2;
  int iVar3;
  uint uVar4;
  
  uVar1 = Framework::CBlendRatePlayer::Add(float)(*(undefined8 *)(param_1 + 0x50));
  iVar3 = (int)(uVar1 >> 0x20);
  if ((iVar3 != 0) && (*(uint *)(param_1 + 0x58) != 0)) {
    puVar2 = *(undefined8 **)(param_1 + 0x60);
    uVar4 = 0;
    do {
      if ((*(int *)(puVar2 + 5) != -1) && (*(int *)(puVar2 + 10) == iVar3)) {
        (**(code **)*puVar2)();
        break;
      }
      uVar4 = uVar4 + 1;
      puVar2 = puVar2 + 0xd;
    } while (uVar4 < *(uint *)(param_1 + 0x58));
  }
  return uVar1 & 0xffffffff;
}

// ==== Framework::CAnimationBlendContainer::StartAnimation(int, float, bool)
// vaddr 0x1e5c5d4 | ghidra 0x1f5c5d4 | size 404 | symbol _ZN9Framework24CAnimationBlendContainer14StartAnimationEifb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Removing unreachable block (ram,0x01f5c71c) */

undefined8
_ZN9Framework24CAnimationBlendContainer14StartAnimationEifb
          (undefined8 param_1,long param_2,int param_3,ulong param_4)

{
  ulong uVar1;
  undefined8 *puVar2;
  long lVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  float fVar10;
  
  uVar4 = *(uint *)(param_2 + 0x58);
  if (uVar4 != 0) {
    if (*(long *)(param_2 + 0x60) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x368,&UNK_027ee29f/*"m_pElements is null."*/);
      uVar4 = *(uint *)(param_2 + 0x58);
      if (uVar4 == 0) {
        return 0;
      }
    }
    lVar9 = *(long *)(param_2 + 0x60);
    uVar6 = 0;
    do {
      if (*(int *)(lVar9 + (ulong)uVar6 * 0x68 + 0x28) == param_3) {
        if ((int)uVar6 < 0) {
          return 0;
        }
        lVar8 = lVar9 + (long)(int)uVar6 * 0x68;
        if (lVar8 == 0) {
          return 0;
        }
        fVar10 = *(float *)(lVar9 + (long)(int)uVar6 * 0x68 + 0x54);
        uVar1 = Framework::CBlendRatePlayer::Add(float)(param_1,*(undefined8 *)(param_2 + 0x50));
        iVar5 = (int)(uVar1 >> 0x20);
        if ((iVar5 == 0) || (*(uint *)(param_2 + 0x58) == 0)) goto code_r0x01f5c6f0;
        puVar2 = *(undefined8 **)(param_2 + 0x60);
        uVar7 = 0;
        goto code_r0x01f5c69c;
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < uVar4);
  }
  return 0;
code_r0x01f5c69c:
  if ((*(int *)(puVar2 + 5) != -1) && (*(int *)(puVar2 + 10) == iVar5)) {
    (**(code **)*puVar2)();
    goto code_r0x01f5c6f0;
  }
  uVar7 = uVar7 + 1;
  puVar2 = puVar2 + 0xd;
  if (*(uint *)(param_2 + 0x58) <= uVar7) {
code_r0x01f5c6f0:
    Framework::CAnimationElement::Start(unsigned int)(lVar8,uVar1 & 0xffffffff);
    lVar3 = Framework::CBlendRatePlayer::rPiece(unsigned int) const(*(undefined8 *)(param_2 + 0x50),uVar1 & 0xffffffff);
    if ((0.0 < fVar10) && ((param_4 & 1) != 0)) {
      Framework::CBlendRatePlayer::CPiece::SetBlendRateElapsedTime(float)(fVar10 * (float)param_1,lVar3);
    }
    if (*(char *)(lVar9 + (long)(int)uVar6 * 0x68 + 100) != '\0') {
      Framework::CBlendRatePlayer::SetTerminatedForIndependentCalcBlendRate()(*(undefined8 *)(param_2 + 0x50));
      *(undefined1 *)(lVar3 + 0x18) = 1;
    }
    Framework::CAnimationTimeElement::TerminateProcess(unsigned int)(lVar8,2);
    *(int *)(param_2 + 0x90) = param_3;
    *(float *)(param_2 + 0x94) = (float)param_1;
    return 1;
  }
  goto code_r0x01f5c69c;
}

// ==== Framework::CAnimationBlendContainer::StartDirectionBlendAnimation(Framework::CAnimationBlendContainer::tDirectionBlend_Arguments const*, int, float)
// vaddr 0x1e5c768 | ghidra 0x1f5c768 | size 316 | symbol _ZN9Framework24CAnimationBlendContainer28StartDirectionBlendAnimationEPKNS0_25tDirectionBlend_ArgumentsEif | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer28StartDirectionBlendAnimationEPKNS0_25tDirectionBlend_ArgumentsEif
               (undefined8 *param_1,int *param_2,uint param_3)

{
  ulong uVar1;
  long lVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar1 = (**(code **)*param_1)(param_1,*param_2,0);
  if ((uVar1 & 1) != 0) {
    uVar4 = *(uint *)(param_1 + 0xb);
    iVar3 = *param_2;
    if (uVar4 == 0) {
      uVar6 = 0xffffffff;
    }
    else {
      uVar6 = 0;
      do {
        if (*(int *)(param_1[0xc] + (ulong)uVar6 * 0x68 + 0x28) == iVar3) goto joined_r0x01f5c7ec;
        uVar6 = uVar6 + 1;
      } while (uVar6 < uVar4);
      uVar6 = 0xffffffff;
    }
joined_r0x01f5c7ec:
    if (0 < (int)param_3) {
      uVar1 = 0;
      if (uVar4 != 0) goto code_r0x01f5c864;
code_r0x01f5c824:
      do {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x39b,&UNK_02960620/*"pTargetElement is null."*/);
        lVar2 = 0;
        while( true ) {
          Framework::CAnimationElement::SetDirectionBlend(int, float, float)(param_2[uVar1 * 3 + 1],param_2[uVar1 * 3 + 2],lVar2,uVar6);
          uVar1 = uVar1 + 1;
          if (uVar1 == param_3) {
            return;
          }
          iVar3 = param_2[uVar1 * 3];
          uVar4 = *(uint *)(param_1 + 0xb);
          if (uVar4 == 0) break;
code_r0x01f5c864:
          uVar5 = 0;
          while (*(int *)(param_1[0xc] + (ulong)uVar5 * 0x68 + 0x28) != iVar3) {
            uVar5 = uVar5 + 1;
            if (uVar4 <= uVar5) goto code_r0x01f5c824;
          }
          if (((int)uVar5 < 0) || (lVar2 = param_1[0xc] + (long)(int)uVar5 * 0x68, lVar2 == 0))
          break;
        }
      } while( true );
    }
  }
  return;
}

// ==== Framework::CAnimationBlendContainer::DirectionBlendRadian(unsigned int, float)
// vaddr 0x1e5c8a4 | ghidra 0x1f5c8a4 | size 124 | symbol _ZN9Framework24CAnimationBlendContainer20DirectionBlendRadianEjf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer20DirectionBlendRadianEjf
               (undefined8 param_1,long param_2,int param_3)

{
  long lVar1;
  int iVar2;
  ulong uVar3;
  
  if (*(uint *)(param_2 + 0x58) != 0) {
    uVar3 = 0;
    do {
      iVar2 = (int)uVar3;
      if (*(int *)(*(long *)(param_2 + 0x60) + uVar3 * 0x68 + 0x28) == param_3) {
        if ((-1 < iVar2) && (lVar1 = *(long *)(param_2 + 0x60) + (long)iVar2 * 0x68, lVar1 != 0))
        goto code_r0x011e9810;
        break;
      }
      uVar3 = (ulong)(iVar2 + 1U);
    } while (iVar2 + 1U < *(uint *)(param_2 + 0x58));
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x3a8,&UNK_02960620/*"pTargetElement is null."*/);
  lVar1 = 0;
code_r0x011e9810:
  (*(code *)PTR__ZN9Framework17CAnimationElement20DirectionBlendRadianEf_02cacbf8)(param_1,lVar1);
  return;
}

// ==== Framework::CAnimationBlendContainer::StartAddAnimation(unsigned int, float, bool)
// vaddr 0x1e5c920 | ghidra 0x1f5c920 | size 344 | symbol _ZN9Framework24CAnimationBlendContainer17StartAddAnimationEjfb | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN9Framework24CAnimationBlendContainer17StartAddAnimationEjfb
                 (undefined8 param_1,long param_2,int param_3,ulong param_4)

{
  uint uVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  
  if (*(uint *)(param_2 + 0x58) != 0) {
    lVar3 = *(long *)(param_2 + 0x60);
    uVar1 = 0;
    do {
      if (*(int *)(lVar3 + (ulong)uVar1 * 0x68 + 0x28) == param_3) {
        if ((-1 < (int)uVar1) &&
           (plVar2 = (long *)(lVar3 + (long)(int)uVar1 * 0x68), plVar2 != (long *)0x0)) {
          if ((float)param_1 < 0.0) {
            (**(code **)*plVar2)(plVar2);
            return plVar2;
          }
          lVar4 = (long)(int)uVar1;
          if (*(long *)(lVar3 + lVar4 * 0x68 + 0x38) == 0) {
            Framework::CAnimationElement::Start(unsigned int)(plVar2,0);
          }
          Framework::CAnimationTimeElement::TerminateProcess(unsigned int)(plVar2,1);
          (**(code **)(*plVar2 + 0x10))(param_1,plVar2);
          Framework::CAnimationTimeElement::SetPresentFrame(float)(param_1,plVar2);
          if ((param_4 & 1) == 0) {
            (**(code **)(*plVar2 + 0x18))(0xbf800000,plVar2);
            *(undefined1 *)(lVar3 + lVar4 * 0x68 + 99) = 1;
          }
          else {
            (**(code **)(*plVar2 + 0x18))(param_1,plVar2);
          }
          Framework::CAnimationElement::PresentBlendRate(float)(0x3f800000,plVar2);
          *(undefined1 *)(lVar3 + lVar4 * 0x68 + 0x60) = 1;
          return plVar2;
        }
        break;
      }
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)(param_2 + 0x58));
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x3b6,&UNK_02960638/*"This animation is nothing.(%d)"*/,param_3);
  return (long *)0x0;
}

// ==== Framework::CAnimationBlendContainer::StartOverwriteAnimation(unsigned int, float, bool)
// vaddr 0x1e5ca78 | ghidra 0x1f5ca78 | size 344 | symbol _ZN9Framework24CAnimationBlendContainer23StartOverwriteAnimationEjfb | lib libSOA-3.7.0.so | 2026-10-04
long * _ZN9Framework24CAnimationBlendContainer23StartOverwriteAnimationEjfb
                 (undefined8 param_1,long param_2,int param_3,ulong param_4)

{
  uint uVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  
  if (*(uint *)(param_2 + 0x58) != 0) {
    lVar3 = *(long *)(param_2 + 0x60);
    uVar1 = 0;
    do {
      if (*(int *)(lVar3 + (ulong)uVar1 * 0x68 + 0x28) == param_3) {
        if ((-1 < (int)uVar1) &&
           (plVar2 = (long *)(lVar3 + (long)(int)uVar1 * 0x68), plVar2 != (long *)0x0)) {
          if ((float)param_1 < 0.0) {
            (**(code **)*plVar2)(plVar2);
            return plVar2;
          }
          lVar4 = (long)(int)uVar1;
          if (*(long *)(lVar3 + lVar4 * 0x68 + 0x38) == 0) {
            Framework::CAnimationElement::Start(unsigned int)(plVar2,0);
          }
          Framework::CAnimationTimeElement::TerminateProcess(unsigned int)(plVar2,1);
          (**(code **)(*plVar2 + 0x10))(param_1,plVar2);
          Framework::CAnimationTimeElement::SetPresentFrame(float)(param_1,plVar2);
          if ((param_4 & 1) == 0) {
            (**(code **)(*plVar2 + 0x18))(0xbf800000,plVar2);
            *(undefined1 *)(lVar3 + lVar4 * 0x68 + 99) = 1;
          }
          else {
            (**(code **)(*plVar2 + 0x18))(param_1,plVar2);
          }
          Framework::CAnimationElement::PresentBlendRate(float)(0x3f800000,plVar2);
          *(undefined1 *)(lVar3 + lVar4 * 0x68 + 0x61) = 1;
          return plVar2;
        }
        break;
      }
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)(param_2 + 0x58));
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x3de,&UNK_02960638/*"This animation is nothing.(%d)"*/,param_3);
  return (long *)0x0;
}

// ==== Framework::CAnimationBlendContainer::ResetAnimationControllers(Aska::AsfHandler*, Aska::CollisionHandler*)
// vaddr 0x1e5cbd0 | ghidra 0x1f5cbd0 | size 144 | symbol _ZN9Framework24CAnimationBlendContainer25ResetAnimationControllersEPN4Aska10AsfHandlerEPNS1_16CollisionHandlerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer25ResetAnimationControllersEPN4Aska10AsfHandlerEPNS1_16CollisionHandlerE
               (long param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  uint uVar2;
  long *plVar3;
  
  uVar1 = *(uint *)(param_1 + 0x58);
  if (uVar1 != 0) {
    uVar2 = 0;
    do {
      if (*(int *)(*(long *)(param_1 + 0x60) + (ulong)uVar2 * 0x68 + 0x28) != -1) {
        plVar3 = (long *)(*(long *)(param_1 + 0x60) + (ulong)uVar2 * 0x68 + 0x38);
        if (*plVar3 != 0) {
          Aska::AafHandler::DeleteControllers()();
          Aska::AafHandler::CreateControllers(Aska::AsfHandler*, Aska::CollisionHandler*, Aska::AsfTargetNameList*, bool)(*plVar3,param_2,param_3,0,1);
          uVar1 = *(uint *)(param_1 + 0x58);
        }
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < uVar1);
  }
  return;
}

// ==== Framework::CAnimationBlendContainer::StartFrame(float)
// vaddr 0x1e5cc60 | ghidra 0x1f5cc60 | size 208 | symbol _ZN9Framework24CAnimationBlendContainer10StartFrameEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer10StartFrameEf(undefined8 param_1,long param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_2 + 0x58);
  if (uVar2 == 0) {
    return;
  }
  iVar1 = *(int *)(param_2 + 0x90);
  if (*(long *)(param_2 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x318,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_2 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5ccd0;
  }
  lVar3 = *(long *)(param_2 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if ((int)uVar4 < 0) goto code_r0x01f5ccec;
      goto code_r0x01f5cd0c;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5ccd0:
  uVar4 = 0xffffffff;
code_r0x01f5ccec:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x31a,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_2 + 0x60);
code_r0x01f5cd0c:
                    /* WARNING: Could not recover jumptable at 0x01f5cd2c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)(lVar3 + (long)(int)uVar4 * 0x68) + 0x10))(param_1);
  return;
}

// ==== Framework::CAnimationBlendContainer::EndFrame(float)
// vaddr 0x1e5cd30 | ghidra 0x1f5cd30 | size 208 | symbol _ZN9Framework24CAnimationBlendContainer8EndFrameEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer8EndFrameEf(undefined8 param_1,long param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_2 + 0x58);
  if (uVar2 == 0) {
    return;
  }
  iVar1 = *(int *)(param_2 + 0x90);
  if (*(long *)(param_2 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x318,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_2 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5cda0;
  }
  lVar3 = *(long *)(param_2 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if ((int)uVar4 < 0) goto code_r0x01f5cdbc;
      goto code_r0x01f5cddc;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5cda0:
  uVar4 = 0xffffffff;
code_r0x01f5cdbc:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x31a,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_2 + 0x60);
code_r0x01f5cddc:
                    /* WARNING: Could not recover jumptable at 0x01f5cdfc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)(lVar3 + (long)(int)uVar4 * 0x68) + 0x18))(param_1);
  return;
}

// ==== Framework::CAnimationBlendContainer::GetAnimationLength(unsigned int)
// vaddr 0x1e5ce00 | ghidra 0x1f5ce00 | size 112 | symbol _ZN9Framework24CAnimationBlendContainer18GetAnimationLengthEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer18GetAnimationLengthEj(long param_1,int param_2)

{
  long lVar1;
  int iVar2;
  ulong uVar3;
  
  if (*(uint *)(param_1 + 0x58) != 0) {
    uVar3 = 0;
    do {
      iVar2 = (int)uVar3;
      if (*(int *)(*(long *)(param_1 + 0x60) + uVar3 * 0x68 + 0x28) == param_2) {
        if ((-1 < iVar2) && (lVar1 = *(long *)(param_1 + 0x60) + (long)iVar2 * 0x68, lVar1 != 0))
        goto code_r0x011f61c0;
        break;
      }
      uVar3 = (ulong)(iVar2 + 1U);
    } while (iVar2 + 1U < *(uint *)(param_1 + 0x58));
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x421,&UNK_02960620/*"pTargetElement is null."*/);
  lVar1 = 0;
code_r0x011f61c0:
  (*(code *)PTR__ZNK9Framework17CAnimationElement18GetAnimationLengthEv_02cb30d0)(lVar1);
  return;
}

// ==== Framework::CAnimationBlendContainer::PresentFrame(float)
// vaddr 0x1e5ce70 | ghidra 0x1f5ce70 | size 200 | symbol _ZN9Framework24CAnimationBlendContainer12PresentFrameEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer12PresentFrameEf(undefined8 param_1,long param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_2 + 0x58);
  if (uVar2 == 0) {
    return;
  }
  iVar1 = *(int *)(param_2 + 0x90);
  if (*(long *)(param_2 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x318,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_2 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5cee0;
  }
  lVar3 = *(long *)(param_2 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if ((int)uVar4 < 0) goto code_r0x01f5cefc;
      goto code_r0x011ebe00;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5cee0:
  uVar4 = 0xffffffff;
code_r0x01f5cefc:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x31a,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_2 + 0x60);
code_r0x011ebe00:
  (*(code *)PTR__ZN9Framework21CAnimationTimeElement15SetPresentFrameEf_02cadef0)
            (param_1,lVar3 + (long)(int)uVar4 * 0x68);
  return;
}

// ==== Framework::CAnimationBlendContainer::TerminateProcess(unsigned int)
// vaddr 0x1e5cf38 | ghidra 0x1f5cf38 | size 200 | symbol _ZN9Framework24CAnimationBlendContainer16TerminateProcessEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer16TerminateProcessEj(long param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_1 + 0x58);
  if (uVar2 == 0) {
    return;
  }
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x318,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5cfa8;
  }
  lVar3 = *(long *)(param_1 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if ((int)uVar4 < 0) goto code_r0x01f5cfc4;
      goto code_r0x011dcc80;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5cfa8:
  uVar4 = 0xffffffff;
code_r0x01f5cfc4:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x31a,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x011dcc80:
  (*(code *)PTR__ZN9Framework21CAnimationTimeElement16TerminateProcessEj_02ca6630)
            (lVar3 + (long)(int)uVar4 * 0x68,param_2);
  return;
}

// ==== Framework::CAnimationBlendContainer::IsEnableLoop() const
// vaddr 0x1e5d000 | ghidra 0x1f5d000 | size 184 | symbol _ZNK9Framework24CAnimationBlendContainer12IsEnableLoopEv | lib libSOA-3.7.0.so | 2026-10-04
byte _ZNK9Framework24CAnimationBlendContainer12IsEnableLoopEv(long param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_1 + 0x58);
  if (uVar2 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,800,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5d068;
  }
  lVar3 = *(long *)(param_1 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if (-1 < (int)uVar4) goto code_r0x01f5d09c;
      goto code_r0x01f5d07c;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5d068:
  uVar4 = 0xffffffff;
code_r0x01f5d07c:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x322,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x01f5d09c:
  return *(byte *)(lVar3 + (long)(int)uVar4 * 0x68 + 0xc) & 1;
}

// ==== Framework::CAnimationBlendContainer::IsEnableFrameStopAtEnd() const
// vaddr 0x1e5d0b8 | ghidra 0x1f5d0b8 | size 184 | symbol _ZNK9Framework24CAnimationBlendContainer22IsEnableFrameStopAtEndEv | lib libSOA-3.7.0.so | 2026-10-04
byte _ZNK9Framework24CAnimationBlendContainer22IsEnableFrameStopAtEndEv(long param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_1 + 0x58);
  if (uVar2 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,800,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5d120;
  }
  lVar3 = *(long *)(param_1 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if (-1 < (int)uVar4) goto code_r0x01f5d154;
      goto code_r0x01f5d134;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5d120:
  uVar4 = 0xffffffff;
code_r0x01f5d134:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x322,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x01f5d154:
  return *(byte *)(lVar3 + (long)(int)uVar4 * 0x68 + 0xc) >> 1 & 1;
}

// ==== Framework::CAnimationBlendContainer::IsEnableFreeTerm() const
// vaddr 0x1e5d170 | ghidra 0x1f5d170 | size 184 | symbol _ZNK9Framework24CAnimationBlendContainer16IsEnableFreeTermEv | lib libSOA-3.7.0.so | 2026-10-04
byte _ZNK9Framework24CAnimationBlendContainer16IsEnableFreeTermEv(long param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_1 + 0x58);
  if (uVar2 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,800,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5d1d8;
  }
  lVar3 = *(long *)(param_1 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if (-1 < (int)uVar4) goto code_r0x01f5d20c;
      goto code_r0x01f5d1ec;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5d1d8:
  uVar4 = 0xffffffff;
code_r0x01f5d1ec:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x322,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x01f5d20c:
  return *(byte *)(lVar3 + (long)(int)uVar4 * 0x68 + 0xe) >> 3 & 1;
}

// ==== Framework::CAnimationBlendContainer::IsLooped() const
// vaddr 0x1e5d228 | ghidra 0x1f5d228 | size 184 | symbol _ZNK9Framework24CAnimationBlendContainer8IsLoopedEv | lib libSOA-3.7.0.so | 2026-10-04
byte _ZNK9Framework24CAnimationBlendContainer8IsLoopedEv(long param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_1 + 0x58);
  if (uVar2 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,800,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5d290;
  }
  lVar3 = *(long *)(param_1 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if (-1 < (int)uVar4) goto code_r0x01f5d2c4;
      goto code_r0x01f5d2a4;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5d290:
  uVar4 = 0xffffffff;
code_r0x01f5d2a4:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x322,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x01f5d2c4:
  return *(byte *)(lVar3 + (long)(int)uVar4 * 0x68 + 0xc) >> 2 & 1;
}

// ==== Framework::CAnimationBlendContainer::IsLoopedAtOnce() const
// vaddr 0x1e5d2e0 | ghidra 0x1f5d2e0 | size 184 | symbol _ZNK9Framework24CAnimationBlendContainer14IsLoopedAtOnceEv | lib libSOA-3.7.0.so | 2026-10-04
byte _ZNK9Framework24CAnimationBlendContainer14IsLoopedAtOnceEv(long param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_1 + 0x58);
  if (uVar2 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,800,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5d348;
  }
  lVar3 = *(long *)(param_1 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if (-1 < (int)uVar4) goto code_r0x01f5d37c;
      goto code_r0x01f5d35c;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5d348:
  uVar4 = 0xffffffff;
code_r0x01f5d35c:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x322,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x01f5d37c:
  return *(byte *)(lVar3 + (long)(int)uVar4 * 0x68 + 0xc) >> 3 & 1;
}

// ==== Framework::CAnimationBlendContainer::NumLoop() const
// vaddr 0x1e5d398 | ghidra 0x1f5d398 | size 180 | symbol _ZNK9Framework24CAnimationBlendContainer7NumLoopEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework24CAnimationBlendContainer7NumLoopEv(long param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_1 + 0x58);
  if (uVar2 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,800,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5d400;
  }
  lVar3 = *(long *)(param_1 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if (-1 < (int)uVar4) goto code_r0x01f5d434;
      goto code_r0x01f5d414;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5d400:
  uVar4 = 0xffffffff;
code_r0x01f5d414:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x322,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x01f5d434:
  return *(undefined4 *)(lVar3 + (long)(int)uVar4 * 0x68 + 0x1c);
}

// ==== Framework::CAnimationBlendContainer::ClearLoopedFlag()
// vaddr 0x1e5d44c | ghidra 0x1f5d44c | size 180 | symbol _ZN9Framework24CAnimationBlendContainer15ClearLoopedFlagEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer15ClearLoopedFlagEv(long param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_1 + 0x58);
  if (uVar2 == 0) {
    return;
  }
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x318,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5d4b4;
  }
  lVar3 = *(long *)(param_1 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if ((int)uVar4 < 0) goto code_r0x01f5d4cc;
      goto code_r0x011ddd40;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5d4b4:
  uVar4 = 0xffffffff;
code_r0x01f5d4cc:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x31a,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x011ddd40:
  (*(code *)PTR__ZN9Framework21CAnimationTimeElement15ClearLoopedFlagEv_02ca6e90)
            (lVar3 + (long)(int)uVar4 * 0x68);
  return;
}

// ==== Framework::CAnimationBlendContainer::AnimationSpeed(float)
// vaddr 0x1e5d500 | ghidra 0x1f5d500 | size 108 | symbol _ZN9Framework24CAnimationBlendContainer14AnimationSpeedEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer14AnimationSpeedEf(undefined8 param_1,long param_2)

{
  int iVar1;
  float fVar2;
  
  if (*(int *)(param_2 + 0x58) != 0) {
    fVar2 = (float)param_1;
    *(float *)(param_2 + 0x70) = fVar2;
    iVar1 = __isnanf(param_1);
    if (((iVar1 != 0) || (iVar1 = __isfinitef(param_1), iVar1 == 0)) || (fVar2 < 0.0)) {
      Framework::gDoAssert(char const*, int, char const*, ...)((double)fVar2,&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x477,&UNK_0296058d/*"m_AnimationSpeed was broken.(%f)"*/);
    }
    *(undefined4 *)(param_2 + 0x74) = 0;
  }
  return;
}

// ==== Framework::CAnimationBlendContainer::AnimationSpeedByTransitionValue(unsigned int, float, float)
// vaddr 0x1e5d56c | ghidra 0x1f5d56c | size 284 | symbol _ZN9Framework24CAnimationBlendContainer31AnimationSpeedByTransitionValueEjff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer31AnimationSpeedByTransitionValueEjff
               (float param_1,float param_2,long param_3,uint param_4)

{
  int iVar1;
  float fVar2;
  
  if (*(int *)(param_3 + 0x58) == 0) {
    return;
  }
  fVar2 = *(float *)(param_3 + 0x70);
  iVar1 = __isnanf(fVar2);
  if (((iVar1 != 0) || (iVar1 = __isfinitef(fVar2), iVar1 == 0)) || (fVar2 < 0.0)) {
    Framework::gDoAssert(char const*, int, char const*, ...)((double)fVar2,&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x480,&UNK_0296058d/*"m_AnimationSpeed was broken.(%f)"*/);
    fVar2 = *(float *)(param_3 + 0x70);
  }
  *(undefined4 *)(param_3 + 0x74) = 0;
  if (param_4 == 6) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029606f3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TrasitionValue.h"*/,0x30,&UNK_0296074b/*"aType is unknown."*/);
  }
  else if (param_4 < 6) goto code_r0x01f5d610;
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029606f3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TrasitionValue.h"*/,0x31,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_4,6);
code_r0x01f5d610:
  *(uint *)(param_3 + 0x74) = param_4;
  *(float *)(param_3 + 0x7c) = fVar2;
  *(float *)(param_3 + 0x80) = param_1 - fVar2;
  if (param_2 <= 0.0) {
    Framework::gDoAssert(char const*, int, char const*, ...)((double)param_2,&UNK_029606f3/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TrasitionValue.h"*/,0x35,&UNK_0296075d/*"The argument 'aTotalTime' has gotten minus value.(%f)"*/);
    fVar2 = *(float *)(param_3 + 0x7c);
  }
  *(float *)(param_3 + 0x88) = fVar2;
  *(undefined4 *)(param_3 + 0x8c) = 0;
  *(float *)(param_3 + 0x84) = param_2;
  *(undefined4 *)(param_3 + 0x78) = 0x40400000;
  return;
}

// ==== Framework::CAnimationBlendContainer::AnimationSpeed() const
// vaddr 0x1e5d688 | ghidra 0x1f5d688 | size 116 | symbol _ZNK9Framework24CAnimationBlendContainer14AnimationSpeedEv | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK9Framework24CAnimationBlendContainer14AnimationSpeedEv(long param_1)

{
  int iVar1;
  float fVar2;
  
  if (*(int *)(param_1 + 0x58) == 0) {
    fVar2 = 0.0;
  }
  else {
    fVar2 = *(float *)(param_1 + 0x70);
    iVar1 = __isnanf(fVar2);
    if (((iVar1 != 0) || (iVar1 = __isfinitef(fVar2), iVar1 == 0)) || (fVar2 < 0.0)) {
      Framework::gDoAssert(char const*, int, char const*, ...)((double)fVar2,&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x48a,&UNK_0296058d/*"m_AnimationSpeed was broken.(%f)"*/);
      fVar2 = *(float *)(param_1 + 0x70);
    }
  }
  return fVar2;
}

// ==== Framework::CAnimationBlendContainer::StartFrame() const
// vaddr 0x1e5d6fc | ghidra 0x1f5d6fc | size 180 | symbol _ZNK9Framework24CAnimationBlendContainer10StartFrameEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework24CAnimationBlendContainer10StartFrameEv(long param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_1 + 0x58);
  if (uVar2 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,800,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5d764;
  }
  lVar3 = *(long *)(param_1 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if (-1 < (int)uVar4) goto code_r0x01f5d798;
      goto code_r0x01f5d778;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5d764:
  uVar4 = 0xffffffff;
code_r0x01f5d778:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x322,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x01f5d798:
  return *(undefined4 *)(lVar3 + (long)(int)uVar4 * 0x68 + 0x14);
}

// ==== Framework::CAnimationBlendContainer::PresentFrame() const
// vaddr 0x1e5d7b0 | ghidra 0x1f5d7b0 | size 180 | symbol _ZNK9Framework24CAnimationBlendContainer12PresentFrameEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework24CAnimationBlendContainer12PresentFrameEv(long param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_1 + 0x58);
  if (uVar2 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,800,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5d818;
  }
  lVar3 = *(long *)(param_1 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if (-1 < (int)uVar4) goto code_r0x01f5d84c;
      goto code_r0x01f5d82c;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5d818:
  uVar4 = 0xffffffff;
code_r0x01f5d82c:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x322,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x01f5d84c:
  return *(undefined4 *)(lVar3 + (long)(int)uVar4 * 0x68 + 0x10);
}

// ==== Framework::CAnimationBlendContainer::EndFrame() const
// vaddr 0x1e5d864 | ghidra 0x1f5d864 | size 180 | symbol _ZNK9Framework24CAnimationBlendContainer8EndFrameEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework24CAnimationBlendContainer8EndFrameEv(long param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_1 + 0x58);
  if (uVar2 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,800,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5d8cc;
  }
  lVar3 = *(long *)(param_1 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if (-1 < (int)uVar4) goto code_r0x01f5d900;
      goto code_r0x01f5d8e0;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5d8cc:
  uVar4 = 0xffffffff;
code_r0x01f5d8e0:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x322,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x01f5d900:
  return *(undefined4 *)(lVar3 + (long)(int)uVar4 * 0x68 + 0x18);
}

// ==== Framework::CAnimationBlendContainer::PresentBlendRate() const
// vaddr 0x1e5d918 | ghidra 0x1f5d918 | size 200 | symbol _ZNK9Framework24CAnimationBlendContainer16PresentBlendRateEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1  [16] _ZNK9Framework24CAnimationBlendContainer16PresentBlendRateEv(long param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  undefined4 extraout_s0;
  undefined4 extraout_var;
  undefined8 extraout_var_00;
  undefined1 auVar5 [16];
  
  uVar2 = *(uint *)(param_1 + 0x58);
  if (uVar2 == 0) goto code_r0x01f5d9d0;
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,800,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
    if (uVar2 != 0) goto code_r0x01f5d958;
  }
  else {
code_r0x01f5d958:
    lVar3 = *(long *)(param_1 + 0x60);
    uVar4 = 0;
    do {
      if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
        if ((int)uVar4 < 0) goto code_r0x01f5d98c;
        goto code_r0x01f5d9ac;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < uVar2);
  }
  uVar4 = 0xffffffff;
code_r0x01f5d98c:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x322,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x01f5d9ac:
  if (*(int *)(lVar3 + (long)(int)uVar4 * 0x68 + 0x50) != 0) {
    Framework::CBlendRatePlayer::crPiece(unsigned int) const(*(undefined8 *)(param_1 + 0x50));
    (*(code *)PTR__ZNK9Framework16CBlendRatePlayer6CPiece4RateEv_02c9fde8)();
    auVar5._4_4_ = extraout_var;
    auVar5._0_4_ = extraout_s0;
    auVar5._8_8_ = extraout_var_00;
    return auVar5;
  }
code_r0x01f5d9d0:
  return ZEXT816(0);
}

// ==== Framework::CAnimationBlendContainer::Flag() const
// vaddr 0x1e5d9e0 | ghidra 0x1f5d9e0 | size 180 | symbol _ZNK9Framework24CAnimationBlendContainer4FlagEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework24CAnimationBlendContainer4FlagEv(long param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_1 + 0x58);
  if (uVar2 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,800,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5da48;
  }
  lVar3 = *(long *)(param_1 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if (-1 < (int)uVar4) goto code_r0x01f5da7c;
      goto code_r0x01f5da5c;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5da48:
  uVar4 = 0xffffffff;
code_r0x01f5da5c:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x322,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x01f5da7c:
  return *(undefined4 *)(lVar3 + (long)(int)uVar4 * 0x68 + 0xc);
}

// ==== Framework::CAnimationBlendContainer::ClearAllFlag()
// vaddr 0x1e5da94 | ghidra 0x1f5da94 | size 180 | symbol _ZN9Framework24CAnimationBlendContainer12ClearAllFlagEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer12ClearAllFlagEv(long param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_1 + 0x58);
  if (uVar2 == 0) {
    return;
  }
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x318,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5dafc;
  }
  lVar3 = *(long *)(param_1 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if ((int)uVar4 < 0) goto code_r0x01f5db14;
      goto code_r0x011f85a0;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5dafc:
  uVar4 = 0xffffffff;
code_r0x01f5db14:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x31a,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x011f85a0:
  (*(code *)PTR__ZN9Framework21CAnimationTimeElement12ClearAllFlagEv_02cb42c0)
            (lVar3 + (long)(int)uVar4 * 0x68);
  return;
}

// ==== Framework::CAnimationBlendContainer::OrFlag(unsigned int)
// vaddr 0x1e5db48 | ghidra 0x1f5db48 | size 200 | symbol _ZN9Framework24CAnimationBlendContainer6OrFlagEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer6OrFlagEj(long param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_1 + 0x58);
  if (uVar2 == 0) {
    return;
  }
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x318,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5dbb8;
  }
  lVar3 = *(long *)(param_1 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if ((int)uVar4 < 0) goto code_r0x01f5dbd4;
      goto code_r0x011ae010;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5dbb8:
  uVar4 = 0xffffffff;
code_r0x01f5dbd4:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x31a,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x011ae010:
  (*(code *)PTR__ZN9Framework21CAnimationTimeElement6OrFlagEj_02c8eff8)
            (lVar3 + (long)(int)uVar4 * 0x68,param_2);
  return;
}

// ==== Framework::CAnimationBlendContainer::AndFlag(unsigned int)
// vaddr 0x1e5dc10 | ghidra 0x1f5dc10 | size 200 | symbol _ZN9Framework24CAnimationBlendContainer7AndFlagEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer7AndFlagEj(long param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_1 + 0x58);
  if (uVar2 == 0) {
    return;
  }
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(long *)(param_1 + 0x60) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x318,&UNK_027ee29f/*"m_pElements is null."*/);
    uVar2 = *(uint *)(param_1 + 0x58);
    if (uVar2 == 0) goto code_r0x01f5dc80;
  }
  lVar3 = *(long *)(param_1 + 0x60);
  uVar4 = 0;
  do {
    if (*(int *)(lVar3 + (ulong)uVar4 * 0x68 + 0x28) == iVar1) {
      if ((int)uVar4 < 0) goto code_r0x01f5dc9c;
      goto code_r0x011b6fb0;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
code_r0x01f5dc80:
  uVar4 = 0xffffffff;
code_r0x01f5dc9c:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,0x31a,&UNK_029605fe/*"This animation ID is invalid.(%d)"*/,iVar1);
  lVar3 = *(long *)(param_1 + 0x60);
code_r0x011b6fb0:
  (*(code *)PTR__ZN9Framework21CAnimationTimeElement7AndFlagEj_02c937c8)
            (lVar3 + (long)(int)uVar4 * 0x68,param_2);
  return;
}

// ==== Framework::CAnimationBlendContainer::DetachApk(void const*)
// vaddr 0x1e5dcd8 | ghidra 0x1f5dcd8 | size 204 | symbol _ZN9Framework24CAnimationBlendContainer9DetachApkEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer9DetachApkEPKv(long param_1,undefined8 param_2)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined1 auStack_48 [24];
  
  Framework::CAnimationPack::CAnimationPack()(auStack_48);
  Framework::CAnimationPack::Initialize(void const*)(auStack_48,param_2);
  iVar2 = Framework::CAnimationPack::NumPairElements() const(auStack_48);
  uVar3 = *(uint *)(param_1 + 0x58);
  bVar1 = uVar3 == 0;
  if (iVar2 != 0) {
    iVar5 = 0;
    do {
      if (!bVar1) {
        uVar4 = 0;
        do {
          if (*(int *)(*(long *)(param_1 + 0x60) + (ulong)uVar4 * 0x68 + 0x28) == iVar5) {
            if ((-1 < (int)uVar4) && (*(long *)(param_1 + 0x60) + (long)(int)uVar4 * 0x68 != 0)) {
              Framework::CAnimationElement::Release()();
              uVar3 = *(uint *)(param_1 + 0x58);
            }
            break;
          }
          uVar4 = uVar4 + 1;
        } while (uVar4 < uVar3);
      }
      iVar5 = iVar5 + 1;
      bVar1 = uVar3 == 0;
    } while (iVar5 != iVar2);
  }
  if (!bVar1) {
    *(undefined1 *)(param_1 + 0x99) = 1;
  }
  Framework::CAnimationPack::~CAnimationPack()(auStack_48);
  return;
}

// ==== Framework::CAnimationBlendContainer::InitializeKeepHipsPosition(Aska::HierarchicalObject*)
// vaddr 0x1e5dda4 | ghidra 0x1f5dda4 | size 176 | symbol _ZN9Framework24CAnimationBlendContainer26InitializeKeepHipsPositionEPN4Aska18HierarchicalObjectE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x01f5ddd0: Changing call to branch */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework24CAnimationBlendContainer26InitializeKeepHipsPositionEPN4Aska18HierarchicalObjectE
               (long param_1,long param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  long lVar5;
  long lVar6;
  long *plVar7;
  undefined8 uVar8;
  undefined *puVar9;
  
  if (*(long *)(param_1 + 0xa0) == 0) {
    plVar7 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x50,PTR__ZSt7nothrow_02cb9a80);
    if (plVar7 != (long *)0x0) {
      *(undefined4 *)(plVar7 + 2) = 0;
      lVar6 = _UNK_027dbb38;
      lVar5 = _UNK_027dbb30;
      *plVar7 = (long)(PTR__ZTVN9Framework17CHipsKeepPositionE_02cba560 + 0x10);
      plVar7[1] = param_2;
      plVar7[7] = lVar6;
      plVar7[6] = lVar5;
      uVar1 = *(undefined4 *)(param_2 + 0x80);
      uVar3 = *(undefined4 *)(param_2 + 0x84);
      *(undefined4 *)(plVar7 + 8) = uVar1;
      *(undefined4 *)((long)plVar7 + 0x44) = uVar3;
      uVar2 = *(undefined4 *)(param_2 + 0x88);
      uVar4 = *(undefined4 *)(param_2 + 0x8c);
      *(undefined4 *)(plVar7 + 4) = uVar1;
      *(undefined4 *)((long)plVar7 + 0x24) = uVar3;
      *(undefined4 *)(plVar7 + 9) = uVar2;
      *(undefined4 *)((long)plVar7 + 0x4c) = uVar4;
      *(undefined4 *)(plVar7 + 5) = uVar2;
      *(undefined4 *)((long)plVar7 + 0x2c) = uVar4;
      *(long **)(param_1 + 0xa0) = plVar7;
      return;
    }
    *(undefined8 *)(param_1 + 0xa0) = 0;
    puVar9 = &UNK_02960681/*"m_pHipsKeepPositionInfo is null."*/;
    uVar8 = 0x50f;
  }
  else {
    puVar9 = &UNK_02960657/*"m_pHipsKeepPositionInfo isn't null.(%08x)"*/;
    uVar8 = 0x50d;
  }
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,uVar8,puVar9);
  return;
}

// ==== Framework::CAnimationBlendContainer::InitializeKeepPosRootPosition(Aska::HierarchicalObject*)
// vaddr 0x1e5de54 | ghidra 0x1f5de54 | size 140 | symbol _ZN9Framework24CAnimationBlendContainer29InitializeKeepPosRootPositionEPN4Aska18HierarchicalObjectE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x01f5de80: Changing call to branch */

void _ZN9Framework24CAnimationBlendContainer29InitializeKeepPosRootPositionEPN4Aska18HierarchicalObjectE
               (long param_1,long param_2)

{
  long *plVar1;
  undefined8 uVar2;
  undefined *puVar3;
  
  if (*(long *)(param_1 + 0xa8) == 0) {
    plVar1 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x18,PTR__ZSt7nothrow_02cb9a80);
    if (plVar1 != (long *)0x0) {
      *(undefined4 *)(plVar1 + 2) = 0;
      *plVar1 = (long)(PTR__ZTVN9Framework20CPosRootKeepPositionE_02cbc910 + 0x10);
      plVar1[1] = param_2;
      *(long **)(param_1 + 0xa8) = plVar1;
      return;
    }
    *(undefined8 *)(param_1 + 0xa8) = 0;
    puVar3 = &UNK_029606cf/*"m_pPosRootKeepPositionInfo is null."*/;
    uVar2 = 0x519;
  }
  else {
    puVar3 = &UNK_029606a2/*"m_pPosRootKeepPositionInfo isn't null.(%08x)"*/;
    uVar2 = 0x517;
  }
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(&UNK_029604c5/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationBlendContainer.cpp"*/,uVar2,puVar3);
  return;
}

// ==== Framework::CAnimationBlendContainer::DeleteBlendManager()
// vaddr 0x1e5dee0 | ghidra 0x1f5dee0 | size 40 | symbol _ZN9Framework24CAnimationBlendContainer18DeleteBlendManagerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework24CAnimationBlendContainer18DeleteBlendManagerEv(long param_1)

{
  if (*(long **)(param_1 + 0x48) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x48) + 0x20))();
    *(undefined8 *)(param_1 + 0x48) = 0;
  }
  return;
}

// ==== Aska::TArray<Framework::CAnimationBlendContainer::_tBlendMotionData, false>::~TArray()
// vaddr 0x1e5e1e4 | ghidra 0x1f5e1e4 | size 60 | symbol _ZN4Aska6TArrayIN9Framework24CAnimationBlendContainer17_tBlendMotionDataELb0EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska6TArrayIN9Framework24CAnimationBlendContainer17_tBlendMotionDataELb0EED0Ev
               (long *param_1)

{
  *param_1 = (long)(
                   PTR__ZTVN4Aska6TArrayIN9Framework24CAnimationBlendContainer17_tBlendMotionDataELb0EEE_02cc4e98
                   + 0x10);
  *(ushort *)((long)param_1 + 0x32) = *(ushort *)((long)param_1 + 0x32) | 1;
  if (param_1[1] != 0) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
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

// ==== Framework::CAnimationElement::CAnimationElement()
// vaddr 0x1e5e358 | ghidra 0x1f5e358 | size 56 | symbol _ZN9Framework17CAnimationElementC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElementC1Ev(long *param_1)

{
  undefined *puVar1;
  
  *(undefined1 *)(param_1 + 1) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  puVar1 = PTR__ZTVN9Framework17CAnimationElementE_02cbbfb0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[7] = 0;
  *(undefined1 *)((long)param_1 + 100) = 0;
  *(undefined8 *)((long)param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 5) = 0xffffffff;
  *param_1 = (long)(puVar1 + 0x10);
  *(undefined8 *)((long)param_1 + 0x54) = 0;
  return;
}

// ==== Framework::CAnimationElement::~CAnimationElement()
// vaddr 0x1e5e390 | ghidra 0x1f5e390 | size 100 | symbol _ZN9Framework17CAnimationElementD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElementD2Ev(long *param_1)

{
  int iVar1;
  long *plVar2;
  
  plVar2 = (long *)param_1[7];
  *param_1 = (long)(PTR__ZTVN9Framework17CAnimationElementE_02cbbfb0 + 0x10);
  if (plVar2 != (long *)0x0) {
    iVar1 = (int)plVar2[1] + -1;
    *(int *)(plVar2 + 1) = iVar1;
    if (iVar1 == 0) {
      (**(code **)(*plVar2 + 8))();
    }
    param_1[7] = 0;
  }
  param_1[8] = 0;
  param_1[9] = 0;
  *(undefined4 *)(param_1 + 5) = 0xffffffff;
  if (param_1[0xb] != 0) {
    operator delete(void*)();
    param_1[0xb] = 0;
  }
  return;
}

// ==== Framework::CAnimationElement::Release()
// vaddr 0x1e5e3f4 | ghidra 0x1f5e3f4 | size 84 | symbol _ZN9Framework17CAnimationElement7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement7ReleaseEv(long param_1)

{
  int iVar1;
  long *plVar2;
  
  plVar2 = *(long **)(param_1 + 0x38);
  if (plVar2 != (long *)0x0) {
    iVar1 = (int)plVar2[1] + -1;
    *(int *)(plVar2 + 1) = iVar1;
    if (iVar1 == 0) {
      (**(code **)(*plVar2 + 8))();
    }
    *(undefined8 *)(param_1 + 0x38) = 0;
  }
  *(undefined8 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0xffffffff;
  if (*(long *)(param_1 + 0x58) != 0) {
    operator delete(void*)();
    *(undefined8 *)(param_1 + 0x58) = 0;
  }
  return;
}

// ==== Framework::CAnimationElement::~CAnimationElement()
// vaddr 0x1e5e448 | ghidra 0x1f5e448 | size 100 | symbol _ZN9Framework17CAnimationElementD0Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x01f5e49c: Changing call to branch */

void _ZN9Framework17CAnimationElementD0Ev(long *param_1)

{
  int iVar1;
  long *plVar2;
  
  plVar2 = (long *)param_1[7];
  *param_1 = (long)(PTR__ZTVN9Framework17CAnimationElementE_02cbbfb0 + 0x10);
  if (plVar2 != (long *)0x0) {
    iVar1 = (int)plVar2[1] + -1;
    *(int *)(plVar2 + 1) = iVar1;
    if (iVar1 == 0) {
      (**(code **)(*plVar2 + 8))();
    }
    param_1[7] = 0;
  }
  param_1[8] = 0;
  param_1[9] = 0;
  *(undefined4 *)(param_1 + 5) = 0xffffffff;
  if ((long *)param_1[0xb] != (long *)0x0) {
    param_1 = (long *)param_1[0xb];
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CAnimationElement::Initialize(Aska::AsfHandler&, void const*, int, bool)
// vaddr 0x1e5e4ac | ghidra 0x1f5e4ac | size 176 | symbol _ZN9Framework17CAnimationElement10InitializeERN4Aska10AsfHandlerEPKvib | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement10InitializeERN4Aska10AsfHandlerEPKvib
               (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,byte param_5)

{
  if (*(long *)(param_1 + 0x38) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296095c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationElement.cpp"*/,0x2e,&UNK_029609b8/*"m_pAafHandler isn't null.(%08x)"*/);
  }
  if (*(long *)(param_1 + 0x40) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296095c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationElement.cpp"*/,0x2f,&UNK_029609d8/*"m_pAsfHandler isn't null.(%08x)"*/);
  }
  if (*(long *)(param_1 + 0x48) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296095c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationElement.cpp"*/,0x30,&UNK_029609f8/*"m_pAet isn't null.(%08x)"*/);
  }
  *(undefined4 *)(param_1 + 0x28) = param_4;
  *(undefined8 *)(param_1 + 0x40) = param_2;
  *(undefined8 *)(param_1 + 0x30) = param_3;
  *(byte *)(param_1 + 0x60) = param_5 & 1;
  Framework::CAnimationTimeElement::Initialize()(param_1);
  (*(code *)PTR__ZN9Framework17CAnimationElement16CreateAafHandlerEv_02ca6c30)(param_1);
  return;
}

// ==== Framework::CAnimationElement::AfterInitialize()
// vaddr 0x1e5e55c | ghidra 0x1f5e55c | size 24 | symbol _ZN9Framework17CAnimationElement15AfterInitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement15AfterInitializeEv(undefined8 param_1)

{
  Framework::CAnimationTimeElement::Initialize()();
  (*(code *)PTR__ZN9Framework17CAnimationElement16CreateAafHandlerEv_02ca6c30)(param_1);
  return;
}

// ==== Framework::CAnimationElement::CreateAafHandler()
// vaddr 0x1e5e574 | ghidra 0x1f5e574 | size 352 | symbol _ZN9Framework17CAnimationElement16CreateAafHandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement16CreateAafHandlerEv(long *param_1)

{
  long lVar1;
  int iVar2;
  long lVar3;
  ulong uVar4;
  long *plVar5;
  undefined8 uVar6;
  undefined *puVar7;
  uint uVar8;
  undefined4 uVar9;
  
  if ((param_1[7] == 0) && (param_1[6] != 0)) {
    lVar3 = Aska::AafHandler::Instantiate()();
    param_1[7] = lVar3;
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296095c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationElement.cpp"*/,0x92,&UNK_02960a4f/*"m_pAafHandler is null."*/);
      lVar3 = param_1[7];
    }
    *(int *)(lVar3 + 8) = *(int *)(lVar3 + 8) + 1;
    lVar3 = param_1[6];
    lVar1 = param_1[7];
    uVar8 = *(uint *)(lVar1 + 0xc);
    if ((uVar8 & 0x18) != 0) {
      Aska::AafHandler::DeleteControllers()(lVar1);
      uVar8 = *(uint *)(lVar1 + 0xc);
    }
    if (((uVar8 >> 2 & 1) == 0) && (*(long *)(lVar1 + 0x10) != 0)) {
      operator delete[](void*)();
      uVar8 = *(uint *)(lVar1 + 0xc);
      *(undefined8 *)(lVar1 + 0x10) = 0;
    }
    *(long *)(lVar1 + 0x10) = lVar3;
    *(uint *)(lVar1 + 0xc) = uVar8 & 0xfffffffa | 4;
    uVar4 = Aska::AafHandler::CreateControllers(Aska::AsfHandler*, Aska::CollisionHandler*, Aska::AsfTargetNameList*, bool)(param_1[7],param_1[8],0,0,1);
    if ((uVar4 & 1) == 0) {
      if (*(long *)(param_1[7] + 0x28) == 0) {
        puVar7 = &UNK_02960a9e/*"CreateControllers failed."*/;
        uVar6 = 0x9f;
      }
      else {
        puVar7 = &UNK_02960a66/*"CreateControllers failed. Any controller was not found."*/;
        uVar6 = 0x9b;
      }
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296095c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationElement.cpp"*/,uVar6,puVar7);
      plVar5 = (long *)param_1[7];
      if (plVar5 != (long *)0x0) {
        iVar2 = (int)plVar5[1] + -1;
        *(int *)(plVar5 + 1) = iVar2;
        if (iVar2 == 0) {
          (**(code **)(*plVar5 + 8))();
        }
        param_1[7] = 0;
      }
    }
    else if (*(float *)(param_1 + 3) < 0.0) {
      if (param_1[7] == 0) {
        uVar9 = 0x3f800000;
      }
      else {
        uVar9 = *(undefined4 *)(*(long *)(param_1[7] + 0x28) + 0x10);
      }
                    /* WARNING: Could not recover jumptable at 0x01f5e6d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_1 + 0x18))(uVar9,param_1);
      return;
    }
  }
  return;
}

// ==== Framework::CAnimationElement::ReplaceAafAndAet(void const*, void const*)
// vaddr 0x1e5e6d4 | ghidra 0x1f5e6d4 | size 160 | symbol _ZN9Framework17CAnimationElement16ReplaceAafAndAetEPKvS2_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement16ReplaceAafAndAetEPKvS2_
               (long param_1,undefined8 param_2,int *param_3)

{
  int iVar1;
  long *plVar2;
  
  plVar2 = *(long **)(param_1 + 0x38);
  if (plVar2 != (long *)0x0) {
    iVar1 = (int)plVar2[1] + -1;
    *(int *)(plVar2 + 1) = iVar1;
    if (iVar1 == 0) {
      (**(code **)(*plVar2 + 8))();
    }
    *(undefined8 *)(param_1 + 0x38) = 0;
  }
  *(undefined8 *)(param_1 + 0x30) = param_2;
  if (param_3 != (int *)0x0) {
    *(int **)(param_1 + 0x48) = param_3;
    if ((param_3[1] != 0x12060400) || (*param_3 != 0x41455400)) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296095c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationElement.cpp"*/,0x60,&UNK_02960a3c/*"Illegal Aet image."*/);
    }
  }
  Framework::CAnimationTimeElement::Initialize()(param_1);
  (*(code *)PTR__ZN9Framework17CAnimationElement16CreateAafHandlerEv_02ca6c30)(param_1);
  return;
}

// ==== Framework::CAnimationElement::DeleteAafHandler()
// vaddr 0x1e5e774 | ghidra 0x1f5e774 | size 56 | symbol _ZN9Framework17CAnimationElement16DeleteAafHandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement16DeleteAafHandlerEv(long param_1)

{
  int iVar1;
  long *plVar2;
  
  plVar2 = *(long **)(param_1 + 0x38);
  if (plVar2 != (long *)0x0) {
    iVar1 = (int)plVar2[1] + -1;
    *(int *)(plVar2 + 1) = iVar1;
    if (iVar1 == 0) {
      (**(code **)(*plVar2 + 8))();
    }
    *(undefined8 *)(param_1 + 0x38) = 0;
  }
  return;
}

// ==== Framework::CAnimationElement::AttachAet(void const*)
// vaddr 0x1e5e7ac | ghidra 0x1f5e7ac | size 108 | symbol _ZN9Framework17CAnimationElement9AttachAetEPKv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement9AttachAetEPKv
               (long param_1,int *param_2,undefined8 param_3,ulong param_4)

{
  undefined8 uVar1;
  undefined *puVar2;
  
  if (*(long *)(param_1 + 0x48) == 0) {
    *(int **)(param_1 + 0x48) = param_2;
    if ((param_2[1] == 0x12060400) && (*param_2 == 0x41455400)) {
      return;
    }
    puVar2 = &UNK_02960a3c/*"Illegal Aet image."*/;
    uVar1 = 0x60;
  }
  else {
    param_4 = (ulong)*(uint *)(param_1 + 0x28);
    puVar2 = &UNK_02960a28/*"AET isn't NULL.(%d)"*/;
    uVar1 = 0x5b;
  }
  (*(code *)PTR__ZN9Framework9gDoAssertEPKciS1_z_02ca3240)(&UNK_0296095c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationElement.cpp"*/,uVar1,puVar2,param_4);
  return;
}

// ==== Framework::CAnimationElement::Reset()
// vaddr 0x1e5e818 | ghidra 0x1f5e818 | size 36 | symbol _ZN9Framework17CAnimationElement5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement5ResetEv(long param_1)

{
  Framework::CAnimationTimeElement::Reset()();
  *(undefined8 *)(param_1 + 0x50) = 0;
  if (*(long *)(param_1 + 0x58) != 0) {
    *(undefined4 *)(*(long *)(param_1 + 0x58) + 0xc) = 0;
  }
  return;
}

// ==== Framework::CAnimationElement::PresentBlendRate(float)
// vaddr 0x1e5e83c | ghidra 0x1f5e83c | size 8 | symbol _ZN9Framework17CAnimationElement16PresentBlendRateEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement16PresentBlendRateEf(undefined4 param_1,long param_2)

{
  *(undefined4 *)(param_2 + 0x54) = param_1;
  return;
}

// ==== Framework::CAnimationElement::DirectionBlendRadian(float)
// vaddr 0x1e5e844 | ghidra 0x1f5e844 | size 16 | symbol _ZN9Framework17CAnimationElement20DirectionBlendRadianEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement20DirectionBlendRadianEf(undefined4 param_1,long param_2)

{
  if (*(long *)(param_2 + 0x58) != 0) {
    *(undefined4 *)(*(long *)(param_2 + 0x58) + 0xc) = param_1;
  }
  return;
}

// ==== Framework::CAnimationElement::Start(unsigned int)
// vaddr 0x1e5e854 | ghidra 0x1f5e854 | size 44 | symbol _ZN9Framework17CAnimationElement5StartEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement5StartEj(undefined8 *param_1,undefined4 param_2)

{
  (**(code **)*param_1)();
  *(undefined4 *)(param_1 + 10) = param_2;
  return;
}

// ==== Framework::CAnimationElement::GetAnimationLength() const
// vaddr 0x1e5e880 | ghidra 0x1f5e880 | size 28 | symbol _ZNK9Framework17CAnimationElement18GetAnimationLengthEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework17CAnimationElement18GetAnimationLengthEv(long param_1)

{
  if (*(long *)(param_1 + 0x38) != 0) {
    return *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x38) + 0x28) + 0x10);
  }
  return 0x3f800000;
}

// ==== Framework::CAnimationElement::Progress(float)
// vaddr 0x1e5e89c | ghidra 0x1f5e89c | size 68 | symbol _ZN9Framework17CAnimationElement8ProgressEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement8ProgressEf(undefined8 param_1,long param_2)

{
  if (*(long *)(param_2 + 0x40) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296095c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationElement.cpp"*/,0xb2,&UNK_02960a11/*"m_pAsfHandler is null."*/);
  }
  (*(code *)PTR__ZN9Framework21CAnimationTimeElement8ProgressEf_02cabd58)(param_1,param_2);
  return;
}

// ==== Framework::CAnimationElement::DirectSetValues(Aska::FiberTask*)
// vaddr 0x1e5e8e0 | ghidra 0x1f5e8e0 | size 24 | symbol _ZN9Framework17CAnimationElement15DirectSetValuesEPN4Aska9FiberTaskE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement15DirectSetValuesEPN4Aska9FiberTaskE(long param_1)

{
  if (*(long *)(param_1 + 0x38) != 0) {
    (*(code *)PTR__ZN4Aska10AafHandler9SetValuesEf_02c98898)(*(undefined4 *)(param_1 + 0x10));
    return;
  }
  return;
}

// ==== Framework::CAnimationElement::SetStartFrame(float)
// vaddr 0x1e5e8f8 | ghidra 0x1f5e8f8 | size 16 | symbol _ZN9Framework17CAnimationElement13SetStartFrameEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement13SetStartFrameEf(float param_1)

{
  if (param_1 < 0.0) {
    param_1 = 0.0;
  }
  (*(code *)PTR__ZN9Framework21CAnimationTimeElement13SetStartFrameEf_02c915f0)(param_1);
  return;
}

// ==== Framework::CAnimationElement::SetEndFrame(float)
// vaddr 0x1e5e908 | ghidra 0x1f5e908 | size 28 | symbol _ZN9Framework17CAnimationElement11SetEndFrameEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement11SetEndFrameEf(float param_1,long param_2)

{
  if ((*(long *)(param_2 + 0x38) != 0) && (param_1 < 0.0)) {
    param_1 = *(float *)(*(long *)(*(long *)(param_2 + 0x38) + 0x28) + 0x10);
  }
  (*(code *)PTR__ZN9Framework21CAnimationTimeElement11SetEndFrameEf_02c97238)(param_1);
  return;
}

// ==== Framework::CAnimationElement::OverwriteAetValueX(unsigned int, float)
// vaddr 0x1e5e924 | ghidra 0x1f5e924 | size 104 | symbol _ZN9Framework17CAnimationElement18OverwriteAetValueXEjf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement18OverwriteAetValueXEjf
               (undefined4 param_1,long param_2,uint param_3)

{
  long lVar1;
  undefined4 *puVar2;
  
  lVar1 = *(long *)(param_2 + 0x48);
  if (lVar1 != 0) {
    if (*(uint *)(lVar1 + 8) <= param_3) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296095c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationElement.cpp"*/,0xe9,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_3);
      lVar1 = *(long *)(param_2 + 0x48);
    }
    puVar2 = (undefined4 *)Framework::AaiExtractTranslate::tImage::rX(unsigned int)(lVar1,param_3);
    *puVar2 = param_1;
  }
  return;
}

// ==== Framework::CAnimationElement::OverwriteAetValueY(unsigned int, float)
// vaddr 0x1e5ebf8 | ghidra 0x1f5ebf8 | size 104 | symbol _ZN9Framework17CAnimationElement18OverwriteAetValueYEjf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement18OverwriteAetValueYEjf
               (undefined4 param_1,long param_2,uint param_3)

{
  long lVar1;
  undefined4 *puVar2;
  
  lVar1 = *(long *)(param_2 + 0x48);
  if (lVar1 != 0) {
    if (*(uint *)(lVar1 + 8) <= param_3) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296095c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationElement.cpp"*/,0xf2,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_3);
      lVar1 = *(long *)(param_2 + 0x48);
    }
    puVar2 = (undefined4 *)Framework::AaiExtractTranslate::tImage::rY(unsigned int)(lVar1,param_3);
    *puVar2 = param_1;
  }
  return;
}

// ==== Framework::CAnimationElement::OverwriteAetValueZ(unsigned int, float)
// vaddr 0x1e5ef94 | ghidra 0x1f5ef94 | size 104 | symbol _ZN9Framework17CAnimationElement18OverwriteAetValueZEjf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement18OverwriteAetValueZEjf
               (undefined4 param_1,long param_2,uint param_3)

{
  long lVar1;
  undefined4 *puVar2;
  
  lVar1 = *(long *)(param_2 + 0x48);
  if (lVar1 != 0) {
    if (*(uint *)(lVar1 + 8) <= param_3) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296095c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationElement.cpp"*/,0xfb,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_3);
      lVar1 = *(long *)(param_2 + 0x48);
    }
    puVar2 = (undefined4 *)Framework::AaiExtractTranslate::tImage::rZ(unsigned int)(lVar1,param_3);
    *puVar2 = param_1;
  }
  return;
}

// ==== Framework::CAnimationElement::SetDirectionBlend(int, float, float)
// vaddr 0x1e5f280 | ghidra 0x1f5f280 | size 144 | symbol _ZN9Framework17CAnimationElement17SetDirectionBlendEiff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement17SetDirectionBlendEiff
               (undefined4 param_1,undefined4 param_2,long param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_3 + 0x58);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)operator new(unsigned long, std::nothrow_t const&)(0x14,PTR__ZSt7nothrow_02cb9a80);
    if (puVar1 == (undefined4 *)0x0) {
      *(undefined8 *)(param_3 + 0x58) = 0;
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0296095c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationElement.cpp"*/,0x107,&UNK_02960ab8/*"m_pDirectionBlendArgs is null."*/);
      puVar1 = *(undefined4 **)(param_3 + 0x58);
    }
    else {
      puVar1[3] = 0;
      puVar1[4] = 0;
      *puVar1 = 0xffffffff;
      *(undefined4 **)(param_3 + 0x58) = puVar1;
    }
  }
  *puVar1 = param_4;
  *(undefined4 *)(*(long *)(param_3 + 0x58) + 4) = param_1;
  *(undefined4 *)(*(long *)(param_3 + 0x58) + 8) = param_2;
  return;
}

// ==== Framework::CAnimationElement::DirectionBlendParentElementId() const
// vaddr 0x1e5f310 | ghidra 0x1f5f310 | size 24 | symbol _ZNK9Framework17CAnimationElement29DirectionBlendParentElementIdEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework17CAnimationElement29DirectionBlendParentElementIdEv(long param_1)

{
  if (*(undefined4 **)(param_1 + 0x58) != (undefined4 *)0x0) {
    return **(undefined4 **)(param_1 + 0x58);
  }
  return 0xffffffff;
}

// ==== Framework::CAnimationElement::DirectionBlend_RadianCenter() const
// vaddr 0x1e5f328 | ghidra 0x1f5f328 | size 24 | symbol _ZNK9Framework17CAnimationElement27DirectionBlend_RadianCenterEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework17CAnimationElement27DirectionBlend_RadianCenterEv(long param_1)

{
  if (*(long *)(param_1 + 0x58) != 0) {
    return *(undefined4 *)(*(long *)(param_1 + 0x58) + 4);
  }
  return 0;
}

// ==== Framework::CAnimationElement::DirectionBlend_RadianRange() const
// vaddr 0x1e5f340 | ghidra 0x1f5f340 | size 24 | symbol _ZNK9Framework17CAnimationElement26DirectionBlend_RadianRangeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework17CAnimationElement26DirectionBlend_RadianRangeEv(long param_1)

{
  if (*(long *)(param_1 + 0x58) != 0) {
    return *(undefined4 *)(*(long *)(param_1 + 0x58) + 8);
  }
  return 0;
}

// ==== Framework::CAnimationElement::DirectionBlendRadian() const
// vaddr 0x1e5f358 | ghidra 0x1f5f358 | size 24 | symbol _ZNK9Framework17CAnimationElement20DirectionBlendRadianEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework17CAnimationElement20DirectionBlendRadianEv(long param_1)

{
  if (*(long *)(param_1 + 0x58) != 0) {
    return *(undefined4 *)(*(long *)(param_1 + 0x58) + 0xc);
  }
  return 0;
}

// ==== Framework::CAnimationElement::DirectionBlendRate(float)
// vaddr 0x1e5f370 | ghidra 0x1f5f370 | size 16 | symbol _ZN9Framework17CAnimationElement18DirectionBlendRateEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework17CAnimationElement18DirectionBlendRateEf(undefined4 param_1,long param_2)

{
  if (*(long *)(param_2 + 0x58) != 0) {
    *(undefined4 *)(*(long *)(param_2 + 0x58) + 0x10) = param_1;
  }
  return;
}

// ==== Framework::CAnimationElement::DirectionBlendRate() const
// vaddr 0x1e5f380 | ghidra 0x1f5f380 | size 24 | symbol _ZNK9Framework17CAnimationElement18DirectionBlendRateEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework17CAnimationElement18DirectionBlendRateEv(long param_1)

{
  if (*(long *)(param_1 + 0x58) != 0) {
    return *(undefined4 *)(*(long *)(param_1 + 0x58) + 0x10);
  }
  return 0;
}

// ==== Framework::CAnimationModel::CAnimationModel()
// vaddr 0x1e5f398 | ghidra 0x1f5f398 | size 64 | symbol _ZN9Framework15CAnimationModelC2Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework15CAnimationModelC1Ev(long *param_1)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  
  uVar3 = _UNK_027dbb08;
  uVar2 = _UNK_027dbb00;
  puVar1 = PTR__ZTVN9Framework15CAnimationModelE_02cb7c48 + 0x10;
  *(undefined4 *)(param_1 + 6) = 0;
  *(undefined8 *)((long)param_1 + 0x34) = 0;
  param_1[4] = 0;
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[1] = 0;
  *param_1 = (long)puVar1;
  *(undefined8 *)((long)param_1 + 0x44) = uVar3;
  *(undefined8 *)((long)param_1 + 0x3c) = uVar2;
  *(undefined8 *)((long)param_1 + 0x54) = uVar3;
  *(undefined8 *)((long)param_1 + 0x4c) = uVar2;
  *(undefined8 *)((long)param_1 + 0x5c) = 0x3f800000;
  return;
}

// ==== Framework::CAnimationModel::~CAnimationModel()
// vaddr 0x1e5f3d8 | ghidra 0x1f5f3d8 | size 24 | symbol _ZN9Framework15CAnimationModelD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModelD2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework15CAnimationModelE_02cb7c48;
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  return;
}

// ==== Framework::CAnimationModel::~CAnimationModel()
// vaddr 0x1e5f3f0 | ghidra 0x1f5f3f0 | size 4 | symbol _ZN9Framework15CAnimationModelD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModelD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Framework::CAnimationModel::Initialize()
// vaddr 0x1e5f3f4 | ghidra 0x1f5f3f4 | size 92 | symbol _ZN9Framework15CAnimationModel10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework15CAnimationModel10InitializeEv(long param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (*(long *)(param_1 + 8) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x2c,&UNK_02960c62/*"m_pAssignedAsfHandler isn't null.(%08x)"*/);
  }
  if (*(long *)(param_1 + 0x10) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x2d,&UNK_02960c8a/*"m_pBlend isn't null.(%08x)"*/);
  }
  uVar2 = _UNK_027dbb38;
  uVar1 = _UNK_027dbb30;
  *(undefined8 *)(param_1 + 0x38) = _UNK_027dbb38;
  *(undefined8 *)(param_1 + 0x30) = uVar1;
  *(undefined8 *)(param_1 + 0x48) = uVar2;
  *(undefined8 *)(param_1 + 0x40) = uVar1;
  return;
}

// ==== Framework::CAnimationModel::ResetPosture()
// vaddr 0x1e5f450 | ghidra 0x1f5f450 | size 16 | symbol _ZN9Framework15CAnimationModel12ResetPostureEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework15CAnimationModel12ResetPostureEv(long param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar2 = _UNK_027dbb38;
  uVar1 = _UNK_027dbb30;
  *(undefined8 *)(param_1 + 0x38) = _UNK_027dbb38;
  *(undefined8 *)(param_1 + 0x30) = uVar1;
  *(undefined8 *)(param_1 + 0x48) = uVar2;
  *(undefined8 *)(param_1 + 0x40) = uVar1;
  return;
}

// ==== Framework::CAnimationModel::Release()
// vaddr 0x1e5f460 | ghidra 0x1f5f460 | size 8 | symbol _ZN9Framework15CAnimationModel7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel7ReleaseEv(long param_1)

{
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  return;
}

// ==== Framework::CAnimationModel::AssignResource(Aska::AsfHandler&, Framework::CAnimationBlendContainer&)
// vaddr 0x1e5f468 | ghidra 0x1f5f468 | size 324 | symbol _ZN9Framework15CAnimationModel14AssignResourceERN4Aska10AsfHandlerERNS_24CAnimationBlendContainerE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel14AssignResourceERN4Aska10AsfHandlerERNS_24CAnimationBlendContainerE
               (long param_1,long param_2,undefined8 param_3)

{
  long lVar1;
  undefined8 uVar2;
  
  *(long *)(param_1 + 8) = param_2;
  *(undefined8 *)(param_1 + 0x10) = param_3;
  if (*(int *)(param_2 + 0xb0) < 1) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined8 *)(**(long **)(param_2 + 0xd8) + 0x38);
  }
  *(undefined8 *)(param_1 + 0x18) = uVar2;
  *(undefined8 *)(param_1 + 0x20) = 0;
  if ((*(int *)(param_2 + 0xb0) < 1) || (lVar1 = Aska::AsfHandler::Search(char const*) const(param_2,&UNK_027f7d1b/*"R:POS_ROOT"*/), lVar1 == 0)
     ) {
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  else {
    lVar1 = *(long *)(lVar1 + 0x38);
    *(long *)(param_1 + 0x20) = lVar1;
    if (lVar1 != 0) {
      return;
    }
  }
  if ((*(int *)(*(long *)(param_1 + 8) + 0xb0) < 1) ||
     (lVar1 = Aska::AsfHandler::Search(char const*) const(*(long *)(param_1 + 8),&UNK_02960ca9/*"POS_ROOT"*/), lVar1 == 0)) {
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  else {
    lVar1 = *(long *)(lVar1 + 0x38);
    *(long *)(param_1 + 0x20) = lVar1;
    if (lVar1 != 0) {
      return;
    }
  }
  if ((*(int *)(*(long *)(param_1 + 8) + 0xb0) < 1) ||
     (lVar1 = Aska::AsfHandler::Search(char const*) const(*(long *)(param_1 + 8),&UNK_02960ca5/*"R:M:POS_ROOT"*/), lVar1 == 0)) {
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  else {
    lVar1 = *(long *)(lVar1 + 0x38);
    *(long *)(param_1 + 0x20) = lVar1;
    if (lVar1 != 0) {
      return;
    }
  }
  if ((*(int *)(*(long *)(param_1 + 8) + 0xb0) < 1) ||
     (lVar1 = Aska::AsfHandler::Search(char const*) const(*(long *)(param_1 + 8),&UNK_027f7d28/*"Hips"*/), lVar1 == 0)) {
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  else {
    lVar1 = *(long *)(lVar1 + 0x38);
    *(long *)(param_1 + 0x20) = lVar1;
    if (lVar1 != 0) {
      return;
    }
  }
  if ((0 < *(int *)(*(long *)(param_1 + 8) + 0xb0)) &&
     (lVar1 = Aska::AsfHandler::Search(char const*) const(*(long *)(param_1 + 8),&UNK_02960cad/*"ROOT"*/), lVar1 != 0)) {
    *(undefined8 *)(param_1 + 0x20) = *(undefined8 *)(lVar1 + 0x38);
    return;
  }
  *(undefined8 *)(param_1 + 0x20) = 0;
  return;
}

// ==== Framework::CAnimationModel::rAssignedAsfHandler()
// vaddr 0x1e5f5ac | ghidra 0x1f5f5ac | size 60 | symbol _ZN9Framework15CAnimationModel19rAssignedAsfHandlerEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework15CAnimationModel19rAssignedAsfHandlerEv(long param_1)

{
  if (*(long *)(param_1 + 8) != 0) {
    return *(long *)(param_1 + 8);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x60,&UNK_02960cb2/*"m_pAssignedAsfHandler is null."*/);
  return *(long *)(param_1 + 8);
}

// ==== Framework::CAnimationModel::crAssignedAsfHandler() const
// vaddr 0x1e5f5e8 | ghidra 0x1f5f5e8 | size 60 | symbol _ZNK9Framework15CAnimationModel20crAssignedAsfHandlerEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework15CAnimationModel20crAssignedAsfHandlerEv(long param_1)

{
  if (*(long *)(param_1 + 8) != 0) {
    return *(long *)(param_1 + 8);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x66,&UNK_02960cb2/*"m_pAssignedAsfHandler is null."*/);
  return *(long *)(param_1 + 8);
}

// ==== Framework::CAnimationModel::rObjectRoot()
// vaddr 0x1e5f624 | ghidra 0x1f5f624 | size 60 | symbol _ZN9Framework15CAnimationModel11rObjectRootEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework15CAnimationModel11rObjectRootEv(long param_1)

{
  if (*(long *)(param_1 + 0x18) != 0) {
    return *(long *)(param_1 + 0x18);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x6c,&UNK_02960cd1/*"m_pNode_ObjectRoot is null."*/);
  return *(long *)(param_1 + 0x18);
}

// ==== Framework::CAnimationModel::pObjectRoot()
// vaddr 0x1e5f660 | ghidra 0x1f5f660 | size 60 | symbol _ZN9Framework15CAnimationModel11pObjectRootEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework15CAnimationModel11pObjectRootEv(long param_1)

{
  if (*(long *)(param_1 + 0x18) != 0) {
    return *(long *)(param_1 + 0x18);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x72,&UNK_02960cd1/*"m_pNode_ObjectRoot is null."*/);
  return *(long *)(param_1 + 0x18);
}

// ==== Framework::CAnimationModel::cpObjectRoot() const
// vaddr 0x1e5f69c | ghidra 0x1f5f69c | size 60 | symbol _ZNK9Framework15CAnimationModel12cpObjectRootEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK9Framework15CAnimationModel12cpObjectRootEv(long param_1)

{
  if (*(long *)(param_1 + 0x18) != 0) {
    return *(long *)(param_1 + 0x18);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x78,&UNK_02960cd1/*"m_pNode_ObjectRoot is null."*/);
  return *(long *)(param_1 + 0x18);
}

// ==== Framework::CAnimationModel::SetObjectRoot(Aska::HierarchicalObject*)
// vaddr 0x1e5f6d8 | ghidra 0x1f5f6d8 | size 60 | symbol _ZN9Framework15CAnimationModel13SetObjectRootEPN4Aska18HierarchicalObjectE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel13SetObjectRootEPN4Aska18HierarchicalObjectE
               (long param_1,long param_2)

{
  if (param_2 != 0) {
    *(long *)(param_1 + 0x18) = param_2;
    return;
  }
  if (0 < *(int *)(*(long *)(param_1 + 8) + 0xb0)) {
    *(undefined8 *)(param_1 + 0x18) =
         *(undefined8 *)(**(long **)(*(long *)(param_1 + 8) + 0xd8) + 0x38);
    return;
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  return;
}

// ==== Framework::CAnimationModel::rAnimationBlendContainer()
// vaddr 0x1e5f714 | ghidra 0x1f5f714 | size 60 | symbol _ZN9Framework15CAnimationModel24rAnimationBlendContainerEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework15CAnimationModel24rAnimationBlendContainerEv(long param_1)

{
  if (*(long *)(param_1 + 0x10) != 0) {
    return *(long *)(param_1 + 0x10);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x8b,&UNK_02960ced/*"m_pBlend is null."*/);
  return *(long *)(param_1 + 0x10);
}

// ==== Framework::CAnimationModel::HasTranslateRoot() const
// vaddr 0x1e5f750 | ghidra 0x1f5f750 | size 16 | symbol _ZNK9Framework15CAnimationModel16HasTranslateRootEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework15CAnimationModel16HasTranslateRootEv(long param_1)

{
  return *(long *)(param_1 + 0x20) != 0;
}

// ==== Framework::CAnimationModel::OffsetAtTranslateRoot() const
// vaddr 0x1e5f760 | ghidra 0x1f5f760 | size 72 | symbol _ZNK9Framework15CAnimationModel21OffsetAtTranslateRootEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework15CAnimationModel21OffsetAtTranslateRootEv(undefined8 *param_1,long param_2)

{
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = *(long *)(param_2 + 0x20);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x97,&UNK_02960cff/*"m_pNode_TranslateRoot is null."*/);
    lVar1 = *(long *)(param_2 + 0x20);
  }
  uVar2 = *(undefined8 *)(lVar1 + 0x80);
  param_1[1] = *(undefined8 *)(lVar1 + 0x88);
  *param_1 = uVar2;
  return;
}

// ==== Framework::CAnimationModel::OffsetAtTranslateRoot(Framework::CVector const&)
// vaddr 0x1e5f7a8 | ghidra 0x1f5f7a8 | size 76 | symbol _ZN9Framework15CAnimationModel21OffsetAtTranslateRootERKNS_7CVectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel21OffsetAtTranslateRootERKNS_7CVectorE
               (long param_1,undefined8 param_2)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x20);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x9f,&UNK_02960cff/*"m_pNode_TranslateRoot is null."*/);
    plVar1 = *(long **)(param_1 + 0x20);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5f7f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0xd0))(plVar1,param_2);
  return;
}

// ==== Framework::CAnimationModel::StartAnimation(int, float, bool)
// vaddr 0x1e5f7f4 | ghidra 0x1f5f7f4 | size 132 | symbol _ZN9Framework15CAnimationModel14StartAnimationEifb | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool _ZN9Framework15CAnimationModel14StartAnimationEifb
               (undefined8 param_1,long param_2,undefined4 param_3,uint param_4)

{
  bool bVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  ulong uVar4;
  
  puVar3 = *(undefined8 **)(param_2 + 0x10);
  if (puVar3 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0xab,&UNK_02960ced/*"m_pBlend is null."*/);
    puVar3 = *(undefined8 **)(param_2 + 0x10);
  }
  uVar4 = (**(code **)*puVar3)(param_1,puVar3,param_3,param_4 & 1);
  uVar2 = _UNK_027dbb30;
  bVar1 = (uVar4 & 1) != 0;
  if (bVar1) {
    *(undefined8 *)(param_2 + 0x38) = _UNK_027dbb38;
    *(undefined8 *)(param_2 + 0x30) = uVar2;
  }
  return bVar1;
}

// ==== Framework::CAnimationModel::PresentAnimation() const
// vaddr 0x1e5f878 | ghidra 0x1f5f878 | size 56 | symbol _ZNK9Framework15CAnimationModel16PresentAnimationEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework15CAnimationModel16PresentAnimationEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x10);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0xb5,&UNK_02960ced/*"m_pBlend is null."*/);
    lVar1 = *(long *)(param_1 + 0x10);
  }
  return *(undefined4 *)(lVar1 + 0x90);
}

// ==== Framework::CAnimationModel::PresentAnimationChangeTime() const
// vaddr 0x1e5f8b0 | ghidra 0x1f5f8b0 | size 56 | symbol _ZNK9Framework15CAnimationModel26PresentAnimationChangeTimeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework15CAnimationModel26PresentAnimationChangeTimeEv(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x10);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0xbb,&UNK_02960ced/*"m_pBlend is null."*/);
    lVar1 = *(long *)(param_1 + 0x10);
  }
  return *(undefined4 *)(lVar1 + 0x94);
}

// ==== Framework::CAnimationModel::StartFrame(float)
// vaddr 0x1e5f8e8 | ghidra 0x1f5f8e8 | size 76 | symbol _ZN9Framework15CAnimationModel10StartFrameEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel10StartFrameEf(undefined8 param_1,long param_2)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_2 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0xc4,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_2 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5f930. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 8))(param_1);
  return;
}

// ==== Framework::CAnimationModel::EndFrame(float)
// vaddr 0x1e5f934 | ghidra 0x1f5f934 | size 76 | symbol _ZN9Framework15CAnimationModel8EndFrameEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel8EndFrameEf(undefined8 param_1,long param_2)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_2 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0xca,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_2 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5f97c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x10))(param_1);
  return;
}

// ==== Framework::CAnimationModel::PresentFrame(float)
// vaddr 0x1e5f980 | ghidra 0x1f5f980 | size 76 | symbol _ZN9Framework15CAnimationModel12PresentFrameEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel12PresentFrameEf(undefined8 param_1,long param_2)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_2 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0xd0,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_2 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5f9c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x18))(param_1);
  return;
}

// ==== Framework::CAnimationModel::TerminateProcess(unsigned int)
// vaddr 0x1e5f9cc | ghidra 0x1f5f9cc | size 76 | symbol _ZN9Framework15CAnimationModel16TerminateProcessEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel16TerminateProcessEj(long param_1,undefined4 param_2)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0xd6,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fa14. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x20))(plVar1,param_2);
  return;
}

// ==== Framework::CAnimationModel::IsEnableLoop() const
// vaddr 0x1e5fa18 | ghidra 0x1f5fa18 | size 60 | symbol _ZNK9Framework15CAnimationModel12IsEnableLoopEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework15CAnimationModel12IsEnableLoopEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0xdc,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fa50. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x28))();
  return;
}

// ==== Framework::CAnimationModel::IsEnableFrameStopAtEnd() const
// vaddr 0x1e5fa54 | ghidra 0x1f5fa54 | size 60 | symbol _ZNK9Framework15CAnimationModel22IsEnableFrameStopAtEndEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework15CAnimationModel22IsEnableFrameStopAtEndEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0xe2,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fa8c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x30))();
  return;
}

// ==== Framework::CAnimationModel::IsEnableFreeTerm() const
// vaddr 0x1e5fa90 | ghidra 0x1f5fa90 | size 60 | symbol _ZNK9Framework15CAnimationModel16IsEnableFreeTermEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework15CAnimationModel16IsEnableFreeTermEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0xe8,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fac8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x38))();
  return;
}

// ==== Framework::CAnimationModel::IsLooped() const
// vaddr 0x1e5facc | ghidra 0x1f5facc | size 60 | symbol _ZNK9Framework15CAnimationModel8IsLoopedEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework15CAnimationModel8IsLoopedEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0xee,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fb04. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x40))();
  return;
}

// ==== Framework::CAnimationModel::IsLoopedAtOnce() const
// vaddr 0x1e5fb08 | ghidra 0x1f5fb08 | size 60 | symbol _ZNK9Framework15CAnimationModel14IsLoopedAtOnceEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework15CAnimationModel14IsLoopedAtOnceEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0xf4,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fb40. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x48))();
  return;
}

// ==== Framework::CAnimationModel::NumLoop() const
// vaddr 0x1e5fb44 | ghidra 0x1f5fb44 | size 60 | symbol _ZNK9Framework15CAnimationModel7NumLoopEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework15CAnimationModel7NumLoopEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0xfa,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fb7c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x50))();
  return;
}

// ==== Framework::CAnimationModel::ClearLoopedFlag()
// vaddr 0x1e5fb80 | ghidra 0x1f5fb80 | size 60 | symbol _ZN9Framework15CAnimationModel15ClearLoopedFlagEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel15ClearLoopedFlagEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x100,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fbb8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x58))();
  return;
}

// ==== Framework::CAnimationModel::AnimationSpeed(float)
// vaddr 0x1e5fbbc | ghidra 0x1f5fbbc | size 76 | symbol _ZN9Framework15CAnimationModel14AnimationSpeedEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel14AnimationSpeedEf(undefined8 param_1,long param_2)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_2 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x109,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_2 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fc04. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x60))(param_1);
  return;
}

// ==== Framework::CAnimationModel::AnimationSpeedByTransitionValue(unsigned int, float, float)
// vaddr 0x1e5fc08 | ghidra 0x1f5fc08 | size 100 | symbol _ZN9Framework15CAnimationModel31AnimationSpeedByTransitionValueEjff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel31AnimationSpeedByTransitionValueEjff
               (undefined8 param_1,undefined8 param_2,long param_3,undefined4 param_4)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_3 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x10f,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_3 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fc68. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x68))(param_1,param_2,plVar1,param_4);
  return;
}

// ==== Framework::CAnimationModel::AnimationSpeed() const
// vaddr 0x1e5fc6c | ghidra 0x1f5fc6c | size 60 | symbol _ZNK9Framework15CAnimationModel14AnimationSpeedEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework15CAnimationModel14AnimationSpeedEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x115,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fca4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x70))();
  return;
}

// ==== Framework::CAnimationModel::StartFrame() const
// vaddr 0x1e5fca8 | ghidra 0x1f5fca8 | size 60 | symbol _ZNK9Framework15CAnimationModel10StartFrameEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework15CAnimationModel10StartFrameEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x11b,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fce0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x78))();
  return;
}

// ==== Framework::CAnimationModel::PresentFrame() const
// vaddr 0x1e5fce4 | ghidra 0x1f5fce4 | size 60 | symbol _ZNK9Framework15CAnimationModel12PresentFrameEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework15CAnimationModel12PresentFrameEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x121,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fd1c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x80))();
  return;
}

// ==== Framework::CAnimationModel::EndFrame() const
// vaddr 0x1e5fd20 | ghidra 0x1f5fd20 | size 60 | symbol _ZNK9Framework15CAnimationModel8EndFrameEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework15CAnimationModel8EndFrameEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x127,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fd58. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x88))();
  return;
}

// ==== Framework::CAnimationModel::PresentBlendRate() const
// vaddr 0x1e5fd5c | ghidra 0x1f5fd5c | size 60 | symbol _ZNK9Framework15CAnimationModel16PresentBlendRateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework15CAnimationModel16PresentBlendRateEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x12d,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fd94. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x90))();
  return;
}

// ==== Framework::CAnimationModel::Flag() const
// vaddr 0x1e5fd98 | ghidra 0x1f5fd98 | size 60 | symbol _ZNK9Framework15CAnimationModel4FlagEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework15CAnimationModel4FlagEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x136,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fdd0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x98))();
  return;
}

// ==== Framework::CAnimationModel::ClearAllFlag()
// vaddr 0x1e5fdd4 | ghidra 0x1f5fdd4 | size 60 | symbol _ZN9Framework15CAnimationModel12ClearAllFlagEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel12ClearAllFlagEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x13c,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fe0c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0xa0))();
  return;
}

// ==== Framework::CAnimationModel::OrFlag(unsigned int)
// vaddr 0x1e5fe10 | ghidra 0x1f5fe10 | size 76 | symbol _ZN9Framework15CAnimationModel6OrFlagEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel6OrFlagEj(long param_1,undefined4 param_2)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x142,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fe58. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0xa8))(plVar1,param_2);
  return;
}

// ==== Framework::CAnimationModel::AndFlag(unsigned int)
// vaddr 0x1e5fe5c | ghidra 0x1f5fe5c | size 76 | symbol _ZN9Framework15CAnimationModel7AndFlagEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel7AndFlagEj(long param_1,undefined4 param_2)

{
  long *plVar1;
  
  plVar1 = *(long **)(param_1 + 0x10);
  if (plVar1 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x148,&UNK_02960ced/*"m_pBlend is null."*/);
    plVar1 = *(long **)(param_1 + 0x10);
  }
                    /* WARNING: Could not recover jumptable at 0x01f5fea4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0xb0))(plVar1,param_2);
  return;
}

// ==== Framework::CAnimationModel::Progress(float)
// vaddr 0x1e5fea8 | ghidra 0x1f5fea8 | size 364 | symbol _ZN9Framework15CAnimationModel8ProgressEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework15CAnimationModel8ProgressEf(undefined8 *param_1,undefined8 param_2,long *param_3)

{
  uint uVar1;
  undefined8 uVar2;
  int iVar3;
  long lVar4;
  ulong uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  
  lVar4 = param_3[1];
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x60,&UNK_02960cb2/*"m_pAssignedAsfHandler is null."*/);
    lVar4 = param_3[1];
  }
  Framework::gSetLocalDTRateToArticulatedDynamicsManagerInAsf(Aska::AsfHandler&, float)(param_2,lVar4);
  uVar2 = _UNK_027dbb30;
  param_1[1] = _UNK_027dbb38;
  *param_1 = uVar2;
  if (param_3[1] == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x15a,&UNK_02960cb2/*"m_pAssignedAsfHandler is null."*/);
    lVar4 = param_3[2];
  }
  else {
    lVar4 = param_3[2];
  }
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x15b,&UNK_02960ced/*"m_pBlend is null."*/);
    iVar3 = Framework::CAnimationBlendContainer::NumElements() const(param_3[2]);
  }
  else {
    iVar3 = Framework::CAnimationBlendContainer::NumElements() const();
  }
  if (iVar3 != 0) {
    uVar5 = (**(code **)(*param_3 + 0x98))(param_3);
    *(bool *)((long)param_3 + 100) = (uVar5 & 0x700) != 0;
    uVar9 = (**(code **)(*param_3 + 0x80))(param_3);
    lVar4 = param_3[4];
    *(undefined4 *)(param_3 + 0xc) = uVar9;
    if (lVar4 == 0) {
      uVar9 = 0;
      uVar6 = 0;
      uVar7 = 0;
      uVar8 = 0x3f800000;
    }
    else {
      uVar9 = *(undefined4 *)(lVar4 + 0x80);
      uVar6 = *(undefined4 *)(lVar4 + 0x84);
      uVar7 = *(undefined4 *)(lVar4 + 0x88);
      uVar8 = *(undefined4 *)(lVar4 + 0x8c);
    }
    *(undefined4 *)(param_3 + 10) = uVar9;
    *(undefined4 *)((long)param_3 + 0x54) = uVar6;
    *(undefined4 *)(param_3 + 0xb) = uVar7;
    *(undefined4 *)((long)param_3 + 0x5c) = uVar8;
    Framework::CAnimationBlendContainer::ProgressBlend(float)(param_2,param_3[2]);
    Framework::CAnimationBlendContainer::ProgressFrame(float, Framework::CAnimationBlendContainer::tProgressFrame_Arguments const*)(param_2,param_3[2],0);
    if (*(long *)(param_3[2] + 0xa8) != 0) {
      uVar1 = *(uint *)(*(long *)(param_3[2] + 0xa8) + 0x10);
      if ((uVar1 & 1) == 0) {
        *(undefined4 *)(param_3 + 10) = 0;
      }
      if ((uVar1 >> 1 & 1) == 0) {
        *(undefined4 *)((long)param_3 + 0x54) = 0;
      }
      if ((uVar1 >> 2 & 1) == 0) {
        *(undefined4 *)(param_3 + 0xb) = 0;
      }
    }
  }
  return;
}

// ==== Framework::CAnimationModel::GetVelocityByAnimation(float)
// vaddr 0x1e60014 | ghidra 0x1f60014 | size 464 | symbol _ZN9Framework15CAnimationModel22GetVelocityByAnimationEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework15CAnimationModel22GetVelocityByAnimationEf(float *param_1,long *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  uint uVar6;
  long lVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  undefined4 uStack_54;
  
  uVar5 = _UNK_027dbb30;
  *(undefined8 *)(param_1 + 2) = _UNK_027dbb38;
  *(undefined8 *)param_1 = uVar5;
  lVar7 = param_2[4];
  if (lVar7 != 0) {
    fVar1 = *(float *)(lVar7 + 0x80);
    fVar3 = *(float *)(lVar7 + 0x84);
    fVar2 = *(float *)(lVar7 + 0x88);
    uVar4 = *(undefined4 *)(lVar7 + 0x8c);
    uVar6 = Framework::CAnimationBlendContainer::OrAllFlag() const(param_2[2]);
    if ((uVar6 & 0x70070) == 0) {
      fVar12 = (*(float *)(param_2 + 8) - fVar1) + 0.0;
      fVar11 = (*(float *)((long)param_2 + 0x44) - fVar3) + 0.0;
      fVar10 = (*(float *)(param_2 + 9) - fVar2) + 0.0;
      *param_1 = fVar12;
      param_1[1] = fVar11;
      param_1[2] = fVar10;
      *(float *)(param_2 + 8) = fVar1;
      *(float *)((long)param_2 + 0x44) = fVar3;
      *(float *)(param_2 + 9) = fVar2;
      *(undefined4 *)((long)param_2 + 0x4c) = uVar4;
    }
    else {
      fStack_60 = fVar1;
      if ((uVar6 >> 4 & 1) != 0) {
        fStack_60 = *(float *)(param_2 + 10);
      }
      fStack_5c = fVar3;
      if ((uVar6 >> 5 & 1) != 0) {
        fStack_5c = *(float *)((long)param_2 + 0x54);
      }
      fStack_58 = fVar2;
      if ((uVar6 >> 6 & 1) != 0) {
        fStack_58 = *(float *)(param_2 + 0xb);
      }
      if ((uVar6 >> 0x10 & 1) != 0) {
        fStack_60 = 0.0;
      }
      if ((uVar6 >> 0x11 & 1) != 0) {
        fStack_5c = 0.0;
      }
      if ((uVar6 >> 0x12 & 1) != 0) {
        fStack_58 = 0.0;
      }
      uStack_54 = uVar4;
      (**(code **)(*(long *)param_2[4] + 0xd0))((long *)param_2[4],&fStack_60);
      fVar10 = 0.0;
      fVar11 = 0.0;
      fVar12 = 0.0;
      param_2[9] = CONCAT44(uStack_54,fStack_58);
      param_2[8] = CONCAT44(fStack_5c,fStack_60);
    }
    uVar6 = (**(code **)(*param_2 + 0x98))(param_2);
    if (*(char *)((long)param_2 + 100) != '\0') {
      fVar8 = *(float *)(param_2 + 7);
      fVar9 = *(float *)((long)param_2 + 0x34);
      if ((uVar6 >> 8 & 1) != 0) {
        *param_1 = fVar12 + (fVar1 - *(float *)(param_2 + 6));
      }
      if ((uVar6 >> 9 & 1) != 0) {
        param_1[1] = (fVar3 - fVar9) + fVar11;
      }
      if ((uVar6 >> 10 & 1) != 0) {
        param_1[2] = (fVar2 - fVar8) + fVar10;
      }
    }
    *(float *)(param_2 + 6) = fVar1;
    *(float *)((long)param_2 + 0x34) = fVar3;
    *(float *)(param_2 + 7) = fVar2;
    *(undefined4 *)((long)param_2 + 0x3c) = uVar4;
  }
  return;
}

// ==== Framework::CAnimationModel::GetVelocityByAet(float)
// vaddr 0x1e601e4 | ghidra 0x1f601e4 | size 1588 | symbol _ZN9Framework15CAnimationModel16GetVelocityByAetEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework15CAnimationModel16GetVelocityByAetEf(float *param_1,long *param_2)

{
  uint uVar1;
  undefined8 uVar2;
  uint uVar3;
  long lVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  long lVar8;
  uint uVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  
  uVar2 = _UNK_027dbb30;
  *(undefined8 *)(param_1 + 2) = _UNK_027dbb38;
  *(undefined8 *)param_1 = uVar2;
  uVar3 = (**(code **)(*param_2 + 0x98))();
  lVar4 = Framework::CAnimationBlendContainer::crElement(int) const(param_2[2],*(undefined4 *)(param_2[2] + 0x90));
  if (((uVar3 & 0x7000) != 0) && (lVar8 = *(long *)(lVar4 + 0x48), lVar8 != 0)) {
    fVar10 = (float)(**(code **)(*param_2 + 0x80))(param_2);
    fVar22 = *(float *)(param_2 + 0xc);
    if (fVar22 != fVar10) {
      fVar13 = 0.0;
      fVar11 = 0.0;
      if ((uVar3 >> 0xc & 1) != 0) {
        uVar7 = *(uint *)(lVar8 + 8);
        uVar5 = (uint)fVar22;
        uVar1 = uVar7 - 1;
        uVar9 = uVar5;
        if (uVar7 <= uVar5) {
          uVar9 = uVar1;
        }
        fVar22 = fVar22 - (float)uVar9;
        if (uVar5 + 1 < uVar7) {
          uVar1 = uVar5 + 1;
        }
        if (1.0 < fVar22) {
          fVar22 = 1.0;
        }
        fVar11 = (float)Framework::AaiExtractTranslate::tImage::X(unsigned int) const(lVar8);
        fVar12 = (float)Framework::AaiExtractTranslate::tImage::X(unsigned int) const(lVar8,uVar1);
        fVar11 = fVar11 + (fVar12 - fVar11) * fVar22;
      }
      if ((uVar3 >> 0xd & 1) != 0) {
        uVar7 = *(uint *)(lVar8 + 8);
        uVar5 = (uint)*(float *)(param_2 + 0xc);
        uVar1 = uVar7 - 1;
        uVar9 = uVar5;
        if (uVar7 <= uVar5) {
          uVar9 = uVar1;
        }
        fVar22 = *(float *)(param_2 + 0xc) - (float)uVar9;
        if (fVar22 <= 0.0) {
          fVar22 = 0.0;
        }
        if (uVar5 + 1 < uVar7) {
          uVar1 = uVar5 + 1;
        }
        if (1.0 < fVar22) {
          fVar22 = 1.0;
        }
        fVar13 = (float)Framework::AaiExtractTranslate::tImage::Y(unsigned int) const(lVar8);
        fVar12 = (float)Framework::AaiExtractTranslate::tImage::Y(unsigned int) const(lVar8,uVar1);
        fVar13 = fVar13 + (fVar12 - fVar13) * fVar22;
      }
      fVar22 = 0.0;
      fVar12 = 0.0;
      if ((uVar3 >> 0xe & 1) != 0) {
        uVar7 = *(uint *)(lVar8 + 8);
        uVar5 = (uint)*(float *)(param_2 + 0xc);
        uVar1 = uVar7 - 1;
        uVar9 = uVar5;
        if (uVar7 <= uVar5) {
          uVar9 = uVar1;
        }
        fVar12 = *(float *)(param_2 + 0xc) - (float)uVar9;
        if (fVar12 <= 0.0) {
          fVar12 = 0.0;
        }
        if (uVar5 + 1 < uVar7) {
          uVar1 = uVar5 + 1;
        }
        if (1.0 < fVar12) {
          fVar12 = 1.0;
        }
        fVar14 = (float)Framework::AaiExtractTranslate::tImage::Z(unsigned int) const(lVar8);
        fVar15 = (float)Framework::AaiExtractTranslate::tImage::Z(unsigned int) const(lVar8,uVar1);
        fVar12 = -(fVar14 + (fVar15 - fVar14) * fVar12);
      }
      if ((uVar3 >> 0xc & 1) != 0) {
        uVar7 = *(uint *)(lVar8 + 8);
        uVar5 = (uint)fVar10;
        uVar1 = uVar7 - 1;
        uVar9 = uVar5;
        if (uVar7 <= uVar5) {
          uVar9 = uVar1;
        }
        fVar14 = fVar10 - (float)uVar9;
        if (uVar5 + 1 < uVar7) {
          uVar1 = uVar5 + 1;
        }
        if (1.0 < fVar14) {
          fVar14 = 1.0;
        }
        fVar22 = (float)Framework::AaiExtractTranslate::tImage::X(unsigned int) const(lVar8);
        fVar15 = (float)Framework::AaiExtractTranslate::tImage::X(unsigned int) const(lVar8,uVar1);
        fVar22 = fVar22 + (fVar15 - fVar22) * fVar14;
      }
      fVar14 = 0.0;
      if ((uVar3 >> 0xd & 1) != 0) {
        uVar7 = *(uint *)(lVar8 + 8);
        uVar5 = (uint)fVar10;
        uVar1 = uVar7 - 1;
        uVar9 = uVar5;
        if (uVar7 <= uVar5) {
          uVar9 = uVar1;
        }
        fVar15 = fVar10 - (float)uVar9;
        if (uVar5 + 1 < uVar7) {
          uVar1 = uVar5 + 1;
        }
        if (1.0 < fVar15) {
          fVar15 = 1.0;
        }
        fVar14 = (float)Framework::AaiExtractTranslate::tImage::Y(unsigned int) const(lVar8);
        fVar16 = (float)Framework::AaiExtractTranslate::tImage::Y(unsigned int) const(lVar8,uVar1);
        fVar14 = fVar14 + (fVar16 - fVar14) * fVar15;
      }
      fVar15 = 0.0;
      if ((uVar3 >> 0xe & 1) != 0) {
        uVar7 = *(uint *)(lVar8 + 8);
        uVar5 = (uint)fVar10;
        uVar1 = uVar7 - 1;
        uVar9 = uVar5;
        if (uVar7 <= uVar5) {
          uVar9 = uVar1;
        }
        fVar15 = fVar10 - (float)uVar9;
        if (uVar5 + 1 < uVar7) {
          uVar1 = uVar5 + 1;
        }
        if (1.0 < fVar15) {
          fVar15 = 1.0;
        }
        fVar16 = (float)Framework::AaiExtractTranslate::tImage::Z(unsigned int) const(lVar8);
        fVar17 = (float)Framework::AaiExtractTranslate::tImage::Z(unsigned int) const(lVar8,uVar1);
        fVar15 = -(fVar16 + (fVar17 - fVar16) * fVar15);
      }
      if (*(float *)(param_2 + 0xc) <= fVar10) {
        *param_1 = fVar22 - fVar11;
        param_1[1] = fVar14 - fVar13;
        param_1[2] = fVar15 - fVar12;
        param_1[3] = 1.0;
      }
      else {
        fVar16 = 0.0;
        uVar9 = (uint)*(float *)(lVar4 + 0x18);
        fVar10 = 0.0;
        if ((uVar3 >> 0xc & 1) != 0) {
          uVar5 = *(uint *)(lVar8 + 8);
          uVar6 = (uint)(float)uVar9;
          uVar7 = uVar5 - 1;
          uVar1 = uVar6;
          if (uVar5 <= uVar6) {
            uVar1 = uVar7;
          }
          fVar17 = (float)uVar9 - (float)uVar1;
          if (fVar17 <= 0.0) {
            fVar17 = 0.0;
          }
          if (uVar6 + 1 < uVar5) {
            uVar7 = uVar6 + 1;
          }
          if (1.0 < fVar17) {
            fVar17 = 1.0;
          }
          fVar10 = (float)Framework::AaiExtractTranslate::tImage::X(unsigned int) const(lVar8);
          fVar18 = (float)Framework::AaiExtractTranslate::tImage::X(unsigned int) const(lVar8,uVar7);
          fVar10 = fVar10 + (fVar18 - fVar10) * fVar17;
        }
        if ((uVar3 >> 0xd & 1) != 0) {
          uVar5 = *(uint *)(lVar8 + 8);
          uVar6 = (uint)(float)uVar9;
          uVar7 = uVar5 - 1;
          uVar1 = uVar6;
          if (uVar5 <= uVar6) {
            uVar1 = uVar7;
          }
          fVar17 = (float)uVar9 - (float)uVar1;
          if (fVar17 <= 0.0) {
            fVar17 = 0.0;
          }
          if (uVar6 + 1 < uVar5) {
            uVar7 = uVar6 + 1;
          }
          if (1.0 < fVar17) {
            fVar17 = 1.0;
          }
          fVar16 = (float)Framework::AaiExtractTranslate::tImage::Y(unsigned int) const(lVar8);
          fVar18 = (float)Framework::AaiExtractTranslate::tImage::Y(unsigned int) const(lVar8,uVar7);
          fVar16 = fVar16 + (fVar18 - fVar16) * fVar17;
        }
        fVar17 = 0.0;
        fVar18 = 0.0;
        if ((uVar3 >> 0xe & 1) != 0) {
          uVar5 = *(uint *)(lVar8 + 8);
          uVar6 = (uint)(float)uVar9;
          uVar7 = uVar5 - 1;
          uVar1 = uVar6;
          if (uVar5 <= uVar6) {
            uVar1 = uVar7;
          }
          fVar18 = (float)uVar9 - (float)uVar1;
          if (fVar18 <= 0.0) {
            fVar18 = 0.0;
          }
          if (uVar6 + 1 < uVar5) {
            uVar7 = uVar6 + 1;
          }
          if (1.0 < fVar18) {
            fVar18 = 1.0;
          }
          fVar19 = (float)Framework::AaiExtractTranslate::tImage::Z(unsigned int) const(lVar8);
          fVar20 = (float)Framework::AaiExtractTranslate::tImage::Z(unsigned int) const(lVar8,uVar7);
          fVar18 = -(fVar19 + (fVar20 - fVar19) * fVar18);
        }
        if ((uVar3 >> 7 & 1) == 0) {
          fVar17 = *(float *)(lVar4 + 0x14);
        }
        fVar20 = 0.0;
        fVar19 = 0.0;
        if ((uVar3 >> 0xc & 1) != 0) {
          uVar7 = *(uint *)(lVar8 + 8);
          uVar5 = (uint)fVar17;
          uVar1 = uVar7 - 1;
          uVar9 = uVar5;
          if (uVar7 <= uVar5) {
            uVar9 = uVar1;
          }
          fVar23 = fVar17 - (float)uVar9;
          if (uVar5 + 1 < uVar7) {
            uVar1 = uVar5 + 1;
          }
          if (1.0 < fVar23) {
            fVar23 = 1.0;
          }
          fVar19 = (float)Framework::AaiExtractTranslate::tImage::X(unsigned int) const(lVar8);
          fVar21 = (float)Framework::AaiExtractTranslate::tImage::X(unsigned int) const(lVar8,uVar1);
          fVar19 = fVar19 + (fVar21 - fVar19) * fVar23;
        }
        if ((uVar3 >> 0xd & 1) != 0) {
          uVar7 = *(uint *)(lVar8 + 8);
          uVar5 = (uint)fVar17;
          uVar1 = uVar7 - 1;
          uVar9 = uVar5;
          if (uVar7 <= uVar5) {
            uVar9 = uVar1;
          }
          fVar23 = fVar17 - (float)uVar9;
          if (uVar5 + 1 < uVar7) {
            uVar1 = uVar5 + 1;
          }
          if (1.0 < fVar23) {
            fVar23 = 1.0;
          }
          fVar20 = (float)Framework::AaiExtractTranslate::tImage::Y(unsigned int) const(lVar8);
          fVar21 = (float)Framework::AaiExtractTranslate::tImage::Y(unsigned int) const(lVar8,uVar1);
          fVar20 = fVar20 + (fVar21 - fVar20) * fVar23;
        }
        fVar23 = 0.0;
        if ((uVar3 >> 0xe & 1) != 0) {
          uVar1 = *(uint *)(lVar8 + 8);
          uVar7 = (uint)fVar17;
          uVar9 = uVar1 - 1;
          uVar3 = uVar7;
          if (uVar1 <= uVar7) {
            uVar3 = uVar9;
          }
          fVar17 = fVar17 - (float)uVar3;
          if (uVar7 + 1 < uVar1) {
            uVar9 = uVar7 + 1;
          }
          if (1.0 < fVar17) {
            fVar17 = 1.0;
          }
          fVar23 = (float)Framework::AaiExtractTranslate::tImage::Z(unsigned int) const(lVar8);
          fVar21 = (float)Framework::AaiExtractTranslate::tImage::Z(unsigned int) const(lVar8,uVar9);
          fVar23 = -(fVar23 + (fVar21 - fVar23) * fVar17);
        }
        *param_1 = (fVar22 - fVar19) + (fVar10 - fVar11) + 0.0;
        param_1[1] = (fVar14 - fVar20) + (fVar16 - fVar13) + 0.0;
        param_1[2] = (fVar15 - fVar23) + (fVar18 - fVar12) + 0.0;
      }
    }
  }
  return;
}

// ==== Framework::CAnimationModel::GetRotateByAet(float)
// vaddr 0x1e60818 | ghidra 0x1f60818 | size 1780 | symbol _ZN9Framework15CAnimationModel14GetRotateByAetEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework15CAnimationModel14GetRotateByAetEf(float *param_1,long *param_2)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  long lVar7;
  uint uVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fStack_34;
  
  param_1[0] = 0.0;
  param_1[1] = 0.0;
  param_1[2] = 0.0;
  param_1[3] = 0.0;
  uVar2 = (**(code **)(*param_2 + 0x98))();
  lVar3 = Framework::CAnimationBlendContainer::crElement(int) const(param_2[2],*(undefined4 *)(param_2[2] + 0x90));
  if (((uVar2 & 0x7000000) != 0) && (lVar7 = *(long *)(lVar3 + 0x48), lVar7 != 0)) {
    fVar9 = (float)(**(code **)(*param_2 + 0x80))(param_2);
    fVar20 = *(float *)(param_2 + 0xc);
    if (fVar20 != fVar9) {
      fVar12 = 0.0;
      fVar10 = 0.0;
      if ((uVar2 >> 0x18 & 1) != 0) {
        uVar6 = *(uint *)(lVar7 + 8);
        uVar4 = (uint)fVar20;
        uVar1 = uVar6 - 1;
        uVar8 = uVar4;
        if (uVar6 <= uVar4) {
          uVar8 = uVar1;
        }
        fVar20 = fVar20 - (float)uVar8;
        if (uVar4 + 1 < uVar6) {
          uVar1 = uVar4 + 1;
        }
        if (1.0 < fVar20) {
          fVar20 = 1.0;
        }
        fVar10 = (float)Framework::AaiExtractTranslate::tImage::RotateX(unsigned int) const(lVar7);
        fVar11 = (float)Framework::AaiExtractTranslate::tImage::RotateX(unsigned int) const(lVar7,uVar1);
        fVar10 = fVar10 + (fVar11 - fVar10) * fVar20;
      }
      if ((uVar2 >> 0x19 & 1) != 0) {
        uVar6 = *(uint *)(lVar7 + 8);
        uVar4 = (uint)*(float *)(param_2 + 0xc);
        uVar1 = uVar6 - 1;
        uVar8 = uVar4;
        if (uVar6 <= uVar4) {
          uVar8 = uVar1;
        }
        fVar20 = *(float *)(param_2 + 0xc) - (float)uVar8;
        if (fVar20 <= 0.0) {
          fVar20 = 0.0;
        }
        if (uVar4 + 1 < uVar6) {
          uVar1 = uVar4 + 1;
        }
        if (1.0 < fVar20) {
          fVar20 = 1.0;
        }
        fVar12 = (float)Framework::AaiExtractTranslate::tImage::RotateY(unsigned int) const(lVar7);
        fVar11 = (float)Framework::AaiExtractTranslate::tImage::RotateY(unsigned int) const(lVar7,uVar1);
        fVar12 = fVar12 + (fVar11 - fVar12) * fVar20;
      }
      fVar20 = 0.0;
      fVar11 = 0.0;
      if ((uVar2 >> 0x1a & 1) != 0) {
        uVar6 = *(uint *)(lVar7 + 8);
        uVar4 = (uint)*(float *)(param_2 + 0xc);
        uVar1 = uVar6 - 1;
        uVar8 = uVar4;
        if (uVar6 <= uVar4) {
          uVar8 = uVar1;
        }
        fVar11 = *(float *)(param_2 + 0xc) - (float)uVar8;
        if (fVar11 <= 0.0) {
          fVar11 = 0.0;
        }
        if (uVar4 + 1 < uVar6) {
          uVar1 = uVar4 + 1;
        }
        if (1.0 < fVar11) {
          fVar11 = 1.0;
        }
        fVar13 = (float)Framework::AaiExtractTranslate::tImage::RotateZ(unsigned int) const(lVar7);
        fVar14 = (float)Framework::AaiExtractTranslate::tImage::RotateZ(unsigned int) const(lVar7,uVar1);
        fVar11 = -(fVar13 + (fVar14 - fVar13) * fVar11);
      }
      if ((uVar2 >> 0x18 & 1) != 0) {
        uVar6 = *(uint *)(lVar7 + 8);
        uVar4 = (uint)fVar9;
        uVar1 = uVar6 - 1;
        uVar8 = uVar4;
        if (uVar6 <= uVar4) {
          uVar8 = uVar1;
        }
        fVar13 = fVar9 - (float)uVar8;
        if (uVar4 + 1 < uVar6) {
          uVar1 = uVar4 + 1;
        }
        if (1.0 < fVar13) {
          fVar13 = 1.0;
        }
        fVar20 = (float)Framework::AaiExtractTranslate::tImage::RotateX(unsigned int) const(lVar7);
        fVar14 = (float)Framework::AaiExtractTranslate::tImage::RotateX(unsigned int) const(lVar7,uVar1);
        fVar20 = fVar20 + (fVar14 - fVar20) * fVar13;
      }
      fVar13 = 0.0;
      if ((uVar2 >> 0x19 & 1) != 0) {
        uVar6 = *(uint *)(lVar7 + 8);
        uVar4 = (uint)fVar9;
        uVar1 = uVar6 - 1;
        uVar8 = uVar4;
        if (uVar6 <= uVar4) {
          uVar8 = uVar1;
        }
        fVar14 = fVar9 - (float)uVar8;
        if (uVar4 + 1 < uVar6) {
          uVar1 = uVar4 + 1;
        }
        if (1.0 < fVar14) {
          fVar14 = 1.0;
        }
        fVar13 = (float)Framework::AaiExtractTranslate::tImage::RotateY(unsigned int) const(lVar7);
        fVar15 = (float)Framework::AaiExtractTranslate::tImage::RotateY(unsigned int) const(lVar7,uVar1);
        fVar13 = fVar13 + (fVar15 - fVar13) * fVar14;
      }
      fVar14 = 0.0;
      if ((uVar2 >> 0x1a & 1) != 0) {
        uVar6 = *(uint *)(lVar7 + 8);
        uVar4 = (uint)fVar9;
        uVar1 = uVar6 - 1;
        uVar8 = uVar4;
        if (uVar6 <= uVar4) {
          uVar8 = uVar1;
        }
        fVar14 = fVar9 - (float)uVar8;
        if (uVar4 + 1 < uVar6) {
          uVar1 = uVar4 + 1;
        }
        if (1.0 < fVar14) {
          fVar14 = 1.0;
        }
        fVar15 = (float)Framework::AaiExtractTranslate::tImage::RotateZ(unsigned int) const(lVar7);
        fVar16 = (float)Framework::AaiExtractTranslate::tImage::RotateZ(unsigned int) const(lVar7,uVar1);
        fVar14 = -(fVar15 + (fVar16 - fVar15) * fVar14);
      }
      if (*(float *)(param_2 + 0xc) <= fVar9) {
        fVar20 = fVar20 - fVar10;
        fVar13 = fVar13 - fVar12;
        fVar14 = fVar14 - fVar11;
        *param_1 = fVar20;
        param_1[1] = fVar13;
        param_1[2] = fVar14;
        param_1[3] = 1.0;
      }
      else {
        fStack_34 = 0.0;
        uVar8 = (uint)*(float *)(lVar3 + 0x18);
        fVar9 = 0.0;
        if ((uVar2 >> 0x18 & 1) != 0) {
          uVar4 = *(uint *)(lVar7 + 8);
          uVar5 = (uint)(float)uVar8;
          uVar6 = uVar4 - 1;
          uVar1 = uVar5;
          if (uVar4 <= uVar5) {
            uVar1 = uVar6;
          }
          fVar15 = (float)uVar8 - (float)uVar1;
          if (fVar15 <= 0.0) {
            fVar15 = 0.0;
          }
          if (uVar5 + 1 < uVar4) {
            uVar6 = uVar5 + 1;
          }
          if (1.0 < fVar15) {
            fVar15 = 1.0;
          }
          fVar9 = (float)Framework::AaiExtractTranslate::tImage::RotateX(unsigned int) const(lVar7);
          fVar16 = (float)Framework::AaiExtractTranslate::tImage::RotateX(unsigned int) const(lVar7,uVar6);
          fVar9 = fVar9 + (fVar16 - fVar9) * fVar15;
        }
        if ((uVar2 >> 0x19 & 1) != 0) {
          uVar4 = *(uint *)(lVar7 + 8);
          uVar5 = (uint)(float)uVar8;
          uVar6 = uVar4 - 1;
          uVar1 = uVar5;
          if (uVar4 <= uVar5) {
            uVar1 = uVar6;
          }
          fVar15 = (float)uVar8 - (float)uVar1;
          if (fVar15 <= 0.0) {
            fVar15 = 0.0;
          }
          if (uVar5 + 1 < uVar4) {
            uVar6 = uVar5 + 1;
          }
          if (1.0 < fVar15) {
            fVar15 = 1.0;
          }
          fStack_34 = (float)Framework::AaiExtractTranslate::tImage::RotateY(unsigned int) const(lVar7);
          fVar16 = (float)Framework::AaiExtractTranslate::tImage::RotateY(unsigned int) const(lVar7,uVar6);
          fStack_34 = fStack_34 + (fVar16 - fStack_34) * fVar15;
        }
        fVar15 = 0.0;
        fVar16 = 0.0;
        if ((uVar2 >> 0x1a & 1) != 0) {
          uVar4 = *(uint *)(lVar7 + 8);
          uVar5 = (uint)(float)uVar8;
          uVar6 = uVar4 - 1;
          uVar1 = uVar5;
          if (uVar4 <= uVar5) {
            uVar1 = uVar6;
          }
          fVar16 = (float)uVar8 - (float)uVar1;
          if (fVar16 <= 0.0) {
            fVar16 = 0.0;
          }
          if (uVar5 + 1 < uVar4) {
            uVar6 = uVar5 + 1;
          }
          if (1.0 < fVar16) {
            fVar16 = 1.0;
          }
          fVar17 = (float)Framework::AaiExtractTranslate::tImage::RotateZ(unsigned int) const(lVar7);
          fVar18 = (float)Framework::AaiExtractTranslate::tImage::RotateZ(unsigned int) const(lVar7,uVar6);
          fVar16 = -(fVar17 + (fVar18 - fVar17) * fVar16);
        }
        if ((uVar2 >> 7 & 1) == 0) {
          fVar15 = *(float *)(lVar3 + 0x14);
        }
        fVar18 = 0.0;
        fVar17 = 0.0;
        if ((uVar2 >> 0x18 & 1) != 0) {
          uVar6 = *(uint *)(lVar7 + 8);
          uVar4 = (uint)fVar15;
          uVar1 = uVar6 - 1;
          uVar8 = uVar4;
          if (uVar6 <= uVar4) {
            uVar8 = uVar1;
          }
          fVar21 = fVar15 - (float)uVar8;
          if (uVar4 + 1 < uVar6) {
            uVar1 = uVar4 + 1;
          }
          if (1.0 < fVar21) {
            fVar21 = 1.0;
          }
          fVar17 = (float)Framework::AaiExtractTranslate::tImage::RotateX(unsigned int) const(lVar7);
          fVar19 = (float)Framework::AaiExtractTranslate::tImage::RotateX(unsigned int) const(lVar7,uVar1);
          fVar17 = fVar17 + (fVar19 - fVar17) * fVar21;
        }
        if ((uVar2 >> 0x19 & 1) != 0) {
          uVar6 = *(uint *)(lVar7 + 8);
          uVar4 = (uint)fVar15;
          uVar1 = uVar6 - 1;
          uVar8 = uVar4;
          if (uVar6 <= uVar4) {
            uVar8 = uVar1;
          }
          fVar21 = fVar15 - (float)uVar8;
          if (uVar4 + 1 < uVar6) {
            uVar1 = uVar4 + 1;
          }
          if (1.0 < fVar21) {
            fVar21 = 1.0;
          }
          fVar18 = (float)Framework::AaiExtractTranslate::tImage::RotateY(unsigned int) const(lVar7);
          fVar19 = (float)Framework::AaiExtractTranslate::tImage::RotateY(unsigned int) const(lVar7,uVar1);
          fVar18 = fVar18 + (fVar19 - fVar18) * fVar21;
        }
        fVar21 = 0.0;
        if ((uVar2 >> 0x1a & 1) != 0) {
          uVar1 = *(uint *)(lVar7 + 8);
          uVar6 = (uint)fVar15;
          uVar8 = uVar1 - 1;
          uVar2 = uVar6;
          if (uVar1 <= uVar6) {
            uVar2 = uVar8;
          }
          fVar15 = fVar15 - (float)uVar2;
          if (uVar6 + 1 < uVar1) {
            uVar8 = uVar6 + 1;
          }
          if (1.0 < fVar15) {
            fVar15 = 1.0;
          }
          fVar21 = (float)Framework::AaiExtractTranslate::tImage::RotateZ(unsigned int) const(lVar7);
          fVar19 = (float)Framework::AaiExtractTranslate::tImage::RotateZ(unsigned int) const(lVar7,uVar8);
          fVar21 = -(fVar21 + (fVar19 - fVar21) * fVar15);
        }
        fVar20 = (fVar20 - fVar17) + (fVar9 - fVar10) + 0.0;
        fVar13 = (fVar13 - fVar18) + (fStack_34 - fVar12) + 0.0;
        fVar14 = (fVar14 - fVar21) + (fVar16 - fVar11) + 0.0;
        *param_1 = fVar20;
        param_1[1] = fVar13;
        param_1[2] = fVar14;
      }
      fVar9 = _UNK_027e3fd0;
      fVar10 = _UNK_027edb30;
      if ((_UNK_027e3fd0 < fVar20) ||
         (fVar9 = _UNK_027edb30, fVar10 = _UNK_027e3fd0, fVar20 < _UNK_027edb30)) {
        fVar20 = (float)fmodf(fVar20 + fVar9,_UNK_027edb34);
        fVar20 = fVar10 + fVar20;
      }
      fVar9 = _UNK_027e3fd0;
      *param_1 = fVar20;
      fVar20 = _UNK_027edb30;
      if ((fVar9 < fVar13) ||
         (fVar9 = _UNK_027edb30, fVar20 = _UNK_027e3fd0, fVar13 < _UNK_027edb30)) {
        fVar13 = (float)fmodf(fVar13 + fVar9,_UNK_027edb34);
        fVar13 = fVar20 + fVar13;
      }
      fVar9 = _UNK_027e3fd0;
      param_1[1] = fVar13;
      fVar20 = _UNK_027edb30;
      if ((fVar9 < fVar14) ||
         (fVar9 = _UNK_027edb30, fVar20 = _UNK_027e3fd0, fVar14 < _UNK_027edb30)) {
        fVar14 = (float)fmodf(fVar14 + fVar9,_UNK_027edb34);
        fVar14 = fVar20 + fVar14;
      }
      param_1[2] = fVar14;
      param_1[3] = 1.0;
    }
  }
  return;
}

// ==== Framework::CAnimationModel::UpdatePosture(Framework::CMatrix const&)
// vaddr 0x1e60f0c | ghidra 0x1f60f0c | size 112 | symbol _ZN9Framework15CAnimationModel13UpdatePostureERKNS_7CMatrixE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel13UpdatePostureERKNS_7CMatrixE(long param_1,undefined8 param_2)

{
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  
  Framework::CQuaternion::Set(Framework::CMatrix const&)(auStack_30);
  Framework::CMatrix::Translate() const(auStack_40,param_2);
  (**(code **)(**(long **)(param_1 + 0x18) + 0xe8))(*(long **)(param_1 + 0x18),auStack_30);
  (**(code **)(**(long **)(param_1 + 0x18) + 0xd0))(*(long **)(param_1 + 0x18),auStack_40);
  *(undefined4 *)(param_1 + 0x68) = 0;
  Framework::CAnimationModel::InvalidateMatrix(Aska::HierarchicalObject*)(param_1,*(undefined8 *)(param_1 + 0x18));
  return;
}

// ==== Framework::CAnimationModel::InvalidateMatrix(Aska::HierarchicalObject*)
// vaddr 0x1e60f7c | ghidra 0x1f60f7c | size 144 | symbol _ZN9Framework15CAnimationModel16InvalidateMatrixEPN4Aska18HierarchicalObjectE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel16InvalidateMatrixEPN4Aska18HierarchicalObjectE
               (long param_1,long param_2)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  int iVar4;
  
  *(byte *)(param_2 + 0x128) = *(byte *)(param_2 + 0x128) & 0xe0 | 1;
  iVar1 = *(int *)(param_1 + 0x68);
  *(int *)(param_1 + 0x68) = iVar1 + 1;
  if (iVar1 < 5) {
    iVar1 = Aska::HierarchicalObjectContainer::GetChildObjectCount() const(param_2 + 0x30);
    if (0 < iVar1) {
      iVar4 = 0;
      do {
        lVar2 = Aska::HierarchicalObjectContainer::ChildObject(int) const(param_2 + 0x30,iVar4);
        if (lVar2 == 0) {
          uVar3 = 0;
        }
        else {
          uVar3 = *(undefined8 *)(lVar2 + 0xe8);
        }
        _ZN9Framework15CAnimationModel16InvalidateMatrixEPN4Aska18HierarchicalObjectE(param_1,uVar3)
        ;
        iVar4 = iVar4 + 1;
      } while (iVar1 != iVar4);
    }
  }
  return;
}

// ==== Framework::CAnimationModel::UpdateScale(Framework::CVector const&)
// vaddr 0x1e6100c | ghidra 0x1f6100c | size 16 | symbol _ZN9Framework15CAnimationModel11UpdateScaleERKNS_7CVectorE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel11UpdateScaleERKNS_7CVectorE(long param_1)

{
                    /* WARNING: Could not recover jumptable at 0x01f61018. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(param_1 + 0x18) + 0x100))();
  return;
}

// ==== Framework::CAnimationModel::EnableFrameOnly(bool)
// vaddr 0x1e6101c | ghidra 0x1f6101c | size 72 | symbol _ZN9Framework15CAnimationModel15EnableFrameOnlyEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework15CAnimationModel15EnableFrameOnlyEb(long param_1,byte param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x10);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960c08/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationModel.cpp"*/,0x2c3,&UNK_02960ced/*"m_pBlend is null."*/);
    lVar1 = *(long *)(param_1 + 0x10);
  }
  *(byte *)(lVar1 + 0x98) = param_2 & 1;
  return;
}

// ==== Framework::CAnimationTimeElement::Initialize()
// vaddr 0x1e6207c | ghidra 0x1f6207c | size 92 | symbol _ZN9Framework21CAnimationTimeElement10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21CAnimationTimeElement10InitializeEv(long *param_1)

{
  (**(code **)(*param_1 + 0x10))(0xbf800000);
  (**(code **)(*param_1 + 0x18))(0xbf800000,param_1);
  *(undefined4 *)(param_1 + 4) = 0;
  (**(code **)*param_1)(param_1);
  *(undefined1 *)(param_1 + 1) = 1;
  return;
}

// ==== Framework::CAnimationTimeElement::SetMaxLoopCount(unsigned int)
// vaddr 0x1e620d8 | ghidra 0x1f620d8 | size 8 | symbol _ZN9Framework21CAnimationTimeElement15SetMaxLoopCountEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21CAnimationTimeElement15SetMaxLoopCountEj(long param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x20) = param_2;
  return;
}

// ==== Framework::CAnimationTimeElement::Reset()
// vaddr 0x1e620e0 | ghidra 0x1f620e0 | size 20 | symbol _ZN9Framework21CAnimationTimeElement5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21CAnimationTimeElement5ResetEv(long param_1)

{
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined8 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0x3f800000;
  return;
}

// ==== Framework::CAnimationTimeElement::SetPresentFrame(float)
// vaddr 0x1e620f4 | ghidra 0x1f620f4 | size 8 | symbol _ZN9Framework21CAnimationTimeElement15SetPresentFrameEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21CAnimationTimeElement15SetPresentFrameEf(undefined4 param_1,long param_2)

{
  *(undefined4 *)(param_2 + 0x10) = param_1;
  return;
}

// ==== Framework::CAnimationTimeElement::Start()
// vaddr 0x1e620fc | ghidra 0x1f620fc | size 12 | symbol _ZN9Framework21CAnimationTimeElement5StartEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21CAnimationTimeElement5StartEv(undefined8 *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x01f62104. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)*param_1)();
  return;
}

// ==== Framework::CAnimationTimeElement::Progress(float)
// vaddr 0x1e62108 | ghidra 0x1f62108 | size 216 | symbol _ZN9Framework21CAnimationTimeElement8ProgressEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21CAnimationTimeElement8ProgressEf(float param_1,long param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar5 = *(float *)(param_2 + 0x14);
  if (fVar5 < 0.0) {
    return;
  }
  uVar1 = *(uint *)(param_2 + 0xc);
  param_1 = *(float *)(param_2 + 0x24) * param_1;
  if ((uVar1 >> 0x1b & 1) == 0) {
    fVar4 = *(float *)(param_2 + 0x18);
    param_1 = *(float *)(param_2 + 0x10) + param_1;
    *(float *)(param_2 + 0x10) = param_1;
    if (param_1 < fVar4) {
      return;
    }
    if ((uVar1 & 1) != 0) {
      if ((uVar1 >> 0x13 & 1) != 0) goto code_r0x01f621d4;
      iVar3 = *(int *)(param_2 + 0x1c);
      iVar2 = *(int *)(param_2 + 0x20);
      if ((uVar1 & 0x80) != 0) {
        fVar5 = 0.0;
      }
      fVar6 = fVar5 + (param_1 - fVar4);
      if (fVar4 <= fVar6) {
        fVar6 = fVar5;
      }
      goto code_r0x01f621b4;
    }
code_r0x01f62180:
    if ((uVar1 >> 1 & 1) != 0) {
      *(float *)(param_2 + 0x10) = fVar4;
    }
    iVar2 = 1;
  }
  else {
    fVar4 = *(float *)(param_2 + 0x18);
    param_1 = *(float *)(param_2 + 0x10) - param_1;
    *(float *)(param_2 + 0x10) = param_1;
    if (fVar4 < param_1) {
      return;
    }
    if ((uVar1 & 1) == 0) goto code_r0x01f62180;
    if ((uVar1 >> 0x13 & 1) != 0) goto code_r0x01f621d4;
    iVar3 = *(int *)(param_2 + 0x1c);
    iVar2 = *(int *)(param_2 + 0x20);
    if ((uVar1 & 0x80) != 0) {
      fVar5 = 0.0;
    }
    fVar6 = fVar5 + (param_1 - fVar4);
    if (fVar6 <= fVar4) {
      fVar6 = fVar5;
    }
code_r0x01f621b4:
    *(float *)(param_2 + 0x10) = fVar6;
    *(uint *)(param_2 + 0x1c) = iVar3 + 1U;
    if (iVar3 + 1U <= iVar2 - 1U) goto code_r0x01f621d4;
    *(float *)(param_2 + 0x10) = fVar4;
  }
  *(int *)(param_2 + 0x1c) = iVar2;
code_r0x01f621d4:
  *(uint *)(param_2 + 0xc) = uVar1 | 0xc;
  return;
}

// ==== Framework::CAnimationTimeElement::OrFlag(unsigned int)
// vaddr 0x1e621e0 | ghidra 0x1f621e0 | size 16 | symbol _ZN9Framework21CAnimationTimeElement6OrFlagEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21CAnimationTimeElement6OrFlagEj(long param_1,uint param_2)

{
  *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | param_2;
  return;
}

// ==== Framework::CAnimationTimeElement::CheckLoopFrame(float, float&, float&) const
// vaddr 0x1e621f0 | ghidra 0x1f621f0 | size 68 | symbol _ZNK9Framework21CAnimationTimeElement14CheckLoopFrameEfRfS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZNK9Framework21CAnimationTimeElement14CheckLoopFrameEfRfS1_
          (float param_1,long param_2,float *param_3,float *param_4)

{
  float fVar1;
  
  if ((*(byte *)(param_2 + 0xc) & 1) == 0) {
    return 0;
  }
  fVar1 = *(float *)(param_2 + 0x18);
  param_1 = *(float *)(param_2 + 0x10) + param_1;
  if (param_1 < fVar1) {
    return 0;
  }
  *param_3 = fVar1 - *(float *)(param_2 + 0x10);
  *param_4 = param_1 - fVar1;
  return 1;
}

// ==== Framework::CAnimationTimeElement::TerminateProcess(unsigned int)
// vaddr 0x1e62234 | ghidra 0x1f62234 | size 120 | symbol _ZN9Framework21CAnimationTimeElement16TerminateProcessEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21CAnimationTimeElement16TerminateProcessEj(long param_1,uint param_2)

{
  uint uVar1;
  ulong uVar2;
  uint uVar3;
  
  if (param_2 < 3) {
    uVar2 = -(ulong)(param_2 >> 0x1f) & 0xfffffffc00000000 | (ulong)param_2 << 2;
    uVar3 = *(uint *)(&UNK_02961054 + uVar2);
    uVar1 = *(uint *)(&UNK_02961060 + uVar2);
  }
  else {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02960f8d/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\AnimationTimeElement.cpp"*/,0xbb,&UNK_02960fed/*"The argument 'aTerminateProcess' has gotten illegal value.(%d/%d)"*/,3,param_2);
    uVar1 = 1;
    uVar3 = 0xfff7fffd;
  }
  *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & uVar3 | uVar1;
  return;
}

// ==== Framework::CAnimationTimeElement::AndFlag(unsigned int)
// vaddr 0x1e622ac | ghidra 0x1f622ac | size 16 | symbol _ZN9Framework21CAnimationTimeElement7AndFlagEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21CAnimationTimeElement7AndFlagEj(long param_1,uint param_2)

{
  *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & param_2;
  return;
}

// ==== Framework::CAnimationTimeElement::ClearLoopedFlag()
// vaddr 0x1e622bc | ghidra 0x1f622bc | size 16 | symbol _ZN9Framework21CAnimationTimeElement15ClearLoopedFlagEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21CAnimationTimeElement15ClearLoopedFlagEv(long param_1)

{
  *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xfffffffb;
  return;
}

// ==== Framework::CAnimationTimeElement::ClearAllFlag()
// vaddr 0x1e622cc | ghidra 0x1f622cc | size 8 | symbol _ZN9Framework21CAnimationTimeElement12ClearAllFlagEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21CAnimationTimeElement12ClearAllFlagEv(long param_1)

{
  *(undefined4 *)(param_1 + 0xc) = 0;
  return;
}

// ==== Framework::CAnimationTimeElement::SetStartFrame(float)
// vaddr 0x1e622d4 | ghidra 0x1f622d4 | size 8 | symbol _ZN9Framework21CAnimationTimeElement13SetStartFrameEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21CAnimationTimeElement13SetStartFrameEf(undefined4 param_1,long param_2)

{
  *(undefined4 *)(param_2 + 0x14) = param_1;
  return;
}

// ==== Framework::CAnimationTimeElement::SetEndFrame(float)
// vaddr 0x1e622dc | ghidra 0x1f622dc | size 8 | symbol _ZN9Framework21CAnimationTimeElement11SetEndFrameEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework21CAnimationTimeElement11SetEndFrameEf(undefined4 param_1,long param_2)

{
  *(undefined4 *)(param_2 + 0x18) = param_1;
  return;
}

// ==== Framework::CBlendRatePlayer::CPiece::Reset()
// vaddr 0x1e65800 | ghidra 0x1f65800 | size 16 | symbol _ZN9Framework16CBlendRatePlayer6CPiece5ResetEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CBlendRatePlayer6CPiece5ResetEv(undefined8 *param_1)

{
  *(undefined2 *)(param_1 + 3) = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  return;
}

// ==== Framework::CBlendRatePlayer::CPiece::Start(float)
// vaddr 0x1e65810 | ghidra 0x1f65810 | size 100 | symbol _ZN9Framework16CBlendRatePlayer6CPiece5StartEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CBlendRatePlayer6CPiece5StartEf(int param_1,int *param_2)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  
  if (*param_2 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0x20,&UNK_02961ab7/*"Status does not wait.(%d)"*/);
  }
  param_2[3] = param_1;
  puVar2 = PTR__ZN9Framework16CBlendRatePlayer6CPiece13gMasterHandleE_02cc1620;
  iVar3 = 1;
  *param_2 = 1;
  iVar1 = *(int *)puVar2;
  if (iVar1 != -1) {
    iVar3 = iVar1 + 1;
  }
  *(int *)puVar2 = iVar3;
  param_2[1] = iVar3;
  return;
}

// ==== Framework::CBlendRatePlayer::CPiece::Handle() const
// vaddr 0x1e65874 | ghidra 0x1f65874 | size 24 | symbol _ZNK9Framework16CBlendRatePlayer6CPiece6HandleEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK9Framework16CBlendRatePlayer6CPiece6HandleEv(int *param_1)

{
  if (*param_1 != 0) {
    return param_1[1];
  }
  return 0;
}

// ==== Framework::CBlendRatePlayer::CPiece::AddBlendRate(float)
// vaddr 0x1e6588c | ghidra 0x1f6588c | size 76 | symbol _ZN9Framework16CBlendRatePlayer6CPiece12AddBlendRateEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CBlendRatePlayer6CPiece12AddBlendRateEf(float param_1,int *param_2)

{
  if (*param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0x35,&UNK_02961ad1/*"Not running.(%d)"*/,0);
  }
  param_2[2] = (int)((float)param_2[2] + param_1);
  return;
}

// ==== Framework::CBlendRatePlayer::CPiece::SetBlendRateElapsedTimeLimit(float)
// vaddr 0x1e658d8 | ghidra 0x1f658d8 | size 68 | symbol _ZN9Framework16CBlendRatePlayer6CPiece28SetBlendRateElapsedTimeLimitEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CBlendRatePlayer6CPiece28SetBlendRateElapsedTimeLimitEf
               (float param_1,long param_2)

{
  if (param_1 < 0.0) {
    Framework::gDoAssert(char const*, int, char const*, ...)((double)param_1,&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0x3b,&UNK_02961ae2/*"aValue has gotten numeric out of range. (%f/0~)"*/);
  }
  *(float *)(param_2 + 0x14) = param_1;
  return;
}

// ==== Framework::CBlendRatePlayer::CPiece::SetBlendRateElapsedTime(float)
// vaddr 0x1e6591c | ghidra 0x1f6591c | size 68 | symbol _ZN9Framework16CBlendRatePlayer6CPiece23SetBlendRateElapsedTimeEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CBlendRatePlayer6CPiece23SetBlendRateElapsedTimeEf(float param_1,long param_2)

{
  if (param_1 < 0.0) {
    Framework::gDoAssert(char const*, int, char const*, ...)((double)param_1,&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0x41,&UNK_02961ae2/*"aValue has gotten numeric out of range. (%f/0~)"*/);
  }
  *(float *)(param_2 + 0x10) = param_1;
  return;
}

// ==== Framework::CBlendRatePlayer::CPiece::SetBlendRateChangeTime(float)
// vaddr 0x1e65960 | ghidra 0x1f65960 | size 16 | symbol _ZN9Framework16CBlendRatePlayer6CPiece22SetBlendRateChangeTimeEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CBlendRatePlayer6CPiece22SetBlendRateChangeTimeEf(float param_1,long param_2)

{
  *(float *)(param_2 + 0xc) = param_1;
  *(float *)(param_2 + 0x10) = *(float *)(param_2 + 8) * param_1;
  return;
}

// ==== Framework::CBlendRatePlayer::CPiece::Rate() const
// vaddr 0x1e65970 | ghidra 0x1f65970 | size 24 | symbol _ZNK9Framework16CBlendRatePlayer6CPiece4RateEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK9Framework16CBlendRatePlayer6CPiece4RateEv(int *param_1)

{
  if (*param_1 != 0) {
    return param_1[2];
  }
  return 0;
}

// ==== Framework::CBlendRatePlayer::CPiece::Progress(float, float&)
// vaddr 0x1e65988 | ghidra 0x1f65988 | size 464 | symbol _ZN9Framework16CBlendRatePlayer6CPiece8ProgressEfRf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework16CBlendRatePlayer6CPiece8ProgressEfRf(float param_1,int *param_2,float *param_3)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  uint uVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  if (*param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0x5a,&UNK_02961b12/*"Illegal status.(%d)"*/,0);
  }
  if (*(char *)((long)param_2 + 0x19) == '\0') {
    fVar5 = (float)param_2[5];
    param_1 = (float)param_2[4] + param_1;
    bVar1 = false;
    bVar2 = true;
    bVar3 = false;
    if (fVar5 < param_1) {
      bVar1 = false;
      bVar2 = false;
      bVar3 = true;
      if (!NAN(fVar5)) {
        bVar1 = fVar5 < 0.0;
        bVar2 = fVar5 == 0.0;
        bVar3 = false;
      }
    }
    if (bVar2 || bVar1 != bVar3) {
      fVar5 = param_1;
    }
    param_2[4] = (int)fVar5;
  }
  else {
    fVar5 = (float)param_2[4] - param_1;
    param_2[4] = (int)fVar5;
    if (fVar5 < 0.0) {
      param_2[4] = 0;
      *param_2 = 2;
      fVar5 = 0.0;
    }
  }
  fVar6 = (float)param_2[3];
  if (fVar6 <= fVar5) {
    param_2[4] = (int)fVar6;
    param_2[2] = (int)*param_3;
    if ((char)param_2[6] != '\0') {
      return;
    }
    *param_2 = 2;
    fVar5 = 0.0;
  }
  else {
    if (fVar6 <= 0.0) {
      Framework::gDoAssert(char const*, int, char const*, ...)((double)fVar6,&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0x80,&UNK_029605ae/*"Internal error.(%f)"*/);
      fVar6 = (float)param_2[3];
      fVar5 = (float)param_2[4];
    }
    fVar6 = (((fVar5 / fVar6) * _UNK_027e3fd4 + _UNK_02961a58) * _UNK_027e3fd0) / _UNK_027e3fd4;
    uVar4 = (uint)(fVar6 * _UNK_027ebdf4);
    fVar6 = fVar6 - (float)(int)uVar4 * _UNK_027e3fd0;
    fVar5 = fVar6;
    if ((uVar4 & 1) != 0) {
      fVar5 = -fVar6;
    }
    fVar6 = fVar6 * fVar6;
    fVar7 = *param_3;
    fVar5 = (fVar5 * (fVar6 * (fVar6 * (fVar6 * (fVar6 * _UNK_027f7ca4 + _UNK_027f7ca8) +
                                       _UNK_027f7cac) + _UNK_027f7cb0) + _UNK_027f7cb4) + 1.0) * 0.5
    ;
    if (1.0 < fVar5) {
      fVar5 = 1.0;
    }
    if (fVar5 <= 0.0) {
      fVar5 = 0.0;
    }
    param_2[2] = (int)(fVar7 * fVar5);
    if ((char)param_2[6] != '\0') {
      return;
    }
    fVar5 = *param_3 - fVar7 * fVar5;
  }
  *param_3 = fVar5;
  return;
}

// ==== Framework::CBlendRatePlayer::CBlendRatePlayer()
// vaddr 0x1e65b58 | ghidra 0x1f65b58 | size 24 | symbol _ZN9Framework16CBlendRatePlayerC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CBlendRatePlayerC2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework16CBlendRatePlayerE_02cbd8d0;
  param_1[2] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  return;
}

// ==== Framework::CBlendRatePlayer::~CBlendRatePlayer()
// vaddr 0x1e65b70 | ghidra 0x1f65b70 | size 48 | symbol _ZN9Framework16CBlendRatePlayerD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CBlendRatePlayerD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework16CBlendRatePlayerE_02cbd8d0 + 0x10);
  if (param_1[2] != 0) {
    operator delete[](void*)();
    param_1[2] = 0;
  }
  return;
}

// ==== Framework::CBlendRatePlayer::Release()
// vaddr 0x1e65ba0 | ghidra 0x1f65ba0 | size 32 | symbol _ZN9Framework16CBlendRatePlayer7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CBlendRatePlayer7ReleaseEv(long param_1)

{
  if (*(long *)(param_1 + 0x10) != 0) {
    operator delete[](void*)();
    *(undefined8 *)(param_1 + 0x10) = 0;
  }
  return;
}

// ==== Framework::CBlendRatePlayer::~CBlendRatePlayer()
// vaddr 0x1e65bc0 | ghidra 0x1f65bc0 | size 48 | symbol _ZN9Framework16CBlendRatePlayerD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CBlendRatePlayerD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework16CBlendRatePlayerE_02cbd8d0 + 0x10);
  if (param_1[2] != 0) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CBlendRatePlayer::Initialize(unsigned int)
// vaddr 0x1e65bf0 | ghidra 0x1f65bf0 | size 164 | symbol _ZN9Framework16CBlendRatePlayer10InitializeEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CBlendRatePlayer10InitializeEj(long param_1,uint param_2)

{
  uint uVar1;
  undefined8 *puVar2;
  ulong uVar3;
  
  if (*(long *)(param_1 + 0x10) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0xaa,&UNK_02961b26/*"Already initialized."*/);
  }
  *(uint *)(param_1 + 8) = param_2;
  puVar2 = (undefined8 *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 * 0x1c,PTR__ZSt7nothrow_02cb9a80);
  *(undefined8 **)(param_1 + 0x10) = puVar2;
  if (param_2 != 0) {
    *(undefined2 *)(puVar2 + 3) = 0;
    puVar2[1] = 0;
    puVar2[2] = 0;
    *puVar2 = 0;
    if (1 < *(uint *)(param_1 + 8)) {
      uVar3 = 1;
      do {
        puVar2 = (undefined8 *)(*(long *)(param_1 + 0x10) + uVar3 * 0x1c);
        *(undefined2 *)(puVar2 + 3) = 0;
        puVar2[1] = 0;
        puVar2[2] = 0;
        *puVar2 = 0;
        uVar1 = (int)uVar3 + 1;
        uVar3 = (ulong)uVar1;
      } while (uVar1 < *(uint *)(param_1 + 8));
    }
  }
  return;
}

// ==== Framework::CBlendRatePlayer::Progress(float)
// vaddr 0x1e65c94 | ghidra 0x1f65c94 | size 140 | symbol _ZN9Framework16CBlendRatePlayer8ProgressEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CBlendRatePlayer8ProgressEf(undefined8 param_1,long param_2)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uStack_24;
  
  if (*(long *)(param_2 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0xc0,&UNK_02961b3b/*"Uninitialized object."*/);
  }
  uStack_24 = 0x3f800000;
  uVar2 = *(uint *)(param_2 + 8);
  if (uVar2 != 0) {
    uVar3 = 0;
    do {
      piVar1 = (int *)(*(long *)(param_2 + 0x10) + (ulong)uVar3 * 0x1c);
      if (*piVar1 != 0) {
        Framework::CBlendRatePlayer::CPiece::Progress(float, float&)(param_1,piVar1,&uStack_24);
        uVar2 = *(uint *)(param_2 + 8);
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < uVar2);
  }
  return;
}

// ==== Framework::CBlendRatePlayer::Add(float)
// vaddr 0x1e65d20 | ghidra 0x1f65d20 | size 328 | symbol _ZN9Framework16CBlendRatePlayer3AddEf | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZN9Framework16CBlendRatePlayer3AddEf(int param_1,long param_2)

{
  undefined *puVar1;
  uint uVar2;
  undefined8 *puVar3;
  int iVar4;
  undefined8 *puVar5;
  ulong uVar6;
  int iVar7;
  int *piVar8;
  ulong uVar9;
  undefined8 uVar10;
  
  puVar3 = *(undefined8 **)(param_2 + 0x10);
  if (puVar3 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0xdd,&UNK_02961b3b/*"Uninitialized object."*/);
    puVar3 = *(undefined8 **)(param_2 + 0x10);
    if (puVar3 == (undefined8 *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0x11d,&UNK_02961b3b/*"Uninitialized object."*/);
      puVar3 = *(undefined8 **)(param_2 + 0x10);
    }
  }
  iVar4 = *(int *)(param_2 + 8);
  uVar6 = (ulong)(iVar4 - 1U);
  if (*(int *)((long)puVar3 + uVar6 * 0x1c) == 0) {
    uVar9 = 0;
  }
  else {
    uVar9 = (ulong)*(uint *)((long)puVar3 + uVar6 * 0x1c + 4) << 0x20;
  }
  if (iVar4 - 1U != 0) {
    uVar2 = 0;
    iVar7 = -2;
    do {
      puVar5 = (undefined8 *)((long)puVar3 + (ulong)(uint)(iVar4 + iVar7) * 0x1c);
      uVar10 = *(undefined8 *)((long)puVar5 + 10);
      puVar3 = (undefined8 *)((long)puVar3 + (ulong)((int)uVar6 + iVar7 + 2) * 0x1c);
      *(undefined8 *)((long)puVar3 + 0x12) = *(undefined8 *)((long)puVar5 + 0x12);
      *(undefined8 *)((long)puVar3 + 10) = uVar10;
      uVar10 = *puVar5;
      uVar2 = uVar2 + 1;
      iVar7 = iVar7 + -1;
      puVar3[1] = puVar5[1];
      *puVar3 = uVar10;
      iVar4 = *(int *)(param_2 + 8);
      puVar3 = *(undefined8 **)(param_2 + 0x10);
      uVar6 = (ulong)(iVar4 - 1U);
    } while (uVar2 < iVar4 - 1U);
  }
  *(undefined2 *)(puVar3 + 3) = 0;
  puVar3[1] = 0;
  puVar3[2] = 0;
  *puVar3 = 0;
  piVar8 = *(int **)(param_2 + 0x10);
  if (*piVar8 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0x20,&UNK_02961ab7/*"Status does not wait.(%d)"*/);
  }
  piVar8[3] = param_1;
  puVar1 = PTR__ZN9Framework16CBlendRatePlayer6CPiece13gMasterHandleE_02cc1620;
  uVar2 = 1;
  *piVar8 = 1;
  iVar4 = *(int *)puVar1;
  if (iVar4 != -1) {
    uVar2 = iVar4 + 1;
  }
  *(uint *)puVar1 = uVar2;
  piVar8[1] = uVar2;
  return uVar9 | uVar2;
}

// ==== Framework::CBlendRatePlayer::MakeBlank()
// vaddr 0x1e65e68 | ghidra 0x1f65e68 | size 192 | symbol _ZN9Framework16CBlendRatePlayer9MakeBlankEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN9Framework16CBlendRatePlayer9MakeBlankEv(long param_1)

{
  undefined4 uVar1;
  undefined8 *puVar2;
  int iVar3;
  undefined8 *puVar4;
  ulong uVar5;
  uint uVar6;
  int iVar7;
  undefined8 uVar8;
  
  puVar2 = *(undefined8 **)(param_1 + 0x10);
  if (puVar2 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0x11d,&UNK_02961b3b/*"Uninitialized object."*/);
    puVar2 = *(undefined8 **)(param_1 + 0x10);
  }
  iVar3 = *(int *)(param_1 + 8);
  uVar5 = (ulong)(iVar3 - 1U);
  if (*(int *)((long)puVar2 + uVar5 * 0x1c) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)((long)puVar2 + uVar5 * 0x1c + 4);
  }
  if (iVar3 - 1U != 0) {
    uVar6 = 0;
    iVar7 = -2;
    do {
      puVar4 = (undefined8 *)((long)puVar2 + (ulong)(uint)(iVar3 + iVar7) * 0x1c);
      uVar8 = *(undefined8 *)((long)puVar4 + 10);
      puVar2 = (undefined8 *)((long)puVar2 + (ulong)((int)uVar5 + iVar7 + 2) * 0x1c);
      *(undefined8 *)((long)puVar2 + 0x12) = *(undefined8 *)((long)puVar4 + 0x12);
      *(undefined8 *)((long)puVar2 + 10) = uVar8;
      uVar8 = *puVar4;
      uVar6 = uVar6 + 1;
      iVar7 = iVar7 + -1;
      puVar2[1] = puVar4[1];
      *puVar2 = uVar8;
      iVar3 = *(int *)(param_1 + 8);
      puVar2 = *(undefined8 **)(param_1 + 0x10);
      uVar5 = (ulong)(iVar3 - 1U);
    } while (uVar6 < iVar3 - 1U);
  }
  *(undefined2 *)(puVar2 + 3) = 0;
  puVar2[1] = 0;
  puVar2[2] = 0;
  *puVar2 = 0;
  return uVar1;
}

// ==== Framework::CBlendRatePlayer::Remove(unsigned int)
// vaddr 0x1e65f28 | ghidra 0x1f65f28 | size 304 | symbol _ZN9Framework16CBlendRatePlayer6RemoveEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CBlendRatePlayer6RemoveEj(long param_1,int param_2)

{
  uint uVar1;
  long lVar2;
  int *piVar3;
  ulong uVar4;
  uint uVar5;
  int iVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined2 uStack_30;
  undefined2 uStack_2e;
  undefined6 uStack_2c;
  
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0xe8,&UNK_02961b3b/*"Uninitialized object."*/);
    uVar1 = *(uint *)(param_1 + 8);
  }
  else {
    uVar1 = *(uint *)(param_1 + 8);
  }
  if (uVar1 != 0) {
    piVar3 = *(int **)(param_1 + 0x10);
    uVar5 = 0;
    do {
      iVar6 = 0;
      if (*piVar3 != 0) {
        iVar6 = piVar3[1];
      }
      if (iVar6 == param_2) {
        *(undefined2 *)(piVar3 + 6) = 0;
        piVar3[2] = 0;
        piVar3[3] = 0;
        piVar3[4] = 0;
        piVar3[5] = 0;
        piVar3[0] = 0;
        piVar3[1] = 0;
        lVar2 = *(long *)(param_1 + 0x10);
        goto joined_r0x01f65fb8;
      }
      uVar5 = uVar5 + 1;
      piVar3 = piVar3 + 7;
    } while (uVar5 < uVar1);
  }
  lVar2 = *(long *)(param_1 + 0x10);
joined_r0x01f65fb8:
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0x12f,&UNK_02961b3b/*"Uninitialized object."*/);
  }
  do {
    if (*(int *)(param_1 + 8) == 1) {
      return;
    }
    piVar3 = *(int **)(param_1 + 0x10);
    uVar4 = 0;
    while ((*piVar3 == 1 || (piVar3[7] != 1))) {
      uVar4 = uVar4 + 1;
      piVar3 = piVar3 + 7;
      if (*(int *)(param_1 + 8) - 1 <= uVar4) {
        return;
      }
    }
    uStack_2c = (undefined6)*(undefined8 *)(piVar3 + 0xc);
    uStack_30 = (undefined2)((ulong)*(undefined8 *)(piVar3 + 10) >> 0x20);
    uStack_2e = (undefined2)((ulong)*(undefined8 *)(piVar3 + 10) >> 0x30);
    uVar8 = *(undefined8 *)(piVar3 + 9);
    uVar7 = *(undefined8 *)(piVar3 + 7);
    *(undefined8 *)((long)piVar3 + 0x2e) = *(undefined8 *)((long)piVar3 + 0x12);
    *(undefined8 *)((long)piVar3 + 0x26) = *(undefined8 *)((long)piVar3 + 10);
    *(undefined8 *)(piVar3 + 9) = *(undefined8 *)(piVar3 + 2);
    *(undefined8 *)(piVar3 + 7) = *(undefined8 *)piVar3;
    *(ulong *)((long)piVar3 + 0x12) = CONCAT62(uStack_2c,uStack_2e);
    *(ulong *)((long)piVar3 + 10) = CONCAT26(uStack_30,(int6)((ulong)uVar8 >> 0x10));
    *(undefined8 *)(piVar3 + 2) = uVar8;
    *(undefined8 *)piVar3 = uVar7;
  } while( true );
}

// ==== Framework::CBlendRatePlayer::Defrag()
// vaddr 0x1e66058 | ghidra 0x1f66058 | size 172 | symbol _ZN9Framework16CBlendRatePlayer6DefragEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CBlendRatePlayer6DefragEv(long param_1)

{
  int *piVar1;
  uint uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined2 uStack_20;
  undefined2 uStack_1e;
  undefined6 uStack_1c;
  
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0x12f,&UNK_02961b3b/*"Uninitialized object."*/);
  }
  do {
    if (*(int *)(param_1 + 8) == 1) {
      return;
    }
    piVar1 = *(int **)(param_1 + 0x10);
    uVar2 = 0;
    while ((*piVar1 == 1 || (piVar1[7] != 1))) {
      uVar2 = uVar2 + 1;
      piVar1 = piVar1 + 7;
      if (*(int *)(param_1 + 8) - 1U <= uVar2) {
        return;
      }
    }
    uStack_1c = (undefined6)*(undefined8 *)(piVar1 + 0xc);
    uStack_20 = (undefined2)((ulong)*(undefined8 *)(piVar1 + 10) >> 0x20);
    uStack_1e = (undefined2)((ulong)*(undefined8 *)(piVar1 + 10) >> 0x30);
    uVar4 = *(undefined8 *)(piVar1 + 9);
    uVar3 = *(undefined8 *)(piVar1 + 7);
    *(undefined8 *)((long)piVar1 + 0x2e) = *(undefined8 *)((long)piVar1 + 0x12);
    *(undefined8 *)((long)piVar1 + 0x26) = *(undefined8 *)((long)piVar1 + 10);
    *(undefined8 *)(piVar1 + 9) = *(undefined8 *)(piVar1 + 2);
    *(undefined8 *)(piVar1 + 7) = *(undefined8 *)piVar1;
    *(ulong *)((long)piVar1 + 0x12) = CONCAT62(uStack_1c,uStack_1e);
    *(ulong *)((long)piVar1 + 10) = CONCAT26(uStack_20,(int6)((ulong)uVar4 >> 0x10));
    *(undefined8 *)(piVar1 + 2) = uVar4;
    *(undefined8 *)piVar1 = uVar3;
  } while( true );
}

// ==== Framework::CBlendRatePlayer::crPiece(unsigned int) const
// vaddr 0x1e66104 | ghidra 0x1f66104 | size 156 | symbol _ZNK9Framework16CBlendRatePlayer7crPieceEj | lib libSOA-3.7.0.so | 2026-10-04
int * _ZNK9Framework16CBlendRatePlayer7crPieceEj(long param_1,int param_2)

{
  uint uVar1;
  int *piVar2;
  ulong uVar3;
  int iVar4;
  
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0xfc,&UNK_02961b3b/*"Uninitialized object."*/);
    uVar1 = *(uint *)(param_1 + 8);
  }
  else {
    uVar1 = *(uint *)(param_1 + 8);
  }
  if (uVar1 != 0) {
    piVar2 = *(int **)(param_1 + 0x10);
    uVar3 = 0;
    do {
      iVar4 = 0;
      if (*piVar2 != 0) {
        iVar4 = piVar2[1];
      }
      if (iVar4 == param_2) {
        return piVar2;
      }
      uVar3 = uVar3 + 1;
      piVar2 = piVar2 + 7;
    } while (uVar3 < uVar1);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0x105,&UNK_02961b51/*"Thi s handle is invalid.(%d)"*/,param_2);
  return *(int **)(param_1 + 0x10);
}

// ==== Framework::CBlendRatePlayer::rPiece(unsigned int) const
// vaddr 0x1e661a0 | ghidra 0x1f661a0 | size 156 | symbol _ZNK9Framework16CBlendRatePlayer6rPieceEj | lib libSOA-3.7.0.so | 2026-10-04
int * _ZNK9Framework16CBlendRatePlayer6rPieceEj(long param_1,int param_2)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0xfc,&UNK_02961b3b/*"Uninitialized object."*/);
    uVar1 = *(uint *)(param_1 + 8);
  }
  else {
    uVar1 = *(uint *)(param_1 + 8);
  }
  if (uVar1 != 0) {
    piVar2 = *(int **)(param_1 + 0x10);
    uVar3 = 0;
    do {
      iVar4 = 0;
      if (*piVar2 != 0) {
        iVar4 = piVar2[1];
      }
      if (iVar4 == param_2) {
        return piVar2;
      }
      uVar3 = uVar3 + 1;
      piVar2 = piVar2 + 7;
    } while (uVar3 < uVar1);
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02961a5c/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\BlendRatePlayer.cpp"*/,0x105,&UNK_02961b51/*"Thi s handle is invalid.(%d)"*/,param_2);
  return *(int **)(param_1 + 0x10);
}

// ==== Framework::CBlendRatePlayer::NumPlayHandle() const
// vaddr 0x1e6623c | ghidra 0x1f6623c | size 76 | symbol _ZNK9Framework16CBlendRatePlayer13NumPlayHandleEv | lib libSOA-3.7.0.so | 2026-10-04
int _ZNK9Framework16CBlendRatePlayer13NumPlayHandleEv(long param_1)

{
  int iVar1;
  int *piVar2;
  ulong uVar3;
  int iVar4;
  
  if (*(uint *)(param_1 + 8) != 0) {
    uVar3 = 0;
    iVar1 = 0;
    piVar2 = (int *)(*(long *)(param_1 + 0x10) + 4);
    do {
      iVar4 = 0;
      if (piVar2[-1] != 0) {
        iVar4 = *piVar2;
      }
      uVar3 = uVar3 + 1;
      if (iVar4 != 0) {
        iVar1 = iVar1 + 1;
      }
      piVar2 = piVar2 + 7;
    } while (uVar3 < *(uint *)(param_1 + 8));
    return iVar1;
  }
  return 0;
}

// ==== Framework::CBlendRatePlayer::SetTerminatedForIndependentCalcBlendRate()
// vaddr 0x1e66288 | ghidra 0x1f66288 | size 76 | symbol _ZN9Framework16CBlendRatePlayer40SetTerminatedForIndependentCalcBlendRateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework16CBlendRatePlayer40SetTerminatedForIndependentCalcBlendRateEv(long param_1)

{
  uint uVar1;
  long lVar2;
  uint uVar3;
  
  uVar1 = *(uint *)(param_1 + 8);
  if (uVar1 != 0) {
    uVar3 = 0;
    do {
      if (*(char *)(*(long *)(param_1 + 0x10) + (ulong)uVar3 * 0x1c + 0x18) != '\0') {
        lVar2 = *(long *)(param_1 + 0x10) + (ulong)uVar3 * 0x1c;
        *(undefined1 *)(lVar2 + 0x19) = 1;
        *(undefined4 *)(lVar2 + 0x10) = 0;
        uVar1 = *(uint *)(param_1 + 8);
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < uVar1);
  }
  return;
}


// FAILED to create function at 02960870 typeinfo name for Aska::TArray<Framework::CAnimationBlendContainer::_tBlendMotionData, false>
// FAILED to create function at 02ba6ac8 Framework::CAnimationBlendContainer::vtable
// FAILED to create function at 02ba6c40 Framework::CAnimationBlendContainer::typeinfo
// FAILED to create function at 02ba6c58 Aska::TArray<Framework::CAnimationBlendContainer::_tBlendMotionData,false>::vtable
// FAILED to create function at 02ba6c78 Aska::TArray<Framework::CAnimationBlendContainer::_tBlendMotionData,false>::typeinfo
// FAILED to create function at 02ba6c88 Framework::CAnimationElement::vtable
// FAILED to create function at 02ba6cd0 Framework::CAnimationElement::typeinfo
// FAILED to create function at 02ba6ce8 Framework::CAnimationModel::vtable
// FAILED to create function at 02ba6de0 Framework::CAnimationModel::typeinfo
// FAILED to create function at 02ba6df8 Framework::CAnimationTimeElement::vtable
// FAILED to create function at 02ba6e28 Framework::CAnimationTimeElement::typeinfo
// FAILED to create function at 02ba7308 Framework::CBlendRatePlayer::vtable
// FAILED to create function at 02ba7328 Framework::CBlendRatePlayer::typeinfo
// FAILED to create function at 02d00280 Framework::CBlendRatePlayer::CPiece::gMasterHandle
