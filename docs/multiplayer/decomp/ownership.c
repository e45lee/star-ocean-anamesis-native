// ownership: Ghidra decompiles of work/libSOA-3.7.0.so (3.7.0), extracted by extract.py.
// Data, not code: see README.md and docs/multiplayer.md for what they show.

// ==== undefined CPartyManager::IsMultiplaySendCharacter(int)
// _ZN13CPartyManager24IsMultiplaySendCharacterEi @ 013a4e48

bool _ZN13CPartyManager24IsMultiplaySendCharacterEi(long param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  undefined *puVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  int *piVar8;
  
  puVar4 = PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908;
  if (*(long *)PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908 != 0) {
    uVar5 = CMultiplayManager::IsMultiplay() const(*(long *)
                             PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908
                           );
    puVar3 = PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
    if (0xb < param_2) {
      return false;
    }
    if ((uVar5 & 1) == 0) {
      return false;
    }
    piVar8 = (int *)(param_1 + (long)(int)param_2 * 0x260 + 0x4c);
    iVar1 = *piVar8;
    if (iVar1 != 0) {
      lVar6 = *(long *)PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)puVar3;
        iVar1 = *piVar8;
      }
      lVar6 = CArena::SearchCharacterObjectByHandle(unsigned int) const(lVar6,iVar1);
      if (lVar6 == 0) {
        return false;
      }
      lVar7 = *(long *)puVar4;
      iVar1 = *(int *)(lVar6 + 0x76d4);
      if (lVar7 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar7 = *(long *)puVar4;
      }
      iVar2 = *(int *)(lVar7 + 0x3d8);
      if (iVar1 != 1) {
        return iVar2 == 0;
      }
      lVar7 = *(long *)puVar3;
      if (lVar7 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar7 = *(long *)puVar3;
      }
      lVar7 = CArena::SearchCharacterObjectByHandle(unsigned int) const(lVar7,*(undefined4 *)(param_1 + (long)iVar2 * 0x260 + 0x4c));
      if (*(int *)(lVar7 + 0x1068) == *(int *)(lVar6 + 0x1068)) {
        return true;
      }
      lVar7 = *(long *)puVar4;
      if (lVar7 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar7 = *(long *)puVar4;
      }
      if (*(int *)(lVar7 + 0x3d8) == 0) {
        if (lVar7 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar7 = *(long *)puVar4;
        }
        if ((3 < param_2) || (*(char *)(lVar7 + (ulong)param_2 + 0x3dc) == '\0')) {
          iVar1 = *(int *)(param_1 + 0x4c);
          if (iVar1 != 0) {
            lVar7 = *(long *)puVar3;
            if (lVar7 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
              lVar7 = *(long *)puVar3;
              iVar1 = *(int *)(param_1 + 0x4c);
            }
            lVar7 = CArena::SearchCharacterObjectByHandle(unsigned int) const(lVar7,iVar1);
            if ((lVar7 != 0) && (*(int *)(lVar7 + 0x1068) == *(int *)(lVar6 + 0x1068))) {
              lVar7 = *(long *)puVar4;
              if (lVar7 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
                lVar7 = *(long *)puVar4;
              }
              if (*(char *)(lVar7 + 0x3dc) != '\0') {
                return false;
              }
            }
          }
          iVar1 = *(int *)(param_1 + 0x2ac);
          if (iVar1 != 0) {
            lVar7 = *(long *)puVar3;
            if (lVar7 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
              lVar7 = *(long *)puVar3;
              iVar1 = *(int *)(param_1 + 0x2ac);
            }
            lVar7 = CArena::SearchCharacterObjectByHandle(unsigned int) const(lVar7,iVar1);
            if ((lVar7 != 0) && (*(int *)(lVar7 + 0x1068) == *(int *)(lVar6 + 0x1068))) {
              lVar7 = *(long *)puVar4;
              if (lVar7 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
                lVar7 = *(long *)puVar4;
              }
              if (*(char *)(lVar7 + 0x3dd) != '\0') {
                return false;
              }
            }
          }
          iVar1 = *(int *)(param_1 + 0x50c);
          if (iVar1 != 0) {
            lVar7 = *(long *)puVar3;
            if (lVar7 == 0) {
              Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
              lVar7 = *(long *)puVar3;
              iVar1 = *(int *)(param_1 + 0x50c);
            }
            lVar7 = CArena::SearchCharacterObjectByHandle(unsigned int) const(lVar7,iVar1);
            if ((lVar7 != 0) && (*(int *)(lVar7 + 0x1068) == *(int *)(lVar6 + 0x1068))) {
              lVar7 = *(long *)puVar4;
              if (lVar7 == 0) {
                Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
                lVar7 = *(long *)puVar4;
              }
              if (*(char *)(lVar7 + 0x3de) != '\0') {
                return false;
              }
            }
          }
          iVar1 = *(int *)(param_1 + 0x76c);
          if (iVar1 == 0) {
            return true;
          }
          lVar7 = *(long *)puVar3;
          if (lVar7 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
            lVar7 = *(long *)puVar3;
            iVar1 = *(int *)(param_1 + 0x76c);
          }
          lVar7 = CArena::SearchCharacterObjectByHandle(unsigned int) const(lVar7,iVar1);
          if (lVar7 == 0) {
            return true;
          }
          if (*(int *)(lVar7 + 0x1068) != *(int *)(lVar6 + 0x1068)) {
            return true;
          }
          lVar6 = *(long *)puVar4;
          if (lVar6 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
            lVar6 = *(long *)puVar4;
          }
          if (*(char *)(lVar6 + 0x3df) == '\0') {
            return true;
          }
          return false;
        }
      }
    }
  }
  return false;
}

