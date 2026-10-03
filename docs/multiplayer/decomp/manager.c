// manager: Ghidra decompiles of work/libSOA-3.7.0.so (3.7.0), extracted by extract.py.
// Data, not code: see README.md and docs/multiplayer.md for what they show.

// ==== undefined IMultiplayNotify::OnProtocolError(Aska::Yayoi::MO::BattleProtocol::FunctionID,Aska::Status)
// _ZN16IMultiplayNotify15OnProtocolErrorEN4Aska5Yayoi2MO14BattleProtocol10FunctionIDENS0_6StatusE @ 015a191c

void _ZN16IMultiplayNotify15OnProtocolErrorEN4Aska5Yayoi2MO14BattleProtocol10FunctionIDENS0_6StatusE
               (long param_1,undefined8 param_2,long *param_3)

{
  undefined *puVar1;
  long lVar2;
  long lStack_28;
  
  puVar1 = PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908;
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908;
  if (((lVar2 != 0) && (*(char *)(lVar2 + 0x3e3) == '\0')) && (*(char *)(lVar2 + 0x3e1) == '\0')) {
    lStack_28 = *param_3;
    if (0 < lStack_28) {
      CNetworkUtility::AskaStatus2ApiErrorCode(Aska::Status)(&lStack_28);
      lVar2 = *(long *)puVar1;
    }
    if (*(long *)(lVar2 + 0x38) == 0) {
      return;
    }
    if ((*param_3 != -0x3af) && (*param_3 != -0x3b4)) {
      return;
    }
  }
  *(undefined1 *)(param_1 + 0xb) = 1;
  return;
}

// ==== undefined CMultiplayManager::PackCharacterParameterEnemy(CMultiplayManager::CharacterParameterEnemy *)
// _ZN17CMultiplayManager27PackCharacterParameterEnemyEPNS_23CharacterParameterEnemyE @ 015a5400

long _ZN17CMultiplayManager27PackCharacterParameterEnemyEPNS_23CharacterParameterEnemyE
               (long param_1,long param_2)

{
  char *pcVar1;
  undefined4 *puVar2;
  undefined *puVar3;
  long lVar4;
  undefined8 uVar5;
  long lVar6;
  ulong uVar7;
  char *pcVar8;
  char *pcVar9;
  char cVar10;
  long lVar11;
  long lVar12;
  ulong uVar13;
  undefined4 uVar14;
  
  puVar3 = PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
  lVar12 = 0;
  uVar13 = 4;
  do {
    lVar4 = *(long *)puVar3;
    if (lVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar4 = *(long *)puVar3;
    }
    uVar5 = CArena::crPartyManager() const(lVar4);
    lVar4 = CPartyManager::GetCharacter(int) const(uVar5,uVar13 & 0xffffffff);
    if (lVar4 != 0) {
      lVar6 = *(long *)puVar3;
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)puVar3;
      }
      uVar5 = CArena::rPartyManager()(lVar6);
      uVar7 = CPartyManager::IsMultiplaySendCharacter(int)(uVar5,uVar13 & 0xffffffff);
      pcVar1 = (char *)(param_1 + uVar13 + 0x3e9);
      if (((uVar7 & 1) != 0) && (*pcVar1 != '\0')) {
        uVar14 = CCharacterData::HP() const(lVar4 + 0x1010);
        puVar2 = (undefined4 *)(param_2 + lVar12 * 8);
        *puVar2 = uVar14;
        *(char *)(puVar2 + 1) = (char)uVar13;
        if (*(int *)(param_1 + 0xa0) == 0) {
code_r0x015a5550:
          cVar10 = -1;
        }
        else {
          pcVar9 = *(char **)(param_1 + 0xb0);
          lVar6 = *(long *)(param_1 + 0xb8);
          pcVar8 = pcVar9;
          if (lVar6 != 0) {
            lVar11 = lVar6 * 0xc;
            do {
              if (*pcVar8 == '\x01') goto code_r0x015a5514;
              lVar11 = lVar11 + -0xc;
              pcVar8 = pcVar8 + 0xc;
            } while (lVar11 != 0);
            goto code_r0x015a5550;
          }
code_r0x015a5514:
          pcVar9 = pcVar9 + lVar6 * 0xc;
          if (pcVar8 == pcVar9) goto code_r0x015a5550;
          do {
            if (*(int *)(pcVar8 + 8) == *(int *)(lVar4 + 0x618)) {
              cVar10 = pcVar8[4];
              break;
            }
            do {
              if (pcVar9 == pcVar8) goto code_r0x015a5550;
              pcVar8 = pcVar8 + 0xc;
            } while (*pcVar8 != '\x01');
            cVar10 = -1;
          } while (pcVar9 != pcVar8);
        }
        lVar12 = lVar12 + 1;
        *(char *)((long)puVar2 + 5) = cVar10;
      }
      *pcVar1 = '\0';
    }
    uVar13 = uVar13 + 1;
    if (uVar13 == 0xc) {
      return lVar12;
    }
  } while( true );
}

// ==== undefined CMultiplayManager::InitMatchingClient(char const *,unsigned short,Aska::Yayoi::IMatchingNotify *)
// _ZN17CMultiplayManager18InitMatchingClientEPKctPN4Aska5Yayoi15IMatchingNotifyE @ 015a3c34

void _ZN17CMultiplayManager18InitMatchingClientEPKctPN4Aska5Yayoi15IMatchingNotifyE
               (long *param_1,long param_2,long param_3,uint param_4,long param_5)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  long lVar6;
  undefined4 *puVar7;
  int *piVar8;
  undefined4 *puStack_70;
  int *piStack_68;
  long lStack_60;
  undefined4 *puStack_58;
  
  if (((param_3 == 0) || ((param_4 & 0xffff) == 0)) || (param_5 == 0)) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0281a8e8/*"C:\BAS_Submission\Client\Project\..\Source\Game\Network\Multiplay\MultiplayManager.cpp"*/,0x679,&UNK_029d2011);
  }
  CMultiplayManager::TermMatchingClient()(param_2);
  puVar4 = PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
  puStack_58 = (undefined4 *)0x0;
  lVar6 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
  if (lVar6 == 0) {
    lVar6 = Aska::Global::GetAvailableMemoryManager()();
  }
  puVar7 = (undefined4 *)Aska::MemoryManager::Malloc(unsigned long)(lVar6,0x100);
  if (puVar7 == (undefined4 *)0x0) {
    piVar8 = (int *)0x0;
    *param_1 = -0x3bf;
  }
  else {
    puStack_58 = (undefined4 *)0x0;
    piVar8 = (int *)Aska::TSharedPointerCode::CreateCounter(int)(0);
    if (piVar8 == (int *)0x0) {
      lVar6 = -0x3bf;
      goto code_r0x015a3e64;
    }
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
      if (bVar3) {
        *piVar8 = *piVar8 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    puStack_58 = puVar7;
    if (puVar7 == (undefined4 *)0x0) {
code_r0x015a3e50:
      *param_1 = -0x3bf;
    }
    else {
      *puVar7 = 5;
      memset(puVar7 + 2,0,0x61);
      Aska::Yayoi::IPAddress::IPAddress()(puVar7 + 0x1c);
      puVar5 = puStack_58;
      *(undefined1 *)(puVar7 + 0x3e) = 0;
      if (puStack_58 == (undefined4 *)0x0) goto code_r0x015a3e50;
      Aska::Yayoi::URI::Deserialize(char const*, unsigned short, Aska::Yayoi::AddressFamily, signed char*, unsigned long)(&lStack_60,puStack_58,param_3,param_4,0,0,0);
      lVar6 = lStack_60;
      if (lStack_60 < 0) goto code_r0x015a3e64;
      lVar6 = **(long **)puVar4;
      if (lVar6 == 0) {
        lVar6 = Aska::Global::GetAvailableMemoryManager()();
      }
      lVar6 = Aska::MemoryManager::Malloc(unsigned long)(lVar6,0x3f8);
      *(long *)(param_2 + 0x40) = lVar6;
      if (lVar6 == 0) goto code_r0x015a3e50;
      Aska::Yayoi::MatchingClient::MatchingClient()();
      lVar6 = *(long *)(param_2 + 0x40);
      if (lVar6 == 0) goto code_r0x015a3e50;
      puStack_70 = puVar5;
      do {
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar3) {
          *piVar8 = *piVar8 + 1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      piStack_68 = piVar8;
      Aska::Yayoi::MatchingClient::Init(Aska::TSharedPointer<Aska::Yayoi::URI>, Aska::Yayoi::IMatchingNotify*)(&lStack_60,lVar6,&puStack_70,param_5);
      lVar6 = lStack_60;
      puVar7 = puStack_70;
      if (piStack_68 == (int *)0x0) {
code_r0x015a3db0:
        if (puStack_70 != (undefined4 *)0x0) {
          Aska::Yayoi::URI::DeleteBuffer()(puStack_70);
          operator delete(void*)(puVar7);
        }
        if (piStack_68 != (int *)0x0) {
          Aska::TSharedPointerCode::DeleteCounter(int*)();
        }
      }
      else {
        do {
          iVar1 = *piStack_68;
          cVar2 = '\x01';
          bVar3 = (bool)ExclusiveMonitorPass(piStack_68,0x10);
          if (bVar3) {
            *piStack_68 = iVar1 + -1;
            cVar2 = ExclusiveMonitorsStatus();
          }
        } while (cVar2 != '\0');
        if (iVar1 + -1 == 0) goto code_r0x015a3db0;
      }
      puStack_70 = (undefined4 *)0x0;
      piStack_68 = (int *)0x0;
      if (lVar6 < 0) {
code_r0x015a3e64:
        *param_1 = lVar6;
      }
      else {
        lVar6 = *(long *)(param_2 + 0x40);
        *(undefined1 *)(lVar6 + 0x301) = 1;
        *(undefined8 *)(lVar6 + 0x304) = 0x500000001;
        *(undefined4 *)(lVar6 + 0x30c) = 6;
        if ((-1 < *(int *)(lVar6 + 0x19c)) &&
           (Aska::Yayoi::Socket::SetKeepAlive(bool, int, int, int)(&lStack_60,lVar6 + 0x19c,1,1,5,6), lVar6 = lStack_60, lStack_60 < 0))
        goto code_r0x015a3e64;
        *(long *)(param_2 + 0x50) = param_5;
        *param_1 = 0;
      }
    }
    if (piVar8 != (int *)0x0) {
      do {
        iVar1 = *piVar8;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piVar8,0x10);
        if (bVar3) {
          *piVar8 = iVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar1 != 1) {
        return;
      }
      bVar3 = false;
      puVar7 = puStack_58;
      goto joined_r0x015a3e9c;
    }
  }
  bVar3 = true;
  puVar7 = puStack_58;
joined_r0x015a3e9c:
  puStack_58 = puVar7;
  if (puVar7 != (undefined4 *)0x0) {
    Aska::Yayoi::URI::DeleteBuffer()(puVar7);
    operator delete(void*)(puVar7);
  }
  if (!bVar3) {
    Aska::TSharedPointerCode::DeleteCounter(int*)(piVar8);
  }
  return;
}

// ==== undefined CMultiplayManager::IsMultiplay(void)
// _ZNK17CMultiplayManager11IsMultiplayEv @ 015a190c

bool _ZNK17CMultiplayManager11IsMultiplayEv(long param_1)

{
  return *(long *)(param_1 + 0x38) != 0;
}

// ==== undefined CMultiplayManager::OnReceiveCommon(void)
// _ZN17CMultiplayManager15OnReceiveCommonEv @ 015a1c48

void _ZN17CMultiplayManager15OnReceiveCommonEv(long param_1)

{
  undefined8 uVar1;
  
  uVar1 = Aska::Global::GetCPUTime()();
  *(undefined8 *)(param_1 + 0x3b8) = uVar1;
  return;
}

// ==== undefined CMultiplayManager::OnStart(Aska::Status)
// _ZN17CMultiplayManager7OnStartEN4Aska6StatusE @ 015a1c60

void _ZN17CMultiplayManager7OnStartEN4Aska6StatusE(undefined8 *param_1)

{
  *param_1 = 0;
  return;
}

// ==== undefined CMultiplayManager::OnSnapshotRes(void const *,unsigned long)
// _ZN17CMultiplayManager13OnSnapshotResEPKvm @ 015a1ce4

void _ZN17CMultiplayManager13OnSnapshotResEPKvm(undefined8 *param_1,long param_2)

{
  if (*(long *)(param_2 + 0x38) != 0) {
    (*(code *)PTR__ZN4Aska5Yayoi21IMultiplayManagerBase15ReceiveSnapshotEPKvm_02cb6570)();
    return;
  }
  *param_1 = 0xfffffffffffffc44;
  return;
}

// ==== undefined CMultiplayManager::OnMessageRes(Aska::Yayoi::MultiplayRPC::Message const *,unsigned long)
// _ZN17CMultiplayManager12OnMessageResEPKN4Aska5Yayoi12MultiplayRPC7MessageEm @ 015a1d94

void _ZN17CMultiplayManager12OnMessageResEPKN4Aska5Yayoi12MultiplayRPC7MessageEm
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined8 param_4)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  
  puVar1 = PTR__ZN9Framework10TSingletonI18CBASMessageManagerE11m_pInstanceE_02cc44e8;
  if (*(long *)(param_2 + 0x38) == 0) {
    uVar3 = 0xfffffffffffffc44;
  }
  else {
    lVar2 = *(long *)PTR__ZN9Framework10TSingletonI18CBASMessageManagerE11m_pInstanceE_02cc44e8;
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar2 = *(long *)puVar1;
    }
    CBASMessageManager::DeliverMultiplayMessages(Aska::Yayoi::MultiplayRPC::Message const*, unsigned long)(lVar2,param_3,param_4);
    uVar3 = 0;
  }
  *param_1 = uVar3;
  return;
}

// ==== undefined CMultiplayManager::OnRSSIPush(float *)
// _ZN17CMultiplayManager10OnRSSIPushEPf @ 015a1e6c

void _ZN17CMultiplayManager10OnRSSIPushEPf(undefined8 *param_1,long param_2,undefined4 *param_3)

{
  undefined *puVar1;
  bool bVar2;
  long lVar3;
  int *piVar4;
  undefined4 uVar5;
  
  puVar1 = PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  lVar3 = CArena::rBattleManager()(lVar3);
  if ((*(byte *)(lVar3 + 0x20f0) & 1) == 0) {
    lVar3 = *(long *)puVar1;
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar3 = *(long *)puVar1;
    }
    piVar4 = (int *)CArena::rBattleManager()(lVar3);
    if (*piVar4 == 3) {
      bVar2 = (piVar4[1] | 1U) == 5;
      lVar3 = *(long *)puVar1;
    }
    else {
      bVar2 = false;
      lVar3 = *(long *)puVar1;
    }
  }
  else {
    bVar2 = true;
    lVar3 = *(long *)puVar1;
  }
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar1;
  }
  lVar3 = CArena::rBattleManager()(lVar3);
  if ((*(byte *)(lVar3 + 0x20f0) >> 6 & 1) == 0) {
    lVar3 = *(long *)puVar1;
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar3 = *(long *)puVar1;
    }
    piVar4 = (int *)CArena::rBattleManager()(lVar3);
    if (*piVar4 == 3) {
      if (bVar2 || (piVar4[1] | 1U) == 7) goto code_r0x015a1fd0;
    }
    else if (bVar2) goto code_r0x015a1fd0;
    *(undefined4 *)(param_2 + 0x3c8) = *param_3;
    *(undefined4 *)(param_2 + 0x3cc) = param_3[1];
    *(undefined4 *)(param_2 + 0x3d0) = param_3[2];
    uVar5 = param_3[3];
  }
  else {
code_r0x015a1fd0:
    uVar5 = 0x3f800000;
    *(undefined4 *)(param_2 + 0x3c8) = 0x3f800000;
    *(undefined4 *)(param_2 + 0x3cc) = 0x3f800000;
    *(undefined4 *)(param_2 + 0x3d0) = 0x3f800000;
  }
  *(undefined4 *)(param_2 + 0x3d4) = uVar5;
  *param_1 = 0;
  return;
}

// ==== undefined CMultiplayManager::OnDisconnectNodePush(signed,signed)
// _ZN17CMultiplayManager20OnDisconnectNodePushEaa @ 015a206c

void _ZN17CMultiplayManager20OnDisconnectNodePushEaa(undefined8 *param_1,long param_2,char param_3)

