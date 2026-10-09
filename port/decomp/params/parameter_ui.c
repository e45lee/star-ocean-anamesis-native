// port/decomp/params/parameter_ui.c: Ghidra decompiles for the params subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-09 02:10 UTC: tools/decomp.sh '--into' 'params/parameter_ui' 'CParameterUI::Reset\(' 'CParameterUI::GetSelectMissionTitle'

// ==== CParameterUI::Reset()
// vaddr 0x16fef4c | ghidra 0x17fef4c | size 544 | symbol _ZN12CParameterUI5ResetEv | lib libSOA-3.7.0.so | 2026-10-09
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN12CParameterUI5ResetEv(long param_1)

{
  byte *pbVar1;
  byte bVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined1 *puVar5;
  char *pcVar6;
  long lVar7;
  int *piVar8;
  undefined1 auStack_938 [2328];
  
  bVar2 = *(byte *)(param_1 + 0x128);
  pbVar1 = (byte *)(param_1 + 0x128);
  if ((bVar2 & 1) != 0) {
    bVar2 = *pbVar1;
  }
  if ((bVar2 & 1) == 0) {
    puVar5 = (undefined1 *)(param_1 + 0x129);
  }
  else {
    puVar5 = *(undefined1 **)(param_1 + 0x138);
  }
  *puVar5 = 0;
  if ((*pbVar1 & 1) == 0) {
    *pbVar1 = 0;
  }
  else {
    *(undefined8 *)(param_1 + 0x130) = 0;
  }
  bVar2 = *(byte *)(param_1 + 0x170);
  pbVar1 = (byte *)(param_1 + 0x170);
  if ((bVar2 & 1) != 0) {
    bVar2 = *pbVar1;
  }
  if ((bVar2 & 1) == 0) {
    puVar5 = (undefined1 *)(param_1 + 0x171);
  }
  else {
    puVar5 = *(undefined1 **)(param_1 + 0x180);
  }
  *puVar5 = 0;
  if ((*pbVar1 & 1) == 0) {
    *pbVar1 = 0;
  }
  else {
    *(undefined8 *)(param_1 + 0x178) = 0;
  }
  bVar2 = *(byte *)(param_1 + 0x188);
  pbVar1 = (byte *)(param_1 + 0x188);
  if ((bVar2 & 1) != 0) {
    bVar2 = *pbVar1;
  }
  if ((bVar2 & 1) == 0) {
    puVar5 = (undefined1 *)(param_1 + 0x189);
  }
  else {
    puVar5 = *(undefined1 **)(param_1 + 0x198);
  }
  *puVar5 = 0;
  if ((*pbVar1 & 1) == 0) {
    *pbVar1 = 0;
  }
  else {
    *(undefined8 *)(param_1 + 400) = 0;
  }
  bVar2 = *(byte *)(param_1 + 0x158);
  pbVar1 = (byte *)(param_1 + 0x158);
  if ((bVar2 & 1) != 0) {
    bVar2 = *pbVar1;
  }
  if ((bVar2 & 1) == 0) {
    puVar5 = (undefined1 *)(param_1 + 0x159);
  }
  else {
    puVar5 = *(undefined1 **)(param_1 + 0x168);
  }
  *puVar5 = 0;
  if ((*pbVar1 & 1) == 0) {
    *pbVar1 = 0;
  }
  else {
    *(undefined8 *)(param_1 + 0x160) = 0;
  }
  *(undefined8 *)(param_1 + 0x140) = 0x600000000;
  *(undefined1 *)(param_1 + 0x1cf) = 1;
  *(undefined8 *)(param_1 + 0x1a0) = 0;
  *(undefined4 *)(param_1 + 0x1a8) = 0;
  *(undefined8 *)(param_1 + 0x150) = 0;
  *(undefined1 *)(param_1 + 0x1cd) = 0;
  *(undefined1 *)(param_1 + 0x1ce) = 0;
  *(undefined4 *)(param_1 + 0x1b0) = 0;
  *(undefined8 *)(param_1 + 0x1b8) = 0;
  *(undefined1 *)(param_1 + 0x1c0) = 0;
  *(undefined4 *)(param_1 + 0x1d0) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1d4) = 0xffffffff;
  *(undefined8 *)(param_1 + 0x1d8) = 0;
  memset(auStack_938,0,0x918);
  CPlayerInfo::CPlayerInfo()(auStack_938);
  CPlayerInfo::operator=(CPlayerInfo&&)(param_1 + 0x1e0,auStack_938);
  CPlayerInfo::~CPlayerInfo()(auStack_938);
  pcVar6 = *(char **)(param_1 + 0xc008);
  if ((pcVar6 != (char *)0x0) && (*(long *)(param_1 + 0xc010) != 0)) {
    lVar7 = *(long *)(param_1 + 0xc010) << 3;
    do {
      piVar8 = (int *)(param_1 + 0xbff8);
      if ((*pcVar6 == '\x01') || (piVar8 = (int *)(param_1 + 0xbffc), *pcVar6 == '\x02')) {
        *piVar8 = *piVar8 + -1;
        *pcVar6 = '\0';
      }
      lVar7 = lVar7 + -8;
      pcVar6 = pcVar6 + 8;
    } while (lVar7 != 0);
  }
  *(int *)(param_1 + 0xbff8) = 0;
  *(undefined4 *)(param_1 + 0xbffc) = 0;
  uVar4 = _UNK_027f7858;
  uVar3 = _UNK_027f7850;
  *(undefined1 *)(param_1 + 0xbfc0) = 0;
  *(undefined8 *)(param_1 + 0xbfcc) = uVar4;
  *(undefined8 *)(param_1 + 0xbfc4) = uVar3;
  *(undefined1 *)(param_1 + 0xbfd8) = 0;
  *(undefined1 *)(param_1 + 0xbfd9) = 0;
  *(undefined8 *)(param_1 + 0xc378) = 0;
  *(undefined8 *)(param_1 + 0xc370) = 0;
  *(undefined8 *)(param_1 + 0xc368) = 0;
  *(undefined8 *)(param_1 + 0xc360) = 0;
  *(undefined4 *)(param_1 + 0x1c8) = 0;
  *(undefined4 *)(param_1 + 0xbfe0) = 0;
  return;
}

