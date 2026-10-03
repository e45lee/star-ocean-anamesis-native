// ui_lambdas: Ghidra decompiles of work/libSOA-3.7.0.so (3.7.0), extracted by extract.py.
// Data, not code: see README.md and docs/multiplayer.md for what they show.

// ==== FUN_01d1afe8 @01d1afe8 (for 01d1b00c)

uint FUN_01d1afe8(long param_1)

{
  undefined8 local_8;
  
  Aska::Yayoi::MultiplayRPC::Cli::LobbyProtocolProxy::SendCreateRoom
            ((LobbyProtocolProxy *)(*(long *)(*(long *)PTR_m_pInstance_02cc2908 + 0x40) + 8),
             (PlayerInfo *)(param_1 + 0x10),(RoomCondition *)(param_1 + 0x490));
  return (uint)((ulong)local_8 >> 0x3f) ^ 1;
}


// NOFUNC @01d1d894
// NOFUNC @01d1da24
// NOFUNC @01d1db28
// NOFUNC @01d1e334
// NOFUNC @01d216b0

// ==== FUN_01d1af10 @01d1af10 (for 01d1af34)

uint FUN_01d1af10(long param_1)

{
  undefined8 local_8;
  
  Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendEnterRoom
            ((BattleProtocolProxy *)(*(long *)(*(long *)PTR_m_pInstance_02cc2908 + 0x48) + 8),
             (PlayerDetailInfo *)(param_1 + 0x10),*(int *)(param_1 + 0x490));
  return (uint)((ulong)local_8 >> 0x3f) ^ 1;
}


// NOFUNC @01d1a20c

// ==== FUN_01d1b5cc @01d1b5cc (for 01d1b5e8)

uint FUN_01d1b5cc(void)

{
  undefined8 uVar1;
  undefined8 local_8;
  
  uVar1 = *(undefined8 *)PTR_m_pInstance_02cc2908;
  Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendUpdatePlayerList();
  return (uint)((ulong)local_8 >> 0x3f) ^ 1;
}

// ==== FUN_01d1b874 @01d1b874 (for 01d1b890)

uint FUN_01d1b874(void)

{
  undefined8 uVar1;
  undefined8 local_8;
  
  uVar1 = *(undefined8 *)PTR_m_pInstance_02cc2908;
  Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendUpdatePlayerList();
  return (uint)((ulong)local_8 >> 0x3f) ^ 1;
}


// NOFUNC @01d1ed3c

// ==== FUN_01d1f2cc @01d1f2cc (for 01d1f2f0)

uint FUN_01d1f2cc(void)

{
  undefined1 local_8 [4];
  uint uStack_4;
  
  Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendExitRoom
            (local_8,*(long *)(*(long *)PTR_m_pInstance_02cc2908 + 0x48) + 8,0,0);
  return uStack_4 >> 0x1f ^ 1;
}

// ==== FUN_01d1ff48 @01d1ff48 (for 01d1ff6c)

uint FUN_01d1ff48(long param_1)

{
  undefined1 local_8 [4];
  uint uStack_4;
  
  Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendExitRoom
            (local_8,*(long *)(*(long *)PTR_m_pInstance_02cc2908 + 0x48) + 8,1,
             *(undefined4 *)(param_1 + 0x10));
  return uStack_4 >> 0x1f ^ 1;
}

// ==== FUN_01d20a1c @01d20a1c (for 01d20a3c)

uint FUN_01d20a1c(long param_1)

{
  undefined1 local_8 [4];
  uint uStack_4;
  
  Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendChangePublicRoom
            (local_8,*(long *)(*(long *)PTR_m_pInstance_02cc2908 + 0x48) + 8,
             *(undefined1 *)(param_1 + 0x10));
  return uStack_4 >> 0x1f ^ 1;
}

// ==== CBattleManager::BattleTimeFrame @012c10fc (for 012c1158)

/* CBattleManager::BattleTimeFrame(float, bool) */

