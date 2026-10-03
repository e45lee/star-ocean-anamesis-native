// mission_api: Ghidra decompiles of work/libSOA-3.7.0.so (3.7.0), extracted by extract.py.
// Data, not code: see README.md and docs/multiplayer.md for what they show.

// ==== undefined CStageManager::CallMissionStart(void)
// _ZN13CStageManager16CallMissionStartEv @ 013ca114

void _ZN13CStageManager16CallMissionStartEv(long param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 uVar4;
  long *plVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  long lVar10;
  code *pcVar11;
  undefined4 uVar12;
  undefined1 auStack_b5c0 [8];
  undefined1 auStack_b5b8 [11568];
  undefined1 auStack_8888 [11568];
  undefined1 auStack_5b58 [11568];
  undefined1 auStack_2e28 [8];
  undefined1 auStack_2e20 [11568];
  long alStack_f0 [4];
  long *plStack_d0;
  undefined *puStack_c0;
  long lStack_b8;
  undefined **ppuStack_a0;
  long alStack_90 [4];
  long *plStack_70;
  undefined1 auStack_58 [8];
  
  puVar3 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  lVar10 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (lVar10 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar10 = *(long *)puVar3;
  }
  lVar10 = CParameterManager::pParameterUI() const(lVar10);
  puVar3 = PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278;
  iVar2 = *(int *)(param_1 + 0x58);
  if (iVar2 == 5) {
    CParameterUI::GetParty(unsigned int) const(auStack_2e20,lVar10,3);
    puVar3 = PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278;
    plVar5 = *(long **)PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278;
    if (plVar5 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      plVar5 = *(long **)puVar3;
    }
    uVar12 = *(undefined4 *)(param_1 + 0x68);
    uVar1 = *(undefined4 *)(param_1 + 0x6c);
    pcVar11 = *(code **)(*plVar5 + 0x4e0);
    CParameterUI::GetParty(unsigned int) const(auStack_5b58,lVar10,0);
    uVar6 = CParameterUtility::tCharaData::CharaId(bool) const(auStack_5b58,0);
    CParameterUI::GetParty(unsigned int) const(auStack_8888,lVar10,1);
    uVar7 = CParameterUtility::tCharaData::CharaId(bool) const(auStack_8888,0);
    CParameterUI::GetParty(unsigned int) const(auStack_b5b8,lVar10,2);
    uVar8 = CParameterUtility::tCharaData::CharaId(bool) const(auStack_b5b8,0);
    uVar9 = CParameterUtility::tCharaData::CharaId(bool) const(auStack_2e20,1);
    uVar4 = CParameterUtility::tCharaData::UserId() const(auStack_2e20);
    (*pcVar11)(auStack_2e28,plVar5,uVar12,uVar1,uVar6,uVar7,uVar8,uVar9,uVar4);
    CParameterUtility::tCharaData::~tCharaData()(auStack_b5b8);
    CParameterUtility::tCharaData::~tCharaData()(auStack_8888);
    CParameterUtility::tCharaData::~tCharaData()(auStack_5b58);
    CParameterUtility::tCharaData::~tCharaData()(auStack_2e20);
    return;
  }
  if (iVar2 != 4) {
    if ((*(int *)(lVar10 + 0x140) == 3) || (*(int *)(lVar10 + 0x140) == 0)) {
      uVar12 = *(undefined4 *)(lVar10 + 0x14c);
    }
    else {
      uVar12 = 0;
    }
    plVar5 = *(long **)PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278;
    if (plVar5 == (long *)0x0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      plVar5 = *(long **)puVar3;
      iVar2 = *(int *)(param_1 + 0x58);
    }
    (**(code **)(*plVar5 + 0x268))
              (auStack_b5c0,plVar5,iVar2,*(undefined4 *)(param_1 + 0x54),
               *(undefined4 *)(param_1 + 0x18),*(undefined8 *)(param_1 + 0x20),
               *(undefined4 *)(param_1 + 0x28),*(undefined8 *)(param_1 + 0x30),uVar12);
    return;
  }
  plVar5 = *(long **)PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278;
  if (plVar5 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    plVar5 = *(long **)puVar3;
  }
  (**(code **)(*plVar5 + 0x2b0))
            (auStack_58,plVar5,*(undefined4 *)(param_1 + 0x54),*(undefined4 *)(param_1 + 0x18),
             *(undefined8 *)(param_1 + 0x20));
  puVar3 = PTR__ZN9Framework10TSingletonI17CErrorHandlerWrapE11m_pInstanceE_02cbc0d8;
  lVar10 = *(long *)PTR__ZN9Framework10TSingletonI17CErrorHandlerWrapE11m_pInstanceE_02cbc0d8;
  if (lVar10 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
    lVar10 = *(long *)puVar3;
  }
  ppuStack_a0 = &puStack_c0;
  puStack_c0 = &UNK_02ab7088;
  plStack_70 = (long *)0x0;
  plStack_d0 = (long *)0x0;
  lStack_b8 = param_1;
  CErrorHandlerWrap::Auto(Aska::Yayoi::GameRPC::GameProtocol::FunctionID, std::__ndk1::function<void ()>, std::__ndk1::function<void (bool, unsigned long)>, CErrorHandlerWrap::eHndlType, std::__ndk1::function<void (unsigned long)>, bool, bool)(lVar10,0xa16fd90,alStack_90,&puStack_c0,0xffffffff,alStack_f0,1,1);
  if (alStack_f0 == plStack_d0) {
    pcVar11 = *(code **)(*plStack_d0 + 0x20);
code_r0x013ca3d0:
    (*pcVar11)();
  }
  else if (plStack_d0 != (long *)0x0) {
    pcVar11 = *(code **)(*plStack_d0 + 0x28);
    goto code_r0x013ca3d0;
  }
  if (&puStack_c0 == ppuStack_a0) {
    pcVar11 = *(code **)(*ppuStack_a0 + 0x20);
  }
  else {
    if (ppuStack_a0 == (undefined **)0x0) goto code_r0x013ca404;
    pcVar11 = *(code **)(*ppuStack_a0 + 0x28);
  }
  (*pcVar11)();
code_r0x013ca404:
  if (alStack_90 == plStack_70) {
    (**(code **)(*plStack_70 + 0x20))();
  }
  else if (plStack_70 != (long *)0x0) {
    (**(code **)(*plStack_70 + 0x28))();
  }
  return;
}

