// port/decomp/game/phase.c: Ghidra decompiles for the game subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-09 02:09 UTC: tools/decomp.sh '--into' 'game/phase' 'CPhase::RequestSwitch' 'CPhase::Progress\(' 'CPhase::Switch' 'CPhase::CPhase' 'CPhase::CBase::' 'CPhase_Base::' 'CPhase_Home::'

// ==== CPhase::CPhase(unsigned int)
// vaddr 0x17b2f34 | ghidra 0x18b2f34 | size 136 | symbol _ZN6CPhaseC1Ej | lib libSOA-3.7.0.so | 2026-10-09
void _ZN6CPhaseC2Ej(long *param_1,undefined4 param_2)

{
  undefined *puVar1;
  
  Framework::CFiberUnit::CFiberUnit(unsigned int)(param_1,0x600);
  puVar1 = PTR__ZN9Framework10TSingletonI6CPhaseE11m_pInstanceE_02cbcd78;
  if (*(long *)PTR__ZN9Framework10TSingletonI6CPhaseE11m_pInstanceE_02cbcd78 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x15,&UNK_027daee5/*"m_pInstance isn't null.(%08x)"*/);
  }
  *(long **)puVar1 = param_1;
  puVar1 = PTR__ZTV6CPhase_02cbda70;
  *(undefined4 *)(param_1 + 7) = param_2;
  *(undefined4 *)((long)param_1 + 0x3c) = param_2;
  param_1[9] = 0;
  *(undefined4 *)(param_1 + 10) = 0;
  param_1[0xf] = 0;
  *(undefined4 *)(param_1 + 8) = 0xffffffff;
  param_1[0xe] = 0;
  param_1[0xd] = 0;
  param_1[0xc] = 0;
  param_1[0xb] = 0;
  *param_1 = (long)(puVar1 + 0x10);
  *(undefined1 *)(param_1 + 0x10) = 0;
  return;
}

// ==== CPhase::Switch(unsigned int)
// vaddr 0x17b3138 | ghidra 0x18b3138 | size 2124 | symbol _ZN6CPhase6SwitchEj | lib libSOA-3.7.0.so | 2026-10-09
/* WARNING: Removing unreachable block (ram,0x018b31a0) */

void _ZN6CPhase6SwitchEj(long param_1,uint param_2)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  ulong uVar4;
  long *plVar5;
  undefined *puVar6;
  undefined4 uVar7;
  long lVar8;
  int *piVar9;
  int iVar10;
  
  if (0x1c < param_2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02863130/*"C:\BAS_Submission\Client\Project\..\Source\Game\Phase\Phase.cpp"*/,0xbd,&UNK_027db1f8/*"The argument has gotten numeric out of range.(%d/%d)"*/,param_2,0x1d);
  }
  uVar7 = *(undefined4 *)(param_1 + 0x38);
  iVar10 = *(int *)(param_1 + 0x50);
  *(uint *)(param_1 + 0x38) = param_2;
  *(undefined4 *)(param_1 + 0x3c) = uVar7;
  if (iVar10 == 0) {
    piVar1 = *(int **)(param_1 + 0x60);
    if (piVar1 == *(int **)(param_1 + 0x58)) {
      iVar10 = 0;
    }
    else {
      piVar9 = piVar1 + -1;
      iVar10 = *piVar9;
      if (piVar1 != piVar9) {
        *(ulong *)(param_1 + 0x60) =
             (long)piVar1 + (~((long)piVar1 + (-4 - (long)piVar9)) & 0xfffffffffffffffcU);
      }
      if (iVar10 == 3) {
        uVar7 = 5;
      }
      else {
        if (iVar10 != 2) goto code_r0x018b31e4;
        uVar7 = 0xb;
      }
      *(undefined4 *)(param_1 + 0x38) = uVar7;
    }
  }
code_r0x018b31e4:
  *(undefined4 *)(param_1 + 0x50) = 0;
  if (*(long **)(param_1 + 0x48) != (long *)0x0) {
    (**(code **)(**(long **)(param_1 + 0x48) + 0x18))();
    if (*(long **)(param_1 + 0x48) != (long *)0x0) {
      (**(code **)(**(long **)(param_1 + 0x48) + 8))();
      *(undefined8 *)(param_1 + 0x48) = 0;
    }
  }
  CTutorialManager::Instance()();
  uVar4 = CTutorialManager::IsStartTutorialNext() const();
  if ((uVar4 & 1) != 0) {
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_02863196/*"NextPhase TutorialNext"*/);
    plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (plVar5 != (long *)0x0) {
      CPhase_TutorialNext::CPhase_TutorialNext(unsigned int)(plVar5,*(undefined4 *)(param_1 + 0x38));
    }