void __thiscall CBattleManager::BattleTimeFrame(CBattleManager *this,float param_1,bool param_2)

{
  long lVar1;
  undefined1 auStack_8 [8];
  
  if ((*(long *)(this + 0x1520) != *(long *)(this + 0x1528)) && (param_2)) {
    if ((DAT_027e8410 < ABS(*(float *)(this + 0x20b8) - param_1)) &&
       ((*(long *)PTR_m_pInstance_02cc2908 != 0 &&
        (lVar1 = *(long *)(*(long *)PTR_m_pInstance_02cc2908 + 0x48), lVar1 != 0)))) {
      Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendExitRoom(auStack_8,lVar1 + 8,0,0);
    }
    return;
  }
  *(float *)(this + 0x20b8) = param_1;
  return;
}

// ==== FUN_01d1592c @01d1592c (for 01d15940)

void FUN_01d1592c(long param_1)

{
  ulong uVar1;
  CMultiPlay3 *this;
  
  this = *(CMultiPlay3 **)(param_1 + 8);
  this[0xb944] = (CMultiPlay3)0x0;
  uVar1 = CMultiPlay3::Server_InitializeCommon(this);
  if ((uVar1 & 1) != 0) {
    return;
  }
  CMultiPlay3::State(this,0x10);
  return;
}

// ==== @01d1d854

uint FUN_01d1d854(long param_1)

{
  RoomCondition aRStack_208 [488];
  undefined8 uStack_18;
  
  memcpy(aRStack_208,(void *)(param_1 + 0x490),0x1e8);
  Aska::Yayoi::MultiplayRPC::Cli::LobbyProtocolProxy::SendAutomatch
            ((LobbyProtocolProxy *)(*(long *)(*(long *)PTR_m_pInstance_02cc2908 + 0x40) + 8),
             (PlayerInfo *)(param_1 + 0x10),aRStack_208);
  return (uint)((ulong)uStack_18 >> 0x3f) ^ 1;
}

// ==== @01d1d9dc

uint FUN_01d1d9dc(long param_1)

{
  RoomCondition aRStack_208 [488];
  undefined8 uStack_18;
  
  memcpy(aRStack_208,(void *)(param_1 + 0x490),0x1e8);
  Aska::Yayoi::MultiplayRPC::Cli::LobbyProtocolProxy::SendGetRoomList
            ((LobbyProtocolProxy *)(*(long *)(*(long *)PTR_m_pInstance_02cc2908 + 0x40) + 8),
             (PlayerInfo *)(param_1 + 0x10),aRStack_208,0,0x32);
  return (uint)((ulong)uStack_18 >> 0x3f) ^ 1;
}

// ==== @01d1dae0

uint FUN_01d1dae0(long param_1)

{
  RoomCondition aRStack_208 [488];
  undefined8 uStack_18;
  
  memcpy(aRStack_208,(void *)(param_1 + 0x490),0x1e8);
  Aska::Yayoi::MultiplayRPC::Cli::LobbyProtocolProxy::SendGetRoomList
            ((LobbyProtocolProxy *)(*(long *)(*(long *)PTR_m_pInstance_02cc2908 + 0x40) + 8),
             (PlayerInfo *)(param_1 + 0x10),aRStack_208,0,0x32);
  return (uint)((ulong)uStack_18 >> 0x3f) ^ 1;
}

// ==== @01d1e2ec

uint FUN_01d1e2ec(long param_1)

{
  RoomCondition aRStack_208 [488];
  undefined8 uStack_18;
  
  memcpy(aRStack_208,(void *)(param_1 + 0x490),0x1e8);
  Aska::Yayoi::MultiplayRPC::Cli::LobbyProtocolProxy::SendGetRoomList
            ((LobbyProtocolProxy *)(*(long *)(*(long *)PTR_m_pInstance_02cc2908 + 0x40) + 8),
             (PlayerInfo *)(param_1 + 0x10),aRStack_208,0,10);
  return (uint)((ulong)uStack_18 >> 0x3f) ^ 1;
}

