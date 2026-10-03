// ui_flow: Ghidra decompiles of work/libSOA-3.7.0.so (3.7.0), extracted by extract.py.
// Data, not code: see README.md and docs/multiplayer.md for what they show.

// ==== undefined Aska::Yayoi::MatchingClient::Init(Aska::TSharedPointer<Aska::Yayoi::URI>,Aska::Yayoi::IMatchingNotify *)
// _ZN4Aska5Yayoi14MatchingClient4InitENS_14TSharedPointerINS0_3URIEEEPNS0_15IMatchingNotifyE @ 022f5b58

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN4Aska5Yayoi14MatchingClient4InitENS_14TSharedPointerINS0_3URIEEEPNS0_15IMatchingNotifyE
               (long *param_1,long param_2,long *param_3,long param_4)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  long lVar9;
  long lStack_50;
  int *piStack_48;
  undefined1 auStack_40 [8];
  long lStack_38;
  
  if ((param_4 == 0) || (lStack_50 = *param_3, lStack_50 == 0)) {
    lStack_38 = -0x3bd;
    goto code_r0x022f5ca8;
  }
  if (-1 < *(int *)(param_2 + 0x19c)) {
    Aska::Yayoi::MatchingClient::ResetPeer()(param_2);
    if (*(long *)(param_2 + 0x28) != 0) {
      Aska::Yayoi::NetworkEvent::DeregisterTransporter(Aska::Yayoi::NetworkBuffer::Type, Aska::Yayoi::TCP*)(&lStack_38,*(long *)(param_2 + 0x28),0,param_2 + 400);
      Aska::Yayoi::NetworkEvent::DeregisterTransporter(Aska::Yayoi::NetworkBuffer::Type, Aska::Yayoi::TCP*)(auStack_40,*(undefined8 *)(param_2 + 0x28),1,param_2 + 400);
    }
    *(undefined1 *)(param_2 + 800) = 0;
    *(undefined8 *)(param_2 + 0x3f0) = 0;
    lStack_50 = *param_3;
  }
  piStack_48 = (int *)param_3[1];
  if (piStack_48 != (int *)0x0) {
    do {
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_48,0x10);
      if (bVar3) {
        *piStack_48 = *piStack_48 + 1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
  }
  Aska::Yayoi::TARPCPeer<Aska::Yayoi::MultiplayRPC::Cli::LobbyProtocolProxy>::Initialize(Aska::Yayoi::MultiplayRPC::Cli::ILobbyProtocolNotify*, Aska::TSharedPointer<Aska::Yayoi::URI>, Aska::Yayoi::NetworkEvent*, long, bool)(&lStack_38,param_2,param_2 + 0x3e0,&lStack_50,0,0,0);
  lVar9 = lStack_50;
  if (piStack_48 == (int *)0x0) {
code_r0x022f5c2c:
    if (lStack_50 != 0) {
      Aska::Yayoi::URI::DeleteBuffer()(lStack_50);
      operator delete(void*)(lVar9);
    }
    if (piStack_48 != (int *)0x0) {
      Aska::TSharedPointerCode::DeleteCounter(int*)();
    }
  }
  else {
    do {
      iVar1 = *piStack_48;
      cVar2 = '\x01';
      bVar3 = (bool)ExclusiveMonitorPass(piStack_48,0x10);
      if (bVar3) {
        *piStack_48 = iVar1 + -1;
        cVar2 = ExclusiveMonitorsStatus();
      }
    } while (cVar2 != '\0');
    if (iVar1 + -1 == 0) goto code_r0x022f5c2c;
  }
  if (-1 < lStack_38) {
    *(undefined4 *)(param_2 + 0x6c) = 0;
    uVar7 = _UNK_0281a957;
    uVar6 = _UNK_0281a94f;
    uVar5 = _UNK_0281a947;
    uVar4 = _UNK_0281a93f;
    *(undefined1 *)(param_2 + 0xbd) = 1;
    *(undefined4 *)(param_2 + 0x78) = 0x474a6152;
    uVar8 = _UNK_0281a95f;
    *(undefined1 *)(param_2 + 0xbc) = 1;
    *(undefined8 *)(param_2 + 100) = uVar7;
    *(undefined8 *)(param_2 + 0x5c) = uVar6;
    *(undefined8 *)(param_2 + 0x54) = uVar5;
    *(undefined8 *)(param_2 + 0x4c) = uVar4;
    *(undefined8 *)(param_2 + 0x70) = uVar8;
    *(long *)(param_2 + 0x3f0) = param_4;
  }
code_r0x022f5ca8:
  *param_1 = lStack_38;
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::ResetPeer(void)
// _ZN4Aska5Yayoi14MatchingClient9ResetPeerEv @ 022f61a0

void _ZN4Aska5Yayoi14MatchingClient9ResetPeerEv(long param_1)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  undefined1 auStack_30 [8];
  long lStack_28;
  
  lVar1 = param_1 + 0x20;
  if (*(long *)(param_1 + 0x28) != 0) {
    plVar2 = *(long **)(*(long *)(param_1 + 0x28) + 0x540);
    if (plVar2 == (long *)0x0) {
      lVar3 = 0;
    }
    else {
      lVar3 = (**(code **)(*plVar2 + 0x18))();
    }
    lVar4 = Aska::Thread::GetCurrentID()();
    if ((((lVar3 != lVar4) &&
         (plVar2 = *(long **)(*(long *)(param_1 + 0x28) + 0x540), plVar2 != (long *)0x0)) &&
        (lVar3 = (**(code **)(*plVar2 + 0x18))(), lVar3 != 0)) &&
       (((Aska::Yayoi::TPeer<Aska::Yayoi::TCP, Aska::Yayoi::TProtocolSuite<Aska::Yayoi::MultiplayRPC::LobbyProtocol, Aska::Yayoi::NoProtocol<1>, Aska::Yayoi::NoProtocol<2> >, true>::RequestTerm()(&lStack_28,lVar1), lStack_28 < 0 ||
         (Aska::Yayoi::TPeer<Aska::Yayoi::TCP, Aska::Yayoi::TProtocolSuite<Aska::Yayoi::MultiplayRPC::LobbyProtocol, Aska::Yayoi::NoProtocol<1>, Aska::Yayoi::NoProtocol<2> >, true>::WaitTerm()(lVar1), lStack_28 < 0)) && (lStack_28 == -0x3ea)))) {
      return;
    }
  }
  if (*(long *)(param_1 + 0x3b0) != 0) {
    Aska::TPriorityQueue<Aska::Yayoi::TARPCPeer<Aska::Yayoi::MultiplayRPC::Cli::LobbyProtocolProxy>::SendingContext, true>::ClearQueue()();
  }
  if (*(long *)(param_1 + 0x3b8) != 0) {
    Aska::TPriorityQueue<Aska::Yayoi::TARPCPeer<Aska::Yayoi::MultiplayRPC::Cli::LobbyProtocolProxy>::SendingContext, true>::ClearQueue()();
  }
  if (*(char *)(param_1 + 0x325) == '\0') {
    Aska::Yayoi::TPeer<Aska::Yayoi::TCP, Aska::Yayoi::TProtocolSuite<Aska::Yayoi::MultiplayRPC::LobbyProtocol, Aska::Yayoi::NoProtocol<1>, Aska::Yayoi::NoProtocol<2> >, true>::_inner_close(bool)(auStack_30,lVar1,1);
  }
  return;
}

// ==== undefined CParameterUtility::IsOpenMulti(bool)
// _ZN17CParameterUtility11IsOpenMultiEb @ 01839aa8

bool _ZN17CParameterUtility11IsOpenMultiEb(ulong param_1)

{
  byte bVar1;
  undefined *puVar2;
  long lVar3;
  
  puVar2 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if ((param_1 & 1) != 0) {
    if (lVar3 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar3 = *(long *)puVar2;
      bVar1 = *(byte *)(lVar3 + 0xe08);
    }
    else {
      bVar1 = *(byte *)(lVar3 + 0xe08);
    }
    if ((bVar1 >> 4 & 1) == 0) {
      return false;
    }
  }
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar2;
  }
  return *(char *)(lVar3 + 0x1ac8) != '\0';
}

// ==== undefined CMissionMenu::ToMultiUI_ParameterUISet(void)
// _ZN12CMissionMenu24ToMultiUI_ParameterUISetEv @ 01ce68d4

/* WARNING: Removing unreachable block (ram,0x01ce6bc0) */
/* WARNING: Removing unreachable block (ram,0x01ce6bd0) */
/* WARNING: Removing unreachable block (ram,0x01ce6be0) */

void _ZN12CMissionMenu24ToMultiUI_ParameterUISetEv(long param_1)

{
  ulong *puVar1;
  ulong *puVar2;
  byte *pbVar3;
  byte bVar4;
  undefined *puVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  undefined1 *puVar10;
  ulong uVar11;
  ulong uVar12;
  
  puVar5 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar7 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar7 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar7 = *(long *)puVar5;
  }
  lVar7 = CParameterManager::pParameterUI() const(lVar7);
  lVar8 = *(long *)(param_1 + 0x498);
  if (lVar8 != *(long *)(param_1 + 0x4a0)) {
    uVar12 = (ulong)*(int *)(param_1 + 0x768);
    if ((ulong)(*(long *)(param_1 + 0x4a0) - lVar8 >> 6) <= uVar12) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar12);
      lVar8 = *(long *)(param_1 + 0x498);
    }
    *(undefined4 *)(lVar7 + 0x150) = *(undefined4 *)(lVar8 + uVar12 * 0x40);
  }
  uVar12 = (ulong)*(int *)(param_1 + 0x76c);
  if ((-1 < *(int *)(param_1 + 0x76c)) &&
     (uVar11 = (*(long *)(param_1 + 0x4b8) - *(long *)(param_1 + 0x4b0) >> 3) * 0x2e8ba2e8ba2e8ba3,
     uVar12 <= uVar11 && uVar11 - uVar12 != 0)) {
    *(undefined4 *)(lVar7 + 0x154) =
         *(undefined4 *)(*(long *)(param_1 + 0x4b0) + uVar12 * 0x58 + 0x44);
  }
  uVar12 = (ulong)*(int *)(param_1 + 0x770);
  if ((*(int *)(param_1 + 0x770) < 0) ||
     (uVar11 = (*(long *)(param_1 + 0x4d0) - *(long *)(param_1 + 0x4c8) >> 3) * -0x2c8590b21642c859,
     uVar11 < uVar12 || uVar11 - uVar12 == 0)) goto code_r0x01ce6b0c;
  *(undefined4 *)(lVar7 + 0x1a0) =
       *(undefined4 *)(*(long *)(param_1 + 0x4c8) + uVar12 * 0xb8 + 0x98);
  lVar8 = *(long *)(param_1 + 0x4c8);
  uVar11 = (ulong)*(int *)(param_1 + 0x770);
  uVar12 = (*(long *)(param_1 + 0x4d0) - lVar8 >> 3) * -0x2c8590b21642c859;
  if (uVar12 < uVar11 || uVar12 - uVar11 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar11);
    lVar8 = *(long *)(param_1 + 0x4c8);
  }
  lVar9 = lVar8 + uVar11 * 0xb8;
  puVar1 = (ulong *)(lVar9 + 0x18);
  puVar2 = (ulong *)(lVar7 + 0x158);
  if (puVar2 == puVar1) goto code_r0x01ce6b0c;
  bVar4 = *(byte *)puVar1;
  lVar8 = lVar8 + uVar11 * 0xb8;
  uVar11 = (ulong)*(byte *)puVar2;
  uVar12 = (ulong)(bVar4 >> 1);
  lVar9 = lVar9 + 0x19;
  if ((bVar4 & 1) != 0) {
    uVar12 = *(ulong *)(lVar8 + 0x20);
    lVar9 = *(long *)(lVar8 + 0x28);
  }
  if ((*(byte *)puVar2 & 1) == 0) {
    uVar6 = 0x16;
    lVar8 = uVar12 - 0x16;
    if (0x15 < uVar12 && lVar8 != 0) {
code_r0x01ce6aac:
      if ((uVar11 & 1) == 0) {
        uVar11 = (ulong)(((uint)uVar11 & 0xfe) >> 1);
      }
      else {
        uVar11 = *(ulong *)(lVar7 + 0x160);
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar2,uVar6,lVar8,uVar11,0,uVar11,uVar12);
      goto code_r0x01ce6b0c;
    }
  }
  else {
    uVar11 = *puVar2;
    uVar6 = (uVar11 & 0xfffffffffffffffe) - 1;
    lVar8 = uVar12 - uVar6;
    if (uVar6 <= uVar12 && lVar8 != 0) goto code_r0x01ce6aac;
  }
  if ((uVar11 & 1) == 0) {
    lVar8 = lVar7 + 0x159;
  }
  else {
    lVar8 = *(long *)(lVar7 + 0x168);
  }
  if (uVar12 != 0) {
    memmove(lVar8,lVar9,uVar12);
  }
  *(undefined1 *)(lVar8 + uVar12) = 0;
  if ((*(byte *)puVar2 & 1) == 0) {
    *(byte *)puVar2 = (byte)(uVar12 << 1);
  }
  else {
    *(ulong *)(lVar7 + 0x160) = uVar12;
  }
code_r0x01ce6b0c:
  if (*(int *)(param_1 + 0x2f4) == 0xe) {
    *(undefined4 *)(lVar7 + 0x1a0) = 0;
    bVar4 = *(byte *)(lVar7 + 0x158);
    pbVar3 = (byte *)(lVar7 + 0x158);
    if ((bVar4 & 1) != 0) {
      bVar4 = *pbVar3;
    }
    if ((bVar4 & 1) == 0) {
      puVar10 = (undefined1 *)(lVar7 + 0x159);
    }
    else {
      puVar10 = *(undefined1 **)(lVar7 + 0x168);
    }
    *puVar10 = 0;
    if ((*pbVar3 & 1) == 0) {
      *pbVar3 = 0;
    }
    else {
      *(undefined8 *)(lVar7 + 0x160) = 0;
    }
    if (*(int *)(param_1 + 0x2f0) == 1) {
      *(undefined4 *)(lVar7 + 0x150) = 0;
    }
  }
  else if (*(int *)(param_1 + 0x2f4) == 0xd) {
    *(undefined8 *)(lVar7 + 0x150) = 0;
    *(undefined4 *)(lVar7 + 0x1a0) = 0;
    bVar4 = *(byte *)(lVar7 + 0x158);
    pbVar3 = (byte *)(lVar7 + 0x158);
    if ((bVar4 & 1) != 0) {
      bVar4 = *pbVar3;
    }
    if ((bVar4 & 1) == 0) {
      puVar10 = (undefined1 *)(lVar7 + 0x159);
    }
    else {
      puVar10 = *(undefined1 **)(lVar7 + 0x168);
    }
    *puVar10 = 0;
    if ((*pbVar3 & 1) == 0) {
      *pbVar3 = 0;
    }
    else {
      *(undefined8 *)(lVar7 + 0x160) = 0;
    }
  }
  if (-1 < *(int *)(param_1 + 0x77c)) {
    *(int *)(lVar7 + 0x1b0) = *(int *)(param_1 + 0x77c) + 1;
  }
  return;
}

// ==== undefined CMissionMenu::ToMultiUI(unsigned int,std::__ndk1::function<void ()> const &)
// _ZN12CMissionMenu9ToMultiUIEjRKNSt6__ndk18functionIFvvEEE @ 01ce6c1c

void _ZN12CMissionMenu9ToMultiUIEjRKNSt6__ndk18functionIFvvEEE
               (long param_1,undefined4 param_2,long *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  long *plVar4;
  long lVar5;
  undefined8 uVar6;
  long *plVar7;
  long lVar8;
  code *pcVar9;
  long lVar10;
  long alStack_160 [4];
  long *plStack_140;
  long lStack_130;
  long alStack_120 [4];
  long *plStack_100;
  undefined *puStack_f0;
  long lStack_e8;
  undefined **ppuStack_d0;
  long alStack_c0 [2];
  long alStack_b0 [2];
  long *plStack_a0;
  long *plStack_90;
  long alStack_80 [4];
  long *plStack_60;
  
  CMissionMenu::ToMultiUI_ParameterUISet()();
  plVar4 = (long *)param_3[4];
  lStack_130 = param_1;
  if (plVar4 == (long *)0x0) {
    plStack_100 = (long *)0x0;
  }
  else if (param_3 == plVar4) {
    plStack_100 = alStack_120;
    (**(code **)(*plVar4 + 0x18))();
  }
  else {
    plStack_100 = (long *)(**(code **)(*plVar4 + 0x10))();
  }
  puVar3 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  iVar1 = *(int *)(param_1 + 0x2e8);
  lVar10 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  if (lVar10 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar10 = *(long *)puVar3;
  }
  if (iVar1 != 0) {
    lVar5 = *(long *)(lVar10 + 0x38);
    uVar2 = *(undefined4 *)(param_1 + 0x2e8);
    if (lVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028998c6/*"C:\BAS_Submission\Client\Project\..\Source\Game\UI/Popup/../UIManager.h"*/,0x50,&UNK_027e6bb9/*"m_pSceneObjectContainer is null."*/);
      lVar5 = *(long *)(lVar10 + 0x38);
    }
    uVar6 = CSceneObjectContainer::pSearch(unsigned int)(lVar5,uVar2);
    lVar10 = lStack_130;
    if (plStack_100 == (long *)0x0) {
      plStack_140 = (long *)0x0;
    }
    else if (alStack_120 == plStack_100) {
      plStack_140 = alStack_160;
      (**(code **)(*plStack_100 + 0x18))();
    }
    else {
      plStack_140 = (long *)(**(code **)(*plStack_100 + 0x10))();
    }
    plVar4 = plStack_140;
    plStack_a0 = (long *)0x0;
    plVar7 = (long *)operator new(unsigned long)(0x50);
    *plVar7 = (long)&UNK_02b6e3d8;
    plVar7[2] = lVar10;
    if (plVar4 == (long *)0x0) {
      plVar7[8] = 0;
    }
    else if (alStack_160 == plVar4) {
      plVar7[8] = (long)(plVar7 + 4);
      (**(code **)(*plVar4 + 0x18))(plVar4);
    }
    else {
      lVar10 = (**(code **)(*plVar4 + 0x10))(plVar4);
      plVar7[8] = lVar10;
    }
    plStack_a0 = plVar7;
    CMultiPlay3::InitializeEx(CMultiPlay3::eMode, std::__ndk1::function<void (bool)> const&)(uVar6,param_2,alStack_c0);
    if (alStack_c0 == plStack_a0) {
      pcVar9 = *(code **)(*plStack_a0 + 0x20);
code_r0x01ce6e84:
      (*pcVar9)();
    }
    else if (plStack_a0 != (long *)0x0) {
      pcVar9 = *(code **)(*plStack_a0 + 0x28);
      goto code_r0x01ce6e84;
    }
    if (alStack_160 == plStack_140) {
      pcVar9 = *(code **)(*plStack_140 + 0x20);
    }
    else {
      if (plStack_140 == (long *)0x0) goto code_r0x01ce7048;
      pcVar9 = *(code **)(*plStack_140 + 0x28);
    }
    (*pcVar9)();
    goto code_r0x01ce7048;
  }
  if (*(long *)(lVar10 + 0x38) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028998c6/*"C:\BAS_Submission\Client\Project\..\Source\Game\UI/Popup/../UIManager.h"*/,0x41,&UNK_027e6bb9/*"m_pSceneObjectContainer is null."*/);
  }
  lVar5 = operator new(unsigned long, std::nothrow_t const&)(0xcbd0,PTR__ZSt7nothrow_02cb9a80);
  if (lVar5 != 0) {
    CMultiPlay3::CMultiPlay3()(lVar5);
  }
  lVar8 = lStack_130;
  alStack_c0[0] = lStack_130;
  if (plStack_100 == (long *)0x0) {
    plStack_90 = (long *)0x0;
  }
  else if (alStack_120 == plStack_100) {
    plStack_90 = alStack_b0;
    (**(code **)(*plStack_100 + 0x18))();
    lVar8 = alStack_c0[0];
  }
  else {
    plStack_90 = (long *)(**(code **)(*plStack_100 + 0x10))();
  }
  plVar4 = plStack_90;
  plStack_60 = (long *)0x0;
  plVar7 = (long *)operator new(unsigned long)(0x50);
  *plVar7 = (long)&UNK_02b6e3d8;
  plVar7[2] = lVar8;
  if (plVar4 == (long *)0x0) {
    plVar7[8] = 0;
  }
  else if (alStack_b0 == plVar4) {
    plVar7[8] = (long)(plVar7 + 4);
    (**(code **)(*plVar4 + 0x18))(plVar4);
  }
  else {
    lVar8 = (**(code **)(*plVar4 + 0x10))(plVar4);
    plVar7[8] = lVar8;
  }
  puStack_f0 = &UNK_02b6e358;
  lStack_e8 = param_1;
  ppuStack_d0 = &puStack_f0;
  plStack_60 = plVar7;
  CMultiPlay3::Initialize(CMultiPlay3::eMode, std::__ndk1::function<void (bool)> const&, CDialog*, std::__ndk1::function<void (bool, bool)> const&, long)(lVar5,param_2,alStack_80,param_1 + 0x1b0,&puStack_f0,
                  *(undefined8 *)(param_1 + 0x680));
  if (&puStack_f0 == ppuStack_d0) {
    pcVar9 = *(code **)(*ppuStack_d0 + 0x20);
code_r0x01ce6fb4:
    (*pcVar9)();
  }
  else if (ppuStack_d0 != (undefined **)0x0) {
    pcVar9 = *(code **)(*ppuStack_d0 + 0x28);
    goto code_r0x01ce6fb4;
  }
  if (alStack_80 == plStack_60) {
    pcVar9 = *(code **)(*plStack_60 + 0x20);
code_r0x01ce6fe0:
    (*pcVar9)();
  }
  else if (plStack_60 != (long *)0x0) {
    pcVar9 = *(code **)(*plStack_60 + 0x28);
    goto code_r0x01ce6fe0;
  }
  if (alStack_b0 == plStack_90) {
    pcVar9 = *(code **)(*plStack_90 + 0x20);
code_r0x01ce7010:
    (*pcVar9)();
  }
  else if (plStack_90 != (long *)0x0) {
    pcVar9 = *(code **)(*plStack_90 + 0x28);
    goto code_r0x01ce7010;
  }
  (**(code **)**(undefined8 **)(lVar10 + 0x38))(*(undefined8 **)(lVar10 + 0x38),lVar5,0);
  plVar4 = (long *)Framework::CTimeElementContainer::rElement_Game()();
  (**(code **)(*plVar4 + 0x10))(plVar4,lVar5);
  *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(lVar5 + 0xb8);
code_r0x01ce7048:
  CMissionMenu::ShowState(CMissionMenu::tUIMode)(param_1,0x13);
  if (alStack_120 == plStack_100) {
    pcVar9 = *(code **)(*plStack_100 + 0x20);
  }
  else {
    if (plStack_100 == (long *)0x0) {
      return;
    }
    pcVar9 = *(code **)(*plStack_100 + 0x28);
  }
  (*pcVar9)();
  return;
}

// ==== undefined CUIMatchingNotify::OnEnterLobbyResult(Aska::Status)
// _ZN17CUIMatchingNotify18OnEnterLobbyResultEN4Aska6StatusE @ 01eb2a20

void _ZN17CUIMatchingNotify18OnEnterLobbyResultEN4Aska6StatusE
               (undefined8 *param_1,long param_2,undefined8 *param_3)

{
  long *plVar1;
  undefined8 uStack_18;
  
  plVar1 = *(long **)(param_2 + 0x40);
  if (plVar1 != (long *)0x0) {
    uStack_18 = *param_3;
    (**(code **)(*plVar1 + 0x30))(plVar1,&uStack_18);
  }
  *param_1 = 0;
  return;
}

// ==== undefined CUIMatchingNotify::OnCreateRoomResult(Aska::Yayoi::MultiplayRPC::RoomInfo &)
// _ZN17CUIMatchingNotify18OnCreateRoomResultERN4Aska5Yayoi12MultiplayRPC8RoomInfoE @ 01eb2a5c

void _ZN17CUIMatchingNotify18OnCreateRoomResultERN4Aska5Yayoi12MultiplayRPC8RoomInfoE
               (undefined8 *param_1,long param_2)

{
  if (*(long **)(param_2 + 0x70) != (long *)0x0) {
    (**(code **)(**(long **)(param_2 + 0x70) + 0x30))();
  }
  *param_1 = 0;
  return;
}

// ==== undefined CUIMatchingNotify::OnCloseRoomResult(Aska::Status)
// _ZN17CUIMatchingNotify17OnCloseRoomResultEN4Aska6StatusE @ 01eb2a84

void _ZN17CUIMatchingNotify17OnCloseRoomResultEN4Aska6StatusE
               (undefined8 *param_1,long param_2,undefined8 *param_3)

{
  long *plVar1;
  undefined8 uStack_18;
  
  plVar1 = *(long **)(param_2 + 0x250);
  if (plVar1 != (long *)0x0) {
    uStack_18 = *param_3;
    (**(code **)(*plVar1 + 0x30))(plVar1,&uStack_18);
  }
  *param_1 = 0;
  return;
}

// ==== undefined CUIMatchingNotify::OnAutomatchResult(Aska::Yayoi::MultiplayRPC::RoomInfo &,int)
// _ZN17CUIMatchingNotify17OnAutomatchResultERN4Aska5Yayoi12MultiplayRPC8RoomInfoEi @ 01eb2ac0

void _ZN17CUIMatchingNotify17OnAutomatchResultERN4Aska5Yayoi12MultiplayRPC8RoomInfoEi
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined4 param_4)

{
  long *plVar1;
  undefined4 uStack_14;
  
  plVar1 = *(long **)(param_2 + 0x2b0);
  if (plVar1 != (long *)0x0) {
    uStack_14 = param_4;
    (**(code **)(*plVar1 + 0x30))(plVar1,param_3,&uStack_14);
  }
  *param_1 = 0;
  return;
}

// ==== undefined CUIMatchingNotify::OnUpdateRoomInfoResult(Aska::Yayoi::MultiplayRPC::RoomInfo &)
// _ZN17CUIMatchingNotify22OnUpdateRoomInfoResultERN4Aska5Yayoi12MultiplayRPC8RoomInfoE @ 01eb2af8

void _ZN17CUIMatchingNotify22OnUpdateRoomInfoResultERN4Aska5Yayoi12MultiplayRPC8RoomInfoE
               (undefined8 *param_1,long param_2)

{
  if (*(long **)(param_2 + 0x280) != (long *)0x0) {
    (**(code **)(**(long **)(param_2 + 0x280) + 0x30))();
  }
  *param_1 = 0;
  return;
}

// ==== undefined CUIMatchingNotify::OnGetRoomListResult(Aska::Yayoi::MultiplayRPC::RoomInfo *,unsigned int &,int,int)
// _ZN17CUIMatchingNotify19OnGetRoomListResultEPN4Aska5Yayoi12MultiplayRPC8RoomInfoERjii @ 01eb2b20

void _ZN17CUIMatchingNotify19OnGetRoomListResultEPN4Aska5Yayoi12MultiplayRPC8RoomInfoERjii
               (undefined8 *param_1,long param_2,undefined8 param_3)

{
  long *plVar1;
  undefined8 uStack_18;
  
  plVar1 = *(long **)(param_2 + 0xa0);
  if (plVar1 != (long *)0x0) {
    uStack_18 = param_3;
    (**(code **)(*plVar1 + 0x30))(plVar1,&uStack_18);
  }
  *param_1 = 0;
  return;
}

// ==== undefined CUIMatchingNotify::OnUpdateRoomListResult(Aska::Yayoi::MultiplayRPC::RoomInfo *,unsigned int &)
// _ZN17CUIMatchingNotify22OnUpdateRoomListResultEPN4Aska5Yayoi12MultiplayRPC8RoomInfoERj @ 01eb2b58

void _ZN17CUIMatchingNotify22OnUpdateRoomListResultEPN4Aska5Yayoi12MultiplayRPC8RoomInfoERj
               (undefined8 *param_1,long param_2,undefined8 param_3)

{
  long *plVar1;
  undefined8 uStack_18;
  
  plVar1 = *(long **)(param_2 + 0xd0);
  if (plVar1 != (long *)0x0) {
    uStack_18 = param_3;
    (**(code **)(*plVar1 + 0x30))(plVar1,&uStack_18);
  }
  *param_1 = 0xfffffffffffffc46;
  return;
}

// ==== undefined CUIMatchingNotify::OnEnterRoomResult(int,Aska::Status,Aska::Yayoi::MultiplayRPC::PlayerDetailInfo *,int)
// _ZN17CUIMatchingNotify17OnEnterRoomResultEiN4Aska6StatusEPNS0_5Yayoi12MultiplayRPC16PlayerDetailInfoEi @ 01eb2b94

void _ZN17CUIMatchingNotify17OnEnterRoomResultEiN4Aska6StatusEPNS0_5Yayoi12MultiplayRPC16PlayerDetailInfoEi
               (undefined8 *param_1,long param_2,undefined4 param_3,undefined8 param_4,
               undefined8 param_5,undefined2 param_6)

{
  long *plVar1;
  undefined2 auStack_24 [2];
  undefined8 uStack_20;
  undefined4 uStack_14;
  
  *(int *)(*(long *)PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908 +
          0x3d8) = (int)(char)param_3;
  plVar1 = *(long **)(param_2 + 0x100);
  if (plVar1 != (long *)0x0) {
    auStack_24[0] = param_6;
    uStack_20 = param_5;
    uStack_14 = param_3;
    (**(code **)(*plVar1 + 0x30))(plVar1,&uStack_14,&uStack_20,auStack_24);
  }
  *param_1 = 0;
  return;
}

// ==== undefined CUIMatchingNotify::OnExitRoomRes(Aska::Yayoi::MultiplayRPC::ExitType)
// _ZN17CUIMatchingNotify13OnExitRoomResEN4Aska5Yayoi12MultiplayRPC8ExitTypeE @ 01eb2c4c

void _ZN17CUIMatchingNotify13OnExitRoomResEN4Aska5Yayoi12MultiplayRPC8ExitTypeE
               (undefined8 *param_1,long param_2,undefined4 param_3)

{
  long *plVar1;
  undefined4 uStack_14;
  
  plVar1 = *(long **)(param_2 + 0x130);
  if (plVar1 != (long *)0x0) {
    uStack_14 = param_3;
    (**(code **)(*plVar1 + 0x30))(plVar1,&uStack_14);
  }
  *param_1 = 0;
  return;
}

// ==== undefined CUIMatchingNotify::OnExitRoomPush(Aska::Yayoi::MultiplayRPC::ExitType)
// _ZN17CUIMatchingNotify14OnExitRoomPushEN4Aska5Yayoi12MultiplayRPC8ExitTypeE @ 01eb2cbc

void _ZN17CUIMatchingNotify14OnExitRoomPushEN4Aska5Yayoi12MultiplayRPC8ExitTypeE
               (undefined8 *param_1,long param_2,undefined4 param_3)

{
  long *plVar1;
  undefined4 uStack_14;
  
  plVar1 = *(long **)(param_2 + 0x160);
  if (plVar1 != (long *)0x0) {
    uStack_14 = param_3;
    (**(code **)(*plVar1 + 0x30))(plVar1,&uStack_14);
  }
  *param_1 = 0;
  return;
}

// ==== undefined CUIMatchingNotify::OnChangePublicRoomRes(Aska::Status)
// _ZN17CUIMatchingNotify21OnChangePublicRoomResEN4Aska6StatusE @ 01eb2d2c

void _ZN17CUIMatchingNotify21OnChangePublicRoomResEN4Aska6StatusE
               (undefined8 *param_1,long param_2,undefined8 *param_3)

{
  long *plVar1;
  undefined8 uStack_18;
  
  plVar1 = *(long **)(param_2 + 0x1c0);
  if (plVar1 != (long *)0x0) {
    uStack_18 = *param_3;
    (**(code **)(*plVar1 + 0x30))(plVar1,&uStack_18);
  }
  *param_1 = 0;
  return;
}

// ==== undefined CUIMatchingNotify::OnRequestProxyResult(Aska::Status)
// _ZN17CUIMatchingNotify20OnRequestProxyResultEN4Aska6StatusE @ 01eb2da4

void _ZN17CUIMatchingNotify20OnRequestProxyResultEN4Aska6StatusE
               (undefined8 *param_1,long param_2,undefined8 *param_3)

{
  long *plVar1;
  undefined8 uStack_18;
  
  plVar1 = *(long **)(param_2 + 0x2e0);
  if (plVar1 != (long *)0x0) {
    uStack_18 = *param_3;
    (**(code **)(*plVar1 + 0x30))(plVar1,&uStack_18);
  }
  *param_1 = 0;
  return;
}

// ==== undefined CUIMatchingNotify::OnUpdatePlayerListResult(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo *,unsigned short,signed,unsigned long)
// _ZN17CUIMatchingNotify24OnUpdatePlayerListResultEPN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoEtam @ 01eb2e1c

void _ZN17CUIMatchingNotify24OnUpdatePlayerListResultEPN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoEtam
               (undefined8 *param_1,long param_2,undefined8 param_3,undefined2 param_4,
               undefined1 param_5,undefined8 param_6)

{
  long *plVar1;
  undefined8 uStack_28;
  undefined1 auStack_20 [4];
  undefined2 auStack_1c [2];
  undefined8 uStack_18;
  
  plVar1 = *(long **)(param_2 + 0x1f0);
  if (plVar1 != (long *)0x0) {
    uStack_28 = param_6;
    auStack_20[0] = param_5;
    auStack_1c[0] = param_4;
    uStack_18 = param_3;
    (**(code **)(*plVar1 + 0x30))(plVar1,&uStack_18,auStack_1c,auStack_20,&uStack_28);
  }
  *param_1 = 0;
  return;
}

// ==== undefined CUIMatchingNotify::OnUpdatePlayerStatusRes(Aska::Status)
// _ZN17CUIMatchingNotify23OnUpdatePlayerStatusResEN4Aska6StatusE @ 01eb2ebc

void _ZN17CUIMatchingNotify23OnUpdatePlayerStatusResEN4Aska6StatusE
               (undefined8 *param_1,long param_2,undefined8 *param_3)

{
  long *plVar1;
  undefined8 uStack_18;
  
  plVar1 = *(long **)(param_2 + 400);
  if (plVar1 != (long *)0x0) {
    uStack_18 = *param_3;
    (**(code **)(*plVar1 + 0x30))(plVar1,&uStack_18);
  }
  *param_1 = 0;
  return;
}

// ==== undefined CUIMatchingNotify::OnStartMultiplayRes(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo *,unsigned short)
// _ZN17CUIMatchingNotify19OnStartMultiplayResEPN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoEt @ 01eb2f34

void _ZN17CUIMatchingNotify19OnStartMultiplayResEPN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoEt
               (undefined8 *param_1,long param_2,long param_3,ushort param_4)

{
  uint uVar1;
  undefined *puVar2;
  long *plVar3;
  long lVar4;
  ulong uVar5;
  int *piVar6;
  ushort auStack_6c [2];
  long lStack_68;
  
  puVar2 = PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908;
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar2;
  }
  uVar5 = (ulong)(uint)param_4;
  *(undefined4 *)(lVar4 + 0x3dc) = 0;
  if (param_4 != 0) {
    piVar6 = (int *)(param_3 + 0x6c);
    do {
      if ((*piVar6 != 0) && (*(long *)(piVar6 + -0x1b) != 0)) {
        uVar1 = piVar6[-1];
        if (3 < uVar1) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_0295117d/*"C:\BAS_Submission\Client\Project\..\Source\Game\UI\UIMatchingNotify.cpp"*/,0x8c,&UNK_029d2011);
          lVar4 = *(long *)puVar2;
        }
        if (lVar4 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar4 = *(long *)puVar2;
        }
        *(undefined1 *)(lVar4 + (ulong)uVar1 + 0x3dc) = 1;
      }
      uVar5 = uVar5 - 1;
      piVar6 = piVar6 + 0x120;
    } while (uVar5 != 0);
  }
  plVar3 = *(long **)(param_2 + 0x220);
  if (plVar3 != (long *)0x0) {
    auStack_6c[0] = param_4;
    lStack_68 = param_3;
    (**(code **)(*plVar3 + 0x30))(plVar3,&lStack_68,auStack_6c);
  }
  *param_1 = 0;
  return;
}

