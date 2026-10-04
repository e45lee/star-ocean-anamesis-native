// port/decomp/kernel/fiber.c: Ghidra decompiles for the kernel subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:15 UTC: tools/decomp.sh '--into' 'kernel/fiber' 'Framework::CFiberKernel::' 'Framework::CFiberUnit::' 'Framework::CFiber'

// ==== Framework::CFiberUnit::OnCreated()
// vaddr 0x114bca0 | ghidra 0x124bca0 | size 4 | symbol _ZN9Framework10CFiberUnit9OnCreatedEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CFiberUnit9OnCreatedEv(void)

{
  return;
}

// ==== Framework::CFiberUnit::OnDestroyed()
// vaddr 0x114bca4 | ghidra 0x124bca4 | size 4 | symbol _ZN9Framework10CFiberUnit11OnDestroyedEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CFiberUnit11OnDestroyedEv(void)

{
  return;
}

// ==== Framework::CDebugMenuItemPiece::Start(Framework::CFiberUnit*)
// vaddr 0x1e6f878 | ghidra 0x1f6f878 | size 188 | symbol _ZN9Framework19CDebugMenuItemPiece5StartEPNS_10CFiberUnitE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework19CDebugMenuItemPiece5StartEPNS_10CFiberUnitE(char *param_1)

{
  char cVar1;
  long lVar2;
  
  if (*param_1 == '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029623cc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DebugMenu.cpp"*/,0x6a,&UNK_029625cf/*"The object hasn't been initialized."*/);
    cVar1 = param_1[1];
  }
  else {
    cVar1 = param_1[1];
  }
  if (cVar1 != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029623cc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DebugMenu.cpp"*/,0x6b,&UNK_029624dc/*"Already started."*/);
  }
  if (*(long *)(param_1 + 0x10) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029623cc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DebugMenu.cpp"*/,0x6c,&UNK_029624ed/*"Not found the Kernel."*/);
    lVar2 = *(long *)(param_1 + 8);
  }
  else {
    lVar2 = *(long *)(param_1 + 8);
  }
  if (lVar2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029623cc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DebugMenu.cpp"*/,0x6d,&UNK_02962503/*"Not found the Fiber."*/);
    lVar2 = *(long *)(param_1 + 8);
  }
  Framework::CFiberKernel::Create(Framework::CFiberUnit*)(*(undefined8 *)(param_1 + 0x10),lVar2);
  param_1[1] = '\x01';
  return;
}

// ==== Framework::CDebugMenu::AddPiece(unsigned int, Framework::CFiberUnit*, char const*)
// vaddr 0x1e6fc60 | ghidra 0x1f6fc60 | size 264 | symbol _ZN9Framework10CDebugMenu8AddPieceEjPNS_10CFiberUnitEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CDebugMenu8AddPieceEjPNS_10CFiberUnitEPKc
               (long param_1,uint param_2,undefined8 param_3,undefined8 param_4)

{
  char *pcVar1;
  char cVar2;
  long lVar3;
  long lVar4;
  
  if (*(long *)(param_1 + 0x48) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029623cc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DebugMenu.cpp"*/,0x1ad,&UNK_029625cf/*"The object hasn't been initialized."*/);
  }
  if (*(uint *)(param_1 + 0x40) <= param_2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029623cc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DebugMenu.cpp"*/,0x1ae,&UNK_0296246a/*"Argument 'number' is outrange."*/);
  }
  lVar3 = *(long *)(param_1 + 0x48);
  pcVar1 = (char *)(lVar3 + (ulong)param_2 * 0x20);
  if (*pcVar1 != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029623cc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DebugMenu.cpp"*/,0x1b2,&UNK_02962489/*"Appointed number was already used."*/);
  }
  lVar4 = *(long *)(param_1 + 0x38);
  if (lVar4 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029623cc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DebugMenu.cpp"*/,0x1b4,&UNK_029625cf/*"The object hasn't been initialized."*/);
    lVar4 = *(long *)(param_1 + 0x38);
    cVar2 = *pcVar1;
  }
  else {
    cVar2 = *pcVar1;
  }
  if (cVar2 != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029623cc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DebugMenu.cpp"*/,0x49,&UNK_029625a5/*"Already used."*/);
  }
  lVar3 = lVar3 + (ulong)param_2 * 0x20;
  *(undefined8 *)(lVar3 + 8) = param_3;
  *(long *)(lVar3 + 0x10) = lVar4;
  *(undefined8 *)(lVar3 + 0x18) = param_4;
  *pcVar1 = '\x01';
  return;
}

// ==== Framework::CDebugMenu::RunPiece(unsigned int, Framework::CFiberUnit*, char const*)
// vaddr 0x1e6fd68 | ghidra 0x1f6fd68 | size 252 | symbol _ZN9Framework10CDebugMenu8RunPieceEjPNS_10CFiberUnitEPKc | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CDebugMenu8RunPieceEjPNS_10CFiberUnitEPKc
               (long param_1,uint param_2,long param_3,long param_4)