code_r0x018b33b4:
    *(long **)(param_1 + 0x48) = plVar5;
    lVar8 = *plVar5;
    goto code_r0x018b33c0;
  }
  CTutorialManager::Instance()();
  uVar4 = CTutorialManager::IsStartTutorial() const();
  puVar6 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
  if (((uVar4 & 1) == 0) && (uVar2 = *(uint *)(param_1 + 0x38), uVar2 < 0x1d)) {
    if ((1 << (ulong)(uVar2 & 0x1f) & 0x10167fe0U) == 0) {
      if (uVar2 == 4) {
        lVar8 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
        if (lVar8 == 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
          lVar8 = *(long *)puVar6;
        }
        lVar8 = CParameterManager::pParameterUI() const(lVar8);
        if ((lVar8 == 0) || (*(char *)(lVar8 + 0xc06f) != '\0')) goto code_r0x018b3284;
      }
    }
    else {
code_r0x018b3284:
      puVar6 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
      lVar8 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
      if (lVar8 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar8 = *(long *)puVar6;
      }
      cVar3 = *(char *)(lVar8 + 0xb440);
      *(undefined1 *)(lVar8 + 0xb440) = 0;
      if (cVar3 != '\0') {
        _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_028631ad/*"NextPhase Relogin"*/);
        plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
        if (plVar5 != (long *)0x0) {
          CPhase_Relogin::CPhase_Relogin()(plVar5);
        }
        goto code_r0x018b33b4;
      }
    }
  }
  if ((*(char *)(param_1 + 0x80) == '\0') && (uVar4 = CPhase::CheckSynkServerTime()(param_1), (uVar4 & 1) == 0)) {
    uVar2 = *(uint *)(param_1 + 0x38);
    if (uVar2 < 0x1d) goto code_r0x018b33dc;
code_r0x018b3434:
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02863130/*"C:\BAS_Submission\Client\Project\..\Source\Game\Phase\Phase.cpp"*/,0x1a9,&UNK_02863439/*"Illegal phase.(%d)"*/);
    goto code_r0x018b3978;
  }
  uVar2 = *(uint *)(param_1 + 0x38);
  if ((uVar2 < 0x1d) && ((1 << (ulong)(uVar2 & 0x1f) & 0x10127ffaU) != 0)) {
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_028631bf/*"NextPhase SyncServerTime"*/);
    Aska::Yayoi::DNSCache::Clear()(*(long *)PTR__ZN4Aska6Global17m_pNetworkManagerE_02cb9e90 + 0xe0);
    plVar5 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (plVar5 != (long *)0x0) {
      CPhase_SyncServerTime::CPhase_SyncServerTime(unsigned int)(plVar5,*(undefined4 *)(param_1 + 0x38));
    }
    goto code_r0x018b33b4;
  }
  *(undefined8 *)(param_1 + 0x70) = 0;
  *(undefined1 *)(param_1 + 0x80) = 0;
  if (0x1c < uVar2) goto code_r0x018b3434;
