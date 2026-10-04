// port/decomp/resource/local_kvs.c: Ghidra decompiles for the resource subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:15 UTC: tools/decomp.sh '--into' 'resource/local_kvs' 'Aska::LocalKVS::' 'CGameLocalKVS::'

// ==== CGameLocalKVS::CGameLocalKVS()
// vaddr 0x136c278 | ghidra 0x146c278 | size 212 | symbol _ZN13CGameLocalKVSC2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN13CGameLocalKVSC1Ev(long *param_1)

{
  undefined *puVar1;
  undefined1 *puVar2;
  undefined8 uVar3;
  long lStack_18;
  
  puVar1 = PTR__ZN9Framework10TSingletonI13CGameLocalKVSE11m_pInstanceE_02cb8e58;
  if (*(long *)PTR__ZN9Framework10TSingletonI13CGameLocalKVSE11m_pInstanceE_02cb8e58 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x15,&UNK_027daee5/*"m_pInstance isn't null.(%08x)"*/);
  }
  *(long **)puVar1 = param_1;
  puVar1 = PTR__ZTV13CGameLocalKVS_02cbad28;
  *(undefined1 *)(param_1 + 3) = 0;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 0;
  puVar2 = (undefined1 *)operator new(unsigned long, std::nothrow_t const&)(0x188,PTR__ZSt7nothrow_02cb9a80);
  puVar1 = PTR__ZZN4Aska8Cryption9TChaCha20ILb0EEC1EvE8constant_02cbffc8;
  if (puVar2 != (undefined1 *)0x0) {
    *(undefined2 *)(puVar2 + 0x180) = 0;
    puVar2[0x184] = 0;
    *puVar2 = 0;
    uVar3 = *(undefined8 *)puVar1;
    *(undefined8 *)(puVar2 + 0x108) = *(undefined8 *)(puVar1 + 8);
    *(undefined8 *)(puVar2 + 0x100) = uVar3;
  }
  param_1[1] = (long)puVar2;
  Aska::LocalKVS::Init(char const*, bool, char*, char*)(&lStack_18,puVar2,&UNK_02807414/*"Game"*/,1,0,0);
  param_1[2] = lStack_18;
  if (-1 < lStack_18) {
    CGameLocalKVS::_VersionCheck(Aska::LocalKVS*)(param_1,param_1[1]);
    CGameLocalKVS::_VersionCheck(Aska::LocalKVS*)(param_1,*(undefined8 *)PTR__ZN4Aska6Global11m_pLocalKVSE_02cbd248);
  }
  return;
}

// ==== CGameLocalKVS::VersionCheck()
// vaddr 0x136c34c | ghidra 0x146c34c | size 40 | symbol _ZN13CGameLocalKVS12VersionCheckEv | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0146c358: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0146c35c) */

void _ZN13CGameLocalKVS12VersionCheckEv(long param_1)

{
  (*(code *)PTR__ZN13CGameLocalKVS13_VersionCheckEPN4Aska8LocalKVSE_02c9b1a8)
            (param_1,*(undefined8 *)(param_1 + 8));
  return;
}

// ==== CGameLocalKVS::~CGameLocalKVS()
// vaddr 0x136c374 | ghidra 0x146c374 | size 92 | symbol _ZN13CGameLocalKVSD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN13CGameLocalKVSD2Ev(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTV13CGameLocalKVS_02cbad28 + 0x10);
  if (param_1[1] != 0) {
    operator delete(void*)();
    param_1[1] = 0;
  }
  puVar1 = PTR__ZN9Framework10TSingletonI13CGameLocalKVSE11m_pInstanceE_02cb8e58;
  if (*(long *)PTR__ZN9Framework10TSingletonI13CGameLocalKVSE11m_pInstanceE_02cb8e58 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x1d,&UNK_027daf21/*"m_pInstance is null."*/);
  }
  *(undefined8 *)puVar1 = 0;
  return;
}

// ==== CGameLocalKVS::~CGameLocalKVS()
// vaddr 0x136c3d0 | ghidra 0x146c3d0 | size 104 | symbol _ZN13CGameLocalKVSD0Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x0146c3f4: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0146c3f8) */

void _ZN13CGameLocalKVSD0Ev(long *param_1)

{
  undefined *puVar1;
  long *plVar2;
  
  plVar2 = (long *)param_1[1];
  *param_1 = (long)(PTR__ZTV13CGameLocalKVS_02cbad28 + 0x10);
  puVar1 = PTR__ZN9Framework10TSingletonI13CGameLocalKVSE11m_pInstanceE_02cb8e58;
  if (plVar2 == (long *)0x0) {
    if (*(long *)PTR__ZN9Framework10TSingletonI13CGameLocalKVSE11m_pInstanceE_02cb8e58 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x1d,&UNK_027daf21/*"m_pInstance is null."*/);
    }
    *(undefined8 *)puVar1 = 0;
    plVar2 = param_1;
  }
  (*(code *)PTR__ZdlPv_02ca4758)(plVar2);
  return;
}

// ==== CGameLocalKVS::Result() const
// vaddr 0x136c438 | ghidra 0x146c438 | size 8 | symbol _ZNK13CGameLocalKVS6ResultEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZNK13CGameLocalKVS6ResultEv(long param_1)

{
  return param_1 + 0x10;
}

// ==== CGameLocalKVS::pSubstance() const
// vaddr 0x136c440 | ghidra 0x146c440 | size 8 | symbol _ZNK13CGameLocalKVS10pSubstanceEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK13CGameLocalKVS10pSubstanceEv(long param_1)

{
  return *(undefined8 *)(param_1 + 8);
}