{
  char *pcVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  
  uVar3 = (ulong)param_2;
  if (*(long *)(param_1 + 0x48) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029623cc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DebugMenu.cpp"*/,0x1bb,&UNK_029625cf/*"The object hasn't been initialized."*/);
  }
  if (*(uint *)(param_1 + 0x40) <= param_2) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029623cc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DebugMenu.cpp"*/,0x1bc,&UNK_0296246a/*"Argument 'number' is outrange."*/);
  }
  lVar4 = *(long *)(param_1 + 0x48);
  pcVar1 = (char *)(lVar4 + uVar3 * 0x20);
  if (param_3 != 0) {
    if (param_4 == 0) {
      if (*pcVar1 == '\0') {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029623cc/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\DebugMenu.cpp"*/,0x60,&UNK_029625b3/*"CDebugMenuItemPiece::pName: The object hasn't been initialized."*/);
      }
      param_4 = *(long *)(lVar4 + uVar3 * 0x20 + 0x18);
    }
    lVar4 = lVar4 + uVar3 * 0x20;
    plVar2 = *(long **)(lVar4 + 8);
    if (plVar2 != (long *)0x0) {
      (**(code **)(*plVar2 + 8))();
      *(long *)(lVar4 + 8) = 0;
    }
    *pcVar1 = '\0';
    *(undefined1 *)(lVar4 + 1) = 0;
    *(undefined8 *)(lVar4 + 0x18) = 0;
    Framework::CDebugMenu::AddPiece(unsigned int, Framework::CFiberUnit*, char const*)(param_1,param_2,param_3,param_4);
  }
  (*(code *)PTR__ZN9Framework19CDebugMenuItemPiece5StartEPNS_10CFiberUnitE_02cb6008)
            (pcVar1,*(undefined8 *)(param_1 + 0x50));
  return;
}

// ==== Framework::CFiberKernel::CFiberKernel(unsigned int)
// vaddr 0x1e7f704 | ghidra 0x1f7f704 | size 72 | symbol _ZN9Framework12CFiberKernelC1Ej | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CFiberKernelC2Ej(long *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  
  param_1[1] = 0;
  param_1[2] = 0;
  *(undefined4 *)((long)param_1 + 0x24) = param_2;
  param_1[5] = 0;
  param_1[6] = 0;
  puVar3 = PTR__ZTVN9Framework12CFiberKernelE_02cc0c00;
  iVar2 = *(int *)PTR__ZN9Framework13TSimpleHandleINS_16CFiberUnitHandleEE14m_MasterHandleE_02cbce60
  ;
  iVar1 = iVar2 + 2;
  if (iVar2 != -1) {
    iVar1 = iVar2 + 1;
  }
  *(int *)PTR__ZN9Framework13TSimpleHandleINS_16CFiberUnitHandleEE14m_MasterHandleE_02cbce60 = iVar1
  ;
  *(int *)(param_1 + 4) = iVar1;
  param_1[3] = 0;
  *param_1 = (long)(puVar3 + 0x10);
  param_1[8] = 0;
  param_1[9] = 0;
  return;
}

// ==== Framework::CFiberUnit::CFiberUnit(unsigned int)
// vaddr 0x1e7f74c | ghidra 0x1f7f74c | size 68 | symbol _ZN9Framework10CFiberUnitC2Ej | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CFiberUnitC2Ej(long *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  undefined *puVar4;
  
  param_1[2] = 0;
  puVar3 = PTR__ZTVN9Framework10CFiberUnitE_02cb8060;
  *(undefined4 *)((long)param_1 + 0x24) = param_2;
  param_1[5] = 0;
  param_1[6] = 0;
  puVar4 = PTR__ZN9Framework13TSimpleHandleINS_16CFiberUnitHandleEE14m_MasterHandleE_02cbce60;
  *param_1 = (long)(puVar3 + 0x10);
  param_1[1] = 0;
  iVar2 = *(int *)puVar4;
  iVar1 = iVar2 + 2;
  if (iVar2 != -1) {
    iVar1 = iVar2 + 1;
  }
  *(int *)puVar4 = iVar1;
  *(int *)(param_1 + 4) = iVar1;
  param_1[3] = 0;
  return;
}

// ==== Framework::CFiberUnit::~CFiberUnit()
// vaddr 0x1e7f790 | ghidra 0x1f7f790 | size 212 | symbol _ZN9Framework10CFiberUnitD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CFiberUnitD1Ev(long *param_1)

{
  long lVar1;
  
  *param_1 = (long)(PTR__ZTVN9Framework10CFiberUnitE_02cb8060 + 0x10);
  if (param_1[5] != 0) {
    Framework::CFiberKernel::Destroy(Framework::CFiberUnit*)(param_1[5],param_1);
    param_1[5] = 0;
  }
  lVar1 = param_1[1];
  *param_1 = (long)(PTR__ZTVN9Framework6TChainINS_10CFiberUnitEEE_02cbb090 + 0x10);
  if (lVar1 == 0) {
    lVar1 = param_1[2];
  }
  else {
    if (*(long **)(lVar1 + 0x10) != param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x31,&UNK_029635d4/*"Previous hasn't myself."*/);
      lVar1 = param_1[1];
    }
    *(long *)(lVar1 + 0x10) = param_1[2];
    lVar1 = param_1[2];
  }
  if (lVar1 != 0) {
    if (*(long **)(lVar1 + 8) != param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x36,&UNK_029635ec/*"Next hasn't myself."*/);
      lVar1 = param_1[2];
    }
    *(long *)(lVar1 + 8) = param_1[1];
  }
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}