// ==== CParameterUI::GetSelectMissionTitle() const
// vaddr 0x16ffc90 | ghidra 0x17ffc90 | size 880 | symbol _ZNK12CParameterUI21GetSelectMissionTitleEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZNK12CParameterUI21GetSelectMissionTitleEv(ulong *param_1,long param_2)

{
  undefined4 uVar1;
  ulong uVar2;
  ulong uVar3;
  undefined1 *puVar4;
  undefined *puVar5;
  long lVar6;
  long lStack_180;
  long lStack_178;
  ulong uStack_170;
  ulong uStack_168;
  undefined1 *puStack_160;
  undefined *puStack_158;
  long lStack_150;
  ulong *puStack_148;
  undefined8 uStack_140;
  undefined4 uStack_138;
  undefined1 uStack_134;
  ulong uStack_130;
  ulong uStack_128;
  undefined1 *puStack_120;
  
  puVar5 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  uStack_168 = 0;
  puStack_160 = (undefined1 *)0x0;
  uStack_170 = 0;
  if (5 < *(uint *)(param_2 + 0x140)) {
code_r0x017fffdc:
    param_1[2] = (ulong)puStack_160;
    param_1[1] = uStack_168;
    *param_1 = uStack_170;
    return;
  }
  uVar1 = *(undefined4 *)(param_2 + 0x1a0);
  switch(*(uint *)(param_2 + 0x140)) {
  case 0:
    lVar6 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (lVar6 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar6 = *(long *)puVar5;
    }
    lVar6 = CParameterManager::pMasterParameterMission() const(lVar6);
    if (lVar6 == 0) goto code_r0x017fffdc;
    snprintf(&uStack_130,0x100,&UNK_027e6d32/*"%u"*/,uVar1);
    puStack_158 = &UNK_027ffe64/*"id"*/;
    lStack_150 = 2;
    puStack_148 = &uStack_130;
    uStack_140 = strlen(&uStack_130);
    puVar5 = &UNK_0285eea9/*"SELECT * FROM master_mission WHERE id=?"*/;
    break;
  case 1:
    lVar6 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (lVar6 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar6 = *(long *)puVar5;
    }
    lVar6 = CParameterManager::pMasterParameterEventMission() const(lVar6);
    if (lVar6 == 0) goto code_r0x017fffdc;
    snprintf(&uStack_130,0x100,&UNK_027e6d32/*"%u"*/,uVar1);
    puStack_158 = &UNK_027ffe64/*"id"*/;
    lStack_150 = 2;
    puStack_148 = &uStack_130;
    uStack_140 = strlen(&uStack_130);
    puVar5 = &UNK_0285eed1/*"SELECT * FROM master_event_mission WHERE id=?"*/;
    break;
  case 2:
    lVar6 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (lVar6 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar6 = *(long *)puVar5;
    }
    lVar6 = CParameterManager::pMasterParameterTowerMission() const(lVar6);
    if (lVar6 == 0) goto code_r0x017fffdc;
    snprintf(&uStack_130,0x100,&UNK_027e6d32/*"%u"*/,uVar1);
    puStack_158 = &UNK_027ffe64/*"id"*/;
    lStack_150 = 2;
    puStack_148 = &uStack_130;
    uStack_140 = strlen(&uStack_130);
    puVar5 = &UNK_0285eeff/*"SELECT * FROM master_tower_mission WHERE id=?"*/;
    break;
  default:
    goto code_r0x017fffdc;
  case 5:
    uVar1 = *(undefined4 *)(param_2 + 0x1a8);
    lVar6 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (lVar6 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar6 = *(long *)puVar5;
    }
    CMasterParameterBaseSqlite_Simple<CMasterSphere211FloorAssetElement>::pParameterFromHash(unsigned int) const(&puStack_158,*(undefined8 *)(*(long *)(lVar6 + 0x5f8) + 0x520),uVar1);
    if (puStack_158 == (undefined *)0x0) {
      if (lStack_150 != 0) {
        std::__ndk1::__shared_weak_count::__release_shared()();
      }
      goto code_r0x017fffdc;
    }
    uStack_128 = 0;
    puStack_120 = (undefined1 *)0x0;
    uStack_130 = 0;
    void CParameterPropertyBase<52u>::CryptString<string >(string&, string const&)(&uStack_130,puStack_158 + 0x98);
    CUIUtility::GetSystemMessage(string const&, long, bool*)(param_1,&uStack_130,0,0);
    lStack_178 = lStack_150;
    if ((uStack_130 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_120);
      lStack_178 = lStack_150;
    }
    goto joined_r0x017fff40;
  }
  uStack_134 = 0;
  uStack_138 = 0;
  CMasterParameterBaseSqlite_Simple<CMasterParameterMissionElement>::ParameterByQuery(char const*, Aska::Yayoi::QueryParam*, unsigned int) const(&lStack_180,lVar6,puVar5,&puStack_158,1);
  if (lStack_180 != 0) {
    lStack_150 = 0;
    puStack_148 = (ulong *)0x0;
    puStack_158 = (undefined *)0x0;
    void CParameterPropertyBase<122u>::CryptString<string >(string&, string const&)(&puStack_158,lStack_180 + 0x2c8);
    CUIUtility::GetSystemMessage(string const&, long, bool*)(&uStack_130,&puStack_158,0,0);
    if ((uStack_170 & 1) == 0) {
      uStack_170 = uStack_170 & 0xffffffffffff0000;
    }
    else {
      *puStack_160 = 0;
      uStack_168 = 0;
    }
    string::reserve(unsigned long)(&uStack_170,0);
    puStack_160 = puStack_120;
    uStack_168 = uStack_128;
    uStack_170 = uStack_130;
    uStack_128 = 0;
    puStack_120 = (undefined1 *)0x0;
    uStack_130 = 0;
    if (((ulong)puStack_158 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_148);
    }
  }
  puVar4 = puStack_160;
  uVar3 = uStack_168;
  uVar2 = uStack_170;
  uStack_168 = 0;
  puStack_160 = (undefined1 *)0x0;
  uStack_170 = 0;
  param_1[2] = (ulong)puVar4;
  param_1[1] = uVar3;
  *param_1 = uVar2;
joined_r0x017fff40:
  if (lStack_178 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()(lStack_178);
  }
  if ((uStack_170 & 1) == 0) {
    return;
  }
  Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_160);
  return;
}