code_r0x018b33dc:
  switch(&UNK_028630b4 + *(int *)(&UNK_028630b4 + (ulong)uVar2 * 4)) {
  case (undefined *)0x18b33f4:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_028631d8/*"NextPhase TitleLogo"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_TitleLogo::CPhase_TitleLogo()(lVar8);
    }
    break;
  case (undefined *)0x18b3450:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_028631ec/*"NextPhase Title"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_Title::CPhase_Title()(lVar8);
    }
    break;
  case (undefined *)0x18b3480:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_028631fc/*"NextPhase Login"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_Login::CPhase_Login()(lVar8);
    }
    break;
  case (undefined *)0x18b34b0:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_0286320c/*"NextPhase Event"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_Event::CPhase_Event()(lVar8);
    }
    break;
  case (undefined *)0x18b34e0:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_0286321c/*"NextPhase Home"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_Home::CPhase_Home()(lVar8);
    }
    break;
  case (undefined *)0x18b3510:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_0286322b/*"NextPhase Mission"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x50,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 == 0) goto code_r0x018b366c;
    CPhase_Mission::CPhase_Mission()(lVar8);
    *(long *)(param_1 + 0x48) = lVar8;
    if (iVar10 == 0) goto code_r0x018b3978;
    goto code_r0x018b3674;
  case (undefined *)0x18b3548:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_0286323d/*"NextPhase DeepSpace"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_DeepSpace::CPhase_DeepSpace()(lVar8);
    }
    break;
  case (undefined *)0x18b3578:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_02863251/*"NextPhase ScenarioLibrary"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_ScenarioLibrary::CPhase_ScenarioLibrary()(lVar8);
    }
    break;
  case (undefined *)0x18b35a8:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_0286326b/*"NextPhase SelectPart"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_SelectPart::CPhase_SelectPart()(lVar8);
    }
    break;
  case (undefined *)0x18b35d8:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_02863280/*"NextPhase ItemMenu"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 == 0) goto code_r0x018b366c;
    CPhase_ItemMenu::CPhase_ItemMenu()(lVar8);
    *(long *)(param_1 + 0x48) = lVar8;
    goto joined_r0x018b3608;
  case (undefined *)0x18b3610:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_02863293/*"NextPhase Shop"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_Shop::CPhase_Shop()(lVar8);
    }
    break;
  case (undefined *)0x18b3640:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_028632a2/*"NextPhase PartyComposition"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_PartyComposition::CPhase_PartyComposition()(lVar8);
    }
code_r0x018b366c:
    *(long *)(param_1 + 0x48) = lVar8;
joined_r0x018b3608:
    if (iVar10 != 0) {
code_r0x018b3674:
      *(int *)(lVar8 + 0x10) = iVar10;
    }
    goto code_r0x018b3978;
  case (undefined *)0x18b367c:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_028632bd/*"NextPhase OtherMenu"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_OtherMenu::CPhase_OtherMenu()(lVar8);
    }
    break;
  case (undefined *)0x18b36ac:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_028632d1/*"NextPhase FriendMenu"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_FriendMenu::CPhase_FriendMenu()(lVar8);
    }
    break;
  case (undefined *)0x18b36dc:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_028632e6/*"NextPhase Presentbox"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_Presentbox::CPhase_Presentbox()(lVar8);
    }
    break;
  case (undefined *)0x18b370c:
    puVar6 = &UNK_028632fb/*"From SingleBattle"*/;
    goto code_r0x018b3720;
  case (undefined *)0x18b3718:
    puVar6 = &UNK_0286330d/*"From MultiBattle"*/;
code_r0x018b3720:
    _SmartBeat::LeaveBreadcrumb(char const*)(puVar6);
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_0286331e/*"NextPhase Battle"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_Battle::CPhase_Battle()(lVar8);
    }
    break;
  case (undefined *)0x18b3754:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_0286332f/*"NextPhase Gacha"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_Gacha::CPhase_Gacha()(lVar8);
    }
    break;
  case (undefined *)0x18b3784:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_0286333f/*"NextPhase Setting"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_SystemSetting::CPhase_SystemSetting()(lVar8);
    }
    break;
  case (undefined *)0x18b37b4:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_02863351/*"NextPhase DataDownload"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x58,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_DataDownload::CPhase_DataDownload()(lVar8);
    }
    break;
  case (undefined *)0x18b37e4:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_02863368/*"NextPhase AchievementMenu"*/);
    goto code_r0x018b3978;
  case (undefined *)0x18b37f4:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_02863382/*"NextPhase PlayerInitialize"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_PlayerInitialize::CPhase_PlayerInitialize()(lVar8);
    }
    break;
  case (undefined *)0x18b3824:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_0286339d/*"NextPhase Server"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x38,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_Server::CPhase_Server()(lVar8);
    }
    break;
  case (undefined *)0x18b3854:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_028633ae/*"NextPhase Tutorial"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_TutorialNext::CPhase_TutorialNext(unsigned int)(lVar8,0);
    }
    break;
  case (undefined *)0x18b3888:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_028633c1/*"NextPhase InterruptionResume"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_InterruptionResume::CPhase_InterruptionResume()(lVar8);
    }
    break;
  case (undefined *)0x18b38b8:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_028633de/*"NextPhase BattleResumeCheck"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_BattleResumeCheck::CPhase_BattleResumeCheck()(lVar8);
    }
    break;
  case (undefined *)0x18b38e8:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_028633fa/*"NextPhase BattleGetPlayer"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_BattleGetPlayer::CPhase_BattleGetPlayer()(lVar8);
    }
    break;
  case (undefined *)0x18b3918:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_02863414/*"NextPhase CBT_End"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x28,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_CBT_End::CPhase_CBT_End()(lVar8);
    }
    break;
  case (undefined *)0x18b3948:
    _SmartBeat::LeaveBreadcrumb(char const*)(&UNK_02863426/*"NextPhase TermInfo"*/);
    lVar8 = operator new(unsigned long, std::nothrow_t const&)(0x30,PTR__ZSt7nothrow_02cb9a80);
    if (lVar8 != 0) {
      CPhase_TermInfo::CPhase_TermInfo()(lVar8);
    }
  }
  *(long *)(param_1 + 0x48) = lVar8;