// ==== Framework::CFiberKernel::~CFiberKernel()
// vaddr 0x1e7f864 | ghidra 0x1f7f864 | size 212 | symbol _ZN9Framework12CFiberKernelD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CFiberKernelD2Ev(long *param_1)

{
  long lVar1;
  
  *param_1 = (long)(PTR__ZTVN9Framework10CFiberUnitE_02cb8060 + 0x10);
  if (param_1[5] != 0) {
    Framework::CFiberKernel::Destroy(Framework::CFiberUnit*)(param_1[5],param_1);
    param_1[5] = 0;
  }
  lVar1 = param_1[1];
  *param_1 = (long)(PTR__ZTVN9Framework6TChainINS_10CFiberUnitEEE_02cbb090 + 0x10);
  if (lVar1 == 0) {
    lVar1 = param_1[2];
  }
  else {
    if (*(long **)(lVar1 + 0x10) != param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x31,&UNK_029635d4/*"Previous hasn't myself."*/);
      lVar1 = param_1[1];
    }
    *(long *)(lVar1 + 0x10) = param_1[2];
    lVar1 = param_1[2];
  }
  if (lVar1 != 0) {
    if (*(long **)(lVar1 + 8) != param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x36,&UNK_029635ec/*"Next hasn't myself."*/);
      lVar1 = param_1[2];
    }
    *(long *)(lVar1 + 8) = param_1[1];
  }
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}

// ==== Framework::CFiberKernel::~CFiberKernel()
// vaddr 0x1e7f938 | ghidra 0x1f7f938 | size 216 | symbol _ZN9Framework12CFiberKernelD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CFiberKernelD0Ev(long *param_1)

{
  long lVar1;
  
  *param_1 = (long)(PTR__ZTVN9Framework10CFiberUnitE_02cb8060 + 0x10);
  if (param_1[5] != 0) {
    Framework::CFiberKernel::Destroy(Framework::CFiberUnit*)(param_1[5],param_1);
    param_1[5] = 0;
  }
  lVar1 = param_1[1];
  *param_1 = (long)(PTR__ZTVN9Framework6TChainINS_10CFiberUnitEEE_02cbb090 + 0x10);
  if (lVar1 == 0) {
    lVar1 = param_1[2];
  }
  else {
    if (*(long **)(lVar1 + 0x10) != param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x31,&UNK_029635d4/*"Previous hasn't myself."*/);
      lVar1 = param_1[1];
    }
    *(long *)(lVar1 + 0x10) = param_1[2];
    lVar1 = param_1[2];
  }
  if (lVar1 != 0) {
    if (*(long **)(lVar1 + 8) != param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x36,&UNK_029635ec/*"Next hasn't myself."*/);
      lVar1 = param_1[2];
    }
    *(long *)(lVar1 + 8) = param_1[1];
  }
  param_1[1] = 0;
  param_1[2] = 0;
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CFiberKernel::Initialize()
// vaddr 0x1e7fa10 | ghidra 0x1f7fa10 | size 56 | symbol _ZN9Framework12CFiberKernel10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CFiberKernel10InitializeEv(long param_1)

{
  if (*(long *)(param_1 + 0x40) != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963431/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Fiber.cpp"*/,0x21,&UNK_02963482/*"mpUnits isn't null.(%08x)"*/);
  }
  *(undefined8 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  return;
}

// ==== Framework::CFiberKernel::Release()
// vaddr 0x1e7fa48 | ghidra 0x1f7fa48 | size 8 | symbol _ZN9Framework12CFiberKernel7ReleaseEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CFiberKernel7ReleaseEv(long param_1)

{
  *(undefined8 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  return;
}

// ==== Framework::CFiberKernel::NumAttachedUnits() const
// vaddr 0x1e7fa50 | ghidra 0x1f7fa50 | size 52 | symbol _ZNK9Framework12CFiberKernel16NumAttachedUnitsEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework12CFiberKernel16NumAttachedUnitsEv(long param_1)

{
  if (*(long *)(param_1 + 0x40) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963431/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Fiber.cpp"*/,0x31,&UNK_0296349c/*"mpUnits is null."*/);
  }
  return *(undefined4 *)(param_1 + 0x38);
}

// ==== Framework::CFiberKernel::NumActiveUnits() const
// vaddr 0x1e7fa84 | ghidra 0x1f7fa84 | size 52 | symbol _ZNK9Framework12CFiberKernel14NumActiveUnitsEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework12CFiberKernel14NumActiveUnitsEv(long param_1)

{
  if (*(long *)(param_1 + 0x40) == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963431/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Fiber.cpp"*/,0x38,&UNK_0296349c/*"mpUnits is null."*/);
  }
  return *(undefined4 *)(param_1 + 0x3c);
}

// ==== Framework::CFiberKernel::pSearchByHandle(unsigned int) const
// vaddr 0x1e7fab8 | ghidra 0x1f7fab8 | size 88 | symbol _ZNK9Framework12CFiberKernel15pSearchByHandleEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework12CFiberKernel15pSearchByHandleEj(long param_1,int param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x40);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963431/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Fiber.cpp"*/,0x45,&UNK_0296349c/*"mpUnits is null."*/);
    lVar1 = *(long *)(param_1 + 0x40);
    if (lVar1 == 0) {
      return;
    }
  }
  do {
    if (*(int *)(lVar1 + 0x20) == param_2) {
      return;
    }
    lVar1 = *(long *)(lVar1 + 0x10);
  } while (lVar1 != 0);
  return;
}