{
  *(undefined1 *)(param_2 + (ulong)(uint)(int)param_3 + 0x3dc) = 0;
  if (*(long *)PTR__ZN9Framework10TSingletonI13CStageManagerE11m_pInstanceE_02cc2fb0 != 0) {
    CStageManager::SetDisconnectPlayer(bool, int)(*(long *)PTR__ZN9Framework10TSingletonI13CStageManagerE11m_pInstanceE_02cc2fb0,1
                   );
  }
  *param_1 = 0;
  return;
}

// ==== undefined CMultiplayManager::OnStampPush(unsigned int,unsigned int)
// _ZN17CMultiplayManager11OnStampPushEjj @ 015a2100

void _ZN17CMultiplayManager11OnStampPushEjj
               (undefined8 *param_1,undefined8 param_2,undefined4 param_3,undefined4 param_4)

{
  CStampUI::OnStampPush(unsigned int, unsigned int)(param_3,param_4);
  *param_1 = 0;
  return;
}

// ==== undefined CMultiplayManager::OnMissionStartPush(unsigned char *,void const *,unsigned long)
// _ZN17CMultiplayManager18OnMissionStartPushEPhPKvm @ 015a219c

void _ZN17CMultiplayManager18OnMissionStartPushEPhPKvm
               (long *param_1,long param_2,char *param_3,undefined8 param_4,undefined8 param_5)

{
  undefined *puVar1;
  long *plVar2;
  long lVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  long lStack_48;
  undefined8 uStack_38;
  
  puVar1 = PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278;
  plVar2 = *(long **)PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278;
  uStack_38 = param_5;
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    plVar2 = *(long **)puVar1;
  }
  lVar3 = (**(code **)(*plVar2 + 0x698))();
  if (lVar3 == 0) {
    lStack_48 = -0x3bc;
  }
  else {
    CApiNotify::OnMissionStart(signed char*, unsigned int&)(&lStack_48,lVar3,param_4,&uStack_38);
    puVar1 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (-1 < lStack_48) {
      lVar3 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
      if (lVar3 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar3 = *(long *)puVar1;
      }
      lVar3 = CParameterManager::pParameterUI() const(lVar3);
      if (lVar3 != 0) {
        if (*param_3 == '\0') {
          uVar5 = 1;
          lVar3 = *(long *)puVar1;
        }
        else {
          lVar3 = *(long *)puVar1;
          if (lVar3 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
            lVar3 = *(long *)puVar1;
          }
          uVar4 = CParameterManager::pParameterUI() const(lVar3);
          CParameterUI::SetLoadingProgress(CParameterUI::LoadingPlayer, int)(uVar4,0,1);
          uVar5 = 0;
          lVar3 = *(long *)puVar1;
        }
        if (lVar3 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar3 = *(long *)puVar1;
        }
        uVar4 = CParameterManager::pParameterUI() const(lVar3);
        CParameterUI::SetLoadingDisconect(CParameterUI::LoadingPlayer, bool)(uVar4,0,uVar5);
        if (param_3[1] == '\0') {
          uVar5 = 1;
          lVar3 = *(long *)puVar1;
        }
        else {
          lVar3 = *(long *)puVar1;
          if (lVar3 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
            lVar3 = *(long *)puVar1;
          }
          uVar4 = CParameterManager::pParameterUI() const(lVar3);
          CParameterUI::SetLoadingProgress(CParameterUI::LoadingPlayer, int)(uVar4,1,1);
          uVar5 = 0;
          lVar3 = *(long *)puVar1;
        }
        if (lVar3 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar3 = *(long *)puVar1;
        }
        uVar4 = CParameterManager::pParameterUI() const(lVar3);
        uVar6 = 1;
        CParameterUI::SetLoadingDisconect(CParameterUI::LoadingPlayer, bool)(uVar4,1,uVar5);
        if (param_3[2] != '\0') {
          lVar3 = *(long *)puVar1;
          if (lVar3 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
            lVar3 = *(long *)puVar1;
          }
          uVar4 = CParameterManager::pParameterUI() const(lVar3);
          CParameterUI::SetLoadingProgress(CParameterUI::LoadingPlayer, int)(uVar4,2,1);
          uVar6 = 0;
        }
        lVar3 = *(long *)puVar1;
        if (lVar3 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar3 = *(long *)puVar1;
        }
        uVar4 = CParameterManager::pParameterUI() const(lVar3);
        CParameterUI::SetLoadingDisconect(CParameterUI::LoadingPlayer, bool)(uVar4,2,uVar6);
        if (param_3[3] == '\0') {
          uVar5 = 1;
          lVar3 = *(long *)puVar1;
        }
        else {
          lVar3 = *(long *)puVar1;
          if (lVar3 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
            lVar3 = *(long *)puVar1;
          }
          uVar4 = CParameterManager::pParameterUI() const(lVar3);
          CParameterUI::SetLoadingProgress(CParameterUI::LoadingPlayer, int)(uVar4,3,1);
          uVar5 = 0;
          lVar3 = *(long *)puVar1;
        }
        if (lVar3 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar3 = *(long *)puVar1;
        }
        uVar4 = CParameterManager::pParameterUI() const(lVar3);
        CParameterUI::SetLoadingDisconect(CParameterUI::LoadingPlayer, bool)(uVar4,3,uVar5);
      }
      lStack_48 = 0;
      *(undefined1 *)(param_2 + 0x3e0) = 1;
      *(undefined1 *)(param_2 + 0x3e4) = 1;
    }
  }
  *param_1 = lStack_48;
  return;
}

// ==== undefined CMultiplayManager::OnMissionEndPush(void const *,unsigned long)
// _ZN17CMultiplayManager16OnMissionEndPushEPKvm @ 015a24ec

void _ZN17CMultiplayManager16OnMissionEndPushEPKvm
               (long *param_1,long param_2,undefined8 param_3,undefined8 param_4)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  long *plVar4;
  long lStack_38;
  undefined8 uStack_28;
  
  puVar1 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  uStack_28 = param_4;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  uVar3 = CParameterManager::pParameterUI() const(lVar2);
  CParameterUI::SetNowloadingOnlineFlag(CParameterUI::eNowloadingOnline, bool)(uVar3,0,0);
  puVar1 = PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278;
  plVar4 = *(long **)PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278;
  if (plVar4 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    plVar4 = *(long **)puVar1;
  }
  lVar2 = (**(code **)(*plVar4 + 0x698))();
  if (lVar2 == 0) {
    lStack_38 = -0x3bc;
  }
  else {
    CApiNotify::OnMissionEnd(signed char*, unsigned int&)(&lStack_38,lVar2,param_3,&uStack_28);
    if (-1 < lStack_38) {
      lStack_38 = 0;
      *(undefined1 *)(param_2 + 0x3e0) = 0;
      *(undefined1 *)(param_2 + 0x3e1) = 1;
      *(undefined1 *)(param_2 + 0x3e5) = 1;
    }
  }
  *param_1 = lStack_38;
  return;
}

// ==== undefined CMultiplayManager::OnMissionContinueRes(void const *,unsigned long)
// _ZN17CMultiplayManager20OnMissionContinueResEPKvm @ 015a2638

void _ZN17CMultiplayManager20OnMissionContinueResEPKvm
               (long *param_1,long param_2,undefined8 param_3,undefined8 param_4)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  long *plVar4;
  long lStack_38;
  undefined8 uStack_28;
  
  puVar1 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  uStack_28 = param_4;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  uVar3 = CParameterManager::pParameterUI() const(lVar2);
  CParameterUI::SetNowloadingOnlineFlag(CParameterUI::eNowloadingOnline, bool)(uVar3,0,0);
  puVar1 = PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278;
  plVar4 = *(long **)PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278;
  if (plVar4 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    plVar4 = *(long **)puVar1;
  }
  lVar2 = (**(code **)(*plVar4 + 0x698))();
  if (lVar2 == 0) {
    lStack_38 = -0x3bc;
  }
  else {
    CApiNotify::DeserializeToInfo(signed char*, unsigned int&)(&lStack_38,lVar2,param_3,&uStack_28);
    if (-1 < lStack_38) {
      lStack_38 = 0;
      *(undefined1 *)(param_2 + 0x3e6) = 1;
    }
  }
  *param_1 = lStack_38;
  return;
}

// ==== undefined CMultiplayManager::OnStartBattleStageRes(unsigned char *)
// _ZN17CMultiplayManager21OnStartBattleStageResEPh @ 015a2774

void _ZN17CMultiplayManager21OnStartBattleStageResEPh
               (undefined8 *param_1,long param_2,char *param_3)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  
  if (*(long *)PTR__ZN9Framework10TSingletonI13CStageManagerE11m_pInstanceE_02cc2fb0 != 0) {
    *(undefined1 *)
     (*(long *)PTR__ZN9Framework10TSingletonI13CStageManagerE11m_pInstanceE_02cc2fb0 + 0x119) = 0;
  }
  puVar1 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  lVar2 = CParameterManager::pParameterUI() const(lVar2);
  if (lVar2 != 0) {
    if (*param_3 != '\0') {
      lVar2 = *(long *)puVar1;
      if (lVar2 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar2 = *(long *)puVar1;
      }
      uVar3 = CParameterManager::pParameterUI() const(lVar2);
      CParameterUI::SetLoadingProgress(CParameterUI::LoadingPlayer, int)(uVar3,0,2);
    }
    if (param_3[1] != '\0') {
      lVar2 = *(long *)puVar1;
      if (lVar2 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar2 = *(long *)puVar1;
      }
      uVar3 = CParameterManager::pParameterUI() const(lVar2);
      CParameterUI::SetLoadingProgress(CParameterUI::LoadingPlayer, int)(uVar3,1,2);
    }
    if (param_3[2] != '\0') {
      lVar2 = *(long *)puVar1;
      if (lVar2 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar2 = *(long *)puVar1;
      }
      uVar3 = CParameterManager::pParameterUI() const(lVar2);
      CParameterUI::SetLoadingProgress(CParameterUI::LoadingPlayer, int)(uVar3,2,2);
    }
    if (param_3[3] != '\0') {
      lVar2 = *(long *)puVar1;
      if (lVar2 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar2 = *(long *)puVar1;
      }
      uVar3 = CParameterManager::pParameterUI() const(lVar2);
      CParameterUI::SetLoadingProgress(CParameterUI::LoadingPlayer, int)(uVar3,3,2);
    }
  }
  lVar2 = *(long *)puVar1;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  uVar3 = CParameterManager::pParameterUI() const(lVar2);
  CParameterUI::SetNowloadingOnlineFlag(CParameterUI::eNowloadingOnline, bool)(uVar3,0,0);
  *(undefined1 *)(param_2 + 0x3e2) = 1;
  *param_1 = 0;
  return;
}

// ==== undefined CMultiplayManager::OnFinishBattleStageRes(void)
// _ZN17CMultiplayManager22OnFinishBattleStageResEv @ 015a2960

void _ZN17CMultiplayManager22OnFinishBattleStageResEv(undefined8 *param_1,long param_2)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  undefined *puVar5;
  long lVar6;
  undefined8 uVar7;
  long lVar8;
  long *plVar9;
  int iVar10;
  ulong uVar11;
  code *pcVar12;
  int *piVar13;
  uint uVar14;
  long *plVar15;
  long *plVar16;
  
  *(undefined1 *)(*(long *)(param_2 + 0x38) + 0x710) = 0;
  Aska::Yayoi::IMultiplayManagerBase::ClearAllMessage()(*(undefined8 *)(param_2 + 0x38));
  *(undefined1 *)(param_2 + 1000) = 0;
  puVar5 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar6 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar6 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar6 = *(long *)puVar5;
  }
  uVar7 = CParameterManager::pParameterUI() const(lVar6);
  CParameterUI::SetNowloadingOnlineFlag(CParameterUI::eNowloadingOnline, bool)(uVar7,0,0);
  piVar13 = (int *)(param_2 + 0xf8);
  iVar10 = 0;
  do {
    while (*piVar13 == -1) {
      cVar3 = '\x01';
      bVar4 = (bool)ExclusiveMonitorPass(piVar13,0x10);
      if (bVar4) {
        *piVar13 = 0;
        cVar3 = ExclusiveMonitorsStatus();
      }
      if (cVar3 == '\0') goto code_r0x015a2aa0;
    }
    ClearExclusiveLocal();
    bVar4 = iVar10 < 0x1ff;
    iVar10 = iVar10 + 1;
  } while (bVar4);
  piVar1 = (int *)(param_2 + 0xfc);
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + 1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
  do {
    if (*piVar13 != -1) {
      ClearExclusiveLocal();
      do {
        uVar11 = Aska::Semaphore::IsReady() const(param_2 + 0x138);
        if ((uVar11 & 1) == 0) {
          do {
            cVar3 = '\x01';
            bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar4) {
              *piVar1 = *piVar1 + -1;
              cVar3 = ExclusiveMonitorsStatus();
            }
          } while (cVar3 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_2 + 0x138);
        }
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar4) {
            *piVar1 = *piVar1 + 1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        while (*piVar13 == -1) {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar13,0x10);
          if (bVar4) {
            *piVar13 = 0;
            cVar3 = ExclusiveMonitorsStatus();
          }
          if (cVar3 == '\0') goto code_r0x015a2a90;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar13,0x10);
    if (bVar4) {
      *piVar13 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x015a2a90:
  do {
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar4) {
      *piVar1 = *piVar1 + -1;
      cVar3 = ExclusiveMonitorsStatus();
    }
  } while (cVar3 != '\0');
code_r0x015a2aa0:
  puVar5 = PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
  DataMemoryBarrier(2,3);
  plVar9 = *(long **)(param_2 + 0x168);
  do {
    if ((long *)(param_2 + 0x158U) == plVar9) {
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_2 + 0xf8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar13 = (int *)(param_2 + 0xfc);
      if (0x14 < *piVar13) {
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar13,0x10);
          if (bVar4) {
            *piVar13 = *piVar13 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar11 = Aska::Semaphore::IsReady() const(param_2 + 0x138);
        if ((uVar11 & 1) != 0) {
          Aska::Semaphore::Signal() const(param_2 + 0x138);
        }
      }
      if (*(long *)PTR__ZN9Framework10TSingletonI13CStageManagerE11m_pInstanceE_02cc2fb0 != 0) {
        *(undefined1 *)
         (*(long *)PTR__ZN9Framework10TSingletonI13CStageManagerE11m_pInstanceE_02cc2fb0 + 0x11a) =
             0;
      }
      *param_1 = 0;
      return;
    }
    plVar16 = (long *)plVar9[2];
    plVar15 = plVar16;
    if (*(long *)puVar5 != 0) {
      uVar7 = CArena::crPartyManager() const();
      lVar6 = CPartyManager::GetCharacter(int) const(uVar7,(long)(char)plVar9[3]);
      if (lVar6 != 0) {
        lVar8 = *(long *)puVar5;
        if (lVar8 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar8 = *(long *)puVar5;
        }
        CArena::rUIManager()(lVar8);
        uVar7 = CBattleUIManager::rBattleUI()();
        CBattle::RushComboUICancel(CCharacterObject const*)(uVar7,lVar6);
      }
      plVar15 = (long *)plVar9[2];
    }
    lVar6 = plVar9[1];
    if (lVar6 != 0) {
      *(long **)(lVar6 + 0x10) = plVar15;
    }
    if (plVar15 != (long *)0x0) {
      plVar15[1] = lVar6;
    }
    if (0 < *(int *)(param_2 + 0x178)) {
      *(int *)(param_2 + 0x178) = *(int *)(param_2 + 0x178) + -1;
    }
    plVar9[1] = 0;
    plVar9[2] = 0;
    if (plVar9 < *(long **)(param_2 + 0x188)) {
code_r0x015a2bb0:
      pcVar12 = *(code **)(*plVar9 + 8);
    }
    else {
      uVar11 = (long)plVar9 - (long)*(long **)(param_2 + 0x188);
      uVar14 = (uint)(uVar11 >> 5);
      if (3 < (int)uVar14) goto code_r0x015a2bb0;
      lVar6 = param_2 + (long)((int)uVar14 >> 5) * 4;
      uVar2 = *(uint *)(lVar6 + 0x184);
      uVar14 = 1 << (ulong)(uVar14 & 0x1f);
      if ((uVar2 & uVar14) == 0) goto code_r0x015a2bb0;
      *(uint *)(lVar6 + 0x184) = uVar2 & (uVar14 ^ 0xffffffff);
      plVar9 = (long *)(*(long *)(param_2 + 0x188) + ((long)(uVar11 * 0x8000000) >> 0x1b));
      pcVar12 = *(code **)*plVar9;
    }
    (*pcVar12)(plVar9);
    plVar9 = plVar16;
  } while( true );
}

// ==== undefined CMultiplayManager::OnForceWinBattleStagePush(void)
// _ZN17CMultiplayManager25OnForceWinBattleStagePushEv @ 015a2cb8