code_r0x018b3978:
  plVar5 = *(long **)(param_1 + 0x48);
  lVar8 = *plVar5;
code_r0x018b33c0:
                    /* WARNING: Could not recover jumptable at 0x018b33cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(lVar8 + 0x10))(plVar5);
  return;
}

// ==== CPhase::RequestSwitch(unsigned int)
// vaddr 0x17b3ed8 | ghidra 0x18b3ed8 | size 48 | symbol _ZN6CPhase13RequestSwitchEj | lib libSOA-3.7.0.so | 2026-10-09
void _ZN6CPhase13RequestSwitchEj(long param_1,undefined4 param_2)

{
  (**(code **)(**(long **)(param_1 + 0x48) + 0x20))();
  *(undefined4 *)(param_1 + 0x40) = param_2;
  return;
}

// ==== CPhase::Progress()
// vaddr 0x17b3ffc | ghidra 0x18b3ffc | size 220 | symbol _ZN6CPhase8ProgressEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN6CPhase8ProgressEv(long param_1)

{
  undefined *puVar1;
  int iVar2;
  long *plVar3;
  ulong uVar4;
  long lVar5;
  long *plVar6;
  
  plVar6 = (long *)(param_1 + 0x48);
  plVar3 = (long *)*plVar6;
  if (plVar3 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02863130/*"C:\BAS_Submission\Client\Project\..\Source\Game\Phase\Phase.cpp"*/,0x295,&UNK_0286345c/*"m_pPresentSubstance is null."*/);
    plVar3 = (long *)*plVar6;
  }
  iVar2 = (**(code **)(*plVar3 + 0x28))();
  if (*(int *)(param_1 + 0x40) == -1) {
    if (iVar2 != -1) {
      (**(code **)(**(long **)(param_1 + 0x48) + 0x20))();
      *(int *)(param_1 + 0x40) = iVar2;
    }
  }
  else {
    uVar4 = (**(code **)(*(long *)*plVar6 + 0x30))();
    puVar1 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
    if ((uVar4 & 1) != 0) {
      lVar5 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
      if (lVar5 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar5 = *(long *)puVar1;
      }
      CUIManager::crSceneObjectContainer() const(lVar5);
      uVar4 = CSceneObjectContainer::IsWaitRelease() const();
      if ((uVar4 & 1) == 0) {
        CPhase::Switch(unsigned int)(param_1,*(undefined4 *)(param_1 + 0x40));
        *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
      }
    }
  }
  return;
}

// ==== CPhase::CBase::ToRelease()
// vaddr 0x17b46fc | ghidra 0x18b46fc | size 4 | symbol _ZN6CPhase5CBase9ToReleaseEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN6CPhase5CBase9ToReleaseEv(void)

{
  return;
}

// ==== CPhase_Base::CPhase_Base()
// vaddr 0x17b4700 | ghidra 0x18b4700 | size 32 | symbol _ZN11CPhase_BaseC2Ev | lib libSOA-3.7.0.so | 2026-10-09
void _ZN11CPhase_BaseC2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTV11CPhase_Base_02cc25e8;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined4 *)(param_1 + 4) = 0xffffffff;
  *param_1 = (long)(puVar1 + 0x10);
  param_1[1] = 0;
  return;
}

// ==== CPhase_Base::~CPhase_Base()
// vaddr 0x17b4720 | ghidra 0x18b4720 | size 20 | symbol _ZN11CPhase_BaseD1Ev | lib libSOA-3.7.0.so | 2026-10-09
void _ZN11CPhase_BaseD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN6CPhase5CBaseE_02cc4988 + 0x10);
  return;
}