// ==== Framework::CFiberKernel::pSearchByHandle(unsigned int)
// vaddr 0x1e7fb10 | ghidra 0x1f7fb10 | size 88 | symbol _ZN9Framework12CFiberKernel15pSearchByHandleEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CFiberKernel15pSearchByHandleEj(long param_1,int param_2)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x40);
  if (lVar1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963431/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Fiber.cpp"*/,0x56,&UNK_0296349c/*"mpUnits is null."*/);
    lVar1 = *(long *)(param_1 + 0x40);
    if (lVar1 == 0) {
      return;
    }
  }
  do {
    if (*(int *)(lVar1 + 0x20) == param_2) {
      return;
    }
    lVar1 = *(long *)(lVar1 + 0x10);
  } while (lVar1 != 0);
  return;
}

// ==== Framework::CFiberKernel::Progress()
// vaddr 0x1e7fb68 | ghidra 0x1f7fb68 | size 212 | symbol _ZN9Framework12CFiberKernel8ProgressEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CFiberKernel8ProgressEv(long param_1)

{
  long lVar1;
  long *plVar2;
  int iVar3;
  long *plVar4;
  
  lVar1 = *(long *)(param_1 + 0x40);
  if (lVar1 != 0) {
    do {
      if (*(int *)(lVar1 + 0x30) == 1) {
        *(undefined4 *)(lVar1 + 0x30) = 2;
      }
      lVar1 = *(long *)(lVar1 + 0x10);
    } while (lVar1 != 0);
    plVar2 = *(long **)(param_1 + 0x40);
    if (plVar2 != (long *)0x0) {
      iVar3 = 0;
      do {
        if ((int)plVar2[6] == 2) {
          iVar3 = iVar3 + 1;
          (**(code **)(*plVar2 + 0x28))(plVar2);
        }
        plVar2 = (long *)plVar2[2];
      } while (plVar2 != (long *)0x0);
      plVar2 = *(long **)(param_1 + 0x40);
      while (plVar2 != (long *)0x0) {
        while ((int)plVar2[6] != 4) {
          plVar2 = (long *)plVar2[2];
          if (plVar2 == (long *)0x0) goto code_r0x01f7fc28;
        }
        if (plVar2[5] != 0) {
          Framework::CFiberKernel::Destroy(Framework::CFiberUnit*)(plVar2[5],plVar2);
          plVar2[5] = 0;
        }
        plVar4 = (long *)plVar2[2];
        (**(code **)(*plVar2 + 8))(plVar2);
        plVar2 = plVar4;
      }
      goto code_r0x01f7fc28;
    }
  }
  iVar3 = 0;
code_r0x01f7fc28:
  *(int *)(param_1 + 0x3c) = iVar3;
  return;
}

// ==== Framework::CFiberUnit::Status() const
// vaddr 0x1e7fc3c | ghidra 0x1f7fc3c | size 8 | symbol _ZNK9Framework10CFiberUnit6StatusEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework10CFiberUnit6StatusEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x30);
}

// ==== Framework::CFiberUnit::ActivateFromActivating()
// vaddr 0x1e7fc44 | ghidra 0x1f7fc44 | size 24 | symbol _ZN9Framework10CFiberUnit22ActivateFromActivatingEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CFiberUnit22ActivateFromActivatingEv(long param_1)

{
  if (*(int *)(param_1 + 0x30) == 1) {
    *(undefined4 *)(param_1 + 0x30) = 2;
  }
  return;
}

// ==== Framework::CFiberUnit::Destroy(bool)
// vaddr 0x1e7fc5c | ghidra 0x1f7fc5c | size 56 | symbol _ZN9Framework10CFiberUnit7DestroyEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CFiberUnit7DestroyEb(long param_1,ulong param_2)

{
  if (*(long *)(param_1 + 0x28) != 0) {
    if ((param_2 & 1) == 0) {
      Framework::CFiberKernel::Destroy(Framework::CFiberUnit*)(*(long *)(param_1 + 0x28),param_1);
      *(undefined8 *)(param_1 + 0x28) = 0;
      return;
    }
    *(undefined4 *)(param_1 + 0x30) = 4;
  }
  return;
}