// ==== @01d21610

void FUN_01d21610(long param_1)

{
  ulong uVar1;
  undefined4 uVar2;
  CMultiPlay3 *pCVar3;
  ulong uVar4;
  
  pCVar3 = *(CMultiPlay3 **)(param_1 + 8);
  if ((pCVar3[0xb945] == (CMultiPlay3)0x0) && (pCVar3[0xb941] == (CMultiPlay3)0x0)) {
    uVar4 = (ulong)*(uint *)(pCVar3 + 0xb924);
    uVar1 = (*(long *)(pCVar3 + 0x1e0) - *(long *)(pCVar3 + 0x1d8) >> 3) * 0x1ef24c80742dd08b;
    if (uVar1 < uVar4 || uVar1 - uVar4 == 0) {
                    /* WARNING: Subroutine does not return */
      Framework::gDoAssert
                ("C:\\BAS_Submission\\Client\\Project\\../Library/Framework/Source\\Framework/STL_Vector.h"
                 ,0x58,"The argument has gotten numeric out of range.(%d/%d)",uVar4);
    }
    Aska::Yayoi::MultiplayRPC::Cli::LobbyProtocolProxy::SendCloseRoom
              ((LobbyProtocolProxy *)(*(long *)(*(long *)PTR_m_pInstance_02cc2908 + 0x40) + 8),
               *(int *)(*(long *)(pCVar3 + 0x1d8) + uVar4 * 0xb918 + 0x44c),0);
  }
  if (pCVar3[0xb947] == (CMultiPlay3)0x0) {
    uVar2 = 7;
    if (*(int *)(pCVar3 + 0xb728) != 5) {
      uVar2 = 4;
    }
  }
  else {
    uVar2 = 0xf;
  }
  CMultiPlay3::State(pCVar3,uVar2);
  return;
}

// ==== @01d1a1cc

uint FUN_01d1a1cc(void)

{
  undefined8 uStack_18;
  
  if (*(long *)PTR_m_pInstance_02cc2908 == 0) {
                    /* WARNING: Subroutine does not return */
    Framework::gDoAssert
              ("C:\\BAS_Submission\\Client\\Project\\../Library/Framework/Source\\Framework/TSingleton.h"
               ,0x23,"m_pInstance is null.");
  }
  Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendStartMultiplay();
  return (uint)((ulong)uStack_18 >> 0x3f) ^ 1;
}

// ==== @01d1eb28

uint FUN_01d1eb28(long param_1)