// ==== CPhase_Base::~CPhase_Base()
// vaddr 0x17b4734 | ghidra 0x18b4734 | size 4 | symbol _ZN11CPhase_BaseD0Ev | lib libSOA-3.7.0.so | 2026-10-09
void _ZN11CPhase_BaseD0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x18b4738);
  (*pcVar1)();
}

// ==== CPhase::CBase::Initialize()
// vaddr 0x17b4738 | ghidra 0x18b4738 | size 4 | symbol _ZN6CPhase5CBase10InitializeEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN6CPhase5CBase10InitializeEv(void)

{
  return;
}

// ==== CPhase::CBase::Release()
// vaddr 0x17b473c | ghidra 0x18b473c | size 4 | symbol _ZN6CPhase5CBase7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN6CPhase5CBase7ReleaseEv(void)

{
  return;
}

// ==== CPhase::CBase::IsEnableRelease()
// vaddr 0x17b4740 | ghidra 0x18b4740 | size 8 | symbol _ZN6CPhase5CBase15IsEnableReleaseEv | lib libSOA-3.7.0.so | 2026-10-09
undefined8 _ZN6CPhase5CBase15IsEnableReleaseEv(void)

{
  return 1;
}

// ==== CPhase::CBase::~CBase()
// vaddr 0x17b4748 | ghidra 0x18b4748 | size 20 | symbol _ZN6CPhase5CBaseD2Ev | lib libSOA-3.7.0.so | 2026-10-09
void _ZN6CPhase5CBaseD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN6CPhase5CBaseE_02cc4988 + 0x10);
  return;
}

// ==== CPhase::CBase::~CBase()
// vaddr 0x17b475c | ghidra 0x18b475c | size 4 | symbol _ZN6CPhase5CBaseD0Ev | lib libSOA-3.7.0.so | 2026-10-09
void _ZN6CPhase5CBaseD0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x18b4760);
  (*pcVar1)();
}

// ==== CPhase_Home::CPhase_Home()
// vaddr 0x17ba9c0 | ghidra 0x18ba9c0 | size 64 | symbol _ZN11CPhase_HomeC1Ev | lib libSOA-3.7.0.so | 2026-10-09
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN11CPhase_HomeC2Ev(long *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  CPhase_Base::CPhase_Base()();
  puVar1 = PTR__ZTV11CPhase_Home_02cb8880;
  *(undefined4 *)((long)param_1 + 0x24) = 0;
  param_1[5] = 0;
  puVar2 = PTR__ZN9Framework10TSingletonI14CDialogManagerE11m_pInstanceE_02cc3e40;
  *param_1 = (long)(puVar1 + 0x10);
  (*(code *)PTR__ZN14CDialogManager17SetPriorityOffsetEf_02c9cae8)
            (_UNK_0286356c,*(undefined8 *)puVar2);
  return;
}

// ==== CPhase_Home::~CPhase_Home()
// vaddr 0x17baa00 | ghidra 0x18baa00 | size 72 | symbol _ZN11CPhase_HomeD1Ev | lib libSOA-3.7.0.so | 2026-10-09
void _ZN11CPhase_HomeD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTV11CPhase_Home_02cb8880 + 0x10);
  CDialogManager::SetPriorityOffset(float)(0,*(undefined8 *)
                     PTR__ZN9Framework10TSingletonI14CDialogManagerE11m_pInstanceE_02cc3e40);
  (**(code **)(*param_1 + 0x18))(param_1);
  (*(code *)PTR__ZN11CPhase_BaseD2Ev_02c92b60)(param_1);
  return;
}

// ==== CPhase_Home::~CPhase_Home()
// vaddr 0x17baa48 | ghidra 0x18baa48 | size 80 | symbol _ZN11CPhase_HomeD0Ev | lib libSOA-3.7.0.so | 2026-10-09
void _ZN11CPhase_HomeD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTV11CPhase_Home_02cb8880 + 0x10);
  CDialogManager::SetPriorityOffset(float)(0,*(undefined8 *)
                     PTR__ZN9Framework10TSingletonI14CDialogManagerE11m_pInstanceE_02cc3e40);
  (**(code **)(*param_1 + 0x18))(param_1);
  CPhase_Base::~CPhase_Base()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== CPhase_Home::Initialize()