// ==== Framework::CFiberKernel::Attach(Framework::CFiberUnit*)
// vaddr 0x1e7fc94 | ghidra 0x1f7fc94 | size 476 | symbol _ZN9Framework12CFiberKernel6AttachEPNS_10CFiberUnitE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CFiberKernel6AttachEPNS_10CFiberUnitE(long param_1,long param_2)

{
  long lVar1;
  long lVar2;
  
  lVar1 = *(long *)(param_1 + 0x40);
  if (lVar1 == 0) {
    if (*(int *)(param_1 + 0x38) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963431/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Fiber.cpp"*/,0xb1,&UNK_029634ad/*"Internal error, mNumAttachedUnits isn't 0.(%d)"*/);
    }
code_r0x01f7fe14:
    *(long *)(param_1 + 0x40) = param_2;
  }
  else {
    if (*(int *)(param_1 + 0x38) == 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963431/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Fiber.cpp"*/,0xb6,&UNK_029634dc/*"Internal error, mNumAttachedUnits is 0."*/);
      lVar1 = *(long *)(param_1 + 0x40);
      if (lVar1 == 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963431/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Fiber.cpp"*/,0xb7,&UNK_02963504/*"Internal error, mpUnits is NULL."*/);
        lVar1 = *(long *)(param_1 + 0x40);
      }
    }
    do {
      lVar2 = lVar1;
      if (*(uint *)(param_2 + 0x24) < *(uint *)(lVar2 + 0x24)) {
        if ((*(long *)(lVar2 + 8) == 0) && (*(long *)(lVar2 + 0x10) == 0)) {
          *(long *)(lVar2 + 8) = param_2;
          *(undefined8 *)(lVar2 + 0x10) = *(undefined8 *)(param_2 + 0x10);
          if (*(long *)(param_2 + 0x10) != 0) {
            *(long *)(*(long *)(param_2 + 0x10) + 8) = lVar2;
          }
          *(long *)(param_2 + 0x10) = lVar2;
        }
        else {
          if (*(long *)(param_2 + 8) != 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x52,&UNK_02963598/*"Target has already m_pPrevious."*/);
          }
          if (*(long *)(param_2 + 0x10) != 0) {
            Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x53,&UNK_029635b8/*"Target has already m_pNext."*/);
          }
          *(long *)(param_2 + 0x10) = lVar2;
          *(undefined8 *)(param_2 + 8) = *(undefined8 *)(lVar2 + 8);
          if (*(long *)(lVar2 + 8) != 0) {
            *(long *)(*(long *)(lVar2 + 8) + 0x10) = param_2;
          }
          *(long *)(lVar2 + 8) = param_2;
        }
        if (lVar2 == *(long *)(param_1 + 0x40)) goto code_r0x01f7fe14;
        goto code_r0x01f7fe18;
      }
      lVar1 = *(long *)(lVar2 + 0x10);
    } while (*(long *)(lVar2 + 0x10) != 0);
    if ((*(long *)(param_2 + 8) == 0) && (*(long *)(param_2 + 0x10) == 0)) {
      *(long *)(param_2 + 8) = lVar2;
      *(undefined8 *)(param_2 + 0x10) = *(undefined8 *)(lVar2 + 0x10);
      if (*(long *)(lVar2 + 0x10) != 0) {
        *(long *)(*(long *)(lVar2 + 0x10) + 8) = param_2;
      }
      *(long *)(lVar2 + 0x10) = param_2;
    }
    else {
      if (*(long *)(lVar2 + 8) != 0) {
        Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x52,&UNK_02963598/*"Target has already m_pPrevious."*/);
        if (*(long *)(lVar2 + 0x10) != 0) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x53,&UNK_029635b8/*"Target has already m_pNext."*/);
        }
      }
      *(long *)(lVar2 + 0x10) = param_2;
      *(undefined8 *)(lVar2 + 8) = *(undefined8 *)(param_2 + 8);
      if (*(long *)(param_2 + 8) != 0) {
        *(long *)(*(long *)(param_2 + 8) + 0x10) = lVar2;
      }
      *(long *)(param_2 + 8) = lVar2;
    }
  }
code_r0x01f7fe18:
  *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + 1;
  return;
}

// ==== Framework::CFiberUnit::Priority() const
// vaddr 0x1e7fe70 | ghidra 0x1f7fe70 | size 8 | symbol _ZNK9Framework10CFiberUnit8PriorityEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework10CFiberUnit8PriorityEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x24);
}

// ==== Framework::CFiberKernel::Detach(Framework::CFiberUnit*)
// vaddr 0x1e7fe78 | ghidra 0x1f7fe78 | size 240 | symbol _ZN9Framework12CFiberKernel6DetachEPNS_10CFiberUnitE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CFiberKernel6DetachEPNS_10CFiberUnitE(long param_1,long param_2)