void _ZN17CMultiplayManager25OnForceWinBattleStagePushEv(undefined8 *param_1,long param_2)

{
  if (*(long *)PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968 != 0) {
    CArena::rBattleManager()();
    CBattleManager::ForceWinMultiBattle()();
  }
  *(undefined1 *)(*(long *)(param_2 + 0x38) + 0x710) = 0;
  Aska::Yayoi::IMultiplayManagerBase::ClearAllMessage()(*(undefined8 *)(param_2 + 0x38));
  *(undefined1 *)(param_2 + 1000) = 0;
  *param_1 = 0;
  return;
}

// ==== undefined CMultiplayManager::OnStartRushComboRes(signed,signed)
// _ZN17CMultiplayManager19OnStartRushComboResEaa @ 015a2d6c

void _ZN17CMultiplayManager19OnStartRushComboResEaa
               (undefined8 *param_1,long param_2,undefined1 param_3,undefined1 param_4)

{
  int *piVar1;
  undefined *puVar2;
  char cVar3;
  bool bVar4;
  code *pcVar5;
  uint uVar6;
  long *plVar7;
  ulong uVar8;
  int iVar9;
  undefined8 uVar10;
  int *piVar11;
  long lVar12;
  
  piVar11 = (int *)(param_2 + 0xf8);
  iVar9 = 0;
code_r0x015a2d94:
  do {
    if (*piVar11 != -1) {
      ClearExclusiveLocal();
      bVar4 = iVar9 < 0x1ff;
      iVar9 = iVar9 + 1;
      if (bVar4) goto code_r0x015a2d94;
      piVar1 = (int *)(param_2 + 0xfc);
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar4) {
          *piVar1 = *piVar1 + 1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
      do {
        if (*piVar11 != -1) {
          ClearExclusiveLocal();
          do {
            uVar8 = Aska::Semaphore::IsReady() const(param_2 + 0x138);
            if ((uVar8 & 1) == 0) {
              do {
                cVar3 = '\x01';
                bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
                if (bVar4) {
                  *piVar1 = *piVar1 + -1;
                  cVar3 = ExclusiveMonitorsStatus();
                }
              } while (cVar3 != '\0');
              Aska::Thread::Sleep(unsigned int)(1);
            }
            else {
              Aska::Semaphore::Wait() const(param_2 + 0x138);
            }
            do {
              cVar3 = '\x01';
              bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar4) {
                *piVar1 = *piVar1 + 1;
                cVar3 = ExclusiveMonitorsStatus();
              }
            } while (cVar3 != '\0');
            while (*piVar11 == -1) {
              cVar3 = '\x01';
              bVar4 = (bool)ExclusiveMonitorPass(piVar11,0x10);
              if (bVar4) {
                *piVar11 = 0;
                cVar3 = ExclusiveMonitorsStatus();
              }
              if (cVar3 == '\0') goto code_r0x015a2e4c;
            }
            ClearExclusiveLocal();
          } while( true );
        }
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar11,0x10);
        if (bVar4) {
          *piVar11 = 0;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x015a2e4c:
      do {
        cVar3 = '\x01';
        bVar4 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar4) {
          *piVar1 = *piVar1 + -1;
          cVar3 = ExclusiveMonitorsStatus();
        }
      } while (cVar3 != '\0');
code_r0x015a2e5c:
      DataMemoryBarrier(2,3);
      uVar6 = Aska::TPoolBase<CMultiplayManager::StartRushComboElement, Aska::TPool<CMultiplayManager::StartRushComboElement, 4> >::SetWithCount(int)(param_2 + 0x180,1);
      if (uVar6 == 4) {
code_r0x015a2e9c:
        plVar7 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x20,PTR__ZSt7nothrow_02cb9a80);
        if (plVar7 == (long *)0x0) {
          uVar10 = 0xfffffffffffffc3f;
          goto code_r0x015a2ef8;
        }
        plVar7[2] = 0;
        *plVar7 = (long)(PTR__ZTVN17CMultiplayManager21StartRushComboElementE_02cb8978 + 0x10);
        plVar7[1] = 0;
      }
      else {
        if (3 < uVar6) {
          uRam0000000000000010 = 0;
          uRam0000000000000008 = 0;
                    /* WARNING: Does not return */
          pcVar5 = (code *)SoftwareBreakpoint(1,0x15a2f7c);
          (*pcVar5)();
        }
        plVar7 = (long *)(*(long *)(param_2 + 0x188) + (long)(int)uVar6 * 0x20);
        puVar2 = PTR__ZTVN17CMultiplayManager21StartRushComboElementE_02cb8978 + 0x10;
        plVar7[1] = 0;
        plVar7[2] = 0;
        *plVar7 = (long)puVar2;
        if (plVar7 == (long *)0x0) goto code_r0x015a2e9c;
      }
      *(undefined1 *)(plVar7 + 3) = param_3;
      *(undefined1 *)((long)plVar7 + 0x19) = param_4;
      lVar12 = *(long *)(param_2 + 0x160);
      uVar10 = 0;
      plVar7[1] = lVar12;
      plVar7[2] = param_2 + 0x158;
      *(long **)(param_2 + 0x160) = plVar7;
      *(long **)(lVar12 + 0x10) = plVar7;
      *(int *)(param_2 + 0x178) = *(int *)(param_2 + 0x178) + 1;
code_r0x015a2ef8:
      *param_1 = uVar10;
      DataMemoryBarrier(2,3);
      *(undefined4 *)(param_2 + 0xf8) = 0xffffffff;
      DataMemoryBarrier(2,3);
      piVar11 = (int *)(param_2 + 0xfc);
      if (0x14 < *piVar11) {
        do {
          cVar3 = '\x01';
          bVar4 = (bool)ExclusiveMonitorPass(piVar11,0x10);
          if (bVar4) {
            *piVar11 = *piVar11 + -1;
            cVar3 = ExclusiveMonitorsStatus();
          }
        } while (cVar3 != '\0');
        uVar8 = Aska::Semaphore::IsReady() const(param_2 + 0x138);
        if ((uVar8 & 1) != 0) {
          (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_2 + 0x138);
          return;
        }
      }
      return;
    }
    cVar3 = '\x01';
    bVar4 = (bool)ExclusiveMonitorPass(piVar11,0x10);
    if (bVar4) {
      *piVar11 = 0;
      cVar3 = ExclusiveMonitorsStatus();
    }
    if (cVar3 == '\0') goto code_r0x015a2e5c;
  } while( true );
}

// ==== undefined CMultiplayManager::OnSyncStartRushComboRes(signed,signed,unsigned char,unsigned char,float,unsigned int)
// _ZN17CMultiplayManager23OnSyncStartRushComboResEaahhfj @ 015a3028

void _ZN17CMultiplayManager23OnSyncStartRushComboResEaahhfj
               (undefined8 *param_1,undefined4 param_2,long param_3,char param_4,char param_5,
               char param_6,char param_7,undefined4 param_8)

{
  char cVar1;
  ulong uVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined8 uVar5;
  long lVar6;
  int *piVar7;
  ulong uVar8;
  ulong uVar9;
  long lVar10;
  int iVar11;
  undefined *puStack_90;
  undefined4 uStack_88;
  undefined8 uStack_80;
  undefined4 uStack_78;
  int iStack_74;
  int iStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  char acStack_58 [4];
  char acStack_54 [4];
  
  *(undefined8 *)(param_3 + 0x3c0) = 0;
  puVar3 = PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
  if (*(long *)PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968 == 0)
  goto code_r0x015a3388;
  uVar5 = CArena::crPartyManager() const();
  lVar6 = CPartyManager::GetCharacter(int) const(uVar5,(int)param_4);
  if (param_6 == '\0') {
    if (lVar6 != 0) {
      lVar10 = *(long *)puVar3;
      if (lVar10 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar10 = *(long *)puVar3;
      }
      CArena::rUIManager()(lVar10);
      uVar5 = CBattleUIManager::rBattleUI()();
      CBattle::RushComboUICancel(CCharacterObject const*)(uVar5,lVar6);
    }
    lVar6 = *(long *)puVar3;
    if (lVar6 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar6 = *(long *)puVar3;
    }
    lVar6 = CArena::rBattleManager()(lVar6);
    *(undefined1 *)(lVar6 + 0x210d) = 0;
    lVar6 = *(long *)puVar3;
  }
  else {
    puStack_90 = (undefined *)CONCAT71(puStack_90._1_7_,param_5);
    uVar8 = *(ulong *)(param_3 + 0xb8);
    if (uVar8 != 0) {
      uVar9 = 0;
      do {
        uVar2 = 0;
        if (uVar8 != 0) {
          uVar2 = ((long)param_5 + uVar9) / uVar8;
        }
        lVar10 = ((long)param_5 + uVar9) - uVar2 * uVar8;
        cVar1 = *(char *)(*(long *)(param_3 + 0xb0) + lVar10 * 0xc);
        if (cVar1 == '\x01') {
          if (*(char *)(*(long *)(param_3 + 0xb0) + lVar10 * 0xc + 4) == param_5) {
            piVar7 = (int *)Aska::THashMap<signed char, unsigned int, Aska::THasher<signed char>, Aska::TEqualTo<signed char>, Aska::TAllocator<Aska::TPair<signed char const, unsigned int> > >::operator[](signed char const&)(param_3 + 0x90,&puStack_90);
            iVar11 = *piVar7;
            lVar10 = *(long *)puVar3;
            goto joined_r0x015a33bc;
          }
        }
        else if (cVar1 == '\0') break;
        uVar9 = uVar9 + 1;
      } while (uVar9 < uVar8);
    }
    iVar11 = 0;
    lVar10 = *(long *)puVar3;
joined_r0x015a33bc:
    if (lVar10 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar10 = *(long *)puVar3;
    }
    CArena::rUIManager()(lVar10);
    uVar5 = CBattleUIManager::rBattleUI()();
    CBattle::RushComboInfoStart(unsigned int)(uVar5,(int)param_4);
    puVar4 = PTR__ZN9Framework10TSingletonI18CBASMessageManagerE11m_pInstanceE_02cc44e8;
    if (param_7 == '\0') {
      uStack_80 = *(undefined8 *)(lVar6 + 0x60);
      uStack_88 = 0x19;
      puStack_90 = PTR__ZTV28CFieldMessage_StartRushCombo_02cbb638 + 0x10;
      iStack_70 = (int)*(float *)(lVar6 + 0x1d68);
      lVar10 = *(long *)PTR__ZN9Framework10TSingletonI18CBASMessageManagerE11m_pInstanceE_02cc44e8;
      uStack_78 = 0;
      uStack_6c = 10;
      iStack_74 = iVar11;
      uStack_68 = param_8;
      if (lVar10 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar10 = *(long *)puVar4;
      }
      if (((*(long *)PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908 == 0)
          || (lVar6 = *(long *)(*(long *)
                                 PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908
                               + 0x38), lVar6 == 0)) || (*(char *)(lVar6 + 0x710) == '\0')) {
        void Framework::CMessageManager::SendMessage<CFieldMessage_StartRushCombo>(CFieldMessage_StartRushCombo const&)(lVar10 + 0x38,&puStack_90);
      }
      else {
        acStack_54[0] = '\0';
        acStack_58[0] = '\0';
        CBASMessageManager::AssortMessage(CBASMessageBase const*, bool*, bool*)(lVar10,&puStack_90,acStack_54,acStack_58);
        if (acStack_54[0] != '\0') {
          void Framework::CMessageManager::SendMessage<CFieldMessage_StartRushCombo>(CFieldMessage_StartRushCombo const&)(lVar10 + 0x38,&puStack_90);
        }
        if (acStack_58[0] != '\0') goto code_r0x015a3358;
      }
code_r0x015a3378:
      lVar6 = *(long *)puVar3;
    }
    else {
      uStack_80 = *(undefined8 *)(lVar6 + 0x60);
      uStack_88 = 0x19;
      puStack_90 = PTR__ZTV35CFieldMessage_RideTogetherRushCombo_02cb7fb0 + 0x10;
      lVar10 = *(long *)PTR__ZN9Framework10TSingletonI18CBASMessageManagerE11m_pInstanceE_02cc44e8;
      iStack_74 = (int)*(float *)(lVar6 + 0x1d68);
      uStack_78 = 0;
      if (lVar10 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar10 = *(long *)puVar4;
      }
      if (((*(long *)PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908 == 0)
          || (lVar6 = *(long *)(*(long *)
                                 PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908
                               + 0x38), lVar6 == 0)) || (*(char *)(lVar6 + 0x710) == '\0')) {
        void Framework::CMessageManager::SendMessage<CFieldMessage_RideTogetherRushCombo>(CFieldMessage_RideTogetherRushCombo const&)(lVar10 + 0x38,&puStack_90);
        lVar6 = *(long *)puVar3;
      }
      else {
        acStack_54[0] = '\0';
        acStack_58[0] = '\0';
        CBASMessageManager::AssortMessage(CBASMessageBase const*, bool*, bool*)(lVar10,&puStack_90,acStack_54,acStack_58);
        if (acStack_54[0] != '\0') {
          void Framework::CMessageManager::SendMessage<CFieldMessage_RideTogetherRushCombo>(CFieldMessage_RideTogetherRushCombo const&)(lVar10 + 0x38,&puStack_90);
        }
        if (acStack_58[0] == '\0') goto code_r0x015a3378;
code_r0x015a3358:
        CBASMessageManager::SendMultiplayMessage(CBASMessageBase const*, bool)(lVar10,&puStack_90,0);
        lVar6 = *(long *)puVar3;
      }
    }
  }
  if (lVar6 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar6 = *(long *)puVar3;
  }
  lVar6 = CArena::rBattleManager()(lVar6);
  *(undefined4 *)(lVar6 + 0x2108) = param_2;
code_r0x015a3388:
  *param_1 = 0;
  return;
}

// ==== undefined CMultiplayManager::OnSyncFinishRushComboRes(float,int,unsigned char)
// _ZN17CMultiplayManager24OnSyncFinishRushComboResEfih @ 015a3440

void _ZN17CMultiplayManager24OnSyncFinishRushComboResEfih
               (undefined8 *param_1,undefined4 param_2,long param_3,undefined4 param_4,char param_5)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  
  *(undefined8 *)(param_3 + 0x3c0) = 0;
  puVar1 = PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
  if (*(long *)PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968 != 0) {
    lVar2 = CArena::rBattleManager()();
    *(undefined4 *)(lVar2 + 0x2108) = param_2;
    lVar2 = *(long *)puVar1;
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar2 = *(long *)puVar1;
    }
    uVar3 = CArena::rBattleManager()(lVar2);
    CBattleManager::SetRushComboTotalDamage(int)(uVar3,param_4);
    lVar2 = *(long *)puVar1;
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar2 = *(long *)puVar1;
    }
    lVar2 = CArena::rBattleManager()(lVar2);
    *(bool *)(lVar2 + 0x2110) = param_5 != '\0';
    lVar2 = *(long *)puVar1;
    if (lVar2 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar2 = *(long *)puVar1;
    }
    lVar2 = CArena::rBattleManager()(lVar2);
    *(undefined1 *)(lVar2 + 0x210e) = 0;
  }
  *param_1 = 0;
  return;
}

// ==== undefined CMultiplayManager::OnAIParameterRes(Aska::Yayoi::MO::HateParameter *,unsigned long)
// _ZN17CMultiplayManager16OnAIParameterResEPN4Aska5Yayoi2MO13HateParameterEm @ 015a3670

void _ZN17CMultiplayManager16OnAIParameterResEPN4Aska5Yayoi2MO13HateParameterEm
               (undefined8 *param_1,long param_2,long param_3,ulong param_4)

{
  long *plVar1;
  long lVar2;
  undefined8 uVar3;
  undefined4 *puVar4;
  ulong uVar5;
  int *piVar6;
  long lVar7;
  long lVar8;
  
  if (*(int *)(param_2 + 0x3d8) == 0) {
    if (*(long *)PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968 == 0) {
      uVar3 = 0;
    }
    else {
      lVar2 = CArena::rBattleManager()();
      uVar3 = 0;
      if ((param_3 != 0) && (param_4 != 0)) {
        uVar5 = 0;
        do {
          plVar1 = (long *)(param_3 + uVar5 * 0x10);
          if ((3 < *(int *)((long)plVar1 + 0xc)) ||
             (puVar4 = (undefined4 *)*plVar1, puVar4 == (undefined4 *)0x0)) {
code_r0x015a378c:
            uVar3 = 0xfffffffffffffc43;
            break;
          }
          piVar6 = (int *)(param_3 + uVar5 * 0x10 + 8);
          if (*piVar6 == 0) goto code_r0x015a378c;
          if ((0 < *piVar6) && (CAITargetManager::DirectSetHate(int, int, float)(puVar4[1],lVar2 + 0x1554,*puVar4), 1 < *piVar6)) {
            lVar7 = 0;
            lVar8 = 1;
            do {
              CAITargetManager::DirectSetHate(int, int, float)(*(undefined4 *)(*plVar1 + lVar7 + 0xc),lVar2 + 0x1554,
                              *(undefined4 *)(*plVar1 + lVar7 + 8),*(int *)((long)plVar1 + 0xc));
              lVar8 = lVar8 + 1;
              lVar7 = lVar7 + 8;
            } while (lVar8 < *piVar6);
          }
          uVar5 = uVar5 + 1;
          uVar3 = 0;
        } while (uVar5 < param_4);
      }
    }
  }
  else {
    uVar3 = 0xfffffffffffffc44;
  }
  *param_1 = uVar3;
  return;
}