// vaddr 0x17baa98 | ghidra 0x18baa98 | size 4 | symbol _ZN11CPhase_Home10InitializeEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN11CPhase_Home10InitializeEv(void)

{
  return;
}

// ==== CPhase_Home::Release()
// vaddr 0x17baa9c | ghidra 0x18baa9c | size 4 | symbol _ZN11CPhase_Home7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN11CPhase_Home7ReleaseEv(void)

{
  return;
}

// ==== CPhase_Home::Progress()
// vaddr 0x17baaa0 | ghidra 0x18baaa0 | size 1008 | symbol _ZN11CPhase_Home8ProgressEv | lib libSOA-3.7.0.so | 2026-10-09
undefined4 _ZN11CPhase_Home8ProgressEv(long param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  long *plVar3;
  undefined8 uVar4;
  long lVar5;
  int iVar6;
  long lVar7;
  
  puVar1 = PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
  switch(*(undefined4 *)(param_1 + 8)) {
  case 0:
    lVar7 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar7 = *(long *)puVar1;
      lVar5 = *(long *)(lVar7 + 0x38);
    }
    else {
      lVar5 = *(long *)(lVar7 + 0x38);
    }
    if (lVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ec285/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/UI/UIManager.h"*/,0x41,&UNK_027e6bb9/*"m_pSceneObjectContainer is null."*/);
    }
    lVar5 = operator new(unsigned long, std::nothrow_t const&)(0x530,PTR__ZSt7nothrow_02cb9a80);
    if (lVar5 != 0) {
      CHome::CHome()(lVar5);
    }
    CHome::Initialize()(lVar5);
    (**(code **)**(undefined8 **)(lVar7 + 0x38))(*(undefined8 **)(lVar7 + 0x38),lVar5,0);
    plVar3 = (long *)Framework::CTimeElementContainer::rElement_Game()();
    (**(code **)(*plVar3 + 0x10))(plVar3,lVar5);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(lVar5 + 0xb8);
    lVar7 = *(long *)puVar1;
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar7 = *(long *)puVar1;
      lVar5 = *(long *)(lVar7 + 0x38);
    }
    else {
      lVar5 = *(long *)(lVar7 + 0x38);
    }
    if (lVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ec285/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/UI/UIManager.h"*/,0x41,&UNK_027e6bb9/*"m_pSceneObjectContainer is null."*/);
    }
    lVar5 = operator new(unsigned long, std::nothrow_t const&)(0x530,PTR__ZSt7nothrow_02cb9a80);
    if (lVar5 != 0) {
      CCommon::CCommon()(lVar5);
    }
    CCommon::Initialize()(lVar5);
    (**(code **)**(undefined8 **)(lVar7 + 0x38))(*(undefined8 **)(lVar7 + 0x38),lVar5,0);
    plVar3 = (long *)Framework::CTimeElementContainer::rElement_Game()();
    (**(code **)(*plVar3 + 0x10))(plVar3,lVar5);
    *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(lVar5 + 0xb8);
    puVar1 = PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    lVar7 = *(long *)PTR__ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE_02cbf9c0;
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar7 = *(long *)puVar1;
    }
    lVar7 = CParameterManager::pParameterUI() const(lVar7);
    if (lVar7 != 0) {
      lVar7 = *(long *)puVar1;
      if (lVar7 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
        lVar7 = *(long *)puVar1;
      }
      lVar7 = CParameterManager::pParameterUI() const(lVar7);
      *(undefined1 *)(lVar7 + 0xc06f) = 1;
    }
    break;
  case 1:
    lVar7 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar7 = *(long *)puVar1;
    }
    lVar5 = *(long *)(lVar7 + 0x38);
    uVar2 = *(undefined4 *)(param_1 + 0x24);
    if (lVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ec285/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/UI/UIManager.h"*/,0x50,&UNK_027e6bb9/*"m_pSceneObjectContainer is null."*/);
      lVar5 = *(long *)(lVar7 + 0x38);
    }
    uVar4 = CSceneObjectContainer::pSearch(unsigned int)(lVar5,uVar2);
    *(undefined8 *)(param_1 + 0x28) = uVar4;
    lVar7 = *(long *)puVar1;
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar7 = *(long *)puVar1;
    }
    lVar5 = *(long *)(lVar7 + 0x38);
    uVar2 = *(undefined4 *)(param_1 + 0x14);
    if (lVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ec285/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/UI/UIManager.h"*/,0x50,&UNK_027e6bb9/*"m_pSceneObjectContainer is null."*/);
      lVar5 = *(long *)(lVar7 + 0x38);
    }
    lVar7 = CSceneObjectContainer::pSearch(unsigned int)(lVar5,uVar2);
    *(long *)(param_1 + 0x18) = lVar7;
    if (lVar7 == 0) {
      return 0xffffffff;
    }
    if (*(long *)(param_1 + 0x28) == 0) {
      return 0xffffffff;
    }
    *(long *)(*(long *)(param_1 + 0x28) + 0x128) = param_1;
    break;
  case 2:
    lVar7 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar7 = *(long *)puVar1;
    }
    lVar5 = *(long *)(lVar7 + 0x38);
    uVar2 = *(undefined4 *)(param_1 + 0x24);
    if (lVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ec285/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/UI/UIManager.h"*/,0x50,&UNK_027e6bb9/*"m_pSceneObjectContainer is null."*/);
      lVar5 = *(long *)(lVar7 + 0x38);
    }
    lVar7 = CSceneObjectContainer::pSearch(unsigned int)(lVar5,uVar2);
    if (lVar7 != 0) {
      return 0xffffffff;
    }
    lVar7 = *(long *)puVar1;
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar7 = *(long *)puVar1;
    }
    CUIManager::DeleteUI(unsigned int)(lVar7,*(undefined4 *)(param_1 + 0x14));
    break;
  case 3:
    lVar7 = *(long *)PTR__ZN9Framework10TSingletonI10CUIManagerE11m_pInstanceE_02cc3ca0;
    if (lVar7 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027dae91/*"C:\BAS_Submission\Client\Project\../Library/Framework/Source\Framework/TSingleton.h"*/,0x23,&UNK_027daf21/*"m_pInstance is null."*/);
      lVar7 = *(long *)puVar1;
    }
    lVar5 = *(long *)(lVar7 + 0x38);
    uVar2 = *(undefined4 *)(param_1 + 0x14);
    if (lVar5 == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_027ec285/*"C:\BAS_Submission\Client\Project\Android\BASAndroid.NativeActivity\..\..\..\Source\Game/UI/UIManager.h"*/,0x50,&UNK_027e6bb9/*"m_pSceneObjectContainer is null."*/);
      lVar5 = *(long *)(lVar7 + 0x38);
    }
    lVar7 = CSceneObjectContainer::pSearch(unsigned int)(lVar5,uVar2);
    if (lVar7 != 0) {
      return 0xffffffff;
    }
    iVar6 = *(int *)(param_1 + 8);
    uVar2 = *(undefined4 *)(param_1 + 0x20);
    goto code_r0x018badb4;
  default:
    return 0xffffffff;
  }
  iVar6 = *(int *)(param_1 + 8);
  uVar2 = 0xffffffff;