{
  int iVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x40);
  do {
    if (lVar2 == 0) {
code_r0x01f7ff48:
      iVar1 = *(int *)(param_1 + 0x38) + -1;
      *(int *)(param_1 + 0x38) = iVar1;
      if (iVar1 == 0) {
        *(undefined8 *)(param_1 + 0x40) = 0;
      }
      return;
    }
    if (lVar2 == param_2) {
      if (*(long *)(param_1 + 0x40) == param_2) {
        *(undefined8 *)(param_1 + 0x40) = *(undefined8 *)(param_2 + 0x10);
        lVar2 = *(long *)(param_2 + 8);
        if (lVar2 == 0) goto code_r0x01f7ff08;
code_r0x01f7feb8:
        if (*(long *)(lVar2 + 0x10) != param_2) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x31,&UNK_029635d4/*"Previous hasn't myself."*/);
          lVar2 = *(long *)(param_2 + 8);
        }
        *(long *)(lVar2 + 0x10) = *(long *)(param_2 + 0x10);
        lVar2 = *(long *)(param_2 + 0x10);
      }
      else {
        lVar2 = *(long *)(param_2 + 8);
        if (lVar2 != 0) goto code_r0x01f7feb8;
code_r0x01f7ff08:
        lVar2 = *(long *)(param_2 + 0x10);
      }
      if (lVar2 != 0) {
        if (*(long *)(lVar2 + 8) != param_2) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x36,&UNK_029635ec/*"Next hasn't myself."*/);
          lVar2 = *(long *)(param_2 + 0x10);
        }
        *(undefined8 *)(lVar2 + 8) = *(undefined8 *)(param_2 + 8);
      }
      *(undefined8 *)(param_2 + 8) = 0;
      *(undefined8 *)(param_2 + 0x10) = 0;
      goto code_r0x01f7ff48;
    }
    lVar2 = *(long *)(lVar2 + 0x10);
  } while( true );
}

// ==== Framework::CFiberKernel::Create(Framework::CFiberUnit*)
// vaddr 0x1e7ff68 | ghidra 0x1f7ff68 | size 108 | symbol _ZN9Framework12CFiberKernel6CreateEPNS_10CFiberUnitE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CFiberKernel6CreateEPNS_10CFiberUnitE(long *param_1,long *param_2)

{
  if (param_2[5] != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963431/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Fiber.cpp"*/,0x10c,&UNK_02963525/*"Already attached."*/);
  }
  param_2[5] = (long)param_1;
  (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *(undefined4 *)(param_2 + 6) = 1;
  param_2[3] = 0;
                    /* WARNING: Could not recover jumptable at 0x01f7ffd0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_2 + 0x30))(param_2);
  return;
}

// ==== Framework::CFiberUnit::IsCreated() const
// vaddr 0x1e7ffd4 | ghidra 0x1f7ffd4 | size 16 | symbol _ZNK9Framework10CFiberUnit9IsCreatedEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework10CFiberUnit9IsCreatedEv(long param_1)

{
  return *(long *)(param_1 + 0x28) != 0;
}

// ==== Framework::CFiberKernel::Destroy(Framework::CFiberUnit*)
// vaddr 0x1e7ffe4 | ghidra 0x1f7ffe4 | size 256 | symbol _ZN9Framework12CFiberKernel7DestroyEPNS_10CFiberUnitE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CFiberKernel7DestroyEPNS_10CFiberUnitE(long param_1,long *param_2)

{
  int iVar1;
  long lVar2;
  long *plVar3;
  
  plVar3 = *(long **)(param_1 + 0x40);
  do {
    if (plVar3 == (long *)0x0) {
code_r0x01f800b4:
      iVar1 = *(int *)(param_1 + 0x38) + -1;
      *(int *)(param_1 + 0x38) = iVar1;
      if (iVar1 == 0) {
        *(undefined8 *)(param_1 + 0x40) = 0;
      }
      *(undefined4 *)(param_2 + 6) = 0;
                    /* WARNING: Could not recover jumptable at 0x01f800e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*param_2 + 0x38))(param_2);
      return;
    }
    if (plVar3 == param_2) {
      if (*(long **)(param_1 + 0x40) == param_2) {
        *(long *)(param_1 + 0x40) = param_2[2];
        lVar2 = param_2[1];
        if (lVar2 == 0) goto code_r0x01f80074;
code_r0x01f80024:
        if (*(long **)(lVar2 + 0x10) != param_2) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x31,&UNK_029635d4/*"Previous hasn't myself."*/);
          lVar2 = param_2[1];
        }
        *(long *)(lVar2 + 0x10) = param_2[2];
        lVar2 = param_2[2];
      }
      else {
        lVar2 = param_2[1];
        if (lVar2 != 0) goto code_r0x01f80024;
code_r0x01f80074:
        lVar2 = param_2[2];
      }
      if (lVar2 != 0) {
        if (*(long **)(lVar2 + 8) != param_2) {
          Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x36,&UNK_029635ec/*"Next hasn't myself."*/);
          lVar2 = param_2[2];
        }
        *(long *)(lVar2 + 8) = param_2[1];
      }
      param_2[1] = 0;
      param_2[2] = 0;
      goto code_r0x01f800b4;
    }
    plVar3 = (long *)plVar3[2];
  } while( true );
}

