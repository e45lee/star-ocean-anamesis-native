// port/decomp/kernel/timing.c: Ghidra decompiles for the kernel subsystem. Data, not code: nothing builds this file.
// Written by tools/decomp.sh / decomp_at.sh --into (tools/decomp_stamp.py); one block per function,
// each with its stamp line (vaddr = ELF address, ghidra = vaddr + 0x100000, the ELF symbol, the lib, the date).
// lib      libSOA-3.7.0.so  sha256 698d55b9fdf93c3573b2e71dd614451529e0f396779e5021c68cc423b2b98c5e  (45988160 bytes)
// tool     Ghidra 12.1.2 analyzeHeadless -noanalysis, tools/ghidra_scripts/DecompileMatching.java, tools/resolve_decomp.py
// run      2026-10-04 06:17 UTC: tools/decomp.sh '--into' 'kernel/timing' 'Aska::VSync::' 'Aska::WaitVSync::' 'Aska::WaitDraw::' 'Aska::PerformanceCounter::' 'Framework::CTimeElement::' 'Aska::NotifierThread::' 'Aska::Global::InstantiatePerformanceCounter' 'Aska::Global::GetCPUTime'

// ==== Framework::CTimeElement::CTimeElement()
// vaddr 0x1e9e85c | ghidra 0x1f9e85c | size 56 | symbol _ZN9Framework12CTimeElementC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CTimeElementC2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN9Framework12CTimeElementE_02cbaf88;
  param_1[6] = 0;
  *(undefined1 *)(param_1 + 7) = 0;
  *(undefined8 *)((long)param_1 + 0x3c) = 0;
  param_1[4] = 0;
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[1] = 0;
  *(undefined4 *)(param_1 + 5) = 0;
  *(undefined4 *)((long)param_1 + 0x2c) = 0x3f800000;
  *param_1 = (long)(puVar1 + 0x10);
  *(undefined1 *)((long)param_1 + 0x44) = 0;
  return;
}

// ==== Framework::CTimeElement::Initialize()
// vaddr 0x1e9e894 | ghidra 0x1f9e894 | size 40 | symbol _ZN9Framework12CTimeElement10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CTimeElement10InitializeEv(long param_1)

{
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined1 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x3c) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0x3f800000;
  *(undefined1 *)(param_1 + 0x44) = 0;
  return;
}

// ==== Framework::CTimeElement::~CTimeElement()
// vaddr 0x1e9e8bc | ghidra 0x1f9e8bc | size 44 | symbol _ZN9Framework12CTimeElementD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CTimeElementD2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework12CTimeElementE_02cbaf88 + 0x10);
  Framework::THierarchy<Framework::CTimeElement>::DetachSelf(Framework::CTimeElement*)(param_1,param_1);
  *(undefined1 *)((long)param_1 + 0x44) = 0;
  return;
}

// ==== Framework::CTimeElement::~CTimeElement()
// vaddr 0x1e9e8e8 | ghidra 0x1f9e8e8 | size 44 | symbol _ZN9Framework12CTimeElementD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CTimeElementD0Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN9Framework12CTimeElementE_02cbaf88 + 0x10);
  Framework::THierarchy<Framework::CTimeElement>::DetachSelf(Framework::CTimeElement*)(param_1,param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Framework::CTimeElement::AddChild(Framework::CTimeElement*)
// vaddr 0x1e9e914 | ghidra 0x1f9e914 | size 336 | symbol _ZN9Framework12CTimeElement8AddChildEPS0_ | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CTimeElement8AddChildEPS0_(long param_1,long param_2)

{
  long lVar1;
  long *plVar2;
  float fVar3;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02966694/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/THierarchy.h"*/,0x58,&UNK_029666e8/*"apParent is null"*/);
  }
  if (param_2 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02966694/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/THierarchy.h"*/,0x59,&UNK_029666f9/*"apTarget is null"*/);
    lVar1 = lRam0000000000000008;
  }
  else {
    lVar1 = *(long *)(param_2 + 8);
  }
  if (lVar1 != 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02966694/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/THierarchy.h"*/,0x5a,&UNK_02805036/*"Argument 'target' arleady has parent."*/);
  }
  if (param_2 == param_1) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02966694/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/THierarchy.h"*/,0x5b,&UNK_0296670a/*"Argument 'target' is itself."*/);
  }
  plVar2 = (long *)(param_1 + 0x18);
  lVar1 = *plVar2;
  if (lVar1 != 0) {
    while (plVar2 = (long *)(lVar1 + 0x10), *plVar2 != 0) {
      lVar1 = *plVar2;
    }
  }
  *plVar2 = param_2;
  *(long *)(param_2 + 8) = param_1;
  lVar1 = param_1;
  if (param_1 != 0) goto code_r0x01f9e9a8;
  do {
    fVar3 = 0.0;
    if (*(float *)(param_2 + 0x34) <= 0.0) {
      if (*(float *)(param_2 + 0x3c) <= 0.0) {
        fVar3 = *(float *)(param_2 + 0x2c);
      }
      else {
        fVar3 = *(float *)(param_2 + 0x40);
      }
    }
    while( true ) {
      *(float *)(param_2 + 0x30) = fVar3;
      param_2 = *(long *)(param_2 + 0x18);
      if (param_2 == 0) {
        *(undefined1 *)(param_1 + 0x44) = 0;
        return;
      }
      lVar1 = *(long *)(param_2 + 8);
      if (lVar1 == 0) break;
code_r0x01f9e9a8:
      fVar3 = 0.0;
      if (*(float *)(param_2 + 0x34) <= 0.0) {
        if (0.0 < *(float *)(param_2 + 0x3c)) {
          fVar3 = *(float *)(param_2 + 0x40);
          goto code_r0x01f9e9cc;
        }
        fVar3 = *(float *)(lVar1 + 0x30) * *(float *)(param_2 + 0x2c);
      }
      else {
code_r0x01f9e9cc:
        fVar3 = *(float *)(lVar1 + 0x30) * fVar3;
      }
    }
  } while( true );
}

// ==== Framework::CTimeElement::UpdateDTForce()
// vaddr 0x1e9ea64 | ghidra 0x1f9ea64 | size 120 | symbol _ZN9Framework12CTimeElement13UpdateDTForceEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CTimeElement13UpdateDTForceEv(long param_1)

{
  float fVar1;
  float fVar2;
  
  do {
    if (*(long *)(param_1 + 8) == 0) {
      fVar1 = 0.0;
      if (*(float *)(param_1 + 0x34) <= 0.0) {
        if (*(float *)(param_1 + 0x3c) <= 0.0) {
          fVar1 = *(float *)(param_1 + 0x2c);
        }
        else {
          fVar1 = *(float *)(param_1 + 0x40);
        }
      }
    }
    else {
      fVar1 = *(float *)(*(long *)(param_1 + 8) + 0x30);
      fVar2 = 0.0;
      if (*(float *)(param_1 + 0x34) <= 0.0) {
        if (*(float *)(param_1 + 0x3c) <= 0.0) {
          fVar1 = fVar1 * *(float *)(param_1 + 0x2c);
          goto code_r0x01f9eacc;
        }
        fVar2 = *(float *)(param_1 + 0x40);
      }
      fVar1 = fVar1 * fVar2;
    }
code_r0x01f9eacc:
    *(float *)(param_1 + 0x30) = fVar1;
    param_1 = *(long *)(param_1 + 0x18);
    if (param_1 == 0) {
      return;
    }
  } while( true );
}

// ==== Framework::CTimeElement::DetachFromParent()
// vaddr 0x1e9eadc | ghidra 0x1f9eadc | size 108 | symbol _ZN9Framework12CTimeElement16DetachFromParentEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CTimeElement16DetachFromParentEv(long param_1)

{
  long lVar1;
  long *plVar2;
  
  if (param_1 == 0) {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_02966694/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework/THierarchy.h"*/,0x77,&UNK_02966727/*"apSelf is null"*/);
    lVar1 = lRam0000000000000008;
  }
  else {
    lVar1 = *(long *)(param_1 + 8);
  }
  if (lVar1 != 0) {
    plVar2 = (long *)(lVar1 + 0x18);
    lVar1 = *plVar2;
    while (lVar1 != param_1) {
      plVar2 = (long *)(*plVar2 + 0x10);
      lVar1 = *plVar2;
    }
    *plVar2 = *(long *)(param_1 + 0x10);
  }
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined1 *)(param_1 + 0x44) = 0;
  return;
}

// ==== Framework::CTimeElement::DetachSelf()
// vaddr 0x1e9eb48 | ghidra 0x1f9eb48 | size 28 | symbol _ZN9Framework12CTimeElement10DetachSelfEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CTimeElement10DetachSelfEv(long param_1)

{
  Framework::THierarchy<Framework::CTimeElement>::DetachSelf(Framework::CTimeElement*)(param_1,param_1);
  *(undefined1 *)(param_1 + 0x44) = 0;
  return;
}

// ==== Framework::CTimeElement::Add(float)
// vaddr 0x1e9ec64 | ghidra 0x1f9ec64 | size 268 | symbol _ZN9Framework12CTimeElement3AddEf | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _ZN9Framework12CTimeElement3AddEf(float param_1,long param_2)

{
  long *plVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  long lVar5;
  float fVar6;
  float fVar7;
  
  fVar4 = _UNK_02951634;
  fVar3 = _UNK_027e6ae0;
  do {
    if (*(float *)(param_2 + 0x34) <= 0.0) {
      fVar6 = *(float *)(param_2 + 0x3c);
      pfVar2 = (float *)(param_2 + 0x40);
      if (fVar6 <= 0.0) {
        pfVar2 = (float *)(param_2 + 0x2c);
      }
      fVar7 = *pfVar2;
      *(undefined4 *)(param_2 + 0x34) = 0;
      param_1 = param_1 * fVar7;
      if (0.0 < fVar6) {
        if (*(char *)(param_2 + 0x38) == '\0') {
          *(undefined1 *)(param_2 + 0x38) = 1;
        }
        else {
          *(float *)(param_2 + 0x3c) = fVar6 - param_1;
          lVar5 = param_2;
          if (fVar6 - param_1 <= 0.0) {
            do {
              *(undefined8 *)(lVar5 + 0x3c) = 0;
              *(undefined1 *)(lVar5 + 0x38) = 0;
              plVar1 = (long *)(lVar5 + 0x18);
              lVar5 = *plVar1;
            } while (*plVar1 != 0);
          }
        }
      }
    }
    else {
      pfVar2 = (float *)(param_2 + 0x3c);
      if (*(float *)(param_2 + 0x3c) <= 0.0) {
        pfVar2 = (float *)(param_2 + 0x2c);
      }
      *(float *)(param_2 + 0x34) = *(float *)(param_2 + 0x34) - param_1 * *pfVar2;
      param_1 = param_1 * 0.0;
    }
    fVar6 = *(float *)(param_2 + 0x28);
    if (fVar3 < fVar6) {
      fVar6 = fVar6 + fVar4;
      *(float *)(param_2 + 0x28) = fVar6;
    }
    *(float *)(param_2 + 0x28) = param_1 + fVar6;
    *(float *)(param_2 + 0x30) = (param_1 + fVar6) - fVar6;
    if (*(long *)(param_2 + 0x10) != 0) {
      _ZN9Framework12CTimeElement3AddEf();
    }
    param_2 = *(long *)(param_2 + 0x18);
  } while (param_2 != 0);
  return;
}