code_r0x018badb4:
  *(int *)(param_1 + 8) = iVar6 + 1;
  *(undefined4 *)(param_1 + 0xc) = 0;
  return uVar2;
}

// ==== CPhase_Home::IsEnableRelease()
// vaddr 0x17bae90 | ghidra 0x18bae90 | size 16 | symbol _ZN11CPhase_Home15IsEnableReleaseEv | lib libSOA-3.7.0.so | 2026-10-09
bool _ZN11CPhase_Home15IsEnableReleaseEv(long param_1)

{
  return 3 < *(uint *)(param_1 + 8);
}

// ==== CPhase_Home::ToClose()
// vaddr 0x17baea0 | ghidra 0x18baea0 | size 16 | symbol _ZN11CPhase_Home7ToCloseEv | lib libSOA-3.7.0.so | 2026-10-09
void _ZN11CPhase_Home7ToCloseEv(long param_1)

{
                    /* WARNING: Could not recover jumptable at 0x018baeac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(long **)(param_1 + 0x28) + 0x38))();
  return;
}


// FAILED to create function at 02b0d458 CPhase::CBase::typeinfo
// FAILED to create function at 02b0d470 CPhase_Base::typeinfo
// FAILED to create function at 02b0d4c8 CPhase_Base::vtable
// FAILED to create function at 02b0d518 CPhase::CBase::vtable
// FAILED to create function at 02b0dd28 CPhase_Home::vtable
// FAILED to create function at 02b0dd80 CPhase_Home::typeinfo