// ==== Framework::CFiberUnit::~CFiberUnit()
// vaddr 0x1e800e4 | ghidra 0x1f800e4 | size 4 | symbol _ZN9Framework10CFiberUnitD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CFiberUnitD0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x1f800e8);
  (*pcVar1)();
}

// ==== Framework::CFiberUnit::pKernel() const
// vaddr 0x1e800e8 | ghidra 0x1f800e8 | size 8 | symbol _ZNK9Framework10CFiberUnit7pKernelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK9Framework10CFiberUnit7pKernelEv(long param_1)

{
  return *(undefined8 *)(param_1 + 0x28);
}

// ==== Framework::CFiberUnit::Group() const
// vaddr 0x1e800f0 | ghidra 0x1f800f0 | size 8 | symbol _ZNK9Framework10CFiberUnit5GroupEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework10CFiberUnit5GroupEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x34);
}

// ==== Framework::CFiberUnit::Group(unsigned int)
// vaddr 0x1e800f8 | ghidra 0x1f800f8 | size 8 | symbol _ZN9Framework10CFiberUnit5GroupEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CFiberUnit5GroupEj(long param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x34) = param_2;
  return;
}

// ==== Framework::CFiberUnit::Activate()
// vaddr 0x1e80100 | ghidra 0x1f80100 | size 28 | symbol _ZN9Framework10CFiberUnit8ActivateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CFiberUnit8ActivateEv(long param_1)

{
  if ((*(int *)(param_1 + 0x30) == 3) || (*(int *)(param_1 + 0x30) == 0)) {
    *(undefined4 *)(param_1 + 0x30) = 1;
  }
  return;
}

// ==== Framework::CFiberUnit::Wait()
// vaddr 0x1e8011c | ghidra 0x1f8011c | size 20 | symbol _ZN9Framework10CFiberUnit4WaitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CFiberUnit4WaitEv(long param_1)

{
  if (*(int *)(param_1 + 0x30) != 0) {
    *(undefined4 *)(param_1 + 0x30) = 3;
  }
  return;
}

// ==== Framework::CFiberUnit::IsActive() const
// vaddr 0x1e80130 | ghidra 0x1f80130 | size 20 | symbol _ZNK9Framework10CFiberUnit8IsActiveEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework10CFiberUnit8IsActiveEv(long param_1)

{
  return *(int *)(param_1 + 0x30) - 1U < 2;
}

// ==== Framework::CFiberUnit::IsDestroyed() const
// vaddr 0x1e80144 | ghidra 0x1f80144 | size 16 | symbol _ZNK9Framework10CFiberUnit11IsDestroyedEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework10CFiberUnit11IsDestroyedEv(long param_1)

{
  return *(int *)(param_1 + 0x30) == 0;
}

// ==== Framework::CFiberUnit::CreateSubFiber(Framework::CFiberUnit*)
// vaddr 0x1e80154 | ghidra 0x1f80154 | size 156 | symbol _ZN9Framework10CFiberUnit14CreateSubFiberEPS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CFiberUnit14CreateSubFiberEPS0_(long param_1,long *param_2)

{
  long lVar1;
  long *plVar2;
  
  plVar2 = *(long **)(param_1 + 0x28);
  if (plVar2 == (long *)0x0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963431/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Fiber.cpp"*/,0x1a6,&UNK_02963537/*"mpKernel is null"*/);
    plVar2 = *(long **)(param_1 + 0x28);
    lVar1 = param_2[5];
  }
  else {
    lVar1 = param_2[5];
  }
  if (lVar1 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963431/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Fiber.cpp"*/,0x10c,&UNK_02963525/*"Already attached."*/);
  }
  param_2[5] = (long)plVar2;
  (**(code **)(*plVar2 + 0x10))(plVar2,param_2);
  *(undefined4 *)(param_2 + 6) = 1;
  param_2[3] = 0;
                    /* WARNING: Could not recover jumptable at 0x01f801c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_2 + 0x30))(param_2);
  return;
}

// ==== Framework::CFiberUnit::Attach(Framework::CFiberUnit*)
// vaddr 0x1e801f0 | ghidra 0x1f801f0 | size 168 | symbol _ZN9Framework10CFiberUnit6AttachEPS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework10CFiberUnit6AttachEPS0_(long param_1,long param_2)

{
  if ((*(long *)(param_2 + 8) == 0) && (*(long *)(param_2 + 0x10) == 0)) {
    *(long *)(param_2 + 8) = param_1;
    *(undefined8 *)(param_2 + 0x10) = *(undefined8 *)(param_1 + 0x10);
    if (*(long *)(param_1 + 0x10) != 0) {
      *(long *)(*(long *)(param_1 + 0x10) + 8) = param_2;
    }
    *(long *)(param_1 + 0x10) = param_2;
  }
  else {
    if (*(long *)(param_1 + 8) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x52,&UNK_02963598/*"Target has already m_pPrevious."*/);
    }
    if (*(long *)(param_1 + 0x10) != 0) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x53,&UNK_029635b8/*"Target has already m_pNext."*/);
    }
    *(long *)(param_1 + 0x10) = param_2;
    *(undefined8 *)(param_1 + 8) = *(undefined8 *)(param_2 + 8);
    if (*(long *)(param_2 + 8) != 0) {
      *(long *)(*(long *)(param_2 + 8) + 0x10) = param_1;
    }
    *(long *)(param_2 + 8) = param_1;
  }
  return;
}