// ==== Framework::CTimeElement::DetailRate() const
// vaddr 0x1e9ed70 | ghidra 0x1f9ed70 | size 44 | symbol _ZNK9Framework12CTimeElement10DetailRateEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework12CTimeElement10DetailRateEv(long param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (*(float *)(param_1 + 0x34) <= 0.0) {
    if (*(float *)(param_1 + 0x3c) <= 0.0) {
      return *(undefined4 *)(param_1 + 0x2c);
    }
    uVar1 = *(undefined4 *)(param_1 + 0x40);
  }
  return uVar1;
}

// ==== Framework::CTimeElement::ResetInterpose()
// vaddr 0x1e9ed9c | ghidra 0x1f9ed9c | size 20 | symbol _ZN9Framework12CTimeElement14ResetInterposeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CTimeElement14ResetInterposeEv(long param_1)

{
  do {
    *(undefined8 *)(param_1 + 0x3c) = 0;
    *(undefined1 *)(param_1 + 0x38) = 0;
    param_1 = *(long *)(param_1 + 0x18);
  } while (param_1 != 0);
  return;
}

// ==== Framework::CTimeElement::Rate(float)
// vaddr 0x1e9edb0 | ghidra 0x1f9edb0 | size 8 | symbol _ZN9Framework12CTimeElement4RateEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CTimeElement4RateEf(undefined4 param_1,long param_2)

{
  *(undefined4 *)(param_2 + 0x2c) = param_1;
  return;
}

// ==== Framework::CTimeElement::Rate() const
// vaddr 0x1e9edb8 | ghidra 0x1f9edb8 | size 52 | symbol _ZNK9Framework12CTimeElement4RateEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework12CTimeElement4RateEv(long param_1)

{
  if (*(char *)(param_1 + 0x44) != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029665d1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\TimeElement.cpp"*/,0x93,&UNK_02966628/*"Locked."*/);
  }
  return *(undefined4 *)(param_1 + 0x2c);
}

// ==== Framework::CTimeElement::IsLockTimeElement() const
// vaddr 0x1e9edec | ghidra 0x1f9edec | size 8 | symbol _ZNK9Framework12CTimeElement17IsLockTimeElementEv | lib libSOA-3.7.0.so | 2026-10-04
undefined1 _ZNK9Framework12CTimeElement17IsLockTimeElementEv(long param_1)

{
  return *(undefined1 *)(param_1 + 0x44);
}

// ==== Framework::CTimeElement::DT(float)
// vaddr 0x1e9edf4 | ghidra 0x1f9edf4 | size 64 | symbol _ZN9Framework12CTimeElement2DTEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CTimeElement2DTEf(undefined4 param_1,long param_2)

{
  if (*(char *)(param_2 + 0x44) != '\0') {
    Framework::gDoAssert(char const*, int, char const*, ...)(&UNK_029665d1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\TimeElement.cpp"*/,0x9a,&UNK_02966628/*"Locked."*/);
  }
  *(undefined4 *)(param_2 + 0x30) = param_1;
  return;
}

// ==== Framework::CTimeElement::DT() const
// vaddr 0x1e9ee34 | ghidra 0x1f9ee34 | size 8 | symbol _ZNK9Framework12CTimeElement2DTEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework12CTimeElement2DTEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x30);
}

// ==== Framework::CTimeElement::IsLockTimeElement(bool)
// vaddr 0x1e9ee3c | ghidra 0x1f9ee3c | size 12 | symbol _ZN9Framework12CTimeElement17IsLockTimeElementEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CTimeElement17IsLockTimeElementEb(long param_1,byte param_2)

{
  *(byte *)(param_1 + 0x44) = param_2 & 1;
  return;
}

// ==== Framework::CTimeElement::Suspend(float)
// vaddr 0x1e9ee48 | ghidra 0x1f9ee48 | size 8 | symbol _ZN9Framework12CTimeElement7SuspendEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CTimeElement7SuspendEf(undefined4 param_1,long param_2)

{
  *(undefined4 *)(param_2 + 0x34) = param_1;
  return;
}

// ==== Framework::CTimeElement::AddSuspend(float)
// vaddr 0x1e9ee50 | ghidra 0x1f9ee50 | size 16 | symbol _ZN9Framework12CTimeElement10AddSuspendEf | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CTimeElement10AddSuspendEf(float param_1,long param_2)

{
  *(float *)(param_2 + 0x34) = *(float *)(param_2 + 0x34) + param_1;
  return;
}

// ==== Framework::CTimeElement::Suspend() const
// vaddr 0x1e9ee60 | ghidra 0x1f9ee60 | size 8 | symbol _ZNK9Framework12CTimeElement7SuspendEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework12CTimeElement7SuspendEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x34);
}

// ==== Framework::CTimeElement::Interpose(float, float)
// vaddr 0x1e9ee68 | ghidra 0x1f9ee68 | size 144 | symbol _ZN9Framework12CTimeElement9InterposeEff | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CTimeElement9InterposeEff(float param_1,float param_2,long param_3)

{
  if (param_1 == 0.0) {
    do {
      *(undefined8 *)(param_3 + 0x3c) = 0;
      *(undefined1 *)(param_3 + 0x38) = 0;
      param_3 = *(long *)(param_3 + 0x18);
    } while (param_3 != 0);
  }
  else {
    if (param_2 <= 0.0) {
      Framework::gDoAssert(char const*, int, char const*, ...)((double)param_2,&UNK_029665d1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\TimeElement.cpp"*/,0xe9,&UNK_02966630/*"The argument 'rate' has gotten illegal value.(%f)"*/);
    }
    if (param_1 <= 0.0) {
      Framework::gDoAssert(char const*, int, char const*, ...)((double)param_1,&UNK_029665d1/*"C:\BAS_Submission\Client\Library\Framework\Project\..\Source\Framework\TimeElement.cpp"*/,0xea,&UNK_02966662/*"The argument 'time' has gotten illegal value.(%f)"*/);
    }
    *(float *)(param_3 + 0x3c) = param_1 * param_2;
    *(float *)(param_3 + 0x40) = param_2;
    *(undefined1 *)(param_3 + 0x38) = 0;
  }
  return;
}

// ==== Framework::CTimeElement::IsInterpose() const
// vaddr 0x1e9eef8 | ghidra 0x1f9eef8 | size 16 | symbol _ZNK9Framework12CTimeElement11IsInterposeEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZNK9Framework12CTimeElement11IsInterposeEv(long param_1)

{
  return 0.0 < *(float *)(param_1 + 0x3c);
}

// ==== Framework::CTimeElement::InterposeRate() const
// vaddr 0x1e9ef08 | ghidra 0x1f9ef08 | size 8 | symbol _ZNK9Framework12CTimeElement13InterposeRateEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework12CTimeElement13InterposeRateEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x40);
}

// ==== Framework::CTimeElement::InterposeTime() const
// vaddr 0x1e9ef10 | ghidra 0x1f9ef10 | size 8 | symbol _ZNK9Framework12CTimeElement13InterposeTimeEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK9Framework12CTimeElement13InterposeTimeEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x3c);
}

// ==== Framework::CTimeElement::PrintS() const
// vaddr 0x1e9ef18 | ghidra 0x1f9ef18 | size 4 | symbol _ZNK9Framework12CTimeElement6PrintSEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK9Framework12CTimeElement6PrintSEv(void)

{
  return;
}

// ==== Framework::CTimeElement::IsCheckParentExist(bool)
// vaddr 0x1e9ef1c | ghidra 0x1f9ef1c | size 4 | symbol _ZN9Framework12CTimeElement18IsCheckParentExistEb | lib libSOA-3.7.0.so | 2026-10-04
void _ZN9Framework12CTimeElement18IsCheckParentExistEb(void)

{
  return;
}

// ==== Aska::Global::InstantiatePerformanceCounter()
// vaddr 0x1f56e5c | ghidra 0x2056e5c | size 172 | symbol _ZN4Aska6Global29InstantiatePerformanceCounterEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska6Global29InstantiatePerformanceCounterEv(void)

{
  undefined *puVar1;
  undefined8 uVar2;
  long *plVar3;
  long lStack_30;
  long lStack_28;
  
  puVar1 = PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8;
  if (*(long *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8 == 0) {
    plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x260,PTR__ZSt7nothrow_02cb9a80);
    if (plVar3 != (long *)0x0) {
      *plVar3 = (long)(PTR__ZTVN4Aska18PerformanceCounterE_02cba338 + 0x10);
      plVar3[1] = 0x3f50624dd2f1a9fc;
      memset(plVar3 + 2,0,0x248);
      clock_gettime(1,&lStack_30);
      plVar3[0x4a] = (lStack_28 + lStack_30 * 1000000000) - plVar3[0x4a];
    }
    uVar2 = 1;
    *(long **)puVar1 = plVar3;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

// ==== Aska::PerformanceCounter::PerformanceCounter()
// vaddr 0x1f56f34 | ghidra 0x2056f34 | size 112 | symbol _ZN4Aska18PerformanceCounterC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18PerformanceCounterC2Ev(long *param_1)

{
  long lStack_20;
  long lStack_18;
  
  *param_1 = (long)(PTR__ZTVN4Aska18PerformanceCounterE_02cba338 + 0x10);
  param_1[1] = 0x3f50624dd2f1a9fc;
  memset(param_1 + 2,0,0x248);
  clock_gettime(1,&lStack_20);
  param_1[0x4a] = (lStack_18 + lStack_20 * 1000000000) - param_1[0x4a];
  return;
}

// ==== Aska::PerformanceCounter::~PerformanceCounter()
// vaddr 0x1f56fa4 | ghidra 0x2056fa4 | size 4 | symbol _ZN4Aska18PerformanceCounterD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18PerformanceCounterD1Ev(void)

{
  return;
}

// ==== Aska::PerformanceCounter::~PerformanceCounter()
// vaddr 0x1f56fa8 | ghidra 0x2056fa8 | size 4 | symbol _ZN4Aska18PerformanceCounterD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18PerformanceCounterD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}

// ==== Aska::PerformanceCounter::Mark(int)
// vaddr 0x1f56fac | ghidra 0x2056fac | size 56 | symbol _ZN4Aska18PerformanceCounter4MarkEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18PerformanceCounter4MarkEi(long param_1,int param_2)

{
  long lStack_20;
  long lStack_18;
  
  clock_gettime(1,&lStack_20);
  *(long *)(param_1 + (long)param_2 * 8 + 0x10) = lStack_18 + lStack_20 * 1000000000;
  return;
}

// ==== Aska::PerformanceCounter::Set(int)
// vaddr 0x1f56fe4 | ghidra 0x2056fe4 | size 104 | symbol _ZN4Aska18PerformanceCounter3SetEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18PerformanceCounter3SetEi(long param_1,int param_2)

{
  long lStack_30;
  long lStack_28;
  
  clock_gettime(1,&lStack_30);
  *(int *)(param_1 + (long)param_2 * 4 + 400) =
       (int)(*(double *)(param_1 + 8) *
            (double)((lStack_28 + lStack_30 * 1000000000) -
                    *(long *)(param_1 + (long)param_2 * 8 + 0x10)));
  return;
}

// ==== Aska::PerformanceCounter::Set(int, long)
// vaddr 0x1f5704c | ghidra 0x205704c | size 96 | symbol _ZN4Aska18PerformanceCounter3SetEil | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18PerformanceCounter3SetEil(long param_1,int param_2,long param_3)

{
  long lStack_30;
  long lStack_28;
  
  clock_gettime(1,&lStack_30);
  *(int *)(param_1 + (long)param_2 * 4 + 400) =
       (int)(*(double *)(param_1 + 8) * (double)((lStack_28 - param_3) + lStack_30 * 1000000000));
  return;
}

// ==== Aska::PerformanceCounter::AddSet(int)
// vaddr 0x1f570ac | ghidra 0x20570ac | size 108 | symbol _ZN4Aska18PerformanceCounter6AddSetEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska18PerformanceCounter6AddSetEi(long param_1,int param_2)

{
  long lVar1;
  long lStack_30;
  long lStack_28;
  
  clock_gettime(1,&lStack_30);
  lVar1 = param_1 + (long)param_2 * 4;
  *(int *)(lVar1 + 400) =
       *(int *)(lVar1 + 400) +
       (int)(*(double *)(param_1 + 8) *
            (double)((lStack_28 + lStack_30 * 1000000000) -
                    *(long *)(param_1 + (long)param_2 * 8 + 0x10)));
  return;
}

// ==== Aska::PerformanceCounter::GetMark(int) const
// vaddr 0x1f57118 | ghidra 0x2057118 | size 12 | symbol _ZNK4Aska18PerformanceCounter7GetMarkEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska18PerformanceCounter7GetMarkEi(long param_1,int param_2)

{
  return *(undefined8 *)(param_1 + (long)param_2 * 8 + 0x10);
}

// ==== Aska::PerformanceCounter::GetAvailableTotalMemorySize() const
// vaddr 0x1f57124 | ghidra 0x2057124 | size 32 | symbol _ZNK4Aska18PerformanceCounter27GetAvailableTotalMemorySizeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska18PerformanceCounter27GetAvailableTotalMemorySizeEv(void)

{
  long lVar1;
  
  lVar1 = Aska::Global::GetAvailableMemoryManager()();
  if (lVar1 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager12CalcFreeSizeEb_02caf290)(lVar1,0);
    return;
  }
  return;
}

// ==== Aska::PerformanceCounter::GetAvailableMemorySize() const
// vaddr 0x1f57144 | ghidra 0x2057144 | size 32 | symbol _ZNK4Aska18PerformanceCounter22GetAvailableMemorySizeEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZNK4Aska18PerformanceCounter22GetAvailableMemorySizeEv(void)

{
  long lVar1;
  
  lVar1 = Aska::Global::GetAvailableMemoryManager()();
  if (lVar1 != 0) {
    (*(code *)PTR__ZN4Aska13MemoryManager12CalcFreeSizeEb_02caf290)(lVar1,0);
    return;
  }
  return;
}

// ==== Aska::PerformanceCounter::GetMemorySizeSystem(long*, long*) const
// vaddr 0x1f57164 | ghidra 0x2057164 | size 8 | symbol _ZNK4Aska18PerformanceCounter19GetMemorySizeSystemEPlS1_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska18PerformanceCounter19GetMemorySizeSystemEPlS1_(void)

{
  return 0;
}

// ==== Aska::VSync::VSync(int)
// vaddr 0x1f8d328 | ghidra 0x208d328 | size 80 | symbol _ZN4Aska5VSyncC1Ei | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5VSyncC2Ei(long *param_1)

{
  undefined *puVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska6IVSyncE_02cb8dc0 + 0x10);
  Aska::NotifierThread::NotifierThread(int)(param_1 + 1);
  puVar1 = PTR__ZTVN4Aska5VSyncE_02cbd050;
  param_1[0x26] = 0xf0000003c;
  param_1[1] = (long)(puVar1 + 0x50);
  *param_1 = (long)(puVar1 + 0x10);
  return;
}