// ==== undefined CUIMatchingNotify::OnProtocolError(Aska::Status)
// _ZN17CUIMatchingNotify15OnProtocolErrorEN4Aska6StatusE @ 01eb3074

void _ZN17CUIMatchingNotify15OnProtocolErrorEN4Aska6StatusE
               (undefined8 *param_1,long param_2,undefined8 *param_3)

{
  long *plVar1;
  undefined8 uStack_18;
  
  plVar1 = *(long **)(param_2 + 0x310);
  if (plVar1 != (long *)0x0) {
    uStack_18 = *param_3;
    (**(code **)(*plVar1 + 0x30))(plVar1,&uStack_18);
  }
  *param_1 = 0;
  return;
}

// ==== undefined CUIMatchingNotify::OnError(Aska::Status)
// _ZN17CUIMatchingNotify7OnErrorEN4Aska6StatusE @ 01eb30b0

void _ZN17CUIMatchingNotify7OnErrorEN4Aska6StatusE
               (undefined8 *param_1,long param_2,undefined8 *param_3)

{
  long *plVar1;
  undefined8 uStack_18;
  
  plVar1 = *(long **)(param_2 + 0x340);
  if (plVar1 != (long *)0x0) {
    uStack_18 = *param_3;
    (**(code **)(*plVar1 + 0x30))(plVar1,&uStack_18);
  }
  *param_1 = 0;
  return;
}

// ==== undefined CUIMatchingNotify::OnProtocolError(Aska::Yayoi::MO::BattleProtocol::FunctionID,Aska::Status)
// _ZN17CUIMatchingNotify15OnProtocolErrorEN4Aska5Yayoi2MO14BattleProtocol10FunctionIDENS0_6StatusE @ 01eb30ec

void _ZN17CUIMatchingNotify15OnProtocolErrorEN4Aska5Yayoi2MO14BattleProtocol10FunctionIDENS0_6StatusE
               (long param_1,undefined8 param_2,undefined8 *param_3)

{
  long *plVar1;
  undefined8 uStack_28;
  undefined8 uStack_18;
  
  uStack_18 = *param_3;
  IMultiplayNotify::OnProtocolError(Aska::Yayoi::MO::BattleProtocol::FunctionID, Aska::Status)(param_1 + 8,param_2,&uStack_18);
  if (*(char *)(param_1 + 0x13) == '\0') {
    plVar1 = *(long **)(param_1 + 0x310);
    if (plVar1 != (long *)0x0) {
      uStack_28 = *param_3;
      (**(code **)(*plVar1 + 0x30))(plVar1,&uStack_28);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x13) = 0;
  }
  return;
}

// ==== undefined CUIMatchingNotify::OnError(Aska::Status,char const *)
// _ZN17CUIMatchingNotify7OnErrorEN4Aska6StatusEPKc @ 01eb31b8

void _ZN17CUIMatchingNotify7OnErrorEN4Aska6StatusEPKc(long param_1,undefined8 *param_2)

{
  long *plVar1;
  undefined8 uStack_28;
  undefined8 uStack_18;
  
  uStack_18 = *param_2;
  IMultiplayNotify::OnError(Aska::Status, char const*)(param_1 + 8,&uStack_18);
  if (*(char *)(param_1 + 0x14) == '\0') {
    plVar1 = *(long **)(param_1 + 0x340);
    if (plVar1 != (long *)0x0) {
      uStack_28 = *param_2;
      (**(code **)(*plVar1 + 0x30))(plVar1,&uStack_28);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x14) = 0;
  }
  return;
}

// ==== undefined CUIMatchingNotify::OnDisconnect(void)
// _ZN17CUIMatchingNotify12OnDisconnectEv @ 01eb3284

void _ZN17CUIMatchingNotify12OnDisconnectEv(long param_1)

{
  IMultiplayNotify::OnDisconnect()(param_1 + 8);
  if (*(char *)(param_1 + 0x12) == '\0') {
    if (*(long **)(param_1 + 0x370) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x01eb32bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(**(long **)(param_1 + 0x370) + 0x30))();
      return;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x12) = 0;
  }
  return;
}

// ==== undefined CUIMatchingNotify::OnMatchingDisconnect(void)
// _ZN17CUIMatchingNotify20OnMatchingDisconnectEv @ 01eb32f8

void _ZN17CUIMatchingNotify20OnMatchingDisconnectEv(void)

{
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::MatchingClient(void)
// _ZN4Aska5Yayoi14MatchingClientC1Ev @ 022f5b00

void _ZN4Aska5Yayoi14MatchingClientC1Ev(long *param_1)

{
  undefined *puVar1;
  
  *(undefined4 *)(param_1 + 3) = 0;
  puVar1 = PTR__ZTVN4Aska5Yayoi9TARPCPeerINS0_12MultiplayRPC3Cli18LobbyProtocolProxyEEE_02cbfd60;
  param_1[2] = 0;
  param_1[1] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  Aska::Yayoi::TPeer<Aska::Yayoi::TCP, Aska::Yayoi::TProtocolSuite<Aska::Yayoi::MultiplayRPC::LobbyProtocol, Aska::Yayoi::NoProtocol<1>, Aska::Yayoi::NoProtocol<2> >, true>::TPeer()(param_1 + 4);
  param_1[0x7a] = 0;
  param_1[0x77] = 0;
  param_1[0x76] = 0;
  param_1[0x79] = 0;
  param_1[0x78] = 0;
  puVar1 = PTR__ZTVN4Aska5Yayoi14MatchingClient19LobbyProtocolNotifyE_02cba900;
  param_1[0x7d] = (long)param_1;
  param_1[0x7e] = 0;
  param_1[0x7c] = (long)(puVar1 + 0x10);
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::Term(void)
// _ZN4Aska5Yayoi14MatchingClient4TermEv @ 022f5cc0

void _ZN4Aska5Yayoi14MatchingClient4TermEv(long param_1)

{
  undefined1 auStack_28 [8];
  undefined1 auStack_18 [8];
  
  if (-1 < *(int *)(param_1 + 0x19c)) {
    Aska::Yayoi::MatchingClient::ResetPeer()(param_1);
    if (*(long *)(param_1 + 0x28) != 0) {
      Aska::Yayoi::NetworkEvent::DeregisterTransporter(Aska::Yayoi::NetworkBuffer::Type, Aska::Yayoi::TCP*)(auStack_18,*(long *)(param_1 + 0x28),0,param_1 + 400);
      Aska::Yayoi::NetworkEvent::DeregisterTransporter(Aska::Yayoi::NetworkBuffer::Type, Aska::Yayoi::TCP*)(auStack_28,*(undefined8 *)(param_1 + 0x28),1,param_1 + 400);
    }
    *(undefined1 *)(param_1 + 800) = 0;
    *(undefined8 *)(param_1 + 0x3f0) = 0;
  }
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::OnEnterLobbyResult(Aska::Status)
// _ZN4Aska5Yayoi14MatchingClient18OnEnterLobbyResultENS_6StatusE @ 022f627c

void _ZN4Aska5Yayoi14MatchingClient18OnEnterLobbyResultENS_6StatusE
               (long param_1,undefined8 *param_2)

{
  undefined8 uStack_18;
  
  uStack_18 = *param_2;
  (**(code **)**(undefined8 **)(param_1 + 0x3f0))(*(undefined8 **)(param_1 + 0x3f0),&uStack_18);
  Aska::Yayoi::MatchingClient::ResetPeer()(param_1);
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::OnCreateRoomResult(Aska::Yayoi::MultiplayRPC::RoomInfo &)
// _ZN4Aska5Yayoi14MatchingClient18OnCreateRoomResultERNS0_12MultiplayRPC8RoomInfoE @ 022f62b8

void _ZN4Aska5Yayoi14MatchingClient18OnCreateRoomResultERNS0_12MultiplayRPC8RoomInfoE(long param_1)

{
  (**(code **)(**(long **)(param_1 + 0x3f0) + 8))();
  (*(code *)PTR__ZN4Aska5Yayoi14MatchingClient9ResetPeerEv_02c9abb8)(param_1);
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::OnGetRoomListResult(Aska::Yayoi::MultiplayRPC::RoomInfo *,unsigned int &,int,int)
// _ZN4Aska5Yayoi14MatchingClient19OnGetRoomListResultEPNS0_12MultiplayRPC8RoomInfoERjii @ 022f62dc

void _ZN4Aska5Yayoi14MatchingClient19OnGetRoomListResultEPNS0_12MultiplayRPC8RoomInfoERjii
               (long param_1)

{
  (**(code **)(**(long **)(param_1 + 0x3f0) + 0x10))();
  (*(code *)PTR__ZN4Aska5Yayoi14MatchingClient9ResetPeerEv_02c9abb8)(param_1);
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::OnUpdateRoomListResult(Aska::Yayoi::MultiplayRPC::RoomInfo *,unsigned int &)
// _ZN4Aska5Yayoi14MatchingClient22OnUpdateRoomListResultEPNS0_12MultiplayRPC8RoomInfoERj @ 022f6300

void _ZN4Aska5Yayoi14MatchingClient22OnUpdateRoomListResultEPNS0_12MultiplayRPC8RoomInfoERj
               (long param_1)

{
  (**(code **)(**(long **)(param_1 + 0x3f0) + 0x18))();
  (*(code *)PTR__ZN4Aska5Yayoi14MatchingClient9ResetPeerEv_02c9abb8)(param_1);
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::OnCloseRoomResult(Aska::Status)
// _ZN4Aska5Yayoi14MatchingClient17OnCloseRoomResultENS_6StatusE @ 022f6324

void _ZN4Aska5Yayoi14MatchingClient17OnCloseRoomResultENS_6StatusE(long param_1,undefined8 *param_2)

{
  undefined8 uStack_8;
  
  uStack_8 = *param_2;
  (**(code **)(**(long **)(param_1 + 0x3f0) + 0x20))(*(long **)(param_1 + 0x3f0),&uStack_8);
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::OnUpdateRoomInfoResult(Aska::Yayoi::MultiplayRPC::RoomInfo &)
// _ZN4Aska5Yayoi14MatchingClient22OnUpdateRoomInfoResultERNS0_12MultiplayRPC8RoomInfoE @ 022f634c

void _ZN4Aska5Yayoi14MatchingClient22OnUpdateRoomInfoResultERNS0_12MultiplayRPC8RoomInfoE
               (long param_1)

{
  (**(code **)(**(long **)(param_1 + 0x3f0) + 0x28))();
  (*(code *)PTR__ZN4Aska5Yayoi14MatchingClient9ResetPeerEv_02c9abb8)(param_1);
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::OnMatchingDisconnect(void)
// _ZN4Aska5Yayoi14MatchingClient20OnMatchingDisconnectEv @ 022f6370

void _ZN4Aska5Yayoi14MatchingClient20OnMatchingDisconnectEv(long param_1)

{
  if (*(long **)(param_1 + 0x3f0) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x022f6380. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(param_1 + 0x3f0) + 0x38))();
    return;
  }
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::OnAutomatchResult(Aska::Status,Aska::Yayoi::MultiplayRPC::RoomInfo &,int)
// _ZN4Aska5Yayoi14MatchingClient17OnAutomatchResultENS_6StatusERNS0_12MultiplayRPC8RoomInfoEi @ 022f6388

void _ZN4Aska5Yayoi14MatchingClient17OnAutomatchResultENS_6StatusERNS0_12MultiplayRPC8RoomInfoEi
               (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  (**(code **)(**(long **)(param_1 + 0x3f0) + 0x30))(*(long **)(param_1 + 0x3f0),param_3,param_4);
  (*(code *)PTR__ZN4Aska5Yayoi14MatchingClient9ResetPeerEv_02c9abb8)(param_1);
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::LobbyProtocolNotify::OnProtocolError(Aska::Yayoi::MultiplayRPC::LobbyProtocol::FunctionID,Aska::Status)
// _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify15OnProtocolErrorENS0_12MultiplayRPC13LobbyProtocol10FunctionIDENS_6StatusE @ 022f63b4

void _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify15OnProtocolErrorENS0_12MultiplayRPC13LobbyProtocol10FunctionIDENS_6StatusE
               (long param_1,undefined8 param_2,undefined8 *param_3)

{
  long *plVar1;
  long lVar2;
  undefined8 uVar3;
  undefined1 auStack_28 [8];
  undefined8 uStack_18;
  
  lVar2 = *(long *)(param_1 + 8);
  uVar3 = *param_3;
  Aska::Yayoi::MatchingClient::ResetPeer()(lVar2);
  plVar1 = *(long **)(lVar2 + 0x3f0);
  uStack_18 = uVar3;
  (**(code **)(*plVar1 + 0x48))(auStack_28,plVar1,&uStack_18);
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::LobbyProtocolNotify::OnError(Aska::Status,char const *)
// _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify7OnErrorENS_6StatusEPKc @ 022f63fc

void _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify7OnErrorENS_6StatusEPKc
               (long param_1,undefined8 *param_2)

{
  long *plVar1;
  long lVar2;
  undefined8 uVar3;
  undefined1 auStack_28 [8];
  undefined8 uStack_18;
  
  lVar2 = *(long *)(param_1 + 8);
  uVar3 = *param_2;
  Aska::Yayoi::MatchingClient::ResetPeer()(lVar2);
  plVar1 = *(long **)(lVar2 + 0x3f0);
  if (plVar1 != (long *)0x0) {
    uStack_18 = uVar3;
    (**(code **)(*plVar1 + 0x50))(auStack_28,plVar1,&uStack_18);
  }
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::LobbyProtocolNotify::OnDisconnect(void)
// _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify12OnDisconnectEv @ 022f6460

void _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify12OnDisconnectEv(long param_1)

{
  long *plVar1;
  
  plVar1 = *(long **)(*(long *)(param_1 + 8) + 0x3f0);
  if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x022f6474. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x38))();
    return;
  }
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::LobbyProtocolNotify::OnEnterLobbyResult(Aska::Status)
// _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify18OnEnterLobbyResultENS_6StatusE @ 022f647c

void _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify18OnEnterLobbyResultENS_6StatusE
               (long param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  long lVar2;
  undefined8 uStack_18;
  
  lVar2 = *(long *)(param_1 + 8);
  uStack_18 = *param_2;
  puVar1 = *(undefined8 **)(lVar2 + 0x3f0);
  (**(code **)*puVar1)(puVar1,&uStack_18);
  Aska::Yayoi::MatchingClient::ResetPeer()(lVar2);
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::LobbyProtocolNotify::OnCreateRoomResult(Aska::Yayoi::MultiplayRPC::RoomInfo &)
// _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify18OnCreateRoomResultERNS0_12MultiplayRPC8RoomInfoE @ 022f64b8

void _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify18OnCreateRoomResultERNS0_12MultiplayRPC8RoomInfoE
               (long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  (**(code **)(**(long **)(lVar1 + 0x3f0) + 8))();
  (*(code *)PTR__ZN4Aska5Yayoi14MatchingClient9ResetPeerEv_02c9abb8)(lVar1);
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::LobbyProtocolNotify::OnCloseRoomResult(Aska::Status)
// _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify17OnCloseRoomResultENS_6StatusE @ 022f64dc

void _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify17OnCloseRoomResultENS_6StatusE
               (long param_1,undefined8 *param_2)

{
  long *plVar1;
  undefined8 uStack_8;
  
  uStack_8 = *param_2;
  plVar1 = *(long **)(*(long *)(param_1 + 8) + 0x3f0);
  (**(code **)(*plVar1 + 0x20))(plVar1,&uStack_8);
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::LobbyProtocolNotify::OnGetRoomListResult(Aska::Yayoi::MultiplayRPC::RoomInfo *,unsigned int &,int,int)
// _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify19OnGetRoomListResultEPNS0_12MultiplayRPC8RoomInfoERjii @ 022f6508

void _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify19OnGetRoomListResultEPNS0_12MultiplayRPC8RoomInfoERjii
               (long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  (**(code **)(**(long **)(lVar1 + 0x3f0) + 0x10))();
  (*(code *)PTR__ZN4Aska5Yayoi14MatchingClient9ResetPeerEv_02c9abb8)(lVar1);
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::LobbyProtocolNotify::OnUpdateRoomInfoResult(Aska::Yayoi::MultiplayRPC::RoomInfo &)
// _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify22OnUpdateRoomInfoResultERNS0_12MultiplayRPC8RoomInfoE @ 022f652c

void _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify22OnUpdateRoomInfoResultERNS0_12MultiplayRPC8RoomInfoE
               (long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  (**(code **)(**(long **)(lVar1 + 0x3f0) + 0x28))();
  (*(code *)PTR__ZN4Aska5Yayoi14MatchingClient9ResetPeerEv_02c9abb8)(lVar1);
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::LobbyProtocolNotify::OnAutomatchResult(Aska::Status,Aska::Yayoi::MultiplayRPC::RoomInfo &,int)
// _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify17OnAutomatchResultENS_6StatusERNS0_12MultiplayRPC8RoomInfoEi @ 022f6550

void _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify17OnAutomatchResultENS_6StatusERNS0_12MultiplayRPC8RoomInfoEi
               (long param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  long *plVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 8);
  plVar1 = *(long **)(lVar2 + 0x3f0);
  (**(code **)(*plVar1 + 0x30))(plVar1,param_3,param_4);
  (*(code *)PTR__ZN4Aska5Yayoi14MatchingClient9ResetPeerEv_02c9abb8)(lVar2);
  return;
}

// ==== undefined Aska::Yayoi::MatchingClient::LobbyProtocolNotify::OnUpdateRoomListResult(Aska::Yayoi::MultiplayRPC::RoomInfo *,unsigned int &)
// _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify22OnUpdateRoomListResultEPNS0_12MultiplayRPC8RoomInfoERj @ 022f657c

void _ZN4Aska5Yayoi14MatchingClient19LobbyProtocolNotify22OnUpdateRoomListResultEPNS0_12MultiplayRPC8RoomInfoERj
               (long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 8);
  (**(code **)(**(long **)(lVar1 + 0x3f0) + 0x18))();
  (*(code *)PTR__ZN4Aska5Yayoi14MatchingClient9ResetPeerEv_02c9abb8)(lVar1);
  return;
}


// FAILED to create function at 0281b8c0 typeinfo name for Aska::Yayoi::NetworkEvent::TDelayDeleter<Aska::Yayoi::MatchingClient>
// FAILED to create function at 029d36f0 typeinfo name for Aska::Yayoi::MatchingClient::LobbyProtocolNotify
// FAILED to create function at 02ac7608 Aska::Yayoi::NetworkEvent::TDelayDeleter<Aska::Yayoi::MatchingClient>::vtable
// FAILED to create function at 02ac7620 Aska::Yayoi::NetworkEvent::TDelayDeleter<Aska::Yayoi::MatchingClient>::typeinfo
// FAILED to create function at 02b9f588 CUIMatchingNotify::vtable
// FAILED to create function at 02b9f750 CUIMatchingNotify::typeinfo
// FAILED to create function at 02c56ea0 Aska::Yayoi::MatchingClient::LobbyProtocolNotify::vtable
// FAILED to create function at 02c56f30 Aska::Yayoi::MatchingClient::LobbyProtocolNotify::typeinfo

// ==== undefined CParameterPlayer::CopyForMultiplay(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo *)
// _ZN16CParameterPlayer16CopyForMultiplayEPN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoE @ 017f856c

void _ZN16CParameterPlayer16CopyForMultiplayEPN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoE
               (undefined8 *param_1,long param_2,long param_3)

{
  ulong uVar1;
  undefined8 uVar2;
  ulong auStack_38 [3];
  
  if (*(char *)(param_2 + 0x178) == '\0') {
    uVar2 = 0xfffffffffffffc5b;
  }
  else {
    *(undefined4 *)(param_3 + 0x6c) = *(undefined4 *)(param_2 + 0x40);
    *(short *)(param_3 + 0x2c) = (short)*(undefined4 *)(param_2 + 0xa0);
    *(undefined4 *)(param_3 + 0x14) = *(undefined4 *)(param_2 + 0xd0);
    auStack_38[1] = 0;
    auStack_38[2] = 0;
    auStack_38[0] = 0;
    void CParameterPropertyBase<42u>::CryptString<string >(string&, string const&)(auStack_38,param_2 + 0x160);
    uVar1 = (ulong)auStack_38 | 1;
    if ((auStack_38[0] & 1) != 0) {
      uVar1 = auStack_38[2];
    }
    snprintf(param_3 + 0x31,0x30,&UNK_027f6a37/*"%s"*/,uVar1);
    if ((auStack_38[0] & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(auStack_38[2]);
    }
    uVar2 = 0;
  }
  *param_1 = uVar2;
  return;
}

// ==== undefined CMultiPlay3::IsHost(void)
// _ZNK11CMultiPlay36IsHostEv @ 01cfd0e0

undefined1 _ZNK11CMultiPlay36IsHostEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0xb940);
}

// ==== undefined CMultiPlay3::IsEnableBattleStart(void)
// _ZNK11CMultiPlay319IsEnableBattleStartEv @ 01d055a4

undefined8 _ZNK11CMultiPlay319IsEnableBattleStartEv(long param_1)

{
  ulong uVar1;
  
  uVar1 = CParameterUtility::tCharaData::IsExist() const(param_1 + 0x2f60);
  if (((((uVar1 & 1) == 0) || (*(char *)(param_1 + 0xb6f1) == '\0')) &&
      ((uVar1 = CParameterUtility::tCharaData::IsExist() const(param_1 + 0x5c90), (uVar1 & 1) == 0 ||
       (*(char *)(param_1 + 0xb6f2) == '\0')))) &&
     ((uVar1 = CParameterUtility::tCharaData::IsExist() const(param_1 + 0x89c0), (uVar1 & 1) == 0 ||
      (*(char *)(param_1 + 0xb6f3) == '\0')))) {
    return 1;
  }
  return 0;
}

// ==== undefined CMultiPlay3::Server_UpdatePlayerStatus(unsigned int,bool,bool,std::__ndk1::function<void ()> const &)
// _ZN11CMultiPlay325Server_UpdatePlayerStatusEjbbRKNSt6__ndk18functionIFvvEEE @ 01d05618

void _ZN11CMultiPlay325Server_UpdatePlayerStatusEjbbRKNSt6__ndk18functionIFvvEEE
               (long param_1,undefined4 param_2,byte param_3,byte param_4,long *param_5)

{
  byte bVar1;
  undefined6 uVar2;
  undefined2 uVar3;
  long *plVar4;
  long *plVar5;
  long lVar6;
  undefined8 uVar7;
  code *pcVar8;
  long lVar9;
  undefined1 auStack_598 [8];
  undefined8 uStack_590;
  undefined4 uStack_588;
  byte bStack_584;
  byte bStack_583;
  long alStack_580 [2];
  long *plStack_570;
  long *plStack_560;
  undefined8 uStack_550;
  undefined6 uStack_548;
  long alStack_540 [2];
  long *plStack_530;
  byte bStack_521;
  long *plStack_520;
  undefined4 uStack_4e8;
  undefined6 uStack_d0;
  undefined2 uStack_ca;
  undefined4 uStack_c8;
  byte bStack_c4;
  byte bStack_c3;
  long alStack_c0 [4];
  long *plStack_a0;
  long alStack_90 [4];
  long *plStack_70;
  
  param_3 = param_3 & 1;
  bVar1 = param_4 & 1;
  uStack_ca = (undefined2)((ulong)param_1 >> 0x30);
  uVar3 = uStack_ca;
  uStack_d0 = (undefined6)param_1;
  uVar2 = uStack_d0;
  if (*(long *)(param_1 + 0xb750) == 0) {
    plVar4 = (long *)param_5[4];
    lVar6 = param_1;
    if (plVar4 == (long *)0x0) {
      plStack_a0 = (long *)0x0;
    }
    else if (param_5 == plVar4) {
      plStack_a0 = alStack_c0;
      (**(code **)(*plVar4 + 0x18))();
      lVar6 = CONCAT26(uStack_ca,uStack_d0);
    }
    else {
      plStack_a0 = (long *)(**(code **)(*plVar4 + 0x10))();
    }
    lVar9 = *(long *)(param_1 + 0x1b8);
    uStack_550._0_6_ = (undefined6)lVar6;
    uStack_550._6_2_ = (undefined2)((ulong)lVar6 >> 0x30);
    if (plStack_a0 == (long *)0x0) {
      plStack_520 = (long *)0x0;
    }
    else if (alStack_c0 == plStack_a0) {
      plStack_520 = alStack_540;
      (**(code **)(*plStack_a0 + 0x18))();
      lVar6 = CONCAT26(uStack_550._6_2_,(undefined6)uStack_550);
    }
    else {
      plStack_520 = (long *)(**(code **)(*plStack_a0 + 0x10))();
    }
    plVar4 = plStack_520;
    plStack_570 = (long *)0x0;
    plVar5 = (long *)operator new(unsigned long)(0x50);
    *plVar5 = (long)&UNK_02b73768;
    plVar5[2] = lVar6;
    if (plVar4 == (long *)0x0) {
      plVar5[8] = 0;
    }
    else if (alStack_540 == plVar4) {
      plVar5[8] = (long)(plVar5 + 4);
      (**(code **)(*plVar4 + 0x18))(plVar4);
    }
    else {
      lVar6 = (**(code **)(*plVar4 + 0x10))(plVar4);
      plVar5[8] = lVar6;
    }
    plStack_570 = plVar5;
    std::__ndk1::function<void (Aska::Status)>::swap(std::__ndk1::function<void (Aska::Status)>&)(&uStack_590,lVar9 + 0x170);
    if (&uStack_590 == plStack_570) {
      pcVar8 = *(code **)(*plStack_570 + 0x20);
code_r0x01d05998:
      (*pcVar8)();
    }
    else if (plStack_570 != (long *)0x0) {
      pcVar8 = *(code **)(*plStack_570 + 0x28);
      goto code_r0x01d05998;
    }
    if (alStack_540 == plStack_520) {
      pcVar8 = *(code **)(*plStack_520 + 0x20);
code_r0x01d059c8:
      (*pcVar8)();
    }
    else if (plStack_520 != (long *)0x0) {
      pcVar8 = *(code **)(*plStack_520 + 0x28);
      goto code_r0x01d059c8;
    }
    if (alStack_c0 == plStack_a0) {
      pcVar8 = *(code **)(*plStack_a0 + 0x20);
code_r0x01d059f8:
      (*pcVar8)();
    }
    else if (plStack_a0 != (long *)0x0) {
      pcVar8 = *(code **)(*plStack_a0 + 0x28);
      goto code_r0x01d059f8;
    }
    plVar4 = *(long **)(param_1 + 0xb7e0);
    if ((long *)(param_1 + 0xb7c0) == plVar4) {
      pcVar8 = *(code **)(*plVar4 + 0x20);
code_r0x01d05a30:
      (*pcVar8)();
    }
    else if (plVar4 != (long *)0x0) {
      pcVar8 = *(code **)(*plVar4 + 0x28);
      goto code_r0x01d05a30;
    }
    *(long *)(param_1 + 0xb7e0) = 0;
    plStack_530 = (long *)0x0;
    std::__ndk1::function<bool (Aska::Status)>::swap(std::__ndk1::function<bool (Aska::Status)>&)(&uStack_550,param_1 + 0xb7f0);
    if (&uStack_550 == plStack_530) {
      pcVar8 = *(code **)(*plStack_530 + 0x20);
code_r0x01d05a74:
      (*pcVar8)();
    }
    else if (plStack_530 != (long *)0x0) {
      pcVar8 = *(code **)(*plStack_530 + 0x28);
      goto code_r0x01d05a74;
    }
    plVar4 = *(long **)(param_1 + 0xb840);
    if ((long *)(param_1 + 0xb820) == plVar4) {
      pcVar8 = *(code **)(*plVar4 + 0x20);
code_r0x01d05aac:
      uVar7 = (*pcVar8)();
    }
    else {
      uVar7 = 0;
      if (plVar4 != (long *)0x0) {
        pcVar8 = *(code **)(*plVar4 + 0x28);
        goto code_r0x01d05aac;
      }
    }
    *(long *)(param_1 + 0xb840) = 0;
    CMultiPlay3::Server_CreatePlayerInfo(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo&, int)(uVar7,&uStack_550,param_2);
    uStack_4e8 = *(undefined4 *)(param_1 + 0xb950);
    plVar4 = (long *)param_5[4];
    uStack_590._0_6_ = uVar2;
    uStack_590._6_2_ = uVar3;
    uStack_588 = param_2;
    bStack_584 = param_3;
    bStack_583 = bVar1;
    bStack_521 = param_3;
    if (plVar4 == (long *)0x0) {
      plStack_560 = (long *)0x0;
    }
    else if (param_5 == plVar4) {
      plStack_560 = alStack_580;
      (**(code **)(*plVar4 + 0x18))();
    }
    else {
      plStack_560 = (long *)(**(code **)(*plVar4 + 0x10))();
    }
    uStack_c8 = uStack_588;
    bStack_c4 = bStack_584;
    bStack_c3 = bStack_583;
    uStack_d0 = (undefined6)uStack_590;
    uStack_ca = uStack_590._6_2_;
    if (plStack_560 == (long *)0x0) {
      plStack_a0 = (long *)0x0;
    }
    else if (alStack_580 == plStack_560) {
      plStack_a0 = alStack_c0;
      (**(code **)(*plStack_560 + 0x18))();
    }
    else {
      plStack_a0 = (long *)(**(code **)(*plStack_560 + 0x10))();
    }
    plVar4 = plStack_a0;
    plStack_70 = (long *)0x0;
    plVar5 = (long *)operator new(unsigned long)(0x50);
    *plVar5 = (long)&UNK_02b737e8;
    *(ulong *)((long)plVar5 + 0x16) =
         CONCAT17(bStack_c3,CONCAT16(bStack_c4,CONCAT42(uStack_c8,uStack_ca)));
    plVar5[2] = CONCAT26(uStack_ca,uStack_d0);
    if (plVar4 == (long *)0x0) {
      plVar5[8] = 0;
    }
    else if (alStack_c0 == plVar4) {
      plVar5[8] = (long)(plVar5 + 4);
      (**(code **)(*plVar4 + 0x18))(plVar4);
    }
    else {
      lVar6 = (**(code **)(*plVar4 + 0x10))(plVar4);
      plVar5[8] = lVar6;
    }
    plStack_70 = plVar5;
    std::__ndk1::function<bool ()>::swap(std::__ndk1::function<bool ()>&)(alStack_90,param_1 + 0xb730);
    if (alStack_90 == plStack_70) {
      pcVar8 = *(code **)(*plStack_70 + 0x20);
code_r0x01d05c48:
      (*pcVar8)();
    }
    else if (plStack_70 != (long *)0x0) {
      pcVar8 = *(code **)(*plStack_70 + 0x28);
      goto code_r0x01d05c48;
    }
    if (alStack_c0 == plStack_a0) {
      pcVar8 = *(code **)(*plStack_a0 + 0x20);
code_r0x01d05c78:
      (*pcVar8)();
    }
    else if (plStack_a0 != (long *)0x0) {
      pcVar8 = *(code **)(*plStack_a0 + 0x28);
      goto code_r0x01d05c78;
    }
    if (alStack_580 == plStack_560) {
      pcVar8 = *(code **)(*plStack_560 + 0x20);
    }
    else {
      if (plStack_560 == (long *)0x0) goto code_r0x01d05cac;
      pcVar8 = *(code **)(*plStack_560 + 0x28);
    }
    (*pcVar8)();
code_r0x01d05cac:
    Aska::Yayoi::MO::Cli::BattleProtocolProxy::SendUpdatePlayerStatus(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo const&, signed char)(auStack_598,
                    *(long *)(*(long *)
                               PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908
                             + 0x48) + 8,&uStack_550,*(char *)(param_1 + 0xb940) != '\0' & param_4);
    return;
  }
  plVar4 = (long *)param_5[4];
  uStack_c8 = param_2;
  bStack_c4 = param_3;
  bStack_c3 = bVar1;
  if (plVar4 == (long *)0x0) {
    plStack_a0 = (long *)0x0;
  }
  else if (param_5 == plVar4) {
    plStack_a0 = alStack_c0;
    (**(code **)(*plVar4 + 0x18))();
  }
  else {
    plStack_a0 = (long *)(**(code **)(*plVar4 + 0x10))();
  }
  uStack_548 = (undefined6)
               (CONCAT17(bStack_c3,CONCAT16(bStack_c4,CONCAT42(uStack_c8,uStack_ca))) >> 0x10);
  uStack_550._0_6_ = uStack_d0;
  uStack_550._6_2_ = uStack_ca;
  if (plStack_a0 == (long *)0x0) {
    plStack_520 = (long *)0x0;
  }
  else if (alStack_c0 == plStack_a0) {
    plStack_520 = alStack_540;
    (**(code **)(*plStack_a0 + 0x18))();
  }
  else {
    plStack_520 = (long *)(**(code **)(*plStack_a0 + 0x10))();
  }
  plVar4 = plStack_520;
  plStack_570 = (long *)0x0;
  plVar5 = (long *)operator new(unsigned long)(0x50);
  *plVar5 = (long)&UNK_02b736e8;
  *(ulong *)((long)plVar5 + 0x16) = CONCAT62(uStack_548,uStack_550._6_2_);
  plVar5[2] = CONCAT26(uStack_550._6_2_,(undefined6)uStack_550);
  if (plVar4 == (long *)0x0) {
    plVar5[8] = 0;
  }
  else if (alStack_540 == plVar4) {
    plVar5[8] = (long)(plVar5 + 4);
    (**(code **)(*plVar4 + 0x18))(plVar4);
  }
  else {
    lVar6 = (**(code **)(*plVar4 + 0x10))(plVar4);
    plVar5[8] = lVar6;
  }
  plStack_570 = plVar5;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&uStack_590,param_1 + 0xb790);
  if (&uStack_590 == plStack_570) {
    pcVar8 = *(code **)(*plStack_570 + 0x20);
code_r0x01d057f8:
    (*pcVar8)();
  }
  else if (plStack_570 != (long *)0x0) {
    pcVar8 = *(code **)(*plStack_570 + 0x28);
    goto code_r0x01d057f8;
  }
  if (alStack_540 == plStack_520) {
    pcVar8 = *(code **)(*plStack_520 + 0x20);
  }
  else {
    if (plStack_520 == (long *)0x0) goto code_r0x01d0582c;
    pcVar8 = *(code **)(*plStack_520 + 0x28);
  }
  (*pcVar8)();
code_r0x01d0582c:
  if (alStack_c0 == plStack_a0) {
    (**(code **)(*plStack_a0 + 0x20))();
  }
  else if (plStack_a0 != (long *)0x0) {
    (**(code **)(*plStack_a0 + 0x28))();
  }
  return;
}

// ==== undefined CMultiPlay3::Server_BattleStart(std::__ndk1::function<void ()>)
// _ZN11CMultiPlay318Server_BattleStartENSt6__ndk18functionIFvvEEE @ 01d05d00

void _ZN11CMultiPlay318Server_BattleStartENSt6__ndk18functionIFvvEEE(long param_1,long *param_2)

{
  long *plVar1;
  code *pcVar2;
  undefined *puStack_50;
  long lStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  plVar1 = (long *)param_2[4];
  if (plVar1 == (long *)0x0) {
    plStack_30 = (long *)0x0;
  }
  else if (param_2 == plVar1) {
    (**(code **)(*plVar1 + 0x18))(plVar1,&puStack_50);
  }
  else {
    plStack_30 = (long *)(**(code **)(*plVar1 + 0x10))();
  }
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_50,param_1 + 0xb760);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar2 = *(code **)(*plStack_30 + 0x20);
code_r0x01d05d90:
    (*pcVar2)();
  }
  else if (plStack_30 != (long *)0x0) {
    pcVar2 = *(code **)(*plStack_30 + 0x28);
    goto code_r0x01d05d90;
  }
  puStack_50 = &UNK_02b730a8;
  lStack_48 = param_1;
  plStack_30 = (long *)&puStack_50;
  std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short)>::swap(std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short)>&)(&puStack_50,*(long *)(param_1 + 0x1b8) + 0x200);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar2 = *(code **)(*plStack_30 + 0x20);
code_r0x01d05de0:
    (*pcVar2)();
  }
  else if (plStack_30 != (long *)0x0) {
    pcVar2 = *(code **)(*plStack_30 + 0x28);
    goto code_r0x01d05de0;
  }
  plVar1 = *(long **)(param_1 + 0xb7e0);
  if ((long *)(param_1 + 0xb7c0) == plVar1) {
    pcVar2 = *(code **)(*plVar1 + 0x20);
code_r0x01d05e18:
    (*pcVar2)();
  }
  else if (plVar1 != (long *)0x0) {
    pcVar2 = *(code **)(*plVar1 + 0x28);
    goto code_r0x01d05e18;
  }
  *(long *)(param_1 + 0xb7e0) = 0;
  plStack_30 = (long *)0x0;
  std::__ndk1::function<bool (Aska::Status)>::swap(std::__ndk1::function<bool (Aska::Status)>&)(&puStack_50,param_1 + 0xb7f0);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar2 = *(code **)(*plStack_30 + 0x20);
code_r0x01d05e5c:
    (*pcVar2)();
  }
  else if (plStack_30 != (long *)0x0) {
    pcVar2 = *(code **)(*plStack_30 + 0x28);
    goto code_r0x01d05e5c;
  }
  plVar1 = *(long **)(param_1 + 0xb840);
  if ((long *)(param_1 + 0xb820) == plVar1) {
    pcVar2 = *(code **)(*plVar1 + 0x20);
  }
  else {
    if (plVar1 == (long *)0x0) goto code_r0x01d05e98;
    pcVar2 = *(code **)(*plVar1 + 0x28);
  }
  (*pcVar2)();
code_r0x01d05e98:
  *(long *)(param_1 + 0xb840) = 0;
  puStack_50 = &UNK_02b731b8;
  lStack_48 = param_1;
  plStack_30 = (long *)&puStack_50;
  CMultiPlay3::RegistCall(std::__ndk1::function<bool ()> const&, bool, unsigned int)(param_1,&puStack_50,1);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar2 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) {
      return;
    }
    pcVar2 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar2)();
  return;
}

// ==== undefined CMultiPlay3::Server_CreateRoomContdition(Aska::Yayoi::MultiplayRPC::RoomCondition *,bool)
// _ZN11CMultiPlay327Server_CreateRoomContditionEPN4Aska5Yayoi12MultiplayRPC13RoomConditionEb @ 01d06150

undefined8
_ZN11CMultiPlay327Server_CreateRoomContditionEPN4Aska5Yayoi12MultiplayRPC13RoomConditionEb
          (long param_1,long param_2,ulong param_3)

{
  int iVar1;
  short sVar2;
  undefined *puVar3;
  long lVar4;
  long lStack_40;
  long lStack_38;
  
  memset(param_2,0,0x1e8);
  *(undefined1 *)(param_2 + 0x12e) = 0;
  *(undefined1 *)(param_2 + 0x14e) = 0;
  *(undefined1 *)(param_2 + 0x16f) = 0;
  *(undefined8 *)(param_2 + 8) = 0xffffffffffffffff;
  *(undefined8 *)(param_2 + 0x10) = 0xffffffffffffffff;
  puVar3 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar4 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar4 = *(long *)puVar3;
  }
  CParameterManager::pParameterPlayer() const(lVar4);
  lVar4 = CParameterPlayer::pParameter() const();
  sVar2 = *(short *)(lVar4 + 0x98);
  *(short *)(param_2 + 300) = sVar2;
  *(byte *)(param_2 + 0x16e) = *(byte *)(param_1 + 0xb9c0) ^ 1;
  *(uint *)(param_2 + 0x18) = (uint)*(byte *)(param_1 + 0xb9c1);
  if (sVar2 == 0) {
    *(undefined2 *)(param_2 + 300) = 1;
  }
  *(undefined4 *)(param_2 + 0x20) = *(undefined4 *)(param_1 + 0xb98c);
  *(undefined4 *)(param_2 + 0x24) = *(undefined4 *)(param_1 + 0xb990);
  *(undefined4 *)(param_2 + 0x28) = *(undefined4 *)(param_1 + 0xb994);
  if ((param_3 & 1) == 0) {
    if (*(int *)(param_1 + 0xb9a0) != 0) {
      *(int *)(param_2 + 0x14) = *(int *)(param_1 + 0xb9a0);
      CParameterUtility::FindAreaWithMissionId(unsigned int)(&lStack_40);
      if (lStack_40 != 0) {
        *(undefined4 *)(param_2 + 0x10) = *(undefined4 *)(lStack_40 + 0x38);
        *(undefined4 *)(param_2 + 0xc) = *(undefined4 *)(lStack_40 + 0xa8);
      }
      if (lStack_38 != 0) {
        std::__ndk1::__shared_weak_count::__release_shared()();
      }
    }
  }
  else {
    if (*(int *)(param_1 + 0xb9a4) != 0) {
      *(int *)(param_2 + 0x10) = *(int *)(param_1 + 0xb9a4);
    }
    if (*(int *)(param_1 + 0xb9a8) != 0) {
      *(int *)(param_2 + 0xc) = *(int *)(param_1 + 0xb9a8);
      *(undefined4 *)(param_2 + 8) = *(undefined4 *)(param_1 + 0xb998);
      iVar1 = *(int *)(param_2 + 0x10);
      goto joined_r0x01d062a8;
    }
  }
  *(undefined4 *)(param_2 + 8) = *(undefined4 *)(param_1 + 0xb998);
  if (*(int *)(param_2 + 0xc) == 0) {
    *(undefined4 *)(param_2 + 0xc) = 0xffffffff;
    iVar1 = *(int *)(param_2 + 0x10);
  }
  else {
    iVar1 = *(int *)(param_2 + 0x10);
  }
joined_r0x01d062a8:
  if (iVar1 == 0) {
    *(undefined4 *)(param_2 + 0x10) = 0xffffffff;
    iVar1 = *(int *)(param_2 + 0x14);
  }
  else {
    iVar1 = *(int *)(param_2 + 0x14);
  }
  if (iVar1 == 0) {
    *(undefined4 *)(param_2 + 0x14) = 0xffffffff;
  }
  return 1;
}

// ==== undefined CMultiPlay3::Server_CreatePlayerInfo(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo &)
// _ZN11CMultiPlay323Server_CreatePlayerInfoERN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoE @ 01d062f8

void _ZN11CMultiPlay323Server_CreatePlayerInfoERN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoE
               (undefined8 param_1,undefined8 param_2)

{
  undefined *puVar1;
  long lVar2;
  
  puVar1 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar2 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)puVar1;
  }
  lVar2 = CParameterManager::pParameterUI() const(lVar2);
  (*(code *)
    PTR__ZN11CMultiPlay323Server_CreatePlayerInfoERN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoEi_02cad058
  )(lVar2,param_2,*(undefined4 *)(lVar2 + 0x1b0));
  return;
}