// ==== undefined CMultiplayManager::Initialize(char const *,unsigned short,Aska::Yayoi::IMatchingNotify *)
// _ZN17CMultiplayManager10InitializeEPKctPN4Aska5Yayoi15IMatchingNotifyE @ 015a3bf4

void _ZN17CMultiplayManager10InitializeEPKctPN4Aska5Yayoi15IMatchingNotifyE(long *param_1)

{
  undefined8 uVar1;
  long lStack_18;
  
  CMultiplayManager::InitMatchingClient(char const*, unsigned short, Aska::Yayoi::IMatchingNotify*)(&lStack_18);
  if (-1 < lStack_18) {
    uVar1 = Aska::OBJParamList::GetOBJParamList()();
    Aska::OBJParamList::Register(Aska::AskaOBJParamList::tagClassDesc const*)(uVar1,&UNK_02ac67e8);
    lStack_18 = 0;
  }
  *param_1 = lStack_18;
  return;
}

// ==== undefined CMultiplayManager::Progress(void)
// _ZN17CMultiplayManager8ProgressEv @ 015a43b8

/* WARNING: Type propagation algorithm not settling */

void _ZN17CMultiplayManager8ProgressEv(long param_1)

{
  int *piVar1;
  long *plVar2;
  undefined8 *puVar3;
  uint uVar4;
  undefined1 uVar5;
  char cVar6;
  char cVar7;
  bool bVar8;
  undefined *puVar9;
  undefined *puVar10;
  bool bVar11;
  uint uVar12;
  long lVar13;
  undefined8 uVar14;
  int *piVar15;
  ulong uVar16;
  ulong uVar17;
  long lVar18;
  undefined4 *puVar19;
  undefined8 uVar20;
  int iVar21;
  long lVar22;
  code *pcVar23;
  ulong uVar24;
  long *plVar25;
  long *plVar26;
  undefined4 uVar27;
  undefined8 uStack_250;
  undefined *puStack_248;
  undefined4 uStack_240;
  undefined8 uStack_238;
  undefined4 uStack_230;
  undefined8 uStack_22c;
  undefined8 uStack_224;
  undefined8 uStack_21c;
  undefined8 uStack_214;
  undefined8 uStack_20c;
  undefined8 uStack_204;
  undefined8 uStack_1fc;
  undefined8 uStack_1f4;
  undefined8 uStack_1ec;
  undefined8 uStack_1e4;
  undefined8 uStack_1dc;
  undefined8 uStack_1d4;
  undefined8 uStack_1cc;
  undefined8 uStack_1c4;
  undefined8 uStack_1bc;
  undefined8 uStack_1b4;
  undefined1 uStack_1ac;
  undefined1 uStack_1ab;
  undefined8 uStack_148;
  undefined4 auStack_140 [22];
  undefined1 auStack_e8 [64];
  undefined1 auStack_a8 [64];
  char acStack_68 [4];
  char acStack_64 [4];
  
  puVar9 = PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
  if (*(char *)(param_1 + 0x3e2) == '\0') goto code_r0x015a45f0;
  iVar21 = *(int *)(param_1 + 0x3d8);
  if (iVar21 == 0) {
code_r0x015a43f8:
    if (*(char *)(param_1 + 0x3dd) != '\0') goto code_r0x015a4420;
    if (iVar21 != 2) goto code_r0x015a4408;
code_r0x015a4418:
    if (*(char *)(param_1 + 0x3df) != '\0') goto code_r0x015a4420;
code_r0x015a4480:
    bVar11 = false;
    bVar8 = false;
    if (*(long *)(param_1 + 0x3c0) == 0) goto code_r0x015a448c;
code_r0x015a442c:
    if ((bVar11) &&
       (lVar13 = Aska::Global::GetCPUTime()(), 0x4af < (ulong)(lVar13 - *(long *)(param_1 + 0x3c0)))) {
code_r0x015a4444:
      puVar9 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
      lVar13 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
      if (lVar13 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar13 = *(long *)puVar9;
      }
      uVar14 = CParameterManager::pParameterUI() const(lVar13);
      uVar20 = 1;
    }
    else {
code_r0x015a45b4:
      puVar9 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
      lVar13 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
      if (lVar13 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar13 = *(long *)puVar9;
      }
      uVar14 = CParameterManager::pParameterUI() const(lVar13);
      uVar20 = 0;
    }
    CParameterUI::SetNowloadingOnlineFlag(CParameterUI::eNowloadingOnline, bool)(uVar14,0,uVar20);
  }
  else {
    if (*(char *)(param_1 + 0x3dc) == '\0') {
      if (iVar21 != 1) goto code_r0x015a43f8;
code_r0x015a4408:
      if (*(char *)(param_1 + 0x3de) == '\0') {
        if (iVar21 != 3) goto code_r0x015a4418;
        goto code_r0x015a4480;
      }
    }
code_r0x015a4420:
    bVar11 = true;
    bVar8 = bVar11;
    if (*(long *)(param_1 + 0x3c0) != 0) goto code_r0x015a442c;
code_r0x015a448c:
    lVar13 = *(long *)PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
    if (lVar13 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar13 = *(long *)puVar9;
    }
    lVar13 = CArena::rBattleManager()(lVar13);
    if ((*(byte *)(lVar13 + 0x20f0) & 1) == 0) {
      lVar13 = *(long *)puVar9;
      if (lVar13 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar13 = *(long *)puVar9;
      }
      piVar15 = (int *)CArena::rBattleManager()(lVar13);
      if (*piVar15 == 3) {
        bVar11 = (piVar15[1] | 1U) == 5;
        lVar13 = *(long *)puVar9;
      }
      else {
        bVar11 = false;
        lVar13 = *(long *)puVar9;
      }
    }
    else {
      bVar11 = true;
      lVar13 = *(long *)puVar9;
    }
    if (lVar13 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar13 = *(long *)puVar9;
    }
    lVar13 = CArena::rBattleManager()(lVar13);
    if ((*(byte *)(lVar13 + 0x20f0) >> 6 & 1) == 0) {
      lVar13 = *(long *)puVar9;
      if (lVar13 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar13 = *(long *)puVar9;
      }
      piVar15 = (int *)CArena::rBattleManager()(lVar13);
      if (*piVar15 != 3) {
        if (!bVar11) goto code_r0x015a459c;
        goto code_r0x015a45f0;
      }
      if (bVar11 || (piVar15[1] | 1U) == 7) goto code_r0x015a45f0;
code_r0x015a459c:
      if ((!bVar8) ||
         (lVar13 = Aska::Global::GetCPUTime()(), (ulong)(lVar13 - *(long *)(param_1 + 0x3b8)) < 0x9c4))
      goto code_r0x015a45b4;
      goto code_r0x015a4444;
    }
  }
code_r0x015a45f0:
  puVar9 = PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
  if ((*(char *)(param_1 + 1000) == '\0') ||
     (*(long *)PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968 == 0))
  goto code_r0x015a4d9c;
  lVar13 = Aska::Global::GetCPUTime()();
  if (299 < (ulong)(lVar13 - *(long *)(param_1 + 0x330))) {
    uVar16 = CMultiplayManager::PackCharacterParameterPlayer(CMultiplayManager::CharacterParameterPlayer*)(param_1,auStack_a8);
    uVar17 = CMultiplayManager::PackCharacterParameterEnemy(CMultiplayManager::CharacterParameterEnemy*)(param_1,auStack_e8);
    lVar13 = 0;
    uVar24 = 0;
    do {
      lVar22 = param_1 + lVar13;
      cVar7 = *(char *)(lVar22 + 0x346);
      if (-1 < cVar7) {
        lVar18 = uVar24 * 8;
        puVar3 = &uStack_148 + uVar24;
        uVar24 = uVar24 + 1;
        *(undefined4 *)puVar3 = *(undefined4 *)(lVar22 + 0x340);
        *(undefined1 *)((long)&uStack_148 + lVar18 + 4) = *(undefined1 *)(lVar22 + 0x344);
        uVar5 = *(undefined1 *)(lVar22 + 0x345);
        *(char *)((long)&uStack_148 + lVar18 + 6) = cVar7;
        *(undefined1 *)((long)&uStack_148 + lVar18 + 5) = uVar5;
        *(undefined4 *)(lVar22 + 0x340) = 0;
        *(undefined2 *)(lVar22 + 0x344) = 0xff00;
        *(undefined1 *)(lVar22 + 0x346) = 0xff;
      }
      puVar10 = PTR__ZN9Framework10TSingletonI18CBASMessageManagerE11m_pInstanceE_02cc44e8;
      lVar13 = lVar13 + 8;
    } while (lVar13 != 0x60);
    if (*(char *)(param_1 + 0x3ac) != '\0') {
      iVar21 = *(int *)(param_1 + 0x3a0);
      if ((0 < iVar21) ||
         ((*(int *)(param_1 + 0x3d8) == 0 && ((iVar21 == 0 || (*(int *)(param_1 + 0x3a8) != 0))))))
      {
        uStack_238 = *(undefined8 *)(param_1 + 0x2b0);
        uStack_240 = 0x25;
        puStack_248 = PTR__ZTV39CFieldMessage_Multiplay_SystemParameter_02cbef88 + 0x10;
        lVar13 = *(long *)PTR__ZN9Framework10TSingletonI18CBASMessageManagerE11m_pInstanceE_02cc44e8
        ;
        uStack_230 = 1;
        uStack_22c = CONCAT44(*(undefined4 *)(param_1 + 0x3a4),iVar21);
        uStack_224 = CONCAT44(uStack_224._4_4_,*(undefined4 *)(param_1 + 0x3a8));
        if (lVar13 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar13 = *(long *)puVar10;
        }
        if (((*(long *)PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908 ==
              0) || (lVar22 = *(long *)(*(long *)
                                         PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908
                                       + 0x38), lVar22 == 0)) || (*(char *)(lVar22 + 0x710) == '\0')
           ) {
          void Framework::CMessageManager::SendMessage<CFieldMessage_Multiplay_SystemParameter>(CFieldMessage_Multiplay_SystemParameter const&)(lVar13 + 0x38,&puStack_248);
        }
        else {
          acStack_64[0] = '\0';
          acStack_68[0] = '\0';
          CBASMessageManager::AssortMessage(CBASMessageBase const*, bool*, bool*)(lVar13,&puStack_248,acStack_64,acStack_68);
          if (acStack_64[0] != '\0') {
            void Framework::CMessageManager::SendMessage<CFieldMessage_Multiplay_SystemParameter>(CFieldMessage_Multiplay_SystemParameter const&)(lVar13 + 0x38,&puStack_248);
          }
          if (acStack_68[0] != '\0') {
            CBASMessageManager::SendMultiplayMessage(CBASMessageBase const*, bool)(lVar13,&puStack_248,0);
          }
        }
      }
      *(undefined1 *)(param_1 + 0x3ac) = 0;
    }
    puVar10 = PTR__ZN9Framework10TSingletonI18CBASMessageManagerE11m_pInstanceE_02cc44e8;
    if (*(char *)(param_1 + 0x3b4) != '\0') {
      if (*(int *)(param_1 + 0x3d8) == 0) {
        uStack_238 = *(undefined8 *)(param_1 + 0x2f8);
        uStack_240 = 0x26;
        lVar13 = *(long *)PTR__ZN9Framework10TSingletonI18CBASMessageManagerE11m_pInstanceE_02cc44e8
        ;
        puStack_248 = PTR__ZTV34CFieldMessage_Multiplay_BattleTime_02cba130 + 0x10;
        uStack_230 = 1;
        uStack_22c = CONCAT44(uStack_22c._4_4_,*(undefined4 *)(param_1 + 0x3b0));
        if (lVar13 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar13 = *(long *)puVar10;
        }
        if (((*(long *)PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908 ==
              0) || (lVar22 = *(long *)(*(long *)
                                         PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908
                                       + 0x38), lVar22 == 0)) || (*(char *)(lVar22 + 0x710) == '\0')
           ) {
          void Framework::CMessageManager::SendMessage<CFieldMessage_Multiplay_BattleTime>(CFieldMessage_Multiplay_BattleTime const&)(lVar13 + 0x38,&puStack_248);
        }
        else {
          acStack_64[0] = '\0';
          acStack_68[0] = '\0';
          CBASMessageManager::AssortMessage(CBASMessageBase const*, bool*, bool*)(lVar13,&puStack_248,acStack_64,acStack_68);
          if (acStack_64[0] != '\0') {
            void Framework::CMessageManager::SendMessage<CFieldMessage_Multiplay_BattleTime>(CFieldMessage_Multiplay_BattleTime const&)(lVar13 + 0x38,&puStack_248);
          }
          if (acStack_68[0] != '\0') {
            CBASMessageManager::SendMultiplayMessage(CBASMessageBase const*, bool)(lVar13,&puStack_248,0);
          }
        }
      }
      *(undefined1 *)(param_1 + 0x3b4) = 0;
    }
    if (uVar16 + uVar17 != 0) {
      uStack_238 = *(undefined8 *)(param_1 + 0x220);
      uStack_240 = 0x23;
      puStack_248 = PTR__ZTV42CFieldMessage_Multiplay_CharacterParameter_02cc43d0 + 0x10;
      uStack_230 = 1;
      if (((uint)uVar16 & 0xff) < 5) {
        memcpy(&uStack_22c,auStack_a8,(uVar16 & 0xff) << 4);
      }
      else {
        uStack_204 = 0;
        uStack_20c = 0;
        uStack_1f4 = 0;
        uStack_1fc = 0;
        uStack_224 = 0;
        uStack_22c = 0;
        uStack_214 = 0;
        uStack_21c = 0;
      }
      if (((uint)uVar17 & 0xff) < 9) {
        memcpy(&uStack_1ec,auStack_e8,(uVar17 & 0xff) << 3);
      }
      else {
        uStack_1c4 = 0;
        uStack_1cc = 0;
        uStack_1b4 = 0;
        uStack_1bc = 0;
        uStack_1e4 = 0;
        uStack_1ec = 0;
        uStack_1d4 = 0;
        uStack_1dc = 0;
      }
      puVar10 = PTR__ZN9Framework10TSingletonI18CBASMessageManagerE11m_pInstanceE_02cc44e8;
      uStack_1ac = (undefined1)uVar16;
      uStack_1ab = (undefined1)uVar17;
      lVar13 = *(long *)PTR__ZN9Framework10TSingletonI18CBASMessageManagerE11m_pInstanceE_02cc44e8;
      if (lVar13 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar13 = *(long *)puVar10;
      }
      if (((*(long *)PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908 == 0)
          || (lVar22 = *(long *)(*(long *)
                                  PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908
                                + 0x38), lVar22 == 0)) || (*(char *)(lVar22 + 0x710) == '\0')) {
        void Framework::CMessageManager::SendMessage<CFieldMessage_Multiplay_CharacterParameter>(CFieldMessage_Multiplay_CharacterParameter const&)(lVar13 + 0x38,&puStack_248);
      }
      else {
        acStack_64[0] = '\0';
        acStack_68[0] = '\0';
        CBASMessageManager::AssortMessage(CBASMessageBase const*, bool*, bool*)(lVar13,&puStack_248,acStack_64,acStack_68);
        if (acStack_64[0] != '\0') {
          void Framework::CMessageManager::SendMessage<CFieldMessage_Multiplay_CharacterParameter>(CFieldMessage_Multiplay_CharacterParameter const&)(lVar13 + 0x38,&puStack_248);
        }
        if (acStack_68[0] != '\0') {
          CBASMessageManager::SendMultiplayMessage(CBASMessageBase const*, bool)(lVar13,&puStack_248,0);
        }
      }
    }
    if (uVar24 != 0) {
      uStack_238 = *(undefined8 *)(param_1 + 0x268);
      uStack_240 = 0x24;
      puStack_248 = PTR__ZTV41CFieldMessage_Multiplay_DamageUIParameter_02cb7128 + 0x10;
      uStack_230 = 1;
      if ((uint)uVar24 < 0xd) {
        memcpy(&uStack_22c,&uStack_148,(uVar24 & 0xffffffff) << 3);
      }
      else {
        memset(&uStack_22c,0,0x60);
      }
      puVar10 = PTR__ZN9Framework10TSingletonI18CBASMessageManagerE11m_pInstanceE_02cc44e8;
      uStack_1cc = CONCAT44(uStack_1cc._4_4_,(uint)uVar24);
      lVar13 = *(long *)PTR__ZN9Framework10TSingletonI18CBASMessageManagerE11m_pInstanceE_02cc44e8;
      if (lVar13 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar13 = *(long *)puVar10;
      }
      if (((*(long *)PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908 == 0)
          || (lVar22 = *(long *)(*(long *)
                                  PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908
                                + 0x38), lVar22 == 0)) || (*(char *)(lVar22 + 0x710) == '\0')) {
        void Framework::CMessageManager::SendMessage<CFieldMessage_Multiplay_DamageUIParameter>(CFieldMessage_Multiplay_DamageUIParameter const&)(lVar13 + 0x38,&puStack_248);
      }
      else {
        acStack_64[0] = '\0';
        acStack_68[0] = '\0';
        CBASMessageManager::AssortMessage(CBASMessageBase const*, bool*, bool*)(lVar13,&puStack_248,acStack_64,acStack_68);
        if (acStack_64[0] != '\0') {
          void Framework::CMessageManager::SendMessage<CFieldMessage_Multiplay_DamageUIParameter>(CFieldMessage_Multiplay_DamageUIParameter const&)(lVar13 + 0x38,&puStack_248);
        }
        if (acStack_68[0] != '\0') {
          CBASMessageManager::SendMultiplayMessage(CBASMessageBase const*, bool)(lVar13,&puStack_248,0);
        }
      }
    }
    uVar14 = Aska::Global::GetCPUTime()();
    *(undefined8 *)(param_1 + 0x330) = uVar14;
  }
  if ((*(int *)(param_1 + 0x3d8) == 0) ||
     (lVar13 = Aska::Global::GetCPUTime()(), (ulong)(lVar13 - *(long *)(param_1 + 0x338)) < 2000))
  goto code_r0x015a4d9c;
  lVar13 = *(long *)puVar9;
  if (lVar13 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar13 = *(long *)puVar9;
  }
  uVar14 = CArena::rPartyManager()(lVar13);
  uVar24 = CPartyManager::IsMultiplaySendCharacter(int)(uVar14,0);
  if ((uVar24 & 1) == 0) {
code_r0x015a4b94:
    lVar22 = 0;
    lVar13 = *(long *)puVar9;
  }
  else {
    lVar13 = *(long *)puVar9;
    if (lVar13 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar13 = *(long *)puVar9;
    }
    uVar14 = CArena::crPartyManager() const(lVar13);
    lVar13 = CPartyManager::GetCharacter(int) const(uVar14,0);
    if (lVar13 == 0) goto code_r0x015a4b94;
    lVar13 = CMultiplayManager::PackEnemyHateParameter(int, Aska::Yayoi::MO::EnemyHate*)(lVar13,0,&puStack_248);
    if (lVar13 == 0) goto code_r0x015a4b94;
    lVar22 = 1;
    auStack_140[1] = 0;
    auStack_140[0] = (undefined4)lVar13;
    lVar13 = *(long *)puVar9;
    uStack_148 = &puStack_248;
  }
  if (lVar13 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar13 = *(long *)puVar9;
  }
  uVar14 = CArena::rPartyManager()(lVar13);
  uVar24 = CPartyManager::IsMultiplaySendCharacter(int)(uVar14,1);
  lVar13 = lVar22;
  if ((uVar24 & 1) != 0) {
    lVar18 = *(long *)puVar9;
    if (lVar18 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar18 = *(long *)puVar9;
    }
    uVar14 = CArena::crPartyManager() const(lVar18);
    lVar18 = CPartyManager::GetCharacter(int) const(uVar14,1);
    if (lVar18 != 0) {
      lVar18 = CMultiplayManager::PackEnemyHateParameter(int, Aska::Yayoi::MO::EnemyHate*)(lVar18,1,&puStack_248 + lVar22 * 8);
      if (lVar18 != 0) {
        lVar13 = lVar22 + 1;
        auStack_140[lVar22 * 4] = (int)lVar18;
        auStack_140[lVar22 * 4 + 1] = 1;
        (&uStack_148)[lVar22 * 2] = &puStack_248 + lVar22 * 8;
      }
    }
  }
  lVar22 = *(long *)puVar9;
  if (lVar22 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar22 = *(long *)puVar9;
  }
  uVar14 = CArena::rPartyManager()(lVar22);
  uVar24 = CPartyManager::IsMultiplaySendCharacter(int)(uVar14,2);
  lVar22 = lVar13;
  if ((uVar24 & 1) != 0) {
    lVar18 = *(long *)puVar9;
    if (lVar18 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar18 = *(long *)puVar9;
    }
    uVar14 = CArena::crPartyManager() const(lVar18);
    lVar18 = CPartyManager::GetCharacter(int) const(uVar14,2);
    if (lVar18 != 0) {
      lVar18 = CMultiplayManager::PackEnemyHateParameter(int, Aska::Yayoi::MO::EnemyHate*)(lVar18,2,&puStack_248 + lVar13 * 8);
      if (lVar18 != 0) {
        lVar22 = lVar13 + 1;
        auStack_140[lVar13 * 4] = (int)lVar18;
        auStack_140[lVar13 * 4 + 1] = 2;
        (&uStack_148)[lVar13 * 2] = &puStack_248 + lVar13 * 8;
      }
    }
  }
  lVar13 = *(long *)puVar9;
  if (lVar13 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar13 = *(long *)puVar9;
  }
  uVar14 = CArena::rPartyManager()(lVar13);
  uVar24 = CPartyManager::IsMultiplaySendCharacter(int)(uVar14,3);
  if ((uVar24 & 1) == 0) {
code_r0x015a4d74:
    if (lVar22 != 0) {
      lVar13 = *(long *)(param_1 + 0x48);
      if (lVar13 == 0) goto code_r0x015a4d68;
code_r0x015a4d80:
      Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendAIParameter(Aska::Yayoi::MO::HateParameter const*, unsigned int)(&uStack_250,lVar13 + 8,&uStack_148,lVar22);
    }
  }
  else {
    lVar13 = *(long *)puVar9;
    if (lVar13 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar13 = *(long *)puVar9;
    }
    uVar14 = CArena::crPartyManager() const(lVar13);
    lVar13 = CPartyManager::GetCharacter(int) const(uVar14,3);
    if (lVar13 == 0) goto code_r0x015a4d74;
    lVar13 = CMultiplayManager::PackEnemyHateParameter(int, Aska::Yayoi::MO::EnemyHate*)(lVar13,3,&puStack_248 + lVar22 * 8);
    if (lVar13 == 0) goto code_r0x015a4d74;
    auStack_140[lVar22 * 4] = (int)lVar13;
    auStack_140[lVar22 * 4 + 1] = 3;
    (&uStack_148)[lVar22 * 2] = &puStack_248 + lVar22 * 8;
    lVar13 = *(long *)(param_1 + 0x48);
    lVar22 = lVar22 + 1;
    if (lVar13 != 0) goto code_r0x015a4d80;
code_r0x015a4d68:
    uStack_250 = 0xfffffffffffffc44;
  }
  uVar14 = Aska::Global::GetCPUTime()();
  *(undefined8 *)(param_1 + 0x338) = uVar14;
code_r0x015a4d9c:
  if (*(char *)(param_1 + 0x3e2) == '\0') {
    return;
  }
  piVar15 = (int *)(param_1 + 0xf8);
  iVar21 = 0;
code_r0x015a4dac:
  do {
    if (*piVar15 == -1) goto code_r0x015a4db8;
    ClearExclusiveLocal();
    bVar11 = iVar21 < 0x1ff;
    iVar21 = iVar21 + 1;
  } while (bVar11);
  piVar1 = (int *)(param_1 + 0xfc);
  do {
    cVar7 = '\x01';
    bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar11) {
      *piVar1 = *piVar1 + 1;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
  do {
    if (*piVar15 != -1) {
      ClearExclusiveLocal();
      do {
        uVar24 = Aska::Semaphore::IsReady() const(param_1 + 0x138);
        if ((uVar24 & 1) == 0) {
          do {
            cVar7 = '\x01';
            bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar11) {
              *piVar1 = *piVar1 + -1;
              cVar7 = ExclusiveMonitorsStatus();
            }
          } while (cVar7 != '\0');
          Aska::Thread::Sleep(unsigned int)(1);
        }
        else {
          Aska::Semaphore::Wait() const(param_1 + 0x138);
        }
        do {
          cVar7 = '\x01';
          bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
          if (bVar11) {
            *piVar1 = *piVar1 + 1;
            cVar7 = ExclusiveMonitorsStatus();
          }
        } while (cVar7 != '\0');
        while (*piVar15 == -1) {
          cVar7 = '\x01';
          bVar11 = (bool)ExclusiveMonitorPass(piVar15,0x10);
          if (bVar11) {
            *piVar15 = 0;
            cVar7 = ExclusiveMonitorsStatus();
          }
          if (cVar7 == '\0') goto code_r0x015a5240;
        }
        ClearExclusiveLocal();
      } while( true );
    }
    cVar7 = '\x01';
    bVar11 = (bool)ExclusiveMonitorPass(piVar15,0x10);
    if (bVar11) {
      *piVar15 = 0;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
code_r0x015a5240:
  do {
    cVar7 = '\x01';
    bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
    if (bVar11) {
      *piVar1 = *piVar1 + -1;
      cVar7 = ExclusiveMonitorsStatus();
    }
  } while (cVar7 != '\0');
  DataMemoryBarrier(2,3);
  goto code_r0x015a4e08;
code_r0x015a4db8:
  cVar7 = '\x01';
  bVar11 = (bool)ExclusiveMonitorPass(piVar15,0x10);
  if (bVar11) {
    *piVar15 = 0;
    cVar7 = ExclusiveMonitorsStatus();
  }
  if (cVar7 == '\0') goto code_r0x015a4e00;
  goto code_r0x015a4dac;
code_r0x015a4e00:
  DataMemoryBarrier(2,3);
code_r0x015a4e08:
  plVar25 = *(long **)(param_1 + 0x168);
  DataMemoryBarrier(2,3);
  *(undefined4 *)(param_1 + 0xf8) = 0xffffffff;
  DataMemoryBarrier(2,3);
  piVar1 = (int *)(param_1 + 0xfc);
  plVar2 = (long *)(param_1 + 0x158);
  if (0x14 < *piVar1) {
    do {
      cVar7 = '\x01';
      bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar11) {
        *piVar1 = *piVar1 + -1;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
    uVar24 = Aska::Semaphore::IsReady() const(param_1 + 0x138);
    if ((uVar24 & 1) != 0) {
      Aska::Semaphore::Signal() const(param_1 + 0x138);
    }
  }
  if (plVar2 == plVar25) {
    return;
  }
  lVar13 = param_1 + 0x138;
  do {
    lVar22 = *(long *)puVar9;
    if (lVar22 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar22 = *(long *)puVar9;
    }
    uVar14 = CArena::crPartyManager() const(lVar22);
    uVar14 = CPartyManager::GetCharacter(int) const(uVar14,(long)(char)plVar25[3]);
    cVar7 = *(char *)((long)plVar25 + 0x19);
    puStack_248 = (undefined *)CONCAT71(puStack_248._1_7_,cVar7);
    uVar24 = *(ulong *)(param_1 + 0xb8);
    if (uVar24 != 0) {
      uVar16 = 0;
      do {
        uVar17 = 0;
        if (uVar24 != 0) {
          uVar17 = ((long)cVar7 + uVar16) / uVar24;
        }
        lVar22 = ((long)cVar7 + uVar16) - uVar17 * uVar24;
        cVar6 = *(char *)(*(long *)(param_1 + 0xb0) + lVar22 * 0xc);
        if (cVar6 == '\x01') {
          if (*(char *)(*(long *)(param_1 + 0xb0) + lVar22 * 0xc + 4) == cVar7) {
            puVar19 = (undefined4 *)Aska::THashMap<signed char, unsigned int, Aska::THasher<signed char>, Aska::TEqualTo<signed char>, Aska::TAllocator<Aska::TPair<signed char const, unsigned int> > >::operator[](signed char const&)(param_1 + 0x90,&puStack_248);
            uVar27 = *puVar19;
            lVar22 = *(long *)puVar9;
            goto joined_r0x015a5044;
          }
        }
        else if (cVar6 == '\0') break;
        uVar16 = uVar16 + 1;
      } while (uVar16 < uVar24);
    }
    uVar27 = 0;
    lVar22 = *(long *)puVar9;
joined_r0x015a5044:
    if (lVar22 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar22 = *(long *)puVar9;
    }
    lVar22 = CArena::SearchCharacterObjectByHandle(unsigned int) const(lVar22,uVar27);
    lVar18 = *(long *)puVar9;
    if (lVar18 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar18 = *(long *)puVar9;
    }
    uVar20 = CArena::rBattleManager()(lVar18);
    uVar12 = CBattleManager::CanRushCombo(CCharacterObject*, CCharacterObject*, bool) const(uVar20,uVar14,lVar22,*(int *)(param_1 + 0x3d8) == 0);
    CCharacterData::HP() const(lVar22 + 0x1010);
    if ((*(long *)(param_1 + 0x48) != 0) &&
       (Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendSyncStartRushCombo(signed char, unsigned char, float)(&puStack_248,*(long *)(param_1 + 0x48) + 8,(char)plVar25[3],uVar12 & 1),
       -1 < (long)puStack_248)) {
      lVar22 = *(long *)puVar9;
      if (lVar22 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar22 = *(long *)puVar9;
      }
      lVar22 = CArena::rBattleManager()(lVar22);
      *(undefined1 *)(lVar22 + 0x210d) = 1;
      uVar14 = Aska::Global::GetCPUTime()();
      *(undefined8 *)(param_1 + 0x3c0) = uVar14;
    }
    iVar21 = 0;
    do {
      while (*piVar15 == -1) {
        cVar7 = '\x01';
        bVar11 = (bool)ExclusiveMonitorPass(piVar15,0x10);
        if (bVar11) {
          *piVar15 = 0;
          cVar7 = ExclusiveMonitorsStatus();
        }
        if (cVar7 == '\0') goto code_r0x015a50b4;
      }
      ClearExclusiveLocal();
      bVar11 = iVar21 < 0x1ff;
      iVar21 = iVar21 + 1;
    } while (bVar11);
    do {
      cVar7 = '\x01';
      bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar11) {
        *piVar1 = *piVar1 + 1;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
    do {
      if (*piVar15 != -1) {
        do {
          ClearExclusiveLocal();
          uVar24 = Aska::Semaphore::IsReady() const(lVar13);
          if ((uVar24 & 1) == 0) {
            do {
              cVar7 = '\x01';
              bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
              if (bVar11) {
                *piVar1 = *piVar1 + -1;
                cVar7 = ExclusiveMonitorsStatus();
              }
            } while (cVar7 != '\0');
            Aska::Thread::Sleep(unsigned int)(1);
          }
          else {
            Aska::Semaphore::Wait() const(lVar13);
          }
          do {
            cVar7 = '\x01';
            bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
            if (bVar11) {
              *piVar1 = *piVar1 + 1;
              cVar7 = ExclusiveMonitorsStatus();
            }
          } while (cVar7 != '\0');
          while (*piVar15 == -1) {
            cVar7 = '\x01';
            bVar11 = (bool)ExclusiveMonitorPass(piVar15,0x10);
            if (bVar11) {
              *piVar15 = 0;
              cVar7 = ExclusiveMonitorsStatus();
            }
            if (cVar7 == '\0') goto code_r0x015a50a4;
          }
        } while( true );
      }
      cVar7 = '\x01';
      bVar11 = (bool)ExclusiveMonitorPass(piVar15,0x10);
      if (bVar11) {
        *piVar15 = 0;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
code_r0x015a50a4:
    do {
      cVar7 = '\x01';
      bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
      if (bVar11) {
        *piVar1 = *piVar1 + -1;
        cVar7 = ExclusiveMonitorsStatus();
      }
    } while (cVar7 != '\0');
code_r0x015a50b4:
    DataMemoryBarrier(2,3);
    plVar26 = (long *)plVar25[2];
    if ((plVar2 != plVar25) && (plVar25 != (long *)0x0)) {
      lVar22 = plVar25[1];
      if (lVar22 != 0) {
        *(long **)(lVar22 + 0x10) = plVar26;
      }
      if (plVar26 != (long *)0x0) {
        plVar26[1] = lVar22;
      }
      if (0 < *(int *)(param_1 + 0x178)) {
        *(int *)(param_1 + 0x178) = *(int *)(param_1 + 0x178) + -1;
      }
      plVar25[1] = 0;
      plVar25[2] = 0;
    }
    if (plVar25 < *(long **)(param_1 + 0x188)) {
code_r0x015a5154:
      pcVar23 = *(code **)(*plVar25 + 8);
    }
    else {
      uVar24 = (long)plVar25 - (long)*(long **)(param_1 + 0x188);
      uVar12 = (uint)(uVar24 >> 5);
      if (3 < (int)uVar12) goto code_r0x015a5154;
      lVar22 = param_1 + (long)((int)uVar12 >> 5) * 4;
      uVar4 = *(uint *)(lVar22 + 0x184);
      uVar12 = 1 << (ulong)(uVar12 & 0x1f);
      if ((uVar4 & uVar12) == 0) goto code_r0x015a5154;
      *(uint *)(lVar22 + 0x184) = uVar4 & (uVar12 ^ 0xffffffff);
      plVar25 = (long *)(*(long *)(param_1 + 0x188) + ((long)(uVar24 * 0x8000000) >> 0x1b));
      pcVar23 = *(code **)*plVar25;
    }
    (*pcVar23)(plVar25);
    DataMemoryBarrier(2,3);
    *piVar15 = -1;
    DataMemoryBarrier(2,3);
    if (0x14 < *piVar1) {
      do {
        cVar7 = '\x01';
        bVar11 = (bool)ExclusiveMonitorPass(piVar1,0x10);
        if (bVar11) {
          *piVar1 = *piVar1 + -1;
          cVar7 = ExclusiveMonitorsStatus();
        }
      } while (cVar7 != '\0');
      uVar24 = Aska::Semaphore::IsReady() const(lVar13);
      if ((uVar24 & 1) != 0) {
        Aska::Semaphore::Signal() const(lVar13);
      }
    }
    plVar25 = plVar26;
    if (plVar2 == plVar26) {
      return;
    }
  } while( true );
}

// ==== undefined CMultiplayManager::PackCharacterParameterPlayer(CMultiplayManager::CharacterParameterPlayer *)
// _ZN17CMultiplayManager28PackCharacterParameterPlayerEPNS_24CharacterParameterPlayerE @ 015a5258

long _ZN17CMultiplayManager28PackCharacterParameterPlayerEPNS_24CharacterParameterPlayerE
               (long param_1,long param_2)

{
  char *pcVar1;
  undefined4 *puVar2;
  undefined *puVar3;
  long lVar4;
  undefined8 uVar5;
  long lVar6;
  ulong uVar7;
  char *pcVar8;
  char *pcVar9;
  char cVar10;
  long lVar11;
  long lVar12;
  ulong uVar13;
  undefined4 uVar14;
  
  puVar3 = PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
  uVar13 = 0;
  lVar12 = 0;
  do {
    lVar4 = *(long *)puVar3;
    if (lVar4 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar4 = *(long *)puVar3;
    }
    uVar5 = CArena::crPartyManager() const(lVar4);
    lVar4 = CPartyManager::GetCharacter(int) const(uVar5,uVar13 & 0xffffffff);
    if (lVar4 != 0) {
      lVar6 = *(long *)puVar3;
      if (lVar6 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar6 = *(long *)puVar3;
      }
      uVar5 = CArena::rPartyManager()(lVar6);
      uVar7 = CPartyManager::IsMultiplaySendCharacter(int)(uVar5,uVar13 & 0xffffffff);
      pcVar1 = (char *)(param_1 + uVar13 + 0x3e9);
      if (((uVar7 & 1) != 0) && (*pcVar1 != '\0')) {
        uVar14 = CCharacterData::HP() const(lVar4 + 0x1010);
        puVar2 = (undefined4 *)(param_2 + lVar12 * 0x10);
        *puVar2 = uVar14;
        uVar14 = *(undefined4 *)(lVar4 + 0x1d68);
        *(char *)(puVar2 + 3) = (char)uVar13;
        puVar2[1] = uVar14;
        if (*(int *)(param_1 + 0xa0) == 0) {
code_r0x015a53b4:
          cVar10 = -1;
        }
        else {
          pcVar9 = *(char **)(param_1 + 0xb0);
          lVar6 = *(long *)(param_1 + 0xb8);
          pcVar8 = pcVar9;
          if (lVar6 != 0) {
            lVar11 = lVar6 * 0xc;
            do {
              if (*pcVar8 == '\x01') goto code_r0x015a5374;
              lVar11 = lVar11 + -0xc;
              pcVar8 = pcVar8 + 0xc;
            } while (lVar11 != 0);
            goto code_r0x015a53b4;
          }
code_r0x015a5374:
          pcVar9 = pcVar9 + lVar6 * 0xc;
          if (pcVar8 == pcVar9) goto code_r0x015a53b4;
          do {
            if (*(int *)(pcVar8 + 8) == *(int *)(lVar4 + 0x618)) {
              cVar10 = pcVar8[4];
              break;
            }
            do {
              if (pcVar9 == pcVar8) goto code_r0x015a53b4;
              pcVar8 = pcVar8 + 0xc;
            } while (*pcVar8 != '\x01');
            cVar10 = -1;
          } while (pcVar9 != pcVar8);
        }
        *(char *)((long)puVar2 + 0xd) = cVar10;
        lVar12 = lVar12 + 1;
        puVar2[2] = *(undefined4 *)(lVar4 + 0x1338);
        *(undefined1 *)((long)puVar2 + 0xe) = *(undefined1 *)(lVar4 + 0x13c8);
      }
      *pcVar1 = '\0';
    }
    uVar13 = uVar13 + 1;
    if (uVar13 == 4) {
      return lVar12;
    }
  } while( true );
}

// ==== undefined CMultiplayManager::PackDamageUIParameter(CMultiplayManager::DamageUIParameter *)
// _ZN17CMultiplayManager21PackDamageUIParameterEPNS_17DamageUIParameterE @ 015a558c

void _ZN17CMultiplayManager21PackDamageUIParameterEPNS_17DamageUIParameterE
               (long param_1,long param_2)

{
  long lVar1;
  undefined4 *puVar2;
  long lVar3;
  long lVar4;
  
  lVar4 = 0;
  lVar3 = 0;
  do {
    lVar1 = param_1 + lVar4;
    if (-1 < *(char *)(lVar1 + 0x346)) {
      puVar2 = (undefined4 *)(param_2 + lVar3 * 8);
      lVar3 = lVar3 + 1;
      *puVar2 = *(undefined4 *)(lVar1 + 0x340);
      *(undefined1 *)(puVar2 + 1) = *(undefined1 *)(lVar1 + 0x344);
      *(undefined1 *)((long)puVar2 + 5) = *(undefined1 *)(lVar1 + 0x345);
      *(undefined1 *)((long)puVar2 + 6) = *(undefined1 *)(lVar1 + 0x346);
      *(undefined4 *)(lVar1 + 0x340) = 0;
      *(undefined2 *)(lVar1 + 0x344) = 0xff00;
      *(undefined1 *)(lVar1 + 0x346) = 0xff;
    }
    lVar4 = lVar4 + 8;
  } while (lVar4 != 0x60);
  return;
}

// ==== undefined CMultiplayManager::PackEnemyHateParameter(int,Aska::Yayoi::MO::EnemyHate *)
// _ZN17CMultiplayManager22PackEnemyHateParameterEiPN4Aska5Yayoi2MO9EnemyHateE @ 015a55f0

long _ZN17CMultiplayManager22PackEnemyHateParameterEiPN4Aska5Yayoi2MO9EnemyHateE
               (undefined8 param_1,int param_2,undefined4 *param_3)

{
  long lVar1;
  undefined *puVar2;
  long lVar3;
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  
  puVar2 = PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar2;
  }
  lVar3 = CArena::rBattleManager()(lVar3);
  lVar5 = *(long *)puVar2;
  if (lVar5 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar5 = *(long *)puVar2;
  }
  lVar7 = (long)param_2;
  uVar4 = CArena::crPartyManager() const(lVar5);
  lVar5 = CPartyManager::GetCharacter(int) const(uVar4,4);
  if ((lVar5 == 0) || (lVar5 = lVar3 + lVar7 * 0x10, *(char *)(lVar5 + 0x18a0) == '\0')) {
    lVar6 = 0;
    lVar5 = *(long *)puVar2;
  }
  else {
    *param_3 = 4;
    lVar6 = 1;
    param_3[1] = *(undefined4 *)(lVar5 + 0x1894);
    lVar5 = *(long *)puVar2;
  }
  if (lVar5 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar5 = *(long *)puVar2;
  }
  uVar4 = CArena::crPartyManager() const(lVar5);
  lVar5 = CPartyManager::GetCharacter(int) const(uVar4,5);
  if ((lVar5 != 0) && (lVar5 = lVar3 + lVar7 * 0x10, *(char *)(lVar5 + 0x1970) != '\0')) {
    lVar1 = lVar6 * 2;
    param_3[lVar1] = 5;
    lVar6 = lVar6 + 1;
    (param_3 + lVar1)[1] = *(undefined4 *)(lVar5 + 0x1964);
  }
  lVar5 = *(long *)puVar2;
  if (lVar5 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar5 = *(long *)puVar2;
  }
  uVar4 = CArena::crPartyManager() const(lVar5);
  lVar5 = CPartyManager::GetCharacter(int) const(uVar4,6);
  if ((lVar5 != 0) && (lVar5 = lVar3 + lVar7 * 0x10, *(char *)(lVar5 + 0x1a40) != '\0')) {
    lVar1 = lVar6 * 2;
    param_3[lVar1] = 6;
    lVar6 = lVar6 + 1;
    (param_3 + lVar1)[1] = *(undefined4 *)(lVar5 + 0x1a34);
  }
  lVar5 = *(long *)puVar2;
  if (lVar5 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar5 = *(long *)puVar2;
  }
  uVar4 = CArena::crPartyManager() const(lVar5);
  lVar5 = CPartyManager::GetCharacter(int) const(uVar4,7);
  if ((lVar5 != 0) && (lVar5 = lVar3 + lVar7 * 0x10, *(char *)(lVar5 + 0x1b10) != '\0')) {
    lVar1 = lVar6 * 2;
    param_3[lVar1] = 7;
    lVar6 = lVar6 + 1;
    (param_3 + lVar1)[1] = *(undefined4 *)(lVar5 + 0x1b04);
  }
  lVar5 = *(long *)puVar2;
  if (lVar5 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar5 = *(long *)puVar2;
  }
  uVar4 = CArena::crPartyManager() const(lVar5);
  lVar5 = CPartyManager::GetCharacter(int) const(uVar4,8);
  if ((lVar5 != 0) && (lVar5 = lVar3 + lVar7 * 0x10, *(char *)(lVar5 + 0x1be0) != '\0')) {
    lVar1 = lVar6 * 2;
    param_3[lVar1] = 8;
    lVar6 = lVar6 + 1;
    (param_3 + lVar1)[1] = *(undefined4 *)(lVar5 + 0x1bd4);
  }
  lVar5 = *(long *)puVar2;
  if (lVar5 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar5 = *(long *)puVar2;
  }
  uVar4 = CArena::crPartyManager() const(lVar5);
  lVar5 = CPartyManager::GetCharacter(int) const(uVar4,9);
  if ((lVar5 != 0) && (lVar5 = lVar3 + lVar7 * 0x10, *(char *)(lVar5 + 0x1cb0) != '\0')) {
    lVar1 = lVar6 * 2;
    param_3[lVar1] = 9;
    lVar6 = lVar6 + 1;
    (param_3 + lVar1)[1] = *(undefined4 *)(lVar5 + 0x1ca4);
  }
  lVar5 = *(long *)puVar2;
  if (lVar5 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar5 = *(long *)puVar2;
  }
  uVar4 = CArena::crPartyManager() const(lVar5);
  lVar5 = CPartyManager::GetCharacter(int) const(uVar4,10);
  if ((lVar5 != 0) && (lVar5 = lVar3 + lVar7 * 0x10, *(char *)(lVar5 + 0x1d80) != '\0')) {
    lVar1 = lVar6 * 2;
    param_3[lVar1] = 10;
    lVar6 = lVar6 + 1;
    (param_3 + lVar1)[1] = *(undefined4 *)(lVar5 + 0x1d74);
  }
  lVar5 = *(long *)puVar2;
  if (lVar5 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar5 = *(long *)puVar2;
  }
  uVar4 = CArena::crPartyManager() const(lVar5);
  lVar5 = CPartyManager::GetCharacter(int) const(uVar4,0xb);
  if ((lVar5 != 0) && (lVar3 = lVar3 + lVar7 * 0x10, *(char *)(lVar3 + 0x1e50) != '\0')) {
    lVar5 = lVar6 * 2;
    param_3[lVar5] = 0xb;
    lVar6 = lVar6 + 1;
    (param_3 + lVar5)[1] = *(undefined4 *)(lVar3 + 0x1e44);
  }
  return lVar6;
}

// ==== undefined CMultiplayManager::SendAIParameter(Aska::Yayoi::MO::HateParameter const *,unsigned long)
// _ZN17CMultiplayManager15SendAIParameterEPKN4Aska5Yayoi2MO13HateParameterEm @ 015a5940

void _ZN17CMultiplayManager15SendAIParameterEPKN4Aska5Yayoi2MO13HateParameterEm
               (undefined8 *param_1,long param_2)

{
  if (*(long *)(param_2 + 0x48) != 0) {
    (*(code *)
      PTR__ZN4Aska5Yayoi2MO3Cli19BattleProtocolProxy15SendAIParameterEPKNS1_13HateParameterEj_02cb4620
    )(*(long *)(param_2 + 0x48) + 8);
    return;
  }
  *param_1 = 0xfffffffffffffc44;
  return;
}

// ==== undefined CMultiplayManager::SendSyncStartRushCombo(signed,unsigned char,float)
// _ZN17CMultiplayManager22SendSyncStartRushComboEahf @ 015a59f8

void _ZN17CMultiplayManager22SendSyncStartRushComboEahf(long *param_1,long param_2)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  long lStack_28;
  
  if (*(long *)(param_2 + 0x48) == 0) {
    lStack_28 = -0x3bc;
  }
  else {
    Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendSyncStartRushCombo(signed char, unsigned char, float)(&lStack_28,*(long *)(param_2 + 0x48) + 8);
    puVar1 = PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
    if (-1 < lStack_28) {
      lVar2 = *(long *)PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
      if (lVar2 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar2 = *(long *)puVar1;
      }
      lVar2 = CArena::rBattleManager()(lVar2);
      *(undefined1 *)(lVar2 + 0x210d) = 1;
      uVar3 = Aska::Global::GetCPUTime()();
      lStack_28 = 0;
      *(undefined8 *)(param_2 + 0x3c0) = uVar3;
    }
  }
  *param_1 = lStack_28;
  return;
}

// ==== undefined CMultiplayManager::IsSendCharacter(CCharacterObject *)
// _ZNK17CMultiplayManager15IsSendCharacterEP16CCharacterObject @ 015a6178

void _ZNK17CMultiplayManager15IsSendCharacterEP16CCharacterObject(long param_1,long param_2)

{
  long lVar1;
  
  lVar1 = 0;
  if (param_2 != 0) {
    lVar1 = param_2 + 0x628;
  }
  (*(code *)PTR__ZNK4Aska5Yayoi21IMultiplayManagerBase12IsSendObjectEPNS_15ISnapshotObjectE_02c91938
  )(*(undefined8 *)(param_1 + 0x38),lVar1);
  return;
}

// ==== undefined CMultiplayManager::SetSendCharacter(CCharacterObject *,bool)
// _ZN17CMultiplayManager16SetSendCharacterEP16CCharacterObjectb @ 015a618c

void _ZN17CMultiplayManager16SetSendCharacterEP16CCharacterObjectb
               (long param_1,long param_2,uint param_3)

{
  long lVar1;
  
  lVar1 = 0;
  if (param_2 != 0) {
    lVar1 = param_2 + 0x628;
  }
  (*(code *)
    PTR__ZN4Aska5Yayoi21IMultiplayManagerBase13SetSendObjectEPNS_15ISnapshotObjectEb_02cb33d0)
            (*(undefined8 *)(param_1 + 0x38),lVar1,param_3 & 1);
  return;
}

// ==== undefined CMultiplayManager::SendMessage(Aska::Yayoi::MultiplayRPC::Message const *,bool)
// _ZN17CMultiplayManager11SendMessageEPKN4Aska5Yayoi12MultiplayRPC7MessageEb @ 015a6c48

void _ZN17CMultiplayManager11SendMessageEPKN4Aska5Yayoi12MultiplayRPC7MessageEb
               (undefined8 *param_1,long param_2,undefined8 param_3,uint param_4)

{
  if (*(long *)(param_2 + 0x38) != 0) {
    (*(code *)
      PTR__ZN4Aska5Yayoi21IMultiplayManagerBase11SendMessageEPNS0_12MultiplayRPC7MessageEb_02c8fe18)
              (*(long *)(param_2 + 0x38),param_3,param_4 & 1);
    return;
  }
  *param_1 = 0xfffffffffffffc44;
  return;
}

// ==== undefined CMultiplayManager::SendStamp(unsigned int)
// _ZN17CMultiplayManager9SendStampEj @ 015a6c64

void _ZN17CMultiplayManager9SendStampEj(undefined8 *param_1,long param_2)

{
  if (*(long *)(param_2 + 0x48) != 0) {
    (*(code *)PTR__ZN4Aska5Yayoi2MO3Cli19BattleProtocolProxy9SendStampEj_02cadcd0)
              (*(long *)(param_2 + 0x48) + 8);
    return;
  }
  *param_1 = 0xfffffffffffffc44;
  return;
}

// ==== undefined CMultiplayManager::SendMissionEnd(void)
// _ZN17CMultiplayManager14SendMissionEndEv @ 015a6c80

void _ZN17CMultiplayManager14SendMissionEndEv(ulong *param_1,long param_2)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  undefined *puVar4;
  undefined4 uVar5;
  ulong uVar6;
  long lVar7;
  undefined8 uVar8;
  long lVar9;
  undefined1 auStack_10e0 [4096];
  undefined1 auStack_e0 [144];
  long lStack_50;
  int *piStack_48;
  ulong uStack_38;
  
  if (*(long *)(param_2 + 0x48) == 0) {
    *param_1 = 0xfffffffffffffc44;
    return;
  }
  BAS::GetUUID()(&lStack_50);
  lVar7 = lStack_50;
  uVar5 = BAS::GetDeviceType()();
  Aska::ASON::ASON()(auStack_e0);
  puVar4 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar9 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar9 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar9 = *(long *)puVar4;
  }
  void AsonSerializer::Serialize<CBattleLogInfo>(CBattleLogInfo&, unsigned int, unsigned long, bool)(auStack_e0,lVar9 + 0x52d8,0,0x4000,1);
  uVar6 = Aska::ASON::CalcSerializedSize() const(auStack_e0);
  if (uVar6 < 0x1001) {
    uVar6 = Aska::ASON::Serialize(void*, unsigned long) const(auStack_e0,auStack_10e0,uVar6);
    if (-1 < (long)uVar6) {
      Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendMissionEnd(signed char const*, Aska::Yayoi::MO::DeviceType, signed char const*, unsigned int)(&uStack_38,*(long *)(param_2 + 0x48) + 8,lVar7,uVar5,auStack_10e0,
                      uVar6 & 0xffffffff);
      if (-1 < (long)uStack_38) {
        lVar7 = *(long *)puVar4;
        if (lVar7 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar7 = *(long *)puVar4;
        }
        uVar8 = CParameterManager::pParameterUI() const(lVar7);
        CParameterUI::SetNowloadingOnlineFlag(CParameterUI::eNowloadingOnline, bool)(uVar8,0,1);
        uStack_38 = 0;
      }
      *param_1 = uStack_38;
      goto code_r0x015a6dc0;
    }
  }
  else {
    uVar6 = 0xfffffffffffffc15;
  }
  *param_1 = uVar6;
code_r0x015a6dc0:
  Aska::ASON::~ASON()(auStack_e0);
  if (piStack_48 != (int *)0x0) {
    do {
      iVar1 = *piStack_48;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_48,0x10);
      if (bVar3) {
        *piStack_48 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) {
      return;
    }
  }
  if (lStack_50 != 0) {
    operator delete[](void*)();
  }
  if (piStack_48 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
  return;
}

// ==== undefined CMultiplayManager::SendMissionContinue(bool)
// _ZN17CMultiplayManager19SendMissionContinueEb @ 015a719c

void _ZN17CMultiplayManager19SendMissionContinueEb(undefined8 *param_1,long param_2,uint param_3)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  undefined *puVar4;
  long lVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  long lVar8;
  long lStack_50;
  int *piStack_48;
  
  if (*(long *)(param_2 + 0x48) == 0) {
    *param_1 = 0xfffffffffffffc44;
  }
  else {
    BAS::GetUUID()(&lStack_50);
    lVar5 = lStack_50;
    uVar6 = BAS::GetDeviceType()();
    puVar4 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    lVar8 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (lVar8 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar8 = *(long *)puVar4;
    }
    uVar7 = CParameterManager::pParameterUI() const(lVar8);
    CParameterUI::SetNowloadingOnlineFlag(CParameterUI::eNowloadingOnline, bool)(uVar7,0,1);
    *(undefined1 *)(param_2 + 0x3e6) = 0;
    Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendMissionContinue(signed char const*, Aska::Yayoi::MO::DeviceType, unsigned char)(param_1,*(long *)(param_2 + 0x48) + 8,lVar5,uVar6,param_3 & 1);
    if (piStack_48 != (int *)0x0) {
      do {
        iVar1 = *piStack_48;
        cVar2 = '\x01';
        bVar3 = (bool)ExclusiveMonitorPass(piStack_48,0x10);
        if (bVar3) {
          *piStack_48 = iVar1 + -1;
          cVar2 = ExclusiveMonitorsStatus();
        }
      } while (cVar2 != '\0');
      if (iVar1 + -1 != 0) {
        return;
      }
    }
    if (lStack_50 != 0) {
      operator delete[](void*)();
    }
    if (piStack_48 != (int *)0x0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  return;
}

// ==== undefined CMultiplayManager::SendStartBattleStage(void)
// _ZN17CMultiplayManager20SendStartBattleStageEv @ 015a7290

void _ZN17CMultiplayManager20SendStartBattleStageEv(long *param_1,long param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  long lVar3;
  long lStack_28;
  
  if (*(long *)(param_2 + 0x48) == 0) {
    lStack_28 = -0x3bc;
  }
  else {
    Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendStartBattleStage()(&lStack_28,*(long *)(param_2 + 0x48) + 8);
    if (-1 < lStack_28) {
      *(undefined1 *)(*(long *)(param_2 + 0x38) + 0x710) = 1;
      Aska::Yayoi::IMultiplayManagerBase::ClearAllMessage()(*(undefined8 *)(param_2 + 0x38));
      *(undefined1 *)(param_2 + 1000) = 1;
      uVar2 = Aska::Global::GetCPUTime()();
      *(undefined8 *)(param_2 + 0x330) = uVar2;
      puVar1 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
      lVar3 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
      if (lVar3 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar3 = *(long *)puVar1;
      }
      uVar2 = CParameterManager::pParameterUI() const(lVar3);
      CParameterUI::SetNowloadingOnlineFlag(CParameterUI::eNowloadingOnline, bool)(uVar2,0,1);
      lStack_28 = 0;
    }
  }
  *param_1 = lStack_28;
  return;
}

// ==== undefined CMultiplayManager::SendFinishBattleStage(void)
// _ZN17CMultiplayManager21SendFinishBattleStageEv @ 015a733c

void _ZN17CMultiplayManager21SendFinishBattleStageEv(long *param_1,long param_2)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  long lStack_18;
  
  if (*(long *)(param_2 + 0x48) == 0) {
    lStack_18 = -0x3bc;
  }
  else {
    *(undefined1 *)(param_2 + 0x3e2) = 0;
    Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendFinishBattleStage()(&lStack_18,*(long *)(param_2 + 0x48) + 8);
    puVar1 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (-1 < lStack_18) {
      lVar2 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
      if (lVar2 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar2 = *(long *)puVar1;
      }
      uVar3 = CParameterManager::pParameterUI() const(lVar2);
      CParameterUI::SetNowloadingOnlineFlag(CParameterUI::eNowloadingOnline, bool)(uVar3,0,1);
      lStack_18 = 0;
    }
  }
  *param_1 = lStack_18;
  return;
}

// ==== undefined CMultiplayManager::SendStartRushCombo(signed,signed,float)
// _ZN17CMultiplayManager18SendStartRushComboEaaf @ 015a73c0

void _ZN17CMultiplayManager18SendStartRushComboEaaf(ulong *param_1,long param_2)

{
  ulong uStack_18;
  
  if (*(long *)(param_2 + 0x48) == 0) {
    uStack_18 = 0xfffffffffffffc44;
  }
  else {
    Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendStartRushCombo(signed char, signed char, float)(&uStack_18,*(long *)(param_2 + 0x48) + 8);
    uStack_18 = uStack_18 & (long)uStack_18 >> 0x3f;
  }
  *param_1 = uStack_18;
  return;
}

// ==== undefined CMultiplayManager::SendSyncFinishRushCombo(float,int)
// _ZN17CMultiplayManager23SendSyncFinishRushComboEfi @ 015a7400

void _ZN17CMultiplayManager23SendSyncFinishRushComboEfi(long *param_1,long param_2)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  long lStack_28;
  
  if (*(long *)(param_2 + 0x48) == 0) {
    lStack_28 = -0x3bc;
  }
  else {
    Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendSyncFinishRushCombo(float, int)(&lStack_28,*(long *)(param_2 + 0x48) + 8);
    puVar1 = PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
    if (-1 < lStack_28) {
      lVar2 = *(long *)PTR__ZN9Framework10TSingletonI6CArenaE11m_pInstanceE_02cbf968;
      if (lVar2 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar2 = *(long *)puVar1;
      }
      lVar2 = CArena::rBattleManager()(lVar2);
      *(undefined1 *)(lVar2 + 0x210e) = 1;
      uVar3 = Aska::Global::GetCPUTime()();
      lStack_28 = 0;
      *(undefined8 *)(param_2 + 0x3c0) = uVar3;
    }
  }
  *param_1 = lStack_28;
  return;
}

// ==== undefined CMultiplayManager::InitBattleRPCClient(char const *,unsigned short,IMultiplayNotify *)
// _ZN17CMultiplayManager19InitBattleRPCClientEPKctP16IMultiplayNotify @ 015a7568

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN17CMultiplayManager19InitBattleRPCClientEPKctP16IMultiplayNotify
               (long param_1,long param_2,uint param_3,undefined8 param_4)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined *puVar6;
  undefined *puVar7;
  long lVar8;
  long *plVar9;
  undefined4 *puVar10;
  int *piVar11;
  undefined8 uVar12;
  undefined4 *puVar13;
  undefined4 *puStack_68;
  int *piStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined4 *puStack_48;
  
  if ((param_2 == 0) || ((param_3 & 0xffff) == 0)) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0281a8e8/*"C:\BAS_Submission\Client\Project\..\Source\Game\Network\Multiplay\MultiplayManager.cpp"*/,0x611,&UNK_029d2011);
  }
  CMultiplayManager::TermBattleRPCClient()(param_1);
  puVar7 = PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
  lVar8 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
  if (lVar8 == 0) {
    lVar8 = Aska::Global::GetAvailableMemoryManager()();
  }
  plVar9 = (long *)Aska::MemoryManager::Malloc(unsigned long)(lVar8,0x3e0);
  *(long **)(param_1 + 0x48) = plVar9;
  if (plVar9 == (long *)0x0) {
code_r0x015a761c:
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0281a8e8/*"C:\BAS_Submission\Client\Project\..\Source\Game\Network\Multiplay\MultiplayManager.cpp"*/,0x618,&UNK_029d2011);
  }
  else {
    *(undefined4 *)(plVar9 + 3) = 0;
    puVar6 = PTR__ZTVN4Aska5Yayoi9TARPCPeerINS0_2MO3Cli19BattleProtocolProxyEEE_02cbbf10;
    plVar9[2] = 0;
    plVar9[1] = 0;
    *plVar9 = (long)(puVar6 + 0x10);
    Aska::Yayoi::TPeer<Aska::Yayoi::TCP, Aska::Yayoi::TProtocolSuite<Aska::Yayoi::MO::BattleProtocol, Aska::Yayoi::NoProtocol<1>, Aska::Yayoi::NoProtocol<2> >, true>::TPeer()(plVar9 + 4);
    plVar9[0x7a] = 0;
    plVar9[0x77] = 0;
    plVar9[0x76] = 0;
    plVar9[0x79] = 0;
    plVar9[0x78] = 0;
    if (*(long *)(param_1 + 0x48) == 0) goto code_r0x015a761c;
  }
  puStack_48 = (undefined4 *)0x0;
  lVar8 = **(long **)puVar7;
  if (lVar8 == 0) {
    lVar8 = Aska::Global::GetAvailableMemoryManager()();
  }
  puVar10 = (undefined4 *)Aska::MemoryManager::Malloc(unsigned long)(lVar8,0x100);
  if (puVar10 == (undefined4 *)0x0) {
    piVar11 = (int *)0x0;
code_r0x015a76cc:
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0281a8e8/*"C:\BAS_Submission\Client\Project\..\Source\Game\Network\Multiplay\MultiplayManager.cpp"*/,0x61c,&UNK_029d2011);
    puVar13 = (undefined4 *)0x0;
  }
  else {
    puStack_48 = (undefined4 *)0x0;
    piVar11 = (int *)Aska::TSharedPointerCode::CreateCounter(int)(0);
    if (piVar11 == (int *)0x0) {
      puVar10 = (undefined4 *)0x0;
      goto code_r0x015a76cc;
    }
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar3) {
        *piVar11 = *piVar11 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    puStack_48 = puVar10;
    if (puVar10 == (undefined4 *)0x0) goto code_r0x015a76cc;
    *puVar10 = 5;
    memset(puVar10 + 2,0,0x61);
    Aska::Yayoi::IPAddress::IPAddress()(puVar10 + 0x1c);
    *(undefined1 *)(puVar10 + 0x3e) = 0;
    puVar10 = puStack_48;
    puVar13 = puStack_48;
    if (puStack_48 == (undefined4 *)0x0) goto code_r0x015a76cc;
  }
  Aska::Yayoi::URI::Deserialize(char const*, unsigned short, Aska::Yayoi::AddressFamily, signed char*, unsigned long)(&uStack_50,puVar10,param_2,param_3,0,0,0);
  uVar12 = *(undefined8 *)(param_1 + 0x48);
  *(undefined8 *)(param_1 + 0x58) = param_4;
  if (piVar11 != (int *)0x0) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar3) {
        *piVar11 = *piVar11 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
  puStack_68 = puVar13;
  piStack_60 = piVar11;
  Aska::Yayoi::TARPCPeer<Aska::Yayoi::MO::Cli::BattleProtocolProxy>::Initialize(Aska::Yayoi::MO::Cli::IBattleProtocolNotify*, Aska::TSharedPointer<Aska::Yayoi::URI>, Aska::Yayoi::NetworkEvent*, long, bool)(&uStack_58,uVar12,param_4,&puStack_68,0,0,0);
  puVar10 = puStack_68;
  uStack_50 = uStack_58;
  if (piStack_60 != (int *)0x0) {
    do {
      iVar1 = *piStack_60;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_60,0x10);
      if (bVar3) {
        *piStack_60 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) goto code_r0x015a7788;
  }
  if (puStack_68 != (undefined4 *)0x0) {
    Aska::Yayoi::URI::DeleteBuffer()(puStack_68);
    operator delete(void*)(puVar10);
  }
  if (piStack_60 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)();
  }