// ==== undefined CBattleUtility::CreateCharacter(CBattleUtility::CreateCharacterInfo,bool,bool,CBattleUtility::CreateCharacterSceneType)
// _ZN14CBattleUtility15CreateCharacterENS_19CreateCharacterInfoEbbNS_24CreateCharacterSceneTypeE @ 013f1598
// decompile failed: Exception while decompiling 013f1598: process: timeout

// ==== undefined CUIUtility::SetMultiplayHost(bool)
// _ZN10CUIUtility16SetMultiplayHostEb @ 01ee6404

void _ZN10CUIUtility16SetMultiplayHostEb(byte param_1)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  undefined1 auStack_a8 [8];
  undefined1 auStack_a0 [128];
  byte abStack_14 [4];
  
  __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(auStack_a0,0x80,0xffffffffffffffff,&UNK_029528e3/*"BAS:IsHost"*/);
  puVar1 = PTR__ZN9Framework10TSingletonI13CGameLocalKVSE11m_pInstanceE_02cb8e58;
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI13CGameLocalKVSE11m_pInstanceE_02cb8e58;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  uVar3 = CGameLocalKVS::pSubstance() const(lVar2);
  abStack_14[0] = param_1 & 1;
  Aska::LocalKVS::SetBinary(char const*, signed char const*, long)(auStack_a8,uVar3,auStack_a0,abStack_14,1);
  return;
}

// ==== undefined CUIUtility::IsMultiplayHost(void)
// _ZN10CUIUtility15IsMultiplayHostEv @ 01ee6488

bool _ZN10CUIUtility15IsMultiplayHostEv(void)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  undefined *puVar4;
  long lVar5;
  undefined8 uVar6;
  char cVar7;
  undefined1 auStack_b0 [128];
  char *pcStack_30;
  int *piStack_28;
  undefined8 uStack_18;
  
  uStack_18 = 0;
  __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(auStack_b0,0x80,0xffffffffffffffff,&UNK_029528e3/*"BAS:IsHost"*/);
  puVar4 = PTR__ZN9Framework10TSingletonI13CGameLocalKVSE11m_pInstanceE_02cb8e58;
  lVar5 = *(long *)PTR__ZN9Framework10TSingletonI13CGameLocalKVSE11m_pInstanceE_02cb8e58;
  if (lVar5 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar5 = *(long *)puVar4;
  }
  uVar6 = CGameLocalKVS::pSubstance() const(lVar5);
  Aska::LocalKVS::GetBinary(char const*, long*) const(&pcStack_30,uVar6,auStack_b0,&uStack_18);
  if (pcStack_30 == (char *)0x0) {
    cVar7 = '\0';
  }
  else {
    cVar7 = *pcStack_30;
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
    if (iVar1 != 1) goto code_r0x01ee6554;
  }
  if (pcStack_30 != (char *)0x0) {
    operator delete[](void*)();
  }
  if (piStack_28 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x01ee6554:
  return cVar7 != '\0';
}


// FAILED to create function at 02cebbac CBattleUIManager::EnableColor
// FAILED to create function at 02cebbb0 CBattleUIManager::DisableColor

// ==== undefined CPartyManager::SetupCharacter_Local(int,bool)
// _ZN13CPartyManager20SetupCharacter_LocalEib @ 013a4cfc

void _ZN13CPartyManager20SetupCharacter_LocalEib(long param_1,int param_2,uint param_3)

{
  undefined *puVar1;
  undefined8 *puVar2;
  long *plVar3;
  undefined4 uVar4;
  long lVar5;
  undefined1 auStack_220 [464];
  
  puVar1 = PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
  lVar5 = *(long *)PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
  if (lVar5 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar5 = *(long *)puVar1;
  }
  puVar2 = (undefined8 *)CArena::rSceneObjectContainer()(lVar5);
  lVar5 = *(long *)puVar1;
  if (lVar5 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar5 = *(long *)puVar1;
  }
  plVar3 = (long *)CArena::rTimeElement()(lVar5);
  if (*(char *)(param_1 + (long)param_2 * 0x260 + 0x36) != '\0') {
    CBattleUtility::CreateCharacterInfo::CreateCharacterInfo(CBattleUtility::CreateCharacterInfo const&)(auStack_220,param_1 + (long)param_2 * 0x260 + 0xa8);
    lVar5 = CBattleUtility::CreateCharacter(CBattleUtility::CreateCharacterInfo, bool, bool, CBattleUtility::CreateCharacterSceneType)(auStack_220,param_3 & 1,param_3 & 1,0);
    CBattleUtility::CreateCharacterInfo::~CreateCharacterInfo()(auStack_220);
    if (lVar5 != 0) {
      uVar4 = 1;
      if ((param_3 & 1) == 0) {
        uVar4 = 2;
      }
      *(undefined4 *)(lVar5 + 0x76d4) = uVar4;
      *(int *)(lVar5 + 0x76d8) = param_2;
      (**(code **)*puVar2)(puVar2,lVar5,0);
      (**(code **)(*plVar3 + 0x10))(plVar3,lVar5);
      *(undefined4 *)(param_1 + (long)param_2 * 0x260 + 0x4c) = *(undefined4 *)(lVar5 + 0xb8);
    }
  }
  return;
}