// ==== undefined CMultiPlay3::Server_CreatePlayerInfo(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo &,int)
// _ZN11CMultiPlay323Server_CreatePlayerInfoERN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoEi @ 01d06348

void _ZN11CMultiPlay323Server_CreatePlayerInfoERN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoEi
               (undefined8 param_1,long *param_2,int param_3)

{
  undefined *puVar1;
  int *piVar2;
  undefined8 *puVar3;
  bool bVar4;
  undefined4 *puVar5;
  byte bVar6;
  undefined1 uVar7;
  undefined4 uVar8;
  uint uVar9;
  long lVar10;
  ulong uVar11;
  undefined8 uVar12;
  ulong uVar13;
  ulong uVar14;
  long *plVar15;
  long lVar16;
  code *pcVar17;
  long lVar18;
  undefined8 *puVar19;
  undefined4 *puVar20;
  long *plVar21;
  undefined4 *puVar22;
  undefined *puVar23;
  long lVar24;
  long lVar25;
  long lVar26;
  float fVar27;
  undefined4 uVar28;
  undefined4 uVar29;
  undefined4 uVar30;
  undefined4 uVar31;
  undefined4 uVar32;
  undefined4 uVar33;
  undefined4 uVar34;
  undefined4 uVar35;
  undefined4 uVar36;
  undefined4 uVar37;
  undefined4 uVar38;
  undefined4 uVar39;
  undefined4 uVar40;
  undefined *puStack_3510;
  ulong uStack_3508;
  int *piStack_3500;
  undefined **ppuStack_34f0;
  int iStack_3360;
  undefined4 auStack_3354 [7];
  undefined4 auStack_3338 [5];
  undefined4 uStack_3324;
  undefined4 uStack_3320;
  undefined4 uStack_3028;
  undefined4 uStack_2ff8;
  long lStack_2f98;
  undefined1 uStack_2f90;
  undefined4 uStack_2f8c;
  undefined4 uStack_2f88;
  undefined4 uStack_2f84;
  long lStack_2f80;
  long lStack_2f70;
  undefined1 auStack_2f68 [32];
  long lStack_2f48;
  long lStack_2f40;
  undefined1 auStack_2f38 [32];
  long lStack_2f18;
  long lStack_2f10;
  long lStack_2f08;
  long lStack_2f00;
  ulong uStack_2ef8;
  undefined8 uStack_2ef0;
  ulong uStack_2ee8;
  undefined *puStack_1c8;
  undefined8 *puStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 *puStack_1a8;
  undefined8 uStack_1a0;
  undefined8 uStack_198;
  undefined *puStack_190;
  undefined8 uStack_188;
  undefined1 uStack_180;
  undefined1 auStack_178 [16];
  undefined4 uStack_168;
  undefined *puStack_160;
  undefined8 uStack_158;
  undefined1 uStack_150;
  undefined1 auStack_148 [24];
  undefined *puStack_130;
  undefined8 uStack_128;
  undefined1 uStack_120;
  undefined1 auStack_118 [16];
  char cStack_108;
  undefined *puStack_100;
  undefined8 *puStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 *puStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  long lStack_c8;
  long lStack_c0;
  undefined8 uStack_b8;
  undefined *puStack_b0;
  undefined1 auStack_a8 [8];
  undefined8 uStack_a0;
  undefined1 auStack_90 [8];
  undefined8 uStack_88;
  undefined8 *puStack_78;
  undefined8 auStack_70 [2];
  
  memset(param_2,0,0x480);
  puVar23 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  CParameterManager::pParameterPlayer() const(*(undefined8 *)
                   PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0);
  lVar10 = CParameterPlayer::pParameter() const();
  uVar8 = *(undefined4 *)(lVar10 + 0x38);
  *(undefined4 *)(param_2 + 0xd) = 0;
  *(undefined4 *)((long)param_2 + 0x6c) = uVar8;
  CParameterManager::pParameterPlayer() const(*(undefined8 *)puVar23);
  lVar10 = CParameterPlayer::pParameter() const();
  uStack_2ef8 = 0;
  uStack_2ee8 = 0;
  uStack_2ef0 = 0;
  void CParameterPropertyBase<42u>::CryptString<string >(string&, string const&)(&uStack_2ef8,lVar10 + 0x158);
  uVar13 = (ulong)&uStack_2ef8 | 1;
  if ((uStack_2ef8 & 1) != 0) {
    uVar13 = uStack_2ee8;
  }
  uVar11 = strlen(uVar13);
  if (uVar11 < 0x30) {
    strcpy((long)param_2 + 0x31,uVar13);
  }
  else {
    raise(5);
  }
  if ((uStack_2ef8 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_2ee8);
  }
  lVar10 = *(long *)puVar23;
  if (lVar10 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar10 = *(long *)puVar23;
  }
  puVar1 = PTR__ZTV8InfoBase_02cc49c8;
  puStack_b0 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
  Framework::CSTLMap<unsigned int, IParameterProperty*>::CSTLMap(Framework::CSTLMap<unsigned int, IParameterProperty*> const&)(auStack_a8,lVar10 + 0x1848);
  Framework::CSTLMap<unsigned int, InfoBase*>::CSTLMap(Framework::CSTLMap<unsigned int, InfoBase*> const&)(auStack_90,lVar10 + 0x1860);
  Framework::CSTLMap<unsigned long, PartySetInfo>::CSTLMap(Framework::CSTLMap<unsigned long, PartySetInfo> const&)(&puStack_78,lVar10 + 0x1878);
  uStack_1b0 = 0;
  uStack_1b8 = 0;
  puStack_b0 = PTR__ZTV15PartySetInfoMap_02cb7190 + 0x10;
  puStack_1c0 = &uStack_1b8;
  puStack_1a8 = &uStack_1a0;
  puStack_1c8 = PTR__ZTV12PartySetInfo_02cb7940 + 0x10;
  puStack_190 = PTR__ZTV22CParameterPropertyBaseILj64EE_02cbbba0 + 0x10;
  uStack_198 = 0;
  uStack_1a0 = 0;
  uStack_188 = 0;
  uStack_180 = 0;
  Framework::CHash32::CHash32()(auStack_178);
  puStack_190 = PTR__ZTV23CParameterPropertyValueIjLj64E18CPropertyConverterE_02cb96a8 + 0x10;
  puStack_160 = PTR__ZTV22CParameterPropertyBaseILj65EE_02cb79a0 + 0x10;
  uStack_158 = 0;
  uStack_150 = 0;
  Framework::CHash32::CHash32()(auStack_148);
  puStack_160 = PTR__ZTV23CParameterPropertyValueIjLj65E18CPropertyConverterE_02cbf1c8 + 0x10;
  puStack_130 = PTR__ZTV22CParameterPropertyBaseILj66EE_02cc1e50 + 0x10;
  uStack_128 = 0;
  uStack_120 = 0;
  Framework::CHash32::CHash32()(auStack_118);
  uStack_e8 = 0;
  uStack_f0 = 0;
  puStack_e0 = &uStack_d8;
  puStack_130 = PTR__ZTV23CParameterPropertyValueIbLj66E18CPropertyConverterE_02cbc8d8 + 0x10;
  puStack_f8 = &uStack_f0;
  uStack_d0 = 0;
  puStack_100 = PTR__ZTV25PartySetCharacterInfoList_02cb8610 + 0x10;
  uStack_d8 = 0;
  uStack_b8 = 0;
  lStack_c0 = 0;
  lStack_c8 = 0;
  while (puStack_78 != auStack_70) {
    if (*(int *)(puStack_78 + 0x11) == param_3) {
      PartySetInfo::operator=(PartySetInfo const&)(&puStack_1c8,puStack_78 + 5);
      *(undefined4 *)((long)param_2 + 0xc) = uStack_168;
      if (lStack_c0 != lStack_c8) goto code_r0x01d06634;
      goto code_r0x01d06610;
    }
    puVar19 = puStack_78;
    puVar3 = (undefined8 *)puStack_78[1];
    if ((undefined8 *)puStack_78[1] == (undefined8 *)0x0) {
      do {
        puStack_78 = (undefined8 *)puVar19[2];
        bVar4 = (undefined8 *)*puStack_78 != puVar19;
        puVar19 = puStack_78;
      } while (bVar4);
    }
    else {
      do {
        puStack_78 = puVar3;
        puVar3 = (undefined8 *)*puStack_78;
      } while ((undefined8 *)*puStack_78 != (undefined8 *)0x0);
    }
  }
  *(undefined4 *)((long)param_2 + 0xc) = uStack_168;
code_r0x01d06610:
  Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,0,0);