code_r0x015a7788:
  uVar5 = _UNK_0281a94f;
  uVar4 = _UNK_0281a947;
  uVar12 = _UNK_0281a93f;
  puStack_68 = (undefined4 *)0x0;
  piStack_60 = (int *)0x0;
  lVar8 = *(long *)(param_1 + 0x48);
  *(undefined8 *)(lVar8 + 100) = _UNK_0281a957;
  *(undefined8 *)(lVar8 + 0x5c) = uVar5;
  uVar5 = _UNK_0281a95f;
  *(undefined4 *)(lVar8 + 0x78) = 0x474a6152;
  *(undefined8 *)(lVar8 + 0x54) = uVar4;
  *(undefined8 *)(lVar8 + 0x4c) = uVar12;
  *(undefined1 *)(lVar8 + 0xbd) = 1;
  *(undefined8 *)(lVar8 + 0x70) = uVar5;
  *(undefined1 *)(lVar8 + 0xbc) = 1;
  *(undefined4 *)(lVar8 + 0x6c) = 0;
  lVar8 = *(long *)(param_1 + 0x48);
  *(undefined1 *)(lVar8 + 0x301) = 1;
  *(undefined8 *)(lVar8 + 0x304) = 0x200000014;
  *(undefined4 *)(lVar8 + 0x30c) = 3;
  if (*(int *)(lVar8 + 0x19c) < 0) {
    uStack_58 = 0;
    puVar10 = puStack_48;
  }
  else {
    Aska::Yayoi::Socket::SetKeepAlive(bool, int, int, int)(&uStack_58,lVar8 + 0x19c,1,0x14,2,3);
    puVar10 = puStack_48;
  }
  if (piVar11 != (int *)0x0) {
    do {
      iVar1 = *piVar11;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piVar11,0x10);
      if (bVar3) {
        *piVar11 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 != 0) {
      return;
    }
  }
  puStack_48 = puVar10;
  if (puVar10 != (undefined4 *)0x0) {
    Aska::Yayoi::URI::DeleteBuffer()(puVar10);
    operator delete(void*)(puVar10);
  }
  if (piVar11 != (int *)0x0) {
    Aska::TSharedPointerCode::DeleteCounter(int*)(piVar11);
  }
  return;
}