// ==== CGameLocalKVS::_VersionCheck(Aska::LocalKVS*)
// vaddr 0x136c448 | ghidra 0x146c448 | size 1112 | symbol _ZN13CGameLocalKVS13_VersionCheckEPN4Aska8LocalKVSE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN13CGameLocalKVS13_VersionCheckEPN4Aska8LocalKVSE(long param_1,long param_2)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int *piVar6;
  long lVar7;
  undefined8 uVar8;
  int iVar9;
  int *piStack_98;
  int *piStack_90;
  undefined1 auStack_88 [12];
  undefined4 uStack_7c;
  undefined1 auStack_78 [8];
  undefined4 uStack_70;
  int iStack_6c;
  undefined5 uStack_68;
  int *piStack_60;
  int *piStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined1 uStack_40;
  
  lVar7 = param_1;
  if (param_2 == 0) {
    lVar7 = Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02807419/*"C:\BAS_Submission\Client\Project\..\Source\Game\GameLocalKVS.cpp"*/,0x13d,&UNK_0280745a/*"apLocalKvs is null."*/);
  }
  CGameLocalKVS::_SetCipherKey(char const*, Aska::LocalKVS*)(lVar7,&UNK_02807472/*"1.1"*/,param_2);
  uVar8 = Aska::LocalKVS::GetBinary(char const*, long*) const(&piStack_60,param_2,&UNK_02a354cc/*"version"*/,0);
  piVar6 = piStack_58;
  piStack_98 = piStack_60;
  if (piStack_58 == (int *)0x0) {
code_r0x0146c4e8:
    if (piStack_60 != (int *)0x0) {
      operator delete[](void*)();
    }
    uVar8 = 0;
    if (piStack_58 != (int *)0x0) {
      uVar8 = Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_58,0x10);
      if (bVar3) {
        *piStack_58 = *piStack_58 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (piStack_58 == (int *)0x0) goto code_r0x0146c4e8;
    do {
      iVar9 = *piStack_58;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_58,0x10);
      if (bVar3) {
        *piStack_58 = iVar9 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar9 + -1 == 0) goto code_r0x0146c4e8;
  }
  if (piStack_98 == (int *)0x0) {
    bVar5 = false;
    bVar3 = true;
    if (piVar6 != (int *)0x0) goto code_r0x0146c5d8;
code_r0x0146c5ec:
    uVar8 = 0;
    if (piStack_98 != (int *)0x0) {
      uVar8 = operator delete[](void*)();
    }
    if (piVar6 != (int *)0x0) {
      uVar8 = Aska::TSharedPointerCode::DeleteCounter(int*)(piVar6);
    }
  }
  else {
    CGameLocalKVS::_SetCipherKey(char const*, Aska::LocalKVS*)(uVar8,piStack_98,param_2);
    uStack_70 = 0;
    iStack_6c = 0;
    Aska::LocalKVS::GetBinary(char const*, long*) const(&piStack_60,param_2,&UNK_0280746e/*"crc"*/,&uStack_70);
    if (piStack_60 == (int *)0x0) {
      iVar9 = 0;
      if (piStack_58 != (int *)0x0) goto code_r0x0146c574;
joined_r0x0146c58c:
      if (piStack_60 != (int *)0x0) {
        operator delete[](void*)();
      }
      if (piStack_58 != (int *)0x0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      iVar9 = *piStack_60;
      if (piStack_58 == (int *)0x0) goto joined_r0x0146c58c;
code_r0x0146c574:
      do {
        iVar1 = *piStack_58;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piStack_58,0x10);
        if (bVar3) {
          *piStack_58 = iVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar1 + -1 == 0) goto joined_r0x0146c58c;
    }
    piStack_60 = (int *)((ulong)piStack_60 & 0xffffffff00000000);
    uVar8 = Aska::Hash::CRC(unsigned char const*, unsigned long, unsigned int*)(&UNK_02807472/*"1.1"*/,3,&piStack_60);
    bVar3 = false;
    bVar5 = true;
    *(bool *)(param_1 + 0x18) = -1 < iStack_6c && (int)piStack_60 == iVar9;
    if (piVar6 == (int *)0x0) goto code_r0x0146c5ec;
code_r0x0146c5d8:
    do {
      iVar9 = *piVar6;
      cVar2 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar4) {
        *piVar6 = iVar9 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar9 + -1 == 0) goto code_r0x0146c5ec;
  }
  if (!bVar3) goto code_r0x0146c784;
  CGameLocalKVS::_SetCipherKey(char const*, Aska::LocalKVS*)(uVar8,&UNK_029dd736/*"1.0"*/,param_2);
  uVar8 = Aska::LocalKVS::GetBinary(char const*, long*) const(&piStack_60,param_2,&UNK_02a354cc/*"version"*/,0);
  piVar6 = piStack_58;
  piStack_98 = piStack_60;
  if (piStack_58 == (int *)0x0) {
code_r0x0146c674:
    if (piStack_60 != (int *)0x0) {
      operator delete[](void*)();
    }
    uVar8 = 0;
    if (piStack_58 != (int *)0x0) {
      uVar8 = Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_58,0x10);
      if (bVar3) {
        *piStack_58 = *piStack_58 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (piStack_58 == (int *)0x0) goto code_r0x0146c674;
    do {
      iVar9 = *piStack_58;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_58,0x10);
      if (bVar3) {
        *piStack_58 = iVar9 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar9 + -1 == 0) goto code_r0x0146c674;
  }
  if (piStack_98 != (int *)0x0) {
    CGameLocalKVS::_SetCipherKey(char const*, Aska::LocalKVS*)(uVar8,piStack_98,param_2);
    uStack_70 = 0;
    iStack_6c = 0;
    Aska::LocalKVS::GetBinary(char const*, long*) const(&piStack_60,param_2,&UNK_0280746e/*"crc"*/,&uStack_70);
    if (piStack_60 == (int *)0x0) {
      iVar9 = 0;
      if (piStack_58 != (int *)0x0) goto code_r0x0146c6e8;
code_r0x0146c700:
      if (piStack_60 != (int *)0x0) {
        operator delete[](void*)();
      }
      if (piStack_58 != (int *)0x0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      iVar9 = *piStack_60;
      if (piStack_58 == (int *)0x0) goto code_r0x0146c700;
code_r0x0146c6e8:
      do {
        iVar1 = *piStack_58;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piStack_58,0x10);
        if (bVar3) {
          *piStack_58 = iVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar1 + -1 == 0) goto code_r0x0146c700;
    }
    piStack_60 = (int *)((ulong)piStack_60 & 0xffffffff00000000);
    Aska::Hash::CRC(unsigned char const*, unsigned long, unsigned int*)(&UNK_02807472/*"1.1"*/,3,&piStack_60);
    bVar5 = true;
    *(bool *)(param_1 + 0x18) = -1 < iStack_6c && (int)piStack_60 == iVar9;
  }
  if (piVar6 != (int *)0x0) {
    do {
      iVar9 = *piVar6;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar6,0x10);
      if (bVar3) {
        *piVar6 = iVar9 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar9 + -1 != 0) goto code_r0x0146c784;
  }
  if (piStack_98 != (int *)0x0) {
    operator delete[](void*)();
  }
  if (piVar6 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)(piVar6);
  }
code_r0x0146c784:
  if (!bVar5) {
    Aska::LocalKVS::SetCipher(bool, char*, char*)(auStack_88,param_2,1,0,0);
    BAS::GetUUID()(&piStack_98);
    if (piStack_98 == (int *)0x0) {
      uStack_7c = 0;
      Aska::Hash::CRC(unsigned char const*, unsigned long, unsigned int*)(&UNK_02807472/*"1.1"*/,3,&uStack_7c);
      uStack_68 = _UNK_0280749f;
      piStack_58 = _UNK_0280747e;
      piStack_60 = _UNK_02807476;
      uStack_48 = _UNK_0280748e;
      uStack_50 = _UNK_02807486;
      uStack_40 = 0;
      uStack_70 = (undefined4)_UNK_02807497;
      iStack_6c = (int)(CONCAT35(_UNK_0280749c,_UNK_02807497) >> 0x20);
      Aska::LocalKVS::SetCipher(bool, char*, char*)(auStack_78,param_2,1,&piStack_60,&uStack_70);
      uStack_70 = uStack_7c;
      Aska::LocalKVS::SetBinary(char const*, signed char const*, long)(&piStack_60,param_2,&UNK_0280746e/*"crc"*/,&uStack_70,4);
      Aska::LocalKVS::SetBinary(char const*, signed char const*, long)(&uStack_70,param_2,&UNK_02a354cc/*"version"*/,&UNK_02807472/*"1.1"*/,4);
    }
    *(undefined1 *)(param_1 + 0x18) = 1;
    if (piStack_90 != (int *)0x0) {
      do {
        iVar9 = *piStack_90;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piStack_90,0x10);
        if (bVar3) {
          *piStack_90 = iVar9 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar9 + -1 != 0) {
        return;
      }
    }
    if (piStack_98 != (int *)0x0) {
      operator delete[](void*)();
    }
    if (piStack_90 != (int *)0x0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  return;
}

// ==== CGameLocalKVS::VersionUpdate()
// vaddr 0x136c8a0 | ghidra 0x146c8a0 | size 4 | symbol _ZN13CGameLocalKVS13VersionUpdateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN13CGameLocalKVS13VersionUpdateEv(void)

{
  return;
}

// ==== CGameLocalKVS::_SetCipherKey(char const*, Aska::LocalKVS*)
// vaddr 0x136c8a4 | ghidra 0x146c8a4 | size 180 | symbol _ZN13CGameLocalKVS13_SetCipherKeyEPKcPN4Aska8LocalKVSE | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN13CGameLocalKVS13_SetCipherKeyEPKcPN4Aska8LocalKVSE
               (undefined8 param_1,long param_2,undefined8 param_3)

{
  int iVar1;
  undefined8 *puVar2;
  undefined5 *puVar3;
  undefined1 *puVar4;
  undefined1 auStack_70 [8];
  undefined1 auStack_68 [8];
  undefined5 uStack_60;
  undefined3 uStack_5b;
  undefined5 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined1 uStack_30;
  undefined1 auStack_18 [8];
  
  puVar4 = auStack_70;
  if (param_2 != 0) {
    iVar1 = strcmp(&UNK_029dd736/*"1.0"*/,param_2);
    if ((iVar1 != 0) && (iVar1 = strcmp(&UNK_02807472/*"1.1"*/,param_2), iVar1 == 0)) {
      uStack_48 = _UNK_0280747e;
      uStack_50 = _UNK_02807476;
      uStack_38 = _UNK_0280748e;
      uStack_40 = _UNK_02807486;
      uStack_30 = 0;
      uStack_58 = _UNK_0280749f;
      uStack_60 = _UNK_02807497;
      uStack_5b = _UNK_0280749c;
      puVar4 = auStack_18;
      puVar2 = &uStack_50;
      puVar3 = &uStack_60;
      goto code_r0x0146c900;
    }
    puVar4 = auStack_68;
  }
  puVar2 = (undefined8 *)0x0;
  puVar3 = (undefined5 *)0x0;
code_r0x0146c900:
  Aska::LocalKVS::SetCipher(bool, char*, char*)(puVar4,param_3,1,puVar2,puVar3);
  return;
}

// ==== CGameLocalKVS::_SetVersion(char const*, Aska::LocalKVS*)
// vaddr 0x136c958 | ghidra 0x146c958 | size 148 | symbol _ZN13CGameLocalKVS11_SetVersionEPKcPN4Aska8LocalKVSE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN13CGameLocalKVS11_SetVersionEPKcPN4Aska8LocalKVSE
               (undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 uVar1;
  long lVar2;
  undefined1 auStack_30 [8];
  undefined1 auStack_28 [8];
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  uStack_18 = 0;
  uVar1 = strlen(param_2);
  uVar1 = Aska::Hash::CRC(unsigned char const*, unsigned long, unsigned int*)(param_2,uVar1,&uStack_18);
  CGameLocalKVS::_SetCipherKey(char const*, Aska::LocalKVS*)(uVar1,param_2,param_3);
  uStack_14 = uStack_18;
  Aska::LocalKVS::SetBinary(char const*, signed char const*, long)(auStack_28,param_3,&UNK_0280746e/*"crc"*/,&uStack_14,4);
  lVar2 = strlen(param_2);
  Aska::LocalKVS::SetBinary(char const*, signed char const*, long)(auStack_30,param_3,&UNK_02a354cc/*"version"*/,param_2,lVar2 + 1);
  return;
}

// ==== void CGameLocalKVS::Set<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >(char const*, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x136c9ec | ghidra 0x146c9ec | size 112 | symbol _ZN13CGameLocalKVS3SetINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEEEvPKcRKT_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN13CGameLocalKVS3SetINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEEEvPKcRKT_
               (long param_1,undefined8 param_2,byte *param_3)

{
  long lVar1;
  byte *pbVar2;
  undefined8 uVar3;
  undefined1 auStack_a0 [128];
  undefined1 auStack_18 [8];
  
  __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(auStack_a0,0x80,0xffffffffffffffff,param_2);
  pbVar2 = *(byte **)(param_3 + 0x10);
  uVar3 = *(undefined8 *)(param_1 + 8);
  if ((*param_3 & 1) == 0) {
    pbVar2 = param_3 + 1;
  }
  lVar1 = strlen(pbVar2);
  Aska::LocalKVS::SetBinary(char const*, signed char const*, long)(auStack_18,uVar3,auStack_a0,pbVar2,lVar1 + 1);
  return;
}

// ==== std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > CGameLocalKVS::Get<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > >(char const*, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> > const&)
// vaddr 0x136cb08 | ghidra 0x146cb08 | size 588 | symbol _ZN13CGameLocalKVS3GetINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEEET_PKcRKSA_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN13CGameLocalKVS3GetINSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEEEET_PKcRKSA_
               (ulong *param_1,long param_2,undefined8 param_3,ulong *param_4)

{
  int iVar1;
  ulong uVar2;
  char cVar3;
  bool bVar4;
  int *piVar5;
  ulong uVar6;
  byte *pbVar7;
  ulong uVar8;
  undefined1 auStack_d0 [128];
  long lStack_50;
  int *piStack_48;
  long lStack_38;
  
  __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(auStack_d0,0x80,0xffffffffffffffff,param_3);
  lStack_38 = 0;
  Aska::LocalKVS::GetBinary(char const*, long*) const(&lStack_50,*(undefined8 *)(param_2 + 8),auStack_d0,&lStack_38);
  piVar5 = piStack_48;
  if (piStack_48 == (int *)0x0) {
code_r0x0146cb9c:
    if (lStack_50 != 0) {
      operator delete[](void*)();
    }
    if (piStack_48 != (int *)0x0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piStack_48,0x10);
      if (bVar4) {
        *piStack_48 = *piStack_48 + 1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (piStack_48 == (int *)0x0) goto code_r0x0146cb9c;
    do {
      iVar1 = *piStack_48;
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piStack_48,0x10);
      if (bVar4) {
        *piStack_48 = iVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (iVar1 + -1 == 0) goto code_r0x0146cb9c;
  }
  param_1[1] = 0;
  param_1[2] = 0;
  *param_1 = 0;
  if (lStack_38 < 0) {
    if ((*param_4 & 1) == 0) {
      param_1[2] = param_4[2];
      uVar6 = *param_4;
      param_1[1] = param_4[1];
      *param_1 = uVar6;
    }
    else {
      uVar6 = param_4[1];
      uVar2 = param_4[2];
      if (uVar6 < 0x17) {
        pbVar7 = (byte *)((long)param_1 + 1);
        *(byte *)param_1 = (byte)(uVar6 << 1);
        if (uVar6 == 0) {
          *pbVar7 = 0;
          goto joined_r0x0146cc1c;
        }
      }
      else {
        uVar8 = uVar6 + 0x10 & 0xfffffffffffffff0;
        if (uVar8 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
        }
        pbVar7 = (byte *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar8,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
        if (pbVar7 == (byte *)0x0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
        }
        param_1[1] = uVar6;
        param_1[2] = (ulong)pbVar7;
        *param_1 = uVar8 | 1;
      }
      memcpy(pbVar7,uVar2,uVar6);
      pbVar7[uVar6] = 0;
    }
  }
  else {
    uVar6 = strlen(lStack_50);
    if (uVar6 < 0x16 || uVar6 - 0x16 == 0) {
      if (uVar6 != 0) {
        memmove((byte *)((long)param_1 + 1),lStack_50,uVar6);
      }
      *(byte *)((long)param_1 + uVar6 + 1) = 0;
      if ((*param_1 & 1) == 0) {
        *(byte *)param_1 = (byte)(uVar6 << 1);
      }
      else {
        param_1[1] = uVar6;
      }
    }
    else {
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(param_1,0x16,uVar6 - 0x16,0,0,0,uVar6,lStack_50);
    }
  }
joined_r0x0146cc1c:
  if (piVar5 != (int *)0x0) {
    do {
      iVar1 = *piVar5;
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar5,0x10);
      if (bVar4) {
        *piVar5 = iVar1 + -1;
        cVar3 = ExclusiveMonitorsStatus();
      }
    } while (cVar3 != '\0');
    if (iVar1 + -1 != 0) {
      return;
    }
  }
  if (lStack_50 != 0) {
    operator delete[](void*)();
  }
  if (piVar5 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)(piVar5);
  }
  return;
}

// ==== unsigned int CGameLocalKVS::Get<unsigned int>(char const*, unsigned int const&)
// vaddr 0x18efa40 | ghidra 0x19efa40 | size 212 | symbol _ZN13CGameLocalKVS3GetIjEET_PKcRKS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN13CGameLocalKVS3GetIjEET_PKcRKS1_(undefined8 param_1,undefined8 param_2,undefined4 *param_3)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  long lStack_b8;
  undefined1 auStack_b0 [128];
  undefined4 *puStack_30;
  int *piStack_28;
  
  __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(auStack_b0,0x80,0xffffffffffffffff,param_2);
  lStack_b8 = 0;
  uVar4 = CGameLocalKVS::pSubstance() const(param_1);
  Aska::LocalKVS::GetBinary(char const*, long*) const(&puStack_30,uVar4,auStack_b0,&lStack_b8);
  if (puStack_30 == (undefined4 *)0x0) {
    uVar5 = 0;
  }
  else {
    uVar5 = *puStack_30;
  }
  if (piStack_28 != (int *)0x0) {
    do {
      iVar1 = *piStack_28;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_28,0x10);
      if (bVar3) {
        *piStack_28 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 != 1) goto code_r0x019efaf0;
  }
  if (puStack_30 != (undefined4 *)0x0) {
    operator delete[](void*)();
  }
  if (piStack_28 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x019efaf0:
  if (lStack_b8 < 0) {
    uVar5 = *param_3;
  }
  return uVar5;
}

// ==== int CGameLocalKVS::Get<int>(char const*, int const&)
// vaddr 0x1de85f4 | ghidra 0x1ee85f4 | size 212 | symbol _ZN13CGameLocalKVS3GetIiEET_PKcRKS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined4
_ZN13CGameLocalKVS3GetIiEET_PKcRKS1_(undefined8 param_1,undefined8 param_2,undefined4 *param_3)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  long lStack_b8;
  undefined1 auStack_b0 [128];
  undefined4 *puStack_30;
  int *piStack_28;
  
  __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(auStack_b0,0x80,0xffffffffffffffff,param_2);
  lStack_b8 = 0;
  uVar4 = CGameLocalKVS::pSubstance() const(param_1);
  Aska::LocalKVS::GetBinary(char const*, long*) const(&puStack_30,uVar4,auStack_b0,&lStack_b8);
  if (puStack_30 == (undefined4 *)0x0) {
    uVar5 = 0;
  }
  else {
    uVar5 = *puStack_30;
  }
  if (piStack_28 != (int *)0x0) {
    do {
      iVar1 = *piStack_28;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_28,0x10);
      if (bVar3) {
        *piStack_28 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 != 1) goto code_r0x01ee86a4;
  }
  if (puStack_30 != (undefined4 *)0x0) {
    operator delete[](void*)();
  }
  if (piStack_28 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x01ee86a4:
  if (lStack_b8 < 0) {
    uVar5 = *param_3;
  }
  return uVar5;
}

// ==== bool CGameLocalKVS::Get<bool>(char const*, bool const&)
// vaddr 0x1dea294 | ghidra 0x1eea294 | size 228 | symbol _ZN13CGameLocalKVS3GetIbEET_PKcRKS1_ | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN13CGameLocalKVS3GetIbEET_PKcRKS1_(undefined8 param_1,undefined8 param_2,char *param_3)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  bool bVar4;
  undefined8 uVar5;
  long lStack_b8;
  undefined1 auStack_b0 [128];
  char *pcStack_30;
  int *piStack_28;
  
  __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(auStack_b0,0x80,0xffffffffffffffff,param_2);
  lStack_b8 = 0;
  uVar5 = CGameLocalKVS::pSubstance() const(param_1);
  Aska::LocalKVS::GetBinary(char const*, long*) const(&pcStack_30,uVar5,auStack_b0,&lStack_b8);
  if (pcStack_30 == (char *)0x0) {
    bVar4 = false;
  }
  else {
    bVar4 = *pcStack_30 != '\0';
  }
  if (piStack_28 != (int *)0x0) {
    do {
      iVar1 = *piStack_28;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_28,0x10);
      if (bVar3) {
        *piStack_28 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 != 1) goto code_r0x01eea34c;
  }
  if (pcStack_30 != (char *)0x0) {
    operator delete[](void*)();
  }
  if (piStack_28 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x01eea34c:
  if (lStack_b8 < 0) {
    bVar4 = *param_3 != '\0';
  }
  return bVar4;
}

// ==== unsigned long CGameLocalKVS::Get<unsigned long>(char const*, unsigned long const&)
// vaddr 0x1df04f0 | ghidra 0x1ef04f0 | size 212 | symbol _ZN13CGameLocalKVS3GetImEET_PKcRKS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN13CGameLocalKVS3GetImEET_PKcRKS1_(undefined8 param_1,undefined8 param_2,undefined8 *param_3)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  undefined8 uVar4;
  long lStack_b8;
  undefined1 auStack_b0 [128];
  undefined8 *puStack_30;
  int *piStack_28;
  
  __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(auStack_b0,0x80,0xffffffffffffffff,param_2);
  lStack_b8 = 0;
  uVar4 = CGameLocalKVS::pSubstance() const(param_1);
  Aska::LocalKVS::GetBinary(char const*, long*) const(&puStack_30,uVar4,auStack_b0,&lStack_b8);
  if (puStack_30 == (undefined8 *)0x0) {
    uVar4 = 0;
  }
  else {
    uVar4 = *puStack_30;
  }
  if (piStack_28 != (int *)0x0) {
    do {
      iVar1 = *piStack_28;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_28,0x10);
      if (bVar3) {
        *piStack_28 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 != 1) goto code_r0x01ef05a0;
  }
  if (puStack_30 != (undefined8 *)0x0) {
    operator delete[](void*)();
  }
  if (piStack_28 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x01ef05a0:
  if (lStack_b8 < 0) {
    uVar4 = *param_3;
  }
  return uVar4;
}

// ==== Aska::LocalKVS::Init(char const*, bool, char*, char*)
// vaddr 0x1f279e0 | ghidra 0x20279e0 | size 148 | symbol _ZN4Aska8LocalKVS4InitEPKcbPcS3_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8LocalKVS4InitEPKcbPcS3_
               (undefined8 *param_1,undefined8 param_2,char *param_3,uint param_4,undefined8 param_5
               ,undefined8 param_6)

{
  ulong uVar1;
  
  if (((param_3 != (char *)0x0) && (*param_3 != '\0')) &&
     (uVar1 = strlen(param_3), uVar1 < 0x100)) {
    strcpy(param_2,param_3);
    (*(code *)PTR__ZN4Aska8LocalKVS9SetCipherEbPcS1__02c99400)
              (param_1,param_2,param_4 & 1,param_5,param_6);
    return;
  }
  *param_1 = 0xfffffffffffffc43;
  return;
}

// ==== Aska::LocalKVS::SetKVSName(char const*)
// vaddr 0x1f27a98 | ghidra 0x2027a98 | size 88 | symbol _ZN4Aska8LocalKVS10SetKVSNameEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8LocalKVS10SetKVSNameEPKc(undefined8 *param_1,undefined8 param_2,char *param_3)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if (((param_3 == (char *)0x0) || (*param_3 == '\0')) ||
     (uVar1 = strlen(param_3), 0xff < uVar1)) {
    uVar2 = 0xfffffffffffffc43;
  }
  else {
    strcpy(param_2,param_3);
    uVar2 = 0;
  }
  *param_1 = uVar2;
  return;
}

// ==== Aska::LocalKVS::SetCipher(bool, char*, char*)
// vaddr 0x1f27af0 | ghidra 0x2027af0 | size 424 | symbol _ZN4Aska8LocalKVS9SetCipherEbPcS1_ | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska8LocalKVS9SetCipherEbPcS1_
               (long *param_1,long param_2,byte param_3,undefined8 *param_4,ulong *param_5)

{
  uint uVar1;
  ulong uVar2;
  uint uVar3;
  uint uVar4;
  long lVar5;
  ulong uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  byte bStack_70;
  undefined4 uStack_6f;
  undefined3 uStack_6b;
  undefined4 uStack_68;
  undefined1 uStack_64;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined1 uStack_40;
  ulong uStack_38;
  byte abStack_28 [8];
  
  *(byte *)(param_2 + 0x184) = param_3 & 1;
  if ((param_3 & 1) != 0) {
    if ((param_4 == (undefined8 *)0x0) || (param_5 == (ulong *)0x0)) {
      abStack_28[0] = 0;
      abStack_28[1] = 0;
      abStack_28[2] = 0;
      abStack_28[3] = 0;
      abStack_28[4] = 0;
      abStack_28[5] = 0;
      abStack_28[6] = 0;
      abStack_28[7] = 0;
      uStack_38 = 8;
      lVar5 = Aska::Machine::GetUniqueID(unsigned char*, unsigned long*)(abStack_28,&uStack_38);
      *param_1 = lVar5;
      if (lVar5 < 0) {
        lVar5 = Aska::Machine::GetStrayMacAddress(unsigned char*, long)(abStack_28,uStack_38);
        *param_1 = lVar5;
        if (lVar5 < 0) {
          return;
        }
      }
      uStack_58 = _UNK_029701b1;
      uStack_60 = _UNK_029701a9;
      uStack_48 = _UNK_029701c1;
      uStack_50 = _UNK_029701b9;
      uStack_40 = 0;
      uStack_68 = (undefined4)_UNK_029701d2;
      uStack_64 = (undefined1)((uint5)_UNK_029701d2 >> 0x20);
      bStack_70 = (byte)_UNK_029701ca;
      uStack_6f = (undefined4)((uint5)_UNK_029701ca >> 8);
      uStack_6b = _UNK_029701cf;
      uVar3 = strlen(&uStack_60);
      uVar4 = strlen(&bStack_70);
      uStack_60 = CONCAT71(uStack_60._1_7_,abStack_28[0]) ^ 0x22;
      if (uVar3 != 0) {
        uVar6 = 1;
        do {
          uVar2 = 0;
          if (uStack_38 != 0) {
            uVar2 = uVar6 / uStack_38;
          }
          uVar1 = (int)uVar6 + 1;
          *(byte *)((long)&uStack_60 + uVar6) =
               *(byte *)((long)&uStack_60 + uVar6) ^ abStack_28[uVar6 - uVar2 * uStack_38];
          uVar6 = (ulong)uVar1;
        } while (uVar1 <= uVar3);
      }
      if (uVar4 != 0) {
        uVar6 = 1;
        do {
          uVar2 = 0;
          if (uStack_38 != 0) {
            uVar2 = uVar6 / uStack_38;
          }
          uVar3 = (int)uVar6 + 1;
          (&bStack_70)[uVar6] = (&bStack_70)[uVar6] ^ abStack_28[uVar6 - uVar2 * uStack_38];
          uVar6 = (ulong)uVar3;
        } while (uVar3 <= uVar4);
      }
      *(undefined8 *)(param_2 + 0x128) = uStack_48;
      *(undefined8 *)(param_2 + 0x120) = uStack_50;
      *(undefined1 *)(param_2 + 0x181) = 1;
      *(undefined8 *)(param_2 + 0x118) = uStack_58;
      *(ulong *)(param_2 + 0x110) = uStack_60;
      *(undefined4 *)(param_2 + 0x13c) = uStack_68;
      uVar6 = CONCAT35(uStack_6b,CONCAT41(uStack_6f,abStack_28[0])) ^ 0x76;
    }
    else {
      uVar7 = param_4[2];
      *(undefined8 *)(param_2 + 0x128) = param_4[3];
      *(undefined8 *)(param_2 + 0x120) = uVar7;
      uVar8 = param_4[1];
      uVar7 = *param_4;
      *(undefined1 *)(param_2 + 0x181) = 1;
      *(undefined8 *)(param_2 + 0x118) = uVar8;
      *(undefined8 *)(param_2 + 0x110) = uVar7;
      *(int *)(param_2 + 0x13c) = (int)param_5[1];
      uVar6 = *param_5;
    }
    *(ulong *)(param_2 + 0x134) = uVar6;
    *(undefined1 *)(param_2 + 0x180) = 1;
    *(undefined4 *)(param_2 + 0x130) = 0;
  }
  *param_1 = 0;
  return;
}

// ==== Aska::LocalKVS::SetBinary(char const*, signed char const*, long)
// vaddr 0x1f27c98 | ghidra 0x2027c98 | size 336 | symbol _ZN4Aska8LocalKVS9SetBinaryEPKcPKal | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8LocalKVS9SetBinaryEPKcPKal
               (long *param_1,char *param_2,undefined1 *param_3,undefined1 *param_4,long param_5)

{
  char cVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  long lVar4;
  long lStack_550;
  undefined1 *puStack_548;
  undefined1 auStack_540 [1024];
  undefined1 auStack_140 [256];
  undefined1 *puStack_38;
  
  if (((param_3 == (undefined1 *)0x0) || (param_4 == (undefined1 *)0x0)) || (param_5 == 0)) {
    *param_1 = -0x3bd;
    return;
  }
  if (*param_2 == '\0') {
    *param_1 = -0x3bc;
    return;
  }
  puStack_38 = (undefined1 *)0x0;
  puStack_548 = (undefined1 *)0x0;
  puVar2 = param_4;
  puVar3 = param_3;
  if (param_2[0x184] == '\0') {
code_r0x02027d58:
    puStack_38 = puVar3;
    puStack_548 = puVar2;
    Aska::LocalKVS::SetBinaryAndroid(char const*, signed char const*, long)(&lStack_550,param_2,puStack_38,puStack_548,param_5);
    lVar4 = lStack_550;
  }
  else {
    lVar4 = Aska::LocalKVS::CipherEncryptKey(char const*, char**, char const*, unsigned long) const(param_2,param_3,&puStack_38,auStack_140,0x100);
    if (lVar4 < 0) {
      cVar1 = param_2[0x184];
      goto joined_r0x02027dc8;
    }
    param_5 = Aska::LocalKVS::CipherEncryptVal(signed char const*, long, signed char**, signed char const*, unsigned long) const(param_2,param_4,param_5,&puStack_548,auStack_540,0x400);
    lVar4 = param_5;
    puVar2 = puStack_548;
    puVar3 = puStack_38;
    if (-1 < param_5) goto code_r0x02027d58;
  }
  cVar1 = param_2[0x184];
joined_r0x02027dc8:
  if (cVar1 != '\0') {
    if (((puStack_38 != param_3) && (puStack_38 != auStack_140)) &&
       (puStack_38 != (undefined1 *)0x0)) {
      operator delete[](void*)();
      puStack_38 = (undefined1 *)0x0;
    }
    if (((puStack_548 != param_4) && (puStack_548 != auStack_540)) &&
       (puStack_548 != (undefined1 *)0x0)) {
      operator delete[](void*)();
    }
  }
  *param_1 = lVar4;
  return;
}

// ==== Aska::LocalKVS::CipherEncryptKey(char const*, char**, char const*, unsigned long) const
// vaddr 0x1f27de8 | ghidra 0x2027de8 | size 704 | symbol _ZNK4Aska8LocalKVS16CipherEncryptKeyEPKcPPcS2_m | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZNK4Aska8LocalKVS16CipherEncryptKeyEPKcPPcS2_m
                (long param_1,long param_2,long *param_3,long param_4,ulong param_5)

{
  ulong uVar1;
  ulong uVar2;
  bool bVar3;
  ulong uVar4;
  undefined1 *puVar5;
  ulong uVar6;
  ulong uVar7;
  byte *pbVar8;
  ulong uVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  undefined8 *puVar13;
  long lVar14;
  long lVar15;
  ulong uVar16;
  undefined8 *puVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  undefined8 uVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  undefined1 auStack_160 [256];
  
  uVar4 = strlen(param_2);
  if (uVar4 < 0x101) {
    puVar5 = auStack_160;
  }
  else {
    puVar5 = (undefined1 *)operator new[](unsigned long, std::nothrow_t const&)(uVar4,PTR__ZSt7nothrow_02cb9a80);
    if (puVar5 == (undefined1 *)0x0) {
      return 0xfffffffffffffc41;
    }
  }
  uVar19 = *(undefined8 *)
            (PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8 + 8);
  uVar18 = *(undefined8 *)PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8;
  *(undefined4 *)(param_1 + 0x130) = 0;
  *(undefined8 *)(param_1 + 0x108) = uVar19;
  *(undefined8 *)(param_1 + 0x100) = uVar18;
  if ((*(char *)(param_1 + 0x181) == '\0') || (*(char *)(param_1 + 0x180) == '\0')) {
    uVar6 = 0;
    lVar15 = 0;
    uVar4 = 0xfffffffffffffc5b;
    goto joined_r0x02028004;
  }
  if ((long)uVar4 < -0x3f) {
code_r0x0202802c:
    lVar15 = 0;
  }
  else {
    uVar6 = uVar4 + 0x3f;
    if (-1 < (long)uVar4) {
      uVar6 = uVar4;
    }
    lVar15 = 0;
    puVar17 = (undefined8 *)(puVar5 + 0x10);
    puVar13 = (undefined8 *)(param_2 + 0x10);
    uVar16 = ~uVar4;
    do {
      lVar14 = lVar15 * 0x40;
      uVar1 = lVar14 + ~uVar4;
      uVar9 = uVar16;
      if ((long)uVar16 < -0x40) {
        uVar9 = 0xffffffffffffffbf;
      }
      if ((long)uVar1 < -0x40) {
        uVar1 = 0xffffffffffffffbf;
      }
      Aska::Cryption::TChaCha20<false>::CreateKeyStream()(param_1 + 0x100);
      uVar2 = lVar14 + 0x40;
      if ((long)(uVar4 + lVar15 * -0x40) < 0x41) {
        uVar2 = uVar4;
      }
      if (lVar14 < (long)uVar2) {
        if (uVar1 < 0xffffffffffffffe0) {
          uVar7 = ~uVar1 & 0xffffffffffffffe0;
          if (uVar7 != 0) {
            uVar9 = ~uVar9 & 0xffffffffffffffe0;
            lVar14 = lVar14 + uVar7;
            puVar10 = puVar13;
            puVar11 = (undefined8 *)(param_1 + 0x150);
            puVar12 = puVar17;
            do {
              uVar19 = puVar10[-1];
              uVar18 = puVar10[-2];
              uVar21 = puVar10[1];
              uVar20 = *puVar10;
              uVar23 = puVar11[-1];
              uVar22 = puVar11[-2];
              uVar25 = puVar11[1];
              uVar24 = *puVar11;
              uVar9 = uVar9 - 0x20;
              puVar11 = puVar11 + 4;
              puVar10 = puVar10 + 4;
              puVar12[-1] = CONCAT17((byte)((ulong)uVar23 >> 0x38) ^ (byte)((ulong)uVar19 >> 0x38),
                                     CONCAT16((byte)((ulong)uVar23 >> 0x30) ^
                                              (byte)((ulong)uVar19 >> 0x30),
                                              CONCAT15((byte)((ulong)uVar23 >> 0x28) ^
                                                       (byte)((ulong)uVar19 >> 0x28),
                                                       CONCAT14((byte)((ulong)uVar23 >> 0x20) ^
                                                                (byte)((ulong)uVar19 >> 0x20),
                                                                CONCAT13((byte)((ulong)uVar23 >>
                                                                               0x18) ^
                                                                         (byte)((ulong)uVar19 >>
                                                                               0x18),
                                                                         CONCAT12((byte)((ulong)
                                                  uVar23 >> 0x10) ^ (byte)((ulong)uVar19 >> 0x10),
                                                  CONCAT11((byte)((ulong)uVar23 >> 8) ^
                                                           (byte)((ulong)uVar19 >> 8),
                                                           (byte)uVar23 ^ (byte)uVar19)))))));
              puVar12[-2] = CONCAT17((byte)((ulong)uVar22 >> 0x38) ^ (byte)((ulong)uVar18 >> 0x38),
                                     CONCAT16((byte)((ulong)uVar22 >> 0x30) ^
                                              (byte)((ulong)uVar18 >> 0x30),
                                              CONCAT15((byte)((ulong)uVar22 >> 0x28) ^
                                                       (byte)((ulong)uVar18 >> 0x28),
                                                       CONCAT14((byte)((ulong)uVar22 >> 0x20) ^
                                                                (byte)((ulong)uVar18 >> 0x20),
                                                                CONCAT13((byte)((ulong)uVar22 >>
                                                                               0x18) ^
                                                                         (byte)((ulong)uVar18 >>
                                                                               0x18),
                                                                         CONCAT12((byte)((ulong)
                                                  uVar22 >> 0x10) ^ (byte)((ulong)uVar18 >> 0x10),
                                                  CONCAT11((byte)((ulong)uVar22 >> 8) ^
                                                           (byte)((ulong)uVar18 >> 8),
                                                           (byte)uVar22 ^ (byte)uVar18)))))));
              puVar12[1] = CONCAT17((byte)((ulong)uVar25 >> 0x38) ^ (byte)((ulong)uVar21 >> 0x38),
                                    CONCAT16((byte)((ulong)uVar25 >> 0x30) ^
                                             (byte)((ulong)uVar21 >> 0x30),
                                             CONCAT15((byte)((ulong)uVar25 >> 0x28) ^
                                                      (byte)((ulong)uVar21 >> 0x28),
                                                      CONCAT14((byte)((ulong)uVar25 >> 0x20) ^
                                                               (byte)((ulong)uVar21 >> 0x20),
                                                               CONCAT13((byte)((ulong)uVar25 >> 0x18
                                                                              ) ^ (byte)((ulong)
                                                  uVar21 >> 0x18),
                                                  CONCAT12((byte)((ulong)uVar25 >> 0x10) ^
                                                           (byte)((ulong)uVar21 >> 0x10),
                                                           CONCAT11((byte)((ulong)uVar25 >> 8) ^
                                                                    (byte)((ulong)uVar21 >> 8),
                                                                    (byte)uVar25 ^ (byte)uVar21)))))
                                            ));
              *puVar12 = CONCAT17((byte)((ulong)uVar24 >> 0x38) ^ (byte)((ulong)uVar20 >> 0x38),
                                  CONCAT16((byte)((ulong)uVar24 >> 0x30) ^
                                           (byte)((ulong)uVar20 >> 0x30),
                                           CONCAT15((byte)((ulong)uVar24 >> 0x28) ^
                                                    (byte)((ulong)uVar20 >> 0x28),
                                                    CONCAT14((byte)((ulong)uVar24 >> 0x20) ^
                                                             (byte)((ulong)uVar20 >> 0x20),
                                                             CONCAT13((byte)((ulong)uVar24 >> 0x18)
                                                                      ^ (byte)((ulong)uVar20 >> 0x18
                                                                              ),
                                                                      CONCAT12((byte)((ulong)uVar24
                                                                                     >> 0x10) ^
                                                                               (byte)((ulong)uVar20
                                                                                     >> 0x10),
                                                                               CONCAT11((byte)((
                                                  ulong)uVar24 >> 8) ^ (byte)((ulong)uVar20 >> 8),
                                                  (byte)uVar24 ^ (byte)uVar20)))))));
              puVar12 = puVar12 + 4;
            } while (uVar9 != 0);
            if (uVar7 == ~uVar1) goto code_r0x02027f7c;
          }
        }
        else {
          uVar7 = 0;
        }
        pbVar8 = (byte *)(param_1 + 0x140 + uVar7);
        do {
          puVar5[lVar14] = *pbVar8 ^ *(byte *)(param_2 + lVar14);
          lVar14 = lVar14 + 1;
          pbVar8 = pbVar8 + 1;
        } while (lVar14 < (long)uVar2);
      }
code_r0x02027f7c:
      uVar16 = uVar16 + 0x40;
      puVar17 = puVar17 + 8;
      bVar3 = lVar15 != (long)uVar6 >> 6;
      lVar15 = lVar15 + 1;
      puVar13 = puVar13 + 8;
      *(int *)(param_1 + 0x130) = *(int *)(param_1 + 0x130) + 1;
    } while (bVar3);
    if ((long)uVar4 < 0) goto code_r0x0202802c;
    uVar6 = Aska::Encode::Base64EncodeGetRequiredLength(unsigned long)(uVar4);
    lVar15 = param_4;
    if ((uVar6 <= param_5) ||
       (lVar15 = operator new[](unsigned long, std::nothrow_t const&)(uVar6,PTR__ZSt7nothrow_02cb9a80), lVar15 != 0)) {
      uVar6 = Aska::Encode::Base64Encode(signed char const*, unsigned long, signed char*, unsigned long)(puVar5,uVar4,lVar15,uVar6);
      if (uVar6 == 0) {
        uVar4 = 0xfffffffffffffc48;
      }
      else {
        uVar4 = 0;
        *param_3 = lVar15;
      }
      goto joined_r0x02028004;
    }
    uVar4 = 0xfffffffffffffc41;
  }
  uVar6 = 0;
joined_r0x02028004:
  if ((puVar5 != (undefined1 *)0x0) && (puVar5 != auStack_160)) {
    operator delete[](void*)(puVar5);
  }
  if ((((long)uVar4 < 0) && (uVar6 = uVar4, lVar15 != 0)) && (lVar15 != param_4)) {
    operator delete[](void*)(lVar15);
  }
  return uVar6;
}

// ==== Aska::LocalKVS::CipherEncryptVal(signed char const*, long, signed char**, signed char const*, unsigned long) const
// vaddr 0x1f280a8 | ghidra 0x20280a8 | size 640 | symbol _ZNK4Aska8LocalKVS16CipherEncryptValEPKalPPaS2_m | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZNK4Aska8LocalKVS16CipherEncryptValEPKalPPaS2_m
                (long param_1,long param_2,ulong param_3,long *param_4,long param_5,ulong param_6)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  bool bVar4;
  long lVar5;
  ulong uVar6;
  byte *pbVar7;
  ulong uVar8;
  ulong uVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  ulong uVar12;
  undefined8 *puVar13;
  undefined8 *puVar14;
  long lVar15;
  long lVar16;
  ulong uVar17;
  undefined8 *puVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  undefined8 uVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  undefined8 uVar26;
  
  lVar5 = param_5;
  if ((param_6 < param_3) &&
     (lVar5 = operator new[](unsigned long, std::nothrow_t const&)(param_3,PTR__ZSt7nothrow_02cb9a80), lVar5 == 0)) {
    param_3 = 0xfffffffffffffc41;
  }
  else {
    uVar20 = *(undefined8 *)
              (PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8 + 8);
    uVar19 = *(undefined8 *)PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8
    ;
    *(undefined4 *)(param_1 + 0x130) = 0;
    *(undefined8 *)(param_1 + 0x108) = uVar20;
    *(undefined8 *)(param_1 + 0x100) = uVar19;
    if (*(char *)(param_1 + 0x181) == '\0') {
      param_3 = 0xfffffffffffffc5b;
    }
    else if (*(char *)(param_1 + 0x180) == '\0') {
      param_3 = 0xfffffffffffffc5b;
    }
    else if (-0x40 < (long)param_3) {
      uVar2 = param_3 + 0x3f;
      if (-1 < (long)param_3) {
        uVar2 = param_3;
      }
      lVar16 = 0;
      puVar14 = (undefined8 *)(lVar5 + 0x10);
      puVar18 = (undefined8 *)(param_2 + 0x10);
      uVar17 = ~param_3;
      do {
        lVar15 = lVar16 * 0x40;
        uVar1 = lVar15 + ~param_3;
        uVar9 = uVar17;
        if ((long)uVar17 < -0x40) {
          uVar9 = 0xffffffffffffffbf;
        }
        if ((long)uVar1 < -0x40) {
          uVar1 = 0xffffffffffffffbf;
        }
        Aska::Cryption::TChaCha20<false>::CreateKeyStream()(param_1 + 0x100);
        uVar3 = lVar15 + 0x40;
        if ((long)(param_3 + lVar16 * -0x40) < 0x41) {
          uVar3 = param_3;
        }
        if (lVar15 < (long)uVar3) {
          if (uVar1 < 0xffffffffffffffe0) {
            uVar8 = ~uVar1 & 0xffffffffffffffe0;
            if (uVar8 == 0) goto code_r0x0202826c;
            uVar12 = (lVar5 + lVar15 + -1) - uVar1;
            uVar6 = 0;
            if (((param_2 + lVar15 + -1) - uVar1 <= (ulong)(lVar5 + lVar15) ||
                 uVar12 <= (ulong)(param_2 + lVar15)) &&
               ((param_1 + 0x13f) - uVar1 <= (ulong)(lVar5 + lVar15) || uVar12 <= param_1 + 0x140U))
            {
              uVar9 = ~uVar9 & 0xffffffffffffffe0;
              lVar15 = lVar15 + uVar8;
              puVar10 = puVar18;
              puVar11 = (undefined8 *)(param_1 + 0x150);
              puVar13 = puVar14;
              do {
                uVar20 = puVar10[-1];
                uVar19 = puVar10[-2];
                uVar22 = puVar10[1];
                uVar21 = *puVar10;
                uVar24 = puVar11[-1];
                uVar23 = puVar11[-2];
                uVar26 = puVar11[1];
                uVar25 = *puVar11;
                uVar9 = uVar9 - 0x20;
                puVar11 = puVar11 + 4;
                puVar10 = puVar10 + 4;
                puVar13[-1] = CONCAT17((byte)((ulong)uVar24 >> 0x38) ^ (byte)((ulong)uVar20 >> 0x38)
                                       ,CONCAT16((byte)((ulong)uVar24 >> 0x30) ^
                                                 (byte)((ulong)uVar20 >> 0x30),
                                                 CONCAT15((byte)((ulong)uVar24 >> 0x28) ^
                                                          (byte)((ulong)uVar20 >> 0x28),
                                                          CONCAT14((byte)((ulong)uVar24 >> 0x20) ^
                                                                   (byte)((ulong)uVar20 >> 0x20),
                                                                   CONCAT13((byte)((ulong)uVar24 >>
                                                                                  0x18) ^
                                                                            (byte)((ulong)uVar20 >>
                                                                                  0x18),
                                                                            CONCAT12((byte)((ulong)
                                                  uVar24 >> 0x10) ^ (byte)((ulong)uVar20 >> 0x10),
                                                  CONCAT11((byte)((ulong)uVar24 >> 8) ^
                                                           (byte)((ulong)uVar20 >> 8),
                                                           (byte)uVar24 ^ (byte)uVar20)))))));
                puVar13[-2] = CONCAT17((byte)((ulong)uVar23 >> 0x38) ^ (byte)((ulong)uVar19 >> 0x38)
                                       ,CONCAT16((byte)((ulong)uVar23 >> 0x30) ^
                                                 (byte)((ulong)uVar19 >> 0x30),
                                                 CONCAT15((byte)((ulong)uVar23 >> 0x28) ^
                                                          (byte)((ulong)uVar19 >> 0x28),
                                                          CONCAT14((byte)((ulong)uVar23 >> 0x20) ^
                                                                   (byte)((ulong)uVar19 >> 0x20),
                                                                   CONCAT13((byte)((ulong)uVar23 >>
                                                                                  0x18) ^
                                                                            (byte)((ulong)uVar19 >>
                                                                                  0x18),
                                                                            CONCAT12((byte)((ulong)
                                                  uVar23 >> 0x10) ^ (byte)((ulong)uVar19 >> 0x10),
                                                  CONCAT11((byte)((ulong)uVar23 >> 8) ^
                                                           (byte)((ulong)uVar19 >> 8),
                                                           (byte)uVar23 ^ (byte)uVar19)))))));
                puVar13[1] = CONCAT17((byte)((ulong)uVar26 >> 0x38) ^ (byte)((ulong)uVar22 >> 0x38),
                                      CONCAT16((byte)((ulong)uVar26 >> 0x30) ^
                                               (byte)((ulong)uVar22 >> 0x30),
                                               CONCAT15((byte)((ulong)uVar26 >> 0x28) ^
                                                        (byte)((ulong)uVar22 >> 0x28),
                                                        CONCAT14((byte)((ulong)uVar26 >> 0x20) ^
                                                                 (byte)((ulong)uVar22 >> 0x20),
                                                                 CONCAT13((byte)((ulong)uVar26 >>
                                                                                0x18) ^
                                                                          (byte)((ulong)uVar22 >>
                                                                                0x18),
                                                                          CONCAT12((byte)((ulong)
                                                  uVar26 >> 0x10) ^ (byte)((ulong)uVar22 >> 0x10),
                                                  CONCAT11((byte)((ulong)uVar26 >> 8) ^
                                                           (byte)((ulong)uVar22 >> 8),
                                                           (byte)uVar26 ^ (byte)uVar22)))))));
                *puVar13 = CONCAT17((byte)((ulong)uVar25 >> 0x38) ^ (byte)((ulong)uVar21 >> 0x38),
                                    CONCAT16((byte)((ulong)uVar25 >> 0x30) ^
                                             (byte)((ulong)uVar21 >> 0x30),
                                             CONCAT15((byte)((ulong)uVar25 >> 0x28) ^
                                                      (byte)((ulong)uVar21 >> 0x28),
                                                      CONCAT14((byte)((ulong)uVar25 >> 0x20) ^
                                                               (byte)((ulong)uVar21 >> 0x20),
                                                               CONCAT13((byte)((ulong)uVar25 >> 0x18
                                                                              ) ^ (byte)((ulong)
                                                  uVar21 >> 0x18),
                                                  CONCAT12((byte)((ulong)uVar25 >> 0x10) ^
                                                           (byte)((ulong)uVar21 >> 0x10),
                                                           CONCAT11((byte)((ulong)uVar25 >> 8) ^
                                                                    (byte)((ulong)uVar21 >> 8),
                                                                    (byte)uVar25 ^ (byte)uVar21)))))
                                            ));
                puVar13 = puVar13 + 4;
              } while (uVar9 != 0);
              uVar6 = uVar8;
              if (uVar8 == ~uVar1) goto code_r0x02028294;
            }
          }
          else {
code_r0x0202826c:
            uVar6 = 0;
          }
          pbVar7 = (byte *)(param_1 + 0x140U + uVar6);
          do {
            *(byte *)(lVar5 + lVar15) = *pbVar7 ^ *(byte *)(param_2 + lVar15);
            lVar15 = lVar15 + 1;
            pbVar7 = pbVar7 + 1;
          } while (lVar15 < (long)uVar3);
        }
code_r0x02028294:
        uVar17 = uVar17 + 0x40;
        puVar14 = puVar14 + 8;
        bVar4 = lVar16 != (long)uVar2 >> 6;
        lVar16 = lVar16 + 1;
        puVar18 = puVar18 + 8;
        *(int *)(param_1 + 0x130) = *(int *)(param_1 + 0x130) + 1;
      } while (bVar4);
      if (-1 < (long)param_3) {
        *param_4 = lVar5;
        return param_3;
      }
    }
    if ((lVar5 != 0) && (lVar5 != param_5)) {
      operator delete[](void*)(lVar5);
    }
  }
  return param_3;
}

// ==== Aska::LocalKVS::SetBinaryAndroid(char const*, signed char const*, long)
// vaddr 0x1f28328 | ghidra 0x2028328 | size 564 | symbol _ZN4Aska8LocalKVS16SetBinaryAndroidEPKcPKal | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8LocalKVS16SetBinaryAndroidEPKcPKal
               (long *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined4 param_5)

{
  ulong uVar1;
  char cVar2;
  ulong uVar3;
  undefined *puVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  char *pcVar12;
  long lVar13;
  long *plVar14;
  long lVar15;
  undefined8 uVar16;
  long lStack_60;
  char acStack_58 [8];
  long *plStack_48;
  
  puVar4 = PTR__ZN4Aska6Global13m_pAndroidAppE_02cc2688;
  plVar14 = *(long **)(*(long *)(*(long *)PTR__ZN4Aska6Global13m_pAndroidAppE_02cc2688 + 0x18) + 8);
  plStack_48 = (long *)0x0;
  Aska::AndroidUtil::AttachCurrentThread(_JavaVM*, _JNIEnv**, void*)(plVar14,&plStack_48,0);
  uVar16 = *(undefined8 *)(*(long *)(*(long *)puVar4 + 0x18) + 0x18);
  uVar5 = (**(code **)(*plStack_48 + 0x538))(plStack_48,param_2);
  uVar6 = (**(code **)(*plStack_48 + 0x538))(plStack_48,param_3);
  uVar7 = (**(code **)(*plStack_48 + 0x580))(plStack_48,param_5);
  (**(code **)(*plStack_48 + 0x680))(plStack_48,uVar7,0,param_5,param_4);
  Aska::AndroidUtil::CallMethod(_JNIEnv*, jvalue*, _jobject*, char const*, char const*, ...)(&lStack_60,plStack_48,acStack_58,uVar16,&UNK_029701d7/*"SetSharedPreferences"*/,&UNK_029701ec/*"(Ljava/lang/String;Ljava/lang/String;[B)Ljava/lang/Boolean;"*/,uVar5,uVar6,
                  uVar7);
  *param_1 = lStack_60;
  (**(code **)(*plStack_48 + 0xb8))(plStack_48,uVar5);
  (**(code **)(*plStack_48 + 0xb8))(plStack_48,uVar6);
  (**(code **)(*plStack_48 + 0xb8))(plStack_48,uVar7);
  if ((-1 < lStack_60) && (acStack_58[0] == '\0')) {
    *param_1 = -1;
  }
  lVar15 = *(long *)PTR__ZN4Aska11AndroidUtil19m_pAttachThreadListE_02cbb5c8;
  if (lVar15 != 0) {
    uVar8 = Aska::Thread::GetCurrentID()();
    uVar9 = *(ulong *)(lVar15 + 0x28);
    if (uVar9 != 0) {
      uVar10 = ~uVar8 + uVar8 * 0x200000;
      uVar10 = (uVar10 ^ uVar10 >> 0x18) * 0x109;
      uVar11 = (uVar10 ^ uVar10 >> 0xe) * 0x15;
      uVar10 = 0;
      do {
        uVar1 = (uVar11 ^ uVar11 >> 0x1c) * 0x80000001 + uVar10;
        uVar3 = 0;
        if (uVar9 != 0) {
          uVar3 = uVar1 / uVar9;
        }
        lVar13 = uVar1 - uVar3 * uVar9;
        pcVar12 = (char *)(*(long *)(lVar15 + 0x20) + lVar13 * 0x18);
        cVar2 = *pcVar12;
        if (cVar2 == '\x01') {
          if (*(ulong *)(*(long *)(lVar15 + 0x20) + lVar13 * 0x18 + 8) == uVar8) {
            *(int *)(lVar15 + 0x10) = *(int *)(lVar15 + 0x10) + -1;
            *(int *)(lVar15 + 0x14) = *(int *)(lVar15 + 0x14) + 1;
            *pcVar12 = '\x02';
            break;
          }
        }
        else if (cVar2 == '\0') break;
        uVar10 = uVar10 + 1;
      } while (uVar10 < uVar9);
    }
  }
  (**(code **)(*plVar14 + 0x28))(plVar14);
  return;
}

// ==== Aska::LocalKVS::GetBinary(char const*, long*) const
// vaddr 0x1f2855c | ghidra 0x202855c | size 756 | symbol _ZNK4Aska8LocalKVS9GetBinaryEPKcPl | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska8LocalKVS9GetBinaryEPKcPl
               (long *param_1,char *param_2,undefined1 *param_3,ulong *param_4)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  undefined1 *puVar4;
  ulong uVar5;
  ulong uVar6;
  int *piVar7;
  long lStack_180;
  int *piStack_178;
  ulong uStack_170;
  long lStack_168;
  long lStack_160;
  int *piStack_158;
  undefined1 auStack_150 [256];
  undefined1 *puStack_48;
  
  if (param_3 == (undefined1 *)0x0) {
    if (param_4 == (ulong *)0x0) goto code_r0x020285e4;
    uVar5 = 0xfffffffffffffc43;
  }
  else {
    if (*param_2 != '\0') {
      puStack_48 = (undefined1 *)0x0;
      lStack_160 = 0;
      piStack_158 = (int *)0x0;
      lStack_168 = 0;
      puVar4 = param_3;
      if ((param_2[0x184] == '\0') ||
         (uVar5 = Aska::LocalKVS::CipherEncryptKey(char const*, char**, char const*, unsigned long) const(param_2,param_3,&puStack_48,auStack_150,0x100),
         puVar4 = puStack_48, -1 < (long)uVar5)) {
        puStack_48 = puVar4;
        Aska::LocalKVS::GetBinaryAndroid(char const*, long*) const(&lStack_180,param_2,puStack_48,&uStack_170);
        if (lStack_180 == 0) {
          piVar7 = (int *)0x0;
code_r0x02028630:
          if (piStack_178 == (int *)0x0) goto code_r0x02028660;
          do {
            iVar1 = *piStack_178;
            cVar2 = '\x01';
            bVar3 = (bool)ExclusiveMonitorPass(piStack_178,0x10);
            if (bVar3) {
              *piStack_178 = iVar1 + -1;
              cVar2 = ExclusiveMonitorsStatus();
            }
          } while (cVar2 != '\0');
          if (iVar1 + -1 == 0) goto code_r0x02028660;
        }
        else {
          lStack_168 = lStack_180;
          piVar7 = piStack_178;
          if (piStack_178 != (int *)0x0) {
            do {
              cVar2 = '\x01';
              bVar3 = (bool)ExclusiveMonitorPass(piStack_178,0x10);
              if (bVar3) {
                *piStack_178 = *piStack_178 + 1;
                cVar2 = ExclusiveMonitorsStatus();
              }
            } while (cVar2 != '\0');
            goto code_r0x02028630;
          }
code_r0x02028660:
          if (lStack_180 != 0) {
            operator delete[](void*)();
          }
          if (piStack_178 != (int *)0x0) {
            Aska::TSharedPointerCode::DeleteCounter(int*)();
          }
        }
        piStack_178 = (int *)0x0;
        if (lStack_168 == 0) goto code_r0x020286b4;
        if (param_2[0x184] == '\0') {
          if (lStack_168 != lStack_160) {
            if (piStack_158 == (int *)0x0) {
code_r0x020286f0:
              if (lStack_160 != 0) {
                operator delete[](void*)();
              }
              if (piStack_158 != (int *)0x0) {
                Aska::TSharedPointerCode::DeleteCounter(int*)();
              }
            }
            else {
              do {
                iVar1 = *piStack_158;
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piStack_158,0x10);
                if (bVar3) {
                  *piStack_158 = iVar1 + -1;
                  cVar2 = ExclusiveMonitorsStatus();
                }
              } while (cVar2 != '\0');
              if (iVar1 + -1 == 0) goto code_r0x020286f0;
            }
            lStack_160 = lStack_168;
            piStack_158 = piVar7;
            if (piVar7 != (int *)0x0) {
              do {
                cVar2 = '\x01';
                bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
                if (bVar3) {
                  *piVar7 = *piVar7 + 1;
                  cVar2 = ExclusiveMonitorsStatus();
                }
              } while (cVar2 != '\0');
            }
          }
          cVar2 = param_2[0x184];
          uVar5 = 0;
          uVar6 = uStack_170;
        }
        else {
          uVar6 = Aska::LocalKVS::CipherDecryptVal(signed char const*, long, Aska::TSharedArray<signed char>&) const(param_2,lStack_168,uStack_170,&lStack_160);
          cVar2 = param_2[0x184];
          uVar5 = uVar6 & (long)uVar6 >> 0x3f;
        }
      }
      else {
        piVar7 = (int *)0x0;
        uStack_170 = uVar5;
code_r0x020286b4:
        uVar6 = 0;
        cVar2 = param_2[0x184];
        uVar5 = uStack_170;
      }
      if ((((cVar2 != '\0') && (puStack_48 != param_3)) && (puStack_48 != auStack_150)) &&
         (puStack_48 != (undefined1 *)0x0)) {
        operator delete[](void*)();
        puStack_48 = (undefined1 *)0x0;
      }
      if ((long)uVar5 < 0) {
        if (param_4 != (ulong *)0x0) {
          *param_4 = uVar5;
        }
        if (lStack_160 != 0) {
          if (piStack_158 == (int *)0x0) {
code_r0x02028798:
            operator delete[](void*)();
code_r0x0202879c:
            if (piStack_158 != (int *)0x0) {
              Aska::TSharedPointerCode::DeleteCounter(int*)();
            }
          }
          else {
            do {
              iVar1 = *piStack_158;
              cVar2 = '\x01';
              bVar3 = (bool)ExclusiveMonitorPass(piStack_158,0x10);
              if (bVar3) {
                *piStack_158 = iVar1 + -1;
                cVar2 = ExclusiveMonitorsStatus();
              }
            } while (cVar2 != '\0');
            if (iVar1 + -1 == 0) {
              if (lStack_160 != 0) goto code_r0x02028798;
              goto code_r0x0202879c;
            }
          }
          lStack_160 = 0;
          piStack_158 = (int *)0x0;
        }
      }
      else if (param_4 != (ulong *)0x0) {
        *param_4 = uVar6;
      }
      *param_1 = lStack_160;
      param_1[1] = (long)piStack_158;
      if (piStack_158 != (int *)0x0) {
        do {
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piStack_158,0x10);
          if (bVar3) {
            *piStack_158 = *piStack_158 + 1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
      }
      if (piVar7 != (int *)0x0) {
        do {
          iVar1 = *piVar7;
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piVar7,0x10);
          if (bVar3) {
            *piVar7 = iVar1 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        if (iVar1 + -1 != 0) goto code_r0x020287f8;
      }
      if (lStack_168 != 0) {
        operator delete[](void*)();
      }
      if (piVar7 != (int *)0x0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)(piVar7);
      }
code_r0x020287f8:
      lStack_168 = 0;
      if (piStack_158 != (int *)0x0) {
        do {
          iVar1 = *piStack_158;
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piStack_158,0x10);
          if (bVar3) {
            *piStack_158 = iVar1 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        if (iVar1 + -1 != 0) {
          return;
        }
      }
      if (lStack_160 != 0) {
        operator delete[](void*)();
      }
      if (piStack_158 == (int *)0x0) {
        return;
      }
      Aska::TSharedPointerCode::DeleteCounter(int*)();
      return;
    }
    if (param_4 == (ulong *)0x0) goto code_r0x020285e4;
    uVar5 = 0xfffffffffffffc44;
  }
  *param_4 = uVar5;
code_r0x020285e4:
  *param_1 = 0;
  param_1[1] = 0;
  return;
}

// ==== Aska::LocalKVS::GetBinaryAndroid(char const*, long*) const
// vaddr 0x1f28850 | ghidra 0x2028850 | size 764 | symbol _ZNK4Aska8LocalKVS16GetBinaryAndroidEPKcPl | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska8LocalKVS16GetBinaryAndroidEPKcPl
               (long *param_1,undefined8 param_2,undefined8 param_3,long *param_4)

{
  ulong uVar1;
  char cVar2;
  bool bVar3;
  ulong uVar4;
  undefined *puVar5;
  int iVar6;
  undefined8 uVar7;
  long lVar8;
  long lVar9;
  int *piVar10;
  long lVar11;
  ulong uVar12;
  ulong uVar13;
  ulong uVar14;
  ulong uVar15;
  char *pcVar16;
  long *plVar17;
  undefined8 uVar18;
  long lVar19;
  undefined1 uStack_60;
  int7 iStack_5f;
  long lStack_58;
  long *plStack_48;
  
  puVar5 = PTR__ZN4Aska6Global13m_pAndroidAppE_02cc2688;
  *param_1 = 0;
  param_1[1] = 0;
  plVar17 = *(long **)(*(long *)(*(long *)puVar5 + 0x18) + 8);
  plStack_48 = (long *)0x0;
  Aska::AndroidUtil::AttachCurrentThread(_JavaVM*, _JNIEnv**, void*)(plVar17,&plStack_48,0);
  uVar18 = *(undefined8 *)(*(long *)(*(long *)puVar5 + 0x18) + 0x18);
  uVar7 = (**(code **)(*plStack_48 + 0x538))(plStack_48,param_2);
  lVar8 = (**(code **)(*plStack_48 + 0x538))(plStack_48,param_3);
  Aska::AndroidUtil::CallMethod(_JNIEnv*, jvalue*, _jobject*, char const*, char const*, ...)(&uStack_60,plStack_48,&lStack_58,uVar18,&UNK_02970228/*"GetSharedPreferences"*/,&UNK_0297023d/*"(Ljava/lang/String;Ljava/lang/String;)[B"*/,uVar7,lVar8);
  lVar19 = CONCAT71(iStack_5f,uStack_60);
  (**(code **)(*plStack_48 + 0xb8))(plStack_48,uVar7);
  (**(code **)(*plStack_48 + 0xb8))(plStack_48,lVar8);
  if (-1 < iStack_5f) {
    if (lStack_58 == 0) {
      lVar19 = -0x3a4;
    }
    else {
      iVar6 = (**(code **)(*plStack_48 + 0x558))(plStack_48,lStack_58);
      lVar8 = (long)iVar6;
      if (iVar6 == 0) {
        lVar19 = -0x3a4;
      }
      else {
        lVar9 = operator new[](unsigned long, std::nothrow_t const&)(lVar8,PTR__ZSt7nothrow_02cb9a80);
        if (lVar9 != 0) {
          *param_1 = 0;
          piVar10 = (int *)Aska::TSharedPointerCode::CreateCounter(int)(0);
          param_1[1] = (long)piVar10;
          if (piVar10 != (int *)0x0) {
            *param_1 = lVar9;
            do {
              cVar2 = '\x01';
              bVar3 = (bool)ExclusiveMonitorPass(piVar10,0x10);
              if (bVar3) {
                *piVar10 = *piVar10 + 1;
                cVar2 = ExclusiveMonitorsStatus();
              }
            } while (cVar2 != '\0');
            lVar9 = *param_1;
            if (lVar9 != 0) {
              uStack_60 = 0;
              lVar11 = (**(code **)(*plStack_48 + 0x6f0))(plStack_48,lStack_58,&uStack_60);
              if (lVar11 != 0) {
                memcpy(lVar9,lVar11,lVar8);
                (**(code **)(*plStack_48 + 0x6f8))(plStack_48,lStack_58,lVar11,uStack_60);
                goto code_r0x02028a1c;
              }
            }
          }
        }
        lVar19 = -0x3bf;
      }
    }
  }
code_r0x02028a1c:
  lVar9 = *(long *)PTR__ZN4Aska11AndroidUtil19m_pAttachThreadListE_02cbb5c8;
  if (lVar9 != 0) {
    uVar12 = Aska::Thread::GetCurrentID()();
    uVar13 = *(ulong *)(lVar9 + 0x28);
    if (uVar13 != 0) {
      uVar14 = ~uVar12 + uVar12 * 0x200000;
      uVar14 = (uVar14 ^ uVar14 >> 0x18) * 0x109;
      uVar15 = (uVar14 ^ uVar14 >> 0xe) * 0x15;
      uVar14 = 0;
      do {
        uVar1 = (uVar15 ^ uVar15 >> 0x1c) * 0x80000001 + uVar14;
        uVar4 = 0;
        if (uVar13 != 0) {
          uVar4 = uVar1 / uVar13;
        }
        lVar11 = uVar1 - uVar4 * uVar13;
        pcVar16 = (char *)(*(long *)(lVar9 + 0x20) + lVar11 * 0x18);
        cVar2 = *pcVar16;
        if (cVar2 == '\x01') {
          if (*(ulong *)(*(long *)(lVar9 + 0x20) + lVar11 * 0x18 + 8) == uVar12) {
            *(int *)(lVar9 + 0x10) = *(int *)(lVar9 + 0x10) + -1;
            *(int *)(lVar9 + 0x14) = *(int *)(lVar9 + 0x14) + 1;
            *pcVar16 = '\x02';
            break;
          }
        }
        else if (cVar2 == '\0') break;
        uVar14 = uVar14 + 1;
      } while (uVar14 < uVar13);
    }
  }
  (**(code **)(*plVar17 + 0x28))(plVar17);
  if (-1 < lVar19) {
    if (param_4 == (long *)0x0) {
      return;
    }
    *param_4 = lVar8;
    return;
  }
  if (param_4 != (long *)0x0) {
    *param_4 = lVar19;
  }
  if (*param_1 == 0) {
    return;
  }
  piVar10 = (int *)param_1[1];
  if (piVar10 == (int *)0x0) {
code_r0x02028b1c:
    operator delete[](void*)();
  }
  else {
    do {
      iVar6 = *piVar10;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar10,0x10);
      if (bVar3) {
        *piVar10 = iVar6 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar6 + -1 != 0) goto code_r0x02028b2c;
    if (*param_1 != 0) goto code_r0x02028b1c;
  }
  if (param_1[1] != 0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x02028b2c:
  *param_1 = 0;
  param_1[1] = 0;
  return;
}

// ==== Aska::LocalKVS::CipherDecryptVal(signed char const*, long, Aska::TSharedArray<signed char>&) const
// vaddr 0x1f28b4c | ghidra 0x2028b4c | size 832 | symbol _ZNK4Aska8LocalKVS16CipherDecryptValEPKalRNS_12TSharedArrayIaEE | lib libSOA-3.7.0.so | 2026-10-04
ulong _ZNK4Aska8LocalKVS16CipherDecryptValEPKalRNS_12TSharedArrayIaEE
                (long param_1,long param_2,ulong param_3,long *param_4)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  int iVar4;
  char cVar5;
  bool bVar6;
  int *piVar7;
  int *piVar8;
  ulong uVar9;
  byte *pbVar10;
  ulong uVar11;
  ulong uVar12;
  undefined8 *puVar13;
  undefined8 *puVar14;
  ulong uVar15;
  undefined8 *puVar16;
  undefined8 *puVar17;
  long lVar18;
  ulong uVar19;
  long lVar20;
  undefined8 *puVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  undefined8 uVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  undefined8 uVar29;
  long lStack_68;
  
  lStack_68 = operator new[](unsigned long, std::nothrow_t const&)(param_3,PTR__ZSt7nothrow_02cb9a80);
  if (lStack_68 == 0) {
    piVar7 = (int *)0x0;
code_r0x02028df8:
    lStack_68 = 0;
    param_3 = 0xfffffffffffffc41;
joined_r0x02028e44:
    if (piVar7 == (int *)0x0) {
      bVar6 = true;
      goto joined_r0x02028e50;
    }
  }
  else {
    piVar7 = (int *)Aska::TSharedPointerCode::CreateCounter(int)(0);
    if (piVar7 == (int *)0x0) goto code_r0x02028df8;
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar6) {
        *piVar7 = *piVar7 + 1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
    if (lStack_68 == 0) {
      param_3 = 0xfffffffffffffc41;
      goto joined_r0x02028e44;
    }
    uVar23 = *(undefined8 *)
              (PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8 + 8);
    uVar22 = *(undefined8 *)PTR__ZZN4Aska8Cryption9TChaCha20ILb0EE11ResetStatusEvE8constant_02cc10e8
    ;
    *(undefined4 *)(param_1 + 0x130) = 0;
    *(undefined8 *)(param_1 + 0x108) = uVar23;
    *(undefined8 *)(param_1 + 0x100) = uVar22;
    if ((*(char *)(param_1 + 0x181) == '\0') || (*(char *)(param_1 + 0x180) == '\0')) {
      param_3 = 0xfffffffffffffc5b;
      goto joined_r0x02028e44;
    }
    if ((long)param_3 < -0x3f) goto joined_r0x02028e44;
    uVar2 = param_3 + 0x3f;
    if (-1 < (long)param_3) {
      uVar2 = param_3;
    }
    lVar18 = 0;
    puVar21 = (undefined8 *)(lStack_68 + 0x10);
    puVar17 = (undefined8 *)(param_2 + 0x10);
    uVar19 = ~param_3;
    do {
      lVar20 = lVar18 * 0x40;
      uVar1 = lVar20 + ~param_3;
      uVar12 = uVar19;
      if ((long)uVar19 < -0x40) {
        uVar12 = 0xffffffffffffffbf;
      }
      if ((long)uVar1 < -0x40) {
        uVar1 = 0xffffffffffffffbf;
      }
      Aska::Cryption::TChaCha20<false>::CreateKeyStream()(param_1 + 0x100);
      uVar3 = lVar20 + 0x40;
      if ((long)(param_3 + lVar18 * -0x40) < 0x41) {
        uVar3 = param_3;
      }
      if (lVar20 < (long)uVar3) {
        if (uVar1 < 0xffffffffffffffe0) {
          uVar11 = ~uVar1 & 0xffffffffffffffe0;
          if (uVar11 == 0) goto code_r0x02028d38;
          uVar15 = (lStack_68 + lVar20 + -1) - uVar1;
          uVar9 = 0;
          if (((param_2 + lVar20 + -1) - uVar1 <= (ulong)(lStack_68 + lVar20) ||
               uVar15 <= (ulong)(param_2 + lVar20)) &&
             ((param_1 + 0x13f) - uVar1 <= (ulong)(lStack_68 + lVar20) || uVar15 <= param_1 + 0x140U
             )) {
            uVar12 = ~uVar12 & 0xffffffffffffffe0;
            lVar20 = lVar20 + uVar11;
            puVar13 = puVar17;
            puVar14 = (undefined8 *)(param_1 + 0x150);
            puVar16 = puVar21;
            do {
              uVar23 = puVar13[-1];
              uVar22 = puVar13[-2];
              uVar25 = puVar13[1];
              uVar24 = *puVar13;
              uVar27 = puVar14[-1];
              uVar26 = puVar14[-2];
              uVar29 = puVar14[1];
              uVar28 = *puVar14;
              uVar12 = uVar12 - 0x20;
              puVar14 = puVar14 + 4;
              puVar13 = puVar13 + 4;
              puVar16[-1] = CONCAT17((byte)((ulong)uVar27 >> 0x38) ^ (byte)((ulong)uVar23 >> 0x38),
                                     CONCAT16((byte)((ulong)uVar27 >> 0x30) ^
                                              (byte)((ulong)uVar23 >> 0x30),
                                              CONCAT15((byte)((ulong)uVar27 >> 0x28) ^
                                                       (byte)((ulong)uVar23 >> 0x28),
                                                       CONCAT14((byte)((ulong)uVar27 >> 0x20) ^
                                                                (byte)((ulong)uVar23 >> 0x20),
                                                                CONCAT13((byte)((ulong)uVar27 >>
                                                                               0x18) ^
                                                                         (byte)((ulong)uVar23 >>
                                                                               0x18),
                                                                         CONCAT12((byte)((ulong)
                                                  uVar27 >> 0x10) ^ (byte)((ulong)uVar23 >> 0x10),
                                                  CONCAT11((byte)((ulong)uVar27 >> 8) ^
                                                           (byte)((ulong)uVar23 >> 8),
                                                           (byte)uVar27 ^ (byte)uVar23)))))));
              puVar16[-2] = CONCAT17((byte)((ulong)uVar26 >> 0x38) ^ (byte)((ulong)uVar22 >> 0x38),
                                     CONCAT16((byte)((ulong)uVar26 >> 0x30) ^
                                              (byte)((ulong)uVar22 >> 0x30),
                                              CONCAT15((byte)((ulong)uVar26 >> 0x28) ^
                                                       (byte)((ulong)uVar22 >> 0x28),
                                                       CONCAT14((byte)((ulong)uVar26 >> 0x20) ^
                                                                (byte)((ulong)uVar22 >> 0x20),
                                                                CONCAT13((byte)((ulong)uVar26 >>
                                                                               0x18) ^
                                                                         (byte)((ulong)uVar22 >>
                                                                               0x18),
                                                                         CONCAT12((byte)((ulong)
                                                  uVar26 >> 0x10) ^ (byte)((ulong)uVar22 >> 0x10),
                                                  CONCAT11((byte)((ulong)uVar26 >> 8) ^
                                                           (byte)((ulong)uVar22 >> 8),
                                                           (byte)uVar26 ^ (byte)uVar22)))))));
              puVar16[1] = CONCAT17((byte)((ulong)uVar29 >> 0x38) ^ (byte)((ulong)uVar25 >> 0x38),
                                    CONCAT16((byte)((ulong)uVar29 >> 0x30) ^
                                             (byte)((ulong)uVar25 >> 0x30),
                                             CONCAT15((byte)((ulong)uVar29 >> 0x28) ^
                                                      (byte)((ulong)uVar25 >> 0x28),
                                                      CONCAT14((byte)((ulong)uVar29 >> 0x20) ^
                                                               (byte)((ulong)uVar25 >> 0x20),
                                                               CONCAT13((byte)((ulong)uVar29 >> 0x18
                                                                              ) ^ (byte)((ulong)
                                                  uVar25 >> 0x18),
                                                  CONCAT12((byte)((ulong)uVar29 >> 0x10) ^
                                                           (byte)((ulong)uVar25 >> 0x10),
                                                           CONCAT11((byte)((ulong)uVar29 >> 8) ^
                                                                    (byte)((ulong)uVar25 >> 8),
                                                                    (byte)uVar29 ^ (byte)uVar25)))))
                                            ));
              *puVar16 = CONCAT17((byte)((ulong)uVar28 >> 0x38) ^ (byte)((ulong)uVar24 >> 0x38),
                                  CONCAT16((byte)((ulong)uVar28 >> 0x30) ^
                                           (byte)((ulong)uVar24 >> 0x30),
                                           CONCAT15((byte)((ulong)uVar28 >> 0x28) ^
                                                    (byte)((ulong)uVar24 >> 0x28),
                                                    CONCAT14((byte)((ulong)uVar28 >> 0x20) ^
                                                             (byte)((ulong)uVar24 >> 0x20),
                                                             CONCAT13((byte)((ulong)uVar28 >> 0x18)
                                                                      ^ (byte)((ulong)uVar24 >> 0x18
                                                                              ),
                                                                      CONCAT12((byte)((ulong)uVar28
                                                                                     >> 0x10) ^
                                                                               (byte)((ulong)uVar24
                                                                                     >> 0x10),
                                                                               CONCAT11((byte)((
                                                  ulong)uVar28 >> 8) ^ (byte)((ulong)uVar24 >> 8),
                                                  (byte)uVar28 ^ (byte)uVar24)))))));
              puVar16 = puVar16 + 4;
            } while (uVar12 != 0);
            uVar9 = uVar11;
            if (uVar11 == ~uVar1) goto code_r0x02028d60;
          }
        }
        else {
code_r0x02028d38:
          uVar9 = 0;
        }
        pbVar10 = (byte *)(param_1 + 0x140U + uVar9);
        do {
          *(byte *)(lStack_68 + lVar20) = *pbVar10 ^ *(byte *)(param_2 + lVar20);
          lVar20 = lVar20 + 1;
          pbVar10 = pbVar10 + 1;
        } while (lVar20 < (long)uVar3);
      }
code_r0x02028d60:
      uVar19 = uVar19 + 0x40;
      puVar21 = puVar21 + 8;
      bVar6 = lVar18 != (long)uVar2 >> 6;
      lVar18 = lVar18 + 1;
      puVar17 = puVar17 + 8;
      *(int *)(param_1 + 0x130) = *(int *)(param_1 + 0x130) + 1;
    } while (bVar6);
    if (((long)param_3 < 0) || (lVar18 = *param_4, lStack_68 == lVar18)) goto joined_r0x02028e44;
    piVar8 = (int *)param_4[1];
    if (piVar8 == (int *)0x0) {
code_r0x02028dc0:
      if (lVar18 != 0) {
        operator delete[](void*)();
      }
      if (param_4[1] != 0) {
        Aska::TSharedPointerCode::DeleteCounter(int*)();
      }
    }
    else {
      do {
        iVar4 = *piVar8;
        cVar5 = '\x01';
        bVar6 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar6) {
          *piVar8 = iVar4 + -1;
          cVar5 = ExclusiveMonitorsStatus();
        }
      } while (cVar5 != '\0');
      if (iVar4 + -1 == 0) {
        lVar18 = *param_4;
        goto code_r0x02028dc0;
      }
    }
    *param_4 = lStack_68;
    param_4[1] = (long)piVar7;
    do {
      cVar5 = '\x01';
      bVar6 = (bool)ExclusiveMonitorPass(piVar7,0x10);
      if (bVar6) {
        *piVar7 = *piVar7 + 1;
        cVar5 = ExclusiveMonitorsStatus();
      }
    } while (cVar5 != '\0');
  }
  do {
    iVar4 = *piVar7;
    cVar5 = '\x01';
    bVar6 = (bool)ExclusiveMonitorPass(piVar7,0x10);
    if (bVar6) {
      *piVar7 = iVar4 + -1;
      cVar5 = ExclusiveMonitorsStatus();
    }
  } while (cVar5 != '\0');
  if (iVar4 != 1) {
    return param_3;
  }
  bVar6 = false;
joined_r0x02028e50:
  if (lStack_68 != 0) {
    operator delete[](void*)();
  }
  if (!bVar6) {
    Aska::TSharedPointerCode::DeleteCounter(int*)(piVar7);
  }
  return param_3;
}

// ==== Aska::LocalKVS::Clear(char const*)
// vaddr 0x1f28e8c | ghidra 0x2028e8c | size 208 | symbol _ZN4Aska8LocalKVS5ClearEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8LocalKVS5ClearEPKc(long *param_1,char *param_2,undefined1 *param_3)

{
  undefined1 *puVar1;
  long lVar2;
  long lStack_140;
  undefined1 *puStack_138;
  undefined1 auStack_130 [256];
  
  if (param_3 == (undefined1 *)0x0) {
    *param_1 = -0x3bd;
  }
  else if (*param_2 == '\0') {
    *param_1 = -0x3bc;
  }
  else {
    puStack_138 = (undefined1 *)0x0;
    puVar1 = param_3;
    if ((param_2[0x184] == '\0') ||
       (lVar2 = Aska::LocalKVS::CipherEncryptKey(char const*, char**, char const*, unsigned long) const(param_2,param_3,&puStack_138,auStack_130,0x100),
       puVar1 = puStack_138, -1 < lVar2)) {
      puStack_138 = puVar1;
      Aska::LocalKVS::ClearAndroid(char const*)(&lStack_140,param_2,puStack_138);
      lVar2 = lStack_140;
    }
    if ((((param_2[0x184] != '\0') && (puStack_138 != param_3)) && (puStack_138 != auStack_130)) &&
       (puStack_138 != (undefined1 *)0x0)) {
      operator delete[](void*)();
    }
    *param_1 = lVar2;
  }
  return;
}

// ==== Aska::LocalKVS::ClearAndroid(char const*)
// vaddr 0x1f28f5c | ghidra 0x2028f5c | size 456 | symbol _ZN4Aska8LocalKVS12ClearAndroidEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8LocalKVS12ClearAndroidEPKc(long *param_1,undefined8 param_2,undefined8 param_3)

{
  ulong uVar1;
  char cVar2;
  ulong uVar3;
  undefined *puVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  char *pcVar11;
  long lVar12;
  long *plVar13;
  long lVar14;
  undefined8 uVar15;
  long lStack_48;
  char acStack_40 [8];
  long *plStack_38;
  
  puVar4 = PTR__ZN4Aska6Global13m_pAndroidAppE_02cc2688;
  plVar13 = *(long **)(*(long *)(*(long *)PTR__ZN4Aska6Global13m_pAndroidAppE_02cc2688 + 0x18) + 8);
  plStack_38 = (long *)0x0;
  Aska::AndroidUtil::AttachCurrentThread(_JavaVM*, _JNIEnv**, void*)(plVar13,&plStack_38,0);
  uVar15 = *(undefined8 *)(*(long *)(*(long *)puVar4 + 0x18) + 0x18);
  uVar5 = (**(code **)(*plStack_38 + 0x538))(plStack_38,param_2);
  uVar6 = (**(code **)(*plStack_38 + 0x538))(plStack_38,param_3);
  Aska::AndroidUtil::CallMethod(_JNIEnv*, jvalue*, _jobject*, char const*, char const*, ...)(&lStack_48,plStack_38,acStack_40,uVar15,&UNK_02970266/*"RemoveSharedPreferences"*/,&UNK_0297027e/*"(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Boolean;"*/,uVar5,uVar6);
  *param_1 = lStack_48;
  (**(code **)(*plStack_38 + 0xb8))(plStack_38,uVar5);
  (**(code **)(*plStack_38 + 0xb8))(plStack_38,uVar6);
  if ((-1 < lStack_48) && (acStack_40[0] == '\0')) {
    *param_1 = -1;
  }
  lVar14 = *(long *)PTR__ZN4Aska11AndroidUtil19m_pAttachThreadListE_02cbb5c8;
  if (lVar14 != 0) {
    uVar7 = Aska::Thread::GetCurrentID()();
    uVar8 = *(ulong *)(lVar14 + 0x28);
    if (uVar8 != 0) {
      uVar9 = ~uVar7 + uVar7 * 0x200000;
      uVar9 = (uVar9 ^ uVar9 >> 0x18) * 0x109;
      uVar10 = (uVar9 ^ uVar9 >> 0xe) * 0x15;
      uVar9 = 0;
      do {
        uVar1 = (uVar10 ^ uVar10 >> 0x1c) * 0x80000001 + uVar9;
        uVar3 = 0;
        if (uVar8 != 0) {
          uVar3 = uVar1 / uVar8;
        }
        lVar12 = uVar1 - uVar3 * uVar8;
        pcVar11 = (char *)(*(long *)(lVar14 + 0x20) + lVar12 * 0x18);
        cVar2 = *pcVar11;
        if (cVar2 == '\x01') {
          if (*(ulong *)(*(long *)(lVar14 + 0x20) + lVar12 * 0x18 + 8) == uVar7) {
            *(int *)(lVar14 + 0x10) = *(int *)(lVar14 + 0x10) + -1;
            *(int *)(lVar14 + 0x14) = *(int *)(lVar14 + 0x14) + 1;
            *pcVar11 = '\x02';
            break;
          }
        }
        else if (cVar2 == '\0') break;
        uVar9 = uVar9 + 1;
      } while (uVar9 < uVar8);
    }
  }
  (**(code **)(*plVar13 + 0x28))(plVar13);
  return;
}

// ==== Aska::LocalKVS::ClearAll()
// vaddr 0x1f29124 | ghidra 0x2029124 | size 24 | symbol _ZN4Aska8LocalKVS8ClearAllEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8LocalKVS8ClearAllEv(undefined8 *param_1,char *param_2)

{
  if (*param_2 != '\0') {
    (*(code *)PTR__ZN4Aska8LocalKVS15ClearAllAndroidEv_02cafe90)();
    return;
  }
  *param_1 = 0xfffffffffffffc44;
  return;
}

// ==== Aska::LocalKVS::ClearAllAndroid()
// vaddr 0x1f2913c | ghidra 0x202913c | size 400 | symbol _ZN4Aska8LocalKVS15ClearAllAndroidEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8LocalKVS15ClearAllAndroidEv(long *param_1,undefined8 param_2)

{
  ulong uVar1;
  char cVar2;
  ulong uVar3;
  undefined *puVar4;
  undefined8 uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  char *pcVar10;
  long lVar11;
  long *plVar12;
  long lVar13;
  undefined8 uVar14;
  long lStack_40;
  char acStack_38 [8];
  long *plStack_28;
  
  puVar4 = PTR__ZN4Aska6Global13m_pAndroidAppE_02cc2688;
  plVar12 = *(long **)(*(long *)(*(long *)PTR__ZN4Aska6Global13m_pAndroidAppE_02cc2688 + 0x18) + 8);
  plStack_28 = (long *)0x0;
  Aska::AndroidUtil::AttachCurrentThread(_JavaVM*, _JNIEnv**, void*)(plVar12,&plStack_28,0);
  uVar14 = *(undefined8 *)(*(long *)(*(long *)puVar4 + 0x18) + 0x18);
  uVar5 = (**(code **)(*plStack_28 + 0x538))(plStack_28,param_2);
  Aska::AndroidUtil::CallMethod(_JNIEnv*, jvalue*, _jobject*, char const*, char const*, ...)(&lStack_40,plStack_28,acStack_38,uVar14,&UNK_029702b8/*"ClearSharedPreferences"*/,&UNK_029702cf/*"(Ljava/lang/String;)Ljava/lang/Boolean;"*/,uVar5);
  *param_1 = lStack_40;
  (**(code **)(*plStack_28 + 0xb8))(plStack_28,uVar5);
  if ((-1 < lStack_40) && (acStack_38[0] == '\0')) {
    *param_1 = -1;
  }
  lVar13 = *(long *)PTR__ZN4Aska11AndroidUtil19m_pAttachThreadListE_02cbb5c8;
  if (lVar13 != 0) {
    uVar6 = Aska::Thread::GetCurrentID()();
    uVar7 = *(ulong *)(lVar13 + 0x28);
    if (uVar7 != 0) {
      uVar8 = ~uVar6 + uVar6 * 0x200000;
      uVar8 = (uVar8 ^ uVar8 >> 0x18) * 0x109;
      uVar9 = (uVar8 ^ uVar8 >> 0xe) * 0x15;
      uVar8 = 0;
      do {
        uVar1 = (uVar9 ^ uVar9 >> 0x1c) * 0x80000001 + uVar8;
        uVar3 = 0;
        if (uVar7 != 0) {
          uVar3 = uVar1 / uVar7;
        }
        lVar11 = uVar1 - uVar3 * uVar7;
        pcVar10 = (char *)(*(long *)(lVar13 + 0x20) + lVar11 * 0x18);
        cVar2 = *pcVar10;
        if (cVar2 == '\x01') {
          if (*(ulong *)(*(long *)(lVar13 + 0x20) + lVar11 * 0x18 + 8) == uVar6) {
            *(int *)(lVar13 + 0x10) = *(int *)(lVar13 + 0x10) + -1;
            *(int *)(lVar13 + 0x14) = *(int *)(lVar13 + 0x14) + 1;
            *pcVar10 = '\x02';
            break;
          }
        }
        else if (cVar2 == '\0') break;
        uVar8 = uVar8 + 1;
      } while (uVar8 < uVar7);
    }
  }
  (**(code **)(*plVar12 + 0x28))(plVar12);
  return;
}


// FAILED to create function at 02abb218 CGameLocalKVS::vtable
// FAILED to create function at 02abb250 CGameLocalKVS::typeinfo