code_r0x01d06634:
  lVar10 = *(long *)puVar23;
  lVar25 = *(long *)(lStack_c8 + 0xc0);
  if (lVar10 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar10 = *(long *)puVar23;
  }
  for (lVar24 = *(long *)(lVar10 + 0x1178);
      (*(long *)(lVar10 + 0x1180) != lVar24 && (*(long *)(lVar24 + 0x60) != lVar25));
      lVar24 = lVar24 + 0xb88) {
  }
  CParameterUtility::tCharaData::tCharaData()(&uStack_2ef8);
  CParameterUtility::tCharaData::Initialize(unsigned long, bool, unsigned int, bool)(&uStack_2ef8,lVar25,1,0,0);
  uVar8 = *(undefined4 *)(lVar24 + 0x100);
  *param_2 = lVar25;
  *(char *)((long)param_2 + 100) = (char)*(undefined4 *)(lVar24 + 0x1f0);
  uVar28 = *(undefined4 *)(lVar24 + 400);
  *(undefined4 *)(param_2 + 2) = uVar8;
  *(short *)((long)param_2 + 0x2c) = (short)uVar28;
  lVar25 = *(long *)puVar23;
  if (lVar25 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar25 = *(long *)puVar23;
  }
  uVar12 = CParameterManager::pMasterParameterRole() const(lVar25);
  CMasterParameterBaseSqlite_Simple<CMasterParameterRoleElement>::pParameterFromHash(unsigned int) const(&lStack_2f08,uVar12,uVar8);
  *(undefined4 *)((long)param_2 + 0x14) = *(undefined4 *)(lStack_2f08 + 0x5a8);
  if (lStack_2f00 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  lVar25 = CParameterUtility::PlayerInfo()();
  *(undefined1 *)((long)param_2 + 99) = *(undefined1 *)(lVar25 + 0x870);
  lVar25 = CParameterUtility::PlayerInfo()();
  *(undefined4 *)(param_2 + 3) = *(undefined4 *)(lVar25 + 0x8a0);
  *(undefined4 *)(param_2 + 1) = *(undefined4 *)(lVar24 + 0x580);
  uVar28 = *(undefined4 *)(lVar24 + 0x830);
  *(undefined2 *)((long)param_2 + 0x2e) = 0;
  *(undefined4 *)((long)param_2 + 0x1c) = 0;
  *(char *)(param_2 + 6) = (char)uVar28;
  CInfoManager::GetResourceVersion() const(&puStack_3510,*(long *)puVar23 + 0x600);
  uVar13 = (ulong)puStack_3510 >> 1 & 0x7f;
  if (((ulong)puStack_3510 & 1) != 0) {
    uVar13 = uStack_3508;
  }
  if (uVar13 == 4) {
    piVar2 = (int *)((ulong)&puStack_3510 | 1);
    if (((ulong)puStack_3510 & 1) != 0) {
      piVar2 = piStack_3500;
    }
    if (*piVar2 != 0x656e6f6e) goto code_r0x01d06794;
  }
  else {
code_r0x01d06794:
    fVar27 = (float)Framework::CSTLStringUtility_Base<string >::AToF(string const&)(&puStack_3510);
    *(int *)((long)param_2 + 0x1c) = (int)fVar27;
  }
  if (((ulong)puStack_3510 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(piStack_3500);
  }
  lVar25 = *(long *)puVar23;
  if (lVar25 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar25 = *(long *)puVar23;
  }
  uVar12 = CParameterManager::pMasterParameterRole() const(lVar25);
  CMasterParameterBaseSqlite_Simple<CMasterParameterRoleElement>::pParameterFromHash(unsigned int) const(&lStack_2f18,uVar12,uVar8);
  lStack_2f48 = lStack_2f18;
  lStack_2f40 = lStack_2f10;
  if (lStack_2f10 != 0) {
    std::__ndk1::__shared_weak_count::__add_shared()();
  }
  CUIUtility::GetParameterAddMaxFromMasterRole(std::__ndk1::shared_ptr<CMasterParameterRoleElement>)(auStack_2f38,&lStack_2f48);
  if (lStack_2f40 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  CUIUtility::GetPersonParameterAdd(CPersonInfo const*)(auStack_2f68,lVar24);
  bVar6 = CUIUtility::tCharaStatus::IsGreaterEqual(CUIUtility::tCharaStatus const&, CUIUtility::tCharaStatus const&)(auStack_2f68,auStack_2f38);
  *(byte *)((long)param_2 + 0x62) = bVar6 & 1;
  *(undefined1 *)((long)param_2 + 0x61) = 0;
  uVar13 = CParameterUtility::EnableSubscriptionType(Common::Subscription::Type, long*)(1,0);
  if (((uVar13 & 1) != 0) && (uVar13 = CUIUtility::IsGalaxyPassIconShow()(), (uVar13 & 1) != 0)) {
    *(undefined1 *)((long)param_2 + 0x61) = 1;
  }
  if (lStack_2f18 == 0) {
    uVar7 = 1;
  }
  else {
    uVar7 = CParameterUtility::GetFavorabilityLevel(unsigned int)(*(undefined4 *)(lStack_2f18 + 0x208));
  }
  *(undefined1 *)((long)param_2 + 0x65) = uVar7;
  uVar8 = CParameterUtility::tCharaData::MasteryRoleID() const(&uStack_2ef8);
  *(undefined4 *)(param_2 + 5) = uVar8;
  uVar8 = CParameterUtility::tCharaData::MasteryTalentID() const(&uStack_2ef8);
  *(undefined4 *)((long)param_2 + 0x24) = uVar8;
  *(undefined4 *)(param_2 + 4) = *(undefined4 *)(lVar24 + 0xb20);
  *(char *)((long)param_2 + 0x66) = (char)*(undefined4 *)(lVar24 + 0xb50);
  *(undefined4 *)(param_2 + 99) = *(undefined4 *)(lVar24 + 0x430);
  *(undefined4 *)((long)param_2 + 0x314) = *(undefined4 *)(lVar24 + 0x460);
  *(undefined4 *)(param_2 + 0x62) = *(undefined4 *)(lVar24 + 0x490);
  *(undefined4 *)(param_2 + 0x67) = *(undefined4 *)(lVar24 + 0x4c0);
  *(undefined4 *)((long)param_2 + 0x30c) = *(undefined4 *)(lVar24 + 0x4f0);
  *(undefined4 *)((long)param_2 + 0x2ec) = *(undefined4 *)(lVar24 + 0x520);
  *(undefined4 *)(param_2 + 0x5d) = *(undefined4 *)(lVar24 + 0x550);
  *(undefined4 *)(param_2 + 0x61) = *(undefined4 *)(lVar24 + 0xab8);
  *(undefined4 *)((long)param_2 + 0x2f4) = *(undefined4 *)(lVar24 + 0x9c8);
  *(undefined4 *)((long)param_2 + 0x2fc) = *(undefined4 *)(lVar24 + 0xa28);
  *(undefined4 *)((long)param_2 + 0x304) = *(undefined4 *)(lVar24 + 0xa88);
  *(undefined4 *)(param_2 + 0x60) = *(undefined4 *)(lVar24 + 0xa58);
  *(undefined4 *)(param_2 + 0x5e) = *(undefined4 *)(lVar24 + 0x998);
  *(undefined4 *)(param_2 + 0x5f) = *(undefined4 *)(lVar24 + 0x9f8);
  lVar18 = *(long *)(lVar24 + 0x8c8);
  lVar25 = *(long *)(lVar24 + 0x8c0);
  uVar13 = (lVar18 - lVar25 >> 4) * -0x5555555555555555;
  if ((int)uVar13 != 0) {
    uVar11 = 0;
    lVar26 = 0x28;
    while( true ) {
      uVar14 = (lVar18 - lVar25 >> 4) * -0x5555555555555555;
      if (uVar14 < uVar11 || uVar14 - uVar11 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar11);
        lVar25 = *(long *)(lVar24 + 0x8c0);
      }
      *(undefined4 *)((long)param_2 + uVar11 * 4 + 0x33c) = *(undefined4 *)(lVar25 + lVar26);
      uVar11 = uVar11 + 1;
      if (((uVar13 & 0xffffffff) <= uVar11) || (0x4f < uVar11)) break;
      lVar18 = *(long *)(lVar24 + 0x8c8);
      lVar25 = *(long *)(lVar24 + 0x8c0);
      lVar26 = lVar26 + 0x30;
    }
  }
  if (cStack_108 == '\0') {
    puVar19 = (undefined8 *)(lVar24 + 0x130);
    plVar21 = (long *)(lVar24 + 0x160);
    *(undefined4 *)((long)param_2 + 0x334) = *(undefined4 *)(lVar24 + 0x220);
    *(undefined4 *)(param_2 + 0x66) = *(undefined4 *)(lVar24 + 0x2c0);
    *(undefined4 *)((long)param_2 + 0x32c) = *(undefined4 *)(lVar24 + 0x360);
    plVar15 = (long *)(lVar24 + 0x710);
    puVar23 = PTR__ZTV22CParameterPropertyBaseILj64EE_02cbbba0;
  }
  else {
    if (lStack_c0 == lStack_c8) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,0,0);
    }
    puVar23 = PTR__ZTV22CParameterPropertyBaseILj64EE_02cbbba0;
    plVar21 = (long *)(lStack_c8 + 0x120);
    *(undefined4 *)((long)param_2 + 0x334) = *(undefined4 *)(lStack_c8 + 0x150);
    *(undefined4 *)(param_2 + 0x66) = *(undefined4 *)(lStack_c8 + 0x180);
    puVar19 = (undefined8 *)(lStack_c8 + 0xf0);
    plVar15 = (long *)(lStack_c8 + 0x1e0);
    *(undefined4 *)((long)param_2 + 0x32c) = *(undefined4 *)(lStack_c8 + 0x1b0);
  }
  lVar25 = *plVar21;
  lVar18 = *plVar15;
  lStack_2f98 = 0;
  uStack_2f90 = 2;
  uStack_2f8c = 0;
  uStack_2f88 = 0;
  CParameterUtility::tItemData::tItemData(unsigned long, CParameterUtility::tItemData::Customizer const&)(&puStack_3510,*puVar19,&lStack_2f98);
  *(undefined8 *)((long)param_2 + 0x2d4) = 0;
  *(undefined8 *)((long)param_2 + 0x2cc) = 0;
  *(undefined8 *)((long)param_2 + 0x2c4) = 0;
  if (iStack_3360 == 0) {
    *(undefined8 *)((long)param_2 + 0x324) = 1;
    *(undefined1 *)((long)param_2 + 0x47d) = 0;
    plVar21 = (long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  }
  else {
    *(undefined4 *)(param_2 + 0x65) = auStack_3338[0];
    *(undefined4 *)((long)param_2 + 0x324) = uStack_3324;
    *(undefined1 *)((long)param_2 + 0x47d) = (undefined1)uStack_3320;
    uVar9 = CParameterUtility::tItemData::GearSlotCount() const(&puStack_3510);
    plVar21 = (long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (uVar9 != 0) {
      if (uVar9 < 8) {
        lVar26 = 0;
      }
      else {
        lVar26 = (ulong)uVar9 - (ulong)(uVar9 & 7);
        if (lVar26 != 0) {
          puVar22 = auStack_3338;
          plVar15 = param_2 + 0x5c;
          lVar16 = lVar26;
          do {
            uVar8 = *puVar22;
            uVar31 = puVar22[1];
            uVar28 = puVar22[2];
            uVar32 = puVar22[3];
            uVar29 = puVar22[4];
            uVar33 = puVar22[5];
            uVar30 = puVar22[6];
            uVar34 = puVar22[7];
            uVar35 = puVar22[-8];
            uVar37 = puVar22[-7];
            uVar36 = puVar22[-6];
            uVar38 = puVar22[-5];
            puVar20 = puVar22 + -4;
            uVar39 = puVar22[-3];
            puVar5 = puVar22 + -2;
            uVar40 = puVar22[-1];
            lVar16 = lVar16 + -8;
            puVar22 = puVar22 + 0x10;
            plVar15[-1] = CONCAT44(*puVar5,*puVar20);
            plVar15[-2] = CONCAT44(uVar36,uVar35);
            plVar15[1] = CONCAT44(uVar30,uVar29);
            *plVar15 = CONCAT44(uVar28,uVar8);
            *(ulong *)((long)plVar15 + -0x14) = CONCAT44(uVar40,uVar39);
            *(ulong *)((long)plVar15 + -0x1c) = CONCAT44(uVar38,uVar37);
            *(ulong *)((long)plVar15 + -4) = CONCAT44(uVar34,uVar33);
            *(ulong *)((long)plVar15 + -0xc) = CONCAT44(uVar32,uVar31);
            plVar15 = plVar15 + 4;
          } while (lVar16 != 0);
          if ((uVar9 & 7) == 0) goto code_r0x01d06ba4;
        }
      }
      lVar16 = (ulong)uVar9 - lVar26;
      puVar22 = (undefined4 *)((long)param_2 + lVar26 * 4 + 0x2d0);
      puVar20 = auStack_3354 + lVar26 * 2;
      do {
        puVar5 = puVar20 + -1;
        uVar8 = *puVar20;
        lVar16 = lVar16 + -1;
        puVar20 = puVar20 + 2;
        *puVar22 = *puVar5;
        puVar22[-3] = uVar8;
        puVar22 = puVar22 + 1;
      } while (lVar16 != 0);
    }
  }
code_r0x01d06ba4:
  CParameterUtility::tItemData::~tItemData()(&puStack_3510);
  puStack_3510 = PTR__ZTVNSt6__ndk110__function6__funcIZN9ItemModel10FindFromIDEmEUlRK9CItemInfoE_NS_9allocatorIS6_EEFbS5_EEE_02cbdaf0
                 + 0x10;
  uStack_3508 = lVar25;
  ppuStack_34f0 = &puStack_3510;
  ItemModel::Find(std::__ndk1::function<bool (CItemInfo const&)>)(&lStack_2f98,&puStack_3510);
  if (&puStack_3510 == ppuStack_34f0) {
    pcVar17 = *(code **)(*ppuStack_34f0 + 0x20);
  }
  else {
    if (ppuStack_34f0 == (undefined **)0x0) goto code_r0x01d06bf8;
    pcVar17 = *(code **)(*ppuStack_34f0 + 0x28);
  }
  (*pcVar17)();
code_r0x01d06bf8:
  uVar8 = 0;
  if (CONCAT44(uStack_2f84,uStack_2f88) != 0) {
    uVar8 = *(undefined4 *)(CONCAT44(uStack_2f84,uStack_2f88) + 0x38);
  }
  *(undefined4 *)(param_2 + 100) = uVar8;
  if (lStack_2f98 == 0) {
    *(undefined4 *)((long)param_2 + 0x31c) = 1;
    *(undefined1 *)((long)param_2 + 0x47c) = 0;
  }
  else {
    *(undefined4 *)((long)param_2 + 0x31c) = *(undefined4 *)(lStack_2f98 + 0x120);
    *(char *)((long)param_2 + 0x47c) = (char)*(undefined4 *)(lStack_2f98 + 0x180);
  }
  if (lVar25 != 0) {
    ItemModel::GetOne(unsigned long, unsigned int)(&puStack_3510,lVar25,*(undefined4 *)(lVar24 + 0x90));
    *(undefined4 *)(param_2 + 0x57) = uStack_3028;
    *(undefined4 *)((long)param_2 + 0x2b4) = uStack_2ff8;
    CItemDetailInfo::~CItemDetailInfo()(&puStack_3510);
  }
  if (lStack_2f70 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  if (lStack_2f80 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  if (lVar18 == 0) {
    *(undefined4 *)((long)param_2 + 0x2e4) = 0;
    *(undefined8 *)((long)param_2 + 0x2dc) = 0;
  }
  else {
    for (lVar25 = *(long *)(lVar10 + 0x1178);
        (*(long *)(lVar10 + 0x1180) != lVar25 && (*(long *)(lVar25 + 0x60) != lVar18));
        lVar25 = lVar25 + 0xb88) {
    }
    *(undefined4 *)((long)param_2 + 0x2e4) = *(undefined4 *)(lVar25 + 0x100);
    uVar8 = *(undefined4 *)(lVar25 + 0x1f0);
    *(undefined4 *)((long)param_2 + 0x2dc) = 0;
    *(undefined4 *)(param_2 + 0x5c) = uVar8;
    lVar10 = *plVar21;
    if (lVar10 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar10 = *plVar21;
    }
    uVar12 = CParameterManager::pMasterParameterRole() const(lVar10);
    CMasterParameterBaseSqlite_Simple<CMasterParameterRoleElement>::pParameterFromHash(unsigned int) const(&puStack_3510,uVar12,*(undefined4 *)(lVar25 + 0x100));
    if (puStack_3510 != (undefined *)0x0) {
      uVar8 = CParameterUtility::GetFavorabilityLevel(unsigned int)(*(undefined4 *)(puStack_3510 + 0x208));
      *(undefined4 *)((long)param_2 + 0x2dc) = uVar8;
    }
    if (uStack_3508 != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
  }
  lVar10 = CParameterUtility::PlayerInfo()();
  *(undefined4 *)(param_2 + 0xe) = *(undefined4 *)(lVar10 + 0x100);
  *(undefined4 *)(param_2 + 0x58) = *(undefined4 *)(lVar24 + 2000);
  *(undefined4 *)((long)param_2 + 700) = *(undefined4 *)(lVar24 + 0x800);
  lVar10 = *(long *)(lVar24 + 0x870);
  uVar13 = (*(long *)(lVar24 + 0x878) - lVar10 >> 3) * -0x3023023023023023;
  if ((int)uVar13 != 0) {
    lVar25 = (long)param_2 + 0xb4;
    lVar18 = 0x3a0;
    uVar11 = 1;
    while( true ) {
      lVar26 = lVar10 + lVar18;
      if (*(int *)(lVar26 + -0x2e0) != 0) {
        *(undefined4 *)(lVar25 + -0x40) = *(undefined4 *)(lVar26 + -0x310);
        *(int *)(lVar25 + -0xc) = *(int *)(lVar26 + -0x2e0);
        uStack_3508 = 0;
        piStack_3500 = (int *)0x0;
        puStack_3510 = (undefined *)0x0;
        void CParameterPropertyBase<79u>::CryptString<string >(string&, string const&)(&puStack_3510,lVar26 + -0x2b0);
        piVar2 = (int *)((ulong)&puStack_3510 | 1);
        if (((ulong)puStack_3510 & 1) != 0) {
          piVar2 = piStack_3500;
        }
        uVar14 = strlen(piVar2);
        if (uVar14 < 0x80) {
          strcpy(lVar25,piVar2);
        }
        else {
          raise(5);
        }
        if (((ulong)puStack_3510 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(piStack_3500);
        }
        puVar22 = (undefined4 *)(lVar10 + lVar18);
        *(undefined4 *)(lVar25 + -0x10) = puVar22[-0x9c];
        *(undefined4 *)(lVar25 + -0x14) = puVar22[-0x90];
        *(undefined4 *)(lVar25 + -0x18) = puVar22[-0x84];
        *(undefined4 *)(lVar25 + -0x1c) = puVar22[-0x78];
        *(undefined4 *)(lVar25 + -8) = puVar22[-0x6c];
        *(undefined4 *)(lVar25 + -0x20) = puVar22[-0x60];
        *(undefined4 *)(lVar25 + -0x28) = puVar22[-0x54];
        *(undefined4 *)(lVar25 + -0x2c) = puVar22[-0x48];
        *(undefined4 *)(lVar25 + -0x30) = puVar22[-0x3c];
        *(undefined4 *)(lVar25 + -0x34) = puVar22[-0x30];
        *(undefined4 *)(lVar25 + -0x38) = puVar22[-0x24];
        *(undefined4 *)(lVar25 + -0x3c) = puVar22[-0x18];
        *(undefined4 *)(lVar25 + -0x24) = puVar22[-0xc];
        *(undefined4 *)(lVar25 + -4) = *puVar22;
      }
      if (((uVar13 & 0xffffffff) <= uVar11) || (2 < uVar11)) break;
      lVar10 = *(long *)(lVar24 + 0x870);
      lVar18 = lVar18 + 0x3a8;
      lVar25 = lVar25 + 0xc0;
      uVar11 = uVar11 + 1;
    }
  }
  if (lStack_2f10 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  CParameterUtility::tCharaData::~tCharaData()(&uStack_2ef8);
  puStack_1c8 = PTR__ZTV12PartySetInfo_02cb7940 + 0x10;
  std::__ndk1::__vector_base<PartySetCharacterInfo, Framework::CSTLAllocator<PartySetCharacterInfo, Framework::CSTLVectorAllocatorInf> >::~__vector_base()(&lStack_c8);
  puVar1 = puVar1 + 0x10;
  puStack_100 = puVar1;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_e0,uStack_d8);
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_f8,uStack_f0);
  puStack_130 = PTR__ZTV22CParameterPropertyBaseILj66EE_02cc1e50 + 0x10;
  Framework::CHash32::~CHash32()(auStack_118);
  puStack_160 = PTR__ZTV22CParameterPropertyBaseILj65EE_02cb79a0 + 0x10;
  Framework::CHash32::~CHash32()(auStack_148);
  puStack_190 = puVar23 + 0x10;
  Framework::CHash32::~CHash32()(auStack_178);
  puStack_1c8 = puVar1;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_1a8,uStack_1a0);
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_1c0,uStack_1b8);
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned long, PartySetInfo>, std::__ndk1::__map_value_compare<unsigned long, std::__ndk1::__value_type<unsigned long, PartySetInfo>, std::__ndk1::less<unsigned long>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned long, PartySetInfo>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned long, PartySetInfo>, void*>*)(&puStack_78,auStack_70[0]);
  puStack_b0 = puVar1;
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(auStack_90,uStack_88);
  std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(auStack_a8,uStack_a0);
  return;
}

// ==== undefined CMultiPlay3::UpdatePlayerListEx(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo const *,unsigned short)
// _ZN11CMultiPlay318UpdatePlayerListExEPKN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoEt @ 01d06fc4

void _ZN11CMultiPlay318UpdatePlayerListExEPKN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoEt
               (long param_1,long param_2,uint param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined4 uVar8;
  int iVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined2 uVar17;
  char cVar18;
  char cVar19;
  uint uVar20;
  int iVar21;
  bool bVar22;
  int iVar23;
  undefined4 uVar24;
  ulong uVar25;
  undefined8 uVar26;
  undefined8 uVar27;
  ulong uVar28;
  ulong uVar29;
  long lVar30;
  long lVar31;
  ulong uVar32;
  long lVar33;
  int *piVar34;
  long *plVar35;
  long lVar36;
  ulong uVar37;
  long lVar38;
  ulong uStack_bb00;
  ulong uStack_baf8;
  ulong uStack_baf0;
  undefined1 auStack_bae8 [144];
  undefined4 uStack_ba58;
  undefined4 uStack_ba28;
  undefined1 auStack_b9f8 [64];
  undefined4 uStack_b9b8;
  undefined4 uStack_b988;
  undefined4 uStack_b958;
  undefined4 uStack_b928;
  undefined4 uStack_b8f8;
  undefined4 uStack_b8c8;
  undefined4 uStack_b898;
  undefined4 uStack_b748;
  undefined4 auStack_b740 [6];
  undefined4 uStack_b728;
  undefined4 uStack_b720;
  undefined4 uStack_b71c;
  undefined4 uStack_b718;
  undefined4 uStack_b714;
  undefined4 uStack_b710;
  undefined4 uStack_b70c;
  undefined4 uStack_b708;
  undefined4 uStack_b704;
  undefined1 auStack_b700 [128];
  undefined *puStack_b680;
  undefined8 *puStack_b678;
  undefined8 uStack_b670;
  undefined8 uStack_b668;
  undefined8 *puStack_b660;
  undefined8 uStack_b658;
  undefined8 uStack_b650;
  ulong uStack_b648;
  ulong uStack_b640;
  ulong uStack_b638;
  undefined *puStack_b630;
  undefined8 *puStack_b628;
  undefined8 uStack_b620;
  undefined8 uStack_b618;
  undefined8 *puStack_b610;
  undefined8 uStack_b608;
  undefined8 uStack_b600;
  undefined *puStack_b5f8;
  undefined8 uStack_b5f0;
  undefined1 uStack_b5e8;
  undefined1 auStack_b5e0 [16];
  undefined4 uStack_b5d0;
  undefined *puStack_b5c8;
  undefined8 uStack_b5c0;
  undefined1 uStack_b5b8;
  undefined1 auStack_b5b0 [16];
  undefined4 uStack_b5a0;
  long lStack_b598;
  undefined1 auStack_b590 [11568];
  undefined1 auStack_8860 [11568];
  undefined1 auStack_5b30 [11568];
  undefined1 auStack_2e00 [11576];
  undefined *puStack_c8;
  undefined1 auStack_c0 [8];
  undefined8 uStack_b8;
  undefined1 auStack_a8 [8];
  undefined8 uStack_a0;
  undefined1 auStack_90 [24];
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  
  memcpy(param_1 + 0xb9d0,param_2,0x1200);
  param_3 = param_3 & 0xffff;
  if (3 < param_3) {
    param_3 = 4;
  }
  if (param_3 != 0) {
    uVar32 = 0;
    piVar34 = (int *)(param_2 + 0x6c);
    do {
      iVar21 = piVar34[-1];
      iVar9 = *piVar34;
      iVar23 = CParameterUtility::tCharaData::UserId() const(param_1 + (long)iVar21 * 0x2d30 + 0x230);
      if (iVar9 != iVar23) {
        *(undefined4 *)(param_1 + (long)iVar21 * 4 + 0xb8e0) = 0;
      }
      uVar32 = uVar32 + 1;
      piVar34 = piVar34 + 0x120;
    } while (uVar32 < param_3);
  }
  CParameterUtility::tCharaData::Reset()(param_1 + 0x230);
  *(undefined1 *)(param_1 + 0xb6f0) = 0;
  CParameterUtility::tCharaData::Reset()(param_1 + 0x2f60);
  *(undefined1 *)(param_1 + 0xb6f1) = 0;
  CParameterUtility::tCharaData::Reset()(param_1 + 0x5c90);
  *(undefined1 *)(param_1 + 0xb6f2) = 0;
  CParameterUtility::tCharaData::Reset()(param_1 + 0x89c0);
  *(undefined1 *)(param_1 + 0xb6f3) = 0;
  if (*(long *)PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    *(undefined4 *)
     (*(long *)PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908 + 0x3dc) =
         0;
  }
  else {
    *(undefined4 *)
     (*(long *)PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908 + 0x3dc) =
         0;
  }
  if (param_3 != 0) {
    uVar29 = (ulong)&uStack_bb00 | 1;
    puVar1 = PTR__ZTV23CParameterPropertyValueIjLj14E18CPropertyConverterE_02cbaef8 + 0x10;
    puVar2 = PTR__ZTV23CParameterPropertyValueIjLj15E18CPropertyConverterE_02cc1598 + 0x10;
    puVar3 = PTR__ZTV28CCharacterDecoObjectInfoList_02cc4040 + 0x10;
    puVar4 = PTR__ZTV8InfoBase_02cc49c8 + 0x10;
    puVar5 = PTR__ZTV15InheritItemInfo_02cc2698 + 0x10;
    puVar6 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
    uVar32 = 0;
    puVar7 = PTR__ZTV22CParameterPropertyBaseILj15EE_02cc0790 + 0x10;
    do {
      uVar20 = *(uint *)(param_2 + uVar32 * 0x480 + 0x68);
      lVar33 = (long)(int)uVar20;
      if (((uVar20 < 4) && (piVar34 = (int *)(param_2 + uVar32 * 0x480 + 0x6c), *piVar34 != 0)) &&
         (plVar35 = (long *)(param_2 + uVar32 * 0x480), *plVar35 != 0)) {
        lVar38 = param_2 + uVar32 * 0x480;
        uStack_78 = *(undefined4 *)(lVar38 + 0x2d0);
        uStack_74 = *(undefined4 *)(lVar38 + 0x2c4);
        uStack_70 = *(undefined4 *)(lVar38 + 0x2d4);
        uStack_6c = *(undefined4 *)(lVar38 + 0x2c8);
        uStack_68 = *(undefined4 *)(lVar38 + 0x2d8);
        uStack_64 = *(undefined4 *)(lVar38 + 0x2cc);
        CParameterUtility::tItemData::GetGearList(unsigned int, CParameterUtility::tItemData::GearInfo const*)(&puStack_c8,3,&uStack_78);
        CParameterUtility::CreatePartyDataOne(unsigned int)(&lStack_b598,*(undefined4 *)(lVar38 + 0xc));
        uVar25 = CParameterUtility::IsPlayerId(unsigned int)(*piVar34);
        if (((uVar25 & 1) == 0) || (lStack_b598 == 0)) {
          bVar22 = false;
        }
        else {
          bVar22 = *(char *)(lStack_b598 + 0xc0) != '\0';
        }
        lVar38 = param_1 + lVar33 * 0x2d30 + 0x230;
        uStack_b620 = 0;
        uStack_b618 = 0;
        uStack_b608 = 0;
        uStack_b600 = 0;
        uStack_b5f0 = 0;
        uStack_b5e8 = 0;
        puStack_b630 = puVar5;
        puStack_b628 = &uStack_b620;
        puStack_b610 = &uStack_b608;
        puStack_b5f8 = puVar6;
        Framework::CHash32::CHash32()(auStack_b5e0);
        uStack_b5c0 = 0;
        uStack_b5b8 = 0;
        puStack_b5f8 = puVar1;
        puStack_b5c8 = puVar7;
        Framework::CHash32::CHash32()(auStack_b5b0);
        uVar26 = 0;
        lVar30 = param_2 + uVar32 * 0x480;
        uStack_b5d0 = *(undefined4 *)(lVar30 + 0x2b8);
        uStack_b5a0 = *(undefined4 *)(lVar30 + 0x2b4);
        cVar18 = *(char *)(lVar30 + 100);
        lVar36 = *plVar35;
        iVar9 = *piVar34;
        uVar10 = *(undefined4 *)(lVar30 + 0x70);
        uVar24 = *(undefined4 *)(lVar30 + 0x10);
        uVar8 = *(undefined4 *)(lVar30 + 0x14);
        uVar17 = *(undefined2 *)(lVar30 + 0x2c);
        uVar11 = *(undefined4 *)(lVar30 + 0x334);
        uVar12 = *(undefined4 *)(lVar30 + 0x330);
        uVar13 = *(undefined4 *)(lVar30 + 0x32c);
        uVar14 = *(undefined4 *)(lVar30 + 0x328);
        puStack_b5c8 = puVar2;
        if ((uVar25 & 1) != 0) {
          uVar26 = CParameterUtility::tCharaData::WeaponItemInfoId() const(auStack_b590);
        }
        lVar31 = param_2 + uVar32 * 0x480;
        uVar15 = *(undefined4 *)(lVar31 + 0x324);
        cVar19 = *(char *)(lVar31 + 0x47d);
        uVar16 = *(undefined4 *)(lVar31 + 800);
        if ((uVar25 & 1) == 0) {
          uVar27 = 0;
        }
        else {
          uVar27 = CParameterUtility::tCharaData::AccItemInfoId() const(auStack_b590);
        }
        lVar31 = param_2 + uVar32 * 0x480;
        CParameterUtility::tCharaData::InitializeMulti(unsigned long, unsigned int, unsigned int, int, signed char const*, int, int, int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned long, unsigned int, unsigned int, CAttachedGearInfoList const&, unsigned int, unsigned long, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, bool, bool, bool, unsigned int, InheritItemInfo const&, bool, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int const*, unsigned int, unsigned int, unsigned char)(lVar38,lVar36,uVar24,iVar9,uVar10,lVar30 + 0x31,uVar8,uVar17,(int)cVar18,
                        uVar11,uVar12,uVar13,uVar14,uVar26,uVar15,(int)cVar19,&puStack_c8,uVar16,
                        uVar27,*(undefined4 *)(lVar31 + 0x31c),(int)*(char *)(lVar31 + 0x47c),
                        *(undefined4 *)(lVar31 + 0x318),*(undefined4 *)(lVar31 + 0x2e8),
                        *(undefined4 *)(lVar31 + 0x314),*(undefined4 *)(lVar31 + 0x310),
                        *(undefined4 *)(lVar31 + 0x30c),*(undefined4 *)(lVar31 + 0x338),
                        *(undefined4 *)(lVar31 + 0x2ec),*(undefined4 *)(lVar31 + 8),
                        *(undefined4 *)(lVar31 + 0x2e4),*(undefined4 *)(lVar31 + 0x2e0),
                        *(undefined4 *)(lVar31 + 0x2dc),*(undefined1 *)(lVar31 + 0x65),0,
                        *(char *)(lVar31 + 99) != '\0',*(char *)(lVar31 + 0x61) != '\0',
                        *(undefined4 *)(lVar31 + 0x18),&puStack_b630,
                        *(char *)(lVar31 + 0x30) != '\0',*(undefined4 *)(lVar31 + 0x308),
                        *(undefined4 *)(lVar31 + 0x2f4),*(undefined4 *)(lVar31 + 0x2fc),
                        *(undefined4 *)(lVar31 + 0x304),*(undefined4 *)(lVar31 + 0x300),
                        *(undefined4 *)(lVar31 + 0x2f0),*(undefined4 *)(lVar31 + 0x2f8),
                        lVar31 + 0x33c,0x50,*(undefined4 *)(lVar31 + 0x20),
                        *(undefined1 *)(lVar31 + 0x66));
        CParameterUtility::tCharaData::InitializeMastery(unsigned int, unsigned int, bool)(lVar38,*(undefined4 *)(lVar31 + 0x28),*(undefined4 *)(lVar31 + 0x24),0);
        CParameterUtility::tCharaData::InitializeRare7Flag(bool)(lVar38,*(char *)(lVar31 + 0x30) != '\0');
        *(bool *)(param_1 + 0x228 + lVar33 * 0x2d30 + 0x13cc) = bVar22;
        *(bool *)(param_1 + 0x228 + lVar33 + 0xb4c8) = *(char *)(lVar31 + 0x2f) != '\0';
        uStack_b670 = 0;
        uStack_b668 = 0;
        uStack_b658 = 0;
        uStack_b650 = 0;
        uStack_b640 = 0;
        uStack_b638 = 0;
        uStack_b648 = 0;
        puStack_b680 = puVar3;
        puStack_b678 = &uStack_b670;
        puStack_b660 = &uStack_b658;
        memcpy(auStack_b740,lVar31 + 0x74,0xc0);
        CCharacterDecoObjectInfo::CCharacterDecoObjectInfo()(auStack_bae8);
        uStack_baf0 = 0;
        uStack_baf8 = 0;
        uStack_ba58 = auStack_b740[0];
        uStack_bb00 = 0;
        uVar25 = strlen(auStack_b700);
        if (uVar25 < 0x17) {
          uStack_bb00 = CONCAT71(uStack_bb00._1_7_,(char)(uVar25 << 1));
          uVar28 = uVar29;
          if (uVar25 != 0) goto code_r0x01d0771c;
        }
        else {
          uVar37 = uVar25 + 0x10 & 0xfffffffffffffff0;
          if (uVar37 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          uVar28 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar37,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (uVar28 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uStack_bb00 = uVar37 | 1;
          uStack_baf8 = uVar25;
          uStack_baf0 = uVar28;
code_r0x01d0771c:
          memcpy(uVar28,auStack_b700,uVar25);
        }
        *(undefined1 *)(uVar28 + uVar25) = 0;
        void CParameterPropertyBase<79u>::CryptString<string >(string&, string const&)(auStack_b9f8,&uStack_bb00);
        if ((uStack_bb00 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_baf0);
        }
        uVar25 = uStack_b640;
        uStack_b9b8 = uStack_b710;
        uStack_b958 = uStack_b718;
        uStack_ba28 = uStack_b70c;
        uStack_b988 = uStack_b714;
        uStack_b8f8 = uStack_b708;
        uStack_b928 = uStack_b71c;
        uStack_b8c8 = uStack_b720;
        uStack_b898 = uStack_b728;
        uStack_b748 = uStack_b704;
        if (uStack_b640 < uStack_b638) {
          if (uStack_b640 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          CCharacterDecoObjectInfo::CCharacterDecoObjectInfo(CCharacterDecoObjectInfo const&)(uVar25,auStack_bae8);
          uStack_b640 = uStack_b640 + 0x3a8;
        }
        else {
          void std::__ndk1::vector<CCharacterDecoObjectInfo, Framework::CSTLAllocator<CCharacterDecoObjectInfo, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<CCharacterDecoObjectInfo&>(CCharacterDecoObjectInfo&)(&uStack_b648,auStack_bae8);
        }
        CCharacterDecoObjectInfo::~CCharacterDecoObjectInfo()(auStack_bae8);
        memcpy(auStack_b740,param_2 + uVar32 * 0x480 + 0x134,0xc0);
        CCharacterDecoObjectInfo::CCharacterDecoObjectInfo()(auStack_bae8);
        uStack_baf0 = 0;
        uStack_baf8 = 0;
        uStack_ba58 = auStack_b740[0];
        uStack_bb00 = 0;
        uVar25 = strlen(auStack_b700);
        if (uVar25 < 0x17) {
          uStack_bb00 = CONCAT71(uStack_bb00._1_7_,(char)(uVar25 << 1));
          uVar28 = uVar29;
          if (uVar25 != 0) goto code_r0x01d078b0;
        }
        else {
          uVar37 = uVar25 + 0x10 & 0xfffffffffffffff0;
          if (uVar37 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          uVar28 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar37,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (uVar28 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uStack_bb00 = uVar37 | 1;
          uStack_baf8 = uVar25;
          uStack_baf0 = uVar28;
code_r0x01d078b0:
          memcpy(uVar28,auStack_b700,uVar25);
        }
        *(undefined1 *)(uVar28 + uVar25) = 0;
        void CParameterPropertyBase<79u>::CryptString<string >(string&, string const&)(auStack_b9f8,&uStack_bb00);
        if ((uStack_bb00 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_baf0);
        }
        uVar25 = uStack_b640;
        uStack_b9b8 = uStack_b710;
        uStack_b958 = uStack_b718;
        uStack_ba28 = uStack_b70c;
        uStack_b988 = uStack_b714;
        uStack_b8f8 = uStack_b708;
        uStack_b928 = uStack_b71c;
        uStack_b8c8 = uStack_b720;
        uStack_b898 = uStack_b728;
        uStack_b748 = uStack_b704;
        if (uStack_b640 < uStack_b638) {
          if (uStack_b640 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          CCharacterDecoObjectInfo::CCharacterDecoObjectInfo(CCharacterDecoObjectInfo const&)(uVar25,auStack_bae8);
          uStack_b640 = uStack_b640 + 0x3a8;
        }
        else {
          void std::__ndk1::vector<CCharacterDecoObjectInfo, Framework::CSTLAllocator<CCharacterDecoObjectInfo, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<CCharacterDecoObjectInfo&>(CCharacterDecoObjectInfo&)(&uStack_b648,auStack_bae8);
        }
        CCharacterDecoObjectInfo::~CCharacterDecoObjectInfo()(auStack_bae8);
        memcpy(auStack_b740,param_2 + uVar32 * 0x480 + 500,0xc0);
        CCharacterDecoObjectInfo::CCharacterDecoObjectInfo()(auStack_bae8);
        uStack_baf0 = 0;
        uStack_baf8 = 0;
        uStack_ba58 = auStack_b740[0];
        uStack_bb00 = 0;
        uVar25 = strlen(auStack_b700);
        if (uVar25 < 0x17) {
          uStack_bb00 = CONCAT71(uStack_bb00._1_7_,(char)(uVar25 << 1));
          uVar28 = uVar29;
          if (uVar25 != 0) goto code_r0x01d07a44;
        }
        else {
          uVar37 = uVar25 + 0x10 & 0xfffffffffffffff0;
          if (uVar37 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
          }
          uVar28 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar37,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
          if (uVar28 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
          }
          uStack_bb00 = uVar37 | 1;
          uStack_baf8 = uVar25;
          uStack_baf0 = uVar28;
code_r0x01d07a44:
          memcpy(uVar28,auStack_b700,uVar25);
        }
        *(undefined1 *)(uVar28 + uVar25) = 0;
        void CParameterPropertyBase<79u>::CryptString<string >(string&, string const&)(auStack_b9f8,&uStack_bb00);
        if ((uStack_bb00 & 1) != 0) {
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_baf0);
        }
        uVar25 = uStack_b640;
        uStack_b9b8 = uStack_b710;
        uStack_b958 = uStack_b718;
        uStack_ba28 = uStack_b70c;
        uStack_b988 = uStack_b714;
        uStack_b8f8 = uStack_b708;
        uStack_b928 = uStack_b71c;
        uStack_b8c8 = uStack_b720;
        uStack_b898 = uStack_b728;
        uStack_b748 = uStack_b704;
        if (uStack_b640 < uStack_b638) {
          if (uStack_b640 == 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xcc,&UNK_027dc43e/*"apAssignedMemory is null."*/);
          }
          CCharacterDecoObjectInfo::CCharacterDecoObjectInfo(CCharacterDecoObjectInfo const&)(uVar25,auStack_bae8);
          uStack_b640 = uStack_b640 + 0x3a8;
        }
        else {
          void std::__ndk1::vector<CCharacterDecoObjectInfo, Framework::CSTLAllocator<CCharacterDecoObjectInfo, Framework::CSTLVectorAllocatorInf> >::__emplace_back_slow_path<CCharacterDecoObjectInfo&>(CCharacterDecoObjectInfo&)(&uStack_b648,auStack_bae8);
        }
        CCharacterDecoObjectInfo::~CCharacterDecoObjectInfo()(auStack_bae8);
        lVar33 = param_2 + uVar32 * 0x480;
        CParameterUtility::tCharaData::InitializeDeco(unsigned int, unsigned int, CCharacterDecoObjectInfoList const&)(lVar38,*(undefined4 *)(lVar33 + 0x2c0),*(undefined4 *)(lVar33 + 700),
                        &puStack_b680);
        lVar33 = *(long *)PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908;
        if (lVar33 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar33 = *(long *)
                    PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908;
        }
        uVar25 = uStack_b648;
        *(undefined1 *)(lVar33 + (ulong)uVar20 + 0x3dc) = 1;
        if (uStack_b648 != 0) {
          while (uStack_b640 != uVar25) {
            uStack_b640 = uStack_b640 - 0x3a8;
            CCharacterDecoObjectInfo::~CCharacterDecoObjectInfo()();
          }
          Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_b648);
        }
        puStack_b680 = puVar4;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_b660,uStack_b658);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_b678,uStack_b670);
        puStack_b630 = PTR__ZTV15InheritItemInfo_02cc2698 + 0x10;
        puStack_b5c8 = PTR__ZTV22CParameterPropertyBaseILj15EE_02cc0790 + 0x10;
        Framework::CHash32::~CHash32()(auStack_b5b0);
        puStack_b5f8 = PTR__ZTV22CParameterPropertyBaseILj14EE_02cb9db0 + 0x10;
        Framework::CHash32::~CHash32()(auStack_b5e0);
        puStack_b630 = puVar4;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(&puStack_b610,uStack_b608);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(&puStack_b628,uStack_b620);
        CParameterUtility::tCharaData::~tCharaData()(auStack_2e00);
        CParameterUtility::tCharaData::~tCharaData()(auStack_5b30);
        CParameterUtility::tCharaData::~tCharaData()(auStack_8860);
        CParameterUtility::tCharaData::~tCharaData()(auStack_b590);
        std::__ndk1::__vector_base<CAttachedGearInfo, Framework::CSTLAllocator<CAttachedGearInfo, Framework::CSTLVectorAllocatorInf> >::~__vector_base()(auStack_90);
        puStack_c8 = puVar4;
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, InfoBase*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, InfoBase*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, InfoBase*>, void*>*)(auStack_a8,uStack_a0);
        std::__ndk1::__tree<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::__map_value_compare<unsigned int, std::__ndk1::__value_type<unsigned int, IParameterProperty*>, std::__ndk1::less<unsigned int>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, Framework::CSTLMapAllocatorInf> >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<unsigned int, IParameterProperty*>, void*>*)(auStack_c0,uStack_b8);
      }
      uVar32 = uVar32 + 1;
    } while (uVar32 < param_3);
  }
  lVar33 = *(long *)(param_1 + 0x1c8);
  if (lVar33 != 0) {
    uVar24 = CParameterUtility::tPartyData::SelfIndex() const(param_1 + 0x228);
    CStampUI::SetSelfIndex(int)(lVar33,uVar24);
  }
  *(undefined4 *)(param_1 + 0xb72c) = 1;
  return;
}

// ==== undefined CMultiPlay3::RoomInfo2RoomData(Aska::Yayoi::MultiplayRPC::RoomInfo const &,bool)
// _ZN11CMultiPlay317RoomInfo2RoomDataERKN4Aska5Yayoi12MultiplayRPC8RoomInfoEb @ 01d07cc4

void _ZN11CMultiPlay317RoomInfo2RoomDataERKN4Aska5Yayoi12MultiplayRPC8RoomInfoEb
               (long param_1,long param_2)

{
  long lVar1;
  ulong *puVar2;
  int iVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  long lStack_60;
  long lStack_58;
  
  lVar1 = param_2 + 0x3a7;
  puVar2 = (ulong *)(param_1 + 0xb958);
  uVar4 = strlen(lVar1);
  uVar6 = (ulong)*(byte *)puVar2;
  if ((*(byte *)puVar2 & 1) == 0) {
    uVar5 = 0x16;
    lVar7 = uVar4 - 0x16;
    if (uVar4 < 0x16 || lVar7 == 0) goto code_r0x01d07d10;
code_r0x01d07d34:
    if ((uVar6 & 1) == 0) {
      uVar6 = (ulong)(((uint)uVar6 & 0xfe) >> 1);
    }
    else {
      uVar6 = *(ulong *)(param_1 + 0xb960);
    }
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar2,uVar5,lVar7,uVar6,0,uVar6,uVar4,lVar1);
  }
  else {
    uVar6 = *puVar2;
    uVar5 = (uVar6 & 0xfffffffffffffffe) - 1;
    lVar7 = uVar4 - uVar5;
    if (uVar5 <= uVar4 && lVar7 != 0) goto code_r0x01d07d34;
code_r0x01d07d10:
    if ((uVar6 & 1) == 0) {
      lVar7 = param_1 + 0xb959;
    }
    else {
      lVar7 = *(long *)(param_1 + 0xb968);
    }
    if (uVar4 != 0) {
      memmove(lVar7,lVar1,uVar4);
    }
    *(undefined1 *)(lVar7 + uVar4) = 0;
    if ((*(byte *)puVar2 & 1) == 0) {
      *(byte *)puVar2 = (byte)(uVar4 << 1);
    }
    else {
      *(ulong *)(param_1 + 0xb960) = uVar4;
    }
  }
  *(int *)(param_1 + 0xb998) = *(int *)(param_2 + 0x240);
  lVar1 = param_2 + 0x386;
  iVar3 = 0;
  if (*(int *)(param_2 + 0x244) != -1) {
    iVar3 = *(int *)(param_2 + 0x244);
  }
  *(int *)(param_1 + 0xb9a8) = iVar3;
  *(undefined4 *)(param_1 + 0xb9a4) = *(undefined4 *)(param_2 + 0x248);
  *(undefined4 *)(param_1 + 0xb9a0) = *(undefined4 *)(param_2 + 0x24c);
  puVar2 = (ulong *)(param_1 + 0xb970);
  uVar4 = strlen(lVar1);
  uVar6 = (ulong)*(byte *)puVar2;
  if ((*(byte *)puVar2 & 1) == 0) {
    uVar5 = 0x16;
    lVar7 = uVar4 - 0x16;
    if (0x15 < uVar4 && lVar7 != 0) {
code_r0x01d07e34:
      if ((uVar6 & 1) == 0) {
        uVar6 = (ulong)(((uint)uVar6 & 0xfe) >> 1);
      }
      else {
        uVar6 = *(ulong *)(param_1 + 0xb978);
      }
      string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(puVar2,uVar5,lVar7,uVar6,0,uVar6,uVar4,lVar1);
      goto code_r0x01d07ea4;
    }
  }
  else {
    uVar6 = *puVar2;
    uVar5 = (uVar6 & 0xfffffffffffffffe) - 1;
    lVar7 = uVar4 - uVar5;
    if (uVar5 <= uVar4 && lVar7 != 0) goto code_r0x01d07e34;
  }
  if ((uVar6 & 1) == 0) {
    lVar7 = param_1 + 0xb971;
  }
  else {
    lVar7 = *(long *)(param_1 + 0xb980);
  }
  if (uVar4 != 0) {
    memmove(lVar7,lVar1,uVar4);
  }
  *(undefined1 *)(lVar7 + uVar4) = 0;
  if ((*(byte *)puVar2 & 1) == 0) {
    *(byte *)puVar2 = (byte)(uVar4 << 1);
  }
  else {
    *(ulong *)(param_1 + 0xb978) = uVar4;
  }
code_r0x01d07ea4:
  *(bool *)(param_1 + 0xb9c0) = *(char *)(param_2 + 0x3a6) == '\0';
  *(undefined4 *)(param_1 + 0xb988) = 0;
  *(bool *)(param_1 + 0xb9c1) = *(int *)(param_2 + 0x250) != 0;
  *(undefined4 *)(param_1 + 0xb98c) = *(undefined4 *)(param_2 + 600);
  *(undefined4 *)(param_1 + 0xb990) = *(undefined4 *)(param_2 + 0x25c);
  *(undefined4 *)(param_1 + 0xb994) = *(undefined4 *)(param_2 + 0x260);
  if (*(int *)(param_1 + 0xb998) == 1) {
    CParameterUtility::FindAreaWithMissionId(unsigned int)(&lStack_60,*(undefined4 *)(param_1 + 0xb9a0));
    if (lStack_60 != 0) {
      *(undefined4 *)(param_1 + 0xb9ac) = *(undefined4 *)(lStack_60 + 0x338);
    }
    if (lStack_58 != 0) {
      std::__ndk1::__shared_weak_count::__release_shared()();
    }
  }
  return;
}

// ==== undefined CMultiPlay3::Server_InitializeCommon(void)
// _ZN11CMultiPlay323Server_InitializeCommonEv @ 01d07f4c

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _ZN11CMultiPlay323Server_InitializeCommonEv(ulong param_1)