// ==== Aska::VSync::Initialize()
// vaddr 0x1f8d378 | ghidra 0x208d378 | size 160 | symbol _ZN4Aska5VSync10InitializeEv | lib libSOA-3.7.0.so | 2026-10-04
bool _ZN4Aska5VSync10InitializeEv(long param_1)

{
  bool bVar1;
  ulong uVar2;
  
  memset(param_1 + 0xc0,0,0x6c);
  *(undefined8 *)(param_1 + 0x144) = 0;
  *(undefined8 *)(param_1 + 0x154) = 0;
  *(undefined8 *)(param_1 + 0x14c) = 0;
  *(undefined4 *)(param_1 + 300) = 0x3f800000;
  uVar2 = Aska::Event::Create(bool, bool)(PTR__ZN4Aska5VSync7m_eventE_02cc10a8,0,0);
  bVar1 = (uVar2 & 1) != 0;
  if (bVar1) {
    *(undefined8 *)(param_1 + 0x13c) = 0;
    *(undefined4 *)(param_1 + 0x15c) = 0;
    *(undefined1 *)(param_1 + 0x138) = 0;
    Aska::VideoManager::SetVSyncCallback(void (*)())(*(undefined8 *)PTR__ZN4Aska6Global15m_pVideoManagerE_02cbe250,
                    PTR__ZN4Aska11VSyncGlobal13VSyncCallbackEv_02cbebc0);
    Aska::Event::Set() const(PTR__ZN4Aska5VSync10m_evRTSyncE_02cb9d30);
  }
  return bVar1;
}

// ==== Aska::VSync::VSyncCallback_Enable()
// vaddr 0x1f8d418 | ghidra 0x208d418 | size 40 | symbol _ZN4Aska5VSync20VSyncCallback_EnableEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZN4Aska5VSync20VSyncCallback_EnableEv(void)

{
  Aska::VideoManager::SetVSyncCallback(void (*)())(*(undefined8 *)PTR__ZN4Aska6Global15m_pVideoManagerE_02cbe250,
                  PTR__ZN4Aska11VSyncGlobal13VSyncCallbackEv_02cbebc0);
  return 1;
}

// ==== Aska::VSync::WakeupForInitRenderThread()
// vaddr 0x1f8d440 | ghidra 0x208d440 | size 12 | symbol _ZN4Aska5VSync25WakeupForInitRenderThreadEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5VSync25WakeupForInitRenderThreadEv(void)

{
  (*(code *)PTR__ZNK4Aska5Event3SetEv_02c9dcf0)(PTR__ZN4Aska5VSync10m_evRTSyncE_02cb9d30);
  return;
}

// ==== Aska::VSync::InitializeForAndroid()
// vaddr 0x1f8d44c | ghidra 0x208d44c | size 100 | symbol _ZN4Aska5VSync20InitializeForAndroidEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5VSync20InitializeForAndroidEv(void)

{
  undefined *puVar1;
  
  if (*(long *)PTR__ZN4Aska5VSync8m_evSyncE_02cbe9f8 == 0) {
    Aska::Event::Create(bool, bool)(PTR__ZN4Aska5VSync8m_evSyncE_02cbe9f8,1,1);
  }
  puVar1 = PTR__ZN4Aska5VSync10m_evRTSyncE_02cb9d30;
  if (*(long *)PTR__ZN4Aska5VSync10m_evRTSyncE_02cb9d30 != 0) {
    return;
  }
  Aska::Event::Create(bool, bool)(PTR__ZN4Aska5VSync10m_evRTSyncE_02cb9d30,1,0);
  (*(code *)PTR__ZNK4Aska5Event5ResetEv_02ca2b60)(puVar1);
  return;
}

// ==== Aska::VSync::WaitForInitRenderThread()
// vaddr 0x1f8d4b0 | ghidra 0x208d4b0 | size 16 | symbol _ZN4Aska5VSync23WaitForInitRenderThreadEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5VSync23WaitForInitRenderThreadEv(void)

{
  (*(code *)PTR__ZNK4Aska5Event4WaitEj_02c992c0)(PTR__ZN4Aska5VSync10m_evRTSyncE_02cb9d30,0);
  return;
}

// ==== Aska::VSync::Exit()
// vaddr 0x1f8d4c0 | ghidra 0x208d4c0 | size 20 | symbol _ZN4Aska5VSync4ExitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5VSync4ExitEv(void)

{
  (*(code *)PTR__ZN4Aska12VideoManager16SetVSyncCallbackEPFvvE_02c9eba8)
            (*(undefined8 *)PTR__ZN4Aska6Global15m_pVideoManagerE_02cbe250,0);
  return;
}

// ==== Aska::VSync::VSyncCallback_Disable()
// vaddr 0x1f8d4d4 | ghidra 0x208d4d4 | size 20 | symbol _ZN4Aska5VSync21VSyncCallback_DisableEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5VSync21VSyncCallback_DisableEv(void)

{
  (*(code *)PTR__ZN4Aska12VideoManager16SetVSyncCallbackEPFvvE_02c9eba8)
            (*(undefined8 *)PTR__ZN4Aska6Global15m_pVideoManagerE_02cbe250,0);
  return;
}

// ==== Aska::VSync::GetVSyncCounter() const
// vaddr 0x1f8d504 | ghidra 0x208d504 | size 16 | symbol _ZNK4Aska5VSync15GetVSyncCounterEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska5VSync15GetVSyncCounterEv(void)

{
  return *(undefined4 *)PTR__ZN4Aska5VSync15m_nVSyncCounterE_02cb71d8;
}

// ==== Aska::VSync::WaitVSync(int, int)
// vaddr 0x1f8d514 | ghidra 0x208d514 | size 292 | symbol _ZN4Aska5VSync9WaitVSyncEii | lib libSOA-3.7.0.so | 2026-10-04
int _ZN4Aska5VSync9WaitVSyncEii(long param_1,int param_2,int param_3)

{
  long lVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  
  if (param_2 < 0) {
    return 0;
  }
  if (param_3 < 0) {
    iVar6 = *(int *)PTR__ZN4Aska5VSync15m_nVSyncCounterE_02cb71d8;
    if (param_2 == 0) goto code_r0x0208d574;
code_r0x0208d538:
    param_2 = param_2 + iVar6;
    if (param_3 != 0) goto code_r0x0208d540;
code_r0x0208d588:
    iVar5 = Aska::VSync::UpdateVSyncEvents(unsigned int, unsigned int, int, bool)(param_1,*(undefined4 *)PTR__ZN4Aska5VSync15m_nVSyncCounterE_02cb71d8,
                            param_2,0,0);
  }
  else {
    iVar6 = *(int *)(param_1 + (long)param_3 * 4 + 0xc0);
    if (param_2 != 0) goto code_r0x0208d538;
code_r0x0208d574:
    uVar4 = 0;
    if (*(uint *)(param_1 + 0x130) != 0) {
      uVar4 = 0x3c / *(uint *)(param_1 + 0x130);
    }
    param_2 = uVar4 + iVar6;
    if (param_3 == 0) goto code_r0x0208d588;
code_r0x0208d540:
    iVar5 = Aska::VSync::UpdateVSyncEvents(unsigned int, unsigned int, int, bool)(param_1,0,param_2,param_3,0);
    if (param_3 < 0) goto code_r0x0208d628;
  }
  lVar1 = param_1 + (long)param_3 * 4;
  iVar2 = *(int *)(lVar1 + 0xc0);
  *(int *)(lVar1 + 0xc0) = iVar5;
  *(int *)(lVar1 + 0xd8) = iVar2;
  uVar3 = iVar5 - iVar2;
  uVar4 = 0;
  if (*(uint *)(param_1 + 0x134) != 0) {
    uVar4 = 0x3c / *(uint *)(param_1 + 0x134);
  }
  if ((int)uVar3 <= (int)uVar4) {
    uVar4 = uVar3;
  }
  *(short *)(param_1 + (long)param_3 * 2 + 0xf0) = (short)uVar4;
  if (uVar4 == 0) {
    fVar7 = 0.0;
  }
  else {
    fVar7 = 1.0 / (float)(int)uVar4;
  }
  lVar1 = param_1 + (long)param_3 * 4;
  *(float *)(lVar1 + 0xfc) = fVar7;
  if (*(char *)(param_1 + 0x138) == '\0') {
    fVar7 = (float)(int)uVar4 /
            *(float *)(*(long *)PTR__ZN4Aska6Global15m_pVideoManagerE_02cbe250 + 0x10);
  }
  else {
    fVar7 = *(float *)(lVar1 + 0x144);
  }
  *(float *)(param_1 + (long)param_3 * 4 + 0x114) = fVar7;
code_r0x0208d628:
  return iVar5 - iVar6;
}