{
  IMultiplayNotify *pIVar1;
  undefined *puVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  undefined8 uStack_48;
  
  lVar6 = *(long *)(param_1 + 8);
  if (*(CParameterManager **)PTR_m_pInstance_02cbf9c0 == (CParameterManager *)0x0) {
                    /* WARNING: Subroutine does not return */
    Framework::gDoAssert
              ("C:\\BAS_Submission\\Client\\Project\\../Library/Framework/Source\\Framework/TSingleton.h"
               ,0x23,"m_pInstance is null.");
  }
  lVar3 = CParameterManager::pParameterUI(*(CParameterManager **)PTR_m_pInstance_02cbf9c0);
  uVar5 = (ulong)*(uint *)(param_1 + 0x490);
  uVar4 = (*(long *)(lVar6 + 0x1e0) - *(long *)(lVar6 + 0x1d8) >> 3) * 0x1ef24c80742dd08b;
  if (uVar4 < uVar5 || uVar4 - uVar5 == 0) {
                    /* WARNING: Subroutine does not return */
    Framework::gDoAssert
              ("C:\\BAS_Submission\\Client\\Project\\../Library/Framework/Source\\Framework/STL_Vector.h"
               ,0x58,"The argument has gotten numeric out of range.(%d/%d)",uVar5);
  }
  *(bool *)(lVar3 + 0x1cf) = *(char *)(*(long *)(lVar6 + 0x1d8) + uVar5 * 0xb918 + 0x424) == '\0';
  *(undefined4 *)(lVar6 + 0xb924) = *(undefined4 *)(param_1 + 0x490);
  puVar2 = PTR_m_pInstance_02cc2908;
  lVar3 = *(long *)(lVar6 + 0x1d8);
  uVar5 = (ulong)*(uint *)(param_1 + 0x490);
  uVar4 = (*(long *)(lVar6 + 0x1e0) - lVar3 >> 3) * 0x1ef24c80742dd08b;
  if (uVar4 < uVar5 || uVar4 - uVar5 == 0) {
                    /* WARNING: Subroutine does not return */
    Framework::gDoAssert
              ("C:\\BAS_Submission\\Client\\Project\\../Library/Framework/Source\\Framework/STL_Vector.h"
               ,0x58,"The argument has gotten numeric out of range.(%d/%d)",uVar5);
  }
  uVar4 = (*(long *)(lVar6 + 0x1e0) - lVar3 >> 3) * 0x1ef24c80742dd08b;
  if (uVar4 < uVar5 || uVar4 - uVar5 == 0) {
                    /* WARNING: Subroutine does not return */
    Framework::gDoAssert
              ("C:\\BAS_Submission\\Client\\Project\\../Library/Framework/Source\\Framework/STL_Vector.h"
               ,0x58,"The argument has gotten numeric out of range.(%d/%d)",uVar5);
  }
  pIVar1 = (IMultiplayNotify *)0x0;
  if (*(long *)(lVar6 + 0x1b8) != 0) {
    pIVar1 = (IMultiplayNotify *)(*(long *)(lVar6 + 0x1b8) + 8);
  }
  CMultiplayManager::InitBattleRPCClient
            (*(CMultiplayManager **)PTR_m_pInstance_02cc2908,
             (char *)(lVar3 + uVar5 * 0xb918 + 0x42a),*(ushort *)(lVar3 + uVar5 * 0xb918 + 0x428),
             pIVar1);
  uVar5 = (ulong)*(uint *)(param_1 + 0x490);
  uVar4 = (*(long *)(lVar6 + 0x1e0) - *(long *)(lVar6 + 0x1d8) >> 3) * 0x1ef24c80742dd08b;
  if (uVar4 < uVar5 || uVar4 - uVar5 == 0) {
                    /* WARNING: Subroutine does not return */
    Framework::gDoAssert
              ("C:\\BAS_Submission\\Client\\Project\\../Library/Framework/Source\\Framework/STL_Vector.h"
               ,0x58,"The argument has gotten numeric out of range.(%d/%d)",uVar5);
  }
  Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendEnterRoom
            ((BattleProtocolProxy *)(*(long *)(*(long *)puVar2 + 0x48) + 8),
             (PlayerDetailInfo *)(param_1 + 0x10),
             *(int *)(*(long *)(lVar6 + 0x1d8) + uVar5 * 0xb918 + 0x44c));
  return (uint)((ulong)uStack_48 >> 0x3f) ^ 1;
}

// ==== @01d1a588

void FUN_01d1a588(long param_1,long param_2)