{
  undefined1 *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined *puVar5;
  undefined8 uVar6;
  ulong uVar7;
  long lVar8;
  long *plVar9;
  undefined8 *puVar10;
  ulong uVar11;
  long lVar12;
  code *pcVar13;
  undefined *puVar14;
  ulong uVar15;
  ulong uVar16;
  ulong uStack_198;
  ulong uStack_190;
  ulong uStack_188;
  long alStack_180 [4];
  long *plStack_160;
  undefined *puStack_150;
  ulong uStack_148;
  undefined **ppuStack_130;
  ulong uStack_120;
  undefined8 uStack_118;
  undefined8 *puStack_110;
  byte abStack_108 [16];
  ulong uStack_f8;
  ulong uStack_f0;
  ulong uStack_e8;
  undefined8 *puStack_e0;
  ulong uStack_d0;
  ulong uStack_c8;
  ulong uStack_c0;
  ulong uStack_b8;
  ulong uStack_b0;
  ulong uStack_a8;
  byte abStack_a0 [16];
  undefined8 uStack_90;
  byte bStack_88;
  undefined1 auStack_87 [15];
  undefined1 *puStack_78;
  undefined *puStack_70;
  ulong uStack_68;
  ulong uStack_60;
  undefined **ppuStack_50;
  
  puVar14 = PTR__ZN9Framework10TSingletonI14ServerSelectorE11m_pInstanceE_02cc2c10;
  lVar12 = *(long *)PTR__ZN9Framework10TSingletonI14ServerSelectorE11m_pInstanceE_02cc2c10;
  if (lVar12 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar12 = *(long *)puVar14;
  }
  uVar6 = ServerSelector::pServerAddressLobby()(lVar12);
  uStack_b8 = 0;
  uStack_b0 = 0;
  uStack_a8 = 0;
  uVar7 = strlen();
  if (uVar7 < 0x17) {
    uVar15 = (ulong)&uStack_b8 | 1;
    uStack_b8 = CONCAT71(uStack_b8._1_7_,(char)(uVar7 << 1));
    if (uVar7 != 0) goto code_r0x01d08030;
  }
  else {
    uVar11 = uVar7 + 0x10 & 0xfffffffffffffff0;
    if (uVar11 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar15 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar15 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_b8 = uVar11 | 1;
    uStack_b0 = uVar7;
    uStack_a8 = uVar15;
code_r0x01d08030:
    memcpy(uVar15,uVar6,uVar7);
  }
  *(undefined1 *)(uVar15 + uVar7) = 0;
  lVar12 = *(long *)puVar14;
  if (lVar12 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar12 = *(long *)puVar14;
  }
  uVar6 = ServerSelector::pServerAddressLobby()(lVar12);
  uStack_d0 = 0;
  uStack_c8 = 0;
  uStack_c0 = 0;
  uVar7 = strlen();
  if (uVar7 < 0x17) {
    uVar15 = (ulong)&uStack_d0 | 1;
    uStack_d0 = CONCAT71(uStack_d0._1_7_,(char)(uVar7 << 1));
    if (uVar7 != 0) goto code_r0x01d08104;
  }
  else {
    uVar11 = uVar7 + 0x10 & 0xfffffffffffffff0;
    if (uVar11 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar15 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar11,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar15 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_d0 = uVar11 | 1;
    uStack_c8 = uVar7;
    uStack_c0 = uVar15;
code_r0x01d08104:
    memcpy(uVar15,uVar6,uVar7);
  }
  *(undefined1 *)(uVar15 + uVar7) = 0;
  CMultiPlay3::tServerData::tServerData(string, string)(abStack_a0,&uStack_b8,&uStack_d0);
  if ((uStack_d0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_c0);
  }
  if ((uStack_b8 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_a8);
  }
  puVar14 = PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908;
  if (*(long **)PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908 !=
      (long *)0x0) {
    (**(code **)(**(long **)
                   PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908 + 8))()
    ;
    *(undefined8 *)puVar14 = 0;
  }
  puVar14 = PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
  lVar12 = **(long **)PTR__ZN4Aska6Global19m_pNetworkAllocatorE_02cbc200;
  if (lVar12 == 0) {
    lVar12 = Aska::Global::GetAvailableMemoryManager()();
  }
  lVar12 = Aska::MemoryManager::Malloc(unsigned long)(lVar12,0x3f8);
  if (lVar12 != 0) {
    CMultiplayManager::CMultiplayManager()(lVar12);
  }
  lVar8 = **(long **)puVar14;
  if (lVar8 == 0) {
    lVar8 = Aska::Global::GetAvailableMemoryManager()();
  }
  lVar8 = Aska::MemoryManager::Malloc(unsigned long)(lVar8,0x380);
  *(long *)(param_1 + 0x1b8) = lVar8;
  if (lVar8 != 0) {
    CUIMatchingNotify::CUIMatchingNotify()();
  }
  puVar14 = PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8;
  lVar8 = *(long *)
           PTR__ZN9Framework10TSingletonINS_12CApplication9CMainTaskEE11m_pInstanceE_02cc41c8;
  if (lVar8 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar8 = *(long *)puVar14;
  }
  plVar9 = (long *)Framework::CApplication::CMainTask::rRootFiberKernel()(lVar8);
  (**(code **)(*plVar9 + 0x48))(plVar9,lVar12);
  *(undefined1 *)(param_1 + 0xb942) = 0;
  puStack_70 = &UNK_02b72d98;
  uStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short)>::swap(std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short)>&)(&puStack_70,*(long *)(param_1 + 0x1b8) + 0x200);
  if (&puStack_70 == ppuStack_50) {
    pcVar13 = *(code **)(*ppuStack_50 + 0x20);
code_r0x01d08250:
    (*pcVar13)();
  }
  else if (ppuStack_50 != (undefined **)0x0) {
    pcVar13 = *(code **)(*ppuStack_50 + 0x28);
    goto code_r0x01d08250;
  }
  CMultiPlay3::Server_ErrorCallback_default()(param_1);
  CMultiPlay3::RegistErrorCreateInstance()(param_1);
  *(undefined4 *)(param_1 + 0xb920) = 0x5a;
  puVar1 = auStack_87;
  if ((bStack_88 & 1) != 0) {
    puVar1 = puStack_78;
  }
  CMultiplayManager::Initialize(char const*, unsigned short, Aska::Yayoi::IMatchingNotify*)(&puStack_70,lVar12,puVar1,0xfa1,*(undefined8 *)(param_1 + 0x1b8));
  puVar5 = puStack_70;
  if (-1 < (long)puStack_70) {
    uVar6 = 1;
    goto joined_r0x01d08764;
  }
  lVar12 = *(long *)puVar14;
  if (lVar12 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar12 = *(long *)puVar14;
  }
  Framework::CApplication::CMainTask::rFader() const(lVar12);
  Framework::CFader::ToOpen(float)(0);
  uStack_e8 = 0;
  puStack_e0 = (undefined8 *)0x0;
  uStack_f0 = 0;
  puVar10 = (undefined8 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x30,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
  if (puVar10 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
  uVar4 = _UNK_028ff768;
  uVar3 = _UNK_028ff760;
  uVar2 = _UNK_028ff758;
  uVar6 = _UNK_028ff750;
  uStack_e8 = _UNK_02869c78;
  uStack_f0 = _UNK_02869c70;
  *(undefined2 *)(puVar10 + 4) = 0x7265;
  puVar10[1] = uVar2;
  *puVar10 = uVar6;
  puVar10[3] = uVar4;
  puVar10[2] = uVar3;
  *(undefined1 *)((long)puVar10 + 0x22) = 0;
  puStack_e0 = puVar10;
  CUIUtility::GetSystemMessage(string const&, long, bool*)(&puStack_70,&uStack_f0,0,0);
  if ((uStack_f0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_e0);
  }
  if (((ulong)puStack_70 & 1) == 0) {
    uVar7 = 0x16;
    puVar14 = (undefined *)((ulong)puStack_70 & 0xff);
  }
  else {
    uVar7 = ((ulong)puStack_70 & 0xfffffffffffffffe) - 1;
    puVar14 = puStack_70;
  }
  uVar11 = (ulong)(((uint)puVar14 & 0xfe) >> 1);
  if (((ulong)puVar14 & 1) != 0) {
    uVar11 = uStack_68;
  }
  if (uVar7 == uVar11) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_70,uVar7,1,uVar7,uVar7,0,1,&UNK_029c5cc4);
  }
  else {
    uVar7 = (ulong)&puStack_70 | 1;
    if (((ulong)puVar14 & 1) != 0) {
      uVar7 = uStack_60;
    }
    *(undefined1 *)(uVar7 + uVar11) = 10;
    uVar11 = uVar11 + 1;
    uVar15 = uVar11;
    if (((ulong)puStack_70 & 1) == 0) {
      puStack_70 = (undefined *)CONCAT71(puStack_70._1_7_,(char)uVar11 * '\x02');
      uVar15 = uStack_68;
    }
    uStack_68 = uVar15;
    *(undefined1 *)(uVar7 + uVar11) = 0;
  }
  uStack_118 = 0;
  puStack_110 = (undefined8 *)0x0;
  uStack_120 = 0;
  puVar10 = (undefined8 *)Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(0x20,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
  if (puVar10 == (undefined8 *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
  }
  uVar2 = _UNK_027ebf1a;
  uVar6 = CONCAT17(UNK_027ebf29,_UNK_027ebf22);
  uStack_118 = _UNK_027dbb68;
  uStack_120 = _UNK_027dbb60;
  *(ulong *)((long)puVar10 + 0xf) = CONCAT71(_UNK_027ebf2a,UNK_027ebf29);
  puVar10[1] = uVar6;
  *puVar10 = uVar2;
  *(undefined1 *)((long)puVar10 + 0x17) = 0;
  puStack_110 = puVar10;
  CUIUtility::GetSystemMessage(string const&, long, bool*)(abStack_108,&uStack_120,0,0);
  uVar7 = (ulong)abStack_108 | 1;
  if ((abStack_108[0] & 1) != 0) {
    uVar7 = uStack_f8;
  }
  Framework::CSTLStringUtility_Base<string >::Format(char const*, ...)(&uStack_f0,uVar7,(ulong)puVar5 & 0xffffffff);
  uVar7 = uStack_f0 >> 1 & 0x7f;
  puVar10 = (undefined8 *)((ulong)&uStack_f0 | 1);
  if ((uStack_f0 & 1) != 0) {
    uVar7 = uStack_e8;
    puVar10 = puStack_e0;
  }
  if (((ulong)puStack_70 & 1) == 0) {
    lVar12 = 0x16;
    puVar14 = (undefined *)((ulong)puStack_70 & 0xff);
  }
  else {
    lVar12 = ((ulong)puStack_70 & 0xfffffffffffffffe) - 1;
    puVar14 = puStack_70;
  }
  uVar11 = (ulong)(((uint)puVar14 & 0xfe) >> 1);
  if (((ulong)puVar14 & 1) != 0) {
    uVar11 = uStack_68;
  }
  if (lVar12 - uVar11 < uVar7) {
    string::__grow_by_and_replace(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, char const*)(&puStack_70,lVar12,(uVar7 - lVar12) + uVar11,uVar11,uVar11,0,uVar7);
  }
  else if (uVar7 != 0) {
    uVar15 = (ulong)&puStack_70 | 1;
    if (((ulong)puVar14 & 1) != 0) {
      uVar15 = uStack_60;
    }
    memcpy(uVar15 + uVar11,puVar10,uVar7);
    uVar11 = uVar11 + uVar7;
    if (((ulong)puStack_70 & 1) == 0) {
      puStack_70 = (undefined *)CONCAT71(puStack_70._1_7_,(char)uVar11 * '\x02');
      *(undefined1 *)(uVar15 + uVar11) = 0;
    }
    else {
      *(undefined1 *)(uVar15 + uVar11) = 0;
      uStack_68 = uVar11;
    }
  }
  if ((uStack_f0 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_e0);
  }
  if ((abStack_108[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_f8);
  }
  if ((uStack_120 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_110);
  }
  puStack_150 = &UNK_02b72d18;
  ppuStack_130 = &puStack_150;
  uVar7 = (ulong)&puStack_70 | 1;
  if (((ulong)puStack_70 & 1) != 0) {
    uVar7 = uStack_60;
  }
  plStack_160 = (long *)0x0;
  uStack_190 = 0;
  uStack_188 = 0;
  uStack_198 = 0;
  uStack_148 = param_1;
  uVar11 = strlen(uVar7);
  if (uVar11 < 0x17) {
    uVar16 = (ulong)&uStack_198 | 1;
    uStack_198 = CONCAT71(uStack_198._1_7_,(char)(uVar11 << 1));
    if (uVar11 != 0) goto code_r0x01d086b0;
  }
  else {
    uVar15 = uVar11 + 0x10 & 0xfffffffffffffff0;
    if (uVar15 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbb,&UNK_027db115/*"aNumElements is zero."*/);
    }
    uVar16 = Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(unsigned long, char const*, unsigned int)(uVar15,&UNK_027db145/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_String.h"*/,0x1c);
    if (uVar16 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027db0be/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Allocator.h"*/,0xbe,&UNK_027db12b/*"pAllocatedMemory is null."*/);
    }
    uStack_198 = uVar15 | 1;
    uStack_190 = uVar11;
    uStack_188 = uVar16;
code_r0x01d086b0:
    memcpy(uVar16,uVar7,uVar11);
  }
  *(undefined1 *)(uVar16 + uVar11) = 0;
  CMultiPlay3::OpenDialog(unsigned int, std::__ndk1::function<void ()>, std::__ndk1::function<void ()>, string, unsigned int, unsigned int)(param_1,0x17,&puStack_150,alStack_180,&uStack_198,0,0);
  if ((uStack_198 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_188);
  }
  if (alStack_180 == plStack_160) {
    pcVar13 = *(code **)(*plStack_160 + 0x20);
code_r0x01d0871c:
    (*pcVar13)();
  }
  else if (plStack_160 != (long *)0x0) {
    pcVar13 = *(code **)(*plStack_160 + 0x28);
    goto code_r0x01d0871c;
  }
  if (&puStack_150 == ppuStack_130) {
    pcVar13 = *(code **)(*ppuStack_130 + 0x20);
code_r0x01d08748:
    (*pcVar13)();
  }
  else if (ppuStack_130 != (undefined **)0x0) {
    pcVar13 = *(code **)(*ppuStack_130 + 0x28);
    goto code_r0x01d08748;
  }
  if (((ulong)puStack_70 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_60);
  }
  uVar6 = 0;
joined_r0x01d08764:
  if ((bStack_88 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(puStack_78);
  }
  if ((abStack_a0[0] & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_90);
  }
  return uVar6;
}

// ==== undefined CMultiPlay3::Server_MultiPlayCbkReset(void)
// _ZN11CMultiPlay324Server_MultiPlayCbkResetEv @ 01d08900

void _ZN11CMultiPlay324Server_MultiPlayCbkResetEv(long param_1)

{
  code *pcVar1;
  undefined *puStack_40;
  long lStack_38;
  long *plStack_20;
  
  plStack_20 = (long *)&puStack_40;
  *(undefined1 *)(param_1 + 0xb942) = 0;
  puStack_40 = &UNK_02b72d98;
  lStack_38 = param_1;
  std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short)>::swap(std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short)>&)(&puStack_40,*(long *)(param_1 + 0x1b8) + 0x200);
  if (&puStack_40 == (undefined **)plStack_20) {
    pcVar1 = *(code **)(*plStack_20 + 0x20);
  }
  else {
    if (plStack_20 == (long *)0x0) {
      return;
    }
    pcVar1 = *(code **)(*plStack_20 + 0x28);
  }
  (*pcVar1)();
  return;
}

// ==== undefined CMultiPlay3::Server_ErrorCallback_default(void)
// _ZN11CMultiPlay328Server_ErrorCallback_defaultEv @ 01d0896c

void _ZN11CMultiPlay328Server_ErrorCallback_defaultEv(long param_1)

{
  long *plVar1;
  code *pcVar2;
  undefined *puStack_50;
  long lStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  puStack_50 = &UNK_02b74588;
  lStack_48 = param_1;
  std::__ndk1::function<void (Aska::Status)>::swap(std::__ndk1::function<void (Aska::Status)>&)(&puStack_50,*(long *)(param_1 + 0x1b8) + 0x2f0);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar2 = *(code **)(*plStack_30 + 0x20);
code_r0x01d089c8:
    (*pcVar2)();
  }
  else if (plStack_30 != (long *)0x0) {
    pcVar2 = *(code **)(*plStack_30 + 0x28);
    goto code_r0x01d089c8;
  }
  puStack_50 = &UNK_02b74608;
  lStack_48 = param_1;
  plStack_30 = (long *)&puStack_50;
  std::__ndk1::function<void (Aska::Status)>::swap(std::__ndk1::function<void (Aska::Status)>&)(&puStack_50,*(long *)(param_1 + 0x1b8) + 800);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar2 = *(code **)(*plStack_30 + 0x20);
code_r0x01d08a18:
    (*pcVar2)();
  }
  else if (plStack_30 != (long *)0x0) {
    pcVar2 = *(code **)(*plStack_30 + 0x28);
    goto code_r0x01d08a18;
  }
  puStack_50 = &UNK_02b74688;
  lStack_48 = param_1;
  plStack_30 = (long *)&puStack_50;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_50,*(long *)(param_1 + 0x1b8) + 0x350);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar2 = *(code **)(*plStack_30 + 0x20);
code_r0x01d08a68:
    (*pcVar2)();
  }
  else if (plStack_30 != (long *)0x0) {
    pcVar2 = *(code **)(*plStack_30 + 0x28);
    goto code_r0x01d08a68;
  }
  plVar1 = *(long **)(param_1 + 0xb7e0);
  if ((long *)(param_1 + 0xb7c0) == plVar1) {
    pcVar2 = *(code **)(*plVar1 + 0x20);
code_r0x01d08aa0:
    (*pcVar2)();
  }
  else if (plVar1 != (long *)0x0) {
    pcVar2 = *(code **)(*plVar1 + 0x28);
    goto code_r0x01d08aa0;
  }
  *(long *)(param_1 + 0xb7e0) = 0;
  plStack_30 = (long *)0x0;
  std::__ndk1::function<bool (Aska::Status)>::swap(std::__ndk1::function<bool (Aska::Status)>&)(&puStack_50,param_1 + 0xb7f0);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar2 = *(code **)(*plStack_30 + 0x20);
code_r0x01d08ae4:
    (*pcVar2)();
  }
  else if (plStack_30 != (long *)0x0) {
    pcVar2 = *(code **)(*plStack_30 + 0x28);
    goto code_r0x01d08ae4;
  }
  plVar1 = *(long **)(param_1 + 0xb840);
  if ((long *)(param_1 + 0xb820) == plVar1) {
    pcVar2 = *(code **)(*plVar1 + 0x20);
  }
  else {
    if (plVar1 == (long *)0x0) goto code_r0x01d08b20;
    pcVar2 = *(code **)(*plVar1 + 0x28);
  }
  (*pcVar2)();
code_r0x01d08b20:
  *(long *)(param_1 + 0xb840) = 0;
  return;
}

// ==== undefined CMultiPlay3::GetLobbyOpenedMaxTime(void)
// _ZN11CMultiPlay321GetLobbyOpenedMaxTimeEv @ 01d096b4

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int _ZN11CMultiPlay321GetLobbyOpenedMaxTimeEv(void)

{
  undefined *puVar1;
  long lVar2;
  int iVar3;
  float fVar4;
  byte bStack_170;
  undefined7 uStack_16f;
  undefined1 uStack_168;
  undefined5 uStack_167;
  undefined2 uStack_162;
  undefined1 uStack_160;
  undefined5 uStack_15f;
  undefined1 uStack_15a;
  undefined1 uStack_159;
  long lStack_158;
  long lStack_150;
  undefined *puStack_148;
  undefined8 uStack_140;
  ulong *puStack_138;
  undefined8 uStack_130;
  undefined4 uStack_128;
  undefined1 uStack_124;
  ulong uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  
  puVar1 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (*(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar2 = *(long *)(*(long *)puVar1 + 0x5f8);
    if (lVar2 != 0) goto code_r0x01d096d8;
code_r0x01d097fc:
    lStack_158 = 0;
    lStack_150 = 0;
  }
  else {
    lVar2 = *(long *)(*(long *)
                       PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0 +
                     0x5f8);
    if (lVar2 == 0) goto code_r0x01d097fc;
code_r0x01d096d8:
    lVar2 = *(long *)(lVar2 + 0x2c0);
    if (lVar2 == 0) goto code_r0x01d097fc;
    uStack_159 = 0;
    bStack_170 = 0x2a;
    uStack_167 = _UNK_028ff77b;
    uStack_16f = (undefined7)_UNK_028ff773;
    uStack_168 = (undefined1)((ulong)_UNK_028ff773 >> 0x38);
    uStack_162 = (undefined2)_UNK_028ff780;
    uStack_160 = (undefined1)((uint3)_UNK_028ff780 >> 0x10);
    uStack_15f = _UNK_028ff783;
    uStack_15a = 0;
    snprintf(&uStack_120,0x100,&UNK_027f6a37/*"%s"*/,(ulong)&bStack_170 | 1);
    puStack_148 = &UNK_029dbbc5/*"key"*/;
    uStack_140 = 3;
    puStack_138 = &uStack_120;
    uStack_130 = strlen(&uStack_120);
    uStack_128 = 0;
    uStack_124 = 0;
    CMasterParameterBaseSqlite_Simple<CMasterParameterGlobalElement>::ParameterByQuery(char const*, Aska::Yayoi::QueryParam*, unsigned int) const(&lStack_158,lVar2,&UNK_028602b5/*"SELECT * FROM master_global WHERE key=?"*/,&puStack_148,1);
    if ((bStack_170 & 1) != 0) {
      Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(CONCAT17(uStack_159,CONCAT16(uStack_15a,CONCAT51(uStack_15f,uStack_160))));
    }
    if (lStack_158 != 0) {
      uStack_118 = 0;
      uStack_110 = 0;
      uStack_120 = 0;
      void CParameterPropertyBase<43u>::CryptString<string >(string&, string const&)(&uStack_120,lStack_158 + 0xe8);
      fVar4 = (float)Framework::CSTLStringUtility_Base<string >::AToF(string const&)(&uStack_120);
      iVar3 = (int)fVar4;
      if ((uStack_120 & 1) != 0) {
        Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_110);
      }
      goto joined_r0x01d09814;
    }
  }
  iVar3 = 0;
joined_r0x01d09814:
  if (lStack_150 != 0) {
    std::__ndk1::__shared_weak_count::__release_shared()();
  }
  return iVar3;
}

// ==== undefined CMultiPlay3::Server_CreateRoomHost(std::__ndk1::function<void ()>,std::__ndk1::function<void ()>)
// _ZN11CMultiPlay321Server_CreateRoomHostENSt6__ndk18functionIFvvEEES3_ @ 01d09868

void _ZN11CMultiPlay321Server_CreateRoomHostENSt6__ndk18functionIFvvEEES3_
               (undefined *param_1,long *param_2,long *param_3)

{
  long *plVar1;
  undefined8 uVar2;
  long *plVar3;
  long lVar4;
  undefined **ppuVar5;
  undefined *puVar6;
  code *pcVar7;
  long lVar8;
  undefined *puStack_720;
  undefined *puStack_718;
  long alStack_710 [2];
  long *plStack_700;
  long *plStack_6f0;
  undefined *apuStack_2a0 [2];
  long alStack_290 [2];
  undefined **ppuStack_280;
  long *plStack_270;
  undefined1 auStack_258 [367];
  undefined1 auStack_e9 [121];
  long alStack_70 [4];
  long *plStack_50;
  
  plStack_700 = (long *)&puStack_720;
  plVar1 = (long *)param_3[4];
  if (plVar1 == (long *)0x0) {
    plStack_700 = (long *)0x0;
  }
  else if (param_3 == plVar1) {
    (**(code **)(*plVar1 + 0x18))(plVar1,&puStack_720);
  }
  else {
    plStack_700 = (long *)(**(code **)(*plVar1 + 0x10))();
  }
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_720,param_1 + 0xb760);
  if (&puStack_720 == (undefined **)plStack_700) {
    pcVar7 = *(code **)(*plStack_700 + 0x20);
code_r0x01d09904:
    (*pcVar7)();
  }
  else if (plStack_700 != (long *)0x0) {
    pcVar7 = *(code **)(*plStack_700 + 0x28);
    goto code_r0x01d09904;
  }
  param_1[0xb947] = 0;
  param_1[0xb949] = 0;
  param_1[0xb94a] = 1;
  *(undefined8 *)(param_1 + 0xb924) = 0;
  uVar2 = CUIUtility::GetButton(Framework::Cocos::CCocosNode*, char const*)(*(undefined8 *)(param_1 + 0x160),&UNK_028ff192/*"Button_start"*/);
  CUIUtility::SetButtonStateOpacity(Framework::Cocos::CCocosNode*, bool)(uVar2,1);
  uVar2 = CUIUtility::GetButton(Framework::Cocos::CCocosNode*, char const*)(*(undefined8 *)(param_1 + 0x160),&UNK_028ff427/*"Button_party"*/);
  CUIUtility::SetButtonStateOpacity(Framework::Cocos::CCocosNode*, bool)(uVar2,1);
  uVar2 = CUIUtility::GetButton(Framework::Cocos::CCocosNode*, char const*)(*(undefined8 *)(param_1 + 0x160),&UNK_028db1fd/*"list/plate/Button_2"*/);
  CUIUtility::SetButtonStateOpacity(Framework::Cocos::CCocosNode*, bool)(uVar2,1);
  *(undefined4 *)(param_1 + 0xb938) = 0;
  param_1[0xb942] = 0;
  puStack_720 = &UNK_02b72d98;
  puStack_718 = param_1;
  plStack_700 = (long *)&puStack_720;
  std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short)>::swap(std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short)>&)(&puStack_720,*(long *)(param_1 + 0x1b8) + 0x200);
  if (&puStack_720 == (undefined **)plStack_700) {
    pcVar7 = *(code **)(*plStack_700 + 0x20);
code_r0x01d099d0:
    (*pcVar7)();
  }
  else if (plStack_700 != (long *)0x0) {
    pcVar7 = *(code **)(*plStack_700 + 0x28);
    goto code_r0x01d099d0;
  }
  CMultiPlay3::Server_CreateRoomContdition(Aska::Yayoi::MultiplayRPC::RoomCondition*, bool)(param_1,auStack_258,0);
  plVar1 = (long *)param_2[4];
  apuStack_2a0[0] = param_1;
  if (plVar1 == (long *)0x0) {
    plStack_270 = (long *)0x0;
  }
  else if (param_2 == plVar1) {
    plStack_270 = alStack_290;
    (**(code **)(*plVar1 + 0x18))();
  }
  else {
    plStack_270 = (long *)(**(code **)(*plVar1 + 0x10))();
  }
  puVar6 = apuStack_2a0[0];
  lVar8 = *(long *)(param_1 + 0x1b8);
  puStack_720 = apuStack_2a0[0];
  if (plStack_270 == (long *)0x0) {
    plStack_6f0 = (long *)0x0;
  }
  else if (alStack_290 == plStack_270) {
    plStack_6f0 = alStack_710;
    (**(code **)(*plStack_270 + 0x18))();
    puVar6 = puStack_720;
  }
  else {
    plStack_6f0 = (long *)(**(code **)(*plStack_270 + 0x10))();
  }
  plVar1 = plStack_6f0;
  plStack_50 = (long *)0x0;
  plVar3 = (long *)operator new(unsigned long)(0x50);
  *plVar3 = (long)&UNK_02b73238;
  plVar3[2] = (long)puVar6;
  if (plVar1 == (long *)0x0) {
    plVar3[8] = 0;
  }
  else if (alStack_710 == plVar1) {
    plVar3[8] = (long)(plVar3 + 4);
    (**(code **)(*plVar1 + 0x18))(plVar1);
  }
  else {
    lVar4 = (**(code **)(*plVar1 + 0x10))(plVar1);
    plVar3[8] = lVar4;
  }
  plStack_50 = plVar3;
  std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::RoomInfo&)>::swap(std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::RoomInfo&)>&)(alStack_70,lVar8 + 0x50);
  if (alStack_70 == plStack_50) {
    pcVar7 = *(code **)(*plStack_50 + 0x20);
code_r0x01d09b40:
    (*pcVar7)();
  }
  else if (plStack_50 != (long *)0x0) {
    pcVar7 = *(code **)(*plStack_50 + 0x28);
    goto code_r0x01d09b40;
  }
  if (alStack_710 == plStack_6f0) {
    pcVar7 = *(code **)(*plStack_6f0 + 0x20);
code_r0x01d09b70:
    (*pcVar7)();
  }
  else if (plStack_6f0 != (long *)0x0) {
    pcVar7 = *(code **)(*plStack_6f0 + 0x28);
    goto code_r0x01d09b70;
  }
  if (alStack_290 == plStack_270) {
    pcVar7 = *(code **)(*plStack_270 + 0x20);
code_r0x01d09ba0:
    (*pcVar7)();
  }
  else if (plStack_270 != (long *)0x0) {
    pcVar7 = *(code **)(*plStack_270 + 0x28);
    goto code_r0x01d09ba0;
  }
  plVar1 = *(long **)(param_1 + 0xb7e0);
  if ((long *)(param_1 + 0xb7c0) == plVar1) {
    pcVar7 = *(code **)(*plVar1 + 0x20);
code_r0x01d09bd8:
    (*pcVar7)();
  }
  else if (plVar1 != (long *)0x0) {
    pcVar7 = *(code **)(*plVar1 + 0x28);
    goto code_r0x01d09bd8;
  }
  *(undefined8 *)(param_1 + 0xb7e0) = 0;
  plStack_700 = (long *)0x0;
  std::__ndk1::function<bool (Aska::Status)>::swap(std::__ndk1::function<bool (Aska::Status)>&)(&puStack_720,param_1 + 0xb7f0);
  if (&puStack_720 == (undefined **)plStack_700) {
    pcVar7 = *(code **)(*plStack_700 + 0x20);
code_r0x01d09c1c:
    (*pcVar7)();
  }
  else if (plStack_700 != (long *)0x0) {
    pcVar7 = *(code **)(*plStack_700 + 0x28);
    goto code_r0x01d09c1c;
  }
  plVar1 = *(long **)(param_1 + 0xb840);
  if ((long *)(param_1 + 0xb820) == plVar1) {
    pcVar7 = *(code **)(*plVar1 + 0x20);
  }
  else {
    if (plVar1 == (long *)0x0) goto code_r0x01d09c58;
    pcVar7 = *(code **)(*plVar1 + 0x28);
  }
  (*pcVar7)();
code_r0x01d09c58:
  *(undefined8 *)(param_1 + 0xb840) = 0;
  if ((param_1[0xb958] & 1) == 0) {
    puVar6 = param_1 + 0xb959;
  }
  else {
    puVar6 = *(undefined **)(param_1 + 0xb968);
  }
  __aska_snprintf_s(char*, unsigned long, unsigned long, char const*, ...)(auStack_e9,0x78,0xffffffffffffffff,&UNK_027f6a37/*"%s"*/,puVar6);
  puVar6 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar8 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar8 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar8 = *(long *)puVar6;
  }
  lVar8 = CParameterManager::pParameterUI() const(lVar8);
  CMultiPlay3::Server_CreatePlayerInfo(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo&, int)(lVar8,&puStack_720,*(undefined4 *)(lVar8 + 0x1b0));
  ppuVar5 = (undefined **)operator new(unsigned long)(0x678);
  *ppuVar5 = &UNK_02b733d8;
  ppuVar5[1] = param_1;
  memcpy(ppuVar5 + 2,&puStack_720,0x480);
  memcpy(ppuVar5 + 0x92,auStack_258,0x1e8);
  ppuStack_280 = ppuVar5;
  CMultiPlay3::RegistCall(std::__ndk1::function<bool ()> const&, bool, unsigned int)(param_1,apuStack_2a0,1);
  if (apuStack_2a0 == ppuStack_280) {
    pcVar7 = *(code **)(*ppuStack_280 + 0x20);
  }
  else {
    if (ppuStack_280 == (undefined **)0x0) {
      return;
    }
    pcVar7 = *(code **)(*ppuStack_280 + 0x28);
  }
  (*pcVar7)();
  return;
}

// ==== undefined CMultiPlay3::Server_AutoMatching(void)
// _ZN11CMultiPlay319Server_AutoMatchingEv @ 01d09d68

void _ZN11CMultiPlay319Server_AutoMatchingEv(long param_1)

{
  byte *pbVar1;
  byte bVar2;
  code *pcVar3;
  undefined1 *puVar4;
  undefined *puStack_80;
  long lStack_78;
  long *plStack_60;
  long alStack_50 [4];
  long *plStack_30;
  
  plStack_60 = (long *)&puStack_80;
  pbVar1 = (byte *)(param_1 + 0xb970);
  bVar2 = *pbVar1;
  if ((bVar2 & 1) != 0) {
    bVar2 = *pbVar1;
  }
  if ((bVar2 & 1) == 0) {
    puVar4 = (undefined1 *)(param_1 + 0xb971);
  }
  else {
    puVar4 = *(undefined1 **)(param_1 + 0xb980);
  }
  *puVar4 = 0;
  if ((*pbVar1 & 1) == 0) {
    *pbVar1 = 0;
  }
  else {
    *(undefined8 *)(param_1 + 0xb978) = 0;
  }
  plStack_30 = (long *)0x0;
  puStack_80 = &UNK_02b73458;
  lStack_78 = param_1;
  CMultiPlay3::Server_CreateRoomList(std::__ndk1::function<void ()>, std::__ndk1::function<void ()>, bool)(param_1,alStack_50,&puStack_80,1);
  if (&puStack_80 == (undefined **)plStack_60) {
    pcVar3 = *(code **)(*plStack_60 + 0x20);
code_r0x01d09e10:
    (*pcVar3)();
  }
  else if (plStack_60 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_60 + 0x28);
    goto code_r0x01d09e10;
  }
  if (alStack_50 == plStack_30) {
    pcVar3 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x01d09e40;
    pcVar3 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar3)();
code_r0x01d09e40:
  *(byte *)(*(long *)(param_1 + 0x180) + 0xd8) = *(byte *)(*(long *)(param_1 + 0x180) + 0xd8) | 2;
  return;
}

// ==== undefined CMultiPlay3::Server_CreateRoomList(std::__ndk1::function<void ()>,std::__ndk1::function<void ()>,bool)
// _ZN11CMultiPlay321Server_CreateRoomListENSt6__ndk18functionIFvvEEES3_b @ 01d09e60

void _ZN11CMultiPlay321Server_CreateRoomListENSt6__ndk18functionIFvvEEES3_b
               (undefined *param_1,long *param_2,long *param_3,byte param_4)

{
  undefined4 uVar1;
  long *plVar2;
  byte *pbVar3;
  undefined8 uVar4;
  byte *pbVar5;
  ulong uVar6;
  code *pcVar7;
  undefined *puVar8;
  long lVar9;
  undefined *puStack_720;
  undefined *puStack_718;
  long *plStack_700;
  undefined *puStack_6f0;
  undefined *puStack_6e8;
  long alStack_6e0 [2];
  undefined **ppuStack_6d0;
  long *plStack_6c0;
  long alStack_6b0 [4];
  long *plStack_690;
  undefined *apuStack_270 [2];
  long alStack_260 [4];
  long *plStack_240;
  long alStack_230 [4];
  long *plStack_210;
  byte bStack_80;
  undefined4 uStack_7f;
  undefined2 uStack_7b;
  undefined1 uStack_79;
  undefined8 uStack_78;
  undefined8 uStack_70;
  byte *pbStack_60;
  
  pbVar5 = param_1 + 0xb947;
  *pbVar5 = param_4 & 1;
  param_1[0xb942] = 0;
  puStack_6f0 = &UNK_02b72d98;
  puStack_6e8 = param_1;
  ppuStack_6d0 = &puStack_6f0;
  std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short)>::swap(std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short)>&)(&puStack_6f0,*(long *)(param_1 + 0x1b8) + 0x200);
  if (&puStack_6f0 == ppuStack_6d0) {
    pcVar7 = *(code **)(*ppuStack_6d0 + 0x20);
code_r0x01d09ee8:
    (*pcVar7)();
  }
  else if (ppuStack_6d0 != (undefined **)0x0) {
    pcVar7 = *(code **)(*ppuStack_6d0 + 0x28);
    goto code_r0x01d09ee8;
  }
  apuStack_270[0] = param_1;
  if (*pbVar5 == 0) {
    plVar2 = (long *)param_2[4];
    if (plVar2 == (long *)0x0) {
      plStack_240 = (long *)0x0;
    }
    else if (param_2 == plVar2) {
      plStack_240 = alStack_260;
      (**(code **)(*plVar2 + 0x18))();
    }
    else {
      plStack_240 = (long *)(**(code **)(*plVar2 + 0x10))();
    }
    puVar8 = apuStack_270[0];
    lVar9 = *(long *)(param_1 + 0x1b8);
    puStack_6f0 = apuStack_270[0];
    if (plStack_240 == (long *)0x0) {
      plStack_6c0 = (long *)0x0;
    }
    else if (alStack_260 == plStack_240) {
      plStack_6c0 = alStack_6e0;
      (**(code **)(*plStack_240 + 0x18))();
      puVar8 = puStack_6f0;
    }
    else {
      plStack_6c0 = (long *)(**(code **)(*plStack_240 + 0x10))();
    }
    plVar2 = plStack_6c0;
    pbStack_60 = (byte *)0x0;
    pbVar3 = (byte *)operator new(unsigned long)(0x50);
    *(undefined **)pbVar3 = &UNK_02b739f8;
    *(undefined **)(pbVar3 + 0x10) = puVar8;
    if (plVar2 == (long *)0x0) {
      pbVar3[0x40] = 0;
      pbVar3[0x41] = 0;
      pbVar3[0x42] = 0;
      pbVar3[0x43] = 0;
      pbVar3[0x44] = 0;
      pbVar3[0x45] = 0;
      pbVar3[0x46] = 0;
      pbVar3[0x47] = 0;
    }
    else if (alStack_6e0 == plVar2) {
      *(byte **)(pbVar3 + 0x40) = pbVar3 + 0x20;
      (**(code **)(*plVar2 + 0x18))(plVar2);
    }
    else {
      uVar4 = (**(code **)(*plVar2 + 0x10))(plVar2);
      *(undefined8 *)(pbVar3 + 0x40) = uVar4;
    }
    pbStack_60 = pbVar3;
    std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::RoomInfo*, unsigned int&)>::swap(std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::RoomInfo*, unsigned int&)>&)(&bStack_80,lVar9 + 0x80);
    if (&bStack_80 == pbStack_60) {
      pcVar7 = *(code **)(*(long *)pbStack_60 + 0x20);
code_r0x01d0a320:
      (*pcVar7)();
    }
    else if (pbStack_60 != (byte *)0x0) {
      pcVar7 = *(code **)(*(long *)pbStack_60 + 0x28);
      goto code_r0x01d0a320;
    }
    plVar2 = plStack_6c0;
    if (alStack_6e0 != plStack_6c0) goto code_r0x01d0a1dc;
code_r0x01d0a338:
    pcVar7 = *(code **)(*plVar2 + 0x20);
code_r0x01d0a340:
    (*pcVar7)();
  }
  else {
    plVar2 = (long *)param_2[4];
    if (plVar2 == (long *)0x0) {
      plStack_240 = (long *)0x0;
      plVar2 = (long *)param_3[4];
joined_r0x01d09f58:
      if (plVar2 == (long *)0x0) goto code_r0x01d09f20;
code_r0x01d09f5c:
      if (param_3 == plVar2) {
        plStack_210 = alStack_230;
        (**(code **)(*plVar2 + 0x18))();
      }
      else {
        plStack_210 = (long *)(**(code **)(*plVar2 + 0x10))();
      }
    }
    else {
      if (param_2 == plVar2) {
        plStack_240 = alStack_260;
        (**(code **)(*plVar2 + 0x18))();
        plVar2 = (long *)param_3[4];
        goto joined_r0x01d09f58;
      }
      plStack_240 = (long *)(**(code **)(*plVar2 + 0x10))();
      plVar2 = (long *)param_3[4];
      if (plVar2 != (long *)0x0) goto code_r0x01d09f5c;
code_r0x01d09f20:
      plStack_210 = (long *)0x0;
    }
    lVar9 = *(long *)(param_1 + 0x1b8);
    puStack_6f0 = apuStack_270[0];
    if (plStack_240 == (long *)0x0) {
      plStack_6c0 = (long *)0x0;
joined_r0x01d0a000:
      if (plStack_210 == (long *)0x0) goto code_r0x01d09ff0;
code_r0x01d0a004:
      if (alStack_230 == plStack_210) {
        plStack_690 = alStack_6b0;
        (**(code **)(*plStack_210 + 0x18))();
      }
      else {
        plStack_690 = (long *)(**(code **)(*plStack_210 + 0x10))();
      }
    }
    else {
      if (alStack_260 == plStack_240) {
        plStack_6c0 = alStack_6e0;
        (**(code **)(*plStack_240 + 0x18))();
        goto joined_r0x01d0a000;
      }
      plStack_6c0 = (long *)(**(code **)(*plStack_240 + 0x10))();
      if (plStack_210 != (long *)0x0) goto code_r0x01d0a004;
code_r0x01d09ff0:
      plStack_690 = (long *)0x0;
    }
    pbStack_60 = (byte *)0x0;
    pbVar3 = (byte *)operator new(unsigned long)(0x80);
    *(undefined **)pbVar3 = &UNK_02b73868;
    *(undefined **)(pbVar3 + 0x10) = puStack_6f0;
    if (plStack_6c0 == (long *)0x0) {
      pbVar3[0x40] = 0;
      pbVar3[0x41] = 0;
      pbVar3[0x42] = 0;
      pbVar3[0x43] = 0;
      pbVar3[0x44] = 0;
      pbVar3[0x45] = 0;
      pbVar3[0x46] = 0;
      pbVar3[0x47] = 0;
joined_r0x01d0a0d0:
      if (plStack_690 == (long *)0x0) goto code_r0x01d0a0c0;
code_r0x01d0a0d4:
      if (alStack_6b0 == plStack_690) {
        *(byte **)(pbVar3 + 0x70) = pbVar3 + 0x50;
        (**(code **)(*plStack_690 + 0x18))();
      }
      else {
        uVar4 = (**(code **)(*plStack_690 + 0x10))();
        *(undefined8 *)(pbVar3 + 0x70) = uVar4;
      }
    }
    else {
      if (alStack_6e0 == plStack_6c0) {
        *(byte **)(pbVar3 + 0x40) = pbVar3 + 0x20;
        (**(code **)(*plStack_6c0 + 0x18))();
        goto joined_r0x01d0a0d0;
      }
      uVar4 = (**(code **)(*plStack_6c0 + 0x10))();
      *(undefined8 *)(pbVar3 + 0x40) = uVar4;
      if (plStack_690 != (long *)0x0) goto code_r0x01d0a0d4;
code_r0x01d0a0c0:
      pbVar3[0x70] = 0;
      pbVar3[0x71] = 0;
      pbVar3[0x72] = 0;
      pbVar3[0x73] = 0;
      pbVar3[0x74] = 0;
      pbVar3[0x75] = 0;
      pbVar3[0x76] = 0;
      pbVar3[0x77] = 0;
    }
    pbStack_60 = pbVar3;
    std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::RoomInfo&, int)>::swap(std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::RoomInfo&, int)>&)(&bStack_80,lVar9 + 0x290);
    if (&bStack_80 == pbStack_60) {
      pcVar7 = *(code **)(*(long *)pbStack_60 + 0x20);
code_r0x01d0a164:
      (*pcVar7)();
    }
    else if (pbStack_60 != (byte *)0x0) {
      pcVar7 = *(code **)(*(long *)pbStack_60 + 0x28);
      goto code_r0x01d0a164;
    }
    if (alStack_6b0 == plStack_690) {
      pcVar7 = *(code **)(*plStack_690 + 0x20);
code_r0x01d0a194:
      (*pcVar7)();
    }
    else if (plStack_690 != (long *)0x0) {
      pcVar7 = *(code **)(*plStack_690 + 0x28);
      goto code_r0x01d0a194;
    }
    if (alStack_6e0 == plStack_6c0) {
      pcVar7 = *(code **)(*plStack_6c0 + 0x20);
code_r0x01d0a1c4:
      (*pcVar7)();
    }
    else if (plStack_6c0 != (long *)0x0) {
      pcVar7 = *(code **)(*plStack_6c0 + 0x28);
      goto code_r0x01d0a1c4;
    }
    plVar2 = plStack_210;
    if (alStack_230 == plStack_210) goto code_r0x01d0a338;