// ==== Aska::VSync::UpdateVSyncEvents(unsigned int, unsigned int, int, bool)
// vaddr 0x1f8d638 | ghidra 0x208d638 | size 620 | symbol _ZN4Aska5VSync17UpdateVSyncEventsEjjib | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 _ZN4Aska5VSync17UpdateVSyncEventsEjjib(long param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int aiStack_50 [2];
  long lStack_48;
  
  uVar1 = *(uint *)(param_1 + 0x130);
  clock_gettime(1,aiStack_50);
  iVar6 = *(int *)(param_1 + 0x140);
  if (iVar6 == 0) goto code_r0x0208d844;
  uVar3 = 0;
  if (*(uint *)(param_1 + 0x130) != 0) {
    uVar3 = 1000000 / *(uint *)(param_1 + 0x130);
  }
  iVar7 = ((int)(SUB168(SEXT816(lStack_48) * SEXT816(0x20c49ba5e353f7cf),8) >> 7) -
          (SUB164(SEXT816(lStack_48) * SEXT816(0x20c49ba5e353f7cf),0xc) >> 0x1f)) +
          aiStack_50[0] * 1000000;
  iVar8 = iVar7 - iVar6;
  param_3 = param_3 - param_2;
  if (*(char *)(param_1 + 0x138) == '\0') {
    uVar4 = 0;
    if (uVar1 != 0) {
      uVar4 = 0x3c / uVar1;
    }
    iVar2 = uVar4 * 0x411b;
    if (0 < iVar8 && 0 < (int)(uVar3 - iVar8)) {
      Aska::Thread::SleepU(unsigned int)();
      clock_gettime(1,aiStack_50);
      iVar6 = *(int *)(param_1 + 0x140);
      iVar7 = ((int)(SUB168(SEXT816(lStack_48) * SEXT816(0x20c49ba5e353f7cf),8) >> 7) -
              (SUB164(SEXT816(lStack_48) * SEXT816(0x20c49ba5e353f7cf),0xc) >> 0x1f)) +
              aiStack_50[0] * 1000000;
    }
    iVar6 = ((iVar7 + uVar4 * -0x411b) - iVar6) + *(int *)(param_1 + 0x15c);
    iVar7 = 0;
    if (iVar2 != 0) {
      iVar7 = iVar6 / iVar2;
    }
    iVar8 = -iVar7;
    if (-1 < iVar7) {
      iVar8 = iVar7;
    }
    *(int *)(param_1 + 0x15c) = iVar6;
    if (iVar6 < iVar2) {
      if (iVar6 <= (int)(uVar4 * -0x411b)) {
        *(int *)(param_1 + 0x15c) = iVar6 + iVar8 * iVar2;
        iVar6 = *(int *)PTR__ZN4Aska5VSync15m_nVSyncCounterE_02cb71d8 - iVar8 * param_3;
        goto code_r0x0208d80c;
      }
    }
    else {
      *(int *)(param_1 + 0x15c) = iVar6 - iVar8 * iVar2;
      iVar6 = *(int *)PTR__ZN4Aska5VSync15m_nVSyncCounterE_02cb71d8 + iVar8 * param_3;
code_r0x0208d80c:
      *(int *)PTR__ZN4Aska5VSync15m_nVSyncCounterE_02cb71d8 = iVar6;
    }
    *(int *)PTR__ZN4Aska5VSync15m_nVSyncCounterE_02cb71d8 =
         *(int *)PTR__ZN4Aska5VSync15m_nVSyncCounterE_02cb71d8 + param_3;
  }
  else {
    if (0 < iVar8 && 0 < (int)(uVar3 - iVar8)) {
      Aska::Thread::SleepU(unsigned int)();
      clock_gettime(1,aiStack_50);
      iVar8 = (((int)(SUB168(SEXT816(lStack_48) * SEXT816(0x20c49ba5e353f7cf),8) >> 7) -
               (SUB164(SEXT816(lStack_48) * SEXT816(0x20c49ba5e353f7cf),0xc) >> 0x1f)) +
              aiStack_50[0] * 1000000) - *(int *)(param_1 + 0x140);
    }
    puVar5 = PTR__ZN4Aska5VSync15m_nVSyncCounterE_02cb71d8;
    *(float *)(param_1 + (long)param_4 * 4 + 0x144) = (float)iVar8 * _UNK_027e519c;
    *(int *)puVar5 = *(int *)puVar5 + param_3;
  }
  if (*(long *)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460 != 0) {
    Aska::Semaphore::Signal() const(*(long *)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460 + 0x60);
  }
code_r0x0208d844:
  Aska::Event::Wait(unsigned int) const(PTR__ZN4Aska5VSync8m_evSyncE_02cbe9f8,0);
  clock_gettime(1,aiStack_50);
  *(int *)(param_1 + 0x140) =
       ((int)(SUB168(SEXT816(lStack_48) * SEXT816(0x20c49ba5e353f7cf),8) >> 7) -
       (SUB164(SEXT816(lStack_48) * SEXT816(0x20c49ba5e353f7cf),0xc) >> 0x1f)) +
       aiStack_50[0] * 1000000;
  return *(undefined4 *)PTR__ZN4Aska5VSync15m_nVSyncCounterE_02cb71d8;
}

// ==== Aska::VSync::CalcDtAndDFrame(int, unsigned int)
// vaddr 0x1f8d8a4 | ghidra 0x208d8a4 | size 140 | symbol _ZN4Aska5VSync15CalcDtAndDFrameEij | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5VSync15CalcDtAndDFrameEij(long param_1,int param_2,int param_3)

{
  long lVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  float fVar5;
  
  if (-1 < param_2) {
    lVar1 = param_1 + (long)param_2 * 4;
    iVar2 = *(int *)(lVar1 + 0xc0);
    *(int *)(lVar1 + 0xc0) = param_3;
    *(int *)(lVar1 + 0xd8) = iVar2;
    uVar3 = param_3 - iVar2;
    uVar4 = 0;
    if (*(uint *)(param_1 + 0x134) != 0) {
      uVar4 = 0x3c / *(uint *)(param_1 + 0x134);
    }
    if ((int)uVar3 <= (int)uVar4) {
      uVar4 = uVar3;
    }
    *(short *)(param_1 + (long)param_2 * 2 + 0xf0) = (short)uVar4;
    if (uVar4 == 0) {
      fVar5 = 0.0;
    }
    else {
      fVar5 = 1.0 / (float)(int)uVar4;
    }
    lVar1 = param_1 + (long)param_2 * 4;
    *(float *)(lVar1 + 0xfc) = fVar5;
    if (*(char *)(param_1 + 0x138) == '\0') {
      fVar5 = (float)(int)uVar4 /
              *(float *)(*(long *)PTR__ZN4Aska6Global15m_pVideoManagerE_02cbe250 + 0x10);
    }
    else {
      fVar5 = *(float *)(lVar1 + 0x144);
    }
    *(float *)(param_1 + (long)param_2 * 4 + 0x114) = fVar5;
  }
  return;
}

// ==== Aska::VSync::UpdateDt(int)
// vaddr 0x1f8d930 | ghidra 0x208d930 | size 152 | symbol _ZN4Aska5VSync8UpdateDtEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5VSync8UpdateDtEi(long param_1,int param_2)

{
  long lVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  float fVar6;
  
  iVar2 = *(int *)PTR__ZN4Aska5VSync15m_nVSyncCounterE_02cb71d8;
  if (-1 < param_2) {
    lVar1 = param_1 + (long)param_2 * 4;
    iVar3 = *(int *)(lVar1 + 0xc0);
    *(int *)(lVar1 + 0xc0) = iVar2;
    *(int *)(lVar1 + 0xd8) = iVar3;
    uVar4 = iVar2 - iVar3;
    uVar5 = 0;
    if (*(uint *)(param_1 + 0x134) != 0) {
      uVar5 = 0x3c / *(uint *)(param_1 + 0x134);
    }
    if ((int)uVar4 <= (int)uVar5) {
      uVar5 = uVar4;
    }
    *(short *)(param_1 + (long)param_2 * 2 + 0xf0) = (short)uVar5;
    if (uVar5 == 0) {
      fVar6 = 0.0;
    }
    else {
      fVar6 = 1.0 / (float)(int)uVar5;
    }
    lVar1 = param_1 + (long)param_2 * 4;
    *(float *)(lVar1 + 0xfc) = fVar6;
    if (*(char *)(param_1 + 0x138) == '\0') {
      fVar6 = (float)(int)uVar5 /
              *(float *)(*(long *)PTR__ZN4Aska6Global15m_pVideoManagerE_02cbe250 + 0x10);
    }
    else {
      fVar6 = *(float *)(lVar1 + 0x144);
    }
    *(float *)(param_1 + (long)param_2 * 4 + 0x114) = fVar6;
  }
  return;
}

// ==== Aska::VSync::Notify()
// vaddr 0x1f8d9c8 | ghidra 0x208d9c8 | size 8 | symbol _ZN4Aska5VSync6NotifyEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5VSync6NotifyEv(long param_1)

{
  (*(code *)PTR__ZN4Aska14NotifierThread6NotifyEv_02cb3698)(param_1 + 8);
  return;
}

// ==== non-virtual thunk to Aska::VSync::Notify()
// vaddr 0x1f8d9d0 | ghidra 0x208d9d0 | size 4 | symbol _ZThn8_N4Aska5VSync6NotifyEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn8_N4Aska5VSync6NotifyEv(void)

{
  (*(code *)PTR__ZN4Aska14NotifierThread6NotifyEv_02cb3698)();
  return;
}

// ==== Aska::VSync::GetDt(int) const
// vaddr 0x1f8d9d4 | ghidra 0x208d9d4 | size 32 | symbol _ZNK4Aska5VSync5GetDtEi | lib libSOA-3.7.0.so | 2026-10-04
float _ZNK4Aska5VSync5GetDtEi(long param_1,uint param_2)

{
  float fVar1;
  
  fVar1 = 0.0;
  if (param_2 < 6) {
    fVar1 = *(float *)(param_1 + (long)(int)param_2 * 4 + 0x114) * *(float *)(param_1 + 300);
  }
  return fVar1;
}

// ==== Aska::VSync::GetBasicFrameRate() const
// vaddr 0x1f8d9f4 | ghidra 0x208d9f4 | size 8 | symbol _ZNK4Aska5VSync17GetBasicFrameRateEv | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZNK4Aska5VSync17GetBasicFrameRateEv(long param_1)

{
  return *(undefined4 *)(param_1 + 0x130);
}

// ==== Aska::VSync::~VSync()
// vaddr 0x1f8d9fc | ghidra 0x208d9fc | size 68 | symbol _ZN4Aska5VSyncD2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5VSyncD2Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska5VSyncE_02cbd050 + 0x10;
  param_1[1] = (long)(PTR__ZTVN4Aska5VSyncE_02cbd050 + 0x50);
  *param_1 = (long)puVar1;
  Aska::VideoManager::SetVSyncCallback(void (*)())(*(undefined8 *)PTR__ZN4Aska6Global15m_pVideoManagerE_02cbe250,0);
  (*(code *)PTR__ZN4Aska14NotifierThreadD2Ev_02ca2268)(param_1 + 1);
  return;
}