{
  IMultiplayNotify *pIVar1;
  undefined4 uVar2;
  undefined *puVar3;
  long lVar4;
  long *plVar5;
  function<void(int,Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*,unsigned_short)> *pfVar6;
  undefined8 uVar7;
  RoomInfo *pRVar8;
  CMultiPlay3 *this;
  RoomInfo **ppRVar9;
  code *pcVar10;
  RoomInfo *pRVar11;
  RoomInfo *apRStack_540 [2];
  long alStack_530 [2];
  long *plStack_520;
  long *plStack_510;
  RoomInfo *apRStack_c0 [2];
  long alStack_b0 [2];
  RoomInfo **ppRStack_a0;
  long *plStack_90;
  function<void(int,Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*,unsigned_short)> afStack_80 [32];
  function<void(int,Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*,unsigned_short)> *pfStack_60;
  
  pRVar11 = *(RoomInfo **)(param_1 + 0x10);
  *(undefined4 *)(pRVar11 + 0xb920) = 0x3c;
  CMultiPlay3::RoomInfo2RoomData(pRVar11,SUB81(param_2,0));
  puVar3 = PTR_m_pInstance_02cbf9c0;
  if (*(CParameterManager **)PTR_m_pInstance_02cbf9c0 == (CParameterManager *)0x0) {
                    /* WARNING: Subroutine does not return */
    Framework::gDoAssert
              ("C:\\BAS_Submission\\Client\\Project\\../Library/Framework/Source\\Framework/TSingleton.h"
               ,0x23,"m_pInstance is null.");
  }
  lVar4 = CParameterManager::pParameterUI(*(CParameterManager **)PTR_m_pInstance_02cbf9c0);
  *(bool *)(lVar4 + 0x1cf) = *(char *)(param_2 + 0x424) == '\0';
  *(undefined4 *)(pRVar11 + 0xb950) = 0;
  plVar5 = *(long **)(param_1 + 0x40);
  pRVar8 = pRVar11;
  apRStack_c0[0] = pRVar11;
  if (plVar5 == (long *)0x0) {
    plStack_90 = (long *)0x0;
  }
  else if ((long *)(param_1 + 0x20) == plVar5) {
    plStack_90 = alStack_b0;
    (**(code **)(*plVar5 + 0x18))();
    pRVar8 = apRStack_c0[0];
  }
  else {
    plStack_90 = (long *)(**(code **)(*plVar5 + 0x10))();
  }
  lVar4 = *(long *)(pRVar11 + 0x1b8);
  apRStack_540[0] = pRVar8;
  if (plStack_90 == (long *)0x0) {
    plStack_510 = (long *)0x0;
  }
  else if (alStack_b0 == plStack_90) {
    plStack_510 = alStack_530;
    (**(code **)(*plStack_90 + 0x18))();
    pRVar8 = apRStack_540[0];
  }
  else {
    plStack_510 = (long *)(**(code **)(*plStack_90 + 0x10))();
  }
  plVar5 = plStack_510;
  pfStack_60 = (function<void(int,Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*,unsigned_short)> *)
               0x0;
  pfVar6 = operator_new(0x50);
  *(undefined ***)pfVar6 = &PTR_LAB_02b732b8;
  *(RoomInfo **)(pfVar6 + 0x10) = pRVar8;
  if (plVar5 == (long *)0x0) {
    *(undefined8 *)(pfVar6 + 0x40) = 0;
  }
  else if (alStack_530 == plVar5) {
    *(function<void(int,Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*,unsigned_short)> **)
     (pfVar6 + 0x40) = pfVar6 + 0x20;
    (**(code **)(*plVar5 + 0x18))(plVar5);
  }
  else {
    uVar7 = (**(code **)(*plVar5 + 0x10))(plVar5);
    *(undefined8 *)(pfVar6 + 0x40) = uVar7;
  }
  pfStack_60 = pfVar6;
  std::__ndk1::function<void(int,Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*,unsigned_short)>::swap
            (afStack_80,(function *)(lVar4 + 0xe0));
  if (afStack_80 == pfStack_60) {
    pcVar10 = *(code **)(*(long *)pfStack_60 + 0x20);
LAB_01d1a770:
    (*pcVar10)();
  }
  else if (pfStack_60 !=
           (function<void(int,Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*,unsigned_short)> *)0x0) {
    pcVar10 = *(code **)(*(long *)pfStack_60 + 0x28);
    goto LAB_01d1a770;
  }
  if (alStack_530 == plStack_510) {
    pcVar10 = *(code **)(*plStack_510 + 0x20);
LAB_01d1a7a0:
    (*pcVar10)();
  }
  else if (plStack_510 != (long *)0x0) {
    pcVar10 = *(code **)(*plStack_510 + 0x28);
    goto LAB_01d1a7a0;
  }
  if (alStack_b0 == plStack_90) {
    pcVar10 = *(code **)(*plStack_90 + 0x20);
LAB_01d1a7d0:
    (*pcVar10)();
  }
  else if (plStack_90 != (long *)0x0) {
    pcVar10 = *(code **)(*plStack_90 + 0x28);
    goto LAB_01d1a7d0;
  }
  pRVar8 = *(RoomInfo **)(pRVar11 + 0xb7e0);
  if (pRVar11 + 0xb7c0 == pRVar8) {
    pcVar10 = *(code **)(*(long *)pRVar8 + 0x20);
LAB_01d1a808:
    (*pcVar10)();
  }
  else if (pRVar8 != (RoomInfo *)0x0) {
    pcVar10 = *(code **)(*(long *)pRVar8 + 0x28);
    goto LAB_01d1a808;
  }
  *(long *)(pRVar11 + 0xb7e0) = 0;
  plStack_520 = (long *)0x0;
  std::__ndk1::function<bool(Aska::Status)>::swap
            ((function<bool(Aska::Status)> *)apRStack_540,(function *)(pRVar11 + 0xb7f0));
  if (apRStack_540 == (RoomInfo **)plStack_520) {
    pcVar10 = *(code **)(*plStack_520 + 0x20);
LAB_01d1a84c:
    (*pcVar10)();
  }
  else if (plStack_520 != (long *)0x0) {
    pcVar10 = *(code **)(*plStack_520 + 0x28);
    goto LAB_01d1a84c;
  }
  pRVar8 = *(RoomInfo **)(pRVar11 + 0xb840);
  if (pRVar11 + 0xb820 == pRVar8) {
    pcVar10 = *(code **)(*(long *)pRVar8 + 0x20);
  }
  else {
    if (pRVar8 == (RoomInfo *)0x0) goto LAB_01d1a888;
    pcVar10 = *(code **)(*(long *)pRVar8 + 0x28);
  }
  (*pcVar10)();
LAB_01d1a888:
  *(long *)(pRVar11 + 0xb840) = 0;
  if (*(CParameterManager **)puVar3 == (CParameterManager *)0x0) {
                    /* WARNING: Subroutine does not return */
    Framework::gDoAssert
              ("C:\\BAS_Submission\\Client\\Project\\../Library/Framework/Source\\Framework/TSingleton.h"
               ,0x23,"m_pInstance is null.");
  }
  this = (CMultiPlay3 *)CParameterManager::pParameterUI(*(CParameterManager **)puVar3);
  CMultiPlay3::Server_CreatePlayerInfo(this,(PlayerDetailInfo *)apRStack_540,*(int *)(this + 0x1b0))
  ;
  pIVar1 = (IMultiplayNotify *)0x0;
  if (*(long *)(pRVar11 + 0x1b8) != 0) {
    pIVar1 = (IMultiplayNotify *)(*(long *)(pRVar11 + 0x1b8) + 8);
  }
  CMultiplayManager::InitBattleRPCClient
            (*(CMultiplayManager **)PTR_m_pInstance_02cc2908,(char *)(param_2 + 0x42a),
             *(ushort *)(param_2 + 0x428),pIVar1);
  uVar2 = *(undefined4 *)(param_2 + 0x44c);
  ppRVar9 = operator_new(0x498);
  *ppRVar9 = (RoomInfo *)&PTR_LAB_02b73348;
  ppRVar9[1] = pRVar11;
  memcpy(ppRVar9 + 2,apRStack_540,0x480);
  *(undefined4 *)(ppRVar9 + 0x92) = uVar2;
  ppRStack_a0 = ppRVar9;
  CMultiPlay3::RegistCall((function *)pRVar11,SUB81(apRStack_c0,0),1);
  if (apRStack_c0 == ppRStack_a0) {
    pcVar10 = *(code **)(*ppRStack_a0 + 0x20);
  }
  else {
    if (ppRStack_a0 == (RoomInfo **)0x0) {
      return;
    }
    pcVar10 = *(code **)(*ppRStack_a0 + 0x28);
  }
  (*pcVar10)();
  return;
}