// ==== Framework::CFiberUnit::pTop()
// vaddr 0x1e80298 | ghidra 0x1f80298 | size 20 | symbol _ZN9Framework10CFiberUnit4pTopEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework10CFiberUnit4pTopEv(long param_1)

{
  long lVar1;
  
  do {
    lVar1 = param_1;
    param_1 = *(long *)(lVar1 + 8);
  } while (param_1 != 0);
  return lVar1;
}

// ==== Framework::CFiberUnit::pBottom()
// vaddr 0x1e802ac | ghidra 0x1f802ac | size 20 | symbol _ZN9Framework10CFiberUnit7pBottomEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN9Framework10CFiberUnit7pBottomEv(long param_1)

{
  long lVar1;
  
  do {
    lVar1 = param_1;
    param_1 = *(long *)(lVar1 + 0x10);
  } while (param_1 != 0);
  return lVar1;
}

// ==== Framework::CFiberKernel::CreateSubFiber(Framework::CFiberUnit*)
// vaddr 0x1e802c0 | ghidra 0x1f802c0 | size 108 | symbol _ZN9Framework12CFiberKernel14CreateSubFiberEPNS_10CFiberUnitE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CFiberKernel14CreateSubFiberEPNS_10CFiberUnitE(long *param_1,long *param_2)

{
  if (param_2[5] != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963431/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\Fiber.cpp"*/,0x10c,&UNK_02963525/*"Already attached."*/);
  }
  param_2[5] = (long)param_1;
  (**(code **)(*param_1 + 0x10))(param_1,param_2);
  *(undefined4 *)(param_2 + 6) = 1;
  param_2[3] = 0;
                    /* WARNING: Could not recover jumptable at 0x01f80328. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_2 + 0x30))(param_2);
  return;
}

// ==== Framework::TChain<Framework::CFiberUnit>::~TChain()
// vaddr 0x1e8032c | ghidra 0x1f8032c | size 176 | symbol _ZN9Framework6TChainINS_10CFiberUnitEED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework6TChainINS_10CFiberUnitEED2Ev(long *param_1)

{
  long lVar1;
  
  lVar1 = param_1[1];
  *param_1 = (long)(PTR__ZTVN9Framework6TChainINS_10CFiberUnitEEE_02cbb090 + 0x10);
  if (lVar1 == 0) {
    lVar1 = param_1[2];
  }
  else {
    if (*(long **)(lVar1 + 0x10) != param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x31,&UNK_029635d4/*"Previous hasn't myself."*/);
      lVar1 = param_1[1];
    }
    *(long *)(lVar1 + 0x10) = param_1[2];
    lVar1 = param_1[2];
  }
  if (lVar1 != 0) {
    if (*(long **)(lVar1 + 8) != param_1) {
      Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02963548/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/TChain.h"*/,0x36,&UNK_029635ec/*"Next hasn't myself."*/);
      lVar1 = param_1[2];
    }
    *(long *)(lVar1 + 8) = param_1[1];
  }
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}

// ==== Framework::TChain<Framework::CFiberUnit>::~TChain()
// vaddr 0x1e803dc | ghidra 0x1f803dc | size 4 | symbol _ZN9Framework6TChainINS_10CFiberUnitEED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework6TChainINS_10CFiberUnitEED0Ev(void)

{
  code *pcVar1;
  
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x1f803e0);
  (*pcVar1)();
}


// FAILED to create function at 02963600 typeinfo name for Framework::CFiberKernel
// FAILED to create function at 02963620 typeinfo name for Framework::CFiberUnit
// FAILED to create function at 02963640 typeinfo name for Framework::TChain<Framework::CFiberUnit>
// FAILED to create function at 02963670 typeinfo name for Framework::CFiberUnitHandle
// FAILED to create function at 02963690 typeinfo name for Framework::TSimpleHandle<Framework::CFiberUnitHandle>
// FAILED to create function at 02ba8c58 Framework::CFiberKernel::vtable
// FAILED to create function at 02ba8cb8 Framework::CFiberUnit::vtable
// FAILED to create function at 02ba8d18 Framework::TChain<Framework::CFiberUnit>::typeinfo
// FAILED to create function at 02ba8d28 Framework::TSimpleHandle<Framework::CFiberUnitHandle>::typeinfo
// FAILED to create function at 02ba8d40 Framework::CFiberUnitHandle::typeinfo
// FAILED to create function at 02ba8d70 Framework::CFiberUnit::typeinfo
// FAILED to create function at 02ba8dc0 Framework::CFiberKernel::typeinfo
// FAILED to create function at 02ba8dd8 Framework::TChain<Framework::CFiberUnit>::vtable
// FAILED to create function at 02d00468 Framework::TSimpleHandle<Framework::CFiberUnitHandle>::m_MasterHandle