// ==== undefined CMultiplayManager::InitMultiplayManager(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo const *)
// _ZN17CMultiplayManager20InitMultiplayManagerEPKN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoE @ 015a7cec

void _ZN17CMultiplayManager20InitMultiplayManagerEPKN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoE
               (long param_1,long param_2)

{
  undefined4 uVar1;
  undefined *puVar2;
  long lVar3;
  long *plVar4;
  long lStack_28;
  
  if (*(long *)(param_1 + 0x38) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0281a8e8/*"C:\BAS_Submission\Client\Project\..\Source\Game\Network\Multiplay\MultiplayManager.cpp"*/,0x64c,&UNK_029d2011);
  }
  lVar3 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
  if (lVar3 == 0) {
    lVar3 = Aska::Global::GetAvailableMemoryManager()();
  }
  plVar4 = (long *)Aska::MemoryManager::Malloc(unsigned long)(lVar3,0x728);
  *(long **)(param_1 + 0x38) = plVar4;
  if (plVar4 != (long *)0x0) {
    Aska::Yayoi::IMultiplayManagerBase::IMultiplayManagerBase()(plVar4);
    puVar2 = PTR__ZTVN4Aska5Yayoi17TMultiplayManagerINS0_2MO3Cli19BattleProtocolProxyEEE_02cc2f28;
    plVar4[0xe3] = 0;
    *(undefined4 *)(plVar4 + 0xe4) = 0xffffffff;
    *plVar4 = (long)(puVar2 + 0x10);
    if (*(long *)(param_1 + 0x38) != 0) {
      lVar3 = *(long *)(param_1 + 0x48);
      goto joined_r0x015a7de0;
    }
  }
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0281a8e8/*"C:\BAS_Submission\Client\Project\..\Source\Game\Network\Multiplay\MultiplayManager.cpp"*/,0x64f,&UNK_029d2011);
  lVar3 = *(long *)(param_1 + 0x48);