// ==== Aska::VSync::~VSync()
// vaddr 0x1f8da40 | ghidra 0x208da40 | size 88 | symbol _ZN4Aska5VSyncD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska5VSyncD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska5VSyncE_02cbd050 + 0x10;
  param_1[1] = (long)(PTR__ZTVN4Aska5VSyncE_02cbd050 + 0x50);
  *param_1 = (long)puVar1;
  Aska::VideoManager::SetVSyncCallback(void (*)())(*(undefined8 *)PTR__ZN4Aska6Global15m_pVideoManagerE_02cbe250,0);
  Aska::NotifierThread::~NotifierThread()(param_1 + 1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::VSync::~VSync()
// vaddr 0x1f8da98 | ghidra 0x208da98 | size 68 | symbol _ZThn8_N4Aska5VSyncD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn8_N4Aska5VSyncD1Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska5VSyncE_02cbd050 + 0x10;
  *param_1 = (long)(PTR__ZTVN4Aska5VSyncE_02cbd050 + 0x50);
  param_1[-1] = (long)puVar1;
  Aska::VideoManager::SetVSyncCallback(void (*)())(*(undefined8 *)PTR__ZN4Aska6Global15m_pVideoManagerE_02cbe250,0);
  (*(code *)PTR__ZN4Aska14NotifierThreadD2Ev_02ca2268)(param_1);
  return;
}

// ==== non-virtual thunk to Aska::VSync::~VSync()
// vaddr 0x1f8dadc | ghidra 0x208dadc | size 88 | symbol _ZThn8_N4Aska5VSyncD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZThn8_N4Aska5VSyncD0Ev(long *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR__ZTVN4Aska5VSyncE_02cbd050 + 0x10;
  *param_1 = (long)(PTR__ZTVN4Aska5VSyncE_02cbd050 + 0x50);
  param_1[-1] = (long)puVar1;
  Aska::VideoManager::SetVSyncCallback(void (*)())(*(undefined8 *)PTR__ZN4Aska6Global15m_pVideoManagerE_02cbe250,0);
  Aska::NotifierThread::~NotifierThread()(param_1);
  (*(code *)PTR__ZdlPv_02ca4758)(param_1 + -1);
  return;
}

// ==== Aska::NotifierThread::GetThreadPriority() const
// vaddr 0x1f8db34 | ghidra 0x208db34 | size 8 | symbol _ZNK4Aska14NotifierThread17GetThreadPriorityEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska14NotifierThread17GetThreadPriorityEv(void)

{
  return 0xd4;
}

// ==== Aska::NotifierThread::GetThreadName() const
// vaddr 0x1f8db3c | ghidra 0x208db3c | size 8 | symbol _ZNK4Aska14NotifierThread13GetThreadNameEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska14NotifierThread13GetThreadNameEv(void)

{
  return 0;
}

// ==== Aska::WaitDraw::WaitDraw()
// vaddr 0x21697a4 | ghidra 0x22697a4 | size 192 | symbol _ZN4Aska8WaitDrawC1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8WaitDrawC2Ev(long *param_1)

{
  undefined4 uVar1;
  long lVar2;
  long *plVar3;
  code *pcVar4;
  
  pcVar4 = *(code **)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x68);
  *param_1 = (long)(PTR__ZTVN4Aska4TaskE_02cbe020 + 0x10);
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined2 *)((long)param_1 + 0x24) = 0;
  *(undefined1 *)((long)param_1 + 0x26) = 0;
  uVar1 = (*pcVar4)();
  *(undefined4 *)(param_1 + 4) = uVar1;
  *param_1 = (long)(PTR__ZTVN4Aska8WaitDrawE_02cc4e90 + 0x10);
  lVar2 = operator new(unsigned long, std::nothrow_t const&)(0x18,PTR__ZSt7nothrow_02cb9a80);
  if (lVar2 != 0) {
    Aska::Semaphore::Semaphore()(lVar2);
  }
  param_1[5] = lVar2;
  Aska::Semaphore::Create(int, int)(lVar2,0,1);
  plVar3 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x10,PTR__ZSt7nothrow_02cb9a80);
  if (plVar3 != (long *)0x0) {
    lVar2 = param_1[5];
    *plVar3 = (long)(PTR__ZTVN4Aska15SemaphoreNotifyE_02cb73d8 + 0x10);
    plVar3[1] = lVar2;
  }
  param_1[6] = (long)plVar3;
  *(long **)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x4458) = plVar3;
  return;
}

// ==== Aska::WaitDraw::Instantiate()
// vaddr 0x2169864 | ghidra 0x2269864 | size 268 | symbol _ZN4Aska8WaitDraw11InstantiateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8WaitDraw11InstantiateEv(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined4 uVar3;
  long *plVar4;
  long lVar5;
  long *plVar6;
  code *pcVar7;
  
  puVar1 = PTR__ZN4Aska8WaitDraw12m_pSingleTonE_02cb77d0;
  if (*(long **)PTR__ZN4Aska8WaitDraw12m_pSingleTonE_02cb77d0 != (long *)0x0) {
    (**(code **)(**(long **)PTR__ZN4Aska8WaitDraw12m_pSingleTonE_02cb77d0 + 8))();
    *(undefined8 *)puVar1 = 0;
  }
  plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x38,PTR__ZSt7nothrow_02cb9a80);
  puVar2 = PTR__ZTVN4Aska4TaskE_02cbe020;
  if (plVar4 != (long *)0x0) {
    plVar4[2] = 0;
    plVar4[3] = 0;
    *(undefined2 *)((long)plVar4 + 0x24) = 0;
    pcVar7 = *(code **)(puVar2 + 0x68);
    *plVar4 = (long)(puVar2 + 0x10);
    plVar4[1] = 0;
    *(undefined1 *)((long)plVar4 + 0x26) = 0;
    uVar3 = (*pcVar7)(plVar4);
    *(undefined4 *)(plVar4 + 4) = uVar3;
    *plVar4 = (long)(PTR__ZTVN4Aska8WaitDrawE_02cc4e90 + 0x10);
    lVar5 = operator new(unsigned long, std::nothrow_t const&)(0x18,PTR__ZSt7nothrow_02cb9a80);
    if (lVar5 != 0) {
      Aska::Semaphore::Semaphore()(lVar5);
    }
    plVar4[5] = lVar5;
    Aska::Semaphore::Create(int, int)(lVar5,0,1);
    plVar6 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x10,PTR__ZSt7nothrow_02cb9a80);
    if (plVar6 != (long *)0x0) {
      lVar5 = plVar4[5];
      *plVar6 = (long)(PTR__ZTVN4Aska15SemaphoreNotifyE_02cb73d8 + 0x10);
      plVar6[1] = lVar5;
    }
    puVar2 = PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
    plVar4[6] = (long)plVar6;
    *(long **)(*(long *)puVar2 + 0x4458) = plVar6;
  }
  puVar2 = PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620;
  *(long **)puVar1 = plVar4;
  (*(code *)PTR__ZN4Aska11TaskManager6AddTopEPNS_4TaskE_02ca6ab8)(*(undefined8 *)puVar2,plVar4);
  return;
}

// ==== Aska::WaitDraw::Deinstantiate()
// vaddr 0x2169970 | ghidra 0x2269970 | size 48 | symbol _ZN4Aska8WaitDraw13DeinstantiateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8WaitDraw13DeinstantiateEv(void)

{
  undefined *puVar1;
  long *plVar2;
  
  puVar1 = PTR__ZN4Aska8WaitDraw12m_pSingleTonE_02cb77d0;
  plVar2 = *(long **)PTR__ZN4Aska8WaitDraw12m_pSingleTonE_02cb77d0;
  if (plVar2 != (long *)0x0) {
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
    *(undefined8 *)puVar1 = 0;
  }
  return;
}

// ==== Aska::WaitDraw::~WaitDraw()
// vaddr 0x21699a0 | ghidra 0x22699a0 | size 116 | symbol _ZN4Aska8WaitDrawD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8WaitDrawD2Ev(long *param_1)

{
  long lVar1;
  
  lVar1 = param_1[5];
  *param_1 = (long)(PTR__ZTVN4Aska8WaitDrawE_02cc4e90 + 0x10);
  if (lVar1 != 0) {
    Aska::Semaphore::~Semaphore()(lVar1);
    operator delete(void*)(lVar1);
    param_1[5] = 0;
  }
  if ((long *)param_1[6] != (long *)0x0) {
    (**(code **)(*(long *)param_1[6] + 0x10))();
    param_1[6] = 0;
  }
  if (*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 != 0) {
    *(undefined8 *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x4458) = 0;
  }
  (*(code *)PTR__ZN4Aska4TaskD1Ev_02c92d10)(param_1);
  return;
}

// ==== Aska::WaitDraw::~WaitDraw()
// vaddr 0x2169a14 | ghidra 0x2269a14 | size 124 | symbol _ZN4Aska8WaitDrawD0Ev | lib libSOA-3.7.0.so | 2026-10-04
/* WARNING: Possible PIC construction at 0x02269a44: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x02269a48) */

void _ZN4Aska8WaitDrawD0Ev(long *param_1)