code_r0x01d0a1dc:
    if (plVar2 != (long *)0x0) {
      pcVar7 = *(code **)(*plVar2 + 0x28);
      goto code_r0x01d0a340;
    }
  }
  if (alStack_260 == plStack_240) {
    pcVar7 = *(code **)(*plStack_240 + 0x20);
code_r0x01d0a370:
    (*pcVar7)();
  }
  else if (plStack_240 != (long *)0x0) {
    pcVar7 = *(code **)(*plStack_240 + 0x28);
    goto code_r0x01d0a370;
  }
  plVar2 = *(long **)(param_1 + 0xb7e0);
  if ((long *)(param_1 + 0xb7c0) == plVar2) {
    pcVar7 = *(code **)(*plVar2 + 0x20);
code_r0x01d0a3a8:
    (*pcVar7)();
  }
  else if (plVar2 != (long *)0x0) {
    pcVar7 = *(code **)(*plVar2 + 0x28);
    goto code_r0x01d0a3a8;
  }
  *(long *)(param_1 + 0xb7e0) = 0;
  ppuStack_6d0 = (undefined **)0x0;
  std::__ndk1::function<bool (Aska::Status)>::swap(std::__ndk1::function<bool (Aska::Status)>&)(&puStack_6f0,param_1 + 0xb7f0);
  if (&puStack_6f0 == ppuStack_6d0) {
    pcVar7 = *(code **)(*ppuStack_6d0 + 0x20);
code_r0x01d0a3ec:
    (*pcVar7)();
  }
  else if (ppuStack_6d0 != (undefined **)0x0) {
    pcVar7 = *(code **)(*ppuStack_6d0 + 0x28);
    goto code_r0x01d0a3ec;
  }
  plVar2 = *(long **)(param_1 + 0xb840);
  if ((long *)(param_1 + 0xb820) == plVar2) {
    pcVar7 = *(code **)(*plVar2 + 0x20);
code_r0x01d0a424:
    (*pcVar7)();
  }
  else if (plVar2 != (long *)0x0) {
    pcVar7 = *(code **)(*plVar2 + 0x28);
    goto code_r0x01d0a424;
  }
  *(long *)(param_1 + 0xb840) = 0;
  CMultiPlay3::Server_CreateRoomContdition(Aska::Yayoi::MultiplayRPC::RoomCondition*, bool)(param_1,apuStack_270,
                  *(int *)(param_1 + 0xb728) - 2U < 7 && (*(int *)(param_1 + 0xb728) - 2U & 1) == 0)
  ;
  puVar8 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar9 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar9 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar9 = *(long *)puVar8;
  }
  lVar9 = CParameterManager::pParameterUI() const(lVar9);
  CMultiPlay3::Server_CreatePlayerInfo(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo&, int)(lVar9,&puStack_6f0,*(undefined4 *)(lVar9 + 0x1b0));
  plVar2 = (long *)param_3[4];
  if (plVar2 == (long *)0x0) {
    pbStack_60 = (byte *)0x0;
  }
  else if (param_3 == plVar2) {
    pbStack_60 = &bStack_80;
    (**(code **)(*plVar2 + 0x18))(plVar2,&bStack_80);
  }
  else {
    pbStack_60 = (byte *)(**(code **)(*plVar2 + 0x10))();
  }
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&bStack_80,param_1 + 0xb760);
  if (&bStack_80 == pbStack_60) {
    pcVar7 = *(code **)(*(long *)pbStack_60 + 0x20);
code_r0x01d0a514:
    (*pcVar7)();
  }
  else if (pbStack_60 != (byte *)0x0) {
    pcVar7 = *(code **)(*(long *)pbStack_60 + 0x28);
    goto code_r0x01d0a514;
  }
  if (*pbVar5 != 0) {
    pbVar5 = (byte *)operator new(unsigned long)(0x678);
    *(undefined **)pbVar5 = &UNK_02b73a88;
    *(undefined **)(pbVar5 + 8) = param_1;
    memcpy(pbVar5 + 0x10,&puStack_6f0,0x480);
    memcpy(pbVar5 + 0x490,apuStack_270,0x1e8);
    uVar4 = 0;
    goto code_r0x01d0a690;
  }
  if ((*(int *)(param_1 + 0x1a8) != 0) &&
     (uVar6 = Framework::Cocos::CCocosScene::IsPlayAnimation(unsigned int) const(*(undefined8 *)(param_1 + 0x168)), (uVar6 & 1) != 0)) {
    Framework::Cocos::CCocosScene::StopAnimation(unsigned int, bool)(*(undefined8 *)(param_1 + 0x168),*(undefined4 *)(param_1 + 0x1a8),0);
  }
  bStack_80 = 0xc;
  uStack_70 = 0;
  uStack_78 = 0;
  uStack_7b = 0x6461;
  uStack_7f = 0x6f6c6572;
  uStack_79 = 0;
  puStack_720 = &UNK_02b73b08;
  puStack_718 = param_1;
  plStack_700 = (long *)&puStack_720;
  uVar1 = Framework::Cocos::CCocosScene::PlayAnimation(string const&, bool, std::__ndk1::function<void ()>)(*(undefined8 *)(param_1 + 0x168),&bStack_80,0,&puStack_720);
  *(undefined4 *)(param_1 + 0x1a8) = uVar1;
  if (&puStack_720 == (undefined **)plStack_700) {
    pcVar7 = *(code **)(*plStack_700 + 0x20);
code_r0x01d0a610:
    (*pcVar7)();
  }
  else if (plStack_700 != (long *)0x0) {
    pcVar7 = *(code **)(*plStack_700 + 0x28);
    goto code_r0x01d0a610;
  }
  if ((bStack_80 & 1) != 0) {
    Framework::CAssignedMemoryManagerForSTLAllocator::Free(void*)(uStack_70);
  }
  if (param_1[0xb9c1] == '\0') {
    pbVar5 = (byte *)operator new(unsigned long)(0x678);
    puVar8 = &UNK_02b73bf8;
  }
  else {
    pbVar5 = (byte *)operator new(unsigned long)(0x678);
    puVar8 = &UNK_02b73b78;
  }
  *(undefined **)pbVar5 = puVar8 + 0x10;
  *(undefined **)(pbVar5 + 8) = param_1;
  memcpy(pbVar5 + 0x10,&puStack_6f0,0x480);
  memcpy(pbVar5 + 0x490,apuStack_270,0x1e8);
  uVar4 = 1;
code_r0x01d0a690:
  pbStack_60 = pbVar5;
  CMultiPlay3::RegistCall(std::__ndk1::function<bool ()> const&, bool, unsigned int)(param_1,&bStack_80,uVar4);
  if (&bStack_80 == pbStack_60) {
    pcVar7 = *(code **)(*(long *)pbStack_60 + 0x20);
  }
  else {
    if (pbStack_60 == (byte *)0x0) {
      return;
    }
    pcVar7 = *(code **)(*(long *)pbStack_60 + 0x28);
  }
  (*pcVar7)();
  return;
}

// ==== undefined CMultiPlay3::Server_UpdateRoom(std::__ndk1::function<void ()>)
// _ZN11CMultiPlay317Server_UpdateRoomENSt6__ndk18functionIFvvEEE @ 01d0a6e0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN11CMultiPlay317Server_UpdateRoomENSt6__ndk18functionIFvvEEE(long *param_1,long *param_2)

{
  float *pfVar1;
  undefined *puVar2;
  ulong uVar3;
  long *plVar4;
  long *plVar5;
  code *pcVar6;
  float fVar7;
  float fVar8;
  undefined *puStack_70;
  long *plStack_68;
  long *plStack_50;
  
  if (((long *)param_1[0x38] != (long *)0x0) &&
     (uVar3 = (**(code **)(*(long *)param_1[0x38] + 0x80))(), (uVar3 & 1) != 0)) {
    return;
  }
  puVar2 = PTR__ZN9Framework10TSingletonI14CDialogManagerE11m_pInstanceE_02cc3e40;
  uVar3 = CDialogManager::IsOpen() const(*(undefined8 *)
                           PTR__ZN9Framework10TSingletonI14CDialogManagerE11m_pInstanceE_02cc3e40);
  if ((uVar3 & 1) != 0) {
    return;
  }
  if ((int)param_1[0x32] != 0) {
    return;
  }
  if (param_1[0x16ea] != 0) {
    return;
  }
  plVar5 = param_1 + 0x16f6;
  if ((long *)*plVar5 != (long *)0x0) {
    (**(code **)(*(long *)*plVar5 + 0x30))();
    plVar4 = (long *)*plVar5;
    if (param_1 + 0x16f2 == plVar4) {
      pcVar6 = *(code **)(*plVar4 + 0x20);
    }
    else {
      if (plVar4 == (long *)0x0) goto code_r0x01d0a7e8;
      pcVar6 = *(code **)(*plVar4 + 0x28);
    }
    (*pcVar6)();
code_r0x01d0a7e8:
    *plVar5 = 0;
    return;
  }
  fVar7 = (float)(**(code **)**(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460)
                           (*(undefined8 **)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460,0);
  pfVar1 = (float *)(param_1 + 0x1721);
  fVar8 = *pfVar1 + fVar7 * _UNK_027e51a0;
  *pfVar1 = fVar8;
  fVar7 = _UNK_027f692c;
  if (*(char *)((long)param_1 + 0xb93d) != '\0') {
    fVar7 = _UNK_027edb38;
  }
  if (fVar7 < fVar8) {
    *(undefined1 *)((long)param_1 + 0xb93c) = 1;
  }
  if (*(char *)((long)param_1 + 0xb93c) == '\0') {
    return;
  }
  *(char *)((long)param_1 + 0xb93d) = '\x01';
  puStack_70 = &UNK_02b734d8;
  plStack_68 = param_1;
  plStack_50 = (long *)&puStack_70;
  std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short, signed char, unsigned long)>::swap(std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short, signed char, unsigned long)>&)(&puStack_70,param_1[0x37] + 0x1d0);
  if (&puStack_70 == (undefined **)plStack_50) {
    pcVar6 = *(code **)(*plStack_50 + 0x20);
code_r0x01d0a870:
    (*pcVar6)();
  }
  else if (plStack_50 != (long *)0x0) {
    pcVar6 = *(code **)(*plStack_50 + 0x28);
    goto code_r0x01d0a870;
  }
  CMultiPlay3::RegistErrorRoomUpdate()(param_1);
  plVar5 = (long *)param_2[4];
  if (plVar5 == (long *)0x0) {
    plStack_50 = (long *)0x0;
  }
  else if (param_2 == plVar5) {
    plStack_50 = (long *)&puStack_70;
    (**(code **)(*plVar5 + 0x18))(plVar5,&puStack_70);
  }
  else {
    plStack_50 = (long *)(**(code **)(*plVar5 + 0x10))();
  }
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,param_1 + 0x16ec);
  if (&puStack_70 == (undefined **)plStack_50) {
    pcVar6 = *(code **)(*plStack_50 + 0x20);
code_r0x01d0a8fc:
    (*pcVar6)();
  }
  else if (plStack_50 != (long *)0x0) {
    pcVar6 = *(code **)(*plStack_50 + 0x28);
    goto code_r0x01d0a8fc;
  }
  puStack_70 = &UNK_02b73568;
  plStack_68 = param_1;
  plStack_50 = (long *)&puStack_70;
  CMultiPlay3::RegistCall(std::__ndk1::function<bool ()> const&, bool, unsigned int)(param_1,&puStack_70,0);
  if (&puStack_70 == (undefined **)plStack_50) {
    pcVar6 = *(code **)(*plStack_50 + 0x20);
  }
  else {
    if (plStack_50 == (long *)0x0) goto code_r0x01d0a950;
    pcVar6 = *(code **)(*plStack_50 + 0x28);
  }
  (*pcVar6)();
code_r0x01d0a950:
  if (((*(char *)((long)param_1 + 0xb94a) != '\0') && ((int)param_1[0x32] == 0)) &&
     (uVar3 = CDialogManager::IsOpen() const(*(undefined8 *)puVar2), (uVar3 & 1) == 0)) {
    (**(code **)(*param_1 + 0x118))(param_1);
  }
  *pfVar1 = 0.0;
  *(char *)((long)param_1 + 0xb93c) = '\0';
  return;
}

// ==== undefined CMultiPlay3::Server_UpdateRoomOne(std::__ndk1::function<void ()>)
// _ZN11CMultiPlay320Server_UpdateRoomOneENSt6__ndk18functionIFvvEEE @ 01d0aad8

void _ZN11CMultiPlay320Server_UpdateRoomOneENSt6__ndk18functionIFvvEEE(long param_1,long *param_2)

{
  long *plVar1;
  code *pcVar2;
  undefined *puStack_50;
  long lStack_48;
  long *plStack_30;
  
  plStack_30 = (long *)&puStack_50;
  *(undefined1 *)(param_1 + 0xb93d) = 1;
  puStack_50 = &UNK_02b735e8;
  lStack_48 = param_1;
  std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short, signed char, unsigned long)>::swap(std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short, signed char, unsigned long)>&)(&puStack_50,*(long *)(param_1 + 0x1b8) + 0x1d0);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar2 = *(code **)(*plStack_30 + 0x20);
code_r0x01d0ab44:
    (*pcVar2)();
  }
  else if (plStack_30 != (long *)0x0) {
    pcVar2 = *(code **)(*plStack_30 + 0x28);
    goto code_r0x01d0ab44;
  }
  CMultiPlay3::RegistErrorRoomUpdate()(param_1);
  plVar1 = (long *)param_2[4];
  if (plVar1 == (long *)0x0) {
    plStack_30 = (long *)0x0;
  }
  else if (param_2 == plVar1) {
    plStack_30 = (long *)&puStack_50;
    (**(code **)(*plVar1 + 0x18))(plVar1,&puStack_50);
  }
  else {
    plStack_30 = (long *)(**(code **)(*plVar1 + 0x10))();
  }
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_50,param_1 + 0xb760);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar2 = *(code **)(*plStack_30 + 0x20);
code_r0x01d0abd0:
    (*pcVar2)();
  }
  else if (plStack_30 != (long *)0x0) {
    pcVar2 = *(code **)(*plStack_30 + 0x28);
    goto code_r0x01d0abd0;
  }
  puStack_50 = &UNK_02b73668;
  lStack_48 = param_1;
  plStack_30 = (long *)&puStack_50;
  CMultiPlay3::RegistCall(std::__ndk1::function<bool ()> const&, bool, unsigned int)(param_1,&puStack_50,1);
  if (&puStack_50 == (undefined **)plStack_30) {
    pcVar2 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x01d0ac24;
    pcVar2 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar2)();
code_r0x01d0ac24:
  *(undefined4 *)(param_1 + 0xb908) = 0;
  *(undefined1 *)(param_1 + 0xb93c) = 0;
  return;
}

// ==== undefined CMultiPlay3::Server_SearchRoom(std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,Framework::CSTLAllocator<char,Framework::CSTLStringAllocatorInf>> const &,std::__ndk1::function<void ()>,std::__ndk1::function<void ()>,std::__ndk1::function<void ()>)
// _ZN11CMultiPlay317Server_SearchRoomERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEENS0_8functionIFvvEEESD_SD_ @ 01d0ac44

void _ZN11CMultiPlay317Server_SearchRoomERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEENS0_8functionIFvvEEESD_SD_
               (undefined *param_1,byte *param_2,long *param_3,long *param_4,long *param_5)

{
  undefined *puVar1;
  long *plVar2;
  long lVar3;
  ulong uVar4;
  code *pcVar5;
  byte *pbVar6;
  long lVar7;
  undefined *puStack_6e0;
  undefined *puStack_6d8;
  long alStack_6d0 [2];
  long *plStack_6c0;
  long *plStack_6b0;
  long alStack_6a0 [4];
  long *plStack_680;
  undefined *apuStack_260 [2];
  long alStack_250 [4];
  long *plStack_230;
  long alStack_220 [4];
  long *plStack_200;
  undefined1 auStack_112 [162];
  long alStack_70 [4];
  long *plStack_50;
  
  plStack_6c0 = (long *)&puStack_6e0;
  plVar2 = (long *)param_5[4];
  if (plVar2 == (long *)0x0) {
    plStack_6c0 = (long *)0x0;
  }
  else if (param_5 == plVar2) {
    (**(code **)(*plVar2 + 0x18))(plVar2,&puStack_6e0);
  }
  else {
    plStack_6c0 = (long *)(**(code **)(*plVar2 + 0x10))();
  }
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_6e0,param_1 + 0xb760);
  if (&puStack_6e0 == (undefined **)plStack_6c0) {
    pcVar5 = *(code **)(*plStack_6c0 + 0x20);
code_r0x01d0ace8:
    (*pcVar5)();
  }
  else if (plStack_6c0 != (long *)0x0) {
    pcVar5 = *(code **)(*plStack_6c0 + 0x28);
    goto code_r0x01d0ace8;
  }
  param_1[0xb942] = 0;
  puStack_6e0 = &UNK_02b72d98;
  puStack_6d8 = param_1;
  plStack_6c0 = (long *)&puStack_6e0;
  std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short)>::swap(std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short)>&)(&puStack_6e0,*(long *)(param_1 + 0x1b8) + 0x200);
  if (&puStack_6e0 == (undefined **)plStack_6c0) {
    pcVar5 = *(code **)(*plStack_6c0 + 0x20);
code_r0x01d0ad40:
    (*pcVar5)();
  }
  else if (plStack_6c0 != (long *)0x0) {
    pcVar5 = *(code **)(*plStack_6c0 + 0x28);
    goto code_r0x01d0ad40;
  }
  plVar2 = (long *)param_3[4];
  apuStack_260[0] = param_1;
  if (plVar2 == (long *)0x0) {
    plStack_230 = (long *)0x0;
    plVar2 = (long *)param_4[4];
joined_r0x01d0ad94:
    if (plVar2 != (long *)0x0) goto code_r0x01d0ad70;
code_r0x01d0ad98:
    plStack_200 = (long *)0x0;
  }
  else {
    if (param_3 == plVar2) {
      plStack_230 = alStack_250;
      (**(code **)(*plVar2 + 0x18))();
      plVar2 = (long *)param_4[4];
      goto joined_r0x01d0ad94;
    }
    plStack_230 = (long *)(**(code **)(*plVar2 + 0x10))();
    plVar2 = (long *)param_4[4];
    if (plVar2 == (long *)0x0) goto code_r0x01d0ad98;
code_r0x01d0ad70:
    if (param_4 == plVar2) {
      plStack_200 = alStack_220;
      (**(code **)(*plVar2 + 0x18))();
    }
    else {
      plStack_200 = (long *)(**(code **)(*plVar2 + 0x10))();
    }
  }
  lVar7 = *(long *)(param_1 + 0x1b8);
  puStack_6e0 = apuStack_260[0];
  if (plStack_230 == (long *)0x0) {
    plStack_6b0 = (long *)0x0;
joined_r0x01d0ae44:
    if (plStack_200 != (long *)0x0) goto code_r0x01d0ae18;
code_r0x01d0ae48:
    plStack_680 = (long *)0x0;
  }
  else {
    if (alStack_250 == plStack_230) {
      plStack_6b0 = alStack_6d0;
      (**(code **)(*plStack_230 + 0x18))();
      goto joined_r0x01d0ae44;
    }
    plStack_6b0 = (long *)(**(code **)(*plStack_230 + 0x10))();
    if (plStack_200 == (long *)0x0) goto code_r0x01d0ae48;
code_r0x01d0ae18:
    if (alStack_220 == plStack_200) {
      plStack_680 = alStack_6a0;
      (**(code **)(*plStack_200 + 0x18))();
    }
    else {
      plStack_680 = (long *)(**(code **)(*plStack_200 + 0x10))();
    }
  }
  plStack_50 = (long *)0x0;
  plVar2 = (long *)operator new(unsigned long)(0x80);
  *plVar2 = (long)&UNK_02b73c88;
  plVar2[2] = (long)puStack_6e0;
  if (plStack_6b0 == (long *)0x0) {
    plVar2[8] = 0;
joined_r0x01d0af14:
    if (plStack_680 != (long *)0x0) goto code_r0x01d0aee8;
code_r0x01d0af18:
    plVar2[0xe] = 0;
  }
  else {
    if (alStack_6d0 == plStack_6b0) {
      plVar2[8] = (long)(plVar2 + 4);
      (**(code **)(*plStack_6b0 + 0x18))();
      goto joined_r0x01d0af14;
    }
    lVar3 = (**(code **)(*plStack_6b0 + 0x10))();
    plVar2[8] = lVar3;
    if (plStack_680 == (long *)0x0) goto code_r0x01d0af18;
code_r0x01d0aee8:
    if (alStack_6a0 == plStack_680) {
      plVar2[0xe] = (long)(plVar2 + 10);
      (**(code **)(*plStack_680 + 0x18))();
    }
    else {
      lVar3 = (**(code **)(*plStack_680 + 0x10))();
      plVar2[0xe] = lVar3;
    }
  }
  plStack_50 = plVar2;
  std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::RoomInfo*, unsigned int&)>::swap(std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::RoomInfo*, unsigned int&)>&)(alStack_70,lVar7 + 0x80);
  if (alStack_70 == plStack_50) {
    pcVar5 = *(code **)(*plStack_50 + 0x20);
code_r0x01d0af8c:
    (*pcVar5)();
  }
  else if (plStack_50 != (long *)0x0) {
    pcVar5 = *(code **)(*plStack_50 + 0x28);
    goto code_r0x01d0af8c;
  }
  if (alStack_6a0 == plStack_680) {
    pcVar5 = *(code **)(*plStack_680 + 0x20);
code_r0x01d0afbc:
    (*pcVar5)();
  }
  else if (plStack_680 != (long *)0x0) {
    pcVar5 = *(code **)(*plStack_680 + 0x28);
    goto code_r0x01d0afbc;
  }
  if (alStack_6d0 == plStack_6b0) {
    pcVar5 = *(code **)(*plStack_6b0 + 0x20);
code_r0x01d0afec:
    (*pcVar5)();
  }
  else if (plStack_6b0 != (long *)0x0) {
    pcVar5 = *(code **)(*plStack_6b0 + 0x28);
    goto code_r0x01d0afec;
  }
  if (alStack_220 == plStack_200) {
    pcVar5 = *(code **)(*plStack_200 + 0x20);
code_r0x01d0b01c:
    (*pcVar5)();
  }
  else if (plStack_200 != (long *)0x0) {
    pcVar5 = *(code **)(*plStack_200 + 0x28);
    goto code_r0x01d0b01c;
  }
  if (alStack_250 == plStack_230) {
    pcVar5 = *(code **)(*plStack_230 + 0x20);
code_r0x01d0b04c:
    (*pcVar5)();
  }
  else if (plStack_230 != (long *)0x0) {
    pcVar5 = *(code **)(*plStack_230 + 0x28);
    goto code_r0x01d0b04c;
  }
  plVar2 = *(long **)(param_1 + 0xb7e0);
  if ((long *)(param_1 + 0xb7c0) == plVar2) {
    pcVar5 = *(code **)(*plVar2 + 0x20);
code_r0x01d0b084:
    (*pcVar5)();
  }
  else if (plVar2 != (long *)0x0) {
    pcVar5 = *(code **)(*plVar2 + 0x28);
    goto code_r0x01d0b084;
  }
  *(long *)(param_1 + 0xb7e0) = 0;
  plStack_6c0 = (long *)0x0;
  std::__ndk1::function<bool (Aska::Status)>::swap(std::__ndk1::function<bool (Aska::Status)>&)(&puStack_6e0,param_1 + 0xb7f0);
  if (&puStack_6e0 == (undefined **)plStack_6c0) {
    pcVar5 = *(code **)(*plStack_6c0 + 0x20);
code_r0x01d0b0c8:
    (*pcVar5)();
  }
  else if (plStack_6c0 != (long *)0x0) {
    pcVar5 = *(code **)(*plStack_6c0 + 0x28);
    goto code_r0x01d0b0c8;
  }
  plVar2 = *(long **)(param_1 + 0xb840);
  if ((long *)(param_1 + 0xb820) == plVar2) {
    pcVar5 = *(code **)(*plVar2 + 0x20);
  }
  else {
    if (plVar2 == (long *)0x0) goto code_r0x01d0b104;
    pcVar5 = *(code **)(*plVar2 + 0x28);
  }
  (*pcVar5)();
code_r0x01d0b104:
  *(long *)(param_1 + 0xb840) = 0;
  CMultiPlay3::Server_CreateRoomContdition(Aska::Yayoi::MultiplayRPC::RoomCondition*, bool)(param_1,apuStack_260,
                  *(int *)(param_1 + 0xb728) - 2U < 7 && (*(int *)(param_1 + 0xb728) - 2U & 1) == 0)
  ;
  pbVar6 = *(byte **)(param_2 + 0x10);
  if ((*param_2 & 1) == 0) {
    pbVar6 = param_2 + 1;
  }
  uVar4 = strlen(pbVar6);
  if (uVar4 < 0x20) {
    strcpy(auStack_112,pbVar6);
  }
  else {
    raise(5);
  }
  puVar1 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar7 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar7 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar7 = *(long *)puVar1;
  }
  lVar7 = CParameterManager::pParameterUI() const(lVar7);
  CMultiPlay3::Server_CreatePlayerInfo(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo&, int)(lVar7,&puStack_6e0,*(undefined4 *)(lVar7 + 0x1b0));
  plVar2 = (long *)operator new(unsigned long)(0x678);
  *plVar2 = (long)&UNK_02b73d08;
  plVar2[1] = (long)param_1;
  memcpy(plVar2 + 2,&puStack_6e0,0x480);
  memcpy(plVar2 + 0x92,apuStack_260,0x1e8);
  plStack_50 = plVar2;
  CMultiPlay3::RegistCall(std::__ndk1::function<bool ()> const&, bool, unsigned int)(param_1,alStack_70,1);
  if (alStack_70 == plStack_50) {
    pcVar5 = *(code **)(*plStack_50 + 0x20);
  }
  else {
    if (plStack_50 == (long *)0x0) {
      return;
    }
    pcVar5 = *(code **)(*plStack_50 + 0x28);
  }
  (*pcVar5)();
  return;
}

// ==== undefined CMultiPlay3::Server_JoinRoom(unsigned int,unsigned int,std::__ndk1::function<void ()>,std::__ndk1::function<void ()>)
// _ZN11CMultiPlay315Server_JoinRoomEjjNSt6__ndk18functionIFvvEEES3_ @ 01d0b240

void _ZN11CMultiPlay315Server_JoinRoomEjjNSt6__ndk18functionIFvvEEES3_
               (undefined *param_1,uint param_2,int param_3,long *param_4,long *param_5)

{
  long *plVar1;
  undefined8 uVar2;
  long lVar3;
  long *plVar4;
  undefined **ppuVar5;
  ulong uVar6;
  undefined4 uVar7;
  code *pcVar8;
  ulong uVar9;
  long lVar10;
  undefined *puVar11;
  long alStack_570 [4];
  long *plStack_550;
  long alStack_540 [4];
  long *plStack_520;
  int iStack_4d8;
  undefined *puStack_c0;
  undefined *puStack_b8;
  long alStack_b0 [2];
  undefined **ppuStack_a0;
  long *plStack_90;
  long alStack_80 [4];
  long *plStack_60;
  
  plVar1 = (long *)param_5[4];
  uVar9 = (ulong)param_2;
  if (plVar1 == (long *)0x0) {
    plStack_520 = (long *)0x0;
  }
  else if (param_5 == plVar1) {
    plStack_520 = alStack_540;
    (**(code **)(*plVar1 + 0x18))(plVar1,alStack_540);
  }
  else {
    plStack_520 = (long *)(**(code **)(*plVar1 + 0x10))();
  }
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(alStack_540,param_1 + 0xb760);
  if (alStack_540 == plStack_520) {
    pcVar8 = *(code **)(*plStack_520 + 0x20);
code_r0x01d0b2e8:
    (*pcVar8)();
  }
  else if (plStack_520 != (long *)0x0) {
    pcVar8 = *(code **)(*plStack_520 + 0x28);
    goto code_r0x01d0b2e8;
  }
  *(undefined2 *)(param_1 + 0xb949) = 0x100;
  uVar2 = CUIUtility::GetButton(Framework::Cocos::CCocosNode*, char const*)(*(undefined8 *)(param_1 + 0x160),&UNK_028ff192/*"Button_start"*/);
  CUIUtility::SetButtonStateOpacity(Framework::Cocos::CCocosNode*, bool)(uVar2,1);
  uVar2 = CUIUtility::GetButton(Framework::Cocos::CCocosNode*, char const*)(*(undefined8 *)(param_1 + 0x160),&UNK_028ff427/*"Button_party"*/);
  CUIUtility::SetButtonStateOpacity(Framework::Cocos::CCocosNode*, bool)(uVar2,1);
  uVar2 = CUIUtility::GetButton(Framework::Cocos::CCocosNode*, char const*)(*(undefined8 *)(param_1 + 0x160),&UNK_028db1fd/*"list/plate/Button_2"*/);
  CUIUtility::SetButtonStateOpacity(Framework::Cocos::CCocosNode*, bool)(uVar2,1);
  lVar10 = *(long *)(param_1 + 0x1d8);
  uVar6 = (*(long *)(param_1 + 0x1e0) - lVar10 >> 3) * 0x1ef24c80742dd08b;
  *(undefined8 *)(param_1 + 0xb8e8) = 0;
  *(undefined8 *)(param_1 + 0xb8e0) = 0;
  if (uVar6 < uVar9 || uVar6 - uVar9 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dc536/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/STL_Vector.h"*/,0x58,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,uVar9);
    lVar10 = *(long *)(param_1 + 0x1d8);
  }
  CMultiPlay3::RoomInfo2RoomData(Aska::Yayoi::MultiplayRPC::RoomInfo const&, bool)(param_1,lVar10 + uVar9 * 0xb918,0);
  puVar11 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar3 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar11;
  }
  lVar3 = CParameterManager::pParameterUI() const(lVar3);
  *(undefined4 *)(lVar3 + 0x1a0) = *(undefined4 *)(lVar10 + uVar9 * 0xb918 + 0x24c);
  lVar3 = *(long *)puVar11;
  if (lVar3 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar3 = *(long *)puVar11;
  }
  lVar3 = CParameterManager::pParameterUI() const(lVar3);
  CMultiPlay3::Server_CreatePlayerInfo(Aska::Yayoi::MultiplayRPC::PlayerDetailInfo&, int)(lVar3,alStack_540,*(undefined4 *)(lVar3 + 0x1b0));
  param_1[0xb945] = 0;
  param_1[0xb941] = 0;
  puStack_c0 = &UNK_02b74188;
  puStack_b8 = param_1;
  ppuStack_a0 = &puStack_c0;
  std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::ExitType)>::swap(std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::ExitType)>&)(&puStack_c0,*(long *)(param_1 + 0x1b8) + 0x140);
  if (&puStack_c0 == ppuStack_a0) {
    pcVar8 = *(code **)(*ppuStack_a0 + 0x20);
code_r0x01d0b47c:
    (*pcVar8)();
  }
  else if (ppuStack_a0 != (undefined **)0x0) {
    pcVar8 = *(code **)(*ppuStack_a0 + 0x28);
    goto code_r0x01d0b47c;
  }
  if (param_3 - 1U < 3) {
    uVar7 = *(undefined4 *)(lVar10 + uVar9 * 0xb918 + (ulong)(param_3 - 1U) * 4 + 600);
  }
  else {
    uVar7 = 0;
  }
  *(undefined4 *)(param_1 + 0xb938) = uVar7;
  *(int *)(param_1 + 0xb928) = param_3;
  plVar1 = (long *)param_4[4];
  iStack_4d8 = param_3;
  if (plVar1 == (long *)0x0) {
    plStack_550 = (long *)0x0;
  }
  else if (param_4 == plVar1) {
    plStack_550 = alStack_570;
    (**(code **)(*plVar1 + 0x18))();
  }
  else {
    plStack_550 = (long *)(**(code **)(*plVar1 + 0x10))();
  }
  lVar10 = *(long *)(param_1 + 0x1b8);
  puVar11 = param_1;
  puStack_c0 = param_1;
  if (plStack_550 == (long *)0x0) {
    plStack_90 = (long *)0x0;
  }
  else if (alStack_570 == plStack_550) {
    plStack_90 = alStack_b0;
    (**(code **)(*plStack_550 + 0x18))();
    puVar11 = puStack_c0;
  }
  else {
    plStack_90 = (long *)(**(code **)(*plStack_550 + 0x10))();
  }
  plVar1 = plStack_90;
  plStack_60 = (long *)0x0;
  plVar4 = (long *)operator new(unsigned long)(0x50);
  *plVar4 = (long)&UNK_02b73d88;
  plVar4[2] = (long)puVar11;
  if (plVar1 == (long *)0x0) {
    plVar4[8] = 0;
  }
  else if (alStack_b0 == plVar1) {
    plVar4[8] = (long)(plVar4 + 4);
    (**(code **)(*plVar1 + 0x18))(plVar1);
  }
  else {
    lVar3 = (**(code **)(*plVar1 + 0x10))(plVar1);
    plVar4[8] = lVar3;
  }
  plStack_60 = plVar4;
  std::__ndk1::function<void (int, Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short)>::swap(std::__ndk1::function<void (int, Aska::Yayoi::MultiplayRPC::PlayerDetailInfo*, unsigned short)>&)(alStack_80,lVar10 + 0xe0);
  if (alStack_80 == plStack_60) {
    pcVar8 = *(code **)(*plStack_60 + 0x20);
code_r0x01d0b614:
    (*pcVar8)();
  }
  else if (plStack_60 != (long *)0x0) {
    pcVar8 = *(code **)(*plStack_60 + 0x28);
    goto code_r0x01d0b614;
  }
  if (alStack_b0 == plStack_90) {
    pcVar8 = *(code **)(*plStack_90 + 0x20);
code_r0x01d0b644:
    (*pcVar8)();
  }
  else if (plStack_90 != (long *)0x0) {
    pcVar8 = *(code **)(*plStack_90 + 0x28);
    goto code_r0x01d0b644;
  }
  if (alStack_570 == plStack_550) {
    pcVar8 = *(code **)(*plStack_550 + 0x20);
code_r0x01d0b674:
    (*pcVar8)();
  }
  else if (plStack_550 != (long *)0x0) {
    pcVar8 = *(code **)(*plStack_550 + 0x28);
    goto code_r0x01d0b674;
  }
  puStack_c0 = &UNK_02b73e08;
  puStack_b8 = param_1;
  ppuStack_a0 = &puStack_c0;
  std::__ndk1::function<bool (Aska::Status)>::swap(std::__ndk1::function<bool (Aska::Status)>&)(&puStack_c0,param_1 + 0xb7c0);
  if (&puStack_c0 == ppuStack_a0) {
    pcVar8 = *(code **)(*ppuStack_a0 + 0x20);
code_r0x01d0b6cc:
    (*pcVar8)();
  }
  else if (ppuStack_a0 != (undefined **)0x0) {
    pcVar8 = *(code **)(*ppuStack_a0 + 0x28);
    goto code_r0x01d0b6cc;
  }
  plVar1 = *(long **)(param_1 + 0xb7e0);
  if (plVar1 == (long *)0x0) {
    ppuStack_a0 = (undefined **)0x0;
  }
  else if ((long *)(param_1 + 0xb7c0) == plVar1) {
    ppuStack_a0 = &puStack_c0;
    (**(code **)(*plVar1 + 0x18))(plVar1,&puStack_c0);
  }
  else {
    ppuStack_a0 = (undefined **)(**(code **)(*plVar1 + 0x10))();
  }
  std::__ndk1::function<bool (Aska::Status)>::swap(std::__ndk1::function<bool (Aska::Status)>&)(&puStack_c0,param_1 + 0xb7f0);
  if (&puStack_c0 == ppuStack_a0) {
    pcVar8 = *(code **)(*ppuStack_a0 + 0x20);
code_r0x01d0b754:
    (*pcVar8)();
  }
  else if (ppuStack_a0 != (undefined **)0x0) {
    pcVar8 = *(code **)(*ppuStack_a0 + 0x28);
    goto code_r0x01d0b754;
  }
  puStack_c0 = &UNK_02b73e88;
  puStack_b8 = param_1;
  ppuStack_a0 = &puStack_c0;
  std::__ndk1::function<bool ()>::swap(std::__ndk1::function<bool ()>&)(&puStack_c0,param_1 + 0xb820);
  if (&puStack_c0 == ppuStack_a0) {
    pcVar8 = *(code **)(*ppuStack_a0 + 0x20);
  }
  else {
    if (ppuStack_a0 == (undefined **)0x0) goto code_r0x01d0b7ac;
    pcVar8 = *(code **)(*ppuStack_a0 + 0x28);
  }
  (*pcVar8)();