joined_r0x015a7de0:
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0281a8e8/*"C:\BAS_Submission\Client\Project\..\Source\Game\Network\Multiplay\MultiplayManager.cpp"*/,0x651,&UNK_029d2011);
  }
  Aska::Yayoi::IMultiplayManagerBase::Init(unsigned long, unsigned long)(&lStack_28,*(undefined8 *)(param_1 + 0x38),300,300);
  if (lStack_28 < 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0281a8e8/*"C:\BAS_Submission\Client\Project\..\Source\Game\Network\Multiplay\MultiplayManager.cpp"*/,0x65a,&UNK_029d2011);
  }
  if ((param_2 == 0) || (*(long *)(param_1 + 0x48) == 0)) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0281a8e8/*"C:\BAS_Submission\Client\Project\..\Source\Game\Network\Multiplay\MultiplayManager.cpp"*/,0x65d,&UNK_029d2011);
  }
  else {
    lVar3 = *(long *)(param_1 + 0x38);
    *(long *)(lVar3 + 0x718) = *(long *)(param_1 + 0x48);
    uVar1 = *(undefined4 *)(param_2 + 0x68);
    *(undefined2 *)(lVar3 + 0x710) = 1;
    *(undefined4 *)(lVar3 + 0x720) = uVar1;
  }
  *(undefined1 *)(param_1 + 1000) = 0;
  Aska::TaskManager::Add(Aska::Task*)(*(undefined8 *)PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620,
                  *(undefined8 *)(param_1 + 0x38));
  CMultiplayManager::RegisterReceiver()(param_1);
  return;
}