{
  long *plVar1;
  
  plVar1 = (long *)param_1[5];
  *param_1 = (long)(PTR__ZTVN4Aska8WaitDrawE_02cc4e90 + 0x10);
  if (plVar1 == (long *)0x0) {
    if ((long *)param_1[6] != (long *)0x0) {
      (**(code **)(*(long *)param_1[6] + 0x10))();
      param_1[6] = 0;
    }
    if (*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 != 0) {
      *(undefined8 *)(*(long *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688 + 0x4458) = 0;
    }
    Aska::Task::~Task()(param_1);
  }
  else {
    Aska::Semaphore::~Semaphore()(plVar1);
    param_1 = plVar1;
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::WaitDraw::Run(int)
// vaddr 0x2169a90 | ghidra 0x2269a90 | size 44 | symbol _ZN4Aska8WaitDraw3RunEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska8WaitDraw3RunEi(long param_1)

{
  Aska::PerformanceCounter::Set(int)(*(undefined8 *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8,0);
  (*(code *)PTR__ZNK4Aska9Semaphore4WaitEv_02ca6750)(*(undefined8 *)(param_1 + 0x28));
  return;
}

// ==== Aska::WaitVSync::Run(int)
// vaddr 0x2169c74 | ghidra 0x2269c74 | size 232 | symbol _ZN4Aska9WaitVSync3RunEi | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9WaitVSync3RunEi(long param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined8 *puVar4;
  long lVar5;
  long lVar6;
  undefined4 uVar7;
  
  puVar2 = PTR__ZN4Aska6Global25m_pResourceHandlerCreatorE_02cc2778;
  lVar5 = *(long *)PTR__ZN4Aska6Global25m_pResourceHandlerCreatorE_02cc2778;
  if (lVar5 != 0) {
    *(undefined8 *)(lVar5 + 0x3278) = 0;
    *(undefined4 *)(lVar5 + 0x3280) = 0;
    Aska::SimpleMessageDispatcher::ResumeWorkerThread()(lVar5);
  }
  puVar3 = PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688;
  Aska::ObjectManager::WaitGPUSync()(*(undefined8 *)PTR__ZN4Aska6Global16m_pObjectManagerE_02cc4688);
  Aska::ShaderLinkManager::Run(int)(*(undefined8 *)PTR__ZN4Aska6Global20m_pShaderLinkManagerE_02cb93f8,0);
  Aska::PerformanceCounter::Set(int)(*(undefined8 *)PTR__ZN4Aska6Global21m_pPerformanceCounterE_02cc3ad8,4);
  puVar1 = PTR__ZN4Aska6Global8m_pVSyncE_02cbd460;
  if (*(char *)(param_1 + 0x38) == '\0') {
    Aska::VSync::UpdateDt(int)(*(undefined8 *)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460,0);
  }
  else {
    Aska::VSync::WaitVSync(int, int)(*(undefined8 *)PTR__ZN4Aska6Global8m_pVSyncE_02cbd460,0,0);
  }
  Aska::ObjectManager::SwapFrame()(*(undefined8 *)puVar3);
  puVar4 = *(undefined8 **)puVar1;
  uVar7 = (**(code **)*puVar4)(puVar4,0);
  lVar6 = *(long *)puVar1;
  lVar5 = *(long *)puVar2;
  *(undefined4 *)PTR__ZN4Aska6Global18m_fSystemDeltaTimeE_02cbfa70 = uVar7;
  *(undefined2 *)PTR__ZN4Aska6Global19m_nSystemDeltaFrameE_02cbda88 = *(undefined2 *)(lVar6 + 0xf0);
  if (lVar5 != 0) {
    (*(code *)PTR__ZN4Aska23SimpleMessageDispatcher19SuspendWorkerThreadEv_02ca1e70)();
    return;
  }
  return;
}

// ==== Aska::WaitVSync::Instantiate()
// vaddr 0x2169d5c | ghidra 0x2269d5c | size 164 | symbol _ZN4Aska9WaitVSync11InstantiateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9WaitVSync11InstantiateEv(void)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined4 uVar3;
  long *plVar4;
  code *pcVar5;
  
  puVar1 = PTR__ZN4Aska9WaitVSync12m_pSingleTonE_02cb7070;
  if (*(long **)PTR__ZN4Aska9WaitVSync12m_pSingleTonE_02cb7070 != (long *)0x0) {
    (**(code **)(**(long **)PTR__ZN4Aska9WaitVSync12m_pSingleTonE_02cb7070 + 8))();
    *(undefined8 *)puVar1 = 0;
  }
  plVar4 = (long *)operator new(unsigned long, std::nothrow_t const&)(0x40,PTR__ZSt7nothrow_02cb9a80);
  puVar2 = PTR__ZTVN4Aska4TaskE_02cbe020;
  if (plVar4 != (long *)0x0) {
    plVar4[2] = 0;
    plVar4[3] = 0;
    *(undefined2 *)((long)plVar4 + 0x24) = 0;
    pcVar5 = *(code **)(puVar2 + 0x68);
    *plVar4 = (long)(puVar2 + 0x10);
    plVar4[1] = 0;
    *(undefined1 *)((long)plVar4 + 0x26) = 0;
    uVar3 = (*pcVar5)(plVar4);
    *(undefined4 *)(plVar4 + 4) = uVar3;
    puVar2 = PTR__ZTVN4Aska9WaitVSyncE_02cb7d38;
    *(undefined1 *)(plVar4 + 7) = 1;
    *plVar4 = (long)(puVar2 + 0x10);
  }
  puVar2 = PTR__ZN4Aska6Global20m_pSystemTaskManagerE_02cbf620;
  *(long **)puVar1 = plVar4;
  (*(code *)PTR__ZN4Aska11TaskManager3AddEPNS_4TaskE_02c95ab0)(*(undefined8 *)puVar2,plVar4);
  return;
}

// ==== Aska::WaitVSync::Deinstantiate()
// vaddr 0x2169e00 | ghidra 0x2269e00 | size 48 | symbol _ZN4Aska9WaitVSync13DeinstantiateEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9WaitVSync13DeinstantiateEv(void)

{
  undefined *puVar1;
  long *plVar2;
  
  puVar1 = PTR__ZN4Aska9WaitVSync12m_pSingleTonE_02cb7070;
  plVar2 = *(long **)PTR__ZN4Aska9WaitVSync12m_pSingleTonE_02cb7070;
  if (plVar2 != (long *)0x0) {
    (**(code **)(*plVar2 + 0x38))(plVar2,0);
    *(undefined8 *)puVar1 = 0;
  }
  return;
}

// ==== Aska::WaitVSync::~WaitVSync()
// vaddr 0x2169e90 | ghidra 0x2269e90 | size 24 | symbol _ZN4Aska9WaitVSyncD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9WaitVSyncD0Ev(undefined8 param_1)

{
  Aska::Task::~Task()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::WaitVSync::GetClassID(int) const
// vaddr 0x2169ea8 | ghidra 0x2269ea8 | size 64 | symbol _ZNK4Aska9WaitVSync10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska9WaitVSync10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 != 0) {
    uVar2 = 0xf000f001;
    if (param_2 != 2) {
      uVar2 = 0xf000;
    }
    uVar1 = 0xf000f001f002;
    if (param_2 != 1) {
      uVar1 = uVar2;
    }
    return uVar1;
  }
  return 0xf002f006;
}

// ==== Aska::WaitVSync::GetDefaultLevel() const
// vaddr 0x2169ee8 | ghidra 0x2269ee8 | size 8 | symbol _ZNK4Aska9WaitVSync15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska9WaitVSync15GetDefaultLevelEv(void)

{
  return 0x10000000;
}

// ==== Aska::WaitDraw::GetClassID(int) const
// vaddr 0x2169f50 | ghidra 0x2269f50 | size 64 | symbol _ZNK4Aska8WaitDraw10GetClassIDEi | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska8WaitDraw10GetClassIDEi(undefined8 param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (param_2 != 0) {
    uVar2 = 0xf000f001;
    if (param_2 != 2) {
      uVar2 = 0xf000;
    }
    uVar1 = 0xf000f001f002;
    if (param_2 != 1) {
      uVar1 = uVar2;
    }
    return uVar1;
  }
  return 0xf002f004;
}

// ==== Aska::WaitDraw::GetDefaultLevel() const
// vaddr 0x2169f90 | ghidra 0x2269f90 | size 8 | symbol _ZNK4Aska8WaitDraw15GetDefaultLevelEv | lib libSOA-3.7.0.so | 2026-10-04
undefined8 _ZNK4Aska8WaitDraw15GetDefaultLevelEv(void)

{
  return 0x400000;
}

// ==== Aska::Global::GetCPUTime()
// vaddr 0x2210de4 | ghidra 0x2310de4 | size 72 | symbol _ZN4Aska6Global10GetCPUTimeEv | lib libSOA-3.7.0.so | 2026-10-04
long _ZN4Aska6Global10GetCPUTimeEv(void)

{
  long lStack_20;
  long lStack_18;
  
  clock_gettime(7,&lStack_20);
  return lStack_18 / 1000000 + lStack_20 * 1000;
}

// ==== Aska::NotifierThread::NotifierThread(int)
// vaddr 0x2235d80 | ghidra 0x2335d80 | size 228 | symbol _ZN4Aska14NotifierThreadC2Ei | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14NotifierThreadC1Ei(long *param_1,undefined4 param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  
  Aska::Thread::Thread()();
  puVar1 = PTR__ZTVN4Aska14NotifierThreadE_02cb7120;
  *(undefined4 *)(param_1 + 7) = 0;
  puVar3 = PTR__ZTVN4Aska4ListE_02cc4bc0;
  puVar2 = PTR__ZTVN4Aska11LinkElementE_02cc16d0;
  param_1[5] = (long)(param_1 + 4);
  param_1[6] = (long)(param_1 + 4);
  *param_1 = (long)(puVar1 + 0x10);
  param_1[4] = (long)(puVar2 + 0x10);
  param_1[3] = (long)(puVar3 + 0x10);
  Aska::Semaphore::Semaphore()(param_1 + 8);
  Aska::Semaphore::Semaphore()(param_1 + 0xb);
  puVar1 = PTR__ZTVN4Aska9TPoolFastINS_14NotifierThread13NotifyElementELb0EEE_02cc38e0 + 0x10;
  param_1[0xf] = (long)(PTR__ZTVN4Aska9TBitArrayImLb0EEE_02cbeda0 + 0x10);
  param_1[0xe] = (long)puVar1;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined1 *)(param_1 + 0x13) = 0;
  *(undefined1 *)((long)param_1 + 0xb1) = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  Aska::Semaphore::Create(int, int)(param_1 + 0xb,0,0x100);
  Aska::Semaphore::Create(int, int)(param_1 + 8,1,1);
  (*(code *)
    PTR__ZN4Aska9TPoolFastINS_14NotifierThread13NotifyElementELb0EE10SecurePoolEjPS2__02c9e208)
            (param_1 + 0xe,param_2,0);
  return;
}

// ==== Aska::TPoolFast<Aska::NotifierThread::NotifyElement, false>::SecurePool(unsigned int, Aska::NotifierThread::NotifyElement*)
// vaddr 0x2235e64 | ghidra 0x2335e64 | size 536 | symbol _ZN4Aska9TPoolFastINS_14NotifierThread13NotifyElementELb0EE10SecurePoolEjPS2_ | lib libSOA-3.7.0.so | 2026-10-04
undefined8
_ZN4Aska9TPoolFastINS_14NotifierThread13NotifyElementELb0EE10SecurePoolEjPS2_
          (long param_1,uint param_2,long param_3)