// ==== undefined CStageManager::CallMissionEnd(void)
// _ZN13CStageManager14CallMissionEndEv @ 013cadb8

void _ZN13CStageManager14CallMissionEndEv(long param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  long *plVar4;
  undefined1 *puVar5;
  code *pcVar6;
  undefined1 auStack_28 [8];
  undefined1 auStack_18 [8];
  
  puVar3 = PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278;
  if (*(int *)(param_1 + 0x58) != 4) {
    if (*(int *)(param_1 + 0x58) == 5) {
      plVar4 = *(long **)PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278;
      if (plVar4 == (long *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        plVar4 = *(long **)puVar3;
      }
      uVar1 = *(undefined4 *)(param_1 + 0x68);
      uVar2 = *(undefined4 *)(param_1 + 0x6c);
      pcVar6 = *(code **)(*plVar4 + 0x4e8);
      puVar5 = auStack_18;
    }
    else {
      plVar4 = *(long **)PTR__ZN9Framework10TSingletonI10CApiCallerE11m_pInstanceE_02cb8278;
      if (plVar4 == (long *)0x0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        plVar4 = *(long **)puVar3;
      }
      uVar1 = *(undefined4 *)(param_1 + 0x54);
      uVar2 = *(undefined4 *)(param_1 + 0x5c);
      pcVar6 = *(code **)(*plVar4 + 0x280);
      puVar5 = auStack_28;
    }
    (*pcVar6)(puVar5,plVar4,uVar1,uVar2);
  }
  return;
}