code_r0x01d0b7ac:
  ppuVar5 = (undefined **)operator new(unsigned long)(0x498);
  *ppuVar5 = &UNK_02b73f88;
  ppuVar5[1] = param_1;
  memcpy(ppuVar5 + 2,alStack_540,0x480);
  *(uint *)(ppuVar5 + 0x92) = param_2;
  ppuStack_a0 = ppuVar5;
  CMultiPlay3::RegistCall(std::__ndk1::function<bool ()> const&, bool, unsigned int)(param_1,&puStack_c0,1);
  if (&puStack_c0 == ppuStack_a0) {
    pcVar8 = *(code **)(*ppuStack_a0 + 0x20);
  }
  else {
    if (ppuStack_a0 == (undefined **)0x0) {
      return;
    }
    pcVar8 = *(code **)(*ppuStack_a0 + 0x28);
  }
  (*pcVar8)();
  return;
}

// ==== undefined CMultiPlay3::Server_RegistExitPush(bool)
// _ZN11CMultiPlay321Server_RegistExitPushEb @ 01d0b838

void _ZN11CMultiPlay321Server_RegistExitPushEb(long param_1,ulong param_2)

{
  long *plVar1;
  code *pcVar2;
  long lVar3;
  undefined *puStack_40;
  long lStack_38;
  long *plStack_20;
  
  plStack_20 = (long *)&puStack_40;
  *(undefined1 *)(param_1 + 0xb945) = 0;
  *(undefined1 *)(param_1 + 0xb941) = 0;
  if ((param_2 & 1) != 0) {
    puStack_40 = &UNK_02b74188;
    lStack_38 = param_1;
    std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::ExitType)>::swap(std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::ExitType)>&)(&puStack_40,*(long *)(param_1 + 0x1b8) + 0x140);
    if (&puStack_40 == (undefined **)plStack_20) {
      (**(code **)(*plStack_20 + 0x20))();
      return;
    }
    if (plStack_20 == (long *)0x0) {
      return;
    }
    (**(code **)(*plStack_20 + 0x28))();
    return;
  }
  lVar3 = *(long *)(param_1 + 0x1b8);
  plVar1 = *(long **)(lVar3 + 0x160);
  if ((long *)(lVar3 + 0x140) == plVar1) {
    pcVar2 = *(code **)(*plVar1 + 0x20);
  }
  else {
    if (plVar1 == (long *)0x0) goto code_r0x01d0b8dc;
    pcVar2 = *(code **)(*plVar1 + 0x28);
  }
  (*pcVar2)();
code_r0x01d0b8dc:
  *(undefined8 *)(lVar3 + 0x160) = 0;
  return;
}

// ==== undefined CMultiPlay3::Server_ExitRoom(bool,std::__ndk1::function<void ()>,std::__ndk1::function<void ()>)
// _ZN11CMultiPlay315Server_ExitRoomEbNSt6__ndk18functionIFvvEEES3_ @ 01d0b8ec

void _ZN11CMultiPlay315Server_ExitRoomEbNSt6__ndk18functionIFvvEEES3_
               (undefined *param_1,byte param_2,long *param_3,long *param_4)

{
  long *plVar1;
  long lVar2;
  undefined **ppuVar3;
  code *pcVar4;
  long alStack_1a0 [4];
  long *plStack_180;
  undefined *puStack_170;
  undefined *apuStack_160 [4];
  undefined **ppuStack_140;
  long alStack_130 [4];
  long *plStack_110;
  byte bStack_100;
  undefined *puStack_f0;
  undefined *puStack_e8;
  long alStack_e0 [2];
  undefined **ppuStack_d0;
  long *plStack_c0;
  long alStack_b0 [4];
  long *plStack_90;
  byte bStack_80;
  long alStack_70 [4];
  long *plStack_50;
  
  if (*(long *)(param_1 + 0xb750) == 0) {
    plVar1 = (long *)param_4[4];
    if (plVar1 == (long *)0x0) {
      ppuStack_d0 = (undefined **)0x0;
    }
    else if (param_4 == plVar1) {
      ppuStack_d0 = &puStack_f0;
      (**(code **)(*plVar1 + 0x18))(plVar1,&puStack_f0);
    }
    else {
      ppuStack_d0 = (undefined **)(**(code **)(*plVar1 + 0x10))();
    }
    std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_f0,param_1 + 0xb760);
    if (&puStack_f0 == ppuStack_d0) {
      pcVar4 = *(code **)(*ppuStack_d0 + 0x20);
code_r0x01d0bcb4:
      (*pcVar4)();
    }
    else if (ppuStack_d0 != (undefined **)0x0) {
      pcVar4 = *(code **)(*ppuStack_d0 + 0x28);
      goto code_r0x01d0bcb4;
    }
    plVar1 = (long *)param_3[4];
    if (plVar1 == (long *)0x0) {
      plStack_180 = (long *)0x0;
    }
    else if (param_3 == plVar1) {
      plStack_180 = alStack_1a0;
      (**(code **)(*plVar1 + 0x18))(plVar1,alStack_1a0);
    }
    else {
      plStack_180 = (long *)(**(code **)(*plVar1 + 0x10))();
    }
    CMultiPlay3::Server_RegistExitRes(bool, std::__ndk1::function<void ()>)(param_1,1,alStack_1a0);
    if (alStack_1a0 == plStack_180) {
      pcVar4 = *(code **)(*plStack_180 + 0x20);
code_r0x01d0bd34:
      (*pcVar4)();
    }
    else if (plStack_180 != (long *)0x0) {
      pcVar4 = *(code **)(*plStack_180 + 0x28);
      goto code_r0x01d0bd34;
    }
    CMultiPlay3::RegistErrorAdExitRoom(bool, bool, std::__ndk1::function<void ()> const&)(param_1,param_2 & 1,1,param_3);
    puStack_f0 = &UNK_02b74088;
    puStack_e8 = param_1;
    ppuStack_d0 = &puStack_f0;
    CMultiPlay3::RegistCall(std::__ndk1::function<bool ()> const&, bool, unsigned int)(param_1,&puStack_f0,1);
    ppuVar3 = ppuStack_d0;
    if (&puStack_f0 != ppuStack_d0) goto code_r0x01d0bc50;
  }
  else {
    plVar1 = (long *)param_3[4];
    param_2 = param_2 & 1;
    puStack_170 = param_1;
    if (plVar1 == (long *)0x0) {
      ppuStack_140 = (undefined **)0x0;
      plVar1 = (long *)param_4[4];
joined_r0x01d0b988:
      if (plVar1 == (long *)0x0) goto code_r0x01d0b94c;
code_r0x01d0b98c:
      if (param_4 == plVar1) {
        plStack_110 = alStack_130;
        (**(code **)(*plVar1 + 0x18))();
      }
      else {
        plStack_110 = (long *)(**(code **)(*plVar1 + 0x10))();
      }
    }
    else {
      if (param_3 == plVar1) {
        ppuStack_140 = apuStack_160;
        (**(code **)(*plVar1 + 0x18))();
        plVar1 = (long *)param_4[4];
        goto joined_r0x01d0b988;
      }
      ppuStack_140 = (undefined **)(**(code **)(*plVar1 + 0x10))();
      plVar1 = (long *)param_4[4];
      if (plVar1 != (long *)0x0) goto code_r0x01d0b98c;
code_r0x01d0b94c:
      plStack_110 = (long *)0x0;
    }
    puStack_f0 = puStack_170;
    bStack_100 = param_2;
    if (ppuStack_140 == (undefined **)0x0) {
      plStack_c0 = (long *)0x0;
joined_r0x01d0ba34:
      if (plStack_110 == (long *)0x0) goto code_r0x01d0ba24;
code_r0x01d0ba38:
      if (alStack_130 == plStack_110) {
        plStack_90 = alStack_b0;
        (**(code **)(*plStack_110 + 0x18))();
      }
      else {
        plStack_90 = (long *)(**(code **)(*plStack_110 + 0x10))();
      }
    }
    else {
      if (apuStack_160 == ppuStack_140) {
        plStack_c0 = alStack_e0;
        (**(code **)(*ppuStack_140 + 0x18))();
        goto joined_r0x01d0ba34;
      }
      plStack_c0 = (long *)(**(code **)(*ppuStack_140 + 0x10))();
      if (plStack_110 != (long *)0x0) goto code_r0x01d0ba38;
code_r0x01d0ba24:
      plStack_90 = (long *)0x0;
    }
    plStack_50 = (long *)0x0;
    bStack_80 = bStack_100;
    plVar1 = (long *)operator new(unsigned long)(0x90);
    *plVar1 = (long)&UNK_02b74008;
    plVar1[2] = (long)puStack_f0;
    if (plStack_c0 == (long *)0x0) {
      plVar1[8] = 0;
joined_r0x01d0bb0c:
      if (plStack_90 == (long *)0x0) goto code_r0x01d0bafc;
code_r0x01d0bb10:
      if (alStack_b0 == plStack_90) {
        plVar1[0xe] = (long)(plVar1 + 10);
        (**(code **)(*plStack_90 + 0x18))();
      }
      else {
        lVar2 = (**(code **)(*plStack_90 + 0x10))();
        plVar1[0xe] = lVar2;
      }
    }
    else {
      if (alStack_e0 == plStack_c0) {
        plVar1[8] = (long)(plVar1 + 4);
        (**(code **)(*plStack_c0 + 0x18))();
        goto joined_r0x01d0bb0c;
      }
      lVar2 = (**(code **)(*plStack_c0 + 0x10))();
      plVar1[8] = lVar2;
      if (plStack_90 != (long *)0x0) goto code_r0x01d0bb10;
code_r0x01d0bafc:
      plVar1[0xe] = 0;
    }
    *(byte *)(plVar1 + 0x10) = bStack_80;
    plStack_50 = plVar1;
    std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(alStack_70,param_1 + 0xb790);
    if (alStack_70 == plStack_50) {
      pcVar4 = *(code **)(*plStack_50 + 0x20);
code_r0x01d0bba8:
      (*pcVar4)();
    }
    else if (plStack_50 != (long *)0x0) {
      pcVar4 = *(code **)(*plStack_50 + 0x28);
      goto code_r0x01d0bba8;
    }
    if (alStack_b0 == plStack_90) {
      pcVar4 = *(code **)(*plStack_90 + 0x20);
code_r0x01d0bbd8:
      (*pcVar4)();
    }
    else if (plStack_90 != (long *)0x0) {
      pcVar4 = *(code **)(*plStack_90 + 0x28);
      goto code_r0x01d0bbd8;
    }
    if (alStack_e0 == plStack_c0) {
      pcVar4 = *(code **)(*plStack_c0 + 0x20);
code_r0x01d0bc08:
      (*pcVar4)();
    }
    else if (plStack_c0 != (long *)0x0) {
      pcVar4 = *(code **)(*plStack_c0 + 0x28);
      goto code_r0x01d0bc08;
    }
    if (alStack_130 == plStack_110) {
      pcVar4 = *(code **)(*plStack_110 + 0x20);
code_r0x01d0bc38:
      (*pcVar4)();
    }
    else if (plStack_110 != (long *)0x0) {
      pcVar4 = *(code **)(*plStack_110 + 0x28);
      goto code_r0x01d0bc38;
    }
    ppuVar3 = ppuStack_140;
    if (apuStack_160 != ppuStack_140) {
code_r0x01d0bc50:
      if (ppuVar3 == (undefined **)0x0) {
        return;
      }
      pcVar4 = *(code **)(*ppuVar3 + 0x28);
      goto code_r0x01d0bd88;
    }
  }
  pcVar4 = *(code **)(*ppuVar3 + 0x20);
code_r0x01d0bd88:
  (*pcVar4)();
  return;
}

// ==== undefined CMultiPlay3::Server_RegistExitRes(bool,std::__ndk1::function<void ()>)
// _ZN11CMultiPlay320Server_RegistExitResEbNSt6__ndk18functionIFvvEEE @ 01d0bda4

void _ZN11CMultiPlay320Server_RegistExitResEbNSt6__ndk18functionIFvvEEE
               (long param_1,ulong param_2,long *param_3)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  code *pcVar5;
  long alStack_d0 [4];
  long *plStack_b0;
  long lStack_a0;
  long alStack_90 [4];
  long *plStack_70;
  long alStack_60 [4];
  long *plStack_40;
  
  if ((param_2 & 1) == 0) {
    *(undefined1 *)(param_1 + 0xb945) = 0;
    *(undefined1 *)(param_1 + 0xb941) = 0;
    lVar4 = *(long *)(param_1 + 0x1b8);
    plVar1 = *(long **)(lVar4 + 0x130);
    if ((long *)(lVar4 + 0x110) == plVar1) {
      pcVar5 = *(code **)(*plVar1 + 0x20);
    }
    else {
      if (plVar1 == (long *)0x0) goto code_r0x01d0be30;
      pcVar5 = *(code **)(*plVar1 + 0x28);
    }
    (*pcVar5)();
code_r0x01d0be30:
    *(undefined8 *)(lVar4 + 0x130) = 0;
    return;
  }
  plVar1 = (long *)param_3[4];
  if (plVar1 == (long *)0x0) {
    plStack_b0 = (long *)0x0;
  }
  else if (param_3 == plVar1) {
    plStack_b0 = alStack_d0;
    (**(code **)(*plVar1 + 0x18))();
  }
  else {
    plStack_b0 = (long *)(**(code **)(*plVar1 + 0x10))();
  }
  lVar4 = *(long *)(param_1 + 0x1b8);
  lStack_a0 = param_1;
  if (plStack_b0 == (long *)0x0) {
    plStack_70 = (long *)0x0;
  }
  else if (alStack_d0 == plStack_b0) {
    plStack_70 = alStack_90;
    (**(code **)(*plStack_b0 + 0x18))();
    param_1 = lStack_a0;
  }
  else {
    plStack_70 = (long *)(**(code **)(*plStack_b0 + 0x10))();
  }
  plVar1 = plStack_70;
  plStack_40 = (long *)0x0;
  plVar2 = (long *)operator new(unsigned long)(0x50);
  *plVar2 = (long)&UNK_02b74108;
  plVar2[2] = param_1;
  if (plVar1 == (long *)0x0) {
    plVar2[8] = 0;
  }
  else if (alStack_90 == plVar1) {
    plVar2[8] = (long)(plVar2 + 4);
    (**(code **)(*plVar1 + 0x18))(plVar1);
  }
  else {
    lVar3 = (**(code **)(*plVar1 + 0x10))(plVar1);
    plVar2[8] = lVar3;
  }
  plStack_40 = plVar2;
  std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::ExitType)>::swap(std::__ndk1::function<void (Aska::Yayoi::MultiplayRPC::ExitType)>&)(alStack_60,lVar4 + 0x110);
  if (alStack_60 == plStack_40) {
    pcVar5 = *(code **)(*plStack_40 + 0x20);
code_r0x01d0bf64:
    (*pcVar5)();
  }
  else if (plStack_40 != (long *)0x0) {
    pcVar5 = *(code **)(*plStack_40 + 0x28);
    goto code_r0x01d0bf64;
  }
  if (alStack_90 == plStack_70) {
    pcVar5 = *(code **)(*plStack_70 + 0x20);
  }
  else {
    if (plStack_70 == (long *)0x0) goto code_r0x01d0bf98;
    pcVar5 = *(code **)(*plStack_70 + 0x28);
  }
  (*pcVar5)();
code_r0x01d0bf98:
  if (alStack_d0 == plStack_b0) {
    pcVar5 = *(code **)(*plStack_b0 + 0x20);
  }
  else {
    if (plStack_b0 == (long *)0x0) {
      return;
    }
    pcVar5 = *(code **)(*plStack_b0 + 0x28);
  }
  (*pcVar5)();
  return;
}

// ==== undefined CMultiPlay3::Server_BanExitRoom(unsigned int,std::__ndk1::function<void ()>,std::__ndk1::function<void ()>)
// _ZN11CMultiPlay318Server_BanExitRoomEjNSt6__ndk18functionIFvvEEES3_ @ 01d0c380

void _ZN11CMultiPlay318Server_BanExitRoomEjNSt6__ndk18functionIFvvEEES3_
               (undefined *param_1,uint param_2,long *param_3,long *param_4)

{
  long *plVar1;
  long lVar2;
  code *pcVar3;
  long alStack_180 [4];
  long *plStack_160;
  undefined *puStack_150;
  undefined *puStack_148;
  long alStack_140 [2];
  undefined **ppuStack_130;
  long *plStack_120;
  long alStack_110 [4];
  long *plStack_f0;
  undefined *puStack_e0;
  undefined8 uStack_d8;
  ulong auStack_d0 [2];
  undefined **ppuStack_c0;
  ulong *puStack_b0;
  long alStack_a0 [4];
  long *plStack_80;
  long alStack_70 [4];
  long *plStack_50;
  
  if (*(long *)(param_1 + 0xb750) == 0) {
    plVar1 = (long *)param_4[4];
    if (plVar1 == (long *)0x0) {
      ppuStack_c0 = (undefined **)0x0;
    }
    else if (param_4 == plVar1) {
      ppuStack_c0 = &puStack_e0;
      (**(code **)(*plVar1 + 0x18))(plVar1,&puStack_e0);
    }
    else {
      ppuStack_c0 = (undefined **)(**(code **)(*plVar1 + 0x10))();
    }
    std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_e0,param_1 + 0xb760);
    if (&puStack_e0 == ppuStack_c0) {
      pcVar3 = *(code **)(*ppuStack_c0 + 0x20);
code_r0x01d0c758:
      (*pcVar3)();
    }
    else if (ppuStack_c0 != (undefined **)0x0) {
      pcVar3 = *(code **)(*ppuStack_c0 + 0x28);
      goto code_r0x01d0c758;
    }
    plVar1 = (long *)param_3[4];
    if (plVar1 == (long *)0x0) {
      plStack_160 = (long *)0x0;
    }
    else if (param_3 == plVar1) {
      plStack_160 = alStack_180;
      (**(code **)(*plVar1 + 0x18))(plVar1,alStack_180);
    }
    else {
      plStack_160 = (long *)(**(code **)(*plVar1 + 0x10))();
    }
    CMultiPlay3::Server_RegistExitRes(bool, std::__ndk1::function<void ()>)(param_1,1,alStack_180);
    if (alStack_180 == plStack_160) {
      pcVar3 = *(code **)(*plStack_160 + 0x20);
code_r0x01d0c7d8:
      (*pcVar3)();
    }
    else if (plStack_160 != (long *)0x0) {
      pcVar3 = *(code **)(*plStack_160 + 0x28);
      goto code_r0x01d0c7d8;
    }
    ppuStack_130 = &puStack_150;
    puStack_150 = &UNK_02b74308;
    plVar1 = *(long **)(param_1 + 0xb7e0);
    puStack_148 = param_1;
    if ((long *)(param_1 + 0xb7c0) == plVar1) {
      pcVar3 = *(code **)(*plVar1 + 0x20);
code_r0x01d0c828:
      (*pcVar3)();
    }
    else if (plVar1 != (long *)0x0) {
      pcVar3 = *(code **)(*plVar1 + 0x28);
      goto code_r0x01d0c828;
    }
    *(long *)(param_1 + 0xb7e0) = 0;
    ppuStack_c0 = (undefined **)0x0;
    std::__ndk1::function<bool (Aska::Status)>::swap(std::__ndk1::function<bool (Aska::Status)>&)(&puStack_e0,param_1 + 0xb7f0);
    if (&puStack_e0 == ppuStack_c0) {
      pcVar3 = *(code **)(*ppuStack_c0 + 0x20);
code_r0x01d0c86c:
      (*pcVar3)();
    }
    else if (ppuStack_c0 != (undefined **)0x0) {
      pcVar3 = *(code **)(*ppuStack_c0 + 0x28);
      goto code_r0x01d0c86c;
    }
    plVar1 = *(long **)(param_1 + 0xb840);
    if ((long *)(param_1 + 0xb820) == plVar1) {
      pcVar3 = *(code **)(*plVar1 + 0x20);
code_r0x01d0c8a4:
      (*pcVar3)();
    }
    else if (plVar1 != (long *)0x0) {
      pcVar3 = *(code **)(*plVar1 + 0x28);
      goto code_r0x01d0c8a4;
    }
    *(long *)(param_1 + 0xb840) = 0;
    if (&puStack_150 == ppuStack_130) {
      pcVar3 = *(code **)(*ppuStack_130 + 0x20);
code_r0x01d0c8d4:
      (*pcVar3)();
    }
    else if (ppuStack_130 != (undefined **)0x0) {
      pcVar3 = *(code **)(*ppuStack_130 + 0x28);
      goto code_r0x01d0c8d4;
    }
    puStack_e0 = &UNK_02b74388;
    uStack_d8 = param_1;
    auStack_d0[0] = (ulong)param_2;
    ppuStack_c0 = &puStack_e0;
    CMultiPlay3::RegistCall(std::__ndk1::function<bool ()> const&, bool, unsigned int)(param_1,&puStack_e0,1);
    if (&puStack_e0 == ppuStack_c0) {
      pcVar3 = *(code **)(*ppuStack_c0 + 0x20);
    }
    else {
      if (ppuStack_c0 == (undefined **)0x0) goto code_r0x01d0c930;
      pcVar3 = *(code **)(*ppuStack_c0 + 0x28);
    }
    (*pcVar3)();
code_r0x01d0c930:
    param_1[0xb946] = 1;
    return;
  }
  puStack_148 = (undefined *)CONCAT44(puStack_148._4_4_,param_2);
  plVar1 = (long *)param_3[4];
  puStack_150 = param_1;
  if (plVar1 == (long *)0x0) {
    plStack_120 = (long *)0x0;
    plVar1 = (long *)param_4[4];
joined_r0x01d0c41c:
    if (plVar1 == (long *)0x0) goto code_r0x01d0c3e0;
code_r0x01d0c420:
    if (param_4 == plVar1) {
      plStack_f0 = alStack_110;
      (**(code **)(*plVar1 + 0x18))();
    }
    else {
      plStack_f0 = (long *)(**(code **)(*plVar1 + 0x10))();
    }
  }
  else {
    if (param_3 == plVar1) {
      plStack_120 = alStack_140;
      (**(code **)(*plVar1 + 0x18))();
      plVar1 = (long *)param_4[4];
      goto joined_r0x01d0c41c;
    }
    plStack_120 = (long *)(**(code **)(*plVar1 + 0x10))();
    plVar1 = (long *)param_4[4];
    if (plVar1 != (long *)0x0) goto code_r0x01d0c420;
code_r0x01d0c3e0:
    plStack_f0 = (long *)0x0;
  }
  uStack_d8 = (undefined *)CONCAT44(uStack_d8._4_4_,puStack_148._0_4_);
  puStack_e0 = puStack_150;
  if (plStack_120 == (long *)0x0) {
    puStack_b0 = (ulong *)0x0;
joined_r0x01d0c4cc:
    if (plStack_f0 == (long *)0x0) goto code_r0x01d0c4bc;
code_r0x01d0c4d0:
    if (alStack_110 == plStack_f0) {
      plStack_80 = alStack_a0;
      (**(code **)(*plStack_f0 + 0x18))();
    }
    else {
      plStack_80 = (long *)(**(code **)(*plStack_f0 + 0x10))();
    }
  }
  else {
    if (alStack_140 == plStack_120) {
      puStack_b0 = auStack_d0;
      (**(code **)(*plStack_120 + 0x18))();
      goto joined_r0x01d0c4cc;
    }
    puStack_b0 = (ulong *)(**(code **)(*plStack_120 + 0x10))();
    if (plStack_f0 != (long *)0x0) goto code_r0x01d0c4d0;
code_r0x01d0c4bc:
    plStack_80 = (long *)0x0;
  }
  plStack_50 = (long *)0x0;
  plVar1 = (long *)operator new(unsigned long)(0x80);
  *plVar1 = (long)&UNK_02b74288;
  *(undefined4 *)(plVar1 + 3) = (undefined4)uStack_d8;
  plVar1[2] = (long)puStack_e0;
  if (puStack_b0 == (ulong *)0x0) {
    plVar1[8] = 0;
joined_r0x01d0c5a4:
    if (plStack_80 == (long *)0x0) goto code_r0x01d0c594;
code_r0x01d0c5a8:
    if (alStack_a0 == plStack_80) {
      plVar1[0xe] = (long)(plVar1 + 10);
      (**(code **)(*plStack_80 + 0x18))();
    }
    else {
      lVar2 = (**(code **)(*plStack_80 + 0x10))();
      plVar1[0xe] = lVar2;
    }
  }
  else {
    if (auStack_d0 == puStack_b0) {
      plVar1[8] = (long)(plVar1 + 4);
      (**(code **)(*puStack_b0 + 0x18))();
      goto joined_r0x01d0c5a4;
    }
    lVar2 = (**(code **)(*puStack_b0 + 0x10))();
    plVar1[8] = lVar2;
    if (plStack_80 != (long *)0x0) goto code_r0x01d0c5a8;
code_r0x01d0c594:
    plVar1[0xe] = 0;
  }
  plStack_50 = plVar1;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(alStack_70,param_1 + 0xb790);
  if (alStack_70 == plStack_50) {
    pcVar3 = *(code **)(*plStack_50 + 0x20);
code_r0x01d0c638:
    (*pcVar3)();
  }
  else if (plStack_50 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_50 + 0x28);
    goto code_r0x01d0c638;
  }
  if (alStack_a0 == plStack_80) {
    pcVar3 = *(code **)(*plStack_80 + 0x20);
code_r0x01d0c668:
    (*pcVar3)();
  }
  else if (plStack_80 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_80 + 0x28);
    goto code_r0x01d0c668;
  }
  if (auStack_d0 == puStack_b0) {
    pcVar3 = *(code **)(*puStack_b0 + 0x20);
code_r0x01d0c698:
    (*pcVar3)();
  }
  else if (puStack_b0 != (ulong *)0x0) {
    pcVar3 = *(code **)(*puStack_b0 + 0x28);
    goto code_r0x01d0c698;
  }
  if (alStack_110 == plStack_f0) {
    pcVar3 = *(code **)(*plStack_f0 + 0x20);
  }
  else {
    if (plStack_f0 == (long *)0x0) goto code_r0x01d0c6cc;
    pcVar3 = *(code **)(*plStack_f0 + 0x28);
  }
  (*pcVar3)();
code_r0x01d0c6cc:
  if (alStack_140 == plStack_120) {
    (**(code **)(*plStack_120 + 0x20))();
  }
  else if (plStack_120 != (long *)0x0) {
    (**(code **)(*plStack_120 + 0x28))();
  }
  return;
}

// ==== undefined CMultiPlay3::Server_UpdatePublicRoom(bool,std::__ndk1::function<void ()>,std::__ndk1::function<void ()>)
// _ZN11CMultiPlay323Server_UpdatePublicRoomEbNSt6__ndk18functionIFvvEEES3_ @ 01d0c954

void _ZN11CMultiPlay323Server_UpdatePublicRoomEbNSt6__ndk18functionIFvvEEES3_
               (undefined *param_1,uint param_2,long *param_3,long *param_4)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  undefined **ppuVar4;
  code *pcVar5;
  undefined *apuStack_140 [4];
  undefined **ppuStack_120;
  long alStack_110 [4];
  long *plStack_f0;
  undefined *puStack_e0;
  undefined *puStack_d8;
  ulong auStack_d0 [2];
  undefined **ppuStack_c0;
  ulong *puStack_b0;
  long alStack_a0 [4];
  long *plStack_80;
  long alStack_70 [4];
  long *plStack_50;
  
  puStack_e0 = param_1;
  if (*(long *)(param_1 + 0xb750) == 0) {
    plVar1 = (long *)param_4[4];
    if (plVar1 == (long *)0x0) {
      ppuStack_c0 = (undefined **)0x0;
    }
    else if (param_4 == plVar1) {
      ppuStack_c0 = &puStack_e0;
      (**(code **)(*plVar1 + 0x18))(plVar1,&puStack_e0);
    }
    else {
      ppuStack_c0 = (undefined **)(**(code **)(*plVar1 + 0x10))();
    }
    std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_e0,param_1 + 0xb760);
    if (&puStack_e0 == ppuStack_c0) {
      pcVar5 = *(code **)(*ppuStack_c0 + 0x20);
code_r0x01d0cd1c:
      (*pcVar5)();
    }
    else if (ppuStack_c0 != (undefined **)0x0) {
      pcVar5 = *(code **)(*ppuStack_c0 + 0x28);
      goto code_r0x01d0cd1c;
    }
    plVar1 = (long *)param_3[4];
    if (plVar1 == (long *)0x0) {
      ppuStack_120 = (undefined **)0x0;
      plVar1 = (long *)param_4[4];
joined_r0x01d0cd70:
      if (plVar1 != (long *)0x0) goto code_r0x01d0cd4c;
code_r0x01d0cd74:
      plStack_f0 = (long *)0x0;
    }
    else {
      if (param_3 == plVar1) {
        ppuStack_120 = apuStack_140;
        (**(code **)(*plVar1 + 0x18))();
        plVar1 = (long *)param_4[4];
        goto joined_r0x01d0cd70;
      }
      ppuStack_120 = (undefined **)(**(code **)(*plVar1 + 0x10))();
      plVar1 = (long *)param_4[4];
      if (plVar1 == (long *)0x0) goto code_r0x01d0cd74;
code_r0x01d0cd4c:
      if (param_4 == plVar1) {
        plStack_f0 = alStack_110;
        (**(code **)(*plVar1 + 0x18))();
      }
      else {
        plStack_f0 = (long *)(**(code **)(*plVar1 + 0x10))();
      }
    }
    lVar2 = *(long *)(param_1 + 0x1b8);
    if (ppuStack_120 == (undefined **)0x0) {
      puStack_b0 = (ulong *)0x0;
joined_r0x01d0ce20:
      if (plStack_f0 != (long *)0x0) goto code_r0x01d0cdf4;
code_r0x01d0ce24:
      plStack_80 = (long *)0x0;
    }
    else {
      if (apuStack_140 == ppuStack_120) {
        puStack_b0 = auStack_d0;
        (**(code **)(*ppuStack_120 + 0x18))();
        goto joined_r0x01d0ce20;
      }
      puStack_b0 = (ulong *)(**(code **)(*ppuStack_120 + 0x10))();
      if (plStack_f0 == (long *)0x0) goto code_r0x01d0ce24;
code_r0x01d0cdf4:
      if (alStack_110 == plStack_f0) {
        plStack_80 = alStack_a0;
        (**(code **)(*plStack_f0 + 0x18))();
      }
      else {
        plStack_80 = (long *)(**(code **)(*plStack_f0 + 0x10))();
      }
    }
    plStack_50 = (long *)0x0;
    plVar1 = (long *)operator new(unsigned long)(0x80);
    *plVar1 = (long)&UNK_02b74488;
    plVar1[2] = (long)puStack_e0;
    if (puStack_b0 == (ulong *)0x0) {
      plVar1[8] = 0;
joined_r0x01d0cef0:
      if (plStack_80 != (long *)0x0) goto code_r0x01d0cec4;
code_r0x01d0cef4:
      plVar1[0xe] = 0;
    }
    else {
      if (auStack_d0 == puStack_b0) {
        plVar1[8] = (long)(plVar1 + 4);
        (**(code **)(*puStack_b0 + 0x18))();
        goto joined_r0x01d0cef0;
      }
      lVar3 = (**(code **)(*puStack_b0 + 0x10))();
      plVar1[8] = lVar3;
      if (plStack_80 == (long *)0x0) goto code_r0x01d0cef4;
code_r0x01d0cec4:
      if (alStack_a0 == plStack_80) {
        plVar1[0xe] = (long)(plVar1 + 10);
        (**(code **)(*plStack_80 + 0x18))();
      }
      else {
        lVar3 = (**(code **)(*plStack_80 + 0x10))();
        plVar1[0xe] = lVar3;
      }
    }
    plStack_50 = plVar1;
    std::__ndk1::function<void (Aska::Status)>::swap(std::__ndk1::function<void (Aska::Status)>&)(alStack_70,lVar2 + 0x1a0);
    if (alStack_70 == plStack_50) {
      pcVar5 = *(code **)(*plStack_50 + 0x20);
code_r0x01d0cf68:
      (*pcVar5)();
    }
    else if (plStack_50 != (long *)0x0) {
      pcVar5 = *(code **)(*plStack_50 + 0x28);
      goto code_r0x01d0cf68;
    }
    if (alStack_a0 == plStack_80) {
      pcVar5 = *(code **)(*plStack_80 + 0x20);
code_r0x01d0cf98:
      (*pcVar5)();
    }
    else if (plStack_80 != (long *)0x0) {
      pcVar5 = *(code **)(*plStack_80 + 0x28);
      goto code_r0x01d0cf98;
    }
    if (auStack_d0 == puStack_b0) {
      pcVar5 = *(code **)(*puStack_b0 + 0x20);
code_r0x01d0cfc8:
      (*pcVar5)();
    }
    else if (puStack_b0 != (ulong *)0x0) {
      pcVar5 = *(code **)(*puStack_b0 + 0x28);
      goto code_r0x01d0cfc8;
    }
    if (alStack_110 == plStack_f0) {
      pcVar5 = *(code **)(*plStack_f0 + 0x20);
code_r0x01d0cff8:
      (*pcVar5)();
    }
    else if (plStack_f0 != (long *)0x0) {
      pcVar5 = *(code **)(*plStack_f0 + 0x28);
      goto code_r0x01d0cff8;
    }
    if (apuStack_140 == ppuStack_120) {
      pcVar5 = *(code **)(*ppuStack_120 + 0x20);
code_r0x01d0d028:
      (*pcVar5)();
    }
    else if (ppuStack_120 != (undefined **)0x0) {
      pcVar5 = *(code **)(*ppuStack_120 + 0x28);
      goto code_r0x01d0d028;
    }
    plVar1 = *(long **)(param_1 + 0xb7e0);
    if ((long *)(param_1 + 0xb7c0) == plVar1) {
      pcVar5 = *(code **)(*plVar1 + 0x20);
code_r0x01d0d060:
      (*pcVar5)();
    }
    else if (plVar1 != (long *)0x0) {
      pcVar5 = *(code **)(*plVar1 + 0x28);
      goto code_r0x01d0d060;
    }
    *(undefined8 *)(param_1 + 0xb7e0) = 0;
    ppuStack_c0 = (undefined **)0x0;
    std::__ndk1::function<bool (Aska::Status)>::swap(std::__ndk1::function<bool (Aska::Status)>&)(&puStack_e0,param_1 + 0xb7f0);
    if (&puStack_e0 == ppuStack_c0) {
      pcVar5 = *(code **)(*ppuStack_c0 + 0x20);
code_r0x01d0d0a4:
      (*pcVar5)();
    }
    else if (ppuStack_c0 != (undefined **)0x0) {
      pcVar5 = *(code **)(*ppuStack_c0 + 0x28);
      goto code_r0x01d0d0a4;
    }
    plVar1 = *(long **)(param_1 + 0xb840);
    if ((long *)(param_1 + 0xb820) == plVar1) {
      pcVar5 = *(code **)(*plVar1 + 0x20);
code_r0x01d0d0dc:
      (*pcVar5)();
    }
    else if (plVar1 != (long *)0x0) {
      pcVar5 = *(code **)(*plVar1 + 0x28);
      goto code_r0x01d0d0dc;
    }
    auStack_d0[0] = (ulong)(param_2 & 1);
    *(undefined8 *)(param_1 + 0xb840) = 0;
    puStack_e0 = &UNK_02b74508;
    puStack_d8 = param_1;
    ppuStack_c0 = &puStack_e0;
    CMultiPlay3::RegistCall(std::__ndk1::function<bool ()> const&, bool, unsigned int)(param_1,&puStack_e0,1);
    ppuVar4 = ppuStack_c0;
    if (&puStack_e0 != ppuStack_c0) goto code_r0x01d0ccb8;
  }
  else {
    plVar1 = (long *)param_3[4];
    if (plVar1 == (long *)0x0) {
      ppuStack_120 = (undefined **)0x0;
      plVar1 = (long *)param_4[4];
joined_r0x01d0c9f4:
      if (plVar1 == (long *)0x0) goto code_r0x01d0c9b8;
code_r0x01d0c9f8:
      if (param_4 == plVar1) {
        plStack_f0 = alStack_110;
        (**(code **)(*plVar1 + 0x18))();
      }
      else {
        plStack_f0 = (long *)(**(code **)(*plVar1 + 0x10))();
      }
    }
    else {
      if (param_3 == plVar1) {
        ppuStack_120 = apuStack_140;
        (**(code **)(*plVar1 + 0x18))();
        plVar1 = (long *)param_4[4];
        goto joined_r0x01d0c9f4;
      }
      ppuStack_120 = (undefined **)(**(code **)(*plVar1 + 0x10))();
      plVar1 = (long *)param_4[4];
      if (plVar1 != (long *)0x0) goto code_r0x01d0c9f8;
code_r0x01d0c9b8:
      plStack_f0 = (long *)0x0;
    }
    puStack_d8 = (undefined *)(CONCAT71(puStack_d8._1_7_,(char)param_2) & 0xffffffffffffff01);
    if (ppuStack_120 == (undefined **)0x0) {
      puStack_b0 = (ulong *)0x0;
joined_r0x01d0caa4:
      if (plStack_f0 == (long *)0x0) goto code_r0x01d0ca94;
code_r0x01d0caa8:
      if (alStack_110 == plStack_f0) {
        plStack_80 = alStack_a0;
        (**(code **)(*plStack_f0 + 0x18))();
      }
      else {
        plStack_80 = (long *)(**(code **)(*plStack_f0 + 0x10))();
      }
    }
    else {
      if (apuStack_140 == ppuStack_120) {
        puStack_b0 = auStack_d0;
        (**(code **)(*ppuStack_120 + 0x18))();
        goto joined_r0x01d0caa4;
      }
      puStack_b0 = (ulong *)(**(code **)(*ppuStack_120 + 0x10))();
      if (plStack_f0 != (long *)0x0) goto code_r0x01d0caa8;
code_r0x01d0ca94:
      plStack_80 = (long *)0x0;
    }
    plStack_50 = (long *)0x0;
    plVar1 = (long *)operator new(unsigned long)(0x80);
    *plVar1 = (long)&UNK_02b74408;
    *(undefined1 *)(plVar1 + 3) = puStack_d8._0_1_;
    plVar1[2] = (long)puStack_e0;
    if (puStack_b0 == (ulong *)0x0) {
      plVar1[8] = 0;
joined_r0x01d0cb7c:
      if (plStack_80 == (long *)0x0) goto code_r0x01d0cb6c;
code_r0x01d0cb80:
      if (alStack_a0 == plStack_80) {
        plVar1[0xe] = (long)(plVar1 + 10);
        (**(code **)(*plStack_80 + 0x18))();
      }
      else {
        lVar2 = (**(code **)(*plStack_80 + 0x10))();
        plVar1[0xe] = lVar2;
      }
    }
    else {
      if (auStack_d0 == puStack_b0) {
        plVar1[8] = (long)(plVar1 + 4);
        (**(code **)(*puStack_b0 + 0x18))();
        goto joined_r0x01d0cb7c;
      }
      lVar2 = (**(code **)(*puStack_b0 + 0x10))();
      plVar1[8] = lVar2;
      if (plStack_80 != (long *)0x0) goto code_r0x01d0cb80;
code_r0x01d0cb6c:
      plVar1[0xe] = 0;
    }
    plStack_50 = plVar1;
    std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(alStack_70,param_1 + 0xb790);
    if (alStack_70 == plStack_50) {
      pcVar5 = *(code **)(*plStack_50 + 0x20);
code_r0x01d0cc10:
      (*pcVar5)();
    }
    else if (plStack_50 != (long *)0x0) {
      pcVar5 = *(code **)(*plStack_50 + 0x28);
      goto code_r0x01d0cc10;
    }
    if (alStack_a0 == plStack_80) {
      pcVar5 = *(code **)(*plStack_80 + 0x20);
code_r0x01d0cc40:
      (*pcVar5)();
    }
    else if (plStack_80 != (long *)0x0) {
      pcVar5 = *(code **)(*plStack_80 + 0x28);
      goto code_r0x01d0cc40;
    }
    if (auStack_d0 == puStack_b0) {
      pcVar5 = *(code **)(*puStack_b0 + 0x20);
code_r0x01d0cc70:
      (*pcVar5)();
    }
    else if (puStack_b0 != (ulong *)0x0) {
      pcVar5 = *(code **)(*puStack_b0 + 0x28);
      goto code_r0x01d0cc70;
    }
    if (alStack_110 == plStack_f0) {
      pcVar5 = *(code **)(*plStack_f0 + 0x20);
code_r0x01d0cca0:
      (*pcVar5)();
    }
    else if (plStack_f0 != (long *)0x0) {
      pcVar5 = *(code **)(*plStack_f0 + 0x28);
      goto code_r0x01d0cca0;
    }
    ppuVar4 = ppuStack_120;
    if (apuStack_140 != ppuStack_120) {
code_r0x01d0ccb8:
      if (ppuVar4 == (undefined **)0x0) {
        return;
      }
      pcVar5 = *(code **)(*ppuVar4 + 0x28);
      goto code_r0x01d0d128;
    }
  }
  pcVar5 = *(code **)(*ppuVar4 + 0x20);