// ==== undefined Aska::Yayoi::IMultiplayManagerBase::Init(unsigned long,unsigned long)
// _ZN4Aska5Yayoi21IMultiplayManagerBase4InitEmm @ 022f7540

void _ZN4Aska5Yayoi21IMultiplayManagerBase4InitEmm
               (long *param_1,long param_2,long param_3,long param_4)

{
  undefined8 *puVar1;
  long lVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  long lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  long lVar10;
  long lVar11;
  long lVar12;
  long lStack_58;
  undefined8 *puVar9;
  
  if ((param_3 == 0) || (param_4 == 0)) {
    lStack_58 = -0x3bd;
  }
  else {
    Aska::SnapshotManager::Init(unsigned long, Aska::SnapshotManager::PriorityMode)(&lStack_58,param_2 + 0x78,2,0);
    if (-1 < lStack_58) {
      if (((ulong)(*(long *)(param_2 + 0x40) - *(long *)(param_2 + 0x30) >> 4) < 0x40) &&
         (puVar3 = (undefined8 *)Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0x400,8), puVar3 != (undefined8 *)0x0)) {
        puVar4 = *(undefined8 **)(param_2 + 0x30);
        puVar1 = *(undefined8 **)(param_2 + 0x38);
        puVar7 = puVar3;
        puVar8 = puVar4;
        if (puVar4 != puVar1) {
          do {
            puVar9 = puVar8 + 2;
            uVar6 = *puVar8;
            puVar7[1] = puVar8[1];
            *puVar7 = uVar6;
            puVar7 = puVar7 + 2;
            puVar8 = puVar9;
          } while (puVar1 != puVar9);
          lVar5 = -0x10 - (long)puVar4;
          puVar4 = *(undefined8 **)(param_2 + 0x30);
          puVar7 = (undefined8 *)
                   ((long)puVar3 + ((long)puVar1 + lVar5 & 0xfffffffffffffff0U) + 0x10);
        }
        Aska::MemoryManagerAdapter::AlignedFree(void*)(puVar4);
        *(undefined8 **)(param_2 + 0x30) = puVar3;
        *(undefined8 **)(param_2 + 0x38) = puVar7;
        *(undefined8 **)(param_2 + 0x40) = puVar3 + 0x80;
      }
      if (((ulong)(*(long *)(param_2 + 0x68) - *(long *)(param_2 + 0x58) >> 7) < 0x40) &&
         (lVar5 = Aska::MemoryManagerAdapter::AlignedMalloc(unsigned long, unsigned long)(0x2000,1), lVar5 != 0)) {
        lVar11 = *(long *)(param_2 + 0x58);
        lVar2 = *(long *)(param_2 + 0x60);
        lVar10 = lVar5;
        if (lVar11 != lVar2) {
          lVar10 = lVar11;
          lVar12 = lVar5;
          do {
            memcpy(lVar12,lVar10,0x80);
            lVar10 = lVar10 + 0x80;
            lVar12 = lVar12 + 0x80;
          } while (lVar2 != lVar10);
          lVar2 = lVar2 - lVar11;
          lVar11 = *(long *)(param_2 + 0x58);
          lVar10 = lVar5 + (lVar2 - 0x80U & 0xffffffffffffff80) + 0x80;
        }
        Aska::MemoryManagerAdapter::AlignedFree(void*)(lVar11);
        *(long *)(param_2 + 0x58) = lVar5;
        *(long *)(param_2 + 0x60) = lVar10;
        *(long *)(param_2 + 0x68) = lVar5 + 0x2000;
      }
      *(long *)(param_2 + 0x2d0) = param_2 + 0x2e0;
      *(undefined8 *)(param_2 + 0x2d8) = 0x200;
      uVar6 = Aska::Global::GetCPUTime()();
      lStack_58 = 0;
      *(long *)(param_2 + 0x6f0) = param_3;
      *(undefined8 *)(param_2 + 0x6f8) = uVar6;
      *(long *)(param_2 + 0x700) = param_4;
      *(undefined8 *)(param_2 + 0x708) = uVar6;
    }
  }
  *param_1 = lStack_58;
  return;
}

// ==== undefined Aska::Yayoi::IMultiplayManagerBase::Run(int)
// _ZN4Aska5Yayoi21IMultiplayManagerBase3RunEi @ 022f76f0

void _ZN4Aska5Yayoi21IMultiplayManagerBase3RunEi(long param_1)

{
  long lVar1;
  undefined8 uVar2;
  
  Aska::Yayoi::IMultiplayManagerBase::RunMessage()();
  if (*(char *)(param_1 + 0x711) == '\0') {
    return;
  }
  lVar1 = Aska::Global::GetCPUTime()();
  if ((ulong)(lVar1 - *(long *)(param_1 + 0x708)) < *(ulong *)(param_1 + 0x700)) {
    if (*(char *)(param_1 + 0x713) == '\0') goto code_r0x011b54a0;
  }
  else {
    *(undefined1 *)(param_1 + 0x713) = 1;
  }
  Aska::Yayoi::IMultiplayManagerBase::FlushSendSnapshot()(param_1);
  uVar2 = Aska::Global::GetCPUTime()();
  *(undefined8 *)(param_1 + 0x708) = uVar2;
  *(undefined1 *)(param_1 + 0x713) = 0;
code_r0x011b54a0:
  (*(code *)PTR__ZN4Aska5Yayoi21IMultiplayManagerBase20FlushReceiveSnapshotEv_02c92a40)(param_1);
  return;
}

// ==== undefined Aska::Yayoi::IMultiplayManagerBase::RunMessage(void)
// _ZN4Aska5Yayoi21IMultiplayManagerBase10RunMessageEv @ 022f7758

void _ZN4Aska5Yayoi21IMultiplayManagerBase10RunMessageEv(long *param_1)

{
  long lVar1;
  long *plVar2;
  undefined1 auStack_28 [8];
  
  if ((char)param_1[0xe2] != '\0') {
    lVar1 = Aska::Global::GetCPUTime()();
    if ((ulong)(lVar1 - param_1[0xdf]) < (ulong)param_1[0xde]) {
      if (*(char *)((long)param_1 + 0x712) == '\0') {
        return;
      }
    }
    else {
      *(undefined1 *)((long)param_1 + 0x712) = 1;
    }
    plVar2 = (long *)param_1[6];
    lVar1 = param_1[7] - (long)plVar2 >> 4;
    if (lVar1 != 0) {
      (**(code **)(*param_1 + 0x98))(auStack_28,param_1,plVar2,lVar1);
      do {
        if ((0x80 < (int)plVar2[1]) && (*plVar2 != 0)) {
          operator delete[](void*)();
          *plVar2 = 0;
        }
        lVar1 = lVar1 + -1;
        plVar2 = plVar2 + 2;
      } while (lVar1 != 0);
      if (param_1[8] != param_1[6]) {
        param_1[7] = param_1[6];
      }
      if (param_1[0xd] != param_1[0xb]) {
        param_1[0xc] = param_1[0xb];
      }
    }
    lVar1 = Aska::Global::GetCPUTime()();
    param_1[0xdf] = lVar1;
    *(undefined1 *)((long)param_1 + 0x712) = 0;
  }
  return;
}

// ==== undefined Aska::Yayoi::IMultiplayManagerBase::RunSnapshot(void)
// _ZN4Aska5Yayoi21IMultiplayManagerBase11RunSnapshotEv @ 022f7834

void _ZN4Aska5Yayoi21IMultiplayManagerBase11RunSnapshotEv(long param_1)

{
  long lVar1;
  undefined8 uVar2;
  
  if (*(char *)(param_1 + 0x711) == '\0') {
    return;
  }
  lVar1 = Aska::Global::GetCPUTime()();
  if ((ulong)(lVar1 - *(long *)(param_1 + 0x708)) < *(ulong *)(param_1 + 0x700)) {
    if (*(char *)(param_1 + 0x713) == '\0') goto code_r0x011b54a0;
  }
  else {
    *(undefined1 *)(param_1 + 0x713) = 1;
  }
  Aska::Yayoi::IMultiplayManagerBase::FlushSendSnapshot()(param_1);
  uVar2 = Aska::Global::GetCPUTime()();
  *(undefined8 *)(param_1 + 0x708) = uVar2;
  *(undefined1 *)(param_1 + 0x713) = 0;
code_r0x011b54a0:
  (*(code *)PTR__ZN4Aska5Yayoi21IMultiplayManagerBase20FlushReceiveSnapshotEv_02c92a40)(param_1);
  return;
}

// ==== undefined Aska::Yayoi::IMultiplayManagerBase::FlushSendMessage(void)
// _ZN4Aska5Yayoi21IMultiplayManagerBase16FlushSendMessageEv @ 022f7898

void _ZN4Aska5Yayoi21IMultiplayManagerBase16FlushSendMessageEv(long *param_1)

{
  long *plVar1;
  long lVar2;
  undefined1 auStack_28 [8];
  
  plVar1 = (long *)param_1[6];
  lVar2 = param_1[7] - (long)plVar1 >> 4;
  if (lVar2 != 0) {
    (**(code **)(*param_1 + 0x98))(auStack_28,param_1,plVar1,lVar2);
    do {
      if ((0x80 < (int)plVar1[1]) && (*plVar1 != 0)) {
        operator delete[](void*)();
        *plVar1 = 0;
      }
      lVar2 = lVar2 + -1;
      plVar1 = plVar1 + 2;
    } while (lVar2 != 0);
    if (param_1[8] != param_1[6]) {
      param_1[7] = param_1[6];
    }
    if (param_1[0xd] != param_1[0xb]) {
      param_1[0xc] = param_1[0xb];
    }
  }
  return;
}

// ==== undefined Aska::Yayoi::IMultiplayManagerBase::FlushSendSnapshot(void)
// _ZN4Aska5Yayoi21IMultiplayManagerBase17FlushSendSnapshotEv @ 022f7934

void _ZN4Aska5Yayoi21IMultiplayManagerBase17FlushSendSnapshotEv(long *param_1)

{
  long *plVar1;
  undefined *puVar2;
  long lVar3;
  long lVar4;
  undefined8 uStack_b8;
  long alStack_b0 [16];
  
  puVar2 = PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
  if (param_1[0x59] != 0) {
    plVar1 = param_1 + 0xf;
    while( true ) {
      Aska::Yayoi::IMultiplayManagerBase::RearrangeSendObject(Aska::ISnapshotObject**, unsigned long*)(param_1,alStack_b0,&uStack_b8);
      if ((int)param_1[0x40] == 0) {
        lVar3 = Aska::SnapshotManager::SerializeFullImage(void*, unsigned long, Aska::ISnapshotObject**, unsigned long, long) const(plVar1,param_1[0x5a],param_1[0x5b],alStack_b0,uStack_b8,
                                0xffffffffffffffff);
      }
      else {
        lVar3 = Aska::SnapshotManager::SerializeDiffImage(void*, unsigned long, Aska::ISnapshotObject**, unsigned long, long, long) const(plVar1);
      }
      if (-1 < lVar3) break;
      if (lVar3 != -0x3c1) {
        return;
      }
      if (((long *)param_1[0x5a] != param_1 + 0x5c) && ((long *)param_1[0x5a] != (long *)0x0)) {
        operator delete[](void*)();
        param_1[0x5a] = 0;
      }
      lVar3 = param_1[0x5b] << 1;
      if (lVar3 == 0) {
        param_1[0x5a] = 0;
        return;
      }
      lVar4 = **(long **)puVar2;
      if (lVar4 == 0) {
        lVar4 = Aska::Global::GetAvailableMemoryManager()();
      }
      lVar4 = Aska::MemoryManager::Malloc(unsigned long)(lVar4,lVar3);
      param_1[0x5a] = lVar4;
      if (lVar4 == 0) {
        return;
      }
      param_1[0x5b] = lVar3;
    }
    (**(code **)(*param_1 + 0xa0))(alStack_b0,param_1,param_1[0x5a],lVar3);
    if (-1 < alStack_b0[0]) {
      Aska::SnapshotManager::TakeSnapshot()(plVar1);
    }
  }
  return;
}