{
  bool bVar1;
  uint uVar2;
  ulong *puVar3;
  undefined *puVar4;
  ulong *puVar5;
  long lVar6;
  undefined8 uVar7;
  long lVar8;
  uint uVar9;
  ulong uVar10;
  long *plVar11;
  uint *puVar12;
  
  if (*(char *)(param_1 + 0x41) == '\0') {
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  else {
    if (*(long *)(param_1 + 0x30) != 0) {
      operator delete[](void*)(*(long *)(param_1 + 0x30) + -8);
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    *(undefined1 *)(param_1 + 0x41) = 0;
  }
  plVar11 = (long *)(param_1 + 0x18);
  if ((*plVar11 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x28) = 0;
  }
  *plVar11 = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  if (param_2 == 0) {
    return 1;
  }
  if (param_3 == 0) {
    puVar5 = (ulong *)operator new[](unsigned long, std::nothrow_t const&)((ulong)param_2 * 0x28 + 8,PTR__ZSt7nothrow_02cb9a80);
    puVar4 = PTR__ZTVN4Aska14NotifierThread13NotifyElementE_02cb7108;
    if (puVar5 != (ulong *)0x0) {
      *puVar5 = (ulong)param_2;
      lVar6 = (ulong)param_2 * 0x28;
      puVar3 = puVar5;
      do {
        puVar3[1] = (ulong)(puVar4 + 0x10);
        puVar3[2] = 0;
        puVar3[3] = 0;
        puVar3[4] = 0;
        *(undefined4 *)(puVar3 + 5) = 0;
        lVar6 = lVar6 + -0x28;
        puVar3 = puVar3 + 5;
      } while (lVar6 != 0);
      *(ulong **)(param_1 + 0x30) = puVar5 + 1;
      *(undefined1 *)(param_1 + 0x41) = 1;
      goto code_r0x02335f38;
    }
    *(undefined8 *)(param_1 + 0x30) = 0;
    if (*(char *)(param_1 + 0x41) != '\0') goto code_r0x02336010;
code_r0x02336058:
    lVar6 = 0;
    *(undefined8 *)(param_1 + 0x30) = 0;
    bVar1 = false;
joined_r0x02336060:
    if ((bVar1) && (*(char *)(param_1 + 0x28) != '\0')) {
      operator delete[](void*)(lVar6);
      *(undefined1 *)(param_1 + 0x28) = 0;
    }
    uVar7 = 0;
    *plVar11 = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  else {
    *(long *)(param_1 + 0x30) = param_3;
code_r0x02335f38:
    uVar10 = (ulong)param_2 + 0x3f >> 6;
    uVar9 = (uint)uVar10;
    if ((*(char *)(param_1 + 0x28) == '\0') || (uVar2 = *(uint *)(param_1 + 0x20), uVar2 < uVar9)) {
      if ((*plVar11 != 0) && (*(char *)(param_1 + 0x28) != '\0')) {
        operator delete[](void*)();
        *(undefined1 *)(param_1 + 0x28) = 0;
      }
      puVar12 = (uint *)(param_1 + 0x20);
      *puVar12 = uVar9;
      *(uint *)(param_1 + 0x24) = param_2;
      lVar8 = uVar10 << 3;
      lVar6 = operator new[](unsigned long, std::nothrow_t const&)(lVar8,PTR__ZSt7nothrow_02cb9a80);
      *(long *)(param_1 + 0x18) = lVar6;
      *(undefined1 *)(param_1 + 0x28) = 1;
      if (lVar6 == 0) {
        *(undefined1 *)(param_1 + 0x28) = 0;
        puVar12[0] = 0;
        puVar12[1] = 0;
        if (*(char *)(param_1 + 0x41) == '\0') goto code_r0x02336058;
code_r0x02336010:
        lVar6 = 0;
        if (*(long *)(param_1 + 0x30) != 0) {
          operator delete[](void*)(*(long *)(param_1 + 0x30) + -8);
          lVar6 = *(long *)(param_1 + 0x18);
          *(undefined8 *)(param_1 + 0x30) = 0;
        }
        *(undefined1 *)(param_1 + 0x41) = 0;
        bVar1 = lVar6 != 0;
        goto joined_r0x02336060;
      }
      if (uVar9 == 0) goto code_r0x02335ff4;
      memset(lVar6,0,lVar8);
      *(undefined8 *)(param_1 + 0x38) = 0;
    }
    else {
      *(uint *)(param_1 + 0x24) = param_2;
      if (uVar2 == 0) {
code_r0x02335ff4:
        *(undefined8 *)(param_1 + 0x38) = 0;
        return 1;
      }
      memset(*(undefined8 *)(param_1 + 0x18),0,uVar2 << 3);
      uVar9 = *(uint *)(param_1 + 0x20);
      *(undefined8 *)(param_1 + 0x38) = 0;
      if (uVar9 == 0) {
        return 1;
      }
    }
    memset(*plVar11,0,uVar9 << 3);
    uVar7 = 1;
  }
  return uVar7;
}

// ==== Aska::NotifierThread::~NotifierThread()
// vaddr 0x223607c | ghidra 0x233607c | size 444 | symbol _ZN4Aska14NotifierThreadD1Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14NotifierThreadD2Ev(long *param_1)

{
  long *plVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  long lVar5;
  undefined *puStack_38;
  long *plStack_30;
  long *plStack_28;
  
  *param_1 = (long)(PTR__ZTVN4Aska14NotifierThreadE_02cb7120 + 0x10);
  plVar1 = (long *)param_1[6];
  while (param_1 + 4 != plVar1) {
    plVar2 = (long *)plVar1[2];
    uVar4 = ((long)plVar1 - param_1[0x14] >> 3) * -0x3333333333333333;
    lVar5 = (uVar4 >> 6 & 0x3ffffff) * 8;
    *(ulong *)(param_1[0x11] + lVar5) =
         *(ulong *)(param_1[0x11] + lVar5) & (1L << (uVar4 & 0x3f) ^ 0xffffffffffffffffU);
    *(int *)((long)param_1 + 0xac) = *(int *)((long)param_1 + 0xac) + -1;
    plVar1 = plVar2;
  }
  plVar1 = param_1 + 0xb;
  puStack_38 = PTR__ZTV10ExitNotify_02cc3db8 + 0x10;
  plStack_30 = plVar1;
  plStack_28 = param_1;
  Aska::NotifierThread::AddNotify(Aska::INotify*, unsigned int)(param_1,&puStack_38,0);
  Aska::Semaphore::Signal() const(plVar1);
  Aska::Thread::WaitEnd()(param_1);
  plVar2 = (long *)param_1[6];
  while (param_1 + 4 != plVar2) {
    plVar3 = (long *)plVar2[2];
    uVar4 = ((long)plVar2 - param_1[0x14] >> 3) * -0x3333333333333333;
    lVar5 = (uVar4 >> 6 & 0x3ffffff) * 8;
    *(ulong *)(param_1[0x11] + lVar5) =
         *(ulong *)(param_1[0x11] + lVar5) & (1L << (uVar4 & 0x3f) ^ 0xffffffffffffffffU);
    *(int *)((long)param_1 + 0xac) = *(int *)((long)param_1 + 0xac) + -1;
    plVar2 = plVar3;
  }
  param_1[0xe] = (long)(PTR__ZTVN4Aska9TPoolFastINS_14NotifierThread13NotifyElementELb0EEE_02cc38e0
                       + 0x10);
  if (*(char *)((long)param_1 + 0xb1) == '\0') {
    param_1[0x14] = 0;
  }
  else {
    if (param_1[0x14] != 0) {
      operator delete[](void*)(param_1[0x14] + -8);
      param_1[0x14] = 0;
    }
    *(undefined1 *)((long)param_1 + 0xb1) = 0;
  }
  if ((param_1[0x11] != 0) && ((char)param_1[0x13] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 0x13) = 0;
  }
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0xf] = (long)(PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10);
  Aska::Semaphore::~Semaphore()(plVar1);
  Aska::Semaphore::~Semaphore()(param_1 + 8);
  Aska::Thread::~Thread()(param_1);
  return;
}

// ==== Aska::NotifierThread::AddNotify(Aska::INotify*, unsigned int)
// vaddr 0x2236238 | ghidra 0x2336238 | size 256 | symbol _ZN4Aska14NotifierThread9AddNotifyEPNS_7INotifyEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14NotifierThread9AddNotifyEPNS_7INotifyEj
               (long param_1,undefined8 param_2,undefined4 param_3)

{
  ulong *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  
  Aska::Semaphore::Wait() const(param_1 + 0x40);
  uVar2 = *(uint *)(param_1 + 0x94);
  if (*(uint *)(param_1 + 0xac) < uVar2) {
    uVar3 = *(uint *)(param_1 + 0xa8);
    uVar6 = (ulong)uVar3;
    *(uint *)(param_1 + 0xac) = *(uint *)(param_1 + 0xac) + 1;
    puVar1 = (ulong *)(*(long *)(param_1 + 0x88) + (ulong)(uVar3 >> 6) * 8);
    uVar9 = *puVar1;
    uVar10 = 1L << (uVar6 & 0x3f);
    uVar11 = uVar10 & uVar9;
    while (uVar11 != 0) {
      uVar3 = (int)uVar6 + 1;
      uVar4 = 0;
      if (uVar2 != 0) {
        uVar4 = uVar3 / uVar2;
      }
      uVar3 = uVar3 - uVar4 * uVar2;
      uVar6 = (ulong)uVar3;
      puVar1 = (ulong *)(*(long *)(param_1 + 0x88) + (ulong)(uVar3 >> 6) * 8);
      uVar9 = *puVar1;
      uVar10 = 1L << (uVar3 & 0x3f);
      uVar11 = uVar10 & uVar9;
    }
    *puVar1 = uVar10 | uVar9;
    uVar4 = 0;
    if (uVar2 != 0) {
      uVar4 = (uVar3 + 1) / uVar2;
    }
    lVar5 = *(long *)(param_1 + 0xa0) + (ulong)uVar3 * 0x28;
    *(uint *)(param_1 + 0xa8) = (uVar3 + 1) - uVar4 * uVar2;
    if (lVar5 != 0) {
      lVar7 = *(long *)(param_1 + 0xa0) + (ulong)uVar3 * 0x28;
      *(undefined8 *)(lVar7 + 0x18) = param_2;
      *(undefined4 *)(lVar7 + 0x20) = param_3;
      lVar8 = *(long *)(param_1 + 0x28);
      *(long *)(lVar7 + 8) = lVar8;
      *(long *)(lVar7 + 0x10) = param_1 + 0x20;
      *(long *)(param_1 + 0x28) = lVar5;
      *(long *)(lVar8 + 0x10) = lVar5;
      *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + 1;
    }
  }
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x40);
  return;
}

// ==== Aska::TPoolFast<Aska::NotifierThread::NotifyElement, false>::~TPoolFast()
// vaddr 0x2236338 | ghidra 0x2336338 | size 128 | symbol _ZN4Aska9TPoolFastINS_14NotifierThread13NotifyElementELb0EED2Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9TPoolFastINS_14NotifierThread13NotifyElementELb0EED2Ev(long *param_1)

{
  *param_1 = (long)(PTR__ZTVN4Aska9TPoolFastINS_14NotifierThread13NotifyElementELb0EEE_02cc38e0 +
                   0x10);
  if (*(char *)((long)param_1 + 0x41) == '\0') {
    param_1[6] = 0;
  }
  else {
    if (param_1[6] != 0) {
      operator delete[](void*)(param_1[6] + -8);
      param_1[6] = 0;
    }
    *(undefined1 *)((long)param_1 + 0x41) = 0;
  }
  if ((param_1[3] != 0) && ((char)param_1[5] != '\0')) {
    operator delete[](void*)();
    *(undefined1 *)(param_1 + 5) = 0;
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[1] = (long)(PTR__ZTVN4Aska13TSmartPointerILb0EEE_02cc2320 + 0x10);
  return;
}

// ==== Aska::NotifierThread::~NotifierThread()
// vaddr 0x22363b8 | ghidra 0x23363b8 | size 24 | symbol _ZN4Aska14NotifierThreadD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14NotifierThreadD0Ev(undefined8 param_1)

{
  Aska::NotifierThread::~NotifierThread()();
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::NotifierThread::Init()
// vaddr 0x22363d0 | ghidra 0x23363d0 | size 48 | symbol _ZN4Aska14NotifierThread4InitEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14NotifierThread4InitEv(long *param_1)

{
  undefined4 uVar1;
  
  uVar1 = (**(code **)(*param_1 + 0x18))();
  (*(code *)PTR__ZN4Aska6Thread6CreateEbiib_02c95600)(param_1,0,uVar1,0x3000,1);
  return;
}

// ==== Aska::NotifierThread::Handler()
// vaddr 0x2236400 | ghidra 0x2336400 | size 44 | symbol _ZN4Aska14NotifierThread7HandlerEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14NotifierThread7HandlerEv(long *param_1)

{
  do {
    Aska::Semaphore::Wait() const(param_1 + 0xb);
    (**(code **)(*param_1 + 0x28))(param_1);
  } while( true );
}

// ==== Aska::NotifierThread::Notify()
// vaddr 0x223642c | ghidra 0x233642c | size 316 | symbol _ZN4Aska14NotifierThread6NotifyEv | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14NotifierThread6NotifyEv(long param_1)

{
  long lVar1;
  int iVar2;
  undefined8 *puVar3;
  long lVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  long *plVar9;
  long alStack_230 [64];
  
  lVar1 = param_1 + 0x40;
  Aska::Semaphore::Wait() const(lVar1);
  lVar4 = *(long *)(param_1 + 0x30);
  if ((param_1 + 0x20 == lVar4) || (lVar4 == 0)) {
    Aska::Semaphore::Signal() const(lVar1);
  }
  else {
    uVar5 = 0;
    do {
      lVar6 = *(long *)(lVar4 + 0x10);
      if ((*(int *)(lVar4 + 0x20) != 0) &&
         (iVar2 = *(int *)(lVar4 + 0x20) + -1, *(int *)(lVar4 + 0x20) = iVar2, iVar2 == 0)) {
        lVar8 = *(long *)(lVar4 + 8);
        if (lVar8 != 0) {
          *(long *)(lVar8 + 0x10) = lVar6;
        }
        if (lVar6 != 0) {
          *(long *)(lVar6 + 8) = lVar8;
        }
        if (0 < *(int *)(param_1 + 0x38)) {
          *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + -1;
        }
        *(long *)(lVar4 + 8) = 0;
        *(undefined8 *)(lVar4 + 0x10) = 0;
        uVar7 = (lVar4 - *(long *)(param_1 + 0xa0) >> 3) * -0x3333333333333333;
        lVar8 = (uVar7 >> 6 & 0x3ffffff) * 8;
        *(ulong *)(*(long *)(param_1 + 0x88) + lVar8) =
             *(ulong *)(*(long *)(param_1 + 0x88) + lVar8) &
             (1L << (uVar7 & 0x3f) ^ 0xffffffffffffffffU);
        *(int *)(param_1 + 0xac) = *(int *)(param_1 + 0xac) + -1;
      }
      uVar7 = uVar5 + 1;
      alStack_230[uVar5] = lVar4;
    } while ((param_1 + 0x20 != lVar6) && (lVar4 = lVar6, uVar5 = uVar7, lVar6 != 0));
    Aska::Semaphore::Signal() const(lVar1);
    if (0 < (int)uVar7) {
      uVar7 = uVar7 & 0xffffffff;
      plVar9 = alStack_230;
      do {
        puVar3 = *(undefined8 **)(*plVar9 + 0x18);
        (**(code **)*puVar3)(puVar3,puVar3);
        uVar7 = uVar7 - 1;
        plVar9 = plVar9 + 1;
      } while (uVar7 != 0);
    }
  }
  return;
}

// ==== Aska::NotifierThread::AddPriorityNotify(Aska::INotify*, unsigned int)
// vaddr 0x2236568 | ghidra 0x2336568 | size 256 | symbol _ZN4Aska14NotifierThread17AddPriorityNotifyEPNS_7INotifyEj | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14NotifierThread17AddPriorityNotifyEPNS_7INotifyEj
               (long param_1,undefined8 param_2,undefined4 param_3)

{
  ulong *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  long lVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  
  Aska::Semaphore::Wait() const(param_1 + 0x40);
  uVar2 = *(uint *)(param_1 + 0x94);
  if (*(uint *)(param_1 + 0xac) < uVar2) {
    uVar3 = *(uint *)(param_1 + 0xa8);
    uVar6 = (ulong)uVar3;
    *(uint *)(param_1 + 0xac) = *(uint *)(param_1 + 0xac) + 1;
    puVar1 = (ulong *)(*(long *)(param_1 + 0x88) + (ulong)(uVar3 >> 6) * 8);
    uVar9 = *puVar1;
    uVar10 = 1L << (uVar6 & 0x3f);
    uVar11 = uVar10 & uVar9;
    while (uVar11 != 0) {
      uVar3 = (int)uVar6 + 1;
      uVar4 = 0;
      if (uVar2 != 0) {
        uVar4 = uVar3 / uVar2;
      }
      uVar3 = uVar3 - uVar4 * uVar2;
      uVar6 = (ulong)uVar3;
      puVar1 = (ulong *)(*(long *)(param_1 + 0x88) + (ulong)(uVar3 >> 6) * 8);
      uVar9 = *puVar1;
      uVar10 = 1L << (uVar3 & 0x3f);
      uVar11 = uVar10 & uVar9;
    }
    *puVar1 = uVar10 | uVar9;
    uVar4 = 0;
    if (uVar2 != 0) {
      uVar4 = (uVar3 + 1) / uVar2;
    }
    lVar5 = *(long *)(param_1 + 0xa0) + (ulong)uVar3 * 0x28;
    *(uint *)(param_1 + 0xa8) = (uVar3 + 1) - uVar4 * uVar2;
    if (lVar5 != 0) {
      lVar7 = *(long *)(param_1 + 0xa0) + (ulong)uVar3 * 0x28;
      *(undefined8 *)(lVar7 + 0x18) = param_2;
      *(undefined4 *)(lVar7 + 0x20) = param_3;
      lVar8 = *(long *)(param_1 + 0x30);
      *(long *)(lVar7 + 8) = param_1 + 0x20;
      *(long *)(lVar7 + 0x10) = lVar8;
      *(long *)(lVar8 + 8) = lVar5;
      *(long *)(param_1 + 0x30) = lVar5;
      *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + 1;
    }
  }
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x40);
  return;
}

// ==== Aska::NotifierThread::RemoveNotify(Aska::INotify*)
// vaddr 0x2236668 | ghidra 0x2336668 | size 192 | symbol _ZN4Aska14NotifierThread12RemoveNotifyEPNS_7INotifyE | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14NotifierThread12RemoveNotifyEPNS_7INotifyE(long param_1,long param_2)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  Aska::Semaphore::Wait() const(param_1 + 0x40);
  lVar3 = *(long *)(param_1 + 0x30);
  do {
    lVar2 = lVar3;
    if (param_1 + 0x20 == lVar2) goto code_r0x011bd9c0;
    lVar3 = *(long *)(lVar2 + 0x10);
  } while (*(long *)(lVar2 + 0x18) != param_2);
  lVar4 = *(long *)(lVar2 + 8);
  if (lVar4 != 0) {
    *(long *)(lVar4 + 0x10) = lVar3;
  }
  if (lVar3 != 0) {
    *(long *)(lVar3 + 8) = lVar4;
  }
  if (0 < *(int *)(param_1 + 0x38)) {
    *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + -1;
  }
  *(long *)(lVar2 + 8) = 0;
  *(undefined8 *)(lVar2 + 0x10) = 0;
  uVar1 = (lVar2 - *(long *)(param_1 + 0xa0) >> 3) * -0x3333333333333333;
  lVar3 = (uVar1 >> 6 & 0x3ffffff) * 8;
  *(ulong *)(*(long *)(param_1 + 0x88) + lVar3) =
       *(ulong *)(*(long *)(param_1 + 0x88) + lVar3) & (1L << (uVar1 & 0x3f) ^ 0xffffffffffffffffU);
  *(int *)(param_1 + 0xac) = *(int *)(param_1 + 0xac) + -1;
code_r0x011bd9c0:
  (*(code *)PTR__ZNK4Aska9Semaphore6SignalEv_02c96cd0)(param_1 + 0x40);
  return;
}

// ==== Aska::NotifierThread::QueryNotify(Aska::INotify*)
// vaddr 0x2236728 | ghidra 0x2336728 | size 104 | symbol _ZN4Aska14NotifierThread11QueryNotifyEPNS_7INotifyE | lib libSOA-3.7.0.so | 2026-10-04
undefined4 _ZN4Aska14NotifierThread11QueryNotifyEPNS_7INotifyE(long param_1,long param_2)

{
  long lVar1;
  undefined4 uVar2;
  
  Aska::Semaphore::Wait() const(param_1 + 0x40);
  lVar1 = *(long *)(param_1 + 0x30);
  do {
    if (param_1 + 0x20 == lVar1) {
      uVar2 = 0;
code_r0x02336778:
      Aska::Semaphore::Signal() const(param_1 + 0x40);
      return uVar2;
    }
    if (*(long *)(lVar1 + 0x18) == param_2) {
      uVar2 = 1;
      goto code_r0x02336778;
    }
    lVar1 = *(long *)(lVar1 + 0x10);
  } while( true );
}

// ==== Aska::TPoolFast<Aska::NotifierThread::NotifyElement, false>::~TPoolFast()
// vaddr 0x2236798 | ghidra 0x2336798 | size 104 | symbol _ZN4Aska9TPoolFastINS_14NotifierThread13NotifyElementELb0EED0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska9TPoolFastINS_14NotifierThread13NotifyElementELb0EED0Ev(long *param_1)

{
  long lVar1;
  
  *param_1 = (long)(PTR__ZTVN4Aska9TPoolFastINS_14NotifierThread13NotifyElementELb0EEE_02cc38e0 +
                   0x10);
  if (*(char *)((long)param_1 + 0x41) == '\0') {
    param_1[6] = 0;
    lVar1 = param_1[3];
  }
  else {
    if (param_1[6] != 0) {
      operator delete[](void*)(param_1[6] + -8);
      param_1[6] = 0;
    }
    *(undefined1 *)((long)param_1 + 0x41) = 0;
    lVar1 = param_1[3];
  }
  if ((lVar1 != 0) && ((char)param_1[5] != '\0')) {
    operator delete[](void*)();
  }
  (*(code *)PTR__ZdlPv_02ca4758)(param_1);
  return;
}

// ==== Aska::NotifierThread::NotifyElement::~NotifyElement()
// vaddr 0x2236800 | ghidra 0x2336800 | size 4 | symbol _ZN4Aska14NotifierThread13NotifyElementD0Ev | lib libSOA-3.7.0.so | 2026-10-04
void _ZN4Aska14NotifierThread13NotifyElementD0Ev(void)

{
  (*(code *)PTR__ZdlPv_02ca4758)();
  return;
}


// FAILED to create function at 029d90a0 typeinfo name for Aska::TPoolFast<Aska::NotifierThread::NotifyElement, false>
// FAILED to create function at 029d90e0 typeinfo name for Aska::NotifierThread::NotifyElement
// FAILED to create function at 02bab498 Framework::CTimeElement::vtable
// FAILED to create function at 02bab4e0 Framework::CTimeElement::typeinfo
// FAILED to create function at 02bb29e8 Aska::PerformanceCounter::vtable
// FAILED to create function at 02bb2a08 Aska::PerformanceCounter::typeinfo
// FAILED to create function at 02bb4b18 Aska::VSync::vtable
// FAILED to create function at 02bb4bb0 Aska::VSync::typeinfo
// FAILED to create function at 02c4fa78 Aska::WaitDraw::vtable
// FAILED to create function at 02c4fbe8 Aska::WaitVSync::vtable
// FAILED to create function at 02c4fc90 Aska::WaitVSync::typeinfo
// FAILED to create function at 02c4fd70 Aska::WaitDraw::typeinfo
// FAILED to create function at 02c5ec18 Aska::NotifierThread::vtable
// FAILED to create function at 02c5eca0 Aska::NotifierThread::typeinfo
// FAILED to create function at 02c5ecf8 Aska::TPoolFast<Aska::NotifierThread::NotifyElement,false>::vtable
// FAILED to create function at 02c5ed18 Aska::TPoolFast<Aska::NotifierThread::NotifyElement,false>::typeinfo
// FAILED to create function at 02c5ed28 Aska::NotifierThread::NotifyElement::vtable
// FAILED to create function at 02c5ed50 Aska::NotifierThread::NotifyElement::typeinfo
// FAILED to create function at 02dcd950 Aska::VSync::m_nVSyncCounter
// FAILED to create function at 02dcd958 Aska::VSync::m_event
// FAILED to create function at 02dcd9c0 Aska::VSync::m_evSync
// FAILED to create function at 02dcda28 Aska::VSync::m_evRTSync
// FAILED to create function at 02dd06b8 Aska::WaitDraw::m_pSingleTon
// FAILED to create function at 02dd06d0 Aska::WaitVSync::m_pSingleTon