code_r0x01d0d128:
  (*pcVar5)();
  return;
}

// ==== undefined CMultiPlay3::RetryAutoMatch(void)
// _ZN11CMultiPlay314RetryAutoMatchEv @ 01d0e614

void _ZN11CMultiPlay314RetryAutoMatchEv(long param_1)

{
  long *plVar1;
  undefined8 uVar2;
  code *pcVar3;
  
  if (*(char *)(param_1 + 0xb947) == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_028ff63e/*"C:\BAS_Submission\Client\Project\..\Source\Game\UI\MultiPlay3.cpp"*/,0x1501,&UNK_028ff7ee/*"m_bIsAutoMatching is null."*/);
  }
  CMultiPlay3::EndCall()(param_1);
  Aska::Yayoi::MatchingClient::ResetPeer()(*(undefined8 *)
                   (*(long *)
                     PTR__ZN9Framework10TSingletonI17CMultiplayManagerE11m_pInstanceE_02cc2908 +
                   0x40));
  plVar1 = *(long **)(param_1 + 0xb750);
  if ((long *)(param_1 + 0xb730) == plVar1) {
    pcVar3 = *(code **)(*plVar1 + 0x20);
  }
  else {
    if (plVar1 == (long *)0x0) goto code_r0x01d0e698;
    pcVar3 = *(code **)(*plVar1 + 0x28);
  }
  (*pcVar3)();
code_r0x01d0e698:
  *(long *)(param_1 + 0xb750) = 0;
  if (*(int *)(param_1 + 0xb710) == 0xb) {
    uVar2 = 0xf;
  }
  else {
    if (0.0 < *(float *)(param_1 + 0xb90c)) {
      (*(code *)PTR__ZN11CMultiPlay319Server_AutoMatchingEv_02c9f9d0)(param_1);
      return;
    }
    uVar2 = 10;
  }
  (*(code *)PTR__ZN11CMultiPlay35StateENS_6eStateE_02ca4638)(param_1,uVar2);
  return;
}

// ==== undefined CMultiPlay3::StateInit(void)
// _ZN11CMultiPlay39StateInitEv @ 01d00494

void _ZN11CMultiPlay39StateInitEv(long param_1)

{
  long lVar1;
  long lVar2;
  code *pcVar3;
  undefined4 uStack_134;
  long alStack_130 [4];
  long *plStack_110;
  long alStack_100 [4];
  long *plStack_e0;
  long alStack_d0 [4];
  long *plStack_b0;
  long alStack_a0 [4];
  long *plStack_80;
  undefined4 *puStack_70;
  long lStack_68;
  undefined4 **ppuStack_50;
  undefined1 auStack_38 [8];
  
  plStack_110 = (long *)0x0;
  plStack_e0 = (long *)0x0;
  plStack_b0 = (long *)0x0;
  plStack_80 = (long *)0x0;
  puStack_70 = (undefined4 *)&UNK_02b71418;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_100);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d00504:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d00504;
  }
  puStack_70 = (undefined4 *)&UNK_02b71498;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_d0);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d00554:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d00554;
  }
  lVar2 = param_1 + 0xb6f8;
  puStack_70 = &uStack_134;
  uStack_134 = 0;
  lVar1 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__tree_node<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__map_value_compare<CMultiPlay3::eState, std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::less<CMultiPlay3::eState>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<CMultiPlay3::eState, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>, std::__ndk1::tuple<> >(CMultiPlay3::eState const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>&&, std::__ndk1::tuple<>&&)(lVar2,&uStack_134,&UNK_028ffd66,&puStack_70,auStack_38);
  CAppState::operator=(CAppState const&)(lVar1 + 0x30,alStack_130);
  if (alStack_a0 == plStack_80) {
    pcVar3 = *(code **)(*plStack_80 + 0x20);
code_r0x01d005c0:
    (*pcVar3)();
  }
  else if (plStack_80 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_80 + 0x28);
    goto code_r0x01d005c0;
  }
  if (alStack_d0 == plStack_b0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x20);
code_r0x01d005f0:
    (*pcVar3)();
  }
  else if (plStack_b0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x28);
    goto code_r0x01d005f0;
  }
  if (alStack_100 == plStack_e0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x20);
code_r0x01d00620:
    (*pcVar3)();
  }
  else if (plStack_e0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x28);
    goto code_r0x01d00620;
  }
  if (alStack_130 == plStack_110) {
    pcVar3 = *(code **)(*plStack_110 + 0x20);
code_r0x01d0064c:
    (*pcVar3)();
  }
  else if (plStack_110 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_110 + 0x28);
    goto code_r0x01d0064c;
  }
  plStack_110 = (long *)0x0;
  plStack_e0 = (long *)0x0;
  plStack_b0 = (long *)0x0;
  plStack_80 = (long *)0x0;
  puStack_70 = (undefined4 *)&UNK_02b71518;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_100);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d006ac:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d006ac;
  }
  puStack_70 = &uStack_134;
  uStack_134 = 1;
  lVar1 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__tree_node<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__map_value_compare<CMultiPlay3::eState, std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::less<CMultiPlay3::eState>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<CMultiPlay3::eState, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>, std::__ndk1::tuple<> >(CMultiPlay3::eState const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>&&, std::__ndk1::tuple<>&&)(lVar2,&uStack_134,&UNK_028ffd66,&puStack_70,auStack_38);
  CAppState::operator=(CAppState const&)(lVar1 + 0x30,alStack_130);
  if (alStack_a0 == plStack_80) {
    pcVar3 = *(code **)(*plStack_80 + 0x20);
code_r0x01d00714:
    (*pcVar3)();
  }
  else if (plStack_80 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_80 + 0x28);
    goto code_r0x01d00714;
  }
  if (alStack_d0 == plStack_b0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x20);
code_r0x01d00744:
    (*pcVar3)();
  }
  else if (plStack_b0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x28);
    goto code_r0x01d00744;
  }
  if (alStack_100 == plStack_e0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x20);
code_r0x01d00774:
    (*pcVar3)();
  }
  else if (plStack_e0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x28);
    goto code_r0x01d00774;
  }
  if (alStack_130 == plStack_110) {
    pcVar3 = *(code **)(*plStack_110 + 0x20);
code_r0x01d007a0:
    (*pcVar3)();
  }
  else if (plStack_110 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_110 + 0x28);
    goto code_r0x01d007a0;
  }
  plStack_110 = (long *)0x0;
  plStack_e0 = (long *)0x0;
  plStack_b0 = (long *)0x0;
  plStack_80 = (long *)0x0;
  puStack_70 = (undefined4 *)&UNK_02b71598;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_100);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d00800:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d00800;
  }
  puStack_70 = (undefined4 *)&UNK_02b71718;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_d0);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d00850:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d00850;
  }
  puStack_70 = &uStack_134;
  uStack_134 = 2;
  lVar1 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__tree_node<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__map_value_compare<CMultiPlay3::eState, std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::less<CMultiPlay3::eState>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<CMultiPlay3::eState, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>, std::__ndk1::tuple<> >(CMultiPlay3::eState const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>&&, std::__ndk1::tuple<>&&)(lVar2,&uStack_134,&UNK_028ffd66,&puStack_70,auStack_38);
  CAppState::operator=(CAppState const&)(lVar1 + 0x30,alStack_130);
  if (alStack_a0 == plStack_80) {
    pcVar3 = *(code **)(*plStack_80 + 0x20);
code_r0x01d008b8:
    (*pcVar3)();
  }
  else if (plStack_80 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_80 + 0x28);
    goto code_r0x01d008b8;
  }
  if (alStack_d0 == plStack_b0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x20);
code_r0x01d008e8:
    (*pcVar3)();
  }
  else if (plStack_b0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x28);
    goto code_r0x01d008e8;
  }
  if (alStack_100 == plStack_e0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x20);
code_r0x01d00918:
    (*pcVar3)();
  }
  else if (plStack_e0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x28);
    goto code_r0x01d00918;
  }
  if (alStack_130 == plStack_110) {
    pcVar3 = *(code **)(*plStack_110 + 0x20);
code_r0x01d00944:
    (*pcVar3)();
  }
  else if (plStack_110 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_110 + 0x28);
    goto code_r0x01d00944;
  }
  plStack_110 = (long *)0x0;
  plStack_e0 = (long *)0x0;
  plStack_b0 = (long *)0x0;
  plStack_80 = (long *)0x0;
  puStack_70 = (undefined4 *)&UNK_02b71798;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_130);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d009a0:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d009a0;
  }
  puStack_70 = (undefined4 *)&UNK_02b71818;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_100);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d009f0:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d009f0;
  }
  puStack_70 = (undefined4 *)&UNK_02b71898;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_d0);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d00a40:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d00a40;
  }
  puStack_70 = &uStack_134;
  uStack_134 = 3;
  lVar1 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__tree_node<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__map_value_compare<CMultiPlay3::eState, std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::less<CMultiPlay3::eState>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<CMultiPlay3::eState, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>, std::__ndk1::tuple<> >(CMultiPlay3::eState const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>&&, std::__ndk1::tuple<>&&)(lVar2,&uStack_134,&UNK_028ffd66,&puStack_70,auStack_38);
  CAppState::operator=(CAppState const&)(lVar1 + 0x30,alStack_130);
  if (alStack_a0 == plStack_80) {
    pcVar3 = *(code **)(*plStack_80 + 0x20);
code_r0x01d00aa8:
    (*pcVar3)();
  }
  else if (plStack_80 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_80 + 0x28);
    goto code_r0x01d00aa8;
  }
  if (alStack_d0 == plStack_b0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x20);
code_r0x01d00ad8:
    (*pcVar3)();
  }
  else if (plStack_b0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x28);
    goto code_r0x01d00ad8;
  }
  if (alStack_100 == plStack_e0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x20);
code_r0x01d00b08:
    (*pcVar3)();
  }
  else if (plStack_e0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x28);
    goto code_r0x01d00b08;
  }
  if (alStack_130 == plStack_110) {
    pcVar3 = *(code **)(*plStack_110 + 0x20);
code_r0x01d00b34:
    (*pcVar3)();
  }
  else if (plStack_110 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_110 + 0x28);
    goto code_r0x01d00b34;
  }
  plStack_110 = (long *)0x0;
  plStack_e0 = (long *)0x0;
  plStack_b0 = (long *)0x0;
  plStack_80 = (long *)0x0;
  puStack_70 = (undefined4 *)&UNK_02b71918;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_130);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d00b90:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d00b90;
  }
  puStack_70 = (undefined4 *)&UNK_02b71998;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_100);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d00be0:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d00be0;
  }
  puStack_70 = (undefined4 *)&UNK_02b71b18;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_d0);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d00c30:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d00c30;
  }
  puStack_70 = &uStack_134;
  uStack_134 = 4;
  lVar1 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__tree_node<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__map_value_compare<CMultiPlay3::eState, std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::less<CMultiPlay3::eState>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<CMultiPlay3::eState, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>, std::__ndk1::tuple<> >(CMultiPlay3::eState const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>&&, std::__ndk1::tuple<>&&)(lVar2,&uStack_134,&UNK_028ffd66,&puStack_70,auStack_38);
  CAppState::operator=(CAppState const&)(lVar1 + 0x30,alStack_130);
  if (alStack_a0 == plStack_80) {
    pcVar3 = *(code **)(*plStack_80 + 0x20);
code_r0x01d00c98:
    (*pcVar3)();
  }
  else if (plStack_80 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_80 + 0x28);
    goto code_r0x01d00c98;
  }
  if (alStack_d0 == plStack_b0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x20);
code_r0x01d00cc8:
    (*pcVar3)();
  }
  else if (plStack_b0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x28);
    goto code_r0x01d00cc8;
  }
  if (alStack_100 == plStack_e0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x20);
code_r0x01d00cf8:
    (*pcVar3)();
  }
  else if (plStack_e0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x28);
    goto code_r0x01d00cf8;
  }
  if (alStack_130 == plStack_110) {
    pcVar3 = *(code **)(*plStack_110 + 0x20);
code_r0x01d00d24:
    (*pcVar3)();
  }
  else if (plStack_110 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_110 + 0x28);
    goto code_r0x01d00d24;
  }
  plStack_110 = (long *)0x0;
  plStack_e0 = (long *)0x0;
  plStack_b0 = (long *)0x0;
  plStack_80 = (long *)0x0;
  puStack_70 = (undefined4 *)&UNK_02b71b98;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_130);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d00d80:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d00d80;
  }
  puStack_70 = (undefined4 *)&UNK_02b71c18;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_100);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d00dd0:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d00dd0;
  }
  puStack_70 = (undefined4 *)&UNK_02b71c98;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_d0);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d00e20:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d00e20;
  }
  puStack_70 = &uStack_134;
  uStack_134 = 5;
  lVar1 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__tree_node<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__map_value_compare<CMultiPlay3::eState, std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::less<CMultiPlay3::eState>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<CMultiPlay3::eState, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>, std::__ndk1::tuple<> >(CMultiPlay3::eState const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>&&, std::__ndk1::tuple<>&&)(lVar2,&uStack_134,&UNK_028ffd66,&puStack_70,auStack_38);
  CAppState::operator=(CAppState const&)(lVar1 + 0x30,alStack_130);
  if (alStack_a0 == plStack_80) {
    pcVar3 = *(code **)(*plStack_80 + 0x20);
code_r0x01d00e88:
    (*pcVar3)();
  }
  else if (plStack_80 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_80 + 0x28);
    goto code_r0x01d00e88;
  }
  if (alStack_d0 == plStack_b0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x20);
code_r0x01d00eb8:
    (*pcVar3)();
  }
  else if (plStack_b0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x28);
    goto code_r0x01d00eb8;
  }
  if (alStack_100 == plStack_e0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x20);
code_r0x01d00ee8:
    (*pcVar3)();
  }
  else if (plStack_e0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x28);
    goto code_r0x01d00ee8;
  }
  if (alStack_130 == plStack_110) {
    pcVar3 = *(code **)(*plStack_110 + 0x20);
code_r0x01d00f14:
    (*pcVar3)();
  }
  else if (plStack_110 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_110 + 0x28);
    goto code_r0x01d00f14;
  }
  plStack_110 = (long *)0x0;
  plStack_e0 = (long *)0x0;
  plStack_b0 = (long *)0x0;
  plStack_80 = (long *)0x0;
  puStack_70 = (undefined4 *)&UNK_02b71d18;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_130);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d00f70:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d00f70;
  }
  puStack_70 = (undefined4 *)&UNK_02b71d98;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_100);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d00fc0:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d00fc0;
  }
  puStack_70 = (undefined4 *)&UNK_02b71e18;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_d0);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d01010:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d01010;
  }
  puStack_70 = &uStack_134;
  uStack_134 = 6;
  lVar1 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__tree_node<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__map_value_compare<CMultiPlay3::eState, std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::less<CMultiPlay3::eState>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<CMultiPlay3::eState, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>, std::__ndk1::tuple<> >(CMultiPlay3::eState const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>&&, std::__ndk1::tuple<>&&)(lVar2,&uStack_134,&UNK_028ffd66,&puStack_70,auStack_38);
  CAppState::operator=(CAppState const&)(lVar1 + 0x30,alStack_130);
  if (alStack_a0 == plStack_80) {
    pcVar3 = *(code **)(*plStack_80 + 0x20);
code_r0x01d01078:
    (*pcVar3)();
  }
  else if (plStack_80 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_80 + 0x28);
    goto code_r0x01d01078;
  }
  if (alStack_d0 == plStack_b0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x20);
code_r0x01d010a8:
    (*pcVar3)();
  }
  else if (plStack_b0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x28);
    goto code_r0x01d010a8;
  }
  if (alStack_100 == plStack_e0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x20);
code_r0x01d010d8:
    (*pcVar3)();
  }
  else if (plStack_e0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x28);
    goto code_r0x01d010d8;
  }
  if (alStack_130 == plStack_110) {
    pcVar3 = *(code **)(*plStack_110 + 0x20);
code_r0x01d01104:
    (*pcVar3)();
  }
  else if (plStack_110 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_110 + 0x28);
    goto code_r0x01d01104;
  }
  plStack_110 = (long *)0x0;
  plStack_e0 = (long *)0x0;
  plStack_b0 = (long *)0x0;
  plStack_80 = (long *)0x0;
  puStack_70 = (undefined4 *)&UNK_02b71f18;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_130);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d01160:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d01160;
  }
  puStack_70 = (undefined4 *)&UNK_02b71f98;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_100);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d011b0:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d011b0;
  }
  puStack_70 = (undefined4 *)&UNK_02b72018;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_d0);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d01200:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d01200;
  }
  puStack_70 = &uStack_134;
  uStack_134 = 7;
  lVar1 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__tree_node<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__map_value_compare<CMultiPlay3::eState, std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::less<CMultiPlay3::eState>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<CMultiPlay3::eState, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>, std::__ndk1::tuple<> >(CMultiPlay3::eState const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>&&, std::__ndk1::tuple<>&&)(lVar2,&uStack_134,&UNK_028ffd66,&puStack_70,auStack_38);
  CAppState::operator=(CAppState const&)(lVar1 + 0x30,alStack_130);
  if (alStack_a0 == plStack_80) {
    pcVar3 = *(code **)(*plStack_80 + 0x20);
code_r0x01d01268:
    (*pcVar3)();
  }
  else if (plStack_80 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_80 + 0x28);
    goto code_r0x01d01268;
  }
  if (alStack_d0 == plStack_b0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x20);
code_r0x01d01298:
    (*pcVar3)();
  }
  else if (plStack_b0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x28);
    goto code_r0x01d01298;
  }
  if (alStack_100 == plStack_e0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x20);
code_r0x01d012c8:
    (*pcVar3)();
  }
  else if (plStack_e0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x28);
    goto code_r0x01d012c8;
  }
  if (alStack_130 == plStack_110) {
    pcVar3 = *(code **)(*plStack_110 + 0x20);
code_r0x01d012f4:
    (*pcVar3)();
  }
  else if (plStack_110 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_110 + 0x28);
    goto code_r0x01d012f4;
  }
  plStack_110 = (long *)0x0;
  plStack_e0 = (long *)0x0;
  plStack_b0 = (long *)0x0;
  plStack_80 = (long *)0x0;
  puStack_70 = (undefined4 *)&UNK_02b72098;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_130);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d01350:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d01350;
  }
  puStack_70 = (undefined4 *)&UNK_02b72118;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_100);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d013a0:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d013a0;
  }
  puStack_70 = (undefined4 *)&UNK_02b72198;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_d0);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d013f0:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d013f0;
  }
  puStack_70 = &uStack_134;
  uStack_134 = 9;
  lVar1 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__tree_node<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__map_value_compare<CMultiPlay3::eState, std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::less<CMultiPlay3::eState>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<CMultiPlay3::eState, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>, std::__ndk1::tuple<> >(CMultiPlay3::eState const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>&&, std::__ndk1::tuple<>&&)(lVar2,&uStack_134,&UNK_028ffd66,&puStack_70,auStack_38);
  CAppState::operator=(CAppState const&)(lVar1 + 0x30,alStack_130);
  if (alStack_a0 == plStack_80) {
    pcVar3 = *(code **)(*plStack_80 + 0x20);
code_r0x01d01458:
    (*pcVar3)();
  }
  else if (plStack_80 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_80 + 0x28);
    goto code_r0x01d01458;
  }
  if (alStack_d0 == plStack_b0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x20);
code_r0x01d01488:
    (*pcVar3)();
  }
  else if (plStack_b0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x28);
    goto code_r0x01d01488;
  }
  if (alStack_100 == plStack_e0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x20);
code_r0x01d014b8:
    (*pcVar3)();
  }
  else if (plStack_e0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x28);
    goto code_r0x01d014b8;
  }
  if (alStack_130 == plStack_110) {
    pcVar3 = *(code **)(*plStack_110 + 0x20);
code_r0x01d014e4:
    (*pcVar3)();
  }
  else if (plStack_110 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_110 + 0x28);
    goto code_r0x01d014e4;
  }
  plStack_110 = (long *)0x0;
  plStack_e0 = (long *)0x0;
  plStack_b0 = (long *)0x0;
  plStack_80 = (long *)0x0;
  puStack_70 = (undefined4 *)&UNK_02b72218;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_130);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d01540:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d01540;
  }
  puStack_70 = (undefined4 *)&UNK_02b72298;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_100);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d01590:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d01590;
  }
  puStack_70 = (undefined4 *)&UNK_02b72318;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_d0);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d015e0:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d015e0;
  }
  puStack_70 = &uStack_134;
  uStack_134 = 10;
  lVar1 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__tree_node<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__map_value_compare<CMultiPlay3::eState, std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::less<CMultiPlay3::eState>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<CMultiPlay3::eState, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>, std::__ndk1::tuple<> >(CMultiPlay3::eState const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>&&, std::__ndk1::tuple<>&&)(lVar2,&uStack_134,&UNK_028ffd66,&puStack_70,auStack_38);
  CAppState::operator=(CAppState const&)(lVar1 + 0x30,alStack_130);
  if (alStack_a0 == plStack_80) {
    pcVar3 = *(code **)(*plStack_80 + 0x20);
code_r0x01d01648:
    (*pcVar3)();
  }
  else if (plStack_80 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_80 + 0x28);
    goto code_r0x01d01648;
  }
  if (alStack_d0 == plStack_b0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x20);
code_r0x01d01678:
    (*pcVar3)();
  }
  else if (plStack_b0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x28);
    goto code_r0x01d01678;
  }
  if (alStack_100 == plStack_e0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x20);
code_r0x01d016a8:
    (*pcVar3)();
  }
  else if (plStack_e0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x28);
    goto code_r0x01d016a8;
  }
  if (alStack_130 == plStack_110) {
    pcVar3 = *(code **)(*plStack_110 + 0x20);
code_r0x01d016d4:
    (*pcVar3)();
  }
  else if (plStack_110 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_110 + 0x28);
    goto code_r0x01d016d4;
  }
  plStack_110 = (long *)0x0;
  plStack_e0 = (long *)0x0;
  plStack_b0 = (long *)0x0;
  plStack_80 = (long *)0x0;
  puStack_70 = (undefined4 *)&UNK_02b72398;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_130);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d01730:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d01730;
  }
  puStack_70 = (undefined4 *)&UNK_02b72418;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_d0);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d01780:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d01780;
  }
  puStack_70 = &uStack_134;
  uStack_134 = 0xb;
  lVar1 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__tree_node<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__map_value_compare<CMultiPlay3::eState, std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::less<CMultiPlay3::eState>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<CMultiPlay3::eState, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>, std::__ndk1::tuple<> >(CMultiPlay3::eState const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>&&, std::__ndk1::tuple<>&&)(lVar2,&uStack_134,&UNK_028ffd66,&puStack_70,auStack_38);
  CAppState::operator=(CAppState const&)(lVar1 + 0x30,alStack_130);
  if (alStack_a0 == plStack_80) {
    pcVar3 = *(code **)(*plStack_80 + 0x20);
code_r0x01d017e8:
    (*pcVar3)();
  }
  else if (plStack_80 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_80 + 0x28);
    goto code_r0x01d017e8;
  }
  if (alStack_d0 == plStack_b0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x20);
code_r0x01d01818:
    (*pcVar3)();
  }
  else if (plStack_b0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x28);
    goto code_r0x01d01818;
  }
  if (alStack_100 == plStack_e0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x20);
code_r0x01d01848:
    (*pcVar3)();
  }
  else if (plStack_e0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x28);
    goto code_r0x01d01848;
  }
  if (alStack_130 == plStack_110) {
    pcVar3 = *(code **)(*plStack_110 + 0x20);
code_r0x01d01874:
    (*pcVar3)();
  }
  else if (plStack_110 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_110 + 0x28);
    goto code_r0x01d01874;
  }
  plStack_110 = (long *)0x0;
  plStack_e0 = (long *)0x0;
  plStack_b0 = (long *)0x0;
  plStack_80 = (long *)0x0;
  puStack_70 = (undefined4 *)&UNK_02b72498;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_130);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d018d0:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d018d0;
  }
  puStack_70 = (undefined4 *)&UNK_02b72518;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_d0);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d01920:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d01920;
  }
  puStack_70 = &uStack_134;
  uStack_134 = 0xe;
  lVar1 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__tree_node<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__map_value_compare<CMultiPlay3::eState, std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::less<CMultiPlay3::eState>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<CMultiPlay3::eState, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>, std::__ndk1::tuple<> >(CMultiPlay3::eState const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>&&, std::__ndk1::tuple<>&&)(lVar2,&uStack_134,&UNK_028ffd66,&puStack_70,auStack_38);
  CAppState::operator=(CAppState const&)(lVar1 + 0x30,alStack_130);
  if (alStack_a0 == plStack_80) {
    pcVar3 = *(code **)(*plStack_80 + 0x20);
code_r0x01d01988:
    (*pcVar3)();
  }
  else if (plStack_80 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_80 + 0x28);
    goto code_r0x01d01988;
  }
  if (alStack_d0 == plStack_b0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x20);
code_r0x01d019b8:
    (*pcVar3)();
  }
  else if (plStack_b0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x28);
    goto code_r0x01d019b8;
  }
  if (alStack_100 == plStack_e0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x20);
code_r0x01d019e8:
    (*pcVar3)();
  }
  else if (plStack_e0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x28);
    goto code_r0x01d019e8;
  }
  if (alStack_130 == plStack_110) {
    pcVar3 = *(code **)(*plStack_110 + 0x20);
code_r0x01d01a14:
    (*pcVar3)();
  }
  else if (plStack_110 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_110 + 0x28);
    goto code_r0x01d01a14;
  }
  plStack_110 = (long *)0x0;
  plStack_e0 = (long *)0x0;
  plStack_b0 = (long *)0x0;
  plStack_80 = (long *)0x0;
  puStack_70 = (undefined4 *)&UNK_02b72598;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_130);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d01a70:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d01a70;
  }
  puStack_70 = (undefined4 *)&UNK_02b72618;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_100);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d01ac0:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d01ac0;
  }
  puStack_70 = (undefined4 *)&UNK_02b72698;
  lStack_68 = param_1;
  ppuStack_50 = &puStack_70;
  std::__ndk1::function<void ()>::swap(std::__ndk1::function<void ()>&)(&puStack_70,alStack_d0);
  if (&puStack_70 == ppuStack_50) {
    pcVar3 = *(code **)(*ppuStack_50 + 8);
code_r0x01d01b10:
    (*pcVar3)();
  }
  else if (ppuStack_50 != (undefined4 **)0x0) {
    pcVar3 = *(code **)(*ppuStack_50 + 10);
    goto code_r0x01d01b10;
  }
  puStack_70 = &uStack_134;
  uStack_134 = 0xf;
  lVar2 = std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__tree_node<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, void*>*, long>, bool> std::__ndk1::__tree<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::__map_value_compare<CMultiPlay3::eState, std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, std::__ndk1::less<CMultiPlay3::eState>, true>, Framework::CSTLAllocator<std::__ndk1::__value_type<CMultiPlay3::eState, CAppState>, Framework::CSTLMapAllocatorInf> >::__emplace_unique_key_args<CMultiPlay3::eState, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>, std::__ndk1::tuple<> >(CMultiPlay3::eState const&, std::__ndk1::piecewise_construct_t const&, std::__ndk1::tuple<CMultiPlay3::eState&&>&&, std::__ndk1::tuple<>&&)(lVar2,&uStack_134,&UNK_028ffd66,&puStack_70,auStack_38);
  CAppState::operator=(CAppState const&)(lVar2 + 0x30,alStack_130);
  if (alStack_a0 == plStack_80) {
    pcVar3 = *(code **)(*plStack_80 + 0x20);
code_r0x01d01b78:
    (*pcVar3)();
  }
  else if (plStack_80 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_80 + 0x28);
    goto code_r0x01d01b78;
  }
  if (alStack_d0 == plStack_b0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x20);
code_r0x01d01ba8:
    (*pcVar3)();
  }
  else if (plStack_b0 != (long *)0x0) {
    pcVar3 = *(code **)(*plStack_b0 + 0x28);
    goto code_r0x01d01ba8;
  }
  if (alStack_100 == plStack_e0) {
    pcVar3 = *(code **)(*plStack_e0 + 0x20);
  }
  else {
    if (plStack_e0 == (long *)0x0) goto code_r0x01d01bdc;
    pcVar3 = *(code **)(*plStack_e0 + 0x28);
  }
  (*pcVar3)();
code_r0x01d01bdc:
  if (alStack_130 == plStack_110) {
    pcVar3 = *(code **)(*plStack_110 + 0x20);
  }
  else {
    if (plStack_110 == (long *)0x0) {
      return;
    }
    pcVar3 = *(code **)(*plStack_110 + 0x28);
  }
  (*pcVar3)();
  return;
}

// ==== undefined CMultiPlay3::InitializeEx(CMultiPlay3::eMode,std::__ndk1::function<void (bool)> const &)
// _ZN11CMultiPlay312InitializeExENS_5eModeERKNSt6__ndk18functionIFvbEEE @ 01d041a4

void _ZN11CMultiPlay312InitializeExENS_5eModeERKNSt6__ndk18functionIFvbEEE
               (long param_1,undefined4 param_2,long *param_3)

{
  long *plVar1;
  code *pcVar2;
  long alStack_50 [4];
  long *plStack_30;
  
  plStack_30 = alStack_50;
  *(undefined4 *)(param_1 + 0xb728) = param_2;
  plVar1 = (long *)param_3[4];
  if (plVar1 == (long *)0x0) {
    plStack_30 = (long *)0x0;
  }
  else if (param_3 == plVar1) {
    (**(code **)(*plVar1 + 0x18))(plVar1,alStack_50);
  }
  else {
    plStack_30 = (long *)(**(code **)(*plVar1 + 0x10))();
  }
  std::__ndk1::function<void (bool)>::swap(std::__ndk1::function<void (bool)>&)(alStack_50,param_1 + 0xb850);
  if (alStack_50 == plStack_30) {
    pcVar2 = *(code **)(*plStack_30 + 0x20);
  }
  else {
    if (plStack_30 == (long *)0x0) goto code_r0x01d04240;
    pcVar2 = *(code **)(*plStack_30 + 0x28);
  }
  (*pcVar2)();
code_r0x01d04240:
  if (*(long *)(param_1 + 0x1c8) != 0) {
    CStampUI::InitializeShow(bool)(*(long *)(param_1 + 0x1c8),0);
  }
  CMultiPlay3::State(CMultiPlay3::eState)(param_1,0);
  return;
}

